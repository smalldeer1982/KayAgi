# Take Your Places!

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1556B/1e01fe272756235c22745e77349edf5747f912ab.png)William has an array of $ n $ integers $ a_1, a_2, \dots, a_n $ . In one move he can swap two neighboring items. Two items $ a_i $ and $ a_j $ are considered neighboring if the condition $ |i - j| = 1 $ is satisfied.

William wants you to calculate the minimal number of swaps he would need to perform to make it so that the array does not contain two neighboring items with the same parity.

## 说明/提示

In the first test case the following sequence of operations would satisfy the requirements:

1. swap(2, 3). Array after performing the operation: $ [6, 1, 6] $

In the second test case the array initially does not contain two neighboring items of the same parity.

In the third test case the following sequence of operations would satisfy the requirements:

1. swap(3, 4). Array after performing the operation: $ [1, 1, 2, 1, 2, 2] $
2. swap(2, 3). Array after performing the operation: $ [1, 2, 1, 1, 2, 2] $
3. swap(4, 5). Array after performing the operation: $ [1, 2, 1, 2, 1, 2] $

In the fourth test case it is impossible to satisfy the requirements.

In the fifth test case the following sequence of operations would satisfy the requirements:

1. swap(2, 3). Array after performing the operation: $ [6, 3, 2, 4, 5, 1] $
2. swap(4, 5). Array after performing the operation: $ [6, 3, 2, 5, 4, 1] $

## 样例 #1

### 输入

```
5
3
6 6 1
1
9
6
1 1 1 2 2 2
2
8 6
6
6 2 3 4 5 1```

### 输出

```
1
0
3
-1
2```

# 题解

## 作者：youyou2007 (赞：4)

## Description
给定一个长度为 $n$ 的数组，每次可以交换相邻的两个数，求最少用多少步使得这个数组中任意相邻两个数的奇偶性不同，如果无解输出 $-1$ 。

共有 $T$ 组询问。
## Solution
先考虑无解情况。

由于要求相邻数奇偶性不同，所以奇数个数与偶数个数之差的绝对值肯定要为 $1$ 或 $0$。如果超过 $2$ 就可以直接判定无解了。

对于有解的情况，我们可以只考虑奇数位置或偶数位置归位的步数，因为如果一种归位了，另一种也肯定是归位的。

题目要求的是最小步数，可以把原序列中奇数和偶数的位置记录下来，然后从小到大枚举，向 $1$，$3$，$5$，$7$ .... $2 * n - 1$ 或 $2$，$4$，$6$.... $2 * n$的位置移动，计算一下距离即可。

同时还要看 $n$ 的奇偶性。

如果 $n$ 是奇数，那么看奇数多还是偶数多，把多的那一种给填到奇数的位置上，另一种填到偶数的位置上。

否则，则尝试把奇数给填到奇数位置和偶数位置上，取操作次数的最小值。

## Code
```cpp
// by youyou2007 Aug.
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define rep(i, x, y) for(register int i = x; i <= y; i++)
#define per(i, x, y) for(register int i = x; i >= y; i--)
using namespace std;
int T,a[100005],n,e[100005],o[100005];
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		int t1=0,t2=0,temp=0;
		rep(i,1,n)
		{
			cin>>a[i];
			if(a[i] & 1)
			{
				e[++t1]=i;
			}
			else 
			{
				o[++t2]=i;
			}
		}
		if(abs(t1-t2)>1)//判断无解
		{
			puts("-1");
			continue;
		}
		int ans=0;
		if(n & 1)//n是奇数的情况
		{
			int s=0;
			if(t1 > t2)
			{
				rep(i,1,t1)
				{
					s+=abs(e[i]-(i*2-1));//
				}
				ans=s;
			}
			else
			{
				rep(i,1,t2)
				{
					s+=abs(o[i]-(i*2-1));
				}
				ans = s;
			}
		}
		else//n是偶数的情况，放到奇数位置和偶数位置都要算一遍
		{
			int s=0;
			rep(i,1,t1)
			{
				s+=abs(e[i]-(i*2-1));
			}
			ans=s;
			s=0;
			rep(i,1,t1)
			{
				s+=abs(e[i]-(i*2));
			}
			ans=min(s,ans);
		}
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：KSToki (赞：2)

# 题目大意
给定一个数组，每次交换相邻的两个数，求使数组最终相邻项奇偶性不同所需的最小交换次数。
# 题目分析
大家好，这里是一个赛时没有想到结论的蒟蒻，于是我用了模拟过了这道题。

首先这题只跟奇偶性有关系，那么就只用存 $01$，不需要原数。如果数组中奇数个数与偶数个数相差大于 $1$，那么无解，否则一定有解，输入时就可以将奇数和偶数所在的位置分别存下来备用。

为了避免过多的讨论，当奇数个数不少于偶数个数时，第一个数可以是奇数；奇数个数不多于偶数个数时，第一个数可以是偶数，跑两边整一个 `min` 就搞定了，两种情况类似。确定情况后，顺序从 $1$ 开始填，第 $i$ 位该填第 $\lceil\frac{i}{2}\rceil$ 个奇数或偶数（根据情况），统计距离加起来即可。

这里数字的前移可能会影响其它数的位置，暴力交换肯定不行，需要开一个树状数组维护一下每个数后面有多少个数前移了，和原位置加起来就得到该它前移时的实际位置。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first
#define se second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,Mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,a[2][100001],x,c[100001];
ll ans;
I void update(int x)
{
	for(;x<=n;x+=lowbit(x))
		++c[x];
}
I int sum(int x)
{
	int res=0;
	for(;x;x-=lowbit(x))
		res+=c[x];
	return res;
}
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		a[0][0]=a[1][0]=0;
		For(i,1,n)
		{
			x=read();
			c[i]=0;
			a[x&1][++a[x&1][0]]=i;
		}
		if(abs(a[0][0]-a[1][0])>1)
		{
			puts("-1");
			continue;
		}
		ans=INF;
		if(a[0][0]>=a[1][0])
		{
			ll res=0;
			For(i,1,n)
			{
				int p=a[((i-1)&1)][(i-1)/2+1];
				res+=p+sum(n)-sum(p)-i;
				update(p);
			}
			chkmin(ans,res);
		}
		For(i,1,n)
			c[i]=0;
		if(a[0][0]<=a[1][0])
		{
			ll res=0;
			For(i,1,n)
			{
				int p=a[i&1][(i-1)/2+1];
				res+=p+sum(n)-sum(p)-i;
				update(p);
			}
			chkmin(ans,res);
		}
		putll(ans);
	}
	return 0;
}

```


---

## 作者：felixshu (赞：1)

[我是传送门](https://www.luogu.com.cn/problem/CF1556B)

## 题目大意

给定一个长度 $n$ 数组，每次交换相邻的两个数，求使数组最终相邻项奇偶性不同所需的最小交换次数。

## 分析

分一下情况。

### $n$ 为偶数

- 如果奇数与偶数数量不同，就不行。

- 如果奇数与偶数数量相同，就只有两种情况，奇数在奇数位后者奇数在偶数位，这两种选最小值就好了。

### $n$ 为奇数

- 如果奇数和偶数的个数差大于 $1$，就不行。 否则只存在个数多的数在奇数位这一种情况。 求出该情况的花费即可。

## 下面是通过代码
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t,ans;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		int a[100005],a1[100005],a2[100005],k2=0,k1=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(a[i]%2==0)
			{
				a1[++k1]=i;
			} 
			else
			{
				a2[++k2]=i;
			}
		}
		if(n%2==0)
		{
			if(k1==k2)
			{ 
			long long m1=0,m2=0;
       
	   		 for(int i = 1; i <= k2; i++)
       			 {
       			 	int l=((i-1)<<1)+1;
        		    m1+=abs(a2[i]-l);
        		}
        	for(int i=1;i<=k1; i++)
        		{
        			int l=((i-1)<<1)+1;
        		    m2+=abs(a1[i]-l);
        		}
        		ans = min(m1 , m2);
        		cout<<ans<<endl;
        		continue;
			}
			else
			{
				cout<<"-1"<<endl;
				continue;
			}
		}
		else
		{
			 if(abs(k1- k2) != 1) 
			 {
			 cout<<"-1"<<endl;
			 continue;
			 }
        	if(k2 > k1)
        	{
        	    long long m1 = 0;
         	   for(int i = 1; i <= k2; i++)
          	  {
			  int l=((i-1)<<1)+1;
     	      m1 += abs(a2[i] - l);
            }
            cout<<m1<<endl;
        }
        else
        {
            long long m1 = 0;
            for(int i = 1; i <= k1; i++)
            {
            	int l=((i-1)<<1)+1;
                m1 +=abs(a1[i] - l);
            }
           cout<<m1<<endl;
        }
		}
	}
} 
```


---

## 作者：NXYorz (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1556B)

----
### 题目大意
给定长度为 $n$ 的序列 $a_n$，每次可以交换相邻的两个数，最小化交换次数使得该序列相邻的两个数奇偶性不相同。无解输出 $-1$。

--------
### 分析

讨论 $n$ 的奇偶性。

#### 当 $n$ 为偶数时：
如果奇数和偶数个数不同，无解。
否则有且仅有两种情况: 奇数在奇数位或者奇数在偶数位。
在这两种情况中取最小值即可。

#### 当 $n$ 为奇数时：
如果奇数和偶数的个数差不为 $1$，无解。
否则只存在个数多的数在奇数位这一种情况。
求出该情况的花费即可。

对于每次就花费时可以贪心来求。

--------
#### $\texttt{Code}$
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int eve[N],odd[N];

void work()
{
    int n; scanf("%d",&n); eve[0] = odd[0] = 0;
    for(int i = 1; i <= n; i++)    
    {
        int x; scanf("%d",&x);
        if(x & 1) eve[++eve[0]] = i;
        else odd[++odd[0]] = i;
    }
    long long ans = N * N;
    if(n & 1)
    {
        if(abs(eve[0] - odd[0]) != 1) {printf("-1\n"); return;}
        if(eve[0] > odd[0])
        {
            long long tot = 0;
            for(int i = 1; i <= eve[0]; i++)
            {
                int loc = ((i - 1) << 1) + 1;
                tot += abs(eve[i] - loc);
            }
            ans = min(ans , tot);
        }
        else
        {
            long long tot = 0;
            for(int i = 1; i <= odd[0]; i++)
            {
                int loc = ((i - 1) << 1) + 1;
                tot += abs(odd[i] - loc);
            }
            ans = min(ans , tot);
        }
    }
    else
    {
        if(eve[0] != odd[0]) {printf("-1\n"); return;}
        long long tot = 0;
        for(int i = 1; i <= eve[0]; i++)
        {
            int loc = ((i - 1) << 1) + 1;
            tot += abs(eve[i] - loc);
        }
        ans = min(ans , tot); tot = 0;
        for(int i = 1; i <= odd[0]; i++)
        {
            int loc = ((i - 1) << 1) + 1;
            tot += abs(odd[i] - loc);
        }
        ans = min(ans , tot); tot = 0;
    }
    printf("%lld\n",ans);
}

int main()
{
    //freopen("aa.in","r",stdin);
    int t; scanf("%d",&t);
    while(t--)
        work();
}
```

---

## 作者：EnofTaiPeople (赞：1)

简要翻译，给定一个数列，求最小交换次数，使得他任意相邻两个数满足**不同奇偶**。此题算法：分类讨论，贪心。

AC 时间：12 分钟。

对于什么进行分类呢？由于要使相邻两数不同奇偶，于是要让技术数量和偶数数量精心比较，先贴上代码：
```cpp
switch(ji-ou){
		case 1:for(i=1,x=1;i<=n;++i)
					if(num[i]&1)ans[ai]+=abbs(i-x),x+=2;break;
		case -1:for(i=1,x=2;i<=n;++i)
					if(num[i]&1)ans[ai]+=abbs(i-x),x+=2;break;
		case 0:for(i=1,x=1,ans[0]=0;i<=n;++i)
				if(num[i]&1)ans[0]+=abbs(i-x),x+=2;
			for(i=1,x=2;i<=n;++i)
				if(num[i]&1)ans[ai]+=abbs(i-x),x+=2;
				if(ans[0]<ans[ai])ans[ai]=ans[0];break;
			default:ans[ai]=-1;break;
		}
```
接下来解释原因：
首先，若奇数比偶数多一个，就应该让把奇数放在奇数位，将每个奇数依次入位，并让答案加上交换次数；若偶数比奇数多一个，同理。

然后，如果奇数个数与偶数个数相同，则两者都试一试，取最小值为答案。

最后，如果都不满足，无解，答案为 $-1$。
考场 AC 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll N=1e5+5;
inline ll read(){
	ll an=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-f;c=getchar();
	}while(c>='0'&&c<='9'){
		an=an*10+c-'0';c=getchar();
	}return an*f;
}
ll n,num[N],ans[N],t;
inline ll abbs(ll a){
	return a>=0?a:-a;
}
int main(){
	register ll i,x,ai,ji,ou;
	for(ai=1,t=read();ai<=t;++ai){
		for(i=1,ji=ou=0,n=read();i<=n;++i)
			if((num[i]=read())&1)++ji;else ++ou;
		switch(ji-ou){
			case 1:for(i=1,x=1;i<=n;++i)
					if(num[i]&1)ans[ai]+=abbs(i-x),x+=2;break;
			case -1:for(i=1,x=2;i<=n;++i)
					if(num[i]&1)ans[ai]+=abbs(i-x),x+=2;break;
			case 0:for(i=1,x=1,ans[0]=0;i<=n;++i)
						if(num[i]&1)ans[0]+=abbs(i-x),x+=2;
					for(i=1,x=2;i<=n;++i)
						if(num[i]&1)ans[ai]+=abbs(i-x),x+=2;
					if(ans[0]<ans[ai])ans[ai]=ans[0];break;
			default:ans[ai]=-1;break;
		}
	}
	for(ai=1;ai<=t;++ai)printf("%lld\n",ans[ai]);
	return 0; 
}
```

---

## 作者：I_am_Accepted (赞：0)

### 题意简述

求使一个序列奇偶交错的相邻数交换操作最小次数。

### 题目分析

其实很简单。

先数奇偶数的个数，**特判掉无解的情况**。

若有解，则最终的状态一定是以下其中一个：

1. 第一个数为奇数，剩下的数奇偶交错排列。~~两岸石壁，五色交辉。~~

2. 第一个数为偶数，剩下的数奇偶交错排列。

其中设奇数个数为 $cnt$，偶数个数为 $(n-cnt)$：

若 $cnt>n-cnt$ 则只有情况 1 满足。

若 $cnt<n-cnt$ 则只有情况 2 满足。

若 $cnt=n-cnt$ 则情况 1，2 皆可，其中取最小操作次数即可。

那怎么求**固定首位奇偶**的最小操作次数呢？

首先给出一个显然的定理（好好读读）：

**两个同奇偶的数在最终状态下在序列中的位置前后关系不变的情况的答案不比其他方案更劣。**

也就是说我们**不改变奇数和偶数内部的顺序**就能得到最优方案。 

而且固定首位奇偶性的情况下，最终序列是唯一（有且仅有一个）的。

于是我就得到了一个特别神奇的想法：

1. 给每一个序列里的位置，写上这个位置上的数在最终状态下的位置。

2. 交换相邻两数的过程**相当于冒泡排序这个位置序列**，即最终答案为冒泡排序交换次数。

3. 冒泡排序交换次数又等于**序列逆序对对数**，所以 $O(n\log n)$ 用归并排序求即可。

总体复杂度 $O(Tkn\log n)$，其中 $k$ 为极小的常数。

[show me the code.](https://codeforces.com/contest/1556/submission/128043114)

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

首先统计奇数和偶数的个数，如果个数之差绝对值大于 $1$，则无解。

对于 $n\equiv1\pmod2$ 的情况，我们可以确认每个位置的奇偶性了，否则要分类讨论。

我们可以这样想：只考虑奇数或偶数，将它们移到适当的位置。

可以证明，根据贪心算法，初始位置越往左的数，最后位置也越左。

那么，统计它们初始位置和最后位置的距离，注意只统计一种奇偶性。输出即可。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int t;
int n;
int a[100002];
int cnt[2];
int ans;
int ans2;
inline int absi(int a){
	return a>0?a:-a;
}
inline int mi(int a,int b){
	return a<b?a:b;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1556B_1.in","r",stdin);
	freopen("CF1556B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		cnt[0]=cnt[1]=0;
		for(int i=1;i<=n;++i){
			scanf("%d",a+i);
			++cnt[a[i]%2];
		}
		if(n==1){
			puts("0");
			continue;
		}
		if(absi(cnt[0]-cnt[1])>1){
			puts("-1");
			continue;
		}
		if(n&1){
			ans=0;
			for(int i=1,j=1;i<=n;++i){
				if(a[i]%2==(cnt[0]<cnt[1])){
					ans+=absi(i-j);
					j+=2;
				}
			}
			printf("%d\n",ans);
		}
		else{
			ans=0;
			ans2=0;
			for(int i=1,j=1;i<=n;++i){
				if(a[i]%2==0){
					ans+=absi(i-j);
					j+=2;
				}
			}
			for(int i=1,j=2;i<=n;++i){
				if(a[i]%2==0){
					ans2+=absi(i-j);
					j+=2;
				}
			}
			printf("%d\n",mi(ans,ans2));
		}
	}
}
```

[记录传送门](https://www.luogu.com.cn/record/57220370)

By **dengziyue**

---

