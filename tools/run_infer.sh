#!/bin/bash

mkdir -p build/Analysis/Infer

${INFER_PATH}/infer run \
  --compilation-database build/Analysis/tmp/Infer/compile_commands.json \
  --keep-going \
  --skip-analysis-in-path build/ \
  --skip-analysis-in-path-skips-compilation \
  --cost \
  --headers \
  --loop-hoisting \
  --purity \
  --pulse \
  --quandary \
  --quandaryBO \
  --siof \
  --starvation \
  --siof-check-iostreams \
  --bufferoverrun \
  --liveness \
  --uninit \
  --biabduction \
  --jobs 4 \
  --enable-issue-type ARRAY_OUT_OF_BOUNDS_L1 \
  --enable-issue-type ARRAY_OUT_OF_BOUNDS_L2 \
  --enable-issue-type ARRAY_OUT_OF_BOUNDS_L3 \
  --enable-issue-type BUFFER_OVERRUN_L4 \
  --enable-issue-type BUFFER_OVERRUN_L5 \
  --enable-issue-type BUFFER_OVERRUN_U5 \
  --enable-issue-type CLASS_CAST_EXCEPTION \
  --enable-issue-type CLASS_CAST_EXCEPTION \
  --enable-issue-type CONDITION_ALWAYS_FALSE \
  --enable-issue-type CONDITION_ALWAYS_TRUE \
  --enable-issue-type DANGLING_POINTER_DEREFERENCE \
  --enable-issue-type DIVIDE_BY_ZERO \
  --enable-issue-type EXPENSIVE_ALLOCATION \
  --enable-issue-type EXPENSIVE_ALLOCATION_COLD_START \
  --enable-issue-type EXPENSIVE_EXECUTION_TIME \
  --enable-issue-type EXPENSIVE_EXECUTION_TIME_COLD_START \
  --enable-issue-type EXPENSIVE_ALLOCATION_COLD_START \
  --enable-issue-type GLOBAL_VARIABLE_INITIALIZED_WITH_FUNCTION_OR_METHOD_CALL \
  --enable-issue-type INFINITE_ALLOCATION \
  --enable-issue-type INFINITE_EXECUTION_TIME \
  --enable-issue-type INTEGER_OVERFLOW_L5 \
  --enable-issue-type INTEGER_OVERFLOW_U5 \
  --enable-issue-type NULL_TEST_AFTER_DEREFERENCE \
  --enable-issue-type RETURN_VALUE_IGNORED \
  --enable-issue-type STACK_VARIABLE_ADDRESS_ESCAPE \
  --enable-issue-type UNARY_MINUS_APPLIED_TO_UNSIGNED_EXPRESSION \
  --enable-issue-type UNTRUSTED_BUFFER_ACCESS \
  --enable-issue-type UNTRUSTED_HEAP_ALLOCATION \
  --enable-issue-type ZERO_ALLOCATION \
  --enable-issue-type ZERO_EXECUTION_TIME \
  --type-size \
  --uninit-interproc \
  --no-hoisting-report-only-expensive \
  --pmd-xml \
  --results-dir build/Analysis/Infer