#include "database.h"

namespace PenguinServer
{

char * getAscii85(const char * data, size_t len)
{
    if(len<=0) return NULL;
    size_t len_t = len+4;
    char * d = (char*) malloc(sizeof(char)*len_t);
    strncpy(d, data,len);
    while(len%4!=0)
    {
        d[len] = '\0';
        len++;
    }

    char * data_ret = (char*) malloc(sizeof(char) * ((5*len)/4)+1);
    size_t ptr = 0;
    for(unsigned int i=0; i < (len/4); i++)
    {
        int j = 4*i;
        quint32 bits = 0;
        for(int k = 0; k<4; k++)
        {
           bits = bits << 8;
           bits |= d[j+k];
        }
        while(bits!=0)
        {
            data_ret[ptr] = (bits%85)+33;
            bits = bits/85;
            ptr++;
        }
    }
    free(d);
    data_ret[ptr] = '\0';
    return data_ret;

}

char * getPlainfrom85(const char * data, int len)
{
    if(len%5!=0) return NULL;
    char * ret = (char*) malloc(sizeof(char)* (4*(len/5)+1));
    size_t ptr = 0;
    for(int i = 0; i< len/5; i++)
    {
        int j = 5*i;
        quint32 t = 0;
        for(int k = 4; k>= 0 ; k--)
        {
            t *= 85;
            t += data[j+k] -33 ;

        }
        for(int l = 3; l>=0; l--)
        {
            ret[ptr+l] = t%(1<<8);
            t = t >> 8;
        }
        ptr+=4;

    }
    ret[ptr+1] = '\0';
    return ret;
}


SqlConnection::SqlConnection()
{
    if(sqlite3_open_v2("users.db", &connection, SQLITE_OPEN_READWRITE, NULL) != SQLITE_OK)
    {
        throw SqlException("Unable to open database");
    }

}

bool SqlConnection::existsUser(const QString &name)
{
    std::string statement1("select * from Users where UserName= ?");
    sqlite3_stmt * stat;
    int res = sqlite3_prepare_v2(connection, statement1.c_str(), statement1.length()+1, &stat, NULL );
    if(res != SQLITE_OK)
    {
        throw SqlException("Nepodarilo se vytvorit statement");
    }
    std::string a(name.toStdString());
    sqlite3_bind_text(stat, 1, a.c_str(), a.length() +1, NULL);
    QMutexLocker l(&mutex);
    qDebug("The locked searching");

    if(sqlite3_step(stat) != SQLITE_ROW)
    {
        sqlite3_finalize(getByName);
        return false;
    }
    //sqlite3_finalize(getByName);
    sqlite3_finalize(getByName);
    return true;
}

SqlConnection::ContainedData SqlConnection::getUserByName(const QString &username)
{
    std::string statement1("select * from Users where UserName= ?");
    sqlite3_stmt * stat;
    int res = sqlite3_prepare_v2(connection, statement1.c_str(), statement1.length()+1, &stat, NULL );
    if(res != SQLITE_OK)
    {
        throw SqlException("Nepodarilo se vytvorit statement");
    }
    std::string a(username.toStdString());
    sqlite3_bind_text(stat, 1, a.c_str(), a.length() +1, NULL);
    QMutexLocker l(&mutex);


    if(sqlite3_step(stat) !=SQLITE_ROW)
    {
        sqlite3_finalize(stat);
        throw SqlException("The user is not in the db");
    }
    ContainedData t;
    t.id = sqlite3_column_int(stat, 0);

    char * t1, *t2, *t3;
    t1 = (char*)sqlite3_column_text(stat,1);
    t2 = (char*)sqlite3_column_text(stat,2);
    t3 = (char*)sqlite3_column_text(stat,3);


    QString name(t1), pass(t2), salt(t3);

    t.name = name;
    t.password = pass;
    t.salt = salt;
    //free(t1);
    //free(t2);
    //free(t3);
    sqlite3_finalize(stat);


    return t;

}

bool SqlConnection::insertUser(const QString &name, const QString &password, const QString &salt)
{
    std::string statement2("insert into Users (UserName, PasswordSHA2, Salt) VALUES(?,?,?)");
    sqlite3_stmt * stat;
    int res = sqlite3_prepare_v2(connection, statement2.c_str(), statement2.length()+1, &stat, NULL );
    if(res != SQLITE_OK)
    {
        throw SqlException("The statement2 was not created");
    }
    std::string a(name.toStdString()), b(password.toStdString()), c(salt.toStdString());
    sqlite3_bind_text(stat, 1, a.c_str(), a.length()+1, NULL);
    sqlite3_bind_text(stat, 2, b.c_str(), b.length()+1, NULL);
    sqlite3_bind_text(stat, 3, c.c_str(), c.length()+1, NULL);

    QMutexLocker  lock(&mutex);

    sqlite3_step(stat);
    sqlite3_finalize(stat);

    //sqlite3_reset(include);
    return true;
}

int SqlConnection::ContainedData::getID() const
{
    return id;
}

const QString & SqlConnection::ContainedData::getName() const
{
    return name;
}

const  QString & SqlConnection::ContainedData::getPass() const
{
    return password;
}

const QString& SqlConnection::ContainedData::getSalt() const
{
    return salt;
}

}
