# [JOI Open 2018] 木琴 / Xylophone

## 题目背景

**特别提醒，由于洛谷交互机制的特殊性，你不能在程序中引用 `xylophone.h`，而需要把 `xylophone.h` 中的内容加入文件的开头。即，在程序中 `solve` 函数的前面加入以下几行语句：**

```cpp
void solve(int N);
int query(int s, int t);
void answer(int i, int a);
```

## 题目描述

木琴是一种乐器，人可以通过敲击木条来演奏它。单个木条总是发出同样音高的音，因此一个木琴包含不同种音高的木条。

JOI 君买了一个有 $N$ 个木条的木琴。这 $N$ 个木条排成一排，从左到右编号为 $1$ 到 $N$。编号为 $i\ (1\le i\le N)$ 的木条能发出音高为 $A_i\ (1\le A_i\le N)$ 的音。不同的木条发出不同音高的音。他知道音高最低的木条要比音高最高的编号小。

因为 JOI 君不知道每个木条的音高是什么，他决定研究这些木条的音高。

JOI 有一种独特的音感，当他连续听到多个音时，他能分辨出最高音和最低音差多少。他可以一次敲击一些木条，然后听它们发出的声音。也就是说，对于两个整数 $s$ 和 $t\ (1\le s\le t\le N)$，他可以连续敲击编号从 $s$ 到 $t$​ 的木条，以知道 $A_s,A_{s+1},\ldots ,A_t$​ 中最大值与最小值的差。

他想在 $10\ 000$ 次敲击之内知道每个木条的音高。

---

**【实现细节】**

你需要实现函数 `solve` 以求出每个木条的音高。

- `solve(N)`

  - $N$：木条的数量。
  - 这个函数每个测试点调用恰好一次。

你的程序可以调用评分器实现的如下函数。

- `query(s, t)`

  这个函数返回在给定区间中木条音高最大值与最小值的差。

  - $s, t$：$s$ 是要敲击的木条区间中第一个数，$t$ 是最后一个数。也就是说，你需要敲击编号在 $[s,t]$ 区间内的所有木条。
  - 必须保证 $1\le s\le t\le N$。
  - 你不能调用 `query` 函数超过 $10\ 000$ 次。
  - 如果上述条件不满足，你的程序会被判为 **Wrong Answer**。

- `answer(i, a)`

  你的程序应当用这个函数回答每个木条的音高。

  - $i, a$：这意味着你回答了 $A_i$ 的值为 $a$，其中 $A_i$ 指木条 $i$ 的音高。
  - 必须保证 $1\le i\le N$。
  - 你不能对于相同的 $\texttt i$ 调用超过一次这个函数。
  - 你必须在函数 $\texttt{solve}$ 结束前调用恰好 $N$ 次此函数。
  - 如果上述条件不满足，你的程序会被判为 **Wrong Answer**。
  - 如果你的回答与实际音高有不同，你的程序会被判为 **Wrong Answer**。

暂不支持 Java 与 Pascal 提交的测评。

## 说明/提示

**【样例交互】**

一个对于 $N=5,(A_1,A_2,A_3,A_4,A_5)=(2,1,5,3,4)$ 的样例交互过程如下。

|          调用           |   返回值   |
| :---------------------: | :--------: |
| $\texttt{query(1, 5)}$  |            |
|                         |    $4$     |
| $\texttt{answer(1, 2)}$ |            |
| $\texttt{query(3, 5)}$  |  |
|                         |    $2$     |
| $\texttt{answer(2, 1)}$​ |            |
| $\texttt{answer(3, 5)}$​ |  |
| $\texttt{answer(5, 4)}$​ |            |
| $\texttt{answer(4, 3)}$​ |  |

**【数据范围】**

所有子任务满足以下限制：

- $1\le A_i\le N\ (1\le i\le N)$
- $A_i\neq A_j\ (1\le i<j\le N)$
- 对于满足 $A_i=1,A_j=N$ 的 $i$ 和 $j$，满足 $i<j$​。

本题有三个子任务。子任务分值及附加限制如下表所示：

| 子任务编号 | 分值 |        $N$         |
| :--------: | :--: | :----------------: |
|    $1$     | $11$ |  $2\le N\le 100$   |
|    $2$     | $36$ | $2\le N\le 1\ 000$ |
|    $3$     | $53$ | $2\le N\le 5\ 000$ |



# 题解

## 作者：Little09 (赞：10)

别写二分加神秘优化了。

定义 $b_i=a_i-a_{i-1}$。直接询问 $(i,i+1)$ 和 $(i-1,i+1)$。考虑第一种询问可以得知 $|a_i-a_{i+1}|$，也就是 $|b_{i+1}|$。

第二种询问能得到的是 $|b_i+b_{i+1}|$。考虑 $b_i,b_{i+1}$ 正负号相同，当且仅当 $|b_i+b_{i+1}|=|b_i|+|b_{i+1}|$。所以可以得知 $b_i,b_{i+1}$ 正负号是否相同。所有询问结束后，如果已知 $b_2$ 的正负号，就可以得知所有 $b$ 的正负号。

枚举 $b_2$ 的正负号，我们就可以得知 $a_i-a_1$ 的值，那么找到最小值就是 $1$，其他也就能算出来了。但是需要满足最小值的下标小于最大值的下标，如果不满足就改变 $b_2$ 的正负号即可。

询问次数 $2n-3$。

```cpp
const int N=5005;
int a[N],b[N],c[N];

void solve(int n)
{
	rep(i,1,n-1) a[i]=query(i,i+1);
	c[2]=1;
	rep(i,1,n-2)
	{
		int w=query(i,i+2);
		if (w==a[i]+a[i+1]) b[i]=0;
		else b[i]=1;
	}
	rep(i,2,n-1)
	{
		if (b[i-1]==1) c[i+1]=-c[i];
		else c[i+1]=c[i];
	}
	rep(i,2,n) c[i]*=a[i-1];
	rep(i,2,n) c[i]+=c[i-1];
	int mnpos=1,mxpos=1;
	rep(i,2,n) if (c[i]<c[mnpos]) mnpos=i;
	rep(i,2,n) if (c[i]>c[mxpos]) mxpos=i;
	if (mxpos<mnpos) 
	{
		rep(i,1,n) c[i]*=-1;
		swap(mxpos,mnpos);
	}
	rep(i,1,n) if (i!=mnpos) c[i]-=c[mnpos];
	c[mnpos]=0;
	rep(i,1,n) answer(i,c[i]+1);
}
```


---

## 作者：_•́へ•́╬_ (赞：3)

## 思路

题目保证了 $1$ 在 $n$ 之前，所以直接能二分找到 $n$。考虑从 $n$ 的位置向两边确定数字。

询问两个相邻的数字的差，一个已知一个未知，这样那个未知的就有两种可能。

再询问三个相邻的数字的差，两个已知一个未知，分讨一下那个未知的就能确定了。

但是加上二分用的次数就超了。

但是可以剪枝。如果仅询问一次就能确定，那就不用第二次了。具体地，两种可能中的某一种，不在 $[1,n]$ 范围或数字已经出现过了，就排除。

可以发现优化效果很好。最大点不超过 7000 次。

## code

```cpp
int query(int s,int t);
void answer(int i,int a);
int a[5009];bool v[5009];
void solve(int n)
{
	int l,r,mid;
	for(l=2,r=n;l<=r;)
	{
		mid=l+r>>1;
		if(query(1,mid)^n-1)l=mid+1;
		else r=mid-1;
	}
	a[l]=n;v[n]=1;
	if(l^n)
	{
		a[l+1]=n-query(l,l+1);v[a[l+1]]=1;
		for(int i=l+2;i<=n;v[a[i++]]=1)
		{
			int tmp=query(i-1,i);
			if(a[i-1]+tmp>n||v[a[i-1]+tmp]){a[i]=a[i-1]-tmp;continue;}
			if(a[i-1]-tmp<1||v[a[i-1]-tmp]){a[i]=a[i-1]+tmp;continue;}
			int tmp2=query(i-2,i);
			if(a[i-2]>a[i-1])
				if((tmp2^a[i-2]-a[i-1])&&a[i-2]-tmp2==a[i-1]-tmp)a[i]=a[i-1]-tmp;
				else a[i]=a[i-1]+tmp;
			else if((tmp2^a[i-1]-a[i-2])&&a[i-2]+tmp2==a[i-1]+tmp)a[i]=a[i-1]+tmp;
				else a[i]=a[i-1]-tmp;
		}
	}
	if(l^1)
	{
		a[l-1]=n-query(l-1,l);v[a[l-1]]=1;
		for(int i=l-2;i;v[a[i--]]=1)
		{
			int tmp=query(i,i+1);
			if(a[i+1]+tmp>n||v[a[i+1]+tmp]){a[i]=a[i+1]-tmp;continue;}
			if(a[i+1]-tmp<1||v[a[i+1]-tmp]){a[i]=a[i+1]+tmp;continue;}
			int tmp2=query(i,i+2);
			if(a[i+2]>a[i+1])
				if((tmp2^a[i+2]-a[i+1])&&a[i+2]-tmp2==a[i+1]-tmp)a[i]=a[i+1]-tmp;
				else a[i]=a[i+1]+tmp;
			else if((tmp2^a[i+1]-a[i+2])&&a[i+2]+tmp2==a[i+1]+tmp)a[i]=a[i+1]+tmp;
				else a[i]=a[i+1]-tmp;
		}
	}
	for(int i=1;i<=n;++i)answer(i,a[i]);
}
```

---

## 作者：_maze (赞：2)

如果我早一分钟开始手玩，就能早一分钟做出来。

如果我早五分钟开始手玩，就能早五分钟做出来。

提高做题速度，从手玩做起。

------------

从直觉上来讲，我们选择的区间越小，获取的信息量不变，但是信息的密度会变大。不妨从小区间开始考虑。

询问长度为 $1$ 的区间没有意义，考虑询问长度为 $2$ 的区间。这意味着我们可以求出 $i\in [1,n)$ 的 $|a_{i+1}-a_i|$。

发现这就是差分数组的绝对值形式。如果我们真的求出来了差分数组，这道题也就结束了。

考虑求解数之间两两大小。根据上文思路，我们尝试询问长度为 $3$ 的区间。分三种情况讨论：

1. 询问 $[i,i+2]$ 的值等于 $[i,i+1]$，那么可以得出 $a_{i+2}$ 的大小在 $a_{i}$ 和 $a_{i+1}$ 之间。即 $|a_{i+1}-a_i|$ 与 $|a_{i+2}-a_{i+1}|$ 在差分数组里有且仅有一个数会变成负数。
2. 询问 $[i,i+2]$ 的值等于 $[i+1,i+2]$，那么可以得出 $a_{i}$ 的大小在 $a_{i+1}$ 和 $a_{i+2}$ 之间。即 $|a_{i+1}-a_i|$ 与 $|a_{i+2}-a_{i+1}|$ 在差分数组里有且仅有一个数会变成负数。
3. 询问 $[i,i+2]$ 的值不等于前两者中任何一个数。那么对于 $a_i$ 来说，$a_{i+2}$ 会替代 $a_{i+1}$ 的位置。对于 $a_{i+2}$ 来说，$a_i$ 会替代 $a_{i+1}$ 的位置。那么可以得出 $a_{i+1}$ 的大小在 $a_{i}$ 和 $a_{i+2}$ 之间。即 $|a_{i+1}-a_i|$ 与 $|a_{i+2}-a_{i+1}|$ 在差分数组里正负相同。

我们求出了对于所有 $i\in[1,n-1)$，差分数组 $del_i$ 和 $del_{i+1}$ 的正负关系，不妨钦定 $del_1$ 的正负，根据题目里的要求“对于 $a_i=1,a_j=n$ 有 $i<j$”判断哪一个才是真正的解即可。

---

## 作者：Demeanor_Roy (赞：2)

- 简单交互题。

------------

首先发现题目中有一个特殊限制条件：

`他知道音高最低的木条要比音高最高的编号小。`

不难据此确定 $1$ 或 $n$ 的位置。以确定 $n$ 的位置为例：二分出做靠右的满足 `query(1,x)=n-1` 的 $x$，这个位置值就为 $n$。这部分调用次数 $\log n$。

然后从 $n$ 开始往两边扩展。同样，以往右扩展为例：假设当前正在确定第 $x$ 个位置，不妨先调用 `query(x-1,x)`，设返回值为 $d$，那么 $v_x$ 只可能为 $v_{x-1}-d$ 或 $v_{x-1}+d$。若这两个值其中之一不在 $[1,n]$ 内或已经被确定，那么 $v_x$ 就为另一个。否则注意到 $v_{x-2}$ 一定已经被确定，考虑调用 `query(x-2,x)`，不难发现根据返回值以及 $v_{x-1}$ 与 $v_{x-2}$ 的大小关系分类讨论可以唯一确定 $v_x$。这部分调用次数最大为 $2n$。

注意到第二部分次数不可能被卡满，实际上按此方法在当前数据下最多不会调用函数超过 $7000$ 次，足以通过本题。

代码：

```cpp
int query(int s,int t);
void answer(int i,int a);
const int N=5010;
int n,v[N];
bool vis[N];
void solve(int n)
{
	int l=2,r=n;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(query(1,mid)==n-1) r=mid;
		else l=mid+1;
	} 
	v[l]=n;vis[n]=true;
	for(int i=l-1;i>=1;i--)
	{
		int x=query(i,i+1);
		if(v[i+1]-x<=0||vis[v[i+1]-x]) v[i]=v[i+1]+x,vis[v[i+1]+x]=true;
		else if(v[i+1]+x>n||vis[v[i+1]+x]) v[i]=v[i+1]-x,vis[v[i+1]-x]=true;
		else
		{
			int y=query(i,i+2);
			if(v[i+2]>v[i+1])
			{
				if(y==x+v[i+2]-v[i+1]) v[i]=v[i+1]-x,vis[v[i+1]-x]=true;
				else v[i]=v[i+1]+x,vis[v[i+1]+x]=true;	
			}	
			else 
			{
				if(y==x+v[i+1]-v[i+2]) v[i]=v[i+1]+x,vis[v[i+1]+x]=true;
				else v[i]=v[i+1]-x,vis[v[i+1]-x]=true; 
			}
		}	
	} 
	for(int i=l+1;i<=n;i++)
	{
		int x=query(i-1,i);
		if(v[i-1]-x<=0||vis[v[i-1]-x]) v[i]=v[i-1]+x,vis[v[i-1]+x]=true;
		else if(v[i-1]+x>n||vis[v[i-1]+x]) v[i]=v[i-1]-x,vis[v[i-1]-x]=true;
		else
		{
			int y=query(i-2,i);
			if(v[i-2]>v[i-1])
			{
				if(y==x+v[i-2]-v[i-1]) v[i]=v[i-1]-x,vis[v[i-1]-x]=true;
				else v[i]=v[i-1]+x,vis[v[i-1]+x]=true;	
			}	
			else 
			{
				if(y==x+v[i-1]-v[i-2]) v[i]=v[i-1]+x,vis[v[i-1]+x]=true;
				else v[i]=v[i-1]-x,vis[v[i-1]-x]=true; 
			}
		}
	}
	for(int i=1;i<=n;i++) answer(i,v[i]);
}
```


---

## 作者：_mayiwei (赞：1)

简要题意：有一个长度为 $n$ 的序列，每次询问可以得到区间最大值与最小值之差，在 $2n$ 次询问之内得到这个序列。

---

以下设 $q(l,r)$ 表示对区间 $\left[ l,r\right]$ 进行一次询问。

区间太长，就无法知道区间最大值和最小值的位置。所以对于每次询问，区间长度越短能得到的信息越多。

因此询问长度为 $2$ 的区间更优，此时 $q(i,i+1)=|a_i-a_{i+1}|$，只需要判断 $a_i$ 和 $a_{i+1}$ 的大小关系即可。

不妨试一下询问长度为 $3$ 的情况，有以下几种情况。

- $a_i<a_{i+1}<a_{i+2}$：$q(i,i+2)=a_{i+2}-a_{i}=a_{i+2}-a_{i+1}+a_{i+1}-a_{i}=q(i,i+1)+q(i+1,i+2)$

- $a_i>a_{i+1}>a_{i+2}$：$q(i,i+2)=a_{i}-a_{i+2}=a_{i}-a_{i+1}+a_{i+1}-a_{i+2}=q(i,i+1)+q(i+1,i+2)$

- $a_i>a_{i+1}<a_{i+2}$：$q(i,i+2)=\max(a_{i}-a_{i+1},a_{i+2}-a_{i+1})=\max(q(i,i+1),a(i+1,i+2))$

- $a_i<a_{i+1}>a_{i+2}$：$q(i,i+2)=\max(a_{i+1}-a_{i},a_{i+2}-a_{i})=\max(q(i,i+1),q(i+1,i+2))$

观察到，当且仅当 $q(i,i+2)=q(i,i+1)+q(i+1,i+2)$ 时，$a_{i}-a_{i+1}$ 和 $a_{i+1}-a_{i+2}$ 同号。

只有以上的条件是不充分的，但题面里说明最小值在最大值前，所以可以先假设 $a_1=0$，$a_1<a_2$，如果最小值在最大值后则说明大小关系恰好相反，整体取负号即可。

因为要求 $a_i$ 的值域在 $[1,n]$ 之间，所以整体加 $1-\min\{a\}$ 即可。

询问所有长度为 $2$ 的区间需要询问 $n-1$ 次，询问所有长度为 $3$ 的区间需要 $n-2$ 次，共计 $2n-3$ 次。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],b[100005],c[100005];
int ans[100005];
int query(int s, int t);
void answer(int i, int a);
void solve(int n){
	for(int i=1;i<=n-1;i++){
		a[i]=query(i,i+1);
	}
	for(int i=1;i<=n-2;i++){
		b[i]=query(i,i+2);
	}
	c[1]=1;
	for(int i=1;i<=n-2;i++){
		if(b[i]==a[i]+a[i+1])c[i+1]=c[i];
		else c[i+1]=-c[i];
	}
	int minx=0,mink=1,maxx=0,maxk=1;
	for(int i=2;i<=n;i++){
		ans[i]=ans[i-1]+c[i-1]*a[i-1];
		if(minx>ans[i]){
			minx=ans[i];
			mink=i;
		}
		if(maxx<ans[i]){
			maxx=ans[i];
			maxk=i;
		}
	}
	if(mink>maxk){
		for(int i=1;i<=n;i++){
			ans[i]=-ans[i];
		}
		minx=-minx;
		maxx=-maxx;
		swap(minx,maxx);
	}
	for(int i=1;i<=n;i++){
		ans[i]+=1-minx;
		answer(i,ans[i]);
	}
}
```

---

## 作者：Sampson_YW (赞：1)

不知道正确性的做法，但是很搞笑。

因为 $1$ 在 $n$ 前面，那么考虑找到 $1$ 的位置。

二分一段后缀，找到最长的最大减最小不等于 $n-1$ 的后缀，那么这个后缀前一个数就是 $1$。

那么 $1$ 的相邻两个数一定比 $1$ 大，可以用一次询问确定。并且容易发现，如果知道相邻两个数的值，可以用两次询问确定这两个数左边或右边的数。

现在还剩 $2n - \log n - 2$ 次询问，知道了三个数的值，还剩下 $n - 3$ 个数的值未知。那么考虑确定这三个数往后 $\log n$ 个数相邻两个的差的绝对值，剩下 $2n- 2\log n - 2$ 次询问和 $n - 3 - \log n$ 个数，就可以用两次询问得到确定的答案了。

然后 $O\left(2^{\log n}\right)$ 枚举后 $\log n$ 个数的值，再 $O(n)$ 判断最终得到的序列是否合法即可。时间复杂度 $O(2^{\log n}n)=O(n^2)$。

但是不知道会不会出现多个序列合法的情况。[code](https://www.luogu.com.cn/paste/un6xt403)

---

## 作者：I_will_AKIOI (赞：0)

题目就是告诉我们每次可以询问区间极差，让你求出每个数。

由于题目说了，最低音在最高音左边，所以我们考虑二分找到一个最小的 $x$，使得 $\operatorname{query}(1,x)=n-1$。我们令 $a_i$ 表示编号为 $i$ 的木条的音高，那么可以得出 $a_x=n$。

接着很容易想到查询 $[x,x-1]$ 和 $[x,x+1]$ 来得出 $a_{x-1}$ 和 $a_{x+1}$。因为 $a_x=n$，$a$ 又是一个 $1\sim n$ 的排列，所以他两边的数只能是 $a_x$ 减去查询结果。

那么接下来自然要继续枚举两边的数来查询了。但是这里会有一个问题。每次我们查询一个长度为 $2$ 的区间 $[i,i+1]$，查询结果为 $q$，那么 $a_{i+1}=a_i\pm q$。如果 $a_i\pm q$ 中的一个不属于 $[1,n]$，或者被使用过了，可以直接确定。但是不能确定的就不好办了。例如 $a_i=3,q=4$，那么 $a_{i+1}=4$ 或 $2$。这个时候我们可以查询一下 $[i-1,i+1]$，然后枚举是加还是减，看看哪个 $a_{i+1}$ 满足 $\max(a_{i-1},a_i,a_{i+1})-\min(a_{i-1},a_i,a_{i+1})=\operatorname{query}(i-1,i+1)$ 即可。注意对需要对 $x$ 的两边枚举。

但是容易发现查询次数为 $2n+\log_2 n$，刚刚好多了个 $\log$，怎么办？很简单，对于可以直接确定的 $a_{i+1}$，不需要查询 $[i-1,i+1]$，所以可以剪枝，最后的查询次数不会超过 $7000$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int query(int s,int t);
void answer(int i,int a);
int l,r,mid,a[5005],vis[5005];
void solve(int n)
{
  l=2,r=n;
  while(l<r)
  {
    mid=l+r>>1;
    int x=query(1,mid);
    if(x==n-1) r=mid;
    else l=mid+1;
  }
  a[r]=n;//二分出a[r]
  a[r-1]=n-query(r-1,r);
  if(r<n) a[r+1]=n-query(r,r+1);
  vis[a[r]]=vis[a[r-1]]=vis[a[r+1]]=1;//将这三个数设为已使用
  for(int i=r-2;i>=1;i--)
  {
    int x=query(i,i+1);
    if(a[i+1]+x>n||vis[a[i+1]+x]) a[i]=a[i+1]-x;
    else if(a[i+1]-x<1||vis[a[i+1]-x]) a[i]=a[i+1]+x;
    else//不能直接确定
    {
      int y=query(i,i+2);
      if(y==max(a[i+1]-x,max(a[i+1],a[i+2]))-min(a[i+1]-x,min(a[i+1],a[i+2]))) a[i]=a[i+1]-x;
      else a[i]=a[i+1]+x;
    }
    vis[a[i]]=1;
  }
  for(int i=r+2;i<=n;i++)
  {
    int x=query(i-1,i);
    if(a[i-1]+x>n||vis[a[i-1]+x]) a[i]=a[i-1]-x;
    else if(a[i-1]-x<1||vis[a[i-1]-x]) a[i]=a[i-1]+x;
    else
    {
      int y=query(i-2,i);
      if(y==max(a[i-1]-x,max(a[i-1],a[i-2]))-min(a[i-1]-x,min(a[i-1],a[i-2]))) a[i]=a[i-1]-x;
      else a[i]=a[i-1]+x;
    }
    vis[a[i]]=1;
  }
  for(int i=1;i<=n;i++) answer(i,a[i]);
  return;
}
```

---

## 作者：DerrickLo (赞：0)

我们先通过二分找到最小的 $x$ 使得 `query(1,x)` 的值是 $n-1$，那么 $a_x$ 就是 $n$，同理我们再次二分找到最大的 $y$ 使得 `query(y,n)` 的值是 $n-1$，则 $a_x$ 就是 $1$。

然后我们对于每个数 $a_i$，假设我们知道了 $a_{i+1}$ 与 $a_{i+2}$，那么我们就可以通过两次询问 `query(i,i+2)` 与 `query(i,i+1)` 求出 $a_i$。首先通过 `query(i,i+1)` 我们可以确定 $a_i$ 只有两种取值，而 `query(i,i+2)` 的取值对于 $a_i$ 的两种取值是不同的，所以我们就能求出 $a_i$。

这样的询问次数大概是 $2n+2\log n$ 次，不足以通过，我们可以加一个优化：注意到如果在第一次询问后可以确定 $a_i$ 就不需要询问第二次了。

优化后的询问次数就变少了很多，最多只有 $6000$ 多次。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[5005],b[5005],vis[5005];
void solve(int n);
int query(int s, int t);
void answer(int i, int a);
void solve(int n){
	int l=1,r=n,ans1=0,ans2=0;
	while(l<=r){
		int mid=l+r>>1;
		if(query(1,mid)==n-1)ans1=mid,r=mid-1;
		else l=mid+1;
	}
	l=1,r=ans1-1;
	while(l<=r){
		int mid=l+r>>1;
		if(query(mid,n)==n-1)ans2=mid,l=mid+1;
		else r=mid-1;
	}
	a[ans1]=n,a[ans2]=1,vis[n]=vis[1]=1;
	if(ans2!=1)a[ans2-1]=query(ans2-1,ans2)+1;
	if(ans2!=n)a[ans2+1]=query(ans2,ans2+1)+1,vis[a[ans2+1]]=1;
	if(ans1!=n)a[ans1+1]=n-query(ans1,ans1+1),vis[a[ans1+1]]=1;
	for(int i=ans2-1;i;i--){
		int y=query(i,i+1);
		if(a[i+1]+y>n||vis[a[i+1]+y]){
			a[i]=a[i+1]-y,vis[a[i]]=1;
			continue;
		}
		if(a[i+1]-y<1||vis[a[i+1]-y]){
			a[i]=a[i+1]+y,vis[a[i]]=1;
			continue;
		}
		int x=query(i,i+2);
		int p=a[i+1]-y;
		if(max({p,a[i+1],a[i+2]})-min({p,a[i+1],a[i+2]})==x)a[i]=p;
		else a[i]=a[i+1]+y;
		vis[a[i]]=1;
	}
	for(int i=ans2+2;i<ans1;i++){
		int y=query(i-1,i);
		if(a[i-1]+y>n||vis[a[i-1]+y]){
			a[i]=a[i-1]-y,vis[a[i]]=1;
			continue;
		}
		if(a[i-1]-y<1||vis[a[i-1]-y]){
			a[i]=a[i-1]+y,vis[a[i]]=1;
			continue;
		}
		int x=query(i-2,i);
		int p=a[i-1]-y;
		if(max({a[i-2],a[i-1],p})-min({a[i-2],a[i-1],p})==x)a[i]=p;
		else a[i]=a[i-1]+y;
		vis[a[i]]=1;
	}
	for(int i=ans1+2;i<=n;i++){
		int y=query(i-1,i);
		if(a[i-1]+y>n||vis[a[i-1]+y]){
			a[i]=a[i-1]-y,vis[a[i]]=1;
			continue;
		}
		if(a[i-1]-y<1||vis[a[i-1]-y]){
			a[i]=a[i-1]+y,vis[a[i]]=1;
			continue;
		}
		int x=query(i-2,i);
		int p=a[i-1]-y;
		if(max({a[i-2],a[i-1],p})-min({a[i-2],a[i-1],p})==x)a[i]=p;
		else a[i]=a[i-1]+y;
		vis[a[i]]=1;
	}
	for(int i=1;i<=n;i++)answer(i,a[i]);
}
/*
int query(int s,int t){
	int maxx=-1e9,minx=1e9;
	for(int i=s;i<=t;i++)maxx=max(maxx,b[i]),minx=min(minx,b[i]);
	return maxx-minx;
}
void answer(int i,int a){
	cout<<a<<"\n";
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>b[i];
	solve(n);
}
*/
```

---

