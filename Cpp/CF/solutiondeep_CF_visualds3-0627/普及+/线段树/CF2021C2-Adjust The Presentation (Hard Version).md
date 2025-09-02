# 题目信息

# Adjust The Presentation (Hard Version)

## 题目描述

This is the hard version of the problem. In the two versions, the constraints on $ q $ and the time limit are different. In this version, $ 0 \leq q \leq 2 \cdot 10^5 $ . You can make hacks only if all the versions of the problem are solved.

A team consisting of $ n $ members, numbered from $ 1 $ to $ n $ , is set to present a slide show at a large meeting. The slide show contains $ m $ slides.

There is an array $ a $ of length $ n $ . Initially, the members are standing in a line in the order of $ a_1, a_2, \ldots, a_n $ from front to back. The slide show will be presented in order from slide $ 1 $ to slide $ m $ . Each section will be presented by the member at the front of the line. After each slide is presented, you can move the member at the front of the line to any position in the lineup (without changing the order of the rest of the members). For example, suppose the line of members is $ [\color{red}{3},1,2,4] $ . After member $ 3 $ presents the current slide, you can change the line of members into either $ [\color{red}{3},1,2,4] $ , $ [1,\color{red}{3},2,4] $ , $ [1,2,\color{red}{3},4] $ or $ [1,2,4,\color{red}{3}] $ .

There is also an array $ b $ of length $ m $ . The slide show is considered good if it is possible to make member $ b_i $ present slide $ i $ for all $ i $ from $ 1 $ to $ m $ under these constraints.

However, your annoying boss wants to make $ q $ updates to the array $ b $ . In the $ i $ -th update, he will choose a slide $ s_i $ and a member $ t_i $ and set $ b_{s_i} := t_i $ . Note that these updates are persistent, that is changes made to the array $ b $ will apply when processing future updates.

For each of the $ q+1 $ states of array $ b $ , the initial state and after each of the $ q $ updates, determine if the slideshow is good.

## 说明/提示

For the first test case, you do not need to move the members as both slides are presented by member $ 1 $ , who is already at the front of the line. After that, set $ b_1 := 2 $ , now slide $ 1 $ must be presented by member $ 2 $ which is impossible as member $ 1 $ will present slide $ 1 $ first. Then, set $ b_1 = 1 $ , the $ b $ is the same as the initial $ b $ , making a good presentation possible.

## 样例 #1

### 输入

```
3
4 2 2
1 2 3 4
1 1
1 2
1 1
3 6 2
1 2 3
1 1 2 3 3 2
3 3
2 2
4 6 2
3 1 4 2
3 1 1 2 3 4
3 4
4 2```

### 输出

```
YA
TIDAK
YA
YA
TIDAK
YA
TIDAK
YA
YA```

# AI分析结果



**唯一算法分类**  
数据结构维护（集合与线段树）

---

**综合分析与结论**  
核心思路是维护每个元素在b数组中的首次出现位置，并确保其按原排列a的顺序递增。关键点在于每次修改后快速判断相邻元素首次出现位置是否递增。  
**核心算法流程**：  
1. 预处理每个元素首次出现位置，存入集合。  
2. 维护违规集合`st`，记录所有不满足递增条件的元素。  
3. 每次修改时，更新旧值和新值的集合，并检查相邻元素的首次位置关系。  
4. 若`st`为空，说明条件满足。  

**可视化设计思路**：  
- **动画方案**：以网格展示各元素的首次出现位置，当前修改位置高亮显示。  
- **颜色标记**：违反条件的元素对用红色标记，合法对为绿色。  
- **步进控制**：可单步执行修改，观察集合变化与违规状态更新。  
- **复古风格**：8位像素界面，用不同颜色方块表示元素首次位置，音效提示违规状态。

---

**题解清单 (≥4星)**  
1. **chenxi2009（5星）**  
   使用集合维护首次出现位置，通过检查相邻元素的最小位置关系高效更新违规集合。代码结构清晰，逻辑严密。  
   关键亮点：利用`set`快速查询首次位置，仅处理受影响元素，复杂度O(q log m)。  

2. **Day_Tao（4星）**  
   维护`cnt`变量统计相邻违规次数，每次修改仅更新相关位置。代码简洁，采用`set`与预判边界条件。  
   关键亮点：通过`cnt`快速判断全局合法性，减少冗余检查。  

3. **GY程袁浩（4星）**  
   映射原排列为排名，线段树维护递增性。代码模块化，线段树合并区间信息高效判断全局条件。  
   关键亮点：线段树维护区间极值与单调性，适合大规模动态检查。  

---

**最优思路或技巧提炼**  
1. **首次出现位置维护**：每个元素用`set`存储出现位置，取最小值即为首次出现位置。  
2. **相邻元素条件检查**：仅需比较相邻元素的首次位置，避免全局遍历。  
3. **高效更新策略**：每次修改仅处理旧值和新值的相邻元素，复杂度O(1)次集合操作。  

---

**同类型题或算法套路**  
- **维护动态序列条件**：如区间单调性、极值约束等，常用线段树或差分集合。  
- **首次出现特征**：类似“最早出现”问题，可结合集合或优先队列。  

---

**推荐洛谷题目**  
1. P1972 [SDOI2009]HH的项链（维护元素首次出现）  
2. P1908 逆序对（动态维护序列条件）  
3. P3384 【模板】轻重链剖分（线段树维护区间属性）  

---

**代码核心逻辑片段**  
以chenxi2009的代码为例：  
```cpp
set<int> q[N]; // 存储每个元素的出现位置
set<int> st;   // 记录违规元素

// 修改操作处理
void update(int s, int t) {
    int old = b[s];
    q[old].erase(s);
    // 处理旧值的影响
    if (q[old].empty() || (q[old-1].size() && *q[old-1].begin() < *q[old].begin())) 
        st.erase(old);
    if (old < n && q[old+1].size() && (q[old].empty() || *q[old].begin() > *q[old+1].begin()))
        st.insert(old+1);

    // 处理新值的影响
    b[s] = t;
    q[t].insert(s);
    if (t != 1 && (q[t-1].empty() || *q[t-1].begin() > *q[t].begin()))
        st.insert(t);
    if (q[t+1].empty() || (q[t].size() && *q[t].begin() < *q[t+1].begin()))
        st.erase(t+1);
}
```

---

**可视化实现要点**  
- **Canvas绘制**：网格每行代表一个元素，方块高度表示首次出现位置。  
- **音效触发**：违规时播放低频音，合法时高频音。  
- **自动演示**：按修改顺序逐步执行，展示集合变化与违规更新。  
- **像素风格**：使用16色调色板，元素位置变化用渐变动画过渡。  

**复古游戏化代码片段（伪代码）**  
```javascript
// 绘制首次位置方块
function drawPositions() {
    ctx.fillStyle = '#8B00FF'; // 紫色背景
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    for (let i = 1; i <= n; i++) {
        const pos = firstPos[i] || m+1;
        const y = (pos / (m+1)) * canvas.height;
        ctx.fillStyle = st.has(i) ? '#FF0000' : '#00FF00'; // 违规红色
        ctx.fillRect(i*30, y, 25, 25);
    }
}
// 修改时播放音效
function playSound(valid) {
    const freq = valid ? 880 : 220;
    osc.frequency.value = freq;
    osc.start().stop(audioCtx.currentTime + 0.1);
}
```

---
处理用时：95.60秒