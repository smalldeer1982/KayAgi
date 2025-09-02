# 题目信息

# Neural Network country

## 题目描述

Due to the recent popularity of the Deep learning new countries are starting to look like Neural Networks. That is, the countries are being built deep with many layers, each layer possibly having many cities. They also have one entry, and one exit point.

There are exactly $ L $ layers, each having $ N $ cities. Let us look at the two adjacent layers $ L_{1} $ and $ L_{2} $ . Each city from the layer $ L_{1} $ is connected to each city from the layer $ L_{2} $ with the traveling cost $ c_{ij} $ for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852B/945db37d32744d415049d069cc0844aba4f66789.png), and each pair of adjacent layers has the same cost in between their cities as any other pair (they just stacked the same layers, as usual). Also, the traveling costs to each city from the layer $ L_{2} $ are same for all cities in the $ L_{1} $ , that is $ c_{ij} $ is the same for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852B/c68efb3baed3cf7572378486b7c111ddb2e0536c.png), and fixed $ j $ .

Doctor G. needs to speed up his computations for this country so he asks you to find the number of paths he can take from entry to exit point such that his traveling cost is divisible by given number $ M $ .

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852B/a69d8a08d51c12997ef7e1fffeead190caef4b9f.png)

This is a country with $ 3 $ layers, each layer having $ 2 $ cities. Paths ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852B/ec8d7c564cdb67dc57f9922091a73334d330a237.png), and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852B/4299965c61d16bcfc0b10fce7b833b4b1e5fc7b5.png) are the only paths having total cost divisible by $ 13 $ . Notice that input edges for layer cities have the same cost, and that they are same for all layers.

## 样例 #1

### 输入

```
2 3 13
4 6
2 1
3 4
```

### 输出

```
2```

# AI分析结果

### 题目内容
# 神经网络国家

## 题目描述
由于深度学习最近的流行，新的国家开始变得像神经网络。也就是说，这些国家构建得很深，有很多层，每一层可能有许多城市。它们也有一个入口和一个出口点。

这里正好有 $L$ 层，每层有 $N$ 个城市。让我们来看两个相邻的层 $L_{1}$ 和 $L_{2}$ 。从层 $L_{1}$ 的每个城市到层 $L_{2}$ 的每个城市都有一条旅行成本为 $c_{ij}$ 的路径，对于相邻的每两层，它们城市之间的旅行成本都相同（就像通常那样，它们只是堆叠了相同的层）。此外，从层 $L_{1}$ 到层 $L_{2}$ 的每个城市的旅行成本对于层 $L_{1}$ 中的所有城市都是相同的，也就是说，对于固定的 $j$ ，$c_{ij}$ 是相同的。

G 博士需要加快他对这个国家的计算，所以他请你找出他从入口到出口可以采取的路径数量，使得他的旅行成本能被给定的数字 $M$ 整除。

## 说明/提示
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852B/a69d8a08d51c12997ef7e1fffeead190caef4b9f.png)

这是一个有 $3$ 层的国家，每层有 $2$ 个城市。路径 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852B/ec8d7c564cdb67dc57f9922091a73334d330a237.png) 和 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852B/4299965c61d16bcfc0b10fce7b833b4b1e5fc7b5.png) 是仅有的总旅行成本能被 $13$ 整除的路径。注意，层内城市的输入边具有相同的成本，并且所有层都是如此。

## 样例 #1
### 输入
```
2 3 13
4 6
2 1
3 4
```
### 输出
```
2```

### 算法分类
组合数学

### 综合分析与结论
这些题解的核心思路都是利用数据范围中 $M$ 较小的特点，结合层与层之间边权相同的条件，通过不同方式优化计算从入口到出口路径长度能被 $M$ 整除的方案数。主要难点在于如何高效地表示和计算路径方案数的转移。各题解的不同点在于具体采用的优化方式，有的通过自定义类似矩阵乘法的运算结合快速幂，有的直接使用矩阵快速幂，有的从生成函数角度利用多项式快速幂。

### 所选的题解
- **作者：_Life_ (5星)**
    - **关键亮点**：通过观察数据范围和边权特点，联想到矩阵快速幂，但发现矩阵不好表示路径方案数转移，于是自定义了一种类似乘法的运算，该运算具有交换律和结合律，从而利用快速幂优化转移，代码简洁明了，思路清晰。
    - **重点代码**：
```cpp
struct vec
{
    int x[105]={0};
    vec operator *(vec a)
    {
        vec ans;
        for(int i=0;i<m;i++)
            for(int j=0;j<m;j++)
                ans.x[(i+j)%m]+=x[i]*a.x[j],ans.x[(i+j)%m]%=mod;
        return ans;
    }
}a,b,c;
vec qpow(vec base,int k)
{
    vec ans;ans.x[0]=1;
    while(k)
    {
        if(k&1)
            ans=ans*base;
        k>>=1;
        base=base*base;
    }
    return ans;
}
```
核心实现思想：自定义 `vec` 结构体表示状态，重载 `*` 运算符实现类似矩阵乘法的运算，`qpow` 函数实现快速幂，用于高效计算状态转移。
- **作者：hater (4星)**
    - **关键亮点**：运用矩阵乘法快速幂的思想，手动处理最后一层转移，避免了在矩阵乘法中嵌套与当前节点位置有关的复杂转移，使代码逻辑清晰，易于理解。
    - **重点代码**：
```cpp
struct Matrix { 
    int a[N][N] ; 
    void clean( ) { memset( a, 0, sizeof(a) ) ; } 
    friend Matrix operator *  ( Matrix A, Matrix B ) { 
        Matrix C ; C.clean( ) ;  
        fp( i, 0, m-1 ) fp( j, 0, m-1 ) fp( k, 0, m-1 ) 
            C.a[i][j] += ( A.a[i][k] * (i60)B.a[k][j] % hgs ), C.a[i][j] %= hgs ; 
        return C ; 
    } 
    Matrix qpow( Matrix A, int B ) { 
        Matrix C ; C.clean( ) ; 
        fp( i, 0, m-1 ) C.a[i][i] = 1 ; 
        for( ; B ; B >>= 1 ) { 
            if( B & 1 ) C = C * A ;  
            A = A * A  ; 
        } return C ; 
    }  
} S, g ;  
```
核心实现思想：定义 `Matrix` 结构体表示矩阵，实现矩阵的初始化 `clean` 函数、乘法 `*` 运算符重载以及矩阵快速幂 `qpow` 函数，通过矩阵运算优化路径方案数的计算。
- **作者：vvauted (4星)**
    - **关键亮点**：从暴力dp出发，通过观察层与层之间边权和转移的特点，将中间层转移看作生成函数，利用多项式快速幂优化计算，复杂度较低。
    - **重点代码**：
```cpp
struct poly {
    int x[Maxm];

    friend poly operator * (poly x, poly y) {
        poly z = {}; 
        rep(i, 0, m) rep(j, 0, m) z.x[(i + j) % m] = add(z.x[(i + j) % m], mul(x.x[i], y.x[j]));
        return z; 
    }
};

poly qpow(poly x, int y) {
    poly ret = {1};

    for (; y; y >>= 1, x = x * x)
        if (y & 1) ret = ret * x;
    return ret;
}
```
核心实现思想：定义 `poly` 结构体表示多项式，重载 `*` 运算符实现多项式乘法，`qpow` 函数实现多项式快速幂，利用多项式运算优化路径方案数的计算。

### 最优关键思路或技巧
利用数据范围中 $M$ 较小，以及层与层之间边权相同的特点，将路径方案数的转移转化为类似矩阵乘法、矩阵快速幂或多项式快速幂的运算，从而优化计算过程，降低时间复杂度。

### 可拓展之处
同类型题通常具有分层结构且层间转移规律相同，类似算法套路是观察数据范围特点，利用数学运算的性质（如结合律等）将状态转移转化为可快速计算的形式，如矩阵快速幂、多项式快速幂等。

### 推荐洛谷题目
- [P1962 斐波那契数列](https://www.luogu.com.cn/problem/P1962)，通过矩阵快速幂优化斐波那契数列计算，与本题利用快速幂优化状态转移类似。
- [P3390 【模板】矩阵快速幂](https://www.luogu.com.cn/problem/P3390)，直接考察矩阵快速幂的应用，可加深对矩阵快速幂优化计算的理解。
- [P1397 地毯填补问题](https://www.luogu.com.cn/problem/P1397)，涉及分治和递推思想，与本题通过优化递推过程解决问题的思路有相似之处。

### 个人心得
无。 

---
处理用时：67.43秒