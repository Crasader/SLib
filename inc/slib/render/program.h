#ifndef CHECKHEADER_SLIB_RENDER_PROGRAM
#define CHECKHEADER_SLIB_RENDER_PROGRAM

#include "definition.h"
#include "base.h"
#include "texture.h"

#include "../math/geometry.h"
#include "../graphics/color.h"

#define SLIB_RENDER_MAX_TEXTURE_SAMPLERS 16

SLIB_RENDER_NAMESPACE_BEGIN

struct Primitive;
class RenderEngine;

class SLIB_EXPORT RenderProgramInfo : public Referable
{
public:
	RenderProgramInfo();
	~RenderProgramInfo();

public:
	sl_uint32 program_GL;
	void* effect_D3D9;
};

class SLIB_EXPORT RenderProgram : public RenderBaseObject
{
	SLIB_DECLARE_OBJECT(RenderProgram, RenderBaseObject)
protected:
	RenderProgram();

public:
	virtual Ref<RenderProgramInfo> create(RenderEngine* engine) = 0;
	virtual sl_bool onInit(RenderEngine* engine, RenderProgramInfo* info) { return sl_true; }
	virtual sl_bool onBeginProgram(RenderEngine* engine, RenderProgramInfo* info) { return sl_true; }
	virtual void onEndProgram(RenderEngine* engine, RenderProgramInfo* info) {}
	virtual sl_bool onPreRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive) { return sl_true; }
	virtual void onPostRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive) {}

	virtual String getGLSLVertexShader(RenderEngine* engine) { return String::null(); }
	virtual String getGLSLFragmentShader(RenderEngine* engine) { return String::null(); }

};


#define SLIB_RENDER_GL_SET_VERTEX_FLOAT_ARRAY_ATTRIBUTE(engine, location, VertexData, member) \
	engine->setVertexFloatArrayAttribute(location, (sl_uint32)(sl_size)(&(((VertexData*)0)->member)), sizeof(((VertexData*)0)->member) / sizeof(float), sizeof(VertexData));

// Base class for 2D RenderPrograms
class SLIB_EXPORT RenderProgram2D : public RenderProgram
{
public:
	RenderProgram2D();
	~RenderProgram2D();

public:
	SLIB_PROPERTY_INLINE(Matrix3, Transform)

	SLIB_PROPERTY_INLINE(Matrix3, TextureTransform)

	SLIB_PROPERTY_INLINE(Color3f, Color)
	SLIB_PROPERTY_INLINE(float, Alpha)

	class Info_GL : public RenderProgramInfo
	{
	public:
		SLIB_INLINE Info_GL() {}

		sl_int32 uniformTransform;	// Matrix3

		sl_int32 uniformTextures[SLIB_RENDER_MAX_TEXTURE_SAMPLERS];	// samplers
		sl_int32 uniformTransformTexture; // Matrix3
		
		sl_int32 uniformColor;		// Vector3
		sl_int32 uniformAlpha;		// float

		sl_int32 attrPosition;		// Vector2
		sl_int32 attrColor;			// Vector4
		sl_int32 attrTexCoord;		// Vector2
	};


	SLIB_INLINE Ref<Texture> getTexture(sl_uint32 no)
	{
		if (no < SLIB_RENDER_MAX_TEXTURE_SAMPLERS) {
			return m_textures[no];
		} else {
			return Ref<Texture>::null();
		}
	}
	SLIB_INLINE Ref<Texture> getTexture()
	{
		return m_textures[0];
	}
	SLIB_INLINE void setTexture(sl_uint32 no, Ref<Texture> texture)
	{
		if (no < SLIB_RENDER_MAX_TEXTURE_SAMPLERS) {
			m_textures[no] = texture;
		}
	}
	SLIB_INLINE void setTexture(Ref<Texture> texture)
	{
		m_textures[0] = texture;
	}

public:
	virtual Ref<RenderProgramInfo> create(RenderEngine* engine);
	virtual sl_bool onInit(RenderEngine* engine, RenderProgramInfo* info);
	virtual sl_bool onBeginProgram(RenderEngine* engine, RenderProgramInfo* info);

protected:
	Ref<Texture> m_textures[SLIB_RENDER_MAX_TEXTURE_SAMPLERS];
};

// Position(2), TexCoord(2)
class SLIB_EXPORT RenderProgram2D_PositionTexture : public RenderProgram2D
{
public:
	RenderProgram2D_PositionTexture() {}
	~RenderProgram2D_PositionTexture() {}

	struct VertexData
	{
		Vector2 position;
		Vector2 texCoord;
	};
public:
	virtual String getGLSLVertexShader(RenderEngine* engine);
	virtual String getGLSLFragmentShader(RenderEngine* engine);
	virtual sl_bool onPreRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive);
	virtual void onPostRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive);
};

// Position(2), Color(4)
class SLIB_EXPORT RenderProgram2D_PositionColor : public RenderProgram2D
{
public:
	RenderProgram2D_PositionColor() {}
	~RenderProgram2D_PositionColor() {}

	struct VertexData
	{
		Vector2 position;
		Color4f color;
	};
public:
	virtual String getGLSLVertexShader(RenderEngine* engine);
	virtual String getGLSLFragmentShader(RenderEngine* engine);
	virtual sl_bool onPreRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive);
	virtual void onPostRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive);
};

// Position(2)
class SLIB_EXPORT RenderProgram2D_Position : public RenderProgram2D
{
public:
	RenderProgram2D_Position() {}
	~RenderProgram2D_Position() {}

	struct VertexData
	{
		Vector2 position;
	};
public:
	virtual String getGLSLVertexShader(RenderEngine* engine);
	virtual String getGLSLFragmentShader(RenderEngine* engine);
	virtual sl_bool onPreRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive);
	virtual void onPostRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive);
};

// Base class for 3D RenderPrograms
class SLIB_EXPORT RenderProgram3D : public RenderProgram
{
public:
	RenderProgram3D();
	~RenderProgram3D();

	SLIB_PROPERTY_INLINE(Vector3, DirectionalLight)
	SLIB_PROPERTY_INLINE(Color3f, DiffuseColor)
	SLIB_PROPERTY_INLINE(Color3f, AmbientColor)
	SLIB_PROPERTY_INLINE(float, Alpha)
	SLIB_PROPERTY_INLINE(Matrix3, TextureTransform)

	class Info_GL : public RenderProgramInfo
	{
	public:
		SLIB_INLINE Info_GL() {}

		sl_int32 uniformTransform;				// Matrix4
		sl_int32 uniformMatrixModel;			// Matrix4
		sl_int32 uniformMatrixView;				// Matrix4
		sl_int32 uniformMatrixProjection;		// Matrix4
		sl_int32 uniformMatrixModelView;		// Matrix4
		sl_int32 uniformMatrixModelViewIT;		// Matrix4
		sl_int32 uniformMatrixViewProjection;	// Matrix4

		sl_int32 uniformTextures[SLIB_RENDER_MAX_TEXTURE_SAMPLERS];	// samplers
		sl_int32 uniformTextureAlphas[SLIB_RENDER_MAX_TEXTURE_SAMPLERS];	// samplers
		sl_int32 uniformTransformTexture;		// Matrix3

		sl_int32 uniformDirectionalLight;		// Vector3
		sl_int32 uniformDiffuseColor;			// Vector3
		sl_int32 uniformAmbientColor;			// Vector3
		sl_int32 uniformAlpha;					// float

		sl_int32 attrPosition;	// Vector3
		sl_int32 attrNormal;	// Vector3
		sl_int32 attrColor;		// Vector3
		sl_int32 attrTexCoord;	// Vector2

	};

	SLIB_INLINE const Matrix4& getModelMatrix()
	{
		return m_matrixModel;
	}
	void setModelMatrix(const Matrix4& t);

	SLIB_INLINE const Matrix4& getViewMatrix()
	{
		return m_matrixView;
	}
	void setViewMatrix(const Matrix4& t);

	SLIB_INLINE const Matrix4& getProjectionMatrix()
	{
		return m_matrixProjection;
	}
	void setProjectionMatrix(const Matrix4& t, sl_bool flagUpdateTransform = sl_true);

	const Matrix4& getTransform();
	void setTransform(const Matrix4& t);

	const Matrix4& getModelViewMatrix();
	void setModelViewMatrix(const Matrix4& t);

	const Matrix4& getModelViewMatrixInverseTranspose();
	void setModelViewMatrixInverseTranspose(const Matrix4& t);

	const Matrix4& getViewProjectionMatrix();
	void setViewProjectionMatrix(const Matrix4& t);

	SLIB_INLINE Ref<Texture> getTexture(sl_uint32 no)
	{
		if (no < SLIB_RENDER_MAX_TEXTURE_SAMPLERS) {
			return m_textures[no];
		} else {
			return Ref<Texture>::null();
		}
	}
	SLIB_INLINE Ref<Texture> getTexture()
	{
		return m_textures[0];
	}
	SLIB_INLINE void setTexture(sl_uint32 no, Ref<Texture> texture)
	{
		if (no < SLIB_RENDER_MAX_TEXTURE_SAMPLERS) {
			m_textures[no] = texture;
		}
	}
	SLIB_INLINE void setTexture(Ref<Texture> texture)
	{
		m_textures[0] = texture;
	}
	
	SLIB_INLINE float getTextureAlpha(sl_uint32 no)
	{
		if (no < SLIB_RENDER_MAX_TEXTURE_SAMPLERS) {
			return m_textureAlphas[no];
		} else {
			return 0;
		}
	}
	SLIB_INLINE void setTextureAlpha(sl_uint32 no, float alpha)
	{
		if (no < SLIB_RENDER_MAX_TEXTURE_SAMPLERS) {
			m_textureAlphas[no] = alpha;
		}
	}

protected:
	Matrix4 m_matrixModel;
	Matrix4 m_matrixView;
	Matrix4 m_matrixProjection;

	sl_bool m_flagValidMatrixTransform;
	Matrix4 m_matrixTransform;
	sl_bool m_flagValidMatrixModelView;
	Matrix4 m_matrixModelView;
	sl_bool m_flagValidMatrixModelViewIT;
	Matrix4 m_matrixModelViewIT;
	sl_bool m_flagValidMatrixViewProjection;
	Matrix4 m_matrixViewProjection;

public:
	virtual Ref<RenderProgramInfo> create(RenderEngine* engine);
	virtual sl_bool onInit(RenderEngine* engine, RenderProgramInfo* info);
	virtual sl_bool onBeginProgram(RenderEngine* engine, RenderProgramInfo* info);

protected:
	Ref<Texture> m_textures[SLIB_RENDER_MAX_TEXTURE_SAMPLERS];
	float m_textureAlphas[SLIB_RENDER_MAX_TEXTURE_SAMPLERS];
};

// Position(3), Normal(3), Color(4)
class SLIB_EXPORT RenderProgram3D_PositionNormalColor_Diffuse : public RenderProgram3D
{
public:
	RenderProgram3D_PositionNormalColor_Diffuse() {}
	~RenderProgram3D_PositionNormalColor_Diffuse() {}
	
	struct VertexData
	{
		Vector3 position;
		Vector3 normal;
		Color4f color;
	};
public:
	virtual String getGLSLVertexShader(RenderEngine* engine);
	virtual String getGLSLFragmentShader(RenderEngine* engine);
	virtual sl_bool onPreRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive);
	virtual void onPostRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive);
};

// Position(3), Color(4)
class SLIB_EXPORT RenderProgram3D_PositionColor : public RenderProgram3D
{
public:
	RenderProgram3D_PositionColor() {}
	~RenderProgram3D_PositionColor() {}

	struct VertexData
	{
		Vector3 position;
		Color4f color;
	};
public:
	virtual String getGLSLVertexShader(RenderEngine* engine);
	virtual String getGLSLFragmentShader(RenderEngine* engine);
	virtual sl_bool onPreRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive);
	virtual void onPostRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive);
};

// Position(3), Normal(3), TexCoord0(2)
class SLIB_EXPORT RenderProgram3D_PositionNormalTexture_Diffuse : public RenderProgram3D
{
public:
	RenderProgram3D_PositionNormalTexture_Diffuse() {}
	~RenderProgram3D_PositionNormalTexture_Diffuse() {}

	struct VertexData
	{
		Vector3 position;
		Vector3 normal;
		Vector2 texCoord;
	};
public:
	virtual String getGLSLVertexShader(RenderEngine* engine);
	virtual String getGLSLFragmentShader(RenderEngine* engine);
	virtual sl_bool onPreRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive);
	virtual void onPostRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive);
};

// Position(3), TexCoord(2)
class SLIB_EXPORT RenderProgram3D_PositionTexture : public RenderProgram3D
{
public:
	RenderProgram3D_PositionTexture() {}
	~RenderProgram3D_PositionTexture() {}

	struct VertexData
	{
		Vector3 position;
		Vector2 texCoord;
	};
public:
	virtual String getGLSLVertexShader(RenderEngine* engine);
	virtual String getGLSLFragmentShader(RenderEngine* engine);
	virtual sl_bool onPreRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive);
	virtual void onPostRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive);
};

// Position(3), Normal(3)
class SLIB_EXPORT RenderProgram3D_PositionNormal_Diffuse : public RenderProgram3D
{
public:
	RenderProgram3D_PositionNormal_Diffuse() {}
	~RenderProgram3D_PositionNormal_Diffuse() {}

	struct VertexData
	{
		Vector3 position;
		Vector3 normal;
	};
public:
	virtual String getGLSLVertexShader(RenderEngine* engine);
	virtual String getGLSLFragmentShader(RenderEngine* engine);
	virtual sl_bool onPreRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive);
	virtual void onPostRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive);
};

// Position(3)
class SLIB_EXPORT RenderProgram3D_Position : public RenderProgram3D
{
public:
	RenderProgram3D_Position() {}
	~RenderProgram3D_Position() {}

	struct VertexData
	{
		Vector3 position;
	};

public:
	virtual String getGLSLVertexShader(RenderEngine* engine);
	virtual String getGLSLFragmentShader(RenderEngine* engine);
	virtual sl_bool onPreRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive);
	virtual void onPostRender(RenderEngine* engine, RenderProgramInfo* info, Primitive* primitive);
};


SLIB_RENDER_NAMESPACE_END

#endif

