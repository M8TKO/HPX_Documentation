#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>

#include <hpx/async_local/dataflow.hpp>
#include <hpx/modules/actions_base.hpp>

#include <iostream>
#include <vector>
#include <hpx/future.hpp>
#include <hpx/thread.hpp>
#include <hpx/algorithm.hpp>

int counter = 0;

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
    std::cout << "add_vectors: Value of counter: " << counter << std::endl;
    counter++;
    return result;
}

std::vector<double> scalar_vector(const double& alpha, const std::vector<double>& vec){
    std::vector<double> result(vec.size());
    hpx::ranges::transform( 
        hpx::execution::par, // ExPolicy, 
        vec.begin(), 
        vec.end(), 
        result.begin(),
        [&](double x) {return alpha * x;});
    std::cout << "scalar_vectors: Value of counter: " << counter << std::endl;
    counter++;
    return result;
}

int hpx_main(){
    const int N = 1e6;
    std::vector<double> init_a(N, 1.0);
    std::vector<double> init_b(N, 2.0);
    std::vector<double> init_c(N, 20.0);
    double alpha = 10;

    hpx::future<std::vector<double>> a = hpx::make_ready_future(init_a);
    hpx::future<std::vector<double>> b = hpx::make_ready_future(init_b);
    hpx::future<std::vector<double>> c = hpx::make_ready_future(init_c);
    
    hpx::future<std::vector<double>> sum_ab = hpx::dataflow(hpx::unwrapping(add_vectors), a, b);
    std::cout << "This is called AFTER the FIRST sum" << std::endl;

    hpx::future<std::vector<double>> product = hpx::dataflow(hpx::unwrapping(scalar_vector), alpha, sum_ab);
    std::cout << "This is called AFTER the scaling" << std::endl;

    hpx::future<std::vector<double>> sum_c_product = hpx::dataflow(hpx::unwrapping(add_vectors), c, product);
    std::cout << "This is called AFTER the SECOND sum" << std::endl;

    std::vector<double> result = sum_c_product.get();
    for(int i = 0 ; i < 10 ; i++ )
        std::cout << result[i] << " ";
    std::cout << std::endl;
    
    return hpx::finalize();
}

int main(){
    return hpx::init();
}