#ifndef RK_METADATA_RETRIEVER_H
#define RK_METADATA_RETRIEVER_H

#include <media/MediaMetadataRetrieverInterface.h>
#include <utils/KeyedVector.h>

#ifdef AVS50
#include <media/IMediaHTTPService.h>
#endif

namespace android
{

class RetrieverDelegate;

#ifdef AVS90
#ifndef MediaMetadataRetrieverInterface
#define MediaMetadataRetrieverInterface  MediaMetadataRetrieverBase
#endif
#endif

class RK_MetadataRetriever: public MediaMetadataRetrieverInterface
{
public:
    RK_MetadataRetriever();
    virtual ~RK_MetadataRetriever();
#ifdef AVS60
    virtual status_t            setDataSource(const sp<DataSource>& source){return NO_ERROR;};
    virtual status_t            setDataSource(const sp<DataSource>& source, const char *mime){return NO_ERROR;};
#endif
#ifdef AVS50
    virtual status_t            setDataSource(const sp<IMediaHTTPService> &httpService,
                                              const char *uri, const KeyedVector<String8, String8> *headers);
#else
    virtual status_t            setDataSource(const char *url, const KeyedVector<String8, String8> *headers);
#endif
    virtual status_t            setDataSource(int fd, int64_t offset, int64_t length);
#ifdef AVS90
    virtual sp<IMemory>         getFrameAtTime(int64_t timeUs, int option, int colorFormat, bool metaOnly);
    virtual sp<IMemory>         getImageAtIndex(int index, int colorFormat, bool metaOnly, bool thumbnail);
    virtual sp<IMemory>         getImageRectAtIndex(int index, int colorFormat, int left, int top, int right, int bottom);
    virtual status_t            getFrameAtIndex(std::vector<sp<IMemory> >* frames,
                                        int frameIndex, int numFrames, int colorFormat, bool metaOnly);
#else
    virtual VideoFrame*         getFrameAtTime(int64_t timeUs, int option);
    virtual VideoFrame*         getFrameAtTime(int64_t timeUs, int option, int colorFormat, bool metaOnly);
#endif
    virtual MediaAlbumArt*      extractAlbumArt();
    virtual const char*         extractMetadata(int keyCode);

private:
    RetrieverDelegate *mRetrieverDelegate;

    RK_MetadataRetriever(const RK_MetadataRetriever &);
    RK_MetadataRetriever &operator=(const RK_MetadataRetriever &);

};
}
#endif // RK_METADATA_RETRIEVER_H
