#pragma once

#include "BaseModel.h"

#define CAR_CHASSIS_MODEL	("model.car.chassis")
#define CAR_CHASSIS_TEXTURE ("texture.car.chassis")

// FRONT WINDOWSHIELD
#define CAR_CHASSIS_FRONT_WINDSHIELD_START_X	(0.75f)
#define CAR_CHASSIS_FRONT_WINDSHIELD_START_Y	(1.f)
#define CAR_CHASSIS_FRONT_WINDSHIELD_START_Z	(0.75f)

#define CAR_CHASSIS_FRONT_WINDSHIELD_END_X		(0.8f)
#define CAR_CHASSIS_FRONT_WINDSHIELD_END_Y		(0.5f)
#define CAR_CHASSIS_FRONT_WINDSHIELD_END_Z		(1.25f)

// FRONT BUMPER
#define CAR_CHASSIS_FRONT_BUMPER_START_X	(0.8f)
#define CAR_CHASSIS_FRONT_BUMPER_START_Y	(0.5f)
#define CAR_CHASSIS_FRONT_BUMPER_START_Z	(2.5f)

#define CAR_CHASSIS_FRONT_BUMPER_END_X		(0.8f)
#define CAR_CHASSIS_FRONT_BUMPER_END_Y		(0.f)
#define CAR_CHASSIS_FRONT_BUMPER_END_Z		(2.5f)

// REAR WINDSHIELD
#define CAR_CHASSIS_REAR_WINDSHIELD_START_X		(0.75f)
#define CAR_CHASSIS_REAR_WINDSHIELD_START_Y		(1.f)
#define CAR_CHASSIS_REAR_WINDSHIELD_START_Z		(-0.5f)

#define CAR_CHASSIS_REAR_WINDSHIELD_END_X		(0.8f)
#define CAR_CHASSIS_REAR_WINDSHIELD_END_Y		(0.5f)
#define CAR_CHASSIS_REAR_WINDSHIELD_END_Z		(-0.75f)

// REAR BUMPER
#define CAR_CHASSIS_REAR_BUMPER_START_X		(0.8f)
#define CAR_CHASSIS_REAR_BUMPER_START_Y		(0.5f)
#define CAR_CHASSIS_REAR_BUMPER_START_Z		(-1.25f)

#define CAR_CHASSIS_REAR_BUMPER_END_X		(0.8f)
#define CAR_CHASSIS_REAR_BUMPER_END_Y		(0.f)
#define CAR_CHASSIS_REAR_BUMPER_END_Z		(-1.25f)

class CarChassisModel : public BaseModel {
public:
	ModelData GetModelData() override {
		std::vector<ModelDataPart> parts;

		// the chassis
		{
			// front windshield
			float fwsx = CAR_CHASSIS_FRONT_WINDSHIELD_START_X;
			float fwsy = CAR_CHASSIS_FRONT_WINDSHIELD_START_Y;
			float fwsz = CAR_CHASSIS_FRONT_WINDSHIELD_START_Z;

			float fwex = CAR_CHASSIS_FRONT_WINDSHIELD_END_X;
			float fwey = CAR_CHASSIS_FRONT_WINDSHIELD_END_Y;
			float fwez = CAR_CHASSIS_FRONT_WINDSHIELD_END_Z;

			// front bumper
			float fbsx = CAR_CHASSIS_FRONT_BUMPER_START_X;
			float fbsy = CAR_CHASSIS_FRONT_BUMPER_START_Y;
			float fbsz = CAR_CHASSIS_FRONT_BUMPER_START_Z;

			float fbex = CAR_CHASSIS_FRONT_BUMPER_END_X;
			float fbey = CAR_CHASSIS_FRONT_BUMPER_END_Y;
			float fbez = CAR_CHASSIS_FRONT_BUMPER_END_Z;

			// rear windshield
			float rwsx = CAR_CHASSIS_REAR_WINDSHIELD_START_X;
			float rwsy = CAR_CHASSIS_REAR_WINDSHIELD_START_Y;
			float rwsz = CAR_CHASSIS_REAR_WINDSHIELD_START_Z;

			float rwex = CAR_CHASSIS_REAR_WINDSHIELD_END_X;
			float rwey = CAR_CHASSIS_REAR_WINDSHIELD_END_Y;
			float rwez = CAR_CHASSIS_REAR_WINDSHIELD_END_Z;

			// rear bumper
			float rbsx = CAR_CHASSIS_REAR_BUMPER_START_X;
			float rbsy = CAR_CHASSIS_REAR_BUMPER_START_Y;
			float rbsz = CAR_CHASSIS_REAR_BUMPER_START_Z;

			float rbex = CAR_CHASSIS_REAR_BUMPER_END_X;
			float rbey = CAR_CHASSIS_REAR_BUMPER_END_Y;
			float rbez = CAR_CHASSIS_REAR_BUMPER_END_Z;

			std::vector<glm::vec3> vertices = {
				// ROOF
				{ -fwsx, fwsy, fwsz },
				{  fwsx, fwsy, fwsz },
				{  rwsx, rwsy, rwsz },
				{ -rwsx, rwsy, rwsz },

				// FRONT WINDSHIELD
				{ -fwex, fwey, fwez },
				{  fwex, fwey, fwez },
				{  fwsx, fwsy, fwsz },
				{ -fwsx, fwsy, fwsz },

				// HOOD
				{ -fbsx, fbsy, fbsz },
				{  fbsx, fbsy, fbsz },
				{  fwex, fwey, fwez },
				{ -fwex, fwey, fwez },

				// FRONT BUMPER
				{ -fbex, fbey, fbez },
				{  fbex, fbey, fbez },
				{  fbsx, fbsy, fbsz },
				{ -fbsx, fbsy, fbsz },

				// REAR WINDSHIELD
				{ -rwsx, rwsy, rwsz },
				{  rwsx, rwsy, rwsz },
				{  rwex, rwey, rwez },
				{ -rwex, rwey, rwez },

				// TRUNK
				{ -rwex, rwey, rwez },
				{  rwex, rwey, rwez },
				{  rbsx, rbsy, rbsz },
				{ -rbsx, rbsy, rbsz },

				// REAR BUMPER
				{ -rbsx, rbsy, rbsz },
				{  rbsx, rbsy, rbsz },
				{  rbex, rbey, rbez },
				{ -rbex, rbey, rbez },

				// FLOOR
				{  fbex, fbey, fbez },
				{ -fbex, fbey, fbez },
				{ -rbex, rbey, rbez },
				{  rbex, rbey, rbez },

				// LEFT SIDE
				{ -fbex, fbey, fbez },
				{ -fbsx, fbsy, fbsz },
				{ -fwex, fwey, fwez },
				{ -fwsx, fwsy, fwsz },
				{ -rwsx, rwsy, rwsz },
				{ -rwex, rwey, rwez },
				{ -rbsx, rbsy, rbsz },
				{ -rbex, rbey, rbez },

				// RIGHT SIDE
				{  fbex, fbey, fbez },
				{  fbsx, fbsy, fbsz },
				{  fwex, fwey, fwez },
				{  fwsx, fwsy, fwsz },
				{  rwsx, rwsy, rwsz },
				{  rwex, rwey, rwez },
				{  rbsx, rbsy, rbsz },
				{  rbex, rbey, rbez },
			};

			std::vector<glm::vec3> normalsBase = {
				 AXIS_OY,			// ROOF
				 AXIS_OY + AXIS_OZ,	// FRONT WINDSHIELD
				 AXIS_OY,			// HOOD
				 AXIS_OZ,			// FRONT BUMPER
				 AXIS_OY - AXIS_OZ,	// REAR WINDSHIELD
				 AXIS_OY,			// TRUNK
				-AXIS_OZ,			// REAR BUMPER
				-AXIS_OY,			// FLOOR
				 AXIS_OX,			// LEFT SIDE
				-AXIS_OX			// RIGHT SIDE
			};

			std::vector<glm::vec3> normals;
			for (int i = 0; i < normalsBase.size(); i++)
				for (int j = 1; j <= (i >= normalsBase.size() - 2 ? 8 : 4); j++)
					normals.push_back(glm::normalize(normalsBase[i]));

			std::vector<glm::vec2> textureCoords = {
				// ROOF
				{ 0.50f, 0.25f },
				{ 0.75f, 0.25f },
				{ 0.75f, 0.75f },
				{ 0.50f, 0.75f },

				// FRONT WINDSHIELD
				{ 0.50f, 0.00f },
				{ 0.75f, 0.00f },
				{ 0.75f, 0.25f },
				{ 0.50f, 0.25f },

				// HOOD
				{ 0.125f, 0.000f },
				{ 0.375f, 0.000f },
				{ 0.375f, 0.250f },
				{ 0.125f, 0.250f },

				// FRONT BUMPER
				{ 0.75f, 0.00f },
				{ 1.00f, 0.00f },
				{ 1.00f, 0.25f },
				{ 0.75f, 0.25f },

				// REAR WINDSHIELD
				{ 0.50f, 0.75f },
				{ 0.75f, 0.75f },
				{ 0.75f, 1.00f },
				{ 0.50f, 1.00f },

				// TRUNK
				{ 0.125f, 0.750f },
				{ 0.375f, 0.750f },
				{ 0.375f, 1.000f },
				{ 0.125f, 1.000f },

				// REAR BUMPER
				{ 0.75f, 0.75f },
				{ 1.00f, 0.75f },
				{ 1.00f, 1.00f },
				{ 0.75f, 1.00f },

				// FLOOR
				{ 0.75f, 0.25f },
				{ 1.00f, 0.25f },
				{ 1.00f, 0.75f },
				{ 0.75f, 0.75f },

				// LEFT SIDE
				{ 0.000f, 0.000f },
				{ 0.125f, 0.000f },
				{ 0.125f, 0.250f },
				{ 0.250f, 0.250f },
				{ 0.250f, 0.750f },
				{ 0.125f, 0.750f },
				{ 0.125f, 1.000f },
				{ 0.000f, 1.000f },

				// RIGHT SIDE
				{ 0.500f, 0.000f },
				{ 0.375f, 0.000f },
				{ 0.375f, 0.250f },
				{ 0.250f, 0.250f },
				{ 0.250f, 0.750f },
				{ 0.375f, 0.750f },
				{ 0.375f, 1.000f },
				{ 0.500f, 1.000f },
			};

			std::vector<unsigned short> indices = {
				// ROOF
				0, 1, 2,
				0, 2, 3,

				// FRONT WINDSHIELD
				4, 5, 6,
				4, 6, 7,

				// HOOD
				8, 9, 10,
				8, 10, 11,

				// FRONT BUMPER
				12, 13, 14,
				12, 14, 15,

				// REAR WINDSHIELD
				16, 17, 18,
				16, 18, 19,

				// TRUNK
				20, 21, 22,
				20, 22, 23,

				// REAR BUMPER
				24, 25, 26,
				24, 26, 27,

				// FLOOR
				28, 29, 30,
				28, 30, 31,

				// LEFT SIDE BOTTOM HALF
				32, 33, 34,
				32, 34, 37,
				32, 37, 38,
				32, 38, 39,

				// LEFT SIDE UPPER HALF
				34, 35, 36,
				34, 36, 37,

				// RIGHT SIDE BOTTOM HALF
				40, 41, 42,
				40, 42, 45,
				40, 45, 46,
				40, 46, 47,

				// RIGHT SIDE UPPER HALF
				42, 43, 44,
				42, 44, 45
			};

			std::string name = CAR_CHASSIS_MODEL;
			int primitive = GL_TRIANGLES;

			parts.push_back(ModelDataPart(vertices, normals, textureCoords, indices, name, primitive));
		}

		return ModelData(parts);
	}
};