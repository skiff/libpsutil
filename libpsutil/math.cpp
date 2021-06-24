#include <fastmath.h>
#include "math.hpp"

namespace libpsutil
{
	namespace math
	{
		namespace
		{
			uint32_t rand_next = 1;
			uint32_t rand_r(uint32_t* ctx)
			{
				return ((*ctx = *ctx * 0x41C64E6D + 0x3039) % ((uint32_t)0x7FFFFFFF + 1));
			}
		}

		int atoi(char* str)
		{
			int32_t res = 0;
			for (auto i = 0; str[i] != '\0'; ++i)
			{
				res = res * 10 + str[i] - '0';
			}

			return res;
		}

		float atof(char* str)
		{
			float rez = 0, fact = 1;
			if (*str == '-')
			{
				str++;
				fact = -1;
			}

			for (int32_t point_seen = 0; *str; str++)
			{
				if (*str == '.')
				{
					point_seen = 1;
					continue;
				}

				int32_t d = *str - '0';
				if (d >= 0 && d <= 9)
				{
					if (point_seen) fact /= 10.0f;
					rez = rez * 10.0f + (float)d;
				}
			}

			return rez * fact;
		}

		void srand(uint32_t seed)
		{
			rand_next = seed;
		}

		uint32_t rand()
		{
			return rand_r(&rand_next);
		}

		vec2_t::vec2_t()
		{
			this->x = this->y = 0;
		}

		vec2_t::vec2_t(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		vec2_t::vec2_t(float vec[2])
		{
			if (vec != 0)
			{
				this->x = vec[0];
				this->y = vec[1];
			}
			else
			{
				this->x = this->y = 0;
			}
		}

		vec2_t vec2_t::operator+(const vec2_t vec)
		{
			return vec2_t(this->x + vec.x, this->y + vec.y);
		}

		vec2_t vec2_t::operator+(const float* vec)
		{
			return vec2_t(this->x + vec[0], this->y + vec[1]);
		}

		vec2_t vec2_t::operator-(const vec2_t vec)
		{
			return vec2_t(this->x - vec.x, this->y - vec.y);
		}

		vec2_t vec2_t::operator-(const float* vec)
		{
			return vec2_t(this->x - vec[0], this->y - vec[1]);
		}

		vec2_t vec2_t::operator-() const
		{
			return vec2_t(-x, -y);
		}

		vec2_t vec2_t::operator*(const vec2_t vec)
		{
			return vec2_t(this->x * vec.x, this->y * vec.y);
		}

		vec2_t vec2_t::operator*(const float scalar)
		{
			return vec2_t(this->x * scalar, this->y * scalar);
		}

		void vec2_t::operator-=(const vec2_t vec)
		{
			this->x -= vec.x;
			this->y -= vec.y;
		}

		void vec2_t::operator+=(const vec2_t vec)
		{
			this->x += vec.x;
			this->y += vec.y;
		}

		void vec2_t::operator*=(const vec2_t vec)
		{
			this->x *= vec.x;
			this->y *= vec.y;
		}

		void vec2_t::operator*=(const float scalar)
		{
			this->x *= scalar;
			this->y *= scalar;
		}

		bool vec2_t::operator==(const vec2_t vec)
		{
			return (this->x == vec.x && this->y == vec.y);
		}

		bool vec2_t::operator==(const float value)
		{
			return (this->x == value && this->y == value);
		}

		bool vec2_t::operator!=(const vec2_t vec)
		{
			return !operator==(vec);
		}

		bool vec2_t::operator!=(const float value)
		{
			return !operator==(value);
		}

		vec2_t::operator float* ()
		{
			return (float*)&this[0];
		}

		vec3_t::vec3_t()
		{
			this->x = this->y = 0;
		}

		vec3_t::vec3_t(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		vec3_t::vec3_t(float vec[3])
		{
			if (vec != 0)
			{
				this->x = vec[0];
				this->y = vec[1];
				this->z = vec[2];
			}
			else
			{
				this->x = this->y = this->z = 0;
			}
		}

		vec3_t vec3_t::operator+(const vec3_t vec)
		{
			return vec3_t(this->x + vec.x, this->y + vec.y, this->z + vec.z);
		}

		vec3_t vec3_t::operator+(const float* vec)
		{
			return vec3_t(this->x + vec[0], this->y + vec[1], this->z + vec[2]);
		}

		vec3_t vec3_t::operator-(const vec3_t vec)
		{
			return vec3_t(this->x - vec.x, this->y - vec.y, this->z - vec.z);
		}

		vec3_t vec3_t::operator-(const float* vec)
		{
			return vec3_t(this->x - vec[0], this->y - vec[1], this->z - vec[2]);
		}

		vec3_t vec3_t::operator-() const
		{
			return vec3_t(-x, -y, -z);
		}

		vec3_t vec3_t::operator*(const vec3_t vec)
		{
			return vec3_t(this->x * vec.x, this->y * vec.y, this->z * vec.z);
		}

		vec3_t vec3_t::operator*(const float scalar)
		{
			return vec3_t(this->x * scalar, this->y * scalar, this->z * scalar);
		}

		void vec3_t::operator-=(const vec3_t vec)
		{
			this->x -= vec.x;
			this->y -= vec.y;
			this->z -= vec.z;
		}

		void vec3_t::operator+=(const vec3_t vec)
		{
			this->x += vec.x;
			this->y += vec.y;
			this->z += vec.z;
		}

		void vec3_t::operator*=(const vec3_t vec)
		{
			this->x *= vec.x;
			this->y *= vec.y;
			this->z *= vec.z;
		}

		void vec3_t::operator*=(const float scalar)
		{
			this->x *= scalar;
			this->y *= scalar;
			this->z *= scalar;
		}

		bool vec3_t::operator==(const vec3_t vec)
		{
			return (this->x == vec.x && this->y == vec.y && this->z == vec.z);
		}

		bool vec3_t::operator==(const float value)
		{
			return (this->x == value && this->y == value && this->z == value);
		}

		bool vec3_t::operator!=(const vec3_t vec)
		{
			return !operator==(vec);
		}

		bool vec3_t::operator!=(const float value)
		{
			return !operator==(value);
		}

		vec3_t::operator float* ()
		{
			return (float*)&this[0];
		}

		vec3_t vec3_t::forward(float x)
		{
			float div = M_PI / 180.0f;

			float angle = this->y * div;
			float sy = sinf(angle);
			float cy = cosf(angle);

			angle = this->x * div;
			float sp = sinf(angle);
			float cp = cosf(angle);

			return vec3_t(cp * cy * x, cp * sy * x, -sp * x);
		}

		vec3_t vec3_t::normalize()
		{
			vec3_t newvec;
			newvec.x = this->x / length();
			newvec.y = this->y / length();
			newvec.z = this->z / length();
			return newvec;
		}

		float vec3_t::distance(vec3_t vec)
		{
			float _x = this->x - vec.x;
			float _y = this->y - vec.y;
			float _z = this->z - vec.z;
			return f_sqrtf((_x * _x) + (_y * _y) + (_z * _z));
		}

		float vec3_t::length()
		{
			return (float)f_sqrtf(x * x + y * y + z * z);
		}

		void vec3_t::vectors(vec3_t* forward, vec3_t* right, vec3_t* up)
		{
			float angle;
			float sr, sp, sy, cr, cp, cy;

			angle = this->y * (M_PI * 2.0f / 360.0f);
			sy = sinf(angle);
			cy = cosf(angle);

			angle = this->x * (M_PI * 2.0f / 360.0f);
			sp = sinf(angle);
			cp = cosf(angle);

			angle = this->z * (M_PI * 2.0f / 360.0f);
			sr = sinf(angle);
			cr = cosf(angle);

			if (forward)
			{
				forward->x = cp * cy;
				forward->y = cp * sy;
				forward->z = -sp;
			}
			if (right)
			{
				right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
				right->y = (-1 * sr * sp * sy + -1 * cr * cy);
				right->z = -1 * sr * cp;
			}
			if (up)
			{
				up->x = (cr * sp * cy + -sr * -sy);
				up->y = (cr * sp * sy + -sr * cy);
				up->z = cr * cp;
			}
		}

		vec4_t::vec4_t()
		{
			this->x = this->y = 0;
		}

		vec4_t::vec4_t(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		vec4_t::vec4_t(float vec[4])
		{
			if (vec != 0)
			{
				this->x = vec[0];
				this->y = vec[1];
				this->z = vec[2];
				this->w = vec[3];
			}
			else
			{
				this->x = this->y = this->z = this->w = 0;
			}
		}

		vec4_t vec4_t::operator+(const vec4_t vec)
		{
			return vec4_t(this->x + vec.x, this->y + vec.y, this->z + vec.z, this->w + vec.w);
		}

		vec4_t vec4_t::operator+(const float* vec)
		{
			return vec4_t(this->x + vec[0], this->y + vec[1], this->z + vec[2], this->w + vec[3]);
		}

		vec4_t vec4_t::operator-(const vec4_t vec)
		{
			return vec4_t(this->x - vec.x, this->y - vec.y, this->z - vec.z, this->w - vec.w);
		}

		vec4_t vec4_t::operator-(const float* vec)
		{
			return vec4_t(this->x - vec[0], this->y - vec[1], this->z - vec[2], this->w - vec[3]);
		}

		vec4_t vec4_t::operator-() const
		{
			return vec4_t(-x, -y, -z, -w);
		}

		vec4_t vec4_t::operator*(const vec4_t vec)
		{
			return vec4_t(this->x * vec.x, this->y * vec.y, this->z * vec.z, this->w * vec.w);
		}

		vec4_t vec4_t::operator*(const float scalar)
		{
			return vec4_t(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
		}

		void vec4_t::operator-=(const vec4_t vec)
		{
			this->x -= vec.x;
			this->y -= vec.y;
			this->z -= vec.z;
			this->w -= vec.w;
		}

		void vec4_t::operator+=(const vec4_t vec)
		{
			this->x += vec.x;
			this->y += vec.y;
			this->z += vec.z;
			this->w += vec.w;
		}

		void vec4_t::operator*=(const vec4_t vec)
		{
			this->x *= vec.x;
			this->y *= vec.y;
			this->z *= vec.z;
			this->w *= vec.w;
		}

		void vec4_t::operator*=(const float scalar)
		{
			this->x *= scalar;
			this->y *= scalar;
			this->z *= scalar;
			this->w *= scalar;
		}

		bool vec4_t::operator==(const vec4_t vec)
		{
			return (this->x == vec.x && this->y == vec.y && this->z == vec.z && this->w == vec.w);
		}

		bool vec4_t::operator==(const float value)
		{
			return (this->x == value && this->y == value && this->z == value && this->w == value);
		}

		bool vec4_t::operator!=(const vec4_t vec)
		{
			return !operator==(vec);
		}

		bool vec4_t::operator!=(const float value)
		{
			return !operator==(value);
		}

		vec4_t::operator float* ()
		{
			return (float*)&this[0];
		}
	}
}