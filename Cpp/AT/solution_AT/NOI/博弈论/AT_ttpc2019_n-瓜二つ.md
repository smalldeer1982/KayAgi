# 瓜二つ

## 题目描述

双胞胎 **尤里（Yuri）** 和 **穆里（Muri）** 虽然长得一模一样，但性格完全相反。例如，尤里喜欢**有理数**，而穆里则喜欢**无理数**。  
他们将用 $N$ 个杯子进行以下游戏：

- 最开始，第 $i$ 个杯子中有 $W_i$ 升水，同时定义两个数 $l_i, u_i$，其中 $l_i < u_i$。
- 他们**轮流**进行操作，**无法进行操作的一方输掉游戏**。

游戏的操作规则如下：

1. 选择一个整数 $k$ ($1 \leq k \leq N$)，并记该杯中剩余的水量为 $R_k$ 升。
2. 选择一个满足 $l_k \leq x \leq u_k$ 且 $x \leq R_k$ 的数 $x$，然后从该杯中喝掉 $x$ 升的水。  
   - **尤里（Yuri）**只能选择**有理数** $x$。
   - **穆里（Muri）**只能选择**无理数** $x$。  
   - 如果找不到符合条件的 $x$ 和 $k$，则无法进行操作，当前玩家输掉游戏。

由于输入中所有的 $W_i, l_i, u_i$ 都是整数，为了保证游戏可行，**穆里（Muri）可以决定自己是否先手**。

假设双方都采取最优策略，请判断谁能获胜：

- 如果尤里（Yuri）获胜，则输出 `"Yuri"`。
- 如果穆里（Muri）获胜，则输出 `"Muri"`。

## 说明/提示

### 限制

- 所有输入均为整数
- $1 \le N \le 2 \times 10^5$
- $1 \le W_i \le 10^9$
- $1 \le l_i < u_i \le 10^9$

### 样例解释 1

- 穆里选择**先手**，并在第一个杯子里选 $x = 5 - \pi / 4$，此时第一个杯子剩余 $3 + \pi / 4$ 升水。
- 尤里只能选择有理数，他选择 $x = 2$，导致剩余 $1 + \pi / 4$。
- 之后穆里可以在第二个杯子执行类似操作，最终导致尤里无路可走，穆里获胜。

### 样例解释 2

- 只有 $1 \leq x \leq 2$ 且 $x \leq 1$，唯一满足条件的 $x = 1$ 是整数，因此尤里可以选择它。
- 由于整数也是有理数，尤里可以执行该操作，而穆里无法选取无理数，所以穆里无法行动，尤里获胜。

## 样例 #1

### 输入

```
2
8 2 5
7 5 6```

### 输出

```
Muri```

## 样例 #2

### 输入

```
1
1 1 2```

### 输出

```
Yuri```

## 样例 #3

### 输入

```
5
12 1 100
11 2 8
1 5 7
7 5 7
29 4 5```

### 输出

```
Muri```

# 题解

## 作者：qzhwlzy (赞：3)

## 题目大意

有 $n$ 个杯子，第 $i$ 个杯子里装有 $W_i$ 升水，且有 $n$ 对正整数 $l_i,r_i$。Yuri 和 Muri 两人在玩一个游戏：两人轮流进行操作，最先不能进行操作者输。

一次操作定义为：操作者选择一个杯子 $i$，从中喝掉 $x_i$ 升水。对于两个人，都要满足 $x_i\in[l_i,\min(r_i,W_i)]$，且对于 Yuri 要满足 $x_i$ 是**有理数**、对于 Muri 要满足 $x_i$ 是**无理数**。

现在，**Muri 可以选择先后手**，若两人以最优策略行动，问谁会获胜。

## 思路

我们发现，在一定的精度内，相距很近的有理数与无理数之间对胜负性的影响并不大，胜负状态间的转折点只是一些整数点，于是可以把 Yuri 和 Muri 的取数值域分别看做是 $[l_i,r_i]$ 和 $(l_i,r_i)$。如下图（表示进行一次操作之后能得到的 $W^\prime_i$。上面为 Yuri 的，下面为 Muri 的，下同）：

![](https://cdn.luogu.com.cn/upload/image_hosting/j1xy3jhr.png)

---

接下来我们尝试打表这个博弈的 SG 函数。

以 Yuri 为例。我们发现，当 $r_i$ 足够大时，前一部分的 SG 具有一定的规律性：

- 若 $W_i\in [0,l_i)$，此时无法进行操作，SG 为 $0$；
- 若 $W_i\in [l_i,2l_i)$，此时可以转移到 SG 为 $0$ 的部分，故 SG 为 $1$；
- 若 $W_i\in [2l_i,3l_i)$，此时可以转移到 SG 为 $0$ 和 $1$ 的部分，故 SG 为 $2$；
- ……

所以，在 $W_i$ 较小的时候，SG 呈现这样一个“阶梯”形。等到遇到了 $r_i$，SG 又会有相应的改变。取整数 $t$，满足 $tl_i < l_i+r_i\le (t+1)l_i$，那么，继续分类讨论：

- 若 $W_i\in[tl_i,l_i+r_i)$，根据上面，SG 为 $t$；
- 若 $W_i\in[l_i+r_i,2l_i,r_i)$，此时，如下图，无法转移到 SG 为 $0$ 的部分，故 SG 为 $0$；
![](https://cdn.luogu.com.cn/upload/image_hosting/g8q29roa.png)
- 若 $W_i\in[2l_i+r_i,3l_i,r_i)$，此时无法转移到 SG 为 $1$ 的部分，故 SG 为 $1$；
- ……

如此下去，得到 Yuri 的最终的 SG 如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/qzfnalo2.png)

同理，我们可以得到 Muri 的 SG，总体如下图所示，它与 Yuri 的只在某些整点处的取值略有不同，大体上是一样的，这也是为什么我们可以把取数值域进行近似的原因。

![](https://cdn.luogu.com.cn/upload/image_hosting/1r9vrcb1.png)

下称 SG 突变的点为转折点，即满足 $l_i\ |\ W_i\bmod(l_i+r_i)$ 的点。

---

那么，对于这个非公平的博弈，SG 是否仍然有用呢？显然是有的。在非转折点上，SG 仍然可以判断胜负性，若 SG 为 $0$ 则先手必败，否则先手必胜。在转折点上的情况下面会讲。

注意到在本题中，Muri 取数值域为 Yuri 取数值域的真子集，所以若**在 Muri 的视角下**其是必败的（故下面两种情况下的“SG”指的是 Muri 的），Yuri 可以只用 Muri 的取数值域让其必败。故，在「SG 为 $0$ 且 Muri 先手」或「SG 不为 $0$ 且 Yuri 先手」时 Yuri 必胜。

---

上面提到在转折点上，SG 可能不奏效。在官方题解中，定义了包括这些转折点在内的一类点，称为“「不正」点”，根据 std，本文中将其翻译为“作弊点”。若此时水量在作弊点，那么 Yuri 可以通过操作改变 SG 对自己的不利。作弊点有以下两类：

1. 所有转折点，即满足 $l_i\ |\ W_i\bmod(l_i+r_i)$ 的点。  
![](https://cdn.luogu.com.cn/upload/image_hosting/t25u8cfl.png)  
此时若 Yuri 先手，假设此时有 $p(l_i+r_i)+ql_i$ 的水，SG 为 $q$，其可以选择喝 $l_i$ 的水，此时水量 $W=p(l_i+r_i)+(q-1)l_i$，SG 为 $q-1$，但是，此时 Muri 操作后能够到达的 $W\in((p-1)(l_i+r_i)+ql_i,p(l_i+r_i)+(q-2)l_i)$，没有 SG 为 $q$ 的点，所以就无法保证必胜。

2. $W\in[2l_i,l_i+r_i]\cap\mathbb{Q}$ 中的点。  
此时 Yuri 可以把水量转移到 $l_i$ 从而保证必胜，因为此时只有其可以操作这杯水。注意一定得是**有理**的，~~有人忘了这个前提以为自己 hack 了 std。~~

于是，我们可以判断，若为「SG 为 $0$ 且 Yuri 先手」的情况，若其中有作弊点，则 Yuri 必胜，否则 Muri 必胜。若为 「SG 不为 $0$ 且 Muri 先手」的情况，则若 Muri 第一步能保证去除所有作弊点，则 Muri 必胜，否则 Yuri 必胜。注意这里的 SG 也应该**在 Muri 的视角下**，因为作弊点是对于 Yuri 而言的。

---

所以，整个过程我们只需要统计初始 Muri 视角下的 SG 和，然后判断是否有 Muri 必胜的情况，若有则 Muri 必胜，否则 Yuri 必胜。

---

```cpp
#include<iostream>
#include<cstdio>
#define maxn 200005
using namespace std;
int n,w[maxn],l[maxn],r[maxn],sg[maxn],sgsum=0;
int main(){
      scanf("%d",&n); for(int i=1;i<=n;i++) scanf("%d%d%d",&w[i],&l[i],&r[i]);
      for(int i=1;i<=n;i++){int res=w[i]%(l[i]+r[i]); sgsum^=(sg[i]=max(0,((res-1)/l[i])));} // calculate sgsum
      if(sgsum==0){ // Muri can win if and only if there's no "cheating point"
            bool flag=0; for(int i=1;i<=n&&!flag;i++){
                  int res=w[i]%(l[i]+r[i]);
                  flag|=((res%l[i]==0)||(w[i]<l[i]+r[i]&&w[i]>=2*l[i])); // determine if there's "cheating point"
            } if(flag) printf("Yuri"); else printf("Muri");
      }else{ // Muri can win if and only if there's one way to make sgsum==0 and there's no "cheating point"
            int num=0,pos=0; for(int i=1;i<=n;i++)
                  {int res=w[i]%(l[i]+r[i]); if((res%l[i]==0)||(w[i]<l[i]+r[i]&&w[i]>=2*l[i])){num++; pos=i;}}
            if(num>1){printf("Yuri"); return 0;} // Muri will never win since the number of "cheating point" > 1
            if(num==0){printf("Muri"); return 0;}// if there's no "cheating point", Muri can always win
            // otherwise, if there's exactly one "cheating point"
            int res=sgsum^sg[pos],mmax=(l[pos]+r[pos]-1)/l[pos]; // new grundy number and maximum grundy number
            if(res>mmax){printf("Yuri"); return 0;} // new grundy number won't exist
            int left=res*l[pos],right=min(res*l[pos]+l[pos],l[pos]+r[pos]);
            int T=max(0,w[pos]/(l[pos]+r[pos])-(sg[pos]<res));
            if(w[pos]<=l[pos]+r[pos]){if((res==0||res==1)&&res<sg[pos]) printf("Muri"); else printf("Yuri"); return 0;}
            // determine if (left+T*(l+r) , right+T*(l+r)) ∩ (w-r , w-l)  
            if(!(right+T*(l[pos]+r[pos])<=w[pos]-r[pos]||left+T*(l[pos]+r[pos])>=w[pos]-l[pos]))
                  printf("Muri"); else printf("Yuri");
      }
      return 0;
}
/*
2
16 3 5
7 5 6

2
17 3 7
10 3 7
*/
```


---

