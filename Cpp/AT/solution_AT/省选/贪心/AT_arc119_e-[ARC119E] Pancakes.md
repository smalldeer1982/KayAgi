# [ARC119E] Pancakes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc119/tasks/arc119_e

$ N $ 枚のパンケーキが積み重なった「パンケーキタワー」があります。最初、上から $ i $ 番目 $ (1\ \leq\ i\ \leq\ N) $ のパンケーキの大きさは $ A_i $ です。シェフである高橋君は、このパンケーキタワーに対して次の操作を最大 $ 1 $ 回行うことができます。

- 整数 $ l,\ r $ $ (1\ \leq\ l\ \lt\ r\ \leq\ N) $ を選び、上から $ l,\ l+1,\ \dots,\ r $ 番目のパンケーキの並び方を反転させる。

ここで、**見栄えの悪さ**を次のように定義するとき、操作後の見栄えの悪さとして考えられる最小の値を求めてください。

> 隣り合うパンケーキの大きさの差の総和。  
>  すなわち、上から $ i $ 番目のパンケーキの大きさを $ A^{\prime}_i $ とするときの、$ |A^{\prime}_1\ -\ A^{\prime}_2|\ +\ |A^{\prime}_2\ -\ A^{\prime}_3|\ +\ \cdots\ +\ |A^{\prime}_{N-1}\ -\ A^{\prime}_N| $ の値。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 300000 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

$ l\ =\ 2,\ r\ =\ 5 $ を選んで操作をすると、操作後のパンケーキの大きさは上から順に $ 7,\ 6,\ 2,\ 12,\ 14 $ となります。 このときの見栄えの悪さは $ |7-6|\ +\ |6-2|\ +\ |2-12|\ +\ |12-14|\ =\ 1\ +\ 4\ +\ 10\ +\ 2\ =\ 17 $ です。これが最小値となり、他のどんな方法を使ってもこれより見栄えの悪さを小さくすることはできません。

### Sample Explanation 2

この入力例では、操作をしないことで見栄えの悪さを最小にすることができます。 このとき、パンケーキの大きさは上から順に $ 111,\ 119,\ 999 $ となり、見栄えの悪さは $ |111-119|\ +\ |119-999|\ =\ 8\ +\ 880\ =\ 888 $ となります。

### Sample Explanation 3

$ l\ =\ 3,\ r\ =\ 5 $ を選んで操作をすると、操作後のパンケーキの大きさは上から順に $ 12,\ 15,\ 15,\ 4,\ 3,\ 7 $ となります。 このときの見栄えの悪さは $ |12-15|\ +\ |15-15|\ +\ |15-4|\ +\ |4-3|\ +\ |3-7|\ =\ 3\ +\ 0\ +\ 11\ +\ 1\ +\ 4\ =\ 19 $ で、これが最小値となります。

### Sample Explanation 4

$ l\ =\ 2,\ r\ =\ 4 $ を選んで操作をすると、操作後のパンケーキの大きさは上から順に $ 100,\ 400,\ 500,\ 800,\ 900,\ 300,\ 700 $ となり、このときの見栄えの悪さは $ 1800 $ となります。

## 样例 #1

### 输入

```
5
7 14 12 2 6```

### 输出

```
17```

## 样例 #2

### 输入

```
3
111 119 999```

### 输出

```
888```

## 样例 #3

### 输入

```
6
12 15 3 4 15 7```

### 输出

```
19```

## 样例 #4

### 输入

```
7
100 800 500 400 900 300 700```

### 输出

```
1800```

## 样例 #5

### 输入

```
10
535907999 716568837 128214817 851750025 584243029 933841386 159109756 502477913 784673597 603329725```

### 输出

```
2576376600```

# 题解

## 作者：Felix72 (赞：5)

被反转的区间中，只有两端真正被影响了，其余的贡献不变。

因此，此题本质是说给若干二元组，可选择两个二元组，交换其中一个的第一项和另一个的第二项，最小化每个二元组元素差之和。

考虑二元组元素差的几何意义，即数轴上的线段长度。我们发现两个二元组表示的线段如果方向一致且相交，那么交换之后相当于去掉了相交部分。那么此题就变成了求线段最大相交。针对两个方向的线段，我们计算两次即可。

```
#include <bits/stdc++.h>
#define lowbit(x) (x & (-x))
#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)
using namespace std;
const int N = 300010;
long long n, a[N], org, ans, cnt, minn = 2e9, maxn = -2e9;
struct node
{
	long long st, en;
	bool operator < (const node &w) const {return st < w.st;}
}b[N];
inline void work()
{
	b[cnt + 1].st = b[cnt + 1].en = 0;
	sort(b + 1, b + cnt + 1);
	long long bj = -1, num = 0;
	for(int i = 1; i <= cnt; ++i)
	{
		num = max(num, min(bj, b[i].en) - b[i].st);
		bj = max(bj, b[i].en);
	}
	ans = min(ans, org - num * 2);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> a[i], minn = min(minn, a[i]), maxn = max(maxn, a[i]);
	for(int i = 1; i < n; ++i) org += abs(a[i + 1] - a[i]);
	ans = org;
	for(int i = 1; i < n; ++i) ans = min(ans, org - abs(a[i] - a[i + 1]) + abs(a[1] - a[i + 1]));
	for(int i = n; i > 1; --i) ans = min(ans, org - abs(a[i] - a[i - 1]) + abs(a[n] - a[i - 1]));
	cnt = 0;
	for(int i = 1; i < n; ++i) if(a[i] <= a[i + 1]) b[++cnt].st = a[i], b[cnt].en = a[i + 1];
	work();
	cnt = 0;
	for(int i = n; i > 1; --i) if(a[i] <= a[i - 1]) b[++cnt].st = a[i], b[cnt].en = a[i - 1];
	work();
	cout << ans << endl;
	return 0;
}

```

---

## 作者：EuphoricStar (赞：2)

感觉挺典的，~~为啥有 2500 啊（~~

观察发现，反转序列对 $\sum\limits_{i=1}^{n-1} |a'_i - a'_{i+1}|$ 影响不大。具体而言，设反转了 $a_l \sim a_r$，记 $s = \sum\limits_{i=1}^{n-1} |a_i - a_{i+1}|$，那么 $s' = s - |a_{l-1} - a_l| - |a_r - a_{r+1}| + |a_l - a_{r+1}| + |a_{l-1} - a_r|$（特判 $l = 1 \lor r = n$）。

则现在就是要找到一组 $(l,r), 2 \le l \le r < n$，使得 $s'$ 最小。对后两项拆绝对值之后化成三维偏序的形式，因此跑四遍 cdq 即可。

时间复杂度 $O(n \log^2 n)$。cdq 内使用归并排序、树状数组，可以通过。

[code](https://atcoder.jp/contests/arc119/submissions/41098176)

---

## 作者：TLE_AK (赞：1)

### 题意
给定一个序列 $A$ 现在你可以反转一个区间 $[l,r]$，求反转后每两个相邻的绝对值之差的和最小值。
## 思路
首先发现反转后改变的仅有 $|A_l-A_{l－1}|$ 与 $|A_r-A_{r+1}|$，也就是说只要考虑 $l,r$ 即可。

注意到绝对值很烦人，考虑处理绝对值的差转化为数轴上对应线段（下图是一种情况）。  

![](https://cdn.luogu.com.cn/upload/image_hosting/yn3mab5c.png)

于是我们就把问题变为了：交换 $A_l,A_r$ 让两条线段总长度变小，讨论什么情况下会使代价变小(这里容易证明有对称性，所以假定 $l<r$）：

- 首先容易证明，$l,r$ 要么分别为最大最小，要么均不为最大最小，否则必定有一条线段交换后覆盖了另一条线段。这样减少了大部分分讨！

![](https://cdn.luogu.com.cn/upload/image_hosting/b3u7ityg.png)

- 其次也可以证明出两条线段**必须相交**。因为我们去掉的一定是一个相交部分。

![](https://cdn.luogu.com.cn/upload/image_hosting/7jvmqaf6.png)

所以我们得出了只有这两种情况（紫色为相交部分）：

![](https://cdn.luogu.com.cn/upload/image_hosting/og4078q7.png)

惊喜的发现两条线段代表下标偏序关系一样，求两遍最大线段交即可。

## 代码
注意边界讨论。
```
#include<bits/stdc++.h>
using namespace std;
#define int long long

namespace acac
{
	struct node
	{
		int l,r;
	}line[600010],line2[600010];
	
	bool cmp(node a,node b)
	{
		if(a.l==b.l)return a.r<b.r;
		return a.l<b.l;
	}

//最大交
	int sovle(node line[],int n)
	{
		sort(line+1,line+1+n,cmp);
		int maxr=line[1].r,ans=0;
		for(int i=2;i<=n;i++)
		{
		//	cout<<line[i].l<<' '<<line[i].r<<endl;
			ans=max(ans,min(line[i].r,maxr)-line[i].l);
			maxr=max(line[i].r,maxr);
		}
		return ans;
	}

	int A[300010];

	int main()
	{
		int n,ans=0,len=0,len2=0,sum=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&A[i]);
			ans+=abs(A[i]-A[i-1])*(i!=1);
		}
  //计算不反转贡献
		sum=ans;
		for(int i=1;i<n;i++)
		{
//讨论于1,n翻转
			if(i>1)ans=min(ans,sum-abs(A[i]-A[i+1])+abs(A[1]-A[i+1]));
			if(i>1)ans=min(ans,sum-abs(A[i]-A[i-1])+abs(A[n]-A[i-1]));
			if(A[i]<A[i+1])line[++len]={A[i],A[i+1]};
			else line2[++len2]={A[i+1],A[i]};
			
		}
	//	cout<<ans<<endl;
		ans=min(ans,sum-max(sovle(line,len),sovle(line2,len2))*2);
		cout<<ans;
		return 0;
	}
}
#undef int
int main()
{
	acac::main();
	return 0;
}
```

---

## 作者：SnowTrace (赞：0)

首先你考虑一次操作就是把 $|a-b|+|c-d|$ 变成了 $|a-c|+|b-d|$。

把这些东西放到数轴上有很好的性质。

答案会变小当且仅当 $a<b,c<d$，或者 $a>b,c>d$，且 $[a,b]$ 和 $[c,d]$ 两个区间有交。

答案减少的部分就是两个区间的交乘上 2.

然后这个问题转化成了一个给定若干条线段求其最大交的问题。

这个问题很棘手。

你如果暴力去做是二维偏序，而且有很多个不等号，你还要写一个离散化然后处理。

一种简便方法是，我们不妨枚举左端点较大的那个区间。

设这个区间是 $[l,r]$。

然后就考虑左端点在 $l$ 前面的所有区间，你发现这时答案和较小的左端点具体在哪里根本没关系。

你只需要在前面找到一个右端点最大的然后和区间 $[l,r]$ 求交即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1000000005;
int n;
int a[500005];
int ans,res,sum;
struct node{
	int l,r;
};
bool operator<(const node& a,const node& b){return a.l<b.l;}
vector<node>p;
void solve(){
	sort(p.begin(),p.end());
	res = 0;int mx = 0;
	for(auto x:p){
		res = max(res,min(mx,x.r)-x.l);
		mx = max(mx,x.r);
	}
	ans = min(ans,sum-res*2);
} 
signed main(){
	cin >> n;for(int i = 1;i<=n;i++)cin >> a[i];
	for(int i = 2;i<=n;i++)sum+=abs(a[i]-a[i-1]);
	ans = sum;
	for(int i = 1;i<n;i++)ans = min(ans,sum-abs(a[i]-a[i+1])+abs(a[1]-a[i+1]));
	for(int i = 2;i<=n;i++)ans = min(ans,sum-abs(a[i]-a[i-1])+abs(a[n]-a[i-1]));
	for(int i = 1;i<n;i++)if(a[i]<a[i+1])p.push_back((node){a[i],a[i+1]});
	solve();p.clear();
	for(int i = 1;i<n;i++)if(a[i]>a[i+1])p.push_back((node){a[i+1],a[i]});
	solve();
	cout << ans << endl; 
}
```

---

