#ifndef _SNAIL_H
#define _SNAIL_H

#include "Primitive.h"
class Snail : public Primitive
{
public:
	Snail(Mesh* mesh, Texture2D* texture, Material* material, Vector3 startPos, Vector3 endPos);
	~Snail();

	void Update() override;
	bool GetFinished();
	void RollSpeed();
private:
	float m_speed;
	Vector3 m_endPos;
	bool m_finished;
};

#endif // !_SNAIL_H