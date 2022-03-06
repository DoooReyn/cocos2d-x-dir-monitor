#include "dmon/dmon.h"
#include "bee_dir_monitor.h"

#define CS_TAG "===============> DirMonitor : "
#define FS_LOG(format, ...)	cocos2d::log(CS_TAG format, ##__VA_ARGS__)

static void watch_callback(dmon_watch_id watch_id, dmon_action action, const char* rootdir,
	const char* filepath, const char* oldfilepath, void* user)
{
	DirMonitor* fw = (DirMonitor *)user;
	if (fw != NULL) {
		switch (action) {
		case DMON_ACTION_CREATE:
			fw->onFileCreated(rootdir, filepath);
			break;
		case DMON_ACTION_DELETE:
			fw->onFileRemoved(rootdir, filepath);
			break;
		case DMON_ACTION_MODIFY:
			fw->onFileModified(rootdir, filepath);
			break;
		case DMON_ACTION_MOVE:
			fw->onFileMoved(rootdir, filepath, oldfilepath);
			break;
		}
	}
}

DirMonitor * DirMonitor::create(string dir)
{
	return create(dir, -1);
}

DirMonitor * DirMonitor::create(string dir, LUA_FUNCTION func)
{
	DirMonitor * ret = new (std::nothrow) DirMonitor(dir, func);
	if (ret && ret->init(dir, func))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

DirMonitor::~DirMonitor()
{
	dmon_deinit();
}

bool DirMonitor::init(string dir, LUA_FUNCTION func)
{
	retain();
	dmon_init();
	return true;
}

void DirMonitor::watch()
{
	if (m_state == State::None)
	{
		dmon_watch_id wid;
		wid = dmon_watch(m_dir.c_str(), watch_callback, DMON_WATCHFLAGS_RECURSIVE, this);
		m_wid = wid.id;
		m_state = State::Watching;
	}
}

void DirMonitor::unwatch()
{
	if (m_state == State::Watching)
	{
		dmon_watch_id wid;
		wid.id = m_wid;
		dmon_unwatch(wid);
		m_state = State::None;
	}
}

void DirMonitor::shutdown() 
{
	if (m_state != State::Dead) {
		m_state = State::Dead;
		release();
	}
}

void DirMonitor::onFileCreated(string rootdir, string filepath)
{
	CCLOG("CREATE: %s%s\n", rootdir.c_str(), filepath.c_str());
	if (m_listener > -1) {
		LuaValueDict dict;
		dict["action"] = LuaValue::intValue(Action::CREATE);
		dict["root"] = LuaValue::stringValue(rootdir);
		dict["file"] = LuaValue::stringValue(filepath);
		_callLuaFunction(dict);
	}
}

void DirMonitor::onFileModified(string rootdir, string filepath)
{
	FS_LOG("MODIFY: %s%s\n", rootdir.c_str(), filepath.c_str());
	if (m_listener > -1) {
		LuaValueDict dict;
		dict["action"] = LuaValue::intValue(Action::MODIFY);
		dict["root"] = LuaValue::stringValue(rootdir);
		dict["file"] = LuaValue::stringValue(filepath);
		_callLuaFunction(dict);
	}
}

void DirMonitor::onFileRemoved(string rootdir, string filepath)
{
	FS_LOG("DELETE: %s%s\n", rootdir.c_str(), filepath.c_str());
	if (m_listener > -1) {
		LuaValueDict dict;
		dict["action"] = LuaValue::intValue(Action::DELETE);
		dict["root"] = LuaValue::stringValue(rootdir);
		dict["file"] = LuaValue::stringValue(filepath);
		_callLuaFunction(dict);
	}
}

void DirMonitor::onFileMoved(string rootdir, string filepath, string oldfilepath) {
	FS_LOG("MOVE: %s%s -> %s%s\n", rootdir.c_str(), oldfilepath.c_str(), rootdir.c_str(), filepath.c_str());
	if (m_listener > -1) {
		LuaValueDict dict;
		dict["action"] = LuaValue::intValue(Action::MOVE);
		dict["root"] = LuaValue::stringValue(rootdir);
		dict["new"] = LuaValue::stringValue(filepath);
		dict["old"] = LuaValue::stringValue(oldfilepath);
		_callLuaFunction(dict);
	}
}

void DirMonitor::_callLuaFunction(LuaValueDict &dict)
{
	if (m_listener > -1) {
		LuaStack *stack = LuaEngine::getInstance()->getLuaStack();
		if (!stack) return;
		stack->pushLuaValueDict(dict);
		stack->executeFunctionByHandler(m_listener, 1);
		stack->clean();
	}
}