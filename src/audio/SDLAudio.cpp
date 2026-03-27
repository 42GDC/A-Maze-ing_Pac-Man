#include "audio/SDLAudio.hpp"
#include <iostream>

SDLAudio::SDLAudio() {
    // Init audio subsystem
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) == false) {
        std::cerr << "SDL Init Audio failed: " << SDL_GetError() << std::endl;
        return;
    }

    if (MIX_Init() == false) {
        std::cerr << "MIX_Init failed: " << SDL_GetError() << std::endl;
        return;
    }

    // Create mixer bound to default playback device
    mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    if (!mixer) {
        std::cerr << "MIX_CreateMixerDevice failed: " << SDL_GetError() << std::endl;
        return;
    }

    // Load SFX audio
    pelletAudio = MIX_LoadAudio(mixer, "assets/sounds/sfx_movement_footsteps5.wav", true);
    moveAudio   = MIX_LoadAudio(mixer, "assets/sounds/sfx_movement_jump1.wav", true);

    // Create persistent tracks
    if (pelletAudio) {
        pelletTrack = MIX_CreateTrack(mixer);
        std::cout << "Created pellet track: " << (pelletTrack ? "success" : "failure") << std::endl;
        MIX_SetTrackAudio(pelletTrack, pelletAudio);
        MIX_SetTrackGain(pelletTrack, PELLET_VOLUME * masterSFXVolume);
    }
    if (moveAudio) {
        moveTrack = MIX_CreateTrack(mixer);
        std::cout << "Created move track: " << (moveTrack ? "success" : "failure") << std::endl;
        MIX_SetTrackAudio(moveTrack, moveAudio);
        MIX_SetTrackGain(moveTrack, MOVE_VOLUME * masterSFXVolume);
    }

    // Load music as audio; we assign to track when playing
    menuMusicAudio = MIX_LoadAudio(mixer, "assets/music/title_screen.wav", false);
    gameMusicAudio = MIX_LoadAudio(mixer, "assets/music/ending.wav", false);

    musicTrack = nullptr;
}
SDLAudio::~SDLAudio() {
    // First, stop all tracks via the mixer
    if (mixer) {
        MIX_StopAllTracks(mixer, 0); // stop everything
    }
    // Now safe to destroy individual tracks
    if (pelletTrack) {
        MIX_DestroyTrack(pelletTrack);
        pelletTrack = nullptr;
    }
    if (moveTrack) {
        MIX_DestroyTrack(moveTrack);
        moveTrack = nullptr;
    }
    if (musicTrack) {
        MIX_DestroyTrack(musicTrack);
        musicTrack = nullptr;
    }

    // Destroy audio objects (safe even if assigned to old tracks)
    if (pelletAudio) {
        MIX_DestroyAudio(pelletAudio);
        pelletAudio = nullptr;
    }
    if (moveAudio) {
        MIX_DestroyAudio(moveAudio);
        moveAudio = nullptr;
    }
    if (menuMusicAudio) {
        MIX_DestroyAudio(menuMusicAudio);
        menuMusicAudio = nullptr;
    }
    if (gameMusicAudio) {
        MIX_DestroyAudio(gameMusicAudio);
        gameMusicAudio = nullptr;
    }

    // Finally destroy mixer
    if (mixer) {
        MIX_DestroyMixer(mixer);
        mixer = nullptr;
    }
    MIX_Quit();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);

    SDL_Quit();
}

void SDLAudio::playEvent(PacmanEvent event) {
    auto now = std::chrono::steady_clock::now();
    switch (event) {
        case PacmanEvent::PELLET_EATEN:
            if (pelletTrack) MIX_PlayTrack(pelletTrack, 0);
            break;

        case PacmanEvent::PLAYER_MOVED:
            if (moveTrack &&
                (now - lastMoveSoundTime >= moveSoundCooldown)) {
                MIX_PlayTrack(moveTrack, 0);
                lastMoveSoundTime = now;
            }
            break;

        case PacmanEvent::GAME_STARTED:
            playMusic("game", true);
            break;

        default:
            break;
    }
}

void SDLAudio::playMusic(const std::string& name, bool loop) {
    // Stop old music
    if (musicTrack) {
        MIX_StopTrack(musicTrack, 0);
        MIX_DestroyTrack(musicTrack);
        musicTrack = nullptr;
    }

    // Create new music track
    MIX_Audio* audio = nullptr;
    if (name == "menu") audio = menuMusicAudio;
    if (name == "game") audio = gameMusicAudio;

    if (!audio) return;

    musicTrack = MIX_CreateTrack(mixer);
    if (!musicTrack) return;

    MIX_SetTrackAudio(musicTrack, audio);
    MIX_SetTrackGain(musicTrack, masterMusicVolume);

    MIX_PlayTrack(musicTrack, loop ? -1 : 0);
}

void SDLAudio::stopMusic() {
    if (musicTrack) {
        MIX_StopTrack(musicTrack, 0);
        MIX_DestroyTrack(musicTrack);
        musicTrack = nullptr;
    }
}

void SDLAudio::setMasterSFXVolume(float vol) {
    masterSFXVolume = vol;
    if (pelletTrack) MIX_SetTrackGain(pelletTrack, PELLET_VOLUME * masterSFXVolume);
    if (moveTrack)   MIX_SetTrackGain(moveTrack, MOVE_VOLUME * masterSFXVolume);
}

void SDLAudio::setMasterMusicVolume(float vol) {
    masterMusicVolume = vol;
    if (musicTrack) MIX_SetTrackGain(musicTrack, masterMusicVolume);
}