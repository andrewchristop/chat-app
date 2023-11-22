#!/bin/bash
gcc ~/Documents/chat-app/tests/test_crypto.c -I /opt/homebrew/opt/openssl@3/include -L /opt/homebrew/opt/openssl@3/lib -lssl -lcrypto

