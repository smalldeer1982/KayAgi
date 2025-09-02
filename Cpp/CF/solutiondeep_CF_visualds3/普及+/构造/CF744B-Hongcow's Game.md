# 题目信息

# Hongcow's Game

## 题目描述

This is an interactive problem. In the interaction section below you will see the information about flushing the output.

In this problem, you will be playing a game with Hongcow. How lucky of you!

Hongcow has a hidden $ n $ by $ n $ matrix $ M $ . Let $ M_{i,j} $ denote the entry $ i $ -th row and $ j $ -th column of the matrix. The rows and columns are labeled from $ 1 $ to $ n $ .

The matrix entries are between $ 0 $ and $ 10^{9} $ . In addition, $ M_{i,i}=0 $ for all valid $ i $ . Your task is to find the minimum value along each row, excluding diagonal elements. Formally, for each $ i $ , you must find ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF744B/60abf7e287a9efbab7664bfef9cac9ebdb2e6b1f.png).

To do this, you can ask Hongcow some questions.

A question consists of giving Hongcow a subset of distinct indices $ {w_{1},w_{2},...,w_{k}} $ , with $ 1<=k<=n $ . Hongcow will respond with $ n $ integers. The $ i $ -th integer will contain the minimum value of $ min_{1<=j<=k}M_{i,wj} $ .

You may only ask Hongcow at most $ 20 $ questions — he thinks you only need that many questions answered.

When you are ready to answer, print out a single integer $ -1 $ on its own line, then $ n $ integers on the next line. The $ i $ -th integer should be the minimum value in the $ i $ -th row of the matrix, excluding the $ i $ -th element. Do not forget to flush the final answer as well. Printing the answer does not count as asking a question.

You will get Wrong Answer verdict if

- Your question or answers are not in the format described in this statement.
- You ask strictly more than $ 20 $ questions.
- Your question contains duplicate indices.
- The value of $ k $ in your question does not lie in the range from $ 1 $ to $ n $ , inclusive.
- Your final answer is not correct.

 You will get Idleness Limit Exceeded if you don't print anything or if you forget to flush the output, including for the final answer (more info about flushing output below).

## 说明/提示

In the first sample, Hongcow has the hidden matrix

`<br></br>[<br></br> [0, 3, 2],<br></br> [5, 0, 7],<br></br> [4, 8 ,0],<br></br>]<br></br>`Here is a more readable version demonstrating the interaction. The column on the left represents Hongcow, while the column on the right represents the contestant.

`<br></br>3<br></br>              3<br></br>              1 2 3<br></br>0 0 0<br></br>              1<br></br>              3<br></br>2 7 0<br></br>              2<br></br>              1 2<br></br>0 0 4<br></br>              1<br></br>              2<br></br>3 0 8<br></br>              1<br></br>              1<br></br>0 5 4<br></br>              -1<br></br>              2 5 4<br></br>`For the second sample, it is possible for off-diagonal elements of the matrix to be zero.

## 样例 #1

### 输入

```
3
0 0 0
2 7 0
0 0 4
3 0 8
0 5 4```

### 输出

```
3
1 2 3
1
3
2
1 2
1
2
1
1
-1
2 5 4
```

## 样例 #2

### 输入

```
2
0 0
0 0```

### 输出

```
1
2
1
1
-1
0 0```

# AI分析结果

---
# 💡 Kay的C++算法解析：Hongcow's Game 深入学习指南 💡

<introduction>
  今天我们来挑战一道**交互式编程题**——《Hongcow's Game》！这道题需要我们通过“问问题”的方式，找出矩阵每行非对角线的最小值。听起来有点像“猜谜游戏”，但其实藏着**二进制拆分**的巧妙思路。跟着Kay一步步拆解，你会发现它其实很有趣～
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：二进制拆分（编程技巧应用）

🗣️ **初步分析**：
解决这道题的关键，在于**避开对角线的0干扰**——因为矩阵的对角线元素都是0，如果我们的问题包含了第`i`列（对应第`i`行的对角线），那么第`i`行的结果肯定是0，这会打乱我们找最小值的计划。

那怎么让每个非对角线元素`M[i][j]`（`j≠i`）都能“安全”地被询问到呢？这里要用到**二进制拆分**的思路——把每个列号看成二进制数，比如列3是`11`，列5是`101`。对于任意`j≠i`，`i`和`j`的二进制至少有一位不同（比如`i=3`是`11`，`j=5`是`101`，第2位不同）。

我们的策略是：**枚举每一位二进制位**（比如第`k`位），分别询问“所有第`k`位为1的列”和“所有第`k`位为0的列”。这样一来：
- 对于第`i`行，如果`i`的第`k`位是1，那么“第`k`位为1的列”包含`i`列，结果是0，直接跳过；
- 如果`i`的第`k`位是0，那么“第`k`位为1的列”**不包含**`i`列，此时询问结果是该行在这些列中的最小值，可以用来更新答案！

同理，询问“第`k`位为0的列”时，只要`i`的第`k`位是1，结果就有效。这样，每个`M[i][j]`都会在某一次询问中被包含，且不会被0干扰～

**可视化设计思路**：我们会用8位像素风格展示矩阵和询问过程——比如用不同颜色的方块代表“当前询问的列”“有效更新的行”，用闪烁效果突出“正在处理的二进制位”。配合“叮”的音效提示有效更新，让你直观看到每个最小值是怎么“凑出来”的～


## 2. 精选优质题解参考

<eval_intro>
我从**思路清晰度、代码可读性、算法有效性**三个维度筛选了3份优质题解，它们都完美贴合二进制拆分的核心思路，非常值得学习～
</eval_intro>

**题解一：作者suxxsfe（赞：5）**
* **点评**：这份题解的逻辑最“干净”——直接枚举0到9位二进制（覆盖1024以内的列号），对每个位分别处理“为1的列”和“为0的列”。代码里用`reg`寄存器优化（虽然现在编译器自动优化了，但能看出作者的严谨），变量名`a[]`（存每行最小值）、`cnt`（统计列数）都很直观。最棒的是**边界处理**——当某类列数为0时直接跳过，避免无效询问，完美符合题目“最多20次”的要求。

**题解二：作者封禁用户（赞：4）**
* **点评**：这份题解的思路和题解一一致，但多了一个`ds()`函数计算二进制位数（比如`n=3`时返回2，因为`3=11`有2位）。虽然这个函数可以用`log2(n)+1`代替，但它把“计算需要枚举多少位”的过程显性化了，适合新手理解“为什么要枚举到10位”。代码结构清晰，注释虽然少，但关键步骤（如跳过对角线列、更新最小值）都很明确。

**题解三：作者hongshixiaobai（赞：1）**
* **点评**：这份题解的亮点是用`qry[]`数组存每次询问的列号，避免重复遍历——比如枚举第`i`位时，先把所有“第`i`位为1的列”存入`qry`，再输出。这种“先收集再输出”的方式更高效，也更符合编程中的“模块化”思想。另外，作者用`long long`定义`ans[]`，避免了大数溢出（题目中元素可达1e9），考虑很周全～


## 3. 核心难点辨析与解题策略

<difficulty_intro>
这道题的“坑”主要在**如何避开0干扰**和**用有限次数覆盖所有情况**。结合优质题解，我总结了3个核心关键点：
</difficulty_intro>

1. **难点1：如何避免对角线的0干扰？**
    * **分析**：关键是让每个非对角线元素`M[i][j]`所在的列`j`，在至少一次询问中**不与`i`列同时出现**。二进制拆分刚好满足这个条件——因为`i`和`j`至少有一位不同，对应位的询问会把它们“分开”。比如`i=3（11）`，`j=5（101）`，第2位不同，询问“第2位为1的列”时，`i`的第2位是0，所以`i`列不在询问中，`j`列在，结果有效！
    * 💡 **学习笔记**：二进制拆分是“拆分问题、覆盖所有可能”的神器～

2. **难点2：如何用≤20次询问覆盖所有情况？**
    * **分析**：每个二进制位对应2次询问（该位为0/1），而`2^20`是1e6，足够覆盖`n`的所有可能（题目中`n`不会超过1e3）。比如枚举10位，刚好20次询问，完美符合要求！
    * 💡 **学习笔记**：要学会用“二进制位数”估算询问次数，这是交互式问题的常用技巧～

3. **难点3：如何维护每行的最小值？**
    * **分析**：用一个数组`ans[]`初始化为极大值（比如`0x3f3f3f3f`），每次得到有效结果（即不包含`i`列的询问）时，用`min(ans[i], 当前结果)`更新。这样，最后`ans[]`里存的就是每行非对角线的最小值～
    * 💡 **学习笔记**：“初始极大值+逐步取min”是找最小值的标准套路！


### ✨ 解题技巧总结
- **技巧1：二进制拆分**：把问题拆分成“每一位的选择”，用有限步骤覆盖所有可能；
- **技巧2：无效结果跳过**：遇到包含对角线的询问结果（0），直接跳过，不更新；
- **技巧3：模块化收集**：用数组存每次询问的列号，避免重复遍历，提高代码效率；


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**综合所有优质题解的通用实现**——它结合了“二进制枚举”“模块化收集”“边界处理”的优点，逻辑清晰，容易理解～
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了3份优质题解的思路，优化了列号收集的方式，更符合新手的阅读习惯。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <cstring>
    #include <algorithm>
    using namespace std;

    const int MAXN = 1005;
    long long ans[MAXN];  // 存每行最小值，用long long避免溢出
    int qry[MAXN];        // 存本次询问的列号

    int main() {
        int n;
        cin >> n;
        memset(ans, 0x3f, sizeof(ans));  // 初始化为极大值

        // 枚举二进制位0~19（足够覆盖n≤1e5的情况）
        for (int bit = 0; bit < 20; ++bit) {
            int cnt = 0;
            // 收集第bit位为1的列
            for (int j = 1; j <= n; ++j) {
                if (j & (1 << bit)) {
                    qry[++cnt] = j;
                }
            }
            if (cnt > 0) {  // 有列需要询问
                cout << cnt << endl;
                for (int j = 1; j <= cnt; ++j) {
                    cout << qry[j] << " ";
                }
                cout << endl;
                cout.flush();  // 必须刷新输出！

                // 读取结果并更新ans
                for (int i = 1; i <= n; ++i) {
                    long long res;
                    cin >> res;
                    if (!(i & (1 << bit))) {  // i的bit位不是1，结果有效
                        ans[i] = min(ans[i], res);
                    }
                }
            }

            cnt = 0;
            // 收集第bit位为0的列
            for (int j = 1; j <= n; ++j) {
                if (!(j & (1 << bit))) {
                    qry[++cnt] = j;
                }
            }
            if (cnt > 0) {  // 有列需要询问
                cout << cnt << endl;
                for (int j = 1; j <= cnt; ++j) {
                    cout << qry[j] << " ";
                }
                cout << endl;
                cout.flush();  // 必须刷新输出！

                // 读取结果并更新ans
                for (int i = 1; i <= n; ++i) {
                    long long res;
                    cin >> res;
                    if (i & (1 << bit)) {  // i的bit位是1，结果有效
                        ans[i] = min(ans[i], res);
                    }
                }
            }
        }

        // 输出最终结果
        cout << "-1" << endl;
        for (int i = 1; i <= n; ++i) {
            cout << ans[i] << " ";
        }
        cout << endl;
        cout.flush();

        return 0;
    }
    ```
* **代码解读概要**：
    > 1. 初始化`ans[]`为极大值，准备存每行最小值；
    > 2. 枚举每一位二进制位（0~19），对每个位做两件事：
    >    - 收集所有“该位为1的列”，询问并更新有效行的`ans`；
    >    - 收集所有“该位为0的列”，询问并更新有效行的`ans`；
    > 3. 最后输出`-1`和`ans[]`，完成任务！


<code_intro_selected>
接下来看3份优质题解的**核心片段**，学习它们的亮点～
</code_intro_selected>

**题解一：作者suxxsfe**
* **亮点**：直接枚举0~9位（覆盖小n的情况），代码简洁，边界处理到位。
* **核心代码片段**：
    ```cpp
    for(reg int cnt,i=0;i<10;i++){  // 枚举0~9位
        cnt=0;
        for(reg int j=1;j<=n;j++)if(j&(1<<i)) cnt++;
        if(!cnt) goto NEXT;  // 没有列，跳过
        printf("%d\n",cnt);
        for(reg int j=1;j<=n;j++)if(j&(1<<i)) printf("%d ",j);EN;
        std::fflush(stdout);
        for(reg int j=1;j<=n;j++){
            cnt=read();
            if(j&(1<<i)) continue;  // 跳过对角线列
            a[j]=std::min(a[j],cnt);
        }
        NEXT:;
        // 处理该位为0的列（类似上面）
    }
    ```
* **代码解读**：
    > 这段代码用`reg`优化循环变量（老式但有效），用`goto`跳过无效询问（虽然`goto`不推荐，但这里逻辑很清晰）。`read()`函数是快速读入（处理大数据），`EN`是换行宏定义。关键是**跳过对角线列**的判断：如果`j`的第`i`位是1，说明这次询问包含`j`列，结果是0，直接跳过！
* 💡 **学习笔记**：用`goto`处理边界条件是可以的，但要注意逻辑清晰～

**题解二：作者封禁用户**
* **亮点**：用`ds()`函数计算需要枚举的位数，显性化“为什么枚举到10位”。
* **核心代码片段**：
    ```cpp
    int ds(int q){  // 计算q的二进制位数
        int tmp=0;
        while(q){ q/=2; tmp++; }
        return tmp;
    }
    int main(){
        cin>>n;
        for(int i=1;i<=n;i++) a[i]=1e9+7;
        for(int i=0;i<ds(n);i++){  // 枚举到n的二进制位数
            // 处理该位为1的列（类似通用代码）
        }
    }
    ```
* **代码解读**：
    > `ds()`函数计算`n`的二进制位数（比如`n=3`返回2），这样枚举的位数刚好覆盖`n`的所有列号，不会多也不会少。比如`n=5`（101），`ds(n)=3`，枚举0~2位，刚好6次询问，远小于20次！
* 💡 **学习笔记**：把“计算位数”的过程写成函数，让代码更易懂～

**题解三：作者hongshixiaobai**
* **亮点**：用`qry[]`数组存询问的列号，避免重复遍历，更高效。
* **核心代码片段**：
    ```cpp
    long long qry[100005];  // 存本次询问的列号
    for(i=0;i<=19;i++){
        cnt=0;
        for(j=1;j<=n;j++)
            if(j&(1<<i))
                qry[++cnt]=j;  // 收集列号
        if(!cnt) continue;
        cout<<cnt<<endl;
        for(j=1;j<=cnt;j++) cout<<qry[j]<<' ';  // 输出收集的列号
        cout<<endl;
        // 读取结果并更新ans
    }
    ```
* **代码解读**：
    > 这段代码先用`qry[]`收集所有需要询问的列号，再一次性输出——避免了“遍历两次n”（一次统计数量，一次输出），更高效。比如`n=1000`，这样可以减少1000次循环！
* 💡 **学习笔记**：“先收集再输出”是减少重复操作的好方法～


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你**直观看到二进制拆分的过程**，Kay设计了一个**8位像素风格的动画**——像玩《超级马里奥》一样，看着“询问”如何一步步找出最小值！
</visualization_intro>

### 🎮 动画演示主题：像素探险家找宝藏
我们把矩阵看成一个**像素网格**，每个格子代表`M[i][j]`，对角线格子是红色（0），其他格子是蓝色（数值）。“探险家”（一个像素小人）会根据二进制位的指令，选择要询问的列（用黄色高亮），然后更新每行的最小值（用绿色闪烁）。

### 🎨 设计思路
- **8位风格**：用FC红白机的配色（红、蓝、黄、绿），字体用像素字，营造复古游戏感；
- **核心逻辑演示**：每枚举一个二进制位，屏幕顶部会显示“当前处理位：bit X”，黄色高亮当前询问的列；
- **有效更新提示**：当某行的`ans[i]`被更新时，该行会闪烁绿色，同时播放“叮”的音效；
- **交互控制**：提供“单步”（点击一次走一步）、“自动”（每秒走一步）、“重置”按钮，速度滑块可以调节自动播放的速度。

### 🕹️ 动画帧步骤
1. **初始化场景**：
   - 屏幕左侧显示`n×n`的像素矩阵，对角线是红色（0），其他是蓝色；
   - 屏幕右侧是“控制面板”：按钮（单步/自动/重置）、速度滑块、当前位显示；
   - 背景播放8位风格的轻快BGM（比如《超级马里奥》的背景音乐）。

2. **处理第bit位**：
   - 顶部显示“当前处理位：bit 0”；
   - 黄色高亮所有“第0位为1的列”（比如列1、3、5...）；
   - 探险家走到这些列前，点击“询问”，屏幕下方弹出“询问结果”；
   - 对于每一行，如果该行的第0位不是1（结果有效），该行闪烁绿色，`ans[i]`更新为更小的值，同时播放“叮”的音效。

3. **处理第bit位为0的列**：
   - 重复步骤2，但黄色高亮“第0位为0的列”（比如列2、4、6...）；
   - 同样更新有效行的`ans[i]`，闪烁绿色+“叮”音效。

4. **完成所有位**：
   - 所有位处理完毕后，屏幕中央弹出“任务完成！”，播放胜利音效（比如《魂斗罗》的通关音乐）；
   - 矩阵的每一行显示最终的`ans[i]`（绿色字体），对角线保持红色。

### 📝 旁白提示
- （处理bit 0时）“现在我们处理第0位！黄色的列是第0位为1的列～”；
- （有效更新时）“看！第3行的最小值更新了，因为这次询问没有包含第3列（对角线）～”；
- （完成时）“所有位处理完毕！绿色的数字就是每行的最小值啦～”。


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
二进制拆分的思路不仅能解决这道题，还能用于**覆盖所有可能、优化询问次数**的问题。比如：
</similar_problems_intro>

### 🌐 通用思路迁移
- **问题1**：找数组中所有数的“不同位组合”；
- **问题2**：交互式问题中，用最少次数问出隐藏的数；
- **问题3**：优化“枚举所有子集”的时间复杂度（比如从`2^n`降到`n`次）。

### 📚 洛谷练习推荐
1. **洛谷 P1028 数的计算**
   - 🗣️ **推荐理由**：这道题需要用递归+记忆化，但核心是“二进制拆分”的思想——把数拆分成更小的部分，覆盖所有可能的情况。
2. **洛谷 P3374 树状数组1**
   - 🗣️ **推荐理由**：树状数组的核心就是“二进制拆分”——用二进制位快速定位需要更新/查询的区间，和本题的思路异曲同工。
3. **洛谷 P4097 【模板】线性基**
   - 🗣️ **推荐理由**：线性基是处理异或问题的神器，其核心也是“二进制拆分”——把数拆成二进制位，逐位处理，和本题的“逐位询问”思路一致。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
3份题解的作者都提到了**“二进制拆分的通用性”**，比如第一个作者说“这种思路在bzoj的图论题中也用过”，第三个作者提到“用qry数组收集列号能减少错误”。这些心得很有用：
</insights_intro>

> **参考经验 (来自suxxsfe)**：“这种二进制拆分的思路很常见，之前在bzoj某图论题中，就是用‘两个点至少有一个二进制位不同’来优化建边的。”
>
> **点评**：二进制拆分是“通用工具”，不仅能解决本题的交互式问题，还能用于图论、动态规划等领域。遇到“覆盖所有可能”的问题时，先想想“能不能用二进制拆分解构？”


<conclusion>
这道题的核心是**二进制拆分+避开干扰**，通过“逐位询问”的方式，用20次询问覆盖所有可能的有效情况。希望这份指南能帮你理解“如何用二进制解决交互式问题”——记住，编程的乐趣在于“用巧妙的思路解决看似复杂的问题”！下次我们再一起挑战更有趣的题目～💪
</conclusion>
---

---
处理用时：143.86秒