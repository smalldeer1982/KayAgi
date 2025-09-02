# [PA 2016] 寻踪 / Ciepło-zimno

## 题目背景


译自 [Potyczki Algorytmiczne 2016](https://sio2.mimuw.edu.pl/c/pa-2016-1/p/) R3 Ciepło-zimno [B] (CIE)。$\texttt{1s,256M}$。

原题为函数式交互题。为了方便不同语言的选手提交，改为 IO 交互题。

特殊的内存限制是交互库的限制导致的，和解法没有关系。

## 题目描述


**这是一道交互题。**

给定正常数 $n,k,r$。

$n$ 维空间中，有一个整点 $P(p_1,p_2,\ldots,p_n)$，满足 $p_i\in [0,r]$。

你有 $k$ 次询问机会，第 $i$ 次询问给定一个整点 $V_i(v_{i,1},v_{i,2},\ldots,v_{i,n})$，回答为「$\operatorname{dist}(V_i,P)$ 是/否**严格**小于 $\operatorname{dist}(V_{i-1},P)$」。**特别地**，$i=1$ 时，答案总为否。

注意，这里的 $\operatorname{dist}(A,B)$ 表示 $A,B$ 之间的 **Chebyshev 距离**。也就是，$\displaystyle \operatorname{dist}(A,B)=\max_{1\le i\le n} |A_i-B_i|$，这里 $A_i$ 表示点 $A$ 坐标在第 $i$ 维上的分量。

利用询问找到点 $P$。

### 实现细节

**注意：本题的 IO 量可能很大，请注意使用快速的 IO 方式。**

读入三个正整数 $n,k,r$。然后开始交互：

- $\texttt{?}$ $v_{i,1}$ $v_{i,2}$ $\ldots$ $v_{i,n}$：询问「$\operatorname{dist}(V_i,P)$ 是/否**严格**小于 $\operatorname{dist}(V_{i-1},P)$」。
    - 回答为 $0$，表示答案为否；回答为 $1$，表示答案为是；回答为 $-1$，表示你的程序已经被判为 WA，请**立刻终止程序**。
        - 特别地，如果这是第一次询问，则（如果询问合法的话）回答总为 $0$。
    - 你需要保证 $v_{i,j}\in [0,r]$，且 $v_{i,j}$ 为整数。
    - 最多可以询问 $k$ 次。
- $\texttt{!}$ $p_{1}$ $p_{2}$ $\ldots$ $p_{n}$：回答 $P$ 的位置。
    - 回答后，你的程序需要立刻终止，不要输出多余内容。

**每次询问或者回答之后，都要换行并刷新缓冲区。** 以下是一些例子：

- C++：`fflush(stdout)`，`std::cout<<std::endl`；
- Java：`System.out.flush()`；
- Pascal：`flush(output)`；
- Python：`sys.stdout.flush()`。

## 说明/提示



- $1\le n\le 500$；
- $k\ge 100\cdot n$；
- $2\le r\le 10^9$。


## 样例 #1

### 输入

```
2 200 2

0

1

1```

### 输出

```

? 0 0

? 1 1

? 2 2

! 2 2```

# 题解

## 作者：FFTotoro (赞：5)

给 mashup 验了个题，简单来写一个题解。

在交互过程中，考虑缩小每一维的取值范围，不妨认为第 $i$ 维 $p_i$ 的取值范围为 $[l_i,r_i]$。

令每一维的值域为 $[0,R]$。一开始我们没有任何信息，所以 $l_i=0,r_i=R$。

考虑每次取出 $r_i-l_i+1$ 最大的 $i$，构造两个向量 $V_1,V_2$ 满足 $V_{1,i}=l_i,V_{2,i}=r_i$ 且 $\forall j\ne i,V_{1,j}=V_{2,j}=\left\lfloor\frac{l_j+r_j}{2}\right\rfloor$ 进行比较（令其他 $V_{1,j}(j\ne i)$ 和 $V_{2,j}(j\ne i)$ 的值为 $l_j$ 与 $r_j$ 的中点，可以尽量减少其他维度的值影响到答案）。

这样的思路类似二分，可以**近似地**得出 $p_i$ 离 $l_i$ 还是 $r_i$ 更近——为什么说是“近似地”？因为对于 $r_i-l_i+1$ 为偶数的情况，假设存在若干个 $r_j-l_j=r_i-l_i$ 的 $j(j\ne i)$，那么按上面的方式询问，答案要对 $\left\lceil\frac{r_i-l_i+1}{2}\right\rceil$ 取 $\max$，最坏情况下只能把值域缩小到 $\left[l_i,\left\lfloor\frac{l_i+r_i}{2}\right\rfloor+1\right]$。

但这种方法已经足够将最终所有的 $l_i$ 和 $r_i$ 缩小到满足 $r_i-l_i\le 1$。此时对于所有 $r_i-l_i=1$ 的 $i$ 单独处理：如果 $l_i>0$，那么构造向量 $V_1,V_2$ 满足 $V_{1,i}=l_i-1,V_{2,i}=r_i$ 且 $V_{1,j}=V_{2,j}=l_j(j\ne i)$ 进行比较，就可以得出 $p_i=l_i$ 还是 $r_i$；由于 $R\ge 2$，所以对于 $l_i=0$ 的情况同理。

询问次数是 $O(n\log R)$ 的。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct info{
  int p,l,r;
  info(int p=0,int l=0,int r=0):p(p),l(l),r(r){}
  inline bool operator <(const info &x)const{
    return r-l<x.r-x.l;
  }
};
int main(){
  ios::sync_with_stdio(false);
  int n,k,v; cin>>n>>k>>v;
  vector<pair<int,int> > w(n,make_pair(0,v));
  priority_queue<info> q;
  for(int i=0;i<n;i++)
    q.emplace(i,0,v);
  while(q.top().r-q.top().l>1){
    auto [p,l,r]=q.top(); q.pop();
    cout<<"? ";
    for(int i=0;i<n;i++){
      if(i==p)cout<<l<<' ';
      else cout<<(w[i].first+w[i].second>>1)<<' ';
    }
    cout<<endl;
    int x; cin>>x;
    cout<<"? ";
    for(int i=0;i<n;i++){
      if(i==p)cout<<r<<' ';
      else cout<<(w[i].first+w[i].second>>1)<<' ';
    }
    cout<<endl;
    if(cin>>x;x)w[p].first=(l+r>>1)+1;
    else{
      if(r-l+1&1)w[p].second=l+r>>1;
      else w[p].second=(l+r>>1)+1;
    }
    q.emplace(p,w[p].first,w[p].second);
  } // 每次取出 r[i]-l[i] 最大的 i 进行询问
  for(int i=0;i<n;i++)
    if(w[i].first<w[i].second){
      if(w[i].second==v){
        cout<<"? ";
        for(int j=0;j<n;j++){
          if(i==j)cout<<w[j].first-1<<' ';
          else cout<<w[j].first<<' ';
        }
        cout<<endl;
        int x; cin>>x;
        cout<<"? ";
        for(int j=0;j<n;j++){
          if(i==j)cout<<w[j].second<<' ';
          else cout<<w[j].first<<' ';
        }
        cout<<endl;
        if(cin>>x;x)w[i].first=w[i].second;
        else w[i].second=w[i].first;
      }
      else{
        cout<<"? ";
        for(int j=0;j<n;j++){
          if(i==j)cout<<w[j].second+1<<' ';
          else cout<<w[j].first<<' ';
        }
        cout<<endl;
        int x; cin>>x;
        cout<<"? ";
        for(int j=0;j<n;j++){
          if(i==j)cout<<w[j].first<<' ';
          else cout<<w[j].first<<' ';
        }
        cout<<endl;
        if(cin>>x;x)w[i].second=w[i].first;
        else w[i].first=w[i].second;
      }
    } // 特殊处理 r[i]-l[i]=1 的 i
  cout<<"! ";
  for(auto i:w)cout<<i.first<<' ';
  cout<<endl;
  return 0;
}
```

---

