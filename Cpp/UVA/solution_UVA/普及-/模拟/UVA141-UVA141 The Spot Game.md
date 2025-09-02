# UVA141 The Spot Game

## 题目背景

有一种叫做 Spot 的游戏，在一个 $N \times N$ 的棋盘上玩，下图是当 $N=4$ 时一些可能的样子：
![](https://cdn.luogu.com.cn/upload/image_hosting/6j8s01tj.png)

游戏中，玩家可以在空的地方放置一颗黑棋或拿走一颗黑棋，从而产生多种图案。如果棋盘上的图案（或者旋转了 $90^{\circ}$ 或 $180^{\circ}$）在之前重复过，则产生了这个图案的玩家失败，另一个玩家胜利。

例如，如果上图中第一种图案出现过，那么另外三种都会结束游戏，但最后一种不会。

## 题目描述

现在给出若干个游戏中每个玩家的操作，请你判断游戏的胜负情况。

## 说明/提示

在输入的第一个游戏中，第二位玩家在第 $3$ 步时取得胜利。

第二个游戏到最后没有出现重复的情况，因此平局。

## 样例 #1

### 输入

```
2
1 1 +
2 2 +
2 2 -
1 2 +
2
1 1 +
2 2 +
1 2 +
2 2 -
0```

### 输出

```
Player 2 wins on move 3
Draw```

# 题解

## 作者：myyyIisq2R (赞：1)

[UVA141 The Spot Game](https://www.luogu.com.cn/problem/UVA141)

### 题目大意
两个玩家依次在棋盘上下棋，每次可以选择放下一枚黑子 `+` 或者取走一枚黑子 `-`，当一个玩家操作完成后，如果棋盘布局出现此前出现过的情况，则该玩家输掉了比赛。（相同的棋盘布局考虑棋盘旋转后等价棋盘）

### 解法
使用字符串来表示棋盘。使用 `map` 来记录每种棋盘布局出现的状态，并且同时对等价的棋局 $+1$。那么出现次数 $>1$ 时该玩家输掉比赛。

### 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
map<string, int> mmap;
string str, str1, str2, str3;
int n;

int main()
{
	int a, b, sign, temp;
	char c;
	while (cin >> n)
	{
		mmap.clear();
		temp = 0;
		sign = 0;
		if (n == 0)
			return 0;
		str = "0";
		for (int i = 0; i <= n * n; i++)
		{
			str.push_back('0');
		}
		str1 = str;
		str3 = str;
		str2 = str;
		for (int i = 0; i < 2 * n; i++)
		{
			cin >> a >> b >> c;
			if (c == '+')
			{
				str[(a - 1)*n + b - 1] = '1';
			}
			else if (c == '-')
			{
				str[(a - 1)*n + b - 1] = '0';
			}
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					str1[n * j + n - i - 1] = str[n * i + j];
				}
			}
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					str2[n * (n - i - 1) + n - j - 1] = str[n * i + j];
				}
			}
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					str3[n * (n - j - 1) + i] = str[n * i + j];
				}
			}
			mmap[str]++;
			if (str1 != str)
				mmap[str1]++;
			if (str2 != str1 && str2 != str)
				mmap[str2]++;
			if (str3 != str2 && str3 != str1 && str3 != str)
				mmap[str3]++;
			if (mmap[str] > 1 && sign == 0)
			{
				temp = i;
				sign = 1;
			}
		}
		if (sign == 0)
			printf("Draw\n");
		else
			printf("Player %d wins on move %d\n", (temp + 1) % 2 + 1, temp + 1);
	}
}

```

---

## 作者：b__b (赞：0)

此题难度主要在旋转上，下文会尝试尽可能简要的讲述如何旋转棋盘。

以这个棋盘为例（`#`表示下了棋，`*`表示空着）：
```
###*
#***
####
****
```
若逆时针旋转 $90^{\circ}$，则变为：
```
**#*
#*#*
#*#*
###*
```
现在我们尝试理解并模拟这个过程。

首先注意到旋转前的第一列是旋转后的最后一行，旋转前的第二列是旋转后的倒数第二行，以此类推。

并且一列字符旋转后会将最上面的第一个字符变为旋转后的一行的第一个字符，第二个字符变为旋转后的一行的第二个字符，以此类推。

因此对于一个棋盘 $\mathrm{game}$，它逆时针旋转 $90^{\circ}$ 后的新棋盘 $\mathrm{newgame}$ 有这个关系（下标从 $0$ 开始，第一个索引表示在哪一行，第二个索引表示在哪一列）：

$\mathrm{newgame}[n-1-i][j]=\mathrm{game}[j][i]$

例如，当 $i=j=0$ 时，$\mathrm{newgame}[n-1][0]=\mathrm{game}[0][0]$，即旋转后的棋盘的最后一行的第一个字符为旋转前的第一行的第一个字符。

再比如，当 $i=1,j=0$ 时，$\mathrm{newgame}[n-2][0]=\mathrm{game}[1][0]$，即旋转后的棋盘的倒数第二行的第一个字符为旋转前的第二行的第一个字符。

同理，旋转 $180^{\circ}$ 和 $270^{\circ}$ 也可以旋转若干次 $90^{\circ}$ 得到。

接下来实现判重，~~这时我们就可以说 STL 大法好~~。

题目有给出数据范围为 $2 \leq N \leq 50$，也就是说最多会有 $100$ 个操作，每一个操作有四种需要判重的情况，最多有 $400$ 个需要判重的情况，$\mathcal{O}(\log_2n)$ 的复杂度完全够够的，因此可以用 set 来判重，具体操作见代码。
## 代码
```cpp
#include <iostream>
#include <set>
std::set<std::string> games;
std::string nowgame, xz, *now = &xz, *old = &nowgame;
int n, x, y, i, nowp, j, p, k;
char c[10];
//我们将一个棋盘压成一行，这个就是转换的函数
inline int wei(int x, int y) {return x * n + y;}
inline void win() {printf("Player %d wins on move %d\n", nowp, i + 1);}
int main() {
    for (;;) {
        end:
        scanf("%d", &n);
        if (!n) break;
        for (i = 0, nowp = 2, now = &xz, old = &nowgame, games.clear(), nowgame.clear(), xz.clear(), nowgame.resize(n * n + 5), xz.resize(n * n + 5); (i >> 1) < n; ++i, nowp = 3 - nowp) {
            scanf("%d%d", &x, &y), getchar();
            if (getchar() == '+') nowgame[wei(x - 1, y - 1)] = 'b';
            else nowgame[wei(x - 1, y - 1)] = 0;
            for (p = 0; p < 4; ++p, std::swap(now, old)) {
                for (k = 0; k < n; ++k) for (j = 0; j < n; ++j) (*now)[wei(n - 1 - k, j)] = (*old)[wei(j, k)];
                if (games.count(*now)) { //count返回set里面这个值有多少个，其实用C++20的contains更优雅但是UVa用不了（
                    win();
                    for (; (i >> 1) < n; ++i) while (getchar() != '\n'); //清空当前测试数据的输入
                    goto end;
                }
            }
            games.insert(nowgame);
        }
        puts("Draw");
    }
}
```

---

## 作者：ANDER_ (赞：0)

## 思路

~~哈希查找写炸了，修了两天~~

一道模拟，将每一行存到一个位中，用一个一维数组表示一个状态，以链表形式存储。

每次出现新操作分四次旋转处理之后在哈希表中查找，用全局变量 $flag$ 记录游戏结束时的双方走的步数，最后模拟输出，有不懂的地方详见代码。

按照题意的旋转函数：

```cpp
inline void over(int a[][50], int b[][50], int n) {
	for(int i = 0 ; i < n ; i ++) {
		for(int j = 0 ; j < n ; j ++) {
			a[j][i] = b[n - 1 - i][j];
		}
	}
	return;
}
```
哈希计算：
```cpp
for(int i = 0 ; i < n ; i ++) {
			hash_node[hash_size].A[i] = 0;
			for(int j = 0 ; j < n ; j ++) {
				hash_node[hash_size].A[i] += tem2[i][j]<<j;//哈希处理 
				sum = (sum + tem2[i][j]) % 100;
			}
		}
```

## 代码
```
#include <bits/stdc++.h>
#define int long long 
using namespace std;
typedef struct node {
	long  A[50];//棋盘 
	node *next;//链表 
}type;
type* hash_head[100];
type hash_node[100];
inline void copy(int a[][50], int b[][50], int n) {//复制函数 
	for(int i = 0 ; i < n ; i ++) {
		for(int j = 0 ; j < n ; j ++) {
			a[i][j] = b[i][j];
		}
	}
	return;
}
inline void over(int a[][50], int b[][50], int n) {//旋转函数
	for(int i = 0 ; i < n ; i ++) {
		for(int j = 0 ; j < n ; j ++) {
			a[j][i] = b[n - 1 - i][j];
		}
	}
	return;
}
int tem1[50][50], tem2[50][50], hash_size, sum, maps[50][50], n, x, y;
char ch;
inline int insert(int a[][50], int n) {
	copy(tem1, a, n);
	for(int k = 0 ; k < 4 ; k ++) {//分四次旋转处理 
		over(tem2, tem1, n);
		copy(tem1, tem2, n);
		sum = 0;
		for(int i = 0 ; i < n ; i ++) {
			hash_node[hash_size].A[i] = 0;
			for(int j = 0 ; j < n ; j ++) {
				hash_node[hash_size].A[i] += tem2[i][j]<<j;//哈希处理 
				sum = (sum + tem2[i][j]) % 100;
			}
		}
		for(type* p = hash_head[sum] ; p ; p = p -> next) {
			int flag = 0;
			for(int i = 0 ; i < n ; i ++) {
				if(p -> A[i] != hash_node[hash_size].A[i]) {//判断是否相同 
					flag = 1;
					break;
				}
			}
			if(!flag) {
				return 1;
			}
		}
	}
	hash_node[hash_size].next = hash_head[sum];
	hash_head[sum] = &hash_node[hash_size ++];
	return 0;
}
signed main() {
	ios::sync_with_stdio(false);
	cout.tie(0);
	cin.tie(0);
	while(~scanf("%d",&n) && n) {
		hash_size = 0;
		memset(maps, 0, sizeof(maps));
		memset(hash_node, 0, sizeof(hash_node));
		memset(hash_head, 0, sizeof(hash_head));
		int flag = 0;
		for (int i = 1 ; i <= 2 * n ; i ++) {
			cin>>x>>y>>ch;
			if(ch == '+') {//处理输入 
				if(maps[x - 1][y - 1] && !flag) {
					flag = i;
				} else {
					maps[x - 1][y - 1] = 1;
				}
			} else {
				if(!maps[x - 1][y - 1] && !flag) {
					flag = i;
				} else {
					maps[x - 1][y - 1] = 0;
				} 
			}
			if(insert(maps, n) && !flag) {//判断 
				flag = i;
			}
		}
		if(!flag) {
			cout<<"Draw"<<endl;
		} else {
			cout<<"Player "<<1 + flag % 2<<" wins on move "<<flag<<endl;//按照 flag 的值输出 
		}
	}
	return 0;
}
```

求过

---

