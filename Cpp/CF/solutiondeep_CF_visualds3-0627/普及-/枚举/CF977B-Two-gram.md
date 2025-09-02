# 题目信息

# Two-gram

## 题目描述

Two-gram is an ordered pair (i.e. string of length two) of capital Latin letters. For example, "AZ", "AA", "ZA" — three distinct two-grams.

You are given a string $ s $ consisting of $ n $ capital Latin letters. Your task is to find any two-gram contained in the given string as a substring (i.e. two consecutive characters of the string) maximal number of times. For example, for string $ s $ = "BBAABBBA" the answer is two-gram "BB", which contained in $ s $ three times. In other words, find any most frequent two-gram.

Note that occurrences of the two-gram can overlap with each other.

## 说明/提示

In the first example "BA" is also valid answer.

In the second example the only two-gram "ZZ" can be printed because it contained in the string "ZZZAA" two times.

## 样例 #1

### 输入

```
7
ABACABA
```

### 输出

```
AB
```

## 样例 #2

### 输入

```
5
ZZZAA
```

### 输出

```
ZZ
```

# AI分析结果



## 算法分类
字符串处理 & 频率统计

---

## 综合分析与结论
### 核心算法流程
1. **遍历字符串**：每次取连续两个字符作为子串
2. **统计频率**：使用二维数组（26x26）记录每个子串出现次数
3. **找最大值**：遍历统计数组，记录最大出现次数及对应子串

### 最优思路
采用**二维数组直接寻址法**：
```cpp
int cnt[26][26] = {0};
for (int i=0; i<s.size()-1; ++i) {
    int x = s[i] - 'A', y = s[i+1] - 'A';
    cnt[x][y]++;
    if (cnt[x][y] > max_cnt) {
        max_cnt = cnt[x][y];
        ans = {s[i], s[i+1]};
    }
}
```

### 可视化设计
1. **像素网格**：用26x26的方格表示所有可能的子串
2. **颜色映射**：
   - 初始灰色（未出现）
   - 蓝色渐变（出现次数增加）
   - 红色高亮（当前最大值）
3. **动画效果**：
   - 字符对逐个扫描，对应格子颜色加深
   - 发现新最大值时触发闪烁红光
   - 右侧面板实时显示当前最大子串和次数

---

## 题解清单（≥4星）
### 1. Cult_style（二维数组法）⭐⭐⭐⭐⭐
**亮点**：时间复杂度O(n)，空间O(1)，最优效率实现  
**核心代码**：
```cpp
int k[30][30] = {0};
for(int i=0; i<n-1; i++){
    int x=a[i]-'A', y=a[i+1]-'A';
    k[x][y]++;
    if(k[x][y]>ma) ma=k[x][y];
}
```

### 2. WinterRain208（map遍历法）⭐⭐⭐⭐
**亮点**：利用C++11特性简化遍历，代码简洁  
**核心代码**：
```cpp
map<string, int> m;
for(int i=0; i<a.size()-1; i++)
    m[a.substr(i,2)]++;
for(auto&& p : m)
    if(p.second>M) ans = p.first;
```

### 3. judgejudge（ASCII直接映射）⭐⭐⭐⭐
**亮点**：通过ASCII码直接计算索引，避免类型转换  
**核心代码**：
```cpp
a[st[i]-64][st[i+1]-64]++;
for(int i=1; i<=26; i++)
    for(int j=1; j<=26; j++)
        if(a[i][j]>maxl) row=i, col=j;
```

---

## 类似题目推荐
1. **P1012 [NOIP1998 提高组] 拼数**  
   （统计数字组合的出现规律）

2. **P1308 [NOIP2011 普及组] 统计单词数**  
   （字符串模式匹配与频率统计）

3. **CF1003B Binary String Constructing**  
   （二进制字符串模式构造）

---

## 可视化代码片段（Canvas实现）
```javascript
// 初始化26x26网格
const grid = new Array(26).fill().map(() => 
    new Array(26).fill(0));

function drawGrid() {
    ctx.clearRect(0, 0, 512, 512);
    for(let i=0; i<26; i++) {
        for(let j=0; j<26; j++) {
            const val = grid[i][j];
            ctx.fillStyle = `hsl(240, ${val*5}%, 50%)`;
            ctx.fillRect(j*18, i*18, 16, 16);
        }
    }
}

// 扫描字符串时更新
function processCharPair(a, b) {
    const i = a.charCodeAt(0)-65;
    const j = b.charCodeAt(0)-65;
    grid[i][j]++;
    drawGrid();
    // 触发音效
    if(grid[i][j] > currentMax) {
        playSound('up');
        currentMax = grid[i][j];
    } else {
        playSound('click');
    }
}
```

---

## 复古游戏化设计
1. **8-bit音效**：
   - `click.wav`：每次统计时播放（8位脉冲音）
   - `up.wav`：发现新最大值时播放（上升琶音）
   - `complete.wav`：结束时播放（胜利小调）

2. **积分系统**：
   - 每统计一个字符对+10分
   - 发现新最大值+100分
   - 连击奖励（连续发现新最大值时分数翻倍）

3. **AI演示模式**：
   - 自动以0.5秒步进速度演示
   - 按空格切换手动/自动模式
   - 按F加速演示（最高4倍速）

---
处理用时：82.62秒