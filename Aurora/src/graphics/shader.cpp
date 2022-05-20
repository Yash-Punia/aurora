#include "graphics/shader.h"
#include "graphics/helpers.h"
#include "log.h"

#include "glad/glad.h"

#include "glm/gtc/type_ptr.hpp"

namespace aurora::graphics
{
    Shader::Shader(const std::string& vertex, const std::string& fragment) 
    {
        mProgramId = glCreateProgram(); //Returns reference to empty program object

        int status = GL_FALSE;
        char errorLog[512];

        uint32_t vertexShaderId = glCreateShader(GL_VERTEX_SHADER); //Returns reference to empty shader object
        {
            const GLchar* glSource = vertex.c_str(); //converts string to const GLchar*
            glShaderSource(vertexShaderId, 1, &glSource, NULL); //sets source code of vertex shader in shader
            glCompileShader(vertexShaderId);
            glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &status); //Returns the output of asked param

            if(status != GL_TRUE) 
            {
                glGetShaderInfoLog(vertexShaderId, sizeof(errorLog), NULL, errorLog); //Puts info log in error log
                AURORA_ERROR("Vertex shader compilation error: {}", errorLog);
            }
            else
            {
                glAttachShader(mProgramId, vertexShaderId);
            }
        }

        uint32_t fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER); //Returns reference to empty shader object
        if(status == GL_TRUE)
        {
            const GLchar* glSource = fragment.c_str(); //converts string to const GLchar*
            glShaderSource(fragmentShaderId, 1, &glSource, NULL); //sets source code of vertex shader in shader
            glCompileShader(fragmentShaderId);
            glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &status); //Returns the output of asked param
    
            if(status != GL_TRUE) 
            {
                glGetShaderInfoLog(fragmentShaderId, sizeof(errorLog), NULL, errorLog); //Puts info log in error log
                AURORA_ERROR("Fragment shader compilation error: {}", errorLog);
            }
            else
            {
                glAttachShader(mProgramId, fragmentShaderId);
            }
        }
        // TODO: Must fix __debugbreak
        // AURORA_ASSERT(status == GL_TRUE, "Error compiling shader");

        if(status == GL_TRUE) 
        {
            glLinkProgram(mProgramId);
            glValidateProgram(mProgramId);
            glGetProgramiv(mProgramId, GL_LINK_STATUS, &status);

            if(status != GL_TRUE) 
            {
                glGetProgramInfoLog(mProgramId, sizeof(errorLog), NULL, errorLog);
                AURORA_ERROR("Shader link error: {}", errorLog);
                glDeleteProgram(mProgramId);
                mProgramId = -1;
            }
        }

        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
    }

    Shader::~Shader() 
    {
        glUseProgram(0);
        glDeleteProgram(mProgramId);
    }

    void Shader::Bind() {
        glUseProgram(mProgramId);
    }

    void Shader::Unbind() {
        glUseProgram(0);
    }

    void Shader::SetUniformInt(const std::string& name, int val)
    {
        glUseProgram(mProgramId);
        glUniform1i(GetUniformLocation(name), val);
    }

    void Shader::SetUniformFloat(const std::string& name, float val1)
    {
        glUseProgram(mProgramId);
        glUniform1f(GetUniformLocation(name), val1);
    }

    void Shader::SetUniformFloat2(const std::string& name, float val1, float val2)
    {
        glUseProgram(mProgramId);
        glUniform2f(GetUniformLocation(name), val1, val2);
    }

    void Shader::SetUniformFloat2(const std::string& name, const glm::vec2& val)
	{
		SetUniformFloat2(name, val.x, val.y);
	}

    void Shader::SetUniformFloat3(const std::string& name, float val1, float val2, float val3)
    {
        glUseProgram(mProgramId);
        glUniform3f(GetUniformLocation(name), val1, val2, val3);
    }

    void Shader::SetUniformFloat3(const std::string& name, const glm::vec3& val)
	{
		SetUniformFloat3(name, val.x, val.y, val.z);
    }

    void Shader::SetUniformFloat4(const std::string& name, float val1, float val2, float val3, float val4)
    {
        glUseProgram(mProgramId);
        glUniform4f(GetUniformLocation(name), val1, val2, val3, val4);
    }

    void Shader::SetUniformFloat4(const std::string& name, const glm::vec4& val)
	{
		SetUniformFloat4(name, val.x, val.y, val.z, val.w);
	}

	void Shader::SetUniformMat3(const std::string& name, const glm::mat3& mat)
	{
		glUseProgram(mProgramId);
        AURORA_CHECK_GL_ERROR;
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat)); AURORA_CHECK_GL_ERROR;
	}

	void Shader::SetUniformMat4(const std::string& name, const glm::mat4& mat)
	{
		glUseProgram(mProgramId);
        AURORA_CHECK_GL_ERROR;
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat)); AURORA_CHECK_GL_ERROR;
	}

    int Shader::GetUniformLocation(const std::string& name) {
        auto it = mUniformLocations.find(name);
        
        if(it == mUniformLocations.end())
        {
            mUniformLocations[name] = glGetUniformLocation(mProgramId, name.c_str());
        }

        return mUniformLocations[name];
    }
}
