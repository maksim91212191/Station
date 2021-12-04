#include <station/managerRemote.h>

namespace Station {

ManagerRemote::ManagerRemote(const std::string& host, uint16_t port) :
    server(new Server(host, port)),
    analyzer(new Analyzer) {}

void ManagerRemote::AddRemote(uint8_t id, RemoteTypes type) {
    remotes[id] = type;
}

ManagerRemote::~ManagerRemote() {
    delete server;
}

void ManagerRemote::SendToUI(uint8_t id, RawData* data) {
    QString msg = data->GetString();
    NewData(id, msg);
}

int ManagerRemote::GetRemoteNum() const {
    return remotes.size();
}

void ManagerRemote::Loop() {
    ReceiveData* recData = new ReceiveData;
    while (1) {
        server->Receive(recData);
        RemoteTypes type = remotes[recData->id];
        analyzer->Init(type);
        analyzer->Process(recData);
        RawData* data = analyzer->GetData();
        SendToUI(recData->id, data);
        analyzer->Reset();
    }
}

} /* namespace Station */
