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
    //define - ����

   //enum - ���� �� ���� 
   
    //function - ����
    GLvoid enter();
    GLvoid exit();
    GLvoid pause();
    GLvoid resume();
    GLvoid handle_events();
    GLvoid update();
    GLvoid draw();

    GLvoid InitBuffer();
    GLvoid InitValue();                        //�� �ʱ�ȭ �Լ�
    GLvoid SetTransformationMatrix();            //model ��ȯ, ī�޶� ��ȯ, ���׺�ȯ, ������ȯ���� ����Ʈ�� �־��ִ� �Լ�

    std::vector<Cube*>& GetGround();

  



}

#endif