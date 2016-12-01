//@	{
//@	 "targets":
//@		[{
//@		 "name":"gltest","type":"application"
//@ 	,"dependencies":
//@			[
//@			 {"ref":"GL","rel":"external"}
//@			,{"ref":"GLEW","rel":"external"}
//@			,{"ref":"glfw","rel":"external"}
//@			]
//@		,"description":"OpenGL test app"
//@		}]
//@	}

#include "../frustum.hpp"
#include "../transformation.hpp"
#include "../translation.hpp"
#include "teapot.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdio>
#include <memory>

using namespace GeoSIMD;

static void init()
	{
	if(!glfwInit())
		{throw "Failed to initialize GLFW";}

	glfwWindowHint(GLFW_SAMPLES,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DOUBLEBUFFER,GL_TRUE);
	}

struct WindowDeleter
	{
	void operator()(GLFWwindow* win) noexcept
		{glfwDestroyWindow(win);}
	};

struct WindowHandle:public std::unique_ptr<GLFWwindow,WindowDeleter>
	{
	WindowHandle(GLFWwindow* win):unique_ptr<GLFWwindow,WindowDeleter>(win,WindowDeleter())
		{
		if(win==nullptr)
			{throw "Window creation failed";}
		}
	};

static void close(GLFWwindow* handle)
	{glfwSetWindowShouldClose(handle,1);}

class GlShader
	{
	public:
		explicit GlShader(GLenum type)
			{id=glCreateShader(type);}

		GlShader& sourceSet(const char* source) noexcept
			{
			glShaderSource(id,1,&source,NULL);
			return *this;
			}

		void compile();

		~GlShader()
			{glDeleteShader(id);}

		GLuint idGet() const noexcept
			{return id;}

	private:
		GLuint id;
	};

void GlShader::compile()
	{
	glCompileShader(id);
	GLint result;
	glGetShaderiv(id,GL_COMPILE_STATUS,&result);
	if(result==GL_FALSE)
		{
		glGetShaderiv(id,GL_INFO_LOG_LENGTH,&result);
		if(result>0)
			{
			char buffer[512];
			glGetShaderInfoLog(id,512,NULL,buffer);
			fprintf(stderr,"Could not compile shader: %s",buffer);
			throw "Shader compilation error";
			}
		}
	}

static GLuint shaderProgramCreate(const char* vertex_shader_src
	,const char* fragment_shader_src)
	{
	GlShader vertex_shader(GL_VERTEX_SHADER);
	vertex_shader.sourceSet(vertex_shader_src);
	vertex_shader.compile();
	GlShader fragment_shader(GL_FRAGMENT_SHADER);
	fragment_shader.sourceSet(fragment_shader_src);
	fragment_shader.compile();
	auto ret=glCreateProgram();
	glAttachShader(ret,vertex_shader.idGet());
	glAttachShader(ret,fragment_shader.idGet());
	glLinkProgram(ret);
	glDetachShader(ret, vertex_shader.idGet());
	glDetachShader(ret, fragment_shader.idGet());
	return ret;
	}



static constexpr GLfloat verts[]=
	{
	-1.0f, -1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,
	 0.0f,  1.0f, 0.0f
	};

static constexpr const char* vertex_shader=
	"#version 330 core\n"
	"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
	"uniform mat4 MVP;\n"
	"void main()\n"
	"	{\n"
	"	gl_Position=MVP*vec4(vertexPosition_modelspace,1);\n"
	"	}\n";

static constexpr const char* fragment_shader=
	"#version 330 core\n"
	"out vec3 color;\n"
	"void main()\n"
	"	{\n"
	"	color = vec3(1,1,1);\n"
	"	}\n";

class GLScene
	{
	public:
		GLScene()
			{
			glGenVertexArrays(1,&m_vertex_array);
			glBindVertexArray(m_vertex_array);
			glGenBuffers(1,&m_vertex_buffer);
			glBindBuffer(GL_ARRAY_BUFFER,m_vertex_buffer);
		
			m_shader=shaderProgramCreate(vertex_shader,fragment_shader);
			m_mvp_id=glGetUniformLocation(m_shader,"MVP");

		//	glBufferData(GL_ARRAY_BUFFER,sizeof(teapot_vertices),teapot_vertices,GL_STATIC_DRAW);
			glBufferData(GL_ARRAY_BUFFER,sizeof(verts),verts,GL_STATIC_DRAW);
			}

		void render()
			{
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			glUseProgram(m_shader);



			auto frust=Frustum<float>(1.0f,16.0f,4.0f/3.0f,45.0_degf);
			auto trans=translate<float>(-4.0_zf);

			auto mvp=frust.data() * trans.data();
		//	mvp.push(translate<float>(4.0_zf));

		//	auto p=transform(origin<float>(),mvp);
		//	printf("%.7g %.7g %.7g\n",p.x(),p.y(),p.z());
			//	.push(rotateZ<float>(30.0_degf));
			

			glUniformMatrix4fv(m_mvp_id, 1, GL_FALSE, mvp.data());

			auto projection=glm::perspective(static_cast<float>(45.0_degf)
				,4.0f/3.0f,1.0f,16.0f);
			auto view=glm::translate(glm::mat4(),glm::vec3(0,0,-4.0f));
			auto mvpglm=projection*view;

			glUniformMatrix4fv(m_mvp_id, 1, GL_FALSE, mvp.data());

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
			glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,nullptr);
			glDrawArrays(GL_TRIANGLES,0,3);
			glDisableVertexAttribArray(0);
			}

		~GLScene()
			{
			glDeleteProgram(m_shader);
			glBindBuffer(GL_ARRAY_BUFFER,0);
			glDeleteBuffers(1,&m_vertex_buffer);

			glBindVertexArray(0);
			glDeleteVertexArrays(1,&m_vertex_array);
			}
	private:
		GLuint m_vertex_array;
		GLuint m_vertex_buffer;
		GLuint m_shader;

		GLuint m_mvp_id;
	};

struct ViewState
	{
	GLScene scene;
	};

static void render(GLFWwindow* handle)
	{
	auto vs=reinterpret_cast<ViewState*>(glfwGetWindowUserPointer(handle));
	vs->scene.render();
	glfwSwapBuffers(handle);
	};

int main()
	{
	try
		{
		init();
		auto window=WindowHandle(glfwCreateWindow(640,480,"test",nullptr,nullptr));
		glfwSetWindowCloseCallback(window.get(),close);
		glfwMakeContextCurrent(window.get());

		glewExperimental=true;
		if(glewInit()!=GLEW_OK)
			{throw "Failed to initialize GLEW";}

		ViewState vs;
		glfwSetWindowUserPointer(window.get(),&vs);
		
		while(!glfwWindowShouldClose(window.get()))
			{
			glfwWaitEvents();
			render(window.get());
			}
		}
	catch(const char* message)
		{
		fprintf(stderr,"Error: %s\n",message);
		return -1;
		}
	return 0;
	}
