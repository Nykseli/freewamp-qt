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
        if (QString(tag->key) == "ALBUM") {
            album = QString(tag->value);
        } else if (QString(tag->key) == "ARTIST") {
            artist = QString(tag->value);
        } else if (QString(tag->key) == "DATE") {
            date = QString(tag->value);
        } else if (QString(tag->key) == "GENRE") {
            genre = QString(tag->value);
        } else if (QString(tag->key) == "TITLE") {
            title = QString(tag->value);
        } else if (QString(tag->key) == "track") {
            // track seems to be the only item is constantly lowercase
            track = QString(tag->value);
        } else if (QString(tag->key) == "TRACKTOTAL") {
            trackTotal = QString(tag->value);
        }
    }

end:
    avformat_close_input(&fmt_ctx);
}
