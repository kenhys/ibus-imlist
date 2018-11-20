#include <stdio.h>
#include <stdlib.h>
#include <ibus.h>
#include <glib.h>

static gchar *list;
static gchar *setlist;

static GOptionEntry entries[] = {
  { "list", 'l', 0, G_OPTION_ARG_NONE, &list,
    "List input method", NULL },
  { "set", 's', 0, G_OPTION_ARG_STRING, &setlist,
    "Set input method list separated by ',' for multiple IM", NULL },
  { NULL }
};

void list_input_method(IBusConfig *config)
{
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

void set_input_method(IBusConfig *config)
{
  GVariantBuilder *builder;
  GVariant *variant;
  builder = g_variant_builder_new(G_VARIANT_TYPE ("as"));
  gchar **items = g_strsplit(setlist, ",", -1);
  gint i = 0;
  while (items[i]) {
    g_debug("%s\n", items[i]);
    if (!g_strcmp0(items[i], "us")) {
      g_variant_builder_add(builder, "s", "xkb:us::eng");
    } else if (!g_strcmp0(items[i], "jp")) {
      g_variant_builder_add(builder, "s", "xkb:jp::jpn");
    } else {
      g_variant_builder_add(builder, "s", items[i]);
    }
    i++;
  }
  g_strfreev(items);
  variant = g_variant_new ("as", builder);
  g_variant_builder_unref (builder);
  ibus_config_set_value(config, "general", "preload-engines", variant);
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

  if (list || setlist) {
    ibus_init();

    IBusBus *bus = ibus_bus_new();
    g_object_ref_sink(bus);

    IBusConfig *config = ibus_bus_get_config(bus);
    if (list) {
      list_input_method(config);
    } else if (setlist) {
      set_input_method(config);
    }
  } else {
    g_print("%s", g_option_context_get_help(context, TRUE, NULL));
  }
  return 0;
}
