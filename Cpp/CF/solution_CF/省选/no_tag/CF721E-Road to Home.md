# Road to Home

## 题目描述

Once Danil the student was returning home from tram stop lately by straight road of length $ L $ . The stop is located at the point $ x=0 $ , but the Danil's home — at the point $ x=L $ . Danil goes from $ x=0 $ to $ x=L $ with a constant speed and does not change direction of movement.

There are $ n $ street lights at the road, each of which lights some continuous segment of the road. All of the $ n $ lightened segments do not share common points.

Danil loves to sing, thus he wants to sing his favourite song over and over again during his walk. As soon as non-lightened segments of the road scare him, he sings only when he goes through the lightened segments.

Danil passes distance $ p $ while performing his favourite song once. Danil can't start another performance if the segment passed while performing is not fully lightened. Moreover, if Danil has taken a pause between two performances, he is not performing while not having passed a segment of length at least $ t $ . Formally,

1. Danil can start single performance at a point $ x $ only if every point of segment $ [x,x+p] $ is lightened;
2. If Danil has finished performing at a point $ x+p $ , then the next performance can be started only at a point $ y $ such that $ y=x+p $ or $ y>=x+p+t $ satisfying the statement under the point $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF721E/3f2808218281075db371b77f474d7f1e009cc138.png)Blue half-circles denote performances. Please note that just after Danil has taken a pause in performing, he has not sang for a path of length of at least $ t $ .Determine how many times Danil can perform his favourite song during his walk from $ x=0 $ to $ x=L $ .

Please note that Danil does not break a single performance, thus, started singing another time, he finishes singing when having a segment of length of $ p $ passed from the performance start point.

## 说明/提示

The first sample case is just about corresponding to the picture from the statement.

## 样例 #1

### 输入

```
17 2 2 6
0 9
13 17
```

### 输出

```
5
```

## 样例 #2

### 输入

```
12 2 2 2
0 5
6 11
```

### 输出

```
4
```

## 样例 #3

### 输入

```
12 2 2 4
0 5
6 11
```

### 输出

```
3
```

# 题解

## 作者：duyi (赞：4)

## 题解 CF721E Road to Home

首先观察发现⼀段亮的路如果开始唱歌，那么就会⼀直唱到不能再唱下去为止。否则可以将下一段要唱的歌提前到这一段，一定不会变差。所以⼀段亮的路有两种选择：不唱歌；尽可能多唱歌。

考虑DP。设$f[i]$表示只考虑前$i$段亮的路，最多能唱几遍完整的歌。设$g[i]$表示在唱的歌的数量达到$f[i]$的前提下，最后一首歌最早什么时候结束。

转移时，先考虑第$i$段不唱歌的情况。即$f[i]=f[i-1]$，$g[i]=g[i-1]$。

如果第$i$段唱歌。考虑暴力的转移：枚举一个转移点$j$。设$s=\max(l_i,g[j]+t)$，表示第$i$段开始唱歌的时间。则转移为：
$$
(f[i],g[i])\leftarrow (f[j]+\lfloor\frac{r_i-s}{p}\rfloor,s+\lfloor\frac{r_i-s}{p}\rfloor\cdot p)
$$
其中$\leftarrow$表示用右边的去更新左边的。具体来说，更新的方式是，如果$f$更大则更优，如果$f$相等则$g$更小的更优。

暴力转移时间复杂度$O(n^2)$。

考虑当$g[j]+t\leq l_i$的时候，转移中除了$f[j]$以外，其他都是一样的。而因为初始时令$f[i]=f[i-1]$，所以$f$是单调不降的，直接找到最后一个这样的$j$转移即可。直接用一个指针维护。

当$l_i<g[j]+t\leq r_i$。可以暴力扫描这段$j$。显然，每个$j$只会被一个$(l_i,r_i]$的区间扫描到。所以时间复杂度$O(n)$。

参考代码：

```cpp
//problem:CF721E
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int MAXN=1e5;
int L,n,p,t;
struct Seg_t{int l,r;};
Seg_t a[MAXN+5];
pii dp[MAXN+5];
bool cmp(pii a,pii b){return a.fi>b.fi||(a.fi==b.fi&&a.se<b.se);}//a比b优
void ck(pii& x,pii y){if(cmp(y,x))x=y;}
int main() {
	cin>>L>>n>>p>>t;
	for(int i=1;i<=n;++i)cin>>a[i].l>>a[i].r;
	dp[0]=mk(0,-t);
	int p1=0,p2=0;
	//p1:最后一个 dp[j].se+t<=l[i] 的 j
	//p2:最后一个 dp[j].se+t<=r[i] 的 j
	for(int i=1;i<=n;++i){
		dp[i]=dp[i-1];//第一种转移:第i段完全不选
		int st;
		while(p1+1<i && dp[p1+1].se+t<=a[i].l)++p1;
		while(p2+1<i && dp[p2+1].se+t<=a[i].r){
			++p2;
			if(p2>p1)st=dp[p2].se+t,ck(dp[i],mk(dp[p2].fi+(a[i].r-st)/p,st+(a[i].r-st)/p*p));
		}
		st=a[i].l;
		ck(dp[i],mk(dp[p1].fi+(a[i].r-st)/p,st+(a[i].r-st)/p*p));
	}
	cout<<dp[n].fi<<endl;
	return 0;
}
```



---

## 作者：封禁用户 (赞：4)

# 0.前言
[我的AC记录](https://www.luogu.com.cn/record/56708790)

题目链接：[CF链接](http://codeforces.com/contest/721/problem/E)
 
题目大意：
在一条数轴上，Bob要学校（点 $0$）走到家（点 $L$），其中有 $n$ 个路灯，路灯照耀的范围是 $(l[i], r[i])$ （路灯的范围不会重叠）；Bob会在灯亮的的范围内唱歌，每次唱的距离为 $p$；（必须唱完，中间必须全部是在路灯照耀范围内）

当Bob唱完一次的时候，下一次唱的地点必须满足以下其中一点：
1. 开始唱的地点和上一次唱结束的地点重合；
2. 开始唱的地点和上一次唱结束的地点距离>=t;
 
问最多，能唱几次。
 

# 1.解析

 - 题目の重点：

路灯 $(l[i], r[i])$ 不会重叠，并且在照耀范围内，那么距离间隔要么为 $0$，要么 $\geq t$；
那么对于 bob 来说，每到一个路灯他都须作出抉择：

1. 唱歌。需要看当前是否满足唱歌的条件：剩下的路灯距离是否足够 $p$，当前位置和上次唱歌的位置是否满足唱歌的距离条件；
2. 不唱歌。对前面没有要求。

那么我们首先想到的就是 dp。

 - 最优子结构：

假设 $dp[i]$ 为到距离 $i$ 能唱的最多次数（并且要求是以唱歌结尾），且区间 $[i-p, i]$ 是在路灯范围内，那么 $dp[i]$ 可以由 $dp[i-p]$ 转移过来。

$dp[i]\to \max(dp[0~(i-t-p)])+1$；
这样的状态数为 $L$（距离的范围）。
状态转移的复杂度为 $O(L)$。

其中的 $\max(dp[0]\to dp[i-t-p])$，可以用 $dmax[i]$ 来表示前 $i$ 个位置的最优解，这样 $\max(dp[0]\to dp[i-t-p])$ 就等于 $dmax[i-t-p]$;
这样状态转移的复杂度就将为 $O(1)$（当 $L$ 非常大时，仍为 $O(L)$）。

 - 状态转移
 
因为区间性，$dp[i]$ 改成到距离 $r[i]$ 能唱的最多次数，注意**不能要求到 $r[i]$ 来结尾**，因为不满足最优解。

这样的话，假设是从 $dp[k]$ 转移到 $dp[i]$，从 $g[k]$ 开始，连续 $t$ 的距离不唱歌，然后 $\min(r[i]-l[i], r[i]-g[k]-t)$ 的距离用于唱歌，这里我们用 $count(L)$ 表示距离 $L$ 能唱的次数，最后 $dp[i]$ 取最优解的时候 $g[i]=\max(l[i], g[k]+t) + count(L)\times p$;
 
对于 $g[k] + t \leq r[i]$ 的 $k$，都可以这样：

$dp[i] = \max(dp[i], dp[k] + count(L))$;

$g[i] = g[k] + count(L) * p + t$

$L=min(r[i]-l[i], r[i]-g[k]-t)$

 - 再次优化！！！
 
目前状态数：$O(N)$, 目前转移复杂度：$O(N)$，总复杂度：$O(N^2)$ 。

对于 $dp[k]$ 是固定值，$count(L)$ 中的 $L$ 会随着 $i$ 的增加而增加，而当 $L$ 很大之后，$dp[k]$ 较小的状态再进行最优化转移是无效的过程，因为 $dp[k+1]$ 是更合适的解。

状态的决策因素有两个,$dp[k]$ 和 $g[k]$：
1. $dp[k]$ 小，$g[k]$ 小的解，不能舍弃，因为 $g[k]$ 小存在转移的可能；
2. $dp[k]$ 大，$g[k]$ 大的解，不能舍弃，因为 $dp[k]$ 大存在转移的可能；
3. $dp[k]$ 小，$g[k]$ 大的解，舍弃；
4. $dp[k]$ 大，$g[k]$ 小的解，不能舍弃，因为 $g[k]$ 小和 $dp[k]$ 大均存在转移的可能。

因为 $i<j$，$r[i] < l[j]$ , 必然有 $g[i] \leq g[j]$，$count(L[i]) < count(L[j])$。$dp[k]+count(L)$ 具有决策单调性，同时有效区间从 $r[i]-g[k]-t\geq 0$ 开始；
 
维护决策的队列，根据 $dp[k]+count(L)$ 可以算出当前所有的有效决策中的最优解。

随着 $r[i]$ 的不断增加，从 $r[i]-g[k]-t\geq0$ 的队列方案中，一直更新 $dp[k]+count(L)$；

# 2.code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 114514;
int l[N], r[N];
int dp[N];
int g[N];
int main() {
    int n, L, p, t;
    cin >> L >> n >> p >> t;
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &l[i], &r[i]);
    }
    deque<int> q;
    q.push_back(0);
    g[0] = -t;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int k = -1;
        while (!q.empty() && g[q.front()] + t <= r[i]) {
            int nl = max(l[i], g[q.front()] + t), nr = r[i];
            if (dp[q.front()] + (nr - nl) / p > dp[i]) {
                dp[i] = dp[q.front()] + (nr - nl) / p;
                g[i] = nl + (nr - nl) / p * p;
            } else if (dp[q.front()] + (nr - nl) / p == dp[i]) {
                g[i] = min(g[i], nl + (nr - nl) / p * p);
            }
            k = q.front();
            q.pop_front();
        }
        if (k != -1) {
            q.push_front(k);
        }
        if (dp[i] > ans) {
            ans = dp[i];
            q.push_back(i);
        }

        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}
```

求关注qwq

---

## 作者：James_Brady (赞：1)

首先，我们定义两个数组f[i],g[i]

f[i]表示走到第i个区间能唱歌的最大次数，g[i]表示f[i]最大时，最后一次唱歌时的，最靠左位置

明显有：

**f[i]=max(f[j]+(r[i]-max(g[j]+t,l))/p)**

**g[j]=max(r[i]-(r[i]-max(g[j]+t,l))%p)**

**(1<=j<i)**

解释：max(g[j]+t,l)为本区间开始唱歌的位置，要么上一个区间过t在唱歌，要么一直不唱，一刚进入就唱

由于j是连续区间，所以可以用单调队列维护优化

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
int L,x,p,t,n;
int f[100010],g[100010];
int l,r,q[100010],head=1,tail=1;
int main()
{
	scanf("%d%d%d%d",&L,&n,&p,&t);
	g[0]=-t;//边界条件，从0开始
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&l,&r);
		g[i]=g[i-1];f[i]=f[i-1];//默认为上一个
		head--;//细节，可以慢慢体会
		while(head<=tail&&g[head]+t<=r)//如果可以跳到当前区间
		{
			int x=max(g[head]+t,l);
			int y=f[head]+(r-x)/p;
			int z=r-(r-x)%p;
			if(y>f[i]||y==f[i]&&z<g[i])
			{
				f[i]=y;
				g[i]=z;
			}
			head++;//队首出队
		}
		tail++;//队尾入队
	}
	printf("%d",f[n]);
	return 0;
}
```


---

## 作者：skyskyCCC (赞：0)

## 前言。
明显的动态规划。
## 分析。
有一个显然的结论：当在某一个位置 $x$ 出现 $x+p>r$ 时，即他在一段路上唱歌，只有当他唱到不能再唱时才会结束。我们可以从这里入手。

设 $dp_i$ 表示到第 $i$ 段为止能唱的歌的曲数的最大数，设 $g_i$ 表示唱完第 $dp_i$ 首歌后的左端点。如果我们用 $k$ 来表示 $l_i$ 和 $g_i+t$ 中的较大值，则考虑暴力转移：
$$dp_i=\frac{dp_j+\left(r-k\right)}{p}$$
同时还有：
$$g_i=r-\left(r-k\right)\bmod p$$
显然存在 $dp$ 和 $g$ 都是非递减的，所以我们可以直接用 $i-1$ 时存的值替换掉 $i$ 存的值，如果 $i-1$ 比 $i$ 更优。那么我们考虑 $dp_i$ 可以从谁转移。我们根据上面的分析，可以得到限制条件为 $x_i\leq j\leq y_i$。设 $w$ 为 $x_i$ 同时 $m$ 为 $y_i$ 则将上面的不等式进行说明：其中 $x_i$ 表示的是最后面的满足 $g_w+t\leq l_i$ 的点，同理 $y_i$ 表示的是最后面的满足 $g_m+t\leq r_i$ 的点。显然对于每一次转移，都有不同的 $r_i$ 和 $l_i$ 所以一定存在 $r_i<l_{i+1}$ 即可以推出：
$$g_m+t<l_{i+1}$$
所以更新 $y_i$ 即可，时间复杂度 $O\left(n\right)$。

代码如下，仅供参考：
```
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;
int L,n,p,t,l,r;
int dp[100005],g[100005];
int main(){
    cin>>L>>n>>p>>t;
    g[0]=-t;
    int j=1;
    for (int i=1;i<=n;i++){
        cin>>l>>r;
        dp[i]=dp[i-1];
        g[i]=g[i-1];
        for (j--;j<i&&g[j]+t<=r;j++){
            int k=max(g[j]+t,l);
			int sum=dp[j]+(r-k)/p;
			int b=r-(r-k)%p;
            if(sum>dp[i]||(sum==dp[i]&&b<g[i])){
			    dp[i]=sum;
				g[i]=b;
			}
        }
    }
    cout<<dp[n]<<"\n";
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

