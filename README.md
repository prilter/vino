# Vino  
Vino - mix of vi and nano text editors.  
  
# Branch info  
This branch was made because I want to make project more "truly". The main branch differs from this one at the moment only in the programming language. This README.md was written by Vino(C branch).  
  
# Update report  
1) Fixed bug with G(console) when your cursor was righter then line  
2) Fixed bug with dd(console) when your cursor was righter then line  
3) Added welcome message  
4) Added dgg and dG(console mode)  
5) Added replace mode(r and R in console mode)  
6) Added dw and db  
7) Added w and b  
8) New command to clone repository: "git clone -b C --single-branch https://github.com/prilter/vino"  
  
  
# Bugs  
1) I do not recommend to make long lines(this can break your cursor)  
2) Use only english keyboard language(others do not supported)  
3) You cannot use ~ in INSERT mode  
  
# Installation guide  
For sudo users:  
```bash
git clone -b C --single-branch https://github.com/prilter/vino
cd vino
sudo make install
```  
  
For doas users:  
```bash
git clone -b C --single-branch https://github.com/prilter/vino
cd vino
doas make install
```  
Also you can disable arrows if set USE_ARROWS to zero in src/appvars.h  
  
# How to quit  
Press C-q(your mode does not matter)  
For now exist autosaving  

