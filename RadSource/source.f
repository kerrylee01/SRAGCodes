*$ CREATE SOURCE.FOR
*COPY SOURCE
*
*=== source ===========================================================*
*
      SUBROUTINE SOURCE ( NOMORE )

      INCLUDE '(DBLPRC)'
      INCLUDE '(DIMPAR)'
      INCLUDE '(IOUNIT)'
*
*----------------------------------------------------------------------*
*                                                                      *
*     Copyright (C) 1990-2010      by    Alfredo Ferrari & Paola Sala  *
*     All Rights Reserved.                                             *
*                                                                      *
*                                                                      *
*     New source for FLUKA9x-FLUKA20xy:                                *
*                                                                      *
*     Created on 07 January 1990   by    Alfredo Ferrari & Paola Sala  *
*                                                   Infn - Milan       *
*                                                                      *
*     Last change on  17-Oct-10    by    Alfredo Ferrari               *
*                                                                      *
*  This is just an example of a possible user written source routine.  *
*  note that the beam card still has some meaning - in the scoring the *
*  maximum momentum used in deciding the binning is taken from the     *
*  beam momentum.  Other beam card parameters are obsolete.            *
*                                                                      *
*       Output variables:                                              *
*                                                                      *
*              Nomore = if > 0 the run will be terminated              *
*                                                                      *
*----------------------------------------------------------------------*
*
      INCLUDE '(BEAMCM)'
      INCLUDE '(FHEAVY)'
      INCLUDE '(FLKSTK)'
      INCLUDE '(IOIOCM)'
      INCLUDE '(LTCLCM)'
      INCLUDE '(PAPROP)'
      INCLUDE '(SOURCM)'
      INCLUDE '(SUMCOU)'
*
      LOGICAL LFIRST
*
**********************************************************************
*     Added By Kerry Lee 6/27/2014 from generic source.f started by 
*     Toni Empl in Jan 2003 and modified by Kerry Lee in Jan 2006
*      
      LOGICAL LMANY, LTOTAL

**********************************************************************

      SAVE LFIRST
**********************************************************************
*     Added by Kerry Lee 6/27/2014
      SAVE LMANY, LTOTAL
**********************************************************************
      DATA LFIRST / .TRUE. /
*======================================================================*
*                                                                      *
*                 BASIC VERSION                                        *
*                                                                      *
*======================================================================*
      NOMORE = 0
*  +-------------------------------------------------------------------*
*  |  First call initializations:
      IF ( LFIRST ) THEN
*  |  *** The following 3 cards are mandatory ***
         TKESUM = ZERZER
         LFIRST = .FALSE.
         LUSSRC = .TRUE.
*  |  *** User initialization ***
*************************************************************************
*     Added by Kerry Lee 6/27/2014
         LMANY = ABS( WHASOU( 6 ) ) .GE. 2
         LTOTAL = WHASOU( 6 ) .LE. -1
         CALL OAUXFI ( SDUSOU, 93, 'FORMATTED', IERR )
         IF ( IERR .GT. 0 ) THEN
            IERR = 0
            CALL OAUXFI ( 'source.inp', 93, 'old', IERR )
         END IF
         IF ( IERR .GT. 0 ) CALL FLABRT ( 'source' , 
     +                                    'source.inp missing' )
*************************************************************************
      END IF

*  |
*  +-------------------------------------------------------------------*
*  Push one source particle to the stack. Note that you could as well
*  push many but this way we reserve a maximum amount of space in the
*  stack for the secondaries to be generated
*  Npflka is the stack counter: of course any time source is called it
*  must be =0
      NPFLKA = NPFLKA + 1
**********************************************************************
*     Added by Kerry Lee 6/27/2014
*
      READ( 93, *, ERR = 99, END = 99 ) IDPART, EP_, X_, Y_, Z_, CX_, 
     &                                  CY_, CZ_, WT_
**********************************************************************

*  Wt is the weight of the particle
      WTFLK  (NPFLKA) = ONEONE
**********************************************************************
*     Added by Kerry Lee 6/27/2014
*
      WTFLK  (NPFLKA) = WT_
**********************************************************************

      WEIPRI = WEIPRI + WTFLK (NPFLKA)

**********************************************************************
*     Added by Kerry Lee 6/27/2014
*
      WRITE( 35, * )'check source input', IDPART, X_, Y_, Z_
     +    , CX_, CY_, CZ_, EP_, WT_, WEIPRI
      
cc      Added some things to 2005.6 version since -201,-301,-302,-402 are not
cc      treated as heavy ions.  May have been true with the previous version
cc      also but I never found it to be a problem. 1/3/2006 KL.
        
cc      Set IJBEAM to appropriate FLUKA particle ID number based on IDpart 
        IF (IDPART .GE. -6 ) THEN
           IJBEAM = IDPART
        ELSE IF ( IDPART .LE. -101 .and. IDPART .GE. -402) THEN
           IF ( IDPART .EQ. -101 ) THEN 
              IJBEAM = 1
           ELSE IF (IDpart.EQ. -201 ) THEN 
              IJBEAM = -3
           ELSE IF (IDpart.EQ. -301 ) THEN 
              IJBEAM = -4
           ELSE IF (IDpart.EQ. -302 ) THEN 
              IJBEAM = -5
           ELSE IF (IDpart.EQ. -402 ) THEN 
              IJBEAM = -6
           ENDIF
        ELSE IF (IDPART .LT. -402 ) THEN
           IJBEAM = -2
cc      ------------ Decode Heavy ion particle Id for 100*A+Z FLUKA number
           IDPART = ABS ( IDPART )
           IPROA = IDPART / 100
           IPROZ = IDPART - 100 * IPROA
        ENDIF
**********************************************************************

*  Particle type (1=proton.....). Ijbeam is the type set by the BEAM
*  card
*  +-------------------------------------------------------------------*
*  |  (Radioactive) isotope:
      IF ( IJBEAM .EQ. -2 .AND. LRDBEA ) THEN
         IARES  = IPROA
         IZRES  = IPROZ
         IISRES = IPROM
         CALL STISBM ( IARES, IZRES, IISRES )
         IJHION = IPROZ  * 1000 + IPROA
         IJHION = IJHION * 100 + KXHEAV
         IONID  = IJHION
         CALL DCDION ( IONID )
         CALL SETION ( IONID )
*  |
*  +-------------------------------------------------------------------*
*  |  Heavy ion:
      ELSE IF ( IJBEAM .EQ. -2 ) THEN
         IJHION = IPROZ  * 1000 + IPROA
         IJHION = IJHION * 100 + KXHEAV
         IONID  = IJHION
         CALL DCDION ( IONID )
         CALL SETION ( IONID )
         ILOFLK (NPFLKA) = IJHION
*  |  Flag this is prompt radiation
         LRADDC (NPFLKA) = .FALSE.
*  |  Group number for "low" energy neutrons, set to 0 anyway
         IGROUP (NPFLKA) = 0
*  |
*  +-------------------------------------------------------------------*
*  |  Normal hadron:
      ELSE
         IONID = IJBEAM
         ILOFLK (NPFLKA) = IJBEAM
*  |  Flag this is prompt radiation
         LRADDC (NPFLKA) = .FALSE.
*  |  Group number for "low" energy neutrons, set to 0 anyway
         IGROUP (NPFLKA) = 0
      END IF

************************************************************************
*     Added by Kerry Lee 6/27/2014
*
*     If the input is Total energy/momentum then adjust it per nucleon.
*     NOTE: May not need to use AMUC12 since AM ( IJBEAM ) has been
*           replaced with AM ( IONID).  This needs to be checked
      IF (LTOTAL) THEN
         WRITE ( LUNOUT, * ) ' ---> source (EP)/n:',
     +                       EP_ * AMUC12 / AM ( IONID )
      ELSE
         EP_ = EP_ * AM ( IONID ) / AMUC12
      ENDIF
      
c     Check to see if ep_ input is energy or momentum and set Plab_ and
cc    Ekin_ accordingly.
*     NOTE: Not sure here if replacing AM (IJBEAM) with AM(IONID) changes
*           the results here, but needs to be checked.
      PLAB_ =  EP_
      IF ( EP_ .LT. 0 ) 
     & PLAB_ = SQRT ( -EP_* ( -EP_ + TWOTWO * AM ( IONID )))
      EKIN_ = SQRT ( PLAB_**2 + AM ( IONID )**2 ) - AM ( IONID )
      WRITE( 35, * ) EKIN_
************************************************************************
*  |
*  +-------------------------------------------------------------------*
*  From this point .....
*  Particle generation (1 for primaries)
      LOFLK  (NPFLKA) = 1
*  User dependent flag:
      LOUSE  (NPFLKA) = 0
*  No channeling:
      LCHFLK (NPFLKA) = .FALSE.
      DCHFLK (NPFLKA) = ZERZER
*  User dependent spare variables:
      DO 100 ISPR = 1, MKBMX1
         SPAREK (ISPR,NPFLKA) = ZERZER
 100  CONTINUE
*  User dependent spare flags:
      DO 200 ISPR = 1, MKBMX2
         ISPARK (ISPR,NPFLKA) = 0
 200  CONTINUE
*  Save the track number of the stack particle:
      ISPARK (MKBMX2,NPFLKA) = NPFLKA
      NPARMA = NPARMA + 1
      NUMPAR (NPFLKA) = NPARMA
      NEVENT (NPFLKA) = 0
      DFNEAR (NPFLKA) = +ZERZER
*  ... to this point: don't change anything
*  Particle age (s)
      AGESTK (NPFLKA) = +ZERZER
      AKNSHR (NPFLKA) = -TWOTWO

**********************************************************************
*     Added by Kerry Lee 6/27/2014
      PBEAM = PLAB_
      TKEFLK (NPFLKA) = EKIN_
      PMOFLK (NPFLKA) = PLAB_
*      PMOFLK (NPFLKA) = SQRT ( TKEFLK (NPFLKA) * ( TKEFLK (NPFLKA)
*     &                       + TWOTWO * AM (IONID) ) )
**********************************************************************
*********************************************************************
*     Commented out since momentum or energy are being read in from file
*     and not being set by the BEAM card - Kerry Lee 6/27/2014
*  Kinetic energy of the particle (GeV)
cc      TKEFLK (NPFLKA) = SQRT ( PBEAM**2 + AM (IONID)**2 ) - AM (IONID)
*  Particle momentum
cc      PMOFLK (NPFLKA) = PBEAM
************************************************************************

*     PMOFLK (NPFLKA) = SQRT ( TKEFLK (NPFLKA) * ( TKEFLK (NPFLKA)
*    &                       + TWOTWO * AM (IONID) ) )
*  Cosines (tx,ty,tz)
*      Commented this out - will be provided in input file - 12/3/12
*      TXFLK  (NPFLKA) = UBEAM
*      TYFLK  (NPFLKA) = VBEAM
*      TZFLK  (NPFLKA) = WBEAM
*     TZFLK  (NPFLKA) = SQRT ( ONEONE - TXFLK (NPFLKA)**2
*    &                       - TYFLK (NPFLKA)**2 )
************************************************************************
*  Cosines (cx, cy, cz) and ensure normalized. Added by Kerry Lee 6/27/2014
      TXFLK  (NPFLKA) = CX_
      TYFLK  (NPFLKA) = CY_
      TZFLK  (NPFLKA) = CZ_
      TZFLK  (NPFLKA) = SQRT ( ONEONE - TXFLK (NPFLKA)**2 
     &                       - TYFLK (NPFLKA)**2 )
************************************************************************
*  Polarization cosines:
      TXPOL  (NPFLKA) = -TWOTWO
      TYPOL  (NPFLKA) = +ZERZER
      TZPOL  (NPFLKA) = +ZERZER
*  Particle coordinates
*      Commented this out - will be provided in input file - 12/3/12
*      XFLK   (NPFLKA) = XBEAM
*      YFLK   (NPFLKA) = YBEAM
*      ZFLK   (NPFLKA) = ZBEAM
*      READ(21,*) UUBEAM, VVBEAM, WWBEAM
************************************************************************
*  Cosines (tx, ty, tz) added by Kerry Lee 6/27/2014
      XFLK   (NPFLKA) = X_
      YFLK   (NPFLKA) = Y_
      ZFLK   (NPFLKA) = Z_
************************************************************************
*      CALL OAUXFI('testfile.txt', 93, 'NEW', IERR)
*      WRITE(93,*) 'Read in', UUBEAM, VVBEAM, WWBEAM
*     Changing input so initial point is in *.inp
*      XFLK   (NPFLKA) = XX
*      YFLK   (NPFLKA) = YY
*      ZFLK   (NPFLKA) = ZZ
*      TXFLK  (NPFLKA) = UUBEAM
*      TYFLK  (NPFLKA) = VVBEAM
*      TZFLK  (NPFLKA) = WWBEAM
*      WRITE(93,*) 'I think I am', TXFLK  (NPFLKA), TYFLK  (NPFLKA),
*     &    TZFLK  (NPFLKA)
*     Normalization option - 12/3/12
*      TZFLK  (NPFLKA) = SQRT ( ONEONE - TXFLK (NPFLKA)**2
*     &                       - TYFLK (NPFLKA)**2 ) 
*  Calculate the total kinetic energy of the primaries: don't change
      IF ( ILOFLK (NPFLKA) .EQ. -2 .OR. ILOFLK (NPFLKA) .GT. 100000 )
     &   THEN
         TKESUM = TKESUM + TKEFLK (NPFLKA) * WTFLK (NPFLKA)
      ELSE IF ( ILOFLK (NPFLKA) .NE. 0 ) THEN
         TKESUM = TKESUM + ( TKEFLK (NPFLKA) + AMDISC (ILOFLK(NPFLKA)) )
     &          * WTFLK (NPFLKA)
      ELSE
         TKESUM = TKESUM + TKEFLK (NPFLKA) * WTFLK (NPFLKA)
      END IF
      RADDLY (NPFLKA) = ZERZER
*  Here we ask for the region number of the hitting point.
*     NREG (NPFLKA) = ...
*  The following line makes the starting region search much more
*  robust if particles are starting very close to a boundary:
      CALL GEOCRS ( TXFLK (NPFLKA), TYFLK (NPFLKA), TZFLK (NPFLKA) )
      CALL GEOREG ( XFLK  (NPFLKA), YFLK  (NPFLKA), ZFLK  (NPFLKA),
     &              NRGFLK(NPFLKA), IDISC )
*  Do not change these cards:
      CALL GEOHSM ( NHSPNT (NPFLKA), 1, -11, MLATTC )
      NLATTC (NPFLKA) = MLATTC
      CMPATH (NPFLKA) = ZERZER
      CALL SOEVSV
      RETURN

************************************************************************
*  Added by Kerry Lee 6/27/2014
 99   CONTINUE
cc   ----------- no more input, tell FLUKA to quit
      NOMORE = 1
      RETURN
************************************************************************

*=== End of subroutine Source =========================================*
      END

