# Paint a Strip

## 题目描述

你有一个长度为 $n$ 的数组 $a_1, a_2, \ldots, a_n$，其元素全为零。

可以对该数组进行两种操作：

1. 选择一个下标 $i$（满足 $1 \le i \le n$ 且 $a_i = 0$），将 $a_i$ 设为 $1$；
2. 选择一对下标 $l$ 和 $r$（满足 $1 \le l \le r \le n$、$a_l = 1$、$a_r = 1$ 且 $a_l + \ldots + a_r \ge \lceil\frac{r - l + 1}{2}\rceil$），将区间 $[l, r]$ 中所有元素设为 $1$。

你的任务是计算，使数组中所有元素都变为 $1$，至少需要多少次第一种操作？

## 说明/提示

- 对于第一个测试用例，你可以对 $i = 1$ 操作一次即可。
- 对于第二个测试用例，可以按以下步骤操作：
  1. 对 $i = 1$ 进行第一种操作，数组变为 $[1, 0]$。
  2. 对 $i = 2$ 进行第一种操作，数组变为 $[1, 1]$。

  第二个测试用例的操作步骤如下图所示：![图示](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2040B/08c860ca61c18c2cea946aa6a8dc785c3721c9f1.png)

- 对于第三个测试用例，可以按以下步骤操作：
  1. 对 $i = 1$ 进行第一种操作，数组变为 $[1, 0, 0, 0]$。
  2. 对 $i = 4$ 进行第一种操作，数组变为 $[1, 0, 0, 1]$。
  3. 对 $l = 1$ 和 $r = 4$ 进行第二种操作，因为 $a_1 + a_2 + a_3 + a_4 = 2$，满足不小于 $\lceil\frac{r - l + 1}{2}\rceil = 2$，所以可以将区间内元素设为 $1$，数组变为 $[1, 1, 1, 1]$。

  第三个测试用例的操作步骤如下图所示：![图示](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2040B/145510fed0c2c1fc91c16be016c113ca0ca5bb2f.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
1
2
4
20```

### 输出

```
1
2
2
4```

# 题解

## 作者：_Supernova (赞：2)

### 一、思路分析。

我们发现，对于一个给定的 $n$，答案就是确定的。

~~于是开始打表。~~

于是我们在回答询问前先预处理所有状态。

然而，对于一个 $n$，直接求最小次数非常不好做。

那么我们转化问题，对于给定的次数，求出最大能满足的 $n$。

于是我们记 $f_i$ 表示 $i$ 次第一种操作能满足的最大的 $n$。

很显然我们应从 $f_{i-1}$ 转移过来。

对于 $i-1$ 次操作 $1$ 的序列，我们再进行一次第一种操作，在进行第二种操作，得到：$f_i=(f_{i-1}+1)\times 2$。


```cpp
f[1] = 1;
for (int i = 2; i < 20; ++i) {
  f[i] = (f[i-1] + 1) * 2;
}
```

求出这个之后，我们开始着手询问。

对于一个 $n$，我们要找到它对应的 $f_i$。

于是，我们使用 lower_bound 函数，找到对应的下标，即是答案。


```cpp
if (n == 1) {
  cout << 1 << '\n';
  continue;
}
int p = lower_bound(f + 1, f + 20, n) - f;
cout << p << '\n';
```

核心代码都已给出，剩余请自行补充。

忽略小常数，时间复杂度 $O(T)$。

谢谢大家！

---

## 作者：ohjun (赞：2)

## 思路分析
设 $f_i$ 为 $i$ 次操作 1 能够满足条件的最大 $n$，容易想到对于 $f_{i + 1}$ 多出来的一次操作应该放在最后一个位置，这样才可以直接用操作 2 把整个数组变为 $1$。所以此时一定有 $f_i + 1$ 个 $1$。我们想用操作 2 使整个数组变为 $1$, 至少要有 $\displaystyle \lceil \frac{n}{2} \rceil$ 个 $1$, 所以 $f_i + 1$ 个 $1$ 可以最多使 $(f_i + 1) \times 2$ 长的数组变为 $1$。即 $f_{i + 1} = (f_i + 1) \times 2$。递推找到答案即可。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 1;
int t, n;
int d[maxn];
 
void solve()
{
	d[0] = 0;
	d[1] = 1;
	for(int i = 2; d[i - 1] < maxn; i++)
		d[i] = (d[i - 1] + 1) * 2;
}
 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);	
	solve();
	cin >> t;
	while(t--)
	{
		cin >> n;
		int ans = 1;
		while(n > d[ans])
			ans++;
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：Sakura_Emilia (赞：1)

# Solution

思路很简单，每一步贪心，然后不断地迭代。当长度为 $1$ 或 $2$ 的时候，直接依次放置即可；当长度更大的时候，由于前一步已经放置了一定长度，假设已经放置的长度为 $n$，那么可以间隔 $n+1$ 个空余位置，再进行放置。此时放置的个数刚好是全长的一半，符合要求，可以使用第二种操作将这一整段全部放置。依次迭代，即可用最少的次数实现最大的放置长度。

最后来检查在这种最大放置方案下，最少需要多少次操作才能覆盖给定的长度。

# Code

来一个小众版本的 PHP 代码实现：

```php
<?php

function solve() {
    $n = (int)trim(fgets(STDIN));
    $cnt = $num = 1;
    while($num < $n){
        $num = 2 * $num + 2;
        $cnt++;
    }

    echo $cnt."\n";
}

function Ciallo() {
    $T = (int)trim(fgets(STDIN));
	while($T--) {
    	solve();
	}
}

Ciallo();
```

---

## 作者：shanxinhan (赞：1)

如果觉得分析的太长的话，其实可以直接看代码，开袋即食。

分析题目，要求操作 $1$ 次数尽量少，也就是我们要尽量使用操作 $2$ 给序列赋值。假设当前序列前 $x$ 个数都已赋为 $1$，那么当我们对 $a_{x \times 2+2}$ 使用操作 $1$，然后以 $a_x$ 为左端点，$a_{x \times 2+2}$ 为右端点使用操作 $2$ 时，能够达到使操作 $1$ 尽量小的目的。（为什么可以这样赋值？因为想使用操作 $2$ 就必须有一左一右两个端点为 $1$，而 $x \times 2+2$ 是能够满足操作 $2$ 所需要求的最远的距离，即进行操作 $2$ 前的序列正好有 $x+1$ 个 $1$ 和 $x+1$ 个 $0$）。

代码实现非常简单，直接看就行，时间复杂度 $O(t \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
int main(){
    cin>>T;
    while(T--){
        cin>>n;
        int cnt=1;
        for(int x=1;x<n;x=x*2+2)cnt++;
        cout<<cnt<<endl;
    }
    return 0;
}

---

## 作者：GavinCQTD (赞：1)

# 题解：CF2040B Paint a Strip

赛时被卡了十多分钟，判断为 whk 导致的智商降低。

## 思路

不妨从左到右思考。根据题意，在最左边有 $p$ 个 $1$ 的时候，我们可以用一次操作一及一次操作二让最左边的 $(p + 1) \times 2$ 个数变成 $1$。因此，在代码实现中，仅需不断取到右边最远可变的地方，通过操作一变为 $1$ 即可。

## 代码

```cpp
void solve(int testID){
    int ans=1,lgh=1; // 最左边的一个数字必须通过操作一变成 1
    cin >> n;
    if(n<=2){
        cout << n << "\n";
        return;
    }
    while(lgh<n){
        ans++;
        lgh = (lgh+1)*2;
    }
    cout << ans << "\n";
}
```

---

## 作者：wuyouawa (赞：0)

### 题目大意

给定一个长度为 $n$ 的零数组 $a_1, a_2, \ldots, a_n$。

你可以对它执行两种类型的操作：
- 选择一个索引 $i$ 使得 $1 \le i \le n$ 且 $a_i = 0$，然后将 $a_i$ 赋值为 $1$；
- 选择一对索引 $l$ 和 $r$ 使得 $1 \le l \le r \le n$，且 $a_l = 1,a_r = 1$，并且满足区间和 $a_l + a_{l+1} + \cdots + a_r \ge \lceil \frac{r - l + 1}{2} \rceil$，然后将区间内的所有元素 $a_i$（对于所有的 $l \le i \le r$）赋值为 $1$。

要求：最少需要进行多少次第一次类型的操作才能使得数组中的所有元素都变为 $1$？

### 思路

考虑贪心。

如果我们已经把前 $b$ 个赋值为 $1$，那么再赋值多一个，就可以选择 $l=1,r=2 \times b+2$ 的区间并使用操作二把它们全变成 $1$，因为 $a_l+a_{l+1}+\ldots+a_r=b+1$，与 $\lceil \frac{r-l+1}{2} \rceil$ 也就是 $\lceil \frac{2 \times b+2-1+1}{2} \rceil=b+1$ 相等，符合大于等于的条件，而且这样是最优情况。所以每次 $1$ 的数量都会 $\times 2+2$，那么只需要一直枚举，到大于 $n$ 为止。

注意多测要清空。
### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,s;
int main(){
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		x=1,s=0;//清空，注意x=1，因为原本有一个，统计到最后了
		while(x<n)//枚举
		{
			x=x*2+2;//每次乘2并加2
			s++;//增加次数
		}
		printf("%d\n",s+1);//输出次数，原本还有一次要+1
	}
	return 0;
}
```

---

## 作者：_xguagua_Firefly_ (赞：0)

### 分析

题目要求是最小化操作一的数量，考虑贪心。设 $f _ i$ 为进行 $i$ 次操作一后染色格子的最大数量，则有 $f _ {i + 1} = 2(f _ i + 1)$。因为多执行了一次操作一，染色格子数量增加了 $1$，而最优方案为选择 $l = 1,r = 2(f _ i + 1)$ 执行一次操作二。

然后答案可以提前存在一个数组里，回答时找出来最小的 $i$，使 $f _ i \ge n$，暴力可以过，我用的二分。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int MAXN = 1e5 + 24;
int T;
int n,f[MAXN];
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int num = 1;
    for(int i = 1;num <= 1e6;i++)
    {
        f[i] = num++;
        num <<= 1;
    }
    cin >> T;
    while(T--)
    {
        cin >> n;
        cout << (lower_bound(f + 1,f + 20,n) - f) << "\n";
    }
}
```

---

