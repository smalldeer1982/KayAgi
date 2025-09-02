# [ARC128C] Max Dot

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc128/tasks/arc128_c

整数 $ N,M,S $，及び長さ $ N $ の整数列 $ A=(A_1,A_2,\cdots,A_N) $ が与えられます．

次の条件をすべて満たす長さ $ N $ の非負**実数**列 $ x=(x_1,x_2,\cdots,x_N) $ を作ることを考えます．

- $ 0\ \leq\ x_1\ \leq\ x_2\ \leq\ \cdots\ \leq\ x_N\ \leq\ M $
- $ \sum_{1\ \leq\ i\ \leq\ N}\ x_i=S $

ここで，$ x $ のスコアを $ \sum_{1\ \leq\ i\ \leq\ N}\ A_i\ \times\ x_i $ と定義します． $ x $ のスコアとしてありうる最大の値を求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5000 $
- $ 1\ \leq\ M\ \leq\ 10^6 $
- $ 1\ \leq\ S\ \leq\ \min(N\ \times\ M,10^6) $
- $ 1\ \leq\ A_i\ \leq\ 10^6 $
- 入力される値はすべて整数である

### Sample Explanation 1

$ x=(0,1,2) $ とするのが最適です．

### Sample Explanation 2

$ x=(2/3,2/3,2/3) $ とするのが最適です．

## 样例 #1

### 输入

```
3 2 3
1 2 3```

### 输出

```
8.00000000000000000000```

## 样例 #2

### 输入

```
3 3 2
5 1 1```

### 输出

```
4.66666666666666666667```

## 样例 #3

### 输入

```
10 234567 1000000
353239 53676 45485 617014 886590 423581 172670 928532 312338 981241```

### 输出

```
676780145098.25000000000000000000```

# 题解

## 作者：ZillionX (赞：3)

# Description

给定一个长度为 $n$ 的序列 $a$，构造一个满足下列条件的序列 $x$ 使得 $\sum\limits_{i=1}^n a_ix_i$ 最大：

- $0 \le x_1 \le  \cdots  \le x_n \le m$

- $\sum\limits_{i=1}^nx_i=S$


$n \le 5 \times 10^3, m,S,a_i \le 10^6$，时限 2s。

# Solution

通常做法是 $\mathcal O(n^2)$ 的，这里提供一个严格线性的做法。

------------

我们设 $a$ 的后缀和数组为 $s$。

考虑如果没有 $m$ 的限制怎么做，观察 $a$ 单增的情况，最优解显然是把 $S$ 全部放到 $a_n$ 去。

拓展到一般情况，容易推广出一个比较显然的结论：找出最大的 $\dfrac{s_i}{n-i+1}$，然后把 $S$ 摊平在这个后缀上。

现在我们加上 $m$ 的限制。可以发现一开始还是考虑上面那个贪心，但是单个数的上界是 $m$，可能无法做到后缀摊平，$S$ 还剩下一点。那么我们可以删去已经被操作的后缀，然后递归到前面那个子问题，继续找一个最优的后缀，以此类推，直到 $S$ 被减为 $0$。

直接暴力做是 $\mathcal O(n^2)$ 的，但是我们会发现这东西可以优化。

观察最终答案的形式，可以发现前面被删的后缀平均值一定比后面的要大。证明考虑反证，要是后面的更大的话，一开始就会把它再加上未被删的后缀合起来的后缀一起删掉。

那么我们就可以类比维护凸包的方法，考虑动态加入点维护可能算入最终答案的区间。

用单调栈维护一个平均值单调上升的区间序列，如果当前点的值比栈顶要大，就直接加入。

否则则直接把栈顶和当前点合并，然后从下到上检查一遍，如果栈顶下面区间的平均值比栈顶大，则把它们两个合并。

时间复杂度 $\mathcal O(n)$。

# Code

```cpp
const int N=5e3+5; 
int n,m,S,a[N];
int tp;
pi st[N];
signed main() {
	scanf("%lld%lld%lld",&n,&m,&S);
	int mx=0;
	for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for (int i=1;i<=n;i++) {
		if (!tp || (db)st[tp].fi/st[tp].se<a[i]) st[++tp]=mp(a[i],1);
		else {
			st[tp].fi+=a[i],st[tp].se++;
			while (tp>1 && (db)st[tp].fi/st[tp].se<=(db)st[tp-1].fi/st[tp-1].se) {
				st[tp-1].fi+=st[tp].fi;
				st[tp-1].se+=st[tp].se;
				tp--;
			}
		}
	}
	db ans=0;
	while (tp) {
		if (S<=st[tp].se*m) {
			ans+=((db)st[tp].fi/st[tp].se)*S;
			break;
		}
		else ans+=((db)st[tp].fi)*m,S-=m*st[tp].se;
		tp--;
	}
	printf("%.10lf",ans); 
	return 0;
}
```


---

## 作者：Sampson_YW (赞：3)

假如没有 $m$ 的限制怎么做？记 $i$ 的后缀和为 $s_i$，一开始所有 $p_i=0$。每次选择一个后缀 $i$ 给这个后缀的 $p_{i,\dots,n}$ 都加上一个实数 $x$，那么它会花费 $(n-i+1)x$ 的代价，产生 $s_i\times x$ 的贡献。性价比为 $\dfrac{s_i}{n-i+1}$。于是只要选性价比最高的后缀，将 $S$ 平均分到这个后缀上就行。

但是现在有 $m$ 的限制。那就是每次选择性价比最高的后缀，如果剩余的 $S$ 能平均分到这个后缀上就分完了。否则将这个后缀全都填成 $m$，再把这个后缀删掉。

---

## 作者：skyskyCCC (赞：2)

## 前言。
日常只会三年前的 ARC 的前三题。本题是一个很有意思的题，考查的为基本的贪心，数论与构造。

题意简述：给定一个大小为 $n$ 的序列 $a$ 和两个数。求一个序列 $p$ 使得其满足以下条件：
- 对于该序列 $p$ 中的每一个数，都在 $0$ 到 $m$ 之间且均为实数。
- $\sum_{i=1}^np_i=s$
- $\sum_{i=1}^na_i\times p_i$ 最大。

输出最大值。
## 分析。
看起来无从下手。那么我们不妨先考虑一种极端的情况，即 $a$ 数组为降序，此时 $p$ 序列中的每一个数都是 $\frac{s}{n}$。此时，我们找到了本题的下手点，就是我们从前往后去找一个可能的值的最大值。我们发现序列需要单调不降，所以我们发现可以差分。此时我们稍作推理。令 $x_i=p_i-p_{i-1}$ 且 $y_i=\sum_{j=i}^na_j$。那么我们不难得出，对于任意一个 $x_i$ 都必定为非负数，同时在 $1\leq j\leq i\leq n$ 的条件下，必定存在 $x_i\leq m$。那么，我们根据差分的基本定义，根据题目中的条件，我们得到 $\sum_{i=1}^nx_i\times\left(n-i+1\right)=s$。我们发现，此时这种形式就比较明了了。此时就是求 $\sum_{i=1}^nx_i\times y_i$ 的最大值。

那么这个问题就比较像是背包了，选择 $n$ 个数，总共最大是 $m$ 个单位，一个单位 $i$ 的数的代价为 $\left(n-i+1\right)$ 且价值为 $y_i$。这些数总代价为 $s$ 的约束条件下，求最大的总代价。如果此时没有 $m$ 的限制，那么有 $p_i=\frac{s}{n-i+1}$。这点很显然。因为我们需要在这些数中找到最大值，所以我们考虑贪心。显然的，我们可以先选取比较大的数，把最大的选中，然后判断其代价。如果其代价小于 $s$ 的话，替换掉某一个数，修改其它没有选择的数的价值修改成与当前要替换的数的差值，去找到最大价值，然后替换，修改，查询如此循环，直到代价到 $s$ 甚至以上。

在此过程中，后面为负数的代价一定不能选，所以从后往前找到 $\frac{y_i}{n-i+1}$ 的最大值去替换即可。

代码如下，仅供参考：
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,a[500005];
double m,s;
double cnt,sum,maxx;
int pos;
double tot,rlt,ans[500005];
int main(){
    cin>>n>>m>>s;
    cnt=n;
    for (int i=1;i<=n;i++){
    	cin>>a[i];
	}
    while(cnt>0){
    	sum=maxx=0;
    	pos=0;
    	for (int i=cnt;i>=1;i--){
    		sum+=a[i];
    		if(sum/(cnt-i+1)>maxx){
    			maxx=sum/(cnt-i+1);
    			pos=i;
			}
		}//从后往前查询。 
		tot=min(m,s/(cnt-pos+1));
		for (int i=cnt;i>=pos;i--){
			ans[i]=tot;
			s-=tot;
		}//替换和修改操作。 
		if(s<=0){
			break;
		}//找到了。 
		cnt=pos-1;
    }
    for (int i=1;i<=n;i++){
    	rlt+=a[i]*ans[i];
	}
	//答案相加即可。 
	printf("%.16lf\n",rlt);
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Argon_Cube (赞：0)

我被这个题卡了一个小时？？？？

------

以下令 $B_i=\sum_{j=i}^nA_j$，即 $B$ 为 $A$ 的后缀和。

考虑如果没有那个最大值 $M$ 的限制怎么做。$x$ 是递增的就很烦，我们不妨换一种描述方式：每次我们可以给 $x$ 的一段后缀 $x_{i\sim n}$ 加上同一个数 $y$，并将权值加上 $yB_i$。可以发现这就等价于以总和增加 $y$ 的代价使权值增加 $\dfrac{B_i}{n-i+1}$，所以我们肯定把所有总和放在最大的那个 $\dfrac{B_i}{n-i+1}$ 上面。

那么如果有 $M$ 的限制，我们发现刚才那个方法同样适用，只不过有了一段后缀最多加多少的限制。那么我们可以同样找到 $\dfrac{B_i}{n-i+1}$ 最大的后缀 $[i,n]$，如果能把剩下的总和全放上去就放，否则直接把这个后缀全部设成最大值（$x_{i\sim n}=M$），然后把这个后缀删掉继续做。

从上述过程可以发现一个性质：最优解 $x_i$ 一定可以分成可空的三段，每一段中的数全相等且第一段全为 $0$，最后一段全为 $M$。于是直接枚举两个分界点即可 $\Theta(N^2)$。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <array>

#define rgall(arr)          (arr).begin(),(arr).end()
#define rgo1(arr,cnt)       (arr).begin()+1,(arr).begin()+1+(cnt)
#define rgcnt(arr,cnt)      (arr).begin(),(arr).begin()+(cnt)
#define rgany(arr,rgl,rgr)  (arr).begin()+(rgl),(arr).begin()+(rgr)
#define fori(i,a,b)         for(int i=(a);i<=(b);i++)
#define ford(i,a,b)         for(int i=(a);i>=(b);i--)
#define fori0(i,a,b)        for(int i=(a);i<(b);i++)
#define ford0(i,a,b)        for(int i=(a);i>(b);i--)
#define fr first
#define sc second

using namespace std;

array<long long,5002> va;

int main(int argc,char* argv[],char* envp[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long cnt,maxv,sum;
    double ans=0;
    cin>>cnt>>maxv>>sum;
    fori(i,1,cnt)
        cin>>va[i];
    ford(i,cnt-1,1)
        va[i]+=va[i+1];
    fori(i,1,cnt+1)
        fori(j,1,i)
            if((cnt-i+1)*maxv<=sum&&(sum-(cnt-i+1)*maxv)<=maxv*(i-j))
                ans=max(ans,va[i]*maxv+1.*(va[j]-va[i])*(sum-(cnt-i+1)*maxv)/max(i-j,1));
    cout.setf(ios_base::fixed,ios_base::floatfield);
    cout.precision(10);
    cout<<ans;
    return 0;
}
*/
```

---

## 作者：under_the_time (赞：0)

## 题意

> 给定 $n,m,s$ 和长度为 $n$ 的正整数序列 $a$，要求构造一个长度为 $n$ 的**实数**序列 $x$，满足：
>
> - $0\le x_1\le x_2\le\cdots \le x_n\le m$；
>
> - $$
>   \sum_{i=1}^{n}x_i=s
>   $$
>
> 令 $x$ 的分数为 $\sum_{i=1}^n x_ia_i$，求合法的 $x$​ 最大的分数。
>
> $n\le 5000$，$1\le m,a_i\le 10^6$，$1\le s\le \min\{n\times m,10^6\}$。

## 解法

考虑贪心，先不考虑 $m$ 的限制，我们找到一段后缀，使得后缀和除以后缀长度最大，然后把 $S$ 均匀分配到这段后缀的每个位置上即可。$m$ 的限制可能会使找到一段后缀后 $S$ 分配不完，那么我们把这段后缀抠掉接着找即可。复杂度 $O(n^2)$​​。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 5005;
int n, m, a[maxn]; double s;
#define ll long long
ll sum[maxn]; double x[maxn];
int main() {
    scanf("%d %d %lf", &n, &m, &s);
    for (int i = 1; i <= n; i ++)
        scanf("%d", &a[i]);
    for (int i = n; i >= 1; i --) sum[i] = sum[i + 1] + a[i];
    for (int lst = n; s > 0 && lst > 0; ) {
        int pos; double mx = -1;
        for (int i = 1; i <= lst; i ++)
            if (1.0 * (sum[i] - sum[lst + 1]) / (lst - i + 1) > mx)
                pos = i, mx = 1.0 * (sum[i] - sum[lst + 1]) / (lst - i + 1);
        double ss = s;
        for (int len = lst - pos + 1; lst >= pos; lst --)
            x[lst] = min(1.0 * s / len, 1.0 * m), ss -= x[lst];
        s = ss;
    } double ans = 0;
    for (int i = 1; i <= n; i ++) 
        ans += x[i] * a[i];
    return printf("%.8lf", ans), 0;
} 
```

---

