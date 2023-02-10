#pragma once

#include <cmath>

namespace kat {
    namespace math {

        static inline constexpr double PI = 3.14159265358979323846;

        static inline constexpr double SQRT_2 = 1.41421356237309504880;
        static inline constexpr double SQRT_3 = 1.73205080756887729352;
        static inline constexpr double SQRT_5 = 2.23606797749978969640;

        static inline constexpr double PHI          = 1.61803398874989484820;
        static inline constexpr double GOLDEN_RATIO = PHI;

        static inline constexpr double SILVER_RATIO = 2.41421356237309504880;

        static inline constexpr double CUBE_ROOT_2    = 1.25992104989487316477;
        static inline constexpr double CUBE_ROOT_3    = 1.44224957030740838232;
        static inline constexpr double TWELFTH_ROOT_2 = 1.05946309435929526456;

        static inline constexpr double SUPER_GOLDEN_RATIO = 1.46557123187676802665;

        static inline constexpr double RADIAN = 0.0174532925199432957692;
        static inline constexpr double DEGREE = 57.2957795130823208768;

        static inline constexpr double EULER_NUMBER = 2.71828182845904523536;

        static inline constexpr double LOG_E  = 1.0;
        static inline constexpr double LOG_0  = -INFINITY;
        static inline constexpr double LOG_1  = 0.0;
        static inline constexpr double LOG_2  = 0.693147180559945309417;
        static inline constexpr double LOG_3  = 1.09861228866810969139;
        static inline constexpr double LOG_5  = 1.60943791243410037460;
        static inline constexpr double LOG_6  = 1.79175946922805500080;
        static inline constexpr double LOG_7  = 1.94591014905531330510;
        static inline constexpr double LOG_8  = 2.07944154167983592820;
        static inline constexpr double LOG_9  = 2.19722457733621938279;
        static inline constexpr double LOG_10 = 2.30258509299404568402;

        static inline constexpr double GOLDEN_ANGLE_DEGREES
            = 137.5077640500378546468;
        static inline constexpr double GOLDEN_ANGLE_RADIANS
            = GOLDEN_ANGLE_DEGREES * RADIAN;

        static inline constexpr double GRAVITY_ACCELERATION_ON_EARTH = 9.80665;
        static inline constexpr double GRAVITY_ACCELERATION_ON_MOON  = 1.622;
        static inline constexpr double GRAVITY_ACCELERATION_ON_MARS  = 3.711;

        static inline constexpr double AVERAGE_HUMAN_ACCELERATION_ON_EARTH = 1.5;
        static inline constexpr double AVERAGE_HUMAN_ACCELERATION_ON_MOON = 0.3;
        static inline constexpr double AVERAGE_HUMAN_ACCELERATION_ON_MARS = 0.5;

        static inline constexpr double LIGHT_SPEED = 299792458.0;

        static inline constexpr double PLANCK_CONSTANT = 6.62607015e-34;
        static inline constexpr double PLANCK_CONSTANT_REDUCED = PLANCK_CONSTANT / (2 * PI);

        static inline constexpr double ELECTRON_VOLT = 1.602176634e-19;
        static inline constexpr double ELECTRON_MASS = 9.1093837015e-31;

        static inline constexpr double BOLTZMANN_CONSTANT = 1.380649e-23;
        static inline constexpr double AVOGADRO_CONSTANT  = 6.02214076e23;
        static inline constexpr double GAS_CONSTANT = BOLTZMANN_CONSTANT * AVOGADRO_CONSTANT;
        static inline constexpr double FARADAY_CONSTANT = AVOGADRO_CONSTANT * ELECTRON_VOLT;

        static inline constexpr double UNIVERSAL_GRAVITATIONAL_CONSTANT = 6.67430e-11;

        static inline constexpr double ELECTRON_CHARGE = -1.602176634e-19;
        static inline constexpr double ELECTRON_MAGNETIC_MOMENT = -9.284764e-24;
        static inline constexpr double ELECTRON_G_FACTOR = -2.00231930436182;
        static inline constexpr double ELECTRON_GYROMAGNETIC_RATIO = 1.760859644e11;

        constexpr static inline double asRadians(const double& degrees)
        {
            return degrees * RADIAN;
        }

        constexpr static inline double asDegrees(const double& radians)
        {
            return radians * DEGREE;
        }

        static inline double sin(const double& v)
        {
            return std::sin(v);
        }

        static inline double cos(const double& v)
        {
            return std::cos(v);
        }

        static inline double tan(const double& v)
        {
            return std::tan(v);
        }

        static inline double asin(const double& v)
        {
            return std::asin(v);
        }

        static inline double acos(const double& v)
        {
            return std::acos(v);
        }

        static inline double atan(const double& v)
        {
            return std::atan(v);
        }

        static inline double atan2(const double& y, const double& x)
        {
            return std::atan2(y, x);
        }

        static inline double sinh(const double& v)
        {
            return std::sinh(v);
        }

        static inline double cosh(const double& v)
        {
            return std::cosh(v);
        }

        static inline double tanh(const double& v)
        {
            return std::tanh(v);
        }

        static inline double asinh(const double& v)
        {
            return std::asinh(v);
        }

        static inline double acosh(const double& v)
        {
            return std::acosh(v);
        }

        static inline double atanh(const double& v)
        {
            return std::atanh(v);
        }

        static inline double exp(const double& v)
        {
            return std::exp(v);
        }

        static inline double log(const double& v)
        {
            return std::log(v);
        }

        static inline double log10(const double& v)
        {
            return std::log10(v);
        }

        static inline double pow(const double& v, const double& p)
        {
            return std::pow(v, p);
        }

        static inline double sqrt(const double& v)
        {
            return std::sqrt(v);
        }

        static inline double cbrt(const double& v)
        {
            return std::cbrt(v);
        }

        static inline double hypot(const double& x, const double& y)
        {
            return std::hypot(x, y);
        }

        constexpr static inline double lerp(const double& a, const double& b,
                                            const double& t)
        {
            return a + (b - a) * t;
        }

        constexpr static inline double min(const double& a, const double& b)
        {
            return a < b ? a : b;
        }

        constexpr static inline double max(const double& a, const double& b)
        {
            return a > b ? a : b;
        }

        constexpr static inline double clamp(const double& v, const double& min,
                                             const double& max)
        {
            return v < min ? min : (v > max ? max : v);
        }

        constexpr static inline double saturate(const double& v)
        {
            return clamp(v, 0.0, 1.0);
        }

        constexpr static inline double smoothstep(const double& a,
                                                  const double& b,
                                                  const double& t)
        {
            double x = clamp((t - a) / (b - a), 0.0, 1.0);
            return x * x * (3.0 - 2.0 * x);
        }

        constexpr static inline double smootherstep(const double& a,
                                                    const double& b,
                                                    const double& t)
        {
            double x = clamp((t - a) / (b - a), 0.0, 1.0);
            return x * x * x * (x * (x * 6.0 - 15.0) + 10.0);
        }

        constexpr static inline double step(const double& a, const double& t)
        {
            return t < a ? 0.0 : 1.0;
        }

        constexpr static inline double sign(const double& v)
        {
            return v < 0.0 ? -1.0 : 1.0;
        }

        static inline double floor(const double& v)
        {
            return std::floor(v);
        }

        static inline double ceil(const double& v)
        {
            return std::ceil(v);
        }

        static inline double round(const double& v)
        {
            return std::round(v);
        }

        static inline double fract(const double& v)
        {
            return v - floor(v);
        }

        static inline double mod(const double& v, const double& m)
        {
            return v - floor(v / m) * m;
        }

        static inline double modf(const double& v, double* i)
        {
            return std::modf(v, i);
        }

        constexpr static inline double abs(const double& v)
        {
            return v < 0 ? -v : v;
        }

        static inline double fmod(const double& v, const double& m)
        {
            return std::fmod(v, m);
        }

        static inline double archimedes(const double& v)
        {
            return 2.0 * v * (1.0 - v / (2.0 * sqrt(1.0 + v * v)));
        }

        static inline std::pair<double, double>
            archimedes_sprial(const double& step, const double& a=5,
                              const double& b=1.8, const double& n=5)
        {
            return std::make_pair(a * cos(step * n) + b * cos(step * n * a / b),
                                  a * sin(step * n) - b * sin(step * n * a / b));
        }

		static inline std::pair<double, double>
            archimedes_sprial2(const double& step, const double& a=5,
                               const double& b=1.8, const double& n=5)
        {
            return std::make_pair(b * step * cos(step + a) * n,
                                  b * step * sin(step + a) * n);
        }

        static inline double erf(const double& v)
        {
            return std::erf(v);
        }

        static inline double easeInSine(const double& t)
        {
            return 1.0 - cos(t * PI / 2.0);
        }

        static inline double easeOutSine(const double& t)
        {
            return sin(t * PI / 2.0);
        }

        static inline double easeInOutSine(const double& t)
        {
            return -(cos(PI * t) - 1.0) / 2.0;
        }

        constexpr static inline double easeInQuad(const double& t)
        {
            return t * t;
        }

        constexpr static inline double easeOutQuad(const double& t)
        {
            return t * (2.0 - t);
        }

        constexpr static inline double easeInOutQuad(const double& t)
        {
            return t < 0.5 ? 2.0 * t * t : -1.0 + (4.0 - 2.0 * t) * t;
        }

        constexpr static inline double easeInCubic(const double& t)
        {
            return t * t * t;
        }

        constexpr static inline double easeOutCubic(double t)
        {
            return (t - 1) * t * t + 1.0;
        }

        constexpr static inline double easeInOutCubic(const double& t)
        {
            return t < 0.5
                ? 4.0 * t * t * t
                : (t - 1.0) * (2.0 * t - 2.0) * (2.0 * t - 2.0) + 1.0;
        }

        constexpr static inline double easeInQuart(const double& t)
        {
            return t * t * t * t;
        }

        constexpr static inline double easeOutQuart(double t)
        {
            return 1.0 - (t - 1) * t * t * t;
        }

        constexpr static inline double easeInOutQuart(double t)
        {
            return t < 0.5 ? 8.0 * t * t * t * t
                           : 1.0 - 8.0 * (t - 1) * t * t * t;
        }

        constexpr static inline double easeInQuint(const double& t)
        {
            return t * t * t * t * t;
        }

        constexpr static inline double easeOutQuint(double t)
        {
            return 1.0 + (t - 1) * t * t * t * t;
        }

        constexpr static inline double easeInOutQuint(double t)
        {
            return t < 0.5 ? 16.0 * t * t * t * t * t
                           : 1.0 + 16.0 * (t - 1) * t * t * t * t;
        }

        constexpr static inline double easeInExpo(const double& t)
        {
            return t == 0.0 ? 0.0 : pow(2.0, 10.0 * (t - 1.0));
        }

        constexpr static inline double easeOutExpo(const double& t)
        {
            return t == 1.0 ? 1.0 : 1.0 - pow(2.0, -10.0 * t);
        }

        constexpr static inline double easeInOutExpo(const double& t)
        {
            return t == 0.0 ? 0.0
                : t == 1.0  ? 1.0
                : t < 0.5   ? pow(2.0, 20.0 * t - 10.0) / 2.0
                            : (2.0 - pow(2.0, -20.0 * t + 10.0)) / 2.0;
        }

        static inline double easeInCirc(const double& t)
        {
            return 1.0 - sqrt(1.0 - (t * t));
        }

        static inline double easeOutCirc(const double& t)
        {
            return sqrt((2.0 - t) * t);
        }

        static inline double easeInOutCirc(const double& t)
        {
            return t < 0.5
                ? (1.0 - sqrt(1.0 - 4.0 * (t * t))) / 2.0
                : (sqrt(-((2.0 * t) - 3.0) * ((2.0 * t) - 1.0)) + 1.0) / 2.0;
        }

        static inline double easeInBack(const double& t)
        {
            return t * t * t - t * sin(t * PI);
        }

        static inline double easeOutBack(double t)
        {
            return 1.0 + (t - 1) * t * t + t * sin(t * PI);
        }

        static inline double easeInOutBack(double t)
        {
            return t < 0.5
                ? (2.0 * t * t * t - t * sin(2.0 * t * PI)) / 2.0
                : (2.0 + (t - 1) * t * t + t * sin(2.0 * t * PI)) / 2.0;
        }

        static inline double easeInElastic(const double& t)
        {
            return sin(13.0 * PI / 2.0 * t) * pow(2.0, 10.0 * (t - 1.0));
        }

        static inline double easeOutElastic(const double& t)
        {
            return sin(-13.0 * PI / 2.0 * (t + 1.0)) * pow(2.0, -10.0 * t)
                + 1.0;
        }

        static inline double easeInOutElastic(const double& t)
        {
            return t < 0.5
                ? sin(13.0 * PI * t) * pow(2.0, 20.0 * t - 10.0) / 2.0
                : sin(-13.0 * PI * (t - 0.5 + 1.0)) * pow(2.0, -20.0 * t + 10.0)
                        / 2.0
                    + 1.0;
        }

        static inline double easeInBounce(const double& t)
        {
            return pow(2.0, 6.0 * (t - 1.0)) * abs(sin(3.0 * PI * t));
        }

        static inline double easeOutBounce(const double& t)
        {
            return 1.0 - pow(2.0, -6.0 * t) * abs(cos(3.0 * PI * t));
        }

        static inline double easeInOutBounce(const double& t)
        {
            return t < 0.5
                ? 8.0 * pow(2.0, 8.0 * (t - 1.0)) * abs(sin(3.0 * PI * t))
                : 1.0 - 8.0 * pow(2.0, -8.0 * t) * abs(sin(3.0 * PI * t));
        }
    }
}
