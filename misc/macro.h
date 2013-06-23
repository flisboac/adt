
#define dtTAGSUFFIX _tag
#define dtTYPEDEF(t) typedef t ## dtTAGSUFFIX t;
#define dtDECLARE(t, b) \
    struct t ## dtTAGSUFFIX { \
        dt_Ctnr


#define dtDECLTYPE(t, b) dtTYPEDEF(t); dtDECLARE(t, b)

#define dt_T()


dt_TVector(int) somemethod() {
    
    dt_TVector(int) v;
    dt_TVector_method(v);
    dt_CVector(int, v, );
}