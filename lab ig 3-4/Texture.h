#ifndef CG_LAB1_TEXTURE_H
#define CG_LAB1_TEXTURE_H

#include <GL/glew.h>
#include <ImageMagick-7/Magick++.h>
#include <ImageMagick-7/Magick++/Blob.h>
#include <ImageMagick-7/Magick++/Exception.h>

#include <string>

class Texture {
public:
    Texture(GLenum textureTarget, std::string fileName);
    // ������� �������� ��������
    bool load();
    // ������� �������� ��������
    void bind(GLenum textureUnit) const;

private:
    std::string mFileName;   // ��� �����
    GLenum mTextureTarget;   // ���� �������� ��������
    GLuint mTextureObj;      // ������ ��������
    Magick::Image* mPImage;  // �����������
    Magick::Blob mBlob;      // ������ �����������
};

#endif  // CG_LAB1_TEXTURE_H