# Numbers Exchange

## 题目描述

Eugeny has $ n $ cards, each of them has exactly one integer written on it. Eugeny wants to exchange some cards with Nikolay so that the number of even integers on his cards would equal the number of odd integers, and that all these numbers would be distinct.

Nikolay has $ m $ cards, distinct numbers from $ 1 $ to $ m $ are written on them, one per card. It means that Nikolay has exactly one card with number $ 1 $ , exactly one card with number $ 2 $ and so on.

A single exchange is a process in which Eugeny gives one card to Nikolay and takes another one from those Nikolay has. Your task is to find the minimum number of card exchanges and determine which cards Eugeny should exchange.

## 样例 #1

### 输入

```
6 2
5 6 7 9 4 5
```

### 输出

```
1
5 6 7 9 4 2 
```

## 样例 #2

### 输入

```
8 6
7 7 7 7 8 8 8 8
```

### 输出

```
6
7 2 4 6 8 1 3 5 
```

## 样例 #3

### 输入

```
4 1
4 2 1 10
```

### 输出

```
-1
```

# 题解

## 作者：_Clown_ (赞：1)

$$\huge\mathcal{Solution}$$
这道题目我们可以按照题目大意**模拟**。

但是，我们还要小小滴卡一下常。。。

首先，我们找出所有不合法的数，拎一个
$\texttt{Vector}$。

然后，我们逐个枚举可以用来替换的数，看看能否换掉一个不合法的数，换成合法的。


如果能换的话，就换。

那么最后再卡卡常，合并几个循环，跑个火车头就过了。

另附火车头代码：
```cpp
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
```
$$\huge\mathcal{Code}$$
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
using namespace std;
int N,M;
int Sum[2];
int Array[200001];
map< int,bool >Have;
vector< int >V;
int main(void)
{
	register int i;
	cin>>N>>M;
	for(i=1;i<=N;i++)
	{
		cin>>Array[i];
		if(Have[Array[i]]||Sum[Array[i]%2]==N/2)
		{
			V.push_back(i);
		}
		else
		{
			Have[Array[i]]=true;
			Sum[Array[i]%2]++;
		}
	}
	register int Count;
	Count=0;
	for(i=1;i<=M;i++)
	{
		if(Have[i]||Sum[i%2]==N/2)
		{
			continue;
		}
		Array[V[Count++]]=i;
		Sum[i%2]++;
		if(Count==V.size())
		{
			break;
		}
	}
	if(Count<V.size())
	{
		cout<<-1<<endl;
		return 0;
	}
	cout<<Count<<endl;
	for(i=1;i<=N;i++)
	{
		cout<<Array[i]<<' ';
	}
	cout<<endl;
	return 0;
}
```


---

## 作者：Ninelife_Cat (赞：0)

贪心好题。

我们可以把换卡的操作看成将某个位置填上一个 $1$ 到 $m$ 之间的数。

题目要求换卡次数最少，即保持不变的数最多。那么我们按照数字的值从大到小检查，对于符合条件的值就直接跳过。

为什么要从大到小呢？因为 $m$ 可能小于 $n$，如果把大于 $m$ 的数也给填掉了，剩下的位置就不够填了。（~~感性理解一下啦~~）

接下来我们将需要填数的地方按照数值从小到大填上就行了，如果当前需要填的数值大于 $m$，那么它就是无解的。

核心代码：

```cpp
const int N=2e5+10;
int n,m,vis[N],b[N],cnt1,cnt2,ans;
//cnt1是奇数的个数,cnt2是偶数的个数,vis记录这个位置是否需要填数
map<int,int> f;//f记录这个数值是否能填
struct qwq {int val,id;} a[N];
inline bool cmp(qwq x,qwq y) {return x.val>y.val;}
signed main()
{
	n=read();m=read();
	for(ri int i=1;i<=n;++i)
		a[a[i].id=i].val=read();
	sort(a+1,a+n+1,cmp);//从大到小排序
	for(ri int i=1;i<=n;++i)
	{
		if((a[i].val&1)&&!f[a[i].val])
			if(cnt1<n/2) f[a[i].val]=1,++cnt1,vis[i]=1;
		if(!(a[i].val&1)&&!f[a[i].val])
			if(cnt2<n/2) f[a[i].val]=1,++cnt2,vis[i]=1;
	}
	ri int now1=1,now2=2;//now1是当前可填的奇数,now2是当前可填的偶数
	for(ri int i=1;i<=n;++i)
		if(!vis[i])
		{
			++ans;
			if(cnt1<n/2)
			{
				while(f[now1]) now1+=2;//找到当前能填数的最小值
				if(now1>m) return cout<<-1,0;//判无解
				++cnt1,vis[i]=1,a[i].val=now1,f[now1]=1;
			}
			else if(cnt2<n/2)
			{
				while(f[now2]) now2+=2;
				if(now2>m) return cout<<-1,0;
				++cnt2,vis[i]=1,a[i].val=now2,f[now2]=1;
			}
		}
	cout<<ans<<endl;
	for(ri int i=1;i<=n;++i)
		b[a[i].id]=a[i].val;
	for(ri int i=1;i<=n;++i)
		cout<<b[i]<<" ";
	return 0;
}
```

---

