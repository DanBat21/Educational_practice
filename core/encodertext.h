#ifndef ENCODERTEXT_H
#define ENCODERTEXT_H
#include <QImage>
#include <QBuffer>
#include <QBitArray>
#include <QObject>

class EncoderText : public QObject
{
    Q_OBJECT
signals:
    void codingChanged();


public:
    explicit EncoderText(QObject *parent = nullptr);

    Q_INVOKABLE QImage coding(QString text, QImage image, int param);
    void writeChanel(int index, QBitArray bitsToWrite, QImage& image);

private:

};
#endif // ENCODERTEXT_H
