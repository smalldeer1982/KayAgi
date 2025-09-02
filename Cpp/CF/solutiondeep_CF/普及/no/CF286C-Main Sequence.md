# 题目信息

# Main Sequence

## 题目描述

As you know, Vova has recently become a new shaman in the city of Ultima Thule. So, he has received the shaman knowledge about the correct bracket sequences. The shamans of Ultima Thule have been using lots of different types of brackets since prehistoric times. A bracket type is a positive integer. The shamans define a correct bracket sequence as follows:

- An empty sequence is a correct bracket sequence.
- If $ {a_{1},a_{2},...,a_{l}} $ and $ {b_{1},b_{2},...,b_{k}} $ are correct bracket sequences, then sequence $ {a_{1},a_{2},...,a_{l},b_{1},b_{2},...,b_{k}} $ (their concatenation) also is a correct bracket sequence.
- If $ {a_{1},a_{2},...,a_{l}} $ — is a correct bracket sequence, then sequence ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF286C/b33e2eedc865caf6f8fa1a0ee5d1acc87a898f62.png) also is a correct bracket sequence, where $ v $ $ (v&gt;0) $ is an integer.

For example, sequences $ {1,1,-1,2,-2,-1} $ and $ {3,-3} $ are correct bracket sequences, and $ {2,-3} $ is not.

Moreover, after Vova became a shaman, he learned the most important correct bracket sequence $ {x_{1},x_{2},...,x_{n}} $ , consisting of $ n $ integers. As sequence $ x $ is the most important, Vova decided to encrypt it just in case.

Encrypting consists of two sequences. The first sequence $ {p_{1},p_{2},...,p_{n}} $ contains types of brackets, that is, $ p_{i}=|x_{i}| $ ( $ 1<=i<=n $ ). The second sequence $ {q_{1},q_{2},...,q_{t}} $ contains $ t $ integers — some positions (possibly, not all of them), which had negative numbers in sequence $ {x_{1},x_{2},...,x_{n}} $ .

Unfortunately, Vova forgot the main sequence. But he was lucky enough to keep the encryption: sequences $ {p_{1},p_{2},...,p_{n}} $ and $ {q_{1},q_{2},...,q_{t}} $ . Help Vova restore sequence $ x $ by the encryption. If there are multiple sequences that correspond to the encryption, restore any of them. If there are no such sequences, you should tell so.

## 样例 #1

### 输入

```
2
1 1
0
```

### 输出

```
YES
1 -1
```

## 样例 #2

### 输入

```
4
1 1 1 1
1 3
```

### 输出

```
YES
1 1 -1 -1
```

## 样例 #3

### 输入

```
3
1 1 1
0
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
4
1 2 2 1
2 3 4
```

### 输出

```
YES
1 2 -2 -1
```

# AI分析结果



# Main Sequence

## 题目描述

众所周知，Vova 最近成为了北极星城的新萨满。因此，他获得了关于正确括号序列的萨满知识。自史前时代起，北极星城的萨满就使用各种不同类型的括号。括号类型用正整数表示。萨满对正确括号序列的定义如下：

- 空序列是正确括号序列。
- 如果 $ {a_{1},a_{2},...,a_{l}} $ 和 $ {b_{1},b_{2},...,b_{k}} $ 是正确括号序列，那么它们的连接序列 $ {a_{1},a_{2},...,a_{l},b_{1},b_{2},...,b_{k}} $ 也是正确括号序列。
- 如果 $ {a_{1},a_{2},...,a_{l}} $ 是正确括号序列，那么序列 $ {v,a_{1},a_{2},...,a_{l},-v} $（其中 $v>0$ 是整数）也是正确括号序列。

例如，序列 $ {1,1,-1,2,-2,-1} $ 和 $ {3,-3} $ 是正确的，而 $ {2,-3} $ 不正确。

Vova 作为新萨满，知道了最重要的正确括号序列 $ {x_{1},x_{2},...,x_{n}} $（包含 $n$ 个整数）。为了加密这个序列，他生成两个序列：
1. 类型序列 $ {p_{1},p_{2},...,p_{n}} $，其中 $p_{i}=|x_{i}|$
2. 位置序列 $ {q_{1},q_{2},...,q_{t}} $，记录原序列中负数出现的位置

现在给定这两个加密序列，请还原原序列 $x$，若存在多个解输出任意一个，若无解输出 NO。

**算法分类**：贪心

---

## 题解分析与结论

### 关键思路
所有题解均采用**逆向贪心+栈匹配**的核心方法：
1. 从右向左遍历序列（确保优先处理必须的右括号）
2. 维护栈存储未匹配的右括号
3. 遇到正数时尝试与栈顶匹配，无法匹配则转为右括号
4. 最终判断栈是否为空验证合法性

### 精选题解

#### 【Cutest_Junior】⭐⭐⭐⭐
**亮点**：
- 清晰的栈操作逻辑
- 快速读入优化处理大数据
- 直接修改原数组节省空间

**核心代码**：
```cpp
for (int i = n ; i ; -- i) {
    if (arr[i] < 0) {
        sta.push(arr[i]);
    } else {
        if (!sta.empty() && arr[i] == -sta.top()) {
            sta.pop();
        } else {
            sta.push(-arr[i]);
            arr[i] = -arr[i];
        }
    }
}
```

#### 【_jhq】⭐⭐⭐⭐
**亮点**：
- 提供严格的正确性证明
- 使用数组模拟栈提升效率
- 输出结果缓存优化

**正确性证明片段**：
> 贪心策略优先将当前括号作为左括号匹配最近的右括号。若存在更优匹配方式，可以通过交换配对顺序构造等价解，证明贪心策略不会错过可行解。

---

## 最优实现要点
1. **逆向处理**：从右向左确保必须的右括号优先处理
2. **栈的维护**：存储未匹配的右括号类型
3. **符号转换策略**：
   - 必须为负的位置直接入栈
   - 可选的数优先匹配栈顶，否则转为右括号
4. **复杂度**：O(n) 时间与空间

**完整核心代码**：
```cpp
// 逆向处理部分
for (int i = n; i >= 1; --i) {
    if (a[i] < 0) {
        sta.push(a[i]);
    } else if (!sta.empty() && a[i] == -sta.top()) {
        sta.pop();
    } else {
        a[i] = -a[i];
        sta.push(a[i]);
    }
}
```

---

## 拓展与心得
**同类问题**：
1. 多类型括号混合匹配（如多种括号类型同时存在）
2. 带权括号匹配（每个括号有不同权重值）

**调试心得**：
- 必须为负的位置要在初始阶段直接标记，避免后续处理覆盖
- 栈空判断是匹配时的关键条件，漏判会导致段错误
- 逆向遍历时索引方向容易出错，建议从n到1递减遍历

---

## 推荐练习
1. [P1739 括号匹配](https://www.luogu.com.cn/problem/P1739) - 基础括号匹配
2. [P7914 括号树](https://www.luogu.com.cn/problem/P7914) - 树形结构中的括号匹配
3. [P1944 最长括号匹配](https://www.luogu.com.cn/problem/P1944) - 进阶的匹配长度计算

---
处理用时：55.60秒