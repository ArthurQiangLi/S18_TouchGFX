#include <gui/containers/CircleAnimator.hpp>
#include <math.h>
#include <gui/common/Constants.hpp>

CircleAnimator::CircleAnimator()
{
    // The numbers of ticks that are between each circle starts animating
    animationDurationCircleDisplacement = 8;

    // The total animation duration of one cycle
    animationDuration = NUMBER_OF_CIRCLES * animationDurationCircleDisplacement;

    // The radius of the circle where on the animating circles are to be placed
    placementCircleRadius = (getWidth() - circle0.getWidth() - 4) / 2;

    // The radius of the animating circles
    circleRadius = circle0.getWidth() / 2;

    // Place the animating circles in an array for easy access
    circles[0] = &circle0;
    circles[1] = &circle1;
    circles[2] = &circle2;
    circles[3] = &circle3;
    circles[4] = &circle4;
    circles[5] = &circle5;
    circles[6] = &circle6;
    circles[7] = &circle7;

    resetAnimation();
    running = false;
}

void CircleAnimator::initialize()
{
    CircleAnimatorBase::initialize();

    Application::getInstance()->registerTimerWidget(this);
}

void CircleAnimator::handleTickEvent()
{
    if (!running)
    {
        return;
    }

    // A delay mechanism for delaying the start of animation
    if (tickCounter < -1)
    {
        tickCounter++;
        return;
    }


    EasingEquation easingEq = &EasingEquations::sineEaseInOut;
    tickCounter++;

    for (int i = 0; i < NUMBER_OF_CIRCLES; i++)
    {
        if (tickCounter % animationDuration == i * animationDurationCircleDisplacement)
        {
            if ((tickCounter / animationDuration) % 2 == 0)
            {
                circles[i]->startMoveAnimation(getCircleEndX(i), getCircleEndY(i), animationDuration, easingEq, easingEq);
            }
            else
            {
                circles[i]->startMoveAnimation(getCircleStartX(i), getCircleStartY(i), animationDuration, easingEq, easingEq);
            }
        }
    }

    int fadeAnimationDurationTotal = animationDuration * 11;
    if (tickCounter % fadeAnimationDurationTotal == 0)
    {
        int newAlpha = ((tickCounter / fadeAnimationDurationTotal) % 2 == 1) ? 0 : 255;

        // Fade in/out circles
        for (int i = 1; i < NUMBER_OF_CIRCLES; i++)
        {
            circles[i]->setFadeAnimationDelay(animationDuration * i);
            circles[i]->startFadeAnimation(newAlpha, animationDuration);
        }

        if (tickCounter > 40)
        {
            lines.setAlpha(newAlpha);
            lines.invalidate();
        }
    }
}

void CircleAnimator::resetAnimation()
{
    tickCounter = -1;

    for (int i = 0; i < NUMBER_OF_CIRCLES; i++)
    {
        circles[i]->moveTo(getCircleStartX(i), getCircleStartY(i));
        circles[i]->setAlpha(0);
    }
    lines.setAlpha(0);
}

void CircleAnimator::startFadeInAnimation()
{
    resetAnimation();

    tickCounter = -20;

    circle0.setFadeAnimationDelay(Constants::FADE_DURATION);
    circle0.startFadeAnimation(255, 10);

    running = true;
}

void CircleAnimator::startFadeOutAnimation()
{
    for (int i = 0; i < NUMBER_OF_CIRCLES; i++)
    {
        circles[i]->setFadeAnimationDelay(0);
        circles[i]->startFadeAnimation(0, Constants::FADE_DURATION);
    }

    lines.setAlpha(0);
    lines.invalidate();

    running = false;
}

bool CircleAnimator::isFadeAnimationRunning()
{
    return circles[0]->isFadeAnimationRunning();
}

int CircleAnimator::getCircleStartX(int circleIndex)
{
    return static_cast<int>((getWidth() / 2) + (cos((PI / 8.0f) * circleIndex) * placementCircleRadius) - circleRadius);
}

int CircleAnimator::getCircleStartY(int circleIndex)
{
    return static_cast<int>((getHeight() / 2) - (sin((PI / 8.0f) * circleIndex) * placementCircleRadius) - circleRadius);
}

int CircleAnimator::getCircleEndX(int circleIndex)
{
    return getCircleStartX(circleIndex + NUMBER_OF_CIRCLES);
}

int CircleAnimator::getCircleEndY(int circleIndex)
{
    return getCircleStartY(circleIndex + NUMBER_OF_CIRCLES);
}
