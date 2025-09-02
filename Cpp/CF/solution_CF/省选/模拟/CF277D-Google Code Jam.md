# Google Code Jam

## 题目描述

Many of you must be familiar with the Google Code Jam round rules. Let us remind you of some key moments that are crucial to solving this problem. During the round, the participants are suggested to solve several problems, each divided into two subproblems: an easy one with small limits (Small input), and a hard one with large limits (Large input). You can submit a solution for Large input only after you've solved the Small input for this problem. There are no other restrictions on the order of solving inputs. In particular, the participant can first solve the Small input, then switch to another problem, and then return to the Large input. Solving each input gives the participant some number of points (usually different for each problem). This takes into account only complete solutions that work correctly on all tests of the input. The participant gets the test result of a Small input right after he submits it, but the test result of a Large input are out only after the round's over. In the final results table the participants are sorted by non-increasing of received points. If the points are equal, the participants are sorted by ascending of time penalty. By the Google Code Jam rules the time penalty is the time when the last correct solution was submitted.

Vasya decided to check out a new tactics on another round. As soon as the round begins, the boy quickly read all the problems and accurately evaluated the time it takes to solve them. Specifically, for each one of the $ n $ problems Vasya knows five values:

- Solving the Small input of the $ i $ -th problem gives to the participant $ scoreSmall_{i} $ points, and solving the Large input gives $ scoreLarge_{i} $ more points. That is, the maximum number of points you can get for the $ i $ -th problem equals $ scoreSmall_{i}+scoreLarge_{i} $ .
- Writing the solution for the Small input of the $ i $ -th problem takes exactly $ timeSmall_{i} $ minutes for Vasya. Improving this code and turning it into the solution of the Large input takes another $ timeLarge_{i} $ minutes.
- Vasya's had much practice, so he solves all Small inputs from the first attempt. But it's not so easy with the Large input: there is the $ probFail_{i} $ probability that the solution to the Large input will turn out to be wrong at the end of the round. Please keep in mind that these solutions do not affect the participants' points and the time penalty.

A round lasts for $ t $ minutes. The time for reading problems and submitting solutions can be considered to equal zero. Vasya is allowed to submit a solution exactly at the moment when the round ends.

Vasya wants to choose a set of inputs and the order of their solution so as to make the expectation of the total received points maximum possible. If there are multiple ways to do this, he needs to minimize the expectation of the time penalty. Help Vasya to cope with this problem.

## 说明/提示

In the first sample one of the optimal orders of solving problems is:

1. The Small input of the third problem.
2. The Small input of the first problem.
3. The Large input of the third problem.
4. The Large input of the first problem.

Note that if you solve the Small input of the second problem instead of two inputs of the third one, then total score expectation will be the same but the time penalty expectation will be worse ( $ 38 $ ).

## 样例 #1

### 输入

```
3 40
10 20 15 4 0.5
4 100 21 1 0.99
1 4 1 1 0.25
```

### 输出

```
24.0 18.875
```

## 样例 #2

### 输入

```
1 1
100000000 200000000 1 1 0
```

### 输出

```
100000000 1
```

# 题解

## 作者：xixiup (赞：6)

### 康康思路

我们首先思考现实中的比赛开题顺序，~~教练告诉我们要先写暴力，再想正解~~。仔细思考后我们发现，如果我们把所有的暴力部分放在前面，正解放在后面，那么我们的正解有一定概率会打挂，就可以有概率减少罚时，同时期望得分是一样的，这样就可以得到一个更优解。

那么我们考虑如何取舍每一道题，经过简单的思考之后我们发现这可以用 $01$ 背包求解。

我们设总用时为 $j$ 时期望最大得分为 $dp_j$，期望罚时为 $g_j$。

这时候我们就可以将一个题目拆成两部分，一个部分为只拿暴力分，另一个部分为尝试拿正解分。在跑 $01$ 背包时我们就可以同时更新两个部分。

那么如何保证不会重复呢？(~~然而你并不能把暴力分拿两次~~) 。这时候我们同时更新两个值的好处就显现出来了。考虑在 $j$ 时间时，假设这一道题的暴力时间为 $t1$，正解时间为 $t2$ (此时保证 $j\leqslant\!t1\!+\!t2$) ，此时你的两个更新来源分别为 $j\!-\!t1$ 和 $j\!-\left(t1\!+\!t2\right)$ 。但是这两个值都没有被更新过，所以这样更新是正确的。

但是我们的正解的排列顺序是什么呢？我们先不考虑这个问题，我们可以先考虑转移的方程式。

我们仍然假设 $t1$ 为暴力时间，$t2$ 为正解时间，$s1$ 为暴力分，$s2$ 为正解分，$p$ 为写出来正解的概率。

对于我们只打暴力时，我们设当前的时间为 $j$，那么我们转移的方程就为：
$$
\begin{cases}dp\!=\!dp_{j-t1}\!+\!s1\\g\!=\!g_{j-t1}\!+\!t1\end{cases}
$$
这样应该很好理解，但是要注意 $g\!=\!g_{j-t1}\!+\!t1$ 而不是 $j$，因为我们要把暴力放在前面，后面的正解的时间期望我们需要保留。

那么对于我们打正解时，我们的转移方程为：
$$
\begin{cases}dp=dp_{j-t1-t2}\!+\!s1\!+\!\left(s2*p\right)\\g=\left(g_{j-t1-t2}\!+\!t1\right)\!\times\!\left(1\!-\!p\right)\!+\!j\!\times\!p\end{cases}
$$
这个也不难理解，需要注意的是，这里的 $g$ 分了两个部分，一个部分是正解打炸了，于是罚时就是 $\left(g_{j-t1-t2}\!+\!t1\right)\!\times\!\left(1\!-\!p\right)$，另一个部分为正解打出来了，罚时就是 $j\!\times\!p$。

那么再回来考虑之前的问题：如何使开正解的顺序最优。

我们考虑设两个正解分别为 $i$ 和 $j$，并且假设它们被排在了最后面。

首先考虑当 $i$ 在 $j$ 前的贡献，这分成了三个部分，一个部分是 $j$ 打对了，罚时就为 $i$ 与 $j$ 的总耗时，而 $j$ 错了 $i$ 对了，则罚时为 $i$ 的耗时，但是如果 $i$ 和 $j$ 都没作对 (~~超可怜的~~) ，那么这两道题就没有贡献罚时，这个部分在等一会列式子时会被忽略。

此时我们可以列出式子：$p_j\!\times\!\left(t2_i\!+\!t2_j\right)\!+\!\left(1\!-\!p_j\right)p_i\!\times\!t2_i$。

$j$ 在 $i$ 前时的式子也是相似的，这里就不列出来了。

那么思考哪一个在前罚时会小一些呢？假设 $i$ 在前 $j$ 在后罚时小一些，那么就可以列出式子：
$$
p_j\!\times\!\left(t2_i\!+\!t2_j\right)\!+\!\left(1\!-\!p_j\right)p_i\!\times\!t2_i<p_i\!\times\!\left(t2_i\!+\!t2_j\right)\!+\!\left(1\!-\!p_i\right)p_j\!\times\!t2_j
$$
经过几步推理即可得到：
$$
\left(1\!-\!p_j\right)p_i\!\times\!t2_j<\left(1\!-\!p_i\right)p_j\!\times\!t2_i
$$
那么我们就可以知道，当 $i$ 与 $j$ 满足 $\dfrac{\left(1\!-\!p_j\right)t2_j}{p_j}<\dfrac{\left(1\!-\!p_i\right)t2_i}{p_i}$ 时，$j$ 在后面更优。此时按照这个式子排一个序就好了。

最后不要忘了，在比较时，若 $dp$ 更小则直接更新，否则 $dp$ 相等时 $g$ 取最小值。

### 代码时间

```cpp
#include<bits/stdc++.h>
using namespace std;
#define db long double//需要开long double，不然会被卡精度
const db eps=1e-8;
const int maxn=1010,maxt=1600;
struct node{
	int s1,s2,t1,t2;db p;//各部分意义与前文一致
	bool operator <(node u)const{//前文的排序
		return 1.*t2/p*((db)1-p)-1.*u.t2/u.p*((db)1-u.p)<=eps;
	}
}a[maxn];
int n,t,s,b;
db dp[maxt],g[maxt];
bool eql(db x,db y){//返回1表示x=y
	return fabs(x-y)<=eps;
}
bool les(db x,db y){//返回1表示x<y
	return !eql(x,y)&&x<y;
}
db Min(db x,db y){
	return les(x,y)?x:y;
}
int main(){
	cin>>n>>t;
	for(int i=1;i<=n;i++){
		int s1,s2,t1,t2;double p;
		scanf("%d%d%d%d%lf",&s1,&s2,&t1,&t2,&p);
		a[i].s1=s1;a[i].s2=s2;
		a[i].t1=t1;a[i].t2=t2;
		a[i].p=((db)1-p);//输入的p是失败概率，所以要处理一发
	}
	sort(a+1,a+1+n);
	for(int i=1;i<=t;i++){
		dp[i]=g[i]=-1;
	}
	for(int i=1;i<=n;i++){
		for(int j=t;j>=a[i].t1;j--){
			db now=dp[j-a[i].t1]+a[i].s1;
			if(eql(dp[j],now)){
				g[j]=Min(g[j],g[j-a[i].t1]+a[i].t1);
			}
			else if(les(dp[j],now)){
				dp[j]=now;
				g[j]=g[j-a[i].t1]+a[i].t1;
			}
            		if(les(a[i].t1+a[i].t2,j)||eql(a[i].t1+a[i].t2,j)){
				db now=dp[j-a[i].t1-a[i].t2]+a[i].s1+(db)(a[i].s2*a[i].p);
				if(eql(dp[j],now)){
					g[j]=Min(g[j],(g[j-a[i].t1-a[i].t2]+a[i].t1)*((db)1-a[i].p)+j*a[i].p);
				}
				else if(les(dp[j],now)){
					g[j]=(g[j-a[i].t1-a[i].t2]+a[i].t1)*((db)1-a[i].p)+j*a[i].p;
					dp[j]=now;
				}
			}
		}
	}
	db a1=0,a2=0;
	for(int j=1;j<=t;j++){
		if(eql(a1,dp[j])){
			a2=Min(a2,g[j]);
		}
		else if(les(a1,dp[j])){
			a1=dp[j];
			a2=g[j];
		}
	}
	printf("%.10lf %.10lf",(double)a1,(double)a2);
	return 0;
}

```

### 后面的话

这里有一些细节：

- 要开```long double```。

- 输入```long double```时编译器会让你用```%Ld```，但是交上去会挂，所以要转换成```double```再输出。

- ```t1```和```t2```，```s1```和```s2```千万不要记混了，不然调起来会很复杂。

- 题中的```p```和这里的```p```是有区别的。

---

## 作者：He_Ren (赞：2)

一开始想到是类似背包的dp

具体做法是,在背包中枚举每个题的时候,枚举是否选择解决数据大的那个问题

再维护最小期望罚时（代码中用$g[i]$表示）

如果dp值更优，则dp值与g都要更新

如果相等，就选较小的g

注意精度，我用double在第7个点wa了。。。

换long double时要注意输入，在上面卡了好久。。

```cpp
#include<cstdio>
#include<algorithm>
typedef long double db;
const int MAXN = 1e3 + 5;
const int MAXT = 1600 + 5;
const db eps = (db)1e-8;
using namespace std;

inline db min(db x,db y){ return x-y<eps? x: y;}
inline db Fabs(db x){ return x<0? -x: x;}

struct Node
{
	db s[3],t[3],p;
}a[MAXN],ans[MAXN];
inline bool cmp(Node x,Node y){ return x.t[1]/x.p*((db)1-x.p) - y.t[1]/y.p*((db)1-y.p) < eps;}

db f[MAXT],g[MAXT];

db tsum[MAXN];
int main(void)
{
	int n,t;
	scanf("%d%d",&n,&t);
	for(int i=1; i<=n; ++i)
	{
		int as0,as1,at0,at1;
		double p;
		scanf("%d%d%d%d%lf",&as0,&as1, &at0,&at1, &p);
		a[i].s[0]=as0; a[i].s[1]=as1; a[i].t[0]=at0; a[i].t[1]=at1;
		a[i].p = (db)1-p;
		a[i].s[1] *= a[i].p;
	}
	sort(a+1,a+n+1,cmp);
	
	for(int i=1; i<=t; ++i) f[i]=g[i]=-1;
	for(int i=1; i<=n; ++i)
	{
		for(int j=t; j>=(int)(a[i].t[0]+eps); --j)
		{
			db t0=a[i].t[0], t1=a[i].t[1];
			
			db now = f[ j-(int)(t0+eps) ] + a[i].s[0];
			if(Fabs(f[j]-now)<=eps)
				g[j] = min(g[j], g[j-(int)(t0+eps)] + t0);
			else if(f[j]-now <= eps)
			{
				g[j] = g[j-(int)(t0+eps)] + t0;
				f[j] = now;
			}
			
			if(j >= (int)(t0+t1+eps))
			{
				now = f[ j-(int)(t0+t1+eps) ] + a[i].s[0]+a[i].s[1];
				if(Fabs(f[j]-now)<=eps)
					g[j] = min(g[j], (g[j-(int)(t0+t1+eps)] + t0) * ((db)1-a[i].p) + j * a[i].p);
				else if(f[j]-now <= eps)
				{
					g[j] = (g[j-(int)(t0+t1+eps)] + t0) * ((db)1-a[i].p) + j * a[i].p;
					f[j] = now;
				}
			}
		}
	}
	
	db ansf=0,ansg=0;
	for(int i=1; i<=t; ++i)
	{
		if(Fabs(ansf-f[i]) <= eps)
			ansg = min(ansg,g[i]);
		else if(ansf-f[i] <= eps)
		{
			ansf=f[i];
			ansg=g[i];
		}
	}
	
	printf("%.10f %.10f",(double)ansf,(double)ansg);
	return 0;
}
```


---

