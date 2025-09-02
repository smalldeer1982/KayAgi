# Symmetric and Transitive

## 题目描述

Little Johnny has recently learned about set theory. Now he is studying binary relations. You've probably heard the term "equivalence relation". These relations are very important in many areas of mathematics. For example, the equality of the two numbers is an equivalence relation.

A set $ ρ $ of pairs $ (a,b) $ of elements of some set $ A $ is called a binary relation on set $ A $ . For two elements $ a $ and $ b $ of the set $ A $ we say that they are in relation $ ρ $ , if pair ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/16a5bd0364ee1c2418519b45f507a656a36915fe.png), in this case we use a notation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/ac1017904cc72900e599536210489e5806c7e715.png).

Binary relation is equivalence relation, if:

1. It is reflexive (for any $ a $ it is true that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/91e4d3abbed748c18e812b3137edc3c1a1f0e778.png));
2. It is symmetric (for any $ a $ , $ b $ it is true that if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/ac1017904cc72900e599536210489e5806c7e715.png), then ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/b6f938add219491e6c1f894f8e7099b7242c4c5e.png));
3. It is transitive (if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/ac1017904cc72900e599536210489e5806c7e715.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/5fd1e1be872bf420a3d068d47d57fec967b2dcb8.png), than ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/78faa71961e282211efc6cc897539a239b2fbcca.png)).

Little Johnny is not completely a fool and he noticed that the first condition is not necessary! Here is his "proof":

Take any two elements, $ a $ and $ b $ . If ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/ac1017904cc72900e599536210489e5806c7e715.png), then ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/b6f938add219491e6c1f894f8e7099b7242c4c5e.png) (according to property (2)), which means ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/91e4d3abbed748c18e812b3137edc3c1a1f0e778.png) (according to property (3)).

It's very simple, isn't it? However, you noticed that Johnny's "proof" is wrong, and decided to show him a lot of examples that prove him wrong.

Here's your task: count the number of binary relations over a set of size $ n $ such that they are symmetric, transitive, but not an equivalence relations (i.e. they are not reflexive).

Since their number may be very large (not $ 0 $ , according to Little Johnny), print the remainder of integer division of this number by $ 10^{9}+7 $ .

## 说明/提示

If $ n=1 $ there is only one such relation — an empty one, i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/519c456ed02b51bdfd523585bf0281cdbd8600fd.png). In other words, for a single element $ x $ of set $ A $ the following is hold: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/3abfc110a65cf385b201a329b8a306e1eb23baef.png).

If $ n=2 $ there are three such relations. Let's assume that set $ A $ consists of two elements, $ x $ and $ y $ . Then the valid relations are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/519c456ed02b51bdfd523585bf0281cdbd8600fd.png), $ ρ={(x,x)} $ , $ ρ={(y,y)} $ . It is easy to see that the three listed binary relations are symmetric and transitive relations, but they are not equivalence relations.

## 样例 #1

### 输入

```
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3
```

### 输出

```
10
```

# 题解

## 作者：Rubidium_Chloride (赞：4)

大概理个题意（）

然后由 $(2)$ $\rho(a,b)=\rho(b,a)=1\to \rho(a,a)=\rho(b,b)=1$。

所以这种关系中的每一条边都可以被认为是一条无向边。

所以一定有孤立点。

这里定义孤立点为 **没有连边（包括自环）** 的点。

传递性使得这个图中的每一个连通块都是一个完全图。

设所求答案为 $P_i$，假设存在 $i$ 个孤立点。

选择 $i$ 个孤立点有 $\dbinom{n}{i}$ 种方法，剩下的就随便连边了，分成若干个极大完全子图（？）然后内部两两连边（含自环）。这部分的贡献是 $B_{n-i}$。

（此处 $B_k$ 为 $\text{Bell Number}$。）

所以 $P_i=\sum\limits_{i=1}^{n} \dbinom{n}{i}B_{n-i}=\sum\limits_{n-i=0}^{n-i=n-1} \dbinom{n}{n-i}B_{n-i}=\sum\limits_{i=0}^{n-1} \dbinom{n}{i}B_i$。

然后根据 $\text{Bell Number}$ 的递推关系，可得 $P_i=B_{n+1}-B_n$。

然后如果你想要做的话理论可以做到 $\mathcal{O}(n\log n)$，但我看到模数以后没兴趣这么干了。

直接 $\text{Bell}$ 三角形递推好了。

复杂度 $\mathcal{O}(n^2)$。

---

## 作者：__Walnuts__ (赞：3)

不会多项式的可以来看看！

将二元关系看成边，则最终形成的图一定能被分成几部分，每部分要么只包含一个点（没有连边），要么任意两点都连有边（含自环）。

枚举有几个孤立点，剩下点的分配就相当于集合划分。即

$$ans=\sum\limits_{i=1}^n\binom{n}{i}B_{n-i}=\sum\limits_{i=0}^{n}\binom{n}{i}B_i-B_i=B_{i+1}-B_i$$

用贝尔三角形递推就可以 $O(n^2)$。

不过这些都是老生常谈了。

现在的问题是不会多项式，还想做到 $O(n\log n)$，怎么办？

因为我们实质上只要求单个贝尔数，可以直接从公式入手：

$$B_n=\sum\limits_{k=0}^n\begin{Bmatrix}n\\k\end{Bmatrix}=\sum\limits_{k=0}^n\sum\limits_{i=0}^k\frac{(-1)^{k-i}i^n}{(k-i)!i!}$$

交换枚举顺序，每个 $i$ 都只对满足 $k\geq i$ 的 $k$ 有贡献。

$$B_n=\sum\limits_{i=0}^n\frac{i^n}{i!}\sum\limits_{k=i}^n\frac{(-1)^{k-i}}{(k-i)!}=\sum\limits_{i=0}^n\frac{i^n}{i!}\sum\limits_{k=0}^{n-i}\frac{(-1)^k}{k!}$$

记 $S_n=\sum\limits_{k=0}^{n}\frac{(-1)^k}{k!}$，则

$$B_n=\sum\limits_{i=0}^n\frac{i^n}{i!}S_{n-i}$$

$i!$ 的逆元和前缀和 $S_n$ 都可以 $O(n)$ 预处理，只有 $i^n$ 的快速幂是 $O(n\log n)$ 的，所以总体是 $O(n\log n)$ 的。

是这样的吗？

不。

$f(x)=x^n$ 是积性函数，也就是说可以用欧拉筛预处理 $i^n$，只计算质数处的快速幂，复杂度 $O(n+\frac n {\ln n} \log n)=O(n)$。

所以不使用多项式，我们最终得到了一个 $O(n)$ 的算法。

注：为了简化计算代码里实际用的是上面柿子的一个变形：

$$ans=\frac{(n+1)^{n+1}}{(n+1)!}+\sum\limits_{i=1}^n\frac{i^n}{i!}((i-1)S_{n-i+1}+\frac{(-1)^{n-i+1}}{(n-i+1)!})$$


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=4010,mod=1e9+7;
int n,a[N],p[N],nth[N],inv[N],top;
bool vis[N];

int fpow(int x,int n){
    long long ans=1,step=x;
    while(n){
        if(n&1)ans=ans*step%mod;
        step=step*step%mod;
        n>>=1;
    }
    return ans;
}

int main(){
    cin>>n;
    long long fac=1,S=0;
    for(int i=2;i<=n+1;++i)
        fac=fac*i%mod;
    inv[n+1]=fpow(fac,mod-2);
    
    //预处理阶乘逆元
    for(int i=n;i;--i)
        inv[i]=1ll*inv[i+1]*(i+1)%mod;
        
    //计算(-1)^k/(k!)
    a[0]=inv[0]=nth[0]=nth[1]=1;
    for(int i=1;i<=n+1;i+=2)
        a[i]=mod-inv[i],
        a[i+1]=inv[i+1];
     
    //求S_n
    for(int i=0;i<=n;++i)
    	S+=a[i];
    S%=mod;
    
    //求i^n
    for(int i=2;i<=n+1;++i){
        if(!vis[i])
            p[++top]=i,
            nth[i]=fpow(i,n);
        for(int j=1;j<=top;++j){
            int t=p[j]*i;
            if(t>n+1)break;
            vis[t]=1;
            nth[t]=1ll*nth[i]*nth[p[j]]%mod;
            if(i%p[j]==0)break;
        }
    }
    
    long long ans=1ll*nth[n+1]*(n+1)%mod*inv[n+1]%mod;
    for(int i=1;i<=n;++i)
    	ans+=1ll*nth[i]*inv[i]%mod*((i-1)*S%mod+a[n-i+1])%mod,
    	S=(S+mod-a[n-i+1])%mod;
    
    cout<<(ans%mod+mod)%mod<<endl;
}

```


---

## 作者：moongazer (赞：3)

# 题解 CF568B 【Symmetric and Transitive】

[$\mathfrak{View\space it\space on\space my\space Blog}$](https://blog.seniorious.cc/2020/CF-568B/)

## 题意

计数$n$个元素的满足对称性、传递性，但不满足自反性的二元关系种数，$n\le4000$

## 思路

发现若$a\sim b$则有$b\sim a,a\sim a,b\sim b$，所以一定存在不和其他所有元素相连的，不妨设有$n-k$个单独点，剩下的$k$个点可以分为几个集合（注意大小为$1$的集合不等于单独点，大小为$1$的集合有自身连自身），此时对答案的贡献为$\binom{n}{k}B_{k}$（$n$个里选$k$个分成若干集合，其他都是单独的），其中$B_i$为第$i$个贝尔数，等于$\sum_{j=1}^i\left\{\begin{matrix}i\\j\end{matrix}\right\}$，于是答案就为$\sum_{k=0}^{n-1}\binom{n}{k}B_k$

由于$n$很小，$\operatorname{O}(n^2)$搞出第二类 Stirling 数即可

## 代码

```cpp
int fac[N], ifac[N];
int S[N][N];
int Bell[N];
int n;

int main () {
  read(n);
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * 1ll * i % Mod;
  }
  ifac[n] = pow(fac[n], Mod - 2, Mod);
  for (int i = n - 1; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * 1ll * (i + 1) % Mod;
  }
  S[0][0] = 1;
  Bell[0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= i; ++j) {
      S[i][j] = (S[i - 1][j - 1] + S[i - 1][j] * 1ll * j % Mod) % Mod;
      Bell[i] = (Bell[i] + S[i][j]) % Mod;
    }
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    ans = (ans + C(n, i) * 1ll * Bell[i] % Mod) % Mod;
  }
  write(ans), EL;
  return 0;
}
```

---

## 作者：dsjkafdsaf (赞：3)

# [My_blog](https://www.cnblogs.com/dsjkafdsaf/)
## 题目描述

要求找出 $n$ 个元素中满足对称性，传递性，但不满足自反性的所有二元关系种数。

有一个集合，它的元素是二元关系$（x，y）$，其中$x，y$的范围是$[1,n]$。这个集合满足如下性质：
1.如果这个集合里有$（x，y）$，那么一定有$（y，x）$。
2.如果这个集合里同时有$（x，y）$和$（y，z）$，那么一定有$（x，z）$。注意，在这条性质里，$x，y，z$可以相等
3.这个集合不同时包含$（1，1），（2，2），……（n，n）$。
问这个集合有多少种组成方式。
（当$n=3$时，有$10$种方式，为∅, {(1,1)} , {(2,2)} , {(3,3)} , {(1,1),(2,2)} , {(1,1),(3,3)} , {(2,2),(3,3)} , {(1,2),(2,1),(1,1),(2,2)} , {(1,3),(3,1),(1,1),(3,3)} , {(2,3),(3,2),(2,2),(3,3)}）。

## Input

输入 $n$ ，表示有 $n$ 个元素, $(1<=n<=4000)$.

## Output

输出满足对称性，传递性，但不满足自反性的所有二元关系种数。

**注意，答案可能很大，需要模 1e9+7，即1000000007**

## Sample Input

```
1
2
3
```
## Sample Output
```
1
3
10
```
首先，我们发现，若一个集合中有二元关系$(x,y)$，则就一定有$(y,x)$，有$(x,x)$和$(y,y)$。

也就是说，一个集合中所有的元素必定会形成$(1,1)$,$(2,2)$......这样的关系。

而题目中要求集合不能同时包含$（1，1），（2，2），……（n，n）$，实际上就是说集合中不能包含$1-n$所有的元素。

而这个我们可以利用贝尔数组解决。

定义：$dp[i][j]$表示前$i$个数分成$j$个集合的方案数。

考虑转移:对于第$i$个元素，我们有两种决策：

1.我们将其放入前面已经有的$j$个集合中。

2.我们们新建一个集合，将其放入。

所以我们有：$dp[i][j]=dp[i-1][j-1]+j*dp[i-1][j]$。

而我们要求的答案是$n$个元素不能在同一个集合的方案数。

对于我们要求的答案，我们可以转换成，在$n$个数中选了$i$个数，这$i$个数分割成若干个集合，而剩下的$n-i$个数独立成为一个集合的方案数，$(i!=n)$。

则答案就为$\sum_{i=1}^{n-1}C(n,i)*bell(i)$。

## 代码如下
```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define reg register
#define Raed Read
#define debug(x) cerr<<#x<<" = "<<x<<endl;
#define rep(a,b,c) for(reg int a=(b),a##_end_=(c); a<=a##_end_; ++a)
#define ret(a,b,c) for(reg int a=(b),a##_end_=(c); a<a##_end_; ++a)
#define drep(a,b,c) for(reg int a=(b),a##_end_=(c); a>=a##_end_; --a)
#define erep(i,G,x) for(int i=(G).Head[x]; i; i=(G).Nxt[i])

inline int Read(void) {
	int res=0,f=1;
	char c;
	while(c=getchar(),c<48||c>57)if(c=='-')f=0;
	do res=(res<<3)+(res<<1)+(c^48);
	while(c=getchar(),c>=48&&c<=57);
	return f?res:-res;
}

template<class T>inline bool Min(T &a,T const&b) {
	return a>b ?a=b,1:0;
}
template<class T>inline bool Max(T &a,T const&b) {
	return a<b?a=b,1:0;
}

const int N=4e3+5,M=3e5+5,mod=1e9+7;

bool MOP1;

int dp[N][N],F[N],Fac[N];

inline int Pow(int x) {
	int res=1,y=mod-2;
	while(y) {
		if(y&1)res=(res*x)%mod;
		x=(x*x)%mod,y>>=1;
	}
	return res;
}

inline int C(int x,int y) {
	if(!x)return 1;
	return (Fac[y]*Pow((Fac[x]*Fac[y-x])%mod))%mod;
}

bool MOP2;

inline void _main(void) {
	dp[0][0]=1,F[0]=1,Fac[0]=1;
	rep(i,1,4000)Fac[i]=(Fac[i-1]*i)%mod;
	rep(i,1,4000)rep(j,1,4000) {
		dp[i][j]=(dp[i-1][j-1]+j*dp[i-1][j])%mod;
		F[i]=(F[i]+dp[i][j])%mod;
	}
	int n;
	while(~scanf("%lld",&n)) {
		int Ans=0;
		ret(i,0,n)Ans=(Ans+(C(i,n)*F[i])%mod)%mod;
		printf("%lld\n",Ans);
	}
}

signed main() {
	_main();
	return 0;
}
```

---

## 作者：sounds_666 (赞：3)

这不就是一个标准的dp题吗？话不多说上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1000000007;//用来取余
int dp[4200][4200];
int main(){
    int n;
    scanf("%d",&n);//输入
    dp[0][0]=1;//第一个点初始化
    for(int i=1;i<=n+1;i++){//记得到n+1
        dp[i][0]=dp[i-1][i-1];//初始化
        for(int j=1;j<=i;j++){
            dp[i][j]=(dp[i][j-1]+dp[i-1][j-1])%=mod;//dp公式
        }
    }
    printf("%d\n",(dp[n+1][0]-dp[n][0]+=mod)%mod);
    return 0;
}
```


---

## 作者：Wangzehao2009 (赞：1)

考虑对于一个二元组 $(a,b)$，和符合题意的二元关系 $R$，其满足传递性和对称性，必然会满足自反性，证明如下

$$\because \text{根据对称性}，R(a,b)\Leftrightarrow R(b,a)$$
$$\therefore \text{根据传递性}，R(a,a),R(b,b)$$

所以二元关系 $R$ 对于 $a,b$ 同时满足对称性、传递性和自反性。不符合题意。

因此，集合 $S$ 满足题意当且仅当 
$$\exists a \in S, !R(a,a) \Leftrightarrow \exists a \in S,  \forall b \in S, !R(a,b)$$

考虑将元素作为点，以 $R$ 这样的二元关系为边建图。所以存在孤立点（没有连边（包括自环）的点）的图的点集是满足题意的集合。

所以将问题转化为：**求存在孤立点的点集大小为 $n$ 的图种数**。

## 解法 1

设 $f_{i,j}$ 表示 $i$ 个点，有 $j$ 个连通块（非孤立点）的方案数。

不难得到转移

$$f_{i,j}=j \cdot f_{i-1,j}+f_{i-1,j-1}$$

答案

$$ans=\sum_{i=0}^{n-1} \binom{n}{i} \sum_{j=0}^{i} f_{i,j}$$

复杂度 $O(n^2)$。

## 解法 2

**贝尔数** 概念引入（详见 [oi-wiki 贝尔数](https://oi-wiki.org/math/combinatorics/bell/)）：

贝尔数 $B_n$ 是基数为 $n$ 的集合的划分⽅法的数目。集合 $S$ 的⼀个划分是定义为 $S$ 的两两不相交的非空子集的族。

贝尔数适用于如下递推公式

$$B_{n+1}=\sum_{i=0}^{n} \binom{n}{i}B_i$$

枚举有几个孤立点，剩下的连通块的点的分配相当于集合的划分。即：

$$ans=\sum_{i=1}^{n}\binom{n}{i}B_{n-i}=\sum_{i=0}^{n}B_i-B_n=B_{i+1}-B_{i}$$

用贝尔三角形（见 oi-wiki）递推可以得到 $O(n^2)$ 的复杂度。

## 优化 1

**斯特林数** 概念引入（详见 [oi-wiki 斯特林数](https://oi-wiki.org/math/combinatorics/stirling/)）

每个贝尔数都是相应的第⼆类斯特林数的和。因为第⼆类斯特林数是把基数为 $n$ 的集合划分为正好 $i$ 个非空集的方法数目。即

$$B_n=\sum_{k=0}^{n}{n\brace k}$$

现在考虑 ${n\brace k}$ 的通项公式如何推导。

设将 $n$ 个两两不同的元素，划分到 $i$ 个两两不同的集合（允许空集）的方案数为 $G_i$，将 $n$ 个两两不同的元素，划分到 $i$ 个两两不同的非空集合（不允许空集）的方案数为 $F_i$。

立即得到

$$G_i=i^n$$
$$G_i=\sum_{j=0}^{i} \binom{i}{j}F_j$$

二项式反演得到

$$F_i=\sum_{j=0}^{i} (-1)^{i-j}\binom{i}{j}G_j \\ =\sum_{j=0}^{i} (-1)^{i-j}\binom{i}{j}j^n \\ =\sum_{j=0}^{i} \frac{(-1)^{i-j}i!j^n}{(i-j)!j!}$$

考虑 $F_i$ 与 ${n\brace i}$ 的关系。第二类斯特林数要求集合之间互不区分，因此 $F_i$ 正好就是 ${n\brace i}$ 的 $i!$ 倍。于是

$$\therefore {n\brace m}=\frac{F_m}{m!}=\sum_{i=0}^{m} \frac{(-1)^{m-i}i^n}{(m-i)!i!}$$

推导完成。

现在我们回到贝尔数。

$$B_n=\sum_{k=0}^{n}{n\brace k}=\sum_{k=0}^{n}\sum_{i=0}^{k} \frac{(-1)^{k-i}i^n}{(k-i)!i!}$$

交换枚举顺序，每个 $i$ 都只对 $k \geq i$ 的 $k$ 有贡献。

$$B_n=\sum_{i=0}^{n} \frac{i^n}{i!}\sum_{k=i}^{n}\frac{(-1)^{k-i}}{(k-i)!}=\sum_{i=0}^{n} \frac{i^n}{i!}\sum_{k=0}^{n-i}\frac{(-1)^{k}}{k!}$$

令

$$f_i=\frac{i^n}{i!}, g_i=\sum_{j=0}^{i} \frac{(-1)^j}{j!}$$

$$h=f \times g$$

$$\therefore B_n=h_n$$

卷积即可得到 $O(n \log{n})$ 的复杂度。

## 优化 2

我们发现上述算法的瓶颈在于卷积而且无法继续优化，所以我们考虑回到这个式子。

$$B_n=\sum_{i=0}^{n} \frac{i^n}{i!}\sum_{k=0}^{n-i}\frac{(-1)^{k}}{k!}$$

记
$$S_n=\sum_{k=0}^{n}\frac{(-1)^k}{k!}$$

$$\therefore B_n=\sum_{i=0}^{n}\frac{i^n}{i!}S_{n-i}$$

$i!$ 的逆元和前缀和 $S_n$ 都可以 $O(n)$ 预处理，只有 $i^n$ 的快速幂是 $O(n \log{n})$ 的，所以可以得到 $O(n \log{n} )$ 的复杂度。

## 优化 3

我们发现上述算法的瓶颈在于计算 $i^n$，我们考虑继续优化。

显然，$f(x)=x^n$ 是积性函数，考虑用线性筛预处理 $i^n$，只计算质数处的快速幂。

复杂度
$$O(n+\frac{n}{\ln{n}} \cdot \log{n})=O(n)$$

---

## 作者：Yansuan_HCl (赞：1)

大家好，我喜欢暴力 dp 并且不会 Bell 数，因此我以 $O(n^2 \log n)$ 的复杂度通过了本题。

可以设 $f[i][l]$ 表示用 $i$ 个点组成一些完全子图，最大完全子图大小为 $l$ 的方案数，答案即为 $\sum_{i=1}^{n-1}\binom{n}{i}\sum_{l=1}^{i}f[i][l]$。

同一个完全子图中，各个点的地位平等（即不区分顺序）；同个大小的完全子图可以互换，也不区分顺序。因此，枚举最大完全图的大小，再枚举最大完全图的数量，即可进行转移。

```cpp
// 适当运用内联、手动内联卡常
#pragma GCC optimize("Ofast")
#include <cstdio>
#include <algorithm>
#define ms(x, v) memset(x, v, sizeof(x))
#define il __attribute__((always_inline))
#define U(i,l,r) for(int i(l),END##i(r);i<=END##i;++i)
#define D(i,r,l) for(int i(r),END##i(l);i>=END##i;--i)
using namespace std;

typedef long long ll;

const ll P = 1000000007; const int N = 4005;
ll fac[N], ifac[N];
ll qpow(ll x, ll t) { ll v = 1; while (t) { if (t & 1) (v *= x) %= P; (x *= x) %= P; t >>= 1; } return v; }
ll pwf[N][N];

int n;
ll f[N][N];
int main() {
    fac[0] = ifac[0] = 1;
    U (i, 1, 4000) fac[i] = fac[i - 1] * i % P;
    ifac[4000] = qpow(fac[4000], P - 2);
    D (i, 3999, 1) ifac[i] = ifac[i + 1] * (i + 1) % P;

    {
        int c = getchar();
        while (c != '\n' && c != EOF) {
            n = n * 10 + (c ^ 48);
            c = getchar();
        }
    }

    ll ans = 1;
    f[0][0] = 1;
    U (i, 1, n) {
        pwf[i][0] = 1;
        for (int k = 1; k * i <= n; ++k)
            pwf[i][k] = pwf[i][k - 1] * ifac[i] % P;
    }
    U (i, 1, n - 1) {
        U (l, 1, i) {
            for (int k = 1; k * l <= i; ++k) 
                f[i][l] += f[i - k * l][min(l - 1, i - k * l)] * fac[i] % P * ifac[i - k * l] % P * pwf[l][k] % P * ifac[k] % P;
            (f[i][l] += f[i][l - 1]) %= P;
        }
        (ans += fac[n] * ifac[i] % P * ifac[n - i] % P * f[i][i]) %= P;
    }
    printf("%lld", ans);
}
```

---

## 作者：Spasmodic (赞：1)

考虑 $f(a,b)=1$ 即有 $f(b,a)=1$ 得 $f(a,a)=f(b,b)=1$，那么如果视为一张无向图（忽略自环）的话，图中有孤立点。

先考虑满足自反性的情况。考虑图的每一个极大连通子集，根据传递性一定是一个团。

那么考虑计数这样的图的数量，很明显就是贝尔数，其生成函数是 $\exp (e^x-1)$，容易在 $O(n\log n)$ 时间内求出。

再考虑不满足自反性，那么我们枚举孤立点的数量，答案就是
$$
\sum_{k<n}\dbinom{n}{k}B_k=\sum_{k}\dbinom{n}{k}B_k-B_n=B_{n+1}-B_n
$$
总复杂度 $O(n\log n)$。

另外顺便一提，如果你想只做到 $O(n^2)$ 还不想预处理组合数，那么你可以考虑[贝尔三角形](https://oi-wiki.org/math/combinatorics/bell/#_2)，这样在合数情况下也能做。

---

## 作者：UnyieldingTrilobite (赞：1)

我觉得生成函数+poly不优美=.=

---

首先我们观察这个所谓“关系”的形式，看到对称性和传递性，我们立马可以想到这玩意等价于把 $n$ 个数（**选取一部分**）划分成若干集合，然后这个所谓“关系”就等价于两个数在同一个集合里……其实挺憨的。

那个不具备自反性相当于是说，不能所有数都被选取出来划分掉了，必须剩一部分（称之为“剩余集合”）。我们不难想到，这剩的一部分和其他集合区别不大，但隐约（这里我说不清楚，但可以感知到把它当成一个正常集合是做不了的，比如说把它和另外一个集合交换一下得到的最终方案不同）还是需要考虑的。其他的集合就完全一致了。

接下来显然就可以动态规划了。

我们定义 $cnt_{i,j}$ 表示对于 $i$ 个数，有**至多** $j$ 个属于“剩余集合”。显然，只需要考虑 $j\le i$ 的情况。答案就是 $cnt_{n,n}-cnt_{n,0}$。

然后开始考虑转移。

对于 $j>0$，把贡献分为两类：属于“剩余集合”的数恰好 $j$ 个，和至多 $j-1$ 个。后者就是 $cnt_{i,j-1}$。前者的话，给 $i$ 个数中标号（对就是题目里那个标号，但具体是多少实际上没有影响）最小的属于“剩余集合”的数给提出来扔掉，会发现它的贡献就是 $cnt_{i-1,j-1}$。这个一一对应是显然的，因为当知道 $i$ 个数的标号和扔掉之后 $i-1$ 个数的标号后能唯一确定被扔掉的数是几。

所以有方程 $cnt_{i,j}=cnt_{i,j-1}+cnt_{i-1,j-1}$。

对于 $j=0$，如果 $i=0$ 那么答案就是 $1$，很显然。如果 $i\ge1$，我们会发现上面枚举出一个“剩余集合”中的数那一套就失效了，必须另辟蹊径。我们不妨“枚举”最后一个数所在集合（实际上不用真的“枚举”），从这个集合中把最后一个数删掉。我们此时惊奇地发现，由于最后需要多加入一个数，**此时这个集合的地位已经和其他集合不对等了**。更棒的是，此时**它的地位和“剩余集合”对等了，而真正的“剩余集合”，由于在这 $i$ 个数中大小为 $0$，可以先不用考虑了。换而言之，我们可以直接在 $cnt_{i-1,i-1}$ 的所有方案中，直接把“剩余集合”换掉，把它降成一个普通集合，然后往里面插入最后一个数，“剩余集合”自己却空了。**（整个一一对应可以严谨说明）。

所以有方程 $cnt_{i,j}=cnt_{i-1,i-1}$。

根据以上两个方程和 $cnt_{0,0}=1$ 的初始条件，就可以很方便地动态规划了。代码就不管了，随便写写。

---

以下为番外。

当然，我们会观察到我们对这个动态规划数组可以滚掉一维，然后在转移对这个一维的数组只用干三件事：

1. 循环位移；

2. 累前缀和；

3. 取模。

于是我们就可以写出一个画风极其诡异的玩意……

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)
#define int long long
using namespace std;
constexpr int mod = 1e9 + 7, N = 4009;
int n, cnt[N];
signed main() {
  cin >> n, cnt[0] = 1;
  for (int i = 1, tmp; i <= n; ++i) {
    tmp = cnt[i - 1], memmove(cnt + 1, cnt, i * sizeof(int));
    cnt[0] = tmp, partial_sum(cnt, cnt + i + 1, cnt);
    transform(cnt, cnt + i + 1, cnt, bind2nd(modulus<int>(), mod));
  }
  cout << (cnt[n] - cnt[0] + mod) % mod << endl;
  return 0;
}
```

目前是在谷上最优解第一位，估计很快就要被踢下去了。

以上。


---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF568B)

### 题目大意
问有 $n$ 个元素中满足对称性和传递性但不满足自反性的二元关系集合的个数。

+ 自反性：若 $a$，则有 $(a,a)$。
+ 对称性：若有 $(a,b)$，则有 $(b,a)$。
+ 传递性：若有 $(a,b)$ 且 $(b,c)$，则有 $(a,c)$。

### 解题思路
最困难的是将题目看懂。

其实题目想要表达的就是，不能同时出现 $(1,1),(2,2),(3,3) \cdots(n,n)$，并且有 $(a,b)$ 就有 $(b,a)$，有 $(a,b)$ 和 $(b,c)$ 就有 $(a,c)$。

我们可以证明一个结论，如果在这个集合中出现了数字 $a$，那么肯定能有 $(a,a)$，因为若有 $(a,b)$，那么肯定有 $(b,a)$，而有 $(a,b)$ 和 $(b,a)$，那么就有 $(a,a)$。

所以首先我们可以将这 $n$ 个数分为两类，在集合中出现的和没有在集合中出现的。

我们不妨将 $(a,b)$ 看成一种联通关系，表示 $(a,b)$ 互相联通。

在集合中出现的，我们又可以分为几个集合，每一个集合中对于任意两个数 $a,b$，都“互相联通”，而不在同一个集合中的，肯定“不连通”，非常显然的，对于每一种划分，这样的方案都是唯一的。

所以我们要考虑的就是将这 $n$ 个数划分的方案数，实际上就是 Stirling 数，而从中选出一个特殊的作为不选的集合。

所以最后答案就是：
$$
\sum_{i=1}^{n} i \times S(i,n)
$$
其实这个东西用 Bell 数会更为简单，但本质上差不多。

---

## 作者：liuyifan (赞：0)

## DP
思路:f[i][j]代表i个点，构成j个联通块的方案数

f[i][j]=f[i][j-1]*j(代表与其中一个连通块合并)+f[i-1][j-1]（代表新开一个联通块)

然后答案是Σc[n][i]*f[i][j]

code:
```cpp
// luogu-judger-enable-o2//在luogu评测机中开启O2优化 ,Remotejudge中似乎无效 
#include<bits/stdc++.h>
#define reg register//register卡常 
#define ll long long//long long 
#define y1 liuifan_y1//防关键字 
#define inf 0x3f3f3f3f
#define iinf 0x3f3f3f3f3f3f3f3f//最大值 
#define data liuyifan_data//同上 
#define next liuyifan_next//同上 
#define ture true//防止打错词 
#define flase false//同上 
#define lowbit(x) x&(-x)//树状数组lowbit 
ll f[4005][4005],c[4005][4005],n,ans; 
int main()
{
    scanf("%d",&n); 
    for(reg int i=1;i<=n;i++)c[i][0]=c[i][i]=1;//初始化 
    for(reg int i=2;i<=n;i++)
    for(reg int j=1;j<i;j++)c[i][j]=(c[i-1][j]+c[i-1][j-1])%1000000007;//记得取模 
    f[0][0]=1;//不要写ll f[4005][4005]={1}，会死的很惨,编译器会给你全部初始化一遍 
    for(reg int i=1;i<=n;i++)
    for(reg int j=1;j<=i;j++)f[i][j]=((1LL*f[i-1][j]*j)%1000000007+f[i-1][j-1])%1000000007;//DP,随时记得取模,不然会炸 
    for(reg int i=0;i<n;i++)
    for(reg int j=0;j<=i;j++)ans=(ans+f[i][j]*c[n][i])%1000000007;//求和,计算最终结果，还是要取模 
    printf("%lld\n",ans);  
    return 0;
}
```
部分内容转自[某巨佬的博客](https://www.cnblogs.com/qzqzgfy/)

---

