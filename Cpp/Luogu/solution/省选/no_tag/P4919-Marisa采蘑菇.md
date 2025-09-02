# Marisa采蘑菇

## 题目背景

$\text {Marisa}$ 是一个爱魔法的女孩子，而火力高而华丽的八卦炉正是她常用的武器，随着时代的进步，$\text {Marisa}$ 也想要升级她的八卦炉的火力，所以她决定去魔法森林采蘑菇来获得做实验的材料  

## 题目描述

$\text {Marisa}$ 来到了森林之中，看到了一排 $n$ 个五颜六色的蘑菇，这些蘑菇的颜色分别为 $a_1,a_2,...,a_n$ 。由于她很挑剔，所以她只会采那些"魔法蘑菇" 。 

一个蘑菇被叫做"魔法蘑菇"，当且仅当它**在给定的某段区间内**，并且在这段给定区间内与它颜色相同的蘑菇(包括它本身)的个数，与在这个给定区间外这种颜色的蘑菇的个数之差小于等于给定的常数 $k$  

现在 $\text {Marisa}$ 会做出 $m$ 个询问,每次询问你 $[l,r]$ 中有多少种不同颜色的"魔法蘑菇"  

## 说明/提示

#### 样例解释:  

常数 $k=2$ ，对于区间  $[1,2]$:    

$a_1=2$，$2$这种颜色的蘑菇在区间 $[1,2]$ 内出现了 $1$ 次，在区间外出现了 $2$ 次，相差为 $|1-2|=1<2$   

$a_2=3$，$3$这种颜色的蘑菇在区间 $[1,2]$ 内出现了 $1$ 次，在区间外出现了 $0$ 次，相差为 $|1-0|=1<2$  

所以 $[1,2]$ 中有两种颜色不同的魔法蘑菇  

#### 数据范围:  

对于全部数据，$a_i \le 10^6,1 \le l_i \le r \le n$

对于 $20\%$ 的数据，$1 \le n,m \le 100,0 \le k \le 5$  

对于 $50\%$ 的数据，$1 \le n,m \le 10^5,0 \le k \le 100$   

对于 $100\%$ 的数据，$1 \le n,m \le 10^6,0 \le k \le 10^4$ 

ps:请注意读入效率  

## 样例 #1

### 输入

```
6 3 2
2 3 2 4 1 2
1 2
2 4
1 6```

### 输出

```
2
3
3```

# 题解

## 作者：_ctz (赞：4)

[进入我的$blog$阅读](https://ctz45562.github.io/2019/03/18/%E9%A2%98%E8%A7%A3-%E6%B4%9B%E8%B0%B7-P4919-%E3%80%90Marisa%E9%87%87%E8%98%91%E8%8F%87%E3%80%91/)

[传送门](https://www.luogu.org/problemnew/show/P4919)

壮哉我大线段树！

这种~~毒瘤~~查询肯定不能在线用数据结构维护，考虑把询问离线下来处理。

假设在某个询问$[L,R]$中某种蘑菇的数量为$x$，这种蘑菇在整个序列中的数量为$all$，则区间$[L,R]$之外的蘑菇数量为$all-x$。

当$|x-(all-x)|\le k$时该种蘑菇会有$1$贡献。分类讨论解方程就有

$\dfrac{all-k}{2}\le x\le \dfrac{all+k}{2}$（由于整形精度问题，代码中的解应为$\dfrac{all-k+1}{2}\le x\le \dfrac{all+k}{2}$）

也就是说如果固定$R$，左端点只要在某个区间内就能获得这种蘑菇的贡献。

献上一张图助于理解：

![](https://cdn.luogu.com.cn/upload/pic/54446.png )

记$next[i]$为下一个和位置$i$同种的蘑菇的位置。注意到右端点移动到$next[R]$，则对应的

绿色区间$[l,r]$也会移动到$[next[l],next[r]]$上。

而一种蘑菇当前能产生贡献的的区间为 $[$ 从$R$往前数第$\dfrac{all-k+1}{2}$个同种蘑菇的位置，从$R$往前数第$\dfrac{all+k}{2}$个同种蘑菇的位置 $]$

这样把每个位置开一个$vector$，每个询问插进它右端点的$vector$中。扫一遍序列，存一下每种蘑菇当前能产生贡献的区间，每次扫到这种蘑菇就删去旧区间的贡献（区间$-1$），并更新新区间的贡献（区间$+1$）。遇到询问右端点单点查询左端点的值作为答案。

区间加减$+$单点查询，树状数组差分可以做。然而线段树作为蒟蒻的信仰，肯定要写一发线段树。既然只有单点查，所有非叶子节点也不需要维护总和，直接维护$tag$，查询时把经过的$tag$加起来就好了，不吸氧最后一个点$2100ms+$（树状数组$1500ms+$）。

代码（可能肥肠乱，因为维护的东西比较复杂。。。）：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>

#define maxn 1000005
#define inf 0x3f3f3f3f

using namespace std;

inline int read(){
	int x=0,y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
int n,k,a[maxn];
struct Question{
	int l,ans;
}q[maxn];//每个询问
struct Segment_Tree{
#define ls(x) x<<1
#define rs(x) x<<1|1
	int tag[maxn<<2];
	void add(int L,int R,int l,int r,int node,int d){
		if(L<=l&&R>=r){
			tag[node]+=d;
			return;
		}
		int mid=l+r>>1;
		if(L<=mid)add(L,R,l,mid,ls(node),d);
		if(R>mid)add(L,R,mid+1,r,rs(node),d);
	}
	int ask(int poi,int l,int r,int node){
		if(l==r)return tag[node];
		int mid=l+r>>1;
		if(poi<=mid)return ask(poi,l,mid,ls(node))+tag[node];
		else return ask(poi,mid+1,r,rs(node))+tag[node];
	}
}st;//线段树
int ll[maxn],rr[maxn],fir[maxn],nex[maxn],last[maxn],all[maxn],cnt[maxn],li[maxn];
//ll、rr就是每种蘑菇当前能产生贡献的区间
//fir是每种蘑菇第一次出现的位置，nex是前面说的next，last是每种蘑菇上一次出现的位置，用于更新nex数组
//all是每种蘑菇总出现次数，cnt是当前已经出现过了几次，li是它的区间限制
bool vis[maxn];
vector<int>Q[maxn];
inline int limit(int i){
	return max(0,(all[i]-k+1)>>1);
}
//计算区间
//其实不难发现，(all+k)/2=all-(all-k+1)/2，所以知道一边另一边直接减一下就行了
int main(){
	n=read();
	int m=read();
	k=read();
	for(register int i=1;i<=n;++i){
		a[i]=read(),++all[a[i]];
		nex[last[a[i]]]=i,last[a[i]]=i,ll[a[i]]=1;
		if(!fir[a[i]])fir[a[i]]=i;
	}
	for(register int i=n;i;--i)
		if(!nex[i])nex[i]=n+1,li[a[i]]=limit(a[i]);
	nex[n+1]=n+1;
	for(register int i=1;i<=m;++i)
		q[i].l=read(),Q[read()].push_back(i);
	int co,p,l;
	for(register int i=1;i<=n;++i){
		co=a[i],p=++cnt[co],l=li[co];
		if(rr[co])st.add(ll[co],rr[co],1,n,1,-1);
		if(p>=l){
			if(!rr[co])rr[co]=fir[co];
			else rr[co]=nex[rr[co]];
		}
		if(p>=all[co]-l+1){
			if(!vis[co])ll[co]=fir[co]+1,vis[co]=1;
			else ll[co]=nex[ll[co]-1]+1;	
		}
		if(rr[co])st.add(ll[co],rr[co],1,n,1,1);
        //上面四个if都是用来维护这个区间的，蒟蒻也不好解释清楚了。。。感性理解一下吧。。。
		for(register int j=0;j<Q[i].size();++j)
			q[Q[i][j]].ans=st.ask(q[Q[i][j]].l,1,n,1);
	}
	for(register int i=1;i<=m;++i)
		printf("%d\n",q[i].ans);
}

```

---

## 作者：Starrydream (赞：4)

第一篇题解，献给这道扫描线好题。
首先解出每种颜色的范围（如果颜色个数>k）
[(col(i)-k)/2 , (col(i)+k)/2]
读入时预处理这么几个数组
next，times，pre ， 分别表示本颜色后继，本颜色第几个出现的位置，前驱。
将查询离线，排序。
然后用扫描线的思想将树状数组不断更新成对于当前查询合法的状态（即去除左边界前的影响）
思维难度大概NOIp D2T2 ， 实现难度差不多也是。
注意要用vector保存每种颜色的位置。
Code：
```cpp
// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <cstdio>
# include <vector>
const int maxn=1000010;
int n,m,k;
int a[maxn];
std::vector<int>p[maxn];
struct query
{
    int l,r;
    int id,ans;
    bool operator<(const query &sjb)const
    {
        return l==sjb.l?r<sjb.r:l<sjb.l;
    }
}q[maxn];
bool cmp1(const query &x,const query &y)
{
    return x.id<y.id;
}
int bit[maxn];
inline int lowbit(int x){return x&(-x);}
void update(int x,int k)
{
    if(!x)return;
    if(x>n)x=n+1;
    while(x<=n)
    {
        bit[x]+=k;
        x+=lowbit(x);
    }
}
int query(int x)
{
    int res=0;
    while(x)
    {
        res+=bit[x];
        x-=lowbit(x);
    }
    return res;
}
bool up[maxn];
int sz[maxn];
int next[maxn];
int pre[maxn];
int times[maxn];
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        if(!p[a[i]].size())up[i]=1;
        p[a[i]].push_back(i);
        next[pre[a[i]]]=i;
        times[i]=times[pre[a[i]]]+1;
        pre[a[i]]=i;
    }
    for(int i=1;i<=n;++i)
    {
        if(!up[i])continue;
        sz[a[i]]=p[a[i]].size();
        if(sz[a[i]]<=k)update(i,1);
        else update(p[a[i]][(sz[a[i]]-k-1)/2],1),update(p[a[i]][(sz[a[i]]+k)/2],-1);
    }
    for(int i=1;i<=m;++i)scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
    std::sort(q+1,q+1+m);
    int L=1;
    for(int i=1;i<=m;++i)
    {
        if(q[i].l==L)q[i].ans=query(q[i].r);
        else
        {
            while(L<q[i].l)
            {
                if(sz[a[L]]<=k)
                {
                    update(L,-1);
                    if(next[L])update(next[L],1);
                    L++;
                    continue;
                }
                if(times[L]-1+(sz[a[L]]-k-1)/2<sz[a[L]])update(p[a[L]][times[L]-1+(sz[a[L]]-k-1)/2],-1);
                if(times[L]-1+(sz[a[L]]+k)/2<sz[a[L]])update(p[a[L]][times[L]-1+(sz[a[L]]+k)/2],1);
                if(times[L]+(sz[a[L]]-k-1)/2<sz[a[L]])
                update(p[a[L]][times[L]+(sz[a[L]]-k-1)/2],1);
                if(times[L]+(sz[a[L]]+k)/2<sz[a[L]])
                update(p[a[L]][times[L]+(sz[a[L]]+k)/2],-1);
                L++;
            }
            q[i].ans=query(q[i].r);
        }
    }
    std::sort(q+1,q+1+m,cmp1);
    for(int i=1;i<=m;++i)	printf("%d\n",q[i].ans);
}

```


---

## 作者：灵乌路空 (赞：2)

知识点：扫描线，树状数组

原题面：[Luogu](https://www.luogu.com.cn/problem/P4919)

更好的阅读体验：[My blog](https://www.cnblogs.com/luckyblock/p/14424104.html)。

最后扯一句，魔理沙世界第一可爱.jpg

## 简述

>给定一长度为 $n$ 的数列 $a$，参数 $k$。给定 $m$ 次询问。  
>每次询问给定区间 $[l,r]$，求区间内有多少个数，满足在区间内的出现次数与区间外的出现次数之差小于等于给定的常数 $k$。  
>$1\le n,m\le 10^6$，$0\le k\le 10^4$，$0\le l\le r\le n$。  
>3S，128MB。  

## 分析

对于一个询问区间 $[l,r]$，设 $s$ 为权值 $x$ 在整个数列中出现的次数。考虑某种权值 $x$ 对该区间有贡献的条件，显然为 $|(s - x) - x|\le k$。上式解得：

$$s - k\le 2\cdot x\le s + k$$

考虑离线询问并排序，通过对询问进行扫描线固定询问的右端点。考虑在询问右端点单调右移的同时，对于每种权值，都维护它有所贡献的询问的左端点范围 $[L,R]$。当询问的左端点 $l\in [L,R]$ 时，区间 $[l,r]$ 内这种权值出现次数满足上式。右端点右移到下一个同权值位置时更新区间。如下图所示：

![魔理沙世界第一可爱](https://cdn.luogu.com.cn/upload/image_hosting/23wdg816.png)

当**前缀** $[1,r]$ 中某权值出现次数满足上式时，有贡献的区间是数列的一段完整前缀，且需要注意 $L,R$ 的初始取值，详见代码。

当扫描线枚举的右端点为 $r$，维护上述信息后，询问 $[l,r]$ 的答案即为覆盖了左端点 $l$ 的区间的个数。  
发现上述算法需要支持区间修改，单点求和，树状数组维护即可，总复杂度 $O(m\log m + (n+m)\log n)$ 级别。

## 代码

```cpp
//知识点：扫描线，树状数组
/*
By:Luckyblock
*/
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#define LL long long
const int kN = 1e6 + 10;
//=============================================================
struct Q {
  int l, r, id;
} q[kN];
int n, m, k, col[kN], ans[kN];
int last[kN], ne[kN], first[kN], sum[kN];
//ne[i]：col[i] 之后第一个等于 col[i] 的位置
//first[i]：颜色 i 在数列中第一次出现的位置
//sum[i]：颜色 i 在数列中出现次数之和
int cnt[kN], L[kN], R[kN];
//在扫描线过程中维护，cnt[i]：到扫描位置为止 i 的出现次数
//L[i]~R[i]：当前扫描位置作为询问右端点时，颜色 i 有贡献的询问左端点范围
//=============================================================
inline int read() {
  int f = 1, w = 0;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    if (ch == '-') f = -1;
  for (; isdigit(ch); ch = getchar()) w = (w << 3) + (w << 1) + (ch ^ '0');
  return f * w;
}
void Chkmax(int &fir, int sec) {
  if (sec > fir) fir = sec;
}
void Chkmin(int &fir, int sec) {
  if (sec < fir) fir = sec;
}
bool CMP(Q fir_, Q sec_) {
  if (fir_.r != sec_.r) return fir_.r < sec_.r;
  return fir_.l < sec_.l;
}
namespace Bit {
  #define low(x) (x&-x)
  const int kLim = 1e6;
  int t[kLim + 10];
  void Add(int pos_, int val_) {
    ++ pos_;
    for (int i = pos_; i <= kLim; i += low(i)) t[i] += val_;
  }
  int Sum(int pos_) {
    ++ pos_;
    int ret = 0;
    for (int i = pos_; i; i -= low(i)) ret += t[i];
    return ret;
  }
  void Modify(int l_, int r_, int val_) {
    Add(l_, val_);
    Add(r_ + 1, -val_);
  }
}
void Init() {
  n = read(), m = read(), k = read();
  for (int i = 1; i <= n; ++ i) {
    col[i] = read();
    if (++ sum[col[i]] == 1) first[col[i]] = i;
    last[col[i]] = n;
  }
  for (int i = n; i >= 1; -- i) {
    ne[i] = last[col[i]];
    last[col[i]] = i;
  }
  for (int i = 1; i <= m; ++ i) q[i] = (Q) {read(), read(), i};
  std::sort(q + 1, q + m + 1, CMP);
}
void Modify(int pos_) {
  int c = col[pos_], s = sum[c];
  ++ cnt[c];
  if (R[c]) Bit::Modify(L[c], R[c], -1); //减去之前颜色 i 对询问左端点的贡献
  if (2 * cnt[c] >= s - k) R[c] = R[c] ? ne[R[c]] : first[c]; //右端点左移，增加区间内该权值出现次数。
  if (2 * cnt[c] > s + k) L[c] = L[c] ?  ne[L[c] - 1] + 1 : first[c] + 1; //左端点右移，减小区间内该权值出现次数。注意开区间。
  if (R[c]) Bit::Modify(L[c], R[c], 1);
}
//=============================================================
int main() { 
  Init();
  for (int i = 1, nowr = 0; i <= m; ++ i) {
    while (nowr < q[i].r && nowr < n) Modify(++ nowr); //扫描位置更新
    ans[q[i].id] = Bit::Sum(q[i].l);
  }
  for (int i = 1; i <= m; ++ i) printf("%d\n", ans[i]);
  return 0; 
}
```

---

## 作者：Jr_Zlw (赞：1)

莫名奇妙跑成最优解了来纪念一下 。

# 离线+树状数组


不难发现，某一种蘑菇在区间内出现个数的取值范围是能轻易预处理的 。

我们假设区间内该蘑菇数为 $x$ , 该蘑菇总数为 $n$ , 区间内外差不超过 $k$ 。

即 ：  $k\leq|x-(n-x)|,x>0$   。

做一个简单的分类讨论可得 ：

$$ \max(1,\lceil\dfrac{n-k}{2}\rceil )  \leq x \leq \lfloor \dfrac{k+n}{2}\rfloor$$

于是我们设第  $i$  种蘑菇的取值为  $[lm_i,rm_i]$  。

我们发现这确实是个 [采花](https://www.luogu.com.cn/problem/P4113) 的加强版，思路一模一样 。

对询问离线，按左端点排序。

我们设  $nxt_i$  表示下一个与第  $i$  个蘑菇相同的位置 。

我们先处理出每一种蘑菇的第  $lm$  次出现的位置，记录为  $lc$  ，该位置  $+1$  。

然后处理出每一种蘑菇第  $rm+1$  次出现的位置，记录为  $rc$  ，该位置  $-1$  。

假设我们拿到一个询问  $[l,r]$  。

可以从数列前面删除数一直删到  $l-1$  处，还原前一步操作，然后将对应  $lc,rc$  跳  $nxt$  ,再在 $lc$  处  $+1$  ，  $rc$  处  $-1$ 即可 。

然后我们只需查询  $r$  的前缀和即为答案 。

奉上丑陋的代码：

```
#include<cstdio>
#include<algorithm>
#define rep(a,b,c) for(int c=(a);c<=(b);++c)
#define drep(a,b,c) for(int c=(a);c>=(b);--c)
inline int read()
{
    int res=0;char ch=getchar();while(ch<'0'||ch>'9')ch=getchar();
    while(ch<='9'&&ch>='0')res=res*10+(ch^48),ch=getchar();return res;
}
inline int Max(int x,int y){return x>y?x:y;}
const int N=1e6+10;bool vis[N];
int t[N],n,m,k,lm[N],rm[N],a[N],nxt[N],lst[N],cnt[N],lc[N],rc[N],ans[N];
inline void add(int p,int v){while(p<=n)t[p]+=v,p+=(p&-p);}
inline int qry(int p){int r=0;while(p)r+=t[p],p^=(p&-p);return r;}
struct Srt{int l,r,idx;inline bool operator<(const Srt &x)const{return l<x.l;}}Q[N];
int main()
{
    n=read();m=read();k=read();
    rep(1,n,i)++cnt[a[i]=read()],lst[a[i]]=n+1;nxt[n+1]=n+1;
    drep(n,1,i)
    {
        nxt[i]=lst[a[i]],lst[a[i]]=i;if(lm[a[i]])continue;
        lm[a[i]]=Max(1,(cnt[a[i]]-k+1)>>1);rm[a[i]]=(k+cnt[a[i]])>>1;
    }
    rep(1,m,i)Q[i].l=read(),Q[i].r=read(),Q[i].idx=i;
    std::sort(Q+1,Q+m+1);
    rep(1,n,i)if(!vis[a[i]])
    {
        lc[a[i]]=rc[a[i]]=i;int tmp;vis[a[i]]=1;
        tmp=1;while(tmp<lm[a[i]]&&lc[a[i]]^(n+1))
            ++tmp,lc[a[i]]=nxt[lc[a[i]]];add(lc[a[i]],1);
        tmp=0;while(tmp<rm[a[i]]&&rc[a[i]]^(n+1))
            ++tmp,rc[a[i]]=nxt[rc[a[i]]];add(rc[a[i]],-1);
    }
    int cur=1;rep(1,m,i)
    {
        while(cur<Q[i].l)
        {
            add(lc[a[cur]],-1);add(rc[a[cur]],1);
            lc[a[cur]]=nxt[lc[a[cur]]];rc[a[cur]]=nxt[rc[a[cur]]];
            add(lc[a[cur]],1);add(rc[a[cur]],-1);++cur;
        }
        ans[Q[i].idx]=qry(Q[i].r);
    }
    rep(1,m,i)printf("%d\n",ans[i]);return 0;
}
```

---

## 作者：Caicz (赞：1)


**[在博客食用效果更佳](https://czicz.cn/2020/10/22/jie-ti-bao-gao-marisa-cai-mo-gu/)**

#### 前言

采用了离线后树状数组的做法，常数极小，且树状数组只需要维护单点修改，区间查找，~~轻松跑到最优解~~

#### 题意

给你一个长度为 $n$ 的序列 $a_1,a_2,a_3\dots a_n$ ，$m$ 次询问一个区间 $[l,r]$ ，求区间中出现次数与区间外出现次数的差小于 $k$ 的不同权值个数，对于每个询问 $k$ 相同  
					$1\le a_i,n,m\le1e6$

#### 题解

类似于各种区间求众数题，很显然的我们可以将询问离线后从左到右依次处理

当找到一个对于 $a[x]$ 满足条件的前缀 x ，即满足 $|2\times cnt[a[x]]-sum[a[x]]|<=k$ 时  
我们在 $x$ 插入 1，并删除掉之前在 $pre[x]$ 插入的 1，一直维护最小区间即可

当现在所在的前缀第一次满足 $2\times cnt[a[x]]-sum[a[x]]>k$ 时  
我们在区间从左到右第一个 $a[x]$ 处插入 -1，同时将 1 右移，之后每多遍历到一个 $a[x]$ ，我们就分别将 -1 和 1 向右移到下一个 $a[x]$，这里可以对每个权值预处理维护一个仅包含 $next$ 指针的链表来 $O(1)$ 解决

注意判断之前是否插入过，防止树状数组访问到 0 下标，同时也注意对于一个数，如果没有进入过第一种情况，那么它将不可能有贡献

把思路理清楚，代码实现可能有点绕
$$
\large\color{grey}{\text{Talk is cheap , show you the code}}
$$

#### 代码

```cpp
#include<stdio.h>
#include<iostream>
#include<cstring>
#include<math.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn=1000005;
const int inf=0x3f3f3f3f;
int n,m,k,col[maxn],net[maxn],pos[maxn],la[maxn];
int cnt[maxn],a[maxn],sum[maxn],ans[maxn];
struct ques
{
	int l,r,id;
	friend bool operator<(ques x,ques y){return x.r<y.r;}
}q[maxn];

inline int read(void)
{
	int num,sign=1;char c;
	while(!isdigit(c=getchar()))if(c=='-')sign=0;num=c-'0';
	while(isdigit(c=getchar()))num=(num<<1)+(num<<3)+c-'0';
	return sign?num:-num;
}
int tr[maxn];
inline void insert(int x,int d){for(;x<=n;x+=x&-x)tr[x]+=d;}
inline int query(int x){int res=0;for(;x;x-=x&-x)res+=tr[x];return res;}

signed main(void)
{
	n=read(),m=read(),k=read();
	for(register int i=1;i<=n;++i)a[i]=read(),++sum[a[i]];
	for(register int i=n;i;--i)net[i]=col[a[i]],col[a[i]]=i;
	for(register int i=1;i<=m;++i)q[i].l=read(),q[i].r=read(),q[i].id=i;
	sort(q+1,q+1+m);
	for(register int j=1,i=1;i<=n;++i)
	{
		++cnt[a[i]];
		if(2*cnt[a[i]]-sum[a[i]]<=k&&2*cnt[a[i]]-sum[a[i]]>=-k)
		{
			int u;
			if(pos[a[i]])
			{
				insert(pos[a[i]],-1);
				u=net[pos[a[i]]];
			}
			else u=col[a[i]];
			insert(u,1),pos[a[i]]=u;
		}
		else if(2*cnt[a[i]]-sum[a[i]]>k)
		{
			int u;
			if(la[a[i]])insert(la[a[i]],1);
			if(pos[a[i]])
			{
				insert(pos[a[i]],-1);
				u=net[pos[a[i]]];
				if(!la[a[i]])la[a[i]]=col[a[i]];
				else la[a[i]]=net[la[a[i]]];
				insert(la[a[i]],-1);
				insert(u,1);pos[a[i]]=u;
			}
		}
		while(q[j].r==i)ans[q[j].id]=query(q[j].r)-query(q[j].l-1),++j;
	}
	for(register int i=1;i<=m;++i)printf("%d\n",ans[i]);
	return 0;
}

```



---

## 作者：_ayaka_ (赞：0)

### 思路

此题类似于 [P1972 [SDOI2009] HH的项链](/problem/P1972)。

首先有显然的离线莫队做法。只要提前统计每个颜色的总数，然后统计区间内和区间外的差值 $\le k$ 的有几个即可。莫队很容易实现。但是 $O(n\sqrt n)$ 只能拿 $50$ 分。

考虑树状数组，将区间按右端点排序后离线处理。先假设这个序列只有一种颜色。枚举右端点，设右端点及其以前有 $x$ 个蘑菇，右端点后有 $y$ 个。我们找左端点为多少时，这个颜色可以产生贡献。设左端点为 $a$。可得需满足以下两个不等式：

-  $y-x+2a\le k$
-  $x-y-2a\le k$

移项后得：

$\frac{x-y-k}{2}\le a \le \frac{x-y+k}{2}$

然后在树状数组上把最后一个满足此式的位置的，即上界赋为 $1$，左侧最后一个不满足此式的，即下界的前一个赋为 $-1$，查询即可。上界超出 $a$ 则上界改为  $a$，下界超出边界则无视。原理可以自行查阅 P1972 中的原理。多种颜色时，将赋值的端点 $a$ 改为此颜色的蘑菇第 $a$ 次出现的位置即可。时间复杂度 $O(n\log n)$。

注意实际左端点是从 $1$ 开始因此要把求出的 $a$ 的上界下界 $+1$。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, m, k, col[1000005], now[1000005], p[1000005], t[1000005], ans[1000005], tot;
//col：此颜色出现的次数。now：右端点枚举到此刻时此颜色出现的次数。
//p：原序列。t：树状数组。ans：答案。 
vector<int> e[1000005];
//e：此颜色从小打到大每一次出现的位置。 
pair<int, int> lst[1000005];
//lst：此颜色上一次的操作。（用于清空上一次赋值） 
int lowbit(int x) {
	return x & (-x);
}
void add(int x, int d) {
	for (int i = x; i <= n; i += lowbit(i))
		t[i] += d;
}
int sum(int x) {
	int ans = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		ans += t[i];
	return ans;
}
struct node {
	int l, r, id;
} a[5000005];
bool cmp(node x, node y) {
	return x.r < y.r;
}
signed main() {
	for (int i = 1; i <= 1e6 + 2; i++) {
		lst[i] = {0, 0};
		col[i] = now[i] = 0;
	}
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
		col[p[i]]++;
	}
	for (int i = 1; i <= m; i++) {
		cin >> a[i].l >> a[i].r;
		a[i].id = i;
	}
	sort(a + 1, a + m + 1, cmp);
	for (int i = 1, l = 0, r = 0; i <= n; i++) {
		auto [ll, rr] = lst[p[i]];
		if (ll > 0) add(ll, 1);
		if (rr > 0) add(rr, -1);
		//将上一次的操作去除。 
		now[p[i]]++;
		e[p[i]].push_back(i);
		l = floor((now[p[i]] - (col[p[i]] - now[p[i]]) - k + 1) * 1.0 / 2);
		r = floor((now[p[i]] - (col[p[i]] - now[p[i]]) + k + 2) * 1.0 / 2);
		//此处比列出的式子大 1。参考最后一句话。 
		//注意使用 floor 是因为 C++ 默认向 0 取整。笔者因此被卡了 20 mins。 
		if (l > now[p[i]]) l = e[p[i]][now[p[i]] - 1];
		else if (l <= 0) l = 0;
		else l = e[p[i]][l - 1];
		if (r > now[p[i]]) r = e[p[i]][now[p[i]] - 1];
		else if (r <= 0) r = 0;
		else r = e[p[i]][r - 1];
		lst[p[i]] = {l, r};
		if (l > 0) add(l, -1);
		if (r > 0) add(r, 1);
		while (a[tot].r <= i && tot <= m) {
			if (a[tot].r == i) {
				ans[a[tot].id] = sum(i) - sum(a[tot].l - 1);
			}
			tot++;
		}
	}
	for (int i = 1; i <= m; i++) cout << ans[i] << "\n";
	return 0;
}
```

---

