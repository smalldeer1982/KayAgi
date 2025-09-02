# [AGC043A] Range Flip Find Route

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc043/tasks/agc043_a

$ H $ 行 $ W $ 列のマス目を考えます。上から $ r $ 番目、左から $ c $ 番目のマスを $ (r,\ c) $ と表すことにします。 全てのマスはそれぞれ白か黒のどちらかの色に塗られています。

次のような経路が存在するとき、このマス目を"良い"状態と呼びます。

- 常に白いマスの上にいながら、$ (1,\ 1) $ から、一つ **右か下** のマスに移動することを繰り返し、 $ (H,\ W) $ へ移動する。

ここで、"良い"状態ならば $ (1,\ 1) $ や $ (H,\ W) $ が必ず白いことに注意してください。

あなたの仕事は、以下の操作を繰り返し、マス目を"良い"状態にすることです。最小で何回操作を行う必要があるか求めてください。なお、有限回の操作で必ず"良い"状態に出来ることが証明可能です。

- $ 4 $ つの整数 $ r_0,\ c_0,\ r_1,\ c_1(1\ \leq\ r_0\ \leq\ r_1\ \leq\ H,\ 1\ \leq\ c_0\ \leq\ c_1\ \leq\ W) $ を選ぶ。$ r_0\ \leq\ r\ \leq\ r_1,\ c_0\ \leq\ c\ \leq\ c_1 $ を満たす全ての $ r,\ c $ について、$ (r,\ c) $ の色を変更する。つまり、白色ならば黒色にし、黒色ならば白色にする。

## 说明/提示

### 制約

- $ 2\ \leq\ H,\ W\ \leq\ 100 $

### Sample Explanation 1

$ (r_0,\ c_0,\ r_1,\ c_1)\ =\ (2,\ 2,\ 2,\ 2) $、つまりマス $ (2,\ 2) $ のみ色を変更すれば良いです。

### Sample Explanation 3

操作が必要ない場合も存在します。

## 样例 #1

### 输入

```
3 3
.##
.#.
##.```

### 输出

```
1```

## 样例 #2

### 输入

```
2 2
#.
.#```

### 输出

```
2```

## 样例 #3

### 输入

```
4 4
..##
#...
###.
###.```

### 输出

```
0```

## 样例 #4

### 输入

```
5 5
.#.#.
#.#.#
.#.#.
#.#.#
.#.#.```

### 输出

```
4```

# 题解

## 作者：xht (赞：8)

注意到，最后走的路线一定是黑白交替的。

每一次翻转颜色都一定是在进入黑色的时候，将后面一段黑色的路变成白色。

这与最短路很类似，由于边权只有 $0/1$，因此本题用 `deque` bfs 即可，时间复杂度 $\mathcal O(nm)$。

```cpp
const int N = 107, inf = 1e9;
int n, m, d[N][N], v[N][N];
char s[N][N];
deque<pi> q;

int main() {
	rd(n), rd(m);
	for (int i = 1; i <= n; i++) rds(s[i], m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			d[i][j] = inf;
	q.pb(mp(1, 1)), d[1][1] = s[1][1] == '#';
	while (q.size()) {
		pi x = q.front();
		q.pop_front();
		if (v[x.fi][x.se]) continue;
		v[x.fi][x.se] = 1;
		if (x.fi < n) {
			if (s[x.fi][x.se] == '.' && s[x.fi+1][x.se] == '#') {
				if (d[x.fi+1][x.se] > d[x.fi][x.se] + 1)
					q.pb(mp(x.fi + 1, x.se)), d[x.fi+1][x.se] = d[x.fi][x.se] + 1;
			} else {
				if (d[x.fi+1][x.se] > d[x.fi][x.se])
					q.push_front(mp(x.fi + 1, x.se)), d[x.fi+1][x.se] = d[x.fi][x.se];
			}
		}
		if (x.se < m) {
			if (s[x.fi][x.se] == '.' && s[x.fi][x.se+1] == '#') {
				if (d[x.fi][x.se+1] > d[x.fi][x.se] + 1)
					q.pb(mp(x.fi, x.se + 1)), d[x.fi][x.se+1] = d[x.fi][x.se] + 1;
			} else {
				if (d[x.fi][x.se+1] > d[x.fi][x.se])
					q.push_front(mp(x.fi, x.se + 1)), d[x.fi][x.se+1] = d[x.fi][x.se];
			}
		}
	}
	print(d[n][m]);
	return 0;
}
```

---

## 作者：oimaster (赞：7)

在我的[博客](https://oi-master.github.io/post/atcoder-agc-043-a-ti-jie/)阅读体验更好哦！

这道题把我坑的无话可说，实在是服了这个做法。动态规划！当时没想出来，现在想想，感觉自己理解得差不多了……好了，回归正题，我们先按照老配方——题面先。

## 题面
### 英文题面
请你走 [这里](https://atcoder.jp/contests/agc043/tasks/agc043_a) ，会带你去 Atcoder 官网。

### 中文题面
这道题大意是这样的：

给你一个 $H\times W$ 的迷宫，其中，“.”代表空地，“#”代表墙。现在，让你从左上角的 $(1, 1)$ 走到右下角的 $(H, W)$ ，只能走右边或下面。不过，这与往常的题目不一样，不是问你最少要走多少步，也不是有几种走法。其实，这个迷宫可能不同，现在给你一个条件，就是选择一个矩阵，把这个区域内的所有的空地转成墙，墙转成空地。问你最少要多少个操作才能保证能同行。
## 思路
这道题，我们先看枚举。枚举什么呢？枚举操作次数，然后在嵌套一个枚举在哪里操作？答案是完美的，不会错，但是你不用写了，一定会超时。

然后，我们考虑贪心。如何贪心？这仍然是个问题。好像贪心很难想全，情况较多。那么引用一位学长的话，叫做：

> 贪心不行就 DP 。

好的，~~为了验证这句话的正确性~~，我们就做一下 DP 吧。不过，这道题的 DP 状态转移方程有点难想，显然，状态较多，一不小心套个四重循环就会爆（其实不一定，不过估计评测机不是用现在的高级 CPU，而是像 CCF 统一评测老爷机来评测的，最好不要冒这个险），所以，这个 DP 又是一个难写的 DP 啊，不好想。

卡在这里显然不太合适，我们先看一下要你写的代码吧，从微观开始讲。先提前说一下，这个代码不是本人自己写的，而是一位大佬 hhhyyyfff 写的，在此先膜拜一下。
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char s[110][110];
int H, W, f[110][110];

int main() {
    scanf("%d%d", &H, &W);
    for (int i = 1; i <= H; ++i) scanf("%s", s[i] + 1);

    f[1][1] = s[1][1] == '#';
    for (int i = 2; i <= W; ++i)
        f[1][i] = f[1][i - 1] + (s[1][i - 1] == '.' && s[1][i] == '#');
    for (int i = 2; i <= H; ++i)
        f[i][1] = f[i - 1][1] + (s[i - 1][1] == '.' && s[i][1] == '#');
    for (int i = 2; i <= H; ++i)
        for (int j = 2; j <= W; ++j)
            f[i][j] = min(f[i - 1][j] + (s[i - 1][j] == '.' && s[i][j] == '#'),
                          f[i][j - 1] + (s[i][j - 1] == '.' && s[i][j] == '#'));
    printf("%d\n", f[H][W]);
    return 0;
}
```
首先，读入没什么难的事情了，主要就是后面的 DP 。

第一行与第一列的初始化大家应该也能看得懂，知道这是什么意思。唯独后面的条件是什么意思还不知道。待会我会解释的，您们放心。

然后，就是主要的 DP 了，发现仍然很简单。当你不看后面那个 `(s[i - 1][j] == '.' && s[i][j] == '#')` 时，你一定会尖叫：

> 这个 DP 太土了！比 [传纸条](https://www.luogu.com.cn/problem/P1006) 还简单呐！

看来，主要的核心就在那一个表达式上面了。表达式的意思是，这个点要不要再翻一次，对不对？这是显而易见的。

首先，如果这个点不是墙，那么小表达式的值一定为 $0$ 。

我们来看看，如果上一步是从上方走下来的，且上方是个墙，那么要不要翻？显然，上边翻的时候，把这一格的墙也同时翻掉了，所以，不用再翻。但是如果上面一格是空地呢？说明没有翻到这个墙，这个墙还要再翻一次。

左边的也是对称的。

嘿，让我们往宏观走走。这个 DP 十分巧妙，在记录最少的翻的次数时，顺便就把翻的标记也延续下来了。十分有意思，也很巧妙。

## 代码
还是刚刚的代码。

还是 stO hhhyyyfff Orz 。
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char s[110][110];
int H, W, f[110][110];

int main() {
    scanf("%d%d", &H, &W);
    for (int i = 1; i <= H; ++i) scanf("%s", s[i] + 1);

    f[1][1] = s[1][1] == '#';
    for (int i = 2; i <= W; ++i)
        f[1][i] = f[1][i - 1] + (s[1][i - 1] == '.' && s[1][i] == '#');
    for (int i = 2; i <= H; ++i)
        f[i][1] = f[i - 1][1] + (s[i - 1][1] == '.' && s[i][1] == '#');
    for (int i = 2; i <= H; ++i)
        for (int j = 2; j <= W; ++j)
            f[i][j] = min(f[i - 1][j] + (s[i - 1][j] == '.' && s[i][j] == '#'),
                          f[i][j - 1] + (s[i][j - 1] == '.' && s[i][j] == '#'));
    printf("%d\n", f[H][W]);
    return 0;
}
```
本文到此结束。

---

## 作者：cjZYZtcl (赞：4)

## DP题。
我们用 $f_{i,j}$ 来表示走到第 $i$ 行第 $j$ 列最少要区间翻转几次。

考虑怎么状态转移。

题目说，只能向下或向右走，那么可以得出，当前点的状态只能从他的左边和上边转移。

那怎么转移呢？

对于一个点，如果是 '.' ，那么这个点肯定不用覆盖。翻转次数等于上一个点。

如果这个点是 '#' ，那么可以发现，如果上一个点也要翻转，那么这个点可以和上一个点在同一个区间里翻转即可。翻转次数也等于上一个点。

如果不是上面两种情况，就为上一个点加一。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int f[105][105];
char a[105][105];
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	int n = read(), m = read();
	char ch;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			ch = getchar();
			while(ch != '.' && ch != '#'){
				ch = getchar();
			}
			a[i][j] = ch;
		}
	}
	if(a[1][1] == '#') f[1][1] = 1;
	else f[1][1] = 0;
	for(int i = 2; i <= n; i++){
		if(a[i][1] == '.' || a[i][1] == a[i - 1][1]) f[i][1] = f[i - 1][1];
		else f[i][1] = f[i - 1][1] + 1;
	}
	for(int j = 2; j <= m; j++){
		if(a[1][j] == '.' || a[1][j] == a[1][j - 1]) f[1][j] = f[1][j - 1];
		else f[1][j] = f[1][j - 1] + 1;
	}
	int x, y;
	for(int i = 2; i <= n; i++){
		for(int j = 2; j <= m; j++){
			x = f[i - 1][j] + 1;
			y = f[i][j - 1] + 1;
			if(a[i][j] == '.'){
				x = f[i - 1][j];
				y = f[i][j - 1];
			}
			if(a[i][j] == a[i - 1][j]){
				x = f[i - 1][j];
			}
			if(a[i][j] == a[i][j - 1]){
				y = f[i][j - 1];
			}
			f[i][j] = min(x, y);
		}
	}
	write(f[n][m]);
}
```


---

## 作者：lzk5627 (赞：3)

### 题意:
给出一个矩阵,每个格子为黑色或是白色

现在定义一次操作为翻转一个矩形中的格子的颜色

求最小的操作次数,使得能够只经过白格子从 $(1,1)$ 到达 $(n,m)$,每次只能向左向下走

### sol

最开始看错题目了(爆炸

考虑一条路径,发现对于任意连续的黑格子段,我们都可以通过一次翻转使得他们变成白色的,所以问题等价于找到一条路径,使得黑格子段最小

然后设 $f_{i,j}$ 表示到达 $(i,j)$ 最小的连续黑格子段数是多少,然后直接转移即可

```cpp
#include<algorithm>
#include<iostream>
#include<climits>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<queue>
#include<set>
#include<map>
#define ll long long
using namespace std;
//{{{ read()
inline int read(){
	register int x=0,f=1;
	register char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')	f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')	x=x*10+(ch^48),ch=getchar();
	return x*f;
}
//}}}
const int N=1005;
char s[N][N];
int n,m,a[N][N];
struct P{
	int x,y,z;
	P (int xx=0,int yy=0,int zz=0){
		x=xx,y=yy,z=zz;
	}
	bool operator < (const P k) const{
		return z>k.z;
	}
};
priority_queue<P> que;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)	scanf("%s",s[i]+1);
	memset(a,27,sizeof(a));
	a[1][1]=(s[1][1]=='#');
	que.push(P(1,1,a[1][1]));
	while(!que.empty()){
		P k=que.top();	que.pop();
		int x=k.x,y=k.y,z=k.z;
		if(z!=a[x][y])	continue;
		if(x<n){
			int k=z+(s[x+1][y]=='#'&&s[x][y]=='.');
			if(k<a[x+1][y])	a[x+1][y]=k,que.push(P(x+1,y,k));
		}
		if(y<m){
			int k=z+(s[x][y+1]=='#'&&s[x][y]=='.');
			if(k<a[x][y+1])	a[x][y+1]=k,que.push(P(x,y+1,k));
		}
	}
	cout<<a[n][m]<<endl;
	return 0;
}
```

---

## 作者：Obviathy (赞：1)

## 解题思路
我们申请一个数组 $f[i][j][1/0]$ 记录从第 $(1,1)$ 位置，到 $(i,j)$ 位置，从两个方向来（$"1"$ 是从上边来，$"0"$ 是从左边来）需要的操作次数。$a[i][j]$ 记录位置上有没有井号。由于是三维的，自认为比较好理解。
 下面就到了推理状态转移方程的时候了！
- 一般情况下，第 $(i,j)$ 个位置从上边来的最小操作数就是上边格子 $(i-1,j)$ 的从两个方向来的操作数的最小值加上这个位置是不是井号，第 $(i,j)$ 个位置从左边来的最小操作数就是左边格子 $(i,j-1)$ 的从两个方向来的操作数的最小值加上这个位置是不是井号。
- 如果左边和本身都是井号，如果这么走，就只需一次操作即可，即删除这两个位置上的井号。所以，如果满足这一条件，它的状态就是左边的两方向最小值。
- 如果上边和本身都是井号，与左边同理。

所以，状态转移方程为：

先判断：

$\begin{cases}if:a[i][j] = a[i-1][j] = 1:f[i][j][1] = min(f[i-1][j][1],f[i-1][j][0]);\\if:a[i][j] = a[i][j-1] = 1:f[i][j][0] = min(f[i][j-1][1],f[i][j-1][0]);\end{cases} $

然后判断（其中 "left";"up" 为左边与本身为井号和上边与本身为井号简写）：

$\begin{cases}if :left:f[i][j][1] = min(f[i-1][j][1],f[i-1][j][0])+a[i][j];\\if:up:f[i][j][0] = min(f[i][j-1][1],f[i][j-1][0])+a[i][j];\\otherwise:\begin{cases}f[i][j][1] = min(f[i-1][j][1],f[i-1][j][0])+a[i][j];\\f[i][j][0] = min(f[i][j-1][1],f[i][j-1][0])+a[i][j];\end{cases}\end{cases}$

~~好复杂QAQ~~

虽然后面的括号里除了 $\texttt {otherwise}$ 的那两个判断不写也能AC（我也不知道是数据太水还是可以证明，反正我没证），但是这样更严谨。

注意！前两个判断要同时，绝对不能 $\texttt {else}$!
## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[102][102];
int f[102][102][2];
int n,m;
int main(){
	cin >> n >> m;
	memset(f,0x3f,sizeof f);
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= m;j ++){
			char s;
			cin >> s;
			a[i][j] = (s=='#');
		}
	}
	f[1][0][1] = f[1][0][0] = 0;
	f[0][1][1] = f[0][1][0] = 0;
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= m;j ++){
			int f1 = 0,f2 = 0;
			if(a[i][j-1] == 1 && a[i][j] == 1){
				f[i][j][0] = min(f[i][j-1][1],f[i][j-1][0]);
				f1 = 1;
			}
			if(a[i-1][j] == 1 && a[i][j] == 1){
				f[i][j][1] = min(f[i-1][j][1],f[i-1][j][0]);
				f2 = 1;
			}
			if(f1 == 0 && f2 == 0){
				f[i][j][0] = min(f[i][j-1][1],f[i][j-1][0])+a[i][j];
				f[i][j][1] = min(f[i-1][j][1],f[i-1][j][0])+a[i][j];
			} 
			if(f1 == 1 && f2 == 0)f[i][j][1] = min(f[i-1][j][1],f[i-1][j][0])+a[i][j];
			if(f1 == 0 && f2 == 1)f[i][j][0] = min(f[i][j-1][1],f[i][j-1][0])+a[i][j];
		}
	}
	cout<<min(f[n][m][0],f[n][m][1])<<endl;
	return 0;
}
```


---

## 作者：QTcyy (赞：1)

## 这题看似是一个贪心，可是仔细一想是一个DP
---
### 过程
因为本题只能向右或向下走，所以设当先的位置坐标为$(i,j)$

**从上到下**

则如果$i-1$为'.'就表示$i-1$可以直接通过,如果$i$为'#'且要从$i-1$走到$i$，就必须变换一次。

**从左到右的同理**

所以我们可以很快地写出**状态转移方程**

设$f_{i,j}$为从$(1,1)$走到$(i,j)$的最小变换次数
1. 如果$(i-1,j)$为'.'且$(i,j)$为'#'：
    $f_{i,j}=f_{i-1,j}+1$
2. 如果$(i,j-1)$为'.'且$(i,j)$为'#'：
    $f_{i,j}=f_{i,j-1}+1$

---
### 当然我们不能忘记初始化

1. 对于起点
    显然，起点肯定是要经过的，所以如果$(1,1)$为'#'，那么$f_{1,1}=1$

2. 对于第一行
    所有向下走的步骤都是建立在第一行的基础上的，都是从第一行走过来的，所以需要初始化。第一行的初始化与本题的状转方程相同
        如果$(i-1,j)$为'.'且$(i,j)$为'#'：$f_{1,j}=f_{1,j-1}+1$
        否则：$f_{1,j}=f_{1,j-1}$

3. 对于第一列
    所有向右走的步骤都是建立在第一行的基础上的，所以第一列也需要初始化。初始化与状转方程相同
    如果$(i-1,j)$为'.'且$(i,j)$为'#'：$f_{i,j}=f_{i-1,j}+1$
    否则：$f_{i,j}=f_{i-1,j}$

---

### 到此所有的步骤都完成了
最后答案为$f_{H,W}$

---
#### 详细步骤参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int n,m;
char ch[N][N];
int f[N][N];

int main(void){
    cin>>n>>m;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            cin>>ch[i][j];
    if (ch[1][1]=='#')
        f[1][1]=1;
    for (int i=2;i<=m;i++){
        int now=0;
        if (ch[1][i-1]=='.' && ch[1][i]=='#')
            now=1;
        f[1][i]=f[1][i-1]+now;
    }
    for (int i=2;i<=n;i++){
        int now=0;
        if (ch[i-1][1]=='.' && ch[i][1]=='#')
            now=1;
        f[i][1]=f[i-1][1]+now;
    }
    for (int i=2;i<=n;i++)
        for (int j=2;j<=m;j++){
            int now1=0,now2=0;
            if (ch[i][j-1]=='.' && ch[i][j]=='#')
                now1=1;
            if (ch[i-1][j]=='.' && ch[i][j]=='#')
                now2=1;
            f[i][j]=min(f[i][j-1]+now1,f[i-1][j]+now2);
        }
    printf("%d\n",f[n][m]);

    return 0;
}
```


---

## 作者：arkerny (赞：0)

这道题是 DP 耶（而且还是比较简单的一种

一开始想到的是 BFS（好像也可以做（（（

不过貌似 DP 更简单。

使用 $dp_{i,j}$ 来表示走到位置 $(i,j)$ 的最小翻转次数。

据题意，只能从左上向右下走，所以对于 $(i,j)$ 只能从 $(i-1,j)$ 和 $(i,j-1)$ 转移。

那么，对于位置 $(i,j)$，只要 $(i-1,j)$ 或 $(i,j-1)$ 翻转过了，且位置 $(i,j)$ 也需要翻转，那么也可以延伸到 $(i,j)$，故翻转次数即为先前点的翻转次数。

而当位置 $(i,j)$ 为 `.` 时，不需要翻转，故翻转次数也为先前点的翻转次数。

不符合上述两种情况时，即位置 $(i,j)$ 需要翻转，故翻转次数加一。

代码如下：

``` cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define il inline

int n,m;
char a[110][110];
int f[110][110];

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",a[i]+1);
    }
    f[1][1]=a[1][1]=='#'?1:0;
    for(int i=2;i<=n;i++)
    {
        if(a[i][1]=='.'||a[i][1]==a[i-1][1])
        {
            f[i][1]=f[i-1][1];
        }
        else
        {
            f[i][1]=f[i-1][1]+1;
        }
    }
    for(int i=2;i<=m;i++)
    {
        if(a[1][i]=='.'||a[1][i]==a[1][i-1])
        {
            f[1][i]=f[1][i-1];
        }
        else
        {
            f[1][i]=f[1][i-1]+1;
        }
    }
    int x,y;
    for(int i=2;i<=n;i++)
    {
        for(int j=2;j<=m;j++)
        {
            x=f[i-1][j]+1;
            y=f[i][j-1]+1;
            if(a[i][j]=='.')
            {
                x=f[i-1][j];
                y=f[i][j-1];
            }
            if(a[i][j]==a[i-1][j])
            {
                x=f[i-1][j];
            }
            if(a[i][j]==a[i][j-1])
            {
                y=f[i][j-1];
            }
            f[i][j]=min(x,y);
        }
    }
    printf("%d",f[n][m]);
    return 0;
}

```

---

## 作者：13802919466djh (赞：0)

[更好的体验？](https://www.luogu.com.cn/blog/dujiahao123456/solution-at5798)

# 解法
因为是网格图，所以我们可以想到用动态规划。
令 $dp(i,j)$ 表示从 $(1,1)$ 走到 $(i,j)$ 的最小操作数。当 $(1,1)$ 为 `#` 时，$dp(1,1)=1$。否则 $dp(1,1)=0$。

对于 $dp(i,j)$，由于只向右或向下移动，所以只能从上方的格子 $dp(i-1,j)$ 和左方的格子 $dp(i,j-1)$ 转移。如果上一个格子是 `.` 且当前格子是 `#`，转移的上一个操作数就得加一。状态转移方程就可以写出来了。具体看代码。

# 代码
**Talking is cheap,show me the code.**
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){int f=1,x=0;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1; ch=getchar();}while (ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}return x*f;}
inline void write(int x){if (x<0){putchar('-');x=-x;}if(x>9) write(x/10);putchar(x%10+'0');}
inline void Write(int x){write(x);putchar('\n');}
const int N=1005;
int n,m,dp[N][N];
char ch[N][N];
signed main(){
    n=read(),m=read();
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            cin>>ch[i][j];
    dp[1][1]=(ch[1][1]=='#');
    for (int i=2;i<=m;i++)dp[1][i]=dp[1][i-1]+((ch[1][i-1]=='.')&&(ch[1][i]=='#'));
    for (int i=2;i<=n;i++)dp[i][1]=dp[i-1][1]+((ch[i-1][1]=='.')&&(ch[i][1]=='#'));
    for (int i=2;i<=n;i++)
        for (int j=2;j<=m;j++)
            dp[i][j]=min(dp[i][j-1]+((ch[i][j-1]=='.')&&(ch[i][j]=='#')),dp[i-1][j]+((ch[i-1][j]=='.')&&(ch[i][j]=='#')));//从两种状态转移
    write(dp[n][m]);
    return 0;
}
```

---

## 作者：pengyule (赞：0)

- 【算法标签】动态规划（初步）
- 【题目要点】
1. 只能向右、下走
2. 只能走白色
3. $n,m\leq100$
- 【题解】设想一条最优路径，它的操作次数一定是在从白色区域走入黑色区域时，需要把一段黑色变成白色，则结果为这条路径中黑色区域的段数（例如 `10001111011`就有 3 段：`1`，`1111`，`11`）。为什么我们翻转一个矩形可以刚好把且仅把这一段黑色区域给变白呢？因为我们只能往右或往下走，因此翻转以这段黑色的第一个格子为左上角、这段黑色的最后一个格子为右下角的矩形就可以达到目的，并且不影响到这条路径中的其他格子。若用 $F_{i,j}$ 表示从起点到 $(i,j)$ 的最少操作次数，则当 $(i,j)$ 不在第一行或第一列时，有 $F_{i,j}=\min\begin{cases}
F_{i-1,j}+\Delta_{(i-1,j)\to(i,j)} \\
F_{i,j-1}+\Delta_{(i,j-1)\to(i,j)}
\end{cases}$
否则，有 $F_{i,j}=\begin{cases}
F_{i,j-1}(i=1,j\neq 1) \\
F_{i-1,j}(j=1,i\neq 1) \\
A_{i-1,j}(i=1,j=1)
\end{cases}$。以上题解中，$A_{i,j}=1$ 表示 `#`，$A_{i,j}=0$ 表示 `.`，从一个黑格子走向一个白格子（须翻转）时 $\Delta_{(x_1,y_1)\to(x_2,y_2)}=1$，反之为 $0$。
- 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f;
int a[105][105],f[105][105];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        getchar();//换行符
        for(int j=1;j<=m;j++){
            a[i][j]=(getchar()=='#');
            f[i][j]=inf;
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            int Up=f[i-1][j]+(!a[i-1][j] && a[i][j]);
            int Left=f[i][j-1]+(!a[i][j-1] && a[i][j]);
            if(i==1) f[i][j]=Left;
            else if(j==1) f[i][j]=Up; 
            else f[i][j]=min(Up,Left);
        }
    cout<<f[n][m]<<endl;
    return 0;
}
```

---

## 作者：feecle6418 (赞：0)

显然，任意 `#` 的连通块都可以用一次操作将其变为 `.`。因此，题目等价于要让黑格子的连通段数最少。

这个可以用双层 BFS 解决：外层用优先队列维护到每个格子的答案，内层用 BFS 找黑格子的连通块。时间复杂度是 $O(n^2\log n)$。

评测链接：https://atcoder.jp/contests/agc043/submissions/11070046

---

