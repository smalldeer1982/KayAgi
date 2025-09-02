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



---

## **唯一算法分类**  
**贪心算法**

---

## **题解思路、算法要点与解决难点**  

### **核心思路**  
1. **分类讨论照片对**：  
   - 每对照片根据 `a1 + b1` 与 `a2 + b2` 的关系分为两类：  
     - **总和大者优先**（`a1 + b1 >= a2 + b2`）：两人争夺这对照片，两张均需参与全局贪心排序。  
     - **总和小者**（`a1 + b1 < a2 + b2`）：进一步判断是否单方面有利，直接累加贡献。  

2. **贪心策略**：  
   - 对总和大者的照片对，将两张的 `a_i + b_i` 存入数组并排序，按奇偶交替分配给 Alice 和 Bonnie。  

### **解决难点**  
- **博弈决策转化**：将两人交替取照片的博弈过程，转化为对 `a + b` 的排序和奇偶分配问题。  
- **贡献计算**：通过预处理累加部分贡献（如 `ans += a1 + a2`），再通过排序后的奇偶项修正差值。  

### **关键变量与数据结构**  
- **数组 `seq`**：存储总和大者的 `a + b` 值，用于全局贪心排序。  
- **奇偶索引**：排序后，偶数索引（从 1 开始）分配给 Alice，奇数索引分配给 Bonnie。  

---

## **题解评分**  
### **≥4星的题解 (3条)**  
1. **Wen_kr（★★★★★）**  
   - **亮点**：  
     - 清晰的分类讨论，将复杂博弈转化为贪心排序。  
     - 代码简洁高效，避免浮点运算（用总和代替 `(a+b)/2`）。  
   - **代码片段**：  
     ```cpp  
     if(a1 + b1 >= a2 + b2) {  
         seq[++cnt] = a1 + b1;  
         seq[++cnt] = a2 + b2;  
         ans += a1 + a2;  
     }  
     ```  

2. **EuphoricStar（★★★★☆）**  
   - **亮点**：  
     - 从单张照片的贪心策略扩展到成对照片。  
     - 明确推导博弈双方的最优选择条件。  
   - **代码片段**：  
     ```cpp  
     if(a1 + b1 < a2 + b2) {  
         if(a1 > b2) ans += a1 - b2;  
         else if(b1 > a2) ans += a2 - b1;  
     }  
     ```  

3. **Yuby（★★★★☆）**  
   - **亮点**：  
     - 将贡献差值拆分为预计算项和排序修正项。  
     - 直接使用整数运算避免精度问题。  
   - **代码片段**：  
     ```cpp  
     sort(a + 1, a + 1 + top);  
     for(int i = 1; i <= top; i += 2) ans -= a[i];  
     ```  

---

## **最优思路与技巧提炼**  
1. **博弈问题转化贪心**：  
   - 将两人博弈的最优策略转化为对 `a + b` 的排序问题，通过奇偶交替分配结果。  
2. **分类讨论简化处理**：  
   - 对无法参与全局排序的照片对，直接计算单边贡献（如 `a1 > b2` 时累加 `a1 - b2`）。  
3. **避免浮点运算**：  
   - 用整数总和代替 `(a + b) / 2`，避免精度损失。  

---

## **同类型题与相似算法套路**  
- **通用解法**：  
  - 博弈问题中，若双方策略可转化为对某指标的排序争夺，优先考虑贪心策略。  
- **类似题目**：  
  - **洛谷 P2123**：皇后游戏（贪心排序推导）。  
  - **洛谷 P1248**：加工生产调度（贪心+奇偶分配）。  

---

## **推荐相似知识点题目**  
1. **P2586** [杀蚂蚁](https://www.luogu.com.cn/problem/P2586)：贪心策略与资源分配。  
2. **P1230** [智力大冲浪](https://www.luogu.com.cn/problem/P1230)：时间窗口贪心。  
3. **P1090** [合并果子](https://www.luogu.com.cn/problem/P1090)：优先队列贪心。  

---

## **个人心得摘录**  
- **Wen_kr**：  
  > 通过将每张照片的贡献拆分为预计算项和排序项，避免了复杂的动态规划，大幅简化了问题。  
- **Yuby**：  
  > 注意题目中的照片对顺序限制，必须取第一张后才能取第二张，这一条件直接影响分类讨论的边界。  

---

## **可视化与算法演示设计**  
### **核心算法动画方案**  
1. **动画流程**：  
   - **步骤1**：展示照片对的分类过程，高亮 `a1 + b1` 和 `a2 + b2` 的比较。  
   - **步骤2**：将总和大者的两张照片加入排序数组，用不同颜色区分（红色为 `a1 + b1`，蓝色为 `a2 + b2`）。  
   - **步骤3**：排序数组后，按奇偶索引分配，偶数项（Alice）用绿色高亮，奇数项（Bonnie）用黄色高亮。  

2. **交互设计**：  
   - **控制面板**：支持暂停/继续、单步执行、调整动画速度。  
   - **音效**：  
     - **分类完成**：播放短促“滴”声。  
     - **分配照片**：根据分配方播放不同音调（Alice：高音，Bonnie：低音）。  

### **复古像素风格实现**  
- **Canvas 绘制**：  
  - 用 8x8 像素块表示照片对，红色块表示 `a1 + b1`，蓝色块表示 `a2 + b2`。  
  - 排序后的数组在网格中横向排列，选中项用闪烁边框标记。  
- **自动演示模式**：  
  - AI 自动执行分类和排序，每步间隔 1 秒，类似“贪吃蛇 AI”路径展示。  

---

## **代码实现（核心片段）**  
```cpp  
#include <cstdio>  
#include <algorithm>  
using namespace std;  

int seq[200050], cnt;  
long long ans;  

int main() {  
    int n, a1, b1, a2, b2;  
    scanf("%d", &n);  
    while(n--) {  
        scanf("%d%d%d%d", &a1, &b1, &a2, &b2);  
        if(a1 + b1 >= a2 + b2) {  
            seq[cnt++] = a1 + b1;  
            seq[cnt++] = a2 + b2;  
            ans += a1 + a2;  
        }  
        else if(a1 > b2) ans += a1 - b2;  
        else if(b1 > a2) ans += a2 - b1;  
    }  
    sort(seq, seq + cnt);  
    for(int i = 0; i < cnt; i += 2) ans -= seq[i];  
    printf("%lld\n", ans);  
    return 0;  
}  
```

---
处理用时：83.81秒