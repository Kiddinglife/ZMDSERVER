#ifndef Scriptable_H_
#define Scriptable_H_

#include "ace/pre.h"
#include "common/common.h"
#include "py_macros.h"

ACE_KBE_BEGIN_VERSIONED_NAMESPACE_DECL

namespace PythonScripts
{
	struct ScriptObject : public PyObject
	{
		/**��ǰ�ű�ģ������ */
		static PyTypeObject _scriptType;
		typedef ScriptObject ThisClass;

		/** ���ս�Ҫ����װ���ű�ģ���еķ����ͳ�Ա����б� */
		static PyMethodDef* _ScriptObject_lpScriptmethods;
		static PyMemberDef* _ScriptObject_lpScriptmembers;
		static PyGetSetDef* _ScriptObject_lpgetseters;

		/** ��ģ����Ҫ��©���ű��ķ����ͳ�Ա�� ���ջᱻ���뵽�����2��ָ���б��� */
		static PyMethodDef _ScriptObject_scriptMethods[ ];
		static PyMemberDef _ScriptObject_scriptMembers[ ];
		static PyGetSetDef _ScriptObject_scriptGetSeters[ ];

		static bool _ScriptObject_py_installed;

		// ���е�kbe�ű����
		typedef UnorderedMap<std::string, PyTypeObject*> SCRIPTOBJECT_TYPES;
		static SCRIPTOBJECT_TYPES scriptObjectTypes;

		ScriptObject(PyTypeObject* pyType, bool isInitialised = false);
		virtual ~ScriptObject();

		// �ű��������ü��� 
		void incRef() const { Py_INCREF(( PyObject* )this); }
		void decRef() const { Py_DECREF(( PyObject* )this); }
		int refCount() const { return int(( ( PyObject* )this )->ob_refcnt); }

		// ��ö��������
		PyObject* tp_repr();
		PyObject* tp_str();

		// �ű������ȡ���Ի��߷���
		PyObject* onScriptGetAttribute(PyObject* attr) { return PyObject_GenericGetAttr(this, attr); }

		// �ű������������Ի��߷���
		int onScriptSetAttribute(PyObject* attr, PyObject* value) { return PyObject_GenericSetAttr(static_cast<PyObject*>( this ), attr, value); }

		// �ű�����ɾ��һ������
		int onScriptDelAttribute(PyObject* attr);

		// �ű������ʼ��
		int onScriptInit(PyObject* self, PyObject *args, PyObject* kwds) { return 0; }

		// ��ȡ�����������
		// For printing, in format "<module>.<name>" 
		const char* scriptName() const { return ob_type->tp_name; }

		static PyTypeObject* getScriptObjectType(const std::string& name);

		// �ű����󴴽�һ���ö���
		static PyObject* tp_new(PyTypeObject* type, PyObject* args, PyObject* kwds) { return type->tp_alloc(type, 0); }

		// �ű�����װʱ������
		static void onInstallScript(PyObject* mod) { }

		// �ű���ж��ʱ������
		static void onUninstallScript() { }

		//DECLARE_PY_GET_MOTHOD(py__module__);
		PyObject* py__module__() { return PyUnicode_FromString(scriptName()); }
		static PyObject* __pyget_py__module__(PyObject *self, void *closure) { return static_cast<ThisClass*>( self )->py__module__(); }

		//DECLARE_PY_GET_MOTHOD(py__qualname__);
		PyObject* py__qualname__() { return PyUnicode_FromString(scriptName()); }
		static PyObject* __pyget_py__qualname__(PyObject *self, void *closure) { return static_cast<ThisClass*>( self )->py__qualname__(); }

		//DECLARE_PY_GET_MOTHOD(py__name__);
		PyObject* py__name__() { return PyUnicode_FromString(scriptName()); }
		static PyObject* __pyget_py__name__(PyObject *self, void *closure) { return static_cast<ThisClass*>( self )->py__name__(); }

		/* python�����Ķ���������python���ͷ�*/
		static void _tp_dealloc(PyObject* self) { ScriptObject::_scriptType.tp_free(self); }

		static PyObject* _tp_repr(PyObject* self) { return static_cast<ScriptObject*>( self )->tp_repr(); }
		static PyObject* _tp_str(PyObject* self) { return static_cast<ScriptObject*>( self )->tp_str(); }

		/** �ű�ģ������python�д��� */
		static PyObject* _tp_new(PyTypeObject* type, PyObject* args, PyObject* kwds) { return ScriptObject::tp_new(type, args, kwds); }

		/** python �����ȡ��ģ������Ի��߷��� */
		static PyObject* _tp_getattro(PyObject* self, PyObject* name) { return static_cast<ScriptObject*>( self )->onScriptGetAttribute(name); }

		/** python �����ʼ����ģ����� */
		static int _tp_init(PyObject* self, PyObject *args, PyObject* kwds) { return static_cast<ScriptObject*>( self )->onScriptInit(self, args, kwds); }

		/** python �������ñ�ģ������Ի��߷��� */
		static int _tp_setattro(PyObject* self, PyObject* name, PyObject* value)
		{
			return ( value != NULL ) ? static_cast<ScriptObject*>( self )->onScriptSetAttribute(name, value) : static_cast<ScriptObject*>( self )->onScriptDelAttribute(name);
		}

		/** getset��ֻ������ */
		static int __py_readonly_descr(PyObject* self, PyObject* value, void* closure);

		/** getset��ֻд���� */
		static int __py_writeonly_descr(PyObject* self, PyObject* value, void* closure);

		/** ����ӿڿ��Ի�õ�ǰģ��Ľű���� */
		static PyTypeObject* getScriptType(void) { return &_scriptType; }

		static PyTypeObject* getBaseScriptType(void)
		{
			if( strcmp("ScriptObject", "ScriptObject") == 0 )
				return NULL;
			return ScriptObject::getScriptType();
		}

		static long calcDictOffset(void)
		{
			if( strcmp("ScriptObject", "ScriptObject") == 0 )
				return 0;
			return 0;
		}

		/** �������м̳�ģ��ı�¶�������� */
		static int calcTotalMethodCount(void);

		/** �������м̳�ģ��ı�¶��Ա���� */
		static int calcTotalMemberCount(void);

		/** �������м̳�ģ��ı�¶getset���� */
		static int calcTotalGetSetCount(void);

		/** �����и����Լ���ǰģ��ı�¶��Ա�ͷ�����װ������Ҫ����ű����б��� */
		static void setupScriptMethodAndAttribute(PyMethodDef* lppmf, PyMemberDef* lppmd, PyGetSetDef* lppgs);

		/** ��װ��ǰ�ű�ģ�� @param mod: ��Ҫ�������ģ�� */
		static void installScript(PyObject* mod, const char* name = "ScriptObject");

		/** ж�ص�ǰ�ű�ģ�� */
		static void uninstallScript(void);
	};
}

ACE_KBE_END_VERSIONED_NAMESPACE_DECL
#include <ace/post.h>
#endif