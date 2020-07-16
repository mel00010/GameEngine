#!/bin/bash

set +o pipefail
mkdir -p build/Analysis/CodeChecker/ClangTidy
cat .codechecker_skip | sed "s|*/PROJECT_DIR|${WORKSPACE}|" > build/Analysis/CodeChecker/ClangTidy/.codechecker_skip
${CODECHECKER_PATH}/_CodeChecker analyze "build/Analysis/tmp/ClangTidy/compile_commands.json" \
  -j6 \
  --analyzers clang-tidy \
  --enable-all \
  -i build/Analysis/CodeChecker/ClangTidy/.codechecker_skip \
  --output build/Analysis/CodeChecker/ClangTidy/
