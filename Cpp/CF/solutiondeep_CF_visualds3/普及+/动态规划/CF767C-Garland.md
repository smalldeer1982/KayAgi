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

# 💡 Kay的C++算法解析：Garland 深入学习指南 💡

<introduction>
  今天我们来一起分析「Garland」这道C++编程题。这道题是**树形DP（子树和问题）**的经典应用，核心是通过遍历树计算子树权值和，找到能将整棵树分成三个等权部分的两条边。本指南会帮你梳理思路、理解核心算法，并通过像素动画直观感受过程！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：树形DP（子树权值和计算）

🗣️ **初步分析**：
解决「Garland」的关键是**树形DP**——它就像给树的每个节点“称体重”：从叶子节点开始，每个节点的“体重”是自己的权值加上所有子节点的“体重”（后序遍历）。  

本题要求将树分成三个权值相等的子树，所以**整棵树的总权值必须能被3整除**（否则直接输出-1）。之后，我们需要找到**两个子树**，它们的权值正好是总权值的1/3——剪去这两个子树与父节点的边，剩下的部分自然也是1/3的权值！

- **核心思路**：后序DFS计算子树权值和，遇到权值等于1/3总权值的子树，就“剪掉”它（将子树权值重置为0，避免重复计算），最后统计符合条件的子树数量（至少需要3个，前两个就是要剪的边）。
- **可视化设计思路**：用8位像素风格画树，节点是彩色方块，权值显示在旁边。DFS时节点闪烁表示正在计算，找到符合条件的子树时，节点变成红色并播放“叮”的音效，旁边弹出提示“找到一个目标子树！”。


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性等方面筛选了4份优质题解（赞≥4），帮你快速理解核心逻辑：
</eval_intro>

**题解一：maniac！（赞17）**
* **点评**：这份题解的思路最直白——直接用后序DFS计算子树权值和，遇到符合条件的子树就记录并重置权值。代码结构简洁，变量命名清晰（`tem`数组存子树和，`ans`数组存结果），边界条件处理严谨（先判断总权值是否能被3整除）。尤其值得学习的是**“剪枝后重置子树和”**的技巧，避免了重复计算，是本题的核心亮点！

**题解二：无咕_（赞6）**
* **点评**：题解详细解释了树形DP的状态转移方程（`treesum[i] = a[i] + sum(treesum[子节点])`），帮你理解子树和的计算逻辑。代码用结构体`Edge`实现邻接表，结构规范；同时明确指出“剪枝后要减去子树权值”，逻辑严谨。这份题解适合新手入门，帮你建立树形DP的基础认知。

**题解三：kenlig（赞5）**
* **点评**：题解加入了**快读函数**（`qread`），解决了大数据输入的效率问题（这在竞赛中很实用！）。代码中`ksum`数组存子树和，`ans`数组存结果，逻辑与前两份一致，但快读的加入让代码更贴近实际竞赛需求。此外，作者在注释中解释了每一步的作用，可读性很高。

**题解四：chihik（赞4）**
* **点评**：题解用`vector`存图，代码更简洁（不用手动维护邻接表的`head`和`next`指针）。核心逻辑与前几份一致，但`vector`的使用降低了代码复杂度，适合喜欢简洁风格的同学。同时，题解直接用`v1`和`v2`记录前两个符合条件的子树，避免了数组存储，逻辑更直接。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题的核心难点在于**正确计算子树和、处理剪枝后的权值重置，以及确保找到有效解**。结合优质题解，我总结了三个关键思考方向：
</difficulty_intro>

1. **关键点1：如何正确计算子树权值和？**
    * **分析**：子树权值和需要从叶子节点往上累加（后序DFS）——先计算所有子节点的权值和，再加上当前节点的权值。比如，`tem[x] = t[x] + sum(tem[子节点])`（来自maniac！的题解）。这种方式能确保每个节点的权值和包含所有子节点的贡献。
    * 💡 **学习笔记**：后序DFS是计算子树信息的“黄金法则”，一定要记牢！

2. **关键点2：如何处理“剪枝”后的权值？**
    * **分析**：找到符合条件的子树后，必须将它的权值重置为0（比如`tem[x] = 0`）——否则父节点的权值和会包含这个子树的贡献，导致无法找到第二个符合条件的子树。比如，若第一个子树权值是1/3，重置后父节点的权值和会减去这部分，后续才能找到第二个1/3的子树。
    * 💡 **学习笔记**：“剪枝重置”是本题的核心技巧，没有它就无法正确分割树！

3. **关键点3：如何确保找到的子树是有效的？**
    * **分析**：需要统计符合条件的子树数量——至少需要3个（因为整棵树本身也是一个符合条件的“子树”，前两个就是要剪的边）。如果数量≤2，说明无法分成三个等权部分。
    * 💡 **学习笔记**：统计符合条件的子树数量是判断解是否存在的关键！


### ✨ 解题技巧总结
<summary_best_practices>
通过本题，我总结了3个通用解题技巧：
</summary_best_practices>
- **技巧1：先判断边界条件**：总权值不能被3整除？直接输出-1，避免无效计算。
- **技巧2：后序DFS计算子树信息**：子树和、子树大小等问题，都可以用后序DFS解决。
- **技巧3：剪枝后重置状态**：找到目标子树后，重置其权值，避免重复计算。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一个**通用核心实现**，综合了优质题解的思路，结构清晰、易理解：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了maniac！、无咕_等题解的思路，用邻接表存树，后序DFS计算子树和，记录符合条件的子树。
* **完整核心代码**：
```cpp
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1000010;
int n, root, sum, cnt, ans[5];
int t[MAXN]; // 节点权值
vector<int> G[MAXN]; // 邻接表存树
long long tem[MAXN]; // 子树权值和

void dfs(int x, int parent) {
    tem[x] = t[x]; // 初始化为当前节点权值
    for (int v : G[x]) { // 遍历子节点
        if (v == parent) continue;
        dfs(v, x);
        tem[x] += tem[v]; // 累加子节点的权值和
    }
    // 找到符合条件的子树，记录并重置权值
    if (tem[x] == sum / 3 && cnt < 2) {
        ans[++cnt] = x;
        tem[x] = 0;
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int a;
        cin >> a >> t[i];
        sum += t[i];
        if (a == 0) root = i; // 根节点（父亲为0）
        else {
            G[a].push_back(i);
            G[i].push_back(a);
        }
    }
    if (sum % 3 != 0) {
        cout << "-1" << endl;
        return 0;
    }
    dfs(root, 0);
    if (cnt >= 2) cout << ans[1] << " " << ans[2] << endl;
    else cout << "-1" << endl;
    return 0;
}
```
* **代码解读概要**：
  1. 读取输入，构建邻接表（树的结构），计算总权值`sum`。
  2. 判断`sum`是否能被3整除，否则直接输出-1。
  3. 后序DFS计算每个节点的子树权值和`tem[x]`。
  4. 遇到`tem[x] == sum/3`的子树，记录到`ans`数组，并重置`tem[x]`为0。
  5. 最后判断是否找到至少2个符合条件的子树，输出结果。


<code_intro_selected>
接下来剖析优质题解的核心片段，看看它们的亮点：
</code_intro_selected>

**题解一：maniac！**
* **亮点**：简洁的邻接表实现+核心的“剪枝重置”技巧。
* **核心代码片段**：
```cpp
void dfs(int x,int y){
	tem[x]=t[x];
	for(int i=head[x];i;i=next[i]){
		int v=ver[i];
		if(v!=y){
			dfs(v,x);
			tem[x]+=tem[v];
		}
	}
	if(tem[x]==sum) ans[++cnt]=x,tem[x]=0; // 关键：重置权值
}
```
* **代码解读**：
  - `tem[x] = t[x]`：初始化当前节点的子树和为自己的权值。
  - `tem[x] += tem[v]`：累加子节点的权值和。
  - `if (tem[x] == sum) ans[++cnt] = x, tem[x] = 0`：找到符合条件的子树，记录并重置权值，避免父节点重复计算。
* 💡 **学习笔记**：重置权值是本题的“点睛之笔”，一定要记住！

**题解三：kenlig**
* **亮点**：快读函数处理大数据输入。
* **核心代码片段**：
```cpp
inline int qread(){
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
```
* **代码解读**：
  - 快读函数通过直接读取字符，避免了`cin`或`scanf`的性能开销，适合处理1e6级别的大数据。
* 💡 **学习笔记**：竞赛中遇到大数据输入，快读是必备技巧！


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观理解**树形DP计算子树和**的过程，我设计了一个**8位像素风格**的动画，融合复古游戏元素，让你“看”到算法的每一步！
</visualization_intro>

### 动画设计方案
#### 1. 整体风格与场景
- **8位像素风**：参考FC红白机的配色（比如绿色背景、黄色节点、蓝色边），节点是16x16的彩色方块，权值用白色像素字显示。
- **场景布局**：屏幕左侧是像素树，右侧是控制面板（按钮+速度滑块），底部是代码同步区域（显示当前执行的代码行）。

#### 2. 核心动画流程
1. **初始化**：
   - 树的根节点（父亲为0）用红色方块标记，其他节点是黄色。
   - 控制面板显示“开始”“单步”“重置”按钮，速度滑块默认中等。
   - 播放8位风格的背景音乐（比如《超级马里奥》的轻快旋律）。

2. **DFS过程演示**：
   - 当DFS进入一个节点时，节点闪烁**蓝色**，表示正在计算它的子树和。
   - 遍历子节点时，用**绿色箭头**指向子节点，子节点闪烁绿色表示正在处理。
   - 计算完子节点的权值和后，将子节点的权值累加到当前节点（用“+”动画显示）。

3. **找到目标子树**：
   - 当某个节点的子树和等于`sum/3`时，节点变成**红色**，并播放“叮”的音效（类似FC游戏的得分声）。
   - 同时，节点下方弹出文字气泡：“找到目标子树！权值=sum/3”。
   - 重置该节点的权值为0（用“0”动画覆盖原权值）。

4. **结果展示**：
   - 找到两个目标子树后，动画停止，红色节点闪烁，播放“胜利”音效（类似FC游戏的通关声）。
   - 屏幕中央显示“成功！剪去节点X和Y的边”。

#### 3. 交互设计
- **单步执行**：点击“单步”按钮，算法执行一步（比如进入一个节点、处理一个子节点）。
- **自动播放**：滑动速度滑块调整播放速度（慢/中/快），算法自动执行。
- **重置**：点击“重置”按钮，回到初始状态，重新开始动画。

#### 4. 代码同步与旁白
- **代码同步**：底部区域显示当前执行的C++代码行（比如`dfs(v, x);`或`tem[x] += tem[v];`），并高亮当前行。
- **旁白提示**：在关键步骤弹出文字提示，比如“现在计算节点5的子树和，先处理子节点3！”“节点3的子树和等于sum/3，剪去它！”。


<visualization_conclusion>
通过这个像素动画，你能清晰看到**子树和的计算过程**、**目标子树的标记**，以及**权值重置的效果**。复古游戏元素让学习更有趣，音效和动画强化了关键步骤的记忆！
</visualization_conclusion>


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
树形DP（子树和问题）的应用非常广泛，比如**选课问题**、**没有上司的舞会**等。掌握了本题的思路，你可以解决很多类似问题！
</similar_problems_intro>

### 通用思路迁移
树形DP的核心是**后序遍历计算子树信息**，适用于以下场景：
1. 计算子树的权值和/大小（本题）。
2. 选择子树中的节点，满足某些条件（比如选课问题）。
3. 树形结构中的最大/最小值问题（比如没有上司的舞会）。

### 洛谷练习推荐
1. **洛谷 P2014 [CTSC1997]选课**
   - 🗣️ **推荐理由**：经典的树形DP问题，需要选择子树中的课程，最大化学分。本题的后序DFS思路能直接迁移过来！
2. **洛谷 P1352 没有上司的舞会**
   - 🗣️ **推荐理由**：树形DP的经典例题，计算子树中的最大快乐值，需要考虑节点选或不选的情况，强化后序DFS的应用。
3. **洛谷 P3146 248**
   - 🗣️ **推荐理由**：虽然是动态规划，但需要处理树形结构的合并问题，锻炼子树信息的计算能力。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
优质题解中的经验能帮你少走弯路，我摘录了几个关键心得：
</insights_intro>

> **经验1（来自maniac！）**：“找到符合条件的子树后，一定要重置权值为0，否则父节点的权值和会包含它，导致无法找到第二个子树。”
> **点评**：这是本题的核心技巧，很多同学容易忽略这一步，导致错误。重置权值能确保后续的计算不被已剪的子树干扰。

> **经验2（来自kenlig）**：“大数据输入时，快读函数能避免超时。”
> **点评**：竞赛中，`cin`和`scanf`的速度可能不够，快读是处理大数据的必备技巧，一定要掌握！

> **经验3（来自chihik）**：“用vector存图更简洁，不用维护邻接表的指针。”
> **点评**：`vector`的动态数组特性降低了代码复杂度，适合新手使用，能减少出错的概率。


<conclusion>
本次关于「Garland」的分析就到这里！这道题是树形DP的入门经典，核心是**后序DFS计算子树和**和**剪枝重置**。记住：树形问题的关键是“从叶子往上算”，而重置状态能帮你避免重复计算。  

编程能力的提升在于**多练、多思**——试试拓展练习中的题目，巩固一下学到的技巧吧！下次我们再一起探索更有趣的算法问题～💪
</conclusion>

---
处理用时：168.90秒