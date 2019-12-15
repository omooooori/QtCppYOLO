#pragma once

#include <QQuickImageProvider>
#include <QPixmap>

#include <opencv2/opencv.hpp>

class VideoImageProvider : public QQuickImageProvider
{
public:
    VideoImageProvider();
    ~VideoImageProvider();

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;

private:
    CvCapture* capture_;
};

