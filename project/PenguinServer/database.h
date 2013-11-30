#ifndef DATABASE_H
#define DATABASE_H

#include <polarssl/sha2.h>
#include <sqlite3.h>
#include <QMutex>

char * getAscii85(const char * data, size_t len);

char * getPlainfrom85(const char * data, int len);

class SqlConnection
{
public:

    class ContainedData;
    class SqlException;

    SqlConnection();


    ContainedData getUserByName(std::string username);

    bool insertUser(std::string name, std::string password);


    class ContainedData
    {
        ContainedData() { }
    public:

        ContainedData(const char name[20],const char pass[20]);

        int getID() const;

        const std::string & getName() const;

        const std::string & getPass() const;

        friend class SqlConnection;

    private:

        int id;
        std::string  name;
        std::string  password;
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




#endif // SQLCONNECTION_H
