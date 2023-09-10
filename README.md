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

## Credits

- [`telebot`](https://github.com/smartnode/telebot) C Library for Telegram bot
  API - by [@smartnode](https://github.com/smartnode)
