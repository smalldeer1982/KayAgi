# 题目信息

# Another Array Problem

## 题目描述

You are given an array $ a $ of $ n $ integers. You are allowed to perform the following operation on it as many times as you want (0 or more times):

- Choose $ 2 $ indices $ i $ , $ j $ where $ 1 \le i < j \le n $ and replace $ a_k $ for all $ i \leq k \leq j $ with $ |a_i - a_j| $

Print the maximum sum of all the elements of the final array that you can obtain in such a way.

## 说明/提示

In the first test case, it is not possible to achieve a sum $ > 3 $ by using these operations, therefore the maximum sum is $ 3 $ .

In the second test case, it can be shown that the maximum sum achievable is $ 16 $ . By using operation $ (1,2) $ we transform the array from $ [9,1] $ into $ [8,8] $ , thus the sum of the final array is $ 16 $ .

In the third test case, it can be shown that it is not possible to achieve a sum $ > 18 $ by using these operations, therefore the maximum sum is $ 18 $ .

## 样例 #1

### 输入

```
3
3
1 1 1
2
9 1
3
4 9 5```

### 输出

```
3
16
18```

# AI分析结果

### 题目内容（中文重写）
# 另一个数组问题

## 题目描述
给定一个包含 $n$ 个整数的数组 $a$。允许对该数组进行任意次数（0 次或多次）以下操作：

- 选择两个索引 $i$ 和 $j$，其中 $1 \leq i < j \leq n$，并将所有 $i \leq k \leq j$ 的 $a_k$ 替换为 $|a_i - a_j|$。

打印通过这种方式可以得到的最终数组所有元素的最大和。

## 说明/提示
在第一个测试用例中，使用这些操作无法获得大于 3 的和，因此最大和为 3。

在第二个测试用例中，可以证明可达到的最大和为 16。通过使用操作 $(1,2)$，我们将数组从 $[9,1]$ 转换为 $[8,8]$，因此最终数组的和为 16。

在第三个测试用例中，可以证明使用这些操作无法获得大于 18 的和，因此最大和为 18。

## 样例 #1
### 输入
```
3
3
1 1 1
2
9 1
3
4 9 5
```

### 输出
```
3
16
18
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过分类讨论来解决问题，主要是根据数组长度 $n$ 的不同情况进行分析：
- **$n = 1$**：答案就是数组中的唯一元素 $a_1$。
- **$n = 2$**：比较不操作时的和 $a_1 + a_2$ 与操作一次后得到的和 $2\times|a_1 - a_2|$，取最大值。
- **$n = 3$**：情况较为复杂，需要分多种情况讨论，包括最大元素的位置等，最终答案是多个可能结果中的最大值。
- **$n \geq 4$**：可以通过一系列操作将数组中的所有元素都变为数组中的最大值，所以最大和为 $n\times\max\{a_i\}$。

各题解的主要区别在于对 $n = 3$ 情况的讨论方式和代码实现细节。

### 所选题解
- **tZEROちゃん（5星）**
    - **关键亮点**：思路清晰，对不同情况的讨论详细且有条理，代码简洁明了，直接给出了核心代码，便于理解。
- **qiuzijin2026（4星）**
    - **关键亮点**：思路完整，代码实现规范，有详细的注释，适合初学者参考。
- **baoziwu2（4星）**
    - **关键亮点**：不仅给出了分类讨论的结果，还对 $n \geq 4$ 的情况进行了详细的证明，逻辑严谨。

### 重点代码
#### tZEROちゃん的核心代码
```cpp
void solve() {
   int n; cin >> n;
   rep (i, 1, n) cin >> a[i];
   if (n == 1) printf("%d\n", a[1]);
   else if (n == 2) {
      printf("%lld\n", max(2 * abs(a[1] - a[2]), a[1] + a[2]));
   } else if (n == 3) {
      printf("%lld\n", max({3 * abs(a[1] - a[2]), 3 * abs(a[3] - a[2]), 3 * a[1], 3 * a[3], a[1] + a[2] + a[3]}));
   } else { sort(a + 1, a + n + 1);
      printf("%lld\n", a[n] * n);
   }
}
```
**核心实现思想**：根据数组长度 $n$ 的不同情况进行分类讨论，分别计算最大和并输出。

#### qiuzijin2026的核心代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t;
long long n;
long long a[200005];
long long maxx;
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		maxx=0;
		for(long long i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			maxx=max(a[i],maxx);
		}
		if(n>=4) printf("%lld\n",maxx*n);
		else if(n==3)  printf("%lld\n",max(max(3*abs(a[1]-a[2]),3*abs(a[3]-a[2])),max(max(3*a[1],3*a[3]),a[1]+a[2]+a[3])));
		else if(n==2) printf("%lld\n",max(2*abs(a[1]-a[2]),a[1]+a[2]));
		else if(n==1) printf("%lld\n",a[1]);;
	}
	return 0;
}
```
**核心实现思想**：通过循环处理多组测试数据，对于每组数据，先找出数组中的最大值，再根据数组长度 $n$ 进行分类讨论，输出最大和。

#### baoziwu2的核心代码
```python
T = int(input())
for _ in range(T):
	n = int(input())
	a = list(map(int, input().split()))
	if(n == 1): print(a[0]);
	elif(n == 2): print(max(2 * abs(a[0] - a[1]), a[0] + a[1]))
	elif(n == 3): print(max(3 * abs(a[0] - a[1]), 3 * abs(a[2] - a[1]), 3 * a[0], 3 * a[2], a[0] + a[1] + a[2]))
	else: print(max(a) * n)
```
**核心实现思想**：使用 Python 语言，通过循环处理多组测试数据，根据数组长度 $n$ 进行分类讨论，输出最大和。

### 关键思路或技巧
- **分类讨论**：根据数组长度 $n$ 的不同情况进行分类讨论，简化问题的复杂度。
- **构造操作**：对于 $n \geq 4$ 的情况，通过构造一系列操作将数组中的所有元素都变为最大值。

### 可拓展之处
同类型题或类似算法套路可能会涉及到对数组的其他操作，如修改元素、交换元素等，然后求数组的某种最优值。解题思路可能仍然是通过分类讨论和构造操作来实现。

### 推荐洛谷题目
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：涉及到对棋盘上棋子移动的操作和路径计数，需要通过递推或动态规划来解决。
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的 0 - 1 背包问题，需要通过动态规划来解决。
- [P1216 [USACO1.5][IOI1994]数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：可以通过动态规划来求解从顶部到底部的最大路径和。

### 个人心得
yingkeqian9217：“这道题让我认识到了一句古老的真理——十年 OI 一场空，不开 long long 见祖宗！(doge)”，提醒我们在处理可能出现大数值的题目时，要注意数据类型的选择，避免溢出问题。

---
处理用时：48.96秒