# [CoE R4 E] 伪随机

## 题目描述

很久很久以前，小明生成了一些数据。

他的数据生成器使用了以下两个函数生成随机数：

```plain
定义函数 srand(32 位无符号整数 seed)
	将 x 赋值为 seed

定义函数 rand()
	将 x 赋值为 x 异或 (x 左移 13 位)
	将 x 赋值为 x 异或 (x 右移 17 位)
	将 x 赋值为 x 异或 (x 左移 5 位)
	返回 x
```

小明在调用 $\text{srand(seed)}$ 后，连续调用了 $n$ 次 $\text{rand()}$，并且记录下了每次 $\text{rand()}$ 的返回值对 $p$ 取模时得到的余数 $a_i$。

很久很久以后，只有数据生成器依然残存（实现见下发文件的 `generator.cpp`），但生成器的参数 $\text{seed}$ 和 $p$ 已经消失。

小明想要从数据中恢复这两个参数。即给定序列 $a_i$，需要找到任意一组 $\text{seed}$ 和 $p$ 的可能的值。你能帮帮他吗？

---

**简要描述**

小明的数据生成器是下发文件的 `generator.cpp`。你需要根据生成器的输出，反推出生成器的输入。


## 说明/提示

### 数据规模

本题共有 $50$ 个测试点，每个测试点 $2$ 分。

对于所有数据，保证 $n = 10^5$，$\text{seed}$ 是随机选取的，且至少存在一组解。


## 样例 #1

### 输入

```
见下发文件的 sample.in```

### 输出

```
见下发文件的 sample.out```

# 题解

## 作者：yzy1 (赞：7)

## 题目大意

给出一个 XOR-Shift 生成的长度为 $n=10^5$ 的数列 $a$，数列元素对 $p$ 取模。根据数列还原 XOR-Shift 的种子 $seed$ 和 $p$。

## 算法 $\bf 1$

显然 $p$ 大于 $a$ 中最大值。易得 $p$ 应在 $\max\{a\} + \max\{a\}/n$ 附近。设 $b$ 为取模前的 $a$ 数列。特别地，$b_0=seed$。考虑如何从 $b_i$ 得到 $b_{i-1}$：把 $b_{i-1}$ 的每个二进制位设为未知数，由 XOR-Shift 的过程列出异或方程组，高斯消元解出。假设 $p$ 已经固定，则 $b_1 \in \{kp+a_1 \mid k \in \mathbb N\}$。又由于取值范围 $32$ 位无符号整数。故 $b_1$ 只有 $O(V / p)$ 种取值。由此我们可以得到一个基于随机化的算法：每次从 $\max\{a\}+1$ 到 $\max\{a\} + 3\max\{a\}/n+1$ 随机一个整数作为 $p$，然后从所有可能成为 $b_1$ 的整数中随机一个作为 $b_1$，检查是否合法。若合法则通过高斯消元得到 $b_0$。

设答案唯一，则每次尝试得到答案的概率约为：

$$
\frac{1}{(\frac{3\max\{a\}}{n}+1) \frac{2^{32}}{\max\{a\}}}
$$

当 $\max\{a\}$ 较大时，概率约等于 $\dfrac n {3\times 2^{32}}$，该算法表现较好。但 $\max\{a\}$ 较小时不佳。调整参数后该算法可获得 $80$ 分。

## 算法 $\bf 2$

$\max\{a\}$ 较小时，可认为 $p=\max\{a\}+1$。考虑用类似 P7350 这题的方式来做这道题。计算出 $a$ 的所有长度为 $50$ 的子区间的 hash 值存入 `unordered_map`。每次随机一个 $seed$，生成一个长度为 $50$ 的序列，查 `unordered_map` 判断这个序列是否和 $a$ 的子区间匹配，若匹配则重复高斯消元直到还原出 $seed$，判断 $seed$ 是否合法。

这个做法正确性不太会证，仅感性理解：$\max\{a\}$ 较小时，若每次随机的 $seed$ 得到的 hash 存在于 `unordered_map`，则较大概率这个种子合法。可以简单地认为检查一个种子是否合法是 $O(1)$ 的。相当于每次检查 $2^{32}$ 个种子中的一个是否在 $O(n)$ 个种子中，每次成功率约 $n/2^{32}$。

---

我们可以数据分治，在 $\max\{a\} \ge 1000$ 时使用做法 $\bf 1$，否则使用做法 $\bf 2$。调参后即可 AC。


---

## 作者：Analgesia (赞：4)

一道有趣的随机~~乱搞~~题，搞了一个上午。

首先，我们考虑 $p$ 比较大怎么做，我们会发现大概率会有一个数满足这次随机出来的数比 $p$ 小，即 $rand()=a_i$ ，因为 $a_i=rand() \mod p$ 的话我们是不好解决的。假设有一个数满足，那么这个数接下来生成的几个数我们就知道了，记为 $x_i$，若他们满足 $x_i \ge a_i$ 且 $gcd(x_i-a_i,x_{i+1}-a_{i+1},...)>max\{a_1,a_2,...,a_n\}$ ，我们就可以认为这个数真的满足条件，且模数 $p=gcd(x_i-a_i,x_{i+1}-a_{i+1},...)$，事实上我们取后面 $5$ 个数在 $p$ 较大时就已经完全可以保证正确性了。

接下来，我们知道了一个时刻的 $rand()$ 是否可以推出 $seed$ 呢？答案是肯定的，我们发现这相当于解出一个异或方程组，事实上这个方程组线性无关，所以我们可以解出来 $seed$ (代码使用了 $2^{32}$ 打表预处理）。于是， $p \ge 10000 $左右的分就可以拿到了，实测 $56pts$。

然后考虑， $p$ 比较小怎么做，这是本题的难点，我们首先发现 $p$ 应该等于 $max\{a_i\}+1$，这是因为在 $p$ 小于 $10000$ 的时候，所有数小于 $p-1$ 的概率只有 $10^{-9}$ 可以忽略，而 $p$ 确定了以后我们发现知道了 $seed$ 就可以知道后面的一串数，于是我们可以考虑随机一个 $x_i$ 表示某个时刻 $i$ 的 $rand()$ ，可以发现接下来的 $x_{i+1},x_{i+2},...,x_n$ 就确定了，考虑向后比对几位 $x_i \mod p$ 与 $a_i$ 如果一样就可以认为 $x_i$ 是对的。

考虑全局随机这个 $x_i$ ,可以用 $map$ 存 $a$ 中所有长度为 $l$ 的子串的值(代码用了 $p$ 进制状压)，再判断 用 $x_i$ 生成的长度为 $l$ 的一段是否在 $a$ 中出现，会发现 $x_i$ 随机次数的期望是 $\frac{2^{32}}{n} $，只要让 $p^l$ 达到 $2^{64}$ 的级别，就可以让错误率可以接受了。

于是就做完了复杂度 $O(n\log n+\frac{2^{32}}{n}\log n)$

code:
```
#include<bits/stdc++.h>
using namespace std;
#define rep(i,x,y) for(int i=x;i<=y;i++)
const int N=100005;
int n;
unsigned int a[N],mx;
unsigned int cal[32]={4071982377u,
3848997458u,
3738612901u,
3182258506u,
2069549716u,
4139099432u,
3983231568u,
3470144673u,
2645322050u,
995676804u,
1991353608u,
3982707216u,
3469095969u,
2643224642u,
991481988u,
1982963976u,
3965927952u,
3435537441u,
2576107586u,
857247876u,
1714495752u,
3428991504u,
2294547488u,
294127680u,
588255360u,
1176510720u,
2353021440u,
142607360u,
285214720u,
570429440u,
1140858880u,
2281717760u};
unsigned int ran(unsigned int &seed){
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;
} 
unsigned int b[N];
unordered_map<long long,int>mp;
unsigned int sol(unsigned int x){
	unsigned int as=0;
	rep(bit,0,31)if((x>>bit)&1)as^=cal[bit];
	return as;
}

int main(){
	cin>>n;
	rep(i,1,n){
		scanf("%u",&a[i]);
		mx=max(mx,a[i]);
		
	}
	if(mx==0){
		printf("2 1");
		return 0;
	}
	unsigned p=0,seed=0,ps=0;
	if(mx>1000)rep(i,1,n-20){
		unsigned int x=a[i];
		long long g=(long long)ran(x)-a[i+1];//代码懒得判小于了，反正不太容易错 
		g=__gcd((long long)ran(x)-a[i+2],g);
		g=__gcd((long long)ran(x)-a[i+3],g);
		g=__gcd((long long)ran(x)-a[i+4],g);
		g=__gcd((long long)ran(x)-a[i+5],g);
		if(g>(long long)mx){
			p=g;seed=a[i],ps=i;
			break;
		}
	}
	if(!p){
		p=mx+1;
		int pm=1;
		long long p0=p;
		while(p0<=(long long)1<<50)pm++,p0*=p;
		rep(i,1,n-pm){
			long long tmp=a[i];
			rep(j,i+1,i+pm)tmp=1ll*tmp*p+a[j];
			mp[tmp]=i;
		}
		rep(i,19260817,100000000){
			unsigned int se=i;
			long long tmp=se%p;
			rep(j,1,pm)tmp=1ll*tmp*p+ran(se)%p;
			if(mp[tmp]){
				seed=i,ps=mp[tmp];
				break;
			}
		}
	}
	rep(i,1,ps)seed=sol(seed);
	printf("%u %u\n",seed,p);
}
//seed
```

---

