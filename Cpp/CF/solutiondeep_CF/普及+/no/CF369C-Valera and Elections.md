# 题目信息

# Valera and Elections

## 题目描述

The city Valera lives in is going to hold elections to the city Parliament.

The city has $ n $ districts and $ n-1 $ bidirectional roads. We know that from any district there is a path along the roads to any other district. Let's enumerate all districts in some way by integers from $ 1 $ to $ n $ , inclusive. Furthermore, for each road the residents decided if it is the problem road or not. A problem road is a road that needs to be repaired.

There are $ n $ candidates running the elections. Let's enumerate all candidates in some way by integers from $ 1 $ to $ n $ , inclusive. If the candidate number $ i $ will be elected in the city Parliament, he will perform exactly one promise — to repair all problem roads on the way from the $ i $ -th district to the district $ 1 $ , where the city Parliament is located.

Help Valera and determine the subset of candidates such that if all candidates from the subset will be elected to the city Parliament, all problem roads in the city will be repaired. If there are several such subsets, you should choose the subset consisting of the minimum number of candidates.

## 样例 #1

### 输入

```
5
1 2 2
2 3 2
3 4 2
4 5 2
```

### 输出

```
1
5 
```

## 样例 #2

### 输入

```
5
1 2 1
2 3 2
2 4 1
4 5 1
```

### 输出

```
1
3 
```

## 样例 #3

### 输入

```
5
1 2 2
1 3 2
1 4 2
1 5 2
```

### 输出

```
4
5 4 3 2 
```

# AI分析结果

### 题目内容
# 瓦莱拉与选举

## 题目描述
瓦莱拉居住的城市即将举行市议会选举。
该城市有\(n\)个区以及\(n - 1\)条双向道路。我们知道从任意一个区出发，都能通过道路抵达其他任何区。现在以某种方式将所有区从\(1\)到\(n\)进行编号。此外，对于每条道路，居民们判定它是否为问题道路。问题道路是指需要修复的道路。
有\(n\)位候选人参与竞选。同样以某种方式将所有候选人从\(1\)到\(n\)进行编号。如果候选人\(i\)当选进入市议会，他将履行一项承诺——修复从第\(i\)区到市议会所在的第\(1\)区途中的所有问题道路。
请帮助瓦莱拉确定一个候选人子集，使得若该子集中的所有候选人都当选进入市议会，城市中的所有问题道路都将得到修复。如果存在多个这样的子集，应选择候选人数量最少的子集。

## 样例 #1
### 输入
```
5
1 2 2
2 3 2
3 4 2
4 5 2
```
### 输出
```
1
5 
```

## 样例 #2
### 输入
```
5
1 2 1
2 3 2
2 4 1
4 5 1
```
### 输出
```
1
3 
```

## 样例 #3
### 输入
```
5
1 2 2
1 3 2
1 4 2
1 5 2
```
### 输出
```
4
5 4 3 2 
```

### 算法分类
搜索（深度优先搜索 DFS 相关）

### 题解综合分析与结论
这三道题解都围绕在树形结构上进行搜索来解决问题，目标都是找到能修复所有问题道路的最小候选子集。主要差异在于搜索的具体方式和处理字典序等细节上。
- **wick 的题解**：从\(1\)号点开始深度优先搜索，在搜索过程中，若发现当前点下方有问题道路，先标记下方点，若下方还有问题道路则清除上方点标记并更新标记为更下方点，以此确定需修复道路的点集。最后通过另一个函数调整点集以满足字典序最小要求。
- **Yexuaj 的第一个题解**：先用广度优先搜索记录每个点到\(1\)区之间坏道路的数量，然后根据坏道路数量从大到小排序，再从下往上深度优先搜索确定答案。此方法未严格考虑字典序最小，且代码逻辑相对复杂，理解和维护成本较高。
- **Yexuaj 的第二个题解**：先通过深度优先搜索将向下还有需要修的边标记为不用修，然后再次深度优先搜索，对于每条问题道路找到下方数码最小的点加入答案，从而保证字典序最小。相比第一个题解，思路更清晰，代码可读性更好。

### 所选的题解
- **wick 的题解**：
  - **星级**：4星
  - **关键亮点**：通过在DFS过程中巧妙标记和更新标记点，确定需修复道路的点集，最后通过二次搜索调整字典序，思路清晰且代码实现简洁明了。
  - **个人心得**：无
  ```cpp
  void dfs(int now,int father,int h) {
      book[now]=1;
      num[now]=h;
      for(int k=0; k<E[now].size(); k++) {
          if(book[E[now][k]]) continue;
          if(mark[now][E[now][k]]==2) {
              ans[E[now][k]]=1;
              ans[father]=0;
              dfs(E[now][k],E[now][k],h+1);
          } else dfs(E[now][k],father,h+1);
      }
  }
  void findmin(int now) {
      for(int k=0; k<E[now].size(); k++) {
          if(num[E[now][k]]<num[now]) continue;
          tem=min(tem,E[now][k]);
          findmin(E[now][k]);
      }
  }
  ```
  核心实现思想：`dfs`函数用于标记需要修复道路的点，`findmin`函数用于调整点集满足字典序最小。
- **Yexuaj 的第二个题解**：
  - **星级**：4星
  - **关键亮点**：先通过一次DFS将向下还有需要修的边标记为不用修，简化后续计算，再通过另一次DFS找到字典序最小的点集，思路清晰，代码简洁高效。
  - **个人心得**：无
  ```cpp
  bool pre(int now,int last) {
      bool flag=false;
      for(int i=0; i<E[now].size(); ++i) {
          if(E[now][i]==last)continue;
          if(pre(E[now][i],now)==true) {
              L[now][i]=1;
              flag=true;
          }
          if(L[now][i]==2)
              flag=true;
      }
      return flag;
  }
  int getmin(int p,int l) {
      int tmp=p;
      for(int i=0; i<E[p].size(); ++i) {
          if(E[p][i]==l) continue;
          tmp=min(tmp,getmin(E[p][i],p));
      }
      return tmp;
  }
  void dfs(int p,int l) {
      for(int i=0; i<E[p].size(); ++i) {
          if(E[p][i]!=l) {
              if(L[p][i]==2) 
                  ans.push(getmin(E[p][i],p));
              else dfs(E[p][i],p);
          }
      }
  }
  ```
  核心实现思想：`pre`函数将向下还有需要修的边标记为不用修，`getmin`函数找到下方数码最小的点，`dfs`函数确定最终答案点集。

### 最优关键思路或技巧
- **树形结构上的深度优先搜索**：利用树的结构特点，从根节点（\(1\)号点）开始进行深度优先搜索，在搜索过程中根据问题道路的位置确定需要修复道路的点集。
- **标记和更新策略**：在搜索过程中，通过合理的标记和更新机制，如wick题解中标记和更新需要修复道路的点，以及Yexuaj第二个题解中标记不需要修复的边，简化问题求解过程。
- **字典序处理**：通过二次搜索（如wick题解中的`findmin`函数）或在搜索过程中直接寻找数码最小的点（如Yexuaj第二个题解中的`getmin`函数）来保证答案的字典序最小。

### 拓展与同类型题套路
此类题目通常围绕树形结构展开，常见套路是利用树的递归性质进行深度优先搜索，在搜索过程中根据题目条件标记、更新状态，以达到解决问题的目的。例如，对于一些在树上进行路径统计、节点选择等问题，都可以尝试使用类似的深度优先搜索策略。

### 推荐洛谷题目
- [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)：树上的最大权独立集问题，通过树形DP解决，与本题类似，都需要在树上进行状态的记录和更新。
- [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)：在二叉树上进行节点选择，使得保留的边权之和最大，同样需要利用树的结构特点进行搜索和决策。
- [P1270 “访问”美术馆](https://www.luogu.com.cn/problem/P1270)：在树形结构上进行时间分配和价值计算，通过深度优先搜索和动态规划结合的方式解决问题，与本题在树形结构上的处理思路有相似之处。

### 个人心得摘录与总结
无。

---
处理用时：89.34秒