#include "play_state.h"
#include "fileManager.h"

namespace Play {
    //카메라 관련 선언
    Camera camera;
    int cType;                              //카메라 타입(2d뷰 / 3d뷰)


    //땅
    std::vector<Cube*> map;      //cube* 에서 cube로 바꿨을때 실행되는지 확인하기

    // 파티클
    std::vector<Particle*> particle;

    //TODO: 적 생성 코드 다른곳으로옮기는게 이쁠지도
    std::vector<Enemy*> enemyVec;

    // TODO:: 얘도
    std::vector<Item*> item;


    //마리오
    Mario mario;

    //허드
    Hud hud;

    //function - 정의
    GLvoid enter() {
        InitValue();
        InitBuffer();
    }

    GLvoid exit() {
        std::cout << "exit - play" << std::endl;
        map.clear();

        //DelBuffer();
        //DelValue();
    }

    GLvoid pause() {
        std::cout << "pause - play" << std::endl;
    }

    GLvoid resume() {
        std::cout << "resume - play" << std::endl;
        cType = 1 - cType;
        if (cType == D3_VIEW) {
            camera.cameraPos = GetMarioPos();
            camera.cameraDirection = glm::vec3(1.0f, 0.0f, 0.0f);
            camera.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        }
        else {
            camera.cameraPos = GetMarioPos();
            camera.cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
            camera.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        }
    }

    GLvoid handle_events() {

    }

    GLvoid update() {
        mario.update();

        for (int i = 0; i < map.size(); i++) {
            map[i]->update();
            if (map[i]->isCanDelete) {
                delete map[i];
                map.erase(map.begin() + i);
            }
        }

        for (int i = 0; i < enemyVec.size(); i++) {
            enemyVec[i]->update();
            for (auto m : map) {
                if (m->trans.y > 0 and m->trans.y < 1.5 and CheckAABB_2D(*enemyVec[i], *m)) {
                    enemyVec[i]->collision_handling(m);
                }
            }
            if (enemyVec[i]->isCanDelete) {
                delete enemyVec[i];
                enemyVec.erase(enemyVec.begin() + i);
            }
        }
        for (int i = 0; i < item.size(); i++) {
            item[i]->update();
            for (auto m : map) {
                if (CheckAABB_2D(*item[i], *m)) {
                    item[i]->collision_handling(m);
                }
            }
            if (item[i]->isCanDelete) {
                delete item[i];
                item.erase(item.begin() + i);
            }
        }
        for (int i = 0; i < particle.size(); i++) {
            particle[i]->update();
            if (particle[i]->isCanDelete) {
                delete particle[i];
                particle.erase(particle.begin() + i);
            }
        }

        camera.update(GetMarioPos(), cType);
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

    GLvoid drawObject() {
        for (auto m : map)
            m->draw();
        for (auto v : enemyVec)
            v->draw();
        for (auto i : item)
            i->draw(cType);
        for (auto p : particle)
            p->draw();
        mario.draw(cType);
        hud.Draw(mario.GetHp(), mario.GetCoinNum());
    }

    GLvoid draw() {
        SetTransformationMatrix();
        drawObject();
    }

    GLvoid key_down(unsigned char key, int x, int y) {
        if (key == '-') printf("줄 확인을 위한 테스트\n"); //TODO: 나중에 지우기
        std::cout << key << std::endl;
        if (key == 'r' || key == 'R') {
            mario.MarioChangeState(0);
            mario.StateEnter_3D();
            push_state(CHANGEDIMENSION);
        }
        else
            mario.handle_events(GLUT_KEY_DOWN, key);
    }

    GLvoid key_up(unsigned char key, int x, int y) {
        mario.handle_events(GLUT_KEY_UP, key);
    }

    GLvoid InitBuffer() {
        loadStage1(map);
        mario.InitBuffer();
        hud.InitBuffer();
        {
            Enemy* temp0 = new Goomba(glm::vec3(1.0, 1.0, 1.0), glm::vec3(30.0, 0.5, 3.0), glm::vec3(0.0, 0.0, 0.0));
            Enemy* temp1 = new Goomba(glm::vec3(1.0, 1.0, 1.0), glm::vec3(65.0, 0.5, 0.0), glm::vec3(0.0, 0.0, 0.0));
            Enemy* temp2 = new Goomba(glm::vec3(1.0, 1.0, 1.0), glm::vec3(98.0, 0.5, -3.0), glm::vec3(0.0, 0.0, 0.0));
            enemyVec.push_back(temp0);
            enemyVec.push_back(temp1);
            enemyVec.push_back(temp2);
        }
        {
            for (int i = 0; i < 6; i++)
            {
                Item* temp = new Coin(glm::vec3(0.8, 0.8, 0.8), glm::vec3(104.5 + i * 2, 0.5, -3.0), glm::vec3(0.0, 0.0, 0.0));
                item.push_back(temp);
            }
        }
        {
            GLfloat i = 0;
            while (4.1667 * i < 127) {
                Cube* backWall = new PictureWall(glm::vec3(4.1667, 10, 1.0), glm::vec3(i * 4.1667 + (4.1667 / 2), 5, -6.5), glm::vec3(0.0, 0.0, 0.0), i);
                map.push_back(backWall);
                i += 1.0;
            }
        }

    }

    GLvoid InitValue() {
        {   //카메라 값 초기화
           //camera.cameraPos = glm::vec3(0.0f, 12.0f, 50.0f);
           //camera.cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
           //camera.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

            camera.cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
            camera.cameraDirection = glm::vec3(1.0f, 0.0f, 0.0f);
            camera.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


            cType = D3_VIEW;
        }

        {//마리오 관련
            mario.Init();
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
                projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 500.0f);
                projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.0));
                //projection = glm::perspective(glm::radians(45.0f), GLfloat(WIDTH)/HEIGHT, 0.1f, (GLfloat)CameraViewSize);
                //projection = glm::translate(projection, glm::vec3(0.0, 0.0, -3.0));
            }
            else {                  //2D 뷰
                projection = glm::ortho(-CameraViewSize / 40, CameraViewSize / 40, -CameraViewSize / 40, CameraViewSize / 40, 0.1f, CameraViewSize);
                //projection = glm::ortho(-CameraViewSize/20,CameraViewSize/20, -CameraViewSize/20, CameraViewSize/20, 0.1f, CameraViewSize);
            }
            unsigned int projectLoc = glGetUniformLocation(Gets_program_texture(), "projection");
            glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
        }

        //unsigned int viewPosLocation = glGetUniformLocation(Gets_program(), "viewPos");
        //glUniform3f(viewPosLocation, camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);

    }

    Camera getCamera() { return camera; }
    GLuint getcType() { return cType; }
    std::vector<Cube*> GetGround() { return map; }
    std::vector<Enemy*> GetEnemy() { return enemyVec; }
    std::vector<Item*> GetItem() { return item; }
    std::vector<Item*> &GetItemToAdd() { return item; }
    std::vector<Particle*>& GetParticleToAdd() { return particle; }

    glm::vec3 GetMarioPos() {
        return mario.trans;
    }
}


