 #ifndef H_MYREADKEY
 #define H_MYREADKEY


enum keys{L,S,R,T1,I,F5,F6, up, down, lft, rght, enter, other};




int rk_readkey(enum keys* key);
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
int rk_mytermrestore (void);
int rk_mytermsave (const char* fd);

 #endif
