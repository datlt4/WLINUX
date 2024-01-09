# Push Docker Images to GitHub Container Registry

1. Create Personal Access Token

   - `Profile` > `Setting` > `Developer Settings` > `Personal access tokens` > `Tokens (classic)` > `Generate new token` > `Generate new token (classic)`.
   - Input `token name` > Select `Expiration` > Select scopes: ☑`write:packages` ☑`read:packages` ☑`delete:packages`.
   - Click `Generate token`.

2. Login Github container registry endpoint

   ```bash
   docker login --username <github username> --password <generated PAT> ghcr.io
   ```

3. Push docker image

   ```bash
   docker build . -r ghcr.io/<github username>/<docker image name>:TAG
   docker push ghcr.io/<github username>/<docker image name>:TAG
   ```
