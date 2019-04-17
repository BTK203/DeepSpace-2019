#ifndef SETTINGS_H
#define SETTINGS_H

/**
 * Settings file, contains settings class
 * Written By: Brach Knutson
 */

class Settings {
    public:
    static const bool USE_CAMERA = true;

    static const int CAMERA_RESOLUTION_X = 320,
                     CAMERA_RESULUTION_Y = 240,
                     CAMERA_FOV = 90;

    static const int MIN_AREA = 250;
    
    static constexpr double ASPECT_RATIO   = 1.5,
                            AR_ERROR       = 0.5,
                            SOLIDITY       = 0.85,
                            SOLIDITY_ERROR = 0.25;
};

#endif