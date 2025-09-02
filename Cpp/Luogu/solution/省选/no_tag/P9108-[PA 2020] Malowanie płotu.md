# [PA 2020] Malowanie płotu

## 题目描述

**题目译自 [PA 2020](https://sio2.mimuw.edu.pl/c/pa-2020-1/dashboard/) Runda 4 [Malowanie płotu](https://sio2.mimuw.edu.pl/c/pa-2020-1/mal/)**

今年的秋季天气已经完全破坏了 Potyczek 先生的围栏上的漆。围栏需要尽快用特殊的蓝色防水剂进行处理，以免即将到来的冬季对其造成不可弥补的破坏。Potyczek 先生请他邻居的勤劳儿子 Bytie 来做这件事。这个男孩今天早上完成了任务，但做得相当粗心，因为他急着参加下一轮 PA。

Potyczek 先生的围栏由 $n$ 根木条组成，每根木条分为长度相等的 $m$ 段。Bytie 只把每根木条从上到下用防水剂涂了一遍，不幸的是，这可能还不足以把栅栏全部涂满。然而，在每根木条上涂防水剂的段都是连续的，每个段要么完全涂上，要么根本不涂。进一步看来，男孩所涂的那部分栅栏是一致的，即每两个连续的木条上所涂的段都存在一个非空的相交区间。

例如，涂完的围栏可能如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/2ov15dzh.png)

由于以下三个原因，下图所示情况是不可能的。

- 编号为 $1$ 的木条根本没涂防水剂。
- 编号为 $3$ 的木条一致的段没有涂防水剂。
- 编号 $5,6$ 的木条涂防水剂的部分相交区间为空。

![](https://cdn.luogu.com.cn/upload/image_hosting/9f315wbr.png)

编写一个程序，计算 Bytie 按照上述规则可以用多少种不同的方式来涂围栏。如果有一段围栏在其中一种方式中被涂上了颜色，而在另一种方式中没有被涂上颜色，那么就称这两种方式是不同的。方法的数量可能相当多，所以只要输出它除以质数 $p$ 的余数就可以了。

## 说明/提示

#### 数据范围

**本题采用捆绑测试**

对于 $100\%$ 的数据，保证 $1\le n\times m\le 10^7$，$10^8\le p\le 10^9$，$p\in \mathbb{P}$。

## 样例 #1

### 输入

```
3 2 100000007```

### 输出

```
17```

## 样例 #2

### 输入

```
6 9 813443923```

### 输出

```
57```

# 题解

## 作者：wxzzzz (赞：11)

### 前言

由于前一天打完 CF 还打了一会儿 florr，导致赛时写了 1h 假做法，然后又似睡非睡地过了 30min，突然发现暴力很好优化，写了 30min 就过了。

### 思路

设 $f_{i,j}$ 表示最后选的区间为 $[i,j]$ 时的方案数。（这是一个滚动数组，随着枚举当前区间而更新，以节省空间）

$$f_{i,j}=\sum_{[x,y]\cap[i,j]\ne\varnothing}f_{x,y}$$

取出所有与 $[i,j]$ 有交集的区间太麻烦且不好优化，故容斥：

$$f_{i,j}=\sum_{1\le x\le y\le n}f_{x,y}-\sum_{1\le x\le y<i}f_{x,y}-\sum_{j<x\le y\le n}f_{x,y}$$

因此需要维护 $sl_i=\displaystyle\sum_{1\le x\le y\le i}f_{x,y},sr_i=\displaystyle\sum_{i\le x\le y\le n}f_{x,y}$，有：

$$f_{i,j}=sl_m-sl_{i-1}-sr_{j+1}$$

发现转移只关心 $f$ 的某段前缀或后缀的和，故优化状态：$f_{i,j}$ 为原 $f_{j,i}$ 的前缀和，$g_{i,j}$ 为原 $f_{i,j}$ 的后缀和。注意，这里 $f$ 优化后的状态用 $i$ 表示区间右端点，这是为了方便后续优化，因为要钦定右端点取值范围在某一点左边。

现在有：

$$sl_i=sl_{i-1}+\sum_{j\le i} f_{i,j}$$
$$sr_i=sr_{i+1}+\sum_{j\ge i} g_{i,j}$$
$$f_{i,j}=f_{i,j-1}+sl_m-sl_{j-1}-sr_{i+1}$$
$$g_{i,j}=f_{i,j+1}+sl_m-sl_{i-1}-sr_{j+1}$$

注意到转移都是将所有钦定区间某端点后取所有区间，因此进一步优化状态：

$f_i$ 表示当前区间右端点为 $i$ 的所有合法方案之和，$g_i$ 表示当前区间左端点为 $i$ 的所有合法方案之和。

有：

$$\begin{aligned}
f_i&=\sum_{j=1}^i(sl_m-sl_{j-1}-sr_{i+1})\\
&=i\times (sl_m-sr_{i+1})-\sum_{j=1}^i sl_{j-1}\\
g_i&=\sum_{j=i}^m(sl_m-sl_{i-1}-sr_{j+1})\\
&=(m-i+1)\times(sl_m-sl_{i-1})-\sum_{j=i}^m sr_{j+1}
\end{aligned}$$

上面两式的末项均可前缀和维护。

最后 $sl,sr$ 的转移是容易的：

$$sl_i=sl_{i-1}+f_i$$
$$sr_i=sr_{i+1}+g_i$$

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
long long ans, MOD, f[10000005], g[10000005], sl[10000005], sr[10000005], ssl[10000005], ssr[10000005];
long long mod(long long x) {
    return x % MOD;
}
int main() {
    cin >> n >> m >> MOD;
    for (int i = 1; i <= m; i++)
        f[i] = mod(i);
    for (int i = m; i >= 1; i--)
        g[i] = mod(m - i + 1);
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            sl[j] = mod(sl[j - 1] + f[j]);
        for (int j = m; j >= 1; j--)
            sr[j] = mod(sr[j + 1] + g[j]);
        for (int j = 1; j <= m; j++)
            ssl[j] = mod(ssl[j - 1] + sl[j]);
        for (int j = m; j >= 1; j--)
            ssr[j] = mod(ssr[j + 1] + sr[j]);
        for (int j = 1; j <= m; j++)
            f[j] = mod(j * (sl[m] - sr[j + 1]) - ssl[j - 1]);
        for (int j = 1; j <= m; j++)
            g[j] = mod((m - j + 1) * (sl[m] - sl[j - 1]) - ssr[j + 1]);
    }
    for (int i = 1; i <= m; i++)
        ans = mod(ans + g[i]);
    ans = mod(ans + MOD);
    cout << ans;
    return 0;
}
```

---

## 作者：Argon_Cube (赞：9)

不会简单容斥/ll

----

显然有一个暴力的 $\Theta(nm^2)$ DP，但是我不会优化。

两个区间 $[l_{i-1},r_{i-1}],[l_i,r_i]$ 如果相交，需要两个条件同时**不满足**：

1. $r_{i-1}<l_{i}$;
2. $r_{i}<l_{i-1}$。

如果只需要管一个条件多好啊！这样就只需要记录其中一个端点（条件 1. 需要记录右端点，2. 需要记录左端点）的位置，状态就只有二维了。

于是我们考虑对于每个 $1\leq i<n$，钦定 $i$ 与 $i+1$ 之间只需要**不满足** 1. 和 2. 中的某一个，这样就有 $2^{n-1}$ 种条件选取方案。如果某个区间选取方案**满足**了 $k$ 个位置上的条件那么认为这个方案的权值为 $(-1)^k$。可以发现所有方案（一共 $2^{n-1}\binom m2^n$ 种）的权值和即为 $2^{n-1}$ 倍的合法方案数。

容易发现如果某个方案不合法，那么在不合法的位置一定恰好满足了一个条件，所以就可以将它的贡献一正一负抵消；合法的方案无论怎么选取条件都是合法的所以会被算恰好 $2^{n-1}$ 次。这样就起到了容斥的效果。

于是设 $f_{1/2,i,j}$ 代表当前在第 $i$ 列，这一列与下一列需要满足条件 1. 或 2.，要记录的端点的位置为 $j$ 的方案权值和。容易用两次差分优化转移。

可以发现 $f_1$ 和 $f_2$ 是对称的，可以合并成一个数组。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <array>

#define rgall(arr) (arr).begin(),(arr).end()
#define rgcnt(arr,cnt) (arr).begin(),(arr).begin()+(cnt)
#define rgo1(arr,cnt) (arr).begin()+1,(arr).begin()+1+(cnt)
#define rgany(arr,cnt,offset) (arr).begin()+(offset),(arr).begin()+(offset)+(cnt)

using namespace std;

long long fast_pow(long long base,long long exp,long long moder)
{
    long long result;
    for(result=1;exp;exp&1?result=result*base%moder:true,base=base*base%moder,exp>>=1);
    return result;
}

vector<long long> dp,dp0;

int main(int argc,char* argv[],char* envp[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n,m,moder;
    cin>>n>>m>>moder;
    dp.resize(m+4),dp[m]=1;
    for(int i=1;i<=n;i++)
    {
        dp0=dp,fill(rgall(dp),0);
        for(int j=1;j<=m;j++)
        {
            long long a=dp0[m-j+1];
            dp[j]+=a*j%moder,dp[j+1]-=a*(j-1)%moder,dp[m-j+2]-=a;
        }
        for(int j=1;j<=m;j++)
            (dp[j]+=dp[j-1])%=moder;
        for(int j=1;j<=m;j++)
            (dp[j]+=dp[j-1]+moder*2)%=moder;
    }
    long long answer=0;
    for(int j=1;j<=m;j++)
        answer+=dp[j];
    cout<<answer%moder;
    return 0;
}
```

---

## 作者：鱼跃于渊 (赞：5)

赛场上想到了一个做法，虽然还是 dp，但是优化方向与目前的题解都不同，可惜写得丑被卡常了。  

## 题意

> 给定 $n,m$，一个长为 $n$ 的区间序列 ${[l_1,r_1],[l_2,r_2]\ldots[l_n,r_n]}$ 合法当且仅当：  
> 1. $\forall i\in [1,n],1\le l_i\le r_i\le m$。  
> 2. $\forall i\in [1,n-1],[l_i,r_i]\cap[l_{i+1},r_{i+1}] \neq \emptyset$。  
> 
> 求合法序列个数对给定质数 $p$ 取模的结果。  

## 解法

我们对于每个可能的开头按照以其开头的合法序列画出一棵树来，以样例 $n=3,m=2$ 为例，可以画出：  

![](https://cdn.luogu.com.cn/upload/image_hosting/22qpx5mv.png)  

显然答案就是这三棵树中叶子节点的数量。  
另外可以发现：对于相同的结点来说，其子结点也相同；而如果高度也相同的话，则其子树内的叶子结点数也相同。  
更进一步的，设 $w_{i,l,r}$ 为以第 $i$ 层 $[l,r]$ 为根的子树内叶子结点的数量，则答案就等于 $\sum_{l=1}^{n}\sum_{r=l}^{n} w_{1,l,r}$。  
还可以发现的是，直接计算子结点似乎不可行，因为总共有 $\frac{m\times(m+1)}{2}$ 棵树，每棵树又有 $n$ 层，实在是不好找规律。所以思考如何求出 $w_{i,l,r}$。  
首先显然的是 $w_{n,l,r}\gets 1$，都在最底层了肯定是叶子结点。  
略微思考可以得出转移式：  
$$ w_{i,l,r}\gets \sum_{r'=l}^{r}\sum_{l'=1}^{r'} w_{i+1,l',r'}$$  
于是 $O(nm^4)$ 的做法就出来了，可以使用滚动数组优化，代码此处略。  

我们思考一下如何优化上述式子，可以想到 $w_{i,l,r}$ 相比起 $w_{i,l,r-1}$ 来说只多了 $\sum_{r'=r}^{n} w_{i+1,r,r'}$ 这一部分，而这无疑可以优化：我们令 $sum_l\gets \sum_{r=l}^{n} w_{i+1,l,r}$，则 $w_{i,l,r}\gets w_{i,l,r-1}+sum_{r}$。  
现在考虑如何计算 $w_{i,l,l}$，它的结果来源于所有包含 $[l,l]$ 的区间，发现这可以使用差分维护。也就是说，设差分数组 $tub$，令 $\forall 1\le l\le r\le n,tub_{l}\gets tub_{l}+w_{i+1,l,r}$ 并且 $tub_{r+1}\gets tub_{r+1}-w_{i+1,l,r}$，最后对 $tub$ 数组做一遍前缀和，则 $w_{i,l,l}\gets tub_l$。  
发现上面提到的都可以在 $O(m^2)$ 的时间内计算出来，所以总时间复杂度为 $O(nm^2)$。  
另外在实现中可以简化掉 $w$ 的第一维，只保留 $w_{l,r}$，主要代码如下：  
```cpp
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
inline int gmod(int x){
	return (x<0?x+mod:(x<mod?x:(x<(mod<<1)?x-mod:x%mod)));
}
...
rep(round,n-1,1){
	fill(tub+1,tub+m+2,0);
	per(i,1,m) per(j,i,m){
		tub[i]=gmod(tub[i]+w[i][j]);
		tub[j+1]=gmod(tub[j+1]-w[i][j]);
	}
	per(i,1,m) tub[i]=gmod(tub[i]+tub[i-1]);
	per(i,1,m){
		w[i][i]=tub[i];
		per(j,i+1,m) w[i][j]=gmod(w[i][j-1]+sum[j]);
	}
    per(i,1,m){
	    sum[i]=0;
	    per(j,i,m) sum[i]=gmod(sum[i]+w[i][j]);
	} 
}
```
这样可以拿到 40pts 的好成绩！但是还不够。  

我们观察一下上面的代码，可以发现能对 $tub_{l}$ 产生影响的只有左端点为 $l$ 的区间，能对 $tub_{r+1}$ 产生影响的只有右端点为 $r$ 的区间，显然这部分可以优化。  
我们令 $suml$ 为原先的 $sum$，意义一样；另外再设 $sumr$，令 $sumr_r\gets \sum_{l=1}^{r} w_{l,r}$（这里的 $w_{l,r}$ 还是下一层的），意义和 $suml$ 正好相反。则 $tub_i\gets suml_i-sumr_{i-1}$，再做一遍前缀和。
这部分的时间复杂度降到了 $O(m)$，接着看下一部分。  
考虑如何快速计算 $suml,sumr$，发现必须去掉 $w_{l,r}$，不然时空复杂度降不下来。  
所以我们考虑从下一层的 $suml',sumr'$ 计算而来，因为在第 $n$ 层时这两个是相当好求的，此时 $suml_i\gets m-i+1,sumr_i\gets i$。  
我们思考一下当前的 $suml,sumr$ 和下一层的 $suml',sumr'$ 有何关联，以 $suml$ 为例：  
$$suml_l\gets \sum_{r=l}^{n} w_{l,r} \\w_{l,r}\gets \begin{cases}tub_{l} &\text{if }l=r\\w_{l,r-1}+suml'_{r} &\text{if }l<r\end{cases}$$  

优化是显然的，我们令 $suf_{i}\gets suf_{i+1}+suml'_{i}\times (m-i+1)$，则 $suml_i\gets suf_i+tub_i\times(m-i+1)$。  
类似的，我们令 $pre_{i}\gets pre_{i-1}+sumr'_{i}\times i$，则 $sumr_i\gets pre_i+tub_i\times i$。  
于是这一部分的时间复杂度也降为 $O(m)$。  
现在总时间复杂度为 $O(nm)$，可以通过此题。  

回顾一下，可以发现其他做法是尝试将 $dp_{i,l,r}$ 中的 $l$ 或 $r$ 优化掉，而此做法是尝试将 $dp_{i,l,r}$ 中的 $i$ 优化掉。  
因为笔者考场上并没有往 dp 方面想，所以优化方向较其他题解有些距离。  

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace fisher{
#define int long long
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
const int N=1e7+5;
int n,m,mod,ans;
int pre,suf,x,tub[N],suml[N],sumr[N];
inline int gmod(int x){
	return (x<0?x+mod:(x<mod?x:(x<(mod<<1)?x-mod:x%mod)));
}
void main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>m>>mod;
	per(i,1,m) suml[i]=(m-i+1),sumr[i]=i;
	rep(rs,n-1,1){
		per(i,1,m) tub[i]=gmod(tub[i-1]+suml[i]-sumr[i-1]);
		pre=suf=0;
		rep(i,m,1){
			x=suml[i];
			suml[i]=gmod(suf+tub[i]*(m-i+1));
			suf=gmod(suf+x*(m-i+1));
		}
		per(i,1,m){
			x=sumr[i];
			sumr[i]=gmod(pre+tub[i]*i);
			pre=gmod(pre+x*i);
		}
	}
	per(i,1,m) ans=gmod(ans+suml[i]);
	cout<<ans<<'\n';
}}
signed main(){
	fisher::main();
	return 0;
}
```

---

## 作者：Sol1 (赞：4)

考虑 dp，设 $f_{i,j}$ 表示前 $i$ 列，强制第 $i$ 列第 $j$ 行被涂上，以及第 $i$ 列第 $j+1\sim m$ 行没有被涂上的方案数。（即强制涂上的区间的下端点是 $j$）

注意到这等于前 $i$ 列，强制第 $i$ 列第 $m-j+1$ 行被涂上，以及第 $i$ 列第 $1\sim m-j$ 行没有被涂上的方案数。（即强制涂上的区间的上端点是 $m-j+1$）

则从第 $i-1$ 列向第 $i$ 列转移时，考虑强制第 $i-1$ 列涂上的区间的上端点是 $k$。我们要求 $k\leq j$。

同时，第 $i$ 列的区间上端点可以在 $1\sim j$ 里面任意选择，于是我们得到转移式：

$$f_{i,j}=j\cdot\sum_{k=m-j+1}^mf_{i-1,k}$$

然而这是错的，因为这样可能统计到 $i-1$ 列的区间下端点在 $i$ 列的区间上端点上面的情况。

考虑直接把这种情况容斥掉。为了统计这种情况的数量，我们再从 $i-1$ 列的下端点考虑，得到最终的转移式：

$$f_{i,j}=j\cdot\sum_{k=m-j+1}^mf_{i-1,k}-\sum_{k=1}^{j-1}(j-k)f_{i-1,k}$$

使用一些前缀和优化，复杂度 $O(nm)$。

```cpp
long long mod, f[2][10000005];

int main() {
    cin >> n >> m >> mod;
    for (int i = 1;i <= m;i++) f[1][i] = i;
    for (int i = 2;i <= n;i++) {
        long long sum1 = 0, sum2 = 0, sum3 = 0;
        for (int j = 1;j <= m;j++) {
            sum1 = (sum1 + f[i - 1 & 1][m - j + 1]) % mod;
            f[i & 1][j] = (sum1 * j - sum3 + mod) % mod;
            sum2 = (sum2 + f[i - 1 & 1][j]) % mod;
            sum3 = (sum3 + sum2) % mod;
        }
    }
    long long ans = 0;
    for (int i = 1;i <= m;i++) ans = (ans + f[n & 1][i]) % mod;
    cout << ans << endl;
    return 0;
}
```

---

## 作者：wwwwwza (赞：3)

推式子题。

设 $dp_{i,l,r}$ 表示第 $i$ 次涂 $[l,r]$ 的方案数。

转移式显然：$dp_{i,l,r}=\sum\limits_{x=1}^r\sum\limits_{y=\max(x,l)}^m dp_{i-1,x,y}$。

容斥一下：$dp_{i,l,r}=\sum\limits_{x=1}^m\sum\limits_{y=x}^m dp_{i-1,x,y}-\sum\limits_{x=1}^{l-1}\sum\limits_{y=x}^{l-1} dp_{i-1,x,y}-\sum\limits_{x=r+1}^{m}\sum\limits_{y=x}^{m} dp_{i-1,x,y}$。

发现这是一个前缀后缀的形式，设 $f_{i,j}=\sum\limits_{x=1}^j\sum\limits_{y=x}^j dp_{i,l,r},g_{i,j}=\sum\limits_{x=j}^m\sum\limits_{y=x}^m dp_{i,l,r}$。

所以 $dp_{i,l,r}=f_{i-1,m}-f_{i-1,l-1}-g_{i-1,r+1}$。

开始推式子。

$$
f_{i,j}
=\sum\limits_{l=1}^j\sum\limits_{r=l}^j dp_{i,l,r}
=\sum\limits_{l=1}^j\sum\limits_{r=l}^j f_{i-1,m}-f_{i-1,l-1}-g_{i-1,r+1}
=\frac{j\times(j+1)}{2}f_{i-1,m}-\sum\limits_{l=1}^j (j-l+1)\times f_{i-1,l-1}-\sum\limits_{r=1}^j r\times g_{i-1,r+1}
=\frac{j\times(j+1)}{2}f_{i-1,m}-\sum\limits_{l=1}^j j\times f_{i-1,l-1}-\sum\limits_{r=1}^j r\times g_{i-1,r+1}+\sum\limits_{l=1}^j (l-1)\times f_{i-1,l-1}
$$

$$
g_{i,j}
=\sum\limits_{l=j}^m\sum\limits_{r=l}^m dp_{i,l,r}
=\sum\limits_{l=j}^m\sum\limits_{r=l}^m f_{i-1,m}-f_{i-1,l-1}-g_{i-1,r+1}

=\frac{(m+j)\times(m-j+1)}{2}f_{i-1,m}-\sum\limits_{l=j}^m (m-l+1)\times f_{i-1,l-1}-\sum\limits_{r=j}^m (r-j+1)\times g_{i-1,r+1}
=\frac{(m+j)\times(m-j+1)}{2}f_{i-1,m}-\sum\limits_{l=j}^m (m-l+1)\times f_{i-1,l-1}-\sum\limits_{r=j}^m r\times g_{i-1,r+1}+\sum\limits_{r=j}^m (j-1)\times g_{i-1,r+1}
$$

可前缀和优化，时间复杂度 $O(nm)$。

答案为 $f_{n,m}$，要用滚动数组优化。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+5;
int n,m,p,f[2][N],g[2][N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin >>n>>m>>p;
	for(int i=1;i<=m;i++)f[1][i]=(f[1][i-1]+i)%p;
	for(int i=m;i>=1;i--)g[1][i]=(g[1][i+1]+m-i+1)%p;
	for(int i=2;i<=n;i++){
		int now=i&1;
		for(int j=1,a=0,b=0,c=0,t=0;j<=m;j++){
			t=(t+j)%p;
			a=(a+j*g[now^1][j+1]%p)%p;
			b=(b+f[now^1][j-1])%p;
			c=(c+f[now^1][j-1]*(j-1)%p)%p;
			f[now][j]=(t*f[now^1][m]%p-a-b*j%p+c+p*2)%p;
		}
		for(int j=m,a=0,b=0,c=0,t=0;j>=1;j--){
			t=(t+m-j+1)%p;
			a=(a+(m-j+1)*f[now^1][j-1]%p)%p;
			b=(b+g[now^1][j+1]*j%p)%p;
			c=(c+g[now^1][j+1])%p;
			g[now][j]=(t*f[now^1][m]-a-b+c*(j-1)%p+p*2)%p;
		}
	}
	cout <<f[n&1][m];
	return 0;
}
```

---

## 作者：NightDiver (赞：3)

状态数是 $O(nm^2)$ 的DP很好想，就是 $dp_{i,l,r}$ 表示第 $i$ 次的区间为 $[l,r]$ 的方案数。

但是这个状态数就已经死了，而题目又提示 $n\times m \leq 10^{7}$ ，说明状态只能形如 $dp_{i,j}$。

这时就会想到一个简陋的打补丁方式：设 $f_{i,l},g_{i,r}$ 分别表示第 $i$ 次以 $l$ 为左端点的所有区间的方案数，以 $r$ 为右端点的所有区间的方案数。

因为 $f,g$ 本质相同，所以下面都只关注 $f$。

设第 $i$ 个区间为 $[l,r]$，第 $i-1$ 个为 $[l',r']$。那么两者相交的话，有以下四种情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/xnqyqd78.png)

方便表述，起个简称：包含，左交，右交，被包含（主语是第 $i$ 个区间）。

我们希望求出 $f_{i,l}$，那么先暴力地转移。那么枚举右端点 $r$，对于1，2种，直接 $f_{i-1,l\textcolor{red}<l'\leq r} \to f_{i,l}$。

那么3，4种呢？如果仿照刚刚直接把右端点 $\geq r$ 的 $g_{i-1}$ 全部加入，那么会有些区间算重复。

观察3，4有没有1，2没有的性质用来转移？是的，他们都与 $[l,r]$ 区间的左端点有交。

故我们再开一个数组 $h_{i,j}$，表示第 $i$ 个区间**经过** $j$ 的方案数。$h_{i-1,l}\to f_{i,l}$ 就行啦（这也是为什么刚刚使用小于号的原因）。

注意我们现在只列出了暴力转移的方程，推推式子前缀和优化就行了。
$$
\begin{aligned}
f_{i,l} & = \sum_{r=l}^{n} h_{i-1,l}+f_{i-1,l<l'\leq r}
\\
& = (n-l+1)h_{i-1,l}+\sum_{r=l}^{n}Sf_{i-1,r}-Sf{i-1,l}
\\
& = (n-l+1)h_{i-1,l}+\sum_{r=l}^{n}Sf_{i-1,r}-(n-l+1)Sf_{i-1,l}
\end{aligned}
$$

$$
\begin{aligned}
g_{i,r}&=\sum_{l=1}^{r}h_{i-1,r}+g_{i-1,l\leq r' < r}
\\
& = r\times h_{i-1,r} + \sum_{l=1}^{r} Sg_{i-1,r-1}-Sg_{i-1,l-1}
\\
& = r\times h_{i-1,r} + r \times Sg_{i-1,r-1} - \sum_{l=1}^{r} Sg_{i-1,l-1}
\end{aligned}
$$

$$
tot=\sum_{l=1}^n f_{i,l}
\\
\begin{aligned}
h_{i,j}=tot-\sum_{r<j}g_{i,r}-\sum_{l>j}f_{i,l}
\end{aligned}
$$

$S_f,S_g$ 表示一次前缀和，还要用二次前缀和优化。

[代码在这里](https://www.cnblogs.com/TongKa/p/18394697)

---

## 作者：liyixin0514 (赞：2)

# [P9108 [PA2020] Malowanie płotu](https://www.luogu.com.cn/problem/P9108)

[可能更好的阅读体验](https://www.cnblogs.com/wingheart/p/18660383)

## 题意

有一个 $n \times m$ 的方格，你需要对每一列涂一个非空连续段，要求相邻列的涂色连续段有交。问涂色方案数。

$n \times m \le 10^7$。

## 思路

我们需要一个 $O(nm)$ 的算法，但是不好直接设一个 $O(nm)$ 的状态。

很容易想到设 $f_{i,l,r}$ 表示考虑到第 $i$ 列，第 $i$ 列涂 $[l,r]$ 的方案数。

$$f_{i,l,r} = \sum_{[l',r'] \cap [l,r] \neq \emptyset} f_{i-1,l',r'}$$

然后你发现这个交非空直接做是一个三维偏序，可以差分成二维偏序，但是仍然很麻烦。

考虑经典的，变成求全集减去不交的，即：

$$f_{i,l,r} = \sum_{l' \le r'} f_{i-1,l',r'} - \sum_{l' \le r' < l} f_{i-1,l',r'} - \sum_{r < l' \le r'} f_{i-1,l',r'}$$

然后我们就可以设 

$$
s0_{i,j} = \sum_{l \le r \le j} f_{i,l,r},s1_{i,j} = \sum_{j \le l \le r} f_{i,l,r}\\
f_{i,l,r} = s0_{i-1,m} - s0_{i-1,l-1} - s1_{i-1,r+1}
$$

这样就可以状态 $O(nm^2)$，转移 $O(1)$ 做到总共 $O(nm^2)$ 的复杂度了。

-----

我们可爱的 $s$ 数组状态只有 $O(nm)$。考虑直接转移 $s$。

$$
\begin{aligned}
s0_{i,j} & = s0_{i,j-1} + \sum_{l\le j} f_{i,l,j}\\
& = s0_{i,j-1} + \sum_{l \le j} s0_{i-1,m} - s0_{i-1,l-1} - s1_{i-1,j+1}\\
& = s0_{i,j-1} + j(s0_{i-1,m} - s1_{i-1,j+1}) - \sum_{l \le j} s0_{i-1,l-1}
\end{aligned}
$$

设

$$
t0_{i,j} = \sum_{k \le j} s0_{i,k}
$$

则

$$
s0_{i,j} = s0_{i,j-1} + j(s0_{i-1,m} - s1_{i-1,j+1}) - t0_{i-1,j-1}
$$

同理，有：

$$
t1_{i,j} = \sum_{k \ge j} s1_{i,j}\\
s1_{i,j} = s1_{i,j+1} + (m-j+1)(s0_{i-1,m} - s0_{i-1,j-1}) - t1_{i-1,r+1}
$$

初始 $f_{1,l,r} = 1$，即 $s0_{1,i} = \frac{i(i-1)}{2} + i,s1_{1,i} = \frac{(m-i+1)(m-i)}{2} + m-i+1$，答案是 $\sum f_{n,l,r}$，即 $f0_{n,m}$。

时间复杂度 $O(nm)$。

## code

要注意一点边界细节。

```cpp
#include<bits/stdc++.h>
#define sf scanf
#define pf printf
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
using namespace std;
typedef long long ll;
namespace hesitate {
	constexpr int N=1e7+7;
	int mod;
	int add(int a,int b) { return a+b>=mod ? a+b-mod : a+b; }
	void _add(int &a,int b) { a=add(a,b); }
	int mul(int a,int b) { return 1ll*a*b%mod; }
	void _mul(int &a,int b) { a=mul(a,b); }
	int n,m;
	int s[2][N],t[2][N];
	void main() {
		sf("%d%d%d",&n,&m,&mod);
		rep(j,0,m-1) s[0][j]=add(1ll*j*(j+1)/2%mod,j+1), s[1][j]=add(1ll*(m-j)*(m-j-1)/2%mod,m-j); 
		t[0][0]=s[0][0], t[1][m-1]=s[1][m-1];
		rep(j,1,m-1) t[0][j]=add(t[0][j-1],s[0][j]);
		per(j,m-2,0) t[1][j]=add(t[1][j+1],s[1][j]);
		rep(i,1,n-1) {
			s[0][i*m]=add(s[0][i*m-1],mod-s[1][(i-1)*m+1]);
			t[0][i*m]=s[0][i*m];
			rep(j,1,m-1) {
				int k=i*m+j;
				s[0][k]=add(s[0][k-1],add(mul(j+1,add(s[0][i*m-1],mod-s[1][(i-1)*m+j+1])),mod-t[0][(i-1)*m+j-1]));
				t[0][k]=add(t[0][k-1],s[0][k]);
			}
			s[1][i*m+m-1]=add(s[0][i*m-1],m==1 ? 0 : mod-s[0][i*m-2]);
			t[1][i*m+m-1]=s[1][i*m+m-1];
			per(j,m-2,0) {
				int k=i*m+j;
				s[1][k]=add(s[1][k+1],add(mul(m-j,add(s[0][i*m-1],j==0 ? 0 : mod-s[0][(i-1)*m+j-1])),mod-t[1][(i-1)*m+j+1]));
				t[1][k]=add(t[1][k+1],s[1][k]);
			}
		}
		pf("%d\n",s[0][n*m-1]);
	}
}
int main() {
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("my.out","w",stdout);
    #endif
	hesitate :: main();
}
```

---

## 作者：dAniel_lele (赞：2)

考虑 $dp_{i,j,k}$ 表示看到第 $i$ 列，涂了 $j\sim k$ 行的方案数。

考虑 $j\sim k$ 转移到 $j'\sim k'$ 有哪些情况：

* $j'\leq j$，$k\leq k'$；
* $j<j'\leq k'<k$；
* $j<j'\leq k$，$k\leq k'$；
* $j'\leq j$，$j\leq k'<k$。

分别使用前缀和/差分即可在 $O(nm^2)$ 时间内解决。

考虑优化，设 $dp_{i,j}$ 表示看到第 $i$ 列，对于所有 $k$，涂了 $k\sim j$ 行的方案数之和。考虑转移：

* $dp_{i,j}\times j\to dp_{i,k}$，其中 $j\leq k$；
* $dp_{i,j}\times k\to dp_{i,k}$，其中 $j>k$；

然而，在第二种转移中，$k<k'\leq j$ 的涂了 $k'\sim j$ 行的方案数应当被扣减。不难发现被扣减的其实是以 $j>k$ 的所有 $j$ 为左端点的方案。由对称性可以转化为 $j\leq m-k$ 的 $dp_{i,j}$ 之和。扣减即可。

可以使用前缀和优化到 $O(nm)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
int dp[10000005],tmp[10000005];
signed main(){
	int n,m,mod; cin>>n>>m>>mod;
	for(int i=1;i<=m;i++) dp[i]=i;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=m;j++) tmp[j]=0;
		int prex=0,prey=0,prez=0;
		for(int j=1;j<=m;j++){
			(prex+=dp[j])%=mod;
			(prey+=dp[j]*j)%=mod;
			(prez+=dp[m-j+1])%=mod;
			tmp[j]=(prey+(prez-prex+mod)*j)%mod;
		}
		for(int j=1;j<=m;j++) dp[j]=tmp[j];
	}
	int ans=0;
	for(int j=1;j<=m;j++) (ans+=dp[j])%=mod;
	cout<<ans;
	return 0;
}

```

---

## 作者：BlackHoles (赞：1)

### 前置知识

动态规划 DP，前缀和。

### 题意简述

求一个大小为 $n$ 的区间序列 $\{[L_1, R_1], [L_2, R_2]..., [L_n, R_n]\}$ 的个数满足任意 $1 \le i \le n$，有 $1 \le L_i \le R_i \le m$，且任意两相邻区间交集不为空集。

### 正解

观察数据范围，不难想到设计一个状态数为 $O(nm)$ 的 DP 方程，于是设 $f_{i, j}$ 表示考虑前 $i$ 个区间，第 $i$ 个区间右端点为 $j$ 的方案数。

注意到实际意义：第 $i$ 个区间右端点为 $j$ 的方案数也就是第 $i$ 个区间左端点为 $m - j + 1$ 的方案数。

运用一点容斥的思想，状态转移方程就能写出来了。

$$
f_{i, j} = k \times \sum_{k = m - j + 1}^m f_{i - 1, k} - \sum_{k = 1}^{j - 1} (f_{i - 1, k} \times (j - k))
$$

每次对 $f$ 数组运用一些前缀和数组优化，同时对 $f$ 使用滚动数组技巧，做到时间复杂度 $O(nm)$，空间复杂度 $O(m)$，可以通过。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, p, ans;
void init(int i, vector <int> &f, vector <int> &suf, vector <int> &sufn, vector <int> &pre) {
	for (int j = m; j >= 1; --j)
		suf[j] = (suf[j+1] + f[j]) % p;
	for (int j = 1; j <= m; ++j)
		pre[j] = (pre[j-1] + f[j]) % p;
	for (int j = m; j >= 1; --j)
		sufn[j] = (sufn[j+1] + (ll)f[j] * (m - j + 1) % p) % p;
	return ;
}
int main(void) {
	scanf("%d %d %d", &n, &m, &p);
	vector <int> f(m + 3);
	vector <int> suf(m + 3, 0), sufn(m + 3, 0), pre(m + 3, 0);
	for (int j = 1; j <= m; ++j)
		f[j] = j;
	init(1, f, suf, sufn, pre);
	for (int i = 2; i <= n; ++i) {
		for (int j = 1; j <= m; ++j)
			f[j] = ((ll)suf[m-j+1] * j % p - ((ll)sufn[1] - sufn[j] - (ll)pre[j-1] * (m - j + 1) % p) + (p << 1)) % p;
		init(i, f, suf, sufn, pre);
	}
	for (int j = 1; j <= m; ++j)
		ans = ((ll)ans + f[j]) % p;
	printf("%d", ans);
	return 0;
}
```

---

## 作者：TH911 (赞：1)

> [题目传送门](https://www.luogu.com.cn/problem/P9108)
>
> [神秘链接](https://www.cnblogs.com/TH911/p/-/P9108)
>
> 绝世前缀和优化 DP 好题。

# 题意分析

即找出长度为 $n$ 的序列 $\langle[l_1,r_1],[l_2,r_2],\cdots,[l_n,r_n]\rangle$ 的个数，且满足：

* $l_i,r_i$ 为整数，且 $1\leq l_i\leq r_i\leq m$。
* 对于 $1\leq i<n$，有 $[l_i,r_i],[l_{i+1},r_{i+1}]$ 相交。

# 朴素 DP

设 $\textit{dp}_{i,l,r}$ 为第 $i$ 项为 $[l,r]$ 的方案数。

枚举第 $i-1$ 项 $[l_2,r_2]$，有：

$$
\textit{dp}_{i,l,r}=\sum_{l_2=1}^m\sum_{r_2=l_2}^{m}[[l,r]\cap[l_2,r_2]\neq\varnothing]\textit{dp}_{i-1,l_2,r_2}
$$

答案即：

$$
\sum_{l=1}^m\sum_{r=l}^m\textit{dp}_{n,l,r}
$$


朴素转移 $\mathcal O\left(nm^4\right)$。

# 前缀和优化 DP

发现，与区间 $[l,r]$ 有交的 $[l_2,r_2]$ 可以**用所有合法区间减去无交区间**得到。

因此可以有：

$$
\begin{aligned}
\textit{dp}_{i,l,r}&=\sum_{l_2=1}^m\sum_{r_2=l_2}^{m}[[l,r]\cap[l_2,r_2]\neq\varnothing]\textit{dp}_{i-1,l_2,r_2}\\
&=\sum_{l_2=1}^m\sum_{r_2=l_2}^m\textit{dp}_{i-1,l_2,r_2}-\sum_{l_2=r+1}^m\sum_{r_2=l_2}^m\textit{dp}_{i-1,l_2,r_2}-\sum_{r_2=l-1}^m\sum_{l=1}^{r_2}\textit{dp}_{i-1,l_2,r_2}
\end{aligned}
$$

显然可以维护 $\textit{dp}_{i-1,l,r}$ 的所有状态的和 $\textit{sum}_i$，即：

$$
\textit{sum}_i=\sum_{l=1}^m\sum_{r=l}^m\textit{dp}_{i,l,r}
$$

故有：

$$
\textit{dp}_{i,l,r}=\textit{sum}_{i-1}-\sum_{l_2=r+1}^m\sum_{r_2=l_2}^m\textit{dp}_{i-1,l_2,r_2}-\sum_{r_2=l-1}^m\sum_{l=1}^{r_2}\textit{dp}_{i-1,l_2,r_2}
$$

考虑优化后面的部分。

对于 $\displaystyle\sum_{l=x+1}^m\sum_{r=l}^m\textit{dp}_{i-1,l,r}$，即 $x$ 右边的所有 DP 值之和。显然可以使用后缀和优化。

记：

$$
\begin{aligned}
\displaystyle\textit{suf}_{i,x}&=\textit{suf}_{i+1,x}+\sum_{r=x}^m\textit{dp}_{i,x,r}\\
\displaystyle\textit{pre}_{i,x}&=\textit{pre}_{i-1,x}+\sum_{l=1}^x\textit{dp}_{i,l,x}
\end{aligned}
$$

分别表示 $x$ 及其右边的所有区间的方案数和 $x$ 及其左边的所有区间的方案数。

这显然可以在求解 DP 时求出来。

因此可以有：

$$
\textit{dp}_{i,l,r}=\textit{sum}_{i-1}-\textit{suf}_{i-1,r+1}-\textit{pre}_{i-1,l-1}
$$

发现，此时答案即 $\textit{suf}_{n,1}$。又可以发现，此时状态 $\textit{dp}_{i,l,r}$ 已经**没有意义**。

$\textit{sum}_i$ 可以进一步优化：

$$
\begin{aligned}
\textit{sum}_i&=\sum_{l=1}^m\sum_{r=l}^m\textit{dp}_{i,l,r}\\
&=\sum_{l=1}^m\sum_{r=l}^m\left(\textit{sum}_{i-1}-\textit{suf}_{i-1,r+1}-\textit{pre}_{i-1,l-1}\right)\\
&=\sum_{l=1}^m\left((m-l+1)(\textit{sum}_{i-1}-\textit{pre}_{i-1,l-1})-\sum_{r=l}^{m}\textit{suf}_{i-1,r+1}\right)
\end{aligned}
$$

这启发我们可以维护 $\displaystyle\sum_{r=l}^{m}\textit{suf}_{i-1,r+1}$ 的后缀和来优化。因此记：

$$
\begin{aligned}
\textit{sufSumSuf}_{i,x}&=\sum_{l=x}^m\textit{suf}_{i,x}\\
&=\textit{sufSumSuf}_{i,x+1}+\textit{suf}_{i,x}\\
\textit{preSumPre}_{i,x}&=\sum_{r=x}^m\textit{pre}_{i,x}\\
&=\textit{preSumPre}_{i,x+1}+\textit{pre}_{i,x}\\
\end{aligned}
$$

则可以将 $\textit{sum}_i$ 的递推转化为：

$$
\textit{sum}_i=\sum_{l=1}^m\left((m-l+1)(\textit{sum}_{i-1}-\textit{pre}_{i-1,l-1})-\textit{sufSumSuf}_{l+1}\right)
$$

同样地，代入可以更改 $\textit{pre}_{i,x},\textit{suf}_{i,x}$ 的递推式，最终与 $\textit{dp}_{i,l,r}$ 无关。有：

$$
\begin{aligned}
\textit{pre}_{i,x}&=\textit{pre}_{i,x-1}+x\left(\textit{sum}_{i-1}-\textit{suf}_{i-1,x+1}\right)-\textit{preSumPre}_{i-1,x-1}\\
\textit{suf}_{i,x}&=\textit{suf}_{i,x+1}+(m-x+1)\left(\textit{sum}_{i-1}-\textit{pre}_{i-1,x-1}\right)-\textit{preSumPre}_{i-1,x+1}\\
\end{aligned}
$$

此时状态量为 $\mathcal O(nm)$，转移 $\mathcal O(1)$。

时间复杂度：$\mathcal O(nm)$。由于 $1\leq nm\leq10^7$，可以通过。

***

使用滚动数组，而不要使用 `vector` 套 `vector`。会被卡空间。

# AC 代码

```cpp lines line-numbers
//#include<bits/stdc++.h>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<string>
#include<vector>
#include<cmath>
#include<ctime>
#include<deque>
#include<queue>
#include<stack>
#include<list>
using namespace std;
constexpr const int N=1e7,M=1e7;
int n,m,P,ans;
int sum[2],pre[2][N+1],preSumPre[2][N+1],suf[2][N+1],sufSumSuf[2][N+1];
int main(){
	/*freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);*/
	
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	cin>>n>>m>>P;
	bool op=0;
	for(int l=1;l<=m;l++){
		suf[op][l]=m-l+1;
	}
	for(int r=1;r<=m;r++){
		pre[op][r]=r;
	}
	sum[op]=(m*(m+1ll)>>1)%P;
	for(int r=1;r<=m;r++){
		pre[op][r]=(pre[op][r]+pre[op][r-1])%P;
		preSumPre[op][r]=(pre[op][r]+preSumPre[op][r-1])%P;
	}
	sufSumSuf[op][m]=suf[op][m];
	for(int l=m-1;1<=l;l--){
		suf[op][l]=(suf[op][l+1]+suf[op][l])%P;
		sufSumSuf[op][l]=(suf[op][l]+sufSumSuf[op][l+1])%P;
	}
	for(int i=2;i<=n;i++){
		op=!op;
		sum[op]=0;
		for(int r=1;r<=m;r++){
			pre[op][r]=(1ll*r*(sum[!op]-suf[!op][r+1])-preSumPre[!op][r-1])%P;
		}
		for(int l=1;l<=m;l++){
			suf[op][l]=((m-l+1ll)*(sum[!op]-pre[!op][l-1])-sufSumSuf[!op][l+1])%P;
		}
		for(int l=1;l<=m;l++){
			sum[op]=(sum[op]+(m-l+1ll)*(sum[!op]-pre[!op][l-1])%P-sufSumSuf[!op][l+1])%P;
		}
		for(int r=1;r<=m;r++){
			pre[op][r]=(pre[op][r]+pre[op][r-1])%P;
			preSumPre[op][r]=(pre[op][r]+preSumPre[op][r-1])%P;
		}
		sufSumSuf[op][m]=suf[op][m];
		for(int l=m-1;1<=l;l--){
			suf[op][l]=(suf[op][l+1]+suf[op][l])%P;
			sufSumSuf[op][l]=(suf[op][l]+sufSumSuf[op][l+1])%P;
		}
	}
	int ans=suf[op][1];
	if(ans<0){
		ans+=P;
	}
	cout<<ans<<'\n';
	
	cout.flush();
	
	/*fclose(stdin);
	fclose(stdout);*/
	return 0;
}
```

---

## 作者：xiezheyuan (赞：1)

> 给定 $n,m$，求有多少个二元组 $(l,r)$ 满足：
>
> * $l,r$ 是一个整数序列，长度为 $n$。
> * $1\leq l_i\leq r_i\leq m$。
> * $\forall 1\lt i\leq n,[l_i,r_i]\cap[l_{i-1},r_{i-1}]\neq\varnothing$。
>
> 答案对 $p$ 取模。
>
> $1\leq nm\leq 10^7$。

模拟赛切了开心。

个人感觉本题为少见的前缀和优化 dp 的好题？

首先有一个比较显然的 dp，设 $f(i,l,r)$ 表示考虑到第 $i$ 个区间 $[l_i,r_i]$ 的方案数。优化到极限也是 $O({nm^2})$，难以通过本题（貌似优化到 $O({nm^2})$ 也不容易？）。

正难则反，不妨将有交的限制改为无交。而无交只分成 $l_{i-1}\leq r_{i-1}<l_i\leq r_i$ 和 $l_i\leq r_i\lt l_{i-1}\leq r_{i-1}$ 两种简单的情况，而这两种情况只和上一个区间的某一个端点有关。

设 $f(i,j)$ 表示考虑到第 $i$ 个区间，使得 $l_i=j$ 的方案数，$g(i,j)$ 表示考虑到第 $i$ 个区间，使得 $r_i=j$ 的方案数。

根据上面的讨论，可以得到转移：

$$
\begin{aligned}
&f(i,j)=\left((m-j+1)\sum_{k=1}^{m}f(i-1,k)\right)-\left(\sum_{k=j}^{m}\sum_{t=k+1}^{m}f(i-1,t)\right)-\left((m-j+1)\sum_{k=1}^{j-1}g(i-1,k)\right)\\
&g(i,j)=\left(j\sum_{k=1}^{m}f(i-1,k)\right)-\left(\sum_{k=1}^{j}\sum_{t=1}^{k-1}g(i-1,t)\right)-\left(j\sum_{k=j+1}^{m}f(i-1,k)\right)
\end{aligned}
$$

两个转移方程大致类似。以 $f(i,j)$ 为例，$(m-j+1)\sum_{k=1}^{m}f(i-1,k)$ 是总方案数，$\sum_{k=j}^{m}\sum_{t=k+1}^{m}f(i-1,t)$ 中，$k$ 是我们枚举的右端点 $r_i$，这描述的是无交情况 $l_{i-1}\leq r_{i-1}<l_i\leq r_i$，$(m-j+1)\sum_{k=1}^{j-1}g(i-1,k)$ 中 $k$ 是上一个的右端点，描述的是另一种无交情况 $l_i\leq r_i\lt l_{i-1}\leq r_{i-1}$。

暴力转移，时间复杂度 $O({nm^3})$ 难以承受。考虑优化,$f,g$ 优化类似，这里讨论 $f$ 转移的优化。

先化简双重和式，我们选用交换求和顺序+乘法分配律的方法：

$$
\sum_{k=j}^{m}\sum_{t=k+1}^{m}f(i-1,t)=\sum_{t=j+1}^{m}(t-j)f(i-1,t)=\sum_{t=j+1}^{m}tf(i-1,t)-j\sum_{t=j+1}^{m}f(i-1,t)
$$

令：

$$
\begin{aligned}
&F(i,j)=\sum_{k=1}^{j}f(i,k)\\
&F'(i,j)=\sum_{k=1}^{j}kf(i,k)
\end{aligned}
$$

类似地，也可以求出来 $G,G'$ 两个辅助函数的值。

这两个玩意都是可以在转移的时候处理的

将 $F,F'$ 代入，得到：

$$
\sum_{k=j}^{m}\sum_{t=k+1}^{m}f(i-1,t)=F'(i-1,m)-F'(i-1,j)-j(F(i-1,m)-F(i-1,j))
$$

可以 $O({1})$ 求。现在我们将时间复杂度优化到了 $O({nm^2})$，胜利在望。

然后考虑剩下的两个和式：

$$
\begin{aligned}
&\sum_{k=1}^{m}f(i-1,k)=F(i-1,m)\\
&\sum_{k=1}^{j-1}g(i-1,k)=G(i-1,j-1)
\end{aligned}
$$

至此，我们可以 $O({1})$ 求出每个 $f(i,j)$。

时间复杂度 $O({nm})$ 可以通过本题。

---

## 作者：zifanwang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9108)

简单 dp 题。

直接 dp，记 $f_{i,j}$ 表示前 $i$ 列，第 $i$ 列区间的右端点 $\le j$ 的方案数，$g_{i,j}$ 表示前 $i$ 列，第 $i$ 列区间的左端点 $\ge j$ 的方案数。

如果第 $i$ 列的区间为 $[l,r]$，那么贡献就是 $f_{i-1,m}-f_{i-1,l-1}-g_{i-1,r+1}$，于是维护个前缀和直接转移即可，状态使用滚动数组记录即可通过。

时间复杂度 $O(nm)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 10000003
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
int n,m,md,f1[2][mxn],f2[2][mxn];
bool fl;
signed main(){
	cin>>n>>m>>md;
	rep(i,1,m)f1[0][i]=(f1[0][i-1]+i)%md;
	drep(i,m,1)f2[0][i]=(f2[0][i+1]+m-i+1)%md;
	rep(i,2,n){
		fl^=1;
		rep(j,0,m+1)f1[fl][j]=f2[fl][j]=0; 
		int s=0;
		rep(j,1,m){
			s=(s+f1[fl^1][j-1])%md;
			f1[fl][j]=(f1[fl][j-1]+(ll)f1[fl^1][m]*j-s-(ll)f2[fl^1][j+1]*j)%md;
		}
		s=0;
		drep(j,m,1){
			s=(s+f2[fl^1][j+1])%md;
			f2[fl][j]=(f2[fl][j+1]+f2[fl^1][1]*(m-j+1ll)-s-f1[fl^1][j-1]*(m-j+1ll))%md;
		}
	}
	cout<<(f1[fl][m]+md)%md;
	return 0;
}
```

---

## 作者：HJY2022 (赞：1)

首先你有一个很弱智的 dp。设 $f_{i,l,r}$ 表示你在第 $i$ 次选择 $l,r$ 有多少中方案。

然后你对一层打一个表，容易发现以下性质:

$$f_{i,l,r}=f_{i,l-1,r}+f_{i,l,r-1}+f_{i,l-1,r-1}$$

这个结论是好证明的。考虑中间那个区间被算了两次。

$$f_{i,1,j}=\sum f_{i-1}-\sum_{l>j,r>j}f_{i-1,l,r}$$

这个结论应该也是好证明的。你若选择 $[1,j]$，你前面不能选择的就是后面那部分。

那么考虑用这个性质优化这个dp。容易发现你只需要记录 $dp_{i,1}$ 就可以知道整个矩阵的信息，然后你在记录一个前缀和就可以 $O(m)$ 转移了。

时间复杂度 $O(nm)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define lc x << 1
#define rc x << 1 | 1
#define pii pair<int,int >
#define fir first
#define sec second
#define ll long long
#define i128 __int128

struct FastIO{
	#define IOSIZE 1048576
	char in[IOSIZE],*p,*pp,out[IOSIZE],*q,*qq,ch[20],*t,b,K,prs;
	FastIO():p(in),pp(in),q(out),qq(out+IOSIZE),t(ch),b(1),K(6){}
	~FastIO(){fwrite(out,1,q-out,stdout);}
	inline char gc(){return p==pp&&(pp=(p=in)+fread(in,1,IOSIZE,stdin),p==pp)?b=0,EOF:*p++;}
	inline void pc(char x){q==qq&&(fwrite(out,1,q-out,stdout),q=out),*q++=x;}
}io;

ll read(){
    ll x = 0,f = 1,ch = io.gc();
    while(ch < 48 || ch > 57){
        if(ch == '-')f = -1;
        ch = io.gc();
    }
    while(ch > 47 && ch < 58)x = x * 10 + ch - 48,ch = io.gc();
    return x * f;
}

void write(ll x){
	if(x < 0){io.pc('-');x = -x;}
	if(x > 9)write(x / 10);
	io.pc(x % 10 + 48);
}
const int MX = 1e7 + 7;
int MOD = 998244353;
ll f[2][MX],sum[2][MX];
int main(){
	int n,m;ll las = 0;
	cin >> n >> m >> MOD;
	las = (1ll * m * (m - 1) / 2) % MOD + m;
	las %= MOD;
	for(int i = 1;i <= m;i++)f[1][i] = 1;
	for(int i = 1;i <= m;i++)sum[1][i] = sum[1][i - 1] + f[1][i]; 
	for(int t = 2;t <= n;t++){
		int u = t & 1,v = u ^ 1;
		ll tot = 0;
		for(int i = m,tmp = 1;i >= 1;i--,tmp++){
			f[u][i] = (MOD + las - tot) % MOD + MOD;
			f[u][i] %= MOD;
			tot += (sum[v][m] - sum[v][i - 1] - tmp * f[v][m] + tmp * f[v][tmp]) % MOD + MOD % MOD;
		}
		for(int i = 1;i <= m;i++)sum[u][i] = (sum[u][i - 1] + f[u][i]) % MOD;
		las = 0;
		for(int i = 1,tmp = m;i <= m;i++,tmp--){
			las = las + sum[u][m] - sum[u][i - 1] - tmp * f[u][m] + tmp * f[u][m - i + 1];
			las = (las % MOD + MOD) % MOD;
		}
	}
	cout << las << '\n';
	return 0;
}
```

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：1)

首先有一个 dp：$f_{i,l,r}$ 表示当前第 $i$ 行的木条在第 $l$ 到 $r$ 段涂防水剂的方案数。

于是有 $f_{i,l,r}=\sum\limits_{L\le r,l\le R}f_{i-1,L,R}$。

这个东西复杂度巨大，因此考虑优化。

随便输入一个，观察 $f_1$ 与 $f_2$ 各项，能够发现几个性质（发现它们的难度逐级递增）：

1. $f_{i,l,r}=f_{n-r+1,n-l+1}$
1. $f_{i,l,r}=f_{i,1,r}+f_{i,l,n}-f_{i,1,n}$
1. $f_{i,1,r}=f_{1,r-1}+\sum\limits_{j\ge r}f_{i-1,r,j}$

接下来我们逐个证明。

第一个比较简单，因为它是左右对称的。

第二个就从 dp 的状态来考虑。

如果一个区间能与 $[l,r]$ 相交，那么它一定可以同时与 $[1,r]$ **和** $[l,n]$ 相交。

但是其它所有区间也会与这两个中的 **恰好一个** 相交，而且上面说的这些区间会被算两次，因此我们再容斥去掉一个 $[1,n]$ 即可。

第三个也类似。

对于区间 $[1,r-1]$ 和 $[1,r]$，后者比前者会多出一些方案。这些方案对应的区间与 $[1,r-1]$ 的交为空，但是与 $[1,r]$ 的交非空。

容易想到只有左端点为 $r$ 的区间满足条件，因此它们的差即为对应行的和。

根据上述性质，我们可以将数组缩成两个二维的：

- $a_{i,j}=f_{i,1,j}$；
- $s_{i,j}=\sum\limits_{k\ge j}f_{i,j,k}$。

用它们替换上面的性质得到一些式子就可以直接递推了，答案是 $\sum\limits_{i}s_{n,i}$。

code：

```cpp

void __SOLVE__(int _case){
	cin>>n>>m>>mod;
	vector<vector<int>>s(2,vector<int>(m+1));
	vector<vector<int>>a(2,vector<int>(m+1));
	for(int i=1;i<=m;i++)s[1][i]=m-i+1;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=m;j++)a[i&1][j]=(a[i&1][j-1]+s[!(i&1)][j])%mod;
		int curs=0;
		for(int j=m;j;j--)s[i&1][j]=((((curs+=a[i&1][j])%=mod)+1ll*(m-j+1)*a[i&1][m-j+1]%mod)%mod+mod-1ll*(m-j+1)*a[i&1][m]%mod)%mod;
	}
	int ans=0;
	for(int i=1;i<=m;i++)(ans+=s[n&1][i])%=mod;
	cout<<ans<<endl;
}
```

---

## 作者：PNNNN (赞：1)

介绍一种比较劣的做法。

不妨将 $n$ 根木条上涂防水剂的连续段视作 $n$ 条线段。设 $dp_{i,j}$ 表示考虑前 $i$ 条线段，第 $i$ 条线段的右端点为 $j$ 的方案数。

考虑枚举第 $i$ 条线段的右端点 $j$ 和第 $i-1$ 条线段的右端点 $k$ 进行转移。

若 $k \leq j$，易得，转移式为 $dp_{i,j}=dp_{i,j}+dp_{i-1,k}\times k$，因为只需要当前线段的左端点 $l$ 满足 $1\leq l\leq k$，因此 $l$ 有 $k$ 种选择。可以设前缀和为 $sum1_{i,j}={\sum\limits_{k=1}^{j} dp_{i,k}\times k}$，则 $dp_{i,j}=dp_{i,j}+sum1_{i-1,j}$，即可实现 $O(1)$ 转移。

若 $k>j$，此种情况较为复杂，因为还要考虑第 $i-1$ 条线段的左端点要小于等于 $j$。不妨假设 $dp_{i-1,k}$ 是由 $dp_{i-2,g}$ 转移而来。

若 $g>k$，可知此时 $dp_{i-1,k}$ 的方案数为 $dp_{i-1,k}-sum1_{i-2,k}$ ，第 $i-1$ 条线段的左端点可以任选，有 $k$ 种选择。但是有左端点要小于等于 $j$ 的限制，方案数应该要为 $(dp_{i-1,k}-sum1_{i-2,k})\times inv_k\times j$，这里的 $inv_k$ 表示 $k$ 在模 $p$ 意义下的逆元。因此 $dp_{i,j}=dp_{i,j}+(dp_{i-1,k}-sum1_{i-2,k})\times inv_k\times j ^2$，这里还乘了一个 $j$，是因为当前线段的左端点可以任选。可以设前缀和数组 $sum2_{i,j}=\sum\limits_{k=1}^{j} (dp_{i,k}-sum1_{i-1,k})\times inv_k$，则 $dp_{i,j}=dp_{i,j}+(sum2_{i-1,m}-sum2_{i-1,j})\times j^2$，即可实现 $O(1)$ 转移。

若 $j<g\leq k$，可知此时 $dp_{i-1,k}$ 的方案数为 $\sum\limits_{g=j+1}^{k} dp_{i-2,g}\times g$，也就是 $sum1_{i-2,k}-sum1_{i-2,j}$。但是这样转移只保证了第 $i-1$ 条线段的左端点小于等于 $g$，而没有保证其小于等于 $j$，此时 $dp_{i-1,k}$ 的合法方案数应该是 $\sum\limits_{g=j+1}^{k} dp_{i-2,g}\times j$，所以 $dp_{i,j}=dp_{i,j}+\sum\limits_{g=j+1}^{k} dp_{i-2,g}\times j\times j$。设 $sum4_{i,j}=\sum\limits_{k=1}^{j}dp_{i,k}$，则 $dp_{i,j}=dp_{i,j}+(sum4_{i-2,k}-sum4_{i-2,j})\times j^2$。再设 $sum3_{i,j}=\sum\limits_{k=1}^{j}sum4_{i,k}$，则 $dp_{i,j}=dp_{i,j}+(sum3_{i-2,m}-sum3_{i-2,j}-(m-j)\times sum4_{i-2,j})\times j^2$，即可实现 $O(1)$ 转移。

若 $g\leq j$，可知此时 $dp_{i-1,k}$ 的方案数为 $sum1_{i-2,j}$，并且第 $i-1$ 条线段的左端点一定也小于等于 $j$，所以可以直接转移，$dp_{i,j}=dp_{i,j}+sum1_{i-2,j}\times j$，可以发现与 $k$ 无关。因此 $dp_{i,j}=dp_{i,j}+sum1_{i-2,j}\times j\times (m-j)$，$O(1)$。

到这里这道就做完了。这是我们今天模拟赛的 T1，然后我成功的从 $100$ 分 MLE 到了 $0$ 分。为了减少空间，我将 $sum4$ 去掉，直接在 $dp$ 上做前缀和，并全部使用滚动数组，且此种做法不能开 long long，开了会炸得很厉害，所以此种做法非常劣。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int inf=10000000;

int n,m,mod,ans;

int fac[inf+5],inv[inf+5];

int sum1[3][inf+5],sum2[3][inf+5],sum3[3][inf+5],dp[3][inf+5];

inline int id(int x){return (x%3+3)%3;}

inline int ksm(int base,int Rana){
	int res=1;
	while(Rana>0){
		if(Rana&1)res=res*1ll*base%mod;
		Rana>>=1,base=base*1ll*base%mod;
	}
	return res;
}

inline int read(){
	register int x(0),t(0);
	static char ch=getchar();
	while(!isdigit(ch)){t|=(ch=='-'),ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48),ch=getchar();}
	return t?-x:x;
}

signed main(){
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	
	n=read(),m=read(),mod=read();
	fac[0]=1;
	for(int i=1;i<=m;i++){
		fac[i]=1ll*fac[i-1]*i%mod;
	}
	inv[m]=ksm(fac[m],mod-2);
	for(int i=m-1;i>=0;i--){
		inv[i]=1ll*inv[i+1]*(i+1)%mod;
	}
	for(int i=1;i<=m;i++){
		inv[i]=1ll*inv[i]*fac[i-1]%mod;
	}
	for(int i=1;i<=m;i++){
		dp[id(1)][i]=i;
		sum1[id(1)][i]=(sum1[id(1)][i-1]+1ll*dp[id(1)][i]*i%mod)%mod;
		dp[id(1)][i]=(dp[id(1)][i-1]+dp[id(1)][i])%mod;
		sum3[id(1)][i]=(sum3[id(1)][i-1]+dp[id(1)][i])%mod;
	}
	for(int i=1;i<=m;i++){
		dp[id(2)][i]=(sum1[id(1)][i]+1ll*i*i%mod*(m-i))*1ll%mod;
		sum1[id(2)][i]=(sum1[id(2)][i-1]+1ll*dp[id(2)][i]*i%mod)%mod;
		sum2[id(2)][i]=(1ll*(dp[id(2)][i]+mod-sum1[id(1)][i])%mod*inv[i]%mod+sum2[id(2)][i-1])%mod;	
		dp[id(2)][i]=(dp[id(2)][i-1]+dp[id(2)][i])%mod;
		sum3[id(2)][i]=(sum3[id(2)][i-1]+dp[id(2)][i])%mod;
	}
	for(int i=3;i<=n;i++){
		for(int j=1;j<=m;j++){	
			(dp[id(i)][j]=sum1[id(i-1)][j])%=mod;
			(dp[id(i)][j]+=1ll*(sum2[id(i-1)][m]+mod-sum2[id(i-1)][j])%mod*j%mod*j%mod)%=mod;
			(dp[id(i)][j]+=1ll*sum1[id(i-2)][j]*(m-j)%mod*j%mod)%=mod;
			(dp[id(i)][j]+=1ll*((sum3[id(i-2)][m]+mod-sum3[id(i-2)][j])%mod+mod-1ll*dp[id(i-2)][j]*(m-j)%mod)%mod*j%mod*j%mod)%=mod;
			sum1[id(i)][j]=(1ll*dp[id(i)][j]*j%mod+1ll*sum1[id(i)][j-1])%mod;
			sum2[id(i)][j]=(1ll*(dp[id(i)][j]+mod-sum1[id(i-1)][j])%mod*inv[j]%mod+sum2[id(i)][j-1])%mod;	
			dp[id(i)][j]=(dp[id(i)][j]+dp[id(i)][j-1])%mod;	
			sum3[id(i)][j]=(dp[id(i)][j]+sum3[id(i)][j-1])%mod;
		}
	}
	cout<<dp[id(n)][m];
	
	return 0;
}
```

---

## 作者：TianTian2008 (赞：0)

容易想到 $O(nm^2)$ 的 DP。

设 $f_{i,l,r}$ 为考虑了前 $i$ 列，第 $i$ 列区间为 $[l,r]$ 的方案数，有 $f_{i,l,r}=\sum\limits_{[u,v]\cap[l,r]\neq\empty}f_{i-1,u,v}$。

但两个区间有交其实不太好表示，所以我们用逆命题来表示：$f_{i,l,r}=\sum f_{i-1,u,v}-\sum\limits_{[u,v]\cap[l,r]=\empty}f_{i-1,u,v}=\sum f_{i-1,u,v}-\sum\limits_{v\le l}f_{i-1,u,v}-\sum\limits_{r\le u}f_{i-1,u,v}$。

不妨记 $\text{pre}_v=\sum f_{i-1,u,v},\text{suf}_u=\sum f_{i-1,u,v}$，然后给 $\text{pre}$ 做前缀和得 $\text{pre}'$、给 $\text{suf}$ 做后缀和得 $\text{suf}'$，则有 $f_{i,l,r}=\sum f_{i-1,u,v}-\text{pre}'_{l-1}-\text{suf}'_{r+1}$。

接下来我们发现从 $f_{i-1}\rightarrow f_i$ 的过程只需要 $\sum,\text{pre},\text{suf}$ 就够了，所以我们不维护 $f$ 了，转而维护 $\text{pre},\text{suf}$。

拆一下式子发现再给 $\text{pre}',\text{suf}'$ 做个前/后缀和就随便维护了。

```cpp
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
int n,m,mod,pre[2][10000010],suf[2][10000010],tp[10000010],ts[10000010];
signed main() {
	scanf("%lld%lld%lld",&n,&m,&mod);
	for(int i=1;i<=m;++i) {
		pre[1][i]=i;
		suf[1][i]=m-i+1;
	}
	for(int i=2;i<=n;++i) {
		int x=i&1,y=x^1;
		for(int j=1;j<=m;++j) {
			pre[y][j]=(pre[y][j]+pre[y][j-1])%mod;
			tp[j]=(tp[j-1]+pre[y][j])%mod;
		}
		for(int j=m;j>=1;--j) {
			suf[y][j]=(suf[y][j]+suf[y][j+1])%mod;
			ts[j]=(ts[j+1]+suf[y][j])%mod;
		}
		for(int j=1;j<=m;++j) {
			pre[x][j]=((pre[y][m]-suf[y][j+1])*j-tp[j-1])%mod;
			suf[x][j]=((pre[y][m]-pre[y][j-1])*(m-j+1)-ts[j+1])%mod;
		}
	}
	int ans=0;
	for(int i=1;i<=m;++i) ans=(ans+pre[n&1][i])%mod;
	printf("%lld",(ans+mod)%mod);
	return 0;
}
```

---

## 作者：Claire0918 (赞：0)

注意到题目的数据范围只给出了 $nm$，考虑 $\mathcal{O}(nm)$ 的 dp，设 $f_{i, j}$ 表示前 $i$ 列，第 $i$ 列涂色右端点是 $j$ 的方案数。

考虑转移。我们首先记第 $i - 1$ 行的涂色范围为 $[l, r]$，第 $i$ 行的涂色范围为 $[p, j]$。我们想要 $[l, r] \cap [p, j] \neq \emptyset$。我们发现这要求的充分必要条件是
$$
\begin{cases}
l \leq j\\
r \geq p\\
\end{cases}
$$

首先满足第一条，我们发现要求一个区间的左端点取 $[1, j]$，与要求其右端点取 $[m - j + 1, m]$ 是满足双射的。具体来说，左端点取 $l$ 和右端点取 $m - l + 1$ 是等价的。注意这时 $p$ 不受第 $i - 1$ 列影响，总可以取 $[1, j]$，有 $j$ 种情况，所以首个式子的贡献为 $\displaystyle \sum_{l = m - j + 1}^{m} j \times f_{i - 1, l}$。

再满足第二条，我们直接将一切 $r < p$ 的减去即可。即先选取一个 $r < j$，再选取一个 $p \in (r, j]$。后一步有 $j - r$ 种情况，所以这式子的贡献为 $\displaystyle -\sum_{r = 1}^{j - 1}(j - r) \times f_{i - 1, r}$。

综上，我们得到转移
$$
\begin{aligned}
f_{i, j}
&= \sum_{l = m - j + 1}^{m} j \times f_{i - 1, l} - \sum_{r = 1}^{j - 1} (j - r) \times f_{i - 1, r}\\
&= j\sum_{l = m - j + 1}^{m} f_{i - 1, l} - j\sum_{r = 1}^{j - 1} f_{i - 1, r} + \sum_{r = 1}^{j - 1} r \times f_{i - 1, r}
\end{aligned}
$$

这样单次转移是 $\mathcal{O}(m)$ 的，总时间复杂度达到了 $\mathcal{O}(nm^2)$，不可接受，考虑优化。

对于当前的 $i$，$\mathcal{O}(m)$ 维护 $\{f_i\}$ 的两个前缀和 $s_j = \sum_{k = 1}^{j} f_{i, k}$ 和 $t_j = \sum_{k = 1}^{j} k \times f_{i, k}$。那么式子变为
$$
\begin{aligned}
f_{i, j}
&= j\sum_{l = m - j + 1}^{m} f_{i - 1, l} - j\sum_{r = 1}^{j - 1} f_{i - 1, r} + \sum_{r = 1}^{j - 1} r \times f_{i - 1, r}\\
&= j(\sum_{l = 1}^{m} f_{i - 1, l} - \sum_{l = 1}^{m - j} f_{i - 1, l}) - j\sum_{r = 1}^{j - 1} f_{i - 1, r} + \sum_{r = 1}^{j - 1} r \times f_{i - 1, r}\\
&= j(s_m - s_{m - j}) - j \times s_{j - 1} + t_{j - 1}
\end{aligned}
$$

这时可以对于 $\mathcal{O}(n)$ 个确定的 $i$ 做到 $\mathcal{O}(m)$ 预处理，$\mathcal{O}(1)$ 单次转移，总时间复杂度 $\mathcal{O}(nm)$。

初始化 $f_{1, i} = i$ 即可。

注意使用滚动数组实现。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxm = 1e7 + 10;

int n, m, mod, res = 0;
int f[2][maxm], pre1[maxm], pre2[maxm];

template<typename Tp_x, typename Tp_y>
inline int mod_add(Tp_x x, Tp_y y){
    x += y;
    return x >= mod ? x -= mod : x;
}

int main(){
    scanf("%d %d %d", &n, &m, &mod);
    for (int i = 1; i <= m; i++){
        f[1][i] = i;
    }
    for (int i = 2; i <= n; i++){
        for (int j = 1; j <= m; j++){
            f[i & 1][j] = 0;
        }
        for (int j = 1; j <= m; j++){
            pre1[j] = mod_add(pre1[j - 1], f[i & 1 ^ 1][j]);
            pre2[j] = mod_add(pre2[j - 1], (long long)f[i & 1 ^ 1][j] * j % mod);
        }
        for (int j = 1; j <= m; j++){
            f[i & 1][j] = mod_add((long long)j * mod_add(pre1[m], mod - pre1[m - j]) % mod, mod_add(mod - (long long)j * pre1[j - 1] % mod, pre2[j - 1]));
        }
    }
    for (int i = 1; i <= m; i++){
        res = mod_add(res, f[n & 1][i]);
    }
    printf("%d", res);

return 0;
}
```

---

## 作者：bryce (赞：0)

## [P9108 [PA2020] Malowanie płotu](https://www.luogu.com.cn/problem/P9108)
### 思路
#### 40pts
设 $dp_{i, j, k}$ 表示第 $i$ 个左端点为 $j$，右端点为 $k$ 的方案数，转移很好想，暴力枚举合法的 $l, r$ 转移，由于空间开不下，选择用滚动数组优化一维，时间复杂度 $O(nm^4)$。
#### 70pts
考虑在什么条件下才能够转移，很明显转移的 $l\le k$，$r\ge \max(l, j)$，由于在 $r\lt l$ 时的 $dp$ 为 $0$，所以 $dp_{i, j, k} = \sum\limits_{1\le l\le k, j\le r\le m}dp_{i - 1, l，r}$，这一坨可以用前缀和优化，时间复杂度 $O(nm^2)$。
#### 100pts
发现这样枚举左右端点是无法继续优化下去了，于是考虑将左右端点拆开进行动态规划，设 $f_{i, j}$ 为第 $i$ 个右端点为 $j$ 的方案数，$g_{i, j}$ 为第 $i$ 个左端点为 $j$ 的方案数。

思考转移方程，需要用到容斥，$f_{i, j} = j\times \sum\limits_{k = 1}^{j} g(i - 1, k) - \sum\limits_{r = 1}^{j}\sum\limits_{k = 1}^{r - 1} f(i - 1, k)$，意思为所有左端点在 $j$ 左侧的区间的方案数减去这些满足上一条件的右端点小于当前区间左端点的区间的方案数，$g_{i, j}$ 同理。集中注意力，发现所有的求和都可以用前缀和优化，顺便还可以直接去掉第一维，减少空间，于是时间复杂度为 $O(nm)$。
### 代码
```cpp
#include<iostream>
#define int long long

using namespace std;

inline int read(){
    register int x = 0, f = 1;
    register char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}

const int N = 5e3 + 10, mod = 998244353;
int n, m, ans;
int f[N], g[N], sf[N], sumf[N], sg[N], sumg[N];

signed main(){
    freopen("true.in", "r", stdin);
    freopen("true.out", "w", stdout);
    n = read(), m = read();
    for (int i = 1; i <= m; i++) f[i] = i, g[i] = m - i + 1;
    for (int i = 2; i <= n; i++){
        for (int j = 1; j <= m; j++) sf[j] = (sf[j - 1] + f[j]) % mod, sumf[j] = (sumf[j - 1] + sf[j]) % mod;
        for (int j = 1; j <= m; j++) sg[j] = (sg[j - 1] + g[j]) % mod;
        for (int j = m; j >= 1; j--) sumg[j] = (sumg[j + 1] + (sg[m] - sg[j - 1] + mod) % mod) % mod;
        for (int j = 1; j <= m; j++) f[j] = (j * sg[j] % mod - sumf[j - 1] + mod) % mod;
        for (int j = 1; j <= m; j++) g[j] = ((m - j + 1) * ((sf[m] - sf[j - 1] + mod) % mod) % mod - sumg[j + 1] + mod) % mod;
    }
    for (int i = 1; i <= m; i++) ans = (ans + f[i]) % mod;
    cout << ans;
    return 0;
}
```

---

## 作者：ZhongYuLin (赞：0)

来一点恶心丑陋的做法。

设 $f_{n,l,r}$ 表示考虑前 $n$ 个，第 $n$ 个刷在区间 $\left[l,r\right]$ 上的方案数。考虑容斥。不考虑题目限制，则 $f_{n,l,r}=f_{n-1,1,m}$。减去两侧不交区间的贡献：

$$f_{n,l,r}=f_{n-1,1,m}-\sum_{i=l}^{l-1} \sum_{j=i}^{l-1} f_{n,i,j}+\sum_{i=r+1}^m \sum_{j=i}^m f_{n,i,j}$$

记：$g_{n,l,r}=\sum_{i=l}^r\sum_{j=i}^r f_{n,i,j}$，于是有：

$$f_{n,l,r}=f_{n-1,1,m}-g_{n,1,l-1}-g_{n,r+1,m}$$

$$g_{n,l,r}=\sum_{i=l}^r\sum_{j=i}^r f_{n-1,1,m}-g_{n,1,i-1}-g_{n,j+1,m}$$

$$g_{n,l,r}=\frac{(r-l+1)(r-l+2)}{2}f_{n-1,1,m}-\sum_{i=l}^r g_{n,1,i-1}(r-i+1)-\sum_{i=l}^r g_{n,j+1,m}(i-l+1)$$

第一块式子容易维护，后面两块拆为：

$$(r+1)\sum_{i=l}^r g_{n,1,i-1}+\sum_{i=l}^r g_{n,1,i-1}i+(1-l)\sum_{i=l}^r g_{n,j+1,m}+\sum_{i=l}^r g_{n,j+1,m}i$$

于是只用维护前后缀。转移的时候前缀和优化即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e7+3;
int P;
template<class T1,class T2>void add(T1 &x,T2 y){if((x+=y)>=P)x-=P;}
template<class T1,class T2>void dlt(T1 &x,T2 y){if((x-=y)<0)x+=P;}
int n,m;
int f[N],g[N],s1[N],s2[N],s3[N],s4[N];
static inline void up(int &x){if(x<0)x+=P;}
int main(){
    int u,v,w,x,y,z;
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>P;
    for(int i=1;i<=m;++i){
        f[i]=1ll*i*(i+1)/2%P;
        int k=m-i+1;
        g[i]=1ll*k*(k+1)/2%P;
    }
    for(int k=2;k<=n;++k){
        int sum=f[m];
        for(int i=1;i<=m;++i){
            s1[i]=(s1[i-1]+f[i-1])%P;
            s2[i]=(s2[i-1]+1ll*f[i-1]*i)%P;
            s3[i]=(s3[i-1]+g[i+1])%P;
            s4[i]=(s4[i-1]+1ll*g[i+1]*i)%P;
        }
        for(int i=1;i<=m;++i){
            f[i]=1ll*i*(i+1)/2%P*sum%P;
            f[i]=(f[i]-(i+1ll)*s1[i]+s2[i]-s4[i])%P;
            up(f[i]);
            int k=m-i+1;
            g[i]=1ll*k*(k+1)/2%P*sum%P;
            g[i]=(g[i]-(m+1ll)*(s1[m]-s1[i-1])+s2[m]-s2[i-1]+(i-1ll)*(s3[m]-s3[i-1])-(s4[m]-s4[i-1]))%P;
            up(g[i]);
        }
    }
    printf("%d\n",f[m]);
    return 0;
}
```

---

## 作者：cppcppcpp3 (赞：0)

[Link](https://www.luogu.com.cn/problem/P9108)

 _~~NOIP 模拟赛 T1，场切的第一道紫，纪念一下~~_ 。

（upd on 9.15）感谢@鱼跃于渊的提醒，时间复杂度已修改正确。

简要题意：

> 给出正整数 $N,M$，求出满足条件的长度为 $N$ 的区间序列 $\{[L_1,R_1],[L_2,R_2],\cdots,[L_N,R_N]\}$ 的个数：
> - $L,R$ 的值域为 $[1,M]$ 中的正整数，且 $\forall i \in [1,N],L_i\le R_i$。
> - $\forall i \in [1,N-1]$，$[L_i,R_i]$ 和 $ [L_{i+1},R_{i+1}]$ 有交。

计数题，这里不好直接算答案，考虑 dp。容易想到状态 $f(n,l,r)$ 表示前 $n$ 个区间的答案，且第 $n$ 个区间为 $[l,r]$。从 $i'\le j,j'\ge i$ 的 $f(n-1,i',j')$ 转移到 $f(n,i,j)$，时间复杂度 $O(NM^4)$。

考虑优化这个做法，状态数太多了，我们直接考虑干掉 $i,j$ 中的一维，不妨只保留 $i$。记 $f(n,i)$ 为前 $n$ 个区间的答案，且当前区间的右端点为 $i$。对称的可以设 $g(n,i)$ 为当前区间左端点为 $i$。直接考虑 $f(n,i)$ 从哪里转移来是复杂的，简单容斥一下，用所有 $n-1$ 的方案数之和减去不交区间的方案数：

$$f(n,i)=i\sum_{j=1}^{M}f(n-1,j)-\sum_{r=1}^{i-1}(i-r)f(n-1,r)-i\sum_{l=i+1}^M g(n-1,l)$$

$$g(n,i)=(m-i+1)\sum_{j=1}^{M}f(n-1,j)-\sum_{l=i+1}^{M}(l-i)g(n-1,l)-\sum_{r=1}^{i-1} f(n-1,r)$$

以 $f(n,i)$ 为例具体解释上述转移：右端点为 $i$ 的 $i$ 区间有 $i$ 种。除掉左边区间（右端点为 $r$）与 $i-r$ 个区间不交、右边区间（左端点为 $l$）与 $i$ 个区间不交；$g(n,i)$ 同理，有 $\sum_{i=1}^M f(n,i)=\sum_{i=1}^M g(n,i)$。

初始状态 $f(1,i)=i,g(1,i)=m-i+1$。最终答案为 $\sum_{i=1}^M f(N,i)$。

显然可以对 $f,g$ 分别做前缀和、后缀和来优化，时间复杂度 $O(NM)$。

```cpp
#include<bits/stdc++.h>
#define FIO(file) freopen(file".in","r",stdin),freopen(file".out","w",stdout)
using namespace std;

static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int wrd(){int x=0,f=1;char c=getchar();while(c<'0' || c>'9'){if(c=='-') f=-1;c=getchar();}while(c>='0' && c<='9') {x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}

int n,m,mod,as;
vector<int> f,g,pr[2],sf[2];
void ad(int &a,int b){(a+=b)>=mod&&(a-=mod);}

void init(){
	for(int i=1;i<=m;++i){
		pr[0][i]=(pr[0][i-1]+f[i])%mod;
		pr[1][i]=(pr[1][i-1]+1ll*f[i]*i%mod)%mod;
	}
	for(int i=m;i;--i){
		sf[0][i]=(sf[0][i+1]+g[i])%mod;
		sf[1][i]=(sf[1][i+1]+1ll*g[i]*i%mod)%mod;
	}
}

signed main(){
	n=wrd(),m=wrd(),mod=wrd();
	for(int i=1;i<=n;++i) f.resize(m+2);
	for(int i=1;i<=n;++i) g.resize(m+2);
	for(int o=0;o<2;++o) pr[o].resize(m+2);
	for(int o=0;o<2;++o) sf[o].resize(m+2);

	for(int i=1;i<=m;++i) f[i]=i,g[i]=m-i+1;
	init();
	
	for(int k=2;k<=n;++k){
		int sum=pr[0][m];
		
		for(int i=1;i<=m;++i){
			f[i]=1ll*i*sum%mod;
			ad(f[i],mod-1ll*i*pr[0][i-1]%mod);
			ad(f[i],pr[1][i-1]);
			ad(f[i],mod-1ll*i*sf[0][i+1]%mod);
		}
		for(int i=1;i<=m;++i){
			g[i]=1ll*sum*(m-i+1)%mod;
			ad(g[i],mod-sf[1][i+1]);
			ad(g[i],1ll*i*sf[0][i+1]%mod);
			ad(g[i],mod-1ll*(m-i+1)*pr[0][i-1]%mod);
		}
		init();
	}
	write(pr[0][m]); 
}
```

---

## 作者：songhongyi (赞：0)

怎么随机到了我们足球俱乐部联考题 /yiw。这是联考我唯一会做的计数题 /cf

设 $dp_{i,l,r}$ 表示考虑到第 $i$ 个木条，当前木条涂 $l \dots r$ 的方案数。

那么考虑上一个木条合法的选择 $l' \cdots r'$，需要满足的是 $\left[l',r'\right] \cap \left[l,r\right]$ 非空。正难则反，非法条件是 $r' < l$ 或 $l' > r$。

通过前缀和统计所有满足 $r<i$ 的答案和和 $l>i$ 的答案和，可以做到 $O(m^2)$ 转移，总复杂度 $O(nm^2)$。显然不太行。

具体来说我们设 $f_{i,j}$ 表示第 $i$ 轮满足 $r'\le l$  的 $dp_{i,l',r'}$ 的和，$g$ 定义类似。

我们现在希望直接转移 $f$ 和 $g$。考虑 $f_{i,j}$，所有区间分为三种。全部在 $j$ 左面，全部在 $j$ 右面，跨过 $j$。全部在 $j$ 右面的显然统统不合法，跨 $j$ 的容易处理，全部在 $j$ 左面的可以通过 $f_{i-1}$ 的前缀和处理。这样我们就可以线性的推出 $f_{i}$ 了。$g$ 转移类似。

复杂度 $O(nm)$。

---

## 作者：Genius_Star (赞：0)

[**或许更好的阅读体验。**](https://www.cnblogs.com/rgw2010/p/18394036)

### 题意：

给定 $n,m$，一个区间序列 $\{[L_1,R_1],[L_2,R_2],\cdots,[L_n,R_n]\}$ 被称为好的当且仅当：

- $\forall i \in [1,n],1 \le L_i \le R_i \le m$。

- $\forall i \in [1,n-1],[L_i,R_i] \cup [L_{i+1},R_{i+1}] \ne \emptyset$。

输出好的序列个数对给定质数 $p$ 取模的结果

$nm \le 10^7$。

### 思路：

考虑动态规划算法，定义 $dp_{i,l,r}$ 表示第 $i$ 次为 $[l,r]$，则状态转移方程为：

$$dp_{i,l,r} = \sum_{L=1}^r \sum_{R=\max(L,l)}^m dp_{L,R}$$

这种是不好转移的，考虑做一个容斥，用总的减去与 $L \le R < l$ 或 $r< L \le R$ 的贡献，记 $s_i$ 表示所有 $dp_{i,l,r}$ 的和：

$$dp_{i,l,r} = s_{i-1} - \sum_{L=1}^{l-1} \sum_{R=L}^{l-1} dp_{L,R} - \sum_{L=r+1}^m \sum_{R=L}^m dp_{L,R}$$

我们可以记 $f_{i,j}$ 表示所有满足 $r \le j$ 的 $dp_{i,l,r}$ 的和，记 $g_{i,j}$ 满足所有 $j \le l$ 的 $dp_{i,l,r}$ 的和，则状态转移方程更新为：

$$dp_{i,l,r} = f_{i-1,m} - f_{i-1,l-1} - g_{i-1,r+1}$$

时间复杂度通过前缀和优化至 $O(nm^2)$，考虑继续优化。

考虑如何快速求 $f_{i,j}$ 和 $g_{i,j}$，可以直接爆推：

$$\begin{aligned} f_{i,j} &= \sum_{l=1}^j \sum_{r=l}^j dp_{i,l,r} \\ &= \sum_{l=1}^j \sum_{r=l}^j f_{i-1,m} - f_{i-1,l-1} - g_{i-1,r+1} \\ & = \frac{j(j+1)}{2} f_{i-1,m} - \Big( \sum_{l=1}^j \sum_{r=l}^j f_{i-1,l-1} + g_{i-1,r+1} \Big) \\ &= \frac{j(j+1)}{2} f_{i-1,m} - \sum_{l=1}^j (j-l+1) \times f_{i-1,l-1} - \sum_{r=1}^j r \times g_{i-1,r+1} \\ &= \frac{j(j+1)}{2} f_{i-1,m} - \sum_{r=1}^j r \times g_{i-1,r+1} - \Big( \sum_{l=1}^j  j \times f_{i-1,l-1}  - \sum_{l=1}^j  (l-1) \times f_{i-1,l-1} \Big) \\ &= \frac{j(j+1)}{2} f_{i-1,m} - \sum_{r=1}^j r \times g_{i-1,r+1} -  j\sum_{l=1}^j f_{i-1,l-1}  + \sum_{l=1}^j  (l-1) \times f_{i-1,l-1} \end{aligned}$$

$$\begin{aligned} g_{i,j} &= \sum_{l=j}^m \sum_{r=l}^m dp_{i,l,r} \\ &= \sum_{l=j}^m \sum_{r=l}^m f_{i-1,m} - f_{i-1,l-1} - g_{i-1,r+1} \\ &= \frac{(m+j)(m-j+1)}{2} f_{i-1,m}  - \Big(\sum_{l=j}^m \sum_{r=l}^m f_{i-1,l-1}  + g_{i-1,r+1} \Big) \\ &= \frac{(m+j)(m-j+1)}{2} f_{i-1,m} - \sum_{l=j}^m (m-l+1) f_{i-1,l-1}-\sum_{r=j}^m (r-j + 1) g_{i-1,r+1} \\ & = \frac{(m+j)(m-j+1)}{2} f_{i-1,m} - \sum_{l=j}^m (m-l+1) f_{i-1,l-1} - \sum_{r=j}^m r \times g_{i-1,r+1} + (j-1) \sum_{r=j}^m g_{i-1,r+1} \end{aligned}$$

这样时间复杂度优化为 $O(nm)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
#define For(i,l,r) for(register int i=l;i<=r;i++)
#define _For(i,l,r) for(register int i=r;i>=l;i--)
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N=1e7+10; 
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
int n,m,st,s1,s2,s3,s4,mod;
int f[2][N],g[2][N];
bool End;
int main(){
	n=read(),m=read(),mod=read();
	For(i,1,m)
	  f[0][i]=(f[0][i-1]+i)%mod;
	_For(i,1,m)
	  g[0][i]=(g[0][i+1]+m-i+1)%mod;
	For(i,2,n){
		st^=1;
		For(j,0,m+1)
		  f[st][j]=g[st][j]=0; 
		s1=s2=s3=s4=0;
		For(j,1,m){
			s1=(s1+j)%mod;
			s2=(s2+1ll*g[st^1][j+1]*j%mod)%mod;
			s3=(s3+f[st^1][j-1])%mod;
			s4=(s4+1ll*f[st^1][j-1]*(j-1)%mod)%mod;
			f[st][j]=(1ll*s1*f[st^1][m]%mod-s2-1ll*s3*j%mod+s4+mod*2ll)%mod;
		}
		s1=s2=s3=s4=0;
		_For(j,1,m){
			s1=(s1+m-j+1)%mod;
			s2=(s2+1ll*f[st^1][j-1]*(m-j+1)%mod)%mod;
			s3=(s3+1ll*g[st^1][j+1]*j%mod)%mod;
			s4=(s4+g[st^1][j+1])%mod;
			g[st][j]=(1ll*s1*f[st^1][m]%mod-s2-s3+1ll*s4*(j-1)%mod+mod*2)%mod;
		}
	}
	write(f[st][m]);
	cerr<<'\n'<<abs(&Begin-&End)/1048576<<"MB";
	return 0;
}
```

---

