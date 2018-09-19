/*
**
** Copyright 2009, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#ifndef ANDROID_RETRIEVER_H
#define ANDROID_RETRIEVER_H

#include <media/MediaMetadataRetrieverInterface.h>

namespace android {

#ifdef AVS90
#ifndef MediaMetadataRetrieverInterface
#define MediaMetadataRetrieverInterface  MediaMetadataRetrieverBase
#endif
#endif

class RK_MetadataRetriever;
typedef int (*CreateRetriever)(RK_MetadataRetriever **mediaRetriever);
typedef int (*DestroyRetriever)(RK_MetadataRetriever **mediaRetriever);

class RkRetriever : public MediaMetadataRetrieverInterface {
public:
   public:
    RkRetriever();
    virtual ~RkRetriever();
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
    virtual status_t            setDataSource(const sp<DataSource>& source, const char *mime);
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

    RK_MetadataRetriever *mMediaRetriever;
    void *mVendorLibHandle;

    RkRetriever(const RkRetriever &);
    RkRetriever &operator=(const RkRetriever &);

    void createRetriever(const char *libname);
    void destroyRetriever();
};

}  // namespace android

#endif  // ANDROID_RETRIEVER_H
