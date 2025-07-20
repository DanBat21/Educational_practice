#ifndef DECODINGTEXT_H
#define DECODINGTEXT_H
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QImage>

class DecodingText : public QObject
{
    Q_OBJECT

signals:
    void decodingChanged();

public:
    explicit DecodingText(QObject *parent = nullptr);

    Q_INVOKABLE QString decoding(QImage image);
    Q_INVOKABLE QBitArray getImageBits(int index, QImage& image, int bitsPerChannel);

};

#endif // DECODINGTEXT_H
