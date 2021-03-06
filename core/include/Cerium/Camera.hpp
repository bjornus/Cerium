#ifndef CERIUM_CAMERA_HPP
#define CERIUM_CAMERA_HPP

#include "vec2.hpp"

#include <glm/mat4x4.hpp>

namespace cerium
{
    class ShaderProgram;
    class Camera
    {
    public:
        /*
            ^[name][init]
            ^[class][Camera]
            ^[description][Setting default value to position (0) and size(size of Window) of Camera]
        */
        static void init(void); //^header
        /*
            ^[name][update]
            ^[class][Camera]
            ^[description][Creating new orthographic matrix]
            ^[argument]<shaderProgram>[Currently rendered Shader]
        */
        static void update(ShaderProgram * shaderProgram); //^header
        /*
            ^[name][move]
            ^[class][Camera]
            ^[description][Moving Camera by the given value]
            ^[argument]<relative>[Relative position of Camera]
        */
        static void move(const vec2 & relative); //^header
        /*
            ^[name][setPosition]
            ^[class][Camera]
            ^[description][Setting new position of Camera]
            ^[argument]<position>[Position where the Camera have to be]
        */
        static void setPosition(const vec2 & position); //^header
        /*
            ^[name][setSize]
            ^[class][Camera]
            ^[description][Setting new size of Camera]
            ^[argument]<size>[New size of Camera]
        */
        static void setSize(const vec2 & size); //^header
        /*
            ^[name][getPosition]
            ^[class][Camera]
            ^[returns][Position of Camera]
        */
        static vec2 getPosition(); //^header
		/*
            ^[name][getSize]
            ^[class][Camera]
            ^[returns][Size of Camera]
        */
        static vec2 getSize(); //^header

		static void setRotation(const float & angle);

		static void rotate(const float & angle);

		static float getRotationAngle(void);
    private:
        static Camera & instance();

        Camera() {};
        ~Camera() {};

        Camera(const Camera & other) = delete;
        void operator=(const Camera & other) = delete;
    private:
        glm::mat4 projection;
        vec2 position;
        vec2 size;
		float angle;
    };
}

#endif