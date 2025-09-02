# 题目信息

# Equalize the Array

## 题目描述

Polycarp was gifted an array $ a $ of length $ n $ . Polycarp considers an array beautiful if there exists a number $ C $ , such that each number in the array occurs either zero or $ C $ times. Polycarp wants to remove some elements from the array $ a $ to make it beautiful.

For example, if $ n=6 $ and $ a = [1, 3, 2, 1, 4, 2] $ , then the following options are possible to make the array $ a $ array beautiful:

- Polycarp removes elements at positions $ 2 $ and $ 5 $ , array $ a $ becomes equal to $ [1, 2, 1, 2] $ ;
- Polycarp removes elements at positions $ 1 $ and $ 6 $ , array $ a $ becomes equal to $ [3, 2, 1, 4] $ ;
- Polycarp removes elements at positions $ 1, 2 $ and $ 6 $ , array $ a $ becomes equal to $ [2, 1, 4] $ ;

Help Polycarp determine the minimum number of elements to remove from the array $ a $ to make it beautiful.

## 样例 #1

### 输入

```
3
6
1 3 2 1 4 2
4
100 100 4 100
8
1 2 3 3 3 2 6 6```

### 输出

```
2
1
2```

# AI分析结果


# 💡 Kay的C++算法解析：Equalize the Array 深入学习指南 💡

<introduction>
今天我们来分析 "Equalize the Array" 这道C++编程题。本指南将帮助你理解题目核心思路，掌握关键算法实现，并通过像素动画直观感受算法运行过程。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`枚举与前缀和优化`

🗣️ **初步分析**：
> 解决本题就像在整理书架：不同高度的书籍（数字出现次数）需要调整成统一高度（相同出现次数C）。核心技巧是先统计每本书的高度（频率统计），然后尝试各种统一高度（枚举C），快速计算需要移走的书籍数量（前缀和优化）。
- 关键思路：统计数字频率→排序→枚举目标C→利用前缀和快速计算最小删除次数
- 算法流程：1) 频率统计 2) 排序频率值 3) 计算前缀和 4) 枚举C计算删除次数
- 可视化设计：像素动画将展示频率直方图，C值滑块移动时，小于C的柱变红（全删），大于C的柱上部变黄（部分删），实时显示总删除量

---

## 2. 精选优质题解参考

<eval_intro>
基于思路清晰性、代码规范性和算法优化度，精选三份优质题解进行深度解析：

**题解一：Frather_**
* **点评**：该题解思路清晰度极佳，完整演示了"离散化→桶排序→前缀和→二分查找"的完整推导链。代码中`bkt[]`桶数组和`sum[]`前缀和变量的命名准确体现了功能边界，特别是对多组数据清空的严谨处理展现了竞赛级代码素养。亮点在于用`lower_bound`高效定位分界点，使复杂度稳定在O(n log n)。

**题解二：registerGen**
* **点评**：解法以数学简洁性见长，创新性使用`psum`(前缀和)和`ssum`(后缀和)双数组优化计算。代码模块化程度高，`rep/per`宏增强可读性，推导公式`psum[i-1] + ssum[i+1] - i*ssum2[i+1]`精炼展现了删除次数的数学本质，是空间换时间的典范。

**题解三：henrytb**
* **点评**：代码实现最为简洁，聚焦问题核心。`bin[]`数组直接存储频率值，通过排序和前缀和快速计算。亮点在于枚举C范围(0~n)的完备性处理，配合`lower_bound`二分查找，即使n较大时也能高效运行，边界条件`id>nn`的处理展现了算法健壮性。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题需突破三个关键难点，结合优质题解策略分析如下：

1.  **难点：删除次数的数学建模**
    * **分析**：如何将"使频率统一为C"转化为可计算的数学表达式？优质题解均采用分段策略：设频率数组b[]，删除次数 = ∑(b[i]|b[i]<C) + ∑(b[i]-C|b[i]>=C)。这要求理解删除操作的本质是处理频率与C的差值。
    * 💡 **学习笔记**：删除次数 = 低频段总和 + 高频段(总和 - C×数量)

2.  **难点：计算效率优化**
    * **分析**：直接双重循环枚举C和频率会导致O(n²)复杂度。策略是预排序后使用前缀和数组pre[]，使每次计算降为O(1)。例如Frather_的解法中，pre[i]表示前i个频率之和，通过二分定位分界点t，删除次数=pre[t-1] + (pre[n]-pre[t-1]) - (n-t+1)×C。
    * 💡 **学习笔记**：排序+前缀和是区间统计问题的黄金搭档

3.  **难点：边界条件处理**
    * **分析**：当C大于最大频率时需全删(pre[n])，当C=0时结果也是pre[n]。henrytb的题解通过`if(id>nn) ans=sum[nn]`优雅处理，而Frather_在循环中特判t>n_的情况，确保逻辑完备。
    * 💡 **学习笔记**：枚举范围必须覆盖[0, max_freq]全区间

### ✨ 解题技巧总结
<summary_best_practices>
提炼三大通用解题技巧：
</summary_best_practices>
-   **频率优先思维**：忽略具体数值，聚焦出现次数分布
-   **数学转换技巧**：将删除操作转化为∑(差值)计算
-   **预处理优化**：排序后立即计算前缀和，避免重复扫描

---

## 4. C++核心代码实现赏析

<code_intro_overall>
综合优质题解，提供可直接运行的通用实现。此代码融合了"离散化+排序+前缀和+枚举"的最佳实践：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：综合Frather_的离散化与henrytb的边界处理，优化变量命名
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>
    #include <map>
    using namespace std;
    
    int main() {
        int T;
        cin >> T;
        while (T--) {
            int n;
            cin >> n;
            vector<int> a(n);
            map<int, int> cntMap;
            
            // 频率统计
            for (int i = 0; i < n; i++) {
                cin >> a[i];
                cntMap[a[i]]++;
            }
            
            // 提取频率并排序
            vector<int> freqs;
            for (auto& kv : cntMap) 
                freqs.push_back(kv.second);
            sort(freqs.begin(), freqs.end());
            
            // 计算前缀和
            vector<int> pre(freqs.size() + 1, 0);
            for (int i = 0; i < freqs.size(); i++)
                pre[i+1] = pre[i] + freqs[i];
            
            // 枚举目标频率C
            int minDel = n;
            for (int i = 0; i < freqs.size(); i++) {
                int C = freqs[i];  // 当前目标频率
                int leftSum = pre[i];  // 小于C的频率和
                int rightCount = freqs.size() - i;  // 大于等于C的频率数量
                int rightSum = pre[freqs.size()] - pre[i];  // 大于等于C的频率和
                int del = leftSum + (rightSum - rightCount * C);
                minDel = min(minDel, del);
            }
            cout << minDel << endl;
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 1) 使用`map`统计原始频率 2) 提取频率值排序 3) `pre[]`存储前缀和 4) 关键计算：删除次数 = 低频段和 + (高频段和 - 高频数量×C) 5) 注意`freqs.size()`是不同数字种类数

---
<code_intro_selected>
精选题解核心片段解析：
</code_intro_selected>

**题解一：Frather_**
* **亮点**：二分查找加速分界点定位
* **核心代码片段**：
    ```cpp
    sort(bkt + 1, bkt + n_ + 1);
    for (int i = 1; i <= n_; i++) sum[i] = sum[i-1] + bkt[i];
    
    for (int C = 1; C <= n; C++) {
        int pos = lower_bound(bkt+1, bkt+n_+1, C) - bkt;
        if (pos > n_) 
            del = sum[n_];  // 全删
        else 
            del = sum[pos-1] + (sum[n_] - sum[pos-1]) - (n_ - pos + 1) * C;
    }
    ```
* **代码解读**：
    > 1) `bkt`存储排序后频率，`sum`为前缀和 2) `lower_bound`找到首个≥C的位置pos 3) 当pos越界说明所有频率<C，需全删(sum[n_]) 4) 否则分两段计算：前pos-1个全删，后面的保留C次
* 💡 **学习笔记**：二分查找将枚举C的复杂度降为O(n log n)

**题解二：registerGen**
* **亮点**：双数组优化避免重复计算
* **核心代码片段**：
    ```cpp
    // cntt[i]: 出现i次的数字种类数
    rep(i,1,n) psum[i] = psum[i-1] + cntt[i]*i;
    per(i,n,1) {
        ssum[i] = ssum[i+1] + cntt[i]*i;
        ssum2[i] = ssum2[i+1] + cntt[i];
    }
    rep(i,1,n) {
        del = psum[i-1] + ssum[i+1] - i*ssum2[i+1];
    }
    ```
* **代码解读**：
    > 1) `psum[i]`：频率≤i的总次数 2) `ssum[i]`：频率≥i的总次数 3) `ssum2[i]`：频率≥i的种类数 4) 删除次数 = 频率<i的总和 + 频率>i的总和 - i×高频种类数
* 💡 **学习笔记**：后缀和数组处理高频段计算更优雅

**题解三：henrytb**
* **亮点**：完备枚举C范围
* **核心代码片段**：
    ```cpp
    sort(bin+1, bin+1+nn);  // bin存储频率
    rep(i,1,nn) sum[i] = sum[i-1] + bin[i];
    
    for(int C=0; C<=n; C++) {
        int id = lower_bound(bin+1, bin+nn+1, C) - bin;
        if(id > nn) 
            del = sum[nn];  // 全删
        else 
            del = sum[id-1] + (sum[nn]-sum[id-1]) - (nn-id+1)*C;
    }
    ```
* **代码解读**：
    > 1) C从0枚举到n保证完备性 2) `id`定位首个≥C的位置 3) `nn-id+1`是频率≥C的种类数 4) 边界处理确保C超范围时逻辑正确
* 💡 **学习笔记**：枚举C∈[0,n]比仅枚举现有频率更易处理边界

-----

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
设计复古像素风动画演示频率调整过程。主题为"频率调音师"，你将通过8-bit界面直观理解前缀和优化策略：
</visualization_intro>

* **动画演示主题**：`像素调音台：通过滑块调整频率阈值C`

* **核心演示内容**：
  1. 左区：原始频率直方图（8-bit柱状图）
  2. 右区：操作面板（开始/单步/滑块控制）
  3. 底部：实时计算公式（随操作高亮变化）

* **设计思路**：采用FC游戏《俄罗斯方块》的像素风格，通过：
  - 柱形高度表意：频率值
  - 颜色编码：蓝色(保留)/红色(全删)/黄色(部分删)
  - 音效反馈：删除操作配"破碎声"，滑块移动配"滴答声"

* **动画帧步骤**：
  1. **初始化阶段**：
      - 左侧生成随机频率柱图（不同高度蓝色像素柱）
      - 右侧控制面板：C=0滑块，公式显示`del = ?`
      - 背景播放8-bit风格BGM

  2. **滑块调整演示**：
      ```markdown
      [柱图]        [控制面板]
      █             C: ────●──── 0
      ██            del = 0 + 0 - 0*0 = 0
      ████
      ```
      - 拖动滑块→C值增大→低于C的柱变红（伴随"咔"声）
      - 高于C的柱：底部留蓝，顶部变黄（"叮"声）

  3. **单步执行模式**：
      - 按右箭头：C+1，柱图更新颜色
      - 当前计算步骤高亮（如`pre[i]=XX`）
      - 音效：有效步"叮"，无效步"嘟"

  4. **AI自动演示**：
      - 点击"AI Run"：滑块自动滑向最优C值
      - 最优解处触发闪光特效+胜利音效
      - 显示"Min Found!"像素艺术字

* **交互控制**：
  - 滑块：实时调节C值（范围0~max_freq）
  - 单步：←/→键微调C值
  - 速度调节：下方速度条控制AI演示速度

* **学习提示**：
  > "注意看！当C=3时红黄区域面积最小，这就是最优解"

-----

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握频率统计算法后，可挑战以下变形问题：
</similar_problems_intro>

* **通用技巧迁移**：
  1. 区间统计优化（前缀和/后缀和）
  2. 枚举目标值+数学优化
  3. 离散化处理大数据范围

* **洛谷题目推荐**：
  1. **P1097 统计数字**  
     🗣️ 基础频率统计，练习离散化与桶排序
  2. **P1638 逛画展**  
     🗣️ 滑动窗口中用频率统计优化，理解"移动区间频率变化"
  3. **P1496 火烧赤壁**  
     🗣️ 离散化+区间合并，强化坐标处理能力

-----

## 7. 学习心得与经验分享

<insights_intro>
题解中提炼的宝贵经验：
</insights_intro>

> **Frather_的调试经验**：
> "多组数据一定要记得清空变量！！！"
> 
> **Kay点评**：这是竞赛常见陷阱。建议封装`init()`函数，在每组数据开头重置：
> ```cpp
> void init() {
>   memset(bkt,0,sizeof(bkt));
>   memset(sum,0,sizeof(sum));
>   // ...
> }
> ```

> **清烛的公式教训**：
> "发现公式错误后重新推导边界条件"
>
> **Kay点评**：数学公式需用小数据验证。推荐测试用例：
> 输入[1,1,2,2] → 频率[2,2] → C=2时del=0

---

<conclusion>
通过本次分析，我们掌握了频率统计问题的核心解法。记住：优秀算法 = 准确建模 + 高效优化。尝试用像素动画可视化你的下一个算法吧！下次见！🚀
</conclusion>
```

---
处理用时：271.60秒