#include "pch.h"
#include "Camera.hpp"

namespace RedLightbulb
{
	void Camera::setPerspective(float fov, float aspect, float near, float far)
	{
		m_proj = Math::createPerspectiveMatrix(fov, aspect, near, far);
		m_projInv = m_proj.inverse();

		m_updateMatrices = true;
	}
	void Camera::lookAt(const Vec3f& position, const Vec3f& target, const Vec3f& up)
	{
		Vec3f f = (target - position).normalized();
		Vec3f r = up.cross(f).normalized();
		Vec3f u = f.cross(r);

		m_viewInv <<
			r.x(), u.x(), f.x(), position.x(),
			r.y(), u.y(), f.y(), position.y(),
			r.z(), u.z(), f.z(), position.z(),
			0.0f, 0.0f, 0.0f, 1.0f;

		m_view = m_viewInv.inverse();

		Mat3f lookAtMatrix3 = m_viewInv.block(0, 0, 3, 3);
		m_rotation = lookAtMatrix3;
	}

	void Camera::addLocalPosition(const Vec3f& position)
	{
		updateBasis();

		Vec3f relativeMovement = position.x() * getRight() + position.y() * getUp() + position.z() * getForward();

		m_viewInv.col(3).head<3>() += relativeMovement;

		m_updateMatrices = true;
	}
	void Camera::addWorldPosition(const Vec3f& position)
	{
		m_viewInv.col(3).head<3>() += position;

		m_updateMatrices = true;
	}
	void Camera::setWorldPosition(const Vec3f& position)
	{
		m_viewInv.col(3).head<3>() = position;

		m_updateMatrices = true;
	}
	void Camera::addLocalRotation(const Quat& rotation, bool rollEnabled)
	{
		Vec3f rotationEuler = rotation.toRotationMatrix().eulerAngles(0, 1, 2);
		addLocalRotation(rotationEuler);
	}
	void Camera::addLocalRotation(const Vec3f& rotation, bool rollEnabled)
	{
		Vec3f right = getRight();
		Vec3f up = getUp();
		Vec3f forward = getForward();

		if (rollEnabled)
		{
			m_rotation *= Quat(Eigen::AngleAxisf(rotation.z(), forward));
			m_rotation *= Quat(Eigen::AngleAxisf(rotation.x(), right));
			m_rotation *= Quat(Eigen::AngleAxisf(rotation.y(), up));
		}
		else
		{
			m_rotation = Quat(Eigen::AngleAxisf(rotation.x(), right)) * Quat(Eigen::AngleAxisf(rotation.y(), Vec3f(0.0f, 1.0f, 0.0f))) * m_rotation;
			//m_rotation *= Quat(Eigen::AngleAxisf(rotation.y(), Vec3f(0.0f, 1.0f, 0.0f)));
		}

		m_rotation.normalize();

		m_updateBasis = true;
		m_updateMatrices = true;
	}
	void Camera::addWorldRotation(const Quat& rotation)
	{
		m_rotation *= rotation;

		m_updateBasis = true;
		m_updateMatrices = true;
	}
	void Camera::addWorldRotation(const Vec3f& rotation)
	{
		m_rotation *= Quat(Eigen::AngleAxisf(rotation.z(), Vec3f(0.0f, 0.0f, 1.0f)));
		m_rotation *= Quat(Eigen::AngleAxisf(rotation.x(), Vec3f(1.0f, 0.0f, 0.0f)));
		m_rotation *= Quat(Eigen::AngleAxisf(rotation.y(), Vec3f(0.0f, 1.0f, 0.0f)));

		m_updateBasis = true;
		m_updateMatrices = true;
	}
	void Camera::setWorldRotation(const Quat& rotation)
	{
		m_rotation = rotation;

		m_updateBasis = true;
		m_updateMatrices = true;
	}
	void Camera::setWorldRotation(const Vec3f& rotation)
	{
		m_rotation = Quat(Eigen::AngleAxisf(rotation.z(), Vec3f(0.0f, 0.0f, 1.0f)));
		m_rotation *= Quat(Eigen::AngleAxisf(rotation.x(), Vec3f(1.0f, 0.0f, 0.0f)));
		m_rotation *= Quat(Eigen::AngleAxisf(rotation.y(), Vec3f(0.0f, 1.0f, 0.0f)));

		m_rotation.normalize();

		m_updateBasis = true;
		m_updateMatrices = true;
	}
	Vec3f Camera::getPosition() const
	{
		return m_viewInv.col(3).head<3>();
	}
	Vec3f Camera::getRight() const
	{
		return m_viewInv.col(0).head<3>();
	}
	Vec3f Camera::getUp() const
	{
		return m_viewInv.col(1).head<3>();
	}
	Vec3f Camera::getForward() const
	{
		return m_viewInv.col(2).head<3>();
	}
	const Mat4f& Camera::getView() const
	{
		return m_view;
	}
	const Mat4f& Camera::getViewInv() const
	{
		return m_viewInv;
	}
	const Mat4f& Camera::getProj() const
	{
		return m_proj;
	}
	const Mat4f& Camera::getProjInv() const
	{
		return m_projInv;
	}
	const Mat4f& Camera::getViewProj() const
	{
		return m_viewProj;
	}
	const Mat4f& Camera::getViewProjInv() const
	{
		return m_viewProjInv;
	}
	void Camera::update()
	{
		m_rotation.normalize();

		updateBasis();
		updateMatrices();
	}
	void Camera::updateBasis()
	{
		if (m_updateBasis)
		{
			m_updateBasis = false;

			Mat3f rotationMat = m_rotation.toRotationMatrix();

			m_viewInv.block(0, 0, 3, 3) = rotationMat;
		}
	}
	void Camera::updateMatrices()
	{
		if (m_updateMatrices)
		{
			m_updateMatrices = false;

			updateBasis();

			m_view = m_viewInv.inverse();

			m_viewProj = m_proj * m_view;
			m_viewProjInv = m_viewInv * m_projInv;
		}
	}
}