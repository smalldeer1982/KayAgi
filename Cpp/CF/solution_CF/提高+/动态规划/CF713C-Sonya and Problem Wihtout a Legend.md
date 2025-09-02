# Sonya and Problem Wihtout a Legend

## 题目描述

Sonya was unable to think of a story for this problem, so here comes the formal description.

You are given the array containing $ n $ positive integers. At one turn you can pick any element and increase or decrease it by $ 1 $ . The goal is the make the array strictly increasing by making the minimum possible number of operations. You are allowed to change elements in any way, they can become negative or equal to $ 0 $ .

## 说明/提示

In the first sample, the array is going to look as follows:

 $ 2 $ $ 3 $ $ 5 $ $ 6 $ $ 7 $ $ 9 $ $ 11 $

 $ |2-2|+|1-3|+|5-5|+|11-6|+|5-7|+|9-9|+|11-11|=9 $

And for the second sample:

 $ 1 $ $ 2 $ $ 3 $ $ 4 $ $ 5 $

 $ |5-1|+|4-2|+|3-3|+|2-4|+|1-5|=12 $

## 样例 #1

### 输入

```
7
2 1 5 11 5 9 11
```

### 输出

```
9
```

## 样例 #2

### 输入

```
5
5 4 3 2 1
```

### 输出

```
12
```

# 题解

## 作者：lgswdn_SA (赞：65)

本篇题解复杂度为 $O(n\log n)$，并且同其他同复杂度题解不同的是，这里我用了**维护凸壳**来解释了这题（当然代码没啥不同）。本题解比较小白向，如果对凸包比较了解的话可以跳掉很多简单的证明。

主要和 [codeforces 上的博客](https://codeforces.com/blog/entry/77298) 有同样的思想。可能那里讲的稍微清晰一点。

首先我们将所有 $a_i$ 减去 $i$ 就可以从严格单调递增转化为单调不降，这样会方便很多。

然后考虑一个很简单的 DP。$f(i,j)$ 表示只考虑前 $i$ 个数，然后修改后的第 $i$ 个数 $\le j$ 的情况最小代价，$g(i,j)$ 表示只考虑前 $i$ 个数，然后修改后的第 $i$ 个数 $=j$ 的最小代价。我们发现 $f$ 是 $g$ 的前缀最小值，然后有转移 $g(i,j)=f(i-1,j)+|a_i-j|$。

到这里已经足矣完成 $O(n^2)$ 的部分了。然而我们要继续优化后，必须考虑对状态进行优化。有经验的话可以很容易发现 $f(i),g(i)$ 关于 $j$ 具有凸性。一般来说这样就可以省掉一个维度。

具体怎么证明其实也很简单。对于一个 $f(i)$，我们把 $f(i,j)$ 作为一个点 $(j,f(i,j))$ 画出来，然后相邻两个点连一下，就可以得到一个分段函数 $F_i$。我们对 $g$ 做同样的操作得到 $G_i$。首先初始时两个必然都是凸函数。考虑转移。用归纳法，若 $F_{i-1}$ 是凸的，则因为 $|a_i-j|$ 是下凸的，$F_{i-1}$ 也是凸的，两个凸函数相加得到的 $G_{i}$ 也是凸的；然后 $F_i$ 是 $G_i$ 的前缀和，所以 $F_i$ 也是凸的，所以可以得到每个 $F$ 和 $G$ 均为下凸壳。并且还有一个很好的性质，斜率均为整数（容易证明）。

然后是一个非常重要的维护手段——维护拐点来维护凸壳。一个下凸壳（其实上凸壳也是类似的）可以按照如下维护（维护一个集合和一条直线）：对于一个凸壳上的点 $s_i$，如果它两端的斜率不一样，就放拐点。设两边斜率差为 $p$，那就在集合中放入 $p$ 个 $s_i$ 的横坐标。由于最后一段必然是无限延申下去的一条支线，我们考虑用一个直线来描述一条直线。容易发现，用一个一次函数和一个拐点集合能够描述一个这样的斜率为整数的凸壳。

设凸函数 $C_1,C_2$ 的集合为 $S_1,S_2$，并且直线分别为 $f_1,f2$，则 $C=C_1+C_2$ 的集合为 $S=S_1\cup S_2$，一次函数是 $f=f_1+f_2$（斜率相加，截距相加）。

这道题有一个很好的地方，就是 $F_i$ 的结尾的一次函数必然是一条水平的直线，$G_i$ 的结尾的一次函数必然是一条斜率为 $1$ 的直线，并且除了结尾部分 $F_i$ 和 $G_i$ 一样。所以我们可以通过移除一个集合内最大的拐点然后修改一下一次函数的斜率即可从 $G_i$ 得到 $F_i$。

至于如何从 $F_{i-1}$ 转移到 $G_{i}$，我们相当于加上一个凸函数 $A_i(x)=|a_i-x|$。首先 $A_i(x)$ 的拐点集合应该为 $\{a_i,a_i\}$。考虑设 $F_{i-1}$ 的最大的拐点为 $s$。

- 若 $a_i\ge s$，那么我们直接在 $F_{i-1}$ 的集合中塞入两个 $a_i$ 即可得到 $G_i$。然后我们再弹出一个 $a_i$ 可以得到 $F_i$。
- 否则，我们在 $F_{i-1}$ 的集合中塞入两个 $a_i$，然后更新一下直线（实际操作中只需要通过更新 $ans$ 即可）可以得到 $G_i$，然后我们再弹出一个 $s$ 即可得到 $F_i$。

以上操作用一个堆就能维护了。

```cpp
int n,ans,a;
priority_queue<int>q;

signed main() {
	n=read();
	rep(i,1,n) {
		q.push(a=read()-i);
		if(a<q.top()) q.push(a), ans+=q.top()-a, q.pop();
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：whiteqwq (赞：45)

## 题意
- 给定一个长为$n$的序列$a$，可以进行若干次操作使得某个数减一或加一，求使序列**严格递增**的操作数；
- $1\leqslant n\leqslant3000$。
[题目链接](https://www.luogu.com.cn/problem/CF713C)

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1733903)

四倍经验：（前三题为使得序列非严格递增）

[P4597 序列sequence](https://www.luogu.com.cn/problem/P4597)

[CF13C Sequence](https://www.luogu.com.cn/problem/CF13C)

[P2893 [USACO08FEB]Making the Grade G](https://www.luogu.com.cn/problem/P2893)

[CF713C Sonya and Problem Wihtout a Legend](https://www.luogu.com.cn/problem/CF713C)

## 分析
首先有一个套路的想法，将$a_i$减去$i$，这样可以使得求严格递增改为**非严格递增**，因为我们需要考虑的只是$a$之间的相对大小关系，因此把$a_i$减去$i$并求非严格递增序列之后，我们加回这个$i$，就可以让相邻两项之间差增加一，变为严格递增。

转化之后，我们考虑如何求解。

考虑下面一种想法（主要是我想不到怎么正向考虑这种诡异的想法，只能强行说明这个做法的正确性）：

我们边维护序列边用优先队列维护当前**修改过的序列**的最大值，每当我们得到一个数$x$，我们先把它加入优先队列，然后取出堆顶$y$（如果有多个最大值，我们取出靠后的），如果$x\geqslant y$，我们不用管，如果$x<y$，我们强行把$y$修改为$x$（即$\text{pop}$掉堆顶，并新$\text{push}$进一个$x$）。

我们考虑任意一种调整方法,发现对于逆序对$x,y(x<y,a_x>a_y)$，我们发现$y$是不可能减小的（否则就更不优了），而我们的算法先钦定了$y$不减小，所以算法在以后的选择一定会更优，因此我们发现这个**代价达到了下界**。

然后考虑一个问题：如果$y$修改为$x$之后，$y$前面的最大值$z$大于$y$了（即$x<z<y$），那么这种构造的代价是否不合法？

我们构造到最后，这个$z$有可能也被修改了，我们不妨讨论$z$最终的值$z'$。

我们定义“微调”为**不改变花费的情况下，改变某个数对的值**。

如果$z'>x$，那么我们可以强行把$x$和$y$强行微调成$z'$（考虑正确性：因为$x<z<y$，所以在进行$x$和$y$的强行修改时可以**用一种反悔的思想**将$x$和$y$同时改成$z'$，此时花费仍然为$(y-z')+(z'-x)=y-x$），这样$z$和$x,y$的矛盾就不存在了。

如果$z'\leqslant x$，那么我们发现它与$x$和$y$不再存在矛盾，而它之前的数与它的矛盾可以用类似归纳法一样的方式证明微调可以使得花费不变。

时间复杂度：$O(n\log n)$。

## 代码
```
#include<stdio.h>
#include<queue>
using namespace std;
int n;
long long ans;
priority_queue<int>q;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		x-=i,q.push(x);
		if(x<q.top()){
			ans+=q.top()-x;
			q.pop(),q.push(x);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：black_trees (赞：15)

upd - 2020.7.31 ：原来的证明有一点问题，合并后的函数应该是满足严格递增的，已修改。

upd - 2021.5.21 ：修改了图床并更正原来的一处笔误，所以重新提交一次。

upd - 2021.5.22 ： 修正以前错误的排版，添加了更多的说明。

upd - 2021.8.8 ： 修正笔误。 

upd - 2022.4.6 ：更新思路，优化排版和代码风格。

## Description

> 给你一个序列 $a$，长度为 $n$。
>
> 每次操作可以把 $a$ 中任意一个元素加一或者减一，代价为 $1$。
>
> 求使得原序列严格单调递增的最小代价。
>
> $1\le n \le 3\times10^3, 1\le a_i \le 10^9$。

## Analysis

本题和 [POJ3666](http://poj.org/problem?id=3666) 十分类似，唯一的区别是，本题要求的是严格单调递增，而 POJ3666 则要求非严格单调递增。

所以可以考虑一个经典 Trick，对于每一个 $a_i$，让它减去 $i$，本题的严格单调递增就转化为了非严格单调递增。

经过分析之后可以得到一个引理（转化为非严格之后）：

### Lemma

> 设最后得到的序列为 $b$，$S_a,S_b$ 分别为 $a,b$ 当中出现的所有数组成的集合。
>
> 必然存在一组最优解，使得 $S_b \subset S_a$。

### Proof

首先可以把问题转化为：给定一个序列 $a$，构造一个非严格单调递增的序列 $b$，使得 $\sum\limits_{i=1}^{n} |a_i -b_i|$ 最小。

[![qj6Y0s.png](https://s1.ax1x.com/2022/04/06/qj6Y0s.png)](https://imgtu.com/i/qj6Y0s)

考虑这样的一张图，其中 $re$ 表示对 $a$ 排序之后得到的序列，橙色点表示 $b$。

对于每个 $re_i,re_{i+1}$，把所有在 $[re_i,re_{i+1}]$ 这个区间的 $b$ 都找出来（上图被框起来的部分）。

统计 $b_i$ 对应的 $a_i$ 大于等于 $re_{i+1}$ 的个数 $y$，小于等于 $re_i$ 的个数 $x$。

如果 $x > y$ ，那么把被框起来的这部分整体向下平移 $d$ 个单位，使得它们当中的最低点等于 $re_i$，总代价就会增加 $d(y-x)$，因为 $x >y$，所以实际上总代价会减小，就会更优。

$x < y$ 的时候同理，$x=y$ 的时候任意选一个方式平移即可。

归纳之后可以发现，任何一个 $b_i$ ，只要它不属于 $S_a$，总是可以把它变成 $S_a$ 当中的某一个数，且最终答案不会更劣。

引理得证。

### Method

根据引理以及其证明过程，不难想到一个 DP 状态：

设 $dp_{i,j}$ 表示，考虑使 $a_1 \sim a_i$ 全部满足条件，且使 $a_i$ 变为 $re_j$ 时的状态集合。

$dp_{i,j}$ 的属性是：“总代价的最小值”。

最终答案是所有 $dp_{n,i}$ 的最小值，其中 $i \in [1, n]$。

考虑从“上一次决策”进行转移，可以将状态集合划分如下：

[![qjRlUs.png](https://s1.ax1x.com/2022/04/06/qjRlUs.png)](https://imgtu.com/i/qjRlUs)

那么可以得到一个方程：

$$dp_{i,j} = \min\limits_{0\le k \le j}\{dp_{i-1,k}\} + |a_i - re_j|$$

写出代码：

```cpp
memset(dp, 0x3f,sizeof dp), dp[0][0] = 0;
for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= n; ++j) {
        for(int k = 0; k <= j; ++k) {
           	dp[i][j] = min(dp[i][j], dp[i - 1][k]);
            dp[i][j] += abs(a[i] - re[j]);
        }
        // 因为初始化只初始化了 dp[0][0]，所以 k 要从 0 开始。
        // 否则从 dp[1][1] 开始的 dp 值就不会被更新，会得到错误的答案。
    }
}
```

复杂度是 $\text{O}(n^3)$ 的，需要优化。

瓶颈在于每次枚举 $k$ 求出 $dp_{i - 1,k}$ 的“候选集合”中的最小值。

发现当外层循环的 $i$ 固定，$j$ 每次增大 $1$ 的时候，$dp_{i-1,k}$ 的候选集合只会新加入一个值： $dp_{i-1,j}$。

所以可以考虑使用一个变量记录当前候选集合当中的最小值，每次直接使用这个变量进行转移。

那么每次转移的复杂度就从 $\text{O}(n)$ 优化到了 $\text{O}(1)$，总时间复杂度变为 $\text{O}(n^2)$，可以通过本题。

```cpp
using i64 = long long;

int main() { 
	cin >> n;
	for(int i = 1; i <= n; ++i) {
		cin >> a[i];
		a[i] -= i, re[i] = a[i];
	}
	sort(re + 1, re + 1 + n);
	
    // 初始化写法和 n^3 做法略有不同，但本质一样。
	for(int i = 1; i <= n; ++i) {
		dp[1][i] = abs(a[1] - re[i]);
	}
	for(int i = 2; i <= n; ++i) {
		i64 minv = 2e18;
		for(int j = 1; j <= n; ++j) {
			minv = min(minv, dp[i - 1][j]);
			dp[i][j] = minv + abs(a[i] - re[j]);
		}
	}
	
	i64 res = 2e18;
	for(int i = 1; i <= n; ++i) {
		res = min(res, dp[n][i]);
	}
	cout << res << endl;
	return 0;
}
```

当然，实际上可以对 $re$ 进行一次去重，这样复杂度可以降到 $\text{O}(n \times |S_a|)$。

---

## 作者：Yaha (赞：10)

## DP

和这题相似的是[P2893](https://www.luogu.com.cn/problem/P2893)，只不过P2893是非严格单调递增，而这题是严格单调的。

[这个是我P2893的题解，建议先看看这个](https://www.luogu.com.cn/blog/Yaha/solution-p2893)

那么严格单调递增该怎么处理呢？

我们可以尝试把这个问题转化成非严格单增问题。

举个例子，我们要把a，b，c构造成一个严格单增数列：aa，bb，cc，

那么aa<bb<cc；那aa和bb来说，aa<=bb-1。

aa-1<=bb-2<=cc-3；

问题可以转化成把a-1,b-2,c-3构造成一个非严格单增数列，而a-1转化成aa-1所需的操作数和之前是一样的。

```cpp
#include<bits/stdc++.h>
#define in long long
using namespace std;
const int amou=3101;
const in Inf=2e18;
int a[amou],b[amou],n;
in f[amou][amou],Min[amou][amou];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a[i]=b[i]=a[i]-i;
	}
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
	{
		Min[i][0]=Inf;
		for(int j=1;j<=n;j++)
		{
			f[i][j]=Min[i-1][j]+abs(a[i]-b[j]);
			Min[i][j]=min(Min[i][j-1],f[i][j]);
		}
	}
	printf("%lld",Min[n][n]);
	return 0;
}
```


---

## 作者：liuyifan (赞：8)

## 来发一个O(nlogn)的做法~~虽然这道题暴力O(n2)能过~~

首先考虑非递增序列，则每个数字最终变成的数字一定是该数组中的某个数。那么O(n^2)DP一下即可。

那么对于递增序列，将a[i]变成a[i]-i后，再照非递增序列跑一遍dp即可。

这个DP算法可以用C++中的STL堆来优化到O(nlogn)

code:
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define reg register 
#define ll long long
#define y1 liuifan_y1 
#define inf 0x3f3f3f3f
#define iinf 0x3f3f3f3f3f3f3f3f 
#define data liuyifan_data 
#define next liuyifan_next 
#define ture true 
#define flase false 
#define lowbit(x) x&(-x)
using namespace std; 
ll n,x,ans;
priority_queue<ll>q;//STL堆(默认为大根堆) 
int main()
{
    scanf("%d",&n);
    for(reg int i=1;i<=n-1;i++)
	{
        scanf("%lld",&x);
        x-=i;//预处理，将a[i]变成a[i]-i 
        q.push(x);
        if(q.top()>x)
		{
            ans+=q.top()-x;//top:顶端 
            q.pop();//pop:弹出 
            q.push(x);//push:压入 
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```
### 关于堆的更多解释和C++ STL中的使用方法，推荐几个链接:[链接1	](http://c.biancheng.net/view/480.html)[链接2	](https://blog.csdn.net/xiaoquantouer/article/details/52015928)[链接3	](https://www.cnblogs.com/cielosun/p/5654595.html)[链接4	](https://baike.baidu.com/item/%E5%A0%86/20606834)[链接5](https://blog.csdn.net/hairetz/article/details/4141043)

---

## 作者：Bezime (赞：6)

这题只要了解其精髓就变得很简单了。

我刚刚做了一个单调不增或单调不减的题，通过推荐题目过来了。

这里我们将单调递增转化为单调不减，只需要将 $a_i$（下标为 $1$~$n$）减去 $i-1$ 就可以了。

为什么呢？反着想，如果要将单调不减转化为单调递增，考虑数组值全相等的特殊情况，我们就得把 $a_2$ 加上 $1$；把 $a_3$ 加上 $2$；把 $a_4$ 加上 $3$；……；把 $a_n$ 加上 $n-1$。即把 $a_i$ 加上 $i-1$。所以要将单调递增转化为单调不减，就把 $a_i$ 减去 $i-1$。现在想想数组不限制的，因为我们不能知道最终序列两个值是否相等，我们按数组值全相等的特殊情况才能保证是单调递增的。

现在来想单调不减的思路，给个样例。

单调处理前：
```
7
1 4 4 7 9 7 15
```
单调处理后：
```
7
1 3 2 4 5 3 9
```
我们按递推顺序想想，

下标为 $1$ 时，符合条件，不做处理。序列为：$\{1\}$。

下标为 $2$ 时，符合条件，不做处理。序列为：$\{1,3\}$。

下标为 $3$ 时，不符合，将前面的 $3$ 改为 $2$。序列为：$\{1,2,2\}$。

下标为 $4$ 时，符合条件，不做处理。序列为：$\{1,2,2,4\}$。

下标为 $5$ 时，符合条件，不做处理。序列为：$\{1,2,2,4,5\}$。

下标为 $6$ 时，不符合，将前面的 $5$ 改为 $3$。序列为：$\{1,2,2,4,3,3\}$。?

下标为 $7$ 时，符合条件，不做处理。序列为：$\{1,2,2,4,3,3,9\}$。

为什么第六步可行呢？我们在做处理时肯定是将前面最大数变为这个数（即最适配情况）（$5,3$ 变 $3,3$），而这个的操作数，与将前面最大数与这个数折中变化的操作数相同（$5,3$ 变 $4,4$）。

而我们每次只找前面最大值，把我们更改的数值当作动态平衡（可小可大），这种动态平衡与单调不减是等效的（这里要好好理解），因为这并不影响我们找到的前面最大值与操作数。

当当前的数小于前面最大值，且这个最大值原本处于动态平衡，则这个数的值就定下来了，每次将前面最大数变为这个数。

当当前的数大于或等于前面最大值，符合条件，不更改值。

所以我们只需维护前面的更改数值后的值的最大值就行了。

附上代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxm 200002
#define mxn 100002
using namespace std;
ll n,mx;
priority_queue<ll>qmx;
inline void rd(ll &x){x=0;short f=1;char c=getchar();while((c<'0'||c>'9')&&c!='-') c=getchar();if(c=='-') f=-1,c=getchar();while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();x*=f;}
inline void pt(ll x){if(x<0) putchar('-'),x=-x;if(x>9) pt(x/10);putchar(x%10+'0');}
int main(){
	rd(n);
	for(ll i=1,x;i<=n;i++){
		rd(x);
		x-=i-1;//将其要求从单调递增，转化为单调不减
		qmx.push(x);//将x放入优先队列
		mx+=qmx.top()-x;//记录操作次数
		qmx.pop();//将最大值弹出
		qmx.push(x);//改为x
	}//想想当x大于或等于时，是否没改值
	pt(mx);//输出操作次数
}
```

---

## 作者：IL杰佣 (赞：6)

## 重点：数据太水（真的）！

我写这篇题解主要是给那些不懂队列的 OI ~~dalao~~ 们看的，纯dp！！

思路还是讲讲吧。。

首先 把a[ i ]转化成 a[ i ]-1。

dp[ i ][ j ]指的是 i 到 j 的最小代价。从1开始正向跑dp。

so：本题的核心代码是
```cpp
	minn=min(minn,dp[i-1][j]);
	dp[i][j]=minn+abs(a[i]-read[j]);
```
前一个最小值加上本次改动的绝对值。

好了，本蒟蒻这次的重点不是讲思路，前面大佬讲过了 ORZ（还有自己不会讲hahaha）

不过我不是光来~~水题解~~的，对，开头讲过，纯 dp或加一点点去重,不用队列

### No.1:去重优化
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
long long a[3100],read[3100],l,dp[3100][3100],n;
int main()
{
	memset(dp,0x3f3f3f3f,sizeof(dp));
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>read[i];
		read[i]-=i;
		a[i]=read[i];
	}
	sort(read+1,read+n+1);
	l=unique(read+1,read+n+1)-read-1;
	dp[0][1]=0;
	for(int i=1;i<=n;i++)
	{
		long long minn=0x3f3f3f3f3f3f;
		for(int j=1;j<=l;j++)
		{
			minn=min(minn,dp[i-1][j]);
			dp[i][j]=minn+abs(a[i]-read[j]);
		}
	}
	long long minn=0x3f3f3f3f3f3f;
	for(int i=1;i<=;i++)
	{
		minn=min(minn,dp[n][i]);
	}
	cout<<minn;
	return 0;
}
```
No.2:无优化
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
long long a[3100],read[3100],dp[3100][3100],n;
int main()
{
	memset(dp,0x3f3f3f3f,sizeof(dp));
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>read[i];
		read[i]-=i;
		a[i]=read[i];
	}
	sort(read+1,read+n+1);
	dp[0][1]=0;
	for(int i=1;i<=n;i++)
	{
		long long minn=0x3f3f3f3f3f3f;
		for(int j=1;j<=n;j++)
		{
			minn=min(minn,dp[i-1][j]);
			dp[i][j]=minn+abs(a[i]-read[j]);
		}
	}
	long long minn=0x3f3f3f3f3f3f;
	for(int i=1;i<=n;i++)
	{
		minn=min(minn,dp[n][i]);
	}
	cout<<minn;
	return 0;
}
```
并没有太多区别，不过不去重确实要废一些不必要的时间


---

## 作者：Tyyyyyy (赞：4)

# 朴素的dp做法
楼下dalao来了个$nlogn$，本蒟蒻来写一篇$O(n^2)$算法。

这题题目很好理解，就不具体分析了。

首先我们先来思考这样一个问题：

**给定一个序列，你每次可以修改其中一个数，请问要将这个序列变成严格递增序列，最少要操作多少次？**

假设当前序列中的元素为$a[i]$，符合题意的序列中，对应元素为$s[i]$。

首先，我们一定知道：**原序列是无序的**。

如何将一个无序的序列转化成有序的呢？

明确一个事实：**由数组下标依次组成的序列是严格递增的。**

那么我们将每一个$a[i]$减去$i$，假设得到的序列中对应的元素是$b[i]$。

不难证明：只要使得$b$数组变成不降序列，那么将每个$b[i]$加上$i$后，$a$数组一定严格递增。

什么？你问我怎么证明？

假设有$b[i]$，$b[j]$（$i<j$）

由于$b$数组已经修改完毕，所以一定有$b[i]<=b[j]$。

根据不等式的性质：$b[i]+i<b[j]+j$。

所以一定有$a[i]<a[j]$。

这道题只是把修改换为了加减，而思路完全是一样的。

$dp$方程非常基础：

$minx=min(minx,dp[i-1][j])$

$dp[i][j]=minx+abs(a[i]-b[j])$

不多解释，相信你都刷到紫题了，这点理解能力还是有的。

最后，避开一个关键的坑点：$1<=a_i<=10^9$。

一定要记住开$long long$！！！

AC代码如下：
```cpp
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#define ll long long
using namespace std;
ll n,a[3100],dp[3100][3100],s[3100],minx;//这里的s数组就是刚刚说的b数组
int main()
{
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++)
	{
		scanf("%lld",&s[i]);
		s[i]-=i;
		a[i]=s[i];
	}
	sort(s+1,s+n+1);
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=n;j++)
			dp[i][j]=1e18;
	dp[0][1]=0;
	for(ll i=1;i<=n;i++)
	{
		minx=1e18;
		for(ll j=1;j<=n;j++)
		{
			minx=min(minx,dp[i-1][j]);
			dp[i][j]=minx+abs(a[i]-s[j]);
		}
	}
	minx=1e18;
	for(ll i=1;i<=n;i++)minx=min(minx,dp[n][i]);
	printf("%lld",minx);
	return 0;
}
```

---

## 作者：YLWang (赞：3)

一只 $\log $ 的做法还是很有趣的。至少我不会。

首先考虑套路地 $a_i \leftarrow a_{i} - i$ 来把问题变成不下降。

那么容易发现一个 Lemma 就是最优解序列中不会出现原来没有的数。离散化再 dp 就可以了。

dp 式子在这里。

```cpp
For(i, 1, n) {
    For(j, 1, t)
        dp[i][j] = mn[i-1][j] + abs(disc[j] - disc[a[i]]);
    For(j, 1, t)
        mn[i][j] = min(mn[i][j-1], dp[i][j]);
}
```

然后我们发现这个 dp 性质非常优美，我们其实只关心最小值的位置。定义每一维的最小值出现的位置为 $x_i$。

- $x_{i-1} \leqslant a_i$。显然 $x_i = a_i$。

- $x_{i-1} \geqslant a_i$。作图或是感性分析可知 $x_i = x_{i-1}$。

然后就变成了一个容易维护的问题了。

代码满地飞就不贴了。


---

## 作者：liuyanxi2 (赞：1)

### DP+离散化O(n²)
## 题目分析

此题的重点在于离散化，因为这道题很明显是一道DP，那么我们就应该知道一下两点：

1.DP是如何定义的，有几维

2.DP的状态转移方程是什么

如何定义是非常简单的，大家都可以很快的想到：dp[i][j]表示从a[i]变为最终的b[i]的最小花费。

这下问题来了：a[i]和b[i]我不知道啊，这怎么DP！！！

现在我们就触及到了这道题的核心：离散化。


------------
## 离散化讲解

离散化，把无限空间中有限的个体映射到有限的空间中去，以此提高算法的时空效率。
通俗的说，离散化是在不改变数据相对大小的条件下，对数据进行相应的缩小。                            ——百度百科

很难懂是不是？那么我们就借这道题来讲解一下：

我们先理解一个东西：一个不降的序列加上一个上升的序列必然上升。

这很容易理解，其实就是不等式的加减。

所以我们就可以将题目中的序列a[i]都减去i，得到一个序列，如果他不下降，那么a[i]一定严格上升。来一个例子：

{1 3 8 12 15}

变化后变为{0 1 5 8 10}

所以现在我们只需要使这一个变化后的序列中不下降的元素尽量多，那么我们需要修改的次数就会尽量的少（最优）



------------
方程就很简单了，不再赘述：

mina=min(mina,dp[i-1][j]

dp[i][j]=mina+abs(a[i]-b[j])


------------


AC代码如下：

```
#include<bits/stdc++.h>
using namespace std;
long long n,m,dp[3010][3010],a[3010],re[3010];
int main ( )
{
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		a[i]-=i;
		re[i]=a[i];
	}
	sort(a+1,a+n+1);
	memset(dp,0x3f3f3f3f,sizeof(dp));
	dp[0][1]=0;
	for(long long i=1;i<=n;i++)
	{
		long long mina=0x3f3f3f3f3f3f;
		for(long long j=1;j<=n;j++)
		{
			mina=min(mina,dp[i-1][j]);
			dp[i][j]=mina+abs(re[i]-a[j]);
		}
	}
	long long minn=0x3f3f3f3f3f3f;
	for(long long i=1;i<=n;i++)
	minn=min(minn,dp[n][i]);
	cout<<minn;
	return 0 ;
}

```

本人蒟蒻一枚，如果题解有误，欢迎私信指正

---

## 作者：_Clown_ (赞：1)

# C.Sonya and Problem Wihtout a Legend
这道题目我们可以考虑直接上 STL。

我们一个数一个数地放进一个大根堆(优先队列)，

其实就是算到当前数时，

取前面最大的数出来。

假如现在这个数比前面最大数大或相等就没事，

反之我们则需要考虑如何改为不降。

我们肯定是将大的往小移，将小的往大移，

那么花费一定是 $|a-b|$。

为了不影响先前的答案，

当然都是移到同一基准，

即是先前的最大数。

代码不难写出。
```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
long long Total;
priority_queue< long long >Queue;
int main(void)
{
	BetterIO;
	#ifndef ONLINE_JUDGE
	freopen("IN.in","r",stdin);
	#endif
	register long long i;cin>>Total;
	register long long Ans(0);
	for(i=1;i<=Total;i++)
	{
		register long long Now;cin>>Now,Now-=i;
		Queue.push(Now);
		if(Queue.top()>Now)
		{
			Ans+=Queue.top()-Now;
			Queue.pop();
			Queue.push(Now);
		}
	}
	cout<<Ans<<endl;
	return 0;
}
```

---

