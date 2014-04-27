#ifndef QUESTION_WINDOW_H
#define QUESTION_WINDOW_H

#include <pebble.h>
#include <qfetcher.h>

void question_load();
void question_init();
void question_window_load(Window *window);
void question_window_unload(Window *window);
static void question_button_back(ClickRecognizerRef recognizer, void *context);
static void question_button_up(ClickRecognizerRef recognizer, void *context);
static void question_button_select(ClickRecognizerRef recognizer, void *context);
static void question_button_down(ClickRecognizerRef recognizer, void *context);
static void question_auto_resize_body();
void select_answer_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context);


#endif