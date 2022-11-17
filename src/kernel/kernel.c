#include <stdint.h>
#include <stddef.h>
#include <limine.h>

#include "serial.c"
 
// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent.
 
static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};
 
static void done(void) {
    for (;;) {
        __asm__("hlt");
    }
}
 
// The following will be our kernel's entry point.
void _start(void) {
    // Ensure we got a terminal
    if (terminal_request.response == NULL
     || terminal_request.response->terminal_count < 1) {
        done();
    }
 
    // We should now be able to call the Limine terminal to print out
    // a simple "Hello World" to screen.
    struct limine_terminal *terminal = terminal_request.response->terminals[0];
    // terminal_request.response->write(terminal, "[ OK ] Initialized terminal", 11);
    terminal_request.response->write(terminal, "Welcome to blahajOS!\n", 22);

	// Initialize serial

	init_serial();
	terminal_request.response->write(terminal, "[ OK ] Initialized Serial output", 32);
	write_serial("Y");

	

    // We're done, just hang...
    done();
}