#include "engine.hpp"

#include <map>

namespace xl {

class engine::impl {
public:
    int32_t regist(concrete_hdl hdl)
    {
        auto it_gid = concretes_.find(hdl->gid());
        if (it_gid == concretes_.end()) {
            concretes_[hdl->gid()][hdl->cid()] = hdl;
            return 0;
        }

        auto it_cid = it_gid->second.find(hdl->cid());
        if (it_cid == it_gid->second.end()) {
            it_gid->second[hdl->cid()] = hdl;
            return 0;
        }

        return -1;
    }

    int32_t unregist(concrete_hdl hdl)
    {
        auto it_gid = concretes_.find(hdl->gid());
        if (it_gid == concretes_.end()) {
            return -1;
        }

        auto it_cid = it_gid->second.find(hdl->cid());
        if (it_cid == it_gid->second.end()) {
            return -1;
        }

        it_gid->second.erase(it_cid);
        if (it_gid->second.empty()) {
            concretes_.erase(it_gid);
        }

        return 0;
    }

    std::vector<concrete_hdl> query(const gid_t &gid) const
    {
        auto it_gid = concretes_.find(gid);
        if (it_gid == concretes_.end()) {
            return {};
        }

        std::vector<concrete_hdl> result(it_gid->second.size());
        std::transform(it_gid->second.cbegin(), it_gid->second.cend(), result.begin(),
            [&result](const std::pair<std::string, concrete_hdl> &item) {
                return item.second;
            });
        return result;
    }

private:
    std::map<std::string, std::map<std::string, concrete_hdl>> concretes_;
};

engine &engine::instance()
{
    static engine ins;
    return ins;
}

engine::engine()
    : impl_(new impl)
{
}

int32_t engine::regist(concrete_hdl hdl)
{
    return impl_->regist(hdl);
}

int32_t engine::unregist(concrete_hdl hdl)
{
    return impl_->unregist(hdl);
}

std::vector<concrete_hdl> engine::query(const gid_t &gid) const
{
    return impl_->query(gid);
}

} // namespace xl
