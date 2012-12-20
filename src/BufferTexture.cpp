/*
    Copyright © 2010, 2011, 2012 Vladimír Vondruš <mosra@centrum.cz>

    This file is part of Magnum.

    Magnum is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License version 3
    only, as published by the Free Software Foundation.

    Magnum is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License version 3 for more details.
*/

#include "BufferTexture.h"

#ifndef MAGNUM_TARGET_GLES
#include "Buffer.h"
#include "Context.h"
#include "Extensions.h"

namespace Magnum {

BufferTexture::SetBufferImplementation BufferTexture::setBufferImplementation = &BufferTexture::setBufferImplementationDefault;

void BufferTexture::initializeContextBasedFunctionality(Context* context) {
    if(context->isExtensionSupported<Extensions::GL::EXT::direct_state_access>()) {
        Debug() << "BufferTexture: using" << Extensions::GL::EXT::direct_state_access::string() << "features";

        setBufferImplementation = &BufferTexture::setBufferImplementationDSA;
    }
}

void BufferTexture::setBufferImplementationDefault(BufferTexture::InternalFormat internalFormat, Buffer* buffer) {
    bindInternal();
    glTexBuffer(GL_TEXTURE_BUFFER, GLenum(internalFormat), buffer->id());
}

void BufferTexture::setBufferImplementationDSA(BufferTexture::InternalFormat internalFormat, Buffer* buffer) {
    glTextureBufferEXT(id(), GL_TEXTURE_BUFFER, GLenum(internalFormat), buffer->id());
}

}
#endif