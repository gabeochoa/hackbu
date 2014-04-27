#include <questionwindow.h>

	
static int currentq = 0;

Window *qwind;
MenuLayer *answer_layer;
TextLayer *question_layer;

//Window *new_question_window;
MenuLayer *new_answer_layer;

char* question_str = "";
char* first = "";
char* second = "";
char* third = "";
char* fourth = "";

void q_draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
	
	APP_LOG(APP_LOG_LEVEL_DEBUG, "16");

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
	
	APP_LOG(APP_LOG_LEVEL_DEBUG, "62");

}
 
uint16_t q_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context)
{
    return 4;
}	
void load_capitals(int q);
void load_baseball(int q);
void load_celebrities(int q);

void load_question(int cat, int q)
{
	switch(cat)
	{
		case 0: // Capitals
					load_capitals(q);
		break;
		case 1: // Celebrities
					load_celebrities(q);
		break;
		case 2: // Baseball
					load_baseball(q);
		break;
	}
	currentq++;
}

struct deck* capitals;
struct deck* celebrities;
struct deck* baseball;

static struct deck *getCapitals(){return capitals;}
static struct deck *getCelebrities(){return celebrities;}
static struct deck *getBaseball(){return baseball;}

void load_capitals(int qa)
{	
	 capitals = (struct deck*) malloc(sizeof(struct deck));
	 APP_LOG(APP_LOG_LEVEL_DEBUG, "start load capitals"); 
	struct question c1qu;
	c1qu.q = "Capital of Afghanistan";
	 APP_LOG(APP_LOG_LEVEL_DEBUG, "1"); 
 	c1qu.answers[0] = "Kabul";
	 APP_LOG(APP_LOG_LEVEL_DEBUG, "2"); 
 	c1qu.answers[1] = "Dhaka";
	 APP_LOG(APP_LOG_LEVEL_DEBUG, "3"); 
 	c1qu.answers[2] = "Armenia";
	 APP_LOG(APP_LOG_LEVEL_DEBUG, "4"); 
 	c1qu.answers[3] = "Vienna";
	 APP_LOG(APP_LOG_LEVEL_DEBUG, "5"); 
	c1qu.correctanswer="Kabul";
	 APP_LOG(APP_LOG_LEVEL_DEBUG, "6"); 
	(*capitals).questions[0] = c1qu;	
	
	 APP_LOG(APP_LOG_LEVEL_DEBUG, "afghan"); 
	struct question c2qu;
	c2qu.q = "Capital of Peru";
 	c2qu.answers[0] = "Lima";
 	c2qu.answers[1] = "Kigali";
 	c2qu.answers[2] = "Tehran";
 	c2qu.answers[3] = "San Salvador";
	c2qu.correctanswer="Lima";
	capitals->questions[1] = c2qu;	
	
	
	 APP_LOG(APP_LOG_LEVEL_DEBUG, "peru"); 
	struct question c3qu;
	c3qu.q = "Capital of Denmark";
 	c3qu.answers[0] = "Copenhagen";
 	c3qu.answers[1] = "Quito";
 	c3qu.answers[2] = "Suva";
 	c3qu.answers[3] = "Cairo";
	c3qu.correctanswer="Copenhagen";
	capitals->questions[2] = c3qu;	
	
	
	 APP_LOG(APP_LOG_LEVEL_DEBUG, "denmoark"); 
	struct question c4qu;
	c4qu.q = "Capital of France";
 	c4qu.answers[0] = "Paris";
 	c4qu.answers[1] = "Havana";
 	c4qu.answers[2] = "Zagreb";
 	c4qu.answers[3] = "Jakarta";
	c4qu.correctanswer="Paris";
	capitals->questions[3] = c4qu;	
	
	
	 APP_LOG(APP_LOG_LEVEL_DEBUG, "france"); 
	struct question c5qu;
	c5qu.q = "Capital of Greece";
 	c5qu.answers[0] = "Athens";
 	c5qu.answers[1] = "Siva";
 	c5qu.answers[2] = "Prague";
 	c5qu.answers[3] = "Libreville";
	c5qu.correctanswer="Athens";
	capitals->questions[4] = c5qu;	

	 APP_LOG(APP_LOG_LEVEL_DEBUG, "greece");
	
	
	question_str = capitals->questions[qa].q;
	first = capitals->questions[qa].answers[0];
	second = capitals->questions[qa].answers[1];
	third = capitals->questions[qa].answers[2];
	fourth = capitals->questions[qa].answers[3];

	APP_LOG(APP_LOG_LEVEL_DEBUG, "finish loading");
  
}
void load_baseball(int qa)
{
	baseball = (struct deck*) malloc(sizeof(struct deck));
	
	struct question b1qu;
	b1qu.q = "Stadium of Boston Red Sox";
	b1qu.answers[0] = "Fenway Park";
	b1qu.answers[1] = "Comerica Park";
	b1qu.answers[2] = "Chase field";
	b1qu.answers[3] = "Busch Stadium";
	b1qu.correctanswer = "Fenway Park";
	baseball->questions[0] = b1qu;

struct question b2qu;
	b2qu.q = "Stadium of Houston Astros";
	b2qu.answers[0] = "Astrodome";
	b2qu.answers[1] = "Citi Field";
	b2qu.answers[2] = "Comerica Park";
	b2qu.answers[3] = "Coors Field";
	b2qu.correctanswer = "Astrodome";
	baseball->questions[1] = b2qu;

struct question b3qu;
	b3qu.q = "Stadium of San Fransisco Giants";
	b3qu.answers[0] = "AT&T Park";
	b3qu.answers[1] = "Angel Stadium of Anahheim";
	b3qu.answers[2] = "Comerica Park";
	b3qu.answers[3] = "PNC Park";
	b3qu.correctanswer = "AT&T Park";
	baseball->questions[2] = b3qu;

struct question b4qu;
	b4qu.q = "Stadium of Milwaukee Brewers";
	b4qu.answers[0] = "Miller Park";
	b4qu.answers[1] = "Minute Maid Park";
	b4qu.answers[2] = "Progressive Field";
	b4qu.answers[3] = "Petco Park";
	b4qu.correctanswer = "Miller Park";
	baseball->questions[3] = b4qu;


struct question b5qu;
	b5qu.q = "Stadium of St. Louis Cardinals";
	b5qu.answers[0] = "Busch Stadium";
	b5qu.answers[1] = "Wrigley Field";
	b5qu.answers[2] = "Turner Field";
	b5qu.answers[3] = "Target Field";
	b5qu.correctanswer = "Busch Stadium";
	baseball->questions[4] = b5qu;

	
	question_str = baseball->questions[qa].q;
	first = baseball->questions[qa].answers[0];
	second = baseball->questions[qa].answers[1];
	third = baseball->questions[qa].answers[2];
	fourth = baseball->questions[qa].answers[3];
}
void load_celebrities(int qa)
{
	celebrities = (struct deck*) malloc(sizeof(struct deck));
	
	
struct question e1qu;
	e1qu.q = "Once dated Brad Pitt";
	e1qu.answers[0] = "Juliette Lewis";
	e1qu.answers[1] = "Julia Roberts";
	e1qu.answers[2] = "Julianne Moore";
	e1qu.answers[3] = "Julie Andrews";
	e1qu.correctanswer = "Juliette Lewis";
	celebrities->questions[0] = e1qu;

struct question e2qu;
	e2qu.q = "Julia Roberts used to be married to";
	e2qu.answers[0] = "Lyle Lovett";
	e2qu.answers[1] = "Benjamin Bratt";
	e2qu.answers[2] = "Matthew Perry";
	e2qu.answers[3] = "Kiefer Sutherland";
	e2qu.correctanswer = "Lyle Lovett";
	celebrities->questions[1] = e2qu;

struct question e3qu;
	e3qu.q = "Who has Gwyneth Paltrow NOT been linked with";
	e3qu.answers[0] = "Matt Dillon";
	e3qu.answers[1] = "Brad Pitt";
	e3qu.answers[2] = "Ben Affleck";
	e3qu.answers[3] = "Chris Martin";
	e3qu.correctanswer = "Matt Dillon";
	celebrities->questions[2] = e3qu;

struct question e4qu;
	e4qu.q = "Who has Angelina Jolie NOT married";
	e4qu.answers[0] = "George Clooney";
	e4qu.answers[1] = "Brad Pitt";
	e4qu.answers[2] = "Johnny Lee Miller";
	e4qu.answers[3] = "Billy Bob Thornton";
	e4qu.correctanswer = "George Clooney";
	celebrities->questions[3] = e4qu;

struct question e5qu;
	e5qu.q = "Who was once married to Tom Cruise";
	e5qu.answers[0] = "Mimi Rogers";
	e5qu.answers[1] = "Penelope Cruz";
	e5qu.answers[2] = "Katie Holmes";
	e5qu.answers[3] = "Scarlet Johannson";
	e5qu.correctanswer = "Mimi Rogers";
	celebrities->questions[4] = e5qu;	
	
	question_str = celebrities->questions[qa].q;
	first = celebrities->questions[qa].answers[0];
	second = celebrities->questions[qa].answers[1];
	third = celebrities->questions[qa].answers[2];
	fourth = celebrities->questions[qa].answers[3];
}


static void question_button_back(ClickRecognizerRef recognizer, void *context)
{
	currentq--;
}
static void question_button_up(ClickRecognizerRef recognizer, void *context)
{
	
}
static void question_button_select(ClickRecognizerRef recognizer, void *context)
{
	
}
static void question_button_down(ClickRecognizerRef recognizer, void *context)
{
	
}
void select_answer_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{
	Window *new_question_window;
		//Get which row
    int which = cell_index->row;
	  int correctPos = 0;
 
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
	
		new_question_window = window_create();
	
	window_set_window_handlers(new_question_window, (WindowHandlers)
		{
			.load = question_window_load,
			.unload = question_window_unload,
	  });
	
	/*
	  //Create menu for ans.
	  new_answer_layer = menu_layer_create(GRect(0, 60, 144, 94));
 		menu_layer_set_click_config_onto_window(new_answer_layer, new_question_window);
	  layer_add_child(window_get_root_layer(new_question_window), menu_layer_get_layer(new_answer_layer));
		*/
	
	APP_LOG(APP_LOG_LEVEL_DEBUG, "pushing new question window");

		window_stack_push(new_question_window ,true);

	 APP_LOG(APP_LOG_LEVEL_DEBUG, "pushed new question window");
}

void question_window_load(Window *window)
{
	APP_LOG(APP_LOG_LEVEL_DEBUG, "loading");
	load_question(0,currentq);	

	  answer_layer = menu_layer_create(GRect(0, 60, 144, 94));
 		menu_layer_set_click_config_onto_window(answer_layer, window);
	  layer_add_child(window_get_root_layer(window), menu_layer_get_layer(answer_layer));
	
	question_layer = text_layer_create(GRect(0, 0, 144, 154));
    
	APP_LOG(APP_LOG_LEVEL_DEBUG, "1");
  //Set the text, font, and text alignment
	text_layer_set_text(question_layer, question_str );//Question field from struct
	text_layer_set_font(question_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
	text_layer_set_text_alignment(question_layer, GTextAlignmentLeft);

	APP_LOG(APP_LOG_LEVEL_DEBUG, "2");
	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(question_layer));
    
	APP_LOG(APP_LOG_LEVEL_DEBUG, "3");

 	//menu_layer_set_click_config_onto_window(answer_layer, window);
	
	APP_LOG(APP_LOG_LEVEL_DEBUG, "4");
	MenuLayerCallbacks callbacks = {
        .draw_row = (MenuLayerDrawRowCallback) q_draw_row_callback,
        .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) q_num_rows_callback,
        .select_click = (MenuLayerSelectCallback) select_answer_click_callback
    };
	
  menu_layer_set_callbacks(answer_layer, NULL, callbacks);
	
	APP_LOG(APP_LOG_LEVEL_DEBUG, "5");
	//Add to Window
  layer_add_child(window_get_root_layer(window), menu_layer_get_layer(answer_layer));
	
	APP_LOG(APP_LOG_LEVEL_DEBUG, "6");
}

void question_window_unload(Window * window)
{
	menu_layer_destroy(answer_layer);
}