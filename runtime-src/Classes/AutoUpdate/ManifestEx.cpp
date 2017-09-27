//
//  ManifestEx.cpp
//  tdht
//
//  Created by hucanhua on 16/8/11.
//
//

#include "ManifestEx.h"
#include "json/filestream.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"

#include <fstream>

#define KEY_UPDATE_URL          "updateUrl"
#define KEY_SRC_URL             "srcUrl"
#define KEY_VERSION             "version"
#define KEY_ENABLE_UPDATE       "enableUpdate"

#define KEY_ASSETS              "assets"
#define KEY_PATH                "path"
#define KEY_MD5                 "md5"
#define KEY_SIZE                "size"
#define KEY_DOWNLOAD_STATE      "downloadState"

using namespace cocos2d;

ManifestEx::ManifestEx()
: _loaded(false)
, _enableUpdate(true)
, _version(0)
, _updateUrl("")
, _srcUrl("")
{
    // Init variables
    _fileUtils = FileUtils::getInstance();
}

bool ManifestEx::isLoaded() const
{
    return _loaded;
}

void ManifestEx::setVersion(uint32_t version)
{
    _version = version;
    if (_json.HasMember(KEY_VERSION))
    {
        _json[KEY_VERSION].SetInt(version);
    }
}

uint32_t ManifestEx::getVersion() const
{
    return _version;
}

const std::string& ManifestEx::getUpdateUrl() const
{
    return _updateUrl;
}

const std::string& ManifestEx::getSrcUrl() const
{
    return _srcUrl;
}

bool ManifestEx::isEnableUpdate() const
{
    return _enableUpdate;
}

const std::unordered_map<std::string, ManifestEx::Asset>& ManifestEx::getAssets() const
{
    return _assets;
}

void ManifestEx::loadJson(const std::string& path)
{
    clear();
    std::string content;
    if (_fileUtils->isFileExist(path))
    {
        // Load file content
        content = _fileUtils->getStringFromFile(path);
        
        if (content.size() == 0)
        {
            CCLOG("Fail to retrieve local file content: %s\n", path.c_str());
        }
        else
        {
            // Parse file with rapid json
            _json.Parse<0>(content.c_str());
            // Print error
            if (_json.HasParseError()) {
                size_t offset = _json.GetErrorOffset();
                if (offset > 0)
                    offset--;
                std::string errorSnippet = content.substr(offset, 10);
                CCLOG("File parse error %d at <%s>\n", _json.GetParseError(), errorSnippet.c_str());
            }
        }
    }
}

void ManifestEx::parseVersion(const std::string& path)
{
    loadJson(path);
    
    if (_json.IsObject())
    {
        loadVersion(_json);
        _loaded = true;
    }
}

void ManifestEx::parse(const std::string& path)
{
    loadJson(path);
    
    if (_json.IsObject())
    {
        loadManifest(_json);
        _loaded = true;
    }
}

ManifestEx::Asset ManifestEx::parseAsset(const std::string &path, const rapidjson::Value &json)
{
    Asset asset;
    asset.path = path;
    
    if ( json.HasMember(KEY_MD5) && json[KEY_MD5].IsString() )
    {
        asset.md5 = json[KEY_MD5].GetString();
    }
    else asset.md5 = "";
    
    if ( json.HasMember(KEY_PATH) && json[KEY_PATH].IsString() )
    {
        asset.path = json[KEY_PATH].GetString();
    }
    
    if ( json.HasMember(KEY_SIZE) && json[KEY_SIZE].IsInt() )
    {
        asset.size = (json[KEY_SIZE].GetInt());
    }
    else asset.size = 0;
    
    
    if ( json.HasMember(KEY_DOWNLOAD_STATE) && json[KEY_DOWNLOAD_STATE].IsInt() )
    {
        asset.downloadState = (DownloadState)(json[KEY_DOWNLOAD_STATE].GetInt());
    }
    else asset.downloadState = DownloadState::UNSTARTED;
    
    return asset;
}

void ManifestEx::loadVersion(const rapidjson::Document &json)
{
    if ( json.HasMember(KEY_UPDATE_URL) && json[KEY_UPDATE_URL].IsString() )
    {
        _updateUrl = json[KEY_UPDATE_URL].GetString();
    }
    
    if ( json.HasMember(KEY_SRC_URL) && json[KEY_SRC_URL].IsString() )
    {
        _srcUrl = json[KEY_SRC_URL].GetString();
    }
    
    if ( json.HasMember(KEY_VERSION) && json[KEY_VERSION].IsInt() )
    {
        _version = json[KEY_VERSION].GetInt();
    }
    
    if ( json.HasMember(KEY_ENABLE_UPDATE) && json[KEY_ENABLE_UPDATE].IsBool() )
    {
        _enableUpdate = json[KEY_ENABLE_UPDATE].GetBool();
    }
}

void ManifestEx::loadManifest(const rapidjson::Document &json)
{
    loadVersion(json);
    
    // Retrieve all assets
    if ( json.HasMember(KEY_ASSETS) )
    {
        const rapidjson::Value& assets = json[KEY_ASSETS];
        if (assets.IsObject())
        {
            for (rapidjson::Value::ConstMemberIterator itr = assets.MemberBegin(); itr != assets.MemberEnd(); ++itr)
            {
                std::string key = itr->name.GetString();
                Asset asset = parseAsset(key, itr->value);
                _assets.emplace(key, asset);
            }
        }
    }
}

std::unordered_map<std::string, ManifestEx::AssetDiff> ManifestEx::genDiff(const ManifestEx *b) const
{
    std::unordered_map<std::string, AssetDiff> diff_map;
    const std::unordered_map<std::string, Asset> &bAssets = b->getAssets();
    
    std::unordered_map<std::string, Asset>::const_iterator valueIt, it;
    for (it = _assets.begin(); it != _assets.end(); ++it)
    {
        const auto &key = it->first;
        const auto &valueA = it->second;
        
        // Deleted
        valueIt = bAssets.find(key);
        if (valueIt == bAssets.cend()) {
            AssetDiff diff;
            diff.asset = valueA;
            diff.type = DiffType::DELETED;
            diff_map.emplace(key, diff);
            continue;
        }
        
        // Modified
        const auto &valueB = valueIt->second;
        if (valueA.md5 != valueB.md5) {
            AssetDiff diff;
            diff.asset = valueB;
            diff.type = DiffType::MODIFIED;
            diff_map.emplace(key, diff);
        }
    }
    
    for (it = bAssets.begin(); it != bAssets.end(); ++it)
    {
        const auto &key = it->first;
        const auto &valueB = it->second;
        
        // Added
        valueIt = _assets.find(key);
        if (valueIt == _assets.cend()) {
            AssetDiff diff;
            diff.asset = valueB;
            diff.type = DiffType::ADDED;
            diff_map.emplace(key, diff);
        }
    }
    
    return diff_map;
}

void ManifestEx::setAssetDownloadState(const std::string &key, const ManifestEx::DownloadState &state)
{
    auto valueIt = _assets.find(key);
    if (valueIt != _assets.end())
    {
        valueIt->second.downloadState = state;
        
        // Update json object
        if(_json.IsObject())
        {
            if ( _json.HasMember(KEY_ASSETS) )
            {
                rapidjson::Value &assets = _json[KEY_ASSETS];
                if (assets.IsObject())
                {
                    for (rapidjson::Value::MemberIterator itr = assets.MemberBegin(); itr != assets.MemberEnd(); ++itr)
                    {
                        if (key.compare(itr->name.GetString()) == 0) {
                            rapidjson::Value &entry = itr->value;
                            if (entry.HasMember(KEY_DOWNLOAD_STATE) && entry[KEY_DOWNLOAD_STATE].IsInt())
                            {
                                entry[KEY_DOWNLOAD_STATE].SetInt((int) state);
                            }
                            else
                            {
                                entry.AddMember<int>(KEY_DOWNLOAD_STATE, (int)state, _json.GetAllocator());
                            }
                        }
                    }
                }
            }
        }
    }
}

void ManifestEx::saveToFile(const std::string &filepath)
{
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    _json.Accept(writer);
    
    std::ofstream output(filepath, std::ofstream::out);
    if(!output.bad())
        output << buffer.GetString() << std::endl;
}

void ManifestEx::clear()
{
    if (_loaded)
    {
        _assets.clear();
        _loaded = false;
    }
}
