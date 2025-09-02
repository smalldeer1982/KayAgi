# 题目信息

# The Child and Zoo

## 题目描述

Of course our child likes walking in a zoo. The zoo has $ n $ areas, that are numbered from $ 1 $ to $ n $ . The $ i $ -th area contains $ a_{i} $ animals in it. Also there are $ m $ roads in the zoo, and each road connects two distinct areas. Naturally the zoo is connected, so you can reach any area of the zoo from any other area using the roads.

Our child is very smart. Imagine the child want to go from area $ p $ to area $ q $ . Firstly he considers all the simple routes from $ p $ to $ q $ . For each route the child writes down the number, that is equal to the minimum number of animals among the route areas. Let's denote the largest of the written numbers as $ f(p,q) $ . Finally, the child chooses one of the routes for which he writes down the value $ f(p,q) $ .

After the child has visited the zoo, he thinks about the question: what is the average value of $ f(p,q) $ for all pairs $ p,q $ $ (p≠q) $ ? Can you answer his question?

## 说明/提示

Consider the first sample. There are $ 12 $ possible situations:

- $ p=1,q=3,f(p,q)=10 $ .
- $ p=2,q=3,f(p,q)=20 $ .
- $ p=4,q=3,f(p,q)=30 $ .
- $ p=1,q=2,f(p,q)=10 $ .
- $ p=2,q=4,f(p,q)=20 $ .
- $ p=4,q=1,f(p,q)=10 $ .

Another $ 6 $ cases are symmetrical to the above. The average is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF437D/58ce2a366aa42eff918fbf0b8467c9ccbcf9601e.png).

Consider the second sample. There are $ 6 $ possible situations:

- $ p=1,q=2,f(p,q)=10 $ .
- $ p=2,q=3,f(p,q)=20 $ .
- $ p=1,q=3,f(p,q)=10 $ .

Another $ 3 $ cases are symmetrical to the above. The average is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF437D/ecc6155982485fab22801f99d7326020bda06f7b.png).

## 样例 #1

### 输入

```
4 3
10 20 30 40
1 3
2 3
4 3
```

### 输出

```
16.666667
```

## 样例 #2

### 输入

```
3 3
10 20 30
1 2
2 3
3 1
```

### 输出

```
13.333333
```

## 样例 #3

### 输入

```
7 8
40 20 10 30 20 50 40
1 2
2 3
3 4
4 5
5 6
6 7
1 4
5 7
```

### 输出

```
18.571429
```

# AI分析结果

### 题目内容
# 孩子与动物园

## 题目描述
当然，我们的孩子喜欢在动物园里散步。动物园有$n$个区域，编号从$1$到$n$。第$i$个区域里有$a_{i}$只动物。此外，动物园里有$m$条路，每条路连接两个不同的区域。自然地，动物园是连通的，所以你可以通过这些路从动物园的任何一个区域到达其他任何区域。

我们的孩子非常聪明。假设孩子想从区域$p$走到区域$q$。首先，他会考虑从$p$到$q$的所有简单路径。对于每条路径，孩子会写下一个数字，这个数字等于路径所经过区域中动物数量的最小值。我们将写下的这些数字中的最大值记为$f(p,q)$。最后，孩子会选择其中一条路径，使得他写下的值为$f(p,q)$。

在孩子参观完动物园后，他思考了一个问题：对于所有的点对$p,q$（$p≠q$），$f(p,q)$的平均值是多少？你能回答他的问题吗？

## 说明/提示
考虑第一个样例。有$12$种可能的情况：
 - $p = 1,q = 3,f(p,q)=10$。
 - $p = 2,q = 3,f(p,q)=20$。
 - $p = 4,q = 3,f(p,q)=30$。
 - $p = 1,q = 2,f(p,q)=10$。
 - $p = 2,q = 4,f(p,q)=20$。
 - $p = 4,q = 1,f(p,q)=10$。
另外$6$种情况与上述情况对称。平均值为![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF437D/58ce2a366aa42eff918fbf0b8467c9ccbcf9601e.png)。

考虑第二个样例。有$6$种可能的情况：
 - $p = 1,q = 2,f(p,q)=10$。
 - $p = 2,q = 3,f(p,q)=20$。
 - $p = 1,q = 3,f(p,q)=10$。
另外$3$种情况与上述情况对称。平均值为![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF437D/ecc6155982485fab22801f99d7326020bda06f7b.png)。

## 样例 #1
### 输入
```
4 3
10 20 30 40
1 3
2 3
4 3
```
### 输出
```
16.666667
```

## 样例 #2
### 输入
```
3 3
10 20 30
1 2
2 3
3 1
```
### 输出
```
13.333333
```

## 样例 #3
### 输入
```
7 8
40 20 10 30 20 50 40
1 2
2 3
3 4
4 5
5 6
6 7
1 4
5 7
```
### 输出
```
18.571429
```

### 算法分类
图论（主要利用最大生成树和并查集解决问题）

### 综合分析与结论
所有题解主要围绕将点权转化为边权，利用最大生成树和并查集统计边对答案的贡献从而求解。各题解思路相近，主要差异在代码实现细节与思路阐述清晰度上。

### 所选的题解
- **hs_black（5星）**
  - **关键亮点**：思路清晰，先点明最大生成树性质，后详细阐述边对答案贡献的原理，代码注释详细，可读性高。
  - **个人心得**：模拟赛中做出该题，考场上因问题涉及路径最小值最大，联想到货车运输问题。
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<iomanip>
#include<algorithm>
using namespace std;
template <typename T> 
void read(T &x) {
    x = 0; int f = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (isdigit(c)) {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar();
    }
    x *= f;
}
const int N = 100500;
const int M = 1005000;

struct node{
    int x, y;
    int w;
    bool operator < (const node &i) const {
        return w > i.w;
    }
}e[M];

long long n, m;


int f[N], a[N];
long long ans = 0;
int siz[N];
int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}


int main() {
    read(n), read(m);
    for (int i = 1;i <= n; i++) f[i] = i, siz[i] = 1;
    for (int i = 1;i <= n; i++) read(a[i]);
    for (int i = 1;i <= m; i++) {
        int x, y;
        read(x), read(y);
        e[i] = (node){x, y, min(a[x], a[y])};
    }
    sort(e + 1,e + m + 1);
    for (int i = 1;i <= m; i++) {
        int fx = find(e[i].x), fy = find(e[i].y);
        if (fx == fy) continue;
        f[fx] = fy;
        ans += (long long)siz[fx] * siz[fy] * e[i].w;
        siz[fy] += siz[fx];
    }
    cout << setprecision(6) << (long double) ans * 2  / (long double)(n * (n-1)) << endl;
    return 0;
}
```
核心代码实现思想：先读入数据，将边权按两端点点权较小值赋值并排序。利用并查集维护连通块，遍历排序后的边，若两端点不在同一连通块，合并连通块并统计该边对答案贡献，最后计算平均值输出。

- **Star_Cried（4星）**
  - **关键亮点**：代码简洁，在思路阐述中清晰地说明了每一步转化的正确性。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<cmath>
using namespace std;
inline int read(){
    int w=0,x=0;char c=getchar();
    while(!isdigit(c))w|=c=='-',c=getchar();
    while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return w?-x:x;
}
namespace star
{
    const int maxn=1e5+10;
    int n,m,siz[maxn],fa[maxn],a[maxn];
    double ans;
    struct edge{
        int u,v,d;
        inline bool operator < (const edge &zp) const{return d>zp.d;}
    }e[maxn];
    inline void onion(int x,int y,int k){
        if(siz[x]<siz[y])swap(x,y);
        ans+=1.0*siz[x]*siz[y]*k;
        fa[y]=x,siz[x]+=siz[y];
    }
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void work(){
        n=read(),m=read();
        for(int i=1;i<=n;i++) a[i]=read(),fa[i]=i,siz[i]=1;
        for(int u,v,i=1;i<=m;i++) u=read(),v=read(),e[i]=(edge){u,v,min(a[u],a[v])};
        sort(e+1,e+1+m);
        for(int cnt=0,i=1;i<=m and cnt<=n-1;i++){
            int u=find(e[i].u),v=find(e[i].v);
            if(u!=v)
                onion(u,v,e[i].d),cnt++;
        }
        printf("%.5lf\n",ans/n/(n-1)*2);
    }
}
signed main(){
    star::work();
    return 0;
}
```
核心代码实现思想：读入数据后，将边权赋值并排序。通过并查集和自定义函数onion合并连通块，统计边贡献，最后计算输出平均值。

### 最优关键思路或技巧
1. **点权转边权**：将点权转化为边权，边权为两端点点权的较小值，简化问题。
2. **最大生成树**：利用最大生成树性质，确定所有点对间路径最小值最大的路径必在最大生成树上。
3. **并查集统计贡献**：使用并查集维护连通块，通过边两端连通块大小乘积乘边权统计边对答案的贡献。

### 同类型题或类似算法套路
同类型题通常围绕图中点权或边权，求路径上最值相关的统计量。类似算法套路为将点权转化为边权，利用生成树（最大或最小）和并查集统计贡献。

### 洛谷推荐题目
1. **P3366 【模板】最小生成树**：基础的最小生成树模板题，可巩固生成树概念与并查集应用。
2. **P1195 口袋的天空**：结合连通性与最小生成树求解问题，锻炼综合应用能力。
3. **P1546 最短网络 Agri-Net**：同样是最小生成树问题，不同场景下的应用，加深对算法理解。 

---
处理用时：77.88秒