#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "service-test.h"

#define DBUS_MACHINELEARNING_SERVICE_INTERFACE  "org.tizen.machinelearning.service"

GMainLoop *loop;
static GDBusConnection *g_dbus_sys_conn[2] = {NULL, };
static MachinelearningService *g_gdbus_instance = NULL;


MachinelearningService *gdbus_get_instance_service (void)
{
  return machinelearning_service_skeleton_new ();
}

int service_module_probe ()
{
  int ret = 0;

  g_gdbus_instance = gdbus_get_instance_service();
  if (g_gdbus_instance == NULL) {
    fprintf(stderr, "Failed to get dbus instance for %s interface\n",
      DBUS_MACHINELEARNING_SERVICE_INTERFACE);
    return -1;
  }

  return 0;
}

void init_modules ()
{
  // call probe & init
  service_module_probe();
}

int gdbus_get_system_connection (int idx)
{
  GError *error = NULL;
  g_dbus_sys_conn[idx] = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);

  if (g_dbus_sys_conn[idx] == NULL) {
    fprintf(stderr, "Failed to get SYSTEM_BUS\n");
    return -1;
  }

  fprintf(stderr, "Success to get SYSTEM_BUS\n");
  return 0;
}

#if 0
guint owner_id;
GMainLoop *loop;

static gboolean
handler_add (MachinelearningService *interface,/
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
#endif


int main (int argc, char* argv[])
{
  loop = g_main_loop_new (NULL, FALSE);

  gdbus_get_system_connection (0);

  g_main_loop_unref (loop);
#if 0
  owner_id = g_bus_own_name (G_BUS_TYPE_SYSTEM, 
                          "org.tizen.machinelearning.service",
                          G_BUS_NAME_OWNER_FLAGS_NONE, NULL,
                          on_bus_acquired, NULL, NULL, NULL);
  if (owner_id == 0) {
    fprintf(stderr, "Failed to get gdbus own name\n");
    exit (-1);
  }

  g_main_loop_run (loop);

  g_main_loop_unref (loop);
#endif

  return 0;
}





