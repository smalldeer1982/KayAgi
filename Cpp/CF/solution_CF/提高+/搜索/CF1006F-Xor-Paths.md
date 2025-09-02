# Xor-Paths

## 题目描述

There is a rectangular grid of size $ n \times m $ . Each cell has a number written on it; the number on the cell ( $ i, j $ ) is $ a_{i, j} $ . Your task is to calculate the number of paths from the upper-left cell ( $ 1, 1 $ ) to the bottom-right cell ( $ n, m $ ) meeting the following constraints:

- You can move to the right or to the bottom only. Formally, from the cell ( $ i, j $ ) you may move to the cell ( $ i, j + 1 $ ) or to the cell ( $ i + 1, j $ ). The target cell can't be outside of the grid.
- The xor of all the numbers on the path from the cell ( $ 1, 1 $ ) to the cell ( $ n, m $ ) must be equal to $ k $ (xor operation is the bitwise exclusive OR, it is represented as '^' in Java or C++ and "xor" in Pascal).

Find the number of such paths in the given grid.

## 说明/提示

All the paths from the first example:

- $ (1, 1) \rightarrow (2, 1) \rightarrow (3, 1) \rightarrow (3, 2) \rightarrow (3, 3) $ ;
- $ (1, 1) \rightarrow (2, 1) \rightarrow (2, 2) \rightarrow (2, 3) \rightarrow (3, 3) $ ;
- $ (1, 1) \rightarrow (1, 2) \rightarrow (2, 2) \rightarrow (3, 2) \rightarrow (3, 3) $ .

All the paths from the second example:

- $ (1, 1) \rightarrow (2, 1) \rightarrow (3, 1) \rightarrow (3, 2) \rightarrow (3, 3) \rightarrow (3, 4) $ ;
- $ (1, 1) \rightarrow (2, 1) \rightarrow (2, 2) \rightarrow (3, 2) \rightarrow (3, 3) \rightarrow (3, 4) $ ;
- $ (1, 1) \rightarrow (2, 1) \rightarrow (2, 2) \rightarrow (2, 3) \rightarrow (2, 4) \rightarrow (3, 4) $ ;
- $ (1, 1) \rightarrow (1, 2) \rightarrow (2, 2) \rightarrow (2, 3) \rightarrow (3, 3) \rightarrow (3, 4) $ ;
- $ (1, 1) \rightarrow (1, 2) \rightarrow (1, 3) \rightarrow (2, 3) \rightarrow (3, 3) \rightarrow (3, 4) $ .

## 样例 #1

### 输入

```
3 3 11
2 1 5
7 10 0
12 6 4
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 4 2
1 3 3 3
0 3 3 2
3 0 1 1
```

### 输出

```
5
```

## 样例 #3

### 输入

```
3 4 1000000000000000000
1 3 3 3
0 3 3 2
3 0 1 1
```

### 输出

```
0
```

# 题解

## 作者：jdsb (赞：14)

## 题意
给出一个矩阵，求出从左上角到右下角所经过的点的点权异或和为k的路径数

## 分析
首先我们发现$n$，$m$的范围很小，只有20，所以可以考虑搜索，开一个$map$数组$s[i][j][k]$，表示走到$(i,j)$时，异或和为$k$的路径数，但是此时的时间复杂度为$2^{40}$，会发现还是要T，所以我们就要优化。考虑双向搜索，以对角线为界限，第一个dfs记录从左上角到对角线的方案，第二个dfs从右下角出发，每当走到对角线时就累计答案，这时时间复杂度就能优化到$2^{20}$。这样就不会T了。一些细节在代码里有说明。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,m;
ll k,a[25][25],ans;
map<ll,ll> s[25][25];
void dfs1(int x,int y,ll sum)
{
	if(x>n||y>m) return;
	//以(n+m)/2+1为对角线，到达这里时就退出 
	if(x+y==(n+m)/2+1)
	{
		++s[x][y][sum];
		return;
	}
	dfs1(x+1,y,a[x+1][y]^sum);
	dfs1(x,y+1,a[x][y+1]^sum);
	//只向下边和右边走 
}
void dfs2(int x,int y,ll sum)
{
	if(x<1||y<1) return;
	if(x+y==(n+m)/2+1)
	{
		ans+=s[x][y][sum^k^a[x][y]];
		/*一个小技巧，一个数异或两次等于没异或，从头到(x,y)
		和从尾到(x,y)都异或了一次，在异或一次才算异或过它*/ 
		return;
	}
	dfs2(x-1,y,a[x-1][y]^sum);
	dfs2(x,y-1,a[x][y-1]^sum);
	//反向dfs，只向上边和左边走 
}
int main()
{
	scanf("%d%d%lld",&n,&m,&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%lld",&a[i][j]);
	dfs1(1,1,a[1][1]);
	dfs2(n,m,a[n][m]);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：psychosocial (赞：6)

首先我们看一看这个题的题面

**大意就是从起点左上角走到终点右下角，只能向下或向右走，计算一下路上异或和为k的路径有多少**

下面开始构造代码

首先看看直接爆搜的复杂度算出来是2的（m+n）次方，这个数处在一个不上不下的位置，实在是不太确定能不能过掉，正好处在被卡时间限制的边缘。

所以我们就可以稍微优化一点点思路，即更高端的操作

# 双向搜索

这个noip好像不考但是学学也没坏处额开拓一下思路

双向搜索顾名思义就是两个方向的搜索，从左上和右下两个方向同时开始广搜，一起向中间靠拢，这样就能保证时间不超（但其实时间依然很长），保证了时间复杂度是2的（m+n）/2次方。

上代码吧，比较丑而且十分模板化，加了一点点判断异或的操作而已（记代码的我逃走）

从左上跑一半，右下跑一半，
跑到相同点时将答案传回


这里我用的双向dfs



	#include<bits/stdc++.h>
	using namespace std;
	typedef long long ll;
	int n,m;
	ll k,a[25][25];
	map<ll,ll> dp[25];
	void dfs(int x,int y,ll s) 
	{
		if (x>n||y>m) return;
		if ((x+y)==(n+m)/2+1) 
	{
		dp[x][s^a[x][y]]++;
		return;

	}
		dfs(x+1,y,s^a[x][y]);//操作一波每个格子上的异或运算
		dfs(x,y+1,s^a[x][y]);

	}
		ll sm(int x,int y,ll s) 
	{
   	 if (x<1||y<1) 
		return 0;
		if ((x+y)==(n+m)/2+1) 
		return dp[x][s];
		return sm(x-1,y,s^a[x][y])+sm(x,y-1,s^a[x][y]);
	}
	int main()
	{ 
    	scanf("%d%d%lld",&n,&m,&k);
    for(int i=1; i<=n; i++)
      for(int j=1; j<=m; j++)  
        scanf("%lld",&a[i][j]);
    dfs(1,1,0);
    printf("%lld\n",sm(n,m,k));
      return 0;  
	}


---

## 作者：Heartlessly (赞：3)

## Description

给定一个 $n \times m$ 的网格，每个格子的权值为 $a_{i,j}$，现在要从 $(1,1)$ 走到 $(n,m)$，求异或和等于 $k$ 的路径数。

$(1 \leq n,m \leq 20,0 \leq a_{i,j},k \leq 10^{18})$


## Solution

$n,m$ 的范围很小，所以考虑搜索。

直接暴搜显然不行，因为路径数很多。

所以使用 **折半搜索** 。

从起点和终点开始分别搜索，搜到对角线停止，设路径总数为 $k$，则时间复杂度可以降为 $O(\sqrt k)$ 。

起点开始只能向下或向右走，终点开始只能向上或向左走，注意边界。

![E5JeZ6.png](https://s2.ax1x.com/2019/05/13/E5JeZ6.png)

我们可以开一个 $\rm map$ 存下从 $(1,1)$ 到对角线上的点 $(x,y)$ 异或和为 $val$ 的路径数。第二次搜到 $(x,y)$ 时，若当前异或和为 $val$，则答案需要加上从 $(1,1)$ 到 $(x,y)$ 异或和为 $k \oplus val$ 的路径数（$\oplus$ 表示异或，异或的逆运算也是异或）。

怎么判断 $(x,y)$ 是否在对角线上？只要看 $x+y$ 是否与 $\left \lfloor \frac{n + m}{2} \right \rfloor + 1$ 相等即可（对角线是一次函数）。至于为什么 $+1$，是因为能够防止 $n = m = 1$ 的情况出错。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}

template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

const int MAXN = 20;
int n, m;
LL k, ans, a[MAXN + 5][MAXN + 5];
map<LL, LL> cnt[MAXN + 5][MAXN + 5];

void dfs1(int x, int y, LL val) {//表示当前到点 (x,y)，路径异或和为 val 
    if (x + y == (n + m) / 2 + 1) {
        ++cnt[x][y][val];//统计 (1,1) -> (x,y) 异或和为 val 的路径数 
        return;
    }
    if (x < n) dfs1(x + 1, y, val ^ a[x + 1][y]);
    if (y < m) dfs1(x, y + 1, val ^ a[x][y + 1]);
}

void dfs2(int x, int y, LL val) {
    if (x + y == (n + m) / 2 + 1) {//搜到对角线就停止
        ans += cnt[x][y][k ^ val ^ a[x][y]];
        //这里异或 a[x][y] 是因为第二次到这个点多异或了 (x,y) 一次，
        //而第一次到 (x,y) 时已经异或过了，再异或一次相当于只保留一次异或 
        return;
    }
    if (x > 1) dfs2(x - 1, y, val ^ a[x - 1][y]);
    if (y > 1) dfs2(x, y - 1, val ^ a[x][y - 1]);
}

int main() {
    read(n), read(m), read(k);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            read(a[i][j]);
    dfs1(1, 1, a[1][1]), dfs2(n, m, a[n][m]);
    write(ans);
    putchar('\n');
    return 0;
}
```

---

## 作者：Wichiene (赞：3)

## 第一个双向dfs  
### 啊

# 题目翻译
有n*m的格子，从（1，1）走到（n，m），只能向下/右走。
每个格子上有权值，求走过格子的权值的异或和=k的方案数

（语文太差了我尽力了

从前往后搜，然后从后往前搜
到对角线上的点就停下，统计方案数

代码
———————————————————————————————
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<cmath>
#include<map> 
#define ll long long
using namespace std;
map<ll,ll>mp[21][21];//我觉得int也可以emmmm
ll tot,k,a[21][21];
ll n,m;
void dfs(ll x1,ll y1,ll v1)//x1,y1:坐标；v1：异或和
{
	if(x1+y1==n+1)//对角线
	{
		mp[x1][y1][v1]++;//到这里，异或和是v
		return;
	}
	
	if(x1<n)dfs(x1+1,y1,v1^a[x1+1][y1]);
	if(y1<m)dfs(x1,y1+1,v1^a[x1][y1+1]);//往后搜
 } 
 void dfss(ll x2,ll y2,ll v2)
{
	if(x2+y2==n+1)
	{
		tot+=mp[x2][y2][v2^k^a[x2][y2]];
        //上一句：~~组织语言……emmm……弃疗~~
        //见下面吧。。。dalao随意。。。~~比我菜的真的有吗。。不写可以吗。。~~
		return;
	}
	if(x2>1)dfss(x2-1,y2,v2^a[x2-1][y2]);
	if(y2>1)dfss(x2,y2-1,v2^a[x2][y2-1]);//往前搜
 } 
int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	cin>>a[i][j];
	dfs(1,1,a[1][1]);
	dfss(n,m,a[n][m]);//没了
	cout<<tot; 
}
```
上面的那个地方

1.不要把x1，y1..再。亦或。一遍。了。^的逆运算就是^, a^b^b=a.
还有a^b=c则a^c=b.

2.上面统计了到x1,y1的异或和为v1的方案数。我们就~~硬生生~~把它接起来，如果这次搜索到x1，y1的异或和为v1^k，那么就是有mp[x1][y1][v1]的方案了

3.没有3

另外，不用回溯也无所谓判重。毕竟他好像走不回来

~~再另外。。感谢一下wjh和zhn。。大佬~~

---

## 作者：封禁用户 (赞：2)

~~难得会做的F题~~
# 核心算法:折半搜索

直接搜索虽然可行，但复杂度难以忍受....

呀，既然给我们了起点和终点，而且统计的是路径和，

折半搜索不就吼了～

通过简单分析，$(n+m+2)/2$为中间的位置。
又因若$a \oplus b=k$，则$k \oplus b=a$这一性质。
将搜索到一半时的异或和存在一个map里面即可。
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <stack>
#include <utility>
#include <functional>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define RI register int 
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const int maxn=100010;
inline ll read(){
    char ch=getchar();ll x=0,f=1;
    while(ch<'0'||ch >'9') {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while('0'<=ch&&ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
inline void print(ll k){
    if(k<0) k=-k,putchar('-');
    if(k>9) print(k/10);
    putchar(k%10+48);
}
ll ans;
ll n,m,k;
ll mapp[25][25];
map<ll,ll> mp[25][25];
void dfs(ll xx,ll yy,ll cur){
    if(xx<1||xx>n||yy<1||yy>m) return ;
    cur^=mapp[xx][yy];
    if(xx+yy==(n+m+2)>>1){
        mp[xx][yy][cur]++;
        return;
    }
    dfs(xx+1,yy,cur);
    dfs(xx,yy+1,cur);
}
//千万不要在dfss里面调用dfs...
//必须再写一遍，又犯这种脑残错....
void dfss(ll xx,ll yy,ll cur){
    if(xx<1||xx>n||yy<1||yy>m) return ;
    if(xx+yy==(n+m+2)>>1){
        ans+=mp[xx][yy][k^cur];
        return;
    }
    cur^=mapp[xx][yy];
    dfss(xx-1,yy,cur);
    dfss(xx,yy-1,cur);
}
int main(){
    //freopen("xor.in","r",stdin);
    //freopen("xor.out","w",stdout);
    n=read();
    m=read();
    k=read();
    rep(i,1,n)
        rep(j,1,m)
            mapp[i][j]=read();
    dfs(1,1,0);
    dfss(n,m,0);
    print(ans);
    putchar('\n');
    return 0;
}
```

---

## 作者：昤昽 (赞：1)

[CF1006F Xor Paths](https://www.luogu.org/problemnew/show/CF1006F)  

这道题如果范围在10以内的话,可以用普通的$bfs$搜过,但是因为范围到达$20$,普通的搜索会炸.因此需要换个算法.

因为起点wei固定点$(1,1)$,重点也为固定点$(n,m)$,且到达终点时的"异或和"为固定值$k$,因此可以考虑使用"双向广度优先搜索".

先设定一条"终点线",正搜反搜到达终点线时都停止.如果在同一个点有重合的状态,则可以统计答案.

因为正反都只搜大约一半,因此与搜索一个$n \leq 10$ 的矩阵相当,不会TLE

```cpp
#include <iostream>
#include <queue>
#include <map>

using namespace std;

typedef long long LL;

const int  MAXN = 20+5;

struct State{
    int x,y;
    LL val;
    State(int a=0,int b=0,LL v=0):x(a),y(b),val(v){}
};

int n,m,mid;
LL a[MAXN][MAXN],k;

map<LL,int>MAP[MAXN << 1];

bool valid(int x,int y)
{
    return x>=1 && x<=n && y>=1 && y<=m;
}
int main()
{
//	freopen("xor.in","r",stdin);

    cin >> n >> m >> k;
    mid = (n+m+2) >> 1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) cin >> a[i][j];

    LL ans = 0;

    queue<State>q;
    q.push(State(1,1,a[1][1]));
    while(!q.empty())
    {
        State u = q.front(); q.pop();
        int x = u.x,y = u.y;
        LL val = u.val;
        if(x + y == mid)
        {
            if(MAP[x].count(val)) ++MAP[x][val];
            else MAP[x][val] = 1;
        }
        else
        {
            if(valid(x+1,y)) q.push(State(x+1,y,val^a[x+1][y]));
            if(valid(x,y+1)) q.push(State(x,y+1,val^a[x][y+1]));
        }
    }

    q.push(State(n,m,k));
    while(!q.empty())
    {
        State u = q.front(); q.pop();
        int x = u.x,y = u.y;
        LL val = u.val;
        if(x + y == mid) ans += MAP[x][val];
        else
        {
            if(valid(x-1,y)) q.push(State(x-1,y,val^a[x][y]));
            if(valid(x,y-1)) q.push(State(x,y-1,val^a[x][y]));
        }
    }

    cout << ans << endl;
}
```

~~调试了两天原来是把一个减号写成了加号...~~

---

## 作者：VenusM1nT (赞：1)

$\texttt{Meet in the middle}$。

大水题一道。首先考虑直接爆搜，肯定会超时不用想，复杂度高达 $2^{40}$，但是如果对其折半的话，就是 $2\times2^{20}$ 的复杂度，这个是完全可以接受的，所以我们矩阵折半，从 右上-左下 对角线分开，先搜左上这一块，把搜出的异或和记录在 $\texttt{map}$ 里，再搜右下角，假如我们搜出的异或和为 $\text{cnt}$，那么我们只需要找一下 $\texttt{map}$ 里有多少个 $\text{k xor cnt}$ 与之对应即可。

```cpp
#include<bits/stdc++.h>
#define MAXN 25
#define reg register
#define inl inline
#define int long long
using namespace std;
map <int,int> mp[MAXN][MAXN];
int n,m,k,a[MAXN][MAXN],lim,ans;
void Dfs1(reg int x,reg int y,reg int cnt)
{
	if(x<1 || x>n || y<1 || y>m) return;
	cnt^=a[x][y];
	if(x+y==lim)
	{
		mp[x][y][cnt]++;
		return;
	}
	Dfs1(x+1,y,cnt);
	Dfs1(x,y+1,cnt);
}
void Dfs2(reg int x,reg int y,reg int cnt)
{
	if(x<1 || x>n || y<1 || y>m) return;
	if(x+y==lim)
	{
		ans+=mp[x][y][cnt^k];
		return;
	}
	cnt^=a[x][y];
	Dfs2(x-1,y,cnt);
	Dfs2(x,y-1,cnt);
}
signed main()
{
	scanf("%lld %lld %lld",&n,&m,&k);
	for(reg int i=1;i<=n;i++)
	{
		for(reg int j=1;j<=m;j++) scanf("%lld",&a[i][j]);
	}
	lim=(n+m+2)/2;
	Dfs1(1,1,0);
	Dfs2(n,m,0);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Parat_rooper (赞：0)

# 题面翻译：
给定一个n*m的矩阵，要从左上角(1,1)走到右下角(n,m)，每次只能朝右走或者朝下走，求路径的异或和为k的方案数。

## 解题思路：
首先确定直接搜索肯定会挂，必须要优化

**那么如何优化呢？**

这就引出了我们的双向搜索

**双向搜索**

~~又名众人拾柴火焰高一头搜太慢我两头搜还挂就怪了搜索~~   
~~这种搜索的精髓就在于你看上去似乎代码更复杂了，但其实你的速度“噌噌噌”地往上涨~~


**瞎扯结束。。。**

------------

我们确定双向搜索是比较优的，那么现在考虑搜索方法：
1. 肯定要有两个方向（从（1,1）开始和从（n,m）开始）
2. 递归终止条件  （肯定是在中间的某一条线上，就假设它是（n+m）/2好了）
3. $ans$ 更新的条件（我们要用一个 $unordered\_map$ 或 $map$ 来存到第一次搜索到那一条线的不同的异或值方案数， 然后在第二次搜索中，一旦到了这个点就加上一次第一次搜索到这的相统异或值的方案数）

**上代码：**
```cpp
#include <iostream>
#include <unordered_map>

using namespace std;

const int kMaxN = 21;

unordered_map<long long, long long>mymap[kMaxN][kMaxN];

int n, m;
long long ans, k, a[kMaxN][kMaxN];

void dfs1(int x, int y, long long d)
{
  d = d ^ a[x][y];
  if ((x + y) == ((n + m + 2) / 2))
  {
    mymap[x][y][d]++;
    return;
  }
  if (x < n) {
    dfs1(x + 1, y, d);
  } 
  if (y < m) {
    dfs1(x, y + 1, d);
  }
}

void dfs2(int x, int y, long long d) 
{
  if ((x + y) == ((n + m + 2) / 2)) {
    ans += mymap[x][y][d];
    return;
  }
  d = d ^ a[x][y];
  if (x > 1) {
    dfs2(x - 1, y, d);
  }
  if (y > 1) {
    dfs2(x, y - 1, d);
  }
}

int main() {
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }
  dfs1(1, 1, 0);
  dfs2(n, m, k);
  cout << ans;
  return 0;
}
```


---

## 作者：永不复行 (赞：0)

自以为之前的题解不适合像我一样的粗心人
dp可以二维，也可以压成一维，反正map垫着；

一定要防越界，计算时由于a^b^b=a,有了统计的方法
(k^fnw=nw)

```
#include<bits/stdc++.h>
using namespace std;
std::map<long long,long long> dp[450];
long long sum=0,n,m,a[25][25],k;
void dfs(int x,int y,long long nw)
{
	if((x+y)==(n+m)/2+1) 
	{
    	dp[21*x+y][nw^a[x][y]]++;
    	return;
	}
	else 
	{
		if(x<n)dfs(x+1,y,nw^a[x][y]);
		if(y<m)dfs(x,y+1,nw^a[x][y]);
	}
}
void fdfs(int fx,int fy,long long fnw)
{
	if((fx+fy)==(n+m)/2+1) 
	{
    //分配律将两端的乘法（次数1*次数2）分解，便于统计
		sum+=dp[21*fx+fy][k^fnw];
		return;
	}
	else 
	{
		if(fx-1)fdfs(fx-1,fy,fnw^a[fx][fy]);
		if(fy-1)fdfs(fx,fy-1,fnw^a[fx][fy]);
	}
}
int main()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%lld",&a[i][j]);
	dfs(1,1,0);
	fdfs(n,m,0);
	printf("%lld\n",sum);
	return 0;
}
```


---

