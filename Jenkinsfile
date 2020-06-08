pipeline {
    agent any

    options {
        buildDiscarder(logRotator(numToKeepStr: '10'))
        skipDefaultCheckout()
    }
    parameters {
        string(name: 'CODECHECKER_PATH', defaultValue: '/home/mel/codechecker/build/CodeChecker/bin/_CodeChecker', description: 'Path to CodeChecker executable')
    }



    stages {
        /**
         * Checkout source code from Github on any of the GIT nodes
         */
        stage('Checkout') {
            environment {
                GITHUB_CREDS = credentials('GithubPAC')
            }
            steps {
                checkout([
                    $class: 'GitSCM',
                    branches: [[name: '*/master']],
                    doGenerateSubmoduleConfigurations: false,
                    extensions: [[
                        $class: 'SubmoduleOption',
                        disableSubmodules: false,
                        parentCredentials: true,
                        recursiveSubmodules: true,
                        reference: '',
                        trackingSubmodules: false
                    ]],
                    submoduleCfg: [],
                    userRemoteConfigs: [[
                        url: 'https://github.com/mel00010/GameEngine.git',
                        credentialsId: 'GithubPAC'
                    ]]
                ])
            }
        }
        stage('Build') {
            agent {
                dockerfile {
                    //args "-v ${PWD}/build/Release/_deps/:/host/Release/_deps -v ${PWD}/build/Debug/_deps/:/host/Debug/_deps -v ${PWD}/build/Coverage/_deps/:/host/Coverage/_deps -v /var/lib/jenkins/tools/:/var/lib/jenkins/tools/"
                    args "-v /var/lib/jenkins/tools/:/var/lib/jenkins/tools/"

                    reuseNode true
                }
            }
            steps {
//                cmakeBuild buildType: 'Release', generator: 'Ninja', buildDir: 'build/Release', installation: 'cmake-3.17.3', steps: [[args: 'clean']]
//                cmakeBuild buildType: 'Debug', generator: 'Ninja', buildDir: 'build/Debug', installation: 'cmake-3.17.3', steps: [[args: 'clean']]
//                cmakeBuild buildType: 'Coverage', generator: 'Ninja', buildDir: 'build/Coverage', installation: 'cmake-3.17.3', steps: [[args: 'clean']]
                cmakeBuild buildType: 'Release', generator: 'Ninja', buildDir: 'build/Release', installation: 'cmake-3.17.3', steps: [[args: 'all']]
                cmakeBuild buildType: 'Debug', generator: 'Ninja', buildDir: 'build/Debug', installation: 'cmake-3.17.3', steps: [[args: 'all']]
                cmakeBuild buildType: 'Coverage', generator: 'Ninja', buildDir: 'build/Coverage', installation: 'cmake-3.17.3', steps: [[args: 'all']]
                cmakeBuild buildType: 'Debug', generator: 'Ninja', buildDir: 'build/DebugNoPCH', installation: 'cmake-3.17.3', steps: [[args: '-DDISABLE_PCH=True all']]
            }
        }
        stage('Test') {
            parallel {
                stage('Test Release') {
                    agent {
                        dockerfile {
                            //args "-v ${PWD}/build/Release/_deps/:/host/Release/_deps -v ${PWD}/build/Debug/_deps/:/host/Debug/_deps -v ${PWD}/build/Coverage/_deps/:/host/Coverage/_deps -v /var/lib/jenkins/tools/:/var/lib/jenkins/tools/"
                            args "-v /var/lib/jenkins/tools/:/var/lib/jenkins/tools/"
                            reuseNode true
                        }
                    }
                    steps {
                        sh 'build/Release/test/tests --gtest_output=xml:build/Release/reports/'
                    }
                    post {
                        always{
                            xunit (
                                thresholds: [ skipped(failureThreshold: '0'), failed(failureThreshold: '0') ],
                                tools: [ GoogleTest(pattern: 'build/Release/reports/*.xml') ]
                            )
                        }
                    }
                }
                stage('Test Debug') {
                    agent {
                        dockerfile {
                            //args "-v ${PWD}/build/Release/_deps/:/host/Release/_deps -v ${PWD}/build/Debug/_deps/:/host/Debug/_deps -v ${PWD}/build/Coverage/_deps/:/host/Coverage/_deps -v /var/lib/jenkins/tools/:/var/lib/jenkins/tools/"
                            args "-v /var/lib/jenkins/tools/:/var/lib/jenkins/tools/"
                            reuseNode true
                        }
                    }
                    steps {
                        sh 'build/Debug/test/tests --gtest_output=xml:build/Debug/reports/'
                    }
                    post {
                        always{
                            xunit (
                                thresholds: [ skipped(failureThreshold: '0'), failed(failureThreshold: '0') ],
                                tools: [ GoogleTest(pattern: 'build/Debug/reports/*.xml') ]
                            )
                        }
                    }
                }
                stage('Test Coverage') {
                    agent {
                        dockerfile {
                            //args "-v ${PWD}/build/Release/_deps/:/host/Release/_deps -v ${PWD}/build/Debug/_deps/:/host/Debug/_deps -v ${PWD}/build/Coverage/_deps/:/host/Coverage/_deps -v /var/lib/jenkins/tools/:/var/lib/jenkins/tools/"
                            args "-v /var/lib/jenkins/tools/:/var/lib/jenkins/tools/"
                            reuseNode true
                        }
                    }
                    steps {
                        sh 'build/Coverage/test/tests --gtest_output=xml:build/Coverage/reports/'
                    }
                    post {
                        always{
                            xunit (
                                thresholds: [ skipped(failureThreshold: '0'), failed(failureThreshold: '0') ],
                                tools: [ GoogleTest(pattern: 'build/Coverage/reports/*.xml') ]
                            )
                        }
                    }
                }
            }
        }
        stage('Analysis') {
            parallel {
                stage('CodeChecker ClangSA') {
                   steps {
                       sh 'mkdir -p build/Analysis/CodeChecker/ClangSA'
                       sh "${CODECHECKER_PATH} analyze \"build/DebugNoPCH/compile_commands.json\" --analyzers clangsa -i .codechecker_skip --enable-all --enable alpha --ctu --output build/Analysis/CodeChecker/ClangSA/"
                   }
                }
                stage('CodeChecker ClangTidy') {
                   steps {
                       sh 'mkdir -p build/Analysis/CodeChecker/ClangTidy'
                       sh "${CODECHECKER_PATH} analyze \"build/DebugNoPCH/compile_commands.json\" --analyzers clang-tidy -i .codechecker_skip --enable-all --enable alpha --ctu --output build/Analysis/CodeChecker/ClangTidy/"
                   }
                }
                stage('CppCheck') {
                    steps {
                        script {
                            DATETIME_TAG = java.time.LocalDateTime.now()
                        }
                        sh 'mkdir -p build/Analysis/CppCheck'
                        sh label: '', returnStatus: true, script: "cppcheck --project=build/DebugNoPCH/compile_commands.json -i${PWD}/build --xml --language=c++ 2> build/Analysis/CppCheck/cppcheck-${DATETIME_TAG}.xml"
                        //publishCppcheck allowNoReport: true, ignoreBlankFiles: true, pattern: '**/cppcheck-result.xml'
                    }
                }
                stage('Infer') {
                    steps {
                        sh 'mkdir -p build/Analysis/Infer'
                        sh 'infer run --compilation-database build/DebugNoPCH/compile_commands.json --keep-going --results-dir build/Analysis/Infer'
                    }
                }
                stage('Valgrind') {
                    steps {
                        sh 'mkdir -p build/Analysis/Valgrind'
                        sh 'valgrind build/Release/test/tests --log-file=build/Analysis/Valgrind/valgrind-%p.log'
                        sh 'valgrind build/Debug/test/tests --log-file=build/Analysis/Valgrind/valgrind-%p.log'
                    }
                }
                stage('Vera++') {
                    steps {
                        script {
                            DATETIME_TAG = java.time.LocalDateTime.now()
                        }
                        sh 'mkdir -p build/Analysis/VeraPlusPlus'
                        sh "find src samples test -type f -name \"*.cpp\" -o -name \"*.cxx\" -o -name \"*.c\" -o -name \"*.cc\" -o -name \"*.hpp\" -o -name \"*.hxx\" -o -name \"*.h\" -o -name \"*.hh\" -o -name \"*.tpp\" -o -name \"*.txx\" -o -name \"*.t\" -o -name \"*.tt\" | vera++ --xml-report build/Analysis/VeraPlusPlus/report-${DATETIME_TAG}.xml"
                    }
                }
                stage('RATS') {
                    steps {
                        script {
                            DATETIME_TAG = java.time.LocalDateTime.now()
                        }
                        sh 'mkdir -p build/Analysis/RATS'
                        sh "rats src samples test --xml 1> build/Analysis/RATS/report-${DATETIME_TAG}.xml"
                    }
                }
                stage('Coverage') {
                    steps {
                        script {
                            DATETIME_TAG = java.time.LocalDateTime.now()
                        }
                        sh 'mkdir -p build/Analysis/Coverage'
                        sh "gcovr -r . -x --object-directory=build/Coverage/test/ > build/Analysis/Coverage/report-${DATETIME_TAG}.xml"
                    }
                }
            }
        }
        stage('SonarQube analysis') {
            steps{
                script {
                    def scannerHome = tool 'sonar-scanner';
                    withSonarQubeEnv() { // If you have configured more than one global server connection, you can specify its name
                        sh "${scannerHome}/bin/sonar-scanner"
                    }
                }
            }
        }
    }
}