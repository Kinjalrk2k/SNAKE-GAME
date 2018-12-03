#ifndef AI_H
#define AI_H

#include "game.h"

class AI : public game
{
    protected:
        double dist;
        double shortest_dist[4];
        position dummy_head[4];

        void set_dummy_heads();
        double calc_dist(position dummy_head);
        bool equate_position();

    public:
        void run_AI();
};

#endif