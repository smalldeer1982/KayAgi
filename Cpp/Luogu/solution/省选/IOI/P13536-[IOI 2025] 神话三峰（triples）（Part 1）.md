# [IOI 2025] 神话三峰（triples）（Part 1）

## 题目背景

本题目前可以评测子问题 1。可在 [P13553](https://www.luogu.com.cn/problem/P13553) 评测子问题 2。

## 题目描述

东科迪勒拉山脉是安第斯山脉跨越玻利维亚的部分。它由连续的 $N$ 座山峰组成，从 $0$ 到 $N - 1$编号。山峰 $i$（$0 \leq i < N$）的**高度** $H[i]$  是 $1$ 到 $N - 1$ 之间的整数。

对任意两座山峰 $i$ 和 $j$（其中 $0 \le i < j < N$），它们的**距离**定义为 $d(i, j) = j - i$。根据古老的印加传说，三座山峰是**神话**三峰的条件是：它们的高度与两两之间的距离在**忽略顺序**后**匹配**。

形式化地， $(i, j, k)$ 是神话三峰的条件为：
* $0 \leq i < j < k < N$，
* 山峰高度 $(H[i], H[j], H[k])$ 与两两之间的距离 $(d(i,j), d(i,k), d(j,k))$ 在忽略顺序后匹配。例如，对山峰 $0, 1, 2$，其两两之间的距离是 $(1, 2, 1)$，所以山峰高度 $(H[0],H[1],H[2]) = (1,1,2)$， $(H[0],H[1],H[2]) = (1,2,1)$ 和 $(H[0],H[1],H[2]) = (2,1,1)$ 都匹配，但山峰高度 $(1,2,2)$ 则不匹配。

该问题分为两个部分，分别对应**子问题一**或者**子问题二**。你可以按任意顺序解决这些子问题。特别地，你**无需**先完成子问题一再尝试子问题二。

### 子问题一

给定山脉的描述，你的任务是计算神话三峰的数量。

#### 实现细节

你要实现以下函数：

```
long long count_triples(std::vector<int> H)
``` 

* $H$: 长度为 $N$ 的数组，表示每座山峰的高度。
* 对每个测试用例，该函数恰好被调用一次。

该函数返回一个整数 $T$，表示山脉中神话三峰的数量。

### 子问题二

你的任务是构造包含尽量多神话三峰的山脉。该子问题包含 $6$ 个有**部分得分**的**提交答案**的子任务。

对每个子任务，你将获得两个正整数 $M$ 和 $K$，需要构造一个**最多包含** $M$ 座山峰的山脉。如果你的答案中包含**至少** $K$ 个神话三峰，你将获得该子任务的满分。否则，你的得分将与你的答案中所包含的神话三峰的数量成正比。

注意，你的答案必须是一个有效的山脉。具体来说，假设你的答案包含 $N$ 座山峰（$N$ 必须满足 $3 \leq N \leq M$）。那么，山峰 $i$ 的高度 $H[i]$（$0 \leq i < N$）必须是一个 $1$ 到 $N - 1$ 之间的整数。

#### 实现细节

有两种提交解答的方法，你可以为每个子任务选择其中一种：
* **输出文件**
* **函数调用**

通过**输出文件**提交解答时，请创建并提交一个格式如下的文本文件：
```
N
H[0] H[1] ... H[N-1]
```

通过**函数调用**提交解答时，你需要实现以下函数。

```
std::vector<int> construct_range(int M, int K)
```

* $M$: 最多允许的山峰数量。
* $K$: 期望的神话三峰数量。
* 对每个测试用例，该函数恰好被调用一次。

该函数应返回一个长度为 $N$ 的数组 $H$，表示每座山峰的高度。

## 说明/提示

### 子问题 1 例子

考虑以下调用。

```
count_triples([4, 1, 4, 3, 2, 6, 1])
```

该山脉中包含 $3$ 个神话三峰：

* 对 $(i,j,k)=(1,3,4)$，高度 $(1,3,2)$ 与两两之间的距离 $(2,3,1)$ 匹配。
* 对 $(i,j,k)=(2,3,6)$，高度 $(4,3,1)$ 与两两之间的距离 $(1,4,3)$ 匹配。
* 对 $(i,j,k)=(3,4,6)$，高度 $(3,2,1)$ 与两两之间的距离 $(1,3,2)$ 匹配。

因此，该函数应该返回 $3$。

注意，$(0, 2, 4)$ 不构成神话三峰，因为其高度 $(4,4,2)$ 与两两之间的距离 $(2,4,2)$ 并不匹配。

### 子问题 1 数据范围

- $3 \leq N \leq 200\,000$。
- 对每个满足 $0 \le i < N$ 的 $i$，都有 $1 \leq H[i] \leq N-1$。

### 子任务与得分规则

子问题一总共 $70$ 分。

| 子任务 | 分数 | 额外的约束条件 |
| :-----: | :----: | ---------------------- |
| 1       | $8$    | $N \leq 100$
| 2       | $6$    | 对每个满足 $0 \leq i < N$ 的 $i$，都有 $H[i] \leq 10$。
| 3       | $10$   | $N \leq 2000$
| 4       | $11$   | 山峰的高度是单调不下降的。  也就是说，对每个满足 $1 \leq i < N$ 的 $i$ 都有 $H[i - 1] \leq H[i]$。
| 5       | $16$   | $N \leq 50\,000$
| 6       | $19$   | 没有额外的约束条件。

子问题二总共 $30$ 分。
每个子任务的 $M$ 和 $K$ 值是固定的，如下表所示：


| 子任务 | 分数 | $M$        | $K$             |
| :-----: | :---: | :--------: | :-------------: |
| 7       | $5$   | $20$       | $30$
| 8       | $5$   | $500$      | $2000$
| 9       | $5$   | $5000$     | $50\,000$
| 10      | $5$   | $30\,000$  | $700\,000$
| 11      | $5$   | $100\,000$ | $2\,000\,000$
| 12      | $5$   | $200\,000$ | $12\,000\,000$

对每个子任务，如果你的答案不构成有效的山脉，你的得分将为 $0$（在 CMS 中被报告为 `Output isn't correct`）。否则，设 $T$ 表示答案中的神话三峰数量。
则你在该子任务中的得分为：
$$5 \cdot \min\left(1,\frac{T}{K}\right)$$

## 样例 #1

### 输入

```
1
7
4 1 4 3 2 6 1```

### 输出

```
3```

# 题解

## 作者：Mirasycle (赞：5)

本题是第一个子问题：求神话三峰的数量。

匹配是一个排序之后的结果，故我们要讨论一些相对大小关系。

不妨假设选取的神话三峰为 $i<j<k$。

可以发现我们最关心 $\{h_i,h_j,h_k\}$ 的最大值，因为确定最大值之后就可以直接知道了 $k-i$，而如果知道了次大值或者最小值无法分辨是 $j-i$ 还是 $k-j$。所以要枚举哪个 $h$ 最大。

假设 $h_i$ 最大，我们发现枚举 $i$ 之后 $k=i+h_i$ 也能确定，再通过 $h_k$ 的信息就可以推到 $j$ 了，这样子 $i,j,k$ 都确定了，最后 check 一下 $h_j$ 是否符合要求即可。

$h_k$ 最大和上面同理，一样处理。

最难处理的是 $h_j$ 最大，因为枚举 $j$ 之后我们并不能推理出 $i,k$ 中某一个是什么。但是这里有一种情况是好做的，就是 $i+h_i=k-h_k=j$，因为我们通过 $i,k$ 都可以唯一对应 $j$，直接把满足 $i+h_i=j$ 或 $k-h_k=j$ 的下标都放在 $j$ 处做一个匹配就行了，寻找间距为 $h_j$ 的数对。枚举 $j$，给 $j$ 对应的 $k$ 打上标记，枚举 $j$ 对应的 $i$，寻找 $k=i+h_j$ 即可，由于每个数只会最多在别的数匹配的地方出现两次，所以均摊 $O(n)$。

最难做的是 $h_j$ 最大的情况下，$i+h_k=k-h_i=j$，这个之所以难做是因为我们无法通过其中的某个下标推到另外一个下标，所有的推导形式都至少涉及两个变量，而枚举两个变量会超时。考虑先列出所有式子，再经典处理将相同变量放到一边。

$$i+h_k=k-h_i$$

$$j+h_i=i+h_j$$

$$k-h_j=j-h_k$$

$$\to \begin{cases}
i+h_i=k-h_k

\\j-h_j=i-h_i

\\k+h_k=j+h_j


\end{cases}$$

这就很明了了吧，对于任意一个山峰 $i$ 都有两种形态 $i-h_i$ 和 $i+h_i$，这启发我们图论建模。将值看成点，在点 $i-h_i$ 和 $i+h_i$ 之间连一条边，这条边代表山峰 $i$。

于是上述三个数学式子就变成了无向图三元环的形式了！而我们要做的就是[无向图三元环计数](https://www.luogu.com.cn/problem/P1989)，给边定向之后暴力枚举即可。

最后别忘记考虑一下是否统计到重复的了。

首先不可能出现两个最大值，所以三种大的类型不会产生重复。

细节是当 $h_i=h_k$，且最大值为 $h_j$ 的时候，第三类的两种类型确实会产生重复，于是在第一类的时候特判 $h_i=h_k$ 的时候不进行统计即可。

时间复杂度 $O(n\sqrt n)$。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
typedef vector<int> vi;
const int maxn=4e5+10;
void cmax(int &x,int y){ x=x>y?x:y; }
void cmin(int &x,int y){ x=x<y?x:y; }
int h[maxn],from[maxn],deg[maxn],n; 
int p[maxn],rk[maxn],vis[maxn]; map<int,int> id;
vector<int> G[maxn],L[maxn],R[maxn]; 
pair<int,int> E[maxn];
bool cmp(int x,int y){ return deg[x]<deg[y]||(deg[x]==deg[y]&&x<y); }
ll count_triples(vi H){
	n=H.size(); ll ans=0;
	for(int i=1;i<=n;i++) h[i]=H[i-1];
	//(i,j,k)
	//Hi=max{Hi,Hj,Hk}
	for(int i=1;i<=n;i++){
		int k=i+h[i];
		if(k>n) continue;
		int j=i+h[k];
		if(j<k&&j+h[j]==k) ans++;
		if(k-h[k]!=j){
			j=k-h[k];
			if(i<j&&j-h[j]==i) ans++;
		}
	}
	//Hk=max{Hi,Hj,Hk}
	for(int k=1;k<=n;k++){
		int i=k-h[k];
		if(i<1) continue;
		int j=i+h[i];
		if(j<k&&j+h[j]==k) ans++;
		if(k-h[i]!=j){
			j=k-h[i];
			if(i<j&&j-h[j]==i) ans++;
		}
	}
	//Hj=max{Hi,Hj,Hk}
	for(int i=1;i<=n;i++){
		if(i+h[i]<=n) L[i+h[i]].pb(i);
		if(i-h[i]>=1) R[i-h[i]].pb(i);
	}
	for(int i=1;i<=n;i++){
		for(auto u:R[i]) vis[u]=1;
		for(auto u:L[i])
			if(u+h[i]<=n&&vis[u+h[i]]&&h[u+h[i]]!=h[u]) ans++;
		for(auto u:R[i]) vis[u]=0;
	}
	int tot=0;
	for(int i=1;i<=n;i++){
		int h1=i+h[i];
		int h2=i-h[i];
		if(id.find(h1)==id.end()) id[h1]=++tot;
		if(id.find(h2)==id.end()) id[h2]=++tot;
		h1=id[h1]; h2=id[h2];
		E[i]=mp(h1,h2); deg[h1]++; deg[h2]++;
	}
	for(int i=1;i<=tot;i++) p[i]=i;
	sort(p+1,p+1+tot,cmp);
	for(int i=1;i<=tot;i++) rk[p[i]]=i;
	for(int i=1;i<=n;i++){
		int u=E[i].fi,v=E[i].se;
		if(rk[u]<rk[v]) G[u].pb(v);
		else G[v].pb(u);
	}
	for(int u=1;u<=tot;u++){
		for(auto v:G[u]) from[v]=u;
		for(auto v:G[u])
			for(auto w:G[v])
				if(from[w]==u) ans++;
	}
	return ans;
}
```

---

## 作者：sto_clx_orz (赞：3)

考虑枚举高度与距离的对应关系那么一共有六种情况：

$$
H_i=j-i,H_j=k-j,H_k=k-i\\
H_i=j-i,H_j=k-i,H_k=k-j\\
H_i=k-j,H_j=j-i,H_k=k-i\\
H_i=k-i,H_j=j-i,H_k=k-j\\
H_i=k-i,H_j=k-j,H_k=j-i\\
H_i=k-j,H_j=k-i,H_k=j-i\\
$$

注意到前五种情况我们都可以暴力枚举其中一个值来将当前情况的备选答案数量缩减至 $O(n)$，于是现在只需考虑第六种情况。

我们对式子做个变形可以得到：

$$
i+H_i=k-H_k\\
i-H_i=j-H_j\\
H_j+j=H_k+k\\
$$

发现将每座山峰 $x$ 视作连接 $H_x-x$ 和 $H_x+x$ 的边则 $i,j,k$ 一定对应图上一个三元环，所以我们将所有三元环视作备选答案一定是不漏的。\
而我们又可以在 $O(n\sqrt n)$ 内找出所有 $O(n\sqrt n)$ 个三元环（不会三元环计数的可以看[这里](https://www.luogu.com.cn/problem/solution/P1989)）\
最后我们把所有备选答案去重后暴力 check 一遍即可（注意到 $n\le 2\times 10^5$ 而时限有整整 2s，于是直接 sort 去重即可）。\
最终复杂度 $O(n\sqrt n\log n)$。

:::info[内含代码]
```cpp
#include<bits/stdc++.h>
using namespace std;

map<int,int>mp;
int cnt,deg[400001],vis[400001];
vector<pair<int,int>>Map[400001];
vector<array<int,3>>vec;

long long count_triples(vector<int>H)
{
    int n=H.size();
    for(int i=0;i<n;i++)
    {
        int u=i-H[i],v=i+H[i];
        if(!mp.count(u))
            mp[u]=++cnt;
        if(!mp.count(v))
            mp[v]=++cnt;
        ++deg[mp[u]];
        ++deg[mp[v]];
    }
    for(int i=0;i<n;i++)
    {
        int u=mp[i-H[i]],v=mp[i+H[i]];
        if(deg[u]>deg[v]||(deg[u]==deg[v]&&u>v))
            swap(u,v);
        Map[u].push_back({v,i});
    }
    for(int i=1;i<=cnt;i++)
        vis[i]=-1;
    for(int u=1;u<=cnt;u++)
    {
        for(auto[v,a]:Map[u])
            vis[v]=a;
        for(auto[v,a]:Map[u])
            for(auto[w,b]:Map[v])
                if(~vis[w])
                    vec.push_back({a,b,vis[w]});
        for(auto[v,a]:Map[u])
            vis[v]=-1;
    }
    for(int i=0;i<n;i++)
    {
        int j=H[i]+i;
        if(0<=j&&j<n)
        {
            int k=H[j]+j;
            if(0<=k&&k<n)
                vec.push_back({i,j,k});
        }
    }
    for(int i=0;i<n;i++)
    {
        int j=H[i]+i;
        if(0<=j&&j<n)
        {
            int k=H[j]+i;
            if(0<=k&&k<n)
                vec.push_back({i,j,k});
        }
    }
    for(int j=0;j<n;j++)
    {
        int i=j-H[j];
        if(0<=i&&i<n)
        {
            int k=H[i]+j;
            if(0<=k&&k<n)
                vec.push_back({i,j,k});
        }
    }
    for(int i=0;i<n;i++)
    {
        int k=H[i]+i;
        if(0<=k&&k<n)
        {
            int j=k-H[k];
            if(0<=j&&j<n)
                vec.push_back({i,j,k});
        }
    }
    for(int i=0;i<n;i++)
    {
        int k=H[i]+i;
        if(0<=k&&k<n)
        {
            int j=H[k]+i;
            if(0<=j&&j<n)
                vec.push_back({i,j,k});
        }
    }
    for(auto&i:vec)
        sort(i.begin(),i.end());
    sort(vec.begin(),vec.end());
    vec.erase(unique(vec.begin(),vec.end()),vec.end());
    int ans=0;
    for(auto&[i,j,k]:vec)
    {
        if(!(0<=i)||!(i<j)||!(j<k)||!(k<n))
            continue;
        array<int,3>a{j-i,k-i,k-j},b{H[i],H[j],H[k]};
        sort(a.begin(),a.end());
        sort(b.begin(),b.end());
        if(a==b)
            ++ans;
    }
    return ans;
}。
```
:::

---

## 作者：cmk666 (赞：3)

一个比较优美的看法？

根据 $(h_i,h_j,h_k)$ 和 $(j-i,k-j,k-i)$ 的对应关系分类讨论。

除了 $h_i=k-j,h_j=k-i,h_k=j-i$ 之外的所有情况可以发现枚举其中一个之后另外的可以确定，也就是总共只有 $O(n)$ 种情况要 check，直接做即可。

对于 $h_i=k-j,h_j=k-i,h_k=j-i$ 这种情况，不难把条件改写为 $i-h_i=j-h_j,i+h_i=k-h_k,j+h_j=k+h_k$。

令 $u_i=i-h_i,v_i=i+h_i$，即 $u_i=u_j,v_i=u_k,v_j=v_k$。欸这不是我们三元环计数吗？甚至可以证明每个三元环和一对 $i,j,k$ 一一对应，都不用 check。直接做单根号。同时也证明了答案上界也是 $O(n\sqrt n)$ 的。

需要注意 $j-i=k-j$ 时可能会重复计数，要判一下。

---

## 作者：cyc001 (赞：3)

### Solution

只会 Part I /ll

分成两种情况计数。

1. 存在至少一对点 $u$ 和 $v$ 满足 $H_u=|u-v|$。
2. 不存在如上点对。

对于情况 $1$，合法的 $(i,j,k)$ 数量只有 $O(n)$ 对，可以暴力枚举。

考虑情况 $2$，显然只有如下图的组成方式。

```
i--H(k)--j--H(i)--k
|                 |
\-------H(j)------/
```

枚举 $k$，移项后发现需要满足如下条件：

1. $H_i+i=k-H_k$
2. $H_j+j=k+H_k$
3. $j-i=H_k$

发现 $j-i$ 是固定的，启发我们使用 `std::bitset` 分别维护满足 $1$ 和 $2$ 中合法的 $i$，$j$ 集合 $S_i$ 和 $S_j$，而条件 $3$ 可以看成计数 $|S_i\cap \{j-H_k | j \in S_j\}|$，可以使用 `std::bitset` 的左移操作和 `count` 函数计算。

还有一个小问题是去重，我们直接枚举满足情况 $1$ 的 $O(n)$ 组三元组，排除掉满足情况 $2$ 的即可。

时间复杂度 $O(\frac{n^2}{w})$，空间复杂度 $O(\frac{n^2}{w})$。

现在我们考虑优化一下空间，设定一个阈值 $B\in O(\frac{n}{w})$，对于每个 $H_i+i$，如果这个集合的大小 $\le B$，我们维护一个 `std::unordered_set` 并在计算时暴力求交，否则维护 `std::bitset`。

这样在时间复杂度不变的情况下空间复杂度优化到了 $O(nw)$。

洛谷 $1.75$s，QOJ $997$ms。

### Code

代码勿喷。

```cpp
#include"triples.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

using lint=long long;

template<const size_t len,const uint k=300>
class ext_bitset{
private:
    bitset<len>*info;
    unordered_set<int> cur;
    auto type(){return info!=nullptr;}
    auto check(){
        if(type()||cur.size()*k<len) return;
        info=new bitset<len>();
        info->reset();
        for(auto&x:cur) info->set(x); 
    }
public:
    static auto count_and(ext_bitset<len,k>&a,ext_bitset<len,k>&b,int delta){
        if(a.type()&&b.type()) return (int)(((*(a.info))&((*(b.info))>>delta)).count());
        if(a.type()){
            auto res=0;
            for(auto&x:b.cur) if(x>delta-1) res+=a.info->test(x-delta);
            return res;
        }else if(b.type()){
            auto res=0;
            for(auto&x:a.cur) if(x+delta<len) res+=b.info->test(x+delta);
            return res;
        }else{
            auto res=0;
            for(auto&x:a.cur) res+=b.cur.contains(x+delta);
            return res;
        }
    }
    auto set(int p){
        if(type()) info->set(p);
        else cur.emplace(p),check();
    }
    ext_bitset():info(nullptr){}
    ~ext_bitset(){if(info) delete info;}
};

static constexpr auto maxn=(int)(2e5+7);

lint count_triples(vector<int> H){
    const auto n=(int)(H.size());
    vector<set<array<int,3>>> vaild(n);
    auto test=[&](int i,int j,int k){
        auto a=array<int,3>({H[i],H[j],H[k]});
        auto b=array<int,3>({abs(i-j),abs(i-k),abs(j-k)});
        ranges::sort(a);
        ranges::sort(b);
        auto p=array<int,3>({i,j,k});
        ranges::sort(p);
        if(a==b) vaild[min({i,j,k})].emplace(p);
    };
    cir(i,0,n){
        if(i-H[i]>-1){
            const auto j=i-H[i];
            if(i-H[j]>-1){
                const auto k=i-H[j];
                test(i,j,k);
            }
            if(i+H[j]<n){
                const auto k=i+H[j];
                test(i,j,k);
            }
            if(j-H[j]>-1){
                const auto k=j-H[j];
                test(i,j,k);
            }
            if(j+H[j]<n){
                const auto k=j+H[j];
                test(i,j,k);
            }
        }
        if(i+H[i]<n){
            const auto j=i+H[i];
            if(i-H[j]>-1){
                const auto k=i-H[j];
                test(i,j,k);
            }
            if(i+H[j]<n){
                const auto k=i+H[j];
                test(i,j,k);
            }
            if(j-H[j]>-1){
                const auto k=j-H[j];
                test(i,j,k);
            }
            if(j+H[j]<n){
                const auto k=j+H[j];
                test(i,j,k);
            }
        }
    }
    auto ans=0ll;
    for(auto&x:vaild) for(auto&[i,j,k]:x){
        ans+=(!(j-i==H[k]&&k-j==H[i]&&k-i==H[j]));
    }
    unordered_map<int,ext_bitset<maxn>> c;
    cir(k,0,n){
        ans+=ext_bitset<maxn>::count_and(c[k-H[k]],c[H[k]+k],H[k]);
        c[H[k]+k].set(k);
    }
    return ans;
}

```

---

## 作者：IvanZhang2009 (赞：3)

我只会第一问。

考虑三峰 $i,j,k$ 中最高峰一定是 $k-i$。我们手动枚举最高峰的位置。

如果最高峰是 $h_i=k-i$，那就得到了 $k$。再讨论一下 $h_k$ 是 $j-i$ 还是 $k-j$ 还是都可以是，就可以了。

如果最高峰是 $k$ 是对称的。

如果最高峰是 $j$，有两种：一种是 $h_i=j-i$，$h_k=k-j$。这个我们可以去枚举 $i$，这样 $j,k$ 唯一确定，检验一下即可。

最难的是 $h_i=k-j$，$h_j=k-i$，$h_k=j-i$。

把充要条件写成这样：$i+h_j=j+h_i$，$k-h_j=j-h_k$，$i+h_k=k-h_i$。（对 $i,j,k$ 换元）

移项：$i-h_i=j-h_j$，$k+h_k=j+h_j$，$i+h_i=k-h_k$。

直接枚举 $i,j$ 可以得到 $O(n^2)$ 做法。

注意到 $i-h_i$ 把所有下标分成若干等价类。合法的 $i,j$ 属于同一个等价类。直接做看上去很困难，考虑根号分治：若干一个等价类大小不超过根号，那就枚举 $i,j$；否则对于这样的等价类，我们直接枚举 $k$，开桶 $O(1)$ 检验是否存在 $i,j$。时间复杂度 $O(n\sqrt n)$。

```cpp
#include "triples.h"
#include<bits/stdc++.h>
using namespace std;
#define MOD         998244353
#define ll          long long
#define pii         pair<int,int>
#define all(v)      v.begin(),v.end()
#define pb          push_back
#define REP(i,b,e)  for(int i=(b);i<(int)(e);++i)
#define over(x)     {cout<<(x)<<endl;return;}
#define lowbit(x)   ((x)&(-(x)))
#define cntbit(x)   __builtin_popcount(x)
#define deal(v)     sort(all(v));v.erase(unique(v.begin(),v.end()),v.end())
#define lbound(v,x) lower_bound(all(v),x)-v.begin()
vector<int>b[200005];
int cnt[400005];
long long count_triples(vector<int>a) {
	int n=a.size();
	ll ans=0;
	REP(i,0,n)if(i+a[i]<n){
		int j=i+a[i];
		if(a[j]>a[i])continue;
		if(a[i+a[j]]+a[j]==a[i])++ans;
		if(i+a[j]!=j-a[j]&&a[j-a[j]]+a[j]==a[i])++ans;
	}
	REP(i,0,n)if(i>=a[i]){
		int j=i-a[i];
		if(a[j]>a[i])continue;
		if(a[i-a[j]]+a[j]==a[i])++ans;
		if(i-a[j]!=j+a[j]&&a[j+a[j]]+a[j]==a[i])++ans;
	}
	REP(i,0,n)if(i+a[i]<n){
		int j=i+a[i];
		if(a[j]>a[i]&&i+a[j]<n){
			if(a[i+a[j]]==a[j]-a[i]&&a[i+a[j]]!=a[i])++ans;
		}
	}
	vector<int>T;
	REP(i,0,n)T.pb(i-a[i]);
	deal(T);
	REP(i,0,n)b[lbound(T,i-a[i])].pb(i);
	int B=sqrt(n);
	REP(_,0,T.size()){
		if(b[_].size()<=B){
			REP(i,0,b[_].size()){
				REP(j,i+1,b[_].size()){
					int I=b[_][i],J=b[_][j];
					if(J+a[I]<n&&a[J+a[I]]==J-I)++ans;
				}
			}
		}else{
			for(auto i:b[_])++cnt[i+a[i]];
			REP(i,0,n)if(i-a[i]>=0){
				ans+=cnt[i-a[i]]*cnt[i+a[i]];
			}
			for(auto i:b[_])--cnt[i+a[i]];
		}
	}
//	REP(i,0,n){
//		REP(j,i+1,n)if(i-a[i]==j-a[j]&&j+a[i]<n){
//			if(a[j+a[i]]==j-i)++ans;
//		}
//	}
	return ans;
}

---

## 作者：_lmh_ (赞：2)

首先要统计 $(i,j,k)$ 的数量。

枚举 $i$。如果 $a_i=j-i$ 或者 $a_i=k-i$ 是简单的——可以确定三元组中第二个数，那么第三个数只有 $O(1)$ 种可能，逐个判断即可。

否则，$a_i=k-j$。

令 $b_i=i-a_i$。分类讨论 $a_j$ 与 $a_k$ 的大小关系，可以得到：$b_j=b_k=i$ 或者 $b_j=i-a_i,b_k=i+a_i$。

用 `bitset` 直接维护每个 $b$ 的出现位置，求交即可，时空复杂度均为 $O(\frac{n^2}{w})$。

但是空间会爆，需要优化。

具体地，把 $b_i$ 按照大小分类，$>B$ 的用 `bitset` 维护，$\le B$ 的直接用 `vector` 维护，暴力枚举。

取 $B=\frac{n}{w}$，时间复杂度不变，空间复杂度降为 $O(n)$。为了减小常数，$B$ 可以开小一些。

然后就到了第二问，构造方案。

$n=20$ 和 $n=500$ 没啥好说的，直接用模拟退火之类的技巧搜索即可——实际上这个答案的界非常松，每次只保留更优解（卡在局部最优解的时候手动回退一下版本）就可以搜出来。

首先我们注意到，满足 $a_i$ 和 $j-i,k-i$ 匹配的东西是 $O(n)$ 的，满足 $b_j=b_k=i$ 的三元组也是 $O(n)$ 的（每个 $b$ 只会被算到一次）。

而题目要求我们构造的 $k$ 比它们能凑出来的三元组数量大一个数量级——考虑到所有构造方案都必定带一个小常数，这个量级接近 $O(n\sqrt n)$。

现在有 $b_j=i-a_i,b_k=i+a_i$。首先选一些根据 $b$ 划分的等价类，往每个等价类里面塞一大堆东西；然后对于所有的 $b_i,b_j(2\mid i+j,i<j)$，令 $a_\frac{i+j}{2}=\frac{j-i}{2}$（如果出现冲突，则任选一个值）。

这里每个 $b$ 平均要被覆盖根号次，考虑设置一个阈值 $B=O(\sqrt n)$，选择 $2x$ 与 $2Bx(0\le x<B)$ 作为 $b$ 的集合，这样每个 $b$ 都被覆盖了 $B+O(1)$ 次。

当然还有 $k-j=a_i$ 的限制。前面对 $a_i$ 进行了特殊的赋值，因此这个条件可以转化为 $j+a_j=k+a_k$。

现在考虑如下策略：每次选择一个起点 $p$，对于所有可能的 $b$，尝试在 $p+b$ 的位置放置 $p-b$（如果出现冲突或者越界就不放置），直到把所有位置放满。

把位置 $p$ 映射到 $([\frac{p}{B}],p\bmod B)$ 上，发现放置一组点相当于覆盖一个 L 形的区域。

一个简单的策略是，将平面划分成若干个 $B\times B$ 的块，每块再次划分成 $B$ 个 L 形区域——此时这一块的贡献约为 $\frac{B^3}{3}$。

粗略估计划分成的块数为 $\frac{n}{B^2}-1$，可以枚举 $B$ 求出一个优秀的块长——然后手动精细调整。

满分需要继续优化：在预处理部分，对于 $b_i,b_j(2\mid i+j,i<j)$，我们令 $a_\frac{i+j}{2}=\frac{j-i}{2}$——这一步不用做完，可以有一个后缀的 $a$ 没有被预处理。它们并不会被统计到太多次，因此没有太大的损失。

考虑这 $B$ 个 L 形区域，发现有 $B-1$ 个仍然有扩展空间——只要把划分成的块从 $B\times B$ 改为 $B\times (B+1)$（或者更大）即可。

具体的实现可以参考代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=200007,B=500;
ll n,m,q,a[N],ans,id[N*3],cnt[N],bid[N],sum[N];
vector<int> vec[N];
bitset<N> bs[B];
mt19937 rng(20120712);
void mysort(ll& x,ll& y,ll& z){
	if (x>y) swap(x,y);
	if (y>z) swap(y,z);
	if (x>y) swap(x,y);
}
bool OK(ll x,ll y,ll z){
	if (z>n||z<=0) return 0;
	ll A[3]={abs(x-y),abs(y-z),abs(x-z)},B[3]={a[x],a[y],a[z]};
	mysort(A[0],A[1],A[2]);mysort(B[0],B[1],B[2]);
	return A[0]==B[0]&&A[1]==B[1]&&A[2]==B[2];
}
ll query(ll u,ll v,ll k){
	static bool ok[N];
	ll ans=0;
	if (cnt[u]<B&&cnt[v]<B){
		for (auto x:vec[v]) ok[x]=1;
		for (auto x:vec[u]) if (x+k<=n) ans+=ok[x+k];
		for (auto x:vec[v]) ok[x]=0;
		return ans;
	}
	if (cnt[u]<B){
		v=bid[v];
		for (auto x:vec[u]) if (x+k<=n) ans+=bs[v][x+k];
		return ans;
	}
	if (cnt[v]<B){
		u=bid[u];
		for (auto x:vec[v]) if (x-k>=0) ans+=bs[u][x-k];
		return ans;
	}
	return (bs[bid[u]]&(bs[bid[v]]>>k)).count();
}
ll count_triples(vector<int> H){
	n=H.size();
	for (int i=1;i<=n;++i) a[i]=H[i-1];
	
//	for (int i=1;i<=n;++i) for (int j=i+1;j<=n;++j) for (int k=j+1;k<=n;++k) if (OK(i,j,k)){
//		++sum[i];++sum[j];++sum[k];
//		++ans;
//	}
	
	for (int i=n;i;--i){
		//count
		int x=id[i+N],y,k=a[i];
		if (cnt[x]>=2) ans+=query(x,x,k);
		x=id[i-k+N];y=id[i+k+N];
		if (cnt[x]&&cnt[y]) ans+=query(x,y,k);
		//insert
		k=i-a[i]+N;
		if (!id[k]) id[k]=++m;
		k=id[k];
		vec[k].emplace_back(i);
		if ((++cnt[k])==B){
			bid[k]=++q;
			for (auto x:vec[k]) bs[q][x]=1;
		}
		if (cnt[k]>B) bs[bid[k]][i]=1;
//		cout<<ans<<endl;
	}
	for (int i=1;i<=n;++i){
		int j=i+a[i];
		if (j>n) continue;
		if (a[j]<a[i]) ans+=OK(i,j,j-a[j]);
		if (a[j]!=a[i]) ans+=OK(i,j,j+a[j]);
		if (a[j]!=2*a[i]&&a[j]*2!=a[i]) ans+=OK(i,j,i+a[j]);
	}
	return ans;
}
vector<int> construct_range(int M,int K){
	n=M;
	vector<int> vec,L,R;
	int B;
	if (n==20){
		vector<int> vec={3,1,2,1,4,3,6,5,6,7,2,3,4,1,2,1,8,1,6,5};
		return vec;
	}
	if (n==500){
		vector<int> vec={1,12,1,2,1,2,1,4,3,2,11,10,9,8,7,2,5,4,1,11,1,22,21,20,19,18,17,16,15,14,13,12,11,32,31,30,29,28,27,26,25,24,23,22,43,42,41,40,39,38,37,36,35,34,11,54,53,52,51,50,49,48,47,46,45,22,65,64,63,62,61,60,59,58,57,56,55,76,111,74,73,72,71,70,69,68,67,22,87,86,85,84,83,82,81,80,79,78,11,98,97,96,95,94,93,92,91,90,89,22,109,108,107,106,105,104,103,102,101,100,11,118,121,116,119,114,125,70,127,110,125,44,143,122,141,178,139,138,137,136,135,134,33,132,131,130,129,128,127,150,149,148,147,22,145,144,143,142,141,116,139,162,161,160,33,158,157,156,155,154,105,128,151,174,173,172,171,170,169,168,167,94,117,140,163,186,11,184,183,182,181,180,83,106,129,152,175,22,197,196,195,194,193,72,95,118,141,164,11,210,209,208,207,206,61,84,107,130,153,1,199,222,221,211,219,50,73,96,119,142,165,188,211,234,233,232,39,62,85,108,131,154,177,200,223,246,245,28,51,74,97,120,143,166,189,212,235,18,259,258,257,256,255,254,253,252,251,250,249,248,271,270,269,268,267,11,265,264,263,262,237,260,283,282,281,280,279,12,277,276,275,226,249,272,295,294,293,292,291,11,289,288,215,238,261,284,307,306,305,304,303,12,301,204,227,250,273,296,319,318,317,316,315,24,193,216,239,262,285,308,331,330,329,328,327,12,205,228,251,274,297,320,343,342,341,340,171,24,217,240,263,286,309,332,355,354,353,160,183,12,229,252,275,298,321,344,367,366,149,172,195,48,241,264,287,310,333,356,139,380,379,378,377,376,375,374,373,372,371,370,369,392,391,390,389,388,121,386,385,384,383,358,381,404,403,402,401,400,133,398,397,396,347,370,393,416,415,414,413,412,121,410,409,336,359,382,405,428,427,426,425,424,109,422,325,348,371,394,417,440,439,438,437,436,97,314,337,360,383,406,429,452,451,450,449,448,133,326,349,372,395,418,441,464,463,462,461,292,121,338,361,384,407,430,453,476,475,474,281,304,109,350,373,396,419,442,465,488,487,270,293,316,145,362,385,408,431,454,477,260};
		return vec;
	}
	if (n==5000) B=41;
	if (n==30000) B=100;
	if (n==100000) B=150;
	if (n==200000) B=258;
//	cin>>B;
	for (int i=0;i<B;++i) L.emplace_back(i);
	for (int i=1;i<B;++i) R.emplace_back(i*B);
	for (auto x:L) for (auto y:L) if (x!=y){
		if (!a[x+y]) a[x+y]=abs(y-x);
		else a[x+y]=min(a[x+y],(ll)abs(y-x));
	}
//	for (auto x:R) for (auto y:R) a[x+y]=y-x;
	for (auto x:L) for (auto y:R) a[x+y]=y-x;
//	if (n==5000) for (int i=2;i<B;i+=2) a[i]=B+1;
	int d=B*B+2800,lim=R.back()-3400;
	if (n==5000) d=B*B+3,lim=R.back()-1;
	if (n==30000) d=B*B+B,lim=R.back()-B-1;
	for (int i=lim+1;i<=n;++i) a[i]=0;
	vector<int> owo;
	for (int i=lim+1;i<=n;i+=d) owo.emplace_back(i);
	reverse(owo.begin(),owo.end());
	for (auto i:owo){
		for (int j=0;j<B;++j){
			int x=i+j*(B+1);
			for (auto d:L) if (x+d>0&&x+d<=n&&a[x+d]==0) a[x+d]=x-d;
			for (auto d:R) if (x+d>0&&x+d<=n&&a[x+d]==0) a[x+d]=x-d;
		}
	}
	for (int i=1;i<=n;++i) vec.emplace_back(min(max(a[i],1ll),n-1));
	return vec;
}
```

---

## 作者：Priestess_SLG (赞：0)

很厉害的题。

分类讨论 $(i,j,k)$（$i<j<k$）和相对高度之间的对应关系：

+ $i$ 的高度最高。那么此时 $i$ 和距离她最远的结点 $k$ 之间的距离 $|k-i|$ 一定能对应上 $a_i$（因为 $|k-i|>\max(|j-i|,|k-j|)$ 而 $a_i\ge\max(h_j,h_k)$），那么可以确定 $k=i+h_i$，然后 $j$ 的位置直接枚举剩余的两种对应关系判断是否可行即可。
+ $k$ 的高度最高，和上一类情况处理方式相同。
+ $j$ 的高度最高，此时继续分类讨论：
  + 对应关系形如 $h_i=|j-i|,h_k=|k-j|$ 即 $i+h_i=k-h_k=j$，那么开桶存储 $i+h_i$ 然后随便计数就能做到线性 / 单 log。
  + 对应关系形如 $h_i=|k-j|,h_k=|j-i|$ 即 $i+h_k=k-h_i=j$，此时把三个关系式都列出来然后把相同参数的放在一边，得到：$i+h_i=k-h_k,j-h_j=i-h_i,j+h_j=k+h_k$ 然后计数满足这些条件的三元组 $(i,j,k)$，经典套路考虑建图，将 $i-h_i$ 和 $i+h_i$ 连一条双向边，这样问题就转化为在新图中对三元环计数，可以做到 $O(n\sqrt n)$。

于是这个题就做完了，总时间复杂度为 $O(n\sqrt n)$ 可以通过。

---

## 作者：fire_and_sweets (赞：0)

考虑分类讨论 $H_i,H_j,H_k$ 和 $j-i,k-j,k-i$ 的对应关系，可以将问题分为六类。下面进行一一讲解。

1. 当 $H_i=j-i,H_j=k-j,H_k=k-i$ 时，我们考虑直接枚举 $i$，那我们就有 $j=H_i+i,k=H_j+j$。检验一下 $H_k=k-i$ 是否成立即可。

2. 当 $H_i=j-i,H_j=k-i,H_k=k-j$ 时，我们考虑直接枚举 $i$，那我们就有 $j=H_i+i,k=H_j+i$。检验一下 $H_k=k-j$ 是否成立即可。

3. 当 $H_i=k-j,H_j=j-i,H_k=k-i$ 时，我们考虑直接枚举 $k$，那么 $i=k-H_k,j=k-H_i$，只需检验 $H_j=j-i$ 是否成立即可。

4. 当 $H_i=k-i,H_j=j-i,H_k=k-j$ 时，我们考虑直接枚举 $i$，那么 $k=H_i+i,j=k-H_k$，只需检验 $H_j=j-i$ 是否成立即可。

5. 当 $H_i=k-i,H_j=k-j,H_k=j-i$ 时，我们考虑直接枚举 $i$，那么 $k=H_i+i,j=H_k+i$，只需检验 $H_j=k-j$ 是否成立即可。

6. 当 $H_i=k-j,H_j=k-i,H_k=j-i$ 时，可以把三个条件等价转化成，$i+H_i=k-H_k,j-H_j=i-H_i,k+H_k=j+H_j$。显然，对于每一个 $i$，把 $i-H_i$ 和 $i+H_i$ 之间连一条边，图的三元环个数即为答案。

#### 细节

我们考虑，如果一个三元组 $(i,j,k)$ 同时满足了几种不同的情况，应该如何处理？

暴力做法就是，由于答案的个数是 $O(\sqrt{n})$ 的，所以我们可以把所有合法的答案都在 $\text{set}$ 中去重。这样的复杂度是 $O(n\sqrt{n}\log n)$，而且代码比较难写。

但是我们注意到前 $5$ 种情况的答案个数是 $O(n)$ 的，所以我们暴力用 $\text{set}$ 去重前面的情况，并在把这些答案加入 $\text{set}$ 的时候保证他们不满足第 $6$ 种情况。

这样答案就是 $\text{set}$ 的不同元素个数与第 $6$ 种情况的答案之和，总复杂度是 $O(n\log n+n\sqrt{n})$ 的。

另外注意，在求三元环的时候，$i-H_i$ 可能会出现负数，要加上一个偏移量 $B$。

#### 代码

```Cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=4000010,B=2000000;
ll u[N],v[N],d[N],n;
vector<int>G[N];
vector<int>h;
bool st[N];
ll sz;
ll hsh(ll i,ll j,ll k){
	return i*sz*sz+j*sz+k;
}
unordered_map<ll,bool>mp;
bool check(ll i,ll j,ll k){
	if(i<0||j<0||k<0)return 0;
	if(i>=sz||j>=sz||k>=sz)return 0;
	if(h[i]==k-j&&h[j]==k-i&&h[k]==j-i)return 0;
	return 1;
}
void solve_ji_kj_ki(){
	for(ll i=0;i<sz;i++){
		ll j=h[i]+i;
		if(j<0||j>=sz)continue;
		ll k=h[j]+j;
		if(!check(i,j,k))continue;
		if(h[k]==k-i)mp[hsh(i,j,k)]=1;
	}
}
void solve_ji_ki_kj(){
	for(ll i=0;i<sz;i++){
		ll j=i+h[i];
		if(j<0||j>=sz)continue;
		ll k=h[j]+i;
		if(!check(i,j,k))continue;
		if(h[k]==k-j)mp[hsh(i,j,k)]=1;
	}
}
void solve_kj_ji_ki(){
	for(ll k=0;k<sz;k++){
		ll i=k-h[k];
		if(i<0||i>=sz)continue;
		ll j=k-h[i];
		if(!check(i,j,k))continue;
		if(h[j]==j-i)mp[hsh(i,j,k)]=1;
	}
}
void solve_ki_ji_kj(){
	for(ll i=0;i<sz;i++){
		ll k=h[i]+i;
		if(k<0||k>=sz)continue;
		ll j=k-h[k];
		if(!check(i,j,k))continue;
		if(h[j]==j-i)mp[hsh(i,j,k)]=1;
	}
}
void solve_ki_kj_ji(){
	for(ll i=0;i<sz;i++){
		ll k=h[i]+i;
		if(k<0||k>=sz)continue;
		ll j=h[k]+i;
		if(!check(i,j,k))continue;
		if(h[j]==k-j)mp[hsh(i,j,k)]=1;
	}
}
ll solve_kj_ki_ji(){
	ll m=sz;
	for(ll i=1;i<=m;i++)u[i]=i-h[i-1]+B,v[i]=i+h[i-1]+B;
	for(ll i=1;i<=m;i++)d[u[i]]++,d[v[i]]++;
	for(ll i=1;i<=m;i++)
		if(d[u[i]]>d[v[i]]||d[u[i]]==d[v[i]]&&u[i]>v[i])G[v[i]].push_back(u[i]);
		else G[u[i]].push_back(v[i]);
	ll res=0;
	for(ll i=0;i<=sz*2+B;i++){
		for(auto j:G[i])st[j]=1;
		for(auto j:G[i])for(auto k:G[j])res+=st[k];
		for(auto j:G[i])st[j]=0;
	}
	return res;
}
ll count_triples(vector<int>h){
	ll res=0;sz=h.size();
	::h=h;
	solve_ji_kj_ki();
	solve_ji_ki_kj();
	solve_kj_ji_ki();
	solve_ki_kj_ji();
	solve_ki_ji_kj();
	res=mp.size();
	res+=solve_kj_ki_ji();
	return res;
}
```

---

