#pragma once

#include <iosfwd>

class Vector2d {
public:
    Vector2d(double x, double y);
    explicit Vector2d(double v);
    Vector2d();
    [[nodiscard]] double X() const;
    [[nodiscard]] double Y() const;
    void Set(double x, double y);
    void SetX(double x);
    void SetY(double y);
    Vector2d &operator/=(double v);
    Vector2d &operator*=(double v);
    Vector2d &operator-=(const Vector2d &rhs);
    Vector2d &operator-=(double v);
    Vector2d &operator+=(double v);
    Vector2d &operator+=(const Vector2d &rhs);
    Vector2d &operator++();
    Vector2d &operator--();
    [[nodiscard]] double Length() const;
    [[nodiscard]] double LengthSq() const;
    [[nodiscard]] double Sum() const;
    [[nodiscard]] Vector2d Normalize() const;

private:
    double x_, y_;
};

Vector2d operator*(const Vector2d &lhs, double v);
Vector2d operator/(const Vector2d &lhs, double v);
Vector2d operator*(double v, const Vector2d &rhs);
Vector2d operator/(double v, const Vector2d &rhs);
double operator*(const Vector2d &lhs, const Vector2d &rhs);
Vector2d operator-(const Vector2d &lhs, const Vector2d &rhs);
Vector2d operator+(const Vector2d &lhs, const Vector2d &rhs);
std::ostream &operator<<(std::ostream &out, const Vector2d &vec);
