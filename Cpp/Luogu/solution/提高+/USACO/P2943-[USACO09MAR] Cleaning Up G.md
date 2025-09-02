# [USACO09MAR] Cleaning Up G

## 题目描述

在过去的好日子里，农夫约翰只为他的 N (1 \leq N \leq 40000) 头优质奶牛提供一种单一类型的牛饲料。时光流逝，如今他为牛群提供总共 M (1 \leq M \leq N) 种不同类型的食物（方便地编号为 1 到 M）。

奶牛们很挑剔。奶牛 i 只有一个食物偏好 $P_i$ (1 \leq P_i \leq M)，并且只吃那种最喜欢的食物。

每天喂食时间，FJ 将谷仓改造成一个灯光优雅的自助餐厅。奶牛们按照之前提到的方便索引编号排队进入餐厅。

不幸的是，由于食物种类繁多，事后清理工作非常耗时。如果农夫约翰提供 K 种不同类型的食物，他需要花费 $K \times K$ 单位的时间来清理谷仓。

为了节省时间，FJ 将奶牛按连续的组来喂食。每组之后，他清理谷仓并为下一组准备食物（当然，他只准备给定组中的奶牛会吃的食物）。请确定 FJ 清理谷仓所需的最少总时间。每组由队列中下一个连续的奶牛组组成；每头奶牛只属于一个组；每组之后，包括最后一组，谷仓都必须清理。



## 说明/提示

有四种类型的食物和十三头奶牛排队。第一头奶牛喜欢类型 1，第二头喜欢类型 2，第三头喜欢类型 1，等等。

前四组每组包含一头奶牛。第五组包含两头喜欢食物 #2 的奶牛（需要一单位时间）。第六组包含喜欢食物 3、4、3、4、3 的奶牛（需要四单位时间清理）。最后两组每组包含一头奶牛。总时间是 11。
（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
13 4 
1 
2 
1 
3 
2 
2 
3 
4 
3 
4 
3 
1 
4 
```

### 输出

```
11 
```

# 题解

## 作者：墨尔 (赞：23)

首先看到题目，会想到f[i]=f[j]+t[i][k](j<i,t[i][j]为[i,j]区间不同食物个数)的n^2的dp方程，而n范围40000，显然超时，我们要换个思路。

仔细观察题目，发现如果把每个食物单独分段，得到时间为n，显然最少时间小于等于这个值，即每一个区间的不同食物个数最多为sqrt(n)

由此可以得到启发，设pos[j]表示区间中不同食物个数小于等于j的最远位置，即在[pos[j],i]中不同食物个数为j，由此dp方程为f[i]=min(f[pos[j]-1]+j\*j)，复杂度为O(n\*sqrt(n))

问题转化为如何快速求区间中不同食物个数以及pos[j]的转移。

设pre[i]表示上一个与在i位置的食物相同的食物位置，nex[i]表示下一个，last[i]表示种类为i的食物出现的最后一个位置，如果i点没有上一个则pre[i]=0，没有下一个则nex[i]=n+1，有些绕口，建议直接看下面这段代码体会：

```cpp
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&p[i]);
        pre[i]=last[p[i]];
        nex[last[p[i]]]=i;
        last[p[i]]=i;
        nex[i]=n+1;
    }
```
判断时，如果pre[i]<pos[j]，说明i这个点在[pos[j],i-1]中并没有出现过，设cnt[j]为pos[j]对应的出现次数，则cnt[j]++；当cnt[j]>j时，显然pos[j]应该右移，如果nex[pos[j]]<i，说明在pos[j]这个位置的食物在区间中出现了不止一次，则删除它后不同个数仍然不变，因此要不断右移，直到nex[pos[j]]>=i，此时删除它后不同个数减一

至此此题解决。

```cpp
#include<cstdio>
#include<cmath>
int min(int a,int b){return a<b?a:b;}
int n,m,pos[205],f[40005],p[40005],last[40005],pre[40005],nex[40005],cnt[205];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&p[i]);
        pre[i]=last[p[i]];
        nex[last[p[i]]]=i;
        last[p[i]]=i;
        f[i]=1e9;nex[i]=n+1;
    }
    int t=sqrt(n);for(int i=1;i<=t;i++)pos[i]=1;
    for(int i=1;i<=n;i++)
     for(int j=1;j<=t;j++)
     {
            if(pre[i]<pos[j])cnt[j]++; 
            if(cnt[j]>j)
            {
                cnt[j]--;
                while(nex[pos[j]]<i)pos[j]++;
                pos[j]++;
            }
            f[i]=min(f[pos[j]-1]+j*j,f[i]);
     }
    printf("%d\n",f[n]);
}
```

---

## 作者：AlanSP (赞：14)

### Description

> 给定一个长度为n的序列 $\{a_n\}$ ，设不同的个数为 $K$，定义每个段的代价为 $K^2$，求分段的方案，使得总代价最小。

---

### Solution

很妙的一个题。

直接做肯定是 $n^2$ 的，那么我们要想一些性质。

可以发现，最优解代价必定 $\le n$ 。

因为单独把每个元素作为一段的代价是 $n$ 。

那么这也就说明，**每一段的 $K$ 必定小于 $\sqrt n$ 。**

所以我们的 $f_i$ 必定从有小于 $\sqrt n$ 个数的段前转移。

如果我们找出了这 $\sqrt n$ 个位置，那么便完成了转移。

---

记 $pos_i$ 表示**段内有i个数的左端点位置**。

我们可以动态维护pos数组。

对每一个 $a_i$ ， 先判断它是不是新来的数值。

这个操作可以通过开 $\sqrt n$ 个桶来实现。

如果是，那么就看当前段的不同数字个数有没有超过枚举的 $j$ 。

若超过，证明我们的 $pos_i$ 需要右移，来减小数字的个数。

把 $pos_i$ 右移至正好 $j$ 个就可以了。（此时包括 $pos_i$ 这个位置）

之后可以转移：
$$
f_i=\min_{j=1}^{\sqrt n}(f_{posj-1}+j^2)
$$
注意只有当前段的个数正好为j才能转移。（小于j则需要再等等）

---

### Code

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=40009,B=202;
int n,m,buk[B][N],cnt[B],ans,f[N],a[N],pos[B];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	memset(f,0x3f3f,sizeof f);
	f[0]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<B;j++)
		{
			++buk[j][a[i]];
			if(buk[j][a[i]]==1)//说明此时是新加入的元素
			{
				++cnt[j];
				if(cnt[j]>j)
				{
					while(--buk[j][a[pos[j]]]!=0) ++pos[j];//直到消除了一种元素的种类
					++pos[j];
					cnt[j]=j;
				}
			}
			if(cnt[j]==j) f[i]=min(f[i],f[pos[j]-1]+j*j);//注意
		}
	}
	printf("%d",f[n]);
	return 0;
}
```



---

## 作者：z7z_Eta (赞：8)

#### 蒟蒻表示并没看懂 开一堆nxt-pos-pre-last 的题解，于是只能发挥⑨的智慧：

## 滑动窗口

其他题解讲的比较完全了，我们要做的就是维护：当前位置为 $i$ 时，有$\sqrt{n}$个左端点，使得对于第$j$个左端点$L_j$，$[\ L_j,i\ ]$中有$j$种食品。

则有dp方程 $f_i=\text{min}^{\sqrt{n}}_{j=1}\ \ f_{L_j-1}+j^2$

所以，滑动窗口内部是桶，每次加入$a_i$，如果桶内新增一种食品，且超过了$j$种，则将$L_j$右移，并且删除元素，直到有一种食品在桶中清除为0，则又回复成了$j$种。

*短代码福利：*

```cpp
// SeptEtavioxy
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<cmath>
#define re register
#define ll long long
#define il inline
#define rep(i,s,t) for(re int i=(s);i<=(t);i++)
using namespace std;

// c_ints
il int ci(){
	re char ch;int f=1;
	while(!isdigit(ch=getchar()))f= ch=='-'?-1:1 ;
	re int x= ch^'0';
	while(isdigit(ch=getchar()))x=(x*10)+(ch^'0');
	return f*x;
}

enum{N=40024,B=256};
int a[N];

// f是dp数组，l为滑动窗口左边界
// M滑动窗口内部桶，cnt为滑动窗口内食品数
int f[N],l[B];
int M[B][N],cnt[B];

int main(){
//	printf("%lld",sizeof(f)+sizeof(a)+sizeof(l)+sizeof(M)+sizeof(cnt));
//	空间 ：41306816 （41MB）
	
	int n= ci(); ci();
	int b= sqrt(n+0.5);
	rep(i,1,n) a[i]= ci();
	
//	dp初值 
	memset(f,0x3f,sizeof(int)*(n+1));
	f[0]= 0;
	
	rep(i,1,n){
		rep(j,1,b){
			
			//如果桶内新增一种食品 
			//且超过了窗口种数限制 
			//则将左端点右移 
			
			if( ++M[j][a[i]]==1 ){
				
				if( ++cnt[j]>j ){
					while( --M[j][a[++l[j]]]!=0 );
					cnt[j]--;
				}
			}
		}
		rep(j,1,b) f[i]= min(f[i],f[l[j]]+j*j);
	}
	
	printf("%d",f[n]);
	
	return 0;
}
```

---

## 作者：nalemy (赞：6)

喜提代码最短题解

首先观察性质，如果我们把每个人都分割开自成一段，那么整个序列的答案为 $n$。

如果一个划分方案中存在一段的颜色数大于 $\sqrt n$，那么这一段的答案贡献就已经大于 $n$ 了。

因此答案最小的划分中每一段的颜色数一定不超过 $\sqrt n$。

---

一个自然的想法是 DP。

设 $f_i$ 为 $[1,i]$ 这个前缀的答案。我们枚举最后的段的起始位置，得到

$$
f_i=\min_{j=0}^{i-1}\left\lbrace f_j+(i-j)^2\right\rbrace
$$

$O(n^2)$ 是过不了的，考虑到上述性质，我们考虑枚举最后段的颜色个数。

当然以 $i$ 为结尾的含有 $j$ 种食品的区间可能有多个，考虑到 $f$ 单调不减，而这个区间的贡献为 $j^2$ 不变，我们希望这个区间越长越好。

$$
f_i=\min_{j=1}^{\sqrt n}\left\lbrace f_{p_{i,j}}+j^2\right\rbrace
$$

其中我们定义 $p_{i,j}+1$ 为以 $i$ 为结尾，且含有 $j$ 种食品的区间中**最长的一个**的左端点位置。

如此 DP 的时间复杂度已优化到 $O(n\sqrt n)$。

---

下面是关于 $p_{i,j}$ 如何由 $p_{i-1,*}$ 求得。

核心问题在于快速判断 $p_{i-1,j}$ 所表示的区间中是否含有第 $a_i$ 种食品。

如果有，那么 $p_{i,j}=p_{i-1,j}$，否则 $p_{i,j}=p_{i-1,j-1}$。

进一步地我们考虑到一定存在一个分界点 $t$ 使得对于所有 $j\gt t$，区间 $(p_{i-1,j},i)$ 含有 $a_i$，其余的 $j\le t$ 都满足 $(p_{i-1,j},i)$ 所表示的区间不含有 $a_i$。

如何求得分界点 $t$ 呢？

我们发现区间 $(p_{i-1,t-1},i)$ 含有 $a_i$，而 $(p_{i-1,t},i)$ 不含有，而根据定义，前者字符集只比后者多 $1$，所以我们推断 $a_{p_{i-1,t}}$ 恰为 $a_i$。

由此我们可以 $O(\sqrt n)$ 地找出分界点 $t$，$O(n\sqrt n)$ 地递推数列 $p$。

---

代码：

```C++
#include<iostream>
#include<cstring>
#include<cmath>
const int N = 4e4+1, K = 2e2+1, I = (1u<<31)-1;
int a[N], f[N], p[K];
int main() {
    int n, m, k; std::cin >> n >> m, k = sqrt(n), memset(p, -1, sizeof p), *p = 0;
    for (int i=1, j; i<=n; i++) {
        for (std::cin>>a[i], j=0; j<=k && ~p[j] && a[p[j]]!=a[i]; j++);
        for (; j; j--) p[j] = p[j-1]; *p = i;
        for (f[i]=I, j=1; j<=k && ~p[j]; j++) f[i] = std::min(f[i], f[p[j]]+j*j);
    }
    return std::cout << f[n], 0;
}
```


---

## 作者：interestingLSY (赞：6)

先放一段 $BZOJ$ 的翻译,感觉更清楚:

> 有 $n$ 头奶牛，每头那牛都有一个标号 $P_i$ 。现在 $Farmer John$ 要把这些奶牛分成若干段，定义每段的不河蟹度为：若这段里有 $k$ 个不同的数，那不河蟹度为 $k^2$。总不河蟹度就是所有段的总和.求最小总不河蟹度.

emmmmmmm...... 您们的算法都好高深呀,我来个最弱的

### 一种概率算法

> 我不太清楚这是不是模拟退火..我太菜了... (逃

首先易发现,对于一段相同的连续的元素,她们一定会被放到一个区间中.所以我们可以先对输入的数组进行去重.

设 $dp_i$ 为将前 $i$ 个数放在几个区间中,且第 $i$ 个数为区间结尾的最小花费

则 $$dp_i = min\{dp_{j-1}+dif_{[i,j]}\}$$

也就是说,我们可以用 $dp_i$ 去转移所有 $dp_j\ (\ j \in (i,n]\ )$ 

( $dif_{[i,j]}$ 表示 $[i,j]$ 中不同元素个数 )

直接做会 $TLE$ 成 $70$ 分.

怎么办?

我们定义一个 $\color{Red}{\text{开心值}H}$ , 是一个 $[0,100]$ 的浮点数, 越高代表程序越开心.每次转移前都将 $H$ 设为 $100$.

当转移个五六千步时,如果当前状态太糟糕(不同元素太多了), $H$ 就会变小, 否则会变大(但变大的很小)

当我们的程序特别不开心(比如 $H<5$ 时) , 就会break掉,直接开始下一轮转移.

这能AC?

能.

代码很短:(这里只贴出关键部分)

需要开O2才能过,不开会90分 QAQ

但不得不说这是一种很好的骗分方法.



```cpp
	ld h;
    dp[0] = 0;
    For(i,n){
        int u = dp[i-1];
        int dif = 0;
        h = 100;
        Forx(j,i,n){
            int v = a[j];
            if(!have[v]){
                have[v] = 1;
                dif++;
            }
            Mymin(dp[j],Sqr(dif)+u);
			if( Sqr(dif)+u >= n ) break;
            if( j-i > 5000 ) h *= 1.005 - (ld)dif / (ld)(j-i+1);
            if( h < 4 ) break;
        }
        Forx(j,i,n)
            have[a[j]] = 0;
    }
```


---

## 作者：是个汉子 (赞：4)

[洛谷传送门](https://www.luogu.com.cn/problem/P2943)

### Solution

这种题~~很显然~~能想到用区间DP去做。

那么我们先列一个最朴素的方程： $f_{i}=\min(f_{i},f_{j}+s)$ ，其中 $s$ 是 $i$ ~ $j$ 的不同种类数。

这是 $O(n^2)$ 的显然不太可。

那有什么能优化的？

发现如果将每只奶牛单独作为一段的话，最后的答案是 $n$ 。

所以 $s$ 中的种类数应该小于 $\sqrt n$ ，不然代价就超过 $n$ 了。

我们拿一个数组 $pos$ ，表示段内有 $i$ 个数，其中右端点为当前点，左端点为 $pos_i$ ，那么现在的转移方程就是：
$$
f_{i=}\min_{j=1}^{\sqrt n}\{f_{pos_j-1}+j^2,f_{i}\}
$$
考虑如何维护 $pos$ ԅ(¯﹃¯ԅ)

可以拿 $\sqrt n$ 个桶，然后对当前位即 $P_i$ 进行判断，如果是新的值，加入桶，判断从 $pos_j$ 到 $i$ 是否是 $j$ 个数，要是大于，就及时往右移，直到满足条件。

### Code

```c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
const int N=4e4+10,B=210;
int n,m,a[B][N],cnt[B],ans,f[N],P[N],pos[B];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

int main(){
    n=read(); m=read();
    for(int i=1;i<=n;i++) P[i]=read();
    memset(f,0x3f3f,sizeof(f));
    f[0]=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<B;j++){
            ++a[j][P[i]];
            if(a[j][P[i]]==1){
                ++cnt[j];
                if(cnt[j]>j){
                    while(--a[j][P[pos[j]]]!=0) ++pos[j];
                    ++pos[j];
                    cnt[j]=j;
                }
            }
            if(cnt[j]==j) f[i]=min(f[i],f[pos[j]-1]+j*j);
        }
    printf("%d\n",f[n]);
    return 0;
}
```



---

## 作者：LawrenceSivan (赞：3)

# P2943 [USACO09MAR]Cleaning Up G

> 给定长度为 $n$ 序列，对其进行分段。
>
> 定义每一段的代价为每一段内不同数的个数的平方。
>
> 求最小总代价。
>
> $n\le 4\times 10^4$

挺神妙的。

考虑 DP。

首先可以想到 $\mathcal{O(n^3)}$ 的 DP。

设 $f_i$ 表示考虑到第 $i$ 位的最小代价。

枚举上一个位置 $j$ ，并且统计 $j$ 到 $i$ 之间的数的种类。

转移是 $f_i=\min\limits_{j<i} f_j+\text{cnt}(j+1,i)^2$。

一边扫描一边计算可以轻易做到 $\mathcal{O(n^2)}$。

不足以通过此题。

注意到如果将每一个数作为单独的一段，那么答案最大是 $n$ 。

于是可以发现，对于最优情况，一段内不同种类的数字一定小于等于 $\sqrt n$。

于是一段中种类数超过 $\sqrt n$ 的转移都是无效的。

可以只记录有效转移位置。

在过程中维护一个 $pos_j$ ，含义是满足 $[pos_j,i]$ 中恰好有 $j$ 种数的段的左端点位置。

考虑使用 $\sqrt n$ 个桶维护 $pos_j$。

每次加入一个数时检查 $a_i$ 是否已经在第 $j$ 个桶中出现。

如果没有出现那么说明这是一个新的数，那么此时段中的数一定超过了该桶的容量限制，于是我们需要调整 $pos_j$ 的位置满足这个段内恰好只有 $j$ 种不同的数字。

如果出现过，没有影响，直接转移。

时空复杂度均为 $\mathcal{O(n \sqrt n)}$ 。

```cpp
constexpr int maxn=4e4+5;
constexpr int maxB=205;

int n,m,B;

int a[maxn],pos[maxn];

int cnt[maxB][maxn];

int num[maxB];

int f[maxn];

inline void update(int block,int val){
    cnt[block][val]++;
    if(cnt[block][val]==1){
        num[block]++;
        while(num[block]>block){
            num[block]-=(--cnt[block][a[pos[block]]]==0);
            pos[block]++;
        }
    }
}

signed main() {
    read(n,m);B=sqrt(n);
    for(int i=1;i<=n;i++){
        read(a[i]);
        pos[i]=1;
    }

    for(int i=1;i<=n;i++){
        f[i]=i;
        for(int j=1;j<=B;j++){
            update(j,a[i]);
            f[i]=min(f[i],f[pos[j]-1]+j*j);
        }
    }

    write(f[n]),puts("");


    return 0;
}
```

 

---

## 作者：杨铠远 (赞：3)

# n方＋剪枝
# A了
具体剪枝见代码
# code:
```cpp
//Code by : Y-k-y
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <bitset>
#define int long long
const int N=40010;
using namespace std;
inline int rnd(){
	int res=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
	return res*f;
}
inline void wr(int x){
	if(x<0){putchar('-');x=-x;}if(x>9) wr(x/10);putchar(x%10+'0');
}
int a[N],k,f[N];
int n;
bitset<N>bi;
signed main(){
	cin>>n>>k;int num=0;
	for(int i=1;i<=n;i++)a[i]=rnd();
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int i=1;i<=n;i++){
		if(a[i]==a[i-1]){//如果和上一个数一样，就直接把值赋过来 
			f[i]=f[i-1];continue;
		}
		int num=0;bi.reset();//bitset优化 
		for(int j=i;j>0;j--){//倒着搞 
			if(!bi[a[j]]){//没有出现过 加加 
				bi[a[j]]=1;num++;
			}
			if(num*num>i)break;//剪枝，区间答案最大为区间长度 
			f[i]=min(f[i],f[j-1]+num*num);
		}
	}
	wr(f[n]);
	return 0;
}
```
拜拜

---

## 作者：joe19025 (赞：3)

## 核心思想
DP：设$f[i]$为从第一位到第$i$位需要的时间
## 暴力解法
$O(n^2)$做法很简单，对于每一位$i$,枚举它前面所有位，边扫边统计有多少个种类s，最后取个min即可。
$f[i]=min(f[i],f[j-1]+s)$
## 进阶做法
其实根本问题很简单：
- 如果每人作为一组那时间为n，所以时间上限为n。
- 我们发现一组内不能超过$sqrt(n)$种。不然代价就超过上限了。

所以我们可以换一种方式来维护，另外维护一个$pos[i]$代表从当前位向前，包含i种最远能到哪里。

于是式子变成这个了:
$f[i]=min(f[i],f[pos[j]-1]+j \times j)$

所以现在问题转化到如何维护$pos[i]$上了。

再建立下面几个变量
- $pre[i]$：第i位元素上一次出现的位置
- $nex[i]$：第i位元素下一次出现的位置
- $las[i]$：i元素上次出现的位置
- $cnt[i]$：当前位，$pos[i]$包含多少个元素

于是可以利用这4个变量相互维护。

而更新$pos[i]$的方法如下：
```cpp
for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=t;j++)
        {
            if(pre[i]<pos[j])cnt[j]++;
            if(cnt[j]>j)
            {
                cnt[j]--;
                while(nex[pos[j]]<i)pos[j]++;
                pos[j]++;
            }
            f[i]=min(f[i],f[pos[j]-1]+(j*j));
        }
    }
```
 因为$pos[j]$只增不减，且最多增加n次，所以均摊最坏复杂度$O(n\times sqrt(n))$
 
 ## Codes
 ```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#define MAXN 40005
using namespace std;

int f[MAXN];
int pre[MAXN];
int nex[MAXN];
int pos[MAXN];
int n,m;
int las[MAXN];
int a[MAXN];
int cnt[MAXN];

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        pre[i]=las[a[i]];
        nex[las[a[i]]]=i;
        las[a[i]]=i;
        f[i]=1e9,nex[i]=n+1;
    }
    int t = sqrt(n);
    for(int i=1;i<=n;i++)pos[i]=1;
    f[0]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=t;j++)
        {
            if(pre[i]<pos[j])cnt[j]++;
            if(cnt[j]>j)
            {
                cnt[j]--;
                while(nex[pos[j]]<i)pos[j]++;
                pos[j]++;
            }
            f[i]=min(f[i],f[pos[j]-1]+(j*j));
        }
    }
    printf("%d",f[n]);
    return 0;
}
```

---

## 作者：wzj423 (赞：2)

补充一些思路
```cpp
#include <bits/stdc++.h>
const int MAXN=80010;
using namespace std;
int N,M,a[MAXN];
/*
    1.易知答案的上限是N 每次都清理
	2.答案随N单调不减
    ->所以对于一段长度为x的区间,其颜色数量一定不超过sqrt(x) 否则一定更劣
    因而,我们只需找到最长的区间满足区间中颜色数量为j的进行转移,
    也就是对于选择的区间按照颜色数量分类,有sqrt(N)类,每种分类仅考虑一个转移,(因为2.)
    转移复杂度O(Nsqrt(N))
    现在考虑如何求出所需的区间,不妨令pos[j]为当前位置向前回溯满足颜色数量为j中的最大区间的左端点坐标
    转移时分别考虑每一个pos[j],那么因为每一个pos[j]都单调不降,所以对于每一个pos[j],均摊O(N),有sqrt(N)种,
    预处理O(Nsqrt(N))
    由于一开始只有一种颜色,所以不妨反向贪心,使得pos[j]的颜色<=j就可以了.
    因而总复杂度O(Nsqrt(N))
*/
int nxt[MAXN],pre[MAXN],but[MAXN];
int pos[MAXN],cnt[MAXN];
int f[MAXN],_UP;
int main() {
	scanf("%d%d",&N,&M);_UP=sqrt(N);
	for(int i=1;i<=N;++i) {
		scanf("%d",a+i);
        nxt[but[a[i]]]=i;
        pre[i]=but[a[i]];
        nxt[i]=80005;
        but[a[i]]=i;
	}
	memset(pos,-1,sizeof pos);memset(f,0x3f,sizeof f);
    for(int i=1;i<=_UP;++i) pos[i]=cnt[i]=1;
    f[1]=1;f[0]=0;
    for(int i=2;i<=N;++i) {
        for(int j=1;j<=_UP;++j) {
            if(pre[i]<pos[j]) ++cnt[j];
            if(cnt[j]>j) {
				--cnt[j];
                while(nxt[pos[j]]<=i) ++pos[j];
				++pos[j];
            }
        }
		for(int j=1;j<=_UP;++j) {
			if(pos[j]!=-1)
				f[i]=min(f[i],f[pos[j]-1]+j*j);
		}
    }
    printf("%d\n",f[N]);
	return 0;
}

```

---

## 作者：Luciylove (赞：1)

非常优秀的一个性质 ：

所有区间都不能有超过 $\sqrt n$ 个颜色， 否则会比以每个元素划分劣。

我们定义 $pos_{i, j}$ 表示 $[pos_{i,j}, i]$ 有 $j$ 个颜色， 然后考虑维护 

$$f_i = \underset{j\leq \sqrt n}\min\{f_{pos_{i,j}} + j ^ 2\}$$

这个方程。

咋维护 $pos_{i, j}$ 呢？ 我们发现随着 $i$ 的增长, $pos_{i, j}$ 是单调不降的, 考虑动态维护这个指针就可以了。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 4e4 + 5, col = 256;

int n, m;
int a[N], f[N], cnt[col][N], pos[col], colC[col];

int main () {
	memset(f, 0x3f, sizeof(f));
	cin >> n >> m, m = sqrt(n + 0.5);
	for (int i = 1; i <= n; i ++)
		cin >> a[i];
	f[0] = 0;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++)
			if (++ cnt[j][a[i]] == 1) {
				if (++ colC[j] > j) {
					while (-- cnt[j][a[++ pos[j]]] != 0) ;
					colC[j] --;
				}
			}
		for (int j = 1; j <= m; j ++)
			f[i] = min(f[i], f[pos[j]] + j * j);
	}
		
	cout << f[n];
	return 0;
}
```


---

## 作者：_虹_ (赞：0)

这里是：**菜的真实**的O(nsqrtnlogn)做法

发现每个划分内部显然不能超过sqrtn种食物，否则还不如一个一个分开优。

所以对于i点，我们可以枚举i点为划分的右端点时的食物种类数x，显然x相同的源状态j，必然是连续的一段。

我们维护以i为划分右端点时，食物种类数量在哪些点发生变化，枚举前sqrtn段转移即可。

对于食物种类数相同的一段，转移取min，可以用线段树维护。

用了set，需要吸氧。

现在luogu氧气好像炸了，所以手开了O2。。。

~~编译需要c++11~~

```cpp
#pragma GCC optimize(2)
#include <iostream>
#include <set>
#include <cmath>
using namespace std;
const int kmaxn=40000+5;
typedef long long ll;
const ll inf=1e15;
int lst[kmaxn];
int a[kmaxn]; 
int n,m;
struct node{
	int l,r;
	ll v=inf;
};
node T[kmaxn<<2];
#define LS (ls(p))
#define RS (rs(p))
#define LEAF (T[p].l==T[p].r)
#define TARGET (T[p].l==l&&T[p].r==r)
#define UPD upd(p)
#define CALMID int mid=((T[p].l+T[p].r)>>1)
inline int ls(int i){return i<<1;}
inline int rs(int i){return ls(i)|1;}
inline void upd(int p)
{
	if(LEAF)return;
	T[p].v=min(T[LS].v,T[RS].v);
}
void build(int l,int r,int p){
	T[p].l=l;T[p].r=r;
	if(LEAF)return;
	CALMID;
	build(l,mid,LS);
	build(mid+1,r,RS);
}
ll qry(int l,int r,int p)
{
	if(TARGET)
		return T[p].v;
	CALMID;
	if(r<=mid)return qry(l,r,LS);
	else if(l>mid)return qry(l,r,RS);
	else{
		return min(qry(l,mid,LS),
				qry(mid+1,r,RS));
	}
}
void ins(int k,ll v,int p)
{
	if(LEAF){
		T[p].v=v;
		return;
	}
	CALMID;
	if(k<=mid)ins(k,v,LS);
	else ins(k,v,RS);
	UPD;
}
int srt;
set<int,greater<int> > st;
void solve(int p)
{
	int cnt=1;
	auto itr=st.begin();
	int ls=p;
	ll ans=p*p;
	++itr;
	while(cnt<=srt && itr!=st.end())
	{
		ans=min(ans,qry((*itr),ls,1)+cnt*cnt);
		ls=*itr;
		++cnt;
		++itr;
	}
	ins(p,ans,1);
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	build(0,n,1);
	ins(0,0,1);
	srt=sqrt(n)+1;
	st.insert(0);
	for(int i=1;i<=n;++i)
	{
		if(lst[a[i]])
			st.erase(lst[a[i]]);
		lst[a[i]]=i;
		st.insert(i);
		solve(i);
	}
	cout<<qry(n,n,1)<<endl;
	return 0;
}
```


---

