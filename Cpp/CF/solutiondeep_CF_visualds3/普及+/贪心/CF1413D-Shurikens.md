# 题目信息

# Shurikens

## 题目描述

Tenten runs a weapon shop for ninjas. Today she is willing to sell $ n $ shurikens which cost $ 1 $ , $ 2 $ , ..., $ n $ ryo (local currency). During a day, Tenten will place the shurikens onto the showcase, which is empty at the beginning of the day. Her job is fairly simple: sometimes Tenten places another shuriken (from the available shurikens) on the showcase, and sometimes a ninja comes in and buys a shuriken from the showcase. Since ninjas are thrifty, they always buy the cheapest shuriken from the showcase.

Tenten keeps a record for all events, and she ends up with a list of the following types of records:

- + means that she placed another shuriken on the showcase;
- - x means that the shuriken of price $ x $ was bought.

Today was a lucky day, and all shurikens were bought. Now Tenten wonders if her list is consistent, and what could be a possible order of placing the shurikens on the showcase. Help her to find this out!

## 说明/提示

In the first example Tenten first placed shurikens with prices $ 4 $ and $ 2 $ . After this a customer came in and bought the cheapest shuriken which costed $ 2 $ . Next, Tenten added a shuriken with price $ 3 $ on the showcase to the already placed $ 4 $ -ryo. Then a new customer bought this $ 3 $ -ryo shuriken. After this she added a $ 1 $ -ryo shuriken. Finally, the last two customers bought shurikens $ 1 $ and $ 4 $ , respectively. Note that the order $ [2, 4, 3, 1] $ is also valid.

In the second example the first customer bought a shuriken before anything was placed, which is clearly impossible.

In the third example Tenten put all her shurikens onto the showcase, after which a customer came in and bought a shuriken with price $ 2 $ . This is impossible since the shuriken was not the cheapest, we know that the $ 1 $ -ryo shuriken was also there.

## 样例 #1

### 输入

```
4
+
+
- 2
+
- 3
+
- 1
- 4```

### 输出

```
YES
4 2 3 1```

## 样例 #2

### 输入

```
1
- 1
+```

### 输出

```
NO```

## 样例 #3

### 输入

```
3
+
+
+
- 2
- 1
- 3```

### 输出

```
NO```

# AI分析结果


### 💡 Kay的C++算法解析：Shurikens 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`模拟`与`贪心策略`  
🗣️ **初步分析**：
> 本题要求验证操作序列的合法性并还原放置顺序。想象你经营一家武器店，每次添加武器时放入未知价格的飞镖，而顾客总是买走最便宜的飞镖。解题关键在于**逆向思维**——就像倒放电影胶片，从最后一步开始回溯验证。  
> - **核心难点**：确保每次购买时被买走的飞镖确实是当前最小。逆向处理时，购买操作（`- x`）相当于把飞镖放回展柜，添加操作（`+`）相当于取走飞镖。此时必须保证后放回的飞镖价格 ≤ 先放回的飞镖（即栈顶元素），否则说明正序操作违反"总是购买最便宜"规则。
> - **可视化设计**：将设计一个**像素风时间倒流动画**：展柜用堆叠的像素方块表示，不同颜色代表不同价格（深色=高价）。购买操作时飞镖从右侧滑入展柜（伴随"叮"音效），添加操作时飞镖向左弹出消失（"嗖"音效）。若新飞镖价格 > 栈顶价格，整个屏幕闪烁红光并播放警报音。

---

#### 2. 精选优质题解参考
<eval_intro>以下题解在思路清晰性、代码规范性和算法优化方面表现突出（均≥4★）：</eval_intro>

**题解一（AFOier）**  
* **点评**：采用倒序栈处理，思路如同倒放录像带般巧妙。代码中`sta`栈存储待放置的飞镖价格，遇到`-`压栈，遇到`+`弹栈赋值。亮点在于仅用**单栈和15行代码**就高效完成验证与还原，边界处理严谨（空栈检测）。变量名`sta`/`cnt`简洁但含义明确，适合竞赛直接使用。

**题解四（AlanSP）**  
* **点评**：创新性用正序处理+标记维护。核心在于`tag`数组动态记录栈内最小值限制，遇到`- x`操作时立即校验`x > tag[栈顶]`。亮点是**实时更新最小值标记**避免后效性问题，代码中`max(tag[stack])`的连锁更新逻辑尤为精妙。

**题解五（NightmareAlita）**  
* **点评**：双栈结构清晰展现逆向思维本质。用`s`栈暂存购买操作的飞镖，`ans`栈收集放置顺序。亮点是**物理模拟操作过程**：如同把飞镖从暂存区(`s`)转移到答案区(`ans`)，代码可读性极强，适合初学者理解。

---

#### 3. 核心难点辨析与解题策略
<difficulty_intro>解决本题需突破三个关键难点：</difficulty_intro>

1.  **逆向思维转换**  
    * **分析**：正序模拟需动态维护最小值，但逆向处理将"购买"转为"放置"后，只需保证后放置的飞镖 ≤ 先放置的（栈顶）。这类似于叠盘子——后放的必须更小才能被先取走。
    * 💡 **学习笔记**：当问题存在"后效性"时，尝试逆向思考往往能化繁为简。

2.  **操作序列的实时验证**  
    * **分析**：必须在每个`- x`操作时立即检查合法性。题解一通过倒序压栈时校验`x > sta[cnt]`，题解四通过`tag`数组预判后续最小值，本质都是**用栈维护价格单调性**。
    * 💡 **学习笔记**：栈结构天然适合处理"最后进入最先检查"的场景。

3.  **边界与异常处理**  
    * **分析**：两类非法情况：① 购买时展柜为空；② 添加操作时无飞镖可取（逆向处理的弹栈空）。所有优质题解都在弹栈/压栈前进行空栈检测。
    * 💡 **学习笔记**：边界检测应**前置**在操作执行前，避免部分修改后状态不一致。

### ✨ 解题技巧总结
- **逆向突破法**：对操作序列问题，从结尾开始回溯常能简化状态管理。
- **数据结构语义化**：如用`tag`数组显式记录栈内最小值约束（题解四），比隐式推断更可靠。
- **单调性维护**：栈内元素保持单调性（本题要求非严格递减）是验证合法性的核心。

---

#### 4. C++核心代码实现赏析
<code_intro_overall>以下通用实现改编自题解一，融合边界检测与逆向处理精华：</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：综合题解一和题解五的逆向栈思路，完整展示输入处理到结果输出。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <vector>
    using namespace std;
    int main() {
        int n;
        cin >> n;
        vector<char> ops(2*n);
        vector<int> nums(2*n, 0), ans(2*n, 0), stack;
        
        // 输入处理
        for (int i = 0; i < 2*n; i++) {
            cin >> ops[i];
            if (ops[i] == '-') cin >> nums[i];
        }
        
        // 逆向处理
        for (int i = 2*n-1; i >= 0; i--) {
            if (ops[i] == '-') {
                if (!stack.empty() && nums[i] > stack.back()) {
                    cout << "NO" << endl;
                    return 0;
                }
                stack.push_back(nums[i]);
            } else {
                if (stack.empty()) {
                    cout << "NO" << endl;
                    return 0;
                }
                ans[i] = stack.back();
                stack.pop_back();
            }
        }
        
        // 输出结果
        cout << "YES" << endl;
        for (int i = 0; i < 2*n; i++) 
            if (ops[i] == '+') cout << ans[i] << " ";
        return 0;
    }
    ```
* **代码解读概要**：
    > ① 读取全部操作序列；② 倒序遍历：遇`-`压栈并校验单调性，遇`+`弹栈记录答案；③ 最终检查栈空状态；④ 输出`+`对应的放置顺序。核心在于`stack`维护价格单调性。

---
<code_intro_selected>精选题解片段解析：</code_intro_selected>

**题解一（AFOier）**
* **亮点**：用原生数组替代STL栈，极致性能优化
* **核心代码片段**：
    ```cpp
    for(int i = n; i >= 1; i--) {
        if(opt[i] == '-') {
            if(cnt && s[i] > sta[cnt]) return 0; // 单调性校验
            sta[++cnt] = s[i];
        }
        else {
            if(!cnt) return 0; // 空栈检查
            ans[i] = sta[cnt--];
        }
    }
    ```
* **代码解读**：
    > 为什么倒序？因为购买操作(`-`)在逆向时变成"补充库存"，需保证新飞镖(`s[i]`) ≤ 当前库存顶(`sta[cnt]`)。`ans[i]`记录正序中`+`操作放置的价格，最后仅输出这些位置的值。
* 💡 **学习笔记**：原生数组栈在已知最大规模时可提升访问效率。

**题解四（AlanSP）**
* **亮点**：正序处理+动态标记维护最小值约束
* **核心代码片段**：
    ```cpp
    if(op[1]=='-') {
        scanf("%d",&x);
        if(!top || x <= tag[stk[top]]) return 0; // 实时校验
        ans[stk[top]] = x;
        tag[stk[top-1]] = max(tag[stk[top-1]], x); // 连锁更新标记
    }
    ```
* **代码解读**：
    > `tag[stk[top]]`记录该飞镖放入后展柜的最小值限制。当新购买操作发生时，若`x` ≤ 当前栈顶位置的最小值约束，说明存在更小飞镖未被购买，立即判否。`max()`保证标记更新覆盖所有可能路径。
* 💡 **学习笔记**：标记传递法可避免重新扫描栈，提升效率至O(1)。

**题解五（NightmareAlita）**
* **亮点**：双栈物理模拟操作转移
* **核心代码片段**：
    ```cpp
    for (int i = opt.size()-1; i >= 0; i--) {
        if (!opt[i]) { // 对应 '+' 操作
            ans.push(s.top()); 
            s.pop();
        }
        else { // 对应 '-' 操作
            if (!s.empty() && opt[i] > s.top()) return 0;
            s.push(opt[i]);
        }
    }
    ```
* **代码解读**：
    > `s`栈作为中转区：遇`-`（逆向的补充）压栈，遇`+`（逆向的取出）则转移到`ans`栈。最终`ans`栈弹出顺序即正序放置顺序。如同工厂流水线：不合格品（`opt[i] > s.top()`）直接中断生产。
* 💡 **学习笔记**：多个栈协同可清晰分离数据流的不同阶段。

---

#### 5. 算法可视化：像素动画演示
<visualization_intro>
设计**「时间逆转的忍具屋」**像素动画，通过倒序模拟直观展示算法核心：
</visualization_intro>

* **主题**：8-bit像素风忍具店，右侧展柜（栈区），左侧操作日志（倒序滚动）
* **美术设计**：飞镖用16色像素方块表示（浅蓝=1元→深紫=5元），背景FC红白机风格芯片网格

* **动画流程**：
  1. **初始化**：展柜空，操作日志显示最后一条操作（如`- 4`），播放低循环BGM
  2. **购买操作(`-`)**：  
     - 飞镖从右侧滑入展柜（带残影动画）  
     - 若新飞镖价格 > 栈顶飞镖：展柜闪烁红光，播放故障音效  
     - 否则：播放"咔嗒"放置音效，新飞镖停在栈顶
  3. **添加操作(`+`)**：  
     - 栈顶飞镖向左弹出，飞向底部"答案序列"区域  
     - 播放"嗖"的取出音效，答案区点亮对应位置
  4. **结束检测**：  
     - 成功：所有操作处理完时，答案区完整显示序列，播放胜利音效+烟花动画  
     - 失败：立即暂停动画，错误操作项高亮闪烁

* **控制面板**：
  - 速度滑块：调节单步延迟（100ms~2s）
  - 单步/自动模式：空格键逐帧，A键自动播放
  - 重置按钮：R键重启动画
  - 模式切换：T键正序/倒序视角对比

* **游戏化设计**：
  - 每成功处理5个操作，展柜放出像素烟花
  - 最终根据操作速度与准确率结算"忍者等级"
  - 彩蛋：连续10次无错误触发隐藏手里剑皮肤

---

#### 6. 拓展练习与相似问题思考
<similar_problems_intro>
掌握本题的逆向思维与栈应用后，可挑战以下相似问题：
</similar_problems_intro>

* **通用技巧迁移**：  
  栈维护单调性的思想还可用于：  
  ① 实时数据流中位数（对顶堆）  
  ② 直方图最大矩形（单调栈经典应用）  
  ③ 线程调度中的资源分配（如银行家算法）

* **练习推荐（洛谷）**：
  1. **P1886 滑动窗口**  
     🗣️ **推荐理由**：单调队列模板题，强化"动态维护极值"思想
  2. **P3467 PLA-Postering**  
     🗣️ **推荐理由**：单调栈经典应用，理解栈如何避免重复计算
  3. **P1165 日志分析**  
     🗣️ **推荐理由**：栈结构维护历史极值，与本题`tag`数组思路相通

---

#### 7. 学习心得与经验分享
<insights_intro>
题解中这些经验值得注意：
</insights_intro>

> **经验一（AFOier）**：  
> *"倒序处理相当于把操作序列反转，将删除最小值转化为添加元素，此时单调性校验就是核心"*  
> **Kay点评**：逆向思维是算法设计的重要突破口，尤其适合状态转移具有后效性的场景。

> **经验二（AlanSP）**：  
> *"更新标记时一定要和原标记取max！我WA三次才找到这个bug"*  
> **Kay点评**：连锁型状态更新需确保覆盖所有路径，设计初始值（如`tag[0]=0`）很关键。

---

<conclusion>
本次Shurikens题解之旅展示了逆向思维与栈的精妙结合。记住：当正序模拟困难时，不妨尝试"倒放录像带"。用`tag`数组维护状态约束、双栈管理数据流等方法都可迁移至其他场景。继续在洛谷挑战相似问题吧，少年忍者！ 🚀  
</conclusion>

---
处理用时：203.17秒