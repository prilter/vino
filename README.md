# Vino  
Vino - mix of vim and nano text editors.  
  
# Branch info  
This branch was made because I want to make project more "truly". The main branch differs from this one at the moment only in the programming language. This README.md was written by Vino(C branch).  
  
# Main differents  
1) Written by C  
2) Use glibc with termios.h instead of ncurses.h  
3) Added modes(like in VIM)  
  
# Bugs  
1) I do not recommend to make long lines(this can break your cursor)  
2) Use only english keyboard language(others do not supported)  
3) You cannot use ~ in INSERT mode  
  
# Installation guide  
For sudo users:  
```bash
git clone https://github.com/prilter/vino/tree/C
cd vino
sudo make install
```  
  
For doas users:  
```bash
git clone https://github.com/prilter/vino/tree/C
cd vino
doas make install
```  
Also you can disable arrows if set USE_ARROWS to zero in src/appvars.h  
  
# How to quit  
Press C-q(your mode does not matter)  
For now exist autosaving  

