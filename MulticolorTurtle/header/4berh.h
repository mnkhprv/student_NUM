#ifndef BERH4_H
#define BERH4_H

namespace berh4 {
    void run_game(int argc, char** argv);

    void init();
    void render();
    bool on_key(unsigned char key);
    void on_timer();
}

#endif
