# Mine-Sweeper

GAME DESCRIPTION:
- This game does NOT have a GUI, it can be played via terminals
- The map is static 10x10
- You can set the number of mines either via command line arguments or in the game
- After setting up the mines you can start guessing the coordinates. First part of the coordinate must be a letter from 'A' to 'J' (must be UpperCase) and the second part must be
  a number between 0 and 9.
  So the coordinates must look like this: A0 J8 B5
- Bombs are represented as * character
- You can save the current state if you want. Type "save" instead of a coordinate.
- And if you have already saved a game you can load it at the start of the program

HOW TO:
- install gcc compiler
- open a terminal and type: **gcc main.c functions.c**
- type **a.exe** and the game started

VERY IMPORTANT:
- A lot of words, rows are colorized in the game. Sadly some of the terminals do NOT support this feature. 
  Recommended terminals for example: 
```diff
 Windows terminal (powersell), Ubuntu terminal.
``` 
- If you try to play the game in cmd, you will definitely see quite interesting characters instead of colors.
<br/>
Picture of the Game:

![kép](https://user-images.githubusercontent.com/60004480/175985289-5bad7d2f-ad22-4ea5-924f-7a62d619b302.png)
