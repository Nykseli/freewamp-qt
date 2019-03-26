#!/bin/bash

###
# Configure and compile needed ffmpeg libraries
###

# FFmpeg submodule path
cd FFmpeg

./configure \
    --prefix=../ffmpeg \
    --toolchain=hardened \
    --disable-doc \
    --disable-programs \
    --enable-gpl \
    --enable-demuxer=aac \
    --enable-demuxer=ac3 \
    --enable-demuxer=ape \
    --enable-demuxer=asf \
    --enable-demuxer=flac \
    --enable-demuxer=matroska_audio \
    --enable-demuxer=mp3 \
    --enable-demuxer=mpc \
    --enable-demuxer=mov \
    --enable-demuxer=mpc8 \
    --enable-demuxer=ogg \
    --enable-demuxer=tta \
    --enable-demuxer=wav \
    --enable-demuxer=wv \
    --disable-bsfs \
    --disable-filters \
    --disable-parsers \
    --enable-parser=aac \
    --enable-parser=ac3 \
    --enable-parser=mpegaudio \
    --disable-protocols \
    --enable-protocol=file \
    --disable-indevs \
    --disable-outdevs \
    --disable-encoders \
    --disable-decoders \
    --enable-decoder=aac \
    --enable-decoder=ac3 \
    --enable-decoder=alac \
    --enable-decoder=ape \
    --enable-decoder=flac \
    --enable-decoder=mp1 \
    --enable-decoder=mp2 \
    --enable-decoder=mp3 \
    --enable-decoder=mpc7 \
    --enable-decoder=mpc8 \
    --enable-decoder=tta \
    --enable-decoder=vorbis \
    --enable-decoder=wavpack \
    --enable-decoder=wmav1 \
    --enable-decoder=wmav2 \
    --enable-decoder=pcm_alaw \
    --enable-decoder=pcm_dvd \
    --enable-decoder=pcm_f32be \
    --enable-decoder=pcm_f32le \
    --enable-decoder=pcm_f64be \
    --enable-decoder=pcm_f64le \
    --enable-decoder=pcm_s16be \
    --enable-decoder=pcm_s16le \
    --enable-decoder=pcm_s16le_planar \
    --enable-decoder=pcm_s24be \
    --enable-decoder=pcm_daud \
    --enable-decoder=pcm_s24le \
    --enable-decoder=pcm_s32be \
    --enable-decoder=pcm_s32le \
    --enable-decoder=pcm_s8 \
    --enable-decoder=pcm_u16be \
    --enable-decoder=pcm_u16le \
    --enable-decoder=pcm_u24be \
    --enable-decoder=pcm_u24le \
    --enable-decoder=rawvideo \
    --enable-shared

make -j4
# Install will create libs to folder named ffmpeg
make install
