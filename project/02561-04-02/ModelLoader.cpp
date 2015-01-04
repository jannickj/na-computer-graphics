#include "ModelLoader.h"
#include "Angel\Angel.h"
#include "Angel\ObjLoader.h"

ModelLoader::ModelLoader(void)
{
}


ModelLoader::~ModelLoader(void)
{
}

Model * ModelLoader::Load(std::string modelfile, ShaderProgram * shaderProgram, float scale)
{
	std::vector<vec3> outPositions;
	std::vector<int> meshIndices;
	std::vector<vec3> outNormal;
	std::vector<vec2> outUv;
	const char * cfile = modelfile.c_str();
	loadObject(cfile, outPositions, meshIndices, outNormal, outUv, scale);
	
	GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vec3) * outPositions.size() * 2, NULL, GL_STATIC_DRAW );


    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(vec3) * outPositions.size(), &outPositions[0] );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(vec3) * outPositions.size(), sizeof(vec3) * outPositions.size(), &outNormal[0] );

	// set up vertex arrays
	GLuint vPosition = shaderProgram->Get("vPosition");
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

    GLuint vNormal = shaderProgram->Get("vNormal"); 
	if (vNormal != GL_INVALID_INDEX ){
		glEnableVertexAttribArray( vNormal );
		glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vec3) * outPositions.size()) );
	}
    glEnableVertexAttribArray(0);
	glBindVertexArray(0);



	return new Model(vao, meshIndices, outNormal, outUv);
}
