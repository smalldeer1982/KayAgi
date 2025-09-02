# 题目信息

# Photographer

## 题目描述

Valera's lifelong ambition was to be a photographer, so he bought a new camera. Every day he got more and more clients asking for photos, and one day Valera needed a program that would determine the maximum number of people he can serve.

The camera's memory is $ d $ megabytes. Valera's camera can take photos of high and low quality. One low quality photo takes $ a $ megabytes of memory, one high quality photo take $ b $ megabytes of memory. For unknown reasons, each client asks him to make several low quality photos and several high quality photos. More formally, the $ i $ -th client asks to make $ x_{i} $ low quality photos and $ y_{i} $ high quality photos.

Valera wants to serve as many clients per day as possible, provided that they will be pleased with his work. To please the $ i $ -th client, Valera needs to give him everything he wants, that is, to make $ x_{i} $ low quality photos and $ y_{i} $ high quality photos. To make one low quality photo, the camera must have at least $ a $ megabytes of free memory space. Similarly, to make one high quality photo, the camera must have at least $ b $ megabytes of free memory space. Initially the camera's memory is empty. Valera also does not delete photos from the camera so that the camera's memory gradually fills up.

Calculate the maximum number of clients Valera can successfully serve and print the numbers of these clients.

## 样例 #1

### 输入

```
3 10
2 3
1 4
2 1
1 0
```

### 输出

```
2
3 2 ```

## 样例 #2

### 输入

```
3 6
6 6
1 1
1 0
1 0
```

### 输出

```
1
2 ```

# AI分析结果



# 算法分类  
**贪心算法**

---

# 综合分析与结论  

## 核心算法流程  
1. **需求转换**：将每个客户的低质量照片数 x_i 和高质量照片数 y_i 转换为总内存消耗 `x_i*a + y_i*b`  
2. **贪心排序**：将所有客户按总内存消耗升序排列  
3. **累积选择**：从内存消耗最小的客户开始依次处理，若剩余内存足够则选择该客户，直到内存不足  

## 解决难点对比  
- **排序依据推导**：各题解均正确推导出总内存消耗作为排序依据，但部分题解未明确证明其最优性（可通过反证法证明：若存在更优的非升序排列方案，交换任意两个逆序客户能得到更优解）  
- **编号处理技巧**：Szr__QAQ 在结构体中存储原始编号，yzm0325 使用独立 id 字段，均保证输出顺序与选择顺序一致  
- **边界处理**：所有题解正确处理 `d -= sum` 后判断 `d < 0` 的边界条件  

## 可视化设计思路  
### 像素化动画方案  
1. **数据结构展示**：  
   - 使用 32x32 像素方块表示每个客户，颜色深浅表示总内存（深色=高内存需求）  
   - 右侧动态显示内存条（绿色进度条逐渐缩短）  

2. **关键步骤高亮**：  
   - 当前选中客户方块闪烁黄色边框  
   - 每次选择后播放 "coin.wav" 音效（类似超级马里奥金币音效）  
   - 内存耗尽时触发红色闪烁警告并播放 "error.wav"  

3. **交互控制**：  
   - 速度调节滑块控制算法执行速度（100ms~2s/步）  
   - 支持拖拽客户方块手动调整顺序（验证贪心策略的最优性）  

---

# 题解清单 (≥4星)  

## 1. Szr__QAQ（★★★★☆）  
**关键亮点**：  
- 结构体封装完整（x,y,id,sum），代码自解释性强  
- 输出时使用独立循环避免修改原数组顺序  
**优化建议**：`d -= sum` 后可合并判断与扣减操作为 `if (d >= sum) { d -= sum; cnt++ }`  

## 2. CleverRaccoon（★★★★☆）  
**关键亮点**：  
- 使用 C++11 的聚合初始化 `a[i] = {aa * x + b * y, i}`  
- 采用 lambda 表达式简化排序函数  
**创新点**：使用 vector 动态记录结果，避免预设数组长度  

## 3. yzm0325（★★★★☆）  
**代码亮点**：  
- 结构体仅保留必要字段（s, id），内存占用更优  
- 输出时使用 `ans` 变量明确记录结果数，逻辑清晰  

---

# 最优思路与技巧提炼  

## 核心技巧  
1. **贪心策略证明**：通过数学归纳法可证，按总内存升序选择必为最优解  
2. **空间换时间**：预处理每个客户的总内存消耗，避免重复计算  
3. **稳定排序**：当总内存相同时按输入顺序处理（题目未明确要求，但各题解均隐含实现）  

## 代码实现要点  
```cpp
// 预处理结构体
struct Client { 
    int sum, id; 
    Client(int x, int y, int _id) : sum(x*a + y*b), id(_id) {} 
};

// 贪心选择循环
sort(clients.begin(), clients.end(), [](auto &a, auto &b){ 
    return a.sum < b.sum; 
});
vector<int> selected;
for (auto &c : clients) {
    if (d < c.sum) break;
    d -= c.sum;
    selected.push_back(c.id);
}
```

---

# 同类型题与算法套路  

## 类似问题模式  
- **部分背包问题**：物品可分割，优先选择单位价值最高者  
- **活动选择问题**：选择不冲突的最大活动数，按结束时间排序  
- **Huffman 编码**：优先合并频率最小的节点  

## 推荐题目  
1. P1090 [NOIP2004 提高组] 合并果子（贪心+优先队列）  
2. P1223 排队接水（贪心排序+累积时间计算）  
3. P5019 [NOIP2018 提高组] 铺设道路（区间贪心）  

---

# 可视化代码片段（JS Canvas）  

```javascript
// 绘制客户方块（伪代码）
function drawClient(ctx, client, x, y, isSelected) {
    const color = `hsl(240, ${client.sum}%, 50%)`; // 内存越高颜色越深
    ctx.fillStyle = color;
    ctx.fillRect(x, y, 32, 32);
    if (isSelected) {
        ctx.strokeStyle = "#FFD700"; // 金色边框
        ctx.lineWidth = 3;
        ctx.strokeRect(x-2, y-2, 36, 36);
    }
    ctx.fillStyle = "#FFF";
    ctx.fillText(client.id, x+8, y+20); // 显示客户编号
}
```

---

# 个人心得摘录  
> "本题看似简单，但实际比赛中有选手因未考虑 `d` 恰好减到零的情况而 WA。调试时构造 `d=0` 的边界测试用例可快速发现问题。" —— CleverRaccoon  
> "使用 `vector` 动态记录结果比预设数组更安全，避免数组越界问题。" —— yzm0325  

---

# 复古游戏化演示方案  

## 8-bit 风格设计  
- **调色板**：  
  - 客户方块：NES 蓝色系（#6B6BFF → #0000AA）  
  - 内存条：FC 绿色（#00FF00）渐变到红色（#FF0000）  
- **音效**：  
  - 选择客户：FamiTracker 风格 8-bit 短音（方波，频率 1000Hz）  
  - 内存耗尽：噪声通道爆破音  

## AI 自动演示逻辑  
```javascript
function autoPlay() {
    const clients = sortedClients.slice();
    let remainingMem = d;
    let interval = setInterval(() => {
        if (clients.length === 0 || remainingMem <= 0) {
            clearInterval(interval);
            return;
        }
        const client = clients.shift();
        if (client.sum <= remainingMem) {
            playSound('select');
            remainingMem -= client.sum;
            addToSelected(client);
        }
        render();
    }, speed);
}
```

---
处理用时：69.91秒