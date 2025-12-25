#include "TimingView.h"
#include "Controller.h"

void TimingView::show() {
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
    Lcd::get()->screen()->print(selectedPos);

    Lcd::get()->invalidateView();
}

void TimingView::reset(int position) {
    currentParam = 0;
    Knob::get()->setMinMax(0, 10000);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(0);
    Knob::get()->setStep(100);
}

void TimingView::onPositionChange(int position) {
    show();
}

void TimingView::onButtonReleased() {
    if (currentParam == 0) {
        currentParam++;
    } else if (currentParam == 1) {
        Knob::get()->setStep(1);
        controller->changeView("mainMenu", 5);
    }
}
