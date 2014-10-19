//
//  Consts.h
//  flappy_bird
//
//  Created by Avirmed Munkhbat on 10/9/14.
//
// consts and enums which are shared between classes are declared here.

#ifndef __CONSTS_H__
#define __CONSTS_H__

enum class kTag {
    kBackground,
    kBackgroundGround,
    kStartBird,
    kGetReady,
    kExplanation
};

enum class kZOrder {
    kBackground,
    kBackgroundGround,
    kStartBird
};

const std::string BACKGROUND_FILENAME = "lv1_background.png";
const std::string BACKGROUND_GROUND_FILENAME = "lv1_background_ground.png";
const std::string PLAY_BUTTON_FILENAME = "lv1_button_start.png";

const std::string RED_BIRD_NORMAL = "lv1_redbird_normal.png";
const std::string RED_BIRD_FLYUP = "lv1_redbird_flyup.png";
const std::string RED_BIRD_FLYDOWN = "lv1_redbird_flydown.png";

const std::string BLUE_BIRD_NORMAL = "lv1_bluebird_normal.png";
const std::string BLUE_BIRD_FLYUP = "lv1_bluebird_flyup.png";
const std::string BLUE_BIRD_FLYDOWN = "lv1_bluebird_flydown.png";

const std::string YELLOW_BIRD_NORMAL = "lv1_bird_normal.png";
const std::string YELLOW_BIRD_FLYUP = "lv1_bird_flyup.png";
const std::string YELLOW_BIRD_FLYDOWN = "lv1_bird_flydown.png";

const std::string FLAPPY_BIRD_LOGO_FILENAME = "lv1_logo.png";
const std::string GET_READY_TEXT_FILENAME = "lv1_text_getready.png";
const std::string EXPLANATION_FILENAME = "lv1_explanation.png";

const std::string PIPE_UP_FILENAME = "lv1_pipe_up.png";
const std::string PIPE_DOWN_FILENAME = "lv1_pipe_down.png";

const int PIPE_COUNT_SHOWN = 2;


const float BIRD_FRAME_DELAY = 0.2f;
const float BIRD_UP_AND_DOWN_ANIMATION_HEIGHT = 10.0f;
const float BIRD_MOVE_TIME = 0.4f;

const float BIRD_FLY_SPEED = 240.0f;
const float BIRD_FLY_TIME = 0.05f;

const int BIRD_COLLISION_MASK = 0x1;
const int OBSTACLE_COLLISION_MASK = 0x2;
const int POINT_COLLISION_MASK = 0x3;

enum class PhysicsBodyTag {
    GROUND = 1,
    PIPE = 10,
    BIRD = 20
};

enum class BirdType {
    RED,
    BLUE,
    YELLOW,
    COUNT
};

enum class BirdState {
    NORMAL,
    FLY,
    FALLING
};

enum class BirdActionTag {
    NORMAL,
    FLY,
    FALLING
};

#endif
