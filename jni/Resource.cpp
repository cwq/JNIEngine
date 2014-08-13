#include "Resource.h"

Resource::Resource(AAssetManager* assetManager, const char* pPath)
	: mPath(pPath),
	mAssetManager(assetManager),
	mAsset(NULL) {

}

const char* Resource::getPath() {
	return mPath;
}

int Resource::open() {
	mAsset = AAssetManager_open(mAssetManager, mPath, AASSET_MODE_UNKNOWN);
	return (mAsset != NULL) ? 1 : 0;
}

void Resource::close() {
	if (mAsset != NULL) {
		AAsset_close(mAsset);
		mAsset = NULL;
	}
}

int Resource::read(void* pBuffer, size_t pCount) {
	int32_t lReadCount = AAsset_read(mAsset, pBuffer, pCount);
	return (lReadCount == pCount) ? 1 : 0;
}