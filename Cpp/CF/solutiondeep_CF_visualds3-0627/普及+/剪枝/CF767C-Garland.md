# 题目信息

# Garland

## 题目描述

Once at New Year Dima had a dream in which he was presented a fairy garland. A garland is a set of lamps, some pairs of which are connected by wires. Dima remembered that each two lamps in the garland were connected directly or indirectly via some wires. Furthermore, the number of wires was exactly one less than the number of lamps.

There was something unusual about the garland. Each lamp had its own brightness which depended on the temperature of the lamp. Temperatures could be positive, negative or zero. Dima has two friends, so he decided to share the garland with them. He wants to cut two different wires so that the garland breaks up into three parts. Each part of the garland should shine equally, i. e. the sums of lamps' temperatures should be equal in each of the parts. Of course, each of the parts should be non-empty, i. e. each part should contain at least one lamp.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/c2b0d1858f505d34921dc11648298e7a84c2f7b5.png)Help Dima to find a suitable way to cut the garland, or determine that this is impossible.

While examining the garland, Dima lifted it up holding by one of the lamps. Thus, each of the lamps, except the one he is holding by, is now hanging on some wire. So, you should print two lamp ids as the answer which denote that Dima should cut the wires these lamps are hanging on. Of course, the lamp Dima is holding the garland by can't be included in the answer.

## 说明/提示

The garland and cuts scheme for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/578d2b3356505b1b3987876ed70f57ef1ae0c5b0.png)

## 样例 #1

### 输入

```
6
2 4
0 5
4 2
2 1
1 1
4 2
```

### 输出

```
1 4
```

## 样例 #2

### 输入

```
6
2 4
0 6
4 2
2 1
1 1
4 2
```

### 输出

```
-1
```

# AI分析结果



## 【唯一算法分类】  
树形遍历（子树和统计）

---

## 【题解思路与算法要点】  
### **核心思路**  
1. **总和校验**：若树的总权值不能被3整除，直接返回-1。  
2. **后序遍历统计子树和**：从叶子节点向上累加子树权值，若某子树和等于目标值（总和的1/3），记录该节点并将子树和置零（避免重复切割）。  
3. **答案判定**：若找到至少两个符合条件的子树，输出对应的两个节点（切断其父边）。

### **解决难点**  
- **子树分割验证**：切断两个子树后，剩余部分的权值必然为sum/3（总和为3k，已切2k，剩余k）。  
- **避免重复切割**：每找到目标子树后，将其和置零，确保父节点统计时不会重复计算。

---

## 【题解评分 (≥4星)】  
1. **maniac！ (4.5星)**  
   - **亮点**：代码简洁，通过`tem[x]=0`实现子树切割，逻辑清晰。  
   - **个人心得**：指出“子树和问题常被误认为动规，实则巧妙遍历即可解决”。  
2. **chihik (4星)**  
   - **亮点**：明确方程表达子树和计算，代码中使用`dp[u]-=dp[v]`显式处理切割。  
3. **试试事实上吗 (4星)**  
   - **亮点**：通过图示解释极端情况，代码中`sz[x]=0`操作直观体现切割逻辑。  

---

## 【最优思路提炼】  
1. **关键变量**  
   - `sum/3`为目标子树和，`cnt`记录找到的子树数量。  
2. **核心步骤**  
   - DFS后序遍历，累加子树和`tem[x] = t[x] + ∑tem[children]`。  
   - 当`tem[x]==sum/3`时，记录节点并重置`tem[x]=0`。  
3. **优化技巧**  
   - 仅需两次切割即可保证三部分均分，无需显式验证第三部分（总和性质保证）。  

---

## 【同类型题与算法套路】  
- **子树和问题**：如统计满足特定条件的子树数量（和、结构等）。  
- **通用解法**：树形DFS遍历+子树状态统计，常见于分割、平衡问题。  

---

## 【推荐相似题目】  
1. P2014 [CTSC1997]选课（树形依赖背包）  
2. P1122 最大子树和（子树和极值）  
3. P3384 【模板】轻重链剖分（树链操作）  

---

## 【个人心得摘录】  
- **maniac！**：“子树和问题常被误认为动规，实则遍历即可解决。”  
- **试试事实上吗**：“切断后父节点统计需扣除已切割子树，否则会重复计算。”  

---

## 【可视化与算法演示】  
### **动画方案**  
1. **树结构绘制**：以根节点为起点，用节点颜色区分未处理/已处理状态。  
2. **DFS过程**：  
   - **高亮当前节点**：红色表示正在计算其子树和。  
   - **子树和更新**：实时显示`tem[x]`数值变化。  
3. **切割标记**：当子树和达标时，节点变为绿色并播放“成功音效”。  
4. **最终结果**：若找到两个绿色节点，显示切断边并播放胜利音效。  

### **复古像素风格设计**  
- **颜色方案**：16色调色板，绿色节点（成功）、红色（处理中）、灰色（未处理）。  
- **音效设计**：  
  - 节点处理：8-bit“滴”声。  
  - 切割成功：上扬音阶（类似FC游戏宝箱开启）。  
  - 失败：低沉“嗡”声。  

---

## 【核心代码实现】  
```cpp
void dfs(int x, int fa) {
    tem[x] = t[x];
    for (int i = head[x]; i; i = next[i]) {
        int v = ver[i];
        if (v != fa) {
            dfs(v, x);
            tem[x] += tem[v];
        }
    }
    if (tem[x] == target) { // 找到目标子树
        ans[cnt++] = x;
        tem[x] = 0; // 关键：置零避免重复统计
    }
}

// 主函数调用
if (sum % 3 != 0) cout << -1;
else {
    target = sum / 3;
    dfs(root, -1);
    cout << (cnt >= 2 ? ans[0] + " " + ans[1] : -1);
}
```

---

## **代码解释**  
- **DFS遍历**：递归计算子树和，回溯时累加子节点值。  
- **目标判定**：当子树和等于`target`时记录节点并重置其和为0。  
- **答案输出**：仅需两个切割点即可保证三部分均分（总和性质保证第三部分存在）。

---
处理用时：63.02秒