#ifndef __ENGINE_TIMER__
#define __ENGINE_TIMER__

#include <chrono>

namespace engine
{
    class timer_t
    {
        using clock_t = std::chrono::steady_clock;

        private:
            static timer_t *_instance;
            clock_t::time_point start_time;
            std::chrono::duration<float> delta_time;
            float time_scale;
        
        public:
            static timer_t* instance();
            static void release ();
            void reset ();
            float get_delta_time ();
            void tick ();

        public:
            inline void set_time_scale(float time_scale = 1.0f)
            {
                this->time_scale = time_scale;
            }
            inline float get_time_scale()
            {
                return this->time_scale;
            }

        private:
            timer_t();
            ~timer_t();
    };
}

#endif
