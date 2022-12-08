#include "play_state.h"
#include "fileManager.h"

namespace Play {
    //카메라 관련 선언
    Camera camera;
    int cType;                              //카메라 타입(2d뷰 / 3d뷰)


    //땅
    std::vector<Ground> ground;      //cube* 에서 cube로 바꿨을때 실행되는지 확인하기
    
    //부숴지는 블럭
    
    //칸막이 블럭
    
    //단단한 블럭

    //마리오
    Mario mario;

    //function - 정의
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
        //camera.update(GetMarioPos());
        if (GetKeyDown()[press5]) {
            glm::mat4 rot = glm::mat4(1.0f);
            rot = glm::rotate(rot, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            camera.cameraPos = rot * glm::vec4(camera.cameraPos, 1.0f);
            camera.cameraDirection = rot * glm::vec4(camera.cameraDirection, 1.0f);
            camera.cameraUp = rot * glm::vec4(camera.cameraUp, 1.0f);
        }
        if (GetKeyDown()[press4]) {
            camera.cameraPos.x -= 0.1;
        }
        if (GetKeyDown()[press6]) {
            camera.cameraPos.x += 0.1;
        }
        if (GetKeyDown()[press8]) {
            camera.cameraPos.y -= 0.1;
        }
        if (GetKeyDown()[press5]) {
            camera.cameraPos.y += 0.1;
        }
        
    }

    GLvoid draw() {
        SetTransformationMatrix();
       
        for (int i = 0; i < ground.size(); ++i) {
            ground[i].draw();
        }
        mario.draw();

        
    }

    GLvoid InitBuffer() {
        //for (int i = 0; i < ground.size(); ++i) {
        //    ground[i].InitBuffer();
        //}
        loadGroundStage1(ground);
        mario.InitBuffer();
    }

    GLvoid InitValue() {
        {   //카메라 값 초기화
            camera.cameraPos = glm::vec3(0.0f, 12.0f, 50.0f);
            camera.cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
            camera.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


            cType = D3_VIEW;
        }

        

        {
            Ground t;
            t.Init();
            t.boundingBox.scale = glm::vec3(1.5 * 12, 10.0f, 200.0f);
           
            ground.push_back(t);

        }

        {//마리오 관련
            mario.init();
        }
    }

    GLvoid SetTransformationMatrix() {
        {//model 변환
            glm::mat4 TR = glm::mat4(1.0f);
            unsigned int modelLocation = glGetUniformLocation(Gets_program_texture(), "model");
            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
        }

        {//카메라 변환
            glm::mat4 view = glm::mat4(1.0f);
            view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraDirection, camera.cameraUp);
            unsigned int viewLocation = glGetUniformLocation(Gets_program_texture(), "view");
            glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
        }

        {//투영 변환
            glm::mat4 projection = glm::mat4(1.0f);
            if (cType == D3_VIEW) {      //3D 뷰
                projection = glm::perspective(glm::radians(45.0f), GLfloat(WIDTH)/HEIGHT, 0.1f, (GLfloat)CameraViewSize);
                //projection = glm::translate(projection, glm::vec3(0.0, 0.0, -3.0));
            }
            else {                  //2D 뷰
                projection = glm::ortho(-CameraViewSize/20,CameraViewSize/20, -CameraViewSize/20, CameraViewSize/20, 0.1f, CameraViewSize);
            }
            unsigned int projectLoc = glGetUniformLocation(Gets_program_texture(), "projection");
            glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
        }

        //unsigned int viewPosLocation = glGetUniformLocation(Gets_program(), "viewPos");
        //glUniform3f(viewPosLocation, camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);

    }

    std::vector<Ground>& GetGround() {
        return ground;
    }

    glm::vec3 GetMarioPos() {
        return mario.boundingBox.trans;
    }
}



