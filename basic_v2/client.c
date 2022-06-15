#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "service-test.h"

int main (int argc, char* argv[])
{
  MachinelearningService *proxy;
  GError *error = NULL;
  gint result;
  int lvalue, rvalue;
  lvalue = atoi (argv[1]);
  rvalue = atoi (argv[2]);


  fprintf(stderr, "Client started!\n");
  proxy = machinelearning_service_proxy_new_for_bus_sync (G_BUS_TYPE_SESSION,
                                                      G_DBUS_PROXY_FLAGS_NONE,
                                                      "org.tizen.machinelearning.service",
                                                      "/Org/Tizen/MachineLearning/Service",
                                                      NULL, &error);
  if (error != NULL) {
    fprintf(stderr, "Failed to machinelearning_service_calc_proxy_new_sync(): %s\n", error->message);
    g_error_free (error);
    return -1;
  }

  machinelearning_service_call_add_sync (proxy, lvalue, rvalue, &result, NULL, &error);
  if (error != NULL) {
    fprintf(stderr, "Failed to machinelearning_service_calc_call_add_sync(): %s\n", error->message);
    g_error_free (error);
    return -1;
  }

  fprintf(stderr, "result: %d\n", result);

  g_object_unref (proxy);
  
  return 0;
}
