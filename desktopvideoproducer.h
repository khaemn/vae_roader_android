#ifndef DESKTOPVIDEOPRODUCER_H
#define DESKTOPVIDEOPRODUCER_H

#include <QObject>

#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QQuickItem>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class DesktopVideoProducer : public QObject
{
    Q_OBJECT

public:
    //Для того чтобы класс был доступен для использования в Qml его необходимо регистрировать
    static void registerQmlType();

    explicit DesktopVideoProducer( QObject *parent = 0 );
    ~DesktopVideoProducer();

   //то самое property, упомянутое выше
    Q_PROPERTY( QAbstractVideoSurface* videoSurface READ videoSurface WRITE setVideoSurface )

    Q_INVOKABLE void setCamera(QQuickItem* ptr);
    Q_INVOKABLE void recognize();

    QAbstractVideoSurface* videoSurface() const;
    void setVideoSurface( QAbstractVideoSurface* s );

public slots:
    void scan();

protected:
    void timerEvent( QTimerEvent* );

private:
    void closeSurface();

private:
    QSharedPointer<QQuickItemGrabResult> m_result;
    QQuickItem* m_camera = nullptr;

    QAbstractVideoSurface* _surface;
    QVideoSurfaceFormat _format;
    cv::VideoCapture m_cap;
    cv::Mat m_grab;
};

#endif // DESKTOPVIDEOPRODUCER_H
