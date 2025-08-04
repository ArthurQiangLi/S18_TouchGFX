#ifndef IMAGEANIMATOR_HPP
#define IMAGEANIMATOR_HPP

#include <gui_generated/containers/ImageAnimatorBase.hpp>

class ImageAnimator : public ImageAnimatorBase
{
public:
    enum ImageAnimatorImages
    {
        touchgfxAcademy = 0,
        touchgfxLogo,
        circleAnimationsLogo,
        NUMBER_OF_IMAGES
    };

    ImageAnimator();
    virtual ~ImageAnimator() {}
    virtual void initialize();
    virtual void handleTickEvent();

    void animateToNextMenuItem();
    bool isAnimateToMenuItemRunning();

    ImageAnimatorImages getCurrentAnimatorImage();

    void startFadeAnimation();
    void setFadeAnimiationDelay(uint16_t delay);
    bool isFadeAnimationRunning();

    bool isActive();


protected:
    int tickCounter;
    bool animatingOut;

    ImageAnimatorImages targetImage;

    bool active;

    void changeImage(ImageAnimatorImages newImage);
    void startMoveAnimation(ImageAnimatorImages image);

    touchgfx::Callback<ImageAnimator, const MoveAnimator<touchgfx::Image>&> imageCallback;
    void imageCallbackHandler(const MoveAnimator<touchgfx::Image>& src);

    static const uint8_t DISPLAY_WIDTH = 240;
    static const uint8_t DISPLAY_HEIGHT = 240;
};

#endif // IMAGEANIMATOR_HPP
