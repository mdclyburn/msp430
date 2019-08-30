// -*- mode: Groovy; groovy-indent-offset: 2 -*-

pipeline {
  agent { node { label 'master' } }

  stages {
    stage('Documentation') {
      steps {
        sh 'doxygen >/dev/null'
        dir ('latex') {
          sh 'latexmk -pdf -dvi- -quiet refman.tex'
          stash(name: 'docs-pdf', includes: 'refman.pdf')
        }

        sh 'tar -cf web.tar -C html .'
        stash(name: 'docs-web', includes: 'web.tar')
      }

      when {
        branch 'master';
      }

      post {
        always {
          sh 'rm -rf docs'
        }
      }
    }

    stage('Build') {
      agent { node { label 'msp430' } }
      steps {
        dir ('src') {
          sh 'make MSP430PATH=/usr/local/msp430 MSP430MCU=msp430g2553'
        }
      }

      post {
        always {
          dir ('src') {
            sh 'make clean'
          }
        }
      }
    }
  }
}
