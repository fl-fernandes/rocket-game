#include "audio.h"

namespace engine 
{
    sound_t::sound_t () {};

    sound_t::sound_t (const char *wav_path)
    {
        this->set_sound(wav_path);
    };

    sound_t::~sound_t ()
    {
        this->destroy();
    }

    bool sound_t::load ()
    {
        Mix_Chunk *sound = Mix_LoadWAV(this->wav_path.c_str());

        if (sound == nullptr)
            return false;

        if (this->sound != nullptr)
            Mix_FreeChunk(this->sound);

        this->sound = sound;
        return true;
    }

    bool sound_t::set_sound (const char *wav_path)
    {
        this->wav_path = wav_path;
        return this->load();
    }

    void sound_t::set_volume (int volume)
    {
        Mix_VolumeChunk(this->sound, volume);
    }

    void sound_t::play ()
    {
        if (!this->is_playable())
            this->load();

        Mix_PlayChannel(-1, this->sound, 0);
    }

    void sound_t::destroy ()
    {
        if (this->is_playable())
            Mix_FreeChunk(this->sound);
    }

    music_t::music_t () {};

    music_t::music_t (const char *wav_path)
    {
        this->set_music(wav_path);
    };

    music_t::~music_t ()
    {
        this->destroy();
    }

    bool music_t::load ()
    {
        Mix_Music *music = Mix_LoadMUS(this->wav_path.c_str());

        if (music == nullptr)
            return false;

        if (this->music != nullptr)
            Mix_FreeMusic(this->music);

        this->music = music;
        return true;
    }

    bool music_t::set_music (const char *wav_path)
    {
        this->wav_path = wav_path;
        return this->load();
    }

    void music_t::play ()
    {
        if (!this->is_playable())
            this->load();
            
        Mix_PlayMusic(this->music, -1);
    }

    void music_t::destroy ()
    {
        if (this->is_playable())
            Mix_FreeMusic(this->music);
    }
}
