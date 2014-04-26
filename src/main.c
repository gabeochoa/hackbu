#include <pebble.h>

Window *base_window;

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
    Window *question_window;
    TextLayer *text_layer;
    // Create a window and text layer
	question_window = window_create();
	text_layer = text_layer_create(GRect(0, 0, 144, 154));
	
	// Set the text, font, and text alignment
	text_layer_set_text(text_layer, "EXAMPLE QUESTION" /*Question field from struct*/);
	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text_layer, GTextAlignmentLeft);
    
    
	
	// Add the text layer to the window
	layer_add_child(window_get_root_layer(question_window), text_layer_get_layer(text_layer));

    window_stack_push(question_window ,true);
    
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}
void window_load(Window *window)
{
    menu_layer = menu_layer_create(GRect(0, 0, 144, 168-16));
    menu_layer_set_click_config_onto_window(menu_layer, window);
    MenuLayerCallbacks callbacks = {
        .draw_row = (MenuLayerDrawRowCallback) draw_row_callback,
        .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback,
        .select_click = (MenuLayerSelectCallback) select_click_callback
    };
    menu_layer_set_callbacks(menu_layer, NULL, callbacks);
    layer_add_child(window_get_root_layer(window), menu_layer_get_layer(menu_layer));
}
 
void window_unload(Window *window)
{
    menu_layer_destroy(menu_layer);
}
 
void init()
{
    base_window = window_create();
    WindowHandlers handlers = {
        .load = window_load,
        .unload = window_unload
    };
    window_set_window_handlers(base_window, (WindowHandlers) handlers);
    window_stack_push(base_window, true);
}
 
void deinit()
{
    window_destroy(base_window);
}
 
int main(void)
{
    init();
    app_event_loop();
    deinit();
}