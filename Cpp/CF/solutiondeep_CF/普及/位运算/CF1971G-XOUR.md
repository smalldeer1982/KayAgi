# 题目信息

# XOUR

## 题目描述

You are given an array $ a $ consisting of $ n $ nonnegative integers.

You can swap the elements at positions $ i $ and $ j $ if $ a_i~\mathsf{XOR}~a_j < 4 $ , where $ \mathsf{XOR} $ is the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Find the lexicographically smallest array that can be made with any number of swaps.

An array $ x $ is lexicographically smaller than an array $ y $ if in the first position where $ x $ and $ y $ differ, $ x_i < y_i $ .

## 说明/提示

For the first test case, you can swap any two elements, so we can produce the sorted array.

For the second test case, you can swap $ 2 $ and $ 1 $ (their $ \mathsf{XOR} $ is $ 3 $ ), $ 7 $ and $ 5 $ (their $ \mathsf{XOR} $ is $ 2 $ ), and $ 7 $ and $ 6 $ (their $ \mathsf{XOR} $ is $ 1 $ ) to get the lexicographically smallest array.

## 样例 #1

### 输入

```
4
4
1 0 3 2
5
2 7 1 5 6
8
1 2 1 2 1 2 1 2
4
16 4 1 64```

### 输出

```
0 1 2 3 
1 5 2 6 7 
1 1 1 1 2 2 2 2 
16 4 1 64```

# AI分析结果

### 题目中文重写
## XOUR

### 题目描述
给定一个由 $n$ 个非负整数组成的数组 $a$。

如果 $a_i \oplus a_j < 4$（其中 $\oplus$ 是按位异或运算），则可以交换位置 $i$ 和 $j$ 处的元素。

找出通过任意次数的交换所能得到的字典序最小的数组。

如果在数组 $x$ 和 $y$ 不同的第一个位置上，$x_i < y_i$，则称数组 $x$ 在字典序上小于数组 $y$。

### 说明/提示
对于第一个测试用例，可以交换任意两个元素，因此可以得到排序后的数组。

对于第二个测试用例，可以交换 $2$ 和 $1$（它们的异或值为 $3$）、$7$ 和 $5$（它们的异或值为 $2$）以及 $7$ 和 $6$（它们的异或值为 $1$），以得到字典序最小的数组。

### 样例 #1
#### 输入
```
4
4
1 0 3 2
5
2 7 1 5 6
8
1 2 1 2 1 2 1 2
4
16 4 1 64
```
#### 输出
```
0 1 2 3 
1 5 2 6 7 
1 1 1 1 2 2 2 2 
16 4 1 64
```

### 综合分析与结论
这些题解的核心思路都是基于 $a_i \oplus a_j < 4$ 等价于 $\lfloor \frac{a_i}{4} \rfloor = \lfloor \frac{a_j}{4} \rfloor$ 这一性质，将数组元素进行分组，使得组内元素可以任意交换，然后对组内元素进行排序以得到字典序最小的数组。

### 思路、算法要点及难点对比
|作者|思路|算法要点|难点|
| ---- | ---- | ---- | ---- |
|sto__Liyhzh__orz|将满足条件的 $a_i$ 和 $a_j$ 存起来，输出时取堆里最小值|利用堆存储可交换元素|理解异或条件与分组的关系|
|Gapple|用 $a_i$ 的第二位及更高位的部分进行分组，对每组在原数组中排序|使用 `unordered_map` 分组，自定义哈希函数|哈希函数的实现和使用|
|Harry1000|对能交换的数分组，遍历原序列将前面的数换成能交换的最小数字|快速排序、二分查找|分组和二分查找的实现|
|JXR_Kalcium|将可交换的数放进同一堆，用优先队列存储，取最小数输出|使用 `map` 存储优先队列|优先队列和 `map` 的使用|
|FiraCode|去掉后两位排序，贪心选择放入原序列|简单排序和贪心|理解去掉后两位排序的原理|
|L_xcy|将每个 $a_i$ 除以 4 相同的数放在同一组，输出组内最小数|使用优先队列维护组内元素|优先队列的使用|
|luogu_gza|将除四下取整相同的 $a_i$ 塞进 `multiset` 排序|使用 `map` 和 `multiset`|`multiset` 的使用|
|Kindershiuo|按 $a_i\div4$ 分组，组内排序后拼接结果|使用 `map` 和优先队列|分组和优先队列的使用|
|kimi0705|将元素放入桶（`map`），排序后填充到答案数组|使用 `map` 存储元素和下标|`map` 的使用和排序|
|shenwentao|按条件分组，用优先队列维护组内元素，从小到大输出|使用 `map` 和优先队列|优先队列的使用|
|Lu_xZ|在能交换的点之间连边，用并查集维护连通块，对连通块内元素排序|并查集的使用|并查集的实现和使用|
|tder|按二进制除后两位相同分类，组内用优先队列排序|使用 `map` 和优先队列|优先队列和 `map` 的使用|
|jhdrgfj|将 $a_i$ 分到 $a_i \mid 3$ 这一组，用 `map` 套 `multiset` 维护组内元素排序|使用 `map` 和 `multiset`|`multiset` 的使用|

### 题解评分
|作者|评分|
| ---- | ---- |
|sto__Liyhzh__orz|4星|
|Gapple|4星|
|Harry1000|3星|
|JXR_Kalcium|4星|
|FiraCode|2星|
|L_xcy|4星|
|luogu_gza|3星|
|Kindershiuo|3星|
|kimi0705|3星|
|shenwentao|3星|
|Lu_xZ|2星|
|tder|4星|
|jhdrgfj|3星|

### 所选题解
- **sto__Liyhzh__orz（4星）**
    - **关键亮点**：思路简洁，直接点明核心性质，便于理解。
- **Gapple（4星）**
    - **关键亮点**：使用 `unordered_map` 分组，代码实现清晰，自定义哈希函数保证效率。
- **JXR_Kalcium（4星）**
    - **关键亮点**：使用优先队列存储可交换元素，代码简洁易懂。

### 重点代码
#### sto__Liyhzh__orz
核心思路：根据异或条件分组，用堆存储可交换元素。
#### Gapple
```cpp
unordered_map<int, vector<int>, Hash> idx;
for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    idx[x >> 2].emplace_back(i);
    arr.emplace_back(x);
}
for (auto& [_, i] : idx)
    sort(i.begin(), i.end(), [&arr](int u, int v) { return arr[u] < arr[v]; });
for (int i = 0; i < n; ++i)
    cout << arr[idx[arr[i] >> 2][pos[arr[i] >> 2]++]] << ' ';
```
核心实现思想：使用 `unordered_map` 按元素右移 2 位的值进行分组，记录每个元素的下标，对每组下标按元素值排序，最后按原数组顺序输出排序后的元素。
#### JXR_Kalcium
```cpp
map<int,priority_queue<int> > mp;
for(int i=1; i<=n; ++i)
    scanf("%d",&a[i]), mp[a[i]/4].push(-a[i]);
for(int i=1; i<=n; ++i)
    printf("%d ",-mp[a[i]/4].top()), mp[a[i]/4].pop();
```
核心实现思想：使用 `map` 存储优先队列，按元素除以 4 的值分组，将元素取负存入优先队列实现小根堆，按原数组顺序输出堆顶元素。

### 最优关键思路或技巧
- 利用异或运算的性质，将 $a_i \oplus a_j < 4$ 转化为 $\lfloor \frac{a_i}{4} \rfloor = \lfloor \frac{a_j}{4} \rfloor$，从而实现分组。
- 使用优先队列、`map`、`unordered_map`、`multiset` 等数据结构来存储和排序可交换元素。

### 拓展思路
同类型题可能会改变交换条件，例如改变异或值的范围，或者使用其他位运算条件。类似算法套路可以应用于需要根据某种条件进行分组并排序的问题。

### 推荐洛谷题目
- [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)
- [P1923 【深基9.例4】求第 k 小的数](https://www.luogu.com.cn/problem/P1923)
- [P1093 [NOIP2007 普及组] 奖学金](https://www.luogu.com.cn/problem/P1093)

### 个人心得摘录与总结
- **Harry1000**：第一次使用 Markdown 和在洛谷写题解，希望得到改进建议。总结：新手写题解时应积极寻求反馈，不断提高。

---
处理用时：45.51秒