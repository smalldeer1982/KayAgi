# 题目信息

# Mars rover

## 题目描述

Natasha travels around Mars in the Mars rover. But suddenly it broke down, namely — the logical scheme inside it. The scheme is an undirected tree (connected acyclic graph) with a root in the vertex $ 1 $ , in which every leaf (excluding root) is an input, and all other vertices are logical elements, including the root, which is output. One bit is fed to each input. One bit is returned at the output.

There are four types of logical elements: [AND](https://en.wikipedia.org/wiki/Logical_conjunction) ( $ 2 $ inputs), [OR](https://en.wikipedia.org/wiki/Logical_disjunction) ( $ 2 $ inputs), [XOR](https://en.wikipedia.org/wiki/Exclusive_or) ( $ 2 $ inputs), [NOT](https://en.wikipedia.org/wiki/Negation) ( $ 1 $ input). Logical elements take values from their direct descendants (inputs) and return the result of the function they perform. Natasha knows the logical scheme of the Mars rover, as well as the fact that only one input is broken. In order to fix the Mars rover, she needs to change the value on this input.

For each input, determine what the output will be if Natasha changes this input.

## 说明/提示

The original scheme from the example (before the input is changed):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1010D/12e9ee861137e7cc1d9adb641b01a0e9e6b988c2.png)

Green indicates bits '1', yellow indicates bits '0'.

If Natasha changes the input bit $ 2 $ to $ 0 $ , then the output will be $ 1 $ .

If Natasha changes the input bit $ 3 $ to $ 0 $ , then the output will be $ 0 $ .

If Natasha changes the input bit $ 6 $ to $ 1 $ , then the output will be $ 1 $ .

If Natasha changes the input bit $ 8 $ to $ 0 $ , then the output will be $ 1 $ .

If Natasha changes the input bit $ 9 $ to $ 0 $ , then the output will be $ 0 $ .

## 样例 #1

### 输入

```
10
AND 9 4
IN 1
IN 1
XOR 6 5
AND 3 7
IN 0
NOT 10
IN 1
IN 1
AND 2 8
```

### 输出

```
10110```

# AI分析结果

### 题目重写
# 火星探测器

## 题目描述
娜塔莎乘坐火星探测器在火星上行驶。但突然探测器出故障了，确切地说是其内部的逻辑电路出了问题。该逻辑电路是一棵无向树（连通无环图），根节点为 $1$ 。在这棵树中，除根节点外的每个叶节点都是输入节点，所有其他节点（包括根节点）都是逻辑元件，根节点作为输出节点。每个输入节点输入一个比特位，输出节点返回一个比特位。

逻辑元件有四种类型：[与（AND）](https://en.wikipedia.org/wiki/Logical_conjunction)（$2$ 个输入）、[或（OR）](https://en.wikipedia.org/wiki/Logical_disjunction)（$2$ 个输入）、[异或（XOR）](https://en.wikipedia.org/wiki/Exclusive_or)（$2$ 个输入）、[非（NOT）](https://en.wikipedia.org/wiki/Negation)（$1$ 个输入）。逻辑元件从其直接子节点（输入）获取值，并返回它们执行的函数的结果。娜塔莎知道火星探测器的逻辑电路，并且知道只有一个输入节点出故障了。为了修复火星探测器，她需要改变这个输入节点的值。

对于每个输入节点，确定如果娜塔莎改变这个输入节点的值，输出会是什么。

## 说明/提示
示例中的原始电路（在输入改变之前）：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1010D/12e9ee861137e7cc1d9adb641b01a0e9e6b988c2.png)

绿色表示比特位 '1'，黄色表示比特位 '0'。

如果娜塔莎将输入比特位 $2$ 改为 $0$，则输出将为 $1$。

如果娜塔莎将输入比特位 $3$ 改为 $0$，则输出将为 $0$。

如果娜塔莎将输入比特位 $6$ 改为 $1$，则输出将为 $1$。

如果娜塔莎将输入比特位 $8$ 改为 $0$，则输出将为 $1$。

如果娜塔莎将输入比特位 $9$ 改为 $0$，则输出将为 $0$。

## 样例 #1
### 输入
```
10
AND 9 4
IN 1
IN 1
XOR 6 5
AND 3 7
IN 0
NOT 10
IN 1
IN 1
AND 2 8
```
### 输出
```
10110
```

### 算法分类
深度优先搜索 DFS

### 综合分析与结论
这些题解的核心思路都是基于树结构进行深度优先搜索。主要难点在于分析不同逻辑元件（AND、OR、XOR、NOT）在输入值改变时对输出的影响。各题解通过不同方式标记或判断输入值改变是否会影响到根节点的输出。

### 所选的题解
- **作者：yybyyb（5星）**
  - **关键亮点**：思路清晰，先求出所有节点初始值，再针对 AND 和 OR 操作的特殊情况给子树打标记，判断输入改变是否影响输出，时间复杂度为 $O(n)$。
  - **个人心得**：无
  - **核心代码片段**：
```cpp
void dfs(int u,int ff)
{
    fa[u]=ff;int son[5],tot=0;
    for(int i=h[u];i;i=e[i].next)
        if(e[i].v!=ff)son[++tot]=e[i].v,dfs(e[i].v,u);
    if(p[u]==0)return;
    if(p[u]==1)c[u]=c[son[1]]&c[son[2]];
    if(p[u]==2)c[u]=c[son[1]]^1;
    if(p[u]==3)c[u]=c[son[1]]|c[son[2]];
    if(p[u]==4)c[u]=c[son[1]]^c[son[2]];
    if(p[u]==1)
    {
        int x=son[1],y=son[2];
        if(!c[x])tag[y]=1;if(!c[y])tag[x]=1;
    }
    if(p[u]==3)
    {
        int x=son[1],y=son[2];
        if(c[x])tag[y]=1;if(c[y])tag[x]=1;
    }
}
void dfs2(int u,int ff)
{
    tag[u]|=tag[ff];
    for(int i=h[u];i;i=e[i].next)
        if(e[i].v!=ff)dfs2(e[i].v,u);
}
```
  - **核心实现思想**：`dfs` 函数计算节点初始值，并针对 AND 和 OR 操作标记子树；`dfs2` 函数下传标记。
- **作者：傅思维666（4星）**
  - **关键亮点**：先给出暴力思路，再优化到 $O(n)$ 做法，通过给节点加标记数组表示节点是否随儿子值变化而变化，进而判断输入改变对输出的影响。
  - **个人心得**：呼吁尊重题目和他人，不要轻视看似简单的题目。
  - **核心代码片段**：
```cpp
void dfs2(int u)
{
    if(v[u]==0) 
        v[son[u][0]]=v[son[u][1]]=0;
    else
    {
        switch(opt[u])
        {
            case 2:
                v[son[u][0]]=1;
                break;
            case 3:
                if(val[son[u][0]]) 
                    v[son[u][1]]=0;
                else 
                    v[son[u][1]]=1;
                if(val[son[u][1]]) 
                    v[son[u][0]]=0;
                else 
                    v[son[u][0]]=1;
                break;
            case 4:
                if(!val[son[u][0]])
                    v[son[u][1]]=0;
                else 
                    v[son[u][1]]=1;
                if(!val[son[u][1]]) 
                    v[son[u][0]]=0;
                else 
                    v[son[u][0]]=1;
                break;
            case 5:
                v[son[u][0]]=v[son[u][1]]=1; 
                break;
        }
    }
    v[0]=0;
    if(son[u][0]) 
        dfs2(son[u][0]);
    if(son[u][1]) 
        dfs2(son[u][1]);
}
```
  - **核心实现思想**：`dfs2` 函数根据当前节点操作和子节点值，更新标记数组，判断子节点值改变是否影响当前节点。
- **作者：wurzang（4星）**
  - **关键亮点**：通过给节点打 “废物标签”，表示子树中节点修改对根节点无影响，再通过 `dfs` 下传标签，判断输入改变对输出的影响。
  - **个人心得**：无
  - **核心代码片段**：
```cpp
void redfs(int x){
	if(fw[x]){
		if(ch[x][0]) fw[ch[x][0]]=1,redfs(ch[x][0]);
		if(ch[x][1]) fw[ch[x][1]]=1,redfs(ch[x][1]);
		return;
	}
	if(ch[x][0]) redfs(ch[x][0]);
	if(ch[x][1]) redfs(ch[x][1]);
}
void dfs(int x){
	if(opt[x]==0) return;
	int i=x;
	if(opt[x]==1){
		dfs(ch[i][0]),dfs(ch[i][1]);
		if(val[ch[i][0]]==0) fw[ch[i][1]]=1;
		if(val[ch[i][1]]==0) fw[ch[i][0]]=1;
		val[x]=val[ch[i][0]]&val[ch[i][1]];
		return;	
	} 
	if(opt[x]==2){
		dfs(ch[i][0]),dfs(ch[i][1]);
		val[x]=val[ch[i][0]]^val[ch[i][1]];	
		return;	
	}
	if(opt[x]==3){
		dfs(ch[i][0]),dfs(ch[i][1]);
		if(val[ch[i][0]]==1) fw[ch[i][1]]=1;
		if(val[ch[i][1]]==1) fw[ch[i][0]]=1;
		val[x]=val[ch[i][0]]|val[ch[i][1]];	
		return;	
	}	
	dfs(ch[i][0]);
	val[x]=!val[ch[i][0]];
}
```
  - **核心实现思想**：`dfs` 函数计算节点值，并针对 AND 和 OR 操作打 “废物标签”；`redfs` 函数下传标签。

### 最优关键思路或技巧
利用深度优先搜索遍历树结构，针对 AND 和 OR 操作的特殊性质，通过标记子树的方式快速判断输入值改变对根节点输出的影响，避免重复计算，将时间复杂度优化到 $O(n)$。

### 可拓展之处
同类型题通常围绕树结构和逻辑运算展开，类似算法套路是在树的遍历过程中，根据不同节点的特性（如本题中的逻辑元件类型）进行状态标记和传递，以优化问题求解过程。

### 洛谷推荐题目
- [P1379 八数码难题](https://www.luogu.com.cn/problem/P1379)：涉及状态搜索与图的遍历，与本题类似，需通过合理的状态表示和搜索策略解决问题。
- [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)：基于二叉树结构，通过树形 DP 解决问题，与本题对树结构的处理有相似之处。
- [P1127 词链](https://www.luogu.com.cn/problem/P1127)：需要构建图结构，并进行深度优先搜索，与本题在图和树的搜索应用上有相通点。

### 个人心得摘录与总结
傅思维666提到应尊重每道题目和他人，不要轻视看似简单的题目，这反映出在解题过程中应保持谦逊态度，重视基础，从不同角度理解和解决问题。 

---
处理用时：107.62秒