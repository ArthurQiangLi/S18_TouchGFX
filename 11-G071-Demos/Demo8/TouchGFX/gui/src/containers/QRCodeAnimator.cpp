#include <gui/containers/QRCodeAnimator.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/Unicode.hpp>
#include <gui/common/Constants.hpp>

QRCodeAnimator::QRCodeAnimator()
{
    animationTick = -1;
    animationDuration = 30;

    urls[0] = "https://support.touchgfx.com/academy/academy-introduction";
    urls[1] = "https://support.touchgfx.com/academy/category/tutorials";
    urls[2] = "https://support.touchgfx.com/academy/how-to/how-to-introduction";

    currentStringDisplaying = -1;
    nextStringToDisplay = 0;
    updateCurrentStringToDisplay();
}

void QRCodeAnimator::initialize()
{
    QRCodeAnimatorBase::initialize();
}

void QRCodeAnimator::handleTickEvent()
{
    if (isAnimationRunning())
    {
        if (animationTick <= animationDuration)
        {
            int16_t currentWidthToDisplay = EasingEquations::cubicEaseOut(animationTick, 0, qrCodeAnimationOverlay.getWidth(), animationDuration);

            int oldWidth = qrViewPort.getWidth();

            qrViewPort.setWidth(currentWidthToDisplay);

            Rect r = Rect(oldWidth, 0, currentWidthToDisplay - oldWidth, qrViewPort.getHeight());
            qrViewPort.invalidateRect(r);

            animationTick++;
        }
        else
        {
            animationTick = -1;
            qrViewPort.setWidth(0);
            updateCurrentStringToDisplay();

            Application::getInstance()->unregisterTimerWidget(this);
        }
    }
}

void QRCodeAnimator::animateToNextQR()
{
    if (!isAnimationRunning())
    {
        animationTick = 0;
        Application::getInstance()->registerTimerWidget(this);
    }
}

bool QRCodeAnimator::isAnimationRunning()
{
    return animationTick >= 0;
}

void QRCodeAnimator::startFadeAnimation()
{
    if (!isFadeAnimationRunning())
    {
        const uint8_t END_ALPHA = (qrCodeMain.getAlpha() > 0) ? 0 : 255;
        const uint8_t FADE_DELAY = END_ALPHA == 255 ? Constants::FADE_DURATION : 0;

        qrCodeMain.setFadeAnimationDelay(FADE_DELAY);
        academyLogo.setFadeAnimationDelay(FADE_DELAY);
        qrCodeMainCircle.setFadeAnimationDelay(FADE_DELAY);
        qrCodeMainText.setFadeAnimationDelay(FADE_DELAY);

        qrCodeMain.startFadeAnimation(END_ALPHA, Constants::FADE_DURATION);
        academyLogo.startFadeAnimation(END_ALPHA, Constants::FADE_DURATION);
        qrCodeMainCircle.startFadeAnimation(END_ALPHA, Constants::FADE_DURATION);
        qrCodeMainText.startFadeAnimation(END_ALPHA, Constants::FADE_DURATION);
    }
}

bool QRCodeAnimator::isFadeAnimationRunning()
{
    return qrCodeMain.isFadeAnimationRunning();
}

void QRCodeAnimator::updateCurrentStringToDisplay()
{
    currentStringDisplaying = (currentStringDisplaying + 1) % numberOfUrls;
    nextStringToDisplay = (currentStringDisplaying + 1) % numberOfUrls;

    qrCodeMain.convertStringToQRCode(urls[currentStringDisplaying]);
    qrCodeAnimationOverlay.convertStringToQRCode(urls[nextStringToDisplay]);

    Unicode::snprintf(qrCodeMainTextBuffer, QRCODEMAINTEXT_SIZE, "%i", currentStringDisplaying + 1);
    Unicode::snprintf(qrCodeAnimationOverlayTextBuffer, QRCODEANIMATIONOVERLAYTEXT_SIZE, "%i", nextStringToDisplay + 1);

    qrCodeMain.invalidate();
}
