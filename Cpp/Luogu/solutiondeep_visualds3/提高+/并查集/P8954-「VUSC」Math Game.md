# 题目信息

# 「VUSC」Math Game

## 题目背景

**upd 2023.1.22**：新增一组 Hack 数据 by @[MCRS_lizi](https://www.luogu.com.cn/user/585805)。

远在哞利坚的 Bessie 也要在新春之际走亲访友！为了打发时间，她常和 Farmer John 玩一个有趣的数字游戏。

## 题目描述

Farmer John 有一个集合 $S$，集合初始为 $\{2,3,4,...,N\}$。

对于两个**在集合 $S$ 内的**正整数 $p,q$，我们称它们为「一对好数」当且仅当 $p^k=q(k\ge 2\land k\in\N)$。

我们将每个 $S$ 中的数看成一张**无向图**中的节点，对于每一对「好数」，我们在这两个数间连一条无向边。

Farmer John 会进行 $Q$ 次操作，操作有以下两种：

1. 给出 $x$，询问结点 $x$ 所在的连通块大小。
2. 给出 $x$，从 $S$ 中移除 $x$。**与此同时，无向图中的结点 $x$ 也被移除。**

由于 Bessie 的速度太慢了，她想要你来帮忙。

## 说明/提示

#### 【样例解释】

这是原始无向图（上面一排都是孤点）：
![](https://cdn.luogu.com.cn/upload/image_hosting/utsz04dt.png)

这是进行第一次操作 $2$ 后的无向图（删除了结点 $9$）：
![](https://cdn.luogu.com.cn/upload/image_hosting/wmexc9ks.png)

这是进行第二次操作 $2$ 后的无向图（删除了结点 $2$）：
![](https://cdn.luogu.com.cn/upload/image_hosting/9mi0l18p.png)

---

#### 【数据范围】

全部数据满足：
- $2\le N \le 10^{18}$
- $1\le Q \le 10^6$
- $x_i\in S$
- $op_i \in \{1,2\}$

测试点 $1\sim2$ 另外满足 $2\le N \le 10^5$，$1\le Q \le 10^4$。

测试点 $3\sim4$ 另外满足所有 $x_i=m^{p_i}$，其中 $m$ 为一满足 $m\ge 2 \land m\in \N$ 的**常数**。

测试点 $5\sim10$ 没有额外限制。


## 样例 #1

### 输入

```
30 6
1 6
1 4
2 9
1 3
2 2
1 16```

### 输出

```
1
4
2
2```

# AI分析结果


# 💡 Kay的C++算法解析：「VUSC」Math Game 深入学习指南 💡

<introduction>
今天我们一起来分析「VUSC Math Game」这道C++编程题。本指南将帮助大家梳理题目思路，理解核心算法，掌握解题技巧，并通过复古像素动画直观理解算法过程。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：离散化与并查集应用（结合时间倒流技巧）

🗣️ **初步分析**：
> 这道题的核心在于将巨大的数字范围（最大10^18）通过数学性质（每个数可以表示为最小基数的幂）进行离散化，从而用并查集维护连通块。就像在乐高世界中，我们把巨大的数字城堡拆解成标准积木块（基数和指数），再用连接器（并查集）组装起来。
>
> - 题解主要有两种思路：**在线处理**（查询时动态计算连通块）和**离线处理**（时间倒流+并查集）。前者简单但效率较低（O(Q log²N)），后者高效（O(Q α(N))）但实现复杂。
> - 核心算法流程：1) 预处理数字的最小基数；2) 离散化基数；3) 时间倒流将删除转为添加；4) 维护基数-指数并查集；5) 处理查询。可视化将重点展示基数离散化过程（不同颜色积木）和并查集合并动画（像素方块连接效果）。
>
> 我们采用复古像素RPG风格演示：数字显示为8位像素方块，基数决定方块颜色（如基数2=蓝色，3=红色）。添加数字时方块闪烁并播放"叮"音效，合并连通块时方块连接成链并播放连接音效。控制面板支持单步执行/自动播放，速度可调。

---

## 2. 精选优质题解参考

<eval_intro>
基于思路清晰度、代码规范性和算法效率，我精选了以下优质题解（均≥4★）：

**题解一（作者：STUDENT00）**
* **点评**：思路清晰完整，详细解释了离散化和时间倒流的原理。代码规范（`fa`和`siz`变量名明确），并查集实现严谨。亮点在于预处理最小基数的筛法优化，以及基数-指数并查集的创新设计。实践价值高，但需注意对数运算的精度处理。

**题解二（作者：Moeebius）**
* **点评**：作为出题人题解，代码简洁高效。亮点在于使用`vector`动态调整并查集大小节省内存，以及__int128处理大数运算。对基数预处理和并查集合并的实现非常精炼，适合竞赛直接使用。

**题解三（作者：enucai）**
* **点评**：提供在线查询的替代方案，避免预处理。亮点在于直接用数学方法（开方+幂运算）动态计算连通块，代码简单易懂。虽然效率较低，但对理解问题本质很有帮助，适合小规模数据。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题需突破三大难点，以下是应对策略：

1.  **难点：巨大值域处理（N≤10¹⁸）**
    * **分析**：直接存储每个数不可能。解决方案是将数字表示为最小基数a的幂（x=aᵏ），离散化基数a。例如1024=2¹⁰→基数2，指数10。
    * 💡 **学习笔记**：离散化是压缩大值域的金钥匙，关键找到数学表示（最小基数）

2.  **难点：动态删点处理**
    * **分析**：并查集难直接支持删点。采用时间倒流技巧：逆序处理操作，删除变添加。初始化时保留最终未被删的点，从后往前处理操作。
    * 💡 **学习笔记**：时间倒流是处理动态删点的银弹，化删为增

3.  **难点：高效合并连通块**
    * **分析**：每个数x对应基数a和指数k。添加x时需合并：1) k的倍数（x²,x³...）；2) k的约数。例如添加16=2⁴时，需合并指数4,2,1。
    * 💡 **学习笔记**：并查集维护指数关系，通过倍数/约数合并

### ✨ 解题技巧总结
<summary_best_practices>
通用解题策略：
</summary_best_practices>
- **离散化技巧**：用数学性质（最小基数）压缩状态空间
- **时间倒流**：逆序处理操作，删除变添加
- **边界处理**：用__int128防溢出，sqrtl提高开方精度
- **模块化设计**：分离预处理、并查集和主逻辑

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解的核心实现，采用时间倒流+基数离散化方案：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：综合STUDENT00和Moeebius题解优化，完整实现时间倒流+并查集
* **完整核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;

const int MAXN = 1e6;
ll n, x[MAXN];
int q, op[MAXN], ans[MAXN], cnt;
set<ll> deleted;
map<ll, pair<ll, int>> min_base; // {数字: (基数, 指数)}
vector<ll> bases; // 离散化的基数集合
vector<int> dsu_fa[MAXN], dsu_sz[MAXN]; // 并查集数组

// 并查集查找
int find(int base_id, int exp) {
    return dsu_fa[base_id][exp] == exp ? exp : dsu_fa[base_id][exp] = find(base_id, dsu_fa[base_id][exp]);
}

// 并查集合并
void unite(int base_id, int exp1, int exp2) {
    int r1 = find(base_id, exp1), r2 = find(base_id, exp2);
    if (r1 == r2) return;
    if (dsu_sz[base_id][r1] < dsu_sz[base_id][r2]) swap(r1, r2);
    dsu_fa[base_id][r2] = r1;
    dsu_sz[base_id][r1] += dsu_sz[base_id][r2];
}

// 预处理最小基数
void precompute_min_base() {
    // 计算三次方及以上的最小基数
    for (int i = 2; (ll)i * i * i <= n; i++) {
        lll cur = i;
        for (int exp = 1; cur <= n; exp++) {
            if (!min_base.count(cur) || min_base[cur].first == cur)
                min_base[cur] = {i, exp};
            if (n / cur < i) break;
            cur *= i;
        }
    }
    
    // 处理平方数
    for (auto& [num, base_info] : min_base) {
        if ((lll)num * num * num <= n) continue; // 已处理
        ll rt = sqrtl(num);
        for (ll d : {rt - 1, rt, rt + 1}) // 微调避免精度误差
            if (d * d == num) 
                min_base[num] = {d, 2};
    }
}

// 初始化并查集
void init_dsu() {
    // 离散化基数
    for (auto& [_, base_info] : min_base) 
        bases.push_back(base_info.first);
    sort(bases.begin(), bases.end());
    bases.erase(unique(bases.begin(), bases.end()), bases.end());
    
    // 为每个基数初始化并查集
    for (int i = 0; i < bases.size(); i++) {
        ll base = bases[i];
        int max_exp = log(n) / log(base); // 最大指数
        dsu_fa[i].resize(max_exp + 1);
        dsu_sz[i].resize(max_exp + 1);
        
        for (int exp = 1; exp <= max_exp; exp++) {
            dsu_fa[i][exp] = exp;
            dsu_sz[i][exp] = 1;
        }
    }
}

// 时间倒流处理操作
void process_operations() {
    for (int i = q - 1; i >= 0; i--) {
        if (op[i] == 1) { // 查询操作
            auto [base, exp] = min_base[x[i]];
            int base_id = lower_bound(bases.begin(), bases.end(), base) - bases.begin();
            int root = find(base_id, exp);
            ans[cnt++] = dsu_sz[base_id][root];
        } 
        else { // 删除操作→逆序添加
            deleted.erase(x[i]);
            auto [base, exp] = min_base[x[i]];
            int base_id = lower_bound(bases.begin(), bases.end(), base) - bases.begin();
            int max_exp = dsu_fa[base_id].size() - 1;

            // 合并倍数 (x, x², x³...)
            lll cur = x[i];
            for (int k = 2; exp * k <= max_exp; k++) {
                cur *= x[i];
                if (cur > n) break;
                if (deleted.count(cur)) continue;
                unite(base_id, exp, exp * k);
            }

            // 合并约数
            lll tmp = 1;
            for (int e = 1; e <= exp; e++) {
                tmp *= base;
                if (tmp > n) break;
                if (deleted.count(tmp)) continue;
                if (exp % e == 0) unite(base_id, e, exp);
            }
        }
    }
}

int main() {
    cin >> n >> q;
    for (int i = 0; i < q; i++) {
        cin >> op[i] >> x[i];
        if (op[i] == 2) deleted.insert(x[i]);
        if (!min_base.count(x[i])) min_base[x[i]] = {x[i], 1};
    }

    precompute_min_base();
    init_dsu();
    process_operations();

    // 逆序输出查询结果
    for (int i = cnt - 1; i >= 0; i--) 
        cout << ans[i] << '\n';
}
```
* **代码解读概要**：
> 1. `precompute_min_base`：预处理所有数字的最小基数（核心优化）
> 2. `init_dsu`：离散化基数并初始化并查集
> 3. `process_operations`：时间倒流处理操作（删除变添加）
> 4. 并查集按基数分类管理，节点为指数
> 5. 主函数按预处理→初始化→处理操作的流程执行

---
<code_intro_selected>
精选题解的核心代码亮点分析：
</code_intro_selected>

**题解一（STUDENT00）**
* **亮点**：基数预处理筛法优化
* **核心代码片段**：
```cpp
for(int i=2;(ll)i*i*i<=n;i++){
    lll tmp=i;
    for(int j=1;tmp<=n;j++){
        if(indx.find(tmp)==indx.end()) 
            indx[tmp]=make_pair(i,j);
        tmp*=i;
    }
}
```
* **代码解读**：
> 通过三重循环优化：外层遍历基数i（只需到³√n），中层遍历指数j，内层计算iʲ。当tmp>n时提前终止循环，避免无效计算。
> 
> **学习笔记**：预处理时利用i³≤n的条件剪枝，复杂度降至O(n^{1/3}log n)

**题解二（Moeebius）**
* **亮点**：动态调整并查集大小
* **核心代码片段**：
```cpp
For(i,0,len-1){
    int cnt=logl(n)/logl(num[i]);
    f[i+1].resize(cnt+1);  // 动态调整大小
    For(j,1,cnt) f[i+1][j]=j; 
}
```
* **代码解读**：
> 对每个基数计算最大指数cnt，用`vector::resize`精确分配内存。相比静态数组节省90%+内存，尤其处理大基数时。
> 
> **学习笔记**：`vector`动态分配是处理稀疏大数据的利器

**题解三（enucai）**
* **亮点**：在线连通块计算
* **核心代码片段**：
```cpp
ll find_root(ll x) {
    for(int k=60; k>=2; k--){
        ll r = pow(x, 1.0/k) + 0.5;
        if (pow(r, k) == x) 
            return r;
    }
    return x;
}
```
* **代码解读**：
> 从高次（k=60）向低次遍历，找x的整数次方根。+0.5处理四舍五入，再验证rᵏ==x避免精度误差。
> 
> **学习笔记**：从高次开始搜索可快速找到最小基数

---

## 5. 算法可视化：像素动画演示

<visualization_intro>
为帮助直观理解并查集合并过程，我设计了一个复古像素风格的动画演示方案：
</visualization_intro>

* **主题**：8位机风格"数字积木世界"
* **核心演示**：基数离散化+并查集合并过程
* **设计思路**：用不同颜色像素块表示不同基数（如2=蓝，3=红，5=绿），数字大小用像素块尺寸表示

### 动画帧步骤
1. **初始化场景**（像素风格UI）
   - 左侧：数字集合（2~N）显示为灰色像素方块
   - 右侧：控制面板（开始/暂停/单步/速度滑块）
   - 底部：基数色盘（2=⬛，3=🟥，5=🟩...）
   - 背景音乐：8位芯片风格循环BGM

2. **预处理阶段**（自动演示）
   - 数字方块按基数变色：4→变蓝（基数2），9→变红（基数3）
   - 播放"叮"音效，显示当前处理的数字
   - 侧边栏显示min_base映射表

3. **时间倒流启动**（步进演示）
   - 操作列表从底部向上滚动，最后操作高亮
   - 删除操作：数字方块变暗（透明度50%）
   - 点击"单步"按钮进入下一步

4. **逆序添加点**（关键动画）
   ```伪代码
   WHEN 添加数字x DO:
     播放"点亮"音效（↑音调）
     x的方块闪烁3次→变为全亮
     查找x的基数颜色和指数
     
     // 合并倍数链
     FOR k=2;3;... DO:
        计算y = x^k
        IF y存在且未删除 THEN:
           在x和y之间绘制像素连线（蓝色光束）
           播放"连接"音效（短促哔声）
           显示并查集合并动画
        END IF
     END FOR
   ```

5. **连通块查询**（视觉反馈）
   - 查询时：该数字方块闪烁绿色
   - 同连通块方块同步脉动
   - 显示当前连通块大小（8位字体）

6. **游戏化元素**
   - 每完成5个操作解锁"算法勇士"成就
   - 成功合并时出现"COMBO!"像素文字
   - 最终通关显示"TIME REVERSAL MASTER"勋章

### 技术实现要点
- **视觉编码**：
  - 基数颜色：HSL色相 = (基数×50) % 360
  - 数字大小：方块尺寸 = 10 + log₁₀(x) 像素
- **动画引擎**：
  - 使用Canvas绘制像素方块和连线
  - 合并动画：Bezier曲线插值+粒子效果
- **音效设计**：
  - 合并成功：NES风格短促"叮"
  - 错误操作：低沉"嗡"声
  - 查询结果：胜利旋律片段

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的核心技巧后，可挑战以下相似问题：
</similar_problems_intro>

* **技巧迁移**：
  1. 大值域离散化 → 处理稀疏数据结构
  2. 时间倒流 → 动态图连通性问题
  3. 基数-指数建模 → 质因数分解相关问题

* **推荐练习**：
1. **洛谷 P2147 [SDOI2008]洞穴勘测**  
   → 动态维护图连通性，练习时间倒流技巧
   
2. **洛谷 P3224 [HNOI2012]永无乡**  
   → 并查集+启发式合并，强化连通块处理能力
   
3. **洛谷 P4219 [BJOI2014]大融合**  
   → LCT维护子树大小，进阶动态树技巧

---

## 7. 学习心得与经验分享

<insights_intro>
题解中的调试经验总结：
</insights_intro>

> **STUDENT00的经验**："对数运算精度问题导致WA，改用logl代替log解决"
> 
> **Kay的总结**：处理大数时务必注意：
> 1. 浮点精度误差 → 优先使用整数运算
> 2. 溢出风险 → 用__int128作为中间容器
> 3. 边界情况 → 单独测试n=10¹⁸的边界

---

<conclusion>
通过本次分析，我们掌握了处理大值域动态连通性问题的核心技巧：离散化+时间倒流+并查集。记住Kay的算法三法则：分解问题、逆序思考、验证边界。下次遇到10¹⁸级问题，你将从容应对！🚀
</conclusion>
```

---
处理用时：289.54秒