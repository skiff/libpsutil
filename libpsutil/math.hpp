#pragma once
#include <sys/prx.h>

namespace libpsutil
{
	namespace math
	{
		int atoi(char* str);
		float atof(char* str);

		void srand(uint32_t seed);
		uint32_t rand();

		class vec2_t
		{
		public:
			float x, y;

			vec2_t();
			vec2_t(float x, float y);
			vec2_t(float vec[2]);

			vec2_t operator+(const vec2_t vec);
			vec2_t operator+(const float* vec);
			vec2_t operator-(const vec2_t vec);
			vec2_t operator-(const float* vec);
			vec2_t operator-() const;
			vec2_t operator*(const vec2_t vec);
			vec2_t operator*(const float scalar);

			void operator-=(const vec2_t vec);
			void operator+=(const vec2_t vec);
			void operator*=(const vec2_t vec);
			void operator*=(const float scalar);

			bool operator==(const vec2_t vec);
			bool operator==(const float value);
			bool operator!=(const vec2_t vec);
			bool operator!=(const float value);

			operator float* ();
		};

		class vec3_t
		{
		public:
			float x, y, z;

			vec3_t();
			vec3_t(float x, float y, float z);
			vec3_t(float vec[3]);

			vec3_t operator+(const vec3_t vec);
			vec3_t operator+(const float* vec);
			vec3_t operator-(const vec3_t vec);
			vec3_t operator-(const float* vec);
			vec3_t operator-() const;
			vec3_t operator*(const vec3_t vec);
			vec3_t operator*(const float scalar);

			void operator-=(const vec3_t vec);
			void operator+=(const vec3_t vec);
			void operator*=(const vec3_t vec);
			void operator*=(const float scalar);

			bool operator==(const vec3_t vec);
			bool operator==(const float value);
			bool operator!=(const vec3_t vec);
			bool operator!=(const float value);

			operator float* ();

			vec3_t forward(float x = 1.0f);
			vec3_t normalize();
			float distance(vec3_t vec);
			float length();
			void vectors(vec3_t* forward, vec3_t* right, vec3_t* up);
		};

		class vec4_t
		{
		public:
			float x, y, z, w;

			vec4_t();
			vec4_t(float x, float y, float z, float w);
			vec4_t(float vec[4]);

			vec4_t operator+(const vec4_t vec);
			vec4_t operator+(const float* vec);
			vec4_t operator-(const vec4_t vec);
			vec4_t operator-(const float* vec);
			vec4_t operator-() const;
			vec4_t operator*(const vec4_t vec);
			vec4_t operator*(const float scalar);

			void operator-=(const vec4_t vec);
			void operator+=(const vec4_t vec);
			void operator*=(const vec4_t vec);
			void operator*=(const float scalar);

			bool operator==(const vec4_t vec);
			bool operator==(const float value);
			bool operator!=(const vec4_t vec);
			bool operator!=(const float value);

			operator float* ();
		};
	}
}