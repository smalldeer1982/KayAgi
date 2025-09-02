# Bear and Up-Down

## 题目描述

人生起起落落，就像令人愉快的序列。只要满足了以下两种条件，序列$t1$,$t2$,...,$tn$就叫做令人愉快的：

- 对于每一个奇数$i（i<n）$有$ti<ti+1$;

- 对于每一个偶数$i（i<n）$有$ti>ti+1$;

举个例子，序列$(2,8)$,$(1,5,1)$和$(2,5,1,100,99,120)$就是令人愉快的，但是$(1,1)$,$(1,2,3)$和$(2,5,3,2)$就不是。

Bear Limak有一个正整数序列$t1$,$t2$,...,$tn$。现在这个序列**不是令人愉快的**，Limak想要通过一次交换来修改它。他将要选择两个指数$i<j$然后交换他们的元素$ti$和$tj$从而得到一个令人愉快的序列。数数有多少种方法可以得到。如果交换的两个元素的指数不同则认为这是两种不同的方法。

## 说明/提示

在第一个样例中，有两种方式通过一次交换得到一个令人满意的序列：

1. 交换$t2=8$和$t4=7$。
1. 交换$t1=2$和$t5=7$。

在第二个样例中，只有一种方式—Limak应该交换$t1=200$和$t4=50$。

## 样例 #1

### 输入

```
5
2 8 4 7 7
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
200 150 100 50
```

### 输出

```
1
```

## 样例 #3

### 输入

```
10
3 2 1 4 1 4 1 4 1 4
```

### 输出

```
8
```

## 样例 #4

### 输入

```
9
1 2 3 4 5 6 7 8 9
```

### 输出

```
0
```

# 题解

## 作者：Zzzzzzzm (赞：1)

## 题目分析
首先找到错误的部分，如$123$中$23$之间有一个错误。**因为只能换一次，所以最多有四个错误，这里我们分类讨论。**

四个时以上：
**绝对没有可能。**

四个时：
1.两两相邻：只能交换两个错误的之间点点才有可能改正所有错误，即$2123343$中$21$，$12$，$34$，$43$中都有错误，只有交换$1$与$4$才有可能。

2.其他都不可能

三个时：1.有一对两两相邻:两个连续错误处只能中间那个交换才有可能，另一处前后皆可。2.其他不可能

两个时：1.错误不相临错误前后调整都有可能。2.错误相邻：搜索整个数组与中间点交换

一个时：错误前后搜索整个数组与之替换

没有时：$O$($n^2$)，无法处理，~~思考了半天没有想到，发现根本无此类测试点~~。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[1500010], n;

bool ok(int i){
    if(i < 1 || i >= n)	return 1;
    if((i&1) && a[i] >= a[i+1])	return 0;
    if(!(i&1) && a[i] <= a[i+1])	return 0;
    return 1;
}

vector<int> w;

bool check(int x, int y){
    bool flag = 1;
    swap(a[x], a[y]);
    for(int i = 0; i < w.size(); i++)	if(!ok(w[i]))	flag = 0;
    if(!ok(x) || !ok(x-1) || !ok(y) || !ok(y-1))	flag = 0;
    swap(a[x], a[y]);
    return flag;
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)	scanf("%d", &a[i]);
    for(int i = 1; i < n; i++)	if(!ok(i))	w.push_back(i);
    if(w.size() > 4){
        printf("0\n");
		return 0;
    }
    int x = w[0];
    int ans = 0;
    for(int i = 1; i <= n; i++)	if(check(i, x))	ans++;
	for(int i = 1; i <= n; i++)	if(check(i, x+1))	ans++;
	if(check(x, x+1))	ans--;
    printf("%d\n", ans);
    return 0;
}
```


---

## 作者：lzyqwq (赞：0)

queueforces /qd。

性质题，提供一个不用分类讨论的做法。

我们称一个位置 $i$ 不合法，当且仅当满足两个条件之一：

- $i$ 为奇数，$t_i\ge t_{i+1}$。
- $i$ 为偶数，$t_i\le t_{i+1}$。

由于一次交换最多改变四个位置和右边的大小关系，因此不合法位置超过 $4$ 时直接无解。

那么我们只剩下了 $\mathcal{O}(1)$ 个不合法的位置。对于这些位置 $i$，必有 $i$ 或者 $i+1$ 被交换，不然这个位置仍然不合法。

枚举这些位置，剩下的一个交换的位置直接枚举剩下的所有位置。现在的枚举量已经 $\mathcal{O}(n)$ 了，考虑 $\mathcal{O}(1)$ 判定。

由于一次交换 $(i, j)$ 只会改变 $\mathcal{O}(1)$ 个位置 $i,i-1,j,j-1$ 和右边的大小关系。我们直接维护这些位置的变化量，是 $\mathcal{O}(1)$ 的，注意这些位置之间可能重复不要算重。若消除了所有不合法的位置就算上这种方案。

这样可能会枚举重，用一个 `set` 去重即可。

时间复杂度为 $\mathcal{O}(n\log n)$，空间复杂度为 $\mathcal{O}(n)$。

[AC Link & Code](https://codeforces.com/contest/653/submission/272885981)。

---

## 作者：shao0320 (赞：0)

#### CF653C Bear and Up-Down

~~有一说一这题就是个吹**~~

拿到这题的时候还挺懵的，以为是没见过的玄学计数，再仔细一想发现不对劲，因为如果本来不符合条件的位置太多那就根本不可能有解。

改变$i$位置上的这个数只会影响两个数，$i-1$和$i$。因此如果想让一个本来不满足条件的$i$位置满足条件，要么把$i$调走，要么把$i+1$调走。

把不满足位置>4的判掉之后暴力即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define pb push_back
#define N 200005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,a[N];
vector<int>G;
int check(int x)
{
	if(x<=0||x>=n)return 1;
	if(x%2==1&&a[x]>=a[x+1])return 0;
	if(x%2==0&&a[x]<=a[x+1])return 0;
	return 1;
}
int Swp(int x,int y)
{
	swap(a[x],a[y]);
	int res=1;
	for(int i=0;i<G.size();i++)if(!check(G[i]))res=0;
	if(!check(x)||!check(x+1)||!check(x-1)||!check(y)||!check(y+1)||!check(y-1))res=0;
	swap(a[x],a[y]);
	return res;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++)if(!check(i))G.pb(i);
	if(G.size()>4)return puts("0"),0;
	//cout<<"~~~~~~~~~~~"<<endl;
	//cout<<G.size()<<endl;
	//for(int i=0;i<G.size();i++)cout<<G[i]<<" ";
	int ans=0;
	for(int i=1;i<=n;i++)ans+=Swp(i,G[0]);
	for(int i=1;i<=n;i++)ans+=Swp(i,G[0]+1);
	ans-=Swp(G[0],G[0]+1);
	printf("%d\n",ans);
	return 0;
}
```



---

