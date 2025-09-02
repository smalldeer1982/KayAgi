# Nim

## 题目描述

重温一下「Nim」游戏的规则。游戏开始时有 $ n $ 堆石子，第 $ i $ 堆中有若干石子。两名玩家轮流行动：选择一个不为空的石子堆，从中取走至少一个石子。不能进行操作的玩家将输掉游戏。

现有一个包含 $ n $ 个整数的数组 $ a $。Artem 和 Ruslan 打算在数组的部分区间上进行 Nim 游戏。每个游戏回合由一个区间 $ (l_i, r_i) $ 确定，其中 $ a_{l_i}, a_{l_i+1}, \dots, a_{r_i} $ 是各个石子堆的大小。

在每轮游戏开始前，Ruslan 可以选择从该区间中移除任意数量的堆，但至少要留下一个堆，因此最多可移除 $ (r_i - l_i) $ 堆。他可以选择不移除任何堆。移除后，游戏将在留下的堆上进行。

每个回合相互独立：某一回合的变动不会影响原始数组或其他回合。

Ruslan 的目标是移除尽可能多的石子堆，以确保始终是先手的 Artem 输掉游戏。

对于每个回合：

1. 确定 Ruslan 可以移除的最大石子堆数量；
2. 计算达到最大移除数量的方法数，并输出其对 $ 998\,244\,353 $ 取模的结果。

若两种移除方法在某个索引 $ i $ 上存在区别，即一种方法移除了该索引对应的堆而另一种没有，则视为两种不同的方法。若 Ruslan 无法确保 Artem 输掉某回合，则输出 -1。

## 样例 #1

### 输入

```
9 5
0 1 2 1 3 4 5 6 0
1 5
2 5
3 5
4 5
1 9```

### 输出

```
4 1
2 1
0 1
-1
8 2```

# 题解

## 作者：sunkuangzheng (赞：2)

*!!))。

分治，每次只处理跨过 $mid$ 的询问。

从 $mid$ 开始预处理前后缀背包，合并前后缀需要 $\mathcal O(v^2)$ 的代价。

总复杂度 $\mathcal O(nv \log n + qv^2)$。[code](https://codeforces.com/contest/2043/submission/298297294)。

---

## 作者：__vector__ (赞：2)

本题披着博弈论的外衣，实际上，除了第一步用 Nim 定理转化题意以外，跟博弈论没什么关系。  

### 题意   

给定一个长度为 $n$ 的非负整数数组。  

给定 $q$ 次询问，每次给定一个区间 $[l,r]$，问这个区间最多删除多少个位置，使得剩下的位置上的数异或和为 $0$。  

不能删完，同时求出能使删除数字数量最多的方案数量。 
 
 两个方案不同当且仅当删除的位置的集合不同。   
 
无解输出 $-1$。  
### 做法   

注意到值域是 $[0,50]$，也就是说最多有 $51$ 种数字。  

对于每一种数字，其最多保留 $2$ 个，证明是假如最优解中出现多于 $2$ 个相同的数字，那么可以删除两个这样的数字得到更优的解。  

随后 dp，$dp_{i,j,0/1}$ 代表前 $i$ 种数字，保留的数字异或和为 $j$，且前 $i$ 个数字是否全部删除。  

状态转移的话，只需要对于每种数字，枚举其保留了几个，转移是显然的。  

这是我的 dp 转移的代码：  

```cpp   
int rem[51];// 每种数字出现的次数
int top;// 有多少不同的数字
dp[0][0][0]=0;// 最多删多少个
ways[0][0][0]=1; // 保证删最多个的方案数
auto ckmxdp=[&](int nxti,int nxtj,int nxtk,int i,int j,int k,int add,ll waymult)->void{
    // nxti,nxtj,nxtk 代表新的状态，i,j,k 是旧的状态，add 是旧的状态转移后 dp 值加上多少,waymult 是本次选保留的位置的方案数。
    if(dp[nxti][nxtj][nxtk]<dp[i][j][k]+add){
        dp[nxti][nxtj][nxtk]=dp[i][j][k]+add;
        ways[nxti][nxtj][nxtk]=ways[i][j][k]*waymult;
    }else if(dp[nxti][nxtj][nxtk]==dp[i][j][k]+add){
        ways[nxti][nxtj][nxtk]+=ways[i][j][k]*waymult;
    }
    ways[nxti][nxtj][nxtk]%=mod;
};
for(int i=0;i<top;i++){
    for(int j=0;j<=63;j++){
        for(int k=0;k<=1;k++){
            // 当前这个数不对总 xor 造成影响。  
            // 情况：保留 0 或 2 个。
            ckmxdp(i+1,j,k,i,j,k,rem[i+1],1);
            if(rem[i+1]>=2){
                ckmxdp(i+1,j,1,i,j,k,rem[i+1]-2,((ll)rem[i+1]*(rem[i+1]-1)/2)%mod);
            }
            // 当前这个数对总 xor 造成影响。  
            // 情况：保留 1 个.
            if(rem[i+1]>=1){
                ckmxdp(i+1,j^b[i+1],1,i,j,k,rem[i+1]-1,rem[i+1]);
            }
        }
    }
}
if(dp[top][0][1]>=0){
    printf("%d %lld\n",dp[top][0][1],(ways[top][0][1]%mod+mod)%mod);
}else{
    puts("-1");
}
```

---

## 作者：Unnamed114514 (赞：0)

考虑莫队，这样你就能快速求出每个元素的出现次数。

有下列三种情况：

- 留下一个数，显然只会留下一个 $0$，方案数为 $cnt_0$。

- 留下两个数，显然会留下两个相同的数，方案数为 $\sum{cnt_i\choose 2}$。

- 留下若干个数，显然 dp 即可，定义 $f_{i,j}$ 表示当前算到 $i$，异或和为 $j$ 的最少数量，注意只有 $cnt_i\ge 1$ 才能进行转移。

时间复杂度 $O(n\sqrt n+nV^2)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f3f3f3f3fLL
#define double long double
#define eps 1e-8
#define endl '\n'
using namespace std;
const int N=1e5+5,mod=998244353;
int n,m,a[N],blk[N],B,cnt[51],f[51][64],g[51][64],l=1,r;
pair<int,int> ans[N];
struct node{
	int l,r,id;
	bool operator <(const node &o) const{
		if(blk[l]!=blk[o.l]) return blk[l]<blk[o.l];
		return (blk[l]&1)?(r<o.r):(r>o.r);
	}
}q[N];
void add(int p){ ++cnt[a[p]]; }
void del(int p){ --cnt[a[p]]; }
pair<int,int> solve(){
	if(cnt[0]) return make_pair(r-l+1-1,cnt[0]);
	int mx=0;
	for(int i=1;i<=50;++i) mx=max(mx,cnt[i]);
	if(mx>=2){
		int sum=0;
		for(int i=1;i<=50;++i) sum=(sum+cnt[i]*(cnt[i]-1)/2)%mod;
		return make_pair(r-l+1-2,sum);
	}
	for(int i=1;i<=50;++i){
		for(int j=0;j<64;++j) f[i][j]=f[i-1][j],g[i][j]=g[i-1][j];
		if(cnt[i]){
			f[i][i]=1,g[i][i]=cnt[i];
			for(int j=0;j<64;++j){
				if(f[i-1][j^i]+1<f[i][j]) f[i][j]=f[i-1][j^i]+1,g[i][j]=0;
				if(f[i-1][j^i]+1==f[i][j]) g[i][j]=(g[i][j]+g[i-1][j^i]*cnt[i])%mod;
			}
		}
	}
	if(f[50][0]==inf) return make_pair(-1,-1);
	return make_pair(r-l+1-f[50][0],g[50][0]);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m,B=sqrt(n);
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=m;++i) cin>>q[i].l>>q[i].r,q[i].id=i;
	for(int i=1;i<=(n+B-1)/B;++i) for(int j=(i-1)*B+1;j<=min(n,i*B);++j) blk[j]=i;
	sort(q+1,q+m+1);
	memset(f[0],inf,sizeof(f[0]));
	memset(g[0],0,sizeof(g[0]));
	for(int i=1;i<=m;++i){
		while(l>q[i].l) add(--l);
		while(r<q[i].r) add(++r);
		while(l<q[i].l) del(l++);
		while(r>q[i].r) del(r--);
		ans[q[i].id]=solve();
	}
	for(int i=1;i<=m;++i) 
		if(ans[i].first==-1) cout<<-1<<endl;
		else cout<<ans[i].first<<' '<<ans[i].second<<endl;
	return 0;
}
```

---

## 作者：xiaoyang222 (赞：0)

题目转换为下面。

> 有多次询问，每次询问两个数 $l$ 和 $r$，问 $l$ 到 $r$ 最多能选多少个数使得其他没有选完的数的异或值为 $0$，并输出选的方案数，取模。

容易发现值域很小，所以可以把值全存进桶里。

考虑反着做，$f_{i,j}$ 表示考虑了前 $i$ 个数，选出的数的异或值为 $j$ 的方案数。过程中再维护一个数组用来记录长度。

这两个数组按照题目的意思就可以了，细节有些多。

这里有一个小优化。如果一个数出现多次，这个数只会选零次或一次，因为使用多次会被抵消。所以就做完了。

但是这里有一个问题，如果之前异或成 $0$ 的方法太弱了，导致使用了大于等于 $2$ 个数，如果当前这个数大于等于二，完全可以替代异或成 $0$ 的方法，重新赋值。见下面代码。

代码用了滚动数组。

```cpp
#include <iostream>
using namespace std;
const int N=1e5+5,M=64,K=51,MOD=998244353;
int sm[N][M];
int cnt[M];
long long f[2][M]/*种类数*/;
int mn[2][M];
//int dug[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,q;
//	n=1e5,q=1;
	cin >> n >> q;
	for (int i=1,x;i<=n;++i) 
		cin >> x
//		x=(i-1)%5+1,dug[i]=x
		,++sm[i][x];
	for (int i=1;i<=n;++i)
		for (int j=0;j<M;++j)
			sm[i][j]+=sm[i-1][j];
	int l1,l2;
	for (int _=0,l,r;_<q;++_){
		cin >> l >> r;
//		l=43789,r=43818;
//		cout<<l<<" "<<r<<" ";
//		cout<<r-l+1<<"\n";
//		for (int i=l;i<=r;++i) cout<<dug[i]<<" ";cout<<"\n";
//		if (n==100000) cout<<l<<" "<<r<<'\n';
		for (int j=0;j<K;++j) 
			cnt[j]=sm[r][j]-sm[l-1][j];
//		for (int i=0;i<=5;++i) cout<<cnt[i]<<" ";
//		cout<<"\n";
//		for (int i=1;i<=5;++i) cout<<cnt[i]<<" ";cout<<"\n";
		int tot=0;
		for (int j=0;j<M;++j) f[0][j]=f[1][j]=0,mn[0][j]=mn[1][j]=MOD;
		for (int i=0;i<K;++i){
			for (int j=0;j<M;++j){
				if (j==i && cnt[i]) mn[tot][j]=1,f[tot][j]=cnt[i];
				else{
					l1=mn[tot^1][j],l2=MOD+2;//两边选的数的个数
					mn[tot][j]=mn[tot^1][j];
					if (cnt[i]) mn[tot][j]=min(mn[tot][j],mn[tot^1][j^i]+1),l2=mn[tot^1][j^i]+1;
					f[tot][j]=0;
//					cout<<l1<<" "<<l2<<"\n";
					if (l1<l2){
						f[tot][j]+=f[tot^1][j];//不选这一位
					}else if (l1>l2){
						f[tot][j]+=1ll*f[tot^1][j^i]*cnt[i]%MOD;//这里肯定是有的，所以选这一位
					}else{
						f[tot][j]+=f[tot^1][j]+1ll*f[tot^1][j^i]*cnt[i]%MOD;
					}
//					f[tot][j]+=f[tot^1][j]+f[tot^1][j^i]*((bool)cnt[i]);
					if (cnt[i]>=2 && j==0){
						if (mn[tot][j]>2) mn[tot][j]=2,f[tot][j]=1ll*cnt[i]*(cnt[i]-1)/2;
						else if (mn[tot][j]==2) f[tot][j]+=1ll*cnt[i]*(cnt[i]-1)/2;
					}
					f[tot][j]%=MOD;
				}
//				cout<<i<<" "<<j<<" : "<<f[tot][j]<<"\n";
			}
			tot^=1;
		}
		tot^=1;
		if (mn[tot][0]>=MOD/2) cout<<"-1\n";
		else cout<<r-l+1-mn[tot][0]<<" "<<f[tot][0]%MOD<<"\n";
	}
	cout.flush();
	return 0;
} 
/*
30 1
1 1 1 1 1 1 2 2 2 2 2 2 3 3 3 3 3 3 4 4 4 4 4 4 5 5 5 5 5 5
1 30
30 1
4 5 1 2 3 4 5 1 2 3 4 5 1 2 3 4 5 1 2 3 4 5 1 2 3 4 5 1 2 3
1 30
*/
```

---

## 作者：spacebar (赞：0)

前置知识：Nim 游戏

不会去学：[【模板】Nim 游戏](https://www.luogu.com.cn/problem/P2197)

Nim 游戏先手必败的条件是每堆石子的数目异或到一起等于零，我们要做的是用最少的数异或出 $0$（用的少删的多）。

拿到这个题，发现 $a_i \leq 50$ 而且异或有一个性质就是一个数异或自己得到的是 $0$！

根据鸽巢原理如果给定区间有超过 $51$ 个数根据鸽巢原理至少有一对一样的数，所以**最多**最少留两个数（最多删的数减一下就行了啊），用类似前缀和的方法统计从开头到某位有多少个某值的数，算一下在给定区间内取两个一样数的取法就行了。

还要预先判断区间内有没有 $0$，如果有零那么只需保留一堆石头（零）就赢了，方案数为区间内零的数目。

在区间的有小于等于 $51$ 个数时由于数据很小可以随便乱搞，我写了一个动态规划仅供参考：


```cpp
 /*
          dip_i (临时的)异或出i最少要保留的数
          wys_i  (临时的)在保留的数最少时的方案数
          dp_i   异或出i最少要保留的数
          ways_i   在保留的数最少时的方案数
 */
for(long long i=l;i<=r;i++){
			for(long long j=0;j<=64;j++){
				dip[j]=114515141919;//初始化最小方案数
				wys[j]=0;//初始化
			}
			shu=a[i];
			dip[shu]=1;
			wys[shu]=1;
			for(long long j=0;j<=64;j++){//计算有a_i参与的答案
				if(dp[j]+1<dip[j^shu]){
					dip[j^shu]=dp[j]+1;
					wys[j^shu]=ways[j];
				}else{
					if(dp[j]+1==dip[j^shu]){
						wys[j^shu]+=ways[j]; 
					}
				}
			}
			for(long long j=0;j<=64;j++){//更新答案
				if(dip[j]<dp[j]){
					dp[j]=dip[j];
					ways[j]=wys[j];
				}else{
					if(dip[j]==dp[j]){
						ways[j]+=wys[j];
					}
				}
				ways[j]%=998244353;
			}
		//	cout<<dp[1]<<' '<<dp[2]<<" "<<dp[3]<<endl;
		}
```

---

