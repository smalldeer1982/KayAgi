# 题目信息

# Add to Neighbour and Remove

## 题目描述

Polycarp was given an array of $ a[1 \dots n] $ of $ n $ integers. He can perform the following operation with the array $ a $ no more than $ n $ times:

- Polycarp selects the index $ i $ and adds the value $ a_i $ to one of his choice of its neighbors. More formally, Polycarp adds the value of $ a_i $ to $ a_{i-1} $ or to $ a_{i+1} $ (if such a neighbor does not exist, then it is impossible to add to it).
- After adding it, Polycarp removes the $ i $ -th element from the $ a $ array. During this step the length of $ a $ is decreased by $ 1 $ .

The two items above together denote one single operation.

For example, if Polycarp has an array $ a = [3, 1, 6, 6, 2] $ , then it can perform the following sequence of operations with it:

- Polycarp selects $ i = 2 $ and adds the value $ a_i $ to $ (i-1) $ -th element: $ a = [4, 6, 6, 2] $ .
- Polycarp selects $ i = 1 $ and adds the value $ a_i $ to $ (i+1) $ -th element: $ a = [10, 6, 2] $ .
- Polycarp selects $ i = 3 $ and adds the value $ a_i $ to $ (i-1) $ -th element: $ a = [10, 8] $ .
- Polycarp selects $ i = 2 $ and adds the value $ a_i $ to $ (i-1) $ -th element: $ a = [18] $ .

Note that Polycarp could stop performing operations at any time.

Polycarp wondered how many minimum operations he would need to perform to make all the elements of $ a $ equal (i.e., he wants all $ a_i $ are equal to each other).

## 说明/提示

In the first test case of the example, the answer can be constructed like this (just one way among many other ways):

 $ [3, 1, 6, 6, 2] $ $ \xrightarrow[]{i=4,~add~to~left} $ $ [3, 1, 12, 2] $ $ \xrightarrow[]{i=2,~add~to~right} $ $ [3, 13, 2] $ $ \xrightarrow[]{i=1,~add~to~right} $ $ [16, 2] $ $ \xrightarrow[]{i=2,~add~to~left} $ $ [18] $ . All elements of the array $ [18] $ are the same.

In the second test case of the example, the answer can be constructed like this (just one way among other ways):

 $ [1, 2, 2, 1] $ $ \xrightarrow[]{i=1,~add~to~right} $ $ [3, 2, 1] $ $ \xrightarrow[]{i=3,~add~to~left} $ $ [3, 3] $ . All elements of the array $ [3, 3] $ are the same.

In the third test case of the example, Polycarp doesn't need to perform any operations since $ [2, 2, 2] $ contains equal (same) elements only.

In the fourth test case of the example, the answer can be constructed like this (just one way among other ways):

 $ [6, 3, 2, 1] $ $ \xrightarrow[]{i=3,~add~to~right} $ $ [6, 3, 3] $ $ \xrightarrow[]{i=3,~add~to~left} $ $ [6, 6] $ . All elements of the array $ [6, 6] $ are the same.

## 样例 #1

### 输入

```
4
5
3 1 6 6 2
4
1 2 2 1
3
2 2 2
4
6 3 2 1```

### 输出

```
4
2
0
2```

# AI分析结果

### 题目内容重写（中文）

**题目描述**

Polycarp 被给定一个包含 $n$ 个整数的数组 $a[1 \dots n]$。他可以对数组 $a$ 进行以下操作，最多进行 $n$ 次：

- Polycarp 选择一个索引 $i$，并将 $a_i$ 的值加到其相邻元素之一。更正式地说，Polycarp 将 $a_i$ 的值加到 $a_{i-1}$ 或 $a_{i+1}$（如果这样的邻居不存在，则无法进行加法操作）。
- 在加法操作之后，Polycarp 从数组 $a$ 中移除第 $i$ 个元素。在这一步中，数组 $a$ 的长度减少了 $1$。

以上两个步骤共同构成一次操作。

例如，如果 Polycarp 有一个数组 $a = [3, 1, 6, 6, 2]$，那么他可以执行以下操作序列：

- Polycarp 选择 $i = 2$ 并将 $a_i$ 的值加到 $(i-1)$ 元素：$a = [4, 6, 6, 2]$。
- Polycarp 选择 $i = 1$ 并将 $a_i$ 的值加到 $(i+1)$ 元素：$a = [10, 6, 2]$。
- Polycarp 选择 $i = 3$ 并将 $a_i$ 的值加到 $(i-1)$ 元素：$a = [10, 8]$。
- Polycarp 选择 $i = 2$ 并将 $a_i$ 的值加到 $(i-1)$ 元素：$a = [18]$。

注意，Polycarp 可以在任何时候停止操作。

Polycarp 想知道他需要进行多少次最少操作才能使数组 $a$ 中的所有元素相等（即他希望所有 $a_i$ 彼此相等）。

**说明/提示**

在第一个样例中，答案可以这样构造（只是众多方式中的一种）：

$ [3, 1, 6, 6, 2] $ $ \xrightarrow[]{i=4,~add~to~left} $ $ [3, 1, 12, 2] $ $ \xrightarrow[]{i=2,~add~to~right} $ $ [3, 13, 2] $ $ \xrightarrow[]{i=1,~add~to~right} $ $ [16, 2] $ $ \xrightarrow[]{i=2,~add~to~left} $ $ [18] $。数组 $ [18] $ 中的所有元素都相同。

在第二个样例中，答案可以这样构造（只是众多方式中的一种）：

$ [1, 2, 2, 1] $ $ \xrightarrow[]{i=1,~add~to~right} $ $ [3, 2, 1] $ $ \xrightarrow[]{i=3,~add~to~left} $ $ [3, 3] $。数组 $ [3, 3] $ 中的所有元素都相同。

在第三个样例中，Polycarp 不需要进行任何操作，因为 $ [2, 2, 2] $ 中的所有元素已经相同。

在第四个样例中，答案可以这样构造（只是众多方式中的一种）：

$ [6, 3, 2, 1] $ $ \xrightarrow[]{i=3,~add~to~right} $ $ [6, 3, 3] $ $ \xrightarrow[]{i=3,~add~to~left} $ $ [6, 6] $。数组 $ [6, 6] $ 中的所有元素都相同。

**样例 #1**

### 输入

```
4
5
3 1 6 6 2
4
1 2 2 1
3
2 2 2
4
6 3 2 1
```

### 输出

```
4
2
0
2
```

### 算法分类
数学

### 题解分析与结论

该题的核心思路是通过合并操作使得数组中的所有元素相等，且操作次数最少。所有题解都围绕这一核心展开，主要思路是通过枚举可能的合并结果，并验证其可行性。以下是各题解的要点总结：

1. **枚举合并后的元素值**：所有题解都指出，合并后的元素值必须是数组元素和的因数。因此，题解中普遍采用枚举因数的方法来寻找可能的合并结果。
2. **验证合并的可行性**：在枚举因数后，题解中通过遍历数组来验证是否可以将数组分割成若干个和等于该因数的子数组。
3. **时间复杂度优化**：部分题解通过优化因数的枚举和验证过程，使得时间复杂度保持在可接受的范围内。

### 高星题解推荐

#### 题解1：xiaomuyun (赞：22)
- **星级**：5星
- **关键亮点**：思路清晰，代码简洁，通过枚举第一段序列的长度来逐步验证合并的可行性，时间复杂度为 $O(n^2)$，适合该题的数据范围。
- **核心代码**：
```cpp
int sum=0,acnt=0,cnt,res=0x3f3f3f3f;
for(int i=1;i<=n;++i){
    sum+=a[i];
    if(i>1) ++acnt;
    cnt=acnt;
    int tmpsum=0;
    bool flag=true;
    for(int j=i+1;j<=n;++j){
        if(tmpsum) ++cnt;
        tmpsum+=a[j];
        if(tmpsum==sum) tmpsum=0;
        else if(tmpsum>sum){
            flag=false;
            break;
        }
    }
    if(flag&&!tmpsum) res=min(cnt,res);
}
```

#### 题解2：ChrisWangZi (赞：2)
- **星级**：4星
- **关键亮点**：通过枚举数组和的因数，并线性扫描验证是否可以将数组分割成若干个和等于该因数的子数组，时间复杂度为 $O(n \sqrt{sum})$。
- **核心代码**：
```cpp
int ck(int g){
    int cnt=0;
    int now=0;
    for(int j=1;j<=n;j++){
        now+=a[j];
        if(now==g){
            cnt++;
            now=0;
        }
        else if(now>g){
            return 0;
        }
    }
    return cnt;
}
```

#### 题解3：Zaku (赞：0)
- **星级**：4星
- **关键亮点**：通过枚举合并后的堆数，并验证是否可以将数组分割成若干个和等于 $sum/(N-x)$ 的子数组，思路清晰，代码简洁。
- **核心代码**：
```cpp
bool check(int cnt){
    for(int i=0,sum=0;i<n;i++){
        sum+=a[i];
        if(sum>cnt)return false;
        if(sum==cnt)sum=0;
    }
    return true;
}
```

### 最优关键思路或技巧
1. **因数的枚举与验证**：通过枚举数组和的因数，并验证是否可以将数组分割成若干个和等于该因数的子数组，是解决该题的核心思路。
2. **时间复杂度优化**：通过优化因数的枚举和验证过程，使得时间复杂度保持在可接受的范围内，如 $O(n^2)$ 或 $O(n \sqrt{sum})$。

### 可拓展之处
该题的思路可以拓展到其他需要将数组分割成若干个子数组，且子数组和满足特定条件的问题。例如，分割数组使得每个子数组的和相等，或者分割数组使得每个子数组的和为某个特定值。

### 推荐题目
1. [P8183](https://www.luogu.com.cn/problem/P8183) - 与本题类似，考察数组分割与合并操作。
2. [P1045](https://www.luogu.com.cn/problem/P1045) - 考察数组分割与合并操作，难度较高。
3. [P1046](https://www.luogu.com.cn/problem/P1046) - 考察数组分割与合并操作，难度适中。

---
处理用时：54.21秒