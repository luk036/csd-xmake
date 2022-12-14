#include <benchmark/benchmark.h>
#include <csd/csd.hpp>

using namespace csd;

static void using_if_else(benchmark::State &state) {
  // Code inside this loop is measured repeatedly
  for (auto _ : state) {
    auto result = to_decimal("+00-00+00+0-0+0+.+00+00-0++");
    // Make sure the variable is not optimized away by compiler
    benchmark::DoNotOptimize(result);
  }
}
// Register the function as a benchmark
BENCHMARK(using_if_else);

static void using_switch(benchmark::State &state) {
  // Code inside this loop is measured repeatedly
  for (auto _ : state) {
    auto result = to_decimal_using_switch("+00-00+00+0-0+0+.+00+00-0++");
    // Make sure the variable is not optimized away by compiler
    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(using_switch);

BENCHMARK_MAIN();
