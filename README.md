# cocos2d-x-dir-monitor

## 一、介绍

**cocos2d-x-dir-monitor** 是内嵌到 Cocos2d-x 中的目录监视器，用以检测文件变化，比如：

- 新增
- 修改
- 删除
- 移动

也就是说，借助目录监视器，我们就可以获取变动的文件，这个尤其在使用 Lua 开发时有用，因为 Lua 热重载的基础就是检测文件变化，针对变化的文件决定是否进行热重载，以及热重载的策略。

# 二、实现

**cocos2d-x-dir-monitor** 的目录检测基于 [dmon](https://github.com/septag/dmon)，因为是单文件，所以移植也很简单。

首先把它 clone 下来，提取有用的文件丢到 cocos2d-x 的 external 下。

然后，把它添加到引用库中，编译一下。

接着，我们来封装一下接口。

让我们看看它的测试用例：

```cpp
#include <stdio.h>

#define DMON_IMPL
#include "dmon.h"

static void watch_callback(dmon_watch_id watch_id, dmon_action action, const char* rootdir,
                           const char* filepath, const char* oldfilepath, void* user)
{
    (void)(user);
    (void)(watch_id);

    switch (action) {
    case DMON_ACTION_CREATE:
        printf("CREATE: [%s]%s\n", rootdir, filepath);
        break;
    case DMON_ACTION_DELETE:
        printf("DELETE: [%s]%s\n", rootdir, filepath);
        break;
    case DMON_ACTION_MODIFY:
        printf("MODIFY: [%s]%s\n", rootdir, filepath);
        break;
    case DMON_ACTION_MOVE:
        printf("MOVE: [%s]%s -> [%s]%s\n", rootdir, oldfilepath, rootdir, filepath);
        break;
    }
}

int main(int argc, char* argv[])
{
    if (argc > 1) {
        dmon_init();
        puts("waiting for changes ..");
        dmon_watch(argv[1], watch_callback, DMON_WATCHFLAGS_RECURSIVE, NULL);
        getchar();
        dmon_deinit();
    } else {
        puts("usage: test dirname");
    }
    return 0;
}
```

可见，使用非常简单：

1. `dmon_init` 可以理解为初始化一个目录监视器
2. `dmon_watch` 可以理解为开始对某个目录进行监视，并添加回调
3. `dmon_uninit` 可以理解为关闭监视器

## 未完待续
