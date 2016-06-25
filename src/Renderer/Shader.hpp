#ifndef SHADER_HPP
#define SHADER_HPP
#include <string>
#include "gl_33.hpp"

class ShaderProgram {
    public:
        ShaderProgram();
        ~ShaderProgram();
        
        void init(const std::string &vertex, const std::string &fragment);
        GLuint getID();
        GLint getUniform(const std::string &name);
    private:
        GLuint programID;
        GLuint vertexShader, fragmentShader;
        std::string vertexFile, fragmentFile;

        GLuint compileShader(const std::string &file, GLenum type);
        std::string getLog(GLuint object);
        std::string loadFile(const std::string &filename);
};

#endif
