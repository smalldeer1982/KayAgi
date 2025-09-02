# 题目信息

# Bits

## 题目描述

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 说明/提示

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 样例 #1

### 输入

```
3
1 2
2 4
1 10
```

### 输出

```
1
3
7
```

# AI分析结果

### 题目翻译
#### 题目描述
用 $popcount(x)$ 表示非负整数 $x$ 的二进制表示中置位（即“1”位）的数量。

给定多组查询，每组查询包含一对整数 $l$ 和 $r$。对于每组查询，找出满足 $l \leq x \leq r$ 且 $popcount(x)$ 尽可能大的 $x$。如果有多个这样的数，则找出其中最小的那个。

#### 说明/提示
用 $popcount(x)$ 表示非负整数 $x$ 的二进制表示中置位（即“1”位）的数量。

给定多组查询，每组查询包含一对整数 $l$ 和 $r$。对于每组查询，找出满足 $l \leq x \leq r$ 且 $popcount(x)$ 尽可能大的 $x$。如果有多个这样的数，则找出其中最小的那个。

#### 样例 #1
##### 输入
```
3
1 2
2 4
1 10
```
##### 输出
```
1
3
7
```

### 综合分析与结论
这些题解大多采用贪心算法解决问题，核心思路是从 $l$ 的二进制最低位开始，尝试将为 $0$ 的位变为 $1$，直到操作后的数大于 $r$ 为止。不同题解在代码实现细节和思路阐述上略有差异，但本质相同。

### 所选题解
- **作者：XiXi（5星）**
    - **关键亮点**：思路清晰，代码简洁，详细说明了贪心策略和代码实现的原理。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,l,r,i;
int main()
{
    scanf("%lld",&T);  //读入T
    while (T--)
    {
    	scanf("%lld%lld",&l,&r);  //读入l和r
    	for (i=1;(l|i)<=r;i<<=1) l|=i;  //l或上2^x
    	printf("%lld\n",l);
	}
}
```
核心实现思想：通过按位或运算 `|` 尝试将 $l$ 的二进制最低位为 $0$ 的位变为 $1$，并使用左移运算符 `<<` 依次处理更高位，直到结果大于 $r$。

- **作者：EuphoricStar（4星）**
    - **关键亮点**：简洁地阐述了贪心策略，给出核心代码并解释了位运算符的含义。
    - **核心代码**：
```cpp
ull t = 1;
while ((l | t) <= r) l |= t, t <<= 1;
```
核心实现思想：从最低位开始，使用按位或运算将 $l$ 的当前位变为 $1$，若结果不超过 $r$ 则更新 $l$，并将 $t$ 左移一位处理下一位。

- **作者：_cmh（4星）**
    - **关键亮点**：思路清晰，代码规范，提醒了数据类型和输入输出的注意事项。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdlib>
using namespace std;
unsigned long long T,l,r;
int main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&l,&r);
		for(unsigned long long i=1;(l|i)<=r;i<<=1) l|=i;
		printf("%lld\n",l);
	}
    return 0;
}
```
核心实现思想：与其他题解类似，使用按位或和左移运算，从最低位开始将 $l$ 的 $0$ 位变为 $1$，直到结果大于 $r$。

### 最优关键思路或技巧
- **贪心策略**：从最低位开始将 $l$ 的二进制位变为 $1$，保证 $1$ 的数量最多且结果最小。
- **位运算**：使用按位或 `|` 运算将指定位置变为 $1$，左移运算 `<<` 用于遍历二进制位。

### 可拓展之处
同类型题可能会改变区间条件、增加约束或改变目标函数，但贪心和位运算的思路仍可作为解决问题的基础。例如，可能会要求找出区间内二进制表示中 $1$ 的个数为特定值的最小数，或者找出满足其他二进制位条件的数。

### 推荐题目
1. [P2431 正妹吃月饼](https://www.luogu.com.cn/problem/P2431)
2. [P1100 高低位交换](https://www.luogu.com.cn/problem/P1100)
3. [P1896 [SCOI2005]互不侵犯](https://www.luogu.com.cn/problem/P1896)

### 个人心得摘录与总结
- **XiXi**：第一次尝试根据 $l$ 和 $r$ 的一些玄学关系解题，后来发现贪心更合适，提醒我们遇到极值问题可优先考虑贪心策略。
- **Argon_Cube**：最初想枚举二进制全 $1$ 的数，但遇到反例后意识到不可行，最终采用贪心算法，说明解题时要多尝试不同思路，遇到问题及时调整。 

---
处理用时：33.99秒