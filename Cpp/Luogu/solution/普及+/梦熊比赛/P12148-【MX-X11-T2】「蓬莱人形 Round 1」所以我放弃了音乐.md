# 【MX-X11-T2】「蓬莱人形 Round 1」所以我放弃了音乐

## 题目背景

原题链接：<https://oier.team/problems/X11C>。

---

$$\text{考えたってわからないし}$$

$$\text{青空の下、君を待った}$$

$$\text{風が吹いた正午、昼下がりを抜け出す想像}$$

$$\text{ねぇ、これからどうなるんだろうね}$$

$$\text{進め方教わらないんだよ}$$

## 题目描述

在一个无限大的棋盘上有 $n$ 个**位置互不相同**的棋子 $(x_i,y_i)$，你需要通过进行若干次以下操作删除全部的棋子：

1. 选择一个格子 $(x,y)$。

2. 若 $(x,y)$ 上有棋子，则把这个棋子删掉，否则结束当前操作。

3. **依次**检查坐标为 $(x+1,y+1)$，$(x+1,y)$，$(x+1,y-1)$ 的格子上是否有棋子。当检查到第一个有棋子的格子时，停止检查，并将当前的 $(x,y)$ 更新为该格子的坐标后返回第二步。如果这三个格子都没有棋子，结束当前操作。

你要回答，最少操作多少次能把所有棋子删光。

## 说明/提示

**【样例解释 #1】**

对于第一组样例，棋盘如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/8glrwdcs.png)

第一次选择格子 $(1,3)$，则 $(1,3),(2,2),(3,3)$ 被删除。

第二次选择 $(3,1)$，则 $(3,1)$ 被删除。

可以证明没有更优的选择方案。

**【数据范围】**

**本题使用子任务捆绑。**

对于所有的测试数据，满足 $1\le n\le 10^6$，$1\le x_i,y_i\le 10^6$。

|子任务编号|$n\le$|$x_i,y_i \le$|特殊性质|分值|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$10^6$|$10^6$|A|$10$|
|$2$|$8$|$10^6$|无|$20$|
|$3$|$300$|$300$|无|$20$|
|$4$|$5\times 10^4$|$5\times 10^4$|无|$20$|
|$5$|$10^6$|$10^6$|无|$30$|

- 特殊性质 A：保证所有 $x_i$ 相等。

## 样例 #1

### 输入

```
4
1 3
2 2
3 1
3 3```

### 输出

```
2```

## 样例 #2

### 输入

```
9
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3```

### 输出

```
3```

# 题解

## 作者：fish_love_cat (赞：10)

赛时想抢首杀，第一个开的就是这题。

然后爆炸了，先去写了其他题转回来才发现自己糖成啥了。

---

最左端显然必须消耗操作，然后就是从下往上遍历会劣于从上往下遍历。

因为当前列最下面的点能消的较低点上面一定消不掉，但如果从它开始，它会锁定到上面可能能消的点，那这样上面的贡献就被挤掉了。

---

于是你像我一样对每一列写了个可删堆模拟每次操作发现挂了。

考虑这么一张图：

```
...@
.@@.
.@..
@.@.
```

`@` 表示棋子，`.` 表示空地。

我们的做法：

```
...1
.21.
.1..
1.3.
```

答案为 $3$。

正解：

```
...1
.11.
.2..
2.2.
```

答案为 $2$。

---

这启示我们对于每一个棋子进行转移而不是直接模拟。

从左到右从上到下的枚举棋子，然后从能抵达它并且未使用的棋子中取最上面的点进行转移。

无法转移的计入答案。

然后你会发现做完了，时间复杂度综合 $O(n \log n)$，瓶颈在于排序。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<int>ve[1000005];
map<int,bool>mp[1000005];
bool cmp(int a,int b){
    return a>b;
}
signed main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int u,v;
        cin>>u>>v;
        mp[u][v]=1;
        ve[u].push_back(v);
    }
    int ans=0;
    for(int i=1;i<=1000000;i++){
        if(ve[i].size()==0)continue;
        sort(ve[i].begin(),ve[i].end(),cmp);
        for(int j=0;j<ve[i].size();j++){
            if(mp[i-1][ve[i][j]+1])mp[i-1][ve[i][j]+1]=0;
            else if(mp[i-1][ve[i][j]])mp[i-1][ve[i][j]]=0;
            else if(mp[i-1][ve[i][j]-1])mp[i-1][ve[i][j]-1]=0;
            else ans++;
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：江湖午餐票 (赞：4)

# 题目大意
在一个无限大的棋盘上有 $n$ 个棋子，每次操作可以选择一个起点并按特定规则删除连续棋子。求删除所有棋子所需的最少操作次数。

操作规则：
1. 选择格子 $(x,y)$，若此处有棋子则删除
2. 依次检查 $(x+1,y+1)$、$(x+1,y)$、$(x+1,y-1)$，找到第一个有棋子的格子并重复操作。

# 解题思路
每个操作实际上形成一条从起点向右下方延伸的路径。最优策略是将棋子组织成尽可能多的连续路径。

个人感觉数有多少条路径的实现比较麻烦，此处我们可以逆向思考一下：若无法形成连续路径，则需要 $n$ 次操作，而**每形成一对棋子的配对就可以减少一次的操作**，那么我们只需要求出棋子的配对数 $c$，答案就是 $n-c$。

此处需要注意每个棋子只能有一个与其配对的棋子，我就是卡在这了……

# 代码

实现的时候脑回路比较清奇，等重构后再贴上来吧 ~~（可能到五一都不一定会重构）~~

---

## 作者：Hoks (赞：3)

## 前言
果然只有猫猫会写这种猎奇做法。

**请注意本题解复杂度大概是不正确的，当个乐子看就豪了。**
## 思路分析
肯定首先去考虑贪心。

然后匆匆忙忙敲个贪心挂完了。

不想对着想贪心细节所以猫猫想到了一个非常猎奇的思路。

我们考虑直接建图。

如果我们取了棋子 $x,y$ 后可以连带着取掉 $x',y'$，那么就从 $x,y$ 向 $x',y'$ 连一条边。

那这个时候的问题就变成了把这张图剖分为最少的链数。

如何你注意到一些问题，就是这个连带取是有顺序的，是从右往左取的。

但我们不妨先不要考虑这个问题，大胆断言，最后求出的最优情况一定是不违反这个规则的。

剩下来的问题就是将这个图剖分为最少的部分了。

利用 Dilworth 定理，我们可以把最小链剖分转化为最大匹配问题。

然后注意到这个连边只能是第 $x$ 行向第 $x+1$ 行连，而且 $x$ 这一行直接互相**不可能**连边。

那其实这张图就是一张 $k$ 分图。

既然是 $k$ 分图直接扔一个匈牙利求最大匹配就可以了。

但是你又考虑到，匈牙利的复杂度是 $O(nm)$ 的，也就相当于是 $O(n^2)$ 级别。

但我们注意到按照题目中的连边方式，每个点最多只会有 $3$ 个出点，大概是能跑的很快的。

然后大力一交就直接过了喵。

接下来补充下上面那个为什么求出来的最优情况一定可以不违反规则。

考虑你如果求出了最小链剖分的方案。

我们不妨从这个网格的右下角开始往左上角剥，在这样的顺序钦定下，原本可能违反规则的更右的顶点会被优先剥掉，最后自然也就符合题意了。
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (ls|1)
using namespace std;
const int N=2e6+10,M=5e4+10,V=2e2+10,lim=19,mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f;
int n,ans,to[N],vis[N];pair<int,int>a[N];map<pair<int,int>,int>mp;vector<int>e[N];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c=='#'||c=='.'||c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline bool dfs(int u,int vv)
{
	if(vis[u]==vv) return false;vis[u]=vv;
	for(auto v:e[u]) if(!to[v]||dfs(to[v],vv)) return to[v]=u,true;
	return false;
}
inline void solve()
{
	ans=n=read();for(int i=1,x,y;i<=n;i++) x=read(),y=read(),a[i]={x,y},mp[{x,y}]=i;
	for(int i=1;i<=n;i++)
	{
		auto [x,y]=a[i];
		if(mp[{x+1,y+1}]) e[i].emplace_back(mp[{x+1,y+1}]+n);
		if(mp[{x+1,y}]) e[i].emplace_back(mp[{x+1,y}]+n);
		if(mp[{x+1,y-1}]) e[i].emplace_back(mp[{x+1,y-1}]+n);
	}for(int i=1;i<=n;i++) if(dfs(i,i)) ans--;print(ans);
}
signed main()
{
	int T=1;
	// T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：Sunset_afterglow (赞：2)

~~赛时为了更高的分，所以我放弃了 T1，因为 70 分仅此而已，就已经足够了。~~
# 题意：
大概就是一个点可以向 $(x+1,y+1)$，$(x+1,y)$，$(x+1,y-1)$ 这几个方向拓展，使得拓展到的点不用在进行一次操作，若没有，则不再拓展。
# 思路：
首先我们看数据范围，对于所有的测试数据，满足 $1\le n\le 10^6$，$1\le x_i,y_i\le 10^6$。  
建图就不用想了，但 $n$ 是 $10^6$，所以思路肯定是往 $\mathcal{O}(n\log_2n)$ 的方向想的，如果有更优的就是我太唐了。  
我的方法就是记录可以到 $i$ 点的个数，若为 $0$ 那就无法从别的点拓展到此处，必须增加一次操作，如果有那么至多三个，一定是优先取横坐标小的，因为每个点只能拓展一次，而取横坐标小的，就可以保证可拓展到下一个点的点尽可能多。
# 实现：
把所有节点坐标记录，按照横坐标为主关键字，纵坐标为副关键字，从小到大排序，把所有坐标用 map 记录，坐标对应这是哪个点，因为保证没有两个位置相同的棋子。  
按照思路中的贪心策略，记录答案，输出即可。
# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {
	int x = 0 ,f = 1;
	char ch = getchar();
	while('0' > ch || ch > '9'){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch & 15);
		ch = getchar();
	}
	return x * f;
}
const int N = 1e6 + 5;
int n ,ans = 0;
int yclx[5] = {1 ,1 ,1} ,ycly[5] = {1 ,0 ,-1} ,zt[N];
pair<int ,int> a[N];
bool vis[N];
map<pair<int ,int> ,int> st;
queue<int>que; 
signed main() {
	n = read();
	for(int i = 1;i <= n;++ i)
		a[i].first = read() ,a[i].second = read();
	sort(a + 1 ,a + n + 1);
	for(int i = 1;i <= n;++ i)st.insert(make_pair(a[i] ,i));
	for(int i = 1;i <= n;++ i)
		zt[i] = ((st[make_pair(a[i].first - 1 ,a[i].second - 1)] != 0) + (st[make_pair(a[i].first - 1 ,a[i].second)] != 0) + (st[make_pair(a[i].first - 1 ,a[i].second + 1)] != 0));
	for(int i = 1;i <= n;++ i) {
		
		if(zt[i] == 0)vis[i] = true ,++ ans;
	}
	for(int i = 1;i <= n;++ i) {
		if(!vis[i]) {
			if(vis[st[make_pair(a[i].first - 1 ,a[i].second - 1)]]) vis[st[make_pair(a[i].first - 1 ,a[i].second - 1)]] = 0;
			else if(vis[st[make_pair(a[i].first - 1 ,a[i].second)]]) vis[st[make_pair(a[i].first - 1 ,a[i].second)]] = 0;
			else if(vis[st[make_pair(a[i].first - 1 ,a[i].second + 1)]]) vis[st[make_pair(a[i].first - 1 ,a[i].second + 1)]] = 0;
			else ++ ans;
			vis[i] = true;
		}
	}
	cout << ans;
	return 0;
}
```
###### 好不容易拿了 47 名，并写了题解，求过

---

## 作者：_RainCappuccino_ (赞：1)

> $\texttt{TAGS}$：贪心

~~因为题目名来做的，快去听听夜鹿口牙。~~

将 $(x, y)$ 与 $(x + 1, y + 1),(x+1, y),(x+1,y - 1)$ 连边，那么题意相当于用最少上升链不重不漏地覆盖整个图。

直接从横坐标最小的点模拟会被如下样例毙掉：

```
.xx
.x.
x.x
```

模拟得到的答案为 3，而正确答案为 2。

我们不妨将链拆开，视作链长 $-1$ 条有向边，此时可以发现，需要的链的数量为没有入边的点的数量。因此，我们每连一条边就可以使答案减一。那么只需要连尽可能多的边就可以得到最优解。

而仅匹配边就只需要看相邻的两个横坐标，其余互不影响。

**贪心策略：**

对于每个横坐标 $x$ 分别考虑，将横坐标 $= x$ 的点一起进行连边，贪心地想，从纵坐标最大的点开始连边，依次检查 $(x + 1, y + 1),(x+1, y),(x + 1, y - 1)$ 是否已经有了入边，没有就连上一条边，接着考虑纵坐标仅次于当前的点。

**证明：**


如果最优解存在这样的一部分：

```
b a
a c
```
（字母相同表示在同一条链）

那么一定可以调整为：

```
a a
b b
```

与最优解假设矛盾，故此贪心策略是正确的。

**代码：**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
typedef long long ll;
typedef pair<int, int> pi;
int n;
struct node {
    int x, y;
};
map<pi, bool> mark;
node a[N];

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> a[i].x >> a[i].y, mark[{a[i].x, a[i].y}] = 1;
    sort (a + 1, a + 1 + n, [](node x, node y) {
        if (x.x == y.x) return x.y > y.y;
        return x.x < y.x;
    });
    for (int i = 1; i <= n; i ++) {
        pi v = {a[i].x, a[i].y};
        if (mark[{v.first + 1, v.second + 1}]) v.first ++, v.second ++, mark.erase(v);
        else if (mark[{v.first + 1, v.second}]) v.first ++, mark.erase(v);
        else if (mark[{v.first + 1, v.second - 1}]) v.first ++, v.second --, mark.erase(v);
    }
    int tmp = 0;
    for (int i = 1; i <= n; i ++) {
        if (mark[{a[i].x, a[i].y}]) tmp ++;
    }
    cout << tmp;
    return 0;
}
```

---

## 作者：zxh_qwq (赞：1)

### P12148 题解

每个操作实际上是覆盖一条从起点向右下方延伸的路径。

显然，最优策略是找出尽可能少的路径覆盖所有点。

数有多少条路径的实现很麻烦，而且不好说能不能证明。所以考虑正难则反。

若所有棋子都是一条单独的路径，则一共需要 $n$ 次操作。但与此同时，每形成一对配对（此处指两个棋子之间的配对）就可以减少一次的操作。那么我们只需要求出棋子的配对数，答案就是总数减去配对数。

代码码风太抽象了，就不贴了。

---

## 作者：__CJY__ (赞：1)

## 思路
每个棋子是一个节点。如果棋子 $A$ 可以移动到棋子 $B$ （即 $B$ 是 $A$ 按照操作规则检查到的第一个棋子），则添加有向边 $A \rightarrow B$。

最少操作次数等于该有向无环图的最小路径覆盖数。根据 Dilworth 定理，最小路径覆盖数等于节点数减去最大匹配数。

对于每个棋子，快速找到它可以移动到的棋子（如果有），可以使用空间索引（如网格或哈希表）加速查找。

将棋子按 $x$ 坐标分组。对于每个棋子，只需要检查 $x+1$ 组的棋子。

对于每组 $x$，按 $y$ 坐标排序，使用二分查找快速定位 $(x+1,y+1),(x+1,y),(x+1,y-1)$。

对于每个棋子，优先匹配 $y$ 坐标最小的可达棋子，以减少路径数。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int>>a;
unordered_map<int,vector<int>>t;
unordered_map<int,multiset<int>>k;
int n,ans;
int main(){
	cin>>n,a.resize(n);
	for(int i=0;i<n;i++) cin>>a[i].first>>a[i].second;
	sort(a.begin(),a.end());
	for(auto p:a) t[p.first].push_back(p.second);
	for(auto [x,y]:t) sort(y.begin(), y.end());
	for(auto p:a){
		int x=p.first,y=p.second;
		bool f=0;
		if(k.count(x-1)){
			auto &s=k[x-1];
			auto it=s.lower_bound(y-1);
			if(it!=s.end()&&*it<=y+1) s.erase(it),f=1;
		}
		if(!f) ans++;
		k[x].insert(y);
	}
	cout<<ans;
}
```

---

## 作者：OIer_ACMer (赞：1)

# Solution
本题是一道和消消乐差不多游戏规则的贪心题目，第二个样例已经提示了我们要从贪心去想，毕竟是一行一行从上往下消灭。

首先，我们要对所有的点进行排序，纵坐标从大到小，横坐标从小到大，之后，我们一个一个遍历点，我们要用性质：每个删除的点属于一条连续线段，这条线段可以是斜着的、直的，当然两者兼具也行，题目中点的扫描是从上往下一个一个找，那么我们组成的线段**会尽量的往左上偏**，这个地方在纸上画一画也可以看得出来。

之后，我们要统计答案，我们先逆着从上往下将**前一列的点**从上往下删除，以求符合题目要求，这一步的原因是我们要组成一条一条如上一段所说的往左上偏的线段，而每一列最后一个点正好没删除，毕竟它之后已经没有点与它组成连续删除线段，而每一条连续删除线段正好对应一次操作，那么我们的答案就是剩下点的点集大小。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}
struct P
{
    int first, second;
};
bool operator<(P a, P b)
{
    return a.first == b.first ? a.second > b.second : a.first < b.first;
}
// void
signed main()
{
    int n = read();
    set<P> p;
    set<P> gg;
    for (int i = 0; i < n; i++)
    {
        int x = read(), y = read();
        p.insert({x, y});
    }
    int ans = 0;
    for (auto it = p.begin(); it != p.end(); it++)
    {
        cout << it->first << " " << it->second << endl;
    }
    for (auto it = p.begin(); it != p.end(); it++)
    {
        // auto [x, y] = *it;
        // if (gg.count({x, y}))
        // {
        //     continue;
        // }
        // int cx = x, cy = y;
        // ans++;
        // while (true)
        // {
        //     gg.insert({cx, cy});
        //     bool found = false;
        //     if (p.count({cx + 1, cy + 1}) && !gg.count({cx + 1, cy + 1}))
        //     {
        //         cx += 1;
        //         cy += 1;
        //         found = true;
        //     }
        //     else if (p.count({cx + 1, cy}) && !gg.count({cx + 1, cy}))
        //     {
        //         cx += 1;
        //         found = true;
        //     }
        //     else if (p.count({cx + 1, cy - 1}) && !gg.count({cx + 1, cy - 1}))
        //     {
        //         cx += 1;
        //         cy -= 1;
        //         found = true;
        //     }
        //     if (!found)
        //     {
        //         break;
        //     }
        //     // cout << "ope=" << ans << " chazhao=" << cx << " " << cy << endl;
        // }
        int x = it->first, y = it->second;
        // p.erase({x, y});
        if (p.count({x - 1, y + 1}))
        {
            p.erase({x - 1, y + 1});
        }
        else if (p.count({x - 1, y}))
        {
            p.erase({x - 1, y});
        }
        else if (p.count({x - 1, y - 1}))
        {
            p.erase({x - 1, y - 1});
        }
        // cout << endl;
    }
    cout << endl;
    for (auto it = p.begin(); it != p.end(); it++)
    {
        cout << it->first << " " << it->second << endl;
    }
    cout << p.size() << endl;
    return 0;
}
```

---

## 作者：weiyiqian (赞：0)

容易发现题目中**依次**这个操作是没有必要的，因为若删掉依次检查出的棋子不是最优的，那么我们可以先删掉这个检查出的棋子保证走不到不是最优解的路径上。

于是问题就转化为最少有多少条删除棋子的路径可以完全覆盖每个棋子。

考虑将每个棋子按以横坐标为第一关键字从小到大、纵坐标为第二关键字从小到大的顺序排序，然后枚举每个棋子向后删一次，若删不了就记录一次答案。

证明：横坐标较大的棋子一定是被横坐标较小的棋子删掉。每次删除操作先删掉纵坐标较小的，这样就能使得后面的棋子能删掉的棋子尽可能多。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,st[N];
map<int,int> S[N];
struct point{
    int x,y;
    bool operator<(const point &a)const{
        if(x==a.x) return y<a.y;
        return x<a.x;
    }
}a[N];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y;
    sort(a+1,a+1+n);
    int cnt=0;
    for(int i=1;i<=n;i++) S[a[i].x][a[i].y]=i;
    for(int i=1;i<=n;i++){
        int x=a[i].x,y=a[i].y;
        int p1=S[x+1][y-1],p2=S[x+1][y],p3=S[x+1][y+1];
        if(p1&&!st[p1]) st[p1]=1;
        else if(p2&&!st[p2]) st[p2]=1;
        else if(p3&&!st[p3]) st[p3]=1;
        else cnt++;
    }
    cout<<cnt;
    return 0;
}
```

---

## 作者：vanueber (赞：0)

赛时脑抽，艰难过掉。

# 题目大意

给定平面直角坐标系中的 $n$ 个点，每次选择一个点，依次检查 $(x+1,y+1),(x+1,y),(x+1,y-1)$ 并跳到这个点继续删除直到不能删为止，记为一次操作，求最小的操作次数。

# 70 pts

一个经典的网络流问题，直接暴力建图跑最大流即可。

# 100 pts

特殊性质 A 启发我们按照不同的 $x$ 分开处理。故开 $10^6$ 个 `set` 维护每个 $x=i$ 时的所有 $y$ 值。不难发现最终的答案是选择的不同路径的起点数量，我们要最小化这个东西。

接下来我们运用类似归纳法的思想得到贪心策略。

假设我们当前处理到了 $x=i$ 的所有点，且这些点的贡献已经累计到答案中，那么 $x=i$ 的这些点，无论是作为一条删除路径的起点或者是一条路径中的点，我们要为他们匹配一个 $x=i+1$ 的后继，这样就能使 $x=i+1$ 的点产生的贡献最小（因为能选择更少的起点）。

贪心策略：对于 $x=i$ 的点 $y$ 值从大到小处理，先匹配 $(x+1,y+1)$，再匹配 $(x+1,y)$，最后匹配 $(x+1,y-1)$。

正确性：感性理解，如果不优先匹配 $y$ 更大的那么对于后面的点就更不可能匹配到了，而 $y$ 更小的还可以交给其他点处理，故不按照 $(x+1,y+1),(x+1,y),(x+1,y-1)$ 的顺序一定不优，满足贪心的最优子结构和贪心选择性的性质。

时间复杂度 $\Theta(n \log n)$。

# 代码

使用大量 stl，常数极大。


```cpp
#include <bits/stdc++.h>
#define vint vector<int>
#define ll long long
#define pii pair<int,int>
#define all(x) x.begin(),x.end()
#define ull unsigned long long
#define uint unsigned int
#define rg register
#define il inline
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define sqr(x) ((x)*(x))
using namespace std;
const int INF=0x3f3f3f3f;
inline int read()
{
    int w=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        w=(w<<1)+(w<<3)+(ch^48);
        ch=getchar();
    }
    return w*f;
}
inline void write(int x)
{
    if(x<0)
    {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

const int N=1e6+10;
int n;
int x[N],y[N];
set<int,greater<int>> pos[N],tmp[N];
map<pii,int> to;
bool used[N];
int ans,maxx;
int maxs[N];
map<int,int> posx[N];
int main()
{
    #ifndef ONLINE_JUDGE
    //freopen("in.txt","r",stdin);
    #endif
    cin>>n;
    rep(i,1,n) x[i]=read(),y[i]=read(),pos[x[i]].insert(y[i]),maxx=max(maxx,x[i]),to[make_pair(x[i],y[i])]=i;
    ans=pos[1].size();
    rep(i,1,maxx-1)
    {
        ans+=pos[i+1].size();
        
        for(auto it=pos[i].begin();it!=pos[i].end();++it)
        {
            int x=i,y=*it;
            if(to[make_pair(x+1,y+1)]&&!used[to[make_pair(x+1,y+1)]])
            {
                --ans,used[to[make_pair(x+1,y+1)]]=1;
                continue;
            }
            if(to[make_pair(x+1,y)]&&!used[to[make_pair(x+1,y)]])
            {
                --ans,used[to[make_pair(x+1,y)]]=1;
                continue;
            } 
            if(to[make_pair(x+1,y-1)]&&!used[to[make_pair(x+1,y-1)]])
            {
                --ans,used[to[make_pair(x+1,y-1)]]=1;
                continue;
            } 
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：sbno333 (赞：0)

首先观察就是到下一列的上中下三个格子。

考虑按照行排序，相邻两行考虑。

我们没有后效性是显然的，所以只考虑前一行，然后什么顺序转移省次数。

从 $y$ 最高开始，因为这里会被优先自动转移，为了省次数不影响下面，我们考虑尽量选上一列靠上的，转移，然后那个格子毙掉。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct st{
	int x,y;
}a[1000009];
bool cmp(st a1,st a2){
	return a1.x==a2.x?a1.y>a2.y:a1.x<a2.x;
} 
int xl[2][1000009];
void pop(int x){
	xl[a[x].x&1][a[x].y]=0;
}
void push(int x){
	xl[a[x].x&1][a[x].y]=1;
}
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+1+n,cmp);
	int ll,l;
	l=ll=1;
	int ans;
	ans=0;
	for(int i=1;i<=n;i++){
		if(a[i].x!=a[i-1].x&&(i!=1)){
			if(a[i].x!=a[i-1].x+1){
				l=i;
				while(ll<l){
					pop(ll);
					++ll;
				}
			}else{
				while(ll<l){
					pop(ll);
					++ll;
				}
				l=i;
			}
		}
		ans++;
		for(int j=1;j>=-1;j--){
			if(xl[!(a[i].x&1)][a[i].y+j]){
				xl[!(a[i].x&1)][a[i].y+j]=0;
				ans--;
				break;
			}
		}
		push(i);
	}
	cout<<ans;
	return 0;
}
```

---

