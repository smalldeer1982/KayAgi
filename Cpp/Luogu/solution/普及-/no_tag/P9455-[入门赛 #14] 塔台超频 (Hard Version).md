# [入门赛 #14] 塔台超频 (Hard Version)

## 题目描述

在一条笔直的马路上有 $n$ 个塔台，它们被依次标号为 $1, 2, \cdots, n$，分别处于距离马路起点 $a _ 1, a _ 2, \cdots, a _ n$（$a _ 1 < a _ 2 < \cdots < a _ n$）的位置。

每个塔台初始时有一个通讯半径 $b _ 1, b _ 2, \cdots, b _ n$，这代表，对于 $i$ 号塔台，其可以与 $[a _ i - b _ i, a _ i + b _ i]$ 范围内的塔台通讯。

需要特别注意，对于两个塔台 A、B，当且仅当 A 塔台的**位置**处在 B 塔台的通讯范围内，B 塔台才能向 A 塔台传递信号。请注意这里不是「二者的通讯范围重合，即可通讯」。

现在你可以对这些塔台进行超频。具体的，你可以指定一个电压 $k$，之后**所有**塔台都会被加上 $k$ 的电压，通讯半径都会增大 $k$。这里的 $k$ 仅可为非负整数。

现在要求你通过超频，使信号可以从 $1$ 号塔台传输到 $n$ 号塔台，路径不限（即，无论如何，只需要让信号从 $1$ 号塔台到达 $n$ 号塔台即可）。但是由于不合理的超频会较严重地磨损塔台，因此你想要尽可能降低超频的电压。

请你计算出，为了达到以上目的，塔台超频需要的最小电压是多少。

## 说明/提示

### 数据规模与约定

对于 $100\%$ 的数据，保证 $2 \leq n \leq 5 \times 10 ^ 5$，$0 \leq a _ i, b _ i \leq 10 ^ 9$。

## 样例 #1

### 输入

```
10
2 3
5 0
6 3
7 2
8 0
10 0
13 2
14 4
15 4
18 2```

### 输出

```
3```

# 题解

## 作者：EdenSky (赞：10)

# [P9455 塔台超频(hard)](https://www.luogu.com.cn/problem/P9455)
- [或许更好的阅读体验](https://www.cnblogs.com/wanguan/p/17558757.html)

写在前面：本题蒟蒻给出两种做法，一种乱搞贪心（只是目前能过，若能被 Hack 请和我说），一种正解二分。

---

## 正文 1

**最坏时间复杂度：$\mathcal{O}(n+\log V)(V=10^9)$**

这个做法是很简单的，在此不多讲。只需要二分超频电压 `mid` 即可，若当前 `mid` 可行，则令右边界缩小至 `mid`，否则令左边界扩大至 `mid`。

接下来是重要的 `check()` 函数的编写，请注意塔台之间传输的路线不限，比如塔台 1 可以直接和塔台 $n$ 通讯。也就是说对于每个塔台 $i$，我们首先要确认它向右的通讯范围是目前最大的。

代码：

```cpp
#include<iostream>
using namespace std;
const int N=5e5+7;
int n,a[N],b[N];
bool check(int x){//判定当前超频电压x的值是否可行
  int t=a[1]+b[1]+x;//起始位
  for(int i=2;i<=n;i++)
    if(t>=a[i])//若该塔台可以覆盖下一个塔台
      t=max(t,a[i]+b[i]+x);//求出更远的可以覆盖到的距离
    else return 0;//否则不可行
  return 1;
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  cin>>n;
  for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
  long long l=0,r=1e9+1,mid;
  while(l<r){//二分
    mid=(l+r)>>1;
    if(check(mid)) r=mid;
    else l=mid+1;
  }
  cout<<l;
}
```

[二分 AC 记录](https://www.luogu.com.cn/record/115920719)。

## 正文 2

**最坏时间复杂度：$\mathcal{O}(n)$**

设答案为 $x$。

我们简化一下正文 1 的思路，当塔台 $i$ 的范围被前一个炮台 $i-1$ 的范围覆盖，即 $a_{i-1}+b_{1-1}+x\geq a_i+b_i+x$，我们可以忽略塔台 $i$ 的范围，直接用塔台 $i-1$ 的参数贪心即可。

```cpp
if(a[i]+b[i]+ans>=a[i+1]+b[i+1]+ans)
  {a[i+1]=a[i],b[i+1]=b[i]; continue;}
```

接下来是贪心，对于每个塔台 $i$，只需考虑它能否覆盖到 $i+1$ 即可，若 $i$ 无法覆盖 $i+1$，则增加超频至可以覆盖到。即：若 $a_i+b_i+x<a_{i+1}$，$x=a_{i+1}-a_i-b_i$。

```cpp
if(a[i]+b[i]+ans>=a[i+1]) continue;
ans=max(ans,a[i+1]-a[i]-b[i]);
```

当然，贪心要有正确性证明。本贪心的思路就是若塔台 $i-1$ 能到达的最右范围比 $i$ 远，则忽略 $i$，且对于每个 $i$，若 $i$ 无法通讯 $i+1$，则增加超频（本段纯属废话）。

证明：

设超频 $ans$。

若 $i-1$ 范围大于 $i$，则 $i-1$ 到 $i+1$ 所需要增加的 $ans$ 一定不多于 $i$ 到 $i+1$，因此对于所有 $i$，若其范围被 $i-1$ 覆盖，则将其扔掉（忽略）。

![](https://cdn.luogu.com.cn/upload/image_hosting/4vya7ih5.png)

对于每个 $i$， $i+2$ 到 $i$ 的距离比 $i+1$ 到 $i$ 更远，因此 $i$ 到 $i+1$ 所需 $ans$ 比到 $i+2$ 少。$i$ 到 $i+2$ 有两种方式，即传输路线是否有 $i+1$。

因为存在前提：$i+1$ 所能到达的最右距离比 $i$ 远（不然 $i+1$ 会被扔掉），所以在相同的 $ans$ 情况下，经过 $i+1$ 能到更远，距离 $i+2$ 更近，所需增加的 $ans$ 更少。于是对于所有 $i$，只需计算 $i$ 到 $i+1$ 所需的 $ans$ 即可，因为这样最优。

![](https://cdn.luogu.com.cn/upload/image_hosting/rk95gxia.png)

综合一下一个乱搞的贪心就出来了。

代码：

```cpp
#include<iostream>
using namespace std;
const int N=5e5+7;
int n,ans,a[N],b[N];
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  cin>>n;
  for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
  for(int i=1;i<n;i++){
    if(a[i]+b[i]+ans>=a[i+1]+b[i+1]+ans)
      {a[i+1]=a[i],b[i+1]=b[i]; continue;}
    if(a[i]+b[i]+ans>=a[i+1]) continue;
    ans=a[i+1]-a[i]-b[i];
  }
  cout<<ans;
}
```

[贪心 AC 记录](https://www.luogu.com.cn/record/115918931)，可以看到贪心快了 0.17 秒。

---

## 作者：wangif424 (赞：6)

看上去似乎都在二分，但实际上只需要 $O(n)$ 进行一遍扫描就可以了~~不会二分做法 QAQ~~。

## 过程分析

塔台是按照位置顺序读入的，因此我们可以定义变量 $r$ 储存当前向右能传递信号的最远距离，变量 $k$ 储存施加的电压，进行一次循环遍历每个塔台。

- 如果能到达下一个塔台，即 $a_i \le r+k$，同时更新 $r \gets \max(r,a_i+b_i)$。
- 如果不能到达下一个塔台，那么必然不能到达再往后的塔台，所以需要增加电压，即 $k \gets a_i-r$，再同上更新 $r$ 的值。

## 代码附上

```cpp
#include<bits/stdc++.h>
#define R(x) x=read()
#define P(x) put(x)
#define ENDL putchar('\n');
#define SPACE putchar(' ');
#define int long long
using namespace std;
inline int read() {
	register int r=0,f=1;
	register char c=getchar();
	while(c>'9'||c<'0') {
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0') {
		r=(r<<1)+(r<<3)+c-'0';
		c=getchar();
	}
	return r*f;
}
inline void put(int x) {
	if(x<0) {
		putchar('-');
		x=-x;
	}
	if(x>9) {
		put(x/10);
		x%=10;
	}
	putchar(x+'0');
	return;
}
int n;
struct d{
	int a,b,l,r,i;
}t[500100];
int rmax;
int k;
signed main() {
	R(n);
	for(int i=1;i<=n;i++){
		t[i].i=1;
		R(t[i].a);
		R(t[i].b);
		t[i].l=t[i].a-t[i].b;
		t[i].r=t[i].a+t[i].b;
	}
	rmax=t[1].r;
	k=0;
	for(int i=2;i<=n;i++){
		if(rmax+k<t[i].a){
			k=t[i].a-rmax;
		}
		rmax=max(rmax,t[i].r);
	}
	P(k);
	return 0;
}
```

---

## 作者：MoonCake2011 (赞：5)

这道题要求符合条件的最大/最小值，可以用二分，用普通模版就可以做出来。

我们设计以下判断函数。

我们将每次能去的塔台用 $vis$ 数组标记，将每次能到的标记，慢慢延伸。

我们贪一下心，如果一个点的后面能到达，那么这个点也能到达，请自行证明。

如果其中一个电台的不能到达，那么后面的电塔也不能到达，就永远不能到达。

判断函数设计好了，接下来就是亮代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[int(5e5)+10],b[int(5e5)+10];
bool vis[int(5e5)+10];
bool p(int x){
	memset(vis,0,sizeof vis);
	int cnt=1;
	vis[1]=1;
	for(int i=1;i<=n;i++){
		if(!vis[i]) return 0;
		while(a[i]+b[i]+x>=a[cnt] && cnt<=n) vis[cnt++]=1;
		if(cnt==n+1) return 1;
	}
	return 1;
}
int main() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	int l=0,r=1e9,mid,ans;
	while(l<=r){
		if(p(mid=l+r>>1)) r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Pink_Cut_Tree (赞：5)

# P9455 [入门赛 #14] 塔台超频 (Hard Version) 题解

### 导言

题目中有一句很重要的话，那就是“为了达到以上目的，塔台超频需要的最小电压是多少”，一看到这里，立刻想**二分答案**！

### 思路

由于塔台本身已经有序，我们不许再对其进行无用的排序。

我们需要二分的是“加上的电压”。

设定一个变量 $p$，它代表的是信号现在的位置。每次经过一个塔台，它的值都会被更新为它本身与下一个塔台辐射范围的最大值。最后判断信号是否会丢失即可。

### 代码

```cpp
// C++14 (GCC 9) -O2 by Present_Coming_Time(793625)
#include<bits/stdc++.h>
using namespace std; 
int n;
struct tower{
	int place,radius;
}t[500005];
bool check(int x){
	int p=t[1].place+t[1].radius+x; //初始位置 
	for(int i=2;i<=n;i++){ //一定从2开始！ 
		if(p>=t[i].place){
			p=max(p,t[i].place+t[i].radius+x); //取最大值 
		}
		else{
			return 1; //传送不到 
		}
	}
return 0; //到达地方 
}
signed main(){
	ios::sync_with_stdio(0); //
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>t[i].place>>t[i].radius; //读入 
	}
	//以下是二分模板，一定要牢记！ 
	int l=0,r=1e9,mid,ans;
	while(l<=r){
		mid=(r-l)/2+l; //避免爆long long的小技巧 
		if(check(mid)){
			l=mid+1;
		}
		else{
			ans=mid,r=mid-1; //提前存答案 
		}
	}
	cout<<ans;
return 0;	
}
```


---

## 作者：ljy_luogu (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P9455)

## 思路
对于第 $i(i \ge 2)$ 个塔台，判断当前位置是否在之前的塔台所覆盖的最大范围之内，如果在，不用超频；否则，更新超频电压。

最后更新塔台覆盖的最大范围即可。

## 复杂度

因为更新每个塔台是 $O(1)$ 的，且共有 $n$ 个塔台，所以复杂度是 $O(n)$ 的。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n;//塔台个数
int a1, b1, a2, b2;//塔台一、塔台二
int ans;//超频电压
int maxn;//塔台所覆盖的最大范围的半径

signed main() {
	ios::sync_with_stdio(false);//cin优化
	cin >> n;
	cin >> a1 >> b1;//输入第一个塔台
	maxn = a1 + b1;//更新塔台覆盖的最大范围
	for (int i = 2; i <= n; i++) {
		cin >> a2 >> b2;
		if (maxn < a2) {//如果不在在塔台覆盖的最大范围之内，更新超频电压
			ans += (a2 - maxn);
			maxn = a2 + b2 + ans;
		}
		else {//如果在塔台覆盖的最大范围之内，不用超频
			maxn = max(maxn, a2 + b2 + ans);;
		}
		a1 = a2;
		b1 = b2;//滚动数组
	}
	cout << ans;//输出

	return 0;//结束
}
```

---

## 作者：Kedit2007 (赞：2)

## P9455 [入门赛 #14] 塔台超频 (Hard Version) 题解

首先，根据题意，我们需要让信号从 $1$ 号塔开始一路传播到最后一个塔。首先考虑如果只有相邻的塔台可以传播（即 [Easy Versoin](https://www.luogu.com.cn/problem/B3807)），我们只需要算出相邻两个塔之间至少需要加多少电压才能传播，最后取最大值即可。可参考 Easy Version 的题解。

---

那么对于 Hard Version，我们尝试将问题转化成 Easy Version。

注意到如果塔 $i$ 能将信号送达至塔 $i + 2$，那么其必定可以将信号送达至塔 $i + 1$，这提醒我们，如果要跳过塔传送信息，**那么塔 $i$ 的初始范围必定大于塔 $i + 1$**。这样，我们只需要在读入时进行预处理，如果前一个塔的范围已经大于正在被读入的塔，那么直接丢弃正在读入的塔即可。

至此，这个问题已经被转化为了 Easy Version，套用 Easy Version 的解法即可。时间复杂度 $O(n)$。

---

**参考代码，跑得很慢，可以进一步优化。**


```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main()
{
	int n;
	cin >> n;
	vector<int> a;
	vector<int> b;
	a.reserve(n), b.reserve(n);
	int maxi = 0;
	for (int i = 0; i < n; i++)
	{
		int ai, bi;
		cin >> ai >> bi;
		// 转化为 Easy Version
		// 只有在当前读入的不被前一个塔包括时 才保留这个塔
		if (a.empty() || ai + bi > a.back() + b.back())
		{
			a.push_back(ai);
			b.push_back(bi);
		}
		maxi = max(ai, maxi);
	}
	// 重新计算大小
	n = a.size();

	int ans = 0;
	
	// Easy Version 解法
	for (int i = 1; i < n; i++)	
	{
		ans = max(ans, a[i] - a[i - 1] - b[i - 1]);
	}
	
	cout << ans;
}
```

---

## 作者：_Spectator_ (赞：2)

[可能更好的食用体验](/blog/523641/P9455) $|$ 
[题目传送门](/problem/P9455) $|$ 
[我的其他题解](/blog/523641/#type=题解-New)

------------

### 思路

看到题解区基本上用的是二分答案，这里说一下我的做法。

显然，在从 $1$ 号塔台到 $n$ 号塔台的传输路径中，每一个塔台都肯定会被覆盖到。因此对于每个塔台，如果覆盖不到，就肯定要增加电压使覆盖范围变大。

设 $p$ 为当前覆盖范围最右（不是最大）的塔台的编号，$k$ 为增加的电压。那么对于每一个塔台 $i$，$a_i+b_i+k$ 即为其覆盖的最右端，$a_p+b_p+k$ 为当前所有塔台能够覆盖到的最右端，记为 $r$。  
具体实现过程可以表述如下：  
1. 对于每一个塔台 $i$，如果当前覆盖不到（`a[i]>r`），那么就增加电压使其刚好能够覆盖到（`k+=a[i]-r`）。
2. 如果塔台 $i$ 能覆盖到的最右端超过了原本能覆盖到的最右端（`a[i]+b[i]+k>r`），则更新 $p$ 的值。

------------

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+5;
long long n,k,p=1;
int a[maxn],b[maxn];
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i]>>b[i];
	for(int i=2;i<=n;i++)//i要从2开始
	{
		int r=a[p]+b[p]+k;//r为当前覆盖到的最右的位置
		if(a[i]>r)k+=a[i]-r;//如果覆盖不到，增加电压使其能够覆盖到
		if(a[i]+b[i]+k>r)p=i;//更新覆盖范围最右的编号
	}
	cout<<k;
	return 0;
}
```

---

## 作者：prt_xcdh (赞：2)

# 思路

这道一眼看过去就是一道典中典的二分答案，我们需要记录塔台之间的最大距离，并看一下 $mid$ 符不符合条件，即看一下第 $i$ 号塔台，是否处在之前塔台的覆盖范围，在则不用超频，不在则需要更新 $sum$（超频电压）。

# 代码

```c++
#include<bits/stdc++.h>
//#pragma GCC optimize(3,"Ofast","inline")
#define f(W, X, Y, Z) for(int W = X; W <= Y; W += Z)
#define F(W, X, Y, Z) for(int W = X; W >= Y; W -= Z)
typedef long long ll;
using namespace std;
int n,a[5000010],b[5000010];
bool check(int x){
	int last=0;
	for(int i=1;i<n;i++){
		last=max(a[i]+b[i]+x,last);
		if(last<a[i+1])
			return false;   
	}
	return true;
}

int main(){
	//freopen("xxx.in","r",stdin);
    //freopen("xxx.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
	}
	int l=0,r=1e9,sum=0;
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid)){
			r=mid-1;
			sum=mid;
		} 
		else l=mid+1;
	}
	cout<<sum;
	return 0;
}

```



---

## 作者：Halberd_Cease (赞：1)

二分是可做的，正确性易证，这里提供一个贪心的做法。

## 思路：贪心

答案为 $ans$ 初始为 $0$。

枚举每一个 $i$，现在能传输到的距离为 $now$，应该是它本身和 $a_i+b_i+ans$ 的最大值。

如果 $now$ 比 $a_{i+1}$ 小，即传输不到 ，那么就把 $now$ 赋值为 $a_{i+1}$，并且 $ans$ 加上原来的差值 $a_{i+1}-now$。

## 正确性证明

显然，如果前面的基站都传输不到，那么后面的基站也肯定传输不到，所以一定要满足前面的基站。

然后还有一种可能，就是前面的基站的距离特别大，而后面的特别小，这样的话我们保存的是当前前面所有基站的最远传输距离，这样子就保证了贪心的正确性。
 
最后有时间复杂度 $O(n)$，优于二分的 $O(n\log n)$。

## 核心代码

```cpp
    for(int i=1;i<n;i++)
    {
        now=max(now,a[i]+b[i]+ans);
        if(now<a[i+1])
        {
            ans+=a[i+1]-now;
            now=a[i+1];
        }
    }
```

---

## 作者：xiaoming007 (赞：1)

二分答案。

## 思路

通过敏锐的观察，题目中要求“最小电压”，且数据范围 $0 \leq a_i,b_i \leq 10^9$，此时暴力已经满足不了我们的需求，所以考虑二分答案 $k$。

二分时，令 $r = \infty$，判断 $k$ 是否合法时，注意要存储右端点所能到达的最大值，此处不存会被 hack 掉，然后判断 $a_i$ 是否能被 $a_i$ 前面的数到达。到达 $a_n$ 即为成功。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#define int long long
#define debug puts("QAQ")
namespace Syxqwq {
	inline int read() {
		register int x = 0, s = 1;
		char c = getchar();
		while (c < '0' || c > '9') {
			if (c == '-') s = -1;
			c = getchar();
		}
		while (c >= '0' && c <= '9') {
			x = (x << 1) + (x << 3) + (c ^ '0');
			c = getchar();
		}
		return x * s;
	}
	inline void Write(int x) {
		if (x < 0) {
			putchar('-');
			x = -x;
		}
		if (x > 9) Write(x / 10);
		putchar((x % 10) + '0');
	}
	inline void write(int x, char c) {
		Write(x);
		putchar(c);
	}
}
using namespace Syxqwq;
pair<int, int> a[1010101];
int n, mid, flag, vis[1010101];
bool check(int now, int mid) {
	int fars = 0;
	for (int i = 1; i < n; ++i) {
		fars = max(fars, a[i].first + a[i].second + mid);
		if (fars < a[i + 1].first) return 0;
	}
	return 1;
}
signed main() {
	n = read();
	for (int i = 1; i <= n; ++i) a[i].first = read(), a[i].second = read();
	int l = 0, r = 2e9 + 7;
	while (l < r) {
		int mid = (l + r) / 2, f1 = 0;
		int maxn = 0;
		for (int i = 1; i < n; ++i) {
			maxn = max(maxn, a[i].first + a[i].second + mid);
			if (maxn < a[i + 1].first) {
				f1 = 1;
				l = mid + 1;
				break;
			}
		}
		if (!f1) {
			r = mid;
		}
	}
	write(l, '\n');
	return 0;
}
```

---

## 作者：CSP_Sept (赞：1)

这里是 [P9455 塔台超频 (**Hard** Version)](https://www.luogu.com.cn/problem/P9455)，若需要 Easy Version 的题解请前往 [【模拟】P9455 塔台超频（easy ver）](https://www.luogu.com.cn/blog/supervise/solution-p9455-easy)。

## 题意

在 $x$ 轴有 $n$ 个塔台，标号为 $1\sim n$，分别处于距离马路起点 $a_1,a_2,\cdots,a_n$（$a_1<a_2<\cdots<a_n$）的位置。

$i$ 号塔台初始时有一个通讯半径 $b_i$，这代表其可以与**位置**在 $[a_i-b_i,a_i+b_i]$ 范围内的塔台通讯。

现在你可以指定一个 $k$（非负整数），之后所有塔台通讯半径都会增大 $k$。这称为「超频」。

现在要求通过超频，使信号可以从 $1$ 号塔台传输到 $n$ 号塔台，路径不限。请求出需要的最小的 $k$ 是多少。

$2\le n\le5\times10^5$，$0\le a_i, b_i\le10^9$。

## 题解

如果你已经通过了 Easy Version，请即刻遗忘之前的做法。

我们考虑如何针对一个 $k$ 判断是否可行。注意到 $a_i<a_{i+1}$。

具体地，维护 $i$ 号塔台之前的可通信位置区间 $[l,r]$，也即，前 $i-1$ 个塔台可以使该区间中的任意塔台都接受到信号。此时，若 $i$ 号塔台位于该区间内，则可利用其通讯区间 $[a_i-b_i,a_i+b_i]$ 尝试拓展 $[l,r]$。

若最终可以拓展至 $n$ 号塔台，则证明这个 $k$ 可行。

___

现在我们已经有了 `check(k)` 函数判断 $k$ 是否可行，要求出最小的可行的 $k$。

这个一看就很二分，确定上下界后平凡二分即可。

因为必定存在一个 $k_0$，使得对于任意 $k<k_0$ 均有 $k$ 不可行；对于任意 $k\ge k_0$ 均有 $k$ 可行。所以利用 `check` 函数是有单调性的。直接做就行了。

下界显然是 $0$。考虑答案可能的最大值，直接算出 $|a_n-a_1|-b_1$ 即可。因为若 $k$ 取此值，$1$ 号塔台可直接与 $n$ 号塔台通信（**这里要判断一下该值是否为正**）。

所以令 $l=0,r=|a_n-a_1|-b_1$ 进行二分即可。

时间复杂度 $O(n\log r)$，可以通过。

## 代码

```cpp
#include <cstdio>
#include <algorithm>

#define N 1000010
#define ll long long
using namespace std;

inline ll rd() {
	char c;
	bool flag = 0;
	while ((c = getchar()) < '0' || c > '9')
		if (c == '-')
			flag = 1;
	ll res = c - '0';
	while ((c = getchar()) >= '0' && c <= '9')
		res = (res << 3) + (res << 1) + c - '0';
	return flag ? -res : res;
}

int n;
int k = 0;

struct node{
	int a, b, c, id;
}t[N];

inline int mabs(int x) {
	return x < 0 ? -x : x;
}

int l, r;
bool check(int k){
	for(int i = 1 ; i <= n ; i++) t[i].c = t[i].b + k;
	l = t[1].a - t[1].c, r = t[1].a + t[1].c;
	for(int i = 2 ; i <= n ; i++)
		if(t[i].a >= l && t[i].a <= r){
			if(i == n) return 1;
			l = min(l, t[i].a - t[i].c);
			r = max(r, t[i].a + t[i].c);
		}
	return 0;
}

int main() {
	n = rd();
	for (int i = 1 ; i <= n ; i++)
		t[i].a = rd(), t[i].b = rd(), t[i].id = i;
	int k = mabs(t[n].a - t[1].a) - t[1].b;
	if(k <= 0){ puts("0"); return 0; }
	int s = 0, e = k;
	while(s < e){
		int mid = (s + e) >> 1;
		if(check(mid)) e = mid;
		else s = mid + 1;
	}
	printf("%d\n", s);
}
```

---

## 作者：May_Cry_ (赞：0)

根据题面说的求最小电压，显然这是一道二分。

### 思路

显然，我们二分电压的值。考虑 check  该怎么写。
1. 首先如果直接看第 $ i $ 个塔位置 $ a_i $ 加 $ b_i $ 再加上二分的 $ mid $ 是否大于等于 $ a_{ i + 1 } $ 的话显然不对，因为当从 $ i $ 可以传到 $ i + 2 $ 但 $ i + 1 $ 传不到 $ i + 2 $ 时，跳到 $ i + 1 $ 显然不优，所以过不去本题。
1. 那么考虑另一种方法，遍历 $ n $ 个塔台，记录一个 $ cnt $ 变量为当前塔台及其前面的能传输到的**最远**的塔台，通过当前塔台来更新 $ cnt $ 的值，开一个 `vs`数组纪录每个塔台是否能被传输到，当遍历到塔台   $ i $ 时，若 $ vs_i \ne  1$ 时，返回 $ 0 $。细节见代码。

### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 7;
int n ,ans;
int a[N] ,b[N] ,vs[N];
int l = 0 ,r = 1e9;
bool check(int mid){
	memset(vs ,0 ,sizeof(vs));
	vs[1] = 1;
	int cnt = 1;
	for(int i = 1;i <= n;i ++){
		if(!vs[i]) return 0;
		while(a[i] + b[i] + mid >= a[cnt] && cnt <= n){
			vs[cnt ++] = 1;
		}
		if(cnt == n + 1)return 1;
	} 
	return 1;
}
inline int read() {
	int f = 1, x = 0; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar();}
	return x * f;
}
signed main(){
	n = read();
	for (int i = 1;i <= n;i ++)a[i] = read() ,b[i] = read();
	while(l <= r){
		int mid = l + r >> 1;
		if(check(mid))ans = mid ,r = mid - 1;
		else l = mid + 1;
	}
	cout << ans;
}
```


---

## 作者：JackMerryYoung (赞：0)

# 前言

Div.3 T2，典中典之二分。

# 正文

先读题。看到题目要求最小的合法加电压，于是直接上二分答案。

考虑 check 怎么写。一个很 naive 的想法就是直接看第 $i$ 个塔的位置 $a_i$ 加上原本电压 $b_i$ 再加上我们二分的 $\operatorname{mid}$ 是否大于等于第 $i + 1$ 个塔的位置 $a_{i + 1}$。但是交上去 WA 了。

再仔细阅读题面。我们发现其实一个塔可以绕过前面的一座塔直接到达下一座塔，而且不一定劣。

于是我们记录可达的塔中最大的可达距离 $\operatorname{maxreach}$，枚举第 $i$ 座塔，如果这座塔可达则用 $a_i + b_i + \operatorname{mid}$ 去更新 $\operatorname{maxreach}$。最后返回 $\operatorname{maxreach}$ 是否大于等于第 $N$ 座塔的位置 $a_N$ 即可。复杂度 $\mathcal{O}(N \log_2 V)$ 可以通过。

# 代码

``` cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define rint register ll

ll N;
ll a[500005], b[500005];

bool check(ll mid)
{
    ll maxreach = a[1] + b[1] + mid;
    for(ll i = 2; i <= N; ++ i)
        if(maxreach >= a[i]) maxreach = max(maxreach, a[i] + b[i] + mid);

    return maxreach >= a[N];
}

signed main()
{
    cin >> N;
    for(ll i = 1; i <= N; ++ i)
        cin >> a[i] >> b[i];
    
    ll l = 0, r = 4000000000;
    ll mid;
    while(l < r)
    {
        mid = (l + r) >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }

    cout << r << endl;
    return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

一个简单二分.

基本思路：每次二分超频的距离即可，再检查此距离是否成立（信息能否传到最后），如果成立，向超频更少的方向二分，否则向超频更多的方向二分。

接下来只剩检查的函数了，这是此题最大的坑，也是这题与 [此题弱化版](https://www.luogu.com.cn/problem/B3807) 的不同点。

>现在要求你通过超频，使信号可以从 $1$ 号塔台传输到 $n$ 号塔台，路径不限。

题目中说了路径不限，说明我们可以跨过一些塔台传信息，实现也很简单，我们可以用一个变量来存储之前的塔台中能传最远的距离，遍历到某一个塔台的时候，这个变量要跟现在的距离取 $\max$ 值。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,a[5000005],b[5000005];

bool check(int x){
	int last=0;  // last 来存储之前的塔台中能传最远的距离。
	for(int i=1;i<n;i++){
		last=max(a[i]+b[i]+x,last);
		if(last<a[i+1]) return false;   //如果之前的最大值都传不到该塔，则该超频值不可以传到最后。
	}
	return true;
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
	}
	int l=0,r=1e9,ans;  //这种二分方法要用一个 ans 值来存储答案。
	while(l<=r){  //二分
		int mid=(l+r)/2;
		if(check(mid)) r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：tkdqmx (赞：0)

二分答案题。

对于每一个 $mid$ 值，从 $a_2$ 枚举到 $a_n$ 看当前点能不能接到前面的点传递的信号，若所有的点都能接到信号，则 $mid$ 是可行解，减小当前 $r$，否则增加 $l$。

初值：

$l$ 赋值成 $0$，不需要解释；

因为最远需要传递到 $a_n$，所以将 $r$ 赋值为 $a_n$。

代码如下：
~~~cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
LL n,k,a[500005],b[500005];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)   cin>>a[i]>>b[i];
    LL l=0,r=a[n];
    while(l<r){
        LL mid=(l+r)>>1,sum=1;
        bool f=0;
        for(int i=1;i<=n;i++){
            if(sum<i){
                f=1,l=mid+1;
                break;
            }
            while(a[sum+1]-a[i]<=b[i]+mid&&sum<n)  sum++;
            if(sum==n)  break;
        }
        if(!f)  r=mid;
    }
    cout<<l;
}
~~~

---

