pipeline {
    agent any
    
    environment {
        RPI_HOST = '192.168.1.100'
        RPI_USER = 'pi'
        RPI_BUILD_DIR = '/tmp/led_driver_build'  // Build in temp folder
    }
    
    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }
                
        stage('Copy & Build on RPi') {
            steps {
                sh '''
                    # Create temp build directory on RPi
                    ssh ${RPI_USER}@${RPI_HOST} "mkdir -p ${RPI_BUILD_DIR}"
                    
                    # Copy source AND Makefile to temp directory
                    scp kernel_module/led_driver.c ${RPI_USER}@${RPI_HOST}:${RPI_BUILD_DIR}/
                    scp kernel_module/Makefile ${RPI_USER}@${RPI_HOST}:${RPI_BUILD_DIR}/
                    
                    # Make it
                    ssh ${RPI_USER}@${RPI_HOST} "cd ${RPI_BUILD_DIR} && make"
                '''
            }
        }
        
        stage('Test LED Module') {
            steps {
                sh '''
                    ssh ${RPI_USER}@${RPI_HOST} "
                        cd ${RPI_BUILD_DIR} &&
                        sudo insmod led_driver.ko && 
                        echo 'LED Module Loaded' &&
                        sleep 2 &&
                        sudo rmmod led_driver &&
                        echo 'LED Module Unloaded'
                    "
                '''
            }
        }
        
        stage('Cleanup') {
            steps {
                sh '''
                    # Remove temp directory after test
                    ssh ${RPI_USER}@${RPI_HOST} "rm -rf ${RPI_BUILD_DIR}"
                '''
            }
        }
    }
}