#include "cube.h"


glm::vec3 cube_vertices[36] = {
    glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,0.5,0.5),
    glm::vec3(-0.5,0.5,-0.5),glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,0.5,-0.5),
    glm::vec3(-0.5,0.5,0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(0.5,-0.5,0.5),
    glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,0.5,0.5),
    glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,-0.5,-0.5),
    glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,-0.5), glm::vec3(0.5,0.5,-0.5),
    glm::vec3(0.5,0.5,-0.5), glm::vec3(0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),
    glm::vec3(0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,0.5,-0.5),
    glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,0.5),
    glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(-0.5,0.5,0.5),
    glm::vec3(-0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,0.5),
    glm::vec3(-0.5,-0.5,-0.5), glm::vec3(0.5,-0.5,0.5),glm::vec3(-0.5,-0.5,0.5)
};
glm::vec3 cube_normal[36] = {
     glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
     glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
     glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
     glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
     glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
     glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
     glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f),
     glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f),
     glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
     glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
     glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),
     glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),
};

glm::vec2 cube_texture[36] = {
    //012 023 -- 윗면
    glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
    glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),


    glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
    glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),


    glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
    glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),


    glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
    glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),


    glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
    glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),


    glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
    glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),
};

Cube::Cube() {}

Cube::Cube(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate) {
    this->trans = trans;
    this->rot = rotate;
    this->scale = scale;
};

GLvoid Cube::init() {
    trans = glm::vec3(0.0f, 0.0f, 0.0f);
    rot = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    color = glm::vec3(1.0f, 1.0f, 1.0f);
}

glm::vec3* GetCubeVertices() {
    return cube_vertices;
}
glm::vec3* GetCubeNormal() {
    return cube_normal;
}
//
//GLvoid Cube::draw() {
//    //model 변환
//    glm::mat4 TR = glm::mat4(1.0f);
//
//    glm::mat4 T = glm::mat4(1.0f);
//    T = glm::translate(T, glm::vec3(trans.x, trans.y, trans.z));
//
//    glm::mat4 S = glm::mat4(1.0f);
//    S = glm::scale(S, glm::vec3(scale.x, scale.y, scale.z));
//
//    glm::mat4 Rot = glm::mat4(1.0f);
//    Rot = glm::rotate(Rot, glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
//    Rot = glm::rotate(Rot, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
//    Rot = glm::rotate(Rot, glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
//    TR = T * Rot * S * TR;
//
//    unsigned int modelLocation = glGetUniformLocation(Gets_program(), "model");
//    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//
//    glBindVertexArray(VAO);
//
//    //조명 o
//    glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO[NORMAL]);   //노말벡터에 관련된 값이오나 임시로 확인하기 위해 사용
//    glm::vec3 norm[36];
//    for (int i = 0; i < 36; ++i) {
//        norm[i] = glm::mat3(glm::transpose(glm::inverse(TR))) * cube_normal[i];
//    }
//
//    glBufferData(GL_ARRAY_BUFFER, sizeof(norm), norm, GL_STATIC_DRAW);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXTURE]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_texture), cube_texture, GL_STATIC_DRAW);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(2);
//
//    int tLocation = glGetUniformLocation(Gets_program(), "outTexture"); //--- outTexture1 유니폼 샘플러의 위치를 가져옴
//    glActiveTexture(box_texture);
//    glBindTexture(GL_TEXTURE_2D, box_texture);
//    glUniform1i(tLocation, 0);
//
//    //int ambientLightLocation = glGetUniformLocation(Gets_program(), "ambientLight");
//    //glUniform3f(ambientLightLocation, 0.35f, 0.35f, 0.35f);
//    //int lightPosLocation = glGetUniformLocation(Gets_program(), "lightPos");
//    //glUniform3f(lightPosLocation, 0.0f, 50.0f, 0.0f);
//    //int lightColorLocation = glGetUniformLocation(Gets_program(), "lightColor");
//    //glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);
//    //int objColorLocation = glGetUniformLocation(Gets_program(), "objectColor");
//    //glUniform3f(objColorLocation, color.x, color.y, color.z);
//    
//
//    glDrawArrays(GL_TRIANGLES, 0, sizeof(cube_vertices) / sizeof(cube_vertices[0]));
//}


GLboolean Cube::CubeCollide(Cube other) {
    //https://handhp1.tistory.com/6 참고
    GLfloat c[3][3];
    GLfloat absC[3][3];
    GLfloat d[3];
    GLfloat r0, r1, r;
    int i;
    const double cutoff = 0.999999;
    GLboolean existsParallelPair = false;
    GLboolean obbCollide = false;
    glm::vec3 diff = glm::vec3(trans - other.trans);

    glm::vec3 axis[3] = {
       glm::vec3(1.0f,0.0f,0.0f),
       glm::vec3(0.0f,1.0f,0.0f),
       glm::vec3(0.0f,0.0f,1.0f)
    };
    glm::vec3 other_axis[3] = {
       glm::vec3(1.0f,0.0f,0.0f),
       glm::vec3(0.0f,1.0f,0.0f),
       glm::vec3(0.0f,0.0f,1.0f)
    };
    glm::vec3 axisLen = { scale.x / 2,scale.y / 2,scale.z / 2 };
    glm::vec3 other_axisLen = { other.scale.x / 2,other.scale.y / 2,other.scale.z / 2 };

    glm::mat4 my_r = glm::mat4(1.0f);
    my_r = glm::rotate(my_r, glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
    my_r = glm::rotate(my_r, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
    my_r = glm::rotate(my_r, glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
    for (int i = 0; i < 3; ++i) {
        axis[i] = glm::vec3(my_r * glm::vec4(axis[i], 1.0f));
    }
    glm::mat4 other_r = glm::mat4(1.0f);
    other_r = glm::rotate(other_r, glm::radians(other.rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
    other_r = glm::rotate(other_r, glm::radians(other.rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
    other_r = glm::rotate(other_r, glm::radians(other.rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
    for (int i = 0; i < 3; ++i) {
        other_axis[i] = glm::vec3(other_r * glm::vec4(other_axis[i], 1.0f));
    }

    for (int i = 0; i < 3; ++i) {
        c[0][i] = glm::dot(axis[0], other_axis[i]);
        absC[0][i] = abs(c[0][i]);
        if (absC[0][i] > cutoff)
            existsParallelPair = true;
    }

    d[0] = glm::dot(diff, axis[0]);
    r = abs(d[0]);
    r0 = axisLen.x;
    r1 = other_axisLen[0] * absC[0][0] + other_axisLen[1] * absC[0][1] + other_axisLen[2] * absC[0][2];
    if (r > r0 + r1) {
        obbCollide = false;
        return false;
    }

    for (i = 0; i < 3; ++i) {
        c[1][i] = glm::dot(axis[1], other_axis[i]);
        absC[1][i] = abs(c[1][i]);
        if (absC[1][i] > cutoff)
            existsParallelPair = true;
    }
    d[1] = glm::dot(diff, axis[0]);
    r = abs(d[1]);
    r0 = axisLen[1];
    r1 = other_axisLen[0] * absC[1][0] + other_axisLen[1] * absC[1][1] + other_axisLen[2] * absC[1][2];
    if (r > r0 + r1) {
        obbCollide = false;
        return false;
    }

    for (int i = 0; i < 3; ++i) {
        c[2][i] = glm::dot(axis[2], other_axis[i]);
        absC[2][i] = abs(c[2][i]);
        if (absC[2][i] > cutoff)
            existsParallelPair = true;
    }

    d[2] = glm::dot(diff, axis[2]);
    r = abs(d[2]);
    r0 = axisLen[2];
    r1 = other_axisLen[0] * absC[2][0] + other_axisLen[1] * absC[2][1] + other_axisLen[2] * absC[2][2];
    if (r > r0 + r1) {
        obbCollide = false;
        return false;
    }
    r = abs(glm::dot(diff, other_axis[0]));
    r0 = axisLen[0] * absC[0][0] + axisLen[1] * absC[1][0] + axisLen[2] * absC[2][0];
    r1 = other_axisLen[0];
    if (r > r0 + r1) {
        obbCollide = false;
        return false;
    }
    r = abs(glm::dot(diff, other_axis[1]));
    r0 = axisLen[0] * absC[0][1] + axisLen[1] * absC[1][1] + axisLen[2] * absC[2][1];

    r1 = other_axisLen[1];
    if (r > r0 + r1) {
        obbCollide = false;
        return false;
    }

    r = abs(glm::dot(diff, other_axis[2]));
    r0 = axisLen[0] * absC[0][2] + axisLen[1] * absC[1][2] + axisLen[2] * absC[2][2];
    r1 = other_axisLen[2];
    if (r > r0 + r1) {
        obbCollide = false;
        return false;
    }

    if (existsParallelPair) {
        obbCollide = true;
        return true;
    }

    r = abs(d[2] * c[1][0] - d[1] * c[2][0]);
    r0 = axisLen[1] * absC[2][0] + axisLen[2] * absC[1][0];
    r1 = other_axisLen[1] * absC[0][2] + other_axisLen[2] * absC[0][1];
    if (r > r0 + r1) {
        obbCollide = false;
        return false;
    }

    r = abs(d[2] * c[1][1] - d[1] * c[2][1]);
    r0 = axisLen[1] * absC[2][1] + axisLen[2] * absC[1][1];
    r1 = other_axisLen[0] * absC[0][2] + other_axisLen[2] * absC[0][0];
    if (r > r0 + r1) {
        obbCollide = false;
        return false;
    }
    r = abs(d[2] * c[1][2] - d[1] * c[2][2]);
    r0 = axisLen[1] * absC[2][2] + axisLen[2] * absC[1][2];
    r1 = other_axisLen[0] * absC[0][1] + other_axisLen[1] * absC[0][0];
    if (r > r0 + r1) {
        obbCollide = false;
        return false;
    }

    r = abs(d[0] * c[2][0] - d[2] * c[0][0]);
    r0 = axisLen[0] * absC[2][0] + axisLen[2] * absC[0][0];
    r1 = other_axisLen[1] * absC[1][2] + other_axisLen[2] * absC[1][1];
    if (r > r0 + r1) {
        obbCollide = false;
        return false;
    }

    r = abs(d[0] * c[2][1] - d[2] * c[0][1]);
    r0 = axisLen[0] * absC[2][1] + axisLen[2] * absC[0][1];
    r1 = other_axisLen[0] * absC[1][2] + other_axisLen[2] * absC[1][0];
    if (r > r0 + r1) {
        obbCollide = false;
        return false;
    }

    r = abs(d[0] * c[2][2] - d[2] * c[0][2]);
    r0 = axisLen[0] * absC[2][2] + axisLen[2] * absC[0][2];

    r1 = other_axisLen[0] * absC[1][1] + other_axisLen[1] * absC[1][0];

    if (r > r0 + r1) {
        obbCollide = false;
        return false;
    }
    r = abs(d[1] * c[0][0] - d[0] * c[1][0]);

    r0 = axisLen[0] * absC[1][0] + axisLen[1] * absC[0][0];

    r1 = other_axisLen[1] * absC[2][2] + other_axisLen[2] * absC[2][1];

    if (r > r0 + r1) {
        obbCollide = false;
        return false;
    }

    r = abs(d[1] * c[0][1] - d[0] * c[1][1]);

    r0 = axisLen[0] * absC[1][1] + axisLen[1] * absC[0][1];

    r1 = other_axisLen[0] * absC[2][2] + other_axisLen[2] * absC[2][0];

    if (r > r0 + r1)

    {

        obbCollide = false;

        return false;

    }

    r = abs(d[1] * c[0][2] - d[0] * c[1][2]);

    r0 = axisLen[0] * absC[1][2] + axisLen[1] * absC[0][2];

    r1 = other_axisLen[0] * absC[2][1] + other_axisLen[1] * absC[2][0];

    if (r > r0 + r1)

    {

        obbCollide = false;

        return false;

    }
    obbCollide = true;

    return true;


}