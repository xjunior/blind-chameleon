/*
 * This file is part of Blind Camaleon.
 *
 * Blind Camaleon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Blind Camaleon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Blind Camaleon.  If not, see <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#include <math.h>
#include <stdlib.h>
#include "complex.h"

Complex::Complex(double real, double imag)
{
    _re = real;
    _im = imag;
}

Complex::Complex(Complex *c)
{
    _re = c->re();
    _im = c->im();
}

double Complex::abso()
{
    return hypot(_re, _im);
}
double Complex::phase()
{
    return atan2(_im, _re);
}

double Complex::magnitude()
{
    return abs(_re*_re + _im*_im);
}

Complex Complex::plus(Complex b)
{
    double real = _re + b.re();
    double imag = _im + b.im();
    return Complex(real, imag);
}

Complex Complex::minus(Complex b) {
    double real = _re - b.re();
    double imag = _im - b.im();
    return Complex(real, imag);
}

Complex Complex::times(Complex b)
{
    double real = _re * b.re() - _im * b.im();
    double imag = _re * b.im() + _im * b.re();
    return Complex(real, imag);
}

Complex Complex::times(double alpha)
{
    return Complex(alpha * _re, alpha * _im);
}

Complex Complex::conjugate()
{
    return Complex(_re, -1 * _im);
}

Complex Complex::reciprocal()
{
    double scale = _re * _re + _im * _im;
    return Complex(_re / scale, -1 * _im / scale);
}

Complex Complex::divides(Complex b)
{
    return times(b.reciprocal());
}

Complex Complex::expo()
{
    return Complex(exp(_re) * cos(_im), exp(_re) * sin(_im));
}

Complex Complex::sino()
{
    return Complex(sin(_re) * cosh(_im), cos(_re) * sinh(_im));
}

Complex Complex::coso()
{
    return Complex(cos(_re) * cosh(_im), -1 * sin(_re) * sinh(_im));
}

Complex Complex::tan()
{
    return sino().divides(coso());
}

Complex Complex::plus(Complex a, Complex b)
{
    double real = a.re() + b.re();
    double imag = a.im() + b.im();
    return Complex(real, imag);
}

