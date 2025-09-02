# Best-of-(2n-1)

## 题目描述

高桥和青木将要玩一个游戏。他们会反复游戏直到其中一人胜利 $N$ 次。

他们玩游戏时，高桥、青木的胜率分别为 $A\%$、$B\%$，平局（双方均不获胜）的概率为 $C\%$。请计算游戏进行次数的估计值，并按以下方式输出。

我们可以找出两个互质的整数 $P$，$Q$，用 $P/Q$ 表示估计值。输出满足 $0 \leq R \leq 10^9+6$ 的整数 $R$，使得 $R \times Q \equiv P \pmod {10^9+7}$ 成立（在本题的条件下，整数 $R$ 总是唯一存在）。

## 说明/提示

- $1 \leq N \leq 100000$
- $0 \leq A,B,C \leq 100$
- $A+B \geq 1$
- $A+B+C=100$
- 输入的数均是整数。

**【样例解释】**

【样例 1】因为 $N=1$，所以他们会重复游戏，直至一人胜利。因此，游戏次数的估计值为 $2$。

【样例 2】$C$ 可能是 $0$。

【样例 3】$B$ 也可能是 $0$。

## 样例 #1

### 输入

```
1 25 25 50```

### 输出

```
2```

## 样例 #2

### 输入

```
4 50 50 0```

### 输出

```
312500008```

## 样例 #3

### 输入

```
1 100 0 0```

### 输出

```
1```

## 样例 #4

### 输入

```
100000 31 41 28```

### 输出

```
104136146```

# 题解

## 作者：chenxia25 (赞：1)

首先有这个平局这个东西存在，使得次数可能达到无限。我们不列无穷级数，想办法把这个平局给搞掉。我们可以重新定义「一次」为从当前开始第一次分出胜负，这样次数显然是有限的，就很好求。而这两者的转化恰好是成比例的，原定义下的答案显然是新定义下的答案乘以「新的一次在原定义下的期望次数」，而这显然是个定值。设它为 $e$，显然满足 $e=1+Ce$，所以 $e=\dfrac{1}{1-C}$（这个 $e$ 其实也能列无穷级数求）。

然后考虑新问题的答案。那次数显然少则 $n$，多则 $2n-1$，枚举一下，考虑每种的概率是多少。假设 A 赢了，最后一步显然一定要是 A，前面要有 $n-1$ 个 A 和 $i-n$ 个 B，总分布方式数是 $\dbinom{i-1}{n-1}$。而每种出现的概率为 $A^nB^{i-n}$。B 赢的话就镜像一波，容易列出 $i$ 次的概率。然后乘以 $ie$ 加起来就是答案的期望值啦。

代码就不用给了吧 qwq

---

## 作者：AC_love (赞：0)

令 $a = A\%, b = B\%, c = C\%$。

先考虑 $c = 0$ 的情况。

此时每局游戏一定有一个人获胜，因此最少 $n$ 轮最多 $2n - 1$ 轮之后就能分出胜负。

我们直接枚举游戏进行的轮次数 $n + i$，其中 $i$ 是最后没赢到 $n$ 轮的人赢的轮数。

此时如果 $a$ 获胜，那么最后一个数一定是 $a$，前面 $n + i - 1$ 个数里有 $n - 1$ 个 $a$。

这个方案数应该是：

$${n + i - 1\choose n - 1}$$

期望步数等于：

$${n + i - 1\choose n - 1} \times  a^nb^i \times (n + i)$$

$b$ 获胜的情况同理，最后统计的答案应该是：

$$\sum_{i = 0}^{n - 1}{n + i - 1\choose n - 1} \times  (a^nb^i + a^ib^n) \times (n + i)$$

现在加入了平局，我们该怎么办呢？

我们考虑期望每 $k$ 轮就会出现一轮有人获胜的情况，那么拿刚才的答案乘上 $k$ 即可。

$k$ 怎么求？$1$ 轮游戏有 $1 - c$ 的期望出现有人获胜的情况，$k$ 轮游戏有 $1$ 的期望出现有人获胜的情况。有：

$$\dfrac{1}{1 - c} = \dfrac{k}{1}$$

即：

$$k = \dfrac{1}{1 - c}$$

需要注意刚才的 $a, b$ 应该改成形如 $\dfrac{a}{a + b}, \dfrac{b}{a + b}$ 的形式，因为这个时候 $c$ 已经不等于 $0$ 了。

[code](https://atcoder.jp/contests/m-solutions2019/submissions/59635892)

---

## 作者：COsm0s (赞：0)

我们令 A 赢得了这场比赛（获胜 $n$ 轮）。

那么 B 有 $0\sim n - 1$ 共 $n$ 个赢的可能。

我们确定 A 与 B 的相对取胜位置，类似以下情况（设 $A$ 代表 A 赢，$B$ 代表 B 赢，$\cdots$ 即平局）：

`A...B...AA...B...B...AAA...A`

对于这个相对取胜位置，我们可以知道，对于 B 获胜 $i$ 局，总共有 $n+i$ 个非平局。

但是显然第 $n+i$ 局只能由 A 取胜。

所以我们总共有 $n+i$ 个“空位”可以插入平局。

设一段平局加一个非平局的期望为 $P$。

那么，

$$

P=\sum\limits_{i=0}^{\infty}(1-a-b)^i=\frac{1}{a+b}

$$

再返回来看没有平局的情况下的期望。

$n+i$ 个非平局中最后一个恒为 $A$，那么其方案数为 $\dbinom{n+i-1}{n-1}$。

那么其期望即为：

$$
	\sum\limits_{i=0}^n\dbinom{n+i-1}{n-1}\left(\dfrac{a}{a+b}\right)^n\left(\dfrac{b}{a+b}\right)^i
$$

那么答案即为：

$$
	S=\sum\limits_{i=0}^n\dbinom{n+i-1}{n-1}\left(\dfrac{a}{a+b}\right)^n\left(\dfrac{b}{a+b}\right)^i(n+i)\left(\frac{1}{a+b}\right)
$$



---

## 作者：Zhao_daodao (赞：0)

## solution

推了一会式子就推出来了。

### 对于 $O(n^2)$
考虑 `DP`。设 $dp_{i,j}$ 表示第一个人赢了 $i$ 次，第二个人赢了 $j$ 次的期望。

能推出状态转移方程：

$dp_{i,j}=\frac{a}{100}\times dp_{i-1,j}+\frac{b}{100}\times dp_{i,j-1}+\frac{c}{100}\times dp_{i,j}$

将式子移项并化简，得到了一条更简洁的式子：

$dp_{i,j}=\frac{a}{100-c}\times dp_{i-1,j}+\frac{b}{100-c}\times dp_{i,j-1}$
### 接下来

考虑 $dp_{0,0}$ 对 $dp_{n,i}$ 的贡献。

因为最后一次一定是 $A$ 赢，所以贡献是：

$dp_{0,0}\times \dbinom{n-1}{i-1}\times (\frac{a}{100-c})^{n}\times (\frac{b}{100-c})^{i}$

现在主要是难以求出 $dp_{0,0}$。

考虑极限，$dp_{0,0}$ 只能是很多个平局，通过样例一能够发现：

$dp_{0,0}=1+\frac{c}{100}+(\frac{c}{100})^{2}+(\frac{c}{100})^{3}+\cdots+(\frac{c}{100})^{\infty }$。

两边同时乘 $\frac{c}{100}$，得：

$\frac{c}{100}\times dp_{0,0}=\frac{c}{100}+(\frac{c}{100})^{2}+(\frac{c}{100})^{3}+\cdots+(\frac{c}{100})^{\infty }$

两式相减：

$\frac{100-c}{100}\times dp_{0,0}=1$

即：

$dp_{0,0}=\frac{100}{100-c}$

带回原式 $dp_{n,i}$ 就算出来了。

---

## 作者：tzc_wk (赞：0)

[Atcoder 题面传送门](https://atcoder.jp/contests/m-solutions2019/tasks/m_solutions2019_c) & [洛谷题面传送门](https://www.luogu.com.cn/problem/AT5011)

无穷级数求和的简单题，稍微写写吧，正好也算帮我回忆下组合数这一块的内容。

首先我们不妨假设 A 赢，B 赢的情况就直接镜像一下即可。我们枚举 B 在 A 赢之前赢了多少局，设为 $j$，由于题目规定只要有人赢的局数到达 $n$ 就停止，因此最后一场比赛必须是 A 赢，而前面相当于在 $n-1+j$ 个场次中选择 $n-1$ 场留给 A 赢，剩余留给 B 赢，方案数 $\dbinom{n-1+j}{n-1}$，而 A 赢 $n$ 场的概率为 $A^n$，B 赢 $j$ 场的概率为 $B^j$，因此这部分的概率为 $\dbinom{n-1+j}{n-1}\times A^n\times B^j$。

接下来考虑平局的问题，按照套路我们枚举有多少次平局，设为 $i$，显然 $i$ 场平局的概率为 $C^i$，而将 $i$ 场平局插入原本 $n-1+j$ 场分出胜负的比赛，根据隔板法可知方案数为 $\dbinom{n-1+j+i}{i}$，最后乘上个比赛次数 $i+j+n$ 就是期望，因此我们可以初步得到答案的表达式：

$$ans_A=\sum\limits_{j=0}^{n-1}\dbinom{n-1+j}{n-1}\times A^n\times B^j\sum\limits_{i=0}^{\infty}C^i\dbinom{n-1+j+i}{i}\times(n+j+i)$$

由于这是个无穷级数，无法直接求和，需将其转化为封闭形式后再计算。注意到后面的 $\sum\limits_{i=0}^{\infty}C^i\dbinom{n-1+j+i}{i}\times(n+j+i)$，如果不看那个 $\times(n+j+i)$，是非常容易转化为封闭形式的，根据生成函数的知识它就是 $\dfrac{1}{(1-C)^{n+j}}$，重点在于后面的 $\times(n+j+i)$ 怎样处理，一个想法是将 $n+j+i$ 拆成 $n+j$ 和 $i$，前面的 $\sum\limits_{i=0}^{\infty}C^i\dbinom{n-1+j+i}{i}\times(n+j)$ 相当好处理，直接乘个 $n+j$ 即可，但是 $\sum\limits_{i=0}^{\infty}C^i\dbinom{n-1+j+i}{i}\times i$ 比较棘手，我花费了九牛二虎之力找这东西的封闭形式，xtbz，果然 wtcl 了啊（

注意到 $(n+j+i)$ 与前面二项式系数的 $n-1+j+i$ 只差一个 $1$，因此很容易联想到吸收恒等式 $\dbinom{n}{k}\times k=\dbinom{n-1}{k-1}\times n$，但是如果直接化后面还是会多出个 $i$，~~等于啥都没干~~，不过显然 $\dbinom{n-1+j+i}{i}=\dbinom{n-1+j+i}{n+j-1}$，而 $\dbinom{n-1+j+i}{n+j-1}\times(n+j+i)=\dbinom{n+j+i}{n+j}\times(n+j)=\dbinom{n+j+i}{i}\times(n+j)$，故 $\sum\limits_{i=0}^{\infty}C^i\dbinom{n-1+j+i}{i}\times(n+j+i)=\sum\limits_{i=0}^{\infty}C^i\dbinom{n+j+i}{i}\times(n+j)$，噫，好，$i$ 没了，这下就可以直接套公式求和了，故：

$$ans_A=\sum\limits_{j=0}^{n-1}\dbinom{n-1+j}{n-1}\times A^n\times B^j\times\dfrac{1}{(1-C)^{n+j+1}}\times(n+j)$$

随便算一下即可，时间复杂度 $\mathcal O(n)/\mathcal O(n\log n)$，取决于你怎么实现。

~~最后，无限 orz ycx，他的方法比我不知道简便到哪里去了 ！！！11~~

```cpp
const int MAXN=2e5;
const int INV100=5.7e8+4;
const int MOD=1e9+7;
int qpow(int x,int e){
	int ret=1;
	for(;e;e>>=1,x=1ll*x*x%MOD) if(e&1) ret=1ll*ret*x%MOD;
	return ret;
}
int n,A,B,C,fac[MAXN*2+5],ifac[MAXN*2+5];
void init_fac(int n){
	fac[0]=ifac[0]=ifac[1]=1;
	for(int i=2;i<=n;i++) ifac[i]=1ll*ifac[MOD%i]*(MOD-MOD/i)%MOD;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%MOD,ifac[i]=1ll*ifac[i-1]*ifac[i]%MOD;
}
int binom(int x,int y){return 1ll*fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;}
int main(){
	scanf("%d%d%d%d",&n,&A,&B,&C);
	A=1ll*A*INV100%MOD;B=1ll*B*INV100%MOD;C=1ll*C*INV100%MOD;
	init_fac(n*2);C=qpow(MOD+1-C,MOD-2);int ans=0;
//	printf("%d %d %d\n",A,B,C);
	for(int i=0;i<n;i++){
		ans=(ans+1ll*binom(n-1+i,n-1)*qpow(A,n)%MOD*qpow(B,i)%MOD*qpow(C,n+i+1)%MOD*(n+i))%MOD;
		ans=(ans+1ll*binom(n-1+i,n-1)*qpow(B,n)%MOD*qpow(A,i)%MOD*qpow(C,n+i+1)%MOD*(n+i))%MOD;
	} printf("%d\n",ans);
	return 0;
}
```



---

