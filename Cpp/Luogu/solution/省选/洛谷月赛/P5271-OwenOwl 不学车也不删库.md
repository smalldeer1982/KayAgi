# OwenOwl 不学车也不删库

## 题目背景

神 mcfx 和神 ComeIntoPower 没事就瞎编题目背景。OwenOwl 去问基佬 zcysky 他们这么做的原因，基佬 zcysky 却这样答复：

![](https://cdn.luogu.com.cn/upload/pic/54751.png)

OwenOwl 非常郁闷，于是他有一天找到了神 J，让神 J 造了 20010910 个指针把他们三个指到阿塞拜疆去陪 sunset 阿克了。

他们三个游览阿塞拜疆的时候，OwenOwl 就把车砸了，库恢复了。

但是因为神 mcfx 和神 ComeIntoPower 之前以 OwenOwl 这个 ID 出了太多毒瘤题，OwenOwl 早就风评被害了。为了证明毒瘤的是他俩，不是自己，OwenOwl 就出了道签到题。

## 题目描述

设 $p$ 是一个质数。

你有一个 $p^k$ 个点的无向完全图（任意两个点之间有一条无向边），点的标号是 $0$ 到 $p^k-1$。

现在你需要从中找出一些 $p$ 个点的完全图，使得原图中每条边属于且恰好属于其中一个完全图。

很显然你需要找出的完全图的个数是 $\frac{p^k(p^k-1)/2}{p(p-1)/2} $，可以发现这个式子一定是整数

## 说明/提示

对于 $10\%$ 的数据，$k \le 1$；

对于 $50\%$ 的数据，$k \le 2$；

另有 $20\%$ 的数据，$p = 2$；

对于 $100\%$ 的数据，$k$ 是正整数，$p$ 是质数，$2 \le p^k \le 2000$。

另外，保证输出总量不超过 2MB，但仍请注意控制输出所花费的时间。

## 样例 #1

### 输入

```
2 2```

### 输出

```
YES
0 1
2 0
3 0
1 2
1 3
3 2```

## 样例 #2

### 输入

```
3 1```

### 输出

```
YES
0 1 2```

# 题解

## 作者：shadowice1984 (赞：14)

神仙构造题……

膜神O

__________________

## 本题题解

题意简单明了此处不在赘述

那么首先我们发现题目中要求我们构造的方案是$P^k$，这个限制条件绝对是在告诉我们"要分治"

那么我们不妨考虑通过分治法来构造我们的方案

换句话讲，我们希望构造出大小为$P^k$的方案，可以采取这样的一个算法流程

如果$k=1$那么可以直接输出$0\dots P-1$

否则我们递归下去构造出一个$P^{k-1}$的解，然后把这个解当中的点的编号分别加上$0,P^{k-1},2P^{k-1} \dots (P-1)P^{k-1}$各输出一下

此时我们发现如果两个点的编号除P下取整一样的话，那么这条边在之前的分治当中已经处理完毕了，此时我们可以认为为所有点被分成了$P$块，每块的长度都是$P^{k-1}$，如果两个点所在的块不同则没有边

**为了方便起见我们把点重新标号，膜$P^{k-1}$同余的点标号相同**，这样会方便我们构造之后的解，输出的时候只需要把点的标号加上所在块的编号×$P^{k-1}$即可还原真实的解

此时我们希望选择一些团覆盖这张图的所有边，这样我们就做完这道题啦~

那咋做呢？

首先先来思考一个很trivial的问题，我们到底要输出多少个团呢？

一共有$(P^{k-1})^2{P \choose 2}$条边，每个团可以覆盖${P \choose 2}$条边，所以我们要输出$(P^{k-1})^2$个团

那我们不妨对着这个平方开始编

不如重新整理一下我们的限制条件，在这一*-层分治我们要做的事情是，确定$P^{k-1}$个长度为$P$的数组，数组当中的每个数字在$[0,P^{k-1}]$之间，并且满足这个限制条件

**任意两个数组至多有1位相同**

注意到我们要构造平方个数组，这样实在是好烦啊，我们想一想能不能把我们的工作量减少一些，现在假装我们构造了$P^{k-1}$个符合上述条件的数组，我们将这些数组的每一位加上$0,1,2, \dots P^{k-1}-1$之后对$P^{k-1}$取膜，这样我们将**有可能**从$P^{k-1}$个数组拓展出一个有$(P^{k-1})^2$个数组

~~喔，你问我怎么编出来的？各种常见的构造方式挨个试一试，碰巧这种对着方案数编构造的方法奏效了而已~~

采取上述方式构造的话,初始的解需要满足以下的条件

**任意两个数组对应位置做差，不能存在相等的数字**

那这样的$P^{k-1}$个数组怎么构造呢？

稍微编了一会之后我们发现让第$i$个数组的第$j$位为$i×j \mod P^{k-1}$
就行了，这样显然任意两个数组做差之后都不存在相等的数字啊

~~喔，你问我这是怎么编出来的?当然还是各种数组胡乱试一试然后这个碰巧奏效啦~~

那这样我们就有了作为"种子"的初始$P^{k-1}$个解，就可以用它倒过来生成 那$(P^{k-1})^2$个数组啦，于是我们的分治法成功奏效这题就做完了……

听说这题卡输出于是写了个快速输出……速度惊人

```C
#include<cstdio>
#include<algorithm>
using namespace std;const int N=2010;typedef long long ll;
inline ll po(ll a,ll p){ll r=1;for(;p;p>>=1,a=a*a)if(p&1)r=r*a;return r;}
char mde[N][6];int hd[N];
inline void pre()//这里写了个快速输出 
{
    mde[0][0]=' ';mde[0][1]='0';hd[0]=1;
    for(int i=1;i<N;i++)
    {
        int p=i;mde[i][0]=' ';
        while(p){mde[i][++hd[i]]='0'+p%10;p/=10;}
    }
}inline void prit(int x){for(int i=hd[x];i>=0;i--)putchar(mde[x][i]);}
int a[N];int b[N];
inline void cons(int ad,int p,int k,int tot)//没啥好说的，就是直接分治就好了 
{
    if(k==1){for(int i=0;i<p;i++)prit(ad+i);putchar('\n');return;}//边界条件 
    int bl=tot/p;for(int i=0;i<tot;i+=bl)cons(ad+i,p,k-1,bl);//挨个递归 
    for(int i=0,id=0;i<tot;i+=bl,id++)a[id]=i;
    for(int st=0;st<bl;st++)
    {
        b[0]=0;b[1]=st;for(int i=2;i<=p-1;i++)b[i]=(st+b[i-1])%bl;
        for(int plus=0;plus<bl;plus++)//输出这一层的解 
        {for(int i=0;i<p;i++)prit(ad+a[i]+(b[i]+plus)%bl);putchar('\n');}
    }
}int main(){pre();int p;int k;scanf("%d%d",&p,&k);printf("YES\n");cons(0,p,k,po(p,k));}
```



---

## 作者：OwenOwl (赞：12)

题目 Idea 来自 call_me_std。

出题人做法不是递归构造，是直接构造。

建立一个模 $p$ 意义下的 $k$ 维空间，这样空间中恰好有 $p^k$ 个点，我们让原图每一个点对应空间中一个点。

枚举一个非零向量 $v$ 和起点 $x$，把 $x, x+v, x+2v,\ldots, x+(p-1)v$ 分为一组即可。

显然两个不同点唯一确定同一组里剩下 $p-2$ 个点。

证明可以考虑在模 $p$ 意义下运算的唯一性（$p$ 不为质数时并不能这样构造）。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
  int p, k, n = 1;
  scanf("%d%d", &p, &k);
  puts("YES");
  for (int i = 0; i < k; i++) {
    n *= p;
  }
  std::function<int(int, int)> add = [&] (int x, int y) {
    int result = 0, power = 1;
    for (int i = 0; i < k; i++, x /= p, y /= p, power *= p) {
      result = result + (p + x % p + y % p) % p * power;
    }
    return result;
  };
  std::vector<std::vector<bool>> visit(n, std::vector<bool>(n));
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) if (!visit[i][j]) {
      //找一条还没处理的边(i,j)，求出同一组剩下的点
      std::vector<int> index(1, i);
      int v = add(j, -i);
      for (int l = 1; l < p; l++) {
        index.push_back(add(index.back(), v));
      }
      for (auto x : index) {
        printf("%d ", x);
        for (auto y : index) {
          visit[x][y] = true;
        }
      }
      puts("");
    }
  }
  return 0;
}
```

---

## 作者：xlpg0713 (赞：0)

方便叙述采用 1-index。

考虑 $k=2$，此时可以把元素划分成 $p$ 行 $p$ 列。每一行划分为同一个子图，然后对于每一对 $w\in[1,p],q\in[0,p-1]$，将第 $x$ 行的第 $w+qx$ 个共 $p$ 个元素划分为一个子图。注意到 $p$ 是质数，所以 $\forall x,a\not\equiv b\ \bmod p$，有 $ax\not\equiv bx$，这样就满足了每一条边只在一个子图中出现。

考虑 $k>2$，构造出 $p^{k-1}$ 的解，将点集平均划分为 $p$ 组，每组内部按照 $p^{k-1}$ 的方法内部连边，然后对于每一对 $w\in[1,p^{k-1}],q\in[0,p^{k-1}-1]$，将第 $x$ 行的第 $w+qx$ 个元素放到一张子图中。我们仍然可以证明这样的构造不会重复。这也是这题保证 $p$ 是质数的关键。

如此递归构造即可。

---

