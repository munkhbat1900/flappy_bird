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
    kBackgroundGround
};

enum class kZOrder {
    kBackground,
    kBackgroundGround
};

const std::string BACKGROUND_FILENAME = "lv1_background.png";
const std::string BACKGROUND_GROUND_FILENAME = "lv1_background_ground.png";

#endif
