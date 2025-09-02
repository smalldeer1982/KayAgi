# Two strings

## 题目描述

You are given two strings $ a $ and $ b $ . You have to remove the minimum possible number of consecutive (standing one after another) characters from string $ b $ in such a way that it becomes a subsequence of string $ a $ . It can happen that you will not need to remove any characters at all, or maybe you will have to remove all of the characters from $ b $ and make it empty.

Subsequence of string $ s $ is any such string that can be obtained by erasing zero or more characters (not necessarily consecutive) from string $ s $ .

## 说明/提示

In the first example strings $ a $ and $ b $ don't share any symbols, so the longest string that you can get is empty.

In the second example ac is a subsequence of $ a $ , and at the same time you can obtain it by erasing consecutive symbols cepted from string $ b $ .

## 样例 #1

### 输入

```
hi
bob
```

### 输出

```
-
```

## 样例 #2

### 输入

```
abca
accepted
```

### 输出

```
ac
```

## 样例 #3

### 输入

```
abacaba
abcdcba
```

### 输出

```
abcba
```

# 题解

## 作者：Joker_M (赞：6)

CF762C Two strings

注意看题！！！

删除连续的一段！！！

首先最最最暴力的一种做法：

枚举删除的区间 $[l,r]$，再用删后的字符去进行匹配，不断更新最优解。

时间复杂度 $\mathcal O(n^3)$。

~~复杂度原地螺旋起飞~~

两个优化方向：

- 优化区间 $[l,r]$ 的枚举；
- 优化字符的匹配过程。

~~一共也就这两过程，说了和没说一样~~

显然区间具有单调性，

如果删掉了区间 $[l,r]$ 之后的 $s$ 能够成为 $t$ 的子序列，

那么你把 $[l,r]$ 往外面扩，多删一点字符，依然满足 $s$ 是 $t$ 的子序列。

所以我们可以枚举左端点 $l$，同时二分右端点 $r$，

把时间复杂度优化到 $\mathcal O(n^2\log n)$。

~~然而复杂度依旧爆炸~~

我们现在的瓶颈在于如何快速判断删掉之后的 $s$ 是不是 $t$ 的子序列。

来还原一下暴力的过程：

用两个指针 $i,j$ 指向 $s$ 和 $t$ 的第一个位置，

如果 $s_i=t_j$ ，那么两者匹配，同时 $i \gets i+1,j \gets j+1$；

否则 $j \gets j+1$。

如果最后所有的 $s_i$ 都能够在 $t$ 中找到一个对应的位置，那么 $s$ 就是 $t$ 的子序列，

同样的，如果我们的指针从后面往后面扫，也能够达到同样的效果。

于是我们就想到了一个优化方法：

对于 $s$ 的每一个字符 $s_i$，维护一个 $lp_i$ 和 $rp_i$。

设 $s$ 的长度为 $len$，

那么 $lp_i$ 表示 $s$ 中 $[1,i]$ 的字符全部匹配到 $t$ 里，第 $i$ 个位置在 $t$ 中对应的位置，

同理，$rp_i$ 表示 $s$ 中 $[i,len]$ 的字符全部匹配到 $t$ 里，第 $i$ 个位置在 $t$ 中对应的位置。

其中 $lp$ 的匹配是从前到后匹配，$rp$ 的匹配时从后往前匹配。

那么，如果我们要删除一段区间 $[l,r]$，

那我们只需要判断 $lp_{l-1} < rp_{r+1}$ 是否成立即可。

时间复杂度优化为 $\mathcal O(n \log n)$。

以及一个特殊情况：$s$ 本身就是 $t$ 的子序列，此时不需要删去任何元素，需要特判一下。



---

## 作者：封禁用户 (赞：4)

# 1.前言
题目链接：http://codeforces.com/contest/762/problem/C

 题目大意：
 
 给出两个字符串 a 和 b，现在从 b 中删去 1 个连续的子串，得到字符串 b'，
 要求 b' 是 a 的子序列；
 
 现在希望删除尽可能短的字符串，并输出 b'。
 

# 2.解析：
 - 暴力做法

枚举 $[l, r]$ 的可能性，得到新的字符串 bNew，对 a 和 bNew 做一次匹配；

 匹配的规则是对于 bNew 的每一个字符，都在原来基础上找最近的匹配，最后看 bNew 是否能在 a 中找到所有的字符匹配位置；
 枚举区间是 $O(N^2)$，匹配是 $O(N)$，总的复杂度是 $O(N^3)$。
 
 - 优化

性质1：

区间 $[l, r]$ 如果满足题意，那么 $[l-1, r]$ 或者 $[l, r+1]$ 也会满足题意；

 如果用动态规划，状态数有 $N^2$，已经超过限制，虽然动态规划的转移是整体 $O(N)$
 
可以再引入一个二分：二分区间长度。

 然后再枚举区间的起点，得到 bNew，再进行一次匹配；
 整体的复杂度是 $O(\log N)$ 的二分，$O(N)$ 的枚举区间起点， $O(N)$ 的单次匹配复杂度。
 
 这里单次匹配可以优化：
 
 $dp[i]$ 表示字符串 b，前 i 个字符匹配字符串 a 的最短长度。
 
 $dpR[i]$ 表示 reverse_b，前 i 个字符串匹配字符串 reverse_a 的最短长度；
 那么 $bNew=b$ 减去区间 $[l, r]=[1,l-1] + [r+1, len]$。
 
 只要 $dp[i]+dpR[j]≤lenA$，那么就有解；
 这样单次匹配的复杂度降到了 $O(1)$。
 
 总体的复杂度是 $O(\log N \times N)$，题目能接受的复杂度。

# 3.code
~~要抄题解直接把所有的接一起就行。~~

1. 定义没什么好说的
```cpp
char a[N], b[N];
char reverse_a[N], reverse_b[N];
int dp[N], dpR[N];
pair<int, int> ans;
```

2. find 函数
```cpp
bool find(int mid, int n, int m) {
    int t = mid;
    for (int i = 0; i+ mid <= m; ++i) {
        int sum = 0;
        if (i > 0) {
            sum += dp[i];
        }
        if (m - i - mid > 0) {
            sum += dpR[m - i - mid];
        }
        if (sum <= n) {
            ans = make_pair(i, i + mid - 1);
            return true;
        }
    
    }
    
    return false;
}
```

3. main 函数
```cpp
int main(){  
    int n, m;
    cin >> a >> b;
    n = (int)strlen(a), m = (int)strlen(b);
    for (int i = 0; i < n; ++i) {
        reverse_a[i] = a[n - i - 1];
    }
    for (int j = 0; j < m; ++j) {
        reverse_b[j] = b[m - j - 1];
    }
    for (int i = 1; i <= m; ++i) {
        int p = dp[i - 1] + 1; // 从上一个开始索引
        while (p <= n && a[p - 1] != b[i - 1]) {
            ++p;
        }
        if (p <= n) {
            dp[i] = p;
        }
        else {
            dp[i] = inf;
        }
        
        int r = dpR[i - 1] + 1;
        while (r <= n && reverse_a[r - 1] != reverse_b[i - 1]) {
            ++r;
        }
        if (r <= n) {
            dpR[i] = r;
        }
        else {
            dpR[i] = inf;
        }
    }
    
    
    
    int l = 0, r = m + 1;
    while (l < r) {
        int mid = (l + r) / 2;
        if (find(mid, n, m)) {
            r = mid;
        }
        else {
            l = mid + 1;
        }
    }
    
    if (ans.first == 0 && ans.second == m - 1) {
        cout << "-" << endl;
    }
    else {
        for (int i = 0; i < m; ++i) {
            if (i < ans.first || i > ans.second) {
                putchar(b[i]);
            }
        }
        puts("");
    }
    
    return 0;
}

```
参考资料：程序员进阶练习。


---

## 作者：幻影星坚强 (赞：1)

我们考虑对于每一个a串的前缀和后缀都能包含几个b串的前缀和后缀，之后枚举前缀长度并找到第一个a串的后缀使得两者所包含的b串没有重复部分。统计最小答案即可

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char a[1000010], b[1000010];
int len1, len2, mins, ll, rr; 
int q1[1000010], q2[1000010];
int main()
{
	scanf("%s%s", a + 1, b + 1);
	len1 = strlen(a + 1);
	len2 = strlen(b + 1);
	int now = 1;
	for (int i = 1; i <= len1; ++ i)
	{
		if(b[now] == a[i])
		{
			++ now;
		}
		q1[i] = now - 1;
	}
	now = len2;
	for (int i = len1; i >= 1; -- i)
	{
		if(b[now] == a[i])
		{
			-- now;
		}
		q2[i] = now + 1;
	}
	q2[len1 + 1] = len2 + 1;
	mins = 1e9;
	for (int i = 0; i < len1; ++ i)
	{
		int r = *upper_bound(q2 + i + 1, q2 + 1 + len1, q1[i]);
		int l = q1[i];
		if(r - l - 1 < mins)
		{
			mins = r - l - 1;
			ll = l;
			rr = r;
		}
	}
	int r = len2 + 1;
	int l = q1[len1];
	if(r - l - 1 < mins)
	{
		mins = r - l - 1;
		ll = l;
		rr = r;
	}
	for (int i = 1; i <= ll; ++ i)
	printf("%c", b[i]);
	for (int i = rr; i <= len2; ++ i)
	printf("%c", b[i]);
	if(ll < 1 && rr > len2)
	printf("-");
}
```


---

