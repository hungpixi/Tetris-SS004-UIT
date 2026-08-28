@echo off
title UIT - SS004: Tro Choi Tetris (Nhom 01)
cls
:: Tu dong go bo chan bao mat Mark-of-the-Web cua Windows neu co
powershell -NoProfile -Command "Unblock-File -Path '%~dp0Tetris_Game_v1.0.exe'" >nul 2>&1

:: Chay tro choi Tetris
"%~dp0Tetris_Game_v1.0.exe"
