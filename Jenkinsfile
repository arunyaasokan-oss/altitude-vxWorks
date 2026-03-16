pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                // 1. Generate the Build Log: 
                // The '2>&1' part ensures both standard errors and output are saved.
                sh 'make clean && make > buildlog.txt 2>&1'
            }
        }

        stage('Coding Standards') {
            steps {
                // 2. Generate the Coding Standards Report:
                // We add '|| true' because if the tool finds errors, it returns a 
                // failure code, which would stop the pipeline. '|| true' forces it to continue.
                sh 'cppcheck . -I udp/ -I client/ --enable=all --suppress=missingIncludeSystem --suppress=misra-c2012-21.6 --addon=misra.py > coding_standards_report.txt 2>&1 || true'
            }
        }

        stage('Static Analysis') {
            steps {
                // 3. Generate the Static Analysis Report:
                sh 'cppcheck . > static-analysis-report.txt 2>&1 || true'
            }
        }
    }
    
    post {
        always {
            // 4. Archive all of them at once!
            // You can use a comma-separated list to archive multiple files.
            archiveArtifacts artifacts: 'buildlog.txt, coding_standards_report.txt, main.o, static-analysis-report.txt', fingerprint: true
        }
    }
}