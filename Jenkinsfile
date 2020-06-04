pipeline {
    agent any

    options {
        buildDiscarder(logRotator(numToKeepStr: '10'))
        skipDefaultCheckout()
    }
    parameters {
        booleanParam name: 'RUN_ANALYSIS', defaultValue: true, description: 'Run Static Code Analysis?'
        booleanParam name: 'DEPLOY', defaultValue: true, description: 'Deploy Artifacts?'
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
        stage('Build and Analyze') {
            parallel {
                stage('Analyse') {
                    when {
                        environment name: 'RUN_ANALYSIS', value: 'true'
                    }
                    steps {
                        sh label: '', returnStatus: true, script: 'cppcheck . --xml --language=c++ --suppressions-list=suppressions.txt 2> cppcheck-result.xml'
                        publishCppcheck allowNoReport: true, ignoreBlankFiles: true, pattern: '**/cppcheck-result.xml'
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
                stage('Build') {
                    agent {
                        dockerfile {
                            args "-v ${PWD}/build/Release/_deps/:/host/Release/_deps -v ${PWD}/build/Debug/_deps/:/host/Debug/_deps -v ${PWD}/build/Coverage/_deps/:/host/Coverage/_deps -v /var/lib/jenkins/tools/:/var/lib/jenkins/tools/"
                            reuseNode true
                        }
                    }
                    steps {
                        cmakeBuild buildType: 'Release', generator: 'Ninja', buildDir: 'build/Release', cleanBuild: true, installation: 'cmake-3.17.3', steps: [[withCmake: true]]
                        cmakeBuild buildType: 'Debug', generator: 'Ninja', buildDir: 'build/Debug', cleanBuild: true, installation: 'cmake-3.17.3', steps: [[withCmake: true]]
                        cmakeBuild buildType: 'Coverage', generator: 'Ninja', buildDir: 'build/Coverage', cleanBuild: true, installation: 'cmake-3.17.3', steps: [[withCmake: true]]
                    }
                }
            }
        }
        stage('Test') {
            parallel {
                stage('Test Release') {
                    agent {
                        dockerfile {
                            args "-v ${PWD}/build/Release/_deps/:/host/Release/_deps -v ${PWD}/build/Debug/_deps/:/host/Debug/_deps -v ${PWD}/build/Coverage/_deps/:/host/Coverage/_deps -v /var/lib/jenkins/tools/:/var/lib/jenkins/tools/"
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
                            args "-v ${PWD}/build/Release/_deps/:/host/Release/_deps -v ${PWD}/build/Debug/_deps/:/host/Debug/_deps -v ${PWD}/build/Coverage/_deps/:/host/Coverage/_deps -v /var/lib/jenkins/tools/:/var/lib/jenkins/tools/"
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
                            args "-v ${PWD}/build/Release/_deps/:/host/Release/_deps -v ${PWD}/build/Debug/_deps/:/host/Debug/_deps -v ${PWD}/build/Coverage/_deps/:/host/Coverage/_deps -v /var/lib/jenkins/tools/:/var/lib/jenkins/tools/"
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
    }
}