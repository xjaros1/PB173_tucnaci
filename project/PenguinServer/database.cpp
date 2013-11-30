#include "database.h"

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
    std::string statement1("select * from user where UserName= ?");
    std::string statement2("insert into user (UserName, password) VALUES(?,?)");
    int res = sqlite3_prepare_v2(connection, statement1.c_str(), statement1.length()+1, &getByName, NULL );
    if(res != SQLITE_OK)
    {
        throw SqlException("The statement was not created");
    }
    res = sqlite3_prepare_v2(connection, statement2.c_str(), statement2.length()+1, &include, NULL);
    if(res != SQLITE_OK)
    {
        throw SqlException("The statement was not created");
    }
}

SqlConnection::ContainedData SqlConnection::getUserByName(std::string username)
{
    QMutexLocker l(&mutex);
    sqlite3_bind_text(getByName, 1, username.c_str(), username.length(), NULL);
    if(sqlite3_step(getByName) !=SQLITE_ROW)
    {
        sqlite3_reset(getByName);
        throw SqlException("The message is not in the db");
    }
    ContainedData t;
    t.id = sqlite3_column_int(getByName, 0);

    const char * t1, *t2;
    t1 = (char*)sqlite3_column_text(getByName,1);
    t2 = (char*)sqlite3_column_text(getByName,2);

    std::string name(t1), pass(t2);

    t.name = name;
    t.password = pass;
    sqlite3_finalize(getByName);

    return t;

}

bool SqlConnection::insertUser(std::string name, std::string password)
{
    QMutexLocker  lock(&mutex);
    sqlite3_bind_text(include, 1, name.c_str(), name.length(), NULL);
    sqlite3_bind_text(include, 2, password.c_str(), password.length(), NULL);

    sqlite3_step(include);
    sqlite3_finalize(include);
    sqlite3_reset(include);
    return true;
}

int SqlConnection::ContainedData::getID() const
{
    return id;
}

const std::string & SqlConnection::ContainedData::getName() const
{
    return name;
}

const  std::string &SqlConnection::ContainedData::getPass() const
{
    return password;
}

