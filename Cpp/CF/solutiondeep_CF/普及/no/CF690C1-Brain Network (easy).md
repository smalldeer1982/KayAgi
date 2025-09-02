# 题目信息

# Brain Network (easy)

## 题目描述

One particularly well-known fact about zombies is that they move and think terribly slowly. While we still don't know why their movements are so sluggish, the problem of laggy thinking has been recently resolved. It turns out that the reason is not (as previously suspected) any kind of brain defect – it's the opposite! Independent researchers confirmed that the nervous system of a zombie is highly complicated – it consists of $ n $ brains (much like a cow has several stomachs). They are interconnected by brain connectors, which are veins capable of transmitting thoughts between brains. There are two important properties such a brain network should have to function properly:

1. It should be possible to exchange thoughts between any two pairs of brains (perhaps indirectly, through other brains).
2. There should be no redundant brain connectors, that is, removing any brain connector would make property 1 false.

If both properties are satisfied, we say that the nervous system is valid. Unfortunately (?), if the system is not valid, the zombie stops thinking and becomes (even more) dead. Your task is to analyze a given nervous system of a zombie and find out whether it is valid.

## 样例 #1

### 输入

```
4 4
1 2
2 3
3 1
4 1
```

### 输出

```
no
```

## 样例 #2

### 输入

```
6 5
1 2
2 3
3 4
4 5
3 6
```

### 输出

```
yes
```

# AI分析结果



# Brain Network (easy)

## 题目描述

关于僵尸的一个特别著名的事实是它们移动和思考极其缓慢。虽然我们仍不知道为何它们的动作如此迟缓，但最近解决了它们思考滞后的问题。原来原因并非（如之前推测的）任何大脑缺陷，而是恰恰相反！独立研究者证实僵尸的神经系统高度复杂——由 $n$ 个大脑组成（类似牛有多个胃）。它们通过脑连接器互连，这些是能在脑间传递思想的血管。这样的脑网络应具备两个重要属性才能正常运作：

1. 必须能在任意两个大脑间交换思想（可能间接通过其他大脑）。
2. 不能有冗余的脑连接器，即移除任何连接器都会使属性1失效。

若同时满足这两个属性，则神经系统是有效的。你的任务是分析给定僵尸的神经系统，判断其是否有效。

## 算法分类
并查集

---

## 题解分析与结论

题目要求判断无向图是否为树，即满足：边数 = n-1 且 连通且无环。根据图论结论，当边数 = n-1 时，只需验证连通性即可（此时无环是必然的）。

### 精选题解

#### 1. Larry76 的题解（★★★★☆）
**关键亮点**：
- 使用并查集同时处理环检测与连通性判断
- 通过并查集合并时的路径压缩优化效率
- 无需显式检查边数，通过连通性和环检测隐式覆盖所有情况

**核心代码**：
```cpp
namespace Larry76{
    const int MAX_SIZE = 1.1e5;
    int fa[MAX_SIZE];
    int getfa(int x){
        if(fa[x]==x)
            return fa[x];
        return fa[x] = getfa(fa[x]);
    }
    void merge(int x,int y){
        int fx = getfa(x);
        int fy = getfa(y);
        fa[fy] = fx;
    }
    void main(){
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++)
            fa[i] = i;
        while(m--){
            int u,v;
            cin>>u>>v;
            if(getfa(u)==getfa(v)){ // 环检测
                cout<<"no"<<endl;
                return;
            }
            merge(u,v);
        }
        int same = 0;
        for(int i=1;i<=n;i++) // 连通性验证
            if(fa[i] == i) same++;
        cout<<(same>1 ? "no" : "yes");
    }
}
```

#### 2. loser_seele 的题解（★★★☆☆）
**亮点**：
- 显式检查边数边界条件
- 代码简洁直接
- 通过并查集实现基础验证

**可改进点**：
- 环检测在边数合法情况下冗余
- 未显式处理多个连通分量

---

### 最优技巧总结
1. **隐式边数检查**：通过环检测自动处理边数过多的情况（当边数 > n-1 时必然存在环）
2. **路径压缩优化**：提升并查集查询效率至近似 O(1)
3. **连通性验证**：通过统计根节点数量判断整体连通性

---

### 扩展训练
1. [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)  
   （并查集基础应用）
2. [P3958 奶酪](https://www.luogu.com.cn/problem/P3958)  
   （三维连通性判断）
3. [P1197 [JSOI2008] 星球大战](https://www.luogu.com.cn/problem/P1197)  
   （动态连通性问题）

---
处理用时：394.89秒