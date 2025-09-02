# 题目信息

# Holidays

## 题目描述

School holidays come in Berland. The holidays are going to continue for $ n $ days. The students of school № $ N $ are having the time of their lives and the IT teacher Marina Sergeyevna, who has spent all the summer busy checking the BSE (Berland State Examination) results, has finally taken a vacation break! Some people are in charge of the daily watering of flowers in shifts according to the schedule. However when Marina Sergeyevna was making the schedule, she was so tired from work and so lost in dreams of the oncoming vacation that she perhaps made several mistakes. In fact, it is possible that according to the schedule, on some days during the holidays the flowers will not be watered or will be watered multiple times. Help Marina Sergeyevna to find a mistake.

## 说明/提示

Keep in mind that in the second sample the mistake occurs not only on the second day, but also on the sixth day, when nobody waters the flowers. However, you have to print the second day, i.e. the day with the minimal number.

## 样例 #1

### 输入

```
10 5
1 2
3 3
4 6
7 7
8 10
```

### 输出

```
OK
```

## 样例 #2

### 输入

```
10 5
1 2
2 3
4 5
7 8
9 10
```

### 输出

```
2 2
```

## 样例 #3

### 输入

```
10 5
1 2
3 3
5 7
7 7
7 10
```

### 输出

```
4 0
```

# AI分析结果



---

### 唯一算法分类
差分数组 / 前缀和

---

### 综合分析与结论
**核心逻辑**：通过区间标记统计每个天数的浇水次数，检测第一个非1值。  
**实现难点**：  
1. 高效处理多次区间累加（模拟法 O(nm) vs 差分法 O(m+n)）  
2. 边界处理（如差分数组的 r+1 反标记）  

**最优解法**：差分数组。时间复杂度 O(m + n)，通过两次遍历完成区间标记和统计，适合本题及更大数据范围。  

**可视化设计**：  
1. **差分步骤动画**：  
   - 用不同颜色高亮当前处理的区间 [a, b]  
   - 在差分数组的 a 位置显示绿色+1，b+1 位置显示红色-1  
   - 前缀和计算时，用流动箭头表示累加过程  
2. **复古像素风格**：  
   - 用 8-bit 像素块表示天数，浇水次数通过颜色深浅变化（如白色=0，黄色=1，红色≥2）  
   - 播放 8-bit 音效：区间标记时短促“滴”声，错误时播放失败音效  

---

### 题解清单（≥4星）

1. **ziiidan（差分法） - ⭐⭐⭐⭐⭐**  
   - 亮点：标准差分实现，代码简洁，逻辑清晰  
   - 核心代码：  
     ```cpp
     c[fr]++; c[to+1]--;  // 差分标记
     c[i] = c[i-1] + c[i]; // 前缀和
     ```

2. **锦瑟，华年（差分法） - ⭐⭐⭐⭐**  
   - 亮点：代码注释明确，适合教学  
   - 心得：“差分核心程序”分两步，强调算法结构  

3. **曼恩薄荷（树状数组） - ⭐⭐⭐⭐**  
   - 亮点：拓展思路展示高级数据结构应用  
   - 技巧：用树状数组维护差分，支持动态更新  

---

### 核心代码实现（差分法）
```cpp
int c[maxn] = {0};
for (int i=1; i<=m; i++) {
    int l, r;
    cin >> l >> r;
    c[l]++;         // 区间起点+1
    c[r+1]--;       // 区间终点+1位置-1
}
for (int i=1; i<=n; i++) {
    c[i] += c[i-1]; // 前缀和计算实际次数
    if (c[i] != 1) {
        cout << i << " " << c[i];
        return 0;
    }
}
```

---

### 同类型题与算法套路
**通用套路**：  
- 区间增减 → 差分数组  
- 单点查询 → 前缀和  

**推荐题目**：  
1. P2280 [HNOI2003]激光炸弹（二维前缀和）  
2. P3406 海底高铁（差分+贪心）  
3. P2367 语文成绩（差分最小值）  

---

### 个人心得摘录
- **ziiidan**：“一维差分原理要打开始和结束标记，前缀和恢复”  
- **rfsfreffr**：“WA多次后发现区间覆盖需分三种情况讨论，边界处理是关键”  

---

### 复古游戏化动画示例（伪代码）
```javascript
// Canvas绘制逻辑（示例）
function drawDay(day, count) {
    ctx.fillStyle = count === 1 ? '#FFFF00' : (count === 0 ? '#FFFFFF' : '#FF0000');
    ctx.fillRect(day * 10, 50, 8, 8); // 8x8像素块表示每一天
}

// 音效触发
function playSound(effect) {
    if (effect === 'error') new Audio('8bit-error.wav').play();
}
```

---

**总结**：差分法以高效和简洁胜出，适合算法教学；模拟法直观易实现，适合快速解题。

---
处理用时：101.18秒