# Two progressions

## 题目描述

等差数列指的是一个任意前后两个元素之间差为定值的非空数列。这个定值被称为公差。例如数列`3,7,11,15`是等差数列。我们规定任何元素个数为 $1$ 或 $2$ 的数列都是等差数列，而元素个数为 $0$ 的数列不是等差数列。

给你一个由不同整数 $a_1,a_2,\cdots,a_n$ 组成的数列，你需要将它分为两个等差数列或确定这是不可能做到的。在分成两个等差数列的时候元素之间的相对位置不能发生变化。

## 样例 #1

### 输入

```
6
4 1 2 7 3 10
```

### 输出

```
1 2 3 
4 7 10 
```

## 样例 #2

### 输入

```
5
1 2 3 -2 -7
```

### 输出

```
1 2 3 
-2 -7 
```

# 题解

## 作者：kouylan (赞：4)

## 题解 CF125D 【Two progressions】

[洛谷题面传送门](https://www.luogu.com.cn/problem/CF125D)

[CF题面传送门](https://codeforces.ml/contest/125/problem/D)

首先，我们能够确定，取出前三个元素，就可以确定两个等差数列。（$a_1,a_2\dots$或$a_2,a_3\dots$或$a_1,a_3\dots$，余下的为另一个）

那么我们就可以分三种情况进行尝试。

我们先贪心的想，取出所有能构成第一个等差数列的数，余下的构成第二个数列。接下来，我们就要判断第二个数列是否可以构成等差数列。

此处会有 $3$ 种情况。

**情况一：整个数列都是等差数列（第二个等差数列为空）**

面对这种情况，我们只要取出等差数列中的最后一个数，把它当成第二个数列就行了。

**情况二：第二个数列只有一个元素**

直接输出即可。

**情况三：第二个数列本身无法构成等差数列**

面对这种情况，我们不要急着输出 "No solution"。因为我们是把所有能构成第一个等差数列的数都放到第一个等差数列中去了，所以会造成，有些第一个数列中的数如果到第二个数列中去，那么第二个数列就能构成等差数列。而且我们是贪心的取，因此可以移到第二个数列中的数，必定是第一个数列的一个后缀（因为不能改变元素的相对位置）。所以在此，第二个等差数列又可以分为两种小情况：

**情况三.1：公差为第二个数列的末项减去第一个数列末项的差**

**情况三.2：公差为第二个数列最后两项元素的差**

为什么不是前两项的差？因为前面几项可能被我们放在第一个数列中的数拆散了。

这两种情况的实现方法是一样的。只需要从末项（肯定是第二个数列的末项）往前推，在过程中插入第一个数列的数即可。

下面是 AC 代码
```cpp
/*
Codeforces 125D
*/
#include <bits/stdc++.h>
using namespace std;

#define int long long

int n,a[30005];
int l1,l2,r1,p1[30005],p2[30005];

bool legal(int dif)
{
	int pre=p2[l2];
	for(int i=l2-1;i>=1;)
	{
		if(pre-p2[i]==dif)
			pre = p2[i], i--;
		else if(pre-p1[r1]==dif)
			pre = p1[r1], r1--;
		else
			return false;
	}
	return true;
}

void work(int st,int dif)
{
	l1 = l2 = 0;
	for(int i=1;i<st;i++)
		p2[++l2] = a[i];
	int now=a[st];
	for(int i=st;i<=n;i++)
		if(a[i]==now)
			p1[++l1] = a[i], now += dif;
		else
			p2[++l2] = a[i];
//	for(int i=1;i<=l1;i++)cout<<p1[i]<<' ';cout<<endl;
	if(l2==0)
	{
		for(int i=1;i<l1;i++)
			cout<<p1[i]<<' ';
		cout<<endl<<p1[l1]<<endl;
		exit(0);
	}
	if(l2==1)
	{
		for(int i=1;i<=l1;i++)
			cout<<p1[i]<<' ';
		cout<<endl;
		for(int i=1;i<=l2;i++)
			cout<<p2[i]<<' ';
		cout<<endl;
		exit(0);
	}
	r1 = l1;
	if(legal(p2[l2]-p2[l2-1]))
	{
		for(int i=1;i<=r1;i++)
			cout<<p1[i]<<' ';
		cout<<endl;
		int d=p2[l2]-p2[l2-1];
		int pre=p2[1];
		cout<<p2[1]<<' ';
		for(int i=2;i<=l2;)
			if(p2[i]-pre==d)
				cout<<p2[i]<<' ', pre = p2[i], i++;
			else
				cout<<p1[++r1]<<' ', pre = p1[r1];
		cout<<endl;
		exit(0);
	}
	r1 = l1;
	if(legal(p2[l2]-p1[l1]))
	{
		for(int i=1;i<=r1;i++)
			cout<<p1[i]<<' ';
		cout<<endl;
		int d=p2[l2]-p1[l1];
		int pre=p2[1];
		cout<<p2[1]<<' ';
		for(int i=2;i<=l2;)
			if(p2[i]-pre==d)
				cout<<p2[i]<<' ', pre = p2[i], i++;
			else
				cout<<p1[++r1]<<' ', pre = p1[r1];
		cout<<endl;
		exit(0);
	}
}

signed main()
{
	cin>>n;
	for(int i=1;i<=n;cin>>a[i++]);
	work(1,a[2]-a[1]);
	work(1,a[3]-a[1]);
	work(2,a[3]-a[2]);
	puts("No solution");
	
	return 0;
}
/*
9
0 3 6 8 9 10 11 12 13
10
-30 -20 -10 0 10 24 22 20 18 16
7
0 3 4 5 6 12 18
*/
```

祝大家 AC 愉快！

---

## 作者：__lfxxx_ (赞：2)

[博客园](https://www.cnblogs.com/noipwen/p/18001885)

## 思路
首先可以发现前三个数中的两个数一定为一个等差数列中，所以我们对于前三个数枚举哪两个数是一个等差数列中的，设这两个数的差为 $w$，在原数列中找到一个最长的公差为 $w$ 的等差数列，记为 $A$，剩下的数记为 $B$，此时有三种可能。

1. $|B|=0$，此时可以知道原数组就是等差数列，此时我们可以把 $B$ 当成最后一个数即可。
2. $|B|\leq 2$，通过题意可知 $B$ 也为等差数列，直接输出即可。
3. $|B|>2$，此时答案不一定不存在，有可能在 $A$ 中选择一些数到 $B$ 后能使 $B$ 成为等差数列，为了仍满足 $A$ 为等差数列，所以我们取出的这些数一定会为 $A$ 的后缀，然后插入进 $B$ 中，这个过程可以用set来维护，但是我们想要快速维护 $B$ 是否为等差数列仍需要知道序列的公差，所以我们可以枚举公差，而有效的公差只有 $B$ 的最后两位的差和 $A$ 与 $B$ 最后两位的差这两种情况。

时间复杂度：$O(n\log n)$。

## 代码
```cpp
#include<bits/stdc++.h>
#define mm 600010
using namespace std;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=(x<<3)+(x<<1)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int n,a[mm];
int A[mm],B[mm];
int num1,num2;
set<int> s;
bool vis[mm];
void check(int w)//将A的后缀插入到B中
{
    s.clear();int add=0;
    for(int i=2;i<=num2;i++)if(a[B[i]]-a[B[i-1]]!=w) ++add;
    for(int i=1;i<=num2;i++)s.insert(B[i]);
    for(int i=num1;i>=0;i--)
    {
        if(add==0)
        {
            if(i==0)
            {
                printf("%d\n",a[1]);
                for(int j=2;j<=n;j++) printf("%d ",a[j]);printf("\n");
                exit(0);
			}
            for(int j=1;j<=i;j++)printf("%d ",a[A[j]]),vis[A[j]]=true;printf("\n");
            for(int j=1;j<=n;j++)if(!vis[j])printf("%d ",a[j]);printf("\n");
            exit(0);
        }
        if(i==0) break;
        int X=A[i];
        s.insert(X);
        auto it=s.lower_bound(X);
        auto it1=it;it1--;auto pre=it1;
		auto it2=it;it2++;auto nxt=it2;
        if(it==s.begin())
        {
            if(a[*nxt]-a[*it]!=w) ++add;
            continue;
		}
        if(it==s.end())
        {
            if(a[*it]-a[*pre]!=w) ++add;
            continue;
        }
        if(a[*nxt]-a[*pre]==w){add+=2;continue;}
        if(a[*it]-a[*pre]!=w && a[*nxt]-a[*it]!=w) ++add;
        else if(a[*it]-a[*pre]==w && a[*nxt]-a[*it]==w) --add;
        //插入一个数，动态维护B是否为等差数列
    }
}
void work(int sta,int w)
{
    num1=num2=0;
    for(int i=1;i<sta;i++) B[++num2]=i;
    for(int i=sta;i<=n;i++)
        if(a[i]-a[A[num1]]==w || i==sta) A[++num1]=i;
        else B[++num2]=i;
    if(num2==0)
    {
        for(int i=1;i<num1;i++) printf("%d ",a[A[i]]);printf("\n");
        printf("%d\n",a[A[num1]]);
        exit(0);
    }//情况1
    if(num2<=2)
    {
        for(int i=1;i<=num1;i++) printf("%d ",a[A[i]]);printf("\n");
        for(int i=1;i<=num2;i++) printf("%d ",a[B[i]]);printf("\n");
        exit(0);
    }//情况2
    check(a[B[num2]]-a[B[num2-1]]);
    check(a[B[num2]]-a[A[num1]]);
    check(a[A[num1]]-a[B[num2]]);
    //情况3
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    work(1,a[2]-a[1]),work(1,a[3]-a[1]),work(2,a[3]-a[2]);//枚举哪两个数在同一个等差数列中
    puts("No solution");
}
```

---

## 作者：王熙文 (赞：0)

## 思路

首先可以发现，前三个数中至少有两个数在同一个等差数列中，且是这个等差数列的前两项。因此可以枚举哪两个数在同一个等差数列中。这样就可以确定一个等差数列的公差了。设这个等差数列的下标为 $A$。考虑将后面属于 $A$ 的数提出来，那么答案的等差数列的下标一定是 $A$ 的前缀。

考虑枚举这个前缀，那么只需要检查剩下的位置是否能组成等差数列 $B$。设前缀的下一个数的位置为 $x$，那么 $B$ 中的下标分为两部分，一部分是 $<x$ 且不属于 $A$ 的下标，另一部分是 $\ge x$ 的下标。分别对两部分预处理是否为等差数列，再检查拼起来的公差是否相等即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n; int a[500010];
bool vis[500010];
int tot1,id1[500010],tot2,id2[500010];
bool ok[500010];
bool dc[500010]; 
bool get_ans(int x,int y,int z)
{
	int d=a[y]-a[x];
	memset(vis,0,n+5);
	int now=a[y]+d;
	tot1=tot2=0;
	id1[++tot1]=x,id1[++tot1]=y;
	for(int i=y+1; i<=n; ++i)
	{
		if(a[i]==now) id1[++tot1]=i,now+=d;
	}
	memset(vis,0,n+5);
	for(int i=1; i<=tot1; ++i) vis[id1[i]]=1;
	for(int i=1; i<=n; ++i)
	{
		if(!vis[i]) id2[++tot2]=i;
	}
	memset(ok,0,n+5);
	ok[0]=ok[1]=1;
	for(int i=2; i<=tot2; ++i) ok[i]=(ok[i-1]&(a[id2[i]]-a[id2[i-1]]==a[id2[2]]-a[id2[1]]));
	if(ok[tot2])
	{
		if(tot2==0)
		{
			for(int i=1; i<=tot1-1; ++i) cout<<a[id1[i]]<<' '; cout<<'\n';
			cout<<a[id1[tot1]];
		}
		else
		{
			for(int i=1; i<=tot1; ++i) cout<<a[id1[i]]<<' '; cout<<'\n';
			for(int i=1; i<=tot2; ++i) cout<<a[id2[i]]<<' ';
		}
		exit(0);
	}
	for(int j=2; j<=tot1; ++j)
	{
		int i=id1[j];
		int wz=lower_bound(id2+1,id2+tot2+1,i)-id2-1;
		if(wz==0)
		{
			if(dc[i])
			{
				for(int k=1; k<=j-1; ++k) cout<<a[id1[k]]<<' '; cout<<'\n';
				for(int k=i; k<=n; ++k) cout<<a[k]<<' ';
				exit(0);
			}
			continue;
		}
		if(ok[wz] && dc[i])
		{
			bool flag=0;
			if(wz==1 && i==n) flag=1;
			else if(wz==1) { if(a[i]-a[id2[wz]]==a[n]-a[n-1]) flag=1; }
			else if(i==n) { if(a[n]-a[id2[wz]]==a[id2[2]]-a[id2[1]]) flag=1; }
			else if(a[id2[2]]-a[id2[1]]==a[n]-a[n-1] && a[n]-a[n-1]==a[i]-a[id2[wz]]) flag=1;
			if(flag)
			{
				for(int k=1; k<=j-1; ++k) cout<<a[id1[k]]<<' '; cout<<'\n';
				for(int k=1; k<=wz; ++k) cout<<a[id2[k]]<<' ';
				for(int k=i; k<=n; ++k) cout<<a[k]<<' ';
				exit(0);
			}
		}
	}
	return 0;
}
signed main()
{
	cin>>n;
	for(int i=1; i<=n; ++i) cin>>a[i];
	dc[n]=1;
	for(int i=n-1; i>=1; --i) dc[i]=(dc[i+1]&(a[i+1]-a[i]==a[n]-a[n-1]));
	if(n==2) cout<<a[1]<<'\n'<<a[2];
	else
	{
		get_ans(1,2,3),get_ans(1,3,2),get_ans(2,3,1);
		cout<<"No solution";
	}
	return 0;
}
```

---

