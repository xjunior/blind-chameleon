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

#ifndef COMPLEX_H
#define COMPLEX_H

class Complex
{
    double _re;
    double _im;
public:
    Complex(double real=0.0, double imag=0.0);
    Complex(Complex*);
    double abso();
    double phase();
    double magnitude();
    Complex plus(Complex);
    Complex minus(Complex);
    Complex times(Complex);
    Complex times(double alpha);
    Complex conjugate();
    Complex reciprocal();
    double re() { return _re; }
    double im() { return _im; }
    void setRe(double re) { _re = re; }
    void setIm(double im) { _im = im; }
    void set(double re, double im) { _re = re; _im = im; }
    void set(Complex &c) { _re = c.re(); _im = c.im(); }
    Complex divides(Complex);
    Complex expo();
    Complex sino();
    Complex coso();
    Complex tan();
    static Complex plus(Complex, Complex);
};

#endif

