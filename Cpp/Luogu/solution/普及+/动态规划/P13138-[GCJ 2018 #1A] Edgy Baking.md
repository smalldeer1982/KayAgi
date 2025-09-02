# [GCJ 2018 #1A] Edgy Baking

## 题目描述

面包师 Mr. Maillard 已经将一些饼干面团擀平并切割，制作出了 $\mathbf{N}$ 块饼干，每块都是一个矩形。他正准备把它们放进烤箱时，突然想起饼干酥脆、焦糖化的边缘特别美味。具体来说，他认为如果所有饼干的周长之和尽可能接近 $\mathbf{P}$ 毫米（mm），且不超过 $\mathbf{P}$，他会最开心。（如果饼干的边太多，可能会烤焦！）

对于每块饼干，Mr. Maillard 可以选择保持原样，或者沿着一条直线将其一分为二（不一定是矩形），使得两部分面积相等。（注意，这样的切割必然经过饼干的中心。）通过这种方式切割后产生的两块新饼干不能再次切割。

如果 Mr. Maillard 做出最优决策，他能得到不超过 $\mathbf{P}$ 的最大周长和是多少？

## 说明/提示

**样例解释**

注意，最后一个样例不会出现在测试集 1 中。

样例 1 中，只有一块边长为 1 的正方形饼干。Mr. Maillard 可以从一个角到对角线上的另一个角切割，得到两个直角三角形，每个三角形的边长为 1、1 和 $\sqrt 2$。此时周长和为 $4+2 \times \sqrt 2$，小于 $\mathbf{P}=7$，但无法更接近。

样例 2 中，Mr. Maillard 可以沿着第一块饼干的长边切割，得到两个 $25 \times 120$ 的矩形，第二块保持不变。总周长为 $580+340=920$，正好等于 $\mathbf{P}$。

样例 3 中，Mr. Maillard 可以将饼干切割成两个梯形，每个梯形的边长为 $2, 4, 5, 5$。此时新的周长和为 $32$，正好等于 $\mathbf{P}$。

样例 4 中，初始周长和正好等于 $\mathbf{P}$，因此不需要切割。

**数据范围**

- $1 \leqslant \mathbf{T} \leqslant 100$。
- $1 \leqslant \mathbf{N} \leqslant 100$。
- $1 \leqslant \mathbf{W}_{\mathbf{i}} \leqslant 250$，对于所有 $i$。
- $1 \leqslant \mathbf{H}_{\mathbf{i}} \leqslant 250$，对于所有 $i$。
- $\mathbf{P} \geqslant 2 \times$ 所有 $\left(\mathbf{W}_{\mathbf{i}}+\mathbf{H}_{\mathbf{i}}\right)$ 的和。（$\mathbf{P}$ 至少等于所有饼干未切割时的周长和。）
- $\mathbf{P} \leqslant 10^{8}$。

**测试集 1（14 分，可见）**

- $\mathbf{W}_{\mathbf{i}}=\mathbf{W}_{\mathbf{j}}$，对于所有 $i$ 和 $j$。
- $\mathbf{H}_{\mathbf{i}}=\mathbf{H}_{\mathbf{j}}$，对于所有 $i$ 和 $j$。
- （所有给定的饼干尺寸都相同。）

**测试集 2（29 分，隐藏）**

- 除一般限制外无其他限制。（特别地，给定的饼干尺寸不一定都相同。）

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
1 7
1 1
2 920
50 120
50 120
1 32
7 4
3 240
10 20
20 30
30 10```

### 输出

```
Case #1: 6.828427
Case #2: 920.000000
Case #3: 32.000000
Case #4: 240.000000```

# 题解

## 作者：tuxiaolai (赞：0)

# 1 说明
由于题目刚出，**不保证**题解正确性，有问题请及时指出。
# 2 思路
由题意：一块大小为 $W_i \times H_i$ 的饼干，在切过后，周长会增加 $\left[2\times\min(W_i,H_i),2\times\sqrt{W_i^2+H_i^2}\right]$，我们记作 $\left[ l_i,r_i \right]$。

我们记一块饼干切之前的周长 $C_i=2 \times (W_i+H_i)$，那么，最后饼干的总周长至少是 $sum_C=\sum_{i=1}^n C_i$。在这基础上，我们要让周长尽量接近 $p$ 但又不大于 $p$。

如果我们只选择了第 $i$ 块饼干来切，那么总周长会是一个区间，即 $\left[ sum_C+l_i,sum_C+r_i \right]$。

- 若 $p\in \left[ sum_C+l_i,sum_C+r_i \right]$，则最大周长为 $p$；
- 若 $p>sum_C+r_i$，则最大周长为 $sum_C+r_i$。
- 若 $p<sum_C+l_i$，则改区间不符合要求。

总结一下就是 $\min(p,sum_C+r_i)$，当然，前提是 $sum_C+l_i\le p$。

如果选择了多块饼干，周长的区间就是 $\left[ sum_C+\sum l,sum_C+\sum r \right]$，而判断方式则与上面相同。也就是说，我们要在保证 $sum_C+\sum l \le p$ 的情况下，尽量增大 $sum_C+\sum r$ 的值。没错！就是背包 DP！！！

我们将左边界作为大小，右边界作为价值，为减少运算次数，将背包容量设为 $\min(p-sum_C,\sum_{i=1}^{n} l_i)$，同时一旦有出现右边界之和大于 $p-sum_C$ 的情况就可以直接输出了。
# 3 AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n;
double p;
double w,h;
double l[110],r[110];
double dp[50010];
double sumc,suml;
double ans;
double c(double w,double h) {
    return 2*(w+h);
}
double minc(double w,double h) {
    return 2*min(w,h);
}
double maxc(double w,double h) {
    return 2*sqrt(w*w+h*h);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    for(int k=1; k<=T; k++) {
        memset(l,0,sizeof(l));
        memset(r,0,sizeof(r));
        memset(dp,0,sizeof(dp));
        sumc=0;
        suml=0;
        cin>>n>>p;
        for(int i=1; i<=n; i++) {
            cin>>w>>h;
            sumc+=c(w,h);
            l[i]=minc(w,h);
            r[i]=maxc(w,h);
            suml+=l[i];
        }
        ans=sumc;
        for(int i=1;i<=n;i++){
            for(int j=min(suml,p-sumc);j>=l[i];j--){
                dp[j]=max(dp[j],dp[j-(int)l[i]]+r[i]);
                ans=max(ans,sumc+dp[j]);
                if(dp[j]+sumc>=p){
                    goto g;
                }
            }
        }
        g:
        cout<<"Case #"<<k<<": ";
        cout<<fixed<<setprecision(6)<<min(ans,p);
        cout<<'\n';
    }
    return 0;
}
```
为方便大家理解，以下是部分注释：

$T,n,p,w,h$ 如题意。

$l,r$ 分别记录每块饼干的左右边界，即上文中的 $l_i,r_i$。

$sumc,suml$ 即 $\sum_{i=1}^{n} C_i,\sum_{i=1}^{n} l_i$。

$c,minc,maxc$ 用于计算原周长和左右边界。

完结撒花！

---

