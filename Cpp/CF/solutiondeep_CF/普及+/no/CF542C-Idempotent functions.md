# 题目信息

# Idempotent functions

## 题目描述

Some time ago Leonid have known about idempotent functions. Idempotent function defined on a set $ {1,2,...,n} $ is such function ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF542C/bd89689373264189cd84dae0d69467be68ca323b.png), that for any ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF542C/9a41c8470dbaa5967772aedda0040717aaf30fea.png) the formula $ g(g(x))=g(x) $ holds.

Let's denote as $ f^{(k)}(x) $ the function $ f $ applied $ k $ times to the value $ x $ . More formally, $ f^{(1)}(x)=f(x) $ , $ f^{(k)}(x)=f(f^{(k-1)}(x)) $ for each $ k&gt;1 $ .

You are given some function ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF542C/7ed3c9bd96ebefaf9c2ae2aa09921c0d35366e17.png). Your task is to find minimum positive integer $ k $ such that function $ f^{(k)}(x) $ is idempotent.

## 说明/提示

In the first sample test function $ f(x)=f^{(1)}(x) $ is already idempotent since $ f(f(1))=f(1)=1 $ , $ f(f(2))=f(2)=2 $ , $ f(f(3))=f(3)=2 $ , $ f(f(4))=f(4)=4 $ .

In the second sample test:

- function $ f(x)=f^{(1)}(x) $ isn't idempotent because $ f(f(1))=3 $ but $ f(1)=2 $ ;
- function $ f(x)=f^{(2)}(x) $ is idempotent since for any $ x $ it is true that $ f^{(2)}(x)=3 $ , so it is also true that $ f^{(2)}(f^{(2)}(x))=3 $ .

In the third sample test:

- function $ f(x)=f^{(1)}(x) $ isn't idempotent because $ f(f(1))=3 $ but $ f(1)=2 $ ;
- function $ f(f(x))=f^{(2)}(x) $ isn't idempotent because $ f^{(2)}(f^{(2)}(1))=2 $ but $ f^{(2)}(1)=3 $ ;
- function $ f(f(f(x)))=f^{(3)}(x) $ is idempotent since it is identity function: $ f^{(3)}(x)=x $ for any ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF542C/11e22b0eed3b852ef44d62d2479b42e2534a18a6.png) meaning that the formula $ f^{(3)}(f^{(3)}(x))=f^{(3)}(x) $ also holds.

## 样例 #1

### 输入

```
4
1 2 2 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
2 3 3
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
2 3 1
```

### 输出

```
3
```

# AI分析结果

### 题目内容
# 幂等函数

## 题目描述
不久前，列昂尼德了解到了幂等函数。定义在集合\(\{1,2,\cdots,n\}\)上的幂等函数\(g\)满足，对于任意\(x\in\{1,2,\cdots,n\}\)，公式\(g(g(x)) = g(x)\)成立。

我们将\(f^{(k)}(x)\)表示为函数\(f\)对值\(x\)应用\(k\)次。更正式地，\(f^{(1)}(x)=f(x)\)，对于每个\(k>1\)，\(f^{(k)}(x)=f(f^{(k - 1)}(x))\)。

给定某个函数\(f\)。你的任务是找到最小的正整数\(k\)，使得函数\(f^{(k)}(x)\)是幂等的。

## 说明/提示
在第一个样例测试中，函数\(f(x)=f^{(1)}(x)\)已经是幂等的，因为\(f(f(1)) = f(1)=1\)，\(f(f(2)) = f(2)=2\)，\(f(f(3)) = f(3)=2\)，\(f(f(4)) = f(4)=4\)。

在第二个样例测试中：
 - 函数\(f(x)=f^{(1)}(x)\)不是幂等的，因为\(f(f(1)) = 3\)但\(f(1)=2\)；
 - 函数\(f(x)=f^{(2)}(x)\)是幂等的，因为对于任何\(x\)，\(f^{(2)}(x)=3\)都成立，所以\(f^{(2)}(f^{(2)}(x)) = 3\)也成立。

在第三个样例测试中：
 - 函数\(f(x)=f^{(1)}(x)\)不是幂等的，因为\(f(f(1)) = 3\)但\(f(1)=2\)；
 - 函数\(f(f(x))=f^{(2)}(x)\)不是幂等的，因为\(f^{(2)}(f^{(2)}(1)) = 2\)但\(f^{(2)}(1)=3\)；
 - 函数\(f(f(f(x)))=f^{(3)}(x)\)是幂等的，因为它是恒等函数：对于任何\(x\in\{1,2,3\}\)，\(f^{(3)}(x)=x\)，这意味着公式\(f^{(3)}(f^{(3)}(x)) = f^{(3)}(x)\)也成立。

## 样例 #1
### 输入
```
4
1 2 2 4
```
### 输出
```
1
```

## 样例 #2
### 输入
```
3
2 3 3
```
### 输出
```
2
```

## 样例 #3
### 输入
```
3
2 3 1
```
### 输出
```
3
```

### 算法分类
数学

### 题解综合分析与结论
三道题解思路本质相似，均通过分析函数性质，利用图论中内向基环树森林的特点求解。关键在于计算环长及点到环的距离，通过最小公倍数等数学方法得出答案。不同点在于具体实现方式和对特殊情况的处理细节。

### 所选的题解
 - **素质玩家孙1超（4星）**
    - **关键亮点**：通过暴力模拟理解题意，手玩数据发现每个位置循环独立且最终序列循环的规律，进而通过求每个位置循环节开始位置和长度的最小公倍数得到答案，并对特殊情况进行了合理处理。
    - **重点代码及核心思想**：
```cpp
n=R();
for(int i=1;i<=n;i++) a[i]=R();
for(int i=1;i<=n;i++)
{
    memset(vis,0,sizeof vis);
    x=a[i];    
    num=1;
    vis[x]=num;
    x=a[x];
    while(!vis[x])
    {
        vis[x]=++num;
        x=a[x];
    }
    m=max(m,vis[x]);//m表示最大的初始循环位置
    num=num-vis[x]+1;
    ans=lcm(ans,(long long )num);//ans表示整个循环节的长度
}
int add=ans;
while(ans<m) ans+=add;//特判
printf("%lld",ans);
```
核心思想是对每个位置，通过标记数组`vis`记录访问顺序，找到其循环节开始位置和长度，更新最大初始循环位置`m`和整个循环节长度`ans`，最后对`ans`小于`m`的情况进行特判。
 - **Shunpower（4星）**
    - **关键亮点**：将问题转化为图论问题，通过连边\(x\to f(x)\)，利用内向基环树森林的性质，先求出所有环长的最小公倍数，再针对未到达环上的点进行处理，保证答案的最优性。
    - **重点代码及核心思想**：
```cpp
void dfs(int x){
    if(dis[lnk[x]]){
        gate=lnk[x];
        len=dis[x]-dis[lnk[x]]+1;
        return;
    }
    else{
        dis[lnk[x]]=dis[x]+1;
        dfs(lnk[x]);
    }
}
//...
fr1(i,1,n){
    dfs(i);
    lcm=1ll*lcm*len/__gcd(lcm,(ll)len);
    condi[i]=mp(len,(dis[gate]+len-1)/len);
    fr1(j,1,n){
        dis[j]=0;
    }
    len=0;
}
fr1(i,1,n){
    rlcm[i]=1;
    fr1(j,1,n){
        if(i==j){
            continue;
        }
        rlcm[i]=1ll*rlcm[i]*condi[j].fi/__gcd(rlcm[i],(ll)condi[j].fi);
    }
}
fr1(i,1,n){
    while(lcm/condi[i].fi<condi[i].se){
        lcm+=rlcm[i];
    }
}
```
核心思想是通过`dfs`函数计算每个连通块中环的长度`len`和每个点到环的距离，求出所有环长的最小公倍数`lcm`，并对每个点记录环长和到环的距离相关信息`condi`，通过计算部分环长的最小公倍数`rlcm`来对`lcm`进行调整，满足所有点的要求。
 - **DE_aemmprty（4星）**
    - **关键亮点**：通过建图将问题转化为基环树问题，分点在环上和不在环上两种情况讨论，利用最小公倍数和带余除法求解答案，思路清晰。
    - **重点代码及核心思想**：
```cpp
int dfs(int x) {
    if (vis[x])
        return dis[x];
    vis[x] = 1;
    dfn[x] = ++ timetmp;
    int num = dfs(a[x]);
    if (vis[a[x]] == 1)
        p = a[x], num = dfn[x] - dfn[p] + 1;
    else if (cycle[a[x]] == 1) dis[x] = 1;
    else dis[x] = num + 1;
    if (p > 0 && vis[p] == 1)
        cycle[x] = 1, dis[x] = num;
    vis[x] = 2;
    return dis[x];
}
//...
int k = 1;
f (i, 1, n)
    if (!vis[i]) {
        p = -1;
        dfs(i);
    }
f (i, 1, n)
    if (cycle[i])
        k = k * dis[i] / __gcd(k, dis[i]);
int x = 0;
f (i, 1, n)
    if (!cycle[i]) 
        x = max(x, dis[i]);
if (x > k)
    k = ((x - 1) / k + 1) * k;
```
核心思想是通过`dfs`函数标记访问节点，计算每个点到环的距离`dis`和环的长度，对在环上的点计算环长的最小公倍数`k`，对不在环上的点找到到环的最大距离`x`，通过带余除法调整`k`得到答案。

### 最优关键思路或技巧
将函数关系转化为图的边关系，利用内向基环树森林的结构特点，通过计算环长和点到环的距离，运用最小公倍数等数学方法求解。这种将函数问题转化为图论问题，并结合数学运算的思维方式是解题关键。

### 同类型题或类似算法套路拓展
此类题目通常将函数迭代问题转化为图论中的路径问题，利用图的结构性质（如环、连通块等）和数学运算（如最小公倍数、最大公约数等）求解。类似题目可能会改变函数性质或图的结构，需要灵活运用图论和数学知识。

### 洛谷相似题目推荐
 - [P1345 凝聚](https://www.luogu.com.cn/problem/P1345)：同样涉及图的连通性和环相关知识，通过分析图的结构求解。
 - [P2762 太空飞行计划问题](https://www.luogu.com.cn/problem/P2762)：需要构建图模型，结合图的性质和一些数学思想来解决问题。
 - [P1993 小K的农场](https://www.luogu.com.cn/problem/P1993)：通过构建图并利用图的性质和数学关系求解不等式相关问题，与本题利用图和数学知识解题思路类似。

### 个人心得摘录与总结
素质玩家孙1超通过暴力模拟和手玩数据理解题意并发现规律，这是一种在面对复杂问题时常用的探索方法，有助于从具体实例中挖掘通用规律，为后续解题提供思路。 

---
处理用时：76.33秒