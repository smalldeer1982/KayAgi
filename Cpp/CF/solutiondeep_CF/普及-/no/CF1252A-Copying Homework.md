# 题目信息

# Copying Homework

## 题目描述

Danang and Darto are classmates. They are given homework to create a permutation of $ N $ integers from $ 1 $ to $ N $ . Danang has completed the homework and created a permutation $ A $ of $ N $ integers. Darto wants to copy Danang's homework, but Danang asks Darto to change it up a bit so it does not look obvious that Darto copied.

The difference of two permutations of $ N $ integers $ A $ and $ B $ , denoted by $ diff(A, B) $ , is the sum of the absolute difference of $ A_i $ and $ B_i $ for all $ i $ . In other words, $ diff(A, B) = \Sigma_{i=1}^N |A_i - B_i| $ . Darto would like to create a permutation of $ N $ integers that maximizes its difference with $ A $ . Formally, he wants to find a permutation of $ N $ integers $ B_{max} $ such that $ diff(A, B_{max}) \ge diff(A, B') $ for all permutation of $ N $ integers $ B' $ .

Darto needs your help! Since the teacher giving the homework is lenient, any permutation of $ N $ integers $ B $ is considered different with $ A $ if the difference of $ A $ and $ B $ is at least $ N $ . Therefore, you are allowed to return any permutation of $ N $ integers $ B $ such that $ diff(A, B) \ge N $ .

Of course, you can still return $ B_{max} $ if you want, since it can be proven that $ diff(A, B_{max}) \ge N $ for any permutation $ A $ and $ N > 1 $ . This also proves that there exists a solution for any permutation of $ N $ integers $ A $ . If there is more than one valid solution, you can output any of them.

## 说明/提示

Explanation for the sample input/output #1

With $ A = [1, 3, 2, 4] $ and $ B = [4, 2, 3, 1] $ , $ diff(A, B) = |1 - 4| + |3 - 2| + |2 - 3| + |4 - 1| = 3 + 1 + 1 + 3 = 8 $ . Since $ 8 \ge 4 $ , $ [4, 2, 3, 1] $ is one of the valid output for this sample.

## 样例 #1

### 输入

```
4
1 3 2 4
```

### 输出

```
4 2 3 1
```

## 样例 #2

### 输入

```
2
2 1
```

### 输出

```
1 2
```

# AI分析结果

### 题目内容
# 抄袭作业

## 题目描述
达南（Danang）和达托（Darto）是同班同学。他们接到作业，要求创建一个由1到N的N个整数组成的排列。达南已经完成了作业，并创建了一个由N个整数组成的排列A。达托想抄袭达南的作业，但达南要求达托稍微改动一下，以免看起来明显是抄袭的。

两个由N个整数组成的排列A和B之间的差异，用diff(A, B)表示，是所有i对应的|Aᵢ - Bᵢ|的总和。换句话说，diff(A, B) = Σᵢ₌₁ᴺ |Aᵢ - Bᵢ|。达托想创建一个由N个整数组成的排列，使其与A的差异最大化。正式地说，他想找到一个由N个整数组成的排列Bₘₐₓ，使得对于所有由N个整数组成的排列B'，都有diff(A, Bₘₐₓ) ≥ diff(A, B')。

达托需要你的帮助！由于布置作业的老师比较宽容，如果A和B的差异至少为N，那么任何由N个整数组成的排列B都被认为与A不同。因此，你可以返回任何由N个整数组成的排列B，只要diff(A, B) ≥ N。

当然，如果你愿意，你仍然可以返回Bₘₐₓ，因为可以证明对于任何排列A和N > 1，都有diff(A, Bₘₐₓ) ≥ N。这也证明了对于任何由N个整数组成的排列A都存在解。如果有多个有效解，你可以输出其中任何一个。

## 说明/提示
样例输入/输出#1的解释
对于A = [1, 3, 2, 4]和B = [4, 2, 3, 1]，diff(A, B) = |1 - 4| + |3 - 2| + |2 - 3| + |4 - 1| = 3 + 1 + 1 + 3 = 8。由于8 ≥ 4，[4, 2, 3, 1]是这个样例的有效输出之一。

## 样例 #1
### 输入
```
4
1 3 2 4
```
### 输出
```
4 2 3 1
```

## 样例 #2
### 输入
```
2
2 1
```
### 输出
```
1 2
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是通过特定的构造方法来生成满足diff(A, B) ≥ N的排列B。不同题解的构造方式略有不同，主要围绕对原排列A中1和N的处理，以及其他元素的安排。有的通过简单交换1和N的位置，有的将小于N的元素加1并特殊处理N元素等。各题解都能有效解决问题，但在思路清晰度、代码简洁性和优化程度上存在差异。

### 所选的题解
- **作者：残阳如血 (5星)**
  - **关键亮点**：思路清晰，先猜想一种构造方式并通过提交验证，后给出详细证明，还对空间复杂度进行了优化。从时间和空间复杂度角度全面分析。
  - **个人心得**：强调作为合格OIer需对猜想进行证明。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int N, tmp;
int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		cout << (tmp == N? 1 : tmp + 1) << " ";
	}
	return 0;
}
```
核心实现思想：读入每个数，若为N则输出1，否则输出该数加1 。
- **作者：LiAuPb (4星)**
  - **关键亮点**：思路直接，明确指出只需把值为1和N的数位置互换，通过简单计算说明这样能满足条件。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, x1, xn;
int a[100010];
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);    //输入
		if(a[i] == 1){    //如果值为一
			x1 = i;    //记录下标
		}
		if(a[i] == n){    //如果值为n
			xn = i;    //记录下标
		}
	}
	swap(a[x1], a[xn]);    //将值交换
	for(int i = 1; i <= n; i++){
		printf("%d ", a[i]);    //输出
	}
	return 0;
}
```
核心实现思想：遍历数组记录1和N的下标，然后交换这两个下标的值并输出数组。
- **作者：zjr0330 (4星)**
  - **关键亮点**：分析过程形象，通过具体例子说明将序列最小值换成n，最大值换成1的构造思路，代码简洁明了。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	long long n, a[100010], ss = 11451419198108122;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		ss = min(ss, a[i]);    //记录下最小值。
	}
	for (int i = 1; i <= n; i++) {
		if (a[i] == 1) {
			cout << n << " ";    //如果是1，输出n。
		}
		else if (a[i] == n) {
			cout << ss << ' ';    //如果是n，输出1。
		} else {
			cout << a[i] << " ";    //否则照常输出。
		}
	}
	return 0;
}
```
核心实现思想：先遍历数组找到最小值，再遍历数组，若元素为1则输出n，若为n则输出最小值，其他元素原样输出。

### 最优关键思路或技巧
在构造满足条件的排列时，利用原排列中1和N这两个边界值，通过交换它们的位置或者对其进行特定变换（如将1换成N，N换成1 ；或N输出1，小于N的数输出自身加1），结合排列元素的特性，使构造的新排列与原排列的差值满足题目要求。这种利用边界值构造的方法简洁有效，能快速满足题目条件。

### 可拓展之处
同类型题通常围绕构造满足特定条件的序列或排列，类似算法套路是从边界值、特殊值入手，分析如何通过对这些值的操作来满足整体条件。例如在构造满足特定距离、和值等条件的序列时，可借鉴这种从特殊元素出发构造的思路。

### 洛谷相似题目推荐
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：涉及数的组合构造，需从给定数字中选取若干个数，使其和为质数，考察构造与质数判断。
- [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：通过给定火柴棒数量，构造满足等式的数字组合，属于构造与枚举结合的题目。
- [P1464 Function](https://www.luogu.com.cn/problem/P1464)：根据给定规则构造函数值，需要对函数规则进行分析并构造出满足条件的结果。 

---
处理用时：81.25秒