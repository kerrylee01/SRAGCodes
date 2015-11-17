      program main

      REAL*8 Energy, Weight
      INTEGER ParticleID
        call sourceinit
        DO I = 1, 10
           call sourcesample(ParticleID, Energy, Weight)
           write(*,*)ParticleID, Energy, Weight
        ENDDO

      END PROGRAM
      
