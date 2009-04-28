#include <SDL.h>

/* We keep handles to these to pass control to a previously installed
 * SDL event filter when appropriate
 */
static SDL_EventFilter oj_sdl_old_event_filter = NULL;
static void * oj_sdl_old_event_filter_user_data = NULL;

/* This is the actual implementation of our event filter. This allows
 * us to transform user input events, such as mocking up a mouse from
 * the input of a player's joystick.
 */
static int oj_sdl_event_filter(void *userdata, SDL_Event *event) {
    /* Give any event filter that was installed before us a crack at this */
    if (oj_sdl_old_event_filter)
        return oj_sdl_old_event_filter(oj_sdl_old_event_filter_user_data, event);
}

/* The client application calls this function to register our event filter,
 * it will also respect the current event filter, but it will be a lower
 * priority.
 */
void oj_register_sdl_event_filter() {
    /* Fetch old event filter, it will be our responsibility to respect it */
    SDL_GetEventFilter(&oj_sdl_old_event_filter, &oj_sdl_old_event_filter_user_data);

    /* This should never happen, but we'll make sure that we didn't
     * somehow register our event filter with SDL twice */
    if (oj_sdl_old_event_filter == oj_sdl_event_filter) {
        fprintf(stderr, __FILE__":%d oj_register_sdl_event_filter() called twice?\n", __LINE__);
        oj_sdl_old_event_filter = NULL;
        oj_sdl_old_event_filter_user_data = NULL;
    }

    /* Register our own event filter! */
    SDL_SetEventFilter(oj_sdl_event_filter, NULL);
}

