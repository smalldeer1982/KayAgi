# [CCC 2024 S5] Chocolate Bar Partition

## 题目描述

Maxwell 有一块巧克力想和他的朋友们分享。巧克力可以看作 $2\times N$ 个小方块组成的，每个小方块的美味度可以表示为 $2 \times N$ 的整数数组 $T_{i,j}$。Maxwell 想把整个巧克力分成若干个连通块，每个连通块的巧克力小方格的平均美味程度都是一样的。Maxwell 想知道根据如上所述，他可以将巧克力棒分成的最大连通块数量是多少。

如果可以通过向上、向下、向左或向右移动的方式访问到每个小方块，则该部分被视为一个连通块。

## 说明/提示


**【样例 1 解释】**

把巧克力分割成 $2$ 块是最优的，一种方案是把右下角的一个小方块作为一个连通块，其余三个小方块作为第二个连通块，如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/2yga1u9u.png)

每一个连通块的平均美味度都为 $5$。

**【样例 2 解释】**

一种获得平均分割巧克力的方案如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/hty1ata8.png)

注意每一块的平均美味度都为 $1$。

**【数据范围】**

**本题采用捆绑测试。**

对于所有数据，保证 $1 \leq N \leq 2 \times 10^5$，$0 \leq T_{i,j} \leq 10^8$。

下面的表格显示了 $15$ 分的分配方案：

| 分值 | $N$ 的范围 | $T_{i,j}$ 的范围 |
| :-: | :-: | :-: |
| $2$ | $N = 2$ | $0 \leq T_{i,j} \leq 5$ |
| $2$ | $1 \leq N \leq 8$ | $0 \leq T_{i,j} \leq 20$ |
| $1$ | $1 \leq N \leq 20$ | $0 \leq T_{i,j} \leq 20$ |
| $2$ | $1 \leq N \leq 100$ | $0 \leq T_{i,j} \leq 20$ |
| $2$ | $1 \leq N \leq 1000$ | $0 \leq T_{i,j} \leq 100$ |
| $3$ | $1 \leq N \leq 2000$ | $0 \leq T_{i,j} \leq 10^5$ |
| $3$ | $1 \leq N \leq 2 \times 10^5$ | $0 \leq T_{i,j} \leq 10^8$ |


## 样例 #1

### 输入

```
2
5 4
6 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
1 0 1 2 0
0 2 0 3 1
```

### 输出

```
5
```

# 题解

## 作者：llingy (赞：8)

## 题目描述

给定一个 $2\times n$ 的网格图，每个格子都有一个权值，你需要将这些格子划分为尽可能多的连通块，使得每一个连通块的格子权值的平均值均相等。这里的联通指的是四联通。

## 分析

首先先将所有格子减去平均值，这样转化为将格子划分为尽可能多的连通块，使得每一块所有格子的和为 $0$。

一个直观的想法是在状态中记录上一列两个格子所在连通块的大小进行 DP，但这是不可接受和不必要的。

如果上一列两个格子所在的连通块不同且两个连通块的权值和都不为 $0$ 的状态是毫无必要的，因为我们完全可以等到至少有一个连通块的权值和为 $0$ 的时候再考虑这种转移。

此时保证在已经考虑完的格子中，至多有一个连通块的权值不为 $0$。此时这个连通块的权值也是不必要记录的，因为其它的连通块的和均为 $0$，则已经考虑完的所有格子的和就是这个连通块的权值。

现在我们把状态精简到 $f_{i,0/1}$，表示已经考虑完了前 $i$ 列的格子，第 $0/1$ 行的格子所在的连通块的和不保证为 $0$。不妨记录 $s_{i,0/1}$ 为第 $0/1$ 行前 $i$ 个格子的和。

当前讨论的是 $f_{i,k}$ 的转移，记 $l=1-k$，即另外一行的编号。

* 让一列两个格子全部划入和不一定为 $0$ 的连通块内，用 $\max\{f_{i-1,0},f_{i-1,1}\}$ 来更新。
* 让在另外一行内末尾若干个格子单独成为一个和为 $0$ 的连通块，用 $\displaystyle\max_{j<i,s_{j,l}=s_{i,l}}\{f_{j,k}+1\}$ 来更新。
* 在另外一行内末尾若干个格子和先前和不一定为 $0$ 的连通块拼起来形成一个和为 $0$ 的连通块，此时会在当前这一行产生一个和不一定为 $0$ 的连通块，用 $\displaystyle\max_{j<i,s_{i,l}+s_{j,k}=0}\{f_{j,l}+1\}$ 来更新。

特殊地，如果 $s_{i,0}+s_{i,1}=0$，则说明此时不保证为 $0$ 的连通块的和为 $0$，需要将 $f_{i,0}$ 和 $f_{i,1}$ 均更新为 $\max\{f_{i,0},f_{i,1}\}+1$。

使用哈希表或者 `std::map` 等维护第二种和第三种转移即可做到 $O(n)$ 或 $O(n\log n)$。

## Code

```cpp
constexpr int N=2e5+5;using ll=unsigned long long;constexpr int inf=1e9;
ll a[N][2],s[N][2];int f[N][2];struct dat{int v;inline dat(){v=-inf;}};
map<ll,dat>mp[4];inline void gmx(dat&x,int y){if(x.v<y) x.v=y;}
inline void work()
{
    ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
    int n;ll sum=0;cin>>n;
    for(int i=0;i<=1;i++) for(int j=1;j<=n;j++) cin>>a[j][i],sum+=a[j][i],a[j][i]*=2*n;
    for(int i=0;i<=1;i++) for(int j=1;j<=n;j++) a[j][i]-=sum;
    for(int i=0;i<=1;i++) for(int j=1;j<=n;j++) s[j][i]=s[j-1][i]+a[j][i];
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=1;j++) gmx(mp[j][s[i-1][j]],f[i-1][j^1]),gmx(mp[j|2][s[i-1][j^1]],f[i-1][j]);
        for(int j=0;j<=1;j++) f[i][j]=max({f[i-1][0],f[i-1][1],mp[j^1][s[i][j^1]].v+1,mp[(j^1)|2][-s[i][j^1]].v+1});
        if(s[i][0]+s[i][1]==0) f[i][0]=f[i][1]=max(f[i][0],f[i][1])+1;
    }
    cout<<f[n][0]<<"\n";
}
```

---

## 作者：C1942huangjiaxu (赞：6)

将所有数减去平均数，变成分成最多的连通块使得每块和为 $0$。

记 $s_{i,j}$ 为第 $i$ 行的前缀和数组, $i\in \{0,1\}$。

考虑如何统计连通块。

+ 对于全都在第 $i$ 行的连通块，$(l_j,r_j]$，有 $s_{i,l_j}=s_{i,r_j}$。
+ 对于跨越 $2$ 行的连通块，考虑每一行最右侧的位置 $r0_j,r1_j$，有 $s_{0,r0_j}+s_{1,r1_j}=0$。

记 $f_{i,j}$ 表示 **$a_{i,j}$ 是已经划分完了的最右侧的位置**的最优答案，其中另一行可能存在跨越 $2$ 行的连通块。

考虑转移。

+ 记 $u$ 为 $\lt j$ 的最大的满足 $s_{i,j}=s_{i,u}$ 的位置，划分一个单行的连通块 $(u,j]$，$f_{i,u}+1 \rightarrow f_{i,j}$。

+ 记 $v$ 为 $\le j$ 的最大的满足 $s_{i,j}+s_{1-i,v}=0$ 的位置，划分一个跨越 $2$ 行的连通块 $j,v$，$f_{1-i,v}+1 \rightarrow f_{i,j}$。

+ 对于任意 $k\lt \max(u,v)$ 的位置，$f_{*,k}+1 \rightarrow f_{i,j}$，这里小于是要保证之前没划分完的位置不被截断，$\max$ 是 $2$ 种划分都行。

时间复杂度 $O(n\log n)$，瓶颈在离散化。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=4e5+5;
int n,m,p[2],hd[2][N],f[2][N],g[N];
ll a[2][N],w,b[N];
int main(){
	scanf("%d",&n);
	for(int i=0;i<2;++i)for(int j=1;j<=n;++j)scanf("%lld",&a[i][j]),w+=a[i][j];
	for(int i=0;i<2;++i)for(int j=1;j<=n;++j)a[i][j]=a[i][j-1]+2ll*n*a[i][j]-w;
	for(int i=0;i<2;++i)for(int j=0;j<=n;++j)b[++m]=a[i][j];
	sort(b+1,b+m+1);
	m=unique(b+1,b+m+1)-b-1;
	memset(hd,-1,sizeof(hd));
	int u=lower_bound(b+1,b+m+1,0)-b;
	hd[0][u]=hd[1][u]=0;
	for(int j=1;j<=n;++j){
		for(int i=0;i<2;++i){
			int o=i^1,i1=lower_bound(b+1,b+m+1,a[i][j])-b,i2=lower_bound(b+1,b+m+1,-a[i][j])-b;
			if(b[i2]!=-a[i][j])i2=0;
			int u1=hd[i][i1],u2=hd[o][i2];
			if(~u2)f[i][j]=max(f[i][j],f[o][u2]+1);
			if(~u1)f[i][j]=max(f[i][j],f[i][u1]+1);
			if(max(u1,u2)>0)f[i][j]=max(f[i][j],g[max(u1,u2)-1]+1);
			hd[i][i1]=j;
		}
		g[j]=max(g[j-1],max(f[0][j],f[1][j]));
	}
	printf("%d\n",g[n]);
	return 0;
}
```

---

## 作者：R_shuffle (赞：3)

由于并不确定具体能分成多少个区间，所以希望的是让平均值为 $0$。这个是非常好处理的，同时在考虑精度问题的情况下不妨把所有数都乘上 $2n$。

现在所有前期的问题都解决了。考虑怎么求最大值。由于只有两行，所以不妨考虑顺着列去 dp。最简单的想法就是直接把每列上下两个各自都存其来，但是显然空间是不够的。不妨考虑划分的具体形式，由于强制选连通块，所以如果出现了上下两个同属一个连通块，那么就只需要考虑这一个连通块即可；同时，从上一个上下两个同属一个连通块的转移到这个上下两个同属一个连通块的，可以用前缀和快速判断转移是否合法。所以实际上有意义的状态只有上下两个格子同属一个连通块的情况。但是发现这实际上有问题，样例就是很好的反例。所以实际上还有一种情况，就是上下两个格子属于两个连通块，且这两个连通块中至少一个已经和为 $0$ 了。所以总结一下，有意义的状态只有上下两个各自所属的连通块的个数不超过 $1$ 个。

那么就有了一个 $n^2$ 的做法，不妨考虑优化。显然从能转移到一个状态的状态是有限的，因为条件是比较苛刻的。所以不妨考虑用 unordered_map 维护条件，这样就可以做到 $O(1)$ 的转移。总时间复杂度为 $O(n)$。

---

## 作者：dyc2022 (赞：1)

[更好的阅读体验](https://www.cnblogs.com/dyc2022/p/19033145)
***
先将所有格子的权值都减去这些格子的平均数。为了方便，我们先将所有格子的权值乘以 $2n$ 保证平均数是整数。问题转化成，将 $2 \times n$ 的网格划分成尽可能多的连通块，使得每一块的权值和为 $0$。

我们可以先考虑一个朴素的 dp：设 $f_{i, j, k}$ 表示只考虑前 $i$ 行，上面的格子所在连通块和为 $j$，下面的格子所在连通块和为 $k$ 的答案。然而状态数是 $O(nV^2)$，$V$ 为值域，没有什么前途。

然而我们发现很多状态是无用的。具体地，我们只关心一个连通块的最后一个格子在哪里，即要从哪里划分连通块。所以由上面的状态设计，一个有用的状态，一定是上面的格子或下面的格子所在连通块的和为 $0$，即 $jk = 0$。更进一步地，由于目前状态下只有一个连通块的权值和不为 $0$，因此我们甚至不需要记录 $j$ 和 $k$，而是直接通过上下两行的前缀和得出答案。

我们设 $f_{0/1, i}$ 表示目前考虑前 $i$ 行，上面或下面的格子所在连通块的权值和不为 $0$。设目前考虑 $f_{j, i}$，令 $k = j \oplus 1$，则转移分三种：

- 将上下的格子都划分到前一列不为 $0$ 的格子所在连通块。则连通块数量不会增加，从 $\max(f_{j, i-1}, f_{k, i-1})$ 转移。
- 将第 $k$ 行末尾的若干个格子形成一个和为 $0$ 的连通块，从 $f_{k, l} + 1$ 转移，其中 $l$ 是一个合法转移点满足 $\sum\limits_{x=l+1}^{i}a_{k, x} = 0$。
- 将第 $k$ 行末尾的若干个格子和前面不为 $0$ 的格子形成一个和为 $0$ 的连通块，从 $f_{k, l} + 1$ 转移，其中 $l$ 是一个合法转移点满足 $\sum\limits_{x=l+1}^{x}a_{k, x} + \sum\limits_{x=1}^{l}a_{k, x} + \sum\limits_{x=1}^{l}a_{j, x} = 0$。
- 该行上下格子所在的格子连通块和都为 $0$，这种条件需满足 $\sum \limits_{x=1}^{i}a_{j, x}+\sum \limits_{x=1}^{i}a_{k, x} = 0$，用 $\max(f_{j, i}, f_{k, i}) + 1$ 转移，表示可以新开一个连通块。

第一和第四个转移直接做就好了。第二、三开一个桶存满足条件的最大 $f_{k, l}$。由于前缀和值域很大，需要离散化。

那么这道题就做完了，复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define N 800006
using namespace std;
inline void chkmax(int &x,int y){x=x<y?y:x;}
int n,bn,sum,b[N],a[2][N],s[2][N],s_[2][N];
int f[2][N],g[4][N];
main()
{
    scanf("%lld",&n);
    for(int i=0;i<2;i++)
        for(int j=1;j<=n;j++)scanf("%lld",&a[i][j]),sum+=a[i][j];
    for(int i=0;i<2;i++)
        for(int j=1;j<=n;j++)a[i][j]=a[i][j]*2*n-sum+a[i][j-1];
    for(int i=0;i<2;i++)
        for(int j=0;j<=n;j++)b[++bn]=a[i][j],b[++bn]=-a[i][j];
    sort(b+1,b+1+bn),bn=unique(b+1,b+1+bn)-b-1;
    for(int i=0;i<2;i++)
        for(int j=0;j<=n;j++)s[i][j]=lower_bound(b+1,b+1+bn,a[i][j])-b;
    for(int i=0;i<2;i++)
        for(int j=0;j<=n;j++)s_[i][j]=lower_bound(b+1,b+1+bn,-a[i][j])-b;
    memset(g,-0x3f,sizeof(g));
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<2;j++)
            chkmax(g[j][s[j][i-1]],f[j^1][i-1]);
        for(int j=0;j<2;j++)
            chkmax(g[j|2][s[j^1][i-1]],f[j][i-1]);
        for(int j=0;j<2;j++)
            chkmax(f[j][i],max(f[0][i-1],f[1][i-1]));
        for(int j=0;j<2;j++)
            chkmax(f[j][i],max(g[j^1][s[j^1][i]],g[(j^1)|2][s_[j^1][i]])+1);
        if(a[0][i]+a[1][i]==0)f[0][i]=f[1][i]=max(f[0][i],f[1][i])+1;
    }
    printf("%lld\n",f[0][n]);
    return 0;
}
```

---

## 作者：dAniel_lele (赞：1)

显然每个连通块的平均值是确定的，考虑计算出来，并化为整数（即，乘 $2n$）。

考虑 $dp_{i,0/1/2}$ 表示 $i$ 列前缀，本列与下一列任意/第一行向外连接/第二行向外连接时，最多分成多少个块。

考虑枚举两行中距离 $i$ 最近的一个结束点，该结束点在第一行/第二行。然后判断一下该行加进去，是否可以得到前缀和之和为 $0$。同时，也可以将两行放开并延伸至下一列。

这样做是 $O(n^2)$ 的，考虑优化。

注意到对于同行的一个连续段，相同前缀和的位置对后面的影响相同。对于一个跨越两行的连续段的最后一小段，另一行前缀和的相反数位相同的位置对后面的影响也相同。故记 $mpa_i$ 表示第一行可以转移到前缀和为 $i$ 位置的 $dp_j$ 的 $\max$，$mpb_i$ 同理。

此时 $dp_{i,1/2}$ 可以省去，借用 $mpa,mpb$ 进行转移即可。$dp_{i,0}$ 以下简写为 $dp_i$。

显然 $dp_i\to dp_{i+1}$，$mpa_{prea_i}+1\to dp_{i+1}$，$mpb_{preb_i}+1\to dp_{i+1}$。

分为以下两种情况转移：

* $prea_i+preb_i=0$ 时：

此时显然会选择上下两列都不与后面连通。故可以将新的 $dp_i$ 赋值为已经进行前序转移的 $dp_i$ 与 $mpa_{prea_i}$ 与 $mpb_{preb_i}$ 的最大值加一。

* $prea_i+preb_i\neq0$ 时：

此时上下两行至少连出去一个。如果说都连出去已经在 $dp_i\to dp_{i+1}$ 中转移了。考虑只连出去一个，不妨以第一行为例。也就是说，$prea_j+preb_i=0$，即 $prea_j=-preb_i$，于是 $dp_i\to mpa_{-preb_i}$。当然，我们也接受刚刚连了一个到 $i$ 列截止的第二行的转移，即 $mpb_{preb_i}+1\to mpa_{-preb_i}$。

同时，还有一种转移以上两种情况同时需要，即，以第一行或第二行第 $i$ 列为开头，连出去一个连续段。对于第一行来说就是 $\max(mpa_{prea_i}+1,dp_i)\to mpa_{prea_i}$。

总复杂度 $O(n\log n)$，可以使用更加快速的哈希表（例如，`gp_hash_table` 期望 $O(1)$）做到 $O(n)$。

```cpp

#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
int a[1000005],b[1000005];
int prea[1000005],preb[1000005];
int dp[1000005];
unordered_map<int,int> mpa,mpb;
unordered_map<int,int> tga,tgb;
signed main(){
	int n,sum=0; cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],sum+=a[i],a[i]*=2*n;
	for(int i=1;i<=n;i++) cin>>b[i],sum+=b[i],b[i]*=2*n;
	for(int i=1;i<=n;i++) a[i]-=sum,prea[i]=prea[i-1]+a[i];
	for(int i=1;i<=n;i++) b[i]-=sum,preb[i]=preb[i-1]+b[i];
	tga[0]=1,tgb[0]=1;
	for(int i=1;i<=n;i++){
		if(tga[prea[i]]) dp[i+1]=max(dp[i+1],mpa[prea[i]]+1);
		if(tgb[preb[i]]) dp[i+1]=max(dp[i+1],mpb[preb[i]]+1);
		dp[i]=max(dp[i],dp[i-1]);
		if(prea[i]+preb[i]==0){
			if(tga[prea[i]]) dp[i]=max(dp[i],mpa[prea[i]]+1);
			if(tgb[preb[i]]) dp[i]=max(dp[i],mpb[preb[i]]+1);
			dp[i]++;
			if(!tga[prea[i]]) tga[prea[i]]=1,mpa[prea[i]]=dp[i];
			else mpa[prea[i]]=max(dp[i],mpa[prea[i]]+1);
			if(!tgb[preb[i]]) tgb[preb[i]]=1,mpb[preb[i]]=dp[i];
			else mpb[preb[i]]=max(dp[i],mpb[preb[i]]+1);
		}
		else{
			if(!tga[-preb[i]]) tga[-preb[i]]=1;
			mpa[-preb[i]]=max(mpa[-preb[i]],dp[i]);
			if(tgb[preb[i]]) mpa[-preb[i]]=max(mpa[-preb[i]],mpb[preb[i]]+1);
			if(!tgb[-prea[i]]) tgb[-prea[i]]=1;
			mpb[-prea[i]]=max(mpb[-prea[i]],dp[i]);
			if(tga[prea[i]]) mpb[-prea[i]]=max(mpb[-prea[i]],mpa[prea[i]]+1);
			if(!tga[prea[i]]) tga[prea[i]]=1,mpa[prea[i]]=dp[i];
			else mpa[prea[i]]=max(dp[i],mpa[prea[i]]+1);
			if(!tgb[preb[i]]) tgb[preb[i]]=1,mpb[preb[i]]=dp[i];
			else mpb[preb[i]]=max(dp[i],mpb[preb[i]]+1);
		}
	}
	cout<<dp[n];
	return 0;
}```

---

## 作者：Albert_Wei (赞：0)

首先先考虑把所有数减去平均值再乘上 $2n$，将条件转化为连通块总和为 $0$。

我们从左往右考虑，将连通块在此格结束的格子称为 `x`，不确定连通块是否延伸的称为 `o`（即我们允许一个本应为 `x` 的格被称作 `o`），则一列共有 `xx`，`xo`，`ox`，`oo` 四种状态。我们考虑对其进行 dp，并在连通块的结束位置计算贡献。设前 $i$ 列以 `xx`，`xo`，`ox`，`oo` 结尾的最多连通块数量分别对应 $f_{i, 0/1/2/3}$。记 $pre_{i, j}$ 为第 $i$ 行前 $j$ 列的和，考虑转移：

1. `oo` 的转移：由于 `oo` 情况没有连通块结束，导致没有贡献产生，故第 $i$ 列结尾为 `oo` 的答案是第 $i - 1$ 列以所有情况结尾的所有 dp 值的 $\max$，即 $f_{i, 3} = \max\{f_{i - 1, 0}, f_{i - 1, 1}, f_{i - 1, 2}, f_{i - 1, 3}\}$。

2. `xx` 的转移：首先可以发现 `xx` 只会在 $pre_{0, i} + pre_{1, i} = 0$ 时出现。此时考虑完该列 `oo`，`ox`，`xo` 的转移后我们发现都可以将原有的分割方式在此处新增一个连通块，故我们有 $f_{i, 0} = \max\{f_{i, 1}, f_{i, 2}, f_{i, 3}\} + 1$。

3. `xo` 的转移：

   ![](https://cdn.luogu.com.cn/upload/image_hosting/ay01faor.png)

   我们考虑找到一个位置 $j$，满足确定了第 $j$ 列的状态我们就能保证新加入的连通块总和为 $0$。我们发现有以下两种条件可保证这一点。

   - 第 $j$ 列由两个在第 $i$ 列前结束的连通块占据（对应第一行和第三行四种情况），要求为 $pre_{0, i} + pre_{1, j} = 0$。
   - 新连通块恰好占据 $(0, j + 1), (0, j + 2), \cdots, (0, i)$，要求为 $pre_{0, i} = pre_{0, j}$。

   我们要找到满足该条件最大的 $j$，以保证第 $j + 1$ 到 $i - 1$ 列间没有贡献产生。在第一种情况中我们要求该连通块必须占据 $(0, j + 1), (0, j + 2), \cdots, (0, i)$ 且不能占据 $(1, j + 1), (1, j + 2), \cdots, (1, i)$，在第两种情况中我们均要求 $(1, j + 1), (1, j + 2), \cdots, (1, i)$ 在同一个连通块中。由于这两个条件，我们容易发现第 $j + 1$ 到第 $i$ 列不会产生贡献。考虑分类讨论：

   - 若两种条件均成立（对应第三行两幅图），则第 $j$ 列状态为 `xx`，故贡献为 $f_{j, 0} + 1$。
   - 若仅有第一个条件成立（对应第一行两幅图），则我们有 $(0,j)$ 在新连通块中，讨论 $(1, j)$ 是否在新连通块中，我们有贡献为 $\max(f_{j, 1}, f_{j, 3}) + 1$。
   - 若仅有第二个条件成立（对应第二行两幅图），则我们有 $(1, j)$ 与 $(1, i)$ 在同一个连通块中。讨论 $(0, j)$ 是否在该连通块中，我们有贡献为 $\max(f_{j, 2}, f_{j, 3}) + 1$。

4. `ox` 的转移：与 `xo` 同理。

我们使用 `map` 或哈希表找到满足 $pre_{j, 0} = pre_{i, 0}$ 和 $pre_{j, 1} = -pre_{i, 0}$ 的 $j$ 的 dp 值的最大值即可完成转移，复杂度为 $\mathcal{O}(n)$ 或 $\mathcal{O}(n \log n)$。

```cpp
  n = read();
  F(i, 0, 1) F(j, 1, n) sum += (a[i][j] = read());
  F(i, 0, 1) F(j, 1, n) a[i][j] = 2 * n * a[i][j] - sum + a[i][j - 1];
  memset(dp, ~0x3f, sizeof dp), dp[0][0] = 0;
  auto get = [&](int x, int y, int z) {
    if (mp[x][y].find(z) != mp[x][y].end()) return mp[x][y][z];
    return -INF;
  };
  mp[0][0][0] = mp[1][0][0] = 0;
  F(i, 1, n) {
    F(j, 0, 3) Fmax(dp[i][3], dp[i - 1][j]);
    dp[i][1] = max(get(0, 0, a[0][i]), get(1, 1, -a[0][i])) + 1;
    dp[i][2] = max(get(1, 0, a[1][i]), get(0, 1, -a[1][i])) + 1;
    if (a[0][i] + a[1][i] == 0) F(j, 1, 3) Fmax(dp[i][0], dp[i][j] + 1);
    F(j, 0, 1) {
      Fmax(mp[j][0][a[j][i]], max({dp[i][0], dp[i][1 + j], dp[i][3]}));
      Fmax(mp[j][1][a[j][i]], max(dp[i][1 + j], dp[i][3]));
    }
  }
  cout << dp[n][0] << '\n';
```

---

## 作者：xgcxgc (赞：0)

首先令每个元素减去整体平均值，则变为求连通块总和为 $0$ 最大数量。

考虑只有在某一列出现拐点时的状态有用，因此对于每一列总共可以分类成 $4$ 种状态。

- $\text{oo}$：这一列两行处在同一个连通块，且该连通块还有可能继续延申；
- $\text{xo}$：这一列第二行所处的连通块结束，第一行所处的连通块还有可能继续延申；
- $\text{ox}$：这一列第一行所处的连通块结束，第二行所处的连通块还有可能继续延申；
- $\text{xx}$：这一列两行涉及到的连通块同时结束；

不妨设 $f_{\text{oo}/\text{xo}/\text{ox}/\text{xx}}[i]$ 分别表示这四种状态在第 $i$ 列时所能划分的最大连通块数。

设 $S_{o,i}$ 表示每行前缀和，令：
$$
s_{o,i} \;\; \gets \;\;
\begin{cases} 
    S_{0,i}, & o = 0 \\[1mm]
    -\,S_{1,i}, & o = 1
\end{cases} 
\quad \text{for } 1 \le i \le n
$$
则我们讨论 $4 \times 4$ 种转移组合有如下转移式：
$$
\begin{aligned}
f_{\text{oo}}[i] 
    &\;\gets\; 
    \max_{1 \le j \le i-1} 
    \Big\{ 
        f_{\text{ox}}[j],\; f_{\text{xo}}[j],\; f_{\text{xx}}[j] 
    \Big\} \\[1mm]

f_{\text{xo}}[i] 
    &\;\gets\; 
    \max \Bigg\{ 
        \max_{\substack{1 \le j \le i-1 \\[1mm] s_{0, i} = s_{0, j}}} 
            \Big\{ f_{\text{oo}}[j],\; f_{\text{xo}}[j],\; f_{\text{xx}}[j] \Big\},\;
        \max_{\substack{1 \le j \le i-1\\[1mm] s_{0, i} = s_{1, j}}} 
            \Big\{ f_{\text{ox}}[j],\; f_{\text{oo}}[j] \Big\}
    \Bigg\} + 1 \\[1mm]

f_{\text{ox}}[i] 
    &\;\gets\; 
    \max \Bigg\{ 
        \max_{\substack{1 \le j \le i-1\\[1mm] s_{1, i} = s_{1, j}}} 
            \Big\{ f_{\text{oo}}[j],\; f_{\text{ox}}[j],\; f_{\text{xx}}[j] \Big\},\;
        \max_{\substack{1 \le j \le i-1\\[1mm] s_{1, i} = s_{0, j}}} 
            \Big\{ f_{\text{xo}}[j],\; f_{\text{oo}}[j] \Big\}
    \Bigg\} + 1 \\[1mm]

f_{\text{xx}}[i] 
    &\;\gets\; 
    \begin{cases} 
        \max \Big\{ f_{\text{xo}}[i],\; f_{\text{ox}}[i],\; f_{\text{oo}}[i] \Big\} + 1, & 
            \text{if } s_{0, i} = s_{1, j} \\[1mm]
        0, & \text{otherwise}
    \end{cases}
\end{aligned}
$$
那么即可在 $O(n \log n)$ 的时间复杂度内解决本题。
```cpp
#include <bits/stdc++.h>

using LL = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n; std::cin >> n;
    std::vector<std::vector<LL>> a(2, std::vector<LL>(n));
    LL sum = 0;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> a[i][j];
            sum += a[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        a[0][i] = 2LL * n * a[0][i] - sum;
        a[1][i] = sum - 2LL * n * a[1][i];
        if (i) {
            a[0][i] += a[0][i - 1];
            a[1][i] += a[1][i - 1];
        }
    }
    std::map<LL, int> g[2];
    g[0][0] = g[1][0] = 1;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int oo = ans;
        int xo = g[0][a[0][i]];
        int ox = g[1][a[1][i]];
        int mx = std::max({oo, xo, ox});
        int xx = a[0][i] == a[1][i] ? mx + 1 : 0;
        ans = std::max(mx, xx);
        g[0][a[0][i]] = std::max(g[0][a[0][i]], std::max({oo, xo, xx}) + 1);
        g[0][a[1][i]] = std::max(g[0][a[1][i]], std::max(ox, oo) + 1);
        g[1][a[1][i]] = std::max(g[1][a[1][i]], std::max({oo, ox, xx}) + 1);
        g[1][a[0][i]] = std::max(g[1][a[0][i]], std::max(xo, oo) + 1);
    }
    std::cout << ans << '\n';
    return 0;
}
```

---

