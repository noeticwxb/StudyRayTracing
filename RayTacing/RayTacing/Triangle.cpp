#include "stdafx.h"
#include "Triangle.h"

Triangle::Triangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2, const rgb& _color)
:mP0(_p0), mP1(_p1), mP2(_p2), mColor(_color)
{

}

bool Triangle::hit(const Ray& r, float tmin, float tmax, float time, HitRecord& record) const
{
	float tval;
	float A = mP0.x() - mP1.x();
	float B = mP0.y() - mP1.y();
	float C = mP0.z() - mP1.z();

	float D = mP0.x() - mP2.x();
	float E = mP0.y() - mP2.y();
	float F = mP0.z() - mP2.z();

	float G = r.direction().x();
	float H = r.direction().y();
	float I = r.direction().z();

	float J = mP0.x() - r.origin().x();
	float K = mP0.y() - r.origin().y();
	float L = mP0.z() - r.origin().z();

	float EIHF = E*I - H*F;
	float GFDI = G*F - D*I;
	float DHEG = D*H - E*G;

	float denom = (A*EIHF + B*GFDI + C*DHEG);

	float beta = (J*EIHF + K*GFDI + L*DHEG) / denom; 

	if (beta <= 0.0f || beta >= 1.0f )
	{
		return false;
	}

	float AKJB = A*K - J*B;
	float JCAL = J*C - A*L;
	float BLKC = B*L - K*C;

	float gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;
	if (gamma <= 0.0f || ( (beta + gamma) >= 1.0f) ) 
	{
		return false;
	}

	tval = -(F*AKJB + E*JCAL + D*BLKC) / denom;
	if (tval >= tmin && tval <= tmax)
	{
		record.t = tval;
		record.normal = unitVertor( cross((mP1 - mP0), (mP2 - mP0)) );
		record.color = mColor;
		return true;
	}

	return false;
}

bool Triangle::shadowHit(const Ray& r, float tmin, float tmax, float time) const
{
	float tval;
	float A = mP0.x() - mP1.x();
	float B = mP0.y() - mP1.y();
	float C = mP0.z() - mP1.z();

	float D = mP0.x() - mP2.x();
	float E = mP0.y() - mP2.y();
	float F = mP0.z() - mP2.z();

	float G = r.direction().x();
	float H = r.direction().y();
	float I = r.direction().z();

	float J = mP0.x() - r.origin().x();
	float K = mP0.y() - r.origin().y();
	float L = mP0.z() - r.origin().z();

	float EIHF = E*I - H*F;
	float GFDI = G*F - D*I;
	float DHEG = D*H - E*G;

	float denom = (A*EIHF + B*GFDI + C*DHEG);

	float beta = (J*EIHF + K*GFDI + L*DHEG) / denom;

	if (beta <= 0.0f || beta >= 1.0f)
	{
		return false;
	}

	float AKJB = A*K - J*B;
	float JCAL = J*C - A*L;
	float BLKC = B*L - K*C;

	float gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;
	if (gamma <= 0.0f || ((beta + gamma) >= 1.0f))
	{
		return false;
	}

	tval = -(F*AKJB + E*JCAL + D*BLKC) / denom;

	return (tval >= tmin && tval <= tmax);
}