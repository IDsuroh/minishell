Things I (Roh) need to do (for the weekend):

1. Write explanation for;
  a. Tokenization
  b. Error Check
  c. Parsing
  d. Printing logic of Tokenization and Parsing.

2. Expand Environment Variables (T_VAR)

3. Findout what redirections are. (Understand the concept in a deeper scale)

4. Findout what to do after these process.


*Check if string expansion (e.g. $HOME, $USER) happens before tokenization or after.
*What is string expansions and how is it different with environmental variable?


❯ echo "prefix$VARsuffix"
prefix
❯ echo "$VARsuffix"

❯ echo "asdfasdf$VARsuffix"
asdfasdf
❯ echo "asdfasdf$VAR"
asdfasdf
❯ echo "asdfasdfVAR"
asdfasdfVAR
❯ echo "asdfasdf$VAR"
asdfasdf
❯ echo "$VAR"

❯ echo "asdfasdf$HOME"
asdfasdf/home/suroh
❯ echo "asdfasdf$HOMEsuffix"
asdfasdf
❯ echo "asdfasdf$HOME suffix"
asdfasdf/home/suroh suffix
❯ echo asdfasdf$HOME suffix
asdfasdf/home/suroh suffix
❯ echo asdfasdf$HOMEsuffix
asdfasdf
❯ echo asdfasdf$HOME>suffix
❯ echo asdfasdf$HOME>suffix
❯ ls
Desktop    Downloads  Music           Pictures  snap    Templates
Documents  DSDT       norminette-env  Public    suffix  Videos
❯ cat suffix
asdfasdf/home/suroh
❯ rm suffix
❯ echo "asdfasdf$HOME>suffix"
asdfasdf/home/suroh>suffix
❯ echo "asdfasdf$HOMEsuffix"
asdfasdf
❯ echo "asdfasdf$HOME suffix"
asdfasdf/home/suroh suffix
❯ echo "asdfasdf$HOME >suffix"
asdfasdf/home/suroh >suffix
❯ echo "asdfasdf$HOME <suffix"
asdfasdf/home/suroh <suffix
❯ echo "asdfasdf$HOME <<suffix"
asdfasdf/home/suroh <<suffix
❯ echo "asdfasdf$HOME<<suffix"
asdfasdf/home/suroh<<suffix
❯ echo "asdfasdf$HOME>>suffix"
asdfasdf/home/suroh>>suffix
❯ echo "asdfasdf$HOME||suffix"
asdfasdf/home/suroh||suffix
❯ echo "asdfasdf$HOME|suffix"
asdfasdf/home/suroh|suffix
❯ echo "asdfasdf$HOME$suffix"
asdfasdf/home/suroh
❯ echo "asdfasdf$HOME$"suffix""
asdfasdf/home/suroh$suffix
❯ echo "asdfasdf$HOME$"suffix"
dquote> "
asdfasdf/home/suroh$suffix

❯ echo "            asdfasdf$HOME||suffix"
            asdfasdf/home/suroh||suffix
❯ echo "            ||asdfasdf$HOME||suffix"
            ||asdfasdf/home/suroh||suffix
❯ echo "     ||       ||asdfasdf$HOME||suffix"
     ||       ||asdfasdf/home/suroh||suffix
❯ echo      ||       ||asdfasdf$HOME||suffix
zsh: parse error near `||'
❯ echo "     ||       ||asdfasdf$HOME||suffix"
     ||       ||asdfasdf/home/suroh||suffix
❯ echo "  >   ||       ||asdfasdf$HOME||suffix"
  >   ||       ||asdfasdf/home/suroh||suffix
❯ echo "  >   ||   >>    ||asdfasdf$HOME||suffix"
  >   ||   >>    ||asdfasdf/home/suroh||suffix
❯ echo "  >   ||   >>  &&  ||asdfasdf$HOME||suffix"
  >   ||   >>  &&  ||asdfasdf/home/suroh||suffix
❯ echo "aerghadfh  >   ||   >>  &&  ||asdfasdf$HOME||suffix"
aerghadfh  >   ||   >>  &&  ||asdfasdf/home/suroh||suffix
❯ echo "aerghadfh  > $  ||   >>  &&  ||asdfasdf$HOME||suffix"
aerghadfh  > $  ||   >>  &&  ||asdfasdf/home/suroh||suffix
❯ echo "aerghadfh  > $  ||   >>  &&  ||$asdfasdf$HOME||suffix"
aerghadfh  > $  ||   >>  &&  ||/home/suroh||suffix
❯ echo "aerghadfh  > $a  ||   >>  &&  ||$asdfasdf$HOME||suffix"
aerghadfh  >   ||   >>  &&  ||/home/suroh||suffix
❯ echo "aerghadfh  > $a $$ ||   >>  &&  ||$asdfasdf$HOME||suffix"
aerghadfh  >  5244 ||   >>  &&  ||/home/suroh||suffix
❯ echo "aerghadfh  > $a $$$ ||   >>  &&  ||$asdfasdf$HOME||suffix"
aerghadfh  >  5244$ ||   >>  &&  ||/home/suroh||suffix
❯ echo "aerghadfh  > $a $$$ || $  >>  &&  ||$asdfasdf$HOME||suffix"
aerghadfh  >  5244$ || $  >>  &&  ||/home/suroh||suffix
❯ echo "asdfasdf$HOME>suffix"
asdfasdf/home/suroh>suffix
❯ echo "asdf$asdf$HOME>suffix"
asdf/home/suroh>suffix
❯ echo "asdf$asdf$HOME>suffix $"
asdf/home/suroh>suffix $
❯ echo "asdf$asdf$HOME>suffix $ "
asdf/home/suroh>suffix $ 
❯ echo "asdf$asdf$HOME>suffix $ $\"
dquote> 
dquote> \
dquote> "
asdf/home/suroh>suffix $ $"


❯ echo "asdf$asdf$HOME>suffix $ $\"

\
"
❯ echo "asdf$asdf$HOME>suffix $ $a"
asdf/home/suroh>suffix $ 
❯ echo "asdf$asdf$HOME>suffix $ $1"
asdf/home/suroh>suffix $ 
❯ echo "asdf$asdf$HOME>suffix $ $|"
asdf/home/suroh>suffix $ $|
❯ echo "asdf$asdf$HOME>suffix $ $>"
asdf/home/suroh>suffix $ $>
❯ echo "asdf$asdf$HOME>suffix $ $> aerghadfh  > $  ||   >>  &&  ||asdfasdf$HOME||suffix"
asdf/home/suroh>suffix $ $> aerghadfh  > $  ||   >>  &&  ||asdfasdf/home/suroh||suffix
❯  bjm"asdf$asdf$HOME>suffix $ $> aerghadfh  > $  ||   >>  &&  ||asdfasdf$HOME||suffix"
zsh: no such file or directory: bjmasdf/home/suroh>suffix $ $> aerghadfh  > $  ||   >>  &&  ||asdfasdf/home/suroh||suffix
