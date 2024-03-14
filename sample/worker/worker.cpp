#include <iostream>

#include "complex.hpp"

#include <xl/plugin_manager.hpp>

using namespace std;
using namespace xl;

namespace {
    void SetUp() {
        plugin_manager::instance().load_plugin("./lib/libplugin_sample.so");
    }

    void TearDown() {
        plugin_manager::instance().unload_plugin("./lib/libplugin_sample.so");
    }
}

int main(int argc, char *argv[]) {
    auto test_complex_add = [] {
        sample::complex_t x{4.5, 5.6};
        sample::complex_t y{3.2, 8.1};

        sample::complex_add complexAdd;
        auto ret = complexAdd(x, y);

        if (ret.first == 0) {
            cout << "complexAdd: res = " << ret.second.value().real << " + " << ret.second.value().image << "j." << endl;
        } else {
            cout << "complexAdd failed: ret = " << ret.first << "." << endl;
        }
    };

    test_complex_add();
    SetUp();
    test_complex_add();
    TearDown();
    test_complex_add();

    return 0;
}
