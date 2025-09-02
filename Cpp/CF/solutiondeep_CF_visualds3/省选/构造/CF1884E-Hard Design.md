# 题目信息

# Hard Design

## 题目描述

Consider an array of integers $ b_0, b_1, \ldots, b_{n-1} $ . Your goal is to make all its elements equal. To do so, you can perform the following operation several (possibly, zero) times:

- Pick a pair of indices $ 0 \le l \le r \le n-1 $ , then for each $ l \le i \le r $ increase $ b_i $ by $ 1 $ (i. e. replace $ b_i $ with $ b_i + 1 $ ).
- After performing this operation you receive $ (r - l + 1)^2 $ coins.

The value $ f(b) $ is defined as a pair of integers $ (cnt, cost) $ , where $ cnt $ is the smallest number of operations required to make all elements of the array equal, and $ cost $ is the largest total number of coins you can receive among all possible ways to make all elements equal within $ cnt $ operations. In other words, first, you need to minimize the number of operations, second, you need to maximize the total number of coins you receive.

You are given an array of integers $ a_0, a_1, \ldots, a_{n-1} $ . Please, find the value of $ f $ for all cyclic shifts of $ a $ .

Formally, for each $ 0 \le i \le n-1 $ you need to do the following:

- Let $ c_j = a_{(j + i) \pmod{n}} $ for each $ 0 \le j \le n-1 $ .
- Find $ f(c) $ . Since $ cost $ can be very large, output it modulo $ (10^9 + 7) $ .

Please note that under a fixed $ cnt $ you need to maximize the total number of coins $ cost $ , not its remainder modulo $ (10^9 + 7) $ .

## 说明/提示

In the first test case, there is only one cycle shift, which is equal to $ [1] $ , and all its elements are already equal.

In the second test case, you need to find the answer for three arrays:

1. $ f([1, 3, 2]) = (3, 3) $ .
2. $ f([3, 2, 1]) = (2, 5) $ .
3. $ f([2, 1, 3]) = (2, 5) $ .

Consider the case of $ [2, 1, 3] $ . To make all elements equal, we can pick $ l = 1 $ and $ r = 1 $ on the first operation, which results in $ [2, 2, 3] $ . On the second operation we can pick $ l = 0 $ and $ r = 1 $ , which results in $ [3, 3, 3] $ . We have used $ 2 $ operations, and the total number of coins received is $ 1^2 + 2^2 = 5 $ .

## 样例 #1

### 输入

```
5
1
1
3
1 3 2
5
3 2 4 5 1
8
6 5 6 4 2 6 2 2
4
10 10 10 10```

### 输出

```
0 0
3 3
2 5
2 5
7 18
7 16
6 22
5 28
5 28
9 27
9 27
9 27
9 27
11 23
9 27
9 27
13 19
0 0
0 0
0 0
0 0```

# AI分析结果

---
# 💡 Kay的C++算法解析：Hard Design（CF1884E）深入学习指南 💡

<introduction>
今天我们要挑战一道有点难度但思路巧妙的C++题——**Hard Design**（对应CF1884E）。题目需要我们处理循环移位后的数组，找出让所有元素相等的最小操作次数，还要在次数最少的前提下最大化“硬币收入”。这道题会用到经典的**积木大赛模型**和**单调栈技巧**，跟着Kay一步步拆解，你会发现它其实没那么难！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：模拟转化 + 单调栈应用  

🗣️ **初步分析**：  
先把题目“翻译”成更易懂的版本——  
原问题是“选区间加1，让所有元素相等”，但**最优策略肯定是把所有元素加到最大值**（因为加得越多，区间越长，硬币越多）。那我们可以把每个元素 `a[i]` 改成 **`maxa - a[i]`**（`maxa`是数组最大值），这样问题就变成了：**选区间减1，把所有元素变成0**（相当于“削积木”）。  

现在问题拆分两个部分：  
1. **最小操作次数`cnt`**：这是经典的**积木大赛问题**——每次削一段连续的积木，最少需要多少次？答案是**相邻元素差的正数之和**（比如数组`[3,2,1]`，差是`3-0=3`、`2-3=-1`、`1-2=-1`，正数和是3？不对，等下再解释！其实原积木大赛的结论是`sum(max(a[i]-a[i-1], 0))`，这里`a[0]=0`）。  
2. **最大硬币`cost`**：每次操作的硬币是区间长度的平方。要最大化总硬币，就要**尽可能延长每次操作的区间**（比如两次操作选`[1,3]`比选`[1,1]`+`[2,3]`的平方和更大：`3²=9` vs `1+4=5`）。这时候需要用**单调栈**维护当前“可延长的区间长度总和”，计算每次延长的硬币增量。  

**可视化设计思路**：我们用8位像素风模拟“削积木”过程——  
- 数组元素用不同高度的像素块表示（比如`maxa - a[i]`的高度）；  
- `cnt`计算时，用“红色箭头”标记相邻元素的差，正数差会“新增操作”（比如`a[i] > a[i-1]`时，箭头向上，加一个操作）；  
- 计算`cost`时，单调栈用“堆叠的蓝色方块”表示，每次弹出栈顶元素时，用“黄色闪烁”提示“缩短区间”，新增元素时用“绿色生长”提示“延长区间”。  


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性三个维度筛选了3份优质题解，帮你快速抓住核心！
</eval_intro>

**题解一：来源 sunzz3183（赞6）**  
* **点评**：这份题解把问题“拆解得明明白白”——先讲如何转化数组，再用图解释`cnt`的计算（相邻差的正数和），最后用**单调栈**推导`cost`的公式。代码里的注释非常详细（比如单调栈的`while`循环部分），甚至用了三张图辅助理解！比如他提到“每次延长区间，硬币增量是`2*num + a[i]`”，这个公式的推导过程让我一下子就懂了——原来平方和的增量是`(c+1)² - c² = 2c+1`，总和就是`2*num + a[i]`（`num`是当前所有区间的长度总和）。  

**题解二：来源 Petit_Souris（赞1）**  
* **点评**：这位作者的思路很“敏锐”——他指出“最大值位置的`a[i]=0`，可以从这里断环成链”（因为0的位置不需要操作，不会有跨这个位置的区间）。这样就把循环数组变成了线性数组，只需要预处理“前缀”和“后缀”的`cost`，就能快速计算每个移位的答案。代码里的`L`和`R`数组分别处理左右两边的`cost`，逻辑非常简洁。  

**题解三：来源 zhongpeilin（赞1）**  
* **点评**：这份题解的“破环成链”方法很实用——把数组复制成3倍长度（`A+A+A`），这样处理循环移位时不用考虑边界问题。他还详细推导了`r`数组的计算（右边的`cost`）：用单调栈维护“高度递增的区间”，每次弹出栈顶元素时，更新`cnt`（当前区间长度总和），然后计算`r[i]`。代码结构清晰，变量命名也很直观（比如`pos_max`表示最大值的位置）。  


## 3. 核心难点辨析与解题策略

<difficulty_intro>
这道题的“坑”主要在**问题转化**和**单调栈的应用**。结合优质题解，我帮你提炼了3个核心难点和解决策略：
</difficulty_intro>

1.  **难点1：如何把原问题转化为“削积木”？**  
    * **分析**：原问题是“加区间到最大值”，但反过来想——“把每个元素削到0”（`maxa - a[i]`），操作变成“减区间”，这样更容易计算操作次数和硬币。这一步是解题的**关键转折点**，如果想不到转化，后面的思路就卡壳了。  
    * 💡 **学习笔记**：遇到“加操作”的问题，可以试试“反向思考”，把目标变成“减到0”，往往更简单！

2.  **难点2：如何计算最小操作次数`cnt`？**  
    * **分析**：这是经典的积木大赛问题——每次削一段连续的积木，最少次数等于“相邻元素差的正数之和”。比如数组`[3,2,1]`（转化后的），`a[0]=0`，差是`3-0=3`、`2-3=-1`、`1-2=-1`，正数和是3？不对，等下！哦，原积木大赛的数组是`[3,2,1]`，对应的操作是：先削`[1,3]`一次（变成`[2,1,0]`），再削`[1,2]`一次（变成`[1,0,0]`），最后削`[1,1]`一次，总共3次？不对，等下样例2中的`[3,2,1]`的`cnt`是2？哦，原来我搞反了！原问题转化后的数组是`maxa - a[i]`，比如样例2中的`[3,2,1]`的maxa是3，转化后的数组是`[0,1,2]`，差是`0-0=0`、`1-0=1`、`2-1=1`，正数和是2，正好是样例中的`cnt=2`！哦，对！我之前搞反了转化后的数组顺序！  
    * 💡 **学习笔记**：`cnt`的计算一定要记住——转化后的数组`b[i] = maxa - a[i]`，然后`cnt = sum(max(b[i] - b[i-1], 0))`（`b[0]=0`）。

3.  **难点3：如何用单调栈计算最大`cost`？**  
    * **分析**：要最大化平方和，就要尽可能延长每次操作的区间。比如当前有`k`个区间，长度总和是`num`，新增一个元素`b[i]`，如果`b[i]`比之前的区间高，那么每个区间都能延长1（增量是`2*num + b[i]`）；如果`b[i]`低，就要缩短前面的区间（用单调栈弹出高的部分，更新`num`）。单调栈在这里的作用是**维护“高度递增的区间”**，确保我们只处理“可延长的区间”。  
    * 💡 **学习笔记**：单调栈常用于维护“递增/递减序列”，解决“区间最值”或“区间长度”问题，比如本题中的“可延长区间总和”。


### ✨ 解题技巧总结
- **技巧1：反向转化**：把“加操作”转化为“减操作”，简化问题。  
- **技巧2：经典模型复用**：`cnt`的计算复用“积木大赛”的结论，不用重新推导。  
- **技巧3：单调栈维护区间信息**：用单调栈处理“可延长区间”，快速计算平方和增量。  


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**综合优质题解的核心代码**，帮你整体把握解题框架：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：综合sunzz3183和zhongpeilin的思路，清晰展示“转化数组→计算cnt→计算cost→处理循环移位”的完整流程。
* **完整核心代码**：
    ```cpp
    #include<bits/stdc++.h>
    #define int long long
    using namespace std;
    const int N=3e6+2, mod=1e9+7;
    int n, a[N], l[N], r[N], b[N]; // b是cnt的前缀和，l/r是左右cost的前缀和

    void solve() {
        cin >> n;
        for(int i=1; i<=n; i++) cin >> a[i];
        int maxa = *max_element(a+1, a+n+1);
        for(int i=1; i<=3*n; i++) a[i] = maxa - a[(i-1)%n +1]; // 转化+破环成链（3倍长度）

        // 计算cnt的前缀和b
        for(int i=1; i<=3*n; i++) b[i] = b[i-1] + max(a[i]-a[i-1], 0LL);

        // 找最大值的位置pos（转化后的a[pos]=0）
        int pos=0;
        for(int i=n+1; i<=2*n; i++) if(a[i]==0) pos=i;

        // 计算右边的cost：r[j]表示从pos+1到pos+j的cost
        stack<pair<int, int>> st; // 存储（高度h，长度w）
        int num=0;
        for(int i=pos+1, j=1; i<=pos+n; i++, j++) {
            int sum=1;
            while(!st.empty() && a[i] <= st.top().first) { // 弹出比当前高的区间
                int h=st.top().first, w=st.top().second; st.pop();
                num = (num + mod - w*(h - a[i])%mod) % mod; // 减去多余的长度
                sum += w;
            }
            r[j] = (a[i] + (num*2)%mod + r[j-1]) % mod; // 增量公式：2*num + a[i]
            num += a[i];
            st.push({a[i], sum});
        }

        // 计算左边的cost：l[j]表示从pos-j到pos-1的cost（反向处理）
        while(!st.empty()) st.pop();
        num=0;
        for(int i=pos-1, j=1; i>=pos-n; i--, j++) {
            int sum=1;
            while(!st.empty() && a[i] <= st.top().first) {
                int h=st.top().first, w=st.top().second; st.pop();
                num = (num + mod - w*(h - a[i])%mod) % mod;
                sum += w;
            }
            l[j] = (a[i] + (num*2)%mod + l[j-1]) % mod;
            num += a[i];
            st.push({a[i], sum});
        }

        // 处理每个循环移位的答案
        pos -= n; // 调整pos到1~n的范围
        for(int i=1; i<=n; i++) {
            int cnt = b[n+i-1] - b[i] + a[i]; // 计算当前移位的cnt
            int L = (pos >= i) ? (pos - i) : (pos + n - i); // 左边的长度
            int R = n - 1 - L; // 右边的长度
            int cost = (l[L] + r[R]) % mod; // 左右cost相加
            cout << cnt << " " << cost << endl;
        }
    }

    signed main() {
        ios::sync_with_stdio(false);
        int T; cin >> T;
        while(T--) solve();
        return 0;
    }
    ```
* **代码解读概要**：  
  1. **转化数组**：把原数组变成`maxa - a[i]`，并复制3倍长度（破环成链）；  
  2. **计算cnt前缀和**：用`b`数组存储前`i`个元素的`cnt`总和；  
  3. **找最大值位置**：转化后的数组中`a[pos]=0`，从这里断环成链；  
  4. **计算左右cost**：用单调栈分别处理右边（`r`数组）和左边（`l`数组）的`cost`；  
  5. **处理循环移位**：每个移位的`cnt`用`b`数组的差计算，`cost`用`l`和`r`数组相加。


<code_intro_selected>
接下来剖析**关键代码片段**，看看单调栈是怎么工作的：
</code_intro_selected>

**题解一核心片段：计算右边的cost**
* **亮点**：用单调栈维护“高度递增的区间”，快速计算`num`（当前区间长度总和）。
* **核心代码片段**：
    ```cpp
    stack<pair<int, int>> st;
    int num=0;
    for(int i=pos+1, j=1; i<=pos+n; i++, j++) {
        int sum=1;
        while(!st.empty() && a[i] <= st.top().first) {
            int h=st.top().first, w=st.top().second; st.pop();
            num = (num + mod - w*(h - a[i])%mod) % mod;
            sum += w;
        }
        r[j] = (a[i] + (num*2)%mod + r[j-1]) % mod;
        num += a[i];
        st.push({a[i], sum});
    }
    ```
* **代码解读**：  
  - `st`是单调栈，存储`(h, w)`：`h`是区间的高度，`w`是这个高度的区间长度总和；  
  - `sum`是当前元素`a[i]`能合并的前面的区间长度（比如前面有一个高度为5的区间，长度为3，当前`a[i]=3`，那么`sum=1+3=4`）；  
  - `while`循环：弹出栈顶所有比`a[i]`高的区间，因为这些区间不能再延长到`i`的位置，要减去它们多余的长度（`w*(h-a[i])`）；  
  - `r[j]`的计算：`a[i]`是新增的`a[i]`个长度为1的区间（每个贡献1），`2*num`是所有现有区间延长1的贡献（每个区间长度`c`变成`c+1`，增量是`2c`），所以总增量是`a[i] + 2*num`，加上之前的`r[j-1]`就是当前的`r[j]`；  
  - `num += a[i]`：新增的`a[i]`个区间，每个长度加1，所以`num`增加`a[i]`。  
* 💡 **学习笔记**：单调栈的“弹出”操作是为了维护“高度递增”，确保我们只计算“可延长的区间”，这样`num`始终是当前所有能延长的区间长度总和。


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你更直观地“看”到算法运行过程，我设计了一个**8位像素风的动画**，主题是“像素小工匠削积木”！
</visualization_intro>

### **动画设计细节**
- **风格与场景**：仿照FC红白机的像素风格（16色调色板），背景是浅灰色的工作台，数组元素用不同高度的“木质积木”表示（高度=转化后的`a[i]`），单调栈用“蓝色方块”堆叠在右侧。
- **核心演示步骤**：
  1. **数组转化**：原数组的“彩色积木”（比如`[1,3,2]`）变成“木质积木”（`maxa=3`，转化后`[2,0,1]`），伴随“叮”的音效。
  2. **计算cnt**：用“红色箭头”从左到右扫过每个积木，箭头向上表示`a[i]>a[i-1]`（新增操作），箭头向下表示`a[i]<a[i-1]`（不新增），底部的“计数器”实时显示`cnt`的总和。
  3. **计算cost（单调栈）**：
     - 右侧的“蓝色方块”堆叠表示单调栈，每个方块显示`(h, w)`；
     - 处理`a[i]`时，如果`a[i]`比栈顶高，“绿色方块”从栈顶生长出来（延长区间），`num`计数器增加；
     - 如果`a[i]`比栈顶低，“黄色方块”从栈顶消失（弹出区间），`num`计数器减少；
     - 每次计算`r[j]`时，底部的“硬币罐”会增加相应的硬币数（用像素数字显示）。
- **交互与音效**：
  - 控制面板有“单步执行”“自动播放”（速度滑块）“重置”按钮；
  - 新增操作时播放“滴”的音效，弹出区间时播放“嗒”的音效，计算`r[j]`时播放“叮”的音效；
  - 完成所有步骤后，播放“胜利”的8位音乐，积木变成“金色”，硬币罐显示总`cost`。


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握了本题的思路，可以解决很多“区间操作”和“单调栈”的问题！
</similar_problems_intro>

### **通用思路迁移**
- **积木大赛模型**：所有“区间加/减到全相同”的问题，都可以用“相邻差的正数和”计算最小操作次数；
- **单调栈维护区间**：需要计算“区间长度的平方和”“区间最值”等问题，都可以用单调栈优化。

### **洛谷练习推荐**
1. **洛谷 P5019 积木大赛**  
   🗣️ **推荐理由**：本题的“原型”！直接考察“最小操作次数”的计算，帮你巩固基础。
2. **洛谷 P1969 积木大赛 II**  
   🗣️ **推荐理由**：在积木大赛的基础上，增加了“区间加”的操作，需要用单调栈维护区间信息，是本题的进阶练习。
3. **洛谷 P2894 [USACO08FEB]Hotel G**  
   🗣️ **推荐理由**：用单调栈维护“最长空房间区间”，和本题的“可延长区间”思路类似，帮你拓展单调栈的应用场景。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
优质题解里的“踩坑经验”很宝贵，比如：
</insights_intro>

> **参考经验（来自 sunzz3183）**：“一开始我没搞懂`cost`的增量公式，后来画了张图，把每个区间的长度变化列出来，才发现平方和的增量是`2c+1`，总和就是`2*num + a[i]`。”  
> **点评**：这位作者的经验很实用——当你看不懂公式时，**动手画图**或**举小例子**（比如`num=3`，`a[i]=2`，增量是`2*3+2=8`，验证一下：3个区间各延长1，增量是`2*1+2*1+2*1=6`，加上2个新区间的`1+1=2`，总和8，对！），比死记公式管用多了！


<conclusion>
这道题的核心是“问题转化”和“单调栈的应用”。记住：**遇到复杂问题，先找经典模型**（比如积木大赛），**遇到需要维护区间信息的问题，试试单调栈**！多画图、多举小例子，你会越来越厉害的！下次我们再一起挑战更难的题目吧！💪
</conclusion>

---

---
处理用时：116.54秒