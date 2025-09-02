# [ICPC 2019 WF] Checks Post Facto

## 题目描述

游戏在一个 $8 \times 8$ 的方格棋盘的深色方格上进行。有两名玩家，黑方和白方，他们轮流移动他们的棋子（所有黑方的棋子都是黑色的，所有白方的棋子都是白色的）。每个棋子占据一个单独的深色方格，可以是**兵**或**王**。一个回合包括选择一个棋子并以以下两种方式之一移动它：

1. 将其**斜着**移动到一个相邻的未占用的深色方格，如图 (a) 所示。这被称为**简单移动**。兵只能沿向前的两种方向移动（对于黑方是朝下，对于白方是朝上）。如果棋子是王，它可以在所有四个斜方向移动。

2. 跳过对方的棋子到达空地，并吃掉对方的子。允许移动的方向与第一条相同。然后，玩家可以重复此步骤，继续使用相同的棋子跳。这样一个或多个跳的序列称为**跳跃移动**。图 (b) 展示了由三个跳跃组成的跳跃移动。

如果在玩家回合开始时有一个跳跃移动可用，他们必须进行跳跃，并且不能停止使用该棋子跳跃，直到它没有更多可能的跳跃。他们可以自由选择使用哪个棋子进行跳跃，以及在有多个可能性的情况下选择在哪里跳跃。在图 (b) 中，黑方不能进行任何其他移动。

如果一个兵达到其玩家的最远一行（即，一个黑子达到底行或一个白子达到顶行），它将变成同色的王（称为**晋升**），然后**回合结束**。这意味着一个兵不能在同一回合中被晋升然后以王的身份继续倒退跳跃。

给定一系列移动，请找到一个初始棋局，使得可以从该棋局开始按顺序合法进行这些移动。此棋局可能不能在底行有黑子或在顶行有白子，因为它们可能已经被晋升为王。你只需要确保上述规则被遵守；不需要确保这个棋局在实际跳棋游戏中是可达的。

## 样例 #1

### 输入

```
W 3
21-17
13x22x31x24
19x28```

### 输出

```
-b-.-.-. -b-.-.-.
.-.-.-.- .-.-.-.-
-.-.-.-. -.-.-.-.
B-.-w-.- .-.-w-.-
-.-.-W-. -.-.-.-.
w-.-.-.- .-.-.-.-
-.-w-w-. -.-.-.-W
.-.-.-.- .-.-.-.-```

## 样例 #2

### 输入

```
B 5
2-7
9x2
32-27
2x11x18
5-9```

### 输出

```
-.-b-.-W -.-.-.-W
b-b-.-.- .-.-.-.-
-w-.-.-. -b-.-.-.
B-w-b-.- B-w-.-.-
-.-.-.-. -.-W-.-.
.-.-.-.- .-.-.-.-
-.-.-.-. -.-.-B-.
.-.-.-B- .-.-.-.-```

# 题解

## 作者：CashCollectFactory (赞：3)

### 题目大意

有一种叫 Checkers 的棋类游戏，有一系列棋谱，要通过棋谱还原出**原来的可能的局面**。 规则如下： 
1. 棋子分为两种，小兵和大王，兵只能往前斜走，王能往回走，隔着对方的子跳过去能吃棋。
2. 兵到了对面底线能晋升王。 
3. 如果当前局面能吃子，必须先吃子。

（~~原本题目翻译里面什么白人男子、黑人国王的机翻实在让人迷茫~~）

### 火力全开的大模拟解法
题目算法不难，难处在于实现上有**特别多细节需要注意**。

首先我们需要**正序遍历**一遍棋谱，把棋谱上移动了的棋子但棋盘上没有的摆上去。摆的时候，**优先摆小兵**（因为移动方向只有2个，后面检查 jump 优先的时候更方便），不符合规则才换成国王，并且把 jump 中被吃掉的子也补上，同时也要处理吃子和晋升的情况。

接下来是**检查局面是否符合 jump 优先的规则**，再次正序跑一遍棋谱，如果有不符合的情况，需要用一些从头到尾未被移动过的棋子去挡住这个可能 jump 的路线。由于不确定这个位置是放黑棋还是白棋，所以**两种情况都要递归地试一下**。 由于棋盘只有 $32$ 个位置，问题规模较小，所以实际上对时间复杂度的影响不大。

还有一些具体的实现方法，就都放在代码中啦。

### 代码时间（~~码丑勿喷~~）

代码中没有用什么特别的卡常手段，但目前已经是全谷最优解啦，卡常大师可以试试再优化一手哦~
```
#include <bits/stdc++.h>
using namespace std;
char startPlayer;
vector<char> moveType;
vector<vector<int>> moves;
inline char opp(char player) { return player == 'W' ? 'B' : 'W'; }
inline int sqX(int sq) { return (sq-1)%4*2 + 1-((sq-1)/4)%2; }
inline int sqY(int sq) { return (sq-1)/4; }
pair<vector<string>, vector<string>> doit(vector<string> start) {
	vector<string> board = start;
	char player = startPlayer;
	for (int i = 0; i < moves.size(); i++, player = opp(player))
		for (int j = 0; j+1 < moves[i].size(); j++) {
			int sx = sqX(moves[i][j  ]), sy = sqY(moves[i][j]);
			int ex = sqX(moves[i][j+1]), ey = sqY(moves[i][j+1]);
			bool promoted = ((player == 'W' && ey == 0) || (player == 'B' && ey == 7)) && islower(board[sy][sx]);

			if (moveType[i] == '-') {
				for (int y = 0; y < 8; y++)
					for (int x = 0; x < 8; x++) if (toupper(board[y][x]) == player)
							for (int dx = -1; dx <= 1; dx += 2)
								for (int dy = -1; dy <= 1; dy += 2) {
									if (board[y][x] == 'w' && dy == 1) continue;
									if (board[y][x] == 'b' && dy == -1) continue;
									int x2 = x+dx+dx, y2 = y+dy+dy;
									if (x2 < 0 || x2 >= 8 || y2 < 0 || y2 >= 8) continue;
									if (toupper(board[y+dy][x+dx]) != opp(player)) continue;
									if (board[y2][x2] == '.')
										return {{}, {}};  
									if (board[y2][x2] == '?') {
										start[y2][x2] = (y2 == 0) ? 'W' : 'w';
										auto ret = doit(start);
										if (ret.first.size())
											return ret;
										start[y2][x2] = (y2 == 7) ? 'B' : 'b';
										return doit(start);
									}
								}
			}
			board[ey][ex] = board[sy][sx];
			if (promoted) board[ey][ex] = toupper(board[ey][ex]);
			board[sy][sx] = '.';
			if (moveType[i] == 'x') {
				int mx = (sx+ex)/2, my = (sy+ey)/2;
				board[my][mx] = '.';
				if (j+2 == moves[i].size() && !promoted) {
					int x = ex, y = ey;
					for (int dx = -1; dx <= 1; dx += 2)
						for (int dy = -1; dy <= 1; dy += 2) {
							if (board[y][x] == 'w' && dy == 1) continue;
							if (board[y][x] == 'b' && dy == -1) continue;
							int x2 = x+dx+dx, y2 = y+dy+dy;
							if (x2 < 0 || x2 >= 8 || y2 < 0 || y2 >= 8) continue;
							if (toupper(board[y+dy][x+dx]) != opp(player)) continue;
							if (board[y2][x2] == '.')
								return {{}, {}}; 
							if (board[y2][x2] == '?') {
								start[y2][x2] = (y2 == 0) ? 'W' : 'w';
								auto ret = doit(start);
								if (ret.first.size())
									return ret;
								start[y2][x2] = (y2 == 7) ? 'B' : 'b';
								return doit(start);
							}
						}
				}
			}
		}
	return {start, board};
}

int main() {
	int N, first = 1;
	while (cin >> startPlayer >> N) {
		moveType = vector<char>(N);
		moves = vector<vector<int>>(N);
		for (int i = 0; i < N; i++) {
			string s;
			cin >> s;
			int j = 0;
			for (;;) {
				int sq = s[j]-'0';
				if (j+1 < s.size() && isdigit(s[j+1])) sq = 10*sq + s[++j]-'0';
				moves[i].push_back(sq);
				if (++j == s.size()) break;
				moveType[i] = s[j++];
			}
		}
		vector<string> start(8, "????????"), board = start;
		char player = startPlayer;
		vector<vector<int>> startX(8), startY(8);
		for (int y = 0; y < 8; y++)
			for (int x = 0; x < 8; x++) {
				startX[y].push_back(x);
				startY[y].push_back(y);
			}
		for (int i = 0; i < moves.size(); i++, player = opp(player))
			for (int j = 0; j+1 < moves[i].size(); j++) {
				int sx = sqX(moves[i][j  ]), sy = sqY(moves[i][j  ]);
				int ex = sqX(moves[i][j+1]), ey = sqY(moves[i][j+1]);
				bool promoted = ((player == 'W' && ey == 0) || (player == 'B' && ey == 7));
				if (board[sy][sx] == '?') {
					board[sy][sx] = start[sy][sx] = tolower(player); 
				}
				if (board[ey][ex] == '?') {
					board[ey][ex] = start[ey][ex] = '.';
				}
				assert(toupper(board[sy][sx]) == player);
				assert(board[ey][ex] == '.');
				if (((player == 'W') ^ (ey < sy)) && islower(board[sy][sx])) {
					board[sy][sx] = start[startY[sy][sx]][startX[sy][sx]] = toupper(board[sy][sx]);
				}
				board[ey][ex] = board[sy][sx];
				if (promoted && j+2 == moves[i].size()) board[ey][ex] = toupper(board[ey][ex]);
				board[sy][sx] = '.';
				startX[ey][ex] = startX[sy][sx];
				startY[ey][ex] = startY[sy][sx];
				if (moveType[i] == 'x') {
					int mx = (sx+ex)/2, my = (sy+ey)/2;
					if (board[my][mx] == '?') {
						board[my][mx] = start[my][mx] = tolower(opp(player));
					}
					assert(toupper(board[my][mx]) == opp(player));
					board[my][mx] = '.';
				}
			}
		auto ret = doit(start);
		assert(ret.first.size()); 
		if (!first) cout << endl;
		first = false;
		for (int y = 0; y < 8; y++)
			for (int x = y%2; x < 8; x += 2) {
				ret.first[y][x] = ret.second[y][x] = '-';
			}
		for (int y = 0; y < 8; y++)
			for (int x = 1-y%2; x < 8; x += 2) {
				if (ret.first[y][x] == '?') ret.first[y][x] = '.';
				if (ret.second[y][x] == '?') ret.second[y][x] = '.';
			}
		for (int y = 0; y < 8; y++) cout << ret.first[y] << ' ' << ret.second[y] << endl;
	}
	return 0;
}
```

补充一句，本代码需要使用 C++11 以上版本才可以正常编译，只因里面用了“ auto ”这个新东西~

---

