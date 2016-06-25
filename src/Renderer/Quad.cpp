#include <glm/glm.hpp>
#include "Quad.hpp"
using namespace std;

struct QuadVert {
    glm::vec3 position;
    glm::vec2 texCoord;
};

GLuint Quad::vbo = 0;
GLuint Quad::vao = 0;

static QuadVert quadVerts[] = {
    {{-1.0, -1.0, 0.0},
    {0.0, 0.0}
    },
    {{-1.0, 1.0, 0.0},
    {0.0, 1.0}
    },
    {{1.0, 1.0, 0.0},
    {1.0, 1.0}
    },
    {{1.0, -1.0, 0.0},
    {1.0, 0.0}
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
}

void Quad::draw() {
    glBindVertexArray(Quad::vao);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
}
