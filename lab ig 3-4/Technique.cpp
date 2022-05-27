#include "Technique.h"

#include <iostream>

Technique::Technique() : mShaderProg(0) {}

Technique::~Technique() {
    for (auto obj : mShaderObjList) glDeleteShader(obj);

    if (mShaderProg != 0) {
        glDeleteProgram(mShaderProg);
        mShaderProg = 0;
    }
}

bool Technique::init() {
    mShaderProg = glCreateProgram();

    if (mShaderProg == 0) {
        std::cerr << "Error creating shader program" << std::endl;
        return false;
    }

    return true;
}

void Technique::enable() const { glUseProgram(mShaderProg); }

bool Technique::addShader(GLenum shaderType, const std::string& shaderText) {
    GLuint shaderObj = glCreateShader(shaderType);

    if (shaderObj == 0) {
        std::cerr << "Error: creating shader type " << shaderType << std::endl;
        return false;
    }

    mShaderObjList.push_back(shaderObj);

    // ��������� ��� ������� � �������
    const GLchar* p[1];
    p[0] = shaderText.c_str();

    // ������ ���� ����� ��������
    GLint lengths[1];
    lengths[0] = static_cast<GLint>(shaderText.length());

    // ����� ��������� �������
    glShaderSource(shaderObj, 1, p, lengths);
    // ����������� ������
    glCompileShader(shaderObj);

    // ���������, ��� ������ ������� ���������������
    GLint success;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shaderObj, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Error compiling shader type " << shaderType << ": '"
            << infoLog << "'" << std::endl;
        return false;
    }

    // ��������� ������ � ���������
    glAttachShader(mShaderProg, shaderObj);

    return true;
}

bool Technique::finalize() {
    GLint success = 0;
    GLchar errorLog[1024] = { 0 };

    // ������� ���������
    glLinkProgram(mShaderProg);
    // ���������, ��� �������� ������ �������
    glGetProgramiv(mShaderProg, GL_LINK_STATUS, &success);
    if (success == 0) {
        glGetProgramInfoLog(mShaderProg, sizeof(errorLog), nullptr, errorLog);
        std::cerr << "Error linking shader program: '" << errorLog << "'"
            << std::endl;
        return false;
    }

    // ���������� ���������
    glValidateProgram(mShaderProg);
    // ���������, ��� ��������� ������ �������
    glGetProgramiv(mShaderProg, GL_VALIDATE_STATUS, &success);
    if (success == 0) {
        glGetProgramInfoLog(mShaderProg, sizeof(errorLog), nullptr, errorLog);
        std::cerr << "Invalid shader program: '" << errorLog << "'"
            << std::endl;
        return false;
    }

    for (auto obj : mShaderObjList) glDeleteShader(obj);

    return true;
}

GLint Technique::getUniformLocation(const std::string& uniformName) const {
    GLint location = glGetUniformLocation(mShaderProg, uniformName.c_str());

    if (location == 0xFFFFFFFF) {
        std::cerr << "Warning! Unable to get the location of uniform '"
            << uniformName << "'" << std::endl;
    }

    return location;
}