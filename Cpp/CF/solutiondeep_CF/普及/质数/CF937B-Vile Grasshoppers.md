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

松树的树干上有几个树枝，它们一个比一个高，编号从 $2$ 到 $y$。其中一些树枝（更准确地说，从 $2$ 到 $p$）被微小讨厌的蚱蜢占据了，而你正在与这些蚱蜢作战。这些蚱蜢以其惊人的跳跃能力而闻名：位于树枝 $x$ 上的蚱蜢可以跳到树枝 $k \cdot x$（$k$ 为正整数）。

考虑到这一点，你明智地决定选择一个没有蚱蜢能干扰你的树枝。同时，你想尽可能地爬到高一些，因为从高处看到的风景简直令人叹为观止。

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
- **思路**：各题解思路基本一致，都是从 $y$ 开始倒序遍历到 $p + 1$，对于每个数检查是否是 $2$ 到 $p$ 中任何一个数的倍数，若不是则该数即为所求，若遍历完都没找到则输出 $-1$。
- **算法要点**：核心在于判断一个数是否是 $2$ 到 $p$ 中数的倍数，为了优化时间复杂度，多数题解利用了只需要检查到 $\sqrt{该数}$ 的性质。部分题解还提到了小于等于 $10^9$ 的两个质数之间的差最大不超过 $300$ 这一特性，说明算法的可行性。
- **解决难点**：主要难点在于时间复杂度的控制，由于数据范围较大，直接暴力枚举会超时，通过只检查到 $\sqrt{该数}$ 以及利用质数间距的特性，将时间复杂度控制在可接受范围内。

### 所选题解
- **hu1029282594（5星）**
  - **关键亮点**：思路清晰，对时间复杂度的分析详细，解释了算法能通过的原因。
  - **个人心得**：提到“要不是看到讨论，我永远想不到这样能过”，说明该题时间复杂度的分析较难，需要参考讨论才能确定算法的可行性。
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
核心实现思想：从 $y$ 开始倒序遍历，对于每个数 $y$，检查 $2$ 到 $\min(\sqrt{y}, p)$ 之间的数是否能整除 $y$，若都不能整除则 $y$ 即为所求。

- **Jasper08（4星）**
  - **关键亮点**：通过线性筛筛出 $[2,\min(p,\sqrt{y})]$ 之间的质数，再进行判断，进一步优化了判断过程。
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
核心实现思想：先通过线性筛筛出 $[2,\min(p,\sqrt{y})]$ 之间的质数，然后从 $y$ 开始倒序遍历，对于每个数检查是否能被这些质数整除。

### 最优关键思路或技巧
- 利用只需要检查到 $\sqrt{该数}$ 的性质来优化时间复杂度。
- 利用小于等于 $10^9$ 的两个质数之间的差最大不超过 $300$ 这一特性，说明算法的可行性。
- 对于判断一个数是否是某些数的倍数的问题，可以先筛出质数，再进行判断，进一步优化。

### 可拓展之处
同类型题或类似算法套路：在处理范围较大的数的倍数判断问题时，可采用类似的倒序遍历和只检查到 $\sqrt{该数}$ 的方法。对于需要频繁判断是否为某些数倍数的问题，可以考虑先筛出质数再进行判断。

### 推荐洛谷题目
- P1217 [USACO1.5] 回文质数 Prime Palindromes
- P1075 质因数分解
- P3383 【模板】线性筛素数

### 个人心得总结
部分题解作者提到该题时间复杂度分析较难，需要参考讨论才能确定算法的可行性，说明在遇到复杂的时间复杂度问题时，可以参考他人的讨论和经验。 

---
处理用时：47.78秒