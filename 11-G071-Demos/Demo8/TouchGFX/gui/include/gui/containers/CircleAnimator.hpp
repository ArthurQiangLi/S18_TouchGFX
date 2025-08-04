#ifndef CIRCLEANIMATOR_HPP
#define CIRCLEANIMATOR_HPP

#include <gui_generated/containers/CircleAnimatorBase.hpp>

class CircleAnimator : public CircleAnimatorBase
{
public:
    CircleAnimator();
    virtual ~CircleAnimator() {}
    virtual void initialize();
    virtual void handleTickEvent();

    void resetAnimation();

    void startFadeInAnimation();
    void startFadeOutAnimation();
    bool isFadeAnimationRunning();

protected:
    int tickCounter;
    int animationDuration;
    int animationDurationCircleDisplacement;

    int placementCircleRadius;
    int circleRadius;

    bool running;

    static const uint8_t NUMBER_OF_CIRCLES = 8;
    FadeAnimator< touchgfx::MoveAnimator< touchgfx::Image > >* circles[NUMBER_OF_CIRCLES];

    int getCircleStartX(int circleIndex);
    int getCircleStartY(int circleIndex);
    int getCircleEndX(int circleIndex);
    int getCircleEndY(int circleIndex);
};

#endif // CIRCLEANIMATOR_HPP
