#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H

#include <SFML/Audio.hpp>
#include <map>

class AudioController
{
public:
    enum SoundType { 
        Ship_Thrusters,
        Ship_Destroyed,
        Weapon_Fire,
        Asteroid_Destroyed,
        SoundCount
    };
    
public:
    AudioController();
    ~AudioController();

    void playSound(SoundType);
    void playLoop(SoundType);
    void stopLoop(SoundType);
    
private:
    void loadSounds();
    
private:
    std::vector<sf::SoundBuffer> soundSources;
    std::vector<sf::Sound> playingSounds;
    std::map<SoundType, sf::Sound> loopSounds;
    
private:
    static const std::string THRUSTERS;
    static const std::string SHOOT;
    static const std::string EXPLOSION;
    static const std::string SHIP_EXPLOSION;

};

#endif // AUDIOCONTROLLER_H
