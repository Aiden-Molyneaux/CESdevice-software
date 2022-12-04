#include "Session.h"

Session::Session(DeviceMediator* device, const string& name): sessionName(name), Widget(device) {}

Session::~Session(){ delete this; }
