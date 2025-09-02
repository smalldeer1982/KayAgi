# Tricky Function

## 题目描述

Iahub and Sorin are the best competitive programmers in their town. However, they can't both qualify to an important contest. The selection will be made with the help of a single problem. Blatnatalag, a friend of Iahub, managed to get hold of the problem before the contest. Because he wants to make sure Iahub will be the one qualified, he tells Iahub the following task.

You're given an (1-based) array $ a $ with $ n $ elements. Let's define function $ f(i,j) $ $ (1<=i,j<=n) $ as $ (i-j)^{2}+g(i,j)^{2} $ . Function g is calculated by the following pseudo-code:

```
int g(int i, int j) {
    int sum = 0;
    for (int k = min(i, j) + 1; k <= max(i, j); k = k + 1)
        sum = sum + a[k];
    return sum;
}
```
Find a value $ min_{i≠j}  f(i,j) $ .

Probably by now Iahub already figured out the solution to this problem. Can you?

## 样例 #1

### 输入

```
4
1 0 0 -1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
1 -1
```

### 输出

```
2
```

# 题解

## 作者：Pengzt (赞：6)

[CF429D](https://www.luogu.com.cn/problem/CF429D)

令 $sum_i$ 表示 $\sum \limits_{j=1}^{i} {a_j}$。

则 $g(i, j) = (sum_j - sum_i)$。

$f(i, j) = (i - j)^2 + g(i, j)^2 = (i - j) ^ 2 + (sum_i - sum_j) ^ 2$

所以 $f(i, j) = (i - j)^2 + (sum_i - sum_j)^2$。

$f(i, j)$ 很像**两点间距离公式**。

即求坐标为 $(i, sum_i)$ 和 $(j, sum_j)$ 两点的距离。

求 $f(i, j)$ 的最小值，就是求这 $n$ 个点中的最近点对。

因为 $n \leqslant 10^5$，朴素的 $\mathcal{O}(n^2)$ 的暴力算法肯定过不去。

于是要求 $\mathcal{O}(n \log n)$ 的时间复杂度。

我们可以使用分治进行求解。

如果不知道 $\mathcal{O}(n \log n)$ 的分治求解平面最近点对的话，
请先完成[这道题](https://www.luogu.com.cn/problem/P1429)和[这道题](https://www.luogu.com.cn/problem/P7883)。

注意：
由于点 $i$ 的纵坐标 $y_i = sum_i$，则 $y_i \in [-10^9, 10^9]$，最后的答案又是距离的平方，所以要开 long long。

[评测记录](https://www.luogu.com.cn/record/96656325)

---

## 作者：cyffff (赞：6)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF429D)

$\text{upd2021.7.23}$：修改一处笔误及不规范排版。
## 题意
给出函数 $g$：
```cpp
int g(int i, int j) {
    int sum = 0;
    for (int k = min(i, j) + 1; k <= max(i, j); k = k + 1)
    	sum = sum + a[k];
    return sum;
}
```
定义函数 $f(i,j)=(i-j)^2+g^2(i,j)$，求 $\min_{1\le i<j\le n}f(i,j)$。

$2\le n\le 10^5,|a_i|\le10^4$
## 思路
我们分析一下题目中给出的函数 $f(i,j)$（我们设 $1\leqslant i<j\leqslant n,Pre_x=\sum ^x_{i=1}a_i$），即

$$f(i,j)=(j-i)^2+(Pre_j-Pre_i)^2$$

我们发现，两个平方十分像两点间的距离，只是不用根号，于是我们就可以转化为求平面最近点对问题。

其实我们求平面最近点对并不需要一些玄学方法，我们按 $x$ 坐标排序，取 $\displaystyle\min_{i∈[1,n-s],i+1\leqslant j\leqslant i+s}f(i,j)$，再按 $y$ 坐标排序，取 $\displaystyle\min_{i∈[1,n-s],i+1\leqslant j\leqslant i+s}f(i,j)$，在这里，我们取 $s=3$。

此做法虽正确性不严谨，但是不刻意卡也不会出错，原因是如果 $x$ 坐标或者 $y$ 坐标离太远，就算 $y$ 或 $x$ 相同也不是最近的，不刻意卡是可通过的。

- [P1429 平面最近点对（加强版）](https://www.luogu.com.cn/problem/P1429)
- [P6247 最近最远点对](https://www.luogu.com.cn/problem/P6247)
- [P4423 最小三角形](https://www.luogu.com.cn/problem/P4423)

都可这么做。

时间复杂度 $O(n\log n+ns)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
	int x,y;
	friend bool operator<(const node &a,const node &b){
		return a.x<b.x;
	}
	friend long long operator-(const node &a,const node &b){
		return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
	}
}a[200001];
inline bool cmp(node a,node b){
	return a.y<b.y;
}
long long minn=1e18;
int n;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		int sss;
		scanf("%lld",&sss);
		a[i].x=i;
		a[i].y=a[i-1].y+sss;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n&&j<=i+3;j++){
			minn=min(minn,(a[i]-a[j]));
		}
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n&&j<=i+3;j++){
			minn=min(minn,(a[i]-a[j]));
		}
	}
	printf("%lld",minn);
	return 0;
}
```
再见 qwq~

---

## 作者：zhaoyp (赞：5)

# Solution

题目的难点在于转化。

------------

用 $s_i$ 表示 $a$ 序列的前缀和，将 $g(i,j)$ 化简：

$$g(i,j) = \sum\limits_{k=i+1}^ja_k = s_j - s_i$$

代回 $f(i,j)$：

$$f(i,j) = (i - j) ^ 2 + g^2(i,j) = (i - j) ^ 2 + (s_i - s_j) ^ 2$$

发现 $f(i,j)$ 是形如 $(a - b) ^ 2 + (c - d) ^ 2$ 的形式，联想到两点之间的距离。

$f(i,j)$ 相当于平面上两点 $(i,s_i)$，$(j,s_j)$ 距离的平方。

先处理一遍 $a$ 的前缀和，然后就是平面最近点对的板子了，可以使用分治等做法~~或人类智慧（详见P1429和P7883最高赞题解）。~~

下面给出分治做法代码。

# code
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int maxn = 1e5 + 5;
long long n,w[maxn];
struct node
{
	long long x,y;
}a[maxn],b[maxn];
bool cmp1(node a,node b){return a.x < b.x;}
bool cmp2(node a,node b){return a.y < b.y;}
long long dist(int i,int j){return (b[i].y - b[j].y) * (b[i].y - b[j].y) + (b[i].x - b[j].x) * (b[i].x - b[j].x);}
void input()
{
	scanf("%lld",&n);
	for(int i = 1;i <= n;i++)
		scanf("%lld",&w[i]);
	for(int i = 1;i <= n;i++)
		w[i] = w[i - 1] + w[i];
	for(int i = 1;i <= n;i++)
		a[i].x = i,a[i].y = w[i];
}
long long cdq(int l,int r)
{
	if(l == r)
		return inf;
	int mid = (l + r) >> 1;
	long long d = min(cdq(l,mid),cdq(mid + 1,r));
	int tot = 0;
	for(int i = l;i <= r;i++)
		if((a[i].x - a[mid].x) * (a[i].x - a[mid].x) <= d)
			b[++tot] = a[i];
	sort(b + 1,b + 1 + tot,cmp2);
	for(int i = 1;i <= tot;i++)
		for(int j = i + 1;j <= tot&&(b[j].y - b[i].y) * (b[j].y - b[i].y) <= d;j++)
			d = min(d,dist(i,j));
	return d;
}
int main()
{
	input();
	cout << cdq(1,n);
	return 0 ;
}
```

---

## 作者：Vermouth_1412 (赞：3)

首先，这是一道思维题。
当然我会想到最简单的暴力枚举i，j并进行函数g，复杂度自然爆炸。O（n^3）

接着，观察g函数可以发现它是可以用前缀和来维护的。然后维护一下再暴力枚举i，j，复杂度继续爆炸。O（n^2）


------------
这是一道思维题！关于题目所求可以转换为求平面最近点对(i->x,sum->y)，然后分治就好？毕竟复杂度nlogn。

那你真的是太小看CF数据了！虽然数据数量只有洛谷的一半，但是质量那是相当的高，分治被卡的妥妥飞起。



------------
其实，这是一道玄学题。
我们只需要枚举横坐标的差，然后枚举横坐标即可，然后当横坐标差的平方大于现有答案时退出循环即可。复杂度玄学……

最后……
## 学习科学，实用玄学——zhx

---

## 作者：FifthAxiom (赞：2)

## 题意
给定长度为$n$的一串序列$a_1, a_2,...,a_n$，找到两个正整数$i,j\in[1,n]$，求
$$
(i-j)^2+(\sum_{k=i+1}^{j}a_k)^2
$$
的最小值

## 分析
将原式中的$\sum_{k=i+1}^{j}a_k$用前缀和$S_j-S_i$替代，则原式变换为
$$
(i-j)^2+(S_j-S_i)^2
$$
不难看出变换后的式子为两点之间欧几里德距离的平方，于是原题转化为求平面上的最近点对距离的平方。

关于最近点对距离的求解可使用二分法，具体可见[~~题解~~](https://www.luogu.org/problemnew/solution/P1429)

说了这么多，我们来看看代码吧！

```cpp
#include <cstdio>
#include <algorithm>

#define re register
#define ll long long

struct Point {
	ll x, y;
};

Point v[100010], temp[100010];
int n;

/*bool comp(Point a, Point b) {
	return a.x == b.x ? a.y < b.y : a.x < b.x;
}*/

bool cmp(const Point& a, const Point& b){
     return a.y < b.y;
}

ll dist(Point a, Point b) {//距离
	return (ll)(a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

ll solve (const int l, const int r) {//求平面最近点对
	if (l == r) return 0x3fffffff;
	if (l + 1 == r) return dist(v[l], v[r]);
	int mid = (l + r) >> 1;
	ll d1 = solve(l, mid), d2 = solve(mid + 1, r);
	ll d = std::min(d1, d2);
	int k = 0; 
	for (re int i = l; i <= r; ++i)
		if ((v[mid].x - v[i].x) * (v[mid].x - v[i].x) <= d) temp[k++] = v[i];
	std::sort(temp, temp + k, cmp);
	for (re int i = 0; i < k; ++i)
		for (re int j = i + 1; j < k; ++j) {
			if ((temp[i].y - temp[j].y) * (temp[i].y - temp[j].y) > d) break;
			d = std::min(d, dist(temp[i], temp[j]));
		}
	return d;
}

int main() {
	scanf("%d", &n);
	for (re int i = 1; i <= n; ++i) {
		int a;
		scanf("%d", &a);
		v[i].y = v[i - 1].y + a;
		v[i].x = i;
	}
	//std::sort(v + 1, v + n + 1, comp);
	ll minn = solve(1, n);
	printf("%lld\n", minn);
	return 0;
}
```
关于上面那位神仙说的分治法会TLE，可以通过一些~~玄学~~优化搞过去，具体详见程序

---

