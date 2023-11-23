#pragma once

#pragma push_macro("_WIN64")
#pragma push_macro("DELETE")
#pragma push_macro("CALLBACK")
#undef _WIN64
#undef DELETE
#undef CALLBACK
#include "libpinmame.h"
#pragma pop_macro("CALLBACK")
#pragma pop_macro("DELETE")
#pragma pop_macro("_WIN64")

#include "vpinmame_i.h"

class VPinMAMERoms : public IRoms
{
public:
   STDMETHOD(QueryInterface)(REFIID iid, void** ppv) {
      if (iid == IID_IRoms) {
         *ppv = reinterpret_cast<VPinMAMERoms*>(this);
         AddRef();
         return S_OK;
      } else if (iid == IID_IDispatch) {
         *ppv = reinterpret_cast<VPinMAMERoms*>(this);
         AddRef();
         return S_OK;
      } else if (iid == IID_IUnknown) {
         *ppv = reinterpret_cast<VPinMAMERoms*>(this);
         AddRef();
         return S_OK;
      } else {
         *ppv = NULL;
         return E_NOINTERFACE;
      }
   }

   STDMETHOD_(ULONG, AddRef)() {
      m_dwRef++;
      return m_dwRef;
   }

   STDMETHOD_(ULONG, Release)() {
      m_dwRef--;

      if (m_dwRef == 0)
         delete this;

      return m_dwRef;
   }

   STDMETHOD(GetTypeInfoCount)(UINT *pCountTypeInfo) { *pCountTypeInfo = 0; return S_OK;  }
   STDMETHOD(GetTypeInfo)(UINT iInfo, LCID lcid, ITypeInfo **ppTInfo) { return E_NOTIMPL; }
   STDMETHOD(GetIDsOfNames)(REFIID /*riid*/, LPOLESTR* rgszNames, UINT cNames, LCID lcid,DISPID* rgDispId);
   STDMETHOD(Invoke)(DISPID dispIdMember, REFIID /*riid*/, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr);

public:
   VPinMAMERoms();
   ~VPinMAMERoms();

   STDMETHOD(Audit)(/*[in]*/ VARIANT_BOOL fStrict);
   STDMETHOD(get_StateDescription)(/*[out, retval]*/ BSTR *pVal);
   STDMETHOD(get_State)(/*[out, retval]*/ LONG *pVal);
   STDMETHOD(get_Available)(/*[out, retval]*/ VARIANT_BOOL *pVal);
   STDMETHOD(get_Count)(LONG* pnCount);
   STDMETHOD(get_Item)(VARIANT *pKey, IRom **pRom);
   STDMETHOD(get__NewEnum)(IUnknown** ppunkEnum);

private:
   ULONG m_dwRef = 0;
};
