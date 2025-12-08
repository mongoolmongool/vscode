#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

const int WIDTH  = 800;
const int HEIGHT = 600;

// 반지름 인식 조건
const float TARGET_RADIUS    = 100.0f;
const float RADIUS_TOLERANCE =  40.0f;

// 성공까지 필요한 회전 수
const int REQUIRED_ROTATIONS = 5;

float centerX = 0, centerY = 0;
bool  tracking = false;
float lastAngle = 0, accumulated = 0;
int   rotations = 0;
double startTime = 0;

float getAngle(float cx, float cy, float mx, float my) {
    return std::atan2(my - cy, mx - cx);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button != GLFW_MOUSE_BUTTON_LEFT) return;

    if (action == GLFW_PRESS) {
        // 클릭 시작
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        centerX = (float)x;
        centerY = (float)y;

        tracking = true;
        startTime = glfwGetTime();
        accumulated = 0;
        rotations   = 0;
        lastAngle = getAngle(centerX, centerY, x, y);

    } else if (action == GLFW_RELEASE) {
        tracking = false;
    }
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Circle Tracker", nullptr, nullptr);
    if (!window) { glfwTerminate(); return -1; }

    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // 좌표계를 (0,0) top-left로
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        if (tracking && glfwGetTime() - startTime < 10.0) {
            double mx, my;
            glfwGetCursorPos(window, &mx, &my);

            float dx = float(mx - centerX);
            float dy = float(my - centerY);
            float dist = std::sqrt(dx*dx + dy*dy);

            // 목표 반지름 내 움직임만 궤적으로 인식
            if (std::fabs(dist - TARGET_RADIUS) < RADIUS_TOLERANCE) {
                float angle = getAngle(centerX, centerY, mx, my);
                float delta = angle - lastAngle;

                if (delta < -M_PI) delta += 2 * M_PI;
                if (delta >  M_PI) delta -= 2 * M_PI;

                accumulated += delta;
                lastAngle = angle;

                // 완료된 회전 수 계산
                int newRot = static_cast<int>(std::fabs(accumulated) / (2 * M_PI));
                if (newRot > rotations) {
                    rotations = newRot;
                    std::cout << "Rotations: " << rotations << std::endl;
                }

                if (rotations >= REQUIRED_ROTATIONS) {
                    std::cout << "success!" << std::endl;
                    tracking = false;
                }
            }

            // 시각화: 클릭한 중심
            glColor3f(1,0,0);
            glBegin(GL_QUADS);
              glVertex2f(centerX-5, centerY-5);
              glVertex2f(centerX+5, centerY-5);
              glVertex2f(centerX+5, centerY+5);
              glVertex2f(centerX-5, centerY+5);
            glEnd();

            // 시각화: 마우스 위치
            glColor3f(0,1,0);
            glBegin(GL_QUADS);
              glVertex2f(mx-3, my-3);
              glVertex2f(mx+3, my-3);
              glVertex2f(mx+3, my+3);
              glVertex2f(mx-3, my+3);
            glEnd();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}