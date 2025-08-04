#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
    virtual void handleClickEvent(const ClickEvent& event);

    virtual void selectActionHandler();
    virtual void nextActionHandler();
    virtual void updateDemoName();

protected:
    int inactiveCounter;
    int inactiveThreshold;

    void resetInactiveCounter();

    static const uint16_t MENU_THRESHOLD = 1200;
    static const uint16_t QR_THRESHOLD = 600;
    static const uint16_t NUMBER_THRESHOLD = 800;
};

#endif // MAINVIEW_HPP
