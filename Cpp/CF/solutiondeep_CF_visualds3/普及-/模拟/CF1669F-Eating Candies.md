# 题目信息

# Eating Candies

## 题目描述

There are $ n $ candies put from left to right on a table. The candies are numbered from left to right. The $ i $ -th candy has weight $ w_i $ . Alice and Bob eat candies.

Alice can eat any number of candies from the left (she can't skip candies, she eats them in a row).

Bob can eat any number of candies from the right (he can't skip candies, he eats them in a row).

Of course, if Alice ate a candy, Bob can't eat it (and vice versa).

They want to be fair. Their goal is to eat the same total weight of candies. What is the most number of candies they can eat in total?

## 说明/提示

For the first test case, Alice will eat one candy from the left and Bob will eat one candy from the right. There is no better way for them to eat the same total amount of weight. The answer is $ 2 $ because they eat two candies in total.

For the second test case, Alice will eat the first three candies from the left (with total weight $ 7 $ ) and Bob will eat the first three candies from the right (with total weight $ 7 $ ). They cannot eat more candies since all the candies have been eaten, so the answer is $ 6 $ (because they eat six candies in total).

For the third test case, there is no way Alice and Bob will eat the same non-zero weight so the answer is $ 0 $ .

For the fourth test case, Alice will eat candies with weights $ [7, 3, 20] $ and Bob will eat candies with weights $ [10, 8, 11, 1] $ , they each eat $ 30 $ weight. There is no better partition so the answer is $ 7 $ .

## 样例 #1

### 输入

```
4
3
10 20 10
6
2 1 4 2 4 1
5
1 2 4 8 16
9
7 3 20 5 15 1 11 8 10```

### 输出

```
2
6
0
7```

# AI分析结果



---
# 💡 Kay的C++算法解析：Eating Candies 深入学习指南 💡

<introduction>
今天我们来一起分析“Eating Candies”这道题。这道题需要我们找到Alice和Bob从左右两端吃糖果时，总重量相等的最大糖果数。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`编程技巧应用（双指针）`

🗣️ **初步分析**：
> 解决“Eating Candies”的关键在于用双指针技巧动态调整左右两端的糖果数量，找到总重量相等的最优解。双指针就像两个“小探险家”，一个从左往右走（代表Alice吃的糖果），一个从右往左走（代表Bob吃的糖果），通过比较两人当前的总重量，调整指针位置，直到找到重量相等的情况。

- **题解思路对比**：题解主要有四种思路：双指针（O(n)）、前缀和+哈希表（O(n logn)）、前缀和+二分（O(n logn)）、双端队列模拟（O(n)）。其中双指针法时间复杂度最低，代码最简洁，是最优解。
- **核心算法流程**：左指针x从左累加重量（sum1），右指针y从右累加重量（sum2），当sum1 < sum2时，x右移增加sum1；当sum1 > sum2时，y左移增加sum2；当sum1 == sum2时，记录当前x+n-y（总糖果数）的最大值。
- **可视化设计**：采用8位像素风格，用两个像素小人分别代表Alice和Bob，左右指针用箭头标记，每次移动指针时播放“滴答”音效，当sum1和sum2相等时播放“叮”的胜利音效，高亮当前总糖果数。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性等方面筛选了以下优质题解（≥4星）：
</eval_intro>

**题解一：IvanZhang2009**
* **点评**：此题解思路非常清晰，直接使用双指针法，时间复杂度O(n)，是最优解法。代码中变量命名简洁（x、y指针，sum1、sum2记录重量），逻辑直白——左指针不断右移，右指针动态调整，确保sum2≥sum1，当相等时更新答案。边界处理严谨（x<=y的循环条件），实践价值高，适合直接用于竞赛。

**题解二：GI录像机**
* **点评**：此题解用前缀和+哈希表，时间复杂度O(n logn)，思路巧妙。通过预处理前缀和存入map，再遍历后缀和查找是否存在相等值，同时判断无交集（i > mp[tsum[i]]）。代码规范（hsum、tsum表示前后缀和），但哈希表查找可能稍慢于双指针，适合理解不同思路。

**题解三：happy_dengziyue**
* **点评**：此题解用前缀和+二分查找，时间复杂度O(n logn)。预处理前缀和和后缀和，枚举每个前缀，二分查找是否存在相等的后缀和。代码中ask函数实现二分逻辑，结构清晰，但二分需要后缀和有序（本题因重量非负，后缀和单调递减），适合练习二分应用。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题时，我们通常会遇到以下关键点，结合优质题解的共性，提炼思考方向和策略：
</difficulty_intro>

1.  **关键点1**：如何高效找到相等的前后缀重量？
    * **分析**：直接枚举所有前后缀组合时间复杂度O(n²)，不可行。优质题解用双指针（动态调整）、哈希表（快速查找）或二分（有序后缀和）优化。双指针法最优，通过一次遍历即可完成。
    * 💡 **学习笔记**：双指针适合处理“两端向中间收缩”的问题，动态调整指针位置能避免重复计算。

2.  **关键点2**：如何避免两人吃的糖果有交集？
    * **分析**：需保证Alice的右边界（x）小于Bob的左边界（y）。双指针法中x<=y的循环条件自然避免交集；哈希表法中i > mp[tsum[i]]显式判断无交集。
    * 💡 **学习笔记**：边界条件（x < y）是保证逻辑正确的关键，需仔细处理。

3.  **关键点3**：如何选择最优算法？
    * **分析**：双指针法时间复杂度最低（O(n)），代码简洁，适合竞赛；哈希表和二分法适合理解不同数据结构的应用。根据题目规模（n≤2e5），双指针是首选。
    * 💡 **学习笔记**：算法选择需考虑时间复杂度和实现难度，双指针在类似问题中常是最优解。

### ✨ 解题技巧总结
<summary_best_practices>
- **双指针动态调整**：通过左右指针移动，动态平衡前后缀重量，避免枚举所有可能。
- **前缀和预处理**：快速计算任意区间的重量和，减少重复计算。
- **边界条件判断**：确保两人吃的糖果无交集（x < y），避免错误解。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
先来看一个高效的通用核心C++实现，基于双指针法，代码简洁且时间复杂度最优。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码来自题解一（IvanZhang2009），采用双指针法，时间复杂度O(n)，是本题最优解。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <algorithm>
    using namespace std;

    const int MAXN = 200005;
    int a[MAXN];

    int main() {
        int t;
        cin >> t;
        while (t--) {
            int n;
            cin >> n;
            for (int i = 0; i < n; ++i) {
                cin >> a[i];
            }
            int x = 0, y = n - 1;
            int sum1 = 0, sum2 = 0, ans = 0;
            while (x <= y) {
                if (sum1 <= sum2) {
                    sum1 += a[x++];
                } else {
                    sum2 += a[y--];
                }
                if (sum1 == sum2) {
                    ans = max(ans, x + (n - y - 1));
                }
            }
            cout << ans << endl;
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取输入，初始化左右指针x、y，分别从左右两端开始。sum1记录Alice的总重量，sum2记录Bob的总重量。循环中，若sum1≤sum2，x右移增加sum1；否则y左移增加sum2。当sum1等于sum2时，计算当前总糖果数（x + (n - y - 1)）并更新最大值。最终输出ans。

---
<code_intro_selected>
接下来剖析优质题解的核心代码片段：
</code_intro_selected>

**题解一：IvanZhang2009**
* **亮点**：双指针法时间复杂度O(n)，代码简洁，动态调整指针位置。
* **核心代码片段**：
    ```cpp
    int x=0,y=n-1;
    int sum1=0,sum2=0,ans=0;
    while(x<=y){
        if(sum1<=sum2) sum1+=a[x++];
        else sum2+=a[y--];
        if(sum1==sum2) ans=max(ans,x+n-y-1);
    }
    ```
* **代码解读**：
    > 左右指针x、y分别从0和n-1开始。sum1是Alice的总重量，sum2是Bob的总重量。循环条件x<=y保证不重叠。若sum1较小，x右移（Alice多吃一颗）；若sum2较小，y左移（Bob多吃一颗）。当sum1等于sum2时，总糖果数是x（Alice吃的数量）加上(n - y - 1)（Bob吃的数量，因为y是当前未吃的最右位置），更新ans为最大值。
* 💡 **学习笔记**：双指针动态调整是关键，每次移动指针都让总重量更接近相等。

**题解二：GI录像机**
* **亮点**：前缀和+哈希表，快速查找相等值。
* **核心代码片段**：
    ```cpp
    map<int, int> mp;
    for (int i = 1; i <= n; i++) {
        hsum[i] = hsum[i-1] + a[i];
        mp[hsum[i]] = i;
    }
    for (int i = n; i >= 1; i--) {
        tsum[i] = tsum[i+1] + a[i];
        if (mp[tsum[i]] && i > mp[tsum[i]]) 
            ans = max(ans, n - i + 1 + mp[tsum[i]]);
    }
    ```
* **代码解读**：
    > 预处理前缀和hsum并存入map（键为重量，值为位置i）。遍历后缀和tsum，若tsum[i]存在于map中，且Bob的起始位置i大于Alice的结束位置mp[tsum[i]]（无交集），则总糖果数是(n - i + 1)（Bob吃的数量）加上mp[tsum[i]]（Alice吃的数量），更新ans。
* 💡 **学习笔记**：哈希表适合快速查找，但需注意无交集的条件。

**题解三：happy_dengziyue**
* **亮点**：前缀和+二分，利用后缀和的单调性。
* **核心代码片段**：
    ```cpp
    int ask(int l,int r,int x){
        int mid, res=-1;
        while(l<=r){
            mid=(l+r)>>1;
            if(sr[mid]==x){ res=mid; break; }
            if(x<sr[mid]) l=mid+1;
            else r=mid-1;
        }
        return res;
    }
    for(int i=1,x;i<=n;++i){
        x=ask(i+1,n,sl[i]);
        if(x!=-1) ans=ma(ans,i+n-x+1);
    }
    ```
* **代码解读**：
    > ask函数在区间[l,r]二分查找是否存在后缀和等于x（sl[i]）。因为后缀和sr[i]单调递减（每次加左边的数），所以可以二分。枚举每个前缀sl[i]，查找是否存在后缀sr[x]等于sl[i]，且x>i（无交集），总糖果数是i（Alice）+ (n - x + 1)（Bob）。
* 💡 **学习笔记**：二分查找适合有序数组，本题后缀和单调递减，满足二分条件。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解双指针法的执行过程，我们设计一个“糖果大冒险”像素动画，用8位风格展示Alice和Bob的吃糖果过程！
</visualization_intro>

  * **动画演示主题**：`像素糖果屋：Alice和Bob的公平挑战`

  * **核心演示内容**：双指针x（Alice）和y（Bob）从左右两端移动，sum1和sum2实时显示重量，当sum1=sum2时，高亮总糖果数。

  * **设计思路简述**：8位像素风格（FC游戏画面）营造轻松氛围，指针移动的“滴答”音效强化操作记忆，相等时的“叮”声增强成就感，帮助记忆关键步骤。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕中间是一排像素糖果（颜色随机，如红、黄、蓝），左右各有一个像素小人（Alice穿粉色，Bob穿蓝色）。
          * 控制面板有“开始/暂停”“单步”“重置”按钮，速度滑块（1x-5x）。
          * 背景播放8位风格的轻快音乐（如《超级玛丽》经典旋律）。

    2.  **初始状态**：
          * x指针（绿色箭头）在最左糖果（位置0），y指针（紫色箭头）在最右糖果（位置n-1）。
          * sum1和sum2显示为0，总糖果数ans显示为0。

    3.  **核心步骤演示**：
          * **指针移动**：若sum1≤sum2，Alice的箭头右移，对应糖果变灰（已吃），sum1增加该糖果重量，播放“滴答”音效；若sum1>sum2，Bob的箭头左移，对应糖果变灰，sum2增加重量，播放“滴答”音效。
          * **相等提示**：当sum1=sum2时，所有已吃糖果闪烁金色，ans更新为当前总糖果数，播放“叮~”胜利音效，屏幕弹出“当前最优！”文字气泡。
          * **边界处理**：当x>y时，循环结束，最终ans高亮显示。

    4.  **交互控制**：
          * 单步执行：点击“单步”按钮，执行一次指针移动，便于观察每一步变化。
          * 自动播放：选择速度后，动画自动运行，适合整体观察流程。
          * 重置：点击后回到初始状态，重新开始。

    5.  **游戏化元素**：
          * 每成功找到一次sum1=sum2，获得10分，积分显示在屏幕上方。
          * 最终得分=ans×10，鼓励学习者寻找最大ans。

  * **旁白提示**：
      * （单步前）“现在sum1=0，sum2=0，Alice先吃一颗！”
      * （指针移动）“sum1现在是10，比sum2大，Bob需要吃一颗！”
      * （相等时）“哇，sum1和sum2都是30了！总糖果数是7，刷新记录！”

<visualization_conclusion>
通过这个像素动画，我们能清晰看到双指针如何动态调整，sum1和sum2如何变化，以及ans如何被更新。在游戏化的氛围中，理解算法变得更有趣！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
双指针和前缀和技巧在类似“两端向中间”的问题中非常实用，我们可以尝试以下题目巩固：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 双指针法适用于需要动态调整左右区间的问题（如两数之和、最长无重复子串）。
      * 前缀和用于快速计算区间和（如子数组和为k的倍数、连续子数组的最大和）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1868 饥饿的奶牛**
          * 🗣️ **推荐理由**：双指针法求最长连续区间，巩固动态调整指针的思路。
    2.  **洛谷 P1102 A-B数对**
          * 🗣️ **推荐理由**：前缀和+哈希表，练习快速查找相等值的技巧。
    3.  **洛谷 P1230 智力大冲浪**
          * 🗣️ **推荐理由**：双指针处理左右区间，结合游戏化场景，提升应用能力。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
题解中未明确提及作者个人心得，但可以总结通用经验：
</insights_intro>

> 调试时可打印sum1、sum2和指针位置，观察是否在正确位置移动。例如，若ans始终为0，可能是循环条件错误（如x<y而非x<=y），或sum相等时未正确计算总糖果数。

**点评**：调试时打印关键变量（sum1、sum2、x、y）是定位错误的有效方法，尤其在双指针问题中，指针位置和sum值的变化是关键。

-----

<conclusion>
本次关于“Eating Candies”的分析就到这里。希望大家通过双指针法、前缀和等技巧的学习，掌握此类问题的解决方法。记住，多动手写代码、调试，才能真正理解算法的核心！下次挑战新题目，我们再见～💪
</conclusion>

-----

---
处理用时：134.14秒