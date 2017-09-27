//
//  ManifestEx.h
//  tdht
//
//  Created by hucanhua on 16/8/11.
//
//

#ifndef ManifestEx_h
#define ManifestEx_h

#include "cocos2d.h"
#include "json/document.h"

class ManifestEx : cocos2d::Ref
{
    
public:
    
    friend class AutoUpdate;
    
    //! The type of difference
    enum class DiffType {
        ADDED,
        DELETED,
        MODIFIED
    };
    
    enum class DownloadState {
        UNSTARTED,
        DOWNLOADING,
        SUCCESSED
    };
    
    //! Asset object
    struct Asset {
        std::string md5;
        std::string path;
        int size;
        DownloadState downloadState;
    };
    
    //! Object indicate the difference between two Assets
    struct AssetDiff {
        Asset asset;
        DiffType type;
    };
    
    bool isLoaded() const;
    void setVersion(uint32_t version);
    uint32_t getVersion() const;
    const std::string& getUpdateUrl() const;
    const std::string& getSrcUrl() const;
    bool isEnableUpdate() const;
    const std::unordered_map<std::string, Asset>& getAssets() const;
    
protected:
    ManifestEx();
    void loadJson(const std::string& path);
    
    void parseVersion(const std::string& path);
    
    void parse(const std::string& path);
    
    Asset parseAsset(const std::string &path, const rapidjson::Value &json);
    
    void loadVersion(const rapidjson::Document &json);
    
    void loadManifest(const rapidjson::Document &json);
    
    std::unordered_map<std::string, AssetDiff> genDiff(const ManifestEx *b) const;
    
    void setAssetDownloadState(const std::string &key, const DownloadState &state);
    
    void saveToFile(const std::string &filepath);
    
    void clear();
private:
    bool _loaded;
    bool _enableUpdate;
    cocos2d::FileUtils *_fileUtils;
    uint32_t _version;
    std::string _updateUrl;
    std::string _srcUrl;
    std::unordered_map<std::string, Asset> _assets;
    rapidjson::Document _json;
};

#endif /* ManifestEx_h */
