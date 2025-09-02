# 题目信息

# Directional Increase

## 题目描述

We have an array of length $ n $ . Initially, each element is equal to $ 0 $ and there is a pointer located on the first element.

We can do the following two kinds of operations any number of times (possibly zero) in any order:

1. If the pointer is not on the last element, increase the element the pointer is currently on by $ 1 $ . Then move it to the next element.
2. If the pointer is not on the first element, decrease the element the pointer is currently on by $ 1 $ . Then move it to the previous element.

But there is one additional rule. After we are done, the pointer has to be on the first element.

You are given an array $ a $ . Determine whether it's possible to obtain $ a $ after some operations or not.

## 说明/提示

In the first test case we can obtain the array after some operations, but the pointer won't be on the first element.

One way of obtaining the array in the second test case is shown below.

 $ \langle \underline{0}, 0, 0, 0\rangle \to \langle 1, \underline{0}, 0, 0 \rangle \to \langle \underline{1}, -1, 0, 0\rangle \to \langle 2, \underline{-1}, 0, 0\rangle \to \langle 2, 0, \underline{0}, 0\rangle \to \langle 2, \underline{0}, -1, 0\rangle \to \langle \underline{2}, -1, -1, 0\rangle $

## 样例 #1

### 输入

```
7
2
1 0
4
2 -1 -1 0
4
1 -4 3 0
4
1 -1 1 -1
5
1 2 3 4 -10
7
2 -1 1 -2 0 0 0
1
0```

### 输出

```
No
Yes
No
No
Yes
Yes
Yes```

# AI分析结果

### 中文重写题目内容

# 方向性增加

## 题目描述

我们有一个长度为 $n$ 的数组。初始时，每个元素都等于 $0$，并且指针位于第一个元素上。

我们可以执行以下两种操作任意次数（可能为零次），顺序不限：

1. 如果指针不在最后一个元素上，将指针当前指向的元素增加 $1$，然后将指针移动到下一个元素。
2. 如果指针不在第一个元素上，将指针当前指向的元素减少 $1$，然后将指针移动到前一个元素。

但有一个额外的规则：操作结束后，指针必须回到第一个元素。

给定一个数组 $a$，判断是否可以通过上述操作得到 $a$。

## 说明/提示

在第一个测试用例中，我们可以通过一些操作得到数组，但指针不会回到第一个元素。

第二个测试用例的一种操作方式如下：

$ \langle \underline{0}, 0, 0, 0\rangle \to \langle 1, \underline{0}, 0, 0 \rangle \to \langle \underline{1}, -1, 0, 0\rangle \to \langle 2, \underline{-1}, 0, 0\rangle \to \langle 2, 0, \underline{0}, 0\rangle \to \langle 2, \underline{0}, -1, 0\rangle \to \langle \underline{2}, -1, -1, 0\rangle $

## 样例 #1

### 输入

```
7
2
1 0
4
2 -1 -1 0
4
1 -4 3 0
4
1 -1 1 -1
5
1 2 3 4 -10
7
2 -1 1 -2 0 0 0
1
0```

### 输出

```
No
Yes
No
No
Yes
Yes
Yes```

### 算法分类
前缀和

### 题解分析与结论

该题的核心在于通过前缀和的性质来判断给定的数组是否可以通过特定的操作得到。题解中主要使用了前缀和的思想，通过计算数组的前缀和来判断是否满足条件。

### 所选高星题解

#### 题解1：Altwilio (4星)
**关键亮点**：
- 通过前缀和的性质来判断数组是否合法。
- 详细证明了前缀和的条件，并给出了代码实现。

**核心代码**：
```cpp
for(int i = 1; i <= n; i ++) a[i] += a[i - 1];
if(a[n] != 0){ printf("No\n"); continue; }
for(int i = 1; i < n; i ++){
    if(a[i] <= 0){ flag = 0; break; }
}
if(flag == 0) printf("No\n");
else printf("Yes\n");
```

#### 题解2：良心WA题人 (4星)
**关键亮点**：
- 通过区间选择的方式来判断数组是否合法。
- 详细分析了左端点和右端点的条件，并给出了代码实现。

**核心代码**：
```cpp
a[1]--,a[last]++;
long long res=0;
for(int i=1;i<=n;i++){
    res+=a[i];
    if(res<0) break;
}
if(res>0||res<0){ puts("No"); continue; }
for(int i=n;i;i--){
    res+=a[i];
    if(res>0) break;
}
if(res>0) puts("No");
else puts("Yes");
```

#### 题解3：I_am_Accepted (4星)
**关键亮点**：
- 通过后缀和的性质来判断数组是否合法。
- 详细分析了后缀和的条件，并给出了代码实现。

**核心代码**：
```cpp
Rof(i,n-1,1) a[i]+=a[i+1];
if(a[1]!=0){ cout<<"No"<<endl; return ; }
For(i,2,n){
    if(a[i]>=0){ cout<<"No"<<endl; return ; }
}
cout<<"Yes"<<endl;
```

### 最优关键思路或技巧
- 使用前缀和或后缀和的性质来判断数组是否合法。
- 通过分析操作的性质，得出前缀和或后缀和必须满足的条件。

### 可拓展之处
- 类似的问题可以通过前缀和或后缀和的性质来解决，例如判断数组是否可以通过某种操作得到目标数组。

### 推荐题目
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

### 个人心得摘录
- **Altwilio**：通过前缀和的性质来判断数组是否合法，并详细证明了前缀和的条件。
- **良心WA题人**：通过区间选择的方式来判断数组是否合法，并详细分析了左端点和右端点的条件。
- **I_am_Accepted**：通过后缀和的性质来判断数组是否合法，并详细分析了后缀和的条件。

---
处理用时：32.11秒