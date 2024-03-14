#include "plugin_manager.hpp"
#include "engine.hpp"

#include <map>

#include <dlfcn.h>

XL_NAMESPACE_BEGIN

class plugin_manager::impl {
public:
    err_code_t load_plugin(const std::string &path)
    {
#ifdef __WIN32
        // TODO
#else
        void *hdl = dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL);
        if (hdl == nullptr) {
            std::cout << "dlopen error: " << dlerror() << std::endl;
            // todo
            return -1;
        }
        auto func = reinterpret_cast<plugin_instance_function>(dlsym(hdl, PLUGIN_INSTANCE_FUNCTION_NAME));
        if (func == nullptr) {
            // todo
        }
#endif

        auto *plugin_ptr = func();
        plugins_.insert(std::make_pair(path, plugin_info{hdl, plugin_ptr}));

        if (plugin_ptr->init() != 0) {
            return -1;
        }
        for (auto conc : plugin_ptr->get_concretes()) {
            auto ret = engine::instance().regist(conc);
            if (ret != 0) {
                // todo
            }
        }
        return 0;
    }

    err_code_t unload_plugin(const std::string &path) {
        auto it = plugins_.find(path);
        if (it != plugins_.end()) {
            for (auto conc : it->second.plugin_ptr->get_concretes()) {
                auto ret = engine::instance().unregist(conc);
                if (ret != 0) {
                    // todo
                }
            }
#ifdef __WIN32
            // TODO
#else
            dlclose(it->second.handle);
#endif
            plugins_.erase(it);
        }

        return 0;
    }

private:
    struct plugin_info
    {
#ifdef __WIN32
        HMODULE handle;
#else
        void *handle;
#endif
        plugin *plugin_ptr;
    };
    
    std::map<std::string, plugin_info> plugins_;
};

plugin_manager &plugin_manager::instance()
{
    static plugin_manager ins;
    return ins;
}

plugin_manager::plugin_manager()
    : impl_(new impl)
{}

err_code_t plugin_manager::load_plugin(const std::string &path)
{
    return impl_->load_plugin(path);
}

err_code_t plugin_manager::unload_plugin(const std::string &path)
{
    return impl_->unload_plugin(path);
}

XL_NAMESPACE_END
