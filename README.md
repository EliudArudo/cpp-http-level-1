## C++ HTTP Server Template
A Web Server Template built on [Rene Nyffenegger's simple web server](https://github.com/ReneNyffenegger/cpp-webserver).
Currently supports windows only, linux support will be added later.

## Challenge for this
1. GET request to 'http://localhost:8080/' returns JSON
2. In memory database OPS
   * GET -> 
      * Get object using "id" as route param
      ```
      http://localhost:8080/db/?id=1
      ```
      * Get all objects - returns an array
      ```
      http://localhost:8080/db/all
      ```
   * PUT -> Put object using JSON
     * Get all objects
      ```
      http://localhost:8080/db/

      // Request body
        {
            "id": "1",
            "item": "dog"
        }
      ```
   * POST -> Change object already in db
     ```
      http://localhost:8080/db/

      // Request body
        {
            "id": "1",
            "item": "cat"
        }
      ```
   * DELETE -> Delete object using id
     ```
      http://localhost:8080/db/?id=2
     ```
3. DELETE request to remove databases 
 ```
   http://localhost:8080/db/
 ```   

### Running this
```
git clone https://github.com/EliudArudo/cpp-webserver-template.git webserver
cd webserver
./compile.mingw.bat
```

Get the executable from the '/debug' folder

Access the server from 
```
http://localhost:8080/
```

