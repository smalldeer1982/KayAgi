# 题目信息

# Lucky Permutation Triple

## 题目描述

Bike is interested in permutations. A permutation of length $ n $ is an integer sequence such that each integer from 0 to $ (n-1) $ appears exactly once in it. For example, $ [0,2,1] $ is a permutation of length 3 while both $ [0,2,2] $ and $ [1,2,3] $ is not.

A permutation triple of permutations of length $ n $ $ (a,b,c) $ is called a Lucky Permutation Triple if and only if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/bd0aa9c2cfa6e7dfc9681d8813c19703f16dbc42.png). The sign $ a_{i} $ denotes the $ i $ -th element of permutation $ a $ . The modular equality described above denotes that the remainders after dividing $ a_{i}+b_{i} $ by $ n $ and dividing $ c_{i} $ by $ n $ are equal.

Now, he has an integer $ n $ and wants to find a Lucky Permutation Triple. Could you please help him?

## 说明/提示

In Sample 1, the permutation triple $ ([1,4,3,2,0],[1,0,2,4,3],[2,4,0,1,3]) $ is Lucky Permutation Triple, as following holds:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/6124807a627fcd49ae8fab0d91c9fa90239af12b.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/598c5f3180986ca384de6df51e7cb84d8ea4e757.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/66b44a153ea212b6a13d195278ac6715ce383457.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/dd4f61ae15bc4151613d0da9fe47b466aa949e1e.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/0ea0fc069d3b3e3451d396fd4b6ef6f3d9456398.png).

In Sample 2, you can easily notice that no lucky permutation triple exists.

## 样例 #1

### 输入

```
5
```

### 输出

```
1 4 3 2 0
1 0 2 4 3
2 4 0 1 3
```

## 样例 #2

### 输入

```
2
```

### 输出

```
-1
```

# AI分析结果

### 题目重写
# Lucky Permutation Triple

## 题目描述

Bike 对排列感兴趣。一个长度为 $n$ 的排列是一个整数序列，其中每个整数从 0 到 $(n-1)$ 恰好出现一次。例如，$[0,2,1]$ 是一个长度为 3 的排列，而 $[0,2,2]$ 和 $[1,2,3]$ 不是。

一个长度为 $n$ 的排列三元组 $(a,b,c)$ 被称为 Lucky Permutation Triple，当且仅当对于所有的 $i$，$a_i + b_i \equiv c_i \pmod{n}$。其中 $a_i$ 表示排列 $a$ 的第 $i$ 个元素。上述模等式表示 $a_i + b_i$ 除以 $n$ 的余数与 $c_i$ 除以 $n$ 的余数相等。

现在，给定一个整数 $n$，Bike 想要找到一个 Lucky Permutation Triple。你能帮助他吗？

## 说明/提示

在样例 1 中，排列三元组 $([1,4,3,2,0],[1,0,2,4,3],[2,4,0,1,3])$ 是一个 Lucky Permutation Triple，因为以下等式成立：

- $1 + 1 \equiv 2 \pmod{5}$;
- $4 + 0 \equiv 4 \pmod{5}$;
- $3 + 2 \equiv 0 \pmod{5}$;
- $2 + 4 \equiv 1 \pmod{5}$;
- $0 + 3 \equiv 3 \pmod{5}$。

在样例 2 中，你可以很容易地注意到不存在 Lucky Permutation Triple。

## 样例 #1

### 输入

```
5
```

### 输出

```
1 4 3 2 0
1 0 2 4 3
2 4 0 1 3
```

## 样例 #2

### 输入

```
2
```

### 输出

```
-1
```

### 题解分析与结论

#### 综合分析
1. **无解情况**：当 $n$ 为偶数时，无解。因为 $a_i + b_i$ 的和在模 $n$ 下会出现重复，无法满足 $c_i$ 的唯一性。
2. **有解情况**：当 $n$ 为奇数时，可以通过简单的构造方法得到解。具体来说，前两行直接输出 $0$ 到 $n-1$ 的序列，第三行输出 $(i \times 2) \bmod n$ 的结果。

#### 最优关键思路
- **奇偶性分析**：通过分析 $n$ 的奇偶性，可以快速判断是否有解。
- **简单构造**：当 $n$ 为奇数时，直接构造 $a$ 和 $b$ 为 $0$ 到 $n-1$ 的序列，$c$ 为 $(i \times 2) \bmod n$。

#### 可拓展之处
- **模运算性质**：类似的题目可以通过模运算的性质来简化问题。
- **排列构造**：排列构造类问题通常需要找到特定的规律或性质来简化构造过程。

### 推荐题目
1. [P1036 选数](https://www.luogu.com.cn/problem/P1036)
2. [P1045 数的划分](https://www.luogu.com.cn/problem/P1045)
3. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)

### 所选高分题解

#### 题解1：作者：_Chjich_ (4星)
**关键亮点**：
- 简洁明了地分析了无解情况。
- 提供了简单的构造方法，代码清晰易读。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	if(n%2==0){
	   cout<<-1;
	   return 0;
	}
	for(int i=0;i<n;i++) 
      cout<<i<<" ";
	cout<<endl;
	for(int i=0;i<n;i++) 
      cout<<i<<" ";
    cout<<endl;
	for(int i=0;i<n;i++) 
      cout<<i*2%n<<" ";
	return 0;
}
```

#### 题解2：作者：DL_Lingkong (4星)
**关键亮点**：
- 详细证明了无解的情况。
- 提供了清晰的构造思路，代码结构良好。

**核心代码**：
```cpp
#include <iostream>
using namespace std;
int n;
void be() {
	cin >> n;
	return ;
}
void ei() {
	if(!(n & 1)) {
		puts("-1");
		return ;
	}
	for(int i = 0;i < n;i++) {
		cout << i << " \n"[i == n];
	}
	for(int i = 0;i < n;i++) {
		cout << i << " \n"[i == n];
	}
	for(int i = 0;i < n;i++) {
		cout << (i * 2 % n) << " \n"[i == n];
	}
	return ;
}
int main() {
	be();
	ei();
	return 0;
}
```

#### 题解3：作者：SpeedStar (4星)
**关键亮点**：
- 通过向量存储排列，代码可读性高。
- 提供了详细的构造方法，逻辑清晰。

**核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n;
	cin >> n;
	if (~n & 1) {
		cout << "-1\n";
		return 0;
	}
	vector<int> a(n + 1), b(n + 1), c(n + 1);
	for (int i = 1; i <= n; ++i) a[i] = i - 1;
	for (int i = 1; i < n; ++i) b[i] = i;
	b[n] = 0;
	for (int i = 1; i <= n; ++i) c[i] = (a[i] + b[i]) % n;
	for (int i = 1; i <= n; ++i) cout << a[i] << " \n"[i == n];
	for (int i = 1; i <= n; ++i) cout << b[i] << " \n"[i == n];
	for (int i = 1; i <= n; ++i) cout << c[i] << " \n"[i == n];
	return 0;
}
```

### 个人心得总结
- **调试经历**：在构造排列时，确保每个元素唯一且符合模运算的条件是关键。
- **踩坑教训**：忽略 $n$ 的奇偶性会导致无解情况的遗漏。
- **顿悟感想**：通过简单的数学分析，可以大大简化问题的复杂度。

---
处理用时：49.34秒