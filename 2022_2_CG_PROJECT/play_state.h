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
#include "select_stage_state.h"
#include "hud.h"
#include "background.h"

#include "particle.h"
#include "brickParticle.h"

#include "pictureWall.h"


#include "enemy.h"
#include "goomba.h"
#include "squiglet.h"
#include "item.h"
#include "mushroom.h"

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

    GLvoid goSelectState();
    Camera getCamera();
    GLuint getcType();

    std::vector<Cube*> GetGround();
    std::vector<Enemy*> GetEnemy();
    std::vector<Item*> GetItem();
    std::vector<Item*>& GetItemToAdd();
    std::vector<Particle*>& GetParticleToAdd();

    GLvoid SetMarioCoin(GLuint num);
    glm::vec3 GetMarioPos();

}

#endif