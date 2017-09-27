//
//  AutoUpdate.cpp
//  tdht
//
//  Created by hucanhua on 16/8/8.
//
//

#include "AutoUpdate.h"

#include "unzip/unzip.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "Md5Ex.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::network;
AutoUpdate* AutoUpdate::s_AutoUpdate = nullptr;

#define VERSION_FILENAME        "version.manifest"
#define TEMP_VERSION_FILENAME   "version.manifest.temp"
#define PROJECT_FILENAME        "project.manifest"
#define TEMP_PROJECT_FILENAME   "project.manifest.temp"

const std::string AutoUpdate::VERSION_ID = "version";
const std::string AutoUpdate::PROJECT_ID = "project";

#define BUFFER_SIZE    8192
#define MAX_FILENAME   512

AutoUpdate::AutoUpdate()
: _enableUpdate(true)
, _isDownloadVersion(false)
, _isDownloadProject(false)
, _isNeedUpdateSrc(false)
, _isNeedUpdateRes(false)
, _isExistFailRes(false)
//
, _updateUrl("")
, _srcUrl("")
, _downloadUrl("")
, _updateStoragePath("")
, _downloadStoragePath("")
//json
, _localVersionManifest(nullptr)
, _remoteVersionManifest(nullptr)
, _localProjectManifest(nullptr)
, _remoteProjectManifest(nullptr)
//
, _percent(0)
, _luaTotalSize(0)
, _resTotalSize(0)
//
, _projectErrorTimes(0)
, _srcErrorTimes(0)
, _resErrorTimes(0)
{
}

AutoUpdate::~AutoUpdate()
{
    destroyDownloader();
}

AutoUpdate* AutoUpdate::getInstance()
{
    if (s_AutoUpdate == nullptr)
    {
        s_AutoUpdate = new AutoUpdate();
    }
    return s_AutoUpdate;
}

void AutoUpdate::initUpdate()
{
    _fileUtils = FileUtils::getInstance();
    createDownloader();
    setStoragePath();
    initManifests();
    
    // Add search paths
    _fileUtils->addSearchPath(_updateStoragePath);
    _fileUtils->addSearchPath(_updateStoragePath + "src/");
    _fileUtils->addSearchPath(_updateStoragePath + "res/");
    
    _fileUtils->addSearchPath(_downloadStoragePath);
    _fileUtils->addSearchPath(_downloadStoragePath + "res/");
}

void AutoUpdate::createDownloader()
{
    _localVersionManifest = new ManifestEx();
    _remoteVersionManifest = new ManifestEx();
    _localProjectManifest = new ManifestEx();
    _remoteProjectManifest = new ManifestEx();
    
    _downloader = new Downloader();
    _downloader->onTaskError = [this](const DownloadTask& task,
                                      int errorCode,
                                      int errorCodeInternal,
                                      const std::string& errorStr)
    {
        this->onError(task.requestURL, task.storagePath, task.identifier);
    };
    

    _downloader->onTaskProgress = [this](const network::DownloadTask& task,
                                         int64_t bytesReceived,
                                         int64_t totalBytesReceived,
                                         int64_t totalBytesExpected)
    {
        this->onProgress(totalBytesExpected, totalBytesReceived, task.requestURL, task.identifier);
    };
    
    _downloader->onFileTaskSuccess = [this](const network::DownloadTask& task)
    {
        this->onSuccess(task.requestURL, task.storagePath, task.identifier);
    };
}

void AutoUpdate::destroyDownloader()
{
    _downloader->onTaskError = (nullptr);
    _downloader->onFileTaskSuccess = (nullptr);
    _downloader->onTaskProgress = (nullptr);
    CC_SAFE_DELETE(_downloader);
    CC_SAFE_RELEASE(_localVersionManifest);
    CC_SAFE_RELEASE(_remoteVersionManifest);
    CC_SAFE_RELEASE(_localProjectManifest);
    CC_SAFE_RELEASE(_remoteProjectManifest);
}

void AutoUpdate::setStoragePath()
{
    _updateStoragePath = _fileUtils->getWritablePath() + "Update/";
    _downloadStoragePath = _fileUtils->getWritablePath() + "Download/";
    
    _fileUtils->createDirectory(_updateStoragePath);
    _fileUtils->createDirectory(_downloadStoragePath);
    CCLOG("updateStoragePath:%s",  _updateStoragePath.c_str());
    CCLOG("downloadStoragePath:%s",  _downloadStoragePath.c_str());
}

void AutoUpdate::initManifests()
{
    std::string cacheVersionPath = _updateStoragePath + VERSION_FILENAME;
    ManifestEx *cacheVersionManifest = nullptr;
    if (_fileUtils->isFileExist(cacheVersionPath))
    {
        cacheVersionManifest = new ManifestEx();
        cacheVersionManifest->parseVersion(cacheVersionPath);
        if (!cacheVersionManifest->isLoaded())
        {
            _fileUtils->removeFile(cacheVersionPath);
            CC_SAFE_RELEASE(cacheVersionManifest);
            cacheVersionManifest = nullptr;
        }
    }
    
    // Load local version file
    _localVersionManifest->parseVersion(VERSION_FILENAME);
    if (!_localVersionManifest->isLoaded())
    {
        CCLOG("AutoUpdate : No local version file found error.\n");
        return;
    }
    
    _updateUrl = _localVersionManifest->getUpdateUrl() + "Update/";
    _srcUrl = _localVersionManifest->getSrcUrl() + "Update/";
    _downloadUrl = _localVersionManifest->getUpdateUrl() + "Download/";
    _enableUpdate = _localVersionManifest->isEnableUpdate();
    
    // Compare with cached manifest to determine which one to use
    if (cacheVersionManifest) {
        if (_localVersionManifest->getVersion() >= cacheVersionManifest->getVersion())
        {
            // Recreate storage, to empty the content
            _fileUtils->removeDirectory(_updateStoragePath);
            _fileUtils->createDirectory(_updateStoragePath);
            CC_SAFE_RELEASE(cacheVersionManifest);
        }
        else
        {
            CC_SAFE_RELEASE(_localVersionManifest);
            _localVersionManifest = cacheVersionManifest;
        }
    }
}


void AutoUpdate::onError(const std::string &srcUrl, const std::string &storagePath, const std::string &customId)
{
    if (customId == VERSION_ID)
    {
        CCLOG("AutoUpdate : Fail to download version file, step skipped\n");
        updateFail(customId);
    }
    else if (customId == PROJECT_ID)
    {
        CCLOG("AutoUpdate : Fail to download project file, step skipped\n");
        _projectErrorTimes++;
        updateFail(customId);
    }
    else if (isExtendRes(customId))
    {
        setExtendResState(customId, ExtendResState::FAIL);
        updateExtendResFinish();
    }
    else
    {
        auto unitIt = _downloadUnits.find(customId);
        // Found unit and add it to failed units
        if (unitIt != _downloadUnits.end())
        {
            _totalWaitToDownload--;
            
            DownloadUnit unit = unitIt->second;
            _failedUnits.emplace(unit.customId, unit);
        }
        CCLOG("AutoUpdate : Fail to download %s file, step skipped\n", customId.c_str());
        
        if (_totalWaitToDownload <= 0)
        {
            this->updateResFinished();
        }
    }
}

void AutoUpdate::onProgress(double total, double downloaded, const std::string &url, const std::string &customId)
{
    if (customId == VERSION_ID || customId == PROJECT_ID)
    {
        //
    }
    else if (isExtendRes(customId))
    {
        int currentPercent = (int)(100 * downloaded / total);
        updateProgress(customId, currentPercent);
    }
    else
    {
        // Calcul total downloaded
        bool found = false;
        double totalDownloaded = 0;
        for (auto it = _downloadedSize.begin(); it != _downloadedSize.end(); ++it)
        {
            if (it->first == customId)
            {
                if (_isExistFailRes)
                {
                    if (downloaded > it->second)
                    {
                        it->second = downloaded;
                    }
                }
                else
                {
                    it->second = downloaded;
                }
                found = true;
            }
            totalDownloaded += it->second;
        }
        
        // Collect information if not registed
        if (!found)
        {
            // Register the download size information
            _downloadedSize.emplace(customId, downloaded);
            totalDownloaded += downloaded;
        }
        
        int currentPercent = (int)(100 * totalDownloaded / _totalSize);
        if (currentPercent > _percent + 1 || currentPercent == 100) {
            _percent = currentPercent;
            updateProgress(customId, currentPercent);
            CCLOG("%s update progress %d", customId.c_str(), currentPercent);
        }
    }
}

void AutoUpdate::onSuccess(const std::string &srcUrl, const std::string &storagePath, const std::string &customId)
{
	if (customId == VERSION_ID)
    {
        CCLOG("AutoUpdate : version.manifest Success.\n");
        parseVersion(storagePath);
    }
    else if (customId == PROJECT_ID)
    {
        CCLOG("AutoUpdate : project.manifest Success.\n");
        parseProject(storagePath);
    }
    else if (isExtendRes(customId))
    {
        asyncDecompress(storagePath, customId);
    }
    else
    {
        bool isSuccess = true;
        auto &assets = _remoteProjectManifest->getAssets();
        auto assetIt = assets.find(customId);
        if (assetIt != assets.end())
        {
            //校验文件md5
            std::string md5AStr = assetIt->second.md5;
            CCLOG("cdn md5 A::%s", md5AStr.c_str());
            
            MD5 md5;
            std::string md5BStr = md5.fileDigest(storagePath);
            CCLOG("cdn md5 B::%s", md5BStr.c_str());
            
            if (md5BStr == md5AStr)
            {
                // Set download state to SUCCESSED
                _remoteProjectManifest->setAssetDownloadState(customId, ManifestEx::DownloadState::SUCCESSED);
            }
            else
            {
                isSuccess = false;
            }
        }
        
        auto unitIt = _downloadUnits.find(customId);
        if (unitIt != _downloadUnits.end())
        {
            // Reduce count only when unit found in _downloadUnits
            _totalWaitToDownload--;
            CCLOG("download file name:%s", customId.c_str());
            if (!isSuccess)
            {
                DownloadUnit unit = unitIt->second;
                _failedUnits.emplace(unit.customId, unit);
            }
        }
        
        if (isSuccess)
        {
            unitIt = _failedUnits.find(customId);
            // Found unit and delete it
            if (unitIt != _failedUnits.end())
            {
                // Remove from failed units list
                _failedUnits.erase(unitIt);
            }
        }
        
        if (_totalWaitToDownload <= 0)
        {
            updateResFinished();
        }
    }
}


void AutoUpdate::asyncDecompress(const std::string &zip, const std::string &customId)
{
    std::thread([this, zip, customId]()
    {
        do
        {
            // Uncompress zip file.
            if (! decompress(zip))
            {
                setExtendResState(customId, ExtendResState::FAIL);
                FileUtils::getInstance()->removeFile(zip);
                Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]{
                    this->updateExtendResFinish();
                });
                break;
            }
            
            setExtendResState(customId, ExtendResState::SUCCESS);
            FileUtils::getInstance()->removeFile(zip);
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this] {
                this->updateExtendResFinish();
            });
                        
        } while (0);
                    
    }).detach();
}

std::string AutoUpdate::basename(const std::string& path) const
{
    size_t found = path.find_last_of("/\\");
    
    if (std::string::npos != found)
    {
        return path.substr(0, found);
    }
    else
    {
        return path;
    }
}

bool AutoUpdate::decompress(const std::string &zip)
{
    // Find root path for zip file
    size_t pos = zip.find_last_of("/\\");
    if (pos == std::string::npos)
    {
        CCLOG("AutoUpdate : no root path specified for zip file %s\n", zip.c_str());
        return false;
    }
    const std::string rootPath = zip.substr(0, pos+1);
    
    // Open the zip file
    unzFile zipfile = unzOpen(_fileUtils->getSuitableFOpen(zip).c_str());
    if (! zipfile)
    {
        CCLOG("AutoUpdate : can not open downloaded zip file %s\n", zip.c_str());
        return false;
    }
    
    // Get info about the zip file
    unz_global_info global_info;
    if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
    {
        CCLOG("AutoUpdate : can not read file global info of %s\n", zip.c_str());
        unzClose(zipfile);
        return false;
    }
    
    // Buffer to hold data read from the zip file
    char readBuffer[BUFFER_SIZE];
    // Loop to extract all files.
    uLong i;
    for (i = 0; i < global_info.number_entry; ++i)
    {
        // Get info about current file.
        unz_file_info fileInfo;
        char fileName[MAX_FILENAME];
        if (unzGetCurrentFileInfo(zipfile,
                                  &fileInfo,
                                  fileName,
                                  MAX_FILENAME,
                                  NULL,
                                  0,
                                  NULL,
                                  0) != UNZ_OK)
        {
            CCLOG("AutoUpdate : can not read compressed file info\n");
            unzClose(zipfile);
            return false;
        }
        const std::string fullPath = rootPath + fileName;
        
        // Check if this entry is a directory or a file.
        const size_t filenameLength = strlen(fileName);
        if (fileName[filenameLength-1] == '/')
        {
            //There are not directory entry in some case.
            //So we need to create directory when decompressing file entry
            if ( !_fileUtils->createDirectory(basename(fullPath)) )
            {
                // Failed to create directory
                CCLOG("AutoUpdate : can not create directory %s\n", fullPath.c_str());
                unzClose(zipfile);
                return false;
            }
        }
        else
        {
            // Entry is a file, so extract it.
            // Open current file.
            if (unzOpenCurrentFile(zipfile) != UNZ_OK)
            {
                CCLOG("AutoUpdate : can not extract file %s\n", fileName);
                unzClose(zipfile);
                return false;
            }
            
            // Create a file to store current file.
            FILE *out = fopen(_fileUtils->getSuitableFOpen(fullPath).c_str(), "wb");
            if (!out)
            {
                CCLOG("AutoUpdate : can not create decompress destination file %s\n", fullPath.c_str());
                unzCloseCurrentFile(zipfile);
                unzClose(zipfile);
                return false;
            }
            
            // Write current file content to destinate file.
            int error = UNZ_OK;
            do
            {
                error = unzReadCurrentFile(zipfile, readBuffer, BUFFER_SIZE);
                if (error < 0)
                {
                    CCLOG("AutoUpdate : can not read zip file %s, error code is %d\n", fileName, error);
                    fclose(out);
                    unzCloseCurrentFile(zipfile);
                    unzClose(zipfile);
                    return false;
                }
                
                if (error > 0)
                {
                    fwrite(readBuffer, error, 1, out);
                }
            } while(error > 0);
            
            fclose(out);
        }
        
        unzCloseCurrentFile(zipfile);
        
        // Goto next entry listed in the zip file.
        if ((i+1) < global_info.number_entry)
        {
            if (unzGoToNextFile(zipfile) != UNZ_OK)
            {
                CCLOG("AutoUpdate : can not read next file for decompressing\n");
                unzClose(zipfile);
                return false;
            }
        }
    }
    
    unzClose(zipfile);
    return true;
}

void AutoUpdate::parseVersion(const std::string &storagePath)
{
    _remoteVersionManifest->parseVersion(storagePath);
    _fileUtils->removeFile(storagePath);
    
    if (!_remoteVersionManifest->isLoaded())
    {
        CCLOG("AutoUpdate : Fail to parse version file, step skipped\n");
        updateFail(VERSION_ID);
        return;
    }
    else if (_remoteVersionManifest->getVersion() <= _localVersionManifest->getVersion())
    {
        updateSucceed(VERSION_ID);
        return;
    }
    
    _isDownloadVersion = true;
    std::string tempProjectPath = _updateStoragePath + TEMP_PROJECT_FILENAME;
    if (_fileUtils->isFileExist(tempProjectPath))
    {
        _remoteProjectManifest->parse(tempProjectPath);
        if (!_remoteProjectManifest->isLoaded())
        {
            _fileUtils->removeFile(tempProjectPath);
        }
        else if (_remoteVersionManifest->getVersion() == _remoteProjectManifest->getVersion())
        {
            //唤醒上次没下载完的资源
            initResumeRes();
            if (!_isNeedUpdateSrc && !_isNeedUpdateRes)
            {
                _fileUtils->removeFile(tempProjectPath);
            }
            else if (!_isNeedUpdateSrc)
            {
                _isDownloadProject = true;
                updateSucceed(VERSION_ID);
                return;
            }
            else
            {
                _isDownloadProject = true;
                _downloadUnits = _downloadSrcUnits;
                _totalWaitToDownload = (int)_downloadUnits.size();
                _percent = 0;
                _totalSize = _luaTotalSize;
                _downloadedSize.clear();
                batchDownload(false);
                return;
            }
        }
        else
        {
            _fileUtils->removeFile(tempProjectPath);
        }
    }
    
    downloadProject();
}

void AutoUpdate::initResumeRes()
{
    _failedUnits.clear();
    _downloadUnits.clear();
    _downloadSrcUnits.clear();
    _downloadResUnits.clear();
    const std::unordered_map<std::string, ManifestEx::Asset> &asset_map = _remoteProjectManifest->getAssets();
    for (auto it = asset_map.begin(); it != asset_map.end(); ++it)
    {
        ManifestEx::Asset asset = it->second;
        
        if (asset.downloadState == ManifestEx::DownloadState::DOWNLOADING)
        {
            DownloadUnit unit;
            unit.customId = it->first;
            std::string extName = _fileUtils->getFileExtension(asset.path);
            if (strcmp(extName.c_str(), ".luac") == 0)
            {
                unit.srcUrl = _srcUrl + "src/app/" + asset.path;
                unit.updateUrl = _updateUrl + "src/app/" + asset.path;
                unit.storagePath = _updateStoragePath + "src/app/" + asset.path;
                _downloadSrcUnits.emplace(unit.customId, unit);
                _luaTotalSize = _luaTotalSize + asset.size;
            }
            else
            {
                unit.srcUrl = _srcUrl + "res/" + asset.path;
                unit.updateUrl = _updateUrl + "res/" + asset.path;
                unit.storagePath = _updateStoragePath + "res/" + asset.path;
                if (strcmp(extName.c_str(), ".pb") == 0 || strcmp(extName.c_str(), ".csb") == 0)
                {
                    _downloadSrcUnits.emplace(unit.customId, unit);
                    _luaTotalSize = _luaTotalSize + asset.size;
                }
                else
                {
                    _downloadResUnits.emplace(unit.customId, unit);
                    _resTotalSize = _resTotalSize + asset.size;
                }
            }
            
            CCLOG("need download file::%s", asset.path.c_str());
        }
    }
    
    if (_downloadSrcUnits.size() > 0)
    {
        _isNeedUpdateSrc = true;
    }
    
    if (_downloadResUnits.size() > 0)
    {
        _isNeedUpdateRes = true;
    }
}

void AutoUpdate::batchDownload(bool isSrcUrl)
{
    for(auto iter : _downloadUnits)
    {
        DownloadUnit& unit = iter.second;
        std::string tempPath = unit.storagePath + ".tmp";
        if (_fileUtils->isFileExist(tempPath))
        {
            _fileUtils->removeFile(tempPath);
        }
        
        if (isSrcUrl)
        {
            _downloader->createDownloadFileTask(unit.srcUrl, unit.storagePath, unit.customId);
        }
        else
        {
            _downloader->createDownloadFileTask(unit.updateUrl, unit.storagePath, unit.customId);
        }
    }
    
    CCLOG("Start to update %d files from remote package.", _totalWaitToDownload);
}

void AutoUpdate::downloadProject()
{
    std::string projectUrl = _updateUrl + PROJECT_FILENAME;
    if (_projectErrorTimes > 1)
    {
        projectUrl = _srcUrl + PROJECT_FILENAME;
    }
    
    std::string tempProjectPath = _updateStoragePath + TEMP_PROJECT_FILENAME;
    std::string tempPath = tempProjectPath + ".tmp";
    if (_fileUtils->isFileExist(tempPath))
    {
        _fileUtils->removeFile(tempPath);
    }
    
    _downloader->createDownloadFileTask(projectUrl, tempProjectPath, PROJECT_ID);
}

void AutoUpdate::parseProject(const std::string &storagePath)
{
    _remoteProjectManifest->parse(storagePath);
    
    if (!_remoteProjectManifest->isLoaded())
    {
        CCLOG("AutoUpdate : Error parsing manifest file\n");
        _fileUtils->removeFile(storagePath);
        updateFail(PROJECT_ID);
        return;
    }
    
    if (_remoteVersionManifest->getVersion() != _remoteProjectManifest->getVersion())
    {
        _projectErrorTimes++;
        updateFail(PROJECT_ID);
        return;
    }
    
    _isDownloadProject = true;
    // Load local project file
    std::string cacheProjectPath = _updateStoragePath + PROJECT_FILENAME;
    _localProjectManifest->parse(cacheProjectPath);
    if (!_localProjectManifest->isLoaded())
    {
        if (_fileUtils->isFileExist(cacheProjectPath))
        {
            _fileUtils->removeFile(cacheProjectPath);
        }
        _localProjectManifest->parse(PROJECT_FILENAME);
    }
    
    if (!_localProjectManifest->isLoaded())
    {
        CCLOG("AutoUpdate : No local project file found error.\n");
        updateFail(PROJECT_ID);
        return;
    }
    else
    {
        downloadDiffRes();
    }
}

void AutoUpdate::downloadDiffRes()
{
    _failedUnits.clear();
    _downloadUnits.clear();
    _downloadSrcUnits.clear();
    _downloadResUnits.clear();
    
    std::unordered_map<std::string, ManifestEx::AssetDiff> diff_map = _localProjectManifest->genDiff(_remoteProjectManifest);
    if (diff_map.size() == 0)
    {
        updateResFinished();
        return;
    }
    
    for (auto it = diff_map.begin(); it != diff_map.end(); ++it)
    {
        ManifestEx::AssetDiff diff = it->second;
        std::string extName = _fileUtils->getFileExtension(diff.asset.path);
        if (strcmp(extName.c_str(), ".luac") == 0)
        {
            std::string path = "src/app/" + diff.asset.path;
            if (diff.type == ManifestEx::DiffType::DELETED)
            {
                _fileUtils->removeFile(_updateStoragePath + path);
                CCLOG("need delete file::%s", diff.asset.path.c_str());
            }
            else
            {
                // Create path
                _fileUtils->createDirectory(basename(_updateStoragePath + path));
                DownloadUnit unit;
                unit.customId = it->first;
                unit.srcUrl = _srcUrl + path;
                unit.updateUrl = _updateUrl + path;
                unit.storagePath = _updateStoragePath + path;
                _downloadSrcUnits.emplace(unit.customId, unit);
                _remoteProjectManifest->setAssetDownloadState(unit.customId, ManifestEx::DownloadState::DOWNLOADING);
                _luaTotalSize = _luaTotalSize + diff.asset.size;
                CCLOG("need download file::%s", diff.asset.path.c_str());
            }
        }
        else
        {
            std::string path = "res/" + diff.asset.path;
            if (diff.type == ManifestEx::DiffType::DELETED)
            {
                _fileUtils->removeFile(_updateStoragePath + path);
                CCLOG("need delete file::%s", diff.asset.path.c_str());
            }
            else
            {
                // Create path
                _fileUtils->createDirectory(basename(_updateStoragePath + path));
                DownloadUnit unit;
                unit.customId = it->first;
                unit.srcUrl = _srcUrl + path;
                unit.updateUrl = _updateUrl + path;
                unit.storagePath = _updateStoragePath + path;
                _downloadResUnits.emplace(unit.customId, unit);
                _remoteProjectManifest->setAssetDownloadState(unit.customId, ManifestEx::DownloadState::DOWNLOADING);
                if (strcmp(extName.c_str(), ".pb") == 0 || strcmp(extName.c_str(), ".csb") == 0)
                {
                    _downloadSrcUnits.emplace(unit.customId, unit);
                    _luaTotalSize = _luaTotalSize + diff.asset.size;
                }
                else
                {
                    _downloadResUnits.emplace(unit.customId, unit);
                    _resTotalSize = _resTotalSize + diff.asset.size;
                }
                CCLOG("need download file::%s", diff.asset.path.c_str());
            }
        }
    }
    
    if (_downloadSrcUnits.size() > 0)
    {
        _isNeedUpdateSrc = true;
    }
    
    if (_downloadResUnits.size() > 0)
    {
        _isNeedUpdateRes = true;
    }
    
    if (!_isNeedUpdateSrc)
    {
        updateSucceed(VERSION_ID);
        return;
    }
    
    _downloadUnits = _downloadSrcUnits;
    _totalWaitToDownload = (int)_downloadUnits.size();
    _percent = 0;
    _totalSize = _luaTotalSize;
    _downloadedSize.clear();
    batchDownload(false);
}

void AutoUpdate::updateResFinished()
{
    std::string tempProjectPath = _updateStoragePath + TEMP_PROJECT_FILENAME;
    if (_failedUnits.size() > 0)
    {
        // Save current download manifest information for resuming
        _remoteProjectManifest->saveToFile(tempProjectPath);
        
        std::string failedFile = "otherFile";
        for (auto it = _failedUnits.begin(); it != _failedUnits.end(); ++it)
        {
            failedFile = it->first;
            break;
        }
        updateFail(failedFile);
        return;
    }
    
    if (_isNeedUpdateRes)
    {
        if (_isNeedUpdateSrc && _downloadSrcUnits.size() > 0)
        {
            _downloadSrcUnits.clear();
            _failedUnits.clear();
            _remoteProjectManifest->saveToFile(tempProjectPath);
            updateSucceed(VERSION_ID);
            return;
        }
    }
    
    _downloadSrcUnits.clear();
    _downloadResUnits.clear();
    _isNeedUpdateRes = false;
    std::string cacheVersionPath = _updateStoragePath + VERSION_FILENAME;
    _localVersionManifest->setVersion(_remoteVersionManifest->getVersion());
    _localVersionManifest->saveToFile(cacheVersionPath);
    _fileUtils->renameFile(_updateStoragePath, TEMP_PROJECT_FILENAME, PROJECT_FILENAME);
    updateSucceed(VERSION_ID);
}

bool AutoUpdate::isExtendRes(const std::string &customId)
{
    auto it = _extendResDownloadList.find(customId);
    if (it != _extendResDownloadList.end())
    {
        return true;
    }
    return false;
}

void AutoUpdate::setExtendResState(const std::string &customId, ExtendResState state)
{
    for (auto it = _extendResDownloadList.begin(); it != _extendResDownloadList.end(); ++it)
    {
        if (it->first == customId)
        {
            it->second = state;
        }
    }
}

void AutoUpdate::updateExtendResFinish()
{
    for (auto it = _extendResDownloadList.begin(); it != _extendResDownloadList.end(); ++it)
    {
        CCLOG("extendRes::%s, %d", it->first.c_str(), it->second);
        if (it->second == ExtendResState::FAIL)
        {
            //fail
            it->second = ExtendResState::UNDOWNLOAD;
            updateFail(it->first);
        }
        else if (it->second == ExtendResState::SUCCESS)
        {
            //success
            updateSucceed(it->first);
        }
    }
}

uint32_t AutoUpdate::getLocalVersion()
{
    return _localVersionManifest->getVersion();
}

bool AutoUpdate::isEnableUpdate()
{
    return _enableUpdate;
}

void AutoUpdate::startUpdateSrc()
{
    if (!_isDownloadVersion)
    {
        std::string versionUrl = _srcUrl + VERSION_FILENAME;
        std::string tempVersionPath = _updateStoragePath + TEMP_VERSION_FILENAME;
        std::string tempPath = tempVersionPath + ".tmp";
        if (_fileUtils->isFileExist(tempPath))
        {
            _fileUtils->removeFile(tempPath);
        }
        
        _downloader->createDownloadFileTask(versionUrl, tempVersionPath, VERSION_ID);
        return;
    }
    
    if (!_isDownloadProject)
    {
        downloadProject();
        return;
    }
    
    _downloadUnits.clear();
    if (_failedUnits.size() > 0)
    {
        _downloadUnits = _failedUnits;
        _totalWaitToDownload = (int)_downloadUnits.size();
        _srcErrorTimes++;
        _isExistFailRes = true;
        if (_srcErrorTimes > 1)
        {
            batchDownload(true);
        }
        else
        {
            batchDownload(false);
        }
    }
    else if(_downloadSrcUnits.size() > 0)
    {
        _downloadUnits = _downloadSrcUnits;
        _totalWaitToDownload = (int)_downloadUnits.size();
        _percent = 0;
        _totalSize = _luaTotalSize;
        _downloadedSize.clear();
        batchDownload(false);
    }
    else
    {
        updateSucceed(VERSION_ID);
    }
}

bool AutoUpdate::isNeedUpdateSrc()
{
    return _isNeedUpdateSrc;
}

bool AutoUpdate::isNeedUpdateRes()
{
    return _isNeedUpdateRes;
}

void AutoUpdate::startUpdateRes()
{
    _downloadUnits.clear();
    if (_failedUnits.size() > 0)
    {
        _downloadUnits = _failedUnits;
        _totalWaitToDownload = (int)_downloadUnits.size();
        _resErrorTimes++;
        _isExistFailRes = true;
        if (_resErrorTimes > 1)
        {
            batchDownload(true);
        }
        else
        {
            batchDownload(false);
        }
    }
    else if(_downloadResUnits.size() > 0)
    {
        _downloadUnits = _downloadResUnits;
        _totalWaitToDownload = (int)_downloadUnits.size();
        _percent = 0;
        _totalSize = _resTotalSize;
        _downloadedSize.clear();
        _isExistFailRes = false;
        batchDownload(false);
    }
    else
    {
        updateResFinished();
    }
}

bool AutoUpdate::downloadExtendRes(const std::string& fileName, int idx)
{
	std::string cacheExResPath = _downloadStoragePath + fileName;
	cacheExResPath.append(".zip");

	std::string exResUrl = _downloadUrl + fileName;
	exResUrl.append(".zip");

	char customId[12] = { 0 };
	sprintf(customId, "extendRes%02d", idx);
    
    bool found = false;
    for (auto it = _extendResDownloadList.begin(); it != _extendResDownloadList.end(); ++it)
    {
        if (it->first == customId)
        {
            found = true;
            if (it->second != ExtendResState::UNDOWNLOAD)
            {
                return false;
            }
            else
            {
                it->second = ExtendResState::DOWNLOADING;
            }
            break;
        }
    }
    
    if (!found)
    {
        _extendResDownloadList.emplace(customId, ExtendResState::DOWNLOADING);
    }
    
    if (_fileUtils->isFileExist(cacheExResPath))
    {
        asyncDecompress(cacheExResPath, customId);
    }
    else
    {
        _downloader->createDownloadFileTask(exResUrl, cacheExResPath, customId);
    }
	
    return true;
}

void AutoUpdate::updateSucceed(const std::string &customId)
{
    lua_State* L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    int top = lua_gettop(L);
    lua_getglobal(L,"updateSucceedLua");
    lua_pushstring(L, customId.c_str());
    lua_pcall(L,1,0,0);
    lua_settop(L,top);
}

void AutoUpdate::updateProgress(const std::string &customId, int per)
{
    lua_State* L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    int top = lua_gettop(L);
    lua_getglobal(L,"updateProgressLua");
    lua_pushstring(L, customId.c_str());
    lua_pushinteger(L, per);
    lua_pcall(L,2,0,0);
    lua_settop(L,top);
}

void AutoUpdate::updateFail(const std::string &customId)
{
	lua_State* L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
	int top = lua_gettop(L);
	lua_getglobal(L, "updateFailLua");
	lua_pushstring(L, customId.c_str());
	lua_pcall(L, 1, 0, 0);
	lua_settop(L, top);
}
