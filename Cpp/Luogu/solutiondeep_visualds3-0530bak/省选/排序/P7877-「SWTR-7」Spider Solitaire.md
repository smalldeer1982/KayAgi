# 题目信息

# 「SWTR-7」Spider Solitaire

## 题目背景

#### 题目描述下方有简化题意。

![](https://cdn.luogu.com.cn/upload/image_hosting/7tdo8cdf.png)

---

小 A 在玩蜘蛛纸牌。  
为了方便你理解蜘蛛纸牌，小 A 给出了简化后的游戏规则：

- 一副牌有 $n$ 张，从小到大分别为 $1,2,\cdots,n$。
- 现有 $m$ 个牌堆，$1$ 副牌。每个牌堆中有 $0$ 张或多张牌。
- 定义「龙」$a_1,a_2,\cdots,a_d$ 为满足 $a_i-1=a_{i+1}\ (1\leq i<d)$ 的任意多张连续的牌。**一张牌也是一个「龙」。**
- 一组连续的牌可以移动，当且仅当这组牌形成了一个「龙」，且「龙」在牌堆的**最右边**。
- 一组连续的牌只能移动到一个**非空**牌堆的最右边，**且必须满足可以与该非空牌堆最右边的「龙」构成一条更大的「龙」**。
- 游戏胜利，当且仅当所有的 $n$ 张牌形成了一个「龙」。

---

例如当 $m=3$，$n=9$，局面为

```plain
9 8 4 3 2 1
7 5
6
```

时，第一个牌堆最右边的 `4 3 2 1` 形成了一个「龙」，所以 `4 3 2 1` 可以移动。将 `4 3 2 1` 移动到第二个牌堆的最右边，此时局面为

```plain
9 8
7 5 4 3 2 1
6
```

接下来将第二个牌堆右边的 `5 4 3 2 1` 移动到第三个牌堆的最右边，此时局面为

```plain
9 8
7
6 5 4 3 2 1
```

接下来将第三个牌堆的 `6 5 4 3 2 1` 移动到第二个牌堆的最右边，此时局面为

```plain
9 8
7 6 5 4 3 2 1
\
```

接下来将第二个牌堆的 `7 6 5 4 3 2 1` 移动到第一个牌堆的最右边，此时牌堆为

```plain
9 8 7 6 5 4 3 2 1
\
\
```

因为所有 $9$ 张牌形成了一个「龙」，所以游戏胜利。

## 题目描述

给定一个蜘蛛纸牌初始局面，小 A 想知道能否获得胜利。若能，请输出 $\texttt{YES}$ 以及**获胜所需的最小步数**。否则输出 $\texttt{NO}$。

小 A 还想知道，对于每张牌 $i$，如果要移动 $i$ 至少需要多少步，**包括移动 $i$ 的这一步**。如果无法移动输出 `-1`。

---

#### 「简化题意」

有 $m$ 个**横向**的数堆，数堆里共有 $n$ 个数，每个数堆里有 $0$ 或多个数。所有数堆里的数组成了 $1\sim n$ 中的所有数。

你可以将一个数堆**最右边递减且公差为 $-1$ 的**连续若干个数 $a_1,a_2,\cdots,a_c$ **按照原来的顺序移到另外一个非空数堆的最右边**，当且仅当该非空数堆最右边的一个数 $b=a_1+1$。

求将所有的 $n$ 个数都移动到同一个数堆且满足从左往右依次递减的最小步数。如果无解输出 $\texttt{NO}$。

**此外，你还需要对于每个数 $i$，输出如果要移动 $i$ 至少需要多少步。**

## 说明/提示

**「样例 1 说明」**

因为 1,2,3,4,5 可以直接移动，所以至少需要 1 步即可移动。  
因为需要先将 5 移至 6 右侧，6 才能移动，所以至少需要 2 步即可移动。  
因为需要先将 5 移至 6 右侧，再将 4,3,2,1 移至 5 右侧，7 才能移动，所以至少需要 3 步即可移动。  
显然 8,9 无法移动。

**「Special Judge」**

本题使用 Special Judge，请**严格遵守输出格式**：

- 如果你正确输出对能否获胜的判定，且如果能够获胜，你正确输出最小步数，你将获得该测试点**至少** $40\%$ 的分数。
- **在上一部分的基础上**，如果你正确输出移动每张牌的最小步数，你将获得该测试点**剩下** $60\%$ 的分数。也就是说，如果你上一部分输出错误，你在这一部分也不会获得任何分数。
- **如果你的输出格式错误，你将获得该测试点 $0\%$ 的分数**，包括但不限于**只输出对能否获胜的判定**。
- 需要特别注意的是，如果你不能正确求出移动每张牌的最小步数，请**随机输出 $[-1,n]$ 之间的任意整数**，否则你将获得该测试点 $0\%$ 的分数。
- 每行结束后你都需要输出换行符，**包括最后一行**。

checker 将在题目最后给出。

**「数据范围与约定」**

**本题采用捆绑测试。**

- Subtask #0（0 points）：是样例。
- Subtask #1（15 points）：$n\leq 3\times 10^3$，$m=2$。
- Subtask #2（15 points）：$b_i>b_{i+1}\ (1\leq i<c)$，$n\leq 3\times 10^3$。
- Subtask #3（25 points）：$n\leq 14$，$m=3$。
- Subtask #4（30 points）：$n\leq 3\times 10^3$。
- Subtask #5（15 points）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n,m\leq 5\times 10^4$。时间限制 1s，空间限制 512MB。

**「题目来源」**

[Sweet Round 07](https://www.luogu.com.cn/contest/51773) D。  
idea & solution & data：[Alex_Wei](https://www.luogu.com.cn/user/123294)；验题：[chenxia25](https://www.luogu.com.cn/user/138400)。

---

以下是 checker，你需要有 testlib.h 才能成功编译。

```cpp
#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pii pair <int,int>
#define fi first
#define se second
#define pb emplace_back
#define mp make_pair 
#define vint vector <int>
#define vpii vector <pii>
#define all(x) x.begin(),x.end()
#define sor(x) sort(all(x))
#define rev(x) reverse(all(x))
#define mem(x,v) memset(x,v,sizeof(x))

#define rint inf.readInt
#define reof inf.readEof()
#define reoln inf.readEoln()
#define rspace inf.readSpace()

// wrong answer : quitf(_wa,"The answer is wrong")
// accepted :  quitf(_ok,"The answer is correct")
// partly correct : quitp(0.5,"The answer is partly correct")

int main(int argc,char* argv[]){
	registerTestlibCmd(argc,argv);
	
	string jans=ans.readToken();
	string pans=ouf.readToken(jans);
	int sub=rint(),n=rint(),diff=0;
	
	if(jans=="YES"){
		int jstep=ans.readInt();
		int pstep=ouf.readInt();
		if(jstep!=pstep)quitf(_wa,"The answer is wrong");
	}
	
	for(int i=1;i<=n;i++){
		int jans=ans.readInt();
		int pans=ouf.readInt();
		if(jans!=pans)diff=1;
	}
	
	while(!ouf.seekEof())ouf.readToken();
	while(!inf.seekEof())inf.readToken();
	while(!ans.seekEof())ans.readToken();
	if(diff)quitp(0.4,"The answer is partially correct");
	else quitf(_ok,"OK, you AK IOI");
	
	return 0;
}
```

## 样例 #1

### 输入

```
0
9 3
6 9 8 4 3 2 1
2 7 5
1 6
```

### 输出

```
YES
4
1
1
1
1
1
2
3
-1
-1
```

## 样例 #2

### 输入

```
0
13 4
4 13 10 1 7
3 11 4 8
4 6 5 3 2
2 12 9
```

### 输出

```
YES
10
2
2
2
3
3
3
1
1
3
6
7
8
-1
```

## 样例 #3

### 输入

```
0
5 1
5 5 4 3 2 1
```

### 输出

```
YES
0
-1
-1
-1
-1
-1
```

## 样例 #4

### 输入

```
0
17 10
2 12 14
1 3
3 1 13 15
0
2 9 8
1 5
3 16 7 6
2 11 2
1 4
2 17 10
```

### 输出

```
YES
14
4
1
1
1
1
1
1
1
1
2
3
4
3
1
2
4
-1```

## 样例 #5

### 输入

```
0
13 4
4 10 1 13 7
4 11 12 4 8
4 6 5 3 2
1 9
```

### 输出

```
NO
-1
2
2
3
3
3
1
1
-1
-1
6
5
-1
```

# AI分析结果



# 算法分类  
**图论（拓扑排序/DAG处理）**

---

# 题解思路与核心难点  

## 核心思路  
1. **牌块压缩**：将每个牌堆中的连续递减序列（龙）压缩为独立节点  
2. **依赖图构建**：  
   - 同一牌堆中上方牌块需先于当前牌块移动（纵向依赖）  
   - 目标牌堆中当前牌块的后继牌块需先移动（横向依赖）  
3. **拓扑排序验证**：若图存在环则无解，否则最小步数为总块数-1  
4. **bitset优化**：通过位运算高效计算每个牌块的前驱步数  

## 解决难点  
- **依赖关系建模**：需同时考虑牌堆内纵向叠加关系和跨牌堆的龙衔接条件  
- **动态步数统计**：通过拓扑排序过程中维护bitset，记录每个节点的可达节点数  
- **线性复杂度保证**：采用后缀优化建图 + bitset压缩，将时间复杂度控制在O(n²/ω)  

---

# 题解评分（≥4星）  

1. **gyh20（★★★★☆）**  
   - 亮点：并查集处理连续牌块，清晰的依赖建图逻辑，完整处理移动条件  
   - 不足：代码中部分变量命名不够直观  

2. **Graphcity（★★★★☆）**  
   - 亮点：fa/link双重关系建模，可视化示例辅助理解  
   - 不足：预处理步骤较复杂，代码可读性略低  

3. **Nuisdete（★★★★☆）**  
   - 亮点：简洁的缩点实现，明确的移动条件分类讨论  
   - 不足：未完整处理牌块间的纵向依赖关系  

---

# 最优思路提炼  

## 关键技巧  
1. **双依赖建图**  
   ```python  
   # 伪代码示例  
   for 每个牌块节点u:  
      添加纵向依赖 u → 上方牌块  
      if u+1存在:  
         添加横向依赖 u → (u+1所在牌堆的后继牌块)  
   ```  
2. **bitset可达性传播**  
   ```cpp  
   // gyh20代码片段  
   bitset<50002> B[50002];  
   void topological_sort() {  
       while(!q.empty()) {  
           int x = q.front();  
           for 所有下游节点y:  
               B[y] |= B[x];  // 传播可达性  
       }  
   }  
   ```  

---

# 相似题目推荐  
1. [P1137 旅行计划](https://www.luogu.com.cn/problem/P1137)（拓扑排序+动态规划）  
2. [P1983 车站分级](https://www.luogu.com.cn/problem/P1983)（隐含依赖关系建模）  
3. [P2741 [USACO4.4] 重叠的图像](https://www.luogu.com.cn/problem/P2741)（拓扑排序求绘制顺序）  

---

# 可视化设计  

## 像素风格算法演示  
**动画要素**：  
1. **牌块表示**：  
   - 8x8像素方块，颜色按牌值渐变（红→蓝）  
   - 当前操作块高亮黄色边框  
2. **依赖关系**：  
   - 纵向依赖：↑箭头（深灰色）  
   - 横向依赖：→箭头（浅绿色）  
3. **拓扑过程**：  
   - 入度减为0时播放"叮"音效  
   - 完成拓扑排序时播放胜利音效  

**交互功能**：  
- **速度调节**：拖拽条控制单步延迟（0.1s~5s）  
- **自动模式**：AI自动运行拓扑排序（类似贪吃蛇AI移动）  
- **故障提示**：发现环路时屏幕闪烁红光，播放警报音  

## 核心动画逻辑  
```javascript  
// 伪代码示例  
class Block {  
  constructor(val, pos) {  
    this.sprite = createPixelSprite(val); // 创建像素精灵  
    this.dependencies = []; // 依赖的块列表  
  }  
  addDependency(target) {  
    drawArrow(this.pos, target.pos); // 绘制依赖箭头  
  }  
  resolve() {  
    this.sprite.flash(); // 高亮闪烁  
    playSound('click'); // 播放点击音效  
  }  
}  

function runTopology() {  
  while (queue.notEmpty()) {  
    let curr = queue.dequeue();  
    curr.resolve();  
    curr.propagate(); // 传播bitset状态  
  }  
}  
```  

---

# 代码实现片段  

## gyh20解法核心逻辑  
```cpp  
// 并查集压缩连续牌块  
for(re int i=1;i<=m;++i){
    for(re int j=1;j<V[i].size();++j)
        if(V[i][j]==V[i][j-1]-1)
            fa[V[i][j]] = V[i][j-1];
}

// 依赖建图  
for(re int i=1;i<=m;++i){
    for(re int j=0;j<V[i].size();++j)
        if(fa[V[i][j]] == V[i][j]){
            int x = 目标牌块;
            add(x, V[i][j]); // 添加横向依赖
        }
}

// 拓扑排序与bitset传播  
while(!q.empty()){
    int x = q.front(); 
    B[x][x] = 1;
    for 所有下游节点y {
        B[y] |= B[x];
        if(--d[y] == 0) q.push(y);
    }
}
```  

完整代码见原题解。

---
处理用时：68.53秒