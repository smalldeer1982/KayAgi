# [ARC166C] LU / RD Marking

## 题目描述

有一个纵向 $H$ 行、横向 $W$ 列的网格。

在这个网格中，有 $H(W+1)$ 条纵向边和 $W(H+1)$ 条横向边，总共有 $H(W+1) + W(H+1)$ 条边（请参考输入输出示例中的图）。

对于这些边，可以通过以下两种操作给边做标记：

- **操作 (1)**：选择一个当前其左侧边和上侧边都没有被标记的格子。将该格子的左侧边和上侧边标记。
- **操作 (2)**：选择一个当前其右侧边和下侧边都没有被标记的格子。将该格子的右侧边和下侧边标记。

操作 (1) 和操作 (2) 可以任意次（包括 $0$ 次）进行。请你求出，最终可能出现的被标记的边的集合的种类数，结果对 $998244353$ 取模。

给定 $T$ 组测试数据，请分别输出每组的答案。

## 说明/提示

### 约束条件

- $1 \leq T \leq 2 \times 10^5$
- $1 \leq H, W \leq 10^6$

### 样例解释 1

当 $(H, W) = (1, 1)$ 时，最终可能出现的被标记的边的集合有如下 $4$ 种。被标记的边用粗线表示。  
![](https://img.atcoder.jp/arc166/bd84a15ada55c0df6d4e66863053bd59.png)  
当 $(H, W) = (2, 3)$ 时，例如如下的边的集合是**可能的**。  
![](https://img.atcoder.jp/arc166/66c77b9132c38d82c36732966ff3ae4f.png)  
另一方面，下面这样的边的集合是**不可能的**。  
![](https://img.atcoder.jp/arc166/0029e3cc83a0232231ddf6e280c7f9a8.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
1 1
2 3```

### 输出

```
4
800```

## 样例 #2

### 输入

```
3
123 456
654 321
1000000 1000000```

### 输出

```
60549740
298307903
656009181```

# 题解

## 作者：Halberd_Cease (赞：16)

挺有意思题，爱来自瓷器。

把一个正方形按题目要求的对角线分成两个三角形，发现两个三角形互不干扰：

![](https://cdn.luogu.com.cn/upload/image_hosting/34zlagxx.png)

意思是把选择边转换成选择三角形，两个三角形取与不取不互相影响。

把 6 个正方形组成的矩形按同样方法分成 12 个三角形：

![](https://cdn.luogu.com.cn/upload/image_hosting/q3peiiis.png)

发现，直角边相邻的三角形互相影响。

将互相影响的三角形染成同一个颜色：

![](https://cdn.luogu.com.cn/upload/image_hosting/xd2xmp0p.png)

发现，对角线分隔开的三角形组互不影响，于是讨论三角形组（我们称染成一个颜色的三角形组成的集合为三角形组）。

将斜着的三角形组进行 dp：

一个三角形如果要选，那么上一个三角形必须不选，一个三角形如果不选，那么上一个选不选都可以。

用方程表示，令 $dp_i$ 表示有 $i$ 个三角形的方案数，如果不选，就有 $dp_{i-1}$ 种，如果选，那么 $i-1$ 不能选，就有 $dp_{i-2}$ 种。

于是得到递推式：$dp_i=dp_{i-1}+dp_{i-2}$。

发现是斐波那契数列，直接预处理即可。

继续考虑上面的矩阵，朴素可以 $O(N+M)$ 进行单次求解，将每一个三角形组的答案累乘即可，但是有 $T \le 2\times 10^5$ 组数据，所以只能单次 $O(1)$ 或者 $O(\log n)$ 求解。

考虑矩阵的答案构成，即每个三角形组的数量，是 $1,3,\dots,2\times i-1,2\times i,\dots,2\times i,2\times i-1,\dots,3,1$。

于是可以快速幂加上预处理 $dp_1\times dp_3\times \dots \times dp_{2\times i-1}$ 的值，单次 $O(\log n)$ 求出。

总复杂度 $O(n+T\log n)$。

[code](https://atcoder.jp/contests/arc166/submissions/46410830)

---

## 作者：樱雪喵 (赞：5)

把少打的半场时间补上大概能过。

## Description

给一个 $n$ 行 $m$ 列的网格，那么它的所有**网格线**上共有 $n(m+1)$ 条竖边，$(n+1)m$ 条横边。

有如下两种操作：

- 选一个上面和左面的网格线都没被涂黑的格子，并涂黑这两条线；
- 选一个下面和右面的网格线都没被涂黑的格子，并涂黑这两条线。

求执行两种操作若干次（可以为 $0$），可能得到不同的涂黑边集数量。

$T\le 2\times 10^5,\ n,m\le 10^6$。

## Solution

在网格线上考虑问题，发现操作一次只会对该折线左下 / 右上相邻的折线产生影响。也就是说，我们把网格线斜向拆成若干条连续的折线，它们之间贡献独立。借用一下官方题解的图：

![](https://img.atcoder.jp/arc166/25192085101f6f5c7b5bd1b5d9ae1849.png)

想到这一步就很好做了，但是想好久才想到这个 /dk

现在我们要求的就是对于每一条折线，在上面选若干长度为 $2$ 的区间，且两两之间不能有交的方案数。

考虑 dp，设 $f_n$ 表示长度为 $n$ 的折线的答案。那么如果不选 $[n-1,n]$ 这条折线，$[n-2,n-1]$ 及以前的都可以选，方案数为 $f_{n-1}$；否则只能选 $[n-3,n-2]$ 及以前的，方案数为 $f_{n-2}$。发现是斐波那契，预处理一下就好了。

统计一对 $(n,m)$ 的答案，这里设 $n<m$，不满足就 $\text{swap}$ 一下。  
那么分成从横/竖边出发，把每条折线的贡献乘起来，则答案为 

$$ans=(f_{2n})^{m-n}\times \prod_{i=1}^n (f_{2i-1})^2$$

前面一半快速幂，后面一半预处理。

```cpp
#define int long long
const int N=2e6+5,mod=998244353;
int T,n,m;
int f[N],sum[N];
void init(int mx)
{
    f[0]=1,f[1]=2;
    for(int i=2;i<=mx;i++) f[i]=(f[i-1]+f[i-2])%mod;
    sum[0]=1;
    for(int i=1;i<=(mx>>1);i++) sum[i]=sum[i-1]*f[2*i-1]%mod*f[2*i-1]%mod;
}
il int qpow(int n,int k)
{
    int res=1;
    for(;k;n=n*n%mod,k>>=1) if(k&1) res=res*n%mod;
    return res;
}
signed main()
{
    init(2e6);  
    T=read();
    while(T--)
    {
        n=read(),m=read();
        if(n>m) swap(n,m);
        int res=sum[n];
        res=res*qpow(f[2*n],m-n)%mod;
        printf("%lld\n",res);
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：3)

## Solution

思路：一个很神奇的转化，注意到实际上有一些操作是完全不相关的，两个操作相关当且仅当这两个操作有共同边，于是如果把所有有共同边的操作放在一起，会发现所有相关操作构成了一堆折线，而且这些折线的长度排列是有规律的，那么就可以先预处理出每个长度的折线对应的方案数，然后乘起来即可。

具体地，预处理部分可以直接 dp（其实做多了会一眼看出就是斐波那契数列）。设 $f_i$ 为长度为 $i$ 的折线的方案数，则考虑最后一个操作是否进行，相当于最后一条边是否染色，有：

$$
f_i = f_{i-1} + f_{i-2}
$$

正确性显然。

计算答案部分，令 $n \le m$，那么手推一下会发现开头结尾的折线长度为 $2,4,6,\dots,2n$ 和 $2n,2n-2,2n-4,\dots,2$，中间有 $m-n$ 个 $2n+1$，于是前者前缀和，后者快速幂即可。

复杂度一只老哥。

## Code

```cpp
int n,m,f[N<<1],s[N<<1];

il void init()
{
	f[0]=f[1]=1,s[0]=1;
	rep(i,2,(N<<1)-1) f[i]=mod_(f[i-1]+f[i-2]),i&1 || (s[i]=mod_(s[i-2]*f[i]));
}

il void solve()
{
	read(n,m),n>m && (swap(n,m),1);
	write((int)mod_(mod_(s[n<<1]*s[n<<1])*fpow(f[(n<<1)+1],m-n)),'\n');
}
```

---

华风夏韵，洛水天依！

---

## 作者：CrTsIr400 (赞：3)

## [[ARC166C] LU / RD Marking](https://www.luogu.com.cn/problem/AT_arc166_c)

~~考试花了一个小时，也没切。考场下看一眼题解，就切了。为啥我这么菜啊。~~

### 题意

$H\times W$ 的矩阵，操作 $1$ 是给一个小矩形的左、上两条边标记，操作 $2$ 是给一个小矩形的右、下两条边标记，这两个操作需要待标记边未被标记才能进行。求最终所有可能出现的标记种类 $\bmod\ 998244353$ 的值。

### 破题点

思考一下 LU 和 RD 边，它们**关于空间对称**。

一次是选择两条边，于是很自然地想到考虑把边转化成点，把操作 $1$ 或者 $2$ 转化成为连边。

观察相邻的边不能选。观察图形我们发现是 $(H+W-1)$ 条不相交的链，从右上角到左下角的不相交的链。

### 题解

相邻的边不能选，很明显就是斐波那契数列的结论（可以考虑 DP 证明，式子和斐波那契一样）；

则对于长度为 $n$ 的链的答案就是 $fib[n+1]$（注意它可以不选）；

对于前 $H$ 条和后 $H$ 条链，长度无非就是 $1,3,5,7\ldots 2H-1$（假设 $H\le W$，因为空间对称性可以旋转）。利用斐波那契前缀积可以优化。

图形中还有 $W-H$ 条长度为 $2H$ 的链，也要利用快速幂算上。

于是就结束了。

### 代码实现

这里使用 ATCoder 的同余类，方便实现。

```cpp
#include<bits/stdc++.h>
#include<atcoder/all>
using atcoder::modint998244353;
#define fo(i,a,b) for(auto i(a),_ei(b);i<=_ei;++i)
#define gch(w) for(;w(CH);CH=getchar())
using I=int;using V=void;using LL=long long;I FL,CH;LL in(){LL a(0);FL=1;gch(!isdigit)FL=(CH=='-')?-1:1;gch(isdigit)a=a*10+CH-'0';return a*FL; }using namespace std;
using MI=modint998244353;
const I N=2e6+10;
MI f[N],fpv[N];
MI ksm(MI x,I y){MI a(1);
	for(;y;y>>=1,x*=x)if(y&1)a*=x;
	return a;}
I main(){f[0]=1;f[1]=2;
	fo(i,2,I(2e6))f[i]=f[i-1]+f[i-2]; 
	fpv[1]=2;
	for(I i=3;i<=I(2e6);++i,++i)
		fpv[i]=fpv[i-2]*f[i];
	I T=in();
	while(T--){
		I n=in(),m=in();
		if(n>m)swap(n,m);
		printf("%d\n",ksm(fpv[2*n-1],2)*ksm(f[2*n],m-n));}
	return 0;
}
```



---

## 作者：SunsetVoice (赞：2)

挺有意思的题，教练出到模拟赛里面了导致个人差极大，放过了我这种运气选手。

第一次场蓝就切双蓝，非常激动的。

题目中说“上左或下右”染色，这提示我们不能按常规的转移思路想否则会掉入陷阱中。我们试图找到一个相互独立的计算方法。

另一种方法是考虑点，类似二分图的想法，略为麻烦此处不做赘述。

于是想到斜对角剖开格子。这样，各个区块都是互不干扰的，我们直接考虑区块贡献怎么算即可。

对于一个长度为 $i$ 的区块：

- 选边，则剩余方案数量为 $i-2$。
- 不选边，此时倒数第二条线是能放的，则剩余方案数量为 $i-1$。

所以这就是一个斐波那契数列，预处理就可以。

不妨设 $n<m$。

对于两侧不满的数列，一侧贡献为 $\prod_{i=1}^{n}f_{2i}$，这个能够预处理。

对于中间长度一致的序列，贡献为 $f_{2n+1}^{m-n}$，快速幂处理就可以。

于是就做完了所有题。


```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
int n,m,g[3000001] = {0},gb[3000001] = {0};
const int mod = 998244353;
int qpow(int x,int y){
	int hjx = x%mod,ans = 1;
	while(y){
		if(y&1){
			ans*=hjx;
			ans%=mod;
		}
		hjx*=hjx;
		hjx%=mod;
		y>>=1;
	}
	return ans%mod;
}
signed main(){
	int T;
	cin>>T;
	g[1] = 1;
	g[2] = 2;
	for(int i = 3;i<=2500000;i++){
		g[i] = g[i-2]+g[i-1];
		g[i]%=mod;
	}
	gb[0] = 1;
	for(int i = 1;i<=1000500;i++){
		gb[i] = gb[i-1]*g[i*2];
		gb[i]%=mod;
	}
	while(T--){
		cin>>n>>m;
		if(n>m)swap(n,m);
		int ans = gb[n];
		ans*=ans;
		ans%=mod;
		ans*=qpow(g[2*n+1],m-n)%mod;
		cout<<ans%mod<<endl;
	}
	return 0;
}
```
~~你是怎么知道我模拟赛两侧贡献的~~ `gb` ~~数组开到 $2\times 10^6$ 访问越界痛失一百分的~~

---

## 作者：BINYU (赞：2)

## 题意

给定一个 $h$ 行 $m$ 列的网格，初始时所有的线都是白的，可以执行任意次以下操作（也可以不执行）：

1. 给一个小正方形左边界与上边界**同时**染黑；

2. 给一个小正方形右边界与下边界**同时**染黑。

求最终可能出现的图的个数。

## 思路

定义一条折线为从一个点出发，向下向左交替走，第一次和最后一次往哪边走无所谓，它的长度为走过的距离，发现整个网格可以用多条长度不同的折线组成，而操作 1 和 2 都是将一条折线上相邻的两条边染黑，**不会影响其他折线**，所以我们可以对每条折线的方案数单独计算，最后相乘即可。

现在讨论单条折线，可以发现，因为操作 1 和 2 是对称的，所以折线的方案数和它起始方向无关，结合一条折线可以**仅用它的长度和起始方向表示**，进而得出折线的方案数**只跟它的长度有关**。

我们利用这一点，考虑设计一个状态关于长度的 DP 来求方案。

设 $dp_i$ 表示一条长度为 $i$ 的折线的合法方案数。

转移时分一下两种情况讨论：

1. 要将这条边与折线上的前一条边染黑（这里已经把操作 1 和 2 统一化了，具体选择那个操作取决于当前边的方向），从 $dp_{i-2}$ 转移；

2. 不染这条边，从 $dp_{i-1}$ 转移。

因为是计数类 DP，所以 DP 方程为：$dp_i = dp_{i-1}+dp_{i-2}$，初始状态为 $dp_0 = dp_1 = 1$。

再考虑在网格内每种长度的折线有多少条，先钦定 $h \le m$（$h > m$ 可以互换 $h$ 和 $m$），分三类讨论：

1. 折线起点在网格上边界上，终点在左边界上，此时折线长度为 $2i$（$1 \le i \le h$），每种有 $1$ 条；

2. 折线起点在网格上边界上，终点在下边界上，此时长度为 $2h + 1$，有 $m-h$ 条；

3. 折线起点在网格右边界上，终点一定在下边界上，此时折线长度为 $2i$（$1 \le i \le h$），每种有 $1$ 条；

所以答案为 $(\prod_{i = 1}^{h}dp_{2i})^2\times (dp_{2h + 1})^{m-h}$。

发现 $dp$ 和 $\prod_{i = 1}^{h}dp_{2i}$ 可以预处理，后面的那一段可以用快速幂算，注意此处 $dp$ 数组要**开两倍**。

时间复杂度 $O(h+t\log h)$，空间复杂度 $O(h)$，可过。

---

## 作者：hejianxing (赞：2)

[link](https://www.luogu.com.cn/problem/AT_arc166_c)

# 题意

有 $n\times m$ 的网格，可以染色若干次，每次可以将一个格子的上边和左边染黑，或者将格子的下边和右边染黑。每条边最多染色一次。求最终结果的方案数，$\bmod 998244353$。$T$ 组数据。$1\le n,m\le 10^6,1\le T\le 2\times 10^{5}$。

# 题解

将边看作点，染色就是染 $(i,j)$ 和 $(i+1,j-1)$，将这样的点连边。因为染色方式只有一种（显然上边左边与下边右边是等价的），所以这个点阵构成了若干条互不相关的斜向的链。答案就是这些链的方案的乘积。

考虑一条边数为 $n$ 的链。限制为相邻的边不能同时选。设 $f_i$ 表示前 $i$ 条边的方案，则转移式为 $f_i=f_{i-1}+f_{i-2}$，因为第 $i$ 条边若不选，则方案为 $f_{i-1}$，第 $i-1$ 条边选不选都无所谓。若第 $i$ 条边选，则第 $i-1$ 条边一定不能选（只有 $1$ 种可能），所以从 $f_{i-2}$ 转移过来。初始态为 $f_0=1,f_1=2$。

于是这个方案数是斐波那契数列。这个东西可以先 $O(n)$ 预处理。

观察发现，一个矩形切割出的若干条链的边数是形如 $1,3,5,7,8,8,8,8,7,5,3,1$ 这样的。对于左右两边（$1,3,5,7$），可以求一个 $f$ 序列奇数位的前缀积，这个同样可以 $O(n)$ 预处理。中间的部分（$8,8,8,8$）就直接快速幂。最后三部分乘起来就结束了。

总的时间复杂度 $O(n+T\log n)$。

#  实现

随便找个例子看一下三个部分的分界点就行。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2000005;
const LL mod = 998244353;
int T, n, m;
LL f[N], sum[N];
void init() {
	f[0] = 1;
	f[1] = sum[1] = 2;
	for (int i = 2; i < N; i++) f[i] = (f[i - 1] + f[i - 2]) % mod;
	for (int i = 3; i < N; i += 2) sum[i] = sum[i - 2] * f[i] % mod;
}
LL qpow(LL x, LL y) {
	LL s = 1;
	while (y) {
		if (y & 1) s = s * x % mod;
		x = x * x % mod, y >>= 1;
	}
	return s;
}
int main() {
	init();
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		if (n > m) swap(n, m);
		printf("%lld\n", sum[2 * n - 1] * sum[2 * n - 1] % mod * qpow(f[2 * n], m - n) % mod);
	}
	return 0;
}
```


# 启示

- 这种题要找到操作内部的逻辑相关性，化边为点是一种可能的处理手段。

---

## 作者：fish_love_cat (赞：1)

哇这转化真的显然吗，想了一个世纪才拆出来。

---

我们钦定 $n\le m$。

首先考虑把棋盘划分成互不干扰的几个部分。

那么会得到下面的这个棋盘：

![](https://cdn.luogu.com.cn/upload/image_hosting/xd2xmp0p.png)

图来自 @[Halberd_Cease](https://www.luogu.com.cn/user/441247) 的 [题解](https://www.luogu.com.cn/article/x84uecik)。

我们只要对于每个同色的块求出方案数，那么最终答案就是所有块答案的积。

容易发现当前三角形可以染色时前面一个必不能染色，于是可以得到有 $i$ 个三角形时方案数为：

$$f_i=f_{i-1}+f_{i-2}$$

其中有 $f_1=2,f_2=3$。

继续观察图形发现，答案总共由以下三部分组成：

![](https://cdn.luogu.com.cn/upload/image_hosting/lzr91w8f.png)

于是答案就是这么一个柿子：

$$f_{2\times n}^{m-n}\times\prod_{i=1}^nf_{2\times i-1}^2$$

可以预处理 $f$ 以及后面的 $\prod_{i=1}^nf_{2\times i-1}^2$，然后对于 $f_{2\times n}^{m-n}$ 使用快速幂即可。

那么做完了。

---

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int fib[2000005];
int p[1000005];
#define flc_INF LLONG_MAX
int qpow(int a,int b,int p=flc_INF){
	int ans=1;
	if(b==0){
		return 1;
	}
	while(b){
		if(b&1){
			ans*=a;
			ans%=p;
		}
		a*=a;
		b>>=1;
		a%=p;
	}
	return ans;
}
signed main(){
    int q;
    cin>>q;
    fib[1]=2,fib[2]=3;
    for(int i=3;i<=2000000;i++)
    fib[i]=(fib[i-1]+fib[i-2])%mod;
    p[0]=1;
    for(int i=1;i<=1000000;i++)
        p[i]=p[i-1]*fib[2*i-1]%mod*fib[2*i-1]%mod;
    while(q--){
        int n,m;
        cin>>n>>m;
        if(n>m)swap(n,m);
        cout<<qpow(fib[2*n],m-n,mod)*p[n]%mod<<'\n';
    }
    return 0;
}
```

---

## 作者：PCCP (赞：1)

## 思路

赛时没有想出来这道题，后来看到官方题解的图一下就明白了（

首先贴一下这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ehh6ot2a.png)

首先整个方格看起来很复杂有很多组合可能，但是每一个方格的操作只能对左上或者右下的边进行染色，互相独立。那么就可以得到官方题解里的那个折线图，每一条折线间相互独立，于是就转化成了在每一条折线上划分为若干长度为 $ 2 $ 的折线。两条折线之间，任一折线可取任意数量的折线段，但相邻折线不能重叠。

很显然的一个 DP 就是：

$$ f_i=f_{i-1}+f_{i-2} $$

其中 $ f_i $ 表示在遍历到横向长度（横纵长度一样）为 $ i $ 的折线的答案，因为不能重叠，那选他就不能选 $ i-1 $ 要空开来选 $ i-2 $，不选他就可以选 $ i-1 $。

那这不就是斐波那契数列，由于数据组数很多，我们提前预处理就好了。~~（不知道有没有大师用的矩阵加速）~~

最后的答案就是乘起来即可：

$$ (f_1f_2\dots f_n)^2f_{2n+1}^{m-n} $$

此处 $ m\ge n $ 不过由于 $ m $ 和 $ n $ 的大小关系不定，交换一下就好了。

## 代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<stack>
#include<set>
using namespace std;
const int N=2e6+10;
const int MOD=998244353;
int t,n,m;
long long fib[N],g[N],ans;
long long ksm(long long x,long long y){
	long long res=1;
	while(y){
		if(y&1){
			res=res*x%MOD;
		}
		y>>=1;
		x=x*x%MOD;
	}
	return res;
}
int main(){
	scanf("%d",&t);
	fib[1]=1;
	for(int i=2;i<=N-5;i++){
		fib[i]=(fib[i-1]+fib[i-2])%MOD;
	}
	g[0]=1;
	for(int i=1;i*2<=N-5;i++){
		g[i]=g[i-1]*fib[i*2-1]%MOD;
	}
	while(t--){
		scanf("%d%d",&n,&m);
		if(n>m){
			swap(n,m);
		}
		ans=g[n+1]*g[n+1]%MOD;
		ans=ans*ksm(fib[n*2+2],m-n)%MOD;
		printf("%lld\n",ans);
	}
}
```


---

## 作者：鲤鱼江 (赞：0)

挺有意思一个题，无心之举让我快速切出了这个题。

发现有一个矩形，每次可以操作左边和上边或右边与下边，那么我们连上对角线，如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/498bg2ve.png)

分成红色和蓝色两个三角形，这两个三角形染色是互不干扰的，会互相干扰的是下面的同色的三角形：

![](https://cdn.luogu.com.cn/upload/image_hosting/ocq7gqhp.png)

每一条同色三角形独立，且方案明显是斐波那契数列。

求出斐波那契前缀积和具体每一项，暴力做就行了。

$O(n+T\log n)$。

```cpp
#include<bits/stdc++.h>
#define endl '\n'

using namespace std;

const int N=2e6+10;
const int mod=998244353;
struct modint {
    int val;
    static int norm(const int& x) { return x < 0 ? x + mod : x; }
    modint inv() const {
        int a = val, b = mod, u = 1, v = 0, t;
        while (b > 0) t = a / b, swap(a -= t * b, b), swap(u -= t * v, v);
        return modint(u);
    }
    modint() : val(0) {}
    modint(const int& m) : val(norm(m)) {}
    modint(const long long& m) : val(norm(m % mod)) {}
    modint operator-() const { return modint(norm(-val)); }
    modint& operator+=(const modint& o) { return val = (1ll * val + o.val) % mod, *this; }
    modint& operator-=(const modint& o) { return val = norm(1ll * val - o.val), *this; }
    modint& operator*=(const modint& o) { return val = static_cast<int>(1ll * val * o.val % mod), *this; }
    modint operator-(const modint& o) const { return modint(*this) -= o; }
    modint operator+(const modint& o) const { return modint(*this) += o; }
    modint operator*(const modint& o) const { return modint(*this) *= o; }
	friend std::ostream& operator<<(std::ostream& os, const modint a) { return os << a.val; }
}f[N],g[N];
int n,m,T;

inline modint expow(modint x,int y){modint res=1;for(;y;y>>=1,x*=x) if(y&1) res*=x;return res;}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	f[1]=g[1]=2;f[2]=3;g[2]=6;
	for(int i=3;i<N;++i){
		f[i]=f[i-1]+f[i-2];
		g[i]=g[i-2]*f[i];
	}
	cin>>T;
	while(T--){
		cin>>n>>m;
		if(n>m) swap(n,m);
		cout<<expow(f[2*n],m-n)*g[2*n-1]*g[2*n-1]<<endl;
	}
	return 0;
}
```

---

## 作者：lalaouye (赞：0)

这种类型的题（对脑电波题）有些题能秒，有些题想多久都想不出来。。。

显然本题能一起染黑的边存在某种关系，我们考虑一条边可以和哪两条边一起染色，乍一看如果还没看出来有什么性质，我们就考虑把连着的边再这样考虑一遍。

突然，灵光乍现！我们这样连可以连出来个斜线！也就是说我们可以将网格图拆开，分开讨论每一个斜线。我们把每个斜线拉直变成序列，发现这显然可以 dp 处理，设 $f_{i,0}$ 表示到第 $i$ 位末尾有偶数个点染黑， $f_{i,1}$ 表示到第 $i$ 位末尾有奇数个点染黑，转移非常 easy：

$$f_{i,0}=f_{i-1,0}+f_{i-1,1}$$
$$f_{i,1}=f_{i-1,0}$$

然后我们再回到网格图，手玩一下就会发现分开的斜线含有的边的数量是一个类似分段函数的东西，不妨设 $n<m$，前 $n$ 条斜线的长度是差为 $2$ 的等差数列，后面有 $m-n$ 条长度为 $2n+1$ 的斜线，再往后有跟第一段等价的一段。

那么我们预处理出累乘的值，每次询问再用快速幂算出第二段的值就做完啦！

时间复杂度 $\mathcal{O}(n+T\log n)$。

代码：

```
int f[N][2], g[N];
signed main ()
{
  f[0][0] = 1;
  g[0] = 1;
  rep (i, 1, N - 1) f[i][0] = (f[i - 1][0] + f[i - 1][1]) % P, f[i][1] = f[i - 1][0];
  rep (i, 1, N - 1) if (i & 1) g[i + 1] = g[i - 1] * f[i + 1][0] % P;
  int T = rd ();
  for (; T; -- T)
  {
    int n = rd (), m = rd ();
    if (n > m) swap (n, m);
    printf ("%lld\n", g[n * 2] * g[n * 2] % P * qpow (f[n * 2 + 1][0], m - n) % P);
  }
}
```

---

## 作者：Erine (赞：0)

很巧妙清新的题！

考虑对网格做一个划分：

![](https://cdn.luogu.com.cn/upload/image_hosting/ygxczj3p.png)

然后我们会发现，一次染色只会影响一个色块的网格。进一步地，我们考虑用凸出的格点描述每次染色：

![](https://cdn.luogu.com.cn/upload/image_hosting/bbdsswq0.png)

注意到，一种染色方案是合法的，当且仅当在每一条斜线上不存在相邻且被染色的格点。

考虑一条一个有 $n$ 个格点的同色的斜线的方案数。有 dp 式：

$$f_{i}=f_{i-1}+f_{i-2}$$

其中 $f_0=1$ 且 $f_1=2$。

此时如果能快速计算出 $n$ 行 $m$ 列的网格中每个划分的格点数量，再将它们的 $f_i$ 对应相乘即可得到答案。

由对称性不妨设 $n\le m$，则从左下角向右上作斜率为 $1$ 的射线，其左上方的划分的格点数依次是 $1,3,5,\dots ,2n-1$，右上角向左下作射线同理，此部分为 

$$\left(\prod_{i=1}^n f_{2i-1}\right)^2$$

而对于两条射线中间部分，所有划分的格点数都相同且为 $2n$，这样的划分一共 $m-n$ 个，所以这部分答案是

$$f_{2n}^{m-n}$$

综上，总方案数为

$$\left(\prod_{i=1}^n f_{2i-1}\right)^2f_{2n}^{m-n}$$

前半部分预处理奇数项前缀积，后半部分快速幂即可。时间复杂度 $\Theta(n+T\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 2e6 + 10;
const int mod = 998244353;

int T, n, m;
int f[maxn], g[maxn];

int power(int a, int b) {
	int t = 1;
	while (b) {
		if (b & 1) t = t * a % mod;
		a = a * a % mod, b >>= 1;
	}
	return t;
}

signed main() {
	f[0] = 1, f[1] = 2, g[0] = 1;
	for (int i = 2; i < maxn; i++) f[i] = (f[i - 1] + f[i - 2]) % mod;
	for (int i = 1; (i << 1) - 1 < maxn; i++) g[i] = g[i - 1] * f[(i << 1) - 1] % mod;
	cin >> T;
	while (T--) {
		cin >> n >> m;
		if (n > m) swap(n, m);
		cout << power(f[n * 2], m - n) * g[n] % mod * g[n] % mod << endl;
	}
	return 0;
}

```

---

## 作者：未来姚班zyl (赞：0)

## 题目大意
给你一个 $n\times m$ 大的正方形网格。你可以给一个正方形的左、上边或者右、下边染色，前提是这两条边没被染色，求染色若干次后可能的局面的总数。

## 题目分析

显然，对于每一条横线，与它关联的有左下的竖线和右上的竖线。同理，每一条竖线也只跟左下的横线和右上的横线相关。这时就可以发现。对于每个斜 $45\degree$ 左下到右上的线上的横竖线是相互关联的，相互关联的线相互连接形成若干条斜线，这些斜线互不关联，所以我们可以单独每条斜线的方案然后求个积就行。

可以发现，对于每条斜线，可以将选择相邻的两条线当成选择这两条线所夹的正方形，且正方形不能相邻。这样的方案数是可以直接 $O(n)$ dp 出来的。由于多组询问，所以要预处理。

然后可以发现，我们设 $N\le M$，则左上角和右下角的斜线对应的正方形数量都依次为：$1,3,5,\dots,2N-1$。而中间的斜线都对应了 $2N$ 个正方形，且恰有 $n-m$ 条，前者预处理前缀积，后者快速幂即可。复杂度 $O(N+T\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1LL)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK l>=Ll&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =2e5+5,M=3e6+5,inf=(1LL<<31)-1;
const ll llf=2e18,mod=998244353,bas=131;
const ui base=13331;
using namespace std;
inline ll qp(ll a,ll b){
	if(!b)return 1;
	ll c=qp(a,b>>1);
	c=c*c%mod;
	if(b&1)c=c*a%mod;
	return c;
}
int T=read(),n,m;
ll f[M][2],g[M];
inline void prep(){
	f[1][0]=f[1][1]=1;
	rep(i,2,M){
		f[i][1]=f[i-1][0];
		f[i][0]=(f[i-1][0]+f[i-1][1])%mod;
	}
	g[1]=2;
	for(int i=3;i<=M;i+=2)g[i]=g[i-2]*(f[i][0]+f[i][1])%mod;
}
signed main(){
	prep();
	while(T--){
		n=read(),m=read();
		if(n>m)swap(n,m);
		int ans=1;
		ans=g[n*2-1]*g[n*2-1]%mod*qp(f[n*2][0]+f[n*2][1],m-n)%mod;
		pf(ans),putchar('\n');
	}
	return 0;
}
```


---

## 作者：Ginger_he (赞：0)

![](https://cdn.luogu.com.cn/upload/image_hosting/9o5l6tem.png)

首先我们可以按照形如上图的方式将原来的方格拆成若干条互不影响的折线。更具体地说，我们可以拆出 $2\min\{h,w\}$ 条有奇数个折点的折线（折点个数为 $1,3,\dots,2\min\{h,w\}-1$ 的折线都恰好有 $2$ 条）以及 $|h-w|$ 条有偶数个折点的折线（这些折线的折点个数均为 $2\min\{h,w\}$）。

所以我们只需要知道每条折线的方案数就能通过乘法原理得出最后的答案。接下来需要考虑有 $k$ 个折点的折线的方案数 $f_k$，我们称选择一个折点为标记覆盖这个折点的折线，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/g3jtqxp1.png)

容易发现不能同时选择相邻的折点，这时候就有一个很显然的 dp，即

$$\begin{aligned}
&dp_{i,0}=dp_{i-1,0}+dp_{i-1,1}\\
&dp_{i,1}=dp_{i-1,0}
\end{aligned}$$

那么就有

$$\begin{aligned}
f_k&=dp_{k,0}+dp_{k,1}\\
&=dp_{k-1,0}+dp_{k-1,1}+dp_{k-1,0}\\
&=dp_{k-1,0}+dp_{k-1,1}+dp_{k-2,0}+dp_{k-2,1}\\
&=f_{k-1}+f_{k-2}
\end{aligned}$$

其中 $f_1=2,f_2=3$。

综上所述，我们只需要预处理出斐波那契数和奇数项的前缀积，令 $n=\min\{h,w\},m=|h-w|$，那么答案为

$$\left(\prod_{i=1}^n{f_{2i-1}}\right)^2\left(f_{2n}\right)^m$$

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 1<<21
const int p=998244353;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int t,h,w,n,m,f[N],g[N];
inline int quickpow(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=1ll*res*a%p;
		b>>=1;
		a=1ll*a*a%p;
	}
	return res;
}
int main()
{
	f[0]=1,f[1]=g[1]=2;
	for(int i=2;i<N;i++)
	{
		f[i]=(f[i-1]+f[i-2])%p;
		if(i&1) g[i]=1ll*g[i-2]*f[i]%p;
	}
	t=read();
	while(t--)
	{
		h=read(),w=read();
		n=min(h,w),m=abs(h-w);
		printf("%lld\n",1ll*g[2*n-1]*g[2*n-1]%p*quickpow(f[2*n],m)%p);
	}
	return 0;
}
```

---

