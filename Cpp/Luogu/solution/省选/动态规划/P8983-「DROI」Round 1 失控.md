# 「DROI」Round 1 失控

## 题目背景

失控的，或许反而是理智的。

## 题目描述

给定一个 $n \times m$ 的矩阵 $G$ 和两个长度为 $m$ 的排列 $p,q$。

我们称元素 $G_{i,j}$ 是**失控的**，当且仅当 $\vert G_{i,j} - G_{i-1,p_j} \vert > C$ **且** $\vert G_{i,j} - G_{i+1,q_j} \vert > C$，其中 $C$ 是给定的常数。特殊地，我们规定无论如何第 $1$ 行和第 $n$ 行的元素都不是失控的。

此时再给定两个长度为 $k$ 的序列 $A$ 和 $B$。

你将有 $k$ 种操作：其中第 $i$ 种操作是将某一行所有元素增加 $A_i$，这将会花费 $B_i$ 的代价。**每种操作可以使用的次数不限，但对于每一行，你只可以进行这些操作中的一种或不操作。并且，你必须保证任意相邻两行最多有一行进行操作。**

请问要使得矩阵 $G$ 中所有元素均不失控，至少要花费的代价是多少（数据保证有解）？

## 说明/提示

#### 样例解释 #1

显然对于样例一，不用进行任何操作就能保证所有元素均不失控。

------------

#### 样例解释 #2

对第三行使用 $3$ 操作，对第七行使用 $4$ 操作即可。可以证明不存在更优的方案。

------------

#### 数据范围

**「本题采用捆绑测试」** 

- $\operatorname{Subtask} 1(10\%)$：$n,m,k \leq 8$。

- $\operatorname{Subtask} 2(30\%)$：$m\leq 50,k\leq 100$。

- $\operatorname{Subtask} 3(20\%)$：$m\leq 50,k\leq 1000$。

- $\operatorname{Subtask} 4(40\%)$：无特殊限制。

对于 $100\%$ 的数据满足：$3 \leq n\leq 50$，$1 \leq m \leq 300$，$0 \leq k \leq 2000$，$C,G_{i,j},A_i,B_i \leq 10^6$。

**本题输入量较大，请用较快的输入方法。**

------------

#### 提示

- 本题不卡常，如果你认为自己的算法差一点就能跑过下一个 Subtask 却没有跑过，那么请不要纠结于无意义的卡常，因为差的这一点可能需要更优秀的算法来弥补。

## 样例 #1

### 输入

```
3 3 5 10
1 2 6
7 3 11
9 44 5
2 3 1
1 3 2
5 10 15 20 25
6 6 6 6 6```

### 输出

```
0```

## 样例 #2

### 输入

```
8 8 8 28
49 11 44 31 25 37 41 1 
29 38 46 21 21 17 45 47 
1 37 11 31 8 15 15 47 
21 47 15 6 11 9 40 28 
21 29 1 11 39 15 21 35 
26 20 3 38 1 41 27 21 
41 41 31 16 11 1 24 3 
33 15 23 26 7 47 49 8 
3 8 2 4 6 5 1 7 
7 5 8 3 6 1 4 2 
36 13 12 3 38 49 22 55 
20 24 2 30 26 25 17 25 ```

### 输出

```
32```

# 题解

## 作者：QwQcOrZ (赞：9)

闲话：出题人曾经转移那部分的问题抽象之后丢到洛谷讨论区里问过，我当时顺手就回答了一下~~然后 std 用了我的做法~~，没想到这次遇上了！

~~全新出题方式，学到了！！1~~

但是这个题是有性质的，可以做到更优的复杂度。

---

为了方便考虑，我们加入操作 $0$ 满足 $A_0=0$，$B_0=0$ 表示不操作。

那么每行我们都必须选择一个操作进行且不能进行连续两次非零操作。

考虑 dp，记 $f_{i,0/1,j}$ 表示当前考虑了前 $i$ 行，前 $i-1$ 行已经确定合法，$0/1$ 表示最后两行中非零操作是哪一行，使用的是第 $j$ 个操作。（需要注意一下两行都为零操作的情况）

转移即考虑 $i+1$ 行进行什么操作，然后检验第 $i$ 行是否合法。

若暴力枚举下一行进行哪个操作，检验是否合法，时间复杂度 $\mathcal O(nmk^2)$。

考虑优化，首先若非零操作在最后一行，那么下一行只能进行操作 $0$，暴力转移即可，时间复杂度 $\mathcal O(nmk)$。

那么现在剩下的情况就是最后一行为操作 $0$，倒数第二行操作为 $j$。

考虑对于每个下一个进行的操作快速找出哪些 $j$ 是合法的，对于第 $i$ 行的每个元素 $G_{i,x}$ 都需要满足 $\vert G_{i,j} - G_{i-1,p_j} \vert > C$ 且 $\vert G_{i,j} - G_{i+1,q_j} \vert > C$，因此第 $i-1$ 行和第 $i+1$ 行我们都可以得到一个区间，当加的数在这个区间内时满足条件。

于是条件变为两行加的数不能都不在区间里，我们枚举 $i+1$ 行进行了什么操作，若加的数在对应区间内，那么没有限制；否则不在区间内，那么 $i-1$ 行操作的数必须在区间中。

可以对于每个操作维护出 $i-1$ 行加数区间的交，时间复杂度 $\mathcal O(nmk)$。

最后，对于 $i+1$ 每个操作能转移的的位置是按照操作的加数 $A_i$ 排序后的一段区间，离散化后查询区间最小值即可。

时间复杂度 $\mathcal O(nmk+n\cdot\operatorname{rmq}(k))$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=55;
const int M=305;
const int K=2e3+5;

int n,m,k,C,a[N][M],p[M],q[M],A[K],B[K],dp[N][2][K],pos[K],b[K],st[11][K],Log[K];

signed main() {
	ios::sync_with_stdio(false),cin.tie(0);
	cout.precision(10),cout.setf(ios::fixed);
	
	cin>>n>>m>>k>>C;
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			cin>>a[i][j];
		}
	}
	for (int i=1;i<=m;i++) {
		cin>>p[i];
	}
	for (int i=1;i<=m;i++) {
		cin>>q[i];
	}
	for (int i=1;i<=k;i++) {
		cin>>A[i];
		b[i]=A[i];
	}
	for (int i=1;i<=k;i++) {
		cin>>B[i];
	}
	b[k+1]=0;
	sort(b+1,b+k+2);
	int cnt=unique(b+1,b+k+2)-b-1;
	for (int i=0;i<=k;i++) {
		pos[i]=lower_bound(b+1,b+cnt+1,A[i])-b;
	}
	for (int i=2;i<=cnt;i++) {
		Log[i]=Log[i/2]+1;
	}
	
	memset(dp,0x3f,sizeof(dp));
	for (int i=0;i<=k;i++) {
		dp[1][i>0][i]=B[i];
	}
	for (int i=2;i<=n;i++) {
		for (int j=1;j<=k;j++) {
			dp[i][0][j]=dp[i-1][1][j];
		}
		vector<pair<int,int>>lim(k+1,make_pair(-(int)1e9,(int)1e9));
		if (i>2) {
			for (int j=1;j<=m;j++) {
				int L1=(a[i-1][j]-C)-a[i-2][p[j]],R1=(a[i-1][j]+C)-a[i-2][p[j]];
				int L2=(a[i-1][j]-C)-a[i][q[j]],R2=(a[i-1][j]+C)-a[i][q[j]];
				for (int t=0;t<=k;t++) {
					if (A[t]<L2||A[t]>R2) {
						lim[t].first=max(lim[t].first,L1);
						lim[t].second=min(lim[t].second,R1);
					}
				}
			}
		}
		for (int j=1;j<=cnt;j++) {
			st[0][j]=1e9+7;
		}
		for (int j=0;j<=k;j++) {
			st[0][pos[j]]=min(st[0][pos[j]],dp[i-1][0][j]);
		}
		for (int j=1;j<11;j++) {
			for (int t=1;t<=cnt;t++) {
				st[j][t]=min(st[j-1][t],st[j-1][t+(1<<(j-1))]);
			}
		}
		for (int x=0;x<=k;x++) {
			bool flag=1;
			if (i<n&&x) {
				for (int j=1;j<=m;j++) {
					if (abs(a[i][j]+A[x]-a[i-1][p[j]])>C&&abs(a[i][j]+A[x]-a[i+1][q[j]])>C) {
						flag=0;
						break;
					}
				}
			}
			if (!flag) {
				continue;
			}
			int l=lower_bound(b+1,b+cnt+1,lim[x].first)-b;
			int r=upper_bound(b+1,b+cnt+1,lim[x].second)-b-1;
			if (l<=r) {
				int k=Log[r-l+1];
				int mn=min(st[k][l],st[k][r-(1<<k)+1]);
				dp[i][x>0][x]=min(dp[i][x>0][x],mn+B[x]);
			}
		}
	}
	int ans=1e9+7;
	for (int i=0;i<=k;i++) {
		ans=min(ans,min(dp[n][0][i],dp[n][1][i]));
	}
	cout<<ans<<"\n";
	
	return 0;
}
```



---

## 作者：Demeanor_Roy (赞：3)

- 出题人题解。

------------

跳过第一档爆搜，不难发现没法直接贪心，看起来也没有什么可以利用的性质，于是考虑 DP。

考虑到对于第 $i$ 行的元素来说，只有对 $i-1,i,i+1$ 这三行元素的操作能影响其是否失控。据此，我们不妨固定顺序，从上往下 DP。

直观的想法是设计 $f(i,j,k)$ 表示前 $i-1$ 行确定合法，且最后两行涉及的操作分别为 $j,k$ 时的最优答案。特殊地，当 $j/k=0$ 时，表示不操作。转移的话就考虑枚举 $f(i-1,k,p)$ 判断对第 $i-1$ 行是否合法即可。时间复杂度 $O(nmk^3)$。

但这样做显然没有利用好一个性质：`保证任意相邻两行最多有一行进行操作。`

由于这个条件，发现 $f$ 中诸多状态是不合法的，考虑压缩：$f(i,state)$ 表示前 $i-1$ 行已确定合法，最后两行状态是 $state$ 的最优答案。其中 $state$ 取值为 $[0,2k]$，当 $state=0$ 时表示最后两行都不操作，取 $[1,k]$ 时表示 $i-1$ 行进行某个操作，取 $[k+1,2k]$ 时表示第 $i$ 行进行某个操作。向之前一样枚举转移即可。时间复杂度 $O(nmk^2)$。

此时可以通过前 $40$ 分。

发现状态已经优化到底了，考虑优化转移。发现 $f(i,now)$ 从 $f(i-1,fr)$ 转移过来时，前者确定了第 $i$ 行对第 $i-1$ 行的影响，后者确定了第 $i-2$ 行对第 $i-1$ 行的影响。而影响可以用一串 $01$ 串表示，其中第 $j$ 位表示对于第 $i-1$ 行第 $j$ 个位置，第 $i-2/i$ 行在当前状态下能否使其合法。至此不难想到 bitset 优化 DP，先分别预处理出 $f(i,now)$ 和 $f(i-1,fr)$ 对应的 $2k$ 个 $01$ 串，转移时就不用 $O(m)$ 判断，而是 $O(\frac{m}{w})$ 判断了。时间复杂度降至 $O(\frac{nmk^2}{w})$。

此时可以通过前 $60$ 分。

我们不妨先将问题抽象化，察觉到状态转移的本质其实是：初始给定 $k$ 个集合，$k$ 次询问每次给定一个集合，问哪些集合与询问集合的并是大小为 $m$ 的全集。

考虑对全集中的元素分块，假设块长为 $B$，则共有 $\frac{m}{B}$ 块。对于每一块，其内部元素共有 $2^B$ 种存在状态，用类似状压 DP 的方式，预处理出每一块每种状态对应的 $01$ 串，其中第 $j$ 个位置表示第 $j$ 个集合是否拥有这一块这些元素。时间复杂度可以做到 $O(\frac{2^Bmk}{Bw})$。

对于每一个询问，将每一块对应的缺失元素的状态的 bitset 做交，即可得到哪些集合是合法的。时间复杂度 $O(\frac{mk^2}{Bw})$。

不难得到当 $B$ 取 $\log_2k$ 时最优，时间复杂度为 $O(\frac{mk^2}{w\log_2k })$，所以总时间复杂度为 $O(\frac{nmk^2}{w\log_2k })$。

至此这道题已经解决完毕。若有更优秀的做法，欢迎各位大佬提出。

下附代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=310,M=2010,INF=1e9;
int n,m,k,c,len,R[N],p[N],q[N],fa[M],id[M],A[M],B[M],nxt[M],G[N][N],f[N][M<<1];
bitset<M> t,total,g[N],s[N][M];
inline int read()
{
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x;
}
inline bool check(int cur,int x,int y,int z)
{
	for(int i=1;i<=m;i++) if(abs(G[cur][i]-G[cur-1][p[i]]+y-x)>c&&abs(G[cur][i]-G[cur+1][q[i]]+y-z)>c) return false;
	return true;
}
int main()
{
	memset(f,0x3f,sizeof f); 
	n=read(),m=read(),k=read(),c=read(),len=log2(k);
	for(int i=1;i<=m;i++) id[i]=i/len+1,R[id[i]]=i;
	for(int i=1;i<1<<len;i++) for(int j=len-1;j>=0;j--) if((i>>j)&1)	fa[i]=j;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) G[i][j]=read();
	for(int i=1;i<=m;i++) p[i]=read();
	for(int i=1;i<=m;i++) q[i]=read();
	for(int i=1;i<=k;i++) A[i]=read();
	for(int i=1;i<=k;i++) B[i]=read();
	for(int i=0;i<=k;i++) total[i]=true;
	for(int i=1;i<=id[m];i++) s[i][0]=total;
	for(int i=0;i<=k<<1;i++) f[2][i]=B[i<=k?i:i-k];
	for(int i=3;i<=n;i++)
	{
		for(int fr=0;fr<=k;fr++) if(check(i-1,A[fr],0,0)) f[i][0]=min(f[i][0],f[i-1][fr]);
		for(int now=1;now<=k;now++) if(check(i-1,0,A[now],0)) f[i][now]=min(f[i][now],f[i-1][now+k]);
		for(int j=1;j<=m;j++) for(int fr=0;fr<=k;fr++) if(abs(G[i-2][p[j]]+A[fr]-G[i-1][j])<=c) g[j][fr]=true;else g[j][fr]=false;
		for(int j=1;j<=id[m];j++)
			for(int state=1;state<1<<(R[j]-R[j-1]);state++)
				s[j][state]=(s[j][state-(1<<fa[state])]&g[R[j-1]+fa[state]+1]);
		int st=k+1;nxt[st]=-1;
		for(int j=k;j>=0;j--) if(f[i-1][j]<=INF) nxt[st]=j,st=j,nxt[st]=-1;
		for(int now=k+1;now<=k<<1;now++)
		{
			t=total;
			for(int j=1;j<=id[m];j++) 
			{
				int cur=0;
				for(int h=R[j-1]+1;h<=R[j];h++) if(abs(G[i][q[h]]+A[now-k]-G[i-1][h])>c) cur|=1<<(h-R[j-1]-1);
				t&=s[j][cur];
			}
			int st=k+1;
			while(nxt[st]>=0) 
			{
				st=nxt[st];
				if(t[st]) f[i][now]=min(f[i][now],f[i-1][st]+B[now-k]);
			}
		}
	}
	int ans=INT_MAX;
	for(int i=0;i<=k<<1;i++) ans=min(ans,f[n][i]);
	printf("%d",ans);
	return 0;
}
```


---

