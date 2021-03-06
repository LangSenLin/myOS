# include "kernel/print.h"
# include "init.h"
# include "interrupt.h"

# include "ioqueue.h"
# include "keyboard.h"

void k_thread_a(void*);
void k_thread_b(void*);

int main(void) {
    // 这里不能使用console_put_str，因为还没有初始化
    put_str("I am kernel.\n");
    init_all();
    
    thread_start("consumer_a", 31, k_thread_a, " A_");
    thread_start("consumer_b", 31, k_thread_b, " B_");

    intr_enable();

    while (1);

    return 0;
}

void k_thread_a(void* arg) 
{
    while (1) {
        enum intr_status old_status = intr_disable();
        if (!is_queue_empty(&keyboard_buffer)) {
            console_put_str(arg);
            char byte = queue_getchar(&keyboard_buffer);
            console_put_char(byte);
        }
        intr_set_status(old_status);
    }
}
void k_thread_b(void* arg) 
{
    while (1) {
        enum intr_status old_status = intr_disable();
        if (!is_queue_empty(&keyboard_buffer)) {
            console_put_str(arg);
            char byte = queue_getchar(&keyboard_buffer);
            console_put_char(byte);
        }
        intr_set_status(old_status);
    }
}
