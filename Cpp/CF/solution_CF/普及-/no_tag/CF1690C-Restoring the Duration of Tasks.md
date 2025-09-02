# Restoring the Duration of Tasks

## 题目描述

Recently, Polycarp completed $ n $ successive tasks.

For each completed task, the time $ s_i $ is known when it was given, no two tasks were given at the same time. Also given is the time $ f_i $ when the task was completed. For each task, there is an unknown value $ d_i $ ( $ d_i>0 $ ) — duration of task execution.

It is known that the tasks were completed in the order in which they came. Polycarp performed the tasks as follows:

- As soon as the very first task came, Polycarp immediately began to carry it out.
- If a new task arrived before Polycarp finished the previous one, he put the new task at the end of the queue.
- When Polycarp finished executing the next task and the queue was not empty, he immediately took a new task from the head of the queue (if the queue is empty — he just waited for the next task).

Find $ d_i $ (duration) of each task.

### 题目翻译

Polycarp（以下称为Pc）得到了 $n\ (1\le n\le2\times 10^5)$ 个任务。

每个任务有两个属性 $s_i$ 和 $f_i$，分别表示这个任务开始和结束的时间。

Pc在任务开始时间没到的时候什么都不会做，时间一到就会立马开始。

在任务期间，下一个任务来了Pc会把这个任务加到任务列表的末尾。

当处理完一个任务后，如果任务列表还有任务时，会立马处理第一个任务。

当处理完一个任务后，如果任务列表没有任务了，Pc什么都不会做直到下一个任务来临。

处理每个任务的时间就是原文中的 $d_i$。

测试数据个数 $t\ (1\le t\le 10^4)$。

**输入：**

第一行，$t$。

对于每一个测试数据：

第一行一个任务数 $n$，

第二行 $n$ 个正整数，表示 $s_1<s_2<s_2<...<s_n\ (0\le s_i\le 10^9)$，

第三行 $n$ 个正整数，表示 $f_1<f_2<f_3<...<f_n\ (s_i<f_i\le 10^9)$。

**输出：**

对于每一个测试数据，一行 $n$ 个正整数，表示 $d_i$。

## 说明/提示

First test case:

The queue is empty at the beginning: $ [ ] $ . And that's where the first task comes in. At time $ 2 $ , Polycarp finishes doing the first task, so the duration of the first task is $ 2 $ . The queue is empty so Polycarp is just waiting.

At time $ 3 $ , the second task arrives. And at time $ 7 $ , the third task arrives, and now the queue looks like this: $ [7] $ .

At the time $ 10 $ , Polycarp finishes doing the second task, as a result, the duration of the second task is $ 7 $ .

And at time $ 10 $ , Polycarp immediately starts doing the third task and finishes at time $ 11 $ . As a result, the duration of the third task is $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1690C/d2350660c42c220190947ba223600b0328cd0bf5.png)An example of the first test case.

## 样例 #1

### 输入

```
4
3
0 3 7
2 10 11
2
10 15
11 16
9
12 16 90 195 1456 1569 3001 5237 19275
13 199 200 260 9100 10000 10914 91066 5735533
1
0
1000000000```

### 输出

```
2 7 1 
1 1 
1 183 1 60 7644 900 914 80152 5644467 
1000000000```

# 题解

## 作者：柳下惠 (赞：4)

[题目链接](https://www.luogu.com.cn/problem/CF1690C)。


一个感性的理解，因为题目求的是连续的长度，那把它们当做线段来看，显然第一条线段的贡献就是它自身的长度减一。对于其它线段，我们只需要判断当前线段是否和上一条线段有交集，如果无交集那么该线段的贡献也是它自身的长度减一，否则就为该线段的终点减去上一条线段的终点（因为这两条线段一定是连续的）。

### code

```cpp
	t=read();
	while(t--)
	{
		n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		for(int i=1;i<=n;i++) b[i]=read(); 
		cout<<b[1]-a[1]<<" ";
		for(int i=2;i<=n;i++)
		{
			if(a[i]>=a[i-1]&&a[i]<=b[i-1]) cout<<b[i]-b[i-1]<<" ";//判断两条线段是否相交
			else cout<<b[i]-a[i]<<" ";
		}
		return puts(""),0;
	}

```

---

## 作者：mouseboy (赞：1)

## 主要题意：
> 有 $n$ 个任务，必须在 $s_i$ 到 $t_i$ 之间完成，求每个任务最大可以完成多久（优先前面的最大）。
## 思路
> 就拿一个变量记录当前时间，然后贪心选择 $a[i].t$ 和 $ a[i + 1].t$ 中的最小值，（应为至少也要给下一个任务留 $1$ 的时间），最后做减法，输出即可。
## 代码
> ```cpp
> #include <bits/stdc++.h>
> using namespace std;
> 
> const int Maxn = 2e5 + 5;
> 
> struct node
> {
>     int s, t;
> } a[Maxn];
> 
> int n, t, ti;
> 
> int main()
> {
>     ios::sync_with_stdio(0);//其实不用快读
>     cin.tie(), cout.tie();//关同步流即可
>     cin >> t;
>     while (t--)
>     {
>         cin >> n;
>         for (int i = 1; i <= n; i++)
>         {
>             cin >> a[i].s;
>         }
>         for (int i = 1; i <= n; i++)
>         {
>             cin >> a[i].t;
>         }
>         a[n + 1].s = a[n + 1].t = INT_MAX;//将最后一个赋值为最大
>         ti = a[1].s;//记录时间
>         for (int i = 1; i <= n; i++)
>         {
>             cout << min(a[i].t, a[i + 1].t) - ti << " ";
>             ti = max(min(a[i].t, a[i + 1].t - 1), a[i + 1].s);//注意减一
>         }
>         cout << "\n";
>     }
>     return 0;//华丽的结束
> }
```

---

## 作者：BFSDFS123 (赞：1)

比较简单的一道模拟题。

----

遍历每一个事情，记录一个**当前时间**。

如果当前时间比当前第一个没有做的开始时间小，则将当前时间变为开始做的时间，否则直接考虑做这件事。

我们只需将当前时间加上这件事所需要做的长度，存储完成时间，再遍历下一个事情即可。

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define LL_inf 1145141919810
//#define int long long
#define ull unsigned long long
#define ll long long
using namespace std;
#define int long long
const int Maxn=2e5+10;
int n;
int s[Maxn],t[Maxn];
int d[Maxn]; 
signed main()
{
	int T;
	scanf("%lld",&T);
	while(T--)
	{
		int ntime=0;
		int pos=1;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++) scanf("%lld",&s[i]);
		for(int i=1;i<=n;i++) scanf("%lld",&t[i]);
		for(int i=1;i<=n;i++)
		{
			if(ntime<s[i]) ntime=s[i];
			d[i]=t[i]-ntime;
			ntime=t[i];
		}
		for(int i=1;i<=n;i++)
		{
			printf("%lld ",d[i]);
		}
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：lrmlrm_ (赞：0)

## 题意

有 $n$ 个任务，每个任务在 $s_i$ 时开始，$f_i$ 时结束。只有完成了上一个任务才可以做下一个任务。问每个任务分别做了多久。

## 思路

既然要完成第 $i-1$ 个任务才能做第 $i$ 个任务，那么不难理解为第 $i$ 个任务的起始时间要在本来的 $s_i$ 和第 $i-1$ 个任务的结束时间 $f_{i-1}$ 中选一个最大的，也就是 $\max(s_i,f_{i-1})$。那有了起始时间，再来想结束时间。不难想到，题目中并没有让结束时间收到任何的限制，也就是结束时间直接用原来的 $f_i$ 就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,t1,t2;
int s[200010],f[200010];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&s[i]);
		for(int i=1;i<=n;i++)scanf("%d",&f[i]);
		s[n+1]=2147483647,f[n+1]=2147483647,t2=s[1];
		for(int i=1;i<=n;i++)
			s[i]=max(f[i-1],s[i]);
		for(int i=1;i<=n;i++)
			printf("%d ",max(f[i]-s[i],0));
		printf("\n");
	}
	return 0;
}
```

---

## 作者：qinshi0308 (赞：0)

首先，这道题的翻译有点让人迷惑。所以，我准备了[题目简述](https://www.luogu.com.cn/paste/rxkn10an)。

## 1. 思路：
我们不难发现，对于第 $i$ 个任务，它实际处理的用的时间是这个任务的结束时间减去这个任务的开始时间和上一个任务的结束时间中较大的一个，就是这个任务的实际处理时间。如果思路看着有点晕，那么可以结合代码理解。

## 2. 代码：
```cpp
# include <bits/stdc++.h>
using namespace std;
int arr[200010];
int brr[200010];
int main(){
	int t;
	cin>>t;
	for(int i=0;i<t;i++){
		int n;
		cin>>n;
		for(int j=0;j<n;j++){
			cin>>arr[j];
		}
		for(int j=0;j<n;j++){
			cin>>brr[j];
		}
		cout<<brr[0]-arr[0]<<" ";//由于第一个任务前面不存在任务，所以特殊处理一下（不这样数组就会越界）。如果数组下标是从1开始的话就不需要这一步。
		for(int j=1;j<n;j++){
			cout<<brr[j]-max(brr[j-1],arr[j])<<" ";
/*这个任务的结束时间减去这个任务的开始时间和上一个任务的结束时间中较大的一个，就是这个任务的实际处理时间。*/
		}
		cout<<endl;
		fill(arr,arr+n,0);//多组数据记得清空数组！
		fill(brr,brr+n,0);//同上
	} 
	return 0;
}

```

---

## 作者：hanzhixian (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1690C)

## 思路：
由于任务都是一个一个做的，一个任务的结尾只会影响下一个任务的开头，所以，对每一个任务，我们只用考虑它的上一个任务：

1. 当上一个任务与当前的任务没有交集时：$d[i]=f[i]-s[i]$。
2. 当上一个任务与当前的任务有交集时：$d[i]=f[i]-f[i-1]$。

综上，$d[i]=f[i]-\max(f[i-1],s[i])$。

剩下的照题意模拟就行啦。

下面献上我奇丑无比的代码。
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int t,n,ans;
struct node{//l，r分别是题目中的s和f
	int l,r;
}a[200010];
inline int read(){//快读
	int w=0,s=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')
			s=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		w=(w<<1)+(w<<3)+(c^48);
		c=getchar();
	}
	return w*s;
}
inline void write(int x){//快写
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
}
signed main(){
	t=read();
	while(t--){
		n=read();
		ans=0;
		for(int i=1;i<=n;i++)//读入
			a[i].l=read();
		for(int i=1;i<=n;i++)
			a[i].r=read();
		for(int i=1;i<=n;i++)//根据刚才的柿子求出d[i]并输出
			printf("%d ",a[i].r-max(a[i-1].r,a[i].l));
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Sternenlicht (赞：0)

思路：模拟。

Polycarp 做任务有两种方式：

1. 与上一个任务无交集，从头干到尾，所需时间为 $f_i-s_i$。

2. 与上一个任务有交集，则从上一个任务的结束时间干到当前任务的结束时间，所需时间为 $f_i-f_{i-1}$。

取两者中的最小值即可。

```cpp
#include <bits/stdc++.h>
namespace IO{
	#define LL long long
	inline LL read(){
		LL x=0,f=1;char c=getchar();
		for (;!isdigit(c);c=getchar())if (c=='-')f=-1;
		for (;isdigit(c);c=getchar())x=(x<<3)+(x<<1)+(c^48);
		return x*f;
	}
	inline void write(LL x,char c='\n'){
		if (x){
			if (x<0)x=-x,putchar('-');
			char a[30];short l;
			for (l=0;x;x/=10)a[l++]=x%10^48;
			for (l--;l>=0;l--)putchar(a[l]);
		}else putchar('0');putchar(c);
	}
}using namespace IO;
using namespace std;

const int N = 2e5+10;
int s[N],f[N],ans[N];
int main(){
	int T=read();
	while (T--){
		int n=read();
		for (int i=1;i<=n;i++)s[i]=read();
		for (int i=1;i<=n;i++)f[i]=read();
		for (int i=1;i<=n;i++)write(min(f[i]-s[i],f[i]-f[i-1]),' ');
		puts("");
	}
	return 0;
}
```

---

## 作者：donk_666 (赞：0)

题解开始于一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/y3ea7ram.png)

很明显，有两种线段：

1. 独立的，开始时间不受上一个活动影响。如这里的 $1$ 号和 $6$ 号，他们的 $d_i$ 就是 $f_i-s_i$。

1. 与其他有交集的，实际开始时间不为 $s_i$ 的。如这里的 $2$，$3$，$4$，$5$ 号，他们的 $d_i$ 是 $f_i-s_{i-1}$。

所以做法就是从 $1$ $\sim$ $n$ 扫一遍，记录上一个活动的结束时间，从而判断属于哪种线段，分类处理。

代码
```
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[200005],b[200005];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(long long i=1;i<=n;i++){
			cin>>a[i];
		}
		for(long long i=1;i<=n;i++){
			cin>>b[i];
		}
		long long st=a[1];
		for(long long i=1;i<=n;i++){
			cout<<b[i]-st<<" ";
			st=max(b[i],a[i+1]);
		}
		cout<<endl;
	}
}
```

---

## 作者：user470883 (赞：0)

## 思路：
根据观察题目样例，我们可以发现 Polycarp 做任务的时间主要是来源于两个方面的。

1. “本身的时间”，也就是从头开始，一直干到结束，这样要的时间就是 $f[i]-s[i]$。

2. “接上来的时间”，也就是在此次任务开始的时候，Polycarp 正在同时做另一个任务，这样要的时间就是 $f[i]-f[i-1]$。

分类讨论完毕。由于题目问您最少要多长时间，那我们就将两种方式的时间比一下，选其中较小的那个即可。

## AC CODE:
```
#include<bits/stdc++.h>
#define yangzd_have_npy long long
#define INF 2000000000
#define jerrlee int
#define CZY signed
#define piggy123 return 0;
using namespace std;

int s[200005],f[200005];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;
		for(int i = 0 ; i < n ; i++)
		{
			cin >> s[i];
		}
		for(int i = 0 ; i < n ; i++)
		{
			cin >> f[i];
		}
		cout << f[0]-s[0] << " ";
		for(int i = 1 ; i < n ; i++)
		{
			int ans=min((f[i]-s[i]),(f[i]-f[i-1]));
			cout << ans << " ";
		}
		cout << endl;
	}
	return 0;
}

```


---

## 作者：LOVE_Ynoi (赞：0)

### 解题思路：
运用一种递推思想。  

对于给定的 $s,f$，当我们处理到 $s_i,f_i$ 时，我们有两种方法：  
由于任务只能一个一个做，所以我们断定，答案只与前一位有关。

如果这个任务的开始时间在前一个任务的结束时间之后，即 $s_i\ge f_{i-1}$，   
那么答案就是开始时间与结束时间的差 $f_i-s_i$。

如果这个任务的开始时间在前一个任务的结束时间之前，即 $s_i<f_{i-1}$，   
那么答案就是等待前一个结束后直接开始，即 $f_i-f_{i-1}$

时间复杂度 $O(n)$
### 代码
```c++
#include<bits/stdc++.h>
using namespace std;
int a[200010];
int b[200010];
int ans[200010];
int n;
void solve(){
    cin>>n;
    for(int i = 1;i<=n;i++) cin>>a[i];
    for(int i = 1;i<=n;i++) cin>>b[i];
    ans[1] = b[1]-a[1];
    for(int i = 2;i<=n;i++){
        if(a[i]>=b[i-1]) ans[i] = b[i]-a[i];
        else ans[i] = b[i]-b[i-1];
    }
    for(int i = 1;i<=n;i++) cout<<ans[i]<<" ";
    cout<<endl;
}
int main(){
    int _ = 1;
    cin>>_;
    while (_--){
        solve();
    }
    return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

# 题目分析

注意到题目中保证 $s,f$ 均严格单调递增。所以对于当前一个任务 $i$，他可能的完成时间为 $f[i]-s[i]$，但我们发现 $s[i]\lt f[i-1]$ 时，完成时间不是 $f[i]-s[i]$，而是 $f[i]-f[i-1]$。

综上，每个答案为 $f[i]-\max\{s[i],f[i-1]\}$。

# 代码

```cpp
// Problem: C. Restoring the Duration of Tasks
// Contest: Codeforces - Codeforces Round #797 (Div. 3)
// URL: https://codeforces.com/contest/1690/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Date:2022-06-07 23:01
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <cmath>
#include <queue>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	inline int read() {
		int ret = 0,f = 0;char ch = getchar();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getchar();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getchar();
		}
		return f ? -ret : ret;
	}
	inline double double_read() {
		long long ret = 0,w = 1,aft = 0,dot = 0,num = 0;
		char ch = getchar();
		while (!isdigit(ch)) {
			if (ch == '-') w = -1;
			ch = getchar();
		}
		while (isdigit(ch) || ch == '.') {
			if (ch == '.') {
				dot = 1;
			} else if (dot == 0) {
				ret = (ret << 3) + (ret << 1) + ch - 48;
			} else {
				aft = (aft << 3) + (aft << 1) + ch - '0';
				num ++;
			}
			ch = getchar();
		}
		return (pow(0.1,num) * aft + ret) * w;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 2e5 + 5;
int st[N],ed[N];
int T,n;
inline void solve() {
	n = read();
	for (register int i = 1;i <= n; ++ i) st[i] = read();
	for (register int i = 1;i <= n; ++ i) ed[i] = read();
	for (register int i = 1;i <= n; ++ i) {
		printf("%d ",ed[i] - std::max(st[i],ed[i - 1]));
	}
	puts("");
}
int main(void) {
	T = read();
	while (T --) {
		solve();
	}
	
	return 0;
}
```

---

