#ifndef OLYMPUS
#define OLYMPUS

#define OLYMPUS_VERSION_MAJOR 0
#define OLYMPUS_VERSION_MINOR 1
#define OLYMPUS_ROOT_DIR "/media/development/olympus"

#include "window/window.hpp"
#include "window/window_manager.hpp"

#include "debug/logger.hpp"
#include "debug/appender.hpp"
#include "debug/file_appender.hpp"
#include "debug/stream_appender.hpp"
#include "debug/fps.hpp"

#include "render/shaders.hpp"
#include "render/standard_render_engine.hpp"
#include "render/resource_manager.hpp"

#include "terrain/terrain.hpp"
#include "terrain/water.hpp"

#include "world/light.hpp"
#include "world/world_object.hpp"
#include "world/renderable.hpp"

#endif
