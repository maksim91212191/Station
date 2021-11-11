#ifndef ANALYZER_H
#define ANALYZER_H
// #pragma once

#include <string>
#include <QString>
#include <station/server.h>
#include <station/resources.h>
#include <station/managerRemote.h>

namespace Station {

class Analyzer {
public:
    Analyzer();
    ~Analyzer();
    void Init(RemoteTypes _type);
    void Process(ReceiveData* _data);
    RawData* GetData() const;
    void Reset();
private:
    RemoteTypes type;
    RawData*       data;
};

} /* Station */

#endif
