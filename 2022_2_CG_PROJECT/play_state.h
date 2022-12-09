#ifndef __PLAY_STATE_H__
#define __PLAY_STATE_H__

#include "stdafx.h"
#include "key_events.h"
#include "MainGame.h"
#include "camera.h"
#include "cube.h"
#include "mario_character.h"
#include "check_collision.h"
#include "ground.h"
#include "changeDimension_state.h"

// TODO: 일단 playstate에서 적 생성
#include "goomba.h"

namespace Play {
    //define - 선언

   //enum - 선언 및 정의 
   
    //function - 선언
    GLvoid enter();
    GLvoid exit();
    GLvoid pause();
    GLvoid resume();
    GLvoid handle_events();
    GLvoid update();
    GLvoid drawObject();
    GLvoid draw();
    GLvoid key_down(unsigned char, int, int);
    GLvoid key_up(unsigned char, int, int);
    GLvoid InitBuffer();
    GLvoid InitValue();                        //값 초기화 함수
    GLvoid SetTransformationMatrix();            //model 변환, 카메라 변환, 뷰잉변환, 투영변환등의 디폴트값 넣어주는 함수

    Camera getCamera();
    GLuint getcType();

    std::vector<Cube*> GetGround();
    glm::vec3 GetMarioPos();

}

#endif