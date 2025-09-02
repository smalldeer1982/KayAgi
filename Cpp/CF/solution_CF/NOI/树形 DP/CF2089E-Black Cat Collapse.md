# Black Cat Collapse

## 题目描述

黑猫的世界正在坍塌。

这个世界可以用一棵根为节点 $$$1$$$ 的有根树表示。Liki 和 Sasami 需要揭开这个世界的真相。

每天，他们可以探索一个尚未坍塌的节点 $$$u$$$。此次探索后，黑猫将导致 $$$u$$$ 及其子树中的所有节点坍塌。此外，在第 $$$i$$$ 天结束时，若存在编号为 $$$n - i + 1$$$ 的节点，该节点也会坍塌。

对于每个 $$$i$$$（从 $$$1$$$ 到 $$$n$$$），请确定满足以下条件的探索方案数：Liki 和 Sasami 恰好探索 $$$i$$$ 天（即执行恰好 $$$i$$$ 次操作），且最后一次探索在节点 $$$1$$$ 进行。结果需对 $$$998\,244\,353$$$ 取模。

注意：保证节点 $$$1$$$ 至 $$$n$$$ 可以构成该树的"DFS"顺序，即存在一种深度优先搜索遍历方式，使得第 $$$i$$$ 个访问的节点为 $$$i$$$。

## 说明/提示

对于第一个样例，以下操作序列是合法的：

$$$\{1\},\{2,1\},\{3,1\},\{4,1\},\{3,2,1\},\{4,2,1\},\{4,3,1\},\{4,3,2,1\}$$$

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2
4
1 2
2 3
2 4
7
4 2
6 1
5 1
7 6
2 3
1 2```

### 输出

```
1 3 3 1
1 6 23 48 43 17 1```

# 题解

## 作者：wangzhiyuan123 (赞：3)

场上黄老师似乎会了 $O(n^6)$ 没写出来。官方题解写的一坨。    

将最后的操作序列反转，前缀补零。比如先删 $4$，再依次删 $3,1$，得到的序列就是 $0134$。每个点能在的位置肯定是一个以自己的 $dfn$（记作 $in_x=x$）为开头的后缀，且每个点在自己祖先后面。

由于不能维护相对关系，我们考虑维护跟序列相关的状态。由于一个子树内的点填的后缀都受限于在 $in_x,out_x$ 内的位置，最先填的点不会在 $in_x$ 的左侧（但是会在右侧），所以设计我们设计一个 $dp_{u,i,j,k}$ 表示将 $u$ 子树内的点填到 $in_x,out_x$ 之间，填的最靠左的位置是 $i$（如果没有点填在区间内则 $i=out_x+1$），$i$ 右边到 $out_x$ 之间还剩 $j$ 个空没有填，有 $k$ 个点需要填到 $>out_x$ 的位置。

从后往前依次合并 $u$ 的儿子 $v$ 时分成两种情况考虑。设我们现在要合并 $dp_{u,i,j,k} 和 dp_{v,ii,jj,kk}$。   
第一种情况就是 $ii=out_v+1$ 。这种情况下考虑枚举 $w$ 表示有多少个 $kk$ 中的点要使用 u 的空位。考虑枚举第一个 $w$ 填的位置 $p$。如果 $w=0$ 或 $i<p$ 则直接转移到 $dp_{u,i,j+jj-w,k+kk-w}$ 上，否则转移到 $dp_{p,i,j+jj-w,k+kk-w}$ 上。通过一些预处理和树上背包可以实现到 $O(n^5)$ 的复杂度。需要滚动数组。

```cpp
//这一部分的代码
for(int ii=out[y]+1;ii<=out[x];ii++){
	for(int i=ii+1;i<=out[x]+1;i++)
		for(int j=0;j<=out[x]-out[y];j++){
			for(int k=0;k<=out[x]-out[y];k++){
				if(!dp[x][i][j][k]) continue;
				(tsum[ii][j+i-ii][k]+=dp[x][i][j][k])%=mod;
			}
		}
}
for(int i=out[y]+1;i<=out[x]+1;i++){
	for(int j=0;j<=out[x]-out[y]+1;j++){
		for(int k=0;k<=out[x]-out[y];k++){
			if(!dp[x][i][j][k]&&!tsum[i][j][k]) continue;
			for(int jj=0;jj<=out[y]-in[y]+1;jj++){
				for(int kk=0;kk<=out[y]-in[y]+1;kk++){
					if(!dp[y][out[y]+1][jj][kk]) continue;
					(tmp[i][j+jj][k+kk]+=dp[x][i][j][k]*dp[y][out[y]+1][jj][kk]%mod*C(k+kk,k))%=mod;
					for(int w=1;w<=j&&w<=kk;w++){
						(tmp[i][j+jj-w][k+kk-w]+=tsum[i][j][k]*dp[y][out[y]+1][jj][kk]%mod*C(j-1,w-1)%mod*C(k+kk-w,k))%=mod;
						(tmp[i][j+jj-w][k+kk-w]+=dp[x][i][j][k]*dp[y][out[y]+1][jj][kk]%mod*C(j,w)%mod*C(k+kk-w,k))%=mod;
					}
				}
			}
		}
	}
}
for(int i=out[y]+1;i<=out[x]+1;i++)
for(int j=0;j<=n;j++){
	for(int k=0;k<=n;k++){
		tsum[i][j][k]=0;
	}
}
```
第二种情况 $ii \le out_v$ 也是枚举 $w$。由于 $i$ 在 $out_v+1,out_u+1$ 之间，而 $ii \le out_v$，所以 $ii<i$ 直接贡献到 $dp_{u,ii,j+jj-w,k+kk-w}$ 即可。这种情况也需要预处理才能 $O(n^5)$。还是开个滚动数组。

```cpp
for(int i=out[y]+1;i<=out[x]+1;i++)
for(int j=0;j<=out[x]-out[y];j++){
	for(int k=0;k<=out[x]-out[y];k++){
		if(!dp[x][i][j][k]) continue;
		(sum[j+i-out[y]-1][k]+=dp[x][i][j][k])%=mod;
	}
}
for(int i=in[y];i<=out[y];i++){
for(int j=0;j<=out[x]-out[y]+1;j++){
	for(int k=0;k<=out[x]-out[y]+1;k++){
		if(!sum[j][k]) continue;
		for(int jj=0;jj<=out[y]-in[y]+1;jj++){
			for(int kk=0;kk<=out[y]-in[y]+1;kk++){
				if(!dp[y][i][jj][kk]) continue;
				for(int w=0;w<=j&&w<=kk;w++){
					(tmp[i][j+jj-w][k+kk-w]+=sum[j][k]*dp[y][i][jj][kk]%mod*C(j,w)%mod*C(k+kk-w,k))%=mod;
				}
			}
		}
	}
}
}
```
最后我们把 $u$ 合并到 $dp_u$ 里。   
第一种情况是 $u$ 直接不填了（$u=1$ 时这种情况不合法因为要求最后操作的是 $1$）。直接把 $dp_{u,i,j,k}$ 转移到 $dp_{u,i,j,k}$（丢进滚动数组里而不是直接自加）。

```cpp
if(x!=1){
	for(int i=in[x]+1;i<=out[x]+1;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k<=n;k++){
				tmp[i][j][k]=dp[x][i][j][k];
			}
		}
	}
}
```
第二种情况是将 $u$ 填到子树内中的子树所有值的左边，即对于 $dp_{u,i,j,k}$ 枚举一个 $p<i$ 表示 $u$ 填的位置，转移到 $dp_{u,p,j+i-p-1,k}$ 中。

```cpp
for(int ii=in[x];ii<=out[x];ii++){
	for(int i=ii+1;i<=out[x]+1;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k<=n;k++){
				if(!dp[x][i][j][k]) continue;
				(tmp[ii][j+i-ii-1][k]+=dp[x][i][j][k])%=mod;
			}
		}
	}
}
```
最后一种情况是将 $u$ 填到子树外。即 $p>out_u$ 的情况。由于子树内所有值都要求在 $u$ 右边，直接贡献到 $dp_{u,out_u+1,j,k+1}$ 即可。

```cpp
//实际上这里不判1也可以
if(x!=1)
	for(int k=1;k<=out[x]-in[x]+1;k++)
		(tmp[out[x]+1][0][k]+=dp[x][out[x]+1][0][k-1])%=mod;
```
最后对于恰好探索 $i$ 天的方案数直接输出 $dp_{1,n-i+1,0,0}$。

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
	int w=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) w=w*10+ch-'0',ch=getchar();
	return w;
}
const int mod=998244353;
inline int qpow(int x,int b){
	int v=1;
	while(b){
		if(b&1) v=v*x%mod;
		x=x*x%mod;
		b>>=1;
	}
	return v;
}
int t,n=80;
int fac[85],inv[85];
void init(){
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
	inv[n]=qpow(fac[n],mod-2);
	for(int i=n;i;i--) inv[i-1]=inv[i]*i%mod;
}
int C(int u,int v){return fac[u]*inv[v]%mod*inv[u-v]%mod;}
vector<int> tr[85];
int in[85],out[85];
int dp[85][85][85][85];
void dfs(int x){
	in[x]=out[x]=x;
	sort(tr[x].begin(),tr[x].end());
	for(int y:tr[x]){
		dfs(y);
		out[x]=out[y];
	}
}
int tmp[85][85][85];
int sum[85][85];
int tsum[85][85][85];
void dfs1(int x){
	dp[x][out[x]+1][0][0]=1;
	reverse(tr[x].begin(),tr[x].end());
	for(int y:tr[x]){
		dfs1(y);
		{
			for(int ii=out[y]+1;ii<=out[x];ii++){
				for(int i=ii+1;i<=out[x]+1;i++)
					for(int j=0;j<=out[x]-out[y];j++){
						for(int k=0;k<=out[x]-out[y];k++){
							if(!dp[x][i][j][k]) continue;
							(tsum[ii][j+i-ii][k]+=dp[x][i][j][k])%=mod;
						}
					}
			}
			for(int i=out[y]+1;i<=out[x]+1;i++){
				for(int j=0;j<=out[x]-out[y]+1;j++){
					for(int k=0;k<=out[x]-out[y];k++){
						if(!dp[x][i][j][k]&&!tsum[i][j][k]) continue;
						for(int jj=0;jj<=out[y]-in[y]+1;jj++){
							for(int kk=0;kk<=out[y]-in[y]+1;kk++){
								if(!dp[y][out[y]+1][jj][kk]) continue;
								(tmp[i][j+jj][k+kk]+=dp[x][i][j][k]*dp[y][out[y]+1][jj][kk]%mod*C(k+kk,k))%=mod;
								for(int w=1;w<=j&&w<=kk;w++){
									(tmp[i][j+jj-w][k+kk-w]+=tsum[i][j][k]*dp[y][out[y]+1][jj][kk]%mod*C(j-1,w-1)%mod*C(k+kk-w,k))%=mod;
									(tmp[i][j+jj-w][k+kk-w]+=dp[x][i][j][k]*dp[y][out[y]+1][jj][kk]%mod*C(j,w)%mod*C(k+kk-w,k))%=mod;
								}
							}
						}
					}
				}
			}
			for(int i=out[y]+1;i<=out[x]+1;i++)
			for(int j=0;j<=n;j++){
				for(int k=0;k<=n;k++){
					tsum[i][j][k]=0;
				}
			}
		}
		

		{
			for(int i=out[y]+1;i<=out[x]+1;i++)
				for(int j=0;j<=out[x]-out[y];j++){
					for(int k=0;k<=out[x]-out[y];k++){
						if(!dp[x][i][j][k]) continue;
						(sum[j+i-out[y]-1][k]+=dp[x][i][j][k])%=mod;
					}
				}
			for(int i=in[y];i<=out[y];i++){
				for(int j=0;j<=out[x]-out[y]+1;j++){
					for(int k=0;k<=out[x]-out[y]+1;k++){
						if(!sum[j][k]) continue;
						for(int jj=0;jj<=out[y]-in[y]+1;jj++){
							for(int kk=0;kk<=out[y]-in[y]+1;kk++){
								if(!dp[y][i][jj][kk]) continue;
								for(int w=0;w<=j&&w<=kk;w++){
									(tmp[i][j+jj-w][k+kk-w]+=sum[j][k]*dp[y][i][jj][kk]%mod*C(j,w)%mod*C(k+kk-w,k))%=mod;
								}
							}
						}
					}
				}
			}
		}

		for(int j=0;j<=n;j++){
			for(int k=0;k<=n;k++){
				sum[j][k]=0;
			}
		}

		for(int i=in[x];i<=out[x]+1;i++){
			for(int j=0;j<=n;j++){
				for(int k=0;k<=n;k++){
					dp[x][i][j][k]=tmp[i][j][k];
					tmp[i][j][k]=0;
				}
			}
		}
	}



	if(x!=1){
		for(int i=in[x]+1;i<=out[x]+1;i++){
			for(int j=0;j<=n;j++){
				for(int k=0;k<=n;k++){
					tmp[i][j][k]=dp[x][i][j][k];
				}
			}
		}
	}
	
	for(int ii=in[x];ii<=out[x];ii++){
		for(int i=ii+1;i<=out[x]+1;i++){
			for(int j=0;j<=n;j++){
				for(int k=0;k<=n;k++){
					if(!dp[x][i][j][k]) continue;
					(tmp[ii][j+i-ii-1][k]+=dp[x][i][j][k])%=mod;
				}
			}
		}
	}
	if(x!=1) for(int k=1;k<=out[x]-in[x]+1;k++) (tmp[out[x]+1][0][k]+=dp[x][out[x]+1][0][k-1])%=mod;
	for(int i=in[x];i<=out[x]+1;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k<=n;k++){
				dp[x][i][j][k]=tmp[i][j][k];
				tmp[i][j][k]=0;
			}
		}
	}
}
main(){
	init();
	t=read();
	while(t--){
		n=read();
		for(int i=1;i<n;i++){
			int u=read(),v=read();
			if(u>v) swap(u,v);
			tr[u].push_back(v);
		}
		memset(dp,0,sizeof(dp));
		dfs(1);
		dfs1(1);
		for(int i=1;i<=n;i++) printf("%lld ",dp[1][n-i+1][0][0]);puts("");
		for(int i=1;i<=n;i++) tr[i].clear();
	}
}
```

---

