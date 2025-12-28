#include "TimingView.h"
#include "Controller.h"

void TimingView::show()
{
    Lcd::get()->screen()->clearDisplay();
    Lcd::get()->screen()->setCursor(35, 5);
    Lcd::get()->screen()->setTextSize(1);
    if (currentParam == 0) {
        Lcd::get()->screen()->print("Rozpalanie");
    } else if (currentParam == 1) {
        Lcd::get()->screen()->print("Stabilizacja");
    }

    Lcd::get()->screen()->setCursor(50, 20);
    Lcd::get()->screen()->setTextSize(2);
    uint32_t m = (selectedPos / 1000) / 60;
    uint32_t s = (selectedPos / 1000) % 60;
    char buf[10];
    sprintf(buf, "%d:%02d", m, s);
    Lcd::get()->screen()->print(buf);
    Lcd::get()->invalidateView();
}

void TimingView::reset(int position)
{
    currentParam = 0;
    selectedPos = Controller::get()->getCurrentState()->firingUpTimeToSet;
    Knob::get()->setMinMax(0, 10 * 60 * 1000);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(selectedPos);
    Knob::get()->setStep(1000);
}

void TimingView::onPositionChange(int position)
{
    selectedPos = position;
    show();
}

void TimingView::onButtonReleased()
{
    if (currentParam == 0) {
        currentParam++;
        Controller::get()->getCurrentState()->firingUpTimeToSet = selectedPos;
        Controller::get()->getCurrentState()->save();
        Controller::get()->getSerialCommunication()->setFiringUpTime(selectedPos);
        selectedPos = Controller::get()->getCurrentState()->stabilizationTimeToSet;
        Knob::get()->setPosition(selectedPos);
    } else if (currentParam == 1) {
        Controller::get()->getCurrentState()->stabilizationTimeToSet = selectedPos;
        Controller::get()->getCurrentState()->save();
        Controller::get()->getSerialCommunication()->setStabilizationTime(selectedPos);

        Knob::get()->setStep(1);
        Controller::get()->changeView("mainMenu", 8);
    }
}
