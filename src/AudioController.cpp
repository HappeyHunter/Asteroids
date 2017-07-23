#include "AudioController.h"

const std::string AudioController::THRUSTERS = "Resources/Audio/Thrusters.ogg";
const std::string AudioController::SHOOT = "Resources/Audio/Shoot.ogg";
const std::string AudioController::EXPLOSION = "Resources/Audio/Explosion.ogg";
const std::string AudioController::SHIP_EXPLOSION = "Resources/Audio/ShipExplosion.ogg";

AudioController::AudioController() : soundSources(SoundCount)
{
    loadSounds();
}

AudioController::~AudioController()
{

}

void AudioController::loadSounds()
{
    soundSources.at(Ship_Thrusters).loadFromFile(THRUSTERS);
    soundSources.at(Ship_Destroyed).loadFromFile(SHIP_EXPLOSION);
    soundSources.at(Weapon_Fire).loadFromFile(SHOOT);
    soundSources.at(Asteroid_Destroyed).loadFromFile(EXPLOSION);
}

void AudioController::playSound(AudioController::SoundType soundType)
{
    bool freeSound {false};
    for(unsigned int i = 0; i < playingSounds.size() && !freeSound; i++) {
        if(playingSounds.at(i).getStatus() == sf::Sound::Stopped) {
            freeSound = true;
            playingSounds.at(i).setBuffer(soundSources.at(soundType));
            playingSounds.at(i).play();
        }
    }
    
    if(!freeSound) {        
        playingSounds.emplace_back(sf::Sound(soundSources.at(soundType)));
        playingSounds.at(playingSounds.size()-1).play();
    }
}

void AudioController::playLoop(AudioController::SoundType soundType)
{
    auto search = loopSounds.find(soundType);
    
    if(search != loopSounds.end()) {
        if(search->second.getStatus() != sf::Sound::Playing) {
            search->second.play();
        }
    } else {
        sf::Sound newSound;
        newSound.setBuffer(soundSources.at(soundType));
        newSound.setLoop(true);
        
        loopSounds.insert(std::make_pair(soundType, newSound));
        
        search = loopSounds.find(soundType);
        search->second.play();
    }
}

void AudioController::stopLoop(AudioController::SoundType soundType)
{
    auto search = loopSounds.find(soundType);
    
    if(search != loopSounds.end()) {
        search->second.stop();
    }
}
