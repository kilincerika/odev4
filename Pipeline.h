#ifndef PIPELINE_H
#ifndef PIPELINE_H
#define PIPELINE_H

#include "IStage.h"
#include <vector>

class Pipeline {
    std::vector<IStage*> stages;
public:
    ~Pipeline() {
        for (size_t i = 0; i < stages.size(); ++i) {
            delete stages[i];
        }
    }

    void addStage(IStage* stage) {
        stages.push_back(stage);
    }

    size_t getStageCount() const {
        return stages.size();
    }

    void execute() {
        std::vector<Record> dataSet;
        for (size_t i = 0; i < stages.size(); ++i) {
            stages[i]->process(dataSet);
        }
    }
};

#endif
#endif
