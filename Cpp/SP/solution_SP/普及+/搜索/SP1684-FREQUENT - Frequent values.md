# FREQUENT - Frequent values

## 题目描述

You are given a sequence of **n** integers **a $ _{1} $ , a $ _{2} $ , ... , a $ _{n} $**  in non-decreasing order. In addition to that, you are given several queries consisting of indices **i** and **j** (_1 ≤ i ≤ j ≤ n_). For each query, determine the most frequent value among the integers **a $ _{i} $ , ... , a $ _{j} $** .

   
#### Input Specification

 The input consists of several test cases. Each test case starts with a line containing two integers **n** and **q** (_1 ≤ n, q ≤ 100000_). The next line contains **n** integers **a $ _{1} $ , ... , a $ _{n} $**  (_-100000 ≤ a $ _{i} $ ≤ 100000_, for each _i ∈ {1, ..., n}_) separated by spaces. You can assume that for each _i ∈ {1, ..., n-1}: a $ _{i} $ ≤ a $ _{i+1} $_ . The following **q** lines contain one query each, consisting of two integers **i** and **j** (_1 ≤ i ≤ j ≤ n_), which indicate the boundary indices for the query.

 The last test case is followed by a line containing a single 0.

   
#### Output Specification

 For each query, print one line with one integer: The number of occurrences of the most frequent value within the given range.

   
#### Sample Input

 ```
10 3
-1 -1 1 1 1 1 3 10 10 10
2 3
1 10
5 10
0
```
   
#### Sample Output

 ```
1
4
3
```
- - - - - -

_A naive algorithm may not run in time!_

# 题解

## 作者：沉MO_Official (赞：11)

#### 题目：

[SP1684](https://www.luogu.com.cn/problem/SP1684)

#### 题目难度：

普及+/提高-

#### 孪生题目编号：

[UVA11235](https://www.luogu.com.cn/problem/UVA11235)

----
#### 部分分写法：

$$\text{A naive algorithm may not run in time!}$$

~~所以部分分写法是朴素算法~~

极端朴素，暴力枚举统计什么的我也不太清楚毕竟上来就是冲着正解去的

----
#### 正解：

算法：$\text{RMQ +}$ 二分查找

对于这个给定序列，我们可以这样处理（以样例为例）：

![](https://cdn.luogu.com.cn/upload/image_hosting/9kp24va5.png)

这个应该很好做，一个 $cnt$，一个前缀和。

然后，对于每个区间 $[L,R]$，二分查找与之对应的$l,r$（$L,R$ 以 $5,10$ 为例）， $l$ 表示 $L$ 所在区块的右端，$r$ 表示 $R$ 所在区块的左端：

![](https://cdn.luogu.com.cn/upload/image_hosting/tqswqr6r.png)

实际代码实现中，$l,r$ 对应的是空隙左边那个数。

该区间中的答案有 $3$ 种可能：

- $[L,l]$ 中元素个数 $presum_l-L+1$

- $(l,r]$ 中的区块做 $\text{RMQ}$ ，找个数最大的。 $max(f_{l+1,s},f_{r-(1<<s)+1,s})$

- $(r,R]$ 中元素个数 $R-presum_r$

![](https://cdn.luogu.com.cn/upload/image_hosting/d4j8fmhu.png)

以上 $3$ 种情况取 $\max$ 值。

注意一下 $l,r$ 的特判。

做完了。

----
#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int LOG=17;
int tot,n,q,a[100005],cnt[100005],presum[100005],Log[100005],f[100005][LOG+1],L,R;
int findL()//二分找l
{
	int Ll=1,Rr=tot,ans=0;
	while(Ll<=Rr)
	{
		int mid=(Ll+Rr)/2;
		if(presum[mid]<L)
			ans=mid,Ll=mid+1;
		else
			Rr=mid-1;
	}
//	printf("%d ",ans);
	return ans+1; //注意要+1,因为找到的是l的左边
}
int findR()//二分找r
{
	int Ll=1,Rr=tot,ans=0;
	while(Ll<=Rr)
	{
		int mid=(Ll+Rr)/2;
		if(presum[mid]<R)
			ans=mid,Ll=mid+1;
		else
			Rr=mid-1;
	}
//	printf("%d ",ans);
	return ans; 
}
int main()
{
	cin>>n;
	while(n!=0)//注意是多组数据！
	{
		tot=q=0;
		memset(a,0,sizeof(a));
		memset(cnt,0,sizeof(cnt));
		memset(f,0,sizeof(f));
		memset(presum,0,sizeof(presum));
		
		scanf("%d",&q);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			if(a[i]==a[i-1])
				cnt[tot]++;
			else
				cnt[++tot]++;//cnt的实现
		}
		Log[0]=-1;
		for(int i=1;i<=tot;i++)
			f[i][0]=cnt[i],Log[i]=Log[i>>1]+1,presum[i]=presum[i-1]+cnt[i];//cout<<cnt[i]<<" ";
       		//presum的实现
		//cout<<endl;
		for(int j=1;j<=LOG;j++)
			for(int i=1;i+(1<<j)-1<=tot;i++)
				f[i][j]=max(f[i][j-1],f[i+(1<<j-1)][j-1]);//RMQ
		for(int i=1;i<=q;i++)
		{
			scanf("%d%d",&L,&R);
			int l=findL(),r=findR();
			if(l==r)
			{
				printf("%d\n",max(presum[l]-L+1,R-presum[r]));//特判1，注意个数是否要+-1，可以自己去画图思考。
				continue;
			}
			if(r<l)//特判2
			{
				printf("%d\n",R-L+1);
				continue;
			}
			int s=Log[r-l];
			//printf("%d %d %d\n",max(f[l+1][s],f[r-(1<<s)+1][s]),max(presum[l]-L+1,R-presum[r]),max(max(f[l+1][s],f[r-(1<<s)+1][s]),max(presum[l]-L+1,R-presum[r])));
			printf("%d\n",max(max(f[l+1][s],f[r-(1<<s)+1][s]),max(presum[l]-L+1,R-presum[r])));//注意是f[l+1]因为不含第l项
		}
		cin>>n;
	}
	return 0;
}

```

---

## 作者：ez_lcw (赞：6)

# RMQ优化
**这道题其实可以预处理出以$i$结尾的最长连续出现次数最大的序列，记为$dp[i]$，也就是$rmq[i][0]$。**

**然后再用平常的方法合并$rmp$，最后答案时处理一波就行了。**

放代码：
```cpp
#include<cstdio>
#include<cmath>
#include<iostream>

#define N 100001
#define K 17
#define Log2(n) (int)(log((double)(n))/log(2.0))

using namespace std;

int n,q,a[N],dp[N],p[N][K];

void RMQ()//RMQ模板
{
	for(int i=1;i<=n;i++)p[i][0]=dp[i];//RMQ初始化
	for(int j=1;j<=Log2(n+1);j++)
	{
		for(int i=1;i+(1<<j)-1<=n;i++)
		{
			p[i][j]=max(p[i][j-1],p[i+(1<<(j-1))][j-1]);//RMQ合并
		}
	}
}

int ask(int l,int r)//询问
{
	if(l>r)return 0;
	int k=Log2(r-l+1);
	return max(p[l][k],p[r-(1<<k)+1][k]);
}

int main()
{
	while(~scanf("%d%d",&n,&q)&&n)
	{
		dp[1]=1;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			if(i>1) dp[i]=(a[i]==a[i-1]?dp[i-1]+1:1);//如果这个数和上一个数一样，那么dp[i]=dp[i-1]+1，否则为1
		}
		RMQ();
		while(q--)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			int now=l;
			while(now<=r&&a[now]==a[now-1])now++;//这里有一个小细节，就是我们先求出以l开头的最长符合题意的序列
			printf("%d\n",max(now-l,ask(now,r)));
		}
	}
}
```

---

## 作者：windrizzle (赞：2)

### 题意

多组测试数据。

给你$n$个数, 以非递减的顺序给出。

再给你$q$个询问,

每个询问给你两个数$a$ $b$。

查询$a$ $b$区间内的众数的出现次数。

### 题解

给大家介绍一种比较简单的方法——使用st表。

st表用于区间最值查询（RMQ），是运用于**静态区间**的求最值。st表的方法非常简单，先预处理然后查询，就好了。其实st表就是一种另类的dp。

### 代码

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
int n,m,ans;
int a[100001];
int dp[100001][26];
int mp[100001];
void sst()//st表
{
	for(int i=1;i<=n;i++) dp[i][0]=mp[i];
	int dd=(int)(log((double)(n+1))/log(2.0));
	for(int i=1;i<=dd;i++)
		for(int j=1;j+(1<<i)-1<=n;j++)
			dp[j][i]=max(dp[j][i-1],dp[j+(1<<(i-1))][i-1]);
}
int ask(int x,int y)
{
	if(x>y)return 0;
    int k=(int)(log((double)(y-x+1))/log(2.0));
    return max(dp[x][k],dp[y-(1<<k)+1][k]);
}
int main()
{
	ios::sync_with_stdio(false);
	while(1)
	{
		cin>>n;
		if(n==0) return 0;
		cin>>m;
		mp[1]=1;
		for(int i=1;i<=n;i++) 
		{
			cin>>a[i];
			if(i>1) 
			{
				if(a[i]==a[i-1]) mp[i]=mp[i-1]+1;
				else mp[i]=1;
			}
		}
		sst();
		while(m--)
		{
			int x,y;
			cin>>x>>y;
			int now=x;
            while(now<=y&&a[now]==a[now-1])now++;
            cout<<max(now-x,ask(now,y))<<endl;
		} 
	}
	return 0;
}
```


---

## 作者：ShuraEye (赞：2)

看大佬们都是清一色RMQ,本蒟蒻就来一发线段树打法

在做此题前，还是推荐大家先去做一道[P3372 【模板】线段树 1](https://www.luogu.org/problemnew/show/P3372)

或是先学一下RMQ。

****
首先用一个$struct$保存每个节点的左边界、右边界以及最大值，这里记得数据范围一定要开到$4*N$！！！。
****

此题有个细节，就是用$f  [i]$去保存以$i$结尾的最长连续字母个数。这样建树就有了依据。

接着在询问环节，先递归找到没有连续字母的子串，减少时间复杂度。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
int n,q;
int f[N],a[N];
struct edge
{
    int l,r;
    int pre;
}tree[N*4+1];
void build(int k,int l,int r)
{
    tree[k].l=l;tree[k].r=r;
    if(l==r)
    {
        int a;
        tree[k].pre=f[l];
        return ;
    }
    int mid=(l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
    tree[k].pre=max(tree[k<<1].pre,tree[k<<1|1].pre);
}
int ask(int k,int l,int r)
{
    if(l<=tree[k].l&&r>=tree[k].r)return tree[k].pre;
    int mid=(tree[k].l+tree[k].r)>>1,t=0;
    if(l<=mid)t=max(t,ask(k<<1,l,r));
    if(r>mid)t=max(t,ask(k<<1|1,l,r));
    return t;
}
int main()
{
    int l,r,e;
    while(scanf("%d %d",&n,&q)&&n)
    {
        memset(tree,0,sizeof(tree));
        memset(f,0,sizeof(f));
        f[1]=1;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            if(i>1)f[i]=(a[i]==a[i-1])?f[i-1]+1:1;
        }
        build(1,1,n);
        while(q--)
        {
            scanf("%d %d",&l,&r);
            e=l;
            while(e<=r&&a[e]==a[e-1])e++;
            printf("%d\n",max(e-l,ask(1,e,r)));
        }
    }
    return 0;
}
```

---

## 作者：叶绫 (赞：1)

###  题意： 
给一个不下降序列，求A到B区间内出现次数最多的数的次数。

### 思路：
序列是按照不下降序列给出来的，所以重复的是连在一起的 。

先预处理一波某个连续数字在当前位置出现的次数。

所以对于给出的区间（A，B），答案就是（A，c）和（c，B）之中最大的。

（A，c）区间预处理过了可以直接给答案，（c，B）区间用神奇RMQ找出。

~~没废话了上代码~~

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath> 
//#define YELING
#include<algorithm>
using namespace std;
const int N=100010;
int st[N][20],dp[N],num[N];
int n,q;
//变量申明
void rmq(){
	for(int i=1;i<=n;i++)
		st[i][0]=dp[i];
	int k=log((double)(n+1))/log(2.0);
	for(int j=1;j<=k;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
//RMQ求最大
int Query(int l,int r){
    if(l>r) return 0;    
	int k=log((double)(r-l+1))/log(2.0);    
	return max(st[l][k],st[r-(1<<k)+1][k]);
} 
//搜索查询
int main(void){    
	while(scanf("%d",&n)!=EOF&&n){
		scanf("%d",&q);
		dp[1]=1;
		for(int i=1;i<=n;i++){
			scanf("%d",&num[i]);
			if(i>1)
				dp[i]=(num[i]==num[i-1]?dp[i-1]+1:1);
                //处理前面（A，c）部分
		}
		rmq();
		while(q--){
			int a,b;
			scanf("%d %d",&a,&b);
			int c=a;
			while(c<=b&&num[c]==num[c-1]) c++;
			cout<<max(Query(c,b),c-a)<<endl;
		}
	}	
	return 0;
}
```

---

## 作者：donkeys (赞：0)

# 先声明,这篇题解可能比较水
~~因为我都说不清我是用什么做的,算法学的多了就忘的忘混的混~~

反正我觉得有st表,树状数组,线段树,分块的影子[手动滑稽]
具体来说就是二进制拆分,分块处理,上级由下级合并,查询的时候就是二进制拆分合并各个块
~~,然后就...莽过了~~
第二次发题解,第一次没过,具体在注释里,如果有某个大佬看了以后能告诉我我到底是用的哪个算法,欢迎评论/私信
```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
int fang[20] = { 1 };
int n, q;
struct LINE
{
	int s = 0, e = 0, sn = 1, en = 1, n = 1;
	//s是开始字符,e是结束字符,sn是开始的连续长度,en是结束的连续长度,n是整体的连续长度
	bool same = 1;
	//整个是不是由同种字符构成
}k[100005][20];
LINE make(LINE a, LINE b)
{//合并两块
	LINE ans;
	ans.n = max(a.n, b.n);
	if (a.e == b.s)
		ans.n = max(ans.n, a.en + b.sn);
	ans.s = a.s, ans.sn = a.sn;
	if (a.same && a.s == b.s)ans.sn += b.sn;
	ans.e = b.e, ans.en = b.en;
	if (b.same && a.e == b.e)ans.en += a.en;
	ans.same = (a.same && b.same && a.e == b.s);
	return ans;
}
int ask(int l, int r)
{//查询答案(二进制拆分)
	LINE ans;
	if (l > r)return -1;
	int len = r - l + 1, i = 0, already = 0;
	//len是区间长度,already是已经处理过的长度,i是位运算右移长度
	while (!(len & 1))len >>= 1, i++;//去零
	ans = k[l][i];//赋初值为第一个小区间
	len >>= 1, already += 1 << i;
	i++;
	for (; len; i++, len >>= 1)
		if (len & 1)
			ans = make(ans, k[l + already][i]), already += 1 << i;//合并
	return ans.n;
}
int main()
{
	for (int i = 1; i < 20; i++)fang[i] = fang[i - 1] << 1;
	while (scanf("%d", &n))
	{
		if (!n)break;
		scanf("%d", &q);
		for (int i = 0; i < n; i++)
		{//输入和初始化
			scanf("%d", &k[i][0].e);
			k[i][0].s = k[i][0].e;
			k[i][0].en = k[i][0].sn = k[i][0].n = k[i][0].same = 1;
		}
		int len = log2(n);//k的第二维度最大值
		for (int i = 1; i <= len; i++)
		{
			for (int j = 0; j < n; j++)
			{//初始化k
				if (j + fang[i] > n)//超长
					break;
				k[j][i] = make(k[j][i - 1], k[j + fang[i - 1]][i - 1]);
			}
		}
		for (int i = 0, a, b; i < q; i++)
		{
			scanf("%d%d", &a, &b);
			printf("%d\n", ask(a - 1, b - 1));
		}
	}
	return 0;
}
```


---

## 作者：极寒神冰 (赞：0)

题目让我们在一个非降序的子序列求出现次数最多的一个数的次数

可以先统计每个数出现的次数保存在一个数组上，然后就是一个区间求最值问题，本人使用ST表实现。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=300010;
int a[N],b[N];
int dp[22][N];
int Log[N];
int bel[N],b_l[N],b_r[N];
int n,m,q;
inline void init_st()//ST表预处理
{
	Log[0]=-1;
	for(int i=1;i<=n;i++)
	{
		Log[i]=Log[i>>1]+1;//预处理最大的小于2^i是多少
	}
	for(int i=1;i<=n;i++)
	{
		dp[0][i]=a[i];//初始化
	}
   //枚举层次 
	for(int j=1;j<=21;j++)
	{
   	  ////枚举起点
		int limit=n-(1<<j)+1;
		for(int i=1;i<=limit;i++)
		{
			dp[j][i]=max(dp[j-1][i],dp[j-1][i+(1<<(j-1))]);
		}
	}
} 
inline int ask(int x,int y)
{
	int len=y-x+1;
	int k=Log[len];//找到最大的一个k满足2^k小于len 
	return max(dp[k][x],dp[k][y-(1<<k)+1]);	
} 
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f; 
}
int main()
{
	while(scanf("%d",&m)==1)
	{
		if(m==0) return 0;
		q=read();
		for(int i=1;i<=m;i++)
		{
			b[i]=read(); 
		} 
		memset(a,0,sizeof(a));
		memset(dp,0,sizeof(dp));
		memset(b_l,0,sizeof(b_l));
		memset(b_r,0,sizeof(b_r));
		n=1;a[1]=1;b_l[1]=1;bel[1]=1;
		for(int i=2;i<=m;i++)
		{
			if(b[i]!=b[i-1])//如果遇到不同的数
			{
				a[++n]=0; 
				b_l[n]=i; //第n个数最左边的数字的下标为i
				b_r[n-1]=i-1; ////第n-1个数最右边的数字的下标为i
			}
			a[n]++;
			bel[i]=n;
		} 
		b_r[n]=m;
		init_st();
		while(q--)
		{
			int l=read(),r=read();
			if(b[l]==b[r])
			{
				printf("%d\n",r-l+1);
				continue;
			}
			int ll=bel[l],rr=bel[r];
			int ans=0;
			ans=max(ans,b_r[ll]-l+1);//寻找不是完整两端的数的个数
			ans=max(ans,r-b_l[rr]+1);
			if(r-l!=1)
			{
				ans=max(ans,ask(ll+1,rr-1));
			}
			printf("%d\n",ans);
		}
	}
}
```


---

## 作者：Sham_Sleep (赞：0)

本题算法：RMQ

读题我们可知，要我们求的是最长相等的序列，而其中有一个重点：

```
非递减序列a1 , a2 , ... , an
```
注意此处是非递减！！！！

所以，按照题目的意思我们可以得知，相同的数都是成段成段出现的，且出现过一次就不会有第二次出现（~~过了这个城就没有下一个村了~~）

由此可得，我们可以将每个段的个数进行预处理。

得到最开始的状态，再由RMQ的st表算法得到一定区间内连续数字最大的长度

主体思路讲明白了之后，我们就要处理细枝末节的了：如果所求区间将可以在一起的区间切开了呢？

我们设l[i]表示以i结尾最多可以有多连续的数，r[i]表示以i开头可以有多少连续的数

所以，我们可以将一次询问拆成三个区间：左边被截断的区间，中间整个整个的区间，右边被截断的区间。所以，这题的大概思路就可以出来了

AC代码

（注意特判，如果询问区间在某一个整体区间之内）

```
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <memory.h> 
using namespace std;

struct node{
	int val;//表示从左往右数第几个数 
	int e;//表示所属组数 
};

int m , n;
int top;
int num[100005]; 
int gr[100005];//每个组数的个数 
int l[100005];//从右往左数的第几个数 
node r[100005];
int st[100005][21];//ST表 

void mem()
{
	memset(gr , 0 , sizeof(gr));
	memset(st , 0 , sizeof(st));
	memset(l , 0 , sizeof(l));
	memset(r , 0 , sizeof(r));
	memset(num , 0 , sizeof(num));
	top = 0;
	return ;
}

int f()
{
	scanf("%d" , &m);
	if(!m) return 0;
	scanf("%d" , &n);
	int sum = 0;
	for(int i = 1; i <= m; ++i){
		scanf("%d" , &num[i]);
		if(num[i] == num[i - 1] || i == 1) //预处理 
		{
			++sum;
			r[i].val = sum;
			r[i].e = top + 1;
		}
		else
		{
			gr[++top] = sum;
			r[i].val = sum = 1; 
			r[i].e = top + 1;
		}
	}
	gr[++top] = sum;
	for(int i = 1; i <= m; ++i){
		l[i] = gr[r[i].e] - r[i].val + 1;//预处理 
	}
	for(int i = 1; i <= top; ++i){
		st[i][0] = gr[i];//st表预处理，因为是求组里面的元素个数最多，所以就用的是gr数组 
	}
	for(int j = 1; 1 << j <= top; ++j){
		for(int i = 1; i + (1 << j) - 1 <= top; ++i){
			st[i][j] = max(st[i][j - 1] , st[i + (1 << j - 1)][j - 1]);//求静态区间最小值 
		}
	}
	int t1 , t2 , t; 
	int l1 , r1;
	for(int i = 1; i <= n; ++i){
		scanf("%d %d" , &t1 , &t2);
		l1 = l[t1] + t1;
		r1 = t2 - r[t2].val;
		if(r[t1].e == r[t2].e - 1) printf("%d\n" , max(l[t1] , r[t2].val)); //区间在同一组的情况下 
		else if(r[t1].e == r[t2].e) printf("%d\n" , t2 - t1 + 1); //区间在相邻组的情况下 
		else {t = log(r[r1].e  - r[l1].e + 1) / log(2); printf("%d\n" , max(max(r[t2].val , l[t1]) , max(st[r[l1].e][t] , st[r[r1].e - (1 << t) + 1][t])));} //区间在毫无关系的两个组下 
	}
	mem();
	return 1;
}

int main()
{
	while(1) if(!f()) break;
	return 0;
}
```


---

## 作者：念古兰 (赞：0)

 _~~emmmm,双倍经验题~~_    
##  “孪生”题目编号 uva11235
下面进入正题：  
首先，我们知道这样一件事情，这个序列是非降序的，也就是说，
### 这个序列里面的相同元素都是在一起的（这个很重要）   
直觉告诉我们，可能要用到分块（就系把一个数据分成几个小块来处理，以此维护数据）  
举个栗子，对于一组数据：  
-1 -1 1 1 1 1 3 10 10 10  
我们可以这样分块：  
-1 -1,1 1 1 1,3,10 10 10  
我们想一下这样子对不对：  
如果这样子来做的话，询问一个区间时，只需要处理中间完整的块跟两端不一定完整的块就可以了。这样子想的话，这道题确实是可以分块的；  
上述的话有些抽象，还是用原来的数据来解释：  
对于一组数据： -1 -1,1 1 1 1,3,10 10 10，将每个元素（不是块）编号为1-10，将块编号为1-4，同时记录每个块的大小与每个元素属于哪一个块；假如我们要查询区间[2,9]，我们找到左端点属于的块与右端点所属于的块，此例子中分别是1跟4。之后，我们找到中间完整的块的大小最大值，此例子中是4。  
然后呢，我们再找出区间覆盖的不完整的块的大小  
例如，左区间与左端点覆盖的大小为[2,2],大小为1，同理，右区间为2。然后比较中间值与两端的大小就可以了  
代码如下，不给太多注释，大家当作是阅读练习 ~~（其实是蒟蒻懒）~~
```cpp
#include <bits/stdc++.h>
#define upd(x) (x--)
//更新值的宏，作用之后看下去就知道了
using namespace std;
const int maxn=1e5+10;
typedef long long ll;
int a[maxn],l[maxn],r[maxn],pos[maxn],cnt[maxn],t=1;
//原数组，块的左端，块的右端，每个点对应的块的编号，每个块的大小，块的序号
int st[maxn][20];
//ST表准备就绪
void Set(int n)
//对大小为n的预处理，从1开始的而不是从0开始的
{
	for(register int i=1;i<=n;i++) st[i][0]=cnt[i];
	for(register int i=1;(1<<i)<=n;i++)
	   for(register int j=1;j+(1<<i)-1<=n;j++)
	   st[j][i]=max(st[j][i-1],st[j+(1<<(i-1))][i-1]);
}
int search(int x,int y)
//查询操作
{
	if(x>y) return 0;
	int j=0,n=y-x+1;
	while((1<<j)<=n) j++;
	upd(j);
	return max(st[x][j],st[y-(1<<j)+1][j]);
	
}
int mymax(int x,int y,int z)
//判断三个数的大小
{
	if(x<y) x=y;//make sure x bigger than y
	if(x<z) x=z;//make sure x bigger than z
	return x;
}
int main()
{
	int n=0,q=0;
	while(scanf("%i",&n)&&n&&scanf("%i",&q))
	{
		memset(a,0,sizeof(a));
		for(register int i=1;i<=n;i++) scanf("%i",a+i);
		for(register int i=1;i<=n;)
		{
			int o=i;
			for(o;o<=n;o++) 
			{
				if(a[o]!=a[i]) break;
				pos[o]=t;
			}
			if(o<=n) upd(o);
			l[t]=i,r[t]=o;
			cnt[t]=o-i+1;
			i=o+1,t++;
		}
		upd(t);//updata the value of t
		Set(t);
		while(q--)
		{
			int x=0,y=0;
			scanf("%i%i",&x,&y);
			if(pos[x]==pos[y]) printf("%i\n",y-x+1);
			else    printf("%i\n",mymax(search(pos[x]+1,pos[y]-1),r[pos[x]]-x+1,y-l[pos[y]]+1));
		}
	}
return 0;
}

```
总结： ST表可以解决很多事情，但总体思路还是将问题转化为区间最值问题，这一步可能需要用到分块或是其他方法做到，时候就利用ST表预处理后就可以快乐地A掉问题了  
判断要不要使用ST表时，还是要判断能不能将问题转化为区间最值问题，可以的话就可以用ST表进行处理


---

## 作者：白いバラの夜 (赞：0)

题目链接：[点击打开链接](http://acm.hdu.edu.cn/showproblem.php?pid=1806)



题目大意：

给你一段连续的递增序列，然后多次查询，每次查询输出查询区间内相同的数出现的最多的次数。

解题思路：

学校内部的比赛碰到的题目，题目看起来异常的简单，基本确定是线段树。刚开始就是想不出来维护的办法，甚至想到用map储存每个点出现次数吧。后来突然想到了什么左连续 最长右连续最长和区间最长连续。思路顿开，遂A。

线段树每个节点维护左连续最长，右连续最长，和区间连续最长，从下往上推。pushup过程不算太难，就是注意左区间右连续和右区间左连续合并要注意值相等才行。剩下可能就查询麻烦一些了，查询的话如果左区间右端点和右区间左端点相同是要加上一种查询情况的，最后取查询出来的最大值就好（听大佬说还可以用什么RMQ算法，还不会， 就先这样啦）。细节看代码，

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <set>
#include <functional>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
int n,m;
struct tree
{
    int l,r,mid;
    int ls,rs,ms;
}t[500000];
int a[200000];
void pushup(int rt)     //从下往上更新
{
    if((t[rt<<1].ls==t[rt<<1].r-t[rt<<1].l+1)&&a[t[rt<<1].r]==a[t[rt<<1|1].l])
        t[rt].ls=t[rt<<1].ls+t[rt<<1|1].ls;
    else
        t[rt].ls=t[rt<<1].ls;
    if((t[rt<<1|1].rs==t[rt<<1|1].r-t[rt<<1|1].l+1)&&(a[t[rt<<1|1].l]==a[t[rt<<1].r]))
        t[rt].rs=t[rt<<1|1].rs+t[rt<<1].rs;
    else
        t[rt].rs=t[rt<<1|1].rs;
    t[rt].ms=max(t[rt<<1].ms,t[rt<<1|1].ms);
    if(a[t[rt<<1].r]==a[t[rt<<1|1].l])      //只有相等才能合并
        t[rt].ms=max(t[rt].ms,t[rt<<1].rs+t[rt<<1|1].ls);
}
void build(int l,int r,int rt)      //建立线段树
{
    int mid=(l+r)>>1;
    t[rt].l=l;t[rt].r=r;
    t[rt].mid=mid;
    if(l==r)
    {
        t[rt].ls=1;
        t[rt].rs=1;
        t[rt].ms=1;
        return ;
    }
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
    pushup(rt);
}
int query(int p,int q,int rt)       //查询稍微麻烦一些
{
    if(t[rt].l==p&&t[rt].r==q)
        return t[rt].ms;
    if(q<=t[rt].mid)
        return query(p,q,rt<<1);
    if(p>t[rt].mid)
        return query(p,q,rt<<1|1);
    else
    {
        int aa=query(p,t[rt].mid,rt<<1);
        int bb=query(t[rt].mid+1,q,rt<<1|1);
        int cc=-1;
        if(a[t[rt<<1].r]==a[t[rt<<1|1].l])      //特判情况
            cc=min(t[rt<<1].rs,t[rt].mid-p+1)+min(t[rt<<1|1].ls,q-t[rt].mid);
        return max(max(aa,bb),cc);
    }
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        if(n==0)
            break;
        scanf("%d",&m);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        build(1,n,1);
        int p,q;
        for(int i=0;i<m;i++)
        {
            scanf("%d%d",&p,&q);
            int g=query(p,q,1);
            printf("%d\n",g);
        }
    }
}


```
按[这](https://blog.csdn.net/f2935552941/article/details/76467724)进入我的csdn博客看原版题解

---

