TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

include(../lib/glrayfw/glrayfw.pri)

HEADERS += \
    game/constants.h \
    game/ailib/blackboard.h \
    game/ailib/fsa.h \
    game/ailib/mapsearchnode.h \
    game/ailib/stlastar.h \
    game/app/app.h \
    game/entity/controller/bulletcontroller.h \
    game/entity/controller/mobaicontroller.h \
    game/entity/controller/moboptioncontroller.h \
    game/entity/controller/nullcontroller.h \
    game/entity/controller/pickupcontroller.h \
    game/entity/controller/playerhumancontroller.h \
    game/entity/script/effectsystem.h \
    game/entity/script/helpers.h \
    game/entity/script/inventory.h \
    game/entity/script/item.h \
    game/entity/script/playerskills.h \
    game/entity/script/playerweapon.h \
    game/entity/script/weapon.h \
    game/entity/actor.h \
    game/entity/bullet.h \
    game/entity/entityfactory.h \
    game/entity/mob.h \
    game/entity/pickup.h \
    game/entity/player.h \
    game/map/mapdata.h \
    game/map/mapgen.h \
    game/physics/contactlistener.h \
    game/render/assets.h \
    game/texgen/canvas.h \
    game/texgen/color.h \
    game/texgen/texgen.h

SOURCES += \
    game/main.cpp \
    game/app/app.cpp \
    game/entity/controller/mobaicontroller.cpp \
    game/entity/controller/moboptioncontroller.cpp \
    game/entity/controller/playerhumancontroller.cpp \
    game/entity/script/helpers.cpp \
    game/entity/script/inventory.cpp \
    game/entity/entityfactory.cpp \
    game/map/mapgen.cpp \
    game/physics/contactlistener.cpp \
    game/render/assets.cpp \
    game/texgen/canvas.cpp \
    game/texgen/texgen.cpp


