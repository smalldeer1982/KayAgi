# [USACO23DEC] Train Scheduling P

## 题目背景

**Note: The memory limit for this problem is 512MB, twice the default.**

## 题目描述

Bessie 找到了一份行车调度的新工作。现在有两座火车站 $A$ 和 $B$，由于预算限制，只有一条单线铁道连接起车站 $A$ 和 $B$。如果一列列车在 $t$ 时刻离开其中一座火车站，它将在 $t+T$（$1 \le T \le 10^{12}$）时刻到达另一座火车站。

现在有 $N$（$1 \le N \le 5000$）列火车的出发时间需要安排。第 $i$ 列火车必须在 $t_i$ 时刻后从车站 $s_i$ 出发（$s_i\in \{A,B\}$，$0 \le t_i \le 10^{12}$）。在同一时刻不允许铁道上有相反方向的列车，否则它们会相撞。但是，假设火车有可以忽略的尺寸，在同一时刻，铁道上可以有许多相同方向的列车。

帮助 Bessie 安排每辆列车的出发时间，在不会相撞的前提下最小化总延误时间。假设第 $i$ 辆列车被安排在 $a_i$ 时刻出发，总延误为 $\sum\limits_{i=1}^n{a_i-t_i}$。

## 说明/提示

### 样例解释 1

唯一的一辆列车准点出发。

### 样例解释 2

有两种最佳方案。第一种是让列车 $2,3,4$ 准点出发，列车 $1$ 延误一分钟后出发。第二种是让列车 $1,2,3$ 准点出发，列车 $4$ 延误一分钟后出发。

### 样例解释 3

最佳方案是让列车 $1,3$ 准点出发，列车 $2$ 在时刻 $13$ 出发，列车 $4$ 在时刻 $23$ 出发。总延误为 $0+11+0+2=13$。

### 测试点性质

- 测试点 $5-6$ 满足 $N \le 15$。
- 测试点 $7-10$ 满足 $N \le 100$。
- 测试点 $11-14$ 满足 $N \le 500$。
- 测试点 $15-18$ 满足 $N \le 2000$。
- 测试点 $19-24$ 没有额外限制。

## 样例 #1

### 输入

```
1 95
B 63```

### 输出

```
0```

## 样例 #2

### 输入

```
4 1
B 3
B 2
A 1
A 3```

### 输出

```
1```

## 样例 #3

### 输入

```
4 10
A 1
B 2
A 3
A 21```

### 输出

```
13```

## 样例 #4

### 输入

```
8 125000000000
B 17108575619
B 57117098303
A 42515717584
B 26473500855
A 108514697534
B 110763448122
B 117731666682
A 29117227954```

### 输出

```
548047356974```

# 题解

## 作者：EnofTaiPeople (赞：9)

### 前情提要

数据过水导致错误 dp 只会 WA 两个点差评。

问题是我一来就认为那个错误做法很假随便 Hack 就没写。

这样的情况下还能上榜？

$833$ 分第 $10$ 名！

不过我本来就切不了这道题，因为我没想清楚，赛后还调试了两个小时才过。

### 设置状态

将 $A$ 存在数组 $a$ 中，$B$ 存在数组 $b$ 中，分别排序，设长度为 $n,m$。

容易发现同一时刻走过的火车形如 $a,b$ 中的前缀。

设 $f_{x,y}$ 表示 $a$ 中走了前 $x$ 个，$b$ 中走了前 $y$ 个，最后一次走 $A$ 这一边，出发时间为 $a_x$，之后要全部走完还需要的答案。

$g_{x,y}$ 即最后一次走 $B$ 这一边，出发时间为 $b_x$。

转移式很简单：$f_{x,y}\leftarrow f_{x+1,y}$，如果 $b_{y+1}\ge a_x+T$，可以 $f_{x,y}\leftarrow g_{x,y+1}$，$g$ 的转移同理。

### 其他转移

上面写了 $f_{x,y}\leftarrow g_{x,y+1}$ 是有条件的！


如果 $b_{y+1}<a_x+T$，下一步又想要走 $b$，该怎么办？

考虑这时会出现一次行走的末尾没有任何列车达到极限，不属于之前的任何一种状态。

发现这种情况一定形如两边交替只走 $T$ 的时间，最多不会超过 $n$ 次，所以枚举进行了多少次可以在 $O(n)$ 的时间内得出答案：
```cpp
ll sol(int tg,int x,int y,ll t){
    if(x>n||y>m)return 1e18;
    ll res=8e18,sum=0;
    while(1){
        if(x==n&&y==m){
            res=min(res,sum);
            break;
        }
        if(tg){// x ran.
            while(x<n&&a[x+1]<t)sum+=t-a[++x];
            if(x<n)res=min(res,sum+f[x+1][y]);
            if(y==m){
                if(x==n)res=min(res,sum);
                break;
            }
            if(b[y+1]>=t+K){
                res=min(res,sum+g[x][y+1]);
                break;
            }else tg=0,t+=K;
        }else{
            while(y<m&&b[y+1]<t)sum+=t-b[++y];
            if(y<m)res=min(res,sum+g[x][y+1]);
            if(x==n){
                if(y==m)res=min(res,sum);
                break;
            }if(a[x+1]>=t+K){
                res=min(res,sum+f[x+1][y]);
                break;
            }else tg=1,t+=K;
        }
    }
    return res;
}
```

直接调用这个函数会达到 $O(n^3)$，不能通过。

但你会发现对于每一个 $x$ 都会是同一种状态，因为这时第一步 $b$ 都会走到最后一个 $b_y\le a_x+k$ 的位置，于是对于 $x$ 记忆化即可，$g$ 的转移同理。

于是做完了，时空复杂度 $O(n^2)$：
```cpp
cin>>T>>K;
while(T--){
    cin>>s;
    if(s[0]=='A')cin>>a[++n];
    else cin>>b[++m];
}
a[++n]=0,b[++m]=0;
sort(a+1,a+n+1),sort(b+1,b+m+1);
for(i=1;i<=n;++i)A[i]=A[i-1]+a[i];
for(i=1;i<=m;++i)B[i]=B[i-1]+b[i];
for(i=0;i<=n+1;++i)
    for(j=0;j<=m+1;++j)
        f[i][j]=g[i][j]=3e18;
for(x=1;x<=n;++x){
    for(k=1;k<=m&&b[k]<a[x]+K;++k);
    tx[x]=k;
}
for(x=1;x<=m;++x){
    for(k=1;k<=n&&a[k]<b[x]+K;++k);
    ty[x]=k;
}
for(x=n;x;--x)
    for(y=m;y;--y){
        if(x==n&&y==m){
            f[x][y]=g[x][y]=0;
            continue;
        }
        f[x][y]=f[x+1][y];
        if(y==tx[x]-1){
            vf[x]=min(sol(0,x,tx[x]-1,a[x]+K),g[x][tx[x]]);
            // cln<<x<<" "<<tx[x]<<" "<<vf[x]<<endl;
        }
        if(x==ty[y]-1)vg[y]=min(sol(1,ty[y]-1,y,b[y]+K),f[ty[y]][y]);
        if(b[y+1]>=a[x]+K)f[x][y]=min(f[x][y],g[x][y+1]);
        else{
            v1=(a[x]+K)*(tx[x]-1-y)-(B[tx[x]-1]-B[y]);
            // cln<<(B[tx[x]-1]-B[y-1])<<endl;
            // cln<<x<<" "<<y<<" "<<v1<<endl;
            f[x][y]=min(f[x][y],vf[x]+v1);
        }
        g[x][y]=g[x][y+1];
        if(a[x+1]>=b[y]+K)g[x][y]=min(g[x][y],f[x+1][y]);
        else{
            v1=(b[y]+K)*(ty[y]-1-x)-(A[ty[y]-1]-A[x]);
            g[x][y]=min(g[x][y],vg[y]+v1);
            // cln<<(b[y]+K)*(ty[y]-1-x)<<endl;
            // cln<<y<<" "<<ty[y]<<" "<<vg[y]<<endl;
        }
        // cln<<x<<" "<<y<<" "<<f[x][y]<<" "<<g[x][y]<<endl;
    }
ll ans=min(f[1][1],g[1][1]);
printf("%lld\n",ans);
```

---

## 作者：Leo_SZ (赞：7)

暴力 + 乱搞优化过的。


---


先考虑朴素的 dp 会是怎么样的。

我们先把 $A$ 站的和 $B$ 站的分开来，按时间从小到大排序。

于是设 $f_{i,j,k}$ 表示 $A$ 站走了前 $i$ 辆，$B$ 站走了前 $j$ 辆，最后走的是来自 $A$ 站的，出发时刻为 $k$ 的最小延误时间和。同时设 $g_{i,j,k}$ 表示 $A$ 站走了前 $i$ 辆，$B$ 站走了前 $j$ 辆，最后走的是来自 $B$ 站的，出发时刻为 $k$ 的最小延误时间和。

转移并不复杂：

$$\begin{cases} f_{i, j, k} + \max(0,k-a_{i+1}) \to f_{i+1, j, \max(k,a_{i+1})} \\ f_{i, j, k} + \max(0,k+T-b_{j+1}) \to g_{i, j+1, \max(k+T,b_{j+1})} \\ g_{i, j, k} + \max(0,k-b_{j+1}) \to g_{i, j+1, \max(k,b_{j+1})} \\ g_{i, j, k} + \max(0,k+T-a_{i+1}) \to f_{i+1, j, \max(k+T,a_{i+1})}  \end{cases}$$

初始化：

$$\begin{cases} f_{0, 0, -T} \gets 0 \\ g_{0, 0, -T} \gets 0 \end{cases}$$

然而，直接存的话，$k$ 的那一维是存不下的。可以感觉一下，总的状态数并不多，于是可以尝试用 map。


---


接下来开始优化。

可以观察到，对于固定的 $i$ 和 $j$，$f_{i,j}$ 是具有一定的单调性的。即对于 $f_{i,j,k_1}$ 和 $f_{i,j,k_2}$，如果 $k_1 \lt k_2$，则一定有 $f_{i,j,k_1} \gt f_{i,j,k_2}$，否则 $f_{i,j,k_2}$ 就是无效的。$g_{i,j}$ 同理。

因此，我们每往 map 中加入某个元素的时候，与前后判断一下，动态地维护单调性。

MLE 了？那就滚动数组。

然后就可以通过 $N \leq 2000$ 的所有点。[洛谷提交记录（TLE）](https://www.luogu.com.cn/record/186876257)


---


尝试进一步优化时间。

把 map 换成 vector，只需要在往后转移之前，进行一次排序和单调性的处理，就能跑得飞快。

AC 代码：

```cpp
#include<bits/stdc++.h>
#define Maxn 5003
#define LL long long
using namespace std;
int n,tota,totb;
LL m,a[Maxn],b[Maxn];
vector<pair<LL,LL> > f[2][Maxn],g[2][Maxn],tmp;

void work(vector<pair<LL,LL> > &q){
	if(q.size() <= 1) return;
	sort(q.begin(), q.end());
	tmp.clear();
	
	for(pair<LL,LL> i : q){
		if(tmp.empty() || tmp.back().second > i.second){
			tmp.emplace_back(i);
		}
	}
	q.swap(tmp);
}

int main(){
	scanf("%d%lld",&n,&m);
	char op[5];
	LL x;
	for(int i=1; i<=n; i++){
		scanf("%s%lld",op,&x);
		(op[0] == 'A') ? (a[++tota] = x) : (b[++totb] = x);
	}
	sort(a+1, a+tota+1);
	sort(b+1, b+totb+1);
	
	f[0][0].emplace_back(-m, 0);
	g[0][0].emplace_back(-m, 0);
	int u, v;
	for(int i=0; i<=tota; i++){
		u = (i&1); v = (i&1)^1;
		for(int j=0; j<=totb; j++){
			f[v][j].clear();
			g[v][j].clear();
		}
		for(int j=0; j<=totb; j++){
//			cerr<<"\n"<<i<<" "<<j<<":\n";
			work(f[u][j]);
			for(pair<LL,LL> k : f[u][j]){
//				cerr<<k.first<<" "<<k.second<<"\n";
				if(i < tota){
					if(a[i+1] <= k.first){
						f[v][j].emplace_back(k.first, k.second+k.first-a[i+1]);
					} else {
						f[v][j].emplace_back(a[i+1], k.second);
					}
				}
				if(j < totb){
					if(b[j+1] <= k.first+m){
						g[u][j+1].emplace_back(k.first+m, k.second+k.first+m-b[j+1]);
					} else {
						g[u][j+1].emplace_back(b[j+1], k.second);
					}
				}
			}
//			cerr<<"--\n";
			work(g[u][j]);
			for(pair<LL,LL> k : g[u][j]){
//				cerr<<k.first<<" "<<k.second<<"\n";
				if(j < totb){
					if(b[j+1] <= k.first){
						g[u][j+1].emplace_back(k.first, k.second+k.first-b[j+1]);
					} else {
						g[u][j+1].emplace_back(b[j+1], k.second);
					}
				}
				if(i < tota){
					if(a[i+1] <= k.first+m){
						f[v][j].emplace_back(k.first+m, k.second+k.first+m-a[i+1]);
					} else {
						f[v][j].emplace_back(a[i+1], k.second);
					}
				}
			}
		}
	}
	u = tota&1; v = totb;
	if(f[u][v].empty()){
		printf("%lld\n", g[u][v].back().second); return 0;
	}
	if(g[u][v].empty()){
		printf("%lld\n", f[u][v].back().second); return 0;
	}
	printf("%lld\n", min(f[u][v].back().second, g[u][v].back().second));
	return 0;
}
```

洛谷单点最大 879ms，USACO 单点最大 1177ms。

---

## 作者：Acoipp (赞：4)

## 分析

比较显然的一个状态设计就是在 $A$ 站和 $B$ 站的火车时间从近到远排序之后，$f_{i,j,t}$ 表示 $A$ 站走了 $i$ 辆，$B$ 站走了 $j$ 辆，最后一个是 $A$ 站的火车，到达 $B$ 站的时间是 $t$ 的最小花费，$g_{i,j,t}$ 同理。

答案就是 $\min_{k}\{f_{n,m,k},g_{n,m,k}\}$。

但是这样的话是一个测试点也通过不了的（理论上来说），考虑优化状态设计。

于是我们不记录时间这一个维度，改为：

- $f_{i,j}$ 表示 $A$ 站的火车走了前 $i$ 辆，$B$ 站的火车走了前 $j$ 辆，$A$ 站第 $i$ 辆火车最后一个离开，离开时间是 $a_i$，剩下的车的延误时间总和最少是多少。

- $g_{i,j}$ 表示 $A$ 站的火车走了前 $i$ 辆，$B$ 站的火车走了前 $j$ 辆，$B$ 站第 $j$ 辆火车最后一个离开，离开时间是 $b_j$，剩下的车的延误时间总和最少是多少。

首先有几个比较显然的转移：

> $f_{i,j} \gets f_{i+1,j}$  
> $f_{i,j} \gets g_{i,j+1} (b_{j+1} \ge a_i+T)$  
> $g_{i,j} \gets g_{i,j+1}$  
> $g_{i,j} \gets f_{i+1,j} (a_{i+1} \ge b_j+T)$

但是我们可以发现还有一种转移就是 $b_{j+1} < a_i+T$ 我们仍然想让 $b_{j+1}$ 移动，此时它开始移动的时间就是 $a_i+T$，但是这个时间并不满足上面的任何一种状态，怎么办呢？

我们可以考虑这种情况一定是 $B$ 站的走几个，$A$ 站的走几个，一共不会超过 $n$ 个，直接暴力枚举即可。（这里读者可以自行画图理解一下）

现在我们做到了 $O(n^3)$ 的复杂度了，但是实测能过 $n \le 2 \times 10^3$ 的测试点。

## 优化

注意到我们每次都是让 $b_{j+1} < a_i+T$ 的 $j$ 移动到最大的 $k$ 满足 $b_{k} < a_i+T$ 并且 $b_{k+1} \ge a_i+T$，对于相同的 $i$ 来说这个 $k$ 值是固定的，因此我们可以记录当 $j=k-1$ 的时候的值，$j$ 每减去 $1$ 都要加上我们的增量 $a_i+T-b_{j+1}$。

这样时间复杂度就做到了 $O(n^2)$。

## 代码

代码如下，写得比较丑。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 5005
using namespace std;
ll n,m,t,tim,i,j,a[N],b[N],x,f[N][N],g[N][N],ff[N],gg[N];
char opt;
inline ll solve(ll tp,ll x,ll y,ll limit){
	ll ans = 0x3f3f3f3f3f3f3f3f,sum = 0;
	if(x>n||y>m) return ans;
	while(1){
		if(x==n&&y==m){
			ans=min(ans,sum);
			break;
		}
		if(tp==0){
			while(x+1<=n&&a[x+1]<limit) sum+=limit-a[++x];
			if(x<n) ans=min(ans,sum+f[x+1][y]);
			limit+=tim;
			if(y==m){
				if(x==n) ans=min(ans,sum);
				break;
			}
			if(b[y+1]>=limit){
				ans=min(ans,sum+g[x][y+1]);
				break; 
			}
		}
		else{
			while(y+1<=m&&b[y+1]<limit) sum+=limit-b[++y];
			if(y<m) ans=min(ans,sum+g[x][y+1]);
			limit+=tim;
			if(x==n){
				if(y==m) ans=min(ans,sum);
				break;
			}
			if(a[x+1]>=limit){
				ans=min(ans,sum+f[x+1][y]);
				break;
			}
		}
		tp ^= 1;
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>t>>tim;
	while(t--){
		cin>>opt>>x;
		if(opt=='A') a[++n]=x;
		else b[++m]=x;
	}
	a[++n]=0,b[++m]=0,sort(a+1,a+n+1),sort(b+1,b+m+1);
	memset(f,0x3f,sizeof(f)),memset(g,0x3f,sizeof(g));
	for(i=n;i>=1;i--){
		for(j=m;j>=1;j--){
			if(i==n&&j==m){f[i][j]=0,g[i][j]=0;continue;}
			if(i+1<=n) f[i][j]=min(f[i][j],f[i+1][j]);
			if(j+1<=m&&b[j+1]>=a[i]+tim) f[i][j]=min(f[i][j],g[i][j+1]);
			if(j+1<=m&&b[j+1]<a[i]+tim){
				if(j+2>m||b[j+2]>=a[i]+tim) ff[i]=solve(1,i,j,a[i]+tim);
				else ff[i]+=(a[i]+tim-b[j+1]);
				f[i][j]=min(f[i][j],ff[i]);
			} 
			//------------------------un-connect------------------------
			if(j+1<=m) g[i][j]=min(g[i][j],g[i][j+1]);
			if(i+1<=n&&a[i+1]>=b[j]+tim) g[i][j]=min(g[i][j],f[i+1][j]);
			if(i+1<=n&&a[i+1]<b[j]+tim){
				if(i+2>n||a[i+2]>=b[j]+tim) gg[j]=solve(0,i,j,b[j]+tim);
				else gg[j]+=(b[j]+tim-a[i+1]);
				g[i][j]=min(g[i][j],gg[j]);
			}
		}
	}
	cout<<min(f[1][1],g[1][1])<<endl;
	return 0;
}
```

---

## 作者：Purslane (赞：3)

# Solution

我的做法转移就是 $O(1)$ 而不是均摊 $O(1)$ 的，还比较好写，跑得快。

显然要将两个车站的列车划分为若干连续段，两个连续段交错排列。

考虑这样一个 DP：设 $dp_{i,j,t,0/1}$ 表示，当前期限是时间 $t$，两个车站分别走了 $i$ 和 $j$ 个人，最后一个添加的连续段是 $\rm A$ 还是 $\rm B$ 车站。

注意到 $t$ 一定是某个人卡到上界之后，不断按照 $+T$ 的形式得出的，所以 $t$ 可以写为 $t_x + yT$ 的形式，所以得到 $dp_{i,j,x,y,0/1}$。

注意到当 $x$ 给定，最优结构的形态就相对确定了——使用归纳法可以的得知（真的假的，感性理解是这样的），最小的 $y$ 一定对应最小的 $dp_{i,j,x,y}$。所以**可以把 $y$ 扔进状态里面**。所以状态只剩下 $dp_{i,j,x,0/1}$。

而 $x$ 显然要么是 $i$ 对应 $\rm A$ 的位置要么是 $j$ 对应的 $\rm B$ 的位置，所以可以变为 $dp_{i,j,0/1,0/1}$。

直接把你的 $O(n^4)$ 暴力往上套即可。复杂度 $O(n^2)$。

为啥题解区都没有这个解法啊？？

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5000+10;
int n,tp[MAXN];
ll T,t[MAXN],t0[MAXN],t1[MAXN];
pair<ll,ll> dp[2][MAXN][2][2];
pair<ll,ll> operator +(pair<ll,ll> A,pair<ll,ll> B) {return {A.first+B.first,A.second+B.second};}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>T;
	ffor(i,1,n) {char ch;cin>>ch>>t[i],tp[i]=ch-'A';}
	memset(dp,0x3f,sizeof(dp));
	int c0=0,c1=0;
	ffor(i,1,n) if(tp[i]==0) t0[++c0]=t[i]; else t1[++c1]=t[i];
	sort(t0+1,t0+c0+1),sort(t1+1,t1+c1+1);
	ffor(i,0,c0) {
		int s=i&1,l=s^1;
		memset(dp[s],0x3f,sizeof(dp[s]));
		if(i==0) dp[0][0][0][0]=dp[0][0][0][1]=dp[0][0][1][0]=dp[0][0][1][1]={0,T};
		ffor(j,0,c1) {
			if(i) {
				ffor(o,0,1) {
					auto nw=dp[l][j][o][0];
					if(nw.second-T>=t0[i]) dp[s][j][o][0]=min(dp[s][j][o][0],nw+make_pair(nw.second-T-t0[i],0));
					else dp[s][j][0][0]=min(dp[s][j][0][0],nw+make_pair(0,t0[i]+T-nw.second));
					nw=dp[l][j][o][1];
					if(nw.second>=t0[i]) dp[s][j][o][0]=min(dp[s][j][o][0],nw+make_pair(nw.second-t0[i],T));
					else dp[s][j][0][0]=min(dp[s][j][0][0],nw+make_pair(0,t0[i]+T-nw.second));
				}
			}
			if(j) {
				ffor(o,0,1) {
					auto nw=dp[s][j-1][o][1];
					if(nw.second-T>=t1[j]) dp[s][j][o][1]=min(dp[s][j][o][1],nw+make_pair(nw.second-T-t1[j],0));
					else dp[s][j][1][1]=min(dp[s][j][1][1],nw+make_pair(0,t1[j]+T-nw.second));
					nw=dp[s][j-1][o][0];
					if(nw.second>=t1[j]) dp[s][j][o][1]=min(dp[s][j][o][1],nw+make_pair(nw.second-t1[j],T));
					else dp[s][j][1][1]=min(dp[s][j][1][1],nw+make_pair(0,t1[j]+T-nw.second));
				}
			}
		}
	}
	ll ans=LONG_LONG_MAX;
	ffor(o1,0,1) ffor(o2,0,1) ans=min(ans,dp[c0&1][c1][o1][o2].first);
	cout<<ans;
	return 0;
}
```

---

## 作者：Little09 (赞：3)

首先将 A，B 按时间排序。最暴力的 DP 是 $dp_{0/1,i,j,t}$ 表示 A，B 分别完成了前缀 $i$ 和 $j$，上一个完成的是 A 还是 B，目前时间是 $t$ 的最小代价，转移直接枚举下一个做 A 还是 B 即可，如果选择不同的就需要将时间 $+T$ 并取 $\max$。由于 $t$ 的值域过大，暴力实现的时候使用 map，可以获得 $40$ 分。原因是 $t$ 只可能是某个 $a_i$ 或 $b_i$ 加上 $kT$，复杂度 $O(n^4)$。

状态数太大几乎不行，这启发我们换个状态，$dp_{0/1,i,j}$ 直接表示 A，B 分别完成了前缀 $i$ 和 $j$，上一个完成的是 A 还是 B，目前时间恰好就是上一个的时间的最小代价。注意到这样我们省去了 $t$ 这一维，但转移会较为复杂。我们需要从 $dp_{0/1,i,j}$ 转移到许多状态，也就是用 $a_i$ 开始每次 $+T$ 交替走所产生的贡献。统计这些贡献看起来不容易，但可以发现从 $(i,j)$ 出发如果要求每次都必须产生交叉的贡献，那么走法是唯一的，并且容易计算。那么每次统计所有交叉的贡献，需要 $O(n)$ 转移，复杂度 $O(n^3)$。这里用刷表实现。

```cpp
const int N=5005;
int n,m,s; 
ll t,a[N],b[N],ans=inf;
ll dp[2][N][N];

void update(bool tp,int x,int y,ll k,ll res)
{
	while (x<n||y<m)
	{
		if (tp==0)
		{
			while (x<n&&a[x+1]<=k) res+=k-a[x+1],x++;
			if (x<n) chkmin(dp[0][x+1][y],res);
			if (y==m) break;
			if (b[y+1]<k+t) k+=t,res+=k-b[y+1],y++,tp^=1;
			else 
			{
				chkmin(dp[1][x][y+1],res);
				break;
			}
		}
		else
		{
			while (y<m&&b[y+1]<=k) res+=k-b[y+1],y++;
			if (y<m) chkmin(dp[1][x][y+1],res);
			if (x==n) break;
			if (a[x+1]<k+t) k+=t,res+=k-a[x+1],x++,tp^=1;
			else 
			{
				chkmin(dp[0][x+1][y],res);
				break;
			}
		}
	}
	if (x==n&&y==m) chkmin(ans,res);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> s >> t;
	rep(i,1,s)
	{
		char x;
		cin >> x;
		if (x=='A')
		{
			++n;
			cin >> a[n];
		}
		else
		{
			++m;
			cin >> b[m];
		}
	}
	sort(a+1,a+n+1),sort(b+1,b+m+1);
	rep(i,0,n) rep(j,0,m) dp[0][i][j]=dp[1][i][j]=inf;
	dp[0][0][0]=0,dp[1][0][0]=0;
	rep(i,0,n) rep(j,0,m)
	{
		if (i!=n) chkmin(dp[0][i+1][j],dp[0][i][j]);
		if (j!=m) chkmin(dp[1][i][j+1],dp[1][i][j]);
		update(0,i,j,a[i],dp[0][i][j]);
		update(1,i,j,b[j],dp[1][i][j]);
	}
	chkmin(ans,min(dp[0][n][m],dp[1][n][m]));
	cout << ans;
	return 0;
}
```

当然这个复杂度还是过不去，但是我们已经把刚才的三维以上的状态改成了二维状态，线性转移了。那么现在的目标就是优化这个转移函数。

对这个转移函数进行观察，考虑传进去的参数 $tp=0$ 且 $x$ 固定，那么我们只要考虑 $b_{y+1}<k+T$ 的情况，且在这个情况下 $y$ 就会直接一路移动到第一个 $>k+T$ 的位置。所以对于相同的 $x$ 传进来不同的 $y$，我们发现 $k$ 值的变化是相同的。所以我们对“移动到第一个 $>k+T$ 的位置”的过程记忆化，就可以实现对于一个 $x$，转移函数均摊 $O(n)$。总复杂度 $O(n^2)$，可以通过这个题。

具体记忆化的过程可以参考代码，总之就是在刚才的刷表法基础上添加了几行代码，从而省去了无效操作。

```cpp
const int N=5005;
int n,m,s; 
ll t,a[N],b[N],ans=inf;
ll dp[2][N][N],g[2][N][N];

void update(bool tp,int x,int y,ll k,ll res)
{
	if (tp==0&&y<m&&b[y+1]<k+t)
	{
		k+=t,res+=k-b[y+1],y++,tp^=1;
		chkmin(res,g[0][x][y]);
		if (y<m&&b[y+1]<=k) 
		{
			chkmin(g[0][x][y+1],res+k-b[y+1]);
			return;
		}
		else
		{
			chkmin(dp[1][x][y+1],res);
		}
	}
	else if (tp==1&&x<n&&a[x+1]<k+t)
	{
		k+=t,res+=k-a[x+1],x++,tp^=1;
		chkmin(res,g[1][x][y]);
		if (x<n&&a[x+1]<=k) 
		{
			chkmin(g[1][x+1][y],res+k-a[x+1]);
			return;
		}
		else
		{
			chkmin(dp[0][x+1][y],res);
		}
	}
	while (x<n||y<m)
	{
		if (tp==0)
		{
			while (x<n&&a[x+1]<=k) res+=k-a[x+1],x++;
			if (x<n) chkmin(dp[0][x+1][y],res);
			if (y==m) break;
			if (b[y+1]<k+t) k+=t,res+=k-b[y+1],y++,tp^=1;
			else 
			{
				chkmin(dp[1][x][y+1],res);
				break;
			}
		}
		else
		{
			while (y<m&&b[y+1]<=k) res+=k-b[y+1],y++;
			if (y<m) chkmin(dp[1][x][y+1],res);
			if (x==n) break;
			if (a[x+1]<k+t) k+=t,res+=k-a[x+1],x++,tp^=1;
			else 
			{
				chkmin(dp[0][x+1][y],res);
				break;
			}
		}
	}
	if (x==n&&y==m) chkmin(ans,res);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> s >> t;
	rep(i,1,s)
	{
		char x;
		cin >> x;
		if (x=='A')
		{
			++n;
			cin >> a[n];
		}
		else
		{
			++m;
			cin >> b[m];
		}
	}
	sort(a+1,a+n+1),sort(b+1,b+m+1);
	n=unique(a+1,a+n+1)-a-1;
	m=unique(b+1,b+m+1)-b-1;
	rep(i,0,n) rep(j,0,m) dp[0][i][j]=dp[1][i][j]=inf;
	rep(i,0,n) rep(j,0,m) g[0][i][j]=g[1][i][j]=inf;
	dp[0][0][0]=0,dp[1][0][0]=0;
	rep(i,0,n) rep(j,0,m)
	{
		if (i!=n) chkmin(dp[0][i+1][j],dp[0][i][j]);
		if (j!=m) chkmin(dp[1][i][j+1],dp[1][i][j]);
		update(0,i,j,a[i],dp[0][i][j]);
		update(1,i,j,b[j],dp[1][i][j]);
	}
	chkmin(ans,min(dp[0][n][m],dp[1][n][m]));
	cout << ans;
	return 0;
}
```


---

## 作者：Harry27182 (赞：1)

部分参考了 EnofTaiPeople 老师的题解，并进行了一些思维路径和细节的补充和拓展。

首先要把 A 和 B 分别按顺序排序，然后有一个显然的思路是记录 $dp_{i,j,k,l,0/1,0/1}$ 表示 A 做到 $i$，B 做到 $j$，当前时刻是 $a_k+l\times T$，是 $a_k$ 还是 $b_k$，上一个走的 A 还是 B 的最小答案，转移比较简单，复杂度 $O(n^4)$。

然后发现 $l$ 这一维一定是越小越优，所以可以去掉这一维并记录进 dp 值，时间复杂度 $O(n^3)$。

发现我们状态已经达到了 $O(n^3)$ 级别，想要优化必须再去掉一维，显然 $i$ 和 $j$ 都是不能去掉的，所以考虑去掉 $k$ 这一维，更改状态 $f_{i,j}$ 表示先走 A，并且这一位上的 A 是满足发车时间和 $a_i$ 相同的。类似地设计 $g_{i,j}$ 状态，这样就把状态压到了 $O(n^2)$ 级别。考虑如何转移。

下面以 $f$ 为例说明转移。首先有 $f_{i,j}\rightarrow f_{i+1,j}$，不需要代价。然后如果满足 $b_{j+1}\geq a_i+T$，那么可以进行一个 $f_{i,j}\rightarrow g_{i,j+1}$，否则一定是在 AB 交替走一段长度为 $T$ 的时间，把能启动的全部启动，这样显然是不劣于留一些不走的。所以可以模拟这个过程，最多交换 $O(n)$ 次就会到达终点，所以转移的复杂度是 $O(n)$ 的，总的复杂度仍然是 $O(n^3)$，但是显然更有前途一些。

发现这样其实没什么前途，刷表法并不好优化，即使能优化代码实现上也并不简单，填表法发现没法处理出来每个点是从哪来的，这样就陷入了瓶颈。我们考虑正难则反，把状态改为当前已经昨晚前面一部分，还需要多少的代价才能解决问题。这样做的好处是，固定前面状态处理后面状态的过程，前面是刷表现在就变成了填表，而填表一般是比刷表好优化的。而从后面状态去处理前面状态的过程，由于映射是一对多的不确定性，并没有优化前途。这样我们就把有优化前途的一部分变成了填表，这一部分的映射是一对一的。考虑如何利用这个映射的唯一性。

发现如果 $f_{i,j}$ 往后走的过程，下面的位置其实是与 $j$ 无关的，一定是走到最后一位满足 $b_k<a_i+T$ 的 $k$，$g$ 的转移同理。所以这就意味着，转移除了第一段，$i$ 相同 $j$ 不同时是一样的，考虑预处理出来 $k$ 对应的最小值，对于其他的 $j<k$ 只需要加上前面一节前缀和即可。由于只需要预处理 $O(n)$ 个位置，所以这部分复杂度就是 $O(n^2)$ 的了，而转移也被优化为了 $O(1)$，所以总的复杂度就是 $O(n^2)$。

回顾这题，做了一个变 $3d/0d$ 为 $2d/1d$，让算法有了优化的可能性。然后又考虑到映射的唯一性，选择将状态反向，从而能把映射唯一的情况对应较为简单的填表法的操作。所以，我个人认为这是一道非常有代表性的 dp 优化好题。

代码细节比较多，本人部分参考了 EnofTaiPeople 老师的实现，在此感谢。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int k,T,n,m,x,a[5005],b[5005],f[5005][5005],g[5005][5005];char op[10];
int suma[5005],sumb[5005],nxt1[5005],nxt2[5005],val1[5005],val2[5005];
int solve(int op,int x,int y,int t)
{
	int res=1e18,sum=0;
	while(1)
	{
		if(x==n&&y==m){res=min(res,sum);break;}
		if(op)  
		{
			while(x<n&&a[x+1]<t)sum+=t-a[++x];
			if(x<n)res=min(res,sum+f[x+1][y]);
			if(y==m){res=min(res,sum);break;}
			if(b[y+1]>=t+T){res=min(res,sum+g[x][y+1]);break;}
			else op=0,t+=T;
		}
		else 
		{
			while(y<m&&b[y+1]<t)sum+=t-b[++y];
			if(y<m)res=min(res,sum+g[x][y+1]);
			if(x==n){res=min(res,sum);break;}
			if(a[x+1]>=t+T){res=min(res,sum+f[x+1][y]);break;}
			else op=1,t+=T;
		}
	}
	return res;
}
signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin>>k>>T;
    for(int i=1;i<=k;i++)
    {
    	cin>>op>>x;
    	if(op[0]=='A')a[++n]=x;
    	else b[++m]=x;
	}
	a[++n]=0;b[++m]=0;
	sort(a+1,a+n+1);sort(b+1,b+m+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)if(b[j]<a[i]+T)nxt1[i]=j;
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)if(a[j]<b[i]+T)nxt2[i]=j;
	}
	for(int i=0;i<=n+1;i++)for(int j=0;j<=m+1;j++)f[i][j]=g[i][j]=1e18;
	for(int i=1;i<=n;i++)suma[i]=suma[i-1]+a[i];
	for(int i=1;i<=m;i++)sumb[i]=sumb[i-1]+b[i];
	f[n][m]=g[n][m]=0;
	for(int i=n;i;i--)
	{
		for(int j=m;j;j--)
		{
			if(i==n&&j==m)continue;
			if(j==nxt1[i])val1[i]=solve(0,i,j,a[i]+T);
			if(i==nxt2[j])val2[j]=solve(1,i,j,b[j]+T);
			f[i][j]=min(f[i][j],f[i+1][j]);
			if(b[j+1]>=a[i]+T)f[i][j]=min(f[i][j],g[i][j+1]);
			else f[i][j]=min(f[i][j],val1[i]+(a[i]+T)*(nxt1[i]-j)-(sumb[nxt1[i]]-sumb[j]));
			g[i][j]=min(g[i][j],g[i][j+1]);
			if(a[i+1]>=b[j]+T)g[i][j]=min(g[i][j],f[i+1][j]);
			else g[i][j]=min(g[i][j],val2[j]+(b[j]+T)*(nxt2[j]-i)-(suma[nxt2[j]]-suma[i]));
		}
	}
	cout<<min(f[1][1],g[1][1])<<'\n';
	return 0;
}
```

---

## 作者：Albert_van (赞：0)

[题](https://www.luogu.com.cn/problem/P9985)。看到题想到[摆渡车](https://www.luogu.com.cn/problem/P5017)和最近的 [Shipping](https://www.luogu.com.cn/problem/AT_abc374_f) 这一类题，都是发车之后间隔 $T$ 才能再次发车并最小化等待时间（这题是一端发车完毕后间隔 $T$ 另一端才能发车）。那两题的核心想法就是，把发车时刻集合划分为若干形如“某个 $t_i$ 开始**连续地每隔 $T$ 发一班车**”（可以只发一班），DP 状态定义为 $f(i)$ 表示“（按 $t$ 排序后）第 $i$ 辆车开始准备连续发车，此时前 $i$ 辆车等待时间和的最小值”，设置哨兵 $t_{n+1}=\inf$ 那么答案即为 $f(n+1)$，转移枚举上次开始连续发车的时间点即可，$\mathcal O(n^2)$，Shipping 那题要加一维状态记录 $k$。

考虑搬到这题。两座车站的车子分别按 $t$ 排序存进 $a$ 和 $b$ 里。第一直觉是想一维状态能不能直接做，发现有点问题，因为在做同一端不断发车的转移时，你无法实时获知对向列车的等待时间和。

![](https://s3.bmp.ovh/imgs/2024/12/10/9be8c71a0400deb5.png)

（类似柳卡图，纵轴时间，线是列车的行进，点是左/右端列车出现的时间点。考虑 $i$ 为左端蓝点的情况，按照摆渡车的做法，图中对应的转移是 $f(i)\gets f(i-1)$ 即从上一个蓝点【红点】转移过来，但同时要考虑到 $f(i)$ 从绿点转移的情况，仅靠 $i$ 一维状态无法获知有哪些绿点在等待发车）

那自然想到加一维状态。左侧 $n$ 辆车，右侧 $m$ 辆车，$f(x,y)(b_y\le a_x-T)$ 表示：左侧第 $x$ 辆车**准备连续发车**（这辆车开走后，左侧不再发车，间隔 $T$ 后右侧积压的车辆全部发车，如此左右交替，可以只发一次）、右侧的前 $y$ 辆车**已经全部开出**，此时左侧前 $x$ 辆和右侧前 $y$ 辆的最小等待时间和；$f(x,y)(a_x\le b_y-T)$ 同理。例子，图中 $x$ 为蓝/红点、$y$ 为黄点时状态有良定义。

转移两种，一是 $f(x,y)\to f(x+1,y),f(x,y+1)$，二是左右交替的连续发车，这个用刷表法做，一轮左右交替不会超过 $n$ 次，直接实现是 $\Theta(n^3)$ 的。发现你做这个刷表，以 $b_y\le a_x-T$ 为例，实际上只关心 $x$ 的值以及一个贡献 $s_y$ 等于 $f(x,y)$ 加上 $y$ 以后的、时间点在 $a_x+T$ 以前的右侧车辆（例子，图中绿点）等待时间和，那么取 $\min\{s_y\}$ 去刷表即可，一个 $x$ 只用刷一轮，整体 $\mathcal O(n^2)$。实现细节：

- 新建两个哨兵 $a_{n+1}=2\times 10^{12},b_{m+1}=3\times 10^{12}$。
- $x$ 和 $y$ 只有一个能放在外层枚举。$x$ 放外层，内层枚举 $y$，对于一个 $y$ 找到最大的 $a_x\le b_y-T$ 时，从 $y$ 开始做一轮左右交替刷表。
- 停止刷表的判断，就是某次去对面并折返形成的长 $2\times T$ 的时间段内本侧没有车，此时从对面折返后退出。
- $x=0/y=0$ 的边界问题。
- 多次涉及查找某个 $a_i/b_i+kT$ 的时间点前后最近的车子。偷懒直接二分了，所以实际上是 $\mathcal O(n^2\log n)$ 的，精细可以离线扫一遍严格 $\mathcal O(n^2)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long

using namespace std;

void cmn(ll& x,ll y){if(x>y) x=y;}

const int N=5141;

int n,m;ll a[N],b[N],sa[N],sb[N],f[N][N],T;

void ext(int p,int q,ll t,ll s,bool sid,bool brk){switch(sid){
	case 0:{
		int y=lower_bound(b+1,b+m+1,t+T)-b;
		cmn(f[p][y],s);if(brk) return ;
		int x=upper_bound(a+1,a+n+1,t+2*T)-1-a;
		ext(q,x,t+T,s+(x-p)*(t+2*T)-(sa[x]-sa[p]),1,x==p);
		break;
	}case 1:{
		int x=lower_bound(a+1,a+n+1,t+T)-a;
		cmn(f[x][p],s);if(brk) return ;
		int y=upper_bound(b+1,b+m+1,t+2*T)-1-b;
		ext(q,y,t+T,s+(y-p)*(t+2*T)-(sb[y]-sb[p]),0,y==p);
		break;
	}
}}

int X[N],Y[N];ll t[N];

//#include "xzr.hpp"

int main()
{
	//wxd;//Xzr;
	int M;scanf("%d%lld",&M,&T);while(M--){
		char s[3];ll x;scanf("%s%lld",s,&x);switch(s[0]){
			case'A':a[++n]=x;break;
			case'B':b[++m]=x;break;
		}
	}
	a[++n]=2e12;b[++m]=3e12;a[n+1]=b[m+1]=1e18;
	sort(a+1,a+n+1);sort(b+1,b+m+1);
	for(int x=1;x<=n;++x) sa[x]=sa[x-1]+a[x];
	for(int y=1;y<=m;++y) sb[y]=sb[y-1]+b[y];
	for(int x=1,y=1;x<=n;++x){
		while(b[y]<=a[x]+T) ++y;
		--y;Y[x]=y;
	}
	for(int y=1,x=1;y<=m;++y){
		while(a[x]<=b[y]+T) ++x;
		--x;X[y]=x;
	}
	memset(t,63,sizeof(t));memset(f,63,sizeof(f));f[0][0]=0;
	for(int x=0;x<=n;++x){ll s=1e18;
		for(int y=0;!y||b[y]<=a[x]-T;++y) cmn(f[x+1][y],f[x][y]),
			cmn(s,f[x][y]+(Y[x]-y)*(a[x]+T)-(sb[Y[x]]-sb[y]));
		if(x) ext(x,upper_bound(b+1,b+m+1,a[x]+T)-1-b,a[x],s,0,0);
		for(int y=x?Y[x]+(b[Y[x]]<a[x]+T):0;y<=m;++y){
			cmn(t[y],f[x][y]+(X[y]-x)*(b[y]+T)-(sa[X[y]]-sa[x]));
			if(a[x+1]>b[y]-T) ext(y,upper_bound(a+1,a+n+1,b[y]+T)-1-a,b[y],t[y],1,0);
			cmn(f[x][y+1],f[x][y]);
		}
	}
	printf("%lld",f[n][m]);
}
```

---

