#include <gui/main_screen/MainView.hpp>
#include <images/BitmapDatabase.hpp>
#include <gui/common/Constants.hpp>

MainView::MainView() :
    inactiveCounter(0),
    inactiveThreshold(MENU_THRESHOLD)
{
}

void MainView::setupScreen()
{
    MainViewBase::setupScreen();

    // Trick to distribute screen updates of the numbers in the numberAnimators
    // so that the overall load will be decreased, as this demo is aimed for lower performance MCUs
    // Alternate between moving the first and the second number, so that only one number is
    // moved and thus updated each tick. This reduces the effort needed by the MCU and is hard to see
    // in a fast running animation
    numberAnimator0.setAnimateOnEvenTick(true);
    numberAnimator1.setAnimateOnEvenTick(false);

    nextActionHandler();
}

void MainView::tearDownScreen()
{
    MainViewBase::tearDownScreen();
}

void MainView::handleTickEvent()
{
    inactiveCounter++;

    // Go to next menu item or execute next action when idle for specified time
    if (inactiveCounter > inactiveThreshold)
    {
        resetInactiveCounter();

        if (imageAnimator.isActive())
        {
            imageAnimator.animateToNextMenuItem();
            inactiveThreshold = 500;
        }
        else
        {
            nextActionHandler();
        }
    }

    // Set select text
    if (imageAnimator.isActive() && !imageAnimator.isFadeAnimationRunning() && selectText.getBitmapId() == BITMAP_EXIT_TEXT_ID)
    {
        selectText.setBitmap(BITMAP_ENTER_TEXT_ID);
        selectText.invalidate();
    }
    else if (!imageAnimator.isActive() && !imageAnimator.isFadeAnimationRunning() && selectText.getBitmapId() == BITMAP_ENTER_TEXT_ID)
    {
        selectText.setBitmap(BITMAP_EXIT_TEXT_ID);
        selectText.invalidate();
    }

    // Set demo name
    if (imageAnimator.isActive() && !demoNameText.isVisible())
    {
        demoNameText.setVisible(true);
        demoNameText.invalidate();
    }
    else if (!imageAnimator.isActive() && demoNameText.isVisible())
    {
        demoNameText.setVisible(false);
        demoNameText.invalidate();
    }

    // Hide or show next icon
    if (numberAnimator0.isAnimating() && nextIcon.isVisible())
    {
        selectText.setVisible(false);
        selectText.invalidate();
        nextIcon.setVisible(false);
        nextIcon.invalidate();
    }
    else if (!numberAnimator0.isAnimating() && !nextIcon.isVisible() && imageAnimator.getCurrentAnimatorImage() == ImageAnimator::touchgfxLogo)
    {
        selectText.setVisible(true);
        selectText.invalidate();
        nextIcon.setVisible(true);
        nextIcon.invalidate();
    }
    else if (!imageAnimator.isActive() && imageAnimator.getCurrentAnimatorImage() == ImageAnimator::circleAnimationsLogo && nextIcon.isVisible())
    {
        nextIcon.setVisible(false);
        nextIcon.invalidate();
    }
}

void MainView::handleClickEvent(const ClickEvent& event)
{
    if (event.getType() == ClickEvent::RELEASED)
    {
        // Select button pressed
        if (event.getX() < 120 && event.getY() < 80)
        {
            selectActionHandler();
        }
        // Next button pressed
        else if (event.getX() > 120 && event.getY() < 100)
        {
            nextActionHandler();
        }
    }
}

void MainView::selectActionHandler()
{
    resetInactiveCounter();

    if (imageAnimator.isFadeAnimationRunning() ||
            numberAnimator0.isFadeAnimationRunning() ||
            qrCodeAnimator.isFadeAnimationRunning() ||
            circleAnimator.isFadeAnimationRunning())
    {
        return;
    }

    // If the imageAnimator is active the menu part is showing, if not, one of the subscreens are (numbers, qrCode, ...)
    if (imageAnimator.isActive())
    {
        // Guard - do not receive events when the imageAnimator is animating
        if (imageAnimator.isAnimateToMenuItemRunning())
        {
            return;
        }

        imageAnimator.setFadeAnimiationDelay(0);
        imageAnimator.startFadeAnimation();

        // Handle "select" action for the menu.
        // This is to fade out the menu and fade in the selected sub demo.
        switch (imageAnimator.getCurrentAnimatorImage())
        {
        case ImageAnimator::touchgfxAcademy:
            qrCodeAnimator.startFadeAnimation();
            inactiveThreshold = QR_THRESHOLD;
            break;
        case ImageAnimator::touchgfxLogo:
            numberAnimator0.startFadeAnimation();
            numberAnimator1.startFadeAnimation();
            numberAnimator0.setAnimationDelay(15);
            numberAnimator1.setAnimationDelay(15);
            numberAnimator0.animateNumbers(7, 150, EasingEquations::cubicEaseOut, EasingEquations::backEaseInOut);
            numberAnimator1.animateNumbers(33, 150, EasingEquations::cubicEaseOut, EasingEquations::cubicEaseInOut);
            inactiveThreshold = NUMBER_THRESHOLD;
            break;
        case ImageAnimator::circleAnimationsLogo:
            circleAnimator.startFadeInAnimation();
            inactiveThreshold = -1;
            nextIcon.setVisible(false);
            nextIcon.invalidate();
            break;
        default:
            break;
        }
    }
    else
    {
        // Handle "select" action for each of the sub demos.
        // This is to fade out and show the menu images.
        switch (imageAnimator.getCurrentAnimatorImage())
        {
        case ImageAnimator::touchgfxAcademy:

            if (!qrCodeAnimator.isAnimationRunning() && !qrCodeAnimator.isFadeAnimationRunning())
            {
                // Goto menu from qrCode
                imageAnimator.startFadeAnimation();
                imageAnimator.setFadeAnimiationDelay(Constants::FADE_DURATION);

                qrCodeAnimator.startFadeAnimation();
            }
            else
            {
                return;
            }
            break;
        case ImageAnimator::touchgfxLogo:
            if (!numberAnimator0.isAnimating() && !numberAnimator0.isFadeAnimationRunning())
            {
                // Goto menu from numbers
                imageAnimator.startFadeAnimation();
                imageAnimator.setFadeAnimiationDelay(Constants::FADE_DURATION);

                numberAnimator0.startFadeAnimation();
                numberAnimator1.startFadeAnimation();
            }
            else
            {
                return;
            }
            break;
        case ImageAnimator::circleAnimationsLogo:
            // Goto menu from circle animation
            imageAnimator.startFadeAnimation();
            imageAnimator.setFadeAnimiationDelay(Constants::FADE_DURATION);

            circleAnimator.startFadeOutAnimation();

            nextIcon.setVisible(true);
            nextIcon.invalidate();
            break;
        default:
            break;
        }

        inactiveThreshold = MENU_THRESHOLD;
    }
}

void MainView::nextActionHandler()
{
    resetInactiveCounter();

    if (imageAnimator.isFadeAnimationRunning() ||
            numberAnimator0.isFadeAnimationRunning() ||
            qrCodeAnimator.isFadeAnimationRunning())
    {
        return;
    }

    // Handle the "next" action either when the menu (imageAnimator) is showing
    // or when one of the sub demos are running.
    if (imageAnimator.isActive())
    {
        // Guard - do not receive events when the imageAnimator is animating
        if (imageAnimator.isAnimateToMenuItemRunning())
        {
            return;
        }

        imageAnimator.animateToNextMenuItem();
    }
    else
    {
        switch (imageAnimator.getCurrentAnimatorImage())
        {
        case ImageAnimator::touchgfxAcademy:
            qrCodeAnimator.animateToNextQR();
            break;
        case ImageAnimator::touchgfxLogo:
            if (!numberAnimator0.isAnimating() && !numberAnimator0.isFadeAnimationRunning())
            {
                int duration = numberAnimator0.getAnimateOnEveryTick() ? 300 : 150;
                numberAnimator0.setAnimationDelay(0);
                numberAnimator1.setAnimationDelay(0);
                numberAnimator0.animateNumbers(7, duration, EasingEquations::cubicEaseOut, EasingEquations::backEaseInOut);
                numberAnimator1.animateNumbers(33, duration, EasingEquations::cubicEaseOut, EasingEquations::cubicEaseInOut);
            }
            break;
        case ImageAnimator::circleAnimationsLogo:
            // No "next" action defined for circle animation
            break;
        default:
            break;
        }
    }
}

void MainView::updateDemoName()
{
    switch (imageAnimator.getCurrentAnimatorImage())
    {
    case ImageAnimator::touchgfxAcademy:
        demoNameText.setBitmap(BITMAP_TITLE_QR_ID);
        break;
    case ImageAnimator::touchgfxLogo:
        demoNameText.setBitmap(BITMAP_TITLE_NUMBER_ID);
        break;
    case ImageAnimator::circleAnimationsLogo:
        demoNameText.setBitmap(BITMAP_TITLE_CIRCLE_ID);
        break;
    default:
        break;
    }

    demoNameText.setVisible(true);
    demoNameText.invalidate();
}

void MainView::resetInactiveCounter()
{
    inactiveCounter = 0;
}
