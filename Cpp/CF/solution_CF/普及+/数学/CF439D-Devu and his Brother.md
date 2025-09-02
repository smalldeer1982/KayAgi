# Devu and his Brother

## 题目描述

给予两个数组 $a$ 和 $b$，每次操作可以使 $a$ 和 $b$ 中的任意元素加 $1$ 或减 $1$，求使得 $a$ 中的最小值大于等于 $b$ 中的最大值的最小步数。

## 说明/提示

$1<=n,m<=10^5$

$1<=a_i , b_i<=10^9$

## 样例 #1

### 输入

```
2 2
2 3
3 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 2
1 2 3
3 4
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3 2
4 5 6
1 2
```

### 输出

```
0
```

# 题解

## 作者：metaphysis (赞：6)

首先指出一个题意翻译的问题。原题目描述为“you are allowed to decrease or increase any element of any of the arrays by 1.”，意思是你可以更改两个数组中的任意一个中的任意一个元素，而题目翻译的“题目描述”中的“每次操作可以使 $a$ 中的任意元素加 $1$ 或减 $1$”，这不符合原题。

初看似乎一点思路都没有，但仔细在阅读了一遍题目后，发现了重点所在：he wants the minimum value of his array a should be at least as much as the maximum value of his brother's array b.

假设经过最少次数的调整，使得数组达到了约束条件，将数组 $a$ 和 $b$ 升序排列，那么可以知道必有 $a[0] \geq b[m-1]$。这让我联想到了快速排序中以基准值为界，右侧的数据均大于基准值，左侧的数据均小于基准值的特征，但是题目和快排有关系么？似乎没有方向。

考虑 $n$ 和 $m$ 都是 $10^5$ 级别，数组 $a$ 和 $b$ 中的元素最大为 $10^9$ 级别，暴力肯定是不行的，初略估算了一下，$10^9$ 的 2 的对数为 30，$30×10^5$ 为3百万，似乎在暗示着有一种复杂度为 $nlog_2n$ 的巧妙方法。

搜索大脑中的 $nlog_2n$ 算法中......

联想到经过操作后右侧数据大于左侧数据，以及复杂度为 $nlog_2n$，是不是和二路归并有关？逆序对数？好像也不对。

思路暂时陷入困境。出去外面走了一圈，边走边想，似乎是放松了的缘故，思维中的那个转折点一下就到了。

由于经过调整后，$a$ 中的最小元素需要大于 $b$ 中的最大元素，怎么调整的暂时先不管它，先把两个数组排好序，必定可以找到一个数 $x$ 使得 $b[m-1] \leq x \leq a[0]$，而且这个数是很容易确定的。这让我想起了最大值最小化问题（给定由 $n$ 个正整数构成的序列，要求将其划分为 $k$ 个部分，$1 \leq k \leq n$，使得这 $k$ 个部分的元素和的最大值尽可能的小）：直接求最小值不可行，但是给定一个值 $x$，验证是否能够使得划分的最大值不超过 $x$ 却很容易。那么是否可以枚举一个值 $x$，使得调整后所有 $a$ 中的元素均大于等于 $x$，$b$ 中的元素均小于等于 $x$ 呢？这显然很容易。

如果我们把 $x$ 定为 $b[m-1]$，那么只需将数组 $a$ 中元素从第一个开始往后进行检查，只要 $a[i]$ 小于 $x$，就将其调整到 $x$，直到某个 $a[i] \ge x$ 时结束，此时可以得到一个调整次数 $y$，不难推知，如果把 $x$ 定得再大一些，那么数组 $a$ 中就可能有更多的元素需要调整，使得 $y$ 增大，因此朝比 $b[m-1]$ 更大的方向调整 $x$ 必将使得调整次数 $y$ 增大。

那么 $x$ 的下限值可以定多少呢？将 $x$ 定得越小，数组 $a$ 中的元素越有可能不需调整，但是数组 $b$ 中的元素可能越来越多的需要调整，因此不难推知调整次数的变化趋势不是单调下降或者单调上升的过程，但由于题目约束了两个数组中的元素最小值为 $1$，令 $x=1$ 时的调整次数为 $z$，当把 $x$ 定得更低的时候，$z$ 肯定会增大。结合 $n$ 和 $m$ 都是 $10^5$ 级别，数组 $a$ 和 $b$ 中的元素最大为 $10^9$ 级别的暗示，以及 $x$ 定在两个极端可能都不是最优值，暗示调整次数的变化曲线很可能是一个抛物线函数，三分搜索！

只要想到了三分搜索，题目立马得到解决。

以下是参考代码（提交时间：$2020-03-27 22:20:01$，运行时间：$5.37s$。第一次提交的时候，由于考虑不周全，将 $left$ 定为 $b[0]$ 导致错误，将 $left$ 定为 $1$ 即获得 $Accepted$）。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int a[MAXN], b[MAXN], n, m;
    
long long f(int x)
{
    long long sum = 0;
    for (int i = 0; i < n; i++)
        if (a[i] < x) sum += x - a[i];
        else break;
    for (int i = m - 1; i >= 0; i--)
        if (b[i] > x) sum += b[i] - x;
        else break;
    return sum;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n >> m)
    {
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < m; i++) cin >> b[i];
        sort(a, a + n);
        sort(b, b + m);
        int left = 1, right = b[m - 1], r;
        while (left <= right)
        {
            int leftThird = left + (right - left) / 3;
            int rightThird = right - (right - left) / 3;
            if (f(leftThird) > f(rightThird)) r = rightThird, left = leftThird + 1;
            else r = leftThird, right = rightThird - 1;
        }
        cout << f(r) << '\n';
    }

    return 0;
}
```

关于本题的讨论参见：[CF439D](https://www.luogu.com.cn/discuss/show/208091)。

有空请访问我的[CSDN博客](https://blog.csdn.net/metaphysis)，里面有我写的一本关于编程竞赛的书，附有相关应用题目（题目源自UVa OJ），可免费下载此书的PDF版本：[《C++，挑战编程——程序设计竞赛进阶训练指南》](https://blog.csdn.net/metaphysis/article/details/90288252)。


---

## 作者：AKPC (赞：5)

### 思路
指出一个翻译的错误：$b$ 数组的元素也是可以加或减 $1$ 的。

首先一个错误的结论，就是不能直接给 $\min\{a\}$ 加到 $\max\{b\}$ 或者相反。因为数列的最值不一定总是同一个位置上的元素，最值的位置可能会在操作中途发生改变。

但是改变数列，肯定是改每次的最值，这就是贪心思想了。所以先给两个数列排序，$a$ 升序，$b$ 降序。遍历 $i=1\sim \min\{n,m\}$，如果 $a_i\geq b_i$ 显然达成了目标，直接退出，否则就需要进行操作让 $a_i=b_i$，显然次数为 $b_i-a_i+1$。那就这样扫就了事了。

总的来说，答案就是先排序，然后计算 $\displaystyle\sum_{i=1}^{\min\{n,m\}}(b_i-a_i)x$，其中如果遇到了 $a_i\geq b_i$ 的情况，则 $x$ 立即设为 $0$，之后也就为 $0$，相当于退出循环，反正 $x$ 保持为 $1$。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[100001],b[100001],ans;
inline bool comp(int o,int p){return o>p;}
signed main(){
	cin>>n>>m;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=m;i++) cin>>b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+m+1,comp);
	for (int i=1;a[i]<b[i]&&i<=n&&i<=m;i++) ans+=b[i]-a[i];
	cout<<ans;
	return 0;
}
```


---

## 作者：C6H14 (赞：4)

## 一点废话

[题目传送门](https://www.luogu.com.cn/problem/CF439D)

[My blog](https://www.luogu.com.cn/blog/128433/#)

调了一个上午的贪心……差点暴毙。

题目翻译有问题，其实 $b$ 也是可以修改的（所以还是练练英语吧）。

## 题目大意

给你两个数组 $a$ 和 $b$，每一步可以使任意一个数加 $1$ 或者减 $1$，问最少用多少步才能使 $\min\limits_{1 \leqslant i \leqslant n} a_i\geqslant \max \limits_{1 \leqslant i \leqslant m} b_i$。

## 思路

你应该想到一点：如果要修改数字，肯定会优先修改 $a_i$ 中的最小值或 $b_i$ 中的最大值。

那么我们把 $a$ 升序排序，$b$ 倒序排序，$a[1]$ 就是 $a$ 中最小值，$b[1]$ 就是 $b$ 中最大值。

抛开其他数不管，先处理 $a[1]$ 和 $b[1]$：

1. $a[1] \geqslant b[1]$，那就不用修改了；

1. $a[1] < b[1]$，那我们肯定要将 $a[1]$ 和 $b[1]$ 都修改成一个数$x$，并且 $x$ 满足 $a[1] \leqslant x \leqslant b[i]$，此时不管 $x$ 是多少，都需要修改 $b[1]-a[1]$ 次。

修改完后惊喜的发现，对于 $a[2]$ 和 $b[2]$、$a[3]$ 和 $b[3]$……结论是一样的。

那么答案就出来了：

把 $a$ 升序排序，$b$ 倒序排序，从左往右扫一遍数组，只要 $a[i] < b[i]$，答案就加上 $b[i] - a[i]$；否则直接退出循环。

## 代码

```cpp
typedef long long ll;
int n,m,l=1;
ll a[100005],b[100005],ans;
int main()
{
	n=read(),m=read();
	for (int i=1;i<=n;i++)
		a[i]=read();
	for (int i=1;i<=m;i++)
		b[i]=read();
	sort(a+1,a+1+n);
	sort(b+1,b+1+m,greater<ll>());
	while (a[l]<b[l] && l<=n && l<=m)//l用于扫描数组
	{
		ans+=b[l]-a[l];
		++l;
	}
	write(ans);
	return 0;
}
```


---

## 作者：wxzzzz (赞：3)

### 思路

这种题的关键在于画图。

图示样例 $2$（红色方块代表排序后的 $a$ 序列，绿色方框代表倒排后的 $b$ 序列）：

![](https://cdn.luogu.com.cn/upload/image_hosting/digdn1un.png)

显然，答案就是绿色方框的独立部分方块数量。

解释：要使 $a$ 中的最小值大于等于 $b$ 中的最大值，这些方块无论如何也要被消除或被红色填上。

最后，记得开 long long！

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, m, ans, maxn, a[100005], b[100005];
inline bool cmp(long long x, long long y) {
    return x > y;
}
int main() {
	cin >> n >> m;
	
    for (long long i = 1; i <= n; i++)
        cin >> a[i];

    for (long long i = 1; i <= m; i++)
        cin >> b[i];

    sort(a + 1, a + 1 + n);
    sort(b + 1, b + 1 + m, cmp);

    for (long long i = 1; i <= min(n, m); i++) {
        if (a[i] >= b[i])
            break;

        ans += b[i] - a[i];
    }

    cout << ans;
    return 0;
}
```

---

## 作者：hanzhongtlx (赞：3)

题目链接：[CF439D Devu and his Brother](https://www.luogu.com.cn/problem/CF439D)              
~~太困肝了一晚上也没肝出来，被大佬虐爆了。~~              
考虑这个结论：如果需要操作才能实现要求，那这个数一定是$a$,$b$中的数。          
为什么呢，你可以尝试设此数为$k$，写出其函数解析式，则一定是一次函数，单调性明显，一定出现在两端点上。           
考虑对答案有贡献：         
显然是$a$数组中$<k$和$b$数组中$>k$的数才有贡献，这时我们直接枚举每一个数，然后二分查找边界值，当然要处理出前缀和，为什么呢？   
$ps$:下面的数组都是从小到大排序意义上的：             
比如说我们要把$max_a$和$min_b$都趋近于$k$,这时$a$数组中前$x$个数$<k$，$b$数组中$b_y$到$b_m>k$，那么我们记$sum_{a/b,i}$为前缀和，则贡献为：
$$kx-sum_{a,x}+sum_{b,m}-sum_{b,y-1}-k(m-y+1)$$      
记得开$long\;long$,这样复杂度就是$O((n+m)\log(n+m))$，可以通过本题。      
另外讨论区还有三分的做法，笔者不会，所以有兴趣就去讨论区看吧（咕咕~ 
## $Code$:
```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;
typedef long long ll;
const ll inf=1ll<<61;
int a[MAXN],b[MAXN];
ll suma[MAXN],sumb[MAXN],ans=inf;
int mina=2147483647,maxb=0;
int n,m;
int mm;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),mina=min(mina,a[i]);
	for(int i=1;i<=m;i++) scanf("%d",&b[i]),maxb=max(maxb,b[i]);
	if(mina>=maxb){
		printf("%d\n",0);
		return 0;
	}
	sort(a+1,a+n+1),sort(b+1,b+m+1);
	for(int i=1;i<=n;i++) suma[i]=suma[i-1]+(ll)a[i];
	for(int i=1;i<=m;i++) sumb[i]=sumb[i-1]+(ll)b[i];
	for(int i=1;i<=n;i++){
		if(a[i]>=b[m]) break;
		int l=1,r=m,mid;
		while(1){
			mid=(l+r)>>1;
			if(l>=r) break;
			if(b[mid]<=a[i]) l=mid+1;
			else r=mid;
		}
		ll now=(ll)a[i]*(ll)(i-1)-suma[i-1];
		if(mid>0) now=now+sumb[m]-sumb[mid-1]-(ll)a[i]*(ll)(m-mid+1);
		if(now<ans) ans=now,mm=a[i];
	}
	for(int i=1;i<=m;i++){
		if(b[i]<a[1]) continue;
		int l=1,r=n,mid;
		while(1){
			mid=(l+r)>>1;
			if(l>=r) break;
			if(a[mid]<=b[i]) l=mid+1;
			else r=mid;
		}
		mid-=1;
		if(b[i]>=a[n]) mid=n;
		ll now=sumb[m]-sumb[i]-(ll)b[i]*(ll)(m-i);
		now=now+(ll)b[i]*(ll)mid-suma[mid];
		if(ans>now) ans=now,mm=b[i];
	}
	printf("%lld\n",ans);
	return 0;
} 

```
大佬xxx:你好傻啊，这么麻烦，其实核心代码只有一行，这么$naive$的贪心都不会。        
我：？？？      
索性盗了一份代码，谁会证明呢，大佬可以在讨论区秀一秀？       
## $Code$(神仙贪心):
```
#include <bits/stdc++.h>
#define gc() getchar() 
#define LL long long
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define _rep(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
const int N = 1e5 + 5;
int n, m, a[N], b[N];

inline int read() {
	int x = 0;
	char ch = gc();
	while (!isdigit(ch)) ch = gc();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = gc();
	return x; 
}

inline bool cmp(int x , int y) {
	return x > y;	
}

int main() {
	n = read(), m = read();
	rep(i, 1, n) a[i] = read();
	rep(i, 1, m) b[i] = read();
	sort(b + 1, b + m + 1, cmp);
	sort(a + 1, a + 1 + n);
	if (n > m) n = m;
	LL ans = 0;
	rep(i, 1, n) if (a[i] < b[i]) ans += 1LL * (b[i] - a[i]);
	printf("%lld\n", ans);
	return 0;
} 
```
这样的复杂度是$O(n\log n+m\log m+n+m)$，比我的快多了，%%%。       
给个赞呗~

---

## 作者：ST_AS_IS_ZHY (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF439D)

## 题意

现在有了两个数列 $a$ 和 $b$，要求我们通过将数列中某个数加一或减一的方法来让 $a$ 中的最小值大于等于 $b$ 中的最大值。

## 思路

首先简化问题，考虑一种简单情况，现在我们拥有两个数 $x$ 和 $y$，如果只通过加减一的方法来让 $x$ 大于等于 $y$，显见无论用什么方法都需要操作至少 ```x-y``` 次。

接下来推广到题目，我们需要序列 $a$ 中每一个数都大于等于 $b$ 中的任何一个数，直接暴力循环一次 $a$ 中的值，将最小的改变量加起来就行

## 代码部分

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;
const int N = 1e5 + 10;

int n, m, a[N], b[N], ans;

bool cmp(int a, int b) { return a > b; }

signed main() 
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> b[i];
    sort(a + 1, a + n + 1);
    sort(b + 1, b + m + 1, cmp);
    for (int i = 1; i <= min(n, m); i++) if (b[i] >= a[i]) ans += b[i] - a[i];
    cout << ans << '\n';
    return 0;
}
```


---

## 作者：Loser_Syx (赞：1)

CF 果真 1s 1e9。

首先通过排序求出最大最小值是显然的，记 $a$ 最小值为 $x$，$b$ 最大值为 $y$。

如果当前 $x < y$，那么我们要做的就是增加 $a$ 数组里的值，或是减少 $b$ 数组里的值，让 $x$ 增加 $1$ 的代价是 $\sum^{n}_{i=1} [a_i\leq x]$，让 $y$ 减少 $1$ 的代价是 $\sum^{m}_{i=1} [b_i \geq y]$，每次操作选择代价最小的即可，因为 $x$ 是递增且 $y$ 是递减的，所以我们可以在排序后的数组中求。

复杂度是 $O(\max b_i-\min a_i)$ 的，但是 CF 神机不做评价。

```cpp
int a[101010], b[101010];
signed main() {
	int n,m;read(n,m);
	int mn=1e18,mx=0;
	for (int i=1;i<=n;++i) read(a[i]),mn=min(mn,a[i]);
	for (int i=1;i<=m;++i) read(b[i]),mx=max(mx,b[i]);
	if (mn>=mx) return write(0,'\n'),0;
	else {
		sort(a+1,a+1+n);
		sort(b+1,b+1+m,greater<int>());
		int i=1,j=1;
        for (;a[i+1]==mn;++i); for (;b[j+1]==mx;++j);
		int ans=0;
		while (mn<mx) {
			if (i<j) {
				if (i>n) {
					ans += (mx-mn)*n;
					break;
				}
				ans+=i;
				++mn;
				for (;a[i+1]==mn;++i);
			} else {
				if (j>m) {
					ans += (mx-mn)*m;
					break;
				}
				ans+=j;
				--mx;
				for (;b[j+1]==mx;++j);
			}
		}
		write(ans,'\n');
	}
	return 0;
}
```

---

## 作者：内拉组里 (赞：0)

# Solution 1

显然当 $ a_{\min} \ge b_{\max} $ 时答案为 $ 0 $。

而 $ a_{\min} \lt b_{\max} $ 时最终要使 $ a_{\min} = b_{\max} $ 才能实现最小步数。

令最终 $ a_{\min} = b_{\max} = \vartheta $，

则操作方法也一定是 $ \forall a_i \lt \vartheta,a_i \leftarrow \vartheta $ 和 $ \forall b_I \gt \vartheta,b_i \leftarrow \vartheta $。

或许会联想到二分或三分，~~但我没写出来~~。

所以直接枚举每个 $ a_i $ 和 $ b_i $ 作为 $ \vartheta $。

首先将两数组排序，$ a $ 数组升序，$ b $ 数组降序方便处理。

然后把两个数组进行 **merge**，从小到大贪心。

令此时 $ b_{\max} - a_{\min} = \Delta $，终止状态即为 $ \Delta \le 0 $，

那么数组中的每个相邻数字之差就是对 $ \Delta $ 的贡献，

而一次性更改的数字数量与相邻数字之差相乘即为对答案的贡献。

## Analyses：

> 总时间复杂度 $ \Theta (N \log{N}) $。
>
> 总空间复杂度 $ \Theta (N) $。

***

# Solution 2

数形结合。

先看一组数据：

```assembly
4 4
1 1 2 3
3 2 1 1	
```

画出图像：

![捕获](https://img.z4a.net/images/2025/01/12/2e5aac1b005647b587cc25f0d033d3ed.png) 

容易发现最终的最佳方案应该是将一条直线与绿线隔离。

![捕获](https://img.z4a.net/images/2025/01/12/380c8f3434225df27b40877a666581ed.png) 

即最佳方案为：

![捕获](https://img.z4a.net/images/2025/01/12/483673a7c222ebee33220d9dc5769454.png) 

or 

![捕获](https://img.z4a.net/images/2025/01/12/650463ad5668e784c433b6413b3e4808.png) 

简单的来说，就是把两幅图像在 $ A $ 点之前的部分啮合，答案就是这两部分在每一处的差之和。

而 $ A $ 点之前的部分即为 $ a_i \lt b_i $ 的部分。

## Analyses：

> 总时间复杂度 $ \Theta (N \log{N}) $。
>
> 总空间复杂度 $ \Theta (N) $。

# Code：

```cpp
/* reference : @ZLOJ.huhangqi */
/* reference : @Luogu.AKPC (540363) */
#include	<algorithm>
#include	<iostream>
#include	<vector>
#define		int		long long
using namespace std;
using pii = pair<int,int>;
constexpr int inf = 0x3f3f3f3f3f3f3f3f;
constexpr int maxn = 1e5+4;

namespace huhangqi
{
	int n, m;
	int a[maxn];
	int b[maxn];
	vector<pii> op;		//index,contribution (difference with the previous one)
	
	signed main (void)
	{
		cin >> n >> m;
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 1; i <= m; i++) cin >> b[i];
		sort (a + 1, a + n + 1);
		sort (b + 1, b + m + 1, greater<int>());
		int dt = *max_element (b + 1, b + m + 1) - *min_element (a + 1, a + n + 1);;
		if (dt <= 0)
		{
			cout << 0 << endl;
			return 0;
		}
		a[n + 1] = inf;
		b[m + 1] = -inf;
		for (int i = 1; i <= n; i++) op.push_back({i, a[i + 1] - a[i]});
		for (int i = 1; i <= m; i++) op.push_back({i, b[i] - b[i + 1]});
		sort (op.begin(), op.end());
		int ans = 0;
		for (auto i : op)
		{
			if (i.second > dt)
			{
				ans += i.first * dt;
				break;
			}
			ans += i.first * i.second;
			dt -= i.second;
//			cerr << ans << endl;
		}
		cout << ans << endl;
		return 0;
	}
}

namespace AKPC
{
	int a[maxn];
	int b[maxn];
	int n, m, ans;
	
	signed main (void)
	{
		cin >> n >> m;
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 1; i <= m; i++) cin >> b[i];
		sort (a + 1, a + n + 1);
		sort (b + 1, b + m + 1, greater<int>());
		for (int i = 1; a[i] < b[i] && i <= n && i <= m; i++) ans += b[i] - a[i];
		cout << ans << endl;
		return 0;
	}
}

signed main (void)
{
	return AKPC::main ();
}
```

---

