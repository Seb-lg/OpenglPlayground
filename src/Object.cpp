//
// Created by seub on 3/14/22.
//


#include <sstream>
#include <fstream>
#include <iterator>
#include <cstring>
#include <iostream>
#include "Object.hpp"
#include "../helpers/stb_image.hpp"
#include "../helpers/HelperFile.hpp"


void Object::Init() {
	LoadVertex();
	program = glCreateProgram();

	float jej[] = {
			// positions          // colors           // texture coords
			0.5f,  0.5f, 0.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f, // top right
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom left
//			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,   1.0f, 1.0f, 0.0f, // top left
	};
	unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
	};

	uint EBO;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBufferData(GL_ARRAY_BUFFER, suzanne_jtebaise.size()*sizeof(float), suzanne_jtebaise.data(), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, obj.size()*sizeof(float), obj.data(), GL_STATIC_DRAW);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(jej), jej, GL_STATIC_DRAW);

//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	for (int i = 0; i < obj.size(); i+=5) {
		std::cout << obj[i+0] << '\t' << obj[i+1] << '\t' << obj[i+2] << "\ttext\t" << obj[i+3] << '\t' << obj[i+4] << std::endl;
	}

	// position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)0);
	// texture coord attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(float)));
	// normals
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)(5*sizeof(float)));

	//	LOAD TEXTURE
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load("./assets/awesomeface.bmp", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	InitShaders();
}

void Object::InitShaders() {
	//  Compile camera's vertex shader
	unsigned int sVertex = glCreateShader(GL_VERTEX_SHADER);
//	std::ifstream t("./shaders/41.texture.vs.shader");
	std::ifstream t("./shaders/camera_v.shader");
	auto tmp = std::string((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
	const char *file = tmp.c_str();
	glShaderSource(sVertex, 1, &file, NULL);
	glCompileShader(sVertex);

	//  Check compilation
	int success;
	glGetShaderiv(sVertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetShaderInfoLog(sVertex, 1024, NULL, infoLog);
		std::cout << "Error during the compilation of the camera's vertex shader"
				  << infoLog << std::endl;
		exit(84);
	}

	glAttachShader(program, sVertex);
	//  Compile obj fragment shader
	unsigned int sFragment = glCreateShader(GL_FRAGMENT_SHADER);
//	t = std::ifstream("./shaders/41.texture.fs.shader");
	t = std::ifstream("./shaders/camera_f.shader");
	tmp = std::string((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
	file = tmp.c_str();
	glShaderSource(sFragment, 1, &file, NULL);
	glCompileShader(sFragment);

	//  Check compilation
	glGetShaderiv(sFragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetShaderInfoLog(sFragment, 1024, NULL, infoLog);
		std::cout << "Error during the compilation of the object's fragment shader"
				  << infoLog << std::endl;
		exit(84);
	}
	glAttachShader(program, sFragment);

	// Compile program linked shaders
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetProgramInfoLog(program, 1024, NULL, infoLog);
		std::cout << "Error during the compilation of the program shaders" << std::endl
				  << infoLog << std::endl;
		exit(84);
	}
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
}

void Object::LoadVertex() {
	obj = HelperFile::LoadObj(vertex_file);
	/*std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	std::ifstream f(vertex_file);
	std::string line;
	while (std::getline(f, line)) {
		if (line.find("vt") == 0) {
			line.erase(0, std::string("vt ").size());
			glm::vec2 uv;
//			scanf(line.c_str(), "%f %f\n", &uv.x, &uv.y);
			std::istringstream iss(line);
			std::vector<float> v;
			std::copy(std::istream_iterator<float>(iss),
					  std::istream_iterator<float>(),
					  std::back_inserter(v));
			temp_uvs.emplace_back(v[0], v[1]);

		} else if (line.find("vn") == 0) {
			line.erase(0, std::string("vt ").size());
			glm::vec3 normal;
//			scanf(line.c_str(), "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			std::istringstream iss(line);
			std::vector<float> v;
			std::copy(std::istream_iterator<float>(iss),
					  std::istream_iterator<float>(),
					  std::back_inserter(v));

			temp_normals.emplace_back(v[0], v[1], v[2]);
		} else if (line.find('v') == 0) {
			line.erase(0, std::string("t ").size());
			glm::vec3 vertex;
//			scanf(line.c_str(), "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			std::istringstream iss(line);
			std::vector<float> v;
			std::copy(std::istream_iterator<float>(iss),
					  std::istream_iterator<float>(),
					  std::back_inserter(v));

			temp_vertices.emplace_back(v[0], v[1], v[2]);
		} else if (line.find('f') == 0) {
			line.erase(0, std::string("t ").size());
			std::replace( line.begin(), line.end(), '/', ' ');
//			std::string vertex1, vertex2, vertex3;
//			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
//			int matches = scanf(line.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0],
//								&normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2],
//								&uvIndex[2], &normalIndex[2]);
//			if (matches != 9) {
//				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
//				exit(false);
//			}

			std::istringstream iss(line);
			std::vector<int> v;
			std::copy(std::istream_iterator<int>(iss),
					  std::istream_iterator<int>(),
					  std::back_inserter(v));

			vertexIndices.push_back(v[0 + 0]);
			vertexIndices.push_back(v[0 + 3]);
			vertexIndices.push_back(v[0 + 6]);

			uvIndices.push_back(v[1 + 0]);
			uvIndices.push_back(v[1 + 3]);
			uvIndices.push_back(v[1 + 6]);

			normalIndices.push_back(v[2 + 0]);
			normalIndices.push_back(v[2 + 3]);
			normalIndices.push_back(v[2 + 6]);


		} else {
			std::cout << "TRASH:\t" << line << "\t" << std::strcmp(line.c_str(), "v")<< std::endl;
		}
	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		glm::vec2 uv = temp_uvs[ uvIndex-1 ];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];

		// Put the attributes in buffers
		vertices.push_back(vertex);
		uvs     .push_back(uv);
		normals .push_back(normal);
	}
//	obj.reserve(vertices.size()*3);
	for (int i = 0; i < vertices.size(); ++i) {
		obj.push_back(vertices[i].x);obj.push_back(vertices[i].y);obj.push_back(vertices[i].z);
		obj.push_back(uvs[i].x);obj.push_back(uvs[i].y);
//		obj.push_back(normals[0].x);obj.push_back(normals[0].y);obj.push_back(normals[0].z);
	}
//	for (int i = 0; i < vertices.size(); ++i) {
//		obj.push_back(vertices[0].x);obj.push_back(vertices[0].y);obj.push_back(vertices[0].z);
//		obj.push_back(uvs[0].x);obj.push_back(uvs[0].y);
//		obj.push_back(normals[0].x);obj.push_back(normals[0].y);obj.push_back(normals[0].z);
//	}
	std::cout << vertices.size() << " " << uvs.size() << " " << normals.size() << std::endl;*/
}

void Object::CheckErrorShader(GLuint shader) {
	// Get log length
	GLint maxLength;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

	// Init a string for it
	std::vector<GLchar> errorLog(maxLength);

	if (maxLength > 1) {
		// Get the log file
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

		std::cout << "--------------Shader compilation error-------------\n";
		std::cout << errorLog.data();
	}
}