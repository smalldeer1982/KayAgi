# Walk

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_r

$ N $ 頂点の単純有向グラフ $ G $ があります。 頂点には $ 1,\ 2,\ \ldots,\ N $ と番号が振られています。

各 $ i,\ j $ ($ 1\ \leq\ i,\ j\ \leq\ N $) について、頂点 $ i $ から $ j $ への有向辺の有無が整数 $ a_{i,\ j} $ によって与えられます。 $ a_{i,\ j}\ =\ 1 $ ならば頂点 $ i $ から $ j $ への有向辺が存在し、$ a_{i,\ j}\ =\ 0 $ ならば存在しません。

$ G $ の長さ $ K $ の有向パスは何通りでしょうか？ $ 10^9\ +\ 7 $ で割った余りを求めてください。 ただし、同じ辺を複数回通るような有向パスも数えるものとします。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 1\ \leq\ N\ \leq\ 50 $
- $ 1\ \leq\ K\ \leq\ 10^{18} $
- $ a_{i,\ j} $ は $ 0 $ または $ 1 $ である。
- $ a_{i,\ i}\ =\ 0 $

### Sample Explanation 1

$ G $ は次図です。 ![](https://img.atcoder.jp/dp/paths\_0\_muffet.png) 長さ $ 2 $ の有向パスは、次の $ 6 $ 通りです。 - $ 1 $ → $ 2 $ → $ 3 $ - $ 1 $ → $ 2 $ → $ 4 $ - $ 2 $ → $ 3 $ → $ 4 $ - $ 2 $ → $ 4 $ → $ 1 $ - $ 3 $ → $ 4 $ → $ 1 $ - $ 4 $ → $ 1 $ → $ 2 $

### Sample Explanation 2

$ G $ は次図です。 ![](https://img.atcoder.jp/dp/paths\_1\_muffet.png) 長さ $ 3 $ の有向パスは、次の $ 3 $ 通りです。 - $ 1 $ → $ 2 $ → $ 1 $ → $ 2 $ - $ 2 $ → $ 1 $ → $ 2 $ → $ 1 $ - $ 2 $ → $ 1 $ → $ 2 $ → $ 3 $

### Sample Explanation 3

$ G $ は次図です。 ![](https://img.atcoder.jp/dp/paths\_2\_muffet.png) 長さ $ 2 $ の有向パスは、次の $ 1 $ 通りです。 - $ 4 $ → $ 5 $ → $ 6 $

### Sample Explanation 5

答えを $ 10^9\ +\ 7 $ で割った余りを出力することを忘れずに。

## 样例 #1

### 输入

```
4 2
0 1 0 0
0 0 1 1
0 0 0 1
1 0 0 0```

### 输出

```
6```

## 样例 #2

### 输入

```
3 3
0 1 0
1 0 1
0 0 0```

### 输出

```
3```

## 样例 #3

### 输入

```
6 2
0 0 0 0 0 0
0 0 1 0 0 0
0 0 0 0 0 0
0 0 0 0 1 0
0 0 0 0 0 1
0 0 0 0 0 0```

### 输出

```
1```

## 样例 #4

### 输入

```
1 1
0```

### 输出

```
0```

## 样例 #5

### 输入

```
10 1000000000000000000
0 0 1 1 0 0 0 1 1 0
0 0 0 0 0 1 1 1 0 0
0 1 0 0 0 1 0 1 0 1
1 1 1 0 1 1 0 1 1 0
0 1 1 1 0 1 0 1 1 1
0 0 0 1 0 0 1 0 1 0
0 0 0 1 1 0 0 1 0 1
1 0 0 0 1 0 1 0 0 0
0 0 0 0 0 1 0 0 0 0
1 0 1 1 1 0 1 1 1 0```

### 输出

```
957538352```

# 题解

## 作者：Legitimity (赞：16)

裸的矩阵加速 Floyd。

我们知道 Floyd 可以传递闭包，并且路径的关系也是二元关系（$i\to k$ 的长度为 $x$，$k\to j$ 的长度为 $y$，那么就可以得到 $i\to j$ 的长度为 $x+y$），那么我们就考虑通过类似 Floyd 的方法来做。

我们设 $f_t[i][j]$ 表示 $i\to j$ 且长度为 $t$ 的路径的条数，根据乘法原理，显然可以得到：

$$f_t[i][j]=\sum^n_{k=1}f_{t-1}[i][k]\times f_1[k][j]$$

其中 $f_1$ 我们发现就是输入的邻接矩阵，而最终答案就是：$\sum^n_{i=1}\sum^n_{j=1}f_k[i][j]$

暴力递推去求，时间复杂度是 $\Theta(kn^3)$，显然无法接受。

那我们开始考虑 Floyd 的本质。

其实很多人在学 Floyd 的时候，我们发现这一坨东西和矩阵乘法长得很像，而现在这题的 Floyd 的递推式就和矩阵乘法一模一样，就相当于:

$$f_t=f_{t-1}\times f_1$$

那么就可以得出 $f_k=f_1^k$。

矩阵乘法是满足结合律的，那么就可以快速幂来求这个东西，时间复杂度是 $\Theta(n^3\log n)$，其中 $n^3$ 是矩阵乘法自带的复杂度。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rg register
#define int long long 
#define inf 0x3f3f3f3f
#define mod 1000000007
inline int read(){
	rg int ret=0,f=0;char ch=getchar();
    while(!isdigit(ch)){if(ch=='n') return inf; ch=getchar();}
    while(isdigit(ch)){ ret=ret*10+ch-48; ch=getchar(); }
    return f?-ret:ret;
}
struct mul{
	int v[105][105],siz;
	mul(){
		memset(v,0,sizeof(v));
	}
}a;
inline mul operator*(const mul& a,const mul& b){
	mul ret; ret.siz=a.siz;
	for(rg int i=1;i<=ret.siz;++i){
		for(rg int k=1;k<=ret.siz;++k){
			for(rg int j=1;j<=ret.siz;++j){
				ret.v[i][j]+=a.v[i][k]*b.v[k][j]%mod;
				ret.v[i][j]%=mod;
			}
		}
	}
	return ret;
} //矩阵乘法。
inline mul ksm(mul base,int p){
	mul ret; ret.siz=base.siz;
	for(rg int i=1;i<=base.siz;++i) ret.v[i][i]=1;
	while(p){
		if(p&1) ret=ret*base;
		base=base*base; p>>=1;
	}
	return ret;
} //快速幂。
int n,k,ans;
signed main(){
	n=read(); k=read(); a.siz=n;
	for(rg int i=1;i<=n;++i){
		for(rg int j=1;j<=n;++j){
			a.v[i][j]=read();
		}
	}
	mul now=ksm(a,k); //求出 f^k
	for(rg int i=1;i<=n;++i){
		for(rg int j=1;j<=n;++j){
			ans+=now.v[i][j]; ans%=mod;
		}
	}
	printf("%lld",ans);
	return 0;
}
//My bones are titanium,but my heart is made of stars
```


---

## 作者：Alexandra (赞：7)

## 题目大意

给定一个有向简单图，求出长度为 $k$ 的路径条数。

## 题目分析
令 $F_{u,v,s}$ 为从点 $u$ 至点 $v$ 长度为 $s$ 的路径条数。   

再枚举中间点 $k$，那么就有递推方程如下：
$$F_{u,v,s}=F_{u,k,s-1} \times F_{k,v,1}$$  
正常情况下，一层层递推求出答案即可。  

可是此题的 $k$ 的范围高达 $10^{18}$，直接递推肯定会时间与空间一起炸。 

观察发现，此方程与矩阵乘法方程完全一样，所以我们可以用**矩阵快速幂**就可以优化时间复杂度了。  

最终的答案即为算出的矩阵中的所有数的和。



## 代码
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 110
#define M 2000100
#define mod 1000000007
struct fun
{
	long long a[N][N];
}r,ans;
long long n,t,s,e,ver[M],Next[M],First[N],edge[M],tot=-1,anss; 
inline long long read()
{
	long long wjl=0,jia=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')jia*=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		wjl=(wjl<<1)+(wjl<<3)+(ch^48);
		ch=getchar();
	}
	return wjl*jia;
}
fun operator *(fun wjl,fun jia)
{
	fun c;
	memset(c.a,0,sizeof(c.a));
	for(long long k=1;k<=n;k++)
	{
		for(long long i=1;i<=n;i++)
		{
			for(long long j=1;j<=n;j++)c.a[i][j]=(c.a[i][j]+wjl.a[i][k]*jia.a[k][j]%mod)%mod;
		}
	}
	return c;
}
fun ksm(fun x,long long p)
{
	fun res;
	memset(res.a,0,sizeof(res.a));
	for(long long i=1;i<=n;i++) res.a[i][i]=1;
	while(p)
	{
		if(p&1) res=res*x;
		x=x*x;
		p>>=1;
	}
	return res;
}
int main ()
{
	n=read(),t=read();
	for(long long i=1;i<=n;i++)
	{
		for(long long j=1;j<=n;j++)r.a[i][j]=read();
	}
	ans=ksm(r,t);
	for(long long i=1;i<=n;i++)
	{
		for(long long j=1;j<=n;j++)anss=(anss+ans.a[i][j])%mod;
	}
	printf("%lld\n",anss%mod);
	
	return 0; 
}
```


---

## 作者：喵仔牛奶 (赞：6)

## $\mathcal{S}olution$

为了避免混肴，下文用 $S[x][y]$ 的形式代替 $S_{x,y}$。

设 $f[k][i][j]$ 为 $i$ 到 $j$ 通过 $k$ 条路径的方案数。显然有转移方程：

$$f[k][i][j]=\sum_{t=1}^{n}f[k-x][i][t]\times f[x][t][j]$$

$x$ 取什么值都行，但是取 $1$ 最方便，因为 $f[1]=a$，转移方程如下：

$$f[k][i][j]=\sum_{t=1}^{n}f[k-1][i][t]\times a[t][j]$$

我们发现，这个式子长得更矩阵乘法一模一样！所以转移方程变成了：

$$f[k]=f[k-1]\times a$$

最终的 $f[k]$ 就是：

$$f[1]\times \underbrace{a\times a\times\cdots\times a}_{k-1}$$

因为 $f[1]=a$，所以原式等于：

$$a^{k}$$

最终答案是：

$$\sum_{i=1}^{n}\sum_{j=1}^{n}a^{k}[i][j]$$

然后用矩阵快速幂算出来就可以了。

时间复杂度 $\mathcal{O}(n^3\log k)$，空间复杂度 $\mathcal{O}(n^2)$。

## $\mathcal{C}ode$

矩阵快速幂，[368ms](https://www.luogu.com.cn/record/89056095)。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 105, mod = 1e9 + 7;
long long f[N][N], n, k, ans;
struct matrix {
	long long a[N][N];
	matrix operator * (matrix x) const {
		matrix c;
		memset(c.a, 0, sizeof c.a);
		for (int i = 1; i <= n; i ++)
			for (int k = 1; k <= n; k ++)
				for (int j = 1; j <= n; j ++)
					c.a[i][j] += a[i][k] * x.a[k][j], c.a[i][j] %= mod;
		return c;
	}
} dis, res;
int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			cin >> dis.a[i][j];
	for (int i = 1; i <= n; i ++) res.a[i][i] = 1;
	for (; k; k >>= 1, dis = dis * dis)
		if (k & 1) res = res * dis;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			ans += res.a[i][j], ans %= mod;
	cout << ans << '\n';
	return 0;
}
```


---

## 作者：云浅知处 (赞：3)

一开始我以为图是 DAG 然后发现用 $F(i,j)$ 以 $i$ 结尾长度为 $j$ 的路径条数就直接做完了......然后写到一半发现不是。。

然后我就想缩点转成 DAG 再做，结果发现没法做。。

考虑另一个 dp：设 $F_k(i,j)$ 为从 $i$ 到 $j$ 的长度为 $k$ 的路径条数，则答案为：

$$
\sum_{i=1}^n\sum_{j=1}^nF_K(i,j)
$$

考虑枚举中间点，我们有转移方程：

$$
F_k(i,j)=\sum_{x=1}^nF_{1}(i,x)\cdot F_{k-1}(x,j)
$$

注意到这东西是一个类似矩阵乘法的形式，因此考虑用矩阵快速幂加速：记 $A_{ij}=F_1(i,j)$，那么答案其实就是 $A$ 的 $k$ 次幂矩阵中所有数的和。

这样就做到了 $O(n^3\log K)$ 的时间复杂度。

挺有意思的是 $A$ 的初值其实就是原图的邻接矩阵，所以其实把矩阵快速幂板子的代码复制过来稍微改改就能 AC（

```cpp
#include<bits/stdc++.h>

#define sz 55
#define int long long
const int p=1e9+7;

using namespace std;

struct matrix{
	int a[sz+5][sz+5];
	
	inline matrix(){
		memset(a,0,sizeof(a));
	}
	
	inline matrix operator*(const matrix &T)const{
		matrix res;
		for(int i=1;i<=sz;i++){
			for(int k=1;k<=sz;k++){
				int r=a[i][k];
				for(int j=1;j<=sz;j++){
					res.a[i][j]+=r*T.a[k][j];
					res.a[i][j]%=p;
				}
			}
		}
		return res;
	}
	
	inline matrix operator^(int t)const{
		matrix bas,ans;
		for(int i=1;i<=sz;i++)for(int j=1;j<=sz;j++)bas.a[i][j]=a[i][j]%p;
		for(int i=1;i<=sz;i++)ans.a[i][i]=1;
		int x=t;
		while(x){
			if(x&1)ans=ans*bas;
			bas=bas*bas;
			x>>=1;
		}
		return ans;
	}
	
};

matrix res;
int n,k;

signed main(){
	
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>res.a[i][j];
	
	res=res^k;int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			ans=(ans+res.a[i][j])%p;
			
	cout<<ans%p<<endl;
	
	return 0;
}
```

---

## 作者：ssss41 (赞：1)

正在练矩阵乘法，发现了这道裸题。

### 题意

很简明了，不再赘述。

### 分析

这是一道典型的矩乘加速 dp。

首先考虑一种 naive 的 dp 思路，也就是用 $f_{i,j,k}$ 表示从 $i$ 走到 $k$ 步到 $j$ 的方案数，但显然此种思路下 $\Theta(n^3k)$ 的复杂度我们是不能接受的。

转向另一种思路，也就是用 $f_{i,j}^k$ 表示从 $i$ 走 $k$ 步到达 $j$ 的方案数，考虑转移，发现可以用 Floyd 的思路解决，即枚举中间点，写出状态转移方程：

$$f_{i,j}^k=\sum\limits_{t=1}^n f_{i,t}^1 \cdot f_{t,j}^{k-1}$$

可以发现这个东西和矩阵乘法长得很像，因此可以把它放在矩阵上用矩阵快速幂加速，最后答案就是矩阵 $S$ 的 $k$ 次方中的所有数的和。

此时时间复杂度已经降到了 $\Theta(n^3 \log k)$，可以通过此题。

注意取模和开 `long long`

### code

```cpp
#include <bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
int n, k, sum;
struct Floyd {int mp[105][105];}a, ans;
Floyd mul (Floyd x, Floyd y) {//合并矩阵 
	Floyd t; memset(t.mp, 0, sizeof t.mp);
	for (int k = 1; k <= n; ++ k) for (int i = 1; i <= n; ++ i)
	for (int j = 1; j <= n; ++ j) t.mp[i][j] = (t.mp[i][j] + (x.mp[i][k] * y.mp[k][j]) % mod) % mod;
	return t;
}
void ksm () {//矩阵快速幂 
	memset(ans.mp, 0, sizeof ans.mp);
	for (int i = 1; i <= n; ++ i) ans.mp[i][i] = 1;
	while (k) {
		if (k & 1) ans = mul (ans, a);
		a = mul(a, a); k >>= 1;
	}
}
signed main () {
	scanf ("%lld%lld", &n, &k);
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= n; ++ j) scanf ("%lld", &a.mp[i][j]);
	ksm(); sum = 0;
	for (int i = 1; i <= n; ++ i) for (int j = 1; j <= n; ++ j)
		sum = (sum + ans.mp[i][j]) % mod;
	printf ("%lld\n", sum);
	return 0;
}
```

---

## 作者：SIXIANG32 (赞：1)

一道入门矩阵加速 dp 题，但是小蒟蒻开始还是不太会，感谢巨佬 @tobie 的帮忙/qq  

闲话少说，切入正题——  

---
首先我们要确立状态，设 $f_{u, k}$ 为一条长度为 $k$ 的结束节点为 $u$ 的路径数量。初始状态显然是 $f_{u, 0} = 1$。方程也很简单，$f_{u, k} = \sum\limits_{i = 1}^{n}a_{i, u}\times f_{v, k - 1}$。时间复杂度为 $O(n^2k)$。

这样不仅空间会炸掉，时间也会炸掉，考虑优化。发现 $k$ 在 $10^{18}$ 级别，应当考虑矩阵加速。  

设目标矩阵为 $Q=\begin{bmatrix}f_{1,k},f_{2,k},f_{3,k},\dots,f_{n,k}\end{bmatrix}$，很容易想到用 $a$ 做另一个矩阵，那么将 $Q\times a$ 得到新矩阵 $\begin{bmatrix}\sum\limits_{i_1 = 1}^{n} f_{i_1, k}\times a_{i_1,1}\\\sum\limits_{i_2 = 1}^{n} f_{i_2, k}\times a_{i_2,2}\\\sum\limits_{i_3 = 1}^{n} f_{i_3, k}\times a_{i_3,3}\\\dots\\\sum\limits_{i_n = 1}^{n} f_{i_n, k}\times a_{i_n,n}\\\end{bmatrix}$。和我们的方程完全一致，这样矩阵快速幂就行了。

```cpp
#include <iostream>
#include <cstring>
#define MAXN 100000
#define int long long
#define Mod 1000000007
#define QWQ cout << "qwq" << endl;
using namespace std;
int a[1010][1010], n, k;
struct Sealx {
    int qwq[1010][1010];
    Sealx operator * (const Sealx &other) const {
        Sealx res;
        memset(res.qwq, 0, sizeof(res.qwq));
        for(int p = 1; p <= n; p++)
            for(int i = 1; i <= n; i++)
                for(int j = 1; j <= n; j++)
                    res.qwq[p][i] = (res.qwq[p][i] + qwq[p][j] * other.qwq[j][i]) % Mod;
        return res;
    }
};
int qpow_M(int k) {
    Sealx res, qaq;
	memset(res.qwq, 0, sizeof(res.qwq));
    for(int p = 1; p <= n; p++)    	
		res.qwq[1][p] = 1;
    memset(qaq.qwq, 0, sizeof(qaq.qwq));
    for(int p = 1; p <= n; p++)
    	for(int i = 1; i <= n; i++)
    		qaq.qwq[p][i] = a[p][i];
    while(k) {
        if(k & 1) res = res * qaq;
        qaq = qaq * qaq, k >>= 1;
    }
    int rest = 0;
    for(int p = 1; p <= n; p++)
    	rest = (rest + res.qwq[1][p]) % Mod;
    return rest;
}
signed main() {
	cin >> n >> k;
	for(int p = 1; p <= n; p++)
		for(int i = 1; i <= n; i++)
			cin >> a[p][i];
	cout << qpow_M(k) << endl;
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

又是简单题。

我们知道弗洛伊德可以求解[传递闭包](https://www.luogu.com.cn/problem/B3611)。

我们有矩阵 $M$，我们给 $M_{k,i,j}$ 定义为 $i\to j$ 长度为 $k$ 的路径数，细想不难发现有转移：

+ $M_{k,i,j}=\sum\limits_{p=1}^{n} (M_{k-1,i,p}\times M_{1,p,j})$。

直接暴力弗洛伊德得到了 $kn^3$ 的上天复杂度。

我们发现这实际就是矩阵乘法，$M_{k}=M_{k-1}\times M_1$。

直接矩阵乘法即可——$M_k=M_1^k$，结果为 $\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n} M_{k,i,j}$。

得到了 $O(n^3\log k)$ 的做法。

[通过记录](https://atcoder.jp/contests/dp/submissions/38318799)

```cpp
#include <stdio.h>
#include <string.h>
using namespace std;
int n;
long long k;
const int mod=1e9+7;
class Matrix{
	public:
		long long s[105][105];
		void input(){
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					scanf("%lld",&s[i][j]);
		}
		void output(){
			int ret=0;
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++)
					(ret+=s[i][j])%=mod;
			}
			printf("%d",ret);
		}
}ans,mid,a;
Matrix operator *(const Matrix& a,const Matrix& b){
	memset(mid.s,0,sizeof mid.s);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++){
				mid.s[i][j]+=a.s[i][k]*b.s[k][j];
				mid.s[i][j]%=mod;
			}
	return(mid);
}
int main(){
	scanf("%d %lld",&n,&k);
	a.input();
	for(int i=1;i<=n;i++)ans.s[i][i]=1;
	while(k>0){
		if(k&1)ans=ans*a;
		a=a*a;
		k>>=1;
	}
	ans.output();
	return(0);
}
```

---

## 作者：_dijkstra_ (赞：0)

矩阵快速幂优化 Floyd 板子。

前置知识：矩阵加速、Floyd。

## 思路

类似 Floyd，设 $dp_{u, v, s}$ 表示 $u$ 走 $s$ 步到 $v$，方案数。

那么类似 Floyd，有转移方程：

$$dp_{u, v, s} = \sum\limits_{w = 1}^n dp_{u, w, 1} \times dp_{k, v, s - 1}$$

含义：枚举中转站 $w$，统计从 $u$ 一步走到 $w$ 的方案数，以及 $w$ 用 $(s - 1)$ 步走到 $v$ 的方案数。乘法原理。

很容易发现，**所有的** $dp_{u, v, s}$ 都可以从 $dp_{u, w, 1}$ 转移来。这就说明，我们可以套矩阵快速幂。

也就是说，我们对原矩阵直接跑快速幂就完事了！

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
const int N = 55, mod = 1e9 + 7;
int n;
namespace Matrix { //矩阵快速幂板子
	int a[N][N];
	void mul(int ANS[][N], int x[][N], int y[][N])
	{
		int ans[N][N] = {};
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				for (int k = 1; k <= n; k++)
					ans[i][j] = (ans[i][j] + 1ll * x[i][k] * y[k][j]) % mod;
		memcpy(ANS, ans, sizeof ans);
	}
	void ksm(int x[][N], ll y)
	{
		int ans[N][N] = {};
		for (int i = 1; i <= n; i++) ans[i][i] = 1;
		while (y)
		{
			if (y & 1) mul(ans, ans, x);
			mul(x, x, x);
			y >>= 1;
		}
		memcpy(x, ans, sizeof ans);
	}
}; using namespace Matrix;
int main()
{
	ios::sync_with_stdio(false);
	ll k;
	scanf("%d%lld", &n, &k);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &a[i][j]);
	ksm(a, k); //直接对原矩阵跑快速幂！
	int ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			ans = (ans + a[i][j]) % mod;
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：5k_sync_closer (赞：0)

题意：给定一张有向简单图，求长度为 $K$ 的路径条数。
# 思路
考虑 DP。设 $f_{i,j,x}$ 为 $i\to j$ 且长度为 $x$ 的路径条数。

考虑枚举中间点。根据乘法原理，显然有 $f_{i,j,x}=\sum\limits_{k=1}^nf_{i,k,x-1}\times f_{k,j,1}$。

我们设 $F_x$ 表示 $f_{i,j,x}$ 组成的矩阵，则上式简化为 $F_x=F_{x-1}\times F_1$，即 $F_x=F_1^x$。

用矩阵快速幂维护之。显然地，答案为 $\sum\limits_{i=1}^n\sum\limits_{j=1}^nF_{x,i,j}$。
# 代码
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define M 1000000007
#define F(x) for(int x = 1;x <= n;++x)
int n;long long k, s;struct S
{
	long long a[55][55];S() {memset(a, 0, sizeof a);}S operator*(S b) {S c;
	F(k) F(i) F(j) (c.a[i][j] += a[i][k] * b.a[k][j] % M) %= M;return c;}
}a, q;
int main()
{
	scanf("%d%lld", &n, &k);F(i) {q.a[i][i] = 1;F(j) scanf("%lld", &a.a[i][j]);}for(;k;k >>= 1)
	{if(k & 1) q = q * a;a = a * a;}F(i) F(j) (s += q.a[i][j]) %= M;return printf("%lld", s), 0;
}
```


---

## 作者：Endt (赞：0)

# Walk-题解

### 题意

给一张有向简单图，给出邻接矩阵，求长度为 $K$ 的路径条数，答案对 $10^9+7$ 取模。

$K\le10^{18}$。

### 分析

这么大个 $K$，肯定需要一个 $\log$ 级别的算法。我们知道一个邻接矩阵的 $k$ 次幂的意义是这两个点走 $k$ 步可以到达，所以这就是一个裸的矩阵快速幂。

统计答案直接将矩阵上的值相加即可，注意取模。

### 代码


```cpp
#include<bits/stdc++.h>

#define  Int  long long int
#define  Tem  template
#define  Pub  public

using std::min;
using std::max;

const Int mod=1e9+7;
const int B=55;

Int n;
Int k;
Int g[55][55];

void turn0(Int x[B][B]){
	memset(x,0,sizeof(x));
	for(int i=0;i<n;++i)x[i][i]=1;
}
void mul(Int x[B][B],Int y[B][B],Int z[B][B]){//x=y*z;
	Int X[B][B]={0};
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			for(int k=0;k<n;++k){
				X[i][j]=(X[i][j]+(y[i][k]%mod*z[k][j]%mod)%mod)%mod;
			}
		}
	}
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			x[i][j]=X[i][j];
		}
	}
}
void power(Int x[B][B],Int Y[B][B],Int z){//x=y^z
	if(z==0)return;
	Int y[B][B];
	for(int i=0;i<n;++i)for(int j=0;j<n;++j)y[i][j]=Y[i][j];
	while(z>1){
		if(z&1)mul(x,x,y);
		mul(y,y,y);
		z>>=1;
	}
	mul(x,x,y);
}

Int ans;

int main(){
    scanf("%lld%lld",&n,&k);
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            scanf("%lld",&g[i][j]);
            
    power(g,g,k-1);
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            ans=(ans+g[i][j])%mod;
    printf("%lld",ans);
    
    return 0;
}
```

---

## 作者：activeO (赞：0)

## 题目大意


[题面](https://www.luogu.com.cn/problem/AT4539)
说的很清楚了，这里不多说。

## 思路

首先一开始想到 dp，~~毕竟这是 AT 的 dp 题~~于是，我们可以确定状态:

$ dp_i[u][v] $ 表示从 $ u \rightarrow v $ 的长度为 i 的路径有多少条。

然后就可以比较容易地推出方程:

$ dp_i[u][v] = \sum_{k=1}^n dp_{i-1}[u][k] \cdot dp_1[k][v] $。

显然最终答案就是 $ \sum_{i=1}^n \sum_{j=1}^n dp_k[i][j] $。
初始矩阵 $ dp_1 $ 就是我们输入的邻接矩阵。

阿但是~，数据范围:

- $ 1 \leq N \leq 50 $

- $ 1 \leq K \leq 10^{18} $

复杂度 $ O(k \cdot n^3) $，显然没办法暴力推。

于是我们发现，这个方程和矩阵乘法一样，于是就可以用矩阵快速幂。

即: $ dp_k=dp_1^k $，时间复杂度 $ O(n^3 \log k) $，可以通过此题。

## 代码

注：变量名与上文略有不同。

```cpp
//zlttxdy luoguid:@zlttql
#include <bits/stdc++.h>//祝大家学习愉快！

#define int long long

using namespace std;

const int maxn=55;
const int mod=1e9+7;
struct Matrix{
	int a[maxn][maxn],n;
	Matrix(){
		memset(a,0,sizeof(a));
	}
	Matrix operator *(const Matrix &b) const {
		Matrix ret;
		ret.n=n;
		for(int i=1;i<=ret.n;i++){
			for(int k=1;k<=ret.n;k++){
				for(int j=1;j<=ret.n;j++) ret.a[i][j]=(ret.a[i][j]+a[i][k]*b.a[k][j]%mod)%mod;
			}
		}
		return ret;
	}
}zltak;

Matrix qpow(Matrix x,int y){
	Matrix res;
	res.n=x.n;
	for(int i=1;i<=res.n;i++) res.a[i][i]=1;
	while(y){
		if(y&1) res=res*x;
		x=x*x;
		y>>=1;
	}
	return res;
}

signed main(){
	
	int n,IOI,ans=0;
	
	scanf("%lld %lld",&n,&IOI);
	
	zltak.n=n;
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) scanf("%lld",&zltak.a[i][j]);
	}
	
	Matrix zlttql=qpow(zltak,IOI);
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) ans=(ans+zlttql.a[i][j])%mod;
	}
	
	printf("%lld\n",ans);
	
	return 0;
}

```



---

