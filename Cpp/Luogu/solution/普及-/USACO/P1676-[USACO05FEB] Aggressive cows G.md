# [USACO05FEB] Aggressive cows G

## 题目描述

农夫约翰建造了一座有 $n$ 间牛舍的小屋，牛舍排在一条直线上，第 $i$ 间牛舍在 $x_i$ 的位置，但是约翰的 $m$ 头牛对小屋很不满意，因此经常互相攻击。约翰为了防止牛之间互相伤害，因此决定把每头牛都放在离其它牛尽可能远的牛舍。也就是要最大化最近的两头牛之间的距离。

牛们并不喜欢这种布局，而且几头牛放在一个隔间里，它们就要发生争斗。为了不让牛互相伤害。约翰决定自己给牛分配隔间，使任意两头牛之间的最小距离尽可能的大，那么，这个最大的最小距离是多少呢？

## 说明/提示

【样例解析】把牛放在 $1$，$4$，$8$ 这三个位置，距离是 $3$。容易证明最小距离已经最大。

【数据范围】对于 $100\%$ 的数据，$2 \le n \le 10^5$，$0 \le x_i \le 10^9$，$2 \le m \le n$。不保证 $x$ 数组单调递增。


## 样例 #1

### 输入

```
5 3
1 2 8 4 9```

### 输出

```
3```

# 题解

## 作者：Pink_Cut_Tree (赞：22)

### 思路

看到“最大的最小距离值”这几个字，“**二分答案**”四个字立刻浮现在我脑海中。

### 二分答案概念

二分答案的核心是：存在一个分界线（即答案 $ans$），大于 $ans$ 时没有合法答案；小于等于 $ans$ 时，一定存在答案。求 $ans$ 的过程。

### 核心

通过阅读题目，大致可以感受到一种贪心算法：从最左端开始，每隔一个单位距离 $x$ 就安置一头牛，一定是**能安置就安置**，可以证明安置了就一定比不安置更优，最后统计安置了几头牛即可。

### 代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,m;
int pl[100005]; //pl是place的缩写
void init(){
	ios::sync_with_stdio(false); //读入数据较多，关闭读写同步以加快读写速度
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>pl[i];
	}
	sort(pl+1,pl+n+1); //对奶牛的需求排序
} 
bool check(int x){
	int num=1,lasth=1; //上一次放牛的房子编号
	for(int i=2;i<=n;i++){
		if(pl[i]-lasth>=x){ //可以放牛 
			lasth=pl[i];
			num++;
		}
	} 
	return num>=m; //返回值的压行技巧
}
int main(){
	init();
    //接下来是二分答案的模板
	int l=1,r=1e9,ans,mid;
	while(l<=r){
		mid=(r-l)/2+l; //防止爆long long的小技巧
		if(check(mid)){
			ans=mid; //暂时存答案
        	l=mid+1;
		}
		else{
			r=mid-1;
		}
	}
	cout<<ans;
return 0;
} 
```

### 题外话

双倍经验：[P1824 进击的奶牛](https://www.luogu.com.cn/problem/P1824)

此外，《深入浅出》这本书对 P1824 也有深入的讲解，大家可以买来看。

---

## 作者：Ggsddu_zzy (赞：12)

[题目传送门](https://www.luogu.com.cn/problem/P1676)

[更好的阅读体验](https://www.cnblogs.com/zzyblog0619/p/17389205.html)

#### 解题思路

最大值最小化问题，考虑**二分答案**。

首先要排序，保证序列单调不降，然后求出两个隔间之间的距离。

```c++
sort(a+1,a+1+n);
for(ri i=1;i<=n;i++)
	dis[i]=a[i+1]-a[i];
```

二分出一个 $mid$，判断它是否合法：每次累加距离，如果距离和比 $mid$ 大，说明当前可以分配牛，记录数量；再把距离和归零，方便下次计算。最后比较可以分配牛的数量与牛的数量，如果前者大于等于后者，则说明当前 $mid$ 合法。

```c++
int check(int mid){
	int sum=0,cnt=1;
	for(ri i=1;i<=n;i++){
		sum+=dis[i];
		if(sum>=mid){
			sum=0;
			cnt++;
		}
		if(cnt>=m)return 1;
	}
	return 0;
}
```

如果当前 $mid$ 合法，求出最大的 $mid$，左端点变为 $mid+1$，否则右端点变为 $mid-1$，进一步缩小范围。

```c++
int l=1,r=1e9;
while(l<=r) {
	int mid=l+r>>1;
	if(check(mid)){
		ans=max(ans,mid);
		l=mid+1;
	}
	else r=mid-1;
}
```

---

## 作者：eggegg185 (赞：4)

注意到题目要求**最小值最大**，所以我们首先考虑二分答案。

首先注意到 $x$ 数组不递增，为了我们更方便地求牛舍间的距离，我们将 $x$ 数组排序。

我们直接二分最小距离 $q$。注意到我们要尽可能的放下更多的牛舍，所以我们将第一个牛安排在第一个牛舍。注意到要满足要求，所以下一个牛舍至少在 $x$ 个距离外。统计一下最多能放多少个牛舍，如果能让所有 $m$ 个牛入住，那说明答案符合要求。

实现时我们可以记录上一个入住的牛舍的位置，然后遍历排好序的数组 $x$，如果目前牛舍与上一个入住牛舍的距离大于等于 $x$，说明这个牛舍可以入住，更新入住牛舍的数量。如果到最后 $m$ 个牛都能入住那么就是合法答案，记录答案且更新 $l$ 让 $q$ 更大，否则就不记录答案且更新 $r$ 让 $q$ 更小。具体实现可以看代码。

代码：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int x[114514],n,m;
bool check(int q) {
	int can = 1;
	int plc = x[1];
	for(int i = 2; i <= n; i++) {
		if(x[i]-plc >= q) plc = x[i],can++;
	}
	return (can >= m);
}
int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> x[i];
	}
	sort(x+1,x+1+n);
	int l = 0,r = 1e9+7,ans;
	while(l <= r) {
		int mid = (l+r)>>1;
		if(check(mid)) ans = mid,l = mid+1;
		else r = mid-1;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：yzm0325 (赞：4)

这种主题库里的题竟然能写题解……我来写一写吧！

首先，看到“最小距离尽可能的大”这句话，这不是二分吗？

我们证明一下这个问题的单调性：令“条件”表示可以把 $m$ 头牛全部安置进隔间使得相邻两头牛距离不超过 $x$。很容易看出：$x$ 越小，越可能全部安置下；当 $x$ 比较大时，就可能做不到了。于是不难想到存在一个分界线 $ans$，当 $x>ans$ 时“条件”一定不成立（即没有合法方案），$x \leq ans$ 时“条件”一定成立（即有合法方案）。完全可以二分解决。

我们二分答案 $mid$，现在的问题是如何检验“条件”的正确性。可以想到一种贪心算法：枚举所有牛棚，判断和上次安置的距离一旦超过 $x$ 就安置并更新上次安置位置，直到牛棚遍历完，看看最多安置的数量是否大于等于牛数 $m$ 就可以了。再判断一下如果现在的距离 $mid$ 安置的下 $m$ 头牛就更新答案 $ans$ 并尝试让 $mid$ 大一点（即局限在右区间），否则就让 $mid$ 小一点（局限在左区间）。

最后输出 $ans$ 即可。

代码不放了，讲的比较详细了。

---

## 作者：Sirkey (赞：4)

没有题解？我捷足先登！

我的思路是朴实无华的二分加贪心。

先讲二分：有二分的方法找一个答案，保证这个答案合理，比较的时候用 `ans=max(ans,mid);` 来更新答案。

定义一个左端点和右端点，合理移动左端点，不合理就移动有段点。

再谈贪心：要想放的最多，那么第一个点必须要放。后面的点，用一个新的变量记录。记录和上一个的距离，当距离比二分枚举到的答案大了，就立马放，把次数加加，而且把答案改为一。最后比较是否可以放下 $m$ 个。

最后直接输出答案。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
#define pb push_back
//
//
//
using namespace std;
ll n,m,a[100005],len[100005],ans;
inline ll read() {
	ll f=0,t=0;
	char c=getchar();
	while(!isdigit(c)) t|=(c=='-'),c=getchar();
	while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
	return t?-f:f;
}
inline void out(ll x) {
	if(x<0) putchar('-');
	if(x>9) out(x/10);
	putchar('0'+x%10);
}
bool check(ll x) {
	ll t=0,time=1;
	FOR(i,1,n-1) {
		t+=len[i];
		if(t>=x) t=0,time++;
	}
//	cout<<time<<" "; 
	if(time>=m) return 1;
	else return 0;
}
int main() {
	n=read(),m=read();
	FOR(i,1,n) a[i]=read();
	sort(a+1,a+n+1);
	FOR(i,2,n) len[i-1]=a[i]-a[i-1];
	ll l=1,r=1e9;
	while(l<=r) {
		ll mid=(l+r)/2;
		if(check(mid)) ans=max(ans,mid),l=mid+1;
		else r=mid-1;
	}
	out(ans);
	return 0;
}



```

——end——
 

---

## 作者：SilverLi (赞：3)

[Aggressive cows G の 传送门](https://www.luogu.com.cn/problem/P1676)

看到题目。

> 最大的最小距离值。

考虑**二分**，二分这个最小距离值 $x$。

先算出两个隔间之间的距离 $a$。

然后依次遍历每一个 $a_i$，每次用一个 $t$ 加上 $a_i$，如果 $t$ 大于 $x$，就让 $t=0$ 并让计数器 `cnt+1`。

然后如果 $cnt>m$ 就证明这个值 $x$ 取得到，则更新 $l$，反之更新 $r$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,l[N],a[N];
inline bool check(int x) {
	int t=0,cnt=1;
	for(int i=1;i<n;++i) {
		t+=a[i];
		if(t>=x)	t=0,++cnt;
		if(cnt>=m)	return true;
	}
	return 0;
}
signed main() {
	cin>>n>>m;
	for(int i=1;i<=n;++i)   cin>>l[i];
	sort(l+1,l+n+1);
	for(int i=2;i<=n;++i)	a[i-1]=l[i]-l[i-1];
	int l=1,r=1e9;
	while(l<r-1) {
		int mid=l+r>>1;
		if(check(mid))  l=mid;
		else    r=mid;
	}
	cout<<l;
	return 0;
}
```

---

## 作者：dby_718 (赞：2)

本题是一道很好的二分答案题。

当我们读题看到“最大的最小距离”这句话是，就应该想到二分答案。

二分答案，就是指存在一个分界 $ans$，大于 $ans$ 时没有合法的答案，而小于或等于 $ans$ 时有合法的答案，我们要求出 $ans$ 的值。

具体的看代码吧。

```cpp
#include<cstdio>
#include<algorithm>
#define MAXN 100005
using namespace std; 
int n, c, a[MAXN];
bool check(int dis)//判断是否合法
{
	int res = 1, pre = 1;
	for(int i = 2; i <= n; i++)
		if(a[i] - a[pre] >= dis)
			res++, pre = i;
	return res >= c;
}
int main()
{
	scanf("%d%d", &n, &c);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);//输入
	sort(a + 1, a + n + 1);//排序
	int l = 0, r = 1000000000, m;//以下为二分模板
	while(l < r)
	{
		m = (l + r + 1) >> 1;
		if(check(m))
			l = m;
		else
			r = m - 1;
	}
	printf("%d", l);
	return 0;
}
```


[双倍经验。](https://www.luogu.com.cn/problem/P1824)

---

## 作者：Vct14 (赞：2)

**中心思路：由于题目要使任意两头牛之间的最小距离尽可能的大，求最大值，所以考虑二分答案。**

因为不保证 $a$ 数组单调递增，所以输入后先进行排序，随后就可以算出每个牛舍之间的距离 $l_i$ 了。

```c++
for(long long i=1; i<=n; i++) cin>>a[i];
sort(a+1,a+n+1);
for(long long i=2; i<=n; i++) l[i-1]=a[i]-a[i-1];
```

然后开始二分最大距离。设当前二分的答案为 $x$。

那么，只有当与前一个放了牛的牛舍之间的距离大于 $x$ 时，再放这一个牛舍，最后才可以更新答案。

我们可以使用变量 $k$ 表示当前与上一个牛舍之间的距离，$s$ 表示当前放的牛数量。由于要使最小距离最大，所以第 $1$ 个牛舍必须放一头牛，则 $s$ 初始值为 $1$。

然后依次枚举 $l_i$。每次让 $k\gets k+l_i$，当 $k\ge x$ 时，即此牛舍与前一个放了牛的牛舍之间的距离大于 $x$，则在此牛舍放一头牛，然后使 $k=0$，$s\gets s+1$，然后判断是否放了 $m$ 头牛即可。

```c++
bool check(int x){
	long long k=0,s=1;
	for(long long i=1; i<n; i++) {
		k+=l[i];
		if(t>=x){
			k=0;
			s++;
		}
		if(s==m) return true;
	}
	return false;
}
```

如果能放，即答案比 $x$ 更大，则更新 $l$，使 $x$ 更大，否则更新 $r$。

```c++
while(l<=r){
	long long mid=(l+r)/2;
	if(check(mid)) l=mid;
	else r=mid-1;
}
```

---

## 作者：_Above_the_clouds_ (赞：1)

# 思路：
这题二分答案。二分的是最大的最小距离值，因为不保证数组单调性，所以先排序，二分范围是 $1$ $\sim$ $10^9$，每次二分设 $mid=\dfrac{l+r}{2}$，用 $check$ 函数，从 $1$ 枚举到 $n-1$，$sum$ 记录每两个小屋间的距离之和，用 $cnt$ 记录放了几只牛。如果 $sum$ 大于等于 $mid$，那么在小屋 $i$ 放一只牛，$cnt$ 也要加一，然后 $sum$ 归零，再判断 $cnt$ 如果大于等于 $m$，说明 $mid$ 成立，返回 `true`，如果到最后也不成立就返回 `false`。如果 $check$ 成立，记录答案，再向上寻找最优解；否则向下枚举。
# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
int x[100005];
bool check(int k){//检查mid是否成立
	long long sum=0,cnt=1;//距离 计数
	for(int i=1;i<n;i++){
		sum+=x[i+1]-x[i];
		if(sum>=k) sum=0,cnt++;//距离归零，牛只数加一
		if(cnt>=m) return 1;//mid成立
	}
	return 0;//不成立
}
void solve(int l,int r){
	int mid=(l+r)/2;
	if(l>r) return ;
	if(check(mid)) ans=max(ans,mid),solve(mid+1,r);//记录答案，向上查找
	else solve(l,mid-1);//向下查找
} 
int main(){
	cin>>n>>m;//输入
	for(int i=1;i<=n;i++) cin>>x[i];
	sort(x+1,x+n+1);//排序
	solve(1,1e9);//二分
	cout<<ans;//输出
	return 0;
}
```

---

