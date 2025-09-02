# [ABC398D] Bonfire

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc398/tasks/abc398_d

在无限广阔的二维网格中，坐标 $(0, 0)$ 处有一堆篝火。  
在时刻 $t=0$ 时，仅单元格 $(0, 0)$ 存在烟雾。

给定一个由 `N`、`W`、`S`、`E` 组成且长度为 $N$ 的字符串 $S$，在时刻 $t=1,2,\dots,N$ 时，将按顺序发生以下现象：

- 风吹过时，当前存在的所有烟雾将按以下规则移动：
  - 若 $S$ 的第 $t$ 个字符为 `N`，则单元格 $(r, c)$ 的烟雾移动到 $(r-1, c)$。
  - 若 $S$ 的第 $t$ 个字符为 `W`，则单元格 $(r, c)$ 的烟雾移动到 $(r, c-1)$。
  - 若 $S$ 的第 $t$ 个字符为 `S`，则单元格 $(r, c)$ 的烟雾移动到 $(r+1, c)$。
  - 若 $S$ 的第 $t$ 个字符为 `E`，则单元格 $(r, c)$ 的烟雾移动到 $(r, c+1)$。
- 若此时单元格 $(0, 0)$ 没有烟雾，则在该位置生成新的烟雾。

高桥君位于坐标 $(R, C)$ 处。  
对于每个整数 $1 \leq t \leq N$，请判断在时刻 $t+0.5$ 时单元格 $(R, C)$ 是否存在烟雾，并按输出格式要求输出结果。

## 说明/提示

### 约束条件

- $N$ 是 $1$ 以上 $200000$ 以下的整数
- $S$ 是由 `N`、`W`、`S`、`E` 组成且长度为 $N$ 的字符串
- $R, C$ 是 $-N$ 以上 $N$ 以下的整数
- $(R, C) \neq (0, 0)$

### 样例解释 1

在时刻 $1.5$、$2.5$、$4.5$、$6.5$ 时，单元格 $(-2, 1)$ 不存在烟雾；在时刻 $3.5$、$5.5$ 时存在烟雾。因此输出 `001010`。  
图示中以篝火所在的单元格 $(0, 0)$ 为基准：
- 若 $r < 0$，则单元格 $(r, c)$ 位于上方 $|r|$ 格
- 若 $r \geq 0$，则单元格 $(r, c)$ 位于下方 $r$ 格
- 若 $c < 0$，则单元格 $(r, c)$ 位于左侧 $|c|$ 格
- 若 $c \geq 0$，则单元格 $(r, c)$ 位于右侧 $c$ 格

各时刻的网格状态如下（以下为原题图片链接，此处保留描述）：
- 时刻 $0.5$：![](https://img.atcoder.jp/abc398/pmRbLy1F_D_t0.png)
- 时刻 $1.5$：![](https://img.atcoder.jp/abc398/pmRbLy1F_D_t1.png)
- 时刻 $2.5$：![](https://img.atcoder.jp/abc398/pmRbLy1F_D_t2.png)
- 时刻 $3.5$：![](https://img.atcoder.jp/abc398/pmRbLy1F_D_t3.png)
- 时刻 $4.5$：![](https://img.atcoder.jp/abc398/pmRbLy1F_D_t4.png)
- 时刻 $5.5$：![](https://img.atcoder.jp/abc398/pmRbLy1F_D_t5.png)
- 时刻 $6.5$：![](https://img.atcoder.jp/abc398/pmRbLy1F_D_t6.png)

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6 -2 1
NNEEWS```

### 输出

```
001010```

## 样例 #2

### 输入

```
10 1 2
NEESESWEES```

### 输出

```
0001101011```

## 样例 #3

### 输入

```
20 -1 -2
WWNNWSWEWNSWWENSNWWN```

### 输出

```
00100111111000101111```

# 题解

## 作者：xxgirlxx (赞：8)

## 题外话
这场 rating 结算的时候显示我正好 rk800，难绷。

这场打完差五分上青，难绷。
## 题目大意

有一团烟雾在 $(0,0)$ 处，高桥在 $(R,C)$ 处，接下来会挂 $N$ 次风，风的信息为 $S$。

若 $S_i=N$，烟雾会从 $(x,y)$ 挪到 $(x-1,y)$。

若 $S_i=W$，烟雾会从 $(x,y)$ 挪到 $(x,y-1)$。

若 $S_i=S$，烟雾会从 $(x,y)$ 挪到 $(x+1,y)$。

若 $S_i=E$，烟雾会从 $(x,y)$ 挪到 $(x,y+1)$。

每次风刮完后，若 $(0,0)$ 处没有烟雾，则 $(0,0)$ 处会生成新的烟雾。

请问每次风刮完后高桥所在的位置有没有烟雾，若有输出 `1`，若没有输出 `0`。

## 题目思路

烟雾太多不好做，考虑移动高桥和篝火。

记录下篝火的路径，若高桥走到了篝火到过的地方就有烟雾，否则没有。

注意高桥和篝火的移动应该跟烟雾反着来。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define mp make_pair
using namespace std;
int n,r,c,x,y;
string s;
map<pair<int,int>,int>m;
signed main(){
	cin>>n>>r>>c>>s,s=' '+s,x=0,y=0,m[mp(x,y)]=1;
	for(int i=1;i<=n;i++){
		if(s[i]=='N'){
			r++,x++;
			m[mp(x,y)]=1;
		}
		else if(s[i]=='S'){
			r--,x--;
			m[mp(x,y)]=1;
		}
		else if(s[i]=='W'){
			c++,y++;
			m[mp(x,y)]=1;
		}
		else{
			c--,y--;
			m[mp(x,y)]=1;
		}
		cout<<m[mp(r,c)];
	}
	return 0;
}
```

---

## 作者：Clover_Lin (赞：4)

[点这里查看原题面。](https://atcoder.jp/contests/abc398/tasks/abc398_d)
## 思路
显然，逐一枚举维护的时间复杂度是不堪设想的。我们可以发现，每一次更新的时候原点处会重新冒烟，接下来向周围飘。我们可以理解为在第 $t+0.5$ 秒，所有有烟的点（先不说原点）为执行第 $i$ 至第 $t$ 次的结果位置（其中 $1 \le i \le t$）。

发现这个规律之后开一个哈希表或者容器维护即可。
## 代码
[赛时已 AC，如有问题请联系作者。](https://atcoder.jp/contests/abc398/submissions/64059582)

---

## 作者：N1tr0us_Acid (赞：4)

非常好的前缀和题，使我的大脑旋转。

# $\texttt{Solution}$
我们可以使用两个前缀和数组，以 $(sumx_i,sumy_i)$ 表示第一团烟雾在时间 $i$ 与 $i + 1$ 之间所处的位置。\
这样，第 $k$ 团烟雾在时间 $i$ 与 $i + 1$ 之间的位置就是 $(sumx_i - sumx_{k - 1},sumy_i - sumy_{k - 1})$。

对于所有的 $1 \le i \le n$，我们可以记录最早出现 $(sumx_i,sumy_i)$ 这一位置的时间。对于第 $i$ 团烟雾，如果在所有的 $1 \le j < i$ 中有位置 $(sumx_i - R,sumy_i - C)$，那么就意味着这团烟雾在时间 $i$ 和 $i + 1$ 之间在位置 $(R, C)$ 上。

# $\texttt{Code}$
很明了了。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 2e5 + 10;

int n, R, C;
int sumx[N], sumy[N];
int ans;
char c[N]; 

typedef pair <int, int> pii;

map <pii, int> mp;

int res[N];

signed main() {
	cin >> n >> R >> C;

	mp[{0, 0}] = -1;

	for (int i = 1; i <= n; i ++) {
		cin >> c[i];
		int dx = 0, dy = 0;

		if(c[i] == 'N') dx = -1;
		if(c[i] == 'W') dy = -1;
		if(c[i] == 'S') dx = 1;
		if(c[i] == 'E') dy = 1;

		sumx[i] = sumx[i - 1] + dx;
		sumy[i] = sumy[i - 1] + dy;

		if(!mp.count({sumx[i], sumy[i]})) mp[{sumx[i], sumy[i]}] = i; // 记录第一次出现该位置时的时间。
	}

	for (int i = 1; i <= n; i ++) {
		ans = 0;

		int nowx = sumx[i] - R, nowy = sumy[i] - C;

		if(mp.count({nowx, nowy}) && mp[{nowx, nowy}] < i) ans ++;
		res[i] = ans;
	}

	for (int i = 1; i <= n; i ++) cout << res[i];

    return 0;
}
```

---

## 作者：endswitch (赞：4)

不妨将一个坐标哈希下来，同时维护一个哈希偏移量懒标记 $tag$。

对于 `W` / `E` 操作，将 $tag$ 加 / 减 $1$，对于 `N` / `S` 操作，将 $tag$ 加 / 减 $N$。

再维护一个 `std :: set`，表示此时有烟的每个点的坐标哈希值。每次查询点对 $(r, c)$ 是否存在于 `std :: set` 中。对于插入一个新节点 `s.insert(-tag)` 即可。

需要注意的是，如果是按行列哈希的话，进制要开大一点。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
int Q, n, m, tag;
char op;
set<int> s;

inline int to(int x, int y) {
	return x * (Q << 3) + y;
}

signed main() {
	ios_base :: sync_with_stdio(NULL);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	cin >> Q >> n >> m;
	
	s.insert(0);
	
	for(int i = 1 ; i <= Q ; ++ i) {
		cin >> op;
		
		if(op == 'N') tag -= (Q << 3);
		else if(op == 'W') -- tag;
		else if(op == 'S') tag += (Q << 3);
		else ++ tag;
		
		s.insert(-tag);
		
//		cerr << "tag:" << tag << ' ' << "to:" << to(n, m) << '\n';	
//		cerr << "\nset:\n";
//		for(auto j : s) cerr << j << ' ';
//		cerr << '\n';
		
		if(s.find(to(n, m) - tag) != s.end()) cout << 1;
		else cout << 0;
		
//		cout << '\n';
	}
	
	return 0;
}
```

---

## 作者：DoubleQLzn (赞：2)

> 考察知识点：set，前缀和
> 
直接记录下所有点肯定不行的。

我们发现只有当烟囱点没有烟的时候才会产生烟。

因此记录偏移量 $nx,ny$，并且做一个前缀和。每次操作后插入即可。

同时由于所有烟都在动，高桥也要跟着他们一起动，才可以使得统计结果准确。因此移动高桥与烟雾，使用一个 set 维护。

由于初始烟囱在 $(0,0)$，一开始先向 set 里插入 $(0,0)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	set<pair<int,int>> s;
	pair<int,int> y,t;
	y = {0,0};
	s.insert(y);
	int n;
	cin >> n >> t.first >> t.second;
	string a;
	cin >> a;
	for (int i = 0;i < a.size();i++)
	{
		if (a[i] == 'S') 
		{
			t.first--;
			y.first--;
		}
		if (a[i] == 'N')
		{
			t.first++;
			y.first++;
		}
		if (a[i] == 'E')
		{
			t.second--;
			y.second--;
		}
		if (a[i] == 'W')
		{
			t.second++;
			y.second++;
		}
		s.insert(y);
		if (!s.count(t)) cout << 0;
		else cout << 1;
	}
	return 0;
}
```

---

## 作者：KobeBeanBryantCox (赞：2)

# AT_abc398_d [ABC398D] Bonfire 题解

--------------

[题目传送门](https://www.luogu.com.cn/problem/AT_abc398_d)。

-------------

## 题意

有一个烟会扩散，问每一时刻会不会扩散到给出的一个位置。

-------------

## 思路

维护所有烟太麻烦了。

你考虑把以人为原点的坐标系（这是移动烟）变成以原本的 $(0,0)$ 为原点的坐标系。

这样就只需要维护人在哪里和原本的 $(0,0)$ 现在在哪里。

说人话就是你把操作反向，移动人和 $(0,0)$ 即可。

然后你用一个 `map<pair<int,int>,bool>` 维护坐标是否有烟即可。

时间复杂度 $O(n\log n)$。

--------------

## AC 代码

```cpp
#include<bits/stdc++.h>
#define Code using
#define by namespace
#define wjb std
Code by wjb;
#define int long long
int in()
{
    int k=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
    return k*f;
}
void out(int x)
{
    if(x<0)putchar('-'),x=-x;
    if(x<10)putchar(x+'0');
    else out(x/10),putchar(x%10+'0');
}
map<pair<int,int>,bool>mp;
signed main()
{
    int n=in(),r=in(),c=in(),xx=0,yy=0;
    mp[{0,0}]=1;
    string s;cin>>s;
    for(int i=0;i<n;i++)
    {
        if(s[i]=='N')r++,xx++;
        else if(s[i]=='W')c++,yy++;
        else if(s[i]=='S')r--,xx--;
        else c--,yy--;
        mp[{xx,yy}]=1;
        out(mp.count({r,c}));
    }
    return 0;
}
```

-----------

若有误或不清，欢迎评论或私信。

---

## 作者：leo120306 (赞：1)

设最开始产生的一朵烟**当前**实际已经移动到了 $(dx,dy)$。

考虑到对已有的烟全部进行移动是 $O(n^2)$ 的，所以不妨令最初的一朵烟坐标始终为 $(0,0)$，把人移动至 $(R-dx,C-dy)$，就可以降为 $O(n)$。

每一次风后会多出一朵烟（与原有的重合也算）。这个烟 的坐标显然应该加在 $(-dx,-dy)$，这样之前的风都刮一遍后它恰好位于 $(0,0)$，也就是烟产生的位置。

使用 `set` 维护烟的位置，时间复杂度 $O(n\log n)$。
```cpp
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
#define N 200005
set<pii>g;int dx,dy;

signed main(){
	int n,x,y;cin>>n>>x>>y;
	g.insert({0,0});
	for(int i=1;i<=n;i++){
		char ch;cin>>ch;
		
		if(ch=='N')dx--;
		else if(ch=='S')dx++;
		else if(ch=='E')dy++;
		else dy--;
		g.insert(pii{-dx,-dy});
		if(g.find(pii{x-dx,y-dy})!=g.end())cout<<'1';
		else cout<<'0';
	}
	
	return 0;
}

---

## 作者：lee_0730 (赞：1)

# 题意：

给定三个数 $N,R,C$，输入一个长度为 $N$ 的字符串 $S$，高桥在坐标为 $(R,C)$ 的位置，在 $(0,0)$ 处有一个篝火，**每秒**会在 $(0,0)$ 处产生一格烟雾，而 $S_i$ 代表的就是第 $i$ 秒烟雾整体平移的方向，求问 $1.5$ 秒到 $N+0.5$ 秒的时间內**每秒**高桥所在的格子是否有烟雾。

# 分析：

如果直接按照题意移动烟雾，明显是会超时 + 超空间的。

分析样例，我们不难发现，从始至终，高桥与营火是**相对静止**的。因此，我们可以把烟雾对于营火和高桥的**相对移动**改为营火和高桥的移动，每次移动判断当前位置是否有烟雾就行了。$N$ 范围为 $2 \times 10^5$，考虑用 **map** 实现，综合时间复杂度为 $O(N \times \log {N} )$。

# code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f first
#define s second
#define fastrd ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define pll pair<ll,ll>
map<pii,int>mp;
int n,a,b,x=0,y=0;
int main(){
	fastrd
	cin>>n>>a>>b;
	for(int i=0;i<n;i++){
		char c;
		cin>>c;
		mp[{x,y}]=1;//在当前位置放置烟雾
		int xx=0,yy=0;
		if(c=='N'){//由于是相对移动，所以所有移动方向是相反的
			xx++;
		}else if(c=='S'){
			xx--;
		}else if(c=='W'){
			yy++;
		}else{
			yy--;
		}
		a+=xx;
		x+=xx;
		b+=yy;
		y+=yy;
		if(mp[{a,b}]){//如果移动到了有烟雾的格子，输出1
			cout<<1;
		}else{
			cout<<0;
		}
	}
}
```

---

## 作者：Tomwsc (赞：1)

# AT_abc398_d [ABC398D] Bonfire 题解

## 思路

首先，直接暴力对每一个格子进行处理肯定是不行的，所以得想一些其它的方法。

容易发现，烟雾的移动其实可以转换成篝火和高桥的移动。什么意思，即：

- 若字符为 ```N```，则篝火和高桥都往下移动。
- 若字符为 ```S```，则篝火和高桥都往上移动。
- 若字符为 ```W```，则篝火和高桥都往右移动。
- 若字符为 ```E```，则篝火和高桥都往左移动。

所以，只需要用一个 ```map``` 存哪些坐标有烟雾，然后在每次处理完后判断一下高桥所在的格子有没有烟雾即可。

时间复杂度：$O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf (1ll << 62)
#define regint register int
#define pb push_back
#define mp make_pair
#define PII pair<int , int>
using namespace std;
const int MAXN = 2e5 + 10;
int n , r , c , cnt;
string s;
map<PII , bool>mapp;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int x , y;
	x = y = 0;
	cin >> n >> r >> c >> s;
	for(regint i = 0;i < n;i ++) {
		mapp[mp(x , y)] = true;
		if(s[i] == 'N')
			x ++;
		else if(s[i] == 'S')
			x --;
		else if(s[i] == 'W')
			y ++;
		else
			y --;
    	//高桥的移动其实便等同于 r 与 c 加上篝火移动的距离
		if(mapp[mp(r + x - 0 , c + y - 0)])
			cout << 1;
		else
			cout << 0;
	}
	return 0;
}
```

---

## 作者：wrh316 (赞：1)

### 思路
由于直接模拟烟雾移动的时间复杂度为 $O(n^2)$，所以我们要进行优化。

因为烟雾的移动可以看作是对所有烟雾位置的偏移，所以如果我们将烟雾的位置看作一个整体，那么每一步的移动可以看作是对所有位置的平移。

只有当 $(0,0)$ 没有烟雾时，才会重新生成烟雾。因此，$(0,0)$ 的烟雾状态是关键。

因为我们需要判断在每一步后，$(r,c)$ 是否有烟雾，所以我们可以通过记录烟雾的位置，快速判断。

因为每一次的操作为 $O(\operatorname{log} n)$，所以总时间复杂度为 $O(n \operatorname{log} n)$。

### 代码
```c++
#include <bits/stdc++.h>
using namespace std;

int n, r, c, x, y;
string s;
set<pair<int, int>> a;
bool vis = true;
int main() {
	cin >> n >> r >> c >> s;
	a.insert({0, 0});
	for (int i = 0; i < n; i++) {
		switch (s[i]) {
			case 'N':
				x--;
				break;
			case 'W':
				y--;
				break;
			case 'S':
				x++;
				break;
			case 'E':
				y++;
				break;
		}
		if (a.find({r - x, c - y}) != a.end()) cout << 1;
		else cout << 0;
		if (a.find({-x, -y}) == a.end()) {
			a.insert({-x, -y});
			vis = true;
		} else vis = false;
		if (!vis) {
			a.insert({-x, -y});
			vis = true;
		}
	}
	return 0;
}
```

---

## 作者：JXR_Kalcium (赞：1)

## 题目大意

存在一个无限大的矩阵，初始时 $(0,0)$ 被染色，时间 $t=0$。给定一个长为 $N$ 的操作串 $S$，对于 $t=i$ 时，若 $s_i=\text{N}$ 则将所有被染色的格子 $(x,y)$ 移动至 $(x-1,y)$，若 $s_i=\text{S}$ 则将所有被染色的格子 $(x,y)$ 移动至 $(x+1,y)$，若 $s_i=\text{E}$ 则将所有被染色的格子 $(x,y)$ 移动至 $(x,y+1)$，否则将所有被染色的格子 $(x,y)$ 移动至 $(x,y-1)$，然后再将 $(0,0)$ 染色。现在对于每个 $t\in[1,N]$，求出在 $t+0.5$ 时刻时 $(R,C)$ 是否被染色，数据范围 $N\le 2\times 10^5$。

## 解题思路

首先不妨只关注 $t=0$ 时染色的这个格子 $G$ 的移动轨迹。拿样例 $2$ 举例，此时 $(R,C)=(1,2)$，则这个格子 $G$ 的移动轨迹为

| 时间 $t$ | $0$ | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ | $7$ | $8$ | $9$ | $10$ |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| **$x$ 坐标** | $0$ | $-1$ | $-1$ | $-1$ | $0$ | $0$ | $1$ | $1$ | $1$ | $1$ | $2$ |
| **$y$ 坐标** | $0$ | $0$ | $1$ | $2$ | $2$ | $3$ | $3$ | $2$ | $3$ | $4$ | $4$ |

在 $t=4$ 时，$(1,2)$ 已经被染色，但 $G$ 坐标为 $(0,2)$，说明肯定在某一时刻在 $G$ 的下面一格染了色，那就只有在 $t=1$ 时 $G(-1,0)$，此时 $(0,0)$ 才会新染一次色，之后才会随之移动。可以发现，若在某一时刻 $G'$ 在 $(0,0)$ 染了色，则在之后的所有时刻中，$G$ 和 $G'$ 的相对位置关系永远不变。于是假设在某一时刻有 $G'(R,C)$，而 $G(x,y)$，则当 $G'(0,0)$ 时（也就是刚染色的时候），一定有 $G(x-R,y-C)$，故只需计算出每个时刻 $G$ 的坐标，若在前面某个时刻有 $G(x-R,y-C)$ 则说明在这个时刻时，必定在 $(R,C)$ 有染色，否则就没有。此处可以使用 `unordered_map` 实现，时间复杂度 $O(N)$。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll n,x,y,sumx,sumy;
char s[200001];
unordered_map<ll,unordered_map<ll,bool>> bz;

int main()
{
    n=read(); x=read(); y=read();
    scanf("%s",s); bz[0][0]=1;

    for(R int i=0; i<n; ++i)
    {
        if(s[i]=='N') --sumx; else if(s[i]=='S') ++sumx;
        else if(s[i]=='E') ++sumy; else --sumy;
        write(bz[sumx-x][sumy-y]); bz[sumx][sumy]=1;
    }

    return 0;
}
```

---

## 作者：Lyw_and_Segment_Tree (赞：0)

## 开始解题！

事实上是很简单的一个题。

考虑烟静止不动。

那么此时假如风向左吹，相当于人和篝火都向右走了，并且篝火产生了一团烟，这样可以保证相对位置不会改变。

所以我们用 `set` 记录篝火走过的每一个位置，如果存在这次操作使得人走到了此前篝火曾经走到的位置那么就输出 `1`，反之输出 `0`。

注意一开始要把 $(0, 0)$ 这个点扔到 `set` 里面去，每一次操作完也要把当前篝火的位置 $(x, y)$ 扔到 `set` 里面。

时间复杂度 $O(n \log n)$，代码是简单的。

code ：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define vec vector
#define pll pair<ll, ll>
#define mkp make_pair
#define endl "\n"

using namespace std;

const ll mod = 998244353;

namespace fastio {
    char buf[1 << 21], *p1 = buf, *p2 = buf;
	
    const ll getc() {
        return p1 == p2 && ( p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++;
    }
	
    const ll read() {
        ll x = 0, f = 1;
		
        char ch = getc();
		
        while (ch < '0' || ch > '9') {
            if (ch == '-') f = -1; ch = getc();
        }
		
        while (ch >= '0' && ch <= '9') {
            x = (x << 1) + (x << 3) + (ch ^ 48), ch = getc();
        }
		
        return x * f;
    }
	
    const void write(ll x) {
        if (x < 0) {
            putchar('-'), x = -x;
        }
		
        ll sta[35], top = 0;
	    
        do {
            sta[top++] = x % 10, x /= 10;
        } while (x);
	    
        while (top) putchar(sta[--top] + 48);
    }
}

#define rd fastio::read
#define wt fastio::write
#define gc fastio::getc

ll n, m, q, a[200005]; string s;

ll opt, l, r, ans = 0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    ll i, j, k, x, y, z, res = 0, now;

    cin >> n >> l >> r >> s; pll nw; nw.first = nw.second = 0;

    set<pll> st; st.insert(nw);

    for (i = 0; i < n; i++) {
        if (s[i] == 'N') {
            nw.first ++, l++;
        } else if (s[i] == 'W') {
            nw.second ++, r++;
        } else if (s[i] == 'E') {
            nw.second --, r--;
        } else {
            nw.first --, l--;
        }

        st.insert(nw);

        cout << (st.find(mkp(l, r)) != st.end() ? 1 : 0);
    }

    return 0;
}
```

[AC record](https://atcoder.jp/contests/abc398/submissions/64115515)

---

## 作者：SunburstFan (赞：0)

## D - Bonfire

### 题目大意

给定在无限二维平面上的一个焰火位置 $(0, 0)$，每个时刻烟雾会按照方向移动，若时刻 $t$ 烟雾不在 $(0,0)$，则在 $(0,0)$ 处重新生成烟雾。我们要判断在每个半时刻 $(t+0.5)$ 时，给定坐标 $(R, C)$ 是否存在烟雾。

### 解题思路

使用一个哈希集合保存已出现过烟雾的坐标。模拟每次风向移动，将当前位置偏移量与目标坐标 $(R, C)$ 比较，通过哈希集合检查是否存在烟雾。

**代码**

```cpp
struct P{
    int r,c;
    bool operator==(const P &o)const{
        return r==o.r&&c==o.c;
    }
};

struct Hash{
    size_t operator()(const P &p)const{
        return (size_t)p.r*13131u^(size_t)p.c;
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    
    int n,r,c;
    cin>>n>>r>>c;
    string s;
    cin>>s;
    
    unordered_set<P,Hash> st;
    st.insert({0,0});
    
    int x=0,y=0;
    string ans;
    ans.resize(n);
    
    for(int i=0;i<n;i++){
        char d=s[i];
        if(d=='N')x--;
        if(d=='S')x++;
        if(d=='W')y--;
        if(d=='E')y++;
        
        P t={x-r,y-c};
        if(st.find(t)!=st.end())
            ans[i]='1';
        else
            ans[i]='0';
        
        P cur={x,y};
        if(st.find(cur)==st.end())
            st.insert(cur);
    }
    
    cout<<ans<<"\n";
    return 0;
}
```

---

## 作者：player_1_Z (赞：0)

### 先来理解题目

[atcoder 原题](https://atcoder.jp/contests/abc398/tasks/abc398_d)

### 思路

首先可以发现直接模拟不太现实，所以想到可以把每个烟的位置存进一个桶，每个时间判断这个人的位置有没有烟。同时可以想到一种优化，把第一个烟的位置设为原点，每次吹风改变人和新产生的烟的位置。具体如下代码。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,r,c,a,b,x,y;
string s;
map<int,map<int,int>> m;
int main(){
	cin>>n>>r>>c>>s;
	m[0][0]=1;//第一朵云 
	r=-r;//atcoder的坐标系很离谱，所以把y轴反转了了 
	ax[0][1]=0,ax[0][2]=0;
	for(int i=0;i<n;i++){
		//因为现在每次吹风烟不动，所以需要让人往反方向动（新产生的云同理） 
		if(s[i]=='N') a--,x--;
		else if(s[i]=='W') b++,y++;
		else if(s[i]=='S') a++,x++;
		else if(s[i]=='E') b--,y--;
		m[x][y]=1;//这个地方有云 
		if(m[r+a][c+b]) cout<<"1";//a,b代表人走的x和y轴上的移动 
		else cout<<"0";
	}
	return 0;
}
```

---

## 作者：cyq32ent (赞：0)

比 E 和 F 难。

假如现在是时刻 $t$，最初的烟现在蔓延到了 $P_t$ 位置，那么 $i$ 时刻的烟现在在 $P_t-P_i$。所以，烟蔓延到了 $(R,C)$ 即存在 $i$，使得 $P_i=P_t-(R,C)$。这样就好算了。

```cpp
#include<bits/stdc++.h>
using namespace std;
pair<int,int>A[4]={{-1,0},{0,-1},{1,0},{0,1}};
map<char,int>M={{'N',0},{'W',1},{'S',2},{'E',3}};
pair<int,int>ad(pair<int,int>A,pair<int,int>B){return {A.first+B.first,A.second+B.second};}
pair<int,int>su(pair<int,int>A,pair<int,int>B){return {A.first-B.first,A.second-B.second};}
map<pair<int,int>,int>m;
int main(){
	int N,R,C;string s;
	cin>>N>>R>>C;
	cin>>s;
	pair<int,int>P={0,0},Q={R,C};
	for(auto c:s){
		auto delta=A[M[c]];
		P=ad(P,delta);
		if(P==Q||m[su(P,Q)])cout<<"1";
		else cout<<"0";
		m[P]=1;
	}
	
	return 0;
}
```

---

## 作者：Graph_Theory (赞：0)

### 思路

因为烟会动，所以我们可以让烟静止，动火炉和人。

用 $mp$ 记录下 $(x,y)$ 区域是否有烟。

如果 $(x-r,y-c)$ 即还原完烟动人不动的位置有烟就输出 $1$。
### 代码
```cpp
map<pair<int,int>,bool> mp;
int main()
{
	mp[{0,0}]=1;
	cin >> n >> r >> c >> s;
	s='@'+s;
	for (int i = 1;i<=n;i++)
	{
		if (s[i]=='N') x--;
		if (s[i]=='W') y--;
		if (s[i]=='S') x++;
		if (s[i]=='E') y++;
		mp[{x,y}]=1;
		cout << mp[{x-r,y-c}];
	}
	return 0;
} 
```

---

## 作者：_sin_ (赞：0)

注意到移动烟雾非常的困难，但是移动人和火堆是简单的。

考虑将移动烟雾转换为移动火堆，火堆每移动到一个为止就在那个位置上放置一个烟雾，用哈希表或者 map 处理即可。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mkp(x,y) make_pair(x,y)
using namespace std;

ll read(){
    ll x=0,f=1;char ch=getchar_unlocked();
    while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar_unlocked();}
    while('0'<=ch&&ch<='9'){x=x*10+ch-'0';ch=getchar_unlocked();}
    return f*x;
}

const int N = 2e5+5;
int n,x,y,p=0,q=0;
char s[N],ans[N];
map<pair<int,int>,bool>vis;

int main(){vis[mkp(0,0)]=1;
    n=read();x=read(),y=read();
    scanf("%s",s+1);for(int i=1;i<=n;i++){
        if(s[i]=='N')p++,x++;
        if(s[i]=='S')p--,x--;
        if(s[i]=='W')q++,y++;
        if(s[i]=='E')q--,y--;
        vis[mkp(p,q)]=1;
        ans[i]=vis[mkp(x,y)]?'1':'0';
    }puts(ans+1);
    return 0;
}
```

---

## 作者：_Accepted_100 (赞：0)

## solution

直接暴力肯定不行，考虑反着暴力。

发现第 $t$ 时刻从原点的烟雾与前面的指令都无关，想到前缀和描述指令。

具体来说，设 $c$ 数组描述南北方向量的前缀和，设 $d$ 数组为东西方向量的前缀和，那么对于时刻 $t$ 从原点的烟雾，若在时刻 $now$ 的时刻到达了目的地，那么应 $c_{now} - c_{t} = r$ 和 $d_{now} - d_{t} = c$ 然后就可以推出 $c_{now} = r + c_{t}$ 和 $d_{now} = c + d_{t}$，然后每一次算出当前等式右边的值，存到一个 map 里面去就可以了。

## code

```
#include <bits/stdc++.h>
using namespace std;

int n, a, b;
int c[2000010], d[2000010];

map <pair <int, int>, bool> m;

int main () {
	cin >> n >> a >> b;
	m[make_pair (a, b)] = 1;
	for (int i = 1; i <= n; i++) {
		char ch;
		cin >> ch;
		c[i] = c[i - 1];
		d[i] = d[i - 1];
		if (ch == 'N') c[i]--;
		if (ch == 'S') c[i]++;
		if (ch == 'E') d[i]++;
		if (ch == 'W') d[i]--;
		m[make_pair (c[i] + a, d[i] + b)] = 1;
		if (m[make_pair (c[i], d[i])]) cout << 1;
		else cout << 0;
	}
	return 0;
}
```

---

## 作者：wmrqwq (赞：0)

这是一篇视频题解。

![](bilibili:BV1E5XWYKE3n?t=194)

[参考代码](https://atcoder.jp/contests/abc398/submissions/64054966)

---

