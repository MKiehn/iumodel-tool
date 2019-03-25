// RUN: %check_clang_tidy %s search-for-Std-Algorithm-Patterns %t -- -- -std=c++11 -I %S/Inputs/iumodel

// SU2-6.1.0/externals/tecio/tecsrc/datautil.cpp:706:25:
while (Connection < FNNumBndryConns[CurZone] && InputIsOk) {
  /*
   * Face neighbor connection have the following format for both
   * ASCII and binary:
   *
   *   FaceNeighborMode_LocalOneToOne     3         cz,fz,cz
   *   FaceNeighborMode_LocalOneToMany    nz+4      cz,fz,oz,nz,cz1,cz2,...,czn
   *   FaceNeighborMode_GlobalOneToOne    4         cz,fz,ZZ,CZ
   *   FaceNeighborMode_GlobalOneToMany   2*nz+4
   * cz,fz,oz,nz,ZZ1,CZ1,ZZ2,CZ2,...,ZZn,CZn
   *
   *   Where:
   *       cz = cell in current zone
   *       fz = face of cell in current zone
   *       oz = face obsuration flag (only applies to one-to-many):
   *              0 = face partially obscured
   *              1 = face entirely obscured
   *       nz = number of cell or zone/cell associations (only applies to
   * one-to-many) ZZ = remote Zone CZ = cell in remote zone
   */
  (void)GetNextI(ReadTecFileStream, &InputIsOk); /* read cz */
  if (!InputIsOk)
    ErrMsg(
        translate("Unexpected end-of-file while reading face neighbor data."));

  (void)GetNextI(ReadTecFileStream, &InputIsOk); /* read fz */

  if (InputIsOk) {
    /*
     * read FaceNeighborMode_LocalOneToOne:   cz ||
     *      FaceNeighborMode_LocalOneToMany:  oz ||
     *      FaceNeighborMode_GlobalOneToOne:  ZZ ||
     *      FaceNeighborMode_GlobalOneToMany: oz
     */
    if (CurZoneSpec->FNMode == FaceNeighborMode_LocalOneToOne)
      (void)GetNextI(ReadTecFileStream, &InputIsOk);
    else if (CurZoneSpec->FNMode == FaceNeighborMode_LocalOneToMany)
      (void)GetNextI(ReadTecFileStream, &InputIsOk);
    else if (CurZoneSpec->FNMode == FaceNeighborMode_GlobalOneToOne)
      (void)GetNextI(ReadTecFileStream, &InputIsOk);
    else if (CurZoneSpec->FNMode == FaceNeighborMode_GlobalOneToMany)
      (void)GetNextI(ReadTecFileStream, &InputIsOk);
    else
      CHECK(FALSE);

    if (CurZoneSpec->FNMode != FaceNeighborMode_LocalOneToOne && InputIsOk) {
      LgIndex_t NumAssociations = 0;
      /*
       * read FaceNeighborMode_LocalOneToMany:  nz ||
       *      FaceNeighborMode_GlobalOneToOne:  CZ ||
       *      FaceNeighborMode_GlobalOneToMany: nz
       */
      if (CurZoneSpec->FNMode == FaceNeighborMode_LocalOneToMany)
        NumAssociations = GetNextI(ReadTecFileStream, &InputIsOk);
      else if (CurZoneSpec->FNMode == FaceNeighborMode_GlobalOneToOne)
        (void)GetNextI(ReadTecFileStream, &InputIsOk);
      else if (CurZoneSpec->FNMode == FaceNeighborMode_GlobalOneToMany)
        NumAssociations = GetNextI(ReadTecFileStream, &InputIsOk);
      else
        CHECK(FALSE);

      if (CurZoneSpec->FNMode != FaceNeighborMode_GlobalOneToOne && InputIsOk) {
        LgIndex_t Assoc;
        if (CurZoneSpec->FNMode == FaceNeighborMode_LocalOneToMany)
          for (Assoc = 0; Assoc < NumAssociations && InputIsOk; Assoc++)
            (void)GetNextI(ReadTecFileStream, &InputIsOk); /* read czn */
        else if (CurZoneSpec->FNMode == FaceNeighborMode_GlobalOneToMany)
          for (Assoc = 0; Assoc < NumAssociations && InputIsOk; Assoc++) {
            (void)GetNextI(ReadTecFileStream, &InputIsOk); /* read ZZn */
            (void)GetNextI(ReadTecFileStream, &InputIsOk); /* read CZn */
          }
        else
          CHECK(FALSE);

        if (InputIsOk) Connection += NumAssociations;
      } else if (InputIsOk) /* CurZoneSpec->FNMode ==
                               FaceNeighborMode_GlobalOneToOne */
        Connection += 1;
    } else if (InputIsOk) /* CurZoneSpec->FNMode ==
                             FaceNeighborMode_LocalOneToOne */
      Connection += 1;

    if (!InputIsOk)
      ErrMsg(translate("Corrupt input file: invalid face neighbors."));
  }
