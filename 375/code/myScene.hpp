/// \file myScene.hpp
/// \brief Declaration of myScene class, which includes a single constructor and stuff to prevent one from copying.
/// \author John Shenk
/// \version A02

#ifndef MYSCENE_HPP
#define MYSCENE_HPP

#include <vector>

#include <glm/mat4x4.hpp>

#include "OpenGLContext.hpp"
#include "ShaderProgram.hpp"
#include "Scene.hpp"

/// \brief An object that exists in the world, which consists of one or more
///   3-D triangles.
class myScene : public Scene
{
    public:
    /// Contruct a scene (my scene).
    myScene (int lights, OpenGLContext* context, ShaderProgram* colors, ShaderProgram* norms);

    /// \brief Copy constructor removed because you shouldn't be copying Meshes.
    myScene (const myScene&) = delete;

    /// \brief Assignment operator removed because you shouldn't be assigning
    ///   additional scenes
    myScene&
    operator= (const myScene&) = delete;

    private:
        ShaderProgram* s_colors;
        ShaderProgram* s_norms;
};

#endif