# Deduction Queries

## 题目描述

有一个长度为 $2^{30}$ 的整数数组 $a$，下标从 $0$ 到 $2^{30}-1$。最初，你只知道 $0 \leq a_i < 2^{30}$（$0 \leq i < 2^{30}$），但你并不知道数组中的具体数值。你的任务是处理两种类型的查询：

- 1 l r x：你被告知子数组 $[l, r]$（包含两端）按位异或的结果等于 $x$。即 $a_l \oplus a_{l+1} \oplus \ldots \oplus a_{r-1} \oplus a_r = x$，其中 $\oplus$ 表示按位异或操作。如果本次更新与之前的更新矛盾，则应忽略本次（当前）更新。
- 2 l r：你需要输出子数组 $[l, r]$（包含两端）按位异或的结果。如果根据所有已知信息仍无法确定该值，则输出 $-1$。

注意，所有查询都是经过编码的。你需要编写一个在线算法来处理这些查询。

## 说明/提示

在第一个样例中，真实的（未编码的）查询如下：

- 12
- 2 1 2
- 2 0 1073741823
- 1 1 2 5
- 2 1 1
- 2 2 2
- 2 1 2
- 1 2 3 6
- 2 1 1
- 1 1 3 0
- 2 1 1
- 2 2 2
- 2 3 3

- 前两次查询的答案都是 $-1$，因为我们最初对数组没有任何信息。
- 第一次更新告诉我们 $a_1 \oplus a_2 = 5$。注意我们仍无法单独确定 $a_1$ 或 $a_2$ 的值（例如，$a_1 = 1, a_2 = 4$，也可以 $a_1 = 3, a_2 = 6$）。
- 在收到所有三次更新后，我们有足够的信息独立推断出 $a_1, a_2, a_3$ 的值。

在第二个样例中，注意在前两次更新后我们已经知道 $a_5 \oplus a_6 = 12$，所以第三次更新与之前的信息矛盾，应予以忽略。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
12
2 1 2
2 1 1073741822
1 0 3 4
2 0 0
2 3 3
2 0 3
1 6 7 3
2 4 4
1 0 2 1
2 0 0
2 4 4
2 0 0
```

### 输出

```
-1
-1
-1
-1
5
-1
6
3
5
```

## 样例 #2

### 输入

```
4
1 5 5 9
1 6 6 5
1 6 5 10
2 6 5
```

### 输出

```
12
```

# 题解

## 作者：reyik (赞：8)

这题其实不难，建议评成紫题。

考虑并查集

对于修改，对于两个端点$l$,$r$,判断是否在一个集中，没有就合并，同时把对应值改成$x$^$num[l]$^$num[r]$

注意不是$x$^$num[find(l)]$^$num[find(r)]$

然后查询差不多

不再同一个集合显然-1

否则答案为$num[l]$^$num[r]$

并查集的时候，做一个类似下推标记的东西，就是让当前的$num[x]$异或一下$num[father[x]]$

这时我们发现 $l,r \le 2e30$ 直接存肯定不行了

但我们有map每一个map对应一个出现过的端点，端点数不超过$q*2$

然后我们就做完了 QAQ

代码:

```cpp

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>
using namespace std;
map<int,int> father , num;
int n,l,r,x,lst=0,q,opt;
int find_(int x) {
	if(!father.count(x)) return x;
	int tmp=find_(father[x]);
	num[x]^=num[father[x]];
	father[x]=tmp;
	return father[x];
}
inline int read() {
	register int x=0,w=1;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	if(ch=='-') w=-1;
	while(isdigit(ch)) x=((x<<3)+(x<<1))+ch-'0',ch=getchar();
	return x*w;
}
int main() {
	q=read();
	while(q--) {
		opt=read();
		if(opt==1) {
			l=read();r=read();x=read();
			l^=lst,r^=lst,x^=lst;
			if(l>r) swap(l,r);
			--l;
			int xf=find_(l),yf=find_(r);
			if(xf!=yf) {
				father[yf]=xf;
				num[yf]=x^num[l]^num[r];
			}
		}
		else {
			l=read();r=read();
			l^=lst;r^=lst;
			if(l>r) swap(l,r);
			--l;
			int xf=find_(l),yf=find_(r);
			if(xf!=yf) {
				lst=1;
				puts("-1");
			}
			else {
				lst=num[l]^num[r];
				printf("%d\n",lst);
			}
		}
	}
	return 0;
} 
```

---

## 作者：良知 (赞：5)

这题。。都是套路啊(~~Doushitao Road~~)

有两种操作

1、opt==1

给出参数l, r, x, 要求使[l, r]这个区间内的xor为x

有一点要注意的是

```
(notice that you need to ignore updates that
contradict previous updates).
```

根据~~百度翻译~~可以得知你需要忽略和上次矛盾的更新

那么有什么东西可以维护某个矛盾信息呢？

**带权并查集！**(套路)

首先先明确一点，就是同一个区间如果更新不止一次，那么第二次及以后的更新就没有意义了（理由是要么和第一次一样，要么就矛盾了）(套路)

那么可以构造这样的一个并查集：对于节点l, r, 找到l的最上层祖先和r的最上层祖先，如果相同就直接结束。为了更好的建立联系，首先把r+1(统统加一，有点像物理里面的转化参考系哈哈)：
```
inline int getans(int l, int r){
    ++r;
    l=mp[l];
	r=mp[r];//C++ STL中的映射，在这里用来记录更新区间端点对应的编号(有点难理解)
    if(l==0||r==0||(find(l)^find(r)))return -1;//如果压根儿不存在或者是已经更新过了返回-1
    return xorsum(l)^xorsum(r);//找答案
}
```
xorsum如何实现呢？

定义xr数组为对应编号的值xor他的父亲

那么根据这个定义就有如下代码：
```
inline int xorsum(int x){
    if(asis[x]==x)return 0;//找到根节点了
    return xr[x]^xorsum(asis[x]);//返回它异或上他父亲再异或到根节点位置。根据x^x=0性质可得
}
```
解决了2的大部分操作(不要问我find函数在哪里，应该都会了吧)，1操作就很简单了，不就是最最普通的带权并查集嘛？

给出部分代码：

**带权**并查集合并：
```
inline void Union(int l, int r, int tmp){
    int rootx=find(mp[l]),rooty=find(mp[r]);
    if(!(rootx^rooty)) return;//如果相等不合并
    tmp=xorsum(mp[l])^xorsum(mp[r])^tmp;//记录tmp，维护上文xr，也就是权值
    if(multip[rootx]>multip[rooty]) swap(rootx, rooty);//可以认为multip就是并查集的秩，按秩合并
    asis[rootx]=rooty;//父亲
    multip[rooty]+=multip[rootx];//multip更新
    xr[rootx]=tmp;//权值更新
}
```

面对一操作，只需要更新上面提到的映射之后再Union即可。

不要忘记更新last，这题目就顺利做完了！

---

## 作者：tybbs (赞：4)

技巧一：一个式子：记 $W\left(l,r\right)=a_l\oplus a_{l+1}\oplus a_{l+2}\oplus\ldots\oplus a_{r-1}$


有 $\forall a,b,c\ \ W\left(a,c\right)=W\left(a,b\right)\oplus W\left(b,c\right)$


证明分情况讨论即可。

技巧二：图论建模。条件 $W\left(l,r\right)$ 表示为 $l,r$ 间一条权值为 $W\left(l,r\right)$ 的边。

求 $W\left(l,r\right)$ 转化为求图上 $l,r$ 见的一条路径上所有边的的权值的异或和。



技巧三：带权并查集。显然的，由于 $W\left(l,r\right)$ 的值是一定的且唯一的，可见 $\forall a,b\ a,b$ 之间至多有一条路径，即任意时刻的图都为一个**森林**。由一中提到的式子，可用**带权并查集**解决。

维护每一个a在森林中的祖先和a到其祖先的路径上所有边的异或和，记为 ${\rm fa}_a\ ,\ val_a$ 得到以下求 $W\left(l,r\right)$ 的办法：若 $fa_l\neq fa_r$ 即 $l,r$ 的祖先不同，则 $l,r$ 不连通，有 $W\left(l,r\right)$ 不确定。否则 $W\left(l,r\right)=W\left(l,fa\right)\oplus W\left(r,fa\right)=val_l\oplus val_r$。

参考代码：

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
map<int,int>fa,val;
int find(int x){
	if(!fa.count(x)) return x;
	int nfa=find(fa[x]);
	val[x]^=val[fa[x]],fa[x]=nfa;
	return nfa;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int q,lst=0;cin>>q;
	while(q--){
		int op;cin>>op;
		switch(op){
			case 1:{
				int l,r,x;cin>>l>>r>>x;
				l^=lst,r^=lst,x^=lst;
				if(l>r) swap(l,r);
				l--;
				int fl=find(l),fr=find(r);
				if(fl!=fr){					
					fa[fl]=fr;
					val[fl]=val[l]^val[r]^x;
				}
				break;
			}
			case 2:{
				int l,r;cin>>l>>r;
				l^=lst,r^=lst;
				if(l>r) swap(l,r);
				l--;
				int fl=find(l),fr=find(r);
				if(fl!=fr){
					cout<<-1<<"\n";
					lst=1;
				}
				else{
					lst=val[l]^val[r];
					cout<<lst<<"\n";
				}
				break;
			}
		}
	}
} 
```


---

## 作者：Hoks (赞：3)

## 前言
带 LCT 玩的都是好人！

有关这题要用到的 LCT 相关知识可以见[树剖博客](https://www.luogu.com.cn/blog/Hok/cute-tree-decomposition)中的 $6.4.1$。

duel 到的喜加一。
## 思路分析
首先这题先考虑建模成图论。

$l\rightarrow r$ 的异或和即为：$a_l\oplus a_{l+1}\dots \oplus a_r$。

但是因为是一段连续的异或值，所以我们能知道的异或值只有 $l\rightarrow r$ 这一段。

也就是 $a_l,a_l+1,\dots,a_r$ 中任何一个的值我们都无法知晓。

所以我们考虑抽象到图上即为：$l\rightarrow r$ 连一条边权为 $w$ 的边。

考虑到 $l,r$ 可能相等，所以处理的时候 $r+1$ 即可。

接着的询问就成了询问 $l,r+1$ 这两个点间的路径异或和。

建模建完了，考虑用什么 DS。

发现建模后的图形态是一颗森林，而且要支持加边，直接想到 LCT。

但是 LCT 不方便维护边权，所以直接拆出新的点，然后对这个点附点权为边权前后连边即可。

对于 $l,r$ 太大的情况，直接考虑套层 map 映射一下即可。

数组记得开到 $60000$。
## 代码
```cpp
#include <bits/stdc++.h>
#define ls son[x][0]
#define rs son[x][1]
#define fi first
#define se second
#define int long long
using namespace std;
const int N=4e5+10,INF=0x3f3f3f3f3f3f3f3f;
int q;
int n,m,tot,cnt,ans;
int f[N],s[N],son[N][2],st[N],w[N],r[N];
map<int,int>mp;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void print(int x)
    {
        if(x<0) putchar('-'),x=-x;
        if(x>9) print(x/10);
        putchar(x%10+'0');
    }
}
using namespace Fast_IO;
bool ntrt(int x){return son[f[x]][1]==x||son[f[x]][0]==x;}
void pushup(int x){s[x]=s[ls]^s[rs]^w[x];}
void pushson(int x){swap(ls,rs),r[x]^=1;}
void pushdown(int x)
{
    if(r[x])
    {
        if(ls) pushson(ls);
        if(rs) pushson(rs);
        r[x]=0;
    }
}
void rotate(int x)
{
    int y=f[x],z=f[y],k=(son[y][1]==x),w=son[x][!k];
    if(ntrt(y)) son[z][son[z][1]==y]=x;son[x][!k]=y;son[y][k]=w;
    if(w) f[w]=y;f[y]=x;f[x]=z;
    pushup(y);
}
void Splay(int x)
{
    int y=x,tot=0;st[++tot]=y;
    while(ntrt(y)) st[++tot]=y=f[y];
    while(tot) pushdown(st[tot--]);
    while(ntrt(x))
    {
        y=f[x];int z=f[y];
        if(ntrt(y)) rotate((son[y][0]==x)^(son[z][0]==y)?x:y);
        rotate(x);
    }
    pushup(x);
}
void access(int x){for(int y=0;x;x=f[y=x]) Splay(x),rs=y,pushup(x);}
void makert(int x){access(x);Splay(x);pushson(x);}
int findrt(int x)
{
    access(x);Splay(x);
    while(ls) pushdown(x),x=ls;
    Splay(x);return x;
}
void split(int x,int y){makert(x);access(y);Splay(y);}
void link(int x,int y){makert(x);if(findrt(y)!=x)f[x]=y,pushup(y);}
signed main()
{
    q=read();
    for(int i=1,op,l,r;i<=q;i++)
    {
        op=read(),l=read()^ans,r=read()^ans;
        if(l>r) swap(l,r);r++;
        if(op==1)
        {
            if(!mp[l]) mp[l]=++cnt;l=mp[l];
            if(!mp[r]) mp[r]=++cnt;r=mp[r];
            if(findrt(l)==findrt(r)){read();continue;}
            tot++,w[2*q+tot]=read()^ans,link(l,2*q+tot),link(r,2*q+tot);
        }
        else
        {
            if(!mp[l]||!mp[r]){ans=1;puts("-1");continue;}
            l=mp[l],r=mp[r];
            if(findrt(l)!=findrt(r)){ans=1;puts("-1");continue;}
            split(l,r);ans=s[r];print(ans);puts("");
        }
    }
    return 0;
}
```

---

## 作者：nynkqh_yzp (赞：2)

大佬们都一眼看出了带权并查集，但我想了好久。
# 题意
给你 $q$ 个操作，告诉你一个区间的异或和或问你一个区间的异或和，强制在线。
# 做法
先想我们人是怎么完成这个任务的。

令 $f_{l,r}$ 表示 $a_l\oplus a_{l+1}\oplus a_{l+1}\oplus⋯\oplus a_{r-1}$。

那么 $f_{l,r}= f_{l,k}\oplus f_{k,r}$。

也就是说可以把 $f_{l,r}$ 理解为 $l$ 和 $r$ 之间的距离。

所以我们可以考虑使用带权并查集处理每个点到它在并查集上的父亲的距离，加上路径压缩就约等于到根的距离。

这样每个 $1$ 操作，就是合并点 $l$ 和 $r+1$，每个 $2$ 操作，就是查询点 $l$ 和 $r+1$ 之间的距离，$-1$ 的情况就相当于两个点不在同一棵树中。

因为定义的的 $f_{l,r}$ 没有算 $a_r$ 所以是点 $r+1$。

直接开数组处理并查集是开不下的，由于一共最多只会 $2\times q$ 个点，所以需要离散化。但是这个题强制在线，所以可以用 `map` 或者 `unordered_map` 来映射。

```cpp
#include<bits/stdc++.h> 
using namespace std;
int q,f[400001],s[400001],cnt,y,la;
unordered_map<int,int>mq;
int zbb(int x){
	if(f[x]==x)
		return x;
	y=zbb(f[x]);
	s[x]=s[f[x]]^s[x];
	f[x]=y;
	return y;
}
int main(){
	scanf("%d",&q);
	while(q--){
		int k,l,r,x;
		scanf("%d%d%d",&k,&l,&r);
		l^=la,r^=la;
		if(l>r)
			swap(l,r);
		r++;
		if(mq[l]==0)
			mq[l]=++cnt,f[cnt]=cnt;
		if(mq[r]==0)
			mq[r]=++cnt,f[cnt]=cnt;
		l=mq[l];
		r=mq[r];
		if(k==1){
			scanf("%d",&x);
			x^=la;
			int ll=zbb(l),rr=zbb(r);
			if(ll!=rr){
				s[ll]=s[l]^s[r]^x;
				f[ll]=rr;
			}
		}
		else{
			if(zbb(l)==zbb(r))
				printf("%d\n",la=s[l]^s[r]);
			else
				printf("-1\n"),la=1;
		}
	}
	return 0;
}
```


---

## 作者：Hooch (赞：2)

### 题目大意

有一个序列 $a$，最开始你不知道 $a$ 长什么样子。

有 $q$ 个操作，每个操作有两种类型：

+ 类型 $1$，告诉你 $a_{l} \oplus a_{l + 1} \oplus \cdots \oplus a_r = x$。

+ 类型 $2$，询问 $a_l \oplus a_{l + 1} \oplus \cdots \oplus a_r$，如果不知道就输出 $-1$。

操作强制在线。

### 题解

~~题解区一片带权并查集，可是我不会，就只能用 LCT 了。~~

看到区间异或和，先想到把 $a_l \oplus a_{l + 1} \oplus \cdots \oplus a_r$ 变成 $s_{l - 1} \oplus s_r$，其中 $s_i = a_1 \oplus a_2 \oplus \cdots \oplus a_i$。

然后考虑图论，修改时，将 $l - 1$ 与 $r$ 连一条边权为 $x$ 的边，查询时，只需查询 $(l - 1) \to r$  的路径异或和。

这个问题可以用 LCT 解决。虽然 $l - 1$ 和 $r$ 很大（值域是 $[0, 2^{30})$ ），但是可以发现有用的 $l - 1$ 和 $r$ 最多只有 $2q$ 个，用 map 记录一下在 LCT 上的编号即可。

LCT 维护边权（例如在 $u$ 和 $v$ 之间连一条边权为 $w$ 的边），可以新建一个点（假设是 $p$），将点 $p$ 的点权赋成 $w$，点 $u, v$ 的点权赋成 $0$，再连接 $(u, p)$ 和 $(v, p)$ 即可。

时间复杂度 $O(n \log n)$。

代码：

```cpp
#include <bits/stdc++.h>
#define dbg cout << "-----------------------\n"
using namespace std;
using i64 = long long;
void debug() {
  cerr << '\n';
}
template <typename T, typename ...L>
void debug(T x, L ...y) {
  cerr << x << ' ';
  debug(y...);
}
const int N = 8E5 + 5;
int q, tot, cnt;
map <int, int> vis;
int son[N][2], sum[N], val[N], fa[N], rev[N];
bool checkson(int x) {return son[fa[x]][1] == x;}
bool checkroot(int x) {return son[fa[x]][0] != x && son[fa[x]][1] != x;}
void pushup(int x) {
  sum[x] = sum[son[x][0]] ^ sum[son[x][1]] ^ val[x];
}
int newnode(int v) {
  ++tot; son[tot][0] = son[tot][1] = 0;
  sum[tot] = val[tot] = v; fa[tot] = rev[tot] = 0;
  return tot;
}
void rotate(int x) {
  int y = fa[x], z = fa[y], chx = checkson(x), chy = checkson(y);
  if (!checkroot(y)) son[z][chy] = x; fa[x] = z;
  son[y][chx] = son[x][!chx]; fa[son[x][!chx]] = y;
  son[x][!chx] = y; fa[y] = x;
  pushup(x); pushup(y);
}
void pushdown(int x) {
  if (rev[x]) {
    auto update = [&](int x) {
      if (!x) return ;
      swap(son[x][0], son[x][1]);
      rev[x] ^= 1;
    } ;
    update(son[x][0]); update(son[x][1]);
    rev[x] = 0;
  }
}
void update(int x) {if (!checkroot(x)) update(fa[x]); pushdown(x);}
void splay(int x) {
  update(x);
  while (!checkroot(x)) {
    if (!checkroot(fa[x])) rotate(checkson(x) != checkson(fa[x]) ? x : fa[x]);
    rotate(x);
  } pushup(x);
}
void access(int x) {
  for (int y = 0; x; y = x, x = fa[x]) {
    splay(x); son[x][1] = y; pushup(x);
  }
}
void makeroot(int x) {
  access(x); splay(x); 
  rev[x] ^= 1;
  swap(son[x][0], son[x][1]);
}
int findroot(int x) {
  access(x); splay(x); pushdown(x);
  while (son[x][0]) {
    x = son[x][0];
    pushdown(x);
  }
  return splay(x), x;
}
void split(int x, int y) {
  makeroot(x);
  access(y); splay(y);
}
void link(int x, int y) {
  makeroot(x);
  if (findroot(x) != findroot(y)) {
    fa[x] = y;
    pushup(y);
  }
}
int query(int x, int y) {
  split(x, y);
  return sum[y];
}
signed main(void) {
  ios :: sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);
  cin >> q;
  int ans = 0;
  for (int _ = 1; _ <= q; ++_) {
    int opt; cin >> opt;
    int a, b; cin >> a >> b;
    a ^= ans; b ^= ans;
    if (a > b) swap(a, b);
    ++b;
    if (opt == 1) {
      int x; cin >> x;
      x ^= ans;
      int ida, idb;
      if (!vis.count(a)) ida = ++tot, val[idb] = 0;
      else ida = vis[a];
      if (!vis.count(b)) idb = ++tot, val[ida] = 0;
      else idb = vis[b];
      vis[a] = ida; vis[b] = idb;
      if (findroot(ida) == findroot(idb)) continue;
      ++tot;
      val[tot] = x;
      link(ida, tot); link(idb, tot);
    } else {
      if (!vis.count(a) || !vis.count(b)) {
        ans = 1;
        cout << -1 << '\n';
      } else {
        int ida = vis[a], idb = vis[b];
        if (findroot(ida) != findroot(idb)) {
          ans = 1;
          cout << -1 << '\n';
        } else cout << (ans = query(ida, idb)) << '\n';
      }
    }
  }
}
```

---

## 作者：DrAlfred (赞：1)

摘要：种类并查集

[传送门：https://www.luogu.com.cn/problem/CF1044D](https://www.luogu.com.cn/problem/CF1044D)

## 题意

有一个长度为 $2^{30}$ 的数列 $a_0, a_1, \dots, a_n$。初始并不知道它们分别是多少。给定 $q$ 次操作，每次操作分为以下两种类型：

- `1 l r x` 表示已经知道了 $a_l \oplus a_{l + 1} \oplus \dots \oplus a_r = x$，若与之前某条件冲突则忽略该条件；
- `2 l r` 询问 $a_l \oplus a_{l + 1} \oplus \dots \oplus a_r$，若无法确定输出 `-1`。

## 分析思路

下文记 $x_d$ 为 $x$ 在二进制表示下的第 $d$ 位。

首先，我们设原数组的异或前缀和为 $s_i = a_0 \oplus a_1 \oplus \dots \oplus a_i$。对于操作一，我们知道 $s_r \oplus s_{l - 1} = x$。考虑对 $x$ 进行拆位，依据异或运算的定义，当 ${s_r}_d \neq {s_{l-1}}_{d}$ 时，$x_d = 1$，否则 $x_d = 0$。于是每个操作一就转化为了动态得知某两个变量相等或不相等，判断是否冲突——即种类并查集解决的基本问题。所以，我们对于每一位开一个种类并查集，即可支持操作一的判断冲突。

那么如何支持操作 $2$ 呢？注意到我们之前使用的关于异或的性质是充要的。也就是说，如果我们枚举每一位 $d$，若可以**确定** ${s_r}_d \neq {s_{l-1}}_{d}$ 或 ${s_r}_d ={s_{l-1}}_{d}$，则第 $d$ 位对答案的贡献是确定的。最终答案即为 $\sum_{d = 0}^{29} [{s_r}_d \neq {s_{l-1}}_{d}] \times 2^d$。否则，如果相等或不相等都不能确定，则答案为 $-1$。

最后的小细节就是数组下标过大，注意到最多只有 $2q$ 个不同的下标，所以我们可以使用 `std::map` 动态进行离散化。使用按秩合并的并查集，时间复杂度 $O\left(q \log V \right)$，其中 $V$ 为值域大小，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 400010;
struct DSU {
    std::vector<int> fa, siz;
    DSU(int n) : fa(n + 1), siz(n + 1, 1) {
        std::iota(fa.begin(), fa.end(), 0);
    }
    inline int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    // true if x and y were not in the same set, false otherwise.
    inline bool merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return false;
        if (siz[fx] < siz[fy]) swap(fx, fy);
        fa[fy] = fx, siz[fx] += siz[fy], siz[fy] = 0;
        return true;
    }
};
template <class T>
struct OnlineMess { // we just want index.
    std::map<T, int> mp;
    inline int query(T x) {
        if (!mp.count(x)) mp[x] = mp.size() + 1;
        return mp[x];
    }
};
OnlineMess<int> M;
int n, opt, last, l, r, x;
vector<DSU> D(30, DSU(N * 2));
inline void read(int &x) { cin >> x, x ^= last; }
inline void write(int x) { cout << x << '\n', last = (x == -1 ? 1 : x); }
inline bool conflict(int l, int r, int x) {
    for (int i = 0; i < 30; i++) {
        if ((x >> i & 1) && D[i].find(r) == D[i].find(l)) return true;
        if (!(x >> i & 1) && D[i].find(r + N) == D[i].find(l)) return true;
    }
    return false;
}
inline void modify(int l, int r, int x) {
    if (l > r) std::swap(l, r);
    l = M.query(l - 1), r = M.query(r);
    if (conflict(l, r, x)) return;
    for (int i = 0; i < 30; i++) {
        if (x >> i & 1) {
            D[i].merge(r + N, l), D[i].merge(r, l + N);
        } else {
            D[i].merge(r, l), D[i].merge(r + N, l + N);
        }
    }
}
inline int query(int l, int r) {
    int ans = 0;
    if (l > r) std::swap(l, r);
    l = M.query(l - 1), r = M.query(r);
    for (int i = 0; i < 30; i++) {
        bool same = D[i].find(r) == D[i].find(l);
        bool diff = D[i].find(r) == D[i].find(l + N);
        if (!same && !diff) {
            return -1;
        } else if (diff) {
            ans |= 1 << i;
        }
    }
    return ans;
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> opt;
        if (opt == 1) {
            read(l), read(r), read(x), modify(l, r, x);
        } else {
            read(l), read(r), write(query(l, r));
        }
    }
    return 0;
}

```

---

## 作者：Nt_Tsumiki (赞：1)

## 题意

给你 $q$ 个操作，有 $2$ 种操作类型，类型 $1$ 是给你区间 $[l,r]$ 的异或值，类型 $2$ 是让你求区间 $[l,r]$ 的异或值。

强制在线。

## 做法

很好的一道题。

注意一下翻译有问题，没有把最关键的性质"如果之后存在与之前操作相矛盾的数据就忽略掉"翻译出来。

虽然看起来并不像并查集，但是以为有维护矛盾信息的性质，所以可以确定是带权并查集，关键在于如何维护。

考虑传统带权并查集里的 $val_x$，它维护的是 $x$ 与 $fa_x$ 的关系，在这道题中可以把 $val_x$ 设为 $x$ 到 $fa_x$ 的区间异或和，那么显而易见答案就是 $val_{l-1} \oplus val_r$。

而对于更新 $val_x$，假如现在新加入了一段区间 $[l,r]$，那么 $val_{rt(l-1)}=val_{l-1}\oplus val_r\oplus k$，愿因如下。

![](https://cdn.luogu.com.cn/upload/image_hosting/k1umje4s.png)

## Code

```cpp
#define _CRT_SECURE_NO_WARNINGS 1
#include <unordered_map>
#include <iostream>
#include <cstdio>

#define int long long

using namespace std;
int q,las;
unordered_map<int,int> fa,val;

int find(int x) {
	if (!fa.count(x)) return x;
	int tf=find(fa[x]);
	val[x]^=val[fa[x]],fa[x]=tf;
	return tf;
}

signed main() {
	scanf("%lld",&q);
	while (q--) {
		int op,l,r,k;
		scanf("%lld",&op);
		if (op==1) {
			scanf("%lld%lld%lld",&l,&r,&k);
			l^=las,r^=las,k^=las;
			if (l>r) swap(l,r);
			l--;
			int fl=find(l),fr=find(r);
			if (fl!=fr)	fa[fl]=fr,val[fl]=val[l]^val[r]^k;
		} else {
			scanf("%lld%lld",&l,&r);
			l^=las,r^=las;
			if (l>r) swap(l,r);
			l--,las=1;
			int fl=find(l),fr=find(r);
			if (fl!=fr) printf("-1\n");
			else printf("%d\n",las=val[l]^val[r]);
		}
	}
}
```

---

## 作者：tribool4_in (赞：0)

感觉关键点在于把区间化为左闭右开，把信息的推导方式变成只有一种简单形式。

考虑设 $F(l,r)\ (l\le r)$ 表示 $[l,r]$ 的异或和，则有两种推导方式：

- $F(l,x)\operatorname{xor}F(x+1,r)=F(l,r)$
- $F(l,x)\operatorname{xor}F(r+1,x)=F(l,r)$

发现这样很恶心，没法做，考虑如何扔掉这个 $+1$。于是考虑将定义换成左闭右开。具体设 $f(l,r)\ (l<r)$ 表示 $[l,r-1]$ 的异或和，并钦定 $f(l,r)=f(r,l)$。于是推导方式可化简为一种：$f(x,y)=f(x,z)\operatorname{xor}f(z,y)$。

于是思路已经比较清晰了：考虑建图，每次已知 $f(l,r)=x$ 相当于在 $l$ 和 $r$ 之间建边，询问相当于询问路径异或和。下标用 map 动态离散化后并查集维护即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 10;
int n = 4e5, q, tot;
map<int, int> mp;
namespace DSU {
    int fa[N], fd[N], siz[N];
    void init() { iota(fa + 1, fa + n + 1, 1), fill(siz + 1, siz + n + 1, 1); }
    int find(int x) { return fa[x] == x ? x : find(fa[x]); }
    bool check(int x, int y) { return find(x) == find(y); }
    int getd(int x) { return fa[x] == x ? 0 : fd[x] ^ getd(fa[x]); }
    void merge(int x, int y, int w) {
        int fx = find(x), fy = find(y);
        // cerr << "Merge " << x << ' ' << y << ' ' << fx << ' ' << fy << '\n';
        if (fx == fy) return;
        w ^= getd(x) ^ getd(y);
        if (siz[fx] < siz[fy]) swap(fx, fy);
        fa[fy] = fx, fd[fy] = w, siz[fx] += siz[fy], siz[fy] = 0;
    }
}  // namespace DSU
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> q;
    DSU::init();
    for (int i = 1, lstans = 0, op, l, r, x; i <= q; i++) {
        cin >> op >> l >> r, l ^= lstans, r ^= lstans;
        if (l > r) swap(l, r);
        r += 1;
        if (op == 1) {
            cin >> x, x ^= lstans;
            if (!mp.count(l)) mp[l] = ++tot;
            if (!mp.count(r)) mp[r] = ++tot;
            if (DSU::check(mp[l], mp[r])) continue;
            // cerr << "M " << l << ' ' << r << '\n';
            DSU::merge(mp[l], mp[r], x);
        } else {
            if (!mp.count(l) || !mp.count(r)) {
                lstans = 1;
                cout << "-1\n";
                continue;
            }
            if (!DSU::check(mp[l], mp[r])) {
                lstans = 1;
                cout << "-1\n";
                continue;
            }
            cout << (lstans = (DSU::getd(mp[l]) ^ DSU::getd(mp[r]))) << '\n';
        }
    }
    return 0;
}
```

---

## 作者：orz_z (赞：0)

### 题目大意

现在有一个大小为 $2^{30}$ 的数组，每个位置都有一个值，每次有两种操作：

* `1 x y z` 表示告诉你 $x$ 到 $y$ 区间的所有值异或和为 $z$。（如果和上次告诉你的矛盾，就可以当做没说。）
* `2 x y` 问你区间 $x$ 到 $y$ 的所有值的异或和是多少，如果你不知道就输出 `-1`。

### 解题思路

有什么东西可以维护矛盾信息呢？

**带权并查集！！！**

定义 $fa$ 为 $a$ 的父亲，$r[ a ]$ 表示 $a$ 异或 $fa$ 的值。

每次告诉我一个区间异或值，我只需要对两个端点进行操作就可以了，比如题目告诉我 `1 a b x`，我先通过路径压缩找到 $fa$，$fb$，如果 $fa=fb$，给的信息无用，就不需要操作了，否则，令 $fa$ 的父亲等于 $fb$，那么怎么求 $r[fa]$ 呢，$r[a]=a \operatorname{xor} fa$，那么 $fa=r[a] \operatorname{xor} a$，$r[fa]=fa \operatorname{xor} fb=r[a] \operatorname{xor}a \operatorname{xor} r[b] \operatorname{xor} b$，因为 $a \operatorname{xor} b=x$，那么 $fa=r[a] \operatorname{xor} r[b] \operatorname{xor} x$，解决了这一步，就没问题了,每次答案即为 $r_l \operatorname{xor} r_b$。

具体参考代码。

### CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

inline int read()
{
    int x = 0, w = 1;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    if (ch == '-')
        w = -1;
    while (isdigit(ch))
        x = ((x << 3) + (x << 1)) + ch - '0', ch = getchar();
    return x * w;
}

map<int, int> fa, num;

int n, l, r, x, last = 0, q, opt;

int find(int x)
{
    if (!fa.count(x))
        return x;
    int tmp = find(fa[x]);
    num[x] ^= num[fa[x]];
    fa[x] = tmp;
    return fa[x];
}

signed main()
{
    q = read();
    while (q--)
    {
        opt = read();
        if (opt == 1)
        {
            l = read();
            r = read();
            x = read();
            l ^= last, r ^= last, x ^= last;
            if (l > r)
                swap(l, r);
            --l;
            int xf = find(l), yf = find(r);
            if (xf != yf)
            {
                fa[yf] = xf;
                num[yf] = x ^ num[l] ^ num[r];
            }
        }
        else
        {
            l = read();
            r = read();
            l ^= last;
            r ^= last;
            if (l > r)
                swap(l, r);
            --l;
            int xf = find(l), yf = find(r);
            if (xf != yf)
            {
                last = 1;
                puts("-1");
            }
            else
            {
                last = num[l] ^ num[r];
                printf("%d\n", last);
            }
        }
    }
    return 0;
}
```

---

