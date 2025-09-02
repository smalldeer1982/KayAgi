# Bingo

## 题目描述

Getting ready for VK Fest 2021, you prepared a table with $ n $ rows and $ n $ columns, and filled each cell of this table with some event related with the festival that could either happen or not: for example, whether you will win a prize on the festival, or whether it will rain.

Forecasting algorithms used in VK have already estimated the probability for each event to happen. Event in row $ i $ and column $ j $ will happen with probability $ a_{i, j} \cdot 10^{-4} $ . All of the events are mutually independent.

Let's call the table winning if there exists a line such that all $ n $ events on it happen. The line could be any horizontal line (cells $ (i, 1), (i, 2), \ldots, (i, n) $ for some $ i $ ), any vertical line (cells $ (1, j), (2, j), \ldots, (n, j) $ for some $ j $ ), the main diagonal (cells $ (1, 1), (2, 2), \ldots, (n, n) $ ), or the antidiagonal (cells $ (1, n), (2, n - 1), \ldots, (n, 1) $ ).

Find the probability of your table to be winning, and output it modulo $ 31\,607 $ (see Output section).

## 说明/提示

In the first example, any two events form a line, and the table will be winning if any two events happen. The probability of this is $ \frac{11}{16} $ , and $ 5927 \cdot 16 \equiv 11 \pmod{31\,607} $ .

## 样例 #1

### 输入

```
2
5000 5000
5000 5000```

### 输出

```
5927```

## 样例 #2

### 输入

```
2
2500 6000
3000 4000```

### 输出

```
24812```

## 样例 #3

### 输入

```
3
1000 2000 3000
4000 5000 6000
7000 8000 9000```

### 输出

```
25267```

# 题解

## 作者：Cry_For_theMoon (赞：11)

[传送门](https://codeforces.com/contest/1530/problem/F)

比E好写一万倍

#### 分析：

把对角线看作两条特殊列。

因为 $n\le 21$ 所以首先考虑暴力枚举哪些行/列全为 $1$，发现这样的复杂度是 $O(2^{2n})$ 往上的。

方便起见，我们定义 $2n+2$ 条线，其中前 $n+2$ 条是列，最后 $n$ 条是行。定义 $A_i$ 代表第 $i$ 条线全为 $1$ 的集合。$|A_i|$ 是第 $i$ 条线全为 $1$ 的概率。而 $\overline{A_i}$ 是 $A_i$ 的补集，即这条线至少有一个 $0$ 的情况集合。

则我们最后要求的是：

$$|A_1\cup A_2\cup ... \cup A_{2n+2}|=|S|-|\overline{A_1} \cap ...\cap \overline{A_{2n+2}}|$$

因此考虑怎么计数每一条线都有至少一个 $0$ 的概率。

我们知道这个东西还是可以 $O(2^{2n})$ 暴力容斥算但显然违背了我们的目的。

非常妙的地方来了：我们先暴力 $O(2^{n+2})$ 枚举哪些列是全为 $1$ 的。这个东西可以按行转移。然后每一次按行转移的时候，我们只要让这一行不全都为 $1$。这样，$A_{n+3}\sim A_{2n+2}$ 就可以全部忽略因为 $n$ 个行永远没有机会全为 $1$。

发现我们还需要预处理一个 $g(i,mask)$ 表示第 $i$ 行所有 $mask$ 中的列的位置为 $1$ 的概率，注意到这个东西可以通过 $lowbit$ 快速转移。

总复杂度 $O(n2^{n+2})$。

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=21,mod=31607;
int power(int a,int n){
	if(!n)return 1;
	int tmp=power(a,n/2);tmp=tmp*tmp%mod;if(n&1)tmp=tmp*a%mod;return tmp;
}
int n,a[MAXN][MAXN],g[MAXN][1<<MAXN],f[1<<MAXN],inv,ret;
int pcnt[1<<MAXN];
int main(){
	cin>>n;
	inv=power(10000,mod-2);
	int lim=(1<<n);
	rep(i,1,lim-1)pcnt[i]=pcnt[i^lowbit(i)]+1; 
	rep(i,0,n-1){
		g[i][0]=1;
		rep(j,0,n-1){
			cin>>a[i][j];
			a[i][j]=a[i][j]*inv%mod;
			g[i][1<<j]=a[i][j];
		}
		rep(j,1,lim-1){
			g[i][j]=g[i][j^lowbit(j)]*g[i][lowbit(j)]%mod; 
		}
	}
	rep(flag,0,3){
		//容斥系数 
		rep(i,0,lim-1)if(odd((pcnt[flag]+pcnt[i])))f[i]=mod-1;else f[i]=1;
		rep(i,0,n-1){
			rep(j,0,lim-1){
				int state=j;
				if(flag&1)state|=(1<<i);
				if(flag&2)state|=(1<<(n-i-1));
				int val=(g[i][state]-g[i][lim-1]+mod)%mod;
				f[j]=f[j]*val%mod;
			}
		}
		rep(i,0,lim-1)ret=(ret+f[i])%mod;
	}
	printf("%d\n",(1-ret+mod)%mod);

	return 0;
}
```

---

## 作者：max67 (赞：6)

# 前言

本篇题解大多数内容来自 [CF 官方题解](https://codeforces.com/blog/entry/92951)，并添加了个人理解。（其实不加也没有关系，挺详细的）

# 正文

## 定义

我们让 $l_1 ..... l_n$ 表示 $n$ 行，$l_{n+1}......l_{2n}$ 表示 $n$ 列， $l_{2n+1}$ 和 $l_{2n+2}$ 表示两条对角线。我们统称他们为直线。

另外，我们令 $P(A)$ 表示直线 $A$ 被选择的概率，即直线 $A$ 所表示的行（假定为行）上的数全为 $1$ 的概率，令 $P(\overline{A})$ 表示 $A$ 的补集，即直线 $A$ 所表示的行上的数不全为 $1$ 的概率（也就是至少有一个 $0$）。一个显然的性质为：$P(A)+P(\overline A) = 1$。（集合 $+$ 他的补集 $=$ 全集）

## 题解

对于直接求至少有一行（/列/对角线）全为 $1$ 的概率的话挺好求的——直接运用容斥原理即可。但是这种思路很难优化——不能用 dp 来降低复杂度（原因看完后再思考）。所以我们考虑求他的补集，即求全部的行（/列/对角线）都至少存在一个 $0$ 的概率。化为公式即为：

$$
P(\overline{l_1} \cap \overline{l_2} \cap......\cap \overline{l_{2n+1}})
$$

我们发现这个东西很难办（暂时不考虑行与列之间的关系），我们想要把他转化的简单一些，即通过一些计算把 $\overline {l_1}$ 去掉。

首先，我们能知道以下几条公式：

**1.**

$$
P(A \cap B) = P(A|B)P(B)
$$

这条公式基于[条件概率](https://baike.baidu.com/item/%E6%9D%A1%E4%BB%B6%E6%A6%82%E7%8E%87/4475278?fr=aladdin)可得这是对的，即 $A$ 与 $B$ 同时发生的概率等同于 $A$ 在条件 $B$ 下发生的概率乘以 $B$ 发生的概率。（其中 $P(AB)$ 与 $P(A \cap B)$ 表示的意思等同）

**2.**

$$
P( \overline A \cap B) + P(A \cap B) = P(B)
$$

因为$P(\overline A \cap B)=P(\overline A|B)P(B)$，$P(A \cap B)=P(A|B)P(B)$，所以：

$$
P( \overline A \cap B) + P(A \cap B)= P(A|B)P(B)+P(\overline A|B)P(B)=P(B)
$$

依据[全概率公式](https://baike.baidu.com/item/%E5%85%A8%E6%A6%82%E7%8E%87%E5%85%AC%E5%BC%8F/9980676?fr=aladdin)可得这是对的。

然后根据上面的公式我们可以推出来下面的式子：

$$
P(l_1 \cap \overline {l_2} ..... \cap \overline {l_{2n+1}}) + P(\overline{l_1} \cap \overline{l_2} \cap......\cap \overline{l_{2n+1}}) = P(\overline {l_2} ..... \cap \overline {l_{2n+1}})
$$

$$
P(l_1 \cap \overline{l_2} ..... \cap \overline{l_{2n+1}})=P(\overline{l_2} ..... \cap \overline{l_{2n+1}}|l_1)P(L_1)
$$

然后根据上面两个式子结合可以得到下式：

$$
P(\overline{l_1} \cap \overline{l_2} \cap......\cap \overline{l_{2n+1}})=P(\overline l_2 \cap ...... \overline {l_{2n+1}})-P(\overline{l_2} \cap......\cap \overline{l_{2n+1}}|l_1)P(l_1)
$$

也就是说明我们求 $l_1......l_n$ 都满足条件（至少有一个为 $0$）转化为求 $l_2....l_n$ 都满足条件。

同理，上面的式子也可以用容斥原理来解释:

* 求 $l_1......l_{2n+1}$ 都满足条件的话，可以转化为 $l_2......l_{2n+1}$ 都满足条件的情况下 $l_1$ 满足条件的概率。直接算 $l_1$ 满足条件的概率的话不好算，我们转化为在全集（在 $l_2......l_{2n+1}$ 的情况下）减去不合法的情况（$l_1$ 不满足条件，即全为 $1$）。

（这样就没有那么绕了。）

为了求解上述问题，我们定义 $f(i,S)$ 表示 $P(\overline {l_i}......\overline {l_{2n+1}} |l_{s_1} \cap ...... l_{s_k})$，其中 $S= \{s_1,s_2......s_k\},S \in \{1,2,3......i-1\}$。也就是我们指定 $k$ 条直线满足全选 $1$ 的情况下从第 $i$ 条直线开始满足条件（至少有一个为 $0$）的概率。我们模仿上面的式子，有：

$$
f(i,S)=f(i+1,S) - f(i+1,S \cup \{i\})P(l_i|l_1 \cap ...... \cap l_k)
$$

这里特别说明一下 $P(l_i|l_1 \cap ...... \cap l_k)$ 怎么求。因为此时 $l_1 ...... l_k$ 都已存在（全为 $1$）。我们把 $l_i$ 这条直线上已经存在（也就是和 $l_1......l_k$ 相交的格子）去掉，剩下的所有格子（在 $l_1$ 上）的乘积。

考虑边界的情况，也就是 $f(2n+3,S)$，他的初值为 $1$。（因为他转移时充当的作用是全集，因为赋为 $1$）。

那么答案就是 $1-f(1,\{\})$。（全集就是随便选，概率为 $1$）。

但是，由于我们有 $2n+3$ 条直线，时间复杂度为 $\mathcal O(n2^{2n+3})$，时间复杂度严重超纲。

首先，因为我们是根据条件概率进行转化，我们可以用容斥原理代替其中一部分 dp。具体的，因为直线分成三类：行，列和对角线。而行与行之间互相不干扰，也就是说用行做条件是不能对另一些行产生影响的。因此，我们可以把他们分开考虑。（先不考虑对角线）

即我们暴力枚举行的情况，然后用 dp 计算固定的行所产生的列的影响，因为此时列加不加入条件都不会对后面的列造成影响，所以上面的式子：

$$
f(i,S)=f(i+1,S) - f(i+1,S \cup \{i\})P(l_i|l_1 \cap ...... \cap l_k)
$$

可以简化为：

$$
f(i,S)=f(i+1,S) - f(i+1,S)P(l_i|l_1 \cap ...... \cap l_k)
$$

然后列就可以做到 $\mathcal O(n)$ dp 了。

（注：此时上面的 dp 没有计算固定行全为 $1$ 的概率，但我们假装他算了）

然后我们再考虑行的贡献。因为此时 $f(n+2,S)$ 表示选择哪些行全为 $1$，其他行不考虑，列满足条件（不全为 $0$） 的概率。我们发现这个东西好像套不进上面的 dp 里。

但你会发现上面 $f$ 的定义和容斥原理的定义很像，因此可以用容斥原理计算。（全集 $-$ 至少有一行全为 $1$ $+$ 至少有两行全为 $1$ ......）

虽然上面的容斥看起来不是很对的样子（虽然和前面的 dp 差不多），加个括号就明显很多了：全集 $-$ （至少有一列全为 $1$ $-$ 至少有两列全为 $1$ $+$ 至少有三列全为 $1$ 的概率......）。

容易发现，括号里算的是至少有一条直线全为 $1$ 的数量，全集减去他恰好就是全部直线都满足条件（至少有一个为 $0$）的数量。所以说绕了一圈又绕回来了。

再来考虑对角线怎么计算，因为对角线只有两条，所以我们可以把对角线视为行来暴力做（虽然他对行也产生干扰，但这个干扰可以用容斥消去，那么只剩他对列的干扰，此时就无所谓了）。复杂度为 $\mathcal O(n^22^{n+2})$。

因为其中的一个 $\mathcal O(n)$ 的时间复杂度为枚举 $P(l_i|l_1 \cap ...... \cap l_k)$，大佬们可以用各种神仙方法优化（这里用预处理优化）成 $\mathcal O(1)$。


## 实现

上面式子：

$$
f(i,S)=f(i+1,S) - f(i,S)P(l_i|l_1 \cap ...... \cap l_k)
$$

优化后是这样：

$$
f(i,S)= (f(i+1,S) - f(i+1,S) \times mul[i][U \oplus S])\times mul[i][S]
$$

上面的 $mul[i][s]$ 表示第 $i$ 列，此时行选择的情况（全为 $1$ 的情况）为 $S$，这些行与第 $i$ 列的相交的格子的乘积。$U$ 表示全集，即 $U =\{1,2,3......n\}$，$\oplus$ 表示异或。

（注：此时上面的 dp 顺带计算固定行全为 $1$ 的概率，也就是那个 $mul[i][S]$）

然后代码中简写为 

$$
f(S)= ( 1- mul[i][U \oplus S])\times mul[i][S] \times f(S)
$$

代码~~贴贴~~：

```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
using namespace std;
const int N=22,mod=31607;

int n,ans;
int lg[1<<N];
int f[1<<N];
int a[N][N];
int mul[N][1<<N];
int inv100=3973; 
//10000 的逆元
signed main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            {scanf("%d",&a[i][j]);a[i][j]=1ll*a[i][j]*inv100%mod;}
    lg[1]=1;
    for(int i=2;i<=(1<<n);i++)lg[i]=lg[i>>1]+1;
    //lg[i] 表示二进制数为 i 的最高位为 1 的位是第几位
    for(int i=1;i<=n;i++)
    {
        mul[i][0]=1;
        for(int S=1;S<(1<<n);S++)
        {
            int j=lowbit(S);
            mul[i][S]=1ll*mul[i][S^j]*a[lg[j]][i]%mod;
            //预处理，从上一个与他只差一个 1 的位置继承
        }
    }
    for(int T=0;T<4;T++)
    {
        for(int S=0;S<(1<<n);S++)
            if((__builtin_popcount(S)+__builtin_popcount(T))&1)f[S]=1;else f[S]=-1;
            //预处理容斥系数，__builtin_popcount(S) 是用来计算 S 转化成二进制后 1 的数量
        for(int i=1;i<=n;i++)
            for(int S=0;S<1<<n;S++)
            {
                int s=S;
                if(T&1)s|=1<<(i-1);
                if(T&2)s|=1<<(n-i);
                //考虑将此时的对角线视为行加上贡献
                f[S]=1ll*f[S]*mul[i][s]%mod*(1-mul[i][((1<<n)-1)^s]+mod)%mod;
            }
        for(int S=0;S<(1<<n);S++)ans=(ans+f[S])%mod;
    }
    printf("%d\n",(ans+1)%mod);
    // 全集 - 补集
    return 0;
}
```

# 后记

我总算知道了为什么不直接算了，因为他那个 dp 要考虑集合和补集的关系，直接算你想不到的（应该吧，小声 bb）。


---

## 作者：ax_by_c (赞：5)

正难则反，考虑计算每条线都不全为一的概率 $P$

对角线很烦，考虑先 $2^2$ 容斥掉，直接把概率改为一即可

于是就有了一个暴力容斥的解法：钦定全为一的行列集合 $S$，则 $P=\sum_{S}(-1)^{\lvert S\rvert}\prod_{(i,j)\in S}p_{i,j}$，时间复杂度 $O(2^{2n}n^2)$

考虑将行分出来，设全为一的行集合为 $S_1$，全为一的列集合为 $S_2$，则 $P=\sum_{S_1}\sum_{S_2}(-1)^{\lvert S_1\rvert+\lvert S_2\rvert}\prod_{i\in S_1\lor j\in S_2}p_{i,j}$

$=\sum_{S_1}(-1)^{\lvert S_1\rvert}(\prod_{i\in S_1}p_{i,j})\sum_{S_2}(-1)^{\lvert S_2\rvert}\prod_{j\in S_2\land i\notin S_1}p_{i,j}$

设 $g_{j,S}=\prod_{i\notin S}p_{i,j},f_{S}=(-1)^{\lvert S\rvert}\prod_{i\in S}p_{i,j}$

$=\sum_{S_1}f_{S_1}\sum_{S_2}(-1)^{\lvert S_2\rvert}\prod_{j\in S_2}g_{j,S_1}$

设 $G_{j,S}=-g_{j,S}$

$=\sum_{S_1}f_{S_1}\sum_{S_2}\prod_{j\in S_2}G_{j,S_1}$

现在相当于有数列 $a$，要求所有集合的元素积的和，答案是 $\prod (a_i+1)$

$=\sum_{S_1}f_{S_1}\prod(G_{j,S_1}+1)$

时间复杂度 $O(n2^n)$
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
const int mod=31607;
const int INV10000=3973;
const int N=23;
const int S=1<<22;
int lb(int x){
	return x&(-x);
}
int n,p[N][N],mxst;
int pct[S],lg2[S];
int vis1[N],vis2[N];
int row[N];
int f[S],g[N][S];
int cal(){
	for(int i=1;i<=n;i++){
		row[i]=1;
		for(int j=1;j<=n;j++){
			row[i]=row[i]*p[i][j]%mod;
		}
	}
	f[0]=1;
	for(int i=1;i<=mxst;i++){
		f[i]=f[i^lb(i)]*row[lg2[lb(i)]]%mod;
	}
	for(int i=0;i<=mxst;i++){
		if(pct[i]%2==1){
			f[i]=mod-f[i];
		}
	}
	for(int j=1;j<=n;j++){
		g[j][mxst]=1;
		for(int s=mxst-1;s>=0;s--){
			g[j][s]=g[j][s|lb(~s)]*p[lg2[lb(~s)]][j]%mod;
		}
		for(int s=0;s<=mxst;s++){
			g[j][s]=mod-g[j][s];
		}
	}
	int res=0;
	for(int s=0;s<=mxst;s++){
		int mul=1;
		for(int j=1;j<=n;j++){
			mul=mul*(g[j][s]+1)%mod;
		}
		res=(res+f[s]*mul)%mod;
	}
	return res;
}
void main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&p[i][j]);
			p[i][j]=p[i][j]*INV10000%mod;
		}
	}
	mxst=(1<<n)-1;
	for(int i=1;i<=mxst;i++){
		pct[i]=pct[i>>1]+(i&1);
	}
	for(int i=1;i<=n;i++){
		lg2[1<<(i-1)]=i;
	}
	int P=0;
	for(int x=0;x<=1;x++){
		int mul=1;
		if(x){
			for(int i=1;i<=n;i++){
				mul=mul*p[i][i]%mod;
				vis1[i]=p[i][i];
				p[i][i]=1;
			}
		}
		for(int y=0;y<=1;y++){
			int muls=mul;
			if(y){
				for(int i=1;i<=n;i++){
					muls=muls*p[i][n-i+1]%mod;
					vis2[i]=p[i][n-i+1];
					p[i][n-i+1]=1;
				}
			}
			if(x^y){
				P=(P-muls*cal()%mod+mod)%mod;
			}
			else{
				P=(P+muls*cal()%mod)%mod;
			}
			if(y){
				for(int i=1;i<=n;i++){
					p[i][n-i+1]=vis2[i];
				}
			}
		}
		if(x){
			for(int i=1;i<=n;i++){
				p[i][i]=vis1[i];
			}
		}
	}
	printf("%d\n",(1-P+mod)%mod);
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：Drind (赞：4)

这道题的难点主要在于容斥原理的使用，以及行和列在最本质上的差别。

我们使用最朴素的容斥原理，是可以直接暴力计算的，但是复杂度是惊人的 $O(2^{2n+2})$，肯定不能接受。

因为我们要算至少有一行，或一列，或一个对角线全是 $1$ 的概率，我们可以先计算没有任何一个行/列/对角线是 $1$ 的概率（这个本质上就是每一个行/列/对角线都存在至少一个 $0$），然后最后用 $1$ 减去就得到我们的答案。

但是，我们并没有改变 $O(2^{2n+2})$ 的复杂度。所以我们剖析这个问题的本质，如果这题是 $2n+2$ 列，那显然没法再优化了，但是这题是 $n$ 行 $n$ 列，他们是交叉的，就给了我们乱搞的机会。

我们可以尝试着在保证 $n$ 行全部都不为 $1$ 的情况下，去计算 $n$ 列和两条对角线全部不为 $1$ 的概率，具体地我们可以使用状压 dp 加容斥，用 $1$ 减去每一列全是 $1$ 的概率，加上有两列全是 $1$ 的概率......以此类推。然后一行一行地转移，每次转移的时候减去一行全是 $1$ 的概率即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=21+10;
const int M=(1<<21)+10;
const int p=31607;
inline int _abs(int x){if(x>0) return x;return -x;}

int qpow(int a,int index){
	int ans=1;
	while(index){
		if(index&1) ans=ans*a%p;
		a=a*a%p; index>>=1;
	}
	return ans;
}

int lowbit(int x){
	return x&(-x);
}

int f[N][M];
int g[M],bt[M];
int a[N][N];

void fake_main(){
	int inv=qpow(10000,p-2);
	int n; cin>>n;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
		cin>>a[i][j];
		f[i][(1<<(j-1))]=(a[i][j]*inv)%p;
	}
	
	int m=(1<<n)-1;
	for(int i=1;i<=n;i++){//预处理一行 j 的位置全是 1 的概率，j 是状压那一维。
		f[i][0]=1;
		for(int j=1;j<=m;j++){
			f[i][j]=f[i][j-lowbit(j)]*f[i][lowbit(j)]%p;
		}
	}
	for(int j=1;j<=m;j++) bt[j]=bt[j-lowbit(j)]+1;//二进制位有几个 1，是为了后面容斥的
	int ans=0;
	for(int xros=0;xros<4;xros++){//枚举对角线是否全是 1
		for(int i=0;i<=m;i++){//乘上一个容斥系数
			if((bt[i]+bt[xros])&1) g[i]=p-1;
			else g[i]=1;
		}
		
		for(int i=1;i<=n;i++){
			for(int j=0;j<=m;j++){
				int cover=j;
				if(xros&1) cover|=(1<<(i-1));//加上两条对角线所在的行
				if(xros&2) cover|=(1<<(n-i));
				g[j]=g[j]*(f[i][cover]-f[i][m]+p)%p;//记得减去一行全是 1 的概率
			}
		}
		for(int j=0;j<=m;j++) ans=(ans+g[j])%p;
	}
	cout<<(p-ans+1)%p<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

---

## 作者：devout (赞：4)

考虑容斥算没有行/列/对角线全选的。

当然可以直接 $\mathcal O(2^{2n})$ 暴力容斥，但是这样复杂度升天。

我们枚举对角线选/不选，枚举每一行选/不选。

这样的话我们知道一些位置是必须选的，现在我们要考虑列的情况。

对于每一列，如果我们想选上这一列，需要的概率就是这一列目前没有被强制选的位置的概率乘起来，设其为 $p$。

考虑我们容斥的过程，如果我们接下来要强制选第 $j$ 列，我们需要额外的概率 $p_j$，同时根据容斥的性质，我们答案需要取反，相当于我们只需要乘上 $-p_j$ 就完成了选下一列的任务。

如果不选第 $j$ 列，直接乘 $1$。

所以对于一个确定的状态，答案就是 $\prod (1-p_i)$ 乘上把这些强制选的状态选上的概率。

这样我们就可以在 $\mathcal O(n2^n)$ 的时间里做出来了。

```cpp
#include <bits/stdc++.h>

using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

const int N=21;
const int inv=3973;
const int mod=31607;

typedef long long ll;
typedef double db;

# define chkmax(a,b) a=max(a,b)
# define chkmin(a,b) a=min(a,b)
# define PII pair<int,int>
# define mkp make_pair

template<typename T> void read(T &x){
    x=0;int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n;
int a[N][N];
int mul[N][1<<N];
int lg[1<<N];
int f[1<<N];
int ans;

int lowbit(int x){
    return x&-x;
}

int main()
{
    # ifdef hibike
    freopen("testdata.in","r",stdin);
    freopen("test1.out","w",stdout);
    # endif
    read(n);
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)read(a[i][j]),a[i][j]=1ll*a[i][j]*inv%mod;
    lg[1]=0;
    for(int i=2;i<1<<n;i++)lg[i]=lg[i>>1]+1;
    for(int i=0;i<n;i++){
        mul[i][0]=1;
        for(int S=1;S<1<<n;S++){
            int j=lowbit(S);
            mul[i][S]=mul[i][S^j]*a[lg[j]][i]%mod;
        }
    }
    int U=(1<<n)-1;
    for(int T=0;T<4;T++){
        for(int S=0;S<1<<n;S++)if((__builtin_popcount(S)+__builtin_popcount(T))&1)f[S]=-1;else f[S]=1;
        for(int i=0;i<n;i++)
            for(int S=0;S<1<<n;S++){
                int SS=S;
                if(T&1)SS|=1<<i;
                if(T>>1&1)SS|=1<<(n-i-1);
                f[S]=1ll*f[S]*mul[i][SS]%mod*(1-mul[i][U^SS]+mod)%mod;
            }
        for(int S=0;S<1<<n;S++)ans+=f[S],ans%=mod;
    }
    printf("%d\n",(1-ans+mod)%mod);
    return 0;
}
```

其实这题有一个更直观的 $\mathcal O(n^22^n)$ 的做法。

用 $f[i][S]$ 表示第 $i$ 行，前 $i$ 行都选了的列的集合为 $S$ 的方案数。

我们发现转移的时候实际上是一个 FWT-AND。

于是就可以 $\mathcal O(n^22^n)$ 了。

但是 $n=21$ 大概是跑不过去的。。。

我写了一个本地跑都要二十多秒就懒得卡了。。。

不过有卡常大神可以试着卡一卡（

[code](https://codeforces.com/contest/1530/submission/126815755)

---

## 作者：_zdc_ (赞：3)

存在全 $1$ 不好求，可以转化成对于每行、列和两条对角线，都存在至少一个 $0$。

对角线有 $0$ 可以容斥掉，现在要做的就是 有些位置强制为 $1$，往剩下格子里填 $0$ 使每行、列都有 $0$。

考虑 dp，$f_{i,S}$ 表示前 $i$ 行，包含 $0$ 的列的集合为 $S$ 概率。

不难得到转移：$f_{i,S}\times g_{i,T}\to f_{i+1,S\text{ or }T}$。其中 $g_{i,T}$ 表示第 $i$ 行，$0$ 集合为 $T$ 概率。

这个 dp 用 FWT 可以做到 $O(n^22^n)$。较难通过。

---

但是这个可以继续优化。

对 $A,B$ 或卷积有一个简单的描述方式：对 $A,B$ 做高维前缀和，对应点相乘，然后再差分回去。

$f$ 的前缀和和差分都只要做一次，复杂度瓶颈是对 $g_i$ 做高维前缀和。

$g_{i,S}=\prod\limits_{j\in S}(1-p_{i,j})\prod\limits_{j\notin S}p_{i,j}$

那么 $g_i$ 的高维前缀和 $sum_S$ 就是：

$
\begin{aligned}
sum_S&=\sum\limits_{T\subseteq S}g_{i,T}\\
&=\sum\limits_{T\subseteq S}\prod\limits_{j\in T}(1-p_{i,j})\prod\limits_{j\notin T}p_{i,j}\\
&=\prod\limits_{j=1}^np_{i,j}\sum\limits_{T\subseteq S}\prod\limits_{k\in T}\dfrac{1-p_{i,k}}{p_{i,k}}\\
&=\prod\limits_{j=1}^np_{i,j}\prod\limits_{k\in S}(\dfrac{1-p_{i,k}}{p_{i,k}}+1)\\
&=\prod\limits_{j=1}^np_{i,j}\prod\limits_{k\in S}\dfrac{1}{p_{i,k}}
\end{aligned}
$

注意因为每行要选至少一个，所以 $g_{i,0}=0$，需要减去上述枚举子集 $T$ 时 $T=0$ 的贡献。

于是 $sum_S$ 可以 $O(2^n)$ 递推求解，总时间复杂度 $O(n2^n)$。

```cpp
#include <bits/stdc++.h>
// #define int int64_t
#define ALL(x) begin(x), end(x)
#define All(x, l, r) &x[l], &x[(r) + 1]
using namespace std;
void file () {
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
}
using ui = unsigned int;
using ll = long long;
using ull = unsigned long long;
using db = long double;
using Li = __int128_t;
template <typename T> using vec = vector<T>;

const int mod = 31607;
void Add(int &x, int y) { if((x += y) >= mod) x -= mod; }
void Sub(int &x, int y) { if((x -= y) < 0) x += mod; }
int Sum(int x, int y) { return Add(x, y), x; } 
int Dif(int x, int y) { return Sub(x, y), x; }
int qpow(int x, int y) {
  int b = x, r = 1;
  for(; y; b = (ll)b * b % mod, y /= 2) if(y & 1) r = (ll)r * b % mod;
  return r;
}
int Inv(int x) { return qpow(x, mod - 2); }

int32_t main () {
//  file();
  ios::sync_with_stdio(0); cin.tie(0);
  const int inv10000 = Inv(10000);
  int n;
  cin >> n;
  vec<vec<int>> P(n, vec<int> (n)), iP(n, vec<int> (n));
  vec<int> Mul(n, 1);
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      cin >> P[i][j];
      P[i][j] = inv10000 * P[i][j] % mod;
      iP[i][j] = Inv(P[i][j]);
      Mul[i] = Mul[i] * P[i][j] % mod;
    }
  }
  
  vec<int> ban(n, 0);
  
  function <int()> solve = [&]() {
    vec<int> f(1 << n, 1), g(1 << n);
    for(int i = 0; i < n; i++) {
      fill(ALL(g), 0);
      g[0] = Mul[i];
      for(int S = 1; S < (1 << n); S++) {
        if(!(S & ban[i])) {
          int lb = __lg(S & -S);
          g[S] = g[S ^ (1 << lb)] * iP[i][lb] % mod;
        }
      }
      for(int S = 0; S < (1 << n); S++) {
        if(S & ban[i]) g[S] = g[S ^ (S & ban[i])];
      }
      for(int S = 0; S < (1 << n); S++) Sub(g[S], Mul[i]);
      for(int S = 0; S < (1 << n); S++) f[S] = g[S] * f[S] % mod;
    }
    for(int i = 0; i < n; i++) {
      for(int S = (1 << n) - 1; ~S; S--) {
        if((S >> i) & 1) Sub(f[S], f[S ^ (1 << i)]);
      }
    }
    return f.back();
  };
  
  int res = 0;
  Add(res, solve());
  for(int i = 0; i < n; i++) ban[i] |= (1 << i);
  Sub(res, solve());
  fill(ALL(ban), 0);
  for(int i = 0; i < n; i++) ban[n - i - 1] |= (1 << i);
  Sub(res, solve());
  for(int i = 0; i < n; i++) ban[i] |= (1 << i);
  Add(res, solve());
  cout << (mod + 1 - res) % mod << "\n";
  return 0;
}
```

---

## 作者：DeaphetS (赞：3)

题目链接：[F - Bingo](https://codeforces.com/contest/1530/problem/F)

题目大意：给定一个 $n\times n(n\le 21)$ 表格，表格中每个元素有 $p_{i,j}$ 的概率为 $1$，否则为 $0$。求至少有一行或一列或一条对角线全为 $1$ 的概率，其中对角线指两条主副对角线。

考虑一个 naive 的容斥想法，直接容斥有多少条（行/列/对角线）是不全为 $1$ 的，并进行计算。

此时发现不全为 $1$ 的计算很繁，于是考虑求原题的补集。即**求所有（行/列/对角线）均不全为 $1$（或者说均存在 $0$）的概率**，那么容斥之后则是求钦定某些（行/列/对角线）均全为 $1$ 的概率，这个概率可以非常直接地算出来：把所有被钦定为 $1$ 的位置对应的 $p_{i,j}$ 乘起来即可。

那么采用这种做法，复杂度则是 $O(n^22^{2n})$ 级别的，显然无法接受。

考虑一个神奇的想法，把容斥计算拆成两部分。假设我们已经钦定了有哪些列或对角线是全为 $1$ 的，观察下我们计算的是什么。

我们的式子本来是所有被钦定为 $1$ 的位置的 $p_{i,j}$ 之积，而现在在这一前提下，则变成我们要再次钦定有哪些行是全为 $1$ 的，并计算 **在第一轮钦定中变为 $1$ 的 $p_{i,j}$ 之积**乘上（枚举第二轮钦定哪些行全为 $1$，并计算容斥系数乘上**在第二轮钦定中新成为 $1$ 的 $p_{i,j}$ 之积**的和）。

而对于括号内的部分，对应式子的意义等同于求每一行均不全为 $1$ 的概率。这时我们发现，这里的每一行相互之间是独立的，所以每行的贡献可以分开算，最后再乘起来就好。

于是我们考虑对每一行预处理在钦定了些列或对角线为 $1$ 后，该行不全为 $1$ 的概率。注意到钦定某些位置为一相当于修改对应的 $p_{i,j}$ 使其变为 $1$。所以把对应行 $p_{i,j}$ 的乘积直接除掉对应列集合的乘积即可，这玩意可以直接利用 lowbit 转移 $O(2^n)$ 求出来，而对于对角线的部分直接枚举四种情况分别做就好。这样时间复杂度是 $O(n2^n)$ 的，足以通过此题。

在实现时，可以先 $2^2$ 枚举对角线的情况，再容斥列，这样实现起来会方便些。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define MOD 31607
#define N 21
int n,m,ans,a[N][N],b[N][N],f[N][1<<N],c[N],g[1<<N],k[1<<N],Lg[1<<N];
int lowbit(int x){return x&(-x);}
int sol()
{
	int res=0;
	for(int i=0;i<n;i++){
		f[i][0]=1;
		for(int j=1;j<=m;j++)
			f[i][j]=f[i][j^lowbit(j)]*b[i][Lg[lowbit(j)]]%MOD;
		for(int j=0;j<=m;j++)f[i][j]=(MOD+1-f[i][j])%MOD;
	}
	for(int j=0;j<=m;j++)
		for(int i=n-2;i>=0;i--)
			(f[i][j]*=f[i+1][j])%=MOD;
	for(int i=0;i<=m;i++)
		res=(res+f[0][m^i]*g[i]%MOD*k[i])%MOD;
	return res;
}
int pre(int o1,int o2)
{
	int K=1;
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
		b[i][j]=a[i][j];
	if(o1)for(int i=0;i<n;i++)(K*=b[i][i])%=MOD,b[i][i]=1;
	if(o2)for(int i=0;i<n;i++)(K*=b[i][n-i-1])%=MOD,b[i][n-i-1]=1;
	for(int i=0;i<n;i++)c[i]=1;
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
		c[j]=c[j]*b[i][j]%MOD;
	g[0]=1;
	for(int i=1;i<=m;i++)
		g[i]=g[i^lowbit(i)]*c[Lg[lowbit(i)]]%MOD;
	return K*sol()%MOD;
}
int main()
{
	k[0]=1;
	for(int i=0,o=1;i<N;i++,o<<=1)Lg[o]=i;
	for(int i=1;i<(1<<N);i++)k[i]=MOD-k[i^lowbit(i)];
	scanf("%d",&n),m=(1<<n)-1;
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++){ 
		scanf("%d",&a[i][j]);
		(a[i][j]*=3973)%=MOD;
	}
	for(int i=0;i<2;i++)
	for(int j=0;j<2;j++)
		ans=(ans+(i^j?MOD-1:1)*pre(i,j))%MOD;
	printf("%d\n",(MOD+1-ans)%MOD);
}
```

---

## 作者：Alex_Eon (赞：3)

## Change log

- 2023.12.18 修改杂题集链接，修改部分格式。

## 广告

### [$\color{blueviolet}\text{CF 杂题集（点我）}$](https://www.cnblogs.com/Eon-Sky/p/17763683.html)
### [$\color{red}\text{博客内食用效果更佳（点我）}$](https://www.luogu.com.cn/blog/Ksy/solution-cf1530f)

## 复杂度：$O(n2^n)$

特别的，本题带有 $4$ 倍常数，因为需要枚举对角线状态也就是增加了 $2^2$ 的常数。

## 完整思路

考虑反着做，将至少有一行或一列或一条对角线全为 $1$ 概率转换为所有行列对角线都至少有一个 $0$。

先不考虑行与对角线，只考虑满足所有列都至少有一个 $0$ 该怎么做，为了使得我们的不完全做法有扩展性，我们考虑使用容斥。

过程如下：

1. 加上**至少**有 $0$ 列全为 $1$ 的概率。（对于**至少**有 $x$ 列全为 $1$ 的概率，可以理解为我们选定 $x$ 列，使得其全为 $1$（概率相乘），其他列的 $0/1$ 情况我们不考虑（概率为 $1$）。而选定的 $x$ 列的所有情况概率要加和，比如我选定 $1$ 列，那么情况总数有 $n$ 种，这些情况的概率都要加和。）

2. 减去**至少**有 $2$ 列全为 $1$ 的概率。

3. 加上**至少**有 $3$ 列全为 $1$ 的概率。

4. 以此类推。

这样容斥并不难理解，我们需要求的是所有列至少有一个 $0$ 的情况，对于第一步加的概率显然是全情况的概率，我们减去其中有一列为 $1$ 的概率，但此时对于两行为 $1$ 的情况我们减了两遍。举个例子，对于 $1,2$ 号列全为 $1$ 的某种情况，我们选定 $1$ 号列时和选定 $2$ 好列时分别减去了一遍，所以要在接下来的运算中将其加回来，以此类推。

接下来考虑在这样计算列的贡献时计算行的贡献，首先每一行的贡献互不影响，考虑固定**选定的列**进行某一行的运算，我只要保证舍去行的全为 $1$ 的概率即可。我们设 $f_{i,j}$ 表示对于第 $i$ 行，选定 $j$ 状态列（$j$ 是一个状压状态，这里选定其中的列就相当于在第 $i$ 行中该位置一定为 $1$。），不考虑其他位置 $0/1$ 状态的概率。这个东西显然是可以预处理的。

于是就有第 $i$ 行在状态 $j$ 下的贡献概率 $g_{i, j} - g_{i, 2 ^ {n - 1}}$，其中我们减掉的是此行全为 $1$ 的状态，也就是上文说到舍去的部分

最后对角线与列的处理相同，枚举一下状态即可，使得一行与对角线交点的位置为 $1$ 即可。


## 参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned UN;
typedef double DB;
//--------------------//
const int N = 21 + 5, S = 2097151 + 5;
const int Mod = 31607;

int n, inv, a[N][N];

int f[N][S], lim, ans;

int qp(int x, int y) {
    int res = 1;
    while (y) {
        if (y & 1)
            res = res * x % Mod;
        x = x * x % Mod;
        y >>= 1;
    }
    return res;
}

int lobit(int x) {return x & -x;}
//--------------------//
int main() {
    inv = qp(10000, Mod - 2);
    scanf("%d", &n), lim = 1 << n;
    for (int i = 1; i <= n; i++) {
        f[i][0] = 1;
        for (int j = 1; j <= n; j++)
            scanf("%d", &a[i][j]), f[i][1 << (j - 1)] = a[i][j] * inv % Mod;
        for (int j = 1; j < lim; j++)
            f[i][j] = f[i][j ^ lobit(j)] * f[i][lobit(j)] % Mod; // 处理 f 数组
    }
    for (int dst = 0; dst < 4; dst++) { // 对角线状态
        for (int tem, st = 0; st < lim; st++) { // 列状态
            tem = (((__builtin_popcount(dst) + __builtin_popcount(st)) & 1) ? Mod - 1 : 1); // 容斥系数计算
            for (int tst, i = 1; i <= n; i++) {
                tst = (st | ((dst & 1) * (1 << (i - 1))) | (((dst >> 1) & 1) * (1 << (n - i)))); // 在已有列状态基础上，根据对角线状态推出此行的状态
                tem = tem * (f[i][tst] - f[i][lim - 1] + Mod) % Mod;
            }
            ans = (ans + tem) % Mod;
            // printf("%d\n", tem);
        }
    }
    printf("%d\n", (1 - ans + Mod) % Mod);
    return 0;
}
```

---

## 作者：pengyule (赞：1)

似乎在大家眼里是比较基础的容斥题诶（似乎确实是这样，但为什么我调了这么久……）

言归正传，我的做法好像跟题解区不是太一样，（大同小异），是这样的。

- 考虑两种情况：有一行全为 1，和没有任何一行全为 1。
- 对于第一种情况：暴力枚举全 1 行的 mask，并计算所有选定格子的概率乘积。
- 对于第二种情况：将对角线视为列；所以有 $n+2$ 列。Dfs 所有全 1 列的 mask，那么就有一些格子已经确定是 1 了；因此对于每一行 $i$ 我们能够计算那些未确定的 $(i,j)$ 的 $p_{i,j}$ 的乘积 $P_i$；计算 $(1-P_i)$ 的乘积应该是“当前 mask 的列集合全为 1，没有行全为 1”的可能性。形式化地说，当前 mask 的答案就是 $\prod_{i=1}^n(1-P_i)$。
- 接着第二种情况说，我们求的其实是保证“当前 mask 的列集合全为 1，至少有这些列全为 1，没有行全为 1”，所以其实重复了一些情况，因此需要容斥。这个就是普通的容斥了，没有什么要注意的。
- 由于我们是用 dfs 在枚举，而枚举过程中可以顺带维护各行的未确定的 $\prod p_{i,j}$，因此每次枚举 mask 结束后，只需要枚举行来计算，即复杂度 $O(2^n+2^{n+2}n)$。

[submission](https://codeforces.ml/problemset/submission/1530/145701213)

---

## 作者：Purslane (赞：0)

# Solution

考虑容斥。

直接枚举容斥的集合可以做到 $O(2^{2n+2})$，过不去。

枚举对角线和行是否在集合的情况，这时候有 $2^{n+2}$ 种：因此我们需要 $O(n)$ 计算列在 $2^n$ 种情况下所有概率之和。

把我们行和对角线已经钦定过的全部扣成 $1$。假设每列的概率之积为 $p_i$，不同列的情况下为 $(1-p_1)(1-p_2)\cdots(1-p_n)$。

直接算是 $O(2^{n+2}n^2)$，可以预处理做到 $O(2^{n+2}n)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=25,MOD=31607;
int n,ans,a[MAXN][MAXN],rev[(1<<21)+10],p[MAXN][MAXN],pre[MAXN][(1<<21)+10];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
int solve(void) {
	int ans=0;
	ffor(j,1,n) pre[j][0]=1;
	ffor(j,1,n) ffor(st,1,(1<<n)-1) pre[j][st]=pre[j][st^(st&-st)]*p[rev[st&-st]][j]%MOD;	
	ffor(st,0,(1<<n)-1) {
		int mul=(__builtin_popcountll(st)&1)?-1:1,psl=1;
		ffor(j,1,n) mul=mul*(1-pre[j][(1<<n)-1-st])%MOD,psl=psl*pre[j][st]%MOD;
		ans=(ans+mul*psl)%MOD;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) rev[1<<i-1]=i;
	ffor(i,1,n) ffor(j,1,n) cin>>a[i][j],a[i][j]=a[i][j]*qpow(10000,MOD-2)%MOD;
	ffor(op1,0,1) ffor(op2,0,1) {
		int mul=1;
		ffor(i,1,n) ffor(j,1,n) p[i][j]=a[i][j];
		if(op1) ffor(i,1,n) mul=mul*p[i][i]%MOD,p[i][i]=1;
		if(op2) ffor(i,1,n) mul=mul*p[i][n-i+1]%MOD,p[i][n-i+1]=1;
		ans=(ans+mul*solve()%MOD*((op1+op2)%2?-1:1));
	}
	cout<<((1-ans)%MOD+MOD)%MOD;
	return 0;
}
```

---

