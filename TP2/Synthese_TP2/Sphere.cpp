#include "Sphere.h"

Sphere::Sphere(const color3 &albedo, const SceneObjectType &type, const glm::vec3 &center, const float &radius) : SceneObject(albedo, type), m_center(center), m_radius(radius), m_radius2(radius * radius) {}

bool Sphere::intersect(const Ray &r, glm::vec3 &position, glm::vec3 &normal, float &t)
{
	//return glm::intersectRaySphere(r.m_origin, r.m_direction, m_center, m_radius, position, normal);
	//t = glm::distance2(r.m_origin, position);
	
	float t0, t1;

	glm::vec3 L = m_center - r.m_origin;
	float tca = glm::dot(L, r.m_direction);

	if (tca < 0) {
		return false;
	}

	float d2 = glm::dot(L, L) - tca * tca;

	if (d2 > m_radius2) {
		return false;
	}
	float thc = sqrt(m_radius2 - d2);

	t0 = tca - thc;
	t1 = tca + thc;

	if (t0 > t1) {
		std::swap(t0, t1);
	}

	if (t0 < 0) {
		t0 = t1;
		if (t0 < 0) {
			return false;
		}
	}

	t = t0;
	
	position = r.m_origin + t * r.m_direction;
	normal = glm::normalize(position - m_center);
	
	return true;
	
}