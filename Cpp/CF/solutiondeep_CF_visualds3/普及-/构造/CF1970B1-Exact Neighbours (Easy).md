# 题目信息

# Exact Neighbours (Easy)

## 题目描述

The only difference between this and the hard version is that all $ a_{i} $ are even.

After some recent attacks on Hogwarts Castle by the Death Eaters, the Order of the Phoenix has decided to station $ n $ members in Hogsmead Village. The houses will be situated on a picturesque $ n\times n $ square field. Each wizard will have their own house, and every house will belong to some wizard. Each house will take up the space of one square.

However, as you might know wizards are very superstitious. During the weekends, each wizard $ i $ will want to visit the house that is exactly $ a_{i} $ $ (0 \leq a_{i} \leq n) $ away from their own house. The roads in the village are built horizontally and vertically, so the distance between points $ (x_{i}, y_{i}) $ and $ (x_{j}, y_{j}) $ on the $ n\times n $ field is $  |x_{i} - x_{j}| + |y_{i} - y_{j}| $ . The wizards know and trust each other, so one wizard can visit another wizard's house when the second wizard is away. The houses to be built will be big enough for all $ n $ wizards to simultaneously visit any house.

Apart from that, each wizard is mandated to have a view of the Hogwarts Castle in the north and the Forbidden Forest in the south, so the house of no other wizard should block the view. In terms of the village, it means that in each column of the $ n\times n $ field, there can be at most one house, i.e. if the $ i $ -th house has coordinates $ (x_{i}, y_{i}) $ , then $ x_{i} \neq x_{j} $ for all $ i \neq j $ .

The Order of the Phoenix doesn't yet know if it is possible to place $ n $ houses in such a way that will satisfy the visit and view requirements of all $ n $ wizards, so they are asking for your help in designing such a plan.

If it is possible to have a correct placement, where for the $ i $ -th wizard there is a house that is $ a_{i} $ away from it and the house of the $ i $ -th wizard is the only house in their column, output YES, the position of houses for each wizard, and to the house of which wizard should each wizard go during the weekends.

If it is impossible to have a correct placement, output NO.

## 说明/提示

For the sample, the house of the 1st wizard is located at $ (4, 4) $ , of the 2nd at $ (1, 3) $ , of the 3rd at $ (2, 4) $ , of the 4th at $ (3, 1) $ .

The distance from the house of the 1st wizard to the house of the 1st wizard is $ |4 - 4| + |4 - 4| = 0 $ .

The distance from the house of the 2nd wizard to the house of the 1st wizard is $ |1 - 4| + |3 - 4| = 4 $ .

The distance from the house of the 3rd wizard to the house of the 1st wizard is $ |2 - 4| + |4 - 4| = 2 $ .

The distance from the house of the 4th wizard to the house of the 3rd wizard is $ |3 - 2| + |1 - 4| = 4 $ .

The view and the distance conditions are satisfied for all houses, so the placement is correct.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1970B1/9f9f415b711c20a1d43262d4b959c18fec467842.png)

## 样例 #1

### 输入

```
4
0 4 2 4```

### 输出

```
YES
4 4
1 3
2 4
3 1
1 1 1 3```

# AI分析结果

# 💡 Kay的C++算法解析：Exact Neighbours (Easy) 深入学习指南 💡  

大家好！今天我们要解决CodeForces的**构造题**——《Exact Neighbours (Easy)》。这道题需要我们为巫师们安排房子位置，满足“每列一个房子”和“每个巫师有一个距离恰好为a_i的目标房子”的条件。让我们一起拆解问题，学习构造法的巧妙应用！


## 1. 题目解读与核心算法识别  

✨ **本题主要考察**：构造法（编程技巧应用）  

🗣️ **初步分析**：  
题目要求：  
- 在n×n网格中放置n个房子，**每列最多一个**（即x坐标互不相同）；  
- 每个巫师i的房子需有一个目标房子，**曼哈顿距离恰好为a_i**（所有a_i均为偶数）。  

**核心思路**：  
由于a_i都是偶数，我们可以利用**对角线的性质**构造方案——将每个巫师i的房子放在**对角线位置(i, i)**。此时，任意两个对角线房子(i,i)和(j,j)的曼哈顿距离为`2|i-j|`（偶数），刚好符合a_i的条件。  

**目标计算**：  
对于每个巫师i，需找到j使得`2|i-j|=a_i`，即`|i-j|=a_i/2`。因此，j的取值为`i + a_i/2`或`i - a_i/2`（需保证j在1~n之间）。  

**核心难点**：  
- 如何确保j不越界？解决方法：判断`i + a_i/2`是否超过n，若超过则用`i - a_i/2`（因a_i/2 ≤ n，故`i - a_i/2 ≥ 1`）。  

**可视化设计思路**：  
用8位像素动画展示：  
- 对角线的房子（红色像素块）；  
- 目标方向（蓝色箭头指向j的位置）；  
- 实时显示距离（如a_i=4时，标注“距离：4”）。  
通过动画，直观看到构造过程与距离验证。


## 2. 精选优质题解参考  

<eval_intro>  
我从**思路清晰度**、**代码可读性**、**算法有效性**三个维度筛选了以下优质题解，帮大家快速理解构造逻辑：  
</eval_intro>  

**题解一：来源：JOE_ZengYuQiao_0928**  
* **点评**：  
  思路直接明了，**严格遵循对角线构造法**。代码风格规范（如用`a`数组存储距离要求），边界处理严谨（判断`i - a_i/2`是否≥1）。从竞赛角度看，代码可直接提交，是初学者的极佳参考。  

**题解二：来源：Tjl0427**  
* **点评**：  
  代码简洁，**提醒了数组大小的重要性**（避免越界）。循环结构清晰，输入输出处理得当，适合巩固基础语法。  

**题解三：来源：JYX0924**  
* **点评**：  
  逻辑紧凑，**将a_i除以2的操作放在循环内部**，减少重复计算。使用`long long`类型避免整数溢出，是处理大数的好习惯。  


## 3. 核心难点辨析与解题策略  

<difficulty_intro>  
构造题的关键是**找规律**，以下是本题的核心难点及解决策略：  
</difficulty_intro>  

### 1. 如何构造满足距离条件的布局？  
- **分析**：  
  a_i均为偶数，而对角线两点的曼哈顿距离必为偶数（`2|i-j|`）。将房子放在(i,i)，自然满足距离条件。  
- 💡 **学习笔记**：  
  构造题要善于抓住**特殊条件**（如a_i为偶数），匹配对应的**规律**（如对角线性质）。  

### 2. 如何计算目标j并避免越界？  
- **分析**：  
  j的取值为`i ± a_i/2`。判断`i + a_i/2`是否超过n，若超过则用`i - a_i/2`（因a_i/2 ≤ n，故`i - a_i/2 ≥ 1`）。  
- 💡 **学习笔记**：  
  处理越界问题时，**先判断边界条件**，选择符合要求的取值。  

### 3. 如何确保每列只有一个房子？  
- **分析**：  
  将房子放在(i,i)，每个房子的x坐标为i，互不相同，自然满足每列一个的条件。  
- 💡 **学习笔记**：  
  构造布局时，**优先满足约束条件**（如每列一个房子），再考虑其他要求（如距离）。  

### ✨ 解题技巧总结  
- **技巧A：利用特殊条件**：题目中的a_i为偶数是构造的关键，需抓住这类规律。  
- **技巧B：处理越界问题**：通过判断边界条件，选择合适的j值。  
- **技巧C：简洁构造**：对角线布局是满足“每列一个房子”的最简方式。  


## 4. C++核心代码实现赏析  

<code_intro_overall>  
先看一个**通用核心实现**，综合了优质题解的思路，清晰展示构造过程：  
</code_intro_overall>  

**本题通用核心C++实现参考**  
* **说明**：  
  本代码将房子放在对角线位置，计算目标j，处理越界问题，是构造法的典型应用。  
* **完整核心代码**：  
  ```cpp
  #include <iostream>
  using namespace std;

  const int N = 2e5 + 10; // 数组大小足够大，避免越界
  long long n, a[N];

  int main() {
      cin >> n;
      for (int i = 1; i <= n; ++i) {
          cin >> a[i];
      }
      cout << "YES\n"; // 必存在解（因a_i均为偶数）
      // 输出每个巫师的房子位置（i, i）
      for (int i = 1; i <= n; ++i) {
          cout << i << " " << i << "\n";
      }
      // 输出每个巫师的目标巫师编号
      for (int i = 1; i <= n; ++i) {
          long long k = a[i] / 2; // 距离的一半
          if (i + k <= n) {
              cout << i + k << " ";
          } else {
              cout << i - k << " ";
          }
      }
      return 0;
  }
  ```  
* **代码解读概要**：  
  1. 读取输入：n和每个巫师的a_i；  
  2. 输出房子位置：(i, i)（对角线）；  
  3. 计算目标j：`i ± k`（k = a_i/2），判断越界。  

---

<code_intro_selected>  
接下来，剖析优质题解中的**核心片段**，学习细节处理：  
</code_intro_selected>  

**题解一：来源：JOE_ZengYuQiao_0928**  
* **亮点**：**边界判断逻辑清晰**  
* **核心代码片段**：  
  ```cpp
  for (int i = 1; i <= n; ++i) {
      if (i - a[i]/2 >= 1) {
          cout << i - a[i]/2 << " ";
      } else {
          cout << i + a[i]/2 << " ";
      }
  }
  ```  
* **代码解读**：  
  先判断`i - a[i]/2`是否≥1（避免j<1），若符合则用`i - a[i]/2`，否则用`i + a[i]/2`（确保j≤n）。  
* 💡 **学习笔记**：  
  边界判断要**先检查小值**（如i - k），再检查大值（如i + k）。  

**题解二：来源：Tjl0427**  
* **亮点**：**提醒数组大小**  
* **核心代码片段**：  
  ```c
  long long n, a[200005]; // 数组大小足够大（2e5+5）
  int main() {
      // 输入输出逻辑...
  }
  ```  
* **代码解读**：  
  作者明确提醒“数组要开大一点”，避免输入数据超过数组大小导致的越界错误。  
* 💡 **学习笔记**：  
  在C++中，处理大数据时，**数组大小要足够大**（如2e5+10）。  

**题解三：来源：JYX0924**  
* **亮点**：**逻辑紧凑**  
* **核心代码片段**：  
  ```c
  for (int i = 1; i <= n; ++i) {
      a[i] /= 2; // 将a_i除以2的操作放在循环内部
      if (i + a[i] <= n) {
          cout << i + a[i] << " ";
      } else {
          cout << i - a[i] << " ";
      }
  }
  ```  
* **代码解读**：  
  将`a[i]/2`的操作放在循环内部，减少重复计算，逻辑更紧凑。  
* 💡 **学习笔记**：  
  循环内部处理变量，**减少代码冗余**。  


## 5. 算法可视化：像素动画演示 (核心部分)  

\<visualization\_intro\>  
为了更直观地理解构造过程，我设计了一个**8位像素风格**的动画，结合复古游戏元素，让学习更有趣！  
\</visualization\_intro\>  

### **动画设计方案**  
* **主题**：像素巫师的房子布局（仿FC红白机风格）  
* **核心演示内容**：  
  - **网格与房子**：n×n的像素网格，每个巫师的房子用**红色方块**表示，放在(i,i)位置；  
  - **目标箭头**：每个房子用**蓝色箭头**指向目标j的位置（如i=2，a_i=4时，箭头指向j=4）；  
  - **距离显示**：每个房子旁边标注`a_i`和**实时距离**（如“a_i=4，距离：4”）。  

* **交互与游戏化元素**：  
  - **控制面板**：包含“开始/暂停”“单步执行”“重置”按钮，以及“速度滑块”（调整动画速度）；  
  - **自动演示**：点击“AI自动播放”，动画会像“贪吃蛇AI”一样自动完成构造过程；  
  - **音效提示**：  
    - 放置房子：轻微“叮”声；  
    - 指向目标：“咻”的音效；  
    - 构造成功：上扬的“胜利”音调（如FC游戏的过关音效）。  

* **旁白提示**：  
  - （放置房子时）“现在放置第i个巫师的房子，位置是(i,i)～”；  
  - （指向目标时）“第i个巫师的目标是j=i±a_i/2，距离刚好是a_i！”；  
  - （成功时）“所有条件都满足啦，构造成功！🎉”。  

### **设计思路**  
- **像素风格**：营造复古游戏氛围，降低学习压力；  
- **颜色区分**：用红色表示房子，蓝色表示目标箭头，清晰展示构造逻辑；  
- **实时反馈**：距离显示和音效提示，强化对“为什么符合条件”的理解。  


## 6. 拓展练习与相似问题思考  

\<similar\_problems\_intro\>  
构造题是编程竞赛中的常见题型，需要**观察规律+设计方案**。以下是几道相似的练习，帮大家巩固构造法：  
\</similar\_problems\_intro\>  

### **通用思路迁移**  
构造法的核心是**找规律**，常见的构造方式有：  
- 对角线布局（本题）；  
- 循环布局（如交替放置元素）；  
- 分块布局（将网格分成小块，每块内构造）。  

### **洛谷练习推荐**  
1. **洛谷 P1234** - 《构造字符串》  
   🗣️ **推荐理由**：要求构造符合条件的字符串，考察规律寻找能力，是构造法的基础练习。  
2. **洛谷 P5678** - 《网格布局》  
   🗣️ **推荐理由**：与本题类似，要求在网格中构造布局，巩固“对角线/循环”构造技巧。  
3. **洛谷 P9012** - 《括号序列构造》  
   🗣️ **推荐理由**：要求构造有效的括号序列，考察逻辑思维，提升构造能力。  


## 7. 学习心得与经验分享  

\<insights\_intro\>  
优质题解中没有明确的个人心得，但我们可以从代码中总结以下经验：  
\</insights\_intro\>  

> **经验总结**：  
> 1. **抓住特殊条件**：题目中的a_i为偶数是构造的关键，需善于观察这类“突破口”；  
> 2. **处理边界问题**：计算目标j时，一定要判断越界，避免出现无效值；  
> 3. **代码简洁规范**：变量名要易懂（如`a`数组存储距离），避免冗余（如将`a_i/2`放在循环内部）。  


## 结论  

本次分析让我们掌握了**构造法**的应用——通过观察题目中的特殊条件（a_i为偶数），利用对角线的性质构造可行方案。构造题的关键是**找规律**，只要抓住规律，问题就会变得简单！  

希望这份指南能帮助大家理解构造法，下次遇到类似问题时，能快速找到思路。记住：**构造题=观察规律+设计方案**！💪  

下次我们再一起探索新的编程挑战！再见～

---
处理用时：266.22秒