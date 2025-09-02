# Arithmetic Operations

## 题目描述

You are given an array of integers $ a_1, a_2, \ldots, a_n $ .

You can do the following operation any number of times (possibly zero):

- Choose any index $ i $ and set $ a_i $ to any integer (positive, negative or $ 0 $ ).

What is the minimum number of operations needed to turn $ a $ into an arithmetic progression? The array $ a $ is an arithmetic progression if $ a_{i+1}-a_i=a_i-a_{i-1} $ for any $ 2 \leq i \leq n-1 $ .

## 说明/提示

In the first test, you can get the array $ a = [11, 10, 9, 8, 7, 6, 5, 4, 3] $ by performing $ 6 $ operations:

- Set $ a_3 $ to $ 9 $ : the array becomes $ [3, 2, 9, 8, 6, 9, 5, 4, 1] $ ;
- Set $ a_2 $ to $ 10 $ : the array becomes $ [3, 10, 9, 8, 6, 9, 5, 4, 1] $ ;
- Set $ a_6 $ to $ 6 $ : the array becomes $ [3, 10, 9, 8, 6, 6, 5, 4, 1] $ ;
- Set $ a_9 $ to $ 3 $ : the array becomes $ [3, 10, 9, 8, 6, 6, 5, 4, 3] $ ;
- Set $ a_5 $ to $ 7 $ : the array becomes $ [3, 10, 9, 8, 7, 6, 5, 4, 3] $ ;
- Set $ a_1 $ to $ 11 $ : the array becomes $ [11, 10, 9, 8, 7, 6, 5, 4, 3] $ .

 $ a $ is an arithmetic progression: in fact, $ a_{i+1}-a_i=a_i-a_{i-1}=-1 $ for any $ 2 \leq i \leq n-1 $ .

There is no sequence of less than $ 6 $ operations that makes $ a $ an arithmetic progression.

In the second test, you can get the array $ a = [-1, 2, 5, 8, 11, 14, 17, 20, 23, 26, 29, 32, 35, 38] $ by performing $ 10 $ operations.

In the third test, you can get the array $ a = [100000, 80000, 60000, 40000, 20000, 0, -20000, -40000, -60000, -80000] $ by performing $ 7 $ operations.

## 样例 #1

### 输入

```
9
3 2 7 8 6 9 5 4 1```

### 输出

```
6```

## 样例 #2

### 输入

```
14
19 2 15 8 9 14 17 13 4 14 4 11 15 7```

### 输出

```
10```

## 样例 #3

### 输入

```
10
100000 1 60000 2 20000 4 8 16 32 64```

### 输出

```
7```

## 样例 #4

### 输入

```
4
10000 20000 10000 1```

### 输出

```
2```

# 题解

## 作者：伟大的王夫子 (赞：21)

设该等差数列首项 $a_0$。

假设原数列组成了一个等差数列，那么设 $d$ 为该数列公差，那么 $\forall i \in [1, n]$ 我们有 $a_i = a_0 + i \times d$。

假设 $d$ 确定了，那么我们有 $a_0 = a_i - i \times d$，其实就是求一下 $a_i - i \times d$ 的众数。这样就有了暴力的思路。

考虑到要维护的这个玩意较为奇怪，所以可以考虑根号分治。

具体的我们设置一个阙值 $lim$。当 $d \le lim$ 时，采用上述暴力算法。

当 $d > lim$ 时，由于 $a_i - i \times d = a_j - j \times d  \to (i-j) \times d=a_i-a_j \to i - j \le \dfrac{10^5}{lim}$ 。因此我们可以枚举首项 $a_i$，向后面的 $\dfrac{10^5}{lim}$ 个数进行统计即可，统计 $ \dfrac{a_i-a_j}{i-j}$ 的众数即可。

综合两部分的时间复杂度，总时间复杂度为 $O(n \times lim +n \times \dfrac{10^5}{lim})$。由于暴力我们要开一个桶来统计，所以空间复杂度为 $O(n \times lim)$。为了平衡时间与空间，我将阙值取为 300。注意因为公差可能为负，所以倒着也要求一遍。

个人认为我这篇题解写的相对较详细、规范，希望对同学们理解有帮助。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, a[N], C[N * 300 + 100000];
int solve() {
	int BB = 300, ans = 0;
	for (int d = 0; d <= BB; ++d) {
		int cnt = 0;
		for (int i = 1; i <= n; ++i) cnt = max(cnt, ++C[a[i] - i * d + 30000000]);
		for (int i = 1; i <= n; ++i) C[a[i] - i * d + 30000000] = 0;
		ans = max(ans, cnt);
	} 
	for (int i = 1; i <= n; ++i) {
		int cnt = 0;
		for (int j = i + 1; j <= n && (j - i) * BB <= 100000; ++j) 
			if ((a[i] - a[j]) % (i - j) == 0) cnt = max(cnt, ++C[(a[i] - a[j]) / (i - j) + 100000]);
		for (int j = i + 1; j <= n && (j - i) * BB <= 100000; ++j) 
			if ((a[i] - a[j]) % (i - j) == 0) C[(a[i] - a[j]) / (i - j) + 100000] = 0;
		ans = max(ans, ++cnt);
	}
	return n - ans;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	int ans = solve();
	reverse(a + 1, a + n + 1);
	ans = min(ans, solve());
	printf("%d", ans);
} 
```

---

## 作者：SunnyYuan (赞：15)

[更好的阅读体验](https://www.cnblogs.com/PlayWithCPP/p/17177518.html)

题目让我们求改变数字的最少次数，那我们转化一下，

求可以保留最多的数字个数 $cnt$，再用 $n$ 减一下就行，即 $res = n - cnt$。

我们先考虑两种暴力方法。

**第一种暴力方法：**

大体思路：因为要保留的最多，那么我们肯定要在众多等差数列中找能**对应数字最多**的那一个并保留下来。

首先，我们要知道一个概念。

![](https://cdn.luogu.com.cn/upload/image_hosting/ne2r09bw.png)


对于这道题，那么我们可以暴力枚举公差 $d$（就是数组中相邻两项的差值都是 $d$，并把题目中的每个 $a[i]$ 对应的等差数列的最后一项 $a[i] + d \times (n - i)$ 计算出来。

---

对于同一个公差 $d$，如果不同位置计算出来的序列的最后一个值相同，那就说明它们属于同一个等差数列。

![](https://cdn.luogu.com.cn/upload/image_hosting/396md7l0.png)

如果有 $x$ 个数字计算出来的最后一个值都相同，那么采用其对应的等差数列作为修改后的数组，这 $x$ 个数字是不需要改变的，只需要改变 $n - x$ 个数字。

那我们可以想到，用桶记录计算出来的值 $x$ 的出现次数 $a[x]$。如果某一次计算出来的值为 $x$，那么可以将 $a[x]$ 加 $1$。

如果 $a[x]$ 是 $a$ 中最大的元素，那么说明，以 $a[x]$ 为结尾的等差数列中存在的元素数量最多，那么更改数字的数量也就减少了，只需要 $n - a[x]$ 个元素。

这种方法的时间复杂度为 $O(DN)$，$D$ 为需要枚举的公差数量。

**第二种暴力方法：**

考虑动态规划，设 $f[i][j]$ 表示以 $a[i]$ 为**等差数列最后一个元素**的以 $j$ 为**公差**的等差数列**最多**可以保留的**数字个数**。

我们可以枚举上一个数字 $a[k]$，如果它与 $a[i]$ 在同一等差数列，那么有 $f[i][j] = f[k][j] + 1$，表示又可以多保存一个数字了。

那这个序列的公差是多少呢？

这样考虑，中间有 $i - k$ 个公差，差了 $a[i] - a[k]$，那么公差就是$\frac{a[i] - a[k]}{i - k}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/5ldi7dan.png)

如果除不尽怎么办呢，那么这就说明 $a[i]$ 和 $a[k]$ 不能在同一个等差数列，不然公差为小数！

那 $k$ 从哪里开始枚举呢？从 $1$ 开始是不是太慢了？

这个等会儿讲。

---

那么为了平衡这两种暴力算法，我们可以这样办：

取输入的数列 $a$ 的最大值 $m$。

**我们只使用第一种方法枚举 $[0, \sqrt m]$ 的部分，时间复杂度为 $O(n \sqrt m)$。**

**我们使用第二种方法枚举 $[\sqrt m + 1, n]$ 的部分。**

下面探讨第二种方法的时间复杂度，

首先回归到前面的问题，来探讨 $k$（$i$ 的上一位数字在哪里） 从何处开始枚举，到哪里。

到哪里好解决，就是 $i - 1$。

而开始的地方，是 $i - \sqrt m$。为啥呢？

首先，因为公差 $D$ 在 $[\sqrt m + 1, n]$ 之间，所以 $D > \sqrt m$，那么我们计算差值 $a[i] - a[k]  = (a[k] + (i - k) \times D) - a[k] = (i - k) \times D > (i - k) \times \sqrt m$。

首先假设 $i, k$ 都在同一个等差数列中，如果 $k+ \sqrt m < i$，那么$a[i] - a[k] > (i - k) \times \sqrt m > \sqrt m \times \sqrt m = m$，这样的话，两数之差竟然比 $m$ 还要大，不成立，

所以 $k + \sqrt m \geq i$，也就是说 $k$ 要从 $i - \sqrt m$ 开始枚举。

**所以，第二种方法的时间复杂度为 $O(n \sqrt m)$。**

**那么这个题的时间复杂度就为 $O(n \sqrt m)$。**

代码：

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

const int N = 100010;

int n;
int a[N], maxx, sqrtmaxx;

int u[(int)(N + N * sqrt(N))];                        // 第一种暴力方法的桶
unordered_map<int, int> f[N];                // 第二种暴力方法的动态规划数组。

int max_keep() {
    int ans = 0;
    for (int d = 0; d <= sqrtmaxx; d++) {    // 第一种暴力方法，枚举公差 D
        for (int i = 1; i <= n; i++) {
            ans = max(ans, ++u[a[i] + (n - i) * d]);
        }
        for (int i = 1; i <= n; i++) {
            u[a[i] + (n - i) * d]--;
	}
    }
    
    for (int i = 1; i <= n; i++) {                         // 第二种暴力方法，动态规划
        for (int j = max(1, i - sqrtmaxx); j < i; j++) {// j只用从 i - sqrt(m) 开始枚举
            if ((a[i] - a[j]) % (i - j) == 0) {
                int x = (a[i] - a[j]) / (i - j);
                if (x <= sqrtmaxx) continue;
                f[i][x] = max(f[i][x], f[j][x] + 1);
                ans = max(f[i][x] + 1, ans);
            }
        }
    }
    
    for (int i = 1; i <= n; i++) f[i].clear();    // 清空数组
    
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], maxx = max(maxx, a[i]);
    sqrtmaxx = sqrt(maxx);
    
    int ans1 = 0, ans2 = 0;
    ans1 = max_keep();
    reverse(a + 1, a + n + 1);                       // 应对公差为负数的情况
    ans2 = max_keep();
    
    cout << n - max(ans1, ans2) << '\n';
    return 0;
}
```

---

## 作者：Little09 (赞：6)

容易发现，题意可以转化为：对于所有公差 $k$，把序列第 $i$ 个数修改为 $a_i-i\times k$，最多有多少个相等的数。

当 $|k|\ge 10^5$ 时，必然不可能相等。因此只要考虑 $-10^5<k<10^5$ 的情况。

考虑两个数距离为 $dis$ 时，只有 $dis\times |k|\le 10^5$ 才可能相等。因此，当 $k$ 比较大的时候，每个数只可能和它后（前）面的 $\lfloor \dfrac{n}{k}\rfloor$ 个数相等。且如果 $i$ 位置与 $j$ 位置相等，$k$ 是可以唯一确定的。

根号分治即可。取阈值为 $lim$，第一部分暴力枚举公差 $O(lim\times n)$，第二部分枚举第一个相等的数以及它后面 $\lfloor \dfrac{n}{k}\rfloor$ 个数，复杂度 $O(\dfrac{n^2}{lim}$)。所以当 $lim=\sqrt{n}$，复杂度是 $O(n\sqrt{n})$。需要开 $O(n\sqrt{n})$ 大小的桶记录。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mem(x) memset(x,0,sizeof(x))
#define printYes puts("Yes")
#define printYES puts("YES")
#define printNo puts("No")
#define printNO puts("NO")
#define lowbit(x) (x&(-x))

const ll inf=1000000000000000000; 
//const ll mod=998244353;
//const ll mod=1000000007;

const int N=100005,B=321,K=N*B+2*N;
int n,m,ans; 
int a[N];

int b[N*B*2+4*N],c[N];

inline int read()
{
    int F=1,ANS=0;
	char C=getchar();
    while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
    while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
    return F*ANS;
}

int main()
{
	n=read();
	for (int i=1;i<=n;i++) a[i]=read();
	for (int i=-B;i<=B;i++)
	{
		for (int j=1;j<=n;j++)
		{
			b[a[j]-i*j+K]++;
			ans=max(ans,b[a[j]-i*j+K]);
		}
		for (int j=1;j<=n;j++)
		{
			b[a[j]-i*j+K]--;
		}
	}
	for (int i=1;i<=n;i++)
	{
		int r=min(n,i+B);
		for (int j=i+1;j<=r;j++)
		{
			int det=a[j]-a[i],len=j-i;
			if (det%len!=0) continue;
			int k=det/len;
			b[k+K]++;
			ans=max(ans,b[k+K]+1);
		}
		for (int j=i+1;j<=r;j++)
		{
			int det=a[j]-a[i],len=j-i;
			if (det%len!=0) continue;
			int k=det/len;
			b[k+K]--;
		}
	}
	cout << n-ans;
	return 0;
}
```


---

## 作者：enucai (赞：3)

## Preface

为什么各位代码这么长？喜提暂时最短代码。

## Analysis

很好的根号分治题目。要求解最少改几个，即求最多不改几个。

对于 $\le \sqrt n$ 的公差，考虑第一种解法：枚举公差。根据公差、每一个数的值与她的位置可以算出她所对应的首项，找到首项的众数即可。时间复杂度 $O(n\sqrt n)$。

对于 $>\sqrt n$ 的公差，考虑第二种解法：枚举首项位置。由于值域为 $[1,10^5]$，因此只要向后枚举 $\frac{10^5}{\sqrt n}$ 个数即可，因为只有这个区间内才会存在不用改的数。时间复杂度 $n\sqrt n$。

最终时间复杂的 $O(n\sqrt n)$，可以解决问题。注意用 map 统计数可能会 TLE，直接开桶（$6\times 10^7$）即可。注意分治点不能严格取在 $\sqrt n$，不然桶的空间太大，容易 MLE。

## Code

**Talk is cheap, show me the code.**

[Codeforces Status](https://codeforces.com/contest/1654/submission/150370501)

```cpp
// And in that light, I find deliverance.
#define int long long
#define B 30000000
int n,a[100010],cnt[2*B+10],ans=1e16;
signed main(){
	read(n);
	For(i,1,n) read(a[i]);
	For(i,-200,200){
		For(j,1,n) cnt[a[j]-i*j+B]++;
		int mx=0; For(j,1,n) ckmax(mx,cnt[a[j]-i*j+B]);
		For(j,1,n) cnt[a[j]-i*j+B]=0;
		ckmin(ans,n-mx);
	}
	For(i,1,n){
		For(j,i+1,min(n,i+500)) if((a[j]-a[i])%(j-i)==0) cnt[(a[j]-a[i])/(j-i)+B]++;
		int mx=0; For(j,i+1,min(n,i+500)) if((a[j]-a[i])%(j-i)==0) ckmax(mx,cnt[(a[j]-a[i])/(j-i)+B]);
		For(j,i+1,min(n,i+500)) if((a[j]-a[i])%(j-i)==0) cnt[(a[j]-a[i])/(j-i)+B]=0;
		ckmin(ans,n-mx-1);
	}
	cout<<ans<<endl;
}
```

---

## 作者：WeLikeStudying (赞：3)

- 希望独立思考。
- 希望全力以赴。
- 希望不留遗憾。

**题意**
- [链接](https://codeforces.com/problemset/problem/1654/E)。
- 给定一个数列 $a_i$，请问最少改动多少个数，可以使得这个数列变成一个全是整数的等差数列。
- 数列长度 $n$，值域 $w$ 不大于 $10^5$。
- 首先命题等价于找到一个等差数列使得它在序列内出现最多次。

**分析**
- 这题当时想了好久，我们先想水分做法吧，对于这种没啥性质的题目，想一个良好的水分做法有助于我们增强信心。
- 做法 $1$：暴力动态规划，设 $f(i,j)$ 表示以 $i$ 为终点，公差为 $j$ 的等差数列的最长长度，通过枚举终点前一个数，我们可以用 $O(n)$ 转移，空间复杂度 $O(nw)$，时间复杂度 $O(n^2)$。
- 做法 $2$：这是不是太麻烦了？如果公差 $d$ 直接确定，令 $b_i=a_i-i\cdot d$，然后我们用哈希表或者排序找到出现次数最多的数即可，时间复杂度 $O(n)$。
- 平衡一下？
- 当公差 $d\le \sqrt w$ 的时候，我们暴力枚举公差，时间复杂度 $O(n\sqrt w)$。
- 当公差 $d\ge \sqrt w$ 的时候，我们发现等差数列的长度是 $O(\sqrt w)$ 的，所以我们只需要找到 $O(\sqrt w)$ 前的元素即可，用哈希表维护，时间复杂度也是 $O(n\sqrt w)$ 的。
- 那么哈希表应该如何实现呢？我选择[无序关联式容器](https://oi-wiki.org/lang/csl/unordered-container/)。
- [代码实现](https://www.luogu.com.cn/paste/9ouc9di8)，调小块长就过了，原因是后面的操作很多都达不到，所以 $\text{DP}$ 常数小而枚举公差常数大。

**总结**
- 这题我一开始总是希望优美地利用数论的调和级数性质，但是如果强行利用的话，效果甚至不如普通的暴力，这对我也是一个很好的警醒，许多真正有用的算法。不一定是优美的。
- 同样，我们要重视暴力算法，许多暴力算法的思想可以产生意想不到的效果。
- 当然，这不一定是通用的，比如说[这题](https://www.luogu.com.cn/problem/CF1654C)，想要容易地发现贪心策略需要寻找到足够优美的性质，比如“同一层”的蛋糕除了“最后一层”外值域不交。
- 总地来说，要敢于尝试灵活多变的策略以解决问题。

---

## 作者：Presentation_Emitter (赞：2)

根号分治~~基础练习~~题。

题意：给出 $n$ 个点 $(i,a_i)$ 求一条斜率为整数且经过关键点最多的直线，输出 $n - num$，其中 $num$ 为经过点数。

枚举点对显然不可行。考虑对于每一个斜率 $k \in [-V,V]$（$V$ 为值域），统计最多的可能经过的点数。具体而言，开个桶 $cnt$ 统计所有点与直线 $y=kx$ 的竖直距离，之后用竖直距离的最大出现次数 $\max cnt_{a_i-ik}$ 更新答案。

直接做是 $\Theta(nV)$ 的，考虑优化。设一个阈值 $lim$。$\forall k \in [-V,-lim] \cup [lim,V]$，可能对答案造成影响的只有其左右约 $\lfloor{2V\over lim}\rfloor$ 个点，暴力枚举这些点，开桶统计更新答案。具体实现时可以只考虑左侧的点。

$\forall k \in (-lim,lim)$，暴力统计即可。

总时间复杂度 $\Theta({nV \over lim}+n \cdot lim)$，$n,V$ 视为同阶时取 $lim=\sqrt{n}$ 时平衡。实际实现时由于 `cache miss` 等原因，取 $lim=64$ 较优。

~~赛时阈值调成 400，差点 FST~~。

Code:

```cpp
cst int lim=64,cnt=(99999+lim)/lim,mx=100000*lim;
int n,a[100005],ans,tot[mx+1000005];
int main()
{
	n=rd();ans=n-1;for(int i=1;i<=n;++i)a[i]=rd();
	for(int i=1;i<=n;++i)
	{
		int l=umax(1,i-cnt);
		for(int j=l;j<i;++j)
		{
			int dx=j-i,dy=a[j]-a[i],t=dy/dx;
			if(dy-t*dx)continue;//equal to dy%dx!=0
			tomin(ans,n-1-(++tot[t+mx]));
		}
		for(int j=l;j<i;++j)tot[(a[j]-a[i])/(j-i)+mx]=0;
	}
	for(int d=0;d<=lim;++d)
	{
		for(int i=1;i<=n;++i)tomin(ans,n-(++tot[mx+a[i]-i*d]));
		for(int i=1;i<=n;++i)tot[mx+a[i]-i*d]=0;
		for(int i=1;i<=n;++i)tomin(ans,n-(++tot[a[i]+i*d]));
		for(int i=1;i<=n;++i)tot[a[i]+i*d]=0;
	}
	prt(ans);
	ret 0;
}
```

---

## 作者：lmy_2011 (赞：1)

### 首先说明：
本文转载于[此](https://blog.csdn.net/nth2000/article/details/123792679?ops_request_misc=&request_id=&biz_id=102&utm_term=CF24E&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-6-123792679.142^v65^opensearch_v2,201^v3^control,213^v2^t3_esquery_v1&spm=1018.2226.3001.4187)
### 思路：
#### 暴力思路：
看到数据范围，应该想到 $\mathrm{O}(n\sqrt{n})$ 的暴力算法：

1. 逆向过程，考虑**没被修改的**元素个数，由于一定大于等于 $2$，因此数列最终公差一定产生于两个元素之间。
2. 考虑**枚举所有正数公差**，也就是当 $0\leq d$ 时。（$d<0$ 只需要将数组反转按大于 $0$ 求解）

通过上面的分析，其实这道题就可以转化成：
对于每个给定的 $d$，用 $\mathrm{O}(n)$ 求解数组中等差数列最长长度。

之后，等差数列性质分析：
- 对于等差数列 $a_i,a_j,i<j$，一定有：$a_i-i=a_j-j$，因此维护键值为  $a_i-i,\forall i$ 的桶，每遇到一个对应键值就将桶中的值加上 $1$，最终桶中数量最大值就是答案。

但如果枚举所有 $d$，由于 $d \leq 10^5$，所以 $\mathrm{O}(n\cdot d)$ 会超时。

#### 剪枝优化：
首先我们得明白以下几点：
1. 当 $d$ 较大时，考察数组中最终没变化的两个元素，其下标差距应该较小，因为 $d$ 很大时，由于等式两侧的 $i$ 与 $j$ 占据主导地位，如果下标差距较大，那么等式不等的概率就很大。
2. 考虑 $\mathrm{O}(n\sqrt{n})$ 的形式，设 $m$ 为数组中元素最大值，这也是 $d$ 的上界。
3. 如果 $d>\sqrt{m}$，那么 $j-i$ 至多为 $\sqrt{m}$。


这意味着当 $d>\sqrt{m}$ 时，对于每个元素，只需最多向后查看 $\sqrt{m}$ 个元素，使用动态规划确定当前公差下最多的个数。

### 后续：
这种方法不像其他大佬那么牛，但不过思路很清晰明了，适用于初学算法的人。

---

## 作者：I_am_Accepted (赞：1)

### Preface

场上一眼**根号分治**，然后写了个劣的 $n^{5/3}$ 死活卡不过去。（差一点点啊 qwq）

### Analysis

要让序列中变化的位置最少等价于不变的最多，我们求后者。$V=10^5$ 为值域。 

对**最终等差序列的公差** $D$ 进行分治。

若 $|D|<B$，枚举每一种 $D$，设 $b_i=a_i-i\cdot D$，则问题转化为求 $\{b\}$ 的众数。

若 $|D|\ge B$，枚举序列中第一个不用变化的位置 $x$，则只有在 $[x,x+\frac{V}{B}]$ 中才可能有不变化的位置，记录这些位置与 $x$ 构成的可能公差进行求众数。

时间

$$O(nB\log n+n\frac{V}{B}\log \frac{V}{B})$$

$B$ 大概取 $\sqrt{V}$ 即可，最终时间 $O(n\sqrt{V}\log (n+\sqrt{V}))$。

### Code

[Link](https://codeforces.com/contest/1654/submission/150708751)

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2300}$
---
### 解题思路：

如果确定公差 $k$，可以将直接计算出每一个位置上对应的 $a_0$，取出 $a_0$ 相同的项就是没有被更改的。处理一个 $k$ 的复杂度为 $O(n)$。

但是这个做法在 $k$ 较大的时候就很差，表现为 $a_i$ 相对 $k$ 不大，只有少数的几个数是有用的。这种情况下，有用的数局限在 $\dfrac{10^5}{k}$ 中，考虑直接枚举两个位置求出强制保留两个数的公差，对于这些公差求众数。

将两种方法结合，取阈值 $\sqrt n$，最后总复杂度为 $O(n\sqrt n)$。

---
### 代码：

```cpp
#include<algorithm>
#include<cstdio>
#include<map>
using namespace std;
const int MAXN=100005;
int n,a[MAXN],ans,m[80000005];
int work_1(int num){
	int maxn=0;
	for(int i=1;i<=n;i++)maxn=max(maxn,++m[a[i]-i*num+40000000]);
	for(int i=1;i<=n;i++)m[a[i]-i*num+40000000]--;
	return maxn;
}
int work_2(int p){
	int maxn=0,len=350;
	for(int i=1;i<=min(len,n-p);i++){
		if((a[i+p]-a[p])%i==0)m[(a[i+p]-a[p])/i+40000000]++;
		if(m[(a[i+p]-a[p])/i+40000000]>maxn)maxn=m[(a[i+p]-a[p])/i+40000000];
	}
	for(int i=1;i<=min(len,n-p);i++){
		if((a[i+p]-a[p])%i==0)m[(a[i+p]-a[p])/i+40000000]--;
	}
	return maxn+1;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	for(int i=-350;i<=350;i++)ans=max(ans,work_1(i));
	for(int i=1;i<=n;i++)ans=max(ans,work_2(i));
	printf("%d\n",n-ans);
	return 0;
}
```


---

## 作者：laboba (赞：0)

设 $d=a_i-a_{i-1}$，$A$ 为 $a$ 的值域，注意到 $A$ 与 $n$ 同阶，又对于原数组中最终没有被修改的 $a_i$，$a_j$，$a_j-a_i=(j-i)\times d$，而 $a_j-a_i$ 是与 $a$ 的值域同阶的，也就是说，“相邻两数之差”与“数的个数”似乎满足一种乘积恒定且偏小的关系，这种关系启示我们这可能是一道诈骗分块讨论题。

有了这种猜测，不妨先考虑 $d$ 较小的情况，暴力枚举 $d$ 的大小，则只要确定最终的 $a_1$，整个数列就确定了，而对于一个确定的 $d$，能使一个 $a_i$ 不被修改的 $a_1$ 是唯一的，因此我们只需要一个桶，记录 $a_i-(i-1)\times d$ 这个值出现的次数，出现最多的就是最优的 $a_1$，复杂度 $O(nd)$。

对于 $d$ 较大的情况，相应的，最终未被修改的两个数之间的距离小于 $\dfrac{A}{d}$，因此对于每一个 $i$，可以直接枚举上一个未被修改的位置 $j$，考虑dp，令 $f_{i,k}$ 表示前 $i$ 个数公差为 $k$ 时最多有多少数可以不修改，第二维用哈希表来存，则 $f_{i,(a_i-a_j)/(i-j)}=min(f_{j,(a_i-a_j)/(i-j)}+1)$，其中 $j$ 只需要取大于等于 $i-\dfrac{A}{d}$，复杂度 $O(\dfrac{nA}{d})$

至此，两种情况都已解决，只要令 $d=\sqrt n$ 复杂度就可以取到 $O(n\sqrt n)$。

不知道为啥常数大到飞起www，时限也开到了5s，实测 $d$ 取小些常数似乎可以有效降低

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<unordered_map>
#include<cassert>
using namespace std;
const int N=101000,M=33000000;
int a[N],q[N];
unordered_map<int,int>mp[N];
int mpp[M*2+1];
int main(){
	int n;
	scanf("%d",&n);
	int tmp=0;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),tmp=max(tmp,a[i]);
	int m=120;
	int sum=-1e7,ans=0;
	for(int i=1;i<=n;i++){
		for(int j=i-1;i-j<=tmp/m&&j>=1;j--){
			if((a[i]-a[j])%(i-j))continue;
			int d=(a[i]-a[j])/(i-j);
			if(!mp[j][d])mp[j][d]=1;
			mp[i][d]=max(mp[i][d],mp[j][d]+1),ans=max(ans,mp[i][d]);
		}
	}
	for(int i=-m;i<=m;i++){
		int tot=0;
      //j*i与(j-1)*i相同道理的
      //这里没有用map不然常数太大
		for(int j=1;j<=n;j++)mpp[a[j]-j*i+M]++;
		for(int j=1;j<=n;j++)ans=max(ans,mpp[a[j]-j*i+M]);
		for(int j=1;j<=n;j++)mpp[a[j]-j*i+M]=0;
	}
	printf("%d",n-ans);
}
```


---

## 作者：max67 (赞：0)

## 前言

QAQ，SHJ 清华大佬 tql

## 正文

### 题意

给你一个长度为 $n$ 的序列 $a$，你可以进行任意次操作，每次可以把 $a_i$ 改成任意一个数。要求最小的操作次数使得满足以下条件：

* $\forall i\in [1,n),a_i+d=a_{i+1}$，其中 $d$ 是一个固定数。

$1\le n\le 10^5$

$1\le a_i\le 10^5$

## 题解

看到这种奇奇怪怪的题（总感觉在哪里看到过）一般都是分块。因为 $1\le a_i\le 10^5$，那么就是提示我们往值的方向想（我按位置分块想了两个小时成功爆炸）。

* 按 $a_i$ 的值分块。然后你就会考虑所有 $a_i-a_j\le \sqrt 10^5$ 的情况，成功排除。

* 按公差排序，大概率是正解（实际上是的）。

我们考虑公差大于 $\sqrt n$ 的序列，他最多有 $\sqrt n$ 项（这跟度数有异曲同工之妙）。因为有了那么一个特殊的性质，所以我们往这方面考虑。

因为最大独立集等于最小点覆盖（除了装 $B$ 没用）,所以操作最小的次数相当于找最大的满足条件的等差数列。

* 公差小于等于 $\sqrt n$。则分别枚举每个公差，再枚举 $i$ 和 $j$（$i<j$），若满足 $a_j-a_i=(j-i)\times d$，则他们可以组成一个等差数列。事实上这样的复杂度为 $O(n^2\sqrt n)$，考虑优化。

* 把式子拆开，有 $a_j-j\times d=a_i- i\times d$，我们可以把 $a_i- i\times d$ 存进数组（用 map 会 T）$O(1)$ 转移，复杂度为 $O(n\sqrt n)$

* 公差大于 $\sqrt n$，则枚举 $i$，再枚举下面的 $\sqrt n$ 项。考虑对于一个公差，统计所有在范围内满足条件的数，即所有的 $a_j-a_i=(j-i)\times d$。因为对于每个数最多枚举 $\sqrt n$ 项公差，则复杂度为 $O(n\sqrt n)$。

然后代码就很好写啦。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,M=sqrt(N)+1;
int n,m;
int a[N];
int mp[2*N*M+100];
int work1()
{
    int res=1;
    for(int j=0;j<=m;j++)
    {
        for(int i=1;i<=n;i++)res=max(res,++mp[a[i]-i*j+N*M]);
        for(int i=1;i<=n;i++)mp[a[i]-i*j+N*M]=0;
    }
    return res;
}
int dp1[N];
int work2()
{
    int res=1;
    for(int i=n;i>=1;i--)
    {
        for(int j=i+1;j<=min(n,i+m+10);j++)
        {
            if(a[i]>a[j]||(a[j]-a[i])%(j-i)!=0)continue;
            int t=(a[j]-a[i])/(j-i);dp1[t]++;
            res=max(res,dp1[t]+1);
        }
        for(int j=i+1;j<=min(n,i+m+10);j++)
        {
            if(a[i]>a[j]||(a[j]-a[i])%(j-i)!=0)continue;
            dp1[(a[j]-a[i])/(j-i)]=0;
        }
    }
    return res;
}
int main()
{
    scanf("%d",&n);m=sqrt(1e5);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    int ans=max(work1(),work2());
    reverse(a+1,a+n+1);
    ans=max({work1(),work2(),ans});
    printf("%d",n-ans);
    return 0;
}
```

---

