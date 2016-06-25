#include <fstream>
#include <streambuf>
#include "Shader.hpp"
#include "../Error.hpp"
using namespace std;

#define SHADER_ERROR "Shader Error"

ShaderProgram::ShaderProgram() {
    programID = 0;
    vertexShader = 0;
    fragmentShader = 0;
}

void ShaderProgram::init(const string &vertex, const string &fragment) {
    vertexFile = vertex;
    fragmentFile = fragment;
    vertexShader = compileShader(vertex, GL_VERTEX_SHADER);
    fragmentShader = compileShader(fragment, GL_FRAGMENT_SHADER);

    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    GLint linkOK = false;
    glGetProgramiv(programID, GL_LINK_STATUS, &linkOK);
    if(linkOK == false) {
        throw ErrMsg(SHADER_ERROR, getLog(programID));
    }
}

ShaderProgram::~ShaderProgram() {
    glDetachShader(programID, vertexShader);
    glDetachShader(programID, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(programID);
}

GLuint ShaderProgram::getID() {
    return programID;
}

GLint ShaderProgram::getUniform(const string &name) {
    GLint location = glGetUniformLocation(programID, name.c_str());
    if(location == -1) {
        throw ErrMsg(SHADER_ERROR, 
            vertexFile+" "+fragmentFile+":\nCan't find uniform: "+name);
    }

    return location;
}

GLuint ShaderProgram::compileShader(const string &file, GLenum type) {
    string data = loadFile(file);
    const char *sourcec = data.c_str();
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &sourcec, NULL);
    glCompileShader(shader);

    GLint compileOK = false;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileOK);
    if(compileOK == false) {
        throw ErrMsg(SHADER_ERROR, file+":\n"+getLog(shader));
    }

    return shader;
}

string ShaderProgram::loadFile(const string &filename) {
    ifstream file(filename);
    if(file.is_open() == false) {
        throw ErrMsg(SHADER_ERROR, "Cannot open file "+filename);
    }
    return string(istreambuf_iterator<char>(file),
                    istreambuf_iterator<char>());
}

string ShaderProgram::getLog(GLuint object) {
    GLint logLength = 0;
    if(glIsShader(object)) {
        glGetShaderiv(object, GL_INFO_LOG_LENGTH, &logLength);
    } else {
        glGetProgramiv(object, GL_INFO_LOG_LENGTH, &logLength);
    }

    char *log = new char[logLength];
    if(glIsShader(object)) {
        glGetShaderInfoLog(object, logLength, nullptr, log);
    } else {
        glGetProgramInfoLog(object, logLength, nullptr, log);
    }

    string out = log;
    delete[] log;
    return out;
}

