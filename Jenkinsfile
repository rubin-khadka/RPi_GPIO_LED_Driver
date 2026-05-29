pipeline {
    agent any
    
    stages {
        stage('Checkout') {
            steps {
                checkout scm
                echo "✅ Code downloaded!"
            }
        }
        
        stage('List Files') {
            steps {
                sh 'ls -la'
            }
        }
        
        stage('Simple Test') {
            steps {
                sh 'echo "Jenkins is working!"'
            }
        }
    }
}