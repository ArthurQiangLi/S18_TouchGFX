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


protected:
    int inactiveCounter;
    int inactiveThreshold;


    static const uint16_t NUMBER_THRESHOLD = 800;

};

#endif // MAINVIEW_HPP
