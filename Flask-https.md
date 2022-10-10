# Running Your Flask Application Over `HTTPS`

## Requirements

[`SOURCE`](https://blog.miguelgrinberg.com/post/running-your-flask-application-over-https)

```bash
python -m pip install Flask flask_cors pyopenssl
```

## The Simplest Way To Do It

- Use `Dummy certificate`to quickly serve an application over HTTPS without having to mess with certificates.

- Add ssl_context='adhoc' to your app.run() call.

- New certificate will be generated each time the server runs.

- The browser does not eliminate the security warnings.

<details>
    <summary>EXAMPLE CODE!</summary>

```python
from flask import Flask
from flask_cors import CORS, cross_origin

app = Flask(__name__)
CORS(app, support_credentials=True)

@app.route("/")
@cross_origin(supports_credentials=True)
def hello_world():
    return "<p>Hello, World!</p>"

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=6262, ssl_context='adhoc')
```

</details>

## Self-Signed Certificates

- Generate self-signed certificates easily from the command line.

```bash
openssl req -x509 -newkey rsa:4096 -nodes -out cert.pem -keyout key.pem -days 365
```

<details>
    <summary>EXAMPLE CODE!</summary>

```python
from flask import Flask
from flask_cors import CORS, cross_origin

app = Flask(__name__)
CORS(app, support_credentials=True)

@app.route("/")
@cross_origin(supports_credentials=True)
def hello_world():
    return "<p>Hello, World!</p>"

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=6262, ssl_context=('cert.pem', 'key.pem'))
```

</details>

## Using free CA with `Let's Encrypt`.

```bash
sudo apt install software-properties-common
sudo add-apt-repository ppa:certbot/certbot
sudo apt update
sudo apt install certbot
```

```bash
sudo certbot certonly --webroot -w /var/www/example -d example.com
```

```bash
sudo certbot renew
```
