#pragma once

#include "core/vec2i.h"
#include "color.h"
#include "game/resource.h"
#include "graphics/image_desc.h"
#include "graphics/graphics.h"

struct viewport_t;
struct SDL_Renderer;
struct SDL_Texture;
struct image_t;

struct sprite {
    const image_t *img = nullptr;
    inline sprite() {}
};

struct sprite_resource_icon : public sprite {
    sprite_resource_icon(e_resource);
};

struct painter {
    viewport_t *view;
    SDL_Renderer *renderer;
    float global_render_scale;

    void draw(
        SDL_Texture *texture, vec2i pos, vec2i offset, vec2i size, color color = COLOR_MASK_NONE,
        float scale_x = 1.f, float scale_y = 1.f, double angle = 0, ImgFlags flags = ImgFlag_None, bool force_linear = false
    );
    void draw(
        const sprite &spr, vec2i pos, color color_mask = COLOR_MASK_NONE,
        float scale_x = 1.f, float scale_y = 1.f, double angle = 0, ImgFlags flags = ImgFlag_None, bool force_linear = false
    );

protected:
    void draw_grayscale(
        SDL_Texture *texture, vec2i pos, vec2i offset, vec2i size,
        float scale_x = 1.f, float scale_y = 1.f, double angle = 0, ImgFlags flags = ImgFlag_None, bool force_linear = false
    );
    void draw_impl(
        SDL_Texture *texture, vec2i pos, vec2i offset, vec2i size, color color = COLOR_MASK_NONE,
        float scale_x = 1.f, float scale_y = 1.f, double angle = 0, ImgFlags flags = ImgFlag_None, bool force_linear = false
    );
    SDL_Texture *convertToGrayscale(SDL_Texture *tx, vec2i offset, vec2i size);
};

