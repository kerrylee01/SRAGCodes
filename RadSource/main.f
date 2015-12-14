      program main

      REAL*8 Energy, Weight
      REAL*8 Ran(6)
      INTEGER ParticleID
      call sourceinitbom2014
      Ran(1) = 0.44;
      Ran(2) = 0.37;
      Ran(3) = 0.86;
      Ran(4) = 0.33;
      Ran(5) = 0.12;
      Ran(6) = 0.08;
      DO I = 1, 10
C         call sourcesample(ParticleID, Energy, Weight)
         call sourcesampleran(Ran, ParticleID, Energy, Weight)
C         call sourcesampleran(ParticleID, Energy, Weight)
         write(*,*)ParticleID, Energy, Weight
      ENDDO

      END PROGRAM
      
