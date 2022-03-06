#ifndef __bee_dir_monitor_h__
#define __bee_dir_monitor_h__

#include <stdio.h>
#include <string>
#include "cocos2d.h"
#include "CCLuaEngine.h"

using namespace std;
using namespace cocos2d;

class DirMonitor : public Ref {
public:
	enum State
	{
		None = 0,
		Watching,
		Dead
	};
	enum Action {
		NONE = 0,
		CREATE,
		DELETE,
		MODIFY,
		MOVE
	};
	static DirMonitor* create(string dir);
	static DirMonitor* create(string dir, LUA_FUNCTION func);
	void watch();
	void unwatch();
	void shutdown();
	void setLuaListener(LUA_FUNCTION listener) {
		m_listener = listener;
	}
	string dir() { return m_dir; }
	int status() { return m_state; }
	void onFileCreated(string rootdir, string filepath);
	void onFileModified(string rootdir, string filepath);
	void onFileRemoved(string rootdir, string filepath);
	void onFileMoved(string rootdir, string filepath, string oldfilepath);

private:
	virtual ~DirMonitor();
	virtual bool init(string dir, LUA_FUNCTION func);
	DirMonitor(string dir, LUA_FUNCTION func)
		: m_dir(".")
		, m_state(State::None)
		, m_listener(-1)
	{
		if (dir.size() > 0) {
			m_dir = dir;
		}
		if (func >= 0) {
			m_listener = func;
		}
	}
	void _callLuaFunction(LuaValueDict &dict);
private:
	uint32_t m_wid;
	string m_dir;
	State m_state;
	//thread* m_thread;
	LUA_FUNCTION m_listener;
};

#endif // __bee_dir_monitor_h__
