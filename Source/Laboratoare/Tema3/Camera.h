#pragma once

#include <include/glm.h>
#include <include/math.h>

#include "Globals.h"

#define CAMERA_INITIAL_POSITION					(glm::vec3(0, 0, 0))
#define CAMERA_INITIAL_FORWARD					(AXIS_OZ)
#define CAMERA_INITIAL_UP						(AXIS_OY)
#define CAMERA_INITIAL_RIGHT					(AXIS_OX)
#define CAMERA_INITIAL_3RD_PERSON_DISTANCE		(10.f)
#define CAMERA_INITIAL_3RD_PERSON_ROTATION_OX	(M_PI / 6)
#define CAMERA_INITIAL_THIRD_PERSON				(true)
#define CAMERA_SENSITIVITY_OX					(0.001f)
#define CAMERA_SENSITIVITY_OY					(0.001f)

namespace Student {

	class Camera {
	private:
		bool mouseRotating = false;

	public:
		Camera() {}

		~Camera() {}

		// Update camera
		void Set(const glm::vec3 position) {
			this->position = position;

			if (!mouseRotating) {
				this->forward = AXIS_OZ;
				this->up = AXIS_OY;
				this->right = glm::cross(forward, up);

				if (IsThirdPerson()) {
					TranslateForward(-distanceToTarget);
					RotateThirdPerson_OX(-CAMERA_INITIAL_3RD_PERSON_ROTATION_OX);
				}
			} else if (IsThirdPerson()) {
				TranslateForward(-distanceToTarget);
			}
			
		}

		void MoveForward(float distance)
		{
			position += glm::normalize(glm::vec3(forward.x, 0, forward.z)) * distance;
		}

		void TranslateForward(float distance)
		{
			position += glm::normalize(forward) * distance;
		}

		void TranslateUpward(float distance)
		{
			position += glm::normalize(up) * distance;
		}

		void TranslateRight(float distance)
		{
			position += glm::normalize(right) * distance;
		}

		void RotateFirstPerson_OX(float angle) {
			glm::vec4 newForward = glm::rotate(glm::mat4(1), angle, right) * glm::vec4(forward, 1);

			// Compute the new "forward" and "up" vectors
			forward = glm::normalize(glm::vec3(newForward));
			up = glm::cross(right, forward);
		}

		void RotateFirstPerson_OY(float angle) {
			glm::vec4 newForward = glm::rotate(glm::mat4(1), angle, AXIS_OY) * glm::vec4(forward, 1);
			glm::vec4 newRight = glm::rotate(glm::mat4(1), angle, AXIS_OY) * glm::vec4(right, 1);

			// Compute the new "forward", "right" and "up" vectors
			forward = glm::normalize(glm::vec3(newForward));
			right = glm::normalize(glm::vec3(newRight));
			up = glm::cross(right, forward);
		}

		void RotateFirstPerson_OZ(float angle) {
			glm::vec4 newUp = glm::rotate(glm::mat4(1), angle, forward) * glm::vec4(up, 1);

			// Compute the new "up" and "right" vectors
			up = glm::normalize(glm::vec3(newUp));
			right = glm::cross(forward, up);
		}

		void RotateThirdPerson_OX(float angle) {
			// Rotate the camera in Third Person mode - OX axis
			TranslateForward(distanceToTarget);
			RotateFirstPerson_OX(angle);
			TranslateForward(-distanceToTarget);
		}

		void RotateThirdPerson_OY(float angle) {
			// Rotate the camera in Third Person mode - OY axis
			TranslateForward(distanceToTarget);
			RotateFirstPerson_OY(angle);
			TranslateForward(-distanceToTarget);
		}

		void RotateThirdPerson_OZ(float angle) {
			// Rotate the camera in Third Person mode - OZ axis
			TranslateForward(distanceToTarget);
			RotateFirstPerson_OZ(angle);
			TranslateForward(-distanceToTarget);
		}

		glm::mat4 GetViewMatrix() {
			// Returns the View Matrix
			return glm::lookAt(position, position + forward, up);
		}

		glm::vec3 GetTargetPosition() {
			return position + forward * distanceToTarget;
		}

		glm::vec3 GetPosition() {
			return position;
		}

		void ToggleThirdPerson() {
			thirdPerson = !thirdPerson;
		}

		void SetThirdPerson(bool thirdPerson) {
			this->thirdPerson = thirdPerson;
		}

		bool IsThirdPerson() {
			return thirdPerson;
		}

		void SetDistanceToTarget(float distanceToTarget) {
			this->distanceToTarget = distanceToTarget;
		}

		void MouseRotate(glm::vec3 position, int deltaX, int deltaY) {
			mouseRotating = true;

			if (IsThirdPerson()) {
				this->position = position;
				TranslateForward(-distanceToTarget);
				RotateThirdPerson_OX(-deltaY * CAMERA_SENSITIVITY_OX);
				RotateThirdPerson_OY(-deltaX * CAMERA_SENSITIVITY_OY);
			} else {
				RotateFirstPerson_OX(-deltaY * CAMERA_SENSITIVITY_OX);
				RotateFirstPerson_OY(-deltaX * CAMERA_SENSITIVITY_OY);
			}
		}

		void StopMouseRotation(glm::vec3 position) {
			if (!mouseRotating)
				return;

			mouseRotating = false;

			Set(position);
		}

	public:
		glm::vec3 position	= CAMERA_INITIAL_POSITION;
		glm::vec3 forward	= CAMERA_INITIAL_FORWARD;
		glm::vec3 up		= CAMERA_INITIAL_UP;
		glm::vec3 right		= CAMERA_INITIAL_RIGHT;

		float distanceToTarget	= CAMERA_INITIAL_3RD_PERSON_DISTANCE;

		bool thirdPerson = CAMERA_INITIAL_THIRD_PERSON;

	};
}