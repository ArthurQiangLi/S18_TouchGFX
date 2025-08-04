#ifndef QRCODEANIMATOR_HPP
#define QRCODEANIMATOR_HPP

#include <gui_generated/containers/QRCodeAnimatorBase.hpp>

class QRCodeAnimator : public QRCodeAnimatorBase
{
public:
    QRCodeAnimator();
    virtual ~QRCodeAnimator() {}
    virtual void initialize();
    virtual void handleTickEvent();

    void animateToNextQR();
    bool isAnimationRunning();

    void startFadeAnimation();
    bool isFadeAnimationRunning();

protected:
    static const int numberOfUrls = 3;
    const char* urls[numberOfUrls];

    int animationTick;
    int animationDuration;

    int currentStringDisplaying;
    int nextStringToDisplay;

    void updateCurrentStringToDisplay();
};

#endif // QRCODEANIMATOR_HPP
