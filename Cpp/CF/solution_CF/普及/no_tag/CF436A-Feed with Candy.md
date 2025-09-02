# Feed with Candy

## 题目描述

### 题意翻译
已知屋子里挂有 $n$ 个糖果，分为两种，水果糖和焦糖糖。对于第 $i$ 个糖果，它的质量为 $m_i$，高度为 $h_i$。Om nom 可以跳跃。他最初时最高可以跳 $x$ 高，此后每吃一个质量为 $m$ 的糖果，最高跳跃高度都会增加 $m$。总之，他不能吃到高过他最高跳跃高度的糖果。另外，由于Om nom是一个很挑剔的食客，他不会吃同一高度上的两颗同类型的糖果。例如，如果焦糖糖果 $1$ 高度在 $5$，焦糖糖果 $2$ 高度也在 $5$，那么Om nom不会同时吃掉他们。请你求出Om nom最多能吃到多少个糖果。

## 样例 #1

### 输入

```
5 3
0 2 4
1 3 1
0 8 3
0 20 10
1 5 5
```

### 输出

```
4
```

# 题解

## 作者：zlqwq (赞：2)

前言：蒟蒻一开始还以为是动态规划呢，后来才发现是贪心。

考虑按什么贪心？显然是质量，因为你吃的质量越高，显然就长得越高。

然后进行两次贪心，先吃类型为 $1$ 的，再吃类型为 $0$ 的。

直接直接取最优答案即可。

## 代码：


```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#define int long long
#define PII pair<int,int>

using namespace std;
struct node {
	int t,h,m;
}; 
const int N=2005;
node a[N];
int n,x,flag[N];
bool cmp(node a,node b){
	return a.m>b.m;
}
signed main() {
	cin>>n>>x;
	for(int i=1;i<=n;++i){
		cin>>a[i].t>>a[i].h>>a[i].m;
	}
	sort(a+1,a+1+n,cmp);
	int cnt1=0,now=0,now1=x;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(flag[j]||a[j].t==now||a[j].h>now1)continue;
			flag[j]=1;
			now=a[j].t;
			now1+=a[j].m;
			cnt1++;
			break;
		}
	}
	int cnt2=0,noww=1,now2=x;
	memset(flag,0,sizeof(flag));
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(flag[j]||a[j].t==noww||a[j].h>now2)continue;
			flag[j]=1;
			now2+=a[j].m;
			noww=a[j].t;
			cnt2++;
			break;
		}
	}
	cout<<max(cnt1,cnt2);
	return 0;
}

```

---

## 作者：ACtheQ (赞：2)

很明显这是一道贪心的题目（并不用 dp)。

考虑如何贪心，首先得满足能吃到的。

然后要按照质量越大，也就是能使得你长得越高的先吃。

因为只有这样，才能达到能吃到其他的糖的要求，从而求出最大值。

由于开始可以随便吃，所以你可以设第一个吃编号为 $0$ 的糖果，再设第一个吃编号为 $1$ 的糖果。

分别做两次贪心即可。

**注意做第二次贪心要初始化！**

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2005;
struct Node
{
	int t,h,m;
}a[N];
bool vis[N];
bool cmp(Node x,Node y)
{
    return x.m>y.m;
}
signed main()
{
	int n,x;
	cin>>n>>x;
    int x1=x;
    int x2=x;
	for(int i=1;i<=n;i++) cin>>a[i].t>>a[i].h>>a[i].m;
    sort(a+1,a+n+1,cmp);
    int last;
    int ans1=0;
    int ans2=0;
    last=0;
    memset(vis,false,sizeof vis);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(vis[j]||a[j].t==last||a[j].h>x1) continue;
			vis[j]=true;
			last=a[j].t;
			x1+=a[j].m;
			ans1++;
			break;
		}
	}
    last=1;
    memset(vis,false,sizeof vis);
    for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(vis[j]||a[j].t==last||a[j].h>x2) continue;
			vis[j]=true;
			last=a[j].t;
			x2+=a[j].m;
			ans2++;
			break;
		}
	}
	cout<<max(ans1,ans2);
    return 0;
}
```

---

## 作者：N_z_ (赞：2)

## 前言
~~翻译误导我好久![dk](https://cdn.luogu.com.cn/upload/pic/62228.png)。~~
## 思路
分两次模拟，一次先吃类型为$0$的糖，一次先吃类型为$1$的糖。

选的时候，注意先选目前能吃到的质量最大的糖，这种取法一定是最优的。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct candy{
    int t,h,m;
}a[2001],b[2001];
bool cmp(candy a,candy b)
{
    if(a.h!=b.h)return a.h<b.h;
    return a.m>b.m;
}
int main()
{
    int n,q;
    cin>>n>>q;
    for(int x=1;x<=n;x++)
    cin>>a[x].t>>a[x].h>>a[x].m;
    sort(a+1,a+1+n,cmp);
    for(int x=1;x<=n;x++)
    b[x]=a[x];
    int ans=0,nowm=q;
    int now=0;
    while(true)
    {
        int man=0;
        a[man].m=0;
        for(int x=1;a[x].h<=nowm&&x<=n;x++)
        if(a[x].m>a[man].m&&a[x].t==now)man=x;
        if(man==0)break;
        ans++;
        now=!now;
        nowm+=a[man].m;
        a[man].m=-1;
    }
    int ans2=0;
    nowm=q;
    now=1;
    while(true)
    {
        int man=0;
        b[man].m=0;
        for(int x=1;b[x].h<=nowm&&x<=n;x++)
        if(b[x].m>b[man].m&&b[x].t==now)man=x;
        if(man==0)break;
        ans2++;
        now=!now;
        nowm+=b[man].m;
        b[man].m=-1;
    }
    cout<<max(ans,ans2)<<endl;
}
```

---

## 作者：jubaoyi2011 (赞：0)

~~这不应该是 dp 吗？？？~~

其实也还好，起码最后发现要贪心：首先要确定能吃到，然后再根据质量贪心，质量越大就长得越高，最后再分别模拟吃水果糖和焦糖的情况就可以啦。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

struct node{
	int t,h,m;
}a[2005];

int n,x,flag[2005];

bool cmp(node a,node b){return a.m>b.m;}

main() {
	cin>>n>>x;
	for(int i=1;i<=n;++i)cin>>a[i].t>>a[i].h>>a[i].m;
	sort(a+1,a+1+n,cmp);
	int cnt_1=0,now=0,now_1=x;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j){
            if(flag[j]||a[j].t==now||a[j].h>now_1)continue;
			flag[j]=1;
			now=a[j].t;
			now_1+=a[j].m;
			cnt_1++;
			break;
		}
	int cnt_2=0,nnow=1,now_2=x;
	memset(flag,0,sizeof(flag));
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(flag[j]||a[j].t==nnow||a[j].h>now_2)continue;
			flag[j]=1;
			now_2+=a[j].m;
			nnow=a[j].t;
			cnt_2++;
			break;
		}
	}
	cout<<max(cnt_1,cnt_2);
	return 0;
}
```

---

## 作者：IkeveLand (赞：0)

本蒟蒻已经在 vjudge 上测过，可以放心食用。
## 解析：
贪心算法，依次求解最优解，对糖果的能量进行排序，每次都吃所能吃到的糖果的最大值并，可以保证能够吃到最多的糖。
## Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+114;

struct node{
	int t,h,m;
}s[N];
bool cmp(node x,node y){
	return x.m>y.m;
}
int  n,xx;
node x[N],y[N];
signed main ()
{
	ios::sync_with_stdio(0);
	scanf("%d%d",&n,&xx);
	for (int i=1;i<=n;i++){
		int t,h,m;
		scanf("%d%d%d",&t,&h,&m);
		x[i].t=t,y[i].t=t;
		x[i].h=h,y[i].h=h;
		x[i].m=m,y[i].m=m;
	}
	sort(x+1,x+n+1,cmp);
	sort(y+1,y+n+1,cmp);
	int ss=xx,res=0,cdy=0;
	for (int i=1;i<=n;i++){
		if (ss>=x[i].h&&x[i].t==cdy){
			ss+=x[i].m;
			res++;
			x[i].t=-1;
			cdy=1-cdy;//转化为其它的candy 
			i=0;//循环求解最优解 
		}
	}
	ss=xx,cdy=1;
	int sum=0;
	for (int i=1;i<=n;i++){
		if (ss>=y[i].h&&y[i].t==cdy){
			ss+=y[i].m;
			sum++;
			y[i].t=-1;
			cdy=1-cdy;
			i=0;//同理 
		}
	}
	if (res>sum) printf("%d",res);
	else printf("%d",sum);
	return 0;	
} 
```

---

## 作者：_Clown_ (赞：0)

$Top$

原来的翻译有误，不知道现在改了没有。
# 概述
|题号|难度|$AC$时间及记录|
| :----: | :----: | :----: |
|$\texttt{CF436A}$|$\texttt{洛谷难度:暂无评定}$|[$\texttt{On 2021/03/19}$](https://www.luogu.com.cn/record/48067578)|
# 解析
这是一道简单题。

题意不难理解。

我们按照题目大意模拟即可。

但是，原来的翻译有误，不知道现在改了没有。

我们考虑分类讨论：

- 第一次吃水果糖。
- 第一次吃焦糖。

然后我们考虑每次选吃哪一个：

- 跳的高度够得到。
- 和上一颗糖不一样。
- 没被吃过。
- 质量最大。

于是代码就不难写出了。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Struct
{
    int Opt;
    int Height;
    int Delta;
    bool Eaten;
    inline bool operator < (const Struct &Compare)const
    {
        if(Height!=Compare.Height)return Height<Compare.Height;
        else return Delta>Compare.Delta;
    }
};
int Total,Highd,High;
Struct Candy[2001];
int main(void)
{
    register int i;
    cin>>Total>>Highd;
    High=Highd;
    for(i=1;i<=Total;i++)cin>>Candy[i].Opt>>Candy[i].Height>>Candy[i].Delta;
    sort(Candy+1,Candy+Total+1);
    register int Last;
    register int Count1;
    Count1=0;
    Last=1;
    for(i=1;i<=Total;i++)Candy[i].Eaten=false;
    while(true)
    {
        register int Mx,W;
        Mx=W=0;
        for(i=1;i<=Total;i++)if(High>=Candy[i].Height&&(!Candy[i].Eaten)&&Last!=Candy[i].Opt)if(Candy[i].Delta>Mx)
        {
            Mx=Candy[i].Delta;
            W=i;
        }
        if(!W)break;
        else Count1++,Candy[W].Eaten=true,High+=Candy[W].Delta;
        Last=1-Last;
    }
    register int Count2;
    Count2=0;
    Last=0;
    High=Highd;
    for(i=1;i<=Total;i++)Candy[i].Eaten=false;
    while(true)
    {
        register int Mx,W;
        Mx=W=0;
        for(i=1;i<=Total;i++)if(High>=Candy[i].Height&&(!Candy[i].Eaten)&&Last!=Candy[i].Opt)if(Candy[i].Delta>Mx)
        {
            Mx=Candy[i].Delta;
            W=i;
        }
        if(!W)break;
        else Count2++,Candy[W].Eaten=true,High+=Candy[W].Delta;
        Last=1-Last;
    }
    cout<<max(Count1,Count2)<<endl;
    return 0;
}
```

---

