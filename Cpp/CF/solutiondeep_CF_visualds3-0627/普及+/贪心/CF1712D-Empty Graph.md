# 题目信息

# Empty Graph

## 题目描述

— Do you have a wish?



 — I want people to stop gifting each other arrays.

O_o and Another Young Boy



An array of $ n $ positive integers $ a_1,a_2,\ldots,a_n $ fell down on you from the skies, along with a positive integer $ k \le n $ .

You can apply the following operation at most $ k $ times:

- Choose an index $ 1 \le i \le n $ and an integer $ 1 \le x \le 10^9 $ . Then do $ a_i := x $ (assign $ x $ to $ a_i $ ).

Then build a [complete](https://en.wikipedia.org/wiki/Complete_graph) undirected weighted graph with $ n $ vertices numbered with integers from $ 1 $ to $ n $ , where edge $ (l, r) $ ( $ 1 \le l < r \le n $ ) has weight $ \min(a_{l},a_{l+1},\ldots,a_{r}) $ .

You have to find the maximum possible diameter of the resulting graph after performing at most $ k $ operations.

The diameter of a graph is equal to $ \max\limits_{1 \le u < v \le n}{\operatorname{d}(u, v)} $ , where $ \operatorname{d}(u, v) $ is the length of the shortest path between vertex $ u $ and vertex $ v $ .

## 说明/提示

In the first test case, one of the optimal arrays is $ [2,4,5] $ .

The graph built on this array:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1712D/6f5937a14546fd0344ab2a7ad56768b75a98a230.png) $ \operatorname{d}(1, 2) = \operatorname{d}(1, 3) = 2 $ and $ \operatorname{d}(2, 3) = 4 $ , so the diameter is equal to $ \max(2,2,4) = 4 $ .

## 样例 #1

### 输入

```
6
3 1
2 4 1
3 2
1 9 84
3 1
10 2 6
3 2
179 17 1000000000
2 1
5 9
2 2
4 2```

### 输出

```
4
168
10
1000000000
9
1000000000```

# AI分析结果



### 【题解思路与算法要点】

1. **核心结论**  
   - 两点间最短路径为 `min(路径上的最小值, 2*全局最小值)`  
   - 图的直径一定在相邻节点间取得（因路径越长，最小值可能更小）

2. **贪心策略**  
   - **前k-1次操作**：将前k-1小的元素改为1e9，最大化剩余最小值  
   - **最后一次操作**：枚举每个元素改为1e9，计算相邻min的最大值和全局最小值的2倍，取最优解  
   - **复杂度**：O(n log n)（排序） + O(n)（枚举）

3. **二分法**  
   - **假设答案mid**，统计需要修改的元素数：  
     - 所有两倍小于mid的元素必须修改  
     - 相邻元素至少有一个≥mid（需额外修改次数）  
   - **Check函数**：通过前缀和统计修改次数，判断是否≤k  
   - **复杂度**：O(n log V)（V为值域1e9）

### 【难点对比】

| 方法   | 贪心                              | 二分法                          |
|--------|-----------------------------------|---------------------------------|
| 核心   | 前k-1次选最小元素改1e9            | 假设答案，验证可行              |
| 难点   | 证明选前k-1小的正确性              | 设计高效Check函数               |
| 优点   | 直接，无需处理复杂条件             | 通用，适应性强                  |
| 适用性 | k较小或操作策略明显时              | 答案单调或条件复杂时            |

---

### 【最优思路提炼】

- **贪心选择**：优先修改较小元素，提升全局最小值  
- **相邻优化**：直径由相邻节点决定，只需检查相邻min  
- **极值处理**：最后一次操作可最大化相邻min或全局min  

---

### 【题解评分（≥4星）】

1. **Gokix（贪心，5星）**  
   - **亮点**：清晰分步处理，转化k=1情况简化问题  
   - **代码**：高效排序+枚举，维护关键变量ans1/ans2  
   ```cpp
   // 核心代码片段
   for(i=1;i<k;i++) a[b[i].id]=MD; // 改前k-1小
   for(i=1;i<=n;i++){ // 枚举最后一次修改
       u=a[i];a[i]=MD;
       mx = max(ans1, max(a[i-1], a[i+1])); // 更新相邻min
       if(u*2 == ans2) ans = max(ans, min(mx, ans3)); 
       else ans = max(ans, min(mx, ans2));
   }
   ```

2. **Dregen_Yor（二分，4.5星）**  
   - **亮点**：简洁Check函数，前缀和统计修改次数  
   - **代码**：快速统计相邻元素修改需求  
   ```cpp
   bool check(int lm){
       int cc=0;
       rep(1,n,i) if(2*a[i]<lm) a[i]=INF,cc++;
       if(cc>k) return 0;
       // 检查相邻是否满足条件
       bool f1=0,f2=0;
       rep(2,n,i) if(min(a[i],a[i-1])>=lm) f1=1;
       rep(1,n,i) if(a[i]>=lm) f2=1;
       return (cc + !f1 + !f2) <=k;
   }
   ```

3. **Jr_Zlw（二分，4星）**  
   - **亮点**：数学推导完整，代码精简  
   - **心得**：“两点间最短路最多经过两条边”是关键观察  

---

### 【可视化设计】

**贪心策略演示（像素风格）**  
1. **初始化**：数组元素显示为像素块，数值越小颜色越深  
2. **修改过程**：  
   - 前k-1小元素变为红色并闪烁，数值变为1e9  
   - 音效：修改时播放“升级”音效  
3. **最后一次修改**：  
   - 高亮当前枚举元素，显示相邻min和全局min计算  
   - 成功找到更大直径时播放胜利音效  

**二分法动态演示**  
1. **滑动条**：调节mid值，实时显示Check结果  
2. **统计高亮**：  
   - 红色：必须修改的元素（2*值<mid）  
   - 黄色：需额外修改的相邻元素  
3. **自动模式**：AI逐步增大mid，失败时回退，模拟二分过程  

---

### 【相似题目推荐】

1. **CF1282D Enchanted Matrix**  
   - 贪心+二分验证极值问题  
2. **Luogu P2216 [HAOI2007]理想的正方形**  
   - 滑动窗口维护二维区间极值  
3. **Luogu P1083 借教室**  
   - 二分答案+差分验证可行性  

---

### 【核心代码实现】

**贪心策略（Gokix）**  
完整代码已贴出，核心在于排序后处理前k-1小元素，最后一次枚举优化。

**二分法（Dregen_Yor）**  
```cpp
int main(){
    while(T--){
        int l=1, r=1e9, ans=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(mid)) ans=mid, l=mid+1;
            else r=mid-1;
        }
        printf("%d\n",ans);
    }
}
```

---

### 【总结】

贪心策略通过修改策略性元素快速提升关键指标，适合操作步骤明确的问题；二分法普适性强，需设计高效验证函数。实际应用中，可根据k的大小和问题特征选择方法。

---
处理用时：104.14秒