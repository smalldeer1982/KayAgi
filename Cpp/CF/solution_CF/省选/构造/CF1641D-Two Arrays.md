# Two Arrays

## 题目描述

Sam changed his school and on the first biology lesson he got a very interesting task about genes.

You are given $ n $ arrays, the $ i $ -th of them contains $ m $ different integers — $ a_{i,1}, a_{i,2},\ldots,a_{i,m} $ . Also you are given an array of integers $ w $ of length $ n $ .

Find the minimum value of $ w_i + w_j $ among all pairs of integers $ (i, j) $ ( $ 1 \le i, j \le n $ ), such that the numbers $ a_{i,1}, a_{i,2},\ldots,a_{i,m}, a_{j,1}, a_{j,2},\ldots,a_{j,m} $ are distinct.

## 说明/提示

In the first test the minimum value is $ 5 = w_3 + w_4 $ , because numbers $ \{2, 3, 4, 5\} $ are distinct.

In the second test case, there are no suitable pair $ (i, j) $ .

## 样例 #1

### 输入

```
4 2
1 2 5
4 3 1
2 3 2
4 5 3```

### 输出

```
5```

## 样例 #2

### 输入

```
4 3
1 2 3 5
2 3 4 2
3 4 5 3
1 3 10 10```

### 输出

```
-1```

# 题解

## 作者：蒟蒻君HJT (赞：16)

看到目前题解区里都是很厉害的容斥做法，还有根号什么的，这些我都不会，所以我来发一个神必的题解（其实我自己觉得这个才是最好想的）。

首先先把 $a_{i,j}$ 都离散化成 $1$ 到 $s$ 之间的整数。

然后考虑这样一个问题。如果 $s$ 很小的话，我们可以把每一个序列映射成一个 $s$ 位二进制 $ma_i$，它的第 $i$ 位 $1/0$ 表示该序列中存在/不存在数字 $i$。这样的话对于 $w_i+w_j$，我们枚举 $i$，对 $j$ 的要求即为 $ma_i\bigcap ma_j =\emptyset$，FMT 即可，单次复杂度 $\mathcal{O}(s\times 2^s)$。

但现在 $s$ 很大怎么办？考虑将所有 $a_{i,j}$ 映射为 $a_{i,j}\bmod p$，将值域转化为 $[0,p-1]$。这样做得到的结果一定合法但不一定最大。

先取 $p=20$，考虑这样做得到正确答案的概率至少为 $\begin{pmatrix}15\\5\end{pmatrix}\div \begin{pmatrix}20\\5\end{pmatrix}\approx 0.2$，这概率当然不够高。

但当我们重复 $t$ 次随机打乱 $a_{i,j}$ 的编号（因为我们只关心编号的相等关系而不关注大小关系）并进行以上流程时，正确率就提高为 $1-(0.8)^t$，取 $t=20$，正确率 $\approx 99\%$，可以接受。

时间复杂度 $\mathcal{O}(t\times s \times 2^s)$，常数小稳过。

code

```cpp
int n, m, a[100005][5], ma[100005], w[100005];
int b[500005], c[500005], pa[500005], tot = 0;
std::map <int, int> mp;
const int P = 20, MaxT = 20;
int f[1 << P], ans = -1;
void solve(){
	srand((unsigned)time(NULL));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= m; ++j){
			scanf("%d", &a[i][j]);
			b[(i - 1) * m + j] = a[i][j];
		}
		scanf("%d", &w[i]);
	}
	std::sort(b + 1, b + n * m + 1);
	for(int i = 1; i <= n * m; ++i) if(b[i] != b[i - 1]) c[++tot] = b[i];
	for(int i = 1; i <= tot; ++i) mp[c[i]] = i;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			a[i][j] = mp[a[i][j]];
	for(int i = 1; i <= tot; ++i) pa[i] = i;
	for(int T = 1; T <= MaxT; ++T){
		std::random_shuffle(pa + 1, pa + tot + 1);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				a[i][j] = pa[a[i][j]];
		for(int i = 0; i < (1 << P); ++i) 
			f[i] = (1 << 30) - 1;
		for(int i = 1; i <= n; ++i){
			ma[i] = 0;
			for(int j = 1; j <= m; ++j)
				ma[i] |= (1 << (a[i][j] % P));
			f[ma[i]] = std::min(f[ma[i]], w[i]);
		}
		for(int o = 1; o < (1 << P); o <<= 1)
			for(int j = 0; j < (1 << P); j += (o << 1))
				for(int k = j; k < j + o; ++k)
					f[k | o] = std::min(f[k | o], f[k]);
		int full = (1 << P) - 1;
		for(int i = 1; i <= n; ++i)
			if(f[full ^ ma[i]] != (1 << 30) - 1)
				if(ans == -1)	ans = w[i] + f[full ^ ma[i]];
				else ans = std::min(ans, w[i] + f[full ^ ma[i]]);
	}
	printf("%d\n", ans);
	return ;
}
```


---

## 作者：tommymio (赞：14)

赛时听到 jly 二分加容斥做完了，非常厉害，当时我还只会口胡一个随机化。

讲一讲两个做法。一个是 ``bitset`` 平衡复杂度，一个是 ``Hash/Trie`` 双指针维护答案。友情 @7kbyte（

### Solution 1

``bitset`` 的做法看上去似乎比较显然。对于 $O(n\times m)$ 种权值，每种权值开一个 $n$ 位的 ``bitset``，表示权值 $c$ 是否出现在第 $i$ 个数组中。将 $n$ 个数组以 $w_i$ 为关键字从小到大排序，枚举数组对 $(i,j)$ 中的 $j$，找一个最小的 $i$ 与之匹配，怎么做呢？可以将数组 $j$ 内的元素的 ``bitset`` 或起来并反转每个位，然后找最低位的 $1$ 的位置。时间复杂度与空间复杂度均为 $O\left(\frac{n^2m}{\omega}\right)$，不过空间复杂度太大了过不去。考虑 trivial 的平衡复杂度，对于出现次数 $<B$ 的权值不再对其维护 ``bitset``，而是直接暴力。时间复杂度为 $O\left(nmB+\frac{n^2}{\omega}\max\left(m,\frac{n}{B}\right)\right)$，空间复杂度为 $O\left(\frac{n^2}{\omega B}\right)$，平衡一下可得 $B \approx \sqrt{\frac{n^2}{m\omega}}$，空间复杂度变为 $O\left(\sqrt{\frac{n^2m}{\omega}}\right)$。

### Solution 2

``Hash/Trie`` 的做法则基于容斥。

双指针的性质特别显然，问题其实是如何快速找出当前是否存在不交的数组对。

分别写出数组 $A,B$ 的幂集 $P_A,P_B$。

对下列式子求值

$$
\sum_{a\in P_A}\sum_{b\in P_B}[a=b](-1)^{|a|-1} 
$$

若 $A,B$ 存在交集，上式值必然为 $1$，否则为 $0$。

设 $A$ 与 $B$ 交集大小为 $s$，考虑这个式子其实求的是

$$
\binom{s}{1}-\binom{s}{2}+\binom{s}{3}\dots
$$

于是显然。

怎么判断子集相同？想到可以用 ``Hash`` 来处理一个集合的子集。具体来说，对于每个数组求出其子集的 ``Hash`` 值。然后两两比对判断当前是否存在不交的数组对么？只需要开一个桶在可能的答案区间发生变化的时候（即双指针移动时）统计上式的贡献即可，若在删除一个数组的贡献之后上式的总贡献没有变化，说明这个数组是不交的数组对的一个元素。

``Trie`` 的做法只是将 ``Hash`` 和桶换掉了，仍然是维护上式的总贡献，本质没有发生变化。

时间复杂度为 $O(n2^m)$。


---

## 作者：tder (赞：8)

You can view the [English version](https://www.luogu.com/article/sasefjnh/) of this solution.

我觉得这个做法很牛啊。作为训练赛的 F 题远小于 E 题，亦是六题中唯三的有数据的题目，这便是我们梦熊。

看到这种出没出现的约束容易想到 bitset，由此引申出以下两种思路。

做法一：考虑用 $n$ 个大小为 $n\times m$ 的 bitset $b_i$ 维护每行出现了哪些数。于是枚举二元组 $(i,j)$，若 $|b_i\cup b_j|=m\times2$ 则对更新答案。时间复杂度、空间复杂度均为 $\mathcal{O}(\frac{n^3m}w)$。

做法二：考虑用 $n\times m$ 个大小为 $n$ 的 bitset $b_i$ 维护每个数在哪几行出现了。对于满足条件的二元组 $(i,j)$ 一定有对于所有 $k$，都有 $i\not\in b_{a_{j,k}}$。由此，想到枚举 $i$，取所有 $b_{a_{i,k}}$ 的并集的补集 $t$，则对于合法的 $j$ 有 $j\in t$。由于要求答案最小，可以按 $w_i$ 将每行排序，最优的 $j$ 即为 $\text{lowbit}(t)$。时间复杂度 $\mathcal{O}(n\log n+\frac{n^2m}w)$，空间复杂度 $\mathcal{O}(\frac{n^2m}w)$。

做法一肯定是没前途的，甚至不如朴素模拟的 $\mathcal{O}(n^2m)$。但是我们还想用 bitset 硬草，于是考虑优化做法二。观察到如果某个数仅在所有行中出现了一次，即 $|b_x|=1$，这会很浪费时间和空间。此例提醒我们对于出现次数较少的 $x$ 直接硬算是更优的，考虑对于 $|b_x|\le\sqrt{nm}$ 直接用 vector 代替 bitset 维护之。

可以做到时间复杂度 $\mathcal{O}(n\log n+nm+(nm-\sqrt{nm})^2\frac nw)$，空间复杂度 $\mathcal{O}(\frac{n\sqrt{nm}}w+nm)$。

[CodeForces Submission.](https://codeforces.com/contest/1641/submission/275174930)

---

## 作者：intel_core (赞：7)

`bitset` 好题。

首先考虑暴力处理元素不能相同的限制。

对每个数 $x$ 开一个 `bitset` $s_x$，第 $i$ 位是 `1` 当且仅当 $a_i$ 中有 $x$。

枚举每个 $a_i$，将 $s_{a_{i,j}}$ 全部或起来得到 $f_i$，$f_i$ 中 `0` 那些位代表可以和 $a_i$ 同时选。

在所有可能的组合中选一个最小的即可，复杂度 $O(\frac{n^2m}{w})$，但是空间不够。

实际上，很多出现次数很少的数独占一个 `bitset` 浪费了大量空间，故考虑根号分治平衡复杂度。

当一个数出现了至少 $\sqrt{nm}$ 次时才单独拿出来开一个 `bitset` ，不难发现此时 `bitset` 最多 $O(\sqrt{nm})$ 个，空间降至 $O(\frac{n\sqrt{nm}}{w})$。

此时时间是 $O(nm\sqrt{nm}+\frac{n^2m}{m})$，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e5+10;
const int MR=5e5+10;
int n,m,Block,v[MR],len,cnt[MR],ans=2e9+10,idx[MR],tot;
vector<int>buc[MR];
#define pb push_back 
struct task{
	int a[6],v;
	bool operator <(const task &T)const{
		return v<T.v;
	}
}t[NR];
bitset<NR>s[800];

int main(){
	cin>>n>>m;Block=sqrt(n*m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			scanf("%d",&t[i].a[j]),v[++len]=t[i].a[j];
		scanf("%d",&t[i].v);
	}
	sort(t+1,t+1+n);
	sort(v+1,v+1+len);
	len=unique(v+1,v+1+len)-v-1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			buc[t[i].a[j]=lower_bound(v+1,v+1+len,t[i].a[j])-v].pb(i),cnt[t[i].a[j]]++;
	for(int i=1;i<=len;i++)
		if(cnt[i]>=Block){
			idx[i]=++tot;
			for(int x:buc[i])s[tot].set(x);
		}
	bitset<NR>tmp;
	for(int i=1;i<=n;i++){
		tmp.reset();
		for(int j=1;j<=m;j++)
			if(idx[t[i].a[j]])tmp|=s[idx[t[i].a[j]]];
		tmp.flip();
		for(int j=1;j<=m;j++)
			if(!idx[t[i].a[j]])
				for(int x:buc[t[i].a[j]])tmp.reset(x);
		int pos=tmp._Find_next(0);
		if(pos<=n)ans=min(ans,t[i].v+t[pos].v);
	}
	if(ans<=2e9)cout<<ans<<endl;
	else puts("-1");
	return 0;
}
```

---

## 作者：xzzduang (赞：7)

**神仙题**

[传送门](https://codeforces.com/contest/1641/problem/D)

参考[ CF 官方题解](https://codeforces.com/blog/entry/100249)。

考虑怎么判断两个集合 $a$ 和 $b$ 是否有至少一个相同元素，正常的方法我们都会选择扫几遍，但是如果换成判断一个集合与 $k$ 个集合呢。所以这里有一个极其神仙的方法：

我们知道容斥原理的基础：$\sum \binom{n}{i}(-1)^i=[n=0]$，假设我们要判断 $a$ 和 $b$ 中是否有至少一个相同元素，我们可以枚举 $b$ 的所有子集，判断其是否也是 $a$ 的子集，如果是，子集大小为奇数的话就给答案加一，是偶数就给答案减一，最终结果如果是 $1$ 就没有相同元素，如果是 $0$ 就有。

通过这个我们也可以做到判断一个集合 $a$ 与若干集合 $b_i$ 是否相同元素，用类似的方法就好了，最终也是判断结果是不是 $0$。

回到原问题，我们把所有数组按照 $w$ 排序，我们可以通过上面的方法找到右端点最小的满足条件的 pair，设为 $(l,r)$。之后我们往右移动 $r$，因为我们要使答案最小，$l$ 往右移是完全没有意义的，所以 $l$ 只能往左移，一直移到这是对于现在的 $r$ 的最左的能满足条件的 $l$，然后更新答案。

因为 $l$ 和 $r$ 都只能往一个方向移动，时间复杂度就是 $\mathcal{O}(n\cdot 2^m)$。

## 关于实现

- 这题其实有些地方文字是有点不好理解的，那就看看代码吧。

- 一个集合和若干个集合的判断可以把这若干个集合的所有子集像 trie 一样建成一个图，拿 `unordered_map` 存图就好了。
- 这题有亿点点卡常。我这个都是很极限才过去的。
- 建议不要借鉴这里的实现方法，用一个哈希表又好写常数又小，用这个类似 trie 的方法很可能 TLE。

```cpp
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize(2)
#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include<algorithm>
#include<unordered_map>
#include<array>
#define N 100005
using namespace std;
inline int read(){
	int x=0,f=0; char ch=getchar();
	while(!isdigit(ch)) f|=(ch==45),ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return f?-x:x;
}
struct arr{
	array <int,10> a;
	int w;
	bool operator < (const arr &A)const{
		return w<A.w;
	}
}a[N];
struct node{
	unordered_map <int,int> mp;
	int cnt;
};
vector <node> G;
int n,m,ans,pool;
int get(const array<int,10> &x,int i,int u){
	if(i>m) return G[u].cnt;
	int res=get(x,i+1,u);
	if(G[u].mp.find(x[i])!=G[u].mp.end()) res-=get(x,i+1,G[u].mp[x[i]]);
	return res;
}
void insert(const array<int,10> &x,int i,int u){
	if(i>m){
		G[u].cnt++;
		return;
	}
	insert(x,i+1,u);
	if(G[u].mp.find(x[i])==G[u].mp.end()) G[u].mp[x[i]]=++pool;
	insert(x,i+1,G[u].mp[x[i]]);
}
void erase(const array<int,10> &x,int i,int u){
	if(i>m){
		G[u].cnt--;
		return;
	}
	erase(x,i+1,u);
	erase(x,i+1,G[u].mp[x[i]]);
}
int main(){
	n=read(),m=read();
	G.resize(n*(1<<m)+1);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			a[i].a[j]=read();
		}
		sort(a[i].a.begin()+1,a[i].a.begin()+m+1);
		a[i].w=read();
	}
	sort(a+1,a+n+1);
	int r=1;
	while(r<=n && !get(a[r].a,1,0)) insert(a[r].a,1,0),r++;
	if(r>n) return puts("-1")&0;
	int l=r-1;
	while(get(a[r].a,1,0)) erase(a[l].a,1,0),l--;
	ans=a[r].w+a[l+1].w;
	for(int i=r+1;i<=n;++i){
		if(!l) break;
		if(get(a[i].a,1,0)){
			while(get(a[i].a,1,0)) erase(a[l].a,1,0),l--;
			ans=min(ans,a[i].w+a[l+1].w);
		}
	}
	cout<<ans;
	return 0;
}

```



---

## 作者：ChengJY_ (赞：6)

真神仙题。

**做法一** 

使用 ```bitset``` 优化暴力，对权值开 ```bitset```，匹配时直接或起来即可。

注意到空间很大，可以通过根号分治优化，时间复杂度大概在 $O(\sqrt{\frac{n^3m}{\omega}})$。

**做法二**

这个容斥是真的 NB。

判断两个集合是否重合的一个方法：枚举两个集合的子集，长度为奇数的子集相同就加一，为偶数的子集相同就减一，最终若有相等元素，则最终值一定为 $1$。

证明：令 $s$ 为交集大小，则我们所求值为 $\sum\limits_{i=1}^{s}\dbinom{i}{s}(-1)^{i+1}$，由二项式定理可以推导得到。

这个方法看似时间复杂度很劣，但是在这道题中有奇用，我们可以用他来判断若干集合中于一个集合有相同元素的集合个数。

具体的，我们把这区间中的子集全部求出来，使用哈希表/Trie等数据结构记录个数，然后做上面的东西即可，最终得到的答案即为有相同元素的集合个数，可以在  $O(m2^m)$ 的时间复杂度内得出。

本题中，最开始我们将所有集合按 $w$ 排序，找到最前面的一个 $r$，和相应的 $l$，然后我们将 $r$ 右移，此时贪心地想，$l$ 必须向左移，具体将 $l$ 左移时删去他的子集，如果此时与 $r$ 相交集合减少，则说明 $l$ 和 $r$ 无交集，更新答案。

由于 $l$ 和 $r$ 单调，最终时间复杂度为 $O(nm2^m)$。

[Code](https://codeforces.com/contest/1641/submission/181036750)

---

## 作者：K8He (赞：5)

[CF1641D Two Arrays *2700](https://codeforces.com/problemset/problem/1641/D)

You can view the [English version](https://www.luogu.com.cn/article/ufjeexf4) of this solution.

我觉得这个做法很牛啊。

先按 $w_i$ 排序，考虑如果我们已经有了一组 $j$ 最小的合法解 $(w_i, w_j)(i < j)$，一组更优解 $(w_u, w_v)$ 一定满足 $u < i$ 且 $j\le v $。注意到这两个指针都是单向移动的，所以我们只要在找出一组合法解后有优秀的做法快速移动这个双指针，就能找到最优解。

移动右指针的时候，我们需要查询一段前缀里和右指针能形成合法解的位置。注意到左指针是单向移动的，所以只要我们只需要知道前缀里是否存在合法位置，具体的位置在移动左指针至一个没有合法位置的前缀 $p$ 后即可知道这个当前最小的合法位置位于 $p + 1$。

现在的问题剩下了，如何快速求若干个集合 $\{S\}$ 中有几个集合与一个指定的集合 $T$ 相交。我们直接枚举 $T$ 的子集作为所有 $S$ 的子集的出现次数是不行的，因为一个集合会有多个子集产生重复贡献，我们需要一种方法删除掉冗余贡献。

也就是说，我们需要构造一个函数 $F(T)$，使得 $\sum_{T\in S}F(T) = 1$，这个直接构造成容斥系数再简单不过了，即 $F(T) = (-1)^{\left|T\right|}$。

那么现在求若干个集合 $\{S\}$ 中有几个集合与一个指定的集合 $T$ 相交的方法就是：枚举 $T$ 的所有子集，计算这个子集出现了多少次，乘上容斥系数并求和。计算子集出现多少次可以用 Hash 或者 Trie 维护，不过你都选择容斥的确定性算法了为啥不用 Trie。

时间复杂度 $O(nm2^m)$。

[CodeForces Submission .](https://codeforces.com/contest/1641/submission/275207319)

---

## 作者：周子衡 (赞：5)

一道思路比较奇怪的题，有点难想。

下面记 $S_i=\{a_{i,1},...,a_{i,m}\}$。

先将所有元素按 $w$ 升序排序。考虑从小到大对每个 $i$ 计算出最小的 $p_i$ 使得 $S_i,S_{p_i}$ 无交，最后在所有 $w_i+w_{p_i}$ 中取最小值即可。此外，如果确定这样的 $p_i$ 一定比某个 $p_j(j<i)$ 大，我们也可以放弃计算 $p_i$（因为这样的 $w_i+w_{p_i}$ 一定不优）。考虑从小到大枚举 $i$，初始时令 $p_i=p_{i-1}$（初始条件可设为 $p_0=n+1$），然后不断缩小 $p_i$，直到 $[1,p_i-1]$ 中所有集合都和 $S_i$ 有交为止。这个做法类似于尺取法。

接下来要考虑的问题是：怎么快速判断某个 $[1,j]$ 中的集合是否全部和 $S_i$ 有交。直接判定似乎有些困难，考虑利用容斥原理来计数有多少个 $S_k(k\in [1,j])$ 使得 $S_k,S_j$ 有交。对每个 $k$，我们把 $S_k$ 的所有子集插入一个大集合中，奇数大小的子集权值标为 $+1$，偶数大小的标为 $-1$。可以发现，$S_i$ 的所有子集的权值之和就是 $S_i$ 和 $S_{1...j}$ 中有交的集合数量，判断其是否等于 $j$ 即可。

维护大集合时可以采用 Trie 来维护。总时间复杂度 $O(nm2^m)$。


---

## 作者：BreakPlus (赞：4)

+ 直接做很难做，考虑哈希判断。但是这题判的是有无交集，我们熟知的 Xor Hash 和 Sum Hash 都很难做。

+ 考虑集合划分模型，将考虑的值域强行变小。具体地，每种值随机分配到 $0 \sim 19$ 中的一个数。判断两数相同可以变成判断两数是否不在一个集合。

+ 然后可以 DP 出 $f(S)$ 表示所有能用 $S$ 中的数表示的集合的 $w$ 最小值。答案为 $\min (f(S), f(T-S))$，其中 $T$ 是全集。

```cpp
ll n,m,a[100005][6],w[100005],f[1048576],tmp[500005],cnt,split[500005];
ll minn(ll a,ll b){
	return a<b?a:b;
}
mt19937 rnd(/*自取*/);
int main(){
	n=read(),m=read();
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++) tmp[++cnt]=a[i][j]=read();
		w[i]=read();
	}
	sort(tmp+1,tmp+cnt+1); cnt=unique(tmp+1,tmp+cnt+1)-(tmp+1);
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++) a[i][j]=lower_bound(tmp+1,tmp+cnt+1,a[i][j])-tmp;
	}
	ll T = 22, ans = 2147483647;
	while(T--){
		memset(f, 127, sizeof(f));
		for(ll i=1;i<=cnt;i++) split[i] = rnd() % 20;
		for(ll i=1;i<=n;i++){
			ll sta0 = 0;
			for(ll j=1; j<=m; j++) sta0 |= (1<<split[a[i][j]]);
			f[sta0] = minn(f[sta0], w[i]);
		}
		for(ll j=0;j<20;j++)
			for(ll i=0;i<(1<<20);i++){
				if((i>>j)&1) f[i] = minn(f[i], f[i^(1<<j)]);
			}
		for(ll i=0;i<(1<<20);i++){
			if(f[i]<=1e9 && f[(1<<20)-i-1]<=1e9)ans = minn(ans, f[i] + f[(1<<20)-i-1]);
		}
	}
	if(ans <= 2e9) printf("%d\n", ans);
   else puts("-1");
	return 0;
}
```

---

## 作者：myee (赞：4)

### 前言

一个感觉很假的做法，赛时写挂了，但是赛后改改改过了 System test。

没注意到 Luogu 爬了 CF。既然爬了，我就发一下吧。

[有兴趣的同学可以来叉](https://www.luogu.com.cn/discuss/412560)。

---
### 思路

就，你考虑一个贪心：每个数组都和可能与它组合成答案的算一遍。

然后可能和它构成答案的数满足一个贪心的性质。

即：
* 差异为 $0$ 的只用保留最小一个。
* 差异为 $1$ 的只用保留最小两个。
* 以此类推。

然后这个阈值我不太会算，于是口胡了一个 `Lim` 数组：

```cpp
const uint Lim[]={0,1,5,15,40,100};
```

---
### Code

放一下核心代码。

```cpp
uint W[100005],A[100005][5],Ans[6][6];
std::vector<uint>QAQ;
typedef std::pair<uint,uint>Pair;
Pair P[6][6];
uint m;
uint lcs(uint a,uint b)
{
    for(uint i=0;i<m;i++)for(uint j=0;j<m;j++)
        if(A[a][i]==A[b][j])Ans[i+1][j+1]=Ans[i][j]+1,P[i+1][j+1]=Pair(i,j);
        else Ans[i+1][j+1]=std::max(Ans[i+1][j],Ans[i][j+1]),
        	P[i+1][j+1]=Ans[i+1][j]>Ans[i][j+1]?Pair(i+1,j):Pair(i,j+1);
    QAQ.clear();
    Pair now=Pair(m,m);
    while(now!=Pair())
    {
        if(P[now.first][now.second].first<now.first
        	&&P[now.first][now.second].second<now.second)
        	QAQ.push_back(A[a][now.first]);
        now=P[now.first][now.second];
    }
    return Ans[m][m];
}
uint Id[100005],Now[100005],cnt=0;
const uint Lim[]={0,1,5,15,40,100};
int main()
{
    uint n;uint ans=-1;
    scanf("%u%u",&n,&m);
    for(uint i=0;i<n;i++)
    {
        for(uint j=0;j<m;j++)scanf("%u",A[i]+j);
        scanf("%u",W+i);
        std::sort(A[i],A[i]+m);
        Id[i]=i;
    }
    std::sort(Id,Id+n,[&](uint a,uint b){return W[a]<W[b];});
    for(uint i=0;i<n;i++)
    {
        uint p=Id[i];
        std::map<std::vector<uint>,uint>LCNT;
        for(uint j=0;j<cnt;j++)
        {
            uint c=lcs(p,Now[j]);
            LCNT[QAQ]++;
            if(!c)_min(ans,W[p]+W[Now[j]]);
        }
        bol b=true;
        for(auto p:LCNT)
        	if(p.second>Lim[m-p.first.size()]){b=false;break;}
        if(b)Now[cnt++]=p;
    }
    printf("%d\n",(int)ans);
    return 0;
}
```


---

## 作者：Masterwei (赞：3)

这题简直了。

容易想到需要贪心，按 $w_i$ 排序，那我们从小到大枚举一个 $i$，我们去找当前合法的一个最左边的端点 $j$，使得 $i,j$ 满足 $a$ 互不相同。其实 $j$ 是可以随着 $i$ 单调递增而单调递减的，因为我们按 $w$ 排序了。这样就启发我们使用双指针。

那么如何判断一个 $j$ 是否为最小合法左端点呢？考虑去判断 $1\sim j$ 是否存在一个合法端点，那么最小合法左端点就是其加 $1$。

这一部分可以使用容斥算出至少包含当前 $i$ 中一个 $a$。

```cpp
#include<bits/stdc++.h>
#define ll unsigned long long
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=1e5+5;
const ll base=1313131311;
int n,m;
struct node{vector<int>a;int w;}a[Maxn];
inline bool cmp(node a,node b){return a.w<b.w;}
unordered_map<ll,int>f;
inline void insert(int id,int p){
	for(int s=1;s<(1<<m);s++){
		ll b=0;
		for(int i=0;i<m;i++)
			if(s&(1<<i))b=b*base+a[id].a[i];
		f[b]+=p;
	}
}
inline int popcount(int x){
	int res=0;
	for(int i=0;i<m;i++)res+=(x>>i);
	return res;
}
inline bool check(int id,int len){
	int cnt=0;
	for(int s=1;s<(1<<m);s++){
		ll b=0;
		for(int i=0;i<m;i++)
			if(s&(1<<i))b=b*base+a[id].a[i];
		cnt+=(popcount(s)&1?f[b]:-f[b]);
	}
	return len==cnt;
}
int main(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)a[i].a.push_back(read());
		sort(a[i].a.begin(),a[i].a.end());
		a[i].w=read();
	}sort(a+1,a+1+n,cmp);
	int r=1;
	while(r<=n){
		insert(r,1);
		if(!check(r,r))break;
		r++;
	}
	if(r==n+1)puts("-1"),exit(0);
	insert(r,-1);
	int p=r-1,ans=2e9+7;
	for(int i=r;i<=n;i++){
		if(p<0)break;
		while(p>0&&!check(i,p))insert(p,-1),p--;
		ans=min(ans,a[i].w+a[p+1].w);
	}
	printf("%d\n",ans>=2e9+7?-1:ans);
	return 0;
}
```

---

## 作者：c20231020 (赞：2)

### 题目链接
[luogu](https://www.luogu.com.cn/problem/CF1641D)

[codeforces](https://codeforc.es/contest/1641/problem/D)

### 思路

> 2023.9.19 感谢 @[cpchenpi](https://www.luogu.com.cn/user/553296)，纠正了时间复杂度并修改了一些细节。

题解区似乎还没有这种乱搞方法……

对每一个数字开一个长度为 $n$ 的 `bitset`，记录哪些数列出现了这个数。

将数列按价值 $w_i$ 从小到大排序，然后从前往后扫。

对于第 $i$ 个数列：

+ 将该数列中的所有数对应的 `bitset` 按位或，再取反，就得到了一个合法集合，为 $1$ 的位对应的数组就可以匹配。
+ 使用 `_Find_first` 函数找到 `bitset` 中第一个 $1$ 的位置，设为 $j$，对 $w_i+w_j$ 和 $ans$ 取最小值即可。这里要注意因为对数列从前往后扫，所以必须满足 $j \in [1,i-1]$。
+ 将数列 $i$ 中的所有元素分别对应的 `bitset` 中的第 $i$ 位改成 $1$，标志第 $i$ 的数列有这个数字。

这么做，时间复杂度是 $O(\frac{n^2m}{w})$，但是空间复杂度是 $O(n^2m)$，需要 5.82GiB 的空间，吃不消啊。

选一个质数 $p$，将每个数映射到一个 $[1,p]$ 内的随机整数，尽管这样做会有某些数冲突，但是每一对冲突的数没有同时出现在两个数列里即可。这样做会使正确率变得玄学且没有时间复杂度的优化，但空间复杂度降至 $O(np)$，能卡过去。我选的 $p=13171$。

还有一种正确率稍高方法：取小一点的 $p$，再随机 $T$ 次映射，可以做到时间 $O(Tnp)$。由于映射的冲突只会导致答案可能变大（无解视为 $\inf$），将各个答案取最小值就行了。记录映射最好手写哈希表，不然 `map` 直接退化到 $O(T(nm\log nm+\frac{np}{w}))$，容易 TLE。`unordered_map` 更容易被对着卡。

没有用上述优化，交了 $2$ 次就过了，代码实际复杂度是 $O(nm\log nm+\frac{n^2m}{w})$。

#### code

省略了很长的缺省源。

```cpp
int n,m;
map<int,int>mp;
struct G{
	int a[6],w;
}a[100010];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
bitset<100010>b[13175],tem;
int rnd(int l,int r){
	return rng()%(r-l+1)+l;
}
void solve(){
	cin>>n>>m;
	For(i,1,n){
		For(j,1,m){
			cin>>a[i].a[j];
		}
		cin>>a[i].w;
	}
	sort(a+1,a+1+n,[](G x,G y){
		return x.w<y.w;
	});
	int ans=ilinf;
	For(i,1,n)For(j,1,m){
		if(mp.find(a[i].a[j])==mp.end()){
			mp[a[i].a[j]]=rnd(1,13171);
		}
	}
	For(i,1,n){
		tem.reset();
		tem[0]=1;
		For(j,1,m){
			tem|=b[mp[a[i].a[j]]];
		}
		int pos=(~tem)._Find_first();
		if(pos<i){
			ans=min(ans,a[i].w+a[pos].w);
		}
		For(j,1,m)b[mp[a[i].a[j]]][i]=1;
	}
	cout<<(ans==ilinf?-1:ans)<<'\n';
	return;
}
```

---

## 作者：small_john (赞：1)

## 思路

神仙题。

考虑暴力。先把 $n$ 个序列按权值排序，然后对每个元素 $v$ 记录一个集合 $s_v$ 表示 $v$ 在那些序列里**出现过**。

对于每个序列 $i$，我们需要求出所有 $a_{i,j}$ 都没有出现过的集合中的第一个，即 $s_{a_{i,1}}\cup s_{a_{i,2}}\cdots \cup s_{a_{i,m}}$ 的补集中的第一个。用 bitset 维护这个集合的时间复杂度是可以被接受的，但是空间爆炸。

考虑根号分治优化空间。考虑一个阈值 $B$，分两种情况：

- 出现次数大于 $B$ 的数用 bitset 记录，这些数至多有 $\frac{nm}{B}$ 个，最多开 $\frac{nm}{B}$ 个 bitset。查询时与上文一样；
- 其他的数就用 vector 记录，查询时暴力遍历。

我们可以套路性的取 $B=\sqrt{nm}$，这样做的时间复杂度为 $O(nm\sqrt{nm}+\frac{n^2m}{\omega})$，空间复杂度为 $O(\frac{n\sqrt{nm}}{\omega})$，可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5,M = 5e5+5,B = sqrt(M);
int n,m,b[M],cnt;
struct node{
	int a[6],w;
	inline friend bool operator < (node x,node y)
	{
		return x.w<y.w;
	}
}a[N]; 
bitset<N> s[B+5],tmp;
vector<int> v[M]; 
map<int,int> ton;
int id[M],tot;
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i = 1;i<=n;i++)
	{
		for(int j = 1;j<=m;j++)
			cin>>a[i].a[j],b[++cnt] = a[i].a[j];
		cin>>a[i].w; 
	}
	sort(b+1,b+cnt+1),cnt = unique(b+1,b+cnt+1)-b-1;
	for(int i = 1;i<=n;i++)
		for(int j = 1;j<=m;j++)
			a[i].a[j] = lower_bound(b+1,b+cnt+1,a[i].a[j])-b;
	sort(a+1,a+n+1);
	for(int i = 1;i<=n;i++)
		for(int j = 1;j<=m;j++)
			ton[a[i].a[j]]++;
	for(int i = 1;i<=n;i++)
		for(int j = 1;j<=m;j++)
			if(ton[a[i].a[j]]>=B)
			{
				if(!id[a[i].a[j]]) id[a[i].a[j]] = ++tot;
				s[id[a[i].a[j]]].set(i);
			}
			else v[a[i].a[j]].push_back(i);
	int ans = 2e9+1;
	for(int i = 1;i<=n;i++)
	{
		tmp.reset();
		for(int j = 1;j<=m;j++)
			if(id[a[i].a[j]]) tmp|=s[id[a[i].a[j]]];
			else for(auto _:v[a[i].a[j]]) tmp.set(_);
		tmp = ~tmp;
		tmp.reset(0);
		if(tmp.count())
		{
			int p = tmp._Find_first();
			if(p>n) continue;
			ans = min(ans,a[p].w+a[i].w);
		}
	}
	if(ans>2e9) ans = -1;
	cout<<ans;
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

介绍一个随机化做法。

考虑计算瓶颈在于颜色数过多，考虑把颜色随机映射到 $[0,15)$ 中，这样做答案只会变差，但是有不低的概率取到正确答案，因为你一个不同位置有 $\frac{14}{15}$ 的概率映射后也不同，并且你的 check 会非常方便，具体而言你要找到最优的 $v1,v2$ 交为空，即 $v2$ 是 $v1$ 补集的子集，高维前缀 $\min$ 预处理再枚举 $v1$ 即可，做 $30$ 次即可通过。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxv = (1<<15);
const int maxn = 1e5+114;
const int maxm = 7;
int a[maxn][maxm];
int w[maxn];
int n,m;
int Min[maxv];
int mask[maxn];
int col[maxn*maxm];
int tot;
mt19937 rd(time(0));
int ans=1e18;
void work(){
    for(int i=0;i<maxv;i++) Min[i]=1e18;
    for(int i=1;i<=tot;i++) col[i]=rd()%15;
    for(int i=1;i<=n;i++){
        mask[i]=0;
        for(int j=1;j<=m;j++) mask[i]|=(1<<col[a[i][j]]);
        Min[mask[i]]=min(Min[mask[i]],w[i]);
    }
    for(int i=0;i<15;i++){
        for(int j=0;j<maxv;j++){
            if((1<<i)&j) Min[j]=min(Min[j],Min[j-(1<<i)]);
        }
    }
    for(int i=1;i<=n;i++) ans=min(ans,w[i]+Min[maxv-1-mask[i]]);
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    set<int> S;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin>>a[i][j],S.insert(a[i][j]);
        cin>>w[i];
    }
    for(int x:S) col[++tot]=x;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int l=1,r=tot+1;
            while(l+1<r){
                int mid=(l+r)>>1;
                if(a[i][j]>=col[mid]) l=mid;
                else r=mid;
            }
            a[i][j]=l;
        }
    }
    memset(col,0,sizeof(col));
    for(int i=1;i<=30;i++) work();
    cout<<(ans<=2e9?ans:-1)<<'\n';
    return 0;
}
```

---

## 作者：Arghariza (赞：0)

三年前的神仙题，放在现在已经是典中典了（而且还是非官方题解做法）。令人感慨。

考虑一个基于值域的做法。设值域为 $\{v_0,v_1,\cdots,v_{B-1}\}$，那么我们用 $B$ 位二进制数 $s_i$ 表示出每个 $a_i$ 的状态，第 $j$ 位为 $1$ 代表 $v_j\in a_i$。

枚举 $i$，考虑所有合法的 $j$，发现 $s_j$ 和 $s_i$ 必然无交，也就是说，$s_j$ 为 $s_i$ 补集的子集。于是我们对 $f_i=\min_{s_j=i}w_j$ 做一个高维前缀和（其实是前缀 $\min$），就能对每个 $i$ 快速求出 $\min(w_i+w_j)$。然后所有贡献取 $\min$ 即可。

上述做法复杂度为 $O(2^BB)$。于是我们合理考虑随机映射。具体地，$T$ 次将值域 $V$ 随机映射到集合 $\{0,1,\cdots,x-1\}$，然后用上述 $O(x2^x)$ 的做法跑 $T$ 次，并将 $T$ 次运算的结果取 $\min$。

考虑 $x,T$ 取何值时候正确率比较高，首先单次找到答案的概率为：
$$
\frac{x^{\underline{2m}}}{x^{2m}}=\frac{x!}{(x-2m)x^{2m}}
$$
那么 $T$ 次找到答案的概率为：
$$
P=1-\left(1-\frac{x!}{(x-2m)!x^{2m}}\right)^T
$$
由于这个做法常数看起来比较小，我们毛估估一下，总共可以进行 $a=2\times 10^8$ 次运算：
$$
T=\frac{a}{\max(nm,2^xx)}\\
P=1-\left(1-\frac{x!}{(x-2m)!x^{2m}}\right)^{\frac{a}{\max(nm,2^xx)}}
$$
![](https://cdn.luogu.com.cn/upload/image_hosting/ftwbc2ro.png)

观察图像，不难发现取 $x=15$ 时，$T$ 大概取 $400$，此时正确率 $P\ge0.9995$，足以通过此题。

```cpp
#include <bits/stdc++.h>
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second
#define F(i, x, y) for (int i = (x); i <= (y); i++)
#define R(i, x, y) for (int i = (x); i >= (y); i--)
#define FIO(FILE) freopen(FILE".in", "r", stdin), freopen(FILE".out", "w", stdout)

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
bool Mbe;

mt19937 rnd(time(0));

const int B = 15;
const int N = 1e5 + 5;
const int M = 5e5 + 5;
const int T = (1 << B) + 5;
const int inf = 2e9 + 5;

int n, m, len;
int a[N][5], w[N], st[N], c[M], id[M], f[T];

void solve() {
	cin >> n >> m;
	F (i, 1, n) {
		F (j, 0, m - 1) {
			cin >> a[i][j];
			c[++len] = a[i][j];
		}
		cin >> w[i];
	}
	sort(c + 1, c + len + 1);
	len = unique(c + 1, c + len + 1) - c - 1;
	F (i, 1, n) {
		F (j, 0, m - 1) {
			a[i][j] = lower_bound(c + 1, c + len + 1, a[i][j]) - c;
		}
	}
	int T = 400, S = (1 << B);
	ll res = inf;
	while (T--) {
		F (i, 1, len) {
			id[i] = rnd() % B;
		}
		F (i, 0, S - 1) {
			f[i] = inf;
		}
		F (i, 1, n) {
			st[i] = 0;
			int fl = 1;
			F (j, 0, m - 1) {
				if ((st[i] >> id[a[i][j]]) & 1) {
					fl = 0;
					break;
				}
				st[i] |= (1 << id[a[i][j]]);
			}
			if (fl) {
				f[st[i]] = min(f[st[i]], w[i]);
			} else {
				st[i] = 0;
			}
		}
		F (i, 0, B - 1) {
			F (j, 0, S - 1) {
				if ((j >> i) & 1) {
					f[j] = min(f[j], f[j ^ (1 << i)]);
				}
			}
		}
		F (i, 1, n) {
			if (st[i]) {
				res = min(res, (ll)w[i] + f[((1 << B) - 1) ^ st[i]]);
			}
		}
	}
	cout << (res >= inf ? -1 : res) << '\n';
}

bool Med;
int main() {
	// FIO("");
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：happybob (赞：0)

做法很多。

首先，根号分治 `bitset` 应该是简单的。注意到直接 `bitset` 瓶颈在于空间，考虑根号分治，只存出现次数 $>B$ 的数的 `bitset` 即可。跑得很快，[具体实现](https://codeforces.com/contest/1641/submission/293302602)。

另一方面，注意到 $[n= 0]=\sum \limits_{i=0}^n (-1)^i \dbinom{n}{i}$。这是简单的容斥。然后对于每个 $r$，枚举子集后哈希就可以容易求出前面有多少集合和其有交。找到一组 $(l,r)$ 后双指针即可。

---

## 作者：封禁用户 (赞：0)

把所有数按照 $w$
 排序之后，扫描 $a_r$，对 $r$
 去查一个最小的 $l$
 使得 $l,r$
 符合条件。

$r$
 是不断增大的，如果 $l$
 也跟着变大，答案肯定不如之前算的。所以 $l$
 是稳定变小的。

我们现在要快速判断 $[1,l]$
 这个区间里是否存在一个和 $a_r$
 互不相同的数。

互不相同很难计算，考虑容斥，枚举一个集合，统计前 $l$
 个里面这个集合的出现次数。统计这里可以 ```map```哈希统计。然后容斥完判断一下就行了。
 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,M=5;
int n,m,a[N][M],w[N],id[N],lsh[N*M],k,ans=2.1e9,pw[N*M],p[N];
mt19937 gen(time(0));
vector<int>g[N*M];
unordered_map<int,int>mp;
int cmp(int x,int y)
{
	return w[x]<w[y];
}
int ok(int x)
{
	int ret=0;
	for(int j=1;j<(1<<m);j++)
	{
		int ans=0,c=0;
		for(int k=0;k<m;k++)
			if(j>>k&1)
				ans^=pw[a[x][k]],c^=1;
		ret+=mp[ans];
	}
	return ret;
}
void ins(int x,int op)
{
	for(int j=1;j<(1<<m);j++)
	{
		int ans=0,c=0;
		for(int k=0;k<m;k++)
			if(j>>k&1)
				ans^=pw[a[x][k]],c^=1;
		mp[ans]+=c? op:-op;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<m;j++)
			scanf("%d",a[i]+j),lsh[++k]=a[i][j];
		scanf("%d",w+i),id[i]=i;
	}
	sort(lsh+1,lsh+k+1);
	k=unique(lsh+1,lsh+k+1)-lsh-1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<m;j++)
			a[i][j]=lower_bound(lsh+1,lsh+k+1,a[i][j])-lsh,g[a[i][j]].push_back(i),pw[a[i][j]]=gen()/2;
	}
	sort(id+1,id+n+1,cmp);
	p[0]=n;
	for(int i=1;i<=n;i++)
		ins(i,1);
	for(int i=1;i<=n;i++)
	{
		p[i]=p[i-1];
		if(ok(id[i])==p[i])
			continue;
		while(p[i])
		{
			ins(id[p[i]],-1);
			if(ok(id[i])==p[i]-1)
			{
				ins(id[p[i]],1);
				break;
			}
			else
				--p[i];
		}
		if(p[i])
			ans=min(ans,w[id[p[i]]]+w[id[i]]);
	}
	printf("%d",ans>=2100000000? -1:ans);
}
```


---

