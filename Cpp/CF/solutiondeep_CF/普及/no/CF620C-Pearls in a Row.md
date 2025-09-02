# 题目信息

# Pearls in a Row

## 题目描述

There are $ n $ pearls in a row. Let's enumerate them with integers from $ 1 $ to $ n $ from the left to the right. The pearl number $ i $ has the type $ a_{i} $ .

Let's call a sequence of consecutive pearls a segment. Let's call a segment good if it contains two pearls of the same type.

Split the row of the pearls to the maximal number of good segments. Note that each pearl should appear in exactly one segment of the partition.

As input/output can reach huge size it is recommended to use fast input/output methods: for example, prefer to use scanf/printf instead of cin/cout in C++, prefer to use BufferedReader/PrintWriter instead of Scanner/System.out in Java.

## 样例 #1

### 输入

```
5
1 2 3 4 1
```

### 输出

```
1
1 5
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
7
1 2 1 3 1 2 1
```

### 输出

```
2
1 3
4 7
```

# AI分析结果



### 题目重写

#### 题目名称：珍珠序列

**题目描述**  
一行中有 $n$ 颗珍珠，从左到右依次编号为 $1$ 到 $n$。第 $i$ 颗珍珠的类型为 $a_i$。  
定义一个连续的珍珠序列为“段”，若某段中包含两个相同类型的珍珠，则称其为“好段”。  
请将珍珠序列分割为尽可能多的“好段”，且每个珍珠必须恰好属于一个段。若无法分割，输出 $-1$。

**输入格式**  
第一行输入整数 $n$，第二行输入 $n$ 个整数表示珍珠类型序列。  
**输出格式**  
第一行输出分割段数，随后每行输出各段的左右端点。若无法分割，输出 $-1$。

---

### 算法分类  
**贪心**

---

### 题解分析与结论

#### 核心思路  
所有题解均采用贪心策略，通过哈希结构（`set/map`）记录当前段中的元素，遇到重复元素时立即分割，尽可能多地生成段，并处理末尾未覆盖的情况。

#### 关键优化与难点  
1. **哈希结构的选择**：利用 `set/map` 快速判断重复元素，时间复杂度为 $O(n \log n)$。  
2. **末尾处理**：分割后若最后一段未覆盖到 $n$，需强制将其右端点设为 $n$。  
3. **避免频繁清空**：通过时间戳标记替代 `clear()`，减少哈希表操作次数（HMZHMZHMZ 的优化）。

---

### 精选题解

#### 1. HMZHMZHMZ（4星）  
**亮点**：时间戳替代清空操作，减少哈希表开销，代码简洁高效。  
**代码核心**：  
```cpp
int t = 1; // 时间戳
for (int i = 1; i <= n; ++i) {
    x = read();
    if (mp[x] == t) { // 当前时间戳已标记该元素
        ++t;
        q.push({l, i});
        l = i + 1;
    } else {
        mp[x] = t; // 更新当前时间戳
    }
}
```

#### 2. 傅思维666（4星）  
**亮点**：强制修正最后一段右端点为 $n$，确保完全覆盖。  
**代码核心**：  
```cpp
ans[cnt].r = n; // 处理末尾
printf("%d %d\n", ans[i].l, ans[i].r);
```

#### 3. hxhhxh（4星）  
**亮点**：队列动态维护分割区间，处理末尾逻辑清晰。  
**代码核心**：  
```cpp
if (ans.empty()) cout << -1;
else {
    ans.back().second = n; // 强制最后一段覆盖到末尾
}
```

---

### 最优思路总结  
1. **贪心分割**：每发现重复元素立即分割。  
2. **哈希加速**：使用 `set/map` 快速判断重复，时间复杂度 $O(n \log n)$。  
3. **末尾修正**：确保最后一段覆盖到 $n$。  
4. **时间戳优化**：避免频繁清空哈希表，提升效率。

---

### 类似题目推荐  
1. [P1496 火烧赤壁](https://www.luogu.com.cn/problem/P1496)（贪心区间覆盖）  
2. [CF1175E Minimal Segment Cover](https://www.luogu.com.cn/problem/CF1175E)（贪心+预处理）  
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)（贪心排序）  

---

### 个人心得摘录  
- **jockbutt**：初始化数组时需注意越界问题（如 `l[1001000]` 的初始化方式可能隐含错误）。  
- **MIN__2500**：大数组易导致 MLE，需合理估算空间。  
- **HMZHMZHMZ**：时间戳替代清空操作是优化关键。

---
处理用时：80.67秒