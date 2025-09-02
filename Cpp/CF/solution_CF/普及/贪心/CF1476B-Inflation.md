# Inflation

## 题目描述

You have a statistic of price changes for one product represented as an array of $ n $ positive integers $ p_0, p_1, \dots, p_{n - 1} $ , where $ p_0 $ is the initial price of the product and $ p_i $ is how the price was increased during the $ i $ -th month.

Using these price changes you are asked to calculate the inflation coefficients for each month as the ratio of current price increase $ p_i $ to the price at the start of this month $ (p_0 + p_1 + \dots + p_{i - 1}) $ .

Your boss said you clearly that the inflation coefficients must not exceed $ k $ %, so you decided to increase some values $ p_i $ in such a way, that all $ p_i $ remain integers and the inflation coefficients for each month don't exceed $ k $ %.

You know, that the bigger changes — the more obvious cheating. That's why you need to minimize the total sum of changes.

What's the minimum total sum of changes you need to make all inflation coefficients not more than $ k $ %?

## 说明/提示

In the first test case, you can, for example, increase $ p_0 $ by $ 50 $ and $ p_1 $ by $ 49 $ and get array $ [20150, 50, 202, 202] $ . Then you get the next inflation coefficients:

1. $ \frac{50}{20150} \le \frac{1}{100} $ ;
2. $ \frac{202}{20150 + 50} \le \frac{1}{100} $ ;
3. $ \frac{202}{20200 + 202} \le \frac{1}{100} $ ;

In the second test case, you don't need to modify array $ p $ , since the inflation coefficients are already good:

1. $ \frac{1}{1} \le \frac{100}{100} $ ;
2. $ \frac{1}{1 + 1} \le \frac{100}{100} $ ;

## 样例 #1

### 输入

```
2
4 1
20100 1 202 202
3 100
1 1 1```

### 输出

```
99
0```

# 题解

## 作者：henrytb (赞：3)

如题目中所述，$p_i$ 对应的 inflation coefficients 的值是 $\frac{p_i}{p_0+p_1+\ldots +p_{i-1}}$。

我们可以先做个前缀和。

可以发现，如果说有个 inflation coefficients 不满足 $\le k\%$ 的要求，那么应当将这个 inflation coefficients 的分母增大或者将分子减小。

然而将分子减小的话会影响到后面的分母，使后面修改所需要花费的代价变大。所以我们考虑将分母增大。

可以发现每个 $p_i$ 对应的 inflation coefficients 值的分母中都带有一个 $p_0$。因此将 $p_0$ 增大可以贡献到最多的不满足条件的地方。

因此我们可以扫一遍，然后将所有不满足条件的地方所需修改的 $p_0$ 的值取 $\max$ 即可。需要预处理前缀和。

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int _,n,k;
int p[105];
int sum[105];
signed main() {
    for(scanf("%lld",&_);_;--_) {
        scanf("%lld%lld",&n,&k);
        rep(i,1,n) {
            scanf("%lld",&p[i]);
            sum[i]=sum[i-1]+p[i];
        }
        int ned=0;
        per(i,n,2) {
            if(p[i]*100>sum[i-1]*k) ned=max(ned,(p[i]*100-sum[i-1]*k+k-1)/k);
        }
        printf("%lld\n",ned);
    }
    return 0;
}
```

---

## 作者：_shine_ (赞：0)

题目主要就是一个式子，即 $\frac{p_i}{p_0+p_1+p_2+\dots+p_{i-1}}$。

在不满足条件的情况下，显然需要减小分子或加大分母，但是无论是改动除 $p_0$ 外的哪一个势必会牵扯到另一次所谓的“通货膨胀率”的计算（即改动了 $p_i$，但是 $p_i$ 也会在其他计算中作为分母进行计算），所以显而易见只能改动 $p_0$。

改动 $p_0$ 方法较为简单，只需要二分最终的值即可。

---

## 作者：云浅知处 (赞：0)

[珂能更好的阅读体验](https://yunqian-qwq.github.io/post/solution-CF1476-ABD/ "欢迎光临！QAQ" )

----------------

### Description

[题目 Link](https://codeforces.com/contest/1476/problem/B)

> - 给 $n$ 个数 $p_1,p_2,\cdots,p_{n}$ 和一个数 $k$
> - 你可以把任意的 $p_i$ 加上任意**正整数** $x$
> - 操作完之后必须满足 $\forall i=2,3,\cdots,n,$ 有 $\dfrac{p_i}{p_1+p_2+\cdots+p_{i-1}}\le\dfrac{k}{100}$
> - 要求求出最小的给这些数加上的值的总和。
> - $2\le n\le 100,1\le k\le 100$
> - $t$ 组数据，$1\le t\le 10^4$

-------------------

### Solution

珂以二分，也可以贪心qwq

这里讲一下贪心的做法w

首先很好想到的是维护一下前缀和 $S_i=\sum\limits_{j=1}^ip_i$，那么此时就是要求 $\dfrac{p_i}{S_{i-1}}\le\dfrac{k}{100}$。

（为了避免精度问题和一堆奇奇怪怪的问题，我们在这里把它化简成 $100p_i\le k\cdot S_{i-1}$。）

然后我们从前往后扫一遍整个序列 $p$，如果发现有不满足条件的，容易发现此时给第一个数加上尽可能大的值是一个很好的方案。

其实感性证明/理解一下就是：若 $\exists p_i,100p_i> k\cdot S_{i-1}$，那我们必须把 $S_{i-1}$ 变得更大一些，也就是把前 $i-1$ 个数增大。

然后如果增大的不是第一个的话，如果我们增大了 $p_a$，很有可能我们增大的那个 $p_a$ 又会太大以至于 $100p_a> k\cdot S_{a-1}$，不满足要求=\_=

而综合来看，只有我们增大 $p_1$ 之后，才绝对不会产生任何负面影响qwq。

严格的证明根据这个思路基本也能证，这里就说一下思路吧w。

那所以我们每次发现一个不满足要求的 $p_i$，直接改第一个即可。

需要增加的值也不难算，就是 $\left\lceil\dfrac{100p_i}{k}\right\rceil-S_{i-1}$。

然后这里我还闲着没事维护了一个树状数组来单点修改查询前缀和，吃了点罚时（草云浅为啥这么菜脑子还这么抽啊）

Code：

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>

#define int long long
#define MAXN 105

using namespace std;

int t;
int n,k;
int a[MAXN];
int s[MAXN];

bool cmp(int a,int b,int kqwq){
    return kqwq*a>=100*b;
}

struct BIT{

    int c[MAXN<<2];

    inline int lowbit(int x){
        return x&(-x);
    }

    inline void PreFix(){
        memset(c,0,sizeof(c));
    }

    inline void modify(int x,int k){
        for(int i=x;i<=n;i+=lowbit(i)){
            c[i]+=k;
        }
    }

    inline int query(int x){
        int ans=0;
        for(int i=x;i;i-=lowbit(i)){
            ans+=c[i];
        }
        return ans;
    }

};

BIT tree;

int ceill(int a,int b){
    if(a%b==0){
        return a/b;
    }
    else return (int)(a/b)+1;
}

signed main(void){

    scanf("%lld",&t);
    while(t--){
        tree.PreFix();
        int ansqwq=0;
        scanf("%lld%lld",&n,&k);
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
            tree.modify(i,a[i]);
        }
        for(int i=2;i<=n;i++){
            int sum=tree.query(i-1);
            if(!cmp(sum,a[i],k)){
                tree.modify(1,ceill(100*a[i],k)-sum);
                ansqwq+=ceill(100*a[i],k)-sum;
            }
        }
        printf("%lld\n",ansqwq);
    }

    return 0;
}
```

---

## 作者：Иɔlɔ (赞：0)

> 给你一个 $n$ 个数的数列 $p$，可以将 $p_i$ 增加任意正整数，使得序列满足对于任何 $i\,(2 \leq i \leq n)$，都有 $\dfrac{p_i}{p_1 + \ldots + p_{i-1}} \leq k\%$。问需要增加的值最小是多少。

首先明确，对于 $i\,(2 \leq i \leq n)$，如果不满足要求，需要增加的只有 $p_1 \sim p_{i-1}$。此时增加 $p_1$ 一定是最优的。如果增加的是 $p_j\,(2 \leq j \leq i-1)$，会使 $j$ 这个位置再次不满足要求从而需要增加更多的值。可以理解为，$p_1$ 不会在分子上出现，不会为不满足要求做贡献。

最后，记得开 $\text{long long}$。

$\text{Code}$：

```cpp
#define W(M) while(M--)

int w[105];
ll mx, pre[105];
 
int main() {
	int T; cin >> T;
	W(T) {
		memset(pre, 0, sizeof pre);
		mx = 0;
		int n, k; qread(n, k);
		QreadArr(w + 1, w + n + 1); // 读入 w[1]~w[n]
		rep(i, 1, n) pre[i] = pre[i - 1] + w[i];
		rep(i, 2, n) {
			ll need = ceil(100.0 * w[i] / k);
			To_max(mx, need - pre[i - 1]); // mx = max(mx, need - pre[i - 1]);
		}
		printf("%lld\n", mx);
	}
	return 0;
}
```


---

## 作者：Remake_ (赞：0)

首先有一个类似于贪心的东西，即有一个最优解一定是只增大$p_0$。

然后这个东西显然是单调的，二分$\triangle p_0$，求出最小符合条件的的$\triangle p_0$即可。

做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define inf 0x7fffffff
#define timeused() (double)clock()/CLOCKS_PER_SEC
#define rep(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define repp(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define debug() assert(0)
typedef long long ll;
typedef unsigned long long ull;
template<typename T> inline T rd(T& x){
   T f=1;x=0;char c=getchar();
   for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
   for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(T)(c-'0');
   x*=f;
   return x;
}
ll t,n,k,a[200005],qzh[200005];
bool check(ll mid){
   qzh[1]=a[1]+mid;
   rep(i,2,n) qzh[i]=qzh[i-1]+a[i];
   rep(i,2,n) if(100*a[i]>k*qzh[i-1]) return 0;
   return 1;
}
int main(){
   rd(t);
   while(t--){
      rd(n);
      rd(k);
      rep(i,1,n) rd(a[i]);
      ll l=0,r=100000000000;
      while(r-l>1){
         ll mid=(l+r)/2;
         if(check(mid)) r=mid;
         else l=mid+1;
      }
      check(l)?printf("%lld\n",l):printf("%lld\n",r);
   }
}
```


---

