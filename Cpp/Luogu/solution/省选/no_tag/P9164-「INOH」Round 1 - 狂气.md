# 「INOH」Round 1 - 狂气

## 题目描述

有一个无限长的序列 $\{a\}$，**数组下标从 $1$ 开始**，初始 $a_1=1$，其余位置均为 $0$。

$m$ 次操作：
1. 对于所有**奇数** $i$，令 $a_{i+1}\gets a_{i+1}+a_i$。
2. 对于所有**偶数** $i$，令 $a_{i+1}\gets a_{i+1}+a_i$。

你需要求出所有操作进行完之后的序列。

为了方便输出，你只需要输出 $( \displaystyle\prod_{i = 1}^{m} (a_i + 1))\bmod 998244353$ 的值即可。  

## 说明/提示

**样例 1 解释**  

经过 5 次操作之后，序列前五项：  
$a_1 = 1$，$a_2 = 3$，$a_3 = 4$，$a_4 = 4$，$a_5 = 0$。

**本题采用捆绑测试**。 

- Subtask 0（10pts）：$1 \le m \le 1000$。  
- Subtask 1（20pts）：操作序列形如 $\tt121212\dots$。
- Subtask 2（20pts）：操作序列随机生成。  
- Subtask 3（50pts）：无特殊限制。  

对于 $100\%$ 的数据，有 $1 \le m \le 2 \times 10^5$。  

**请选手注意常数因子对运行效率的影响**

## 样例 #1

### 输入

```
5
11221```

### 输出

```
200```

## 样例 #2

### 输入

```
13
1122121212212```

### 输出

```
400201782```

# 题解

## 作者：Petit_Souris (赞：2)

看起来就不是什么正常思路的 DS 题，结合模数 $998244353$，考虑生成函数。

设奇数位的生成函数为 $F(x)=a_1+a_3x+a_5x^2+\dots $，偶数位的生成函数为 $G(x)=a_2+a_4x+a_6x^2+\dots $。

那么操作 $1$ 等价于 $G\leftarrow F+G$，操作 $2$ 等价于 $F\leftarrow F+Gx$。

考虑做一个类似半在线卷积的分治 NTT：对于一个分治区间 $[l,r]$，我们可以求出，以 $(F,G)$ 作为起始值的时候，经过这个区间之后，新的二元组 $(F,G)$ 可以被表示成 $(AF+BG,CF+DG)$ 的形式，其中 $A,B,C,D$ 均为不超过 $r-l+1$ 次的多项式。

取中点 $mid$，递归计算 $[l,mid]$ 和 $[mid+1,r]$，设得到的结果为 $(AF+BG,CF+DG)$ 和 $(PF+QG,RF+SG)$，那么可以合并得到 $((PA+QC)F+(PB+QD)G,(RA+SC)F+(RB+SD)G)$。时间复杂度为 $\mathcal O(n\log^2 n)$。

除去模板的关键代码：

```cpp
using namespace Poly;
ll n;
char s[N];
array<poly,4> solve(ll l,ll r){
    if(l==r){
        array<poly,4> ret;
        if(s[l]=='1'){
            ret[0].resize(1),ret[1].resize(1),ret[2].resize(1),ret[3].resize(1);
            ret[0][0]=1,ret[2][0]=1,ret[3][0]=1;
        }
        else {
            ret[0].resize(1),ret[1].resize(2),ret[2].resize(1),ret[3].resize(1);
            ret[0][0]=1,ret[1][1]=1,ret[3][0]=1;
        }
        return ret;
    }
    ll mid=(l+r)>>1;
    array<poly,4>L=solve(l,mid),R=solve(mid+1,r),ret;
    ret[0]=R[0]*L[0]+R[1]*L[2];
    ret[1]=R[0]*L[1]+R[1]*L[3];
    ret[2]=R[2]*L[0]+R[3]*L[2];
    ret[3]=R[2]*L[1]+R[3]*L[3];
    return ret;
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read();
    scanf("%s",s+1);
    array<poly,4> ret=solve(1,n);
    ll ans=1,pos=1;
    for(ll x:ret[0].a){
        if(pos>n)break;
        ans=1ll*ans*(x+1)%Mod,pos+=2;
    }
    pos=2;
    for(ll x:ret[2].a){
        if(pos>n)break;
        ans=1ll*ans*(x+1)%Mod,pos+=2;
    }
    write(ans);
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：critnos (赞：1)

水题解/se

考虑偶数位置和奇数位置分别的生成函数，分别记做 $f(x),g(x)$，那么操作 $1$ 是 $f\gets g+f$，操作 $2$ 是 $g\gets g+fx$，这俩都是线性变换，所以直接分治 NTT 维护区间中会把 $(f,g)$ 变成 $(af+bg,cf+dg)$。时间复杂度 $O(n\log^2n)$。

---

