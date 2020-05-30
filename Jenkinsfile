pipeline {
    agent any

    options {
        buildDiscarder(logRotator(numToKeepStr: '10'))
    }

    parameters {
        booleanParam name: 'RUN_ANALYSIS', defaultValue: true, description: 'Run Static Code Analysis?'
        booleanParam name: 'DEPLOY', defaultValue: true, description: 'Deploy Artifacts?'
    }

    stages {
        stage('Build') {
            steps {
                cmakeBuild buildType: 'Release', generator: 'Ninja', buildDir: 'build/Release', cleanBuild: true, installation: 'InSearchPath', steps: [[withCmake: true, args: all]]
                cmakeBuild buildType: 'Debug', generator: 'Ninja', buildDir: 'build/Debug', cleanBuild: true, installation: 'InSearchPath', steps: [[withCmake: true, args: all]]
                cmakeBuild buildType: 'Coverage', generator: 'Ninja', buildDir: 'build/Coverage', cleanBuild: true, installation: 'InSearchPath', steps: [[withCmake: true, args: all]]
            }
        }
        stage('Test') {
            steps {
                sh 'build/Release/test/tests --gtest_output=xml:build/Release/reports/'
            }
        }
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
            def scannerHome = tool 'SonarScanner 4.0';
            withSonarQubeEnv('My SonarQube Server') { // If you have configured more than one global server connection, you can specify its name
                sh "$/opt/sonar-scanner/bin/sonar-scanner"
            }
        }
        post {
            always{
                xunit (
                    thresholds: [ skipped(failureThreshold: '0'), failed(failureThreshold: '0') ],
                    tools: [ GoogleTest(pattern: 'build/Release/reports/*.xml') ])
                )
            }
        }
    }
}