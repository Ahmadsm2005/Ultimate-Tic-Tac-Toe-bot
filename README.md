# Ultimate-Tic-Tac-Toe-bot
The bot uses Monte Carlo Tree Search to play.
Every turn, the opponent plays row number and column number(-1,-1 if the bot will start instead).
The output will be row number and column number.

Rules:
When a player plays on a small board, he also decides where the next player will be allowed to play: for example, if a player has played in the bottom left square of one of the small boards, the next player will play on the small board located at the bottom left square of the main board.

If a player is sent to a board that is either already won, or full, then that player is allowed to play in any empty square.
