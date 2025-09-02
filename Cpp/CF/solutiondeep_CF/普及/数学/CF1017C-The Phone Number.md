# 题目信息

# The Phone Number

## 题目描述

Mrs. Smith is trying to contact her husband, John Smith, but she forgot the secret phone number!

The only thing Mrs. Smith remembered was that any permutation of $ n $ can be a secret phone number. Only those permutations that minimize secret value might be the phone of her husband.

The sequence of $ n $ integers is called a permutation if it contains all integers from $ 1 $ to $ n $ exactly once.

The secret value of a phone number is defined as the sum of the length of the longest increasing subsequence (LIS) and length of the longest decreasing subsequence (LDS).

A subsequence $ a_{i_1}, a_{i_2}, \ldots, a_{i_k} $ where $ 1\leq i_1 < i_2 < \ldots < i_k\leq n $ is called increasing if $ a_{i_1} < a_{i_2} < a_{i_3} < \ldots < a_{i_k} $ . If $ a_{i_1} > a_{i_2} > a_{i_3} > \ldots > a_{i_k} $ , a subsequence is called decreasing. An increasing/decreasing subsequence is called longest if it has maximum length among all increasing/decreasing subsequences.

For example, if there is a permutation $ [6, 4, 1, 7, 2, 3, 5] $ , LIS of this permutation will be $ [1, 2, 3, 5] $ , so the length of LIS is equal to $ 4 $ . LDS can be $ [6, 4, 1] $ , $ [6, 4, 2] $ , or $ [6, 4, 3] $ , so the length of LDS is $ 3 $ .

Note, the lengths of LIS and LDS can be different.

So please help Mrs. Smith to find a permutation that gives a minimum sum of lengths of LIS and LDS.

## 说明/提示

In the first sample, you can build a permutation $ [3, 4, 1, 2] $ . LIS is $ [3, 4] $ (or $ [1, 2] $ ), so the length of LIS is equal to $ 2 $ . LDS can be ony of $ [3, 1] $ , $ [4, 2] $ , $ [3, 2] $ , or $ [4, 1] $ . The length of LDS is also equal to $ 2 $ . The sum is equal to $ 4 $ . Note that $ [3, 4, 1, 2] $ is not the only permutation that is valid.

In the second sample, you can build a permutation $ [2, 1] $ . LIS is $ [1] $ (or $ [2] $ ), so the length of LIS is equal to $ 1 $ . LDS is $ [2, 1] $ , so the length of LDS is equal to $ 2 $ . The sum is equal to $ 3 $ . Note that permutation $ [1, 2] $ is also valid.

## 样例 #1

### 输入

```
4
```

### 输出

```
3 4 1 2
```

## 样例 #2

### 输入

```
2
```

### 输出

```
2 1
```

# AI分析结果

### 题目内容重写

#### 题目描述

Smith夫人试图联系她的丈夫John Smith，但她忘记了秘密电话号码！

Smith夫人唯一记得的是，任何$n$的排列都可以是秘密电话号码。只有那些使秘密值最小的排列才可能是她丈夫的电话号码。

一个包含$n$个整数的序列被称为排列，如果它恰好包含从$1$到$n$的所有整数。

电话号码的秘密值定义为最长递增子序列（LIS）的长度与最长递减子序列（LDS）的长度之和。

一个子序列$a_{i_1}, a_{i_2}, \ldots, a_{i_k}$，其中$1\leq i_1 < i_2 < \ldots < i_k\leq n$，如果$a_{i_1} < a_{i_2} < a_{i_3} < \ldots < a_{i_k}$，则称为递增子序列。如果$a_{i_1} > a_{i_2} > a_{i_3} > \ldots > a_{i_k}$，则称为递减子序列。最长递增/递减子序列是指在所有递增/递减子序列中长度最长的子序列。

例如，如果有一个排列$[6, 4, 1, 7, 2, 3, 5]$，它的LIS是$[1, 2, 3, 5]$，因此LIS的长度为$4$。LDS可以是$[6, 4, 1]$、$[6, 4, 2]$或$[6, 4, 3]$，因此LDS的长度为$3$。

注意，LIS和LDS的长度可以不同。

请帮助Smith夫人找到一个使LIS和LDS长度之和最小的排列。

#### 说明/提示

在第一个样例中，你可以构造一个排列$[3, 4, 1, 2]$。LIS是$[3, 4]$（或$[1, 2]$），因此LIS的长度为$2$。LDS可以是$[3, 1]$、$[4, 2]$、$[3, 2]$或$[4, 1]$。LDS的长度也为$2$。因此，它们的和为$4$。注意，$[3, 4, 1, 2]$并不是唯一有效的排列。

在第二个样例中，你可以构造一个排列$[2, 1]$。LIS是$[1]$（或$[2]$），因此LIS的长度为$1$。LDS是$[2, 1]$，因此LDS的长度为$2$。它们的和为$3$。注意，排列$[1, 2]$也是有效的。

#### 样例 #1

##### 输入

```
4
```

##### 输出

```
3 4 1 2
```

#### 样例 #2

##### 输入

```
2
```

##### 输出

```
2 1
```

### 题解综合分析与结论

该题的核心目标是通过构造一个排列，使得其最长递增子序列（LIS）和最长递减子序列（LDS）的长度之和最小。通过分析，可以发现将排列分成多个块，块内递增，块间递减，能够有效地最小化LIS和LDS的长度之和。最优的块长通常取$\sqrt{n}$，因为这样可以在数学上最小化$LIS + LDS$的值。

### 所选高星题解

#### 1. 作者：FxorG (赞：7)  
**星级：5星**  
**关键亮点：**  
- 通过分块的思想，将排列分成多个块，块内递增，块间递减，从而最小化LIS和LDS的长度之和。
- 使用$\sqrt{n}$作为块长，并通过数学推导证明了其最优性。
- 代码简洁明了，易于理解。

**核心代码：**
```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int n,bl;

int main() {
	scanf("%d",&n);
	bl=sqrt(n);
	while(n>0) {
		for(int i=n-bl+1;i<=n;i++) {
			if(i>0) printf("%d ",i);
		}
		n-=bl;
	}
	return 0;
}
```

#### 2. 作者：皎月半洒花 (赞：3)  
**星级：4星**  
**关键亮点：**  
- 通过Dilworth定理，证明了LIS和LDS的长度之和的最小值，并给出了构造方法。
- 详细解释了如何通过分块构造排列，使得LIS和LDS的长度之和最小。
- 代码实现清晰，逻辑严谨。

**核心代码：**
```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>

const int N = 300010 ;

int n, m ;
int ans[N] ;

int main(){
    scanf("%d", &n) ;
    m = std :: ceil(std :: sqrt(n)) ;
    int p = 0, q, k = n ;
    for (int i = 1 ; i <= std :: ceil(1.0 * n / m) ; ++ i){
        q = p ; for (int j = 1 ; j <= m && p < n ; ++ j) ans[++ p] = k -- ;
        std :: reverse(ans + q + 1, ans + p + 1) ;
    }
    for (int i = 1 ; i <= n ; ++ i)
        printf("%d ", ans[i]) ; return 0 ;
}
```

#### 3. 作者：agicy (赞：3)  
**星级：4星**  
**关键亮点：**  
- 通过大量数据模拟，得出了分块构造排列的结论，并通过数学推导证明了其正确性。
- 详细解释了如何通过分块构造排列，使得LIS和LDS的长度之和最小。
- 代码实现简洁，逻辑清晰。

**核心代码：**
```cpp
#include<stdio.h>
#include<math.h>

int n;

int main(void){
	register int i,root;
	scanf("%d",&n);
	root=sqrt(n);
	while(n>0){
		for(i=n-root+1;i<=n;i++)
			if(i>0)
				printf("%d ",i);
		n-=root;
	}
	return 0;
}
```

### 最优关键思路或技巧

1. **分块构造排列**：将排列分成多个块，块内递增，块间递减，能够有效地最小化LIS和LDS的长度之和。
2. **数学推导**：通过数学推导，证明块长取$\sqrt{n}$时，$LIS + LDS$的值最小。
3. **代码实现**：通过简单的循环和数学运算，实现分块构造排列的算法。

### 可拓展之处

该题的思路可以拓展到其他需要构造排列以优化某些指标的题目中，例如构造排列使得某些特定子序列的长度最小或最大。类似的问题可以通过分块、数学推导等方法来解决。

### 推荐相似题目

1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
2. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)
3. [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)

---
处理用时：57.18秒