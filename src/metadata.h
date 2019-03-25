#ifndef METADATA_H
#define METADATA_H

#include <QString>

class Metadata
{

public:
    Metadata(QString filePath);

    // Metadata items
    QString album;
    QString artist;
    QString date;
    QString genre;
    QString title;
    QString track;
    QString trackTotal;

private:
    QString filePath;
    void parseData();
};

#endif
