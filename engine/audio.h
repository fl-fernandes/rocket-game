#ifndef __ENGINE_SOUND__
#define __ENGINE_SOUND__

#include <SDL2/SDL_mixer.h>
#include <string>
#include "lib.h"

namespace engine
{
    class sound_t
    {
        private:
            Mix_Chunk *sound = nullptr;
            std::string wav_path;

        public:
            ~sound_t ();
            sound_t ();
            sound_t (const char *wav_path);

        private:
            bool load ();

        public:
            inline std::string get_sound_path ()
            {
                return this->wav_path;
            }
            inline bool is_playable ()
            {
                return this->sound != nullptr;
            }
        
        public:
            bool set_sound (const char *wav_path);
            void set_volume (int volume);
            void play ();
            void destroy ();
    };

    class music_t
    {
        private:
            Mix_Music *music = nullptr;
            std::string wav_path;

        public:
            ~music_t ();
            music_t ();
            music_t (const char *wav_path);

        private:
            bool load ();

        public:
            inline std::string get_music_path ()
            {
                return this->wav_path;
            }
            inline bool is_playable ()
            {
                return this->music != nullptr;
            }
        
        public:
            bool set_music (const char *wav_path);
            void play ();
            void destroy ();

        public:
            static void set_volume (int volume)
            {
                Mix_VolumeMusic(volume);
            }
            static void pause ()
            {
                Mix_PauseMusic();
            }
            static void resume ()
            {
                Mix_ResumeMusic();
            }
            static void rewind ()
            {
                Mix_RewindMusic();
            }
    };
}

#endif