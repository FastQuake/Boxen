#include <glm/gtc/matrix_transform.hpp>
#include "Quad.hpp"
#include "../ResourceManager/ResourceManager.hpp"
using namespace std;

struct QuadVert {
    glm::vec3 position;
    glm::vec2 texCoord;
};

GLuint Quad::vbo = 0;
GLuint Quad::vao = 0;

static QuadVert quadVerts[] = {
    {{-1.0, -1.0, 0.0},
    {0.0, 1.0}
    },
    {{-1.0, 1.0, 0.0},
    {0.0, 0.0}
    },
    {{1.0, 1.0, 0.0},
    {1.0, 0.0}
    },
    {{1.0, -1.0, 0.0},
    {1.0, 1.0}
    }
}; 

Quad::Quad(const string &texture) {
    /* If this is the first time create vbo for cube */
    if(Quad::vbo == 0 || Quad::vao == 0) {
        QuadVert *p = NULL;
        glGenVertexArrays(1, &Quad::vao);
        glBindVertexArray(Quad::vao);
        glGenBuffers(1, &Quad::vbo);
        glBindBuffer(GL_ARRAY_BUFFER, Quad::vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), quadVerts, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                false,
                sizeof(QuadVert),
                &p->position);

        glVertexAttribPointer(
                1,
                2,
                GL_FLOAT,
                false,
                sizeof(QuadVert),
                &p->texCoord);
    }

    ResourceManager *rm = ResourceManager::instance();

    tex = rm->loadTexture(texture);
}

void Quad::draw(Uniforms unis) {
    glBindVertexArray(Quad::vao);
    glBindTexture(GL_TEXTURE_2D, tex->getGlName());
    glUniform1i(unis.tex, 0);
    glm::mat4 pos = glm::translate(glm::mat4(1.0f), position);
    glUniformMatrix4fv(unis.model, 1, false, &pos[0][0]);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
