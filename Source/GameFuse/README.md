# Implementation Notes

Three main classes are 

- GameFuseUser.h / .cpp
  - Handles specific user actions ( SignUp/In, Add Score/Credits ) 
  - Public functions set InternalResponseManager as the callback and hits UserAPIManager to handle calling the endpoint
  - InternalResponseManager calls internal funcs based on the response's Json data
  - Internal Functions read json objects 
- GameFuseCore.h / .cpp
  - UGameFuseCore::InternalResponseManager orchestrates json to specific function calls
- CoreAPIManager.h / .cpp
  - Actually implements the HTTP calls defining the endpoint and using the ResponseManager to call the callbacks

### API Access Classes
- APIResponseManager.h / .cpp
  - Wrapper class receives the HTTP response and calls the Callback
- UserAPIManager.h / .cpp
  - Actually forms the HTTP Request passed from the publically called function
  - Repeats the same lamba (functor?) for all API endpoint functions

### Overall Notes

- GameFuseUser/Core need to have their signatures fixed/updated in the docs (class methods)
- GameFuseUser/Core both import Serialization, maybe refactor
