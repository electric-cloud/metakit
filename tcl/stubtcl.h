/* Internal stub code, copied from CritLib */

const TclStubs *tclStubsPtr;
const TclPlatStubs *tclPlatStubsPtr;
const struct TclIntStubs *tclIntStubsPtr;
const struct TclIntPlatStubs *tclIntPlatStubsPtr;

static int MyInitStubs(Tcl_Interp *ip) {
  typedef struct  {
    char *result;
    Tcl_FreeProc *freeProc;
    int errorLine;
    TclStubs *stubTable;
  } HeadOfInterp;

  HeadOfInterp *hoi = (HeadOfInterp*)ip;

  if (hoi->stubTable == NULL || hoi->stubTable->magic != TCL_STUB_MAGIC) {
    Tcl_SetResult(ip, const_cast<char *>("This extension requires stubs-support."), TCL_STATIC);
    return 0;
  }

  tclStubsPtr = hoi->stubTable;

  if (Tcl_PkgRequire(ip, "Tcl", "8.1", 0) == NULL) {
    tclStubsPtr = NULL;
    return 0;
  }

  if (tclStubsPtr->hooks != NULL) {
    tclPlatStubsPtr = tclStubsPtr->hooks->tclPlatStubs;
    tclIntStubsPtr = tclStubsPtr->hooks->tclIntStubs;
    tclIntPlatStubsPtr = tclStubsPtr->hooks->tclIntPlatStubs;
  }

  return 1;
}
