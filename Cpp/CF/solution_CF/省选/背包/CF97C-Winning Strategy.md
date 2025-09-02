# Winning Strategy

## 题目描述

One university has just found out about a sport programming contest called ACM ICPC v2.0. This contest doesn't differ much from the well-known ACM ICPC, for example, the participants are not allowed to take part in the finals more than two times. However, there is one notable difference: the teams in the contest should consist of exactly $ n $ participants.

Having taken part in several ACM ICPC v2.0 finals and having not won any medals, the students and the university governors realized that it's high time they changed something about the preparation process. Specifically, as the first innovation it was decided to change the teams' formation process. Having spent considerable amount of time on studying the statistics of other universities' performance, they managed to receive some interesting information: the dependence between the probability of winning a medal and the number of team members that participated in the finals in the past. More formally, we know $ n+1 $ real numbers $ p_{0}<=p_{1}<=...<=p_{n} $ , where $ p_{i} $ is the probability of getting a medal on the finals if the team has $ i $ participants of previous finals, and other $ n-i $ participants arrived to the finals for the first time.

Despite such useful data, the university governors are unable to determine such team forming tactics that would provide the maximum probability of winning a medal at ACM ICPC v2.0 finals on average (we are supposed to want to provide such result to the far future and we are also supposed to have an endless supply of students). And how about you, can you offer such optimal tactic? At the first stage the university governors want to know the value of maximum average probability.

More formally, suppose that the university sends a team to the $ k $ -th world finals. The team has $ a_{k} $ participants of previous finals ( $ 0<=a_{k}<=n $ ). Since each person can participate in the finals no more than twice, the following condition must be true: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/b04e8ade7d007ad0702101fe8e64b638ac1fbbe2.png). Your task is to choose sequence ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/e2f72adfe680a0617dc36d9bd6fe81357712642f.png) so that the limit $ Ψ $ exists and it's value is maximal:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/cb2ffabcf620f29ef29bcdc17d35b1562b965de1.png)As ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/e2f72adfe680a0617dc36d9bd6fe81357712642f.png) is an infinite sequence, you should only print the maximum value of the $ Ψ $ limit.

## 说明/提示

In the second test, no matter what participants the team contains, it is doomed to be successful.

## 样例 #1

### 输入

```
3
0.115590 0.384031 0.443128 0.562356
```

### 输出

```
0.4286122500
```

## 样例 #2

### 输入

```
3
1 1 1 1
```

### 输出

```
0.9999999999
```

# 题解

## 作者：yzy1 (赞：2)

今天模拟赛正好出了这道题，分享一种考场上写的做法。

考虑每种操作所能增加或减少多少个还能参加一次比赛的人数，我们设第 $i$ 种操作所增加的人数为 $b_i$，则：
$$
b_i=\begin{cases}n&i=1\\b_{i-1}-2 &\text{otherwise}.\end{cases}
$$
分析样例可得，最优策略一定是一个 $b_i>0$ 的 $i$ 操作和一个 $b_j<0$ 的 $j$ 操作不断交替，然后一直循环下去。根据贪心思想，因为数据保证 $p_i<p_j$，我们要让 $j$ 操作尽量的多。我们要让每次循环后的次数为 $1$ 的人数均不变，换句话说，$i$ 操作是为 $j$ 操作「提供」次数为 $1$ 的人数。计算方程
$$
xb_i+yb_j=0,
$$
可得出其中一个解是
$$
\begin{cases}x=-b_j\\y=b_i.\end{cases}
$$
如果按着这个循环不断重复无穷遍，则平均概率为：
$$
\frac{-b_jp_i+b_ip_j}{-b_j+b_i}.
$$
则答案为：
$$
\max_{i\in\{i|b_i>0\}}\max_{j\in\{j|b_j<0\}}\frac{-b_jp_i+b_ip_j}{-b_j+b_i}
$$
另外有一种情况需要特判，就是存在一个 $k$ 使得 $b_k=0$ 的情况，当 $b_k=0$ 时我们可以只选择一种操作不断重复，平均概率为 $p_k$。这种情况下的答案为 $\max\{\text{原答案},p_k\}$。

```cpp
signed main() {
  n = in;
  int nowone = n;
  rep(i, 0, n) {
    lf p;
    cin >> p;
    if (nowone > 0)
      zheng.insert({nowone, p});
    else if (nowone == 0)
      ans = p;
    else
      fu.insert({nowone, p});
    nowone -= 2;
  }
  each(z, zheng) {
    each(f, fu) {
      lf res = (f.gx * z.one + z.gx * (-f.one)) / (z.one - f.one);
      up(ans, res);
    }
  }
  printf("%.12LF\n", ans);
  return 0;
}
```

---

## 作者：Brioche (赞：2)

### [blog](https://www.cnblogs.com/terribleterrible/p/9827558.html)

各种原因今天爆0...QAQ

首要原因就是这道杠了两个多小时的T1.

最开始没有给样例解释,手玩了好久的样例发现怎么也凑不出,后来才知道是无穷的,凑得出才怪了.

其实给了样例解释之后就暗示这题可以二分逼近答案.

由于考试的时候给的题面是:

一些有两滴血的人站在一起,有n种刀,砍一刀可以获得一定的权值,最大化这个权值比上死掉的人.

所以之后都是这样描述的.

此题有三种方法:

### 倍增floyd

关于倍增floyd可以看[幸福路径](https://www.luogu.org/problemnew/show/P4308)
和[CF147B Smile House](https://www.luogu.org/problemnew/show/CF147B)

看到题这个算法就在脑子中间闪过,然而,,,仅仅是闪过而已.

先处理出转移矩阵,$mat[c][i][j]$表示走$2^c$步,剩余i个1滴血随从转移到j个1滴血的随从的最小值.

但如果你每次只砍一排,然后接着再换一批新的再砍一排,以此无限地砍下去,那么状态是无限的.是无限的吗?

考虑缩减状态数.显然当我们的人数在2n以内,都是必须要保留的.超过2n我们可以先砍掉.由于是无穷,所以我们的1滴血的人数可以是负数,因为可以忽略前面几项,前面几次操作可以都是增加1滴血的人数的.

于是直接倍增就好了

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
#define maxn 205
#define ll long long
using namespace std;
int n,cur,pre,m,cnt;
double inf,p[maxn],ans,tim;
struct matrix
{
    double a[maxn][maxn];
    void init(){memset(a,0xc2,sizeof(a));}
    double* operator [] (int x){return a[x];}
    matrix operator * (matrix x)
        {
            matrix y;y.init();
            for(int i=1;i<=m;i++)
                for(int j=1;j<=m;j++)
                    for(int k=1;k<=m;k++)
                        if(a[i][k]!=inf&&x[k][j]!=inf)
                            y[i][j]=max(y[i][j],a[i][k]+x[k][j]);
            return y;
        }
}mat[35],f;
int main()
{
    //freopen("blasphemy.in","r",stdin);
    //freopen("blasphemy.out","w",stdout);
    cin>>n;m=n<<1;
    for(int i=0;i<=n;i++)scanf("%lf",&p[i]);
    for(int i=0;i<=30;i++)mat[i].init();f.init();
    inf=f[0][0];f[0][0]=0;
    for(int i=0;i<=m;i++)//转移矩阵
        for(int j=0;j<=n;j++)
        {
            int k=i+n-j-j;
            if(i-j>=0&&k>=0&&k<=m)mat[0][i][k]=max(mat[0][i][k],p[j]);
        }
    cnt=1;pre=1;
    for(int c=1;cnt<=30;c<<=1,cnt++)
    {
        for(int i=0;i<=m;i++)
            if(f[cur][i]!=inf)
            {
                for(int j=0;j<=m;j++)
                    if(mat[cnt-1][i][j]!=inf)
                        f[pre][j]=max(f[pre][j],f[cur][i]+mat[cnt-1][i][j]);
                f[cur][i]=inf;
            }
        tim+=c;mat[cnt]=mat[cnt-1]*mat[cnt-1];swap(cur,pre);
        for(int i=0;i<=m;i++)ans=max(ans,f[cur][i]/tim);
    }
    printf("%.10lf\n",ans);
    return 0;
}

```
### 分数规划

最后我们是要得到最大的ans使得下面的式子恒成立,ans越小越有可能合法.
$$ans<=\frac{a_0p_0+a_1p_1+a_2p_2+...}{a_0+a_1+a_2+...}\\
a_0(ans-p_0)+a_1(ans-p_1)+...<=0$$

像上面处理转移矩阵一样建图,二分ans,跑出负环说明合法(因为可以在负环上面无限绕),check更大的ans
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
#define maxn 305
#define maxm 500005
#define ll long long
using namespace std;
int n,vis[maxn],o[maxn],cn[maxn],nxt[maxm],head[maxn];
int to[maxm],cnt,m;
double p[maxn],mid,w[maxm],dis[maxn];
const double eps=1e-10;
queue<int> q;
void add(int u,int v,double ww)
{
    nxt[++cnt]=head[u];head[u]=cnt;
    to[cnt]=v;w[cnt]=ww;
}
bool spfa(int s)
{
    dis[s]=0;while(!q.empty())q.pop();
    q.push(s);vis[s]=1;
    while(!q.empty())
    {
        int u=q.front();q.pop();++cn[u];
        vis[u]=1;o[u]=0;if(cn[u]==m)return 1;
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i];
            if(dis[v]>dis[u]+w[i]+mid)
            {
                dis[v]=dis[u]+w[i]+mid;
                if(!o[v])q.push(v),o[v]=1;
            }
        }
    }
    return 0;
}
bool check()
{
    memset(o,0,sizeof(o));
    memset(vis,0,sizeof(vis));
    memset(cn,0,sizeof(cn));
    for(int i=0;i<=m;i++)dis[i]=1e15;
    for(int i=0;i<=m;i++)
        if(!vis[i])if(spfa(i))return 1;
    return 0;
}
int main()
{
    //freopen("blasphemy.in","r",stdin);
    //freopen("blasphemy.out","w",stdout);
    cin>>n;m=n*2;
    for(int i=0;i<=n;i++)scanf("%lf",&p[i]);
    for(int i=0;i<=m;i++)
        for(int j=0;j<=n;j++)
        {
            int k=i+n-j-j;
            if(k>0&&k<=m)add(i,k,-p[j]);
        }
    double l=0,r=1;
    while(r-l>eps)
    {
        mid=(l+r)*0.5;
        if(check())l=mid;
        else r=mid;
    }
    printf("%.10lf\n",l);
    return 0;
}

```
### 结论

每一种p对应一种修改:$p_i$表示增加了场上$n-2i$个1血人数,于是我们要是他们一直循环下去得到一个最优解,其实就是求,每个背包有个重量$n-2i$,价值$p_i$,要求重量和为0.

这个结论其实考场上也yy了,只是觉得肯定是错的于是去想怎么合并多个符号相同的价值.其实完全是不要考虑的,因为一定是一个正数和一个负数是最优的,(不知道证明,感性理解).于是我们只要枚举一个正的,一个负的,直接算他们的$(w[i]p[j]+w[j]p[i])/(w[i]+w[j])$的最大值就可以了.
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
#define maxn 205
#define ll long long
using namespace std;
int n;
double c[maxn],p[maxn],ans;
int main()
{
    //freopen("blasphemy.in","r",stdin);
    //freopen("blasphemy.out","w",stdout);
    cin>>n;
    for(int i=0;i<=n;i++)scanf("%lf",&p[i]);
    for(int i=0;i<=n;i++)c[i]=fabs(n-2*i);
    for(int i=0;i<=(n-1)/2;i++)
        for(int j=(n-1)/2+1;j<=n;j++)
            ans=max(ans,(c[j]*p[i]+c[i]*p[j])/(c[j]+c[i]));
    printf("%.12lf",ans);
    return 0;
}

```




---

## 作者：daniEl_lElE (赞：0)

考虑二分最后的极限值，显然要想取到极限需要最后进入一个循环。

设目前的基准“参加过一次的人数”为 $0$。每次派出一个 $j$ 个新人，$n-j$ 个已参加过的人会让人数变化 $n-2j$。考虑 $dp_i$ 表示目前相对基准参加过一次的人数为 $i$ 时选择方案 $p_x-mid$ 之和的最大值。连边找是否有正环即可。

注意到总会有一种方案使得参加过一次的人数波动不超过 $n$（即，可以选择相对基准人数绝对值变小/符号反号），于是可以只在 $[-n,n]$ 之间 dp。

总复杂度 $O(n^3\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const double eps=1e-10;
double p[205];
double dp[205];
signed main(){
	int n; cin>>n; for(int i=0;i<=2*n;i+=2) cin>>p[i];
	double l=0,r=1;
	while(l<r-eps){
		double mid=(l+r)/2;
		for(int i=0;i<=2*n;i++) dp[i]=-1e18;
		dp[n]=0;
		for(int i=1;i<=n;i++){
			for(int j=0;j<=2*n;j++){
				for(int k=-n;k<=n;k+=2){
					if(j+k>=0&&j+k<=2*n){
						dp[j+k]=max(dp[j+k],dp[j]+p[k+n]-mid);
					}
				}
			}
		}
		if(dp[n]>0) l=mid;
		else r=mid;
	}
	cout<<fixed<<setprecision(10)<<l;
	return 0;
}
```

---

