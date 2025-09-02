# Time Gap

## 题目描述

### 题目大意
给定$n$个数$d$，每个$d$都可以选择变成$24-d$或者保留数值，求任意两个数之间差的最小值中的最大值。

## 说明/提示

1$\leq$$n$$\leq$50\
0$\leq$$d_i$$\leq$12

## 样例 #1

### 输入

```
3
7 12 8```

### 输出

```
4```

## 样例 #2

### 输入

```
2
11 11```

### 输出

```
2```

## 样例 #3

### 输入

```
1
0```

### 输出

```
0```

# 题解

## 作者：installb (赞：1)

## 题目意思: 
给定n个数D,而且 $0<=D_i<=12$,每一个数可以选择保留它原来的值或把它变成 $24-D_i$  
求: 任意两数之间差的最小值 的最大值  

这题确实是道思路奇特的题目 一般看到最小值中的最大值 都会想到二分答案  
但这题并不是  

### 关键切入点: $0<=D_i<=12$  
这题和n完全没有关联!n多大都行  
如果一个数出现了**3次及以上** 那么无论怎么样都会存在两个一样的数 答案**一定是0**  
如果一个数出现了**2次** 那么一定是一个为a,另一个为24-a 这样至少有希望答案大于零  
如果一个数出现了**1次** 直接暴力枚举所有出现1次的数的情况 由于12的限制时间一定够  

### 细节:  
除了输入的D 有一个人的D为0 一开始加上去  

此题完结
## code:
```cpp
#include <map>
#include <list>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LL long long
using namespace std;

int n,a;
int cnt[255] = {0};
int q1[255] = {0},q2[255] = {0},h1 = 0,h2 = 0;
int q[255] = {0},h = 0; // q存的是某个状态下所有的数
int ans,maxn = 0;

int main(){
	scanf("%d",&n); cnt[0] = 1; // 把0先加上去
	for(int i = 1;i <= n;i ++){
		scanf("%d",&a);
		cnt[a] ++; // 统计数量
	}
	for(int i = 0;i <= 12;i ++){
		if(cnt[i] >= 3){
			printf("0\n");
			return 0;
		}
		if(cnt[i] == 1) q1[++ h1] = i; // q1存所有出现一次的数
		if(cnt[i] == 2){
			q2[++ h2] = i;
			q2[++ h2] = 24 - i; // q2存入出现两次的数(原数d和24-d)
		}
	}
	for(int i = 0;i < (1 << (h1 + 1));i += 2){
      // 直接二进制枚举取d还是24-d 我q1从1开始 所以要(h1+1)和i+=2
		h = 0; ans = 25;
		for(int j = 1;j <= h1;j ++){
			if(i & (1 << j)) q[++ h] = q1[j];
			else q[++ h] = 24 - q1[j]; // 对应存入q
		}
		for(int j = 1;j <= h2;j ++) q[++ h] = q2[j];
      // q2直接全扔进去
		q[++ h] = 24; // 注意最后还要扔个24 (即0和最大数之间的差距)
		sort(q + 1,q + 1 + h); // 排序后计算min 取max
		for(int i = 2;i <= h;i ++) ans = min(ans,q[i] - q[i - 1]);
		maxn = max(maxn,ans);
	}
	printf("%d\n",maxn);
	return 0;
}
```

---

## 作者：ISTP (赞：0)

死因：翻译有误。

## 题意简述

[原题链接：https://www.luogu.com.cn/problem/AT_cf17_final_c](https://www.luogu.com.cn/problem/AT_cf17_final_c)

但是截止到 24.11.10 的翻译还是错的，新翻译已经交了，这里也挂一下，有对题面进行改动但是抽象出来一样：[https://www.luogu.com.cn/paste/5re2trzh](https://www.luogu.com.cn/paste/5re2trzh)

转化一下：有 $n$ 个数 $(1 \le n \le 50)$，第 $i$ 个数为 $d_i(0 \le d_i \le 12)$，你可以将一些 $d_i$ 改成 $24-d_i$，然后在这些数中加入 $0$ 和 $24$ ，使序列中的数两两作差的绝对值的最小值最大。

拿样例一举例子，把 $d_3=8$ 改成 $24-8=16$ 后，有序列 $0,7,12,16,24$，两两作差，最小值 $s$ 为 $16-12=4$。枚举一下可以证明这是最大的 $s$。

## 思路

$n$ 很小，考虑暴力一点的做法。

容易发现，当改动好的序列中有相同的数时，答案总为 $0$。

注意到 $d_i \in [0,12]$。

首先 $0$ 肯定不可以有，因为最后要加进来 $0$ 和 $24$，改不改都会撞上；$d_i \in [1,11]$ 有某个数出现 $2$ 次的话，肯定会把其中一个变成 $24-d_i$；要是 $d_i=12$ 就只能出现 $1$ 次，原因显然。

那么当 $d_i \in [1,11]$ 有某数在原序列出现超过 $2$ 次时，或者有 $d_i=0$，又或者 $d_i=12$ 出现超过 $1$ 次时，无论怎么操作答案都为 $0$。

结合以上可得需要计算的 $n \le 23$。这个范围内暴搜变得可行。

暴搜每个 $d_i$ 是否改成 $24-d_i$，选完后判断合法性，时间复杂度 $O(2^n)$。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 55;

void input();
int n;
int d[maxn];

void solve();

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	input();
	solve();
	return 0;
}

int dfs(int);

void solve(){

	if(n > 23) return void(cout << 0 << '\n');
	return void(cout << dfs(1) << '\n');
}

int num[maxn];

int dfs(int x){

	if(x > n){

		int tmp[maxn];
		for(int i = 1; i <= n; i ++) tmp[i] = num[i];
		sort(tmp + 1, tmp + n + 1);
		int res = tmp[1];
		for(int i = 2; i <= n; i ++) res = min(res, tmp[i] - tmp[i - 1]);

		return min(res, 24 - tmp[n]);
	}

	num[x] = d[x];
	int res = dfs(x + 1);
	if(d[x] == 0 || d[x] == 12) return res;
	num[x] = 24 - d[x];
	res = max(res, dfs(x + 1));
	return res;
}
void input(){

	cin >> n;
	for(int i = 1; i <= n; i ++) cin >> d[i];
	return ;
}
```

完结撒花。有解释不到位的地方欢迎评论区提出。

---

