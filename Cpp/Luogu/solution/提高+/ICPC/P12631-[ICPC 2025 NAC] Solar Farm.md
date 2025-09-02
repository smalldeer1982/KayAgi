# [ICPC 2025 NAC] Solar Farm

## 题目描述

你正在建造一个新的太阳能农场。允许建造的区域是一个半径为 $r$ 的圆形场地，而每块太阳能电池板占据一个大小为 $w \times h$ 的矩形空间。你必须将所有电池板按照你选择的同一方向排列成一个单一的矩形阵列（即所有电池板组合起来恰好形成一个完整的矩形）。在这个农场中，最多可以放置多少块电池板？

## 说明/提示

下图展示了样例输入 1 中三个测试用例（从左到右）各自的一种最优太阳能电池板布局。

![](https://cdn.luogu.com.cn/upload/image_hosting/l3d8fv6t.png)

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
5 4 3
2 2 2
8 1 5```

### 输出

```
4
1
24```

## 样例 #2

### 输入

```
2
500000003 1 600000010
511374200 637192506 100000000```

### 输出

```
799999999
7```

# 题解

## 作者：shinzanmono (赞：1)

先判掉无解（$w^2+h^2>4r^2$）。

如果横放 $i$ 列，那最多能放 $\left\lfloor\dfrac{\sqrt{4r^2-i^2w^2}}h\right\rfloor$ 行。答案即为 $\max_{i=0}^{\lfloor2r/w\rfloor}i\left\lfloor\dfrac{\sqrt{4r^2-i^2w^2}}h\right\rfloor$。考虑后面这个东西如果去掉下取整，其最值是简单的（取导求极值点）。合理猜想有下取整的极值点和原极值点差的不远，对一个邻域 $[p-B,p+B]$ 枚举求值即可。笔者的 $B$ 取 $10000$。

```cpp
#include<iostream>
#include<algorithm>
using ll=long long;
ll sqrt(ll x){
  ll p=__builtin_sqrtl(x);
  while(p*p<=x)p++;
  while(p*p>x)p--;
  return p;
}
int main(){
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  std::cin>>t;
  while(t--){
    ll rad,w,h;
    std::cin>>rad>>w>>h;
    if(w*w+h*h>4*rad*rad){
      std::cout<<"0\n";
      continue;
    }
    if(w<h)std::swap(w,h);
    auto ff=[&](ll x){return sqrt(4*rad*rad-w*w*x*x)/h*x;};
    ll l=sqrt(2*rad*rad/w/w),ans=0,B=10000;
    for(ll i=std::max(1ll,l-B);i<=std::min(2*rad/w,l+B);i++)ans=std::max(ans,ff(i));
    std::cout<<ans<<"\n";
  }
  return 0;
}
```

---

