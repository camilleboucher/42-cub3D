#include "app.h"
#include "menus.h"

int main(void) {
    struct s_app app;

    app = (struct s_app){ 0 };

    app_init(&app);

    open_main_menu(&app);

    app_destroy(&app);
}