# Reality Show

## 题目描述

A popular reality show is recruiting a new cast for the third season! $ n $ candidates numbered from $ 1 $ to $ n $ have been interviewed. The candidate $ i $ has aggressiveness level $ l_i $ , and recruiting this candidate will cost the show $ s_i $ roubles.

The show host reviewes applications of all candidates from $ i=1 $ to $ i=n $ by increasing of their indices, and for each of them she decides whether to recruit this candidate or not. If aggressiveness level of the candidate $ i $ is strictly higher than that of any already accepted candidates, then the candidate $ i $ will definitely be rejected. Otherwise the host may accept or reject this candidate at her own discretion. The host wants to choose the cast so that to maximize the total profit.

The show makes revenue as follows. For each aggressiveness level $ v $ a corresponding profitability value $ c_v $ is specified, which can be positive as well as negative. All recruited participants enter the stage one by one by increasing of their indices. When the participant $ i $ enters the stage, events proceed as follows:

- The show makes $ c_{l_i} $ roubles, where $ l_i $ is initial aggressiveness level of the participant $ i $ .
- If there are two participants with the same aggressiveness level on stage, they immediately start a fight. The outcome of this is:
  - the defeated participant is hospitalized and leaves the show.
  - aggressiveness level of the victorious participant is increased by one, and the show makes $ c_t $ roubles, where $ t $ is the new aggressiveness level.
- The fights continue until all participants on stage have distinct aggressiveness levels.

It is allowed to select an empty set of participants (to choose neither of the candidates).

The host wants to recruit the cast so that the total profit is maximized. The profit is calculated as the total revenue from the events on stage, less the total expenses to recruit all accepted participants (that is, their total $ s_i $ ). Help the host to make the show as profitable as possible.

## 说明/提示

In the first sample case it is optimal to recruit candidates $ 1, 2, 3, 5 $ . Then the show will pay $ 1 + 2 + 1 + 1 = 5 $ roubles for recruitment. The events on stage will proceed as follows:

- a participant with aggressiveness level $ 4 $ enters the stage, the show makes $ 4 $ roubles;
- a participant with aggressiveness level $ 3 $ enters the stage, the show makes $ 3 $ roubles;
- a participant with aggressiveness level $ 1 $ enters the stage, the show makes $ 1 $ rouble;
- a participant with aggressiveness level $ 1 $ enters the stage, the show makes $ 1 $ roubles, a fight starts. One of the participants leaves, the other one increases his aggressiveness level to $ 2 $ . The show will make extra $ 2 $ roubles for this.

Total revenue of the show will be $ 4 + 3 + 1 + 1 + 2=11 $ roubles, and the profit is $ 11 - 5 = 6 $ roubles.

In the second sample case it is impossible to recruit both candidates since the second one has higher aggressiveness, thus it is better to recruit the candidate $ 1 $ .

## 样例 #1

### 输入

```
5 4
4 3 1 2 1
1 2 1 2 1
1 2 3 4 5 6 7 8 9```

### 输出

```
6```

## 样例 #2

### 输入

```
2 2
1 2
0 0
2 1 -100 -100```

### 输出

```
2```

## 样例 #3

### 输入

```
5 4
4 3 2 1 1
0 2 6 7 4
12 12 12 6 -3 -5 3 10 -4```

### 输出

```
62```

# 题解

## 作者：良心WA题人 (赞：15)

# 原题链接

[洛谷的](https://www.luogu.com.cn/problem/CF1322D)

[CF的](http://codeforces.com/problemset/problem/1322/D)

[VJ的](https://vjudge.net/problem/CodeForces-1322D)

# 题目描述

有一堆选手，从左到右枚举每个人，当枚举到$i$时可以让他上场表演获得$c_{l_i}$的表演费，花费$s_i$。此时，如果场上有两个人$i$和$j$，使得$l_i==l_j$，那么他俩会打一架，一个人被打死，另一个人晋一级并再表演一次，收益自然也是$c_{l_i+1}$，没有花费。要求选出来的选手$l_i$不上升。

~~好像又啰嗦了~~

# 解题思路

先康康数据范围：

>The first line contains two integers $n$ and $m$ $( 1 \le n, m \le 2000)$

明示时间复杂度$\Theta(n(m+n))$啊（$m+n$的原因是因为本题晋级之后最多$m+n$个等级）。好的，这种复杂度一般都是$dp$，那么就努力往$dp$上思考。~~说实话这样就考虑到dp还是有亿点玄学的。~~ 现在来构造$dp$，执行以下五步：

第一步：分析状态所要装的值。因为本题求的是雇佣选手得到的最大收益，所以$f$数组要装最大值。

第二步：设计状态。这个题要的是选手不上升，那么可以设计状态$f_{i,j}$表示使用等级$i...n$的选手，第$i$个等级的选$j$个。因为这样在后面不方便计算，所以反着计算序列，把状态就可以改成用$1...i$的最大值。

第三步：状态转移方程设计。首先，可以有一种直接选择当前选手的策略，则$f_{i,j}=f_{i,j-1}-s_i+c_{l_i}$，其中$j$枚举的是当前等级的选手选的个数。其次，还可以选了这个选手晋级，则$f_{j+1,k\div2}=f_{j,k}+k\div2\times c_{j+1}$，其中$j$枚举的是升级之前的等级，$k$枚举的是升级之前使用的个数。

第四步：边界情况。最开始一个都没有选，所以只有每种等级的选手一个都不选是$0$，$f_{i,0}=0$，否则设为极小值。
第五步：考虑答案状态。不难想到晋级到$m+1$是显然不可能的，但是其实晋级到$m$就不可能了。则输出$f_{m,0}$即可。
# 丑陋代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=2004;
int l[NN],s[NN],c[NN*2],f[NN*2][NN];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	m=n+m;
	for(int i=n;i;i--)
		scanf("%d",&l[i]);
	for(int i=n;i;i--)
		scanf("%d",&s[i]);
	for(int i=1;i<=m;i++)
		scanf("%d",&c[i]);
	memset(f,0xaf,sizeof(f));
	for(int i=0;i<=m;i++)
		f[i][0]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=n;j;j--)
			f[l[i]][j]=max(f[l[i]][j],f[l[i]][j-1]+c[l[i]]-s[i]);
		for(int j=l[i];j<=m;j++)
			for(int k=0;k<=n>>j-l[i];k++)
				f[j+1][k/2]=max(f[j+1][k/2],f[j][k]+k/2*c[j+1]);
	}
	printf("%d",f[m][0]);
	return 0;
}
```

---

## 作者：鲤鱼江 (赞：4)

被教练搬到了模拟赛，写个题解庆祝一下。

题目要求我们找出一个非严格单调不增的子序列，可以发现正着是不好做的，因为这样的话，DP 得到的值可能和之前所有位置都挂钩，复杂度会很高，所以考虑倒序 DP，取消后效性。

设 $dp_{i,j}$ 表示合并之后序列有 $i$ 个 $j$。这个状态比较抽象，仔细解释一下：我们每一次转移时不把这些相同的数合并完，只合并一部分，然后剩下的一部分塞进 DP 状态里。换句话说，序列里的 $i$ 个 $j$ 可能有些是选的，有些是合并出来的，我们将其同等对待。如果无法理解，去看 Calc 函数部分。

然后讲一下转移，对于加上一个与上一位相同的值，闭着眼睛都能做。加上一个不同的值，就先将之前的的值合并到等于当前值或者合并完，很简单，也就是 Calc 函数。

然后分析一下时间复杂度，仔细分析一下发现在每一个点，有效状态数都只有 $O(n)$ 级别，总状态是 $O(n\times n)=O(n^2)$ 的。来具体分析一下：发现 $(\sum\limits_i  Cnt_i)=O(n)$ 所以有效位置只有 $O(n)$ 个，精细实现一下可做到 $O(n^2\log n)$ 但实际表现很优秀，只跑了 $77$ 毫秒。

在代码中使用了 set 来存后面出现了哪些数，多此一举了。

温馨提示：将一个数右移很多位（比如 $100$ 位）之后得到的可能不是零（二进制位移是循环的）。

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Fread {
	const int SIZE=1<<21;char buf[SIZE],*S,*T;
	inline char getchar() {if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}
}
namespace Fwrite {
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct POPOSSIBLE{~POPOSSIBLE(){flush();}}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();T f=1;
        	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}x=0;
        	while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}x*=f;
	        return *this;
    	}
	    Reader(){}
	}cin;
	struct Writer{
	    template<typename T>
	    Writer& operator << (T x) {
	        if(x==0){putchar('0');return *this;}
	        if(x<0){putchar('-');x=-x;}
	        static int sta[45];int top=0;
	        while(x){sta[++top]=x%10;x/=10;}
	        while(top){putchar(sta[top]+'0');--top;}
	        return *this;
    	}
    	Writer& operator << (char c) {putchar(c);return *this;}
    	Writer(){}
	}cout;
}
#define endl '\n'
#define cin Fastio :: cin
#define cout Fastio :: cout

const int N=5e3+10;
int dp[N][N],n,a[N],w[N<<1],c[N],m,ct[N],ans,cct;
set < int > s;

inline void Set(int i,int j,int k){dp[i][j]=max(k,dp[i][j]);ct[j]=max(ct[j],i);}
void Calc(int x,int y,int z,int c){while(y<z&&x){c+=w[y]*x;x>>=1;++y;}Set(x+1,z,c);}
int GetVal(int x,int y){int res=0;while(x){res+=w[y]*x;x>>=1;++y;}return res;}

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i) for(int j=0;j<=m;++j) dp[i][j]=-1e9;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i) cin>>c[i];
	for(int i=1;i<=n+m;++i) cin>>w[i];
	for(int i=n;i;--i){
		for(int k=(ct[a[i]]++);~k;--k){dp[k+1][a[i]]=max(dp[k+1][a[i]],dp[k][a[i]]-c[i]);}
		for(int j:s){if(j>=a[i]) break;for(int k=1;k<=ct[j];++k) Calc(k,j,a[i],dp[k][j]-c[i]);}
		s.insert(a[i]);
	}
	for(int j=1;j<=m;++j) for(int i=1;i<=ct[j];++i) ans=max(ans,dp[i][j]+GetVal(i,j));
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：tzc_wk (赞：4)

[Codeforces 题面传送门](https://codeforces.ml/contest/1322/problem/D) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1322D)

首先这个消消乐的顺着消的过程看起来有点难受，DP 起来有点困难。考虑对其进行一个转化：将所有出场的人按照攻击力从小到大合并，然后每次将两个攻击力为 $l$ 的合并为一个攻击力为 $l+1$ 的人，答案加上 $c_{l+1}$，如果发现攻击力为 $l$ 的人 $\le 1$ 那就继续合并攻击力为 $l+1$ 的人，不难发现这个过程与原题的过程等价。

接下来考虑如何 DP 求解原问题。我们将序列翻转，这样单调不减就可以转化为单调不升，方便我们的合并过程。设 $dp_{x,i,j}$ 表示当前考虑了前 $x$ 个人，合并到攻击力 $=i$ 的人，目前攻击力 $=i$ 的人有 $j$ 个，转移就新加入一个人时，令 $dp_{x,l_x,j+1}\leftarrow dp_{x-1,l_x,j}-s_x+c_{l_x}$，然后从 $l_x$ 开始往 $n$ 枚举更新合并的贡献即可，具体来说 $dp_{x,i+1,j/2}\leftarrow dp_{x,i,j}+\dfrac{j}{2}·c_{i+1}$。你可能会疑惑为什么不直接一次性合并完所有攻击力为 $i$ 的人直到不能合并为止，这是因为你有可能出现合并到一半又进来了新的人的情况，这种情况下就要一步步合并。$x$ 那一维可以去掉这样空间复杂度可以达到平方。直接转移单次复杂度是 $n^2$ 的，总复杂度 $n^3$，无法通过。不过注意到在合并的过程中，我们的 $j$ 只可能达到 $\dfrac{x}{2^{i-l_x}}$，因此 $j$ 的枚举只用枚举到 $\dfrac{x}{2^{i-l_x}}$ 即可，这样总复杂度就是平方。

```cpp
const int MAXN=2000;
int n,m,l[MAXN+5],s[MAXN+5],dp[MAXN*2+5][MAXN+5],c[MAXN*2+5];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&l[i]);
	for(int i=1;i<=n;i++) scanf("%d",&s[i]);
	for(int i=1;i<=n+m;i++) scanf("%d",&c[i]);
	memset(dp,192,sizeof(dp));
	for(int i=1;i<=n+m;i++) dp[i][0]=0;
	for(int i=n;i;i--){
		for(int j=n;j;j--) chkmax(dp[l[i]][j],dp[l[i]][j-1]+c[l[i]]-s[i]);
		for(int j=l[i];j<=n+m;j++) for(int k=0;k<=(n>>(j-l[i]));k++)
			chkmax(dp[j+1][k>>1],dp[j][k]+1ll*(k>>1)*c[j+1]);
	} printf("%d\n",dp[n+m][0]);
	return 0;
}
```



---

## 作者：约瑟夫用脑玩 (赞：3)

又看漏题面，人麻了。

首先人是从高往低丢进来的，可能有不同的人停在不同的层，感觉不舒服。

发现加入人的顺序与收益无关，也就是说你丢了两个 $l=1$ 和一个 $l=2$ 的，最后收益都是固定的，于是正着考虑和倒着考虑一样，于是我们倒着从低往高丢人。

我们一直想要解决的问题在于，可能有一些单着的人被遗留在了某一层而且还会对收益造成影响。

比如有三个或五个 $l=1$ 的人，最后肯定有一个人留在了 $l=1$，但如果再加入一个 $l=1$ 它们还会继续升。

于是我们不一次性就把人全部打架升级的结果处理出来，而是把人先停在这里，防止还有等级相同的人加进来打架。

由于已经倒着保证从低往高加入人了，于是当丢的人等级变高的同时我们就可以不管等级低的那些人了，因为没人和他们升级。

而对于更高层的人，我们只是把有多少人要打停了下来，继续打仍然可以处理出打到对应层剩下的人，于是我们在信息完全的情况下可以进行 DP。

直接设 $f_{i,j}$ 表示第 $i$ 层停了 $j$ 个人的最大收益减去代价，更低的层数因为不会丢人而忽略，更高层的贡献因为还没打上去故没有计算。

加人转移就是 $f_{i,j+1}\leftarrow f_{i,j}+s_x+c_{l_x}$ 代表在这一层加人。

由于下次加的人可能在更高层的人，于是我们要将人打上去的 DP 给转移过去。

即 $f_{i+1,\lfloor \frac j2\rfloor}\leftarrow f_{i,j}+\lfloor \frac j2\rfloor\times c_{j+1}$ 代表人往上打并加入贡献。

转移一轮发现第二维总共只用转移 $O(n)$ 个即可，因为每打一次剩的人减半。

每次 $O(n)$，总共 $O(n^2)$。

代码：

```
	int i,j,k,v,mx;
	n=read();m=read();
	for(i=1;i<=n;l[i++]=read());
	for(i=1;i<=n;s[i++]=read());
	for(i=1;i<=n+m;c[i++]=read())
	for(j=1;j<=n;j++)F[i][j]=INT_MIN>>1;
	for(i=n;i;i--)
	{
		v=l[i];for(j=n;j;j--)ckmx(F[v][j],F[v][j-1]+c[v]-s[i]);
		for(j=v;j<=n+m;j++)for(k=0,mx=((n-i+1)>>(j-v));k<=mx;k++)ckmx(F[j+1][k>>1],F[j][k]+(k>>1)*c[j+1]);
	}writenum(F[n+m][0],10);
```

---

## 作者：Fuyuki (赞：2)

将参赛者的序列翻转转化成选一个单调不降的子序列。

设 $f_{i,j}$ 表示有 $j$ 个攻击力为 $i$ 的选手的最大收益，转移为：

$$f_{i+1,j/2}\leftarrow_{max}f_{i,j}+\lfloor j/2\rfloor\times c_i$$

含义很显然，将攻击力提升的人的数量和代价一起算出来。

此时将序列翻转的好处也体现出来了，可以一边维护单调不降的限制一边维护选手的贡献。

现在加入一个攻击力为 $l_i$ 的选手，会对 $f_i$ 的前 $n$ 项产生影响，对 $f_{i+1}$ 的前 $\frac{n}{2}$ 项产生影响，...，可以发现最多只会影响 $O(n)$ 处的 $dp$ 值。

那么暴力修改就行了，复杂度为 $O(n^2)$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
const int N=4e3+2,K=2047,INF=0x3f3f3f3f;
int n,m,ans;
int d[N],s[N],c[N],t[N],f[N][N];
void cmax(int&x,int y){if(x-y>>31)x=y;}
int main(){
	scanf("%d%d",&n,&m),t[0]=n,m+=n;
	ROF(i,n,1)scanf("%d",d+i);
	ROF(i,n,1)scanf("%d",s+i);
	FOR(i,1,m)scanf("%d",c+i);
	FOR(i,0,m)FOR(j,1,n)f[i][j]=-INF;
	FOR(i,1,n)t[i]=t[i-1]>>1;
	FOR(i,1,n){
		int p=d[i];
		ROF(j,n,1)cmax(f[p][j],f[p][j-1]+c[p]-s[i]);
		FOR(j,p,m)FOR(k,0,t[j-p])cmax(f[j+1][k/2],f[j][k]+k/2*c[j+1]);
	}
	cout<<f[m][0];
	return 0;
}
```

---

## 作者：GreenDay (赞：1)

[题面](https://www.luogu.com.cn/problem/CF1322D)


### 简要做法

正着做不太科学，**但是倒着做就好多了!**

如果没有消消乐的规则，这就是个裸的lis问题。我们考虑在原先朴素的lis的DP上新增一维，来**确定消消乐的状态和数列的情况**。

我们记录$dp_{i,j}$表明：最后一个选的选手，他的初始攻击力是$i$，当前攻击力为$i,i+1......i+ \left\lfloor\log_2n\right\rfloor$选手的数量。（状压DP）。

第二维度这么设置的原因？对于初始攻击力最大为$i$的选手序列，我们考虑~~快乐消消乐~~。

- 1个选手：$i$

- 2个选手：$i+1$

- 3个选手：$i,i+1$

- 4个选手：$i+2$

- 5个选手: $i,i+2$

---

我们发现，原序列攻击力最大为$i$，那么在合并次数最大的情况下，最终选手的攻击力会是$i+\left\lfloor\log_2n\right\rfloor$，而且在这个范围内，每种攻击力的选手数量$<2$。（倒着DP会有后效性，所以初始的时候数组要反过来）。

状压DP。选攻击力为i的选手时，我们就从$dp_j,j\le i$向$dp_i$转移，第二维状态可以枚举一维，计算一维。

等等，这复杂度是$O(n^3)$的？

有个朴素的优化，即如果当前选手的攻击力为$i$,对于$j< i-\left\lfloor\log_2n\right\rfloor$我们的转移仅仅是$\max(dp_i) \rightarrow dp_{j,1}$，维护$\max(dp_i)$，复杂度为$O(n^2\log n)$。事实上，我们还可以通过特殊的前缀和操作让复杂度降低为$O(n^2)$。(维护二进制不同位数末尾相同的$\max$,用给最高位的下一位“盖帽子”的方法确定维护的位数，这个语言描述不太清楚，我语文差qwq)

看代码：

```cpp
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const int N = 2048;
int n , m , log2n , t , ans , l[N] , s[N] , c[N];
int dp[N][N] , mxv[N][N * 2];

void update(int *num , int *val) {
    for(int i = 0 ; i < t ; ++i) val[i | t] = num[i];
    for(int i = t - 1 ; i ; --i) val[i] = max(val[i << 1] , val[i << 1 | 1]);
}
int calc(int p , int mask)
{
    int ans = c[p];
    while(mask & 1) ans += c[++p] , mask >>= 1;
    return ans;
}

template<typename _T>
inline void chkmax(_T &x , _T y) {if(x < y) x = y;}

int main()
{
    cin >> n >> m;
    log2n = log2(n) , t = 1 << (log2n + 1);
    for(int i = n ; i ; i--) cin >> l[i];
    for(int i = n ; i ; i--) cin >> s[i];
    for(int i = 1 ; i <= m + log2n ; ++i) cin >> c[i];
    memset(dp , 0xc0 , sizeof(dp)) , dp[0][1] = 0;
    for(int i = 0 ; i <= m ; ++i) update(dp[i] , mxv[i]);
    for(int i = 1 ; i <= n ; ++i)
    {
        int val = l[i] , w;
        for(int j = val ; j >= 0 ; --j)
        {
            w = max(log2n + 1 - val + j , 0);
            for(int k = 0 ; k < (1 << w) ; ++k)
                chkmax(dp[val][k + 1] , mxv[j][k | (1 << w)] + calc(val , k) - s[i]);
        }
        update(dp[val] , mxv[val]);
    }
    for(int i = 0 ; i <= m ; ++i) ans = max(ans , mxv[i][1]);
    cout << ans << endl;
}
```

---

## 作者：xfrvq (赞：0)

直接做需要 $O(n)$ vis 数组的，空间 $2^n$，具体状态是 $f_{i,S}$ 表示前 $i$ 个人中选第 $i$ 个人，$1\sim n+m$ vis 数组状压为 $S$。

但可以发现，倒过来从小到大加入人，产生的收益代价都一样。这时状态变为后缀，只需要记录 $i,\cdots,i+\log n$ 的 vis 数组，原因是 $n$ 个 $i$ 最多只能消到 $O(i+\log n)$。空间复杂度到了 $O(n^2)$，暴力转移时间仍是 $O(n^3)$。

考虑转移，设 $i,\cdots,i+\log n$ 的 vis 数组状压为 $S$，现在再加入一个 $i$。那么从 $i$ 开始一串 $1$ 会被消掉，取而代之是一个 $1$ 和一串 $0$。实际上就是 $S\gets S+1$。同时得到这一个区间的收益。

又可以发现，大部分位置只能贡献到 $f_{i,1}$。实际上只有 $a_j\in[a_i-\log n,a_i]$ 的 $j$ 能贡献到别的。我们不妨把 $a_i$ 而不是 $i$ 放入状态。

设 $f_{a_i,S}$ 代表当前后缀中，上个数取了 $a_i$，vis 状压为 $S$ 的答案。对 $j\in[a_i-\log n,a_i]$ 暴力转移 $f_{j,T}\to f_{a_i,S}$。对于别的 $j$，我们并不关心 $S$ 是什么，因此记录 $g_j=\max\{f_{j,S}\}$，转移 $g_j\to f_{a_i,1}$ 即可。

总复杂度 $O(n^2\log n)$，由于 $f_{i,S}$ 会转移到 $f_{i,T}$，不妨分层一下，避免死循环。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e3 + 50;

int n,m,a[N],w[N],c[N * 2],f[N][1 << 12],g[N],F[1 << 12],G;

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;++i) scanf("%d",a + i);
	for(int i = 1;i <= n;++i) scanf("%d",w + i);
	for(int i = 1;i <= n + m;++i) scanf("%d",c + i),c[i] += c[i - 1];
	memset(f,-0x3f,sizeof f),memset(g,-0x3f,sizeof g),f[0][0] = g[0] = 0;
	for(int i = n;i >= 1;--i){
		memcpy(F,f[a[i]],sizeof F),G = g[a[i]];
		for(int j = 0;j <= a[i];++j)
			if(a[i] - 11 > j) F[1] = max(F[1],g[j] - w[i] + c[a[i]] - c[a[i] - 1]);
			else for(int S = 0;S < (1 << 12);++S) if(f[j][S] >= -1e9){
				int T = S >> (a[i] - j);
				++T,F[T] = max(F[T],f[j][S] - w[i] + c[a[i] + __lg(T & -T)] - c[a[i] - 1]);
				G = max(G,F[T]);
			}
		G = max(G,F[1]);
		g[a[i]] = G,memcpy(f[a[i]],F,sizeof F);
	}
	printf("%d\n",*ranges::max_element(g));
	return 0;
}
```

---

## 作者：江户川·萝卜 (赞：0)

观察演出收益的计算方式，发现可看做对于一个二进制数进行加 $2^{l_i}$ 操作，并对每次进位计算额外贡献。从而可知上场顺序无关。

笔者将整个序列 **reverse** 了一下，即求**单调不降**的子序列的最大收益。

则有显然的 dp 状态，$dp_{i,msk}$ 表示考虑前 $i$ 个选手，其中第 $i$ 个必选，将整个二进制数 $l_i-1$ 位以下**截断**后得到 $msk$ 的最大收益。

> 由于我们钦定必选 $i$，则之后的 $l$ 都要 $\ge l_i$，因此 $l_i-1$ 位以下不必考虑。

直接转移是不行的，考虑优化。

实际上，对于 $msk>1$ 的状态，它要求在 $i$ 之前必须选择了一个 $j$ 使得 $l_i-l_j\le \log n$，否则有 $2^{l_i-\log n-\varepsilon}\times n<2^{l_i}$，无法进位上去。

所以可以在算出一个 dp 值后更新 $to_{x,msk}$ 表示对于 $l_i=x$ 的所有 $dp_{i,msk}$ 的可供转移值，具体实现看代码。

对于 $msk=1$ 的状态类似地做，对于前面 $l_j<l_i-\log n$ 的部分任意转移，$l_j\ge l_i-\log n$ 的部分类似预处理即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
constexpr int maxn=5e3+5;
int c[maxn],sc[maxn],s[maxn],a[maxn],dp[2005][2005],to[maxn][2005],mx[maxn],ans;
constexpr int B=12;
inline void upd(int x,int y,int z){
	mx[x]=max(mx[x],z);ans=max(ans,z);
	for(int i=1;i<=B;i++){
		to[x][y]=max(to[x][y],z);
		x++;y>>=1;
	}
}
int main(){
	std::ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;for(int i=n;i>=1;i--) cin>>a[i];
	memset(to,-0x3f,sizeof to);memset(mx,-0x3f,sizeof mx);
	for(int i=n;i>=1;i--) cin>>s[i];
	for(int i=1;i<=n+m;i++) cin>>c[i],sc[i]=sc[i-1]+c[i];
	for(int i=1;i<=n;i++){
		int w=0;
		for(int j=1;j<=a[i]-B;j++) w=max(w,mx[j]);
		dp[i][1]=max(w,to[a[i]][0])-s[i]+c[a[i]];
		for(int j=2;j<=i;j++){
			int z=__builtin_ctz(j);
			dp[i][j]=to[a[i]][j-1]+sc[a[i]+z]-sc[a[i]-1]-s[i];
		}
		for(int j=1;j<=i;j++) upd(a[i],j,dp[i][j]);
	}
	cout<<ans<<'\n';
}
```

---

## 作者：intel_core (赞：0)

注意到整个过程相当于模拟了二进制带进位加法，正着算比较蛋疼，因此考虑倒过来。

倒过来的好处是之前统计过的数只需要保留最高位的那几个就可以了，因此设 $f_{i,j}$ 表示钦定选的最后一个数是 $i$，从第 $a_i$ 位开始的二进制数是 $j$ 的最大收益。

注意到每次 DP 转移的时候，$j$ 这一维最多加一，因此 $j$ 的范围就是 $O(n)$ 的。

令 $g_{i,j}$ 表示下一个转移到第 $i$ 位，从第 $i$ 位开始形成的二进制数是 $j$ 的状态的最大收益。

每次转移，先用 $g_{a_i}$ 更新 $f_i$，再用 $f_i$ 更新 $g$ 即可。

复杂度 $O(n^2\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=5e3+10;
int n,m,a[NR],w[NR],val[NR],sum[NR];
int f[NR][NR],g[NR][NR],lg[NR];
void chkmax(int &x,int y){x=(x>y)?x:y;}
int lowbit(int x){
	return x&(-x);
}

int main(){
	cin>>n>>m;
	for(int i=0;i<=12;i++)lg[1<<i]=i;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>val[i];
	for(int i=1;i<=n+m;i++)cin>>w[i],sum[i]=sum[i-1]+w[i];
	for(int i=1;i<=n;i++)val[i]=w[a[i]]-val[i];
	memset(g,-999999,sizeof(g));
	for(int i=1;i<=5000;i++)g[i][0]=0;
	int ans=0;
	for(int i=n;i>=1;i--){
		int maxv=0;
		for(int j=0;j<=n;j++){
			int tmp=lg[lowbit(j^8191)]+a[i];
			f[i][j+1]=g[a[i]][j]+val[i]+sum[tmp]-sum[a[i]];
			chkmax(ans,f[i][j+1]);chkmax(maxv,f[i][j+1]);
		}
		for(int j=0;j<=12;j++)
			for(int k=0;k<=n;k++)chkmax(g[a[i]+j][k>>j],f[i][k]);
		for(int j=a[i]+13;j<=5000;j++)chkmax(g[j][0],maxv);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

