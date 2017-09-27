//
//  AutoUpdate.h
//  tdht
//
//  Created by hucanhua on 16/8/8.
//
//

#ifndef AutoUpdate_h
#define AutoUpdate_h

#include "cocos2d.h"
#include "network/CCDownloader.h"
#include "ManifestEx.h"

struct DownloadUnit
{
    std::string updateUrl;
    std::string srcUrl;
    std::string storagePath;
    std::string customId;
};

typedef std::unordered_map<std::string, DownloadUnit> DownloadUnits;

class AutoUpdate : cocos2d::Ref
{
    
public:
    AutoUpdate();
    ~AutoUpdate();
    static AutoUpdate* getInstance();
    void initUpdate();
    void createDownloader();
    void destroyDownloader();
public:
    enum class ExtendResState
    {
        UNDOWNLOAD,
        DOWNLOADING,
        FAIL,
        SUCCESS
    };
    
    const static std::string VERSION_ID;
    const static std::string PROJECT_ID;
    
    //获取版本号
    uint32_t getLocalVersion();
    
    bool isEnableUpdate();
    void startUpdateSrc();
    bool isNeedUpdateSrc();
    bool isNeedUpdateRes();
    void startUpdateRes();
    //下载分包资源
	bool downloadExtendRes(const std::string& fileName, int idx);
protected:
    void onError(const std::string &srcUrl, const std::string &storagePath, const std::string &customId);
    void onProgress(double total, double downloaded, const std::string &url, const std::string &customId);
    void onSuccess(const std::string &srcUrl, const std::string &storagePath, const std::string &customId);
    
    void updateSucceed(const std::string &customId);
    void updateProgress(const std::string &customId, int per);
    void updateFail(const std::string &customId);
protected:
    void setStoragePath();
    void initManifests();
    void parseVersion(const std::string &storagePath);
    void initResumeRes();
    void batchDownload(bool isSrcUrl);
    void downloadProject();
    void parseProject(const std::string &storagePath);
    void downloadDiffRes();
    void updateResFinished();
    bool isExtendRes(const std::string &customId);
    void setExtendResState(const std::string &customId, ExtendResState state);
    void updateExtendResFinish();
    void asyncDecompress(const std::string &zip, const std::string &customId);
    std::string basename(const std::string& path) const;
    bool decompress(const std::string &zip);
private:
    static AutoUpdate* s_AutoUpdate;
    cocos2d::FileUtils *_fileUtils;
    cocos2d::network::Downloader* _downloader;
    std::unordered_map<std::string, ExtendResState> _extendResDownloadList;
    DownloadUnits _downloadSrcUnits;
    DownloadUnits _downloadResUnits;
    DownloadUnits _downloadUnits;
    DownloadUnits _failedUnits;
    std::unordered_map<std::string, double> _downloadedSize;
    
    std::string _updateUrl;
    std::string _srcUrl;
    std::string _downloadUrl;
    bool _enableUpdate;
    std::string _updateStoragePath;
    std::string _downloadStoragePath;
    
    ManifestEx *_localVersionManifest;
    ManifestEx *_remoteVersionManifest;
    ManifestEx *_localProjectManifest;
    ManifestEx *_remoteProjectManifest;
    
    bool _isDownloadVersion;
    bool _isDownloadProject;
    bool _isNeedUpdateSrc;
    bool _isNeedUpdateRes;
    bool _isExistFailRes;
    
    int _totalWaitToDownload;
    double _totalSize;
    double _luaTotalSize;
    double _resTotalSize;
    int _percent;
    
    int _projectErrorTimes;
    int _srcErrorTimes;
    int _resErrorTimes;
};

#endif /* AutoUpdate_h */
