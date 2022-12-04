#include "Widget.h"

Widget::Widget(DeviceMediator* device): device(device) {}

void Widget::changed(const string& widgetName){
    device->WidgetChanged(this, widgetName);
}
