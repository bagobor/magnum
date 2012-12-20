#ifndef Magnum_DebugTools_ShapeRenderer_h
#define Magnum_DebugTools_ShapeRenderer_h
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

#include "Color.h"
#include "Resource.h"
#include "SceneGraph/Drawable.h"
#include "Physics/Physics.h"

#include "magnumDebugToolsVisibility.h"

namespace Magnum { namespace DebugTools {

template<std::uint8_t> class ShapeRenderer;

#ifndef DOXYGEN_GENERATING_OUTPUT
namespace Implementation {
    template<std::uint8_t> class AbstractShapeRenderer;

    template<std::uint8_t dimensions> void createDebugMesh(ShapeRenderer<dimensions>* renderer, Physics::AbstractShape<dimensions>* shape);
}
#endif

/**
@brief Shape renderer options

See ShapeRenderer documentation for more information.
*/
struct ShapeRendererOptions {
    Color3<> color;             /**< @brief Color */
};

/**
@brief Shape renderer

Creates renderers for object collision shape.

@section ShapeRenderer-usage Basic usage

ResourceManager must be instanced for the whole lifetime of debug
renderers. You can specify options via Options struct - add it to the manager
and then create debug renderer with the same options key. This way you can
easily share the same options with more renderers. If no options for given key
exist, default is used.

Example code:
@code
// Instance the manager at first
DebugTools::ResourceManager manager;

// Group of drawables, preferrably dedicated for debug renderers, so you can
// easily enable or disable debug draw
SceneGraph::DrawableGroup2D debugDrawables;

// Create some options
auto o = new DebugTools::ShapeRendererOptions {
    {1.0f, 0.0f, 0.0f} // Red color
};
manager->set<DebugTools::ShapeRendererOptions>("red", o, ResourceDataState::Final, ResourcePolicy::Persistent);

// Create debug renderer for given shape, use "red" options for it
Physics::ObjectShape2D* shape;
debugDrawables.add(new DebugTools::ShapeRenderer2D(shape, "red", debugDrawables));
@endcode

@see ShapeRenderer2D, ShapeRenderer3D
*/
template<std::uint8_t dimensions> class MAGNUM_DEBUGTOOLS_EXPORT ShapeRenderer: public SceneGraph::Drawable<dimensions> {
    #ifndef DOXYGEN_GENERATING_OUTPUT
    friend void Implementation::createDebugMesh<>(ShapeRenderer<dimensions>*, Physics::AbstractShape<dimensions>*);
    #endif

    public:
        /**
         * @brief Constructor
         * @param shape     Shape for which to create debug renderer
         * @param options   Options resource key. See
         *      @ref ShapeRenderer-usage "class documentation" for more
         *      information.
         * @param drawables Drawable group
         *
         * @attention @p shape must be available for the whole lifetime of
         *      this class
         */
        explicit ShapeRenderer(Physics::ObjectShape<dimensions>* shape, ResourceKey options = ResourceKey(), SceneGraph::DrawableGroup<dimensions>* drawables = nullptr);

        ~ShapeRenderer();

    protected:
        /** @todoc Remove GLfloat when Doxygen properly treats this as override */
        void draw(const typename DimensionTraits<dimensions, GLfloat>::MatrixType& transformationMatrix, SceneGraph::AbstractCamera<dimensions, GLfloat>* camera) override;

    private:
        Resource<ShapeRendererOptions> options;
        std::vector<Implementation::AbstractShapeRenderer<dimensions>*> renderers;
};

/** @brief Two-dimensional shape renderer */
typedef ShapeRenderer<2> ShapeRenderer2D;

/** @brief Three-dimensional shape renderer */
typedef ShapeRenderer<3> ShapeRenderer3D;

}}

#endif