#ifndef DECODERTEXT_H
#define DECODERTEXT_H
#include <QImage>
#include <QObject>
#include <QBitArray>

class DecoderText : public QObject
{
    Q_OBJECT
signals:
    void decodingChanged();

public:
    explicit DecoderText(QObject *parent = nullptr);

    Q_INVOKABLE QString decoding(QImage image);
    Q_INVOKABLE QBitArray getImageBits(int index, QImage& image, int bitsPerChannel);
};

#endif // DECODERTEXT_H
