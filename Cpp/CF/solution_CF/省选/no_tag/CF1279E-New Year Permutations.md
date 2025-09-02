# New Year Permutations

## 题目描述

Yeah, we failed to make up a New Year legend for this problem.

A permutation of length $ n $ is an array of $ n $ integers such that every integer from $ 1 $ to $ n $ appears in it exactly once.

An element $ y $ of permutation $ p $ is reachable from element $ x $ if $ x = y $ , or $ p_x = y $ , or $ p_{p_x} = y $ , and so on.

The decomposition of a permutation $ p $ is defined as follows: firstly, we have a permutation $ p $ , all elements of which are not marked, and an empty list $ l $ . Then we do the following: while there is at least one not marked element in $ p $ , we find the leftmost such element, list all elements that are reachable from it in the order they appear in $ p $ , mark all of these elements, then cyclically shift the list of those elements so that the maximum appears at the first position, and add this list as an element of $ l $ . After all elements are marked, $ l $ is the result of this decomposition.

For example, if we want to build a decomposition of $ p = [5, 4, 2, 3, 1, 7, 8, 6] $ , we do the following:

1. initially $ p = [5, 4, 2, 3, 1, 7, 8, 6] $ (bold elements are marked), $ l = [] $ ;
2. the leftmost unmarked element is $ 5 $ ; $ 5 $ and $ 1 $ are reachable from it, so the list we want to shift is $ [5, 1] $ ; there is no need to shift it, since maximum is already the first element;
3. $ p = [\textbf{5}, 4, 2, 3, \textbf{1}, 7, 8, 6] $ , $ l = [[5, 1]] $ ;
4. the leftmost unmarked element is $ 4 $ , the list of reachable elements is $ [4, 2, 3] $ ; the maximum is already the first element, so there's no need to shift it;
5. $ p = [\textbf{5}, \textbf{4}, \textbf{2}, \textbf{3}, \textbf{1}, 7, 8, 6] $ , $ l = [[5, 1], [4, 2, 3]] $ ;
6. the leftmost unmarked element is $ 7 $ , the list of reachable elements is $ [7, 8, 6] $ ; we have to shift it, so it becomes $ [8, 6, 7] $ ;
7. $ p = [\textbf{5}, \textbf{4}, \textbf{2}, \textbf{3}, \textbf{1}, \textbf{7}, \textbf{8}, \textbf{6}] $ , $ l = [[5, 1], [4, 2, 3], [8, 6, 7]] $ ;
8. all elements are marked, so $ [[5, 1], [4, 2, 3], [8, 6, 7]] $ is the result.

The New Year transformation of a permutation is defined as follows: we build the decomposition of this permutation; then we sort all lists in decomposition in ascending order of the first elements (we don't swap the elements in these lists, only the lists themselves); then we concatenate the lists into one list which becomes a new permutation. For example, the New Year transformation of $ p = [5, 4, 2, 3, 1, 7, 8, 6] $ is built as follows:

1. the decomposition is $ [[5, 1], [4, 2, 3], [8, 6, 7]] $ ;
2. after sorting the decomposition, it becomes $ [[4, 2, 3], [5, 1], [8, 6, 7]] $ ;
3. $ [4, 2, 3, 5, 1, 8, 6, 7] $ is the result of the transformation.

We call a permutation good if the result of its transformation is the same as the permutation itself. For example, $ [4, 3, 1, 2, 8, 5, 6, 7] $ is a good permutation; and $ [5, 4, 2, 3, 1, 7, 8, 6] $ is bad, since the result of transformation is $ [4, 2, 3, 5, 1, 8, 6, 7] $ .

Your task is the following: given $ n $ and $ k $ , find the $ k $ -th (lexicographically) good permutation of length $ n $ .

## 样例 #1

### 输入

```
5
3 3
5 15
4 13
6 8
4 2
```

### 输出

```
2 1 3 
3 1 2 5 4 
-1
1 2 6 3 4 5 
1 2 4 3 
```

# 题解

## 作者：猪脑子 (赞：8)

观察一下题目中对于“好排列”的定义，不难发现，如果排列$p$是个好排列，假设$p_1=m$，那么$1,2,\dots,m$肯定都出现在排列的前$m$个位置，并且属于同一个“list”。这样的话，每个好排列都应该可以拆成若干段，使得每一段内部都组成一个环（$i$向$p_i$连边），且每一段开头连出的边都指向这一段的最后一个位置。

这样，我们就可以计算$f_n$：长度为$n$的满足条件的排列个数：

$$f_0=1,f_n=\sum_{i=1}^{n}f_{n-i}\times g_{i}$$

其中$g_n$代表长度为$n$的排列$p$，满足$p_1=n$且是一个环的这样的$p$的个数。这个也好算：

$$g_1=1,g_n=(n-2)!$$

然后就可以递推得出$f_n$了。

现在问题就在于，我们如何构造出字典序第$k$小的满足条件的排列。

首先假设我们要构造长度为$n$的第$k$小的排列$p$，一个显然的思路是先枚举$p_1$的值。由于$p_1$的值决定了这个排列第一段的长度，于是$p_1$的值就很容易确定了。假设求出了$p_1=m$,我们先将$k$减去$p_1$取$1,\dots,m-1$的方案数，此时排列被分成两部分：左边一个长度为$m$的环，然后是右边一个长度为$n-m$的排列。由于左边的环具体长什么样对右边的方案数没有影响，那么我们就可以确定左边的环的排名$t_1=\lceil\frac{k}{f_{n-m}}\rceil$，这样也可以确定右边的排列在所有相同长度的排列中排名为$t_2=k-(t-1)\times f_{n-m}$。

对于右边的部分，直接递归就好了，那么问题就是如何算左边的部分。

这个也相当简单，确定$p_1$之后，我们还是从$p_2$开始往后一个一个确定对应位置的取值，只是枚举的时候不要让排列在第$m$个位置之前成环就可以了。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const long long INF=1e18+7;
long long f[53],fac[53];
long long add(long long a,long long b)
{
	return min(INF,a+b);
}
long long mul(long long a,long long b)
{
	if(INF/a<b)return INF;
	return a*b;
}
const int N=50;
long long g(int n)
{
	if(n==1)return 1;
	return fac[n-2];
}
void init()
{
	fac[0]=1;
	for(int i=1;i<=N;i++)
		fac[i]=mul(fac[i-1],i);
	f[0]=1;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=i;j++)
			f[i]=add(f[i],mul(f[i-j],g(j)));
	return ;
}
int p[53];
int q[53];
bool vis[53];
int find(int x)
{
	while(q[x])x=q[x];
	return x;
}
void getq(int n,long long k)
{
	if(n==1){
		q[1]=1;
		return ;
	}
	for(int i=1;i<=n;i++)
		q[i]=vis[i]=0;
	q[1]=n;vis[n]=1;
	for(int i=2;i<n;i++)
	{
		long long num=fac[n-i-1];
		for(int j=1;j<=n;j++)
			if(j!=i&&!vis[j]&&find(j)!=i)
			{
				if(k<=num){
					q[i]=j;
					vis[j]=true;
					break;
				}
				k-=num;
			}
	}
	for(int i=1;i<=n;i++)
		if(!vis[i])q[n]=i;
	return ;
}
void getp(int n,long long k)
{
	if(!n)return ;
	int len=0;
	for(int i=1;i<=n;i++)
	{
		long long num=mul(g(i),f[n-i]);
		if(k<=num){
			len=i;
			break;
		}
		k-=num;
	}
	long long num=f[n-len];
	long long need=(k-1)/num+1;
	getp(n-len,k-(need-1)*num);
	for(int i=n;i>len;i--)
		p[i]=p[i-len]+len;
	getq(len,need);
	for(int i=1;i<=len;i++)
		p[i]=q[i];
	return ;
}
int main()
{
	init();
	int t;scanf("%d",&t);
	while(t--)
	{
		int n;long long k;
		scanf("%d %lld",&n,&k);
		if(f[n]<k)printf("-1\n");
		else{
			getp(n,k);
			for(int i=1;i<=n;i++)
				printf("%d ",p[i]);
			printf("\n");
		}
	}
	return 0;
}
```

~~表面上是计数，其实是个小小的模拟~~

~~水水水~~

---

## 作者：skyskyCCC (赞：0)

## 前言。
第一次独立作出 $2700$ 的题，纪念一下。这道题的基本思路就是标准的两种做法。提供一种并查集的做法，同时我们需要采用动态规划。
## 分析。
首先，我们需要求出，以某一个数据开头有多个可能的排列情况，这就是动态规划的样子了。注意这个排列情况必须合法，即枚举从这个点开始的子区间长度。那么我们显然有在区间长度为 $n$ 时合法的置换群有 $n−2$ 的阶乘个。我们直接预处理出来就行。

然后，我们既然知道了有多少个可能情况，那么直接开始逐位往里面填上数就行了。这里有一个巧妙的思路，就是我们枚举当前位置应该填哪个数，事实上就是去找子区间的结束位置，即右端点，其中，如果方案数大于 $k$ 则说明子区间在这里结束。那么显然我们只需要再找出字典序第 $k$ 大的一个置换群，那么这里的 $k$ 我们就可以转化为整体答案的 $k$ 除掉后面的字典序较大的方案数，这些去掉的方案就是每种子区间排列对应后面的排列。

最后用并查集检查一下防止提前出现环。更新方案数即可。计算 $dp_i$ 时，每次计算区间的长度就是 $j-i+1$。那么转移方程就是
$$dp_i = \sum_{j=i}^n(dp_{j + 1} \cdot C_{j - i - 1})$$
其中的 $C$ 就是前面预处理出来的数组。

具体的优化可以见代码。代码如下，仅供参考:
```
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const long long inf=2e18;
int T,n;
long long k;
long long dp[105],sum[105];
int fa[105],ans[105],vised[105];
inline long long mul(long long x,long long y){
	if(inf/x<y){
	    return inf;
    }
	return min(x*y,inf);
}
inline int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
inline void work(int l,int r,long long t){
	ans[l]=r;
	for (int i=l;i<=r;i++){
		vised[i]=0;
		fa[i]=i;
	}
	for (int i=l+1;i<r;i++){
		long long w=sum[r-i-1];
		for (int j=l;j<r;j++){
			if(vised[j]||find(j)==find(i)){
			    continue;
			}
			if(t<=w){
				vised[j]=1;
				ans[i]=j;
				fa[find(i)]=find(j);
				break;
			}
			t-=w;
		}
	}
	for (int i=l;i<r;i++){
	    if(!vised[i]){
	    	ans[r]=i;
		}
	}
}
inline void solve(int l,int r){
	if(l>r){
	    return;
	}
	if(k<=dp[r-l]){
		solve(l+1,r);
		ans[l]=l;
		return;
	}
	k-=dp[r-l];
	for (int i=2;i<=r-l+1;i++){
		long long w=mul(sum[i-2],dp[r-l+1-i]);
		if (k<=w){
			long long t=(k-1)/dp[r-l+1-i]+1;
			k-=(t-1)*dp[r-l+1-i];
			solve(l+i,r);
			work(l,l+i-1,t);
			return;
		}
		k-=w;
	}
}
int main() {
	cin>>T;
	while(T--){
		cin>>n>>k;
		sum[0]=1;
		for (int i=1;i<=n;i++){
			sum[i]=mul(sum[i-1],i);
		}
		dp[0]=1;
		for (int i=1;i<=n;i++){
			dp[i]=dp[i-1];
			for (int j=2;j<=i;j++){
				dp[i]=min(inf,dp[i]+mul(dp[i-j],sum[j-2]));
			}
		}
		if(dp[n]<k){
			cout<<"-1\n";
			continue;
		}
		solve(1,n);
		for (int i=1;i<=n;i++){
			cout<<ans[i]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

