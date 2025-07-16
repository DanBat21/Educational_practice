#ifndef CODINGTEXT_H
#define CODINGTEXT_H
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QImage>
#include <QBuffer>
#include <QBitArray>

class CodingText : public QObject
{
    Q_OBJECT

signals:
    void codingChanged();


public:
    explicit CodingText(QObject *parent = nullptr);

    Q_INVOKABLE QImage coding(QString text, QImage image, int param);
    void writeChanel(int index, QBitArray bitsToWrite, QImage& image);

private:

};

#endif // CODINGTEXT_H
