# 题目信息

# Insert Zero and Invert Prefix

## 题目描述

You have a sequence $ a_1, a_2, \ldots, a_n $ of length $ n $ , each element of which is either $ 0 $ or $ 1 $ , and a sequence $ b $ , which is initially empty.

You are going to perform $ n $ operations. On each of them you will increase the length of $ b $ by $ 1 $ .

- On the $ i $ -th operation you choose an integer $ p $ between $ 0 $ and $ i-1 $ . You insert $ 0 $ in the sequence $ b $ on position $ p+1 $ (after the first $ p $ elements), and then you invert the first $ p $ elements of $ b $ .
- More formally: let's denote the sequence $ b $ before the $ i $ -th ( $ 1 \le i \le n $ ) operation as $ b_1, b_2, \ldots, b_{i-1} $ . On the $ i $ -th operation you choose an integer $ p $ between $ 0 $ and $ i-1 $ and replace $ b $ with $ \overline{b_1}, \overline{b_2}, \ldots, \overline{b_{p}}, 0, b_{p+1}, b_{p+2}, \ldots, b_{i-1} $ . Here, $ \overline{x} $ denotes the binary inversion. Hence, $ \overline{0} = 1 $ and $ \overline{1} = 0 $ .

You can find examples of operations in the Notes section.

Determine if there exists a sequence of operations that makes $ b $ equal to $ a $ . If such sequence of operations exists, find it.

## 说明/提示

In the first test case,

1. Before the first operation, $ b = [\,] $ . You choose $ p = 0 $ and replace $ b $ with $ [\, \underline{0} \,] $
2. On the second operation you choose $ p = 0 $ and replace $ b $ with $ [\, \underline{0}, 0 \,] $ .
3. On the third operation you choose $ p = 2 $ and replace $ b $ with $ [\, 1, 1, \underline{0} \,] $ .
4. On the fourth operation you choose $ p = 1 $ and replace $ b $ with $ [\, 0, \underline{0}, 1, 0 \,] $ .
5. On the fifth operation you choose $ p = 3 $ and replace $ b $ with $ [\, 1, 1, 0, \underline{0}, 0 \,] $ .

Hence, sequence $ b $ changes in the following way: $ [\,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0} \,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0}, 0 \,] $ $ \xrightarrow{p \, = \, 2} $ $ [\, 1, 1, \underline{0} \,] $ $ \xrightarrow{p \, = \, 1} $ $ [\, 0, \underline{0}, 1, 0 \,] $ $ \xrightarrow{p \, = \, 3} $ $ [\, 1, 1, 0, \underline{0}, 0 \,] $ . In the end the sequence $ b $ is equal to the sequence $ a $ , so this way to perform operations is one of the correct answers.

In the second test case, $ n = 1 $ and the only achiveable sequence $ b $ is $ [\, 0 \, ] $ .

In the third test case, there are six possible sequences of operations:

1. $ [\,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0} \,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0}, 0 \,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0}, 0, 0 \,] $ .
2. $ [\,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0} \,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0}, 0 \,] $ $ \xrightarrow{p \, = \, 1} $ $ [\, 1, \underline{0}, 0 \,] $ .
3. $ [\,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0} \,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0}, 0 \,] $ $ \xrightarrow{p \, = \, 2} $ $ [\, 1, 1, \underline{0} \,] $ .
4. $ [\,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0} \,] $ $ \xrightarrow{p \, = \, 1} $ $ [\, 1, \underline{0} \,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0}, 1, 0 \,] $ .
5. $ [\,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0} \,] $ $ \xrightarrow{p \, = \, 1} $ $ [\, 1, \underline{0} \,] $ $ \xrightarrow{p \, = \, 1} $ $ [\, 0, \underline{0}, 0 \,] $ .
6. $ [\,] $ $ \xrightarrow{p \, = \, 0} $ $ [\, \underline{0} \,] $ $ \xrightarrow{p \, = \, 1} $ $ [\, 1, \underline{0} \,] $ $ \xrightarrow{p \, = \, 2} $ $ [\, 0, 1, \underline{0} \,] $ .

None of them makes $ b $ equal to $ [\, 0, 1, 1 \,] $ , so the answer is "NO".

## 样例 #1

### 输入

```
4
5
1 1 0 0 0
1
1
3
0 1 1
6
1 0 0 1 1 0```

### 输出

```
YES
0 0 2 1 3
NO
NO
YES
0 1 0 2 4 2```

# AI分析结果

### 题目内容重写

#### 题目描述
你有一个长度为 $n$ 的序列 $a_1, a_2, \ldots, a_n$，每个元素为 $0$ 或 $1$，以及一个初始为空的序列 $b$。

你将进行 $n$ 次操作，每次操作会将 $b$ 的长度增加 $1$。

- 在第 $i$ 次操作中，你选择一个整数 $p$，范围在 $0$ 到 $i-1$ 之间。你将在序列 $b$ 的第 $p+1$ 个位置插入 $0$（即在前 $p$ 个元素之后），然后将 $b$ 的前 $p$ 个元素进行反转（即 $0$ 变 $1$，$1$ 变 $0$）。
- 更正式地，设第 $i$ 次操作前的序列为 $b_1, b_2, \ldots, b_{i-1}$。在第 $i$ 次操作中，你选择 $p$，并将 $b$ 替换为 $\overline{b_1}, \overline{b_2}, \ldots, \overline{b_{p}}, 0, b_{p+1}, b_{p+2}, \ldots, b_{i-1}$，其中 $\overline{x}$ 表示二进制反转。

你需要判断是否存在一系列操作使得 $b$ 最终等于 $a$。如果存在，请找出这样的操作序列。

#### 说明/提示
在第一个测试用例中：

1. 第一次操作前，$b = [\,]$。选择 $p = 0$，$b$ 变为 $[\, \underline{0} \,]$。
2. 第二次操作选择 $p = 0$，$b$ 变为 $[\, \underline{0}, 0 \,]$。
3. 第三次操作选择 $p = 2$，$b$ 变为 $[\, 1, 1, \underline{0} \,]$。
4. 第四次操作选择 $p = 1$，$b$ 变为 $[\, 0, \underline{0}, 1, 0 \,]$。
5. 第五次操作选择 $p = 3$，$b$ 变为 $[\, 1, 1, 0, \underline{0}, 0 \,]$。

最终 $b$ 等于 $a$，因此这个操作序列是正确的。

### 算法分类
构造

### 题解分析与结论
本题的核心是通过逆向思维，从目标序列 $a$ 出发，模拟删除操作并记录每次操作的位置。难点在于如何通过删除操作和反转操作来还原序列 $b$ 的构造过程。以下是对各题解的总结与对比：

1. **aeiouaoeiu 的题解**：通过从后向前扫描序列 $a$，判断当前元素是否为 $0$，并记录连续 $1$ 的个数。当遇到 $0$ 时，输出相应的操作位置。思路清晰，代码简洁。
2. **233L 的题解**：同样采用逆向思维，通过删除操作和反转操作来还原序列 $b$。使用栈来记录操作序列，并通过标记来避免实际反转操作。代码实现较为巧妙。
3. **Lonehll 的题解**：通过分析序列的连续 $1$ 和 $0$ 的分布，构造操作序列。思路清晰，但代码实现较为复杂。

### 所选高分题解

#### 1. aeiouaoeiu 的题解（评分：4星）
**关键亮点**：通过从后向前扫描序列 $a$，判断当前元素是否为 $0$，并记录连续 $1$ 的个数。当遇到 $0$ 时，输出相应的操作位置。思路清晰，代码简洁。

**核心代码**：
```cpp
for(int i=n;i>=1;i--){
    if(a[i]==0) cout<<"0 ";
    else{
        cnt++;
        if(a[i-1]==0){
            cout<<cnt<<" ";
            cnt=0;
        }else cout<<"0 ";
    }
}
```

#### 2. 233L 的题解（评分：4星）
**关键亮点**：通过删除操作和反转操作来还原序列 $b$。使用栈来记录操作序列，并通过标记来避免实际反转操作。代码实现较为巧妙。

**核心代码**：
```cpp
for(int i=n-1;~i;i--,rev^=1){
    if(!i||a[i-1]^rev) s.push(i);
    else a[i-1]^=1, s.push(i-1);
}
while(!s.empty()){
    printf("%d ",s.top());
    s.pop();
}
```

### 最优关键思路
通过逆向思维，从目标序列 $a$ 出发，模拟删除操作并记录每次操作的位置。使用栈来记录操作序列，并通过标记来避免实际反转操作。

### 拓展思路
类似的问题可以通过逆向思维和构造操作序列来解决。例如，某些序列生成问题或操作序列还原问题。

### 推荐题目
1. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
2. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

### 个人心得摘录
**rainygame 的题解**中提到：“考场上想出来了，但是写成了答辩，最后差 $5$ 分钟就调完。差亿点点就可以破个人记录了。” 这提醒我们在竞赛中不仅要思路正确，还要注意代码实现的效率和准确性。

---
处理用时：35.16秒