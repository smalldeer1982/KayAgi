# CGCDSSQ

## 题目描述

Given a sequence of integers $ a_{1},...,a_{n} $ and $ q $ queries $ x_{1},...,x_{q} $ on it. For each query $ x_{i} $ you have to count the number of pairs $ (l,r) $ such that $ 1<=l<=r<=n $ and $ gcd(a_{l},a_{l+1},...,a_{r})=x_{i} $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF475D/57fa10a542946ca7729b1feeb84648963b002c6d.png) is a greatest common divisor of $ v_{1},v_{2},...,v_{n} $ , that is equal to a largest positive integer that divides all $ v_{i} $ .

## 样例 #1

### 输入

```
3
2 6 3
5
1
2
3
4
6
```

### 输出

```
1
2
2
0
1
```

## 样例 #2

### 输入

```
7
10 20 3 15 1000 60 16
10
1
2
3
4
5
6
10
20
60
1000
```

### 输出

```
14
0
2
2
2
0
2
2
1
1
```

# 题解

## 作者：XieXuan (赞：21)

显然，这是一道st表优化gcd的题目。

st表:[史上最烂st表教程](https://5210-ac-hunter.blog.luogu.org/st-biao)

题目用人话说就是：
输入一个整数序列，多次询问，每次给出x，问你序列中有多少个区间，满足区间内所有数的最大公约数为x  。数列中数的个数≤$10^{5}$，询问次数≤3×$10^{5}$，数的范围=$10^{9}$  。


解法：

用st表维护各个区间的gcd。

注意：并不是区间的询问，只有整体的询问

注意：求两个数的gcd的时间复杂度为O(log U)

而如果l固定，而只有r发生变化时，gcd⁡($a_{l}$,$a_{l+1}$,…,$a_{r}$ )的不同取值至多只有O(log U)种。
	证明：如果gcd⁡($a_{l}$,$a_{l+1}$,…,$a_{r}$ )发生了变化，那么变化后的gcd值一定是变化前gcd值的约数这说明：如果变化了，起码会缩小一半，所以至多缩小O(log U)次。

只有O(n log U)种x的询问结果不为0，我们可以在所有询问之前，预处理出一个O(n log U)的表，对于每次询问直接查表，使用哈希表，可以做到每次询问O(1)处理；最简单的还是用STL的map了，每次O(log n)，反正时间限制没有那么紧

考虑刚才证明O(n log U)这个上界的思路，枚举l，如果我们能快速找到gcd⁡($a_{l}$,$a_{l+1}$,…,$a_{r}$ )发生变化的r和对应的gcd值，就可以快速处理答案了

换言之，要解决的问题是：给出l和r0，求最小的$r_{1}$ 使得gcd⁡($a_{l}$,$a_{l+1}$,…,$a_{r0}$)≠gcd⁡($a_{l}$,$a_{l+1}$,…,$a_{r1}$) ，或得出不存在

如果假设给出l和$r_{0}$，能在T的时间内求最小的$r_{1}$ 和对应的gcd值


则我们得到算法流程如下：


从1到n枚举l：

·初始值$r_{0}$=l

·重复直到$r_{0}$>n：
    
·求出最小的r1 （如果不存在，则令$r_{1}$=n+1）
        
·记录：gcd⁡($a_{l}$,$a_{l+1}$,…,$a_{r0}$)出现了$r_{1}$−$r_{0}$ 次
        
·更新$r_{0}$=$r_{1}$
        
        
则我们可以在O(n T log U)的时间内完成预处理

给出l和$r_{0}$，求最小的r1 (二分$r_{1}$在哪里，上ST表里查询答案)使得gcd⁡($a_{l}$,$a_{l+1}$,…,$a_{r0}$)≠gcd($a_{l}$,$a_{l+1}$,…,$a_{r1}$)，或得出不存在
注意gcd($a_{l}$,$a_{l+1}$,…,$a_{r0}$)是已知的（先设它为g），不需要重新求了

总时间复杂度：O(n log n log U + q log n)
```cpp
#include <cstdio>
#include <map>
#define maxn 100010
#define Maxn 300030
using namespace std;
typedef unsigned long long ll;
map<int,ll> ans;//被询问的没一个数对应的答案 
int n,q,u,a[maxn],st[maxn][21],que[Maxn],sqr[maxn],logo[maxn];
//a[]数列，st[][]st表，que[]询问的数，sqr[]预处理出各数的2次方，logo[]预处理处各数对2取的对数 
inline int read()
{
    char c=getchar();int num=0;
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9')
    {
        num=num*10+c-'0'; 
        c=getchar();
    }
    return num;
}
inline int gcd(int x,int y)//使用gcd的递推式有利于降低时空复杂度 
{
    int tmp;
    while(y)
    {
        tmp=y;
        y=x%y;
        x=tmp;
    }
    return x;
}
inline void pre()//预处理 
{
    sqr[0]=1;
    for(int i=1;i<20;i++)
    sqr[i]=sqr[i-1]<<1;//预处理出各数的2次方，常数优化 
    logo[0]=-1;
    for(int i=1;i<=n;i++)
    logo[i]=logo[(i>>1)]+1;//预处理出各数对2取的对数，常数优化 
    for(int i=1;i<=n;i++)
    st[i][0]=a[i];//st表预处理，边界条件 
    for(int j=1;j<20;j++)//先枚举j 
    for(int i=1;i+sqr[j]-1<=n;i++)//防止爆数组 一定注意这里i+sqr[j]-1<=n的-1很重要
    st[i][j]=gcd(st[i][j-1],st[i+sqr[j-1]][j-1]);//st表预处理
}
inline int question(int l,int r)//常规的st表查询 
{
    int N=logo[r-l+1];
    return gcd(st[l][N],st[r-sqr[N]+1][N]); 
}
inline int found(int l,int newl,int g) 
//l（固定）到newl的gcd是g，求newl到r的gcd也是g的r的最小值 
{
    int r=n,anss=0;//先假设区间右端点在n处 
    while(r>=newl) //大于等于而非大于 
    {
        int mid=(newl+r)>>1;//二分查找 
        if(question(l,mid)==g)//如果mid的左面的最大公约数都是g，那么左面一定不用看了 ，直接看右面就行了
        anss=mid,newl=mid+1;//所以ans先变成mid，将区间左端点放到mid+1来检测下面还有多长的区间gcd也是g 
        else r=mid-1;//如果mid左面最大公约数不是g就缩小一下区间宽度，找到符合题目要求的r的最大值 
    }
    return anss;
}
inline void solve(int l)//l是主函数枚举出的左端点l.  
{
    int last,nowright=l,t=a[l];//nowright是根据左端点不断枚举出的右端点r1，刚开始右端点就是它本身，last是上一个右端点,last可以充当r0。t就是gcd值，题解解释中的g
    //t表示该序列最大公因数，t先是左端点本身的数字，是t能形成的最大公因数的最大值 
    while("我喜欢李靖妍")
    {
        last=nowright;
        nowright=found(l,nowright,t);//令当前左端点l到右端点最大公因数改变的新的右端点 
        if(ans[t])//如果这个最大公因数被询问了，就要计算它 
        ans[t]+=nowright-last+1;//从上一个右端点到这一个右端点最大公因数并没有改变，所以这些都是答案。直接加上这一区间 
        if(nowright==n) return; //如果枚举完了所有右端点，就返回 
        nowright++;//枚举下一个右端点 
        t=question(l,nowright);//从左端点到右端点的新的最大公因数 
    } 
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    a[i]=read();
    q=read();
    for(int i=1;i<=q;i++)
    que[i]=read(),ans[que[i]]=1;//先表示是否存在，最后-1输出答案 
    pre();//预处理 
    for(int i=1;i<=n;i++)
    solve(i);//枚举出左端点 
    for(int i=1;i<=q;i++)
    printf("%lld\n",ans[que[i]]-1);
    return 0;
}

```


---

## 作者：BigJoker (赞：9)

# 前言

这题挺有意思。先开始题读错了，想了半天。其实细细看来还挺妙的，做法的复杂度有点奇怪。

# 思路

* **Solution1**

对于每一次询问考虑暴力。直接枚举，复杂度 $O(m\ n^2)$，很明显过不了。

* **Solution2**

用一个 `map` 将所有公约数的个数的值存下来，然后查询直接输出。很显然过不了。

* **Solution3**

考虑对上述做法进行优化，很明显，我们的用 `map` 的想法一定是对的，不过对于增添个数可以考虑进行优化。

我们可以发现，对于 $\gcd$ 来说，当操作的数越来越多，$\gcd$ 的值是呈**不上升**的，也就是单调的，对于单调的序列，不难想到二分算法。那么做法也就水落石出了。

考虑固定**左端点**，即使用一层循环枚举左端点。然后二分枚举**当前的最大公约数**最大能维持到哪里。

我们结合实际来看一下：

这是我们的原序列 $a$：$12,16,8,4,2,1$

按照我们的想法，先固定左端点 $12$。

这里为了方便理解，我们将以 $12$ 为左端点的 $\gcd$ 序列搞出来看一下。

$12,4,4,4,2,1$

可以观察到此时的 $\gcd$ 序列是单调递减的，并且相同的 $\gcd$ 值是连续的。

那么，对于任意的 $\gcd$ 的值来说，只要确定了其左端点和右端点，就可以确定它的数量了。

对于这个 $\gcd$ 值我们使用 `map` 存下来就可以了。

相信会思考的同学就会想了：这个 $\gcd$ 的值万一全都不同，岂不是直接起飞？

对于这个，其实有一个性质，那就是：

$\gcd$ 的值每次递减起码缩小一倍，也就是除以 $2$。

这个肯定十分好想，不需要过多阐述，如果需要严格的证明也可以自行百度。

不难看出算法当中需要区间 $\gcd$，对于这个我们可以用 `st表`。

接下来我们算一下时间复杂度：

$O(n\log^2n\log K)$

$K$ 是值域大小，最大为 $10^9$

大概算出来 $8\times 10^8$。

数据水一点应该过得去。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m;
int dp[N][20];
map<int,long long>q;
int Get_Gcd(int l,int r){
	int k=log2(r-l+1);
	return __gcd(dp[l][k],dp[r-(1<<k)+1][k]);
}
int f(int k,int l,int r,int c){
	if(l==r) return l;
	if(l+1==r){
		if(Get_Gcd(k,r)==c) return r;
		return l;
	}
	int mid=(l+r)/2;
	if(Get_Gcd(k,mid)==c) return f(k,mid,r,c);
	else return f(k,l,mid-1,c);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&dp[i][0]);
	for(int j=1;j<=19;j++)
		for(int i=1;i+(1<<j)-1<=n;i++) dp[i][j]=__gcd(dp[i][j-1],dp[i+(1<<j-1)][j-1]);
	for(int i=1;i<=n;i++){
		int l=i;
		while(l<=n){
			int r=f(i,l,n,Get_Gcd(i,l));
			q[Get_Gcd(i,l)]+=(r-l+1);
			l=r+1;
		}
	}
	scanf("%d",&m);
	while(m--){
		int x;
		scanf("%d",&x);
		printf("%lld\n",q[x]);
	} 
	return 0;
}
```

---

## 作者：drophell (赞：7)


暴力枚举区间的左端点，随着右端点的二分移动(在保证与现有gcd相等情况下尽量右移)，区间gcd最多变化log次

那么只要通过二分找出这log个区间即可

至于区间gcd询问，我本来用线段树，后来发现多一个log被卡常了，只能%hzwer的st表了。

顺便分享个知识：

段数长度越长，gcd越小，且严格单调递减。

由于gcd(a，b)==a或者 $\leq \frac{a}{2}$ ,

而且int类型在$2^{31}$以内，所以可以肯定一个数最多有31个gcd（每次减少至少一个素因子）。所以可以用dp也。

```cpp

#include<set>
#include<map>
#include<ctime>
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
#define ll long long 
const int MAXN=300000+50;
int n,m,bin[20],Log[MAXN],f[MAXN][20],a[MAXN],x[MAXN];

map<int ,ll>ans;

int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
void pre()
{
	bin[0]=1;
	for(int i=1;i<20;i++)bin[i]=bin[i-1]<<1;
	Log[0]=-1;
	for(int i=1;i<=n;i++)Log[i]=Log[i>>1]+1;
	for(int i=1;i<=n;i++)f[i][0]=a[i];
	for(int k=1;k<20;k++)
		for(int i=1;i<=n;i++)
			if(i+bin[k]-1<=n)//没这句话就会下标溢出
		    	f[i][k]=gcd(f[i][k-1],f[i+bin[k-1]][k-1]);
			else break;
}

int qry(int l,int r)
{
	int k=Log[r-l+1];
	return gcd(f[l][k],f[r-bin[k]+1][k]);
}
//左端点L到l的gcd=g，未知区间[l，n]的l，固定的左端点
int find(int g,int l,int L)
{
	int ans=0,r=n;//贪心地二分出右端点r
	while(l<=r)
	{
		int mid=(l+r)>>1;
		//使得[l-r]的gcd等于[L，l]的gcd
		if(qry(L,mid)==g)ans=mid,l=mid+1;
		else r=mid-1;
	}
	//返回右端点
	return ans;
}

void solve(int x)
{
	int lst,now=x,t=a[x];
	while(1)
	{
		lst=now;
		//find(gcd,l->n,L);
		now=find(t,now,x);
		//对于每一次扩大区间，gcd一定变小（/2）或等于原值，所以要不断更新t（当前L到l的gcd）
		if(ans[t])ans[t]+=now-lst+1;//这些位置代表的右端点与左端点L构成的区间都满足t（gcd），
		if(now==n)return ;
		now++;t=qry(x,now);//now（l右端点初始值）增加，那么[L,l]的gcd要重新求一下
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)scanf("%d",&x[i]),ans[x[i]]=1;//一开始当作访问与否
	pre();
	//枚举左端点;
	for(int i=1;i<=n;i++)solve(i);
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[x[i]]-1);
}
```

---

## 作者：Citnaris (赞：6)

# CF475D CGCDSSQ

**引理及证明**

* 引理：对于一个序列 $a_1\cdots a_n$ ，定义集合 $b=\{\gcd\{a_i,\cdots a_i\},\gcd\{a_i,\cdots a_{i+1}\},\cdots \gcd\{a_i,\cdots a_n\}\}$ ，$b$ 中的元素单调不加且其中至多有 $\log(\max\{a_i\cdots a_n\})$ 个不同的元素。

* 证明：我们记 $\gcd\{a_i\cdots a_j\}=g_j$ ，则显然对于任意 $j$ ， $g_j$ 满足 $1 \le g_j\le \max\{a_i\cdots a_j\}$ 且 $g_j|g_{j-1}(j>i)$ 。 所以，我们可以发现若 $g_j$ 相对于 $g_{j-1}$ 发生了变化，则 $g_j\le g_{j-1}\div 2$ 。所以变化的次数至多为 $\log(\max\{a_i\cdots a_n\})$ ，即至多有 $\log(\max\{a_i\cdots a_n\})$ 个不同的元素。

**分析**

显然，暴力会超时，所以我们采用 $\text{ST}$ 表（一种 $\mathcal{O}(n\log n)$ 预处理 $\mathcal{O}(1)$ 查询区间最值等信息的数据结构）表来存储 $\gcd$ ：

* 状态：记 $f_{i,j}$ 表示从下标为 $i$ 的的数开始，连续 $2_j$ 个数的 $\gcd$ 。

* 初值： $f_{i,0}=a_i(1\le i\le n)$ 。

* 转移： $f_{i,j}=\gcd\{f_{i,j-1},f_{i+2^{j-1},j-1}\}$ 。

* 查询 $[l,r]$ 的 $\gcd$ ： $\gcd\{f_{l,\log(r-l+1)},f_{r-2^{\log(r-l+1)}+1,\log(r-l+1)}\}$ 。

有了这些信息，我们只需要枚举起点 $i$ ，每次采用二分查找查询连续 $\gcd$ 相等且为 $m$ 的段的长度，将 $ans_m$ 加上这个连续段的长度即可。

**时间复杂度分析**

根据引理，我们知道对于同一个起点，不同的连续段的个数是 $\log$ 级的，故总复杂度为 $\mathcal{O}(n\log n)$ 。

**注意**

* 不开 $\text{long long}$ 见祖宗。

* 由于 $m$ 很大，所以需要 $\text{map}$ 进行映射。

**代码**

```cpp
#include <cstdio>
#include <map>
#include <algorithm>

using namespace std;

const int NR = 1e5 + 5;
const int MR = 20;

int n, f[NR][MR], a[NR], lg[NR], m; 
map < int, long long > mp;

int query(int x, int y)
{
    int tmp = lg[y - x + 1];
    return __gcd(f[x][tmp], f[y - (1 << tmp) + 1][tmp]);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
        f[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; ++j)
        for (int i = 1; i <= n; ++i)
            if (i + (1 << j) - 1 <= n)
                f[i][j] = __gcd(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]); // 预处理 ST 表
    lg[1] = 0;
    for (int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1; // 预处理 log
    for (int i = 1; i <= n; ++i)
    {
        int cur = i;
        while (cur <= n) // 当前位置
        {
            int val = query(i, cur);
            int l = cur, r = n;
            while (l < r) // 二分右端点
            {
                int mid = l + r >> 1; mid += 1;
                if (query(i, mid) != val) r = mid - 1;
                else l = mid;
            }
            mp[val] += l - cur + 1; // 加上长度
            cur = l + 1; // 更新当前左端点位置
        }
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
    {
        int p;
        scanf("%d", &p);
        printf("%lld\n", mp[p]);
    }
    return 0;
}
```

---

## 作者：cmwqf (赞：5)

这一题是个好题，具体的就是对于每一个以a[i]为结尾的区间，有一个递推式,设前以a[i-1]为结尾的区间的最大公约数为last_gcd：

sum[i][gcd(a[i],last_gcd)]+=sum[i-1][last_gcd];

其正确性显然：以a[i-1]为结尾的所有区间中，最大公约数为last_gcd的与a[i]的最大公约数必为gcd(a[i],last_gcd)，数量就可以相加。

另外，程序中map<ll,ll>::iterator it=sum[pre].begin(),it指的是sum[pre]中的元素地址，it->first是最大公约数，it->second是最大公约数中是it->first的个数；

由于sum只在i与i-1中转换，为了节省空间和时间，可以设成滚动数组，即sum[now]指目前需要修改的数组，sum[pre]是上一个数组。

上代码


------------

```
#include<cstdio>
#include<map>
using namespace std;
typedef long long ll;
const int maxN=100000 + 100;
int n,m;
ll a[maxN+1];
map<ll,ll> sum[2],ans;
int gcd(int x,int y)
{
	int r=x%y;
	while(r)	
	{
		x=y;y=r;r=x%y;
	}
	return y;
} 
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	int now=0,pre=1;
	for(int i=1;i<=n;i++)
	{
		sum[now].clear();
		sum[now][a[i]]=1;
		map<ll,ll>::iterator it=sum[pre].begin();
		while(it!=sum[pre].end())
		{
			sum[now][gcd(a[i],it->first)]+=it->second;
			it++;
		}
		it=sum[now].begin();
		while(it!=sum[now].end())
		{
			ans[it->first]+=it->second;
			it++;
		}
		pre=!pre;now=!now;
	}
	scanf("%d",&m);
	while(m--)
	{
		ll x;
		scanf("%lld",&x);
		printf("%lld\n",ans[x]);
	}
	return 0;
}
```



---

## 作者：yzc2005 (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF475D·)

引理：**对于一个数组 $a$，不同的 $gcd(1,i)$ 最多有 $log(maxval)$ 个。**

原因：如果 $gcd$ 变了，它必定是原来的 $gcd$ 的因数，因此至少减小到原来的 $\frac{1}{2}$ 。

直接预处理，以每个点作为左端点，每次用二分直接找出这 $log$ 个区间。因为没有修改，用st表维护，方便且高效。把答案存在map里。

最后对于每个询问直接输出即可。

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rint register int
#define fu(i, a, b) for(rint i = a, I = (b) + 1; i < I; ++i)
#define fd(i, a, b) for(rint i = a, I = (b) - 1; i > I; --i)
#define finish(x) return x, 0;

const int N = 1e5 + 5, K = 20;
int n, q, st[N][K], Log[N];
map<int, ll> ans;

inline void prework() {
	fu(i, 2, n) Log[i] = Log[i >> 1] + 1;
	fu(i, 1, n) scanf("%d", &st[i][0]);
	fu(k, 1, Log[n]) 
		fu(i, 1, n - (1 << k) + 1)
			st[i][k] = __gcd(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]); 
}

inline int query(int l, int r) {
	int k = Log[r - l + 1];
	return __gcd(st[l][k], st[r - (1 << k) + 1][k]);
}

inline int find(int g, int p, int l) {
	int r = n, ans;
	while(l <= r) {
		int mid = l + r >> 1;
		if(query(p, mid) == g) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	return ans + 1;
}

int main() {
	scanf("%d", &n); prework();
	fu(i, 1, n) {
		int pos = i;
		while(pos <= n) { 
			int lst = pos, g = query(i, pos);
			pos = find(g, i, pos);
			ans[g] += pos - lst;
		}
	}
	scanf("%d", &q); int a;
	while(q--) {
		scanf("%d", &a);
		printf("%lld\n", ans[a]);
	}
	return 0;
}
```




---

## 作者：惜时如金 (赞：3)

# 今天学习了分治之后，做ppt中间的一道题，没错，就是这道^_^  
## **首先**
### 我们先来看一下题，题目中让我们求的是一段区间的gcd为x的对数有多少。  
我们这样考虑一下，当我们的区间的数的个数越多，我们的gcd一定**不会**比原来的gcd大。  
所以，我们就可以的到一个单调不减gcd序列。
这样我们就可以预处理出所有的gcd，这样我们就可以直接的出答案。  
因为一个数x，它的gcd的个数一定不会超过$logx$，所以我们就可以进行分治，统计个数，分为左右两部分，两部分分别进行暴力计算，，对于中间的部分，由于两者的答案互不影响，所以我们使用乘法原理，这样，我们就可以计算出跨mid的答案。  
### 其实，这就是分治的思想的体现， 
就像这张图一样![](https://cdn.luogu.com.cn/upload/pic/65453.png )  
(~~看起来还是可以的吧~~)  
将所求的的问题划分为两部分，最后在反回的时候，将答案进行一系列的操作，最后求得答案。  
这就是分治在题中的思想运用。
代码:
```c++
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<map>
using namespace std;
template<typename type>
void scan(type &x){
    type f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}
int gcd(int a,int b){return !b?a:gcd(b,a%b);}
#define ll long long
const int N=1e5+7;
ll a[N],n,m;
vector <pair<int,int> >v[2];//分别记录左右两部分的答案
map <int,ll>ans;//统计答案
void solve(int l,int r){
    if(l==r){
        ans[a[l]]++;//如果l==r显然
        return ;
    }
    int mid=(l+r)>>1;
    solve(l,mid);solve(mid+1,r);
    v[1].clear();v[0].clear();
    int last=a[mid],now=a[mid],cnt=0;//统计左半部分
    for(int i=mid;i>=l;i--){
        now=gcd(now,a[i]);
        if(last!=now){//如果gcd有变化，进行更新
            v[0].push_back(make_pair(last,cnt));
            cnt=1;
            last=now;
        }else cnt++;//统计个数
    }v[0].push_back(make_pair(last,cnt));
    last=now=a[mid+1],cnt=0;
    for(int i=mid+1;i<=r;i++){//同理，右半部分
        now=gcd(now,a[i]);
        if(now!=last){
            v[1].push_back(make_pair(last,cnt));
            cnt=1;
            last=now;
        }else cnt++;
    }v[1].push_back(make_pair(last,cnt));
    for(int i=0;i<v[0].size();i++){
        for(int j=0;j<v[1].size();j++){//跨mid答案统计
            ans[gcd(v[0][i].first,v[1][j].first)]+=1LL*v[0][i].second*v[1][j].second;
        }
    }
}
int main(){
    scan(n);
    for(int i=1;i<=n;i++){
        scan(a[i]);
    }
    solve (1,n);
    scan(m);
    while(m--){
        int x;
        scan(x);
        printf("%lld\n",ans[x]);
    }
}
```
这道题就讲到这里了，有什么问题希望大家可以提出。  
最后，安利一波博客  
# [进来看看呗^_^](https://www.cnblogs.com/xishirujin/)

---

## 作者：MILLOPE (赞：2)

## 题目

[题目传送门](https://www.luogu.org/problemnew/show/CF475D)

给出一个长度为$n(1<=n<=10^{5})$的序列和$q(1<=q<=3*10^{5})$个询问,每个询问输出一行,询问$gcd(a_l,a_{l+1},\cdots,a_r)=x$的$(i,j)$的对数.


## 题解
- 大佬给我们讲分治时用的例题，我这种不会分治的cb赶紧去学了一下，发现这道题真的非常妙$qwq$
- 首先如果我们固定一个左端点，那么在右端点移动的过程中$\gcd$一定是单调不增的，而如果$\gcd$出现变化时，它一定至少变了$2$，所以$\gcd$的变化是$\log$级别的，那么这样我们就可以预处理出每个区间的$\gcd$。~~ST表好啊[蒟蒻的ST表讲解qwq](https://blog.csdn.net/qq_34493840/article/details/89305417)~~
- 预处理出每个$\gcd$之后，我们就可以以$1$~$n$的每个点为左端点，二分查找最短的与左端点$\gcd$相同的右端点，用$map$记录此段区间个数，一直处理到$R=n$;这样我们就能得出题目要求的区间了。

## $code$
```cpp
#include <bits/stdc++.h> 
using namespace std; 
#define maxn 101000
typedef long long LL; 

template <typename T> 
inline void read(T &s) {
	s = 0; 
	T w = 1, ch = getchar(); 
	while (!isdigit(ch)) { if (ch == '-') w = -1; ch = getchar(); }
	while (isdigit(ch)) { s = (s << 1) + (s << 3) + (ch ^ 48); ch = getchar(); }
	s *= w; 
}

int n, m; 
int a[maxn], lg[maxn], q[maxn]; 
int f[maxn][25]; 
map <int, LL> ans; 

inline int gcd(int x, int y) { return y ? gcd(y, x % y) : x; } 

inline void pre_work() { // 预处理gcd
	lg[0] = -1; 
	for (int i = 1; i <= n; ++i) {
		lg[i] = lg[i >> 1] + 1, f[i][0] = a[i]; 
	}
	for (int j = 1; j <= 20; ++j) {
		for (int i = 1; i <= n - (1 << (j - 1)) + 1; ++i) {
			f[i][j] = gcd(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]); 
		}
	}
}

inline int query(int l, int r) { // 查询
	int t = lg[r - l + 1]; 
	return gcd(f[l][t], f[r - (1 << t) + 1][t]); 
}

void solve(int x) { // x 为固定的左端点
	int L = x, R = x; 
	while (R <= n) {
		int left = L, right = n; 
		int g = query(x, L); 
		while (left <= right) {
			int mid = (left + right) >> 1; 
			if (query(x, mid) == g) left = mid + 1; 
			else right = mid - 1; 
		}
		R = left; 
		ans[g] += (LL)R - L; 
		L = R; 
	}
} 

int main() {
	read(n); 
	for (int i = 1; i <= n; ++i) read(a[i]); 
	
	pre_work(); 
	
	for (int i = 1; i <= n; ++i) solve(i); // 处理左端点

	read(m); 
	for (int i = 1; i <= m; ++i) {
		int x; read(x); 
		printf("%lld\n", ans[x]); 
	}
	return 0; 
}

```

---

## 作者：Mr_Leceue (赞：1)

~~分治例题~~

在一个区间中，不断二分，处理区间和跨区间问题，即是分治，而重点就是计算出跨区间的个数；

这道题中，由于gcd是单调不加的，而一个数gcd最多有logn个，所以说最多有nlogn个，这个是我们可以接受的，离线预处理便提上了日程。

### **步骤**：
	1.不断二分，更新单个区间；
    2.每个区间计算出左右区间的连续gcd（因为左右区间要连在一起，所以左区间从mid向l更新），去重，累计个数（类似于手写离散化）。
    3.用左右区间的连续gcd匹配，并用乘法原理累加个数
    PS：连续gcd都是从mid或mid+1出发，思考其正确性（理解分治的一个关键）
#### **细节处理**
	1.由于数字太大，数组根本开不下，所以说巧用map很重要；
    2.用vector存区间gcd更加方便快捷；
    3.去重，累计个数时，思考以前写的离散化（用unique的除外）


### **Code**（有细节注释）
```
#include<bits/stdc++.h>
#define ll long long
#define maxn 300007
using namespace std;
int n,m,a[maxn];
vector<pair<int,int> >val[2];//方便（不过好像占空间大一些） 
map<int,ll>ans;//小技巧 

template<typename type_of_scan>
inline void scan(type_of_scan &x){
    type_of_scan f=1;x=0;char s=getchar();
    while(s<'0'||s>'9') f=s=='-'?-1:1,s=getchar();
    while(s>='0'&&s<='9') x=(x<<3)+(x<<1)+s-'0',s=getchar();
    x*=f;
}
int gcd(int a,int b){return !b?a:gcd(b,a%b);}
void solve(int l,int r){
	if(l==r){
		ans[a[l]]++;
		return ;
	}//单点更新 
	int mid=l+r>>1;
	solve(l,mid),solve(mid+1,r);//二分区间，分而治之 
	val[0].clear(),val[1].clear();
	int last=a[mid],now=last,cnt=0;//处理左区间 
	for(int i=mid;i>=l;i--){//从mid->l，因为要连接右区间 
		now=gcd(now,a[i]);//更新now 
		if(now!=last){
			val[0].push_back(make_pair(last,cnt));
			last=now,cnt=1;
		}else cnt++;//去重累加 
	}val[0].push_back(make_pair(last,cnt));//最后要加上last，思考why 
	last=now=a[mid+1],cnt=0;//处理右区间 
	for(int i=mid+1;i<=r;i++){
		now=gcd(now,a[i]);
		if(now!=last){
			val[1].push_back(make_pair(last,cnt));
			last=now,cnt=1;
		}else cnt++;
	}val[1].push_back(make_pair(last,cnt));//同左区间 
	for(int i=0;i<val[0].size();i++) 
		for(int j=0;j<val[1].size();j++)
			ans[gcd(val[0][i].first,val[1][j].first)]+=1ll*val[0][i].second*val[1][j].second;
	//匹配，累加 
}

int main(){
	scan(n);
	for(int i=1;i<=n;i++) scan(a[i]);
	solve(1,n);
	scan(m);
	for(int i=1,x;i<=m;i++){
		scan(x);
		printf("%lld\n",ans[x]);
	}
	return 0;
}
```
注意细节，否则wa了真的很难受。。。

---

## 作者：rainygame (赞：0)

来一篇不用任何数据结构、好写好调、时间复杂度为 $O(n\log^2 V)$ 的题解。

首先有结论，固定左端点 $l$，不同的 $r$ 构成的不同 $\gcd\{a_l, a_{l+1},\dots,a_r\}$ 只有 $O(\log V)$ 个，因为每次变化都至少会除以二。

考虑从后往前枚举 $l$，对于每个出现的 $x=\gcd\{a_l, a_{l+1},\dots,a_r\}$，用 `map` 维护最大的满足条件的 $r$ 即可，维护就只需要枚举前面的 `map`，然后和 $a_i$ 取 $\gcd$ 再添加进来即可。统计答案也是容易的。显然时间复杂度为 $O(n\log^2 V)$。

[submission](https://codeforces.com/contest/475/submission/313252916)

---

## 作者：刘嘉琦 (赞：0)

这题利用了 gcd 的性质。

我们可以发现，$\gcd_{i=1}^k a_i(k \in [1,n])$ 中不同的数其实很少，是 $\log n$ 级别的，因为每次多放一个数进来和原来的数一起取 gcd 时，gcd 要么不变，要么减小一半以上，所以最多达到 $\log n$ 个不同的数。

既然如此，我们就建立一个 map，其中索引 $x$ 对应 $a$ 数列中的 gcd 值为 $x$ 的区间个数。枚举区间左端点，通过二分右端点来依次找到每个 gcd 值的个数（当左端点固定时，gcd 值一定是单调不增的，所以相同的 gcd 值一定是连续的），并在 map 中记录。至于怎么查询 gcd 值，当然是用 ST 表最快。这样的记录是 $O(n \log^3 n)$ 的（枚举左端点 $O(n)$，不同 gcd 值 $O(\log n)$，二分右端点 $O(\log n)$，查询 gcd 值 $O(\log n)$）。

贴个代码：
```cpp
#include <cstdio>
#include <map>
namespace LJQ {
	template<typename T>
	T& read(T& s) {
		s = 0;
		T f = 1;
		char ch = getchar();
		while (ch < '0' || ch > '9') {
			if (ch == '-')
				f = -1;
			ch = getchar();
		}
		while ('0' <= ch && ch <= '9')
			s = s * 10 + ch - '0', ch = getchar();
		return s *= f;
	}
	template<typename T>
	inline T max(T x, T y) {
		return x > y ? x : y;
	}
	template<typename T>
	inline T min(T x, T y) {
		return x < y ? x : y;
	}
	template<typename T>
	inline void swap(T& x, T& y) {
		T tmp = x;
		x = y;
		y = tmp;
	}
} 
using namespace LJQ;

const int N = 100005;
int n, q, a[N];
int st[N][25], pw[25], log2[N];
std::map<int, long long> m; // n^2 级别的答案还是有必要开 long long 

int gcd(int x, int y) {
	if (x == 0)
		return y;
	return gcd(y % x, x);
}

void initST() {
	for (int i = 1; i <= n; i++)
		st[i][0] = a[i];
	for (int j = 1; pw[j] <= n; j++)
		for (int i = 1; i + pw[j] - 1 <= n; i++)
			st[i][j] = gcd(st[i][j - 1], st[i + pw[j - 1]][j - 1]);
}

void init() {
	pw[0] = 1;
	for (int i = 1; i <= 20; i++)
		pw[i] = pw[i - 1] << 1;
	log2[1] = 0;
	for (int i = 2; i <= n; i++)
		log2[i] = log2[i >> 1] + 1;
	initST();
}

int qry(int l, int r) {
	int j = log2[r - l + 1];
	return gcd(st[l][j], st[r - pw[j] + 1][j]);
}

int main()
{
	read(n);
	for (int i = 1; i <= n; i++)
		read(a[i]);
	init();
	for (int i = 1; i <= n; i++) { // 枚举左端点 
		int pos = i; // pos 为每个不同 gcd 值的起始位置 
		while (pos <= n) {
			int b = qry(i, pos), l = pos, r = n + 1;
			// 二分找到最后一个值为 b 的位置 
			while (l + 1 < r) {
				int mid = l + r >> 1;
				if (qry(i, mid) != b)
					r = mid;
				else
					l = mid;
			}
			m[b] += l - pos + 1;
			pos = l + 1;
		}
	}
	read(q);
	for (int i = 1; i <= q; i++) {
		int t;
		read(t);
		printf("%lld\n", m[t]);
	}
	return 0;
}
```

---

## 作者：Others (赞：0)

~~就差把预处理写在题面上了。~~

st 表~~模板~~。

预处理时每个 $l$ 肯定都要枚举到，固定好 $l$ 后就想找到 $\gcd(a_l,...,a_r)=now$ 的最远的 $r$，这东西显然是二分，因为 $\gcd$ 的序列肯定是非严格递减，然后这里介绍一个性质：

每次更新时这个 $now$ 至少降一半。简单的证一下：当前的是 $now$，更新过后肯定是 $now$ 的因数（~~好像就结束了~~）。

然后就推进右端点，算一下预处理的复杂度：枚举左端点 $O(n)$，二分右端点 $\times\gcd\times \log_2a_l\ \ \ \ O(\log_2^3n)$，总复杂度：$O(n\log_2^3n)$，理论计算爆掉了......实测是可以过的。

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename zqw>void qr(zqw &x){
	bool f=x=0;
	char c=getchar();
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
	x=f?~(x-1):x;
}
int st[100005][66],lo[100005],n,T,a[100005],m,l,r;
map<int,long long> mp;
int gcd(int x,int y){return x%y==0?y:gcd(y,x%y);}
int getgcd(int l,int r){return gcd(st[l][lo[r-l+1]],st[r-(1<<lo[r-l+1])+1][lo[r-l+1]]);}
int binary_search(int x,int p){
	int l=x,r=n,mid;
	while(r-l>1){
		mid=l+r>>1;
		if(getgcd(x,mid)>p) l=mid+1;
		else if(getgcd(x,mid)<p) r=mid-1;
		else l=mid;
	}
	if(l==r) return l;
	if(getgcd(x,r)==p) return r;
	else return l;
}
int main() {
		qr(n);
		for(int i=2;i<=n;i++) lo[i]=lo[i>>1]+1;
		for(int i=1;i<=n;i++){
			qr(a[i]);
			st[i][0]=a[i];
		}
		for(int i=1;(1<<i)<=n;i++){
			for(int j=1;j+(1<<i)-1<=n;j++){
				st[j][i]=gcd(st[j][i-1],st[j+(1<<i-1)][i-1]);
			}
		}
		for(int i=1;i<=n;i++){
			int Idx,idx=i,p=a[i];
			while(1){
				Idx=binary_search(i,p);
				if(mp.count(p)) mp[p]+=Idx-idx+1;
				else mp[p]=Idx-idx+1;
				idx=Idx+1;
				if(idx==n+1) break;
				p=gcd(p,a[idx]);
			}
		}
		qr(m);
		for(int i=1;i<=m;i++){
			qr(l);
			printf("%lld\n",mp[l]);
		}
	return 0;
}
```

---

## 作者：一只书虫仔 (赞：0)

#### Description

> 给定一个长为 $n$ 的序列 $a_i$，给定 $q$ 次询问，每次询问给定 $x$，求有多少组数对 $(l,r)$ 使得 $\gcd(a_l,a_{l+1},\cdots,a_r)=x$。

#### Solution

ST 表好题。

首先，我们先回答对于这道题引申出的两个问题：

1. 如何用 ST 表求解多次询问的区间 $\gcd$？这个应该比较简单，我们可以直接将求最值转化成求 $\gcd$，即下面这个式子是求多次询问的区间 $\max$ 的状态转移方程：

$$dp_{i,k} = \max(dp_{i,k-1}, dp_{i + 2^{k-1},k - 1})$$

我们可以直接将 $\max$ 替换成 $\gcd$，即：

$$dp_{i,k} = \gcd(dp_{i,k-1}, dp_{i + 2^{k-1},k - 1})$$

最后询问输出的时候也只需把 $\max$ 替换成 $\gcd$ 即可，原因很简单，因为 $\gcd$ 的性质和 $\max$ 相差无几，将一个区间拆分为互相重合的两段分别求解再用 $\gcd$ 连接也是可行的。

2. 一个长为 $n$ 的序列最多能有多少个不同的 $\gcd$？答案是 $n \log n$。

因此，我们可以先把这个序列的所有区间 $\gcd$ 用 ST 表预处理到 $dp$ 数组里，然后定义 $cnt_i$ 为截止到 $a_i$ 的答案，那么我们可以往右去寻找一个最大的 $l$ 使得 $\gcd(a_l,a_{l+1},\cdots,a_i)=a_i$，这个过程可以二分，然后再往前从 $l-1$ 开始继续寻找，然后不断的二分，替换答案，就可以预处理 $cnt_i$ 了。

因为 $\gcd$ 可能会很大，因此可以尝试用 map 处理 $cnt_i$。

最后对于 $q$ 组询问，每次输出 $cnt_x$ 即可。

---

## 作者：iiawaKL (赞：0)

###### ~~大佬~~写题解啦！！！
这题我自认为不太难。

题意：输入一个整数序列，多次询问，每次给出x，问你序列中有多少个区间，满足区间内所有数的最大公约数为x 。数列中数的个数≤10^5，询问次数≤3×10^5 ，数的范围=10^9。

思路：可以枚举右端点i，每次枚举gcd(a[0],a[1],....a[i])之前的所有可能的x,用一个map压进去，最后输出就行了。

代码见下->

```
#include<bits/stdc++.h> 
typedef long long ll;
using namespace std;
int a[100010];
map<int,long long> ans;
map<int,long long> mp;
map<int,long long> inv;
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++)cin>>a[i];
	for(int i=0;i<n;i++){
		mp.clear();
		for(map<int,long long>::iterator it=inv.begin();it!=inv.end();it++){
			mp[__gcd(it->first,a[i])]+=it->second;
		}
		mp[a[i]]++;
		swap(mp,inv);
		for(map<int,long long>::iterator it=inv.begin();it!=inv.end();it++){
			ans[it->first]+=it->second;
		}
	}
	int m;
	cin>>m;
	while(m--){
		int x;
		cin>>x;
		cout<<ans[x]<<endl;
	}
	return 0;
}
```


---

## 作者：桑树下的邂逅 (赞：0)

# **滚动数组+map容器**
sum[i][gcd(a[i],last_gcd)]+=sum[i-1][last_gcd];

其正确性显然：以a[i-1]为结尾的所有区间中，最大公约数为last_gcd的与a[i]的最大公约数必为gcd(a[i],last_gcd)，数量就可以相加。

另外，程序中map<ll,ll>::iterator it=sum[pre].begin(),it指的是sum[pre]中的元素地址，it->first是最大公约数，it->second是最大公约数中是it->first的个数；
```cpp
#define ll long long
#include<cstdio>
#include<map>
using namespace std;
const int maxN=100000+5;
ll n,a[maxN],m;
map<ll,ll>sum[2],ans;
int gcd(int x,int y){
	int r=x%y;
	while(r){
		x=y;
		y=r;
		r=x%y;
	}
	return y;
}
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
	ll now=0,pre=1;
	for(int i=1;i<=n;i++){
		sum[now].clear();
		sum[now][a[i]]=1;
		map<ll,ll>::iterator it=sum[pre].begin();
		while(it!=sum[pre].end()){
			sum[now][gcd(a[i],it->first)]+=it->second;
			it++;
		}
		it=sum[now].begin();
		while(it!=sum[now].end()){
			ans[it->first]+=it->second;
			it++;
		}
		now=!now;pre=!pre;
	}
	scanf("%lld",&m);
	while(m--){
		ll x;
		scanf("%lld",&x);
		printf("%lld\n",ans[x]);
	}
	return 0;
}
```

---

