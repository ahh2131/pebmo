#include "friends.h"
#include "pebble.h"
#include "pay.h"

#define NUM_MENU_SECTIONS 2
#define NUM_FIRST_MENU_ITEMS 7
#define NUM_SECOND_MENU_ITEMS 1

static Window *window;

// This is a simple menu layer
static SimpleMenuLayer *simple_menu_layer;

// A simple menu layer can have multiple sections
static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];

// Each section is composed of a number of menu items
static SimpleMenuItem first_menu_items[NUM_FIRST_MENU_ITEMS];

static SimpleMenuItem second_menu_items[NUM_SECOND_MENU_ITEMS];

// Menu items can optionally have icons
static GBitmap *menu_icon_image;

static bool special_flag = false;

static int hit_count = 0;

enum {
    AKEY_NAME,
    AKEY_NAME2,
    AKEY_NAME3,
    AKEY_NAME4,
    AKEY_NAME5,
    AKEY_NAME6,
    AKEY_NAME7,

};

Tuple *text_tuple;
Tuple *text_tuple2;
Tuple *text_tuple3;
Tuple *text_tuple4;
Tuple *text_tuple5;
Tuple *text_tuple6;
Tuple *text_tuple7;
static int ping_count = 0;


static void out_sent_handler(DictionaryIterator *sent, void *context) {
   // outgoing message was delivered
 }


static void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
   // outgoing message failed
 }

static void in_received_handler(DictionaryIterator *iter, void *context) {

          text_tuple = dict_find(iter, AKEY_NAME);
          text_tuple2 = dict_find(iter, AKEY_NAME2);
          text_tuple3 = dict_find(iter, AKEY_NAME3);
          text_tuple4 = dict_find(iter, AKEY_NAME4);
          text_tuple5 = dict_find(iter, AKEY_NAME5);
          text_tuple6 = dict_find(iter, AKEY_NAME6);
          text_tuple7 = dict_find(iter, AKEY_NAME7);



          post_data();
        


}


static void in_dropped_handler(AppMessageResult reason, void *context) {
   // incoming message dropped
 }
// You can capture when the user selects a menu icon with a menu item select callback
static void menu_select_callback(int index, void *ctx) {
  // Here we just change the subtitle to a literal string
  //first_menu_items[index].subtitle = "You've hit select here!";
  // Mark the layer to be updated
  //layer_mark_dirty(simple_menu_layer_get_layer(simple_menu_layer));
  //payAmount(first_menu_items[index]);
  pay_amount(index);
}

// You can specify special callbacks to differentiate functionality of a menu item
static void special_select_callback(int index, void *ctx) {
  // Of course, you can do more complicated things in a menu item select callback
  // Here, we have a simple toggle
  special_flag = !special_flag;

  SimpleMenuItem *menu_item = &second_menu_items[index];

  if (special_flag) {
    menu_item->subtitle = "Okay, it's not so special.";
  } else {
    menu_item->subtitle = "Well, maybe a little.";
  }

  if (++hit_count > 5) {
    menu_item->title = "Very Special Item";
  }

  // Mark the layer to be updated
  layer_mark_dirty(simple_menu_layer_get_layer(simple_menu_layer));
}

void post_data (void){
    menu_icon_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_1);

  // Although we already defined NUM_FIRST_MENU_ITEMS, you can define
  // an int as such to easily change the order of menu items later
  int num_a_items = 0;
  if (text_tuple){
  // This is an example of how you'd set a simple menu item
  first_menu_items[num_a_items++] = (SimpleMenuItem){
    // You should give each menu item a title and callback
    .title = text_tuple->value->cstring,
    .callback = menu_select_callback,
  };
}
if (text_tuple2){
  // The menu items appear in the order saved in the menu items array
  first_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = text_tuple2->value->cstring,
    // You can also give menu items a subtitle
    //.subtitle = "Here's a subtitle",
    .callback = menu_select_callback,
  };
}
if (text_tuple3){
  first_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = text_tuple3->value->cstring,
    //.subtitle = "This has an icon",
    .callback = menu_select_callback,
    // This is how you would give a menu item an icon
    //.icon = menu_icon_image,
  };
}
if (text_tuple4){
    first_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = text_tuple4->value->cstring,
    //.subtitle = "This has an icon",
    .callback = menu_select_callback,
    // This is how you would give a menu item an icon
    //.icon = menu_icon_image,
  };
}
if (text_tuple5){
    first_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = text_tuple5->value->cstring,
    //.subtitle = "This has an icon",
    .callback = menu_select_callback,
    // This is how you would give a menu item an icon
    //.icon = menu_icon_image,
  };
}
if (text_tuple6){
    first_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = text_tuple6->value->cstring,
    //.subtitle = "This has an icon",
    .callback = menu_select_callback,
    // This is how you would give a menu item an icon
    //.icon = menu_icon_image,
  };
}
if (text_tuple7){
    first_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = text_tuple7->value->cstring,
    //.subtitle = "This has an icon",
    .callback = menu_select_callback,
    // This is how you would give a menu item an icon
    //.icon = menu_icon_image,
  };
}
/*
  // This initializes the second section
  second_menu_items[0] = (SimpleMenuItem){
    .title = "Special Item",
    // You can use different callbacks for your menu items
    .callback = special_select_callback,
  };
*/
  // Bind the menu items to the corresponding menu sections
  menu_sections[0] = (SimpleMenuSection){
    .title = "          Pay Someone!",
    .num_items = NUM_FIRST_MENU_ITEMS,
    .items = first_menu_items,
  };
  /*menu_sections[1] = (SimpleMenuSection){
    // Menu sections can also have titles as well
    .title = "Yet Another Section",
    .num_items = NUM_SECOND_MENU_ITEMS,
    .items = second_menu_items,
  };*/

  // Now we prepare to initialize the simple menu layer
  // We need the bounds to specify the simple menu layer's viewport size
  // In this case, it'll be the same as the window's
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  // Initialize the simple menu layer
  simple_menu_layer = simple_menu_layer_create(bounds, window, menu_sections, NUM_MENU_SECTIONS, NULL);

  // Add it to the window for display
  layer_add_child(window_layer, simple_menu_layer_get_layer(simple_menu_layer));
}
// This initializes the menu upon window load
static void window_load(Window *window) {
  // We'll have to load the icon before we can use it

}

// Deinitialize resources on window unload that were initialized on window load
void window_unload(Window *window) {
  simple_menu_layer_destroy(simple_menu_layer);

  // Cleanup the menu icon
  gbitmap_destroy(menu_icon_image);
}

 void friends_init(void) {

  window = window_create();


  // Setup the window handlers
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });   
    //window_stack_push(window, true /* Animated */);
    app_message_register_inbox_received(in_received_handler);
   app_message_register_inbox_dropped(in_dropped_handler);
   app_message_register_outbox_sent(out_sent_handler);
   app_message_register_outbox_failed(out_failed_handler);


   
 }

 void friends_deinit(void) {
    window_destroy(window);
 }
 
 void display_people(int index){
    window_stack_push(window, true);


   const uint32_t inbound_size = 124;
   const uint32_t outbound_size = 64;
   app_message_open(inbound_size, outbound_size);

   // create message to phone 
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    //original
    Tuplet value2 = TupletInteger(100, 15);

    Tuplet value3 = TupletInteger(101, 15);
    if (index){
    dict_write_tuplet(iter, &value3);

    } else {
    dict_write_tuplet(iter, &value2);
  }
    

    // send message
    app_message_outbox_send();
 }

