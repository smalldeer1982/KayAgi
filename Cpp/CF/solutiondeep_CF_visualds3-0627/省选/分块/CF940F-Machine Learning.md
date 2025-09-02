# 题目信息

# Machine Learning

## 题目描述

You come home and fell some unpleasant smell. Where is it coming from?

You are given an array $ a $ . You have to answer the following queries:

1. You are given two integers $ l $ and $ r $ . Let $ c_{i} $ be the number of occurrences of $ i $ in $ a_{l:r} $ , where $ a_{l:r} $ is the subarray of $ a $ from $ l $ -th element to $ r $ -th inclusive. Find the Mex of $ {c_{0},c_{1},...,c_{10^{9}}} $
2. You are given two integers $ p $ to $ x $ . Change $ a_{p} $ to $ x $ .

The Mex of a multiset of numbers is the smallest non-negative integer not in the set.

Note that in this problem all elements of $ a $ are positive, which means that $ c_{0} $ = 0 and $ 0 $ is never the answer for the query of the second type.

## 说明/提示

The subarray of the first query consists of the single element — $ 1 $ .

The subarray of the second query consists of four $ 2 $ s, one $ 3 $ and two $ 1 $ s.

The subarray of the fourth query consists of three $ 1 $ s, three $ 2 $ s and one $ 3 $ .

## 样例 #1

### 输入

```
10 4
1 2 3 1 1 2 2 2 9 9
1 1 1
1 2 8
2 7 1
1 2 8
```

### 输出

```
2
3
2
```

# AI分析结果



### 算法分类  
**带修莫队**

---

### 综合分析与结论  
#### 核心思路与难点  
1. **离散化处理**  
   所有输入元素（包括修改后的值）需离散化，以应对数值范围过大（1e9）的问题。  
   - **实现关键**：将原数组和修改操作中的新值统一排序去重，映射到连续整数。  

2. **带修莫队框架**  
   - **分块排序**：按块排序查询，块大小为 `n^(2/3)`，保证复杂度为 `O(n^(5/3))`。  
   - **时间轴处理**：维护当前修改操作的时间戳，处理区间移动时同步调整修改影响。  

3. **维护出现次数与mex计算**  
   - **核心变量**：  
     - `cnt[x]`：数值 `x` 的出现次数。  
     - `tot[y]`：出现次数为 `y` 的数值个数。  
   - **mex暴力求解**：从1开始枚举，找到最小的未在 `tot` 中出现的值，复杂度 `O(√n)`。  

#### 可视化设计思路  
- **动画流程**：  
  1. **区间移动**：左右指针移动时，高亮当前元素（如红色方块），显示 `cnt` 和 `tot` 的更新过程。  
  2. **时间轴回退/推进**：以时间线滑动效果展示修改操作的撤销或应用，用箭头指示当前修改位置。  
  3. **mex计算**：动态显示枚举过程，每次检查 `tot[i]` 是否为零，高亮当前检查的 `i`。  
- **复古像素风格**：  
  - **颜色方案**：使用16色调色板，`cnt` 用蓝色渐变，`tot` 用绿色渐变，当前操作元素闪烁黄色。  
  - **音效**：指针移动时播放“滴”声，修改操作时播放“咔嚓”声，找到mex时播放胜利音效。  

---

### 题解评分（≥4星）  
1. **ouuan（5星）**  
   - **亮点**：代码简洁，离散化处理全面，暴力求mex的复杂度分析清晰。  
   - **关键代码**：  
     ```cpp  
     for (ans[q[i].id]=1; tot[ans[q[i].id]]>0; ++ans[q[i].id]);  
     ```  
   - **个人心得**：“`tot[0]` 初始化为极大值，避免0干扰mex计算”。  

2. **NaCly_Fish（4星）**  
   - **亮点**：优化 `cnt` 数组更新逻辑，减少冗余操作。  
   - **关键代码**：  
     ```cpp  
     void update(int x, int t) {  
         if (x >= l && x <= r) {  
             --cnt1[old]; ++cnt1[++new];  
         }  
     }  
     ```  

3. **juju527（4星）**  
   - **亮点**：详细推导mex的上界，强调分块暴力合理性。  
   - **关键代码**：  
     ```cpp  
     for (ans=1; tot[ans]>0; ++ans);  
     ```  

---

### 最优思路与技巧  
1. **离散化全覆盖**：将原数组和修改值统一离散化，确保所有可能值被映射。  
2. **双数组维护**：`cnt` 和 `tot` 分离统计，避免混淆数值与次数。  
3. **时间轴交换技巧**：修改操作时交换原值与修改值，便于撤销操作。  
4. **暴力求mex**：利用 `O(√n)` 特性，直接枚举无需复杂数据结构。  

---

### 同类型题与推荐  
1. **P1903 [国家集训队]数颜色**：带修莫队模板题。  
2. **P4137 Rmq Problem**：普通莫队求数值mex。  
3. **P4074 糖果公园**：树上带修莫队综合应用。  

---

### 可视化代码片段（复古风格）  
```javascript  
// Canvas绘制像素块  
function drawBlock(x, y, color) {  
    ctx.fillStyle = color;  
    ctx.fillRect(x * 10, y * 10, 8, 8);  
}  

// 播放音效  
function playSound(effect) {  
    const osc = audioContext.createOscillator();  
    osc.frequency.value = effect === 'move' ? 440 : 880;  
    osc.connect(audioContext.destination);  
    osc.start(); osc.stop(0.1);  
}  

// 自动演示循环  
function autoStep() {  
    if (step < maxSteps) {  
        movePointer();  
        updateCounters();  
        playSound('move');  
        step++;  
        requestAnimationFrame(autoStep);  
    }  
}  
```  

---

### 核心代码实现  
```cpp  
// 离散化处理（ouuan题解）  
vector<int> b;  
for (int i=1; i<=n; ++i) b.push_back(a[i]);  
for (int i=1; i<=m; ++i) {  
    if (修改操作) b.push_back(新值);  
}  
sort(b.begin(), b.end());  
auto it = unique(b.begin(), b.end());  
b.resize(distance(b.begin(), it));  

// 带修莫队移动（关键逻辑）  
void add(int x) {  
    --tot[cnt[x]];  
    ++tot[++cnt[x]];  
}  
void del(int x) {  
    --tot[cnt[x]];  
    ++tot[--cnt[x]];  
}  

// 求mex  
for (ans=1; tot[ans]>0; ++ans);  
```

---
处理用时：61.01秒