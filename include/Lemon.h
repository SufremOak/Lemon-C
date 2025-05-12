#ifndef LEMON_H
#define LEMON_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
#include <cmath>
#include <limits>
#include <cassert>
#include <memory>

namespace Lemon {
    // Constants
    const double PI = 3.14159265358979323846;
    const double EPSILON = 1e-9;
    const double INF = std::numeric_limits<double>::infinity();

    // Type definitions
    using Point = std::pair<double, double>;
    using Line = std::pair<Point, Point>;
    using Polygon = std::vector<Point>;

    // Function declarations
    double distance(const Point& a, const Point& b);
    double cross(const Point& a, const Point& b);
    bool isPointInPolygon(const Point& p, const Polygon& poly);

    namespace Io {
        void Log(const std::string& message) {
            std::cout << message << std::endl;
        }

        void Error(const std::string& message) {
            std::cerr << "Error: " << message << std::endl;
        }
        void Warning(const std::string& message) {
            std::cerr << "Warning: " << message << std::endl;
        }

        struct expr {
            std::string str;
            expr(const std::string& s) : str(s) {}
            friend std::ostream& operator<<(std::ostream& os, const expr& e) {
                os << e.str;
                return os;
            };
        };
    }

    namespace Math {
        double gcd(double a, double b) {
            while (b != 0) {
                double t = b;
                b = std::fmod(a, b);
                a = t;
            }
            return a;
        }

        double lcm(double a, double b) {
            return (a * b) / gcd(a, b);
        };
    }
    namespace Geometry {
        double distance(const Point& a, const Point& b) {
            return std::sqrt(std::pow(a.first - b.first, 2) + std::pow(a.second - b.second, 2));
        }

        double cross(const Point& a, const Point& b) {
            return a.first * b.second - a.second * b.first;
        }

        bool isPointInPolygon(const Point& p, const Polygon& poly) {
            int n = poly.size();
            bool inside = false;
            for (int i = 0, j = n - 1; i < n; j = i++) {
                if ((poly[i].second > p.second) != (poly[j].second > p.second) &&
                    (p.first < (poly[j].first - poly[i].first) * (p.second - poly[i].second) / (poly[j].second - poly[i].second) + poly[i].first)) {
                    inside = !inside;
                }
            }
            return inside;
        }
    }
    namespace Debug {
        void assertCondition(bool condition, const std::string& message) {
            if (!condition) {
                Io::Error(message);
                assert(condition);
            }
        }

        void assertEqual(double a, double b, const std::string& message) {
            if (std::abs(a - b) > EPSILON) {
                Io::Error(message);
                assert(false);
            }
        }
    }
    namespace Utils {
        std::string toString(double value) {
            return std::to_string(value);
        }

        std::string toString(int value) {
            return std::to_string(value);
        }

        std::string toString(const Point& p) {
            return "(" + toString(p.first) + ", " + toString(p.second) + ")";
        }

        std::string toString(const Polygon& poly) {
            std::string result = "[";
            for (const auto& p : poly) {
                result += toString(p) + ", ";
            }
            result += "]";
            return result;
        }
    }
    namespace Algorithms {
        // Example algorithm: Convex Hull (Graham's scan)
        Polygon convexHull(const Polygon& points) {
            // Sort points lexicographically
            Polygon sortedPoints = points;
            std::sort(sortedPoints.begin(), sortedPoints.end(), [](const Point& a, const Point& b) {
                return a.first < b.first || (a.first == b.first && a.second < b.second);
            });

            // Build lower hull
            Polygon lower;
            for (const auto& p : sortedPoints) {
                while (lower.size() >= 2 && Geometry::cross(lower[lower.size() - 1], lower[lower.size() - 2]) <= 0) {
                    lower.pop_back();
                }
                lower.push_back(p);
            }

            // Build upper hull
            Polygon upper;
            for (int i = sortedPoints.size() - 1; i >= 0; --i) {
                const auto& p = sortedPoints[i];
                while (upper.size() >= 2 && Geometry::cross(upper[upper.size() - 1], upper[upper.size() - 2]) <= 0) {
                    upper.pop_back();
                }
                upper.push_back(p);
            }

            // Remove the last point of each half because it's repeated at the beginning of the other half
            lower.pop_back();
            upper.pop_back();

            // Concatenate lower and upper hull to get the full hull
            lower.insert(lower.end(), upper.begin(), upper.end());
            return lower;
        }
    }

    #define LEMON_ASSERT(condition, message) \
        Lemon::Debug::assertCondition(condition, message)
    #define LEMON_ASSERT_EQUAL(a, b, message) \
        Lemon::Debug::assertEqual(a, b, message)
    #define LEMON_LOG(message) \
        Lemon::Io::Log(message)
    #define LEMON_ERROR(message) \
        Lemon::Io::Error(message)
    #define LEMON_WARNING(message) \
        Lemon::Io::Warning(message)
    #define LEMON_EXPR(expr) \
        Lemon::Io::expr(expr)

    #define func(r) void(r)
    #define struct(r) struct r
    #define type (r) using r

    typedef struct Typing {
        int a;
        double b;
    } Typing;

    class ObjectSystem {
        template <typename T>
        void addObject(const std::string& name, const T& object) {
            objects[name] = std::make_shared<Wrapper<T>>(object);
        }

        template <typename T>
        T getObject(const std::string& name) const {
            auto it = objects.find(name);
            if (it != objects.end()) {
                auto wrapper = std::dynamic_pointer_cast<Wrapper<T>>(it->second);
                if (wrapper) {
                    return wrapper->object;
                }
            }
            throw std::runtime_error("Object not found or type mismatch");
        }

    private:
        struct BaseWrapper {
            virtual ~BaseWrapper() = default;
        };

        template <typename T>
        struct Wrapper : BaseWrapper {
            Wrapper(const T& obj) : object(obj) {}
            T object;
        };

        std::map<std::string, std::shared_ptr<BaseWrapper>> objects;
    };
}

#endif // LEMON_H