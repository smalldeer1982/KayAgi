# 题目信息

# Yet Another Walking Robot

## 题目描述

There is a robot on a coordinate plane. Initially, the robot is located at the point $ (0, 0) $ . Its path is described as a string $ s $ of length $ n $ consisting of characters 'L', 'R', 'U', 'D'.

Each of these characters corresponds to some move:

- 'L' (left): means that the robot moves from the point $ (x, y) $ to the point $ (x - 1, y) $ ;
- 'R' (right): means that the robot moves from the point $ (x, y) $ to the point $ (x + 1, y) $ ;
- 'U' (up): means that the robot moves from the point $ (x, y) $ to the point $ (x, y + 1) $ ;
- 'D' (down): means that the robot moves from the point $ (x, y) $ to the point $ (x, y - 1) $ .

The company that created this robot asked you to optimize the path of the robot somehow. To do this, you can remove any non-empty substring of the path. But this company doesn't want their customers to notice the change in the robot behavior. It means that if before the optimization the robot ended its path at the point $ (x_e, y_e) $ , then after optimization (i.e. removing some single substring from $ s $ ) the robot also ends its path at the point $ (x_e, y_e) $ .

This optimization is a low-budget project so you need to remove the shortest possible non-empty substring to optimize the robot's path such that the endpoint of his path doesn't change. It is possible that you can't optimize the path. Also, it is possible that after the optimization the target path is an empty string (i.e. deleted substring is the whole string $ s $ ).

Recall that the substring of $ s $ is such string that can be obtained from $ s $ by removing some amount of characters (possibly, zero) from the prefix and some amount of characters (possibly, zero) from the suffix. For example, the substrings of "LURLLR" are "LU", "LR", "LURLLR", "URL", but not "RR" and "UL".

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
4
4
LRUD
4
LURD
5
RRUDU
5
LLDDR```

### 输出

```
1 2
1 4
3 4
-1```

# AI分析结果

【题目内容】
# 又一个行走的机器人

## 题目描述

有一个机器人在坐标平面上。初始时，机器人位于点 $ (0, 0) $。它的路径由一个长度为 $ n $ 的字符串 $ s $ 描述，字符串由字符 'L', 'R', 'U', 'D' 组成。

每个字符对应一种移动：

- 'L' (左)：表示机器人从点 $ (x, y) $ 移动到点 $ (x - 1, y) $；
- 'R' (右)：表示机器人从点 $ (x, y) $ 移动到点 $ (x + 1, y) $；
- 'U' (上)：表示机器人从点 $ (x, y) $ 移动到点 $ (x, y + 1) $；
- 'D' (下)：表示机器人从点 $ (x, y) $ 移动到点 $ (x, y - 1) $。

创建这个机器人的公司要求你优化机器人的路径。为此，你可以删除路径中的任何非空子串。但公司不希望客户注意到机器人行为的变化。这意味着如果优化前机器人结束路径于点 $ (x_e, y_e) $，那么优化后（即从 $ s $ 中删除某个子串）机器人也应结束路径于点 $ (x_e, y_e) $。

这个优化是一个低预算项目，因此你需要删除尽可能短的非空子串来优化机器人的路径，且不改变其终点。有可能无法优化路径，也有可能优化后的目标路径为空字符串（即删除的子串是整个字符串 $ s $）。

回想一下，$ s $ 的子串是指通过从 $ s $ 中删除一些字符（可能为零）从前缀和后缀中得到的字符串。例如，"LURLLR" 的子串有 "LU", "LR", "LURLLR", "URL"，但不是 "RR" 和 "UL"。

你需要回答 $ t $ 个独立的测试用例。

## 样例 #1

### 输入

```
4
4
LRUD
4
LURD
5
RRUDU
5
LLDDR```

### 输出

```
1 2
1 4
3 4
-1```

【算法分类】
模拟

【题解分析与结论】
该题的核心思路是通过模拟机器人的移动路径，记录每个坐标点第一次出现的位置，当再次遇到该坐标点时，说明存在一个环，可以删除这段路径。所有题解都采用了类似的方法，主要区别在于实现细节和代码风格。

【评分较高的题解】

1. **作者：123456zmy (赞：6)**
   - **星级：4.5**
   - **关键亮点：**
     - 使用 `map` 记录每个坐标点的步数，代码简洁高效。
     - 通过 `(x*100000000)+y` 将二维坐标映射为一维，避免了使用 `pair`，提高了效率。
   - **核心代码：**
     ```cpp
     for(int i=0;i<n;i++) {
         if(vis[(x*100000000)+y]) {
             if(i-vis[(x*100000000)+y]<ansr-ansl) {
                 ansr=i;
                 ansl=vis[(x*100000000)+y];
             }
         }
         vis[(x*100000000)+y]=i+1;
         if(s[i]=='U')++y;
         if(s[i]=='D')--y;
         if(s[i]=='R')++x;
         if(s[i]=='L')--x;
     }
     ```

2. **作者：Priori_Incantatem (赞：3)**
   - **星级：4**
   - **关键亮点：**
     - 使用 `map<pair<int,int>,int>` 记录坐标点的访问时间，思路清晰。
     - 通过 `vis[make_pair(x,y)]` 记录最近一次访问的时间，便于更新答案。
   - **核心代码：**
     ```cpp
     for(int i=1;i<=n;++i) {
         move(s[i],x,y);
         pair<int,int> cur=make_pair(x,y);			
         if(vis[cur] || !x && !y) {
             if(i-vis[cur]<ans) {
                 ans=i-vis[cur];
                 l=vis[cur]+1,r=i;
             }
         }
         vis[cur]=i;
     }
     ```

3. **作者：Aehnuwx (赞：1)**
   - **星级：4**
   - **关键亮点：**
     - 使用 `map<pair<int,int>,int>` 记录坐标点的访问时间，代码结构清晰。
     - 通过 `z=i` 更新坐标点的访问时间，确保记录的是最近一次访问。
   - **核心代码：**
     ```cpp
     for(int i=2;i<=n;i++) {
         x+=mv[s[i]][0];y+=mv[s[i]][1];
         int &z=mp[make_pair(x,y)];
         if(z) {
             if(i-z<len) {
                 len=i-z;ans=make_pair(z+1,i);
             }
         }
         z=i;
     }
     ```

【最优关键思路或技巧】
- **数据结构选择**：使用 `map` 记录坐标点的访问时间，便于快速查找和更新。
- **坐标映射**：将二维坐标映射为一维，可以提高查找效率。
- **最近访问时间更新**：每次访问坐标点时，更新其最近访问时间，确保找到最短的删除路径。

【可拓展之处】
- 类似问题可以扩展到三维空间，或者考虑更多种类的移动指令。
- 可以进一步优化 `map` 的使用，例如使用哈希表来提高查找效率。

【推荐题目】
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
2. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
3. [P1036 选数](https://www.luogu.com.cn/problem/P1036)

【个人心得摘录】
- **调试经历**：部分题解提到在调试过程中发现多测不清空会导致错误，提醒了多测清空的重要性。
- **踩坑教训**：使用 `map` 时，需要注意坐标点的映射方式，避免重复计算或遗漏。

---
处理用时：42.84秒