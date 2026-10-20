#ifndef STAGE_REGISTRY_H
#define STAGE_REGISTRY_H

#include "IStage.h"
#include <map>
#include <string>
#include <stdexcept>

// Fabrika fonksiyon göstericisi (Function Pointer)
typedef IStage* (*StageCreator)(const std::map<std::string, std::string>& params);

class StageRegistry {
    std::map<std::string, StageCreator> registryMap;

    StageRegistry() {}
public:
    static StageRegistry& getInstance() {
        static StageRegistry instance;
        return instance;
    }

    void registerStage(const std::string& typeName, StageCreator creator) {
        registryMap[typeName] = creator;
    }

    IStage* createStage(const std::string& typeName, const std::map<std::string, std::string>& params) {
        if (registryMap.find(typeName) == registryMap.end()) {
            throw std::runtime_error("[Yapilandirma Hatasi] Bilinmeyen aþama türü tespit edildi: '" + typeName + "' (Fail Fast)");
        }
        return registryMap[typeName](params);
    }
};

#endif
