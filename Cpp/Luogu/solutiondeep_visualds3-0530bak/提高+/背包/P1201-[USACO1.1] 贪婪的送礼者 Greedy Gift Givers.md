# 题目信息

# [USACO1.1] 贪婪的送礼者 Greedy Gift Givers

## 题目描述

对于一群 $n$ 个要互送礼物的朋友，GY 要确定每个人送出的钱比收到的多多少。在这一个问题中，每个人都准备了一些钱来送礼物，而这些钱将会被平均分给那些将收到他的礼物的人。  

然而，在任何一群朋友中，有些人将送出较多的礼物(可能是因为有较多的朋友)，有些人有准备了较多的钱。  

给出一群朋友，没有人的名字会长于 $14$ 字符，给出每个人将花在送礼上的钱，和将收到他的礼物的人的列表，请确定每个人收到的比送出的钱多的数目。

## 说明/提示

【数据范围】  
$1\le n \le 10$。

题目翻译来自NOCOW。

USACO Training Section 1.1

## 样例 #1

### 输入

```
5
dave
laura
owen
vick
amr
dave
200 3
laura
owen
vick
owen
500 1
dave
amr
150 2
vick
owen
laura
0 2
amr
vick
vick
0 0
```

### 输出

```
dave 302
laura 66
owen -359
vick 141
amr -150
```

# AI分析结果



### 算法分类
模拟

---

### 题解思路与核心难点
**核心逻辑**：
1. **金额计算模型**：送礼者总金额 = 原始金额 - 平均分配金额 × 人数 + 余数
2. **数据结构**：使用 `map<string, int>` 实现名字到金额的快速映射
3. **边界处理**：当送礼人数为0时跳过除法操作，避免除零异常

**关键难点对比**：
1. **名字匹配**：线性查找（O(n)） vs map映射（O(logn)）
2. **余数处理**：部分题解错误地将总金额全部扣除而非扣除可分配部分
3. **顺序输出**：需按输入顺序输出结果，故需额外维护名字数组

**精炼结论**：
最优解法使用 map 管理金额，时间复杂度 O(n²)，核心流程为：
1. 读取所有名字并初始化金额为0
2. 处理每个送礼者：
   - 扣除总分配金额（平均金额 × 人数）
   - 将余数加回送礼者账户
3. 按初始顺序输出结果

---

### 高星题解（≥4⭐）
1. **BlueArc（5⭐）**
   - **亮点**：使用 map 实现名字映射，代码简洁清晰
   ```cpp
   map<string,int> cnt;
   cnt[s] -= num*p;  // 核心逻辑：扣除可分配金额
   cnt[person] += num;
   ```

2. **w1049（4⭐）**
   - **亮点**：结合 vector 维护输入顺序，输出时保证顺序正确
   ```cpp
   vector<string> id;  // 存储初始顺序
   m[tmp] += money/num;  // 分配金额
   ```

3. **f112358（4⭐）**
   - **亮点**：双 map 分别记录收支，思路直观
   ```cpp
   map <string,int> receive, give;
   receive[b] += money/num;
   give[a] += (money/num)*num;
   ```

---

### 最优思路提炼
**关键技巧**：
1. **map 代替线性查找**：将名字映射到金额，避免 O(n) 查找
2. **余数计算公式**：总扣除金额 = 平均金额 × 人数 → `money -= (money/num)*num`
3. **边界处理**：在计算平均金额前检查 `num != 0`

**通用模板**：
```cpp
map<string, int> balance;
for (送礼者) {
    int total = 送礼总金额;
    int people = 收礼人数;
    balance[送礼者] -= total - (total % people); // 扣除可分配部分
    for (收礼者) balance[收礼者] += total / people;
}
```

---

### 类似题目推荐
1. [P1305 新二叉树](https://www.luogu.com.cn/problem/P1305)（字符串树结构）
2. [P1152 欢乐的跳](https://www.luogu.com.cn/problem/P1152)（集合与差值处理）
3. [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)（字符频率统计）

---

### 可视化设计
**复古像素化演示方案**：
```html
<canvas id="pixel-canvas"></canvas>
<script>
// 初始化参数
const names = ["dave", "laura", "owen", "vick", "amr"];
const balances = new Map(names.map(name => [name, 0]));

// 绘制函数
function draw() {
    ctx.fillStyle = "#2D2D2D"; // 复古深灰背景
    names.forEach((name, i) => {
        drawPixelText(name, 10, 30*i + 20); // 8-bit风格文字
        drawBalanceBar(balances.get(name), 100, 30*i + 20); // 动态柱状图
    });
}

// 音效触发
function playSound(type) {
    const sfx = {
        deduct: new Audio('data:audio/wav;base64,UklGRl...'), // 扣除音效
        receive: new Audio('data:audio/wav;base64,UklGRl...') // 收到音效
    };
    sfx[type].play();
}
</script>
```

**交互特性**：
1. **步进控制**：空格键单步执行送礼过程
2. **高亮变化**：当前操作的送礼者名字显示为红色，金额变动时柱状图闪烁
3. **音效反馈**：每次金额变动伴随 8-bit 音效（扣除为低音，收到为高音）

---

### 个人心得摘录
> "被除数为0的情况让我WA了三次，最后发现要在计算平均金额前加 `if (num != 0)`，血的教训！" —— Aoki_灏

> "原来 map 的 `operator[]` 会自动插入不存在的键，这特性让代码简洁但容易踩坑" —— BlueArc

---

### 核心算法动画演示
![算法流程图](https://i.imgur.com/ZjJ9g8L.gif)
1. **初始状态**：所有人金额为0，名字按输入顺序排列
2. **送礼阶段**：
   - 送礼者名字**红色高亮**，总金额柱状图缩短
   - 每个收礼者名字**绿色闪烁**，金额柱状图增长
3. **余数返还**：送礼者金额柱状图部分恢复（黄色部分）

**颜色标记规则**：
- 红色：当前操作的送礼者
- 绿色：正在接收金额的收礼者
- 黄色：返还的余数金额

---
处理用时：65.84秒