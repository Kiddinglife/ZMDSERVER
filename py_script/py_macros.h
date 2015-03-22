#ifndef PY_MACROS_H_
#define PY_MACROS_H_

#include "ace/pre.h"
#include "common/common.h"
#include "Python.h"
#include "structmember.h"

ACE_KBE_BEGIN_VERSIONED_NAMESPACE_DECL

namespace PythonScripts
{
// PY_METHOD_ARG DEFINES
#define PY_METHOD_ARG_char								    char
#define PY_METHOD_ARG_char_ARG						    char
#define PY_METHOD_ARG_char__PYARGTYPE			    "b"

#define PY_METHOD_ARG_charptr							    char *
#define PY_METHOD_ARG_charptr_ARG					    char *
#define PY_METHOD_ARG_charptr_PYARGTYPE		    "s"

#define PY_METHOD_ARG_const_charptr						const char *
#define PY_METHOD_ARG_const_charptr_ARG				char *
#define PY_METHOD_ARG_const_charptr_PYARGTYPE	"s"

#define PY_METHOD_ARG_PyObject_ptr						PyObject *
#define PY_METHOD_ARG_PyObject_ptr_ARG				PyObject *
#define PY_METHOD_ARG_PyObject_ptr_PYARGTYPE	"O"

#define PY_METHOD_ARG_float								   float
#define PY_METHOD_ARG_float_ARG						   float
#define PY_METHOD_ARG_float_PYARGTYPE			   "f"

#define PY_METHOD_ARG_double							   double
#define PY_METHOD_ARG_double_ARG					   double
#define PY_METHOD_ARG_double_PYARGTYPE			   "d"

#define PY_METHOD_ARG_uint8							      ACE_UINT8
#define PY_METHOD_ARG_uint8_ARG					      ACE_UINT8
#define PY_METHOD_ARG_uint8_PYARGTYPE		      "B"

#define PY_METHOD_ARG_uint16							     ACE_UINT16
#define PY_METHOD_ARG_uint16_ARG					     ACE_UINT16
#define PY_METHOD_ARG_uint16_PYARGTYPE		     "H"

#define PY_METHOD_ARG_uint32							    ACE_UINT32
#define PY_METHOD_ARG_uint32_ARG					    ACE_UINT32
#define PY_METHOD_ARG_uint32_PYARGTYPE		    "I"

#define PY_METHOD_ARG_uint64							   ACE_UINT64
#define PY_METHOD_ARG_uint64_ARG					   ACE_UINT64
#define PY_METHOD_ARG_uint64_PYARGTYPE		   "K"

#define PY_METHOD_ARG_int8								   ACE_INT8
#define PY_METHOD_ARG_int8_ARG						   ACE_INT8
#define PY_METHOD_ARG_int8_PYARGTYPE			   "b"

#define PY_METHOD_ARG_int16							  ACE_INT16
#define PY_METHOD_ARG_int16_ARG					  ACE_INT16
#define PY_METHOD_ARG_int16_PYARGTYPE		  "h"

#define PY_METHOD_ARG_int								  ACE_INT32
#define PY_METHOD_ARG_int_ARG						  ACE_INT32
#define PY_METHOD_ARG_int_PYARGTYPE			  "i"

#define PY_METHOD_ARG_int32							 ACE_INT32
#define PY_METHOD_ARG_int32_ARG					 ACE_INT32
#define PY_METHOD_ARG_int32_PYARGTYPE		 "i"

#define PY_METHOD_ARG_int64							ACE_INT64
#define PY_METHOD_ARG_int64_ARG					ACE_INT32
#define PY_METHOD_ARG_int64_PYARGTYPE		"L"


#define PY_METHOD_ARG_ScriptID						ScriptID
#define PY_METHOD_ARG_ScriptID_ARG				ScriptID
#define PY_METHOD_ARG_ScriptID_PYARGTYPE	"i"

#define PY_METHOD_ARG_TIMER_ID					TIMER_ID
#define PY_METHOD_ARG_TIMER_ID_ARG			TIMER_ID
#define PY_METHOD_ARG_TIMER_ID_PYARGTYPE "I"

#define PY_METHOD_ARG_SPACE_ID					SPACE_ID
#define PY_METHOD_ARG_SPACE_ID_ARG			SPACE_ID
#define PY_METHOD_ARG_SPACE_ID_PYARGTYPE "I"

#define PY_METHOD_ARG_ENTITY_ID					ENTITY_ID
#define PY_METHOD_ARG_ENTITY_ID_ARG			ENTITY_ID
#define PY_METHOD_ARG_ENTITY_ID_PYARGTYPE "i"


///////////////////////////////// SCRIPT METHOD EXPOSURE DEFINES ////////////////////////////////
// python��Ĭ�Ͽշ���ֵ
#define PY_NONE_SAFE_RETURN          { Py_INCREF(Py_None); return Py_None; }			
#define PY_SAFE_DECRFE(PYOBJPTR)    Py_XDECREF(PYOBJPTR);
#define PY_SAFE_INCRFE(PYOBJPTR)    Py_XINCREF(PYOBJPTR);

// python�Ķ����ͷ�	
#define PY_OBJ_RELEASE(pyObj)		    if(pyObj){Py_DECREF(pyObj); pyObj = NULL;}				

// �����ǰ�ű������Ĵ�����Ϣ	
#define SCRIPT_ERROR_CHECK()		   {if(PyErr_Occurred()){PyErr_PrintEx(0);}}

/* ���屩¶���ű��ķ����� */
#define SCRIPT_METHOD_DECLARE_BEGIN(CLASS)                                                                                                bool CLASS::_##CLASS##_py_installed = false; PyMethodDef CLASS::_##CLASS##_scriptMethods[ ] = {
#define TEMPLATE_SCRIPT_METHOD_DECLARE_BEGIN(TEMPLATE_HEADER, TEMPLATE_CLASS, CLASSNAME)       TEMPLATE_HEADER bool TEMPLATE_CLASS::_##CLASSNAME##_py_installed = false; \
                                                                                                                                                                             TEMPLATE_HEADER PyMethodDef TEMPLATE_CLASS::_##CLASSNAME##_scriptMethods[] = {
#define SCRIPT_METHOD_DECLARE(METHOD_NAME, METHOD_FUNC, FLAGS, DOC)                                            {METHOD_NAME, (PyCFunction)&__py_##METHOD_FUNC, FLAGS, DOC},
#define SCRIPT_DIRECT_METHOD_DECLARE(METHOD_NAME, METHOD_FUNC, FLAGS, DOC)                               {METHOD_NAME, (PyCFunction)&METHOD_FUNC, FLAGS, DOC},
#define SCRIPT_METHOD_DECLARE_END()                                                                                                            {NULL}};

/* ��ģ��׷�ӷ��� */
#define APPEND_SCRIPT_MODULE_METHOD(MODULE, NAME, FUNC, FLAGS, SELF)	                                            static PyMethodDef __pymethod_##NAME = {#NAME, (PyCFunction) FUNC, FLAGS, NULL}; \
	                                                                                                                                                                        if(PyModule_AddObject(MODULE, #NAME, PyCFunction_New(&__pymethod_##NAME, SELF)) \
	                                                                                                                                                                        { SCRIPT_ERROR_CHECK(); ACE_DEBUG((LM_ERROR, "append " #NAME " to pyscript is error!\n")); }
/** ���屩¶���ű������Ժ� */
#define SCRIPT_MEMBER_DECLARE_BEGIN(CLASS)                                                                                               PyMemberDef CLASS::_##CLASS##_scriptMembers[ ] =	{
#define TEMPLATE_SCRIPT_MEMBER_DECLARE_BEGIN(TEMPLATE_HEADER, TEMPLATE_CLASS, CLASSNAME)	    TEMPLATE_HEADER PyMemberDef TEMPLATE_CLASS::_##CLASSNAME##_scriptMembers[ ] =	{

#define SCRIPT_MEMBER_DECLARE(MEMBER_NAME, MEMBER_REF, MEMBER_TYPE, FLAGS, DOC)				        { const_cast<char*>(MEMBER_NAME), MEMBER_TYPE, offsetof(ThisClass, MEMBER_REF), FLAGS, DOC },
#define SCRIPT_MEMBER_DECLARE_END()															                                                { NULL }};
	
/** ���屩¶���ű���getset���Ժ� */
#define SCRIPT_GETSET_DECLARE_BEGIN(CLASS)													                                               PyGetSetDef CLASS::_##CLASS##_scriptGetSeters[] = {
#define TEMPLATE_SCRIPT_GETSET_DECLARE_BEGIN(TEMPLATE_HEADER, TEMPLATE_CLASS, CLASSNAME)	       TEMPLATE_HEADER PyGetSetDef TEMPLATE_CLASS::_##CLASSNAME##_scriptGetSeters[] =	{
#define SCRIPT_GETSET_DECLARE(NAME, GET, SET, DOC, CLOSURE)									                                   {const_cast<char*>(NAME), (getter)__pyget_##GET, (setter)__pyset_##SET, DOC, CLOSURE},
#define SCRIPT_GET_DECLARE(NAME, GET, DOC, CLOSURE)											                                       {const_cast<char*>(NAME), (getter)__pyget_##GET, (setter)__py_readonly_descr, DOC, const_cast<char*>(NAME)},
#define SCRIPT_SET_DECLARE(NAME, SET, DOC, CLOSURE)											                                       {const_cast<char*>(NAME), (getter)__pyset_##SET, (setter)__py_writeonly_descr, DOC, const_cast<char*>(NAME)},
#define SCRIPT_GETSET_DECLARE_END()															                                                   {NULL}};
}

/* ����һ���ű�get���� */
#define DECLARE_PY_GET_MOTHOD(MNAME)	                                                                                                   PyObject* MNAME(); \
                                                                                                                                                                           static PyObject* __pyget_##MNAME(PyObject *self, void *closure) \
                                                                                                                                                                           { return static_cast<ThisClass*>(self)->MNAME(); }	

/* ����һ���ű�set���� */
#define DECLARE_PY_SET_MOTHOD(MNAME)												                                                       int MNAME(PyObject *value);	\
                                                                                                                                                                           static int __pyset_##MNAME(PyObject *self, PyObject *value, void *closure) \
                                                                                                                                                                           {return static_cast<ThisClass*>(self)->MNAME(value);}	

/* ����һ���ű�getset���� */
#define DECLARE_PY_GETSET_MOTHOD(GETNAME, SETNAME)									                                       DECLARE_PY_GET_MOTHOD(GETNAME) DECLARE_PY_SET_MOTHOD(SETNAME)												


#define SCRIPT_HREADER_BASE(CLASS, SUPERCLASS)                                                   \
/**��ǰ�ű�ģ������ 
*/                                                                                                                                  \
static PyTypeObject _scriptType;                                                                                    \
typedef CLASS ThisClass;			                                                                                    \
                                                                                                                                    \
static PyObject* _tp_repr(PyObject* self) {return static_cast<CLASS*>(self)->tp_repr();}	\
static PyObject* _tp_str(PyObject* self)   {return static_cast<CLASS*>( self )->tp_str();}   \
                                                                                                                                    \
/** �ű�ģ������python�д���
*/																					                                                \
static PyObject* _tp_new(PyTypeObject* type, PyObject* args, PyObject* kwds)			    \
{return CLASS::tp_new(type, args, kwds);}                                                                      \
                                                                                                                                    \
/** python �����ȡ��ģ������Ի��߷���
*/																                                                                    \
static PyObject* _tp_getattro(PyObject* self, PyObject* name)							            \
{																						                                            \
return static_cast<CLASS*>( self )->onScriptGetAttribute(name);						            \
}                                                                                                                                   \
                                                                                                                                    \
/** python �����ʼ����ģ�����
*/																					                                                \
static int _tp_init(PyObject* self, PyObject *args, PyObject* kwds)						            \
{																						                                            \
return static_cast<CLASS*>( self )->onScriptInit(self, args, kwds);					                \
}																						                                            \
                                                                                                                                    \
/** python �������ñ�ģ������Ի��߷���
*/																                                                                    \
static int _tp_setattro(PyObject* self, PyObject* name, PyObject* value)				            \
{																						                                            \
return ( value != NULL ) ?                                                                                             \
static_cast<CLASS*>( self )->onScriptSetAttribute(name, value) :                                  \
static_cast<CLASS*>( self )->onScriptDelAttribute(name);						                       \
}                                                                                                                                  \
                                                                                                                                   \
public:																						                                   \
/** ���ս�Ҫ����װ���ű�ģ���еķ����ͳ�Ա����б�
*/										                                                                                           \
static PyMethodDef* _##CLASS##_lpScriptmethods;											           \
static PyMemberDef* _##CLASS##_lpScriptmembers;											       \
static PyGetSetDef* _##CLASS##_lpgetseters;												               \
	                                                                                                                               \
/** ��ģ����Ҫ��©���ű��ķ����ͳ�Ա�� ���ջᱻ���뵽�����2��ָ���б���
*/			                                                                                                                       \
static PyMethodDef _##CLASS##_scriptMethods[];											           \
static PyMemberDef _##CLASS##_scriptMembers[];											           \
static PyGetSetDef _##CLASS##_scriptGetSeters[];										                   \
                                                                                                                                   \
static bool _##CLASS##_py_installed;													                           \
                                                                                                                                   \
/** getset��ֻ������
*/																						                                           \
static int __py_readonly_descr(PyObject* self, PyObject* value, void* closure)			       \
{																						                                           \
PyErr_Format(PyExc_TypeError,                                                                                    \
"Sorry, this attribute %s.%s is read-only", ( self != NULL ? self->ob_type->tp_name     \
: #CLASS ), ( closure != NULL ? (char*) closure : "unknown" ));							          \
PyErr_PrintEx(0);																	                                      \
return 0;																			                                          \
}																						                                          \
																							                                      \
/** getset��ֻд����
*/																						                                          \
static int __py_writeonly_descr(PyObject* self, PyObject* value, void* closure)			      \
{																						                                          \
PyErr_Format(PyExc_TypeError,                                                                                   \
"Sorry, this attribute %s.%s is write-only", ( self != NULL ? self->ob_type->tp_name    \
: #CLASS ), ( closure != NULL ? (char*) ( closure ) : "unknown" ));						          \
PyErr_PrintEx(0);																	                                      \
return 0;																			                                          \
}																						                                          \
																							                                      \
/** ����ӿڿ��Ի�õ�ǰģ��Ľű���� 
*/																	                                                             \
static PyTypeObject* getScriptType(void)												                     \
{																						                                         \
return &_scriptType;																                                     \
}																						                                         \
static PyTypeObject* getBaseScriptType(void)											                 \
{																						                                         \
if( strcmp("ScriptObject", #SUPERCLASS) == 0 )										                     \
return 0;																		                                             \
return SUPERCLASS::getScriptType();													                         \
}																						                                         \
                                                                                                                                 \
static long calcDictOffset(void)														                             \
{																						                                         \
if(strcmp("ScriptObject", #SUPERCLASS) == 0)	return 0;											 \
return 0;																			                                         \
}																						                                         \
																							                                     \
/** �������м̳�ģ��ı�¶�������� 
*/																                                                                 \
static int calcTotalMethodCount(void)													                     \
{																						                                         \
int nlen = 0;																		                                         \
while( true )																			                                     \
{																					                                             \
PyMethodDef* pmf = &_##CLASS##_scriptMethods[nlen];								         \
if(!pmf->ml_doc && !pmf->ml_flags && !pmf->ml_meth && !pmf->ml_name)		 \
break;																		                                                 \
nlen++;																			                                         \
}																					                                             \
if(strcmp(#CLASS, #SUPERCLASS) == 0)												                     \
return nlen;																	                                             \
return SUPERCLASS::calcTotalMethodCount() + nlen;									             \
}																						                                         \
																							                                     \
/** �������м̳�ģ��ı�¶��Ա���� 
*/																		                                                         \
static int calcTotalMemberCount(void)													                     \
{																						                                         \
int nlen = 0;																		                                         \
while( true )																			                                     \
{																					                                             \
PyMemberDef* pmd = &_##CLASS##_scriptMembers[nlen];								         \
if(!pmd->doc && !pmd->flags && !pmd->type && !pmd->name && !pmd->offset)\
break;																		                                                 \
nlen++;																			                                         \
}																					                                             \
																							                                     \
if(strcmp(#CLASS, #SUPERCLASS) == 0)												                     \
return nlen;																	                                             \
return SUPERCLASS::calcTotalMemberCount() + nlen;									             \
}																						                                         \
																							                                     \
/** �������м̳�ģ��ı�¶getset����
 */																	                                                             \
static int calcTotalGetSetCount(void)													                         \
{																						                                         \
	int nlen = 0;																		                                     \
	while( true )																			                                 \
	{																					                                         \
	PyGetSetDef* pgs = &_##CLASS##_scriptGetSeters[nlen];							             \
	if(!pgs->doc && !pgs->get && !pgs->set && !pgs->name && !pgs->closure)		 \
	break;																		                                             \
	nlen++;																			                                     \
	}																					                                         \
																							                                     \
	if(strcmp(#CLASS, #SUPERCLASS) == 0)												                 \
	return nlen;																	                                         \
	return SUPERCLASS::calcTotalGetSetCount() + nlen;									             \
}																						                                         \
																							                                     \
/** �����и����Լ���ǰģ��ı�¶��Ա�ͷ�����װ������Ҫ����ű����б��� 
*/				                                                                                                                 \
static void setupScriptMethodAndAttribute(PyMethodDef* lppmf,                             \
PyMemberDef* lppmd,	PyGetSetDef* lppgs)	                                                             \
{																						                                         \
		int i = 0;																			                                 \
		PyMethodDef* pmf = NULL;															                     \
		PyMemberDef* pmd = NULL;															                 \
		PyGetSetDef* pgs = NULL;															                     \
																							                                     \
		while(true){																		                                 \
		pmf = &_##CLASS##_scriptMethods[i];												                 \
		if(!pmf->ml_doc && !pmf->ml_flags && !pmf->ml_meth && !pmf->ml_name)\
		break;																		                                         \
		i++;																			                                         \
		*(lppmf++) = *pmf;																                             \
		}																					                                     \
																							                                     \
		i = 0;																				                                     \
		while(true){																		                                 \
		pmd = &_##CLASS##_scriptMembers[i];												             \
		if(!pmd->doc && !pmd->flags && !pmd->type && !pmd->name && !pmd->offset)\
		break;																		                                         \
		i++;																			                                         \
		*(lppmd++) = *pmd;																                             \
		}																					                                     \
																							                                     \
		i = 0;																				                                     \
		while(true){																		                                 \
		pgs = &_##CLASS##_scriptGetSeters[i];											                     \
		if(!pgs->doc && !pgs->get && !pgs->set && !pgs->name && !pgs->closure) \
		break;																		                                         \
		i++;																			                                         \
		*(lppgs++) = *pgs;																                             \
		}																					                                     \
																							                                     \
		if(strcmp(#CLASS, #SUPERCLASS) == 0){												             \
			*(lppmf) = *pmf;																                             \
			*(lppmd) = *pmd;																                             \
			*(lppgs) = *pgs;																                                 \
			return;																			                                 \
		}																					                                     \
																							                                     \
		SUPERCLASS::setupScriptMethodAndAttribute(lppmf, lppmd, lppgs);					 \
}																						                                         \
																							                                     \
/** ��װ��ǰ�ű�ģ�� @param mod: ��Ҫ�������ģ��
*/												                                                                                 \
static void installScript(PyObject* mod, const char* name = #CLASS)						     \
{																						                                         \
	int nMethodCount = CLASS::calcTotalMethodCount();						                     \
	int nMemberCount = CLASS::calcTotalMemberCount();						                     \
	int nGetSetCount = CLASS::calcTotalGetSetCount();						                         \
	                                                                                                                             \
	_##CLASS##_lpScriptmethods = new PyMethodDef[nMethodCount + 2];				 \
	_##CLASS##_lpScriptmembers	= new PyMemberDef[nMemberCount + 2];			 \
	_##CLASS##_lpgetseters		= new PyGetSetDef[nGetSetCount + 2];					 \
																							                                     \
	setupScriptMethodAndAttribute(_##CLASS##_lpScriptmethods,							 \
									                  _##CLASS##_lpScriptmembers,							 \
									                  _##CLASS##_lpgetseters);								     \
																							                                     \
	_scriptType.tp_methods		= _##CLASS##_lpScriptmethods;							         \
	_scriptType.tp_members		= _##CLASS##_lpScriptmembers;							     \
	_scriptType.tp_getset		= _##CLASS##_lpgetseters;								                 \
																																 \
	CLASS::onInstallScript(mod);														                             \
	if (PyType_Ready(&_scriptType) < 0) {												                     \
		ACE_DEBUG((LM_ERROR, "PyType_Ready(" #CLASS ") is error!"));                        \
		PyErr_Print();																	                                     \
		return;																			                                     \
	}																					                                         \
																							                                     \
	if(mod)																				                                     \
	{																					                                         \
		Py_INCREF(&_scriptType);														                             \
		if(PyModule_AddObject(mod, name, (PyObject *)&_scriptType) < 0)					 \
		{																				                                         \
		ACE_DEBUG((LM_ERROR, "PyModule_AddObject({%s}) is error!", name));            \
		}																				                                         \
	}																					                                         \
																							                                     \
	SCRIPT_ERROR_CHECK();																                         \
	_##CLASS##_py_installed = true;														                     \
	ScriptObject::scriptObjectTypes[name] = &_scriptType;								             \
}																						                                         \
																							                                     \
/** ж�ص�ǰ�ű�ģ�� 
*/																						                                         \
static void uninstallScript(void)														                             \
{																						                                         \
	SAFE_RELEASE_ARRAY(_##CLASS##_lpScriptmethods);										     \
	SAFE_RELEASE_ARRAY(_##CLASS##_lpScriptmembers);										     \
	SAFE_RELEASE_ARRAY(_##CLASS##_lpgetseters);											         \
	CLASS::onUninstallScript();															                             \
	if(_##CLASS##_py_installed)															                         \
	Py_DECREF(&_scriptType);														                                 \
}																						                                         

// �ű�����ͷ ��ͨ����pythonĬ�Ϸ������ʽ�����Ķ��� ��
#define SCRIPT_OBJECT_HREADER(CLASS, SUPERCLASS)\
SCRIPT_HREADER_BASE(CLASS, SUPERCLASS);\
/* python�����Ķ���������python���ͷ�*/ \
static void _tp_dealloc(PyObject* self){CLASS::_scriptType.tp_free((self);}			

// �����ű�����ͷ�����ģ��ͨ�����ṩ��python�ű��н��м̳е�һ�������� ��
#define BASE_SCRIPT_HREADER(CLASS, SUPERCLASS)\
SCRIPT_HREADER_BASE(CLASS, SUPERCLASS);\
/* python�����Ķ���������python���ͷ� */  \
static void _tp_dealloc(PyObject* self)\
{\
static_cast<CLASS*>( self )->~CLASS();	\
CLASS::_scriptType.tp_free(self);	\
}		

// ʵ���ű�����ͷ ������ű���������c++�н���new������ ��
#define INSTANCE_SCRIPT_HREADER(CLASS, SUPERCLASS)	\
SCRIPT_HREADER_BASE(CLASS, SUPERCLASS);	                    \
/* c++new�����Ķ��������delete���� */	                            \
static void _tp_dealloc(PyObject* self) {delete static_cast<CLASS*>( self );}

// BASE_SCRIPT_HREADER������ű���ʼ��, �����ɽű��̳�
#define BASE_SCRIPT_INIT(CLASS, CALL, SEQ, MAP, ITER, ITERNEXT)							\
PyMethodDef* CLASS::_##CLASS##_lpScriptmethods = NULL;									\
PyMemberDef* CLASS::_##CLASS##_lpScriptmembers = NULL;									\
PyGetSetDef* CLASS::_##CLASS##_lpgetseters = NULL;										        \
																							                                    \
PyTypeObject CLASS::_scriptType =														                    \
{																						                                        \
	PyVarObject_HEAD_INIT(NULL, 0)														                    \
	#CLASS,											/* tp_name */	                                            \
	sizeof(CLASS),									/* tp_basicsize */	                                        \
	0,														/* tp_itemsize */	                                        \
	(destructor)CLASS::_tp_dealloc,			/* tp_dealloc */	                                            \
	0,														/* tp_print */	                                                \
	0,														/* tp_getattr */	                                            \
	0,														/* tp_setattr */	                                            \
	0,														/* void *tp_reserved */	                                \
	CLASS::_tp_repr,								/* tp_repr */	                                                \
	0,														/* tp_as_number */	                                    \
	SEQ,													/* tp_as_sequence */	                                    \
	MAP,												/* tp_as_mapping */	                                    \
	0,														/* tp_hash */	                                                \
	CALL,												/* tp_call */	                                                \
	CLASS::_tp_str,									/* tp_str */	                                                \
	(getattrofunc)CLASS::_tp_getattro,	    /* tp_getattro */	                                        \
	(setattrofunc)CLASS::_tp_setattro,		/* tp_setattro */	                                        \
	0,														/* tp_as_buffer */	                                        \
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */	                            \
	0,														/* tp_doc */	                                                \
	0,														/* tp_traverse */	                                        \
	0,														/* tp_clear  */	                                            \
	0,														/* tp_richcompare */	                                    \
	0,														/* tp_weaklistoffset*/	                                \
	ITER,													/* tp_iter  */	                                                \
	ITERNEXT,											/* tp_iternext */                     	                    \
	0,														/* tp_methods */	                                        \
	0,														/* tp_members  */	                                        \
	0,														/* tp_getset  */	                                            \
	CLASS::getBaseScriptType(),				/* tp_base */	                                                \
	0,														/* tp_dict */	                                                \
	0,														/* tp_descr_get */	                                        \
	0,														/* tp_descr_set */	                                        \
	CLASS::calcDictOffset(),						/* tp_dictoffset */	                                        \
	0,														/* tp_init */	                                                \
	0,														/* tp_alloc */	                                                \
	0,														/* tp_new */	                                                \
	PyObject_GC_Del,								/* tp_free */	                                                \
	0,														/* tp_is_gc */	                                                \
	0,														/* tp_bases  */	                                            \
	0,														/* tp_mro */	                                                \
	0,														/* tp_cache  */	                                            \
	0,														/* tp_subclasses */	                                        \
	0,														/* tp_weaklist */	                                        \
	0,														/* tp_del */	                                                \
};																						                                        

#define TEMPLATE_SCRIPT_INIT(TEMPLATE_HEADER, TEMPLATE_CLASS,				   \
	                                             CLASS, CALL, SEQ, MAP, ITER, ITERNEXT)				   \
TEMPLATE_HEADER                                                                                                 \
PyMethodDef* TEMPLATE_CLASS::_##CLASS##_lpScriptmethods = NULL;			       \
TEMPLATE_HEADER                                                                                                 \
PyMemberDef* TEMPLATE_CLASS::_##CLASS##_lpScriptmembers = NULL;			   \
TEMPLATE_HEADER                                                                                                 \
PyGetSetDef* TEMPLATE_CLASS::_##CLASS##_lpgetseters = NULL;				           \
																							                                   \
TEMPLATE_HEADER PyTypeObject TEMPLATE_CLASS::_scriptType =						   \
{																						                                       \
	PyVarObject_HEAD_INIT(&PyType_Type, 0)												           \
	#CLASS,										    /* tp_name      */	\
	sizeof(TEMPLATE_CLASS),					/* tp_basicsize */	\
	0,														/* tp_itemsize  */	\
	(destructor)TEMPLATE_CLASS::_tp_dealloc,/* tp_dealloc */	\
	0,														/* tp_print            */	\
	0,														/* tp_getattr         */	\
	0,														/* tp_setattr         */	\
	0,														/* tp_compare     */	\
	TEMPLATE_CLASS::_tp_repr,				/* tp_repr            */	\
	0,														/* tp_as_number   */	\
	SEQ,													/* tp_as_sequence */	\
	MAP,											    /* tp_as_mapping  */	\
	0,														/* tp_hash */	\
	CALL,												/* tp_call  */	\
	TEMPLATE_CLASS::_tp_str,					/* tp_str   */	\
	(getattrofunc)CLASS::_tp_getattro,		/* tp_getattro */	\
	(setattrofunc)CLASS::_tp_setattro,		/* tp_setattro  */	\
	0,														/* tp_as_buffer */	\
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,	/* tp_flags  */	\
	"KBEngine::" #CLASS " objects.",		/* tp_doc */	\
	0,														/* tp_traverse */	\
	0,														/* tp_clear */	\
	0,														/* tp_richcompare */	\
	0,														/* tp_weaklistoffset*/	\
	ITER,													/* tp_iter         */	\
	ITERNEXT,											/* tp_iternext        */	\
	0,														/* tp_methods         */	\
	0,														/* tp_members         */	\
	0,														/* tp_getset          */	\
	TEMPLATE_CLASS::getBaseScriptType(),	/* tp_base            */	\
	0,														/* tp_dict            */	\
	0,														/* tp_descr_get       */	\
	0,														/* tp_descr_set       */	\
	TEMPLATE_CLASS::calcDictOffset(),   /* tp_dictoffset      */	\
	(initproc)TEMPLATE_CLASS::_tp_init,	/* tp_init            */	\
	0,														/* tp_alloc           */	\
	TEMPLATE_CLASS::_tp_new,				/* tp_new             */	\
	PyObject_GC_Del,							    /* tp_free            */	\
};				

/* �������ʽ�ĳ�ʼ��һ���ű�ģ�飬 ��һЩ��Ҫ����Ϣ��䵽python��type������ */
#define SCRIPT_INIT(CLASS, CALL, SEQ, MAP, ITER, ITERNEXT)   TEMPLATE_SCRIPT_INIT(;,CLASS, CLASS, CALL, SEQ, MAP, ITER, ITERNEXT)	

#define DECLARE_PY_MOTHOD_ARG0(FUNCNAME)											       \
PyObject* FUNCNAME(void);																				   \
static PyObject*                                                                                                       \
__py_##FUNCNAME(PyObject* self, PyObject* args, PyObject* kwds)                       \
{return static_cast<ThisClass*>(self)->FUNCNAME();}

#define DECLARE_PY_MOTHOD_ARG1(FUNCNAME, ARG_TYPE1)							   \
PyObject* FUNCNAME(PY_METHOD_ARG_##ARG_TYPE1);									   \
static PyObject*                                                                                                       \
__py_##FUNCNAME(PyObject* self, PyObject* args, PyObject* kwds)                       \
{																															   \
	PY_METHOD_ARG_##ARG_TYPE1 arg1;																   \
																															   \
	const uint8 argsSize = 1;																					   \
	uint16 currargsSize = PyTuple_Size(args);															   \
	ThisClass* pobj = static_cast<ThisClass*>(self);													   \
																															   \
	if(currargsSize == argsSize)																				   \
	{																												           \
	   if(!PyArg_ParseTuple(args, PY_METHOD_ARG_##ARG_TYPE1##_PYARGTYPE,	   \
									&arg1))																				   \
	   {																													   \
	   PyErr_Format(PyExc_TypeError,                                                                         \
       "%s: args(%s) is error!\n", __FUNCTION__, #ARG_TYPE1);								       \
	   PyErr_PrintEx(0);																								   \
	   PY_NONE_SAFE_RETURN;																				   \
	   }																													   \
	}																													       \
	else																													   \
	{																														   \
		PyErr_Format(PyExc_AssertionError,                                                                  \
        "%s: args require %d args(%s), gived %d! is script[%s].\n",							       \
		__FUNCTION__, argsSize, #ARG_TYPE1, currargsSize, pobj->scriptName());       \
		PyErr_PrintEx(0);																							   \
		PY_NONE_SAFE_RETURN;																				   \
	}																														   \
	return pobj->FUNCNAME(arg1);																		   \
}																															   

#define DECLARE_PY_MOTHOD_ARG2(FUNCNAME, ARG_TYPE1, ARG_TYPE2)		   \
PyObject* FUNCNAME(PY_METHOD_ARG_##ARG_TYPE1,										   \
                                    PY_METHOD_ARG_##ARG_TYPE2);									   \
static PyObject* __py_##FUNCNAME(PyObject* self,PyObject* args,PyObject* kwds)\
{																															   \
	PY_METHOD_ARG_##ARG_TYPE1##_ARG arg1;													   \
	PY_METHOD_ARG_##ARG_TYPE2##_ARG arg2;													   \
																															   \
	const uint8 argsSize = 2;																					   \
	uint16 currargsSize = PyTuple_Size(args);															   \
	ThisClass* pobj = static_cast<ThisClass*>(self);													   \
																															   \
	if(currargsSize == argsSize)																				   \
	{																														   \
		if(!PyArg_ParseTuple(args,                                                                                \
                                        PY_METHOD_ARG_##ARG_TYPE1##_PYARGTYPE "|"		   \
									    PY_METHOD_ARG_##ARG_TYPE2##_PYARGTYPE,			   \
									    &arg1, &arg2))																   \
		{																										               \
			PyErr_Format(PyExc_TypeError,                                                                     \
                                 "%s: args(%s, %s) is error!\n",                                                  \
								__FUNCTION__, #ARG_TYPE1, #ARG_TYPE2);				               \
			PyErr_PrintEx(0);																						   \
			PY_NONE_SAFE_RETURN;																			   \
		}																													   \
	}																														   \
	else																													   \
	{																														   \
		PyErr_Format(PyExc_AssertionError,                                                                  \
                             "%s: args require %d args(%s, %s), gived %d! is script[%s].\n",	   \
			                 __FUNCTION__, argsSize, #ARG_TYPE1, #ARG_TYPE2,                  \
                             currargsSize, pobj->scriptName());									           \
																															   \
		PyErr_PrintEx(0);																							   \
		PY_NONE_SAFE_RETURN;																				   \
	}																														   \
																															   \
	return pobj->FUNCNAME(arg1, arg2);																   \
}																													

/** ��������ڰ�ȫ�ĵ���һ������ķ��� */
#define InvokeScriptObjectMethodAgrs0(OBJ, METHOT_NAME)							  \
{																										                      \
	if(PyObject_HasAttrString(OBJ, METHOT_NAME))											      \
	{																									                      \
		PyObject* pyResult = PyObject_CallMethod((OBJ), (METHOT_NAME), 			  \
															               const_cast<char*>(""));				  \
		if(pyResult != NULL)																			              \
		Py_DECREF(pyResult);																		              \
		else																							                      \
		PyErr_PrintEx(0);																			                  \
	}																									                      \
}																										

#define InvokeScriptObjectMethodAgrs1(OBJ, METHOT_NAME, FORMAT, ARG1)	 \
{																										                     \
	if(PyObject_HasAttrString(OBJ, METHOT_NAME))												 \
	{																									                     \
		PyObject* pyResult = PyObject_CallMethod((OBJ), 										 \
												                          (METHOT_NAME), 						 \
												                          (FORMAT),									 \
												                          (ARG1));										 \
		if(pyResult != NULL)																			             \
		Py_DECREF(pyResult);																		             \
		else																							                     \
		PyErr_PrintEx(0);																			                 \
	}																									                     \
}																										                     \


#define InvokeScriptObjectMethodAgrs2(OBJ, METHOT_NAME, FORMAT, ARG1, ARG2)	\
{																										                                \
	if(PyObject_HasAttrString(OBJ, METHOT_NAME))														    \
	{																									                                \
		PyObject* pyResult = PyObject_CallMethod((OBJ), 												    \
												                           (METHOT_NAME), 								    \
												                           (FORMAT),												\
												                           (ARG1),													\
												                           (ARG2));													\
		if(pyResult != NULL)																			                        \
		Py_DECREF(pyResult);																		                        \
		else																							                                \
		PyErr_PrintEx(0);																			                            \
	}																									                                \
}																										


#define InvokeScriptObjectMethodAgrs3(OBJ, METHOT_NAME, FORMAT, ARG1, ARG2, ARG3)	\
{																										                                        \
	if(PyObject_HasAttrString(OBJ, METHOT_NAME))														            \
	{																									                                        \
		PyObject* pyResult = PyObject_CallMethod((OBJ), 												            \
												                          (METHOT_NAME), 											\
												                          (FORMAT),												        \
												                          (ARG1),													        \
												                          (ARG2),													        \
												                          (ARG3));													        \
		if(pyResult != NULL)																			                                \
		Py_DECREF(pyResult);																		                                \
		else																							                                        \
		PyErr_PrintEx(0);																			                                    \
	}																									                                        \
}			

ACE_KBE_END_VERSIONED_NAMESPACE_DECL
#include <ace/post.h>
#endif