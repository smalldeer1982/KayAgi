# Three Parts of the Array

## 题目描述

**问题描述**  
给定一个长度为n的整数序列$\{d_1,d_2,\dots,d_n\}$。  
你的任务是将序列分成3部分，每部分可以是空的，并保证每一个数都属于这三个部分的某一个，每一部分都必须是一些连续的整数。  
设三部分的和分别为$sum_1$,$sum_2$,$sum_3$。  那么你需要在所有划分方案中找到一个方案使得$sum_1=sum_3$且$sum_1$尽可能的大。  
确切的说，如果第一部分包含$a$个整数，第二部分包含$b$个整数而第三部分包含$c$个，那么应该有
$$sum_1 = \sum\limits_{1 \le i \le a}d_i,$$
$$sum_2 = \sum\limits_{a + 1 \le i \le a + b}d_i,$$
$$sum_3 = \sum\limits_{a + b + 1 \le i \le a + b + c}d_i.$$
并且对于空的那部分，它的和为0。  
你需要在所有划分方案中找到一个方案使得$sum_1=sum_3$且$sum_1$尽可能的大。

## 样例 #1

### 输入

```
5
1 3 1 1 4
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
1 3 2 1 4
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3
4 1 2
```

### 输出

```
0
```

# 题解

## 作者：communist (赞：7)

### 二分查找水题

记$sum[i]$为$d[i]$的前缀和数组

枚举第一段区间的结尾$i$

然后二分出$lower$_$bound(sum[n]-sum[i])$的位置$x$，如果$sum[x]$与$sum[n]-sum[i]$相等，且$x$大于$i$，更新答案

```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=2e5+10;
int n;
long long sum[maxn],ans;
int main()
{
	scanf("%d",&n);
	for(int x,i=1;i<=n;i++)
	{
		scanf("%d",&x);
		sum[i]=sum[i-1]+x;
	}
	for(int i=1;i<=n;i++)
		if(sum[i]<=sum[n]/2)
		{
			int x=lower_bound(sum+1,sum+n+1,sum[n]-sum[i])-sum;
			if(x>=i&&sum[x]==sum[n]-sum[i])
				ans=sum[i];
		}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：信守天下 (赞：1)

# 题解CF1006C【Three Parts of the Array】
# [洛谷传送门](https://www.luogu.com.cn/problem/CF1006C)
# [CF传送门](https://codeforces.com/contest/1006/problem/C)
# 题目大意
给定一个长为n的序列d，

要求将d切成连续的三段，

并且第一段的和等于最后一段的和，

求第一段的最大值。
# 思路：双指针 + 前缀和做法
这里就有人不懂了，前缀和是什么？
## 前缀和
我们可以把一个数组看成一个区间

则这个数组的左边界为最小值的区间则为前缀和

右区间则为后缀和

任意区间的和都可以由前缀区间相减而成

例如$i$ ~ $l$的区间和可以由0 ~ $l$的和减去0 ~ $i$ - 1的和得到
## 前缀计算

前缀计算就是基于前缀和进行一种快速地计算

1，预处理所有前缀区间的运算结果，$a$[$i$]储存0 ~ $i$的和

2，$i$ ~ $l$的和 = $a$[$l$] - $a$[$i - 1$]

注意：前缀和一定要从下标1开始存数，以避免$i$ = 1的情况数组越界

# 本题思路

1，读入，做出前缀和数组

2，一个指针在左边控制左前缀和。

3，另一个指针控制右前缀和。

4，如果左前缀和 = 右前缀和就更新最大值。

5，指针移动，重复234。
# $code$
~~~cpp
#include <iostream>
using namespace std;
const int kMaxN = 10000001;
long long a[kMaxN], ans;//ans要用long long不然会炸
int n;
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {//从1开始存
    cin >> a[i];
    a[i] += a[i - 1];//前缀和
  }
  for (int l = 1, r = n; l <= r; l++){//l,r双指针
    for ( ; a[n] - a[r] < a[l] && r >= l ; r--);//后指针移动
    /*a[n] - a[r]表示a[r]到a[n]的前缀和,a[n]表示a[1]到a[n]的前缀和*/
    if (r >= l && a[n] - a[r] == a[l]) {
    /*后指针在前指针后且右前缀和=左前缀和*/
      ans = a[l];//更新最大值
    }
  }
  cout << ans;//输出最大值
  return 0;
}
~~~

---

## 作者：GoldenFishX (赞：1)

### 此题的坑

- 中间的部分也可以为空
- 求和时记得开long long
## 思路
#### 双指针
$l$ :左边的部分的边界（左边的部分包括l)

$r$ :右边的部分的边界（右边的部分包括r）

如果 ```左边的和```$>$```右边的和``` 就 扩大右边的边界 $(r--)$

如果 ```左边的和```$<=$```右边的和``` 就 扩大左边的边界 $(l++)$

出现相同的情况就更新答案（由于左边和右边的部分是不断扩大的，所以不用取最大值）

## 核心代码
```cpp
  long long suml = a[0], sumr = a[n - 1];//左边和右边的和
  int l = 0, r = n - 1;
  while(l < r) {
    if(sumr == suml) { //更新答案
      ans = sumr;
    }
    if(suml > sumr) {
      sumr += a[--r];
    } else {
      suml += a[++l];
    }
  }

```

---

## 作者：lsw1 (赞：0)

本题解提供两种做法：二分和尺取法。

### 一、二分

前置例题：

- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)

- [P1873 砍树](https://www.luogu.com.cn/problem/P1873)

- [P2678 \[NOIP2015 提高组\] 跳石头](https://www.luogu.com.cn/problem/P2678)

- [P2440 木材加工](https://www.luogu.com.cn/problem/P2440)

做完这几道二分模板题后，我们再来看看这一题。

考虑枚举第 $2$ 部分和第 $3$ 部分的分界点。

设现在枚举到的分界点为 $x$，那么再二分点 $y$ 使得 $\sum_{i=1}^x=\sum_{j=y}^{n}$。

如果没有二分到满足条件的 $y$，那么第 $2$ 部分和第 $3$ 部分的分界点显然不可能是点 $x$。


否则，更新答案。

注意要用前缀和优化一下。

时间复杂度 $O(n\log n)$。

### 二、尺取法

我们先考虑暴力。

时间复杂度显然是 $O(n^2)$，无法通过此题。

我们来好好想想我们暴力的这些状态有哪些是冗余的。

如果 $\sum_{i=1}^x<\sum_{j=y}^{n}$，那么判断 $x_1>x,y_1<y$ 显然也没有任何意义。

针对暴力的这一缺陷，我们设计出了一个新算法：设 $l$ 为第 $1$ 部分和第 $2$ 部分的分界点，$r$ 为第 $2$ 部分和第 $3$ 部分的分界点，然后每次 $l$ 向右移动 $1$，$r$ 就向左移动，直到 $\sum_{i=1}^l\ge\sum_{j=r}^{n}$，如果$\sum_{i=1}^l=\sum_{j=r}^{n}$ 就更新答案。

时间复杂度乍一看很玄学，但是换个角度仔细想想就会发现 $l$ 从 $1$ 开始一直向右移，$r$ 从 $n$ 开始一直向左移，直到它们相遇，那么时间复杂度显然是 $O(n)$ 的。

---

## 作者：Na2PtCl6 (赞：0)

## 分析题目
题目只是要求 $sum_1=sum_3$，所以我们就只关心这个，如果凑不出来，就输出 $0$。

我们可枚举以 $i$ 到 $n$ 的和，在 $[1,i)~(1\le i\le n)$ 中找与之相等的前缀和，这用二分查找实现。

## 注意事项
找相等的前缀和别用 `lower_bound` ,应该用 `upper_bound` 找到的指针位-1 。原因在于：如果 $[1,i)$ 中没有足够大的前缀和，那么 `lower_bound` 就会返回查找范围的后一个指针位，如果这个指针位上的前缀和刚好和后缀和相等，就把不符合要求的分割当成了对的。

## 代买实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a;
long long suf,res,pre[200004];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a);
		pre[i]=pre[i-1]+a;
	}
	for(int i=1;i<=n;i++){
		suf=pre[n]-pre[i-1];
		if(*(upper_bound(pre+1,pre+i,suf)-1)==suf){
			printf("%lld\n",suf);
			return 0;
		}
	}
	puts("0");
	return 0;
}
/*
19
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
*/
```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

本题 $1\le n\le2\times10^5$，数据范围并不大，不需要二分，但需要前缀和优化。

我们可以维护两个变量：$a$ 和 $c$，意义与题目所述相同。

然后循环，根据 $a$ 和 $c$ 计算出 $sum_1$ 与 $sum_3$ 的值，比较一下，出现以下 $3$ 种情况。

1. $sum_1=sum_3$，此时：

    1. 如果 $sum_1>ans$，更新 $ans$。
    
    2. 将 $a$ 加 $1$，同时将 $c$ 加 $1$。

2. $sum_1<sum_3$，此时将 $a$ 加 $1$。

3. $sum_1>sum_3$，此时将 $c$ 加 $1$。

直到 $a+c>n$ 时，说明“第一部分”和“第三部分”有重合，此时退出循环并输出结果。

另外，由于 $ans$ 已被初始化为 $0$，所以如果始终没有出现 $sum_1=sum_3$ 的情况，将输出 $0$。

### 二、完整代码

```cpp
#include<cstdio>
using namespace std;
int n;
long long input[200005],pre[200005];//input负责存储输入，pre负责维护前缀和。
int a,c;
long long ans;//十年OI一场空，不开long long见祖宗。
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&input[i]);
		pre[i]=pre[i-1]+input[i];//计算前缀和。
	}
	while(a+c<=n)
	{
		long long sum_a=pre[a];//其实这里的完整版是pre[a]-pre[0]，因为pre[0]=0，所以省略了。
		long long sum_c=pre[n]-pre[n-c];
		if(sum_a==sum_c)
		{
			if(ans<sum_a)
			{
				ans=sum_a;
			}
			a++;
			c++;
		}
		else if(sum_a<sum_c)
		{
			a++;
		}
		else if(sum_a>sum_c)
		{
			c++;
		}
	}
	printf("%lld\n",ans);//输出。
	return 0;//完结撒花！
}

```


### 三、后记

记录：<https://www.luogu.com.cn/record/51499255>。

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

这道题可以不用二分，一个个枚举就行了。

1. 首先，输入数列，并算出前缀和；

2. 接着，定义变量 $a$ 和 $c$，其中，$a$ 代表第一个数列的最后一个数的下标，$c$ 代表第三个数列的第一个数的下标。初始化为 $a=0$，$c=n+1$，也就是说，第一个数列与第三个数列都是空的，$sum_1=0$，$sum_3=0$。我们可以先初始化 $a$ 和 $c$，再一步一步将 $a$ 和 $c$ 往中间推进。

3. 接下来是一个循环。

	1. 如果 $sum_1=sum_3$ 并且 $ans<sum_1$，更新 $ans$；
    
	2. 如果 $sum_1<sum_3$，为了让两边尽可能平衡，需要让 $a$ 加 $1$ （也就是让第一个数列更加长，因为数字为正数，若 $a$ 增加，则 $sum_1$ 必然增加）；
    
	3. 同理，如果 $sum_1>sum_3$，$c$ 要减少 $1$。
    
	4. 如果 $a\ge c$，退出循环。
    
4. 输出 $ans$ 的值。

注意，一定要用long long型变量， 不然会溢出。同时，使用前缀和，可以使运行速度快不少。

### 2 代码与记录

```cpp
#include<cstdio>
using namespace std;
const int max_n=200000;
int n;
long long d[max_n+2];
long long s[max_n+2];
int a,c;
long long sum_a,sum_c;
long long ans=0;
int main(){
	scanf("%d",&n);
	s[0]=0;
	a=0;
	c=n+1;
	for(int i=1;i<=n;++i){
		scanf("%lld",d+i);
		s[i]=s[i-1]+d[i];
	}
	s[n+1]=s[n];
	while(a<c){
		sum_a=s[a];
		sum_c=s[n]-s[c-1];
		if(sum_a==sum_c){
			if(ans<sum_a){
				ans=sum_a;
			}
			++a;
			--c;
			continue;
		}
		if(sum_a<sum_c){
			++a;
		}
		else{
			--c;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/51350719)

By **dengziyue**


---

## 作者：小闸蟹 (赞：0)

```cpp
// 这一题用双指针，设一头一尾的指针为l和r，然后这两根指针不停地往中间移动，遇到头尾之和分别相等时则记录一下
// 中间移动的过程中注意一下何时移动一根指针，何时两根指针同时移动就很容易AC了
#include <iostream>
#include <algorithm>
#include <array>

using ll = long long;

constexpr int MaxN = 200000 + 5;

std::array<int, MaxN> Arr{ 0 };

ll Ans = 0;

// 我们设DFS(l, r, sl, sr)为头指针指向Arr[l]，尾指针指向Arr[r]，此时头之和为sl，尾之和为sr
void DFS(int l, int r, ll sl, ll sr)
{
    if (sl == sr)   // 遇到头尾之和相等的情况
    {
        Ans = sl;   // 则记录一下目前的最大值（由于数列中所有数都是正数，可以保证每次遇到相等的情况都是目前为止的最优解）

        if (l < r)  // 两根指针还没有相遇，则它们还能同时向中间进一步
        {
            DFS(l + 1, r - 1, sl + Arr[l], sr + Arr[r]);
        }
    }
    else if (l > r) // 递归终点
    {
        return;
    }
    else if (sl < sr)   // 头之和比较小，所以移动头指针
    {
        DFS(l + 1, r, sl + Arr[l], sr);
    }
    else if (sl > sr)   // 尾之和比较小，所以移动尾指针
    {
        DFS(l, r - 1, sl, sr + Arr[r]);
    }
    else    // 不知道还有什么奇奇怪怪的情况反正剪掉就是了
    {
        return;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> Arr[i];
    }

    DFS(0, n - 1, 0, 0);    // 一头一尾开始搜，初始时头之和和尾之和都为0

    std::cout << Ans << std::endl;

    return 0;
}
```

---

