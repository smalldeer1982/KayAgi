# Fusing Slimes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dwacon6th-prelims/tasks/dwacon6th_prelims_b

数直線上に $ N $ 匹のスライムが並んでいます。 左から $ i $ 番目のスライムは位置 $ x_i $ にいます。

ここで、$ 1\ \leq\ x_1\ <\ x_2\ <\ \ldots\ <\ x_N\ \leq\ 10^{9} $ が成立することが保証されます。

ニワンゴ君は操作を $ N-1 $ 回行います。$ i $ 回目の操作は以下の手順からなります。

- $ 1 $ 以上 $ N-i $ 以下の整数を等確率で選ぶ(これを $ k $ とする)
- 左から $ k $ 番目にいるスライムを右隣にいるスライムの位置まで移動させる
- その後、同じ位置にいる $ 2 $ 匹のスライムを合体させ、$ 1 $ 匹のスライムにする

$ N-1 $ 回の操作によって、スライムが移動した距離の総和の期待値に $ (N-1)! $ をかけた値(これは整数になることが示せます)を $ 10^{9}+7 $ で割ったあまりを求めてください。なお、合体後のスライムが移動した場合は $ 1 $ 体のスライムの移動として数えます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^{5} $
- $ 1\ \leq\ x_1\ <\ x_2\ <\ \ldots\ <\ x_N\ \leq\ 10^{9} $
- $ x_i $ は整数

### 部分点

- $ N\ \leq\ 2000 $ であるようなテストケースすべてに正解すると、$ 400 $ 点が与えられる。

### Sample Explanation 1

\- 確率 $ \frac{1}{2} $ で最初に左から $ 1 $ 番目のスライムが選ばれ、このときの移動距離の総和は $ 2 $ となります。 - 確率 $ \frac{1}{2} $ で最初に左から $ 2 $ 番目のスライムが選ばれ、このときの移動距離の総和は $ 3 $ となります。 - 移動距離の総和の期待値である $ 2.5 $ に $ 2! $ をかけた値である $ 5 $ が答えとなります。

### Sample Explanation 2

\- 期待値の $ (N-1)! $ 倍を $ 10^9+7 $ で割ったあまりを求めてください。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
5```

## 样例 #2

### 输入

```
12
161735902 211047202 430302156 450968417 628894325 707723857 731963982 822804784 880895728 923078537 971407775 982631932```

### 输出

```
750927044```

# 题解

## 作者：Clouder (赞：5)

可以想到，每种情况都对应一个长度为 $n - 1$ 的排列。

考虑计算每条路径被经过了多少次， 先对原数组做差分。

记 $d(i)$ 为 $i \to i + 1$ 的长度，$f(i)$ 为 $i \to i + 1$ 的路径被经过的期望次数。

$E = \sum \limits _{i = 1}^{n-1}d(i) \times f(i)$

考虑如何计算 $f(i)$。

定义 $g(j,i)$ 为点 $j$ 向右融合经过 $i \to i + 1$ 这条路径的期望次数。

有：$f(i) = \sum \limits _{j = 1}^i g(j,i)$

问题在于计算 $g(j,i)$，考虑 $j$ 点能顺畅地右移到 $i + 1$，那么 $[j + 1,i]$ 间的点都已经右移。

表现在序列上，就是 $j$ 的出现位置一定在 $[j + 1,i]$ 之后。

可以考虑先在移动序列中对 $[j,i]$ 间的 $i - j + 1$ 个元素去序，然后将 $j$ 放在最后，剩余 $i - j$ 个元素进行全排列，放回原序列中。

$$g(j,i) = \dfrac{(n-1)!}{(i - j + 1)!} \times (i-j)!$$

$$g(j,i) = \dfrac{(n-1)!}{i-j+1}$$
这样就较为简单地推出了 $g(j,i)$，而不需要别的题解中我看不懂的奇怪式子。(

$$f(i) = \sum \limits _{j=1}^i g(j,i) = (n-1)! \times \sum \limits _{j=1}^i \dfrac{1}{i-j+1}$$
还可以进一步化简：

$$f(i) = (n-1)! \times \sum \limits _{j=1}^i \dfrac{1}{j}$$

而答案就是：

$$E = \sum d(i) \times f(i) = (n - 1)! \times \sum \limits _{i=1}^{n-1} (d(i) \times \sum \limits _{j=1}^i \dfrac{1}{j})$$

可以线性递推逆元，预处理调和级数前缀和做到 $O(n)$ 复杂度。

```cpp
const int maxn = 1e5 + 100;
const int mod = 1e9 + 7;
inline int add(int x, int y) { int res = x + y; return res >= mod ? res - mod : res; }
inline int mul(int x, int y) { return 1ll * x * y % mod; }
int n, a[maxn], inv[maxn], sum[maxn], res, prod = 1;
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    inv[1] = sum[1] = 1;
    for (int i = 2; i <= n; ++i) sum[i] = add(sum[i - 1], inv[i] = mul(inv[mod % i], mod - mod / i));
    for (int i = 1; i < n; ++i) prod = mul(prod, i), res = add(res, mul(a[i + 1] - a[i], sum[i]));
    printf("%d\n", mul(prod, res));
    return 0;
}
```


---

## 作者：tommymio (赞：2)

可以发现，每组操作唯一对应一个长度为 $n-1$ 的排列。有了这个结论，后面就好做多了。

像这类排列，与期望相关的题目，我们一般都不需要得到整个完整的排列，而是从排列中拆一段贡献出来算，这题也是一样。

非常 $\text{Naive}$ 的想法：设 $E[X]$ 为期望移动距离和，有 $E[X]=\sum\limits_{i=1}^{n-1}E[i]$，其中 $E[i]$ 是第 $i$ 次期望移动的距离。这样不太好算。不妨换个想法，设 $E[i]$ 为 $x_i\to x_{i+1}$ 这一段被经过的期望次数。如果我们能够计算出每个 $E[i]$ ，把它乘上 $(x_{i+1}-x_i)$ ，就是 $x_i\to x_{i+1}$ 这一段期望移动的距离和。

按照套路，$E[i]=\sum\limits_{j=1}^{i} p_{i,j}$，其中 $p_{i,j}$ 为第 $j$ 个点经过 $x_i\to x_{i+1}$ 的概率，根据期望的线性性质，这是显然的。

现在尝试计算出 $p_{i,j}$。有：
$$
p_{i,j}=\frac{1}{(n-1)!}\sum_{k=i-j}^{n-2}\binom{k}{i-j}(i-j)!(n-2-(i-j))!
$$
很容易可以算出 $p_{i,j}=\frac{1}{i-j+1}$。回带可得：
$$
E[X]=\sum_{i=1}^{n-1}(x_{i+1}-x_i)\sum_{j=1}^i\frac{1}{j}
$$
前缀和处理一下，可以做到 $O(n \log n)$。记得答案最后是 $E[X]\times(n-1)!$（

```cpp
#include<cstdio>
#define int ll
typedef long long ll;
const int mod=1e9+7;
int pref[100005],x[100005];
inline int read() {
    register int x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline int pow(int x,int p) {int res=1;for(;p;p>>=1) {if(p&1) res=res*x%mod; x=x*x%mod;}return res;}
signed main() {
    int n=read(),ans=0;
    for(register int i=1;i<=n;++i) x[i]=read();
    for(register int i=1;i<=n;++i) pref[i]=(pref[i-1]+pow(i,mod-2))%mod;
    for(register int i=1;i<n;++i) ans=(ans+(x[i+1]-x[i])*pref[i]%mod)%mod;
    for(register int i=1;i<n;++i) ans=ans*i%mod;
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：LCuter (赞：2)

可以在[我的个人博客](https://lcuter.gitee.io)观看。

## AT5741 题解

##### $\text{Description}$

数轴上有 $n$ 只史莱姆，第 $i$ 只史莱姆的位置为 $x_i$。

保证 $1\le x_1\le x_2\le \cdots\le x_n\le 10^9$。

Niwango 要进行 $n-1$ 次操作，第 $i$ 次操作的过程如下： 

1. 在 $[1,n-i]$ 中等概率随机选取一个**整数** $k$。 
2. 将从左至右第 $k$ 只史莱姆移至其右边距其最近的史莱姆处，并合并为一只史莱姆。 

你需要求出这 $n-1$ 次操作的过程中，Niwango 每次移动史莱姆的距离和的期望与 $(n-1)!$ 的乘积对 $10^9+7$ 取模后的值。 

形式化地，设你的答案为 $A$，则你需要输出 $$A\times (n-1)!\bmod{10^9+7}$$ 。

##### $\text{Solution}$

想了半天往错误的方向想了……

首先我们有 $E(\sum a_i)=\sum E(a_i)$，考虑将最终所求的 $A$ 分解为若干段 $x_{i+1}-x_i$ 的期望。

其次，我们认为一段 $x_{i+1}-x_{i}$ 被第 $j$ 个史莱姆走过当且仅当第 $j$ 个史莱姆是直接被移到第 $i+1$ 个史莱姆或更后面的史莱姆处的。这里的第几个指的是初始局面意义下的第几个。

那么记 $p_{i-j,i}$ 表示第 $i-j$ 个史莱姆走过 $x_{i+1}-x_i$ 这一段的概率，容易有 $p_{i-j,i}=\frac{1}{j+1}$，这是因为这个史莱姆必须在 $[i-j+1,i]$ 内的史莱姆全部都进行过移动后才进行移动的，也就是说它必须在第 $j+1$ 次或更后面才被移动，同时，按照题目中的选法，实际上任意一种选法都唯一对应一个排列，且任意选法概率相同，故有：
$$
\begin{aligned}
	p_{i-j,i}&=\frac{1}{(n-1)!}\sum_{k=j}^{n-2}{k\choose j}j!(n-j-2)!\\
			 &=\frac{j!(n-j-2)!}{(n-1)!}{n-1\choose j+1}\\
			 &=\frac{j!(n-j-2)!}{(n-1)!}\frac{(n-1)!}{(j+1)!(n-j-2)!}\\
			 &=\frac{1}{j+1}
\end{aligned}
$$


所以答案为：
$$
(n-1)!\sum_{i=1}^{n-1}(x_{i+1}-x_i)\sum_{j=1}^{i}\frac{1}{j}
$$


##### $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define REG register
using namespace std;
inline void read(int& x){
	static char c;
	while(!isdigit(c=getchar()));x=c^48;
	while(isdigit(c=getchar()))x=(x*10)+(c^48);
}

const int Mod=1000000007;

int n;

int x[100005];

int Pow(int a,int b){
	int ans=1;
	while(b){
    	if(b&1) ans=1ll*ans*a%Mod;
    	a=1ll*a*a%Mod,b>>=1;
    }
	return ans;
}

int _Inv[100005];

inline void Work(){
	read(n);
	for(REG int i=1;i<=n;++i) read(x[i]);
	int Ans=0;
	for(REG int i=1;i<=n;++i) _Inv[i]=(_Inv[i-1]+Pow(i,Mod-2))%Mod;
	for(REG int i=1;i<n;++i) Ans=(Ans+1ll*(x[i+1]-x[i])*_Inv[i]%Mod)%Mod;
	for(REG int i=1;i<n;++i) Ans=1ll*Ans*i%Mod;
	printf("%d\n",Ans);
}

int main(){Work();}
```



---

## 作者：white_carton (赞：1)

#### 前言

本篇题解仅作为对 @LCuterLCuter 的题解的解释。

---

#### 正文

把每段距离分开来计算贡献，设 $p_{i-j,i}$ 为第 $i-j$ 个史莱姆，经过 $x_{i+1}-x_i$ 这一段的概率，有 $\displaystyle ans=(n-1)!\sum_{i=1}^{n-1}(x_{i+1}-x_{i})\sum_{j=0}^{i-1} p_{i-j,i}$。

考虑到，$i-j$ 想要经过 $x_{i+1}-x_i$，必须要在 $[i-j+1,i]$ 这 $j$ 个都操作过了之后操作才能有贡献，如果把每次操作的点的原编号拿出来形成一个长度为 $n-1$ 的排列，刚才提及到的性质就相当于 $i-j$ 在排列里出现的位置一定在 $[i-j+1,i]$ 的后面。

我们钦定 $i-j$ 出现在排列的第 $k+1$ 个位置，于是有：

$$
p_{i-j,i}=\frac{1}{(n-1)!}\sum_{k=j}^{n-2}{k \choose j}j!(n-2-j)!
$$

稍微解释一下，${k \choose j}$ 表示前 $k$ 个位置中选择 $j$ 个位置填入 $[i-j+1,i]$，由于这 $j$ 个数的顺序没有限制，因此再乘上一个 $j!$，除去钦定的 $i-j$，剩下的 $n-2-j$ 的排列也是随意的。

注意到 $j!(n-2-j)!$ 与 $k$ 没有关系，因此可以提出去。

$$
\begin{align}
p_{i-j,i}&=\frac{j!(n-2-j)!}{(n-1)!}\sum_{k=j}^{n-2}{k \choose j}\\
&=\frac{j!(n-2-j)!}{(n-1)!}{n-1 \choose j+1}\\
&=\frac{1}{j+1}
\end{align}
$$

求和转为组合数的解释如下，画的有点抽象。

![alt text](https://cdn.luogu.com.cn/upload/image_hosting/vukka7nb.png)

每个三角形都代表杨辉三角。

![alt text](https://cdn.luogu.com.cn/upload/image_hosting/0e77wmla.png)

这里是两个式子：
$$
{n \choose n}=1={n+1 \choose n+1}\\
{n \choose m}={n-1 \choose m}+{n-1 \choose m-1}
$$
三角形上的较小的圆代表单个点，较长的代表圈中的部分的和，较长的圈中最上面的一个组合数会和小圆里的组合数形成下一层的一个，也就是上面的第二个式子，这个操作可以一直递推下去。

有了式子然后直接求就好了。

---

## 作者：AC_love (赞：0)

设 $f(i)$ 表示每条 $x_i \rightarrow x_{i + 1}$ 的路径在所有 $(N - 1)!$ 情况中被经过的次数。

显然最终的答案就是 $\sum f(i) \times dis(i, i + 1)$。

考虑如何计算 $f(i)$。

枚举 $i$ 左侧的点 $j$，每个 $j$ 都有对 $f(i)$ 有一定贡献，考虑这个贡献怎么计算：

原问题的本质其实是每次选择一个点再删掉，因此最后选择的所有点一定构成一个长度为 $N - 1$ 的排列。

考虑一个什么样的排列能让 $j$ 对 $i$ 产生贡献。

显然，我们需要让 $j$ 和 $i$ 中间的点都在 $j$ 之前被选择。

我们现在只考虑 $j$ 到 $i$ 的 $i - j + 1$ 个点，用这些点组成排列，但 $j$ 必须在最后，这样的排列占 $i - j + 1$ 个点能组成的排列数的 $\dfrac{(i - j)!}{(i - j + 1)!}$，化简一下等于 $\dfrac{1}{i - j + 1}$。

考虑 $n - 1$ 个点的排列，不难发现符合条件的排列就占全排列个数的 $\dfrac{1}{i - j + 1}$。

因此有：

$$f(i) = \sum_{j = 1}^{i}\dfrac{(n - 1)!}{i - j + 1}$$

化简得：

$$f(i) = \sum_{j = 1}^i\dfrac{(n - 1)!}{j}$$

可以利用前缀和快速计算出所有 $f(i)$，然后带入答案的计算式即可。

[code](https://atcoder.jp/contests/dwacon6th-prelims/submissions/59585205)

---

## 作者：WanderOvO (赞：0)

$upd:$增加了一处式子的中间计算过程，使得看起来更加有规律；代码增加了3处注释。

# 说明

本题解是对唯一一篇题解（LCuter大佬）中一些模棱两可的概率推导的补充，以及一些实验验证。

# 正文

第一篇题解考虑最后结果的期望怎么求，由于该题中两个史莱姆移动到一起就相当于只有一个史莱姆了，所以我们可以看成每个史莱姆只移动了一次。而我们最后要求的期望，可以转化为每个史莱姆走的距离的期望之和（即$E(\sum a_i)=\sum E(a_i)$） 。

下面考虑怎么算某个$E(a_i)$ 。

## 理论分析

我们以考第一只史莱姆为例子进行分析。第一只史莱姆可能在移动时移动几个空呢？显然可能取值是$1$到$n-1$。我们假设$n=5$模拟一下，找找规律。

我们考虑**移动操作进行顺序的全排列**，即对$1$到$n-1$个数进行全排列（第$n$个不用管他，他只能被动合并，不能主动合并）。

要想让1号史莱姆移动1步，那么2号必须在1号之后进行移动，即$1,2$在整个$1$到$n-1$的全排列中相对顺序是$2,1$，显然其概率为$\frac{0!}{2!}=\frac{1}{2}$。

要想让1号史莱姆移动2步，则2号必须在1号之前移动，且3号必须在1号之后移动，即在123的全排列中，1必须排在中间，且2在前面，3在后面，这种概率是$\frac{1!}{3!}=\frac{1}{6}$，其中$3!$指的是$1,2,3$的全排列数。

1号想移动3步，则23必须在1号前面移动，且4号必须在1号后面移动，所以概率是$\frac{2!}{4!}=\frac{1}{12}$ ，其中$2!$指的是$2,3$ 的相对顺序（即是$2,3$还是$3,2$），$4!$为$1,2,3,4$的全排列数。

走$1,2,3$步的情况都分析清楚了，而走$4$步的情况，就是$2,3,4$全在$1$前面，因为只有$5$个数，所以相当于是在$1$到$5$的全排列中，$1$在第四个，$5$在第五个，另外三个在前三个里面随便排，所以概率为$\frac{3!}{4!}$ 。

可以验证，$n=5$时，这四个概率加起来可以归一化。且不管$n$是多少，这样分析的话，总会发现概率加起来是可以归一化的。在计算期望时，我们稍微观察一下，就能发现明显的规律：其实对于第一个史莱姆来说，其期望就是$1+\frac{1}{2}+\frac{1}{3}+…+\frac{1}{n-1}$，即调和级数求和。

## 实验验证

手动计算：考虑史莱姆个数是$2,3,4,5,6$时，1号史莱姆移动距离的期望，手算结果分别是$1,1.5,1.83,2.08,2,28$，而实验结果如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/5n0javxu.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这在一定程度上验证了刚才的理论分析。

## 实验代码

下面附上验证该理论分析的实验代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int T=1e4+9;
int cnt[15],a[15],now,pos,ans;
bool create[15];
bool used[15];
bool flag=false;
int main(){
	ll tmp,step;
	srand(998244353);
	for(int N=2;N<=6;N++){
		ans=0;
		for(int i=1;i<=T;i++){
			flag=false;
			now=0;
			step=1;
			for(int j=1;j<=N;j++){
				create[j]=false;
				used[j]=false;
			}
			while(!flag){
				flag=true;
				tmp=rand()%N+1;
				if(!create[tmp] && tmp!=N){
					create[tmp]=true;
					a[++now]=tmp;
				}
				for(int j=1;j<N;j++){
					if(!create[j]){
						flag=false;
						break;
					}
				}
			} //生成一个移动全排列 
			for(int j=1;j<=N;j++){ //找一下1号史莱姆是第几个被移动的
				if(a[j]==1){
					pos=j;
					break;
				}
			}
			for(int j=1;j<pos;j++){
				used[a[j]]=true; //把在1号之前移动的史莱姆进行移动 
			}
			for(int j=2;j<N;j++){//遍历看看到底1号在该次模拟中走几步
				if(used[j]){
					step++;
				} else {
					break;
				}
			}
			ans+=step;
		}
		printf("N=%d Expectation=%lf\n",N,(1.0*ans)/T);
	}
	return 0;
}
```

在明白了上面的理论分析之后，就可以放心大胆的按照第一篇题解中所说的那样去做了。

---

