#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>

#include <hpx/async_local/dataflow.hpp>
#include <hpx/modules/actions_base.hpp>

#include <iostream>
#include <vector>
#include <hpx/future.hpp>
#include <hpx/thread.hpp>
#include <hpx/algorithm.hpp>

std::vector<double> add_vectors(const std::vector<double>& vec1, const std::vector<double>& vec2){
    std::vector<double> result(vec1.size());
    hpx::ranges::transform(
        hpx::execution::par, // ExPolicy
        vec1.begin(),   // FwdIter1
        vec1.end(), // Sent1
        vec2.begin(), // FwdIter2
        vec2.end(), // Sent2
        result.begin(), // FwdIter3
        [](double x, double y){
        return x + y;
    });
    return result;
}

int hpx_main(){
    const int N = 10;
    std::vector<double> init_a(N, 1.0);
    std::vector<double> init_b(N, 2.0);

    hpx::future<std::vector<double>> a = hpx::make_ready_future(init_a);
    hpx::future<std::vector<double>> b = hpx::make_ready_future(init_b);
    
    hpx::future<std::vector<double>> c = hpx::dataflow(hpx::unwrapping(add_vectors), a, b);
    
    return hpx::finalize();
}

int main(){
    return hpx::init();
}