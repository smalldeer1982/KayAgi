# 题目信息

# Make Equal With Mod

## 题目描述

You are given an array of $ n $ non-negative integers $ a_1, a_2, \ldots, a_n $ . You can make the following operation: choose an integer $ x \geq 2 $ and replace each number of the array by the remainder when dividing that number by $ x $ , that is, for all $ 1 \leq i \leq n $ set $ a_i $ to $ a_i \bmod x $ .

Determine if it is possible to make all the elements of the array equal by applying the operation zero or more times.

## 说明/提示

In the first test case, one can apply the operation with $ x = 3 $ to obtain the array $ [2, 2, 0, 2] $ , and then apply the operation with $ x = 2 $ to obtain $ [0, 0, 0, 0] $ .

In the second test case, all numbers are already equal.

In the fourth test case, applying the operation with $ x = 4 $ results in the array $ [1, 1, 1, 1] $ .

## 样例 #1

### 输入

```
4
4
2 5 6 8
3
1 1 1
5
4 1 7 0 8
4
5 9 17 5```

### 输出

```
YES
YES
NO
YES```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个包含 $n$ 个非负整数的数组 $a_1, a_2, \ldots, a_n$。你可以进行如下操作：选择一个整数 $x \geq 2$，并将数组中的每个元素替换为该元素除以 $x$ 的余数，即对于所有 $1 \leq i \leq n$，将 $a_i$ 替换为 $a_i \bmod x$。

判断是否可以通过零次或多次操作使数组中的所有元素相等。

#### 说明/提示

在第一个测试用例中，可以选择 $x = 3$ 进行操作，得到数组 $[2, 2, 0, 2]$，然后选择 $x = 2$ 进行操作，得到 $[0, 0, 0, 0]$。

在第二个测试用例中，所有元素已经相等。

在第四个测试用例中，选择 $x = 4$ 进行操作，得到数组 $[1, 1, 1, 1]$。

#### 样例 #1

##### 输入

```
4
4
2 5 6 8
3
1 1 1
5
4 1 7 0 8
4
5 9 17 5
```

##### 输出

```
YES
YES
NO
YES
```

### 算法分类

数学、构造

### 题解分析与结论

该题目要求通过模运算使数组中的所有元素相等，核心思路是分类讨论。主要分为以下几种情况：

1. **数组中同时包含 0 和 1**：由于模数必须大于等于 2，0 和 1 无法通过模运算改变，因此这种情况无法使所有元素相等，输出 `NO`。
2. **数组中不包含 1**：可以通过多次选择最大数作为模数，将所有元素逐步变为 0，输出 `YES`。
3. **数组中包含 1 但不包含 0**：需要将所有元素变为 1，但如果数组中存在两个连续的数（如 $x$ 和 $x+1$），则无法通过模运算使它们相等，输出 `NO`；否则输出 `YES`。

### 高星题解推荐

#### 题解1：RedLycoris (5星)

**关键亮点**：
- 清晰分类讨论，逻辑严谨。
- 代码简洁，直接处理三种情况，避免了复杂的判断。

**核心代码**：
```cpp
inline void solve(){
    cin>>n;
    int hv0=0,hv1=0;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        if(a[i]==0)hv0=1;
        if(a[i]==1)hv1=1;
    }
    sort(a+1,a+n+1);
    if(hv0 and hv1){
        cout<<"NO\n";
        return;
    }
    if(!hv1){
        cout<<"YES\n";
        return;
    }
    for(int i=1;i<n;++i)if(a[i+1]==a[i]+1){
        cout<<"NO\n";
        return;
    }
    cout<<"YES\n";
}
```

#### 题解2：HPXXZYY (4星)

**关键亮点**：
- 详细解释了每种情况的处理方式，尤其是关于连续数的判断。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
if (Zero&&One) flag=false;
else if (!One) flag=true;
else{
    for(int i=1;i<n;i++)
        if (a[i]+1==a[i+1]){
            flag=false;
            break;
        }
}
```

#### 题解3：BorisDimitri (4星)

**关键亮点**：
- 简洁明了地总结了三种情况，并给出了清晰的判断条件。
- 代码实现简洁，直接处理了所有可能的情况。

**核心代码**：
```cpp
if(one && suc) cout<<no;
else cout<<yes;
```

### 关键思路与技巧

1. **分类讨论**：根据数组中是否包含 0 或 1，以及是否存在连续数，进行分类处理。
2. **模运算性质**：利用模运算的性质，逐步将数组元素变为 0 或 1。
3. **排序与遍历**：通过排序和遍历，快速判断是否存在连续数。

### 拓展与举一反三

类似的问题可以通过分类讨论和模运算的性质来解决，尤其是在涉及数组元素变化的题目中。例如，洛谷上的以下题目也涉及类似的思想：

1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)

### 个人心得摘录

- **RedLycoris**：通过分类讨论，避免了复杂的判断，直接处理了所有可能的情况。
- **caibet**：CF 的操作题做法往往和样例解释有很大差别，不能完全依赖样例解释，需要独立思考。

### 总结

该题目的核心在于分类讨论和模运算的性质，通过合理的分类和判断，可以快速解决问题。推荐的题解均具有清晰的思路和简洁的代码实现，适合学习和参考。

---
处理用时：38.03秒