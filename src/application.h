/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * application.h:
 *
 * Copyright 2008 Novell, Inc.  (http://www.novell.com)
 *
 * See the LICENSE file included with the distribution for details.
 */

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <glib.h>

#include "utils.h"
#include "enums.h"
#include "control.h"
#include "dependencyobject.h"
#include "downloader.h"

/* @CBindingRequisite */
typedef Style *(*GetDefaultStyleCallback)(ManagedTypeInfo *key);
/* @CBindingRequisite */
typedef void (*ConvertSetterValuesCallback)(Style *style);
/* @CBindingRequisite */
typedef void *(*ConvertKeyframeValueCallback)(int kind, DependencyProperty *property, Value *original, Value *converted);
/* @CBindingRequisite */
typedef ManagedStreamCallbacks (*GetResourceCallback)(const char *resourceBase, const char *name);

enum NotifyType {NotifyStarted, NotifySize, NotifyProgressChanged, NotifyCompleted, NotifyFailed};
typedef void (*NotifyFunc) (NotifyType type, gint64 args, gpointer user_data);
typedef void (*WriteFunc) (void* buf, gint32 offset, gint32 n, gpointer user_data);

/* @Namespace=None */
/* @ManagedDependencyProperties=Manual */
/* @ManagedEvents=Manual */
class Application : public DependencyObject {
public:
	/* @PropertyType=ResourceDictionary,AutoCreateValue,GenerateAccessors */
	const static int ResourcesProperty;

	/* @GenerateCBinding,GeneratePInvoke */
	Application ();
	
	/* @GenerateCBinding,GeneratePInvoke */
	void RegisterCallbacks (GetDefaultStyleCallback get_default_style_cb, ConvertSetterValuesCallback convert_setter_values_cb, GetResourceCallback get_resource_cb, ConvertKeyframeValueCallback convert_keyframe_callback);
	
	Style *GetDefaultStyle (ManagedTypeInfo *key);
	void ConvertSetterValues (Style *style);
	
	void ConvertKeyframeValue (Type::Kind kind, DependencyProperty *property, Value *original, Value *converted);
	
	bool GetResource (const char *resourceBase, const Uri *uri, NotifyFunc notify_cb, WriteFunc write_cb, DownloaderAccessPolicy policy, Cancellable *cancellable, gpointer user_data);
	char *GetResourceAsPath (const char *resourceBase, const Uri *uri);
	const char *GetResourceRoot ();
	
	/* @GenerateCBinding,GeneratePInvoke */
	void CheckAndDownloadUpdateAsync ();
	
	void UpdateComplete (bool updated, const char *error);
	
	/* @GenerateCBinding,GeneratePInvoke */
	bool IsRunningOutOfBrowser ();
	
	void SetInstallState (InstallState state);
	/* @GenerateCBinding,GeneratePInvoke */
	InstallState GetInstallState ();
	
	bool IsInstallable ();
	
	/* @GenerateCBinding,GeneratePInvoke */
	bool InstallWithError (MoonError *error);
	void Uninstall ();
	bool Install ();
	
	/* @GenerateCBinding,GeneratePInvoke */
	static Application *GetCurrent ();
	/* @GenerateCBinding,GeneratePInvoke */
	static void SetCurrent (Application *current);
	
	//
	// Property Accessors
	//
	void SetResources (ResourceDictionary *value);
	ResourceDictionary *GetResources ();
	
	const static int InstallStateChangedEvent;
	const static int CheckAndDownloadUpdateCompletedEvent;
	
protected:
	virtual ~Application ();

private:
	GetDefaultStyleCallback get_default_style_cb;
	ConvertSetterValuesCallback convert_setter_values_cb;
	ConvertKeyframeValueCallback convert_keyframe_callback;
	GetResourceCallback get_resource_cb;
	InstallState install_state;
	char *resource_root;
	
	static void update_complete (bool updated, const char *error, gpointer user_data);
};

#endif /* __APPLICATION_H__ */
