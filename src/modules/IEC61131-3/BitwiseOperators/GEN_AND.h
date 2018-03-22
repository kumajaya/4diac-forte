/*******************************************************************************
 * Copyright (c) 2014 Profactor GmbH
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *   Matthias Plasch
 *   - initial API and implementation and/or initial documentation
 *******************************************************************************/

#ifndef _GEN_AND_H_
#define _GEN_AND_H_

#include <funcbloc.h>

class GEN_AND: public CFunctionBlock {
DECLARE_GENERIC_FIRMWARE_FB(GEN_AND)

private:
  CStringDictionary::TStringId *m_anDataInputNames;
  CStringDictionary::TStringId *m_anDataInputTypeIds;

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_ANY_BIT &OUT() {
    return *static_cast<CIEC_ANY_BIT*>(getDO(0));
  }
  ;

  static const TEventID scm_nEventREQID = 0;
  static const TForteInt16 scm_anEIWithIndexes[];
  TDataIOID *m_anEIWith;
  static const CStringDictionary::TStringId scm_anEventInputNames[];

  static const TEventID scm_nEventCNFID = 0;
  static const TForteInt16 scm_anEOWithIndexes[];
  static const TDataIOID scm_anEOWith[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];

  //self-defined members
  int m_nDInputs;

  CStringDictionary::TStringId m_nConfiguredFBTypeNameId;

  virtual void executeEvent(int pa_nEIID);

  GEN_AND(const CStringDictionary::TStringId pa_nInstanceNameId,
      CResource *pa_poSrcRes);
  virtual ~GEN_AND();

public:

  CStringDictionary::TStringId getFBTypeId(void) const {
    return m_nConfiguredFBTypeNameId;
  }

  bool configureFB(const char *pa_acConfigString);

  template<typename T> void calculateValue() {
    T oIn, oOut;

    for (int nInputIndex = 0; nInputIndex < m_nDInputs; nInputIndex++) {

      oIn.saveAssign(*static_cast<T*>(getDI(nInputIndex)));

      if (0 == nInputIndex) {
        OUT().saveAssign(oIn);
      } else {
        oOut.saveAssign(OUT());
        OUT().saveAssign(AND(oOut, oIn));
      }
    }
  }
};

#endif //close the ifdef sequence from the beginning of the file

