cmake_minimum_required(VERSION 3.16)
project(DGov C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "-mavx2 -maes -O3")

enable_language(ASM)

add_executable(DGov main.c util.h node.h nrns.h genann.c genann.h mcrypt.h vote.h net.h rainbow/api.h rainbow/api_config.h rainbow/blas.h rainbow/blas_comm.c rainbow/blas_comm.h rainbow/blas_config.h rainbow/blas_matrix.c rainbow/blas_matrix.h rainbow/blas_matrix_ref.c rainbow/blas_matrix_ref.h rainbow/blas_u32.h rainbow/blas_u64.h rainbow/gf16.h rainbow/gf16_u64.h rainbow/hash_len_config.h rainbow/parallel_matrix_op.c rainbow/parallel_matrix_op.h rainbow/rainbow.c rainbow/rainbow.h rainbow/rainbow_blas.h rainbow/rainbow_config.h rainbow/rainbow_keypair.c rainbow/rainbow_keypair.h rainbow/rainbow_keypair_computation.c rainbow/rainbow_keypair_computation.h rainbow/rainbow_publicmap.c rainbow/rbw.h rainbow/rng.c rainbow/rng.h rainbow/sign.c rainbow/utils.c rainbow/utils.h rainbow/utils_hash.c rainbow/utils_hash.h rainbow/utils_malloc.h rainbow/utils_prng.c rainbow/utils_prng.h blake3/blake3.c blake3/blake3_dispatch.c blake3/blake3_portable.c blake3/blake3_sse41_x86-64_unix.S blake3/blake3_avx2_x86-64_unix.S blake3/blake3_avx512_x86-64_unix.S hash.h blabla.h saber/verify.c saber/verify.h saber/rng2.c saber/rng2.h saber/randombytes2.c saber/randombytes2.h saber/poly.c saber/poly.h saber/pack_unpack.c saber/pack_unpack.h saber/kem.c saber/kem.h saber/fips202x4.c saber/fips202x4.h saber/fips202.c saber/fips202.h saber/crypto_stream.c saber/crypto_stream.h saber/cpucycles.c saber/cpucycles.h saber/cbd.c saber/cbd.h saber/api.h saber/SABER_params.h saber/SABER_indcpa.h saber/SABER_indcpa.c saber/polymul/consts.h saber/keccak4x/KeccakP-1600-times4-SnP.c saber/keccak4x/KeccakP-1600-times4-SnP.h saber/keccak4x/SIMD256-config.h saber/keccak4x/align.h saber/keccak4x/brg_endian.h saber/saber.h)

target_link_libraries(DGov -lm -lsodium -lssl -lcrypto)