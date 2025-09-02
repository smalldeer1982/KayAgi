# [ARC155F] Directable as Desired

## 题目描述

给定一个长度为 $N$ 的非负整数序列 $D=(D_1, D_2, \dots, D_N)$。

请计算有多少个满足以下条件的、编号为 $1$ 到 $N$ 的 $N$ 个顶点的有标号树，并将答案对 $998244353$ 取模：

- 可以对 $N-1$ 条边进行适当的定向，使得每个顶点 $i\ (1\leq i \leq N)$ 的出度恰好为 $D_i$。

## 说明/提示

## 限制条件

- $2 \leq N \leq 2 \times 10^5$
- $0 \leq D_i \leq N-1$
- $\sum_{i=1}^{N} D_i = N-1$
- 输入的所有值均为整数

## 样例解释 1

满足条件的树（以及其一种定向方式）如下图所示，共有 $5$ 种。  
![](https://img.atcoder.jp/arc155/5b5b99752b5330a2dd41607c3946fdd4.jpg)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
0 1 0 2```

### 输出

```
5```

## 样例 #2

### 输入

```
5
0 1 1 1 1```

### 输出

```
125```

## 样例 #3

### 输入

```
15
0 0 0 0 0 0 0 1 1 1 1 1 2 3 4```

### 输出

```
63282877```

# 题解

## 作者：william555 (赞：7)

很离谱的计数题。

首先可以发现，对于每个无向树，我们从叶子开始分配方向，至多只有一种分配方案满足 $D$ 的条件。于是，满足条件的无向树就和每个点出度分别为 $D_i$ 的有向树一一对应（注意，是有向树，不是内向/外向树）。

直接算有向树比较抽象，于是我们给树指定一个根，再将每个点的出边编号。而原来的一颗无根有向树就对应了 $n \cdot \prod D_i !$ 棵“有根有向边有编号”树。

然后我们来计算这样的树的数量。由于有了根，那么每一条边的方向就要么是父亲指向儿子（向下），要么是儿子指向父亲（向上）。我们分开计算这两种边的方案。

于是计算过程可以分为一下三步：

1. 枚举一个点集 $S$，规定只有 $S$ 中的点和父亲之间的边是向上的，且对于 $S$ 中的每个点，选出其向上的这条边的编号，方案数为 $\prod_{i\in s} D_i$。
2. 计算给这些向上的边确定每条边的终点的方案数。
3. 计算向下的边每条边确定终点的方案数。

令 $m= |S|$。

第三步是最好做的，由于每一条边都有了编号，那么我们按编号顺序一条一条确定终点。因为是向下的边，所以终点必须还没有父亲，又因为不能有环，终点不能是起点的祖先。第二步以后还剩下 $n-m$ 个弱连通块，所以第一条边的终点有 $n-m-1$ 种选择（每个弱连通块只有一个没有祖先的点，还不能选和起点一个若联通块的那个）。以此类推，第 $i$ 条边有 $n-m-i$ 种选择，所以第三步一共有 $(n-m-1)!$ 种方案。

再看第二步，第二步执行之后的结果是 $n$ 个点，$m$ 条边的内向树森林，森林不好算，我们添加一个“超级根” $0$，让所有没父亲的点连一条边指向 $0$。那么现在就是要算以 $0$ 为根，且 $0$ 的入度为 $n-m$ 的内向树有多少棵。有根内向树的方案显然和无根无向树的方案一一对应，所以用 prufer 序来计算。指定 prufer 序每一项是最大标号叶子的父亲，则 $0$ 一定会成为最后留下来两个点之一，在 prufer 序中 $0$ 就一定会出现 $n-m-1$ 次，所以 prufer 序的方案数是 $C_{n-1}^{n-m-1}\cdot n^m$，但是这样算出来的结果包含了指定 $S$ 集合的方案，但这是第一步算的内容，所以我们要除掉 $C_n^m$，最后得到第二步的结果为 $n^{m-1}\cdot(n-m)$。

于是，最后的答案可以写为：
$$
\sum_{m=0}^n (n-m-1)!\cdot n^{m-1}\cdot(n-m)\cdot\sum_{|S|=m} \prod _{i\in S} D_i
$$
然后对于 $\sum_{|S|=m} \prod _{i\in S} D_i$，可以直接使用背包计算，复杂度 $O(n^2)$。使用分治 NTT，就可复杂度 $O(n\log^2n)$。

但是注意到这道题满足 $\sum D_i =n-1$，我们可以先把相同的 $D_i$ 一起用二项式定理算出来，然后按 $D_i$ 从大到小乘起来。$D \ge i$ 的至多有 $\dfrac n i$ 项，所以总复杂度不超过 $\sum \dfrac ni \log \dfrac n i$ ，据说是 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1<<18|5,mod=998244353;
inline int add(int a,int b){return a+b>=mod?a+b-mod:a+b;}
inline int mul(int a,int b){return 1ll*a*b%mod;}
inline int qpow(int a,int b){
	int c=1;
	for(;b;b>>=1,a=mul(a,a))if(b&1)c=mul(c,a);
	return c;
}
void ntt(int n,int *a,int op){
	static int pw[N],rev[N];pw[0]=1;
	for(int i=0;i<n;i++)rev[i]=(rev[i>>1]>>1)|(i&1?n>>1:0);
	for(int i=0;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int i=1;i<n;i<<=1){
		int g=qpow(3,mod/i/2);
		for(int j=1;j<i;j++)pw[j]=mul(pw[j-1],g);
		for(int j=0;j<n;j+=i<<1)
			for(int k=0;k<i;k++){
				int x=a[j+k],y=mul(a[i+j+k],pw[k]);
				a[j+k]=add(x,y),a[i+j+k]=add(x,mod-y);
			}
	}
	if(op==-1){
		int inv=qpow(n,mod-2);
		for(int i=0;i<n;i++)a[i]=mul(a[i],inv);
		reverse(a+1,a+n);
	}
}
vector<int> Mul(vector<int> a,vector<int> b){
	static int A[N],B[N],n;
	for(n=1;n<=a.size()+b.size()-2;n<<=1);
	for(int i=0;i<n;i++)A[i]=B[i]=0;
	for(int i=0;i<a.size();i++)A[i]=a[i];
	for(int i=0;i<b.size();i++)B[i]=b[i];
	ntt(n,A,1),ntt(n,B,1);
	for(int i=0;i<n;i++)A[i]=mul(A[i],B[i]);
	ntt(n,A,-1);
	vector<int> c(a.size()+b.size()-1);
	for(int i=0;i<c.size();i++)c[i]=A[i];
	return c;
}
int n,d[N],cnt[N];
int fac[N],ifac[N];
vector<int> init(int d,int k){
	vector<int> v(k+1);
	for(int i=0,pw=1;i<=k;i++,pw=mul(pw,d))
		v[i]=mul(pw,mul(fac[k],mul(ifac[i],ifac[k-i])));
	return v;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",d+i),cnt[d[i]]++;
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=mul(fac[i-1],i);
	ifac[n]=qpow(fac[n],mod-2);
	for(int i=n;i>=1;i--)ifac[i-1]=mul(ifac[i],i);
	vector<int> res(1,1);
	for(int i=n;i>=1;i--){
		res=Mul(res,init(i,cnt[i]));
	}
	int ans=0;
	for(int i=0,pw=qpow(n,mod-2);i<res.size();i++,pw=mul(pw,n)){
		ans=add(ans,mul(res[i],mul(pw,fac[n-i])));
	}
	ans=mul(ans,qpow(n,mod-2));
	for(int i=1;i<=n;i++)ans=mul(ans,ifac[d[i]]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Leasier (赞：2)

Update on 2023.2.6 & 2.8：感谢 @[Iridescent41](https://www.luogu.com.cn/user/324362)。

考虑把原问题转化为一个**有根且边点均带标号的问题**。

设原问题答案为 $A$，新问题答案为 $B$，则 $B = An \displaystyle\prod_{i = 1}^n d_i!$。

现在我们来尝试解决新问题。进行一棵树的构造，如下：

- 选定一个点集 $S$，使得 $\forall u \in S$，$u$ 有一条边沿根方向。
- 确定每条根向边的终点。
- 根据 $d_i$ 要求从叶子到根确定剩下边的终点。

假如我们已知点集 $S$，则选择沿根方向的边的编号的方案数为 $\displaystyle\prod_{i \in S} d_i$。

接下来考虑确定根向边终点的方案数。不难发现在前两步结束后只有 $S$ 中的点被选择了父亲，则这玩意的方案数与一棵 $n$ 个点的森林且只有某确定的 $|S|$ 个点拥有父亲的方案数相同。

考虑重复以下操作 $|S|$ 次以构造一棵 $n$ 个点的有向森林：

- 选择两个不在同一连通块内的点 $u, v$ 且 $v$ 没有父亲。
- 令 $v$ 的父亲为 $u$。

这样构造的方案数为 $\displaystyle\prod_{i = 1}^{|S|} n(n - i) = \frac{n^{|S|} (n - 1)!}{(n - |S| - 1)!}$，忽略选边顺序后即为 $n^{|S|} C_{n - 1}^{|S|}$。但是因为这 $|S|$ 个点本来是固定的，实际上还要除以 $C_n^{|S|}$，得到 $n^{|S| - 1}$。

接下来再考虑确定剩下边的方向。一共有 $n - |S|$ 个这样的点，则方案数为 $(n - |S|)!$。

乘起来即可得到 $n^{|S| - 1} (n - |S|)! \displaystyle\prod_{i \in S} d_i$。

我们用多项式 $f(x) = \displaystyle\prod_{i = 1}^n (1 + d_i x)$ 来描述子集积之和，则答案为 $\displaystyle\sum_{i = 0}^{n - 1} n^{i - 1} (n - i)! [x^i] f(x)$。

分治 NTT 即可。时间复杂度为 $O(n \log^2 n)$。

代码：
```cpp
#include <iostream>
#include <vector>
#include <atcoder/convolution>

using namespace std;
using namespace atcoder;

typedef modint998244353 mint;
int d[200007];
mint fac[200007];
vector<mint> v;

inline void init(int n){
	fac[0] = 1;
	for (register int i = 1; i <= n; i++){
		fac[i] = fac[i - 1] * i;
	}
}

vector<mint> solve(int l, int r){
	if (l == r) return vector<mint>{1, d[l]};
	int mid = (l + r) >> 1;
	return convolution(solve(l, mid), solve(mid + 1, r));
}

int main(){
	int n;
	mint prod = 1, ans;
	cin >> n;
	init(n);
	ans = fac[n - 1];
	for (register int i = 1; i <= n; i++){
		cin >> d[i];
	}
	v = solve(1, n);
	for (register int i = 1; i < n; i++){
		ans += prod * fac[n - i] * v[i];
		prod *= n;
	}
	ans /= n;
	for (register int i = 1; i <= n; i++){
		ans /= fac[d[i]];
	}
	cout << ans.val();
	return 0;
}
```

---

## 作者：Coward2008 (赞：1)

首先考虑钦定一个根，使得树的形态更清晰。

于是我们枚举一个点集 $S$，使得 $S$ 内的点和父亲间的边是 x->fa。

先考虑连 x->fa 的边的方案数，再考虑此基础上连 fa->x 的方案数。

第一部分的方案只和 $|S|$ 大小相关，所以我们考虑 $n$ 个点，连了 $|S|$ 条 x->fa 边的森林一共有多少个，再除以 $\tbinom{n}{|S|}$ 。

考虑构造超级点 $0$ ，使森林内每棵树的根连向 $0$ ，则变成 $n+1$ 个点，$0$ 的度数为 $n-|S|$ 的方案数。 

使用 prufer 序列处理这个问题，易得 $\tbinom{n-1}{n-|S|-1}n^{|S|}$ ，除掉 $\tbinom{n}{|S|}$ 得到 $n^{|S|-1}*(n-|S|)$ 。

第二部分，考虑依次连每一条边，你发现边是无序的，影响了计数。所以我们给边打上标号，一开始连 x->fa 的时候要乘上 $\prod\limits_{i\in S} d_i$ 。

然后这剩下 $n-|S|-1$ 条边，它们的方案数与起点无关，并且每连一条边，终点的个数就会 -1 。所以这里方案就是 $(n-|S|-1)!$ 。

所以一个集合 $|S|$ 的答案就是 $\frac{1}{n\prod d_i!}\prod\limits_{i\in S} d_i\ (n-|S|-1)!(n-|S|)n^{|S|-1}=\frac{1}{n\prod d_i!}\prod\limits_{i\in S} d_i\ (n-|S|)!n^{|S|-1}$ 。

发现除了 $\prod\limits_{i\in S}d_i$ ，其他项只与 $|S|$ 有关，于是利用分治 NTT 求出 $\prod (1+d_ix)$ 即可方便计算答案。

---

