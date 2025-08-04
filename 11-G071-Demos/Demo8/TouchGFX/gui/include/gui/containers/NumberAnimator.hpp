#ifndef NUMBERANIMATOR_HPP
#define NUMBERANIMATOR_HPP

#include <gui_generated/containers/NumberAnimatorBase.hpp>


class NumberAnimator : public NumberAnimatorBase
{
public:
    NumberAnimator();
    virtual ~NumberAnimator() {}
    virtual void initialize();
    virtual void handleTickEvent();

    void setAnimationDelay(uint16_t delay);
    void animateNumbers(int number, uint16_t duration, EasingEquation xProgressionEquation, EasingEquation yProgressionEquation);
    bool isAnimating();

    void startFadeAnimation();
    bool isFadeAnimationRunning();

    int getCurrentNumber();

    bool getAnimateOnEveryTick();
    void setAnimateOnEvenTick(bool even);

protected:
    int currentNumber;

    int tickCounter;
    bool animateOnEven;
    bool animateOnEveryTick;

    bool moveAnimationRunning;             ///< True if the animation is running
    uint16_t moveAnimationCounter;         ///< Counter that is equal to the current step in the animation
    uint16_t moveAnimationDelay;           ///< The delay applied before animation start. Expressed in ticks.
    uint16_t moveAnimationDuration;        ///< The complete duration of the actual animation. Expressed in ticks.
    int16_t moveAnimationStartX;           ///< The X value at the beginning of the animation.
    int16_t moveAnimationStartY;           ///< The Y value at the beginning of the animation.
    int16_t moveAnimationEndX;             ///< The X value at the end of the animation.
    int16_t moveAnimationEndY;             ///< The Y value at the end of the animation.
    EasingEquation moveAnimationXEquation; ///< EasingEquation expressing the development of the X value during the animation.
    EasingEquation moveAnimationYEquation; ///< EasingEquation expressing the development of the Y value during the animation.

    void startMoveAnimation(int16_t endX, int16_t endY, uint16_t duration, EasingEquation xProgressionEquation, EasingEquation yProgressionEquation);
    void animateToNumber(int number, uint16_t duration, EasingEquation xProgressionEquation, EasingEquation yProgressionEquation);
};

#endif // NUMBERANIMATOR_HPP
