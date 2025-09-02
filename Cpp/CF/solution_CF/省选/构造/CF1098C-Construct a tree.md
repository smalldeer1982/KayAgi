# Construct a tree

## 题目描述

Misha 漫步在雪地森林中，被树木深深吸引，决定画一棵属于自己的树！

Misha 想要构造一棵有 $n$ 个结点的有根树，结点编号从 $1$ 到 $n$，其中根结点编号为 $1$。每个其他结点都有一个父结点 $p_i$，$i$ 被称为结点 $p_i$ 的子结点。若从 $u$ 出发，沿着父结点链（$u$，$p_u$，$p_{p_u}$，……）能够到达 $v$，则称结点 $u$ 属于结点 $v$ 的子树。显然，$v$ 也属于自己的子树，子树中结点的数量称为子树的大小。Misha 只对所有结点都属于结点 $1$ 的子树的树感兴趣。

下图是一棵有 $6$ 个结点的树。结点 $2$ 的子树包含结点 $2$、$3$、$4$、$5$，因此其子树大小为 $4$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1098C/c0bc9c82cdcd20b087d88b1afdb2ab79756ebad2.png)

树的分支系数定义为任意结点的最大子结点数。例如，上图中树的分支系数为 $2$。你的任务是构造一棵有 $n$ 个结点的树，使得所有结点的子树大小之和等于 $s$，并且分支系数尽可能小。

## 说明/提示

下面是第一个样例的其中一种可能解。所有子树大小之和为 $3 + 1 + 1 = 5$，分支系数为 $2$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1098C/ee98c5c7cbd89b2c919d59781e8421d44b49e284.png)

下面是第三个样例的其中一种可能解。所有子树大小之和为 $6 + 3 + 2 + 1 + 2 + 1 = 15$，分支系数为 $2$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1098C/c9978c0d5d53b71095c0212966f1b4c387ec4ee6.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 5
```

### 输出

```
Yes
1 1 
```

## 样例 #2

### 输入

```
4 42
```

### 输出

```
No
```

## 样例 #3

### 输入

```
6 15
```

### 输出

```
Yes
1 2 3 1 5 
```

# 题解

## 作者：文文殿下 (赞：8)

# 题解
## ~~挺水的一道题.~~ Rating $ \color{orange} {2300}$  以下送命题。
## 首先我们知道，所有子树大小之和就是节点个数加上从根到所有节点的路径长度之和。
## 他要求度数尽可能小，所以我们二分度数$k$.显然，度数越小，子树和越大。
## 对于一个$k$叉树，他的子树大小之和为$n+k^2+k^3+...+rem$
## 我们通过二分得到最大的边界$k$
## 然后，此时我们的子树大小$s$是要小于等于规定的子树大小和的。
## 我们考虑扩大子树大小。
## 显然，我们让某些节点，往深度扩展将会扩大我们的子树大小。
## 我们记录每个深度的节点个数，已经每个节点的深度。
## 我们尝试从深度最深的节点开始往下扩展，直至子树大小达到规定大小。

## Tips:n-1叉树的大小显然为2*n-1 而一条链的大小为 n*(n+1)/2 。如果k不在这个范围内，则无解。
## 具体实现非常简单。代码如下



```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int maxn = 1e6+10;
ll n,k,cnt[maxn],d[maxn];
bool check(int x) {
	ll i(2),j,t=1,num=k-n,dep=0;
	memset(d,0,sizeof d);
	memset(cnt,0,sizeof cnt);
	while(i<=n) {
		t*=x;++dep;
		for(j=1;j<=t&&i<=n;++i,++j) cnt[dep]++,d[i]=dep,num-=dep;
	}
	if(num<0) return false;
	j=n;
	while(num) {
		++dep;
		if(cnt[d[j]]==1) --j;
		t = min(num,dep-d[j]);
		cnt[d[j]]--;
		d[j]+=t;
		cnt[d[j]]++;
		num-=t;
		--j;
	}
	return true;
}
int main() {
	cin>>n>>k;
	if(k<(1LL*2*n-1)||k>(1LL*n*(n+1)/2)) {
		puts("No");
		exit(0);
	}
	int l = 1, r = n;
	while(l<r) {
		int mid = (l+r)>>1;
		if(check(mid)) r=mid;
		else l = mid+1;
	}
	check(r);
	puts("Yes");
	int pos;
	d[pos=1]=0; sort(d+2,d+1+n); memset(cnt,0,sizeof cnt);
	for(int i = 2;i<=n;++i) {
		while(d[pos]!=d[i]-1||cnt[pos]==r) ++pos;
		cout<<pos<<' ';cnt[pos]++;
	}
	return 0;
}

```

---

## 作者：lndjy (赞：7)

牛逼构造题。

按照我模拟赛看到这个题的想法和没想到的部分一步一步推：

令 $m$ 为题目给出的 $s$，$s$ 为当前的儿子个数。

- 无解显然：$m$ 最小是菊花图，最大是链，判一下如果不在他们两个之间。
- 首先，子树和是不好处理的，尤其这个题还要构造。考虑每个节点的贡献，为它的深度（自身到根的每个点），那么 $m=\sum dep_i$。（$dep$ 为深度）
- 看一下分支系数的限制，设分支系数为 $k$，$k$ 越小 $s$ 越大。那么我们可以二分求出 $k$。
- 如何 check：对于给定的 $k$，完全 $k$ 叉树是 $s$ 最小的构造方案，同时可以通过把一个点下拉来让 $s$ 更大直到变成 $k-1$ 叉树。那么我们直接 check 完全 $k$ 叉树，然后和 $m$ 比较。
- 找到满足 $s\le m$ 的最大 $k$，然后调整。
- 考虑先建出完全 $k-1$ 叉树，设此时的 $m$ 为 $ans$，然后把点上调。
- 直接调整感觉很难的样子，维护每个深度点的个数。
- 设当前上面的部分深度 $a$，下面是 $b$，重复执行以下步骤来调整（这里如果看不懂可以结合代码的 work 函数）：
- 求一下上面的部分剩余的空位和下面部分多的点的最小值，为 $now$。
- 然后 $ans=ans-now*(b-a)$。就是点的个数乘上深度的变化量。
- 更新 $a,b$ 深度点的数量，一个加 $now$ 一个减去。
- 如果 $a$ 满了，将 $a$ 下移，$b$ 空了则上调。
- 有一个细节：$ans-now*(b-a)<m$ 时，不能更新 $now$ 这么多，要特判。
- 剩下一个简单的问题：给定每个深度点的个数，构造一棵满足条件的树，同时儿子个数不过 $k$，保证有解。
- 从小到大枚举深度，用一个 vector 存深度为当前深度减一的点，然后枚举当前深度的点去连 vector 中的点，如果满 $k$ 了就换下一个。

代码：
```cpp
#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
#include<cstdio>
#define write WWQWQW
using namespace std;
void write(int x)
{
	if(x/10) write(x/10);
	putchar(x%10+'0');
}
void F(int x)
{
	if(x) putchar(' ');
	else putchar('\n');
}
const int N=1e6+5;
#define int long long
int f[N],num[N],Dep,ans;
int n,m;
int check(int x)
{
	int now=n,dep=1;ans=0;
	for(int i=1;i<=now;i*=x)
	{
		ans+=i*dep;
		num[dep]=i;
		dep++;
		now-=i;
	}
	num[dep]=now;
	ans+=now*dep;
	Dep=dep;
	return ans;
}
vector<int> fa;
void work(int x)
{
	if(x-1) check(x-1);
	int a=2,b=Dep;
	while(1)
	{
		int now=min(num[a-1]*x-num[a],num[b]);
		if(ans-now*(b-a)<=m) break;
		ans-=now*(b-a);
		num[a]+=now;
		num[b]-=now;
		if(num[a]==x*num[a-1]) a++;
		if(num[b]==0) b--;
	}
	int rest=ans-m;
	int now=rest/(b-a);
	num[a]+=now;
	num[b]-=now;
	rest-=now*(b-a);
	num[b]--;num[b-rest]++;
	fa.push_back(1);
	now=1;
	for(int i=2;i<=b;i++)
	{
		int cnt=0,fat=0;
		int tmp=now+1;
		for(int j=1;j<=num[i];j++)
		{
			f[++now]=fa[fat];
			cnt++;
			if(cnt==x) fat++,cnt=0;
		}
		fa.clear();
		for(int j=tmp;j<=now;j++)
		fa.push_back(j);
	}
}
signed main()
{
//	freopen("info.in","r",stdin);
//	freopen("info.out","w",stdout);
	int T=1;
	while(T--)
	{
		cin>>n>>m;
		if(m>n*(n+1)/2||m<2*n-1)
		{
			puts("No");
			continue;
		}
		puts("Yes");
		int l=1,r=n-1;
		while(l<r)
		{
			int mid=l+r>>1;
			if(check(mid)>m) l=mid+1;
			else r=mid;
		}
//		write(l);F(0);
		work(l);
		for(int i=2;i<=n;i++)
		write(f[i]),F(1);
		F(0);
	}
	return 0;
}
```


---

## 作者：Exp10re (赞：1)

小清新构造题。

[一道思路一模一样的题](https://www.luogu.com.cn/problem/CF1311E)，推荐去写一下，~~CF 出原题实锤了~~。

## 解题思路

先简单判定一下无解：当 $s\lt 2n-1$（菊花图）或者 $s \gt \frac {n(n+1)} 2$（链）时显然无解。

注意到题目要求最小值，考虑二分。

注意到对于一棵 $k$ 叉树，若需要使其每颗子树大小之和最小化，那么构造一棵完全 $k$ 叉树显然每颗子树大小之和最小。

**注意到对于任一点，其对于子树大小之和的计数贡献等同于其深度，即子树大小之和等于所有节点深度之和**。显然完全 $k$ 叉树每个节点深度之和最小。

那么我们二分一个最小的 $k$ 使得完全 $k$ 叉树的深度之和小于等于 $s$，然后在这一颗完全 $k$ 叉树上通过移动节点来使得其深度之和等于 $s$。

记节点 $u$ 的深度为 $dep_u$，父亲为 $fa_u$，孩子个数为 $cnt_u$，当前深度之和为 $sum$。具体而言：

- 随机选择一个叶子节点并将其标记，记为 $leaftop$。

- 另找一个叶子节点 $u$，然后分类讨论：

  - 若 $dep_{leaftop}+1-dep_u \leq s-sum$，那么将 $u$ 的父亲设为 $leaftop$。这对 $sum$ 的贡献为 $dep_{leaftop}+1-dep_u$。注意要维护好 $cnt_{fa_u}$，若 $cnt_{fa_u}=0$，说明 $fa_u$ 也成为了一个叶子。
  
  - 否则，不断使 $leaftop\leftarrow fa_{leaftop}$，每一次这样的操作都会使得 $dep_{leaftop}$ 比操作前少 $1$。接下来：
  
    - 若 $cnt_{leaftop}+1 \gt k$，说明在 $k$ 叉树下该节点的孩子已经有 $k$ 个，无法再增加新的孩子，这个时候任取另一个叶子节点作为 $leaftop$ 即可。
    
    - 否则，不断进行以上操作直到 $dep_{leaftop}+1-dep_u = s-sum$，然后将 $u$ 的父亲设为 $leaftop$。该操作进行完毕之后显然 $sum = s$，就结束了。
    
输出所有节点的父亲即可。

## 代码

此处在二分部分计算深度总和的代码是 $O(n)$ 的，也就是说总时间复杂度为 $O(n \log n)$。理论使用数学计算能做到 $O(\log_k n)$ 计算深度总和，即总时间复杂度为 $O(\log^2 n +n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=100010;
long long n,m;
long long fa[MAXN],leaftop,leafset[MAXN],l,r,dep[MAXN],cnt[MAXN];
long long check(long long x)
{
	long long sum=0,i,j;
	dep[1]=1;
	sum=1;
	for(i=1;(i-1)*x+2<=n;i++)
	{
		for(j=(i-1)*x+2;j<=min(i*x+1,n);j++)
		{
			dep[j]=dep[i]+1;
			sum+=dep[j];
		}
	}
	return sum;
}
void work(long long x)
{
	long long i,j,sum=0,maxn=0;
	dep[1]=1;
	for(i=1;(i-1)*x+2<=n;i++)
	{
		sum+=dep[i];
		for(j=(i-1)*x+2;j<=min(i*x+1,n);j++)
		{
			fa[j]=i;
			dep[j]=dep[fa[j]]+1;
			cnt[i]++;
		}
	}
	l=1;
	r=0;
	leaftop=i;
	j=i;
	for(;i<=n;i++)
	{
		if(dep[i]>maxn)
		{
			maxn=dep[i];
			leaftop=i;
		}
	}
	i=j;
	for(;i<=n;i++)
	{
		sum+=dep[i];
		if(i!=leaftop)
		{
			r++;
			leafset[r]=i;
		}
	}
	while(sum<m)
	{
		if(dep[leaftop]+1-dep[leafset[l]]<=m-sum)
		{
			sum+=dep[leaftop]+1-dep[leafset[l]];
			cnt[fa[leafset[l]]]--;
			if(cnt[fa[leafset[l]]]==0)
			{
				r++;
				leafset[r]=fa[leafset[l]];
			}
			fa[leafset[l]]=leaftop;
			cnt[leaftop]++;
			fa[leafset[l]]=leaftop;
			dep[leafset[l]]=dep[leaftop]+1;
			leaftop=leafset[l];
		}
		else
		{
			while(dep[leaftop]+1-dep[leafset[l]]>m-sum)
			{
				leaftop=fa[leaftop];
				if(cnt[leaftop]+1>x)
				{
					leaftop=leafset[r];
					r--;
				}
			}
			sum+=dep[leaftop]+1-dep[leafset[l]];
			cnt[fa[leafset[l]]]--;
			if(cnt[fa[leafset[l]]]==0)
			{
				r++;
				leafset[r]=fa[leafset[l]];
			}
			fa[leafset[l]]=leaftop;
			cnt[leaftop]++;
			dep[leafset[l]]=dep[leaftop]+1;
			leaftop=leafset[l];
		}
		l++;
	}
	return;
}
int main()
{
	long long l,r,mid,ans,i;
	scanf("%lld%lld",&n,&m);
	if(m<n*2-1||m>n*(n+1)/2)
	{
		printf("No\n");
		return 0;
	}
	l=1;
	r=n-1;
	while(l<=r)
	{
		mid=(l+r)/2;
		if(check(mid)<=m)
		{
			ans=mid;
			r=mid-1;
		}
		else
		{
			l=mid+1;
		}
	}
	work(ans);
	printf("Yes\n");
	for(i=2;i<=n;i++)
	{
		printf("%lld ",fa[i]);
	}
	return 0;
}
```

---

## 作者：Albedo (赞：1)


## Solution

首先，我们考虑二分答案，先算出这个分支系数最小是多少，但难点就在于如何判断，首先我们知道，如果不考虑分支系数，$ s $ 的最小值为 $ 2\times n -1 $ ，最大值为 $ \frac{n\times(n-1) }{2} $ ,而前者的分支系数为 $ n-1 $ 后者的分支系数为 $ 1 $,一种是菊花图，一种是链，那这种构造方式是不是能给我们一点启发，就是我们可不可以算出在分支系数为 $ a $ 时，他的 $ s $ 的上限与下限的构造方案是不是一成不变的，而当我们求出了最小的分支系数过后，我们就可以开始真正的构造了。

我们首先可以发现，题目中的要求可以转化为 $ \sum_{i=1}^n dep_i=s $ ，也许你会问这样子转化一下有什么用处，但我们发现，如果题目中的要求转化成了这样，我们只需要更换一个点的深度就可以改变他整棵树的价值，而且可以做到，就是单纯 $ +1 $ ，但是我们发现，这样子是会 $ T $ 的，因为 $ s $ 的范围在 $ (0,10^{10}] $ ,那我们就要加速。我们考虑最左边的那条链为最终链，那么对于一个点，他改变一定是改变到最左边那条链，而改变的上限就是 $ sum-dep[now]+1 $ ，而 $ sum $ 就是那条最终链的长度。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
inline long long read()
{
  long long x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
long long pow(long long x,long long y,long long p)
{
    long long ans=1;
    for (;y;y>>=1,x=x*x % p)
        if (y&1) ans=ans*x % p;
    return ans;
}
long long up,U,ww,aa[1001010],fre[1001010],ls[1001010],nw,id,deg[1001010],gg,j,dfn[1001010],di,fat[1001010],n,i,idd,dfnn[1001010],K,l,r,mid,ans,down,bb,dif,now,ed[1001010],sum,dep[1001010],e[1001010];
vector<int> edge[1001010];
bool exist[1001010];
void sc(int x,int fa)
{
	dep[x]=1;
	for (int i=0;i<edge[x].size();i++)
	    {
	    	int y=edge[x][i];
	    	if (dep[y]==0)
	    	    {
	    	    	sc(y,x);dep[x]+=dep[y];
				}
		}
}
long long calc(long long mid)
{
	for (i=1;i<=n;i++) edge[i].clear(),dep[i]=0;
    for (i=1;i<=n;i++) fre[i]=0;
    int nw=1;
    for (i=2;i<=n;i++)
         {
         	edge[nw].push_back(i);
         	fre[nw]++;
         	if (fre[nw]==mid) nw++;
		 }
	sc(1,0);
	long long ans=0;
	for (i=1;i<=n;i++) ans+=dep[i];
	return ans;
}
void sc_build(int x,int fa)
{
id++;dfnn[id]=x;
for (int i=0;i<edge[x].size();i++)
	if (edge[x][i]!=fa)
	 {
     	dep[edge[x][i]]=dep[x]+1;
     sc_build(edge[x][i],x);
     }
}
int main()
{
	//ios::sync_with_stdio(0);cin.tie();cout.tie();
    n=read();K=read();
    if ((K<2*n-1)||(K>n*(n+1)/2))
          {
          	puts("No");return 0;
		  }
	puts("Yes");
    l=1;r=n-1;
    while (l<=r)
         { 
         mid=(l+r)/2;
         if (calc(mid)<=K)
              {
              ans=mid;r=mid-1;
		      }
		  else l=mid+1;
		 }
	down=calc(ans);dif=K-down;bb=1;
//	cout<<dif<<endl;
	for (now=0;now<n;now+=bb,bb*=ans)
	    sum++,ed[sum]=now+1,exist[now+1]=true;
	     //cout<<"fuck"<<sum<<endl;
	for (i=1;i<=n;i++) edge[i].clear();
	for (i=1;i<=n;i++) fre[i]=0,dep[i]=0;
	dep[1]=1;
nw=1;
	for (i=2;i<=n;i++)
	     {
	     	edge[nw].push_back(i);deg[nw]++;deg[i]++;
	     	fat[i]=nw;
	     	fre[nw]++;
	     	if (fre[nw]==ans) nw++;
		 }
	sc_build(1,0);idd=sum;
	for (i=1;i<=n;i++)
	    if (exist[i]==false)
	       {
	       	gg++;up=dfnn[i];for (j=dfnn[i];j;j=fat[j]) up=j;
	       	U=max(U,dep[i]);
	       	if ((gg>1)&&(up==2))
	       	     {
	       	     	ww++;aa[ww]=i;
					}
			 }  
	for (i=U;i>=1;i--)
	     for (j=1;j<=ww;j++)
	         if (dep[aa[j]]==i)
	             {
	             	idd++;dfn[idd]=aa[j];exist[aa[j]]=true;
				 }
		ww=0;
		for (i=1;i<=n;i++)
		   if (exist[i]==false)
	       {
	       	gg++;up=dfnn[i];for (j=dfnn[i];j;j=fat[j]) up=j;
	       	U=max(U,dep[i]);
	       	if ((gg>1)&&(up!=2))
	       	     {
	       	     	ww++;aa[ww]=i;
					}
			 }  
	for (i=U;i>=1;i--)
	     for (j=1;j<=ww;j++)
	         if (dep[aa[j]]==i)
	             {
	             	idd++;dfn[idd]=aa[j];
				 }
    //sum:原先链的长度。
    //cout<<fat[2]<<endl;
    if (dif!=0)
        {
    for (i=sum+1;i<=n;i++)
        { 
        now=dfn[i];//cout<<now<<endl;
        if (dif>sum-dep[now]+1)  
             { 
             dif-=(sum-dep[now]+1);
             fat[now]=ed[sum];
             sum++;ed[sum]=now;
			 }
		else
		    { 
		    di=dep[now]+dif-1;
		    //cout<<ed[di]<<endl;
		    dif=0;
		    fat[now]=ed[di];break;
			}
		}
    }
    //cout<<"------"<<dif<<"------"<<endl;
for (i=2;i<=n;i++) printf("%d ",fat[i]);
    return 0;
}

```



---

## 作者：happybob (赞：0)

有点太厉害了。

遇到构造题束手无策。

比较显然的，最小和最大的两种分别是链和菊花。所以 $s$ 不在范围内必然无解。

然后我们先考虑怎么确定最终的答案，即最大儿子大小的最小值。首先注意到可以二分，假设二分答案为 $x$，我们要验证是否存在树，每个点儿子数量 $\leq x$，且每个点子树大小求和为 $s$。考虑把子树大小求和变成每个点深度求和，容易验证这是等价的。那么比较容易看出，深度求和最大还是链，最小是一棵完全 $x$ 叉树。我们猜测深度求和是连续的，所以二分是对的，那么我们就可以在 $O(n \log n)$ 的复杂度内求出这个答案。

然而就止步于构造了。最后至少想了 $30$ 分钟以上才想出来构造方式。

考虑对于答案 $x$，先构造一棵完全 $x$ 叉树。我们发现此时必然是每个点深度之和小于等于目标 $s$。我们考虑拎出最深的那层的某个点，然后将其他点按照深度挂在这个点为根的下面一条链上，此时深度之和与 $s$ 的差不断减小，直至某个时刻，挂在最下面会使得深度之和超过 $s$。这个时候把这个点挂到这条链最低点上面的某个组先上，就可以得到正确构造。此时链上每个点儿子数必然 $\leq 2$，原本的点儿子数都 $\leq x$。而当 $x=1$ 时我们根本不需要调整，故这个构造是正确的。

[Submmision link.](https://codeforces.com/problemset/submission/1098/263490811)

深深感受到了自己的弱小。

---

## 作者：hegm (赞：0)

### [Construct a tree](https://www.luogu.com.cn/problem/CF1098C)

整体分成两部分，判断和方案。

首先我们把子树大小和转化成为每个节点的深度和。

判断还是比较简单的，首先我们二分一个分支系数 $k$（显然具有可二分性）

那么这种情况下，一个树的最小权值是形如下的方式。

![](https://cdn.luogu.com.cn/upload/image_hosting/q19xbggx.png)

第一层 $k^0$ 个点，第二层 $k^1$ 个点 $\cdots$

最大的贡献是 

![](https://cdn.luogu.com.cn/upload/image_hosting/37crkcy5.png)

贡献是 $1+2+3\cdots n-1+n$

我们来证明结论，只要 $s$ 在 $[\min,\max]$ 的区间内即可。

我们尝试从最小一步一步变成最大：

![](https://cdn.luogu.com.cn/upload/image_hosting/q19xbggx.png)

还是以这张图为原型,我们取 $1-2-4-8$ 为主路径。

每次操作可以视作将一个节点的深度增加 $1$，并且由于没有深度限制，所以一定存在这样一种方案。

比如我们可以把 $9$ 接到 $8$ 的下方，以此类推，每次把一个节点深度下调 $1$ 即可。

那么最后就会成为一条链子的情况。

所以在 $[\min,\max]$ 里的所有数都能取到，问题在于如何输出方案。

一步一步前进肯定是不行的，我们考虑如下的方法。

每次选择深度最大并且不在主路径的节点，把它接到主路径上。

考虑这样的增长速度，容易发现，大概顺序是第一次增长 $1$，第二次增长 $2$，这样的速度（中途可能会出现增长速度增加 $2$ 的情况，因为原本深度最大的节点用完了，不过不影响）。

等到某次这样的增长即将超过我们的答案的时候，我们就暂停。

考虑下一次增长权值为 $x$ 会超过 $s$，那么我们就不挪动到主路径的底部了，而是挪到主路径上的某一个孩子上，那么这样增加的权值可以在 $[0,x]$ 之间。

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define ull unsigned long long
#define make make_pair
#define N 100005
#define int long long
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,s,siz[N],fa[N],dep[N];
bool check(int x)
{
	int sum=1,lim=0;dep[1]=1;
	for(int i=2;i<=n;i++)
	{
		fa[i]=(i+x-2)/x;
		dep[i]=dep[fa[i]]+1;
		sum+=dep[i];
	}
	for(int i=1;i<=n;i++)lim+=i;
	if(sum<=s&&lim>=s)return 1;
	return 0;
}
signed main()
{
	n=read();s=read();
	int l=1,r=n,mid;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid))r=mid-1;
		else l=mid+1;
	}
	if(l==n+1)cout<<"No\n";
	else 
	{
		stack<int> t;t.push(1);
		stack<int> q;
		int k=r+1,cnt=k;
		dep[1]=1;s--;
		for(int i=2;i<=n;i++)
		{
			if(i-t.top()==cnt)
			{
				t.push(i);
				cnt*=k;
			}
			else q.push(i);
			fa[i]=(i+k-2)/k;
			dep[i]=dep[fa[i]]+1;
			s-=dep[i];
		}
		while(t.size()&&q.size()&&s>=dep[t.top()]+1-dep[q.top()])
		{
			s-=dep[t.top()]+1-dep[q.top()];
			fa[q.top()]=t.top();
			dep[q.top()]=dep[t.top()]+1;
			t.push(q.top());q.pop();
		}
		if(t.size()&&q.size()&&s)
		{
			int w=dep[t.top()]+1-dep[q.top()]-s;
			while(w--)t.pop();
			fa[q.top()]=t.top();
		}
		cout<<"Yes\n";
		for(int i=2;i<=n;i++)
		cout<<fa[i]<<" ";
	}
	return 0;
}

```

---

## 作者：EuphoricStar (赞：0)

考虑一个显然的转化，$\sum sz_i = \sum dep_i$。所以要构造一棵 $\sum dep_i = s$ 的树，使得最大儿子数最小。

考虑二分这个儿子数。也就是二分到 $x$ 时计算满 $x$ 叉树的 $\sum dep_i$。

然后我们现在有一个满 $x$ 叉树，其中 $\sum dep_i \le s$。我们希望在不影响最大儿子数 $x$ 的前提下，让 $\sum dep_i$ 增加至 $s$。

考虑从前往后遍历，贪心地判断 $dep_i$ 是否能增加。算出增加 $dep_i$ 的最小 $\sum dep_i$。如果此时 $\sum dep_i \le m$ 那么就增加。这样可以覆盖到每一个 $s$。

得出每个点的 $dep_i$ 后考虑构造它的父亲。贪心地选上一层儿子数最小的点当父亲即可。

时间复杂度 $O(n \log n)$。

[code](https://codeforces.com/contest/1098/submission/242695787)

---

## 作者：Qiaoqia (赞：0)

退役选手玩玩构造。  

首先我们要确定答案是多少，因为叉数所能达到的最小子树和是随着叉数大小而递增的，所以枚举叉数 $k$，填一个完全 $k$ 叉树看看答案是否小于 $s$，找到第一个小于 $s$ 的即可。  
因为完全 $k$ 叉树深度只有 $\log$ 级别，所以这部分时间复杂度是 $\mathcal O(n \log n)$ 的。因为从完全 $k$ 叉数开始，任意时刻（除了成为一条链）存在一种方案使得叉数不增加且一个挪动到下一层，所以对于 $k$ 叉树一定有解。

考虑如何构造出这个解，可以把树上问题转换成序列上问题，即求序列 $a$ 满足 $\sum a = n$ 且 $\max_{i = 2}^r \frac{a_i - a_{i - 1}}{a_{i - 1}} \le k$ 且 $\sum_{i = 1}^r i \cdot a_i = s$。  
同样可以从满的情况开始移动。手玩一下 $k = 2$ 的情况可以发现，如果确保一个后面的都是这一个的 $\frac{1}{k}$ 及以下，那么就可以随便往后移动，容易证明，这对于 $k > 2$ 同样适用。  
所以就有了这样一个做法，搞俩指针 $l, r$，每次从 $r$ 遍历到 $l$，若 $a_r = k^{l-1}$ 则 $r$ 右移一个，如果当前的大于 $k^{l - 1}$ 则需要移动，如果当前塞到 $a_r$ 去不会使答案超出 $s$ 那么移动到最右边，否则移动到合适的位置终止构造。  
每次最多遍历树的所有结点，$l$ 最多移动 $\log$ 次，所以复杂度是 $\mathcal O(n \log n)$ 的。

Codeforces 提交记录：[#158536993](https://codeforces.com/contest/1098/submission/158536993)。

---

## 作者：cmll02 (赞：0)

紫题吓人的，显然没到这个难度。

容易发现子树大小的和是每个点深度之和。

考虑二分答案，设当前答案是 $k$，我们先放一条链，然后每次将链深度最大的点接到其他地方去。

贪心的想，直接往深度最小的度数没超 $k$ 的地方接上去。

一步一步让深度的和逼近题目给出的数就行了。

这样得出了一组深度，构造就比较简单了。

[Code](https://paste.ubuntu.com/p/jHhFRsvmm8/)

---

