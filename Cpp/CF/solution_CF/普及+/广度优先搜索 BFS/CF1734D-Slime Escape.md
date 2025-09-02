# Slime Escape

## 题目描述

You are playing a game called Slime Escape. The game takes place on a number line. Initially, there are $ n $ slimes. For all positive integers $ i $ where $ 1 \le i \le n $ , the $ i $ -th slime is located at position $ i $ and has health $ a_i $ . You are controlling the slime at position $ k $ .

There are two escapes located at positions $ 0 $ and $ n+1 $ . Your goal is to reach any one of the two escapes by performing any number of game moves.

In one game move, you move your slime to the left or right by one position. However, if there is another slime in the new position, you must absorb it. When absorbing a slime, the health of your slime would be increased by the health of the absorbed slime, then the absorbed slime would be removed from the game.

Note that some slimes might have negative health, so your health would decrease when absorbing such slimes.

You lose the game immediately if your slime has negative health at any moment during the game.

Can you reach one of two escapes by performing any number of game moves, without ever losing the game?

## 说明/提示

In the first test case, you control the slime at position $ 4 $ with health $ 6 $ . One way to escape is to absorb the slimes at positions $ 5 $ , $ 6 $ , and $ 7 $ . Your slime escapes with $ 0 $ health at position $ 8 $ .

In the second test case, you control the slime with $ 232 $ health at position $ 1 $ . Since your slime is already located next to the escape at position $ 0 $ , you can move to it without absorbing any slime.

In the third test case, it can be shown that your slime would always have a negative health before reaching any one of two escapes.

In the fourth test case, you control the slime at position $ 4 $ with health $ 6 $ . The following describes a possible sequence of moves to win:

1. Absorb the slimes at positions $ 5 $ , $ 6 $ , and $ 7 $ : your health becomes $ 4 $ after absorbing the slime with health $ -2 $ ; becomes $ 1 $ after absorbing the slime with health $ -3 $ ; and becomes $ 7 $ after absorbing the slime with health $ 6 $ .
2. Absorb the slimes at positions $ 3 $ , and $ 2 $ : your health becomes $ 7-7+10=10 $ .
3. Absorb the slime at position $ 8 $ : your health becomes $ 10-10=0 $ .
4. Use the escape at position $ 9 $ .

Since your slime has maintained non-negative health at all times, you have won.

## 样例 #1

### 输入

```
6
7 4
-1 -2 -3 6 -2 -3 -1
3 1
232 -500 -700
7 4
-1 -2 -4 6 -2 -4 -1
8 4
-100 10 -7 6 -2 -3 6 -10
8 2
-999 0 -2 3 4 5 6 7
7 3
7 3 3 4 2 1 1```

### 输出

```
YES
YES
NO
YES
NO
YES```

# 题解

## 作者：VinstaG173 (赞：8)

贪心。为了方便，我们认为 slime 每移动一格会将所在格完全吞并，格子的总数减少 $1$，这样数轴上所有格子都不空（我们认为初始时 $a_i=0$ 的格子不是空的）。

在这样的情况下，每次操作就是将 slime 向左或向右移动一格，可记为一个由左右组成的操作序列。在不让 slime 死掉的情况下任意调换操作序列的顺序是没有影响的。此时我们想让 slime 尽可能地规律行动，则操作序列由若干有规律可循的连续向左或向右序列组成。

考虑一段连续向左的序列（向右同理）为何终止。第一种情况即到达 $0$，此时已经逃出。第二种情况即再走一步会死亡，此时接下来必须向右。但是假设我们在面临死亡之前走到的若干格子贡献为负（即 $\sum a_i<0$），此时显然不走这几个格子直接转向右边能走的距离更远（或者不近）。因此我们的贪心策略希望我们每次往一个方向连续走时会在不死亡的情况下尽可能地增加自己的体重。

接下来我们实现这个贪心策略，容易想到用两个指针维护向左和向右走到的位置，每次向左（或向右同理）一直走到逃离或者会死亡为止，如果会死亡则记录下路上到哪个格子时体重变为最大，在此基础上哪个格子走得最远，然后将向左的指针移到这个最大的格子，然后转向。当向两个方向都无法增加体重也无法逃离时，就一定被困住了。

这个实现过程中每个指针更新位置时走到的最远的位置（即“会死亡”的位置）相对实际更新到的位置（即“取到最大值”的位置）的贡献一定为负，但此方向下次若能更新则一定贡献不小于 $0$，故一定能跳过这次走不通的位置。而若一个方向上已经不能为 slime 增加体重，那在另一个方向上 slime 也无法走得更远，slime 将会被困住。因此每个位置至多有一次走不通并返回，第二次便一定会路过或被困住而结束。从而总操作次数不超过 $2n$。每次操作复杂度为 $O(1)$，故时间复杂度为 $O(n)$。

Code:
```cpp
#include<cstdio>
#define rg register
#define ll long long
int n,k,p;ll v,s,m;
ll a[2000003];
int t;int main(){
	scanf(" %d",&t);while(t--){
		scanf(" %d %d",&n,&k);
		for(rg int i=1;i<=n;++i)scanf(" %lld",&a[i]);
		v=a[k];if(a[k]<0){puts("NO");continue;}
		int l=k-1,r=k+1;while(l&&r<=n){
			ll pv=v;
			s=m=0;p=r-1;for(;r<=n;++r){
				s+=a[r];if(s>m)m=s,p=r;
				if(s<-v)break;
			}if(r<=n)v+=m,r=p+1;
			else break;
			s=m=0;p=l+1;for(;l;--l){
				s+=a[l];if(s>m)m=s,p=l;
				if(s<-v)break;
			}if(l)v+=m,l=p-1;
			else break;
			if(v==pv)break;
		}if(l&&r<=n)puts("NO");
		else puts("YES");
	}return 0;
}
```

---

## 作者：jockbutt (赞：8)

## 题意

在 $ n $ 个点的数轴上有一只 ${\color{black}{\text{S}}}{\color{red}{\text{lime}}}$，它在第 $ k $ 个点的位置，初始大小为 $ a_k $。

当史莱姆到达第 $ i $ 个点时，它的大小会加上 $ a_i $，如果它的大小为负数，它就死了。

请问史莱姆能否逃出数轴（即活着到达 $ 0 $ 活着 $ n + 1 $ 号点）。

## Solution

首先，向左向右出去做法一样，我们仅讨论是否能向左逃脱。

史莱姆肯定是希望自己变得更大，策略一定是如果往某一边能够让自己增大，那么就往那边吃，一直到能让自己体积最大的而且能到的点。

我们可以做一个向左的前缀和，往左边走，记录往左走时体积最大的时候，然后拿右边体积最大的时候来判断自己是否能再继续往左边走。

在代码书写的时候，我们可以往左往右同时计算，同时更新最大体积，这样会好写一些。

具体细节看代码。

## Code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int BUFFER=1<<20;
char RB[BUFFER],*RP=RB,*RT=RB;
#define getchar() RP==RT?(RT=RB+fread(RB,1,BUFFER,stdin),RP=RB,*RP++):*RP++
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9')	{if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9')	{x=x*10+ch-48;ch=getchar();}
	return x*f;
}
#define YES {printf("YES\n");return ;}
#define NO {printf("NO\n");return ;}
#define GG {printf("-1\n");return ;}
int n,m,k;
const int maxn=1e6+10;
int a[maxn],tot,ans;
int s[maxn];
inline void solve()
{
	n=read(),k=read(),ans=tot=0;
	for(int i=1;i<=n;++i)	a[i]=read();
	if(a[k]<0)	NO
	s[k-1]=a[k-1],s[k+1]=a[k+1],s[k]=0;
	for(int i=k-2;i>0;--i)	s[i]=s[i+1]+a[i];
	for(int i=k+2;i<=n;++i)	s[i]=s[i-1]+a[i];
	int l=k-1,r=k+1,s1=a[k],s2=a[k],ll,rr;
	for(;l>0&&r<=n;)
	{
		ll=l,rr=r;
		while(s[l]+s2>=0&&l>0)	s1=max(s1,a[k]+s[l]),l--;
		while(s[r]+s1>=0&&r<=n)	s2=max(s2,a[k]+s[r]),r++;
		if(ll==l&&rr==r)	NO
	}
	YES
}
signed main(){
	int T=read();
	while(T--)	solve();
	return 0;
}
```


---

## 作者：xujingyu (赞：2)

什么什么？ @2022tysc0080 写了本题 tj？~~我也要写~~

## 题意:

数轴上有一只史莱姆，它可以向左走或向右走。每走一格，史莱姆就会将该格的怪物吞噬。吞噬后史莱姆的血量就会加上怪物的血量（可能是负数）。若史莱姆血量 $<0$ 就会挂。求史莱姆能否活着去到 $0$ 或 $n+1$ 的位置。

## 解答:

假设该史莱姆不停向左走。如果它停止了，只有两种情况：

* 史莱姆挂了。
* 史莱姆到了 $0$ 格。

如果是第二种情况，就可以输出 `Yes` 了。

考虑第一种情况，在史莱姆不停向左走时记录它的血量最大值，若史莱姆挂了，就让它只走到血量最大值的位置，再不停向右走（因为它若想出去只能这么走了）。

但是若向右走还是会挂，就输出 `No` 了。否则是可以的。

**代码中是一开始枚举不断向右走的情况。**

## code:

```cpp
#include <stdio.h>
#include <queue>
#include <iostream>
#define int long long
using namespace std;

int t,n,k,p,ak,a[2000002],l,r;

signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&k);
		for(int i = 1;i <= n;i++) scanf("%lld",&a[i]);
		
		ak = a[k];//记录血量
		
		l = k - 1;
		r = k + 1;
		
		int sum,most;//当前血量与最大血量
		while(l && r <= n)
		{
			int ak1 = ak;
			sum = 0;
			most = 0;
			p = r - 1;
			for(;r <= n;r++)//一直向右走
			{
				sum += a[r];
				if(sum > most)
				{
					most = sum;//保存最大血量
					p = r;
				}
				if(sum < -ak) break;
			}
			if(r <= n)//没能过去
			{
				ak += most;
				r = p + 1;
			}
			else break;
			sum = most = 0;
			p = l + 1;
			for(;l;l--)//再不停向左走
			{
				sum += a[l];
				if(sum > most)
				{
					most = sum;
					p = l;
				}
				if(sum < -ak) break;
			}
			if(l)
			{
				ak += most;
				l = p - 1;
			}
			else break;
			if(ak == ak1) break;
		}
		
		if(l && r <= n)//还是没出去
		{
			printf("NO\n");
			continue;
		}
		else printf("YES\n");
	}
	return 0;
}
```


---

## 作者：vegetable_chili (赞：1)

## 分类

这题可以用**双指针**，是一道不错（~~比较水~~）的双指针保存左右最优解的题。

## 思路

当史莱姆要往左走时，我们可以先找出上一次找到的右边的最优解，就是血量收益的点，从该点往左扩展，看最远能走到哪，过程中记录收益最大的点。

当史莱姆要往右走时，我们可以学习左边的方法，取最优值开始扩展。

那么我们怎么判断无法再走了呢？我们可以发现，如果一边走时取了另一边最优解还无法进行任何扩展，那这边就暂时走不了了。如果同时出现**两边都无法扩展**，那两边的最优值必然也不会有更新，那史莱姆就被困住了，此时就无法再走了，直接判断无解即可。

最后，如果**任意一边扩展到了终点**就直接判断有解即可。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int T,n,k,blood[N];
bool work(int n,int k){
	if(blood[k]<0)return false;
	int l=k,r=k,maxl=blood[k],maxr=blood[k],ll=0,rr=0;
	bool flag;blood[n+1]=0;
	while(l>0&&r<=n){
		flag=false;
		while(l>0&&ll+blood[l-1]+maxr>=0){
			l--;flag=true;
			maxl=max(maxl,ll+blood[l]+blood[k]);
			ll+=blood[l];
		}
		while(r<=n&&rr+blood[r+1]+maxl>=0){
			r++;flag=true;
			maxr=max(maxr,rr+blood[r]+blood[k]);
			rr+=blood[r];
		}
		if(flag==false)return false;
	}
	return true;
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++)scanf("%lld",&blood[i]);
		if(work(n,k))printf("YES\n");
		else printf("NO\n");
	}
}
```


---

## 作者：az__eg (赞：1)

题意：

给你一个数轴，从 $1$ 到 $n$ 有 $n$ 个数字，一只史莱姆从位置 $1\leq k\leq n$ 出发，每次能向左或向右走，问能否能走到边缘，且史莱姆每次走都会取出当前位置的数字（每个数字只能取一次！但是能多次经过），取出来的数字何时何地都不能小于 $0$。

解法：

一开始想的是每次左右找到最大的数走，想了一会发现假了，如果左右两边都是负的话，就会导致可能多取不必要的负数。

发现可以直接枚举从左走还是从右走。然后如果从左走则把右边的加起来大于 $0$ 的段数给统计一下，并且记录一下要走到那需要起码当前的值为多少。右边同理。

完整代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#define int long long
using namespace std;
int n,k;
int t;
int l,r;
int a[200001];
int sum1[200001];
int mn1[200001];
int sum2[200001];
int mn2[200001];
int cnt1,cnt2;
int num;
signed main()
{
	int i,j;
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--)
	{
		cnt1=cnt2=0;
		cin>>n>>k;
		for(i=1;i<=n;i++)
		{
			cin>>a[i];
			sum1[i]=sum2[i]=mn1[i]=mn2[i]=0;
		}
		int sum=0;
		for(i=k+1;i<=n;i++)
		{
			sum+=a[i];
			mn1[cnt1+1]=min(sum,mn1[cnt1+1]);
			if(sum>=0)//当前段对答案有正贡献了
			{
				sum1[++cnt1]=sum;
				sum=0;
			}
		}
		sum=0;
		for(i=k-1;i>=1;i--)
		{
			
			sum+=a[i];
			mn2[cnt2+1]=min(sum,mn2[cnt2+1]);
			if(sum>=0)
			{
				sum2[++cnt2]=sum;
				sum=0;
			}
		}
		bool flag=true;
		sum=a[k];
		int cnt=0;
		for(i=k+1;i<=n;i++)
		{
			while(cnt+1<=cnt2&&sum+mn2[cnt+1]>=0)//贪心
			{
				sum+=sum2[cnt+1];
				cnt+=1;
			}
			sum+=a[i];
			if(sum<0)
			{
				flag=false;
				break;
			}
		}
		sum=a[k];
		cnt=0;
		if(flag)
		{
			printf("YES\n");
			continue;
		}
		flag=true;
		for(i=k-1;i>=1;i--)
		{
			while(cnt+1<=cnt1&&sum+mn1[cnt+1]>=0)
			{
				sum+=sum1[cnt+1];
				cnt+=1;
			}
			sum+=a[i];
			if(sum<0)
			{
				flag=false;
				break;
			}
		}
		if(flag)
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
}
```


---

## 作者：Allanljx (赞：1)

## 思路
以点 $k$ 为中心向左、右分别记录前缀和，前缀和为正的位置和前缀和的前缀最小值。

每次同时向左右扩展，能扩展当且仅当前缀和为正以及前缀和的前缀最小值加上当前的值大于 $0$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,k,l1[200005],r1[200005];
int a[200005],minn[200005],qz[200005];
signed main()
{
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i];
		a[0]=a[n+1]=1e18;
		int sum1=0,sum2=0,fl=0;
		for(int i=k-1;i>=0;i--)
		{
			if(fl) qz[i]=qz[i+1]+a[i],minn[i]=min(minn[i+1],qz[i]);
			else minn[i]=qz[i]=a[i],fl=1;
			if(qz[i]>0) l1[++sum1]=i,fl=0;
		}
		fl=0;
		for(int i=k+1;i<=n+1;i++)
		{
			if(fl) qz[i]=qz[i-1]+a[i],minn[i]=min(minn[i-1],qz[i]);
			else minn[i]=qz[i]=a[i],fl=1;
			if(qz[i]>0) r1[++sum2]=i,fl=0;
		}
		int l=k,r=k,tmp1=1,tmp2=1;
		int sum=a[k];
		while(tmp1<=sum1&&tmp2<=sum2&&(sum>=-minn[l1[tmp1]]||sum>=-minn[r1[tmp2]]))
		{
			if(sum>=-minn[l1[tmp1]]) sum+=qz[l1[tmp1++]];
			if(sum>=-minn[r1[tmp2]]) sum+=qz[r1[tmp2++]];
		}
		if(tmp1>sum1||tmp2>sum2) cout<<"YES\n";
		else cout<<"NO\n";
	}
    return 0;
}
```

---

## 作者：cryozwq (赞：0)

首先可以枚举最后从哪个方向出来，那么我们这个方向是一定每一步都要走的。

容易想到一个贪心策略，我们每往目标方向走一步，就走到另一个方向能到达的位置中，能使得自己增量最大位置。

注意我们一定要让增量为正，所以把另一个方向上和大于 $0$ 的缩成一段，记录要走完这一段至少需要多少健康值，然后类似双指针，做两遍即可。

代码见 CF 提交。

---

