function watchDirectory(node)
    local root = cc.FileUtils:getInstance():getDefaultResourceRootPath() .. 'src'
    local fw =
        cc.DirMonitor:create(
        root,
        function(dict)
            dump(dict, 'watchDirectory')
        end
    )
    if tolua.isnull(fw) then
        print('== cc.DirMonitor 创建失败 ==')
        return
    end
    print('== cc.DirMonitor 已创建 ==')

    -- 输出DirMonitor基础信息
    print('== cc.DirMonitor 基础信息==')
    print('cc.DirMonitor.dir ', fw:dir())
    print('-------------------------')

    -- 启动监听
    fw:watch()

    -- 用延时来观察DirMonitor暂停/恢复/关闭情况
    local time_handler_1 = function()
        fw:unwatch()
        print('== cc.DirMonitor.unwatch 暂停监听 ==')
        print('cc.DirMonitor.status', fw:status())
        print('-------------------------')
    end
    local time_handler_2 = function()
        fw:watch()
        print('== cc.DirMonitor.watch 重新监听 ==')
        print('cc.DirMonitor.status', fw:status())
        print('-------------------------')
    end
    local time_handler_3 = function()
        fw:shutdown()
        print('== cc.DirMonitor.shutdown 请求关闭 ==')
        print('cc.DirMonitor.status', tolua.isnull(fw) and -1 or fw:status())
        print('-------------------------')
    end
    local time_handler_4 = function()
        if tolua.isnull(fw) then
            print('== cc.DirMonitor 已关闭 ==')
            print('-------------------------')
            return
        end
    end

    performWithDelay(node, time_handler_1, 20) -- 20秒后暂停，对目录操作无效
    performWithDelay(node, time_handler_2, 40) -- 40秒后恢复，对目录操作有效
    performWithDelay(node, time_handler_3, 60) -- 60秒后关闭，对目录操作无效
    performWithDelay(node, time_handler_4, 80) -- 80秒后检测，此时fw无效了
end
