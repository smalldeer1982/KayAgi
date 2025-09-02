# σ

## 题目描述

请提供详细、清晰的问题描述，以便参赛者理解题目要解决的问题。

## 说明/提示

提供与数据相关的约束和范围，以帮助参赛者估计可能的算法复杂度和性能需求。另外，给出一些可能有用的提示，帮助参赛者找到解决问题的思路。

欢迎补充具体内容，以便更好地翻译和润色。

 **本翻译由 AI 自动生成**

# 题解

## 作者：FFTotoro (赞：0)

这种排列交互题可以使用随机化调整法，一起感受 $11$ 年前的人类智慧。下文中和代码中所有数列均默认 $0$-indexed。

随机 $Q=240$ 个排列直接问，然后存一个表下来表示询问的结果。记 $p_i$（即题面中的 $\tau_i$）为第 $i$ 次**询问的排列**，同时令 $m_{i,p_{i,j}}=j$，$b_i$ 为第 $i$ 次询问时**交互库返回的序列**，$c_{i,x}$ 为 **$b_i$ 中 $x$ 出现的次数**。

对于我们需要求出的 $r$（即最终回答给交互库的答案排列），考虑如下这个值：

$$P=\sum\limits_{q=0}^{Q-1}\sum\limits_{d=0}^{N-1}\max\left\{c_{q,d}-\sum\limits_{i=0}^{N-1}\left[|m_{q,r_i}-i|=d\right],0\right\}$$

其中 $||$ 表示绝对值，$[]$ 表示艾弗森括号。由 $P$ 的定义可以看出，$P=0$ 是所有数都“归位”了的必要条件（即求出来的答案符合所有的询问结果），因为是 $Q$ 个排列都是随机的，所以可以将其视为充要条件。

先随机一个 $r$，然后不断交换 $r$ 中的两个元素 $i,j$，如果 $P$ 的值变小了就将 $r$ 变为新的 $r$，否则不接受新方案。每次交换后计算 $P$ 的时间复杂度可以优化到 $O(Q)$：不需要每次都求一遍 $\sum\limits_{i=0}^{N-1}\left[|m_{q,r_i}-i|=d\right]$，开始时直接把 $c_{q,d}$ 减掉这个值，后续交换时直接维护 $c_{q,d}$ 和 $P$ 就行。

记得特判一下 $N=1$。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Q=240;
mt19937 g(time(0));
int main(){
  ios::sync_with_stdio(false);
  int n; cin>>n;
  if(n==1)cout<<"! 1"<<endl,exit(0);
  vector<int> r(n);
  vector p(Q,vector<int>(n)),m=p,c=p;
  iota(r.begin(),r.end(),0);
  for(int i=0;i<Q;i++){
    shuffle(r.begin(),r.end(),g),p[i]=r;
    for(int j=0;j<n;j++)
      m[i][p[i][j]]=j;
  } // 生成若干询问排列，顺带求出 m 数组
  for(int i=0;i<Q;i++){
    cout<<"? ";
    for(int j=0;j<n;j++)
      cout<<p[i][j]+1<<' ';
    cout<<endl;
    for(int j=0;j<n;j++){
      int x; cin>>x,c[i][x]++;
    }
  } // 进行询问，求出 c 数组
  int P=Q*n;
  for(int i=0;i<Q;i++)
    for(int j=0;j<n;j++){
      int d=abs(m[i][r[j]]-j);
      if(--c[i][d]>=0)P--;
    } // 求出初始的 P
  uniform_int_distribution<> u(0,n-1);
  auto op=[&](int a,int b){
    int P=0,w=0;
    // 分别为分数的减量（与增量相对）和还原标记
    for(int i=0;i<Q;i++){
      if(c[i][abs(m[i][r[a]]-a)]++>=0)P--;
      if(c[i][abs(m[i][r[b]]-b)]++>=0)P--;
      if(--c[i][abs(m[i][r[a]]-b)]>=0)P++;
      if(--c[i][abs(m[i][r[b]]-a)]>=0)P++;
      if(w=i;P<-9)break;
      // 小优化，不让答案在一个前缀增量太大
    } // O(Q) 计算修改后的 c 数组
    if(P<0){
      for(int i=0;i<=w;i++){
        c[i][abs(m[i][r[a]]-a)]--;
        c[i][abs(m[i][r[b]]-b)]--;
        c[i][abs(m[i][r[a]]-b)]++;
        c[i][abs(m[i][r[b]]-a)]++;
      } // 还原 c 数组
      return P;
    } // 会让答案变大，不采纳
    return swap(r[a],r[b]),P;
  };
  while(P){
    int x=u(g),y=u(g);
    while(x==y)y=u(g);
    if(int p=op(x,y);p>0)P-=p;
  } // 循环直到找到答案
  cout<<"! ";
  for(int i:r)cout<<i+1<<' ';
  cout<<endl;
  return 0;
}
```

---

