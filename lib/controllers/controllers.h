#include "../webserver/webserver.h"

class Controller
{
public:
  Controller();

  void static Request_Handler(webserver::http_request *);

  void static POST_handler(webserver::http_request *);
  void static GET_handler(webserver::http_request *);
  void static PUT_handler(webserver::http_request *);
  void static DELETE_handler(webserver::http_request *);
  void static Handle_404(webserver::http_request *);
};