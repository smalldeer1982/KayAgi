# 题目信息

# Rebranding

## 题目描述

The name of one small but proud corporation consists of $ n $ lowercase English letters. The Corporation has decided to try rebranding — an active marketing strategy, that includes a set of measures to change either the brand (both for the company and the goods it produces) or its components: the name, the logo, the slogan. They decided to start with the name.

For this purpose the corporation has consecutively hired $ m $ designers. Once a company hires the $ i $ -th designer, he immediately contributes to the creation of a new corporation name as follows: he takes the newest version of the name and replaces all the letters $ x_{i} $ by $ y_{i} $ , and all the letters $ y_{i} $ by $ x_{i} $ . This results in the new version. It is possible that some of these letters do no occur in the string. It may also happen that $ x_{i} $ coincides with $ y_{i} $ . The version of the name received after the work of the last designer becomes the new name of the corporation.

Manager Arkady has recently got a job in this company, but is already soaked in the spirit of teamwork and is very worried about the success of the rebranding. Naturally, he can't wait to find out what is the new name the Corporation will receive.

Satisfy Arkady's curiosity and tell him the final version of the name.

## 说明/提示

In the second sample the name of the corporation consecutively changes as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/b0c9599f7e4282de011e545b3b2138ce054cf709.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/b503b89dff83c09912a9706615e9f382f03f5909.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/e277cc6136141b35244d23f5857e2b4088822639.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/cfe2461ca78ee24244102008b38c52289020e201.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/c06bdcdcec7417c4f543399c6c3d126f67ecf0a6.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/e46b37134536ad3b6c864840e66c2932fc25c838.png)

## 样例 #1

### 输入

```
6 1
police
p m
```

### 输出

```
molice
```

## 样例 #2

### 输入

```
11 6
abacabadaba
a b
b c
a d
e g
f a
b b
```

### 输出

```
cdcbcdcfcdc
```

# AI分析结果



### 算法分类
字符串处理、映射优化

### 题解思路与解决难点
**核心思路**：  
维护字符的映射关系，每次交换操作仅更新映射表，而非修改整个字符串。最终根据映射表快速生成结果字符串。

**解决难点**：  
- **暴力不可行**：直接遍历字符串进行交换的时间复杂度为 O(nm)，无法处理 2e5 的数据量。
- **优化关键**：所有交换操作的最终效果可等效为每个字符的最终映射结果，因此只需维护每个字符的映射关系。

**算法实现要点**：  
1. **初始化映射表**：每个字符初始映射到自身。
2. **处理交换操作**：每次交换 x 和 y 时，交换它们的映射值。
3. **生成结果字符串**：根据最终映射表替换原字符串中的每个字符。

### 题解评分（≥4星）
1. **Lemansky的题解（5星）**  
   - 使用两个数组维护字符映射，时间复杂度 O(m + n)。  
   - 代码简洁高效，直接交换映射表中的值，逻辑清晰。  
   - 核心代码片段：  
     ```cpp
     swap(a[pos[x]], a[pos[y]]);
     swap(pos[x], pos[y]);
     ```

2. **wanggk的题解（4星）**  
   - 使用 `map` 维护映射，每次交换遍历所有字符更新映射。  
   - 时间复杂度 O(26m)，适用于大范围数据但略低于最优。  
   - 代码逻辑直观，适合理解映射原理。  
   - 核心代码片段：  
     ```cpp
     if (mp[i] == a) mp[i] = b;
     else if (mp[i] == b) mp[i] = a;
     ```

3. **zfw100的题解（4星）**  
   - 使用数组维护映射关系，每次交换直接更新数组。  
   - 时间复杂度 O(m + n)，代码简洁，但变量命名可优化。  
   - 核心代码片段：  
     ```cpp
     swap(r[a - 97], r[b - 97]);
     ```

### 最优思路提炼
1. **映射表法**：维护一个数组 `mp`，`mp[c]` 表示字符 `c` 的最终替换结果。  
2. **交换优化**：每次交换操作只需交换 `mp[x]` 和 `mp[y]`，时间复杂度 O(1)。  
3. **结果生成**：遍历原字符串，根据 `mp` 生成最终结果，时间复杂度 O(n)。

### 同类型题与算法套路
- **类似题目**：  
  - 字符替换（如 LeetCode 1154. 字符替换）  
  - 字符串变换（如 CodeForces 727E. Game with Strings）  
- **通用套路**：  
  当操作可分解为独立步骤且最终状态可累积时，优先维护状态映射而非实时处理。

### 推荐题目
1. [CF978B File Name](https://www.luogu.com.cn/problem/CF978B)  
2. [CF999B Reversing Encryption](https://www.luogu.com.cn/problem/CF999B)  
3. [CF1003B Binary String Constructing](https://www.luogu.com.cn/problem/CF1003B)

### 个人心得摘录
- **qian_shang**：通过逆向映射数组优化，但需注意映射逻辑的正确性。  
- **Lemansky**：通过双向数组维护映射关系，确保每次交换操作的高效性。  

### 可视化与算法演示
**核心算法流程**：  
1. **初始化**：每个字符映射到自身，用数组可视化初始状态。  
2. **交换操作**：高亮交换的字符对（如 x 和 y），更新映射表。  
3. **生成结果**：按原字符串顺序逐个替换为映射表中的值。

**复古像素动画设计**：  
- **颜色标记**：  
  - 当前交换的字符对（x, y）用红色高亮。  
  - 映射表更新时，对应字符位置用绿色闪烁。  
- **音效设计**：  
  - 交换操作时播放“哔”声，结果生成时播放“叮”声。  
- **Canvas 动画**：  
  以网格形式展示字符映射表，每次交换动态更新网格颜色，最终结果以滚动形式展示。

**交互功能**：  
- **步进控制**：支持暂停/继续，观察每一步映射表的变化。  
- **自动演示**：模拟 AI 自动执行所有交换操作，速度可调。  

---

### 核心代码实现（Lemansky）
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[130], pos[130], x, y;
int main() {
    int n, m; string s; 
    cin >> n >> m >> s;
    for (int i = 'a'; i <= 'z'; i++) 
        a[i] = i, pos[i] = i;
    while (m--) {
        cin >> x >> y;
        swap(a[pos[x]], a[pos[y]]);
        swap(pos[x], pos[y]);
    }
    for (char c : s) cout << a[c];
    return 0;
}
```

**代码解释**：  
- `a[c]` 存储字符 `c` 的最终映射值。  
- `pos[c]` 存储字符 `c` 在映射表中的位置，确保交换操作的高效性。  
- 每次交换时，直接交换映射表中的值及其位置，时间复杂度 O(1)。

---
处理用时：340.31秒