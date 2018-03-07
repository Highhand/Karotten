+: White
-: Black
0: Empty
1: Pawn
2: Knight
3: Bishop
4: Rook
5: Queen
6: King


Engine
- CommunicatorUCI
    - Board
    - MoveEvaluator
        - MoveGenerator

# Perft
| Depth | Nodes      | Karotten Nodes |
| ----- |:----------:|:--------------:|
| 0     | 1          | 1              |
| 1     | 20         | 20             |
| 2     | 400        | 400            |
| 3     | 8902       | 8902           |
| 4     | 197,281    | 197,281        |
| 5     | 4,865,609  | 4,865,609      |
