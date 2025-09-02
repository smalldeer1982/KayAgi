# 「RdOI R3」race

## 题目描述

某足球赛事上，A 国队和 B 国队共进行了 $n$ 场比赛。比赛采用积分赛制，胜者队伍得 $a$ 分，败者队伍得 $b$ 分，若打平则双方各得 $c$ 分。现已知 A 国队总进球数 $d$ 球，B 国队总进球数 $e$ 球，求 A 国队的最大可能得分和最小可能得分。

## 说明/提示

### 样例解释

为便于理解样例，现给出前三组数据的样例解释：

| 数据编号 | 最大得分方案                    | 最小得分方案                    |
| -------- | ------------------------------- | ------------------------------- |
| $1$      | $(1,0),(0,0),(2,1),(0,0),(2,1)$ | $(0,0),(5,0),(0,1),(0,0),(0,1)$ |
| $2$      | $(0,0),(0,5),(0,0),(0,0),(0,0)$ | $(0,1),(0,1),(0,1),(0,1),(0,1)$ |
| $3$      | $(3,2),(0,2),(3,2)$             | $(6,6),(0,0),(0,0)$             |

表格中的 $(x_1,y_1),(x_2,y_2),\cdots,(x_n,y_n)$ 表示第 $1$ 场比分为 $x_1:y_1$，第 $2$ 场比分为 $x_2:y_2$，以此类推。

---

### 数据范围

**本题采用捆绑测试。**

对于所有数据，$1\le T\le 10^5$，$1\le n \le 10^9$
，$0\le d,e\le10^9$，$0\le b\le c \le a\le10^9$。

| subtask | 分值 | 特殊限制             | subtask 依赖 |
| ------- | ---- | -------------------- | ------------ |
| $1$     | $10$ | $e=0$                | 无           |
| $2$     | $20$ | $n,d,e\le 5,T\le100$ | 无           |
| $3$     | $20$ | $n\le 5$             | $2$          |
| $4$     | $50$ | 无                   | $1,3$        |



## 样例 #1

### 输入

```
5
5 3 0 2 5 2
5 5 2 3 0 5
3 100 1 2 6 6
5 9 0 2 3 9
4 5 0 5 1 3```

### 输出

```
13 7
14 10
201 6
29 0
15 5```

# 题解

## 作者：yzy1 (赞：14)

由于题目中规定 $b\le c\le a$，我们可以得出一个性质：最大得分策略 A 输的场数不大于 $1$。对于这个性质，这里有一个简单的证明：

若 A 输的场数为 $k(k>1)$​​，这几局中 A 与 B 的比分分别为 $(a_1,b_1),(a_2,b_2),\cdots,(a_k,b_k)$。我们可以将这些同为输的场次合并为一场，即 $(a_1+a_2+\cdots+a_k,b_1+b_2+\cdots+b_k)$。而剩下的 $k-1$ 场为零比零平局。由于题目保证 $b\le c$，所以合并后的得分一定不劣于原得分。

同理，我们可以推出第二个性质：最小得分策略 A 赢的场数不大于 $1$，证明和上一个性质类似，这里不过多讲述。

我们可以采用贪心思想来解决这个问题。

- 对于最大得分，枚举「输 $0$ 场」和「输 $1$ 场」，剩下的场尽可能的赢，实在不行就平局。结果取两种方案最大值。
- 对于最小得分，枚举「赢 $0$ 场」和「赢 $1$ 场」，剩下的场尽可能的输，实在不行就平局。结果取两种方案最小值。

```cpp
ll mx = -1, mn = 1e18;
if (d >= e) up(mx, min(n, d - e) * a + (n - min(n, d - e)) * c);
up(mx, min(n - 1, d) * a + (e ? b : c) + (n - 1 - min(n - 1, d)) * c);
if (e >= d) down(mn, min(n, e - d) * b + (n - min(n, e - d)) * c);
down(mn, min(n - 1, e) * b + (d ? a : c) + (n - 1 - min(n - 1, e)) * c);
```

---

## 作者：MY（一名蒟蒻） (赞：6)

[P7821 「RdOI R3」race](https://www.luogu.com.cn/problem/P7821)

考场上做出来这题以为能弄点比赛分的，没想到 unrated 了。

还是记录下做法。

考虑最朴素的贪心。最大化得分，则赢得越多越好；最小化得分，则输得越多越好。

很容易写出这样的代码。

```cpp
int t,n,a,b,c,d,e;
ll ans1,ans2;
scanf("%d",&t);
while(t--)
{
	scanf("%d%d%d%d%d%d",&n,&a,&b,&c,&d,&e);
	if(d >= n-1) ans1=1ll*(n-1)*a+(d-n+1 > e? a:(d-n+1 == e)? c:b);
	else ans1=1ll*d*a+1ll*(n-d-1)*c+b; 
	if(e >= n-1) ans2=1ll*(n-1)*b+(e-n+1 > d? b:(e-n+1 == d)? c:a); 
	else ans2=1ll*e*b+1ll*(n-e-1)*c+a;
	printf("%lld %lld\n",ans1,ans2);
}
```

变量都是字面意思。

但是过不去样例中的第一个和第三个测试数据。

观察发现我们的贪心策略中最后一场有可能并不是我们想要的结果，也就是说我们需要用平局来换掉这一场的不如意。

注释很无聊，如果仔细思考过代码是不难看懂的。

```cpp
int t,n,a,b,c,d,e;
ll ans1,ans2;
scanf("%d",&t);
while(t--)
{
	scanf("%d%d%d%d%d%d",&n,&a,&b,&c,&d,&e);
	if(d >= n-1)
	{
		ans1=1ll*(n-1)*a+(d-n+1 > e? a:(d-n+1 == e)? c:b);
		if(d-n+1 < e && d >= e) ans1=max(ans1,c+1ll*min(d-e,n-1)*a+(d-e < n-1? 1ll*(n-1-d+e)*c:0));
	}
	else
	{
		ans1=1ll*d*a+1ll*(n-d-1)*c+b;
		if(e <= d) ans1=max(ans1,1ll*e*c+1ll*(d-e)*a+1ll*(n-d)*c);
	}
	if(e >= n-1)
	{
		ans2=1ll*(n-1)*b+(e-n+1 > d? b:(e-n+1 == d)? c:a);
		if(e-n+1 < d && e >= d) ans2=min(ans2,c+1ll*min(e-d,n-1)*b+(e-d < n-1? 1ll*(n-1-e+d)*c:0));
	}
	else
	{
		ans2=1ll*e*b+1ll*(n-e-1)*c+a;
		if(d <= e) ans2=min(ans2,1ll*d*c+1ll*(e-d)*b+1ll*(n-e)*c);
	}
	printf("%lld %lld\n",ans1,ans2);
}
```

**_Thank you for your reading !_**

---

## 作者：信息向阳花木 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P7821)

相信大家题目都读过了。~~蒟蒻的我没有参加比赛。~~

然而，~~这道题应该没这么简单（不至于橙）~~，个人认为应该黄。

其实就是很简单的贪心题，对于得分，一定满足以下两点性质

* 最小得分就是输的尽可能多
* 最大得分就是赢的尽可能多

知道以上两点，我们得出算法：贪心

> 尽可能让最小得分输的多，最大得分赢得多，真不行就平局处理。

因为本蒟蒻很懒，所以用了三目运算符，这里简单说明用法：

> 表达式?成立时执行的表达式:不成立时的表达式

核心代码
```cpp
cin>>n>>a>>b>>c>>d>>e;
if(d>n) ans1=1ll*(n-1)*a+(d-n+1>e?a:(d-n+1==e)?c:b);
else ans1=1ll*d*a+1ll*(n-d-1)*c+b; 
if(e>=n-1) ans2=1ll*(n-1)*b+(e-n+1>d?b:(e-n+1==d)?c:a); 
else ans2=1ll*e*b+1ll*(n-e-1)*c+a;
```


---

## 作者：EnofTaiPeople (赞：2)

这是一道很好的入门题，考察知识点如下：
1. 选择结构程序设计；
2. 循环结构程序设计。

需要我们分类讨论，步骤如下：

定义一些让我们更方便的东西，用 $\_$ 表示 $0ll$、用 ll 表示 long long，代码如下：
```cpp
typedef long long ll;
const ll _=0;
```
读入数据、定义变量存储答案，代码如下：
```cpp
scanf("%lld%lld%lld%lld%lld%lld",&n,&a,&c,&b,&d,&e);
	long long smal,bmax,f=d-e;
```
考虑 $f=d-e$ 的正负，需要用到 if 和 else。
分成三类：$f>0$、$f=0$ 和 $f<0$。

若 $f>0$ 即 $d>e$ 考虑 A 国队必胜一场，最坏情况是本场 $d:0$ 接下来，最多败 $\min(n-1,e)$ 场，如还有剩，只能是平局。再考虑最优策略，有两种方案:
1. 先输一场，$0:e$，接下来赢 $\min(d,n-1)$ 场，剩下的平局；
2. 先赢 $\min(f,n)$ 场，剩下的平。

代码如下：
```cpp
if(f>0){
	smal=a+c*min(n-1,e)+b*max(_,n-1-e);
	bmax=max(c+a*min(n-1,d)+b*max(n-1-d,_),a*min(f,n)+b*max(_,n-f));
}
```
若 $f=0$ 即 $d=e$ 有一种基本策略，全部打平。然后最优策略与最坏情况各有一种:
1. 先输一场，$0:e$，接下来赢 $\min(d,n-1)$ 场，剩下打平；

2. 先赢一场，$d:0$，接下来输 $\min(e,n-1)$ 场，剩下打平。

代码如下：
```cpp
else if(f==0){
	smal=min(a+c*min(n-1,e)+b*max(_,n-1-e),b*n);
	bmax=max(c+a*min(n-1,d)+b*max(n-1-d,_),b*n);
	}
```
若 $f<0$ 即 $d<e$ 考虑必输一场，容易得到最优策略为，先输一场，$0:e$，接下来赢 $\min(d,n-1)$ 场，剩下打平。最坏情况有两种可能：
1. 先赢一场，$d:0$，接下来输 $\min(n-1,e)$ 场，剩下打平。
2. 先输 $\min(n,-f)$ 场，剩下打平。

代码如下：
```cpp
else if(f<0){
	smal=min(a+c*min(n-1,e)+b*max(_,n-1-e),c*min(-f,n)+b*max(_,n+f));
	bmax=c+a*min(n-1,d)+b*max(n-1-d,_);
	}
```

综上所述，考场 AC 代码如下：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll _=0;
ll n,a,b,c,d,e,T;
inline void Solve(){
	scanf("%lld%lld%lld%lld%lld%lld",&n,&a,&c,&b,&d,&e);
	long long smal,bmax,f=d-e;
	if(f>0){
		smal=a+c*min(n-1,e)+b*max(_,n-1-e);
		bmax=max(c+a*min(n-1,d)+b*max(n-1-d,_),a*min(f,n)+b*max(_,n-f));
	}else if(f==0){
		smal=min(a+c*min(n-1,e)+b*max(_,n-1-e),b*n);
		bmax=max(c+a*min(n-1,d)+b*max(n-1-d,_),b*n);
	}else if(f<0){
		smal=min(a+c*min(n-1,e)+b*max(_,n-1-e),c*min(-f,n)+b*max(_,n+f));
		bmax=c+a*min(n-1,d)+b*max(n-1-d,_);
	}
	printf("%lld %lld\n",bmax,smal);
}
int main(){
	scanf("%lld",&T);
	while(T--)Solve();
}
```

---

## 作者：Nygglatho (赞：1)

分类讨论。

先考虑求最大值，可以分为四种情况：

第一种是 $d \ge (e + N)$。这样子，每一场比赛都可以比对方多**至少**一分，所以最好方法肯定是全赢，分数为 $a \times N$。

第二种是 $d > e$ 且 $d < (e + N)$，这样子，我们有两种方案，一是**输一场**（输的这场比分是 $0 : e$）之后尽量以 $1 : 0$ 来比，如果不够就后面 $0 : 0$ 打平，如果多余就加在**任意**一场上。二是不输，前面几场与对手只多 $1$ 分，之后不够了就打平，多了就加在任意一场上，取最大值即可。

第三种是 $d = e$。这样子，也有两种方法，一是**全部平局**，得分为 $c \times N$，第二种是输一场之后尽量比对方多一分（即 $1 : 0$），如果进球数不够则 $0 : 0$ 打平。也取最大值即可。

第四种就是 $d < e$，这样子如果打平了后面也必定要输，那么可以直接先**输一场**，之后就可以每一次 $1 : 0$ 打赢，进球数不够仍 $0 : 0$ 打平。

最小分数同理。

```cpp
#include <stdio.h>
#define int long long
int max(int x, int y) {return x > y ? x : y;}
int min(int x, int y) {return x < y ? x : y;}

int n, a, b, c, d, e;

int get_max() {
	int ans = 0;
	if (d >= (e + n)) ans = a * n;
	else if (d > e) {
		if (d >= n) {
			ans = max((a * (n - 1) + b), (a * (d - e) + c * (n - (d - e))));//输一场，剩下尽可能赢和不输，每一次都打赢，后面平。
		} else {
			ans = max((a * d + b + c * (n - d - 1)), (a * (d - e) + c * (n - (d - e))));
		}
	} else if (d == e) {
		if (d >= n) {
			ans = max((a * (n - 1) + b), c * n);
		} else {
			ans = max((a * d + b + c * (n - d - 1)), c * n);
		}
	} else {
		if (d >= n) {
			ans = a * (n - 1) + b;
		} else {
			ans = a * d + b + c * (n - d - 1);
		}
	}
	return ans;
}

int get_min() {
	int ans = 0;
	if (e >= (d + n)) ans = b * n;
	else if (e > d) {
		if (e >= n) {
			ans = min((b * (n - 1) + a), (b * (e - d) + c * (n - (e - d))));
		} else {
			ans = min((b * e + a + c * (n - e - 1)), (b * (e - d) + c * (n - (e - d))));
		}
	} else if (e == d) {
		if (e >= n) {
			ans = min((b * (n - 1) + a), c * n);
		} else {
			ans = min((b * e + a + c * (n - e - 1)), c * n);
		}
	} else {
		if (e >= n) {
			ans = b * (n - 1) + a;
		} else {
			ans = b * e + a + c * (n - e - 1);
		}
	}
	return ans;
}

signed main() {
	int t;
	scanf ("%lld", &t); 
	while(t--) {
		scanf ("%lld%lld%lld%lld%lld%lld", &n, &a, &b, &c, &d, &e);
		printf ("%lld %lld\n", get_max(), get_min());
	}
}
```
事实上，也可以把这些代码**组合**到一起，因为每一种情况的解决过程都**很相似**。

---

## 作者：小小小朋友 (赞：1)

## 题意

题目里写得挺清楚了，注意有 $b\leq c\leq a$ 那么这题会简单很多。

## 思路

考虑几种情况：

1. $d-e$ 或 $e-d$ 大于等于 $n$

那么 A 队每局都能赢，如果反过来那么每局都能输。

2. $n=1$

那么只需判断两边谁进的球多即可。

3. 其他情况：

注意到一个显然正确的方法：只需要一把之内把 A/B 队的进球用完即可。

那么如果发现对方不少于自己进球，那么需要判断的是对面是打平还是赢了还是输了。

剩下的尽可能赢，不行就平局。

注意代码细节比较多。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int n,a,b,c,d,e;
inline void redn(int& ret) {
    ret=0;int f=1;char ch=getchar();
    while (ch<'0'||ch>'9') {if (ch=='-') f=-f;ch=getchar();}
    while (ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
    ret*=f;
}
int getmax(){
    int ans=0;
    if(d-e>=n) return a*n;
    if(n==1){
        if(d>e) return a;
        else if(d==e) return c;
        else return b;
    }
    if(d>=n-1){
        if(d>=e){
            ans=c+min((d-e),n-1)*a+c*(n-1-min((d-e),n-1));
            if(d>e) ans=max(ans,a+min(n-1,d-e-1)*a+c*(n-min(n-1,d-e-1)-1));
        }
        return max(ans,(n-1)*a+b);
    }
    if(d>=e){
        ans=c+(d-e)*a+c*(n-d+e-1);
        if(d>e) ans=max(ans,a+(d-e-1)*a+c*(n-d+e));
    }
    return max(ans,d*a+(n-1-d)*c+b);
}
int getmin(){
    int ans=1e18;
    if(e-d>=n) return b*n;
    if(n==1){
        if(d>e) return a;
        else if(d==e) return c;
        else return b;
    }
    if(e>=n-1){
        if(e>=d){
            ans=c+min((e-d),n-1)*b+c*(n-1-min((e-d),n-1));
            if(e>d) ans=min(ans,b+min(n-1,e-d-1)*b+c*(n-min(n-1,e-d-1)-1));
        }
        return min(ans,(n-1)*b+a);
    }
    if(e>=d){
        ans=min(ans,c+(e-d)*b+c*(n-e+d-1));
        if(e>d) ans=min(ans,b+(e-d-1)*b+c*(n-e+d));
    }
    return min(ans,e*b+(n-1-e)*c+a);
}
signed main(){
    // ios::sync_with_stdio(0);
    redn(T);
    while(T--){
        int maxsco,minsco;
        redn(n),redn(a),redn(b),redn(c),redn(d),redn(e);
        maxsco=getmax();
        minsco=getmin();
        printf("%lld %lld\n",maxsco,minsco);
    }
    return 0;
}
```

---

