# Graph Traveler

## 题目描述

Gildong 正在用一台有趣的机器 Graph Traveler 进行实验。在 Graph Traveler 中，有一个有向图，包含 $n$ 个顶点，编号从 $1$ 到 $n$。第 $i$ 个顶点有 $m_i$ 条有向边，分别标记为 $e_i[0]$、$e_i[1]$、$\ldots$、$e_i[m_i-1]$，每条边表示该边的目标顶点。该图可以有重边和自环。第 $i$ 个顶点上还写有一个整数 $k_i$。

在这个图上的一次旅行按如下方式进行：

1. Gildong 选择一个顶点作为起点，并选择一个整数作为起始值。将变量 $c$ 设为该整数。
2. 每当到达顶点 $i$，或者刚开始在某个顶点 $i$ 开始旅行时，将 $k_i$ 加到 $c$ 上。
3. 下一个顶点为 $e_i[x]$，其中 $x$ 是满足 $0 \le x \le m_i-1$ 且 $x \equiv c \pmod{m_i}$ 的整数。前往下一个顶点并回到第 2 步。

显然，这样的旅行永远不会结束，因为第 2 步和第 3 步会无限循环。

例如，假设 Gildong 从顶点 $1$ 开始，$c=5$，且 $m_1=2$，$e_1[0]=1$，$e_1[1]=2$，$k_1=-3$。刚开始在顶点 $1$ 时，$c$ 变为 $2$。唯一满足条件的 $x$（$0 \le x \le 1$ 且 $x \equiv c \pmod{m_i}$）是 $0$，所以 Gildong 前往顶点 $e_1[0]=1$。再次到达顶点 $1$ 后，$c$ 变为 $-1$。唯一满足条件的 $x$ 是 $1$，所以他前往顶点 $e_1[1]=2$，以此类推。

由于 Gildong 非常好奇，他会向你提出 $q$ 个询问。他想知道，如果从某个顶点以某个 $c$ 的初始值开始旅行，将会有多少个不同的顶点被无限次访问。注意，不要统计那些只会被访问有限次的顶点。

## 说明/提示

第一个样例可以用下图表示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1200F/a011bde48ef56a4766df088c213c0f3fb6972396.png)

每个顶点上标记了三个整数：$i$、$k_i$ 和 $m_i$。出边用整数标记，表示该顶点的第几条边。

每个询问的旅行过程如下，描述为“顶点（加上 $k_i$ 后的 $c$ 值）”的序列：

- $1(0) \to 2(0) \to 2(0) \to \ldots$
- $2(0) \to 2(0) \to \ldots$
- $3(-1) \to 1(-1) \to 3(-1) \to \ldots$
- $4(-2) \to 2(-2) \to 2(-2) \to \ldots$
- $1(1) \to 3(1) \to 4(1) \to 1(1) \to \ldots$
- $1(5) \to 3(5) \to 1(5) \to \ldots$

第二个样例与第一个样例相同，只是顶点上的值非零，因此每个询问的答案也不同。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1200F/fa2b54acddea0c522ade11c446830a8460d01a6b.png)

第二个样例的每个询问过程如下：

- $1(4) \to 2(-1) \to 2(-6) \to \ldots$
- $2(-5) \to 2(-10) \to \ldots$
- $3(-4) \to 1(0) \to 2(-5) \to 2(-10) \to \ldots$
- $4(-3) \to 1(1) \to 3(-2) \to 4(-3) \to \ldots$
- $1(5) \to 3(2) \to 1(6) \to 2(1) \to 2(-4) \to \ldots$
- $1(9) \to 3(6) \to 2(1) \to 2(-4) \to \ldots$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
0 0 0 0
2
2 3
1
2
3
2 4 1
4
3 1 2 1
6
1 0
2 0
3 -1
4 -2
1 1
1 5
```

### 输出

```
1
1
2
1
3
2
```

## 样例 #2

### 输入

```
4
4 -5 -3 -1
2
2 3
1
2
3
2 4 1
4
3 1 2 1
6
1 0
2 0
3 -1
4 -2
1 1
1 5
```

### 输出

```
1
1
1
3
1
1
```

# 题解

## 作者：cccgift (赞：5)

### 这应该算是CFdiv2最后一题中较为简单的题了。（以前的最后一题我根本想不出来）

~~真是可惜，竟然没有去打……~~

乍一眼看过去好像并不可做，如果只有一个询问直接处理就好了。

我们肯定不能在线处理每一个询问，因为要找出有多少个点会被经过无数次，时间复杂度起码要$O(n)$，承受不住。

那么，我们换一个思路：能否预处理出所有答案，$O(1)$回答呢？

看看数据范围好像也不行，$|y|≤10^9$，但对于每一个$y$，能否找到一个等效的$y'$，使得答案不变呢？

注意到$1≤m_i≤10$，从这里入手，观察题目中所给的同余式，发现只要使$y\equiv y'(\mod lcm(1..10))$，即可使每一个同余式的答案不变。

我们把每一个询问设成状态$(x,y)$，那么状态只剩下了$2520n$个！（$lcm(1..10)=2520$）

接下来，我们考虑能否预处理出每一个状态$(x,y)$的答案，询问使直接调用。

先预处理出每一个状态的后继状态，就是接下来会到达哪个点和到了那个点之后剩余的点权。

从状态$(1,0)$开始搜索，分两种情况：

1、当前状态没有被搜到过：这种情况直接继续搜索，并继承它的后继状态的答案即可。

2、当前状态被搜到过了：说明此时构成了一个环，那么所有环上的点就都是可以被经过无限次的，类似于找环的方法，把环上的点弄出来去重，加入答案即可。

由于每个状态只会被搜到一次，而统计答案时只会统计没有被统计过的状态，所以最终时间复杂度是$O(2520n+q)$。

### 代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<cctype>
#include<utility>
#include<algorithm>
#include<cmath>
using namespace std;
#define res register int
#define ll long long
//#define cccgift
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
namespace wode{
    template<typename T>
    inline void read(T &x)
    {
        static char ch;bool f=1;
        for(x=0,ch=getchar();!isdigit(ch);ch=getchar()) if(ch=='-') f=0;
        for(;isdigit(ch);x=(x<<1)+(x<<3)+(ch^48),ch=getchar());x=f?x:-x;
    }
    template<typename T>
    void print(T x)
    {
        if (x<0) putchar('-'),x=-x;
        if (x>=10) print(x/10);
        putchar(x%10+'0');
    }
    template<typename T>
    inline void print(T x,char ap) {print(x);if (ap) putchar(ap);}
    template<typename T>
    inline T max(T x,T y) {return x<y?y:x;}
    template<typename T>
    inline T min(T x,T y) {return x<y?x:y;}
    template<typename T>
    inline void chkmax(T &x,T y) {x=x<y?y:x;}
    template<typename T>
    inline void chkmin(T &x,T y) {x=x<y?x:y;}
}
using wode::read;using wode::chkmin;using wode::chkmax;using wode::print;
#define lcm 2520
int n,m,a[1001],b[10],nxt[2520001],f[2520001],sum,col[2520001],stack[1001],top,x,y;
bool vis[1001];
void dfs(int x,int bel) {
	col[x]=bel;
	if(!col[nxt[x]]) dfs(nxt[x],bel),f[x]=f[nxt[x]];
	else if(col[nxt[x]]==bel) { //当前状态已经被搜到过了
		int now=nxt[x],tot=1;vis[x/lcm]=true,stack[top=1]=x/lcm;
		for(;now!=x;now=nxt[now]) if(!vis[now/lcm]) vis[now/lcm]=true,stack[++top]=now/lcm,++tot;
		f[x]=tot;
		for(res i=1;i<=top;++i) vis[stack[i]]=false; //防止复杂度退化
	}
	else f[x]=f[nxt[x]]; //进入了之前就有的循环，直接继承，保证复杂度。
}
int main()
{
	read(n);
	for(res i=1;i<=n;++i) read(a[i]),a[i]=(a[i]%lcm+lcm)%lcm;
	for(res i=1;i<=n;++i) {
		read(m);
		for(res j=0;j<m;++j) read(b[j]);
		for(res j=0;j<lcm;++j) {
			int s=(a[i]+j)%lcm;int now=s%m;
			nxt[(i-1)*lcm+j]=s+(b[now]-1)*lcm; //nxt表示每一个状态的后继状态
		}
	}
	for(res i=0;i<n*lcm;++i) if(!col[i]) dfs(i,++sum); //没有被搜到过再搜
	read(m);
	while(m--) read(x),read(y),y=(y%lcm+lcm)%lcm,print(f[(x-1)*lcm+y],'\n'); //注意！取模有可能出现负数。
    return 0;
}
```

---

## 作者：_soul_ (赞：4)

第一次比赛的时候AK div 2 毕竟最后一题还算是比较简单的

首先你观察到$m_i$范围就只有1到10，所以只需要将每一个点拆成2520(1--10的lcm)个点，然后在拆完点之后的图中跑一遍dfs即可。

最近cf好喜欢考拆点啊，最近一场div1+div2中的F题也考到了
```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 2520;
int n;
int insta[1010][2530], ans[1010][2530];
int w[1010];
int dep[1010][2530];
int son[1010][12], len[1010];
int sta[2530000];
int cnt[1010];
inline int dfs(int x, int y) {
    insta[x][y] = 1;
    if(ans[x][y]) return ans[x][y];
    sta[dep[x][y]] = x;
    int newx = son[x][y % len[x]], newy = (y + w[newx]) % mod;
    if(insta[newx][newy]) {
        if(ans[newx][newy]) return ans[x][y] = ans[newx][newy];
        int l = dep[newx][newy], r = dep[x][y];
        for(int i = l; i <= r; i++) cnt[sta[i]] = 0;
        for(int i = l; i <= r; i++) if(cnt[sta[i]] == 0) cnt[sta[i]] = 1, ans[x][y]++;
        return ans[x][y];
    }
    dep[newx][newy] = dep[x][y] + 1;
    ans[x][y] = dfs(newx, newy);
    return ans[x][y];
}
int main() {
    ios :: sync_with_stdio(false);
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> w[i], w[i] = (w[i] % mod + mod) % mod;
    for(int i = 1; i <= n; i++) {
        cin >> len[i];
        for(int j = 0; j < len[i]; j++) cin >> son[i][j];
    }
    int q;
    cin >> q;
    while(q--) {
        int x, c;
        cin >> x >> c;
        c = (c % mod + mod) % mod;
        cout << dfs(x, (c + w[x]) % mod) << endl;
    }
    return 0;
}
```


---

## 作者：EllinY (赞：1)

[Codeforces AC 提交记录](https://codeforces.com/problemset/submission/1200/279020777)
# 题意
有一张图，可重边可自环。行走规则：初始时有一个值 $c$ 和所在的点 $x$，到达一个点就将 $c$ 加上点权 $k_x$，每次可以走从点 $x$ 连出去的第 $c\bmod m_x$ 条边，到达下一个点。有 $q$ 个询问，给你 $x$ 和 $c$，问在行走过程中有几个点会经过无限次（如果从一个点能走到一个环，问这个环包含的点数；否则是 $0$）。
# 思路
$q$ 和 $y$ 都太大了，发现 $m_i$ 很小。$y$ 对 $m_i$ 取模决定走到哪个点，可以先将 $y$ 对 $\operatorname{lcm}(1,2,3,\dots,10)$ 取模。因为 $m_i$ 在 $1$ 到 $10$ 范围内，无论对哪个 $m_i$，$\operatorname{lcm}(1,2,3,\dots,10)$ 都是它的倍数，所以不影响 $y$ 对每个 $m_i$ 取模的结果。$\\$ 当前的值 $y$ 对于边是有影响的，遂将 $(x,y)$ 作为一个状态。$\operatorname{lcm}(1,2,3,\dots,10)=2520$，那么状态数最多只有 $1000\times2520$ 种，只要用记忆化搜索处理出每种状态的答案，就可以 $O(1)$ 回答问题。
# 实现
由于 $x,y$ 确定，每种状态有固定的下一个状态：$tx=e_{x,y\bmod_x},ty=y+k_{tx}$。我们用 $cnt_{x,y}$ 记录答案，$flag_{x,y}$ 记录这个状态在第几次 dfs（在 main 函数里被调用第几次）的时候算到了。如果即将到达的状态的 $flag$ 是 $0$，就 dfs(tx,ty)；如果 $flag$ 等于当前的次数，就证明这个环是新找到的，计算环里有几个点并赋值给 $cnt_{x,y}$；如果这个状态在之前的 dfs 中就已经计算过了，证明这个环已经被找到过了，直接 $cnt_{x,y}=cnt_{tx,ty}$。最后查询答案的时候要把 $x$ 的点权加进去，答案是 $cnt_{x,y+k_x}$。$\\$ 过程中注意 $y$ 的取模，由于 $y$ 可能是负数，$y=(y\bmod2520+2520)\bmod2520$。计算环里点的个数时，要用 $vis$ 标记一个点是否数过了，因为 stack 记录的只有 $x$，而状态里是 $(x,y)$，可能重复。
在下图中，原本的路径是黑色的，更新答案的路径是蓝色的：$\\$![](https://cdn.luogu.com.cn/upload/image_hosting/a32wq5x6.png)
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 2520
int n,k[1005],m[1005],e[1005][15],q,a,b;
int cnt[1005][2520],st[2520000],pos[1005][2520],flag[1005][2520];
bool vis[1005];
void mo(int& x){ x=(x%mod+mod)%mod; }
void dfs(int x,int y,int id){
	flag[x][y]=id;
	st[pos[x][y]]=x;
	int tx=e[x][y%m[x]];int ty=y+k[tx];mo(ty);
	if(!flag[tx][ty]){
		pos[tx][ty]=pos[x][y]+1,dfs(tx,ty,id);
		cnt[x][y]=cnt[tx][ty];
	}
	if(flag[tx][ty]==id){
		for(int i=pos[tx][ty];i<=pos[x][y];i++)
			vis[st[i]]=0;
		for(int i=pos[tx][ty];i<=pos[x][y];i++)
			if(!vis[st[i]]) vis[st[i]]=1,cnt[x][y]++;
	}
	else cnt[x][y]=cnt[tx][ty];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&k[i]),mo(k[i]);
	for(int i=1;i<=n;i++){
		scanf("%d",&m[i]);
		for(int j=0;j<m[i];j++) scanf("%d",&e[i][j]);
	}
	int l=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<mod;j++)
			if(flag[i][j]==0) dfs(i,j,++l);
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		scanf("%d%d",&a,&b);
		b+=k[a];mo(b);
		printf("%d\n",cnt[a][b]);
	}
	return 0;
}
```
感谢阅读 Thanks♪(･ω･)ﾉ。

---

