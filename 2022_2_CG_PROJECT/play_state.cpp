#include "play_state.h"

namespace Play {
    //ī�޶� ���� ����
    Camera camera[2];
    int cType;                              //ī�޶� Ÿ��(2d�� / 3d��)

    //��ü(ť��) ���� �ӽ� ����
    Cube cube;
    Cube test_cube;

    //��
    std::vector<Cube> ground;      //cube* ���� cube�� �ٲ����� ����Ǵ��� Ȯ���ϱ�
    
    //�ν����� ��
    
    //ĭ���� ��
    
    //�ܴ��� ��

    //������
    Mario mario;

    //function - ����
    GLvoid enter() {
        InitValue();
        InitBuffer();
    }

    GLvoid exit() {
        std::cout << "exit - play" << std::endl;
        ground.clear();
        
        //DelBuffer();
        //DelValue();
    }

    GLvoid pause() {
        std::cout << "pause - play" << std::endl;
    }

    GLvoid resume() {
        std::cout << "resume - play" << std::endl;
    }

    GLvoid handle_events() {
        
    }

    GLvoid update() {
        mario.update();
        

        
    }

    GLvoid draw() {
        SetTransformationMatrix();
       

        for (int i = 0; i < ground.size(); ++i) {
            ground[i].draw();
        }
        mario.draw();

        
    }

    GLvoid InitBuffer() {
        //cube.InitBuffer();
        //test_cube.InitBuffer();
        
        for (int i = 0; i < ground.size(); ++i) {
            ground[i].InitBuffer();
        }
        mario.InitBuffer();
    }

    GLvoid InitValue() {
        {   //ī�޶� �� �ʱ�ȭ
            camera[D3_VIEW].cameraPos = glm::vec3(0.0f, 15.0f, 50.0f);
            camera[D3_VIEW].cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
            camera[D3_VIEW].cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

            camera[D2_VIEW].cameraPos;
            camera[D2_VIEW].cameraDirection;
            camera[D2_VIEW].cameraUp;

            cType = D3_VIEW;
        }

        {   //ť�� ����
            {
                cube.init();
                cube.scale = glm::vec3(20.0f, 20.0f, 20.0f);
                cube.color = glm::vec3(0.0f, 1.0f, 0.0f);

                test_cube.init();
                test_cube.scale = glm::vec3(10.0f, 10.0f, 10.0f);
                test_cube.color = glm::vec3(0.0f, 0.0f, 1.0f);

                //ground.push_back(cube);
                //ground.push_back(test_cube);

            }
        }

        {
            Cube temp;
            temp.init(); 
            temp.scale = glm::vec3(10.0f, 10.0f, 10.0f);
            temp.color = glm::vec3(0.0f, 0.0f, 1.0f);
           
            ground.push_back(temp);

            Cube t;
            t.init();
            t.scale = glm::vec3(20.0f, 5.0f, 20.0f);
            t.color = glm::vec3(0.0f, 1.0f, 0.0f);
            ground.push_back(t);
        }

        {//������ ����
            mario.init();
        }
    }

    GLvoid SetTransformationMatrix() {
        {//model ��ȯ
            glm::mat4 TR = glm::mat4(1.0f);
            unsigned int modelLocation = glGetUniformLocation(Gets_program(), "model");
            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
        }

        {//ī�޶� ��ȯ
            glm::mat4 view = glm::mat4(1.0f);
            view = glm::lookAt(camera[cType].cameraPos, camera[cType].cameraPos + camera[cType].cameraDirection, camera[cType].cameraUp);
            unsigned int viewLocation = glGetUniformLocation(Gets_program(), "view");
            glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
        }

        {//���� ��ȯ
            glm::mat4 projection = glm::mat4(1.0f);
            if (cType == D3_VIEW) {      //3D ��
                projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, (GLfloat)CameraViewSize);
                //projection = glm::translate(projection, glm::vec3(0.0, 0.0, -3.0));
            }
            else {                  //2D ��
                GLfloat halfsize = CameraViewSize / 2;
                projection = glm::ortho(-halfsize, halfsize, -halfsize, halfsize, halfsize, halfsize);
            }


            unsigned int projectLoc = glGetUniformLocation(Gets_program(), "projection");
            glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
        }

        unsigned int viewPosLocation = glGetUniformLocation(Gets_program(), "viewPos");
        glUniform3f(viewPosLocation, camera[cType].cameraPos.x, camera[cType].cameraPos.y, camera[cType].cameraPos.z);

    }

    std::vector<Cube>& GetGround() {
        return ground;
    }
}



