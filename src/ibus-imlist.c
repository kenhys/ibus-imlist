#include <stdio.h>
#include <stdlib.h>
#include <ibus.h>

static gchar *list;

static GOptionEntry entries[] = {
  { "list", 'l', 0, G_OPTION_ARG_NONE, &list,
    "List input method", NULL },
  { NULL }
};

void list_input_method(void)
{
  ibus_init();

  IBusBus *bus = ibus_bus_new();
  g_object_ref_sink(bus);

  IBusConfig *config = ibus_bus_get_config(bus);
  GVariant *variant = NULL;
  variant = ibus_config_get_value(config, "general", "preload-engines");

  GVariantIter iter;
  g_variant_iter_init(&iter, variant);
  g_debug("%d\n",  g_variant_iter_n_children(&iter));
  GVariant *item;
  gsize  size;
  while ((item = g_variant_iter_next_value (&iter)))  {
    g_print("\t%s\n", g_variant_get_string(item, &size));
    g_variant_unref(item);
  }
  g_variant_unref(variant);
}

int main(int argc, char *argv[])
{
  GOptionContext *context;
  GError *error;

  context = g_option_context_new("- IBus input method list utility");
  g_option_context_set_help_enabled(context, TRUE);
  g_option_context_add_main_entries(context, entries, "");
  if (!g_option_context_parse(context, &argc, &argv, &error)) {
    g_print("option parsing failed: %s\n", error->message);
    exit(1);
  }

  if (list) {
    list_input_method();
  } else {
    g_print("%s", g_option_context_get_help(context, TRUE, NULL));
  }
  return 0;
}
