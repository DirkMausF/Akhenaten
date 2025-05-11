#include "common.h"

#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/screen.h"
#include "graphics/view/view.h"
#include "game/game.h"

int sidebar_common_get_height() {
    return screen_height() - TOP_MENU_HEIGHT;
}

void sidebar_common_draw_relief(vec2i offset, image_desc desc) {
    painter ctx = game.painter();

    int image_id = image_group(desc);
    int y_max = screen_height();

    while (offset.y < y_max) {
        ImageDraw::img_generic(ctx, image_id, offset.x, offset.y + 6);
        offset.y += 285;
    }
}
