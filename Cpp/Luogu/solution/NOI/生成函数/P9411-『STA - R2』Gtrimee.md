# 『STA - R2』Gtrimee

## 题目描述

令满足如下条件的儿子有序的无标号有根树数量为 $w_k(n)$：
- 点数 $n_0\in[1,n]$。
- 所有深度为 $k$ 的点都不是叶子。

给定固定正整数 $k$，多次给定正整数 $n$，求 $w_k(n)\bmod 998244353$ 的值。

此处一个点的深度定义为它到根的唯一简单路径的长度，比如根的深度就是 $0$。

## 说明/提示

### 样例解释
样例 1 解释：

$k=2$，树上恰有 $5$ 个点时的所有方案：

![](https://cdn.luogu.com.cn/upload/image_hosting/pwgn6z92.png)
### 数据范围
**本题采用捆绑测试。**
$$
\newcommand{\arraystretch}{1.5}
\begin{array}{c|c|c|c}\hline\hline
\textbf{Subtask} & \bm{n}\le & \textbf{分值} & \textbf{特殊性质}\\\hline
\textsf{1} & 5 & 5  \\\hline
\textsf{2} & 10^2 & 20\\\hline
\textsf{3} & 2\times10^5 & 35 & k=1\\\hline
\textsf{4} & 2\times10^5 & 40\\\hline\hline
\end{array}
$$

对于全部数据，$1\le n,q,k\le 2\times10^5$。

## 样例 #1

### 输入

```
0
5 2
1
2
3
4
5```

### 输出

```
1
2
3
5
10```

## 样例 #2

### 输入

```
0
5 200
1
10
100
1000
10000```

### 输出

```
1
6918
721868074
972431902
815282281```

# 题解

## 作者：jijidawang (赞：5)

令 $n$ 个点的满足题意的树的数量 $f_k(n)$ 的 OGF 为 $F_k(z)$，那么枚举根的最左侧子树大小即可得到递推：
$$f_k(n)=\sum_{i=0}^{n-1}f_{k-1}(i)f_k(n-1-i)$$
翻译为 OGF 就是卷积形式 $F_k(z)=1+zF_{k-1}(z)F_k(z)$，即
$$F_k(z)=\dfrac1{1-zF_{k-1}(z)}$$
通过类似的方法可以推得 $F_1(z)$ 的表达式，于是只需要解出递推 .

令 $p=998244353$ . 定义线性分式变换为函数 $f:\mathbb F_p[[z]]\to\mathbb F_p[[z]]$，满足存在 $a,b,c,d\in \mathbb F_p[[z]]$，使得
$$f(x)=\dfrac{ax+b}{cx+d}$$

那么可以发现线性分式变换对于复合是封闭的，具体可以验证：
$$\dfrac{a_0\frac{a_1x+b_1}{c_1x+d_1}+b_0}{c_0\frac{a_1x+b_1}{c_1x+d_1}+d_0}=\dfrac{(a_0a_1+b_0c_1)x+(a_0b_1+b_0d_1)}{(c_0a_1+d_0c_1)x+(c_0b_1+d_0d_1)}$$

观察递推，看成线性分式变换的形式就是 $a=0,\,b=1,\,c=1,\ d=-z$ . 令 $F_k(z)=\dfrac{a_kF_1(z)+b_k}{c_kF_1(z)+d_k}$，则可以简单写出系数的递推：
$$\begin{aligned}&a_i=c_{i-1}\\&b_i=d_{i-1}\\&c_i=c_{i-1}-z\cdot a_{i-1}\\&d_i=b_{i-1}-z\cdot d_{i-1}\end{aligned}$$
那么不难发现的是这个递推本质上可以看做二阶常系数齐次线性递推，于是大力解出 $a,b,c,d$ 后代入即可 .

于是可以通过多项式基本操作在 $\Theta(n\log n)$ 的时间复杂度内求出 $F_k(z)$ 的前 $n$ 项系数 . 前缀和后即为答案 . 时间复杂度为 $\Theta(n\log n+q)$，可以通过 . 如果实现优秀是可以跑到 500ms 以内的 .

---

## 作者：xiaoyaowudi (赞：4)

设儿子有顺序的无标号有根树生成函数为 $F$。

设第 $k$ 层不能有叶子的生成函数为 $G_k\left(z\right)$。

那么 $G_0\left(z\right)=F-z$，因为除非是只有根这 $1$ 个点，都满足条件。

则 $G_{i}=\dfrac{z}{1-G_{i-1}}$。不妨把 $G_k$（$k\ge 1$）表示成 $\dfrac{f_{k-1}z}{f_{k}}$ 的有理分式的形式。那么有：

$$
f_0=1,f_1=1+z-F,f_i=f_{i-1}-zf_{i-2}
$$

设特征根方程的一个单位根 $\dfrac{1-\sqrt{1-4z}}{2z}=w$，即二叉树的生成函数。那么 $F=wz$，且有：

$$
\begin{aligned}
A&=\dfrac{z}{2wz-1}\\
B&=\dfrac{2wz-z-1}{2wz-1}\\
f_i&=A\left(wz\right)^i+\dfrac{B}{w^i}
\end{aligned}
$$

$$
\begin{aligned}
G_k\left(z\right)&=z\cdot \dfrac{A\times \left(wz\right)^{k-1}+B\times w^{-k+1}}{A\times \left(wz\right)^{k}+B\times w^{-k}}\\&=z\cdot\dfrac{w^{k-1}z^k+\left(2wz-z-1\right)w^{1-k}}{w^kz^{k+1}+\left(2wz-z-1\right)w^{-k}}\\&=z\times \dfrac{w^{2k-1}z^k+2w^2z-wz-w}{w^{2k}z^{k+1}+2wz-z-1}
\end{aligned}
$$

其中 $\displaystyle\left[z^n\right]w^k=\dfrac{k}{n+k}\binom{2n+k-1}{n}$，可由组合意义或拉格朗日反演得到。于是一遍求逆即可解决该问题。

```cpp
constexpr int N(1e6+10),p(998244353),_2((p+1)/2);
int fp(int a,int b){int ans(1),off(a);while(b){if(b&1) ans=1ll*ans*off%p;off=1ll*off*off%p;b>>=1;}return ans;}
int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	static int fac[N],ifac[N],inv[N];
	fac[0]=1;for(int i(1);i<N;++i) fac[i]=1ll*fac[i-1]*i%p;ifac[N-1]=fp(fac[N-1],p-2);
	for(int i(N-1);i;--i) ifac[i-1]=1ll*ifac[i]*i%p,inv[i]=1ll*ifac[i]*fac[i-1]%p;
	auto binom=[](int a,int b)->int{return 1ll*fac[a]*ifac[b]%p*ifac[a-b]%p;};
	int n(1);int id,k,q;std::cin>>id>>q>>k;
	std::vector<int> ns(q);for(int &v:ns) std::cin>>v,n=std::max(n,v);
	init_poly_weights(n);poly U(n),D(n);D[0]=p-1;U[0]=p-1;
	for(int i(1);i<n;++i)
	{
		{
			long long tot(0);
			if(i>=k) tot+=1ll*(2*k-1)*inv[i+k-1]%p*binom(i*2-2,i-k);
			tot+=2ll*2*inv[i-1+2]*binom(i*2-2+2-1,i-1);
			tot+=1ll*(p-inv[i])*binom(i*2-2+1-1,i-1);
			tot+=1ll*(p-inv[i+1])*binom(i*2,i);
			U[i]=tot%p;
		}
		{
			long long tot((i==1)?p-1:0);
			if(i>=k+1) tot+=1ll*(2*k)*inv[i+k-1]%p*binom(i*2-3,i-k-1);
			tot+=2ll*inv[i]*binom(i*2-2+1-1,i-1);
			D[i]=tot%p;
		}
	}
	poly A=poly_inv(D)*U;
	static int ans[N];
	for(int i(1);i<=n;++i) ans[i]=(ans[i-1]+A[i-1])%p;
	for(int v:ns) std::cout<<ans[v]<<"\n";
	return 0;
}
```

---

## 作者：zhouyuhang (赞：2)

一个不用动脑子的做法。

记 $F_k(z)$ 为一行的生成函数，易得 $F_k(z) = \frac {z} {1 - F_{k - 1}(z)}$。而通过左儿子右兄弟表示法跟二叉树建立双射，有 $F_0(z) = \frac {1 - \sqrt {1 - 4z}} {2} - z$。

将 $F_k(z)$ 写作 $\frac {P_k(z)} {Q_k(z)}$ 的形式，有

$$
\left\{ 
\begin{aligned}
& P_k(z) = z Q_{k - 1}(z) \\
& Q_k(z) = Q_{k - 1}(z) - P_{k - 1}(z) 
\end{aligned}
\right.
$$

写成矩阵形式做快速幂即可。由 $T(n) = T(n / 2) + O(n \log n)$ 解得 $T(n) = O(n \log n)$，常数很大但可以通过。

小时候还是太笨了。

---

## 作者：Anoshag_Ruwan (赞：1)

一道少见的连分数相关计数题。

对于节点无标号、而儿子有标号这类树，显然需要用 OGF 处理。本题核心思路是，一棵树无深度为 $k(k\ge1)$ 叶节点，充要条件是所有子树均为无深度为 $k-1$ 叶节点的树。首先设无深度为 $k$ 叶节点树的生成函数为 $f_k(x)$，$n$ 次项表示 $n$ 个节点（含根）时的方案，则递推式为 $f_k(x)=\frac{x}{1-f_{k-1}(x)}$。

因此 $f_{k}(x)$ 可表示为连分数形式即 $f_k(x)=\frac{x}{1-\frac{x}{1-...}}$，所有树均不存在深度为 $+\infty$ 的叶节点，因此该式的不动点 $f_n(x)$ 满足 $f_n(x)=\frac{1-\sqrt{1-4x}}{2}$ 即卡特兰数 $xC(x)$ 对应无叶节点限制时的答案，这与经典结论是一致的，同时也有了递推初始条件 $f_0(x)=x(C(x)-1)$，只需将只有单节点树去掉就行。

然后处理这个连分数，不妨设 $f_k(x)=\frac{a}{b}$，其中 $a,b$ 均为关于 $x$ 的多项式，则有 $f_{k+1}(x)=\frac{bx}{b-a}$，这一递推也就是乘上二阶矩阵 $\begin{bmatrix}0\;\;x\\-1\;\;1\end{bmatrix}$ 的过程。而二阶矩阵就是变形杨辉三角的应用场景了。

想象一个旋转 $45\degree$ 的杨辉三角，其满足 $f_{n,m}=\tbinom{\frac{n+m}{2}}{\frac{n-m}{2}}$，则对于如上的矩阵，其 $m$ 次方将对应该三角某一行的某种形式，在这里令 $\begin{bmatrix}0\;\;x\\-1\;\;1\end{bmatrix}^m=\begin{bmatrix}v_1(x)\;\;v_2(x)\\v_3(x)\;\;v_4(x)\end{bmatrix},g_m(x)=\sum\limits_{k \ge 0}\tbinom{m-k}{k}(-1)^kx^k$，则有 $v_4(x)=g_m(x),v_3(x)=-g_{m-1}(x),v_2(x)=-xv_3(x),v_1(x)=-xg_{m-2}(x)[m \ge 2]$，就可以使用简单的多项式卷积与求逆在 $O(n\log n)$ 处理出答案，最后别忘了前缀和就可以了。


```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#define LL long long
using namespace std;
const int N=2.1e6,p=998244353,iv2=499122177;
LL frc[N],inv[N],r[N],w[N],k1,c[N],iv[N],g1[N],ct[N];
LL v1[N],v2[N],v3[N],v4[N];
inline LL add(LL x,LL y){return x+y>=p?x+y-p:x+y;}
inline LL minn(LL x,LL y){return x<y?x:y;} 
inline LL maxx(LL x,LL y){return x>y?x:y;}
inline LL cmb(LL x,LL y){return x<y||y<0?0:frc[x]*inv[y]%p*inv[x-y]%p;}
inline LL ksm(LL x,LL y){
    LL k=1,l=x;if(l>=p)l%=p;
    while(y){if(y&1)k=k*l%p;l=l*l%p,y>>=1;}
    return k;
}
inline LL rd(){
	LL i=0,j=1;char g=getchar();
	while(g>57||g<48){if(g=='-')j=-1;g=getchar();}
	while(g>47&&g<58)i=(i<<3)+(i<<1)+g-48,g=getchar();
	return i*j;
}
inline void bter(){
	for(int i=0;i<k1;i++)r[i]=(r[i>>1]>>1)|(i&1?k1>>1:0); }
inline void ntt(LL *f,bool m){
	LL i,j,k,l,h;
	for(i=0;i<k1;i++)
		if(i<r[i])swap(f[i],f[r[i]]);
	for(i=1;i<k1;i<<=1){
		l=ksm(m?3:332748118,(p-1)/(i<<1));
		for(j=w[0]=1;j<i;j++)w[j]=w[j-1]*l%p;
		for(j=0;j<k1;j+=i<<1)for(h=j;h<j+i;h++)
			k=w[h-j]*f[h+i]%p,f[h+i]=add(f[h],p-k),f[h]=add(f[h],k);
	}if(!m)for(i=0,j=ksm(k1,p-2);i<k1;i++)
		f[i]=f[i]*j%p;
}
inline void dxsinv(LL k,LL *f,LL *g){
	if(k==1){g[0]=ksm(f[0],p-2);return;}
	dxsinv(k+1>>1,f,g);int i,j;
	for(k1=1;k1<k<<1;k1<<=1);
	for(i=(k+1>>1);i<k1;i++)g[i]=0;
	for(i=0;i<k;i++)c[i]=f[i];for(i=k;i<k1;i++)c[i]=0;
	bter();ntt(c,1);ntt(g,1);
	for(i=0;i<k1;i++)g[i]=g[i]*add(2,p-c[i]*g[i]%p)%p;ntt(g,0);
}
int main()
{
	LL i,j,k=rd(),n=2e5,t=rd(),m=rd();
	for(i=frc[0]=1;i<=n<<1;i++)frc[i]=frc[i-1]*i%p;
	for(i--,inv[i]=ksm(frc[i],p-2);i;i--)inv[i-1]=inv[i]*i%p,iv[i]=inv[i]*frc[i-1]%p;
	for(i=1;i<n;i++)ct[i+1]=cmb(i<<1,i)*iv[i+1]%p;
	for(k1=1;k1<=n+m;k1<<=1);bter();
	for(i=0,j=1;i<=m>>1;i++,j=p-j)
		v1[i]=cmb(m-i,i)*j%p,v3[i+1]=cmb(m-i-1,i)*j%p,v2[i]=p-v3[i+1],v4[i+1]=p-cmb(m-i-2,i)*j%p;
	ntt(ct,1);ntt(v2,1);ntt(v4,1);
	for(i=0;i<k1;i++)v2[i]=v2[i]*ct[i]%p,v4[i]=v4[i]*ct[i]%p;
	ntt(v2,0);ntt(v4,0);
	for(i=0;i<=n;i++)v1[i]=add(v2[i],v1[i]),v3[i]=add(v4[i],v3[i]);
	dxsinv(n+1,v1,g1);
	for(i=n+1;i<k1;i++)g1[i]=0;ntt(g1,1);ntt(v3,1);
	for(i=0;i<k1;i++)g1[i]=g1[i]*v3[i]%p;ntt(g1,0);
	for(i=1;i<=n;i++)g1[i]=add(g1[i],g1[i-1]); 
	while(t--){
		k=rd();printf("%lld\n",g1[k]);
	}return 0;
} 
```

---

