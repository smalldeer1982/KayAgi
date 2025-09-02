# 题目信息

# Rubik's Cube Coloring (easy version)

## 题目描述

It is the easy version of the problem. The difference is that in this version, there are no nodes with already chosen colors.

Theofanis is starving, and he wants to eat his favorite food, sheftalia. However, he should first finish his homework. Can you help him with this problem?

You have a perfect binary tree of $ 2^k - 1 $ nodes — a binary tree where all vertices $ i $ from $ 1 $ to $ 2^{k - 1} - 1 $ have exactly two children: vertices $ 2i $ and $ 2i + 1 $ . Vertices from $ 2^{k - 1} $ to $ 2^k - 1 $ don't have any children. You want to color its vertices with the $ 6 $ Rubik's cube colors (White, Green, Red, Blue, Orange and Yellow).

Let's call a coloring good when all edges connect nodes with colors that are neighboring sides in the Rubik's cube.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1594E1/b0755608caf4588a1ceffdca8e2be827560017bc.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1594E1/c6ef9fa6fcd45f3211d7baf9a8cc69c074f640a9.png)A picture of Rubik's cube and its 2D map.More formally:

- a white node can not be neighboring with white and yellow nodes;
- a yellow node can not be neighboring with white and yellow nodes;
- a green node can not be neighboring with green and blue nodes;
- a blue node can not be neighboring with green and blue nodes;
- a red node can not be neighboring with red and orange nodes;
- an orange node can not be neighboring with red and orange nodes;

You want to calculate the number of the good colorings of the binary tree. Two colorings are considered different if at least one node is colored with a different color.

The answer may be too large, so output the answer modulo $ 10^9+7 $ .

## 说明/提示

In the picture below, you can see one of the correct colorings of the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1594E1/dcebca3c4893383a751dc627ead5632c7d038ce7.png)

## 样例 #1

### 输入

```
3```

### 输出

```
24576```

## 样例 #2

### 输入

```
14```

### 输出

```
934234```

# AI分析结果

### 题目内容
# 魔方着色（简单版）

## 题目描述
这是该问题的简单版本。不同之处在于，在此版本中，不存在已选定颜色的节点。

迪奥凡尼斯饿了，他想吃他最喜欢的食物——烤肠。然而，他首先得完成作业。你能帮他解决这个问题吗？

你有一棵完美二叉树，有 \(2^k - 1\) 个节点——一棵二叉树，其中所有编号从 \(1\) 到 \(2^{k - 1} - 1\) 的顶点都恰好有两个子节点：顶点 \(2i\) 和 \(2i + 1\)。编号从 \(2^{k - 1}\) 到 \(2^k - 1\) 的顶点没有任何子节点。你想用魔方的6种颜色（白色、绿色、红色、蓝色、橙色和黄色）为其顶点着色。

当所有边连接的节点颜色在魔方中是相邻面的颜色时，我们称这种着色是好的。

![魔方图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1594E1/b0755608caf4588a1ceffdca8e2be827560017bc.png)
![魔方2D地图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1594E1/c6ef9fa6fcd45f3211d7baf9a8cc69c074f640a9.png)
更正式地说：
- 白色节点不能与白色和黄色节点相邻；
- 黄色节点不能与白色和黄色节点相邻；
- 绿色节点不能与绿色和蓝色节点相邻；
- 蓝色节点不能与绿色和蓝色节点相邻；
- 红色节点不能与红色和橙色节点相邻；
- 橙色节点不能与红色和橙色节点相邻；

你想计算这棵二叉树的好的着色数量。如果至少有一个节点颜色不同，则两种着色被认为是不同的。

答案可能太大，所以输出答案对 \(10^9 + 7\) 取模的结果。

## 说明/提示
在下面的图片中，你可以看到第一个示例的一种正确着色。

![示例图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1594E1/dcebca3c4893383a751dc627ead5632c7d038ce7.png)

## 样例 #1
### 输入
```
3
```
### 输出
```
24576
```

## 样例 #2
### 输入
```
14
```
### 输出
```
934234
```

### 算法分类
数学

### 综合分析与结论
这些题解主要围绕计算满二叉树满足特定颜色相邻条件的着色方案数展开。解题思路可分为数学推导和动态规划两类。数学推导思路是确定根节点有6种选择，其余节点有4种选择，得出方案数为 \(6×4^{2^{k}-2}\)。动态规划思路则是通过状态转移方程计算每种颜色在不同深度满二叉树的方案数。各题解在实现细节和复杂度上有所不同，如树形dp的状态定义和转移条件，以及对指数取模的处理等。

### 所选的题解
- **作者：XL4453（5星）**
  - **关键亮点**：利用动态规划，通过设 \(f_i\) 为某一种颜色在高度为 \(i\) 的满二叉树上的方案数，根据子树方案数关系得到 \(f_{i + 1}=16×f_i^2\)，思路清晰，代码简洁高效。
  - **重点代码**：
```cpp
#include<cstdio>
using namespace std;
long long n,MOD=1e9+7,f[65];
int main(){
    scanf("%d",&n);
    f[1]=1;
    for(int i=2;i<=n+1;i++){
        f[i]=(f[i-1]*f[i-1])%MOD*16%MOD;
    }
    printf("%lld",f[n]*6%MOD);
    return 0;
}
```
  - **核心实现思想**：初始化 \(f[1]=1\)，通过循环利用递推式 \(f[i]=(f[i - 1]*f[i - 1])×16\) 计算 \(f_i\)，最后乘以6得到总方案数并取模输出。
- **作者：vectorwyx（4星）**
  - **关键亮点**：提供两种方法，一是树形dp，定义 \(f(i,j)\) 表示深度为 \(i\) 的满二叉树且根结点颜色为 \(j\) 时的方案数，通过枚举左右子树颜色转移；二是直接计数得出 \(6×4^{2^{k}-2}\) 的结论，方法多样。
  - **重点代码（方法2）**：
```cpp
#include<bits/stdc++.h>
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
#define sml(x,y) x=min(x,y)
#define big(x,y) x=max(x,y)
#define mk make_pair
#define pb push_back
#define int ll
#define ll long long
#define db double
using namespace std;
inline void out(int *a,int l,int r){fo(i,l,r) printf("%d ",*(a+i));puts("");}
inline int read(){ int x=0,f=1; char ch=getchar(); while(!isdigit(ch)){ if(ch=='-') f=-1; ch=getchar(); } while(isdigit(ch)){ x=(x<<1)+(x<<3)+(ch^48); ch=getchar(); } return x*f; }

const int qlr=1e9+7;
int ksm(int x,int y){
    int ans=1,t=x;
    while(y){
        if(y&1) ans=ans*t%qlr;
        t=t*t%qlr;
        y>>=1;
    }
    return ans;
}

signed main(){
    int k=read(),w=(1ll<<k)-2;
    cout<<6*ksm(4,w)%qlr;
    return 0;
}
```
  - **核心实现思想**：通过快速幂函数 `ksm` 计算 \(4\) 的 \((2^{k}-2)\) 次幂，乘以6并取模输出方案数。
- **作者：Huami360（4星）**
  - **关键亮点**：直接通过分析得出根节点有6种方案，其余节点有4种方案，进而得出方案数公式 \(6×4^{2^{k}-2}\)，思路直接明了，代码简洁。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
typedef long long ll;
const int MOD = 1e9 + 7;
int fast_pow(ll n, ll k){
    int ans = 1;
    while(k){
        if(k & 1) ans = ans * n % MOD;
        n = n * n % MOD;
        k >>= 1;
    }
    return ans;
}
ll ans;
int main(){
    scanf("%d", &n);
    ans = 6ll * fast_pow(4, (1ll<<n)-2) % MOD;
    printf("%d\n", ans);
    return 0;
}
```
  - **核心实现思想**：利用快速幂函数 `fast_pow` 计算 \(4\) 的 \((2^{n}-2)\) 次幂，乘以6并取模得到最终方案数并输出。

### 最优关键思路或技巧
- **数学推导**：通过分析根节点和其他节点的颜色选择可能性，直接得出方案数公式 \(6×4^{2^{k}-2}\)，简洁高效。
- **动态规划**：合理定义状态 \(f_i\) 表示某一种颜色在高度为 \(i\) 的满二叉树上的方案数，利用子树关系构建递推式，有效解决问题。

### 可拓展之处
同类型题可考虑其他形状树的着色问题，或改变颜色相邻限制条件。类似算法套路是先分析特殊节点（如根节点）的选择情况，再推导其他节点的选择与整体方案数的关系，可运用数学推导或动态规划解决。

### 洛谷推荐题目
- [P1226 取余运算](https://www.luogu.com.cn/problem/P1226)：涉及快速幂和取模运算，与本题计算方案数时的取模操作类似。
- [P1962 斐波那契数列](https://www.luogu.com.cn/problem/P1962)：通过递推求解数列，与本题动态规划的递推思路相似。
- [P3390 【模板】矩阵快速幂](https://www.luogu.com.cn/problem/P3390)：同样是快速幂相关，不过应用在矩阵上，可拓展对快速幂应用场景的理解。

### 个人心得摘录与总结
无。 

---
处理用时：56.78秒