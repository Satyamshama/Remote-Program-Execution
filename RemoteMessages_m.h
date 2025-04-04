//
// Generated file, do not edit! Created by opp_msgtool 6.1 from RemoteMessages.msg.
//

#ifndef __REMOTEMESSAGES_M_H
#define __REMOTEMESSAGES_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0601
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class TaskMessage;
class ResultMessage;
class GossipMessage;
/**
 * Class generated from <tt>RemoteMessages.msg:1</tt> by opp_msgtool.
 * <pre>
 * packet TaskMessage
 * {
 *     int clientId;
 *     int taskId;
 *     int subtaskId;
 *     int arrayData[];
 * }
 * </pre>
 */
class TaskMessage : public ::omnetpp::cPacket
{
  protected:
    int clientId = 0;
    int taskId = 0;
    int subtaskId = 0;
    int *arrayData = nullptr;
    size_t arrayData_arraysize = 0;

  private:
    void copy(const TaskMessage& other);

  protected:
    bool operator==(const TaskMessage&) = delete;

  public:
    TaskMessage(const char *name=nullptr, short kind=0);
    TaskMessage(const TaskMessage& other);
    virtual ~TaskMessage();
    TaskMessage& operator=(const TaskMessage& other);
    virtual TaskMessage *dup() const override {return new TaskMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getClientId() const;
    virtual void setClientId(int clientId);

    virtual int getTaskId() const;
    virtual void setTaskId(int taskId);

    virtual int getSubtaskId() const;
    virtual void setSubtaskId(int subtaskId);

    virtual void setArrayDataArraySize(size_t size);
    virtual size_t getArrayDataArraySize() const;
    virtual int getArrayData(size_t k) const;
    virtual void setArrayData(size_t k, int arrayData);
    virtual void insertArrayData(size_t k, int arrayData);
    [[deprecated]] void insertArrayData(int arrayData) {appendArrayData(arrayData);}
    virtual void appendArrayData(int arrayData);
    virtual void eraseArrayData(size_t k);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TaskMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TaskMessage& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>RemoteMessages.msg:8</tt> by opp_msgtool.
 * <pre>
 * packet ResultMessage
 * {
 *     int clientId;
 *     int taskId;
 *     int subtaskId;
 *     int result;
 *     bool isHonest;
 * }
 * </pre>
 */
class ResultMessage : public ::omnetpp::cPacket
{
  protected:
    int clientId = 0;
    int taskId = 0;
    int subtaskId = 0;
    int result = 0;
    bool isHonest_ = false;

  private:
    void copy(const ResultMessage& other);

  protected:
    bool operator==(const ResultMessage&) = delete;

  public:
    ResultMessage(const char *name=nullptr, short kind=0);
    ResultMessage(const ResultMessage& other);
    virtual ~ResultMessage();
    ResultMessage& operator=(const ResultMessage& other);
    virtual ResultMessage *dup() const override {return new ResultMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getClientId() const;
    virtual void setClientId(int clientId);

    virtual int getTaskId() const;
    virtual void setTaskId(int taskId);

    virtual int getSubtaskId() const;
    virtual void setSubtaskId(int subtaskId);

    virtual int getResult() const;
    virtual void setResult(int result);

    virtual bool isHonest() const;
    virtual void setIsHonest(bool isHonest);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ResultMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ResultMessage& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>RemoteMessages.msg:16</tt> by opp_msgtool.
 * <pre>
 * packet GossipMessage
 * {
 *     string content;
 *     int timestamp;
 *     int sourceId;
 * }
 * </pre>
 */
class GossipMessage : public ::omnetpp::cPacket
{
  protected:
    omnetpp::opp_string content;
    int timestamp = 0;
    int sourceId = 0;

  private:
    void copy(const GossipMessage& other);

  protected:
    bool operator==(const GossipMessage&) = delete;

  public:
    GossipMessage(const char *name=nullptr, short kind=0);
    GossipMessage(const GossipMessage& other);
    virtual ~GossipMessage();
    GossipMessage& operator=(const GossipMessage& other);
    virtual GossipMessage *dup() const override {return new GossipMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const char * getContent() const;
    virtual void setContent(const char * content);

    virtual int getTimestamp() const;
    virtual void setTimestamp(int timestamp);

    virtual int getSourceId() const;
    virtual void setSourceId(int sourceId);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const GossipMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, GossipMessage& obj) {obj.parsimUnpack(b);}


namespace omnetpp {

template<> inline TaskMessage *fromAnyPtr(any_ptr ptr) { return check_and_cast<TaskMessage*>(ptr.get<cObject>()); }
template<> inline ResultMessage *fromAnyPtr(any_ptr ptr) { return check_and_cast<ResultMessage*>(ptr.get<cObject>()); }
template<> inline GossipMessage *fromAnyPtr(any_ptr ptr) { return check_and_cast<GossipMessage*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __REMOTEMESSAGES_M_H

