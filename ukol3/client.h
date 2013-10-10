/* 
 * File:   client.h
 * Author: xjaros1
 *
 * Created on 9. říjen 2013, 19:35
 */

#ifndef CLIENT_H
#define	CLIENT_H


class ConectionToClient
{
    virtual initializeConnection() = 0;
    
    /*
        Tady si nejsem moc jiste co s tim, takze bych to dnes probral a potom dopsal.
        Bude to tu trochu slozitejsi.
    
    */
    
};

/**
 * 
 * \brief Represents connection to Certification Authority
 * 
 * Interface represents funcionality for connection to server.
 * 
 */
class CAConnection
{
    
    /**
     * \brief Starts connection to CA server
     * 
     * \param myKey Clients private key
     * \param CAkey Public key of Certification Authority
     * 
     * \return 0 if success else fail code
     */
    virtual int initializeConnection(RSAPrivateKey myKey, RSAPublicKey CAkey) = 0;
    
    /**
     * \brief Sents request to CA. 
     * 
     * This can be used for request for public key of some other
     * client
     * 
     * \param message Message to be sent
     */
    virtual int sentRequestToCA(byte[] message) = 0;
    
    /**
     * \brief Get last response of CA.
     * 
     * \return last message recieved from CA
     */
    virtual byte[] getCAResponse() = 0;
    
    /**
     * \brief Requests resend of last recieved message
     * 
     * Thi can be used when last message was corrupted.
     */
    virtual int requestResendLastMessage(RSAPrivateKey myKey, RSAPublicKey CAkey) = 0;
    
    
    /**
     * \brief Ends connection to CA server
     */
    virtual void closeConnection() = 0;
    

    
};

/**
 * \brief Class represents the interface to comunication to server
 * 
 * It can be very unified because the messages are very specified.
 */
class ServerConnection
{
    
    /**
     * \brief Requests server for https (or other) certificate
     * 
     * \return 0 on succes else fail code
     */
    virtual int requestServerCertificate() = 0;
    
    /**
     * \brief Starts Connection to server
     * 
     * \return 0 on succes else fail code
     */
    virtual int initializeConnection() = 0;
    
    /**
     * \brief Requests list of clients which are online
     * 
     * \return 0 on succes else fail code
     */
    virtual int requestForListOfClients() = 0;
    
    /**
     * \brief Requests the connection to Client
     * 
     * \param c TODO
     * \return 0 on succes else fail code
     */
    virtual int requestForClientConnection(Client c) = 0;
    
    /**
     * \brief gets the connection to requested client
     * 
     * \return The Connection to client on succes else NULL
     */
    virtual ConnectionToClient* getConnectionClientREsponse() = 0;
    
    /**
     * \brief Gets new request from client to connection.
     * 
     * 
     */
    virtual ConnectionToClient* getConnectionToClientRequest = 0;
    
    /**
     * \brief Get last Clients response
     * 
     * \return List of clients which was connected in last request or null on fail
     */
     virtual vector<Client>* getClientsResponse() = 0;
    
    /**
     * \brief Registers new user in the system
     * 
     * \return 0 on succes else fail code
     */
    virtual int registerAsNewClientRequest() = 0;
    
    //TODO
    //Needed to make some interface for entering and getting informations
    
    /**
     * \brief Closes connection to server
     */
    virtual void closeConnection() = 0;
};
#endif	/* CLIENT_H */

