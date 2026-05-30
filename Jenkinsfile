pipeline {
    agent any
    
    environment {
        RPI_HOST = '10.42.0.214'
        RPI_USER = 'rubin'
        RPI_BUILD_DIR = '/tmp/led_driver_build'
    }
    
    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }
        
        stage('Copy & Build on RPi') {
            steps {
                withCredentials([sshUserPrivateKey(
                    credentialsId: 'pi-ssh-key',
                    keyFileVariable: 'SSH_KEY',
                    usernameVariable: 'SSH_USER'
                )]) {
                    sh '''
                        ssh -i ${SSH_KEY} -o StrictHostKeyChecking=no ${SSH_USER}@${RPI_HOST} "mkdir -p ${RPI_BUILD_DIR}"
                        scp -i ${SSH_KEY} -o StrictHostKeyChecking=no kernel_module/* ${SSH_USER}@${RPI_HOST}:${RPI_BUILD_DIR}/
                        ssh -i ${SSH_KEY} -o StrictHostKeyChecking=no ${SSH_USER}@${RPI_HOST} "cd ${RPI_BUILD_DIR} && make"
                        echo "Build successful!"
                    '''
                }
            }
        }
        
        stage('Test LED Module') {
            steps {
                withCredentials([sshUserPrivateKey(
                    credentialsId: 'pi-ssh-key',
                    keyFileVariable: 'SSH_KEY',
                    usernameVariable: 'SSH_USER'
                )]) {
                    sh '''
                        ssh -i ${SSH_KEY} -o StrictHostKeyChecking=no ${SSH_USER}@${RPI_HOST} "
                            cd ${RPI_BUILD_DIR} &&
                            sudo rmmod led_driver 2>/dev/null || true &&
                            sudo insmod led_driver.ko && 
                            echo 'LED Module Loaded Successfully!' &&
                            sleep 2 &&
                            sudo rmmod led_driver &&
                            echo 'LED Module Unloaded Successfully!'
                        "
                    '''
                }
            }
        }
        
        stage('Cleanup') {
            steps {
                withCredentials([sshUserPrivateKey(
                    credentialsId: 'pi-ssh-key',
                    keyFileVariable: 'SSH_KEY',
                    usernameVariable: 'SSH_USER'
                )]) {
                    sh '''
                        ssh -i ${SSH_KEY} -o StrictHostKeyChecking=no ${SSH_USER}@${RPI_HOST} "rm -rf ${RPI_BUILD_DIR}"
                        echo "Cleanup complete!"
                    '''
                }
            }
        }
    }
}