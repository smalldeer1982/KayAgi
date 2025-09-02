# 题目信息

# String Deletion

## 题目描述

You have a string $ s $ consisting of $ n $ characters. Each character is either 0 or 1.

You can perform operations on the string. Each operation consists of two steps:

1. select an integer $ i $ from $ 1 $ to the length of the string $ s $ , then delete the character $ s_i $ (the string length gets reduced by $ 1 $ , the indices of characters to the right of the deleted one also get reduced by $ 1 $ );
2. if the string $ s $ is not empty, delete the maximum length prefix consisting of the same characters (the indices of the remaining characters and the string length get reduced by the length of the deleted prefix).

Note that both steps are mandatory in each operation, and their order cannot be changed.

For example, if you have a string $ s = $ 111010, the first operation can be one of the following:

1. select $ i = 1 $ : we'll get 111010 $ \rightarrow $ 11010 $ \rightarrow $ 010;
2. select $ i = 2 $ : we'll get 111010 $ \rightarrow $ 11010 $ \rightarrow $ 010;
3. select $ i = 3 $ : we'll get 111010 $ \rightarrow $ 11010 $ \rightarrow $ 010;
4. select $ i = 4 $ : we'll get 111010 $ \rightarrow $ 11110 $ \rightarrow $ 0;
5. select $ i = 5 $ : we'll get 111010 $ \rightarrow $ 11100 $ \rightarrow $ 00;
6. select $ i = 6 $ : we'll get 111010 $ \rightarrow $ 11101 $ \rightarrow $ 01.

You finish performing operations when the string $ s $ becomes empty. What is the maximum number of operations you can perform?

## 说明/提示

In the first test case, you can, for example, select $ i = 2 $ and get string 010 after the first operation. After that, you can select $ i = 3 $ and get string 1. Finally, you can only select $ i = 1 $ and get empty string.

## 样例 #1

### 输入

```
5
6
111010
1
0
1
1
2
11
6
101010```

### 输出

```
3
1
1
1
3```

# AI分析结果

### 题目翻译
# 字符串删除

## 题目描述

你有一个由 $n$ 个字符组成的字符串 $s$，每个字符是 0 或 1。

你可以对字符串进行操作。每次操作包含两个步骤：

1. 从 $1$ 到字符串 $s$ 的长度中选择一个整数 $i$，然后删除字符 $s_i$（字符串长度减少 $1$，被删除字符右侧的字符索引也减少 $1$）；
2. 如果字符串 $s$ 不为空，删除由相同字符组成的最大长度前缀（剩余字符的索引和字符串长度减少被删除前缀的长度）。

注意，每个操作中的两个步骤都是必须的，且它们的顺序不能改变。

例如，如果你有一个字符串 $s = $ 111010，第一次操作可以是以下之一：

1. 选择 $i = 1$：得到 111010 $ \rightarrow $ 11010 $ \rightarrow $ 010；
2. 选择 $i = 2$：得到 111010 $ \rightarrow $ 11010 $ \rightarrow $ 010；
3. 选择 $i = 3$：得到 111010 $ \rightarrow $ 11010 $ \rightarrow $ 010；
4. 选择 $i = 4$：得到 111010 $ \rightarrow $ 11110 $ \rightarrow $ 0；
5. 选择 $i = 5$：得到 111010 $ \rightarrow $ 11100 $ \rightarrow $ 00；
6. 选择 $i = 6$：得到 111010 $ \rightarrow $ 11101 $ \rightarrow $ 01。

当字符串 $s$ 变为空时，操作结束。你能执行的最大操作次数是多少？

## 说明/提示

在第一个测试用例中，你可以选择 $i = 2$，并在第一次操作后得到字符串 010。然后，你可以选择 $i = 3$，得到字符串 1。最后，你只能选择 $i = 1$，得到空字符串。

## 样例 #1

### 输入

```
5
6
111010
1
0
1
1
2
11
6
101010```

### 输出

```
3
1
1
1
3```

### 算法分类
贪心

### 题解分析与结论
本题的核心在于如何最大化操作次数。通过分析，我们可以发现，每次操作后删除前缀的操作会影响到后续的操作次数。因此，我们需要通过贪心策略来尽可能减少每次操作对后续操作的影响。

### 精选题解
#### 1. 作者：vectorwyx (赞：6)
**星级：5星**
**关键亮点：**
- 通过将字符串划分为连续字符段，简化了问题。
- 使用贪心策略，优先删除长度大于1的连续段中的字符，以减少对后续操作的影响。
- 代码简洁，逻辑清晰，时间复杂度为 $O(n)$。

**核心代码：**
```cpp
int pos=1;
fo(i,1,top){
    while(pos<=top&&a[pos]==1) pos++;
    a[pos]--;
    if(pos>top){
        ans=i-1+(top-i+2)/2;
        printf("%d\n",ans);
        return;
    }
    if(pos<=i) pos=i+1;
}
```
**核心思想：**
维护一个指针 `pos`，指向第一个长度大于1的连续段。每次操作时，从该段中删除一个字符，并更新指针位置。如果指针越界，则计算剩余段的操作次数。

#### 2. 作者：explorerxx (赞：3)
**星级：4星**
**关键亮点：**
- 详细分析了不同情况下的删除策略，特别是如何处理单字符和多字符连续段。
- 通过模拟操作，验证了贪心策略的正确性。
- 代码实现较为复杂，但思路清晰。

**核心代码：**
```cpp
int flag=0;
for(int i=1;i<=blo;i++){
    if(flag){
        ans++;i++;
        continue;
    }
    if(bl[i]>=2){
        ans++;
    }
    else{
        while(q<i||(q<=blo&&bl[q]<2))q++;
        if(q>blo){
            flag=1;
            ans++;
            i++;
        }
        else{
            bl[q]--;
            ans++;
        }
    }
}
```
**核心思想：**
使用指针 `q` 来寻找长度大于1的连续段，优先删除这些段中的字符。如果找不到，则删除单字符段，并标记后续操作只能删除两个字符。

#### 3. 作者：vеctorwyx (赞：2)
**星级：4星**
**关键亮点：**
- 通过手玩样例，得出了贪心策略。
- 将问题转化为删除连续段的问题，简化了操作步骤。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
int x=1;
for(int i=1;i<=cnt;i++){
    while(x<=cnt&&sta[x]==1) x++;
    sta[x]--;
    if(x>cnt){
        cout<<(i-1+(cnt-i+2)/2)<<endl;
        ans=1;
        break;
    }
    if(x<=i) x=i+1;
}
```
**核心思想：**
维护一个指针 `x`，指向第一个长度大于1的连续段。每次操作时，从该段中删除一个字符，并更新指针位置。如果指针越界，则计算剩余段的操作次数。

### 最优关键思路
通过将字符串划分为连续字符段，并优先删除长度大于1的连续段中的字符，可以减少每次操作对后续操作的影响，从而最大化操作次数。

### 可拓展之处
类似的问题可以通过将字符串划分为连续段，并使用贪心策略来优化操作次数。例如，在处理字符串删除或合并问题时，可以考虑类似的思路。

### 推荐题目
1. [P1430 序列划分](https://www.luogu.com.cn/problem/P1430)
2. [P1431 字符串删除](https://www.luogu.com.cn/problem/P1431)
3. [P1432 字符串操作](https://www.luogu.com.cn/problem/P1432)

---
处理用时：43.15秒