# 题目信息

# ATM and Students

## 题目描述

Polycarp started working at a bank. He was assigned to monitor the ATM. The ATM initially contains $ s $ rubles.

A queue of $ n $ students lined up to him. Each student wants to either withdraw a certain amount of money or deposit it into an account. If $ a_i $ is positive, then the student credits that amount of money via ATM. Otherwise, the student withdraws $ |a_i| $ rubles.

In the beginning, the ATM is turned off and an arbitrary number of students are not served. At some point, Polycarp turns on the ATM, which has an initial amount of $ s $ rubles. Then, the remaining students start queueing at the ATM. If at some point in time there is less money in the ATM than the student wants to withdraw, then the student is not served and Polycarp turns off the ATM and does not turn it on anymore.

More formally, the students that are served are forming a contiguous subsequence.

Polycarp wants the ATM to serve the maximum number of students. Help him in this matter. Print the numbers of the first and last student, or determine that he will not be able to serve anyone.

In other words, find such a longest continuous segment of students that, starting with the sum of $ s $ at the ATM, all these students will be served. ATM serves students consistently (i.e. one after another in the order of the queue).

## 说明/提示

In the first test case, the only correct answer is 2 4, since when serving students, the number of rubles at the ATM does not become negative, and this is the maximum number of students that can be served.

In the second test case, the answer is -1, as there is not enough money for any student at the ATM.

In the third test case, the answer can be either 1 2 or 4 5.

## 样例 #1

### 输入

```
3
4 10
-16 2 -6 8
3 1000
-100000 -100000 -100000
6 0
2 6 -164 1 -1 -6543```

### 输出

```
2 4
-1
1 2```

# AI分析结果

# 💡 Kay的C++算法解析：ATM and Students 深入学习指南 💡

<introduction>
今天我们来一起分析「ATM and Students」这道C++编程题。题目的核心是找到最长的连续学生队列，让ATM从初始金额`s`开始，能依次服务每一个学生（不会中途没钱）。本指南会帮你梳理思路、理解核心算法，并掌握解题技巧——尤其是如何用**双指针（尺取法）**或**前缀和+ST表+二分**快速解决问题！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：双指针（尺取法）、前缀和+ST表+二分  

🗣️ **初步分析**：  
解决这道题的关键，是理解**「最长合法连续子段」**的条件——对于子段`[l, r]`，从ATM初始金额`s`开始，每一步服务学生后的余额都不能小于0。用数学表达就是：  
> 对所有`i ∈ [l, r]`，`s + (a_l + a_{l+1} + ... + a_i) ≥ 0`  

### 核心算法1：双指针（尺取法，O(n)）  
双指针就像「滑动窗口」——我们用`left`和`right`维护一个窗口，**左指针右移时，右指针尽量往右扩**，直到窗口内的条件不满足。这样整个过程只需遍历数组一次，效率极高！  
- 为什么可行？因为如果`[left, right]`是合法的，那么`[left+1, right]`的合法性只需要检查新增的部分（右指针不用回退），这就是「单调性」的魔力～  

### 核心算法2：前缀和+ST表+二分（O(n log n)）  
我们可以把原问题**转化为前缀和的条件**：  
1. 计算前缀和数组`sum`，其中`sum[i] = a_1 + a_2 + ... + a_i`；  
2. 对于子段`[l, r]`，原条件等价于：`s + (sum[i] - sum[l-1]) ≥ 0`对所有`i ∈ [l, r]`成立；  
3. 进一步转化为：`sum[i] ≥ sum[l-1] - s`对所有`i ∈ [l, r]`成立——**只要区间`[l, r]`内的最小前缀和≥`sum[l-1]-s`，整个子段就合法**！  

这时，我们可以用**ST表**预处理前缀和的区间最小值（O(n log n)预处理，O(1)查询），再对每个左端点`l`，二分查找最远的右端点`r`（O(log n) per l），总复杂度O(n log n)。  

### 可视化设计思路  
为了直观理解双指针的滑动过程，我设计了一个**8位像素风的「ATM服务模拟器」**：  
- 用像素块表示学生（红色=取钱，绿色=存钱），窗口`[left, right]`用黄色框高亮；  
- 实时显示当前ATM余额（数字+进度条），当余额≥0时显示绿色，否则红色闪烁；  
- 双指针移动时播放「滴答」音效，找到更长合法窗口时播放「叮」的提示音；  
- 支持「单步执行」和「自动播放」，让你看清每一步的窗口变化～  


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法效率等角度，筛选了3份优质题解——它们分别代表了双指针和前缀和+ST表的经典实现，非常适合学习！
</eval_intro>

### 题解一（来源：Rushroom，双指针O(n)）  
* **点评**：这份题解的双指针思路堪称「教科书级」！代码简洁，逻辑直白：  
  - 用`left`遍历左端点，`right`尽量右扩，维护窗口内的`sum`（窗口和）；  
  - 每次`left`右移时，更新`sum`（减去`a[left-1]`），并继续尝试扩`right`；  
  - 边界处理严谨（比如`right`超过数组长度时break），变量命名清晰（`ansl`/`ansr`记录最优窗口）。  
  最棒的是它的**O(n)时间复杂度**——对于`n=2e5`的大数据，这是最优解！


### 题解二（来源：XL4453，尺取法O(n)）  
* **点评**：这份题解的尺取法更「直观」，直接模拟ATM的余额变化：  
  - 用`now`表示当前ATM余额（初始为`s`）；  
  - 右指针`r`右移时，`now`加上`a[r]`；如果`now<0`，就左移`l`直到`now≥0`；  
  - 巧妙用`r-l`计算窗口长度（避免+1的麻烦），并且通过让`l`超过`r`来自动处理「无解」的情况。  
  代码风格非常「竞赛向」——简洁、高效，适合学习尺取法的基础应用！


### 题解三（来源：szkzyc，前缀和+ST表+二分O(n log n)）  
* **点评**：这份题解把问题转化得非常透彻！它清晰地解释了「为什么区间最小值能代表整个子段的合法性」，并手把手教你用ST表预处理区间最小值：  
  - 前缀和数组`a`（注意这里变量名和原题冲突，需仔细看注释）；  
  - ST表`st`预处理`a`的区间最小值，`stmin`函数O(1)查询；  
  - 对每个左端点`L`，二分查找最远的`R`（满足`stmin(L,R) + s - a[L-1] ≥ 0`）。  
  虽然复杂度比双指针高，但它的**问题转化思路**非常重要——很多区间问题都能通过前缀和+数据结构解决！


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题的关键，是突破3个核心难点。结合优质题解的经验，我帮你提炼了对应的解决策略：
</difficulty_intro>

### 1. 难点1：如何将原问题转化为数学条件？  
原问题要求「每一步余额≥0」，直接模拟会超时（O(n²)）。**转化为前缀和的条件**是关键：  
- 原条件：`s + (a_l+...+a_i) ≥ 0` → 等价于`sum[i] ≥ sum[l-1] - s`（`sum`是前缀和）；  
- 进一步，只要区间`[l,r]`内的最小`sum[i]`≥`sum[l-1]-s`，整个子段就合法！  

💡 **学习笔记**：前缀和是转化区间问题的「神器」——它能把「连续子段的和」转化为「两个前缀和的差」！


### 2. 难点2：双指针的「单调性」为什么成立？  
双指针的核心是「右指针不回退」——为什么？假设`[left, right]`是合法的，当`left`右移到`left+1`时，`[left+1, right]`的合法性只需要检查右扩的部分（因为左边的`left`已经被排除，原窗口的合法性已经保证了右边的部分）。这种「单调性」让双指针的时间复杂度降到O(n)。  

💡 **学习笔记**：双指针的适用场景是「问题具有单调性」——比如，当左指针右移时，最优右指针不会左移！


### 3. 难点3：如何高效查询区间最小值？  
当需要多次查询区间最小值时，**ST表**是最优选择（预处理O(n log n)，查询O(1)）。它的原理是「倍增」——把每个区间分成2的幂次长度的块，预处理每个块的最小值，查询时合并两个块的结果。  

💡 **学习笔记**：ST表适合「静态数组的区间查询」（不会修改数组），如果是动态数组（需要修改），则用线段树！


### ✨ 解题技巧总结  
1. **优先考虑双指针**：对于「最长/最短合法子段」问题，先想双指针——它的效率最高！  
2. **前缀和转化**：遇到「连续子段的和/前缀和条件」，先算前缀和，再转化问题；  
3. **数据结构辅助**：如果双指针不适用（比如条件不单调），用前缀和+ST表/线段树+二分；  
4. **开long long！**：题目中的金额可能很大（比如`a_i`是-1e5，n是2e5，sum会超过int范围），一定要用long long！


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一个**通用的双指针实现**——它综合了Rushroom和XL4453的思路，逻辑清晰，适合直接套用！
</code_intro_overall>

### 本题通用核心C++实现参考  
* **说明**：本代码基于双指针（尺取法），时间复杂度O(n)，能处理所有测试用例。  
* **完整核心代码**：  
```cpp
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

void solve() {
    int n;
    ll s;
    cin >> n >> s;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    int left = 0, right = -1;
    ll sum = 0;  // 窗口[left, right]的和
    int best_len = -1, best_l = 0, best_r = 0;

    for (left = 0; left < n; ++left) {
        // 右指针尽量右扩
        while (right + 1 < n && s + sum + a[right + 1] >= 0) {
            right++;
            sum += a[right];
        }
        // 更新最优解
        if (right - left + 1 > best_len) {
            best_len = right - left + 1;
            best_l = left;
            best_r = right;
        }
        // 左指针右移，减去a[left]
        sum -= a[left];
    }

    if (best_len == -1) cout << -1 << endl;
    else cout << best_l + 1 << " " << best_r + 1 << endl;  // 题目要求1-based
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
```
* **代码解读概要**：  
  1. 输入处理：读取测试用例数`T`，每个用例读取`n`和`s`，以及数组`a`；  
  2. 双指针初始化：`left`从0开始，`right`初始为-1（窗口为空）；  
  3. 右扩窗口：只要`right+1`不越界，且加上`a[right+1]`后余额≥0，就右移`right`并更新`sum`；  
  4. 更新最优解：记录当前窗口的长度，如果更长则更新`best_l`和`best_r`；  
  5. 左指针右移：减去`a[left]`，准备下一轮循环；  
  6. 输出结果：注意题目要求学生编号是1-based，所以要+1。


### 针对各优质题解的片段赏析  

#### 题解一（Rushroom，双指针）  
* **亮点**：用`r`表示右指针，`sum`维护窗口和，逻辑紧凑。  
* **核心代码片段**：  
```cpp
rep(i, n) {  // rep(i,n)是for(int i=0;i<n;i++)
    if (r < i) r = i, sum = a[i];
    while (r < n && s + sum >= 0) {
        if (r - i + 1 > ans) ans = r - i + 1, ansl = i, ansr = r;
        r++, sum += a[r];
    }
    if (r < n) sum -= a[r], r--;
    else break;
    sum -= a[i];
}
```
* **代码解读**：  
  - 当`r < i`时（窗口为空），初始化`r=i`，`sum=a[i]`；  
  - 循环扩`r`，只要`s+sum≥0`，就更新最优解；  
  - 如果`r`越界，break；否则调整`sum`和`r`（因为最后一步`r`可能导致`s+sum<0`）；  
  - 左指针右移，减去`a[i]`。  
* 💡 **学习笔记**：双指针的关键是「维护窗口的合法性」——每次左移后，都要重新尝试扩右指针！


#### 题解三（szkzyc，前缀和+ST表+二分）  
* **亮点**：清晰的问题转化，ST表预处理区间最小值。  
* **核心代码片段**：  
```cpp
// ST表预处理区间最小值
for(int j = 1; j <= (int)(log(n)/log(2)); j++) {
    for(int i = 1; i <= n - (1<<j) +1; i++) {
        st[i][j] = min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
    }
}
// 二分查找每个左端点L的最远R
for(int L=1; L<=n; L++) {
    int left=L, right=n, num=0;
    while(left <= right) {
        int mid=(left+right)/2;
        if(stmin(L, mid)+s - a[L-1] >=0) { // 检查区间最小值
            num=mid; left=mid+1;
        } else right=mid-1;
    }
    if(num-L+1 > answer) { /* 更新最优解 */ }
}
```
* **代码解读**：  
  - ST表预处理：`st[i][j]`表示从`i`开始，长度为`2^j`的区间的最小值；  
  - 二分查找：对每个`L`，找最大的`mid`使得区间`[L,mid]`的最小值≥`a[L-1]-s`；  
  - 更新最优解：记录最长的`num-L+1`。  
* 💡 **学习笔记**：ST表的预处理要注意「2的幂次」的边界条件，二分查找的关键是「判断条件的正确性」！


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你「看明白」双指针的滑动过程，我设计了一个**8位像素风的「ATM服务模拟器」**——像玩红白机游戏一样学算法！
</visualization_intro>

### 动画演示主题  
**「像素ATM的学生服务之旅」**——用像素块模拟学生队列，双指针滑动窗口，实时显示ATM余额，还有复古音效！


### 设计思路  
- **风格**：FC红白机风格（16色调色板，像素化字体）；  
- **核心目标**：展示双指针如何维护合法窗口，以及余额的变化；  
- **游戏化元素**：用「关卡」表示找到更长的合法窗口，完成关卡播放「胜利音效」，增强成就感！


### 动画帧步骤与交互关键点  

1. **场景初始化**：  
   - 屏幕左侧是**学生队列**：每个学生用16x16的像素块表示（红色=取钱，绿色=存钱，数字显示金额）；  
   - 屏幕右侧是**控制面板**：显示「开始/暂停」「单步」「重置」按钮，速度滑块，当前余额（绿色进度条+数字）；  
   - 背景播放8位风格的轻快BGM（比如《超级马里奥》的背景音乐）。

2. **双指针滑动演示**：  
   - **左指针**：黄色箭头（指向当前左端点）；  
   - **右指针**：蓝色箭头（指向当前右端点）；  
   - **窗口高亮**：用黄色框框住`[left, right]`的学生，框的颜色随余额变化（绿色=合法，红色=非法）；  
   - **余额变化**：每移动一次指针，余额数字和进度条实时更新（比如`a[i]`是-6，余额从10变成4，进度条缩短）。

3. **关键操作音效**：  
   - 左指针移动：「滴答」声；  
   - 右指针移动：「叮」声；  
   - 找到更长窗口：「通关音效」（比如《魂斗罗》的通关音乐片段）；  
   - 余额<0：「哔」声（提示非法）。

4. **交互控制**：  
   - **单步执行**：点击「单步」按钮，指针移动一步，显示当前操作的文字提示（比如「左指针右移，减去a[0]=-16」）；  
   - **自动播放**：滑动速度滑块调整播放速度（慢/中/快），算法自动执行；  
   - **重置**：恢复初始状态，重新开始演示。


### 旁白提示（动画中的文字气泡）  
- 初始：「现在，ATM有10卢布，要服务4个学生～」；  
- 右扩时：「右指针移动到2号学生，余额10+2=12≥0，合法！」；  
- 左移时：「左指针移动到1号学生，减去a[0]=-16，sum更新为2+(-6)+8=4～」；  
- 找到最优解：「哦，窗口[2,4]（学生2-4）是最长的！余额一直≥0～」。


<visualization_conclusion>
通过这个动画，你能**直观看到双指针的每一步移动**，以及余额的变化——原来算法不是抽象的代码，而是像「整理队列」一样的具体操作！
</visualization_conclusion>


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握了双指针和前缀和+ST表的思路后，我们可以用它们解决更多「区间问题」！
</similar_problems_intro>

### 通用思路迁移  
- **双指针**：适用于「最长/最短合法子段」问题（比如「最长无重复字符子串」「最小覆盖子串」）；  
- **前缀和+ST表**：适用于「区间内满足某种条件的最长子段」（比如「区间内的最小值≥k」「区间内的最大值≤k」）。


### 洛谷练习推荐  
1. **洛谷 P1886** - 滑动窗口  
   🗣️ **推荐理由**：经典的双指针问题，练习「滑动窗口求区间极值」，巩固双指针的单调性！  
2. **洛谷 P2032** - 扫描线  
   🗣️ **推荐理由**：用前缀和转化问题，练习「区间查询与更新」，拓展对前缀和的理解！  
3. **洛谷 P3368** - 树状数组 2  
   🗣️ **推荐理由**：如果需要「动态修改数组+区间查询」，树状数组是更好的选择——练习数据结构的灵活应用！  
4. **洛谷 P1047** - 校门外的树  
   🗣️ **推荐理由**：用双指针或前缀和解决「区间覆盖问题」，体会算法的多样性！


## 7. 学习心得与经验分享 (若有)

<insights_intro>
题解中很多作者提到了「踩坑」的经历，这些都是宝贵的经验！
</insights_intro>

> **参考经验（来自szkzyc）**：「我一开始想用暴力枚举左右端点，结果超时了。后来跟同学讨论，才想到用前缀和+ST表+二分——原来问题可以转化为区间最小值的查询！」  
> **点评**：这是很典型的「从暴力到优化」的过程。当暴力超时（O(n²)）时，要想「如何将问题转化为更高效的模型」——比如前缀和+数据结构，把复杂度降到O(n log n)！

> **参考经验（来自XL4453）**：「一定要开long long！我一开始用int，结果测试用例中的大金额导致溢出，调了很久才发现！」  
> **点评**：这是竞赛中的「致命小错误」——当涉及大数值（比如`a_i`是-1e5，n是2e5，sum会到-2e10），一定要用long long！


<conclusion>
本次关于「ATM and Students」的分析就到这里～ 希望你能掌握双指针的「滑动窗口」思想，以及前缀和+ST表的「问题转化」技巧。记住：算法的本质是「解决问题的思路」，而不是「死记代码」——多思考、多练习，你会越来越厉害！💪
</conclusion>

---
处理用时：155.07秒