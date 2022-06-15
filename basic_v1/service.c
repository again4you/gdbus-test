#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "service-test.h"

guint owner_id;
GMainLoop *loop;

static gboolean
handler_add (MachinelearningService *interface,
            GDBusMethodInvocation *invocation,
            int left, int right, gpointer user_data)
{
  int result = left + right;
  fprintf(stderr, "handler_add(): %d + %d = %d\n", left, right, result);

  machinelearning_service_complete_add (interface, invocation, result);

  return TRUE;
}


static void
on_bus_acquired (GDBusConnection *connection,
                const gchar *name,
                gpointer user_data)
{
  MachinelearningService *interface;
  gboolean ret;
  GError *error = NULL;

  fprintf(stderr, "Acquire name: %s\n", name);

  interface = machinelearning_service_skeleton_new ();

  g_signal_connect (interface, "handle-add",
                  G_CALLBACK (handler_add), NULL);

  ret = g_dbus_interface_skeleton_export(
    G_DBUS_INTERFACE_SKELETON(interface),
    connection,
    "/Org/Tizen/MachineLearning/Service", &error);
  if (!ret) {
    fprintf (stderr, "Failed to export: \n");
    g_free (error);
  }
}


int main (int argc, char* argv[])
{
  loop = g_main_loop_new (NULL, FALSE);

  owner_id = g_bus_own_name (G_BUS_TYPE_SESSION, 
                          "org.tizen.machinelearning.service",
                          G_BUS_NAME_OWNER_FLAGS_NONE, NULL,
                          on_bus_acquired, NULL, NULL, NULL);
  if (owner_id == 0) {
    fprintf(stderr, "Failed to get gdbus own name\n");
    exit (-1);
  }

  g_main_loop_run (loop);

  g_main_loop_unref (loop);

  return 0;
}





