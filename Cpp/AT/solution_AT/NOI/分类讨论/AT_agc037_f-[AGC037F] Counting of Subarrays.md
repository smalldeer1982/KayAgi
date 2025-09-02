# [AGC037F] Counting of Subarrays

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc037/tasks/agc037_f

正整数列 $ S $ 及び正整数 $ k,l $ が以下のいずれかの条件をみたすとき、 $ S $ が  **レベル**  $ (k,l) $ に属すると定義することにします。

- $ S $ の要素数が $ 1 $ であり、その要素の値が $ k $ である。
- あるレベル$ (k-1,l) $ に属する数列 $ T_1,T_2,...,T_m $ ($ m\ ≧\ l $) が存在して、 $ T_1,T_2,...,T_m $ をこの順に連結して得られる数列と $ S $ が一致する。

ただし、$ k=1 $ のとき二番目の条件は意味を持たない、つまりレベル$ (1,l) $の正整数列は一つ目の条件をみたすもののみであることに注意して下さい。

正整数列 $ A_1,A_2,...,A_N $ と正整数 $ L $ が与えられます。 以下の条件をみたす部分列 $ A_i,A_{i+1},...,A_j $ ($ 1\ ≦\ i\ ≦\ j\ ≦\ N $) の個数を求めてください。

- ある正整数 $ K $ が存在して、数列 $ A_i,A_{i+1},...,A_j $ がレベル$ (K,L) $に属する。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 2\ \times\ 10^5 $
- $ 2\ ≦\ L\ ≦\ N $
- $ 1\ ≦\ A_i\ ≦\ 10^9 $

### Sample Explanation 1

例えば $ (1,1,1) $ と $ (2) $ という数列はともにレベル $ (2,3) $ に属するので、$ (2,1,1,1,1,1,1) $ という数列はレベル $ (3,3) $ に属します。

## 样例 #1

### 输入

```
9 3
2 1 1 1 1 1 1 2 3```

### 输出

```
22```

## 样例 #2

### 输入

```
9 2
2 1 1 1 1 1 1 2 3```

### 输出

```
41```

## 样例 #3

### 输入

```
15 3
4 3 2 1 1 1 2 3 2 2 1 1 1 2 2```

### 输出

```
31```

# 题解

## 作者：xht (赞：9)

## [Counting of Subarrays](https://atcoder.jp/contests/agc037/tasks/agc037_f)

### 题意

- 给定一个正整数序列 $a_{1\dots n}$ 和一个正整数 $l$，求 $a$ 有多少个非空子段 $a_{i\dots j}$，满足存在正整数 $k$ 使得 $a_{i \dots j}$ 属于等级 $k$。
- 对于一个正整数序列 $a$ 和正整数 $k,l$，称 $a$ 属于等级 $k$ 当且仅当满足以下两个条件至少一个：
  - $a$ 的长度为 $1$ 且唯一的元素为 $k$。
  - 当 $k \ne 1$ 时，可以将 $a$ 分成不少于 $l$ 个非空子段，使得每一段都属于等级 $k-1$。
- $n \le 2 \times 10^5$，$2 \le l \le n$，$a_{i} \le 10^9$。

### 题解

首先考虑如何判断一个序列 $s$ 是否合法（即存在正整数 $k$ 使得 $s$ 属于等级 $k$）。

考虑将定义的过程反着推，相当于每次对于 $s$ 中最小的元素 $x$，找到所有 $x$ 的连续段。设一个连续段的长度为 $t$，若 $t < l$ 则判定为不合法，否则将这一段合并为 $\lfloor \frac tl \rfloor$ 个 $x + 1$，直到 $s$ 中只剩下一种元素。注意这个元素一定是一开始 $s$ 中的最大值，同时我们不再合并这个元素。

设 $s$ 的最大值为 $w$，此时分三种情况：

- 若 $w$ 的数量为 $1$，这种情况当且仅当原序列的长度为 $1$，$s$ 属于等级 $w$，合法。
- 若 $w$ 的数量不少于 $l$，$s$ 属于等级 $w + 1$，合法。
- 不合法。

考虑将这个过程搬到整个序列 $a$ 中。

首先对于第一种情况直接特判。

然后从小到大考虑 $a$ 中出现过的值 $w$，当考虑到 $w$ 时，我们需要计算 $a$ 中所有最大值为 $w$ 的子段的中合法的数量，这个过程可以用一个单调栈维护。

即我们现在有一个序列 $s = s_0ws_1w \cdots ws_m$，其中 $s_i$ 为一个所有元素都 $<w$ 的序列，我们要求出这个序列中有多少个子段满足其属于等级 $w+1$。

考虑对于一个序列 $s$ 维护以下几个信息（其中 $w$ 为 $s$ 中的最大值）：

- $f_{s,i}$ 表示 $s$ 中至多能合并出 $i$ 个 $w$ 的前缀个数。
- $g_{s,i}$ 表示 $s$ 中至多能合并出 $i$ 个 $w$ 的后缀个数。
- $h_{s}$ 表示 $s$ 至多能合并出的 $w$ 的个数，这个可以根据 $f,g$ 求出。

根据 $f_s,g_s,h_s$，我们可以简单地求出对于任意一个 $w^\prime > w$，$s$ 中至多能合并出 $i$ 个 $w^\prime$ 的前/后缀个数，以及 $s$ 至多能合并出的 $w^\prime$ 的个数。

假设我们现在对于 $s = s_0ws_1w \cdots ws_m$ 中的所有 $s_i$ 都求出了 $f_{s_i},g_{s_i},h_{s_i}$，则我们首先可以求出 $s_i$ 中至多能合并出 $i$ 个 $w$ 的前/后缀个数，以及 $s$ 至多能合并出的 $w$ 的个数。然后使用 Two pointers 在 $\mathcal O(m + \sum_{i=0}^m h_{s_i})$ 的时间复杂度下求出 $s$ 的答案，以及 $f_s,g_s,h_s$。

接下来考虑一下时间复杂度，乍看下去可能时间复杂度非常高，但如果我们只记录不为 $0$ 的 $f_s,g_s$，状态总数是 $\mathcal O(n \log n)$ 的。

这是因为对于 $a$ 中的一个元素 $w$，它至多为最大值为 $w$ 的极长子段提供 $1$ 的状态数，为最大值为 $w+1$ 的极长子段提供 $\frac1l$ 的状态数，为最大值为 $w+2$ 的极长子段提供 $\frac1{l^2}$ 的状态数，因此总状态数实际上是 $\mathcal O(n \log n)$ 的。

精细实现的话，总时间复杂度为 $\mathcal O(n \log n)$。

### 代码

```cpp
const int N = 2e5 + 7;
int n, l, s[N], t, f[N], g[N], sf[N], sg[N];
ll ans;

inline void pop() {
	int k = 1, x = s[t];
	while (s[t-1] == x) --t, ++k;
	--t;
	if (k < l) {
		while (t) pop();
		return;
	}
	int w = k / l;
	for (int i = 1; i <= k; i++)
		sf[i] = sf[i-1] + f[i+t], sg[i] = sg[i-1] + g[i+t];
	for (int i = l; i <= k; i++)
		ans += 1ll * sf[i-l+1] * g[i+t];
	for (int i = 1; i <= w; i++)
		f[t+i] = sf[k-l*(w-i+1)+1] - sf[max(k-l*(w-i+2)+1,0)],
		g[t+i] = sg[min(l*(i+1)-1,k)] - sg[l*i-1];
	for (int i = l, s = 0; i <= w; i++)
		ans -= 1ll * (s += f[t+i-l+1]) * g[t+i];
	for (int i = 1; i <= w; i++)
		s[++t] = x + 1;
}

int main() {
	rd(n, l), ans = n;
	for (int i = 1, x; i <= n; i++) {
		rd(x);
		while (t && s[t] < x) pop();
		s[++t] = x, f[t] = g[t] = 1;
	}
	while (t) pop();
	print(ans);
	return 0;
}
```

---

## 作者：Kubic (赞：6)

先考虑给定一个序列和 $m$，如何判断这个序列是否满足条件。

考虑当前序列中的最小值 $x$ ，对于每一段连续的长度为 $len$ 的 $x$ 进行以下操作：

- 如果 $len<m$ 则保留不变。
- 如果 $len\ge m$ 则变为一段长度为 $\lfloor\dfrac{len}{m}\rfloor$ 的 $x+1$。

这里的“最小值”定义为还有机会能够进行第二种操作的最小的 $x$。

可以发现如果进行过第一种操作则一定不可能满足条件。

那么一个序列满足条件当且仅当重复这样的操作直到只剩下一种数，且剩下的数个数 $\ge m$。

也就是说，如果一个序列满足条件，则它一定可以属于第 最大值$+1$ 级别。

考虑对原序列进行这样的操作，并比较一个子串的操作过程和原序列的操作过程。

同一时刻，前者一定还是后者的一个子串。

于是可以考虑如何在原序列的操作过程中维护答案。

从小到大枚举每个数，考虑最大值为当前值的子串中有多少个满足条件。

对于原序列中的每一个位置 $x$ 维护：

- 有多少个**原序列中的子串**现在被合并为了 $x$ 所在段中以 $x$ 为结尾的前缀。

对于后缀同理维护。

合并两个段时可以统计段间贡献，利用前缀和即可线性，新的前缀与后缀也容易维护。

然后就一个一个枚举并暴力合并就好啦！！1

分析一波复杂度：每次合并完之后元素个数会除以 $m$。而 $m\ge 2$，所以总元素个数 $O(n\log n)$。

看起来十分对，真的吗？~~别问我怎么知道的~~

一个段被合并过一次之后与后面的段合并时，元素个数并不会再次除以 $m$。

如何规避这样的复杂度问题呢？

其实只要把一段将要合并的东西全部拿出来一起合并即可，精细实现可做到线性合并。

因此总复杂度 $O(n\log n)$。细节极多，建议自己在实践中想一想。

代码（实现很不优美）：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 200005
#define ll long long
#define pb push_back
int n,m,pw[N],a[N],ds[N],fa[N],R[N],st[N];ll ans;vector<int> vc[N];
int tp[N],z1[N],z2[N],lst[N],s[N],cnt1[N],cnt2[N];
int findRt(int x) {return x==fa[x]?x:fa[x]=findRt(fa[x]);} 
void merge(int x,int y) {x=findRt(x);y=findRt(y);fa[y]=x;R[x]=R[y];}
void upd(int x)
{for(int i=tp[x];i>=x;--i) s[s[0]+1]=s[s[0]]+z2[i],++s[0];}
void upd1(int x,int d)
{
	d=min(d,n);
	for(int i=x;i<=tp[x];++i)
		cnt1[(i-x+1)/pw[d]]+=z1[i],cnt2[(i-x+1)/pw[d]]+=z2[i];
	tp[x]=(tp[x]-x+1)/pw[d]+x-1;
	for(int i=x;i<=tp[x];++i)
		z1[i]=cnt1[i-x+1],z2[i]=cnt2[i-x+1],cnt1[i-x+1]=cnt2[i-x+1]=0;
}
void slv(int x)
{
	int t,rt,mn;s[0]=cnt1[0]=cnt2[0]=0;
	for(int i=1;i<=st[0];++i) z1[++tp[st[i]]]=1,z2[tp[st[i]]]=1;
	t=findRt(st[1]-1);if(t<=tp[t]) rt=t,upd(t);else rt=st[1];
	for(int i=1;i<=st[0];++i)
	{
		upd(st[i]);if(s[0]>=m) ans+=s[s[0]-m+1];t=findRt(st[i]+1);
		if(rt!=st[i]) z1[++tp[rt]]=1,merge(rt,st[i]);
		if((i<st[0] && st[i]+1==st[i+1]) || t>tp[t]) continue;
		for(int j=t;j<=tp[t];++j)
		{
			z1[++tp[rt]]=z1[j];
			if(s[0]>=m-j+t-1) ans+=1ll*z1[j]*s[min(s[0]-m+j-t+2,s[0])];
		}upd(t);merge(rt,t); 
	}for(int i=rt;i<=tp[rt];++i) z2[i]=s[s[0]-i+rt];
	for(int i=rt;i<tp[rt];++i) z2[i]-=z2[i+1];mn=2e9;
	if(x<a[rt-1]) mn=min(mn,a[rt-1]);
	if(x<a[R[rt]+1]) mn=min(mn,a[R[rt]+1]);upd1(rt,mn-x);
}
int main()
{
	scanf("%d %d",&n,&m);
	tp[0]=-1;tp[n+1]=n;fa[n+1]=n+1;pw[0]=1;
	for(int i=1;i<=n;++i) pw[i]=min(1ll*pw[i-1]*m,1ll+n);
	for(int i=1;i<=n;++i)
		fa[i]=R[i]=i,tp[i]=i-1,scanf("%d",&a[i]),ds[++ds[0]]=a[i];
	sort(ds+1,ds+ds[0]+1);ds[0]=unique(ds+1,ds+ds[0]+1)-ds-1;
	for(int i=1;i<=n;++i)
		vc[lower_bound(ds+1,ds+ds[0]+1,a[i])-ds].pb(i);
	for(int i=1,t,t1;i<=ds[0];++i) for(int j=0;j<vc[i].size();++j)
	{
		t=vc[i][j];st[++st[0]]=t;t1=findRt(t+1);
		if(j==vc[i].size()-1 ||
		   (t+1!=vc[i][j+1] && (t1>tp[t1] || t1!=findRt(vc[i][j+1]-1))))
			slv(ds[i]),st[0]=0;
	}printf("%lld\n",ans+n);return 0;
}
```

---

## 作者：myee (赞：1)

### 前言

发现我的做法和大家都不太一样，介绍一下吧。

### 思路

考虑对右端点扫描线，并对当前前缀维护一个单调栈，使得其从栈底到栈顶单调减——因为到当前右端点的所有区间如果遇到比其更大的值，必然会发生改变，所以可以提前变好。

我们规定，一段区间是合法的，当且仅当其可以变成 $\ge L$ 个相同的数。容易发现这样只会计漏长度等于 $1$ 的情况，补上即可。

栈中每个点如果是合法的左端点，其取法未必唯一，我们同时记录下该信息即可。弹栈时容易顺带更新。

然后查询一个右端点对应的合法左端点方案数之和时，我们可以依次考虑栈中每个权值相同段中的每个点作为左端点的方案数之和。显然对于一个固定的权值相同段，其方案数只和**栈中在其上面的元素可以转化成最多多长的当前值**有关。容易发现恰好有一个前缀的方案数被计入答案，使用前缀和即可维护。

由于过程是不断往栈底深入的，我们可以对每次查询对应的答案记忆化，从而使用 $L$ 进制进位器的技巧进行**复杂度均摊**。

这样就可以通过了。

### Code

代码很好写，跑得很快。

```cpp
uint Now[200005],A[200005],S[200005],From[200005],m,tp;
uint Qp[200005],Qv[200005];
uint PM[55],qwq;
ullt ans;
uint query(uint p,uint v,uint c)
{
    if(!~p||Now[p]-v>qwq||!(c/=PM[Now[p]-v]))return 0;
    if(c==Qp[p])return Qv[p];
    Qp[p]=c;
    return Qv[p]=(c+p-From[p]+1>=m?(c>=m?S[p+1]-S[From[p]]:
        S[p+2+c-m]-S[From[p]])+query(From[p]-1,Now[p],c+p-From[p]+1):0);
}
voi insert(uint v)
{
    while(tp&&tp-From[tp-1]>=m&&Now[tp-1]<v)
    {
        uint t=From[tp-1];
        std::vector<uint>V;
        for(uint j=m;tp>=j+t;j++){
            if(j%m==0)V.push_back(0);
            V.back()+=A[tp-j];
        }
        tp=t;
        while(V.size())
            Now[tp]++,From[tp]=tp&&Now[tp]==Now[tp-1]?From[tp-1]:tp,
            A[tp]=V.back(),S[tp+1]=S[tp]+A[tp],
            V.pop_back(),Qp[tp]=-1,tp++;
    }
    if(tp&&Now[tp-1]<v)tp=0;
    ans+=1+query(tp-1,v,1);
    Now[tp]=v,From[tp]=tp&&Now[tp]==Now[tp-1]?From[tp-1]:tp,
    A[tp]=1,S[tp+1]=S[tp]+A[tp],Qp[tp]=-1,tp++;
}
int main()
{
#ifdef MYEE
    freopen("QAQ.in","r",stdin);
    freopen("QAQ.out","w",stdout);
#endif
    uint n;scanf("%u%u",&n,&m);
    PM[0]=1;while(PM[qwq]<=n/m)PM[qwq+1]=PM[qwq]*m,qwq++;
    for(uint i=0,a;i<n;i++)scanf("%u",&a),insert(a);
    printf("%llu\n",ans);
    return 0;
}
```



---

## 作者：UltiMadow (赞：0)

首先考虑如何判断一个序列是不是好的

1. 序列只有一个数，一定是好的
2. 序列所有数相同，且长度 $\ge L$，一定是好的
3. 记序列中最小数为 $x$，所有的连续的 $x$ 段的长度为 $len_i$，把每一段合并成 $\lfloor \frac{len_i}L\rfloor$ 个 $x+1$，继续判断

每次合并需要 $O(L)$，序列长度减小 $L-1$，排序需要 $\mathcal O(n\log n)$，所以这个过程的复杂度为 $\mathcal O(n\log n)$

考虑把要求的东西加强一下，变成对于每个数有两个权值 $L_i$ 和 $R_i$，对于每个好的数列 $[i,j]$ 去求 $L_iR_j$ 的和

仍然用上面的步骤

1. 序列只有一个数，一定是好的
2. 序列所有数相同，且长度 $\ge L$，一定是好的，这时可以 $\mathcal O(n)$ 求出答案
3. 记序列中最小的数为 $x$，所有连续的 $x$ 段长度为 $len_i$，对于每一段按照 2 的方法求出答案，合并成 $\lfloor \frac{len_i}L\rfloor$ 个 $x+1$，求出这些 $x+1$ 的 $L$ 和 $R$，继续这些步骤

现在的问题就是要在合并的时候更新 $L$ 和 $R$

不难发现每次已经求出了一个 $x$ 连续段内的答案，记这个连续段为 $[l,r]$，我们更新 $[l,r]$ 中的 $L_i$ 和 $R_i$ 的目的是要求在 $[l,r]$ 两边的 $x+1$ 段对 $[l,r]$ 中的 $x$ 产生的贡献，不妨考虑 $r$ 右边的 $x+1$ 段对 $[l,r]$ 中的 $x$ 的贡献（即更新 $L$）

记 $i$ 离 $r$ 的距离为 $q$，则 $L_i$ 应该贡献给合并后 $\lfloor \frac{len_i}L\rfloor-\lfloor\frac qL\rfloor$ 位置的 $L$（贡献 $\lfloor\frac qL\rfloor$ 个 $x+1$ 给后面的 $x+1$ 段）

注意在之后计算 $x+1$ 的时候会重复计算 $x$ 的答案，需要减掉，长度为 1 的序列直接在最开始答案加上 $n$ 即可

复杂度计算和之前一样，为 $\mathcal O(n\log n)$

注意特判 $L=1$ 的情况，这时每次合并减少 $L-1=0$ 个数，会一直合并下去

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define MAXN 200010
using namespace std;
int n,L,ans,a[MAXN];
struct Node{int l,r,vl,vr;};
vector<Node>que;
vector<pii>pos;
bool cmp(Node a,Node b){return a.l<b.l;}
int calc(vector<Node>&now){
	int ret=0,sum=0,sz=now.size();
	for(int i=L-1;i<sz;i++)
		sum+=now[i-L+1].vl,ret+=sum*now[i].vr;
	return ret;
}
signed main(){
	scanf("%lld%lld",&n,&L);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]),pos.pb(mp(a[i],i));
	if(L==1)return printf("%lld",n*(n+1)/2),0;
	sort(pos.begin(),pos.end());int p=0,val=0;
	while(true){
		if(que.empty()){if(p==n)break;val=pos[p].fi;}
		for(;p<n&&val==pos[p].fi;p++)que.pb((Node){pos[p].se,pos[p].se,1,1});
		sort(que.begin(),que.end(),cmp);int sz=que.size();vector<Node>tmp(0);
		for(int l=0,r;l<sz;l=r){
			for(r=l+1;r<sz&&que[r].l==que[r-1].r+1;r++);
			int cnt=(r-l)/L;if(!cnt)continue;
			vector<Node>now(0);
			for(int i=l;i<r;i++)now.pb(que[i]);
			ans+=calc(now);now.clear();
			for(int i=0;i<cnt;i++){
				int pl=l+i*L,pr=(i==cnt-1?r-1:pl+L-1);
				now.pb((Node){que[pl].l,que[pr].r,0,0});
			}
			for(int i=l;i<r;i++){
				int tl=i-l+1,tr=r-i;
				if(tr>=L)now[cnt-tr/L].vl+=que[i].vl;
				if(tl>=L)now[tl/L-1].vr+=que[i].vr;
			}ans-=calc(now);for(auto i:now)tmp.pb(i);
		}swap(tmp,que);val++;
	}printf("%lld",ans+n);
	return 0;
}
```

---

