# Missing Numbers

## 题目描述

Chouti is working on a strange math problem.

There was a sequence of $ n $ positive integers $ x_1, x_2, \ldots, x_n $ , where $ n $ is even. The sequence was very special, namely for every integer $ t $ from $ 1 $ to $ n $ , $ x_1+x_2+...+x_t $ is a square of some integer number (that is, a [perfect square](https://en.wikipedia.org/wiki/Square_number)).

Somehow, the numbers with odd indexes turned to be missing, so he is only aware of numbers on even positions, i.e. $ x_2, x_4, x_6, \ldots, x_n $ . The task for him is to restore the original sequence. Again, it's your turn to help him.

The problem setter might make mistakes, so there can be no possible sequence at all. If there are several possible sequences, you can output any.

## 说明/提示

In the first example

- $ x_1=4 $
- $ x_1+x_2=9 $
- $ x_1+x_2+x_3=25 $
- $ x_1+x_2+x_3+x_4=36 $
- $ x_1+x_2+x_3+x_4+x_5=100 $
- $ x_1+x_2+x_3+x_4+x_5+x_6=144 $

 All these numbers are perfect squares.In the second example, $ x_1=100 $ , $ x_1+x_2=10000 $ . They are all perfect squares. There're other answers possible. For example, $ x_1=22500 $ is another answer.

In the third example, it is possible to show, that no such sequence exists.

## 样例 #1

### 输入

```
6
5 11 44
```

### 输出

```
Yes
4 5 16 11 64 44
```

## 样例 #2

### 输入

```
2
9900
```

### 输出

```
Yes
100 9900
```

## 样例 #3

### 输入

```
6
314 1592 6535
```

### 输出

```
No
```

# 题解

## 作者：hegm (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1081E)

大家的做法似乎都是 $n \sqrt n $ 的，本人在这里说下自己的做法。

首先，我们可以看到它奇奇怪怪的范围限制。

数列 $x$ 的偶数项大小不超过 $2\times10^5$。

也就是说差值不能超过 $2 \times 10^5$，因此我们可以计算一下完全平方数的范围。

我们把范围设定为 $(2 \times 10^5 +5)$ 跑一边。

```
long long n,m;
while(n*n-m*m<200005)
{
	n++;
	m++;
}
cout<<n<<" "<<m<<endl;
```

得出的 $n$ 和 $m$ 为 $100003$ 和 $100002$ 。

范围能直接暴力，我们先把 $1$ 到 $100003$ 的完全平方数算出来。（记得开 $\texttt{long long}$）

我们记 $f_i$ 为 $i^2$ ，$c_i$ 为 $i^2-(i-1)^2$。显然对于题面给定的偶数项 $x_i$ 他的值为两个完全平方数的差值，所以他一定能被表示为 $ \sum_{k=i-j}c_k$ 。注意连加一定是连续的。

那么我们怎么找到这个位置呢？

我们考虑定义两个指针 $l$ 和 $r$ 表示左端点和右端点，$cnt$ 表示 $\sum\limits_{k=l}^r c_k$，$now$ 表示当前做完的位置，$to$ 表示当前的前缀和。

对于当前情况

- 如果 $cnt > x_i$ 我们把 $l$ 向右移动一位 $cnt\leftarrow cnt-c_{l-1}$。

- 如果 $cnt < x_i$ 我们把 $r$ 向右移动一位 $cnt\leftarrow cnt+c_r$。

- 如果 $cnt=x_i$ 我们退出当前循环。

- 如果 $l>r$ 返回无解。

最后我们会得出一个区间 $[l,r]$ ，此时 $cnt$ 已经和 $x_i$ 相等了。

我们就需要求出和这个偶数项配套的上一项 $x_{i-1}$ 。

显然我们要让 $to+x_{i-1}=f_{l-1}$ 只有这样我们才能使得前缀和再加上 $x_i$ 为完全平方数。

然后再更新 $now=r$，$to=f_r$ 。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define M 100500
#define N 100005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,a[M],b[M],f[M],c[M],ans[N*2],tot;
signed main()
{
	n=read()/2;
	for(int i=1;i<=N;i++)f[i]=i*i;
	for(int i=1;i<=N;i++)c[i]=f[i]-f[i-1];
	for(int i=1;i<=n;i++)b[i]=read();
	int l=1,r=1,now=0,to=0,cnt;
	for(int i=1;i<=n;i++)
	{
		l=r=now+2;
		cnt=c[l];
		while(cnt!=b[i]&&l<=r)
		{
			if(cnt<b[i])
			{
				r++;
				cnt+=c[r];
			}
			if(cnt>b[i])
			{
				cnt-=c[l];
				l++;
			}
		}
		if(l>r)
		{
			cout<<"No\n";
			return 0;
		}
		ans[++tot]=f[l-1]-to;
		ans[++tot]=b[i];
		now=r;
		to=f[now];
	}
	cout<<"Yes\n";
	for(int i=1;i<=tot;i++)cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：dead_X (赞：2)

## 前言
把输入的 $x_{2i}\leq 10^5$ 看成 $10^{13}$ 然后觉得不可做……
## 思路
显然我们可以把序列每两个数为一组，那么每组最后的前缀和必然是越小越好的。

例如 $x_2=21,x_4=13$。

你当然可以让 $x_1$ 为 $10^2$，$x_1+x_2$ 为 $11^2$，但是后面就无解了。

但是 $x_1$ 为 $2^2$，$x_1+x_2$ 为 $5^2$，$x_1+x_2+x_3=6^2$，$x_1+x_2+x_3+x_4=7^2$。

又由于 $x_{2i+1}$ 是可以自己定的，所以前两项一定越小越好。

那么我们的任务是找到最小的 $\sum x_{2i}$。

由于 $x_{2i}=A^2-B^2=(A-B)(A+B)$，而一个数分乘两个数之积只有 $\sqrt x$ 种选法，此处只需要暴力即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[1000003];
int ans[1000003];
void print(int n)
{
	for(int i=1; i<=n; i++) printf("%lld ",ans[i]);
	return ;
}
signed main()
{
	int c=0;
    int n=read(),m=n/2;
    for(int i=1,lst=0; i<=m; i++) 
    {
    	a[i]=read();
    	int X=0,Y=0,qwq=-1;
    	int j=1;
    	for(; j*j<=a[i]; ++j) ;
    	for(; j>=1; --j)if(a[i]%j==0)
    	{
    		int x=j,y=a[i]/x;
    		if((x&1)!=(y&1)) continue;
    		int a=(x+y)>>1,b=(y-x)>>1;
    		x=b,y=a;
    		if(x<=lst) continue;
    		qwq=0,X=x,Y=y;
    		break;
    	}
    	if(qwq==-1)
    	{
    		puts("No");
    		return 0;
    	}
    	ans[++c]=X*X-lst*lst;
    	ans[++c]=Y*Y-X*X;
    	lst=Y;
    }
    puts("Yes");
    print(n);
	return 0;
}
```

---

## 作者：Lates (赞：1)

大致是官方题解，因为题解里没有 $\mathcal{O(x\log x)}$ 的做法。

设 $x$ 偶数项值域为 $V$。

设 $s_i = t_i ^ 2 = \sum\limits_{j=1}^{i} x_i$，随后 $V \ge x_{2i} = s_{2i} - s_{2i-1} = t^2_{2i} - t^2_{2i-1} \ge 2t_{2i-1}+1$

那么 $t_{2i} < V$。

考虑计算出对于所有 $x\in[1,V]$，使得 $x = b ^ 2 - a ^ 2$ 的二元组 $(a,b)$。 这里是可以暴力的。

直接枚举 $a,b$，如果 $b^2 - a^2 > V$ 就跳出。

复杂度： $V \ge b^2 - a^2 = \sum\limits_{i=a}^{b-1}2i+1\ge(2a+1)(b-a)$

$b-a\le \dfrac{V}{2a+1}<\dfrac{V}{a}$。即 $\mathcal{O}(V\log V)$。

对于每个 $2i$，求出 $t_{2i-1}, t_{2i}$，这时凭直觉找出 $x_{2i} = b^2 - a^2$，中最小的 $a$。这样使得前缀和最小，更有机会有解（大雾）。

```cpp
#include <bits/stdc++.h>
#include <assert.h>
#define int long long 
typedef long long ll;
using namespace std;
inline int read(){
	register int x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')f^=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9')x=x*10+(ch^'0'),ch=getchar();
	return f?-x:x;
}
const int MAX = 2e5+5;
int t[MAX];
int n; 

vector<pair<int,int>>v[MAX];
#define mp make_pair
signed main(){
	for(int a=1;a<=MAX-5;++a) {
		for(int b=a+1, x;(x=b*b-a*a)<=MAX-5;++b) {
			v[x].push_back(mp(a,b));	
		}
	}
	n = read();
	for(int i=2;i<=n;i+=2) {
		int x = read();
		t[i] = -1;
		for(auto h:v[x]) {
			if(h.first > t[i-2]) {
				t[i-1] = h.first;
				t[i] = h.second;
				break; 
			}
		}	
		if(t[i] == -1) {
			puts("No");
			return 0;
		}
	}
	puts("Yes");
	for(int i=1;i<=n;++i) {
		printf("%lld ", t[i] * t[i] - t[i-1] * t[i-1]);
	}
	return 0;
}



```

---

## 作者：yszs (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1081E)

看到题解大部分都是 $O(n \sqrt{n} )$，这里提供一个乱搞的线性做法。

首先我们打出来所有相邻的平方数的差值：

$1,3,5,7,9,11,13,15,17......$

那么给定的偶数项就是依次选择一个不相交且左端点递增的区间求和。

我们可以有两种处理方法，第一种是双指针，第二种是枚举中心点。

都是线性做法。

说一下枚举中心点。

对于偶次项 $a_i$ 是奇数的情况。

我们从第一个差值 $x$ 开始枚举，如果满足 $x\mid a_i$，且下界没有与上一个上界相交，我们就贪心的选这个点，然后跳到上界继续枚举。

对于偶次项 $a_i$ 是偶数的情况同理，不过中心点我们设成枚举点加一。

具体看代码。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=b;i>=a;i--)
#define FOR(i,u) for(int i=head[u];i;i=e[i].next)
#define endl "\n"
#define DeBug(i) cout<<"QwQ "<<i<<endl;
int read()
{
	int x;
	scanf("%lld",&x);
	return x;
}
using namespace std;
const int N=1e6+6;
int a[N];
signed main()
{
	int n=read();
	rep(i,1,n/2)
	{
		a[i*2-1]=-1;
		a[i*2]=read();
	}
	int down=3,last=1,sum=0;
	rep(i,1,n/2)
	{
		if(a[i*2]%2==1)
		{
			while(1)
			{
				if(down>200000) 
				{
					cout<<"No"<<endl;
					return 0;
				}
				if(a[i*2]%down==0)
				{
					int tmp=a[i*2]/down/2;
					int ttmp=((down-1)/2-tmp)*2+1;
					if(ttmp>last)
					{
						a[i*2-1]=(ttmp/2)*(ttmp/2)-sum;
						if(a[i*2-1]<=0)
						{
							down+=2;
							continue;
						}
						last=((down-1)/2+tmp)*2+1;
						down=last;
						break;
					}
				}
				down+=2;
			}
			sum+=a[i*2]+a[i*2-1];
		}
		else
		{
			while(1)
			{
				if(down>200000) 
				{
					cout<<"No"<<endl;
					return 0;
				}
				if(a[i*2]%(down+1)==0)
				{
					if(a[i*2]/(down+1)%2==1)
					{
						down+=2;
						continue;
					} 
					int tmp=a[i*2]/(down+1)/2-1;
					int ttmp=((down-1)/2-tmp)*2+1;
					if(ttmp>last)
					{
						a[i*2-1]=(ttmp/2)*(ttmp/2)-sum;
						if(a[i*2-1]<=0)
						{
							down+=2;
							continue;
						}
						last=((down-1)/2+tmp)*2+1;
						down=last;
						break;
					}
				}
				down+=2;
			}
			sum+=a[i*2]+a[i*2-1];
		}
//		cout<<a[i*2-1]<<" "<<a[i*2]<<endl;
	}
	cout<<"Yes"<<endl;
	rep(i,1,n)
	{
		cout<<a[i]<<" ";
	}
	return 0;
}

```

稍微卡常就到了最优解第二。

---

## 作者：shao0320 (赞：1)

#### CF1081E Missing Numbers

好玩的暴力+数学+乱搞题。

首先一个很显然的思路就是一边算一边维护前缀和。

考虑把这个条件转换一下，设两个相邻的前缀和是$x,y$，然后这个数是$a_i$，那么$a_i=y-x$，由于这俩数都是完全平方数，那么$a_i$显然是两个完全平方数之差，也就是一定可以写成$a_i=p^2-q^2$的形式。

看到这个如此熟悉的形式，想到数学课上老师教过一个东西叫做$x^2-y^2=(x+y)(x-y)$，这个玩意终于可以派上用场了，就大力拆之后枚举即可，因为$a_i$的因数至多只需要枚举到$\sqrt {a_i}$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long
#define N 200005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,now,a[N],b[N],cnt;
signed main()
{
	n=read();
	for(int i=1;i<=n/2;i++)a[i]=read();
	for(int i=1;i<=n/2;i++)
	{
		int tmp,anss=1e15;
		for(int j=1;j*j<=a[i];j++)
		{
			if(a[i]%j)continue;
			int xx=j,yy=a[i]/j;
			if((xx-yy)%2)continue;
			tmp=(xx-yy)*(xx-yy)/4;
			if(tmp>now)anss=min(anss,tmp);
		}
		if(anss==1e15)return puts("No"),0;
		b[++cnt]=anss-now;b[++cnt]=a[i];
		now=a[i]+anss;
	}
	puts("Yes");
	for(int i=1;i<=n;i++)printf("%lld ",b[i]);
	puts("");
	return 0;
}

```



---

## 作者：tommy0221 (赞：1)

VP的时候写了27min才过去，感觉手速不行了。。。

设读进来的数组为 $a$ ，答案数组为 $b$，和题面有点不一样。

发现我们面对的问题其实是，你当前有一个前缀和 $now=b_1+b_2+\cdots+b_{2(i-1)}$ ，需要填上一个数 $x=b_{2i-1}$ ，使得 $now+x,now+x+a_i$ 均为完全平方数，或者判断无解。 

所以 $x=a^2-now^2,a_i=b^2-a^2$ ，$a,b$ 是需要算出来的数

注意到满足 $a_i=b^2-a^2$ 这个东西的 $(a,b)$ 数量其实很少。因为 $a_i=(b+a)(b-a)$ ，因数对最多只有 $\sqrt{a_i}$ 对，暴力枚举然后判断是否合法即可。

合法只需要满足 $a^2>now$ 并且枚举到的两个因数奇偶性相同即可。设枚举到的一对因数为 $(d,\dfrac{a_i}{d})(d\le \sqrt{a_i})$ ，解方程可得 $a=\dfrac{\frac{a_i}{d}-d}{2}$。

在枚举的时候可能有多个满足条件的 $(a,b)$ ，我们应该取 $a$ 最小的那个。因为如果存在 $a$ 更大的解，我们可以通过调整 $x$ 的值直接构造出一个完全一样的，小前缀和的解集包括了大前缀和的解集。

所以复杂度就是枚举因数对，$O(n\sqrt{a})$ 。如果预处理因数可以 $O(n\log n+n\sum\sigma(a_i))$ ，不过为了手速没写。

```cpp
#define int long long
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N=200005;
int n,a[N],b[N],now,tot;
signed main(){
	n=read()/2;
	rep(i,1,n)a[i]=read();
	for(int i=1;i<=n;++i){
		bool flg=0;int res;
		for(int j=sqrt(a[i]);j>=1;--j){
			if(a[i]%j)continue;
			int X=a[i]/j,Y=j;
			if((X-Y)%2)continue;
			res=(X-Y)/2,res*=res;
			if(res<=now)continue;
			flg=1;break;
		}
		if(now>=res||!flg)return puts("No"),0;
		b[++tot]=res-now,b[++tot]=a[i];
		now=a[i]+res;
	}
	puts("Yes");
	rep(i,1,n<<1)printf("%lld ",b[i]);
	puts("");
	return 0;
}
```

---

## 作者：Caro23333 (赞：1)

假设答案数列的前缀和为$S_1,S_2,\dots,S_{2n}$，再令$x_1,x_2,\dots,x_{2n}$为满足$x_i^2=S_i$的正整数，给出的数列为$a_1,a_2,\dots,a_n$，则有$a_k=S_{2k}-S_{2k-1}=(x_{2k}+x_{2k-1})(x_{2k}-x_{2k-1})$。

我们对每个$a_k$求出其所有的因数。对于某一对因数，不妨设为$p,q(p>q)$，其中$a_k=pq$。那么有:
$$p=(x_{2k}+x_{2k-1}),\ q=(x_{2k}-x_{2k-1})$$

即：
$$x_{2k-1}=\frac{p-q}{2},\ x_{2k}=\frac{p+q}{2}$$

由于每一个$x_i$都是正整数，所以需要$p,q$的奇偶性相同。对每一个$a_k$，对所有奇偶性相同的因数对$p,q$，计算出对应的$x_{2k},x_{2k-1}$，称之为一个**x数对**。将每个$a_k$对应的x数对存储起来从小到大排序（关键字任意，不难证明排序后两个关键字都是分别从小到大排序的）。称一个x数对中较小的项为它的**首项**。

从前到后依次构造$x_i$。因为最终答案要求每个数都是正整数，所以要求$S_1<S_2<\dots<S_{2n}$，即$x_1<x_2<\dots<x_{2n}$。也就是说，要求对于$k>1$，需要从$a_k$对应的所有x数对中找到一个首项大于$x_{2k-2}$的选入答案。

利用贪心的思想不难发现，选出最小的、首项大于$x_{2k-2}$的进入答案最容易使后续满足条件，所以通过二分查找来完成这一过程，从而完成构造答案。

对于无解的判定，有两种情况：

- 某一个$a_k$对应的x数对集合为空；
- 某一个$a_k$对应的x数对集合中不存在首项比$x_{2k-2}$更大的x数对。

这都是容易判定的。

时间复杂度至多为$O(n\sqrt{n\log{n}})$。

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
const int MAXN = 200005;
inline int readint()
{
	int res = 0;
	char c = 0;
	while(!isdigit(c))
	    c = getchar();
	while(isdigit(c))
	    res = res*10+c-'0', c = getchar();
	return res;
}
int n,a[MAXN],f[MAXN];
vector<pii> s[MAXN];
vector<pii>::iterator it; 
ll ans[MAXN];

int main()
{
    n = readint();
    for(int i = 1; i<=n/2; i++)
        a[i] = readint();
    for(int i = 1; i<=n/2; i++)
    {
        int tmp = a[i];
        for(int j = 1; j*j<tmp; j++)
        {
            if(tmp%j)
                continue;
            if((j^(tmp/j))&1)
                continue;
            s[i].push_back(mp((tmp/j-j)/2,(tmp/j+j)/2));
	    }
	    if(s[i].empty())
	    {
	        cout << "No" << endl;
			return 0; 
		} 
		sort(s[i].begin(),s[i].end());
	}
	ll now = 0;
	for(int i = 1; i<=n/2; i++)
	{
		it = upper_bound(s[i].begin(),s[i].end(),mp(f[i-1],1<<30));
		if(it==s[i].end())
		{
	        cout << "No" << endl;
	        return 0;
		}
		int x = it->fi, y = it->se;
		ans[i*2-1] = 1ll*x*x-now, ans[i*2] = a[i]; 
		f[i] = y;
		now = 1ll*y*y;
	}
	printf("Yes\n");
	for(int i = 1; i<=n; i++)
	    printf("%lld ",ans[i]);
	printf("\n");
	return 0;
}

```


---

## 作者：yuhooo (赞：1)

## Hint 1 : 
$a^2 - b^2 = (a - b)(a + b)$ 

$(a - b) $ 和 $ (a + b) $ 奇偶性必然相同

------------

##  Hint 2 :

给定 $x[2] = (a - b) (a + b)$
通过分解 $x[2]$ 可以解出 $a$ 和 $b$

##### 举个栗子 :

$x[2] = 21 = 3 * 7 = 1 * 21$ 

比较两种分解方式 ：


1. $(a - b) (a + b ) = 3 * 7$ 

解得 $a = (3 + 7) / 2 = 5$ 与 $b = (7 - 3) / 2 = 2$

2. $(a - b) (a + b ) = 1 * 21$ 

解得 $a = (1 + 21) / 2 = 11$ 与 $b = (21 - 1) / 2 = 10$

显然分解的两个数约接近，对应的两个平方数会越小


------------
## Hint 3 :

贪心前面越小，留给后面选择机会更多。选择的同时不要忘记检查合法性，自己可以考虑一下。

------------

## Code：

```c++
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

#define int long long

int a[N], b[N];
//a数组为题目中的x
//b数组为sqrt(Σx[i]) 
signed main() {
    int n;
    scanf("%lld", &n);
    for (int i = 2; i <= n; i += 2) {
        scanf("%lld", &a[i]);
        int flag = 0;
        for (int j = (int)(sqrt(a[i]) + 0.5); j >= 1; --j) { 
        //倒着循环为了保证b[i-1],b[i]尽量的接近，使得平方数尽量的小
            if (a[i] % j == 0) {
                if ((j & 1) ^ (a[i] / j & 1)) continue; 
                //拆分时奇偶不同直接pass，和与差都不能被2整除当然不行
                b[i] = (j + a[i] / j) >> 1;  //后面的平方和取大的
                b[i - 1] = (a[i] / j - j) >> 1; //前面的平方和取小的
                //倒着循环时也要保证合法性
                if (b[i - 1] <= b[i - 2] || b[i] * b[i] <= a[i]) continue; 
                else {
                    flag = 1; //合法时直接过，防止b[i]变得更大，留给后面的选择就不多了
                    break;
                }
            }
        } 
        if (!flag) {
            puts("No");
            return 0;
        }
    }
    // 处理数据并且输出
    for (int i = 1; i <= n; i += 2) {
        a[i] = b[i] * b[i] - b[i - 1] * b[i - 1]; 
    }
    puts("Yes");
    for (int i = 1; i <= n; ++i) {
        printf((i == 1) ? "%lld" : " %lld", a[i]);
    }puts("");
    return 0; //华丽的结束
}
```

---

## 作者：赵悦岑 (赞：0)

## 题意

给定长度为 $n$（n为偶数）的数列 $a$ 的偶数项，构造出数列 $a$ 的奇数项，使得 $\forall i \in [1,n],\sum\limits_{j=1}^i a_j$ 为平方数。

## 分析

首先，因为有 $a^2-b^2=(a-b)(a+b)$，我们设 $b_i = \sum\limits_{j=1}^i a_j$，那么就有 $b_i-b_{i-1}=a_i$，令 $c_i^2=b_i$，则 $(c_i-c_{i-1})(c_i+c_{i-1}) = a_i$，当 $i$ 为偶数时，$a_i$ 已知，所以我们可以通过 $\sqrt{n}$ 的时间分解质因数来求得可能的 $c_i,c_{i-1}$。

当 $c_i$ 有多种选择时，我们假设所有的 $c_i$ 尽可能小，设 $c_x' > c_x$，因为题目中要求是正整数，所以 $\forall i \in [1,n-1],c_i<c_{i+1}$，又所有的 $c_i$ 尽量小，所以 $\forall i \in [x,n],c_i' \geq c_i$，所以一定不比原来的情况优，所以我们每一个 $i$ （$i$ 为偶数）都尽量保证 $c_i$ 最小即可。

## code
```
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1000001;
typedef long long ll;
int n;
ll a[N],b[N];
int main()
{
    scanf("%d",&n);
    n/=2;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        bool u=false;
        for(ll j=sqrt(a[i]);j>=1;--j)
        {
            if(a[i]%j!=0) continue;
            if(((j%2)^((a[i]/j)%2))) continue;
            if((a[i]/j-j)/2>s)
            {
                b[i]=((a[i]/j-j)/2)*((a[i]/j-j)/2)-s*s;
                s=(a[i]/j+j)/2;
                u=true;
                break;
            }
        }
        if(u==false)
        {
            printf("No");
            return 0;
        }
    }
    printf("Yes\n");
    for(int i=1;i<=n;++i)
    {
        printf("%lld %lld ",b[i],a[i]);
    }
    return 0;
}
```

---

## 作者：钓鱼王子 (赞：0)

来源：[108 题进阶计划第五题](https://www.luogu.com.cn/blog/gyh20/post-60-ti-jin-jie-ji-hua)

贪心？乱搞？我也不知道该算什么。

首先，我们预处理出每一个 $j^2-i^2=x$ 的数对。并存入 vector，之后方便处理。

我们只用求出每一个前缀和是哪一个数的平方，然后求出答案即可，令 $a_i$ 为这个数列。

也就是说，我们要保证 $a_{2i}^2-a_{2i-1}^2=x_i$，且 $a_i$ 尽量小。假设我们已知 $a_{i-2(i\bmod 2=0)}$，那么我们只用找每一个平方差为 $x_i$ 且更小的数比 $a_{i-2}$ 大的一个数对且尽量小。

直接模拟即可，如果没有合法答案就退出，由于数对个数不是很多，所以复杂度不高。

```cpp
#include<cstdio>
#include<vector>
#define pi pair<int,int>
#define mp make_pair
#define re register
using namespace std;
vector<pi >v[200002];
int n,a[100002],sq[100002];
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int main(){
	n=read();
	for(re int i=1;i<=100000;++i)
		for(re int j=i+1;1ll*j*j-1ll*i*i<=200000;++j)
			v[1ll*j*j-1ll*i*i].push_back(mp(i,j));
	for(re int i=2,x;i<=n;i+=2){
		x=read();
		for(re int j=0;j<v[x].size();++j)
			if(v[x][j].first>sq[i-2]){
				sq[i-1]=v[x][j].first;
				sq[i]=v[x][j].second;
				break;
			}
		if(!sq[i])return puts("No"),0;
	}
	puts("Yes");
	for(re int i=1;i<=n;++i)printf("%lld ",1ll*sq[i]*sq[i]-1ll*sq[i-1]*sq[i-1]);
}
```


---

