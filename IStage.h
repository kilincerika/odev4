#ifndef ISTAGE_H
#define ISTAGE_H

#include <string>
#include <map>
#include <vector>

// Log veya veri satýrýný temsil eder (Örn: timestamp, clientip, status, path)
typedef std::map<std::string, std::string> Record;

class IStage {
public:
    virtual ~IStage() {}
    // Aþamanýn ana iþ mantýðý
    virtual void process(std::vector<Record>& dataSet) = 0;
};

#endif
