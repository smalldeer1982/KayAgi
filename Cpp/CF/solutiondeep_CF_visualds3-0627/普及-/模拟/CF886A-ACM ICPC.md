# 题目信息

# ACM ICPC

## 题目描述

In a small but very proud high school it was decided to win ACM ICPC. This goal requires to compose as many teams of three as possible, but since there were only $ 6 $ students who wished to participate, the decision was to build exactly two teams.

After practice competition, participant number $ i $ got a score of $ a_{i} $ . Team score is defined as sum of scores of its participants. High school management is interested if it's possible to build two teams with equal scores. Your task is to answer that question.

## 说明/提示

In the first sample, first team can be composed of $ 1 $ st, $ 2 $ nd and $ 6 $ th participant, second — of $ 3 $ rd, $ 4 $ th and $ 5 $ th: team scores are $ 1+3+1=2+1+2=5 $ .

In the second sample, score of participant number $ 6 $ is too high: his team score will be definitely greater.

## 样例 #1

### 输入

```
1 3 2 1 2 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
1 1 1 1 1 99
```

### 输出

```
NO
```

# AI分析结果



## 算法分类
**暴力枚举**

## 综合分析与结论

### 核心思路与难点
**题目核心**：将6个数字分成两个总和相等的三人组。  
**关键点**：  
1. 总和必须为偶数（否则直接输出NO）
2. 需找到一组三个数，其和为总和的一半  
**难点**：高效枚举所有可能的三人组合，避免重复计算。

### 题解对比与最优思路
- **infinities**：暴力生成所有可能分法，代码冗长但正确。复杂度高，不推荐。  
- **chufuzhe**：枚举所有三元组索引，复杂度O(n³)，存在重复但可行。  
- **Dog_Two**：全排列检查前三个数，复杂度O(n!)，效率较低。  
- **hello2020**：直接枚举组合i<j<k，复杂度O(1)（固定20次循环），最优解。  
- **AmaZingFantasy**：DFS递归搜索三人组合，思路清晰但实现略复杂。

**最优思路**：总和判偶后，枚举所有C(6,3)=20种组合，检查是否存在合法分法。

---

## 题解清单 (≥4星)
1. **hello2020（4星）**  
   - **亮点**：直接三重循环i<j<k，枚举组合数最少，代码简洁高效。  
   - **代码**：  
     ```cpp
     for (int i=1;i<=4;i++)
         for (int j=i+1;j<=5;j++)
             for (int k=j+1;k<=6;k++)
                 if (a[i]+a[j]+a[k]==sum/2) return YES;
     ```

2. **chufuzhe（4星）**  
   - **亮点**：清晰的总和判偶逻辑，暴力枚举所有索引组合。  
   - **代码片段**：  
     ```cpp
     for(int i=0;i<6;i++)
         for(int j=0;j<6;j++)
             for(int k=0;k<6;k++)
                 if(i!=j && j!=k && a[i]+a[j]+a[k]==sum/2)...
     ```

3. **Dog_Two（3星）**  
   - **思路**：全排列后检查前三个数，复杂度较高但代码简洁。  
   - **代码**：  
     ```cpp
     do{
         if(a[1]+a[2]+a[3] == sum/2) return YES;
     } while(next_permutation(a+1,a+7));
     ```

---

## 可视化算法设计
### 核心流程动画
1. **像素风格界面**：  
   - 用6个彩色方块表示学生，上方显示当前选中三人组的总和。  
   - 背景音乐：8-bit风格循环音效。  
2. **执行步骤**：  
   - **红色高亮**：当前枚举的i,j,k三个方块。  
   - **绿色闪烁**：找到合法组合时播放上扬音效，所有方块变绿。  
   - **灰色提示**：总和为奇数时立即灰屏，播放失败音效。  
3. **交互控制**：  
   - 步进按钮：手动触发下一组枚举。  
   - 自动播放：以0.5秒/步速度自动展示枚举过程。

### 复古游戏化实现
- **Canvas绘制**：6x6网格，每个数字用16x16像素块表示。  
- **音效触发**：  
  - 每次枚举播放“滴”声。  
  - 成功时播放《超级玛丽》过关音效。  
- **积分系统**：每完成10组枚举未找到解，速度加快一档。

---

## 相似题目推荐
1. **P1036 选数**：枚举k数之和为素数。  
2. **P1618 三连击**：暴力枚举三位数组合。  
3. **P1149 火柴棒等式**：组合数字满足特定等式。

---
处理用时：82.27秒