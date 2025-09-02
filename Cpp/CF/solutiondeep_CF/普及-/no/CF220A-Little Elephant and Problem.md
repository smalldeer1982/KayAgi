# 题目信息

# Little Elephant and Problem

## 题目描述

The Little Elephant has got a problem — somebody has been touching his sorted by non-decreasing array $ a $ of length $ n $ and possibly swapped some elements of the array.

The Little Elephant doesn't want to call the police until he understands if he could have accidentally changed the array himself. He thinks that he could have accidentally changed array $ a $ , only if array $ a $ can be sorted in no more than one operation of swapping elements (not necessarily adjacent). That is, the Little Elephant could have accidentally swapped some two elements.

Help the Little Elephant, determine if he could have accidentally changed the array $ a $ , sorted by non-decreasing, himself.

## 说明/提示

In the first sample the array has already been sorted, so to sort it, we need 0 swap operations, that is not more than 1. Thus, the answer is "YES".

In the second sample we can sort the array if we swap elements 1 and 3, so we need 1 swap operation to sort the array. Thus, the answer is "YES".

In the third sample we can't sort the array in more than one swap operation, so the answer is "NO".

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
3 2 1
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
4
4 3 2 1
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# 小象与问题

## 题目描述
小象遇到了一个问题——有人动了它按非递减顺序排序的长度为 $n$ 的数组 $a$，并且可能交换了数组中的一些元素。

小象在弄清楚是否可能是自己不小心改动了数组之前，不想报警。它认为，只有在数组 $a$ 可以通过不超过一次交换元素的操作（不一定是相邻元素）来排序的情况下，才可能是自己不小心改动的。也就是说，小象可能不小心交换了某两个元素。

请帮助小象判断它是否可能不小心改动了这个原本按非递减顺序排序的数组 $a$。

## 说明/提示
在第一个样例中，数组已经排好序，因此要对其进行排序，我们需要0次交换操作，即不超过1次。因此，答案是“YES”。

在第二个样例中，如果我们交换元素1和3，就可以对数组进行排序，所以我们需要1次交换操作来对数组进行排序。因此，答案是“YES”。

在第三个样例中，我们无法通过不超过一次的交换操作对数组进行排序，所以答案是“NO”。

## 样例 #1
### 输入
```
2
1 2
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
3
3 2 1
```
### 输出
```
YES
```

## 样例 #3
### 输入
```
4
4 3 2 1
```
### 输出
```
NO
```

### 算法分类
排序

### 综合分析与结论
所有题解的核心思路都是通过将原数组复制一份，对副本数组进行排序，然后对比原数组与排序后数组不同元素的个数。若不同元素个数为0（即原数组已排序）或2（可通过一次交换完成排序），则输出“YES”，否则输出“NO”。不同题解的主要差异在于代码风格、变量命名以及输入输出方式等方面。

### 所选的题解
- **作者：Ryan_Yu (5星)**
    - **关键亮点**：思路清晰，代码简洁明了，变量命名规范，使用了标准库函数进行输入输出和排序，代码可读性高。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000005;
int a[maxn],b[maxn],i,dif,n;
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
        {
            cin>>a[i];
            b[i]=a[i];
        }
    sort(a+1,a+1+n);
    for(i=1;i<=n;i++)
        if(a[i]!=b[i])
            dif++;
    if(dif<=2)
        cout<<"YES"<<endl;
    else
        cout<<"NO"<<endl;
    return 0;
}
```
    - **核心实现思想**：先将输入数组存入 `a` 数组，并复制到 `b` 数组，对 `a` 数组排序后，遍历对比 `a` 和 `b` 数组对应位置元素，统计不同元素个数 `dif`，根据 `dif` 是否小于等于2输出结果。
- **作者：LLGZ (4星)**
    - **关键亮点**：对题意分析清晰，代码结构较为清晰，使用 `scanf` 和 `printf` 进行输入输出，符合常见的C风格输入输出习惯。
    - **重点代码**：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int a[100100],b[100100];//a储存升序序列，b储存原序列
int main()
{
  int n;
  scanf("%d",&n);
  
  for(int i=1;i<=n;i++)
  {
  	scanf("%d",&a[i]);
  	b[i]=a[i];//同时赋值
  }
  sort(a+1,a+1+n);//sort默认升序排列
  
  int t=0;
  for(int i=1;i<=n;i++)
  if(a[i]!=b[i])//与原序列变化位置数量
  t++;
  
  if(t==2)//判断是否为2
  printf("YES");
  else printf("NO");
  
  return 0;
}
```
    - **核心实现思想**：与Ryan_Yu思路类似，先输入数据到 `a` 数组并复制到 `b` 数组，排序 `a` 数组后，遍历统计 `a` 和 `b` 数组不同元素个数 `t`，根据 `t` 是否为2输出结果。
- **作者：Eason_AC (4星)**
    - **关键亮点**：对题目要求和数据范围有清晰说明，代码风格简洁，变量命名有一定表意性，使用 `scanf` 和 `printf` 进行输入输出。
    - **重点代码**：
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

int n, a[100007], a1[100007], scnt;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		a1[i] = a[i];
	}
	sort(a1 + 1, a1 + n + 1);
	for(int i = 1; i <= n; ++i)
		if(a1[i]!= a[i])	scnt++;
	if(scnt <= 2)	printf("YES");
	else	printf("NO");
	return 0;
}
```
    - **核心实现思想**：将输入数组存入 `a` 数组并复制到 `a1` 数组，对 `a1` 数组排序后，遍历统计 `a` 和 `a1` 数组不同元素个数 `scnt`，根据 `scnt` 是否小于等于2输出结果。

### 最优关键思路或技巧
利用排序后对比数组元素差异的方法来判断是否可通过一次交换完成排序，这种方法简洁高效，充分利用了排序算法的特性以及一次交换只会改变两个元素位置的特点。

### 拓展
同类型题通常围绕数组的交换、排序规则的变化等展开，类似套路是通过对目标状态和当前状态的对比，利用排序等手段简化判断过程。

### 洛谷相似题目推荐
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：考察贪心策略与简单的数学计算，与本题类似在于都需要对数据进行处理并做出判断。
- [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055)：涉及字符串处理和简单的校验计算，和本题思路类似之处在于对输入数据进行特定规则的处理和判断。
- [P1161 开灯](https://www.luogu.com.cn/problem/P1161)：通过模拟开关灯的过程考察逻辑判断，与本题类似在于对给定条件下状态变化的分析判断。 

---
处理用时：60.39秒