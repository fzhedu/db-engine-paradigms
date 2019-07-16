#pragma once
#include "common/runtime/Hashmap.hpp"
#include "vectorwise/Operators.hpp"
#include <assert.h>
#include "common/Compat.hpp"
#include "common/runtime/Concurrency.hpp"
#include "common/runtime/SIMD.hpp"
#include "hyper/ParallelHelper.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <x86intrin.h>
#include <string>
#include "vectorwise/Primitives.hpp"
#include <vector>
#include "common/runtime/Hash.hpp"
#include "common/defs.hpp"
#define VECTORSIZE 8
#define ROF_VECTOR_SIZE 10000
#define PDIS 2048
#define SEQ_PREFETCH 1
#define WRITE_SEQ_PREFETCH 0
static int stateNum = vectorwise::Hashjoin::stateNum;
static int stateNumSIMD = vectorwise::Hashjoin::imvNum;

#define UNLIKELY(expr) __builtin_expect(!!(expr), 0)
#define LIKELY(expr) __builtin_expect(!!(expr), 1)
using namespace vectorwise;
using namespace runtime;
using hash = runtime::MurMurHash;

using hash_t = defs::hash_t;
inline void v_prefetch(__m512i& vec){
  uint64_t * ht_pos = (uint64_t*)&vec;
  for (int i = 0; i < VECTORSIZE; ++i) {
    _mm_prefetch((char * )(ht_pos[i]), _MM_HINT_T0);
    _mm_prefetch(((char * )(ht_pos[i]) + 64), _MM_HINT_T0);
  }
}
size_t probe_row(types::Integer* probe_keys, uint32_t num, runtime::Hashmap* hash_table, void** output_build, uint32_t*output_probe, uint64_t* pos_buff=nullptr);
size_t probe_imv(types::Integer* probe_keys, uint32_t num, runtime::Hashmap* hash_table, void** output_build, uint32_t*output_probe, uint64_t* pos_buff=nullptr);
size_t probe_simd(types::Integer* probe_keys, uint32_t num, runtime::Hashmap* hash_table, void** output_build, uint32_t*output_probe, uint64_t* pos_buff=nullptr);
size_t probe_amac(types::Integer* probe_keys, uint32_t num, runtime::Hashmap* hash_table, void** output_build, uint32_t*output_probe, uint64_t* pos_buff=nullptr);
size_t probe_gp(types::Integer* probe_keys, uint32_t num, runtime::Hashmap* hash_table, void** output_build, uint32_t*output_probe, uint64_t* pos_buff=nullptr);
size_t probe_simd_amac(types::Integer* probe_keys, uint32_t num, runtime::Hashmap* hash_table, void** output_build, uint32_t*output_probe, uint64_t* pos_buff=nullptr);
