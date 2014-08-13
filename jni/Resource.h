#ifndef RESOURCE_H
#define RESOURCE_H

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

class Resource
{
public:
	Resource(AAssetManager* assetManager, const char* pPath);
	const char* getPath();
	int open();
	void close();
	int read(void* pBuffer, size_t pCount);

private:
	const char* mPath;
	AAssetManager* mAssetManager;
	AAsset* mAsset;
};

#endif // !RESOURCE_H
