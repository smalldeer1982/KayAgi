# [PA 2022] Drzewa rozpinające

## 题目描述

**题目译自 [PA 2022](https://sio2.mimuw.edu.pl/c/pa-2022-1/dashboard/) Runda 5 [Drzewa rozpinające](https://sio2.mimuw.edu.pl/c/pa-2022-1/p/drz/)**

给定一个长为 $n$ 的整数序列 $a_1,a_2,\ldots,a_n$。根据这个序列你可以生成一个 $n$ 个节点的无向图：节点 $i$ 和 $j$ 之间（对于 $i\neq j$）有 $\gcd(a_i,a_j)$ 条可区分的边将这两个节点相连。你的任务是计算这个图的生成树数量。如果对于两棵树，其中一棵树包含另一棵树中不存在的边，那么就认为这两棵树不同。因为生成树数量很大，请输出它对 $10^9+7$ 取模后的值。

## 说明/提示

对于 $100\%$ 的数据，满足：

$1\le n\le 5000, 1\le a_i\le 5000$。

## 样例 #1

### 输入

```
4
1 2 3 4
```

### 输出

```
24
```

# 题解

## 作者：Rainbow_qwq (赞：6)

PA 2022 Drzewa rozpinające

根据 Matrix-tree 定理，我们要计算 $(n-1)\times (n-1)$ 的矩阵的 $\det$. 设 $G_{i,j} = \gcd(a_i,a_j),D_{i,i}=\sum_j G_{i,j}$，要计算 $\det(D-G)$.

由于 $\gcd(a_i,a_j)=\sum_{d|a_i,d|a_j}\varphi(d)$，设两个 $(n-1)\times m$ 的矩阵 $U,V$，$U_{i,d}=\varphi(d)[d|a_i],V_{i,d}=[d|a_i]$，则有 $G=UV^T$. （$V^T$ 是转置矩阵）

下面考虑使用 [Matrix determinant lemma](https://en.wikipedia.org/wiki/Matrix_determinant_lemma) 化简式子。

$\det(D-G) = \det(D-UV^T) = \det(I_m-V^TD^{-1}U)\det(D)$.

$D$ 是对角矩阵，$\det$ 好算。于是问题转化为计算 $\det(I_m-V^TD^{-1}U)$.

设 $Q=I_m-V^TD^{-1}U$，只有 $\operatorname{lcm}(i,j)\le m$ 的地方可能有值，对这个稀疏矩阵高斯消元，跑的比较快。

---

## 作者：yyyyxh (赞：4)

设 $\mathbf U$ 是 $n\times m$ 阶矩阵，$\mathbf V$ 是 $m\times n$ 阶矩阵，$\mathbf I_x$ 是 $x$ 阶单位矩阵。

那么矩阵行列式引理的一个核心等式是： $|\mathbf I_n+\mathbf U\mathbf V|=|\mathbf I_m+\mathbf V\mathbf U|$。

证明考虑分块矩阵乘法，有等式：

$$
\begin{aligned}
&\begin{pmatrix}
\mathbf I_n & \\
\mathbf V & \mathbf I_m
\end{pmatrix}
\begin{pmatrix}
\mathbf I_n+\mathbf U\mathbf V & \mathbf U \\
 & \mathbf I_m
\end{pmatrix}
\begin{pmatrix}
\mathbf I_n & \\
-\mathbf V & \mathbf I_m
\end{pmatrix}\\
=&
\begin{pmatrix}
\mathbf I_n+\mathbf U\mathbf V & \mathbf U \\
\mathbf V(\mathbf I_n+\mathbf U\mathbf V) & \mathbf I_m+ \mathbf U\mathbf V
\end{pmatrix}
\begin{pmatrix}
\mathbf I_n & \\
-\mathbf V & \mathbf I_m
\end{pmatrix}\\
=&
\begin{pmatrix}
\mathbf I_n & \mathbf U \\
 & \mathbf I_m+\mathbf V\mathbf U
\end{pmatrix}
\end{aligned}
$$

这些矩阵都是分块三角矩阵，所以左边第一、三个矩阵行列式都是 $1$，两边取行列式就得到了 $|\mathbf I_n+\mathbf U\mathbf V|=|\mathbf I_m+\mathbf V\mathbf U|$。

考虑拓展这个等式，对于可逆 $n$ 阶方阵 $\mathbf A$ 来说：

$$
|\mathbf A+\mathbf U\mathbf V|=|\mathbf A||\mathbf I_n+(\mathbf A^{-1}\mathbf U) \mathbf V|=|\mathbf A||\mathbf I_m + \mathbf V (\mathbf A^{-1}\mathbf U)|=|\mathbf A||\mathbf I_m + \mathbf V \mathbf A^{-1}\mathbf U|
$$

进一步地，对于可逆 $m$ 阶方阵 $\mathbf B$ 来说：

$$
|\mathbf A+\mathbf U\mathbf B\mathbf V|=|\mathbf A+\mathbf U(\mathbf B\mathbf V)|=|\mathbf A||\mathbf I_m + (\mathbf B\mathbf V) \mathbf A^{-1}\mathbf U|=|\mathbf A||\mathbf B||\mathbf B^{-1} + \mathbf V \mathbf A^{-1}\mathbf U|
$$

> 例题：[PA 2022] Drzewa rozpinające
>
> 一张无向图，点 $i$ 和点 $j$ 之间连着 $\gcd(a_i,a_j)$ 条边，求生成树个树。设 $m=\max a_i$，则 $n,m\le 5000$。

首先这个题我以为是 [gcd-matrix](https://arxiv.org/pdf/1012.5445) 那套理论，但是这个矩阵比起 gcd-matrix 来说中间修改了主对角线，所以说这个题得借助别的理论，也就是 Matrix Determinant Lemma。

本题相当于是对于 $n-1$ 阶的对角矩阵 $\mathbf D$ 和 gcd 矩阵 $\mathbf G_{i,j}=\gcd(a_i,a_j)$，求 $|\mathbf D-\mathbf G|$。

对于 gcd 矩阵 $\mathbf G$，考虑到 $\gcd(a_i,a_j)=\sum_{d|a_i,d|a_j} \varphi(d)$，我们依旧是类似处理 gcd-matrix 的手法做矩阵分解，分解之后得到 $\mathbf U_{i,j}=[j|a_i]\varphi(j),\mathbf V_{i,j}=[i|a_j],\mathbf G=\mathbf U \mathbf V$。其中 $\mathbf U$ 为 $(n-1)\times m$ 阶，$\mathbf V$ 为 $m\times (n-1)$ 阶。

分解之后运用矩阵行列式引理，有 $|\mathbf D-\mathbf G|=|\mathbf D-\mathbf U\mathbf V|=|\mathbf D||\mathbf I_m-\mathbf V\mathbf D^{-1}\mathbf U|$。

看起来还是要求行列式？注意到 $|\mathbf I_m-\mathbf V\mathbf D^{-1}\mathbf U|$ 第 $i$ 行 $j$ 列的值是 $\varphi(j)\sum_{i|a_k,j|a_k} \mathbf D_{k,k}^{-1}$，其只在 $\operatorname{lcm}(i,j)\le m$ 的时候有值。这是稀疏矩阵，从 $m$ 行到第 $1$ 行依次消元，消元时只遍历有值的位置，复杂度就是玄学了！（你只需要实验一下 $m=5000$ 时的运行速度就行了）

MDL 这个东西我觉得可以这样理解，众所周知矩阵数值算法中 LU 分解的作用可以与高斯消元互相替代，LU 分解问题、行列式问题、高斯消元问题、逆矩阵问题等等问题相互规约。当你把一个矩阵分解成 $\mathbf M=\mathbf L\mathbf U$ 时，此时求行列式是简单的：$|\mathbf M|=|\mathbf L||\mathbf U|=|\mathbf U||\mathbf L|$，这个想法的应用就是 gcd-matrix，也就是说 $\mathbf G$ 的行列式很容易用莫反分解成两个三角矩阵。

但是有的时候，LU 分解并不足够有性质。我们考虑到当矩阵可以写成 $\mathbf A+\mathbf U\mathbf V$ 这种形式，其中 $\mathbf A$ 是一个好求逆的矩阵（常常是对角矩阵，这也就是为什么矩阵行列式引理常跟矩阵树定理配合使用），此时使用 MDL 可以把原行列式转变为另一个等难行列式（可以类比理解，这两个行列式互为一种“对偶问题”？），但是另一个行列式的结构更好观察，所以可以设计算法解决问题！

另一道在 Rainbow 博客里看到的例题是 AGC060F，大家可以看一下。

---

## 作者：ZhongYuLin (赞：1)

orz @yyyyxh，orz @zhouhuanyi。

记 $A$ 为 gcd-matrix，其中 $A_{i,j}=\gcd(a_i,a_j)$。尝试使用矩阵树定理，写出 Kirchhoff 矩阵 $G$。分析或者打表发现，**除了主对角线的元素**，其余元素为 $-A_{i,j}$。记对角矩阵 $D$，其中 $G=D-A$。现在根据矩阵树定理去除 $G,D,A$ 的一行一列，方便表述，我们不改变符号。所求即为 $|D-A|$。

套路性地，对 $A$ 进行欧拉反演。记值域为 $V$。构造矩阵 $L,U$，其中 $L_{i,j}=[j|a_i]\varphi(j)$，大小为 $(n-1)\times V$，$U_{i,j}=[i|a_j]$，大小为 $V\times (n-1)$。所求即为 $|D-LU|$。考虑矩阵行列式基本定理，证明参照 @yyyyxh 的[博客](https://www.luogu.com/article/0j0jvzdu)：
对于 $n\times m$ 的矩阵 $A$ 和 $m\times n$ 的矩阵 $B$，有：$|I_n+AB|=|I_m+BA|$。

将 $D$ 提出：

$$|D||I_{n-1}-LUD^{-1}|$$

将 $UD^{-1}$ 视为整体，应用上述定理：

$$|D||I_V-UD^{-1}L|$$

计算得到：

$$(UD^{-1})_{i,j}=[i|a_j]D^{-1}_{j,j}$$

$$(UD^{-1}L)_{i,j}=\sum_{k=1}^{n-1}[i|a_k]D^{-1}_{k,k}[j|a_k]\varphi(j)$$

发现有值的地方集中于矩阵左上角，转置后行列式求值。因为是稀疏矩阵，所以很快。


```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e3+3,P=1e9+7;
template<class T1,class T2>void ckmn(T1 &x,T2 y){if(x>y)x=y;}
template<class T1,class T2>void ckmx(T1 &x,T2 y){if(x<y)x=y;}
template<class T1,class T2>void add(T1 &x,T2 y){if((x+=y)>=P)x-=P;}
template<class T1,class T2>void dlt(T1 &x,T2 y){if((x-=y)<0)x+=P;}
ll fp(ll a,ll b=P-2){ll ans=1;for(;b;b>>=1,a=a*a%P)if(b&1)ans=ans*a%P;return ans;}
template<class T>int det(T a,int n){
    int ans=1,x=1;
    for(int i=1;i<=n;++i){
        int p=i;for(;!a[p][i];)if(++p>n)return 0;
        if(p!=i)swap(a[p],a[i]),x=-x;
        vector<int>tmp;
        for(int j=i;j<=n;++j)
            if(a[i][j])tmp.push_back(j);
        for(int j=i+1;j<=n;++j){
            if(!a[j][i])continue;
            int cf=1ll*a[j][i]*fp(a[i][i])%P;
            for(auto k:tmp)
                a[j][k]=((a[j][k]-1ll*cf*a[i][k])%P+P)%P;
        }
        ans=1ll*ans*a[i][i]%P;
    }
    if(x==-1)ans=P-ans;
    return ans;
}
int a[N],ph[N],p[N],d[N];
bool vis[N];
int n,V,tot;
vector<int>g[N];
int main(){
    int u,v,w,x,y,z;
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i],ckmx(V,a[i]);
    ph[1]=1;
    for(int i=2;i<=V;++i){
    if(!vis[i])p[++tot]=i,ph[i]=i-1;
        for(int j=1;j<=tot&&p[j]*i<=V;++j){
            vis[i*p[j]]=1;
            if(i%p[j]==0){
                ph[i*p[j]]=ph[i]*p[j];
                break;
            }
            ph[i*p[j]]=ph[i]*(p[j]-1);
        }
    }
    ll ans=1;
    for(int i=1;i<n;++i){
        for(int j=1;j<=n;++j)
            add(d[i],__gcd(a[i],a[j]));
        ans=ans*d[i]%P;d[i]=fp(d[i]);
    }
    for(int i=1;i<=V;++i)g[i].resize(V+1),g[i][i]=1;
    for(int i=1;i<=V;++i)
        for(int j=1;j<=V;++j){
            if(i*j/__gcd(i,j)>V)continue;
            for(int k=1;k<n;++k)
                if(a[k]%i==0&&a[k]%j==0)
                    g[V-i+1][V-j+1]=((g[V-i+1][V-j+1]-1ll*ph[j]*d[k])%P+P)%P;
        }
    printf("%lld\n",ans*det(g,V)%P);
    return 0;
}
```

---

