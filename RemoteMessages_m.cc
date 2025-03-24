//
// Generated file, do not edit! Created by opp_msgtool 6.1 from RemoteMessages.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "RemoteMessages_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(TaskMessage)

TaskMessage::TaskMessage(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

TaskMessage::TaskMessage(const TaskMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

TaskMessage::~TaskMessage()
{
    delete [] this->arrayData;
}

TaskMessage& TaskMessage::operator=(const TaskMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void TaskMessage::copy(const TaskMessage& other)
{
    this->clientId = other.clientId;
    this->taskId = other.taskId;
    this->subtaskId = other.subtaskId;
    delete [] this->arrayData;
    this->arrayData = (other.arrayData_arraysize==0) ? nullptr : new int[other.arrayData_arraysize];
    arrayData_arraysize = other.arrayData_arraysize;
    for (size_t i = 0; i < arrayData_arraysize; i++) {
        this->arrayData[i] = other.arrayData[i];
    }
}

void TaskMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->clientId);
    doParsimPacking(b,this->taskId);
    doParsimPacking(b,this->subtaskId);
    b->pack(arrayData_arraysize);
    doParsimArrayPacking(b,this->arrayData,arrayData_arraysize);
}

void TaskMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->clientId);
    doParsimUnpacking(b,this->taskId);
    doParsimUnpacking(b,this->subtaskId);
    delete [] this->arrayData;
    b->unpack(arrayData_arraysize);
    if (arrayData_arraysize == 0) {
        this->arrayData = nullptr;
    } else {
        this->arrayData = new int[arrayData_arraysize];
        doParsimArrayUnpacking(b,this->arrayData,arrayData_arraysize);
    }
}

int TaskMessage::getClientId() const
{
    return this->clientId;
}

void TaskMessage::setClientId(int clientId)
{
    this->clientId = clientId;
}

int TaskMessage::getTaskId() const
{
    return this->taskId;
}

void TaskMessage::setTaskId(int taskId)
{
    this->taskId = taskId;
}

int TaskMessage::getSubtaskId() const
{
    return this->subtaskId;
}

void TaskMessage::setSubtaskId(int subtaskId)
{
    this->subtaskId = subtaskId;
}

size_t TaskMessage::getArrayDataArraySize() const
{
    return arrayData_arraysize;
}

int TaskMessage::getArrayData(size_t k) const
{
    if (k >= arrayData_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)arrayData_arraysize, (unsigned long)k);
    return this->arrayData[k];
}

void TaskMessage::setArrayDataArraySize(size_t newSize)
{
    int *arrayData2 = (newSize==0) ? nullptr : new int[newSize];
    size_t minSize = arrayData_arraysize < newSize ? arrayData_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        arrayData2[i] = this->arrayData[i];
    for (size_t i = minSize; i < newSize; i++)
        arrayData2[i] = 0;
    delete [] this->arrayData;
    this->arrayData = arrayData2;
    arrayData_arraysize = newSize;
}

void TaskMessage::setArrayData(size_t k, int arrayData)
{
    if (k >= arrayData_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)arrayData_arraysize, (unsigned long)k);
    this->arrayData[k] = arrayData;
}

void TaskMessage::insertArrayData(size_t k, int arrayData)
{
    if (k > arrayData_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)arrayData_arraysize, (unsigned long)k);
    size_t newSize = arrayData_arraysize + 1;
    int *arrayData2 = new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        arrayData2[i] = this->arrayData[i];
    arrayData2[k] = arrayData;
    for (i = k + 1; i < newSize; i++)
        arrayData2[i] = this->arrayData[i-1];
    delete [] this->arrayData;
    this->arrayData = arrayData2;
    arrayData_arraysize = newSize;
}

void TaskMessage::appendArrayData(int arrayData)
{
    insertArrayData(arrayData_arraysize, arrayData);
}

void TaskMessage::eraseArrayData(size_t k)
{
    if (k >= arrayData_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)arrayData_arraysize, (unsigned long)k);
    size_t newSize = arrayData_arraysize - 1;
    int *arrayData2 = (newSize == 0) ? nullptr : new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        arrayData2[i] = this->arrayData[i];
    for (i = k; i < newSize; i++)
        arrayData2[i] = this->arrayData[i+1];
    delete [] this->arrayData;
    this->arrayData = arrayData2;
    arrayData_arraysize = newSize;
}

class TaskMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_clientId,
        FIELD_taskId,
        FIELD_subtaskId,
        FIELD_arrayData,
    };
  public:
    TaskMessageDescriptor();
    virtual ~TaskMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(TaskMessageDescriptor)

TaskMessageDescriptor::TaskMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(TaskMessage)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

TaskMessageDescriptor::~TaskMessageDescriptor()
{
    delete[] propertyNames;
}

bool TaskMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TaskMessage *>(obj)!=nullptr;
}

const char **TaskMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TaskMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TaskMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int TaskMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_clientId
        FD_ISEDITABLE,    // FIELD_taskId
        FD_ISEDITABLE,    // FIELD_subtaskId
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_arrayData
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *TaskMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "clientId",
        "taskId",
        "subtaskId",
        "arrayData",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int TaskMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "clientId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "taskId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "subtaskId") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "arrayData") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *TaskMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_clientId
        "int",    // FIELD_taskId
        "int",    // FIELD_subtaskId
        "int",    // FIELD_arrayData
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **TaskMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *TaskMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int TaskMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TaskMessage *pp = omnetpp::fromAnyPtr<TaskMessage>(object); (void)pp;
    switch (field) {
        case FIELD_arrayData: return pp->getArrayDataArraySize();
        default: return 0;
    }
}

void TaskMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TaskMessage *pp = omnetpp::fromAnyPtr<TaskMessage>(object); (void)pp;
    switch (field) {
        case FIELD_arrayData: pp->setArrayDataArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TaskMessage'", field);
    }
}

const char *TaskMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TaskMessage *pp = omnetpp::fromAnyPtr<TaskMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TaskMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TaskMessage *pp = omnetpp::fromAnyPtr<TaskMessage>(object); (void)pp;
    switch (field) {
        case FIELD_clientId: return long2string(pp->getClientId());
        case FIELD_taskId: return long2string(pp->getTaskId());
        case FIELD_subtaskId: return long2string(pp->getSubtaskId());
        case FIELD_arrayData: return long2string(pp->getArrayData(i));
        default: return "";
    }
}

void TaskMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TaskMessage *pp = omnetpp::fromAnyPtr<TaskMessage>(object); (void)pp;
    switch (field) {
        case FIELD_clientId: pp->setClientId(string2long(value)); break;
        case FIELD_taskId: pp->setTaskId(string2long(value)); break;
        case FIELD_subtaskId: pp->setSubtaskId(string2long(value)); break;
        case FIELD_arrayData: pp->setArrayData(i,string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TaskMessage'", field);
    }
}

omnetpp::cValue TaskMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TaskMessage *pp = omnetpp::fromAnyPtr<TaskMessage>(object); (void)pp;
    switch (field) {
        case FIELD_clientId: return pp->getClientId();
        case FIELD_taskId: return pp->getTaskId();
        case FIELD_subtaskId: return pp->getSubtaskId();
        case FIELD_arrayData: return pp->getArrayData(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TaskMessage' as cValue -- field index out of range?", field);
    }
}

void TaskMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TaskMessage *pp = omnetpp::fromAnyPtr<TaskMessage>(object); (void)pp;
    switch (field) {
        case FIELD_clientId: pp->setClientId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_taskId: pp->setTaskId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_subtaskId: pp->setSubtaskId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_arrayData: pp->setArrayData(i,omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TaskMessage'", field);
    }
}

const char *TaskMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr TaskMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TaskMessage *pp = omnetpp::fromAnyPtr<TaskMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TaskMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TaskMessage *pp = omnetpp::fromAnyPtr<TaskMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TaskMessage'", field);
    }
}

Register_Class(ResultMessage)

ResultMessage::ResultMessage(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

ResultMessage::ResultMessage(const ResultMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

ResultMessage::~ResultMessage()
{
}

ResultMessage& ResultMessage::operator=(const ResultMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void ResultMessage::copy(const ResultMessage& other)
{
    this->clientId = other.clientId;
    this->taskId = other.taskId;
    this->subtaskId = other.subtaskId;
    this->result = other.result;
    this->isHonest_ = other.isHonest_;
}

void ResultMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->clientId);
    doParsimPacking(b,this->taskId);
    doParsimPacking(b,this->subtaskId);
    doParsimPacking(b,this->result);
    doParsimPacking(b,this->isHonest_);
}

void ResultMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->clientId);
    doParsimUnpacking(b,this->taskId);
    doParsimUnpacking(b,this->subtaskId);
    doParsimUnpacking(b,this->result);
    doParsimUnpacking(b,this->isHonest_);
}

int ResultMessage::getClientId() const
{
    return this->clientId;
}

void ResultMessage::setClientId(int clientId)
{
    this->clientId = clientId;
}

int ResultMessage::getTaskId() const
{
    return this->taskId;
}

void ResultMessage::setTaskId(int taskId)
{
    this->taskId = taskId;
}

int ResultMessage::getSubtaskId() const
{
    return this->subtaskId;
}

void ResultMessage::setSubtaskId(int subtaskId)
{
    this->subtaskId = subtaskId;
}

int ResultMessage::getResult() const
{
    return this->result;
}

void ResultMessage::setResult(int result)
{
    this->result = result;
}

bool ResultMessage::isHonest() const
{
    return this->isHonest_;
}

void ResultMessage::setIsHonest(bool isHonest)
{
    this->isHonest_ = isHonest;
}

class ResultMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_clientId,
        FIELD_taskId,
        FIELD_subtaskId,
        FIELD_result,
        FIELD_isHonest,
    };
  public:
    ResultMessageDescriptor();
    virtual ~ResultMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(ResultMessageDescriptor)

ResultMessageDescriptor::ResultMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(ResultMessage)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

ResultMessageDescriptor::~ResultMessageDescriptor()
{
    delete[] propertyNames;
}

bool ResultMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ResultMessage *>(obj)!=nullptr;
}

const char **ResultMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ResultMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ResultMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int ResultMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_clientId
        FD_ISEDITABLE,    // FIELD_taskId
        FD_ISEDITABLE,    // FIELD_subtaskId
        FD_ISEDITABLE,    // FIELD_result
        FD_ISEDITABLE,    // FIELD_isHonest
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *ResultMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "clientId",
        "taskId",
        "subtaskId",
        "result",
        "isHonest",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int ResultMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "clientId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "taskId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "subtaskId") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "result") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "isHonest") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *ResultMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_clientId
        "int",    // FIELD_taskId
        "int",    // FIELD_subtaskId
        "int",    // FIELD_result
        "bool",    // FIELD_isHonest
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **ResultMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ResultMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ResultMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ResultMessage *pp = omnetpp::fromAnyPtr<ResultMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ResultMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ResultMessage *pp = omnetpp::fromAnyPtr<ResultMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ResultMessage'", field);
    }
}

const char *ResultMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ResultMessage *pp = omnetpp::fromAnyPtr<ResultMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ResultMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ResultMessage *pp = omnetpp::fromAnyPtr<ResultMessage>(object); (void)pp;
    switch (field) {
        case FIELD_clientId: return long2string(pp->getClientId());
        case FIELD_taskId: return long2string(pp->getTaskId());
        case FIELD_subtaskId: return long2string(pp->getSubtaskId());
        case FIELD_result: return long2string(pp->getResult());
        case FIELD_isHonest: return bool2string(pp->isHonest());
        default: return "";
    }
}

void ResultMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ResultMessage *pp = omnetpp::fromAnyPtr<ResultMessage>(object); (void)pp;
    switch (field) {
        case FIELD_clientId: pp->setClientId(string2long(value)); break;
        case FIELD_taskId: pp->setTaskId(string2long(value)); break;
        case FIELD_subtaskId: pp->setSubtaskId(string2long(value)); break;
        case FIELD_result: pp->setResult(string2long(value)); break;
        case FIELD_isHonest: pp->setIsHonest(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ResultMessage'", field);
    }
}

omnetpp::cValue ResultMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ResultMessage *pp = omnetpp::fromAnyPtr<ResultMessage>(object); (void)pp;
    switch (field) {
        case FIELD_clientId: return pp->getClientId();
        case FIELD_taskId: return pp->getTaskId();
        case FIELD_subtaskId: return pp->getSubtaskId();
        case FIELD_result: return pp->getResult();
        case FIELD_isHonest: return pp->isHonest();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ResultMessage' as cValue -- field index out of range?", field);
    }
}

void ResultMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ResultMessage *pp = omnetpp::fromAnyPtr<ResultMessage>(object); (void)pp;
    switch (field) {
        case FIELD_clientId: pp->setClientId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_taskId: pp->setTaskId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_subtaskId: pp->setSubtaskId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_result: pp->setResult(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_isHonest: pp->setIsHonest(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ResultMessage'", field);
    }
}

const char *ResultMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr ResultMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ResultMessage *pp = omnetpp::fromAnyPtr<ResultMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ResultMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ResultMessage *pp = omnetpp::fromAnyPtr<ResultMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ResultMessage'", field);
    }
}

Register_Class(GossipMessage)

GossipMessage::GossipMessage(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

GossipMessage::GossipMessage(const GossipMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

GossipMessage::~GossipMessage()
{
}

GossipMessage& GossipMessage::operator=(const GossipMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void GossipMessage::copy(const GossipMessage& other)
{
    this->content = other.content;
    this->timestamp = other.timestamp;
    this->sourceId = other.sourceId;
}

void GossipMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->content);
    doParsimPacking(b,this->timestamp);
    doParsimPacking(b,this->sourceId);
}

void GossipMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->content);
    doParsimUnpacking(b,this->timestamp);
    doParsimUnpacking(b,this->sourceId);
}

const char * GossipMessage::getContent() const
{
    return this->content.c_str();
}

void GossipMessage::setContent(const char * content)
{
    this->content = content;
}

int GossipMessage::getTimestamp() const
{
    return this->timestamp;
}

void GossipMessage::setTimestamp(int timestamp)
{
    this->timestamp = timestamp;
}

int GossipMessage::getSourceId() const
{
    return this->sourceId;
}

void GossipMessage::setSourceId(int sourceId)
{
    this->sourceId = sourceId;
}

class GossipMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_content,
        FIELD_timestamp,
        FIELD_sourceId,
    };
  public:
    GossipMessageDescriptor();
    virtual ~GossipMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(GossipMessageDescriptor)

GossipMessageDescriptor::GossipMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(GossipMessage)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

GossipMessageDescriptor::~GossipMessageDescriptor()
{
    delete[] propertyNames;
}

bool GossipMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GossipMessage *>(obj)!=nullptr;
}

const char **GossipMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GossipMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GossipMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int GossipMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_content
        FD_ISEDITABLE,    // FIELD_timestamp
        FD_ISEDITABLE,    // FIELD_sourceId
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *GossipMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "content",
        "timestamp",
        "sourceId",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int GossipMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "content") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sourceId") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *GossipMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_content
        "int",    // FIELD_timestamp
        "int",    // FIELD_sourceId
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **GossipMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GossipMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GossipMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GossipMessage *pp = omnetpp::fromAnyPtr<GossipMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void GossipMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GossipMessage *pp = omnetpp::fromAnyPtr<GossipMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GossipMessage'", field);
    }
}

const char *GossipMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GossipMessage *pp = omnetpp::fromAnyPtr<GossipMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GossipMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GossipMessage *pp = omnetpp::fromAnyPtr<GossipMessage>(object); (void)pp;
    switch (field) {
        case FIELD_content: return oppstring2string(pp->getContent());
        case FIELD_timestamp: return long2string(pp->getTimestamp());
        case FIELD_sourceId: return long2string(pp->getSourceId());
        default: return "";
    }
}

void GossipMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GossipMessage *pp = omnetpp::fromAnyPtr<GossipMessage>(object); (void)pp;
    switch (field) {
        case FIELD_content: pp->setContent((value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2long(value)); break;
        case FIELD_sourceId: pp->setSourceId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GossipMessage'", field);
    }
}

omnetpp::cValue GossipMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GossipMessage *pp = omnetpp::fromAnyPtr<GossipMessage>(object); (void)pp;
    switch (field) {
        case FIELD_content: return pp->getContent();
        case FIELD_timestamp: return pp->getTimestamp();
        case FIELD_sourceId: return pp->getSourceId();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GossipMessage' as cValue -- field index out of range?", field);
    }
}

void GossipMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GossipMessage *pp = omnetpp::fromAnyPtr<GossipMessage>(object); (void)pp;
    switch (field) {
        case FIELD_content: pp->setContent(value.stringValue()); break;
        case FIELD_timestamp: pp->setTimestamp(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_sourceId: pp->setSourceId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GossipMessage'", field);
    }
}

const char *GossipMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr GossipMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GossipMessage *pp = omnetpp::fromAnyPtr<GossipMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GossipMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GossipMessage *pp = omnetpp::fromAnyPtr<GossipMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GossipMessage'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

