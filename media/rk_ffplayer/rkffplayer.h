#ifndef RK_FF_MEDIAPLAYER_H
#define RK_FF_MEDIAPLAYER_H

#include <media/MediaPlayerInterface.h>
#include <utils/Vector.h>

#ifdef AVS90
#define FFVirtual virtual
#else
#define FFVirtual
#endif

namespace android
{

class FFPlayerDelegate;

class FF_MediaPlayer
{
public:
    FF_MediaPlayer();
    virtual                       ~FF_MediaPlayer();
    FFVirtual void                setListener(const wp<MediaPlayerBase> &listener);
    FFVirtual status_t            setDataSource(int fd, int64_t offset, int64_t length);

    FFVirtual status_t            setDataSource(const sp<IMediaHTTPService> &httpService,
                                       const char *url, const KeyedVector<String8, String8> *headers);

    FFVirtual status_t            setSurfaceTexture(const sp<IGraphicBufferProducer> &bufferProducer);
    FFVirtual void                setAudioSink(const sp<MediaPlayerBase::AudioSink> &audioSink);
    FFVirtual status_t            dump(int fd, const Vector<String16> &args);
    FFVirtual status_t            prepare();
    FFVirtual status_t            prepareAsync();
    FFVirtual status_t            start();
    FFVirtual status_t            stop();
    FFVirtual status_t            pause();
    FFVirtual status_t            reset();
    FFVirtual bool                isPlaying();
    FFVirtual status_t            seekTo(int64_t timeUs, MediaPlayerSeekMode mode);
    FFVirtual status_t            getDuration(int64_t *durationUs);
    FFVirtual status_t            getPosition(int64_t *positionUs);
    FFVirtual status_t            invoke(const Parcel &request, Parcel *reply);
    FFVirtual status_t            getParameter(int key, Parcel *reply);
    FFVirtual status_t            setParameter(int key, const Parcel &request);
    FFVirtual uint32_t            flags() const ;
    FFVirtual status_t            setLooping(int loop) ;

private:
    FFPlayerDelegate* mPlayer;

    FF_MediaPlayer(const FF_MediaPlayer &);
    FF_MediaPlayer &operator=(const FF_MediaPlayer &);

};
}
#endif // RK_FF_MEDIAPLAYER_H
