#include <gui/main_screen/MainView.hpp>
#include <images/BitmapDatabase.hpp>
#include <gui/common/Constants.hpp>

MainView::MainView() {

}

void MainView::setupScreen() {
	MainViewBase::setupScreen();

	numberAnimator0.startFadeAnimation();
	numberAnimator1.startFadeAnimation();
	numberAnimator0.setAnimationDelay(15);
	numberAnimator1.setAnimationDelay(15);
	numberAnimator0.animateNumbers(7, 150, EasingEquations::cubicEaseOut,
			EasingEquations::backEaseInOut);
	numberAnimator1.animateNumbers(33, 150, EasingEquations::cubicEaseOut,
			EasingEquations::cubicEaseInOut);
//    inactiveThreshold = NUMBER_THRESHOLD;
	inactiveCounter = 0;
}

void MainView::tearDownScreen() {
	MainViewBase::tearDownScreen();
}

void MainView::handleTickEvent() {
	inactiveCounter++;
	// Go to next menu item or execute next action when idle for specified time
	if (inactiveCounter > NUMBER_THRESHOLD) {
		inactiveCounter = 0;
		if (!numberAnimator0.isAnimating()) {
			int duration = numberAnimator0.getAnimateOnEveryTick() ? 300 : 150;
			numberAnimator0.setAnimationDelay(0);
			numberAnimator1.setAnimationDelay(0);
			numberAnimator0.animateNumbers(17, duration,
					EasingEquations::cubicEaseOut,
					EasingEquations::backEaseInOut);
			numberAnimator1.animateNumbers(11, duration,
					EasingEquations::cubicEaseOut,
					EasingEquations::cubicEaseInOut);
		}
	}
}

