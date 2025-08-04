#include <gui/containers/ImageAnimator.hpp>
#include <images/BitmapDatabase.hpp>
#include <gui/common/Constants.hpp>

ImageAnimator::ImageAnimator() :
    tickCounter(0),
    animatingOut(false),
    targetImage(touchgfxAcademy),
    active(true),
    imageCallback(this, &ImageAnimator::imageCallbackHandler)
{
}

void ImageAnimator::initialize()
{
    ImageAnimatorBase::initialize();
    Application::getInstance()->registerTimerWidget(this);

    image1.setMoveAnimationEndedAction(imageCallback);

    startMoveAnimation(touchgfxAcademy);
}

void ImageAnimator::handleTickEvent()
{
    tickCounter++;

    if (image1.isMoveAnimationRunning())
    {
        // Trick to only move one image at each tick so that the rendering
        // can be done on time and no tearing appears on the screen
        const uint16_t NO_DELAY = 0;
        const uint16_t LARGE_DELAY = 1000;
        image1.setMoveAnimationDelay(((tickCounter % 4) == 0) ? NO_DELAY : LARGE_DELAY);
        image2.setMoveAnimationDelay(((tickCounter % 4) == 1) ? NO_DELAY : LARGE_DELAY);
        image3.setMoveAnimationDelay(((tickCounter % 4) == 2) ? NO_DELAY : LARGE_DELAY);
        image4.setMoveAnimationDelay(((tickCounter % 4) == 3) ? NO_DELAY : LARGE_DELAY);
    }
}

void ImageAnimator::animateToNextMenuItem()
{
    startMoveAnimation((ImageAnimatorImages)((getCurrentAnimatorImage() + 1) % NUMBER_OF_IMAGES));
}

void ImageAnimator::startMoveAnimation(ImageAnimatorImages image)
{
    if (!isAnimateToMenuItemRunning())
    {
        const uint8_t ICON_ANIMATION_DURATION = 50;

        targetImage = image;

        if (animatingOut)
        {
            image1.startMoveAnimation(DISPLAY_WIDTH, image1.getY(), ICON_ANIMATION_DURATION, touchgfx::EasingEquations::cubicEaseIn, touchgfx::EasingEquations::cubicEaseIn);
            image2.startMoveAnimation(-image2.getWidth(), image2.getY(), ICON_ANIMATION_DURATION, touchgfx::EasingEquations::cubicEaseIn, touchgfx::EasingEquations::cubicEaseIn);
            image3.startMoveAnimation(image3.getX(), -image3.getHeight(), ICON_ANIMATION_DURATION, touchgfx::EasingEquations::cubicEaseIn, touchgfx::EasingEquations::cubicEaseIn);
            image4.startMoveAnimation(image4.getX(), DISPLAY_HEIGHT, ICON_ANIMATION_DURATION, touchgfx::EasingEquations::cubicEaseIn, touchgfx::EasingEquations::cubicEaseIn);
        }
        else
        {
            image1.startMoveAnimation(image4.getX(), image1.getY(), ICON_ANIMATION_DURATION, touchgfx::EasingEquations::cubicEaseOut, touchgfx::EasingEquations::cubicEaseOut);
            image2.startMoveAnimation(image3.getX(), image2.getY(), ICON_ANIMATION_DURATION, touchgfx::EasingEquations::cubicEaseOut, touchgfx::EasingEquations::cubicEaseOut);
            image3.startMoveAnimation(image3.getX(), image1.getY(), ICON_ANIMATION_DURATION, touchgfx::EasingEquations::cubicEaseOut, touchgfx::EasingEquations::cubicEaseOut);
            image4.startMoveAnimation(image4.getX(), image2.getY(), ICON_ANIMATION_DURATION, touchgfx::EasingEquations::cubicEaseOut, touchgfx::EasingEquations::cubicEaseOut);
        }
    }
}

bool ImageAnimator::isAnimateToMenuItemRunning()
{
    return image1.isMoveAnimationRunning();
}

ImageAnimator::ImageAnimatorImages ImageAnimator::getCurrentAnimatorImage()
{
    return targetImage;
}

void ImageAnimator::startFadeAnimation()
{
    if (!isFadeAnimationRunning())
    {
        int targetAlpha = active ? 0 : 255;
        image1.startFadeAnimation(targetAlpha, Constants::FADE_DURATION);
        image2.startFadeAnimation(targetAlpha, Constants::FADE_DURATION);
        image3.startFadeAnimation(targetAlpha, Constants::FADE_DURATION);
        image4.startFadeAnimation(targetAlpha, Constants::FADE_DURATION);

        active = !active;
    }
}

void ImageAnimator::setFadeAnimiationDelay(uint16_t delay)
{
    image1.setFadeAnimationDelay(delay);
    image2.setFadeAnimationDelay(delay);
    image3.setFadeAnimationDelay(delay);
    image4.setFadeAnimationDelay(delay);
}

bool ImageAnimator::isFadeAnimationRunning()
{
    return image4.isFadeAnimationRunning();
}

bool ImageAnimator::isActive()
{
    return active;
}

void ImageAnimator::changeImage(ImageAnimatorImages newImage)
{
    switch (newImage)
    {
    case touchgfxAcademy:
        image1.setBitmap(BITMAP_ACADEMYTOPRIGHT_ID);
        image2.setBitmap(BITMAP_ACADEMYBOTTOMLEFT_ID);
        image3.setBitmap(BITMAP_ACADEMYTOPLEFT_ID);
        image4.setBitmap(BITMAP_ACADEMYBOTTOMRIGHT_ID);
        break;
    case touchgfxLogo:
        image1.setBitmap(BITMAP_XLOGOTOPRIGHT_ID);
        image2.setBitmap(BITMAP_XLOGOBOTTOMLEFT_ID);
        image3.setBitmap(BITMAP_XLOGOTOPLEFT_ID);
        image4.setBitmap(BITMAP_XLOGOBOTTOMRIGHT_ID);
        break;
    case circleAnimationsLogo:
        image1.setBitmap(BITMAP_TEXTSCROLLINGTOPRIGHT_ID);
        image2.setBitmap(BITMAP_TEXTSCROLLINGBOTTOMLEFT_ID);
        image3.setBitmap(BITMAP_TEXTSCROLLINGTOPLEFT_ID);
        image4.setBitmap(BITMAP_TEXTSCROLLINGBOTTOMRIGHT_ID);
        break;
    default:
        break;
    }

    image1.setXY(DISPLAY_WIDTH, DISPLAY_HEIGHT / 2 - image1.getHeight());
    image2.setXY(-image2.getWidth(), DISPLAY_HEIGHT / 2);
    image3.setXY(DISPLAY_WIDTH / 2 - image3.getWidth(), -image3.getHeight());
    image4.setXY(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT);
}

void ImageAnimator::imageCallbackHandler(const MoveAnimator<touchgfx::Image>& src)
{
    if (animatingOut)
    {
        animatingOut = false;

        changeImage(targetImage);
        startMoveAnimation(targetImage);
        emitImageIsOutCallback();
    }
    else
    {
        animatingOut = true;

        // Due to the delay trick used in handleTick we need to make sure that no
        // animation keep on running after it has actually finished
        image1.cancelMoveAnimation();
        image2.cancelMoveAnimation();
        image3.cancelMoveAnimation();
        image4.cancelMoveAnimation();
    }
}
