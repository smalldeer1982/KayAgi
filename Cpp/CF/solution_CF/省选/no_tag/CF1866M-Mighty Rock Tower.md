# Mighty Rock Tower

## 题目描述

Pak Chanek comes up with an idea in the midst of boredom to play a game. The game is a rock tower game. There is a big rock that is used as a base. There are also $ N $ small identical rocks that Pak Chanek will use to build a rock tower with a height of $ N $ above the base rock.

Initially, there are no small rocks that are located above the base rock. In other words, the height of the tower above the base rock is initially $ 0 $ . In one move, Pak Chanek can place one small rock onto the top of the tower which makes the height of the tower above the base rock increase by $ 1 $ . Each time Pak Chanek place one small rock, the following will happen after the small rock is placed:

- Let's say $ x $ is the height of the tower above the base rock right after the small rock is placed.
- There is a probability of $ P_x $ percent that the topmost rock falls.
- If $ x \geq 2 $ and the topmost rock falls, then there is another probability of $ P_x $ percent that the $ 2 $ -nd topmost rock also falls.
- If $ x \geq 3 $ and the $ 2 $ -nd topmost rock falls, then there is another probability of $ P_x $ percent that the $ 3 $ -rd topmost rock also falls.
- If $ x \geq 4 $ and the $ 3 $ -rd topmost rock falls, then there is another probability of $ P_x $ percent that the $ 4 $ -th topmost rock also falls.
- And so on.

If the tower successfully reaches a height of $ N $ without any rocks falling after that, then the game is ended.

If given an integer array $ [P_1, P_2, \ldots, P_N] $ , what is the expected value of the number of moves that Pak Chanek needs to do to end the game? It can be proven that the expected value can be represented as an simple fraction $ \frac{P}{Q} $ where $ Q $ is coprime to $ 998\,244\,353 $ . Output the value of $ P \times Q^{-1} $ modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, the expected value of the number of moves that Pak Chanek needs to do to end the game is $ \frac{19}{2} $ .

## 样例 #1

### 输入

```
2
80 50```

### 输出

```
499122186```

## 样例 #2

### 输入

```
3
25 16 20```

### 输出

```
879786027```

# 题解

## 作者：CYZZ (赞：7)

## [CF1866M](https://codeforces.com/problemset/problem/1866/M)

这篇题解较为详细地展示了 dp 式子的化简过程。

由于石子必须一个一个堆上去，所以设 $f_i$ 表示从第 $i-1$ 层堆到第 $i$ 层的期望次数。

分两种情况转移：掉到非零层，掉到第零层。

转移时考虑这次堆叠掉落到了那一层，初始 $f_0=0$。

$$
f_i=1+\sum_{j=1}^{i-1}({P_i}^{i-j}(1-P_i)\sum_{k=j+1}^{i}f_k)+{P_i}^{i}\sum_{j=1}^{i}f_j
$$

把 $(1-P_i)$ 拆开，得到：
$$
f_i=1+\sum_{j=1}^{i-1}({P_i}^{i-j}\sum_{k=j+1}^{i}f_k)-\sum_{j=1}^{i-1}({P_i}^{i-j+1}\sum_{k=j+1}^{i}f_k)+{P_i}^{i}\sum_{j=1}^{i}f_j
$$

把第四项合并到第二项上（$1$ 也是一项哦），得到：
$$
f_i=1+\sum_{j=0}^{i-1}({P_i}^{i-j}\sum_{k=j+1}^{i}f_k)-\sum_{j=1}^{i-1}({P_i}^{i-j+1}\sum_{k=j+1}^{i}f_k)
$$

将第三项的 $j$ 整体往左移一位，得到：
$$
f_i=1+\sum_{j=0}^{i-1}({P_i}^{i-j}\sum_{k=j+1}^{i}f_k)-\sum_{j=0}^{i-2}({P_i}^{i-j}\sum_{k=j+2}^{i}f_k)
$$

把第三项合并到第二项上（即括号内的数相减），得到：
$$
f_i=1+\sum_{j=0}^{i-2}({P_i}^{i-j}f_{j+1})+P_if_i
$$

将第三项挪到左边，得到：
$$
(1-P_i)f_i=1+\sum_{j=0}^{i-2}{P_i}^{i-j}f_{j+1}
$$

将 $(1-P_i)$ 除过去，得到：
$$
f_i=\frac{1+\sum_{j=0}^{i-2}{P_i}^{i-j}f_{j+1}}{1-P_i}
$$

 此时已经可以 $O(n^2)$ dp 了，需要优化。发现瓶颈在 sigma 求值上，而且很难用前缀和之类的优化。

发现 $P_i$ 仅有 $100$ 种取值，考虑把这 $100$ 种直接暴力计入状态。

具体的，设 $g_{t,i}$ 表示钦定 $P_i=t\%$ 时的  $\sum_{j=0}^{i-2}{t}^{i-j}f_{j+1}$。

自行推导不难得出，$f,g$ 的转移。
$$
g_{t,i}=tg_{t,i-1}+t^2f_{i-1},f_i=\frac{1+g_{P_i,i}}{1-P_i}
$$
成功做到 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200005
#define mod 998244353
int n,a[N],p[105];
int f[N],g[105][N];
inline int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
inline int del(int x,int y){return x-y<0?x-y+mod:x-y;}
inline int qpow(int x,int y){int ret=1;for(;y;y>>=1,x=1ll*x*x%mod)if(y&1)ret=1ll*ret*x%mod;return ret;}
int main()
{
	scanf("%d",&n);
	int inv100=qpow(100,mod-2);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=0;i<100;i++) p[i]=1ll*i*inv100%mod;
	for(int i=1;i<=n;i++)
	{
		if(i>1) for(int t=0;t<100;t++) g[t][i]=add(1ll*p[t]*g[t][i-1]%mod,1ll*p[t]*p[t]%mod*f[i-1]%mod);
		f[i]=1ll*add(1,g[a[i]][i])*qpow(del(1,p[a[i]]),mod-2)%mod;
	}
	int ans=0;
	for(int i=1;i<=n;i++) ans=add(ans,f[i]);
	printf("%d",ans);
}
```

---

## 作者：weirdoX (赞：5)


# CodeForces 1866 M. Mighty Rock Tower solution

[题目连接](https://codeforces.com/contest/1866/problem/M) 
[安利博客qwq](https://www.cnblogs.com/weirdoX/p/17831319.html)

首先有一个很妙的状态设计，就是这么设计，$dp_i$ 表示高度从 $i$ 到 $i+1$ 的期望步数，

那么这样就比较转移。最后的答案也就是 $\sum_{i=1}^ndp_i$ 。

容易想到转移的式子，就是一种是坍塌到了 0，另一种就是坍塌到了某一层。

$$
dp_i=1+(\sum_{j=1}^idp_j\times p_i^i) + \sum_{j=1}^{i-1}dp_{i-j+1}\times(1-p_i)\times p_i^j
$$

$$
=1+(\sum_{j=1}^idp_j\times p_i^i) + \sum_{j=1}^{i-1}((1-p_i)\times p_i^j\times\sum_{k=i-j+1}^{i}dp_k)
$$

$$
=1+(\sum_{j=1}^idp_j\times p_i^i) + \sum_{j=1}^{i-1}\sum_{k=i-j+1}^{i}dp_k\times(1-p_i)\times p_i^j
$$

$$
=1+(\sum_{j=1}^idp_j\times p_i^i) +\sum_{k=1}^{i}dp_k\times\sum_{j=i-k+1}^{i-1} p_i^j\times (1-p_i) 
$$

然后这里最后一项可以等比数列求和：得到：  

$$
\sum_{j=i-k+1}^{i-1} p_i^j
$$

$$
=\frac{(p_i^i-1)-(p_i^{i-k+1}-1)}{p_i-1}
$$

$$
=\frac{p_i^i-p_i^{i-k+1}}{p_i-1}
$$

所以

$$
dp_i=1+(\sum_{j=1}^idp_j\times p_i^i) +\sum_{k=1}^{i}dp_k\times (p_i^{i-k+1}-p_i^i)
$$

$j$ 和 $k$ 合并。  

$$
=1+\sum_{j=1}^idp_j\times p_{i}^{i-j+1}
$$

$dp_i$ 拆出来，移项：

$$
dp_i-dp_i\times p_i=1+\sum_{j=1}^{i-1}dp_j\times p_{i}^{i-j+1}
$$

移回去:

$$
dp_i=\frac{1+\sum_{j=1}^{i-1}dp_j\times p_{i}^{i-j+1}}{1-p_i}
$$

### 最后的优化：！

我们对于每一种 $x \in [0,99]$ ，的 $dp_i\times x^i$ 做一遍前缀和即可。
时间复杂度： $O(Vn)$。

### AC Code:

```cpp
const int N = 200010;
int n;
int p[N];
mint dp[N], s[N][100], val[100];//这里用了modint，见谅

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &p[i]);
    for (int i = 0; i < 100; i++) 
        val[i] = mi(i) / 100;//这里注意要这么算，否则会TLE..

    mint ans;
    for (int i = 1; i <= n; i++) {
        dp[i] = (1 + s[i - 1][p[i]] * val[p[i]]) / (1 - val[p[i]]);//就是是式子。。
        for (int j = 0; j < 100; j++) {
            s[i][j] = (s[i - 1][j] + dp[i]) * val[j];
        }
        ans += dp[i];
    }
    printf("%d\n", ans);
    return 0;
}
```

可以点个赞吗 QWQ。


---

## 作者：Register_int (赞：5)

考虑 $dp_i$ 为从 $i-1$ 个搭到第 $i$ 个的期望步数。枚举搭上去后跌下来的格数，可以得到方程：

$$
\begin{aligned}
dp_i&=1+p_i^i\sum^i_{j=1}dp_j+\sum^{i-1}_{j=1}p_i^j(1-p_i)\sum^i_{k=i-j+1}dp_k\\
&=1+\sum^i_{j=1}p_i^jdp_{i-j+1}\\
&=1+p_idp_i+\sum^i_{j=2}p_i^jdp_{i-j+1}\\
\end{aligned}
$$

得到转移式：

$$dp_i=\dfrac{1+\sum^i_{j=2}p_i^jdp_{i-j+1}}{1-p_i}$$

此时我们很希望使用前缀和优化这个 dp，但是求和中带了一个 $p_i^j$，怎么办呢？答案是直接对于每一种 $p$ 维护前缀和，这样的复杂度是 $O(kn)$ 的，其中 $k=100$，可以接受。

然后就做完了。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;
const int mod = 998244353;
const int inv = 828542813;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	for (; p; p >>= 1, b = b * b % mod) if (p & 1) res = res * b % mod;
	return res;
}

int n, a[MAXN]; ll dp[MAXN], s[100], p[100], ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 0; i < 100; i++) p[i] = (ll)i * inv % mod;
	for (int i = 1; i <= n; i++) {
		dp[i] = (s[a[i]] + 1) * qpow(mod + 1 - p[a[i]], mod - 2) % mod, ans = (ans + dp[i]) % mod;
		for (int j = 0; j < 100; j++) s[j] = (s[j] * p[j] % mod + p[j] * p[j] % mod * dp[i] % mod) % mod;
	}
	printf("%lld", ans);
}
```

---

## 作者：_HCl_ (赞：4)

概率 DP 好题。

# CF1866M 题解

**题意简述**

叠石头，叠完第 $x$ 个石头后有 $P_x$ 的概率掉下来，掉下来后第 $x-1$ 个石头也有 $P_x$ 的概率掉下来，再掉下来后第 $x-2$ 个石头也有 $P_x$ 的概率掉下来，以此类推。求叠 $N$ 个石头的期望次数。

**思路引导**

按照常理，我们设的状态应该是 $f_i$ 表示叠到 $i$ 层的期望次数。但稍加考虑，这个状态导出的转移方程非常难想。因此我们考虑对它差分，也就是 $f_i$ 表示从第 $i$ 层叠到 $i+1$ 层的期望次数。

从第 $i$ 层叠到第 $i+1$ 层，有可能直接叠上去，有可能坍塌到第 $j$ 层，也有可能直接坍塌到第 $0$ 层。

其中，第一种情况的期望就是 $1$；

第二种情况，考虑坍塌到第 $j$ 层的期望。坍塌到第 $j$ 层的概率是 $p_i^j(1-p_i)$，代价是 $\sum_{k=i-j+1}^if_k$，故期望是 $p_i^j(1-p_i)\sum_{k=i-j+1}^if_k$；

第三种情况的概率是 $p_i^i$，代价是 $\sum_{j=1}^if_j$，期望是 $p_i^i\sum_{j=1}^if_j$。

我们直接对这三种情况的期望线性相加，即：

$$f_i=1+\sum_{j=1}^{i-1}(p_i^j(1-p_i)\sum_{k=i-j+1}^if_k)+p_i^i\sum_{j=1}^if_j$$
$$=p_if_i+1+\sum_{j=2}^ip_i^jf_{i-j+1}$$

解得

$$f_i=\dfrac{1+\sum_{j=2}^ip_i^jf_{i-j+1}}{1-p_i}$$

这就是状态转移方程了。

然而，如果直接按照这个方程来打的话，时间复杂度为 $\mathcal{O}(n^2)$，显然会超时。因此我们考虑使用前缀和优化 $\sum_{j=2}^ip_i^jf_{i-j+1}$。

由于 $p$ 是不定的，但 $p$ 可能的可能的取值又很少，所以我们对于每一种 $p$ 去求前缀和。设 $s_i=\sum_{j=2}^ip^jf_{i-j+1}$，那么 $s_{i+1}=p(s_i+p\cdot f_i)$。每一种 $p$ 对应的 $s$ 只用存在一个变量里滚动使用即可。最终答案即为 $\sum_{i=1}^Nf_i$。

总复杂度为 $\mathcal{O}(n)$，常数为 $100$，有点大，但不多。

**实现**

1. 读入
1. 预处理出 $p_i$。
1. 动态规划计算答案。

对于 DP 中的每一轮循环（每一个 $i$）：

1. 计算 $f_i$。
1. 统计进答案。
1. 处理出前缀和。

**代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int MOD=998244353;
int n,p[200001],inv[1001],f[200001],s[1001];
int qpow(int x,int y) {
	int res=1;
	for(; y; y>>=1) {
		if(y&1)res=(res*x)%MOD;
		x=(x*x)%MOD;
	}
	return res;
}
signed main() {
	cin>>n;
	for(int i=1; i<=n; ++i)scanf("%lld",p+i);
	int tmp=qpow(100,MOD-2);
	for(int i=0; i<=100; ++i)inv[i]=i*tmp%MOD;//inv即p_i
	int ans=0;
	for(int i=1; i<=n; ++i) {
		f[i]=(1+s[p[i]])%MOD*qpow((1+MOD-inv[p[i]])%MOD,MOD-2)%MOD;
		ans=(ans+f[i])%MOD;
		for(int j=0; j<=100; ++j)
			s[j]=(inv[j]*s[j]%MOD+inv[j]*inv[j]%MOD*f[i]%MOD)%MOD;//s[j]是p=j的前缀和
	}
	cout<<ans;
}
```

---

## 作者：wangyishan (赞：3)

提供一种不一样的做法。主要思路来自 @Ebola。好闪，拜谢！

考虑令 $E_x$ 表示当前叠了 $x$ 个石子后距离结束的期望步数，则 $E_n=0$，答案即为 $E_0$。

考虑加了一个石子后会变成什么石子。令 $q_i=\dfrac{p_i}{100} \pmod m$，不难得到转移方程：
$$
E_i=(1-q_{i+1})E_{i+1}+\sum_{j=1}^i{q_{i+1}^{i+1-j}(1-q_{i+1})E_j}+q_{i+1}^{i+1}E_0+1
$$
这有点难算，考虑把 $E_{i+1}$ 移到左边。
$$
E_{i+1}=\dfrac{E_i-q_{i+1}^{i+1}E_0-1}{1-q_{{i+1}}}-\sum_{j=1}^i{q_{i+1}^{i+1-j}E_j}
$$
但是这样仍然不能做。因为这么做是根据 $E_0$ 求 $E_n$，但是我们需要根据 $E_n$ 求 $E_0$。

这里需要运用一定的线性代数知识：

注意到每个 $E_i$ 都是一个关于 $E_0$ 的一次函数。考虑把每个 $E_i$ 表示成 $k_i E_0+b_i$ 的形式，维护这个 $k_i$ 与 $b_i$ ，最后通过 $E_n=0=k_n E_0+b_n$ 求得 $E_0=-\dfrac{b_n}{k_n}$。

然后就能做了。

但是还存在复杂度的问题。直接转移是 $\mathcal{O}(n^2)$ 的，过不去。

以下的部分就和其他题解类似了。发现 $p_i$ 只有 $100$ 种取值，考虑维护一个 $S(n,p)=\sum_{j=1}^{n}q_jE_{i-j}$，就是原式的求和，维护也很简单。

时间复杂度 $\mathcal{O}(kn)$，其中 $k=100$。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long
#define maxn 200010
#define mod 998244353
int n;
int a[maxn],b[maxn],iv=828542813;
int ans[maxn][2],s[101][2];
int qpow(int a,int b){
    int ans=1,base=a%mod;
    while(b){
        if(b&1)ans=ans*base%mod;
        base=base*base%mod;
        b>>=1;
    }
    return ans;
}
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){cin>>a[i];b[i]=b[i]*iv%mod;}
    ans[0][0]=1,ans[0][1]=0;
    for(int i=1;i<=n;i++){
        int c=qpow((100-a[i])*iv%mod,mod-2)%mod,x=qpow(a[i]*iv%mod,i)%mod;
        ans[i][0]=((ans[i-1][0]-x+mod)%mod*c%mod-s[a[i]][0]+mod)%mod;
        ans[i][1]=((ans[i-1][1]-1+mod)%mod*c%mod-s[a[i]][1]+mod)%mod;
        for(int p=0;p<=100;p++){
            s[p][0]=p*(s[p][0]+ans[i][0])%mod*iv%mod;
            s[p][1]=p*(s[p][1]+ans[i][1])%mod*iv%mod;
        }
    }
    cout<<(-ans[n][1]*qpow(ans[n][0],mod-2)%mod+mod)%mod<<endl;
    
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T=1;
   // cin>>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：_YangZJ_ (赞：2)

记 $f_x$ 表示从 $x$ 到达 $x+1$ 并且不会掉下来的期望步数，

$g_x$ 表示从 $x+1$ 掉下来，再次能回到 $x$ 的期望步数，

$h_y$ 表示对于当前枚举的 $x$，从 $y$ 上到 $x$ 的期望步数，其中 $y\leq x$。

考虑转移：考虑总共期望 $\frac{1}{1-p_x}$ 次才能从 $x$ 到达 $x+1$，其中前面 $\frac{1}{1-p_x}-1$ 次需要用 $g_x$ 步才可以进到下一次：
$$
f_x = (\frac{1}{1-p_{x+1}}-1)\cdot g_x+\frac{1}{1-p_{x+1}}
$$
那么 $h$ 的转移就很简单，原本是从 $y$ 到 $x$，现在是到 $x+1$，加上 $f_x$ 即可。
$$
h_y'=h_y+f_x
$$
最后再来考虑 $g_{x+1}$，直接对 $h$ 带权求和即可：
$$
g_{x+1}=\sum_{i=1}^{x+1}p_{x+2}^{x+1-i}(1-p_{x+2})h_i'+p_{x+2}^{x+1}h_0'
$$

$$
=p_{x+2}^{x+1}\left(\sum_{i=1}^{x+1}h_i'\cdot (1-p_{x+2})\cdot p_{x+2}^{-i}+h_0\right)
$$

考虑 $p$ 的取值只有 $100$ 种，而 $h$ 的操作又是全局 $+$，因此只需要对于每个 $p$ 维护括号里那个式子所有 $h$ 的系数和即可。

复杂度 $O(nP_{max})$。

code 

[$O(n^2)$](https://codeforces.com/contest/1866/submission/222145518) 

[$O(nP_{max})$](https://codeforces.com/contest/1866/submission/222146594)

---

## 作者：TSY48 (赞：2)

**解题思路**

相信大家在看到题的第一想法应该是设：$dp_i$ 为表示叠 
$i$ 层的期望次数。本蒟篛也是酱紫想的，但推了 $20$min 之后，蒟篛发现递推方程异常难qwq（也可能是我太菜了）。

但虽说设：$dp_i$ 为表示叠到 $i$ 层的期望次数不太行。但可以用差分的思想。设：$dp_i$ 为从第 $i$ 层叠到第 $i+1$ 层的期望次数。酱紫递推方程就好写辣！

现在来说递推方程长成神马样：

首先，从第 $i$ 叠到第 $i+1$ 时的状态有3种：

1：直接叠上去

2：掉到 $j$ 层

3：直接掉到 $0$ 层

下面对这 $3$ 种情况讨论：

1：期望为 $1$

2：考虑掉到第 $j$ 层第情况。掉到第 $j$ 层的概率为 $
p_i^j(1-p_i)$，代价为 $\sum_{k=i-j+1}^idp_k$，则期望为
$$
p_i^j(1-p_i)\sum_{k=i-j+1}^idp_k
$$
3：概率是 $p_i^i$，代价为 $\sum_{j=1}^idp_i$，则期望为
$$
p_i^i\sum_{j=1}^idp_i
$$
则 $dp_i$ 为这三种情况的期望相加
$$
dp_i=1+\sum_{j=1}^{i-1}(p_i^j(1-p_i)\sum_{k=i-j+1}^idp_k)+\sum_{j=1}^idp_i
$$
简化可得：
$$
dp_i=\frac{1+\sum_{j=2}^ip_i^jdp_{i-j+1}}{1-p_i}
$$
但对此方程直接转移肯定是不行的（复杂度为 $O(n^2)$）。

考虑优化：设 $pre_i=\sum_{j=2}^ip_i^jdp_{i-j+1}$，则 $pre_{i+1}=p \cdot (pre_i+p \cdot dp_i)$。

但这里有个问题：就是如何对每个 $p_i$ 去求前缀和。

注意到在求 $pre_i$ 时只在意前一位，与在前面无关。我们可以将 $pre_i$ 表示为在 $p=i$ 时的前缀和，转移时只需用原来的值来更新现在的值就可以了（其实就是类似滚动数组的操作）。

最终答案为 $\sum_{i=1}^{n}dp_i$。

复杂度为 $O(100n)$。

AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define m_p make_pair
#define str string
#define lowbit(x) (x&(-x))
#define fi first
#define se second
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pi;
//typedef __int128 it;
const int Maxn=2e5+10;
const int inf=0x3f;
const ll mod=998244353;
inline ll qpow(ll a,ll b)
{
    ll ans=1;
    a=a%mod;
    while(b!=0){
        if(b&1) ans=(ans*a)%mod;
        b>>=1;
        a=(a*a)%mod;
    }
    return ans;
}
ll p[Maxn];
ll inv[Maxn];
ll pre[Maxn],dp[Maxn];
int main()
{
    ll n;
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&p[i]);
    for(int i=1;i<=100;i++) inv[i]=i*qpow(100,mod-2)%mod;
    ll ans=0;
    for(int i=1;i<=n;i++){
        dp[i]=(1+pre[p[i]])%mod*qpow((1+mod-inv[p[i]])%mod,mod-2)%mod;
        ans=(ans+dp[i])%mod;
        for(int j=0;j<=100;j++){
            pre[j]=(inv[j]*pre[j]%mod+inv[j]*inv[j]%mod*dp[i]%mod);
        }
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：zhongpeilin (赞：1)

首先我们可以设 $dp_{i}$ 表示搭到第 $i$ 层的期望步数，不难发现这样是有后效性的，且式子不好拆，舍弃。  
换个思路，设 $dp_{i}$ 表示从 $i-1$ 层到第 $i$ 层且搭完之后没掉的期望搭的次数，需要分讨（注意下面的都不算从 $i - 1 \to i$ 的第一步）。
1. 首先我们有 $1-p_{i}$ 的概率使得搭上去之后不掉下来，代价为 `0`。  
2. 我们假设掉了 $1 \le j < i$ 个石头，这样概率为 $p_{i}^j \times (1 - p_{i})$，代价是 $\sum_{k = i - j + 1}^{i} dp_{k}$，因为掉了 $j$ 个后变成了 $i - j$，那么由于 $dp_{i - j + 1}$ 表示从 $i - 1 \to i - j+ 1$ 的代价，所以从 $i - j + 1$ 开始，一直回到 $i$ 的 $dp$ 之和。  
3. 就是都掉完的情况，因为如果都没掉完，那么就需要乘 $1 - p_{i}$，但都掉完就不需要了，概率为 $p_{i}^{i}$，代价为 $\sum_{k = 1}^{i} dp_{k}$。  
加在一块：
$$dp_{i} = 1 + (1 - p_{i}) \times 0 + \sum_{j = 1}^{i-1} p_{i}^j \times (1 - p_{i}) \times (\sum_{k = i - j + 1}^{i} dp_{k}) + p_{i}^{i} \times (\sum_{k = 1}^{i} dp_{k})$$
$$=1 + \sum_{j = 1}^{i-1} p_{i}^j \times (1 - p_{i}) \times (\sum_{k = i - j + 1}^{i} dp_{k}) + p_{i}^{i} \times (\sum_{k = 1}^{i} dp_{k})$$

$$=1 + \sum_{j = 1}^{i-1} p_{i}^j \times (\sum_{k = i - j + 1}^{i} dp_{k}) + p_{i}^{i} \times (\sum_{k = 1}^{i} dp_{k}) - \sum_{j = 1}^{i-1} p_{i}^{j + 1} \times (\sum_{k = i - j + 1}^{i} dp_{k})$$

$$=1 + \sum_{j = 1}^{i} p_{i}^j \times (\sum_{k = i - j + 1}^{i} dp_{k})  - \sum_{j = 1}^{i-1} p_{i}^{j + 1} \times (\sum_{k = i - j + 1}^{i} dp_{k})$$

此时我们发现减数的 $j$ 和被减数的 $j + 1$ 时都有 $p_{i}^{j + 1}$，考虑让他俩建立关系：
$$p_{i}^{j+1} \times (\sum_{k = i - (j+1) + 1}^{i} dp_{k}) - p_{i}^{j+1} \times (\sum_{k = i - j + 1}^{i} dp_{k}) = p_{i}^{j+1} \times dp_{i - j}$$
所以上面的式子可以化为：
$$dp_{i} = 1 + p_{i} \times dp_{i}  + \sum_{j = 1}^{i-1} p_{i}^{j + 1} \times dp_{i - j}$$
$$= 1 + p_{i} \times dp_{i}  + \sum_{j = 2}^{i} p_{i}^{j} \times dp_{i - j + 1}$$
将 $p_{i} \times dp_{i}$ 移项：
$$(1 - p_{i}) \times dp_{i} = 1 + \sum_{j = 2}^{i} p_{i}^{j} \times dp_{i - j + 1}$$
$$dp_{i} = \frac{1 + \sum_{j = 2}^{i} p_{i}^{j} \times dp_{i - j + 1}}{1 - p_{i}}$$
我们发现这还是 $O(n^2)$ 的时间，但不好优化了，所以我们可以枚举 $i - j + 1 = k$，就有：
$$dp_{i} = \frac{1 + \sum_{k = 1}^{i-1} p_{i}^{i-k+1} \times dp_{k}}{1 - p_{i}}$$
那么我们设 $sum_{i, j}$ 表示 $\sum_{k = 1}^{j-1} i^{j-k+1} \times dp_{k}$，那么有 $sum_{i,j} = sum_{i, j - 1} \times i + i^2 \times dp_{j - 1}$。  
## CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
int n, a[200005], c[105], dp[200005], sum[105];
int inv[105];

int qp(int a, int b = mod - 2){
	int ans = 1;
	while(b){
		if(b % 2) ans = ans * a % mod;
		a = a * a % mod;
		b /= 2;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	inv[1] = 1;
	for(int i = 2; i <= 100; i++){
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	}
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= 100; i++) c[i] = i * inv[100] % mod;
	dp[0] = 0;
	int ans = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 0; j <= 99; j++){
			sum[j] = c[j] * (sum[j] + c[j] * dp[i - 1] % mod) % mod;
		}
		dp[i] = (1 + sum[a[i]]) * qp(1 + mod - c[a[i]] % mod) % mod;
		ans = (ans + dp[i]) % mod;
	}
	cout << ans << endl;
	return 0;
}

---

## 作者：Helenty (赞：0)

我们设 $f_x$ 表示 $x-1\rightarrow x$ 的期望步数。

那么转移 $f_i=1+\sum_{j=1}^if_jp_i^{i-j+1}$，当然这个是一元一次要解一下。

考虑设 $f_x$ 表示经过 $x$ 的期望次数，$f_{N+1}=1$。

那么转移就是 $f_i=1+\sum_{j=i}^nf_jp_j^{j-i+1}$，当然这个是一元一次要解一下。

这俩看起来都是 $O(n^2)$ 的，说明要想优化思路了。

实际上第一个的 $p_i$ 是统一的，所以我们对这 $K=1\sim 100$ 种概率存下前缀和即可优化做到 $O(nk)$ 了。

---

## 作者：lyhqwq (赞：0)

# Solution

神奇期望 dp。

考虑期望 dp 的经典状态设计，令 $f_i$ 表示第 $i$ 层叠到第 $n$ 层的期望步数，但转移非常复杂，我们考虑对状态进行简化。

令 $f_i$ 表示第 $i-1$ 层叠到第 $i$ 层的期望步数，可以由 $f_j(0\leq j\leq i+1)$，转移得到。

$$f_i=1+\sum\limits_{j=1}^{i-1}p_i^j(1-p_i)\sum\limits_{k=i-j+1}^i f_k+p_i^i\sum\limits_{j=1}^i f_j$$

$$=1+\sum\limits_{j=1}^{i-1}p_i^j\sum\limits_{k=i-j+1}^i f_k-p_i\sum\limits_{j=1}^{i-1}p_i^j\sum\limits_{k=i-j+1}^i f_k+p_i^i\sum\limits_{j=1}^i f_j$$

$$=1+\sum\limits_{j=1}^ip_i^j\sum\limits_{k=i-j+1}^i f_k-\sum\limits_{j=1}^{i-1}p_i^{j+1}\sum\limits_{k=i-j+1}^i f_k$$

$$=1+\sum\limits_{j=0}^{i-1}p_i^{j+1}\sum\limits_{k=i-j}^if_k-\sum\limits_{j=1}^{i-1}p_i^{j+1}\sum\limits_{k=i-j+1}^i f_k$$

$$=1+\sum\limits_{j=1}^{i}p_i^jf_{i-j+1}$$

将带 $f_i$ 的项全部移到左边，解方程得

$$f_i=\dfrac{1+\sum\limits_{j=2}^ip_i^jf_{i-j+1}}{1-p_i}=\dfrac{1+\sum\limits_{j=1}^{i-1}p_i^{i-j+1}f_{j}}{1-p_i}$$

考虑进一步优化。

令 $g_{i,j}=\sum\limits_{k=1}^{j-1}i^{j-k+1}f_k$。

有 $f_i=\dfrac{1+g_{p_i,i}}{1-p_i}$，$g_{i,j}=g_{i,j-1}\times i+i^2\times f_{j}$。

将 $g$ 数组滚动，时间复杂度 $O(100n)$，可过。

# Code
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=200005;
const int Mod=998244353;
int n;
int a[N];
LL f[N],g[100],p[100];
LL qpow(LL a,int b){
    LL ans=1;
    for(;b;b>>=1,a=a*a%Mod) if(b&1) ans=ans*a%Mod;
    return ans;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=0;i<=99;i++) p[i]=i*qpow(100,Mod-2)%Mod;
    for(int i=1;i<=n;i++){
        f[i]=(1+g[a[i]])*qpow(1-p[a[i]]+Mod,Mod-2)%Mod;
        for(int j=0;j<=99;j++) g[j]=(g[j]*p[j]%Mod+qpow(p[j],2)*f[i]%Mod)%Mod;
    }
    LL ans=0;
    for(int i=1;i<=n;i++) ans=(ans+f[i])%Mod;
    printf("%lld\n",ans);
    return 0;
}

```

---

