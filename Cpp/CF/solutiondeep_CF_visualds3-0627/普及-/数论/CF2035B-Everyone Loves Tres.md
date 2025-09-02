# 题目信息

# Everyone Loves Tres

## 题目描述

There are 3 heroes and 3 villains, so 6 people in total.



Given a positive integer $ n $ . Find the smallest integer whose decimal representation has length $ n $ and consists only of $ 3 $ s and $ 6 $ s such that it is divisible by both $ 33 $ and $ 66 $ . If no such integer exists, print $ -1 $ .

## 说明/提示

For $ n=1 $ , no such integer exists as neither $ 3 $ nor $ 6 $ is divisible by $ 33 $ .

For $ n=2 $ , $ 66 $ consists only of $ 6 $ s and it is divisible by both $ 33 $ and $ 66 $ .

For $ n=3 $ , no such integer exists. Only $ 363 $ is divisible by $ 33 $ , but it is not divisible by $ 66 $ .

For $ n=4 $ , $ 3366 $ and $ 6666 $ are divisible by both $ 33 $ and $ 66 $ , and $ 3366 $ is the smallest.

## 样例 #1

### 输入

```
6
1
2
3
4
5
7```

### 输出

```
-1
66
-1
3366
36366
3336366```

# AI分析结果



**唯一算法分类**  
数学构造

---

**综合分析与结论**  
该题需构造满足条件的n位数，核心在于数学分析：  
1. **被66整除**等价于同时满足被2、3、11整除。  
   - 末位必为6（被2整除）。  
   - 所有位和为3的倍数（由3和6组成，自动满足）。  
   - 奇数位和与偶数位和的差为0或11的倍数（被11整除）。  

2. **构造方法**：  
   - **偶数n**：前n-2位填3，末两位填66（奇偶差为0）。  
   - **奇数n（≥5）**：前n-5位填3，末五位填36366（奇偶差为0）。  
   - 特判n=1或3时无解。  

**可视化设计要点**  
- **像素动画**：用Canvas绘制数字生成过程，分两部分显示：  
  - **前半部分**：动态填充3（绿色像素块）。  
  - **后半模式**：高亮显示66（红色块）或36366（红蓝交替）。  
- **音效触发**：填充完成时播放成功音效，无解时播放失败音效。  
- **交互控制**：支持调整n值并单步观察构造步骤。  

---

**题解清单（≥4星）**  
1. **Yxy7952（5星）**  
   - **亮点**：数学推导清晰，代码简洁高效。通过分解质因数，结合奇偶位差构造最优解。  
   - **代码**：直接按奇偶生成结果，时间复杂度O(n)。  

2. **Sakura_Emilia（4星）**  
   - **亮点**：结论明确，代码直观。末尾模式选择合理，符合最小字典序。  

3. **Arefa（4星）**  
   - **亮点**：将问题转换为由1和2构造数，再映射回3和6，思路独特。  

---

**最优思路与技巧**  
- **数学构造**：通过分析质因数与数位性质，直接生成最小解。  
- **奇偶分类**：偶数末补66，奇数补36366，确保奇偶和差为0。  
- **字典序最小**：高位尽可能填3，保证数值最小。  

**代码片段**  
```cpp
// Yxy7952的构造代码
if (n % 2) {
    for (int i = 5; i <= n; i++) cout << "3";
    cout << "6366\n";
} else {
    for (int i = 3; i <= n; i++) cout << "3";
    cout << "66\n";
}
```

---

**相似题目推荐**  
1. [CF1665A - GCD vs LCM](https://codeforces.com/problemset/problem/1665/A)  
2. [洛谷P1129 - 产生数](https://www.luogu.com.cn/problem/P1129)  
3. [CF514B - Han Solo and Lazer Gun](https://codeforces.com/problemset/problem/514/B)  

---

**个人心得摘录**  
- **调试关键**：验证奇偶位差时，需注意数位顺序（从左到右编号，而非从右）。  
- **构造陷阱**：n=5时，直接补36366而非6366，避免奇偶差无法归零。  

---

**可视化与像素动画实现**  
```javascript
// 示例：构造过程动画（伪代码）
function drawNumber(n) {
  let result = [];
  if (n % 2 === 0) {
    fillGreenBlocks(n - 2); // 前n-2位绿色3
    fillRedBlocks(2);       // 末两位红色66
  } else {
    fillGreenBlocks(n - 5); // 前n-5位绿色3
    fillPattern('36366');   // 末五位红蓝交替
  }
  playSuccessSound();
}
```  
- **颜色方案**：3→绿色（#00FF00），6→红色（#FF0000），模式部分交替显示。  
- **交互功能**：滑块调整n值，点击播放动画，实时显示构造结果。  

---

**复古游戏化效果**  
- **8位音效**：使用Web Audio生成芯片音乐，填充时播放短促“哔”声，成功时播放胜利旋律。  
- **积分系统**：正确构造一次得10分，快速连续正确触发连击加分。  
- **自动演示模式**：AI自动遍历n值，动态展示构造逻辑，类似“贪吃蛇”自动寻路。

---
处理用时：112.29秒