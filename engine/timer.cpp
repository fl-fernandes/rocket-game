#include "timer.h"

namespace engine
{
    timer_t *timer_t::_instance = nullptr;

    timer_t* timer_t::instance ()
    {
        if (_instance == nullptr)
            _instance = new timer_t();

        return _instance;
    }

    void timer_t::release ()
    {
        delete _instance;
        _instance = nullptr;
    }

    timer_t::timer_t ()
    {
        this->reset();
        this->time_scale = 1.0f;
        this->delta_time = std::chrono::duration<float>(0.0f);
    }

    timer_t::~timer_t () {}

    void timer_t::reset ()
    {
        this->start_time = clock_t::now();
    }

    float timer_t::get_delta_time ()
    {
        return this->delta_time.count();
    }

    void timer_t::tick ()
    {
        this->delta_time = clock_t::now() - this->start_time;
    }
}