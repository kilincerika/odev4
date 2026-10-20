#ifndef PIPELINE_LOADER_H
#ifndef PIPELINE_LOADER_H
#define PIPELINE_LOADER_H

#include "Pipeline.h"
#include "StageRegistry.h"
#include "Stages.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

class PipelineLoader {
public:
    static Pipeline* loadFromFile(const std::string& configFilePath) {
        std::ifstream file(configFilePath.c_str());
        if (!file.is_open()) {
            throw std::runtime_error("[Yapilandirma Hatasi] Yapilandirma dosyasi bulunamadi veya acilamadi: " + configFilePath);
        }

        Pipeline* pipeline = new Pipeline();
        std::string line;
        std::string currentStageType = "";
        std::map<std::string, std::string> currentParams;

        // Basit metin/YAML tabanlý konfigürasyon okuyucu simülasyonu
        while (std::getline(file, line)) {
            // Yorum veya boþ satýrlarý atla
            if (line.empty() || line[0] == '#') continue;

            if (line.find("type:") != std::string::npos) {
                // Eðer daha önceden bir aþama biriktirildiyse kaydet
                if (!currentStageType.empty()) {
                    pipeline->addStage(StageRegistry::getInstance().createStage(currentStageType, currentParams));
                    currentParams.clear();
                }
                size_t pos = line.find("type:");
                currentStageType = line.substr(pos + 5);
                // Boþluklarý temizle
                currentStageType.erase(0, currentStageType.find_first_not_of(" \t"));
                currentStageType.erase(currentStageType.find_last_not_of(" \t\r\n") + 1);
            }
            else if (line.find("path:") != std::string::npos) {
                size_t pos = line.find("path:");
                std::string val = line.substr(pos + 5);
                val.erase(0, val.find_first_not_of(" \t"));
                val.erase(val.find_last_not_of(" \t\r\n") + 1);
                currentParams["path"] = val;
            }
            else if (line.find("format:") != std::string::npos) {
                size_t pos = line.find("format:");
                std::string val = line.substr(pos + 7);
                val.erase(0, val.find_first_not_of(" \t"));
                val.erase(val.find_last_not_of(" \t\r\n") + 1);
                currentParams["format"] = val;
            }
            else if (line.find("field:") != std::string::npos) {
                size_t pos = line.find("field:");
                std::string val = line.substr(pos + 6);
                val.erase(0, val.find_first_not_of(" \t"));
                val.erase(val.find_last_not_of(" \t\r\n") + 1);
                currentParams["field"] = val;
            }
            else if (line.find("op:") != std::string::npos) {
                size_t pos = line.find("op:");
                std::string val = line.substr(pos + 3);
                val.erase(0, val.find_first_not_of(" \t"));
                val.erase(val.find_last_not_of(" \t\r\n") + 1);
                currentParams["op"] = val;
            }
            else if (line.find("value:") != std::string::npos) {
                size_t pos = line.find("value:");
                std::string val = line.substr(pos + 6);
                val.erase(0, val.find_first_not_of(" \t"));
                val.erase(val.find_last_not_of(" \t\r\n") + 1);
                currentParams["value"] = val;
            }
        }

        // Son aþamayý ekle
        if (!currentStageType.empty()) {
            pipeline->addStage(StageRegistry::getInstance().createStage(currentStageType, currentParams));
        }

        file.close();

        // Boþ iþlem hattý denetimi (Fail Fast)
        if (pipeline->getStageCount() == 0) {
            delete pipeline;
            throw std::runtime_error("[Yapilandirma Hatasi] Islem hatti bos olamaz!");
        }

        return pipeline;
    }
};

#endif
#endif
