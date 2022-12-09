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

// TODO: �ϴ� playstate���� �� ����
#include "goomba.h"

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
    GLvoid drawObject();
    GLvoid draw();
    GLvoid key_down(unsigned char, int, int);
    GLvoid key_up(unsigned char, int, int);
    GLvoid InitBuffer();
    GLvoid InitValue();                        //�� �ʱ�ȭ �Լ�
    GLvoid SetTransformationMatrix();            //model ��ȯ, ī�޶� ��ȯ, ���׺�ȯ, ������ȯ���� ����Ʈ�� �־��ִ� �Լ�

    Camera getCamera();
    GLuint getcType();

    std::vector<Cube*> GetGround();
    glm::vec3 GetMarioPos();

}

#endif