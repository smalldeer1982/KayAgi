# Omkar and Landslide

## 题目描述

Omkar is standing at the foot of Celeste mountain. The summit is $ n $ meters away from him, and he can see all of the mountains up to the summit, so for all $ 1 \leq j \leq n $ he knows that the height of the mountain at the point $ j $ meters away from himself is $ h_j $ meters. It turns out that for all $ j $ satisfying $ 1 \leq j \leq n - 1 $ , $ h_j < h_{j + 1} $ (meaning that heights are strictly increasing).

Suddenly, a landslide occurs! While the landslide is occurring, the following occurs: every minute, if $ h_j + 2 \leq h_{j +       1} $ , then one square meter of dirt will slide from position $ j       + 1 $ to position $ j $ , so that $ h_{j + 1} $ is decreased by $ 1 $ and $ h_j $ is increased by $ 1 $ . These changes occur simultaneously, so for example, if $ h_j + 2 \leq h_{j +       1} $ and $ h_{j + 1} + 2 \leq h_{j + 2} $ for some $ j $ , then $ h_j $ will be increased by $ 1 $ , $ h_{j + 2} $ will be decreased by $ 1 $ , and $ h_{j + 1} $ will be both increased and decreased by $ 1 $ , meaning that in effect $ h_{j       + 1} $ is unchanged during that minute.

The landslide ends when there is no $ j $ such that $ h_j + 2       \leq h_{j + 1} $ . Help Omkar figure out what the values of $ h_1, \dots, h_n $ will be after the landslide ends. It can be proven that under the given constraints, the landslide will always end in finitely many minutes.

Note that because of the large amount of input, it is recommended that your code uses fast IO.

## 说明/提示

Initially, the mountain has heights $ 2, 6, 7, 8 $ .

In the first minute, we have $ 2 + 2 \leq 6 $ , so $ 2 $ increases to $ 3 $ and $ 6 $ decreases to $ 5 $ , leaving $ 3, 5, 7, 8 $ .

In the second minute, we have $ 3 + 2 \leq 5 $ and $ 5 + 2       \leq 7 $ , so $ 3 $ increases to $ 4 $ , $ 5 $ is unchanged, and $ 7 $ decreases to $ 6 $ , leaving $ 4, 5, 6, 8 $ .

In the third minute, we have $ 6 + 2 \leq 8 $ , so $ 6 $ increases to $ 7 $ and $ 8 $ decreases to $ 7 $ , leaving $ 4, 5, 7, 7 $ .

In the fourth minute, we have $ 5 + 2 \leq 7 $ , so $ 5 $ increases to $ 6 $ and $ 7 $ decreases to $ 6 $ , leaving $ 4, 6, 6, 7 $ .

In the fifth minute, we have $ 4 + 2 \leq 6 $ , so $ 4 $ increases to $ 5 $ and $ 6 $ decreases to $ 5 $ , leaving $ 5, 5, 6, 7 $ .

In the sixth minute, nothing else can change so the landslide stops and our answer is $ 5, 5, 6, 7 $ .

## 样例 #1

### 输入

```
4
2 6 7 8```

### 输出

```
5 5 6 7```

# 题解

## 作者：RiverHamster (赞：8)

结论题。

首先，最后的位置和操作的顺序没有关系。

显然最后 $h_{i+1}-h_i \in \{0, 1\}$。暴力算一些答案，可以发现最后的差分序列中最多有 $1$ 个 $0$。

**结论**：最后的序列中满足 $h_i = h_{i+1}$ 的 $i$ 数量不超过 $1$。

**证明**：

> 考虑从点 $i$ 开始向左依次推进的算法：
>
> - 如果 $i = 1$ 或 $h_i - h_{i - 1} < 2$，结束；
> - 否则令 $h_i \leftarrow h_i - 1, \;h_{i-1} \leftarrow h_{i-1}+1, \;i \leftarrow i-1$，回到第一步递归执行。
>
> 执行一次推进后，如果 $i$ 左边的数互不相等，那么会一直推进到 $1$，这可能使相等对数增加 $1$，否则，若 $h_i = h_{i + 1}$，那么推进操作会在 $i+1$ 处结束，使相等对数减少 $1$ 或不变（高度形如 $x, x, x+2$ 等时个数不变）。
>
> 那么依次对 $2, 3, \dots, n$ 执行推进，就容易发现相等对始终不会超过 $1$ 对。（注意开始时没有相等对）

有了这个结论，可以发现 $S = \sum h_i$ 唯一确定了一个最终的高度序列。先假设没有相等对，那么 $\displaystyle \sum h_i = S = \frac{n(2h_1 + n - 1)}{2}$，解出 $h_1$（上取整），再调整其中一个不会增加的位置即可。

[**参考实现**](https://www.cnblogs.com/RiverHamster/p/sol-cf1392f.html)

---

## 作者：Prean (赞：4)

首先题意很明显就不说了吧www
# 先说一下做这道题的经历
昨天下午和 blw 一起去食堂吃饭，和他产生了一点儿冲突，于是我考了一下他 P1119 （就是那道 Floyd），他很快做出来了，于是考了我这道题，并称其为“神仙结论题”

首先我 10min 就搞出了正解，然而 blw 说我 WA 了，我就很谔谔，或许是他搞错了吧qaq

~~并且吐槽一句这题结论不难想啊~~

首先这道题序列单调递增，所以不论怎么操作最后的序列都是单调不降的。

并且，还有一个明显能够得到的结论：

若 $ [a_L+1<a_{L+1}][a_{R-1}+1<a_R][\sum_{i=L+1}^{R-1}[a_i<a_{i+1}] = 1 $，那么可以让 $ a_L $ 加一，$ a_R $ 减一。

证明很简单，略。

于是，我们每次就让最右边能够产生“山体滑坡”（本题的名称，也相当于最右边能够进行操作的数）减尽量多，最左边能够进行“山体滑坡”的数加上这个数。

于是左边的数就会尽量大，右边的数就会尽量小。

再由于题意，能够得到最多只有两个相邻的项相等。

于是我们就得出了以下算法：

先算出最所有项的和，然后算出 $ a_1 $，由结论得：$ a_i = a_{i-1}+1 $。

这时用最开始所有项的和减去现在所有项的和，还会剩下 $ O(n) $ 的值。

从左往右一个一个填即可。

code：
```cpp
#include<cstdio>
#include<cctype>
typedef long long ll;
const int M=1e6+5;
int n;
ll sum,ans,a[M];
inline ll read(){
	ll a=0;char s;
	while(!isdigit(s=getchar()));
	while(a=a*10+(s^48),isdigit(s=getchar()));
	return a;
}
signed main(){
	int i;
	n=read();
	for(i=1;i<=n;++i)a[i]=read(),sum+=a[i];
	sum-=1ll*n*(n+1)>>1;
	ans=sum/n;sum-=ans*n;
	for(i=1;i<=n;++i)a[i]=ans+i;
	i=1;
	while(sum--)++a[i++];
	for(i=1;i<=n;++i)printf("%lld ",a[i]);
}
```

---

## 作者：dead_X (赞：3)

## 题意
给你一个严格递增的数列，定义一次操作为**同时**对于所有 $i<n$ 且 $a_{i+1}-a_i\geq2$ 的 $a_i$ 增加 $1$ ，$a_{i+1}$ 减小 $1$ 。

问你一直操作直到没有任何数能在操作中改变后，最终所有数的大小。
## 思路
* # 警告：这不是正解，建议只在比赛中使用，对您的实力没有任何帮助。


Tag：玄学，找规律，数学

我们先手膜一些数据。

$\{1,3,5,7\}\to\{3,4,4,5\}$

$\{1,2,3,10\}\to\{3,4,4,5\}$

$\{1,4,5,6\}\to\{3,4,4,5\}$

$\{2,3,4,7\}\to\{3,4,4,5\}$

$\{2,3,4,6\}\to\{3,3,4,5\}$

发现了什么？最终的排列只和所有数的**和**有关。

我们再手膜一些数据。

$\sum=16\to\{3,3,4,5\}=\{2+1,3,4,5\}$

$\sum=17\to\{3,4,4,5\}=\{2+1,3+1,4,5\}$

$\sum=18\to\{3,4,5,5\}=\{2+1,3+1,4+1,5\}$

$\sum=19\to\{3,4,5,6\}=\{3,4,5,6\}$

发现了什么？简单的来说，答案开始为 $\{1,2,3,\cdots,n\}$ ，然后在总和不超过 $\sum a_i$ 的前提下依次往每一位增加 $1$。

现在，问题变得很 simple 了：给定 $n$ 和 $a$ ，构造答案，只需要一点点 Math 知识和决心就可以过题了！
## 代码
```

#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
signed main()
{
	int n=read(),sum=0;
	for(int i=1; i<=n; i++) sum+=read();
	int x=(((sum<<1)/n-n+1)>>1),y=sum-((((x<<1)+n-1)*n)>>1);
	for(int i=1; i<=n; i++) if(i<=y) printf("%lld ",i+x); else printf("%lld ",i+x-1); 
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

手玩一下，我们发现最终的情况一定是一个 $L,L+1,L+2,...,R$ 的阶梯中间插入一个与上一级阶梯登高的阶梯，并且每次往后放入一座山时可以视作高度 $R+1$ 以上的山体会向前塌，具体而言这会使得那级与上一级登高的阶梯后移，于是考虑利用周期性快速算下即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e6+114;
int a[maxn],n;
int d,pos,h;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    d=h=a[1];
    for(int i=2;i<=n;i++){
        h++;
        int c=a[i]-h;
        int t=i-1-pos;
        if(c==0) continue;
        if(c<=t){
            if(pos==0) d++;
            pos+=c;
        }else{
            if(pos==0) d++;
            c-=(t+1);
            pos=0;
            h++;
            int f=c/i;
            c%=i;
            d+=f;
            h+=f;
            if(c>0){
                d++;
                pos=c;
            }
        }
        /*
        for(int j=1;j<=c;j++){
            if(pos==0){
                pos=1;
                d++;
            }else if(pos+1<i){
                pos++;
            }else{
                pos=0;
                h++;
            }
        }*/
        //cout<<d<<' '<<h<<' '<<pos<<'\n';
    }
    cout<<d<<" ";
    for(int i=2;i<=n;i++){
        cout<<d+i-1-(pos==0?0:1)*(pos+1<=i?1:0)<<' ';
    }
    return 0;
}
```

---

