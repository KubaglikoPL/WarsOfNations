#include <platform/platform.h>
#include <malloc.h>
#ifdef PLATFORM_GL2_IMPL
#include "gl2.h"

#ifdef PLATFORM_GLFW_IMPL
#include <GLFW/glfw3.h>

void* glGetProc(const char* name) {
	return glfwGetProcAddress(name);
}
#endif

PFNGLGENTEXTURESPROC glGenTextures;
PFNGLBINDTEXTUREPROC glBindTexture;
PFNGLTEXIMAGE2DPROC glTexImage2D;
PFNGLTEXSUBIMAGE2DPROC glTexSubImage2D;
PFNGLDELETETEXTURESPROC glDeleteTexture;

PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLBUFFERSUBDATAPROC glBufferSubData;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

PFNGLCREATESHADERPROC glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLDELETESHADERPROC glDeleteShader;

PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
PFNGLUSEPROGRAMPROC glUseProgram;

PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLUNIFORM4FVPROC glUniform4fv;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;

PFNGLCLEARPROC glClear;
PFNGLCLEARCOLORPROC glClearColor;

PFNGLDRAWARRAYSPROC glDrawArrays;
PFNGLDRAWELEMENTSPROC glDrawElements;

Renderer createRenderer(Window window) {
	glRenderer_t renderer;
	renderer.activeTexture = 0;
	renderer.activeVBO = 0;
	renderer.activeEBO = 0;
	renderer.activeProgram = 0;

	glGenTextures = glGetProc("glGenTextures");
	glBindTexture = glGetProc("glBindTexture");
	glTexImage2D = glGetProc("glTexImage2D");
	glTexSubImage2D = glGetProc("glTexSubImage2D");
	glDeleteTexture = glGetProc("glDeleteTexture");

	glGenBuffers = glGetProc("glGenBuffers");
	glBindBuffer = glGetProc("glBindBuffer");
	glBufferData = glGetProc("glBufferData");
	glBufferSubData = glGetProc("glBufferSubData");
	glDeleteBuffers = glGetProc("glDeleteBuffers");
	glVertexAttribPointer = glGetProc("glVertexAttribPointer");
	glEnableVertexAttribArray = glGetProc("glEnableVertexAttribArray");

	glCreateShader = glGetProc("glCreateShader");
	glShaderSource = glGetProc("glShaderSource");
	glCompileShader = glGetProc("glCompileShader");
	glGetShaderiv = glGetProc("glGetShaderiv");
	glGetShaderInfoLog = glGetProc("glGetShaderInfoLog");

	glCreateProgram = glGetProc("glCreateProgram");
	glAttachShader = glGetProc("glAttachShader");
	glLinkProgram = glGetProc("glLinkProgram");
	glGetProgramiv = glGetProc("glGetProgramiv");
	glGetProgramInfoLog = glGetProc("glGetProgramInfoLog");
	glDeleteShader = glGetProc("glDeleteShader");

	glBindAttribLocation = glGetProc("glBindAttribLocation");
	glUseProgram = glGetProc("glUseProgram");

	glGetUniformLocation = glGetProc("glGetUniformLocation");
	glUniform1i = glGetProc("glUniform1i");
	glUniform4fv = glGetProc("glUniform4fv");
	glUniformMatrix3fv = glGetProc("glUniformMatrix3fv");
	glUniformMatrix4fv = glGetProc("glUniformMatrix4fv");

	glClear = glGetProc("glClear");
	glClearColor = glGetProc("glClearColor");

	glDrawArrays = glGetProc("glDrawArrays");
	glDrawElements = glGetProc("glDrawElements");

	return renderer;
}

inline void bindTexture(Renderer* renderer, uint32_t texture) {
	if (renderer->activeTexture != texture) {
		glBindTexture(GL_TEXTURE_2D, texture);
		renderer->activeTexture = texture;
	}
}

Texture createTexture(Renderer *renderer, uint32_t w, uint32_t h) {
	glRenderer_t* gl2_renderer = (glRenderer_t*)renderer;
	uint32_t texture;
	glGenTextures(1, &texture);
	bindTexture(renderer, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	gl2_renderer->activeTexture = texture;
	return texture;
}

void destroyTexture(Texture *texture) {
	glDeleteTexture(1, &texture);
}

void updateTexture(Renderer *renderer, Texture *texture, uint32_t x, uint32_t y, uint32_t w, uint32_t h, void* data) {
	glRenderer_t* gl2_renderer = (glRenderer_t*)renderer;
	uint32_t gl2_texture = *texture;
	bindTexture(renderer, gl2_texture);
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void rendererClear(Renderer *renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

inline void bindBuffer(Renderer* renderer, uint32_t buffer, uint32_t target) {
	if (target == GL_ARRAY_BUFFER) {
		if (renderer->activeVBO != buffer) {
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			renderer->activeVBO = buffer;
		}
	}
	else if (target == GL_ELEMENT_ARRAY_BUFFER) {
		if (renderer->activeEBO != buffer) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
			renderer->activeEBO = buffer;
		}
	}
}

Buffer rendererCreateBuffer(Renderer *renderer, uint32_t VBO_Size, uint32_t EBO_Size, bool shortIndicies, bool dynamicBuffer) {
	Buffer buffer;
	buffer.VBO_Size = VBO_Size;
	buffer.EBO_Size = EBO_Size;
	buffer.shortIndicies = shortIndicies;
	if (buffer.EBO_Size) glGenBuffers(1, &buffer.EBO);
	else buffer.EBO = 0;
	glGenBuffers(1, &buffer.VBO);
	uint32_t type = GL_STATIC_DRAW;
	if (dynamicBuffer) type = GL_STREAM_DRAW;
	if (buffer.VBO) {
		glBindBuffer(GL_ARRAY_BUFFER, buffer.VBO);
		glBufferData(GL_ARRAY_BUFFER, VBO_Size, NULL, type);
		renderer->activeVBO = buffer.VBO;
	}
	if (buffer.EBO) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBO_Size, NULL, type);
		renderer->activeEBO = buffer.EBO;
	}
	return buffer;
}

#include <stdio.h>

Shader createShader(const char* vertexShader, const char* fragmentShader, const char** defines, uint32_t numDefines) {
	Shader s;
	s.program = 0;

	uint32_t vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	uint32_t fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const char** strings = alloca((3 + numDefines) * sizeof(const char*));
	strings[0] = "#version 120\n";
	for (uint32_t i = 0; i < numDefines; i++) {
		strings[i + 1] = defines[i];
	}

	FILE* v_file = fopen(vertexShader, "rb");
	FILE* f_file = fopen(fragmentShader, "rb");
	if (v_file && f_file) {
		fseek(v_file, 0, SEEK_END);
		fseek(f_file, 0, SEEK_END);

		uint32_t v_size = ftell(v_file);
		uint32_t f_size = ftell(f_file);

		fseek(v_file, 0, SEEK_SET);
		fseek(f_file, 0, SEEK_SET);

		char* v_data = alloca(v_size + 1);
		char* f_data = alloca(f_size + 1);

		fread(v_data, 1, v_size, v_file);
		fread(f_data, 1, f_size, f_file);

		v_data[v_size] = 0;
		f_data[f_size] = 0;

		int success;
		char infoLog[512];

		strings[numDefines + 1] = "#define VERTEX_SHADER\n";
		strings[numDefines + 2] = v_data;
		glShaderSource(vertexShaderID, 3 + numDefines, strings, NULL);
		glCompileShader(vertexShaderID);
		glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			memset(infoLog, 0, 512);
			glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
			setLastError(infoLog);
			return s;
		}

		strings[numDefines + 1] = "#define FRAGMENT_SHADER\n";
		strings[numDefines + 2] = f_data;
		glShaderSource(fragmentShaderID, 3 + numDefines, strings, NULL);
		glCompileShader(fragmentShaderID);
		glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			memset(infoLog, 0, 512);
			glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
			setLastError(infoLog);
			return s;
		}

		uint32_t program = glCreateProgram();
		glAttachShader(program, vertexShaderID);
		glAttachShader(program, fragmentShaderID);
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			memset(infoLog, 0, 512);
			glGetProgramInfoLog(program, 512, NULL, infoLog);
			setLastError(infoLog);
			return s;
		}

		s.program = program;

		s.texture0_location = glGetUniformLocation(program, "texture0");
		s.VP_location = glGetUniformLocation(program, "VP_Matrix");

		if (s.texture0_location != -1) glUniform1i(s.texture0_location, 0);
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	
	glBindAttribLocation(s.program, 0, "aPos");
	glBindAttribLocation(s.program, 1, "aUV");
	glBindAttribLocation(s.program, 2, "aColor");

	return s;
}

inline void glUpdateBuffer(uint32_t target, uint32_t uSize, uint32_t bSize, uint32_t off, const void* data) {
	if ((uSize == bSize) && (off == 0)) {
		glBufferData(target, uSize, data, GL_STREAM_DRAW);
	}
	else {
		glBufferSubData(target, off, uSize, data);
	}
}

void updateVertexBuffer(Renderer* renderer, Buffer* buffer, vertex_t* v, uint32_t vNum, uint32_t off) {
	bindBuffer(renderer, buffer->VBO, GL_ARRAY_BUFFER);
	glUpdateBuffer(GL_ARRAY_BUFFER, sizeof(vertex_t) * vNum, buffer->VBO_Size, off, (const void*)v);
}

void updateIndexBuffer(Renderer* renderer, Buffer* buffer, uint32_t* i, uint32_t iNum, uint32_t off) {
	bindBuffer(renderer, buffer->EBO, GL_ELEMENT_ARRAY_BUFFER);
	glUpdateBuffer(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * iNum, buffer->EBO_Size, off, (const void*)i);
}

void updateIndexBuffer16(Renderer* renderer, Buffer* buffer, uint16_t* i, uint32_t iNum, uint32_t off) {
	bindBuffer(renderer, buffer->EBO, GL_ELEMENT_ARRAY_BUFFER);
	glUpdateBuffer(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * iNum, buffer->EBO_Size, off, (const void*)i);
}

void renderGeometry(Renderer* renderer, Buffer* buffer, Shader* shader, Texture* texture, uint32_t num, uint32_t off) {
	if (buffer && shader) {
		if (texture) {
			bindTexture(renderer, *texture);
		}
		bindBuffer(renderer, buffer->VBO, GL_ARRAY_BUFFER);
		bindBuffer(renderer, buffer->EBO, GL_ELEMENT_ARRAY_BUFFER);
		if (renderer->activeProgram != shader->program) {
			glUseProgram(shader->program);
			renderer->activeProgram = shader->program;
		}

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, x));
		glVertexAttribPointer(1, 2, GL_UNSIGNED_SHORT, GL_TRUE, sizeof(vertex_t), (void*)offsetof(vertex_t, u));
		glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vertex_t), (void*)offsetof(vertex_t, r));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		if (buffer->EBO) {
			if (!buffer->shortIndicies) glDrawElements(GL_TRIANGLES, num, GL_UNSIGNED_INT, (void*)(off * sizeof(uint32_t)));
			else glDrawElements(GL_TRIANGLES, num, GL_UNSIGNED_SHORT, (void*)(off * sizeof(uint16_t)));
		}
		else {
			glDrawArrays(GL_TRIANGLES, off, num);
		}
	}
}
#endif
