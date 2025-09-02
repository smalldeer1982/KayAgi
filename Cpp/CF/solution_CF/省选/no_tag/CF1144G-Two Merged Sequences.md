# Two Merged Sequences

## 题目描述

最初存在两个整数序列，其中一个是严格递增的，另一个是严格递减的。

严格递增序列是整数序列 $[x_1 < x_2 < \dots < x_k]$。严格递减序列是整数序列 $[y_1 > y_2 > \dots > y_l]$。注意，空序列和只包含一个元素的序列也可以视为递增或递减序列。

递增序列的元素被插入到递减序列的元素之间（也可能插入到递减序列的第一个元素之前或最后一个元素之后），且不改变递增序列和递减序列各自的顺序。例如，序列 $[1, 3, 4]$ 和 $[10, 4, 2]$ 可以生成如下结果序列：$[10, \textbf{1}, \textbf{3}, 4, 2, \textbf{4}]$，$[\textbf{1}, \textbf{3}, \textbf{4}, 10, 4, 2]$。但如下序列不能作为插入结果：$[\textbf{1}, 10, \textbf{4}, 4, \textbf{3}, 2]$，因为递增序列的元素顺序被改变了。

设最终得到的序列为 $a$。该序列 $a$ 已在输入中给出。你的任务是找出任意一组符合要求的初始序列，其中一个为严格递增序列，另一个为严格递减序列。注意，空序列和只包含一个元素的序列也可以视为递增或递减序列。

如果输入存在矛盾，无法将给定序列 $a$ 拆分为一个递增序列和一个递减序列，请输出 "NO"。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
9
5 1 3 6 8 2 9 0 10
```

### 输出

```
YES
1 0 0 0 0 1 0 1 0 
```

## 样例 #2

### 输入

```
5
1 2 4 0 2
```

### 输出

```
NO
```

# 题解

## 作者：platelett (赞：25)

> [题目链接](https://codeforces.com/problemset/problem/1144/G) [可能更好的体验](http://coding-pages-bucket-3532178-8430896-13917-522304-1305159063.cos-website.ap-hongkong.myqcloud.com/CF1144G/)
>
> 给定一个长度为 $n$ 的序列 $A$。
>
> 问能否把它拆成一个严格递增序列和一个严格递减序列，如果有解则输出方案。
>
> $n \le 2 \cdot 10^5$

设 $f_{i,0}$ 表示把序列的前 $i$ 个数拆成一个递增序列和一个递减序列（可以为空），并且 $A_i$ 属于递增序列时，递减序列结尾可能的最大值。$f_{i,1}$ 表示 $A_i$ 属于递减序列时，递增序列结尾可能的最小值。

转移有四种：

- $A_{i-1},A_i$ 都属于递增序列，条件是 $A_{i-1} < A_i$，转移为 $f_{i-1,0} \rightarrow f_{i,0}$ 。
- $A_{i-1},A_i$ 都属于递减序列，情况类似。
- $A_{i-1}$ 属于递减序列，$A_i$ 属于递增序列，条件是 $f_{i-1,1} < A_i$，转移为 $A_{i-1} \rightarrow f_{i,0}$。
- $A_{i-1}$ 属于递增序列，$A_i$ 属于递减序列，情况类似。

为了输出方案，记 $g_{i,0}$ 表示在最优方案中 $A_{i-1}$ 属于哪个序列，$g_{i,1}$ 同理。

实现中可以用 ```pair <int, int>``` 把 ```f``` 和 ```g``` 数组压一起。

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define per(i, r, l) for(int i = (r); i >= (l); i--)
#define mem(a, b) memset(a, b, sizeof a)
#define For(i, l, r) for(int i = (l), i##e = (r); i < i##e; i++)
#define fi first
#define se second
#define mp make_pair

using namespace std;
const int N = 2e5 + 5;
int n, A[N], in[N];
pair <int, int> f[N][2], ans;
int main() {
	cin >> n;
	rep(i, 1, n) scanf("%d", &A[i]);
	f[1][0].fi = N, f[1][1].fi = -1;
	rep(i, 2, n) {
		f[i][0].fi = -1, f[i][1].fi = N;
		if(A[i - 1] < A[i]) f[i][0] = {f[i - 1][0].fi, 0};
		if(A[i - 1] > A[i]) f[i][1] = {f[i - 1][1].fi, 1};
		if(f[i - 1][1].fi < A[i]) f[i][0] = max(f[i][0], mp(A[i - 1], 1));
		if(f[i - 1][0].fi > A[i]) f[i][1] = min(f[i][1], mp(A[i - 1], 0));
	}
	if(~f[n][0].fi || f[n][1].fi < N) {
		puts("YES");
		in[n] = ~f[n][0].fi ? 0 : 1;
		per(i, n, 2) in[i - 1] = f[i][in[i]].se;
		rep(i, 1, n) printf("%d ", in[i]);
	} else puts("NO");
	return 0;
}
```

---

## 作者：zifanwang (赞：9)

考虑从左到右贪心加入每个数。

记 $x,y,a$ 分别表示**上升序列**的最后一个元素、**下降序列**的最后一个元素、当前要加入的元素。

- 若 $a\le x\land a\ge y$，可以直接输出 `NO` 了。

- 否则如果 $a\le x\lor a\ge y$，那就只有一种方案，直接更新 $x,y$。

- 下面考虑加到两个序列都合法的情况。若 $a_i=a_{i+1}$，则两种方案一样，两个数会一个加到上升序列，一个加到递减序列。若 $a_i<a_{i+1}$，则加到递减序列后 $a_{i+1}$ 就肯定会加到递增序列，这时如果再来个 $[a_i,a_{i+1}]$ 之间的数就不行了，所以 $a_i$ 肯定加到递增序列，$a_i>a_{i+1}$ 的情况同理（一定加到递减序列）。

参考代码：

```cpp
#include<bits/stdc++.h>
#define mxn 200003
#define rep(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
int n,d1,d2,a[mxn];
signed main(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&a[i]);
	d1=-1,d2=2e9;
	rep(i,1,n){
		if(a[i]>d1&&(a[i]>=d2||a[i]<a[i+1]))d1=a[i],a[i]=0;
		else if(a[i]<d2)d2=a[i],a[i]=1;
		else{
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	rep(i,1,n)printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：xyin (赞：3)

题目其实分为两部分，第一步让你判断该序列是否合法，第二步让你进一步输出~~合法状态下~~每个 $i$ 属于递增 or 递减。

## PART 1

**状态设计**：

* 设 $dp_{i,0}$ 表示 $i$ 放在**递减**序列时，**递增**序列的**最小值**（设为最小值是为了方便我们贪心转移）。

* 设 $dp_{i,1}$ 表示 $i$ 放在**递增**序列时，**递减**序列的**最大值**（最大值同理）。

**初始化**：

```cpp
for (int i=1;i<=n;i++)
	  dp[i][1]=-INF,dp[i][0]=INF;//后面取 max 和 min
      //只有当我们遍历结束时，dp[n][1] 和 dp[n][0] 都还是初始值时，该序列不合法
dp[1][0]=-INF;dp[1][1]=INF;//起始端点当然是合法的
```

**转移方程式**：

* $i$ 放在递增序列时，此时 $dp_{i,1}$ 的转移为：

1. $i-1$ 也放在递增序列，$dp_{i,1}$ 可由 $dp_{i-1,1}$ 转移过来（条件：$a_{i-1}$ 到 $a_i$ 递增）。

```cpp
if (a[i]>a[i-1]) dp[i][1]=max(dp[i][1],dp[i-1][1]);
```

2. $i-1$ 放在递减序列，此时 $dp_{i,1}$（递减序列的最大值）可由 $a_{i-1}$ 转移（条件：$i$ 能放在递减序列）。

```cpp
if (dp[i-1][0]<a[i]) dp[i][1]=max(dp[i][1],a[i-1]);
```

* $dp_{i,0}$ 的转移同理，建议自己推 $dp$ 方程式。

这时我们就有了一个 $O(n)$ 的做法来判断该序列是否合法啦。

## PART 2

$dp$ 推完后，我们第二步就好做了，其实判断 $i$ 属于递增还是递减有很多方法，这里就简单说一下我的判断方法。

我们**从后往前**逆推，记录一下此时递增序列的第一个值（设为 $nxt1$）和递减序列的第一个值（设为 $nxt2$），（~~由于是从后往前，此时 $i$ 位置之后答案的已经求得了，递增和递减中也只放入了 $i$ 位置之后的元素，所以是记录“第一个值”~~）。

此时你可能会遇到两种情况：

* $dp_{i,0}\ne \infty$ 并且 $dp_{i,1}\ne -\infty$ （也就是两个 $dp$ 值都合法），此时比较一下 $nxt2$ 与 $a_i$ 的大小，如果符合递减原则（$a_i>nxt2$），就统计答案，并更新 $nxt2$，同理反过来也一样。

* $dp_{i,0}\ne \infty$ 或 $dp_{i,1}\ne -\infty$（也就是只有一个 $dp$ 值合法）说明该位置只能放在递减序列（或递增序列）此时直接更新 $nxt2$（或 $nxt1$）就好。

**注意！！！**：放在递减序列输出 $1$，递增序列输出 $0$。

**代码实现**：

```cpp
int n,a[maxn],dp[maxn][2];
int nxt1=INF,nxt2=-INF,vis[maxn];
void solve(){
	for (int i=n;i>=1;i--){
		if (dp[i][0]!=INF&&dp[i][1]!=-INF){
			if (a[i]>nxt2) vis[i]=1,nxt2=a[i];
			else nxt1=a[i];
		}
		else if (dp[i][0]!=INF) vis[i]=1,nxt2=a[i];
		else nxt1=a[i];
 	}
}
signed main(){
	n=read();
	for (int i=1;i<=n;i++)
	  a[i]=read();
	for (int i=1;i<=n;i++)
	  dp[i][1]=-INF,dp[i][0]=INF;
	dp[1][1]=INF,dp[1][0]=-INF;
	for (int i=1;i<=n;i++){
		if (a[i]>a[i-1]) dp[i][1]=max(dp[i-1][1],dp[i][1]);
		if (dp[i-1][0]<a[i]) dp[i][1]=max(a[i-1],dp[i][1]);
		if (a[i]<a[i-1]) dp[i][0]=min(dp[i-1][0],dp[i][0]);
		if (dp[i-1][1]>a[i]) dp[i][0]=min(a[i-1],dp[i][0]);
	}
	if (dp[n][1]==-INF&&dp[n][0]==INF) 
	  {printf("NO");return 0;}
	printf("YES\n");solve();
	for (int i=1;i<=n;i++)
	  printf("%d ",vis[i]);
	return 0;
}
```

贴一个这题的强化版 [Decinc Dividing](https://www.luogu.com.cn/problem/CF1693D)（需要计算一个序列的合法字段共有多少，但 $dp$ 设计是相同的）。

---

## 作者：wucstdio (赞：3)

这是一道贪心题。

从前往后，我们记录一下上升子序列和下降子序列的第一个元素，分别记为$x_1$和$x_2$，那么对于一个元素$a_i$，如果$a_i>x_1$，那就放到上升子序列里，否则就放到下降子序列里，都不行就无解。

那么同时满足的情况呢？这时显然不能随便乱放，否则容易出现下面这种情况：

![](https://cdn.luogu.com.cn/upload/pic/61440.png)

其中红色是贪心得到的解，绿色是正确的方法。

我们发现，这个算法错就错在它让两个序列提前产生了交点，从而导致处于中间的数字无解。

于是我们就想到了一个改进方法：我们再记录一下两个序列的上一个数字，如果$x_1>x_2$，并且这两个数字可以交换，那么就把它们交换。

经过这样一番调整，我们发现上面的样例在处理到第四个点的时候会把两个序列末尾的数字交换，从而不会出现问题。

然而你发现仍然是WA on test 15，这启示我们不得不去找反例。

经过一通分析，我们画出了下面这一组样例：$6,1,3,5,2,4$

![](https://cdn.luogu.com.cn/upload/pic/61441.png)

我们发现，当处理到第四个点的时候，由于我们错误地把第三个点放到了上升子序列里，导致第四个点只能放到下降子序列里并无法更改，从而使得第六个点无解。

进一步分析我们发现，在处理到第四个点的时候，如果我们能把第三个点从上升子序列里放到下降子序列里，那么就可以得到正确的解。

注意到，第三个点放到下降子序列里并不会造成下降子序列的最小元素变小，反而会使得上升子序列的最大元素变小。

于是我们再开一个$pre$数组表示每一个点的前驱。当处理到一个点的时候，我们不断检查其中一个序列的结尾元素能不能丢到另一个序列里去，能就丢进去。

这样你发现可能需要写一个平衡树来查询。但是其实并不需要，我们只需要检查能不能放到另一个序列的结尾两个元素之间就行了。因为如果它只能放到中间的某两个元素之间，一定在之前就已经被处理了。

时间复杂度$O(n)$

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,_a[200010],*a=_a+5,ans[200005],now1,last1,now2,last2,_pre[200010],*pre=_pre+5;
int main()
{
	scanf("%d",&n);
	a[-3]=-2;
	a[-2]=-1;
	a[-1]=1000000000;
	a[0]=999999999;
	pre[-2]=-3,pre[0]=-1;
	now1=-2,last1=-3,now2=0,last2=-1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[now1]>a[now2]&&a[now1]<a[last2]&&a[now2]>a[last1]&&now1>last2&&now2>last1)
		{
			swap(ans[now1],ans[now2]);
			swap(now1,now2);
			swap(pre[now1],pre[now2]);
		}
		while(now1>last2&&now1<now2&&a[now1]<a[last2]&&a[now1]>a[now2])
		{
			pre[now1]=last2;
			pre[now2]=now1;
			ans[now1]^=1;
			last2=now1;
			now1=last1;
			last1=pre[last1];
		}
		while(now2>last1&&now2<now1&&a[now2]>a[last1]&&a[now2]<a[now1])
		{
			pre[now2]=last1;
			pre[now1]=now2;
			ans[now2]^=1;
			last1=now2;
			now2=last2;
			last2=pre[last2];
		}
		if(a[i]>a[now1])
		{
			ans[i]=0;
			pre[i]=now1;
			last1=now1,now1=i;
		}
		else if(a[i]<a[now2])
		{
			ans[i]=1;
			pre[i]=now2;
			last2=now2,now2=i;
		}
		else
		{
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n");
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
	printf("\n");
	return 0;
}
```

---

## 作者：cirnovsky (赞：3)

给一个 much simpler 的做法，main idea 是动态维护严格递增子序列和严格递减子序列。

- 依序考虑每一个元素，考察能够加入递增 / 递减子序列；
  - 仅能够加入到递增子序列：加入即可；
  - 仅能够加入到递减子序列：加入即可；
  - 不能够加入到任意一个子序列：无解；
  - 同时能加入到两个子序列中：若该元素后面紧邻的第一个元素大于该元素，则加入递增子序列，否则加入递减子序列，易证正确性。

---

## 作者：NightDiver (赞：2)

首先我们考虑最暴力的方法，仿照着 LIS 板子题设计状态：$dp_{i,j}$ 表示考虑前 $\max(i,j)$ 个，单减序列以 $i$ 结尾，单增序列以 $j$ 结尾，然后进行 $O(1)$ 的转移。

但是这样状态数就爆炸了，如何优化状态数呢？

我们考虑进行换维。因为我们刚刚设计的是一个弱鸡的可行性 DP，很强力的“答案”这个位置上却被我们放上了 $0/1$ 这样信息很少的东西。

那么就考虑设 $f_i$ 表示单增序列以 $i$ 结尾，单减序列最后一项的最大值（浅浅运用贪心的思想，反正只要能分成两个序列就行了，没必要考虑长度的话，只要是已经考虑过的位置，它们之间的相对关系并不重要）。

开始打补丁，因为一个位置也有可能是单减序列的结尾，所以考虑再设一个 $g$。

设 $g_i$ 表示单减序列以 $i$ 结尾，单增序列最后一项的最小值。那么就可以交替转移了。

转移式子在代码里面。（如果对会不会漏掉情况有疑问，可以这样想：$f_i,g_i$ 是在考虑前 $i$ 位时的两个最优情况，其它的情况能匹配的接下来（$i$ 位之后）的方案，一定能是他们两个交集的子集）。

[代码在这里](https://www.cnblogs.com/TongKa/p/18418163)

---

## 作者：Sshenyyyu (赞：2)

~~这可能是我见过的最难的Div3题（一定是我太弱了才会这么想~~

这题有若干种做法，我把两个数列画成折线统计图的形式，发现只有一个交点（这是显然的），于是我们可以枚举这个交点位置，然后前后就可以直接固定下来（左边数字大于这个交点的为一组，小于的另一组，右边同理），然后我们就得到了一个O(n^2)的算法

考虑优化，我们用单调栈来优化，往单调栈中加元素时，把不符合的直接弹到另一组中如果发现两组都放不下，我们就找到了这个交点的前面一个数位置

对于这个位置，我们还要分情况看一下它属于递增还是递减序列，分别讨论一下就好啦

```cpp
#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
int n,i,sta[200005],ans[200005],top,a[200005],p;
bool flag=false;
bool check()
{
	int p;
	p=1<<30;
	for(i=1;i<=n;i++)
		if(ans[i]==1)
		{
			if(p<=a[i])
				return false;
			p=a[i];
		}
	p=-100000000;
	for(i=1;i<=n;i++)
		if(ans[i]==0)
		{
			if(p>=a[i])
				return false;
			p=a[i];
		}
	return true;
}
int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sta[top=1]=1;
	for(i=2;i<=n;i++)
	{
		if(a[i]==a[sta[top]])
			break;
		if(a[i]>=a[sta[top]])
		{
			if(top>1&&a[i]>=a[sta[top-1]])
				break;
			top--;
		}
		sta[++top]=i;
	}
	for(;i<=n;i++)
		if(a[i]<a[sta[top]])
			sta[++top]=i;
	for(i=1;i<=top;i++)
		ans[sta[i]]=1;
	if(check())
	{
		printf("YES\n");
		for(i=1;i<=n;i++)
			printf("%d ",ans[i]);
		return 0;
	}
	memset(ans,0,sizeof(ans));
	sta[top=1]=1;
	for(i=2;i<=n;i++)
	{
		if(a[i]==a[sta[top]])
			break;
		if(a[i]>=a[sta[top]])
		{
			top--;
			if(top>0&&a[i]>=a[sta[top]])
				break;
		}
		sta[++top]=i;
	}
	for(;i<=n;i++)
		if(a[i]<a[sta[top]])
			sta[++top]=i;
	for(i=1;i<=top;i++)
		ans[sta[i]]=1;
	if(check())
	{
		printf("YES\n");
		for(i=1;i<=n;i++)
			printf("%d ",ans[i]);
		return 0;
	}
	printf("NO");
}

```


---

## 作者：wnsyou (赞：1)

# [Two Merged Sequences](https://www.luogu.com.cn/problem/CF1144G)

推销[我的博客园](https://www.cnblogs.com/wnsyou-blog/p/18249863)。

## 题意

有一个长度为 $n$ 的序列 $a$，问能否将其拆成一个**严格递增子序列**和一个**严格递减子序列**。

若能，输出 YES 并在下一行给出方案，若不能，输出 NO。

输出方案的方法是对于每一位都输出 $0$ 或者 $1$，若输出 $0$ 表示其在递增序列中，否则在递减序列中。

### 数据范围

- $1 \leqslant n \leqslant 2 \times 10 ^ 5$。
- $0 \leqslant a_i \leqslant 2 \times 10 ^ 5$。

## 思路

与 xhr 和 cn 巨佬一起完善出来了思路。

考虑使用动态规划。

- 状态：$dp_{i,0/1}$ 表示序列第 $i$ 位作为递增序列或者递减序列时的最优情况，$0$ 代表在递增序列中，$1$ 代表在递减序列中。

那么最优化属性呢？很显然，当你把当前位作为当前递增序列的最后一个时，递减序列的最后一个数**越大越好**，反之，若你把当前位作为当前递减序列的最后一个时，递增序列的最后一个数**越小越好**。

那么 $dp_{i,0}$ 就表示序列第 $i$ 位作为递增序列时的最大递减序列末项的值，$dp_{i,1}$ 就表示序列第 $i$ 位作为递减序列时的最小递增序列末项的值。

那么转移就很显然了，这里拿 $dp_{i,0}$ 举例，$dp_{i,1}$ 也差不多。

当上一个数小于当前数时，上一个数作为递增序列的最后一个的状态便可以转移至当前数作为递增序列的最后一个的状态。而如果上一个数作为递减序列时的最小递增序列末项的值小于当前数，便可以让当前数接到上一个数作为递减序列时的递增序列之后，那么此时的递减序列末项值为 $a_{i-1}$。

总结如下：

- $dp_{i,0}=\begin{cases}-10^9\\10^9&i=1\\dp_{i - 1, 0}&a_{i-1}<a_i\\a_{i-1}&dp_{i-1,1}<a_i\end{cases}$ 取最大值。​
- $dp_{i,1}=\begin{cases}10^9\\-10^9&i=1\\dp_{i - 1, 1}&a_{i-1}>a_i\\a_{i-1}&dp_{i-1,0}>a_i\end{cases}$​ 取最小值。​

其中 $10^9$ 和 $-10^9$ 均为极值，可以自行调整，需保证极大值大于 $\max\limits _{1\leqslant i \leqslant n} \{a_i\} \leqslant 2 \times 10^5$，极小值小于 $\min\limits _{1\leqslant i \leqslant n} \{a_i\} \geqslant 0$​。

- 初始状态：$dp_{0,0}=10^9,dp_{0,1}=-10^9$。
- 合法目标状态：$dp_{n,0} \geqslant 0$ 和 $dp_{n,1} \leqslant 2 \times 10^5$。

那么怎么求出方案呢？很简单，用个数组记录当前状态是如何转移来的，最后逆推即可。

详细见代码。

### 复杂度

- 时间：$O(n)$。
- 空间：$O(n)$。

## Code

```cpp
#include <iostream>

using namespace std;

const int N = 2e5 + 10;

int n, a[N], dp[N][2], lst[N][2]; // lst 用于记录当前状态是如何转移来的，为 0 表示是由 dp[i - 1][0] 转移而来，否则由 dp[i - 1][1] 转移而来

void Output (int x, int y) { // 逆推求方案
  if (!x) {
    return ;
  }
  Output(x - 1, lst[x][y]);
  cout << y << ' ';
}

int main () {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n, dp[0][0] = 1e9, dp[0][1] = -1e9; // 初始状态
  for (int i = 1; i <= n; i++) {
    cin >> a[i], dp[i][0] = -1e9, dp[i][1] = 1e9;
    // 下面是四种转移方式
    if (a[i - 1] < a[i] || i == 1) {
      dp[i][0] = dp[i - 1][0], lst[i][0] = 0;
    }
    if (dp[i - 1][1] < a[i] && a[i - 1] > dp[i][0]) {
      dp[i][0] = a[i - 1], lst[i][0] = 1;
    }
    if (a[i - 1] > a[i] || i == 1) {
      dp[i][1] = dp[i - 1][1], lst[i][1] = 1;
    }
    if (dp[i - 1][0] > a[i] && a[i - 1] < dp[i][1]) {
      dp[i][1] = a[i - 1], lst[i][1] = 0;
    }
    // cout << dp[i][0] << ' ' << dp[i][1] << '\n'; // Debug
  }
  // 判断目标状态是否合法
  if (dp[n][0] != -1e9) {
    cout << "YES\n";
    Output(n, 0);
  } else if (dp[n][1] != 1e9) {
    cout << "YES\n";
    Output(n, 1);
  } else {
    cout << "NO";
  }
  return 0;
}
```

---

## 作者：yuanruiqi (赞：1)

### 题意简述

将序列 $a$ 分成一个严格递增子序列和一个严格递减子序列。

### 题目分析

可以使用贪心。

动态维护两个序列。一个数能否加入一个子序列，只和子序列的最后一个值有关。

即当这个数大于递增序列的末项时可以放进递增序列，

小于递减序列末项时可以加入递减序列。

记递增和递减序列的末项分别为 $great,less$，分析 $a_i$。

- $ a_i < great $ 并且 $ a_i > less $ ：则 $a_i$ 不能添加到任意序列，那么两个序列就此终结，无解。

- $ a_i < great $ 并且 $ a_i < less $ ：则 $a_i$ 只符合递减序列的条件，加入递减序列并更改 $ less \gets a_i $。

- $ a_i > great $ 并且 $ a_i > less $ ：则 $a_i$ 只符合递增序列的条件，加入递增序列并更改 $ great \gets a_i $。

- $ a_i > great $ 并且 $ a_i < less $ ：则 $a_i$ 符合两个递减序列的条件，此时分析 $ a_i $ 添加到一个序列对之后的影响。

	- 当 $a_i$ 加入到递增序列， 则 $great = a_i$ ， 考虑 $a_{i+1}$ 。
    
    	若 $a_{i+1} < a_i$ ，则 $ a_{i+1} < great $ 并且 $ a_{i+1} < less $。
        
      此时 $ a_{i+1} $ 会加入到递减序列，而当 $a_i$ 加入递减序列时， $a_{i+1}$ 同样能加入到递减序列，此时方案是劣的。
      
   - 所以当 $a_{i+1}<a_i$ 时，$a_i$ 加入到递减序列最优。
   
   - 同理当 $a_{i+1}>a_i$ 时，$a_i$ 加入到递增序列最优。
   
   - $a_i = a_{i+1} $ 时，$a_i$ 无论加入到那个序列，$a_{i+1}$ 都会加入到另一个序列，没有单独分类讨论的必要。

### 代码

```cpp
#include<cstdio>
using namespace std;
const int maxn = 200000 + 10;
const int inf = 0x3f3f3f3f;
int a[maxn];
int n, great=-inf, less=inf; 
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;++i) scanf("%d",&a_i);
    for (int i=1;i<=n;++i)
        if (a_i < less && a_i > great)
            if (a_{i+1} > a_i) great = a_i, a_i = 0;
            else less = a_i, a_i = 1;
        else if (a_i > great) great = a_i, a_i = 0;
        else if (a_i < less) less = a_i, a_i = 1;
        else return puts("NO"), 0;
    puts("YES");
    for (int i=1;i<=n;++i) printf("%d ",a_i);
    putchar('\n');
    return 0;
}
```

---

## 作者：OrezTsim (赞：1)

这个 trick 好像不是很常见啊，至少我之前没碰到过。

发现状态仅和前面某一个比它小 / 比它大的数有关，考虑将其放入状态。

贪心地想，对于递增序列，每一次最后的数越小越好，越可能找到合法解。

同理对于递减序列也有相同的贪心策略。

那么如何记录这个比它小 / 比它大的数呢？

考虑如果连续两个数都在同一类型的序列中，那么可以直接转移。

如果连续两个数 $a_{i-1},a_i$ 不在同一类型的序列中，必须要从 $i-1$ 处转移。

这样就得记录不同类型的信息。

那么考虑这样干。

$dp_{i,0}$ 表示 $a_i$ 属于递增序列时，递减序列的最后一个位置的最大值。

$dp_{i,1}$ 表示 $a_i$ 属于递减序列时，递增序列的最后一个位置的最小值。

1. $a_{i-1},a_i$ 均属于递增序列，则 $dp_{i,0}=dp_{i-1,0}$。

2. $a_{i-1},a_i$ 均属于递减序列，则 $dp_{i,1}=dp_{i-1,1}$。

3. $a_{i-1}$ 属于递减序列，$a_i$ 属于递增序列，则 $dp_{i,0}=a_{i-1}$。

4. $a_{i-1}$ 属于递增序列，$a_i$ 属于递减序列，则 $dp_{i,1}=a_{i-1}$。

这样转移就好了。

```cpp
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 2e5 + 10, inf = 1e9;
int n, a[N]; pair <int, int> dp[N][2];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    cin >> n; for (int i = 1; i <= n; ++i) cin >> a[i];
    dp[1][0].fi = inf, dp[1][1].fi = -inf;
    for (int i = 2; i <= n; ++i) {
        dp[i][0].fi = -inf, dp[i][1].fi = inf;
        if (a[i - 1] < a[i]) dp[i][0] = {dp[i - 1][0].fi, 0};
        if (a[i - 1] > a[i]) dp[i][1] = {dp[i - 1][1].fi, 1};
        if (dp[i - 1][1].fi < a[i]) dp[i][0] = max(dp[i][0], {a[i - 1], 1});
        if (dp[i - 1][0].fi > a[i]) dp[i][1] = min(dp[i][1], {a[i - 1], 0});
    }
    if (dp[n][0].fi <= -inf && dp[n][1].fi >= inf) return cout << "NO" << endl, 0;
    stack <int> st; int typ = 0; cout << "YES" << endl;
    if (dp[n][0].fi <= -inf) typ = 1; st.push(typ);
    for (int i = n; i > 1; --i) st.push(typ = dp[i][typ].se);
    while (!st.empty()) cout << st.top() << ' ', st.pop(); cout << endl;
    return 0;
}
```

---

## 作者：wz20201136 (赞：1)

### 题意

给定序列 $a_1,a_2,...,a_n$，求能否将其划分成两个子序列，使得其中一个子序列单调递增，另一个单调下降。

### 题解

考虑动态规划：

$dp_{i,0}$ 表示以 $i$ 结尾，$i$ 属于单调下降子序列，单调上升子序列结尾的最小值，$dp_{i,1}$ 同理。

转移时决策 $i-1$ 属于哪个子序列，并记录从哪转移。

注意赋值最小值时注意要赋 $-inf$，否则会在 #12 挂掉。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
int n,a[MAXN],dp[MAXN][2];
bool book[MAXN][2];
void out(int x,int y)
{
	if(x>1) out(x-1,book[x][y]);
	cout<<(y^1)<<' ';
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	dp[1][0]=-INT_MAX,dp[1][1]=INT_MAX;
	for(int i=2;i<=n;i++)
	{
		dp[i][0]=-1;
		if(a[i-1]>a[i]) dp[i][0]=dp[i-1][0];
		if(dp[i-1][1]!=-1&&dp[i-1][1]>a[i])
			if(dp[i][0]==-1||dp[i][0]>a[i-1]) dp[i][0]=a[i-1],book[i][0]=1;
		dp[i][1]=-1,book[i][1]=1;
		if(a[i-1]<a[i]) dp[i][1]=dp[i-1][1];
		if(dp[i-1][0]!=-1&&dp[i-1][0]<a[i])
			if(dp[i][1]==-1||dp[i][1]<a[i-1]) dp[i][1]=a[i-1],book[i][1]=0;
	}
	if(dp[n][1]==-1&&dp[n][0]==-1) return puts("NO")*0;
	puts("YES");
	int o=1;
	if(dp[n][0]!=-1) o=0;
	out(n,o);
	return 0;
}
```



---

## 作者：__vector__ (赞：0)

虽然我的做法比较唐，但好像没人用双端队列，就来交一个。    
### 做法  
假设现在考虑前 $i$ 个，且第 $i$ 个属于上升序列的。  

那么，贪心的想一下，显然是此时下降序列的最后一个数的值越大越好。  

设 $f_{i}$ 代表考虑前 $i$ 个数，第 $i$ 个数属于上升序列，此时下降序列的最后一个数的最大值是多少。  

转移的话，考虑上升序列中 $i$ 的前一个位置 $j$，分类讨论 $j \lt i-1$ 和 $j = i-1$，不存在 $j$ 三种情况。  
-  若 $j \lt i-1$。  
  那么只要存在一个合法的这样的 $j$，那么 $f_i \leftarrow a_{i-1}$。而一个 $j$ 合法的条件是 $f_{j} \gt a_{j+1}$，并且 $[j+1,i-1]$ 是严格降序。现在问题是怎么快速判定符合条件的 $j$ 是否存在。注意到 $f_j \gt a_{j+1}$ 这个条件仅和 $j$ 有关，考虑每计算出一个 $f_k$，若 $f_k \gt a_{k+1}$，那么将其加入一个双端队列的末尾，若 $a_k$ 小于等于双端队列的末尾对应位置的值，那么就把队尾弹出。这样就形成了一个值递增的单调队列。另外，观察第二个条件，容易发现其对于 $j$ 的限制是单调不降的，所以每次可以从双端队列头部弹出不符合第二个条件要求的位置。由于队列的值递增，此时最优的位置一定是队列第一个位置。  
- 若 $j=i-1$。  
只需要满足 $a_{i} \gt a_{i-1}$ 就行了，转移是 $f_{i} \leftarrow f_{i-1}$。
- 若 $j$ 不存在。  
  此时需要满足 $[1,i-1]$ 是严格递减，$f_i \leftarrow a_{i-1}$。

一个细节：可以令 $a_0 = \infty$，代表不存在递减序列时，递减序列最后一个数是无穷大，后面接什么都可以。  

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(auto i=(a);i<=(b);i++)
#define REP(i,a,b) for(auto i=(a);i>=(b);i--)
#define FORK(i,a,b,k) for(auto i=(a);i<=(b);i+=(k))
#define REPK(i,a,b,k) for(auto i=(a);i>=(b);i-=(k))
#define pb push_back
#define mkpr make_pair
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
template<class T>
void ckmx(T& a,T b){
    a=max(a,b);
}
template<class T>
void ckmn(T& a,T b){
    a=min(a,b);
}
template<class T>
T gcd(T a,T b){
    return !b?a:gcd(b,a%b);
}
template<class T>
T lcm(T a,T b){
    return a/gcd(a,b)*b;
}
#define gc getchar()
#define eb emplace_back
#define pc putchar
#define ep empty()
#define fi first
#define se second
#define pln pc('\n');
#define islower(ch) (ch>='a'&&ch<='z')
#define isupper(ch) (ch>='A'&&ch<='Z')
#define isalpha(ch) (islower(ch)||isupper(ch))
template<class T>
void wrint(T x){
    if(x<0){
        x=-x;
        pc('-');
    }
    if(x>=10){
        wrint(x/10);
    }
    pc(x%10^48);
}
template<class T>
void wrintln(T x){
    wrint(x);
    pln
}
template<class T>
void read(T& x){
    x=0;
    int f=1;
    char ch=gc;
    while(!isdigit(ch)){
        if(ch=='-')f=-1;
        ch=gc;
    }
    while(isdigit(ch)){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=gc;
    }
    x*=f;
}
const int maxn=2e5+5;
int n;
int a[maxn];
int des[maxn];
int dp[maxn];
int lst[maxn];
deque<int> okids;
bool added[maxn];
bool ans[maxn];
bool wait[maxn];
void solve(int id_of_test){
	read(n);
    bool alldes=1;
    FOR(i,1,n){
        read(a[i]);
    }
    FOR(i,2,n)alldes&=(a[i]>a[i+1]);
    if(alldes){
        puts("YES");
        FOR(i,1,n)printf("%d ",1);
        pln
        return;
    }
    FOR(i,1,n){
        if(a[i]<a[i-1])des[i]=des[i-1];
        des[i]++;
    }
    a[0]=1e9;
    dp[0]=1e9;
    FOR(i,1,n){
        
        bool can_be_add=0;
        int lim=i-1-des[i-1];
        while(!okids.empty()&&okids.front()<lim){
            okids.pop_front();
        }
        if(!okids.empty()&&a[okids.front()]<a[i]){
            ckmx(dp[i],a[i-1]);
            lst[i]=okids.front();
            can_be_add=1;
        }
        if(a[i]>a[i-1]&&added[i-1]){
            ckmx(dp[i],dp[i-1]);
            if(dp[i]==dp[i-1])lst[i]=i-1;
            can_be_add=1;
        }
        // 还有一种情况，它是第一个节点
        if(des[i-1]==i-1){
            ckmx(dp[i],a[i-1]);
            if(dp[i]==a[i-1])lst[i]=0;
            can_be_add=1;
        }
        if(a[i+1]<dp[i]&&can_be_add){
            wait[i]=1;
        }
        added[i]=can_be_add;
       
        if(wait[i-1]){
            while(!okids.empty()&&a[i-1]<=a[okids.back()])okids.pop_back();
            okids.eb(i-1);
        }
       // printf("lst[%d] = %d\n",i,lst[i]);
    }
    FOR(i,1,n)ans[i]=1;
    REP(i,n,n-des[n]){
        if(added[i]&&(i==n||a[i+1]<dp[i])){
            puts("YES");
            int nw=i;
            while(nw>=1){
                ans[nw]=0;
                nw=lst[nw];
            }
            FOR(i,1,n){
                printf("%d ",int(ans[i]));
            }
            pln
            return;
        }
    }
    puts("NO");
}
int main()
{
	int T;
	T=1;
	FOR(_,1,T){
		solve(_);
	}
	return 0;
}
```

---

## 作者：DerrickLo (赞：0)

提供一个神秘做法。

我们把在递增序列的数记为 $0$，在递减序列的数记为 $1$，则原序列变成一个 $0,1$ 序列。然后我们记 $f_{i,0/1}$ 表示第 $i$ 个数是 $0/1$ 连续段的开头是否可行，然后我们有转移：

$$f_{i,0}=\bigvee_{a_{j-1}<a_i,r_{j,1}\ge i-1}f_{j,1}$$

$$f_{i,1}=\bigvee_{a_{j-1}>a_i,r_{j,0}\ge i-1}f_{j,1}$$

其中 $r_{i,0/1}$ 表示从 $i$ 开始的最长递增或递减子序列。使用 set 维护所有 $r_{i,0/1}$ 满足要求的数，然后拿 set 里最小或者最大的数进行转移，再记录一个转移位置即可。时间复杂度 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200005],f[200005][2],lst[200005][2],r1[200005],r2[200005],ans,flag,cnt,b[200005];
vector<int>ve1[200005],ve2[200005];
pair<int,int>anss[200005];
multiset<pair<int,int>>st1,st2;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=n;i;i--){
		if(i==n||a[i]>=a[i+1])r1[i]=i;
		else r1[i]=r1[i+1];
		if(i==n||a[i]<=a[i+1])r2[i]=i;
		else r2[i]=r2[i+1];
	}
	for(int i=1;i<=n;i++)ve1[r1[i]+2].emplace_back(i),ve2[r2[i]+2].emplace_back(i);
	f[1][0]=f[1][1]=1,st1.insert(make_pair(1e18,1)),st2.insert(make_pair(-1e18,1));
	for(int i=2;i<=n;i++){
		for(int v:ve1[i]){
			int x=v==1?1e18:a[v-1];
			if(st1.find(make_pair(x,v))!=st1.end())st1.erase(st1.find(make_pair(x,v)));
		}
		for(int v:ve2[i]){
			int x=v==1?-1e18:a[v-1];
			if(st2.find(make_pair(x,v))!=st2.end())st2.erase(st2.find(make_pair(x,v)));
		}
		if(st1.size()>0&&(*st1.rbegin()).first>a[i])f[i][1]=1,lst[i][1]=(*st1.rbegin()).second;
		if(st2.size()>0&&(*st2.begin()).first<a[i])f[i][0]=1,lst[i][0]=(*st2.begin()).second;
		if(f[i][0])st1.insert({a[i-1],i});
		if(f[i][1])st2.insert({a[i-1],i});
	}
	for(int i=1;i<=n;i++){
		if(r1[i]>=n&&f[i][0])ans=i,flag=0;
		if(r2[i]>=n&&f[i][1])ans=i,flag=1;
	}
	if(!ans)cout<<"NO",exit(0);cout<<"YES\n";
	anss[0]={n+1,flag^1};
	while(ans){
		anss[++cnt]={ans,flag};
		ans=lst[ans][flag],flag^=1;
	}
	for(int i=1;i<=cnt;i++)for(int j=anss[i].first;j<anss[i-1].first;j++)b[j]=anss[i].second;
	for(int i=1;i<=n;i++)cout<<b[i]<<" ";
	return 0;
}
```

---

## 作者：yqr123YQR (赞：0)

### 分析
由于原序列会被拆分为单增 + 单降的序列，考察较为特殊的位置会对我们分析答案的形态有帮助，故对于最小值所属序列分讨（假设 $a_p$ 为最小值）：
1. 单降部分

   易知其位于单降部分的末尾，即 $\forall i>p$，$a_i$ 属于单增部分，且后半部分单增。现在问题转化为前半部分的分割，且分割成的两个序列均带值域上的限制。
2. 单增部分

   同理，$\forall i<p$，$a_i$ 属于单降部分，且前半部分单降，只需考虑后半部分。

但有时 $a_p$ 按上述条件检验，看起来既可以在单增部分，也可以在单降部分。

这时，容易看出方案的形态除了上面两种平凡情况，还会出现 $a_1$ 被接到上升部分且 $a_p$ 接到下降部分的情况。差不多是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/6xr5y13h.png)

类似地，还有另外一种。补上这两种情况，就解决了这道题目。[Submission](https://codeforces.com/contest/1144/submission/299564574).

### 代码
```cpp
//...
typedef long long ll;
typedef unsigned long long ull;
constexpr int maxn = 200005;
int n, a[maxn];
bool path[maxn];
struct segment_tree {//维护区间单调性
	struct node {
		int l, r, up, down, mn;
		friend node operator + (const node &a, const node &b)
		{
			return {a.l, b.r,
					a.up && b.up && a.r < b.l,
					a.down && b.down && a.r > b.l,
					::a[a.mn] <= ::a[b.mn]? a.mn: b.mn};
		}
	}s[maxn << 2];
	void pushup(int k) {s[k] = s[k << 1] + s[k << 1 | 1];}
	void build(int k, int sl, int sr)
	{
		if(sl == sr) return void(s[k] = {::a[sl], ::a[sl], 1, 1, sl});
		int mid = sl + sr >> 1;
		build(k << 1, sl, mid), build(k << 1 | 1, mid + 1, sr);
		pushup(k);
	}
	node query(int k, int sl, int sr, int ql, int qr)
	{
		if(ql <= sl && sr <= qr) return s[k];
		int mid = sl + sr >> 1;
		node ret;
		ret.l = -1;
		if(ql <= mid) ret = query(k << 1, sl, mid, ql, qr);
		if(qr > mid)
		{
			if(!~ret.l) ret = query(k << 1 | 1, mid + 1, sr, ql, qr);
			else ret = ret + query(k << 1 | 1, mid + 1, sr, ql, qr);
		}
		return ret;
	}
}tree;
int findmn(int l, int r) {return tree.query(1, 1, n, l, r).mn;}
bool down(int l, int r) {return l >= r || tree.query(1, 1, n, l, r).down;}
bool up(int l, int r) {return l >= r || tree.query(1, 1, n, l, r).up;}
void check(int l, int r, int dl, int dr, int ul, int ur)
{
	if(dl > dr || ul > ur) return;
	if(l > r)
	{
		puts("YES");
		for(int i = 1; i <= n; i++) printf("%d ", path[i]? 1: 0);
		exit(0);
	}
	int pos = findmn(l, r);//最小值所在位置
	// printf("[%d,%d]:%d [%d,%d][%d,%d]\n", l, r, pos, dl, dr, ul, ur);
	bool a = down(l, pos - 1), b = up(pos + 1, r);
	if(a && b)
	{
		// puts("3");
		for(int i = l; i < pos; i++) path[i] = 1;
		for(int i = pos + 1; i <= r; i++) path[i] = 0;
		if((pos == l || ::a[pos - 1] > ::a[pos]) && ::a[pos] > dl)
		{
			if(::a[l] < dr && (pos == r || ::a[pos + 1] > ul && ::a[r] < ur))
			{
				path[pos] = 1;
				puts("YES");
				for(int i = 1; i <= n; i++) printf("%d ", path[i]? 1: 0);
				exit(0);
			}
			if(pos > l && (pos == r || ::a[pos + 1] > ::a[l]) && (pos == r? ::a[l]: ::a[r]) < ur && ::a[l] > ul && ::a[pos] > dl && ::a[l + 1] < dr)
			{
				path[pos] = 1, path[l] = 0;
				puts("YES");
				for(int i = 1; i <= n; i++) printf("%d ", path[i]? 1: 0);
				exit(0);
			}
		}
		if(pos == r || ::a[pos + 1] > ::a[pos])
		{
			if(::a[r] < ur && (pos == l || ::a[pos - 1] > dl && ::a[l] < dr))
			{
				path[pos] = 0;
				puts("YES");//!
				for(int i = 1; i <= n; i++) printf("%d ", path[i]? 1: 0);
				exit(0);
			}
			if(pos < r && (pos == l || ::a[pos - 1] > ::a[r]) && (pos == l? ::a[r]: ::a[l]) < dr && ::a[r] > dl && ::a[pos] > ul && ::a[r - 1] < ur)
			{
				path[pos] = 0, path[r] = 1;
				puts("YES");
				for(int i = 1; i <= n; i++) printf("%d ", path[i]? 1: 0);
				exit(0);
			}
		}
		return;
	}
	if(b)//单降子序列末尾
	{
		path[pos] = 1;
		for(int i = pos + 1; i <= r; i++) path[i] = 0;
		if(r > pos)
		{
			if(::a[r] >= ur) return;
			ur = ::a[pos + 1];
		}
		check(l, pos - 1, ::a[pos], dr, ul, ur);
	}
	if(a)//单增子序列开头
	{
		// puts("2");
		path[pos] = 0;
		for(int i = l; i < pos; i++) path[i] = 1;
		if(l < pos)
		{
			if(::a[l] >= dr) return;
			dr = ::a[pos - 1];
		}
		check(pos + 1, r, dl, dr, ::a[pos], ur);
	}
}
int main()
{
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; i++) read(a[i]);
	tree.build(1, 1, n);
	check(1, n, -1, maxn, -1, maxn);
	puts("NO");
	return 0;
}
```

---

## 作者：良心WA题人 (赞：0)

同学推荐的神秘 trick 题，但是疑似被我弱智的注意到结论给秒了（？

## 思路

注意到第一个数一定是其中一个序列的第一个数，则分类处理第一个数属于上升还是下降的序列。这里先考虑上升序列，另一种全部取相反数后可以使用相同方法完成。

若当前数可以加入上升序列则直接加入，否则考虑它是否大于这个序列的倒数第二个数。因为若出现 $i<j$ 且 $a_i<a_j$，则这两个数无法同时放到另一个序列。那么若小于了序列倒数第二个数就必须将这个数放到下降序列。

此时考虑这个上升序列选择当前数还是原来的结尾。若不考虑另一个序列，则一定取当前数更优，因为结尾更小了，未来放入上升序列的数的空间更大了。那么我们记录之前的结尾在当时能否放入下降序列，若能放入，则用当前数替换掉原来的结尾。

考虑为什么是对的，若之前的结尾 $i$ 被替换后另一个序列不递减，则存在另一个序列的一个位置 $j>i$ 使得它满足 $a_j>a_i$，则这个 $j$ 必然被加入了上升序列。

可以发现每次操作都是最优且合法的，故该贪心正确。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=2e5+4;
int q[NN],a[NN],head,tail,n;
bool flag[NN];
bool solve()
{
	head=0,tail=0;
	q[0]=1;
	memset(flag,false,sizeof(false));
	for(int i=2,minn=1e9;i<=n;i++)
	{
		if(a[i]<minn)
			flag[i]=true;
		if(a[i]>a[q[tail]])
			q[++tail]=i;
		else if(head<tail&&a[i]>a[q[tail-1]])
		{
			if(flag[q[tail]])
			{
				minn=min(a[q[tail]],minn);
				q[tail]=i;
			}
			else
			{
				if(a[i]>=minn)
					return false;
				minn=a[i];
			}
		}
		else
		{
			if(a[i]>=minn)
				return false;
			minn=a[i];
		}
	}
	return true;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	if(solve())
	{
		puts("YES");
		for(int i=1,j=0;i<=n;i++)
			if(q[j]==i)
			{
				j++;
				printf("0 ");
			}
			else
				printf("1 ");
		return 0;
	}
	for(int i=1;i<=n;i++)
		a[i]=-a[i];
	if(solve())
	{
		puts("YES");
		for(int i=1,j=0;i<=n;i++)
			if(q[j]==i)
			{
				j++;
				printf("1 ");
			}
			else
				printf("0 ");
		return 0;
	}
	printf("NO");
	return 0;
}
```

---

## 作者：forest114514 (赞：0)

### CF1144G Two Merged Sequences

首先我们考虑如何检验一个子段是否合法，这让我们想到了 **Bipartite Array** 这道题，那题中是划分为两个单调递增子序列，而这题是一个单增一个单减的子序列。

类似的贪心拓展，在长度一定时，我们尽量让递增子序列的末项最小，递减子序列的末项最大，意会一下，这样贪心一定是最优的。所以我们令 $f_{i,0}$ 为 $a_i$ 位于单增子序列时，单减子序列最后一位的最大值；$f_{i,1}$ 为 $a_i$ 位于单减子序列时，单增子序列最后一位的最小值，就很容易沿着左端点去 DP，如果最后一位能够被化为某一个子序列中，这就说明整个数组是合法的。

状态转移方程：
$$
f_{i-1,0}\to\begin{cases}f_{i,1}=a_{i-1}&(f_{i-1,0}>a_i)\\f_{i,0}=f_{i-1,0}&(a_i>a_{i-1})\end{cases}
$$
$$
f_{i-1,1}\to\begin{cases}f_{i,1}=f_{i-1,1}&(a_i<a_{i-1})\\f_{i,0}=a_{i-1}&(f_{i-1,0}<a_{i})\end{cases}
$$

至于输出方案，我们可以在 DP 时记录一个 $ch$ 数组记录每一个转移时的决策，直接递归输出就可以了。

说一句，这题还有一个加强版让我们求出有多少个合法的子段，仿照上文转态转移方程我们以 $f_{i,0}$ 为例，我们知道 $f_{i,0}\in{\{a_{i-1},f_{i-1,0},\operatorname{inf},\operatorname{-inf}\}}$，那么 $f_{i-1,0}$ 与 $a_{i-1}$ 只会后面影响最多 $4$ 个数的决策，$f_{i-1,1}$ 同理，所以每次可以从一个左端点直接转移，遇见不能拓展就更新拓展到的右端点，与之前的状态相同时就跳过转移继承之前的右端点，可以证明每个 $a_{i}$ 只会最多更新一个常数次，也能 $O(N)$ 解决这个加强版问题。

CODE：
```cpp
const int N=2e5+100;
int n,a[N],ch[N][2],f[2];
void output(int pos,int c){
	if(pos>1) output(pos-1,ch[pos][c]);
	write(c,' ');
}
signed main(){
	read(n);
	rep(i,1,n)read(a[i]);
	f[0]=inf,f[1]=-inf;
	rep(i,2,n){
		int F0=-inf,F1=inf;
		if(f[0]>a[i]) F1=a[i-1],ch[i][1]=0;
		if(a[i-1]<a[i]&&i) F0=f[0],ch[i][0]=0;
		if(i&&a[i-1]>a[i]&&f[1]<F1) F1=f[1],ch[i][1]=1;
		if(f[1]<a[i]&&a[i-1]>F0) F0=a[i-1],ch[i][0]=1;
		f[0]=F0,f[1]=F1;
	}
	if(f[0]==-inf&&f[1]==inf){
			return puts("NO"),0;
	}
	puts("YES");
	if(f[0]!=-inf) output(n,0);
	else output(n,1);
	return 0;
}
```

---

