#include <gui/containers/NumberAnimator.hpp>
#include <gui/common/Constants.hpp>

NumberAnimator::NumberAnimator() :
    currentNumber(0),
    tickCounter(0),
    animateOnEven(true),
    animateOnEveryTick(false),
    moveAnimationRunning(false),
    moveAnimationCounter(0),
    moveAnimationDelay(0),
    moveAnimationDuration(0),
    moveAnimationStartX(0),
    moveAnimationStartY(0),
    moveAnimationEndX(0),
    moveAnimationEndY(0),
    moveAnimationXEquation(),
    moveAnimationYEquation()
{
}

void NumberAnimator::initialize()
{
    NumberAnimatorBase::initialize();
    Application::getInstance()->registerTimerWidget(this);
}

void NumberAnimator::handleTickEvent()
{
    tickCounter++;

    // Mechanism to only update the widget in either even or odd ticks. This is used to
    // ensure that only one of two NumberAnimators will update for a given tick
    if ((animateOnEven && (tickCounter % 2 == 1)) || (!animateOnEven && (tickCounter % 2 == 0)))
    {
        return;
    }

    if (moveAnimationRunning)
    {
        moveAnimationCounter++;
        if (moveAnimationCounter >= moveAnimationDelay)
        {
            if (numberImage1.getY() < 0)
            {
                moveAnimationStartY += numberImage0.getHeight();
                moveAnimationEndY += numberImage0.getHeight();
            }

            // Adjust the used animationCounter for the startup delay
            uint32_t actualAnimationCounter = moveAnimationCounter - moveAnimationDelay;

            int16_t deltaX = moveAnimationXEquation(actualAnimationCounter, 0, moveAnimationEndX - moveAnimationStartX, moveAnimationDuration);
            int16_t deltaY = moveAnimationYEquation(actualAnimationCounter, 0, moveAnimationEndY - moveAnimationStartY, moveAnimationDuration);

            numberImage0.moveTo(moveAnimationStartX + deltaX, moveAnimationStartY + deltaY);
            numberImage1.moveTo(moveAnimationStartX + deltaX, numberImage0.getHeight() + moveAnimationStartY + deltaY);

            // touchgfx_printf("Y = %i Y2 = %i\n", numberImage0.getY(), numberImage1.getY());

            if (moveAnimationCounter >= (uint32_t)(moveAnimationDelay + moveAnimationDuration))
            {
                // End of animation
                moveAnimationRunning = false;
                moveAnimationCounter = 0;
                Application::getInstance()->unregisterTimerWidget(this);
            }
        }
    }
}

void NumberAnimator::startMoveAnimation(int16_t endX, int16_t endY, uint16_t duration, EasingEquation xProgressionEquation = &EasingEquations::linearEaseNone, EasingEquation yProgressionEquation = &EasingEquations::linearEaseNone)
{
    if (!moveAnimationRunning)
    {
        Application::getInstance()->registerTimerWidget(this);
    }

    moveAnimationCounter = 0;
    moveAnimationStartX = numberImage0.getX();
    moveAnimationStartY = numberImage0.getY();
    moveAnimationEndX = endX;
    moveAnimationEndY = endY;
    moveAnimationDuration = duration;
    moveAnimationXEquation = xProgressionEquation;
    moveAnimationYEquation = yProgressionEquation;

    moveAnimationRunning = true;

    if (moveAnimationDelay == 0 && moveAnimationDuration == 0)
    {
        handleTickEvent(); // Set end position and shut down
    }
}

void NumberAnimator::setAnimationDelay(uint16_t delay)
{
    moveAnimationDelay = delay;
}

void NumberAnimator::animateToNumber(int number, uint16_t duration, EasingEquation xProgressionEquation = &EasingEquations::linearEaseNone, EasingEquation yProgressionEquation = &EasingEquations::linearEaseNone)
{
    int numbersToMove = (number > currentNumber) ? number - currentNumber : 10 + number - currentNumber;
    animateNumbers(numbersToMove, duration, xProgressionEquation, yProgressionEquation);
}

void NumberAnimator::animateNumbers(int number, uint16_t duration, EasingEquation xProgressionEquation = &EasingEquations::linearEaseNone, EasingEquation yProgressionEquation = &EasingEquations::linearEaseNone)
{
    if (!moveAnimationRunning)
    {
        startMoveAnimation(numberImage0.getX(), numberImage0.getY() - (number * 153), duration, xProgressionEquation, yProgressionEquation);
        currentNumber = (currentNumber + number) % 10;
    }
}

int NumberAnimator::getCurrentNumber()
{
    return currentNumber;
}

bool NumberAnimator::isAnimating()
{
    return moveAnimationRunning;
}

void NumberAnimator::startFadeAnimation()
{
    if (!isFadeAnimationRunning() && !isAnimating())
    {
        const uint8_t END_ALPHA = !numberImage1.getAlpha() ? 255 : 0;
        const uint8_t FADE_DELAY = END_ALPHA == 255 ? Constants::FADE_DURATION : 0;

        numberImage0.setFadeAnimationDelay(FADE_DELAY);
        numberImage1.setFadeAnimationDelay(FADE_DELAY);
        numberImage0.startFadeAnimation(END_ALPHA, Constants::FADE_DURATION);
        numberImage1.startFadeAnimation(END_ALPHA, Constants::FADE_DURATION);
    }
}

bool NumberAnimator::isFadeAnimationRunning()
{
    return numberImage1.isFadeAnimationRunning();
}

bool NumberAnimator::getAnimateOnEveryTick()
{
    return animateOnEveryTick;
}

void NumberAnimator::setAnimateOnEvenTick(bool even)
{
    animateOnEven = even;
}
