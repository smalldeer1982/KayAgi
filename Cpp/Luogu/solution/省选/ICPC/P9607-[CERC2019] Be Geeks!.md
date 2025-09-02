# [CERC2019] Be Geeks!

## 题目背景

**题目译自 [CERC 2019](https://contest.felk.cvut.cz/19cerc/solved.html) 「[Be Geeks!](https://contest.felk.cvut.cz/19cerc/solved/begeeks.pdf)」**

## 题目描述

音乐乐队 Be Geeks! 的名字并非偶然，因为所有成员都是真正的数学怪才。除此之外，他们喜欢研究数列的各种性质。下面是他们感兴趣的一个例子：
- 设 $A$ 是一个非空正整数序列，$A=(a_1, a_2, \dots, a_N)$。
- $G(i, j)=\gcd (a_i, a_{i+1}, \dots, a_j)$，其中 $1\le i\le j\le N$。
- $M(i, j)=\max (a_i, a_{i+1}, \dots, a_j)$，其中 $1\le i\le j\le N$。
- $P(i, j)=G(i, j)\times M(i, j)$，其中 $1\le i\le j\le N$。
- $F(A)=\sum P(i, j)[1\le i\le j\le N]$。

给出一个序列 $A$，你需要求出 $F(A)\bmod 1\,000\,000\,007$ 的值。

## 样例 #1

### 输入

```
4
1 2 3 4
```

### 输出

```
50
```

## 样例 #2

### 输入

```
5
2 4 6 12 3
```

### 输出

```
457
```

# 题解

## 作者：缪凌锴_Mathew (赞：17)

## 思路

首先，如果只求最大值之和就比较简单。

对于每一个点 $x$，求出最小的 $l$，最大的 $r$，使得：

- $a_{l},a_{l+1},\dots,a_{x-1} <a_x$

- $a_{x+1},a_{x+2},\dots,a_r \le a_x$

例如下面这个例子:

```
24 18 20 14 15 30
```

对于 $x=3,a_x=20$ 来说 $l=2,r=5$。

$l$ 再减小，则 $24>20$，$r$ 再增大，则 $30>20$。

![lr.png](https://s3.bmp.ovh/imgs/2023/09/15/dbe193a053f4786b.png)

所有 $l \le i \le x \le j \le r$ 的区间 $[i,j]$ 的最大值为 $a_x$。

此时对答案的贡献为 $a_x \times \sum_{l \le i \le x \le j \le r} G(i,j)$。

快速求这个 $l,r$，考虑倍增，预处理出每个点向前和向后 $2^k$ 个数的最大值，倍增跳 $l,r$ 到边界。

为什么第一个条件是 $<x$ 而不是 $\le x$ 呢？

**序列中有相等的数会使得区间被重复计算。**

我们向右扩到 $n$，向左扩不超过上一个一样的数，就可以避免使得区间被重复计算。

用 map 维护就能求出上一个一样的数了。

---

现在要求所有 $l \le i \le x \le j \le r$ 的区间 $[i,j]$ 的区间 gcd 的和。

观察这个样例从第一个数开始的前缀 gcd：

```
72 36 48 12 24 18 24 36 66 44 26 34 17 19 51
```

![gcd.png](https://s3.bmp.ovh/imgs/2023/09/15/eb8e8ef2cf573ad0.png)

所有前缀 gcd，若有变化，则变化前的 $lstgcd$ 为变化后的 $nxtgcd$ 的倍数。$nxtgcd \le \dfrac{lstgcd}{2}$，因此 gcd 最多有 $\log V$ 种。

得到结论，$x \le p \le r$ 的区间 $[x,p]$ 的 gcd 只有 $\log V$ 种。

同理 $l \le p \le x$ 的区间 $[p,x]$ 的 gcd 只有 $\log V$ 种。

我们只需把两边的这 $\log V$ 种 gcd 求出来，直接暴力 $O(log^{2} V)$ 枚举求答案。

同样，倍增求值，预处理出每个点向前和向后 $2^k$ 个数的 gcd ，每个 gcd 值倍增跳到边界。

复杂度看似还有一个 gcd 的 $O(\log V)$，实际上我们做区间 $[x,i]$ 的 gcd 时可以利用上一次的 gcd ，辗转相除一共 $O(\log V)$ 次，均摊下来每次 gcd 的复杂度为 $O(1)$。

总复杂度 $O(n \log^{2} V)$。

## 代码

```cpp
#include<map>
#include<set>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<cstdio>
#include<vector>
#include<string>
#include<bitset>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=2e5+10;
const int MAXM=25;//log n
const int M=20;
const int MAXK=35;//log V
const int INF=0x3f3f3f3f;
const long long LINF=0x3f3f3f3f3f3f3f3f;
const int mod=1e9+7;
int gcd(int a,int b){
    if(!b){
        return a;
    }
    return gcd(b,a%b);
}
int n,ans=0;
int a[MAXN];
int maxl[MAXN][MAXM],maxr[MAXN][MAXM];//i向左、向右2^k个数的最大值
int gcdl[MAXN][MAXM],gcdr[MAXN][MAXM];//i向左、向右2^k个数的gcd
map <int,int> mp;
struct node{//每一个最大公因数的范围，数值
    int ql,qr,val;
}L[MAXK],R[MAXK];
int cntl,cntr;//左。右的最大公因数的数值个数（<logV）
void work(int x){
    int l=x,r=x;
    int lim=mp[a[x]];//上一个一样的数（没有则为0）
    for(int i=M;i>=0;i--)//倍增跳l和r
    {
        if(l-(1<<i)>lim&&maxl[l-1][i]<=a[x]){
            l-=(1<<i);
        }
        if(r+(1<<i)<=n&&maxr[r+1][i]<=a[x]){
            r+=(1<<i);
        }
    }
    cntl=0;
    cntr=0;
    int Gcd=a[x],p=x;//当前最大公因数的数值，当前位置
    while(1)
    {
        int lst=p;
        for(int i=M;i>=0;i--)
        {
            if(p-(1<<i)>=l&&gcdl[p-1][i]%Gcd==0){
                p-=(1<<i);
            }
        }
        cntl++;
        L[cntl]=(node){p,lst,Gcd};
        if(p==l){
            break;
        }
        p--;
        Gcd=gcd(Gcd,a[p]);
    }
    Gcd=a[x];
    p=x;
    while(1)
    {
        int lst=p;
        for(int i=M;i>=0;i--)
        {
            if(p+(1<<i)<=r&&gcdr[p+1][i]%Gcd==0){
                p+=(1<<i);
            }
        }
        cntr++;
        R[cntr]=(node){lst,p,Gcd};
        if(p==r){
            break;
        }
        p++;
        Gcd=gcd(Gcd,a[p]);
    }
    int res=0;
    //暴力统计答案
    for(int i=1;i<=cntl;i++)
    {
        int lst=L[i].val;//优化gcd
        for(int j=1;j<=cntr;j++)
        {
            int lenl=L[i].qr-L[i].ql+1;
            int lenr=R[j].qr-R[j].ql+1;
            res+=1ll*lenl*lenr%mod*gcd(lst,R[j].val)%mod;
            res%=mod;
        }
    }
    ans+=1ll*res*a[x]%mod;
    ans%=mod;
}
signed main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        maxl[i][0]=a[i];
        maxr[i][0]=a[i];
        gcdl[i][0]=a[i];
        gcdr[i][0]=a[i];
    }
    for(int i=1;i<=M;i++)//预处理
    {
        int len=(1<<(i-1));
        for(int j=1;j<=n;j++)
        {
            maxl[j][i]=maxl[j][i-1];
            maxr[j][i]=maxr[j][i-1];
            gcdl[j][i]=gcdl[j][i-1];
            gcdr[j][i]=gcdr[j][i-1];
        }
        for(int j=1;j+len<=n;j++)
        {
            maxr[j][i]=max(maxr[j][i],maxr[j+len][i-1]);
            gcdr[j][i]=gcd(gcdr[j][i],gcdr[j+len][i-1]);
        }
        for(int j=len+1;j<=n;j++)
        {
            maxl[j][i]=max(maxl[j][i],maxl[j-len][i-1]);
            gcdl[j][i]=gcd(gcdl[j][i],gcdl[j-len][i-1]);
        }
    }
    for(int i=1;i<=n;i++)
    {
        work(i);
        mp[a[i]]=i;
    }
    printf("%d\n",ans);
    return 0;
}
```

#### update 2023.10.8 改正一个错误，感谢 [@Sunny郭](https://www.luogu.com.cn/user/360547) 指出。

#### update 2023.10.25 改正一个复杂度分析的错误，感谢 [@VioletIsMyLove](https://www.luogu.com.cn/user/188879) 指出。

---

## 作者：KazamaRuri (赞：13)

## P9607 [CERC2019] Be Geeks!

写给不喜欢冗长代码的人，由于别的题解代码我认为较难理解，所以有了这篇题解，随手一写就是最优榜第一页。

## 题意

- 设 $ A $ 是一个非空正整数序列，$ A=(a_1, a_2, \dots, a_N) $。
- $ G(i, j)=\gcd (a_i, a_{i+1}, \dots, a_j) $，其中 $1\le i\le j\le N $。
- $ M(i, j)=\max (a_i, a_{i+1}, \dots, a_j)$，其中 $1\le i\le j\le N $。
- $ P(i, j)=G(i, j)\times M(i, j)$，其中 $1\le i\le j\le N $。
- $ F(A)=\sum P(i, j)[1\le i\le j\le N] $。

现在给了你 $ A $（以下称之为 $ a $），求 $ F(A)\bmod 1\,000\,000\,007 $ 的值。

## 分析

区间 $ \max $ 加区间贡献，可以用笛卡尔树求解，但是我更喜欢它的另一个名字——**极值分治**（极值分治的过程本质上就是在建笛卡尔树）。

对于一个区间 $ [l,r] $，找到最大值的位置 $ mid $，计算包含下标 $ mid $ 的区间答案，这样当前计算的所有区间的 $ M(i, j) $ 均等于 $ a_{mid} $，对于 $ \gcd $ 的部分，详见下文。对于剩下的答案（不包含 $ mid $ 的区间），递归分治 $ [l,mid-1] $ 和 $ [mid+1,r] $ 即可。

讲完整体思路，到了具体实现。数据结构采用可以 $ O(1) $ 静态查询的 st 表来处理区间 $ \max $ 和 区间 $ \gcd $，尽量减小常数。重点还是在确定最大值后计算区间答案。有一个简单的性质，区间 $ \gcd $ 的变化次数不会超过 $ \log V $ 次，其中 $ V $ 为元素的值域。简单证明一下，**每次 $ \gcd $ 变化都至少会变为原来的二分之一**，因为最小的质因数是 $ 2 $。利用这个性质和 $ \gcd $ 的单调递减性，在左半区间用二分求出很多个分别连续的最长段 $ [i,j] $ 使得对于在区间中所有的 $ k $，$ \gcd(a_{k},a_{k+1}, \cdots , a_{mid}) \ \  ( k \in [i,j] )$ 均相等，最重要的是这样的最长段一定不超过 $ \log V $ 个；同样地，在右半区间也干一次这种操作。最后用  $ O( \log^2 V ) $ 的时间暴力计算左半区间的小段和右半区间小段互相造成的贡献。枚举小段，在左边枚举到的小段中取区间左边界 $ i $，右小段取右边界 $ j $，这样不仅 $ M(i, j) $ 是**唯一且确定**的了，$ G(i,j) $ 也是**确定**的了，我们能**快速计算**出答案。详见代码，有点难解释清楚，当然如果能自己想到如何计算就更好了。总的平均时间复杂度大概在 $ O(n \cdot \log n \cdot \log V) $，最坏也只能被卡到 $ O(n \cdot \log^2 V) $，随便过二十万的数据范围。

## 代码

没有刻意压行，总计行数不算注释 34 行，应该是题解里短的。

```cpp
#include <iostream>
#include <map>
using namespace std;

const int N=2e5+5,mod=1e9+7; map<int,int>m1,m2;
int n,a[N],lg[N],st[N][20],g[N][20],ans;
int _gcd(int x,int y){ return y?_gcd(y,x%y):x; }
int _get(int x,int y){ return a[x]<a[y]?y:x; }
int rmq(int l,int r){ int k=lg[r-l+1]; return _get(st[l][k],st[r-(1<<k)+1][k]); }
int gcd(int l,int r){ int k=lg[r-l+1]; return _gcd(g[l][k],g[r-(1<<k)+1][k]); }
int get(int typ,int p,int l,int r,int x){ int mid;
	if(!typ) while(l<r) mid=l+r>>1,gcd(mid,p)==x?r=mid:l=mid+1;
	else while(l<r) mid=l+r+1>>1,gcd(p,mid)==x?l=mid:r=mid-1;
	return typ?l:r;
}
void solve(int l,int r){
	if(l>r) return ; if(l==r) return ans=(ans+1ll*a[l]*a[l]%mod)%mod,void();
	int mid=rmq(l,r); solve(l,mid-1),solve(mid+1,r);
	for(int i=mid,j;i>=l;i=j-1) j=get(0,mid,l,i,gcd(i,mid)),m1[gcd(i,mid)]=i-j+1;
	for(int i=mid,j;i<=r;i=j+1) j=get(1,mid,i,r,gcd(mid,i)),m2[gcd(mid,i)]=j-i+1;
  //    维护每个小段的gcd值和段长（即可作为边界的点的数量）
	for(auto x:m1) for(auto y:m2) ans=(ans+1ll*a[mid]*_gcd(x.first,y.first)%mod*x.second%mod*y.second%mod)%mod;
  //    计算答案，乘法原理。first为gcd值，second为段长，或者说取值数量。
  //    a[mid]即M(i,j),区间最大值。gcd(x.first,y.first)就是两半区间边界“并”起来之后的总gcd
	m1.clear(),m2.clear();
}
int main(){
	scanf("%d",&n),lg[0]=-1;
	for(int i=1;i<=n;i++)
		scanf("%d",a+i),lg[i]=lg[i>>1]+1,
		st[i][0]=i,g[i][0]=a[i];
	for(int j=1;(1<<j)<=n;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			st[i][j]=_get(st[i][j-1],st[i+(1<<j-1)][j-1]),
			g[i][j]=_gcd(g[i][j-1],g[i+(1<<j-1)][j-1]);
	return solve(1,n),printf("%lld",ans),0;
}
```

---

## 作者：xkcdjerry (赞：4)

提供一个好想好写还常数特别小的做法

---

拆贡献部分其他题解讲的很清楚，这里只放一下结论：

令 $L_x$ 为 $x$ 左侧最靠右的 $\geqslant a_x$ 的值的位置，$R_x$ 为 $x$ 右侧最靠左的 $>a_x$ 的值的位置。（此处认为 $a_0$ 和 $a_{n+1}$ 均为无穷大）  
显然这两个数组可以用单调栈 $O(n)$ 求出来。

那么我们要求的值就变成了：  
$$
F(A)= \sum_{x=1}^n a_x \sum_{i=L_x}^x \sum_{j=x}^{R_x} G(i,j)
$$

---

那么我们现在的目标就转为了求 $\sum_{i=L}^x \sum_{j=x}^R G(i,j)$ 的值，后称该函数为 $SG(L,R)$：  
$$
SG(L,R)=\sum_{i=L}^x \sum_{j=x}^R \gcd(G(i,x),G(x,j))
$$

由于 $\gcd(x,y)|x, \gcd(x,y)|y$，所以若 $\gcd(x,y) \neq x$，一定有 $\gcd(x,y) \leqslant \dfrac{x}2$。

由此可得，对于给定的 $x$，$G(i,x)$ 和 $G(x,j)$ 最多有 $\log a_x$ 种不同的取值。如果能够确定每个取值出现的次数，那就可以 $O(\log^2 V)$ 枚举取值对来计算 $SG$ 的值了。

这里用到了一个和 [CF1834E](https://www.luogu.com.cn/problem/solution/CF1834E) 类似的 trick：

（为了简明起见一下均以 $G(x,j)$ 作为例子，$G(i,x)$ 与之大同小异）

首先考虑如果已经求出来每个取值出现的次数，如何高效贮存：  
我们可以从左向右记录每次 $\gcd$ 改变的位置。那么每段区间的值就是这个区间左边的位置对应值的 $\gcd$ 和，而长度（出现次数）就是相邻位置的差。


先证个定理：若 $G(x,i)=G(x,i-1)$，则 $G(x-1,i)=G(x-1,i-1)$。    证明：  
因为 $G(x,i)=G(x,i-1)$，那么有 $G(x,i-1)|a_i$。  
又因为 $G(x-1,i-1)=\gcd(a_{x-1},G(x,i-1))$，所以 $G(x-1,i-1)|G(x,i-1)$。  
由此可得 $G(x-1,i-1)|a_i$，即 $G(x-1,i)=G(x-1,i-1)$。  
故证

**换句话说，以 $x$ 作为左端点时未使 $\gcd$ 改变的值，以 $x-1$ 作为左端点的时候也不会使 $\gcd$ 改变。**

那么自然而然的引出这个思路：  
从右往左扫，对于每个值维护以它为左端点时 $\gcd$ 改变的位置。  
为 $i$ 计算位置集合的时候，先插入自己所在的位置，然后把 $i+1$ 对应的改变位置一一应用到目前 $\gcd$ 上，如果改变了 $\gcd$ 那就插入到自己的位置集合里，否则忽略。

这里文字说着比较晦涩难懂，代码会清楚很多：

```c++
for(int i=n;i>=1;i--)
{
	right[i].push_back(i); int tmp=a[i];
	for(auto j:right[i+1]) if(gcd(tmp,a[j])!=tmp)
		tmp=gcd(tmp,a[j]), right[i].push_back(j);
}
```

由于每次 $\gcd$ 变化至少减少一半，那么每个变化数组最多有 $\log V$ 个值，维护数组的复杂度为 $O(n \log V)$。  
而由于 $\gcd$ 的值从 $a_i$ 单调递减，所以运行 $\gcd$ 的复杂度也是 $O(n \log V)$ 的。  
因此这段代码的总复杂度为 $O(n \log V)$。

---

现在我们有了每个值作为 $\max$ 的贡献范围和每个值左右 $\gcd$ 的值和数量，只需要把两个组合在一起就行了。注意上面求的 $\gcd$ 变化点是全局的，裁剪到给定的范围内即可。

用不到任何数据结构（除非你算 `vector`）

```c++
#include <cstdio>
#include <vector>
#define N 200010
#define P 1000000007
int n,a[N];
std::vector<int> left[N],right[N];
int fl[N],fr[N],stk[N],top;
int gcd(int x,int y) {return y?gcd(y,x%y):x;}
int main()
{
	scanf("%d",&n); for(int i=1;i<=n;i++) scanf("%d",a+i);
	//维护向左的 gcd 变化点
	for(int i=1;i<=n;i++)
	{
		left[i].push_back(i); int tmp=a[i];
		for(auto j:left[i-1]) if(gcd(tmp,a[j])!=tmp)
			tmp=gcd(tmp,a[j]), left[i].push_back(j);
	}
	//维护向右的 gcd 变化点
	for(int i=n;i>=1;i--)
	{
		right[i].push_back(i); int tmp=a[i];
		for(auto j:right[i+1]) if(gcd(tmp,a[j])!=tmp)
			tmp=gcd(tmp,a[j]), right[i].push_back(j);
	}
	//维护每个数左边第一个>=它的
	top=0; for(int i=1;i<=n;i++)
	{
		while(top&&a[stk[top]]<a[i]) top--;
		fl[i]=top?stk[top]:0;
		stk[++top]=i;
	}
	//维护每个数右边第一个>它的
	top=0; for(int i=n;i>=1;i--)
	{
		while(top&&a[stk[top]]<=a[i]) top--;
		fr[i]=top?stk[top]:n+1;
		stk[++top]=i;
	}
	//对于每个数统计答案
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		//裁剪范围
		while(!right[i].empty()&&right[i].back()>=fr[i]) right[i].pop_back();
		right[i].push_back(fr[i]);
		while(!left[i].empty()&&left[i].back()<=fl[i]) left[i].pop_back();
		left[i].push_back(fl[i]);

		int tr=a[i],lastr=i;
		for(auto j:right[i])
		{
			int tl=a[i],lastl=i;
			for(auto k:left[i])
			{
				(ans+=1ll*(lastl-k)*(j-lastr)%P*gcd(tl,tr)%P*a[i])%=P;
				tl=gcd(tl,a[lastl=k]);
			}
			tr=gcd(tr,a[lastr=j]);
		}
	}
	printf("%lld",ans);
}
```

不做任何卡常就能跑到 [4.64s](https://www.luogu.com.cn/record/132709637)，本文写的时候是最优解第二页上半部分。

~~如果有谁以这个为基础卡常冲到最优解前面请务必在下面评论让我更新本文~~

---

## 作者：zesqwq (赞：4)

对最大值做笛卡尔树。

然后问题变为给定 $p,q,t$, 求 $\sum_{p \le l \le q,q \le r \le t} \gcd_{l \le i \le r}(a_i)$

我们定义 $f(x, y) = \sum_{x \le l \le r \le y} \gcd_{l \le i \le r} (a_i)$，那么原问题可以差分为 $f(p, t) - f(p, q - 1) - f(q + 1, t)$。

$f$ 的求解可以用 [该题](https://www.luogu.com.cn/problem/P8421) 的做法解决，时间复杂度 $O(n \log V)$。

---

## 作者：_AyachiNene (赞：2)

来一发笛卡尔树分治题解。
# 思路：
首先看到题目要求区间最大值乘区间 gcd，很容易想到笛卡尔树分治，每次找到最大值，以最大值为中点，算短的一半区间对长的一半的贡献即可。对于这道题，算贡献的难度主要在于区间 gcd。可以发现，gcd 是会单调递减的，且从一个点出发最多会有 $\log n$ 段 gcd 值不同的区间，因为如果两个数如果互质，那么 gcd 就直接为 $1$ 了，不然如果要 gcd 之后的值发生改变，至少都要除以 $2$。所以直接上数据结构维护从每个位置开始分的段就行了。具体的，可以用 st 表加二分，复杂度 $\log^3 n$ 总的段数和二分和 st 表都是 $\log n$。这里好像有均摊 $O(1)$ 求 gcd 的做法，但我太菜了不会。之后正常上分治还有一个 $\log n$ 肯定跑不过，所以把分的段预处理出来就可以了。总复杂度 $O(n\log^3n)$。这道题还卡空间，直接存分的段会超一点，我的解决办法是分两次跑分治，一次跑短边在左边的一次右边的。
# Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){char ch=getch();while(ch<'a'||ch>'z')ch=getch();while(ch>='a'&&ch<='z'){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
const int mod=1e9+7;
int n,a[200005];
vector<pair<int,int> >posl[200005];
vector<int>gcdl[200005];
int lg[200005];
namespace Elaina
{
	int st[200005][19];
	void bld()
	{
		for(int i=1;i<=n;i++) st[i][0]=i;
		for(int j=1;j<=18;j++)
			for(int i=1;i+(1<<j)-1<=n;i++)
				if(a[st[i][j-1]]<a[st[i+(1<<(j-1))][j-1]]) st[i][j]=st[i+(1<<(j-1))][j-1];
				else st[i][j]=st[i][j-1];
	}
	int query(int l,int r)
	{
		int k=lg[r-l+1];
		return a[st[l][k]]<a[st[r-(1<<k)+1][k]]?st[r-(1<<k)+1][k]:st[l][k];
	}
}
namespace Chtholly
{
	int st[200005][19];
	void bld()
	{
		a[0]=a[1];
		for(int i=0;i<=n;i++) st[i][0]=a[i];
		for(int j=1;j<=18;j++)
			for(int i=1;i+(1<<j)-1<=n;i++)
				st[i][j]=__gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	}
	int query(int l,int r)
	{
		int k=lg[r-l+1];
		return __gcd(st[l][k],st[r-(1<<k)+1][k]);
	}
}
ll ans;
void dcrs_solve1(int l,int r)
{
	if(l>r) return;
	if(l==r)
	{
		ans=(ans+1ll*a[l]*a[l])%mod;
		return;
	}
	int pos=Elaina::query(l,r);
	dcrs_solve1(l,pos-1);dcrs_solve1(pos+1,r);
	if(pos-l<=r-pos)
		for(int i=l;i<=pos;i++)
			for(int j=0;j<posl[i].size();j++)
				if(posl[i][j].second>=pos&&posl[i][j].first<=r)
					ans=(ans+1ll*a[pos]*gcdl[i][j]%mod*(min(r,posl[i][j].second)-max(pos,posl[i][j].first)+1))%mod;
}
void dcrs_solve2(int l,int r)
{
	if(l>=r) return;
	int pos=Elaina::query(l,r);
	dcrs_solve2(l,pos-1);dcrs_solve2(pos+1,r);
	if(pos-l>r-pos)
		for(int i=pos;i<=r;i++)
			for(int j=0;j<posl[i].size();j++)
				if(posl[i][j].first<=pos&&posl[i][j].second>=l)
					ans=(ans+1ll*a[pos]*gcdl[i][j]%mod*(min(pos,posl[i][j].second)-max(l,posl[i][j].first)+1))%mod;
}
int main()
{
	read(n);
	for(int i=2;i<=n;i++) lg[i]=lg[i/2]+1;
	for(int i=1;i<=n;i++) read(a[i]);
	Elaina::bld();
	Chtholly::bld();
	for(int i=1;i<=n;i++)
	{
		int p=i;
		while(p<=n)
		{
			int l=p,r=n,res=p;
			while(l<=r)
			{
				int mid=l+r>>1;
				if(Chtholly::query(i,mid)<Chtholly::query(i,p)) r=mid-1;
				else  res=mid,l=mid+1;
			}
			posl[i].push_back({p,res});
			gcdl[i].push_back(Chtholly::query(i,res));
			p=res+1;
		}
	}
	dcrs_solve1(1,n);
	for(int i=1;i<=n;i++) posl[i].clear(),gcdl[i].clear();
	for(int i=n;i>=1;i--)
	{
		int p=i;
		while(p>=1)
		{
			int l=1,r=p,res=p;
			while(l<=r)
			{
				int mid=l+r>>1;
				if(Chtholly::query(mid,i)<Chtholly::query(p,i)) l=mid+1;
				else res=mid,r=mid-1;
			}
			posl[i].push_back({res,p});
			gcdl[i].push_back(Chtholly::query(res,i));
			p=res-1;
		}
	}
	dcrs_solve2(1,n);
	write(ans);
	flush();
}
```

---

## 作者：CAICAIA (赞：2)

# P9607 [CERC2019] Be Geeks 题解

## 思路

学校模拟赛考了这个题，场切了。

先考虑这个式子如何求 $\sum\limits_{i=1}^n\sum\limits_{j=i}^n\max\{a_i,a_{i+1},...,a_j\}$。

很套路，极值分治。

对于一个区间 $\left[l,r\right]$ 找到最大值位置 $mid$，计算跨过 $mid$ 的答案为 $a_{mid}\times \left(mid-l+1\right)\times \left(r-mid+1\right)$，然后再分治左区间和右区间即可。

笛卡尔树可以 $\mathcal{O\left(n\right)}$ 完成。

现在考虑加上 $\gcd$ 的版本。

对于一个区间 $\left[l,r\right]$ 记他的前缀 $\gcd$ 数组为 $b$。

根据 $\gcd$ 的性质，$b$ 一定是单调递减的，而且 $b_{i+1}$ 为 $b_i$ 的因数。

而这个区间的变化次数为 $log_2 V$ 次，证明：每次 $\gcd$ 都至少变为原来的一半，因为最小质因数是 $2$。

利用这个性质和单调递减性，可以利用二分求出若干个最长连续的区间 $\left[i,j\right]$，使得对于在区间中的所有数 $k$ ，$\gcd\left(a_l,a_{l+1},...,a_k\right),k\in\left[i,j\right]$ 均相等。

这样在 $\left[l,mid\right]$ 和 $\left[mid,r\right]$ 分别正着做一遍二分，反着做一遍二分即可。

最后暴力枚举所有二分的区间，时间复杂度 $\mathcal{O\left(log^2V\right)}$。

最后答案为 $\sum\limits_{mid=1}^n\sum\limits_{i=1}^{cnt_l}\sum\limits_{j=i}^{cnt_r}
val_{mid}\times siz_i\times siz_j\times gcd_i\times gcd_j$ 。

![](https://s21.ax1x.com/2024/09/02/pAVkT4H.jpg)

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MO=1000000007,INF=0x3f3f3f3f,MX=200010;
struct node{
    int lc,rc;
    int siz;
    int l,r;
}tree[MX];
int input[MX]={0},n;
void dfs(int now){
    if(!now)  return ;
    tree[now].l=tree[now].r=now;
    dfs(tree[now].lc),dfs(tree[now].rc);
    tree[now].siz+=tree[tree[now].lc].siz+tree[tree[now].rc].siz+1;
    if(tree[now].lc)  tree[now].l=tree[tree[now].lc].l;
    if(tree[now].rc)  tree[now].r=tree[tree[now].rc].r;
}
int lg[MX]={0},st[MX][30]={0};
void build_st(){
    for(int i=2;i<MX;i++)  lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;i++)  st[i][0]=input[i];
    for(int j=1;j<=lg[n];j++)
        for(int i=1;i+(1<<j-1)-1<=n;i++)
            st[i][j]=__gcd(st[i][j-1],st[i+(1<<j-1)][j-1]);
}
inline int cy(int l,int r){
    return __gcd(st[l][lg[r-l+1]],st[r-(1<<lg[r-l+1])+1][lg[r-l+1]]);
}
long long siz_l[MX]={0},siz_r[MX]={0},cnt_l;
long long val_l[MX]={0},val_r[MX]={0},cnt_r;
void ef_left(int l,int r){
    int i=r;cnt_l=0;
    while(l<=i){
        int lef=l,rig=i,mid,ans=i,now=cy(i,r);
        while(lef<=rig){
            mid=(lef+rig)>>1;
            if(cy(mid,r)==now)  rig=mid-1,ans=mid;
            else  lef=mid+1;
        }
        siz_l[++cnt_l]=i-ans+1,val_l[cnt_l]=now;
        i=ans-1;
    }
}
void ef_right(int l,int r){
    int i=l;cnt_r=0;
    while(i<=r){
        int lef=i,rig=r,mid,ans=i,now=cy(l,i);
        while(lef<=rig){
            mid=(lef+rig)>>1;
            if(cy(l,mid)==now)  lef=mid+1,ans=mid;
            else  rig=mid-1;
        }
        siz_r[++cnt_r]=ans-i+1,val_r[cnt_r]=now,i=ans+1;
    }
}
long long sum=0;
void meg(int now){
    if(!now)  return ;
    meg(tree[now].lc),meg(tree[now].rc);
    ef_left(tree[now].l,now),ef_right(now,tree[now].r);
    for(int i=1;i<=cnt_l;i++)for(int j=1;j<=cnt_r;j++)  sum=(sum+(((((siz_l[i]*siz_r[j])%MO)*__gcd(val_l[i],val_r[j]))%MO)*input[now])%MO)%MO;
}
signed main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&input[i]);
    stack<int>st;int root=0;
    for(int i=1;i<=n;i++){
        int now=0;
        while(!st.empty()&&input[st.top()]<input[i])  now=st.top(),st.pop();
        if(st.empty())  root=i;
        else  tree[st.top()].rc=i;
        tree[i].lc=now;st.push(i);
    }
    dfs(root);build_st();
    meg(root);
    printf("%lld",sum);
    return 0;
}//P9607
```

---

## 作者：zyn0309 (赞：1)

# P9607 [CERC2019] Be Geeks!
[题目传送门](https://www.luogu.com.cn/problem/P9607)

## 思路
考虑直接对原序列分治，每次将当前分治区域处理完后再处理左右两边，分治树总大小为 $n \log n$。


设当前分治区间左右端点为 $l$ 和 $r$，中点为 $mid$，思考如何处理跨过分治中点的答案。

把左区间（$mid$ 到 $l$）的后缀的 $\gcd $ 和右区间（$mid+1$ 到 $r$）前缀的 $\gcd$ 处理出来，因为 $\gcd$ 每一次改变都至少减半，所以两个区间处理出的 $\gcd$ 分别最多有 $\log V$ 个。（$V$ 为值域上界）

对于两个区间中的每一种 $\gcd$，我们都开一个 vector，然后插入该区间中前缀或后缀的 $\gcd$ 等于对应值位置的区间最大值。然后在另一半区间的每一个位置，枚举所有的 $\gcd$，去对应的 vector 里面二分有多少个最大值小于它的数位置，最后把 $ans$ 加上两个位置的 $\gcd$ 乘上最大值再乘上二分出的个数即可。


## Code 
```cpp
#include<bits/stdc++.h>
namespace fast_IO{
	#define IOSIZE 100000
		char ibuf[IOSIZE], obuf[IOSIZE], *p1 = ibuf, *p2 = ibuf, *p3 = obuf;
	#define getchar() ((p1==p2)and(p2=(p1=ibuf)+fread(ibuf,1,IOSIZE,stdin),p1==p2)?(EOF):(*p1++))
	#define putchar(x) ((p3==obuf+IOSIZE)&&(fwrite(obuf,p3-obuf,1,stdout),p3=obuf),*p3++=x)
	#define isdigit(ch) (ch>47&&ch<58)
	#define isspace(ch) (ch<33)
		template<typename T> inline T read() { T s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s * w; }
		template<typename T> inline bool read(T &s) { s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s *= w, true; }
		template<typename T> inline void print(T x) { if (x < 0) putchar('-'), x = -x; if (x > 9) print(x / 10); putchar(x % 10 + 48); }
		inline bool read(char &s) { while (s = getchar(), isspace(s)); return true; }
		inline bool read(char *s) { char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) *s++ = ch, ch = getchar(); *s = '\000'; return true; }
		inline void print(char x) { putchar(x); }
		inline void print(char *x) { while (*x) putchar(*x++); }
		inline void print(const char *x) { for (int i = 0; x[i]; i++) putchar(x[i]); }
		inline bool read(std::string& s) { s = ""; char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) s += ch, ch = getchar(); return true; }
		inline void print(std::string x) { for (int i = 0, n = x.size(); i < n; i++) putchar(x[i]); }
		inline bool read(bool &b) { char ch; while(ch=getchar(), isspace(ch)); b=ch^48; return true; }
		inline void print(bool b) { putchar(b+48); }
		template<typename T, typename... T1> inline int read(T& a, T1&... other) { return read(a) + read(other...); }
		template<typename T, typename... T1> inline void print(T a, T1... other) { print(a), print(other...); }
		struct Fast_IO { ~Fast_IO() { fwrite(obuf, p3 - obuf, 1, stdout); } } io;
		template<typename T> Fast_IO& operator >> (Fast_IO &io, T &b) { return read(b), io; }
		template<typename T> Fast_IO& operator << (Fast_IO &io, T b) { return print(b), io; }
	#define cout io
	#define cin io
}using namespace fast_IO;
using namespace std;
const int mod=1e9+7,N=2e5+10;
int n,g[N],a[N],ans,len,p[N];
vector<int>v[N];
#define pb push_back
inline int check(int x,int val){
	return lower_bound(v[x].begin(),v[x].end(),val)-v[x].begin();
}
inline void solve(int l,int r){
	if(l==r){
	  ans=(ans+1ll*a[l]*a[l]%mod)%mod;
	  return;
	}
	int mid=(l+r)>>1;
	g[mid]=a[mid];
	for(int i=mid-1;i>=l;--i)g[i]=__gcd(g[i+1],a[i]);
	g[mid+1]=a[mid+1];
	for(int i=mid+2;i<=r;++i)g[i]=__gcd(g[i-1],a[i]);
	int ma=0;
	len=0;
	for(int i=mid;i>=l;--i){
	  ma=max(ma,a[i]);
	  if(g[i]!=p[len]){
	    p[++len]=g[i];
	    v[len].clear();
	  }
	  v[len].pb(ma);
	}
	ma=0;
	for(int i=mid+1;i<=r;++i){
	  ma=max(ma,a[i]);
	  for(int j=1;j<=len;++j)
		ans=(ans+1ll*check(j,ma+1)*__gcd(g[i],p[j])%mod*ma%mod)%mod;
	}
	ma=0,len=0;
	for(int i=mid+1;i<=r;++i){
	  ma=max(ma,a[i]);
	  if(g[i]!=p[len]){
	    p[++len]=g[i];
	    v[len].clear();
	  }
	  v[len].pb(ma);
	}
	ma=0;
	for(int i=mid;i>=l;--i){
	  ma=max(ma,a[i]);
	  for(int j=1;j<=len;++j)
		ans=(ans+1ll*check(j,ma)*__gcd(g[i],p[j])%mod*ma%mod)%mod;
	}
	solve(l,mid),solve(mid+1,r);
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	solve(1,n);
	cout<<ans<<"\n";
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/220959687)

---

## 作者：红黑树 (赞：1)

[可能更好的阅读体验](https://rbtr.ee/a-problem-by-koicy)

## [题意](https://www.luogu.com.cn/problem/P9607)
给定长度为 $n$ 的数组 $a$，求
$$\displaystyle\sum\limits_{i=1}^n\sum\limits_{j=i}^n \gcd\left\{a_i, a_{i + 1}, \ldots, a_j\right\} \cdot \max\left\{a_i, a_{i + 1}, \ldots, a_j\right\}$$

答案对 $10^9 + 7$ 取模。

## 题解
首先考虑一个简单版本的问题：
$$\displaystyle\sum\limits_{i=1}^n\sum\limits_{j=i}^n \gcd\left\{a_i, a_{i + 1}, \ldots, a_j\right\}$$

对于这个问题，$\gcd$ 是单调递减的，因此可以使用 ST 来维护区间 $\gcd$，统计答案时对于每个 $\gcd$ 值，乘以对应区间长度即可。

再回到原题。在一段区间里，最大值是不会改变的。所以对于每个最大值，乘上对应 $\gcd$ 值和长度，就是这个值的贡献。线段树维护最大值即可。

## 代码
```cpp
// Please submit with C++17! It's best to use C++20 or higher version.
// By Koicy (https://koicy.ly)
// rbtree (i@koicy.ly)
// Only one ace left.

#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#define _CONSOLE 0
// #define EFILE ""

using namespace std;
using tp = long long;
constexpr tp ZERO = 0, ONE = 1, INF32 = -1u >> 2, INF = -1ull >> 2;

template <typename _Type, size_t _Size>
struct mray : array<_Type, _Size + 9> {
  _Type& operator[](size_t index) { return this->at(index); }
};

// Defines

// Constants
constexpr tp Hat_N = 5e5, mod = 1e9 + 7;

// Classes
struct Seg_Tree {
  mray<tp, Hat_N * 4> laz;
  mray<tp, Hat_N * 4> val;

  void push(tp x) { val[x] = (val[x << 1] + val[x << 1 | 1]) % mod; }

  void pull(tp x, tp l, tp r) {
    if (laz[x]) {
      tp mid = l + r >> 1;
      laz[x << 1] = laz[x << 1 | 1] = laz[x];
      val[x << 1] = laz[x] * (mid - l + 1) % mod;
      val[x << 1 | 1] = laz[x] * (r - mid) % mod;
      laz[x] = 0;
    }
  }

  void build(tp x, tp l, tp r) {
    tp mid = l + r >> 1;
    laz[x] = val[x] = 0;
    if (l == r) return;
    build(x << 1, l, mid);
    build(x << 1 | 1, mid + 1, r);
    push(x);
  }

  void modify(tp x, tp l, tp r, tp ml, tp mr, tp k) {
    if (l <= ml && mr <= r) {
      val[x] = k * (mr - ml + 1);
      laz[x] = k;
    } else {
      tp mid = ml + mr >> 1;
      pull(x, ml, mr);
      if (l <= mid) modify(x << 1, l, r, ml, mid, k);
      if (r > mid) modify(x << 1 | 1, l, r, mid + 1, mr, k);
      push(x);
    }
  }
  
  tp query(tp x, tp l, tp r, tp ml, tp mr) {
    if (l <= ml && mr <= r) return val[x];
    else {
      tp mid = ml + mr >> 1, ans = 0;
      pull(x, ml, mr);
      if (l <= mid) ans += query(x << 1, l, r, ml, mid);
      if (r > mid) ans += query(x << 1 | 1, l, r, mid + 1, mr);
      return ans % mod;
    }
  }
} tre;

// Typedeves

// Variables
tp n, ans;

// Arrays
stack<tp> stk;
mray<tp, Hat_N> lg, pmav;
mray<mray<tp, 17>, Hat_N> st;

// Functions
void MIST() {
}

// :/

tp gcd(tp a, tp b) { return !b ? a : gcd(b, a % b); }

void STP() {
  tp k = log2(n / 2) + 1;
  lg[1] = 0;
  for (tp i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
  for (tp j = 1; j <= k; ++j) {
    for (tp i = 1; i + (1ll << j) - 1 <= n; ++i) st[i][j] = gcd(st[i][j - 1], st[i + (1ll << j - 1)][j - 1]);
  }
}

tp sgcd(tp l, tp r) {
  tp k = lg[r - l + 1];
  return gcd(st[l][k], st[r - (1ll << k) + 1][k]);
}

void calc(tp x, tp h) {
  if (x <= 0) return;
  tp l = 1, r = x - 1, g = sgcd(x, h);
  while (l <= r) {
    tp mid = l + r >> 1;
    if(sgcd(mid, h) == g) r = mid - 1;
    else l = mid + 1;
  }
  ans = (ans + tre.query(1, l, x, 1, n) * g) % mod;
  calc(l - 1, h);
}

void STRUGGLING([[maybe_unused]] tp TEST_NUMBER) {
  cin >> n;
  tre.build(1, 1, n);
  for (tp i = 1; i <= n; ++i) cin >> st[i][0];
  for (tp i = 1; i <= n; ++i) {
    while (stk.size() && st[stk.top()][0] < st[i][0]) stk.pop();
    pmav[i] = stk.empty() ? 1 : stk.top() + 1;
    stk.push(i);
  }
  STP();
  for (tp i = 1; i <= n; ++i) {
    tre.modify(1, pmav[i], i, 1, n, st[i][0]);
    calc(i, i);
  }
  cout << ans << '\n';
}

#include <fstream>

signed main() {
  tp t = 0, _t = 1;
  cin.tie(0)->sync_with_stdio(0);
#if !_CONSOLE
#ifdef _LOCAL
  static ifstream _in("input.in");
  cin.rdbuf(_in.rdbuf());
#else
#ifdef EFILE
  static ifstream _in(EFILE ".in");
  static ofstream _out(EFILE ".out");
  cin.rdbuf(_in.rdbuf());
  cout.rdbuf(_out.rdbuf());
#endif
#endif
#endif
  // cin >> _t;
  MIST();
  while (t < _t) STRUGGLING(++t);
  return 0;
}

//*/
```

---

## 作者：dAniel_lele (赞：1)

解法 1：

观察到一个简单的性质：$\gcd(a_i),\gcd(a_i,a_{i+1}),\dots,\gcd(a_i,a_{i+1},\dots,a_n)$ 中只有 $O(\log V)$（$V$ 为值域）种不同的值。于是可以暴力 $O(\log^2V)$ 维护。

考虑 $\max$，显然可以用单调栈+线段树解决。

于是总复杂度是 $O(n(\log^2V+\log n))$。

---

解法 2：

考虑建出笛卡尔树。于是我们要对每个子树维护上面所说的 $O(\log V)$ 个值。合并是 $O(\log^2V)$ 的，而统计答案时需要枚举左右端点分别在哪里，暴力可以 $O(\log^3V)$，适当优化可以 $O(\log^2V)$。

---

只写了解法 1 的代码。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
struct sgt{
	int f[1000005],lzt[1000005];
	void pushdown(int i,int l,int r){
		(f[i*2]+=lzt[i]*(mid-l+1))%=mod;
		(lzt[i*2]+=lzt[i])%=mod;
		(f[i*2+1]+=lzt[i]*(r-mid))%=mod;
		(lzt[i*2+1]+=lzt[i])%=mod;
		lzt[i]=0; 
	}
	void change(int i,int l,int r,int ql,int qr,int cg){
		if(ql<=l&&r<=qr){
			(lzt[i]+=cg)%=mod;
			(f[i]+=(r-l+1)*cg)%=mod;
			return ;
		}
		pushdown(i,l,r);
		if(ql<=mid) change(i*2,l,mid,ql,qr,cg);
		if(qr>mid) change(i*2+1,mid+1,r,ql,qr,cg);
		f[i]=(f[i*2]+f[i*2+1])%mod;
	}
	int qry(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return f[i];
		if(ql>r||qr<l) return 0;
		pushdown(i,l,r);
		return (qry(i*2,l,mid,ql,qr)+qry(i*2+1,mid+1,r,ql,qr))%mod;
	}
}tree;
int smax[200005],pmax[200005],top1;
int lpos[200005],rpos[200005],rg[200005],top2;
signed main(){
	int n; cin>>n;
	int a[n+1],ans=0; for(int i=1;i<=n;i++) cin>>a[i];
	pmax[0]=n+1;
	for(int i=n;i>=1;i--){
		while((top1)&&(smax[top1]<a[i])){
			tree.change(1,1,n,pmax[top1],pmax[top1-1]-1,a[i]-smax[top1]);
			top1--;
		}
		smax[++top1]=a[i],pmax[top1]=i;
		tree.change(1,1,n,i,i,a[i]);
		top2++; lpos[top2]=rpos[top2]=i,rg[top2]=a[i];
		for(int j=1;j<=top2;j++) rg[j]=__gcd(rg[j],a[i]);
		int top3=0;
		for(int j=1;j<=top2;j++){
			if(rg[j]!=rg[top3]){
				rg[++top3]=rg[j];
				lpos[top3]=lpos[j];
				rpos[top3]=rpos[j];
			}
			else{
				lpos[top3]=lpos[j];
			}
		}
		top2=top3;
		for(int j=1;j<=top2;j++){
			(ans+=tree.qry(1,1,n,lpos[j],rpos[j])*rg[j])%=mod;
		}
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：ZepX_D (赞：0)

来个跑得飞快的 $O(n\log^2 n\log v)$ 写法。

对于区间最大值，我们考虑极值分治，每次选定区间 $[l,r]$ 内的最大值的位置（多个相同值选任意一个）为分治中心，统计跨过当前分治中心的所有区间的贡献。

设分治中心为 $mid$。
* 若 $mid-l<r-mid$，那么我们扫左区间，枚举左区间每个点为左端点，处理右端点在 $[mid,r]$ 中的区间贡献。具体的，用 ST 表预处理区间 $\gcd$，然后二分出 $\gcd$ 相同的段，统计贡献的话就是对满足 $\forall r\in [x,y],\gcd(l,r)=k$ 的一段，它的贡献是 $(y-x+1)k\times a_{mid}$。
* 若 $r-mid<mid-l$ 同理。

分析一下时间复杂度，一个数被扫一遍区间长度至少乘二，所以每个数至多被扫 $\log n$ 次，枚举一个数作为端点时统计贡献时，ST 表+二分的时间复杂度为 $O(\log n\log v)$，总时间复杂度为 $O(n\log^2 n\log v)$。


```cpp
#include <bits/stdc++.h>
#define fr first
#define se second
#define Un unsigned
#define LL long long
#define pb push_back
#define pii pair<int,int>
#define pLi pair<LL,int>
#define pLL pair<LL,LL>
#define __ __int128
#define LD long double
#define VE vector<LL>
#define DB double
#define Ve vector<int>

using namespace std;

inline int read()
{
	int x = 0,f = 1;char ch = getchar();
	while(!isdigit(ch)) (ch == '-') && (f = -1),ch = getchar();
	while(isdigit(ch)) x = x*10+ch-48,ch = getchar();
	return x*f;
}

const int N = 2e5+5,P = 1e9+7;
int a[N],f[18][N];
pii mx[18][N];

inline int Q1(int l,int r)
{
	int k = __lg(r-l+1);
	return __gcd(f[k][l],f[k][r-(1<<k)+1]);
}
inline int Q2(int l,int r)
{
	int k = __lg(r-l+1);
	return max(mx[k][l],mx[k][r-(1<<k)+1]).se;
}
inline int G1(int k,int i,int l,int r)
{
	while (l < r)
	{
		int mid = (l+r+1)>>1;
		if (Q1(i,mid) == k) l = mid;
		else r = mid-1;
	}
	return l;
}
inline int G2(int k,int i,int l,int r)
{
	while (l < r)
	{
		int mid = (l+r)>>1;
		if (Q1(mid,i) == k) r = mid;
		else l = mid+1;
	}
	return l;
}
LL ans;
void solve(int l,int r)
{
	if (l > r) return ;
	LL res = 0;
	int mid = Q2(l,r);
	if (mid-l < r-mid)
	{
		for (int i = l;i <= mid;i++)
		{
			for (int j = mid;j <= r;)
			{
				int k = Q1(i,j),nxt = G1(k,i,j,r);
				res += 1LL*(nxt-j+1)*k,j = nxt+1;
			}
		}
	}
	else
	{
		for (int i = mid;i <= r;i++)
		{
			for (int j = mid;j >= l;)
			{
				int k = Q1(j,i),pre = G2(k,i,l,j);
				res += 1LL*(j-pre+1)*k,j = pre-1;
			}
		}
	}
	ans = (ans+res%P*a[mid])%P;
	solve(l,mid-1),solve(mid+1,r);
}

int main()
{
	int n = read();
	for (int i = 1;i <= n;i++)
		f[0][i] = a[i] = read(),mx[0][i] = {a[i],i};
	for (int i = 1;i <= __lg(n);i++)
		for (int j = 1;j+(1<<i)-1 <= n;j++)
			f[i][j] = __gcd(f[i-1][j],f[i-1][j+(1<<(i-1))]),
			mx[i][j] = max(mx[i-1][j],mx[i-1][j+(1<<(i-1))]);
	solve(1,n),printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Mu_leaf (赞：0)

笛卡尔树分治练手好题。

~~就是又卡时间又卡空间的。~~

## [思路]

需要最大值，很容易联想到笛卡尔树分治。区间 gcd 还有个不错的性质，那就是每次变化后的值一定小于当前值的一半，自然 gcd 不同的个数最多也就 $\log_{n}$ 个了。

考虑二分到当前值后面第一个 gcd 不同的下标，在这里定义 $L_{i,j}$，$R_{i,j}$ 表示以第 $i$ 个点为左端点，第 $j$ 个不同的 gcd 区间的左右端点，则如果笛卡尔树分治的左区间小于右区间则当前点 $i$ 对答案的贡献就是。

$$ a_{pos}\times G_{i,j}\times (\min(r,R_{i,j})-\max(pos,L_{i,j})+1)$$

其中 $G_{i,j}$ 表示以第 $i$ 个点为左端点，第 $j$ 个区间的 gcd。pos 表示当前区间最大值的下标。

右区间小于左区间同理。

- 注意本题内存限制较小，可以考虑左区间大于右区间的情况和右区间大于左区间的情况分开处理，这样一个数组就可以重复使用。
- 不要开 long long。
- 理论复杂度是 $O(n \log^2 n)$ 所以需要用线段树或 ST 表预处理出最大值的下标，区间 gcd，还有 $L_{i,j}$ 和 $R_{i,j}$。

--------
马蜂很丑，细节问题可以参考一下。

## Code:


```cpp
#include<bits/stdc++.h>
//#define int long long 
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){char ch=getch();while(ch<'a'||ch>'z')ch=getch();while(ch>='a'&&ch<='z'){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
const int N=2e5+5,mod=1e9+7;
int ans,lg[N];
int n;
struct kkk{
	int first,second,G;
};
vector<kkk> nxt[N];
int a[N];
namespace SGT{
	#define ls (x<<1)
	#define rs (x<<1|1)
	#define mid ((l+r)>>1)
	struct Tree{
		int id;
	}tr[N*4];
	int merge(int l,int r){
		if(a[l]>a[r]) return l;
		return r;
	}
	void pushup(int x){
		tr[x].id=merge(tr[ls].id,tr[rs].id);
	}
	void build(int x,int l,int r){
		if(l==r){
			tr[x].id=l;
			return;
		}
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(x);
	}
	int query(int x,int l,int r,int lt,int rt){
		if(l>=lt && r<=rt){
			return tr[x].id;
		}
		int ans=0;
		if(lt<=mid) ans=query(ls,l,mid,lt,rt);
		if(rt >mid) ans=merge(ans,query(rs,mid+1,r,lt,rt));
		return ans;
	}
}
namespace ST{
	int G[N][19];
	void init(){
		for(int j=1;j<=18;j++){
			for(int i=1;i<=n && i+(1<<(j-1))<=n;i++){
				G[i][j]=__gcd(G[i][j-1],G[i+(1<<(j-1))][j-1]);
			}
		}
	}
	int query(int l,int r){
		int k=lg[r-l+1];
		return __gcd(G[l][k],G[r-(1<<k)+1][k]);
	}
}
void Mod(int &x){
	if(x>=mod) x-=mod;
}

void lsolve(int l,int r){
	if(l>r) return;
	if(l==r){
		Mod(ans+=1ll*a[l]*a[l]%mod);
		return;
	}
	int pos=SGT::query(1,1,n,l,r);
	lsolve(l,pos-1);lsolve(pos+1,r); 
	if(pos-l<=r-pos){
		for(int i=l;i<=pos;i++){
			for(int j=0;j<nxt[i].size();j++){
				if(!nxt[i][j].first) break;
				if(nxt[i][j].second>=pos && nxt[i][j].first<=r){
					Mod(ans+=(1ll*a[pos]*nxt[i][j].G%mod*(min(r,nxt[i][j].second)-max(pos,nxt[i][j].first)+1)%mod));
				}
			}
		} 
	}
}
void rsolve(int l,int r){
	if(l>=r) return;
	int pos=SGT::query(1,1,n,l,r);
	rsolve(l,pos-1);rsolve(pos+1,r); 
	if(pos-l>r-pos){
		for(int i=pos;i<=r;i++){
			for(int j=0;j<nxt[i].size();j++){
				if(!nxt[i][j].first) break;
				if(nxt[i][j].first<=pos && nxt[i][j].second>=l){
					Mod(ans+=(1ll*a[pos]*nxt[i][j].G%mod*(min(pos,nxt[i][j].second)-max(l,nxt[i][j].first)+1)%mod));
				}
			}
		}
	}
}
signed main(){
	read(n);
	for(int i=2;i<=n;i++){
		lg[i]=lg[i/2]+1;
	}
	for(int i=1;i<=n;i++){
		read(a[i]);
		ST::G[i][0]=a[i];
	}
	SGT::build(1,1,n);
	ST::init();
	int p,cnt;
	for(int i=1;i<=n;i++){
		p=i,cnt=0; 
		while(p<=n){
			int l=p,r=n,res=p;
			while(l<=r){
				int md=l+r>>1;
				if(ST::query(i,md)<ST::query(i,p)) r=md-1;
				else res=md,l=md+1;
			}
			nxt[i].push_back((kkk){p,res,ST::query(i,res)});
			p=res+1;
		}
	}
	lsolve(1,n);
	for(int i=1;i<=n;i++) nxt[i].clear();
	for(int i=n;i>=1;i--){
		p=i,cnt=0;
		while(p>=1){
			int l=1,r=p,res=p;
			while(l<=r){
				int md=l+r>>1;
				if(ST::query(md,i)<ST::query(p,i)) l=md+1;
				else res=md,r=md-1;
			}
			nxt[i].push_back((kkk){res,p,ST::query(res,i)});
			p=res-1;
		}
	}
	rsolve(1,n);
	write(ans);
	flush();
}
/*
1 1 1 1
2 1 1
*/

```

---

