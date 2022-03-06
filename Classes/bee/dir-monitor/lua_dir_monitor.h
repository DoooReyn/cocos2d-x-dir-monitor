#ifndef __lua_dir_monitor_h__
#define __lua_dir_monitor_h__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

int lua_module_register_dir_monitor(lua_State* tolua_S);

#endif // __lua_dir_monitor_h__
