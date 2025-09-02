# Tree

## 题目描述

## Tree

### 题目大意

需要维护一棵树，其中各点有其点权，要求支持 $q$ 次强制在线的操作：  

1. 加入一个叶子；  
2. 给出 $u, X$，查询满足下列条件的序列 $????[1 ⋯ t]$ 中的最大的 $t$：
   - 要求 $s_1 = t$；
   - 序列中所有节点的点权之和 $\le x$；
   - 有 $s_i + 1$ 为 $s_i$ 的祖先，同时有 $s_i + 1$ 的点权不小于 $s_i$ 的点权，且树中 $s_i \to s_{i+1}$ 一段链上的节点（不含 $s_i, s_{i+1}$）点权均小于 $s_i$ 的点权。


给出一个权重为 $0$ 且索引为 $1$ 的树节点。设 $cnt$ 为该树中节点的数量（初始时，$cnt$ 被设为 $1$）。支持 $Q$ 个查询，查询分为以下两种类型：

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF932D/da4b1378453cb99e049b53a08b0ba18e7ba1e551.png) 添加一个新节点（索引 `index` 为 $cnt + 1$）权重为 $W$，并在节点 $R$ 和此节点之间添加边；
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF932D/ed73083bdc6b75130b20ebceb85afda31415dcb3.png) 输出以 $R$ 为起始节点的节点序列的最大长度，该序列满足以下条件：
  1. 以 $R$ 开始；
  2. 序列中的每个节点都是其前驱的祖先；
  3. 序列中节点的权重之和不超过 $X$；
  4. 对于序列中连续的节点 $i,j$，如果 $i$ 是 $j$ 的祖先，则 $w[i] \geq w[j]$，且在从 $i$ 到 $j$ 的简单路径上不存在节点 $k$，使得 $w[k] \geq w[j]$。

树在任何时刻都以节点 $1$ 为根。

请注意，查询是以修改后的方式给出的。

## 说明/提示

在样例输入 1 中，$last=0$。

\- 查询 1: `1 1 1`，节点 $2$ （权重为 $1$）被添加到节点 $1$。

\- 查询 2: `2 2 0`，以 $2$ 为起始节点的节点序列中没有权重小于等于 $0$ 的节点。此时有 $last=0$ 。

\- 查询 3: `2 2 1`，答案是 $1$，序列为 $\{2\}$。此时有 $last=1$ 。

\- 查询 4: `1 2 1`，节点 $3$ （权重为 $1$）被添加到节点 $2$。

\- 查询 5: `2 3 1`，答案是 $1$，序列为 $\{3\}$。此处节点 $2$ 不能被添加，因为权重和不能大于 $1$。此时有 $last=1$ 。

\- 查询 6: `2 3 3`，答案是 $2$，序列为 $\{3,2\}$。此时有 $last=2$ 。

> 校对：Xue Ouyang & Emma Lee from MZES.

## 样例 #1

### 输入

```
6
1 1 1
2 2 0
2 2 1
1 3 0
2 2 0
2 2 2
```

### 输出

```
0
1
1
2
```

## 样例 #2

### 输入

```
6
1 1 0
2 2 0
2 0 3
1 0 2
2 1 3
2 1 6
```

### 输出

```
2
2
3
2
```

## 样例 #3

### 输入

```
7
1 1 2
1 2 3
2 3 3
1 0 0
1 5 1
2 5 0
2 4 0
```

### 输出

```
1
1
2
```

## 样例 #4

### 输入

```
7
1 1 3
1 2 3
2 3 4
1 2 0
1 5 3
2 5 5
2 7 22
```

### 输出

```
1
2
3
```

# 题解

## 作者：kkxacj (赞：4)

#### 思路

可以发现，每次加点对前面的点的贡献没有影响，所以可以对于每个点预处理。

观察最长链的限制，发现对于点 $i$ 只需要找到祖先中第一个比它大的点在哪就行了，可以倍增求。

对于每个点，找到第一个比它大的点后，可以发现，最后求的答案是从第 $i$ 个点开始往前的连续一段，考虑求一个前缀和，然后倍增看一段数是否满足条件，满足就加上贡献，继续往下就行了。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO{
    const int BUF=1<<21;
    char buff[BUF],*p1=buff,*p2=buff;
    #define getchar() (p1==p2&&(p2=((p1=buff)+fread(buff,1,BUF,stdin)),p1==p2)?EOF:*p1++)
    template<typename T>inline void read(T &x){
        char ch=getchar();x=0;
        while(!isdigit(ch)) ch=getchar();
        while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    }
    char obuf[BUF],*p3=obuf;
    inline void putch(char ch){
        if(p3-obuf<BUF) *p3++=ch;
        else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;
    }
    char ch[32],ctop;
    template<typename T>inline void print(T x){
    	if(x<0) putch('-'),x=~x+1;
        if(!x) return putch(48);
        while(x) ch[++ctop]=x%10+48,x/=10;
        while(ctop) putch(ch[ctop--]);
    }
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
const int N = 4e5+10;
int q,last,x,y,cnt,f[N][20],fa[N][20],cnt1,lg[N],dep[N],o,ans[N],ans1;
long long g[N][20],sum[N],z;
signed main()
{
	read(q); cnt++; 
	dep[cnt] = ans[cnt] = 1;
	while(q--)
	{
		read(x),read(y),read(z);
		y ^= last,z ^= last;
		if(x == 1)
		{
			cnt++;
			lg[cnt] = lg[cnt>>1]+1;
			dep[cnt] = dep[y]+1;
			f[cnt][0] = y; g[cnt][0] = z;
			for(int i = 1;i <= lg[dep[cnt]];i++)
			{
				f[cnt][i] = f[f[cnt][i-1]][i-1];
				g[cnt][i] = max(g[f[cnt][i-1]][i-1],g[cnt][i-1]);
			}
			if(g[y][0] >= z) fa[cnt][0] = y;
			else
			{
				o = f[cnt][0];
				for(int i = lg[dep[cnt]];i >= 0;i--)
					if(dep[o] >= (1<<i) && g[o][i] < z) o = f[o][i];
				fa[cnt][0] = o;
			}
			ans[cnt] = ans[fa[cnt][0]] + 1;
			sum[cnt] = sum[fa[cnt][0]] + z;
			for(int i = 1;i <= lg[ans[cnt]];i++)
				fa[cnt][i] = fa[fa[cnt][i-1]][i-1];
		}
		else
		{
			o = y;ans1 = 0;
			for(int i = lg[ans[y]];i >= 0;i--)
				if(ans[o] >= (1<<i) && sum[o]-sum[fa[o][i]] <= z) z -= (sum[o]-sum[fa[o][i]]),ans1 += (1<<i),o = fa[o][i];
			print(ans1),putch('\n');
			last = ans1;
		}
	}
	flush();
	return 0;
}
```

---

## 作者：duanyll (赞：4)

## 题意

一棵树开始只有一个1号点，权值为0，两种操作：

- `1 R W` 在R号点下面加一个cnt+1号点
- `2 R X` 从R号点开始向祖先走，依次选择R的祖先，要求权值依次增大，且已选择的点权值之和小于X，输出最多能选几个点

强制在线

## 题解

观察发现只要记录当前已选点序列中的最远点，就可以倍增合并两段的点权之和，回答时与X比较即可

由于新的点只会是叶节点，就可以在加点时倍增预处理出该点向上选取`1<<i`个合法点时的最远点和此时的点权之和。详见代码。

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

const int MAXN = 500010;
const int64 INF = 0x3f3f3f3f3f3f3f3fll;

int fa[MAXN][22];	//向上跳1<<i个权值大于u的点的编号，忽视权值小于u的点 
int64 w[MAXN];
int64 sum[MAXN][22];	//到第1<<i个满足要求的祖先的和 

void adde(int u,int v){
	if(w[u] >= w[v]){
		fa[v][0] = u;
	}else{
		for(int i = 20;i>=0;i--){
			if(w[fa[u][i]] < w[v]){
				u = fa[u][i];
			}
			fa[v][0] = fa[u][0];
		}
	}
	sum[v][0] = w[fa[v][0]];
	for(int i = 1;i<=20;i++){
		fa[v][i] = fa[fa[v][i-1]][i-1];
		if(fa[v][i] != 0){	//防爆int64
			sum[v][i] = sum[v][i-1] + sum[fa[v][i-1]][i-1];
		}else{
			sum[v][i] = INF;
		}		
	} 
}

int query(int r,int64 x){
	if(w[r] > x){
		return 0;
	}
	x -= w[r];
	int now = r,ans = 1;
	for(int i = 20;i>=0;i--){
		if(x - sum[now][i] >= 0){
			x -= sum[now][i];
			ans += 1<<i;
			now = fa[now][i];
		}
	} 
	return ans;
}

#include <cctype>
#include <cstdio>

inline int64 read() {
    int64 X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch)) {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch)) {
        X = (X << 3) + (X << 1) + (ch ^ 48);
        ch = getchar();
    }
    return w ? -X : X;
}

template<typename T>
inline void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

int main(){
	w[0] = INF;	//边界条件  
	memset(sum[1],INF,sizeof sum[1]);
	int64 last = 0;
	int q,cnt = 1;
	cin >> q;
	for(int i = 1;i<=q;i++){
		int64 opr,a,b;
		opr = read();
		a = read();
		b = read();
		a ^= last;
		b ^= last;
		//clog << a << ' ' << b << endl;
		if(opr == 1){
			w[++cnt] = b;
			adde(a,cnt);
		}else{
			last = query(a,b);
			write(last);
			putchar('\n');
		}
	}
}
```

注意INF要开int64，被坑了好久

---

## 作者：_AyachiNene (赞：3)

~~水紫。~~
# 思路：
首先容易发现一个性质，从一个点出发跳出的序列是固定的，如果我们能把它提出来进行一些操作就可以了。对于第一个操作，看起来像 Lct，其实没必要，每次新建的点是挂在最后的，只会对它自己有影响，可以直接改，用倍增跳到它第一次会跳上去的点，把它挂在这个序列的末尾就可以了。接下来考虑如何维护这个序列，直接存下来显然是不行的，因为一个点可能在多个序列里。但是可以发现，我们不在乎每一条序列具体长什么样，只用知道以某个点为结尾的序列就行。这里我用了个可持久化线段树，直接把加入的点用第一步跳到的点更新就能维护好。对于查询在线段树上二分一下就行。
# Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){char ch=getch();while(ch<'a'||ch>'z')ch=getch();while(ch>='a'&&ch<='z'){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
int n,m;
namespace Elaina
{
	struct segt
	{
		int l,r,cnt;
		ll val;
	}t[1145141<<3];
	int cnt,rt[114514<<2];
	#define mid (l+r>>1)
	int insert(int x,ll v,int root,int l=1,int r=m)
	{
		int cur=++cnt;
		t[cur]=t[root];
		if(l==r)
		{
			t[cur].val+=v;
			++t[cur].cnt;
			return cur;
		}
		if(x<=mid) t[cur].l=insert(x,v,t[cur].l,l,mid);
		else t[cur].r=insert(x,v,t[cur].r,mid+1,r);
		t[cur].val=t[t[cur].l].val+t[t[cur].r].val;
		t[cur].cnt=t[t[cur].l].cnt+t[t[cur].r].cnt;
		return cur;
	}
	int query(ll v,int root,int l=1,int r=m)
	{
		if(l==r) return t[root].val<=v?t[root].cnt:0;
		if(t[t[root].r].val<=v) return t[t[root].r].cnt+query(v-t[t[root].r].val,t[root].l,l,mid);
		return query(v,t[root].r,mid+1,r); 
	}
}
using namespace Elaina;
int f[114514<<2][20];
ll maxn[114514<<2][20];
ll val[114514<<2];
signed main()
{
	read(m);
	int lastans=0;
	++n;
	rt[1]=insert(1,0,rt[0]);
	val[0]=1e18;
	for(int i=0;i<20;i++) maxn[1][i]=1e18;
	for(int T=1;T<=m;T++)
	{
		ll op,x,y;
		read(op,x,y);
		x^=lastans,y^=lastans;
		if(op==1)
		{
			val[++n]=y;
			f[n][0]=x;
			maxn[n][0]=val[x];
			for(int i=1;i<20;i++) 
			{
				f[n][i]=f[f[n][i-1]][i-1];
				maxn[n][i]=max(maxn[f[n][i-1]][i-1],maxn[n][i-1]);
			}
			int u=n;
			for(int i=19;i>=0;i--) if(maxn[u][i]<val[n]) u=f[u][i];
			u=f[u][0];
			rt[n]=insert(n,y,rt[u]);
		}
		else write(lastans=query(y,rt[x])),putch('\n');
	}
	flush();
}
```

---

## 作者：djh0314 (赞：3)

[**洛谷**](https://www.luogu.com.cn/problem/CF932D)      
[**Codeforces**](https://codeforces.com/problemset/problem/932/D)      

## 题意
一开始只有一个节点，编号为 1，权重为 0，$cnt$ 初始值为 1。     
接下来给 $Q$ 个操作：      
- $1$ $R$ $W$：加入一个节点（编号为 $cnt+1$，同时 $cnt$ 加一），该节点的权重为 $W$，父亲为 $R$。
- $2$ $R$ $X$：寻找最大长度的链满足：
	1. 从 $R$ 开始。
    2. 每个节点都是前一个节点的祖先。
    3. 这些节点的和值不超过 $X$。
    4. 对于任意两个相邻的节点 $i$，$j$（$i$ 是 $j$ 的祖先，$w_i\ge w_j$），满足不存在节点 $k$ 位于 $i$ 到 $j$ 的简单路径上使得 $w_k\ge w_j$。
    
树的根恒定为 1。      
输入是加密的，所输入的 $R$ 与 $W$、$X$ 都需要异或上上一次 2 操作的答案。（初始值为 0）。

#### 希望能成为翻译。

## 解题

对于 2 操作的第 4 点，我们可以分析出，
1. 我们并不需要想背包一样寻找更多的可转移的点，我们是找到就与前面的答案相连。
2. 我们的 1 操作并不会影响其祖先的答案。

于是我们可以很快想到，我们可以用倍增来维护我们的答案。       
在构图上，我们可以选择离线先把整棵树建完，也可以采用在插入节点时处理。

对于维护倍增，我们是寻找祖先中最近的大于等于当前值的节点，为了找到这个节点，我们需要不断寻找大于当前锁定节点的方式，快速找到这个节点。

[**Code**](https://www.luogu.com.cn/paste/fsqkwd1s)。

---

## 作者：JK_LOVER (赞：2)

# 题意
给你一棵树，要你实现两个操作，且强制在线。[$qwq$](https://www.luogu.com.cn/blog/xzc/solution-cf932d)
- 在新建一个节点链接到原有节点。
- 查询当前节点 $X$ 到根节点有多少个值大于等于 $X$ 的，且路径长度小于一定值 $D$ 。
# 分析
如果我们暴力求解。那么插入节点的时间复杂度为 $O(1)$ ，查询操作的时间复杂度为 $O(n)$ 。考虑平衡时间复杂度。因为是没有修改操作的，那么当插入一个节点之后这个节点到根节点的路径就确定了。考虑优化暴力走父亲的过程。定义 $f_{i,j}$ 是节点 $i$ 的应该走的第 $2^j$ 节点，$s_{i,j}$ 是 $f_{i,j}$ 到 $i$ 的路径长度。那么只需要在插入一个节点时更新它的倍增数组就好了，时间复杂度 $O(\log n)$ 。查询的复杂度为 $O(\log n)$ 。讨论一下定值 $D$ 和 $s_{i,j}$ 的关系就好了。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
LL read() {
	LL x = 0,f = 0;char ch = getchar();
	while(!isdigit(ch)) {if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)) {x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
} 
const LL N = 4e5+100,inf = 0x3f3f3f3f3f3f3f3f;
LL val[N],fa[N][21],s[N][21],si = 1,ans = 0,Q;
void add(LL x,LL f) {
	if(val[f] >= val[x]) fa[x][0] = f;
	else {
		for(int i = 19;~i;i--) if(val[fa[f][i]] < val[x]) f = fa[f][i];
		fa[x][0] = fa[f][0];
	} 
	s[x][0] = val[fa[x][0]];
	for(int i = 1;i <= 19;i++) {
		fa[x][i] = fa[fa[x][i-1]][i-1];
		if(!fa[x][i]) s[x][i] = inf;
		else s[x][i] = (s[fa[x][i-1]][i-1] + s[x][i-1]) >= inf?inf:(s[fa[x][i-1]][i-1]+s[x][i-1]);
	}
} 
LL ask(LL x,LL tot) {
	if(tot-val[x] < 0) return 0;
	LL Ans = 1;tot -= val[x];
	for(int i = 19;~i;i--) if(tot >= s[x][i]) tot -= s[x][i],x = fa[x][i],Ans = (Ans+(1<<i));
	return Ans;
}
int main() {
	val[0] = inf;
	memset(s[1],0x3f,sizeof(s[1]));memset(s[0],0x3f,sizeof(s[0]));
	Q = read();
	while(Q--) {
		int opt = read();LL R = read()^ans,W = read()^ans;
		if(opt == 1) {
			val[++si] = W;
			add(si,R);
		}
		else {
			ans = ask(R,W);
			printf("%lld\n",ans);
		}
	}
}

```



---

## 作者：decoqwq (赞：2)

我们考虑插入时，如果 $x$ 的权值小于 $w$ ，就倍增跳到 $x$ 的 $2^i$ 父亲，找到第一个权值大于等于 $w$ 的节点设为新点的父亲，这样一定是满足条件，可以倍增找到第一个大于 $w$ 的，因为我们每次都这样插入一定保证了一条链从下到上权值递增，所以可以倍增，然后倍增处理出向上 $2^i$ 级祖先的权值和，能选多少选多少即可，主要需要注意的就是要把 $0$ 号点的权值赋值为 $inf$ ，然后 $1$ 节点的 $2^i$ 级总和赋值为 $inf$ ，就做完了qwq

时空复杂度 $O(nlogn)$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int inf=0x3f3f3f3f3f3f3f3f;
int cnt=1,f[400010][20],sum[400010][20],q,w[400010];
void insert(int fa,int val)
{
	w[++cnt]=val;
	if(w[cnt]<=w[fa])
	{
		f[cnt][0]=fa;
	}
	else
	{
		for(int i=19;i>=0;i--)
		{
			if(w[f[fa][i]]<w[cnt])
			{
				fa=f[fa][i];
			}
		}
		f[cnt][0]=f[fa][0];
	}
	if(f[cnt][0]==0)
	{
		sum[cnt][0]=inf;
	}
	else
	{
		sum[cnt][0]=w[f[cnt][0]];
	}
	for(int i=1;i<=19;i++)
	{
		f[cnt][i]=f[f[cnt][i-1]][i-1];
		if(f[cnt][i]==0||sum[cnt][i-1]==inf)
		{
			sum[cnt][i]=inf;
		}
		else
		{
			sum[cnt][i]=sum[cnt][i-1]+sum[f[cnt][i-1]][i-1];
		}
	}
}
int query(int x,int val)
{
	if(w[x]>val)
	{
		return 0;
	}
	val-=w[x];
	long long ans=1;
	for(int i=19;i>=0;i--)
	{
		if(sum[x][i]<=val)
		{
			val-=sum[x][i];
			ans+=(1<<i);
			x=f[x][i];
		}
	}
	return ans;
}
signed main()
{
	cin>>q;
	int last=0;
	w[0]=inf,w[1]=0;
	memset(sum[1],0x3f,sizeof(sum[1]));
	for(int i=1;i<=q;i++)
	{
		int opt,x,y;
		scanf("%lld%lld%lld",&opt,&x,&y);
		x^=last,y^=last;
		if(opt==1)
		{
			insert(x,y);
		}
		else
		{
			last=query(x,y);
			cout<<last<<"\n";
		}
	}
}
```

---

## 作者：STPGUY (赞：1)

# [Tree](https://www.luogu.com.cn/problem/CF932D)

## 题目大意：
- 首先，我们有$Q$次操作

> - 操作$1$：在节点$R$下面再加一个权值为$W$的点
> - 操作$2$：询问从点$X$开始往上走，（每次遇到权值大于当前选过的最后一个点的点必定会选），问最多能选多少点

## 分析

我们可以很容易的发现，我们选中的点一定是一个单调不下降序列

那么就是说，我们可以稍微改动一下操作一，让每一条链都一定是单调不上升的（从根出发的链）

然后，我们每次加入的点必定不会是已经存在的某个点的祖先，所以我们改变他的位置对原来的树是没有影响的

若有节点成为了这个被我们认为操作的节点的儿子，它的值依赖于我们人为操作的那个点，所以这个答案也不会因为我们的操作出现问题

那么我们就可以在加入节点的时候，找到第一个权值大于该节点的点做为这个点的父节点

顺便跟新一下前缀和

这个用倍增实现就好了
```cpp
inline void AddPoint(ll u, ll p)
{
    ll v = ++cnt;
    wight[v] = p;
    if (wight[u] >= wight[v]) {
        father[v][0] = u;
    } else {
        for (ll i = 19; ~i; --i)
            if (wight[father[u][i]] < wight[v])
                u = father[u][i];
        father[v][0] = father[u][0];
    }
    sum[v][0] = wight[father[v][0]]; 
    for (ll i = 1; i < 20; ++i) {
        father[v][i] = father[father[v][i - 1]][i - 1];
        if (sum[v][i - 1] < inf && father[v][i]) {
            sum[v][i] = sum[v][i - 1] + sum[father[v][i - 1]][i - 1];
        } else break;
    }
}
```

然后查询的话，能跳就跳，每次向上跳了更新一下限制即可

```cpp
inline ll Query(ll x)
{
    if (wight[x] > limit) return 0;
    ll ans(1);
    limit -= wight[x];
    for (ll i = 19; ~i; --i)
        if (sum[x][i] <= limit) {
            ans += (1 << i);//向上跳了2的i次方层，那就有2的i次方个点
            limit -= sum[x][i];
            x = father[x][i];
        }
    return ans;
}
```

## Code
```cpp
int main()
{
    memset (sum, 0x6f, sizeof sum);
    wight[0] = inf;
    Q = Read();
    while (Q--)
    {
        Opt = Read(), X = Read() ^ lastans, Y = Read() ^ lastans;
        if (Opt == 1) AddPoint(X, Y);
        else limit = Y, printf ("%lld\n", lastans = Query(X));
    }
    system("pause");
}
```
至于这份代码常数巨大，跑了30s+

[JK_LOVER](https://www.luogu.com.cn/record/38015293)这位巨佬快了我好几秒

---

## 作者：yzy4090 (赞：0)

考虑我们要求的路径，不难发现只要给定起点 $R$，整条路径都可以计算，因此可以不停跳到第一个权值大于等于当前点的祖先。对于“权值和 $\le X$”的约束，再多记录一个权值和，倍增判断即可。  
接下来就是计算出对于每个点，第一个权值大于等于它的祖先。由于加入点的方式的特殊性，这对之前的节点没有影响，因此和处理询问类似地倍增向上跳。  
这样的时空复杂度均为单 $\log$ 的。[代码](https://www.luogu.com.cn/paste/xngq4hk4)

---

## 作者：Hoks (赞：0)

## 前言
有意思的题，但是我差点没看懂题意。

倍增，还是太蒻了。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842#information)。
## 思路分析
首先给个简要题意：
> - 给定 $n$ 个操作，操作种类有两种：
> - $1$ 操作，给定点 $cnt+1$ 的父亲与权值，同时 $cnt\leftarrow cnt+1$。
> - $2$ 操作，给定点 $x$，依次选择 $x$ 的祖先，满足权值单增且总和小于给定值。
> - $n\le4\times10^5$，强制在线。

树形结构，却强制在线，就很有意思了。

考虑树的特点，显然的是对于一个点 $x$，他到根节点的路径是固定的。

暴力的做这个问题，就是一步一步往上跳，碰到能选的就选上。

这样是 $O(1)$ 插入 $O(n)$ 查询。

考虑优化，因为要动态插入，所以考虑倍增来做到 $O(\log n)$ 插入/查询。

考虑 $f_{i,j}$ 是从 $i$ 走 $2^j$ 步**应该走到的点**，也就是满足权值单增的点。

用 $s_{i,j}$ 表示从 $i$ 跳了这 $2^j$ 步的路径长度。

倍增插入查询即可，记得给 $0,1$ 赋极大值。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+10,INF=0x3f3f3f3f3f3f3f3f,lim=20;
int n,w[N],f[N][lim],s[N][lim];
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
    inline bool chk(char c) { return !(c>='A'&&c<='Z'); }
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
inline void add(int u,int v,int x)
{
    if(w[u]<x) for(int i=lim-1;i>=0;i--) if(w[f[u][i]]<x) u=f[u][i];
    f[v][0]=u=(w[u]>=x?u:f[u][0]);s[v][0]=w[u];
    for(int i=1;i<lim;i++) f[v][i]=f[f[v][i-1]][i-1],s[v][i]=(f[v][i]?min(INF,s[f[v][i-1]][i-1]+s[v][i-1]):INF);
}
inline int query(int u,int d)
{
    int res=0;
    for(int i=lim-1;i>=0;i--) if(s[u][i]<=d) d-=s[u][i],u=f[u][i],res+=(1<<i);
    return res+1;
}
signed main()
{
    n=read();w[0]=INF;memset(s[1],0x3f,sizeof s[1]);memset(s[0],0x3f,sizeof s[0]);
    for(int i=1,op,x,y,lst=0,tot=1;i<=n;i++)
    {
        op=read(),x=read()^lst,y=read()^lst;
        if(op==1) w[++tot]=y,add(x,tot,y);
        else print(lst=(y>=w[x]?query(x,y-w[x]):0)),put('\n');
    }
    genshin:;flush();return 0;
}
```

---

## 作者：lgswdn_SA (赞：0)


VP 时就我没做出来这题而且题还读错……让我坚信我是个傻子

由于每个点往上跳的路径是固定的，所以我们首先考虑一个不大劣的暴力，就是每次操作1时记录点 $u$ 应该跳到哪个点。然而暴力跳太费时间了。我们考虑倍增地跳。所以我们考虑维护一个 $f_{u,h}$，表示 $u$ 向上跳 $2^h$ 步达到的点。然后我们记录一个 $s_{u,h}$ 表示跳 $2^h$ 步所跳过的点的权值和，这样就能求出题目所求了。

然后你会发现树的原形态就不需要记录了。这就是为什么有些题解中提到可以改动树的形态。

加入的时候，我们从 $R$ 结点向上跳。理由很简单：如果 $W_u<W_R$，那么我们直接连；否则由于一定能在 $R$ 向上跳的序列中找到一个比 $W_u$ 大的第一个结点（感性理解）。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=4e5+9,inf=0x3f3f3f3f3f3f3f3f;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

struct edge {int to,nxt;} e[N*2]; int hd[N],tot;
void add(int u,int v) {e[++tot]=(edge){v,hd[u]};hd[u]=tot;} 

int Q,lst,cnt=1,w[N],f[N][29],s[N][29];

void add(int u,int v,int x) {
	if(w[u]<x) per(h,20,0) if(w[f[u][h]]<x) u=f[u][h];
	f[v][0]=u=(w[u]>=x?u:f[u][0]);
	s[v][0]=w[u];
	rep(h,1,20)
		f[v][h]=f[f[v][h-1]][h-1],
		s[v][h]=(f[v][h]?min(inf,s[f[v][h-1]][h-1]+s[v][h-1]):inf);
}
int query(int u,int d,int ret=0) {
	per(h,20,0) if(s[u][h]<=d) d-=s[u][h], u=f[u][h], ret+=(1<<h);
	return ret+1;
}

signed main() {
	Q=read();
	w[0]=inf; memset(s[1],0x3f,sizeof(s[1])), memset(s[0],0x3f,sizeof(s[0]));
	while(Q--) {
		int opt=read(), p=read(), q=read();
		int r=p^lst, x=q^lst;
		if(opt==1) w[++cnt]=x, add(r,cnt,x);
		else printf("%lld\n",lst=(x>=w[r]?query(r,x-w[r]):0));
	}
	return 0;
}
```

---

