# [IOI 2008] Teleporters

## 题目描述

你正在参加一项沿着直线路线自西向东横穿埃及的比赛。开始时你位于这条直线路线的最西端。根据比赛规则，你必须要沿着这条直线路线始终向东行进。

在这条直线路线上有 $N$ 个传送器。每个传送器都有两个端点。每当你到达某个传送器的两个端点之一时，传送器都会立即将你传送到该传送器的另一个端点（注意，根据你所在的端点位置，传送器能够将你从当前位置向东或者向西传送）。当你被传送到另一个端点之后，你必须继续沿这条直线路线向东行进；你无法避开你前进路上的任何传送器端点。绝不会出现两个端点在同一位置的情形。所有端点都严格位于这条直线路线的起点和终点之间。

每当你被传送一次，你就会获得 $1$ 分。比赛的目标就是获取尽可能多的分数。为使获得的分数最多，允许你在比赛开始前在这条路线上增设 $M$ 个新的传送器。使用这些新的传送器你也同样可以获得分数。

你可以将这些新传送器的端点设在任何位置上（甚至是非整数坐标点也可以），只要这些坐标点并不出现在已经被另一个端点占用的位置上即可。换句话说，所有传送器的端点位置必须是唯一的。同样，新传送器的端点都必须严格位于这条直线路线的起点和终点之间。

题目可以保证，不管你如何增设这些传送器，你一定可以到达比赛路线的终点。

试编写一个程序，对于给定的 $N$ 个传送器的端点位置和你可以增设的新传送器的数目 $M$，计算你能获得的最高分数。

## 说明/提示

### 样例 1 说明

![](https://cdn.luogu.com.cn/upload/pic/20908.png )

上面左图表示一条初始有 $3$ 个传送器的比赛路线的情形。右图表示在增设一个端点分别为 $0.5$ 和 $1.5$ 的新传送器之后的同一比赛路线。

在增设上图所示的新的传送器之后，你的比赛路途如下：
- 你从位置 $0$ 出发，向东行进。
- 你到达位于 $0.5$ 的传送器端点，并且被传送到另一端点 $1.5$（你获得 $1$ 分）。
- 你继续向东行进，并且到达位于 $2$ 的传送器端点；你被传送到位于 $3$ 的另一端点（这时你共获得 $2$ 分）。
- 你到达位于 $4$ 的传送器端点，并且被传送到位于 $1$ 的另一端点（这时你共获得 $3$ 分）。
- 你到达位于 $1.5$ 的传送器端点，并且被传送到位于 $0.5$ 的另一端点（这时你共获得 $4$ 分）。
- 你到达位于 $1$ 的传送器端点，并且被传送到位于 $4$ 的另一端点（这时你共获得 $5$ 分）。
- 你到达位于 $10$ 的传送器端点，并且被传送到位于 $11$ 的另一端点（这时你共获得 $6$ 分）。
- 你继续行进直到到达比赛的终点，以获得总分为 $6$ 分结束。

### 数据范围

- 对于 $30\%$ 的数据，$N \leq 500$ 并且 $M \leq 500$。 
- 对于所有数据，$1 \leq N \leq 1,000,000$，$1 \leq M \leq 1,000,000$，$1 \leq W_X < E_X \leq 2,000,000$。

## 样例 #1

### 输入

```
3
1
10 11
1 4
2 3```

### 输出

```
6```

## 样例 #2

### 输入

```
3
3
5 7
6 10
1999999 2000000```

### 输出

```
12```

# 题解

## 作者：文文殿下 (赞：12)

一个结论：“从出发点开始走绝对不会出现死循环”。  
考虑如何证明这个结论（这会直接提示正解）：  
我们对数轴分段，对于任意一个传送门，把当前段分成两段。  
对于每一段（除了第一段）我们总会有一个到达这个段的方法：走一个传送门。这个传送门的位置是这个段左边第一个传送门，我们查看这个传送门通向哪里，然后把那个点与这个点连一条有向边。  
对于每一段（除了最后一段）我们总会有一个离开这个段的方法，和上面类似建图。  
我们考虑，我们在行走过程中，由于第一个段没有入度，所以我们绝对不会回到第一个段。  
由于最后一个段没有出度，所以我们绝对不会向其他地方循环。  
由于除了开头和结尾的特殊段，其他任何段有且仅有一个入度和出度，所以我们一定会从一号段到达最后一个段离开。  
证毕。  
我们发现，除了从一号点到最后一个点是一条简单路径，其他的点一定在一个环里（可以画图理解）。  
考虑我们新加一个传送门，会导致这张有向图如何变化？  
我们有三种加的方式：  
* 一：用一对传送门把两个不在同一个连通块的点链接。  
这会直接导致有两个点一分为二，然后他们所在的连通块合并。  
如果我们合并路径和环，我们会得到一个更长的路径。  
如果我们合并环和环，我们会得到一个更大的环。  
* 二：用一对传送门链接同一个连通块里两个点。  
这会直接导致这个连通块一分为二。这对答案没有任何帮助。  
* 三：这对传送门放在某对传送门的内部，这会导致我们永远无法访问到这个传送门，所以他单独成一个点。  

题解显而易见，我们把所有环从大到小排序。  
然后从大到小，用传送门把他们用方法一连到我们的路径里。 
如果连完以后，传送门还有剩余，我们可以不断做方法三和方法一，把他们累加到答案里。  
细节：如果只剩一个传送门，我们就把他加在末尾。   
时间复杂度$O(nlogn)$  
进一步优化：  
我们发现复杂度瓶颈在于排序，但是由于排序的值非常小，我们使用桶排序。  
时间复杂度到达理论下届：$O(n)$  
但是我懒得写线性的，下面给出$O(nlogn)$的代码，吸氧能过。  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e6+10;
struct qwq {
    int inc,out;
}s[maxn];
struct QQQ {
    int l,r;
}L[maxn];
struct QAQ {
    int v,bl,type;
    const bool operator < (const QAQ& rhs) const {
        return v<rhs.v;
    }
}v[maxn];
int n,m,cnt,ind[maxn];
int sz[maxn],ans,tot;
bool vis[maxn];
int find(int x) {
    return lower_bound(v+1,v+1+cnt,(QAQ){x,0,0})-v;
}
void dfs(int cur,int pos) {
    while(!vis[cur]) {
        vis[cur]=1;
        sz[pos]++;
        int nxt;
        if(v[cur].type) nxt = find(L[v[cur].bl].l+1);
        else nxt=find(L[v[cur].bl].r+1);
        cur = nxt;
    }
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) {
        scanf("%d%d",&L[i].l,&L[i].r);
        v[++cnt].v=L[i].l;
        v[cnt].bl=i;
        v[cnt].type=0;
        v[++cnt].v=L[i].r;
        v[cnt].bl=i;
        v[cnt].type=1;
    }
    sort(v+1,v+1+cnt);
    int cur = 1;
    while(cur!=cnt+1) {
        vis[cur]=1;
        ++ans;
        int nxt;
        if(v[cur].type) nxt = find(L[v[cur].bl].l+1);
        else nxt=find(L[v[cur].bl].r+1);
        cur = nxt;
    }
    vis[cur]=1;
    for(int i=1;i<=cnt;++i) {
        if(!vis[i]) {
            dfs(i,++tot);
        }
    }
#ifdef DEBUG
    printf("%d\n",ans);
    printf("%d\n",tot);
    for(int i=1;i<=tot;++i) printf("%d ",sz[i]);
#endif
    sort(sz+1,sz+1+tot,greater<int>());
    for(int i=1;i<=tot&&m;++i) {
        ans+=2;
        --m;
        ans+=sz[i];
    }
    if(m) {
        if(m&1) --m,++ans;
        ans+= 2*m;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：251Sec (赞：6)

考虑对于第 $i$ 组传送器，把左边那个传送器的左侧和右边那个传送器的右侧看成一个点 $i+n$，把左边那个传送器的右侧和右边那个传送器的左侧看成一个点 $i$。另外，我们把最左侧传送器的左侧和最右侧传送器的右侧也看成一个点 $0$。

样例 1 be like:

![](https://cdn.luogu.com.cn/upload/image_hosting/tdquic55.png)


然后我们对于这 $2n+1$ 个点，发现每个点恰好能到达一个点，例如上图中 $0 \to 5, 2 \to 6$ 等。因此最终得到的图是若干个环。

样例 1 be like:

![](https://cdn.luogu.com.cn/upload/image_hosting/9gcimyvu.png)

发现最终答案为与 $0$ 连通的环的大小减 $1$。（由此可以发现答案不可能为无穷大）

考虑 $m$ 次操作如何进行，手玩一下可以发现一次操作可能有以下效果：

- 连接两个环，得到的新环大小为它们的大小之和加上 $2$。
- 将一个环破开，得到两个新环，它们的大小之和为原环大小加上 $2$。

于是我们得到贪心策略：

每次贪心选择最大的环和与 $0$ 相连的环合并，合并完成之后反复从与 $0$ 相连的环中破出大小为 $1$ 的环然后把这个环合并回去。

容易写出代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
int nxt[2000005];
bool vis[2000005];
struct TP {
    int pos, id;
    bool tp;
    bool operator<(const TP &o) const {
        return pos < o.pos;
    }
} w[2000005];
int cur, siz[2000005];
void DFS(int u) {
    if (vis[u]) return;
    siz[cur]++;
    vis[u] = true;
    DFS(nxt[u]);
}
int ans;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        w[i].pos = l;
        w[i].id = i;
        w[i].tp = 0;
        w[i + n].pos = r;
        w[i + n].id = i;
        w[i + n].tp = 1;
    }
    sort(w + 1, w + n * 2 + 1);
    nxt[0] = w[1].id + n;
    for (int i = 1; i <= n * 2; i++) {
        int id = w[i].id;
        if (!w[i].tp) {
            if (i) nxt[w[i - 1].id + n * w[i - 1].tp] = id + n;
            nxt[id] = w[i + 1].id + n * !w[i + 1].tp;
        }
        else {
            nxt[w[i - 1].id + n * w[i - 1].tp] = id;
            if (i != n * 2) nxt[id + n] = w[i + 1].id + n * !w[i + 1].tp;
        }
    }
    for (int i = 0; i <= n * 2; i++) {
        if (!vis[i]) {
            cur++;
            DFS(i);
        }
    }
    sort(siz + 2, siz + cur + 1, greater<int>());
    ans = siz[1] - 1;
    for (int i = 2; i <= cur; i++) {
        if (!m) break;
        m--;
        ans += 2; ans += siz[i];
    }
    if (m & 1) {
        ans++;
        m--;
    }
    ans += m * 2;
    printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Flash_Man (赞：5)

对于一个传送器，我们把它拆成两个点，左点和右点（左传送门的右点和右传送门的左点是一个点，同理左传送门的左点和右传送门的右点是一个点），如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/1ynosqeq.png)

这时，我们把数轴上所有点的前驱和后继（最开始和最后都是 $0$）关系求出来，可以发现它是一个「置换」，即每个点都有一个前驱和一个后继的图，即由若干个环组成的图。

我们发现，分数即是 $0$ 所在的环的长度。如果一个传送门在同一个环的路径上，此环就会裂开；若不在，此两个环就会拼接。所以，建完图后，我们先求出所有环的长度，贪心地从大到小把环并到 $0$ 所在的环，若还有传送门次数，就重复此过程：一个传送门先新建一个环，一个传送门再把这个新建的环并入 $0$ 所在的环。

代码如下：

```cpp
#include <cstdio>
#include <algorithm>

using std::sort;

const int maxl = 2e6 + 3;

int n, m;
int l, r;

int t[maxl];
bool b[maxl];
int nxt[maxl];
int cnt = -1, num[maxl];
bool vis[maxl];
int ans = 0;

void dfs(int x) {
    int res = 1, cur = nxt[x];
    vis[x] = true;
    while (cur != x) {
        res++;
        vis[cur] = true;
        cur = nxt[cur];
    }
    num[++cnt] = res;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &l, &r);
        t[l] = t[r] = i;
        b[l] = true;
    }
    int pr = 0;
    for (int i = 1; i < maxl; i++)
        if (t[i]) {
            if (b[i]) {
                nxt[pr] = (t[i] << 1) - 1;
                nxt[t[i] << 1] = 0;
                pr = t[i] << 1;
            } else {
                nxt[pr] = t[i] << 1;
                nxt[(t[i] << 1) - 1] = 0;
                pr = (t[i] << 1) - 1;
            }
        }
    dfs(0);
    for (int i = 1; i <= (n << 1); i++)
        if (!vis[i])
            dfs(i);
    sort(num + 1, num + cnt + 1, [](int x, int y) {return x > y;});
    if (m <= cnt) {
        ans = -3;
        for (int i = 0; i <= m; i++)
            ans += num[i] + 2;
    }
    else {
        ans = (n + cnt) << 1;
        m -= cnt;
        ans += (m << 1) + (m & 1);
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：Little_Cancel_Sunny (赞：5)

## 题意

在一条线上有 $n$ 个传送门，每个传送门有两个端点，遇到一个端点便会传送到另外一个端点，你需要从起点到终点，每经过一次传送，就可以使得分增加一，询问如果再添加 $m$ 个传送门可以获得的最大分数。

## 思路

首先我们先明确一下添加传送门的目的，添加的传送门既可以借助原来的图增加得分，也可以另立门户独立创造得分

然后我们先拆解问题：

1. 如何利用原图与添加的传送门增加得分
2. 如何才可以使另立门户的传送门得分尽可能的高

### 问题 1 的解法

我们先观察原图，对原图的不同情况分类，相同图形表示一种传送门。

类型1，如图。
![](https://cdn.luogu.com.cn/upload/image_hosting/bnhjahlq.png)

显而易见，中间的传送门没有任何贡献。

类型2，如图。
![](https://cdn.luogu.com.cn/upload/image_hosting/hvi0ghvz.png)

如果手模一下就可以发现这种情况可做的贡献是最多的，当然在这种类型中还分有两种情况，第一种，有偶数个传送门交替出现，它会造成 $2 n$ 的贡献，第二种，有奇数个传送门交替出现，但是它造成的贡献却达不到 $2 n$。

可以证明 $2 n$ 即为偶数个传送门可以造成的最大贡献，既每一种传送门的两种传送路线你都最多经过一次。

假设有一条线路被走了两次，那么你一定会再次经过原先走过的路，因为你无法躲避中间的传送门，如果出现了这种情况，那么你一定处于一个循环中，但是这种情况不可能出现~~但是我不会证明~~，故你不可能两次经过同一条传送道路。

所以我们要借助新加的传送门，将原图中没有做贡献或者做贡献未做满的传送门的贡献补回来。

如果你十分有经验，那么像跳来跳去的题，第一个想到的一定是将它转移到图上，那么将每一种可能经过的路径画出来，以样例二为例，如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/q6aq9rsk.png)

~~好丑~~。

如果你是正常人，那么像这种图，很难看出什么性质直接用于解题。

如果细心一点，就可以发现由于遇到红线的一端，我们就必须走过这条红线到达另外一端，那么我们是否可以认为这两个端点是同一个点，并且我们经过该点时可以获得一次贡献。

在图上或许会更好理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/own6tm1a.png)

然后把编号相同的两点缩为同一个点，就变成了这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/p13rf5ky.png)

如果我们将起点与终点合并那么它就变为了一个环，并且答案为这个环的 $size - 1$。

可以发现其他不做贡献的线路也会自己变成一个环或者与其他线路组成一个大环。

那么可以发现我们添加的线路就是要让这些没有做贡献的环做出贡献。

还可以发现，这些没有做贡献的环仅仅是因为没有进入它们的线路，那么我们添加的传送门就要进入这些线路，那么我们继续以样例二为例，但是此时我们只添加一个传送门。

![](https://cdn.luogu.com.cn/upload/image_hosting/sbnfz97f.png)

好的，不难发现添加的传送门在接入不做贡献的环后，不仅自己做了贡献还使得该环也做出了贡献，那么解决该问题的方法也就显而易见了。

首先先建图，寻找图中的环，然后取出与起点相连的环，将剩下的环按大小排序，每次取出最大的环，使用一个传送们将其与起点环相连，最后将答案累计即可。

### 问题 2 的解法

由于在上文中，我们知道了如何使传送门做出最大贡献，那么解决这个问题也十分简单。

首先如果剩下偶数个传送门，将它们的所有线路累计进答案即可（也就是两倍的传送门数量），否则先取出一个传送门，将剩余的传送门按上文方法计入答案，当然剩下的这个传送门也会做出一次贡献。

至此问题完美解决。

## 代码

~~最开心的代码时间~~。

```cpp
#include<bits/stdc++.h>
namespace fast_IO {
#define IOSIZE 1000000
	char ibuf[IOSIZE], obuf[IOSIZE], *p1 = ibuf, *p2 = ibuf, *p3 = obuf;
#define getchar() ((p1==p2)and(p2=(p1=ibuf)+fread(ibuf,1,IOSIZE,stdin),p1==p2)?(EOF):(*p1++))
#define putchar(x) ((p3==obuf+IOSIZE)&&(fwrite(obuf,p3-obuf,1,stdout),p3=obuf),*p3++=x)
#define isdigit(ch) (ch>47&&ch<58)
#define isspace(ch) (ch<33)
	template<typename T> inline T read() { T s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s * w; }
	template<typename T> inline bool read(T &s) { s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s *= w, true; }
	template<typename T> inline void print(T x) { if (x < 0) putchar('-'), x = -x; if (x > 9) print(x / 10); putchar(x % 10 + 48); }
	inline bool read(char &s) { while (s = getchar(), isspace(s)); return true; }
	inline bool read(char *s) { char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) *s++ = ch, ch = getchar(); *s = '\000'; return true; }
	inline void print(char x) { putchar(x); }
	inline void print(char *x) { while (*x) putchar(*x++); }
	inline void print(const char *x) { for (int i = 0; x[i]; i++) putchar(x[i]); }
	inline bool read(std::string& s) { s = ""; char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) s += ch, ch = getchar(); return true; }
	inline void print(std::string x) { for (int i = 0, n = x.size(); i < n; i++) putchar(x[i]); }
	inline bool read(bool &b) { char ch; while(ch=getchar(), isspace(ch)); b=ch^48; return true; }
	inline void print(bool b) { putchar(b+48); }
	template<typename T, typename... T1> inline int read(T& a, T1&... other) { return read(a) + read(other...); }
	template<typename T, typename... T1> inline void print(T a, T1... other) { print(a), print(other...); }
	struct Fast_IO { ~Fast_IO() { fwrite(obuf, p3 - obuf, 1, stdout); } } io;
	template<typename T> Fast_IO& operator >> (Fast_IO &io, T &b) { return read(b), io; }
	template<typename T> Fast_IO& operator << (Fast_IO &io, T b) { return print(b), io; }
#define cout io
#define cin io
#define endl '\n'
} using namespace fast_IO;
using namespace std;

const int N=2e6+15;

int h[N],to[N],ne[N],idx=0;
int siz[N],tot;
bool vis[N];
int n,m;
struct node 
{
	int l,r;
	int loc;
}point[N];
int sum,ans;

bool cmp(node a,node b)
{
	return a.loc<b.loc;
}

bool cmp2(int x,int y)
{
	return x>y;
}

void add(int u,int v)
{
	to[++idx]=v;
	ne[idx]=h[u];
	h[u]=idx;
}

void dfs(int u)
{
	if(vis[u])
		return;
	siz[tot]++;
	for(int i=h[u];i!=-1;i=ne[i])
		vis[u]=1,dfs(to[i]);
}

signed main()
{
	memset(h,-1,sizeof h);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		point[++sum]={i,n+i,x};
		point[++sum]={n+i,i,y};
	}
	sort(point+1,point+sum+1,cmp);
	add(0,point[1].l);
	for(int i=1;i<sum;i++)
		add(point[i].r,point[i+1].l);
	add(point[sum].r,0);
	for(int i=0;i<=sum;i++)
		if(!vis[i])
			tot++,dfs(i);
	ans=siz[1];
	sort(siz+2,siz+tot+1,cmp2);
	for(int i=2;i<=tot;i++)
		if(m)
			m--,ans=ans+2+siz[i];
	else 
		break;
	if(m%2)
		m--,ans+=1;
	ans=ans+2*m;
	cout<<ans-1<<endl;
	return 0;
}
```

## 结尾

上述代码因为空间限制无法通过本题的，但是细心的你会发现，每个点只会连一条边，所以链式前向星的空间可以压缩，最后再重复利用一些数组，以时间换空间就可以通过了。

---

