#ifndef _SCENE_OBJECT_H
#define _SCENE_OBJECT_H

#include "Primitive.h"
class SceneObject : public Primitive
{
public:
	/// <summary></summary>
	/// <param name="mesh"></param>
	/// <param name="texture"></param>
	/// <param name="material"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	SceneObject(Mesh* mesh, Texture2D* texture, Material* material, float x, float y, float z);
	~SceneObject();

	void Draw() override;
};

#endif // !_SCENE_OBJECT_H