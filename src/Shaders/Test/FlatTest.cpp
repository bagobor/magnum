/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013 Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include "Shaders/Flat.h"
#include "Test/AbstractOpenGLTester.h"

namespace Magnum { namespace Shaders { namespace Test {

class FlatTest: public Magnum::Test::AbstractOpenGLTester {
    public:
        explicit FlatTest();

        void compile2D();
        void compile3D();
        void compile2DTextured();
        void compile3DTextured();
};

FlatTest::FlatTest() {
    addTests({&FlatTest::compile2D,
              &FlatTest::compile3D,
              &FlatTest::compile2DTextured,
              &FlatTest::compile3DTextured});
}

void FlatTest::compile2D() {
    Shaders::Flat2D shader;
    CORRADE_VERIFY(shader.validate().first);
}

void FlatTest::compile3D() {
    Shaders::Flat3D shader;
    CORRADE_VERIFY(shader.validate().first);
}

void FlatTest::compile2DTextured() {
    Shaders::Flat2D shader(Shaders::Flat2D::Flag::Textured);
    CORRADE_VERIFY(shader.validate().first);
}

void FlatTest::compile3DTextured() {
    Shaders::Flat3D shader(Shaders::Flat3D::Flag::Textured);
    CORRADE_VERIFY(shader.validate().first);
}

}}}

CORRADE_TEST_MAIN(Magnum::Shaders::Test::FlatTest)
