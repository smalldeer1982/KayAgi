# 题目信息

# Tyndex.Brome

## 题目描述

每个测试字符串$S$都有一个**独立**的$ans$。



对于测试字符串$S$的每个字母$S_{i}$，可以找到标准字符串$C$中字母$S_{i}$的离$i$的最近位置$j$。将位置的绝对差$\left|i-j \right|$加到$ans$中。也就是说对于每个$i$，取位置$j$，使得 $S_i = C_j$ 且$\left|i-j \right|$最小。



如果标准字符串中不存在字母$C_i$，则将测试字符串$S$的长度添加到$ans$。

## 样例 #1

### 输入

```
2 10
codeforces
codeforces
codehorses
```

### 输出

```
0
12
```

## 样例 #2

### 输入

```
9 9
vkontakte
vcontacte
vkontrakte
vkollapse
vkrokodile
vtopke
vkapuste
vpechke
vk
vcodeforcese
```

### 输出

```
18
14
36
47
14
29
30
0
84
```

# AI分析结果



### 题目重写
每个测试字符串$S$都有一个**独立**的$ans$。对于$S$中的每个字符$S_i$，找到标准字符串$C$中相同字符的最近位置$j$，将$|i-j|$累加到$ans$。若$C$中无该字符，则累加$S$的长度。

### 算法分类
字符串、二分

### 综合分析与结论
核心问题需要快速找到字符在标准字符串中的最近位置。最优解法通过预处理字符位置+二分查找实现高效查询。关键技巧是利用有序数据结构存储位置，通过二分快速定位最近前驱/后继位置。

---

### 精选题解
#### 1. HyGeoIceFairy（5星）
**关键亮点**：
- 使用`set`存储字符位置，插入哨兵值处理边界
- 利用`upper_bound`和`lower_bound`快速定位最近前后位置
- 代码简洁，时间复杂度O(L log K)

**核心代码**：
```cpp
set<int> se[27]; // 存储每个字符的位置
for(int i=0;i<lc;i++) 
    se[c[i]-'a'+1].insert(i); // 预处理

ui = se[ch].upper_bound(j);  // 第一个大于j的位置
li = ui; --li;               // 最后一个小于等于j的位置
temp = min(j-*li, *ui-j);     // 取最近距离
```

#### 2. fjy666（4星）
**关键亮点**：
- 显式处理`lower_bound`的边界情况
- 检查迭代器是否指向`begin/end`避免越界
- 详细注释解释二分逻辑

**核心代码**：
```cpp
It(std::set<int>) it = S[ch].lower_bound(j);
It(std::set<int>) it2 = it;
if(it != S[ch].begin()) --it; 
if(it2 == S[ch].end()) it2 = it;
int Min = min(abs(*it-j), abs(*it2-j));
```

#### 3. Ryan_Adam（4星）
**关键亮点**：
- 用`vector`存储位置，`lower_bound`二分查找
- 比较前驱、当前、后继三个位置取最小值
- 代码结构清晰，适合理解二分思想

**核心代码**：
```cpp
vector<int>& pos = mp[c[j]]; // 当前字符的位置数组
auto it = lower_bound(pos.begin(), pos.end(), j);
int min_dist = min(abs(*it-j), abs(*(it-1)-j));
```

---

### 关键思路总结
1. **预处理位置**：为每个字符建立有序位置列表（`vector`或`set`）
2. **二分查找**：使用`lower_bound/upper_bound`快速定位最近前驱/后继
3. **边界处理**：通过哨兵值或显式检查处理空列表/首尾位置

---

### 拓展与相似题目
1. [P2249 【深基13.例1】查找](https://www.luogu.com.cn/problem/P2249)  
   （二分查找模板题）
2. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)  
   （字符串匹配与位置查找）
3. [P1918 保龄球](https://www.luogu.com.cn/problem/P1918)  
   （二分查找应用）

---

### 调试经验摘录
- **HyGeoIceFairy**：插入极大/极小哨兵值，统一处理无前驱/后继的情况  
  > "两边用maxx判断是否存在字母，避免迭代器越界"
- **wangshi**：通过代码生成器处理重复逻辑  
  > "输出生成26个字母的if判断代码，避免手动编写冗余代码"

---
处理用时：191.26秒