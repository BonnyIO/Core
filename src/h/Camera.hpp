#pragma once

#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_float4x4.hpp>

namespace Core {

	class Camera {

	public:

		enum class ProjectionMode {

			Perspective,
			Orthographic
		};

		Camera(const glm::vec3& position = { 0, 0, 0 }, const glm::vec3& rotation = { 0, 0, 0 }, const ProjectionMode projection_mode = ProjectionMode::Perspective);

		void set_position(const glm::vec3& position);
		void set_rotation(const glm::vec3& rotation);
		void set_position_rotation(const glm::vec3& position, const glm::vec3& rotation);
		void set_projection_mode(const ProjectionMode projection_mode);

		glm::mat4 getView() const { return m_View; }
		glm::mat4 getProjection() const { return m_Projection; }

	private:

		void updateView();
		void updateProjection();

		glm::vec3 m_position;
		glm::vec3 m_rotation;
		ProjectionMode m_projection_mode;

		glm::mat4 m_View;
		glm::mat4 m_Projection;
	};

}