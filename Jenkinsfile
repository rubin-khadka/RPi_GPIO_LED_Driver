pipeline {
    agent any
    environment {
        PI_HOST = '10.42.0.214'
        PI_USER = 'rubin'
        MODULE_DIR = 'kernel_module'
        REMOTE_DIR = '/tmp/jenkins-rpi-gpio'
    }
    stages {
        stage('1. Deploy Source to Pi') {
            steps {
                sshagent(credentials: ['pi-ssh-key']) {
                    sh '''
                        ssh ${PI_USER}@${PI_HOST} "mkdir -p ${REMOTE_DIR}/${MODULE_DIR}"
                        scp ${MODULE_DIR}/hello.c ${MODULE_DIR}/Makefile ${PI_USER}@${PI_HOST}:${REMOTE_DIR}/${MODULE_DIR}/
                    '''
                }
            }
        }
        stage('2. Compile on Pi') {
            steps {
                sshagent(credentials: ['pi-ssh-key']) {
                    sh '''
                        ssh ${PI_USER}@${PI_HOST} "cd ${REMOTE_DIR}/${MODULE_DIR} && make"
                    '''
                }
            }
        }
        stage('3. Hardware Test on Pi') {
            steps {
                sshagent(credentials: ['pi-ssh-key']) {
                    sh '''
                        # Load module with default parameter (myname=World)
                        ssh ${PI_USER}@${PI_HOST} "sudo insmod ${REMOTE_DIR}/${MODULE_DIR}/hello.ko"
                        
                        # Verify init message with default name
                        ssh ${PI_USER}@${PI_HOST} "dmesg | tail -n 5 | grep -q 'Hello, World!'"
                        
                        # Unload module
                        ssh ${PI_USER}@${PI_HOST} "sudo rmmod hello"
                        
                        # Verify exit message
                        ssh ${PI_USER}@${PI_HOST} "dmesg | tail -n 5 | grep -q 'Goodbye, World!'"
                    '''
                }
            }
        }
    }
    post {
        always {
            archiveArtifacts artifacts: 'kernel_module/hello.ko', allowEmptyArchive: false
        }
    }
}