# Set

## 题目描述

Define the binary encoding of a finite set of natural numbers $ T \subseteq \{0,1,2,\ldots\} $ as $ f(T) = \sum\limits_{i \in T} 2^i $ . For example, $ f(\{0,2\}) = 2^0 + 2^2 = 5 $ and $ f(\{\}) = 0 $ . Notice that $ f $ is a bijection from all such sets to all non-negative integers. As such, $ f^{-1} $ is also defined.

You are given an integer $ n $ along with $ 2^n-1 $ sets $ V_1,V_2,\ldots,V_{2^n-1} $ .

Find all sets $ S $ that satisfy the following constraint:

- $ S \subseteq \{0,1,\ldots,n-1\} $ . Note that $ S $ can be empty.
- For all non-empty subsets $ T \subseteq \{0,1,\ldots,n-1\} $ , $ |S \cap T| \in V_{f(T)} $ .

Due to the large input and output, both input and output will be given in terms of binary encodings of the sets.

## 说明/提示

In the first test case, one possible $ S $ is $ f^{-1}(3) = \{0,1\} $ . All the non-empty subsets $ T \subseteq \{0,1,2\} $ and the corresponding $ |S \cap T| $ , $ f(T) $ and $ V_f(T) $ are as follows:

  $ T $  $ |S\cap T| $  $ f(T) $  $ V_{f(T)} $  $ \{0\} $  $ 1 $  $ 1 $  $ \{0,1,2,3\} $  $ \{1\} $  $ 1 $  $ 2 $  $ \{0,1,2,3\} $  $ \{2\} $  $ 0 $  $ 4 $  $ \{0,1,2,3\} $  $ \{0,1\} $  $ 2 $  $ 3 $  $ \{0,1,2,3\} $  $ \{0,2\} $  $ 1 $  $ 5 $  $ \{0,1,2,3\} $  $ \{1,2\} $  $ 1 $  $ 6 $  $ \{0,1,2,3\} $  $ \{0,1,2\} $  $ 2 $  $ 7 $  $ \{2,3\} $

## 样例 #1

### 输入

```
3
15 15 15 15 15 15 12```

### 输出

```
4
3
5
6
7```

## 样例 #2

### 输入

```
5
63 63 63 63 6 63 63 63 63 63 63 5 63 63 63 63 63 63 8 63 63 63 63 2 63 63 63 63 63 63 63```

### 输出

```
1
19```

# 题解

## 作者：eastcloud (赞：9)

首先有个暴力做法：枚举所有的集合然后检查是否对所有约束都合法，这显然不太能过。

这样做的缺点在于你对两个相差不大的集合进行检查时会进行一些冗余操作（这也是大多数类似问题的突破口），于是我们考虑能不能用一些方法压缩约束快速判断。

考虑什么样的约束容易合并，由于这题里集合类似的约束其实相关性很大，我们尝试把这样的约束合并。

考察集合 $S$ 和集合 $S \cup v$：

- 如果我选 $v$，那么 $S\cup v$ 的约束直接右移一位和 $S$ 并上就是在剩下里面选数的约束

- 如果我不选 $v$，那么 $S\cup v$ 的约束直接并上 $S$ 就是新的。

注意这里讨论的是约束不是合法取值，所以用并，合法取值是类似的。

有了这个性质其实解法就很明了了：我们从高到底考虑是否选取当前位置上的数，然后根据选择合并约束，最后判断即可。


```cpp
int cons[N],tmp[21][N];
vector<int> res;
int n;
void copy(int k){
    for(int i=0;i<(1<<n);i++){
        if(i&(1<<k))break;
        tmp[k][i]=cons[i];
    }
}
void refresh(int k){
    for(int i=0;i<(1<<n);i++){
        if(i&(1<<k))break;
        cons[i]=tmp[k][i];
    }
}
void solve(int k,int now){
    if(k==-1){if(cons[0]&1)res.push_back(now);return;}
    int T=(1<<k);copy(k);
    for(int i=(1<<k);i<(1<<(k+1));i++)cons[i^T]&=cons[i];
    solve(k-1,now);refresh(k);
    for(int i=(1<<k);i<(1<<(k+1));i++)cons[i^T]&=(cons[i]>>1);
    solve(k-1,now|(1<<k));
}
int main(){
    #ifdef EAST_CLOUD
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    #endif
    n=read();cons[0]=(1<<(n+1))-1;
    for(int i=1;i<(1<<n);i++)cons[i]=read();
    solve(n-1,0);
    write(res.size());putchar('\n');
    for(auto v:res)write(v),putchar('\n');
}
```

---

## 作者：_lmh_ (赞：8)

问题难点在于给定 $2^n$ 个限制 $\{v_i\}$，同时对于所有 $2^n$ 位置询问。直接做是 $2^{2n}$ 的，无法接受。

考虑**按位**做。下方推导过程中，以小写字母表示集合转化后得到的数，以大写字母表示集合。如，$f(S)=s,f^{-1}(s)=S$。

具体地，考虑最高位 $2^{n-1}$，就可以将 $2^n$ 个询问转换为两个大小为 $2^{n-1}$ 的子问题。

注意到
$$
\forall t \in [0,2^{n-1}-1], |S \cap f^{-1}(t+2^{n-1})| = |S \cap f^{-1}(t)| + [(n-1) \in S]
$$

更进一步，如果 $S$ 不包含 $n-1$，那么
$$
\forall t \in [0,2^{n-1}-1], |S \cap f^{-1}(t)| \in f^{-1}(t) \cap f^{-1}(t+2^{n-1})
$$

右边这个式子等价于把 $v_t$ 和 $v_{t+2^{n-1}}$ 求按位与。这样我们就把限制缩小了一半。

否则，
$$
\forall t \in [0,2^{n-1}-1], |S \cap f^{-1}(t)| \in f^{-1}(t) \wedge |S \cap f^{-1}(t)|+1 \in f^{-1}(t+2^{n-1})
$$
等价于把 $v_t$ 和 $\lfloor\frac{v_{t+2^{n-1}}}{2}\rfloor$ 求按位与。

其实写到这里对每个位置 dfs 就可以通过，但是这样不够优雅。

发现 dfs 常数比较大~~虽然也能过~~，考虑 FFT 从递归写法转化成非递归写法的过程，直接把 $v_t$ 和 $v_{t+2^{n-1}}$ 修改成上面的按位与求出的结果，就可以分割成两个子问题，并且会发现最后 $v_s\mod 2$ 就是 s 的答案。

小细节：输入里没有 $v_0$，记得初始化为 $1$。

做法比较类似 FWT 的过程。代码非常短。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1050007;
ll n,a[N],m,ans,cnt[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;m=1<<n;
	for (int i=1;i<m;++i) {cin>>a[i];}
	a[0]=1;
	for (int i=m>>1;i;i>>=1) for (int j=0;j<m;j+=(i<<1)) for (int k=0;k<i;++k){
		ll p=a[j|k],q=a[i|j|k];
		a[j|k]=p&q;a[i|j|k]=p&(q>>1);
	}
	for (int i=0;i<m;++i) ans+=(a[i]&1);
	cout<<ans<<'\n';
	for (int i=0;i<m;++i) if (a[i]&1) cout<<i<<'\n';
	return 0;
}
```

---

## 作者：hez_EX (赞：7)

#### upd，题解已经过审过，修改了定理 1 处的笔误

好题！于是写一篇题解记录一下。

乍一看无论怎么做时间复杂度都是 $\mathcal{O}(2^{2n})$ 的，于是我们考虑按位处理。

### 遇事不决，先推式子

这里我们钦定读者已经掌握了[艾弗森括号](https://baike.baidu.com/item/%E8%89%BE%E4%BD%9B%E6%A3%AE%E6%8B%AC%E5%8F%B7/22361197)。

我们约定大写字母表示集合，小写字母表示其对应的二进制表示。约定映射 $f(S)=s,f^{-1}(s)=S$。

先指出两个显然的定理：
1. 若有 $a\in f^{-1}(s)$，则 $a+1\in f^{-1}(s\times2)$。  
此处的 $s\times2$ 即 $s$ 右移一位。
2. 若有 $S\in f^{-1}(a),S\in f^{-1}(b)$，则 $S\in f^{-1}(a\wedge b)$。

对于某个已经在开头 $n$ 位合法的 $s$，现在考察其第 $n-1$ 位的情况，考察：
$$\forall t\in[0,2^{n-1}),|S\cap f^{-1}(t)|\in^?f^{-1}(v_{t})$$
$$\forall t\in[0,2^{n-1}),|S\cap f^{-1}(t+2^{n-1})|\in^?f^{-1}(v_{t+2^{n-1}})$$

对于下面一种情况，显然有:
$$\forall t\in[0,2^{n-1}),|S\cap f^{-1}(t)|+[n-1\in S]\in^?f^{-1}(v_{t+2^{n-1}})$$

分讨 $n-1\in S$ 的情况。  
若 $n-1\in S$，上式结合最初我们提到的定理一可得：
$$\forall t\in[0,2^{n-1}),|S\cap f^{-1}(t)|\in^?f^{-1}(v_{t+2^{n-1}}\times2)$$
再把之前的第一式也放过来：
$$
\forall t\in[0,2^{n-1}),
\left\{\begin{matrix}
|S\cap f^{-1}(t)|\in^?f^{-1}(v_{t}) \\
|S\cap f^{-1}(t)|\in^?f^{-1}(v_{t+2^{n-1}}\times2)
\end{matrix}\right.
$$

利用定理二合并：
$$\forall t\in[0,2^{n-1}),|S\cap f^{-1}(t)|\in^?f^{-1}(v_{t}\wedge(v_{t+2^{n-1}}\times2)))$$

另一种情况的讨论同理，读者自推不难，这里只放出结果。

 - 当 $n-1\in S$ 时：$\forall t\in[0,2^{n-1}),|S\cap f^{-1}(t)|\in^?f^{-1}(v_{t}\wedge(v_{t+2^{n-1}}\times2)))$
 - 当 $n-1\notin S$ 时：$\forall t\in[0,2^{n-1}),|S\cap f^{-1}(t)|\in^?f^{-1}(v_{t}\wedge v_{t+2^{n-1}})$

推到这里，我们发现不妨先后钦定 $S$ 的第 $n-1$ 位为 $0$ 和 $1$，然后进行递归，这样每次区间就会由 $[0,2^{n})$ 缩到 $[0,2^{n-1})$，这样一共进行 $\log(n)$ 次量级的递推，每次会完整地将整个限制合并一遍共 $n$ 次，总时间复杂度为 $\mathcal{O}(n\log n)$。

### [AC](https://codeforces.com/contest/1975/submission/267152601) 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cctype>
#include <vector>
using namespace std;
inline void read(int &x)
{
	char c=getchar();x=0;
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-48,c=getchar();
}
vector<int> V,ans;
void dfs(int s,vector<int> v,int l)
{
	if(l==0)
	{
		if(v[0]&1) ans.push_back(s);
		return;
	}
	int n=1<<l;
	vector<int> sub;
	for(int i=0;i<n>>1;i++) sub.push_back(v[i]&v[i+(n>>1)]);
	dfs(s,sub,l-1);sub.clear();
	for(int i=0;i<n>>1;i++) sub.push_back(v[i]&(v[i+(n>>1)]>>1));
	dfs(s|(1<<l>>1),sub,l-1);
}
int main()
{
	int n=0,l=0;
	read(l);n=1<<l;
	for(int i=1,u;i<n;i++) read(u),V.push_back(u);
	V.insert(V.begin(),1);
	dfs(0,V,l);
	printf("%d\n",ans.size());
	for(int i:ans) printf("%d\n",i);
	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：5)

神仙题，看了好久题解才看懂，那就来写一篇比较详细的题解并给出一个较为简洁的实现吧 qwq

我们记 $s=f(S),S=f^{-1}(s)$，即小写字母表示集合转化后得到的数，大写字母表示集合。记 $\land$ 表示**按位与**，即 C++ 中的 `&`。

题目里面 $T\neq\emptyset$ 的限制不太符合常理，我们先把这个限制解除。由于 $\lvert S\cap \emptyset\rvert=0$，所以令 $v_0=1$ 即可。下文不再有该限制。

观察 $S$ 合法的条件：
$$\forall t\in[0,2^n),\lvert S\cap f^{-1}(t)\rvert\in f^{-1}(v_t)$$

我们考虑把 $t$ 的 $2^{n-1}$ 这位拆出来，条件变为：
$$
\forall t\in[0,2^{n-1}),
\begin{cases}
\lvert S\cap f^{-1}(t)\rvert\in f^{-1}(v_t)\\
\lvert S\cap f^{-1}(t)\rvert+[(n-1)\in S]\in f^{-1}(v_{t+2^{n-1}})
\end{cases}
$$

分讨 $S$ 中是否有 $(n-1)$：
- 若有，则第二个条件变为 $\lvert S\cap f^{-1}(t)\rvert+1\in f^{-1}(v_{t+2^{n-1}})$，即 $\lvert S\cap f^{-1}(t)\rvert\in f^{-1}(\lfloor\frac{v_{t+2^{n-1}}}{2}\rfloor)$。联立第一个条件得到 $\lvert S\cap f^{-1}(t)\rvert\in f^{-1}(v_t)\cap f^{-1}(\lfloor\frac{v_{t+2^{n-1}}}{2}\rfloor)$，也就是：
$$\forall t\in[0,2^{n-1}),\lvert S\cap f^{-1}(t)\rvert\in f^{-1}(v_t\land \lfloor\frac{v_{t+2^{n-1}}}{2}\rfloor)$$
- 若没有，第二个条件变为 $\lvert S\cap f^{-1}(t)\rvert\in f^{-1}(v_{t+2^{n-1}})$，联立第一个条件得
$$\forall t\in[0,2^{n-1}),\lvert S\cap f^{-1}(t)\rvert\in f^{-1}(v_t\land v_{t+2^{n-1}})$$

对照最前面 $S$ 合法的条件，我们发现我们已经将原问题分解为了两个规模为 $2^{n-1}$ 的子问题，递归下去即可解决。当 $n=0$ 时，$\lvert S\cap f^{-1}(t)\rvert=0$，若此时 $v_t\bmod 2=1$ 就有 $S$ 合法。

至于实现，我们可以不真地递归下去，而是从 $(n-1)$ 到 $0$ 枚举 $k$，对每个 $k$ 枚举形如 $[0,2^k),[2^k,2\times2^k),[2\times 2^k,3\times 2^k),\cdots$ 的区间分成两半即可。具体实现见代码，非常简洁。

时间复杂度 $\mathcal{O}(n2^n)$。

参考代码：
```cpp
... //  下文 REP(i, l, r) 表示从 l 到 r 枚举 i
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 2e6 + 5;
	int n, ct, v[N];
	int main() {
		cin >> n, v[0] = 1; // 去除 T 不为空的限制
		REP(i, 1, (1 << n) - 1) cin >> v[i];
		for (int k = 1 << (n - 1); k; k >>= 1) // 长度为 2k 的区间分成前后长度为 k 的两半
			REP(i, 0, (1 << n) - 1) {
				if (i & k) continue; // 是否在区间中的前一半，若在后一半则跳过
				int x = v[i], y = v[i + k];
				v[i] = x & y, v[i + k] = x & y >> 1; // 同时处理前后两半中对应的数
			}
		REP(i, 0, (1 << n) - 1) ct += v[i] & 1;
		cout << ct << '\n';
		REP(i, 0, (1 << n) - 1)
			if (v[i] & 1) cout << i << '\n';
		return 0;
	}
}
```

---

## 作者：云浅知处 (赞：3)

搞了一个很笨的 $O(n^22^n)$ 做法，好像和官方题解不太一样......QAQ

以下用 $V_T$ 代指题目中的 $V_{f(T)}$。

对于 $S$，考虑计算 $f_S=\sum_{T}[|S\cap T|\in V_T]$，则只需判断是否有 $f_S=2^n$。枚举 $|S\cap T|$，这就是
$$
f_S=\sum_{i=0}^n\sum_T[|S\cap T|=i][i\in V_T]
$$
枚举 $i$，把问题泛化为：给定序列 $A_{0\cdots 2^n-1},B_{0\cdots 2^n-1}$，计算
$$
C_S=\sum_{T}A_{S\cap T}\times B_T
$$
那么这里就是 $A_T=[|T|=i],B_T=[i\in V_T]$。发现 $S\cap T$ 不好处理，把 $A$ 做高维前缀差分得到 $a$，即
$$
A_S=\sum_{T\subseteq S}a_T
$$
那么有
$$
C_S=\sum_TB_T\sum_{P\subseteq (S\cap T)}a_P=\sum_{P\subseteq S}a_P\sum_{P\subseteq T}B_T
$$
于是我们先做一遍高维后缀和算出 $E_P=\sum_{P\subseteq T}B_T$，然后令 $E_P\leftarrow E_P\times a_P$，再做高维前缀和即可得到 $C$。

于是我们可以在 $O(n2^n)$ 时间内算出所有 $C$，加上外层枚举 $i$ 的复杂度，总复杂度 $O(n^22^n)$。

直接写大概过不去，不过我们注意到对 $A$ 做高维前缀差分的结果可以直接算出：$a_S=(-1)^{i+|S|}\binom{|S|}{i}$，于是可以少一遍 FMT；然后加上 `#pragma GCC optimize("Ofast,unroll-loops")` 即可通过。

```cpp
#pragma GCC optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>

#define ll long long
#define mk make_pair
#define fi first
#define se second

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

template<typename T>void cmax(T &x,T v){x=max(x,v);}
template<typename T>void cmin(T &x,T v){x=min(x,v);}

const int N=21;
int n,Sets[1<<N];
void fmt_pre(int *A,int k){
	for(int i=0;i<k;i++)for(int S=0;S<(1<<k);S++)if(S&(1<<i))A[S]+=A[S^(1<<i)];
}
void fmt_suf(int *A,int k){
	for(int i=0;i<k;i++)for(int S=0;S<(1<<k);S++)if(S&(1<<i))A[S^(1<<i)]+=A[S];
}

int f[1<<N],sum[1<<N],g[1<<N],C[N][N];

signed main(void){

#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif

	n=read();Sets[0]=(1<<(n+1))-1;
	for(int S=1;S<(1<<n);S++)Sets[S]=read();

	C[0][0]=1;
	for(int i=1;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
	}

	for(int i=0;i<=n;i++){
		for(int S=0;S<(1<<n);S++){
			int p=__builtin_popcount(S);
			if((p+i)&1)f[S]=-C[p][i];
			else f[S]=C[p][i];
		}

		for(int S=0;S<(1<<n);S++)g[S]=((Sets[S]>>i)&1);
		fmt_suf(g,n);

		for(int S=0;S<(1<<n);S++)g[S]*=f[S];
		fmt_pre(g,n);
		for(int S=0;S<(1<<n);S++)sum[S]+=g[S];
	}

	vector<int>ans;
	for(int S=0;S<(1<<n);S++)if(sum[S]==(1<<n))ans.emplace_back(S);
	cout<<ans.size()<<'\n';
	for(int S:ans)cout<<S<<'\n';

	return 0;
}
```

---

## 作者：lfxxx (赞：1)

思维题加训。

注意到我们要求解的问题是计数 $s \in [0,2^n)$ 满足对于任意 $t \in [1,2^n)$ 有 $|f^{-1}(s) \cap f^{-1}(t)| \in V_t$。

首先令 $V_0 = f(0)$ 后认为 $t$ 可以为 $0$。

不妨从高往低按位考虑，现在考虑第 $h$ 位并令 $s$ 的前 $h-1$ 位构成的数为 $s'$。

假若第 $h$ 位填的是 $1$。

那么需要对于 $t \in [0,2^{h-1})$ 有 $|f^{-1}(s') \cap f^{-1}(t)| \in V_t$ 且对于 $t \in [2^{h-1},2^h)$ 有 $|f^{-1}(s') \cap f^{-1}(t)| \in V_t$ 而这是因为第 $h$ 位一定不在交集中。

合并两个限制，得到对于 $t \in [0,2^{h-1})$ 有 $|f^{-1}(s') \cap f^{-1}(t)| \in V_t \cap V_{t+2^{h-1}}$。

否则，需要对于 $t \in [0,2^{h-1})$ 有 $|f^{-1}(s') \cap f^{-1}(t)| \in V_t$ 且对于 $t \in [2^{h-1},2^h)$ 有 $|f^{-1}(s') \cap f^{-1}(t)| + 1 \in V_t$。

观察 $|f^{-1}(s') \cap f^{-1}(t)| + 1 \in V_t$ 这个奇怪的限制，我们注意到，假若令 $V_t$  集合整体向前平移一位，得到新集合 $V_{t}'$，这样做虽然可能会挤掉第一个元素，但是那与限制无关，而且我们可以得到 $|f^{-1}(s') \cap f^{-1}(t)| \in V_{t}'$ 这个新限制，继续与上面限制合并，得到对于 $t \in [0,2^{h-1})$ 有 $|f^{-1}(s') \cap f^{-1}(t)| \in V_t \cap V_{t+2^{h-1}}'$。

不难发现上面两个限制合并后，限制全部被我们放到了前 $h-1$ 位也就是 $s'$ 上，而且递归到第 $h-1$ 位时集合限制大小都减半了，当 $h = 0$ 也就是 $t = 0$ 时，只有 $0 \in V_{t}$ 中时才会得到合法解（这也是为什么要将 $V_0$ 设置为 $f(0)$ 而不是其他值的原因）。

设处理最高 $h$ 位的问题时间复杂度是 $T(h)$，有 $T(h) = 2 \times T(h-1) + 2^h$，因此时间复杂度为 $O(n 2^n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> ans;
void dfs(int h,vector<int> v,int lst){//前面确定的位之和
    if(h==0){
        if((1<<0)&v[0]) ans.push_back(lst);
        return ;
    }
    vector<int> ls,rs;
    for(int i=0;i<(1<<(h-1));i++) ls.push_back(v[i]),rs.push_back(v[i]);
    //不选
    for(int i=0;i<(1<<(h-1));i++) ls[i]&=v[i+(1<<(h-1))],rs[i]&=(v[i+(1<<(h-1))]>>1);
    dfs(h-1,ls,lst);
    dfs(h-1,rs,lst+(1<<(h-1)));
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n;
    cin>>n;
    vector<int> v={1};
    for(int i=1;i<(1<<n);i++){
        int x;
        cin>>x;
        v.push_back(x);
    }
    dfs(n,v,0);
    cout<<ans.size()<<'\n';
    for(int x:ans){
        cout<<x<<'\n';
    }
    return 0;
}

```

---

## 作者：zzzYheng (赞：1)

首先限制可以转化为 $ans$ 和 $x$ 的交的大小不能为 $i$。

这种二进制数题目，首先可以考虑二进制拆两半的暴力做法，就像数据结构题可以先考虑分块一样。

令 $x'$ 表示 $x$ 前 $\frac{n}{2}$ 位的值，$x''$ 表示 $x$ 后 $\frac{n}{2}$ 位的值。

对于一个限制 $(x,i)$，我们枚举 $ans$ 的前 $\frac{n}{2}$ 位 $ans'$，那么限制可以转化为 $ans''$ 和 $x''$ 的交不能为 $i-|x'\cap ans'|$。

这样就得到了 $\Theta(2^n\cdot 2^{\frac{n}{2}})$ 个形如 $(x,y,i)$ 表示前一半为 $x$ 的数后一半不能与 $y$ 的交大小 $i$ 这样的限制。

然后我们枚举 $ans$，只有形如 $(ans',y,i)$ 的限制对其是有效的，暴力判断即可做到时间复杂度 $\Theta(2^{n}\cdot 2^{\frac{n}{2}})$。

上述做法中我们枚举前 $\frac{n}{2}$ 位把限制转化成对后 $\frac{n}{2}$ 的限制。这可以进一步改进，我们可以一位一位枚举取值，一位一位缩小限制。

具体而言可以 $\text{dp}$，令 $f_{x,y}$ 表示对包含前缀 $x$ 的数，与后缀 $y$ 的交的大小的限制。

枚举第 $|x|+1$ 位的取值即可完成转移。具体实现的时候可以把 $x$ 和 $y$ 拼接起来记为 $j$，再用个 $i$ 记录分界点即可。

时间复杂度 $\Theta(2^{n}\cdot n)$。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 21;
const int kMaxPowN = (1 << 20) + 5;

int n;

int v[kMaxPowN];

int f[kMaxN][kMaxPowN];

vector<int> ans;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	for (int i = 1; i < (1 << n); ++i) {
		cin >> v[i];
		f[0][i] = (1 << n + 1) - 1 ^ v[i];
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < (1 << n); ++j) {
			if ((j & (1 << i - 1)) == 0) {
				f[i][j] |= f[i - 1][j];
				f[i][j ^ (1 << i - 1)] |= f[i - 1][j];
			}
			else {
				f[i][j ^ (1 << i - 1)] |= f[i - 1][j];
				f[i][j] |= f[i - 1][j] >> 1;
			}
		}
	}
	for (int i = 0; i < (1 << n); ++i) {
		if (!(f[n][i] & 1)) ans.emplace_back(i);
	}
	cout << ans.size() << '\n';
	for (auto it : ans) cout << it << '\n';
	return 0;
}
```

---

## 作者：ricky0916 (赞：1)

比较简单的一道题。

从高到低枚举每一位是什么，第 $i$ 位根据 $ V_{2^i} $ 判断是否符合条件。如果第 $ i $ 位确定，即可把 $ V_{0} $ 到 $V_{2^i-1}$ 与 $ V_{2^i+1} $ 到 $ V_{2^{i+1}-1} $ 这些集合对应合并，继续考虑剩下其他位的情况。显然，合并前后条件是等价的。

时间复杂度 $O(n 2^n)$。

场上在还剩 7 分钟的时候开始写，剩两分钟的时候发现输出格式错了，还剩十秒的时候交。然后发现临时变量存在了一个公共的位置，我真是服了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x;
}
void write(long long x){
	static int sta[20];
	int top=0;
	if(x<0) putchar('-'),x=-x;
	do{
		sta[top++]=x%10,x/=10;
	}while(x);
	while(top) putchar(sta[--top]+48);
}
void we(long long x){
	write(x);
	putchar('\n');
}
void put(string s){
	int len=s.length();
	for(int i=0;i<len;i++){
		putchar(s[i]);
	}
}
int t,n,v[3000010],vv[3000010],vvv[23][3000010],tot,ans[2000010];
void dfs(int dep,int ttt){
	if(dep==0){
		ans[++tot]=ttt;
		return;
	}
//	cout<<dep<<" "<<ttt<<endl;
	if(vv[1<<(dep-1)]&1){
		for(int i=1;i<=(1<<(dep-1))-1;i++) vvv[dep][i]=vv[i],vv[i]=vv[i]&vv[i+(1<<(dep-1))];
		dfs(dep-1,(ttt<<1));
		for(int i=1;i<=(1<<(dep-1))-1;i++) vv[i]=vvv[dep][i];
	}
	if(vv[1<<(dep-1)]&2){
		for(int i=1;i<=(1<<(dep-1))-1;i++) vvv[dep][i]=vv[i],vv[i]=vv[i]&(vv[i+(1<<(dep-1))]>>1);
		dfs(dep-1,(ttt<<1)|1);
		for(int i=1;i<=(1<<(dep-1))-1;i++) vv[i]=vvv[dep][i];
	}
}
int main(){
	n=read();
	for(int i=1;i<=(1<<n)-1;i++) v[i]=read();
	memcpy(vv,v,sizeof(vv));
	dfs(n,0);
	we(tot);
	for(int i=1;i<=tot;i++) we(ans[i]);
	return 0;
}
```

---

## 作者：strcmp (赞：0)

考虑分治。

建立类似 0-1 trie 的结构，然后按位考虑 $s$ 的取值。

因为题目相当于是判断 $|s \cap t|$ 是否在 $v_t$ 中。

设当前 $s$ 的当前位取 $0$，则我们完全可以把当前位是 $1$ 的 $v$ 位与到当前位是 $0$ 的 $v$ 上去。这是因为 $s$ 当前位是 $0$，代表 $t$ 的当前位无论取什么对 $|s \cap t|$ 都没有影响。进而是 $1$ 的 $v_t$ 的限制可以合并到当前位是 $0$ 的 $v$ 上去，不影响答案。$s$ 当前位是 $1$ 同理，反过来即可。注意如果记录 $s$ 的大小，则是这种情况 $v$ 要先右移再位与。

分治即可。

时间复杂度 $T(2^n) = 2T(2^{n-1}) + \Theta(2^n) = \Theta(n2^n)$。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define mid (l + r >> 1)
#define rep(i, a, b) for(int i = a; i <= b; i++)
using namespace std;
typedef long long int ll;
using pii = pair<int, int>;
const int maxn = (1 << 21) + 10, mod = 998244353; 
int n, v[maxn], d[maxn], p[maxn], ans[maxn], len = 0;
void solve(int l, int r, int x) {
	int w = p[x];
	if (l == r) { 
		//cout << x << " " << l << " " << d[l] << " " << v[l] << "\n";
		if (d[l] & 1 && v[l] >> w & 1) ans[++len] = x;
		return;
	}
	vector<int> q;
	rep(i, l, r) q.push_back(d[i]);
	rep(i, l, mid) d[i] &= d[mid - l + i + 1];
	//, cout << d[i] << " "; cout << "\n";
	solve(l, mid, x << 1);
	rep(i, l, r) d[i] = q[i - l];//, cout << d[i] << " "; cout << "\n";
	rep(i, mid + 1, r) d[i] >>= 1;
	rep(i, mid + 1, r) d[i] &= d[i - mid + l - 1];
	solve(mid + 1, r, x << 1 | 1);
}
int main() {
	//freopen("set.in", "r", stdin);
	//freopen("set.out", "w", stdout);
	scanf("%d", &n); 
	for (int i = 1; i < 1 << n; i++) scanf("%d", &v[i]), d[i] = v[i]; d[0] = v[0] = (1 << n + 1) - 1;
	for (int i = 1; i < maxn; i++) p[i] = p[i >> 1] + (i & 1);
	solve(0, (1 << n) - 1, 0);
	printf("%d\n", len);
	for (int i = 1; i <= len; i++) printf("%d\n", ans[i]);
	return 0;
}
/* 
3 
15 15 15 15 15 15 12

6
123 11 31 35 47 7 79 3 23 7 63 7 95 79 31 55 87 39 15 15 95 47 31 23 15 15 31 15 63 63 127 15 111 71 47 7 31 127 63 55 15 15 31 31 95 95 63 7 15 79 95 95 63 95 63 79 63 31 127 31 63 127 127

*/
```

---

## 作者：Galois_Field_1048576 (赞：0)

**明确记号.** 由于本题涉及位运算，明确所使用的二进制数学记号如下：$\wedge$ 表示按位与运算 `&`，$\vee$ 表示按位或运算 `|`，$\oplus$ 表示按位异或运算 `^`，$\ll$ 表示左移运算 $a \ll b = a2^b$，$\gg$ 表示右移运算 $a \gg b = \left\lfloor\dfrac a{2^b}\right\rfloor$。本文不区分集合 $S$ 与其二进制表示 $\sum_{x \in S} 2^x$，因此 $\cap, \wedge$、$\cup,\vee$ 等可以视为同一运算。

若 $T = A \sqcup B$，则显然 $|S \cap T| = |S \cap A| + |S \cap B|$。特别地，取 $B = \{x\}$ 得 $|S \cap T| = |S \cap A| + [x \in S]$。现在让 $T$ 取遍 $\mathscr P(\{0, \dots, n-1\})$（$\mathscr P$ 表示幂集），则有双射 $\{T:x\in T\} \leftrightarrow \{T : x \notin T\}$：将 $T$ 映向 $T \setminus \{x\}$。题目中的约束告诉我们 $|S \cap T| \in c_T$，根据上述讨论：
* 若 $x \in S$：$|S \cap T| = |S \cap (T \setminus \{x\})| + 1$，故 $|S \cap T| \in c_T \implies |S \cap (T \setminus \{x\})| \in c_T \gg 1$，而 $|S \cap (T \setminus \{x\})|$ 同时也需要属于 $c_{T \setminus \{x\}}$，故可知：
  $$
  |S \cap (T \setminus \{x\})| \in (c_T \gg 1) \wedge c_{T \setminus \{x\}} \iff \text{关于 $T$ 和 $T \setminus \{x\}$ 的条件都被满足。}
  $$
* $x \notin S$：同样地，可以发现
  $$
  |S \cap (T \setminus \{x\})| \in c_T \wedge c_{T \setminus \{x\}} \iff \text{关于 $T$ 和 $T \setminus \{x\}$ 的条件都被满足。}
  $$
  
所以我们如果确定 $x \in S$ 或 $x \notin S$，则我们可以将剩下的约束两两合并。所以考虑递归：我们已经确定了 $1, 2, \dots, m$ 是否属于 $S$，并且根据这些 $S$，我们将原来的约束 $C_0$ 缩小到了 $C_m$（由于每次缩小都会缩小一半，$|C_m| = 2^{-m}|C_0|$），容易通过分类讨论进行递归。注意到 $C_m \to C_{m+1}$ 的时间复杂度为 $\Theta(|C_m|)$，故总时间复杂度可以分析为
$$
T(n) = 2T(n-1)+2^{N-n},
$$
其中 $N$ 是原来的那个 $n$，故时间复杂度 $\Theta(T(N)) = \Theta(N2^N)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
vi merge(vi a, vi b) {
    vi c;
    for (int x : a) c.push_back(x);
    for (int x : b) c.push_back(x);
    return c;
}

vi dfs(int dep, vi cons, int pref) {
    if (dep == 0) {
        if (cons[0] & 1)
            return {pref};
        else
            return {};
    }
    dep--;
    vector<vi> new_cons(2);
    int m = cons.size() / 2;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < 2; j++)
            new_cons[j].push_back(cons[i] & (cons[i + m] >> j));
    return merge(dfs(dep, new_cons[0], pref),
                 dfs(dep, new_cons[1], pref + (1 << dep)));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vi a((1 << n) - 1);
    for (int &x : a) cin >> x;
    a.insert(a.begin(), 1);
    vi ans = dfs(n, a, 0);
    cout << ans.size() << endl;
    for (int x : ans) cout << x << '\n';
}
```

---

