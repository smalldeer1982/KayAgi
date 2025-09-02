# 题目信息

# Water Taps

## 题目描述

Consider a system of $ n $ water taps all pouring water into the same container. The $ i $ -th water tap can be set to deliver any amount of water from $ 0 $ to $ a_{i} $ ml per second (this amount may be a real number). The water delivered by $ i $ -th tap has temperature $ t_{i} $ .

If for every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF954E/035d166bda223ecd5c31eb614a76bdcc9b8fe8c4.png) you set $ i $ -th tap to deliver exactly $ x_{i} $ ml of water per second, then the resulting temperature of water will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF954E/4d0f711b0c4dc1450cd61a20f118d34a644e0d79.png) (if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF954E/dbce41b29215315b290a54646261b5eaa9727507.png), then to avoid division by zero we state that the resulting water temperature is $ 0 $ ).

You have to set all the water taps in such a way that the resulting temperature is exactly $ T $ . What is the maximum amount of water you may get per second if its temperature has to be $ T $ ?

## 样例 #1

### 输入

```
2 100
3 10
50 150
```

### 输出

```
6.000000000000000
```

## 样例 #2

### 输入

```
3 9
5 5 30
6 6 10
```

### 输出

```
40.000000000000000
```

## 样例 #3

### 输入

```
2 12
1 3
10 15
```

### 输出

```
1.666666666666667
```

# AI分析结果



### 综合分析与结论

**题目核心**：将水龙头分为温度高于、等于、低于目标温度三类，通过贪心策略最大化总水量。  
**关键变形**：$\sum x_i(t_i-T)=0$，转化为热量差总和为0的问题。  
**贪心策略**：优先使用温度差较小的冷/热水龙头，以等热量差下获得更多水量。  
**实现难点**：排序方向、双指针移动逻辑、浮点精度处理。  

**可视化设计**：  
- **8位像素风格**：冷（蓝色）、热（红色）、温水（绿色）水龙头分列两侧。  
- **动画步骤**：高亮当前处理的冷热水龙头，动态显示水量调整与热量差抵消。  
- **音效**：选择时短音，成功抵消时上升音调，错误时警报音。  
- **自动模式**：AI模拟双指针移动，展示贪心选择过程。  

---

### 题解评分（≥4星）

1. **UncleSam_Died（4.5星）**  
   - **亮点**：严谨的双指针分类讨论，正确处理正负热量差。  
   - **代码**：结构清晰，通过排序后分界点处理冷热队列。  

2. **Fimlty（4.5星）**  
   - **亮点**：简洁的向量分治，直接按绝对值排序，代码优雅易读。  
   - **技巧**：利用`auto`和引用简化变量操作，逻辑紧凑。  

3. **Kelin（4星）**  
   - **亮点**：单次遍历解决正负总和，代码极简，适合竞赛快速实现。  
   - **优化**：通过反转数组减少判断分支。  

---

### 最优思路与代码片段

**核心贪心逻辑**：  
1. 将温度等于T的水龙头直接加满。  
2. 冷热水龙头按温度差绝对值升序排序。  
3. 双指针遍历冷热队列，每次选择较小热量差的水龙头，计算最大可抵消水量。  

**代码实现（Fimlty题解）**：  
```cpp
sort(H.begin(), H.end());  // 热水按温度差升序
sort(C.begin(), C.end());  // 冷水按绝对值升序

int hl = 0, cl = 0;
while (hl < H.size() && cl < C.size()) {
    auto& [ht, ha] = H[hl];
    auto& [ct, ca] = C[cl];
    if (ht * ha > ct * ca) {  // 热水热量差大，全用冷水
        ans += ca + (ct * ca) / ht;  // 冷水全用，调整热水
        ha -= (ct * ca) / ht;
        cl++;
    } else {  // 反之全用热水
        ans += ha + (ht * ha) / ct;
        ca -= (ht * ha) / ct;
        hl++;
    }
}
```

---

### 同类型题目与套路

**贪心常见场景**：  
- 热量/资源平衡问题（如本题的冷热抵消）。  
- 区间调度（选择不重叠区间最大化数量）。  
- 最小生成树（Kruskal的边排序）。  

**相似题目**：  
1. **P1230 智力大冲浪**（时间与收益的贪心平衡）。  
2. **P1094 纪念品分组**（双指针求最小组合）。  
3. **P5019 铺设道路**（贪心填坑问题）。  

---

### 个人心得摘录

- **UncleSam_Died**：调试中发现未处理浮点精度，需引入`eps`比较。  
- **Fimlty**：利用`auto&`直接修改vector元素，简化代码逻辑。  
- **Kelin**：通过反转数组统一处理正负情况，减少代码分支。  

---

### 可视化代码（简略示例）

```javascript
// 伪代码：Canvas绘制冷热队列
function drawTaps() {
    ctx.fillStyle = '#00F'; // 冷水
    coldTaps.forEach((tap, i) => drawRect(i*30, 100, 20, tap.amount));
    ctx.fillStyle = '#F00'; // 热水
    hotTaps.forEach((tap, i) => drawRect(i*30, 200, 20, tap.amount));
}

// 贪心步骤动画
function animateStep() {
    let cold = coldQueue[cl], hot = hotQueue[hl];
    if (cold.heat < hot.heat) {
        // 消耗冷水，调整热水
        playSound('cold');
        adjustHotAmount(-cold.heat);
    } else {
        // 消耗热水，调整冷水
        playSound('hot');
        adjustColdAmount(-hot.heat);
    }
}
```

---

### 推荐题目

1. **P1090 合并果子**（贪心+优先队列）。  
2. **P1223 排队接水**（平均等待时间最小化）。  
3. **P3817 小A的糖果**（相邻约束下的贪心调整）。

---
处理用时：89.06秒