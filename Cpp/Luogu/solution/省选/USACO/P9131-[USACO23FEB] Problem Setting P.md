# [USACO23FEB] Problem Setting P

## 题目描述

**注意：本题的内存限制为 512MB，是默认值的两倍。**

农夫约翰创建了 $N(1 \le N \le 10^5)$ 个问题。然后他招募了 $M (1 \le M \le 20)$ 个测试解答者，每个解答者将每个问题评为“简单”或“困难”。

他的目标是创建一个按难度递增顺序排列的问题集，该问题集由他的 $N$ 个问题的某个子集按某种顺序排列而成。必须不存在这样的一对问题，使得某个测试解答者认为顺序中后面的那个问题简单，而前面的那个问题困难。

计算他可以形成的不同非空问题集的数量，结果对 $10^9+7$ 取模。

## 说明/提示

### 样例 1 的解释

九个可能的问题集如下：

$[1]$  
$[1,2]$  
$[1,3]$  
$[1,3,2]$  
$[2]$  
$[3]$  
$[3,1]$  
$[3,2]$  
$[3,1,2]$  

注意问题集内问题的顺序很重要。

### 评分

- 输入 $3-4$：$M=1$
- 输入 $5-14$：$M \le 16$
- 输入 $15-22$：无额外限制。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3 1
EHE```

### 输出

```
9```

## 样例 #2

### 输入

```
10 6
EHEEEHHEEH
EHHHEEHHHE
EHEHEHEEHH
HEHEEEHEEE
HHEEHEEEHE
EHHEEEEEHE```

### 输出

```
33```

# 题解

## 作者：Little09 (赞：16)

首先我们把每道题 `H` 看做 $1$，`E` 看做 $0$ 的话，那么条件变成了选若干道题并排序，使得相邻两项满足前一项是后一项的子集。

把状态相同的题目放在一起考虑，假设有 $k$ 道题，那么选择至少一题的方案数就是：

$$\sum_{i=1}^k\binom kii!$$

可以直接预处理。那么现在我们需要按顺序进行 DP 转移，有以下几种方法：

### 直接暴力

定义 $dp_{S}$ 表示最后一项是 $S$ 的选法的方案数，那么每次的转移我们需要枚举 $S$ 的所有子集进行转移，按 $S$ 大小依次转移。直接转移的总复杂度为 $O(3^m)$。

### 分成前后两部分

这套路某年 CSP 初赛考过。

刚才的瓶颈在于枚举子集，那能不能改进一下。考虑 $s_{i,j}$ 表示所有 $dp_{x}$ 的和，其中 $x$ 需要满足前 $10$ 位是 $i$，后 $10$ 位是 $k$，其中 $k$ 是 $j$ 的子集。

这样我们每次计算 $dp$ 的时候只要枚举上一个的前 $10$ 位，转移 $s$ 的时候枚举后 $10$ 位，复杂度大致是 $O(n2^{\frac m2})$，可以精细分析到更准确的下界 $O(6^{\frac m2})$，空间可以做到 $O(2^m)$。

```cpp
for (int i=0;i<=mx;i++)
{
	if (b[i]==0) continue;
	int A=i>>10,B=i&1023;
	ll res=1;
	for (int j=0;j<1024;j++) if ((j&A)==j) (res+=dp[j][B])%=mod;
	f[i]=val[i]*res%mod;
	for (int j=0;j<1024;j++) if ((j&B)==B) (dp[A][j]+=f[i])%=mod;
	(ans+=f[i])%=mod;
}
```


### 按 $|S|$ 顺序

考虑按 $|S|$ 顺序进行 DP 转移，也就是按照 $|S|$ 分成 $m$ 层，每一层一定是从之前的层里转移过来。那么我们只需要做完每一层后做一次 FMT 累计入答案，每次计算 $dp$ 的时候可以直接 $O(1)$ 计算，这样时间可以做到 $O(m^22^m)$，空间可以做到 $O(2^m)$。

```cpp
for (int i=0;i<=m;i++)
{
	for (int j=0;j<(1<<m);j++) dp[j]=0;
	for (int j=0;j<(1<<m);j++)
	{
		if (__builtin_popcount(j)!=i) continue;
		dp[j]=(1+s[j])*val[j]%mod;
		(ans+=dp[j])%=mod;
	}
	FMT();
}
```


### FMT 同时转移（官方做法）

考虑我们执行 FMT 的过程，比方说在做完前 $k$ 位的时候我们得到的数组是什么：$s_i$ 是需要满足前 $k$ 位是 $i$ 的前 $k$ 位的子集，$k$ 位以后恰好就是 $i$ 的 $k$ 位以后，这样的位置的和。

我们直接定义 $sdp_{b,i}$ 表示所有 $dp_{x}$ 的和，其中 $x$ 满足前 $k$ 位是 $b$ 的前 $k$ 位的子集，$k$ 位以后恰好就是 $b$ 的 $k$ 位以后。如果我们计算出了 $dp_b$，我们可以在 $O(m)$ 的时间里计算出 $sdp_b$ 的每个位，递推即可。而我们如果得到了所有 $sdp_x$ 满足 $x<b$，我们也可以 $O(m)$ 计算出 $dp_b$，枚举不同的第一个位置转移即可。

这样可以做到时间 $O(m2^m)$，空间 $O(m2^m)$。

```cpp
for (int i=0;i<(1<<m);i++)
{
	dp[i]=1;
	for (int j=0;j<m;j++) if (i&(1<<j)) (dp[i]+=s[j][i^(1<<j)])%=mod;
	dp[i]=dp[i]*val[i]%mod;
	s[0][i]=dp[i];
	(ans+=dp[i])%=mod;
	for (int j=1;j<m;j++) 
	{
		s[j][i]=s[j-1][i];
		if (i&(1<<(j-1))) (s[j][i]+=s[j-1][i^(1<<(j-1))])%=mod;
	}
}
```


### 分治

考虑对最高位 $0/1$ 分治，也就是在 trie 的结构上做类似 CDQ 分治的东西。那么就是先做左儿子，接下来考虑左儿子对右儿子的贡献，再做右儿子。

考虑记以 $S$ 结束的答案为 $dp_S$，我们还需要在 trie 上一边遍历一边维护 $dp$ 的 FMT 数组 $g$，假设当前做到的位是 $d$，目前已有的数是 $S$，我们需要 $g_i$ 是 $dp_j$ 的和，其中 $j$ 满足满足最高的 $d$ 位和 $i$ 相同，后面的位是 $i$ 子集。那么在每个节点做完左右儿子后，我们把当前子树内的 $g$ 从左儿子向右儿子累加即可。

时间复杂度为 $O(m2^m)$，空间复杂度为 $O(2^m)$。

```cpp
void solve(int i,int S) 
{
	if (i==-1) 
	{
		Add(g[S],dp[S]);
		return;
	}
	solve(i-1,S);
	for (int T=0;T<(1<<i);T++) Add(dp[S|T|(1<<i)],g[S|T]*val[S|T|(1<<i)]%mod);
	solve(i-1,S|(1<<i));
	for (int T=0;T<(1<<i);T++) Add(g[S|T|(1<<i)],g[S|T]);
}
```


---

## 作者：IamZZ (赞：6)

**P组练习总结#3**

### 题目大意

FJ 为 USACO 贡献了 $n(n\leq10^5)$ 道题来恶心选手们，他也聘请了 $m(m\leq20)$ 位验题人（怕不是奶牛，不然怎么出这么离谱）。

每一位验题人对 $n$ 道题目都有一个难度评定（两种之一），`E` 和 `H`，代表题目简单或者困难。

如今，FJ 立志于出一场比赛，他需要选择几道题组合一下（不能不选），选出来的题可以任意排列。

排列后，需要满足一个条件：如果一个验题人觉得第 $i$ 道题难，他也必须觉得 $i+1$ 题难，相当于这个验题人认为这个排列的难度递增咯（怪良心的）。

现在 FJ 想要知道有多少套题可以满足条件，答案可能很大，对 $10^9+7$ 取模。

### 题解思路（部分分）

这次我们一步步来，先从部分分入手。

$m$ 真的好小啊，提示我们从指数级寻找思路……

这种题目，我们应该想到状态压缩 DP，考虑状压每一道题验题人对它的态度。

`H` 视为 1，`E` 反之，这样我们就压缩出了 $n$ 个长度为 $m$ 的 01 串，经过这样的转换，我们考虑限制条件怎样变化了。

首先，题目难度递增，我们发现，这个在 01 串上也表现为单调递增，因此 DP 可行。

而且，相同值的题可以放在一起处理，他们之间没有区别，因此我们统计每个值的个数 $c_i$。

至于另一个限制条件，我们设选取了 $p_1,p_2,p_3\dots sp_c$ 号题，依次排列，而第 $i$ 道题状压后的值为 $w_i$，则需要满足 $w_{p_i}\operatorname{and} w_{p_{i+1}}=w_{p_i}$。

观察可知，觉得 $p_i$ 难的人是觉得 $p_{i+1}$ 难的人的子集（部分分做法遍历子集时使用的方法很新，很高效）。

好了，有了这些条件，我们可以开始我们的 DP 了：

设 $f_i$ 为当前选中最后一道题为 $i$ 时的方案数。

首先，我们要找到上一次选择的最后一道题 $j$，统计 $v=1+\sum_{j\operatorname{and}i=i,j\neq i}f_j$（$+1$ 是因为可以选择直接作为开头）。

而当前的 $i$ 有多少种排列方式？我们可以从 $c_i$ 个中选择任意（不为 0）个，并任意排列，计算 $s=\sum_{i=0}^{c_i-1}\frac{c_i!}{i!}$，暴力算就好。

有了这些，我们已经可以看出来 $f_i$ 的转移方程了吧？没错，就是 $f_i=v\times s$，最后的答案将所有的 $f_i$ 加在一起即可。

### 参考代码（部分分）

真觉得遍历子集挺妙的……

```c++
#include<bits/stdc++.h>//60pts
using namespace std;
const int N=1e5+5,M=1<<20,d=1e9+7; 
int n,m,a[N],f[M],v,s[N]={1},t[N],c[M],ans;
char ch[N];
int quickpow(int b,int p)
{
	int w=1;
	while(p)
	{
		if(p&1)
		  w=1ll*w*b%d;
		b=1ll*b*b%d;
		p=p>>1;
	}
	return w;
}
int calc(int p)
{
	int i,v=0;
	for(i=0;i<=p-1;++i)
	  v=(v+1ll*s[p]*t[i]%d)%d;
	return v;
}
void init()
{
	int i;
	for(i=1;i<=n;++i)
	  s[i]=1ll*s[i-1]*i%d;
	t[n]=quickpow(s[n],d-2);
	for(i=n;i;--i)
	  t[i-1]=1ll*t[i]*i%d;
	return ;
}
int main()
{
	int i,j;
	scanf("%d%d",&n,&m);
	init();
	for(i=1;i<=m;++i)
	{
		scanf("%s",ch+1);
		for(j=1;j<=n;++j)
		  a[j]=a[j]|(ch[j]=='H'?1<<i-1:0);
	}
	for(i=1;i<=n;++i)
	  ++c[a[i]];
	f[0]=calc(c[0])%d;
	ans=f[0];
	for(i=1;i<1<<m;++i)
	{
		v=1;
		for(j=i;j>=0;j=(j-1)&i)
		{
			if(j==i)
			  continue;
			v=(v+f[j])%d;
			if(!j)
			  break;
		}
		f[i]=1ll*v*calc(c[i])%d;
		ans=(ans+f[i])%d;
	}
	printf("%d",ans);
	return 0;
}
```

### 题解思路（正解）

但是，如你所见，上面的代码是不够优秀的。

考虑如何优化，现在我们转移的复杂度太慢了，导致最后有一个约为 $\Theta(3^m)$ 的总复杂度，无法通过全部测试点。

转移太慢，我们就把一部分工作分给前面的求值，提前把答案准备好了，优化时间复杂度，就快起来了不是吗？

是的，因此我们要引入辅助数组 $g_{i,j}$！

$g_{i,j}$ 代表当前状态为 $i$，$\sum_{k\operatorname{and}i=k,k\oplus i<2^{j}}f_k$ 的值，很抽象，是吧？

我来解释一下，找到那些题 $k$ 并求和，这些题 $k$ 满足是 $i$ 的子集且对 $k$ 和 $i$ 有不同意见的验题人最大编号恰好为 $j-1$，注意，是最大的**恰好**等于。

这样我们就可以用 $\Theta(m)$ 的复杂度实现来自 $f_i$ 子集的转移，只需要枚举最大不同的编号就可以全部统计了！

当然 $g_{i,j}$ 也有自己的转移，如下：

$g_{i,0}=f_i$，毕竟没有区别的也只有自己啦~

若 $i$ 的第 $j-1$ 位是 0，$g_{i,j}=g_{i,j-1}$，否则 $g_{i,j}=g_{i,j-1}+g_{i-2^{j-1},j-1}$，这个还比较好理解，一步步转移就好了。

这边处理也需要 $\Theta(m)$，但是我们已经成功将总复杂度分担之后降到了 $\Theta(m\times2^m)$！这已经足够通过这道题了（记得取模）。

完结撒花(●'◡'●)！

### 参考代码（正解）

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,M=1<<20,d=1e9+7; 
int n,m,a[N],f[M],v,s[N]={1},t[N],c[M],ans,g[M][21];
char ch[N];
int quickpow(int b,int p)
{
	int w=1;
	while(p)
	{
		if(p&1)
		  w=1ll*w*b%d;
		b=1ll*b*b%d;
		p=p>>1;
	}
	return w;
}
int calc(int p)//计算同一个值中的排列方式
{
	int i,v=0;
	for(i=0;i<=p-1;++i)
	  v=(v+1ll*s[p]*t[i]%d)%d;
	return v;
}
void init()
{
	int i;
	for(i=1;i<=n;++i)
	  s[i]=1ll*s[i-1]*i%d;
	t[n]=quickpow(s[n],d-2);
	for(i=n;i;--i)
	  t[i-1]=1ll*t[i]*i%d;
	return ;
}
int main()
{
	int i,j;
	scanf("%d%d",&n,&m);
	init();
	for(i=1;i<=m;++i)
	{
		scanf("%s",ch+1);
		for(j=1;j<=n;++j)
		  a[j]=a[j]|(ch[j]=='H'?1<<i-1:0);
	}
	for(i=1;i<=n;++i)
	  ++c[a[i]];
	f[0]=calc(c[0])%d;
	for(i=1;i<=m;++i)
	  g[0][i]=f[0];
	ans=f[0];
	for(i=1;i<1<<m;++i)
	{
		v=1;
		for(j=1;j<=m;++j)//f[i]的转移
		{
			if(i&(1<<j-1))//枚举最大的位数
			  v=(v+g[i^(1<<j-1)][j])%d;
		}
		f[i]=1ll*v*calc(c[i])%d;
		ans=(ans+f[i])%d;
		g[i][1]=f[i];
		for(j=1;j<m;++j)//g[i][j]的转移
		{
			g[i][j+1]=g[i][j];
			if(i&(1<<j-1))
			  g[i][j+1]=(g[i][j+1]+g[i^(1<<j-1)][j])%d;
		}
	}
	printf("%d",ans);
	return 0;
}
```



---

## 作者：luoguhandongheng (赞：4)

人生第一道 Sum over Subsets DP(SOSDP)。  
SOSDP 顾名思义，解决的是求 $f(T)=\sum\limits_{S \subset T}g(S)$ 的问题。

首先需要学会最简单的子集枚举。
```cpp
for (int m = 0; m < (1 << n); ++m)
  for (int s = m; s; s = (s - 1) & m)
```
第一层遍历 $T$，第二层遍历 $S$。$s \gets (s-1) \land m $ 相当于把找到 $s$ 的最后一个 $1$ 并取反，所以这样一定可以降序遍历 $T$ 的所有子集。由于最终遍历时每一位只可能出现 $m$ 为 $1$ 且 $s$ 为 $1$，$m$ 为 $1$ 且 $s$ 为 $0$，$m$ 为 $0$ 且 $s$ 为 $0$ 三种情况所以复杂度是 $O(3^n)$。

实际上对于一个状态 $i$，可以定义 $sum_{i,j}$ 表示只可以修改 $i$ 的前 $j$ 位且是 $i$ 的子集的所有 $f_i$ 的和。

那么 
$f_i=\sum\limits_{1 \le k \le n}\begin{cases} sum_{i \oplus(1<<k),i} & \text{if the k-th postion of i is 1} \\ 0 & \text{else} \end{cases}$。

同时， 
$sum_{i,j} \gets sum_{i,j-1}+[\text{the j-th postion of i is 1}]sum_{i \oplus (1<<j),j}  $。

且有初始化，
$sum_{i,1} \gets g_i+[\text{the first position of i is 1}]sum_{i\oplus 1}$。

这样我们可以得到 $O(n\times 2^n)$ 的算法解决这一问题。

回到这题，可以发现，对于一道题 $i$，每个验题人给他的评价 H(1),E(0) 可以按顺序写成长度为 $m$ 的 01 串。按照这一标准，可以将 $n$ 到题目分为 $2^m$ 组。设这组共有 $k$ 个题目，组内的排列顺序显然任意，单独一组（必须取）的方案数就是 $T(k)=A_k^1+A_k^2+ \dots + A_k^k$，可以直接预处理。组间顺序得先放子集，再放自己。设 $dp_i$ 表示以第 $i$ 组为结尾的方案数，那么 $dp_i \gets ((\sum_{j \subset i} dp_j)+ 1) \times T(|i|)$，$|i|$ 表示第 $i$ 组有多少题。看到了子集求和，可以套用上面 SOSDP 的办法，类似定义 $sumdp$。这道题就解决了。

直接枚举子集的 $O(3^n)$ CODE(60pts):
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 i128;
const int N=1e5+5,mod=1e9+7,M=20;
int n,m;
ll A[N],dp[1<<M];
int busket[1<<M];
string s[25];
int f(int x){
    bitset <20> bs;
    for(int i=0;i<m;++i){
        bs[i]=(s[i+1][x]=='E' ? 0 : 1);
    }
    int k=bs.to_ullong();
    return k;
}
void init(){
    A[1]=1;
    for(int i=2;i<=n;++i){
        A[i]=(A[i-1]*i%mod+i)%mod;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        cin>>s[i];
        s[i]=" "+s[i];
    }
    for(int i=1;i<=n;++i){
        busket[f(i)]++;
    }
    init();
    ll ans=A[busket[0]];
    dp[0]=A[busket[0]];
    for(int i=1;i<(1<<m);++i){
        i128 sum=0;
        for(int j=i;;j=(j-1)&i){
            sum=(sum+dp[j])%mod;
            if(j==0) break;
        }
        dp[i]=(sum*A[busket[i]]+A[busket[i]])%mod;
        (ans+=dp[i])%=mod;
    }
    cout<<ans;
    return 0;
}
```
SOSDP $O(n \times 2^n)$ CODE(100pts):
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 i128;
const int N=1e5+5,mod=1e9+7,M=20;
int n,m;
ll A[N],dp[1<<M],sdp[1<<M][M+5];
int busket[1<<M];
string s[25];
int f(int x){
    bitset <20> bs;
    for(int i=0;i<m;++i){
        bs[i]=(s[i+1][x]=='E' ? 0 : 1);
    }
    int k=bs.to_ullong();
    return k;
}
void init(){
    A[1]=1;
    for(int i=2;i<=n;++i){
        A[i]=(A[i-1]*i%mod+i)%mod;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        cin>>s[i];
        s[i]=" "+s[i];
    }
    for(int i=1;i<=n;++i){
        busket[f(i)]++;
    }
    init();
    ll ans=A[busket[0]];
    dp[0]=A[busket[0]];
    for(int i=1;i<=m;++i)
        sdp[0][i]=dp[0];
    for(int i=1;i<(1<<m);++i){
        i128 sum=0;
        for(int j=1;j<=m;++j){
            if(i&(1<<(j-1))){
                int pre=i^(1<<(j-1));
                sum+=sdp[pre][j];
                sum%=mod;
            }
        }
        dp[i]=(sum+1)*A[busket[i]];
        dp[i]%=mod;
        (ans+=dp[i])%=mod;
        sdp[i][1]=dp[i];
        if(i&1) (sdp[i][1]+=sdp[i^1][1])%=mod;
        for(int j=2;j<=m;++j){
            sdp[i][j]+=sdp[i][j-1];
            if(i&(1<<(j-1))){
                int pre=i^(1<<(j-1));
                sdp[i][j]+=sdp[pre][j];
                sdp[i][j]%=mod;
            }
        }
    }
    cout<<ans;
    return 0;
}
```
一些后话：SOSDP 好像就是快速莫比乌斯变化（FMT），~~可由于 FMT 过于高深我不会~~，所以就不涉及。

---

## 作者：2huk (赞：2)

我们把每一列看作一个行编号的集合 $S_i$，即若 $a_{j, i} = \texttt H$ 则 $j \in S_i$。那么一个序列 $(i_1,i_2,\dots,i_k)$ 合法，等价于 $S_{i_1} \subseteq S_{i_2} \dots \subseteq S_{i_k}$。

尝试 DP 这个东西：设 $f(S)$ 表示有多少合法序列以 $S$ 结尾。那么：

$$
f(S) = g(cnt_S) \times \sum_{S' \subseteq S} f(S')
$$

其中 $cnt_S$ 表示 $S$ 出现的次数（在所有列中）。$g(x)$ 表示从 $x$ 中任选若干个数，并任意排列的方案数。不难得出：

$$
\begin{aligned}
g(x) &= \sum_{i=1}^x A_x^i \\ 
     &= \sum_{i=1}^x \dfrac {x!}{i!} \\
     &= 1 + \sum_{i=1}^{x-1} \dfrac{(x-1)! \times x}{i!}\\
     &= 1 + x \times g(x - 1)
\end{aligned}
$$

我们一层一层转移，即按照 $|S|$ 转移。那么这一层的转移，等价于之前的层的 DP 值的高维前缀和。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 4e6 + 10, P = 1e9 + 7;

int n, m;
int s[N];         
int f[N], g[N];
int cnt[N];
vector<int> state[N];
int sum[N];

int main() {
  g[0] = 0;
  g[1] = 1;
  for (int i = 2; i < N; ++ i ) {
    g[i] = (1ll * i * (g[i - 1] + 1) % P) % P;
  }
  
  cin >> n >> m;
  
  for (int i = 0; i < m; ++ i ) {
    for (int j = 0; j < n; ++ j ) {
      char c;
      cin >> c;
      s[j] |= (c == 'H') << i;
    }
  }
  
  for (int i = 0; i < n; ++ i ) {
    cnt[s[i]] ++ ;
  }
  
  for (int i = 0; i < (1 << m); ++ i )
    state[__builtin_popcount(i)].push_back(i);
  
  f[0] = g[cnt[0]];
  for (int i = 1; i <= m; ++ i ) {
    
    for (int j = 0; j < (1 << m); ++ j ) sum[j] = f[j];
    for (int j = 0; j < m; ++ j )
      for (int k = 0; k < 1 << m; ++ k )
        if (k >> j & 1) sum[k] = (sum[k] + sum[k ^ (1 << j)]) % P;
    
    for (int k : state[i]) {
      f[k] = 1ll * (sum[k] + 1) * g[cnt[k]] % P;
    }
  }
  
  int res = 0;
  for (int i = 0; i < (1 << m); ++ i ) {
    res = (res + f[i]) % P;
  }
  cout << res;
  
  return 0;
}
```

---

## 作者：tc291311 (赞：1)

# P9131[USACO23FEB]Problem Setting P
~~题目说的很绕，意思就是所有**验题人都认为题目难度顺序单增**。~~

题目就不解释了，大家可以理解。
## 思路 1
大概是要做一个类似于半在线卷积的东西，只是在集合意义下。

考虑每次做完一层 popcount，然后再对这一层进行 FWT 之类的操作。

于是 $O(2^mm^2)$，~~然而我感觉 $O(3^m)$ 也可以~~通过了此题。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+10;
const int mod=1e9+7;
const int inf=1e9;
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define ppc(x) __builtin_popcount(x)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int n,m,a[maxn],c[maxn],v[maxn],dp[21][1<<20];
int fac[maxn],inv[maxn],ifc[maxn],ans;
inline void add(int &x,int y){x=(x+y>=mod?x+y-mod:x+y);}
inline void FMT(int *f,int len){
	for(int i=2;i<=len;i<<=1)
		for(int j=0,p=i/2;j<len;j+=i)
			for(int k=j;k<j+p;k++)add(f[k+p],f[k]);
}
int main(){
	n=read(),m=read();
	for(int i=0;i<m;i++){
		for(int j=1;j<=n;j++){
			char ch=getchar();
			if(ch=='H')a[j]|=(1<<i);
		}getchar();
	}for(int i=1;i<=n;i++)c[a[i]]++;v[1]=1;
	for(int i=2;i<=n;i++)v[i]=1ll*(1+v[i-1])*i%mod;
	for(int i=0;i<=m;i++){
		for(int j=0;j<(1<<m);j++)if(ppc(j)==i){
			int sum=1;
			for(int k=0;k<i;k++)add(sum,dp[k][j]);
			dp[i][j]=1ll*sum*v[c[j]]%mod;
			add(ans,dp[i][j]);
		}FMT(dp[i],(1<<m));
	}printf("%d\n",ans);
	return 0;
}

```

### 代码解释

变量以及宏定义就不多解释了。

但是数组稍微解释一下：

-  `fac`,`inv`,`ifc` ：分别存储阶乘、逆元和阶乘逆元的数组。

-  `add` ：将 $y$ 加到 $x$ 上，并对 $mod$ 取模。

-   `FMT` ：快速沃尔什变换（Fast Walsh-Hadamard Transform），用于优化某些本题类型的动态规划问题.

-   使用二维数组 `dp` 进行动态规划，其中 $dp_{i,j}$ 表示选择 $i$ 个状态且状态集合为 $j$ 的方案数。

最后累加得出答案即可。
## 思路 2
把这一列题在审核的过程抽象化，每个时刻个裁判都处在两个状态之一：

则我们可以把这些裁判的状态压缩成一个的二进制数。

每次加入一个新题，新的题目对应的状态必定是原先状态的超集。

那么把维持集合不变的都压成一步，状压 `dp` 即可。

思路 2 只是稍微扩充一下大家的思路，代码就不放了。

---

## 作者：I_am_Accepted (赞：1)

给出高维空间中一些关键点，没有重复点，点有点权，求所有有非严格偏序关系的非空子集的点权积的和。

想到 DP，对于空间每个位置 $p$，$f_p$ 为【每个维度坐标减一的位置 $p'$ 的 $f_{p'}$】之和。但是这样是不对的，因为两个相邻偏序点之间会算【两点空间中路径个数】遍。

所以我们规定每两个相邻点之间的路径按照维度顺序走每个维度，这样就保证了路径唯一。

枚举每个维度，设这个维度的值域为 $v$，依次做 $v$ 个子空间的问题。第 $i$ 个子空间的子问题依赖于所有第 $j<i$ 个子空间的答案。根据下文，这个依赖可以前缀和优化。

每个子问题要输入两个高维数组 $w,f$ 表示每个位置的关键点权（没有关键点则为 $0$），$f$ 表示每个位置从之前的子空间通过枚举的这一维走过来的方案数。

子问题返回一个数组 $f'$，表示每个点结尾的方案数（结尾不一定是关键点，可以通过子空间内的维度走）。

复杂度 $O(s\prod v)$，$s$ 是维度数。

对本题来说，每一维 $v=2$，参考代码：

```cpp
#define rep(Ii,Jj,Kk) for(int Ii=(Jj),Ii##_=(Kk);Ii<=Ii##_;Ii++)
const int M=20,N=1<<M;
int n,m,cnt[N];
Z w[N],f[N];// Z 为模意义下整数类
char s[M][100010];
void slv(int dp,int ma){
/*
input:
	w:本下标非空选择的方案数
	f:此位置结束的前缀（不接受 push_front）方案数

output:
	f:作为结尾的方案数
*/
	if(dp==-1){
		f[ma]+=w[ma];
		return ;
	}
	slv(dp-1,ma);
	rep(i,0,(1<<dp)-1) f[ma|(1<<dp)|i]+=w[ma|(1<<dp)|i]*f[ma|i];
	slv(dp-1,ma|(1<<dp));
	rep(i,0,(1<<dp)-1) f[ma|(1<<dp)|i]+=f[ma|i];
}
```

---

## 作者：Eric998 (赞：0)

独立切的第多少个紫来着。不数了。

考虑如果所有的题的评价完全相同会怎样。选择一个子集，并将子集内部的元素进行全排列，发现答案是 $f_i=\displaystyle \sum_{i=0}^nC_i^n\times i!=\sum_{i=0}^n\frac {n!}{i!}$。这东西显然有递推式 $f_i=if_{i-1}+1$。

定义 $c_i$ 是评价集合为 $i$ 的题目的个数，$a_i=f_{c_i}-1$，即选出至少一个评价集合为 $i$ 的集合并全排列的方案数。设 $dp_S$ 为最后一道题的集合为 $S$ 的方案数。枚举上一个出现的集合，转移显然：$dp_S=c_S(1+\displaystyle\sum_{T\in S,T\not =S}dp_T)$。直接做是 $O(3^m)$ 的，用 meet-in-the-middle 优化可以做到 $O(2.828^m)$，不可过。据说有 $O(2.445^m)$ 的做法（？

考虑枚举 $t=|S|$，对于每个 $t$，先做出 $t=|S|$ 的集合的答案，然后再把 $t\leq|S|$ 的集合的 $dp$ 值单独存下来做个 ```FWT```，下一轮计算直接使用。这样就强行钦定了一个转移顺序，可以做到 $O(n+2^mm^2)$。

code:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 1050000
#define M 1000000007
#define int long long

int a[N], val[N] = {1}, c[N], n, m, ans;
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for (int i = 1; i < N; i++)
		val[i] = (val[i - 1] * i + 1) % M;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < n; j++)
			c[j] += (s[j] == 'H') << i;
	}
	for (int i = 0; i < n; i++)
		a[c[i]]++;
	for (int i = 0; i < (1 << m); i++)
		a[i] = (val[a[i]] + M - 1) % M;
	memset(c, 0, sizeof(c));
	for (int i = 0; i < (1 << m); i++)
		c[i] = a[0] + 1;
	ans = a[0];
	for (int t = 1; t <= m; t++) {
		for (int i = 0; i < (1 << m); i++)
			if (__builtin_popcount(i) == t)
				a[i] = a[i] * c[i] % M, ans += a[i];
		memset(c, 0, sizeof(c)), c[0] = 1;
		for (int i = 0; i < (1 << m); i++)
			if (__builtin_popcount(i) <= t)
				c[i] += a[i];
		for (int j = 0; j < m; j++)
			for (int i = 0; i < (1 << m); i++)
				if (i & (1 << j))
					c[i] += c[i ^ (1 << j)];
		for (int i = 0; i < (1 << m); i++)
			c[i] %= M;
	}
	cout << ans % M;
}
```

---

## 作者：Laoshan_PLUS (赞：0)

## [[USACO23FEB] Problem Setting P](https://www.luogu.com.cn/problem/P9131)

题目说的很绕，意思就是**所有验题人都认为题目难度顺序单增**。

发现 $m$ 很小，很容易想到状压。把 `H` 看作 $\tt1$，`E` 看作 $\tt0$，则我们得到 $m$ 个长度为 $n$ 的 $\tt01$ 串，这就是每道题的 “状态”。发现状态相同的题没有本质区别，所以我们对于每个状态都统计有多少个题目，记为 $c_i$。

而对于单增的限制条件，我们转化为：对于所有相邻的两道题 $i$ 和 $i+1$，设 $s_i$ 为第 $i$ 题的状态，则一定满足：$s_i\subseteq s_{i+1}$。

于是设 $f_i$ 为当前选中最后一道题的状态为 $i$ 的方案数。那么转移时，我们首先要找到上一道题的状态 $j$，且这个 $j$ 一定满足 $j\subseteq i$。注意若 $j=i$，则一定有一种方案，这里需要预先加上 $1$。综上，统计：
$$
v=1+\sum_{j\subsetneq i}f_j
$$
这就是能选的状态集合。至于当前 $i$ 有多少种排列方式，这也是好计算的。相当于从 $c_i$ 个中挑选任意个（不为 $0$）并任意排列，统计公式为：
$$
s=\sum_{k=1}^{c_i}(c_i)^{\underline k}=\sum_{k=0}^{c_i-1}\frac{c_i!}{k!}
$$
最后的 $f_i=vs$。

这个方法的复杂度是 $O(3^m)$ 的，瓶颈在于遍历子集。

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll=long long;
constexpr int MAXN=1e5+5,MAXM=1<<20,MOD=1e9+7;
int n,m,num[MAXN],c[MAXM],f[MAXN],ans;
int fac[MAXN],inv[MAXN];
int g[MAXM][21];
string s;
void add(int&x,int y){
	x=x+y>=MOD?x+y-MOD:x+y;
}
int power(ll a,int b){
	ll res=1;
	for(;b;a=a*a%MOD,b>>=1)if(b&1)res=res*a%MOD;
	return res;
}
void init(){
	fac[0]=1;
	for(int i=1;i<=n;++i) fac[i]=(ll)fac[i-1]*i%MOD;
	inv[n]=power(fac[n],MOD-2);
	for(int i=n-1;~i;--i) inv[i]=(ll)inv[i+1]*(i+1)%MOD; 
}
int calc(int ci){
	int res=0;
	for(int i=0;i<ci;++i)
		add(res,(ll)fac[ci]*inv[i]%MOD);
	return res;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	init();
	for(int i=1;i<=m;++i){
		cin>>s;
		for(int j=0;j<n;++j)
			if(s[j]=='H')
				num[j+1]|=1<<(i-1);
	}
	for(int i=1;i<=n;++i) ++c[num[i]];
	f[0]=calc(c[0]);
	for(int i=1;i<=m;++i) g[0][i]=f[0];
	ans=f[0];
	for(int i=1,B=1<<m,v;i<B;++i){
		v=1;
		for(int j=1;j<=m;++j)
			if(i&(1<<(j-1)))
				add(v,g[i^(1<<(j-1))][j]);
		f[i]=(ll)v*calc(c[i])%MOD;
		add(ans,f[i]);
		g[i][1]=f[i];
		for(int j=1;j<m;++j){
			g[i][j+1]=g[i][j];
			if(i&(1<<(j-1))) add(g[i][j+1],g[i^(1<<(j-1))][j]);
		}
	}
	cout<<ans<<'\n';
	return 0;
}
```

考虑满分做法。引入辅助数组 $g_{i,j}$ 表示：找到所有的 $f_k$ 并求和，这些 $k$ 满足 $k\subseteq i$ 且对 $k$ 和 $i$ 有不同意见的编号最大的验题人的编号为 $j-1$（$j=0$ 时即为没有区别），公式表示下来就是：
$$
g_{i,j}=\sum_{\substack{k\subseteq i\\[0.5ex]\max x\in\complement_ik=j-1}}f_k
$$
所以原本的 $O(3^m)$ 枚举子集的转移就被优化为了 $O(m2^m)$ 转移，因为对于 $f_i$ 的转移我们只需要枚举有不同意见的编号最大的验题人的编号就行了。

当然对于 $g_{i,j}$ 的转移也有，首先 $g_{i,0}=f_i$，然后：

- 若 $i$ 的 $j-1$ 位为 $\tt0$，则 $g_{i,j}=g_{i,j-1}$；
- 否则 $g_{i,j}=g_{i,j-1}+g_{i\setminus\{\max x\in i\},j-1}$，其中 $i\setminus\{\max x\in i\}$ 意思是 $i$ 去掉最大的元素后组成的集合。

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll=long long;
constexpr int MAXN=1e5+5,MAXM=1<<20,MOD=1e9+7;
int n,m,num[MAXN],c[MAXM],f[MAXN],ans;
int fac[MAXN],inv[MAXN];
int g[MAXM][21];
string s;
void add(int&x,int y){
	x=x+y>=MOD?x+y-MOD:x+y;
}
int power(ll a,int b){
	ll res=1;
	for(;b;a=a*a%MOD,b>>=1)if(b&1)res=res*a%MOD;
	return res;
}
void init(){
	fac[0]=1;
	for(int i=1;i<=n;++i) fac[i]=(ll)fac[i-1]*i%MOD;
	inv[n]=power(fac[n],MOD-2);
	for(int i=n-1;~i;--i) inv[i]=(ll)inv[i+1]*(i+1)%MOD; 
}
int calc(int ci){
	int res=0;
	for(int i=0;i<ci;++i)
		add(res,(ll)fac[ci]*inv[i]%MOD);
	return res;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	init();
	for(int i=1;i<=m;++i){
		cin>>s;
		for(int j=0;j<n;++j)
			if(s[j]=='H')
				num[j+1]|=1<<(i-1);
	}
	for(int i=1;i<=n;++i) ++c[num[i]];
	f[0]=calc(c[0]);
	for(int i=1;i<=m;++i) g[0][i]=f[0];
	ans=f[0];
	for(int i=1,B=1<<m,v;i<B;++i){
		v=1;
		for(int j=1;j<=m;++j)
			if(i&(1<<(j-1)))
				add(v,g[i^(1<<(j-1))][j]);
		f[i]=(ll)v*calc(c[i])%MOD;
		add(ans,f[i]);
		g[i][1]=f[i];
		for(int j=1;j<m;++j){
			g[i][j+1]=g[i][j];
			if(i&(1<<(j-1))) add(g[i][j+1],g[i^(1<<(j-1))][j]);
		}
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：DeepSeaSpray (赞：0)

把每道题的 `H` 当作一个集合，那么合法的选定题目的顺序要求前面的题目是后面的题目的子集。

考虑动态规划，设 $f(S)$ 表示最后选定的题目集合是 $S$。

设一种题目集合的数量是 $c(S)$，计算一个 $w(S) = \sum_{i=1}^{c(S)} \operatorname{A}_{c(S)}^i$，表示至少选择一个此类题目的方案数。

那么有转移方程：

$$
f(S) = w(S) (1 + \sum_{T \subseteq S} f(T))
$$

这样做时间复杂度是 $O(3^m)$ 的。

我们考虑类似于高维前缀和的优化，但是直接修改是会超时的。

我们考虑一个折中的办法，设 $g(S,T)$ 表示前 $10$ 位集合为 $S$，后 $10$ 位集合为 $T$ 的子集的 $f$ 值之和。

查询 $(S,T)$ 的时候遍历 $S$ 的子集 $P$，对 $g(P,T)$ 求和。

修改 $(S,T)$ 的时候遍历 $T \subseteq P$，修改 $g(S,P)$。

那么我们可以在 $O(2^{10})$ 的时间复杂度内完成修改与查询。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5;
const int maxm=1<<20;
const int maxs=1<<10;
const int mod=1e9+7;
int n,m;
int a[maxn+5];
int c[maxm+5];
int w[maxm+5];
int f[maxm+5];
int g[maxs+5][maxs+5];
int fac[maxn+5],inv[maxn+5];
int ans;
inline int Get(){
    char ch=getchar();
    while(!(ch=='E'||ch=='H')) ch=getchar();
    return ch=='H';
}
inline int Fpow(int x,int y){
    int res=1;
    for(;y;x=1ll*x*x%mod,y>>=1)
        if(y&1) res=1ll*res*x%mod;
    return res;
}
inline int A(int x,int y){
    return 1ll*fac[x]*inv[x-y]%mod;
}
inline void Init(){
    fac[0]=1;
    for(int i=1;i<=maxn;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[maxn]=Fpow(fac[maxn],mod-2);
    for(int i=maxn-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
signed main(){
    Init();
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
        for(int j=1;j<=n;j++)
            a[j]|=Get()<<i;
    for(int i=1;i<=n;i++) c[a[i]]++;
    for(int i=0;i<1<<m;i++)
        for(int j=1;j<=c[i];j++)
            w[i]=(w[i]+A(c[i],j))%mod;
    for(int i=0;i<1<<m;i++){
        if(!c[i]) continue;
        int A=i>>10,B=i&1023;
        int res=1;
        for(int j=0;j<1024;j++)
            if((j&A)==j) res=(res+g[j][B])%mod;
        f[i]=1ll*w[i]*res%mod;
        for(int j=0;j<1024;j++)
            if((j&B)==B) g[A][j]=(g[A][j]+f[i])%mod;
        ans=(ans+f[i])%mod;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：qczrz6v4nhp6u (赞：0)

### Solution

将 $\texttt E$ 看为 $0$，$\texttt H$ 看为 $1$，则每道题目对应一个二进制数，则一个长为 $m$ 序列 $p$ 合法当且仅当 $\forall 1\le i<m$，$p_i\operatorname{ or }p_{i+1}=p_{i+1}$。

考虑 DP。但这个转移是基于值域的，直接做不太好做。我们考虑将 $p_i$ 相等的缩成一段，再对这个段进行扩充。显然，对于每一个 $p_i=x$ 的段，扩充的方案数是 $val_x=\sum_{i=1}^{cnt_x}{cnt_x}^{\underline i}$，其中 $cnt_x$ 是原序列中 $x$ 出现的次数。

设 $f_i$ 为以 $i$ 为结尾的方案数。不难得到转移式：

$$f_i=val_i\times(1+\sum_{\substack{j\operatorname{ or }i=i\\j\ne i}}f_j)$$

转移里面那一坨是 FWT 状物，类似分治 NTT，我们考虑把 DP 搬到分治上做。

设 ${\rm solve}(l,r)$ 计算 $\forall i\in[l,r)$，只考虑 $[l,r)$ 内贡献的 $f_i$。换句话说，${\rm solve}(l,r)$ 执行完毕时有：

$$f_i=val_i\times(1+\sum\limits_{\substack{j\operatorname{ or }i=i\\j\ne i\\j\in[l,r)}}f_j)$$

设 $mid=\dfrac{l+r}{2}$。我们先计算 $\text{solve}(l,mid)$，再考虑 $[l,mid)$ 对 $[mid,r)$ 的贡献，再计算 $\text{solve}(mid,r)$。

$[l,mid)$ 对 $[mid,r)$ 的贡献显然可以 FWT 搞，于是这题可以在 $O(nm+m^22^m)$ 的时间内解决。

如果希望得到 $O(nm+m2^m)$ 的做法，只需要在分治过程中动态维护 FWT 数组即可。

闲话：所以分治 NTT 精细实现可以做到 $O(n\log n)$？有点牛逼。

### Code

给一下核心代码。

$O(nm+m^22^m)$ 的实现：

```cpp
ll f[N],g[N];
void fwt(ll *f,int n){
	for(int i=1;i<n;i<<=1)
		for(int j=0;j<n;j+=i<<1)
			for(int k=0;k<i;k++)
				f[i|j|k]=(f[i|j|k]+f[j|k])%mod;
}
void solve(int l,int r){
	if(r-l==1){
		f[l]=(f[l]+1)*val[l]%mod;
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid);
	copy(g,f+l,mid-l);
	fwt(g,mid-l);
	for(int i=mid;i<r;i++)
		f[i]=(f[i]+g[i-mid])%mod;
	solve(mid,r);
}
```

$O(nm+m2^m)$ 的实现：

```cpp
ll f[N],g[N];
void solve(int l,int r){
	if(r-l==1){
		f[l]=(f[l]+1)*val[l]%mod;
		g[l]=f[l];
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid);
	for(int i=mid;i<r;i++)f[i]=(f[i]+g[i-mid+l])%mod;
	solve(mid,r);
	for(int i=mid;i<r;i++)g[i]=(g[i]+g[i-mid+l])%mod;
}
```

---

## 作者：Graphcity (赞：0)

首先求出 $val_i=\sum_{j=1}^i\dbinom{i}{j}j!$ 表示有 $i$ 个相同元素，且至少需要选择其中一个时的选择及排列方案。

考虑动态规划。设 $f_i$ 为最后一道题目的难度集合为 $i$ 的方案数。转移则是枚举 $i$ 的子集 $j$，这样是 $O(3^m)$ 的，卡卡常可能能够通过本题。

显然要从子集枚举方面去着手优化。考虑从集合 $i$ 到集合 $i\cup \{s_1,s_2,\cdots s_k\}$ 的转化：假如我们每次从 $i$ 新加入一个元素，那么从 $i$ 到 $i\cup \{s_1,s_2,\cdots s_k\}$ 的方案数为 $k!$。

设 $f_{i,j}$ 表示当前到达集合 $i$，总共走了 $j$ 步的方案数。转移如下：

- 下一步走到的元素不选：$f_{i\cup \{x\},j+1}\gets f_{i,j}$。
- 下一步走到的元素至少得选一个：$f_{i\cup \{x\},0}\gets f_{i,j}\times \dfrac{1}{(j+1)!}\times val_{cnt_i+1}$。这里 $\dfrac{1}{(j+1)!}$ 的系数是由于 $(j+1)!$ 种本质相同的加入方式导致的。

时间复杂度 $O(m^22^m)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=(1<<20),Maxk=1e5,Mod=1e9+7;

inline int Pow(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1) res=1ll*res*x%Mod;
        x=1ll*x*x%Mod,y>>=1;
    }
    return res;
}

int n,m,lim,f[Maxn+5][20],cnt[Maxn+5];
int fac[Maxn+5],inv[Maxn+5],val[Maxn+5];
char s[25][Maxk+5];

int main()
{
    scanf("%d%d",&n,&m),fac[0]=inv[0]=1,lim=(1<<m)-1;
    For(i,1,Maxn) fac[i]=1ll*fac[i-1]*i%Mod;
    inv[Maxn]=Pow(fac[Maxn],Mod-2);
    Rof(i,Maxn-1,1) inv[i]=1ll*inv[i+1]*(i+1)%Mod;
    For(i,1,m) scanf("%s",s[i]+1);
    For(j,1,n) {int k=0; For(i,1,m) if(s[i][j]=='H') k|=(1<<i-1); cnt[k]++;}
    For(i,0,lim)
    {
        For(j,1,cnt[i]) val[i]=(val[i]+1ll*fac[cnt[i]]*inv[cnt[i]-j])%Mod;
        f[i][0]=1;
    }
    For(i,0,lim)
    {
        f[i][0]=1ll*f[i][0]*val[i]%Mod;
        For(j,0,m-1) if(!(i&(1<<j)))
        {
            int p=(i|(1<<j));
            For(k,0,m-1) if(f[i][k])
            {
                f[p][k+1]=(f[p][k+1]+f[i][k])%Mod;
                f[p][0]=(f[p][0]+1ll*f[i][k]*inv[k+1])%Mod;
            }
        }
    }
    int ans=0;
    For(i,0,lim) ans=(ans+f[i][0])%Mod;
    cout<<ans<<endl;
    return 0;
}
```



---

