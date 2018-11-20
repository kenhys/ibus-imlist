# ibus-imlist

`ibus-imlist` is a sample program to show or change input method list from command line.
In such a case, it is common to use `dconf` command.
But if you want to set Mozc and English keyboard layout with `dconf`, you need to type:

```
dconf write /desktop/ibus/general/preload-engines "['mozc-jp', 'xkb:us:eng']"
```

Then if you want to back to Mozc and Japanese keyboard layout with `dconf`, you need to type:

```
dconf write /desktop/ibus/general/preload-engines "['mozc-jp', 'xkb:jp:jpn']"
```

It is a bit complicated, so I wrote a demo program which use IBus API.

# Usage

## How to show input methods?

Use `-l` option to list input methods which is enabled.

    % ibus-imlist -l

## How to change the order of input methods?

Use `-s` option with input methods list to change the order.

    % ibus-imlist -s mozc-jp,us
