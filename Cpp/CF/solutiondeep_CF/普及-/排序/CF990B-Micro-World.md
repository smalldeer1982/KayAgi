# 题目信息

# Micro-World

## 题目描述

You have a Petri dish with bacteria and you are preparing to dive into the harsh micro-world. But, unfortunately, you don't have any microscope nearby, so you can't watch them.

You know that you have $ n $ bacteria in the Petri dish and size of the $ i $ -th bacteria is $ a_i $ . Also you know intergalactic positive integer constant $ K $ .

The $ i $ -th bacteria can swallow the $ j $ -th bacteria if and only if $ a_i > a_j $ and $ a_i \le a_j + K $ . The $ j $ -th bacteria disappear, but the $ i $ -th bacteria doesn't change its size. The bacteria can perform multiple swallows. On each swallow operation any bacteria $ i $ can swallow any bacteria $ j $ if $ a_i > a_j $ and $ a_i \le a_j + K $ . The swallow operations go one after another.

For example, the sequence of bacteria sizes $ a=[101, 53, 42, 102, 101, 55, 54] $ and $ K=1 $ . The one of possible sequences of swallows is: $ [101, 53, 42, 102, \underline{101}, 55, 54] $ $ \to $ $ [101, \underline{53}, 42, 102, 55, 54] $ $ \to $ $ [\underline{101}, 42, 102, 55, 54] $ $ \to $ $ [42, 102, 55, \underline{54}] $ $ \to $ $ [42, 102, 55] $ . In total there are $ 3 $ bacteria remained in the Petri dish.

Since you don't have a microscope, you can only guess, what the minimal possible number of bacteria can remain in your Petri dish when you finally will find any microscope.

## 说明/提示

The first example is clarified in the problem statement.

In the second example an optimal possible sequence of swallows is: $ [20, 15, 10, 15, \underline{20}, 25] $ $ \to $ $ [20, 15, 10, \underline{15}, 25] $ $ \to $ $ [20, 15, \underline{10}, 25] $ $ \to $ $ [20, \underline{15}, 25] $ $ \to $ $ [\underline{20}, 25] $ $ \to $ $ [25] $ .

In the third example no bacteria can swallow any other bacteria.

## 样例 #1

### 输入

```
7 1
101 53 42 102 101 55 54
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6 5
20 15 10 15 20 25
```

### 输出

```
1
```

## 样例 #3

### 输入

```
7 1000000
1 1 1 1 1 1 1
```

### 输出

```
7
```

# AI分析结果

### 题目中文重写
# 微观世界

## 题目描述
你有一个培养着细菌的培养皿，正准备深入这个严苛的微观世界。但不幸的是，你附近没有显微镜，所以无法观察它们。

你知道培养皿中有 $n$ 个细菌，第 $i$ 个细菌的大小为 $a_i$ 。此外，你还知道一个星际正整数常量 $K$ 。

第 $i$ 个细菌能够吞噬第 $j$ 个细菌，当且仅当 $a_i > a_j$ 且 $a_i \le a_j + K$ 。第 $j$ 个细菌会消失，但第 $i$ 个细菌的大小不会改变。细菌可以进行多次吞噬操作。每次吞噬操作中，任何满足 $a_i > a_j$ 且 $a_i \le a_j + K$ 的细菌 $i$ 都可以吞噬细菌 $j$ 。吞噬操作依次进行。

例如，细菌大小序列 $a=[101, 53, 42, 102, 101, 55, 54]$ ，$K = 1$ 。一种可能的吞噬序列是：$ [101, 53, 42, 102, \underline{101}, 55, 54] $ $ \to $ $ [101, \underline{53}, 42, 102, 55, 54] $ $ \to $ $ [\underline{101}, 42, 102, 55, 54] $ $ \to $ $ [42, 102, 55, \underline{54}] $ $ \to $ $ [42, 102, 55] $ 。最终培养皿中还剩下 $3$ 个细菌。

由于你没有显微镜，你只能猜测，当你最终找到显微镜时，培养皿中最少可能剩下多少个细菌。

## 说明/提示
第一个样例在题目描述中已说明。

在第二个样例中，一个最优的吞噬序列是：$ [20, 15, 10, 15, \underline{20}, 25] $ $ \to $ $ [20, 15, 10, \underline{15}, 25] $ $ \to $ $ [20, 15, \underline{10}, 25] $ $ \to $ $ [20, \underline{15}, 25] $ $ \to $ $ [\underline{20}, 25] $ $ \to $ $ [25] $ 。

在第三个样例中，没有细菌能够吞噬其他细菌。

## 样例 #1
### 输入
```
7 1
101 53 42 102 101 55 54
```
### 输出
```
3
```

## 样例 #2
### 输入
```
6 5
20 15 10 15 20 25
```
### 输出
```
1
```

## 样例 #3
### 输入
```
7 1000000
1 1 1 1 1 1 1
```
### 输出
```
7
```

### 综合分析与结论
这些题解的核心思路都是先对细菌大小数组进行排序，然后通过不同方式模拟细菌吞噬过程，以求出培养皿中最少剩余细菌数量。

#### 思路对比
- **使用 `vector` 模拟**：如 Mysterious_Mini 和 CQ_Bab 的题解，将细菌大小依次加入 `vector`，若当前细菌能吞噬 `vector` 尾部细菌，则不断删除尾部元素，最后 `vector` 元素个数即为答案。
- **标记删除法**：Texas_the_Omertosa、Aya_tt、Qiancy1427、AlicX 和 alex_liu 的题解，通过标记数组记录被吞噬的细菌，从第二个细菌开始往前扫描，满足条件则标记并累加被删除细菌数量，最后用总数减去被删除数量得到剩余细菌数。
- **栈模拟法**：As_Snow 和 Symbolize 的题解，用栈模拟细菌吞噬过程，对于每个细菌，若能吞噬栈顶元素则弹出栈顶，最后栈内元素个数为答案。
- **特殊数组处理法**：帅到报警的题解，使用额外数组 `b` 记录每种大小细菌的数量，避免处理相同大小细菌的问题，排序后扫描并更新剩余细菌数量。

#### 算法要点
- **排序**：所有题解都先对细菌大小数组进行排序，确保后续模拟时能按从小到大顺序进行吞噬判断。
- **循环判断**：通过 `while` 循环不断判断当前细菌能否吞噬前面的细菌，直到不满足条件为止。

#### 解决难点
- **相同大小细菌处理**：帅到报警的题解通过额外数组 `b` 记录每种大小细菌数量，避免了相同大小细菌的重复处理。
- **边界条件处理**：部分题解在循环时需要注意边界条件，如避免数组越界，确保不会重复扫描已被吞噬的细菌。

### 题解评分与选择
|作者|评分|亮点|
| ---- | ---- | ---- |
|Mysterious_Mini|5星|思路清晰，详细介绍了 `vector` 的用法，代码注释完善，执行效率高。|
|As_Snow|4星|提供了数组模拟栈和 STL 栈两种实现方式，思路明确。|
|Symbolize|4星|思路步骤清晰，代码规范，使用宏定义简化代码。|

### 最优关键思路与技巧
- **排序**：排序是解决本题的关键，能使后续的吞噬判断更有序。
- **栈或 `vector` 模拟**：利用栈或 `vector` 的后进先出特性，方便模拟细菌吞噬过程，减少代码复杂度。

### 拓展思路
同类型题可能会改变吞噬条件或增加其他限制，如细菌有不同属性、吞噬后自身属性变化等。类似算法套路可用于处理有前后依赖关系的元素删除或合并问题，如区间合并、字符串压缩等。

### 推荐题目
1. [P1104 生日](https://www.luogu.com.cn/problem/P1104)：考察排序和结构体使用。
2. [P1093 奖学金](https://www.luogu.com.cn/problem/P1093)：涉及排序和多条件判断。
3. [P1271 选举学生会](https://www.luogu.com.cn/problem/P1271)：排序和计数的应用。

### 个人心得摘录与总结
题解中未包含个人心得相关内容。

### 重点代码
#### Mysterious_Mini 的题解核心代码
```cpp
for(int i = 0; i < n; i++)
{
    while(!v.empty() && a[i] > v.back() && a[i] <= v.back() + k)
        v.pop_back();
    v.push_back(a[i]);
}
```
核心思想：遍历细菌数组，若当前细菌能吞噬 `vector` 尾部细菌，则删除尾部元素，最后将当前细菌加入 `vector`。

#### As_Snow 的题解核心代码（数组模拟栈）
```cpp
for(int i=1;i<=n;i++){
    while(size&&st[size]<a[i]&&a[i]<=st[size]+k)size--;
    st[++size]=a[i];
}
```
核心思想：遍历细菌数组，若当前细菌能吞噬栈顶元素，则弹出栈顶，最后将当前细菌入栈。

#### Symbolize 的题解核心代码
```cpp
rep1(i,1,n)
{
    while(!sta.empty()&&a[i]>sta.top()&&a[i]<=sta.top()+k) sta.pop();
    sta.push(a[i]);
}
```
核心思想：遍历细菌数组，若当前细菌能吞噬栈顶元素，则弹出栈顶，最后将当前细菌入栈。 

---
处理用时：48.85秒