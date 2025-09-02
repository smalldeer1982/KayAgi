# Zigzags

## 题目描述

给出 $n$ 个数 $a_1,a_2,\cdots,a_n$。求问有多少个四元组 $(i,j,k,l)$，使得这个四元组满足下列条件：

- $1 \leq i<j<k<l \leq n$；   
- $a_i=a_k$ 并且 $a_j=a_l$。

## 样例 #1

### 输入

```
2
5
2 2 2 2 2
6
1 3 3 1 2 3```

### 输出

```
5
2```

# 题解

## 作者：H6_6Q (赞：22)

### 翻译

给定一个长度为 $n$ 的序列 $a$ $( n\le 3000,a_i \le n )$ ，求有多少个四元组 $(i,j,k,l)$ 满足：

- $1 \le i < j < k < l \le n$
- $a_i=a_k$ 且 $a_j=a_l$

### 思路

看到 $n \le 3000$ ，所以可以确定复杂度最高是 $\text{O}(n^2)$ 的，故枚举时至多只能枚举两个变量。

那么枚举 $i,j,k,l$ 中的哪两个量能得到的信息最多呢？

- 当枚举 $i,j$ 时：

	能够得到满足条件时 $a_k$ 和 $a_l$ 的值，即 $a_k=a_i$，$a_l=a_j$ 。
    
    但是这样枚举无法得到 $k,l$ 的相对位置，不好满足条件 $k<l$，故不可行。
    
    枚举 $k,l$ 也是同理。
    
- 当枚举 $i,k$ 时：

	能够得到 $j,l$ 的相对位置，即 $j$ 在 $i\sim k$ 之间， $l$ 在 $k \sim n$ 之间。
    
    但是这样无法得到 $a_j$ 和 $a_l$ 的值，不好满足条件 $a_j=a_l$ ，故也不可行。
    
    枚举 $j,l$ 也是同理。
    
- 当枚举 $j,k$ 时：
	
    能够得到满足条件时 $a_i$ 和 $a_l$ 的值，即 $a_i=a_k$，$a_l=a_j$ 。
    
    同时也能够得到 $i,l$ 的相对位置，即 $i$ 在 $1\sim j$ 之间， $l$ 在 $k \sim n$ 之间。
    
    这显然是可行的。

那么我们可以枚举 $j,k$，这样只要统计一个前缀和，维护每个数在某个区间出现的个数，再根据乘法原理，就能 $\text{O}(1)$ 计算出当 $j,k$ 确定时的方案数。
    
由于 $a_i \le n$ ，故预处理前缀和的复杂度也是 $\text{O}(n^2)$ 的。
    
总时间复杂度  $\text{O}(n^2)$ 。
    
### Code
```
#include<bits/stdc++.h>
#define int long long

using namespace std;

int read()
{
	int ans=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}

const int N=3005;
int t,n,sum[N][N],a[N],ans;

signed main()
{
	t=read();
	while(t--)
	{
		n=read();
		for(int i=1;i<=n;++i)
		{
			a[i]=read();
			for(int j=1;j<=n;++j)
				sum[i][j]=sum[i-1][j];
			sum[i][a[i]]++;
			//统计每个数出现次数的前缀和 
		}
		ans=0;
		
		//枚举 j,k O(1) 计算答案 
		for(int j=2;j<=n;++j)
			for(int k=j+1;k<=n-1;++k)
				ans+=(sum[j-1][a[k]])*(sum[n][a[j]]-sum[k][a[j]]);
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：FerventTemp0 (赞：11)

这个题感觉 $O(n^2)$ 做法不是很优美，于是我就一直想着优化一下，今天终于把坑填了。

首先，假定一个数字 $b$，这个数字目前适合设置多大还不知道。将出现次数大于等于 $b$ 的数称为“多数”，将出现次数小于 $b$ 的数称为少数。

> 假设 $b=3$，则 `1 1 2 1 2 2 5 2 4` 中，$1$ 和 $2$ 是多数，$5$ 和 $4$ 是少数。

然后对答案贡献的来源进行分类讨论

--------------
首先，因为数量只有大于等于 $b$ 的数才能被称为多数，这意味着多数的数量至多为 $\frac{n}{b}$ 个。

题目要求为 $a_i=a_k$ 且 $a_j=a_l$，如果这四个数都是多数，最多只会有两个不同的多数，那么我们枚举所有的多数对，再将多数从原数列中提取出来。多数对的个数最多为 $\frac{n^2}{b^2}$，将多数对提取出来的计算量为 $b$，相乘得 $\frac{n^2}{b}$。

> 如果原数列为 `1 1 2 1 2 2 5 2 4`，当前枚举的多数对为 $(1,2)$，则提取后为 `1 1 2 1 2 2 2`。

然后我们惊喜的发现，如果一个数列只有两个数，那么计算这个数列的答案也可以做到线性复杂度！

因为数字的大小对答案没有影响，所以将只有两个数的数列改成 $01$ 数列，方便表示和计算。

首先，做一个指针，从左扫到右，同时维护：左边 $0$ 的个数，左边 $1$ 的个数，右边 $0$ 的个数，右边 $1$ 的个数，右边 $0\text{X}1$ 的个数，右边 $1\text{X}0$ 的个数。

对于单个位置做计算，随便维护一下就行了。

该部分虽然说着简单，但是代码写的有点难受，有要参考代码的可以看完整代码的 `calc11` 函数。

所以该部分复杂度为 $O(\frac{n^2}{b})$

---------------
然后就是 $a_i,a_j$ 中有一个或两个小数的情况。

首先，因为小数的个数最多为 $b$，所以小数对的个数最多为 $\frac{n}{b}\times b^2=nb$（容易证明）。

那么对于这么多个小数对进行莫队，然后查询符合条件的数对个数就行了。

如果 $a_i,a_j$ 都是小数，那么一个满足条件的四元组会被计算两次，而如果有一个是大数，就只会被计算一次，所以跑莫队的时候记得分开。

计算量为 $nb^2+\frac{n^2}{b}$（莫队 $l$ 和 $r$ 指针分别的移动次数）。

所以该部分复杂度为 $O(nb^2+\frac{n^2}{b})$，总复杂度也是这个

-------------

然后为了方便计算，上面两个情况计算时排除掉 $a_i=a_j$ 的情况，然后这里直接组合数算一下就行了，非常简单。

令 $b=n^{\frac{1}{3}}$ ，则总复杂度取最小值，为 $O(n^\frac{5}{3})$。

代码（没有取模所以 $10^5$ 时会爆 long long，如果要跑记得加取模）：
```
// O(n^{5/3})
#include<bits/stdc++.h>
using namespace std;
const long long N=100002;
long long n,bl,a[N];
vector<long long> num[N];
bool issmall[N];
long long calc3() {
    long long ans=0,x;
    for(long long i=1;i<=n;++i) {
        x=num[i].size();
        ans+=x*(x-1)*(x-2)*(x-3)/24;
    }
    return ans;
}
bool cmp(pair<long long,long long> a,pair<long long,long long> b) {
    if(a.first/bl!=b.first/bl)
        return a.first>b.first;
    return a.second>b.second;
}
long long calc2() {
    long long ans=0,sums=0,sumb=0,l=1,r=2,lc[N]={},mc[N]={},rc[N]={};
    vector<pair<long long,long long> > temp;
    for(long long i=1;i<=n;++i)
        if(num[i].size()<bl)
            for(long long j=0;j<num[i].size();++j)
                for(long long k=j+1;k<num[i].size();++k)
                    temp.push_back(pair<long long,long long>{num[i][j],num[i][k]});
    sort(temp.begin(),temp.end(),cmp);
    for(long long i=3;i<=n;++i)
        rc[a[i]]++;
    for(long long i=0;i<temp.size();++i) {
        while(r<temp[i].second) {
            mc[a[r]]++;
            if(issmall[a[r]])
                sums+=lc[a[r]]+rc[a[r]];
            else
                sumb+=lc[a[r]]+rc[a[r]];
            rc[a[r+1]]--;
            if(issmall[a[r+1]])
                sums-=mc[a[r+1]];
            else
                sumb-=mc[a[r+1]];
            r++;
        }
        while(r>temp[i].second) {
            rc[a[r]]++;
            if(issmall[a[r]])
                sums+=mc[a[r]];
            else
                sumb+=mc[a[r]];
            mc[a[r-1]]--;
            if(issmall[a[r-1]])
                sums-=rc[a[r-1]]+lc[a[r-1]];
            else
                sumb-=rc[a[r-1]]+lc[a[r-1]];
            r--;
        }
        while(l<temp[i].first) {
            lc[a[l]]++;
            if(issmall[a[l]])
                sums+=mc[a[l]];
            else
                sumb+=mc[a[l]];
            mc[a[l+1]]--;
            if(issmall[a[l+1]])
                sums-=lc[a[l+1]]+rc[a[l+1]];
            else
                sumb-=lc[a[l+1]]+rc[a[l+1]];
            l++;
        }
        while(l>temp[i].first) {
            lc[a[l-1]]--;
            if(issmall[a[l-1]])
                sums-=mc[a[l-1]];
            else
                sumb-=mc[a[l-1]];
            mc[a[l]]++;
            if(issmall[a[l]])
                sums+=lc[a[l]]+rc[a[l]];
            else
                sumb+=lc[a[l]]+rc[a[l]];
            l--;
        }
        ans+=sums+sumb*2-mc[a[l]]*(rc[a[l]]+lc[a[l]]);
        cerr << sumb << endl;
    }
    return ans/2;
}
long long calc11(vector<long long> a) {
    long long ans=0,l0=0,l1=0,r0=0,r1=0,r01=0,r10=0;
    for(long long i=a.size()-1;i>=0;--i)
        if(a[i]==0) {
            r01+=r1;
            r0++;
        } else {
            r10+=r0;
            r1++;
        }
    for(long long i=0;i<a.size();++i)
        if(a[i]==0) {
            ans+=l1*r10;
            l0++;r0--;r01-=r1;
        } else {
            ans+=l0*r01;
            l1++;r1--;r10-=r0;
        }
    return ans;
}
long long calc1() {
    bool bit[N]={};
    long long ans=0;
    vector<long long> lis,temp;
    for(long long i=1;i<=n;++i)
        if(num[i].size()>=bl)
            lis.push_back(i);
        else
            issmall[i]=true;
    for(long long i=0;i<lis.size();++i)
        for(long long j=i+1;j<lis.size();++j) {
            temp.clear();
            merge(num[lis[i]].begin(),num[lis[i]].end(),num[lis[j]].begin(),num[lis[j]].end(),back_inserter(temp));
            for(long long k=0;k<num[lis[i]].size();++k)
                bit[num[lis[i]][k]]=0;
            for(long long k=0;k<num[lis[j]].size();++k)
                bit[num[lis[j]][k]]=1;
            for(long long k=0;k<temp.size();++k)
                temp[k]=bit[temp[k]];
            ans+=calc11(temp);
        }
    return ans;
}
void tra() {
    map<long long,long long> temp;
    long long s=0;
    cin >> n;
    for(long long i=0;i<=n;++i)
        num[i].clear();
    bl=pow(n,1.0/3);
    if(bl<1) bl=1;
    for(long long i=1;i<=n;++i) {
        cin >> a[i];
        if(temp[a[i]]==0)
            temp[a[i]]=++s;
        num[temp[a[i]]].push_back(i);
        a[i]=temp[a[i]];
    }
}
int main() {
    long long t;
    cin >> t;
    while(t--) {
        tra();
        cout << calc1()+calc2()+calc3() << endl;
    }
}
```

---

## 作者：邓布利多6 (赞：4)

题意简述 ： 在一个数列中， 计算四元组 $(i,j,k,l)$ 的数量， 满足：

1. $a_i = a_k, a_j = a_l$ .

2. $1 \leq i < j < k < l \leq n$ .  

数列长度 $n <= 3000$ .

这题做法其实很多， 比如 @syksykCCC 大佬就用来枚举 $j,l$ 的方法，我的办法是循环 $j, k$ , 个人认为比较简单。

循环 $j, k$ 后，统计这时的数量，根据乘法原理可知，应该是 $j$ 前面 数字 $k$ 的数量 和 $k$ 后面 数字 $j$ 的数量，注意复杂度要做到 $O(1)$ 求出。

那怎么办呢 ? $\large \textbf{前缀和预处理}$ .

后面就是常规操作了，统计出 $sum_{i,j}$ 表示数字 $i$ 在前面 $j$ 个数中出现了几次，那么总数就是：

$$ \sum_{i=1}^{n} \sum_{j = i+ 1}^{n} sum[a_k][\,j-1\,] \times (sum[a_j][\,n\,] - s[a_j][\,k\,]) $$

注意：记得开上 long long .

#### Code

``` cpp
#include <iostream>
#define int long long 
using namespace std;
const int N = 3005;
int T, n, ans, a[N], s[N][N];
signed main()
{
	cin >> T;
	while(T--)
	{
		cin >> n; ans = 0;
		for(int i = 1; i <= n; i++)	cin >> a[i];
		
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				s[i][j] = s[i][j - 1] + (a[j] == i);
				
		for(int j = 1; j <= n; j++)
			for(int k = j + 1; k <= n; k++)
				ans += s[a[k]][j - 1] * (s[a[j]][n] - s[a[j]][k]);
		
		cout << ans << endl;
	}
	return 0;
}


```

---

## 作者：ZigZagKmp (赞：3)

本文同步发表于[我的cnblog](https://www.cnblogs.com/ZigZagKmp/p/13563143.html)

本场题解可见[此](https://www.luogu.com.cn/blog/ZigZagKmp/codeforces-1400-edu-94-solution)
## 题意简述
给定一个长度为$n$的数列$\{a_n\}$，计算满足如下条件的四元组$(i,j,k,l)$个数：

- $1\le i<j<k<l\le n$；
- $a_i=a_k$且$a_j=a_l$。

多测，$4\le n\le 3000$，$1\le a_i\le n$，$\sum n\le 3000$。
### 算法考察
计数原理，前缀和，二分，尺取法
## 算法分析
不难想到按照权值计数。

我们预处理出每一个权值出现的位置，这里可以使用$vector$实现。

为了减少讨论，我们可以先处理出$a_i=a_j=a_k=a_l$的情况，枚举每一个权值，直接组合数计算。

下面假设我们枚举的权值为$x,y$，且$a_i=a_k=y$，$a_j=a_l=x$。

下面我们枚举$k,l$，问题转化为给定$x,y$，多次询问$k$，求有多少个二元组$(i,j)$，满足：

- $1\le i<j<k$
- $a_i=y$且$a_j=x$

我们可以枚举$j$，在$y$的位置数组中二分计算出小于$j$有多少个位置，记为$b_j$。

然后再对$b$求前缀和，完成预处理。

对于每一个询问，我们可以在$x$的位置数组中二分，找到对应的$b$，累加答案即可。

如上实现的复杂度为$O(n^2\log n)$，类比图论中有关边数的证明，可以证明对$k,l$的枚举是均摊$O(1)$的。

上述算法已经可以通过本题。如果扩大数据范围，可以利用枚举$j$的单调和枚举$k$的单调，用指针的移动代替二分。

同时我们发现，其实我们没有必要枚举$l$，我们只需要枚举$k$，不难发现对于一个确定的$k$，每一个$l$答案都是一样的，因此可以直接乘上$l$的个数。

如上优化后的复杂度为$O(n^2)$，但考场上不建议使用上述优化，耗时耗力，还容易打挂。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 3005
#define maxm 2000005
#define inf 0x3f3f3f3f
#define int long long//注意long long
#define mod 1000000007
#define local
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int n,m;
vector<int>p[maxn];//位置数组
vector<int>h[maxn];//前缀和数组
int sum1,sum2;
int C4(int x){//求C(x,4)
	if(x<4)return 0;
	else return x*(x-1)*(x-2)*(x-3)/24;
}
int calc(int x,int y){
	h[x].clear();
	for(unsigned i=0;i<p[x].size();i++){
		int tt=lower_bound(p[y].begin(),p[y].end(),p[x][i])-p[y].begin();
		h[x].push_back(tt);
	}
	for(unsigned i=1;i<p[x].size();i++){
		h[x][i]+=h[x][i-1];
	}//二分并求前缀和
	int ret=0;
	for(unsigned i=0;i<p[x].size();i++){
		for(unsigned j=0;j<p[y].size()&&p[y][j]<p[x][i];j++){
			int k=lower_bound(p[x].begin(),p[x].end(),p[y][j])-p[x].begin()-1;//二分对应前缀和位置
			if(k!=-1)ret+=h[x][k];
		}
	}
	return ret;
}
signed main(){
	int CasT;
	read(CasT);
	while(CasT--){
		read(n);
		for(int i=1,x;i<=n;i++)read(x),p[x].push_back(i);
		sum1=sum2=0;
		for(int i=1;i<=n;i++){
			sum1+=C4(p[i].size());
		}//处理四个全相等
		for(int i=1;i<=n;i++)if(p[i].size()<2)p[i].clear();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(i==j)continue;
				if(p[i].size()<2||p[j].size()<2)continue;//小剪枝，也是为了避免讨论
				sum2+=calc(i,j);
			}
		}
		printf("%lld\n",sum1+sum2);
		for(int i=1;i<=n;i++)p[i].clear();//注意多测清空
	}
	return 0;
}

```

---

## 作者：AlanSP (赞：2)

## D.Zigzags

### [题目链接](https://codeforces.com/contest/1400/problem/D)

我们可以先枚举第一个区间 $[i,j]$ ，保证 $a_i=a_j$ 。

那么问题转化成在 $(i,j)$ 和 $(j,n]$ 间，相等的数字对数。

我们可以预处理出在  $[1,j]$ 和 $[1,n]$ 间，相等的数字对数 $s[j][n]$

若要提取给定区间，可以运用差分思想减去 $s[i][n]$ 和 $s[j-1][j]$ 。

相当于去除了 $[1,i]$ 和 $[1,j]$ 对答案的贡献。

根据容斥，还要加上 $s[i][j]$ 。

受到[P6006](https://www.luogu.com.cn/problem/P6006)的启发，这就是一个二维前缀和。

那么我们就可以 $O(1)$ 回答了。

记得开longlong。

### Code
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
#define int long long
const int N=3009;
int n,T,m;
int s[N][N],a[N];
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		int ans=0;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+(a[i]==a[j]);
		for(int i=1;i<=n;i++)
			for(int j=i+2;j<=n;j++)
				if(a[i]==a[j])
					ans+=s[j-1][n]+s[i][j]-s[i][n]-s[j-1][j];
		printf("%lld\n",ans);		
	}
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

考虑枚举 $j , k$ ，这样我们只用统计出 $j - 1$ 前面有多少个 $a_k$ 和 $k + 1$ 后面有多少个 $a_j$ 就好了，可以离散化然后暴力前缀和，时间复杂度 $O(n ^ 2)$ 。          
题目已经帮忙离散化就不必自己手写了。               

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Len = 3e3 + 5;
int n,m,a[Len],pre[Len][Len],suf[Len][Len];
int main()
{
	int t;scanf("%d",&t);
	while(t --)
	{
		scanf("%d",&n);
		for(int i = 1 ; i <= n ; i ++) scanf("%d",&a[i]);
		for(int i = 1 ; i <= n ; i ++)
			for(int j = 1 ; j <= n ; j ++) pre[i][j] = suf[i][j] = 0;
		for(int i = 1 ; i <= n ; i ++)
		{
			pre[i][a[i]] ++;
			for(int j = 1 ; j <= n ; j ++) pre[i][j] += pre[i - 1][j];
		}
		for(int i = n ; i >= 1 ; i --)
		{
			suf[i][a[i]] ++;
			for(int j = 1 ; j <= n ; j ++) suf[i][j] += suf[i + 1][j]; 
		}
		long long ans = 0;
		for(int k = 1 ; k <= n ; k ++)
			for(int j = 1 ; j < k ; j ++) ans += pre[j - 1][a[k]] * suf[k + 1][a[j]];
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：rouxQ (赞：1)

考场上想到做法没调出来，自闭了。
## 题意
给定长度为 $n$ 的数组 $a$，询问有多少组 $(i,j,k,l)$ 满足：
- $1\le i<j<k<l\le n$
- $a_i=a_k$ 且 $a_j=a_l$

$n\le 3000$

## $\operatorname{Sol}$
先看到这个数据范围，显然暗示着我们去寻找 $\Theta(n^2)$ 的做法，再不难猜测，做法应当是枚举四元组中的两个，再 $\Theta(1)$ 计算贡献。如果我们枚举 $i,j$，我们会发现很难处理 $k$ 和 $l$ 的相对位置关系，所以做法应当是枚举 $i,k$，这样 $j\in (i,k),l\in(k,n]$，达到了我们的预期。

我们在枚举 $i,k$ 的同时对 $(i,k)$ 区间和 $(k,n]$ 区间维护两个桶 $t1,t2$，显然此处的贡献为 $\sum t1_i\times t2_i$，如果在转移的同时更新桶，再计算贡献，发现这样做是 $\Theta (n^3)$ 的，考虑优化。可以发现，在转移过程中，一次 $k$ 的移动只会造成两个桶中分别一个元素的变化，也就是说，在计算贡献的 $\sum$ 中，**一次转移最多伴随着两项值的变化**，让总贡献直接更新即可。

时间复杂度 $\Theta(Tn^2)$。
## $\operatorname{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[3001], t1[3001], t2[3001];
int main (){
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)cin >> a[i];
        long long ans = 0;
        for (int i = 1; i <= n; i++){
            memset(t1, 0, sizeof(t1));
            memset(t2, 0, sizeof(t2));
            long long tmp = 0;//贡献
            for (int j = i + 1; j <= n; j++)t2[a[j]]++;
            for (int j = i + 1; j < n; j++){
                
                tmp -= t1[a[j]], t2[a[j]]--;//此处贡献变为t1[a[j]] * (t2[a[j]] - 1)
                if (a[i] == a[j])ans += tmp;
                tmp += t2[a[j]], t1[a[j]]++;//注意此处加上的贡献在下一个循环才是合法的
                                            //所以在计算对答案的贡献之后再更新
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：引领天下 (赞：1)

一个挺有意思的递推。

设 $f_{i,j}=\sum_{k=j}^n{a_k==a_i}$，则有以下转移：

$f_{i,j}=f_{i,j+1}+(a_j==a_i)$。

另设 $g_{i,j}=\sum_{k=i+1}^{j-1}{f_{k,j}}$，则有 $ans=\sum_{i=1}^n\sum_{j=i+1}^n{c_{i,j}}$，其中 $c_{i,j}$ 表示 $a_i=a_j$ 时的 $f_{i,j}$。

```cpp
#include <bits/stdc++.h>- 
using namespace std;
int t,n,a[3005];
long long f[3005][3005],g[3005][3005];
int main(){
    scanf("%d",&t);
    while(t--){
        long long ans=0;
        scanf("%d",&n);memset(f,0,sizeof(f));memset(g,0,sizeof(g));
        for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
        for(int j=n;j>=1;j--)f[i][j]=f[i][j+1]+(a[j]==a[i]);//倒序递推f
        for(int j=1;j<=n;j++)
        for(int i=j-2,k=0;i>=1;i--)g[i][j]=(k+=f[i+1][j+1]);//倒序递推g
        for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)if(a[i]==a[j])ans+=g[i][j];//统计答案
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：2huk (赞：0)

> - 给出 $n$ 个数 $a_1,a_2,\cdots,a_n$。求问有多少个四元组 $(i,j,k,l)$，使得这个四元组满足下列条件：
>
>   - $1 \leq i<j<k<l \leq n$；   
>   - $a_i=a_k$ 并且 $a_j=a_l$。
>
> - $a_i \le n \le 3000$。

显然可以枚举 $j, k$，所以此时 $a_j, a_k$ 为定值。那么 $i$ 必须要满足 $i < j$ 且 $a_i = a_k$，$l$ 必须要满足 $l > k$ 且 $a_l = a_j$。所以我们要做的就是统计一段区间内某个数字的出现次数。

套路。用 vector 存储每个数字出现的位置，那么每次查询相当于是问某个 vector 中有多少数在 $[l, r]$ 范围内。二分即可。

```cpp
int n, a[N];
ll res;
vector<int> mp[N];

int calc(int l, int r, int x) {
	if (!mp[x].size()) return 0;
	return upper_bound(mp[x].begin(), mp[x].end(), r) - lower_bound(mp[x].begin(), mp[x].end(), l);
}

void Luogu_UID_748509() {
	fin >> n;
	for (int i = 1; i <= n; ++ i ) {
		fin >> a[i];
		mp[a[i]].push_back(i);
	}
	
	res = 0;
	for (int j = 2; j < n; ++ j )
		for (int k = j + 1; k < n; ++ k )
			res += calc(1, j - 1, a[k]) * 1.0 * calc(k + 1, n, a[j]);
	
	fout << res << '\n';
	
	for (int i = 1; i <= n; ++ i ) mp[i].clear();
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
这题我们只要 $O(n^2)$ 枚举 $j$ 和 $k$ 就行，根据乘法原理，对于每个 $\{j,k\}$，所有方案共有在 $j$ 前等于 $a_k$ 的数量乘上在 $k$ 后等于 $a_j$ 的数量即可。做一个前缀和快速求出区间相等的元素个数，前缀和也是 $O(n^2)$。
# 代码
```cpp
# include <bits/stdc++.h>
# define ffor(i,name) \
	for (auto i = name.begin (); i != name.end (); ++ i)
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, a[3005], s[3005][3005];
//s[i][j] 表示 在 $a[1]~a[i] 间 =j 的个数$
ll sum;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n;
		sum = 0;
		for (int i = 1; i <= n; ++ i) {
			cin >> a[i];
			for (int j = 1; j <= n; ++ j)
				s[i][j] = s[i - 1][j];
			++ s[i][a[i]];
		}
		for (int j = 2; j < n; ++ j)
			for (int k = j + 1; k < n; ++ k)
				sum += (s[n][a[j]] - s[k][a[j]]) * s[j - 1][a[k]];
		cout << sum << '\n';
	}
	return 0;
}
```

---

## 作者：wuzijie (赞：0)

## 题面解释：
$t$ 组数据,每组有 $n$ 个数 $a_1,a_2,\cdots,a_n$。求问有多少个四元组 $(i,j,k,l)$，使得这个四元组满足下列条件：

- $1 \leq i<j<k<l \leq n$；   
- $a_i=a_k$ 并且 $a_j=a_l$。

## 思路分析：
考虑枚举 $j$ 和 $k$，则我们需要找出 $i<j$ 并且 $a_i=a_k$ 的 $i$ 的个数与 $k<l$ 并且 $a_j=a_l$ 的 $l$ 的个数，对于每一组 $(j,k)$ 利用乘法原理计算贡献，最后利用加法原理求和即可。

那么我们如何解决上述文题呢？我们可以使用桶计数配合前缀和，$sum1_{i,j}$ 表示从前往后到第 $i$ 位为止 $j$ 出现的次数，$sum2_{i,j}$ 则从后往前。

$n$ 与 $m$ 同阶，可行。

注意：

- 由于有多组数据，注意每次初始化。
- 最终答案最大可能有 $\mathrm{C}_n^4$ 最大可以达到 $3\times10^{12}$ 以上，所以要开 `longlong` 。
## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e3+10;
int t,n,a[N],sum1[N][N],sum2[N][N],ans;
signed main(){
	scanf("%lld",&t);
	while(t--){
		memset(sum1,0,sizeof(sum1));
		memset(sum2,0,sizeof(sum2));
		ans=0;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)	
			scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)
				sum1[i][j]+=sum1[i-1][j];
			sum1[i][a[i]]++;
		}
		for(int i=n;i;i--){
			for(int j=1;j<=n;j++)
				sum2[i][j]+=sum2[i+1][j];
			sum2[i][a[i]]++;
		}
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				ans+=sum1[i-1][a[j]]*sum2[j+1][a[i]];
		printf("%lld\n",ans);
	}
	return 0;
}
```

谢谢！

---

## 作者：k2saki (赞：0)

看到数据范围是 3000，就可以想到枚举 2 个，剩下的 O(1) 算 2 个，最后根据乘法原理求出来累加。

手模一遍发现只有枚举 j,k 是合理的。

然后就可以前缀和记录了，$sum[i][j]$ 表示前 i 个数 j 的数量。

每次统计就是 `ans += sum[i - 1][a[j]] * (sum[n][a[i]] - sum[j][a[i]]);`

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, m;
int read()
{
    int s = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}
int T;
int x;
int a[101010];
int sum[3003][3003];
signed main()
{
    T = read();
    while (T--)
    {
        n = read();
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= 3000; ++j)
            {
                sum[i][j] = 0;
            }
        }
        for (int i = 1; i <= n; ++i)
            a[i] = read();
        for (int i = 1; i <= n; ++i)
        {
            sum[i][a[i]] = 1;
        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= 3000; ++j)
            {
                sum[i][j] = sum[i][j] + sum[i - 1][j];
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = i + 1; j <= n; ++j)
            {
                ans += sum[i - 1][a[j]] * (sum[n][a[i]] - sum[j][a[i]]);
            }
        }
        cout << ans << endl;
    }
}
```


---

## 作者：KSToki (赞：0)

# 前置芝士
前缀和，~~简单吧~~。
# 题目大意
给出 $n$ 个数 $a_1,a_2,…,a_n$，问有多少个四元组 $(i,j,k,l)$，满足 $1\le i<j<k<l\le n$ 且 $a[i]==a[k],a[j]==a[l]$。
# 题目分析
注意到数据范围 $4\le n\le3000$，猜想解决问题的时间复杂度应该为 $O(n^2)$ 或是 $O(n^2logn)$，想到有两重循环，枚举 $i,j,k,l$ 中的两个，然后 $O(1)$ 或是 $O(logn)$ 求解。$(i,k)$ 作为一组，$(j,l)$ 作为一组，枚举就有四种方案：

枚举 $i,j$，~~至少我想不到怎么确定~~无法确定 $k,l$。

枚举 $i,l$，嗯，我们机房有个巨佬好像是这么做的，维护两个数组，具体……~~我太菜了~~。

枚举 $k,l$，跟枚举 $i,j$ 差不多吧。

蒟蒻的做法就是枚举 $j,k$，用一个前缀和数组 $s[i][j]$ 维护 $1$~$i$ 中出现了几次 $j$，利用乘法原理可得对应每个 $j,k$，答案为 $s[j-1][a[k]]\times(s[n][a[j]]-s[k][a[j]])$，加法原理统计答案，加起来即可。
# 代码
记得开 `long long`。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[3001],s[3001][3001];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		memset(s,0,sizeof(s));
		scanf("%d",&n);
		for(register int i=1;i<=n;++i)
		{
			scanf("%d",&a[i]);
			for(register int j=0;j<=n;++j)
				s[i][j]=s[i-1][j]+(j==a[i]);
		}
		long long ans=0;
		for(register int j=1;j<n;++j)
			for(register int k=j+1;k<=n;++k)
				ans+=(long long)s[j-1][a[k]]*(s[n][a[j]]-s[k][a[j]]);
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：ignited (赞：0)

应该是最容易理解的一个做法。前缀和dp。

$f_{i,j}$表示第$j$个数后面与$a_i$相等的个数。

显然有：


$$f_{i,j}=\begin{cases}f_{i,j+1}+1&a_{j+1}=a_i\\f_{i,j+1}&a_{j+1}\neq a_i\end{cases}$$

做一个前缀和数组$s$。

$$s_{i,j}=\sum\limits^{i}_{k=1}f_{k,j}=s_{i-1,j}+f_{i,j}$$

那么每次可以枚举相等的数对$i,k$。对于区间$(i,k)$中的每一个$j$,对答案的贡献为$f_{j,k}$。

$O(1)$可算出$\{j,l\}$的个数，即$s_{k-1,k}-s_{i,k}$


$$Ans=\sum\limits_{1\leq i<k \leq n,,a_i=a_k}s_{k-1,k}-s_{i,k}$$

然后就做完了，复杂度最坏$O(n^2)$

记得开$long   \ long$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long a[3010];
long long f[3010][3010]; 
long long s[3010][3010];
int main()
{
	cin>>t;
	while(t--)
	{
		long long ans=0;
		int n;
		cin>>n;
		vector<int> v[3010];
		memset(f,0,sizeof(f));
		memset(s,0,sizeof(s));
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		if(a[i]==a[j]) v[i].push_back(j);
		
		for(int i=1;i<=n;i++)
		{
			for(int j=n;j>=1;j--)
			{
				if(a[j+1]==a[i]) f[i][j]=f[i][j+1]+1;
				else f[i][j]=f[i][j+1];
			}
		}

		

		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				s[i][j]=s[i-1][j]+f[i][j];
			}
		}
		
		for(int i=1;i<=n;i++)
		{
			for(int k=0;k<v[i].size();k++)
			{
				int p=v[i][k];
				if(p==i+1) continue;
				ans+=(s[p-1][p]-s[i][p]);
			}
		}
		cout<<ans<<endl;
	}
	
	return 0;
} 

```



---

