# Tic-Tac-Toe

## 题目背景

两头熊在玩一个游戏。

这个游戏的棋盘是由9个大方格排成$3\*3$的形式，每个大方格中有9个小方格，也是排成$3\*3$的形式。一个熊执x棋，一个执o棋。第一步由执x棋的熊下，可以下在任意一个小方格中，然后从第二步开始，上一个熊把棋下在的小方格在它所属的$3\*3$小方格中的对应位置，这头熊需要下在3\*3的大方格的对应位置大方格中的9个小方格中的一个。比如上一头熊下到了(6,4)(6,4)位置,(6,4)(6,4)位属于中间的那个大方格，在中间那个大方格的9个小方格中属于左下位，下一步就必须下到9个大方格的左下位的那个大方格中的9个小方格中的一个(样例1)。但是如果这9个小方格已经都被下过棋子了，那么就可以从其他地方任选一个小格子下棋(样例2)。

给定一个棋盘，上面有当前已经下完的棋子，再给出最后一步的坐标，要求在棋盘上下一步可以下的位置上打出"!"(无引号)

## 题目描述

Two bears are playing tic-tac-toe via mail. It's boring for them to play usual tic-tac-toe game, so they are a playing modified version of this game. Here are its rules.

The game is played on the following field.

 ![](http://espresso.codeforces.com/9f2cb44894dfaba91b9e381419482b55cfe9ff63.png)Players are making moves by turns. At first move a player can put his chip in any cell of any small field. For following moves, there are some restrictions: if during last move the opposite player put his chip to cell with coordinates $ (x_{l},y_{l}) $ in some small field, the next move should be done in one of the cells of the small field with coordinates $ (x_{l},y_{l}) $ . For example, if in the first move a player puts his chip to lower left cell of central field, then the second player on his next move should put his chip into some cell of lower left field (pay attention to the first test case). If there are no free cells in the required field, the player can put his chip to any empty cell on any field.

You are given current state of the game and coordinates of cell in which the last move was done. You should find all cells in which the current player can put his chip.

A hare works as a postman in the forest, he likes to foul bears. Sometimes he changes the game field a bit, so the current state of the game could be unreachable. However, after his changes the cell where the last move was done is not empty. You don't need to find if the state is unreachable or not, just output possible next moves according to the rules.

## 说明/提示

In the first test case the first player made a move to lower left cell of central field, so the second player can put a chip only to cells of lower left field.

In the second test case the last move was done to upper left cell of lower central field, however all cells in upper left field are occupied, so the second player can put his chip to any empty cell.

In the third test case the last move was done to central cell of central field, so current player can put his chip to any cell of central field, which is already occupied, so he can move anywhere. Pay attention that this state of the game is unreachable.

## 样例 #1

### 输入

```
... ... ...
... ... ...
... ... ...

... ... ...
... ... ...
... x.. ...

... ... ...
... ... ...
... ... ...
6 4
```

### 输出

```
... ... ... 
... ... ... 
... ... ... 

... ... ... 
... ... ... 
... x.. ... 

!!! ... ... 
!!! ... ... 
!!! ... ... 

```

## 样例 #2

### 输入

```
xoo x.. x..
ooo ... ...
ooo ... ...

x.. x.. x..
... ... ...
... ... ...

x.. x.. x..
... ... ...
... ... ...
7 4
```

### 输出

```
xoo x!! x!! 
ooo !!! !!! 
ooo !!! !!! 

x!! x!! x!! 
!!! !!! !!! 
!!! !!! !!! 

x!! x!! x!! 
!!! !!! !!! 
!!! !!! !!! 

```

## 样例 #3

### 输入

```
o.. ... ...
... ... ...
... ... ...

... xxx ...
... xox ...
... ooo ...

... ... ...
... ... ...
... ... ...
5 5
```

### 输出

```
o!! !!! !!! 
!!! !!! !!! 
!!! !!! !!! 

!!! xxx !!! 
!!! xox !!! 
!!! ooo !!! 

!!! !!! !!! 
!!! !!! !!! 
!!! !!! !!! 

```

# 题解

## 作者：EdenSky (赞：4)

# [CF907B Tic-Tac-Toe](https://www.luogu.com.cn/problem/CF907B)
- [或许更好的阅读体验](https://www.cnblogs.com/wanguan/p/17066196.html)

## 正文

设数组 $c_{x,y,i,j}$ 代表 $(x,y)$ 位置的大格子中 $(i,j)$ 位置的小格子。

很显然，输入中字符的输入顺序是要调整的，实际的顺序是 $x,i,y,j$。

对于输入的 $x_0,y_0$，只要对 3 取模（若整除则结果为 3）即可得到它对应的大格子的位置。

详见代码：

```cpp
#include<iostream>
#define g(a) (a)%3==0?3:(a)%3//对3取模
using namespace std;
char c[4][4][4][4]; int x,y;
int main(){
  for(int x=1;x<=3;x++)
    for(int i=1;i<=3;i++)//输入
      for(int y=1;y<=3;y++)
        for(int j=1;j<=3;j++)
          cin>>c[x][y][i][j];
  cin>>x>>y; x=g(x),y=g(y);
  bool is_empty=true;//对应大方块是否为空
  for(int i=1;i<=3;i++)
    for(int j=1;j<=3;j++)
      if(c[x][y][i][j]=='.')
        is_empty=false,
        c[x][y][i][j]='!';
  if(is_empty)
    for(int x=1;x<=3;x++){
      for(int i=1;i<=3;i++){
        for(int y=1;y<=3;y++){
          for(int j=1;j<=3;j++)
            if(c[x][y][i][j]=='.')
              cout<<'!';
            else cout<<c[x][y][i][j];
          cout<<' ';}
        cout<<'\n';}
      cout<<'\n';}
  else
    for(int x=1;x<=3;x++){
      for(int i=1;i<=3;i++){
        for(int y=1;y<=3;y++){
          for(int j=1;j<=3;j++)
            cout<<c[x][y][i][j];
          cout<<' ';}
        cout<<'\n';}
      cout<<'\n';}
}

```

[完结！！](https://www.luogu.com.cn/record/100187130)

---

## 作者：Tjaweiof (赞：2)

# CF907B 题解
[题目传送门](https://www.luogu.com.cn/problem/CF907B)

思路：模拟。找出第二个人要放的大格，判断是否有空位，如果有则把那个大格里的所有 `.` 都改成 `!`，如果没有则把所有 `.` 都改成 `!` 即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
char a[4][4][4][4];
bool f;
int x, y;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for (int n = 1; n <= 3; n++){
		for (int i = 1; i <= 3; i++){
			for (int m = 1; m <= 3; m++){
				for (int j = 1; j <= 3; j++){
					cin >> a[n][m][i][j];
				}
			}
		}
	}
	cin >> x >> y;
	x %= 3;
	y %= 3;
	if (!x){
		x = 3;
	}
	if (!y){
		y = 3;
	}
	for (int i = 1; i <= 3; i++){
		for (int j = 1; j <= 3; j++){
			if (a[x][y][i][j] == '.'){
				f = true;
			}
		}
	}
	if (f){
		for (int n = 1; n <= 3; n++){
			for (int i = 1; i <= 3; i++){
				for (int m = 1; m <= 3; m++){
					for (int j = 1; j <= 3; j++){
						if (a[n][m][i][j] == '.' && n == x && m == y){
							cout << "!";
						} else {
							cout << a[n][m][i][j];
						}
					}
					cout << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
	} else {
		for (int n = 1; n <= 3; n++){
			for (int i = 1; i <= 3; i++){
				for (int m = 1; m <= 3; m++){
					for (int j = 1; j <= 3; j++){
						if (a[n][m][i][j] == '.'){
							cout << "!";
						} else {
							cout << a[n][m][i][j];
						}
					}
					cout << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
	}
	return 0;
}

```

---

## 作者：codeLJH114514 (赞：2)

[$\colorbox{#5798db}{\color{#fff}返回题目}$](https://www.luogu.com.cn/problem/CF907B)

## 题目描述

现在两头熊在下棋，棋盘被分成了 $3 \times 3$ 的 $9$ 个大格，每个大格都被分成了 $3 \times 3$ 的 $9$ 个小格。

两头熊轮流放棋子，摆放规则如下：

- 第一次可以随便摆。
- 第二次及以后必须在棋盘中位于上一次所放棋子在大格的位置的位置的大格中放置棋子。（例如前一次将棋子放在了一个大格的左上角上，则这一次必须放在左上角的大格中。）
- 如果本来要放的大格已经没有可以放的地方了，则可以在任意未放置棋子的小格放置该棋子。

## 输入输出

输入棋盘，用 $\texttt{x}$ 表示先手棋子，用 $\texttt{o}$ 表示后手棋子，用 $\texttt{.}$ 表示未被放棋子的小格。

从上到下，从左到右的输入 $9 \times 9$ 的 $81$ 个**小格**。

接下来两个整数，$x$ 和 $y$，表示上一步所下的棋子的坐标。

输出所有可以放置棋子的地方（使用 $\texttt{!}$ 表示，格式与输入相同。）。

## 解题思路

使用 $c_{i, j, k, l}$ 表示在第 $i$ 行第 $j$ 列的大格的第 $k$ 行第 $l$ 列的小格。

注意输入时下标的顺序（顺序解释看下面。），不难写出输入的代码：

```cpp
for (int i = 1; i <= 3; i++)
    for (int j = 1; j <= 3; j++) // 第i行第j列的大格
        for (int k = 1; k <= 3; k++)
            for (int l = 1; l <= 3; l++) // 第k行第l列的小格
                cin >> c[i][k][j][l]; // 注意顺序
cin >> x >> y;
```

我们希望的输入顺序：

```
1 1 1 1（分别为 i, j, k, l）
1 1 1 2
1 1 1 3
1 1 2 1
1 1 2 2
1 1 2 3
1 1 3 1
1 1 3 2
1 1 3 3
1 2 1 1
...
```

实际的输入顺序：
```
1 1 1 1
1 1 1 2
1 1 1 3
1 2 1 1
1 2 1 2
1 2 1 3
1 3 1 1
1 3 1 2
1 3 1 3
1 1 2 1
...
```

由此可见，只需按照 $i, k, j, l$ 的顺序输入即可。（因为它不是一个大格一个大格来输入的，因此 $l > 3$ 时加一的是 $j$，$j > 3$ 时加一的是 $k$。）

输入完了之后再将输入的 $x, y\bmod 3$ 就可以算出前一步下在大格的哪个位置上了。（下文将 $x \bmod 3$ 简称为 $m_x$，将 $y \bmod 3$ 简称为 $m_y$。）

然后只需要将第 $m_x$ 行第 $m_y$ 列的大格中可以填的地方填上 $\texttt{!}$ 就行了，当然如果那个大格全部是满的，只需要讲整个棋盘中可以填的地方填上 $\texttt{!}$ 即可。

输出只需要将整个 $c$ 数组向输入一样分配到二维数组中，再根据已输出小格数选择合适的分隔符。

输出的代码：
```cpp
void Print() {
    char show[128][128];
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++)
            for (int k = 1; k <= 3; k++)
                for (int l = 1; l <= 3; l++)
                    show[(i - 1) * 3 + k][(j - 1) * 3 + l] = c[i][j][k][l];
                    // 在show中copy一遍。
    int cnt = 0; // 已输出小格的数量。
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++) {
            cout << show[i][j];
            cnt += 1;
            if (cnt % 27 == 0) cout << "\n\n"; // 一行的大格已输出完毕。
            else if (cnt % 9 == 0) cout << "\n"; // 一行的小格已输出完毕。
            else if (cnt % 3 == 0) cout << " "; 
            // 选择合适的分隔符。
        }
    exit(0); // 直接结束程序。
}
```

## 完整代码

```cpp
#include <iostream>
#include <cstdlib>
using namespace std;
char c[4][4][4][4];
int x, y;
bool Fill(int, int, char, char);
void Print();
int main() {
    for (int i = 1; i <= 3; i++)
    	for (int j = 1; j <= 3; j++) // 第i行第j列的大格
            for (int k = 1; k <= 3; k++)
            	for (int l = 1; l <= 3; l++) // 第k行第l列的小格
                	cin >> c[i][k][j][l]; // 注意顺序
    cin >> x >> y;
    int mx = (x - 1) % 3 + 1;
    int my = (y - 1) % 3 + 1;
    bool b = Fill(mx, my, '!', '.');
    if (b) Print();
    // 如果没有更改过则每一个还未被放置的小格均可放置棋子。
    for (int i = 1; i <= 3; i++) 
        for (int j = 1; j <= 3; j++) 
            Fill(i, j, '!', '.');
    Print();
    return 0;
}
bool Fill(int x, int y, char f, char ch) {
// 将第x行第y列的大格中为ch的小格赋值为f。
    bool changed = false;
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++)
            if (c[x][y][i][j] == ch) {
                c[x][y][i][j] = f;
                changed = true;
            }
    return changed; // 返回是否更改过c数组。
}
void Print() {
    char show[128][128];
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++)
            for (int k = 1; k <= 3; k++)
                for (int l = 1; l <= 3; l++)
                    show[(i - 1) * 3 + k][(j - 1) * 3 + l] = c[i][j][k][l];
                    // 在show中copy一遍。
    int cnt = 0; // 已输出小格的数量。
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++) {
            cout << show[i][j];
            cnt += 1;
            if (cnt % 27 == 0) cout << "\n\n"; // 一行的大格已输出完毕。
            else if (cnt % 9 == 0) cout << "\n"; // 一行的小格已输出完毕。
            else if (cnt % 3 == 0) cout << " "; 
            // 选择合适的分隔符。
        }
    exit(0); // 直接结束程序。
}
```

---

## 作者：LaDeX (赞：1)

## 题意

有 $3\times3$ 个大格，每个大格又包含 $3\times3$ 个小格。

第一个人下在了 $(x, y)$，第二个人可以下在哪儿。

规则：第二个人可以下在第一个人下的 **小格在大格方位** 所对应的 **大格** 在中，如果大格被填满，那么可以任意下。

举个例子。

例如第一个人下在了 第 $2$ 行，第 $2$ 列的大格的左下角，第二个人就可以下在 左下角 的大格中，也就是 第 $3$ 行，第 $1$ 列的大格。

## 解法

按题意模拟即可，本人打了一个表，代表 这个小格在大格方位所对应的大格。

**Tips： 注意输出格式**

## Code
```cpp
#include<bits/stdc++.h>
#define LL long long
#define Fcin\
	ios :: sync_with_stdio(0);\
	cin.tie(0); cout.tie(0)
using namespace std;
char mp[10][10];
LL type[10][10] = {
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 1, 2, 3, 1, 2, 3, 1, 2, 3},
{0, 4, 5, 6, 4, 5, 6, 4, 5, 6},
{0, 7, 8, 9, 7, 8, 9, 7, 8, 9},
{0, 1, 2, 3, 1, 2, 3, 1, 2, 3},
{0, 4, 5, 6, 4, 5, 6, 4, 5, 6},
{0, 7, 8, 9, 7, 8, 9, 7, 8, 9},
{0, 1, 2, 3, 1, 2, 3, 1, 2, 3},
{0, 4, 5, 6, 4, 5, 6, 4, 5, 6},
{0, 7, 8, 9, 7, 8, 9, 7, 8, 9}
}, X, Y;

int main(){
    Fcin;
    for (LL i = 1; i <= 9; i ++){
    	for (LL j = 1; j <= 9; j ++){
    		cin >> mp[i][j];
		}
	}
	
	cin >> X >> Y;
	
	LL t = type[X][Y];
	
	// 目标大格的行列起始位置
	LL lx = ((t - 1) / 3) * 3 + 1, rx = ((t - 1) / 3 + 1) * 3; 
	LL ly = ((t % 3 == 0 ? 3 : t % 3) - 1) * 3 + 1, ry = ((t % 3 == 0 ? 3 : t % 3)) * 3; 
	
	
	bool flag = true;
	for (LL i = lx; i <= rx; i ++){
		for (LL j = ly; j <= ry; j ++){
			if (mp[i][j] == '.')
				flag = false;
		}
	}
	// 如果这个大格全被填满
	if (flag){
		for (LL i = 1; i <= 9; i ++){
			for (LL j = 1; j <= 9; j ++){
				if (mp[i][j] == '.')
					mp[i][j] = '!';
			}
		}
	}
	// 否则
	else{
		for (LL i = lx; i <= rx; i ++){
			for (LL j = ly; j <= ry; j ++){
				if (mp[i][j] == '.')
					mp[i][j] = '!';
			}
		}
	}
	
	for (LL i = 1; i <= 9; i ++){
		for (LL j = 1; j <= 9; j ++){
			cout << mp[i][j];
			if (j % 3 == 0)
				cout << " ";
		}
		cout << "\n";
		if (i % 3 == 0)
			cout << "\n";
	}
    
    
	return 0;
}

```


---

## 作者：oddy (赞：1)

转了一圈，没有打表的题解，那我来发一篇罢。

## Analysis

这题主要有四个难点：输入、检查大格是否填满、从小格映射到大格、输出。

先看输入：考虑用类似快读的方式，遇到无意义字符（空格、回车）就读入下一个字符直到读入可见字符为止。

可以这么写：

```cpp
char ch, s[10][11];
for(int i = 1; i <= 9; i++)
    for(int j = 1; j <= 9; j++) {
        while((ch = getchar()) && (ch == ' ' || ch == '\n')); // 过滤掉空格和回车
        s[i][j] = ch;
    }
```

再看怎样检查大格是否填满：容易发现，每个大格也是一个矩阵，所以我们可以打个表，记录每个大格的行起点、行终点、列起点、列终点。（当然也可以利用取模打一个更简单的表~~，可惜这里地方太小写不下了~~）

```cpp
struct node {
    int a, // 行起点
        b, // 行终点
        c, // 列起点
        d; // 列终点
};

const node f[] = {
    {0, 0, 0, 0}, // 占位
    {1, 3, 1, 3},
    {1, 3, 4, 6},
    {1, 3, 7, 9},
    {4, 6, 1, 3},
    {4, 6, 4, 6},
    {4, 6, 7, 9},
    {7, 9, 1, 3},
    {7, 9, 4, 6},
    {7, 9, 7, 9}
};
```

再看怎样映射：再打一个表，令 $g_{i,j}$ 代表第 $i$ 行第 $j$ 列的小格将要映射到的大格的位置，则有：

```cpp
const int g[10][10] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 占位，每个子数组的第一个元素也用来占位
    {0, 1, 2, 3, 1, 2, 3, 1, 2, 3},
    {0, 4, 5, 6, 4, 5, 6, 4, 5, 6},
    {0, 7, 8, 9, 7, 8, 9, 7, 8, 9},
    {0, 1, 2, 3, 1, 2, 3, 1, 2, 3},
    {0, 4, 5, 6, 4, 5, 6, 4, 5, 6},
    {0, 7, 8, 9, 7, 8, 9, 7, 8, 9},
    {0, 1, 2, 3, 1, 2, 3, 1, 2, 3},
    {0, 4, 5, 6, 4, 5, 6, 4, 5, 6},
    {0, 7, 8, 9, 7, 8, 9, 7, 8, 9}
};
```

我们要检查大格是否填满，然后根据它是否填满决定下一步是只能下在一个大格还是整个棋盘（根据 `check` 函数的返回值，决定调用 `f1` 还是 `f2`）：

```cpp
int p;

bool check() { // 检查大格是否填满
    p = g[x][y];
    for(int i = f[p].a; i <= f[p].b; i++)
        for(int j = f[p].c; j <= f[p].d; j++)
            if(s[i][j] == '.') return true; // 至少有一个格还有空位置
    return false;
}

void f1() {    // 还没填满就只能下在此大格
    for(int i = f[p].a; i <= f[p].b; i++)
        for(int j = f[p].c; j <= f[p].d; j++)
            if(s[i][j] == '.') s[i][j] = '!';
}

void f2() {    // 已经填满了就可以下在整个棋盘
    for(int i = 1; i <= 9; i++)
        for(int j = 1; j <= 9; j++)
            if(s[i][j] == '.') s[i][j] = '!';
}
```

最后看如何输出：如果行数能被 $3$ 整除，要多输出一个空行；如果列数能被 $3$ 整除，要输出一个空格：

```cpp
for(int i = 1; i <= 9; i++) {
    for(int j = 1; j <= 9; j++) {
        putchar(s[i][j]);
        if(!(j % 3)) putchar(' ');
    }
    putchar('\n');
    if(!(i % 3)) putchar('\n');
}
```

---

## 作者：Swiftie_wyc22 (赞：0)

这题不应该评蓝……

## 思路

 就是模拟，输入大棋盘坐标 $\left(x, y\right)$，通过对三取模获得小棋盘坐标，在小棋盘对应的大棋盘中模拟。如果对应的小棋盘找到 `.` 就变成叹号，结束程序；如果对应的棋盘是满的，那么就将整个棋盘的所有 `.` 都变成叹号，结束程序。 

## 如何存储棋盘

如何存储棋盘，使得很好在大小棋盘之间切换？

用一个四维数组存储。

首先将大棋盘分为九个块。用 $3 \times 3$ 的数组表示。也就是四维数组的前两个维。

内部再分成九个块，也用 $3 \times 3$ 的数组表示。也就是四维数组的后两个维。

 ![img](https://cdn.luogu.com.cn/upload/image_hosting/3wixqnco.png) 

## 输入和输出技巧

由于输入是一行一行输入的，所以发现输入输出的时候规则与存储棋盘的方法不符。

我们按照我们存储的方法，结合输入写出每一个字符的位置。

我们模拟一下，输入第一行每一个字符存到四维数组里面是：

```
1 1 1 1 (前两个数是小棋盘编号，后两个数是小棋盘坐标。总体是大棋盘)
1 1 1 2
1 1 1 3
1 2 1 1
1 2 1 2
1 2 1 3
1 3 1 1
1 3 1 2
1 3 1 3
```

第二行：

```
1 3 2 1
1 3 2 2
1 3 2 3
......
```

这四个数依次是

```
x, y, j, k
```

 按照输入规则，在 for 循环中就应该是

```
x, j, y, k
```

即

```cpp
void input()
{
    for (int x = 1; x <= 3; x++) // 注意循环变量顺序！！！ 
        for (int j = 1; j <= 3; j++)
            for (int y = 1; y <= 3; y++)
                for (int k = 1; k <= 3; k++)
                    cin >> c[x][y][j][k];

}
```

输出也同理。

## 完整代码

```cpp
#include <bits/stdc++.h>

using namespace std;

char c[10][10][10][10];
void input()
{
    for (int x = 1; x <= 3; x++) // 注意循环变量顺序！！！ 
        for (int j = 1; j <= 3; j++)
            for (int y = 1; y <= 3; y++)
                for (int k = 1; k <= 3; k++)
                    cin >> c[x][y][j][k];

}
bool check(int x, int y)
{
    bool haveDot = false;
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            if (c[x][y][i][j] == '.'){
                haveDot = true;
                c[x][y][i][j] = '!';
            }
        }
    }
    if (haveDot)
        return true;
    else
        return false;
}
void gg(int dx, int dy)
{
    for (int x = 1; x <= 3; x++)
        for (int y = 1; y <= 3; y++)
        {
            if (x == dx && y == dy)
                continue;
            for (int j = 1; j <= 3; j++)
                for (int k = 1; k <= 3; k++)
                    if (c[x][y][j][k] == '.')
                        c[x][y][j][k] = '!';
        }
}
void output()
{
    for (int x = 1; x <= 3; x++)
    {
        for (int j = 1; j <= 3; j++)
        {
            for (int y = 1; y <= 3; y++)
            {
                for (int k = 1; k <= 3; k++)
                    printf("%c", c[x][y][j][k]);
                printf(" ");
            }
            printf("\n");
        }
        printf("\n");
    }
}
int main()
{
    int x, y;
    input(); // 输入 
    cin >> x >> y;

    x = x % 3;
    y = y % 3;
    if (x == 0) x = 3;
    if (y == 0) y = 3; // 转换为小格子坐标 
    bool flag = check(x, y); // 检查对应小棋盘有没有空位 
    if (flag == true) {
        output(); // 输出 
        return 0;
    }
    gg(x, y); // 除了当前这个小格子，整个棋盘的空位都变成'!'
    output(); // 输出 
    return 0;
}
```



---

## 作者：Iron_Heart (赞：0)

## 思路

模拟。

先计算出第一个人当前放棋子的格子属于哪个大格子。

然后判断那个大格子是否已经放满棋子了。如果是，则将棋盘所有空的格子设为 `!`。

否则，将那个大格子的所有空的格子设为 `!`。

**要特别注意，输入输出都是每三个格子有一个空格，每三个大格有一个换行。**

## 代码

```cpp
#include <cstdio>
char chess[10][10], buf[5];
int x, y;

void print_chess() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            putchar(chess[i][j]);
            if (j % 3 == 2) {
                putchar(' ');
            }
        }
        putchar('\n');
        if (i % 3 == 2) {
            putchar('\n');
        }
    }
}

int main() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 3; ++j) {
            scanf("%s", buf);
            for (int k = 3 * j; k < 3 * (j + 1); ++k) {
                chess[i][k] = buf[k % 3];
            }
        }
    }
    scanf("%d%d", &x, &y);
    x = (x - 1) % 3;
    y = (y - 1) % 3;
    bool flag = 1;
    for (int i = 3 * x; i < 3 * (x + 1); ++i) {
        for (int j = 3 * y; j < 3 * (y + 1); ++j) {
            if (chess[i][j] == '.') {
                flag = 0;
                break;
            }
        }
    }
    if (flag) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (chess[i][j] == '.') {
                    chess[i][j] = '!';
                }
            }
        }
    } else {
        for (int i = 3 * x; i < 3 * (x + 1); ++i) {
            for (int j = 3 * y; j < 3 * (y + 1); ++j) {
                if (chess[i][j] == '.') {
                    chess[i][j] = '!';
                }
            }
        }
    }
    print_chess();
    return 0;
}
```


---

## 作者：　　　吾皇 (赞：0)

### 大概需要注意的地方：
1. 在输出时每行中每三个之间要空一格
1. 同样是输出，每输出三行要空一行
### 那么这题要怎么做呢：
 - 首先建一个char数组把所有东西都存起来，再输入最后坐标x，y（本题可以直接输出不需要读入string处理）
 - 分析x、y的坐标满足什么条件时对应的是哪一个方格。
```
由于本题是九宫格，不难想到x、y模3后可能会有规律。先从x%3==0入手，此时对应的是3、6、9行，发现当y%3==0时对应的是右下角，y%3==1时对应的是左下角...以此类推，不难发现规律
```
- 这题可以用类似打表的方法枚举每一个模数然后搜索。在搜索时先建一个bool变量，只要区间内有一个'.'，bool变量为真，并将其变为‘！’，若搜索完后仍未假，就把所有是‘.’的都变为‘！’
### 代码在这里：
```cpp
#include<bits/stdc++.h>
using namespace std;
char m[10][10];
int x,y;
void no(){//这对应的是整个可以放的宫格都被占满的情况
	for(int i=1;i<=9;i++)
	    for(int j=1;j<=9;j++) if(m[i][j]=='.') m[i][j]='!';
}
void sou(int xa,int xb,int ya,int yb){//先搜索，看看对应宫格内有没有占满
	bool n=false;
	for(int i=xa;i<=ya;i++)
		for(int j=xb;j<=yb;j++)
			if(m[i][j]=='.'){
				n=true;
				m[i][j]='!';
			}
	if(n) return;//如果有，直接返回即可
	else no();//否则搜索全部
}

int main(){
	for(int i=1;i<=9;i++)
	    for(int j=1;j<=9;j++) cin>>m[i][j];//读入超方便
	cin>>x>>y;
	switch(x%3){//这里用switch感觉比较方便
		case 1:{
			switch(y%3){
				case 1:{
					sou(1,1,3,3);//这里也就类似打表了
					break;
				}
				case 2:{
					sou(1,4,3,6);
					break;
				}
				case 0:{
					sou(1,7,3,9);
					break;
				}
			}
			break;
		}
		case 2:{
			switch(y%3){
				case 1:{
					sou(4,1,6,3);
					break;
				}
				case 2:{
					sou(4,4,6,6);
					break;
				}
				case 0:{
					sou(4,7,6,9);
					break;
				}
			}
			break;
		}
		case 0:{
			switch(y%3){
				case 1:{
					sou(7,1,9,3);
					break;
				}
				case 2:{
					sou(7,4,9,6);
					break;
				}
				case 0:{
					sou(7,7,9,9);
					break;
				}
			}
			break;
		}
	}
	for(int i=1;i<=9;i++){
		for(int j=1;j<=9;j++){
			cout<<m[i][j];
			if(j%9==0) cout<<endl;//如果j是最后一个自然要换行
			else if(j%3==0) cout<<" ";//否则如果j是3的倍数空一格，这里因为9也是3的倍数所以else
		}
		if(i%3==0) cout<<endl;//如果i是3的倍数再空一行
	}
}
```
### 祝大家都能AC本题

---

