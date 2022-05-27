#ifndef CG_LAB1_CAMERA_H
#define CG_LAB1_CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    Camera(int windowWidth, int windowHeight);

    Camera(int windowWidth, int windowHeight, const glm::vec3& pos,
        const glm::vec3& target, const glm::vec3& up);

    const glm::vec3& getPos() const { return mPos; }

    const glm::vec3& getTarget() const { return mTarget; }

    const glm::vec3& getUp() const { return mUp; }

    bool onKeyPressed(int key);

    void onMouse(int x, int y);

    void onRender();

private:
    void init();

    void update();

    glm::vec3 mPos;     // ������� ������
    glm::vec3 mTarget;  // ����������� ������
    glm::vec3 mUp;      // "�����" ������

    int mWindowWidth;   // ������ ������
    int mWindowHeight;  // ������ ������

    float mAngleH;  // �������������� ����
    float mAngleV;  // ������������ ����

    // ����������, ������������, ��� ������ ��������� �� ����� �� ����
    // ������
    bool mOnUpperEdge;
    bool mOnLowerEdge;
    bool mOnLeftEdge;
    bool mOnRightEdge;

    glm::ivec2 mMousePos;  // ������� ����
};

#endif  // CG_LAB1_CAMERA_H