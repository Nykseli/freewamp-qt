extern "C"
{
    #include <stdio.h>
    #include <libavformat/avformat.h>
    #include <libavutil/dict.h>
}

#include "metadata.h"

Metadata::Metadata(QString filePath)
{
    this->filePath = filePath;
    parseData();
}

void Metadata::parseData()
{
    AVFormatContext *fmt_ctx = avformat_alloc_context();
    AVDictionaryEntry *tag = NULL;


    int ret;
    if ((ret = avformat_open_input(&fmt_ctx, filePath.toStdString().c_str(), NULL, NULL)) < 0){
        // If the opening of the input fails. We cannot do anything with it
        // TODO: error logging
        goto end;
    }

    while ((tag = av_dict_get(fmt_ctx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))){
        QString key = QString(tag->key);
        if (key == "ALBUM" || key == "key") {
            album = QString(tag->value);
        } else if (key == "ARTIST" || key == "artist") {
            artist = QString(tag->value);
        } else if (key == "DATE" || key == "date") {
            date = QString(tag->value);
        } else if (key == "GENRE" || key == "genre") {
            genre = QString(tag->value);
        } else if (key == "TITLE" || key == "title") {
            title = QString(tag->value);
        } else if (key == "track" || key == "track") {
            track = QString(tag->value);
        } else if (key == "TRACKTOTAL" || key == "tracktotal") {
            trackTotal = QString(tag->value);
        }
    }

end:
    avformat_close_input(&fmt_ctx);
}
