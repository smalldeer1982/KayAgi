# Write The Contest

## 题目描述

Polycarp，Arkady 的朋友，正在为编程比赛做准备，并决定自己出一场比赛。比赛包含 $n$ 道题目，持续 $T$ 分钟。每道题目由两个正整数 $a_i$ 和 $p_i$ 描述，分别表示其难度和解出该题可获得的分数。

根据 Polycarp 的经验，他的能力值用一个正实数 $s$ 表示，初始时 $s=1.0$。要解第 $i$ 道题，Polycarp 需要花费 $a_i/s$ 分钟。

Polycarp 喜欢追剧，在解每道题之前，他一定会看一集剧。每看一集剧，他的能力会下降 $10\%$，即能力值 $s$ 变为 $0.9s$。每集剧正好需要 $10$ 分钟。当 Polycarp 决定解某道题时，他首先要看一集剧，然后才能连续解题 $a_i/s$ 分钟（此处 $s$ 为当前能力值）。在计算 $a_i/s$ 时，不进行任何取整，仅做整数 $a_i$ 与实数 $s$ 的除法。

此外，Polycarp 还可以进行训练。如果他训练 $t$ 分钟，他的能力值会提升 $C \cdot t$，其中 $C$ 是给定的正实数常数。Polycarp 只能在解第一道题之前（且在看剧之前）进行训练，训练时间 $t$ 可以为任意实数。

Polycarp 想知道，在比赛时间内，他最多能获得多少分？题目可以按任意顺序解答，但训练只能在解第一道题之前进行。

## 说明/提示

在第一个样例中，Polycarp 可以获得 $7$ 分，具体如下：

1. 首先他训练 $4$ 分钟，将能力值提升到 $5$；
2. 然后他选择先解第 $4$ 题：先花 $10$ 分钟看一集剧，能力值降为 $s=5 \times 0.9=4.5$，然后用 $5/s=5/4.5$ 分钟解题，约为 $1.111$ 分钟；
3. 最后他解第 $2$ 题：再花 $10$ 分钟看一集剧，能力值降为 $s=4.5 \times 0.9=4.05$，然后用 $20/s=20/4.05$ 分钟解题，约为 $4.938$ 分钟。

这样，Polycarp 总共用时约 $4+10+1.111+10+4.938=30.049$ 分钟，获得 $7$ 分。在 $31$ 分钟内无法获得更高分数。

在第二个样例中，Polycarp 可以获得 $20$ 分，具体如下：

1. 首先他训练 $4$ 分钟，将能力值提升到 $5$；
2. 然后他选择先解第 $1$ 题：先花 $10$ 分钟看一集剧，能力值降为 $s=5 \times 0.9=4.5$，然后用 $1/s=1/4.5$ 分钟解题，约为 $0.222$ 分钟；
3. 最后他解第 $2$ 题：再花 $10$ 分钟看一集剧，能力值降为 $s=4.5 \times 0.9=4.05$，然后用 $10/s=10/4.05$ 分钟解题，约为 $2.469$ 分钟。

这样，Polycarp 总共用时约 $4+10+0.222+10+2.469=26.691$ 分钟，获得 $20$ 分。在 $30$ 分钟内无法获得更高分数。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
4
1.000 31.000
12 3
20 6
30 1
5 1
3
1.000 30.000
1 10
10 10
20 8
```

### 输出

```
7
20
```

# 题解

## 作者：NATO (赞：5)

~~小学~~初中数学题。

### 思路浅析：

首先我们感觉到不知道训练后的效率这道题是不好下手的。

那么我们先考虑如果我们知道训练后的效率（为 $C\cdot t+1$），如何做它呢？

考虑 DP。

考虑到当我们确定了做哪些题时我们先做难度系数大的必然是优于先做难度系数小的的，因为在效率降低之后难度系数大的所需要付出的额外时间是比难度系数小的更多的，所以我们先按难度系数从大到小排序。

考虑到知识水平可以是一个小数，故用它来设计状态是不好做的，于是我们换一个角度想，得 $i$ 分是合法的就是能够在规定时间内完成分数和为 $i$ 的题，于是我们可以确定转移方程的一维是得到分数，考虑到做的题的数目会对效率产生影响，那么转移方程还需要的一维就是做了的题数，而维护的信息就是做这些题所需的最小时间。

考虑如何转移。

设 $dp_{i,j}$ 表示做了 $j$ 道题，获得了 $i$ 分所用的最小时间，易得转移如下：

$$dp_{i,j}=\min\limits_{k=j}^{n}dp_{i-p_k,j-1}+\frac{a_k}{0.9^j(C\cdot t+1)}+10$$

意义显然，不做阐述。

可以在 $O(\sum\limits_i p_in^2)$ 内处理出所有情况。

但是这是在知道 $C\cdot t+1$ 的情况下的解法，但是我们不知道，该怎么办呢？

注意到每个 $a_k$ 都会除以一个 $C\cdot t+1$，不妨将 $C\cdot t+1$ 和常数 $10$ 移除出转移过程中，那么对于现在的 $dp_{i,j}$，做题所用的时间即为 $\frac{dp_{i,j}}{C\cdot t+1}+10j$。

现在我们就可以在不知道 $s$ 的情况下处理出所有 $dp_{i,j}$ 了。

考虑写出对于 $dp_{i,j}$ 什么情况下 $C\cdot t+1$ 合法：

$$\frac{dp_{i,j}}{C\cdot t+1}+10j\le T-t$$

注意到 $C\cdot t+1>0$，两边同乘 $C\cdot t+1$ 得：

$$dp_{i,j}+10j(C\cdot t+1)\le(T-t)(C\cdot t+1)$$

注意到式子中只有 $t$ 是未知的，故将它作为主元整理得：

$$Ct^2-(C(T-10j)-1)t+(10j+dp_{i,j}-T)\le 0$$

考虑 $f(t)=Ct^2-(C(T-10j)-1)t+(10j+dp_{i,j}-T)$ 的函数图像。由于 $C>0$，所以图像开口向上，所以 $\le0$ 的部分存在仅当方程 $Ct^2-(C(T-10j)-1)t+(10j+dp_{i,j}-T)=0$ 有解，且我们要求 $0\le t\le T$，所以若有解，则求根公式解出两个解（记为 $C1,C2$ 且 $C1\le C2$），判断区间 $[0,T]$ 和 $[C1,C2]$ 是否有交即可，有交即合法。

时间复杂度即 $O(\sum\limits_i p_in^2)$。

#### 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double 
#define INF 214748364719260817ll
using namespace std;
const db eps=0.0001;
ll tc;
ll n;
db c,t;
db dp[1005][105],use[105];
ll sum=0; 
struct px
{
	ll a,p;
	bool operator<(const px&b)const
	{
		return a>b.a;
	}
}a[105];
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>tc;
	use[0]=1.00;
	for(ll i=1;i<=100;++i)use[i]=use[i-1]/0.900;
	while(tc--)
	{
		cin>>n;
		cin>>c>>t;
		sum=0;
		for(ll i=1;i<=n;++i)cin>>a[i].a>>a[i].p,sum+=a[i].p;
		sort(a+1,a+1+n);
		for(ll i=0;i<=n;++i)
			for(ll j=0;j<=sum;++j)
			dp[j][i]=INF;
		dp[0][0]=0;
		for(ll i=1;i<=n;++i)
		for(ll j=i;j>=1;--j)
			for(ll k=a[i].p;k<=sum;++k)
				{
					dp[k][j]=min(dp[k][j],dp[k-a[i].p][j-1]+a[i].a*1.00*use[j]);
				}
		ll res=0;
		for(ll i=1;i<=sum;++i)
			for(ll j=1;j<=n;++j)
			{
				if(dp[i][j]==INF)continue;
				db yc=c;
				db b=-(1.00*(t-j*10.00)-1.00/yc);
				db c=(j*10.00+dp[i][j]-t)/yc; 
				if(b*b-4.00*c>=0)
				{
					db g=sqrt(b*b-4.00*c);
					db c1=(-b+g)/2.00,c2=(-b-g)/2.00;
					if((0<=c1&&c1<=t)||(0<=c2&&c2<=t))
					{
						res=i;break;
					}
				}
			}
		cout<<res<<'\n';
	}
}
```

---

## 作者：λᴉʍ (赞：2)

> 题意：
Polycarp要打一场比赛。
这场比赛共持续$T$的时间，包含$n$道题，第$i$题有一个难度系数$a_i$​和分数$p_i$​。
Polycarp有一个知识水平$s$，初始值为$1$。做一道题的时间为$a_i/s$，做完这题可以得到该题的分数$p_i$​。
在开始做题之前，Polycarp可以训练任意分钟，如果训练了$t$分钟，则$s$会增加$C\cdot t$。**在做每一道题之前**，Polycarp会看一集吸氧羊，花费$10$分钟的时间，而且看完之后知识水平$s$会变成$0.9s$。
Polycarp想知道他在限定的时间内最多可以得到多少分。
保证了如果将$T$增加或减少$0.001$，不会改变答案。


其实这题就是开始的训练不好想。

首先可以发现，做的题越多知识水平越低，所以做题应该按照$a_i$从大往小做。

可以这么想，初始知识水平是$1$，不训练，做了$k$道题难度系数为$a_1,\cdots,a_k$的话，需要的时间是$10k+\sum_{i=1}^kc^ia_i$，其中$c$是常数，值为$\frac{10}{9}$，对应的是知识水平的下降

如果开始训练$t$单位时间的话，需要的时间是$10k+\frac{\sum_{i=1}^kc^ia_i}{1+C\cdot t}+t$

这里面只有训练时间$t$是变量，这是一个形如$f(x)=\frac{a}{1+bx}+x$的单峰函数。

所以如果确定了一套做题方案的话，训练时间就确定了。

怎么计算答案呢？枚举$k$和$\sum_{i=1}^kp_i$的值，用dp算出最小的$\sum_{i=1}^kc^ia_i$。然后三分一遍就可以知道需要的时间，如果$<T$就计入答案。

```cpp
#include<bits/stdc++.h>
#define il inline
#define vd void
typedef long long ll;
il int gi(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return x*f;
}
struct prob{int a,p;}s[101];
il bool operator<(const prob&a,const prob&b){return a.a>b.a;}
double f[101][1010];
double p1[101];
int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    p1[0]=1;for(int i=1;i<101;++i)p1[i]=p1[i-1]*10/9;
    int tc=gi();
    double l,r,lmid,rmid,lans,rans;
    while(tc--){
        int n=gi();
        double C,T;scanf("%lf%lf",&C,&T);
        for(int i=1;i<=n;++i)s[i].a=gi(),s[i].p=gi();
        std::sort(s+1,s+n+1);
        for(int i=0;i<101;++i)
            for(int j=0;j<1010;++j)
                f[i][j]=1e18;
        f[0][0]=0;
        for(int i=1;i<=n;++i)
            for(int j=i;j;--j)
                for(int k=s[i].p;k<=10*i;++k)
                    f[j][k]=std::min(f[j][k],f[j-1][k-s[i].p]+s[i].a*p1[j]);
        int ans=0;
        for(int i=1;i<=n;++i)
            for(int j=ans+1;j<=10*i;++j){
                l=0,r=T;
                while(r-l>1e-5){
                    lmid=l+(r-l)/3;
                    rmid=lmid+(r-l)/3;
                    lans=lmid+f[i][j]/(1+C*lmid);
                    rans=rmid+f[i][j]/(1+C*rmid);
                    if(lans<rans)r=rmid;
                    else l=lmid;
                }
                l=(l+r)*0.5;
                if(l+f[i][j]/(1+C*l)+10*i<T)ans=j;
            }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

