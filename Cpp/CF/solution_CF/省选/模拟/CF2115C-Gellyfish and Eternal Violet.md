# Gellyfish and Eternal Violet

## 题目描述

There are $ n $ monsters, numbered from $ 1 $ to $ n $ , in front of Gellyfish. The HP of the $ i $ -th monster is $ h_i $ .

Gellyfish doesn't want to kill them, but she wants to keep these monsters from being a threat to her. So she wants to reduce the HP of all the monsters to exactly $ 1 $ .

Now, Gellyfish, with The Sword Sharpened with Tears, is going to attack the monsters for $ m $ rounds. For each round:

1. The Sword Sharpened with Tears shines with a probability of $ p $ .
2. Gellyfish can choose whether to attack: 
  - If Gellyfish doesn't attack, nothing happens.
  - If Gellyfish chooses to attack and The Sword Sharpened with Tears shines, the HP of all the monsters will be reduced by $ 1 $ .
  - If Gellyfish chooses to attack and The Sword Sharpened with Tears does not shine, Gellyfish can choose one of the monsters and reduce its HP by $ 1 $ .

Please note that before Gellyfish decides whether or not to attack, she will know whether the sword shines or not. Also, when the sword shines, Gellyfish can only make attacks on all the monsters and cannot make an attack on only one monster.

Now, Gellyfish wants to know what the probability is that she will reach her goal if she makes choices optimally during the battle.

## 说明/提示

In the first test case, Gellyfish will always attack whether the sword shines or not in the first round.

If the sword shines in the first round, then Gellyfish can reach her goal after the attack in the first round.

Otherwise, if the sword does not shine in the first round, she will attack monster $ 1 $ in the first round. For the second round:

- If the sword shines, since monster $ 1 $ was attacked in the first round, Gellyfish can't reach her goal.
- Otherwise, Gellyfish can attack monster $ 2 $ , allowing her to reach her goal.

Therefore, the probability that Gellyfish can reach her goal is $ 10\% + (90\% \cdot 90\%) = 91\% $ .

In the second test case, Gellyfish will only attack in the first round where the sword shines. It can be observed that the only way Gellyfish can't reach her goal is if the sword never shines in all $ 5 $ rounds. The probability that Gellyfish can reach her goal is $ 100\% - (80\%)^5 = 67.232\% $ .

## 样例 #1

### 输入

```
4
2 2 10
2 2
5 5 20
2 2 2 2 2
6 20 50
1 1 4 5 1 4
9 50 33
9 9 8 2 4 4 3 5 3```

### 输出

```
0.910000
0.672320
0.588099
0.931474```

# 题解

## 作者：E_firework (赞：6)

**upd on 6-13** 修改了一处公式错误。

### 简要题意

有一个长度为 $n$ 的正整数序列 $a$。每次操作的过程如下：

+ 生成一个有 $p$ 的概率为 $1$，$1-p$ 的概率为 $0$ 的随机变量 $x$。

+ 如果 $x=1$，你可以让序列 $a$ 中所有的元素减少 $1$，或者什么都不做。

+ 如果 $x=0$，你可以让序列 $a$ 中的一个指定元素减少 $1$，或者什么都不做。

求出在最优策略下，能在 $m$ 次操作内把序列 $a$ 中的每个元素都变为 $1$ 的概率。

### 解法

先分析一下最优的策略应该是什么样的。

+ 如果 $x=1$，那么只要序列中的最小值不为 $1$ 都应该操作。

+ 如果 $x=0$ 且序列中有至少两种元素，那么我们可以选择一个不为最小值的元素减小，直接选择最小值是不优的。

+ 如果 $x=0$ 且序列中所有元素都相同，那么操作或不操作都有可能成为最优解，无法直接说明。也许应该用 DP 去找最优的策略？

尽管无法直接确定最优策略，但我们可以发现，一个状态的答案只与最小值和元素和有关。于是我们可以设计这样的 DP 状态：

令 $dp_{i,x,s}$ 表示还有 $i$ 次操作次数，序列最小值为 $x$，元素和为 $s+nx$ 时，能够达成目标的概率最大是多少，那么转移和边界条件如下：

$$
dp_{i,x,s}=
\begin{cases}
1 & (i\ge0\land s=0\land x=1)\\
p\times dp_{i-1,x-1,0}+(1-p)\times \max(dp_{i-1,x-1,n-1},dp_{i-1,x,0}) & (i>0\land x>1\land s=0)\\
p\times dp_{i-1,x-1,s}+(1-p)\times dp_{i-1,x,s-1} & (i>0\land s>0)\\
0 & \text{Otherwise}
\end{cases}\\
$$

这个 DP 的时间复杂度为 $O(nmV^2)$（$V$ 表示值域），不足以通过本题，我们需要找到一个方法优化这个 DP。

发现在操作的过程中，$s$ 在第一次变为 $0$ 之后他的取值都不会超过 $n-1$，而从初始状态到 $s$ 第一次变为 $0$ 时这一段操作的最优策略是确定的。我们可以凭此优化 DP。考虑枚举 $s$ 第一次变为 $0$ 是在哪次操作，假设是第 $i$ 次，那么这种情况下最后能达成目标的概率是
 $(1-p)^s\times p^{i-s}\times\binom{i-1}{s-1}\times dp_{m-i,\max(x-(i-s),1)),0}$。这样 DP 的第三维的大小就降到了 $n$，可以通过本题。但是还有一个问题，组合数太大了直接预处理会丢精度，于是把组合数和概率的幂次放在一起递推计算。令 $f_{i,j}$ 表示做了 $i$ 次操作后 $s$ 的值为 $j$，且过程中 $s$ 没有变成过 $0$ 的概率，这是容易计算的。最后的答案就是 $\sum_{i=s}^mf_{i,0}\times dp_{m-i,max(x-(i-s)),1}$。时间复杂度为 $O(nmV)$。

[#322598211](https://codeforces.com/contest/2115/submission/322598211)

---

## 作者：Unnamed114514 (赞：1)

首先容易想到单点操作只会操作最大值，但是第二种操作还跟最小值有关。

注意到**如果没有空操作，那么我们可以通过和反推最大最小值**。因此第一个 dp 只需要记录和和当前操作次数就行了。

考虑在哪些情况会产生空操作：

- 当所有值都相同时，可能会为了一个 AOE 而去跳过单点修改。但是注意到可能会根据剩下的操作总数而执行单点操作，因此第二个 dp 只需要记录最大值数目，最大值和当前操作次数。

- 最小值为 $1$ 时，AOE 一定是空操作，显然概率只跟和和剩下的操作次数相关，因此定义第三个 dp 记录剩余需要单点减的次数和当前操作次数。

时间复杂度 $O(nmh)$，注意常数；代码 1999ms，不保证能通过。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
int T,n,m,h[405],cnt[405];
double p,f[4005][8005],g[25][405][4005],dp[4005][8005];
bool visf[4005][8005],visg[25][405][4005],visdp[4005][8005];
double solve(int c,int mx,int now){
	if(mx==1) return 1;
	if(now==m+1) return 0;
	if(visg[c][mx][now]) return g[c][mx][now];
	visg[c][mx][now]=1,g[c][mx][now]=(mx-(c!=n)==1?solve(c,mx,now+1):solve(c,mx-1,now+1))*p+(c==1?solve(n,mx-1,now+1):solve(c-1,mx,now+1))*(1-p);
	if(c==n) g[c][mx][now]=max(g[c][mx][now],solve(c,mx,now+1)*(1-p)+solve(c,mx-1,now+1)*p);
	return g[c][mx][now];
}
double get(int rest,int now){
	if(!rest) return 1;
	if(now==m+1) return 0;
	if(visdp[now][rest]) return dp[now][rest];
	visdp[now][rest]=1,dp[now][rest]=0;
	return dp[now][rest]=get(rest-1,now+1)*(1-p)+get(rest,now+1)*p;
}
double dfs(int c,int mx,int now,int k,int mi,int sum){
	if(mx==1) return 1;
	if(now==m+1) return 0;
	if(visf[now][sum]) return f[now][sum];
	visf[now][sum]=1;
	if(mi==1) return f[now][sum]=get(sum-n,now);
	if(c==n) return f[now][sum]=solve(n,mx,now);
	f[now][sum]=dfs(c,mx-1,now+1,k+1,mi-1,sum-n)*p;
	if(c==1) f[now][sum]+=dfs(cnt[mx-1+k],mx-1,now+1,k,min(mi,mx-1),sum-1)*(1-p);
	else f[now][sum]+=dfs(c-1,mx,now+1,k,min(mi,mx-1),sum-1)*(1-p);
	return f[now][sum];
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m>>p;
		p/=100;
		int s=0;
		for(int i=1;i<=n;++i) memset(visg[i],0,sizeof(visg[i]));
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=n;++i) cin>>h[i],++cnt[h[i]],s+=h[i];
		for(int i=1;i<=m;++i) for(int j=1;j<=s;++j) visf[i][j]=visdp[i][j]=0;
		sort(h+1,h+n+1);
		for(int i=400;i;--i) cnt[i]+=cnt[i+1];
		if(n==1){
			if(h[1]-m>1) cout<<0<<endl;
			else cout<<1<<endl;
			continue;
		}
		cout<<fixed<<setprecision(10)<<dfs(cnt[h[n]],h[n],1,0,h[1],s)<<endl;
	}
	return 0;
}
```

---

## 作者：CreutzWilknare (赞：0)

教大家一个技巧。

组合数太大了会丢精度，其他题解都是直接递推求解组合数的，但是如果这样做了的话常数会飞起来教你做人。

题目要求函数 $g(n,m)=\frac{n!}{m!(n-m)!}p^n(1-p)^m$，可以直接预处理所有的 $\ln(i!)$，然后算的时候直接写成：$\exp(\ln(n!)-\ln(m!)-\ln((n-m)!)+n\ln p+m\ln(1-p))$。

这样子也不会掉精度，也可以正常的计算了。不过如果 $n$ 和 $p$ 都是零，或者 $m$ 是零 $p$ 是一的情况就会爆掉，开头特判两个 $p$ 的极值即可。

好像忘记讲题了。

这场我迟到了，然后读题五分钟秒了，结果一看半个小时过了零个，当时我场外随便看题的看没人过以为自己假了就没写，结果赛后一看确实是对的。

考虑如果把这题改成交互我会怎么做？如果最小值非 $1$ 并且亮了我必定会砍一刀，然后呢如果所有数都不相同并且泪剑没亮，我必定砍最大的那个数一刀。

那万一所有数都相同并且泪剑没亮呢？那我就得权衡一下是我自认倒霉操作次数减一胜率高，还是直接莽一发胜率高。

然后 dp 状态就出来了，假如当前我还需要砍 $m$ 刀使所有数字相同，并且最小的数字是 $v$，还有 $a$ 次操作次数，状态就是胜率。

然后发现莽一刀之后 $m$ 必定是 $n-1$，因此只有最开始的那一段 $m$ 会超过 $n$，所以组合数一下，直到 $m$ 为零，然后算出所有所有可能的亮的次数的概率。

其实状态还可以砍掉 $m$ 这一个维度，然后直接去更低的地方转移即可，可以带来一些常数上的优势，不过因为这题完全不卡常，所以我没写。

[提交记录](https://codeforces.com/contest/2115/submission/326388819)

这题真不卡常吗？卡了吗卡了吗？到底卡不卡常？

---

## 作者：lfxxx (赞：0)

有点难的过分了。

好歹是自己想出来了，虽然想了很久很久。

考虑假若知道了每轮抽奖的结果怎么决策是否攻击以达到目标。

我们声称：

1. 如果当前所有人血量均大于等于 $2$，那么全体减 $1$ 抽到了必须用。

很简单，你不用了如果是为了留到后面再全体减 $1$ 不如现在就用，如果是为了留到后面使用单体减 $1$ 就更没意义了。

2. 如果要使用单体减 $1$，一定是给血量最高的人用。

这个显然，因为你不希望血量最低的人血量为 $1$，这样全体减 $1$ 就直接失效了。

3. 如果当前所有人血量并不全部相同并且血量最小的人的血量不小于初始状态血量最小的人的血量，那么你抽到了则一定会使用单体减 $1$。

这是因为，你最后总得要抹平一开始大家之间的血量差距，因此这种情况下的单体减 $1$ 一定是可以视作用来抹平差距的，所以能用则用。

分析到这里，我们就可以 dp 了，并且应当把 dp 过程分成两个阶段：

当所有人血量相等之前，我们的策略是能在不让最小血量到 $0$ 的前提下所有操作能用就用，单体减 $1$ 用到血量最大的人身上。

这个部分可以设计状态 $f_{i,j}$ 表示从初始状态到已经进行了 $i$ 次单体操作与 $j$ 次有效的群体操作的状态的概率。

那总操作次数怎么办。

这里实际上是我们刻意地利用了**有效群体操作次数不超过 $\max a_i$ 的性质**，因为注意到当人的血量到 $1$ 的时候，后面所有群体操作都会失效。

所以 $f_{i,j}$ 满足确定了 $i,j$ 时就确定了总操作次数与**目前的血量序列**，并且我们只让其转移到出现了血量为 $1$ 的人的时刻，在这后面的 $m-(i+j)$ 次操作中，只有单体操作是有效的，所以问题是求 $1 \leq k \leq m$ 个 $1-p$ 的概率为 $1$，$p$ 的概率为 $0$ 的随机变量和大于等于 $1 \leq l \leq k$ 的期望。

这个暴力做是 $m^2$ 的，咋办？

考虑充分发扬人类智慧，$k$ 次操作的期望得分是 $k \times (1-p)$，不难想到离这个值比较远的位置 dp 数组的值可以直接忽略掉，于是设置阈值 $B$，每次只进行 $[k \times (1-p) -B,k \times (1-p) + B]$ 内 dp 数组的转移，时间复杂度降低到 $O(m \times B)$。

当所有人血量都相等之后，似乎策略都失效了，但是此时情形变得简单，即确定了血量和可以直接确定出血量序列（每个人都是等价的），于是直接设 $T_i$ 表示从血量和为 $i$ 的状态出发，进行合理决策后成功的**最大**概率，也就是通过倒过来转移实现不同概率下的选取最优策略的过程，这个部分的 dp 容易做到 $O(n \times m \times \max a_i)$。

总时间复杂度 $(\sum n \times m \times \max a_i + t \times m \times B)$，特判 $n$ 全部是 $1$ 的逆天情况后可以通过。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 4e3+114;
const int warma = 400;
double dp[maxn][maxn],suf[maxn][maxn];
int n,m,p;
double P;
int h[maxn];
double f[maxn][maxn];
double V[maxn][maxn];
double T[8003],nT[8003];
double solve(int x,int y){
    if(x<0) return 0;
    if(x>m) return 0;
    if(y>min(m,(int)(x*(1-P))+warma)) return 0;
    if(x==0) return dp[x][y];
    if(y<=0) return 1;
    if(y<max(0,(int)(x*(1-P))-warma)) return suf[x][max(0,(int)(x*(1-P))-warma)];
    return suf[x][y];
}
void work(){
    cin>>n>>m>>p;
    if(n==1){
        cin>>h[1];
        cout<<(m>=h[1]?1:0)<<"\n";
        return ;
    }
    P=p*1.0/100;
    int miv=1e9;
    for(int i=1;i<=n;i++) cin>>h[i],miv=min(miv,h[i]);
    dp[0][0]=1;
    for(int i=1;i<=m;i++){
        for(int j=max(0,(int)(i*(1-P))-warma);j<=min(m,(int)(i*(1-P))+warma);j++){
            dp[i][j]=dp[i-1][j]*P;
            if(j>0) dp[i][j]+=dp[i-1][j-1]*(1-P);
        }
        for(int j=min(m,(int)(i*(1-P))+warma);j>=max(0,(int)(i*(1-P))-warma);j--){
            suf[i][j]=suf[i][j+1]+dp[i][j];
        }
    }
    //F[s] 从所有人血量均等的状态出发的答案
    f[0][0]=1;
    double ans=0;
    for(int i=0;i<=m;i++){
        int minv=1e9;
        int sum=0;
        int mxv=0;
        for(int j=1;j<=n;j++) minv=min(minv,h[j]),mxv=max(mxv,h[j]),sum+=h[j]-1;
        for(int j=0;j<minv-1&&i+j<=m;j++){
            if(minv==mxv){
                //直接贡献到答案
                V[m-(i+j)][minv-j]+=f[i][j];
                continue;
            }
            //f[i][j] -> f[i][j+1]
            f[i][j+1]=(f[i][j+1]+f[i][j]*P);
            //f[i][j] -> f[i+1][j]
            f[i+1][j]=(f[i+1][j]+f[i][j]*(1-P));
        }
        //f[i][minv-1] 特殊转移，直接贡献到答案
        ans+=f[i][minv-1]*solve(m-(i+minv-1),sum-(minv-1)*n);
        int mx=1;
        for(int j=1;j<=n;j++){
            if(h[j]>h[mx]) mx=j;
        }
        if(h[mx]==1){
            //此时已经全部都变成了 1
            //由于答案已经在 f[i][0] 中统计过了所以不需要再统计
            break;
        }
        h[mx]--;        
    }
    T[n]=1;
    ans+=V[0][1]*T[n];
    for(int i=1;i<=m;i++){
        nT[n]=1;
        for(int j=n+1;j<=n*400;j++){
            if(j<2*n){
                nT[j]=(1-P)*T[j-1]+P*T[j];
            }else{
                nT[j]=P*max(T[j-n],T[j-n])+(1-P)*max(T[j-1],T[j]);
            }         
        }
        for(int j=0;j<=n*400;j++) T[j]=nT[j],nT[j]=0;
        for(int s=0;s<=400;s++) ans+=V[i][s]*T[n*s];
    }
    for(int i=0;i<=8000;i++) T[i]=nT[i]=0;
    for(int i=0;i<=m+1;i++){
        for(int j=0;j<=miv;j++) f[i][j]=0,V[i][j]=0;
    } 
    dp[0][0]=f[0][0]=0;
    for(int i=1;i<=m;i++){
        for(int j=max(0,(int)(i*(1-P))-warma);j<=min(m,(int)(i*(1-P))+warma);j++){
            dp[i][j]=suf[i][j]=0;
        }
    }
    printf("%.6lf\n",ans);
}
int main(){
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
/*
1
5 488 0
28 47 96 23 100
*/
```

---

## 作者：jiazhichen844 (赞：0)

## 题意
有 $n$ 个怪，第 $i$ 个怪血量为 $a_i$，游戏有 $m$ 轮，每一轮你的剑有 $p$ 的概率会发光 ，有 $1-p$ 的概率不会发光。若剑发光了，你可以选择将所有怪血量减一，若剑没发光，你可以选择一个怪，并将其血量减一（可以不选），在 $m$ 轮之后，若所有怪的血量都变为 $1$，则你成功了，你需要最大化成功概率（你可以在每一轮开始前知道这一轮剑会不会发光）。  
$n\le 20,m\le 4000,a_i\le 400$。
## 做法
考虑你的策略是什么样的。  
若某一轮你的剑不发光，且存在两个怪的血量不同，则你一定会打血量最大的那个怪。  
若某一轮剑发光，且存在两个怪的血量不同，且不存在怪的血量是 $1$，则你一定会普遍攻击。  
然后你注意到，令 $k=\sum a_i-n\min a_i$ 为要使所有怪的血量，则普遍攻击不会改变 $k$。  
你又注意到，当一轮后怪的血量都相同，则之后怪的血量极差不超过 $1$，且局面数不超过 $n\min a_i$。

于是我们考虑将局面分为两段进行 dp。  
设 $f_{i,j}$ 为 $i$ 轮，打完如下局面的概率：$n$ 个怪，总共血量 $j+n$（即一共要打 $j$ 次），血量极差 $\le 1$。（容易发现这样的局面是唯一 $1$）。  
转移就枚举是否攻击即可。  
设 $g_{i,j}$ 为 $i$ 轮，有 $j$ 轮剑不发光的概率，转移显然。  
答案统计就枚举所有怪第一次血量全相同的时间 $t$，此时剑不发光**恰好** $k$ 次，概率为 $g_{t-1,k-1}(1-p)$，之后能打赢的概率是 $f_{m-t,\max(\min a_i-1-(t-k),0)}$，乘起来求和即可。  
时间复杂度 $O(m(m+n\min a_i))$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
double f[4005][8005],g[4005][4005];
int n,m;
double p;
int a[405];
void test()
{
	cin>>n>>m>>p;
	p/=100;
	for(int i=1;i<=n;i++)
		cin>>a[i],a[i]--;
	sort(a+1,a+n+1);
	int k=0;
	for(int i=1;i<=n;i++)
		k+=a[i]-a[1];
	for(int i=0;i<=m;i++)
		for(int j=0;j<=a[1]*n;j++)
			f[i][j]=0;
	f[0][0]=1;
	for(int i=1;i<=m;i++)
	{
		f[i][0]=1;
		for(int j=1;j<=a[1]*n;j++)
		{
			f[i][j]=(1-p)*max(f[i-1][j],f[i-1][j-1]);
			if(j>=n)
				f[i][j]+=p*max(f[i-1][j],f[i-1][j-n]);
			else
				f[i][j]+=p*f[i-1][j];
		}
	}
	for(int i=0;i<=m;i++)
		for(int j=0;j<=k;j++)
			g[i][j]=0;
	g[0][0]=1;
	for(int i=1;i<=m;i++)
		for(int j=0;j<=k;j++)
		{
			if(!j)
				g[i][j]=p*g[i-1][j];
			else
				g[i][j]=p*g[i-1][j]+(1-p)*g[i-1][j-1];
		} 
	double ans=0;
	for(int i=k;i<=m;i++)
	{
		double q=0;
		if(!i)
			q=1;
		else
		{
			if(!k)
				q=0;
			else
				q=g[i-1][k-1]*(1-p);
		}
		ans+=q*f[m-i][max(a[1]-(i-k),0)*n];
	}
	cout<<fixed<<setprecision(10)<<ans<<"\n";
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
		test();
}
```

---

