# [USACO24FEB] Minimum Sum of Maximums P

## 题目描述

Bessie 有一行 $N$（$2\le N\le 300$）块瓷砖，依次具有丑陋度 $a_1,a_2,\ldots,a_N$（$1\le a_i\le 10^6$）。其中 $K$（$0\le K\le \min(N,6)$）块瓷砖卡住了；具体地，索引为 $x_1,\ldots,x_K$（$1\le x_1<x_2<\cdots<x_K\le N$）的瓷砖。

Bessie 想要最小化瓷砖的总丑陋度，其中总丑陋度定义为每对相邻瓷砖的最大丑陋度之和；即 $\sum\limits^{N−1}_{i=1}\max(a_i,a_{i+1})$。她可以任意次执行以下操作：选择两块均未卡住的瓷砖，并交换它们。

求 Bessie 以最优方案执行操作可以达到的最小总丑陋度。 

## 说明/提示

### 样例解释 1

Bessie 可以交换第二块和第三块瓷砖，使得 $a=[1,10,100]$，达到总丑陋度 $\max(1,10)+\max(10,100)=110$。或者，她也可以交换第一块和第二块瓷砖，使得 $a=[100,1,10]$，同样达到总丑陋度 $\max(100,1)+\max(1,10)=110$。

### 样例解释 2

瓷砖的初始总丑陋度为 $\max(1,100)+\max(100,10)=200$。Bessie 只允许交换第一块和第三块瓷砖，这并不能使她能够减少总丑陋度。

### 测试点性质

- 测试点 $5$：$K=0$。
- 测试点 $6-7$：$K=1$。
- 测试点 $8-12$：$N\le 50$。
- 测试点 $13-24$：没有额外限制。

## 样例 #1

### 输入

```
3 0
1 100 10```

### 输出

```
110```

## 样例 #2

### 输入

```
3 1
1 100 10
2```

### 输出

```
200```

## 样例 #3

### 输入

```
4 2
1 3 2 4
2 3```

### 输出

```
9```

## 样例 #4

### 输入

```
3 1
1 100 10
3```

### 输出

```
110```

# 题解

## 作者：Bronya18C (赞：33)

赛时场切了，感觉相当有意思，来补一篇题解。

## 简要题意

给定一个长度为 $n$ 的序列，有 $K$ 个位置被固定住了，剩下的数之间可以随意交换，问最小的 $\sum_{i=1}^{n-1}\max(a_i,a_{i+1})$ 的权值是多少。

$n\le 300,K\le 6$。

## 分析性质

考虑将 $\max(a_i,a_{i+1})$ 拆成 $\dfrac{a_i+a_{i+1}+|a_i-a_{i+1}|}{2}$。

其中 $a_i+a_{i+1}$ 是固定的，意思就是我们要最小化 $|a_i-a_{i+1}|$ 的总和。

对于边界的情况，我们可以往两端塞入一个被固定的充分大的数 $C$，最后再减去这部分的答案即可。

由于原来固定的 $K$ 个位置将原序列分为至多 $K+1$ 段，考虑假如我们已经将数分配进了这 $K$ 段里面，段内如何分配才是最优。

由于段与段之间互不影响，我们考虑对于一段计算贡献。

考虑这一个段左边的数为 $L$，右边的数为 $R$，不失一般性地假设 $L\le R$。

那么我们肯定是将分配进来的数从左到右，从小到大排最优，因为可以通过如下的调整法证明：

1. 假如相邻的三个数 $x,y,z$ 满足 $x\ge y \le z$，那么将其变为 $y,x,z$ 不会更劣。

2. 同理，对于 $x\le y \ge z$ 将其变为 $x,z,y$ 不会更劣。

然后一直调整可以使分配的数有序，然后对于边界，我们已经假设 $L\le R$，那么把小的放左边肯定更优。

设这段数的最小值为 $mi$，最大值为 $ma$，那么这一段的贡献是 $|L-mi|+ma-mi+|R-ma|$。

则最后答案为 

$$\sum_{i=1}^{K+1}|L_i-mi_i|+ma_i-mi_i+|R_i-ma_i|$$

答案只和每一段的最小值 $mi_i$ 和 $ma_i$ 有关。

考虑如何分配 $mi_i$ 和 $ma_i$。

**性质：存在一种最优方案，使得对于任意的数对 $(i,j)$，都满足 $(mi_i,ma_i)$ 和 $(mi_j,ma_i)$ 的关系为相离或者包含。**

证明：

还是考虑调整法，不妨设存在 $(i,j)$ 满足 $mi_i\lt mi_j \lt ma_i \lt ma_j$，则我们可以通过交换第 $i$ 段里最大的数和第 $j$ 段里最小的数，直到 $ma'_i\le mi'_j$，此时 $ma'_i \le ma_i$ 且 $mi'_j\ge mi_i$。

考虑 $ma_i$ 变小对第 $i$ 段贡献的影响，由于第 $i$ 段贡献与 $ma_i$ 有关的只有 $ma_i+|ma_i-R|$，分类讨论可得 $ma_i$ 变小后，这个式子要么不变要么变小。

同理 $mi_i$ 变大，对答案的贡献也要么不变要么变小。

所以这样调整会使得答案不劣。

证毕。

## 做法

从上面的式子我们可以得到一个大概的思路，通过确定每段的边界，然后将剩下的数填进去。

容易发现我们不关系中间的数怎么填的，只需要有一个合法的填数方案即可。

考虑我们从小到大考虑每个数，要么它作为某一段的左边界，要么它填入目前左边界最大的没填满的段（因为根据上面性质可知，左边界最大肯定有边界最小，我们先贪心地满足更紧的限制），此时若将这个段填满了就直接作为这个段右边界。

考虑我们如何实现这个填数过程，考虑区间 dp，设 $f_{l,r,S}$ 满足下标为 $[l,r]$ 的数已经填满集合为 $S$ 的段的最小贡献。

由上面的填数过程可知，我们不会在内部的小段留一些数给外面更大的段。（调整法也可以证明）

因此，设 $len_S$ 表示集合为 $S$ 的段的长度之和，满足 $f_{l,r,S}$ 最小且 $r-l+1$ 最小的 $l,r$ 一定满足 $r-l+1=len_S$。

于是我们只用考虑三种转移，

1. 目前左边/右边的数留给下一个包住它的段，$f_{l,r,S}=\min(f_{l+1,r,S},f_{l,r-1,S})$，这部分转移是 $O(1)$ 的，复杂度等于状态数 $O(2^Kn^2)$。

2. 把两端拼起来，考虑枚举子集，$f_{l,r,S}$ 可以从 $f_{l,l+len_{S'}-1,S'}+f_{r-len_{S-S'}+1,r,S-S'}$ 转移过来，复杂度为 $O(3^{K}n^2)$。

3. 用一个大段包住中间的小段，$f_{l,r,S}$ 可以从 $f_{l+1,r-1,S-\{x\}}+F_x(a_l,a_r)$，其中 $F_x(a_l,a_r)$，表示第 $x$ 段最小值为 $a_l$ 最大值为 $a_r$ 的贡献，这部分由于用大段包住小段的时候一定满足 $r-l+1=len_S$，所以复杂度为 $O(n2^{K}K)$ 的。

最后复杂度为 $O(3^Kn^2)$，瓶颈为第二种转移。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;
int n,k;
int a[305];
int b[305];
int ned[305];
int f[305][305][128];
int sum[128];
int L[305],R[305];
bool pd[305];
vector<int>sb;
int main(){
    scanf("%d%d",&n,&k);
    int ans=0;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),ans+=2*a[i];
    a[0]=1e6;a[n+1]=1e6;ans+=2e6;
    for(int i=2;i<=k+1;i++)scanf("%d",&b[i]),pd[b[i]]=true;
    b[1]=0;b[k+2]=n+1;
    for(int i=1;i<=n;i++)
        if(!pd[i])sb.push_back(a[i]);
    int K=0;
    for(int i=1;i<=k+1;i++){
        if(b[i]==b[i+1]-1){ans+=abs(a[b[i+1]]-a[b[i]]);continue;}
        ned[++K]=b[i+1]-b[i]-1;L[K]=a[b[i]];R[K]=a[b[i+1]];
        if(L[K]>R[K])swap(L[K],R[K]);
    }sb.push_back(-1);
    sort(sb.begin(),sb.end());
    int m=sb.size()-1;
    for(int j=0;j<(1<<K);j++)
        for(int i=1;i<=K;i++)
            if(j&(1<<i-1))sum[j]+=ned[i];
    for(int l=0;l<=m+1;l++)
        for(int r=0;r<=m+1;r++)
            for(int j=0;j<(1<<K);j++)
                f[l][r][j]=(j==0?0:1e9);
    for(int i=1;i<=m;i++){
        for(int l=1;l+i-1<=m;l++){
            int r=l+i-1;
            for(int j=0;j<(1<<K);j++){
                f[l][r][j]=min(f[l+1][r][j],f[l][r-1][j]);
                if(sum[j]>i)continue;
                if(sum[j]==i){
                    for(int x=1;x<=K;x++)
                        if(j&(1<<x-1)){
                            if(ned[x]==1&&i==1)f[l][r][j]=min(f[l][r][j],abs(L[x]-sb[l])+abs(R[x]-sb[l]));
                            else if(ned[x]>1)
                                f[l][r][j]=min(f[l][r][j],f[l+1][r-1][j^(1<<x-1)]+abs(L[x]-sb[l])+abs(R[x]-sb[r])+sb[r]-sb[l]);
                        }
                }
                for(int s=(j-1)&j;s;s=(s-1)&j)
                    f[l][r][j]=min(f[l][r][j],f[l][l+sum[s]-1][s]+f[l+sum[s]][r][j^s]);
                // cerr<<l<<" "<<r<<" "<< j<<" "<<f[l][r][j]<<endl;
            }
        }
    }
    ans+=f[1][m][(1<<K)-1];//cerr<<f[1][m][(1<<K)-1]<<endl;
    ans/=2;ans-=2e6;
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：9)

[Problem Link](https://www.luogu.com.cn/problem/P10197)

**题目大意**

> 给定长度为 $n$ 的序列 $a_1\sim a_n$，给定 $k$ 个位置不能交换，其他位置上的元素可以任意交换，最小化 $\sum\limits_{i=1}^{n-1}\max(a_i,a_{i+1})$。
>
> 数据范围：$n\le 300,k\le 6$。

**思路分析**

从 $k=0$ 的情况开始，注意到 $\max(a_i,a_{i+1})=\dfrac 12(a_i+a_{i+1}+|a_i-a_{i+1}|)$，因此我们只要最小化 $\sum |a_i-a_{i+1}|$，升序或降序排列即可。

回到一般的问题，我们设 $a_0=a_{n+1}=\infty$ 且这两个位置不能交换，那么整个序列就被不能交换的点分成若干个区间 $(l_i,r_i)$，我们只要把可以交换的元素填入这些区间即可。

假设我们在区间 $(l_i,r_i)$ 中填的元素是 $S$，根据刚才的结论，显然 $S$ 升序排列或降序排列最优，如果 $a_{l_i}<a_{r_i}$ 那么升序排列，否则降序排列。

设 $S$ 中元素的最大最小值分别为 $\max_i,\min_i$，那么这一段区间的贡献就是 $|a_{l_i}-\min_i|+|a_{r_i}-\max_i|+\max_i-\min_i$。

注意到关于 $\max_i$ 的贡献为 $|a_{r_i}-\max_i|+\max_i$ 随着 $\max_i$ 变小递减，关于 $\min_i$ 的贡献 $|a_{l_i}-\min_i|-\min_i$ 随着 $\min_i$ 变大递减。

因此可以通过调整法证明每个区间内的值域区间 $[\min_i,\max_i]$ 要么相离要么包含，否则可以把相交区间切成两部分，使得 $\max_i$ 变小 $\min_j$ 变大。

那么就可以考虑在值域上 dp，设可以交换的元素排序后是 $w_1\sim w_m$，那么设 $f_{l,r,S}$ 表示考虑 $S$ 中的区间用 $w_l\sim w_r$ 中的元素填满的最小代价。

根据代价函数的性质进一步分析，我们发现：对于两个值域区间 $[\min_i,\max_i]\subseteq[\min_j,\max_j]$，$[\min_i,\max_i]$ 内部不可能有元素在 $j$ 中，否则交换该元素和 $\min_i$ 即可让 $\min_i$ 变大。

设 $S$ 中的区间大小总和为 $siz_S$，那么我们只要在 $r-l+1=siz_S$ 时考虑向 $S$ 中插入一个区间，否则直接从 $\min(f_{l,r-1,S},f_{l+1,r,S})$。

考虑插入区间的形式：

- 合并两个值域区间，枚举 $T\subset S$ 后从 $f(l,l+siz_T-1,T)+f(l+siz_T,r,S\setminus T)$ 转移。
- 插入一个区间 $x$：
  - 特判 $x$ 大小为 $1$ 的情况，可以钦定这种情况最先考虑，只需要在 $l=r$ 时计算，通过合并操作即可转移。
  - 否则一定插入 $\min_x=w_l,\max_x=w_r$ 的若干个元素，算出其转移代价后从 $f(l+1,r-1,S\setminus\{x\})$ 转移。

时间复杂度 $\mathcal O(n^2(3^k+k2^k))$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int V=1e6+5;
int a[305],L[10],R[10],len[10],sz[1<<7],w[305],id[10],f[305][305][1<<7];
void chkmin(int &x,int y) { x=x<y?x:y; }
signed main() {
	int N,M,n=0,m=0,ans=0;
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;++i) scanf("%d",&a[i]),ans+=2*a[i];
	for(int i=1;i<=M;++i) scanf("%d",&id[i]);
	a[0]=a[N+1]=V,id[0]=0,id[M+1]=N+1,ans+=2*V;
	for(int i=0;i<=M;++i) {
		if(id[i+1]-id[i]==1) ans+=abs(a[id[i]]-a[id[i+1]]);
		else {
			L[m]=id[i],R[m]=id[i+1],len[m]=R[m]-L[m]-1;
			for(int j=L[m]+1;j<=R[m]-1;++j) w[++n]=a[j];
			if(a[L[m]]>a[R[m]]) swap(L[m],R[m]); ++m;
		}
	}
	sort(w+1,w+n+1);
	for(int s=0;s<(1<<m);++s) for(int i=0;i<m;++i) if(s>>i&1) sz[s]+=len[i];
	memset(f,0x3f,sizeof(f));
	for(int i=0;i<=n;++i) f[i+1][i][0]=0;
	for(int d=1;d<=n;++d) for(int l=1,r=d;r<=n;++l,++r) for(int s=0;s<(1<<m);++s) if(sz[s]<=d) {
		f[l][r][s]=min(f[l][r-1][s],f[l+1][r][s]);
		for(int t=(s-1)&s;t;t=(t-1)&s) {
			chkmin(f[l][r][s],f[l][l+sz[t]-1][t]+f[l+sz[t]][r][s^t]);
		}
		if(sz[s]<d) continue;
		for(int j=0;j<m;++j) if(s>>j&1) {
			int z=abs(a[L[j]]-w[l])+abs(a[R[j]]-w[r])+w[r]-w[l];
			if(len[j]==1&&d==1) {
				chkmin(f[l][r][s],z);
			} else if(len[j]>1) {
				chkmin(f[l][r][s],f[l+1][r-1][s^(1<<j)]+z);
			}
		}
	}
	printf("%d\n",(ans+f[1][n][(1<<m)-1])/2-2*V);
	return 0;
}
```

---

## 作者：Purslane (赞：7)

# Solution

昨天讲的题，非常有趣，记录一下。

考虑如果只有 $1$ 和 $n$ 有限制怎么做。不妨假设 $a_1 \le a_n$。

则 $\sum_{i=1}^{n-1} \max\{a_i,a_{i+1}\} = \sum_{i=1}^{n-1} a_i + \max\{0,a_{i+1}-a_i\}$。显然前者是确定的，我们希望让后者最大。

如果我们在坐标轴上描出若干个点 $(x,a_x)$，并且在相邻的点之间连边，那么相当于爬升总高度。有下界 $\max_{i=1}^n a_i - \min_{i=1}^n a_i$，且容易在 $a_2 \le a_3 \le \dots \le a_{n-1}$ 时取到。

原问题中不妨设 $0$ 和 $n+1$ 处都有一个固定的 $+ \infty$，我们相当于给把游离的 $a$ 分给若干个有初值的集合，使得这些集合的极差最小。

注意到不同集合加入数的“值域”（不准确，是最小值和最大值之间的区域）要么相交，要么包含，否则可以调整使得情况更优。因此，可以把游离的数排序后做区间 $\rm DP$。

设 $dp_{l,r,S}$ 为用 $l$ 到 $r$ 中的数，满足 $S$ 中集合要求所需要的最小代价。转移有：

1. $dp_{l,r,S} \leftarrow dp_{l+1,r,S}$ 和 $dp_{l,r,s} \leftarrow dp_{l,r-1,S}$。表示 $l$ 或 $r$ 并不在 $S$ 对应的任何一个集合中；
2. 如果有一个长度为 $1$ 的集合在 $S$ 中，拿走 $l$ 或 $r$ 填充进去；
3. 选取 $S$ 中一个集合，设它的最小值和最大值分别是 $v_l$ 和 $v_r$，用 $dp_{l+1,r-1,S-\{x\}}$ 转移；
4. 设 $l$ 往后极长连续被放入 $S$ 的集合为 $T$，用 $dp_{l,l+sze_T-1,T} + dp_{l+sze_{S - T},S-T}$ 转移。

第四步用了子集枚举，是主要瓶颈。复杂度 $O(n^2 3^k)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=300+10,MAXM=(1<<7)+10;
int n,k,ans,flg[MAXN],a[MAXN],cnt[MAXM],x[MAXN],L[MAXN],R[MAXN],len[MAXN];
int m,v[MAXN],dp[MAXN][MAXN][MAXM];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k,memset(dp,0x3f,sizeof(dp));
	ffor(i,1,n) cin>>a[i];
	a[0]=a[n+1]=1000001;
	ffor(i,1,k) cin>>x[i],flg[x[i]]=1;
	x[k+1]=n+1,k++;
	ffor(i,1,k) L[i]=x[i-1],R[i]=x[i],len[i]=R[i]-L[i]-1;
	ffor(i,1,k) {
		if(len[i]==0) {ans+=max(a[L[i]],a[R[i]]);continue ;}
		if(a[L[i]]<=a[R[i]]) {
			ffor(j,L[i],R[i]-1) ans+=a[j];
		}
		else {
			ffor(j,L[i]+1,R[i]) ans+=a[j];
			swap(L[i],R[i]);
		}
	}
	ffor(i,1,n) if(!flg[i]) v[++m]=a[i];
	sort(v+1,v+m+1);
	ffor(i,0,(1<<k)-1) ffor(j,1,k) if(i&(1<<j-1)) cnt[i]+=len[j];
	ffor(l,1,m) ffor(r,1,m) dp[l][r][0]=0;
	ffor(s,1,(1<<k)-1) ffor(Len,cnt[s],m) for(int l=1,r=Len;r<=m;l++,r++) {
		dp[l][r][s]=min(dp[l+1][r][s],dp[l][r-1][s]);
		ffor(j,1,k) if(len[j]==1&&(s&(1<<j-1))) {
			dp[l][r][s]=min(dp[l][r][s],dp[l+1][r][s-(1<<j-1)]+max(a[R[j]],v[l])-min(a[L[j]],v[l]));
			dp[l][r][s]=min(dp[l][r][s],dp[l][r-1][s-(1<<j-1)]+max(a[R[j]],v[r])-min(a[L[j]],v[r]));
		}
		for(int S=s&(s-1);S!=0;S=s&(S-1)) dp[l][r][s]=min(dp[l][r][s],dp[l][l+cnt[S]-1][S]+dp[l+cnt[S]][r][s-S]);
		if(l!=r) ffor(j,1,k) if(len[j]!=1&&(s&(1<<j-1))) dp[l][r][s]=min(dp[l][r][s],max(a[R[j]],v[r])-min(a[L[j]],v[l])+dp[l+1][r-1][s-(1<<j-1)]);
	}
	int st=0;
	ffor(i,1,k) if(len[i]) st+=(1<<i-1);
	cout<<ans+dp[1][m][st]-a[0]*2;
	return 0;
}
```

---

## 作者：konyakest (赞：2)

### 转化

称固定的两个位置之间为一段。特别的，我们固定 $a_0=a_{n+1}=inf$，则起始和结束都有段。

考虑一段内 $\sum_{i=1}^{n−1}\max⁡(a_i,a_{i+1})$ 是什么。

发现这个东西在 $a$ 没有峰的时候是最小的，有峰的时候峰会被算两次从而不优。

仔细想想，发现峰最多只有 $1$ 个（如果不是 $1$ 个，调整即可）。

不妨令左端固定的那个位置的数最小，设为 $L$，设右端的为 $R$。

设中间这些数最大值为 $mx$，最小值为 $mn$。

考虑答案，除了每个数固定的贡献，最大值（峰）会额外贡献一次，为 $\max(R,mx)$，最小值会被少算 $\max(0,mn-L)$。

于是每个段的贡献为 $\sum a_i+\max(R,mx)+\max(0,mn-L)$，改写成  $\sum a_i+R+\max(0,mx-R)+\max(0,mn-L)$ 的形式更优美一些。

转化为最小化 $\max(0,mx-R)+\max(0,mn-L)$。于是，只要保证每一段填的数的个数正确，我们就只需要考虑每一段填的 $\min$ 和 $\max$ 是什么。这和题目中段数较小的条件正好契合！

### sol

考虑在值域序列上 dp，发现好像不是很能做。

想一想我们是不是少用了什么条件。

发现，对于最优的 $(mn,mx)$ 二元组，它们在值域序列上是不交的。证明手模一下就行。

于是，这个形式就是经典的区间 dp 了。

设 $dp_{l,r,S}$ 表示 $l,r$ 区间，对应的 $(mn,mx)$ 对 $S$ 被分配到 $S$ 这个集合对应的段。转移是简单的。

### 总结

主要是对于题目所给的条件的转化。其他题解有将 $\max$ 化为绝对值的，这并不是必须的，只要仔细分析最优结构也可得到对应结论。

---

## 作者：_Cheems (赞：0)

题意：给序列 $a$，有 $k$ 个位置固定，其它可任意交换，最小化 $\sum \max(a_i,a_{i+1})$。$n\le 300,k\le 6$。

首先，对 $\max$ 进行讨论非常不友好，可以拆成绝对值的形式。

$$\sum\max(a_i,a_i+1)=\sum\frac{a_i+a_{i+1}+|a_i-a_{i+1}|}2$$

可以在两端设两个极大值，以规避对边界的讨论。那么现在每个 $a_i$ 恰贡献两次，只考虑最小化 $\sum |a_i-a_{i+1}|$。

序列被固定元素划分为若干段，对于一段，假设已确定元素集合，考虑如何排列。记左右端固定元素为 $L_i,R_i$，有结论：

* 记 $L_i\le R_i$，则元素从左到右从小到大排列最优。

很符合人类知觉，证明也不难调整法即可。大概就是假如序列中间出现非法情况那么显然调整更优，假如是两端出现非法情况，简单分讨发现不会更劣。

那么该段价值 $val(i)$ 只和最大最小元素有关：$val(i)=|L_i-mi|+|R_i-ma|+ma-mi$。

然后你看了看数据范围，感觉非常像是区间 dp 再套个状压。那么自然想到能不能证明集合只会不交和包含？确实是可以的。

先确立一个认知：对于一个段，假如最大值变小或最小值变大那么不劣，分讨即可。那么对于两个相交段 $X,Y$，设 $ma_X>mi_Y$，那么一定可以交换 $ma_X,mi_Y$，显然不劣。

开始愉快的 dp。对序列排序，记 $f_{l,r,S}$ 表示考虑区间 $[l,r]$ 已经填完 $S$ 集合的段的最小代价。不过比较麻烦的是会不会留一些元素不选、而留给后面的段呢？其实不会，因为你考虑满足这个条件的两个段，那么显然是可以调整使得大段的最值不变、而小段边界缩短的。

所以呢留的元素只可能放在序列两边。转移分三类讨论：边界留元素、套一个大段、两边拼起来。非常容易就不说了。

复杂度 $O(n^23^k+nk2^k)$。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MIN(a, b) a = min(a, b)
#define myz(x) ((x) < 0 ? -(x) : (x))
const int N = 3e2 + 5, K = 7, inf = 2e6;
int _n, n, _m, m, _a[N], a[N], x[K + 5], f[N][N][1 << K], ans, Len[1 << K];
struct node{int l, r, len;} b[K];

inline int Val(int i, int mi, int ma) {return myz(b[i].l - mi) + myz(b[i].r - ma) + ma - mi;}
signed main(){
	cin >> _n >> _m, ++_m;
	x[_m] = _n + 1, _a[0] = _a[_n + 1] = inf; 
	for(int i = 1; i <= _n; ++i) scanf("%lld", &_a[i]), ans += _a[i] * 2;
	for(int i = 1; i < _m; ++i) scanf("%lld", &x[i]);
	for(int i = 0; i < _m; ++i){
		node qwq = {_a[x[i]], _a[x[i + 1]], x[i + 1] - x[i] - 1}; 
		if(qwq.l > qwq.r) swap(qwq.l, qwq.r);
		if(!qwq.len) ans += qwq.r - qwq.l;
		else b[m++] = qwq;
	}
	for(int i = 0; i < _m; ++i)
		for(int j = x[i] + 1; j < x[i + 1]; ++j) a[++n] = _a[j];
	sort(a + 1, a + 1 + n);
	memset(f, 0x3f, sizeof f);
	for(int i = 1; i <= n + 1; ++i) f[i][i - 1][0] = 0;
	for(int i = 0; i < 1 << m; ++i)
		for(int j = 0; j < m; ++j) 
			if((i >> j) & 1) Len[i] += b[j].len;
	for(int len = 1; len <= n; ++len)
		for(int l = 1; l + len - 1 <= n; ++l){
			int r = l + len - 1;
			for(int S = 0; S < 1 << m; ++S){
				if(Len[S] > len) continue;
				MIN(f[l][r][S], min(f[l + 1][r][S], f[l][r - 1][S]));
				if(len == Len[S]){
					for(int i = 0; i < m; ++i)
						if((S >> i) & 1){
							if(b[i].len > 1) MIN(f[l][r][S], f[l + 1][r - 1][S ^ (1 << i)] + Val(i, a[l], a[r]));
							else if(len == 1) MIN(f[l][r][S], Val(i, a[l], a[r]));
						}
				}
				for(int S2 = S; S2; S2 = (S2 - 1) & S)
					MIN(f[l][r][S], f[l][l + Len[S2] - 1][S2] + f[l + Len[S2]][r][S ^ S2]);
			}
		}
	cout << (ans + f[1][n][(1 << m) - 1]) / 2 - inf;
    return 0;
}
```

---

