#include <pebble.h>
#include <qfetcher.h>
	
Window* window;

MenuLayer * menu_layer;

Window *question_window;
MenuLayer *answer_layer;

struct deck* capitals;
struct deck* celebrities;
struct deck* baseball;

static struct deck *getCapitals(){return capitals;}
static struct deck *getCelebrities(){return celebrities;}
static struct deck *getBaseball(){return baseball;}

//TextLayer *layer_q_name, *layer_q_descr, *layer_q_a1, *layer_q_a2, *layer_q_a3, *layer_q_a4;
char q_name_buffer[16], q_descr_buffer[32], ansA[16], ansB[16], ansC[16], ansD[16];
char *first;
char *second;
char *third;
char *fourth;
char *correct;
int correctPos = 0;

enum {
    KEY_QNAME = 0,
    KEY_QDESCRIPTION = 1,
    KEY_CANSA = 2,
    KEY_WANS = 3
};

static void send_category(MenuIndex cell_index) {
  Tuplet value = TupletInteger(1, cell_index.row);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "inside send category %d" ,cell_index.row);
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  if (iter == NULL) {
    return;
  }

  dict_write_tuplet(iter, &value);
  dict_write_end(iter);
  app_message_outbox_send();
}

void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
    //Which row is it?
    switch(cell_index->row)
    {
    case 0:
        menu_cell_basic_draw(ctx, cell_layer, "Capitals", "Know your Capitals!", NULL);
        break;
    case 1:
        menu_cell_basic_draw(ctx, cell_layer, "Celebrities", "Know your Celebs!", NULL);
        break;
    case 2:
        menu_cell_basic_draw(ctx, cell_layer, "Baseball", "Know your Ballparks!", NULL);
        break;
    }
}
 
uint16_t num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context)
{
    return 3;
}
 
//////////////////

    
void draw_ansrow_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context) {
    
    //Which row is it?
    switch(cell_index->row)
    {
    case 0:
        menu_cell_basic_draw(ctx, cell_layer, "A", (char *) first, NULL);
        break;
    case 1:
        menu_cell_basic_draw(ctx, cell_layer, "B", (char*) second, NULL);
        break;
    case 2:
        menu_cell_basic_draw(ctx, cell_layer, "C", (char*) third, NULL);
        break;
    case 3:
        menu_cell_basic_draw(ctx, cell_layer, "D", (char*) fourth, NULL);
        break;
    }
}

void initRandomChoice() {
    int randomno = rand() % 4;
    APP_LOG(APP_LOG_LEVEL_DEBUG, "random no %d", randomno); 
    switch (randomno) {
    case 0:
        correct = first = ansA;
        correctPos = 0;
        second = ansB;
        third = ansC;
        fourth = ansD;
        break;
    case 1:
        correct = second = ansA;
        correctPos = 1;
        first = ansB;
        third = ansC;
        fourth = ansD;
        break;
    case 2:
        correct = third = ansA;
        correctPos = 2;
        first = ansC;
        second = ansB;
        fourth = ansD;
        break;
    case 3:
        correct = fourth = ansA;
        correctPos = 3;
        first = ansD;
        second = ansB;
        third = ansC;
        break;
    }
}

uint16_t num_ansrows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context) {
    return 4;
}

// Respond to whether the chosen answer is correct or not
void select_ansclick_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
    //Get which row
    int which = cell_index->row;
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Row num %d", which);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Correct num %d", correctPos);
 
    //The array that will hold the on/off vibration times
    uint32_t segments[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
 
    //Build the pattern (milliseconds on and off in alternating positions)
    for(int i = 0; i < 1; i++)
    {
         segments[2 * i] = 600;
         //segments[(2 * i) + 1] = 100;
    }
 
    //Create a VibePattern data structure
    VibePattern pattern = {
        .durations = segments,
        .num_segments = 16
    };
   if(correctPos == which){
     //Tell them they are correct! Right answer
   }
   else{
     //Do the vibration pattern as punishment for getting it wrong
      vibes_enqueue_custom_pattern(pattern);
   }
}
//////////////////

void select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{  
	//Create new window
 	question_window = window_create();
	
	window_set_window_handlers(question_window, (WindowHandlers)
		{
			.load = question_window_load,
			.unload = question_window_unload,
	  });
	
	  //Create menu for ans.
	/*
	  answer_layer = menu_layer_create(GRect(0, 60, 144, 94));
 		menu_layer_set_click_config_onto_window(answer_layer, question_window);
	  layer_add_child(window_get_root_layer(question_window), menu_layer_get_layer(answer_layer));
		*/

		window_stack_push(question_window ,true);

	 APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!"); 
}

void process_tuple(Tuple *t)
{
  //Get key
  int key = t->key;
 
  //Get string value, if present
  char string_value[32];
  strcpy(string_value, t->value->cstring);
 
  //Decide what to do
  switch(key) {
    case KEY_QNAME:
      //question name received
      snprintf(q_name_buffer, sizeof("Question Descr: couldbereallylongname"), "Question: %s", string_value);
     // text_layer_set_text(layer_q_name, (char*) &q_name_buffer);
      APP_LOG(APP_LOG_LEVEL_DEBUG, "string %s", (char*) &q_name_buffer);
      break;
    case KEY_QDESCRIPTION:
      //question description received
    snprintf(q_descr_buffer, sizeof("Question Name: couldbereallylongname"), "%s", string_value);
    //  text_layer_set_text(layer_q_descr, (char*) &q_descr_buffer);
      APP_LOG(APP_LOG_LEVEL_DEBUG, "string %s", (char*) &q_descr_buffer);
      break;
     case KEY_CANSA:
      snprintf(ansA, sizeof("Answer of some kind"), "%s", string_value);
      APP_LOG(APP_LOG_LEVEL_DEBUG, "correct choice %s", (char*) &ansA);
      break;
      
     case KEY_WANS:
      //snprintf(ansB, sizeof("0123456789ABCDEF0123456789A"), "%s", string_value);
       APP_LOG(APP_LOG_LEVEL_DEBUG, "wrong choice BCD: %s", string_value);
      int Cstart = 0;
      int Dstart = 0;
      for (int i = 0; i < (int) strlen(string_value); ++i) {
          APP_LOG(APP_LOG_LEVEL_DEBUG, "iteratin...");
          if (string_value[i] == '/') {
              string_value[i] = '\0';
              snprintf(ansB, sizeof("0123456789ABCDEF0123456789A"), "%s", string_value);
              string_value[i] = '/';
              Cstart = i+1;
              break;
          }
      }
     for (int i = Cstart; i < (int) strlen(string_value); ++i) {
         if (string_value[i] == '/') {
             string_value[i] = '\0';
             snprintf(ansC, sizeof("0123456789ABCDEF0123456789A"), "%s", string_value+Cstart);
             string_value[i] = '/';
              Dstart = i + 1;
            break;
        }
    }
      snprintf(ansA, sizeof("0123456789ABCDEF0123456789A"), "%s", string_value+Dstart);
      APP_LOG(APP_LOG_LEVEL_DEBUG, "wrong choice B: %s", (char*) &ansB);
      APP_LOG(APP_LOG_LEVEL_DEBUG, "wrong choice C: %s", (char*) &ansC);
      APP_LOG(APP_LOG_LEVEL_DEBUG, "wrong choice D: %s", (char*) &ansD);
		
  }
}
static void in_received_handler(DictionaryIterator *iter, void *context) 
{		
	 APP_LOG(APP_LOG_LEVEL_DEBUG, "HANDLERS");
  
	//Get data
  Tuple *t = dict_read_first(iter);
  if(t)
  {
    process_tuple(t);
  }  
  //Get next
  while(t != NULL)
  {
    t = dict_read_next(iter);
    if(t)
    {
      process_tuple(t);
    }
  }
}

void window_load(Window *window)
{
    /*
  layer_q_name = init_text_layer(GRect(5, 0, 144, 30), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_18", GTextAlignmentLeft);
  text_layer_set_text(layer_q_name, "Some Title");
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(layer_q_name));

layer_q_descr = init_text_layer(GRect(5, 30, 144, 138), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_18", GTextAlignmentLeft);
text_layer_set_text(layer_q_descr, "Question Description:abcdefghijkl N/A");
layer_add_child(window_get_root_layer(window), text_layer_get_layer(layer_q_descr));
 text_layer_set_overflow_mode(layer_q_descr, GTextOverflowModeWordWrap);
    */
    //Create it - 12 is approx height of the top bar
    menu_layer = menu_layer_create(GRect(0, 0, 144, 168 - 16));
 
    //Let it receive clicks
    menu_layer_set_click_config_onto_window(menu_layer, window);
 
    //Give it its callbacks
    MenuLayerCallbacks callbacks = {
        .draw_row = (MenuLayerDrawRowCallback) draw_row_callback,
        .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback,
        .select_click = (MenuLayerSelectCallback) select_click_callback
    };
    menu_layer_set_callbacks(menu_layer, NULL, callbacks);
 
    //Add to Window
    layer_add_child(window_get_root_layer(window), menu_layer_get_layer(menu_layer));
/*
layer_q_a1 = init_text_layer(GRect(5, 60, 144, 30), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_18", GTextAlignmentLeft);
text_layer_set_text(layer_q_a1, "Answer 1: N/A");
layer_add_child(window_get_root_layer(window), text_layer_get_layer(layer_q_a1));
    
layer_q_a2 = init_text_layer(GRect(5, 90, 144, 30), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_18", GTextAlignmentLeft);
text_layer_set_text(layer_q_a2, "Answer 2: N/A");
layer_add_child(window_get_root_layer(window), text_layer_get_layer(layer_q_a2));
    
layer_q_a3 = init_text_layer(GRect(5, 120, 144, 30), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_18", GTextAlignmentLeft);
text_layer_set_text(layer_q_a3, "Answer 3: N/A");
layer_add_child(window_get_root_layer(window), text_layer_get_layer(layer_q_a3));
    
layer_q_a4 = init_text_layer(GRect(5, 150, 144, 30), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_18", GTextAlignmentLeft);
text_layer_set_text(layer_q_a4, "Answer 4: N/A");
layer_add_child(window_get_root_layer(window), text_layer_get_layer(layer_q_a4));
*/
}
  
void window_unload(Window *window)
{
    /*
  text_layer_destroy(layer_q_name);
  text_layer_destroy(layer_q_descr);
  text_layer_destroy(layer_q_a1);
  text_layer_destroy(layer_q_a2);
  text_layer_destroy(layer_q_a3);
  text_layer_destroy(layer_q_a4); */
    menu_layer_destroy(answer_layer);
    menu_layer_destroy(menu_layer);
}

void in_dropped_handler(void *context, AppMessageResult reason)
{
	 APP_LOG(APP_LOG_LEVEL_DEBUG, "Dropped Message");
}

void init()
{
  window = window_create();
  WindowHandlers handlers = {
    .load = window_load,
    .unload = window_unload
  };
  window_set_window_handlers(window, handlers);
 
    initRandomChoice();
  //Register AppMessage events
app_message_register_inbox_received(in_received_handler);      
app_message_open(512, 512);    //Large input and output buffer sizes
    
  window_stack_push(window, true);
}

static void sync_error_callback(DictionaryResult dict_error, AppMessageResult app_message_error, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Sync Error: %d", app_message_error);
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