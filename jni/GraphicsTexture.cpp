#include "GraphicsTexture.h"

GraphicsTexture::GraphicsTexture(AAssetManager* assetManager, const char* pPath)
	: mResource(assetManager, pPath),
	mTextureId(0),
	mWidth(0), mHeight(0) {

}

GraphicsTexture::~GraphicsTexture() {

}

int32_t GraphicsTexture::getHeight() {
	return mHeight;
}

int32_t GraphicsTexture::getWidth() {
	return mWidth;
}

void GraphicsTexture::loadWidthHeight() {
	png_byte lHeader[8];
	png_structp lPngPtr = NULL;
	png_infop lInfoPtr = NULL;

	if (mResource.open() != 1) goto ERROR;
	if (mResource.read(lHeader, sizeof(lHeader)) != 1)
		goto ERROR;
	if (png_sig_cmp(lHeader, 0, 8) != 0) goto ERROR;
	lPngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
		NULL, NULL, NULL);
	if (!lPngPtr) goto ERROR;
	lInfoPtr = png_create_info_struct(lPngPtr);
	if (!lInfoPtr) goto ERROR;
	png_set_read_fn(lPngPtr, &mResource, callback_read);
	if (setjmp(png_jmpbuf(lPngPtr))) goto ERROR;
	png_set_sig_bytes(lPngPtr, 8);
	png_read_info(lPngPtr, lInfoPtr);
	png_int_32 lDepth, lColorType;
	png_uint_32 lWidth, lHeight;
	png_get_IHDR(lPngPtr, lInfoPtr, &lWidth, &lHeight,
		&lDepth, &lColorType, NULL, NULL, NULL);
	mWidth = lWidth; mHeight = lHeight;

	ERROR:
		mResource.close();
		if (lPngPtr != NULL) {
			png_infop* lInfoPtrP = lInfoPtr != NULL ? &lInfoPtr : NULL;
			png_destroy_read_struct(&lPngPtr, lInfoPtrP, NULL);
		}
}

uint8_t* GraphicsTexture::loadImage() {
	png_byte lHeader[8];
	png_structp lPngPtr = NULL;
	png_infop lInfoPtr = NULL;
	png_byte* lImageBuffer = NULL;
	png_bytep* lRowPtrs = NULL;
	png_int_32 lRowSize;
	bool lTransparency;

	if (mResource.open() != 1) goto ERROR;
	if (mResource.read(lHeader, sizeof(lHeader)) != 1)
		goto ERROR;
	if (png_sig_cmp(lHeader, 0, 8) != 0) goto ERROR;
	lPngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
		NULL, NULL, NULL);
	if (!lPngPtr) goto ERROR;
	lInfoPtr = png_create_info_struct(lPngPtr);
	if (!lInfoPtr) goto ERROR;
	png_set_read_fn(lPngPtr, &mResource, callback_read);
	if (setjmp(png_jmpbuf(lPngPtr))) goto ERROR;
	png_set_sig_bytes(lPngPtr, 8);
	png_read_info(lPngPtr, lInfoPtr);
	png_int_32 lDepth, lColorType;
	png_uint_32 lWidth, lHeight;
	png_get_IHDR(lPngPtr, lInfoPtr, &lWidth, &lHeight,
		&lDepth, &lColorType, NULL, NULL, NULL);
	mWidth = lWidth; mHeight = lHeight;
	// Creates a full alpha channel if transparency is encoded as
	// an array of palette entries or a single transparent color.
	lTransparency = false;
	if (png_get_valid(lPngPtr, lInfoPtr, PNG_INFO_tRNS)) {
		png_set_tRNS_to_alpha(lPngPtr);
		lTransparency = true;
		goto ERROR;
	}
	// Expands PNG with less than 8bits per channel to 8bits.
	if (lDepth < 8) {
		png_set_packing (lPngPtr);
		// Shrinks PNG with 16bits per color channel down to 8bits.
	} else if (lDepth == 16) {
		png_set_strip_16(lPngPtr);
	}
	// Indicates that image needs conversion to RGBA if needed.
		switch (lColorType) {
		case PNG_COLOR_TYPE_PALETTE:
			png_set_palette_to_rgb(lPngPtr);
			mFormat = lTransparency ? GL_RGBA : GL_RGB;
			break;
		case PNG_COLOR_TYPE_RGB:
			mFormat = lTransparency ? GL_RGBA : GL_RGB;
			break;
		case PNG_COLOR_TYPE_RGBA:
			mFormat = GL_RGBA;
			break;
		case PNG_COLOR_TYPE_GRAY:
			png_set_expand_gray_1_2_4_to_8(lPngPtr);
			mFormat = lTransparency ? GL_LUMINANCE_ALPHA:GL_LUMINANCE;
			break;
		case PNG_COLOR_TYPE_GA:
			png_set_expand_gray_1_2_4_to_8(lPngPtr);
			mFormat = GL_LUMINANCE_ALPHA;
			break;
	}
	png_read_update_info(lPngPtr, lInfoPtr);
	lRowSize = png_get_rowbytes(lPngPtr, lInfoPtr);
	if (lRowSize <= 0) goto ERROR;
	lImageBuffer = new png_byte[lRowSize * lHeight];
	if (!lImageBuffer) goto ERROR;
	lRowPtrs = new png_bytep[lHeight];
	if (!lRowPtrs) goto ERROR;
	for (int32_t i = 0; i < lHeight; ++i) {
		lRowPtrs[lHeight - (i + 1)] = lImageBuffer + i * lRowSize;
	}
	png_read_image(lPngPtr, lRowPtrs);
	mResource.close();
	png_destroy_read_struct(&lPngPtr, &lInfoPtr, NULL);
	delete[] lRowPtrs;
	return lImageBuffer;

ERROR:
/*	Log::error("Error while reading PNG file");*/
	mResource.close();
	delete[] lRowPtrs; delete[] lImageBuffer;
	if (lPngPtr != NULL) {
		png_infop* lInfoPtrP = lInfoPtr != NULL ? &lInfoPtr: NULL;
		png_destroy_read_struct(&lPngPtr, lInfoPtrP, NULL);
	}
	return NULL;
}

void GraphicsTexture::callback_read(png_structp png, png_bytep data, png_size_t size) {
	Resource* lResource = ((Resource*) png_get_io_ptr(png));
	if (lResource->read(data, size) != 1) {
		lResource->close();
		png_error(png, "Error while reading PNG file");
	}
}

int GraphicsTexture::load() {
	uint8_t* lImageBuffer = loadImage();
	if (lImageBuffer == NULL) {
		return 0;
	}
	// Creates a new OpenGL texture.
	GLenum lErrorResult;
	glGenTextures(1, &mTextureId);
	glBindTexture(GL_TEXTURE_2D, mTextureId);
	// Set-up texture properties.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Loads image data into OpenGL.
	glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mWidth, mHeight, 0,
		mFormat, GL_UNSIGNED_BYTE, lImageBuffer);

	delete[] lImageBuffer;

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (glGetError() != GL_NO_ERROR) {
/*		Log::error("Error loading texture into OpenGL.");*/
		unload();
		return 0;
	}
	return 1;
}

void GraphicsTexture::unload() {
	if (mTextureId != 0) {
		glDeleteTextures(1, &mTextureId);
		mTextureId = 0;
	}
	mWidth = 0; mHeight = 0; mFormat = 0;
}

GLuint GraphicsTexture::getTextureId() {
	return mTextureId;
}
