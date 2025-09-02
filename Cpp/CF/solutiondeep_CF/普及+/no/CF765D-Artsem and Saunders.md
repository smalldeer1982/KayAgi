# 题目信息

# Artsem and Saunders

## 题目描述

令 $ [n] $ 表示整数集 $ \{1,...,n\} $ ，令 $f:[x]\rightarrow[y]$ 表示函数 $f$ 的定义域为整数 $\{1,...,x\}$ 并且它的所有函数值在 $\{1,...,y\}$ 中。



现在，给定一个函数 $f:[x]\to[y]$ ，你的任务是找出一个正整数 $m$ ，和两个函数 $g:[n]\to[m]$、$h:[m]\to[n]$ ，满足对于任意 $x\in[m]$ ，有 $g(h(x))=x$ ；对于任意 $x\in[n]$ ，有 $h(g(x))=f(x)$ 。或者判定无解。

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
3
1 2 3
1 2 3
```

## 样例 #2

### 输入

```
3
2 2 2
```

### 输出

```
1
1 1 1
2
```

## 样例 #3

### 输入

```
2
2 1
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
#### Artsem and Saunders
1. **题目描述**：令$[n]$表示整数集$\{1,...,n\}$ ，令$f:[x]\rightarrow[y]$表示函数$f$的定义域为整数$\{1,...,x\}$并且它的所有函数值在$\{1,...,y\}$中。

现在，给定一个函数$f:[x]\to[y]$ ，你的任务是找出一个正整数$m$ ，和两个函数$g:[n]\to[m]$、$h:[m]\to[n]$ ，满足对于任意$x\in[m]$ ，有$g(h(x))=x$ ；对于任意$x\in[n]$ ，有$h(g(x))=f(x)$ 。或者判定无解。
2. **样例 #1**
    - **输入**：
```
3
1 2 3
```
    - **输出**：
```
3
1 2 3
1 2 3
```
3. **样例 #2**
    - **输入**：
```
3
2 2 2
```
    - **输出**：
```
1
1 1 1
2
```
4. **样例 #3**
    - **输入**：
```
2
2 1
```
    - **输出**：
```
-1
```

### 算法分类
构造

### 题解综合分析与结论
两道题解思路相近，均将函数关系转化为图的边关系来处理。核心难点在于根据题目中两个函数的限制条件，判断是否有解以及如何构造出满足条件的函数。二者都通过动态维护左右部点的连边关系来解决问题，时间复杂度均为$O(n)$。

### 所选的题解
- **作者：TUIFEI_oier (5星)**
    - **关键亮点**：思路清晰，详细分析了题目条件转化为图论问题后的情况，对无解情况的判断和有解时的构造过程阐述清晰，代码实现简洁明了，注释详细。
    - **重点代码核心思想**：通过读入$f(x)$，根据$g(x)$和$h(x)$的连边情况分三种情况处理，同时维护$g$数组（左部点到右部点的连边）和$h$数组（右部点到左部点的连边），若出现不满足条件的情况则判定无解，最后输出构造结果。
    - **核心代码片段**：
```c++
#include <bits/stdc++.h>
using namespace std;
// 快读部分
#define ch getchar
template<typename T> void read(T &x){
    x = 0; int f(1); char c = ch();
    for(;!isdigit(c);c = ch()) if(c == '-') f = -1;
    for(;isdigit(c);c = ch()) x = x*10+c-'0';
    x *= f;
}
template<typename T,typename... Args>
inline void read(T &x,Args&... args){
    read(x); read(args...);
}

const int maxn = 100005;
int n,g[maxn],h[maxn],tot;
// g[x] 为左部点 x 向右部点的连边。
// h[y] 为右部点 y 向左部点的连边。
// tot 为右部点数。
int main(){
    read(n);
    for(int i(1);i <= n;++i){
        int x; read(x);
        if(!g[x])    g[x] = ++tot,h[tot] = x,g[i] = tot;
        else if(h[g[x]] == x)    g[i] = g[x];
        else    return puts("-1"),0;
    }
    printf("%d\n",tot);
    for(int i(1);i <= n;++i)    printf("%d ",g[i]);
    puts("");
    for(int i(1);i <= tot;++i)    printf("%d ",h[i]);
    puts("");
    return 0;
}
```
- **作者：Coros_Trusds (4星)**
    - **关键亮点**：简洁地阐述了将函数关系转化为建图问题，代码实现较为简洁。但对思路的分析和代码注释不如TUIFEI_oier的题解详细。
    - **重点代码核心思想**：与上一题解类似，通过读入$f(x)$，根据$left\_mat$（左部点到右部点的连边）和$right\_mat$（右部点到左部点的连边）数组的情况分情况处理，判断无解并构造结果。
    - **核心代码片段**：
```cpp
//2022/1/14

const int ma=1e5+5;

int left_mat[ma],right_mat[ma];
//left_mat[i]:左部点 i 的对应点
//right_mat[i]:右部点 i 的对应点 

int n,m;

int main(void)
{
    n=read();
    
    for(register int i=1;i<=n;i++)
    {
        int x=read();
        
        if(left_mat[x]==0)
        {
            left_mat[x]=++m;
            
            right_mat[m]=x;
            
            left_mat[i]=m;
        }
        
        else if(right_mat[left_mat[x]]==x)
        {
            left_mat[i]=left_mat[x];
        }
        
        else
        {
            puts("-1");
            
            return 0;
        }
    }
    
    printf("%d\n",m);
    
    blow(left_mat,1,n," ");
    
    putchar('\n');
    
    blow(right_mat,1,m," ");
    
    return 0;
} 
```

### 最优关键思路或技巧
将函数关系转化为图的边关系，利用图论思想解决问题。通过动态维护左右部点的连接关系，根据条件判断无解情况并构造出满足条件的函数。

### 可拓展思路
此类题目属于函数构造与图论结合的问题，类似套路可应用于其他涉及函数映射关系且可转化为图结构的题目。例如一些需要根据特定条件构建有向图，并在图上进行操作和判断的问题。

### 洛谷相似题目推荐
- [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)
- [P1525 关押罪犯](https://www.luogu.com.cn/problem/P1525)
- [P2032 扫描游戏](https://www.luogu.com.cn/problem/P2032)

### 个人心得摘录与总结
无。 

---
处理用时：47.43秒