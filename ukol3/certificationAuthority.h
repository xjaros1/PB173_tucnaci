/* 
 * File:   certificationAuthority.h
 * Author: mirek
 *
 * Created on 9. říjen 2013, 19:36
 */

#ifndef CERTIFICATIONAUTHORITY_H
#define	CERTIFICATIONAUTHORITY_H

/**
 * 
 * @\brief  Represents connectivity to client.
 * 
 */
class ClientConnection
{
public:
    
    
    /**
     * \brief Verifies the incomming connection.
     * 
     * \param clientKey The RSA client Public key
     * 
     * \return 0 if client was verified else fail code
     *
     */
    virtual int verifyConnection(RSAPublicKey clientKey) = 0;
    
    /**
     * \brief Accepts incomming connection and sends the acceptacion message
     * 
     * \param CAKey private key of certification Authority
     * \param clientKey public key of connected client
     * 
     * \return 0 if succes (the message was send) else fail code
     */
    virtual int acceptConnection(RSAPrivateKey CAkey, RSAPublicKey clientKey) = 0;
    
    /**
     * \brief Gets last request from client
     * 
     * \return Message which was send to CA
     */
    virtual string getClientRequest() = 0;//Mozna spise zapojit eventy
    
    /**
     * \brief Sents message to client
     * 
     * \return 0 on succes else fail code 
     */
    virtual int postClientResponse(string message) = 0;
    
    
    /**
     * 
     * \brief Ends connection to client
     * 
     */
    virtual void closeConnection() = 0;
    
    /**
     * 
     * \brief Sends request to client to resend last recieved message
     * 
     * Can be used if the message was broken or CA was unnable to verify signature
     * 
     * \param CAkey private RSA key of CA (for signature)
     * \param clientKey public key of client (for encryption)
     * 
     * \return 0 if succes else fail code
     */
    virtual int resendLastMessageRequest(RSAPrivateKey CAkey, RSAPublicKey clientKey) = 0;
    

};

#endif	/* CERTIFICATIONAUTHORITY_H */

