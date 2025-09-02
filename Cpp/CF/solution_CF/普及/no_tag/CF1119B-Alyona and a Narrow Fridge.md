# Alyona and a Narrow Fridge

## 题目描述

一个大小是 $2\times h$ 的冰箱（就是 $2$ 列 $h$ 行），有 $n$ 个瓶子，高度分别是 $a_1,a_2,\cdots,a_n$，要求把最多瓶子放进冰箱（要求按顺序）。

瓶子只能放在架子上。可以有任意多个架子。架子不能把瓶子砍成两瓣。

## 样例 #1

### 输入

```
5 7
2 3 5 4 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
10 10
9 1 1 1 1 1 1 1 1 1
```

### 输出

```
4
```

## 样例 #3

### 输入

```
5 10
3 1 4 2 4
```

### 输出

```
5
```

# 题解

## 作者：xht (赞：5)

题目地址：[CF1119B Alyona and a Narrow Fridge](https://www.luogu.org/problemnew/show/CF1119B)

$O(n^2)$ 暴力枚举+贪心

从小到大枚举答案

假设枚举到 $i$ ，将 $a_1$ 到 $a_i$ 排序，从大到小贪心的放。

如果高度超过给定的高度，答案为 $i-1$ 。

如果一直到 $n$ 都没超过，答案为 $n$ 。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll N = 1e3 + 6;
ll n, m, a[N], b[N];

int main() {
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) scanf("%lld", &a[i]);
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= i; j++)
            b[i] = a[i];
        sort(b + 1, b + i + 1);
        ll now = 0;
        for (ll j = i; j > 0; j -= 2) {
            now += b[j];
        }
        if (now > m) {
            cout << i - 1 << endl;
            return 0;
        }
    }
    cout << n << endl;
    return 0;
}
```

---

## 作者：Frozencode (赞：2)

这里给出一种O(nlognlogn)的做法:二分能放的最多的瓶子数，然后按题意检验。详见注释

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=500010;
const ll INF=2147483647;
ll n,h,a[maxn],maxx=0,cnt=0,pos1,pos2,l,r;
vector<ll> e;
bool cmp(ll x,ll y)
{
    return x>y;
}
bool check(ll x)
{
    e.clear();
    for(int i=1;i<=x;i++)
    {
        e.push_back(a[i]);
    }
    sort(e.begin(),e.end(),cmp);//这里基于贪心的思想，把当前所有瓶子按高度排序。
    maxx=0;//maxx代表当前最高高度。
    for(int i=0;i<e.size();i++)//把瓶子按高度从高到低放下去并检验。
    {
        if((i+1)%2)
        {
            pos1=maxx+e[i];
            if(pos1>h)
            {
                return false;
            }
        }
        else
        {
            pos2=maxx+e[i];
            if(pos2>h)
            {
                return false;
            }
            maxx=max(pos1,pos2);
        }
    }
    return true;
}
int main()
{
    cin>>n>>h;
    for(int i=1;i<=n;i++)cin>>a[i];
    l=1;
    r=n+1;
    while(l<r-1)//二分答案
    {
        ll mid=(l+r)>>1;
        if(check(mid))
        {
            l=mid;
        }
        else
        {
            r=mid;
        }
    }
    cout<<l;
    return 0;
}
```


---

## 作者：WsW_ (赞：1)

### 总思路：
枚举 $k$，找到最大的 $k$。  
我们将冰箱视作被挡板切成了多个部分。显然，一个部分内因为不存在挡板，所以最多能放两个瓶子。  
由于最多能放两个瓶子，所以当两个瓶子高度差最小的时候，一格内的空余最少。按照贪心的思想，将瓶子排序，并将排序后相邻的两个瓶子放在一格。该格高度即为两个瓶子间较高的高度。  
举个例子：
```
4 10
1 6 1 6
```
显然应该将两个 $a=6$ 的瓶子放在一格，将两个 $a=1$ 的瓶子放在一格。  
从上述思想得出，给定一个 $k$，检验方法如下：  
1. 将瓶子排序。
2. 将相邻高度的两个瓶子放在同一格。
3. 每一格的高度为格子内两瓶子间较高的高度。
4. 若所有格子的总高度小于等于 $h$，则给出的 $k$ 可行。

---

我将按照时间复杂度从高到低讲解四种方法。  

---

### 1.暴力枚举
时间复杂度为 $O\left(n^2 \log_2 n\right)$（xht 题解中写的时间复杂度是错的）。  
循环 $n$ 次枚举所有的 $k$，每次按照总思路检验。当 $k$ 不可行时，说明已经找到了最大的 $k$，停止枚举并输出答案。  
如果用 `sort` 实现，可以参考 [xht 的题解](https://www.luogu.com.cn/blog/xht37/cf1119b-alyona-and-a-narrow-fridge)。  
我想到了当年的 [[CSP-J2020] 直播获奖](https://www.luogu.com.cn/problem/P7072)，考场上用 `sort` 喜提 50 分。于是我选择使用优先队列，在输入的同时枚举 $k$，常数更小。
#### 代码和[提交记录](https://codeforces.com/problemset/submission/1119/214691912)：
```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue<int>q;
int a[10003];
int sum;
int n,h;
int main(){
	scanf("%d%d",&n,&h);
	for(int i=1;i<=n;++i){//循环输入的同时枚举k
		sum=0;
		scanf("%d",&a[i]);
		while(!q.empty()){
			q.pop();
		}
		for(int j=1;j<=i;++j)q.push(a[j]);
		for(int j=1;j<=i;j++){
			if(j&1){//第奇数个为较大的。例如a[1]在a[2]前，a[1]>a[2]。
				sum+=q.top();
				if(sum>h)return !printf("%d",i-1);//当前k不可行，上一个k可行，输出上一个k
			}
			q.pop();
		}
	}
	printf("%d",n);
	return 0;
}

```

---

### 2.插入排序优化排序过程
时间复杂度为 $O\left(n^2\right)$。  
想到了 [[CSP-J 2021] 插入排序](https://www.luogu.com.cn/problem/P7910)。由于每次枚举 $k$ 相较上次只是多了一个数，因此只需要将这个数 $O\left(n\right)$ 插入到原来已经排序好的数列中。
#### 代码和[提交记录](https://codeforces.com/problemset/submission/1119/214692288)
```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue<int>q;
int a[1003];
int sum;
int n,h;
int main(){
	scanf("%d%d",&n,&h);
	for(int i=1;i<=n;++i){
		sum=0;
		scanf("%d",&a[i]);
		for(int j=i;j>1;--j){//O(n)插入a[i]
			if(a[j]>a[j-1]){
				int t=a[j];
				a[j]=a[j-1];
				a[j-1]=t;
			}
		}
		for(int j=1;j<=i;++j){
			if(j&1){
				sum+=a[j];
				if(sum>h)return !printf("%d",i-1);
			}
		}
	}
	printf("%d",n);
	return 0;
}
```

---

### 3.二分答案优化枚举过程
时间复杂度为 $O\left(n (\log_2 n)^2\right)$。  
在第一种方法中，我们提到：
>当 $k$ 不可行时，说明已经找到了最大的 $k$，停止枚举并输出答案。  

这体现了 $k$ 是否可行具有单调性。通俗地说，当 $k$ 小于等于某个值的时候，$k$ 可行；当 $k$ 大于那个值的时候 $k$ 不可行。  
求可行值最大，可以用二分答案枚举 $k$。  
可以参考 [cccyyylll888 的题解](https://www.luogu.com.cn/blog/cccyyylll888/cf1119b-alyona-and-a-narrow-fridge-ti-xi)。

---

### 4.离散化+二分+桶排
时间复杂度 $O\left(n \log_2 n\right)$，为目前已知最优解。  
看到[这篇题解](https://www.luogu.com.cn/blog/430409/solution-cf1119b)提到有 $O\left(n \log n\right)$ 的做法，中午没吃饭想了一个小时（哭）。  
在二分答案的基础上，我考虑对其中的排序过程进行优化。一开始考虑的是按照第二种方法每次 $O\left(n\right)$ 进行插入排序。但由于每次二分导致区间并不固定，大概每次要插入或删除 $\log n$ 个数，总时间复杂度依然为 $O\left(n \log^2n\right)$。  
依旧是想到了 [[CSP-J2020] 直播获奖](https://www.luogu.com.cn/problem/P7072)的另一个正解，用桶排进行排序，每次排序时间复杂度为 $O\left(n\right)$。  
题目中 $1\le a_i\le 10^9$，肯定不能直接桶排。根据我做毒瘤分块题的经验，立刻想到了 $1\le n\le 10^3$，可以先离散化再桶排。  
这样做的时间复杂度为离散化时的排序预处理 $O\left(n \log_2 n\right)$，以及二分答案的 $O\left(n \log_2 n\right)$。
#### 代码和[提交记录](https://codeforces.com/contest/1119/submission/214705216)
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int s,id;
};
node a[10003];
int b[10003],bl;
int box[10003];
int t[10003],len;
int cnt[10003];
int sum;
int n,h;
bool cmp1(node u,node v){
	if(u.s!=v.s)return u.s<v.s;
	return u.id<v.id;
}
bool cmp2(node u,node v){
	return u.id<v.id;
}
bool check(int x){
	bl=0;
	for(int i=1;i<=x;++i)++box[a[i].s];
	for(int i=1;i<=n;++i){
		while(box[i]>0){
			--box[i];
			b[++bl]=i;
		}
	}
	int sum=0;
	for(int i=x;i>=1;i-=2){
		sum+=t[b[i]];
		if(sum>h)return 0;
	}
	return 1;
}
int main(){
	scanf("%d%d",&n,&h);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i].s);
		a[i].id=i;
	}
	sort(a+1,a+1+n,cmp1);
	t[1]=a[1].s;
	a[1].s=len=1;
	for(int i=2;i<=n;i++){
		if(a[i].s!=a[i-1].s){
			t[++len]=a[i].s;
		}
		a[i].s=len;
	}
	sort(a+1,a+1+n,cmp2);
	int l=1,r=n,mid;
	while(l<=r){
		mid=(l+r+1)>>1;
		if(l==r)break;
		if(check(mid)){
			l=mid;
		}
		else{
			r=mid-1;
		}
	}
	printf("%d",l);
	return 0;
}

```

---

### 小结：
做题的快乐不仅仅在于 $\mathtt{AC}$，更在于对算法优化的精益求精。  
$1\le n\le 10^3$ 的数据固然可以用很复杂的算法过去，但谁又能拒绝一个 $O\left(n \log_2 n\right)$ 的优美算法呢？

---

## 作者：Coros_Trusds (赞：1)

[$\rm \color{black}CF1119B~official ~solution$](https://codeforces.com/blog/entry/66411)

# 题目大意

一个大小是 $2\times h$ 的冰箱（就是 $2$ 列 $h$ 行），有 $n$ 个瓶子，高度分别是 $a_1,a_2,a_3,\cdots,a_n$，要求把最多瓶子放进冰箱（不要求按顺序）。

瓶子只能放在架子上。可以有任意多个架子。架子不能把瓶子砍成两瓣。

# 题目分析

考虑贪心。

最优方案一定是：将所有高度降序排列，$h_{2k-1},h_{2k}$ 放在一排，价值为 $\sum\limits_{k=0}^{\left\lfloor\tfrac{n}{2}\right\rfloor}h_{2k+1}$。

如此去算即可。

然后只要尝试所有可能的 $i$，排序前 $i$ 个瓶子的高度，当满足要求时输出正确答案。

具体地，若当前和大于了高度 $h$，那么你是时候结束了，答案即为 $i-1$。

如果均没有超过，最后输出 $n$。

总复杂度为 $O(n^2\log n)$。

还有 $O(n\log n)$ 的做法，但是并不会，也没有在 $\rm Codeforces$ 的提交记录中找到，会的大佬可以教教 $\texttt{CT}$。

# 代码

代码和 $\rm xht$ 的差不多，主要是对 $\rm xht$ 的题解的补充。

```cpp
//2021/12/16

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <cstdio>

#include <climits>//need "INT_MAX","INT_MIN"

#include <ctime>

#include <algorithm>

#define enter() putchar(10)

#define debug(c,que) cerr<<#c<<" = "<<c<<que

#define cek(c) puts(c)

#define blow(arr,st,ed,w) for(register int i=(st);i<=(ed);i++)cout<<arr[i]<<w;

#define speed_up() cin.tie(0),cout.tie(0)

#define endl "\n"

#define Input_Int(n,a) for(register int i=1;i<=n;i++)scanf("%d",a+i);

#define Input_Long(n,a) for(register long long i=1;i<=n;i++)scanf("%lld",a+i);

#define mst(a,k) memset(a,k,sizeof(a))

namespace Newstd
{
	inline int read()
	{
		int x=0,k=1;
		char ch=getchar();
		while(ch<'0' || ch>'9')
		{
			if(ch=='-')
			{
				k=-1;
			}
			ch=getchar();
		}
		while(ch>='0' && ch<='9')
		{
			x=(x<<1)+(x<<3)+ch-'0';
			ch=getchar();
		}
		return x*k;
	}
	inline void write(int x)
	{
		if(x<0)
		{
			putchar('-');
			x=-x;
		}
		if(x>9)
		{
			write(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

const int ma=1005;

int a[ma],t[ma];

int n,m;

inline void init(int i)
{
	for(register int j=1;j<=i;j++)
	{
		t[j]=a[j];
	}
}

int main(void)
{
	n=read(),m=read();
	
	Input_Int(n,a);
	
	for(register int i=1;i<=n;i++)
	{
		init(i);
		
		sort(t+1,t+i+1);
		
		int now(0);
		
		for(register int j=i;j>=1;j-=2)
		{
			now+=t[j];
		}
		
		if(now>m)
		{
			printf("%d\n",i-1);
			
			return 0;
		}
	}
	
	printf("%d\n",n);
	
	return 0;
}
```

---

## 作者：cccyyylll888 (赞：0)

题目：[点击进入题目（CF1119B） 放瓶子](https://www.luogu.com.cn/problem/CF1119B)。

## 分析题意：

我们放 $k$ 个瓶子进入冰箱，上下两个瓶子之间有挡板，且挡板不能将瓶子分割，求出能满足将前 $k$ 个瓶子放入冰箱的最大的 $k$。

## 解决方法：

#### 一、如何放瓶子？

现在假设我们已经找出了 $k$，那么，我们怎么知道 $k$ 是否满足要求呢？

考虑放瓶子的最优方案，使所需高度最低。

由于最高的瓶子一定会用一个挡板，设其高度为 $a_k$，则剩余的高度为 $h-a_k$。

因为我们想要的是最小的高度，并且最高的瓶子用了的挡板还有一格可放，则我们当然会选择放第二高的瓶子。

那么，问题就变成了有 $k-2$ 个瓶子，放入 $h-a_k$ 的高度。以此类推，我们可以得到瓶子放置顺序为从下到上放从高到低的瓶子。

#### 二、如何找到 $k$？

#### 答案：二分。

我们考虑二分。

考虑 $k$ 的最大值。若当前 $k$ 满足最优方案下的高度小于等于 $h$，则 $k$ 是符合条件的，从 $k$ 到二分区间末尾继续寻找。反之，则从二分区间开头到 $k$ 寻找。

代码：

```cpp
//时间复杂度:O(nlogn)
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
long long n,h;
long long a[100005];//a存瓶子高度 
long long d[100005];//d为排序时所用数组(line12) 
bool isok(long long p)
{
	for(int i = 1;i <= p;i++)
	d[i] = a[i];
	sort(d+1,d+p+1);
	long long needh = 0;//最优方案所需高度 
	for(int i = p;i >= 1;i -= 2)
	{
		needh += d[i];//挡板高度
	}
	//所做的一点优化：只需考虑每一层最高的瓶子的高度，即为挡板之间高度，不用考虑第二高的。 
	if(needh <= h)//满足条件 
	return true;
	else
	return false;
}
int main()
{
	cin >> n >> h;
	for(int i = 1;i <= n;i++)
	{
		cin >> a[i];
	}
	int now;//相当于平时的mid，代表现在二分到的点 
	int l = 1,r = n;
	while(l <= r)
	{
		now = (l+r+1)/2;
		if(l == r)
		break;
		if(isok(now))//如果可以在冰箱中装得下 
		{
			l = now;
		}
		else
		{
			r = now-1;
		}
	}
	cout << l;//答案 
	return 0;
} 
```

---

## 作者：皮卡丘最萌 (赞：0)

主要思路：**二分**。

首先对**能放的个数**进行**二分**，假设当前**二分**到放 $k$ 个瓶子。

根据**贪心**，我们知道一定要把**高度最相近**的 $2$ 个瓶子放在同一层。所以我们需要**从大到小排序**（思考：为什么是从大到小？） ，每 $2$ 个瓶子一组。

最后判断高度和是否符合即可。

时间复杂度$O(n \log^2 n)$，可以通过本题。

代码：

```pascal
var n,m,i,t,w,mid,bao:longint;
a,b:array[0..1001] of longint;
procedure sort(l,r: longint);
   var i,j,x,y: longint;
   begin
      i:=l; j:=r;
      x:=b[(l+r) div 2];
      repeat
        while b[i]<x do inc(i);
        while x<b[j] do dec(j);
        if not(i>j) then
          begin
          y:=b[i];b[i]:=b[j];b[j]:=y;
          inc(i); j:=j-1;
          end;
      until i>j;
      if l<j then sort(l,j);
      if i<r then sort(i,r);
   end;                        //排序

function pd(x:longint):boolean;
var s:int64;
begin
s:=0;
while x>0 do
  begin
  s:=s+b[x];
  if s>m then exit(false);
  dec(x,2);
  end;
exit(true);
end;                          //判断是否可行

begin
readln(n,m);
for i:=1 to n do read(a[i]);
t:=1; w:=n;
while t<=w do
  begin
  mid:=(t+w) div 2;
  b:=a; sort(1,mid);
  if pd(mid) then
    begin bao:=mid; t:=mid+1; end
  else w:=mid-1;
  end;                         //二分答案
writeln(bao);
end.
```


---

