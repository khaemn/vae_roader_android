#include "desktopvideoproducer.h"

#include <QtQml/qqml.h>

#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
#include <QQuickItemGrabResult>

// NOTE: This does not cover all cases - it should be easy to add new ones as required.
inline QImage  cvMatToQImage( const cv::Mat &inMat )
{
    switch ( inMat.type() )
    {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_ARGB32 );

        return image;
    }

        // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_RGB888 );

        return image.rgbSwapped();
    }

        // 8-bit, 1 channel
    case CV_8UC1:
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Grayscale8 );
#else
        static QVector<QRgb>  sColorTable;

        // only create our color table the first time
        if ( sColorTable.isEmpty() )
        {
            sColorTable.resize( 256 );

            for ( int i = 0; i < 256; ++i )
            {
                sColorTable[i] = qRgb( i, i, i );
            }
        }

        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Indexed8 );

        image.setColorTable( sColorTable );
#endif

        return image;
    }

    default:
        qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
    }

    return QImage();
}

void DesktopVideoProducer::registerQmlType()
{
    //Регистрируем наш класс в составе пакета DesktopVideoProducer,
    //под версией 0.1, под именем DesktopVideoProducer.
    //Нижележащая строчка является подсказкой для парсера типов QtCreator,
    //и она не обязательна.
    // @uri DesktopVideoProducer
    qmlRegisterType<DesktopVideoProducer>(
                "DesktopVideoProducer", 0, 1,
                "DesktopVideoProducer" );
}

DesktopVideoProducer::DesktopVideoProducer( QObject *parent )
    : QObject( parent ), _surface( 0 )
{
    //m_cap.open(0);
    startTimer( 1000 / 15 ); //15 fps
}

DesktopVideoProducer::~DesktopVideoProducer()
{
    //m_cap.release();
    closeSurface();
}

QAbstractVideoSurface* DesktopVideoProducer::videoSurface() const
{
    return _surface;
}

void DesktopVideoProducer::setVideoSurface( QAbstractVideoSurface* s )
{
    closeSurface();
    _surface = s;
}

void DesktopVideoProducer::scan()
{
    using namespace cv;
    if( !_surface )
        return;

    QImage img = m_result->image().convertToFormat(QImage::Format_ARGB32);
    m_is_grabbing = false;
    // imshow("Grab", m_grab);
    cv::Mat input(img.height(), img.width(),
                  CV_8UC4,
                  const_cast<uchar*>(img.bits()),
                  static_cast<size_t>(img.bytesPerLine())
                  );

    //Canny(input, input, 100, 200);
    //equalizeHist(input, input);
    cvtColor(input, input, COLOR_RGB2BGR);
    Mat norm_color = input.clone();
    cvtColor(norm_color, norm_color, COLOR_BGR2RGB);

    float alpha = 0.5;
    float beta = 1 - alpha;
    addWeighted(input, alpha, norm_color, beta, 0, input);


    QImage processed = cvMatToQImage(input).convertToFormat(QImage::Format::Format_RGB32);
    if (processed.isNull()) {
        qDebug() << "NULL!";
    }

    QVideoFrame::PixelFormat pixelFormat =
            QVideoFrame::pixelFormatFromImageFormat( processed.format() );

    if( processed.size() != _format.frameSize() ||
            pixelFormat != _format.pixelFormat() )
    {
        closeSurface();
        _format =
                QVideoSurfaceFormat( processed.size(),
                                     pixelFormat );
        _surface->start( _format );
    }

    _surface->present( QVideoFrame( processed ) );
}

void DesktopVideoProducer::closeSurface()
{
    if( _surface && _surface->isActive() )
        _surface->stop();
}

void DesktopVideoProducer::setCamera(QQuickItem* ptr)
{
    if (ptr)
    {
        m_camera = ptr;
    }
}

void DesktopVideoProducer::recognize()
{
    if (m_camera == nullptr || m_is_grabbing) {
        return;
    }
    m_result = m_camera->grabToImage();
    connect(m_result.data(), &QQuickItemGrabResult::ready,
            this, &DesktopVideoProducer::scan);
    m_is_grabbing = true;
}

void DesktopVideoProducer::timerEvent( QTimerEvent* )
{
    //scan();
}
