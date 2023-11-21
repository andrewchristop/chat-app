#!/bin/bash
gcc ~/Documents/chat-app/src/main.c -I /opt/homebrew/opt/openssl@3/include -L /opt/homebrew/opt/openssl@3/lib -lssl -lcrypto
