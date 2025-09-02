# 题目信息

# F1 Champions

## 题目描述

Formula One championship consists of series of races called Grand Prix. After every race drivers receive points according to their final position. Only the top 10 drivers receive points in the following order 25, 18, 15, 12, 10, 8, 6, 4, 2, 1. At the conclusion of the championship the driver with most points is the champion. If there is a tie, champion is the one with most wins (i.e. first places). If a tie still exists, it is chosen the one with most second places, and so on, until there are no more place to use for compare.

 Last year another scoring system was proposed but rejected. In it the champion is the one with most wins. If there is tie, champion is the one with most points. If a tie still exists it is proceeded the same way as in the original scoring system, that is comparing number of second, third, forth, and so on, places.

You are given the result of all races during the season and you are to determine the champion according to both scoring systems. It is guaranteed, that both systems will produce unique champion.

## 说明/提示

It is not guaranteed that the same drivers participate in all races. For the championship consider every driver that has participated in at least one race. The total number of drivers during the whole season is not more then $ 50 $ .

## 样例 #1

### 输入

```
3
3
Hamilton
Vettel
Webber
2
Webber
Vettel
2
Hamilton
Vettel
```

### 输出

```
Vettel
Hamilton
```

## 样例 #2

### 输入

```
2
7
Prost
Surtees
Nakajima
Schumacher
Button
DeLaRosa
Buemi
8
Alonso
Prost
NinoFarina
JimClark
DeLaRosa
Nakajima
Patrese
Surtees
```

### 输出

```
Prost
Prost
```

# AI分析结果



### 算法分类
排序、模拟

---

### 题解思路与难点分析
#### 核心算法流程
1. **数据结构设计**  
   使用结构体存储选手信息：名称、总得分、各名次出现次数（数组或map）
   ```cpp
   struct Driver {
       string name;
       int score;
       int rank_count[51]; // rank_count[i]表示获得第i名的次数
   };
   ```

2. **输入处理**  
   - 通过map或哈希表建立选手名字到结构体的映射  
   - 对每场比赛的每个名次：  
     - 若选手不存在则新建条目  
     - 更新该选手的得分（仅前10名有分）  
     - 更新对应名次的计数器（所有名次均记录）

3. **双排序规则实现**  
   **规则一**：总分 > 第1名次数 > 第2名次数 > ...  
   ```cpp
   bool cmp1(Driver a, Driver b) {
       if(a.score != b.score) return a.score > b.score;
       for(int i=1; i<=50; ++i)
           if(a.rank_count[i] != b.rank_count[i])
               return a.rank_count[i] > b.rank_count[i];
   }
   ```
   **规则二**：第1名次数 > 总分 > 第2名次数 > ...  
   ```cpp
   bool cmp2(Driver a, Driver b) {
       if(a.rank_count[1] != b.rank_count[1]) 
           return a.rank_count[1] > b.rank_count[1];
       if(a.score != b.score) return a.score > b.score;
       for(int i=2; i<=50; ++i)
           if(a.rank_count[i] != b.rank_count[i])
               return a.rank_count[i] > b.rank_count[i];
   }
   ```

#### 关键难点
1. **名次处理范围**：所有名次（最多50名）均需记录，不能仅处理前10名  
2. **排序深度**：需要逐个比较名次直到找到差异（类似字典序比较）  
3. **选手去重**：需处理跨比赛出现的新选手

---

### 题解评分（≥4星）
1. **_Give_up_（4.5星）**  
   - 使用map维护选手索引，结构清晰  
   - 明确处理所有名次记录  
   - 提供完整可运行的代码

2. **wmrqwq（4.0星）**  
   - 直接使用数组存储名次次数  
   - 排序逻辑简明，适合快速理解规则  
   - 代码略冗长，但核心逻辑突出

3. **Minecraft万岁（4.0星）**  
   - 使用哈希表优化查找效率  
   - 详细注释解释关键步骤  
   - 代码风格统一易维护

---

### 最优思路提炼
1. **双维度排序**：通过自定义排序函数实现复杂比较规则  
2. **名次全记录**：即使超出得分范围的名次也需统计  
3. **动态选手管理**：使用map或哈希表处理动态选手集合

---

### 相似题目推荐
1. [P1781 总统选举](https://www.luogu.com.cn/problem/P1781)  
   （多维度候选人排序）
2. [P1051 谁拿了最多奖学金](https://www.luogu.com.cn/problem/P1051)  
   （复合条件排序）
3. [P1093 奖学金](https://www.luogu.com.cn/problem/P1093)  
   （多关键字排序）

---

### 可视化设计
#### 算法过程演示
1. **得分更新动画**  
   - 每场比赛后显示选手得分变化  
   - 前10名用不同颜色标注得分值，其他名次显示灰色

2. **排序比较过程**  
   - 高亮当前比较的名次（如比较到第3名时，两选手的第三名次数闪烁）  
   - 逐步展示比较链条：总分 → 第1名次数 → 第2名次数 → ...

3. **复古像素风格**  
   ```javascript
   // 伪代码示例：绘制选手卡片
   function drawDriverCard(ctx, driver, x, y) {
       // 8-bit风格背景
       ctx.fillStyle = "#8B8B83";
       ctx.fillRect(x, y, 120, 30);
       // 显示名称
       ctx.fillStyle = "#FFFFFF";
       ctx.font = "8px Pixel";
       ctx.fillText(driver.name, x+5, y+10);
       // 显示总分
       drawPixelNumber(ctx, driver.score, x+80, y+8);
   }
   ```

#### 交互功能
- **步进控制**：可单步执行比赛输入或排序比较  
- **音效提示**：  
  - 得分更新时播放"哔"声（Web Audio API）  
  - 排序确定冠军时播放胜利音效  
- **双模式对比**：并排显示两种规则下的排序过程

---

### 核心代码实现
```cpp
// 选自 _Give_up_ 题解的关键片段
struct rec {
    string name;
    int sum;
    map<int, int> mp; // 名次计数器
};
vector<rec> drivers;

// 输入处理核心逻辑
for (每场比赛) {
    for (每个名次 j) {
        string name = 当前选手名;
        if (!选手存在) {
            drivers.push_back({name});
            drivers.back().mp[j]++;
            drivers.back().sum += 得分表[j];
        } else {
            更新已存在选手的mp[j]和sum;
        }
    }
}

// 规则一排序
sort(drivers.begin(), drivers.end(), [](rec a, rec b) {
    if (a.sum != b.sum) return a.sum > b.sum;
    for (int i=1; i<=50; ++i)
        if (a.mp[i] != b.mp[i]) 
            return a.mp[i] > b.mp[i];
});

// 规则二排序
sort(drivers.begin(), drivers.end(), [](rec a, rec b) {
    if (a.mp[1] != b.mp[1]) return a.mp[1] > b.mp[1];
    if (a.sum != b.sum) return a.sum > b.sum;
    for (int i=2; i<=50; ++i)
        if (a.mp[i] != b.mp[i])
            return a.mp[i] > b.mp[i];
});
```

---

### 总结与扩展
本题通过多关键字排序模拟真实竞赛规则，训练对复合数据结构的处理能力。关键点在于理解排序规则的优先级，并通过循环比较实现深度字典序排序。类似问题可考虑使用优先队列或自定义排序扩展。

---
处理用时：76.70秒