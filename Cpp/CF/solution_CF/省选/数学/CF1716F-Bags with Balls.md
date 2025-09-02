# Bags with Balls

## 题目描述

# Bags with Balls 袋中之球


这里有 $ n $ 个袋子，每个袋子里面有 $ m $ 个带有从 $ 1 $ - $ m $ 标记的球。对于每一个 $ 1 $ ≤ $ i $ ≤ $ m $  来说，每个袋子中都一定存在一个带有 $ i $ 标记的球。

你需要在每个袋子中取出一个球 ( 所有的袋子都是不同的，比如在 $ 1 $ 号袋子取 $ 2 $ 号球 并且从 $ 2 $ 号袋子里取 $ 1 $ 号球 与 从 $ 1 $ 号袋子取 $ 1 $ 号球并且从 $ 2 $ 号袋子取 $ 2 $ 号球是不同的两种方案 ) 然后计算出你取出的标号是奇数的球的数量，记这个数量为 $ F $ 。

你的任务是计算所有可能的取球方案的 $ F^k $ 之和。

## 样例 #1

### 输入

```
5
2 3 8
1 1 1
1 5 10
3 7 2000
1337666 42424242 2000```

### 输出

```
1028
1
3
729229716
652219904```

# 题解

## 作者：DeaphetS (赞：39)

[更好的阅读体验](https://www.luogu.com.cn/blog/DeaphetS/solution-cf1716f)

[给自己的 cnblogs 博客引路](https://www.cnblogs.com/DeaphetS/p/16552830.html)



一道很好的**第二类斯特林数**题，当然如果不会相关知识却知道函数求导的话，也可以推出公式（本人就属于后者）。

PS：不过 OIer 如果会函数求导的话应该肯定会斯特林数吧……

题目链接：[1716F - Bags with Balls](https://codeforces.com/contest/1716/problem/F)

题目大意：设一个长度为 $n$，元素取值在 $[1,m]$ 内的数组 $A$ 中的奇数元素个数为 $x$。令 $F(A)=x^k$，对所有可能的 $A$，求 $\sum F(A)$。

首先肯定是列式子，设奇数个数为 $x$，偶数个数为 $y$。那么枚举奇数个数，就有：
$$
ans=\sum_{i=1}^{n}i^k\cdot C_n^i\cdot x^iy^{n-i}
$$
关于式子的简化有两种做法，下面一一介绍。

### 做法一（函数求导）

这是本人考场上想到的做法，需要对初等函数求导有基础的了解，适合不熟悉第二类斯特林数的选手，如果觉得太长可以看简单粗暴的做法二。

考虑组合数学中恒等式 $\sum_{i=1}^n i\cdot C_n^i=n\cdot2^{n-1}$ 及 $\sum_{i=1}^n i^2\cdot C_n^i=n(n+1)\cdot2^{n-2}$ 的证明过程，先看第一个式子：

- 设 $f(x)=(1+x)^n=\sum_{i=0}^{n} C_n^i\cdot x^i$，将函数关于 $x$ 求导；
- 得到 $n\cdot (1+x)^{n-1}=\sum_{i=1}^ni\cdot C_n^i\cdot x^{i-1}$；
- 两边同乘 $x$ 得 $n\cdot x(1+x)^{n-1}=\sum_{i=1}^ni\cdot C_n^i\cdot x^{i}$；
- 将 $x=1$ 代入即可得，$n\cdot 2^{n-1}=\sum_{i=1}^n i\cdot C_n^i$。

对于第二个式子，我们也可以利用同样的技巧：

- 首先还是得到 $n\cdot x(1+x)^{n-1}=\sum_{i=1}^ni\cdot C_n^i\cdot x^{i}$；
- 还是关于 $x$ 求导得到 $n\cdot (1+x)^{n-1}+n(n-1)\cdot x(1+x)^{n-2}=\sum_{i=1}^ni^2\cdot C_n^i\cdot x^{i-1}$；
- 同样再次乘 $x$：$n\cdot x(1+x)^{n-1}+n(n-1)\cdot x^2(1+x)^{n-2}=\sum_{i=1}^ni^2\cdot C_n^i\cdot x^{i}$；
- 再次将 $x=1$ 代入就是 $n(n+1)\cdot2^{n-2}=\sum_{i=1}^n i^2\cdot C_n^i$。

通过上述两个式子的证明过程，我们不难发现，每次我们只要将式子 $\sum_{i=1}^ni^k\cdot C_n^i\cdot x^{i}$ 求导后再乘以 $x$，就能得到式子 $\sum_{i=1}^ni^{k+1}\cdot C_n^i\cdot x^{i}$。但是我们需要求的式子是 $\sum_{i=1}^{n}i^k\cdot C_n^i\cdot x^iy^{n-i}$，那么只需要把一开始的函数变成 $f(x)=(x+y)^n$，并把 $y$ 看成一个已知常数，就能够得到对应的式子了，那么我们只需要求出等式左边每一项的系数就可以做到 $O(k)$ 的快速求解。另外如果有大佬熟练掌握生成函数求导应该也有其它的解题方法，但是由于本弱不会所以我们来另辟蹊径。

我们设 $f(x)=(x+y)^n$，再走一遍刚刚的流程：

- $(x+y)^n=\sum_{i=0}^{n} C_n^i\cdot x^iy^{n-i}$，对 $x$ 求导；
- $n\cdot (x+y)^{n-1}=\sum_{i=1}^{n} i\cdot C_n^i\cdot x^{i-1}y^{n-i}$，两边同乘 $x$；
- $n\cdot x(x+y)^{n-1}=\sum_{i=1}^{n} i\cdot C_n^i\cdot x^{i}y^{n-i}$，这是 $k=1$ 的情况，再次求导；
- $n\cdot (x+y)^{n-1}+n(n-1)\cdot x(x+y)^{n-2}=\sum_{i=1}^{n} i^2\cdot C_n^i\cdot x^{i-1}y^{n-i}$，再次两边同乘 $x$；
- $n\cdot x(x+y)^{n-1}+n(n-1)\cdot x^2(x+y)^{n-2}=\sum_{i=1}^{n} i^2\cdot C_n^i\cdot x^{i}y^{n-i}$，得到 $k=2$ 的结果，那么我们还是求导后再两边同乘 $x$；
- $n\cdot x(x+y)^{n-1}+3n(n-1)\cdot x^2(x+y)^{n-2}+n(n-1)(n-2)\cdot x^3(x+y)^{n-3}=\sum_{i=1}^{n} i^3\cdot C_n^i\cdot x^{i}y^{n-i}$；
- ……

那么到这里我们可以发现，等式左边与 $x$ 有关的式子都是 $x^i(x+y)^{n-i}$ 的形式，而对应的系数则是一个数字乘上一个 $n$ 的下降幂，即 $\frac{n!}{(n-i)!}=n^{\underline{i}}$，我们来关注一下经过 $k$ 次求导后，$x^i(x+y)^{n-i}$ 的系数 $c(k,i)$ 的递推式。

对于 $x^i(x+y)^{n-i}$，我们将其求导后可以得到 $i\cdot x^{i-1}(x+y)+(n-i)\cdot x^{i}(x+y)^{n-i-1}$。那么乘以 $x$ 后就能得到 $i\cdot x^{i}(x+y)+(n-i)\cdot x^{i+1}(x+y)^{n-i-1}$，由此可以得出 $c(k,i)$ 对 $c(k+1,i)$ 和 $c(k+1,i+1)$ 分别有 $i$ 和 $n-i$ 的贡献。于是就有递推式 $c(k,i)=i\cdot c(k-1,i)+(n-i+1)\cdot c(k-1,i-1)$。

那么可以通过（打表）观察得出，若设 $c(k,i)=s(k,i)\cdot n^{\underline{i}}$，就会有递推式 $s(k,i)=i\cdot s(k-1,i)+s(k-1,i-1)$。有了递推式之后就是预处理系数接一个 for 循环解决的事，实际上如果对第二类斯特林数有一定了解的话就不难看出这其实就是第二类斯特林数的递推式，不过就算不知道相关知识也不影响解题了。

最后把答案式子写出来（不要忘记 $x+y=m$）：
$$
ans=\sum_{i=1}^{k}s(k,i)\cdot n^{\underline i}\cdot x^im^{n-i}
$$

### 做法二（暴力推式子）

学弟的做法，比较简单粗暴，非常适合 OI 巨佬及具体数学带师，需要知道式子 $n^m =\sum_{k=0}^m{m \brace k} \binom{n}{k}k!$。${m \brace k}$ 即为第二类斯特林数 ${S2}(m,k)$。

$
\begin{aligned}
ans& =\sum_{i=0}^{n}i^k\cdot \binom{n}{i}\cdot x^iy^{n-i}\\
& =\sum_{i=0}^{n}\binom{n}{i} x^iy^{n-i}\cdot \sum_{j=0}^k \begin{Bmatrix} k\\j \end{Bmatrix} \binom{i}{j}j!\\
& = \sum_{j=0}^{k}\begin{Bmatrix} k\\j \end{Bmatrix} \sum_{i=0}^{n} \frac{n!}{i!(n-i)!}\cdot x^iy^{n-i}\cdot \frac{i!}{(i-j)!} \\
& = \sum_{j=0}^{k}\begin{Bmatrix} k\\j \end{Bmatrix} \sum_{i=0}^{n} \frac{n!}{(n-i)!(i-j)!}\cdot x^iy^{n-i}\\
& = \sum_{j=0}^{k}\begin{Bmatrix} k\\j \end{Bmatrix} \frac{n!}{(n-j)!}\sum_{i=0}^{n}\binom{n-j}{n-i} x^iy^{n-i}\\
& = \sum_{j=0}^{k}\begin{Bmatrix} k\\j \end{Bmatrix} \frac{n!}{(n-j)!}\sum_{t=0}^{n-j}\binom{n-j}{t} x^{n-t}y^{t}\\
& = \sum_{j=0}^{k}\begin{Bmatrix} k\\j \end{Bmatrix} n^{\underline j}\sum_{t=0}^{n-j}\binom{n-j}{t} x^j\cdot x^{n-j-t}y^{t}\\
& = \sum_{j=0}^{k}\begin{Bmatrix} k\\j \end{Bmatrix} n^{\underline j}x^jm^{n-j}
\end{aligned}
$

也得到了一样的结果。

最后附上本人简短而又丑陋的代码，时间复杂度 $O(k^2+Tk)$，不要忘了 $k$ 要和 $n$ 取 $\min$：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 2020
#define LL long long
#define MOD 998244353
LL T,n,m,k,s[N][N];
LL qow(LL x,LL y){return y?(y&1?x*qow(x,y-1)%MOD:qow(x*x%MOD,y/2)):1;}
int main()
{
	s[1][1]=1;
	for(LL i=2;i<N;i++)
	for(LL j=1;j<=i;j++)
		s[i][j]=(s[i-1][j-1]+j*s[i-1][j])%MOD;
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld%lld",&n,&m,&k);
		LL ans=0,x=m-m/2,inv=qow(m,MOD-2);
		for(LL i=1,K=x*qow(m,n-1)%MOD*n%MOD;i<=min(n,k);i++,K=K*x%MOD*inv%MOD*(n-i+1)%MOD)
			ans=(ans+s[k][i]*K)%MOD;
		printf("%lld\n",ans);
	}
}
```



---

## 作者：出言不逊王子 (赞：8)

好题。

我们要计算所有可能数组的 $f(x)$ 的和。

我们考虑假设 $[1,m]$ 中有 $x$ 个奇数，$y$ 个偶数，则有 $m=x+y$。

我们假设当前有 $i$ 个奇数，则剩下 $n-i$ 个都是偶数。

则有 $i$ 个奇数，这些奇数可能的方案有 $x^i$ 个。相应地，偶数可能的方案有 $y^{n-i}$ 个。

我们要在 $n$ 个位置中给这些奇数选 $i$ 个位置，方案数是 $C_n^i$。

为什么这里是无序的呢？因为上边选取奇数的过程就已经帮我们有序了。

那为什么不在上面选取奇数的时候无序而在下面排序时有序呢？因为上边无序还得把**选取几种奇数**和**选取几个奇数**分开讨论，白白增加了时间复杂度。

然后再加上 $i$ 个奇数对答案的贡献 $i^k$，我们就可以得到，奇数个数为 $i$ 时对答案的贡献是 $C_n^i\times x^i\times y^{n-i}$。 

所以答案就是 $\sum_{i=0}^n C_n^i\times x^i\times y^{n-i}$。

然后考虑一个式子：$n^m=\sum_{k=0}^m \{^m_{\ k}\}C_n^k\times k!$

然后拆开这里面唯一一个和 $n,m$ 毫无关系的项 $i^k$，答案变成了：

$\sum_{i=0}^n C_{n}^i x^i y^{n-i}\times (\sum_{j=0}^k \{^k_{j}\}C_i^j \times j!)$

看到枚举对象从 $n$ 可以变成 $k$，这不得把 $k$ 捞到前面来？于是答案变成了：

$\sum_{j=0}^k \{^k_{j}\}\times j!\sum_{i=0}^n C_{n}^i x^i y^{n-i}\times C_i^j $

到这一步毫无思路了。但是观察到两个组合数，能不能把组合数展开？于是答案变成了：

$\sum_{j=0}^k \{^k_{j}\}\times j!\sum_{i=0}^n \frac{n!}{i!(n-i)!} x^i y^{n-i}\times \frac{i!}{j!(i-j)!}$

哎哟哟，$i!$ 和 $j!$ 不是可以削掉吗，于是答案变成了：

$\sum_{j=0}^k \{^k_{j}\}\sum_{i=0}^n \frac{n!}{(n-i)!(i-j)!} x^i y^{n-i}$

那个分数长得好像组合的形式啊，我们观察到 $n-i+i-j=n-j$，这样一来中间那一项可以变成组合的形式。

具体实现起来，可以把分数乘上 $(n-j)!$，然后再给式子乘上 $\frac{n!}{(n-j)!}$。

$\sum_{j=0}^k \{^k_{j}\}\times \frac{n!}{(n-j)!}\sum_{i=0}^n C_{n-j}^{n-i} x^i y^{n-i}$

发现右边这个式子很像二项式定理，考虑通过微操把他变成二项式定理的形式。

然后看上去没法优化了。但是这里面出现了三个 $n-x$，能不能让循环反过来写呢？

考虑 $p=n-i$。因为 $m>n$ 时 $C_n^m$ 无意义，所以循环上界改成 $n-j$。

$\sum_{j=0}^k \{^k_{j}\}\times \frac{n!}{(n-j)!}\sum_{p=0}^{n-j} C_{n-j}^{p} x^{n-p} y^{p}$

那为什么要转一下循环顺序呢？因为不转的话循环的变量是 $i$，好像和 $n-i$ 没有什么太大的联系。

所以翻转一下，这样循环顺序就对上了。

此时右边的式子充斥着 $n-j$ 和 $p$。但是 $x$ 的次幂是 $n-p$，和 $n-j$ 还有一定差别，如果改完了，右边这个式子就只有两种系数了！

现在我们观察到 $x^{n-p}=x^{(n-j)-p}\times x^j$，那么我们就把 $x$ 的项拆成两半。

$\sum_{j=0}^k \{^k_{j}\}\times \frac{n!}{(n-j)!}\times x^j\sum_{p=0}^{n-j} C_{n-j}^{p} x^{n-j-p} y^{p}$

现在右边的这个式子就是二项式定理的标准形式了。和下文二项式定理的式子一对比，我们会发现他们长得简直一模一样！

$(x+y)^n=\sum_{k=0}^n C_n^k \times x^k\times y^{n-k}$

然后我们就可以快乐地把右边的式子替换成 $(x+y)^{n-j}=m^{n-j}$ 了。

现在答案变成了 $\sum_{j=0}^k \{^k_{j}\}\times \frac{n!}{(n-j)!}\times x^j\times m^{n-j}$。

但是第二类斯特林数不可能每次给你算一遍，那么我们通过递推公式预处理出来即可。

不仅如此 $\frac{n!}{(n-j)!}$ 太大了，所以我们必须通过上一个 $j$ 时的答案推出下一个 $j$ 时的。

具体地，每次我们让当前的答案 $c$ 乘以 $n-j$，乘以一个 $x$ 再除以一个 $m$。

最后将这个 $c$ 和 $\{^k_{j}\}$ 乘起来，丢到最终的答案里。

代码：

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define int long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=2001,inf=998244353ll;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
inline int ksm(int x,int y){
	int res=1;while(y){
		if(y&1) res=res*x%inf;
		x=x*x%inf;y>>=1;
	}
	return res;
}
int stlin2[N][N],k,m,n,x,invm;
void mian(){
	n=read(),m=read(),k=read();
	x=m-m/2,invm=ksm(m,inf-2);//[1,m]奇数个数 
	int cur=ksm(m,n),res=0;
	fs(i,1,min(n,k),1){
		cur=cur*invm%inf*x%inf*(n-i+1)%inf;
		res=(res+cur*stlin2[k][i])%inf;
	} 
	printf("%lld\n",res);
}
signed main(){
	stlin2[1][1]=1;
	fs(i,2,N-1,1) fs(j,1,i,1) stlin2[i][j]=(stlin2[i-1][j-1]+j*stlin2[i-1][j]%inf)%inf;
	int t=read();while(t--) mian();
	return 0;
}
```

---

## 作者：Shimotsuki (赞：4)

每个袋子有 $\left \lceil \frac{m}{2}  \right \rceil $ 个奇数编号的球，有 $\left \lfloor \frac{m}{2}  \right \rfloor $ 个偶数编号的球，综合一下题意，可以发现此题实际是在求：
$$\sum_{i=0}^{n}i^k \binom{n}{i} \left ( \left \lceil \frac{m}{2}  \right \rceil  \right )^i \left ( \left \lfloor \frac{m}{2}  \right \rfloor  \right )^{n-i}$$

首先考虑处理式子中的 $i^k$，我们可以利用第二类斯特林数将常幂展开为下降幂求和的方法：
$$i^k=\sum_{j=0}^{k}\begin{Bmatrix} k\\j \end{Bmatrix}j!\binom{i}{j}$$
$$=\sum_{j=0}^{k}\begin{Bmatrix} k\\j \end{Bmatrix}i^{\underline j}$$
代入原式：
$$\sum_{i=0}^{n}i^k \binom{n}{i} \left ( \left \lceil \frac{m}{2}  \right \rceil  \right )^i \left ( \left \lfloor \frac{m}{2}  \right \rfloor  \right )^{n-i}$$
$$=\sum_{i=0}^{n}\sum_{j=0}^{k}\begin{Bmatrix} k\\j \end{Bmatrix}i^{\underline j}\binom{n}{i} \left ( \left \lceil \frac{m}{2}  \right \rceil  \right )^i \left ( \left \lfloor \frac{m}{2}  \right \rfloor  \right )^{n-i}$$
因为
$$\binom{n}{i}i^{\underline j}=\binom{n-j}{i-j}n^{\underline j}$$
所以式子又可以化成：
$$=\sum_{i=0}^{n}\sum_{j=0}^{k}\begin{Bmatrix} k\\j \end{Bmatrix}\binom{n-j}{i-j}n^{\underline j} \left ( \left \lceil \frac{m}{2}  \right \rceil  \right )^i \left ( \left \lfloor \frac{m}{2}  \right \rfloor  \right )^{n-i}$$
注意到
$$\sum_{j=0}^{k}\begin{Bmatrix} k\\j \end{Bmatrix} n^{\underline j}$$
这个部分与 $i$ 并没有关系，所以可以把这部分提到前面：
$$\sum_{j=0}^{k}\begin{Bmatrix} k\\j \end{Bmatrix} n^{\underline j}\sum_{i=0}^{n}\binom{n-j}{n-i} \left ( \left \lceil \frac{m}{2}  \right \rceil  \right )^i \left ( \left \lfloor \frac{m}{2}  \right \rfloor  \right )^{n-i}$$
最后，我们可以用二项式定理化到最简，最简式子：
$$\sum_{j=0}^{k}\begin{Bmatrix} k\\j \end{Bmatrix}n^{\underline j}\left ( \left \lceil \frac{m}{2}  \right \rceil  \right ) ^j m^{n-j}$$
综上，我们可以 $O(k^2)$ 递推第二类斯特林数，单次查询 $O(k)$，足以通过此题。

递推代码：
```cpp
stir[0][0]=1;
for(int i=1;i<=2000;++i){
	for(int j=1;j<=i;++j) stir[i][j]=(stir[i-1][j-1]+stir[i-1][j]*j%mod)%mod;
}
```
查询代码：
```cpp
inline ll qpow(ll a,ll b){
	ll res=1;
	while(b){
		if(b&1) res=res*a%mod;
		b>>=1;a=a*a%mod;
	}
	return res;
}
inline void solve(){
	ll n,m,k;
	cin>>n>>m>>k;
	ll ans=0;
	ll base=qpow(m,n),inv=qpow(m,mod-2);
	for(int i=1;i<=min(n,k);++i){
		base=base*(n-i+1)%mod*((m+1)/2)%mod*inv%mod;
		ans=(ans+base*stir[k][i]%mod)%mod;
	}
	cout<<ans<<'\n';
}
```


---

## 作者：_SeeleVollerei_ (赞：3)

这种题好像挺常见的，但是谁能想到这是我第一次赛时做出这种题呢。

为了方便，首先设 $l=\lceil\frac{m}{2}\rceil$。

考虑放到原式子考虑这个问题，相当于 n 个 0/1 加起来的 k 次方。

考虑相当于有 k 个式子，要求从每个式子选一个 1，考虑怎么求这个的方案数。

假设这 k 个 1 来自 i 个盒子，那么这部分的方案数为 $\sum \frac{k!}{\prod p_j!}$，这里满足 $\sum_{j=1}^i p_j=k$。

然后直接设 $f_{i,k}$ 为上面的方案数，那么答案为

$$ans=\sum_{i=1}^{\min(n,k)}\binom{n}{i}m^{n-i}l^if_{i,k}$$

考虑怎么求 $f_{i,k}$，可以先令 $g_{i,k}=\frac{f_{i,k}}{k!}$，那么有 $g_{i,j}\times \frac{1}{k!}\to g_{i+1,j+k}$，发现这是个卷积的形式，$O(k^2\log k)$ 预处理即可。

对于 $\binom{n}{i}$ 和后面两个幂，直接在枚举 i 的过程中算就好，所以总的复杂度为 $O(k^2\log k+Tk)$。

C++14 过不去，C++20 跑得还可以。

https://codeforces.com/contest/1716/submission/166973566

考虑优化这个 $f_{i,k}$ 的预处理过程，从组合意义考虑，相当于把 k 个有标号小球分到 i 个有标号箱子，而第二类斯特林数的意义与其唯一的差别就是箱子无标号，所以有 $f_{i,k}=i!S_{k,i}$。

第二类斯特林数的求解是 $O(k^2)$ 的，所以总的复杂度为 $O(k^2+Tk)$。

https://codeforces.com/contest/1716/submission/166996254

---

## 作者：Messywind (赞：2)

**题意**

给定三个正整数 $n,m,k$，有 $n$ 个盒子，每个盒子有 $m$ 个标号分别为 $1 \sim m$ 的球，现从每个盒子选出恰好一个球，将奇数编号的球的个数记为 $F$，求所有方案的 $F ^ k$ 之和对 $998 \, 244 \, 353$ 取模。 

$(1 \le n, m \le 998244352, 1 \le k \le 2 \times 10 ^ 3)$

**分析：**

首先每个盒子有 $\lceil \dfrac{m}{2} \rceil$ 个奇数球和 $\lfloor \dfrac{m}{2} \rfloor$ 个偶数球，那么所有方案数为 $m ^ n = (\lceil \dfrac{m}{2} \rceil + \lfloor \dfrac{m}{2} \rfloor) ^ n$，根据二项式定理，所以每个 $F$ 的贡献就为 $F ^ k \times \dbinom{n}{F} \times \lceil \dfrac{m}{2} \rceil ^ F \times \lfloor \dfrac{m}{2} \rfloor ^ {n - F}$ 所以总答案为
$$
\sum_{i = 0} ^ {n} i ^ k \times \binom{n}{i} \times \lceil \dfrac{m}{2} \rceil ^ i \times \lfloor \dfrac{m}{2} \rfloor ^ {n - i}
$$
由于 $n \le 998244352$，没法直接求，但是看到 $i ^ k$ 想到自然数幂展开
$$
i ^ k = \sum_{j = 0} ^ {k} \begin{Bmatrix}k \\ j\end{Bmatrix} \times j! \times \binom{i}{j}
$$
带入得
$$
\sum_{i = 0} ^ {n} \dbinom{n}{i} \times \lceil \dfrac{m}{2} \rceil ^ i \times \lfloor \dfrac{m}{2} \rfloor ^ {n - i} \sum_{j = 0} ^ {k} \begin{Bmatrix}k \\ j\end{Bmatrix} \times j! \times \binom{i}{j}
$$
将 $\dbinom{n}{i}$ 放到后面的求和号化简：$\dbinom{n}{i} \times j! \times \dbinom{i}{j} = \dfrac{n!}{i! \times (n - i)!} \times j! \times \dfrac{i!}{j! \times (i - j)!} = \dfrac{n!}{(n - i)! \times (i - j)!}$，那么式子变为
$$
\sum_{i = 0} ^ {n} \lceil \dfrac{m}{2} \rceil ^ i \times \lfloor \dfrac{m}{2} \rfloor ^ {n - i} \sum_{j = 0} ^ {k} \begin{Bmatrix}k \\ j\end{Bmatrix} \times \dfrac{n!}{(n - i)! \times (i - j)!}
$$
交换求和次序，注意 $i$ 要从 $j$ 开始，因为要保证 $i - j \ge 0$

$$
\sum_{j = 0} ^ {k} \begin{Bmatrix}k \\ j\end{Bmatrix} \sum_{i = j} ^ {n} \dfrac{n!}{(n - i)! \times (i - j)!} \times \lceil \dfrac{m}{2} \rceil ^ i \times \lfloor \dfrac{m}{2} \rfloor ^ {n - i}
$$
对第二个和式做变换 $i - j \rightarrow i$

$$
\sum_{j = 0} ^ {k} \begin{Bmatrix}k \\ j\end{Bmatrix} \sum_{i = 0} ^ {n - j} \dfrac{n!}{(n - i - j)! \times i!} \times \lceil \dfrac{m}{2} \rceil ^ {i + j} \times \lfloor \dfrac{m}{2} \rfloor ^ {n - i - j}
$$
到这里发现第二个和式比较像二项式展开了，即 $(a + b) ^ n = \sum\limits_{i = 0} ^ {n} \dbinom{n}{i} a ^ {i} b ^ {n - i}$，那么考虑往这个方向凑式子，首先要解决的是组合数，发现第二个和式上界为 $n - j$，那么我们就要凑一个 $\dbinom{n - j}{i} = \dfrac{(n - j)!}{(n - i - j) \times i!}$ 的组合数，发现恰好多了 $n \times(n - 1) \times \cdots \times (n - j + 1) = n ^ {\underline j}$，那么后面也多了 $\lceil \dfrac{m}{2} \rceil ^ {j}$，提出来之后为
$$
\sum_{j = 0} ^ {k} \begin{Bmatrix}k \\ j\end{Bmatrix} \times n ^ {\underline j} \times \lceil \dfrac{m}{2} \rceil ^ {j} \sum_{i = 0} ^ {n - j} \binom{n - j}{i} \times \lceil \dfrac{m}{2} \rceil ^ {i} \times \lfloor \dfrac{m}{2} \rfloor ^ {n - i - j}
$$

由二项式定理得 $\sum\limits_{i = 0} ^ {n - j} \dbinom{n - j}{i} \times \lceil \dfrac{m}{2} \rceil ^ {i} \times \lfloor \dfrac{m}{2} \rfloor ^ {n - i - j} = (\lceil \dfrac{m}{2} \rceil + \lfloor \dfrac{m}{2} \rfloor) ^ {n - j} = m ^ {n - j}$，那么答案为
$$
\sum_{j = 0} ^ {k} \begin{Bmatrix}k \\ j\end{Bmatrix} \times n ^ {\underline j} \times \lceil \dfrac{m}{2} \rceil ^ {j} \times m ^ {n - j}
$$
所以只需要预处理 $2 \times 10 ^ 3$ 以内的第二类斯特林数，再 $O(k)$ 维护下降幂即可。

## 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int mod = 998244353, N = 2e3;
int norm(int x) {
    if (x < 0) {
        x += mod;
    }
    if (x >= mod) {
        x -= mod;
    }
    return x;
}
template<class T>
T power(T a, int b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
struct Z {
    int x;
    Z(int x = 0) : x(norm(x)) {}
    int val() const {
        return x;
    }
    Z operator-() const {
        return Z(norm(mod - x));
    }
    Z inv() const {
        assert(x != 0);
        return power(*this, mod - 2);
    }
    Z &operator*=(const Z &rhs) {
        x = i64(x) * rhs.x % mod;
        return *this;
    }
    Z &operator+=(const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator-=(const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator/=(const Z &rhs) {
        return *this *= rhs.inv();
    }
    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend istream &operator>>(istream &is, Z &a) {
        i64 v;
        is >> v;
        a = Z(v);
        return is;
    }
    friend ostream &operator<<(ostream &os, const Z &a) {
        return os << a.val();
    }
};
vector<vector<Z>> stirling(N + 1, vector<Z>(N + 1));
void init() {
    stirling[0][0] = 1;
    for (int i = 1; i <= N; i ++) {
        for (int j = 1; j <= i; j ++) {
            stirling[i][j] = stirling[i - 1][j - 1] + j * stirling[i - 1][j];
        }
    }
}
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    Z res, sum = 1;
    for (int i = 0, cnt = n; i <= k; i ++, cnt --) {
        res += stirling[k][i] * power(Z((m + 1) / 2), i) * power(Z(m), n - i) * sum;
        sum *= cnt;
    }
    cout << res << "\n";
}
signed main() {
    init();
    cin.tie(0) -> sync_with_stdio(0);
    int T;
    cin >> T;
    while (T --) {
        solve();
    }
}
```

---

## 作者：_jimmywang_ (赞：2)

纪念第一个场切的 EDU 的 F。

### 题意：

有 $n$ 个不同的盒子，每个盒子里有 $m$ 个编号分别为 $1\dots m$ 的小球。现在要从每个盒子中恰好取出 $1$ 个球，计算每种取法中，编号是奇数的小球个数的 $k$ 次方和，答案对 $998244353$ 取模。

首先，我们设 $a$ 为 $1 \dots m$ 中奇数的个数，$b$ 为 $1 \dots m$ 中偶数的个数

显然，对于编号是奇数的小球个数相等的取法，其贡献是等价的。

考虑生成函数，设 $F=(ax+b)^{n}$，则我们要求的答案就是：

$$\sum_{i=1}^{n} [x^i] F \times i^k$$

因为由二项式定理，有：

$$F=\sum_{i=1}^{n} \binom{n}{i}a^{i}b^{n-i}x^i $$

所以 $[x^i]F=\binom{n}{i}a^{i}b^{n-i}$。

于是得出：

$$ans=\sum_{i=1}^{n} \binom{n}{i}a^{i}b^{n-i} i^k$$

然后我们发现这个东西和 [CF932E Team Work](https://www.luogu.com.cn/problem/CF932E) 非常相似，于是我们仿照那题的套路来处理。


$$\begin{aligned}ans &=\sum_{i=1}^{n} \binom{n}{i}a^{i}b^{n-i} i^k \\ & = \sum_{i=1}^{n} \binom{n}{i}a^{i}b^{n-i} \sum_{j=1}^{k}\begin{Bmatrix} k \\ j \end{Bmatrix} i^{\underline{j}}\\ & = \sum_{i=1}^{n} \binom{n}{i}a^{i}b^{n-i} \sum_{j=1}^{k}\begin{Bmatrix} k \\ j \end{Bmatrix} \binom{i}{j} j! \end{aligned}$$

改变求和顺序：

$$\begin{aligned} & = \sum_{j=1}^{k}\begin{Bmatrix} k \\ j \end{Bmatrix}  j!\sum_{i=1}^{n} \binom{n}{i} \binom{i}{j} a^{i}b^{n-i} \\ & = \sum_{j=1}^{k}\begin{Bmatrix} k \\ j \end{Bmatrix}  j!\sum_{i=1}^{n} \binom{n}{i} \binom{i}{j}  a^{i}b^{n-i} \\ & = \sum_{j=1}^{k}\begin{Bmatrix} k \\ j \end{Bmatrix}  j!\sum_{i=1}^{n} \binom{n}{j} \binom{n-j}{i-j}  a^{i}b^{n-i} \\ & = \sum_{j=1}^{k}\begin{Bmatrix} k \\ j \end{Bmatrix}  \binom{n}{j} j!\sum_{i=1}^{n} \binom{n-j}{i-j}  a^{i}b^{n-i} \\& = \sum_{j=1}^{k}\begin{Bmatrix} k \\ j \end{Bmatrix} n^{\underline{j}} \sum_{i=1}^{n} \binom{n-j}{i-j}  a^{i}b^{n-i}  \end{aligned}$$

前面的循环已经可以求解了，现在考虑后半部分：

$$\begin{aligned} \sum_{i=1}^{n} \binom{n-j}{i-j}  a^{i}b^{n-i}  \end{aligned}$$

考虑到 $i < j$ 时 $ \binom{n-i}{i-j} =0$，不会产生贡献，于是可以重写为：

$$\begin{aligned} \sum_{i=j}^{n} \binom{n-j}{i-j}  a^{i}b^{n-i}  \end{aligned}$$

等价于：

$$\begin{aligned} &=\sum_{i=0}^{n-j} \binom{n-j}{i}  a^{i+j}b^{n-i-j}   \\ &= a^{j} \sum_{i=0}^{n-j} \binom{n-j}{i}  a^{i} b^{n-j-i}     \\ &= a^j (a+b)^{n-j}  \end{aligned} $$

于是我们最终的式子可以写成：

$$\sum_{j=1}^{k}\begin{Bmatrix} k \\ j \end{Bmatrix} n^{\underline{j}} a^j (a+b)^{n-j}  $$

第二类斯特林数可以用 $O(k^2)$ 的预处理递推出来，$n$ 的下降幂也可以 $O(k)$ 预处理。于是这道题就能用 $O(k^2+Tk)$ 的复杂度完成了。

---

## 作者：Presentation_Emitter (赞：2)

~~泻药，被 C 整自闭了~~

怎么放这种板题啊。。。

枚举选的奇数的数量 $i$，于是答案 $=\sum\limits_{i=0}^{n}\binom{n}{i}\lceil {m \over 2} \rceil^i\lfloor {m \over 2} \rfloor^{n-i}i^k$。接下来根据套路展开（$S_2$ 为第二类斯特林数）：

$$
\begin{aligned}
Ans&=\sum\limits_{i=0}^{n}\binom{n}{i}\lceil {m \over 2} \rceil^i\lfloor {m \over 2} \rfloor^{n-i}\sum\limits_{j=0}^k S_2(k,j)\binom{i}{j}j!\\
&=\sum\limits_{i=0}^{n}\binom{n}{i}\lceil {m \over 2} \rceil^{i-j}\lfloor {m \over 2} \rfloor^{n-i}\sum\limits_{j=0}^k S_2(k,j)\binom{i}{j}j!\lceil {m \over 2} \rceil^j\\
&=\sum\limits_{j=0}^k S_2(k,j)j!\lceil {m \over 2} \rceil^j \sum\limits_{i=j}^{n}\binom{n}{i}\binom{i}{j}\lceil {m \over 2} \rceil^{i-j}\lfloor {m \over 2} \rfloor^{n-i}\\
&=\sum\limits_{j=0}^k S_2(k,j)j!\lceil {m \over 2} \rceil^j \sum\limits_{i=j}^{n}\binom{n}{j}\binom{n-j}{i-j}\lceil {m \over 2} \rceil^{i-j}\lfloor {m \over 2} \rfloor^{n-i}\\
&=\sum\limits_{j=0}^k S_2(k,j)\binom{n}{j}j!\lceil {m \over 2} \rceil^j \sum\limits_{i=0}^{n-j}\binom{n-j}{i}\lceil {m \over 2} \rceil^{i}\lfloor {m \over 2} \rfloor^{n-j-i}\\
&=\sum\limits_{j=0}^k S_2(k,j)n^{\underline{j}}\lceil {m \over 2} \rceil^j m^{n-j}
\end{aligned}
$$

然后预处理第二类斯特林数并暴力求式子 $O(k^2+Tk)$ 即可。本题卡 $O(k^2+Tk \log P)$。

---

## 作者：老莽莽穿一切 (赞：2)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16595543.html)

---

[**CF link**](https://codeforces.com/contest/1716/problem/F)

[**你谷 link**](https://www.luogu.com.cn/problem/CF1716F)

给一种从组合角度的解法。

首先发现 $F^k$ 这个条件里的幂次并不是很好看，我们试图构造一种巧妙的结构，在统计这个结构时就可以直接达到统计 $F^k$ 的效果。

我们定义一个下标的有序 $k$ 元组 $(i_1,i_2,\cdots,i_k)$，定义对于 $k$ 元组 $T$ 的函数 $f(T)$ 表示下标在 $k$ 元组中出现过位置的取值都为奇数，其余位置**任意**，这个 $k$ 元组中元素可重，满足要求的取法方案数，此时我们发现答案就是 $\sum_Tf(T)$，因为对于任意一个有 $F$ 个位置取奇数的情况，我们的 $k$ 元组中每个元素能取 $F$ 个位置，方案数正好为 $F^k$。

那么问题就在于如何去枚举 $T$ 来快速求得 $f(T)$ 的和，首先要解决对于给定的 $T$ 如何计算 $f(T)$。

不难发现 $f(T)$ 对于 $T$ 中具体什么元素无关，只与 $T$ 中有**几种元素**有关，如果 $T$ 中有 $k'$ 种元素，则 $f(T)=\lceil\frac m2\rceil^{k'}m^{n-k'}$。

那么枚举 $T$ 的方式也就很明显了，我们只要枚举 $k'$，然后计算满足 $T$ 中不同元素种数为 $k'$ 的方案数，设方案数为 $g(k')$。

那么我们将式子写成如下形式：

$$
\sum_{i=1}^{\min\{k,n\}}g(i)\left\lceil\frac m2\right\rceil^{i} m^{n-i}
$$

那么问题再转化为如何求 $g(i)$，我们可以用 dp 的思想，设 $f_{i,j}$ 表示 $i$ 元组中有 $j$ 种不同的元素的方案数，可以得到 dp 转移方程：

$$
f_{i,j}=jf_{i-1,j}+(n-j+1)f_{i-1,j}
$$

解释一下转移方程，新的元素有两种选择，与之前的元素相同或者是一种新的元素，分别对应上面的两种转移。

这样我们就得到了一种对于每次询问 $\mathcal O\left(k^2\right)$ 的做法，基于上面的想法去优化它。

上面的递推式和 $n$ 相关，故每次得重新递推，如果能将式子转化成两部分，一部分与 $n$ 无关，预处理，另一个与 $n$ 有关的部分每次询问用更低的时间复杂度处理，就可以解决了。

那么我们先得从 $g(i)$ 的意义考虑，怎样去构造一个与 $n$ 无关的式子与一个部分组合得到 $g(i)$，首先与 $k$ 相关是没有关系的，因为 $k$ 的规模比较小，在 $\mathcal O\left(k^2\right)$ 范围内的预处理，在调用的时候我们也可以接受在 $\mathcal O\left(k\right)$ 范围内的枚举，我们基于这个条件去思考这个问题。

前面 $f_{i,j}$ 的定义是 $\mathcal O\left(k^2\right)$ 的，我们只要在定义中与 $n$ 无关就好了，我们发现现在的 $f_{i,j}$ 的定义中元素的值是 $[1,n]$，实际上种类数只有 $k$，我们可以考虑用类似离散化的思想，按照元素出现顺序重新标号，询问时在动态分配每个标号对应的元素。

重新定义 $f_{i,j}$ 表示 $i$ 元组中出现 $j$ 种元素，**满足对于每个出现的元素 $i$，$[1,i)$ 中的元素全部在它前面出现**，即元素种类无标号，则转移方程：

$$
f_{i,j}=jf_{i-1,j}+f_{i-1,j-1}
$$

不难发现这就是**斯特林子集数**，即第二类斯特林数 $i\brace j$。

就像前面说的，接下来我们要用斯特林子集数来得到前面我们的 $g(i)$，根据 $g(i)$ 表示有 $i$ 种不同元素的 $k$ 元组个数，那么对于 $i$ 种不同元素，其选取方式一共有 $k^\underline i$ 种，$i$ 种不同元素的 $k$ 元组的无标号方案数为 $f_{k,i}$，再结合上式，答案就是：

$$
\sum_{i=1}^{\min\{k,n\}}f_{k,i}k^\underline i\left\lceil\frac m2\right\rceil^{i} m^{n-i}
$$

这个式子其实可以直接根据第二类斯特林数的方幂转下降幂得到。

[代码](https://codeforces.com/contest/1716/submission/167523060)就是直接实现这个式子。

---

## 作者：Anoshag_Ruwan (赞：1)

典中典的 EGF 练手题 qwq.

这是个有标号集合计数问题，设 $q=\lfloor \frac{m+1}{2} \rfloor$ 即 $m$ 以内奇数个数，不难得出暴力式子 $ans=\sum\limits_{i=0}^n{n \choose i}q^i(m-q)^{n-i}$

使用 EGF,令 $\hat F(x)=\sum\limits_{i \geq 0}i^k\frac{(qx)^i}{i!}$，$\hat G(x)=\sum\limits_{i \geq 0}\frac{((m-q)x)^i}{i!}=e^{(m-q)i}$，所求即 $ans=n![x^n]\hat F(x)\hat G(x)$（对初学者的一个入门的理解：OGF 求的是凑满 $n$ 元钱的方案数，EGF 求的是涂满 $1 \times n$ 纸带的方案数，因为收钱时不会管你第几块钱用什么付，即无顺序）。

由于有个 $i^k$ 的系数，$\hat F(x)$ 没有封闭形式，如果 $k=0$，则能轻易求出 $n![x^n]\hat F(x)\hat G(x)=n![x^n]e^{mx}=m^n$（以上为废话），于是关键在于处理掉 $i^k$，回想与 $i^k$ 相关的式子和套路，不难想到**斯特林反演**：$n^k=\sum\limits_{i \geq 0}{n \choose i}{\begin{Bmatrix}k\\i\end{Bmatrix}}i!$（如果不知道，左转第二类斯特林数入门篇，或者看看某喜闻乐见的[幼儿园篮球题](https://www.luogu.com.cn/problem/P2791)）

于是：$\hat F(x)=(\sum\limits_{i=0}^n\frac{(qx)^i}{i!}(\sum\limits_{j \leq i}{i \choose j}{\begin{Bmatrix}k\\j\end{Bmatrix}}j!))$

$=\sum\limits_{j=0}^k{\begin{Bmatrix}k\\j\end{Bmatrix}}j!(\sum\limits_{i \geq j}{i \choose j}\frac{(qx)^i}{i!})=\sum\limits_{j=0}^k{\begin{Bmatrix}k\\j\end{Bmatrix}}(qx)^j(\sum\limits_{i \geq j}\frac{(qx)^{i-j}}{(i-j)!})$

$=\sum\limits_{j=0}^k{\begin{Bmatrix}k\\j\end{Bmatrix}}(qx)^j\times e^{qx}$

$n![x^n]\hat F(x)\hat G(x)=n![x^n]\sum\limits_{j=0}^k{\begin{Bmatrix}k\\j\end{Bmatrix}}(qx)^j\times e^{qx}\times e^{(m-q)x}$

$=n!\sum\limits_{j=0}^k{\begin{Bmatrix}k\\j\end{Bmatrix}}[x^j](qx)^j\times [x^{n-j}]e^{mx}=n!\sum\limits_{j=0}^k{\begin{Bmatrix}k\\j\end{Bmatrix}}q^j\frac{m^{n-j}}{(n-j)!}$

$=\sum\limits_{j=0}^k{\begin{Bmatrix}k\\j\end{Bmatrix}}q^jm^{n-j}n^{\underline j}$

预处理第二类斯特林数直接递推即可（反正 $O(k \log k$）做法在这没用），$O(k^2)$，处理每个询问时间复杂度 $O(kt)$，总复杂度 $O(kt+k^2)$

顺便推荐一道进阶版的 EGF 好题：[CTS2019珍珠](https://www.luogu.com.cn/problem/solution/P5401)

```cpp
#include<cstdio>
using namespace std;
long long s[2011][2011],p=998244353;
inline long long add(long long x,long long y){return x+y>=p?x+y-p:x+y;}
inline long long ksm(long long x,long long y){
	long long k=1,l=x;while(x<=1||y==1)return x;
	while(y){if(y&1)k=k*l%p;l=l*l%p,y>>=1;}
	return k;
}
inline long long rd(){
	long long i=0,j;char g=getchar();
	while(g>57||g<48)g=getchar();
	while(g>47&&g<58)i=(i<<3)+(i<<1)+g-48,g=getchar();
	return i;
}
int main()
{
	long long i,j,l,h,k,inv,m,n=2000,ans,t=rd(),q;
	for(i=s[0][0]=1;i<=n;i++)
		for(j=1;j<=i;j++)
			s[i][j]=add(s[i-1][j-1],s[i-1][j]*j%p);
	while(t--){
		n=rd(),m=rd(),k=rd();
		ans=0;q=m+1>>1;l=ksm(m,n);
		inv=ksm(m,p-2),l=l*inv%p;
		for(i=1,j=q,h=n;i<=k;i++)
			ans=add(ans,s[k][i]*h%p*j%p*l%p),\
			j=j*q%p,l=l*inv%p,h=h*(n-i)%p;
		printf("%lld\n",ans);
	}return 0;
}
```


---

## 作者：pvzelyyds (赞：1)

# Solution
考虑枚举奇数编号球的总数目 $i$，从 $n$ 个包中选择 $i$ 个方案数为 $C_n^i$，每个包中有 $\lfloor\frac{m+1}{2}\rfloor$ 个奇数球和 $\lfloor\frac{m}{2}\rfloor$ 个偶数球，那么容易得到 $ans = \sum_{i=0}^n i^kC_n^i\lfloor\frac{m+1}{2}\rfloor^i \lfloor\frac{m}{2}\rfloor^{n-i}$ 。

直接计算显然不可取，接下来考虑优化。

根据二项式定理可知 $(a+x)^n = \sum_{i=0}^n x^ia^{n-i}$ 。

对等式两边分别求导再同时乘 $x$ 可得 $nx(a+x)^{n-1}=\sum_{i=0}^n ix^ia^{n-i}$ 。显然经过 $k$ 次操作后等号右边将变为 $\sum_{i=0}^n i^kx^ia^{n-i}$，此时将 $x=\lfloor\frac{m+1}{2}\rfloor$ 及 $a=\lfloor\frac{m}{2}\rfloor$ 带入等式左边即可得到 $ans$ 。

接下来观察求导的过程：

$f_1(x)=nx(a+x)^{n-1}$

$f_2(x)=n(n-1)x^2(a+x)^{n-2}+nx(a+x)^{n-1}$

$f_3(x)=n(n-1)(n-2)x^3(a+x)^{n-3}+3n(n-1)x^2(a+x)^{n-2}+nx(a+x)^{n-1}$

$\cdots$

我们发现 $f_m(x)$ 总是可以表达为 $\sum_{i=1}^ma_in(n-1)(n-2)\cdots(n-i+1)x^i(a+x)^{n-i}$ 这样的形式，其中 $a_i$ 为待求系数且与输入无关，于是考虑预处理 $a_i$，下面求解 $a_i$ 的过程其实也是对于 $f_m(x)$ 形式的归纳论证。

令 $g(x)=a_in(n-1)(n-2)\cdots(n-i+1)x^i(a+x)^{n-i}$，那么 $xg'(x)=ia_in(n-1)\cdots(n-i+1)x^i(a+x)^{n-i}+a_in(n-1)\cdots(n-i)x^{i+1}(a+x)^{n-(i+1)}$。

这说明 $f_m(x)$ 的第 $i$ 项的求导结果会分别对 $f_{m+1}$ 的第 $i$ 项和第 $i+1$ 项产生 $ia_i$ 和 $a_i$ 的贡献，于是我们就可以用类似 $dp$ 的思路预处理出所有 $f_m(x)$ 的系数，查询时可以 $O(k)$ 计算出 $f_k(x)$ 的函数值，即为答案。

时间复杂度 $O(k^2+T(k+log\ p))$ 。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 2e3 + 10;
#define __cs() int T; cin >> T; while (T--)
ll n, m, k, dp[maxn][maxn];
ll qpow(ll a, int b, ll ans = 1) { for (; b; (a *= a) %= mod, b >>= 1)if (b & 1)(ans *= a) %= mod; return ans; }
void init() { 
    dp[1][1] = 1;
    for (int i = 1; i <= 2000; ++i) {
        for (int j = 1; j <= i; ++j) {
            (dp[i + 1][j + 1] += dp[i][j]) %= mod;
            (dp[i + 1][j] += j * dp[i][j]) %= mod;
        }
    }
}
void solve() {
    cin >> n >> m >> k;
    ll mul = 1, ans = 0, X = (m + 1) / 2, A = X + m / 2;
    ll pwX = X, pwA = qpow(A, n - 1), inv = qpow(A, mod - 2);
    for (int i = 1; i <= k; ++i) {
        if (n < i) break;
        (mul *= n - i + 1) %= mod;
        (ans += dp[k][i] * mul % mod * pwX % mod * pwA) %= mod;
        (pwX *= X) %= mod; (pwA *= inv) %= mod;
    }
    cout << ans << '\n';
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    init();
    __cs()solve();
    return 0;
}
```


---

## 作者：Gorenstein (赞：0)

大家都推得好麻烦。

令 $\lceil\frac{m}{2}\rceil=x,\lfloor\frac{m}{2}\rfloor=y$，根据题意，其答案为

$$\sum_{i=0}^{n}i^k\binom{n}{i}x^{i}y^{n-i}$$

而我们知道这两个恒等式（[证明见此](https://www.luogu.com.cn/paste/o8rgntg8)）：

$$
x^{n}\sum_{k=0}^n{n\brace k}x^{\underline k}
$$

$$
k^{\underline j}\binom{n}{k}=j!\binom{k}{j}\binom{n}{k}=j!\binom{n}{j}\binom{n-j}{k-j}=n^{\underline j}\binom{n-j}{k-j}
$$

那么作为一个熟练的 Stirling 数选手，我们能很快将式子化简完毕。

$$
\begin{aligned}
\sum_{i=0}^{n}i^k&\binom{n}{i}x^{i}y^{n-i}
\\&=\sum_{i=0}^n\sum_{j=0}^{k}{i\brace j}i^{\underline j}\binom{n}{i}x^{i}y^{n-i}\\
&=\sum_{j=0}^{k}{i\brace j}n^{\underline j}\sum_{i=0}^n\binom{n-j}{i-j}x^{i}y^{n-i}\\
&=\sum_{j=0}^{k}{i\brace j}n^{\underline j}\sum_{i=0}^{n-j}\binom{n-j}{i}x^{i+j}y^{n-i-j}\\
&=\sum_{j=0}^{k}{i\brace j}n^{\underline j}x^j(x+y)^{n-j}
\end{aligned}
$$

```cpp
ll Tst,n,m,K,X,dnp[N],s[N][N],ans;
void Pre(){
	s[0][0]=1,dnp[0]=1;
	for(ll i=1;i<N;i++)
		for(ll j=1;j<=i;j++)
			s[i][j]=(j*s[i-1][j]%mod+s[i-1][j-1])%mod;
}
void work(){
	n=read(),m=read(),K=read(),ans=0,X=m+1>>1;
	for(ll i=n,j=1,x=1;j<=K;i--,j++)x=x*i%mod,dnp[j]=x;
	for(ll i=0;i<=min(n,K);i++)
		ans=(ans+s[K][i]*dnp[i]%mod*Qpow(X,i)%mod*Qpow(m,n-i)%mod)%mod;
	printf("%lld\n",ans),ans=0;
}
```

---

## 作者：Un1quAIoid (赞：0)

**洛谷传送门：** [CF1716F Bags with Balls](https://www.luogu.com.cn/problem/CF1716F)

-----------------------

暴力推式子大法好

-----------------------

题目实际上就是让我们求：

$$
\sum_{i=0}^{n} i^k \binom{n}{i} \left( \left \lceil \frac{m}{2} \right \rceil \right)^i \left( \left \lfloor \frac{m}{2} \right \rfloor \right)^{n-i}
$$

即枚举奇数编号球的个数，计算对应的方案数。

式子中的 $i^k$ 很难搞，考虑将普通幂转为下降幂，因为下降幂与组合数相乘能把底数从求和变量换成常量，结果很好看：
$$
\begin{aligned}
x^k &= \sum_{i=0}^{k} \begin{Bmatrix} k\\i \end{Bmatrix}x^{\underline i}\\
\binom{n}{x}x^{\underline k} &= \binom{n-k}{x-k}n^{\underline k}
\end{aligned}
$$

剩下的过程就非常顺畅了，一步到位：

$$
\begin{aligned}
&\sum_{i=0}^{n} i^k \binom{n}{i} \left( \left \lceil \frac{m}{2} \right \rceil \right)^i \left( \left \lfloor \frac{m}{2} \right \rfloor \right)^{n-i}\\
= &\sum_{i=0}^n \binom{n}{i} \left( \left \lceil \frac{m}{2} \right \rceil \right)^i \left( \left \lfloor \frac{m}{2} \right \rfloor \right)^{n-i} \sum_{j=0}^k \begin{Bmatrix} k\\j \end{Bmatrix}i^{\underline j}\\
= &\sum_{i=0}^n \sum_{j=0}^k \begin{Bmatrix} k\\j \end{Bmatrix} \binom{n-j}{i-j} n^{\underline j} \left( \left \lceil \frac{m}{2} \right \rceil \right)^i \left( \left \lfloor \frac{m}{2} \right \rfloor \right)^{n-i}\\
= &\sum_{j=0}^k \begin{Bmatrix} k\\j \end{Bmatrix} n^{\underline j} \sum_{i=0}^n \binom{n-j}{n-i} \left( \left \lceil \frac{m}{2} \right \rceil \right)^i \left( \left \lfloor \frac{m}{2} \right \rfloor \right)^{n-i}\\
= &\sum_{j=0}^k \begin{Bmatrix} k\\j \end{Bmatrix} n^{\underline j} \sum_{i=0}^{n-j} \binom{n-j}{i} \left( \left \lceil \frac{m}{2} \right \rceil \right)^{n-i} \left( \left \lfloor \frac{m}{2} \right \rfloor \right)^{i}\\
= &\sum_{j=0}^k \begin{Bmatrix} k\\j \end{Bmatrix} n^{\underline j} \left( \left \lceil \frac{m}{2} \right \rceil \right)^{j}m^{n-j}\\
\end{aligned}
$$

最后一步将 $n-i$ 替换为 $i$ 并使用了二项式定理化简。现在我们就可以做到 $O(k^2)$ 预处理第二类斯特林数，$O(k)$ 查询了（注意不要写成 $O(k \log n)$ 查询，会T）。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int Mod = 998244353;
const int MAXN = 2005;

ll n, m, k;
ll S[MAXN][MAXN];

inline int qpow(int a, int b) {
    ll base = a, ans = 1;
    while (b) {
        if (b & 1) ans = ans * base % Mod;
        base = base * base % Mod;
        b >>= 1;
    }
    return ans;
}

void solve() {
    scanf("%d%d%d", &n, &m, &k);

    int ans = 0;
    ll a1 = 1, a2 = 1, a3 = qpow(m, n), inv = qpow(m, Mod - 2);
    for (int j = 1; j <= min(k, n); j++) {
        a1 = a1 * ((m + 1) / 2) % Mod;
        a2 = a2 * (n - j + 1) % Mod;
        a3 = a3 * inv % Mod;
        ans = (ans + S[k][j] * a1 % Mod * a2 % Mod * a3) % Mod;
    }
    printf("%d\n", ans);
}

int main() {
    S[0][0] = 1;
    for (int i = 1; i < MAXN; i++)
        for (int j = 1; j <= i; j++)
            S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j]) % Mod;
    
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：0)

**纯大力推式子题，而且板 $+$ 原。**

## 一、题意

$n$ 个**不同**的袋子，每个袋子有 $m$ 个编号从 $1$ 到 $m$ 的小球。从每个袋子里选出 $1$ 个球一共 $n$ 个球，记编号为奇数的球数为 $F$，求所有情况下 $F^k$ 之和。 

$n,m\leq 998244352, k \leq 2000$。


## 二、前置知识

第二类斯特林数的递推式和组合意义，二项式定理，微积分基础。


## 三、狂暴推式子

记 $t=\frac{m+1}{2}$，即奇数的个数。 

朴素的式子：

$$
Ans=\sum_{i=0}^ni^k \begin{pmatrix}n\\i\end{pmatrix} t^i (m-t)^{n-i}
$$ 

首先展开 $i^k$。

考虑 $i^k$ 的组合意义：$k$ 个不同的球放入 $i$ 个不同的可空盒子的方案数。枚举用到了几个盒子，我们就可以把 $i^k$ 拆出来了： 

$$i^k=\sum_{y=0}^{k}\begin{pmatrix}i\\y\end{pmatrix} \begin{Bmatrix}k\\y\end{Bmatrix}y!$$ 

带入 $Ans$ 的计算式。

$$Ans=\sum_{i=0}^n\begin{pmatrix}n\\i\end{pmatrix} t^i (m-t)^{n-i}\sum_{y=0}^k\begin{pmatrix}i\\y\end{pmatrix} \begin{Bmatrix}k\\y\end{Bmatrix}y!=\sum_{y=0}^ky!\begin{Bmatrix}k\\y\end{Bmatrix}\sum_{i=y}^n\begin{pmatrix}n\\i\end{pmatrix}\begin{pmatrix}i\\y\end{pmatrix}t^i(m-t)^{n-i}=(m-t)^n\sum_{y=0}^ky!\begin{Bmatrix}k\\y\end{Bmatrix}\sum_{i=y}^n\begin{pmatrix}n\\i\end{pmatrix}\begin{pmatrix}i\\y\end{pmatrix}(\frac{t}{m-t})^i$$

所以现在的问题是怎么快点计算第二个求和号后面的东西。

考虑二项式定理，假设要求这个东西。

$$(x+1)^p=\sum_{u=0}^p\begin{pmatrix}p\\u\end{pmatrix}x^u$$

两边对 $x$ 求 $k$ 阶导数。

$$p(p-1)...(p-y+1)(x+1)^{p-y}=\sum_{u=y}^pu(u-1)...(u-y+1)x^{u-y}{p\choose u}$$

两边除以 $y!$：

$$\begin{pmatrix}p\\y\end{pmatrix}(x+1)^{p-y}=\sum_{u=y}^p\begin{pmatrix}u\\y\end{pmatrix}x^{u-y}\begin{pmatrix}p\\u\end{pmatrix}$$

因此，

$$\sum_{i=y}^n\begin{pmatrix}i\\y\end{pmatrix}\begin{pmatrix}n\\i\end{pmatrix}(\frac{t}{m-t})^i=(\frac{t}{m-t})^y(\frac{t}{m-t}+1)^{n-y}\begin{pmatrix}n\\y\end{pmatrix}$$

再代回 $Ans$ 的计算式：

$$Ans=(m-t)^n\sum_{y=0}^ky!\begin{Bmatrix}k\\y\end{Bmatrix}\begin{pmatrix}n\\y\end{pmatrix}(\frac{t}{m-t})^y(\frac{t}{m-t}+1)^{n-y}$$

这样的话就可以在 $O(k+\log(mod))$ 的时间复杂度计算出答案了。注意对两种情况进行特判：$n<k$ 和 $m=1$。都是 trivial 的。


---

