# 题目信息

# Chiori and Doll Picking (easy version)

## 题目描述

This is the easy version of the problem. The only difference between easy and hard versions is the constraint of $ m $ . You can make hacks only if both versions are solved.

Chiori loves dolls and now she is going to decorate her bedroom!

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336E1/7f2871c87cb2f7ef2408d5e1359121eb7612b9c0.png)As a doll collector, Chiori has got $ n $ dolls. The $ i $ -th doll has a non-negative integer value $ a_i $ ( $ a_i < 2^m $ , $ m $ is given). Chiori wants to pick some (maybe zero) dolls for the decoration, so there are $ 2^n $ different picking ways.

Let $ x $ be the bitwise-xor-sum of values of dolls Chiori picks (in case Chiori picks no dolls $ x = 0 $ ). The value of this picking way is equal to the number of $ 1 $ -bits in the binary representation of $ x $ . More formally, it is also equal to the number of indices $ 0 \leq i < m $ , such that $ \left\lfloor \frac{x}{2^i} \right\rfloor $ is odd.

Tell her the number of picking ways with value $ i $ for each integer $ i $ from $ 0 $ to $ m $ . Due to the answers can be very huge, print them by modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
4 4
3 5 8 14```

### 输出

```
2 2 6 6 0```

## 样例 #2

### 输入

```
6 7
11 45 14 9 19 81```

### 输出

```
1 2 11 20 15 10 5 0```

# AI分析结果

---
# 💡 Kay的C++算法解析：Chiori and Doll Picking (easy version) 深入学习指南 💡

<introduction>
今天我们来一起分析“Chiori and Doll Picking (easy version)”这道题。这道题需要计算所有选法中异或和的二进制1的个数对应的方案数，涉及线性基、折半搜索和快速沃尔什变换（FWT）等技巧。本指南将帮你理清思路，掌握核心算法！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：数学与算法综合应用（线性基、折半搜索、FWT异或卷积）

🗣️ **初步分析**：
解决这道题的关键在于利用线性基缩小问题规模，再通过折半搜索和FWT高效统计异或和的1的个数。  
线性基就像一个“压缩包”，它能表示原数组所有可能的异或和，且每个异或和出现的次数是固定的（$2^{n-r}$，r是线性基的大小）。这一步将问题从$2^n$的规模压缩到$2^r$，大大降低了复杂度。  

核心难点在于如何高效统计线性基内所有异或和的1的个数。题解普遍采用**折半搜索+FWT**的策略：  
- 将线性基分为高位和低位两部分，分别枚举所有可能的异或和（折半搜索），记录每部分的1的个数和低位状态。  
- 合并两部分时，利用FWT处理异或卷积（因为异或和的低位由两部分异或得到），快速计算总1的个数的方案数。  

可视化设计上，我们可以用8位像素风格展示线性基的构造（如不同颜色的方块代表不同位的基）、折半搜索的分支过程（左右分屏显示高低位枚举），以及FWT卷积时的数值流动（用像素箭头连接异或对）。关键步骤用闪烁高亮，入队/异或操作配“叮”音效，完成时播放胜利音效增强记忆。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码规范性、算法有效性等维度筛选出以下优质题解：
</eval_intro>

**题解一：Froggy的线性基+折半搜索+FWT解法 (来源：Froggy's blog)**
* **点评**：此题解思路非常清晰，完整覆盖了线性基构造、折半搜索分治、FWT异或卷积的全流程。代码中变量命名规范（如`d[i]`表示线性基第i位，`mid`表示折半分界点），边界处理严谨（如`pcnt`预处理1的个数）。亮点在于将复杂的异或和统计拆解为高低位分治，并用FWT高效合并，时间复杂度控制在合理范围内（约$10^8$次操作），适合竞赛实战参考。

**题解二：SDNetFriend的动态规划解法 (来源：洛谷题解)**
* **点评**：此题解另辟蹊径，利用线性基“低位不影响高位”的性质设计动态规划。状态定义`f[0/1][i][j]`直观（表示处理到第i位时的高位1个数和低位状态），通过队列优化状态转移，避免了全状态枚举。代码中使用`unordered_map`存储状态，节省空间，适合理解线性基与DP的结合。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题的核心难点主要集中在以下三个方面，我们逐一分析：
</difficulty_intro>

1.  **关键点1：线性基的构造与性质应用**  
    * **分析**：线性基的构造需要从高位到低位依次插入，确保每个基的最高位唯一。例如，插入一个数x时，若某一位已有基，则x异或该基，直到找到未被占用的位或变为0（此时x是“自由元”）。线性基的性质是：所有可能的异或和共有$2^r$种（r是基的个数），每种出现$2^{n-r}$次。  
    * 💡 **学习笔记**：线性基是处理异或问题的“压缩神器”，能将指数级问题降维到基的数量级。

2.  **关键点2：折半搜索的分治策略**  
    * **分析**：当基的数量r较大（如35），直接枚举$2^r$种异或和不可行。折半搜索将基分为高位（前r/2位）和低位（后r/2位），分别枚举两部分的异或和，记录高位的1的个数和低位状态。例如，Froggy的题解中，`mid=(m+1)>>1`将基分为高低位，分别用`dfs1`和`dfs2`搜索。  
    * 💡 **学习笔记**：折半搜索通过“分而治之”将复杂度从$O(2^r)$降至$O(2^{r/2})$，是处理大指数问题的常用技巧。

3.  **关键点3：FWT异或卷积的合并**  
    * **分析**：合并高低位的异或和时，需要计算所有可能的异或对（i异或j）的1的个数之和。FWT能将异或卷积的时间复杂度从$O(N^2)$降至$O(N\log N)$。例如，Froggy的题解中，对高低位的结果分别做FWT，点乘后逆FWT，得到合并后的异或和分布。  
    * 💡 **学习笔记**：FWT是处理异或、与、或卷积的“黑科技”，适合快速合并分治后的结果。

### ✨ 解题技巧总结
- **问题压缩**：用线性基将原问题压缩到$2^r$规模，利用自由元数$2^{n-r}$放大结果。  
- **分治枚举**：折半搜索将大指数问题拆分为两个小指数问题，降低计算量。  
- **FWT加速**：异或卷积用FWT高效合并，避免暴力枚举所有异或对。  

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们选取Froggy的题解作为通用核心实现，其代码逻辑清晰，完整覆盖了线性基、折半搜索、FWT的关键步骤。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了线性基构造、折半搜索分治、FWT异或卷积的核心逻辑，是解决此类问题的典型实现。
* **完整核心代码**：
    ```cpp
    #include<iostream>
    #include<cstdio>
    #include<cstring>
    using namespace std;
    #define N 400020
    typedef long long ll;
    const ll mod=998244353;
    int n,m,cnt,mid;
    ll a[N],d[N],f[28][N],g[N],pcnt[N<<1],ans[N],tmp[N]; 
    
    void Insert(ll x) { // 线性基插入
        for(int i=m-1;i>=0;--i){
            if((x>>i)&1){
                if(!d[i]){
                    d[i]=x,++cnt;
                    return;
                } else x^=d[i];
            }
        }
    }
    
    void dfs1(int u,ll num) { // 高位折半搜索
        if(u==mid-1){
            f[pcnt[num>>mid]][num&((1<<mid)-1)]++;
            return;
        }
        dfs1(u-1,num);
        if(d[u]) dfs1(u-1,num^d[u]);
    }
    
    void dfs2(int u,ll num) { // 低位折半搜索
        if(u==mid){
            g[num]++;
            return;
        }
        dfs2(u+1,num);
        if(d[u]) dfs2(u+1,num^d[u]);
    }
    
    ll qpow(ll a,ll b) { // 快速幂
        ll ans=1;
        while(b){
            if(b&1) ans=ans*a%mod;
            a=a*a%mod;
            b>>=1;
        }
        return ans;
    }
    
    void XOR(ll *f,ll x,int n) { // FWT异或变换
        for(int p=2;p<=n;p<<=1){
            int len=(p>>1);
            for(int k=0;k<n;k+=p){
                for(int i=k;i<k+len;++i){
                    ll t1=f[i]+f[i+len],t2=f[i]-f[i+len];
                    f[i]=t1*x%mod,f[i+len]=t2*x%mod;
                }
            }
        }
    }
    
    int main(){
        n=read(),m=read(); // 假设read()已实现
        for(int i=1;i<=n;++i){
            a[i]=read();
            Insert(a[i]);
        }
        mid=(m+1)>>1;
        for(int i=1;i<=300000;++i) pcnt[i]=pcnt[i>>1]+(i&1); // 预处理1的个数
        dfs1(m-1,0); dfs2(0,0); // 高低位搜索
        memcpy(tmp,g,sizeof(g));
        for(int i=0;i<=m-mid;++i){ // 枚举高位1的个数，合并结果
            memcpy(g,tmp,sizeof(g));
            XOR(f[i],1,1<<mid); XOR(g,1,1<<mid);
            for(int j=0;j<(1<<mid);++j) f[i][j]=f[i][j]*g[j]%mod;
            XOR(f[i],qpow(2LL,mod-2),1<<mid);
            for(int j=0;j<(1<<mid);++j) ans[i+pcnt[j]]=(ans[i+pcnt[j]]+f[i][j])%mod;
        }
        ll pow2=qpow(2LL,n-cnt); // 乘以自由元的贡献
        for(int i=0;i<=m;++i) printf("%lld ",ans[i]*pow2%mod);
        return 0;
    }
    ```
* **代码解读概要**：  
  代码首先构造线性基`d`，将原问题压缩到$2^{cnt}$规模。通过`dfs1`和`dfs2`分别枚举高位和低位的异或和，记录高位的1的个数（`f[i][j]`）和低位状态（`g[j]`）。利用FWT对`f`和`g`做异或卷积，合并后统计总1的个数的方案数，最后乘以自由元的贡献$2^{n-cnt}$得到答案。

---
<code_intro_selected>
接下来分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：Froggy的线性基+折半搜索+FWT解法**
* **亮点**：折半搜索分治+FWT高效合并，代码结构清晰，边界处理严谨。
* **核心代码片段**：
    ```cpp
    void dfs1(int u,ll num) { // 高位折半搜索，记录高位1的个数和低位状态
        if(u==mid-1){
            f[pcnt[num>>mid]][num&((1<<mid)-1)]++;
            return;
        }
        dfs1(u-1,num);
        if(d[u]) dfs1(u-1,num^d[u]);
    }
    ```
* **代码解读**：  
  `dfs1`函数递归枚举高位部分的异或和。`u`表示当前处理的位，`num`是当前异或和。当`u`到达分界点`mid-1`时，计算高位部分的1的个数（`pcnt[num>>mid]`）和低位状态（`num&((1<<mid)-1)`），并在`f`数组中计数。递归时，选择或不选当前基（`d[u]`），覆盖所有可能的异或组合。  
  这里的`pcnt`是预处理的1的个数数组，避免重复计算，提高效率。
* 💡 **学习笔记**：折半搜索通过递归枚举所有可能的异或组合，利用线性基的高位唯一性，确保枚举的异或和不重复。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

\<visualization\_intro\>
为了直观理解线性基构造、折半搜索和FWT合并的过程，我们设计一个“像素异或探险”动画，用8位复古风格展示算法每一步！
\</visualization\_intro\>

  * **动画演示主题**：像素异或探险——线性基的构造与合并  
  * **核心演示内容**：线性基的插入过程（基的“抢占”高位）、折半搜索的分支枚举（左右分屏展示高低位异或和）、FWT卷积的数值流动（异或对的1的个数合并）。  

  * **设计思路简述**：  
    采用FC红白机风格的像素网格，用不同颜色区分线性基的位（红色=高位，蓝色=低位）。折半搜索时，左右分屏展示高位和低位的枚举过程，每选一个基，对应颜色的方块闪烁并移动。FWT卷积时，用像素箭头连接异或对，数值流动时播放“叮”音效，最终结果用金色高亮，增强成就感。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：  
        - 屏幕分为左右两部分，左半屏显示线性基构造区（8x8像素网格，每列代表一个位），右半屏是控制面板（开始/暂停、单步按钮）。  
        - 播放8位风格的轻快BGM（类似《超级玛丽》的主题音乐）。

    2.  **线性基插入动画**：  
        - 输入一个数（如样例中的3），像素方块从顶部下落，尝试插入最高位（第3位）。若该位已有基（绿色方块），则异或该基（方块闪烁，数值变化），直到找到空位（红色方块）或变为0（灰色方块，标记为自由元）。  
        - 插入成功时播放“滴”音效，自由元出现时播放“噗”音效。

    3.  **折半搜索枚举**：  
        - 高位搜索（左分屏）：从最高位开始，递归选择或不选基，每一步用箭头标记当前位（黄色闪烁），异或后的数值用新方块表示（颜色渐变）。  
        - 低位搜索（右分屏）：类似高位，枚举低位的异或和，结果存入`g`数组（蓝色方块堆叠）。

    4.  **FWT卷积合并**：  
        - 高低位的结果数组（`f`和`g`）用像素条显示，FWT变换时，像素条按位分解（如长度2→4→8...），数值重新排列（用箭头指示交换）。  
        - 点乘时，对应位置的像素条颜色叠加（红+蓝=紫），逆FWT后得到合并结果，播放“唰”音效。

    5.  **结果输出**：  
        - 最终答案数组用柱状图展示（高度代表方案数），每个柱子颜色按1的个数渐变（0→蓝，m→红）。播放胜利音效（类似《塞尔达》的胜利旋律），关键数值用星星特效包围。

  * **旁白提示**：  
    - 线性基插入时：“看！这个数在抢占高位，如果该位已有基，它会异或基，直到找到空位～”  
    - FWT变换时：“现在，我们用FWT快速合并高低位的结果，就像把两堆积木快速组合成新形状！”  

\<visualization\_conclusion\>
通过这个像素动画，你可以直观看到线性基如何压缩问题、折半搜索如何分治枚举，以及FWT如何高效合并结果，让抽象的算法变得“可见可触”！
\</visualization\_conclusion\>

-----

## 6\. 拓展练习与相似问题思考

\<similar\_problems\_intro\>
本题的线性基、折半搜索、FWT技巧在异或统计类问题中非常通用，我们可以通过以下题目巩固：
\</similar\_problems\_intro\>

  * **通用思路/技巧迁移**：  
    线性基+折半搜索+FWT的组合适用于：  
    - 统计异或和满足特定条件（如1的个数、大小范围）的方案数；  
    - 处理大规模异或问题（n大但m较小）；  
    - 多维度统计（如同时统计异或和的1的个数和其他属性）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P4869 albus就是要第一个出场**  
          * 🗣️ **推荐理由**：直接考察线性基的性质（异或和出现次数），是本题的基础题，适合巩固线性基知识。
    2.  **洛谷 P3812 线性基**  
          * 🗣️ **推荐理由**：线性基的模板题，练习线性基的构造和基本应用，为复杂问题打基础。
    3.  **洛谷 P5643 【CSGRound2】游戏**  
          * 🗣️ **推荐理由**：结合线性基和博弈论，需要灵活运用线性基的性质，适合提升综合解题能力。

-----

## 7\. 学习心得与经验分享 (若有)

\<insights\_intro\>
Froggy在题解中提到：“晚上刚CF想到了正解，但是没写完呜呜呜，第二天早上20min就AC了。” 这提醒我们：
\</insights\_intro\>

> **参考经验**：“思路卡壳时，先整理核心步骤（如线性基构造、折半分治），第二天理清逻辑后往往能快速实现。”  
> **点评**：遇到复杂问题时，可先拆解核心步骤（如本题的线性基、折半、FWT），分开实现后再整合。调试时，重点检查线性基插入是否正确、折半分界点是否合理，这些是容易出错的地方。

-----

\<conclusion\>
本次关于“Chiori and Doll Picking (easy version)”的分析就到这里。希望你掌握了线性基、折半搜索和FWT的核心技巧，下次遇到异或统计问题时，能自信地“压缩”问题、“分治”枚举、“快速”合并！加油，你是最棒的算法小能手！💪
\</conclusion\>

---
处理用时：148.64秒