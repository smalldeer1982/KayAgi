# Area Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/toyota2023spring-final/tasks/toyota2023spring_final_a

$ N $ 行 $ M $ 列からなる盤面があり，各マス目には row-major 順に $ 1 $ から $ N\ \times\ M $ までの整数が書かれています． つまり，上から $ i $ 行目，左から $ j $ 列目のマスに書かれている整数を $ A_{i,j} $ で表すことにすると， $ A_{i,j}=(i-1)\ \times\ M\ +\ j $ です．

この盤面の部分長方形であって，その内部に書かれた値の総和がちょうど $ V $ になるものの個数を数えてください．

より厳密に言えば，整数の $ 4 $ つ組 $ (a,b,c,d) $ ($ 1\ \leq\ a\ \leq\ b\ \leq\ N $, $ 1\ \leq\ c\ \leq\ d\ \leq\ M $) であって，$ \sum_{a\ \leq\ i\ \leq\ b,\ c\ \leq\ j\ \leq\ d}\ A_{i,j}=V $ を満たすものの個数を数えてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ M\ \leq\ 5000 $
- $ 1\ \leq\ V\ \leq\ 10^{15} $
- 入力される値はすべて整数である

### Sample Explanation 1

盤面には以下のように整数が書き込まれています． ``` 12 34 ``` 条件を満たす部分長方形は，$ (a,b,c,d)=(1,1,1,2),(2,2,1,1) $ の $ 2 $ つです．

## 样例 #1

### 输入

```
2 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
2 2 5```

### 输出

```
0```

## 样例 #3

### 输入

```
13 8 1032```

### 输出

```
5```

# 题解

## 作者：FFTotoro (赞：3)

为了便于解题，先考虑一个子矩阵中数的和如何 $O(1)$ 计算。

令 $S(a,b,c,d)$ 为以 $(a,b)$ 为左上角，$(c,d)$ 为右下角的子矩阵中数的和，那么有：

$$
\begin{aligned}
S(a,b,c,d)&=\sum_{i=a}^c\sum_{j=b}^dM(i-1)+j\\
&=\sum_{i=a}^cM(d-b+1)(i-1)+\frac{d(d+1)-b(b-1)}{2}\\
&=\frac{(c-a+1)[d(d+1)-b(b-1)]+M(d-b+1)[c(c-1)-(a-1)(a-2)]}{2}
\end{aligned}
$$

接着枚举目标的子矩阵的长和宽，如果存在长宽给定且满足和为 $V$ 的子矩阵，可以二分套二分求出它的左上角坐标。具体地，先二分它的行，在行固定的情况下二分它的列。可以证明两层二分都满足单调性。

但是时间复杂度 $O(NM\log NM)$，而 $1\le N,M\le 5000$，会爆掉。于是我们想着能不能加点优化。

有一种便捷好想的优化：在每次二分之前（不管是内层的还是外层的），判断一下可能的子矩阵是否在二分的范围内，如果不在范围内，就进行下一次二分。

这样可以将常数大大减小，最终可以控制在 $1500\,\mathrm{ms}$ 内通过题目。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
main(){
  ios::sync_with_stdio(false);
  int n,m,v,c=0; cin>>n>>m>>v;
  function<int(int,int,int,int)> f=[&](int a,int b,int c,int d){
    return (c-a+1)*(d*(d+1)-b*(b-1)>>1)+m*(d-b+1)*(c*(c-1)-(a-1)*(a-2)>>1);
  }; // 快速计算子矩阵和
  for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++){
      int xl=1,xr=n-i+1;
      if(f(1,i,1,j)<=v&&v<=f(xr,n,m-j+1,m)){ // 优化，内层同理
        bool b=false;
        do{
          int xm=xl+xr>>1,yl=1,yr=m-j+1;
          int l=f(xm,1,xm+i-1,j),r=f(xm,yr,xm+i-1,yr+j-1);
          if(l<=v&&v<=r){
            do{
              int ym=yl+yr>>1;
              int s=f(xm,ym,xm+i-1,ym+j-1);
              if(s==v)b=true; // 找到解
              if(s>v)yr=ym-1;
              else yl=ym+1;
            }while(yl<=yr&&!b);
          }
          if(l>v)xr=xm-1;
          else xl=xm+1;
        }while(xl<=xr&&!b); // 外层二分
        if(b)c++;
      }
    }
  cout<<c<<endl;
  return 0;
}
```

---

