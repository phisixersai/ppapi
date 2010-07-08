// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_C_PPP_CLASS_H_
#define PPAPI_C_PPP_CLASS_H_

#include "ppapi/c/pp_stdint.h"
#include "ppapi/c/pp_var.h"

typedef struct _pp_Var PP_Var;

// Interface for the plugin to implement JavaScript-accessible objects.
//
// This interface has no interface name. Instead, the plugin passes a pointer
// to this interface to PPB_Var.CreateObject that corresponds to the object
// being implemented.
//
// Please see the PPB_Var interface for more information on these functions.
// This interface just allows you to implement the "back end" of those
// functions, so most of the contract is specified in that interface.
//
// Please also see:
//   http://code.google.com/p/ppapi/wiki/InterfacingWithJavaScript
// for general information on using and implementing vars.
typedef struct _ppp_Class {
  // |name| is guaranteed to be an integer or string type var. Exception is
  // guaranteed non-NULL. This test should also return true for methods, a
  // caller will have to call HasMethod() to distinguish between method
  // properties and non-method properties.
  bool (*HasProperty)(void* object,
                      PP_Var name,
                      PP_Var* exception);

  // |name| is guaranteed to be a string-type or integer-type var. Exception is
  // guaranteed non-NULL. If the property does not exist, return false and
  // don't set the exception. Errors in this function will probably not occur
  // in general usage, but if you need to throw an exception, return false.
  bool (*HasMethod)(void* object,
                    PP_Var name,
                    PP_Var* exception);

  // |name| is guaranteed to be a string-type or an integer-type var. Exception
  // is gauaranteed non-NULL. If the property does not exist, set the exception
  // and return a var of type Void.
  PP_Var (*GetProperty)(void* object,
                        PP_Var name,
                        PP_Var* exception);

  // Exception is guaranteed non-NULL.
  //
  // This should include all enumerable properties, including methods. Be sure
  // to set |*property_count| to 0 and |properties| to NULL in all failure
  // cases, these should never be unset when calling this function. The
  // pointers passed in are guaranteed not to be NULL, so you don't have to
  // NULL check them.
  //
  // If you have any properties, allocate the property array with
  // PPB_Core.MemAlloc(sizeof(PP_Var) * property_count) and add a reference
  // to each property on behalf of the caller. The caller is responsible for
  // Release()ing each var and calling PPB_Core.MemFree on the property pointer.
  void (*GetAllPropertyNames)(void* object,
                              uint32_t* property_count,
                              PP_Var** properties,
                              PP_Var* exception);

  // |name| is guaranteed to be an integer or string type var. Exception is
  // guaranteed non-NULL.
  void (*SetProperty)(void* object,
                      PP_Var name,
                      PP_Var value,
                      PP_Var* exception);

  // |name| is guaranteed to be an integer or string type var. Exception is
  // guaranteed non-NULL.
  void (*RemoveProperty)(void* object,
                         PP_Var name,
                         PP_Var* exception);

  // TODO(brettw) need native array access here.

  // |name| is guaranteed to be a string type var. Exception is guaranteed
  // non-NULL
  PP_Var (*Call)(void* object,
                 PP_Var method_name,
                 uint32_t argc,
                 PP_Var* argv,
                 PP_Var* exception);

  // Exception is guaranteed non-NULL.
  PP_Var (*Construct)(void* object,
                      uint32_t argc,
                      PP_Var* argv,
                      PP_Var* exception);

  // Called when the reference count of the object reaches 0. Normally, plugins
  // would free their internal data pointed to by the |object| pointer.
  void (*Deallocate)(void* object);
} PPP_Class;

#endif  // PPAPI_C_PPP_CLASS_H_