# 「EZEC-11」Unmemorable

## 题目描述

Unputdownable 手中有一个长度为 $n$ 的排列 $a$。

他在练习单调栈的时候用程序对于每一个 $i$ 求出了最大的 $l_i$ 使得 $a_{l_i} < a_i$ 且 $l_i<i$，以及最小的 $r_i$ 使得 $a_{r_i}<a_i$ 且 $r_i>i$。

特别的，若这样的 $l_i$ 不存在，则定义为 $0$，不存在的 $r_i$ 则定义为 $n+1$。

某日 Unputdownable 忘记了排列 $a$，而且只剩余**分别重排**后的 $l$ 和 $r$ 数组了，你能帮助他还原原来的排列 $a$ 吗？

随后由于他发现无法还原 $a$，你只要告诉他有多少种可能的原排列 $a$。 

答案对于 $998244353$ 取模，数据保证至少存在一种方案。

## 说明/提示

**样例解释 1**

一种可能的排列是 $\{2,5,1,3,4\}$，$l$ 数组是 $\{0,1,0,3,4\}$，$r$ 数组是 $\{3,3,6,6,6\}$。

**本题采用捆绑测试。**

- Subtask 1（5 pts）：$n\leq 8$。
- Subtask 2（15 pts）：$r_i\geq n$。
- Subtask 3（15 pts）：$n\leq 2000$，保证存在一个排列 $a$ 满足排列 $a$ 所求出的 $l,r$ 即为给定的。 
- Subtask 4（25 pts）：$n\leq 10^6$，保证存在一个排列 $a$ 满足排列 $a$ 所求出的 $l,r$ 即为给定的。 
- Subtask 5（40 pts）：无特殊限制。 

对于 $100\%$ 的数据，$1 \leq n \leq 10^6$，$0 \leq l_i,r_i \leq n+1$，**数据保证至少存在一种方案**。

## 样例 #1

### 输入

```
5
3 1 0 0 4
6 3 6 3 6
```

### 输出

```
6
```

# 题解

## 作者：yyyyxh (赞：9)

一道思维好题。

首先将题目中所给的 $l_i$ 加一，$r_i$ 减一，发现这就是笛卡尔树的“影响区间”，再观察一下部分分，发现 Subtask 3,4 中说的是“存在一个排列”，但如果是仅仅存在一个排列这挡部分分意义就不大。我们于是大胆猜测对于一个重排后的 $l_i,r_i$ 数组，能确定的笛卡尔树形态是唯一的。

思考 Subtask 3,4 的做法。对 $l_i,r_i$ 建笛卡尔树后相当于要往树上填一些数字 $S=\{1,2,3,\dots,n\}$ ，使其满足小根堆性质。对于当前的备选集合 $S$ ，为了满足小根堆性质，我们必须把 $S$ 中最小的数填到当前的根，然后再把 $S$ 分成两个集合 $S_1,S_2$ 填到左右儿子上。

具体地，设 $f_u$ 表示大小为 $size_u$ 的备选集合 $S$ 填到节点 $u$ 的方案数，那么可以推出：

$$f_u=f_{lson_u}\times f_{rson_u} \times {size_u-1\choose size_{lson_u}}$$

$f_{root}$ 即为答案，这部分子任务的代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int read(){
	//……
}
const int _=1000003;
const int P=998244353;
int inv[_],fac[_],fiv[_];
int n;
int L[_],R[_];
vector<int> g[_];
int f(int l,int r){
	g[l].pop_back();
	if(l+1>=r-1) return 1;
	int p=g[l].empty()?l+1:g[l].back();
	int lc=f(l,p),rc=f(p,r);
	return 1ll*lc*rc%P*fiv[p-l-1]%P*fiv[r-p-1]%P*fac[r-l-2]%P;
}
void solve(){
	for(int i=0;i<n;++i) g[i].clear();
	for(int i=1;i<=n;++i) g[L[i]].emplace_back(R[i]);
	for(int i=0;i<n;++i) sort(g[i].begin(),g[i].end());
	printf("%d\n",f(0,n+1));
}
int main(){
	n=read();fac[0]=fiv[0]=inv[1]=1;
	for(int i=1;i<=n;++i) L[i]=read();
	for(int i=1;i<=n;++i) R[i]=read();
	for(int i=2;i<=n;++i) inv[i]=1ll*inv[P%i]*(P-P/i)%P;
	for(int i=1;i<=n;++i) fac[i]=1ll*i*fac[i-1]%P;
	for(int i=1;i<=n;++i) fiv[i]=1ll*inv[i]*fiv[i-1]%P;
	solve();
	return 0;
}
```

有了 $55$ 分，证明结论正确。

那么对于一个重排后的 $l_i,r_i$ 数组，一定存在一种方式构造出唯一一种笛卡尔树。

再次对题目性质进行观察，抓住重排不变量，也就是每个边界的出现次数，考虑对于笛卡尔树形态的影响。

![](https://cdn.luogu.com.cn/upload/image_hosting/qch6q347.png)

对于上图的笛卡尔树，2 作为右边界出现两次，4 作为左边界出现两次。

一个数 $a_i$ 开始作为右边界出现的时候，就是 $a_{i+1}$ 变成了一个区间的最小值，将序列分割成了 $[l_{i+1},i]$ 和 $[i+2,r_{i+1}]$。$a_i$ 会一直成为右边界直到到达他自己作为一个区间最小值的节点。那么发现笛卡尔树上的深度差 $deep_{i}-deep_{i+1}$ 恰好就是 $i$ 作为右边界的出现次数。左边界同理，只不过是 $deep_{i}-deep_{i-1}$。

由于相邻两数要么 $deep_{i}>deep_{i+1}$ 要么 $deep_{i}<deep_{i+1}$，那么我们就可以用重排后的 $l_i,r_i$ 得到整个 $deep$ 数组的相对大小关系，强制 $deep_1=0$ 后求出 $deep$ 数组直接单调栈建笛卡尔树，再跑上述树形 $DP$ ，这道题也就做完了。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int read(){
	//……
}
const int _=1000003;
const int P=998244353;
int inv[_],fac[_],fiv[_];
int n;
int cL[_],cR[_],a[_],sz[_];
int lc[_],rc[_],stk[_],tp;
int solve(int u){
	if(!u) return 1;
	int lo=solve(lc[u]),ro=solve(rc[u]);
	sz[u]=sz[lc[u]]+sz[rc[u]]+1;
	return 1ll*lo*ro%P*fac[sz[lc[u]]+sz[rc[u]]]%P*fiv[sz[lc[u]]]%P*fiv[sz[rc[u]]]%P;
}
int main(){
	n=read();fac[0]=fiv[0]=inv[1]=1;
	for(int i=1;i<=n;++i) ++cL[read()+1];
	for(int i=1;i<=n;++i) ++cR[read()-1];
	for(int i=2;i<=n;++i) inv[i]=1ll*inv[P%i]*(P-P/i)%P;
	for(int i=1;i<=n;++i) fac[i]=1ll*i*fac[i-1]%P;
	for(int i=1;i<=n;++i) fiv[i]=1ll*inv[i]*fiv[i-1]%P;
	a[1]=0;
	for(int i=2;i<=n;++i){
		if(cL[i]) a[i]=a[i-1]+cL[i];
		if(cR[i-1]) a[i]=a[i-1]-cR[i-1];
	}
	for(int i=1;i<=n;++i){
		while(tp>1&&a[i]<a[stk[tp-1]]) rc[stk[tp-1]]=stk[tp],--tp;
		if(a[i]<a[stk[tp]]) lc[i]=stk[tp],stk[tp]=i;
		else stk[++tp]=i;
	}
	while(tp>1) rc[stk[tp-1]]=stk[tp],--tp;
	printf("%d\n",solve(stk[tp]));
	return 0;
}
```

听说这道题有只用 $l_i$ 数组的做法，希望有大佬可以发题解指教。

---

## 作者：littleKtian (赞：7)

想了大半天发现题意看反了（恼）。

------------
### Part 1：如何求 $l_i$ 和 $r_i$

既然题目给了个单调栈我们就往这方向想。

对 $a$ 建立一个单调递增的单调栈，然后我们可以利用下面的代码求出 $l$ 和 $r$（单调栈内存储下标）。

```cpp
	for(int i=1;i<=n;i++)
	{
		while(zd&&a[z[zd]]>a[i])r[z[zd--]]=i;
		l[i]=z[zd],z[++zd]=i;
	}
	while(zd)r[z[zd--]]=n+1;
```

手玩容易得证。

### Part 2：如何还原

考虑怎么把打乱的 $l$ 和 $r$ 变回去。

观察上面的代码容易发现，如果记 $t_i$ 表示 $i$ 在 $r$ 中出现的次数，那么 $t_i$ 其实就是循环运行到 $i$ 时单调栈弹出的元素个数。

显然如果 $t$ 确定，那么单调栈在每个时刻的状态也是能确定的。

求 $t$ 是简单的，所以我们可以直接求出 $t$ 后对上面代码稍作改造来求出 $l$ 和 $r$。

### Part 3：如何利用 $l$ 和 $r$

由 $l$ 和 $r$ 我们能得到 $O(n)$ 个排列 $a$ 中元素的大小关系。

再次回看一开始求 $l$ 和 $r$ 的代码，我们可以发现 $l$ 和 $r$ 正好覆盖了所有我们在单调栈求解时用到的所有的大小关系。也就是满足这里所有关系的排列 $a$ 个数就是答案。

容易想到从 $i$ 往 $l_i$ 和 $r_i$ 连单向边（$l_i=0$ 和 $r_i=n+1$ 的情况不连），显然这是个 DAG，其拓扑序的方案数就是答案。

### Part 4：如何求答案

一般 DAG 的拓扑序计数目前只有指数级做法，所以我们考虑进一步找性质。

注意到一个点的出边最多两条，考虑能不能把有两条出边的点变成只有一条，这样原图就变成了森林，有 $O(n)$ 的做法计算拓扑序数量。

实际上我们可以证明如果 $l_i\neq 0$ 且 $r_i\neq n+1$，那么必有 $r_{l_i}=r_i$ 或者 $l_{r_i}=l_i$。

>证明：
>
>根据 $l_i$ 和 $r_i$ 的定义，显然有 $a_{l_i}<a_i,a_{r_i}<a_i,\forall j\in(l_i,i)\bigcup(i,r_i),a_j>a_i$。
>
>那么有 $\forall j\in(l_i,r_i),a_{l_i}<a_j,a_{r_i}<a_j$。
>
>因为是排列，显然 $a_{l_i}\neq a_{r_i}$。
>
>于是必有 $r_{l_i}=r_i$ 或者 $l_{r_i}=l_i$。

如果 $r_{l_i}=r_i$，那么实际上我们不需要连 $i$ 到 $r_i$ 的边，也能表示出 $i$ 和 $r_i$ 的大小关系（因为已经有 $i$ 到 $l_i$ 的边和 $l_i$ 到 $r_i$ 的边了）。$l_{r_i}=l_i$ 同理。

于是每个点的出边就被缩到只剩一条了。

剩下来就是 $O(n)$ 的树形 dp 求答案了。

---

## 作者：test13 (赞：4)

考虑题目本身不好计数，思考寻找某些性质或结论来做

比较容易发现对于匹配好的 $l_i$ 和 $r_i$，合法的数列是唯一的，也就是说能唯一对应一棵笛卡尔树，打个表发现是对的，因为是排列，所以如果交换某些 $(p_i,p_j)$ 后相对顺序必然发生改变，笛卡尔树的形态也会变化

现在问题就是求合法匹配的方案数，考虑将 $l_i+1$，$r_i-1$，变成一个数作为最小值的区间，能够发现，是 $n$ 个 $l_i$ 和 $r_i$ 匹配的方案数，画个图，转化成有 $2n$ 个点，$n$ 个点作为左端点，$n$ 个点作为右端点，发现对于任意匹配了合法的 $n$ 个区间后，他们线段的长度总和肯定不会变，证明考虑差分，无论怎么匹配都是对于所有的点，操作 $d_{l_i}+1$ 或 $d_{r_i}-1$，最后还原的数组形态一致

假设现在差分后的 $d$ 已经成原数组了，考虑 $d_i$ 是什么，$d_i$ 实际上就是被多少个点囊括在支配区间里，在笛卡尔树上就是深度

显然 $d_x=1$ 的 $x$ 是最小值，那么 $[1,x)$ 的最小值的 $d_y=2$，$(x,n]$ 同理

归纳一下，就是对于一个区间 $[l,r]$，设区间 $[l,r]$ 的最小值**位置**是 $x$，设 $d_x=t$ 那么 $[l,x)$ 的最小值的 $d$ 就是 $t+1$，$(x,r]$ 的最小值的 $d$ 也是 $t+1$，显然左半边的最小值和右半边的最小值是 $x$ 的儿子，所以我能够很轻松的通过 $d_i$ 还原出笛卡尔树，具体单调栈就好了

答案就容易算了，设当前点 $x$，左子树大小为 $siz_l$，右子树大小为 $siz_r$，贡献是 $\binom{siz_l+siz_r}{siz_l}$，都乘起来就好了

```c++
int n,l[MAXN],r[MAXN],d[MAXN],st[MAXN],top,siz[MAXN],root,ls[MAXN],rs[MAXN];
int fac[MAXN],fiv[MAXN],ans=1;
std::vector<int>nbr[MAXN];
int C(int x,int y){return fac[x]*fiv[y]%mod*fiv[x-y]%mod;}
vd init(){
	fac[0]=fiv[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	fiv[n]=pow(fac[n],mod-2);
	for(int i=n-1;i>=1;i--)fiv[i]=fiv[i+1]*(i+1)%mod;
}
vd link(int u,int v){nbr[u].emplace_back(v);}
vd dfs(int u){
	if(ls[u])dfs(ls[u]);
	if(rs[u])dfs(rs[u]);
	siz[u]+=(siz[ls[u]]+siz[rs[u]]);
}
vd calc(int u){
	if(ls[u])calc(ls[u]);
	if(rs[u])calc(rs[u]);
	ans=ans*C(siz[ls[u]]+siz[rs[u]],siz[ls[u]])%mod;
}
signed main(){
	n=gi();init();
	for(int i=1;i<=n;i++)l[i]=gi(),++d[l[i]+1],siz[i]=1;
	for(int i=1;i<=n;i++)r[i]=gi(),--d[r[i]];
	for(int i=1;i<=n;i++)d[i]+=d[i-1];
	for(int i=1;i<=n;i++){
		while(top&&d[st[top]]>d[i])ls[i]=st[top--];
		if(top)rs[st[top]]=i;
		st[++top]=i;
	}
	root=st[1];
	dfs(root),calc(root);
	printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：Zhao_daodao (赞：2)

# P8180 「EZEC-11」Unmemorable
抽象做法。

## Description

你有一个长度为 $n$ 的排列 $a$。

其中对于每一个位置 $i$，记录两个值 $l_i$，$r_i$。

$l_i$ 表示位置 $i$ 左边的最大的 $x$。其中 $x$ 满足 $a_x<a_i$。

$r_i$ 表示位置 $i$ 右边的最小的 $x$。其中 $x$ 满足 $a_x<a_i$。

现在把序列 $l$ 和序列 $r$ 分别重新排列，求有多少个可能的原序列。

答案对 $998244353$ 取模。

保证至少有一个原序列，换句话说，你不用考虑无解。

## Solution

首先你写一个指数级暴力。然后把所有的排列的 $l$ 数组和 $r$ 数组写出来。

发现，好像每一个排列的 $l$ 和 $r$ 在排序之后也不会相同。

就是说，如果要唯一决定 $l$ 和 $r$，并不需要知道 $l_i$ 和 $r_i$，而是知道数码出现的数量就够了。

证明在别的题解里面有。

---

现在考虑如何还原。

对于 $l$ 数组，如果 $x$ 出现了，那么 $l_{x+1}$ 必定等于 $x$。

> 证明：
>
> 考虑 $a_x$ 和 $a_{x+1}$ 的关系。因为 $a$ 是排列，所以不存在相等的情况。
>
> 如果 $a_x<a_{x+1}$，那么 $l_{x+1}=x$，结论成立。
>
> 如果 $a_x>a_{x+1}$，那么对于所有 $j\in [x+1,n]$，其 $l_j$ 不可能等于 $x$。
>
> 若 $l_j=x$，根据定义，$a_j>a_x$，$a_j<a_{x+1}$，与条件矛盾。
>
> 证毕。

所以每一个数码都可以对应回原来的位置。

考虑多余的数码在那里放置。考虑一个 $l_i$ 数组：`0,0,1,1,1,1,3`。

定义 $l_i$ 当前没有数，此时 $l_i=-1$。

此时根据第一步，还原出数组：`0,1,-1,3,-1,-1,-1`。

直接上结论：从后往前维护所有 $l_i=-1$ 的 $i$，遇到一个 $l_i\ne-1$ 的值，如果 $l_i$ 这个数码没有填完，就直接从栈里弹出若干个位置，直到当前数码填完。

证明从单调栈和大小关系很容易得出，不证明。~~留给读者自证。~~

$r_i$ 的重排类似，不在赘述。

---

你现在得到了原来的 $a$ 数组的 $l_i$ 和 $r_i$。你需要计算 $a$ 的可能的数量。

考虑递归的计算。即当前考虑到区间 $[L,R]$，此时的方案数。

首先，找到当前区间的最小值。

一个点 $i$ 是区间的最小值当且仅当 $l_i<L$ 且 $r_i>R$。

如果当前位置 $j$ 不是最小值，那么 $l_j=i$ 或者 $r_j=i$。

而且一定有 $l_i\le l_j$，$r_i\ge r_j$。因为 $a_j>a_i$，所以判断条件会更弱，$[l_j,r_j]$ 形成的区间肯定更小。

所以，当前区间 $[L,R]$ 的最小值 $i$，满足 $r_i-l_i+1$ 最大。

因为整个区间已经被 $i$ 分割开了，所以左右两边的真正的 $a_i$ 的取值不会相互影响。

所以在剩余的数量 $R-L$ 中选出 $i-L$ 个数作为左边的 $a$，剩余的作为右边的 $a$，就可以了。

转移柿子：
$$
Ans(L,R)=\binom{R-L}{i-L}Ans(L,i-1)Ans(i+1,R)
$$
结束状态就是当 $l\ge r$ 时 $Ans(l,r)=1$。

直接计算，最终答案就是 $Ans(1,n)$。

其中，组合数预处理。还有一个 `RMQ` 问题。

你可以使用 `st` 表，复杂度 $O(n\log n)$，复杂度正确，会被卡空间。

你可以使用线段树，复杂度 $O(n\log^2 n)$，跑不满，可以通过。

## Code

把 `modint` 部分省略了。写的时线段树。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int MAXN=1e6+5,N=1e6;
mint fac[MAXN],inv[MAXN];
inline void init(){
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=fac[i-1]*i;
    inv[N]=fac[N].inv();for(int i=N-1;i>=0;i--)inv[i]=inv[i+1]*(i+1);
}
inline mint C(int n,int m){
	if(n<m||n<0||m<0)return 0;
	return fac[n]*inv[m]*inv[n-m];
}
int n,ll[MAXN],rr[MAXN];
int l[MAXN],r[MAXN],tong1[MAXN],tong2[MAXN];
inline int _mn(int x,int y){
	if((r[x]-l[x]+1)<(r[y]-l[y]+1))return y;
	return x;
}
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
int tr[MAXN<<2];
void build(int l,int r,int q){
	if(l==r){
		tr[q]=l;return ;
	}
	int mid=l+r>>1;
	build(l,mid,ls(q)),build(mid+1,r,rs(q));
	tr[q]=_mn(tr[ls(q)],tr[rs(q)]);
}
int find(int l,int r,int ql,int qr,int q){
	if(ql<=l&&r<=qr)return tr[q];
	int mid=l+r>>1;
	if(ql<=mid&&mid<qr)return _mn(find(l,mid,ql,qr,ls(q)),find(mid+1,r,ql,qr,rs(q)));
	if(ql<=mid)return find(l,mid,ql,qr,ls(q));
	if(mid<qr)return find(mid+1,r,ql,qr,rs(q));
}
inline mint solve(int L,int R){
	if(L>=R)return 1;
	int mn=find(1,n,L,R,1);
	mint ans=C(R-L,mn-L);
	ans*=solve(L,mn-1)*solve(mn+1,R);
	return ans;
}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    init();cin>>n;
    for(int i=1;i<=n;i++)cin>>ll[i],tong1[ll[i]]++;
    for(int i=1;i<=n;i++)cin>>rr[i],tong2[rr[i]]++;
    for(int i=1;i<=n;i++)l[i]=r[i]=-1;
    for(int i=0;i<n;i++)if(tong1[i]){
    	l[i+1]=i;tong1[i]--;
    }
    for(int i=1;i<=n+1;i++)if(tong2[i]){
    	r[i-1]=i;tong2[i]--;
    }
    stack<int>S;
    for(int i=n;i>=1;i--){
        if(l[i]==-1)S.push(i);
        else{
            while(tong1[i-1]){
                l[S.top()]=i-1;
                S.pop();
                tong1[i-1]--;
            }
        }
    }
    stack<int>ed;
    for(int i=1;i<=n;i++){
        if(r[i]==-1)ed.push(i);
        else{
            while(tong2[i+1]){
                r[ed.top()]=i+1;
                ed.pop();
                tong2[i+1]--;
            }
        }
    }
    build(1,n,1);
    cout<<solve(1,n)<<"\n";
}
```

---

## 作者：AbsMatt (赞：1)

### [题目传送器](https://www.luogu.com.cn/problem/P8180)

### [更爽的阅读体验](https://yaohaoyou.github.io/post/P8180-solution/)

## 前言

赛时会了，结果预处理忘优化了，大样例跑得飞快，$O(n^2)$ 假完~~甲烷~~了，喜提暴力分。

## 题意

自己看题面。

## 做法

先大眼暴力，观察结论（我也不会证明，但把表打出来后还比较明显）：

1. $r$ 数组无用
2. 顺序正确的 $l$ 数组唯一
3. 先从大到小排序，对于当前值 $i$，放入第一个 $l_j=0$ 的位置，$j>i$。形成最后的 $l$。

对于第 $3$ 点的观察，可以自己参考别的题解的做法，反正能确定 $l$ 数组即可。

现在已经得到了 $l$ 数组了，$r$ 数组已经固定，有保证有解，所以算出多少个排列 $p$ 满足 $l$ 的限制即可。

其实做到这一步，就完全是[这题](https://www.luogu.com.cn/problem/AT_arc186_b)了，接下来讲一讲具体的做法。

对于当前数组能推出的信息很少，所以先从局部推结论。不难发现在当前 $l$ 数组中 $p$ 最小的位置一定是当前最后一个 $l_i=0$ 的 $i$，证明可以设 $a_k=\min_{i=1}^na_i$，因为是最小值，所以前面不会再有 $p_k<p_i$，故 $l_k$ 一定是 $0$，最后一个 $l_k=0$ 一定会满足前面的 $\forall l_j=0,p_k<p_j$。

推出当前序列的最小值后，序列就又分成了两个独立的区间，因为保证有解，所以 $\forall j>k,p_j\ge k$，将 $i \in [k+1,n]$ 的 $l_i \gets l_i-k$ 后，后面的部分就与前面独立了。接下来就类似于分治的做法，将当前区间分成两段，递归求解。设当前区间为 $[L,R]$，这个区间的最小值已经确定，从剩下的 $R-L$ 个数中选取 $k-L$ 个数作为左边区间，剩下就是右边区间，所以要再乘上 $\binom{R-L}{k-L}$。形式化的，设 $f(L,R)$ 为区间 $[L,R]$ 的分配方案数（数的集合已经固定，相当于离散化后的方案数）。
$$
f(L,R)=\begin{cases}
1 & L>R \\
f(L,k-1)\times f(k+1,R) \times \binom{R-L}{k-L} & L<=R
\end{cases}
$$
想到这里就完成了，实现并不难。注意 $l_k$ 是区间最小值，但并不一定是 $mid$，所以直接做不是 $O(n\times\log_2n)$ 的，而是卡不满的 $O(n^2)$。可以使用 st 表或线段树做 rmq。本题空间要求线性，于是只能使用线段树，复杂度为 $O(n\times \log_2n)$。

## Code

递归求 $f$ 的主要代码如下：

```cpp
void dfs(int l,int r){
    if(l>r)    return;
    int x=-query(all,l,r).se;  // 区间最小值的位置
    mmul(ans,C(r-l,x-l));
    dfs(l,x-1);
    dfs(x+1,r);
}
```

[完整代码](https://www.luogu.com.cn/paste/nea3m78u)

---

## 作者：gdf_yhm (赞：1)

### [P8180](https://www.luogu.com.cn/problem/P8180)

[my blog](https://yhddd123.github.io/post/P8180-ti-jie/)

不同的解法，感觉比较牛。

### 思路

对 $ll_i$ 和 $rr_i$ 排序。直接考虑最小值在哪里，假设为位置 $p$。那么 $[1,p-1]$ 的 $rr_i$ 都 $\le p$，$[p,n]$ 的 $rr_i$ 都 $>p$，$ll_i$ 也有相似的限制。都符合 $ll,rr$ 限制的 $p$ 是唯一的，更进一步，符合 $rr$ 的限制的最右的点和符合 $ll$ 限制的最左的点是同一个点，且就是 $p$。否则不难说明会寄。

那就分治 $[l,r]$，找到 $p$，真实的 $ll_p$ 是 $ll_l=l$，真实的 $rr_p$ 是 $rr_r=r$，平移 $ll[l,p-1]=ll[l+1,p],rr[p+1,r]=rr[p,r-1]$ 后分治 $[l,p-1],[p+1,rr]$，贡献是 $\binom{r-l}{r-p}$。$O(n^2)$ 的分治只需要 $ll$ 或 $rr$ 中的一个数组，会被单调递增递减卡 T。难以快速寻找区间对应的 $p$ 。

但是只要枚举到了 $p$ 可以 $O(1)$ 检查是否合法。从左往右和从右往左同时枚举第一个满足 $ll$ 限制和最后一个满足 $rr$ 限制的点，一找到就退出递归。这样能保证每个区间枚举次数为分治两边的较短的长度，复杂度分析同 [min+sum](https://www.luogu.com.cn/problem/AT_abc282_h)，每个点被枚举一次对应的区间翻倍。注意双指针也要保证严格枚举次数为两边的较短的长度，恰好比当前枚举的位置多 $1$ 即可。

复杂度 $O(n\log n)$。

### code

```cpp
int n,ans=1;
int ll[maxn],rr[maxn];
int fac[maxn],inv[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void sovle(int l,int r,int p1,int p2,int p3,int p4){
	if(l>=r)return ;
	int p=0;
	for(int ir=r,il=l,jr=p4+1,jl=p1-1;ir>=l;ir--,il++){
		while(jr-1>=p3&&rr[jr-1]>ir){
			jr--;
			if(jr-p3<ir-l)break;
		}
		if(ir-l==jr-p3){
			p=ir;
			break;
		}
		while(jl+1<=p2&&ll[jl+1]<il){
			jl++;
			if(jl-p1>il-l)break;
		}
		if(il-l==jl-p1){
			p=il;
			break;
		}
		// cout<<il<<" "<<ir<<" "<<jl<<" "<<jr<<"\n";
	}
	// cout<<l<<" "<<r<<" "<<p<<" "<<p1<<" "<<p2<<" "<<p3<<" "<<p4<<"\n";
	if(p<l||p>r)exit(0);
	ans=ans*C(r-l,r-p)%mod;
	sovle(l,p-1,p1+1,p1+p-l,p3,p3+p-l-1),sovle(p+1,r,p1+p-l+1,p2,p3+p-l,p4-1);
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)ll[i]=read();
	for(int i=1;i<=n;i++)rr[i]=read();
	sort(ll+1,ll+n+1),sort(rr+1,rr+n+1);
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	sovle(1,n,1,n,1,n);
	printf("%lld\n",ans);
}
```

---

## 作者：cppcppcpp3 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P8180)

先考虑 $l_i,r_i$ 没有重排的情况。令 $l_i,r_i$ 分别 $+1,-1$，意义变成 $[l_i,r_i]$ 表示包含位置 $i$ 且 $a_i$ 为区间最大值的极大区间。显然区间两两之间只有**包含和不交**两种关系，套路地考虑**按区间包含关系建树**，限制即父亲节点的值大于儿子节点的值。比较典的树形 dp，记 $f_u$ 表示 $u$ 子树的答案：

$$f_u=\binom{sz(u)-1}{sz(v_1),sz(v_2),\cdots,sz(v_k)}\prod_{i=1}^kf_{v_i}$$

边界是叶子节点的 $f$ 值为 $1$，最终答案就是根节点的答案。其中 $sz$ 表示子树大小，$v_{1\sim k}$ 是 $u$ 的所有儿子。式子的意义是把 $sz(u)$ 个不同的数分配到子树 $u$ 的每个点上，最大的数必须给 $u$，剩下的数分配 $sz(v_i)$ 个给子树 $v_i$。预处理组合数，这部分的时间复杂度为 $O(n)$。

现在考虑怎么建树。自己场上的 naive 做法是对区间按照长度从大到小排序，最大的区间一定是 $[1,n]$。线段树维护接下来对于左端点为 $i$ 的区间，包含它的最短区间编号。每次对区间 $[l_i,r_i]$ 单点查它的父亲、区间覆盖 $[l_i,r_i]$ 为 $i$，时间复杂度 $O(n\log n)$，由于区间要么互相包含要么不交，这样做是对的。

当然加以思考可以发现，建树过程中一个父亲区间，它的所有儿子区间的并恰好比父亲区间缺少一个点，且这个点的 $a_i$ 就是区间最大值，所以实质上我们就是在对排列建笛卡尔树，可以 $O(n)$ 做。（这也说明上述转移中 $k=2$）

最后来考虑 $l_i,r_i$ 重排的情况。这实际上是吓人的，对于存在排列方案的 $\{l_i\},\{r_i\}$，只有**唯一**的 $l_i,r_i$ 的匹配方式。具体来说就是，维护一个栈，从左往右扫一遍，把遇到的 $l$ push 进去，对于一个 $r$ 就取出栈顶和它配对。这满足区间要么包含要么不交的性质，感性证明唯一性，考虑交换两个区间的右端点：

- 两个区间存在包含关系，那么交换 $r$ 后相交。
- 不交的两个区间存在 $l_1\le r_1\le l_2\le r_2$，无法交换 $r$。

证毕。同时上面已经给出了还原出 $\{(l_i,r_i)\}$ 的方法，还原出来后建树 dp 即可。

至于实现上的细节，我自己写 dfs 导致在这里 MLE 了，但是建树时得到每个点的父亲相当于知道了拓扑序，所以直接按照拓扑序逆序 dp 即可，甚至不用显式建树。

```cpp
#include<bits/stdc++.h>
#define FIO(file) freopen(file".in","r",stdin),freopen(file".out","w",stdout)
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=1e6+5;
const int mod=998244353;

static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int wrd(){int x=0,f=1;char c=getchar();while(c<'0' || c>'9'){if(c=='-') f=-1;c=getchar();}while(c>='0' && c<='9') {x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}

int n,f[N],sz[N],dp[N];
struct node{int l,r;}a[N];

int qpw(int a,int b){
	int as=1;
	while(b){
		if(b&1) as=1ll*as*a%mod;
		a=1ll*a*a%mod,b>>=1;
	}
	return as;
}
int fac[N],inv[N];
void init(int n){
	fac[0]=1; for(int i=1;i<=n;++i) fac[i]=1ll*fac[i-1]*i%mod;
	inv[n]=qpw(fac[n],mod-2); for(int i=n;i;--i) inv[i-1]=1ll*inv[i]*i%mod;
}
int C(int n,int m){
	if(n<m || m<0) return 0;
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}

struct SGT{
	#define ls (t<<1)
	#define rs (t<<1|1)
	#define md ((l+r)>>1) 
	int lz[N<<2];
	void mdf(int t,int k){lz[t]=k;}
	void pd(int t){if(lz[t])mdf(ls,lz[t]),mdf(rs,lz[t]),lz[t]=0;}
	void upd(int l,int r,int t,int x,int y,int k){
		if(l>y || r<x) return;
		if(l>=x&&r<=y){mdf(t,k);return;}
		pd(t),upd(l,md,ls,x,y,k),upd(md+1,r,rs,x,y,k);
	}
	int qry(int l,int r,int t,int x){
		if(l==r) return lz[t];
		pd(t); return x<=md?qry(l,md,ls,x):qry(md+1,r,rs,x);
	}
}T;

int st[N],tp;
pii d[N<<1];

signed main(){
	n=wrd(),init(n);
	for(int i=1;i<=n;++i) d[i]={wrd()+1,i};
	for(int i=1;i<=n;++i) d[n+i]={wrd()-1,n+i};
	sort(d+1,d+2*n+1);
	for(int i=1,c=0;i<=2*n;++i){
		if(d[i].se<=n) st[++tp]=d[i].fi;
		else a[++c]={st[tp],d[i].fi},--tp;
	}
	sort(a+1,a+n+1,[&](node x,node y){return x.r-x.l>y.r-y.l;});
	T.upd(1,n,1,1,n,1);
	
	for(int i=2;i<=n;++i){
		int l=a[i].l,r=a[i].r;
		f[i]=T.qry(1,n,1,l);
		T.upd(1,n,1,l,r,i);
	}
	for(int i=1;i<=n;++i) dp[i]=1;
	for(int u=n;u;--u){
		int v=f[u];
		++sz[u],sz[v]+=sz[u];
		dp[v]=1ll*dp[v]*dp[u]%mod;
		dp[v]=1ll*dp[v]*C(sz[v],sz[u])%mod;
	}
	write(dp[1]);
	return 0;
}
```

---

## 作者：takanashi_mifuru (赞：0)

考虑假设第 $i$ 个点左边第一个比他小的点为 $l_i$，则显然区间 $(l_i,i)$ 要么相交要么包含。

那么现在枚举到第 $i$ 个点，对于可选的 $l$ 中，如果他不选择其中最大的，则最大的必然会被后面的某个点选中，则这样的话就会有两个开区间产生交，不合法，所以他强制选择其中标号最大的。

$r$ 数组则是以此类推，我们这样就可以确定 $l$ 数组和 $r$ 数组的取值。

容易发现我们可以用这个东西建笛卡尔树，那么每次决策的分歧就在笛卡尔树的分叉，我们可以用组合数选择把一些数组开，然后就可以了，时间复杂度 $O(n\log n)$ 精细实现可以丢掉 $\log$ 不过我比较懒就直接写了。

```cpp
#include<bits/extc++.h>
#define int long long
using namespace std;
int n;
int L[1000005],R[1000005];
struct node{
    int lt,rt;
}A[1000005];
map<int,int> mp[1000005];
int ans=1;
const int P=998244353;
int power(int x,int y=P-2){
    if(y==0)return 1;
    int tmp=power(x,y>>1);
    if(y&1)return tmp*tmp%P*x%P;
    return tmp*tmp%P;
}
int fac[1000005];
int invfac[1000005];
int C(int n,int m){
    return fac[n]*invfac[m]%P*invfac[n-m]%P;
}
void getans(int lt,int rt){
    if(lt>=rt)return;
    int mid=mp[lt][rt];
    // printf("%lld %lld %lld\n",lt,rt,mid);
    ans=ans*C(rt-lt,mid-lt)%P;
    getans(lt,mid-1);
    getans(mid+1,rt);
    return;
}
signed main(){
    scanf("%lld",&n);
    fac[0]=1;
    for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%P;
    invfac[n]=power(fac[n]);
    for(int i=n;i>=1;i--)invfac[i-1]=invfac[i]*i%P;
    for(int i=1;i<=n;i++){
        scanf("%lld",&L[i]);
    }
    for(int i=1;i<=n;i++){
        scanf("%lld",&R[i]);
    }
    sort(L+1,L+1+n);
    int j=1;
    priority_queue<int> q;
    for(int i=1;i<=n;i++){
        while(j<=n&&L[j]<i){
            q.push(L[j]);
            j++;
        }
        A[i].lt=q.top()+1;
        q.pop();
    }
    sort(R+1,R+1+n);
    j=n;
    for(int i=n;i>=1;i--){
        while(j>=1&&R[j]>i){
            q.push(-R[j]);
            j--;
        }
        A[i].rt=-q.top()-1;
        q.pop();
    }
    for(int i=1;i<=n;i++){
        mp[A[i].lt][A[i].rt]=i;
    }
    getans(1,n);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：modfish_ (赞：0)

虽然我并没有想到笛卡尔树，但是经过仔细思考，我发现我建的好像就是笛卡尔树……

## 思路
本人在体育课上对着单杠瞪了一整节课，终于想出了这道题的做法（虽然十分抽象且复杂）。

首先，记 $cl_x$ 表示 $x$ 在 $l_i$ 中的出现次数，$cr_x$ 表示 $x$ 在 $r_i$ 中的出现次数。

让我们尝试往这个序列中放入最大值 $n$。容易发现，假设我们在位置 $i$ 上放了 $n$，则应有：

- $cl_i=cr_i=0$

- $cl_{i-1}>0,cr_{i+1}>0$

第一条是显然的，因为不存在任何 $a_j$ 会比 $n$ 还大，所以 $n$ 不会作为 $l_j$ 或 $r_j$ 出现。

第二条也是显然的，因为 $a_{i-1}<n,a_{i+1}<n$，所以必定有 $l_i=i-1,r_i=i+1$。

放入后，我们惊喜地发现：在这之后，$n$ 对其他元素都没有影响了。所以，我们可以直接把位置 $i$ 删掉。

接着，问题变成了一个子问题。于是我们可以对这个子问题继续求解。如果可以把这个序列删完，说明方案是存在的，否则不存在。

这个过程可以用一个栈来维护。详见代码。

实际上，在进行的过程中，我们可以唯一确定每一个位置会对应的 $l_i$ 和 $r_i$（在将数填到位置 $x$ 上时，当前序列上它左边相邻的位置一定是 $l_i$，右边相邻的位置一定是 $r_i$）。并且容易发现，所有开区间 $(l_i,r_i)$ 两两之间要么完全包含，要么不交。

于是，我们可以考虑对这些区间关系建成一棵树。每一个区间向最短的、包含它的区间连边。最后拉一个虚点 $0$，将所有根连到它上面。

建树过程也可以用一个栈来维护，详见代码。

回到我们最初的假设：不停地将序列的最大值放进去，然后删掉那个位置。事实上，如果 $(l_i,r_i)$ 包含 $(l_j,r_j)$，那么必须先删掉 $j$ 才能删掉 $i$。这是容易推导的。

也就是说，在删掉父亲前，要先删掉所有儿子。

于是，问题转换为了：有一棵树，每次可以删掉一个叶子，问有多少种删除方案？

设 $dp_x$ 表示将 $x$ 及其子树全部删掉的方案数。

实际上，一个方案实质上是 $x$ 子树内所有点编号的一个排列 $p_{x,i}$。只要这个排列中，元素的相对位置不发生改变，那么这个方案就是合法的。

考虑从 $x$ 的儿子 $j$ 转移。我们不妨先令 $p_{x,i}$ 为空，然后不断把 $p_{j,i}$ 合并上来。每次合并时，我们可以在不打乱 $p_{x,i}$ 和 $p_{j,i}$ 内部元素的顺序的情况下，任意地将 $p_{j,i}$ 中的元素插入 $p_{x,i}$。不难发现这总共有 $\binom{now}{siz_j}$ 种方案。其中，$now$ 表示算上 $j$，当前处理过的所有儿子的子树大小之和。

于是这么转移就可以了。复杂度 $O(n)$。

其实这棵树本质上就是笛卡尔树。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 1e6 + 5, p = 998244353;

int cl[maxn], cr[maxn], lt[maxn], rt[maxn];
int st[maxn], tp = 0, st2[maxn], tp2 = 0;
int head[maxn], nxt[maxn], to[maxn], cnt = 0, siz[maxn];
ll dp[maxn], fac[maxn], infa[maxn];

ll qpow(ll a, ll x){
	ll res = 1;
	while(x){
		if(x & 1) res = res * a % p;
		a = a * a % p;
		x >>= 1;
	}
	return res;
}
ll C(int n, int m){
	return fac[n] * infa[m] % p * infa[n - m] % p;
}
void match(int u, int v){
	nxt[++ cnt] = head[u], to[cnt] = v, head[u] = cnt;
}
void dfs(int x){
	siz[x] = dp[x] = 1;
	for(int i = head[x]; i; i = nxt[i]){
		int j = to[i];
		dfs(j);
		siz[x] += siz[j];
		dp[x] = dp[x] * dp[j] % p * C(siz[x] - 1, siz[j]) % p;
	}
}

int main(){
	int n;
	scanf("%d", &n);
	fac[0] = infa[0] = 1;
	for(int i = 1; i <= n; i ++) fac[i] = fac[i - 1] * i % p;
	infa[n] = qpow(fac[n], p - 2);
	for(int i = n - 1; i >= 1; i --) infa[i] = infa[i + 1] * (i + 1) % p;
	for(int i = 1; i <= n; i ++){
		int l;
		scanf("%d", &l);
		cl[l] ++; 
	}
	for(int i = 1; i <= n; i ++){
		int r;
		scanf("%d", &r);
		cr[r] ++; 
	}
	bool fl = false;
	for(int i = 1; i <= n; i ++){
		st[++ tp] = i;
		while(tp && cl[st[tp]] == 0 && cr[st[tp]] == 0){
			int x = st[tp --];
			lt[x] = st[tp], rt[x] = i + 1;
			if(cl[lt[x]]) cl[lt[x]] --;
			else fl = true;
			if(cr[rt[x]]) cr[rt[x]] --;
			else fl = true;
			if(fl) break;
			while(tp2 && lt[x] <= lt[st2[tp2]] && rt[st2[tp2]] <= rt[x]) match(x, st2[tp2 --]);
			st2[++ tp2] = x;
		}
		if(fl) break;
	}
	if(fl){
		printf("0\n");
		return 0;
	}
	dfs(st2[tp2]);
	printf("%lld\n", dp[st2[tp2]]);
	return 0;
}
```

---

## 作者：liujy_ (赞：0)

首先，对于一个确定的排列，我们发现 $n$ 个 $l_i$ 为左端点 $i$ 为右端点的区间一定只会构成包含或者不交的关系，这个是容易证明的。具体可以考虑如果两个区间相交但不包含的话就不符合定义了。   
然后我们想对于一个给定重排过后的 $l$ 序列，从 $1$ 开始尝试确定每一个位置原本的 $l_i$。首先 $l_i$ 一定是小于 $i$ 的，然后我们把 $l$ 序列中所有小于 $i$ 且还没被选择的部分都拿出来，这个时候我们发现真实的 $l_i$ 一定是取到拿出来的数里面最大的数。  
考虑如何证明这个结论。首先 $i$ 前面的对应的 $l_i$ 都已经确定了，那么剩下的还未被选择的数只能放到 $i$ 或 $j$ 满足 $j$ 大于 $i$ 的 $l_i$ 或者 $l_j$ 中。这个时候 $l_i$ 如果不选择能选的数里面最大的数，则一定会产生两个不存在包含关系并且相交的区间，那就不合法了。   
所以可以先给 $l$ 排序，然后拿一个栈，每次把小于 $i$ 的数丢进栈里，然后 $l_i$ 取栈顶。   
$r$ 序列也是同样的道理。  
通过上述的构造可以看出原本的 $l,r$ 一定也是唯一的。然后我们可以唯一确定最小值的位置，找出最小值之后就把序列分成了相互独立的两个区间，又可以分别找到两个区间最小值的位置，这样递归的过程实际上是建立了排列的笛卡尔树。在树结构已经确定了的情况下合法的排列可以简单计算。具体其实就是这个树结构合法拓扑序的个数。    

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5,mod=998244353;
int n,l[N],r[N],top,st[N],L[N],R[N],ls[N],rs[N],fac[N],inv[N];
int ksm(int a,int b){int s=1;
	for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)s=1ll*s*a%mod;
	return s;
}
int C(int n,int m){return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;}
int dfs(int l,int r,int x){
	if(l>=r)return 1;
	int s1=dfs(l,x-1,ls[x]),s2=dfs(x+1,r,rs[x]);
	return 1ll*s1*s2%mod*C(r-l,x-l)%mod;
}
int read(){int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return x*f;
}
int main(){fac[0]=1;
	for(int i=1;i<=N-1;i++)fac[i]=1ll*fac[i-1]*i%mod;
	inv[N-1]=ksm(fac[N-1],mod-2);
	for(int i=N-1;i>=1;i--)inv[i-1]=1ll*inv[i]*i%mod;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)l[i]=read();
	for(int i=1;i<=n;i++)r[i]=read();
	sort(l+1,l+n+1),sort(r+1,r+n+1),reverse(r+1,r+n+1);
	int j=0;
	for(int i=1;i<=n;i++){
		while(j+1<=n&&l[j+1]<i)j++,st[++top]=l[j];
		L[i]=st[top--];
	}
	j=0,top=0;
	for(int i=n;i>=1;i--){
		while(j+1<=n&&r[j+1]>i)j++,st[++top]=r[j];
		R[i]=st[top--];
	}
	int rt=0;
	for(int i=1;i<=n;i++){
		if(L[i]==0&&R[i]==n+1)rt=i;
		else if(R[i]==n+1)rs[L[i]]=i;
		else if(L[i]==0)ls[R[i]]=i;
		else if(L[R[i]]==L[i])ls[R[i]]=i;
		else rs[L[i]]=i;
	}
	printf("%d\n",dfs(1,n,rt));
	return 0;
}

```

---

## 作者：Inui_Sana (赞：0)

挺简单的，场上 30min 做出来了。

首先看这个题就大概能猜到和单调栈和笛卡尔树有关系。所以先考虑把 $l_i,r_i$ 转化成更好一点的限制。

考虑得到 $l_i$ 可以用单调栈处理，$l_i$ 本质上就是有多少元素在加进 $i$ 时出栈了。于是枚举 $i=n\to 1$，可以根据 $l_j=i$ 的个数还原出单调栈。

据此，我们又可以得到若干个形如 $a_i>a_j$ 的限制，具体地，若一个 $i$ 在 $j$ 加入时出栈，则 $a_i<a_j$。若 $j$ 的出栈进行完后，栈中还有元素，设栈顶为 $x$，则 $a_x<a_j$。

这样根据 $l_i,r_i$ 可以得到若干限制，连边则变成了拓扑序计数问题。但是 DAG 的拓扑序计数是经典 NP 问题。于是再进一步挖掘性质。

仔细想想，会发现其实是不可能有两个 $deg=0$ 且互相有影响的点入队的，这是因为如果有这样的两个点，又不存在 $a_i$ 相同，于是一定会有其中一个小于另一个。也就输说要不其中一个在另一个的子树内，要不两个点会被一个更小的 $a_i$ 隔开。

所以这个 DAG 本质上是一棵树，其实也就是笛卡尔树。剩下的就是树的拓扑序计数，简单 dp 计数即可。

code：

```cpp
bool Mbe;
int n,m,top,deg[N],a[N],b[N],st[N],frm[N],q[N];
int cur,dp[N],siz[N],dfn[N],rk[N];
bool vis[N];
int fac[N],ifac[N];
vector<int> E[N];
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<2];
il void add(int u,int v){
	deg[v]++;
	e[++tot]={v,head[u]},head[u]=tot;
}
il int Mod(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
il int binom(int x,int y){
	if(x<0||y<0||x<y){
		return 0;
	}
	return 1ll*fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}
il int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1){
			ret=1ll*ret*x%mod;
		}
		x=1ll*x*x%mod,y>>=1;
	}
	return ret;
}
void initFac(int n){
	fac[0]=1;
	rep(i,1,n){
		fac[i]=1ll*fac[i-1]*i%mod;
	}
	ifac[n]=qpow(fac[n],mod-2);
	drep(i,n-1,0){
		ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
	}
}
void dfs(int u){
	dp[u]=1,vis[u]=1;
	for(int v:E[u]){
		if(vis[v]){
			continue;
		}
		dfs(v),siz[u]+=siz[v];
		dp[u]=1ll*dp[u]*dp[v]%mod*binom(siz[u],siz[v])%mod;
	}
	siz[u]++;
}
void Yorushika(){
	read(n);
	rep(i,1,n){
		int x;read(x);
		a[x]++;
	}
	drep(i,n,1){
		rep(j,1,a[i]){
			add(i,st[top--]);
		}
		if(top){
			add(st[top],i);
		}
		st[++top]=i;
	}
	rep(i,1,n){
		int x;read(x);
		b[x]++;
	}
	top=0;
	rep(i,1,n){
		rep(j,1,b[i]){
			add(i,st[top--]);
		}
		if(top){
			add(st[top],i);
		}
		st[++top]=i;
	}
	int rt=0;
	int l=1,r=0;
	rep(i,1,n){
		if(!deg[i]){
			q[++r]=i,rt=i;
		}
	}
	while(l<=r){
		int u=q[l++];
		dp[u]=1,rk[dfn[u]=++cur]=u;
		go(i,u){
			int v=e[i].to;
			frm[v]=u;
			if(!--deg[v]){
				q[++r]=v;
			}
		}
	}
	initFac(n);
	drep(i,n,1){
		int u=rk[i],v=frm[u];
		siz[u]++,siz[v]+=siz[u];
		dp[v]=1ll*dp[v]*dp[u]%mod*binom(siz[v],siz[u])%mod;
	}
	printf("%d\n",dp[rt]);
}
bool Med;
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：Prean (赞：0)

如果 $l,r$ 数组是没有被乱序，我们很容易能 $O(n)$ 建笛卡尔树求出答案。且因为 $a$ 数组是排列所以笛卡尔树形态唯一。

但是这里 $l,r$ 打乱了，题目保证至少存在一种方案。

我们发现出题人非常好心给了样例解释，于是看一下样例解释，发现重排后的 $(l_i,r_i)$ 的区间，根节点只会被一个区间包含。

于是我们就可以求出当前根节点后，将 $l,r$ 分到两边去，然后递归建笛卡尔树，这样建出来的树一定是唯一的。

建树办法有很多，可以线段树区间减区间查询最值 $O(n\log n)$。

思考如何线性建树。如果我们把每个正确排序的 $(l_i,r_i)$ 区间集体加一，那么我们得到的就是对应深度的数组。我们可以用这个深度数组得到笛卡尔树的 BFS 序。

我们反向遍历 BFS 序，使用并查集维护深度大于 $k$ 的节点构成的森林，遍历到节点 $u$ 时只需要看 $u+1$ 和 $u-1$ 的联通块最浅节点深度是否比自己恰好大 $1$ 即可。

复杂度 $O(n\alpha(n))$。
```cpp
#include<cstdio>
#include<cctype>
const int M=1e6+5,mod=998244353;
int n,d[M],sz[M],fa[M],inv[M];int CB[M],id[M];
inline int read(){
	int n(0);char s;while(!isdigit(s=getchar()));while(n=n*10+(s^48),isdigit(s=getchar()));return n;
}
inline int Find(int u){
	return fa[u]==u?u:fa[u]=Find(fa[u]);
}
inline void Merge(int x,int y){
	if(sz[x=Find(x)]<sz[y=Find(y)])x^=y^=x^=y;fa[y]=x;sz[x]+=sz[y];
}
signed main(){
	int ans(1);n=read();inv[1]=1;
	for(int i=2;i<=n;++i)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<=n;++i)++d[read()+1];for(int i=1;i<=n;++i)--d[read()];
	for(int i=1;i<=n;++i)sz[i]=1,fa[i]=i,ans=1ll*ans*i%mod;
	for(int i=1;i<=n;++i)++CB[d[i]+=d[i-1]];
	for(int i=1;i<=n;++i)CB[i]+=CB[i-1];
	for(int i=n;i>=1;--i)id[CB[d[i]]--]=i;
	for(int i=n;i>=1;--i){
		const int u=id[i];
		if(d[u-1]>d[u])Merge(u-1,u);if(d[u]<d[u+1])Merge(u,u+1);ans=1ll*ans*inv[sz[Find(u)]]%mod;
	}
	printf("%d",ans);
}
```

---

## 作者：NATO (赞：0)

很好的一道计数题，但有人场上因为循坏边界而写挂了。

### 思路浅析：

（下默认 $l$ 数组均自增 $1$，$r$ 数组均自减 $1$。）

考虑题目中未打乱的一个 $[l_i,r_i]$ 的意义即为 $a_i$ 是区间 $[l_i,r_i]$ 的最小值。

对于每个数都求出这样一个东西让我们想到了笛卡尔树。

但是 $l,r$ 被分别重排过，似乎我们并不能得到重排前的笛卡尔树，该怎么办呢？

我们在这里断言：重排前的笛卡尔树有且仅有一种形态！

下面笔者将通过唯一构造出该笛卡尔树证明这一结论。

考虑强行构造笛卡尔树。

如果我们能够不断地找到一个区间的最小值，我们就构造出了笛卡尔树。

我们先考虑如何找到全局最小值。

考虑如何用我们得到的信息表示“全局最小值”这一条件。

考虑在全局最小值左边的那些数的 $r$ 都必然 $<$ 全局最小值的位置（下设为 $x$），即对 $r$ 做前缀和（下设为 $sr$）有 $sr_{x-1}=x-1$。

同理可知对 $l$ 做后缀和（下设为 $sl$）后有 $sl_{x+1}=n-x$。

考虑 $sr_{x-1}=x-1$ 和 $sl_{x+1}=n-x$ 的意义，容易发现一个位置 $i$ 满足 $sr_{i-1}=i-1$ 则该位置必然是一个前缀最小值（考虑它左边的那些数的 $r$ 都被它“拦”下来了），同理可得满足 $sl_{i+1}=n-i$ 的位置 $i$ 必然是一个后缀最小值。

既是前缀最小值又是后缀最小值，这显然只有最小值才可能满足的条件！

冷静下来考虑，既是前缀最小值又是后缀最小值说明它必然是最后一个前缀最小值！

所以我们只要找到最后一个满足 $sr_{i-1}=i-1$ 的 $i$ 即可，$l$ 毛用没有。

考虑一般化上述解法建笛卡尔树。

考虑我们需要快速求出区间 $[l,r]$ 的最小值位置，考虑由于我们是分治到这个位置的，所以 $l-1$ 必然是当前节点笛卡尔树的祖先，左边的 $r$ 都被“拦下来了”，所以 $sr_{i-1}-sr_{l-1}$ 必然只包含了区间 $[l,i-1]$ 的 $r$。

条件即可写为满足 $sr_{i-1}-sr_{l-1}=(i-1)-(l-1)$ 的最大 $<r$ 的 $i$。

套路地，将 $i-1$ 和 $l-1$ 分置两边，化为 $sr_{i-1}-(i-1)=sr_{l-1}-(l-1)$。

开桶存 $sr_{i}-i$ 相同的值，用 $sr_{l-1}-(l-1)$ 的那个桶二分找到最大 $<r$ 的 $i$ 即可 $O(\log n)$ 找到一个区间的最小值位置。

由是则可以 $O(n\log n)$ 递归建笛卡尔树矣。

上述过程显然是唯一确定地还原了重排前的笛卡尔树。

求一颗笛卡尔树对应的排列数是典，考虑子树 DP 合并左右儿子：

$dp_i=dp_{ls_i}\times dp_{rs_i}\times C_{sz_{ls_i}+sz_{rs_i}}^{sz_{ls_i}}$

组合意义过于显然，懒得讲了。

于是我们只使用 $r$ 以 $O(n\log n)$ 解决了此题。

#### 参考代码：

在此对煞笔出题人开闹餐 $128$ MB 空间卡递归栈空间的行为表示强烈抗议！

代码使用了 `queue` 代替递归实现。


```cpp
#include<bits/stdc++.h>
#define ll int
using namespace std;
const int MOD=998244353,MAXN=1000000;
int n,r[1000005];
int sr[1000005];
vector<int>c[2000005];
ll dp[1000005];
ll f[1000005],inv[1000005];
ll C(ll n,ll m)
{
	return f[n]*1ll*inv[m]%MOD*1ll*inv[n-m]%MOD;
}
ll ls[1000005],rs[1000005];
ll lv;
ll qpow(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1)res=res*1ll*a%MOD;
		a=a*1ll*a%MOD;b>>=1;
	}
	return res;
}
struct px
{
	ll l,r,where;
}a[1000005];
ll cot;
queue<px>k;
#define ls(id) ls[id]
#define rs(id) rs[id]
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	ll cs;
	for(ll i=1;i<=n;++i)cin>>cs;
	for(ll i=1;i<=n;++i)cin>>r[i],--r[i],++sr[r[i]];
	for(ll i=1;i<=n;++i)sr[i]+=sr[i-1];
	f[0]=1;
	for(ll i=1;i<=n;++i)f[i]=f[i-1]*1ll*i%MOD;
	inv[n]=qpow(f[n],MOD-2);
	for(ll i=n-1;i>=0;--i)inv[i]=inv[i+1]*1ll*(i+1)%MOD;
	ll mw=0;
	for(ll i=n-1;i>=0;--i)
		if(sr[i]==i)
		{
			mw=i+1;break;
		}
	for(ll i=0;i<n;++i)
	c[sr[i]-i+MAXN].emplace_back(i);
	k.push((px){1,n,mw});
	while(!k.empty())
	{
		px now=k.front();k.pop();
		ll where=now.where,l=now.l,r=now.r;
		if(l==r)
		{
			dp[where]=1;continue;
		}
		a[++cot]=now;
		if(where!=l)
		{
			lv=MAXN+sr[l-1]-(l-1);
			ll lid=lower_bound(c[lv].begin(),c[lv].end(),where-1)-c[lv].begin();
			--lid;lid=c[lv][lid]+1;
			ls[where]=lid;
			if(l!=where-1)
			k.push((px){l,where-1,lid});
			else dp[l]=1;
		}
		if(where!=r)
		{
			lv=MAXN+sr[where]-where;
			ll rid=lower_bound(c[lv].begin(),c[lv].end(),r)-c[lv].begin();
			--rid;rid=c[lv][rid]+1;
			rs[where]=rid;
			if(where+1!=r)
			k.push((px){where+1,r,rid});
			else dp[r]=1;
		}
	}
	for(ll i=cot;i;--i)
	{
		ll where=a[i].where,l=a[i].l,r=a[i].r;
		if(ls(where)&&rs(where))
		{
			ll lsz=(where-1)-l+1,rsz=r-where;
			dp[where]=dp[ls(where)]*1ll*dp[rs(where)]%MOD*C(lsz+rsz,lsz)%MOD;
		}
		else if(ls(where))dp[where]=dp[ls(where)];
		else dp[where]=dp[rs(where)];
	}
	cout<<dp[mw];
}//考虑可否建出笛卡尔树？（如何还原 l,r？） 
//若能则转化为放球问题
//建树过程证明考虑前缀最小值和后缀最小值有且仅有一个交？
```

---

## 作者：unputdownable (赞：0)

通过大量的打表可以猜出一个结论：

> 重排后的 $l$ 和 $r$ 数组对应唯一一种未重排的 $l$ 和 $r$。

对于这个结论的证明，可能先解题后证更为直观。

--------

假设我们能直接得到未重排的 $l$ 和 $r$ 数组，思考 $l_i$ 和 $r_i$ 的意义。

这说明 $\forall\ l_i<k<r_i$，$a_k \ge a_i$。

**考虑每一个 $i$ 作为上式中 $k$ 的出现次数**，记为 $cnt_i$。

则易得如果 $a_i=1$，$cnt_i=1$。

分治到 $1$ 的左右两侧，则这两个区间的最小值的 $cnt_i=2$，其中 $1$ 次是因为它自己，$1$ 次因为序列中的 $1$。

不会存在一个和它在 $1$ 的同侧且更小的值，因为这样就违背了最小值的定义。

继续递归，容易证明这样递归的子区间中，$cnt_i$ 最小的位置 $a_i$ 也最小。

那么如果能得到 $cnt$ 数组，我们就能找到一个[笛卡尔树](https://baike.baidu.com/item/%E7%AC%9B%E5%8D%A1%E5%B0%94%E6%A0%91/7579802)的结构。

--------

有了笛卡尔树后计数就显得十分简单，因为排列的笛卡尔树一定是二叉的。

其两个子树完全是独立的，所以任何一种将数分入两个子树的方案都是合法的，每个节点上的方案数就是

$$\binom{siz_1}{siz_1+siz_2}$$

其中 $siz_{1,2}$ 表示两个子树的大小。

序列的方案数就是全部乘起来。

--------

对于求 $cnt$ 数组，每次加一个区间，直接用差分维护即可（毕竟是静态的）。

转念一想，重排对如何差分并没有任何影响。

这样，一组重排后的 $l$ 和 $r$ 数组对应一棵唯一的笛卡尔树，于是也就对应唯一的未重排的 $l$ 和 $r$ 了。

每个部分的复杂度都是线性的，所以总复杂度也是线性的。

--------

**Code：**

```cpp
long long n, Ans = 1;
int del[1000006];
int stk[1000006], siz[1000006], top;
int lch[1000006], rch[1000006];
void dfs(int x) {
    if (lch[x]) dfs(lch[x]);
    if (rch[x]) dfs(rch[x]);
    Ans = Ans * C(siz[lch[x]], siz[rch[x]]) % p;
    siz[x] += siz[lch[x]] + siz[rch[x]];
}
signed main() {
    n = read();
    init(n);
    for (int i = 1; i <= n; ++i) ++del[read() + 1];
    for (int i = 1; i <= n; ++i) --del[read()];
    for (int i = 1; i <= n; ++i) del[i] += del[i - 1];
    for (int i = 1; i <= n; ++i) {  // 建立笛卡尔树
        siz[i] = 1;
        while (top && del[stk[top]] > del[i]) lch[i] = stk[top--];
        if (top) rch[stk[top]] = i;
        stk[++top] = i;
    }
    dfs(stk[1]);
    write(Ans); puts("");
    return 0;
}
```

--------

是很小清新的一道题，对吧。

另外有一种只用 $l$ 的做法，可以去看其他人的题解，这里就不赘述了。

---

