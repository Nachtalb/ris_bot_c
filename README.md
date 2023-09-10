# Telegram Reverse Image Search Bot 🕵️‍♂️🔍

A rewrite of my
[reverse image search](https://github.com/Nachtalb/reverse_image_search_bot) bot
in pure C.

This repos is more used for actually learning C while rewriting the bot. In the
end the code should come over into the repo linked above.

## Installation

```sh
git clone --recursive https://github.com/Nachtalb/ris_bot_c
cd ris_bot_c
./build.sh  # basically just does cmake / make
```

## Usage

Get a Telegram Bot API token by talking to [@BotFather](https://t.me/BotFather).

```sh
echo "YOUR_API_TOKEN" > .token
./run.sh
```

## Developing

I use [uncrustify](https://github.com/uncrustify/uncrustify) for formatting my
code. As there is no [coc.nvim](https://github.com/neoclide/coc.nvim) plugin for
it, I started making one. But don\'t quote me on that (I loose my patience with
JS very quickly).

In the meantime I added a `.vimrc` to the folder which can be loaded in vim with
`:so .vimrc` which will do these things:

- run cmake when `CMakeLists.txt` is saved
- compile the app when `main.c` is saved
- run `uncrustify` on all `*.c` files

If you also want to do something in here and don't use Vim just use the command:

```sh
uncrustify -c .uncrustify.cfg src/*.c --replace
```

## Credits

- [`telebot`](https://github.com/smartnode/telebot) C Library for Telegram bot
  API - by [@smartnode](https://github.com/smartnode)
