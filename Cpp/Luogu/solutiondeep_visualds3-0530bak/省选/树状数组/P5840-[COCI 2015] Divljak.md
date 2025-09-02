# 题目信息

# [COCI 2015] Divljak

## 题目描述

Alice 有 $n$ 个字符串 ${S}_1, {S}_2, \ldots, {S}_n$，Bob 有一个字符串集合 ${T}$，一开始集合是空的。

接下来会发生 $q$ 个操作，操作有两种形式：

1. `1 P`：Bob 往自己的集合里添加了一个字符串 ${P}$。
2. `2 x`：Alice 询问 Bob，集合 ${T}$ 中有多少个字符串包含串 ${S}_x$（我们称串 ${A}$ 包含串 ${B}$，当且仅当 ${B}$ 是 ${A}$ 的子串）。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n,q \leq 10^5$，字符串由小写字母构成，$S$ 和 $P$ 的总长分别 $\le 2 \times 10^6$。


## 样例 #1

### 输入

```
3
a
bc
abc
5
1 abca
2 1
1 bca
2 2
2 3
```

### 输出

```
1
2
1
```

# AI分析结果



## 唯一算法分类
AC自动机、树上差分、树状数组

---

## 综合分析与结论

### 核心思路
所有题解均采用AC自动机与fail树的核心框架，结合树上差分和树状数组维护子树和。具体实现步骤如下：
1. **构建AC自动机**：将所有S串插入Trie树，构建fail指针形成fail树
2. **树上差分预处理**：对fail树进行DFS序预处理，建立树状数组维护差分标记
3. **处理插入操作**：
   - 将字符串P在AC自动机上走一遍，记录所有经过的节点
   - 按DFS序排序去重后，对每个节点到根的链进行+1操作，对相邻节点的LCA进行-1操作
4. **查询操作**：查询S_x对应节点在fail树上的子树和

### 可视化设计要点
1. **AC自动机构建**：动态显示Trie树生长过程，fail指针用虚线箭头连接
2. **插入字符串匹配**：高亮当前字符对应的节点，显示fail树上的覆盖路径（红色路径）
3. **差分操作动画**：
   - 当处理相邻节点时，显示LCA节点的位置（黄色高亮）
   - 树状数组更新时，用蓝色闪烁表示+1操作，红色闪烁表示-1操作
4. **树状数组可视化**：以柱状图形式展示DFS序对应的值，实时更新子树区间

### 复古像素风格实现
1. **Trie节点**：用8x8像素方块表示，不同颜色区分普通节点与终止节点
2. **fail指针**：用绿色像素虚线连接，动态绘制时有"滋滋"音效
3. **树状数组更新**：对应区块用爆炸粒子特效，配合8-bit风格的"哔"声
4. **自动演示模式**：按空格键可切换自动/手动模式，自动模式时算法步骤以0.5秒间隔执行

---

## 题解清单 (≥4星)

1. **Calculatelove (★★★★★)**  
   - 亮点：最早提出fail树上链求并的差分策略，代码用树状数组高效实现
   - 关键代码：排序后链式差分处理
   ```c++
   sort(seq + 1, seq + len + 1, cmp);
   for(int i=1; i<=len; i++) add(dfn[seq[i]],1);
   for(int i=1; i<len; i++) add(dfn[lca(seq[i],seq[i+1])],-1);
   ```

2. **皎月半洒花 (★★★★☆)**  
   - 亮点：详细解释dfs序排序的必要性，提出虚树思想
   - 调试心得：提到"_end是关键字"的编译错误，具有实践警示意义

3. **MoYuFang (★★★★☆)**  
   - 亮点：完整实现树剖求LCA，代码结构清晰
   - 关键优化：预处理DFS序后直接使用树状数组维护

---

## 核心代码实现

```c++
// AC自动机构建
void build(){
    queue<int> q;
    for(int i=0; i<26; i++)
        if(tr[0][i]) q.push(tr[0][i]);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int i=0; i<26; i++){
            if(tr[u][i]) 
                fail[tr[u][i]] = tr[fail[u]][i], q.push(tr[u][i]);
            else 
                tr[u][i] = tr[fail[u]][i];
        }
    }
}

// 插入处理
void handle(char *s){
    int p = 1, len = strlen(s+1), cnt = 0;
    static int stk[MAXN];
    for(int i=1; i<=len; i++){
        p = tr[p][s[i]-'a'];
        stk[++cnt] = p;
    }
    sort(stk+1, stk+cnt+1, [](int x,int y){return dfn[x]<dfn[y];});
    cnt = unique(stk+1, stk+cnt+1) - stk - 1;
    for(int i=1; i<=cnt; i++){
        update(dfn[stk[i]], 1);
        if(i>1) update(dfn[lca(stk[i],stk[i-1])], -1);
    }
}

// 树状数组查询
int query(int x){
    return bit.query(ed[x]) - bit.query(dfn[x]-1);
}
```

---

## 相似题目推荐
1. P3796 【模板】AC自动机（加强版）
2. P5357 【模板】AC自动机（二次加强版）
3. P2414 [NOI2011] 阿狸的打字机

---

## 可视化伪代码示例（Canvas动画）
```javascript
class ACAnimator {
  constructor() {
    this.nodes = []; // 节点坐标
    this.edges = []; // 连线
    this.currentPath = []; // 当前插入字符串路径
  }

  drawTrie() {
    // 绘制Trie树结构，动态添加节点
  }

  highlightPath(node) {
    // 高亮当前匹配路径，红色闪烁效果
  }

  showDiff(u, v, lcaNode) {
    // 显示u到根、v到根的路径，黄色高亮LCA节点
    // 播放"click"音效
  }

  updateBIT(pos, val) {
    // 树状数组对应位置柱状图变化
    // 蓝色+1，红色-1
  }
}
```

---
处理用时：75.43秒