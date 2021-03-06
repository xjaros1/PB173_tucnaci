#ifndef MESSAGEENVELOP_HPP
#define MESSAGEENVELOP_HPP


#define PING 0
#define OK 1
#define SEND_LOGIN_TO_SERVER 2
#define REQUEST_CLIENT_LIST_FROM_SERVER 3
#define REQUEST_CALL_TO_CLIENT_FROM_SERVER 4
#define SEND_CLIENT_LIST_TO_CLIENT 5
#define SEND_INCOMMING_CALL_TO_CLIENT 6

#define END_OF_CALL_TO_CLIENT 7
#define END_OF_CALL_FROM_CLIENT 8
#define LOGOUT_TO_SERVER 9


#define SEND_SUCCESS_RESPONSE_TO_COMMUNICATION 10
#define SEND_DENIED_RESPONSE_TO_COMMUNICATION 11
#define SEND_LOGOUT_REQUEST 12
#define SEND_LOGOUT_RESPONSE 13

#define REGISTER_TO_SERVER 14
#define REGISTER_APROOVED 15
#define REGISTER_DENIED 16

#define ERROR_SERVER_RESPONSE 666

#define CLIENT_PEARL_HARBOR_PORT 41712
#define SERVER_VIETNAM_WAR_PORT  27173


#include <QtNetwork>
#include <exception>


class MessageEnvelop; //forward declaration

class MessageException: public std::exception
{
    std::string message;

public:

    MessageException(std::string message):message(message)
    { }

    virtual ~MessageException() throw()
    { }

    virtual const char * what() const throw()
    {
        return message.c_str();
    }

};




/**
 * @brief operator <<
 *        Overloading operator for
 * @param out Output steam where will be wrote data
 * @param wr Envelop to read from
 * @return Refrence to stream
 */
QDataStream& operator <<(QDataStream & out, const MessageEnvelop & wr);

/**
 * @brief operator >>
 * @param in
 * @param out
 * @return
 */
QDataStream& operator >>(QDataStream& in, MessageEnvelop & out)  throw (MessageException);




/**
 * @brief The MessageEnvelop class
 */
class MessageEnvelop
{

public:

    MessageEnvelop(qint16 reason = 0);

    /**
     * @brief operator <<
     * @return
     */
    friend QDataStream& operator <<(QDataStream&, const MessageEnvelop&);
    /**
     * @brief operator >>
     * @return
     */
    friend QDataStream& operator >>(QDataStream&, MessageEnvelop &) throw (MessageException);

    /**
     * @brief getAddr
     * @return
     */
    QHostAddress getAddr() const;

    /**
     * @brief getPort
     * @return
     */
    qint16 getPort() const;

    /**
     * @brief getList
     * @return
     */
    QList<QString> getList() const;

    /**
     * @brief getNamea
     * @return
     */
    QString getName() const;

    QString getPassword() const;

    /**
     * @brief getRequestType
     * @return
     */
    qint16 getRequestType() const;

    /**
     * @brief setAddr
     * @param addr
     */
    void setAddr(QHostAddress addr);

    /**
     * @brief setPort
     * @param port
     */
    void setPort(qint16 port);

    /**
     * @brief setClients
     * @param list
     */
    void setClients(const QList<QString> &list);

    /**
     * @brief setName
     * @param name
     */
    void setName(const QString & name);

    void setPassword(const QString &password);




private:

    qint16 messageType;
    QHostAddress addr;
    qint16 port;
    QList<QString> clients;
    QString name;
    QString password;






};


#endif // MESSAGEENVELOP_HPP
