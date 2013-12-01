#ifndef DATABASE_H
#define DATABASE_H


#include <sqlite3.h>
#include <QMutex>
#include <QString>

namespace PenguinServer
{
char * getAscii85(const char * data, size_t len);

char * getPlainfrom85(const char * data, int len);

class SqlConnection
{
public:

    class ContainedData;
    class SqlException;

    SqlConnection();


    ContainedData getUserByName(const QString & username);

    bool insertUser(const QString &name, const QString &password, const QString &salt);

    bool existsUser(const QString & name);


    class ContainedData
    {
        ContainedData() { }
    public:

        ContainedData(const char name[20],const char pass[20]);

        int getID() const;

        const QString & getName() const;

        const QString & getPass() const;

        const QString & getSalt() const;

        friend class SqlConnection;

    private:

        int id;
        QString  name;
        QString  password;
        QString  salt;
    };

    class SqlException: public std::exception
    {
        std::string message;

    public:

        SqlException(std::string message): message(message)
        {
        }


        virtual ~SqlException() throw () {}

        virtual const char * what() const throw()
        {
            return message.c_str();
        }
    };


private:

    QMutex mutex;

    sqlite3 * connection;

    sqlite3_stmt * include;

    sqlite3_stmt * getByName;

    sqlite3_stmt * getAllInfo;

};

}


#endif // SQLCONNECTION_H
