# Flags

## 题目描述

When Igor K. was a freshman, his professor strictly urged him, as well as all other freshmen, to solve programming Olympiads. One day a problem called "Flags" from a website called Timmy's Online Judge caught his attention. In the problem one had to find the number of three-colored flags that would satisfy the condition... actually, it doesn't matter. Igor K. quickly found the formula and got the so passionately desired Accepted.

However, the professor wasn't very much impressed. He decided that the problem represented on Timmy's Online Judge was very dull and simple: it only had three possible colors of flag stripes and only two limitations. He suggested a complicated task to Igor K. and the fellow failed to solve it. Of course, we won't tell anybody that the professor couldn't solve it as well.

And how about you? Can you solve the problem?

The flags consist of one or several parallel stripes of similar width. The stripes can be one of the following colors: white, black, red or yellow. You should find the number of different flags with the number of stripes from $ L $ to $ R $ , if:

- a flag cannot have adjacent stripes of one color;
- a flag cannot have adjacent white and yellow stripes;
- a flag cannot have adjacent red and black stripes;
- a flag cannot have the combination of black, white and red stripes following one after another in this or reverse order;
- symmetrical flags (as, for example, a WB and a BW flag, where W and B stand for the white and black colors) are considered the same.

## 说明/提示

In the first test the following flags exist (they are listed in the lexicographical order, the letters B, R, W, Y stand for Black, Red, White and Yellow correspondingly):

3 stripes: BWB, BYB, BYR, RWR, RYR, WBW, WBY, WRW, WRY, YBY, YRY (overall 11 flags).

4 stripes: BWBW, BWBY, BYBW, BYBY, BYRW, BYRY, RWRW, RWRY, RYBW, RYBY, RYRW, RYRY (12 flags).

That's why the answer to test 1 is equal to $ 11+12=23 $ .

## 样例 #1

### 输入

```
3 4
```

### 输出

```
23```

## 样例 #2

### 输入

```
5 6
```

### 输出

```
64```

# 题解

## 作者：Twig_K (赞：5)

**题意**

问只由 R、B、W、Y 组成的长度介于 $[L,R]$ 且满足以下条件的字符串数量。
- 相邻两个字符不同。W 和 Y 不能相邻，R 和 B 不能相邻（**相邻两个字母的限制**）。
- 不能出现连续三个字符是 B、W、R 的一个排列（**连续三个字母的限制**）。
- 两个字符串互为反序视做同一个（**反序限制**）。


**算法：矩阵快速幂优化 dp**

[有一点点相似，也是矩阵优化对字符串的 dp](https://www.luogu.com.cn/problem/CF107D)

------------
**Part 1：朴素 dp**（可以跳过）

先不管反序限制。设 $f_{i,y,z}$ 表示当前字符串长度为 $i$，倒数第二位为字母 $y$，最后一位字母为 $z$ 的方案数（$i \geq 2$）。

转移：$f_{i,y,z}=\sum f_{i-1,x,y}$，转移中的 $x,y,z$ 应分别满足相邻两个字母的限制和连续三个字母的限制。

那么长度**不超过** $n$ 的方案数为 $4+\sum_{i=2}^n f_{i,x,y}$，其中 $x,y$ 应满足相邻两个字母的限制。加 $4$ 是为了算上长度为 $1$ 的串（不过不重要）。

现在加入反序的限制。如果用刚才的算法，对于非回文串会计数两次，对于回文串恰好会计数一次。因此，如果 $g_i=\sum f_{i,x,y}$（即长度为 $i$ 的串，不考虑反序限制的方案数），那么长度为 $i$ 的回文串的方案数就为 $g_{ \lceil \frac{i}{2} \rceil }$（长度除以 $2$，另外半边对称）。

因此，对于长度 $i$，满足反序限制的方案数为 $\frac{g_i+g_{ \lceil \frac{i}{2} \rceil }}{2}$。

设前缀和 $h_i=\sum_{j=1}^i g_j$ 那么长度**不超过 $n$ 且满足反序限制的**的方案数 $ans_n=\frac{h_i+h_{ \lceil \frac{i}{2} \rceil }}{2}$。

最终所求答案即为 $ans_R-ans_{L-1}$。

------------

**Part 2：矩阵快速幂优化**

改进求 $f$ 数组的过程，矩阵快速幂的转移和 $f$ 数组的转移本质是一样的，且都不考虑反序限制。

刚才记录的状态是 $f_{i,x,y}$，如果将二元组 $(x,y)$ 映射到编号，那么**合法的**二元组共 $8$ 个（具体见第二份代码）。

我们只需要得知哪些二元组之间可以转移，就可以用 $8$ 行 $8$ 列的矩阵快速转移。不过还要求前缀和，所以矩阵是 $9$ 行 $9$ 列。

设 $f_{i,id}$ 为以编号 $id$ 的二元组结尾，长度为 $i$ 的方案数，$w_i$ 为长度**不超过** $i$ 的方案数（即 $f$ 的前缀和）。

转移如下（这里实现的是左乘转移矩阵，二元组的编号以及矩阵下标从 $0$ 开始）：

$$
\begin{pmatrix}
a_{00} & a_{01} & \cdots & a_{07} & 0\\
a_{10} & a_{11} & \cdots & a_{17} & 0\\
\vdots & \vdots & \ddots & \vdots & \vdots\\
a_{70} & a_{71} & \cdots & a_{77} & 0\\
\sum a_{j0} & \sum a_{j1} & \cdots & \sum a_{j7} & 1
\end{pmatrix}
\begin{pmatrix}
f_{i-1,0} \\
f_{i-1,1} \\
\vdots \\
f_{i-1,7}\\
w_{i-1}
\end{pmatrix}
=
\begin{pmatrix}
f_{i,0} \\
f_{i,1} \\
\vdots \\
f_{i,7}\\
w_{i}
\end{pmatrix}
$$

其中 $w_i=w_{i-1}+\sum f_{i,j}$，由此得到转移矩阵的最后一行。$a_{ij} \in \{0,1\} $ 且 $a_{ij}$ 等于 $1$ 就表示**二元组 $j$ 可以转移到二元组 $i$**。

长度**不超过 $n$ 且满足反序限制的**的方案数 $ans_n=\frac{w_i+w_{ \lceil \frac{i}{2} \rceil }}{2}$，最终答案为 $ans_R-ans_{L-1}$。

-------------------

构造转移矩阵的代码：
```cpp
#include<bits/stdc++.h>
#define For(i,il,ir) for(register int i=(il);i<=(ir);++i)
using namespace std;
int a[13][13];
string tmp[13]={"RW","RY","BW","BY","WR","WB","YR","YB"};
namespace O_O{
	int id(string s){ For(i,0,7) if(s==tmp[i]) return i; }
	signed my_main()
	{
		For(i,0,7) For(j,0,7) if(i!=j&&tmp[i][1]==tmp[j][0]){
			bool f1=(tmp[i][0]=='B'||tmp[i][1]=='B'||tmp[j][1]=='B');
			bool f2=(tmp[i][0]=='W'||tmp[i][1]=='W'||tmp[j][1]=='W');
			bool f3=(tmp[i][0]=='R'||tmp[i][1]=='R'||tmp[j][1]=='R');
			if(f1&&f2&&f3) continue;
			a[j][i]=1,a[8][i]++;
		}
		a[8][8]=1;
		For(i,0,8){
			printf("{");
			For(j,0,8) printf("%d,",a[i][j]);
			printf("},\n");
		}
		return 0;
	}
}
signed main(){ return O_O::my_main(); }
```

AC 代码：
```cpp
#include<bits/stdc++.h>
#define For(i,il,ir) for(register int i=(il);i<=(ir);++i)
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
const ll inv2=500000004;
const int M[10][11]={
	{0,0,0,0,1,0,1,0,0},
	{0,0,0,0,1,0,1,0,0},
	{0,0,0,0,0,1,0,1,0},
	{0,0,0,0,0,1,0,1,0},
	{1,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0},
	{0,1,0,1,0,0,0,0,0},
	{0,1,0,1,0,0,0,0,0},
	{1,2,1,2,2,2,2,2,1},
};
namespace O_O{
	struct Mat{
		ll a[10][10];
		Mat(){ memset(a,0,sizeof(a)); }
		Mat operator * (Mat rc)const{
			Mat res;
			For(i,0,8) For(j,0,8) For(k,0,8) res.a[i][j]=(res.a[i][j]+a[i][k]*rc.a[k][j]%mod)%mod;
			return res;
		}
	}A,Tr;
	void qp(Mat &res,Mat x,int base){
		while(base){
			if(base&1) res=x*res;
			x=x*x;base>>=1;
		}
	}
	ll cal(int x){
		if(x==0) return 0;
		if(x==1) return 4;
		For(i,0,7) A.a[i][0]=1ll; A.a[8][0]=12ll;
		For(i,0,8) For(j,0,8) Tr.a[i][j]=(ll)M[i][j];
		qp(A,Tr,x-2);
		return A.a[8][0];
	}
	signed my_main()
	{
		int L,R;scanf("%d%d",&L,&R);
		ll tmp1=(cal(L-1)+cal(L/2))%mod*inv2%mod;
		ll tmp2=(cal(R)+cal((R+1)/2))%mod*inv2%mod;
		ll ans=(tmp2-tmp1+mod)%mod;
		printf("%lld\n",ans);
		return 0;
	}
}
signed main(){ return O_O::my_main(); }
```

---

## 作者：QwQ蒟蒻wjr (赞：2)

[我的blog](https://www.cnblogs.com/wangjunrui/p/12624553.html)

> > 题目链接：[CF93D Flags](https://codeforces.com/problemset/problem/93/D)
> >
> > 洛谷翻译：[CF93D Flags](https://www.luogu.com.cn/problem/CF93D)

$$preface$$

~~看到这道题没人写题解我就来水一篇吧~~

$$solution$$

我们先不考虑条件 $4$ 。

设满足条件 $1,2,3$ 时长度在 $[1,x]$ 之间的串的个数 $g(x)$

将 $x$ 按奇偶性划分，~~通过简单的计算~~可以求出

$$
g(x)=\left\{\begin{matrix}19\times3^{\frac{x}{2}-1}-7 & (x\equiv0\pmod2)
\\ 11\times3^{\frac{x-1}2}-7 & (x\equiv1\pmod2)

\end{matrix}\right.
$$

我们考虑一下加上条件 $4$ 第一反应为将答案除 $2$ ，但是这种处理时不正确的，一个回文串本来只会被计算一次却被除 $2$ 了，设满足题目所给的所有条件时长度在 $[1,x]$ 之间的串的个数 $f(x)$ 。

因为  $1,2,3$ 时长度在 $[1,x]$ 之间的回文串的个数 $g(\left \lceil \frac{x}{2} \right \rceil)$ 。

所以 $f(x)=\frac{g(x)+g(\left \lceil \frac{x}{2} \right \rceil)}{2}$

答案为 $f(r)-f(l-1)$


$$code$$
```cpp
#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int mod=1e9+7;
const int inv2=(mod+1)/2;
inline ll quickpow(ll a,int b)
{
	ll res=1;
	while(b)
	{
		if(b&1)
			res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
inline ll f(int x)
{
	if(x==0)
		return 0;
	if(x&1)
		return (11*quickpow(3,x/2)-7)%mod;
	else
		return (19*quickpow(3,x/2-1)-7)%mod;
}
inline ll g(int x)
{
	return (f(x)+f((x+1)>>1))*inv2%mod;
}
int n;
signed main()
{
	int l,r;
	read(l,r);
	printf("%lld\n",(g(r)-g(l-1)+mod)%mod);
	return 0;
}
```



---

## 作者：HYdroKomide (赞：1)

## 题意：
按照一定的规则对一个序列进行四色染色，求一个长度区间的不同染色种类数之和。

## 思路：
看到这样传统的转移方案和较大的数据范围，第一时间就可以想到矩阵快速幂加速。状态数很少，不妨尝试手推一下递推矩阵。

如果不熟悉线性代数中矩阵的概念，[这里](https://oi-wiki.org/math/linear-algebra/matrix/)有详细的介绍。

状态要存连续的两个字符，由于前两条条件的限制，合法的状态只有 RW、RY、BW、BY、WR、WB、YR、YB 八种。而合法的转移当且仅当此状态的第二个字符等于下一个状态的第一个字符，还要排除条件三的两个转移：BW $\rightarrow$ WR、RW $\rightarrow$ WB。

构造矩阵的方法也很简单。考虑当前向量 $\vec{P}$ 左乘转移矩阵，得到一个新的向量 $\vec{Q}$。矩阵第 $i$ 行 $j$ 列的元素 $a_{i,j}$ 即为 $\vec{P}_{j}$ 转移到 $\vec{Q}_{i}$ 的倍率。用公式表示就是：

$$\vec{Q}_i=\sum_{j=1}^n a_{i,j}\times \vec{P}_j$$

如此一来，我们可以将基本转移过程的 $8\times 8$ 矩阵手玩出来。

题目要求区间和，考虑再维护一个前缀和的变量，存在向量的末尾，矩阵也就需要扩大到 $9\times 9$ 的规模。在末尾的一行，考虑每次转移不同位置对总和带来的贡献即可。

最终得出的转移矩阵如下，这代表了序列长度为 $n$ 时的前缀和答案。注意当 $n\le1$ 时要特判，而最开始满足的是 $n=2$ 的情况，所以需要乘的起始向量就是 $n=2$ 时的前缀和答案。

$$
\begin{pmatrix}
a_1\\
a_2\\
a_3\\
a_4\\
a_5\\
a_6\\
a_7\\
a_8\\
s
\end{pmatrix}=
\begin{pmatrix}
0&0&0&0&1&0&1&0&0\\
0&0&0&0&1&0&1&0&0\\
0&0&0&0&0&1&0&1&0\\
0&0&0&0&0&1&0&1&0\\
1&0&0&0&0&0&0&0&0\\
0&0&1&0&0&0&0&0&0\\
0&1&0&1&0&0&0&0&0\\
0&1&0&1&0&0&0&0&0\\
1&2&1&2&2&2&2&2&1
\end{pmatrix}^{n-2}\cdot
\begin{pmatrix}
1\\
1\\
1\\
1\\
1\\
1\\
1\\
1\\
12
\end{pmatrix}
$$

最终，本次转移的答案就在 $s$ 的位置。

到了这里，还剩下最后一个需要解决的限制：两个互为反序的字符串视作一个。

我们发现，在使用上面方法进行转移的时候，对于正反序相同的染色方式（也就是回文串的情况），转移可以成功去重。但所有非回文串实际上都计算了两次。因此，去重后的答案应为 $\dfrac{s_n}{2}+\dfrac{p_n}{2}$，其中 $p_n$ 表示长度小于等于 $n$ 的回文答案数。

分奇数和偶数分类讨论，不难发现 $p_n$ 即为 $s_{\lceil \frac{n}{2}\rceil}$。于是 $n$ 长度的正确前缀和就是 $\dfrac{s_n+s_{\lceil\frac{n}{2}\rceil}}{2}$。两个前缀和相减就是答案。

## 程序如下：
```cpp
#include<cstdio>
using namespace std;
const int MOD=1e9+7,INV=5e8+4;//INV表示2在模数下的逆元
int l,r;
struct MATRIX{
	long long a[10][10]={
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,0,1,0,0},
		{0,0,0,0,0,1,0,1,0,0},
		{0,0,0,0,0,0,1,0,1,0},
		{0,0,0,0,0,0,1,0,1,0},
		{0,1,0,0,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,0,0,0},
		{0,0,1,0,1,0,0,0,0,0},
		{0,0,1,0,1,0,0,0,0,0},
		{0,1,2,1,2,2,2,2,2,1}
	};
};
MATRIX operator*(MATRIX x,MATRIX y){
	MATRIX ret;
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++){
			ret.a[i][j]=0;
			for(int k=1;k<=9;k++)ret.a[i][j]=(ret.a[i][j]+x.a[i][k]*y.a[k][j]%MOD)%MOD;
		}
	return ret;
}
MATRIX qpow(MATRIX ret,int p){
	MATRIX x;
	while(p){
		if(p&1)ret=x*ret;//注意一定要左乘原矩阵
		x=x*x;
		p>>=1;
	}
	return ret;
}
long long getAns(int x){
	if(x==0)return 0;
	if(x==1)return 4;
	MATRIX ans;
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
			ans.a[i][j]=0;
	for(int i=1;i<=8;i++)ans.a[i][1]=1;
	ans.a[9][1]=12;
	ans=qpow(ans,x-2);
	return ans.a[9][1];
}
int main(){
	scanf("%d%d",&l,&r);
	long long suml=(getAns(l-1)+getAns(l/2))%MOD*INV%MOD;
	long long sumr=(getAns(r)+getAns((r+1)/2))%MOD*INV%MOD;
	printf("%lld\n",(sumr-suml+MOD)%MOD);
	return 0;
}
```
## THE END

---

## 作者：Thomas0218 (赞：0)

## 题意
求满足以下要求的序列个数：
1. 长度在 $L$ 到 $R$ 之间，仅由白色、黑色、红色和黄色构成；
2. 相邻元素颜色不同；
3. 白黄不相邻；
4. 红黑不相邻；
5. 不存在连续的排列（黑，白，红）和排列（红，白，黑）；
6. 两个互为镜像的序列算作一个。

## 步骤一
最初步的分析可以发现，黑红颜色和白黄颜色必须交替出现，即第一位为白或者黄，那么第二位就只能是红或者黑。将 $L$ 到 $R$ 转化为 $1$ 到 $L-1$ 和 $1$ 到 $R$。

先不考虑要求6。显然可以递推，只需要记录最后两位的状态。

先考虑长度 $n$ 为偶数的序列，并且不考虑前缀和累加的问题。将其两位一分离，注意到这里白色和黄色不太一样，而红色和黑色等价。我们钦定这个序列的首位是黑/红（在不考虑要求6的情况下最后乘个2即可）。

因此设 $f_{i,0/1}$ 表示考虑了 $2i$ 位，第 $2i$ 位是否为白色的方案数。

若上面两位以白色结尾，那么这两位的黑/红状态是定的。那么 $f_{i,0}=2f_{i-1,0}+f_{i-1,1},f_{i,1}=2f_{i-1,0}+f_{i-1,1}$。

$0/1$ 这两维的数列是同构的。$f_{1,0}=2,f_{1,1}=2$，那么通项就是 $f_{n,0}=f_{n,1}=2\times3^{n-1}$。因此，在不考虑要求6的情况下 $n$ 为偶数的方案是 $8\times 3^{\frac{n}{2}-1}$，以下设偶数序列首位为黑/红的方案数 $f_n=4\times 3^{\frac{n}{2}-1}$。

## 步骤二
现在考虑 $n$ 为奇数的序列。尝试将其转化为偶数序列。奇数序列的结构只能是：

* (白/黄)，(红/黑)，$\dots$ ，(白/黄)
* (红/黑)，(白/黄)，$\dots$ ，(红/黑)

对于第一种情况，可以去掉第一个变为以(红/黑) 开头的偶数序列，方案数为 $2f_n$。

对于第二种情况，可以去掉最后一个变为(红/黑) 开头的偶数序列，而此时若：
* 最后一个是白，那么方案数为 $f_{i,1}$ 即 $\frac{f_n}{2}$。
* 最后一个是黄，那么方案数为 $f_n$。

所以奇数序列的方案数为 $2f_n+\frac{f_n}{2}+f_n=\frac{7}{2}f_n=14\times 3^{\frac{n-1}{2}-1}$。

整合以下，满足除了要求6以外要求的，长度为 $n$ 的序列方案数为：
* $n$ 为偶， $8\times 3^{\frac{n}{2}-1}$。
* $n$ 为奇， $14\times 3^{\frac{n-1}{2}-1}$。

现在考虑前缀和 $F_n=\sum_{i=1}^n f_n$ 的问题，可以发现同奇偶的 $f_n$ 构成了等比数列求和公式：
* 若 n 为偶， $\sum_{i=1}^n f_n=4\times (3^{\frac{n}{2}}-1)+7\times (3^{\frac{n}{2}-1}-1)+4$。
* 若 n 为奇， $\sum_{i=1}^n f_n=4\times (3^{\frac{n}{2}}-1)+7\times (3^{\frac{n}{2}-1}-1)+4+14\times 3^{\frac{n-1}{2}-1}$。

这样不考虑要求6时就做完了。

## 步骤三
加上要求6。其要求我们去重。直接除以二显然是不正确的，因为本来就只会被计算一次的回文串也会被除以2。而这样的回文串共有 $F_{\lceil \frac{n}{2}\rceil}$ 个。

那么我们最终的前缀和 $G_n$ 就是 $\frac{F_n+F_{\lceil \frac{n}{2}\rceil}}{2}$。

最终答案是 $G_r-G_{l-1}$。代码较为好写。

---

## 作者：kimi0705 (赞：0)

### 题解：CF93D Flags
#### part0
对于区间求值的问题，基本上都是用**求前缀和相减**的方法。
#### part1
计算**只满足** $1.2.3$ 三个条件的个数。

计答案个数为 $f(x)$，$x'=\lceil\frac{x}{2}\rceil-1$。通过递推得出：
$$f(x)=\left\{
\begin{aligned}
19\times 3^{x'} - 7 (x\equiv0\bmod 2)\\
11\times 3^{x'} - 7 (x\equiv1\bmod 2)
\end{aligned}
\right. $$

推导思路：求出每一个长度的数量记为 $a_i$。再求 $f(x)=\sum_{i=1}^{x}a_i$ 即可。
### part2 

但现在的问题是有条件 $4$。

- 当串为**回文串**时，答案不变，比较好算，数量记为 $p$。
- 当串为**非文串**时，答案会被**多算一次**。

所以答案应为 $y=\frac{f(x)-p}{2}+p$，即 $y=\frac{f(x)+p}{2}。$
### part3 code
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <limits>
#include <cmath>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <limits>
#include <map>
#include <vector>
#include <set>
#include <queue>
using namespace std;
const int mod = 1e9 + 7;
const int div2 = (mod + 1) / 2;
long long qpow(int x, int y) {
    if (y == 0) return 1LL;
    else if (y == 1) return x;
    long long res = qpow(x, y / 2);
    res = res * res % mod;
    if (y & 1) return res * x % mod;
    return res;
}
long long f(int x) {
    if (x == 0) return 0;
    if (x % 2 == 0) return (19LL * qpow(3, (int)ceil(x / 2.0) - 1) - 7) % mod;
    else return (11LL * qpow(3, (int)ceil(x / 2.0) - 1) - 7) % mod;
}
long long  g(int x) {
    return (f(x) + f((x + 1) / 2)) % mod * div2 % mod;
}
void solve() {
    int l, r;
    cin >> l >> r;
    cout << (g(r) - g(l - 1) + mod) % mod;
}
int main () {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    while (t--) solve();
    putchar(10);
    return 0;
}
```

---

