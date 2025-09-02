# 题目信息

# Love Triangles

## 题目描述

There are many anime that are about "love triangles": Alice loves Bob, and Charlie loves Bob as well, but Alice hates Charlie. You are thinking about an anime which has $ n $ characters. The characters are labeled from $ 1 $ to $ n $ . Every pair of two characters can either mutually love each other or mutually hate each other (there is no neutral state).

You hate love triangles (A-B are in love and B-C are in love, but A-C hate each other), and you also hate it when nobody is in love. So, considering any three characters, you will be happy if exactly one pair is in love (A and B love each other, and C hates both A and B), or if all three pairs are in love (A loves B, B loves C, C loves A).

You are given a list of $ m $ known relationships in the anime. You know for sure that certain pairs love each other, and certain pairs hate each other. You're wondering how many ways you can fill in the remaining relationships so you are happy with every triangle. Two ways are considered different if two characters are in love in one way but hate each other in the other. Print this count modulo $ 1000000007 $ .

## 说明/提示

In the first sample, the four ways are to:

- Make everyone love each other
- Make 1 and 2 love each other, and 3 hate 1 and 2 (symmetrically, we get 3 ways from this).

In the second sample, the only possible solution is to make 1 and 3 love each other and 2 and 4 hate each other.

## 样例 #1

### 输入

```
3 0
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 4
1 2 1
2 3 1
3 4 0
4 1 0
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4 4
1 2 1
2 3 1
3 4 0
4 1 1
```

### 输出

```
0
```

# AI分析结果



## 唯一算法分类
**并查集/二分图判定**

---

## 综合分析与结论

### 核心思路
所有合法图必须满足以下两个条件：
1. **二分图性质**：每个连通块必须是二分图（通过爱恨边的约束关系推导）
2. **连通块独立性**：每个连通块内部关系确定，不同连通块之间可自由选择两种关系模式

### 算法流程
1. **约束建模**：爱边（1）要求两点同色，恨边（0）要求两点异色
2. **连通性判断**：使用带权并查集或DFS染色，维护每个节点的颜色关系
3. **矛盾检测**：若合并时发现颜色冲突，则直接返回无解
4. **连通块计数**：合法情况下，最终答案为 $2^{(连通块数-1)} \mod 10^9+7$

### 可视化设计
- **像素动画**：用 8-bit 风格网格表示节点，爱边显示为绿色，恨边显示为红色
- **动态合并**：并查集合并时，用闪烁效果标记操作节点，下方状态栏显示当前连通块数
- **矛盾提示**：检测到冲突时，触发红色闪烁和 "Error" 音效（类似经典游戏《魂斗罗》的失败音）
- **自动演示**：按空格键切换手动/自动模式，自动模式以0.5秒步进展示合并过程

---

## 题解清单（评分≥4星）

### 1. Cry_For_theMoon（5星）
- **亮点**：带权并查集实现简洁，维护异或权值判断关系矛盾
- **代码**：通过路径压缩时的异或操作维护相对关系
```c++
int Find(int x){
    if(fa[x]==x)return x;
    int rt=Find(fa[x]);
    d[x] ^= d[fa[x]]; // 路径压缩时更新相对关系
    return fa[x]=rt;
}
```

### 2. Brioche（4星）
- **亮点**：DFS染色清晰展示二分图判定逻辑
- **调试心得**：在DFS中同时处理爱恨边的约束传播
```c++
void dfs(int u, int ff, int ty){
    if(vis[u]){
        if(cor[u]!=ty) exit(0); // 发现矛盾立即终止
        return;
    }
    vis[u]=1; cor[u]=ty;
    for(/*遍历邻接边*/){
        dfs(v,u,(e[i].w?ty:-ty)); // 根据边类型传播颜色
    }
}
```

### 3. cosf（4星）
- **亮点**：通过等价类分析直接得出二分图结论
- **思维角度**："所有合法关系构成等价类，最多两个集合"

---

## 核心代码实现（Cry_For_theMoon版）
```c++
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+10, mod=1e9+7;

ll fa[MAXN], d[MAXN], vis[MAXN], power[MAXN];

int Find(int x){
    if(fa[x]==x) return x;
    int rt=Find(fa[x]);
    d[x] ^= d[fa[x]]; // 维护异或权值
    return fa[x]=rt;
}

int main(){
    // 预处理2的幂次
    power[0]=1;
    for(int i=1;i<=1e5;i++) 
        power[i]=power[i-1]*2%mod;

    int n,m; cin>>n>>m;
    for(int i=1;i<=n;i++) fa[i]=i;

    while(m--){
        int u,v,w; cin>>u>>v>>w;
        int ru=Find(u), rv=Find(v);
        if(ru == rv){ // 已连通时检查约束
            if((w==1 && d[u]!=d[v]) || 
               (w==0 && d[u]==d[v])) return cout<<0,0;
        }else{
            fa[ru] = rv;
            d[ru] = d[u]^d[v]^(!w); // 关键合并逻辑
        }
    }

    // 统计连通块数
    int cnt=0;
    for(int i=1;i<=n;i++)
        if(Find(i)==i) cnt++;
    
    cout<<power[cnt-1];
}
```

---

## 相似题目推荐
1. **P1525 关押罪犯**（并查集分集合）
2. **P3386 二分图最大匹配**（二分图基础应用）
3. **P1892 团伙**（种类并查集基础）

---

## 可视化算法演示设计

### 像素风格实现
```html
<canvas id="demo" width="640" height="480"></canvas>
<script>
const palette = ["#000","#F00","#0F0","#FF0","#00F","#FFF"];
class PixelAnim {
    constructor(n){
        this.nodes = Array(n).fill().map((_,i)=>({
            x: 50+(i%8)*70, y: 50+Math.floor(i/8)*70, // 8x8网格布局
            color: 0, root: i 
        }));
        this.edges = [];
    }
    
    draw(ctx){
        ctx.fillStyle = palette[5];
        ctx.fillRect(0,0,640,480);
        // 绘制边和节点...
    }
    
    merge(u, v, type){
        // 显示合并动画：u节点闪烁黄色后变为v的颜色
        this.playSound(type ? 'blip' : 'error');
    }
}
</script>
```

### 交互功能
- **WASD** 移动视角
- **空格** 暂停/继续
- **数字键1-3** 切换不同解法动画
- **H** 显示帮助信息（含当前连通块数）

---

## 个人心得摘录
> "_lbw 在题解中提到：'难度虚高'，反映出此类问题一旦理解二分图本质，代码实现反而简洁。关键在于将题目约束转化为颜色传播问题" 

> "esquigybcu 的异或性质推导揭示：三元环约束本质上构建了传递性关系系统，这与布尔方程的可满足性有深刻联系"

---
处理用时：86.05秒