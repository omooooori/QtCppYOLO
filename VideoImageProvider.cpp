#include "VideoImageProvider.h"


VideoImageProvider::VideoImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
    capture_ = cvCaptureFromCam(0);
}


VideoImageProvider::~VideoImageProvider()
{
    cvReleaseCapture(&capture_);
}


QPixmap VideoImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    // get camera input
    cv::Mat img = cvQueryFrame(capture_);

    // resize
    *size = QSize(img.cols, img.rows);
    int width  = requestedSize.width()  > 0 ? requestedSize.width()  : img.rows;
    int height = requestedSize.height() > 0 ? requestedSize.height() : img.cols;
    cv::Mat resized_img(width, height, img.type());
    cv::resize(img, resized_img, resized_img.size(), cv::INTER_CUBIC);

    // BGR -> ARGB
    cv::cvtColor(resized_img, resized_img, CV_BGR2BGRA);
    std::vector<cv::Mat> bgra;
    cv::split(resized_img, bgra);
    std::swap(bgra[0], bgra[3]);
    std::swap(bgra[1], bgra[2]);

    QImage video_img(resized_img.data, resized_img.cols, resized_img.rows, QImage::Format_ARGB32);
    return QPixmap::fromImage(video_img);
}
