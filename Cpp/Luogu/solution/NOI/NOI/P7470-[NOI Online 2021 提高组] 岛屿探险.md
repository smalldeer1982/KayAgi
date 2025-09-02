# [NOI Online 2021 提高组] 岛屿探险

## 题目描述

凇睦是一个喜欢探险的女孩子，这天她到一片海域上来探险了。

在这片海域上一共有 $n$ 座岛屿排成一排，标号为 $1,2,3, \ldots ,n$。每座岛屿有两个权值，分别为劳累度 $a_i$ 和有趣度 $b_i$。

对于一座劳累度为 $a$，有趣度为 $b$ 的小岛，如果这个小岛满足 $(a\oplus c) \leq \min(b,d)$，凇睦到这座岛探险就会感到开心，其中 $c$ 表示凇睦到岛上去之前就有的劳累度（称作初始劳累度），同理 $d$ 代表凇睦的初始有趣度。$\oplus$ 表示二进制异或（即二进制表示下不进位的加法）。

为了玩的更尽兴，凇睦会向你询问 $q$ 次，每次给出一个区间 $[l_i,r_i]$ 和两个数 $c_i,d_i$，你需要告诉凇睦若她的初始劳累度为 $c_i$，初始有趣度为 $d_i$，则有多少个标号在 $[l_i,r_i]$ 这个区间内的岛屿能使凇睦探险时感到开心。

## 说明/提示

测试点 $1,2$ 满足 $1\leq n,q\leq 5000$。

测试点 $3,4$ 满足 $1\leq n,q\leq 10^4$。

测试点 $5,6,7$ 满足 $1\leq n,q\leq 10^5$ 且 $\max\{d_i\}\leq \min\{b_i\}$。

测试点 $8,9,10,11$ 满足 $1\leq n,q\leq 10^5$ 且 $\min\{d_i\}\geq \max\{b_i\}$。

测试点 $12,13$ 满足 $1\leq n,q\leq 10^5$ 且 $l_i=1,r_i=n$。

测试点 $14,15,16$ 满足 $1\leq n,q\leq 7\times 10^4$。

测试点 $17,18,19,20$ 满足 $1\leq n,q\leq 10^5$。

所有数据满足 $1\leq n,q\leq 10^5$， $1\leq a_i,b_i,c_i,d_i\leq 2^{24}-1$。

## 样例 #1

### 输入

```
4 2
1 1
4 2
5 1
2 7
1 4 6 5
2 4 3 3```

### 输出

```
2
1```

## 样例 #2

### 输入

```
20 10
215 144
2 110
174 132
214 142
116 108
155 192
236 208
216 214
99 220
236 118
190 81
230 131
10 238
189 198
183 13
45 193
14 234
208 192
126 19
49 38
7 14 251 184
2 18 89 76
11 15 49 196
8 11 83 139
10 15 119 239
9 16 148 120
11 17 225 34
15 16 3 46
14 15 86 227
7 18 252 103```

### 输出

```
7
2
2
2
1
3
1
1
0
7```

# 题解

## 作者：duyi (赞：65)

[噜啦噜啦咧，噜啦噜啦咧的阅读体验](https://www.cnblogs.com/dysyn1314/p/14585866.html)


# 「NOI Online 2021 #1」岛屿探险

## 题目大意

给定一排 $n$ 个元素，每个元素有两个属性：$a_i, b_i$。

有 $q$ 次询问，每次询问给出四个参数 $l_j, r_j, c_j, d_j$。问区间 $[l, r]$ 里满足 $a_i\operatorname{xor} c_j \leq \min\{b_i, d_j\}$ 的 $i$ 有多少个。

数据范围：$1\leq n,q\leq 10^5$，$1\leq l_j\leq r_j\leq n$，$0\leq a_i, b_i, c_j, d_j\leq 2^{24} - 1$。

## 本题题解

**0. 约定**

设 $m = \max\{a_i, b_i, c_j, d_j\}$，这是分析复杂度用的。

---

**1. 分析一次询问**

对于一次询问 $l_j, r_j, c_j, d_j$，考虑把 $i$ 分为 $b_i > d_j$ 和 $b_i\leq d_j$ 两类，分别统计答案。

**1.1. b[i] > d[j] 的 i**

对于 $b_i > d_j$ 的 $i$，答案是 $\sum_{i} [a_i \operatorname{xor} c_j\leq d_j]$。此时的特点是：答案与 $b_i$ 无关。考虑把这些 $a_i$ 插入到一个 $\text{01 trie}$ 中：也就是按二进制从高位到低位的顺序，把 $a_i$ 当成一个 $01$ 串。我们在 $\text{01 trie}$ 上从根往下走（也就是按二进制从高位向低位走），对于当前节点，假设它深度为 $h$，那么它代表的值等于 $c_j\operatorname{xor}d_j$ 的前 $h$ 高位。考虑下一位：

- 如果 $d_j$ 的下一位为 $0$，那么说明 $a_i$ 的下一位必须和 $c_j$ 的下一位相等（否则 $a_i \operatorname{xor} c_j > d_j$，不满足要求），我们直接向这个方向走即可。
- 如果 $d_j$ 的下一位为 $1$，那么有两种可能：
  - 如果 $a_i$ 的下一位和 $c_j$ 的下一位相等，那么无论 $a_i$ 后面更低的位上填什么，都一定满足：$a_i\operatorname{xor} c_j < d_j$。所以 $a_i$ 后面的位可以任意填，方案数就是这一整棵子树里 $a_i$ 的个数之和。
  - 如果 $a_i$ 的下一位和 $c_j$ 的下一位不相等，那么此时 $a_i$ 仍然是等于 $c_j \operatorname{xor} d_j$ 的。我们向这个方向走过去，然后考虑更低的位即可。

**1.2. b[i] <= d[j] 的 i**

对于 $b_i \leq d_j$ 的 $i$，答案是 $\sum_{i} [a_i \operatorname{xor} c_j\leq b_i]$。看到限制里既有 $a_i$，又有 $b_i$，我们难以把它们放到同一个数据结构里去，所以很难实现查询。换个角度考虑：观察 $a_i\operatorname{xor} c_j \leq \min\{b_i, d_j\}$ 这个式子，你会发现 $(a, b)$ 和 $(c, d)$ 是**对称**的。那么，把修改当成询问做，询问当成修改做，是不是就和 1.1. 的情况一样了呢？

具体来说，我们将询问离线，把所有 $c_j$，按上述方法（和上面的 $a_i$ 一样）插入一个 $\text{01 trie}$ 中。然后对每组 $(a_i, b_i)$，把它当成上面的 $(c_j, d_j)$，在 $\text{01 trie}$ 上“查询”。当然，我们其实不是要查询一个结果，而是要把它“贡献”到符合条件的 $c_j$ 里。在 1.1, 里，我们遇到一整棵符合条件的子树，就把这个子树里 $a_i$ 的数量加入答案中；而现在，我们遇到一整棵符合条件的子树，就在该节点处打一个标记，表示令子树里所有 $c_j$ 的答案加上 $1$。最后，每个 $j$ 的答案，就是 $c_j$ 到根路径上的标记之和。

---

**2. 多次询问时**

当然我们不可能每次询问都重新建两个 $\text{trie}$，那样时间复杂度是 $\mathcal{O}(qn\log m)$，还不如暴力。

考虑一个简化的问题：如果只有 $b_i > d_j$ 的 $i$（也就是测试点 $5\sim 7$），那么可以在所有询问开始前，先建好一个可持久化 $\text{trie}$。则查询时，将 $r_j$ 和 $l_j - 1$ 两个时刻的 $\text{trie}$ 上查询的结果相减即可。时间复杂度 $\mathcal{O}(q\log m)$。

考虑另一个简化的问题：如果只有 $b_i \leq d_j$ 的 $i$（也就是测试点 $8\sim 11$），那么可以先将询问离线，建出所有 $c_j$ 的 $\text{trie}$。然后将询问拆成两个：$[1, r_j]$ 和 $[1, l_j - 1]$（相减得到答案）。现在所有询问的左端点都是 $1$。将询问按右端点排序，从小到大扫描。每次加入当前的 $i$（如前文所述，这个加入操作有点像 1.1. 里的查询操作，只不过把查询变成了打标记），然后对右端点为 $i$ 的询问统计答案。时间复杂度 $\mathcal{O}(q\log m)$。

上述两种情况我们都会做了，那么现在唯一的问题是，怎么把 $b_i > d_j$ 的 $i$ 和 $b_i\leq d_j$ 的 $i$ **分离出来**。考虑把所有 $b_i, d_j$ 放在一起排序（特别地，$b_i, d_j$ 想到时，$b_i$ 放在前）。然后做 $\text{cdq}$ 分治。那么每次只需要考虑右半边对左半边的贡献。具体来说，取出右半边的所有 $a_i$，左半边的所有 $(c_j,d_j)$，按情况 1.1. 的方法做一次；再取出右半边的所有 $c_j$，左半边的所有 $(a_i,b_i)$，按情况 1.2. 的方法做一次。就求出所有答案了。

每层分治时，做问题 1.1. 和 1.2.，时间复杂度是 $\mathcal{O}(\mathrm{len}\log m)$（$\mathrm{len}$ 是当前分治区间的长度），所以总时间复杂度 $\mathcal{O}((n + q)\cdot \log (n + q)\cdot  \log m)$。

## 参考代码

[勇敢向前进，前进有奖品！！！！](https://www.cnblogs.com/dysyn1314/p/14585866.html)

---

## 作者：panyf (赞：26)

首先根据套路，将询问差分为 $[1,r_i]-[1,l_i-1]$。

对于每个岛屿 $(a,b)$,满足 $a\oplus c\leq b$ 的 $c$ 形如 $\log$ 个区间，每个区间都是从高位到低位有一个前缀 $01$ 取值固定，剩下的随便取。容易发现这些区间每个只对应 $[0,2^{24}-1]$ 的线段树上的一个区间。

将岛屿 $(a,b)$ 插入对应的 $\log$ 个区间，询问 $(c,d)$ 插入所有包含 $c$ 的区间，并按编号排序。

现在问题转化为每次插入一个 $a$，或者查询有多少个 $a$ 满足 $a\oplus c\leq d$。建 $01 trie$ 并维护子树 $size$，$trie$ 上二分即可。

实现时可以将询问离线插入对应区间，而不是直接建出线段树。

时间复杂度 $O(n\log^2 w)$,空间 $O(n\log w)$。

注意 $01trie$ 空间是 $O(n\log w)$ 而不是 $O(n)$！考场代码数组开小挂了。

还有这题时间和空间都很卡，需要精细实现（比如用邻接表代替 vector）。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=75e5+3,N=25e5+3,O=1e5+3;
int he[33554499],ne[M],to[M],t,a[O],b[O],c[O],d[O],u,w,ans[O],ct,ch[N][2],sz[N]; 
vector<int>v[O];
void add(int x,int y){ne[++t]=he[x],to[t]=y,he[x]=t;}
void work(int k,int l,int r){
	add(k,u);
	if(l==r)return;
	int m=l+r>>1;
	w>m?work(k*2+1,m+1,r):work(k*2,l,m);
}
int qry(int c,int d){
	bool o;
	int i=1<<23,x=1,r=0;
	for(;i&&x;i>>=1){
		if(d&i){
			o=c&i,r+=sz[ch[x][o]],x=ch[x][!o];
		}else{
			o=c&i,x=ch[x][o];
		}
	}
	return r+sz[x];
}
void upd(int a){
	bool o;
	int i=1<<23,x=1;
	for(;i;i>>=1){
		if(o=a&i,!ch[x][o])ch[x][o]=++ct,sz[ct]=ch[ct][0]=ch[ct][1]=0;
		x=ch[x][o],++sz[x];
	}
}
int main(){
	int n,q,i,j,k,l;
	scanf("%d%d",&n,&q);
	for(i=1;i<=n;++i)scanf("%d%d",a+i,b+i);
	for(i=1;i<=q;++i){
		scanf("%d%d%d%d",&j,&k,c+i,d+i);
		v[j-1].push_back(-i),v[k].push_back(i); 
	}
	for(i=n;i;--i){
		l=v[i].size();
		for(j=0;j<l;++j){
			u=v[i][j],w=c[abs(u)];
			work(1,0,(1<<24)-1);
		}
		k=1;
		for(j=1<<23;j;j>>=1){
			k*=2;
			if(j&a[i])k^=1;
			if(j&b[i]){
				add(k,i+q);
				k^=1;
			}
		}
		add(k,i+q);
	}
	for(i=(1<<25)-1;~i;--i)if(k=he[i]){
		ct=1,ch[1][0]=ch[1][1]=sz[1]=0;
		for(;k;k=ne[k]){
			l=to[k];
			if(l<0)ans[-l]-=qry(c[-l],d[-l]);
			else if(l<=q){
				ans[l]+=qry(c[l],d[l]);
			}
			else upd(a[l-q]);
		}
	}
	for(i=1;i<=q;++i)printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：Daniel13265 (赞：24)

> 给两个长 $n$ 的数列 $a,b$，$q$ 次询问，每次询问给出 $l_i,r_i,c_i,d_i$，求有多少个 $j$ 满足 $l_i\le j\le r_i$ 且 $(a_j\oplus c_i)\le\min(b_j,d_i)$。
> 
> $1\le n,q\le10^5$，$1\le l_i\le r_i\le n$，$1\le a_i,b_i,c_i,d_i<2^{24}$。

**这是一篇指令集题解，不是正解。如果想要知道正解请移步其他题解。另外，不要尝试在正式 OI 竞赛中使用指令集。**

我们发现这是一个序列上问题，并且 $O\left(nq\right)$ 暴力非常好写，于是我们考虑指令集。

我们需要能够同时对多个数判断 $(a\oplus c)\le\min(b,d)$，这等价于 $(a\oplus c)\le b$ 且  $(a\oplus c)\le d$。由于 $\oplus$，$\le$ 与 $\&$ 都是指令集基本运算，所以我们已经做完了。

顺便借此推广一下一种（可能）更好写更好记的写法，具体可见代码。需注意布尔真值为二进制全一。

```cpp
#pragma GCC target("sse", "avx2")

#include <cstdio>
#include <algorithm>

char ibuf[1 << 20], obuf[1 << 20];
const char *sp, *ep;
char *op = obuf;

#define gc() (sp == ep && (ep = (sp = ibuf) + fread(ibuf, 1, sizeof ibuf, stdin)), *sp++)
#define flush() (fwrite(obuf, 1, op - obuf, stdout), op = obuf)
#define pc(c) (op == obuf + sizeof obuf && flush(), *op++ = (c))

int read() {
  static int c, x;
  while ((c = gc()) < 48) {}
  x = c & 15;
  while ((c = gc()) >= 48) x = x * 10 + (c & 15);
  return x;
}
void write(const int &x) {
  if (x >= 10) write(x / 10);
  pc((x % 10) | 48);
}

typedef unsigned u256 __attribute((vector_size(32)));

const int N = 100000 >> 3;

u256 ans, cs, ds, tp;
u256 a[N], b[N];

int main() {
  const int n = read();
  int q = read();
  for (int i = 0; i < n; ++i) {
    a[i >> 3][i & 7] = read();
    b[i >> 3][i & 7] = read();
  }
  while (q--) {
    const int l = read() - 1, r = read() - 1;
    const unsigned c = read(), d = read();
    cs = u256{ c, c, c, c, c, c, c, c };
    ds = u256{ d, d, d, d, d, d, d, d };
    ans = u256{ 0, 0, 0, 0, 0, 0, 0, 0 };
    int res = 0;
    if ((l >> 3) == (r >> 3)) {
      for (int i = l & 7; i <= (r & 7); ++i) {
        res += (a[l >> 3][i] ^ c) <= std::min(b[l >> 3][i], d);
      }
    } else {
      for (int i = l & 7; i <= 7; ++i) {
        res += (a[l >> 3][i] ^ c) <= std::min(b[l >> 3][i], d);
      }
      for (int i = 0; i <= (r & 7); ++i) {
        res += (a[r >> 3][i] ^ c) <= std::min(b[r >> 3][i], d);
      }
      for (int i = (l >> 3) + 1; i != (r >> 3); ++i) {
        tp = a[i] ^ cs;
        ans += (tp <= b[i]) & (tp <= ds);
      }
      for (int i = 0; i <= 7; ++i) res -= ans[i];
    }
    write(res);
    pc(10);
  }
  flush();
  return 0;
}

```

---

## 作者：hsfzLZH1 (赞：16)

本篇题解有不一样的分治做法。

### 题目大意

给定 $n$ 个数对 $a_i,b_i$ ， $q$ 次询问，每次询问给定 $l,r,c,d$ ，询问区间 $[l,r]$ 内满足 $a_i\oplus c\le \min\{b_i,d\}$ 的 $i$ 的个数。

$1\le n,q\le 10^5,1\le a_i,b_i,c,d\le 2^{24}-1$

### 解题思路

首先考虑 $l=1,r=n$ 时的做法。

将数对按 $b_i$ 升序排序，询问按 $d$ 升序排序。可以将数对划分为两个集合，即 $\min\{b_i,d\}=d$ 的集合 $A$ 和 $\min\{b_i,d\}=b_i$ 的集合 $B$ 。依次考虑每一个询问，每次会有一些数对从集合 $A$ 被划分到集合 $B$ 。只需对 $A,B$ 分别计数并求和即可。

考虑集合 $A$ 的做法。即查询 $c,d$ ，求 $a_i\oplus c\le d$ 的数对个数。将 $a_i$ 插入 01-Trie ，查询异或 $c$ 小于等于 $d$ 的子树大小即可。

考虑集合 $B$ 的做法。即查询 $c$ ，求 $a_i\oplus c\le b_i$ 的数对个数。将 $\oplus a_i\le b_i$ 的子树大小 $+1$ ，查询时求 $c$ 处的大小即可。

现在我们在 $O(n\log a_i)$ 的时间复杂度内解决了 $l=1,r=n$ 时的问题。套用一层分治算法，就可以解决 $l,r$ 任意时的问题。本篇题解用的是类似于线段树分治的做法，这也是本篇题解和其他题解不同之处。

观察到将询问区间拆分成若干区间再对询问答案求和，答案不变。将每个询问区间都 **拆分成线段树上的区间** 。这样最多拆分成 $O(n\log n)$ 个区间，对每个线段树上区间分别向之前那样求解即可。时间复杂度 $O(n\log n\log a_i)$ ，空间复杂度 $O(n\log a_i)$ 。

### 参考代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn=100010;
typedef long long ll;
int n,q,l,r,ans[maxn],id[maxn];
ll a[maxn],b[maxn],c[maxn],d[maxn];
#define lc (o<<1)
#define rc (o<<1|1)
vector<int>g[maxn*4];
bool cmp(int x,int y){return d[x]<d[y];}
bool ccc(int x,int y){return b[x]<b[y];}
void update(int o,int l,int r,int ql,int qr,int v)
{
	if(r<ql||l>qr)return;
	if(ql<=l&&r<=qr){g[o].push_back(v);return;}
	int mid=(l+r)>>1;
	update(lc,l,mid,ql,qr,v);update(rc,mid+1,r,ql,qr,v);
}
struct Trie
{
	int cnt,rt,ch[maxn*40][2],siz[maxn*40];
	void clear()
	{
		for(int i=1;i<=cnt;i++)ch[i][0]=ch[i][1]=siz[i]=0;
		cnt=rt=1;
	}
	void insert1(int x,ll v)
	{
		int nww=rt;siz[nww]+=v;
		for(int i=24;i>=0;i--)
		{
			int c=((x>>i)&1ll);
			if(!ch[nww][c])ch[nww][c]=++cnt;
			nww=ch[nww][c];siz[nww]+=v;
		}
	}
	int query1(int x,ll d,ll c,int k)//min(b,d)=d
	{
		if(!x)return 0;
		if(k==-1)return siz[x];
		int dc=((d>>k)&1ll),cc=((c>>k)&1ll);
		if(dc==0)return query1(ch[x][cc],d,c,k-1);
		else return siz[ch[x][cc]]+query1(ch[x][cc^1],d,c,k-1);
	}
	void insert2(int x,ll a,ll b,int k)//min(b,d)=b
	{
		if(!x)return;
		if(k!=-1){if(!ch[x][0])ch[x][0]=++cnt;if(!ch[x][1])ch[x][1]=++cnt;}
		else {siz[x]++;return;}
		int ac=((a>>k)&1ll),bc=((b>>k)&1ll);
		if(bc==0)insert2(ch[x][ac],a,b,k-1);
		else siz[ch[x][ac]]++,insert2(ch[x][ac^1],a,b,k-1);
	}
	int query2(int x,ll d,int k)
	{
		if(!x)return 0;
		if(k==-1)return siz[x];
		int dc=((d>>k)&1ll);
		return siz[x]+query2(ch[x][dc],d,k-1);
	}
}A,B;//A:min(b,d)=d,B:min(b,d)=b
void solve(int o,int l,int r)
{
	sort(g[o].begin(),g[o].end(),cmp);
	for(int i=l;i<=r;i++)id[i]=i;sort(id+l,id+r+1,ccc);
	A.clear();B.clear();
	for(int i=l;i<=r;i++)A.insert1(a[id[i]],1);
	int cur=l;
	for(int i=0;i<g[o].size();i++)
	{
		for(;d[g[o][i]]>=b[id[cur]]&&cur<=r;cur++)A.insert1(a[id[cur]],-1),B.insert2(1,a[id[cur]],b[id[cur]],24);
		ans[g[o][i]]+=A.query1(1,d[g[o][i]],c[g[o][i]],24)+B.query2(1,c[g[o][i]],24);//;,printf("A %d B %d\n",A.query1(1,d[g[o][i]],c[g[o][i]],24),B.query2(1,c[g[o][i]],24));
	}
	if(l==r)return;
	int mid=(l+r)>>1;
	solve(lc,l,mid);solve(rc,mid+1,r);
}
signed main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)scanf("%lld%lld",a+i,b+i);
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d%lld%lld",&l,&r,c+i,d+i);
		update(1,1,n,l,r,i);
	}
	solve(1,1,n);
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
	return 0;
}
```

运行时间的瓶颈仍然在每次的排序上。现在有一些方法可以使对每个线段树上结点排序的总复杂度降低为 $O(n\log n)$ 。常数更小的代码稍后奉上。

---

## 作者：jun头吉吉 (赞：14)

## 题意
有两个长度为 $n$ 的序列 $a,b$，给出 $q$ 组询问，每组询问有 $l,r,c,d$，问在 $i\in[l,r]$ 有多少满足 $(a_i\oplus c)\le \min(b_i,d)$
## 题解
暴力开 $\rm O_2$ $80$ 分就很离谱。

一个一个点往下看。
### $1\sim 4$
暴力随便跑好吧。

循环展开参见 `namespace solve1`
### $5\sim 7$ $\max\{d_i\}\leq \min\{b_i\}$
这个点 $(a_i\oplus c)\le \min(b_i,d)$ 事实上就是 $(a_i\oplus c)\le d_i$。这个 $[l,r]$ 明显可以差分，变成 $[1,r]-[1,l-1]$。

于是问题就变成了对于 $[1,x]$ 的个数，那么先对 $[1,x]$ 的 $a_i$ 建一棵字母树，然后给定 $c,d$ 问有多少 $a_i$ 可以满足上式。

分类讨论：

1. $d$ 这一位为 $0$，那么只能走 $c$ 这一位取反的值，这一位才能比 $d$ 小；
1. $d$ 这一位为 $1$，若这一位与 $c$ 相同得到 $0$，往这一路走所有的 $a$ 都满足条件，若不相同则得到 $1$，继续往下走。


那么单次插入复杂度 $O(24)$，单次查询复杂度 $O(24)$，总复杂度 $O(24n+24q)$。

$\rm 01Tire$ 的实现参见 `namespace T1`，差分的实现参见 `namespace solve2`

### $8\sim 11$ $\min\{d_i\}\geq \max\{b_i\}$
这个也挺容易构造的。。。

由于约束条件只有 $b_i$，考虑对 $a,b$ 构造出可行的 $c$，构造方法还是分类讨论：

1. $b$ 这一位是 $0$，则 $c$ 这一位只能和 $a$ 相反不然不可能小于等于 $b$；
1. $b$ 这一位是 $1$，则 $c$ 这一位于 $a$ 相等则必小于，或者不相等就处理下一位。


$\rm 01Tire$ 的实现参见 `namespace T2`，差分的实现参见 `namespace solve3`

### $12\sim13$ $l_i=1,r_i=n$
这个在考场上也写出来了。在这样的情况下，每个 $(a_i,b_i)$ 无序，因此对 $b_i$ 排序完全没有影响。那么把询问 $c,d$ 看做是两部分：$b\le d$ 的和 $b>d$ 的。把 $d$ 排序，用 `T1` 的方法处理 $b\le d$。反过来用 `T2` 处理 $b>d$。具体实现可以参考 `namespace solve4`

复杂度 $O(n\log n+24q)$

### $14\sim20$
没有任何限制，可以强行改到 $12\sim13$。

对序列分块,那么整块就是 $12\sim13$ 的情况，零散块直接暴力即可。为了速度循环展开了一下下。

时间复杂度 $O\left(q\log q+\dfrac nT(T\log T+24q)\right)$，应该是 $T=1800$ 左右速度过得去。

这份菜得离谱代码不开 $\rm O_2$ 也是稳过的。
## 代码
```cpp
#include<bits/stdc++.h>
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
const int N=1e5+10;
#define faster
namespace in{
    #ifdef faster
    char buf[1<<21],*p1=buf,*p2=buf;
    inline int getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
    #else
    inline int getc(){return getchar();}
    #endif
    template <typename T>inline void read(T& t){
        t=0;int f=0;char ch=getc();while (!isdigit(ch)){if(ch=='-')f = 1;ch=getc();}
        while(isdigit(ch)){t=t*10+ch-48;ch = getc();}if(f)t=-t;
    }
    template <typename T,typename... Args> inline void read(T& t, Args&... args){read(t);read(args...);}
}
namespace out{
    char buffer[1<<21];int p1=-1;const int p2 = (1<<21)-1;
    inline void flush(){fwrite(buffer,1,p1+1,stdout),p1=-1;}
    inline void putc(const char &x) {if(p1==p2)flush();buffer[++p1]=x;}
    template <typename T>void write(T x) {
        static char buf[15];static int len=-1;if(x>=0){do{buf[++len]=x%10+48,x/=10;}while (x);}else{putc('-');do {buf[++len]=-(x%10)+48,x/=10;}while(x);}
        while (len>=0)putc(buf[len]),--len;
    }
}
int n,q,a[N],b[N],l[N],r[N],c[N],d[N],ans[N];
namespace solve1{
	//暴力+循环展开
	void work(){
		for(int kk=1;kk<=q;kk++){
			register int ans1=0,ans2=0,ans3=0,ans4=0,ans5=0,ans6=0,ans7=0,ans8=0;
			register int i=l[kk],R=r[kk],C=c[kk],D=d[kk];
			for(;i+7<=R;i+=8)
				ans1+=((a[i  ]^C)<=min(b[i  ],D)),
				ans2+=((a[i+1]^C)<=min(b[i+1],D)),
				ans3+=((a[i+2]^C)<=min(b[i+2],D)),
				ans4+=((a[i+3]^C)<=min(b[i+3],D)),
				ans5+=((a[i+4]^C)<=min(b[i+4],D)),
				ans6+=((a[i+5]^C)<=min(b[i+5],D)),
				ans7+=((a[i+6]^C)<=min(b[i+6],D)),
				ans8+=((a[i+7]^C)<=min(b[i+7],D));
			for(;i<=R;i++)
				ans1+=((a[i]^C)<=min(b[i],D));  
			ans[kk]=ans1+ans2+ans3+ans4+ans5+ans6+ans7+ans8;
		}
	}
}

const int L=24;
void pre(int x,int *tmp){int now=L-1;while(now>=0)tmp[now]=x&1,x>>=1,now--;}
namespace T1{
	int ch[N*24][2],sz[N*24];int tot=0;
	int newnode(){++tot;ch[tot][0]=ch[tot][1]=0;sz[tot]=0;return tot;}
	void insert(int*tmp){
		int now=0;
		for(int i=0;i<L;i++){
			if(ch[now][tmp[i]]==0)ch[now][tmp[i]]=newnode();
			now=ch[now][tmp[i]];sz[now]++;
		}
	}
	int qry(int*C,int*D){
		//求有多少 a^C<=D
		int now=0;int ans=0;
		for(int i=0;i<L;i++){
			if(C[i]==0&&D[i]==0){
				if(!ch[now][0])return ans;
				now=ch[now][0];
			}
			if(C[i]==1&&D[i]==0){
				if(!ch[now][1])return ans;
				now=ch[now][1];
			}
			if(C[i]==0&&D[i]==1){
				ans+=sz[ch[now][0]];
				if(!ch[now][1])return ans;
				now=ch[now][1];
			}
			if(C[i]==1&&D[i]==1){
				ans+=sz[ch[now][1]];
				if(!ch[now][0])return ans;
				now=ch[now][0];
			}
		} 
		ans+=sz[now];
		return ans;
	}
	void clear(){tot=0;ch[0][0]=ch[0][1]=sz[0]=0;}
}
namespace T2{
	int ch[N*24][2],sz[N*24];int tot=0;
	int newnode(){++tot;ch[tot][0]=ch[tot][1]=0;sz[tot]=0;return tot;}
	void insert(int*A,int*B){
		//构造出一棵C要满足的条件的树 
		int now=0;
		for(int i=0;i<L;i++){
			if(A[i]==0&&B[i]==0){
				//此时 C[i] 只能为 0
				if(!ch[now][0])ch[now][0]=newnode();
				now=ch[now][0];
			} 
			if(A[i]==1&&B[i]==0){
				//此时 C[i] 只能为 1
				if(!ch[now][1])ch[now][1]=newnode();
				now=ch[now][1]; 
			}
			if(A[i]==0&&B[i]==1){
				if(!ch[now][0])ch[now][0]=newnode();
				sz[ch[now][0]]++;
				if(!ch[now][1])ch[now][1]=newnode();
				now=ch[now][1];
			}
			if(A[i]==1&&B[i]==1){
				if(!ch[now][1])ch[now][1]=newnode();
				sz[ch[now][1]]++;
				if(!ch[now][0])ch[now][0]=newnode();
				now=ch[now][0];
			}
		}
		sz[now]++;
	}
	int qry(int*C){
		int now=0,ans=0;
		for(int i=0;i<L;i++){
			if(!ch[now][C[i]])return ans;
			now=ch[now][C[i]];ans+=sz[now];
		}return ans;
	}
	void clear(){tot=0;ch[0][0]=ch[0][1]=sz[0]=0;}
}
namespace solve2{
	//max d<=min b 的情况，限制的因素是d 
	//首先差分，然后建01-tire
	struct node{int c,d,op,id;node(int _,int __,int ___,int ____):c(_),d(__),op(___),id(____){}};
	std::vector<node>Q[N];
	void work(){
		for(int i=1;i<=q;i++)
			Q[l[i]-1].push_back(node(c[i],d[i],-1,i)),
			Q[r[i]].push_back(node(c[i],d[i],1,i));
		for(int i=1;i<=n;i++){
			static int tmp[L],C[L],D[L];
			pre(a[i],tmp);T1::insert(tmp);
			for(int j=0;j<Q[i].size();j++){
				pre(Q[i][j].c,C);
				pre(Q[i][j].d,D);
				ans[Q[i][j].id]+=Q[i][j].op*T1::qry(C,D);
			}
		}
	}
}
namespace solve3{
	//min d>=max b 的情况，限制的因素是b 
	//首先差分，然后建01-tire
	struct node{int c,op,id;node(int _,int __,int ___):c(_),op(__),id(___){}};
	std::vector<node>Q[N];
	void work(){
		for(int i=1;i<=q;i++)
			Q[l[i]-1].push_back(node(c[i],-1,i)),
			Q[r[i]].push_back(node(c[i],1,i));
		for(int i=1;i<=n;i++){
			static int A[L],B[L],C[L];
			pre(a[i],A);pre(b[i],B);T2::insert(A,B);
			for(int j=0;j<Q[i].size();j++){
				pre(Q[i][j].c,C);
				ans[Q[i][j].id]+=Q[i][j].op*T2::qry(C);
			}
		}
	}
}
namespace solve4{
	struct node{
		int id,c,d;
		bool operator<(const node b)const{return d<b.d;}
	}Q[N];
	std::pair<int,int>kk[N];
	void work(){
		for(int i=1;i<=q;i++)
			Q[i].id=i,Q[i].c=c[i],Q[i].d=d[i];
		for(int i=1;i<=n;i++)kk[i].first=b[i],kk[i].second=a[i];
		std::sort(Q+1,Q+1+q);std::sort(kk+1,kk+1+n);
		int now=0;
		static int A[L],B[L],C[L],D[L];
		for(int i=1;i<=q;i++){
			while(now+1<=n&&kk[now+1].first<=Q[i].d){
				now++;
				pre(kk[now].first,B);
				pre(kk[now].second,A);
				T2::insert(A,B);
			}
			pre(Q[i].c,C);
			ans[Q[i].id]+=T2::qry(C);
		}
		now=n+1;
		for(int i=q;i>=1;i--){
			while(now>1&&kk[now-1].first>Q[i].d){
				now--;
				pre(kk[now].second,A);
				T1::insert(A);
			}
			pre(Q[i].c,C);
			pre(Q[i].d,D);
			ans[Q[i].id]+=T1::qry(C,D);
		}
	}
}
namespace solve5{
	struct node{
		int id,l,r,c,d;
		bool operator<(const node b)const{return d<b.d;}
	}Q[N];
	std::pair<int,int>kk[N];
	void work(){
		for(int i=1;i<=q;i++)
			Q[i].id=i,Q[i].c=c[i],Q[i].d=d[i],Q[i].l=l[i],Q[i].r=r[i];
		std::sort(Q+1,Q+1+q);
		int sz=1800;
		static int A[L],B[L],C[L],D[L];
		for(int l=1,r;l<=n;l=r+1){
			r=min(l+sz,n);int len=r-l+1;
			for(int i=l;i<=r;i++)kk[i-l+1].first=b[i],kk[i-l+1].second=a[i];
			sort(kk+1,kk+1+len);
			int now=0;
			for(int i=1;i<=q;i++){
				int ll=Q[i].l,rr=Q[i].r;
				if(ll>l||r>rr)continue;
				while(now+1<=len&&kk[now+1].first<=Q[i].d){
					now++;
					pre(kk[now].first,B);
					pre(kk[now].second,A);
					T2::insert(A,B);
				}
				pre(Q[i].c,C);
				ans[Q[i].id]+=T2::qry(C);
			}
			now=len+1;
			for(int i=q;i>=1;i--){
				int ll=Q[i].l,rr=Q[i].r;
				if(ll>l||r>rr)continue;
				while(now>1&&kk[now-1].first>Q[i].d){
					now--;
					pre(kk[now].second,A);
					T1::insert(A);
				}
				pre(Q[i].c,C);
				pre(Q[i].d,D);
				ans[Q[i].id]+=T1::qry(C,D);
			}
			for(int i=1;i<=q;i++){
				int ll=Q[i].l,rr=Q[i].r;
				if(ll<=l&&r<=rr)continue;
				ll=max(ll,l);rr=min(rr,r);
				unsigned short sum1=0,sum2=0,sum3=0,sum4=0,sum5=0,sum6=0;
				int j=ll;
				for(;j+5<=rr;j+=6)
					sum1+=(a[j  ]^Q[i].c)<=min(b[j  ],Q[i].d),
					sum2+=(a[j+1]^Q[i].c)<=min(b[j+1],Q[i].d),
					sum3+=(a[j+2]^Q[i].c)<=min(b[j+2],Q[i].d),
					sum4+=(a[j+3]^Q[i].c)<=min(b[j+3],Q[i].d),
					sum5+=(a[j+4]^Q[i].c)<=min(b[j+4],Q[i].d),
					sum6+=(a[j+5]^Q[i].c)<=min(b[j+5],Q[i].d);
				for(;j<=rr;j++)
					sum1+=(a[j  ]^Q[i].c)<=min(b[j  ],Q[i].d);
				ans[Q[i].id]+=sum1+sum2+sum3+sum4+sum5+sum6;
			}
			T1::clear();
			T2::clear();
		}
	}
}
signed main(){
	//freopen("island.in","r",stdin);
	//freopen("island.out","w",stdout);
	in::read(n,q);
	int mnb=0x3f3f3f3f,mxb=-0x3f3f3f3f;
	int mnd=0x3f3f3f3f,mxd=-0x3f3f3f3f;
	bool flag=true;
	for(int i=1;i<=n;i++)in::read(a[i],b[i]),mnb=min(mnb,b[i]),mxb=max(mxb,b[i]);
	for(int i=1;i<=q;i++)in::read(l[i],r[i],c[i],d[i]),mnd=min(mnd,d[i]),mxd=max(mxd,d[i]),flag&=(l[i]==1&&r[i]==n);
	if(n<=5000)solve1::work();
	else if(mxd<=mnb)solve2::work();
	else if(mnd>=mxb)solve3::work();
	else if(flag)solve4::work();
	else solve5::work();
	for(int i=1;i<=q;i++)out::write(ans[i]),out::putc('\n');
	out::flush();
	return 0;
}
```


---

## 作者：Diaоsi (赞：9)

[[NOI Online 2021 提高组] 岛屿探险](https://www.luogu.com.cn/problem/P7470)

线段树分治 + $\mathtt{01\ Trie}$ 

不难发现一个询问可以分多段分别计算然后累加合并，所以可以线段树分治。

开始时将每个询问挂在 $l \sim r$ 在线段树上对应的 $\mathcal{\log n}$ 个节点上，最后扫描整棵线段树统一处理，这样区间这一维的限制就被解除了，故以下的讨论均限制在某个线段树节点上。

对于一个询问，询问中的 $d_j$ 将岛屿划分为两个集合，分别是 $b_i \leq d_j$ 和 $b_i>d_j$ ，进行分类讨论。


------------


#### 第一种情况：$b_i>d_j$ 

这一部分相当于查询满足 $a_i \oplus c_j \leq d_j$ 的岛屿数，这是 $\mathtt{01\ Trie}$ 的经典应用，故在此不详细展开，不会的可以左转 [CF817E Choosing The Commander](https://www.luogu.com.cn/problem/CF817E) 。

大致做法是在 $\mathtt{01\ Trie}$ 上记录一个标记，表示当前有多少个数共用根到这个节点对应的二进制前缀，查询时对 $(c_j,d_j)$ 从二进制高位到低位进行匹配，讨论严格小于和小于等于两种情况。

设当前到二进制的第 $p$ 位，若 $a_i$ 满足 $a_i \oplus c_j < d_j$ 且 $a_i \oplus c_j$ 与 $d_j$ 的前 $p-1$ 位二进制都相等，则当 $d_j$ 的第 $p$ 位为 $1$ 时 $(a_i \oplus c_j)_p=0 $ 有贡献， $(a_i \oplus c_j)_p=1 $ 可能有贡献。

于是当 $d_j$ 的第 $p$ 位为 $1$ 时累加 $\mathtt{01\ Trie}$ 当前位上 $(a_i \oplus c_j)_p=0 $ 的节点上的标记，然后走向 $(a_i \oplus c_j)_p=1 $ 的节点继续讨论。

不难发现走到叶子节点时该节点上的标记就是 $a_i \oplus c_j = d_j$ 的个数。


------------


#### 第二种情况：$b_i \leq d_j$ 

这一部分比较麻烦，相当于查询 $a_i \oplus c_j \leq b_i$ 的岛屿数，但我们发现这个结构与 $a_i \oplus c_j \leq d_j$ 是非常相似的。

$a_i \oplus c_j \leq d_j$ 是对 $a_i$ 建 $\mathtt{01\ Trie}$ 后对 $(c_j,d_j)$ 查询，那我们可以参考这个做法，对 $c_j$ 建 $\mathtt{01\ Trie}$ ，把 $(a_i,b_i)$ 当作询问进行查询，在 $\mathtt{01\ Trie}$ 上查询时记录 $(a_i,b_i)$ 对每个 $c_j$ 的贡献。

更具体地，仿照第一种情况对 $(a_i,b_i)$ 进行逐位匹配和分类讨论，在需要累加标记的地方对另一个标记（初始为空，后文称为“贡献标记”）加一，表示 $(a_i,b_i)$ 对经过此节点的 $c_j$ 产生了一的贡献，或者说经过此节点的 $c_j$ 满足 $a_i \oplus c_j < b_i$ ，同理在匹配到叶子节点时在叶子节点加一，表示
经过此节点的 $c_j$ 满足 $a_i \oplus c_j = b_i$ 

最后将每个 $c_j$ 在 $\mathtt{01\ Trie}$ 上进行匹配，累加上沿途的贡献标记就可以计算出 $a_i \oplus c_j \leq b_i$ 的岛屿数。


------------


接下来该解决的是，如何优雅地处理每个询问。

将 $(a_i,b_i)$ 与 $(c_j,d_j)$ 分别按照 $b_i$ 和 $d_j$ 升序排序，用双指针扫描，开两个 $\mathtt{01\ Trie}$ 分别维护第一种情况和第二种情况，扫描到第 $j$ 个询问时将不满足 $b_i>d_j$ 的 $a_i$ 从维护第一种情况的 $\mathtt{01\ Trie}$ 上删除，然后查询 $(c_j,d_j)$ 累加贡献。同时将满足 $b_i \leq d_j$ 的 $(a_i,b_i)$ 在维护第二种情况的 $\mathtt{01\ Trie}$ 上计算贡献，然后对 $c_j$ 进行匹配累加贡献。

由于 $b_i$ 和 $d_j$ 按照升序排序，所以两个指针单调向右移。

#### 一些精细实现：

在线段树分治时，要先计算低层的答案再计算高层的答案，否则在对岛屿排序时会造成一些顺序混乱。

在每次计算之后清空 $\mathtt{01\ Trie}$ ，而不是在每个节点都开一个 $\mathtt{01\ Trie}$ ，可以节省空间（在 ```256MB``` 的空间下是非常必要的）。

分治到 $l=r$ 时直接对当前节点的询问暴力统计答案，此时只有一个岛屿，可以省去将各种东西插入 $\mathtt{01\ Trie}$ 的时间复杂度。

由于分治的特殊性，对 $(a_i,b_i)$ 的排序可以使用归并排序而不是 ```std::sort``` 。

经过上述细节处理后本代码跑进了最优解第三名（6.08s）。

总的时间复杂度为 $\mathcal{O(n \log n \log a_i)}$ 。

既然你能找到这题，我相信你能瞬间做出来的。

```Code:```
```cpp
#include<bits/stdc++.h>
typedef long long LL;
typedef long double LD;
using namespace std;
const int N=100010,M=1000010,INF=0x3f3f3f3f;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int n,m,ans[N];
int cnt,tr[N<<5][2],tag[N<<5],rt[2];
struct rec{int x,y,id;}s[N],w[N];
vector<rec> q[N<<2];
bool cmp(rec a,rec b){return a.y<b.y;}
struct SegmentTree{
	int l,r;
	#define l(x) tree[x].l
	#define r(x) tree[x].r
}tree[N<<2];
void clr(){
	rt[0]=rt[1]=0;
	for(int i=1;i<=cnt;i++)
		tr[i][0]=tr[i][1]=tag[i]=0;
	cnt=0;
}
void ins(int p,int x,int t){
	for(int i=1<<23;i;i>>=1){
		bool ch=x&i;
		if(!tr[p][ch])tr[p][ch]=++cnt;
		p=tr[p][ch];tag[p]+=t;
	}
}
int ask(int p,int x,int y){//a ^ c <= d
	int res=0;
	for(int i=1<<23;i;i>>=1){
		if(!p)break;
		bool cc=x&i,dd=y&i;
		if(dd)res+=tag[tr[p][cc]];
		p=tr[p][cc^dd];
	}
	if(p)res+=tag[p];
	return res;
}
void upd(int p,int x,int y){//c ^ a <= b
	for(int i=1<<23;i;i>>=1){
		if(!p)break;
		bool aa=x&i,bb=y&i;
		if(bb&&tr[p][aa])tag[tr[p][aa]]++;
		p=tr[p][aa^bb];
	}
	if(p)tag[p]++;
}
int qry(int p,int x){
	int res=0;
	for(int i=1<<23;i;i>>=1){
		bool ch=x&i;
		res+=tag[tr[p][ch]];
		p=tr[p][ch];
	}
	return res;
}
void build(int x,int l,int r){
	l(x)=l,r(x)=r;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
void insert(int x,int L,int R,rec t){
	int l=l(x),r=r(x);
	if(L<=l&&r<=R){q[x].push_back(t);return;}
	int mid=(l+r)>>1;
	if(L<=mid)insert(x<<1,L,R,t);
	if(R>mid)insert(x<<1|1,L,R,t);
}
void query(int x,int l,int r){
	if(l==r){
		for(int i=0;i<(int)q[x].size();i++)
			ans[q[x][i].id]+=(s[l].x^q[x][i].x)<=min(s[l].y,q[x][i].y);
		return;
	}
	int mid=(l+r)>>1;
	query(x<<1,l,mid);
	query(x<<1|1,mid+1,r);

	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r)
		if(s[i].y<=s[j].y)w[k++]=s[i++];
		else w[k++]=s[j++];
	while(i<=mid)w[k++]=s[i++];
	while(j<=r)w[k++]=s[j++];
	for(int i=l;i<=r;i++)s[i]=w[i];

	sort(q[x].begin(),q[x].end(),cmp);
	rt[0]=++cnt;rt[1]=++cnt;

	for(int i=0;i<(int)q[x].size();i++)
		ins(rt[0],q[x][i].x,0);//c

	for(int i=l;i<=r;i++)
		ins(rt[1],s[i].x,1);//a

	for(int i=0,j=l;i<(int)q[x].size();i++){
		while(j<=r&&s[j].y<=q[x][i].y){
			ins(rt[1],s[j].x,-1);
			upd(rt[0],s[j].x,s[j].y);
			j++;
		}
		ans[q[x][i].id]+=qry(rt[0],q[x][i].x)+ask(rt[1],q[x][i].x,q[x][i].y);
	}
	clr();
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&s[i].x,&s[i].y);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int l,r,c,d;
		scanf("%d%d%d%d",&l,&r,&c,&d);
		insert(1,l,r,(rec){c,d,i});
	}
	query(1,1,n);
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```





---

## 作者：wishapig (赞：8)

这是一个苟过了空间的树套树。。。

考试的时候写了线段树套trie，但被卡了空间就非常恼火（那份代码是$65$分）

~~做法应该都清楚~~就是离线下来分别按$b_i$和$d_i$排序，然后就是一个分别支持动态加点的 $\max\{d_i\}\leq \min\{b_i\}$和$\min\{d_i\}\ge \max\{b_i\}$的部分，这可以用线段树套trie来做

好了这个东西的时空复杂度都是$O(n\log n\log a_i)$的（空间还因为要存trie的左右儿子和权值而有一个$3$的常数），空间是会达到$\rm 466MB$的（~~所以为什么不开$512$~~）

然后你就开始了第一次卡空间，你发现如果一个线段树上的节点再所有询问中都没有被经过，那就不需要再这个点上建trie树了，感性思考一波发现其实没有被经过的节点应该还挺多了，于是就卡到了$90$分

然后你就有点迷了，经过分析发现trie一次插入的$\log a_i$个节点是绝对省不下来的，于是就只能在线段树的树高上考虑，然后我就把线段树改成了五叉的。。。（~~什么你问为什么不是四叉，四叉就是卡不过啊~~）于是就以$\rm 245MB$的空间苟过了

实际上你发现左右儿子的大小是$10^7$左右的，权值是$10^5$左右的，它们的乘积是$10^{19}$能用一个long long存，所以其实认真卡的话还可以把三个int卡成一个long long，再节省三分之一的空间

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int Bits=23;
#define ls now<<1
#define rs now<<1|1
int ch[N*200][2],cnt[N*200],rt[N<<4],ans[N],vis[N<<4];
int n,q,treesize;
struct data{ int a,b,id; } a[N];
struct ques{ int l,r,c,d,id; } que[N];
bool operator < (const data& a, const data& b){ return a.b<b.b; }
bool operator < (const ques& a, const ques& b){ return a.d<b.d; }
namespace S1{
	inline void Add(int& pos){ cnt[(pos?pos:pos=++treesize)]++; }
	void Insert(int& now, int dep, int pos){
		if (!now) now=++treesize;
		if (dep==-1){ cnt[now]++; return; }
		if (a[pos].b&(1<<dep)) Add(ch[now][1-(((a[pos].a>>dep)&1)^((a[pos].b>>dep)&1))]);
		Insert(ch[now][((a[pos].a>>dep)&1)^((a[pos].b>>dep)&1)],dep-1,pos);
	}
	void update(int now, int l, int r, int x, int y){
		if (vis[now]) Insert(rt[now],Bits,y);
		if (l==r) return;
		int mid1=l+(r-l+1)/5-1;
		int mid3=(mid1+1+r)>>1,mid2=(mid1+1+mid3)>>1,mid4=(mid3+1+r)>>1,locx=0;
		int L[5]={l,mid1+1,mid2+1,mid3+1,mid4+1};
		int R[5]={mid1,mid2,mid3,mid4,r};
		for (int i=0; i<5; i++)
			if (L[i]<=x && x<=R[i]) locx=i;
		update(now*5+locx,L[locx],R[locx],x,y);
	}
	int Query(int now, int dep, int v){
		if (!now) return 0;
		if (dep==-1) return cnt[now];
		return Query(ch[now][(v>>dep)&1],dep-1,v)+cnt[now];
	}
	int query(int now, int l, int r, int x, int y, int z){
		if (l==x && r==y) return Query(rt[now],Bits,z);
		int mid1=l+(r-l+1)/5-1;
		int mid3=(mid1+1+r)>>1,mid2=(mid1+1+mid3)>>1,mid4=(mid3+1+r)>>1,locx=0,locy=0;
		int L[5]={l,mid1+1,mid2+1,mid3+1,mid4+1};
		int R[5]={mid1,mid2,mid3,mid4,r};
		for (int i=0; i<5; i++){
			if (L[i]<=x && x<=R[i]) locx=i;
			if (L[i]<=y && y<=R[i]) locy=i;
		}
		if (locx==locy) return query(now*5+locx,L[locx],R[locx],x,y,z);
		else {
			int res=0;
			for (int i=locx+1; i<locy; i++) res+=query(now*5+i,L[i],R[i],L[i],R[i],z);
			res+=query(now*5+locx,L[locx],R[locx],x,R[locx],z);
			res+=query(now*5+locy,L[locy],R[locy],L[locy],y,z);
			return res;
		}
	}
	void solve(){
		int now=1;
		for (int i=1; i<=q; i++){
			while (now<=n && a[now].b<=que[i].d) update(1,1,n,a[now].id,now),now++;
			ans[que[i].id]=query(1,1,n,que[i].l,que[i].r,que[i].c);
		}
	}
}
namespace S2{
	void Insert(int& now, int dep, int v){
		if (!now) now=++treesize;
		cnt[now]++;
		if (dep==-1) return;
		Insert(ch[now][(v>>dep)&1],dep-1,v);
	}
	void update(int now, int l, int r, int x, int y){
		if (vis[now]) Insert(rt[now],Bits,y);
		if (l==r) return;
		int mid1=l+(r-l+1)/5-1;
		int mid3=(mid1+1+r)>>1,mid2=(mid1+1+mid3)>>1,mid4=(mid3+1+r)>>1,locx=0;
		int L[5]={l,mid1+1,mid2+1,mid3+1,mid4+1};
		int R[5]={mid1,mid2,mid3,mid4,r};
		for (int i=0; i<5; i++)
			if (L[i]<=x && x<=R[i]) locx=i;
		update(now*5+locx,L[locx],R[locx],x,y);
	}
	int Query(int now, int dep, int c, int d){
		if (!now) return 0;
		if (dep==-1) return cnt[now];
		int res=Query(ch[now][((c>>dep)&1)^((d>>dep)&1)],dep-1,c,d);
		if ((d>>dep)&1) res+=cnt[ch[now][1-(((c>>dep)&1)^((d>>dep)&1))]];
		return res;
	}
	int query(int now, int l, int r, int x, int y, int C, int D){
		if (l==x && r==y) return Query(rt[now],Bits,C,D);
		int mid1=l+(r-l+1)/5-1;
		int mid3=(mid1+1+r)>>1,mid2=(mid1+1+mid3)>>1,mid4=(mid3+1+r)>>1,locx=0,locy=0;
		int L[5]={l,mid1+1,mid2+1,mid3+1,mid4+1};
		int R[5]={mid1,mid2,mid3,mid4,r};
		for (int i=0; i<5; i++){
			if (L[i]<=x && x<=R[i]) locx=i;
			if (L[i]<=y && y<=R[i]) locy=i;
		}
		if (locx==locy) return query(now*5+locx,L[locx],R[locx],x,y,C,D);
		else {
			int res=0;
			for (int i=locx+1; i<locy; i++) res+=query(now*5+i,L[i],R[i],L[i],R[i],C,D);
			res+=query(now*5+locx,L[locx],R[locx],x,R[locx],C,D);
			res+=query(now*5+locy,L[locy],R[locy],L[locy],y,C,D);
			return res;
		}
	}
	void solve(){
		memset(ch,0,sizeof(ch));
		memset(rt,0,sizeof(rt));
		memset(cnt,0,sizeof(cnt)); treesize=0;
		int now=n;
		for (int i=q; i>=1; i--){
			while (now>=1 && a[now].b>que[i].d) update(1,1,n,a[now].id,a[now].a),now--;
			ans[que[i].id]+=query(1,1,n,que[i].l,que[i].r,que[i].c,que[i].d);
		}
	}
}
void modify(int now, int l, int r, int x, int y){
	if (l==x && r==y){ vis[now]=1; return; }
	int mid1=l+(r-l+1)/5-1;
	int mid3=(mid1+1+r)>>1,mid2=(mid1+1+mid3)>>1,mid4=(mid3+1+r)>>1,locx=0,locy=0;
	int L[5]={l,mid1+1,mid2+1,mid3+1,mid4+1};
	int R[5]={mid1,mid2,mid3,mid4,r};
	for (int i=0; i<5; i++){
		if (L[i]<=x && x<=R[i]) locx=i;
		if (L[i]<=y && y<=R[i]) locy=i;
	}
	if (locx==locy) modify(now*5+locx,L[locx],R[locx],x,y);
	else {
		for (int i=locx+1; i<locy; i++) modify(now*5+i,L[i],R[i],L[i],R[i]);
		modify(now*5+locx,L[locx],R[locx],x,R[locx]);
		modify(now*5+locy,L[locy],R[locy],L[locy],y);
	}
}
int main(){
//	freopen("island.in","r",stdin);
//	freopen("island.out","w",stdout);
	scanf("%d%d",&n,&q);
	for (int i=1; i<=n; i++) scanf("%d%d",&a[i].a,&a[i].b),a[i].id=i;
	for (int i=1; i<=q; i++) scanf("%d%d%d%d",&que[i].l,&que[i].r,&que[i].c,&que[i].d),que[i].id=i,modify(1,1,n,que[i].l,que[i].r);
	sort(a+1,a+1+n); sort(que+1,que+1+q);
	S1::solve(); S2::solve();
	for (int i=1; i<=q; i++) printf("%d\n",ans[i]);
	return 0;
}
/*
4 2
1 1
4 2
5 1
2 7
1 4 6 5
2 4 3 3

20 10
215 144
2 110
174 132
214 142
116 108
155 192
236 208
216 214
99 220
236 118
190 81
230 131
10 238
189 198
183 13
45 193
14 234
208 192
126 19
49 38
7 14 251 184
2 18 89 76
11 15 49 196
8 11 83 139
10 15 119 239
9 16 148 120
11 17 225 34
15 16 3 46
14 15 86 227
7 18 252 103
*/
```

---

## 作者：Aly_ (赞：7)

​	**本篇题解的不同之处在于其对 $b_i<d_j$ 部分的处理上。**

#### 题意简述

- 一行 $n$ 对数，第 $i$ 对数为权值对 $<a_i,b_i>$。
- 回答 $q$ 个询问 $<l_j,r_j,c_j,d_j>$，询问的是在 $l_j$ 到 $r_j$ 内所有数对中满足 $a_i\operatorname{xor} c_j\leq\min(b_i,d_j)$ 的数对个数。
- $1\leq n,q\leq 10^5$，$1\leq l_j\leq r_j\leq n$，$0\leq a_i, b_i, c_j$, $d_j\leq 2^{24} - 1$。

#### 解法

​	先考虑一个询问怎么求。

​	看到异或就知道大概是要建 0-1 trie 的。对于一个询问，分 $b_i\geq d_j$ 和 $b_i<d_j$ 两种情况考虑。

​	对于 $b_i\geq d_j$ 的情况，要求即为 $a_i\operatorname{xor} c_j\leq d_j$ ，以 $a_i$ 为权值建出序列的 0-1 trie。

​	令 $c_j$ 从高位往低位走，对于一个节点（假设 $c_j$ 当前位为 $0$）有 $0$ 和 $1$ 两个儿子：若 $d_j$ 当前位为 $1$，则 $0$ 儿子及其子树一定可行，$1$ 儿子可能可行，向 $1$ 递归；反之 $1$ 儿子一定不可行，向 $0$ 递归。这一部分是 0-1 trie 经典问题，不再赘述。

​	对于 $b_i< d_j$ 的情况，要求即为 $a_i\operatorname{xor} c_j\leq b_i$ 。

​	分析一下各种情况，这里还是假设 $c_j$ 当前位为 $0$：

- $a_i$ 当前位为 $0$，$b_i$ 当前位为 $0$：可能可行，需向下递归。
- $a_i$ 当前位为 $0$，$b_i$ 当前位为 $1$：**一定可行**，子树全部可行。
- $a_i$ 当前位为 $1$，$b_i$ 当前位为 $0$：**一定不可行**，子树全部不可行。
- $a_i$ 当前位为 $1$，$b_i$ 当前位为 $1$：可能可行，需向下递归。

​	观察发现：**当 $a_i\operatorname{xor}b_i=0$ 时需要向下递归，否则要么全可行，要么全不可行。**

​	对 $c_j$ 当前位为 $1$ 的情况分析类似。

​	**以 $a_i\operatorname{xor}b_i$ 为权值建出序列的 0-1 trie**，再在每个节点记录其子树内 $a_i=0$ 和 $1$ 的数的个数。查询时令 $c_j$ 从高位往低位走，按上面的讨论做即可。

​	再考虑原问题。按 $b_i,d_j$ 排序，顺着扫一遍，分块维护两组 trie 树：一组是关于 $b_i\geq d_j$ 的，另一组是关于 $b_i< d_j$ 的，扫的时候在 trie 上动态加点删点即可。

​	设块长为 $B$，值域为 $A$，时间复杂度 $O(n\log A+Q(\frac{n}{B}\log A+B))$。$n,Q$ 同级，理论取 $B=\sqrt{n\log n}$，实践中设 $B=2000\sim 3000$ 时最优。空间 $O(n\log A)$。

​	**较小的常数使得分块做法的通过成为可能。**

​	**CDQ 分治之类的做法（似乎）也可以类似地套用**。按 $b_i,d_j$ 排序，分治时左区间对右区间的贡献即所有 $b_i$ 的插入（$b_i< d_j$ 部分的 trie 树上）和删除（ $b_i\geq d_j$ 的 trie 树上）。其它题解里有这方面的详细讲解。

​	不济的话把分块（时间被卡）和树套树（空间被卡）结合一下把块长调大一点也能过。

​	放一下关键位置的源代码（$b_i< d_j$ 部分的 trie 树建立与查询）：

```
void trieadd1(int u,int aa,int bb,int np){
	if(!np)return;
	int ng=(((aa^bb)&(1<<(np-1)))>>(np-1));
	if(!son[u][ng])son[u][ng]=++pb;
	dq[son[u][ng]][(aa&(1<<np-1))>>(np-1)]++;
	trieadd1(son[u][ng],aa,bb,np-1);
}
int triereq1(int u,int x,int np){
	if(!u)return 0;
	if(!np)return dq[u][0]+dq[u][1];
	int ng=((x&(1<<(np-1)))>>(np-1));
	return triereq1(son[u][ng],x,np-1)+dq[son[u][ng^1]][ng];
}
```



---

## 作者：ZigZagKmp (赞：6)

本文同步于我的 [cnblog](https://www.cnblogs.com/ZigZagKmp/p/14587026.html)。

## 题意简述
一个长度为 $n$ 的序列，每一个位置 $i$ 有两个属性值 $a_i,b_i$ 。

有 $q$ 次询问，形如 $l,r,c,d$ ，查询有多少个 $i$ 满足 $i\in [l,r],(a_i\oplus c)\le \min\{b_i,d\}$ ，其中 $\oplus$ 为按位异或运算。

$1\le n,q\le 10^5\ ,\ 1\le l\le r\le n\ ,\ 0\le a_i,b_i,c,d<2^{24}$。

## 算法分析
首先暴力特别好写，复杂度 $\mathcal O(nq)$ ~~（然后就可以用指令集优化了，暴力碾标算）~~。

先考虑一个部分分，$\max\{d\}\le \min\{b_i\}$，即我们只需要考虑 $d$ 的限制。[这是一道原题](https://codeforces.com/problemset/problem/817/E)。

限制是异或，因此考虑按位分析。我们从高位到低位遍历，考虑第 $p$ 位，分两种情况：
1. $d_p=0$ ，此时如果在考虑的范围内 $(a_i\oplus c)_p=1$，则一定不合法，即必须满足 $(a_i\oplus c)_p=0$ 但仍然不确定，因此需继续遍历低位；
2. $d_p=1$ ，此时如果在考虑的范围内 $(a_i\oplus c)_p=0$，则一定合法，无需继续遍历，否则不确定，需继续遍历低位。

这种限制条件很容易用 `0-1 trie` 表示出，即：

![图片.png](https://i.loli.net/2021/03/27/lcr3vEAOBFfy8Wj.png)

把 $a_i$ 插入 trie 即可，为了处理 $i\in [l,r]$ 的限制，要使用可持久化 `trie` ，时空复杂度均为 $\mathcal O(n\log n)$ 。

再考虑第二个部分分，$\max\{b_i\}\le \min\{d\}$，即我们只需要考虑 $b_i$ 的限制。此时插入的有两个限制，询问只有一个限制，因此考虑反过来计算贡献，如下分析：

继续从高位到低位遍历，考虑第 $p$ 位，分两种情况：
1. $b_p=0$ ，此时如果在考虑的范围内询问的 $c$ 会使得 $(a_i\oplus c)_p=1$ 成立，则一定不合法，即必须满足 $(a_i\oplus c)_p=0$ ，这个元素才有可能给询问 $c$ 一个贡献，但仍然不确定，因此需继续遍历低位；
2. $b_p=1$ ，此时如果在考虑的范围内询问的 $c$ 会使得 $(a_i\oplus c)_p=0$，则一定合法，一定有贡献，无需继续遍历，否则不确定是否产生贡献，需继续遍历低位。

这种限制条件是类似的，也可以用 `0-1 trie` 表示出，即：

![图片.png](https://i.loli.net/2021/03/27/DN46JbWir5lc73z.png)

其中黄色节点表示此处有贡献，最后询问的时候把经过的所有点的贡献相加即为答案。

同样使用可持久化 `trie` 维护下标偏序关系，时空复杂度均为 $\mathcal O(n\log n)$ 。

两者结合，我们很难同时考虑两个限制。不妨找到一个分界，前面的所有元素满足 $b_i<d$ ，后面的所有元素满足 $b_i>d$ 。我们按照 $b,d$ 升序排序后 two pointers 扫一遍即可求解。

但是由于排序的存在，我们无法继续沿用可持久化 `trie` 的方法处理下标偏序关系。由于信息可加**可减**，因此有如下两种解决方案：
1. 树状数组套 `trie` ，时空复杂度均为 $\mathcal O(n\log^2 n)$，空间卡不过去。
2. `cdq分治`套 `trie`，时间复杂度 $\mathcal O(n\log^2 n)$ ，空间复杂度  $\mathcal O(n\log n)$，可以卡过去。

树状数组套 `trie` 直接维护 $n$ 棵 `trie`，外层树状数组维护其维护区间的所有元素的 `trie` 的根，修改直接暴力插入即可，比较直观，也比较无脑。

`cdq分治` 套 `trie`，在外层把下标限制拆开，按照下标排序，内层再按照 $b_i/d$ 排序，左边修改对右边询问产生贡献，实现起来有一些细节。

## 代码实现
树状数组套 `trie`，（luogu民间数据只有20分，沦为暴力……）
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define maxm 20000005
#define inf 0x3f3f3f3f
#define LL long long
#define ull unsigned long long
#define ldb long double
#define mod 1000000007
#define eps 1e-9
#define local
void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int n,m;
struct node{
	int id,a,b;
	bool operator <(node y)const{
		return b<y.b;
	}
};
struct Quer{
	int id,l,r,c,d;
	bool operator <(Quer y)const{
		return d<y.d;
	}
};
node ai[maxn];
Quer qi[maxn];
int ans[maxn];

namespace Sub1{//d<b  chk d
	int ch[maxm][2],siz[maxm],T[maxn],tot;
	void upd(int rt,int x,int v){//情况1的插入
		int p=rt,dir;
		for(int i=23;~i;--i){
			dir=((x>>i)&1);
			if(!ch[p][dir])ch[p][dir]=++tot;
			p=ch[p][dir];
			siz[p]+=v;//记录个数
		}
	}
	int query(int rt,int c,int d){//情况1的查询
		++d;//这里要+1，因为我们上面的分析过程没有计算本身，这样写能减少边界细节
		int ret=0,p=rt,dc,dd;
		for(int i=23;~i;--i){
			dc=((c>>i)&1);dd=((d>>i)&1);
			if(dd){
				ret+=siz[ch[p][dc]];//累加确定的个数
				p=ch[p][dc^1];
			}
			else p=ch[p][dc];
			if(!p)break;
		}
		return ret;
	}
	void add(int x,int a,int v){//树套树修改
		for(;x<=n;x+=(x&(-x))){
			upd(T[x],a,v);
		}
	}
	int ask(int x,int c,int d){//树套树查询
		int ret=0;
		for(;x;x-=(x&(-x)))ret+=query(T[x],c,d);
		return ret;
	}
	void prep(){
		for(int i=1;i<=n;++i)T[i]=++tot;
		for(int i=1;i<=n;++i)add(ai[i].id,ai[i].a,1);
	}
}

namespace Sub2{// d>b chk b
	int ch[maxm][2],siz[maxm],T[maxn],tot;
	void upd(int rt,int a,int b,int v){//情况2的插入
		++b;//这个细节与上面的同理
		int p=rt,da,db;
		for(int i=23;~i;--i){
			da=((a>>i)&1);db=((b>>i)&1);
			if(db){
				if(!ch[p][da])ch[p][da]=++tot;
				if(!ch[p][da^1])ch[p][da^1]=++tot;
				siz[ch[p][da]]+=v;//记录贡献
				p=ch[p][da^1];
			}
			else{
				if(!ch[p][da])ch[p][da]=++tot;
				p=ch[p][da];
			}
		}
	}
	int query(int rt,int c){//情况2的查询
		int p=rt,ret=0,dir;
		for(int i=23;~i;--i){
			dir=((c>>i)&1);
			if(!ch[p][dir])break;
			p=ch[p][dir];ret+=siz[p];//累加贡献
		}
		return ret;
	}
	void add(int x,int a,int b,int v){
		for(;x<=n;x+=(x&(-x))){
			upd(T[x],a,b,v);
		}
	}
	int ask(int x,int c){
		int ret=0;
		for(;x;x-=(x&(-x)))ret+=query(T[x],c);
		return ret;
	}
	void prep(){
		for(int i=1;i<=n;++i)T[i]=++tot;
	}
}
//其实两个情况的代码十分类似，第一个的插入与第二个的询问几乎一样，第一个的询问与第二个的插入几乎一样，
signed main(){
	#ifndef local
		file("island");
	#endif
	read(n);read(m);
	for(int i=1;i<=n;++i){
		read(ai[i].a);read(ai[i].b);ai[i].id=i;
	}
	for(int i=1;i<=m;++i){
		read(qi[i].l);read(qi[i].r);read(qi[i].c);read(qi[i].d);qi[i].id=i;
	}
	sort(ai+1,ai+n+1);
	sort(qi+1,qi+m+1);
	
	Sub1::prep();
	Sub2::prep();
	for(int i=1,j=1;i<=m;++i){
		while(j<=n&&ai[j].b<qi[i].d){//two pointers扫描
			Sub1::add(ai[j].id,ai[j].a,-1);
			Sub2::add(ai[j].id,ai[j].a,ai[j].b,1);
			++j;
		}
		int t1=Sub1::ask(qi[i].r,qi[i].c,qi[i].d);
		int t2=Sub1::ask(qi[i].l-1,qi[i].c,qi[i].d);
		int t3=Sub2::ask(qi[i].r,qi[i].c);
		int t4=Sub2::ask(qi[i].l-1,qi[i].c);
		ans[qi[i].id]=(t1-t2)+(t3-t4);//代价相减，统计总和
	}
	for(int i=1;i<=m;++i)printf("%d\n",ans[i]);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```
`cdq分治` 套 `trie`（luogu民间数据能 AC）
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define maxm 10000005
#define inf 0x3f3f3f3f
#define LL long long
#define ull unsigned long long
#define ldb long double
#define mod 1000000007
#define eps 1e-9
#define local
void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int n,m,nm;

struct Oper{
	int id,ps,typ,a,b,c,d;//为了能够cdq，这里做了比较大的改版
	bool operator <(Oper y)const{
		if(ps==y.ps){
			if(!typ||!y.typ)return !typ;
			else return typ<y.typ;
		}
		else return ps<y.ps;
	}
};
bool cmp1(Oper x,Oper y){
	return x.b<y.b;
}
Oper ai[maxn];

int ans[maxn];

namespace Sub1{//d<b  chk d
	int ch[maxm][2],siz[maxm],RT,tot;
	void upd(int x,int v){
		int p=RT,dir;
		for(int i=23;~i;--i){
			dir=((x>>i)&1);
			if(!ch[p][dir])ch[p][dir]=++tot;
			p=ch[p][dir];
			siz[p]+=v;
		}
	}
	int query(int c,int d){
		++d;
		int ret=0,p=RT,dc,dd;
		for(int i=23;~i;--i){
			dc=((c>>i)&1);dd=((d>>i)&1);
			if(dd){
				ret+=siz[ch[p][dc]];
				p=ch[p][dc^1];
			}
			else p=ch[p][dc];
			if(!p)break;
		}
		return ret;
	}
	void prep(){RT=tot=1;}
}

namespace Sub2{// d>b chk b
	int ch[maxm][2],siz[maxm],RT,tot;
	void upd(int a,int b,int v){
		++b;
		int p=RT,da,db;
		for(int i=23;~i;--i){
			da=((a>>i)&1);db=((b>>i)&1);
			if(db){
				if(!ch[p][da])ch[p][da]=++tot;
				if(!ch[p][da^1])ch[p][da^1]=++tot;
				siz[ch[p][da]]+=v;
				p=ch[p][da^1];
			}
			else{
				if(!ch[p][da])ch[p][da]=++tot;
				p=ch[p][da];
			}
		}
	}
	int query(int c){
		int p=RT,ret=0,dir;
		for(int i=23;~i;--i){
			dir=((c>>i)&1);
			if(!ch[p][dir])break;
			p=ch[p][dir];ret+=siz[p];
		}
		return ret;
	}
	void prep(){RT=tot=1;}
}
//两个情况与树套树做法几乎一模一样，唯一的不同是只有一棵树，没有外层的树状数组结构
void cdq(int l,int r){
	if(l==r)return;
	int mid=((l+r)>>1);
	cdq(l,mid);cdq(mid+1,r);
	sort(ai+l,ai+mid+1,cmp1);sort(ai+mid+1,ai+r+1,cmp1);//这里可以写归并优化常数
	for(int i=l;i<=mid;++i){
		if(!ai[i].typ){
			Sub1::upd(ai[i].a,1);
		}
	}
	int j=l;
	for(int i=mid+1;i<=r;++i){
		while(j<=mid&&ai[j].b<ai[i].d){//同样 two pointers计算贡献
			if(!ai[j].typ){
				Sub1::upd(ai[j].a,-1);
				Sub2::upd(ai[j].a,ai[j].b,1);
			}
			++j;
		}
		if(ai[i].typ){
			int t1=Sub1::query(ai[i].c,ai[i].d);
			int t2=Sub2::query(ai[i].c);
			ans[ai[i].id]+=ai[i].typ*(t1+t2);//因为询问的[l,r]拆解，这里要乘上系数
		}
	}
	for(int i=l;i<j;++i){//记得 全 部 清 空
		if(!ai[i].typ){
			Sub2::upd(ai[i].c,ai[i].d,-1);
		}
	}
	for(int i=j;i<=mid;++i){
		if(!ai[i].typ){
			Sub1::upd(ai[i].a,-1);
		}
	}
}

signed main(){
	#ifndef local
		file("island");
	#endif
	read(n);read(m);
	for(int i=1,a,b;i<=n;++i){
		read(a);read(b);
		ai[++nm]=(Oper){i,i,0,a,b,a,b};
	}
	for(int i=1,l,r,c,d;i<=m;++i){
		read(l);read(r);read(c);read(d);
		ai[++nm]=(Oper){i,r,1,c,d,c,d};
		ai[++nm]=(Oper){i,l-1,-1,c,d,c,d};
	}
	sort(ai+1,ai+nm+1);
	Sub1::prep();Sub2::prep();
	cdq(1,nm);
	for(int i=1;i<=m;++i)printf("%d\n",ans[i]);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}

```

---

## 作者：loveJY (赞：4)

~~没有人在树上猫一猫吗~~

## Part 0
$\max~d\leq \min~b$

即对于所有的询问,我们都满足d取到这两者中的最小值

可以发现我们需要满足的条件就是

$a\oplus c<d$

其中c,d对于一次询问来说都是已知的,那么我们不难想到用一个方法快速维护a

和异或有关,同时又是比较大小,可以考虑01trie

我们还是从高到底的考虑每一位,先插入区间中每一个a,考虑c对于01trie的影响就相当于**对于c为1的为i,交换所有第i-1层的节点左右儿子**,这个不难在trie递归过程中简单处理

再考虑$<d$的条件,所有$a\oplus c<d$的信息一定满足前k位$a\oplus c$和d相同,而在第k+1位$a\oplus c$为0而d的该位为1

这也就告诉我们可以在01trie上沿着d的二进制位走,同时对于d某一位为1的,选择向0的一侧走的所有a都会被计入答案,统计子树和即可

## Part 1

$\max~b\leq \min~d$

即对于所有的询问,我们的b总满足取到两者中的最小值

可以发现此时每个元素的信息多了一维b,**但是我们查询的信息只有一维c**,因此可以考虑对于c进行维护答案的值

具体的,我们考虑插入一个怎样的c才能满足$a\oplus c\leq b$这个条件,仿照Part0,我们去从高到底比较a和b的每一位,并假设前k位都相同

1. 对于第k位都为0,显然c这一位只有放0一种取值,递归左子树即可

2. 对于第k位都为1,c可以选择放1,此时之后a一定小于b,那么不需要递归右子树,只需要考虑c放0之后递归左子树即可

3. 对于第k位a为1b为0,c可以选择放0,同理无需递归,只需要递归右子树

4. 对于第k位a为1b为0,显然c只能放1,否则$b<a$

那么我们对于一个元素,建立他的满足条件的C的过程显然是$O(\log W)$

于是我们按上述讨论的方法维护出这样一颗trie,表示某一个c会产生多少合法的元素即可

## Part3

上述过程均没有考虑区间这两维信息,但是他们也是最好考虑的,因为信息满足可减性,所以只需要建立可持久化trie然后对应的在$root_r,root_{l-1}$查询即可

## Part4

全局怎么做?

按照b排序,二分查找最后一个小于等于d的位置,于是它前面的前缀就是满足Part0解决的问题,而剩下的后缀就是满足Part1解决的问题

区间怎么做?

难点在于怎么区分这两类操作,其实就是怎么对于b排序

我们知道有一类经典的~~不出名~~数据结构叫做归并树,树上的每个节点保存了区间所有的数排好序后的数组

直接这样类似的做,排序后建立区间可持久化trie好像就好了!

但是仔细一想这个空间是$O(n\log n\log w)$,死活不可能过的去的

一个来自分块的经典的卡空间技巧是我们对于所有询问挂到每个串上,然后对于每一块都跑一遍,然后回答所有询问

那么本题也可以使用这样的技巧,离线所有询问,然后挂到对应的区间上,每次我们将区间排序然后建立可持久化trie回答上面所有询问即可

复杂度等价于线段树节点长度之和$*\log w$,也就是$O(n\log n\log w)$

不过其实这部分并不是重点,解决前两个Part,后面的就都是纯套路了

猫树就是类似的处理每个区间的信息然后回答询问,不过和这个题确实没关系,~~我只是想表示一下这个离线的思想...~~

```cpp
#include<bits/stdc++.h>
#define vi vector<int>
#define pb push_back
using namespace std;
const int MAXN = 5e5 + 7;

int n, m;
struct rec {
	int a, b;
	rec(int A = 0, int B = 0): a(A), b(B) {};
	bool operator<(const rec &x)const {
		return b < x.b;//按照b排序
	}
} a[MAXN];

namespace fastIO {
#define BUF_SIZE (1<<20)
	static char buf[BUF_SIZE], *p1 = buf, *pend = buf;
	inline char nc() {
		if(p1 == pend) {
			p1 = buf;
			pend = buf + fread(buf, 1, BUF_SIZE, stdin);
		}
		return *p1++;
	}
	inline int read() {
		int x = 0;
		char s = nc();
		for(; !isdigit(s); s = nc());
		for(; isdigit(s); s = nc())x = (x << 1) + (x << 3) + s - '0';
		return x;
	}
}
using namespace fastIO;

const int MAXT = 5e6 + 7;
int root[MAXN], root2[MAXN];
struct seg {//可持久化01trie!!
	int T, ls[MAXT], rs[MAXT], sum[MAXT];
	inline void build(int &x, int y) {
		if(!x || x == y) {
			x = ++T;
			ls[x] = ls[y];
			rs[x] = rs[y];
			sum[x] = sum[y];
		}
	}
	inline void mdf2(int &x, int y, int dep, int p, int q) {
		if(x == y || !x) {
			x = ++T;
			ls[x] = ls[y];
			rs[x] = rs[y];
			sum[x] = sum[y];
		}
		if(dep == 0) {
			sum[x]++;
			return ;
		}//你赢了
		if((p >> (dep - 1) & 1) && (q >> (dep - 1) & 1)) {
			build(rs[x], rs[y]);
			sum[rs[x]]++;//放1直接小于
			mdf2(ls[x], ls[y], dep - 1, p, q);
		} else if((p >> (dep - 1) & 1) && !(q >> (dep - 1) & 1)) {
			mdf2(rs[x], rs[y], dep - 1, p, q);//向右递归,我只能放1
		} else if(!(p >> (dep - 1) & 1) && (q >> (dep - 1) & 1)) {
			build(ls[x], ls[y]);
			sum[ls[x]]++;//放0直接小于
			mdf2(rs[x], rs[y], dep - 1, p, q);
		} else {//都是0只能放0
			mdf2(ls[x], ls[y], dep - 1, p, q);
		}
	}
	inline void mdf(int &x, int y, int dep, int p) {
		if(x == y || !x) {
			x = ++T;
			ls[x] = ls[y];
			rs[x] = rs[y];
			sum[x] = sum[y];
		}
		sum[x]++;
		if(dep == 0)return;//最低位
		if(!(p >> (dep - 1) & 1))mdf(ls[x], ls[y], dep - 1, p);
		else mdf(rs[x], rs[y], dep - 1, p);
	}

	inline int qry2(int x, int dep, int p) {//统计c一路的贡献
		if(!x)return 0;
		if(dep == 0)return sum[x];
		if(p >> (dep - 1) & 1) { //这一位为1
			return sum[x] + qry2(rs[x], dep - 1, p);
		} else {//为0!
			return sum[x] + qry2(ls[x], dep - 1, p);
		}
	}
	inline int qry(int x, int dep, int p, int c) {//计算异或c后小等于p的
		if(!x)return 0;
		if(dep == 0)return sum[x];
		if(p >> (dep - 1) & 1) { //这一位为1
			if(c >> (dep - 1) & 1)return sum[rs[x]] + qry(ls[x], dep - 1, p, c);
			else return sum[ls[x]] + qry(rs[x], dep - 1, p, c);
		} else {//为0!
			if(c >> (dep - 1) & 1)return qry(rs[x], dep - 1, p, c);
			else return qry(ls[x], dep - 1, p, c);
		}
	}
	inline void init() {
		T = 0;
		sum[0] = ls[0] = rs[0] = 0;
	}
} T1, T2;

int l[MAXN], r[MAXN], c[MAXN], d[MAXN], ans[MAXN];
vi v[MAXN];

inline void build(int l, int r) {
	sort(a + l, a + r + 1);
	for(int i = l - 1; i <= r; ++i)root[i] = root2[i] = 0;
	T1.init();
	for(int i = l; i <= r; ++i) {
		T1.mdf(root[i], root[i - 1], 24, a[i].a);
	}
	T2.init();
	for(int i = l; i <= r; ++i) {
		T2.mdf2(root2[i], root2[i - 1], 24, a[i].a, a[i].b);
	}
	return ;
}

inline void solveq(int k, int l, int r) {
	for(auto p : v[k]) {
		int fz = upper_bound(a + l, a + r + 1, rec(0, d[p])) - a - 1;
		if(fz >= l) {
			ans[p] += T2.qry2(root2[fz], 24, c[p]);
		}
		if(fz < r) {
			ans[p] += T1.qry(root[r], 24, d[p], c[p]) - T1.qry(root[fz], 24, d[p], c[p]);
		}
	}
	return ;
}
#define mid ((l+r)>>1)

inline void solve(int k, int l, int r) {
	if(l != r) {
		solve(k << 1, l, mid);
		solve(k << 1 | 1, mid + 1, r);
	}
	if(!v[k].empty()) {
		build(l, r);
		solveq(k, l, r);
	}
	return;
}

inline void addqry(int k, int l, int r, int L, int R, int p) {
	if(L <= l && r <= R) {
		v[k].pb(p);
		return ;
	}
	if(L <= mid)addqry(k << 1, l, mid, L, R, p);
	if(R > mid)addqry(k << 1 | 1, mid + 1, r, L, R, p);
}

int main() {
	n = read();
	m = read();
	for(int i = 1; i <= n; ++i) {
		a[i].a = read();
		a[i].b = read();
	}
	for(int i = 1; i <= m; ++i) {
		l[i] = read();
		r[i] = read();
		c[i] = read();
		d[i] = read();
		addqry(1, 1, n, l[i], r[i], i);
	}
	solve(1, 1, n);
	for(int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：zzw4257 (赞：3)

~~我真的不想调格式啊啊~~

> 给定一个二元组序列$(a_i,b_i)$,多次询问形如$(c_i,d_i)$,求$i$的个数使得$a_i\bigoplus c_i\leqslant \min\{b_i,d_i\}$

考场上完全不会$b$小的部分分~~

- 区间为$[1,n]$

	- 所有的$\min$均由$d_i$取到

	用$c_i$在Trie树上游走，假设走到$x$,这个高位是$1$，必定存在一边使这一位为$0$,累加这一边遍历次数，走另一边，否则高位为$0$，直接走异或起来为$0$的那边即可

	- 所有的$\min$均由$b_i$取到

	让$a_i$能取到$\leqslant b_i$的$c_i$在$\mathrm{Trie}$树上是一些不交的子树内的标记点，具体来说跟上一个Sub一样假装用$a_i$作为$c_i$来游走，其中会涉及到一些`必定存在一边使这一位为 0 `的选择，把这些子树打上标记(真的打在根处)，以后用$c_i$遍历时累加经过标记即可
   - 一般情况
   
   考虑把$(a,c),(b,d)$丢在一起按$b/d$从大到小排序，按序处理即可
- 区间为$[l,r]$
	
    首先差分掉转为前缀$[1,i]$，然后问题变成了计算顺序的维护，一个Naive的想法是使用树套树，考察问题本质是要让每个询问被出现时间更早的修改更新到，这是一个偏序问题，考虑CDQ分治，具体的，先按照$b/d$排序，对每个分治区间两侧按照位置排序，之后双指针
    - 左边修改右边询问 :$\min$由$b_i$取到
    - 右边修改左边询问 :$\min$由$d_i$取到
    
	  按照最初的手段处理即可

---

## 作者：UltiMadow (赞：3)

**非正解**

~~考场上没想到分治，就无脑写分块了（~~

这么大一个数据结构题，直接考虑分块（

对于非整块的查询，直接暴力搞就行了

对于整块，考虑将块内排序，分成 $b_i< d$ 和 $b_i\ge d$ 两类处理

1. 对于 $b_i\ge d$ 的点，我们发现它们排完序之后都在一个连续区间内，于是用可持久化 trie 类似于主席树一样查询即可

2. 对于 $b_i<d$ 的点，我们可以考虑把询问离线下来按 $d$ 从小到大排序，于是发现每次新处理一次询问这一种点的数量只会增加  
然后每次新加入一个点的时候考虑有哪些 $c$ 满足 $a_i\oplus c\le b_i$，考虑依次处理每一位，发现这种 $c$ 是一些区间的交  
于是就变成了区间加 1，单点查询问题，用树状数组维护就行了

设块长 $S$，则对于非整块，查询复杂度 $\mathcal O(QS)$，对于整块，查询复杂度 $\mathcal O(Q\frac nS \log a)$，于是当 $S=\sqrt{n\log a}$ 的时候取到理论最优复杂度 $\mathcal O(Q\sqrt{n\log a})$

实测 $S=1750$ 时最优，可以获得 90pts 的好成绩，会被 $l=1,r=n$ 卡掉（本机跑 6s 左右）~~（原来这不是部分分而是光明正大卡 sqrt 算法啊~~

于是只能加上特判，在 $l=1,r=n$ 的时候把 $S$ 调成 $n$ 才能通过/dk/dk

[**code**](https://www.luogu.com.cn/paste/6d9paxz0)

---

## 作者：7KByte (赞：3)

可能被卡的 T3 做法

T3 的方法都写到部分分里了。

$N^2$ 的做法跳过。

不考虑 $b$ 的部分分，就是可持久化 Trie 模板。

不考虑 $d$ 的部分分，我们可以考虑每个位置会对哪些$c$产生贡献，所以我们可以对$c$建立 Trie 树，然后在$Trie$树上的路径打贡献标记即可。对于一个询问，我们直接找路径上的贡献标记在$[l,r]$之间的贡献个数，可以动态开点线段树。

$l=1,r=n$的部分分，可以不用开线段树，直接记录贡献个数，然后可持久化 Trie 需要支持修改，套一个树状数组即可。

我们对每个位置按 $b_i$ 排序，每个询问按 $d_i$ 排序，然后对于每个询问，$b\le d$的位置和$b>d$的分开计算贡献。说白了就是把上面几个方法结合起来。

所以我们需要维护一个树状数组套可持久化trie，和一个trie套动态开点线段树。这样时间复杂度$\rm O(N\log^2 N)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 100005
#define M 10000000
#define W 2500005
using namespace std;
char buf[1<<22],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read(){
    int x=0;char ch=getchar();
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x;
}
int n,q;
struct node{
	int op,a,b;
	bool operator<(const node o)const{return b<o.b;}
}u[N];
struct query{
	int op,c,d,l,r;
	bool operator<(const query o)const{return d<o.d;}
}b[N];
int ch[M][2],sz[M],rt[N],idx;
int ins(int x,int y,int op,int ps){
	int now=++idx;
	ch[now][0]=ch[x][0];
	ch[now][1]=ch[x][1];
	sz[now]=sz[x]+op;
	if(ps<0)return now;
	int cur=(y>>ps)&1;
	ch[now][cur]=ins(ch[x][cur],y,op,ps-1);
	return now;
}
int ask(int x,int u,int v,int ps){
	if(!x||ps<0)return 0;
	if((v>>ps)&1){
		int cur=(u>>ps)&1;
		return sz[ch[x][cur]]+ask(ch[x][cur^1],u,v,ps-1);
	}
	else{
		return ask(ch[x][(u>>ps)&1],u,v,ps-1);
	}
}
void add(int x,int y,int op){for(;x<=n;x+=x&-x)rt[x]=ins(rt[x],y,op,23);}
int query(int x,int u,int v){
	int sum=0;
	for(;x;x-=x&-x)sum+=ask(rt[x],u,v+1,23);
	return sum;
}
struct Node{
	int sum,l,r;
	Node(){sum=0;}
}a[M];int tot;
#define ls a[x].l
#define rs a[x].r
#define S a[x].sum
void insw(int x,int l,int r,int pos){
	S++;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(mid>=pos){
		if(!ls)ls=++tot;
		insw(ls,l,mid,pos);
	}
	else {
		if(!rs)rs=++tot;
		insw(rs,mid+1,r,pos);
	}
}
int get(int x,int l,int r,int L,int R){
	if(!x)return 0;
	if(l>=L&&r<=R)return S;
	int mid=(l+r)>>1,sum=0;
	if(mid>=L)sum+=get(ls,l,mid,L,R);
	if(mid<R)sum+=get(rs,mid+1,r,L,R);
	return sum;
}
int top=1,nxt[W][2],Rt[W],mat[N],fa[W];
void addw(int x,int op){
	int now=1;
	pre(i,23,0){
		int cur=(x>>i)&1;
		if(!nxt[now][cur])nxt[now][cur]=++top;
		fa[nxt[now][cur]]=now;now=nxt[now][cur];
	}
	mat[op]=now;
}
void addtag(int x,int u,int v,int val,int ps){
	if(!x||ps<0)return;
	if((v>>ps)&1){
		int cur=(u>>ps)&1;
		if(nxt[x][cur]){
			if(!Rt[nxt[x][cur]])Rt[nxt[x][cur]]=++tot;
			insw(Rt[nxt[x][cur]],1,n,val);
		}
		addtag(nxt[x][cur^1],u,v,val,ps-1);
	}
	else{
		addtag(nxt[x][(u>>ps)&1],u,v,val,ps-1);
	}
}
int gettag(int x,int l,int r){
	int sum=0;
	while(x)sum+=get(Rt[x],1,n,l,r),x=fa[x];
	return sum;
}
int ans[N];
int main(){
	//freopen("island.in","r",stdin);
	//freopen("island.out","w",stdout);
	n=read();q=read();
	rep(i,1,n)u[i].op=i,u[i].a=read(),u[i].b=read();
	rep(i,1,q)b[i].op=i,b[i].l=read(),b[i].r=read(),b[i].c=read(),b[i].d=read(),
		addw(b[i].c,i);
	sort(u+1,u+n+1);
	rep(i,1,n)add(u[i].op,u[i].a,1);
	sort(b+1,b+q+1);
	int j=1;
	rep(i,1,q){
		while(j<=n&&u[j].b<b[i].d){
			add(u[j].op,u[j].a,-1);
			addtag(1,u[j].a,u[j].b+1,u[j].op,23);
			j++;
		}
		ans[b[i].op]=gettag(mat[b[i].op],b[i].l,b[i].r)+query(b[i].r,b[i].c,b[i].d)-query(b[i].l-1,b[i].c,b[i].d);
	}
	rep(i,1,q)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：FxorG (赞：2)

**不一定正确！提供一个三合一才能过的分块**

$$ a_i \ xor\ c_j \le min(b_i,d_j)$$ 

$$ a_i \ xor \ c_j \le b_i$$

$$ a_i \ xor \ c_j \le d_j$$

$$a_i \ xor \ c_j \le d_j$$ 

可以考虑 $c_j,d_j=0$ 那么 $a_i=0$。

$c_j=1,dj=0,ai=1$。

$c_j=0,d_j=1,a_i=1/0$ 如果选 $1$ 的话就接着跳， $0$ 就加上左子树的所有的元素个数。

$c_j=1,d_j=1,a_i=1/0$ $0$ 接着跳，加上 $1$ 那边子树的元素个数。

然后，区间就可持久化 01-trie。

$$ a_i \ xor \ c_j \le b_i$$

$$ c_j \ xor \ a_i \le b_i$$

$b_i,a_i$ 作为询问 就一样跳 然后整个子树可以就加计数器 一个询问符合的 $c_j$ 就是 $c_j$ 到根的路径计数器和。

可以可持久化，对于每一个 $c_j$ 去拆 $[1,r]-[1,l-1]$ 就是答案。

我们需要保证查询的时候 $a_i,b_i$ 都已经刚刚好更新完毕了，这个将 $a_i,b_i$ 的加计数器也认为操作，右端点是 $i$，然后按右端点排序就可以。

**先修改后询问！**

那么，如何分离出 $[L,x],[x+1,R]$ 使得 $[L,x]$ 是 $min\{b_i\}\ge d,i\in[L,x]$?

实际上直接分块就好了，块内从小到大排序，并且我们可以将询问离线按 $d$ 排，这样每次块内 $x$ 不降，可以双指针优化。

算下复杂度，令 $T$ 为块长。

$O(\dfrac{n}{T}T\log T+mT+\dfrac{n}{T}m\log(\dfrac{n}{T}m)+\dfrac{n}{T}m\log w)$

第一个为预处理块的复杂度，第二个为在线处理 $d\le b$ 的复杂度，第三个为离线完操作+排序的复杂度，因为有 $\dfrac{n}{T}$ 个块，假如每次每个块都被覆盖到，那么会有 $m$ 次。最后一个是处理这些操作的复杂度。

**关于块长**，我们发现瓶颈是 $\dfrac{n}{T}m\log(\dfrac{n}{T}m)$，所以我们让 $T$ 尽可能大，实测在 $1750$ 最优。

[评测记录](https://www.luogu.com.cn/record/54653671)

$\text{Code}$

```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <queue>
#include <map>

#define ll long long

using namespace std;
int rd() {
	int f=1,sum=0; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum*f;
}
ll lrd() {
	ll f=1,sum=0; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum*f;
}
void pr(int x) {
	if(x<0) {putchar('-');x=-x;}
	if(x>9) pr(x/10);
	putchar(x%10+'0');
}
void lpr(ll x) {
	if(x<0) {putchar('-');x=-x;}
	if(x>9) pr(x/10);
	putchar(x%10+'0');
}
/*
有区间之后枚举块
之前将所有c加入trie
考虑块排序后的区间所对应的 这个可以在分块build的时候处理出来 
*/ 
#define N (int)(1e5+2) 
#define M 80
#define il inline

int ans[N],son[2][N*30],sum[N*30];
int cnt[N],rid[N],a[N],b[N],C[N],L[M],R[M],id[N];
int n,m,bl,tot=1;

struct ques {
	int l,r,uid,yx;
}q[N*M]; int qtot=0;
struct node {
	int x,y;
}tmp[1752];
int B[M][1752],rt[N],rttot;
bool cmp(node x,node y) {
	return x.x<y.x;
}

il void ins(int x) {
	int pre=rt[rttot]; rt[++rttot]=++tot;
	for(int i=24;i>=0;i--) {
		int c=(x>>i)&1;
		sum[tot]=sum[pre]+1;
		son[c^1][tot]=son[c^1][pre];
		son[c][tot]=tot+1; ++tot;
		pre=son[c][pre];
	}
	sum[tot]=sum[pre]+1;
}

il int query(int l,int r,int c,int d) {
	l=rt[l-1]; r=rt[r];
	int res=0;
	for(int i=24;i>=0;i--) {
		int r1=(c>>i)&1,r2=(d>>i)&1;
		if(r2) res+=sum[son[r1][r]]-sum[son[r1][l]];
		if(!r1&&!r2) l=son[0][l],r=son[0][r];
		if(r1&&!r2) l=son[1][l],r=son[1][r];
		if(!r1&&r2) l=son[1][l],r=son[1][r];
		if(r1&&r2) l=son[0][l],r=son[0][r];
	}
	res+=sum[r]-sum[l];
	return res;
}

il void build(int x) {
	for(int i=L[x];i<=R[x];++i) {
		tmp[i-L[x]+1].x=b[i]; tmp[i-L[x]+1].y=i;
	}
	sort(tmp+1,tmp+1+R[x]-L[x]+1,cmp);
	for(int i=1;i<=R[x]-L[x]+1;++i) {
		B[x][i]=tmp[i].x; rid[L[x]+i-1]=tmp[i].y;
	}
	cnt[x]=L[x];
}

il void update(int l,int r,int c,int d,int uid) {
	if(id[l]==id[r]) {
		for(int i=l;i<=r;++i) ans[uid]+=((a[i]^c)<=min(b[i],d));
	} else {
		for(int i=l;i<=R[id[l]];++i) ans[uid]+=((a[i]^c)<=min(b[i],d));
		for(int i=L[id[r]];i<=r;++i) ans[uid]+=((a[i]^c)<=min(b[i],d));
		for(int i=id[l]+1;i<id[r];++i) {
			while(cnt[i]<R[i]&&B[i][cnt[i]-L[i]+1]<=d) ++cnt[i];
			if(B[i][cnt[i]-L[i]+1]<d) {
				q[++qtot]=ques{1,L[i]-1,uid,2}; q[++qtot]=ques{1,R[i],uid,3};
			} else { //L[i]~cnt[i]-1 cnt[i]-R[i]
				if(L[i]<=cnt[i]-1) q[++qtot]=ques{1,L[i]-1,uid,2},q[++qtot]=ques{1,cnt[i]-1,uid,3};
				ans[uid]+=query(cnt[i],R[i],c,d);
			}
		}
	}
}

bool cmp2(ques x,ques y) {
	return x.r==y.r?x.yx<y.yx:x.r<y.r;
}

il void insC(int x) {
	int p=1;
	for(int i=24;i>=0;i--) {
		int c=(x>>i)&1;
		if(!son[c][p]) son[c][p]=++tot;
		p=son[c][p];
	}
}

il void solve(int x,int y) {
	int p=1;
	for(int i=24;i>=0;i--) {
		int r1=(x>>i)&1,r2=(y>>i)&1;
		if(r2) sum[son[r1][p]]++;
		if(r1&&r2) p=son[0][p];
		if(!r1&&r2) p=son[1][p];
		if(!r1&&!r2) p=son[0][p];
		if(r1&&!r2) p=son[1][p]; 
	}
	++sum[p];
}

il int query(int x) {
	int res=0,p=1;
	for(int i=24;i>=0;i--) {
		int c=(x>>i)&1;
		res+=sum[p]; p=son[c][p];
	}
	res+=sum[p];
	return res;
}

struct ask{
	int l,r,c,d,id;
}A[N];
il bool cmp3(ask x,ask y) {
	return x.d<y.d;
}
int st[20][N];

il int st_qry(int l,int r) {
	int qwq=log2(r-l+1);
	return max(st[qwq][l],st[qwq][r-(1<<qwq)+1]);
}

il void solve1() {
	for(int i=1;i<=m;++i) {
		q[++qtot]=ques{1,A[i].l-1,i,2}; q[++qtot]=ques{1,A[i].r,i,3};
	}
	for(int i=1;i<=n;++i) q[++qtot]=ques{0,i,i,1};
	sort(q+1,q+1+qtot,cmp2);
	for(int i=1;i<=m;++i) insC(C[i]);
	for(int i=1;i<=qtot;++i) {
		if(q[i].yx==1) {
			solve(a[q[i].uid],b[q[i].uid]);
		} else if(q[i].yx==2) {
			ans[q[i].uid]-=query(C[q[i].uid]);
		} else {
			ans[q[i].uid]+=query(C[q[i].uid]);
		}
	}
	for(int i=1;i<=m;++i) pr(ans[i]),puts("");
}

namespace solve2 {
	struct node {
		int x,id;
	}T[N];
	bool cmp(node x,node y) {
		return x.x<y.x;
	} int tmp[N];
	void sol() {
		for(int i=1;i<=n;i++) T[i].x=b[i],T[i].id=i;
		sort(T+1,T+1+n,cmp);for(int i=1;i<=n;i++) tmp[i]=b[i]; sort(tmp+1,tmp+1+n);
		for(int i=1;i<=n;i++) ins(a[T[i].id]);
		for(int i=1;i<=m;i++) {
			int qwq=upper_bound(tmp+1,tmp+1+n,A[i].d)-tmp-1;
			if(qwq) q[++qtot]=ques{1,qwq,i,1}; 
			if(qwq+1<=n) ans[A[i].id]+=query(qwq+1,n,A[i].c,A[i].d);
		}
		for(int i=1;i<=tot;i++) sum[i]=son[0][i]=son[1][i]=0; tot=1;
		for(int i=1;i<=m;i++) insC(C[i]);
		for(int i=1;i<=n;i++) q[++qtot]=ques{1,i,T[i].id,0};
		sort(q+1,q+1+qtot,cmp2);
		for(int i=1;i<=qtot;i++) {
			if(q[i].yx==0) solve(a[q[i].uid],b[q[i].uid]);
			else ans[q[i].uid]+=query(C[q[i].uid]);
		}
		for(int i=1;i<=m;i++) pr(ans[i]),puts("");
	}
}

int main() {
	n=rd(); m=rd(); bl=1750;
	for(int i=1;i<=n;++i) a[i]=rd(),b[i]=rd();
	for(int i=1;i<=n;++i) st[0][i]=b[i];
	for(int i=1;i<=18;++i)
		for(int j=1;j+(1<<i)-1<=n;j++)
			st[i][j]=max(st[i-1][j],st[i-1][j+(1<<(i-1))]);	
	bool fl=1,fl2=1;
	for(int i=1;i<=m;++i) {      
		A[i].l=rd(); A[i].r=rd(); A[i].c=C[i]=rd(); A[i].d=rd(); A[i].id=i;
		if(A[i].d<st_qry(A[i].l,A[i].r)) fl=0;
		if(A[i].l!=1||A[i].r!=n) fl2=0;
	}
	if(fl) {
		solve1(); return 0;
	}
	if(fl2) {
		solve2::sol(); return 0;
	}
	for(int i=1;i<=n;++i) id[i]=(i-1)/bl+1;
	for(int i=1;i<=id[n];++i) L[i]=(i-1)*bl+1,R[i]=i*bl; R[id[n]]=n;
	for(int i=1;i<=id[n];++i) build(i);
	for(int i=1;i<=n;++i) ins(a[rid[i]]);
	sort(A+1,A+1+m,cmp3);
	for(int i=1;i<=m;++i) update(A[i].l,A[i].r,A[i].c,A[i].d,A[i].id);
	for(int i=1;i<=n;++i) q[++qtot]=ques{rid[i],i,0,1};
	sort(q+1,q+1+qtot,cmp2);
	for(int i=1;i<=tot;i++) sum[i]=0,son[0][i]=son[1][i]=0; tot=1;
	for(int i=1;i<=m;++i) insC(C[i]);
	for(int i=1;i<=qtot;++i) {
		if(q[i].yx==1) {
			solve(a[q[i].l],b[q[i].l]);
		} else if(q[i].yx==2) {
			ans[q[i].uid]-=query(C[q[i].uid]);
		} else {
			ans[q[i].uid]+=query(C[q[i].uid]);
		}
	}
	for(int i=1;i<=m;++i) pr(ans[i]),puts("");
	return 0;
}
```

---

## 作者：lupengheyyds (赞：1)

区间变为前缀相减，不难发现按 $b_i<d$ 和 $b_i\ge d$ 分类讨论。

- $b_i<d$ 此时满足 $a_i\oplus c\le b_i$ 的 $c$ 在 $01$ 字典树上处于一条链的若干子树，可以单次 $\mathcal O(\log)$ 修改和查询。

- $b_i\ge d$ 此时满足 $a_i\oplus c\le d$ 的 $a_i$ 在 $01$ 字典树处于一条链的若干子树，可以单次 $\mathcal O(\log)$ 修改和查询。

有 $r,d$ 两维限制，用 CDQ 即可。

```cpp
#include<bits/stdc++.h>
#define io ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
#define int long long
#define loop(i,a,b) for(int i=a;i<=b;i++)
#define pool(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int NN=1e5+5;
int n,q; 
struct Query{
	int r,c,d,id,f;
	bool operator<(const Query &b)const{
		if(r!=b.r)return r<b.r;
		return id<b.id;//修改总在询问前，插入总在删除前 
	}
}qry[NN*3];
struct Trie1{
	int trie[NN*24][2],val[NN*24],tot;
	void Insert(int a,int b,int v){//存储[a^c<=b]的c，子树链加，相当于标记永久化 
		int p=0;
		pool(i,23,0){
			int ta=(a>>i)&1,tb=(b>>i)&1;
			loop(c,0,1)if(!trie[p][c])trie[p][c]=++tot;
			if(tb==1)val[trie[p][ta]]+=v;
			p=trie[p][ta^tb];
		}
		val[p]+=v;
		return;
	} 
	int Ask(int c){//查询存储[a^c<=b]的c，链和 
		int sum=0,p=0;
		pool(i,23,0){
			int tc=(c>>i)&1;
			p=trie[p][tc];
			if(!p)return sum;
			sum+=val[p];
		}
		return sum;
	}
	void Clear(){
		loop(i,0,tot)val[i]=trie[i][0]=trie[i][1]=0;
		tot=0;
		return;
	}
}t1;//t1存b<=d,t2存b>d
struct Trie2{
	int trie[NN*24][2],val[NN*24],tot;
	void Insert(int a,int v){//储存[a^c<=d]的a，链加 
		int p=0;
		pool(i,23,0){
			int ta=(a>>i)&1;
			if(!trie[p][ta])trie[p][ta]=++tot;
			p=trie[p][ta];
			val[p]+=v;
		}
		return;
	}
	int Ask(int c,int d){//查询[a^c<=d]的a，子树链和 
		int p=0,sum=0;
		pool(i,23,0){
			int tc=(c>>i)&1,td=(d>>i)&1;
			if(td==1)sum+=val[trie[p][tc]];
			p=trie[p][tc^td];
			if(!p)return sum;
		}
		sum+=val[p];
		return sum;
	}
	void Clear(){
		loop(i,0,tot)val[i]=trie[i][0]=trie[i][1]=0;
		tot=0;
		return;
	}
	
}t2;
int ans[NN];
void CDQ(int l,int r){
	if(l==r)return;
	int mid=l+r>>1;
	CDQ(l,mid),CDQ(mid+1,r);
	int R=l;
	loop(i,l,mid)if(!qry[i].id)t2.Insert(qry[i].c,1);
	loop(i,mid+1,r){
		for(;R<=mid&&qry[R].d<qry[i].d;R++)
			if(!qry[R].id)t2.Insert(qry[R].c,-1),t1.Insert(qry[R].c,qry[R].d,1);
		if(qry[i].id)ans[qry[i].id]+=qry[i].f*(t1.Ask(qry[i].c)+t2.Ask(qry[i].c,qry[i].d));
	}
	t1.Clear(),t2.Clear();
	inplace_merge(qry+l,qry+mid+1,qry+r+1,[&](Query a,Query b){return a.d<b.d;});
	return;
}
int cnt=0;
signed main(){
	io;cin>>n>>q;
	loop(i,1,n){
		int a,b;cin>>a>>b;
		qry[++cnt]={i,a,b,0,i};
	}
	loop(i,1,q){
		int l,r,c,d;cin>>l>>r>>c>>d;
		qry[++cnt]={r,c,d,i,1};
		qry[++cnt]={l-1,c,d,i,-1};
	}
	sort(qry+1,qry+1+cnt);
	CDQ(1,cnt);
	loop(i,1,q)cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：sqrtqwq (赞：1)

[problem](https://www.luogu.com.cn/problem/P7470)

我们可以发现这个东西可以拆成很多个子问题，然后累计合并，这个东西可以使用线段树合并来做。

先考虑 $b_i > d_j$ 的情况。那么答案就是 $\sum [a_i \oplus c_j \le d_j]$。我们把 $a_i$ 插入 $01 \text{trie}$ 中。然后我们从上往下走，走到深度为 $h$ 的节点，那么代表他的值等于 $c_i \oplus d_j$ 的前 $h$ 位。然后我们考虑第 $h + 1$ 位。

- $d_i = 0$，那么 $a_i$ 和 $c_j$ 的第 $h + 1$ 位必须相等，否则 $a_i \oplus c_j > d_j$，然后直接往这个方向走即可。

- $d_i = 1$，那么此时 $a_i$ 和 $c_j$ 的第 $h + 1$ 位任意取都行。那么就有两种可能：

	- 如果 $a_i$ 和 $c_j$ 的第 $h + 1$ 位不一样，那么此时 $a_i$ 依然等于 $c_j \oplus d_j$，所以我们向这个方向继续走即可。
	- 如果 $a_i$ 和 $c_j$ 的第 $h + 1$ 位一样，那么此时 $a_i \oplus c_j$ 就会一定小于 $d_j$ 了，那么对于答案的贡献就是这个子树里 $a_i$ 的个数之和。

这一部分就是 [CF817E](https://www.luogu.com.cn/problem/CF817E)。比较简单。

接下来我们考虑 $b_i \le d_j$ 的情况。这一个部分比较困难。但是我们发现这一个部分和 $a_i \oplus c_j \le d_j$ 的结构很像，所以我们可以考虑类似的操作。

前面的是对于 $a_i$ 扔到 $01 \text{trie}$ 上然后查询 $(c_j,d_j)$，那么我们这次就可以把 $c_j$ 扔到 $01 \text{trie}$ 上，然后记录每一个 $(a_i,b_i)$ 对于 $c_j$ 的贡献。

具体的我们只需要把 $c_j$ 离线下来，然后对于 $(a_i,b_i)$ 查询，但是唯一的区别就是在上面我们遇到了一个节点满足 $a_i \oplus c_j < d_j$ 时我们加上的是子树里 $a_i$ 的个数和，而现在我们要在这一个子树打一个标记，让整一个子树全部都加上 $1$，然后统计答案是就是从根到 $c_j$ 路径上的标记和。

当然我们不能每一次都建 $2$ 个 $01 \text{trie}$，但是那样子的复杂度爆炸，无法接受。

然后我们考虑如何优雅的计算多组数据。

首先我们将 $(a_i,b_i)$ 和 $(c_j,d_j)$ 按照 $b_i,d_j$ 升序排列。然后那双指针进行维护。此时我们开两个 $01 \text{trie}$。然后当我们扫到了第 $j$ 个问题不满足 $b_j > d_j$ 的 $a_i$ 从维护第一个 $01 \text{trie}$ 中删除，然后计算贡献。同时对于满足条件的 $(a_i,b_i)$ 加入维护第二个情况的 $01 \text{trie}$ 上并且计算贡献。

当然此时两个指针都往右移动。

---

## 作者：Petit_Souris (赞：1)

三年前在这个题上获得最低档暴力 20 分。今天再次挑战这个题，当时的小朋友望着遥不可及的黑题无助地崩溃的画面在我眼前复现。三年后，我在我跌倒的地方爬起，我已经不再是以前的那个我了。

实话实说：这个题确实不难且非常小清新（如果你的做法比较牛）。

首先观察 $a\oplus c\le \min(b,d)$ 这个限制。显然可以拆成 $a\oplus c\le b$ 和 $a\oplus c\le d$ 两个限制，且要同时满足。

先考虑 $b\ge d$ 的部分分：我们发现合法的 $c$ 可以用 $\log $ 个区间覆盖：最高位 $<a\oplus b$ 的最高位、最高位 $=a\oplus b$ 的最高位，次高位更小、前二高位相等，第三高位更小......这样问题就变成了给定一些区间 $[l_1,r_1],\dots [l_k,r_k]$，每次给定 $c,u,v$，查询编号在 $[u,v]$ 中的区间有多少包含 $c$，离线差分之后就是一个线段树板子。

这时候意识到原问题和这个部分分也是差不多的：我们只是需要多考虑一个 $a\oplus c\le d$。和上面类似的，把每个 $(a,b)$ 的限制先拆分，$c$ 挂到对应的区间上面。扫描所有的区间（容易发现这些区间就是 $[0,2^{24}-1]$ 的线段树节点，所以数量是 $2^{25}$），建立 trie 树来统计答案。按照下表顺序从小到大扫描所有的 $a$ 限制和 $c$ 查询（差分到了左右端点两个位置），如果遇到限制，就把 $a$ 插入 trie 树，否则直接在 trie 树上查询。时间复杂度 $\mathcal O(n\log^2 V)$，注意控制时间空间上的常数。

---

## 作者：lzyqwq (赞：1)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/p/17864462.html)**

我永远喜欢数据结构。

**[题目传送门](https://www.luogu.com.cn/problem/P7470)**

> - 给出 $n$ 个二元组 $(a_i,b_i)$，有 $q$ 次询问，每次给出 $l_i,r_i,c_i,d_i$，求有多少个 $j$ 满足 $j\in[l_i,r_i]$ 且 $a_j\oplus c_i\le \min\{b_j,d_i\}$。 
>
> - $n,q\le 10^5$，设值域为 $V$，$|V|\le 2^{24}$。
>
> - $2.00\,\text{s}\,/\,256.00\,\text{MB}$。

一句话题解：离线，拆 $\min$，考虑贡献。

我们知道线段树可以将一个区间拆成 $\mathcal{O}(\log n)$ 个不交的节点，使得这些节点的并等于给定的区间。

于是我们考虑离线，在线段树上将每个询问拆成 $\mathcal{O}(\log n)$ 个子区间，分别求解这些子区间的答案。

考虑对于线段树的一个节点 $[L,R]$，求解挂在它上面的询问。将这些询问按照 $d_i$ 从小到大排序，同时将节点内的二元组按照 $b_j$ 从小到大排序。

对于一个询问，分成 $b_j<d_i$ 和 $b_j\ge d_i$ 两类二元组。不难发现排序后**存在一个 $\boldsymbol k$ 使得 $\boldsymbol{k\in[L,R]}$ 且当 $\boldsymbol{j\in[L,k)}$ 时，$\boldsymbol{b_j<d_i}$；当 $\boldsymbol{j\in[k,R]}$ 时，$\boldsymbol{b_j\ge d_i}$**。

即，两类二元组分别在一个连续区间内。

- 对于 $b_j\ge d_i$ 的部分，$\min\{b_j,d_i\}=d_i$。

  这部分较为平凡。就是求区间内有多少个数异或定值后不超过定值。使用 01 trie 维护，将区间内所有数加入 01 trie，统计根节点（即全局）的答案。

  考虑一个子问题：统计以 $u$ 为根的子树内的答案。维护每个点子树内部的答案。讨论 $d_i$ 当前位是 $0$ 还是 $1$ 即可。若是 $1$，则另这一位取 $0$ 的数都满足条件需要被统计。这样的数在当 $u$ 的某个儿子内。维护一个 $sz_u$ 表示以 $u$ 为根的子树内，有多少个询问内的数。用 $sz_u$ 以及递归儿子求解即可。
  
- 对于 $b_j<d_i$ 的部分，$\min\{b_j,d_i\}=b_j$。
   
  对于区间内的每个二元组，将其插入 01 trie，并考虑它会对哪些询问的 $c_i$ 产生贡献。此时的 01 trie 是对于 $c_i$ 维护的。
  
  同样考虑这个二元组会被以 $u$ 为根的子树内的哪些数统计。讨论 $b_j$ 当前位是 $0$ 还是 $1$。如果是 $1$，意味着另这一位为 $0$ 的 $c_i$ 都会统计到这个二元组。这样的 $c_i$ 也在某个儿子的 $u$ 的子树内。即子树内所有数的贡献 $+1$。此时 $sz_u$ 数组变成懒标记，使得某个叶子的初始答案，加上它即其祖先的懒标记后，等于其在当前加入的二元组构成的集合中的答案。
  
  对于一个询问，查询 $c_i$ 的答案即可。由于初始空集合答案为 $0$，只需要统计根链上所有点的标记之和。
  
  **本质上是动态开点线段树。**

由于实现的原因，01 trie 需要支持删除操作。因此我们不能简单地把空节点理解成不存在的节点。此处 01 trie 上的空节点定义为，**仅当 $\boldsymbol{sz_u=0}$ 时，$\boldsymbol{u}$ 为空**。注意那个是必要条件。这样我们不去计算空节点的原因不是因为其不存在，而是因为**其没有贡献**。

同样要再次强调这句话，**本质上是动态开点线段树**。

我们发现，由于排过序，若按顺序处理询问，**$\boldsymbol{k}$ 单调不降**。

每次 $k$ 移动时，将当前位置从第一类的 01 trie 中删除，加入第二类的 01 trie。这样在一个线段树节点内，一个二元组被操作的次数是 $\mathcal{O}(1)$ 的。单次操作时间复杂度为 $\mathcal{O}(\log |V|)$，一个二元组会在 $\mathcal{O}(\log n)$ 个线段树节点中被操作。

对于一个询问，拆分成了 $\mathcal{O}(\log n)$ 段，一段查询的时间复杂度为 $\mathcal{O}(\log |V|)$。

所以，时间复杂度为 $\mathcal{O}((n+q)\log n\log |V|)$，空间复杂度为 $\mathcal{O}((n+q)\log |V|)$。


**[提交记录（$\color{white}\colorbox{limegreen}{\bf Accepted}$ $\color{limegreen}\bf 100$，$\bf 8.00\,s\,/\,54.18\,MB$）](https://www.luogu.com.cn/record/137294663) [代码](https://www.luogu.com.cn/paste/ojhxn4b0)**

---

## 作者：Alex_Wei (赞：1)

> [P7470 [NOI Online 2021 提高组] 岛屿探险](https://www.luogu.com.cn/problem/P7470)

一道相当裸的题目。

考虑一次询问的本质，这个 $\min(b, d)$ 很烦，分类讨论搞掉，发现是形如三维偏序的东西：$l_i\leq p \leq r_i$，$b_p\leq d_i$ 或 $b_p > d_i$，且 $a_p\oplus c_i \leq b_p$ 或 $d_i$，自然考虑 CDQ 分治。

首先将区间询问差分成 $r$ 处贡献系数为 $1$ 和 $l - 1$ 处贡献系数为 $-1$ 的前缀询问，用 $(Q, c, d, qid, coef)$ 描述，表示查询前缀下标 $Q$，劳累度为 $c$，有趣度为 $d$，询问序号为 $qid$，贡献系数为 $coef$。

对于岛屿，同样用 $(P, a, b)$ 描述，下标为 $P$，劳累度为 $a$，有趣度为 $b$。

先套一层 CDQ 分治，将所有询问和岛屿按照下标为第一关键字从小到大，若下标相同则岛屿优先，则一个询问只有可能受到在它之前的岛屿的贡献。

现在只需考虑左区间 $[l, mid]$ 对右区间 $[mid + 1, r]$ 的贡献。

先考虑 $b_p > d_i$，则 $b$ 更大的岛屿会对 $d$ 更小的询问产生贡献，因此区间内部按照有趣度从大到小排序。若左区间当前位置 $pl$ 有趣度更大，则加入左区间当前位置，并令 $pl$ 向后移一单位，否则对于 $pr$ 同理。注意 $b_p > d_i$，所以有趣度相同时优先右区间。

- 如果加入的左区间位置上是一个岛屿，则将岛屿加入集合 $S$；否则是一次询问，忽略掉它。
- 如果加入的右区间位置上是一个岛屿，则忽略掉它；否则是一次询问，形如给定 $c, d$，查询 $S$ 当中 $a\oplus c \leq d$ 的 $a$ 的数量。

学过 01 字典树的同学可以感性理解，使得与 $a$ 异或起来不大于 $d$ 的所有 $c$ 可以用 01 字典树上 $\mathcal{O}(\log V)$ 个子树描述。

设 $d$ 在二进制表示下第 $x_1 > x_2 > \cdots > x_k$ 位是 $1$，令 $s_i$ 为 $2 ^ {x_i}$ 关于 $i$ 的前缀和，则使得与 $a$ 异或起来恰等于 $[s_i, s_{i + 1})$ 的 $c$ 恰好是第 $x_i$ 位以及比 $x_i$ 高的位上恰好等于 $a\oplus d$ 的第 $x_{i + 1}$ 位及其高位，且低 $x_{i + 1} - 1$ 位可以任取，因为 $[s_i, s_{i + 1})$ 的第 $x_{i + 1}$ 位及其高位恰好等于 $s_i$ 的第 $x_{i + 1}$ 位及其高位，且低 $x_{i + 1} - 1$ 位取遍了 $0\sim 2 ^ {x_{i + 1}} - 1$。

这个结论有点意识流，但是只要想通了就很简单。你也可以理解为线段树上一个区间的拆分区间只有 $\mathcal{O}(\log n)$ 个，尽管它们俩本质不太相同，但可以类比一下。

如下图，绿色点是 01 字典树插入 $a\oplus d$ 时形成的路径，**与路径相连** 的黄色点子树被打上标记，红色点子树未被打上标记，注意路径结尾的绿点应当被打上标记。所有黄点子树内所有节点和路径结尾的绿点即为所有与 $a$ 异或起来 $\leq d$ 的值对应的节点。

![](https://cdn.luogu.com.cn/upload/image_hosting/gyz8933u.png)

那我们考虑如何在 01 字典树上定位这些区间。考虑向 01 字典树插入 $a \oplus d$，设当前位为 $B$，当前节点为 $x$，$a \oplus d$ 的第 $B$ 位为 $A$：

- 若 $d$ 的第 $B$ 位为 $1$，说明 $x$ 父节点的另一个儿子子树均合法，因为其对应的节点 **异或 $a$ 之后** 在第 $x + 1$ 位及其高位均与 $d$ 的第 $x + 1$ 位及其高位相同，但第 $x$ 位为 $0$，而 $d$ 的第 $x$ 位为 $1$，所以异或值必然不大于 $d$。
- 若 $d$ 的第 $B$ 位为 $0$，啥事也不用干。

子树打标记的话直接标记永久化，查询时只要查 01 字典树上查找 $c$ 时经过所有节点的标记之和即可。视 $n, q$ 同级，因为进行 $\mathcal{O}(n\log n)$ 次插入操作，所以总时间复杂度为 $\mathcal{O}(n\log n\log V)$，空间复杂度 $\mathcal{O}(n\log V)$。

再考虑 $b_p \leq d_i$，发现几乎是对称的，有趣度从大到小变成了从小到大，有趣度相同时优先右区间变成了优先左区间。01 字典树插入变成了单点插入，查询变成了子树查询，所以 01 字典树上每个节点维护的信息从懒标记值变成了子树的数的个数之和。当然你也可以将询问和区间反转得到同样效果，但注意特判 $b_p = d_i$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int K = N << 6;
const int W = 24;
int n, q, cnt, ans[N];
int a[N], b[N], c[N], d[N];
vector<int> buc[N];
struct event {
  int a, b, id;
  bool operator < (const event &v) const {return b != v.b ? b < v.b : id < v.id;}
} e[N * 3], f[N * 3]; // 注意这里要 * 3 =.=
struct Trie {
  int R, node, son[K][2], val[K];
  void tag(int &x, int v) {if(!x) x = ++node; val[x] += v;}
  void insert1(int pos, int &x, int p, int lim, int v) {
    // 当前是第 pos 位，插入的值为 p，需要限制 xor <= lim，delta val = v、
    // 这里的 val 是子树加的 tag，标记永久化
    if(!x) x = ++node;
    if(!pos) return val[x] += v, void(); // 递归到叶子，合法，需要加 v
    int bit = p >> pos - 1 & 1;
    if(lim >> pos - 1 & 1) {
      if(!son[x][bit]) son[x][bit] = ++node;
      val[son[x][bit]] += v;
      insert1(pos - 1, son[x][bit ^ 1], p, lim, v);
    }
    else insert1(pos - 1, son[x][bit], p, lim, v);
  }
  int query1(int pos, int x, int p) {
    if(!x || !pos) return val[x];
    // cerr << "query1 " << x << " " << val[x] << " " << son[x][0] << endl;
    return val[x] + query1(pos - 1, son[x][p >> pos - 1 & 1], p);
  }
  void insert2(int pos, int &x, int p, int v) {
    if(!x) x = ++node;
    val[x] += v;
    if(!pos) return;
    insert2(pos - 1, son[x][p >> pos - 1 & 1], p, v);
  }
  int query2(int pos, int x, int p, int lim) {
    if(!x || !pos) return val[x];
    int bit = p >> pos - 1 & 1;
    if(lim >> pos - 1 & 1) {
      int ans = query2(pos - 1, son[x][bit ^ 1], p, lim);
      return ans + val[son[x][bit]];
    }
    return query2(pos - 1, son[x][bit], p, lim);
  }
  void clear() {
    for(int i = 0; i <= node; i++) son[i][0] = son[i][1] = val[i] = 0;
    node = R = 0; // 注意 R 也要清空
  }
} tr;
void solve(int l, int r, int type) {
  if(l == r) return f[l] = e[l], void();
  int m = l + r >> 1;
  solve(l, m, type), solve(m + 1, r, type);
  int pl = l, pr = m + 1, p = l;
  static event g[N * 3];
  // cerr << "solve " << l << " " << r << endl;
  auto moveL = [&]() {
    if(f[pl].id == -N) {
      // cerr << "addL " << f[pl].a << " " << f[pl].b << " " << f[pl].id << endl;
      if(type == 1) tr.insert1(W, tr.R, f[pl].a, f[pl].b, 1);
      else tr.insert2(W, tr.R, f[pl].a, 1);
    }
    g[p++] = f[pl++];
  };
  auto moveR = [&]() {
    if(f[pr].id != -N) {
      int id = abs(f[pr].id), sgn = f[pr].id / id;
      // cerr << "queryR " << id << " " << sgn << " " << c[id] << endl;
      if(type == 1) ans[id] += tr.query1(W, tr.R, c[id]) * sgn;
      else ans[id] += tr.query2(W, tr.R, c[id], d[id]) * sgn;
      // cerr << "res " << ans[id] << endl;
    }
    g[p++] = f[pr++];
  };
  while(pl <= m && pr <= r) {
    if(type == 1 ? f[pl] < f[pr] : f[pr] < f[pl]) moveL();
    else moveR();
  }
  while(pr <= r) moveR();
  for(int i = pl; i <= m; i++) g[p++] = f[i];
  for(int i = l; i <= r; i++) f[i] = g[i];
  tr.clear();
}
int main() {
  // freopen("1.in", "r", stdin);
  cin >> n >> q;
  for(int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]);
  for(int i = 1; i <= q; i++) {
    int l, r;
    scanf("%d%d%d%d", &l, &r, &c[i], &d[i]);
    if(l > 1) buc[l - 1].push_back(-i);
    buc[r].push_back(i);
  }
  for(int i = 1; i <= n; i++) {
    e[++cnt] = {a[i], b[i], -N};
    for(int it : buc[i]) e[++cnt] = {c[abs(it)], d[abs(it)], it}; 
  }
  // for(int i = 1; i <= cnt; i++) cerr << "dat " << i << " " << e[i].a << " " << e[i].b << " " << e[i].id << endl;
  solve(1, cnt, 1);
  solve(1, cnt, 2);
  for(int i = 1; i <= q; i++) printf("%d\n", ans[i]);
  return cerr << "Time: " << clock() << endl, 0;
}
/*
2022/5/21
start thinking at
二维数点问题。
cdq 分治。
外层是下标，内层是有趣度。
写出了好多 bug，像个蠢蛋。
start coding at 8:29
finish debugging at 9:40
*/
```

---

## 作者：Y_B_X (赞：1)

[原题链接](https://www.luogu.com.cn/problem/P7470)

>题意  
给出一个序列 $a_{1\dots n},b_{1\dots n}$，  
每次查询给出一段区间 $l,r$ 以及两个数 $c,d$，  
问区间 $[l,r]$ 内有多少个数满足 $a_i\operatorname{xor}c\leq \min(b_i,d)$。

太久没写 $\text{cdq}$ 竟还能这么快过掉。

首先，由于询问可加性，区间的限制可以拆为两个 $[1,t]$ 的查询。

于是这就可以以位置为第一维进行 $\text{cdq}$ 分治了。

然后为了方便地拆掉 $\min(b_i,d)$，可以将 $\geq d$ 的 $b_i$ 与 $< d$ 的，分开统计。

先是 $b_i\geq d$ 的 $i$ ，此时有 $a_i\operatorname{xor}c\leq d$。这是 $\text{01trie}$ 的经典运用。将所有 $a_i$ 插到 $\text{01trie}$ 上。查询时在 $\text{01trie}$ 上按着一条 $c\operatorname{xor}s=d$ 的链 $s$ ，这使得前几位 $\operatorname{xor}c$  后与 $d$ 相同。如果这一位上 $d$ 为 $1$，则累加上使这一位 $\operatorname{xor}c=0$ 的数的个数，跳到叶子节点的数的个数同样要算上，此时 $\operatorname{xor}c=d$。

而对于 $b_i<d$ 的 $i$，有 $a_i\operatorname{xor}c\leq b_i$。考虑将能使 $a_i\operatorname{xor}c\leq b_i$ 的 $c$ 处打上 $+1$ 的标记。维护一条使 $s\operatorname{xor}a_i=b_i$ 的链  $s$，如果这一位上 $b_i$ 为 $1$，将 $\operatorname{xor}a_i$ 后这一位为 $0$ 的子树打上 $+1$ 的标记，跳到的叶子节点同样要打上 $+1$ 的标记。查询时按着 $c$ 从根开始一路累加被加上的标记和即可。

时间复杂度为 $O(n\log n\log V)$，$\text{cdq}$ 与 $\text{01trie}$ 各带一个 $\log$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10,K=24;
int n,m,x,y,l,r,a,b,tot,t_tot,rt,tmp;
int res[N];bool bx,bw;char ch;
inline void read(int &x){
	x=0;ch=getchar();while(ch<48)ch=getchar();
	while(ch>47)x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
}
void write(int x){if(x>9)write(x/10);putchar(48+x%10);}
struct cdq{
	int i,a,b,id;char opt;cdq()=default;//opt=0:mdf otherwise:inq
	cdq(int _i,int _a,int _b,char _opt=0,int _id=0)
		:i(_i),a(_a),b(_b),opt(_opt),id(_id){}
}q[N],q0[N],qq[N],qq0[N];//min=d for q ; min=b for qq
bool cmpi(cdq x,cdq y){return x.i^y.i?x.i<y.i:!x.opt;}
bool cmpq(cdq x,cdq y){return x.b^y.b?x.b>y.b:!x.opt;}
bool cmpqq(cdq x,cdq y){return x.b^y.b?x.b<y.b:x.opt;}
struct trie01{int son[2],tag[2],sz;}t[N*(K+1)];
void update(int &k,int x,int i,int v){
	if(!k)k=++t_tot;t[k].sz+=v;
	if(~i)update(t[k].son[(x>>i)&1],x,i-1,v);
}
void update(int &k,int x,int w,int i,int v){
	if(!k)k=++t_tot;
	bw=(w>>i)&1;bx=bw^((x>>i)&1);
	if(~i){
		if(bw)t[k].tag[!bx]+=v;
		update(t[k].son[bx],x,w,i-1,v);
	}
	else t[k].tag[0]+=v;
}
void inquiry(int k,int x,int w,int i){
	if(~i){
		bw=(w>>i)&1;bx=bw^((x>>i)&1);
		if(bw)tmp+=t[t[k].son[!bx]].sz;
		inquiry(t[k].son[bx],x,w,i-1);
	}
	else tmp+=t[k].sz;
}
void inquiry(int k,int x,int i){
	if(~i){
		bx=(x>>i)&1;tmp+=t[k].tag[bx];
		inquiry(t[k].son[bx],x,i-1);
	}
	else tmp+=t[k].tag[0];	
}
void solve(int l,int r){
	if(l^r){
		int mid=(l+r)>>1,i;
		solve(l,mid);solve(mid+1,r);
		merge(q+l,q+mid+1,q+mid+1,q+r+1,q0+l,cmpq);
		merge(qq+l,qq+mid+1,qq+mid+1,qq+r+1,qq0+l,cmpqq);
		for(i=l;i<=r;++i)q[i]=q0[i],qq[i]=qq0[i];
		for(i=l;i<=r;++i){
			if(q[i].i<=mid&&!q[i].opt)update(rt,q[i].a,K,1);
			else if(q[i].i>mid&&q[i].opt){
				tmp=0;inquiry(rt,q[i].a,q[i].b,K);
				res[q[i].id]+=tmp*q[i].opt;
			}
		}
		for(i=l;i<=r;++i)if(q[i].i<=mid&&!q[i].opt)update(rt,q[i].a,K,-1);
		for(i=l;i<=r;++i){
			if(qq[i].i<=mid&&!qq[i].opt)update(rt,qq[i].a,qq[i].b,K,1);
			else if(qq[i].i>mid&&qq[i].opt){
				tmp=0;inquiry(rt,qq[i].a,K);
				res[qq[i].id]+=tmp*qq[i].opt;
			}
		}
		for(i=l;i<=r;++i)if(qq[i].i<=mid&&!qq[i].opt)update(rt,qq[i].a,qq[i].b,K,-1);
	}
}
main(){
	read(n);read(m);register int i;
	for(i=1;i<=n;++i)read(a),read(b),q[++tot]=cdq(i,a,b);
	for(i=1;i<=m;++i){
		read(l),read(r),read(a),read(b);
		q[++tot]=cdq(r,a,b,1,i);
		if(l>1)q[++tot]=cdq(l-1,a,b,-1,i);
	}
	sort(q+1,q+tot+1,cmpi);
	for(i=1;i<=tot;++i)q[i].i=i;
	for(i=1;i<=tot;++i)qq[i]=q[i];
	solve(1,tot);
	for(i=1;i<=m;++i)write(res[i]),putchar('\n');
}
```


---

## 作者：xxxxxzy (赞：0)

首先考虑全局的查询该怎么做。

把数对按 $b_i$ 升序排序，询问按 $d_i$ 升序排序。

对于一个 $d$ 数对可以划为两类，一类 $b_i > d$，另一类反之，而且随着 $d$ 从小变大，这个分界的指针是单向移动的。

接下来分类处理：

第一个集合查询 $a_i \oplus c \le d$ 的个数，这个方便用 Trie 解决。

第二个集合查询 $a_i \oplus c \le b_i$ 的个数，这个跟第一个集合的维护方法是类似的，或者说某种意义上对偶的。

答案可以拆开，然后区间版本弄上去一个线段树分治。

时间 $O(n \log n \log V)$，空间 $O(n \log V)$。

---

