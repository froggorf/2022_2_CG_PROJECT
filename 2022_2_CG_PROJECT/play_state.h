#ifndef __PLAY_STATE_H__
#define __PLAY_STATE_H__

#include "stdafx.h"
#include "key_events.h"
#include "MainGame.h"
#include "camera.h"
#include "cube.h"
#include "mario_character.h"
#include "check_collision.h"
#define CameraViewSize 300

enum CameraType { D3_VIEW = 0, D2_VIEW = 1 };
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
    GLvoid draw();

    GLvoid InitBuffer();
    GLvoid InitValue();                        //값 초기화 함수
    GLvoid SetTransformationMatrix();            //model 변환, 카메라 변환, 뷰잉변환, 투영변환등의 디폴트값 넣어주는 함수

    std::vector<Cube*>& GetGround();

  



}

#endif