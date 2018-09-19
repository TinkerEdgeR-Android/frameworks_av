/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//#define LOG_NDEBUG 0
#define LOG_TAG "RkRetriever"
#include <utils/Log.h>
#include <dlfcn.h>
#include <fcntl.h>

#include "RkRetriever.h"
#include "RkMetadataRetriever.h"
#include <media/Metadata.h>
#include <media/MediaExtractor.h>

#define LIB_FFPLAYER "librkffplayer.so"

#undef ALOGV
#define ALOGV
namespace android {

RkRetriever::RkRetriever()
    : mMediaRetriever(NULL) {
    createRetriever(LIB_FFPLAYER);
}

RkRetriever::~RkRetriever() {
    destroyRetriever();
}

void RkRetriever::createRetriever(const char *libname) {
    mVendorLibHandle = dlopen(libname, RTLD_NOW);

    if (mVendorLibHandle == NULL) {
        ALOGE("Failed to load library(%s), err %s", libname, dlerror());
        return;
    }

    CreateRetriever create_retriever = (CreateRetriever)dlsym(mVendorLibHandle, "Retriever_create");
    if (create_retriever) {
        create_retriever(&mMediaRetriever);
    } else {
        ALOGE("Not found create player method)");
    }
}

void RkRetriever::destroyRetriever() {
    if (mVendorLibHandle == NULL) {
        if (mMediaRetriever) {
            delete mMediaRetriever;
            mMediaRetriever = NULL;
        }
        return;
    }

    DestroyRetriever destroy_retriever = (DestroyRetriever)dlsym(mVendorLibHandle, "Retriever_destroy");
    if (destroy_retriever) {
        destroy_retriever(&mMediaRetriever);
    } else if (mMediaRetriever) {
        delete mMediaRetriever;
        mMediaRetriever = NULL;
    }

    if (mVendorLibHandle != NULL) {
        dlclose(mVendorLibHandle);
        mVendorLibHandle = NULL;
    }
}

status_t RkRetriever::setDataSource(const sp<IMediaHTTPService> &httpService, const char *uri, const KeyedVector<String8, String8> *headers)
{
    return mMediaRetriever->setDataSource(httpService, uri, headers);
}

// Warning caller retains ownership of the filedescriptor! Dup it if necessary.
status_t RkRetriever::setDataSource(int fd, int64_t offset, int64_t length)
{
    return mMediaRetriever->setDataSource(fd, offset, length);
}

status_t RkRetriever::setDataSource(const sp<DataSource>& source, const char *mime)
{
    return mMediaRetriever->setDataSource(source,mime);
}

sp<IMemory> RkRetriever::getFrameAtTime(int64_t timeUs, int option, int colorFormat, bool metaOnly)
{
    return  mMediaRetriever->getFrameAtTime(timeUs, option, colorFormat, metaOnly);
}

sp<IMemory> RkRetriever::getImageAtIndex(int index, int colorFormat, bool metaOnly, bool thumbnail)
{
    return mMediaRetriever->getImageAtIndex(index,colorFormat,metaOnly,thumbnail);
}

sp<IMemory> RkRetriever::getImageRectAtIndex(int index, int colorFormat, int left, int top, int right, int bottom)
{
    return mMediaRetriever->getImageRectAtIndex(index,colorFormat,left,top,right,bottom);
}

status_t RkRetriever::getFrameAtIndex(std::vector<sp<IMemory> >* frames,
                                    int frameIndex, int numFrames, int colorFormat, bool metaOnly)
{
    return  mMediaRetriever->getFrameAtIndex(frames,frameIndex,numFrames,colorFormat,metaOnly);
}

MediaAlbumArt* RkRetriever::extractAlbumArt()
{
    return mMediaRetriever->extractAlbumArt();
}

const char* RkRetriever::extractMetadata(int keyCode)
{
    return mMediaRetriever->extractMetadata(keyCode);
}

}  // namespace android
