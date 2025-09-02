# [ABC220E] Distance on Large Perfect Binary Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc220/tasks/abc220_e

$ 2^N-1 $ 頂点からなる木があります。  
 頂点には $ 1 $ から $ 2^N-1 $ の番号がつけられており、各 $ 1\leq\ i\ <\ 2^{N-1} $ について、

- 頂点 $ i $ と頂点 $ 2i $ を結ぶ無向辺
- 頂点 $ i $ と頂点 $ 2i+1 $ を結ぶ無向辺

が存在します。これら以外の辺はありません。

$ 2 $ 頂点間の距離を、その $ 2 $ 頂点を結ぶ単純パスに含まれる辺の個数とします。

頂点の組 $ (i,j) $ であって、距離が $ D $ であるようなものの個数を $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^6 $
- $ 1\ \leq\ D\ \leq\ 2\times\ 10^6 $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

与えられる木は以下の図のようなものです。 !\[図\](https://img.atcoder.jp/ghi/86d098048a50638decb39ed6659d32cf.png) 距離が $ 2 $ であるような頂点の組は $ (1,4),(1,5),(1,6),(1,7),(2,3),(3,2),(4,1),(4,5),(5,1),(5,4),(6,1),(6,7),(7,1),(7,6) $ の $ 14 $ 組存在します。

## 样例 #1

### 输入

```
3 2```

### 输出

```
14```

## 样例 #2

### 输入

```
14142 17320```

### 输出

```
11284501```

# 题解

## 作者：Symbolize (赞：8)

# 思路
首先因为是一棵树，所以节点 $x$ 到根节点的距离即为 $x$ 的深度减去根节点的深度。

所以我们可以将距离为 $D$ 的两点拆分为两部分，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ubfaqizc.png)

所以我们可以通过枚举左边的长度，推导出右边的长度，计算出三个节点在此情况下分别的选择数，最后计算出此情况的总答案，上图已给出方法。

# Code
下面附上 AC 代码！！！
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e7+10;
const int mod=998244353;
using namespace std;
int n,d,ans;
int power(int a,int b)//快速幂
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=(ans*a)%mod;
		b>>=1;
		a=(a*a)%mod;
	}
	return ans;
}
signed main()
{
	cin>>n>>d;//输入
	rep1(i,0,d)//左边长度
	{
		int j=d-i;//右边长度
		if(max(i,j)>=n) continue;//如果左边或右边长度大于总深度则无法取到
		int root=(power(2,n-max(i,j))-1)%mod;//根节点选择数
		int l=power(2,max(0ll,i-1))%mod;//右子树节点选择数
		int r=power(2,max(0ll,j-1))%mod;//左子树节点选择数
		ans=(ans+2*root%mod*l%mod*r%mod)%mod;//当前情况总方案数
	}
	cout<<(ans+mod)%mod<<endl;//输出
	return 0;//收场
}
```

---

## 作者：StayAlone (赞：7)

## 更简要的题意

给定 $n,d$，求一棵节点数量为 $2^n -1$ 的满二叉树上，有多少有序点对 $(x,y)$ 满足它们之间的简单路径上的边的数量为 $d$。

## 思路


显然这条路径可以被分成两部分，一条左边的加上一条右边的，交于一点。

![図](https://img.atcoder.jp/ghi/86d098048a50638decb39ed6659d32cf.png)

如何快速计数？例如样例，有一条 $2\to 1\to 3$ 的路径，那么有一些与这条路径形态完全相同的路径，$4\to 2\to 5$ 和 $6\to 3\to 7$。具体地，设左右两条路径的长度分别为 $x,y$，考虑枚举 $x$，则 $y=d-x$。则在固定两条路径交点的情况下，可以找到 $2^{x-1}\times 2^{y-1}$ 条路径。此外，可以找到 $2^{n-\max\{x,y\}} - 1$ 个可以“容纳”这条路径的交点，即有这么多条形态相同的路径。

upd：无用的事实：$2^{x-1}\times 2^{y-1}=2^{x+y-2}=2^{d-2}$。

这样计数的答案是无序数对，最后答案再乘 $2$ 即可。

结论：$ans = 2\times \sum\limits_{i=0}^d 2^{i-1}\times 2^{d-i-1}\times (2^{n-\max\{i,d-i\}}-1)$。特殊地，对于 $\max\{i,d-i\}\geq n$ 的情况不计数，且在计算时为了方便，令 $2^{-1}=1$。

使用快速幂，时间复杂度 $\mathcal O(d\cdot(\log n+\log t))$，可以加强 $n=10^{18}$。

对于此题，可以先预处理 $2$ 的次幂，时间复杂度为 $\mathcal O(n+d)$。

[AC record](https://www.luogu.com.cn/record/102384699)

```cpp
int n, d; const int mod = 998244353;
ll ans;

il int qpow(int a, int b) {
	if (b < 0) return 1;
	ll ans = 1, base = a;
	while (b) {
		if (b & 1) (ans *= base) %= mod;
		(base *= base) %= mod; b >>= 1;
	} return ans;
}

int main() {
	read(n, d);
	rep1(i, 0, d) {
		int l = i, r = d - i;
		if (max(l, r) >= n) continue;
		(ans += 1ll * qpow(2, l - 1) * qpow(2, r - 1) % mod * (qpow(2, n - max(l, r)) - 1) % mod) %= mod;
	}
	(ans *= 2) %= mod; (ans += mod) %= mod;
	printf("%lld", ans);
	rout;
}
```

---

## 作者：Shunpower (赞：6)

[题目链接](https://www.luogu.com.cn/problem/AT_abc220_e)。

VP 的时候以为是道神奇数学题最后才开。

## 思路

首先一个非常显然的事情是同一层里面的节点都是等价的。也就是说，我们只需要算出来第 $i$ 层一个点的答案乘上 $2^{i-1}$ 即可得到这一层的答案。

那么我们考虑如何得到第 $i$ 层某一个点的答案。

首先我们考虑一下路径终点是其子树内某个点，显然有 $2^d$ 个在同一层的路径终点，也就有 $2^d$ 条路径。注意存在这种路径的前提条件是 $i+d\leqslant n$，否则子树内没有距离足够的点。

然后考虑路径终点是子树外的点，它必然经过一个该点的 $k(k\leqslant i-1)$ 级父亲。考虑分类讨论。

### $d> i-1$

这个时候我可以取满这个点的所有 $x$ 级父亲。

考虑 $x$ 级父亲的贡献，首先我需要消耗 $x$ 长度走到这个位置，然后花 $1$ 步走进另一个子树，剩下的则是在那个子树中随便找一条 $d-x-1$ 长度路径。因此 $x$ 级的父亲贡献即为 $2^{d-x-1}$。

然而并不一定可以找到，所以我们需要算出 $x$ 的下界。我们考虑用式子表示路径的终点在第 $w$ 层。

$$
w=i-x+1+(d-x-1)=i+d-2x
$$

然后又有 $w\leqslant n$，变形一下就可以得到 $x\geqslant \left\lceil\frac{i+d-n}{2}\right\rceil$，然而右边可能是负数，所以和 $1$ 取一下 $\max$ 就可以得到 $x$ 的下界了。

这里 $x$ 显然上界为 $i-1$，因此我们算出上下界（下面用 $lx$ 表示 $x$ 的下界，$rx$ 表示 $x$ 的上界），注意到所有 $x$ 级父亲的贡献和是一个这样的和式：$\sum\limits_{i=d-rx-1}^{d-lx-1}2^i$，显然用等比数列求和乱做即可。

### $d\leqslant i-1$

注意到前 $d-1$ 级父亲都是和上面一模一样的，只需要将 $x$ 的上界再和 $d-1$ 取个 $\min$ 即可。

而第 $d$ 级父亲直接对最终答案贡献 $1$。

于是直接归纳成第一种情况的式子，只是这种情况算出来的答案要加个 $1$。

细节比较多，注意求和的时候下界可能大于上界，下界可能是 $0$。

通过以上方法就可以得到第 $i$ 层某个点对答案的贡献，把这个贡献乘上 $2^{i-1}$ 加到总答案即可。

时间复杂度 $\mathcal O(n(\log d+\log n))$，注意到可以预处理 $2$ 的次幂做到 $\mathcal O(n+d)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define fr1(i,a,b) for(ll i=a;i<=b;i++)
using namespace std;
ll ans;
const ll M=998244353;//注意不要写成1e9+7
ll qpow(ll b,ll p){
	if(!p){
		return 1;
	}
	ll d=qpow(b,p>>1);
	if(p&1){
		return d*d%M*b%M;
	}
	else{
		return d*d%M;
	}
}
ll n,d;
ll sum(ll r){
	if(r<0){
		return 0;
	}
	return ((qpow(2,r+1)-1)%M+M)%M;
}//计算2的0次方到2的r次方之和
int main(){
	cin>>n>>d;
	fr1(i,1,n){
		ll cans=0;
		if(d<=n-i){//子树内有足够的距离
			cans+=qpow(2,d);//子树内路径数
			cans%=M;
		}
		ll kl=max(1ll,(i+d-n+1)/2);//下界
		ll kr=min(i-1,d-1);//上界
		if(kl<=kr){//警惕下界大于上界
			cans+=((sum(d-kl-1)-sum(d-kr-1-1))%M+M)%M;//计算贡献
		}
		if(i-1>=d){//这种情况d级父亲需要特判
			cans++;
			cans%=M;
		}
		cans*=qpow(2,i-1);//乘上点数
		cans%=M;
		ans+=cans;//加总贡献
		ans%=M;
	}
	cout<<ans<<endl;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/102385308)

---

## 作者：XCDRF_ (赞：4)

# AT_abc220_e [ABC220E] Distance on Large Perfect Binary Tree

[原题传送门](https://atcoder.jp/contests/abc220/tasks/abc220_e)

[更好的阅读体验](https://www.luogu.com.cn/article/bsu72kso)

## 题目大意

给定一颗完全二叉树，求有多少组节点间距离为 $D$，答案模 $998244353$。

## 解题思路

直接从一整颗树的角度不好考虑，不妨从根节点入手。

这样我们就可以将一条路径拆成根节点左边的路径和根节点右边的路径。设左边路径长度为 $i$，右边路径长度为 $j$，只需要枚举 $i$，并根据 $i+j=D$ 推出 $j=D-i$ 且保证 $\max(i,j)\le n$。左端点数量就为根节点左子树中深度为 $i$ 的节点数量，右端点数量同理。

但这只是根节点，怎么推广到一整棵二叉树上呢？注意到题目给的是一棵**完全二叉树**，它有一个很好的性质：每一棵子树都与原树的上半部分相同。也就是说，根节点的情况适用于每个节点，只需要 $\max(i,j) > n$ 的路径去除即可。

此时又有了新的问题，如果每个节点都要枚举 $i$ 显然会超时，有没有更快的方法？观察到，每个节点的左端点深度区间是连续的。设该节点深度为 $k$，则左端点实际深度为 $k+i$，右端点实际深度为 $k+D-i$。
需保证 $\begin{cases}
 \max(k+i,k-D+i)\le n\\
 0\le i\le D
\end{cases}$，可求出 $i\in [\max(k+D-n,0),\min(n-k,D)]$。这样只需要对答案数组做一个前缀和即可查询一段区间上的答案。

但枚举每个节点仍会超时。因为同层节点子树结构完全一样，所以一层只需算出一个节点答案，然后直接乘该层节点数量即可。

记得开 long long。

## 参考代码

```cpp
#include<iostream>
#define int long long
using namespace std;
const int N=2e6+5,mod=998244353;
int n,d,res,cnt;
int pw[N],ans[N];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>d;
    pw[0]=1;
    for(int i=1;i<=n;i++) pw[i]=pw[i-1]*2%mod;//预处理2的幂次
    for(int i=0;i<=d;i++){
    	int j=d-i;//无限制情况以根节点为顶点且长度为d的路径数 
    	int l=pw[max(0ll,i-1)];//路径左端点
    	int r=pw[max(0ll,j-1)];//路径右端点 
    	ans[i+1]=(ans[i]+2*l*r%mod)%mod;//前缀和（因为数组下标不能为负且有i=0的情况，所以数组下标整体右移1） 
	}
	for(int i=1;i<=n;i++){
		int l=max(0ll,i+d-n),r=min(d,n-i);//加入本层限制 
		if(l>r) continue;//如果没有满足条件的路径，则跳过 
		res=(ans[min(d,n-i)+1]-ans[max(0ll,i+d-n)]+mod)%mod;//算出本层以一个节点为顶点的路径数 
		cnt=(cnt+pw[i-1]*res%mod)%mod;//路径数*本层节点数 
	}
	cout<<cnt;
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc220/submissions/63409329)

---

## 作者：Kyl_in_2024 (赞：2)

**前言**

~~疑似是楼里码风最可爱代码~~

**思路**

没看数据范围然后想的是枚举每个点然后向上走向下走，直到发现 $2 \le n \le 10^{6}$。。。

发现每层的节点的贡献都一致，决定枚举 $n$，但是这样统计的答案会漏掉一些。怎么办呢？

发现 $1 \le d \le 2 \times 10^{6}$，可以枚举往上多少层再往下，然后如果两边不一致就乘二，因为可以反过来计算。最后前缀和统计节点数就行了。细节看代码。

**代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MOD=998244353;
int a[2000006],b[2000006],s[1000005];
signed main(){
	int n,d,ans=0;
	cin>>n>>d;
	a[0]=b[0]=1;
	for(int i=1;i<=2000000;i++){
		a[i]=(a[i-1]*2)%MOD;
		b[i]=(b[i-1]+a[i])%MOD;
	}
	for(int i=d-(d/2);i<=min(d,n);i++){
		int sum;
		if(i==d) sum=1;
		else sum=a[d-i-1];//扫过的面积
		sum*=(b[n-1]-b[i-1]+MOD)%MOD;//开始的节点数
		sum%=MOD;
		if(i==d/2) ans+=sum;
		else ans+=sum*2;//如果不一致就乘2再统计答案
		ans%=MOD;
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：liluhexuan (赞：1)

首先想到枚举 $i,j$，然后用 LCA 得到两点间距离。如果距离是 $D$，那就将答案加一。但时间复杂度很高，无法过此题。

然后想到枚举 $i$，再统计 $j$。但还是过不了。

发现每一行的所有节点的值都相等。所以可以枚举层数 $i$。

对于第 $i$ 层：

1. 如果这一层的层数加上 $D$ 还没有超出这棵树的范围，那就说明它可以与自己第 $i+k$ 层的所有子孙匹配，想一想就知道，这个点第 $i+k$ 层的所有子孙一共有 $2^x$ 个点，而这一层一共有 $2^{i-1}$ 个点，所以这答案加上 $2^x \times 2^{i-1}$ 对。

2. 我们让它先向上走 $j$ 层，然后再求 $i-j$ 层向下走 $x-j$ 层的结果，式子就是（$j=x$ 的情况比较特殊）:

$$
\sum_{j=1}^{x-1} 2^{i-1} \times 2^{x-j-1} (i-j<1\operatorname{and}i-j+x-j>n)
$$

3. 如果往上跳 $x$ 位，那每个点只有一种可能，这一层有 $2^{i-1}$ 对。

时间复杂度是 $\Theta(nx)$。 优化很大，但还是过不了。

发现第二步可以用前缀和优化成 $\Theta(1)$。其中，$j$ 的最小值是 $\operatorname{max}(1,\lfloor\frac{i+x-n+1}2\rfloor)$，$j$ 的最大值是 $\operatorname{min}(x-1,i-1)$。稍微整理一下，结果就是：

$$
\sum_{i=1}^n \left(2^x \times 2^{i-1}+s_{x-\min(x-1,i-1)-1}-s_{x-\max(1,\lfloor\frac{i+x-n+1} 2\rfloor)-2}+2^{i-1}\right)
$$

其中，$s_i=s_i-1+2^i (s_0=1)$。

代码（别忘了取模）：
```cpp
#include<iostream>
using namespace std;
#define int long long
const int P=998244353,N=2e6+10;
int f[N],s[N];
signed main(){
	int n,x,ans=0;
	cin>>n>>x;
	f[0]=1,s[0]=1;
	for(int i=1;i<=max(x,n);i++)
		f[i]=f[i-1]*2%P;
	for(int i=1;i<=max(x,n);i++)
		s[i]=(s[i-1]+f[i])%P;
	for(int i=1;i<=n;i++){
		int c=f[i-1];
		if(i+x<=n) ans+=c*f[x]%P;
		ans%=P;
		if(i-x>=1) ans+=c;
		ans%=P;
		int l=max(1ll,(i+x-n+1)/2);
		int r=min(x-1,i-1);
		int L=x-r-1,R=x-l-1;
		if(L>R) continue; //这层不合法
		ans+=c*((s[R]-s[L-1])%P+P)%P;
		ans%=P;
	}
	cout<<ans%P;
	return 0;
}

```

---

