# 题目信息

# Median

## 题目描述

A median in an array with the length of $ n $ is an element which occupies position number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF166C/a3cce6c26f6207c41846eedd0e6a59cdcc521015.png) after we sort the elements in the non-decreasing order (the array elements are numbered starting with $ 1 $ ). A median of an array $ (2,6,1,2,3) $ is the number $ 2 $ , and a median of array $ (0,96,17,23) $ — the number $ 17 $ .

We define an expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF166C/ff48225f7f772c08409f2d464b02c44cf20620e2.png) as the integer part of dividing number $ a $ by number $ b $ .

One day Vasya showed Petya an array consisting of $ n $ integers and suggested finding the array's median. Petya didn't even look at the array and said that it equals $ x $ . Petya is a very honest boy, so he decided to add several numbers to the given array so that the median of the resulting array would be equal to $ x $ .

Petya can add any integers from $ 1 $ to $ 10^{5} $ to the array, including the same numbers. Of course, he can add nothing to the array. If a number is added multiple times, then we should consider it the number of times it occurs. It is not allowed to delete of change initial numbers of the array.

While Petya is busy distracting Vasya, your task is to find the minimum number of elements he will need.

## 说明/提示

In the first sample we can add number $ 9 $ to array $ (10,20,30) $ . The resulting array $ (9,10,20,30) $ will have a median in position ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF166C/087e5fa70c281cf5e7b5f392e766cd46089615e4.png), that is, $ 10 $ .

In the second sample you should add numbers $ 4 $ , $ 5 $ , $ 5 $ , $ 5 $ . The resulting array has median equal to $ 4 $ .

## 样例 #1

### 输入

```
3 10
10 20 30
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 4
1 2 3
```

### 输出

```
4
```

# AI分析结果

# 💡 Kay的C++算法解析：Median 深入学习指南 💡

<introduction>
  今天我们要解决的问题是「CF166C Median」——给定一个数组和目标数x，求最少添加多少个数，才能让x成为新数组的中位数。这个问题看似需要“凑数”，其实核心是**用统计和数学计算找到最优解**。让我们一起拆解思路，掌握关键技巧！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：编程技巧应用（侧重统计与数学计算）

🗣️ **初步分析**：
解决这个问题的关键，就像**让x在“排序后的队伍”里站到正中间**——排序后的数组中，中位数是第 `(当前数组长度 + 1) // 2` 位（比如长度为4时，中位数是第2位；长度为5时是第3位）。我们的目标是让x“占据”这个中间位置，或者让x所在的连续区间覆盖这个位置。

具体来说，算法的核心流程是：
1. **排序数组**：把原数组从小到大排好队，方便统计。
2. **统计三类数的数量**：
   - `small`：比x小的数的个数；
   - `equal`：等于x的数的个数；
   - `big`：比x大的数的个数。
3. **计算需要添加的数**：如果x不在数组中（`equal=0`），必须先加一个x；然后通过数学计算，补充足够的数让x覆盖中位数位置。

**核心难点**：
- 正确理解中位数的位置公式；
- 处理x不在原数组的情况；
- 用数学推导代替暴力枚举，找到最少添加次数。

**可视化设计思路**：
我们会用**8位像素风**做一个“排队游戏”动画：
- 用不同颜色的像素块表示数组元素（比如x是黄色，其他数是蓝色）；
- 用红色箭头指向当前中位数的位置；
- 添加数时，黄色块会“自动加入队伍”，箭头同步移动；
- 关键操作（如添加x、调整中位数位置）会播放“叮”的像素音效，成功时播放上扬的“胜利音效”。


## 2. 精选优质题解参考

<eval_intro>
我从**思路清晰度、代码可读性、算法效率**三个维度筛选了3份优质题解，覆盖了“数学推导”“STL简化”“直观枚举”三种思路，适合不同学习阶段的同学参考。
</eval_intro>

**题解一：cachejtt（数学推导派）**
* **点评**：这份题解的亮点是**用数学公式直接算出答案**，完全不用枚举！作者先统计`small`（比x小的数）、`equal`（等于x的数）、`big`（比x大的数），然后通过两个公式判断需要补充的数量：
  - 如果x太小（中位数位置在x右边），需要补充`big - (small + equal)`个小数；
  - 如果x太大（中位数位置在x左边），需要补充`small - (big + equal - 1)`个大数。
  最后取两个值的最大值——因为负数表示不需要补充。代码极其简洁，变量名清晰，是“用数学简化问题”的典范！

**题解二：Lucifer_Bartholomew（STL简化派）**
* **点评**：作者用`lower_bound`和`upper_bound`快速找到x在排序数组中的范围（`l`是第一个≥x的位置，`r`是第一个>x的位置），然后循环添加x，直到中位数位置落在`[l, r)`区间内。代码短到“惊艳”，STL函数的使用非常巧妙，适合学习如何用标准库简化操作。

**题解三：飞啾6373（直观枚举派）**
* **点评**：这份题解最适合初学者！作者先处理x不在数组的情况（手动加一个x），然后排序后**枚举每个x的位置**，计算需要补充的数的最小值。注释写得非常详细（比如`qwq`变量标记是否有x），逻辑一步一步展开，像“手把手教你解题”，能帮你彻底理解每一步的意义。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这个问题时，大家容易卡在“中位数位置怎么算”“x不在数组怎么办”“怎么最少加数”这三个点上。结合优质题解，我总结了针对性的解决方法：
</difficulty_intro>

1.  **关键点1：中位数的位置到底怎么算？**
    * **分析**：中位数是排序后的第 `m` 位，其中 `m = (当前数组长度 + 1) // 2`（整数除法）。比如：
      - 数组长度为3 → m=(3+1)//2=2（第2位）；
      - 数组长度为4 → m=(4+1)//2=2（第2位）；
      - 数组长度为5 → m=(5+1)//2=3（第3位）。
    * 💡 **学习笔记**：记住公式`m=(len+1)//2`，每次数组长度变化时重新计算！

2.  **关键点2：x不在原数组里怎么办？**
    * **分析**：如果原数组没有x，无论加多少其他数，x都不可能成为中位数。因此必须**先加一个x**，再调整其他数。比如样例2中，原数组是[1,2,3]，x=4不在里面，所以先加一个4变成[1,2,3,4]，再补充3个4，让中位数变成4。
    * 💡 **学习笔记**：第一步先检查`equal`（等于x的数的个数），如果`equal=0`，必须先加1！

3.  **关键点3：怎么计算最少需要加多少数？**
    * **分析**：假设我们已经有了x（`equal≥1`），排序后x的位置范围是`[l, r)`（`l`是第一个x的位置，`r`是最后一个x的下一位）。我们需要让中位数位置`m`落在`[l, r)`里。通过统计`small`（左边的数）、`big`（右边的数），可以用两个公式计算需要补充的数：
      - 如果`m < l`（x太靠右）：需要补充`small - (big + equal - 1)`个大数；
      - 如果`m ≥ r`（x太靠左）：需要补充`big - (small + equal)`个小数。
    * 💡 **学习笔记**：用统计代替枚举，数学公式能快速找到最优解！

### ✨ 解题技巧总结
- **技巧1：先排序再统计**：排序是统计的基础，能快速区分“比x小”“等于x”“比x大”的数；
- **技巧2：用STL简化查找**：`lower_bound`和`upper_bound`能快速找到x的位置范围，避免手动遍历；
- **技巧3：数学推导代替暴力**：通过统计`small`/`equal`/`big`，用公式直接算答案，效率更高。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**综合所有优质题解思路的通用核心代码**，它结合了数学推导的高效和边界处理的严谨，适合直接参考！
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码来自题解cachejtt的思路，用统计和数学公式直接计算答案，是最简洁高效的实现。
* **完整核心代码**：
  ```cpp
  #include <iostream>
  using namespace std;

  int main() {
      int n, k;
      cin >> n >> k;
      int small = 0, equal = 0, big = 0;
      for (int i = 0; i < n; ++i) {
          int a;
          cin >> a;
          if (a < k) small++;
          else if (a == k) equal++;
          else big++;
      }
      // 检查当前是否已经满足条件
      int len = n;
      int m = (len + 1) / 2;
      if (small < m && small + equal >= m) {
          cout << 0 << endl;
          return 0;
      }
      // 如果没有x，先加一个
      int ans = 0;
      if (equal == 0) {
          ans = 1;
          equal = 1;
          len = n + 1;
          m = (len + 1) / 2;
      }
      // 计算需要补充的数量
      int need1 = big - (small + equal);    // 需要补充的小数数量
      int need2 = small - (big + equal - 1); // 需要补充的大数数量
      ans += max(need1, need2);
      cout << ans << endl;
      return 0;
  }
  ```
* **代码解读概要**：
  1. 读取输入，统计`small`/`equal`/`big`；
  2. 检查当前数组是否已经满足条件（中位数是x）；
  3. 如果没有x，先加一个x（更新`ans`/`equal`/`len`）；
  4. 计算需要补充的小数或大数数量，取最大值加到`ans`；
  5. 输出结果。

---

<code_intro_selected>
接下来看3份优质题解的核心片段，分析它们的亮点！
</code_intro_selected>

**题解一：cachejtt（数学推导）**
* **亮点**：用两个公式直接算出需要补充的数量，不用循环。
* **核心代码片段**：
  ```cpp
  int need1 = big - (small + equal);    // 补充小数，让x左移
  int need2 = small - (big + equal - 1); // 补充大数，让x右移
  ans += max(need1, need2);
  ```
* **代码解读**：
  - `need1`：如果x太靠左（中位数在x右边），需要补充`need1`个小数，让x的左边人数增加，中位数左移；
  - `need2`：如果x太靠右（中位数在x左边），需要补充`need2`个大数，让x的右边人数增加，中位数右移；
  - 取最大值是因为负数表示不需要补充（比如`need1=-2`意味着不需要补充小数）。
* 💡 **学习笔记**：数学推导能把问题从“枚举”变成“计算”，效率翻倍！

**题解二：Lucifer_Bartholomew（STL简化）**
* **亮点**：用`lower_bound`和`upper_bound`快速找x的位置范围。
* **核心代码片段**：
  ```cpp
  sort(a, a+n);
  int l = lower_bound(a, a+n, k) - a;
  int r = upper_bound(a, a+n, k) - a;
  int mid = (n-1) >> 1; // 等价于(n-1)/2
  while (mid < l || mid >= r) {
      ans++;
      r++;
      mid = (++n -1) >> 1;
  }
  ```
* **代码解读**：
  - `lower_bound`找第一个≥k的位置`l`；
  - `upper_bound`找第一个>k的位置`r`；
  - `mid`是当前中位数的位置（注意这里用`(n-1)>>1`，和之前的`(len+1)//2`等价吗？比如n=4时，`(4-1)>>1=1`，对应第2位，是的！）；
  - 循环添加k（`r++`表示x的范围扩大），直到`mid`落在`[l, r)`里。
* 💡 **学习笔记**：STL的`lower_bound`和`upper_bound`是处理有序数组的神器，一定要掌握！

**题解三：飞啾6373（直观枚举）**
* **亮点**：枚举每个x的位置，计算需要补充的数量，适合初学者理解。
* **核心代码片段**：
  ```cpp
  if (qwq == 0) { // qwq标记是否有x
      n++;
      a[n] = k;
      ans = 1;
  }
  sort(a+1, a+n+1);
  for (int i=1; i<=n; ++i) {
      if (a[i] == k) {
          int x = abs((i-1) - (n-i));
          if (i-1 < n-i) x--;
          q = min(q, x);
      } else if (a[i] > k) break;
  }
  ans += q;
  ```
* **代码解读**：
  - `qwq==0`表示没有x，先加一个x；
  - 排序后，枚举每个x的位置`i`；
  - `i-1`是x左边的数的个数，`n-i`是右边的数的个数；
  - `x`是需要补充的数的数量（如果左边少，就减1）；
  - 取所有x中的最小值，加到`ans`里。
* 💡 **学习笔记**：枚举法虽然效率不高，但能帮你直观理解问题，是入门的好方法！


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让大家更直观地“看”到算法的执行过程，我设计了一个**8位像素风的“排队游戏”动画**，结合复古游戏元素，让学习更有趣！
</visualization_intro>

### 🎮 动画演示主题：像素小队的“中间位挑战”
**设计思路**：用FC红白机的风格展示数组排序、x的位置调整，通过“添加像素块”和“箭头移动”直观呈现中位数的变化。游戏化元素（如音效、关卡）能强化记忆，让你在“玩”中理解算法。

### 🎬 动画帧步骤与交互关键点
1. **场景初始化**：
   - 屏幕左侧是**排序后的数组**（蓝色像素块），右侧是**控制面板**（开始/暂停、单步、重置按钮，速度滑块）；
   - 背景是FC风格的草地，播放8位循环BGM（比如《超级玛丽》的轻快旋律）。

2. **数据初始化**：
   - 输入样例2（原数组[1,2,3]，x=4）：排序后的数组显示为`[1,2,3]`（蓝色块）；
   - 因为x不在数组中，先添加一个4（黄色块），数组变成`[1,2,3,4]`，播放“叮”的音效；
   - 中位数位置`m=(4+1)//2=2`（红色箭头指向第2位的“2”）。

3. **核心步骤演示**：
   - 当前x的位置是第4位，中位数位置是第2位（x太靠右）；
   - 需要补充3个4（黄色块），每次添加时：
     1. 数组长度加1（`[1,2,3,4,4]`→`[1,2,3,4,4,4]`→`[1,2,3,4,4,4,4]`）；
     2. 中位数位置`m`更新：`(5+1)//2=3`→`(6+1)//2=3`→`(7+1)//2=4`；
     3. 红色箭头同步移动，每次添加播放“叮”的音效；
   - 当数组变成`[1,2,3,4,4,4,4]`时，中位数位置是第4位（指向黄色块4），播放“胜利音效”（类似《魂斗罗》的通关音乐），屏幕弹出“挑战成功！”的像素文字。

4. **交互设计**：
   - **单步执行**：点击“单步”按钮，手动添加一个4，观察中位数位置的变化；
   - **自动播放**：点击“自动”按钮，动画自动执行，速度可通过滑块调整；
   - **重置**：点击“重置”按钮，回到初始状态，重新开始挑战。

### 📝 旁白提示（动画中的文字气泡）
- “现在x不在数组里，先加一个4吧！”（添加第一个4时）；
- “中位数位置是第2位，指向2，还没到x的位置！”（第一次添加后）；
- “添加第3个4后，中位数位置到第4位啦，x成为中位数！”（挑战成功时）。

<visualization_conclusion>
这个动画把抽象的“统计”和“数学计算”变成了具象的“排队游戏”，你能清晰看到x如何从“队伍末尾”移动到“正中间”，中位数位置如何随数组长度变化。8位风格和音效让学习更轻松，赶紧试试吧！
</visualization_conclusion>


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握了本题的统计和数学技巧后，我们可以把思路迁移到**需要“调整数量使目标满足条件”**的问题中，比如：
</similar_problems_intro>

### 🔍 通用思路迁移
- **场景1**：调整数组元素，让某个数成为“众数”（出现次数最多的数）；
- **场景2**：调整分数，让平均分达到目标值；
- **场景3**：调整队列长度，让某个人站到指定位置。

### 📚 洛谷练习推荐
以下题目能帮你巩固“统计+数学计算”的技巧：
1. **洛谷 P1168 中位数**  
   🗣️ **推荐理由**：直接考察中位数的计算，帮你熟练掌握中位数的位置公式。
2. **洛谷 P2078 朋友**  
   🗣️ **推荐理由**：需要统计每个朋友圈的大小，类似本题的“分类统计”思路。
3. **洛谷 P1090 合并果子**  
   🗣️ **推荐理由**：用贪心算法统计最小合并成本，锻炼“统计+优化”的思维。
4. **洛谷 P1614 爱与愁的心痛**  
   🗣️ **推荐理由**：统计连续子数组的最小值，强化“滑动窗口+统计”的技巧。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
优质题解中的“踩坑经验”能帮你少走弯路，我摘录了2条有价值的心得：
</insights_intro>

> **经验1（来自飞啾6373）**：“我一开始忘了处理x不在数组的情况，提交后 WA 了好几次。后来加了‘如果没有x就先加一个’的判断，才通过！”  
> **点评**：这是初学者最容易犯的错误——忽略边界条件。一定要记住：**x必须存在于数组中，否则不可能成为中位数**！

> **经验2（来自Lucifer_Bartholomew）**：“用`lower_bound`和`upper_bound`找x的范围时，要注意数组必须是排序后的！我一开始没排序，结果位置找错了。”  
> **点评**：STL的二分查找函数（`lower_bound`/`upper_bound`）只对**有序数组**有效，这是使用标准库的关键前提！


<conclusion>
本次关于「Median」的分析就到这里啦！这道题的核心是**用统计和数学简化问题**，而不是暴力枚举。记住：排序是基础，统计是关键，数学推导能让你事半功倍。下次遇到“调整数量使目标满足条件”的问题，不妨试试今天学的技巧——先排序、再统计、最后算答案！💪
</conclusion>

---
处理用时：204.20秒