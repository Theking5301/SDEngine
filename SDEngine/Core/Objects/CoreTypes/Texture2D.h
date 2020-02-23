#pragma once
#include <GLEW/glew.h>
#include "Core/DataTypes/TypeDefenitions.h"
#include "Core/Assets/ISerializeableAsset.h"
#include "Core/Objects/EngineObject.h"

class Shader;

class Texture2D : public EngineObject, public ISerializeableAsset {

public:
	/*Wrap Behavior: GL_REPEAT or GL_CLAMP. Filter Behavior: GL_LINEAR or GL_NEAREST*/
	Texture2D(const TString& TextureName);
	Texture2D(const TString& TextureName, int32 Width, int32 Height);
	virtual ~Texture2D();

	void Bind(const TString& Name, Shader* BindShader, const uint8& Offset);

	const GLuint& GetTexture() const;
	const vec2& GetDimensions() const;

	bool ImportAsset(const TString& FilePath) override;
	bool SerializeToBuffer(SerializationStream& Stream) const override;
	bool DeserializeFromBuffer(DeserializationStream& Stream) override;

protected:
	virtual void SendTextureDataToGPU();

private:
	bool bSentToGPU;
	GLuint Texture;

	vec2 TextureDimensions;
	int32 NumComponents;
	int32 ExpectedComponents;
	GLint WrapBehaviour;
	GLfloat FilterBehaviour;
	SArray<unsigned char> TextureData;
};

