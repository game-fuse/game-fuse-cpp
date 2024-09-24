# Implementation Notes

Three main classes are 

- GameFuseUser.h / cpp
- GameFuseCore.h / cpp
  - UGameFuseCore::InternalResponseManager orchestrates json to specific function calls
- CoreAPIManager.h / cpp

(TODO: make these ^ links)

### Overall Notes

-GameFuseUser/Core need to have their signatures fixed/updated in the docs (class methods)
-GameFuseUser/Core both import Serialization, maybe refactor
