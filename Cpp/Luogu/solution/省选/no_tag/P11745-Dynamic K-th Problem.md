# Dynamic K-th Problem

## 题目背景

> 萤火穿过风 融化成飞光 就在你眼眸盛放

## 题目描述

小 D 发现了一群萤虫，萤群中有 $n$ 个萤虫且按照顺序排成一行并将其从 $1$ 从 $n$ 编号。小 D 非常厉害，他一眼就看出这 $n$ 个萤虫的光度，且这些萤虫的亮度值是 $1\sim n$ 的一个排列。小 D 想找一些萤虫，让它们共同编织出如梦似幻的璀璨光幕，具体的，他需要一个 **萤虫区间**。

小 D 对 **萤虫区间** 定义苛刻：至少得有 $k$ 个萤虫且这些萤虫编号连续。

小 D 十分欣赏萤虫的光芒，他定义编号从 $L$ 到 $R$ 的萤虫区间的总体光度值为这些萤虫的光度值中的第 $m$ 大数。小 D 给定了 $Q$ 个指标，每个指标给定一个数 $x$，寻找一个 **萤虫区间** 使得这个区间的总体光度值大于等于 $x$。当然，这种区间是很多的，你需要帮小 D 数有多少这样的区间。


## 说明/提示

**【样例解释 $\mathbf 1$】**

萤虫从 $1$ 到 $n$ 的光度值为：$5,4,2,3,1$。总共有 $6$ 个萤虫区间，要求区间第 $2$ 大值，分别是：
* 编号 $1$ 至 $3$ 构成的萤虫为 $[5,4,2]$，总体光度值为 $4$。
* 编号 $2$ 至 $4$ 构成的萤虫为 $[4,2,3]$，总体光度值为 $3$。
* 编号 $3$ 至 $5$ 构成的萤虫为 $[2,3,1]$，总体光度值为 $2$。
* 编号 $1$ 至 $4$ 构成的萤虫为 $[5,4,2,3]$，总体光度值为 $4$。
* 编号 $2$ 至 $5$ 构成的萤虫为 $[4,2,3,1]$，总体光度值为 $3$。
* 编号 $1$ 至 $5$ 构成的萤虫为 $[5,4,2,3,1]$，总体光度值为 $4$。

共有 $5$ 次询问，询问指标分别是 $2,2,2,0,2$，则答案分别是：$6,6,6,6,6$。则总异或值为 $6$。

**【样例解释 $\mathbf 2$】**

萤虫从 $1$ 到 $n$ 的光度值为：$3,1,4,2,5,6$。

共有 $5$ 次询问，询问指标分别是 $1,5,1,4,6$，答案分别是：$10,4,10,7,0$。则总异或值为 $3$。

**【样例解释 $\mathbf 3$】** 该数据满足 `Subtask 4` 的限制。具体求解不做解释。请注意整形溢出相关问题。

**【样例解释 $\mathbf 4$】** 该数据满足 `Subtask 5` 的限制。具体求解不做解释。

**【样例解释 $\mathbf 5$】** 该数据满足 `Subtask 8` 的限制。具体求解不做解释。


---


**【数据规模与约定】**


**本题开启子任务捆绑测试**。本题输入输出量一点不大，但请注意优化常数。本题自动开启 O2 优化。



* Subtask 1（10 pts）：$m\leq n\leq 100$，$Q\leq 100$。
* Subtask 2（10 pts）：$m\leq n\leq 1000$，$Q\leq 100$。
* Subtask 3（18 pts）：$n\leq 10^5$，$m\leq 100$。
* Subtask 4（9 pts）：$n\leq 10^6$，$m=1$。
* Subtask 5（9 pts）：$n\leq 10^6$，$m=2$。
* Subtask 6（15 pts）：$n\leq 10^6$，$k=m\leq 100$。
* Subtask 7（7 pts）：$n\leq 10^6$，$m\leq 100$，$0\leq x\leq 1$。
* Subtask 8（22 pts）：$n\leq 10^6$，$m\leq 100$。

对于所有测试点满足 $1\leq m\leq k\leq n\leq 10^6$，$m\leq \min\{1000,n\}$，$1\leq a_i\leq n$，$1\leq Q\leq 10^6$，$1\leq B\leq 10^9$。


## 样例 #1

### 输入

```
5 3 2 999 1
5```

### 输出

```
6```

## 样例 #2

### 输入

```
6 3 2 998 1
5```

### 输出

```
3```

## 样例 #3

### 输入

```
1000000 10000 1 998244353 4
1000000```

### 输出

```
306558155574```

## 样例 #4

### 输入

```
1000000 10000 2 998244353 5
1000000```

### 输出

```
39831215473```

## 样例 #5

### 输入

```
1000000 100000 100 1231 8
1000000```

### 输出

```
170979323511```

# 题解

## 作者：Kingna (赞：2)

## Subtask #1~2

考虑 $O(Qn^2\log n)$ 的暴力，期望得分 $20$ 分。

## Subtask #7

$0\leq x\leq 1$ 答案为区间总数。且所有询问答案相等，求异或值时，如果 $Q$ 为偶数，答案就是 $0$。实际上在数据中 $Q$ 确实是偶数。

## Subtask #4~5

询问的是一个后缀，直接预处理。考虑第 $k$ 大值至多 $n$ 种，那么对每一个 $a_i$ 处理出有多少个区间的第 $m$ 大值为 $a_i$，则等于 $a_i$ 的区间个数就可以求解。查询的时候，直接二分寻找答案。

考虑到区间 $[l,r]$ 用 $a_i$ 作为第 $m$ 大值，那么区间 $[l,r]$ 中就恰好有 $m-1$ 个数大于 $a_i$。那么我们找到比 $a_i$ 大的位置。可能有下列 $m$ 种情况：

* 左边有 $m-1$ 个比 $a_i$ 大，右边有 $0$ 个比 $a_i$ 大。
* 左边有 $m-2$ 个比 $a_i$ 大，右边有 $1$ 个比 $a_i$ 大。
* 以此类推。左边有 $0$ 个比 $a_i$ 大，右边有 $m-1$ 个比 $a_i$ 大。

不难发现，还需要解决区间长度大于等于 $K$ 的问题。这等价于左端点从 $[L_1,R_1]$ 中选择，右端点从 $[L_2,R_2]$ 中选择，区间长度大于等于 $K$ 的选择方案数。可以用数学方法在 $O(1)$ 时间内求解。

现在只需要找到比 $a_i$ 大的位置。如果花费 $O(\log n)$ 时间去找每一个位置，比如 ST 表或线段树，则总复杂度为 $O(nm\log n)$。期望得分 $56$。

## Subtask #8

用链表存储所有数字。按照 $a_i$ 从小到大扫的顺序，如果当前 $a_i$ 计算完毕，直接从链表中删除。此时链表中剩余的数字就是大于 $a_i$ 的数。

查找比 $a_i$ 大的位置时，只需要左跳右跳就行。复杂度 $O(nm)$。

期望得分 $100$。

---

## 作者：AL8624 (赞：1)

赛时写巨大分讨被卡常，卡了非常久，写题解记录一下。

先考虑忽略区间长度限制：

从大到小加入所有数，那么要求第 $m$ 大是 $x$ 的区间个数就可以在加入 $x$ 的时候，枚举所有恰含 $m$ 个已加入的数，且包含 $x$ 的所有区间。

我们可以通过枚举最左端已加入的数来完成这一点，这样最右端的已加入的数就被确定了，那么总共区间个数就是 $左端点合法位置个数 \times 右端点合法位置个数$。

如果考虑区间长度限制，那么再容斥掉不合法的区间即可，详见代码。

由于要求必定包含 $x$，那么想办法用数据结构维护 $O(m)$ 插入一个数、$O(m)$ 获取与它左右相邻的总共 $2\times m$ 个数，枚举的复杂度为 $O(m)$，总复杂度为 $O(nm)$。

|数据结构|合适位置插入一个数的复杂度|获取左右相邻 $2\times m$ 个数复杂度|总复杂度|运行时间|
|-|-|-|-|-|
|平衡树 / set|$O(\log n)$|$O(m)$|$O(n\log n+nm)$|11s|
|链表 / list|$O(1)$|$O(m)$|$O(nm)$|9s|
|bitset|$O(1)$|期望均摊 $O(\frac{m\ln n}{\omega})$|$O(nm+\frac{nm\ln n}{\omega})$|1s|

放一下 list 和 bitset 的核心代码，list 的一直没卡过去，bitset 甚至是最优解第一页。。

list：

```cpp
auto erer=IT[pre[i]];++erer;
auto it=IT[mp[i]]=pos.insert(erer,mp[i]),itb=it;
vector<int>t;t.reserve(2*m+3);
t.push_back(mp[i]);
int cntt=m;
while(it!=pos.begin()&&(cntt--))t.push_back(*(--it));
reverse(t.begin(),t.end());
cntt=m,it=itb;
while((++it)!=pos.end()&&(cntt--))t.push_back(*it);
for(int j=1ll;j+m<t.size();++j){
    const int L=t[j-1]+1,R=t[j+m]-1;
    const int l=t[j],r=t[j+m-1];
    if(R-L+1<k)continue;
    ans+=(l-L+1)*(R-r+1);
    if(r-l+1<k){// 容斥
        int k1=k-(r-l+1);
        ll ewrwe=0,s1=0,s2=0;
        int a=l-L,b=R-r+1;
        if(max(0ll,k1-b)<=min(k1,a)){
            ll t=min(k1,a)-max(0ll,k1-b)+1;
            ans-=t*(k1-min(k1,a)+k1-max(0ll,k1-b))/2;
        }
        ans-=max(k1-b,0ll)*b;
    }
}
xo^=fac[i]?ans:0;
```

bitset：

```cpp
auto it=mp[i],itb=it;
v1[it]=v2[(n+1)-it]=1;
szt=0;
t[szt++]=mp[i];
int cntt=m;
it=n+1-it;
while((it=v2._Find_next(it))<=n+1&&(cntt--))t[szt++]=(n+1)-it;
reverse(t,t+szt);
cntt=m,it=itb;
while((it=v1._Find_next(it))<=n+1&&(cntt--))t[szt++]=it;
for(int j=1ll;j+m<szt;++j){
    const int L=t[j-1]+1,R=t[j+m]-1;
    const int l=t[j],r=t[j+m-1];
    if(R-L+1<k)continue;
    ans+=(l-L+1)*(R-r+1);
    if(r-l+1<k){
        const int k1=k-(r-l+1);
        const ll ewrwe=0,s1=0,s2=0;
        const int a=l-L,b=R-r+1;
        if(max(0ll,k1-b)<=min(k1,a)){
            const ll t=min(k1,a)-max(0ll,k1-b)+1;
            ans-=t*(k1-min(k1,a)+k1-max(0ll,k1-b))/2;
        }
        ans-=max(k1-b,0ll)*b;
    }
}
xo^=fac[i]?ans:0;
```

---

## 作者：_lmh_ (赞：0)

首先对询问的 $x$ 从大到小做扫描线，相当于选一个区间使得其中至少有 $m$ 个数 $\ge x$。

维护一个 $\ge x$ 的数的链表，对每个左端点可能的区间（每个区间与右侧第一个 $\ge x$ 的数一一对应）维护其对答案的贡献，在链表中插入数的时候暴力重构受到影响的 $O(m)$ 个区间即可。

时间复杂度 $O(nm)$，注意常数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1000007,INF=2147483647;
ll cid,n,m,k,nQ,B,a[N],p[N],R[N],stk[N],top,pre[N],nxt[N],q[N],val[N],ans,now;
struct myrand{
	ll A,B,P,X;
	myrand(ll a,ll b,ll p,ll x){A=a;B=b;P=p;X=x;}
	ll next(){return X=(A*X+B)%P;}
}rng(0,0,0,0);
ll convert(ll x){
	if (cid==7) return x%2;
	return x%(n+1);
}
void rebuild(ll l,ll r){
	if (r>n) return;
//	cout<<"rebuild "<<l<<' '<<r<<endl;
	now-=val[l];
	ll& v=val[l];
	ll L=pre[l]+1;l=min(l,n-k+1);
	if (L>l){v=0;return;}
	v=(n+1)*(l-L+1);
	ll p=min(l+1,max(L,r-k+1));
	if (L<p) v-=r*(p-L);
	if (p<=l) v-=(k-1)*(l-p+1)+(p+l)*(l-p+1)/2;
	now+=v;
}
void add(int x){
	ll r=R[x];
	nxt[x]=r;pre[x]=pre[r];
	nxt[pre[x]]=x;pre[r]=x;
//	s.insert(x);
	ll l=x,i=1;
	while(i<m){
		if (pre[l]==0) break;
		l=pre[l];++i;
	}
	r=l;
	for (int i=1;i<m;++i) r=nxt[r];
	for (;~i;--i){
		rebuild(l,r);
		l=nxt[l];r=nxt[r];
	}
}
int main(){
	cin>>n>>k>>m>>B>>cid>>nQ;
	rng=myrand(16807,B,INF,0);
	for (int i=1;i<=n;++i) a[i]=i;
	for (int i=1;i<=n;++i){
		int l=rng.next()%n+1,r=rng.next()%n+1;
		swap(a[l],a[r]);
	}
	for (int i=1;i<=n;++i) p[a[i]]=i;
	for (int i=1;i<=nQ;++i) q[convert(rng.next())]^=1;
	stk[0]=n+1;a[n+1]=n+1;
	for (int i=n;i;--i){
		while(a[stk[top]]<a[i]) --top;
		R[i]=stk[top];stk[++top]=i;
	}
//	for (int i=1;i<=n;++i){cout<<a[i]<<' ';}cout<<endl;
	q[1]^=q[0];
//	s.insert(0);s.insert(n+1);
	nxt[0]=nxt[n+1]=n+1;
	for (int i=n;i;--i){
		add(p[i]);
//		cout<<i<<' '<<now<<endl;
		if (q[i]) ans^=now;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

