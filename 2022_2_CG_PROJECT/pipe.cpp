#include "pipe.h"

glm::vec2 pipe_text_pos[] = {
   glm::vec2(0.5f,1.0f),glm::vec2(0.5f,0.0f),glm::vec2(1.0f,0.0f),
   glm::vec2(0.5f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),

   glm::vec2(0.5f,1.0f),glm::vec2(0.5f,0.0f),glm::vec2(1.0f,0.0f),
   glm::vec2(0.5f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),

   glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(0.5f,0.0f),
   glm::vec2(0.0f,1.0f),glm::vec2(0.5f,0.0f),glm::vec2(0.5f,1.0f),

   glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(0.5f,0.0f),
   glm::vec2(0.0f,1.0f),glm::vec2(0.5f,0.0f),glm::vec2(0.5f,1.0f),

   glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(0.5f,0.0f),
   glm::vec2(0.0f,1.0f),glm::vec2(0.5f,0.0f),glm::vec2(0.5f,1.0f),

   glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(0.5f,0.0f),
   glm::vec2(0.0f,1.0f),glm::vec2(0.5f,0.0f),glm::vec2(0.5f,1.0f),
};

glm::vec3 test_pipe_vertices[] = {
   glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,0.5,0.5),      // 0, 1, 2      ????
   glm::vec3(-0.5,0.5,-0.5),glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,0.5,-0.5),      // 0, 2, 3

   glm::vec3(-0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,0.5),      // 7, 6, 5      ?Ʒ???
   glm::vec3(-0.5,-0.5,-0.5), glm::vec3(0.5,-0.5,0.5),glm::vec3(-0.5,-0.5,0.5),   // 7, 5, 4

   glm::vec3(-0.5,0.5,0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(0.5,-0.5,0.5),      // 1, 4, 5      ?? ??
   glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,0.5,0.5),         // 1, 5, 2

   glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,-0.5,-0.5),      // 2, 5, 6
   glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,-0.5), glm::vec3(0.5,0.5,-0.5),      // 2, 6, 3

   glm::vec3(0.5,0.5,-0.5), glm::vec3(0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),   // 3, 6, 7
   glm::vec3(0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,0.5,-0.5),      // 3, 7, 0

   glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,0.5),   // 0, 7, 4
   glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(-0.5,0.5,0.5),      // 0, 4, 1
};

GLuint pipe_texture = -1;
GLuint bigpipe_texture = -1;

Pipe::Pipe() {
    InitBuffer();
    this->trans = glm::vec3(0.0, 0.0, 0.0);
    this->rot = glm::vec3(0.0, 0.0, 0.0);
    this->scale = glm::vec3(1.0, 1.0, 1.0);
};
Pipe::Pipe(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate) {
    InitBuffer();
    this->trans = trans;
    this->scale = scale;
    this->rot = rotate;
};
Pipe::~Pipe() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(3, VBO);
};


GLvoid Pipe::Init() {

}
GLvoid Pipe::InitBuffer() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(3, VBO);
    if (pipe_texture == -1) {
        //?ӽ? ?ڵ??? ???߿? ?̹??? ?????ؾ???
        LoadTexture(pipe_texture, "resource/Map/pipe.png");
        LoadTexture(bigpipe_texture, "resource/Map/bigpipe.png");
    }
}

GLvoid Pipe::draw() {
    glUseProgram(Gets_program_texture());
    glm::mat4 TR = glm::mat4(1.0f);
    glm::mat4 T = glm::mat4(1.0f);
    T = glm::translate(T, glm::vec3(trans.x, trans.y, trans.z));
    glm::mat4 S = glm::mat4(1.0f);
    S = glm::scale(S, glm::vec3(scale.x, scale.y, scale.z));
    TR = T * S * TR;

    unsigned int modelLocation = glGetUniformLocation(Gets_program_texture(), "model");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);

    glBindVertexArray(VAO);

    //???? o
    glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(test_pipe_vertices), test_pipe_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXTURE]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pipe_text_pos), pipe_text_pos, GL_STATIC_DRAW);
    glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(5);

    int tLocation = glGetUniformLocation(Gets_program_texture(), "outTexture"); //--- outTexture1 ?????? ???÷??? ??ġ?? ??????
    if (scale.y < 2.0) {
        glActiveTexture(pipe_texture);
        glBindTexture(GL_TEXTURE_2D, pipe_texture);
        glUniform1i(tLocation, 0);
    }
    else {
        glActiveTexture(bigpipe_texture);
        glBindTexture(GL_TEXTURE_2D, bigpipe_texture);
        glUniform1i(tLocation, 0);
    }

    glDrawArrays(GL_TRIANGLES, 0, sizeof(test_pipe_vertices) / sizeof(test_pipe_vertices[0]));
}