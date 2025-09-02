# Born This Way

## 题目描述

$Arkady$ 买了一张从 $A$ 市到 $C$ 市的机票。不幸的是，这两个城市之间没有直飞航班，但是从 $A$ 市到 $B$ 市和从 $B$ 市到 $C$ 市的航班有很多。

从 $A$ 市到 $B$ 市有 $N$ 个航班，它们分别在 $a_1,a_2,a_3,...$ $,a_n$ 时起飞，在 $ta$ 个单位时间的飞行后到达 $B$ 市。

从 $B$ 市到 $C$市 有 $M$ 个航班，它们在 $b_1,b_2,b_3,...$ $,b_m$ 起飞。在 $tb$ 个单位时间的飞行后到达 $C$ 市。

转机的时间忽略不计，因此只有当 $b_j \ge a_i+ta$ 时，$Arkady$ 才能搭乘从 $A$ 市到 $B$ 市的第 $i$ 次航班和 $B$ 市到 $C$ 市的第 $j$ 次航班抵达目的地。 

你最多可以不择手段地取消 $k$ 次航班。如果你取消了航班，$Arkady$ 当然就不能搭乘它了。

$Arkady$ 想尽早到 $C$ 市，而你想让他尽可能地晚到 $C$ 市。计算你取消了 $k$ 次航班之后 $Arkady$ 最早到达 $C$ 市的时间点。如果你可以通过取消 $k$ 次或更少的航班，使 $Arkady$ 不能达到 $C$ 市，请输出 $−1$ 。

## 样例 #1

### 输入

```
4 5 1 1 2
1 3 5 7
1 2 3 9 10
```

### 输出

```
11
```

## 样例 #2

### 输入

```
2 2 4 4 2
1 10
10 20
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4 3 2 3 1
1 999999998 999999999 1000000000
3 4 1000000000
```

### 输出

```
1000000003
```

# 题解

## 作者：Jameswood (赞：5)


### 题意大概

有三个点A、B、C，之间有联结AB、BC的线段，且通过线段所需的时间给定。

建立一条时间线，从时间点0开始。可以从点A出发前往点B和从点B出发前往点C的时间点分别有m和n个。

问题是求删除k个允许的出发时间点后，能否使在任意时刻从点A出发，都无法到达点C。不能的话，则求出删除后从点A出发，选择最优策略下最终达到点C的最晚时间。

------

### 太烦不看或大佬专用版

```pascal
其实还是挺好做的，因为你无论如何也只能在AB和BC这两条线路上选择删除的时间点，所以只要将k次分成两部分给两条线路即可。
实现上就枚举k1(0<=k1<=k)，每次分别取消AB上的前k1个时间点和BC上的前（k-k1）个时间点，然后稍加比较，记录最优值。若有任意一方不能达到，则输出-1。
```
------

### 详解版

~~显而易见的~~ 如果 $k$ 的值大于等于 $n$ 或 $m$ ，那么 Arkady 即使手眼通天也无法到达点C。这个可以先行特判掉。

```cpp
//注：这个时候可以使从A到B或从B到C的所有允许出发的时间点都被删除，即根本无法出发
if(k>=n||k>=m){
	printf("-1\n");
	return 0;
}
```

然后从0开始枚举一个数到k（即0<=i<=k），代表在从A到B的出发点中删除几个，因为输入是递增的，所以无需排序。只要忽视前 i 个点就可以了。

同时使用一个 while 循环进行判断，如果在B中的出发点已经无法被抵达了，则向前推进一位，这个计数器需要全程保留。

这里需要一个特判，若从B到C的剩余的出发点小于等于 k-i 个，那么删除 k 个
以后就无法抵达C点了。

记录一个 ANS 作为最晚抵达时间。

```cpp
//注：因为前面已经判断过了，所以不用担心 i>=n 或 k-i>=m 的情况
for(int i=0;i<=k;++i){
	while(a[i+1]+ta>b[p]&&p<=m) ++p;
	if(p+k-i>m){
		ans=-1;break;
	}
	ans=max(ans,b[p+k-i]+tb);
}
```

------

最后附上标程：

```cpp
//Made by Jameswood
#include<cstdio>
#include<cstdlib>
using namespace std;
const int SIZE=200005;
int m,n,ta,tb,k,a[SIZE],b[SIZE],ans,p;
inline int max(int x,int y){
	if(x>y) return x;
	else return y;
}
int main(){
	scanf("%d%d%d%d%d",&n,&m,&ta,&tb,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++) scanf("%d",&b[i]);
	if(k>=n||k>=m){
		printf("-1\n");
		return 0;
	}
	for(int i=0;i<=k;++i){
		while(a[i+1]+ta>b[p]&&p<=m) ++p;
		if(p+k-i>m){
			ans=-1;break;
		}
		ans=max(ans,b[p+k-i]+tb);
	}
	printf("%d\n",ans);
	return 0;
} 
```


------

---

## 作者：xh001 (赞：3)

# 题意
每组数据包含 $5$ 个数 $n$，$m$，$ta$，$tb$，$k$ 和一个长度为 $n$ 的序列 $a$，一个长度为 $m$ 的序列 $b$，$ta$ 表示从 $A$ 飞到 $B$ 所需时间，$tb$ 表示从 $B$ 飞到 $C$ 所需时间，$k$ 表示可以删去 $k$ 个出发点，序列 $a$ 为可以从 $A$ 出发到 $B$ 的时间点，序列 $b$ 为可以从 $B$ 出发到 $C$ 的时间点，求在删去 $k$ 个出发点后从 $A$ 到 $C$ 的最晚最早时间（不能到达则输出`-1`）。
# 思路
首先进行分类讨论：

当 $n \le k$ 或 $m \le k$ 时：显然无法到达，直接特判即可。

否则从 $0$ 开始枚举删去从 $A$ 出发的出发点个数，并记录下最晚到达时间，**同时**，若当前 $B$ 到 $C$ 的出发点个数小于等于 $k-i$，则无法到达。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//好习惯。 
ll n,m,ta,tb,k,a[200001],b[200001];
ll t;//记录最晚到达时间。 
ll cnt;//记录当前枚举到b数组的位置。 
inline ll read()
{
	ll k=0,f=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) f|=c=='-';
	for(;isdigit(c);c=getchar()) k=(k<<1)+(k<<3)+(c^48);
	return f?-k:k;
}
int main()
{
	n=read();
	m=read();
	ta=read();
	tb=read();
	k=read();
	if(k>=n || k>=m)//特判。 
	{
		cout<<-1;
		return 0;
	}
	for(ll i=1;i<=n;i++) a[i]=read();
	for(ll i=1;i<=m;i++) b[i]=read();
	for(int i=0;i<=k;++i)
	{
		while(a[i+1]+ta>b[cnt] && cnt<=m) ++cnt;
		if(cnt+k-i>m)//飞不了就直接输出。 
		{
			cout<<-1;
			return 0;
		}
		t=max(t,b[cnt+k-i]+tb);//最晚到达时间。 
	}
	cout<<t;
	return 0;
}
```


---

## 作者：hao_zi6366 (赞：0)

## 题意分析
显然，在 $k \ge m$ 或 $k \ge n$ 时，一定没有办法到达，可以直接输出 -1。

```cpp
if(k>=n || k>=m){
		std::cout<<-1;exit(0);
}
```

接下来依次模拟 k 次的删除，一般情况我们删除现在 A 市到 B 市的最早的航班。

接着用 while 判断当下的 B 市到 C 市航班是否可以接上 A 市到 B 市航班，如果不可以，则查看下一趟航班。

```cpp
while(a[now_a]+ta>b[now_b] && now_b<=m) now_b++;
```

然后判断现在的 B 市到 C 市的航班是否在现有情况全部删除完后还有航班，如果一定没有，就输出 -1。

```cpp
if(now_b>m+i-k){
	std::cout<<-1;exit(0);
}
```

最后更新答案即可。

------------

## 完整代码
```cpp
#include<bits/stdc++.h>
#define N 200005
typedef long long ll;
int a[N],b[N];

int main(){
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	
	int ans=0;
	int n,m,ta,tb,k,now_b=1;
	std::cin>>n>>m>>ta>>tb>>k;
	for(int i=1;i<=n;i++)std::cin>>a[i];
	for(int i=1;i<=m;i++)std::cin>>b[i];
	if(k>=n || k>=m){
		std::cout<<-1;exit(0);
	}
	for(int i=0;i<=k;i++){								//模拟k次删除 
		while(a[i+1]+ta>b[now_b] && now_b<=m) now_b++;	//如果搭乘不上了，继续搜索下一趟 
		if(now_b>m+i-k){								//如果肯定可以取消完，输出-1			
			std::cout<<-1;exit(0);
		}
		ans=std::max(b[now_b-i+k]+tb,ans);				//更新答案 
	}
	std::cout<<ans;
	return 0;
}
```


---

## 作者：expecto__patronum (赞：0)

## 思路：
很好的一道题，很考验思维。整体上来说就是二分+暴力。

但是我一开始想简单了。。。

对于每一个从 A 开始的航班，我们可以二分出离他到达时间最近的 B 航班。

这样的话，怎么分配禁止的名额就是关键了。。

对于阻止的那个人来说，肯定是禁止越早的航班越好。但是对于飞行的那个人来说，肯定是越早飞越好。那么我们就枚举第一个没有被禁止的 A 航班，二分找到符合这个 A 航班的 B 航班，将剩下的禁止名额分配给 B 航班，不断的更新最优解。


是如果剩下的禁止名单大于符合 A 条件的航班数的话，也是飞不了的。
## 代码如下：
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxx=2e5+100;
ll a[maxx],b[maxx];
int vis[maxx];
int n,m,k;
ll ta,tb;

int main()
{
	scanf("%d%d%lld%lld%d",&n,&m,&ta,&tb,&k);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),a[i]+=ta;
	for(int i=1;i<=m;i++) scanf("%lld",&b[i]);
	if(k>=n||k>=m) puts("-1");
	else
	{
		sort(b+1,b+1+m);
		ll ans=0;
		for(int i=1;i<=k+1;i++)//这里的i是枚举的没有被禁止的第一个航班。
		{
			int pos=lower_bound(b+1,b+1+m,a[i])-b;
			pos+=k-i+1;
			if(pos>=m+1)//剩下的禁止名单大于符合A条件的航班数
			{
				puts("-1");
				return 0;
			}
			ans=max(ans,b[pos]+tb);
		}
		cout<<ans;
	}
}

```
[博客](https://blog.csdn.net/starlet_kiss/article/details/102560879)

---

## 作者：zzyxl_qaq (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1148B)

### 思路简述

首先，如果 $ k \ge n $ 或者 $ k \ge m $，那么他无论如何也到不了终点，直接输出 `-1`。然后扫描前 $ k $ 个航班，二分查找他最迟能赶上的航班，如果无法到达则可以直接取消前 $ k $ 个航班，也输出 `-1`。每次扫描时记录到达时间，打擂台取最大值后输出。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,t1,t2,k;
ll a[200005],b[200005];
int main(){
    cin>>n>>m>>t1>>t2>>k;
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<m;i++)cin>>b[i];
    if(k>=n||k>=m)cout<<-1;//特判
    else{
    	ll ans=-1;
    	for(int i=0;i<=k;i++){
			ll x=a[i]+t1,y=lower_bound(b,b+m,x)-b;//二分查找
			ll pos=y+k-i;
    		if(pos>=m){cout<<-1;return 0;}
    		ans=max(ans,b[pos]+t2);//打擂台
    	}
    	cout<<ans;
    }
}
```


---

## 作者：zljhenry (赞：0)

这是一道模拟题。

思路：

- 如果 $k$ 大于 $n$ 或 $m$ 就输出 $-1$ 。
- 枚举 A 到 B 取消航班的次数 $k$，然后计算，求最大值。
- 对于每一个 $k$ ，找第一个比 A 到 B 的 $k+1$ 次航班大或相等的数。
- B 到 C 中取消的航班数为 $k-i$ 。

但是我们应该怎么快速找到 $b$ 中的这个数呢？

那就要用到 lower_bound 了！

这个函数的作用是找第一个大于等于目标值的数的地址。


比如：
```cpp
int a[5]={1,2,3,4,5};
int b[5]={5,3,4,2,1};
k=lower(a+0,a+5,b[2])-a;
//这里的 k 的值为 4
//含义是 a 数组中第一个大于或等于 b[2] 的数的下标
```
这个函数是用的二分查找，所以比较快。


这样，就可以完成题目了：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int a[200005],b[200005];
int maxx=-1;
int main(){	
	int n=read(),m=read(),ta=read(),tb=read(),k=read();
	for(int i=1;i<=n;i++){a[i]=read();a[i]+=ta;}
	for(int i=1;i<=m;i++) b[i]=read();
	if(k>=m||k>=n){
		printf("-1\n");
		return 0;
	}
	for(int i=0;i<=k;++i){
		int w=lower_bound(b+1,b+m+1,a[i+1])-b;
		int h=w+k-i;//k-i 是 B 到 C 中删除的数量
		if(h>m){
			printf("-1\n");
			return 0;
		}
		maxx=max(maxx,b[h]+tb);//取最大值
	}
	printf("%d\n",maxx);
	return 0;
}
```

---

