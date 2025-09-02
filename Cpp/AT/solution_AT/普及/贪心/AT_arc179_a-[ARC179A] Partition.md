# [ARC179A] Partition

## 题目描述

给定你整数 $N$ 和 $K$。

定义长度为 $N$ 的整数序列 $X=(X_1,X_2,\dots,X_N)$ 的**前缀和**为长度为 $N+1$ 的序列 $Y=(Y_0,Y_1,\dots,Y_N)$ 满足：

- $Y_0=0$

- $Y_i=\sum\limits_{j=1}^{i}X_j (i=1,2,\dots,N)$

如果一个长度为 $N$ 的整数序列 $X=(X_1,X_2,\dots,X_N)$ 满足以下条件，那么它被成为**好的序列**：

- 在 $X$ 的前缀和中，任何小于 $K$ 的值都出现在任何不小于 $K$ 的值之前。
	- 形式化的说，对于 $X$ 的前缀和 $Y$，对于任意整数对 $(i,j)$ 其中 $0\le i,j\le N$，如果 $Y_i<K$ 且 $Y_j\ge K$ 那么 $i<j$。
	
给你一个长度为 $N$ 的整数序列 $A=(A_1,A_2,\dots,A_N)$。判断是否能够通过重排 $A$ 中的元素使 $A$ 变成一个好的序列。如果可以，输出重排后的结果。

## 说明/提示

- $1\le N\le 2\times 10^5$； 
- $-10^9\le K\le 10^9$； 
- $-10^9\le A_i\le 10^9$； 
- 所有输入都是整数。

## 样例 #1

### 输入

```
4 1
-1 2 -3 4```

### 输出

```
Yes
-3 -1 2 4```

## 样例 #2

### 输入

```
4 -1
1 -2 3 -4```

### 输出

```
No```

## 样例 #3

### 输入

```
10 1000000000
-1000000000 -1000000000 -1000000000 -1000000000 -1000000000 1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
Yes
-1000000000 -1000000000 -1000000000 -1000000000 -1000000000 1000000000 1000000000 1000000000 1000000000 1000000000```

# 题解

## 作者：chinazhanghaoxun (赞：6)

## 分析

这道题的思路为贪心，对 $k$ 进行分类讨论。

- $k\ge 1$，只需要把 $a$ 按升序排序即可，这样的序列一定有解，因为 $a_i<k$ 的数一定在相对前面的位置，而 $a_i\ge k$ 的数一定在相对后面的位置，这种排序是满足题意的。
- $k<1$，设 $sum$ 表示所有数的和。如果 $sum \ge k$，就把 $a$ 按降序排序。这是因为 $a_i>k$ 的数字在前面，$a_i\le k$ 的数字在后面。另一种情况是，$sum<k$，那么无解，输出 ```No```。
## 代码+注释

**一定要开 long long 哟！**
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a[200005],sum;
bool cmp(int a,int b){
	return a>b;
} 
signed main(){
	cin>>n>>k; 
	for(int i=1;i<=n;i++)
		cin>>a[i],sum+=a[i]; //可以顺便把和算出来 
	if(k>=1){ //k是正数 
		sort(a+1,a+n+1);//默认升序排序 
		puts("Yes");//默认有换行 
		for(int i=1;i<=n;i++)
			cout<<a[i]<<' ';
		puts("");
	}else{
		if(sum>=k){ //可以操作 
			sort(a+1,a+n+1,cmp);//定义cmp函数降序比较 
			puts("Yes");
			for(int i=1;i<=n;i++)
				cout<<a[i]<<' ';
			puts("");
		}else //不行 
			puts("No");
	}
	return 0;
} 
```

---

## 作者：uncle_steve (赞：2)

[题目传送门AT_arc179_a [ARC179A] Partition](https://www.luogu.com.cn/problem/AT_arc179_a)

**知识点：** 贪心+分类讨论（两种情况）。

## 题目分析：

将 $k$ 分类讨论：

**第一种：**$k\ge1$ 时，只需要将数组升序排列即可。

可以证明一定有解：当 $a_i<k$ 时，$a_i$ 一定在前面的位置；当 $a_i\ge k$ 时，$a_i$ 一定在后面的位置，满足题目条件。

**第二种：**$k<1$ 时，再分两种情况：
- 所有数总和 $(sum)\ge k$，只需将数组降序排列即可。证明方法与第一种相似，可以证明。
  
- 所有数总和 $(sum)<k$，此时一定无解，输出 No 即可。

**注意：** 有解的情况要输出 Yes，同时注意大小写。 

部分转自@[chinazhanghaoxun](https://www.luogu.com.cn/user/684848)。

## AC CODE（部分分析见注释）：


```cpp
#include<bits/stdc++.h>
#define int long long//增强数据范围
using namespace std;
int n,k,a[200005],sum;
bool cmp(int a,int b){
	return a>b;
} 
signed main(){
	cin>>n>>k; 
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i]; //顺便计算出总和（sum为总和）
	}
	if(k>=1){//第一种情况 
		sort(a+1,a+n+1);//升序排列
		cout<<"Yes"<<endl;//注意：这里要输出！！！
		for(int i=1;i<=n;i++){
			cout<<a[i]<<" ";//输出
		}
	}
	else{//第二种情况
		if(sum>=k){ //当sum>=k时
			sort(a+1,a+n+1,cmp);//降序排列
			cout<<"Yes"<<endl;
			for(int i=1;i<=n;i++){
				cout<<a[i]<<" ";//输出
			}
		}
		else cout<<"No"<<endl;//无解情况
	}
	
	return 0;
}
```

---

## 作者：Wendy_Hello_qwq (赞：1)

[题目传送门。](https://www.luogu.com.cn/problem/AT_arc179_a)

[原文食用效果更佳。](https://www.luogu.com/article/miljnrsa)

## 题意

给定一个整数序列 $A$ 和 $K$，判断是否能够通过重排 $A$ 中的元素使 $A$ 变成一个好的序列，即：

> 这个好的序列 $A$ 里所有小于 $K$ 的前缀和必须在所有大于或等于 $K$ 的前缀和之前出现。

如果可以，先输出 `Yes`，然后输出重排后的结果；如果不能，输出 `No`。

## 分析

这道题的思路是**贪心**，要对 $K$ 进行**分类讨论**：

- 如果 $K \ge 1$，那么这种一定是有解的，直接输出 $A$ 数组的升序排序即可，因为排序后当 $A_i<k$ 时，$A_i$ 一定在前面的位置，反之则在后面。

- 如果 $K<1$，那么设 $ans$ 为 $A$ 数组所有数字的和，判断 $ans \ge k$，则 $A_i>k$ 的数在前面，故使用降序排序输出。但是如果 $ans<k$，就是说连 $A$ 数组所有数的和都小于 $K$ 的话，那么一定无解，输出 `No` 即可。

还有一点要注意：记得开 **long long**，不然稍微大点的数据会炸掉~~因为这个问题硬控了我一次提交。~~
## Code

```cpp
// AT_arc179_a.Partition
#include <cstdio>
#include <algorithm>
using namespace std;
// 记得开 long long，数据范围 
long long n, k, ans, a[200005];
// 排序降序函数 
bool cmp (int x, int y) {
	return x > y;
}
int main() {
	scanf ("%lld%lld", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf ("%lld", &a[i]);
		// 所有数字总和 
		ans += a[i];
	}
	// 分类讨论 k 的范围 
	if (k >= 1) {
		// 升序排序 
		sort (a + 1, a + n + 1);
		printf ("Yes\n");
		for (int i = 1; i <= n; i++) printf ("%lld ", a[i]);
		printf ("\n");
	} else {
		// 判断如果全部的总和大于等于 k 
		if (ans >= k) {
			// 降序排序 
			sort (a + 1, a + n + 1, cmp);
			printf ("Yes\n");
			for (int i = 1; i <= n; i++) printf ("%lld ", a[i]);
			printf ("\n");
		// 都不行，输出 No 
		} else printf ("No");
	}
	return 0;
}
```

[AC 记录。](https://atcoder.jp/contests/arc179/submissions/61101348)

完结撒花。

作者写题解不易，点个赞再走呗。

---

## 作者：fire_and_sweets (赞：1)

本题可以使用贪心的策略。

首先，如果 $k\ge 1$，显然只需要把 $a$ 从小到大排序即可。可以证明一定有解：由于从小到大排序，所以 $<k$ 的一定在前面，$\ge k$ 的一定在后面，这样排序一定满足要求。

如果 $k<1$，再分两类：
- 如果所有数的总和 $\ge k$，可以把 $a$ 从大到小排序。正确性显然，具体证明方法和 $k\ge 1$ 的类似，这里不再赘述。
- 否则，直接返回无解。

时间复杂度 $\mathcal{O}(n)$。

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200010;
int n, k, a[N];
signed main()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i ++ ) cin >> a[i];
	int sum = 0;
	for (int i = 1; i <= n; i ++ ) sum += a[i];
	if (k >= 1)
	{
		sort(a + 1, a + n + 1);
		cout << "Yes\n";
		for (int i = 1; i <= n; i ++ ) cout << a[i] << " ";
		cout << endl;
	}
	else
	{
		if (sum >= k)
		{
			sort(a + 1, a + n + 1, greater<int>());
			cout << "Yes\n";
			for (int i = 1; i <= n; i ++ ) cout << a[i] << " ";
			cout << endl;
		}
		else cout << "No\n";
	}
	return 0;
} 
```

---

## 作者：Kratos_Charger (赞：0)

## AT_arc179_a [ARC179A] Partition  题解

### 题目大意

给定一个整数序列 $A$ 和整数 $K$，要求判断是否可以通过重排序列 $A$ 的元素，使得重排后的序列 $A'$ 满足一个特殊的条件，即：

对于重排后的序列 $A'$ ，其前缀和序列 $Y$ 中，任何小于 $K$ 的前缀和都应该出现在任何大于等于 $K$ 的前缀和之前。

设序列 $A' = (A_1', A_2', \dots, A_N') $，前缀和序列 $ Y = (Y_0, Y_1, \dots, Y_N) $，其中 $ Y_0 = 0 $ 且对于 $ 1 \le i \le N $，有：

$$ Y_i = \sum_{j=1}^{i} A_j'$$ 

就是说所有小于 $K$ 的前缀和必须在所有大于或等于 $K$ 的前缀和之前出现。

### 思路

首先将数组排序，让前缀和逐渐增大，避免出现先有一个较小的前缀和。

接着，需要检查排序后的数组，确保前缀和的顺序不会违反题目的要求。如果在某个位置的前缀和小于 $K$，而在此之前已经有前缀和大于等于 $K$，那么这就是一个违反条件的情况，应该返回 `No`。

如果排序后没有出现这种问题，说明可以通过这个排列满足题目的要求，最后输出 `Yes` 并输出出这个排列。

### Code


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,a[200005],s[200005],f=0;
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	if(k<=0) reverse(a+1,a+n+1);
	for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
	for(int i=0;i<=n;i++){
		if(s[i]>=k) f=1;
		if(s[i]<k&&f==1){
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes"<<endl;
	for(int i=1;i<=n;i++) cout<<a[i]<<" ";
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc179_a)

### 思路
一道简单的贪心题。分类讨论 $k$ 的情况。
+ $k \ge 1$ 时，只需要将 $a$ 数组进行升序排列，可以证明此时一定有解。证明大致如下：对于 $a_i < k$ 的情况，$a_i$ 一定在相对前面的位置；而对于 $a_i \ge k$ 的情况，$a_i$ 一定在相对后面的位置。一定满足要求。
+ $k < 1$ 时，还有两种情况：

  1. 如果所有数的总和 $\ge k$，那么将 $a$ 进行降序排列即可，证明跟上面基本相同。
  2. 如果所有数的总和 $< k$，显然无解，直接输出 `No` 即可。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+1;
int n,k,a[N],s;
bool cmp(int a,int b){
	return a>b;
}
signed main(){
	cin>>n>>k; 
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s+=a[i];
	}
	if(k>=1){
		sort(a+1,a+n+1);
		cout<<"Yes\n";
		for(int i=1;i<=n;i++){
			cout<<a[i];
			if(i!=n) cout<<' ';
			else cout<<endl;
		}
	}
	else{
		if(s>=k){
			sort(a+1,a+n+1,cmp);
			cout<<"Yes\n";
			for(int i=1;i<=n;i++){
				cout<<a[i];
				if(i!=n) cout<<' ';
				else cout<<endl;
			}
		}
		else cout<<"No\n";
	}
}
```

---

## 作者：luogu_gza (赞：0)

考虑对于 $k$ 进行讨论。

如果 $k$ 为正数，那么只需要将 $a$ 从小到大排序即可，不难发现负数部分不用讨论，正数部分会让前缀和序列一直上升，满足条件。

如果 $k$ 为负数，那么只需要从大到小排序即可，这样会增大成功的概率，因为正数叠的多了，负的不至于绝对值太大。

但是还是可能失败，直接扫一遍 check 一下答案打不打即可。

[code](https://atcoder.jp/contests/arc179/submissions/56461316)。

---

## 作者：Andy_WA (赞：0)

## 分析
- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ -10^9\ \leq\ K\ \leq\ 10^9 $
- $ -10^9\ \leq\ A_i\ \leq\ 10^9 $

## 思路
+ 若 $K>0$，则 $Y_0<K$，将 $A$ 数组从小到大排序，如果某个 
$Y$ 中的某一项大于 $K$，因为 $K>0$，所以 $A$ 中的对应项必定为正整数。
+ 因为 $A$ 数组在排序后单调递增，则后面的每一项大于 $K$。
+ 如果每有则已经满足条件，故一定有解。
+ 若 $K≤0$，则 $Y_0≥K$，将 $A$ 数组从大到小排序，如果 $Y$ 中后面有一项小于 $K$，则一定无解，否则有解。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MaxN=2*1e5+10;
long long a[MaxN],f[MaxN];
long long n,k;
int main(){
	scanf("%lld%lld",&n,&k);
	for(long long i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	stable_sort(a+1,a+n+1);
	for(long long i=1;i<=n;i++){
		f[i]=f[i-1]+a[i];
	}
	if(k<=0){
		stable_sort(a+1,a+n+1,greater<long long>());
		for(long long i=1;i<=n;i++){
			f[i]=f[i-1]+a[i];
		}
		for(long long i=1;i<=n;i++){
			if(f[i]<k){
				printf("No\n");
				return 0;
			}
		}
	}
	printf("Yes\n");
	for(long long i=1;i<=n;i++){
		printf("%lld ",a[i]);
	}
	printf("\n");
	return 0;
}
```

最后，以一句话结束：
$$
\textit{\textbf{莫抄袭，棕了少年名，空悲切。}}
$$

---

## 作者：CodingOIer (赞：0)

## [ARC179A] Partition 题解

### 思路分析

贪心。

对于 $k \le 0$ 的情况，由于一开始我们就处于了 $Y_i \ge k$ 的部分，所以我们需要让 $Y_i$ 始终大于 $k$。

为了最大化成功的可能，我们先加上所以的正数，再减去所有的负数。

降序排序即可。

```cpp
std::sort(p + 1, p + 1 + n, [](int x, int y) { return x > y; });
long long s = 0;
for (int i = 1; i <= n; i++)
{
    s += p[i];
    if (s < k)
    {
        printf("No\n");
        return 0;
    }
}
printf("Yes\n");
for (int i = 1; i <= n; i++)
{
    printf("%d ", p[i]);
}
```

对于 $k \ge 0$ 的情况，我们在最初时处于 $Y_i \le 0$ 的部分，我们可以先让 $Y_i \ge k$，然后再 $\le k$。

升序排序即可，对于这种情况，没事失败的可能。

```cpp
std::sort(p + 1, p + 1 + n);
printf("Yes\n");
for (int i = 1; i <= n; i++)
{
    printf("%d ", p[i]);
}
```

### 代码实现

```cpp
#include <algorithm>
#include <cstdio>
constexpr int MaxN = 2e5 + 5;
int n, k;
int p[MaxN];
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    if (k <= 0)
    {
        std::sort(p + 1, p + 1 + n, [](int x, int y) { return x > y; });
        long long s = 0;
        for (int i = 1; i <= n; i++)
        {
            s += p[i];
            if (s < k)
            {
                printf("No\n");
                return 0;
            }
        }
        printf("Yes\n");
        for (int i = 1; i <= n; i++)
        {
            printf("%d ", p[i]);
        }
    }
    else
    {
        std::sort(p + 1, p + 1 + n);
        printf("Yes\n");
        for (int i = 1; i <= n; i++)
        {
            printf("%d ", p[i]);
        }
    }
    return 0;
}
```

---

## 作者：ran_qwq (赞：0)

记 $sum=\sum a_i$。如果 $m\le 0$ 且 $sum<m$，则前面的 $0$ 大于等于 $m$，矛盾，输出 `-1`。

如果 $m\le0$，从大到小排。前缀和是单峰函数，$sum_n\ge m$，所以所有前缀和都 $\ge m$。

如果 $m>0$，从小到大排。前缀和是单谷函数，先小于等于 $0$，再在大于 $0$ 的段单调不降，所有小于 $m$ 的数当然排在大于等于 $m$ 的数的前面。

```cpp
int n,m,a[N]; ll sum;
void QwQ() {
	n=rd(),m=rd();
	for(int i=1;i<=n;i++) a[i]=rd(),sum+=a[i];
	if(m<=0) {
		if(sum<m) puts("No"),exit(0); puts("Yes");
		sort(a+1,a+1+n,greater<int>());
		for(int i=1;i<=n;i++) wr(a[i]," ");
	} else {
		sort(a+1,a+1+n),puts("Yes");
		for(int i=1;i<=n;i++) wr(a[i]," ");
	}
}
```

---

## 作者：YuYuanPQ (赞：0)

唐了。

读完题转化一下题意。

## 题意

### 累计和的定义

设 y 序列是 x 序列的累计和。

由题意得：y 是 x 的前缀和，即 $y_i=\sum_{j=1}^{i}x_i$。

### 好序列的定义

以 $k$ 为分界，左边的 $y_i<k$，右边的 $y_j \geq k$。

### 求

给定数组 a，问重排后能否为好的序列。

## 分析

首先说明，$k$ 左右 $2$ 边的 $y_i$ **不一定**有序。

显然，升序或降序时为最优的情况，那么如何判断呢？

贪心+分类讨论。

以下函数图像仅为**大致**的示意图，其中，紫点为 $k$。

- 当 $k>0$ 时：

![function1](https://cdn.luogu.com.cn/upload/image_hosting/icu8kt0h.png)


这种情况无脑升序输出即可。

- 当 $k\leq0$， $sum\geq k$ 时：

![function2](https://cdn.luogu.com.cn/upload/image_hosting/h5o08e60.png)

此时，降序输出。

- 其他情况为 `No`。

使用 [desmos](https://www.desmos.com/calculator?lang=zh-CN) 进行绘制。

画图不易，点个赞再走吧~

## Code

[Link](https://atcoder.jp/contests/arc179/submissions/54187234)

---

## 作者：Harrylzh (赞：0)

## 思路

题目把数分为两类，第一类是小于 $k$ 的，第二类是大于等于 $k$ 的。因为前缀和中的第一个数一定是 $0$，所以考虑两种情况：

- $k\le 0$

此时 $0$ 属于第二类，所以要让后面所有的数都属于第二类。贪心地将正数放前面，负数放后面，如果这样还不行，就一定无法满足要求，否则可以。

- $k >0$

此时 $0$ 属于第一类，所以可以先让负数在前面减，此时前缀和一定小于 $0$，属于第一类，再让正数使后面的前缀和递增，一定可以符合要求。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k;
long long a[1000000+5];
bool cmp(long long x,long long y)
{
	return x>y;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(long long i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	if(k<=0)
	{
		sort(a+1,a+n+1,cmp);
		long long tot=0;
		for(long long i=1;i<=n;i++)
		{
			tot+=a[i];
		}
		if(tot>=k)
		{
			cout<<"Yes\n";
			for(long long i=1;i<=n;i++) cout<<a[i]<<' ';
		}
		else
		{
			cout<<"No";
		}
		cout<<"\n";
	}
	else
	{
		sort(a+1,a+n+1);
		cout<<"Yes\n";
		for(long long i=1;i<=n;i++)
		{
			cout<<a[i]<<' ';
		}
		cout<<"\n";
	}
	return 0;
}

```

---

## 作者：HasNoName (赞：0)

### 思路

若 $K>0$，则 $Y_0<K$，将 $A$ 数组从小到大排序，如果某个 $Y$ 中的某一项大于 $K$，因为 $K>0$，所以 $A$ 中的对应项必定为正整数。因为 $A$ 数组在排序后单调递增，则后面的每一项大于 $K$。如果每有则已经满足条件，故一定有解。

若 $K\le0$，则 $Y_0\ge K$，将 $A$ 数组从大到小排序，如果 $Y$ 中后面有一项小于 $K$，则一定无解，否则有解。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200005;
ll a[N],f[N];
bool cmp(ll x,ll y)
{
    return x>y;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)
    {
        f[i]=f[i-1]+a[i];
    }
    if(k<=0)
    {
        sort(a+1,a+n+1,cmp);
        for(int i=1;i<=n;i++)
        {
            f[i]=f[i-1]+a[i];
        }
        for(int i=1;i<=n;i++)
        {
            if(f[i]<k)
            {
                cout<<"No\n";
                return 0;
            }
        }
    }
    cout<<"Yes\n";
    for(int i=1;i<=n;i++)
        cout<<a[i]<<' ';
    cout<<'\n';
    return 0;
}
```

---

## 作者：int_stl (赞：0)

我们将 $k$ 的取值分两种情况讨论。

- 当 $k > 0$ 时，我们考虑将 $X$ 从小到大排序，这样负数在前，正数在后，可以让 $Y$ 单调递减，再单调递增，又因 $Y_0 < k$，因此满足要求。

- 否则，我们将 $X$ 从大到小排序，这样尝试让 $Y$ 的所有元素都小于 $k$ 或大于等于 $k$，再检查一遍即可。

代码如下：
```cpp
int n, k;
int a[200006], pre[200006];
int main() {
	read(n, k);
	FORL(i, 1, n, 1) {
		read(a[i]);
	}
	if (k > 0) {
		sort(a + 1, a + n + 1);
		cout << "Yes\n";
		FORL(i, 1, n, 1) {
			write1(a[i]);
		}
	}
	else {
		sort(a + 1, a + n + 1, greater<>());
		ll sum = 0;
		FORL(i, 1, n, 1) {
			sum += a[i];
		}
		if (sum < 1ll * k) {
			cout << "No\n";
			return 0;
		}
		cout << "Yes\n";
		FORL(i, 1, n, 1) {
			write1(a[i]);
		}
	}
	return 0;
}
```

---

