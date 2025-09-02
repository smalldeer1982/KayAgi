# [PA 2025] 考试 / Egzamin

## 题目背景

PA 2025 R2 A.

1G/3s.

## 题目描述

期末考试有 $n$ 道题。对于每道题，你都可以选择是否作答。

如果选择作答第 $i$ 题，有 $p_i$ 的概率作答正确，$(1-p_i)$ 的概率作答错误。

每道题的评分规则如下：

- 作答正确：得 $1$ 分；
- 不作答：得 $0$ 分；
- 作答错误：倒扣 $1$ 分。

为了不挂科，你需要获得至少 $t$ 分。

**每道题目作答结果是相互独立的。**

在自由选择是否作答每道题的前提下，最大化不挂科的概率。只需要求出不挂科的概率。

注意在考试过程中你无法知道每个题的答题情况，只能决定要回答的题目。


## 说明/提示

### 样例解释
- 样例 $1$ 解释：最优策略是选择作答前 $4$ 题。
- 样例 $2$ 解释：最优策略是作答 $1,3,4$ 题。这样，不挂科的概率为 $0.3\times 0.2\times 0.15=0.009$。
- 样例 $3$ 解释：不挂科的概率为 $10^{-18}$。输出 $0$ 也被视为正确的答案。
### 数据范围

-  $ 1 \leq t \leq n \leq 50\, 000 $；
- $p_i\in [0,1]$，且至多有 $9$ 位小数。


## 样例 #1

### 输入

```
5 2
0.77
0.85
0.75
0.98
0.6```

### 输出

```
0.8798125```

## 样例 #2

### 输入

```
5 3
0.3
0.01
0.2
0.15
0```

### 输出

```
0.009```

## 样例 #3

### 输入

```
3 3
0.000001
0.000001
0.000001```

### 输出

```
0```

# 题解

## 作者：WrongAnswer_90 (赞：8)

首先对 $p$ 从大到小排序，一定取一段前缀做。暴力 DP $f_{i,j}$ 表示前 $i$ 个做对了 $j$ 个。可以证明有值的项不会特别多（？？？），大概是 $\mathcal O(\sqrt{n\log{\epsilon^{-1}}})$ 级别的，所以暴力就过了。

模拟赛场上写了一个非常不牛的分块 FFT，但是 luogu 上似乎被卡精度了。首先每个位置可以看成一个 $(p_i+(1-p_i)x)$ 的多项式。序列分块，处理出 $F_i$ 表示前 $i$ 个块多项式的乘积，块内用上面的暴力 DP。两部分拼起来的时候前缀和优化一下即可做到 $\mathcal O(n\sqrt{n\log n})$。

还有一个很牛的分治。设 `solve(l,r,F)` 表示要处理区间 $[l,r]$，然后 $[1,l-1]$ 的所有多项式乘起来是 $F$。

对于 $[x^i]F$，如果 $i-(r-l+1)>k$，那这个 $f_i$ 在区间里一定有贡献，直接加到区间里面就行了。如果 $i+(r-l+1)<k$，那这个 $f_i$ 在区间里一定没有贡献，所以需要考虑的项只有 $[k-(r-l+1),k+(r-l+1)]$ 里面的，所以 solve 需要保留的多项式长度就是 $\mathcal O(r-l+1)$ 级别的。这样 FFT 一下就可以做到 $\mathcal O(n\log^2 n)$ 求出每一项的答案了。

---

## 作者：Junounly (赞：3)

背景知识请先阅读 https://www.luogu.com.cn/article/xs2uucwg

---

> 有 $n$ 个随机变量 $X_1,X_2,\ldots,X_n$，其中 $X_i$ 有 $p_i$ 的概率为 $1$，否则为 $-1$。你选择一个 $k$，再选择其中的 $k$ 个随机变量，求最优决策下你选择的随机变量的和 $\ge t$ 的概率。
>
> $1 \le t \le n \le 50000$，误差在 $10^{-6}$ 以内。

首先，可以贪心地选随机变量，因为希望和尽可能大，所以优先选 $p_i$ 大的随机变量。

将所有 $p_i$ 排完序后，最终答案一定是一段前缀。

可以设计一个简单的 DP，记 $f_{i,j}$ 为选长度为 $i$ 的前缀，和为 $j$ 的概率。

每一次和只会 $+1$ 或者 $-1$，则有转移式：

$$f_{i,j}=p_i \cdot f_{i-1,j-1} + (1-p_i) \cdot f_{i-1,j+1}$$

这样做是 $\Theta(n^2)$ 的。

考虑优化，令 $\varepsilon$ 为误差，我们断言，对于每一个 $i$，使得 $f_{i,j} > \varepsilon$ 的位置不会很多。

转移时只需舍去 $f_{i,j} \le \varepsilon$ 的状态，精细实现即可通过本题。

下面给出这个做法的复杂度证明。

考虑对于每一个 $i$ 分析复杂度。事实上，事件 $\{$所有随机变量取值为 $-1$ 或 $1$，且和 $\ge t\}$ 等价于事件 $\{$所有随机变量取值为 $0$ 或 $1$，且和 $\ge \frac{i+t}{2}\}$，这样我们就把问题转化为了若干次的 $\text{Bernoulli}$ 分布，此时和的期望 $\mu=\sum \limits_{k=1}^{i} p_i$。

容易注意到的是，满足 $f_{i,j} > \varepsilon$ 的 $j$ 应该是一段连续区间，不妨设这一段区间为 $[(1-B_1)\mu,(1+B_2)\mu]$，且 $B_1,B_2>0$。

代入 $\text{Multiplicative Chernoff Bound}$ 可以得到：

$$\textbf{Pr}\big(X \ge (1+B_2) \mu \big) \le e^{-\frac{B_2^2 \mu}{B_2+2}} \le \varepsilon$$

$$\textbf{Pr}\big(X \le (1-B_1) \mu \big) \le e^{-\frac{B_1^2 \mu}{2}} \le \varepsilon$$

不等式两边同时取对数的相反数：

$$\frac{B_2^2 \mu}{B_2+2} \ge \ln \varepsilon^{-1}$$

$$\frac{B_1^2 \mu}{2} \ge \ln \varepsilon^{-1}$$

解二次不等式组得：

$$B_2 \ge \frac{\ln \varepsilon^{-1} + \sqrt{\ln^2 \varepsilon^{-1}-8\mu \ln \varepsilon^{-1}}}{2\mu}$$

$$B_1 \ge \sqrt{\frac{2\ln \varepsilon^{-1}}{\mu}}$$

舍去常数，由于 $0 \le \mu \le i$，所以可以视为 $n,\mu$ 同阶，且 $\ln \varepsilon^{-1}$ 相对于 $n$ 是小量，所以：

$$B_1,B_2 \ge \sqrt{\frac{\ln \varepsilon^{-1}}{n}}$$

取等号时最优，得到满足条件的区间为 $[\mu - \sqrt{n \ln \varepsilon^{-1}},\mu + \sqrt{n \ln \varepsilon^{-1}}]$，即对于每个 $i$，合法状态数为 $\Theta(\sqrt{n \ln \varepsilon^{-1}})$ 个。

综上，总时间复杂度为 $\Theta(n \sqrt{n \ln \varepsilon^{-1}})$。

经过测试，实际 $\varepsilon$ 的值大约取到 $10^{-11}$，此时总时间复杂度不超过 $6 \times 10^7$。

核心代码：

```c++
constexpr int N=5e4+5;
constexpr double eps=1e-11;
namespace Junounly
{
    int n,K;
    double p[N];
    vector<pair<int,double> > q[2];
    void main()
    {
        scanf("%d%d",&n,&K);
        for(int i=1;i<=n;i++) scanf("%lf",&p[i]);
        sort(p+1,p+n+1,greater<double>());
        q[0].emplace_back(0,1);
        double res=0;
        for(int i=1,op=0;i<=n;i++,op^=1)
        {
            for(auto [X,Y]:q[op])
            {
                int x=X-1;double y=Y*(1-p[i]);
                if(y>eps)
                {
                    if(q[op^1].size()&&q[op^1][q[op^1].size()-1].first==x) q[op^1][q[op^1].size()-1].second+=y;
                    else if(q[op^1].size()>1&&q[op^1][q[op^1].size()-2].first==x) q[op^1][q[op^1].size()-2].second+=y;
                    else q[op^1].emplace_back(x,y);
                }
                x=X+1;y=Y*p[i];
                if(y>eps) q[op^1].emplace_back(x,y);
            }
            q[op].clear();
            double now=0;
            for(auto [X,Y]:q[op^1])
                if(X>=K) now+=Y;
            res=max(res,now);
        }
        printf("%.11lf\n",res);
    }
}
```

---

## 作者：沉石鱼惊旋 (赞：3)

# 题意

有 $n$ 个 $[0,1]$ 之间的实数 $p_i$，选择若干个数。初始有 $s=0$，之后对于你选出的若干个 $p_i$，有 $p_i$ 的概率 $s\gets s+1$，有 $p_i$ 的概率 $s\gets s-1$。

自己选择 $p_i$，问最大有多大的概率能得到 $s\geq k$。

原题 $1\leq n,k\leq 5\times 10^4$，$0\leq p_i\leq 1$，$p_i$ 在十进制下至多九位小数，允许误差 $10^{-6}$。

模拟赛开到了 $1\leq n,k\leq 2\times 10^5$。

# 做法

一个显然的事情是你对 $p_i$ 排序之后，选择的一定是一段前缀。

设计状态 $f_{i,j}$ 表示前 $i$ 个数，得到 $s=j$ 的概率。

转移有 $f_{i,j}\gets f_{i-1,j-1}\times p_i+f_{i-1,j+1}\times (1-p_i)$。

直接做是平方的。如果求的是所有前缀的答案而不是最大概率好像是可以分治 FFT 做到 $\mathcal O(n\log^2 n)$ 的。但是这题求的是最大概率。

尝试打一下这个 DP 的表。发现边上都是一些很小的值。而这些很小的值占了很大一部分。

而概率题不取模绝对是有问题的（确信）我们从允许的误差入手，我们设一个 $\varepsilon=10^{-12}$。所有 $\leq \varepsilon$ 的 DP 状态都可以忽略。之后很轻松通过本题数据，稍微卡卡常就过了模拟赛数据范围。

我们 [yuanruiqi](https://www.luogu.com.cn/user/706028) 大神指出，这里一次都是一个伯努利分布，如果 $n$ 足够大那就是正态分布，然后可以积分算概率。

然后结合一下中心极限定理和切尔诺夫界可以推出有效的状态数是 $\mathcal O(n\sqrt{n \ln \frac{1}{\varepsilon}})$ 的。

# 代码

<https://www.luogu.com.cn/record/208697325>

```cpp
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-12;
template <typename T>
void chkmx(T &x, T y) { x = max(x, y); }
int n, k;
double p[200020];
double f_[2][400020];
double *f[2] = {f_[0] + 200005, f_[1] + 200005};
int g[2][400020];
int top[2];
int vec[400020], vtop;
void add(int t, int x) { g[t][++top[t]] = x; }
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> p[i];
    sort(p + 1, p + n + 1, greater<double>());
    bool t = 0;
    f[t][0] = 1;
    add(t, 0);
    double ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int _ = 1, j = g[t][_]; _ <= top[t]; j = g[t][++_])
            f[t ^ 1][j + 1] = f[t ^ 1][j - 1] = 0;
        vec[vtop = 0] = -1e9;
        for (int _ = 1, j = g[t][_]; _ <= top[t]; j = g[t][++_])
        {
            f[t ^ 1][j + 1] += f[t][j] * p[i];
            f[t ^ 1][j - 1] += f[t][j] * (1 - p[i]);
            if (vec[vtop] < j - 1)
                vec[++vtop] = j - 1;
            if (vec[vtop] < j + 1)
                vec[++vtop] = j + 1;
        }
        top[t] = 0;
        t ^= 1;
        double tmp = 0;
        for (int _ = 1, j = vec[_]; _ <= vtop; j = vec[++_])
        {
            if (j >= k - (n - i) && f[t][j] >= eps)
            {
                add(t, j);
                if (j >= k)
                    tmp += f[t][j];
            }
        }
        chkmx(ans, tmp);
    }
    cout << fixed << setprecision(10) << ans << '\n';
    return 0;
}
```

---

## 作者：littlez_meow (赞：2)

首先 $p$ 从大到小排序，贪心来看每次作答的必然是前缀。

于是设 $dp(i,j)$ 表示当前答前 $i$ 个题获得 $j$ 分的概率。

转移显然为 $dp(i,j)=dp(i-1,j-1)p_{i-1}+dp(i-1,j+1)(1-p_{i-1})$。可以做到 $O(n^2)$。

发现有很多 $dp(i,j)$ 都很小，我们不妨只对 $dp(i,j)>\epsilon$ 转移。

本题中，每道题的得分服从两点分布，方差可以视为常数。根据中心极限定理，总得分应服从正态分布。

如果你不会很多概率论知识，我们可以用人教版数学选择性必修三的内容解释。数学书上提到了 $3\sigma$ 原则——对于均值为 $\mu$、方差为 $\sigma^2$ 的正态分布，绝大部分样本都落在 $[\mu-3\sigma,\mu+3\sigma]$ 的地方。由于每道题得分的方差视为常数，故总得分服从的正态分布的方差 $\sigma^2=O(n)$，也就是绝大部分样本落在的区间长度约为 $O(\sqrt n)$。

如果你学过概率论，你应该听说过切尔诺夫引理。具体内容比较复杂就不展开了，这个引理表明 $>\epsilon$ 的样本落在的区间长度为 $O(\sqrt{-n\log\epsilon})$。故时间复杂度为 $O(n\sqrt{-n\log\epsilon})$。如果把精度视为常数，这和上面使用高中课本知识推出来的吻合。

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define F(i,a,b) for(int i(a),i##i##end(b);i<=i##i##end;++i)
#define File(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define ll long long
#define fi first
#define se second
using namespace std;
const int MAXN=5e4+1;
const double EPS=1e-12;
int n,t;
double p[MAXN],ans[MAXN]; 
__gnu_pbds::cc_hash_table<int,double>dp[2];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>t;
	F(i,1,n) cin>>p[i];
	sort(p+1,p+n+1,greater<double>());
	dp[0][n]=1;
	F(i,0,n-1){
		int now=i&1,nxt=now^1;
		dp[nxt].clear();
		for(auto qwq:dp[now]) if(qwq.se>EPS){
			if(qwq.fi>=n+t) ans[i]+=qwq.se;
			dp[nxt][qwq.fi+1]+=qwq.se*p[i+1];
			dp[nxt][qwq.fi-1]+=qwq.se*(1-p[i+1]);
		}
	}
	for(auto qwq:dp[n&1]) if(qwq.se>EPS) if(qwq.fi>=n+t) ans[n]+=qwq.se;
	double res=0;
	F(i,1,n) res=max(res,ans[i]);
	cout<<fixed<<setprecision(10)<<res;
	return 0;
} 
```

---

## 作者：伊地知虹夏 (赞：1)

### Description

期末考试有 $n$ 道题。对于每道题，你都可以选择是否作答。

如果选择作答第 $i$ 题，有 $p_i$ 的概率作答正确，$(1-p_i)$ 的概率作答错误。

每道题的评分规则如下：

- 作答正确：得 $1$ 分；
- 不作答：得 $0$ 分；
- 作答错误：倒扣 $1$ 分。

为了不挂科，你需要获得至少 $t$ 分。

**每道题目作答结果是相互独立的。**

在自由选择是否作答每道题的前提下，最大化不挂科的概率。求出不挂科的概率。

-  $1 \leq t \leq n \leq 50\, 000 $；
- $p_i\in [0,1]$，且至多有 $9$ 位小数。

### Analyze

首先按 $p_i$ 从大到小排序，我们发现最优方案一定是一段前缀。考虑设 $f_{i,j}$ 表示 $[1, i]$ 中答对 $j$ 个的最大概率概率，最后答案为 $\max\limits_{j \geq \lceil \frac{i+k}{2} \rceil} f_{i, j}$。

考虑优化它，打个表发现满足 $f_{i,j} \geq 10^{-10}$ 的状态并不多，每次只转移满足条件的 $f_{i,j}$ 即可通过此题。

为什么这个是对的呢？你考虑 $f_i$ 这个函数满足正态分布，那么根据正态分布相关结论（忘了啥结论），$f_{i,j} > \epsilon$ 的解集是个区间，且区间长度为 $O(\sqrt{n \log \epsilon^{-1}})$。时间复杂度 $O(n \sqrt{n \log \epsilon^{-1}})$。

---

