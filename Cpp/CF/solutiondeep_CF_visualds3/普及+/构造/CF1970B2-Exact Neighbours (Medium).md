# 题目信息

# Exact Neighbours (Medium)

## 题目描述

The only difference between this and the hard version is that $ a_{1} = 0 $ .

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

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1970B2/9f9f415b711c20a1d43262d4b959c18fec467842.png)

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

## 样例 #2

### 输入

```
4
0 1 3 1```

### 输出

```
YES
1 1
2 1
4 1
3 1
1 1 1 3```

# AI分析结果

# 💡 Kay的C++算法解析：Exact Neighbours (Medium) 深入学习指南 💡

<introduction>
  今天我们来一起分析「Exact Neighbours (Medium)」这道C++编程题。这道题需要我们在网格中巧妙放置房子，满足每列一个且每个房子到目标房子的距离恰好为给定值。本指南将帮助大家梳理构造思路，理解核心技巧，并掌握解题的关键步骤！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：编程技巧应用（构造法）

🗣️ **初步分析**：
解决这道题的关键是**构造法**——就像搭积木一样，从第一个房子（已知条件`a₁=0`）开始，一步步推导后面每个房子的位置，确保每一步都满足距离要求。构造法的核心思想是“用已知推未知”，通过合理利用题目给出的约束（如每列一个房子、`a₁=0`），逐步确定每个元素的状态。  
在本题中，构造法的应用逻辑是：  
- 第一个房子必须放在**(1,1)**（因为`a₁=0`，只能自己作为目标），作为后续所有房子的“基准点”；  
- 对于第`i`个房子（`i≥2`），根据`a_i`与`i`的大小关系，分两种情况构造位置：  
  1. 若`a_i ≥ i`：目标只能是第一个房子（因为前面的房子不足以满足距离），行号计算为`a_i - i + 2`（保证曼哈顿距离为`a_i`）；  
  2. 若`a_i < i`：目标是前面第`i - a_i`个房子（直接取其行号，保证距离为`a_i`）。  
核心难点是**如何正确分情况计算行号**，解决方案是通过“曼哈顿距离公式”反向推导（列号固定为`i`，只需调整行号）。  
可视化设计思路：用8位像素风格展示网格，第一个房子用红色标记，后续房子用黄色逐步出现，目标房子用蓝色高亮，同时显示距离计算过程（如`a_i = |i - 1| + |行号 - 1|`）。动画中加入“放置房子”的叮声和“目标选中”的滴声，增强互动感。


## 2. 精选优质题解参考

<eval_intro>
为了更好地理解构造过程，我从思路清晰度、代码可读性、算法有效性等方面筛选了以下3份优质题解（均≥4星）：
</eval_intro>

**题解一：来源：0tAp**  
* **点评**：这份题解的思路非常直白，直接围绕`a₁=0`的基准点展开，分情况讨论`a_i`与`i`的关系，逻辑推导过程清晰易懂。代码风格规范（用`rep`循环、变量名`x`/`y`/`ans`含义明确），特别是处理`a_i=0`的边界条件时非常严谨（直接将房子放在当前列的第1行）。算法上，通过“列号固定为`i`”的技巧，完美满足“每列一个房子”的约束，实践中可以直接用于竞赛，是构造法的典型示例。

**题解二：来源：FFTotoro**  
* **点评**：此题解的亮点是**下标从0开始**的处理（符合编程习惯），用`r`数组存储行号、`l`数组存储目标索引，变量命名简洁。虽然下标转换需要注意（如输出时`i+1`），但逻辑与题解一一致，且代码更紧凑（用`ios::sync_with_stdio(false)`加速输入）。对于熟悉0-based索引的学习者来说，这份题解更容易理解。

**题解三：来源：I_am_Tangser**  
* **点评**：这份题解的变量名最贴近问题描述（`b`数组存行号、`c`数组存目标），步骤明确（先输出第一个房子，再循环处理后面的）。作者特别提到“将左上角转为左下角”的细节，虽然题目中网格是左下角为(1,1)，但代码中直接用(1,1)作为起点，不影响结果，反而简化了逻辑。对于新手来说，这种“直来直去”的代码风格非常友好。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
在构造过程中，我们通常会遇到以下3个核心难点。结合优质题解的共性，我为大家提炼了对应的解决策略：
</difficulty_intro>

1. **难点1：如何利用`a₁=0`的条件构造基准？**  
   * **分析**：`a₁=0`意味着第一个房子只能自己作为目标，因此必须将其放在一个固定位置（如(1,1)），作为后续所有房子的“参考点”。优质题解都选择了(1,1)，因为这是最容易计算后续行号的位置（列号固定为1，行号固定为1）。  
   * 💡 **学习笔记**：固定基准点是构造法的关键，它能简化后续所有计算。

2. **难点2：如何分情况计算行号？**  
   * **分析**：对于第`i`个房子，列号固定为`i`（满足每列一个），只需调整行号。根据曼哈顿距离公式`a_i = |i - 目标列号| + |行号 - 目标行号|`：  
     - 若目标是第一个房子（列号1，行号1），则`a_i = (i-1) + (行号-1)`，解得行号`= a_i - (i-1) + 1 = a_i -i +2`（要求`a_i ≥i-1`，即`a_i ≥i`时成立）；  
     - 若目标是前面第`k`个房子（`k = i - a_i`，列号`k`，行号`b[k]`），则`a_i = (i -k) + |行号 - b[k]|`，解得行号`= b[k]`（因为`i -k = a_i`，所以第二项为0）。  
   * 💡 **学习笔记**：分情况讨论是解决构造问题的常用技巧，关键是找到“不变量”（如列号固定为`i`）。

3. **难点3：如何确保每列一个房子？**  
   * **分析**：题目要求每列只能有一个房子，因此第`i`个房子的列号必须是`i`（从1到n）。优质题解都直接将`x[i]`（列号）设为`i`，完美满足这一约束，无需额外处理。  
   * 💡 **学习笔记**：利用题目约束简化问题，是编程中的重要思维方式。

### ✨ 解题技巧总结
- **技巧A：固定基准点**：对于有已知条件的构造问题，先固定一个基准点（如`a₁=0`的房子），再推导其他元素；  
- **技巧B：分情况讨论**：根据变量的大小关系（如`a_i`与`i`），选择不同的构造逻辑；  
- **技巧C：利用约束简化**：将“每列一个房子”转化为“列号固定为`i`”，减少变量维度。


## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解之前，先来看一个**通用核心C++实现**（综合了三个题解的思路，逻辑清晰）：
</code_intro_overall>

**本题通用核心C++实现参考**  
* **说明**：本代码综合了三个优质题解的思路，以(1,1)为基准点，分情况计算行号，满足所有约束。  
* **完整核心代码**：
  ```cpp
  #include <iostream>
  #include <vector>
  using namespace std;

  int main() {
      int n;
      cin >> n;
      vector<int> a(n+1), x(n+1), y(n+1), target(n+1); // x列号，y行号，target目标索引
      for (int i=1; i<=n; i++) {
          cin >> a[i];
      }
      // 第一个房子：(1,1)，目标是自己
      x[1] = 1;
      y[1] = 1;
      target[1] = 1;
      cout << "YES" << endl;
      cout << x[1] << " " << y[1] << endl;
      // 处理后面的房子
      for (int i=2; i<=n; i++) {
          x[i] = i; // 列号固定为i
          if (a[i] == 0) { // 自己为目标
              y[i] = 1;
              target[i] = i;
          } else if (a[i] >= i) { // 目标是第一个房子
              y[i] = a[i] - i + 2;
              target[i] = 1;
          } else { // 目标是前面第i-a[i]个房子
              int k = i - a[i];
              y[i] = y[k];
              target[i] = k;
          }
          cout << x[i] << " " << y[i] << endl;
      }
      // 输出目标
      for (int i=1; i<=n; i++) {
          cout << target[i] << " ";
      }
      return 0;
  }
  ```
* **代码解读概要**：  
  代码分为三部分：  
  1. 读取输入：`n`和`a`数组（`a[i]`是第`i`个房子的距离要求）；  
  2. 处理第一个房子：固定为(1,1)，目标是自己；  
  3. 处理后面的房子：列号固定为`i`，分三种情况计算行号和目标（`a[i]=0`、`a[i]≥i`、`a[i]<i`）；  
  4. 输出所有房子的位置和目标。


<code_intro_selected>
接下来，我们剖析三个优质题解的核心片段，点出各自的亮点：
</code_intro_selected>

**题解一：来源：0tAp**  
* **亮点**：用`rep`循环简化代码，分情况讨论明确。  
* **核心代码片段**：
  ```cpp
  rep(i,2,n){
      if(!a[i]){x[i]=i,y[i]=1,ans[i]=i;continue;}
      int now=a[i]-i+1;
      if(now==0){x[i]=i,y[i]=1;ans[i]=1;continue;}
      if(now>0){x[i]=i,y[i]=now+1;ans[i]=1;continue;}
      else{x[i]=i,y[i]=y[-now+1],ans[i]=-now+1;continue;}
  }
  ```
* **代码解读**：  
  这段代码用`rep`循环（`for(int i=2;i<=n;i++)`的简写）处理后面的房子。`now`变量是`a[i]-i+1`，其实等价于`a[i] - (i-1)`（因为`i-1`是第`i`列到第1列的距离）。当`now>0`时，行号是`now+1`（即`a[i]-i+2`）；当`now<0`时，`-now+1`是目标索引（`i - a[i]`），行号取目标的行号`y[-now+1]`。  
* 💡 **学习笔记**：`rep`循环是竞赛中常用的简写，能提高代码可读性。

**题解二：来源：FFTotoro**  
* **亮点**：下标从0开始，用`r`数组存行号，`l`数组存目标。  
* **核心代码片段**：
  ```cpp
  for(int i=1;i<n;i++){
      if(!a[i]){cout<<i+1<<" 1\n",r[i]=1,l[i]=i; continue;}
      int x=a[i]-i;
      if(x>=0)cout<<i+1<<' '<<(r[i]=x+1)<<endl;
      else cout<<i+1<<' '<<(r[i]=r[l[i]=i-a[i]])<<endl;
  }
  ```
* **代码解读**：  
  这段代码用`i`从1到`n-1`（因为下标从0开始），`r[i]`存储第`i`个房子的行号，`l[i]`存储目标索引。`x=a[i]-i`等价于`a[i] - (i+1-1)`（因为列号是`i+1`），当`x≥0`时，行号是`x+1`（即`a[i]-i+1`，对应1-based的`a[i]-i+2`）；当`x<0`时，`i-a[i]`是目标索引（0-based），行号取`r[i-a[i]]`。  
* 💡 **学习笔记**：下标从0开始是编程中的常见习惯，需要注意转换（如输出时`i+1`）。

**题解三：来源：I_am_Tangser**  
* **亮点**：变量名贴近问题描述，步骤明确。  
* **核心代码片段**：
  ```cpp
  for(int i=2;i<=n;i++){
      if(a[i]<i){
          cout<<i<<" "<<b[i-a[i]]<<endl;
          b[i]=b[i-a[i]];
          c[i]=i-a[i];
      }
      else{
          cout<<i<<" "<<2+a[i]-i<<endl;
          b[i]=2+a[i]-i;
          c[i]=1;
      }
  }
  ```
* **代码解读**：  
  这段代码用`b[i]`存储第`i`个房子的行号，`c[i]`存储目标索引。当`a[i]<i`时，目标是`i-a[i]`，行号取`b[i-a[i]]`；当`a[i]≥i`时，行号是`2+a[i]-i`（即`a[i]-i+2`），目标是1。代码逻辑与通用实现完全一致，但变量名更易理解（`b`对应行号，`c`对应目标）。  
* 💡 **学习笔记**：变量名应尽量贴近问题描述，这样代码更易读。


## 5. 算法可视化：像素动画演示 (核心部分)

\<visualization\_intro\>
为了更直观地理解**构造过程**，我设计了一个**8位像素风格的动画**，结合复古游戏元素，让大家“看”到每一步房子的放置过程！
\</visualization\_intro\>

  * **动画演示主题**：像素巫师在网格中建造房子（仿FC游戏《超级马里奥》的画面风格）。  
  * **核心演示内容**：展示第一个房子（红色）作为基准，后面的房子（黄色）依次出现，目标房子（蓝色）高亮，同时显示距离计算过程。  
  * **设计思路简述**：采用8位像素风是为了营造轻松复古的学习氛围；“叮”的音效在放置房子时响起，强化操作记忆；每放置一个房子，屏幕下方显示当前步骤的文字说明（如“第3个房子：a=2 < 3，目标是第1个房子”）。

  * **动画帧步骤与交互关键点**：
    1. **场景初始化**：屏幕显示一个`n×n`的像素网格（背景为浅绿色，网格线为深绿色），左上角有“控制面板”（开始/暂停、单步、重置按钮，速度滑块），下方有“提示框”（显示当前步骤说明）。  
    2. **放置第一个房子**：红色像素块出现在(1,1)位置，伴随“叮”的音效，提示框显示“第1个房子：a=0，目标是自己”。  
    3. **处理第2个房子**：黄色像素块出现在(2,?)位置（列号固定为2），根据`a[2]`的值：  
       - 若`a[2]≥2`：蓝色箭头指向(1,1)，计算行号（如`a[2]=4`，行号=4-2+2=4），黄色块移动到(2,4)，伴随“滴”的音效，提示框显示“第2个房子：a=4 ≥2，目标是第1个房子，行号=4”。  
       - 若`a[2]<2`：蓝色箭头指向前面的房子（如`a[2]=1`，目标是第1个房子），黄色块移动到(2,1)，提示框显示“第2个房子：a=1 <2，目标是第1个房子，行号=1”。  
    4. **重复步骤3**：直到所有房子都放置完毕，屏幕显示“完成！”，伴随胜利音效（仿FC游戏的“通关”音乐）。  
    5. **交互控制**：支持“单步执行”（逐帧观看）、“自动播放”（可调速度）、“重置”（重新开始）。

  * **旁白提示**：
    - （放置第一个房子时）“第一个房子必须放在(1,1)，因为a₁=0，只能自己作为目标！”  
    - （处理第i个房子时）“第i个房子的列号是i，因为每列只能有一个房子！”  
    - （计算行号时）“根据曼哈顿距离公式，行号= a_i -i +2，这样到第一个房子的距离刚好是a_i！”

\<visualization\_conclusion\>
通过这个动画，我们可以清晰地看到**构造法**的每一步：从基准点开始，分情况计算行号，逐步完成所有房子的放置。复古游戏元素让学习过程更有趣，也更容易记住关键步骤！


## 6. 拓展练习与相似问题思考

\<similar\_problems\_intro\>
构造法是编程中的常用技巧，掌握了本题的思路后，可以尝试解决以下相似问题：
\</similar\_problems\_intro\>

  * **通用思路迁移**：  
    构造法常用于解决“满足特定约束的序列/网格生成”问题，比如：  
    1. 生成一个排列，使得每个元素的左边有`k`个比它大的元素；  
    2. 在网格中放置棋子，满足每行每列恰好一个，且距离某个点的距离为给定值；  
    3. 构造一个字符串，使得每个字符的出现次数满足特定条件。

  * **练习推荐 (洛谷)**：
    1. **洛谷 P1002 [NOIP2002 普及组] 过河卒**  
      * 🗣️ **推荐理由**：这道题需要构造一个路径，满足不能经过某些点，是构造法的基础练习。  
    2. **洛谷 P1044 [NOIP2003 普及组] 栈**  
      * 🗣️ **推荐理由**：这道题需要构造栈的操作序列，满足特定的输出顺序，锻炼分情况讨论的能力。  
    3. **洛谷 P1115 最大子段和**  
      * 🗣️ **推荐理由**：虽然这道题是动态规划，但构造最大子段的过程需要用到“贪心+构造”的思路，是拓展练习的好选择。


## 7. 学习心得与经验分享 (若有)

\<insights\_intro\>
三个题解的作者都提到了**分情况讨论**和**利用已知条件**的重要性，以下是有价值的经验分享：
\</insights\_intro\>

> **参考经验 (来自0tAp)**：“我在解决这道题时，最初没有想到‘列号固定为i’的技巧，导致行号计算很复杂。后来想到‘每列一个房子’的约束，直接将列号设为i，问题就简化了很多。”  
> **点评**：这位作者的经验很典型——**利用题目约束简化问题**是编程中的关键思维方式。比如本题中的“每列一个房子”约束，直接将列号设为i，减少了变量维度，让行号计算变得容易。


\<conclusion\>
本次关于「Exact Neighbours (Medium)」的C++解题分析就到这里。希望这份学习指南能帮助大家理解构造法的核心思想，掌握分情况讨论的技巧。记住，构造问题的关键是“用已知推未知”，从基准点开始，逐步推导所有元素的状态。下次我们再一起探索新的编程挑战！💪
\</conclusion\>

---
处理用时：174.62秒