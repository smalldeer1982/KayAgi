# Intercity Travelling

## 题目描述

Leha 正在计划从莫斯科到萨拉托夫的旅程。他讨厌火车，所以决定开车从一个城市到另一个城市。

从莫斯科到萨拉托夫的路线可以看作是一条直线（虽然实际上并不是很直，但在本题中我们认为它是直线），两地之间的距离为 $n$ 千米。假设莫斯科位于坐标 $0$ 千米处，萨拉托夫位于坐标 $n$ 千米处。

长时间驾驶可能非常辛苦。具体来说，如果 Leha 自上一次休息后已经连续行驶了 $i$ 千米，那么他认为接下来第 $i+1$ 千米的难度为 $a_{i+1}$。保证对于每个 $i \in [1, n-1]$，都有 $a_i \le a_{i+1}$。旅程的总难度定义为每一千米的难度之和。

幸运的是，在莫斯科和萨拉托夫之间可能有一些休息站。每一个从 $1$ 到 $n-1$ 的整数点都可能有一个休息站。当 Leha 到达休息站并休息后，接下来的第一千米难度为 $a_1$，第二千米难度为 $a_2$，以此类推。

例如，如果 $n=5$，在坐标 $2$ 处有一个休息站，则旅程的总难度为 $2a_1 + 2a_2 + a_3$：第一千米难度为 $a_1$，第二千米难度为 $a_2$，然后 Leha 休息，第三千米难度为 $a_1$，第四千米难度为 $a_2$，最后一千米难度为 $a_3$。再如：如果 $n=7$，在坐标 $1$ 和 $5$ 处有休息站，则旅程的总难度为 $3a_1 + 2a_2 + a_3 + a_4$。

Leha 并不知道哪些整数点有休息站，所以他必须考虑所有可能的情况。显然，休息站的分布有 $2^{n-1}$ 种不同的方案（如果存在某个点 $x$，在两个方案中恰好只有一个包含休息站，则这两个方案不同）。Leha 认为所有这些分布是等概率的。他想计算 $p$——旅程难度的期望值。

显然，$p \cdot 2^{n-1}$ 是一个整数。你需要计算它对 $998244353$ 取模的结果。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
5
```

## 样例 #2

### 输入

```
4
1 3 3 7
```

### 输出

```
60
```

# 题解

## 作者：Zi_Gao (赞：7)

## 前言

这种推式子的题只给结论？~~有没有素质~~

## 正文

### 题目分析

由于一号点出发相当于一号点必须休息，那么只剩下了 $n-1$ 个点，总的选择方案是 $2_{n-1}$，而题目要求答案乘上 $2_{n-1}$ 相当于消掉了，只需要统计每种方案的代价和即可。

经典套路分开讨论每个 $a_i$ 的贡献。对于每个 $a_i$ 同样进行拆分，考虑这个 $a_i$ 在哪个位置会造成贡献，既然能产生 $a_i$ 的贡献，说明前面一定是 $a_1,a_2,\cdots,a_{i-1}$ 那么相当于固定了 $i$ 长度序列不能动，中间不能休息，并且只有这个要求，其他地方随便选，休息不休息都可以。但是对于一号点要钦定必须休息所以需要分开讨论一下，设选择作为 $a_i$ 的这个点位置在 $pos$：

1. 当 $pos=i$ 时，满足两个条件，剩下随便选，答案为 $2^{n-i}$，并且这种情况会出现一次。

2. 其他情况，需要满足一号点必须休息，并且固定了长度为 $i$ 只有 $n-i-1$ 个地方随便选了，答案为 $2^{n-i-1}$，并且这种情况会出现 $n-i$ 次。

那么总的答案为：

$$ans=\sum_{i=1}^{n}\left(2^{n-i}+\left(n-i\right)\times2^{n-i-1}\right)\times a_i$$

### 代码实现

注意 $n-i-1$ 可能为负数，但是并不需要逆元因为这时 $n-i$ 为 $0$。

AC CODE

```cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE long long
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

long long p[1000010];

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    register int i,n=read();
    const long long mod=998244353;
    register long long ans=0;
    p[0]=1;
    for(i=1;i<=n;++i) p[i]=(p[i-1]<<1)%mod;
    for(i=1;i<=n;++i)
        (ans+=(p[n-i]+((n-i-1)>=0?(p[n-i-1]*(n-i)):0))%mod*read())%=mod;

    print(ans);

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

---

## 作者：spider_oyster (赞：3)

**核心代码甚至有两行！！！**

设一个选择休息地的集合 $S$，若第 $i$ 位为 0 表示不休息，为 1 表示在当地休息，这里规定 $S_1=1$。

若 $S$ 里存在连续子串 ```100...00```，其中有 $x$ 个 0，那么会对答案贡献 $a_{x+1}$。

考虑对每个 $a_i$ 分别算贡献。枚举对应子串出现的位置，然后其他位置随便选。注意规定了 $S_1=1$，拿出来单独考虑。

答案为 $\sum\limits_{1\leq i \leq n} (2^{n-i}+2^{n-i-1}\cdot (n-i))\cdot a_i$。

复杂度线性。代码就不贴了。

---

## 作者：YuntianZhao (赞：3)

# CF1009E

首先$p \cdot 2^{n - 1}$即期望乘上全部可能，就是各个可能的困难度的和。

可以用数学方法（打表找规律）...

得到式子后$O(n)$求解，$ans = \sum_{i = 1} ^ {n} (2^{n-i + 1}+(n - i) \cdot 2^{n - i}) \cdot a_i$，其中$a_i$甚至不用开数组。

```c++
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000005;
const long long mod = 998244353;

long long p[maxn];

int main() {
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  p[1] = 1;
  for (int i = 1; i <= n; i++) {
    p[i + 1] = p[i] * 2 % mod;
  }
  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    long long x;
    cin >> x;
    ans += (p[n - i + 1] + (n - i) * p[n - i]) % mod * x % mod;
  }
  ans %= mod;
  cout << ans;
  return 0;
}

```





---

## 作者：__staring__ (赞：2)

根据题意，显然所求答案 $p \cdot 2^{n-1}$ 即为所有休息室出现情况的代价之和。

考虑位置 $i$ 对总代价的贡献 $f_i$ ，其与前第一个出现的休息室 $j$ 有关，则枚举 $j$ ，有$f_i = 2^{n-i} \cdot a_i + \sum_{j=1}^{i-1} 2^{n-j-1} \cdot a_j$ 。

即位置 $1$ 到位置 $i$ 均不出现休息室的情况有 $2^{n-i}$ 种，贡献均为 $a_i$ ，位置 $i$ 与前 $j-1$ 个位置均不出现休息室，而位置 $i-j$ 出现休息室的情况有 $2^{n-j-1}$ 种，其贡献为 $a_j$ 。

那么答案 $res = \sum_{i=1}^n 2^{n-i} \cdot a_i + \sum_{j=1}^{i-1} 2^{n-j-1} \cdot a_j$ 。

即 $res = (a_n) +(\sum_{i=1}^{n-1} 2^{n-i} \cdot a_i) + (\sum_{i=1}^{n-1} \sum_{j=1}^{i-1} 2^{n-j-1} \cdot a_j)$。

发现二三部分有相似部分，则记 $g_i = \sum_{j=1}^i 2^{n-j-1} \cdot a_j$ 。

得 $res = a_n + 2g_{n-1} + \sum_{i=1}^{n-1} g_i$ 。

$g_i$ 可递推得到，时间复杂度 $O(n)$ 。

~~话说码风这么抽象常数又大的代码真的有人会看吗。~~

```cpp
#include<bits/stdc++.h>
using namespace std;

constexpr int mod=998244353,inv2=499122177;

int main()
{
    int n;
    scanf("%d",&n);

    //快速幂得到 2^(n-1)
    int pow2=1;
    for(int i=n-1,v=2;i;i>>=1,v=1ll*v*v%mod)
        if(i&1)pow2=1ll*pow2*v%mod;
    
    //sum1表示gi sum2表示sigma gi val为ai
    int sum1=0,sum2=0,val;
    while(--n)
    {
        scanf("%d",&val);
        pow2=1ll*pow2*inv2%mod;
        sum1=(sum1+1ll*pow2*val%mod)%mod;
        sum2=(sum2+sum1)%mod;
    }
    //最后的an不进行g的计算，单独输入
    scanf("%d",&val);
    printf("%d",((sum1*2%mod+sum2)%mod+val)%mod);

    return 0;
}
```

---

## 作者：_FL_ (赞：2)

## $ \texttt{CF1009E} $  

---

### 思路：  

这里分享我的猜结论做法及结论证明。感觉这题评 $ 2000 $ 略低了？  

首先发现可以直接计算每个 $ a_i $ 的贡献次数，最后加起来。  

然后发现 $ a_n $ 的贡献次数是 $ 1 $，并且从 $ n $ 到 $ 1 $ 贡献次数逐渐减少。所以设 $ dp_i $ 表示 $ a_{n-i+1} $ 的贡献次数，$ dp_1=1 $。  

这时套入 $ n=4 $，手算得到 $ dp $ 数组：  

$ 1,3,8,20 $  

这里就大概尝试一下，应该是比较容易发现规律的，$ dp_i=2dp_{i-1}+2^{i-1} $。  

然后浅写一下交上去发现过了，很神奇。于是开始尝试证明。以下为证明。  

首先，对于 $ dp_{i-1} $ 的每一种合法方案中出现的 $ a_1 $ 到 $ a_{n-i+2} $ 这一段，$ a_1 $ 到 $ a_{n-i+1} $ 这一段显然也同样地出现了一次。因此 $ dp_i $ 要加上 $ dp_{i-1} $。  

然后，我们将 $ dp_{i-1} $ 的每一种合法方案中出现的所有 $ a_1 $ 到 $ a_{n-i+2} $ 这一段中的最后一段的最后一步，即 $ a_{n-i+2} $，改为休息，即 $ a_1 $，这样必定产生不同的合法的方案且贡献次数相同。因此，$ dp_i $ 再次加上 $ dp_{i-1} $，至此，$ dp_i=2dp_{i-1} $。  

那么这个 $ 2^{i-1} $ 是怎么来的呢？以上的统计还有一点缺漏，比如 $ a_1 $ 到 $ a_{n-i+1} $ 这一段被放在最后，这就是 $ dp_{i-1} $ 考虑不到的情况，这种情况下前面的 $ i-1 $ 位可以任意选择休息或者不休息，所以是 $ 2^{i-1} $ 次的贡献。  

感觉好像很对，但是仔细想又会发现这样的统计似乎有问题，比如：  

$ \cdots,a_{1},\cdots,a_{n-i+1},a_1,\cdots,a_{n-i+2} $  

这种情况下 $ dp_{i-1} $ 不会考虑到前面这段 $ a_1 $ 到 $ a_{n-i+1} $ 的贡献。这个问题我想了很久，然后发现一件事情，我们统计改变后序列的贡献和是与改变前序列的贡献无关的，也就是说对于这种情况，会存在另一种方案，比如：  

$ \cdots,a_1,\cdots,a_{n-i+2},a_1,\cdots,a_{n-i+1} $  

这样两种情况将 $ a_{n-i+2} $ 改为 $ a_1 $ 后是一样的，就是说前面所有的 $ a_1 $ 到 $ a_{n-i+1} $ 段都有对应的序列使得改变后可以计算到贡献。讲得可能不太好，实在不懂可以自己拿样例推一次，我就是这么干的。  

那么就结束了，直接用式子实现即可，我写的 $ O(n\log n) $，事实上直接预处理 $ 2^{i-1} $ 就可以 $ O(n) $。  

---

### 代码：  

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;
const int N = 1e6 + 5;
int s1[N], n, ans;
int qpow(int x, int k);
int main() {
	int T1 = 1;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &s1[i]);
	}
	for (int i = 1; i <= n; i++) {
		ans = (ans + 1ll * T1 * s1[n - i + 1] % mod) % mod;
		T1 = (2ll * T1 % mod + qpow(2, i - 1)) % mod;//此时T1即为dp_i
	}
	printf("%d", ans);
	return 0;
}
int qpow(int x, int k) {
	int Ans = 1;
	for (int i = k; i; i >>= 1, x = 1ll * x * x % mod) {
		if (i & 1) {
			Ans = 1ll * Ans * x % mod;
		}
	}
	return Ans;
}
```


---

## 作者：star_magic_young (赞：2)

这道题先考虑一种暴力n方做法

设$f_i$表示到$i$点所有情况的困难度之和($f_0=0$),$pre_i=\sum_{j=1}^{i} a_j$

考虑从点$j$中途不经过休息站到达$i$,可以得到$$f_i=pre_i+\ \sum_{j=1}^{i-1} f_j+2^{j-1}pre_{i-j}$$

(要乘$2^{j-1}$是因为到第$j$个点有那么多方案)

这个很容易就能优化到$O(n)$

记$g_i=\sum_{j=1}^{i} f_j,h_i=pre_i+\sum_{j=1}^{i-1} 2^{j-1}pre_{i-j}=\sum_{j=1}^{i}2^{i-j}a_j=2h_{i-1}+a_i$

所以$$f_i=g_{i-1}+h_i$$

直接$O(n)$救星了,也不要多开数组


```cpp
#include<bits/stdc++.h>
#define LL long long
#define il inline
#define re register
#define db double

using namespace std;
const int mod=998244353,N=1000000+10;
il LL rd()
{
    re LL x=0,w=1;re char ch;
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*w;
}
LL n,a[N],an,ss,bb; //乱定变量名(逃

int main()
{
  n=rd();
  for(int i=1;i<=n;i++) a[i]=rd();
  for(int i=1;i<=n;i++)
    {
      bb=((bb<<1)%mod+a[i])%mod;
      an=(ss+bb)%mod;
      ss=(ss+an)%mod;
    }
  printf("%lld\n",an);
  return 0;
}
```

---

## 作者：MyukiyoMekya (赞：1)

这里提供一种过不了的做法，但是我看题解区没有人这么做（可能就是做不了，也可能是我不会优化）

首先 $p \cdot 2^{n - 1}$ 即期望乘上全部可能，就是各个可能的困难度的和。

我们把样例 $2$ 扒过来

有8种可能的代价分别为 `1 3 3 7`、`1 1 3 3`、`1 3 1 3`、`1 1 1 3`、`1 3 3 1`、`1 1 3 1`、`1 3 1 1`、`1 1 1 1`，期望为 `7.5`，答案为 `60`。

这里有 $8$ 组数字，我们先把 $1$ 的出现次数统计一下

出现 $4$ 次 $1$ 的组数：1

出现 $3$ 次 $1$ 的组数：3

出现 $2$ 次 $1$ 的组数：3

出现 $1$ 次 $1$ 的组数：1

那么贡献就是 $((1)*4+(3)*3+(3)*2+(1)*1)*1=8$

$1,3,3,1$ 和 $4$ ，然后我就想到了**杨辉三角的第** $4$ **行恰好是** $1,3,3,1$ !!!!!!

剩下 3，3，7分别是 $((1)*3+(2)*2+(1)*1)*3$ ，$((1)*2+(1)*1)*3$，$((1)*1)*7$

于是，一个规律出来了

把杨辉三角第 $i$ 行中 $\sum _{j=1}^i{yhsj[i][j]*j}$ 求出来，记作 $sum[i]$，
那么答案就是 $\sum _{i=1}^n{(a[i]*sum[n-i+1])}$ 

#### 但是，这个做法是n方的QAQ

我也不知道怎么优化，可能我比较菜，以后如果找到方法会回来更新

放上代码：

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define int long long
using namespace std;
const int p=998244353;
template <class t> inline void read(t &s)
{
	s=0;
	reg int f=1;
	reg char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	s*=f;
	return;
}
int yhsj[2050][2050];
int a[2050];
signed main(void)
{

	for(int i=1;i<2050;++i)
		yhsj[i][1]=yhsj[i][i]=1;
	for(int i=2;i<2050;++i)
		for(int j=2;j<i;++j)
			yhsj[i][j]+=(yhsj[i-1][j-1]+yhsj[i-1][j])%p,
			yhsj[i][j]%=p;

	int n;
	reg int ans=0;
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	for(int i=1;i<=n;++i)
	{
		reg int t=0;
		for(int j=1;j<=i;++j)
			t=(t+j*yhsj[i][j]%p)%p;
		ans+=t*a[n-i+1]%p;
		ans%=p;
	}
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：2020kanade (赞：0)

前言：笔者刚脱离高考深海，正在复健，因此题解可能详细到了啰嗦的地步，比较适合和笔者一样的复健人或者基础不好或完全不懂人。

提供一个粗暴的 DP 写法。

令初始位置标号为 $1$，设走到位置 $i$ 时所有走法的代价的期望之和为 $dp_i$，下面对转移方程的推导只需要高中理科数学知识：

首先注意，按照题目定义，$a$ 数组是具体地每一步的代价，题目中的意思其实就是连续走的第 $s$ 步代价是 $a_s$，注意，参照常识，这里显然没有对第 $0$ 步进行定义。那么，连续走若干步的总代价是 $a$ 数组的前缀和，建立前缀和数组 $s$，即 $s_i=\sum_{j=1}^{i}a_j$。

之后，考虑转移：这种线性模型题显然是分段模型，前继状态清晰——所有有可能的上次的位置，显然是个前缀；附加贡献清晰——从前继状态走到当前位置的位移长度的期望。本身看着不太难，大概一写方程就会发现有点复杂。

如果有写过高中数学题的经验，期望之间直接搞是很难算的，由于期望在这种离散情景下不严谨地可以说是用概率和实际值的积定义的，可以在转移的时候把式子拆回这两个层面。

考虑概率，之前的每一步都有可能休息，设此时走了 $s$ 步，那么休息方式的数量等同于大小为 $s$ 的集合的子集个数（包含自身与空集，对应一步一歇和打死不歇的情况），为 $2^s$ ~~（若不知道请补习高中数学集合论部分，推不出来顺便补习加法原理与乘法原理）~~，注意最开始的 DP 状态定义的下标是位置，从初始位置走到当前位置的步数为当前位置标号减一。可见，知道位移就可以在常数时间或次常数时间复杂度内算出概率。

实际值的话，一段位移的贡献是区间和，前继状态是期望值，算出来实际值也很简单：将其视作从初始位置到前继下标位置的位移，知道位移就知道步数，概率也就能算出来，直接除下去就是。

注意这里还有一个坑：状态定义是期望和，转化成实际值是所有实际值的和，位移贡献一次一般是不够的（除非可能性只有一种），需要对每个可能性都产生贡献，也就是说，位移对状态实际值的贡献是位移长度与该状态包含的可能性个数之积（说通俗一点，方案数），后者显然是概率的倒数。

现在，推出方程：如果没有前继，也就是直接从初始位置走，位移为 $i$，贡献的期望是 $\frac{s_{i}}{2^{i-1}}$；否则，设前继状态为 $dp_j$，其贡献转化为实际值为 $\frac{dp_j}{\frac{1}{2^{j-1}}}=dp_j \times 2^{j-1}$，从前继走到当前位置的位移为 $i-j+1$,步数为 $i-j$，实际值为 $s_{i-j}$，前继包含方案数按上文为 $2^{j-1}$，则位移的贡献为 $s_{i-j}\times 2^{j-1}$，该前继贡献的实际值为 $dp_{j}\times 2^{j-1}+s_{i-j}\times 2^{j-1}$，转为期望值为 $\frac{dp_{j}\times 2^{j-1}+s_{i-j}\times 2^{j-1}}{2_{i-1}}$。

综上，考虑所有前继，可得出转移方程：

$dp_{i}=\frac{s_{i}}{2^{i-1}}+\sum_{j=1}^{i-1}\frac{dp_{j}\times 2^{j-1}+s_{i-j}\times 2^{j-1}}{2_{i-1}}$

复杂度看起来非常平方，这里用一些手法把 DP 过程本身优化到线性或次线性复杂度：

把式子后半截那一堆分数拆开整理一下：

$\sum_{j=1}^{i-1}\frac{dp_{j}\times 2^{j-1}+s_{i-j}\times 2^{j-1}}{2^{i-1}}$

$=\sum_{j=1}^{i-1}(\frac{dp_{j}\times 2^{j-1}}{2^{i-1}}+\frac{s_{i-j}\times 2^{j-1}}{2^{i-1}})$

$=\sum_{j=1}^{i-1}(\frac{dp_{j}\times 2^j}{2^i}+\frac{s_{i-j}}{2^{i-j}})$

注意：在这里求和的遍历过程内，$j$ 与 $i-j$ 的区别仅在于遍历顺序，对总的结果无影响，因此，进一步转化，得：

$\sum_{j=1}^{i-1}(\frac{dp_{j}\times 2^j}{2^i}+\frac{s_{j}}{2^j})$

$=\sum_{j=1}^{i-1}\frac{dp_{j}\times 2^j}{2^i}+\sum_{j=1}^{i-1}\frac{s_{j}}{2^j}$

令 $s1_i=\sum_{j=1}^{i}{dp_{j}\times 2^j}$，$s2_i=\sum_{j=1}^{i}\frac{s_{j}}{2^j}$，二者均可以通过前缀和递推完成计算，此时转移方程为

$dp_i=\frac{s_{i}}{2^{i-1}}+\frac{s1_{i-1}}{2^{i}}+{s2}_{i-1}$

初始状态显然为 $dp_0=0$，注意取模和逆元处理。

总复杂度为 $\Theta(n\log p+n) ,p=998244353$，瓶颈在于逆元预处理用了快速幂。

Code：（去掉那几行注释挺短的。注释给自己写的，主要是写的时候提醒自己。）

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+1,DLA=998244353;
ll a[N],s[N],tp[N],tpinv[N],n,s1[N],s2[N];
ll dp[N];
ll fpm(ll x,ll y)
{
    ll ans=1;x=x%DLA;
    for(;y;y>>=1,x=(x*=x)%DLA) if(y&1) ans=(ans*=x)%DLA;
    return ans;
}
//dp[i]=s[i]*inv(2^(i-1))+/sum (dp[j]+s[i-j])*(2^(j-1))*inv(2^(i-1))
//j=1,j<=i-1
//dp[i]=s[i]*inv(2^(i-1))+/sum (dp[j]+s[i-j])*inv(2^(i-j))
//后半部分求和式：把期望乘上概率（已知）还原成实际值，之后除回去
//s[i-j]也要乘，因为还原成实际值后，所有的情况都要加一份s[i-j]
//注意i-j与j在1到i-1上对称
//dp[i]=s[i]*inv(2^(i-1))+/sum (dp[j]*2^j)*inv(2^i) +/sum s[j]*inv(2^(j))
//前缀和处理sum (dp[j]*2^j)与sum s[j]*inv(2^(j))
int main()
{
    ios::sync_with_stdio(0);
    cin>>n;tp[0]=1;
    for(auto i=1;i<=n;++i) cin>>a[i],s[i]=(s[i-1]+a[i])%DLA,
    tp[i]=(tp[i-1]*2)%DLA;
    for(int i=0;i<=n;++i) tpinv[i]=fpm(tp[i],DLA-2);
    for(int i=1;i<=n;++i) s2[i]=(s2[i-1]+s[i]*tpinv[i]%DLA)%DLA;
    for(auto i=1;i<=n;++i) dp[i]=(s[i]*tpinv[i-1]+s1[i-1]*tpinv[i]+s2[i-1])%DLA,s1[i]=(s1[i-1]+dp[i]*tp[i]%DLA)%DLA;
    cout<<(dp[n]*tp[n-1])%DLA;return 0;
}
```


---

## 作者：RC·阿柒 (赞：0)

## CF1009E 题解

数学题，可见答案求的是所有代价的和。

考虑每个 $a_{i}$ 会被计算几次，发现对于一个 $a_{i}$，它的贡献是 $\sum\limits_{i=1}^{n-i+1}i \times C_{n-i+1}^{n-i}$。例如，样例 $2$ 中 $a_{1}$ 的贡献是 $(4\times 1 +3\times 3+2\times 3+1\times 1 )\times a_{1}=20$。

但是直接做是 $O(n^2)$ 的，考虑化简，把式子 $\times 2$，变成（暂时把上式中 $n-i+1$ 看成 $N$ ）：

原式$=\large{\frac {N\times C_{N}^{0}+ 1\times C_{N}^{N-1} +(N-1)\times C_{N}^{1}+2\times C_{N}^{N-2}+... }{2}}$

​		$=\large{\frac{(N+1)\times \sum\limits_{i=0}^{N-1}C_{N}^{i}}{2}}$  

​		$=\large{\frac{(N+1)\times 2^{N-1}}{2}}$ 

​		$=(N+1)\times 2^{N-2}$

把 $N=n-i+1$ 代入，得 原式 $=(n-i+2)\times 2^{n-i-1}$。

最后答案便是 $\sum\limits_{i=1}^{n} a_{i}\times (n-i+2)\times 2^{n-i-1}$，时间复杂度 $O(n)$。

注意指数可能为负，稍微改改快速幂就行。

---

**Talk is cheap, show me the code.**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int,int> Pii;
const int N=1e6+5,Mod=998244353;
int n;
int a[N];
int ans=0;
inline int qp(int a,int b,int res=1)
{
	bool f=b<0;b=abs(b);
	while(b)
	{
		if(b&1)res=res*a%Mod;
		a=a*a%Mod;b>>=1;
	}return f?qp(res,Mod-2):res;
}
signed main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		(ans+=(n-i+2)*qp(2,n-i-1)%Mod*a[i]%Mod)%=Mod;
	} 
	cout<<ans<<'\n';
	return 0;
}
```



---

## 作者：Purslane (赞：0)

# Solution

老年退役选手做蓝题来水课时。

应该看出题目求的是所有方案的代价的和。

一种想法是 DP。设 $dp_u$ 为以 $u$ 为最后一次休息位置的答案数。那么应该有：

$$dp_u= \sum_{v=0}^{u-1} dp_{v}\sum_{j=1}^{u-v} a_j$$

可能是我太蠢了，想不到多项式以外的做法。

我们最后不用动态规划，但是交换这个式子的内外求和符号可以给我们带来一定的启示。我们说不定可以枚举所有情况中每个 $a_i$ 出现了多少次。

考虑如果出现了长度为 $u$ 的连续段，那么所有 $v \le u$ 都会有 $a_v$ 被统计进一次答案。于是我们对于每个 $u$，钦定某个位置 $i$ 到 $i+u-1$ 是一个连续段，其他位置是否和上一个连续看情况。如果 $i=1$，那么相当于有 $n-u$ 个位置随便选；否则一共有 $n-u$ 个可能的 $i$，每个 $i$ 都有 $n-u+1$ 个位置随便选

所以答案是 $\sum_{u=1}^n a_u(2^{n-u}+(n-u)\times 2^{n-u-1})$。

预处理 $2$ 的幂次可以做到 $O(n)$。

---

