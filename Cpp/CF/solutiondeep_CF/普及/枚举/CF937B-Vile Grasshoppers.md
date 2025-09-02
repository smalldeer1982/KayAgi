# 题目信息

# Vile Grasshoppers

## 题目描述

The weather is fine today and hence it's high time to climb the nearby pine and enjoy the landscape.

The pine's trunk includes several branches, located one above another and numbered from $ 2 $ to $ y $ . Some of them (more precise, from $ 2 $ to $ p $ ) are occupied by tiny vile grasshoppers which you're at war with. These grasshoppers are known for their awesome jumping skills: the grasshopper at branch $ x $ can jump to branches ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF937B/e256171e16de0ce2bc4667496d6c5befd611ffc8.png).

Keeping this in mind, you wisely decided to choose such a branch that none of the grasshoppers could interrupt you. At the same time you wanna settle as high as possible since the view from up there is simply breathtaking.

In other words, your goal is to find the highest branch that cannot be reached by any of the grasshoppers or report that it's impossible.

## 说明/提示

In the first sample case grasshopper from branch $ 2 $ reaches branches $ 2 $ , $ 4 $ and $ 6 $ while branch $ 3 $ is initially settled by another grasshopper. Therefore the answer is $ 5 $ .

It immediately follows that there are no valid branches in second sample case.

## 样例 #1

### 输入

```
3 6
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 4
```

### 输出

```
-1
```

# AI分析结果

### 题目中文重写
# 讨厌的蚱蜢

## 题目描述
今天天气很好，正是爬上附近的松树欣赏风景的好时机。

松树的树干上有几个树枝，它们一个接一个地排列着，编号从 $2$ 到 $y$。其中一些树枝（更准确地说，从 $2$ 到 $p$）被微小的讨厌的蚱蜢占据了，而你正在与这些蚱蜢作战。这些蚱蜢以其惊人的跳跃能力而闻名：位于树枝 $x$ 上的蚱蜢可以跳到树枝 $\lfloor \frac{x}{k} \rfloor$（$k$ 为正整数）。

考虑到这一点，你明智地决定选择一个没有蚱蜢能够干扰你的树枝。同时，你希望尽可能地爬到高处，因为从高处看到的风景简直令人叹为观止。

换句话说，你的目标是找到最高的、任何蚱蜢都无法到达的树枝，或者报告这是不可能的。

## 说明/提示
在第一个样例中，位于树枝 $2$ 的蚱蜢可以跳到树枝 $2$、$4$ 和 $6$，而树枝 $3$ 最初就被另一只蚱蜢占据了。因此，答案是 $5$。

由此可以立即得出，在第二个样例中没有有效的树枝。

## 样例 #1
### 输入
```
3 6
```
### 输出
```
5
```

## 样例 #2
### 输入
```
3 4
```
### 输出
```
-1
```

### 综合分析与结论
这些题解的核心思路都是从 $y$ 开始倒序遍历到 $p + 1$，对于每个数，检查它是否是 $2$ 到 $p$ 中任何一个数的倍数，如果不是则输出该数，若遍历完都没找到则输出 $-1$。

算法要点在于判断一个数是否为 $2$ 到 $p$ 中数的倍数时，为了优化时间复杂度，只需要检查到 $\sqrt{该数}$ 即可。

解决的难点在于时间复杂度的控制，由于小于等于 $10^9$ 的两个质数之间的差最大不超过 $300$，所以整体时间复杂度在可接受范围内。

### 所选题解
- **hu1029282594（5星）**
    - **关键亮点**：对时间复杂度进行了详细分析，指出小于等于 $10^9$ 的两个质数之间的差最大不超过 $300$，从而说明算法的可行性。
    - **个人心得**：“要不是看到讨论，我永远想不到这样能过”，表明该题的时间复杂度分析较难，需要参考他人讨论。
```cpp
#include<bits/stdc++.h>
#define MAXN 50000050 
using namespace std;
int p,y;
int main()
{
	scanf("%d%d",&p,&y);
	for(;y>=2;y--)
	{
		if(y<=p){
			printf("%d\n",-1);
			break;
		}
		bool ok=1;
		for(register int i=2;i*i<=y&&i<=p;i++)
		if(y%i==0){ok=false;break;}
		if(ok){
			printf("%d\n",y);break;
		}
	}
	return 0;	
} 
```
核心实现思想：从 $y$ 开始倒序遍历，对于每个数 $y$，检查它是否能被 $2$ 到 $\min(\sqrt{y}, p)$ 中的数整除，如果都不能整除则输出 $y$，若 $y$ 小于等于 $p$ 则输出 $-1$。

- **Jasper08（4星）**
    - **关键亮点**：用线性筛筛出区间 $[2,\min(p,\sqrt{y})]$ 之间的质数，然后用质数来判断，减少了不必要的判断。
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <bitset>

using namespace std;

const int N = 5e4+10; 
int primes[N], cnt;
bitset<N> st; 

void get_primes(int n) { 
	st[0] = st[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!st[i])
			primes[cnt ++] = i;
		for (int j = 0; primes[j] <= n/i && j < cnt; ++j) {
			st[i*primes[j]] = 1;
			if (i % primes[j] == 0)
				break;
		}
	}
}

int main() {
	int p, y;
	scanf("%d%d", &p, &y);
	int t = (int)sqrt(y) > p ? p : (int)sqrt(y); 
	get_primes(t);
	for (int i = y; i > p; --i) { 
		bool check = 1;
		for (int j = 0; j < cnt; ++j) { 
			if (i % primes[j] == 0) {
				check = 0;
				break;
			}
		}
		if (check) {
			printf("%d\n", i); 
			return 0; 
		}
	}
	puts("-1"); 
	return 0;
}
```
核心实现思想：先通过线性筛筛出 $[2,\min(p,\sqrt{y})]$ 之间的质数，然后从 $y$ 倒序遍历到 $p + 1$，对于每个数，检查它是否能被筛出的质数整除，若都不能整除则输出该数，若遍历完都没找到则输出 $-1$。

### 最优关键思路或技巧
- 倒序遍历：从 $y$ 开始倒序遍历到 $p + 1$，可以保证找到的第一个满足条件的数就是最大值。
- 优化判断范围：判断一个数是否为 $2$ 到 $p$ 中数的倍数时，只需要检查到 $\sqrt{该数}$ 即可，减少不必要的判断。
- 利用质数性质：可以只筛出 $[2,\min(p,\sqrt{y})]$ 之间的质数，用质数来判断，进一步减少判断次数。

### 可拓展之处
同类型题或类似算法套路：
- 求区间内满足某种条件的最大或最小数，通常可以采用倒序或正序遍历的方法。
- 判断一个数是否为其他数的倍数或质数相关问题，可以利用质数的性质和优化判断范围的方法来减少时间复杂度。

### 推荐洛谷题目
- [P1217 [USACO1.5] 回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
- [P1075 [NOIP2012 普及组] 质因数分解](https://www.luogu.com.cn/problem/P1075)
- [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)

---
处理用时：33.42秒