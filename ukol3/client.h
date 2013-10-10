/* 
 * File:   client.h
 * Author: mirek
 *
 * Created on 9. říjen 2013, 19:35
 */

#ifndef CLIENT_H
#define	CLIENT_H


class ConectionToClient
{
    
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

class ServerConnection
{
    
    
};
#endif	/* CLIENT_H */

