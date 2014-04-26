#include <pebble.h>
 
Window *window;
MenuLayer *menu_layer;

void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
    //Which row is it?
    switch(cell_index->row)
    {
    case 0:
        menu_cell_basic_draw(ctx, cell_layer, "1. Apple", "Green and crispy!", NULL);
        break;
    case 1:
        menu_cell_basic_draw(ctx, cell_layer, "2. Orange", "Peel first!", NULL);
        break;
    case 2:
        menu_cell_basic_draw(ctx, cell_layer, "3. Pear", "Teardrop shaped!", NULL);
        break;
    }
}
 
uint16_t num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context)
{
    return 3;
}
 
void select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{
    
}
void window_load(Window *window)
{
 
}
 
void window_unload(Window *window)
{
 
}
 
void init()
{
    window = window_create();
    WindowHandlers handlers = {
        .load = window_load,
        .unload = window_unload
    };
    window_set_window_handlers(window, (WindowHandlers) handlers);
    window_stack_push(window, true);
}
 
void deinit()
{
    window_destroy(window);
}
 
int main(void)
{
    init();
    app_event_loop();
    deinit();
}