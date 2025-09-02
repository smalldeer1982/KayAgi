# 题目信息

# Family Photos

## 题目描述

Alice and Bonnie are sisters, but they don't like each other very much. So when some old family photos were found in the attic, they started to argue about who should receive which photos. In the end, they decided that they would take turns picking photos. Alice goes first.

There are $ n $ stacks of photos. Each stack contains exactly two photos. In each turn, a player may take only a photo from the top of one of the stacks.

Each photo is described by two non-negative integers $ a $ and $ b $ , indicating that it is worth $ a $ units of happiness to Alice and $ b $ units of happiness to Bonnie. Values of $ a $ and $ b $ might differ for different photos.

It's allowed to pass instead of taking a photo. The game ends when all photos are taken or both players pass consecutively.

The players don't act to maximize their own happiness. Instead, each player acts to maximize the amount by which her happiness exceeds her sister's. Assuming both players play optimal, find the difference between Alice's and Bonnie's happiness. That is, if there's a perfectly-played game such that Alice has $ x $ happiness and Bonnie has $ y $ happiness at the end, you should print $ x-y $ .

## 样例 #1

### 输入

```
2
12 3 4 7
1 15 9 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
5 4 8 8
4 12 14 0
```

### 输出

```
4
```

## 样例 #3

### 输入

```
1
0 10 0 10
```

### 输出

```
-10
```

# AI分析结果



### 综合分析与结论

**核心思路**：基于贪心策略，将照片对分为三类处理：(1) 可争夺的优质对（按 a+b 总和排序交替选取）; (2) 单方优势对（直接计算贡献）; (3) 无效对（直接舍弃）。通过排序和奇偶交替选择实现最优决策。

**贪心策略证明**：当 a1+b1 ≥ a2+b2 时，两人争夺首张照片；排序后交替选择等价于动态规划最优解。其他情况通过数学推导证明单方优势或双弃最优性。

**可视化设计**：  
- 采用 8-bit 像素风格，用不同颜色区分三类照片对（红-争夺/蓝-单方/灰-无效）。  
- 动画展示排序过程（像素块升降排列），奇偶交替选取时高亮当前决策照片。  
- 音效：选择时播放不同音调（争夺对用高音，单方优势用中音，无效对无声），错误操作触发警示音。

---

### 题解清单（≥4星）

| 题解作者 | 星级 | 核心亮点 |
|---------|------|---------|
| Wen_kr  | ⭐⭐⭐⭐⭐ | 分类清晰，代码简洁，数学推导严谨 |
| Yuby    | ⭐⭐⭐⭐  | 实现思路与数学分析高度统一，变量命名规范 |
| XL4453  | ⭐⭐⭐⭐  | 博弈视角分析透彻，贡献转化策略直观 |

---

### 代码实现核心逻辑

```cpp
// 核心贪心处理逻辑
sort(seq + 1, seq + 1 + cnt);
for(int i = 1; i <= cnt; i += 2) 
    ans -= seq[i];
```

**实现思想**：  
1. 预处理时将优质对的 a1+b1 和 a2+b2 存入数组  
2. 排序后奇索引项为 Bonnie 必选项，累计时减去其总和  
3. 单方优势对直接计算贡献  

---

### 可视化设计要点

**像素动画实现**：
```javascript
// Canvas 绘制示例
function drawPhotoPair(type, value) {
    ctx.fillStyle = type === 'compete' ? '#FF3355' : '#33AAFF';
    ctx.fillRect(x, y, 32, 32); // 绘制32x32像素块
    ctx.fillText(value, x+8, y+20); // 显示a+b值
}
```

**AI自动演示逻辑**：
```javascript
function autoPlay() {
    let turn = 0; // 0:Alice, 1:Bonnie
    const sorted = seq.sort((a,b) => b-a); // 降序排列
    sorted.forEach((val, idx) => {
        if(idx % 2 === turn) {
            selectPhoto(val); // 高亮当前选择
            playSound('select'); // 触发音效
        }
    });
}
```

**游戏化规则**：
- 连击奖励：连续正确选择3次触发2x积分  
- 错误惩罚：错误操作扣除10%积分  
- 成就系统：首次完成所有优质对选择解锁"博弈大师"徽章  

---

### 同类型题目推荐

1. **P2123 皇后游戏**（贪心排序策略比较）  
2. **P1248 加工生产调度**（Johnson法则应用）  
3. **P1090 合并果子**（优先队列贪心）

---

### 个人心得摘录

> "调试时发现排序顺序影响奇偶索引的归属，必须统一升序/降序才能保证交替选择正确性" —— Wen_kr  
> "贡献转化策略的数学证明是关键，否则无法确定直接加减的合法性" —— Yuby

---

### 知识拓展

**贪心选择证明模板**：  
1. 定义局部最优选择标准（如 a+b 最大化）  
2. 证明该选择不影响后续最优性（无后效性）  
3. 数学归纳法证明全局最优  

**博弈论启示**：将双人博弈转化为单人决策序列，通过逆向归纳法确定最优策略。

---
处理用时：55.08秒