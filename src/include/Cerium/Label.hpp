#ifndef CERIUM_LABEL_HPP
#define CERIUM_LABEL_HPP

#include <string>

#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>

#include "Prop.hpp"

namespace cerium
{
    class Person;
    class Font;
    class Label : public Prop
    {
    public:
        Label(Person * basePerson, Font * font, const std::string & text, float r, float g, float b, float a);
        ~Label();

        virtual void update(const float & deltaTime) override;
        virtual void draw(void) override;
    private:
        GLuint texture;
    };
}

#endif