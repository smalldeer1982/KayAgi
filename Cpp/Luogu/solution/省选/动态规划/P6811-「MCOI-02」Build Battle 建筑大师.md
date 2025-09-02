# 「MCOI-02」Build Battle 建筑大师

## 题目背景

WAPER 爱玩 hypixel（世界上最大的 Minecraft 小游戏服务器） 建筑大师！

提示：在本题中，羊毛属于一种方块。

## 题目描述

现在 WAPER 准备玩 $q$ 局建筑大师。在第 $i$ 局游戏的开始，WAPER 会选定一个参数 $m_i$，并 **按顺序** 放置 $n$ 个有颜色的羊毛，羊毛颜色的排列如下：

$$1,\ 2,\ ...\ ,\ m_i-1,\ m_i,\ 1,\ 2,\ ...\ ,m_i-1\ ,m_i\ ,\ ...\ (n-1) \ \bmod \  m_i+1$$

例如 $n=7,m=3$ 时，颜色排列如下：

$$1\ ,2,\ 3,\ 1,\ 2,\ 3,\ 1$$

现在 WAPER 准备打破一些方块（可以一个也不打破，也可以全部打破），WAPER 想知道这样可以产生多少种不同的颜色序列。（两个颜色序列不同当且仅当其长度不同或某一位置的羊毛颜色不同）

因为答案太大，所以输出答案对 $10^9+7$ 取模的结果。

（其实就是询问这个序列本质不同的子序列对 $10^9+7$ 取模的结果）

## 说明/提示

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（5 pts）$\ \ $：$n \le 20$，$q=1$。
- Subtask 2（15 pts）：$n \le 10^3$，$q=1$。
- Subtask 3（15 pts）：$\max\{m_i\} \le 20$，$q=1$。
- Subtask 4（25 pts）：$q=1$。
- Subtask 5（40 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n,q \le 10^6$，$1 \le m_i \le n$。

#### 说明

Minecraft OI Round 2 B

- Maker：WAPER420
- Tester：灵空

$样例不是出题人写的！！！！！！！！$

## 样例 #1

### 输入

```
10 6
1 1 4 5 1 4```

### 输出

```
11
11
833
944
11
833```

## 样例 #2

### 输入

```
1000000 1
114514```

### 输出

```
945636198```

# 题解

## 作者：w4p3r (赞：16)

假设当前询问的$m_i$为$m$，$a_i$为第$i$个羊毛的颜色。

$Subtask\ 1:$

直接暴力枚举所有可能的子序列并用Hash/一些奇奇怪怪的方法判重。

时间复杂度$O(2^n*$判重的时间$)$。期望得分$5$分。

$Subtask\ 2$ && $3:$

考虑DP，$f_i$表示我们匹配到颜色序列第$i$位时的方案数。考虑再在后面添加一个$x$，假设$next_{i,x}$表示$i$右边最近的$x$的位置，则$f_{next_{x,i}}+=f_i$。

因为我们这种贪心匹配（每次选择最近的一个），所以不会计算重复。

时间复杂度$O(n*max \{ m_i\})$。期望得分$35$分。

$Subtask\ 4:$

我们这样只是将这个序列当成一个普通序列来做的，并没有利用其良好的性质。

我们考虑对于$x$，只有$x-m$，$x-m-1$，...，$x-1$会转移到$x$（因为更前面的点会转移到$x-m$）。

所以$f_i=f_{i-1}+f_{i-2}+...+f_{i-m}$，前缀和优化即可。

时间复杂度$O(n)$，期望得分$60$分。

$Subtask\ 5:$

假设$s_i=\sum_{j=1}^{i}f_j$，所以$s_i=2*s_{i-1}-s_{i-m-1}$，而我们要求的就是$s_n$。

可以考虑把这个问题转换成另一个问题：

从$0$出发走到$n$，有一个初始等于$1$的阈值$v$，有两种行动方式：

$1.$从$x$走到$x+1$，并让$v=2*v$。

$2.$从$x$走到$x+m+1$，并让 $v=-v$。

每次走到$n$之后，让初始为$0$的$ans+=v$。可以发现转换问题后$s_n=ans$（即跟原问题等价）。

可以发现$v$的值只跟两种行动方式的次数有关，所以考虑枚举行动方式$2$的次数，则可以得到：

$s_n=ans=\sum_{i=0}^{i\le \lfloor \frac{n}{m+1} \rfloor}2^{n-(m+1)*i}*(-1)^{i}* \binom{(n-(m+1)*i)+i}{i}$

(行动方式$2$走了$i$步，行动方式$1$会走$n-(m+1)*i$步，总共就会走$(n-(m+1)*i)+i$步)

可以对所有$m$直接暴力算出这个式子的值，这样时间复杂度是$n/1+n/2+...+n/n=O(nlogn)$的。期望得分$100$分。

总体来说本题应该是一道比较良心的签到题，有经验的OIer应该可以直接秒掉。出题人认为这题应该比A简单，但是书虫非要我放B /kk。


为啥那么多人会60不会100啊，这trick不是挺常见的嘛/fad。

upd：我才发现我上面的系数写反了，感谢@2016wudi的指出qwq。

---

## 作者：gghack_Nythix (赞：3)

## 前言：
这种题目还是不看题解，自己思考出来比较有意思。
## 分析：

爆搜的分数很好拿，不再赘述。

然后对于 $\max\{m_i\}\leq20$，也许可以使用矩阵乘法在 $\mathcal{O(m^3\log n)}$ 的时间复杂度内解决，但是这玩意我没写，而且还不如直接转移。

考虑怎么拿 60pts。

设 $dp_i$ 表示选到第 $i$ 位的颜色序列的个数，设 $L_{i,a}$ 表示 $i$ 位置前一个颜色为 $a$ 的羊毛所在位置。

则容易发现，在 $L_{i,a}-1$ 以及其前面的所有羊毛都在 $[L_{i,a},i]$ 被 $dp_{L_{i,a}}$ 处转移到。所以说把这一部分重复转移的减掉，得到：
$$
dp_i=\sum\limits_{j=1}^{i-1}dp_j-\sum\limits_{j=1}^{L_{i,a}-1}dp_j=\sum\limits_{j=L_{i,a}}^{i-1}dp_j
$$

由于此题序列的特殊性，$L_{i,a}$ 就是 $i-m$，带入后前缀和优化上述转移即可。

考虑怎么拿 100pts。

将上文的前缀和以 $S_i$ 表示，则我们要求的其实就是 $S_n$，表示 $1$ 到 $n$ 的方案数，同时 $S_i=2\times S_{i-1}-S_{i-m-1}$，不理解可自行画图。

观察到我们的转移过程可以这样子表示：

- 有一个值 $x$ 表示当前的位置，有一个值 $v$ 表示当前的 $S_x$。

- 每次可以让 $x$ 加上 $1$，并将 $v$ 翻倍，记作一操作。

- 每次也可以让 $x$ 加上 $m+1$，并将 $v$ 符号取反，记作二操作。

- 每次 $x$ 到 $n$ 后，将 $S_n$ 加上 $v$。

很显然，这个二操作只会影响到符号，那么枚举二操作的操作次数，记为 $q$，那么操作一会执行 $n-q\times (m+1)$ 次，总共会进行 $q+n-q\times (m+1)$ 次。权值为 $2^{n-q\times (m+1)} \times (-1)^{q}$，操作方法为 $\operatorname{C}_{q+n-q\times (m+1)}^{q}$ 种，其实就是把 $q$ 个二操作放在所有操作中的任意位置形成的不重复操作序列的方案数。

那么就有：

$$
S_n=\sum\limits_{q=0}^{\left \lfloor \frac{n}{m+1} \right \rfloor }2^{n-q\times (m+1)} \times (-1)^{q} \times \operatorname{C}_{q+n-q\times (m+1)}^{q}
$$

这玩意直接预处理即可，然后就做完了。

[代码](https://www.luogu.com.cn/paste/szwchre9)

---

## 作者：wwwwwza (赞：0)

求本质不同子序列 dp 方程：$f_i=2\times f_{i-1}-f_{lst_{a_i}-1}$。

对于本题的 dp 方程：$f_i=2\times f_{i-1}-f_{i-m-1}$。

这个式子可以抽象成走路计数问题，即往前走 $1$ 步，价值乘二；往前走 $m+1$ 步，代价取相反数，求所有走到 $n$ 的方案代价。

可以发现，其怎么走不重要，重要的是往前走 $m+1$ 步的次数，可以枚举这个次数，这样就能简单求出最后的价值，走路方案可以抽象成格路计数问题。

答案就为 $\sum\limits_{i=0}^{\left \lfloor \frac{n}{m+1} \right \rfloor } (-1)^i\times 2^{n-(m+1)\times i} \times \binom{n-(m+1)\times i+i}{i}$。

这是一个调和级数，时间复杂度是 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e6+5;
const int inf=2e6;
const int mod=1e9+7;
int n,q,x,ans[N],vis[N],fac[N],inv[N],two[N];
int ksm(int a,int b){
	int sum=1;
	while(b){
		if(b&1)sum=1ll*sum*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return sum;
}
int c(int n,int m){
	if(n<0||m<0||n<m)return 0;
	return 1ll*(1ll*fac[n]*inv[m]%mod)*inv[n-m]%mod;
}
int solve(int m){
	if(vis[m])return ans[m];
	vis[m]=1;
	int res=0;
	for(int i=0;i<=n/(m+1);i++){
		int cnt=1ll*two[n-(m+1)*i]*c(n-(m+1)*i+i,i)%mod;
		if(i&1)res=(res-cnt+mod)%mod;
		else res=(res+cnt)%mod;
	}
	return ans[m]=res;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin >>n>>q;
	fac[0]=two[0]=1;
	for(int i=1;i<=inf;i++)fac[i]=1ll*i*fac[i-1]%mod,two[i]=2ll*two[i-1]%mod;
	inv[inf]=ksm(fac[inf],mod-2);
	for(int i=inf-1;i>=0;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
	while(q--){
		cin >>x;
		cout <<solve(x)<<"\n";
	}
	return 0;
}

```

---

## 作者：Svemit (赞：0)

考虑一次询问怎么做。

这是一个经典问题，设 $f_i$ 表示 $1 - i$ 的本质不同子序列个数，我们有 $f_i = 2 \times f_{i - 1} - f_{lst_{a_i} - 1}$，其中 $lst_{a_i}$ 指 $a_i$ 上一次出现的位置。本题中 $lst_i = i - m$。

一次询问的话直接做即可。

发现 $f_i = 2 \times f_{i - 1} - f_{i - m - 1}$ 这式子并不好直接优化。

考虑组合意义，从 0 开始走，初始权值是 1，如果从 $i$ 走到 $i + 1$，那么权值翻倍，否则权值取负。发现最终权值只和中间取了多少次负有关，并不关心什么时候取负。所以枚举走了多少次 $i$ 到 $i + m + 1$ 这样的操作。

假设对某个 $m$，取了 $i$ 次负，对答案的贡献是 $(-1) ^ i \times 2 ^ {n - (m + 1) \times i} \times \binom {i + n - (m + 1) \times i}{i} $。

对于单个 $m$，复杂度是 $O(\frac {n}{m})$ 的，对所有的 $m$ 算出来就是 $O(n \ln n)$ 的。

代码删去了 modint。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
const int P = 1e9 + 7;
using Z = MInt<P>; 

Z fac[N], infac[N], pw[N];
void init(int n) {
	fac[0] = infac[0] = pw[0] = 1;
	for (int i = 1; i <= n; i ++) {
		fac[i] = fac[i - 1] * i;
		pw[i] = pw[i - 1] * 2;
	}
	infac[n] = (Z)1 / fac[n];
	for (int i = n - 1; i >= 1; i --) {
		infac[i] = infac[i + 1] * (i + 1);
	}
}

Z comb(int a, int b) {
	if (a < 0 || b < 0 || a < b) return 0;
	return fac[a] * infac[a - b] * infac[b];
} 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, q;
    cin >> n >> q;
    init(n + 1);
    vector<Z> ans(n + 1, 0);
    for (int m = 1; m <= n; m ++) {
    	Z sig = 1;
    	for (int i = 0; i <= n / (m + 1); i ++) {
    		ans[m] += sig * pw[n - (m + 1) * i] * comb(n - (m + 1) * i + i, i);
    		sig *= -1;
    	}
    } 
    while (q --) {
    	int m;
    	cin >> m;
    	cout << ans[m] << "\n";
    }

    return 0;
}
```

---

