#ifndef MANAGER_REMOTE_H
#define MANAGER_REMOTE_H

// #pragma once

#include <map>
#include <string>
#include <cstdint>
#include <QWidget>
#include <QString>
#include <station/server.h>
#include <station/resources.h>
#include <station/analyzer.h>

namespace Station {

class Analyzer;

class ManagerRemote : public QObject {
    Q_OBJECT
public:
    ManagerRemote(const std::string& host, uint16_t port);
    void AddRemote(uint8_t id, RemoteTypes type);
    virtual ~ManagerRemote();
public slots:
    void Loop();
signals:
    void NewData(QString str);
private:
    void SendToUI(RawData* data);

    Server*                        server;
    Analyzer*                      analyzer;
    std::map<uint8_t, RemoteTypes> remotes;
};

} /* namespace Station*/

#endif
