# [BalticOI 2019] 潜艇 / Nautilus

## 题目背景

**译自 [BalticOI 2019](http://boi2019.eio.ee/tasks/) Day1 T2.** ***[Nautilus](http://boi2019.eio.ee/wp-content/uploads/2019/04/nautilus.en_.pdf)***

## 题目描述

有一艘潜艇正在海洋中秘密航行。

海洋是一个 $R \times C$ 的网格，其中 `#` 代表岛屿，`.` 代表水域，潜艇只能在水域中航行。

每分钟，潜艇会发出一个无线电信号，代表潜艇要航行的方向。方向由如下字母表示：北（N），东（E），南（S），西（W）。

现在监听者已经架设了一台拦截潜艇信号的雷达。在最近的 $M$ 分钟，雷达收集到了 $M$ 个信号，由一个长度为 $M$ 的字符串表示，例如 `WS?EE??`。收集到的信号有些无法解码，用 `?` 表示。

监听者并不知道潜艇最初的位置，但想要借助地图计算出潜艇的当前位置。请你帮助监听者计算出潜艇当前可能的位置共有几种。

## 说明/提示

各子任务的分值与数据规模如下：

- 子任务 1（29 分）：$1 \leq R,C,M \leq 100$，监听到的信号中没有 `?`。
- 子任务 2（37 分）：$1 \leq R,C,M \leq 100$。
- 子任务 3（34 分）：$1 \leq R,C \leq 500$，$1 \leq M \leq 5000$。

## 样例 #1

### 输入

```
5 9 7
...##....
..#.##..#
..#....##
.##...#..
....#....
WS?EE??```

### 输出

```
22```

# 题解

## 作者：hsfzLZH1 (赞：7)

### 题目大意

给定一个 $R\times C$ 的地图，和一个长度为 $M$ 的操作序列。潜艇的初始位置可能是没有障碍的任意位置，每次操作会按操作对应的方向前进一步，若操作为 `?` 则可能是任意方向，目标位置不能有障碍物。求出潜艇最后可能的位置有多少种。

### Subtask#1

$1\le R,C,M\le 100$ ，操作序列中没有 `?` 。

此时每一个操作都是确定的。枚举初始位置，按操作模拟潜艇的移动，统计最终潜艇的位置即可。时间复杂度为 $O(RCM)$ ，空间复杂度为 $O(RC)$ 。

### Subtask#2

$1\le R,C,M\le 100$

考虑同时计算一次操作后每个位置上是否可能有潜艇。令 $f[t][x][y]$ 表示在前 $t$ 次操作后 $(x,y)$ 这个位置上是否可能有潜艇。每次根据 $f[t-1]$ 来计算 $f[t]$ 的值，若 $t-1$ 次操作后 $(x,y)$ 位置上可能有潜艇且操作符为  `N` 且位置 $(x-1,y)$ 上不为障碍物，则令 $f[t][x-1][y]=1$ ，其他操作符以此类推。若操作符为 `?` ，则对四个方向同时进行更新。最后 $f[M]$ 中 $1$ 的个数即为答案。时间复杂度为 $O(RCM)$ ，使用滚动数组压缩掉第一维，则空间复杂度为 $O(RC)$ 。

### Subtask#3

$1\le R,C\le 500,1\le M\le 5000$

考虑对 Subtask#2 的解法进行优化。观察到 $f$ 数组的值均为 $0$ 或 $1$ ，每个操作符对 $f$ 数组的改变可以视为将 $f$ 数组向一个方向移一格，考虑使用 `bitset` 进行二进制压缩。将一个数组写成一个二进制串，则对每个操作符的运算都可以用位移运算和与运算来实现，只需注意边界即可。

时间复杂度为 $O(\dfrac {RCM} w)$ ，空间复杂度为 $O(\dfrac {RC} w)$ 。

### 参考代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
using namespace std;
const int maxn=510;
int r,c,m,ans;
char mp[maxn][maxn],op[5010];
bitset<maxn*maxn>st,f,W,E;
int main()
{
	scanf("%d%d%d",&r,&c,&m);
	for(int i=1;i<=r;i++)scanf("%s",mp[i]+1);
	scanf("%s",op);
	for(int i=1;i<=r;i++)for(int j=1;j<=c;j++)
	{
		if(mp[i][j]=='.')st[(i-1)*c+j]=1;//st 表示所有非障碍格
		if(j!=1)E[(i-1)*c+j]=1;//E 操作时不能移动最右一列
		if(j!=c)W[(i-1)*c+j]=1;//W 操作时不能移动最左一列
	}
	f=st;
	/*
	for(int i=0;i<m;i++)//这里是 Subtask#2 的实现
	{
		cur^=1;
		for(int j=1;j<=r;j++)for(int k=1;k<=c;k++)f[j][k][cur]=0;
		for(int j=1;j<=r;j++)for(int k=1;k<=c;k++)if(f[j][k][cur^1])
		{
			if(op[i]=='N'||op[i]=='?')if(j-1>=1&&mp[j-1][k]=='.')f[j-1][k][cur]=1;
			if(op[i]=='S'||op[i]=='?')if(j+1<=r&&mp[j+1][k]=='.')f[j+1][k][cur]=1;
			if(op[i]=='E'||op[i]=='?')if(k+1<=c&&mp[j][k+1]=='.')f[j][k+1][cur]=1;
			if(op[i]=='W'||op[i]=='?')if(k-1>=1&&mp[j][k-1]=='.')f[j][k-1][cur]=1;
		}
	}
	*/
	for(int i=0;i<m;i++)
	{
		if(op[i]=='N')f=(f>>c)&st;
		if(op[i]=='S')f=(f<<c)&st;
		if(op[i]=='W')f=(f>>1)&st&W;
		if(op[i]=='E')f=(f<<1)&st&E;
		if(op[i]=='?')f=((f>>c)|(f<<c)|((f>>1)&W)|((f<<1)&E))&st;
	}
	printf("%d\n",f.count());
	return 0;
} 
```

---

## 作者：船酱魔王 (赞：5)

# P6226 [BalticOI 2019 Day1] 潜艇 题解

## 题意回顾

一个潜艇在棋盘上航行，有些位置不能走，有些位置可以走，潜艇每一秒必须向上下左右四个方向走一步，你知道潜艇行动的总时间和部分时间潜艇的移动情况，求出潜艇在最后可能到达哪些位置。

棋盘行列数均不超过 $ 500 $，潜艇移动时间不超过 $ 5000 $。

## 分析

首先考虑一种暴力：开始时，潜艇可能在所有不是障碍物的地方，我们每次把所有潜艇的潜在位置向对应方向转移即为下一秒的潜在位置集合，如果不知道移动方向的话可以向四个方向转移再求出四方向位置集合的并即为新的潜在位置集合。注意每次需要把潜在位置集合删除掉障碍物格子。

可以发现，这个暴力极限运行次数约为 $ 1.25 \times 10^9 $，还有较大的常数。但是如果常数小一点的话可以冲过去。我们发现删除障碍物格子本质上是潜在位置集合与非障碍物格子取交集，而合并四个方向的并集也是可以用位运算实现的。而位置转移也本质上是左移、右移和赋值操作，因此考虑使用二进制压位优化，这里使用了 STL 中 ```bitset``` 来实现。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <bitset>
#include <string>
using namespace std;
const int N = 505;
const int K = 5005;
bitset<N> mp[N];
int n, m, k;
string s;
bitset<N> dp[2][N];
int main() {
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++) {
        cin >> s;
        s = " " + s;
        for(int j = 1; j <= m; j++) {
            if(s[j] == '.') {
                mp[i][j] = 1;
            }
        }
    }
    cin >> s;
    s = " " + s;
    int fg = 0;
    for(int i = 1; i <= n; i++) {
        dp[0][i] = mp[i];
    }
    for(int ti = 1; ti <= k; ti++) {
        fg ^= 1;
        if(s[ti] == 'W') {
            for(int i = 1; i <= n; i++) {
                dp[fg][i] = (dp[fg ^ 1][i] >> 1);
                dp[fg][i] &= mp[i];
            }
        } else if(s[ti] == 'E') {
            for(int i = 1; i <= n; i++) {
                dp[fg][i] = (dp[fg ^ 1][i] << 1);
                dp[fg][i] &= mp[i];
            }
        } else if(s[ti] == 'N') {
            for(int i = 1; i <= n; i++) {
                dp[fg][i] = dp[fg ^ 1][i + 1];
                dp[fg][i] &= mp[i];
            }
        } else if(s[ti] == 'S') {
            for(int i = 1; i <= n; i++) {
                dp[fg][i] = dp[fg ^ 1][i - 1];
                dp[fg][i] &= mp[i];
            }
        } else if(s[ti] == '?') {
            for(int i = 1; i <= n; i++) {
                dp[fg][i] = (dp[fg ^ 1][i] >> 1);
            }
            for(int i = 1; i <= n; i++) {
                dp[fg][i] |= (dp[fg ^ 1][i] << 1);
            }
            for(int i = 1; i <= n; i++) {
                dp[fg][i] |= dp[fg ^ 1][i + 1];
            }
            for(int i = 1; i <= n; i++) {
                dp[fg][i] |= dp[fg ^ 1][i - 1];
                dp[fg][i] &= mp[i];
            }
        } else {
            printf("dthkxy AK IOI\n");
        }
    }
    int tot = 0;
    for(int i = 1; i <= n; i++) {
        tot = tot + dp[fg][i].count();
    }
    cout << tot << endl;
    return 0;
}

```

## 总结与评价

在暴力 DP 侧重于可行性且状态数接近于程序可以运行的上限时，可以使用 ```bitset``` 优化掉很多倍的常数。

---

## 作者：StudyingFather (赞：4)

首先可以想到 DP：设 $f(i,x,y)$ 表示在第 $i$ 次操作后，$(x,y)$ 位置是否可达。

转移的时候枚举每个位置，向指定的方向尝试更新即可，时间复杂度 $O(rcm)$。

能不能优化呢？可以用 bitset！

我们来看看我们转移的本质：刚开始有一个 $01$ 矩阵，每次我们会将这个矩阵向上平移，向下平移，向左平移或是向右平移（当然 `?` 就代表着四个方向都可以平移）。

这个正是 bitset 所擅长的。

```cpp
// Problem : P6226 [BalticOI 2019 Day1]潜艇
// Contest : Luogu Online Judge
// URL : https://www.luogu.com.cn/problem/P6226
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit : 250 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <iostream>
#include <bitset>
using namespace std;
char s[505][505],t[5005];
bitset<505*505> ma,f,w,e;
int main()
{
 int r,c,m;
 cin>>r>>c>>m;
 for(int i=1;i<=r;i++)
  cin>>(s[i]+1);
 cin>>(t+1);
 for(int i=1;i<=r;i++)
  for(int j=1;j<=c;j++)
  {
   if(s[i][j]=='.')ma[(i-1)*c+j]=1;
   if(j!=1)e[(i-1)*c+j]=1;
   if(j!=c)w[(i-1)*c+j]=1;
  }
 f=ma;
 for(int i=1;i<=m;i++)
 {
  if(t[i]=='N')f=(f>>c)&ma;
  else if(t[i]=='S')f=(f<<c)&ma;
  else if(t[i]=='W')f=(f>>1)&w&ma;
  else if(t[i]=='E')f=(f<<1)&e&ma;
  else f=((f>>c)|(f<<c)|(f>>1&w)|(f<<1&e))&ma;
 }
 cout<<f.count()<<endl;
 return 0;
}
```

---

## 作者：cjh20090318 (赞：2)

# 题解 [P6226 [BalticOI 2019 Day1] 潜艇](https://www.luogu.com.cn/problem/P6226)

## 题意

很清楚，忽略。

## 分析

看到这种字符串题很容易想到直接广度优先搜索，复杂度 $O(rc4^m)$。

很显然承受不了，所以考虑 DP。

### 状态设计

设 $f_{i,x,y}$ 表示执行完前 $i$ 个操作后位置 $(x,y)$ 能否作为终点。

设命令字符串为 $s$，原地图为 $a$。

### 状态转移

$$
f_{i,x,y}=f_{0,x,y} \operatorname{and} 
\begin{cases}
f_{i-1,x+1,y} & s_i=\texttt{N}\\
f_{i-1,x-1,y} & s_i=\texttt{S}\\
f_{i-1,x,y+1} & s_i=\texttt{W}\\
f_{i-1,x,y-1} & s_i=\texttt{E}\\
f_{i-1,x+1,y} \operatorname{or} f_{i-1,x-1,y} \operatorname{or} f_{i-1,x,y-1} \operatorname{or} f_{i-1,x,y+1} & s_i=\texttt{?}\\
0 & \text{otherwise}
\end{cases}
$$

### 初始状态

$$

$$

$$
f_{0,x,y}=
\begin{cases}
1 & a_{x,y}=\texttt{.}\\
0 & a_{x,y}=\texttt{\#}\\
0 & \text{otherwise}
\end{cases}
$$

经过观察可以发现状态转移只需要两维，所以可以直接滚动省略掉第一维。

时间复杂度 $O(rcm)$，仍然难以通过此题。

发现 $f$ 数组的值仅为 $0$ 或 $1$，所以我们可以直接使用 `std::bitset` 进行压位砍掉常数。

### 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<bitset>
int r,c,m;
std::bitset<505> a[505],f[505],g[505];//a 为初始状态，f 为过程状态，g 为辅助状态。
int main(){
	scanf("%d%d%d",&r,&c,&m);
	for(int i=1;i<=r;i++){
		scanf(" ");
		for(int j=1;j<=c;j++) a[i][j]=getchar()=='.';
		f[i]=a[i];
	}
	scanf(" ");
	for(char c;m--;){
		c=getchar();
		if(c=='N'){
			for(int i=1;i<r;i++)f[i]=f[i+1]&a[i];
			f[r].reset();
		}
		else if(c=='S'){
			for(int i=r;i>1;--i)f[i]=f[i-1]&a[i];
			f[1].reset();
		}
		else if(c=='W'){
			for(int i=1;i<=r;i++)f[i]=(f[i]>>1)&a[i];
		}
		else if(c=='E'){
			for(int i=1;i<=r;i++)f[i]=(f[i]<<1)&a[i];
		}
		else if(c=='?'){
			for(int i=1;i<=r;i++)g[i]=(f[i-1]|f[i+1]|(f[i]<<1)|(f[i]>>1))&a[i];
			for(int i=1;i<=r;i++)f[i]=g[i];
		}
		else break;//直接转移即可。
	}
	int s=0;
	for(int i=1;i<=r;i++)s+=f[i].count();//统计有多少个值为 1，即有多少个可行的点。
	printf("%d\n",s);
	return 0;
}

```



---

## 作者：_EternalRegrets_ (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P6226)


可以发现直接搜索显然会超时，考虑动态规划。

令 $f_{i,x,y}$ 表示到了第 $i$ 个信号后，是否可以达到坐标 $(x,y)$，转移时直接向四个方向进行更新。

这样我们的时间复杂度是 $O(RCM)$ 的，还是会超时。

考虑到 $f_{i,x,y}$ 的值只可以是 $0$ 或者 $1$ , 可以使用 `bitset` 过掉。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

char ss[50005];
char s[505][505];
bitset <300000> a;
bitset <300000> f;
bitset <300000> east;
bitset <300000> west;

signed main()
{
	int r; cin>>r;
	int c; cin>>c;
	int m; cin>>m;

	for(int i=1;i<=r;i++){
		cin>>(s[i]+1);
	}

	cin>>ss;

	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			if(s[i][j]=='.'){
				a[c*(i-1)+j]=1;
			}

			if(j!=1){
				east[c*(i-1)+j]=1;
			}

			if(j!=c){
				west[c*(i-1)+j]=1;
			}
		}
	}

	f=a;

	for(int i=0;i<m;i++){
		if(ss[i]=='N'){
			f=(f>>c)&a;
		}

		if(ss[i]=='S'){
			f=(f<<c)&a;
		}

		if(ss[i]=='E'){
			f=(f<<1)&east&a;
		}

		if(ss[i]=='W'){
			f=(f>>1)&west&a;
		}

		if(ss[i]=='?'){
			f=((f<<c)|(f>>c)|((f<<1)&east)|((f>>1)&west))&a;
		}
	}

	cout<<f.count();
	return 0;
}
```

---

## 作者：sinestrea (赞：1)

[更好的阅读体验](http://103.166.246.5:8888/blog/2/6530a28d0547e700bd63cebd)

我们可以将初始位置都标记出来，对于每次操作整体向对应位置移动（若是问号则想四个方向移动），即当前操作下的所有可能。

这样时间复杂度是 $O(RCM)$，显然是过不了的，于是我们可以用 std::bitset，于是时间复杂度变成了 $O(\frac{RCM}{w} )$。

```cpp
#include <bits/stdc++.h>

const int MAX = 555;

int r{}, c{}, m{};

std::bitset<MAX> map[MAX]{}, state[MAX]{}, auxState[MAX]{};
std::string opt{};

void optN() {
    for (int i = 1; i < r; i++) state[i] = state[i + 1];
    state[r] = 0;
}

void optE() {
    for (int i = 1; i <= r; i++) state[i] = (state[i] << 1);
}

void optS() {
    for (int i = r; i > 1; i--) state[i] = state[i - 1];
    state[1] = 0;
}

void optW() {
    for (int i = 1; i <= r; i++) state[i] = (state[i] >> 1);
}

void optInd() {
    for (int i = 1; i <= r; i++) auxState[i] = 0;
    for (int i = 1; i < r; i++) auxState[i] |= state[i + 1];
    for (int i = 1; i <= r; i++) auxState[i] |= (state[i] << 1);
    for (int i = r; i > 1; i--) auxState[i] |= state[i - 1];
    for (int i = 1; i <= r; i++) auxState[i] |= (state[i] >> 1);
    for (int i = 1; i <= r; i++) state[i] = auxState[i];
}

void update() {
    for (int i = 1; i <= r; i++) state[i] &= map[i];
}

void init() {
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            char c = getchar();
            while (c != '#' && c != '.') c = getchar();
            if (c == '.') map[i][j] = 1, state[i][j] = 1;
        }
    }
}

void dp() {
    char nowOpt{};
    for (int i = 1; i <= m; i++) {
        nowOpt = opt[i - 1];
        if (nowOpt == 'N') optN(), update();
        else if (nowOpt == 'E') optE(), update();
        else if (nowOpt == 'S') optS(), update();
        else if (nowOpt == 'W') optW(), update();
        else optInd(), update();
    }
    int sum{};
    for (int i = 1; i <= r; i++) sum += state[i].count();
    std::cout << sum;
}


int main() {
    std::cin >> r >> c >> m;
    init();
    std::cin >> opt;
    dp();
}

```

---

## 作者：SolIII (赞：1)

## 前言

[更好的阅读体验](https://www.luogu.com.cn/blog/gjhdbk/solution-p6226#)

S 组模拟赛的 T1，在考场没做对，交发题解加深下印象。

## 题目分析

第一眼见到这道题目时，想到的是 Sub1 的暴力解，枚举整个矩阵中的海洋，然后直接按照信号模拟潜水艇的路径上是否有陆地。其次，我们可以想到，对于信号中的 `'?'`，可以将其拓展成四个方向，再进行枚举。

进一步的优化，我们可以发现对于同一个终点，可能会有超过 1 个的起点可以到达，我们如果分别枚举每个点，可能会发生重复的情况。所以考虑到是否可以对整个矩阵直接进行模拟。

设计状态 $f_{k, i, j}$ 表示在处理信号到第 $k$ 位时，潜水艇有没有可能出现在第 $i$ 行 $j$ 列。在处理信号时根据信号中的方向转移，时间复杂度为 $O(RCM)$，可以获得 66 分。

考虑再次优化，首先将三位压为两位，$f_{k, (i - 1) \times n + j}$ 表示在处理信号到第 $k$ 位时，潜水艇有没有可能出现在第 $i$ 行 $j$ 列。再考虑状态压缩，用 [bitset（点击直达 oi - wiki）](https://oi-wiki.org/lang/csl/bitset/) 优化，将转移直接写成位移，不能在陆地上用按位与运算操作。可获得时间复杂度为 $O(\frac{RCM}{w})$ 的可行算法。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR = 5 * 1e2;
const int MR = 5 * 1e3;
char a[NR + 10][NR + 10];
char s[MR + 10];
bitset<NR * NR + 10> bs;//陆地
bitset<NR * NR + 10> w;//西
bitset<NR * NR + 10> e;//东
bitset<NR * NR + 10> dp;//模拟数组

int main(){
    int n, m, len;
    scanf("%d%d%d", &n, &m, &len);//读入
    for(int i = 1;i <= n;i++){
        scanf("%s", a[i] + 1);
        for(int j = 1;j <= m;j++){
            if(a[i][j] == '.'){
                bs[(i - 1) * n + j] = true;//存进 bitset
            }
            //对于e和w，在位移时会出现这一行的第一个（最后一个）变成了上一行（下一行）的最后一个（第一个）的情况，需要特殊处理
            if(j != 1) e[(i - 1) * n + j] = true;
            if(j != m) w[(i - 1) * n + j] = true;
        }
    }
    scanf("%s", s + 1);
    dp = bs;
    for(int i = 1;i <= len;i++){//开始模拟
        if(s[i] == 'W'){//W方向
            dp = ((dp >> 1) & w) & bs;//特殊处理
        }
        if(s[i] == 'E'){//E方向
            dp = ((dp << 1) & e) & bs;//特殊处理
        }
        //我们发现，对于向N或向S，可以直接用右移或左移m个来表示
        if(s[i] == 'N'){//N方向
            dp = (dp >> m) & bs;
        }
        if(s[i] == 'S'){//S方向
            dp = (dp << m) & bs;
        }
        if(s[i] == '?'){//对于问号，将其拓展为 W E N S 四个方向
            dp = (((dp >> 1) & w) | ((dp << 1) & e) | (dp >> m) | (dp << m)) & bs;
        }
    }
    printf("%d\n", (int)dp.count());//答案为true的个数
    return 0;
}
```

---

## 作者：xuyuesen (赞：0)

## 题目大意
在一个 $R\times C$ 的表格中，潜艇只能存在于'.'上，给定潜艇的航行方向，求潜艇最终可能在的位置的数量。
## 思路
容易想到通过当前可能的点去推导出下一个状态可能的点。

记 $ok_{i,j,k}$ 表示点 $(j,k)$ 在记录中是否能满足前 $i$ 个移动，$nw_{i,j,k}$ 表示是否能通过 $ok$ 数组推出点 $(j,k)$ 在记录中满足前 $i$ 个移动。$fx_{0,1,2,3}$ 与 $fy_{0,1,2,3}$ 表示移动的方向与移动的长度（一格）。点 $(i,j)$ 是否可行记为 $ch_{i,j}$。

当点 $(j,k)$ 可行时，当且仅当 $(j,k)$ 为'.'，其旁边的点可行且可以通过当前移动到达此点，我在移动为'?'时将其与上次结果或起来，所以转移方程为:
$$
\large nw_{i,j,k}\gets nw_{i,j,k}\cup(ok_{i,j-fx_{tp},k-fy_{tp}} \cap ch_{j,k})
$$
随后 $nw$ 数组即为新的 $ok$ 数组。
$$
  \large ok_{i,j,k}\gets nw_{i,j,k}
$$
时间复杂度为 $O(RCm)$，空间复杂度为 $O(RCm)$。

可以发现 $ok$ 和 $nw$ 数组只依赖上一层的结果，第一维不需要，可以删掉。\
之后时间复杂度 $O(RCm)$，空间复杂度 $O(RC)$。

又发现，转移方程在一整层中都是一样的，而且 $ok$ 和 $nw$ 数组中存的都是 0 和 1，可以使用 bitset 以提升时间。\
之后时间复杂度为 $O(\frac{RCM}{w})$，空间复杂度为 $O(RC)$。其中 $w$ 为计算机字长。

---

## 作者：National_Studying (赞：0)

题意很清楚。

第一想法是直接暴搜，复杂度为 $O(rc4 ^ m)$，是肯定会超时的。

就考虑一下 DP，令 $f_{i,x,y}$ 表示为当执行了 $i$ 个操作时，是否到达了 $(x,y)$，转移就向四个方向进行转移即可。

考虑到这，复杂度为 $O(rcm)$，还是会超时。就考虑用 `bitset` 压位砍掉常数。

故最终复杂度为 $O(\frac{rcm}{w})$，是本题可以接受的。

---

## 作者：封禁用户 (赞：0)

### 题目传送门

[P6226](https://www.luogu.com.cn/problem/P6226)

### 题意

有一张 $C \times R$ 的地图，有一些点可以行走，有一个长度为 $n$ 一些位置不确定的行走的序列，问终点的可能数量。

朴素的 DP 是 $O(CRn)$ 的，如果用广搜优化能少很多无用状态，但并没有改变时间复杂度，仍然卡不过去。

可以看出，每个位置只有能到和不能到两种状态，所以可以对每个时刻每一行记一个 bitset。

设 $st[i][j]$ 表示 $i$ 时刻第 $j$ 行的状态。

状态转移方程：

```cpp
if(b[t] == 'N'||b[t] == '?')
	F(i,1,n)	
		st[t][i] |= st[t-1][i+1];
if(b[t] == 'S'||b[t] == '?')
	F(i,1,n)
		st[t][i] |= st[t-1][i-1];
if(b[t] == 'E'||b[t] == '?')
	F(i,1,n)
		st[t][i] |= st[t-1][i] << 1;
if(b[t] == 'W'||b[t] == '?')
	F(i,1,n)
		st[t][i] |= st[t-1][i] >> 1;
```

时间复杂度为 $O(\frac{CRn}{w})$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IO
{
	constexpr int fsize = 1<<24;
	#define getchar() ((IO::si!=IO::ti||(IO::ti=(IO::si=IO::input)+fread(IO::input,1,IO::fsize,stdin))),IO::si!=IO::ti?*(IO::si++):EOF)
	#define putchar(c) ((IO::out.so!=IO::out.to||(fwrite(IO::out.output,1,IO::fsize,stdout),IO::out.so=IO::out.output)),*(IO::out.so++)=c)
	char input[fsize],*si = input,*ti = input;
	struct output_stream
	{
		char output[fsize],*so = output,*to = output + fsize;
		inline ~output_stream()
		{
			if(so == output) return;
			fwrite(output,1,so-output,stdout);
			so = output;
		}
	}out; 
	template<typename T>inline void read(T &x)
	{
		int c = getchar(),p = 1;
		x = 0;
		while(c < 48||c > 57)
		{
			if(c == 45) p = -1;
			c = getchar();
		}
		while(48 <= c&&c <= 57)
		{
			x = (x<<3)+(x<<1)+(c^48);
			c = getchar();
		}
		x *= p;
	}
	template<typename T>inline void write(T x)
	{
		static int c[40],cnt = 0;
		if(x < 0) putchar(45),x = -x;
		if(!x) putchar(48);
		while(x) c[++cnt] = x%10^48,x /= 10;
		while(cnt) putchar(c[cnt--]);
	}
}
using IO::read;
using IO::write;
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define M 5010
#define N 510
char b[M];
bitset<N> mp[N],st[M][N];
int n,m,k,ans = 0;
int main()
{
	read(n),read(m),read(k);
	F(i,1,n) 
	{
		F(j,1,m) st[0][i][j] = mp[i][j] = (getchar() == '.');
		getchar();
	}
	F(i,1,k) b[i] = getchar();
	F(t,1,k)
	{
		if(b[t] == 'N'||b[t] == '?')
			F(i,1,n)	
				st[t][i] |= st[t-1][i+1];
		if(b[t] == 'S'||b[t] == '?')
			F(i,1,n)
				st[t][i] |= st[t-1][i-1];
		if(b[t] == 'E'||b[t] == '?')
			F(i,1,n)
				st[t][i] |= st[t-1][i] << 1;
		if(b[t] == 'W'||b[t] == '?')
			F(i,1,n)
				st[t][i] |= st[t-1][i] >> 1;
		F(i,1,n) st[t][i] &= mp[i];	
	}
	F(i,1,n) ans += st[k][i].count();
	write(ans);
	return 0;
}
```


---

