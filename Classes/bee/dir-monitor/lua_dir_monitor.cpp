#include "bee/dir-monitor/bee_dir_monitor.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "CCLuaEngine.h"
#include "lua.h"

static int lua_dir_monitor_make(lua_State* L)
{
	(DirMonitor*)tolua_tousertype(L, 1, 0);
	return 0;
}

static int lua_dir_monitor_create(lua_State* L)
{
	if (NULL == L)
		return 0;

	int argc = 0;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(L, 1, "cc.DirMonitor", 0, &tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(L) - 1;
	if (argc == 1)
	{
		if (!lua_isstring(L, 2)) {
			luaL_error(L, "invalid 'rootdir' in function 'lua_dir_monitor_create'.\n");
			return 0;
		}

		std::string rootdir;
		ok &= luaval_to_std_string(L, 2, &rootdir, "cc.DirMonitor:create");
		if (!ok) goto tolua_lerror;

		DirMonitor *fw = DirMonitor::create(rootdir);
		object_to_luaval<DirMonitor>(L, "cc.DirMonitor", (DirMonitor*)fw);

		return 1;
	}
	else if (argc == 2)
	{
		if (!lua_isstring(L, 2)) {
			luaL_error(L, "invalid 'rootdir' in function 'lua_dir_monitor_create'.\n");
			return 0;
		}

		if (!lua_isfunction(L, 3)) {
			luaL_error(L, "invalid 'listener' in function 'lua_dir_monitor_create'.\n");
			return 0;
		}

		string rootdir;
		ok &= luaval_to_std_string(L, 2, &rootdir, "cc.DirMonitor:create");
		if (!ok) goto tolua_lerror;

		LUA_FUNCTION listener = (toluafix_ref_function(L, 3, 0));
		DirMonitor *fw = DirMonitor::create(rootdir, listener);
		object_to_luaval<DirMonitor>(L, "cc.DirMonitor", (DirMonitor*)fw);

		return 1;
	}

	luaL_error(L, "create wrong number of arguments: %d, was expecting %d/%d\n", argc, 1, 2);
	return 0;

#if COCOS2D_DEBUG >= 1
	tolua_lerror:
		tolua_error(L, "#ferror in function 'lua_dir_monitor_create'.\n", &tolua_err);
#endif
	return 0;
}

static int lua_dir_monitor_watch(lua_State* L)
{
	if (NULL == L)
		return 0;

	int argc = 0;
	DirMonitor* cobj;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(L, 1, "cc.DirMonitor", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (DirMonitor*)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(L, "invalid 'cobj' in function 'lua_dir_monitor_watch'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(L) - 1;

	if (argc == 0)
	{
		cobj->watch();
		return 1;
	}
	luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DirMonitor:watch", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
	tolua_lerror:
		tolua_error(L, "#ferror in function 'lua_dir_monitor_watch'.\n", &tolua_err);
#endif
	return 0;
}

static int lua_dir_monitor_unwatch(lua_State* L)
{
	if (NULL == L)
		return 0;

	int argc = 0;
	DirMonitor* cobj;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(L, 1, "cc.DirMonitor", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (DirMonitor*)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(L, "invalid 'cobj' in function 'lua_dir_monitor_unwatch'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(L) - 1;

	if (argc == 0)
	{
		cobj->unwatch();
		return 1;
	}
	luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DirMonitor:unwatch", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
	tolua_lerror:
		tolua_error(L, "#ferror in function 'lua_dir_monitor_unwatch'.\n", &tolua_err);
#endif
	return 0;
}

static int lua_dir_monitor_shutdown(lua_State* L)
{
	if (NULL == L)
		return 0;

	int argc = 0;
	DirMonitor* cobj;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(L, 1, "cc.DirMonitor", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (DirMonitor*)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(L, "invalid 'cobj' in function 'lua_dir_monitor_shutdown'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(L) - 1;

	if (argc == 0)
	{
		cobj->shutdown();
		return 1;
	}
	luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DirMonitor:shutdown", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
	tolua_lerror:
		tolua_error(L, "#ferror in function 'lua_dir_monitor_shutdown'.\n", &tolua_err);
#endif
	return 0;
}

static int lua_dir_monitor_dir(lua_State* L)
{
	if (NULL == L)
		return 0;

	int argc = 0;
	DirMonitor* cobj;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(L, 1, "cc.DirMonitor", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (DirMonitor*)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(L, "invalid 'cobj' in function 'lua_dir_monitor_dir'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(L) - 1;

	if (argc == 0)
	{
		string ret = cobj->dir();
		tolua_pushstring(L, ret.c_str());
		return 1;
	}
	luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DirMonitor:dir", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
	tolua_lerror:
		tolua_error(L, "#ferror in function 'lua_dir_monitor_dir'.\n", &tolua_err);
#endif
	return 0;
}

static int lua_dir_monitor_setLuaListener(lua_State* L)
{
	if (NULL == L)
		return 0;

	int argc = 0;
	DirMonitor* cobj;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(L, 1, "cc.DirMonitor", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (DirMonitor*)tolua_tousertype(L, 1, 0);
	if (!cobj)
	{
#if COCOS2D_DEBUG >= 1
		tolua_error(L, "invalid 'cobj' in function 'lua_dir_monitor_setLuaListener'", nullptr);
#endif
		return 0;
	}

	argc = lua_gettop(L) - 1;
	if (argc == 1)
	{
		if (!lua_isfunction(L, 2)) {
			luaL_error(L, "invalid 'listener' in function 'lua_dir_monitor_setLuaListener'.\n");
			return 0;
		}
		LUA_FUNCTION listener = (toluafix_ref_function(L, 2, 0));
		cobj->setLuaListener(listener);
		return 1;
	}

	luaL_error(L, "create wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;

#if COCOS2D_DEBUG >= 1
	tolua_lerror:
		tolua_error(L, "#ferror in function 'lua_dir_monitor_setLuaListener'.\n", &tolua_err);
#endif
	return 0;
}

static int lua_dir_monitor_status(lua_State* L)
{
	if (NULL == L)
		return 0;

	int argc = 0;
	DirMonitor* cobj;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(L, 1, "cc.DirMonitor", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (DirMonitor*)tolua_tousertype(L, 1, 0);
#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(L, "invalid 'cobj' in function 'lua_dir_monitor_status'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(L) - 1;

	if (argc == 0)
	{
		int ret = cobj->status();
		tolua_pushnumber(L, ret);
		return 1;
	}
	luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DirMonitor:status", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
	tolua_lerror:
		tolua_error(L, "#ferror in function 'lua_dir_monitor_status'.\n", &tolua_err);
#endif
	return 0;
}


TOLUA_API int lua_module_register_dir_monitor(lua_State* L) {
	lua_getglobal(L, "_G");
	if (lua_istable(L, -1))
	{
		tolua_open(L);
		tolua_usertype(L, "cc.DirMonitor");
		tolua_module(L, "cc", 0);
		tolua_beginmodule(L, "cc");
		tolua_cclass(L, "DirMonitor", "cc.DirMonitor", "cc.Ref", lua_dir_monitor_make);
		tolua_beginmodule(L, "DirMonitor");
		tolua_function(L, "create", lua_dir_monitor_create);
		tolua_function(L, "watch", lua_dir_monitor_watch);
		tolua_function(L, "unwatch", lua_dir_monitor_unwatch);
		tolua_function(L, "shutdown", lua_dir_monitor_shutdown);
		tolua_function(L, "status", lua_dir_monitor_status);
		tolua_function(L, "setLuaListener", lua_dir_monitor_setLuaListener);
		tolua_function(L, "dir", lua_dir_monitor_dir);
		tolua_endmodule(L);
		tolua_endmodule(L);
	}
	lua_pop(L, 1);
	return 1;
}