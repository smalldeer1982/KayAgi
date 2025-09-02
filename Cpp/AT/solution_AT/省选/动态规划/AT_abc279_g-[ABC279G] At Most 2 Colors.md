# [ABC279G] At Most 2 Colors

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc279/tasks/abc279_g

$ 1\ \times\ N $ のマス目があり、マスには左から $ 1,2,\dots,N $ の番号が付いています。

高橋君は $ C $ 色の絵の具を用意し、各マスを $ C $ 色のいずれかで塗りました。  
 すると、どの連続する $ K $ マスを見ても高々 $ 2 $ 色しか現れませんでした。  
 厳密には、 $ 1\ \le\ i\ \le\ N-K+1 $ を満たす全ての整数 $ i $ について、マス $ i,i+1,\dots,i+K-1 $ には高々 $ 2 $ 色しか現れませんでした。

高橋君の色の塗り方として考えられるものは何通りですか？  
 この数は非常に大きくなる場合があるので、 $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 2\ \le\ K\ \le\ N\ \le\ 10^6 $
- $ 1\ \le\ C\ \le\ 10^9 $
 
### Sample Explanation 1

この入力では、マス目は $ 1\ \times\ 3 $ です。 連続する $ 3 $ マスの中で高々 $ 2 $ 色しか現れないように塗る方法は、考えうる全ての塗り方 $ 27 $ 通りから全てのマスを異なる色で塗る $ 6 $ 通りを引いた $ 21 $ 通りです。

### Sample Explanation 2

$ C=2 $ なので、どのように塗っても連続する $ K $ マスには高々 $ 2 $ 色しか含まれません。

### Sample Explanation 3

$ 998244353 $ で割った余りを出力してください。

## 样例 #1

### 输入

```
3 3 3```

### 输出

```
21```

## 样例 #2

### 输入

```
10 5 2```

### 输出

```
1024```

## 样例 #3

### 输入

```
998 244 353```

### 输出

```
952364159```

# 题解

## 作者：small_cyt (赞：15)

有点妙的 dp，感觉和大家的有点不同。



首先我们有个朴素的 dp，设 $f_{i,j}$ 表示前 $i$ 个格子中，从第 $j$ 个格子到第 $i$ 个格子都是同样颜色，且第 $j-1$ 个格子和第 $j$ 个格子颜色不同，满足 $1$ 到 $i$ 都合法的方案数，则



$$f_{i,j}=f_{i-1,j} \left[j<i\right]$$	

（第 $i$ 个格子要和第 $i-1$ 个格子颜色相等）



$$f_{i,i}=\left( \sum_{j=i-k+2}^{i-1} f_{i-1,j} \right) + \left( \sum_{j=1}^{i-k+1}f_{i-1,j} \times\left(c-1\right) \right)$$	

（如果第 $j-1$ 个格子到第 $i$ 个格子的格子数小于等于 $k$，则强制第 $i$ 个格子与第 $j-1$ 个格子同色，否则只需强制第 $i$ 个格子与第 $i-1$ 个格子不同色即可）



直接做是 $O(n^2)$ 的。



发现第一部分可以**直接继承**，于是可以把第一维省掉。



直接用前缀和算第二部分，代码中的 $g_i$ 为前缀和数组。



注意 $f_1$ 转移到 $f_i$ 时可能要特判，因为此时只出现过一种颜色。



这题就做完了。



代码真的很短。

```c++
int main(){
	scanf("%lld %lld %lld",&n,&K,&c);
	f[1]=g[1]=c;
	for(R i=2; i<=n; ++i){
		LL x=max(i-K+1,(LL)1);
		f[i]=g[i-1]-g[x]+g[x]*(c-1)%mo;//唯一的转移
		f[i]=(f[i]+mo)%mo;
		g[i]=(g[i-1]+f[i])%mo;
	}
	printf("%lld\n",g[n]);
}
```

如有错请指出，谢谢。



---

## 作者：JSQ_ (赞：6)

## 思路

很明显，这是一个计数 DP 的题

设 $f_i$ 表示前 $i$ 个格子染色的方案数，考虑第 $i$ 个格子的染色情况：

* 如果 $i$ 前面 $k-1$ 个格子一共染了 $2%$ 种颜色，那么第 $i$ 个格子只能冉这 $2$ 种颜色之一。用 $i$ 前面 $k - 1$ 个格子的染色方案总数减去 $i$ 前面只有 $1$ 种颜色的方案数就是第 $i$ 个格子染两种颜色的方案数，让 $i$ 前面 $k - 2$ 个格子和 $i - k + 1$ 染成一样，就是染 $1$ 种颜色的方案数，即：
$$f_i=(f_i-f_{\max(1,i-k+1)}) \times 2$$
* 如果 $i$ 前面 $k - 1$ 个格子有 $1$ 种颜色，那么第 $i$ 个格子可以染成任意颜色，即：
$$f_i=f_{\max(1,i-k+1)} \times c$$

所以 
$$f_i=2 \times f_{i-1}+(c-2) \times f_{\max(1,i-k+1)}$$ 
因为第一个格子可以自由选择，所以 DP 的初始状态 $f_1=c$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using cint = const int;

cint mod = 998244353, N = 1e6 + 5;

int main() {
	ll n, c, k, f[N];//不开 long long 见祖宗
	cin >> n >> k >> c;
	f[1] = c;
	for (int i = 2; i <= n; i++) 
		f[i] = ((2 * f[i - 1]) % mod + ((c - 2) * f[max(1ll, i - k + 1)]) % mod) % mod; //记得取模
	cout << f[n] % mod;

	return 0;
}
```

---

## 作者：王熙文 (赞：4)

没有场切，wtcl。赛后看到了一个很妙的题解，于是来记录一下。

## 思路

设 $dp_{i,1/2}$ 表示到第 $i$ 个位置，**最后 $k-1$ 个**（如果不够就算全部）中有 $1/2$ 种颜色的方案数。

首先思考一下，为什么要用 $k-1$ 个而不是 $k$ 个作为状态？这样其实是为了更好地转移。对于一个位置 $i$，如果我们知道了 $i$ 的选择和 $i-1$ 的最后 $k-1$ 个的颜色个数，就能知道 $i$ 的最后 $k$ 个的颜色个数。但是如果只知道 $i-1$ 的最后 $k$ 个的颜色个数，放到 $i$ 这里来，$i-k$ 的颜色已经不算做 $i$ 的颜色个数里了，就会出现问题（比如 $i-k$ 是 $i-1$ 的最后 $k$ 个唯一的颜色）。

对于 $dp_{i,1}$，有如下的转移：

$$dp_{i,1}=C+\sum\limits_{j=1}^{i-k+1} \left( dp_{j,1} \times (C-1) + dp_{j,2}\right)$$

解释一下。首先一种方案是最后 $i$ 个都为一种颜色，方案数为 $C$。否则**枚举最后一个不相同的位置 $j$**。如果 $j$ 的最后 $k-1$ 个为一种颜色，则 $j+1$ 的颜色（它的颜色即为后面到 $i$ 所有的颜色）可以是剩下的 $C-1$ 种（颜色不能相同，因为枚举限制了不相同）。如果 $j$ 的最后 $k-1$ 个有两种颜色，则 $j+1$ 只能选择这两种颜色了。而 $j$ 一定是这两种的一种，所以 $j+1$ 只能是另一种。

对于 $dp_{i,2}$，有如下的转移：

$$dp_{i,2}=\sum\limits_{j=i-k+2}^{i-1} \left( dp_{j,1} \times (C-1) + dp_{j,2}\right)$$

可以发现它的转移和上面的转移类似。思路仍然是枚举最后一个不相同的位置 $j$。因为这一段要有两种颜色，所以枚举的范围变成了 $i$ 前面的 $k-1$ 个位置。转移的意义等与上面相同。

转移时需要使用前缀和优化，复杂度为 $\mathcal O(n)$。

最后的答案即为两种情况之和，$dp_{n,1}+dp_{n,2}$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int n,k,c;
int dp[1000010][3],sum[1000010][3]; // 到 i 最后 k-1 个颜色个数为 1/2 的方案
signed main()
{
	cin>>n>>k>>c;
	dp[1][1]=c%mod,dp[1][2]=0;
	sum[1][1]=c%mod,sum[1][2]=0;
	for(int i=2; i<=n; ++i)
	{
		dp[i][1]=(c+(i-k+1<=0?0:sum[i-k+1][1]*(c-1)+sum[i-k+1][2]))%mod;
		// c 为全都为一个颜色，否则枚举最后一个不同的位置
		// 如果这个位置前面只有一种颜色，那么这个位置加一的颜色（即为后面所有颜色）有 c-1 种
		// 如果这个位置前面有两种颜色，那么这个位置加一的颜色只有两种选择，而它不能和前面的相同，所以只有一种
		dp[i][2]=((sum[i-1][1]-sum[max(i-k+1,0ll)][1]+mod)*(c-1)+(sum[i-1][2]-sum[max(i-k+1,0ll)][2]+mod))%mod;
		// 这里同理，枚举最后一个不同的位置，区别是枚举的范围
		sum[i][1]=(sum[i-1][1]+dp[i][1])%mod;
		sum[i][2]=(sum[i-1][2]+dp[i][2])%mod;
	}
	cout<<(dp[n][1]+dp[n][2])%mod;
	return 0;
}
```

---

## 作者：vegetable_king (赞：3)

在[博客](https://yjh965.github.io/post/abc279g-at-most-2-colors-ti-jie/)食用更佳。

首先可以想到设 $f_i$ 为长度为 $i$ 的网格的个数。

然后考虑转移，具体考虑第 $i$ 个格子染成什么颜色。可以分成两种情况：

- 第 $i$ 个格子前 $k - 1$ 个格子颜色相同。这样当前格可以染成任意颜色。

- 否则，前 $k - 1$ 个格子里共出现过两种颜色。这样当前格只能在这两种颜色之中选择。

显然，每一个长度为 $i - k + 1$ 的网格都与一个长度为 $i - 1$ 且后 $k - 1$ 个格子颜色相同的网格形成**双射**，因为我们可以把前者的最后一个格子再复制 $k - 2$ 次接在后面形成后者，且满足要求。所以后者的方案数即为 $f_{i - k + 1}$。

而容斥可得长度为 $i - 1$ 且后 $k - 1$ 个格子里共出现过两种颜色的网格个数即为 $f_{i - 1} - f_{i - k + 1}$。

可得转移方程：

$$f_{i} = 2(f_{i - 1} - f_{i - k + 1}) + c \times f_{i - k + 1}$$

整理后可得

$$f_{i} = 2f_{i - 1} + (c - 2)f_{i - k + 1}$$

然后考虑 $f_{1 \sim k}$ 的初始化。

$f_i$ 其实就是在 $c$ 种颜色中选择两种颜色，然后用这两种颜色染 $i$ 个格子的方案数，$\binom c2 2^i$。但是这样会计重，只使用一种颜色的方案会算 $c - 1$ 次，所以得

$$f_{i} = \binom c2 2^i - c(c - 2) \ (i \le k)$$

答案为 $f_{n}$。时间复杂度为 $O(n)$。

可以发现，虽然方程中出现了 $\binom c2, c - 2$ 这样的东西，但是把 $c = 1$ 的情况代入进去是完全没有问题的。

---

## 作者：OrinLoong (赞：0)

## ATB279G At Most 2 Colors 学习笔记
[Luogu Link](https://www.luogu.com.cn/problem/AT_abc279_g)

### 前言
参考文献：[这位巨佬的题解](https://www.luogu.com.cn/article/mxgp9phe)

### 题意简述
现在有一行 $N$ 个格子和 $C$ 种颜色。每一个格子都需涂 $C$ 种颜色中的一种，并且任意相邻的 $K$ 个格子最多有两种不同的颜色。

问有多少种染色方案。答案对 $998244353$ 取模。

$2\le K\le N\le 10^6,1\le C\le 10^9$。

### 做法解析
看到一行上相邻格子这种玩意不难往连续段DP方向想。设 $f_{i,j}$ 表示前 $i$ 个格子中，$[j,i]$ 颜色相同，$A_{j-1},A_j$ 相异的合法方案数。

那么转移方程呢？有：
$$f_{i,j}=f_{i-1,j}[j<i]$$
$$f_{i,i}=\big(\sum_{j=i-k+2}^{i-1} f_{i-1,j}\big)+\big(\sum_{j=1}^{i-k+1}f_{i-1,j}\times (c-1)\big)$$

怎么理解这两个式子呢？作为连续段 dp，我们肯定要按照新开一段与否讨论。

如果不新开一个颜色段，也就是 $A_i=A_{i-1}$ 时，$f_{i,j}$ 就直接继承了 $f_{i,j-1}$——我往这长为 $K$ 的窗口里多塞一个和原来段尾相同的颜色，合法性一定有保证。

如果新开一个颜色段，我们又要分两种情况讨论：
+ 如果之前的那个颜色段足够长，也就是有 $i-j'+1\ge K$，即 $j'\le i-K+1$ 时，新的窗口中只会有那一大段 $A_{i-1}$ 色和一个 $A_i$ 色。那么 $A_i$ 的颜色就有 $c-1$ 种选择。对应的就是上文 $\sum_{j=1}^{i-k+1}f_{i-1,j}\times (c-1)$。
+ 如果之前的那个颜色段不够长，也就是说 $j'>i-K+1$，那么当前的窗口最左端就还有异于 $A_{i-1}$ 的一种颜色，$A_i$ 只能涂上这种颜色。对应的就是上文 $\sum_{j=i-k+2}^{i-1} f_{i-1,j}$。

好了我们已经会 $N^2$ 做法了。我们又发现 $f$ 的第一维**完全**可以通过前缀和去掉。然后就 $O(N)$ 了！

### 代码实现
这个前缀和似乎和平时见到的不太一样……？

这里的下标到底是原来的 $i$ 还是 $j$？

实际上，你再仔细看看上面那个式子，你就会发现所有 $j\neq i$ 的状态都可以等于那个 $j=i$ 的状态，所以我们只用记录所有 $f_{i,i}$ 就够了，也就是说只有一维下标是有用的，所以这里只记录一维。

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace obasic{
    typedef long long lolo;
    template <typename _T>
    void readi(_T &x){
        _T k=1;x=0;char ch=getchar();
        for(;!isdigit(ch);ch=getchar())if(ch=='-')k=-1;
        for(;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+ch-'0';
        x*=k;return;
    }
    template <typename _T>
    void writi(_T x){
        if(x<0)putchar('-'),x=-x;
        if(x>9)writi(x/10);
        putchar(x%10+'0');
    }
};
using namespace obasic;
const int MaxN=1e6+5,Mod=998244353;
lolo N,K,C,f[MaxN],g[MaxN];
int main(){
    readi(N),readi(K),readi(C);
    f[1]=g[1]=C;
    for(int i=2;i<=N;i++){
        lolo x=max(i-K+1,1ll);
        f[i]=(g[i-1]-g[x]+g[x]*(C-1)%Mod+Mod)%Mod;
        g[i]=(g[i-1]+f[i])%Mod;
    }
    writi(g[N]);
    return 0;
}
```

### 反思总结
善于观察式子，可能只有一维下标有用。
见到一个序列填东西，连续多少有限制，考虑连续段 dp。

---

## 作者：Hoks (赞：0)

## 前言
很巧妙的题，有意思。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
$n\le10^6$ 的计数题，主观感觉就是 $O(n)$ 的 dp。

考虑设计 $f_i$ 表示填到方格 $i$ 的方案数。

那么可以对 $i$ 这个格子进行分类讨论：
1. 前 $k-1$ 个格子已经填了两种不同的颜色。

   此时 $i$ 这个格子只能填这两种颜色之一，所以答案先加上 $f_{i-1}\times2$。
   
  	但是这样显然会计算重复，因为 $f_{i-1}$ 中还包括只染一种颜色的方案。
    
   不难发现只染一种颜色的方案数为 $f_{i-k+1}$，因为我们可以把他的最后一个格子颜色复制 $k-2$ 次拼接得到长度为 $k-1$ 的同色后缀。
   
  	那么这种方式的转移即为 $f_i\leftarrow 2\times(f_{i-1}-f_{i-k+1})$。
2. 前 $k-1$ 个格子只填了一种颜色。

   此时的方案数即为 $f_{i-k+1}$，而 $i$ 这个格子填什么都行，所以有 $c$ 种方案。
   
   简单得到方程式为 $f_i\leftarrow c\times f_{i-k+1}$。

接着来考虑预处理，因为上述两个方程式都是建立在 $i-k+1\ge1$ 的前提下的，所以要预处理出 $i\le k$ 的情况。

因为 $k$ 个方格中最多只能选两种颜色，所以其实就是一个组合问题，总方案数即为 $\binom{c}{2}2^i$。

但是这样会重复计算只选取一种颜色的情况，所以要减去 $c\times(c-2)$。

那就得到了 $f_i=\binom{c}{2}2^i-c\times(c-2),(i\le k)$。

实现时考虑偷懒，直接从 $f_{n+2}$ 开写来避免 $i-k+1<0$。

接着来合并方程式，首先我们有的方程式是：
$$ f_i=\left\{
\begin{matrix}
 f_i=2\times f_{i-1}+(c-2)\times f_{i-k+1},i>k \\
 f_i=\binom{c}{2}2^i-c\times(c-2),(i\le k)
\end{matrix}
\right.
$$

简单合并一下就可以得到：
$$f_i=2\times f_{i-1}+(c-2)\times f_{i-k+1}+c\times(c-1),i\ge2$$

其中当 $i<k$ 时，$f_{i-k+1}=0$，刚好都符合条件。

仔细观察下就会发现这个方程式还有漏洞，随便代入一个 $i=2$ 的时候，算出来的值即为 $c\times(c-1)$，正确答案应为 $c^2$。

刚好相差了一个 $c$。

不难发现这样合并之后每一项都会刚好差一个 $c$。

因为虽然每次 $f_i\times2$ 导致答案相差 $2\times c$，但比起原方程式加上的 $c\times(c-2)$，又加上了 $c\times(c-1)$，补回了差距。

所以这个式子求出来的答案刚好每项相差 $c$，直接给最后答案额外加 $c$ 即可。

记得取模。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,k,c,f[N<<1];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
signed main()
{
    n=read(),k=read(),c=read();
    for(int i=n+2;i<=(n<<1);i++) f[i]=((f[i-1]<<1)+(c-2)*f[i+1-k]+c*(c-1))%mod;
    print((f[n<<1]+c)%mod);
    genshin:;flush();return 0;
}
```

---

