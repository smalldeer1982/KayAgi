# [ABC096C] Grid Repainting 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc096/tasks/abc096_c

$ H $ 行 $ W $ 列のマス目で表されるキャンバスがあります. 上から $ i $ 番目, 左から $ j $ 番目のマスを $ (i,\ j) $ と表します.  
 最初, すべてのマス目は白色です. square1001 君は, 黒い絵の具を使って絵を描きたいと思いました. 具体的には, square1001 君の目標は, $ s_{i,\ j}= $ `#` のときマス $ (i,\ j) $ を黒色, $ s_{i,\ j}= $ `.` のときマス $ (i,\ j) $ を白色にすることです.  
 しかし, 彼は絵を描くことが得意ではないので, 何回か ($ 0 $ 回でもよい)「上下左右に隣接する $ 2 $ つのマスを選び, 両方黒く塗る」ことしかできません. ただし, すでに黒く塗られているマスを選ぶこともでき, この場合マスの色は黒のまま変わりません.   
 square1001 君が目標を達成することができるか判定してください.

## 说明/提示

### 制約

- $ H $ は $ 1 $ 以上 $ 50 $ 以下の整数
- $ W $ は $ 1 $ 以上 $ 50 $ 以下の整数
- すべての $ (i,\ j)\ (1\ \leq\ i\ \leq\ H,\ 1\ \leq\ j\ \leq\ W) $ に対して, $ s_{i,\ j} $ は `#` または `.`

### Sample Explanation 1

目標を達成する手順の一例として, 下の図の方法が挙げられます. この図では, 「次に黒く塗るマス」を「☆」で表しています. !\[ \](https://img.atcoder.jp/abc096/18f94b6627ec5dc8aa4f6d99ae1c8fca.png)

### Sample Explanation 2

square1001 君は目標を達成することができません.

## 样例 #1

### 输入

```
3 3
.#.
###
.#.```

### 输出

```
Yes```

## 样例 #2

### 输入

```
5 5
#.#.#
.#.#.
#.#.#
.#.#.
#.#.#```

### 输出

```
No```

## 样例 #3

### 输入

```
11 11
...#####...
.##.....##.
#..##.##..#
#..##.##..#
#.........#
#...###...#
.#########.
.#.#.#.#.#.
##.#.#.#.##
..##.#.##..
.##..#..##.```

### 输出

```
Yes```

# 题解

## 作者：Trump__Biden (赞：1)

~~啊嗨嗨嗨，蒟蒻来喽。~~

[传送门](https://www.luogu.com.cn/problem/AT4126)

题意：
------------
有没有一个黑色的点事上下左右四个方向上没有黑色的点，如果没有，输出 No，否则，输出 Yes。

思路：
------------
把整张图遍历一遍，找到孤立的黑点，输出 No，如果整张图都没有被孤立的黑点，就在最后输出 Yes。

AC代码：
------------
```
#include<bits/stdc++.h>
using namespace std;
int n,m;
bool flag;
char a[550][550];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1 ;i<=n;++i)
	  for(int j=1;j<=m;++j)
	    scanf(" %c",&a[i][j]);
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			if(a[i][j]=='#')
			  if(a[i][j-1]!='#'&&a[i][j+1]!='#'&&a[i-1][j]!='#'&&a[i+1][j]!='#')//判断该点是否被孤立
			  {
				  printf("No\n");
				  return 0;
			  }
		}
	}
	printf("Yes\n");
	return 0;
}
```
~~最后说一句，其实，我是小黑子。~~

---

## 作者：Ninelife_Cat (赞：0)

### 题目大意：

有一个 $n \times m$ 的网格图，`.` 代表这一格是白色，`#` 代表这一格是黑色。一开始网格图全是白色的，你每次可以选择一个格子并把它和它四周的其中一个格子涂黑（已经是黑色的格子也可以重复涂）。现在给出网格图的最终状态，问是否能经过多次操作把它涂成这样。

### 思路：

因为每次涂色必然是选择两个相邻的方格涂黑，所以永远不存在一个黑色方格使得它周围全是白色方格。

所以只要遍历整张图，如果存在不合法的黑色方格就直接判无解就行了。

### 代码：

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define ri register
#define int long long
#define inf 2147483647
#define pb(x) push_back((x))
#define mp(x,y) make_pair((x),(y))
#define reset(x,y) memset((x),(y),sizeof((x)))
using namespace std;
inline int read()
{
	int x=0;bool f=false;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') f=true;c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^'0');c=getchar();}
	return f?-x:x;
}
const int N=520;//5.20特供版(逃
int n,m;
char a[N][N];
signed main()
{
	n=read();m=read();
 	reset(a,'.');//先把方格全部变成白色
	for(ri int i=1;i<=n;++i)	
		for(ri int j=1;j<=m;++j)
			scanf(" %c",&a[i][j]);
	for(ri int i=1;i<=n;++i)
		for(ri int j=1;j<=m;++j)
			if(a[i][j]=='#') 
				if(a[i][j-1]=='#'||a[i][j+1]=='#'||a[i-1][j]=='#'||a[i+1][j]=='#') continue;
			else return cout<<"No",0;判无解的情况
	cout<<"Yes";
	return 0;
}

---

## 作者：μηδσ (赞：0)

## Definition

我们有一个画布，比分成了$H$行和$W$列的网格。第$i$行第$j$列的方格表示为$s_{i\,j}$

最初，画布是白色的，square1001想用黑色颜料画一幅画。他想让当$s[i][j]$是'#'的时候变黑$s[i][j]$为'.'的时候变白

然而，有他不是一个后打的画家，他只能选择两个水平或垂直的相邻正方向，并将这些正方形土城黑色

他也可以选择已经涂成黑色的方块，在这种情况下，这些方块的颜色仍然是黑色。

请问square1001能否实现它的目标

## Solution

因为这个画家只能涂相邻两个正方形，所以目标画是不可能有单独存在的'#'，即不会出现任何一个位置是'#'且他的上下左右均为'.'

所以只要一个'#'周围有'#'，那么这个'#'，那么这个'#'就可以被涂黑了

## Code

~~~cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef double ld;
typedef unsigned long long ull;

const int MAXN = 55;

const int dx[] = {0, 1, 0, -1};						//坐标偏移数组 
const int dy[] = {1, 0, -1, 0};

char s[MAXN][MAXN];
int n, m;

int main(){
	cin >> n >> m;									//输入画布的长和宽 
	for(int i = 1;i <= n;i++)
		cin >> s[i] + 1;							//输入画布信息 
	for(int i = 1;i <= n;i++)						//循环判断每一个点是否合法 
		for(int j = 1;j <= n;j++)
			if(s[i][j]=='#'){						//如果这一个点是# 
				bool flag = false;					//定义旗帜 
				for(int k = 0;k < 4;k++){			//循环偏移数组坐标 
					int nx = i + dx[k];
					int ny = j + dy[k];
					if((nx > 0) && (nx <= n) && (ny > 0) && (ny <= m) && (s[nx][ny] == '#')){
						flag = true; 
						break;
					}
				}
				if(flag == false){
					cout << "No";
					return 0;
				}
			}
	cout << "Yes"; 
	return 0;
}
~~~

---

