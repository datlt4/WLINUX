# SSL Certificates for Web Developers

[__*COURSE*__](https://www.linkedin.com/learning/ssl-certificates-for-web-developers/why-ssl-certificates-are-essential-for-every-website)

## What is SSL Certificate

- Triggers the "little padlock" or green bar in a browser.

- Use `HTTPS` for secure communication.

- Certifies the ownership of a public key.

- Used for encrypting data sent between a browser and a remote server.

- `SSL`: Secure Sockets Layer.

- Cryptographic protocol for communication security.

- TLS: Transport Layer Security

- Certificates are not dependent on the protocol

    > The certificates is just certifying the public key and 2 protocols (`SSL` and `TLS`) use that public key while they communicate.
    >> So it doesn't affected.
    >>> So if a website use `TLS` --> It have `SSL` certificate

## Handshakes and Cryptography

### Symmetric key Crytpography

- Encrypt data using a password

    > Take some data, take password.
    >> Put it into an algorithm.
    >>> Get encrypted data that cant't be read.

- Decrypt data using the same password.

    > Take same password.
    >> Put it into an algorithm.
    >>> Get decrypted data --> readable.

- Symmetric key = Same key.

### Public key Cryptography

- Asymmetric cryptography.

    > asymmetric password - They are not same anymore.

- Pair of mathematically linked numbers.

    > 2 linked numbers derived from multiple prime numbers together.
    >> We refer to them as the public key and the private key.

- Public key and Private key.

- Private key can be shared widely.

- Data encrypted with the public key can be decrypted using private key.

### SSL / TLS handshake

- A browser sends a request to a secure server.

- The server send back its SSL certificate, which includes the public key and other data about the server's identiry.

- The browser confirms the SSL certificate is valid.

    > The browser decide the public key is something that it can trust.
    >> Look and see if the expiration data has passed yet.</br>
    >> It can also look at who issued the certificate to see if that's some one that we trust.</br>
    >> If browser decides we can trust.
    >>> then it can use that public key.

- The browser encrypts a very long password using the public key and send it to the server.

    > Then that can be transmitted securely, over the internet.

- The server decrypts the data using its private key and retrieves the password.

- The server and browser bot posses the same password.

- They use the shared password to encrypt all future communications with symmetric key cryptography.

### Why they switch to symmetric-key cryptography, when we were doing so well with the public-key cryptography?

> Because it allow us to have the benefit of both technology.

1. Public-key cryptography.

- Private communication in public.

- Slow algorithms.

2. Symmetric-key cryptography.

- Difficult to send key publicly.

    > Make it hard to be able to share data anonymously over the Internet.

- Fast algorithms.

### Certificate and Encryption

- SSL certificate certifies ownership of public key.

- Public key is used to exchange a password in public.

- Password used to encrypt all data between browser and server.

- Password is temporary and not used.

