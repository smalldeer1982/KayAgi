# 题目信息

# [USACO23FEB] Equal Sum Subarrays G

## 题目描述

注意：本题的时间限制为 3 秒，为默认时间的 1.5 倍。

FJ 给了 Bessie 一个长度为 $N$ 的数组 $a$（$2 \leq N \leq 500, -10^{15} \leq a_i \leq 10^{15}$），其中所有 $\dfrac{N(N+1)}{2}$ 个连续子数组的和都是不同的。对于每个下标 $i \in [1,N]$，帮助 Bessie 计算最小的改变量，使得数组中存在两个不同的连续子数组的和相等。

## 样例 #1

### 输入

```
2
2 -3```

### 输出

```
2
3```

## 样例 #2

### 输入

```
3
3 -10 4```

### 输出

```
1
6
1```

# AI分析结果

• 综合分析与结论：这些题解主要围绕如何找到修改数组中每个元素后能使两个不同连续子数组和相等的最小改变量。核心思路是利用性质，即最终相等的两个子数组必然一个包含待修改元素，一个不包含。算法上，大多先求出所有子数组和并排序，再通过不同方式找满足条件的最小差值。时间复杂度有 $O(n^3)$ 和 $O(n^2\log n)$ 等。部分题解通过离散化、优化数据结构使用等方式优化复杂度。
- 作者：MessageBoxA (赞：7)  星级：5星
  - 关键亮点：提出 $O(n^2\log n)$ 解法，详细分析问题性质，如两个区间有交情况可归纳为无交情况等。利用set和前缀和，通过枚举分界点，在set中二分查找与当前区间和最接近的区间，更新答案，代码实现细节处理较好。
  - 个人心得：提到该做法细节多，调试时交了十几发才通过。
  ```cpp
  // 核心代码片段
  for(int l = 2; l <= n; l++){
      minx = LLINF;
      for(int r = n; r >= l; r--){
          tmp = pre[r] - pre[l - 1];
          minx = min(minx, abs(tmp));
          res = s.lower_bound({tmp, -1, -1});
          if(res!= s.end()) minx = min(minx, abs(res->val - tmp));
          if(res!= s.begin()){
              res--;
              minx = min(minx, abs(res->val - tmp));
          }
          ans[r] = min(ans[r], minx);

          tmp = -tmp;
          res = s.lower_bound({tmp, -1, -1});
          if(res!= s.end())
              if(!is_range_merge_cover_all(l, r, res->l, res->r))
                  minx = min(minx, abs(res->val - tmp));
          if(res!= s.begin()){
              res--;
              if(!is_range_merge_cover_all(l, r, res->l, res->r))
                  minx = min(minx, abs(res->val - tmp));
          }
          ans[r] = min(ans[r], minx);
      }
      for(int i = 1; i <= l; i++)
          s.insert({pre[l] - pre[i - 1], i, l});
  }
  ```
  核心实现思想：枚举分界点 $l$，倒序枚举 $r$，计算区间 $[l,r]$ 的和 $tmp$，在 $set$ 中查找与 $tmp$ 最接近的区间和更新 $ans[r]$，同时考虑区间和取相反数的情况，判断是否满足性质3更新答案。
- 作者：yzh_Error404 (赞：2)  星级：4星
  - 关键亮点：采用 $O(n^2\log n)$ 解法，用线段树维护更新最小值。先求出所有子区间的左右端点及和并排序，根据区间位置关系分相离、包含、相交三种情况，利用线段树进行区间修改、单点查询操作更新答案。
  ```cpp
  // 核心代码片段
  for(register int i = 1; i < cnt; i++){
      node l = e[i], r = e[i + 1];
      int now = r.val - l.val;
      if(l.l > r.l)swap(l, r);
      if(l.r < r.l){//相离
          change(1, 1, n, l.l, l.r, now);
          change(1, 1, n, r.l, r.r, now);
      }
      else if(l.r > r.r){//包含
          change(1, 1, n, l.l, r.l - 1, now);
          change(1, 1, n, r.r + 1, l.r, now);
      }
      else{//相交
          change(1, 1, n, l.l, r.l - 1, now);
          change(1, 1, n, l.r + 1, r.r, now);
      }
  }
  ```
  核心实现思想：对排序后的相邻区间，根据其位置关系，通过线段树的 `change` 函数对相应区间进行最小值更新操作。
- 作者：lsj2009 (赞：1)  星级：4星
  - 关键亮点：给出 $\Theta(n^2\log{n^2})$ 做法，先证明对于两个连续子序列通过改变 $a_k$ 使两者和相等的条件。利用两个集合分别保存包含和不包含当前元素的区间，通过动态维护集合元素，结合排序后相邻元素差值最小的性质，用 `multiset` 实现高效查询和修改。
  ```cpp
  // 核心代码片段
  void delone(multiset<int>& s,int x) {
      auto it = s.find(x); s.erase(*it);
  }
  void del(PII x) {
      auto it = s2.lower_bound(x);
      auto a = ++it; --it;
      if(a!= s2.end()) {
          if((*a).second!= (*it).second)
              delone(s1, (*a).first - (*it).first);
      }
      if(it!= s2.begin()) {
          auto b = --it; ++it;
          if((*b).second!= (*it).second)
              delone(s1, (*it).first - (*b).first);
          if(a!= s2.end()) {
              if((*a).second!= (*b).second)
                  s1.insert((*a).first - (*b).first);
          }
      }
      s2.erase(it);
  }
  void ins(PII x) {
      auto it = s2.lower_bound(x); 
      if(it!= s2.end()) {
          if((*it).second!= x.second)
              s1.insert((*it).first - x.first);
      }
      if(it!= s2.begin()) {
          auto a = --it; ++it;
          if((*a).second!= x.second)
              s1.insert(x.first - (*a).first);
          if(it!= s2.end()) {
              if((*a).second!= (*it).second)
                  delone(s1, (*it).first - (*a).first);
          }
      }
      s2.insert(x);
  }
  ```
  核心实现思想：通过 `delone` 函数删除 `multiset` 中元素，`del` 函数删除 `s2` 中元素并更新 `s1`，`ins` 函数插入元素到 `s2` 并更新 `s1`，从而动态维护两个集合元素及差值。

• 最优关键思路或技巧：利用问题性质，将有交区间情况归纳为无交情况处理。优化方面，采用合适数据结构如 `set`、`multiset` 结合排序，减少查找时间；或利用线段树进行区间修改和单点查询。离散化技巧在数据规模小的情况下，可将排序复杂度降低。
• 可拓展之处：此类题目属于数组子区间和相关问题，类似套路是先分析子区间和性质，利用排序、数据结构优化查找和更新操作。同类型题可考虑改变条件，如子数组和满足其他关系，或对多个数组进行操作等。
• 相似知识点洛谷题目：
  - P1115 最大子段和：考察对数组子段和的理解与处理。
  - P3166 [CQOI2014]数三角形：涉及组合数学与子区间相关计算。
  - P1631 序列合并：与子数组和类似，需对多个数组组合结果进行处理。 

---
处理用时：69.27秒