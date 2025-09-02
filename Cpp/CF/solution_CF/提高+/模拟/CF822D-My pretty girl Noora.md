# My pretty girl Noora

## 题目描述

In Pavlopolis University where Noora studies it was decided to hold beauty contest "Miss Pavlopolis University". Let's describe the process of choosing the most beautiful girl in the university in more detail.

The contest is held in several stages. Suppose that exactly $ n $ girls participate in the competition initially. All the participants are divided into equal groups, $ x $ participants in each group. Furthermore the number $ x $ is chosen arbitrarily, i. e. on every stage number $ x $ can be different. Within each group the jury of the contest compares beauty of the girls in the format "each with each". In this way, if group consists of $ x $ girls, then ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF822D/969c596ed060cb668747b79aae52c3adc4b7f3f8.png) comparisons occur. Then, from each group, the most beautiful participant is selected. Selected girls enter the next stage of the competition. Thus if $ n $ girls were divided into groups, $ x $ participants in each group, then exactly ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF822D/8f8703916c06209ae2c6ec59180f52b09e3975b5.png) participants will enter the next stage. The contest continues until there is exactly one girl left who will be "Miss Pavlopolis University"

But for the jury this contest is a very tedious task. They would like to divide the girls into groups in each stage so that the total number of pairwise comparisons of the girls is as few as possible. Let $ f(n) $ be the minimal total number of comparisons that should be made to select the most beautiful participant, if we admit $ n $ girls to the first stage.

The organizers of the competition are insane. They give Noora three integers $ t $ , $ l $ and $ r $ and ask the poor girl to calculate the value of the following expression: $ t^{0}·f(l)+t^{1}·f(l+1)+...+t^{r-l}·f(r) $ . However, since the value of this expression can be quite large the organizers ask her to calculate it modulo $ 10^{9}+7 $ . If Noora can calculate the value of this expression the organizers promise her to help during the beauty contest. But the poor girl is not strong in mathematics, so she turned for help to Leha and he turned to you.

## 说明/提示

Consider the sample.

It is necessary to find the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF822D/cada51a85db8e48cf197de751d78ba932c387644.png).

 $ f(2)=1 $ . From two girls you can form only one group of two people, in which there will be one comparison.

 $ f(3)=3 $ . From three girls you can form only one group of three people, in which there will be three comparisons.

 $ f(4)=3 $ . From four girls you can form two groups of two girls each. Then at the first stage there will be two comparisons, one in each of the two groups. In the second stage there will be two girls and there will be one comparison between them. Total $ 2+1=3 $ comparisons. You can also leave all girls in same group in the first stage. Then ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF822D/f0bdffc4a640a3c926e3ac1b0c07f337ac1e9d1c.png) comparisons will occur. Obviously, it's better to split girls into groups in the first way.

Then the value of the expression is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF822D/766d39075b51c44c1ef841a8899d917995ced842.png).

## 样例 #1

### 输入

```
2 2 4
```

### 输出

```
19
```

# 题解

## 作者：素质玩家孙1超 (赞：3)

来一发全场最慢解，总共跑了 $\rm 1.16 \min$ ,但是思路简单，代码好写。

用 $n\log n$ 大力跑过 $5 \times 10^6$，本题时限 $\rm 1.5 \ s$ 我最慢的一个点跑了 $\rm 1497 \ ms$。

---

题意：

$n $ 个女生，进行若干论选美。选美的方式如下：

+ 设当前人数为 $m$ ，选择一个正整数 $x(m≥x>1,x ∣ m)$ ，划分为 $\frac{m}{x}$ 组，每组 $x$ 个人。

+ 每一组中的女生两两比较，共进行 $\frac{x\times(x-1)}{2} $ 次比较。最终每一组只会有 $1$ 名女生晋级。

+ 所有晋级的女生继续进行选美，直到只剩下一名女生。

设初始为 $n$ 名女生时最少的总比较次数为 $f(n)$，求 

$$\sum_{i=l}^r t^{i-l}\times f(i) \mod (10^9+7)$$

---

其实就是批量求一个 $f(i)$ 然后最后用一种奇怪的方式求和之后输出。

开始，我们可以有一个幼稚的想法，直接枚举因数取 $\min$ 。式子是这个：

$$f(i) = \min _{d|n}  \frac{n}{d}\times \frac{d(n-1)}{2} \times f(\frac{n}{d})$$

其实 $\sum_{i=1}^n \sum_{d|i} 1$ 是 $O(n \log n )$ 的，但我们直接枚举因数是 $O(n\sqrt n)$ 的，考虑如何优化这个东西。


我们枚举复杂度不够优的原因是枚举了大量不是因数的东西，所以我们把式子搞成递推的形式，就可以直接枚举倍数而不多枚举了。这个是递推式：

$$f(i\times j)=\min (f(i \times j),f[i]+ \frac{j\times i \times (j-1)}{2})$$

其实这个转换挺常见的，然后枚举代码变成

```cpp
for(int i=1;i<=n;i++)
for(int j=2;j*i<=n;j++)
```

就是 $O(n\log n )$ 的了，就可以（靠着cf的评测机）大力艹过去了。

（这个 $O(n\log n )$ 有两种方式理解，一种是考虑意义是这个$\sum_{i=1}^n \sum_{d|i} 1$ ，还有一种是直接写式子发现是个调和级数求和就可以推出来了）


---

代码：

```cpp
#include<bits/stdc++.h>
inline int R()
{
	char c;int sign=1,res=0;
	while((c=getchar())>'9'||c<'0') if(c=='-') sign=-1;res+=c-'0';
	while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';
	return res*sign;	
}
using namespace std;
#define int long long
const int Maxm=5e6+5;
const int Mo=1e9+7;
int n,m,f[Maxm],t,l,r;
signed main()
{
	memset(f,0x7f,sizeof f);
	t=R();l=R();r=R();n=r;
	f[1]=0;
	for(int i=1;i<=n;i++)
	for(int j=2;j*i<=n;j++)
	f[i*j]=min(f[i*j],f[i]+1ll*j*i*(j-1)/2);
	int ans=0,S=1;
	for(int i=l;i<=r;i++)
	{
		ans=(ans+S*(f[i]%Mo))%Mo;
		S=S*t%Mo;
	}
	printf("%lld\n",ans);
}
```


---

## 作者：porse114514 (赞：1)

# CF822D My pretty girl Noora 题解
个人认为题意翻译已经足够清晰，于是我就不再赘述了。
## 思路
首先，看到筛选方法，感到很奇怪，于是我便觉得这是到找规律题，于是开始推式子。

假设按照 $x$ 人一组淘汰，那么：
- 这一组淘汰 $x$ 个人；
- 这一组有 $\frac{x\times (x-1)}{2}$ 次比较。

所以平均每 $\frac{\frac{x\times (x-1)}{2}}{x}=\frac{x-1}{2}$ 次比较淘汰一个人，显然，要使比较最少，$\frac{x-1}{2}$ 也要尽可能小，所以 $x$ 要尽可能小。又因为 $x\,|\,m$（$m$ 的含义与题目相同）
，所以 $x$ 应取 $m$ 的最小质因子。

所以我们有了递推方程，设 $x$ 的最小质因子为 $g(x)$，则：
$$f(i)=f(\frac{i}{g(i)})+\frac{g(i)\times(g(i)-1)}{2}\times\frac{i}{g(i)}$$
化简得：
$$f(i)=f(\frac{i}{g(i)})+\frac{i\times(g(i)-1)}{2}$$

我们注意到，$2\le l\le r\le 5\times 10^6$，所以我们可以做一遍质数筛，预处理出每个数的质因子，然后从 $2$ 到 $n$ 递推即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
constexpr int maxn = 5000010, modd = 1e9 + 7;

int t, l, r, poww, ans;

int p[maxn], book[maxn], cnt;
int g[maxn]; //最小质因数
void prime() { // 质数筛
	for (int i = 2; i <= 5000000; i++) {
		if (!book[i]) {
			p[++cnt] = i;
			g[i] = i; //求最小质因数
		}
		for (int j = 1; j <= cnt && i * p[j] <= 5000000; j++) {
			book[i * p[j]] = 1;
			g[i * p[j]] = p[j]; //求最小质因数
			if (i % p[j] == 0) {
				break;
			}
		}
	}
	return ;
}

int M(int x) { //一个万能取模，非常好用，强烈推荐！！！
	return ((x < 0) ? ((x % modd + modd) % modd) : ((x < modd) ? x : x % modd));
}

int f[maxn];
void getf() { //递推
	f[1] = 0;
	for (int i = 2; i <= 5000000; i++) {
		f[i] = M(f[i / g[i]] + M(i * (g[i] - 1) / 2));
	}
	return ;
}

signed main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr); //读入、输出优化
	
	cin >> t >> l >> r;
	
	prime();
	getf();
	poww = 1; //答案中的指数部分
	for (int i = l; i <= r; i++, poww = M(poww * t)) {
		ans = M(ans + M(poww * f[i])); //统计答案
	}
	
	cout << ans << '\n';
	
	return 0;
}
```
结语：十年 OI 一场空，不开 long long 见祖宗。

---

## 作者：chenzhaoxu2027 (赞：1)

# 题目

[link](https://www.luogu.com.cn/problem/CF822D)

# 分析

先看数据范围，这么小的 $l,r$ 完全可以先预处理出 $f$ 的取值，然后 $O(r-l)$ 来求解。所以说问题变成了预处理 $f$ 的值。

从简单情况开始考虑，假设 $A$ 是质数，那么显然，只能打一轮比赛，就是 $f(A)=\frac{A(A-1)}{2}$。

更进一步，假设 $x$ 是两个质数 $p,q$ 的乘积，其中 $p \le q$，那么有三种情况，打一轮比赛，或是打两场，先分成 $p$ 人一组，或者先分成 $q$ 人一组。

- 如果先分成 $q$ 人一组，有式子 $f(x)=f(q)\times p+f(p)=\frac{pq(q-1)+p(p-1)}{2}$

- 如果先分成 $p$ 人一组，有式子 $f(x)=f(p)\times q+f(q)=\frac{pq(p-1)+q(q-1)}{2}$

容易发现前者比后者劣势，而分成 1 轮比 2 轮劣势。所以说要先按**小**的分组，而且尽量不合并。

再来，假设 $y$ 是两个质数 $p,q,s$ 的乘积，其中 $p \le q \le s$，那么类似的推式子，发现先按 $p$ 分组，然后按 $q$，最后按 $s$ 分组最优秀。$f(y)=f(p)\times qs+f(q) \times s+f(s)$。可以递推发现从小到大按质因数分组最优秀。这种分组方式我们暂且叫做质因数分组。

那么最后，假设 $z$ 是质数 $p$ 与不知道啥数 $r$ 的乘积，其中 $p \le r$。根据上面的理论分析，把 $f(r)$ 的质因数分组形式展开并代入上面的式子，确实有 $f(z)=f(p)\times r+f(r)$。于是我们知道，求出一个数的**最小质因子**然后递推就可以了。求最小质因子可以用埃拉托斯特尼筛法或者欧拉筛法，都能过。我用的是埃拉托斯特尼筛法。

最后把输入的 $t$ 预处理出各个幂次的答案，依次乘积求和就结束了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 1000000007 
int t[5000005]; 
int v[5000005];
int f[5000005];
int Pow[5000005];
int T,l,r;
inline void init(){
	for(int i=2;i<=5000000;i++){//埃拉托斯特尼筛法筛质数
		if(v[i]==0){
			t[i]=(i-1)*i;
			t[i]>>=1;
			for(int j=2*i;j<=5000000;j+=i){
				if(v[j]==0){
					f[j]=i;//记录最小质因子
				}
				v[j]=1;
			}
		}
	}
	for(int i=2;i<=5000000;i++){
		if(v[i]){
			t[i]=t[f[i]]*i/f[i]+t[i/f[i]];//递推求f值
		}
		t[i]%=mod;
	}
}
signed main(){
	cin>>T>>l>>r;
//	T=99359,l=1,r=5000000;//测试极限数据，本机跑了500ms。
	init();
	Pow[0]=1;
	for(int i=l+1;i<=r;i++){//预处理幂次
		Pow[i-l]=Pow[i-l-1]*T;
		Pow[i-l]%=mod;
	}
	int ans=0;
	for(int i=l;i<=r;i++){
		ans+=Pow[i-l]*t[i]%mod;
		ans%=mod;
	}
	cout<<ans;
	return 0;
}
/*
p<=q<=s 
当数X=质数p*质数q时，f(X)=f(p)*q+f(q)
当数Y=质数p*质数q*质数s时，f(Y)=f(p)*qs+f(q)*s+f(s)
所以说，对于任意一个数Z，把Z的所有素因子从小到大依次分组即可得到最小值。 
当合数W=质数p*比p大的不知道什么数a时，有： f(W)=f(p)*a+f(a)。 
*/
```

---

## 作者：myster1ous (赞：0)

[题目](https://www.luogu.com.cn/problem/CF822D)

## 公式化题意

定义 $\text f(i)$：

$$\text f(i) = \min\limits_{\prod s = n, s_i \in \textbf N^+ } \left\{ \sum\limits_{i=1}^{|s|}\frac{s_i \times (s_i - 1)}{2} \times n \times \left(\prod\limits^{i}_{j=1} s_j\right) ^ {-1} \right\}$$

然后给出三个正整数 $t, l, r$，让你求：

$$\left(\sum\limits_{i=l}^r \text f(i) \times t^{i - l}\right) \mod 10^9+7$$

数据范围：$2\leqslant l,r \leqslant 5 \times 10^6, 1 \leqslant t \leqslant 10^9+7$。

## 思路

本题中 $t$ 和最后的求和基本不用管，因为 $l,r \leqslant 5 \times 10^6$，所以我们只需要 $\mathcal{O}(r)$ 的复杂度求出 $\text f(l) \sim \text f(r)$ 就可以了。

---

首先，$s$ 一定是单调上升序列，原因如下：

对于一种基本的情况，$n = a \times b$，$a < b$。

如果 $s$ 中 $a$ 在前，$b$ 在后，那么：

$$
\begin{aligned}
\text f(n) = & \;\frac{1}{2} \times a \times (a - 1) \times b + \frac{1}{2} \times b \times (b - 1)\\
= & \;\frac{1}{2} \times (a^2 \times b - a \times b - b^2)
\end{aligned}
$$

否则：

$$
\begin{aligned}
\text f(n) = & \;\frac{1}{2} \times b \times (b - 1) \times a + \frac{1}{2} \times a \times (a - 1)\\
= & \;\frac{1}{2} \times (b^2 \times a - a \times b - a^2)
\end{aligned}
$$
 
不难发现，因为 $a<b$，$a^2 \times b - b^2$ 明显小于 $b^2 \times a - a^2$，所以把 $a$ 放在 $b$ 的前面会更优。

---

然后，$s$ 中的数一定是 $n$ 的质因数，原因如下：

还是假设 $n = a \times b$，如果 $s$ 中只有一个 $n$，那么：

$$
\begin{aligned} 
\text f(n) = &\; \frac{1}{2} \times n \times (n - 1)\\
= & \; \frac{1}{2} \times (n^2 - n)\\
= & \; \frac{1}{2} \times (a^2 \times b^2 - n) 
\end{aligned}
$$

如果 $s$ 中是 $a$ 和 $b$，假设 $a<b$，$a$ 在 $b$ 的前面，那么：

$$
\begin{aligned}
\text f(n) = & \;\frac{1}{2} \times a \times (a - 1) \times b + \frac{1}{2} \times b \times (b - 1)\\
= & \;\frac{1}{2} \times (a^2 \times b - a \times b - b^2)\\
= & \;\frac{1}{2} \times (a^2 \times b - n - b^2)
\end{aligned}
$$

两边 $- n$ 抵消了，$a^2 \times b - b^2$ 显然小于 $a^2 \times b^2$，所以把 $s$ 中的合数拆掉一定更优。

---

综上所述，$s$ 一定包含 $n$ 的所有质因数，且是按照大小排序的。

所以我们就可以通过 $n$ 的最小质因子来写出一个递推式子：

$$
k = \min_{i|n, i \in \textbf{P}} \{i\}\\

\begin{aligned}
\text{f}(n) & = \sum\limits_{i=1}^{|s|}\frac{s_i \times (s_i - 1)}{2} \times n \times \left(\prod\limits^{i}_{j=1} s_j\right) ^ {-1} \\
& = \frac{k \times (k - 1)}{2} \times \frac{n}{k} + \sum\limits_{i=2}^{|s|}\frac{s_i \times (s_i - 1)}{2} \times n \times \left(\prod\limits^{i}_{j=1} s_j\right) ^ {-1} \\
& = \frac{(k - 1) \times n}{2} + \sum\limits_{i=2}^{|s|}\frac{s_i \times (s_i - 1)}{2} \times n \times \left(\prod\limits^{i}_{j=2} s_j\right) ^ {-1} \times k ^ {-1} \\
 & = \frac{(k - 1) \times n}{2} + \text f\left(\frac{n}{k}\right)
\end{aligned}
$$

---

最后的最后，梳理一下代码的结构：

- 使用线性筛求出 $1 \sim r$ 的全部数的最小质因子。
- 通过最小质因子递推出来 $\text f(1) \sim \text f(r)$。
- 通过题目给出的式子和 $t$ 算出来最终最终的答案。


```cpp
#include <bits/stdc++.h>
#define int long long

constexpr int maxn = 10000007;
constexpr int mod = 1000000007;

int t, l, r;
int f[maxn], minfactor[maxn];
std::bitset<maxn> composite;
std::vector<int> primes; 

signed main() {
    std::cin >> t >> l >> r;

    composite[0] = composite[1] = true;
    for (int i = 2; i <= r; i++) {
        if (!composite[i]) 
            primes.emplace_back(i), minfactor[i] = i;
        for (int j = 0; primes[j] * i <= r; j++) {
            if (!composite[primes[j] * i]) minfactor[primes[j] * i] = primes[j];
            composite[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }    
    }

    f[1] = 0;
    for (int i = 2; i <= r; i++) {
        int mf = minfactor[i];
        f[i] = (mf) * (mf - 1) / 2 * (i / mf) % mod + f[i / mf];
        f[i] %= mod;
    }

    // for (int i = l; i <= r; i++) std::cout << i << " : " << f[i] << "\n";

    int power = 1;
    int ans = 0;
    for (int i = l; i <= r; i++) {
        ans = (ans + power * f[i] % mod) % mod;
        power = power * t % mod;
    }

    std::cout << ans;
    return 0;
}
```

---

## 作者：KrOX (赞：0)

乍一看题目所求的式子还以为是什么神奇的推式子题，其实就是把$f(l)$到$f(r)$分别求出来，是个最优化问题。

DP式很方便得出：$f(i)=\mathop{min}\limits_{d|i}\{f(\frac{i}{d})\times\frac{i}{d}\times\frac{d(d-1)}{2}\}$

不是常规的DP方程，官方题解给了枚举因数转化为枚举倍数的优化，做到了$log$级别，我们尝试观察最优化目标本身。

第一个问题，一个数拆的次数多好，还是少好？

我们简单比较两个式子即可：$k\times\frac{ab-1}{2}$和$k\times\frac{a-1}{2}+\frac{k}{a}\times\frac{b-1}{2}$。进行一些简单的化简发现前者恒大于后者。故拆的次数越少越好，于是DP式中不需枚举约数，枚举素因数即可。

第二个问题，先拆出来的素因数大好，还是小好？

同样比较两个式子（不妨设$a>b$）：$k\times\frac{a-1}{2}+\frac{k}{a}\times\frac{b-1}{2}$和$k\times\frac{b-1}{2}+\frac{k}{b}\times\frac{a-1}{2}$。化简同样不难，作差法，因式分解后即观察$(a-b)(a-1)(b-1)$的正负，显然为正，于是先拆出来的素因数小好，DP式得到了最终的化简$f(i)=f(\frac{i}{p_{min}})+ i \times\frac{(p_{min}-1)}{2}$

最优化问题转化为了求一个数的最小质因数，考虑到线性筛中所有合数正用的是它最小素因数筛掉的，于是我们另开一个数组记录$p_{min}$即可。

总时间复杂度$O(r)$。~~爆踩标算(bushi~~

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll t,l,r;

const int maxn = 5e6+5;
const ll mod = 1e9+7;

int prime[maxn],pt,sm[maxn];

void shai(){
    for(int i=2;i<=maxn-5;i++){
        if(!vst[i]) prime[++pt]=i;
        for(int j=1;j<=pt&&i*prime[j]<=maxn-5;j++){
            vst[i*prime[j]]=1;
            sm[i*prime[j]]=prime[j];
            if(i%prime[j]==0) break;
        }
    }
}

ll f[maxn],ans;

int main(){

    shai();
    cin>>t>>l>>r;
    for(int i=2;i<=r;i++){
        if(!sm[i]) sm[i]=i;
        f[i]=f[i/sm[i]]+((ll)i*((ll)sm[i]-1)/2)%mod;
        f[i]%=mod;
    }
    ll nw=1;
    for(int i=l;i<=r;i++){
        ans+=nw*f[i]%mod;
        ans%=mod;
        nw=nw*t%mod;
    }
    cout<<ans;
    return 0;
}


```

---

## 作者：WorldMachine (赞：0)

考虑到 CF 的神机以及调和级数的小常，我们尝试用 $\mathcal O(n\log n)$ 的做法碾过去这道题。

对于 $i$ 的最小操作次数 $f_i$，它可以向 $i$ 的所有倍数 $ij$ 转移：
$$
f_{ij}\leftarrow\min(f_{ij},f_i+\dfrac12ij(j-1))
$$
然后就过了。最慢点只用了 $890$ 毫秒，还是比较稳的。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5000005, p = 1000000007;
int t, l, r, q = 1, s;
ll f[N];
int main() {
	scanf("%d%d%d", &t, &l, &r);
	memset(f, 0x7f, sizeof(ll) * (r + 1));
	f[1] = 0;
	for (int i = 1; i <= r; i++) {
		for (int j = 2; i * j <= r; j++) f[i * j] = min(f[i * j], f[i] + (1ll * j * (j - 1) >> 1ll) * i);
	}
	for (int i = l; i <= r; i++) {
		s = (s + (ll)q * (f[i] % p)) % p;
		q = (ll)q * t % p;
	}
	printf("%d", s);
}
```

---

## 作者：AC_love (赞：0)

首先我们能得到一个显然的递推式。

假设把 $i$ 人分成 $\dfrac{i}{k}$ 组，那么每组就有 $k$ 个人，每组内部需要比较 $\dfrac{k \cdot (k - 1)}{2}$ 次。那么递推式显然就是：

$$f(i) = \underset{k\ |\ i}{\min}\ f(\dfrac{i}{k}) + \dfrac{i}{k} \cdot \dfrac{k(k - 1)}{2}$$

我们知道，枚举因数是 $O(\sqrt{n})$ 的，直接枚举因数跑记忆化搜索复杂度就是 $O(n \sqrt{n})$，直接 T 飞不解释。

不过可以稍加转化，从枚举因数变成枚举倍数，这样的话复杂度就变成了 $O(n \log n)$，由于 CF 的评测机非常给力，所以 $5 \times 10^6$ 也能过。

凭借 CF 性能不错的评测机，我们可以 $O(n \log n)$ 艹过 $5 \times 10^6$ 的数据，但是难道就没有更好的方法了吗？

显然是有的，这道题看起来就很像结论题的样子，如果不好好利用一下这道题的性质那岂不就浪费了。

接下来我们开始推结论：

首先，我们应该尽可能多地拆，还是尽可能少地拆？

我们可以设现在有 $a \cdot b$ 个人（$a \ge b \ge 2$），如果我们把这些人全部放在一组的话，需要比较 $\dfrac{(a \cdot b)(a \cdot b - 1)}{2}$ 次。

这玩意等于：

$$\dfrac{a}{2} \cdot (ab^2 - b)$$

而如果我们把这些人拆成 $a$ 组，每组 $b$ 人，需要比较多少次呢？

第一轮，对于每一组，我们都需要比较 $\dfrac{b(b - 1)}{2}$ 次，一共 $a$ 组，总共 $a \cdot \dfrac{b(b - 1)}{2}$ 次。

第二轮，只有一组，一共 $a$ 人，需要比较 $\dfrac{a(a - 1)}{2}$ 次。

故总共需要比较 $a \cdot \dfrac{b(b - 1)}{2} + \dfrac{a(a - 1)}{2}$ 次。

这玩意稍加化简，得到：

$$\dfrac{a}{2} \cdot (b^2 - b + a - 1)$$

我们用上面那玩意减去刚得到的东西：

$$\dfrac{a}{2} \cdot (ab^2 - b) - \dfrac{a}{2} \cdot (b^2 - b + a - 1)$$

最后得到：

$$\dfrac{a}{2} \cdot (ab^2 - a - b^2 + 1)$$

$\dfrac{a}{2}$ 肯定大于 $0$，关键看后一部分。

我们发现，后面一部分形如 $xy - x - y + 1$，根据初中知识，这玩意可以因式分解：

$$xy - x - y + 1 = x(y - 1) - (y - 1) = (x - 1)(y - 1)$$

那么原式可以转化为：

$$\dfrac{a}{2} \cdot (a - 1)(b ^ 2 - 1)$$

我们发现三部分都是严格大于 $0$ 的，那么这个数一定是个正数。

所以：

$$\dfrac{a}{2} \cdot (ab^2 - b) - \dfrac{a}{2} \cdot (b^2 - b + a - 1) > 0$$

所以：

$$\dfrac{(a \cdot b)(a \cdot b - 1)}{2} > a \cdot \dfrac{b(b - 1)}{2} + \dfrac{a(a - 1)}{2}$$

所以我们得到结论：把人拆成多组分别比一定比一组一群人一起比更优。所以我们能多拆一定要多拆。

那么我们就直接拆所有质数就可以了。

第二个问题：我们应该拆 $a$ 组，每组 $b$ 人，还是拆 $b$ 组，每组 $a$ 人呢？

我们可以把式子列出来：

第一种情况的比较数：

$$\dfrac{a}{2} \cdot (b^2 - b + a - 1)$$

第二种情况的比较数：

$$\dfrac{b}{2} \cdot (a^2 - a + b - 1)$$

这玩意怎么比较呢？

我们不妨同时乘个 $2$，然后一式减二式：

$$ab^2 - ab + a^2 - a - a^2b + ab - b^2 + b$$

这个式子经过化简得到：

$$-ab(a - b) + (a + b)(a - b) - (a - b)$$

提取公因式：

$$-(a - b)(ab - a - b + 1)$$

后面的括号可以因式分解：

$$-(a - b)(a - 1)(b - 1)$$

我们发现这玩意是个负数。

因此一式小于二式。

所以第一种情况比较数比较少。

所以我们拆分的时候应该优先拆分人数更少的。

那么这个问题的解决方案就十分显然了：

对于任意一个数，我们能拆就拆，拆的时候每组的人数都是它最小的质因数，知道拆不下去为止。

DP 式子为：

$$f(i) = f(\dfrac{i}{k}) + \dfrac{i}{k} \cdot \dfrac{k(k - 1)}{2}$$

其中 $k$ 是 $i$ 最小的质因子。

问题转化为如何快速找到一个数最小的质因子。

这玩意显然可以快速筛出来。

如果用欧式筛的话本题复杂度为 $O(n)$，如果换成埃氏筛会稍微慢一点，不过其实也无伤大雅。

代码实现如下：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 1e9 + 7;
const int N = 5e6 + 500;
int memory[N];
int mp[N];
int m;

void sieve()
{
	for(int i = 2; i <= 5e6 + 1; i = i + 1)
		if(mp[i] == 0)
			for(int j = i * 2; j <= 5e6 + 1; j = j + i)
				if(mp[j] == 0)
					mp[j] = i;
}

int f(int x)
{
	if(x == 1)
		return 1;
	if(memory[x])
		return memory[x];
	if(!mp[x])
		return memory[x] = ((x) * (x - 1) / 2ll) % mod;
	return memory[x] = f(x / mp[x]) + ((x * (mp[x] - 1) / 2ll) % mod) % mod;
}

int l, r, t;
int ans;

signed main() 
{
	m = 1;
	sieve();
	cin >> t >> l >> r;
	for(int i = l; i <= r; i = i + 1)
		ans += f(i) * m % mod,
		m *= t,
		m %= mod,
		ans %= mod;
	cout << ans;
	return 0;
}
```

---

## 作者：_edge_ (赞：0)

我不会拆柿子，我也不会分析性质。

咋办？我们先写暴力。

相信各位应该都会这个的 DP 柿子。

设 $f_i$ 表示有 $i$ 个人的时候需要比较最少次数。

转移就枚举其约数即可，然后用那个式子稍微算一算就可以了。

```cpp
for (int i=2;i<=n;i++) {
		f[i]=1e9;
		for (int j=1;j*j<=i;j++) {
			if (i%j) continue;
			int X=j;
			if (X>1)
				f[i]=min(f[i/X]+X*(X-1)/2,f[i]);
			
			X=i/j;
			f[i]=min(f[i/X]+X*(X-1)/2,f[i]);
		}
}
```

核心代码如上。

那么我们进一步考虑优化这个过程。

我们会发现，这个东西似乎挺难搞的，并且我们的复杂度最好是线性的。

如果说要求 $O(n \log n)$ 的话可以考虑刷表，然后调和级数即可。

那么我们先打表打出来它的所有转移决策点。

```cpp
cin>>n;
	for (int i=2;i<=n;i++) {
		f[i]=1e9;
		for (int j=1;j*j<=i;j++) {
			if (i%j) continue;
			int X=j;
			if (X>1)
				f[i]=min(f[i/X]+X*(X-1)/2,f[i]);
			
			X=i/j;
			f[i]=min(f[i/X]+X*(X-1)/2,f[i]);
		}
//		cout<<i<<" fad?\n";
		for (int j=1;j*j<=i;j++) {
			if (i%j) continue;
			int X=j;
			if (X>1)
				if (f[i]==f[i/X]+X*(X-1)/2) cout<<X<<" ?\n";
			
			X=i/j;
			if (f[i]==f[i/X]+X*(X-1)/2) cout<<X<<" ?\n";
		}
		cout<<f[i]<<" "<<i<<" ?\n";
	}
```

打表之后发现一件非常有趣的事情，就是决策点有一个一定是最小质因数。

猜一下上面这个结论，然后利用欧拉筛把最小质因子筛出来，大力转移。

恭喜你通过了这道题。

大致证明就是除法一定是下降的比较快的，因此我们应该把旁边那个加法给缩小，最好的情况是最小。

同时这题要线性处理逆元，这里给出一个比较好的做法，就是先求 $n!$ 的逆元然后再乘上 $(n-1)!$，这两个东西可以 $O(n)$ 递推求得。

[code](https://codeforces.com/contest/822/submission/176869683)

---

## 作者：囧仙 (赞：0)

## 题目大意

$n$个女生，进行若干论选美。选美的方式如下：

- 设当前人数为$m$，选择一个正整数$x(m\ge x>1, x\ |\  m)$，划分为$\frac{m}{x}$组，每组$x$个人。

- 每一组中的女生两两比较，共进行$\frac{x\times(x-1)}{2}$次比较。最终每一组只会有$1$名女生晋级。

- 所有晋级的女生继续进行选美，直到只剩下一名女生。

设初始为$n$名女生时最少的**总比较次数**为$f(n)$，求$\sum_{i=l}^r t^{i-l}\times f(i) \mod (10^9+7)$。

## 题解

根据最终需要我们计算的式子，显然需要求出$x\in [l,r]$时**所有**的$f(x)$。不过$f(x)$比较复杂，让我们先证明几个结论。

### $0.$简单的化简

设总共$m$人，$x$个人分为一组，则一共需要比较$\frac{m}{x}\times \frac{x\times (x-1)}{2}=\frac{m\times (x-1)}{2}$。

这步化简主要是为了方便下面的推算，并没有什么难度。

### $1.$每次分组的人数按照从小到大排列

假设目前有$m$轮。进行两次选美，分别是$a$个人一组、$b$个人一组。$(a\ge b>1)$

先$a$后$b$，总比较次数为：

$$\frac{m\times (a-1)}{2}+\frac{m\times (b-1)}{2\times a} \kern{50pt} \cdots \cdots (1) \kern{-50pt}$$

先$b$后$a$，总比较次数为：

$$\frac{m\times (b-1)}{2}+\frac{m\times (a-1)}{2\times b}\kern{50pt} \cdots \cdots (2) \kern{-50pt}$$

两式相减，得到：

$$\begin{aligned}(1)-(2)&=\frac{m}{2\times a\times b}\times(a^2\times b-a\times b+b^2-b+a\times b^2+a\times b-a^2+a)\cr&=\frac{m}{2\times a\times b}\times [a\times b\times (a-b)-(a+b)\times (a-b)+(a-b)]\cr&=\frac{m}{2\times a\times b}\times (a-b)\times (a\times b-a-b+1)\cr&=\frac{m}{2\times a\times b}\times (a-b)\times (a-1)\times (b-1)\end{aligned}$$

所以$(1)\ge(2)$，因而$a<b$时才能使得总比较次数最少。

### $2.$如果$x$为合数，就拆分为若干轮选美

不妨设$x=a\times b\  (1< b\le a <x)$，当前人数为$m$。

由结论$1$可以得到，先$b$后$a$比先$a$后$b$更好。再我们考虑每组$a\times b$个人的情况。

每组$a\times b$个人需要的比较次数：

$$\frac{m\times (a\times b-1)}{2} \kern{50pt} \cdots \cdots (3) \kern{-50pt}$$

与先$b$后$a$的情况相减：

$$\begin{aligned}(3)-(2)&=\frac{m}{2\times b}\times (a\times b^2-b-b^2+b-a+1)\cr
&=\frac{m}{2\times b}\times[(a-1)\times b^2-(a-1)]\cr
&=\frac{m}{2\times b}\times (a-1)\times (b+1)\times (b-1)\end{aligned}$$

因此，$(3)>(2)$，也就是说，拆成两组总是更优。

---

在证明完上述结论后，我们能得到一个初步的算法：

设$x=\prod_{i=1}^k p_i$，其中$p_i$为质数。那么依次化为$p_1,p_2,\cdots,p_k$个人为一组，可以使得最终的比较次数最少。

考虑区间筛素数的思想。即用$1\sim \sqrt{R}$内的所有质数，筛一遍$[L,R]$内的数字，并统计答案。具体来说，我们用$A_i$表示$f(i)$的贡献，$B_i$表示数字$i$目前还剩下多少。每次用$p$筛一遍含有因子$p$的数字，更新答案（$A_i\gets A_i+\frac{B_i\times (p-1)}{2},B_i\gets \frac{B_i}{p}$）。需要注意的是，每个数字可能有若干个质因子$p$，因此需要使用$p^2,p^3\cdots$继续处理。最后$B_i$剩下的要么是$1$，要么是它最大的质因数。处理一遍即可。

最后统计答案就可以了。时间复杂度与埃氏筛法相似，约为$\mathcal O(N \log \log N)$。

另外这里提供一个偷懒的小技巧：由于我们每次要访问$A_{l..r}$，而数组下标从$0$开始非常不方便。于是我们用指针$ * P$指向$A_0-l$，那么访问$P_x$就相当于访问了$A_{x-l}$。因为指针只表示地址，因此不会产生数组越界等问题。

## 参考代码

```
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
const int MAXN =5e6+3,MAXM=5e5+3,MOD=1e9+7;
int t,l,r,m,M1[MAXN],M2[MAXN],*A,*B,x=1,ans;
bool V[MAXM]; int P[MAXM],n;
int main(){
    t=qread(),l=qread(),r=qread();
    A=M1-l,B=M2-l,m=sqrt(r)+1;
    up(2,m,i){
        if(V[i]) continue; P[++n]=i;
        up(2,m/i,j) V[i*j]=true;
    }
    up(l,r,i) B[i]=i;
    up(1,n,i){
        LL p=P[i]; while(p<=r){
            int a=(l-1)/p+1,b=r/p;
            up(a,b,j) A[p*j]=((LL)A[p*j]+(LL)B[p*j]*(P[i]-1)/2)%MOD,B[p*j]/=P[i];
            p*=P[i];
        }
    }
    up(l,r,i) A[i]=((LL)A[i]+(LL)B[i]*(B[i]-1)/2)%MOD;
    up(l,r,i) ans=((LL)ans+(LL)x*A[i])%MOD,x=((LL)x*t)%MOD;
    printf("%d\n",ans);
    return 0;
}
```








---

