#include <station/analyzer.h>

namespace Station {

Analyzer::Analyzer() :
    type(RemoteTypes::A) {}

void Analyzer::Init(RemoteTypes _type) {
    type = _type;
}

void Analyzer::Reset() {
    type = RemoteTypes::A;
    delete data;
}

RawData* Analyzer::GetData() const {
    return data;
}

void Analyzer::Process(ReceiveData* _data) {
    data->type = type;
    switch (type) {
    case RemoteTypes::A:
        data = new DataA;
        break;
    case RemoteTypes::B:
        data = new DataB;
        break;
    default:
        break;
    }
    data->Fill(_data->data, _data->size);

}

}/* namespace Station */
