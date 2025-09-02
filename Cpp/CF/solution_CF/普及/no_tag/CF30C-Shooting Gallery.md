# Shooting Gallery

## 题目描述

One warm and sunny day king Copa decided to visit the shooting gallery, located at the Central Park, and try to win the main prize — big pink plush panda. The king is not good at shooting, so he invited you to help him.

The shooting gallery is an infinite vertical plane with Cartesian coordinate system on it. The targets are points on this plane. Each target is described by it's coordinates $ x_{i} $ , and $ y_{i} $ , by the time of it's appearance $ t_{i} $ and by the number $ p_{i} $ , which gives the probability that Copa hits this target if he aims at it.

A target appears and disappears instantly, so Copa can hit the target only if at the moment $ t_{i} $ his gun sight aimed at $ (x_{i},y_{i}) $ . Speed of movement of the gun sight on the plane is equal to 1. Copa knows all the information about the targets beforehand (remember, he is a king!). He wants to play in the optimal way, which maximizes the expected value of the amount of hit targets. He can aim at any target at the moment 0.

## 样例 #1

### 输入

```
1
0 0 0 0.5
```

### 输出

```
0.5000000000
```

## 样例 #2

### 输入

```
2
0 0 0 0.6
5 0 5 0.7
```

### 输出

```
1.3000000000
```

# 题解

## 作者：jdsb (赞：3)

## 题意
- 平面上有 $n$ 个点，第 $i$ 个点的坐标为 $(x_i,y_i)$，出现时间为 $t_i$，之后就消失，出现时有 $p_i$ 的概率能选中它。求最多能选中的点的期望值。
- $1\le n \le 10^3$

## 分析
首先我们肯定是要按照出现时间来选择每个点，所以将所有点按照出现时间从小到大排序。

设 $f_i$ 表示处理完前 $i$ 个点，且必选第 $i$ 个点的最大期望，则转移方程为 $f_i=max\{f[j]\}+p_i$，每个点都可以由之前的所有点转移过来，转移条件就为 $dis_{i,j}\le (t_i-t_j)$。

最后答案即为 $max\{f_i\}$，因为每个点都可能为最后选的点。总的时间复杂度为 $O(n^2)$，可以通过此题。

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^'0'),c=getchar();
	return x*f;
}
const int N=1e3+5;
struct node{
	int x,y,t;
	double p;
	friend int operator<(const node x,const node y) { return x.t<y.t; }
}a[N];
int n;
double f[N],ans;
inline int check(int x,int y)
{
	ll dis=1ll*(a[x].x-a[y].x)*(a[x].x-a[y].x)+1ll*(a[x].y-a[y].y)*(a[x].y-a[y].y);
	ll tim=1ll*(a[x].t-a[y].t)*(a[x].t-a[y].t);
	return dis<=tim;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		int x=read(),y=read(),t=read();
		double p;
		scanf("%lf",&p);
		a[i]={x,y,t,p};
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<i;j++) if(check(i,j)) f[i]=max(f[i],f[j]);
		f[i]+=a[i].p;
		ans=max(ans,f[i]);
	}
	printf("%.10lf\n",ans);
	return 0;
}
```


---

## 作者：tZEROちゃん (赞：1)

简单题。

这个期望就是用来忽悠你用的，实际上做这个题并不需要用到期望的知识。

然后你对这 $n$ 个点排序，考虑 dp。

设 $dp_i$ 表示考虑到第 $i$ 个点，其中第 $i$ 个点必选的最大期望值。

显然，我们枚举 $j(1\le j<i)$，然后判断 $i$ 能不能由 $j$ 转移过来。至于具体怎么判断，大概是这样（其实本质就是按照题意模拟）：

```cpp
auto dis = [&](int x, int y) {
  return (a[x].x - a[y].x) * (a[x].x - a[y].x) + (a[x].y - a[y].y) * (a[x].y - a[y].y);
};
auto ti = [&](int x, int y) {
  return (a[x].t - a[y].t) * (a[x].t - a[y].t);
};
auto ck = [&](int x, int y) {
  if (dis(x, y) <= ti(x, y)) return 1;
  return 0;
};
```

状态转移方程是 $dp_i=\max\{dp_j\}+p_i$。

代码：[226297800](https://codeforces.com/contest/30/submission/226297800)。

---

## 作者：TTpandaS (赞：0)

击中第 $i$ 的靶子的期望为：

$$ 0 \times (1-p_i)+1 \times p_i=p_i $$

根据期望的可加性，答案为我们选择的靶子的期望之和。

所以对答案的唯一限制就是时间，我们需要根据时间选择靶子。

将 $t_i$ 排序，然后根据时间先后选择靶子。$dp_i$ 表示最后一个选择靶子 $i$ 的最大期望，转移为：

$$ dp_i=\max_{j=1 \land t_i-t_j \leq dis(i,j)}^{i-1}dp_j +p_i $$

答案为 $\max_{i=1}^{n} dp_i$。

---

## 作者：wangyibo201026 (赞：0)

## 前言

还有 $114514$ 天就要 CSP 了，刷刷 dp 题，涨涨 RP。

## 题意

~~很简单就不说了。~~

## 思路

由于肯定是按照时间顺序来打目标，所以按照时间排个序。

~~按照线性 dp 的老套路~~，我们可以设 $f_i$ 为前 $i$ 个目标最多打中的期望。

那么会有一个问题，在转移的时候，由于没有最后一个目标是什么，我们无法确定移枪口的时间。

哦，那么我们设 $f_{i,j}$ 为前 $i$ 个目标以第 $j$ 个结尾。可是可以，但是没必要，~~根据经验~~我们可以设 $f_i$ 为前 $i$ 个目标以 $i$ 结尾，最后全扫一遍就可以了。

状态转移方程是~~显然~~的：

$$f_i = \max\{f_j + p, f_i\}(j < i)$$

## 代码

代码：

```cpp
#include<bits/stdc++.h>

#define int long long
#define endl '\n'

using namespace std;

const int N = 1005;

int n;
double ans, f[N];

struct Node{
  int x, y, t;
  double p;
}a[N];

bool cmp(Node x, Node y){
  return x.t < y.t;
}

signed main(){
  cin >> n;
  for(int i = 1; i <= n; i++){
    cin >> a[i].x >> a[i].y >> a[i].t >> a[i].p;
  }
  sort(a + 1, a + 1 + n, cmp);
  for(int i = 1; i <= n; i++){
    for(int j = 1; j < i; j++){
      if((a[i].x - a[j].x) * (a[i].x - a[j].x) + (a[i].y - a[j].y) * (a[i].y - a[j].y) <= (a[i].t - a[j].t) * (a[i].t - a[j].t)){
        f[i] = max(f[i], f[j]);
      }
    }
    f[i] += a[i].p;
  }
  for(int i = 1; i <= n; i++){
    ans = max(ans, f[i]);
  }
  cout << fixed << setprecision(10) << ans;
  return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路：

~~您就叫蓝题啊。~~

考虑 DP。

首先将发现，每一个点的价值数值上等于这个点打中的概率。由于每一个点打中的价值为 $1$ ，这个结论可以用全期望公式简单推导。

然后将所有的点按照出现的时间排序，用 $f_i$ 表示考虑到第 $i$ 个点，当前这一个点必须取所能取到的最大价值。

其中对于每一个点，如果想要取到另一个点的价值，那么就需要在一定的时间范围内移动到另一个点的位置。显然移动的距离小于两者之间的时间差就能在时间允许的范围内移动到另一个点，从而取到那个点的价值。

转移的方程为：$f_i=max(f_j|[\text{ j 是能在规定时间内到 i 的点}])+p_i$。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct str{
	long long x,y,t;
	double p;
	bool operator <(const str a)const {
		return t<a.t;
	}
}num[1005];
long long n;
double ans,f[1005];
bool dis(int i,int j){
	if((num[i].x-num[j].x)*(num[i].x-num[j].x)
	+(num[i].y-num[j].y)*(num[i].y-num[j].y)
	<=(num[i].t-num[j].t)*(num[i].t-num[j].t))
	return 1;
	return 0;
}
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	scanf("%lld%lld%lld%lf",&num[i].x,&num[i].y,&num[i].t,&num[i].p);
	sort(num+1,num+n+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++)
		if(dis(i,j)){
			f[i]=max(f[i],f[j]);
		}
		f[i]+=num[i].p;
 		ans=max(ans,f[i]);
	}
	printf("%.8lf",ans);
	return 0;
}
```


---

