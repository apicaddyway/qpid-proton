#ifndef PROTON_CPP_PROTONHANDLE_H
#define PROTON_CPP_PROTONHANDLE_H

/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */

#include "proton/ImportExport.hpp"

namespace proton {
namespace reactor {

template <class> class ProtonImplRef;

/**
 * See Handle.h.  Similar but for lightly wrapped Proton pn_object_t targets.
 */
template <class T> class ProtonHandle {
  public:

    /**@return true if handle is valid,  i.e. not null. */
    PROTON_CPP_INLINE_EXTERN bool isValid() const { return impl; }

    /**@return true if handle is null. It is an error to call any function on a null handle. */
    PROTON_CPP_INLINE_EXTERN bool isNull() const { return !impl; }

    /** Conversion to bool supports idiom if (handle) { handle->... } */
    PROTON_CPP_INLINE_EXTERN operator bool() const { return impl; }

    /** Operator ! supports idiom if (!handle) { do_if_handle_is_null(); } */
    PROTON_CPP_INLINE_EXTERN bool operator !() const { return !impl; }

    void swap(ProtonHandle<T>& h) { T* t = h.impl; h.impl = impl; impl = t; }

  private:
    // Not implemented, subclasses must implement.
    ProtonHandle(const ProtonHandle&);
    ProtonHandle& operator=(const ProtonHandle&);

  protected:
    typedef T Impl;
    PROTON_CPP_INLINE_EXTERN ProtonHandle() :impl() {}

    mutable Impl* impl;

  friend class ProtonImplRef<T>;
};

}}

#endif  /*!PROTON_CPP_PROTONHANDLE_H*/