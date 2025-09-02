# Graph

## 题目描述

You are given an undirected graph where each edge has one of two colors: black or red.

Your task is to assign a real number to each node so that:

- for each black edge the sum of values at its endpoints is $ 1 $ ;
- for each red edge the sum of values at its endpoints is $ 2 $ ;
- the sum of the absolute values of all assigned numbers is the smallest possible.

Otherwise, if it is not possible, report that there is no feasible assignment of the numbers.

## 说明/提示

Note that in the second example the solution is not unique.

## 样例 #1

### 输入

```
4 4
1 2 1
2 3 2
1 3 2
3 4 1```

### 输出

```
YES
0.5 0.5 1.5 -0.5```

## 样例 #2

### 输入

```
2 1
1 2 1```

### 输出

```
YES
0.3 0.7```

## 样例 #3

### 输入

```
3 2
1 2 2
2 3 2```

### 输出

```
YES
0 2 0```

## 样例 #4

### 输入

```
3 4
1 2 2
2 2 1
2 1 1
1 2 2```

### 输出

```
NO```

# 题解

## 作者：chen_hx (赞：4)

## 一个蒟蒻来水本题第一篇题解
### 分析
> 首先不难发现一条边$(u,v,w)$表示的是一个方程 $x_u+x_v=w$ ，那么问题就转换为了方程组是否有解，求出绝对值最小解的问题

### 实现
> 首先图是不一定联通的，但因为每个连通块是独立的，所以可以分开处理。对于一个连通块如果存在唯一解，就把这个唯一解求出来，具体可以使用。

> 对于一个连通块存在多解，那么不妨设其中一个点的值为 $x$ 然后用 $±x+b$ 的方式把其他点值表示出来。然后再回到这个连通块对于答案的贡献：
$$
\sum_{i=1}^{siz} \left\vert x-b_i\right\vert
$$
> 考虑绝对值之和的几何意义，可以把每个 $\left\vert x-b_i\right\vert$ 放到数轴上，显然让 $x$ 等于最中间的那一段（或者最中间的那一个点）的时候贡献最小，那么就排个序求出中间值即可

> 最后不要忘记用已知的那个点的值把其他点值推出来，整个算法的过程可以使用 ``` pair<int,int> ```来实现。

### 代码

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int> 
#define mpr make_pair
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch))f^=(ch=='-'),ch=getchar();
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return f?x:-x;
}
const int N=1e5+5,M=2e5+5;
const double eps=1e-6;
struct edge{
	int to,p,w;
}d[M*2];
int last[N],cnt,n,m,vis[N],calc[N],sta[N],stop,mvp[N];
double ans[N];
pii coe[N];
map<pii,int> use;
void charu(int x,int y,int z){
	d[++cnt]=edge{y,last[x],z};
	last[x]=cnt;
}
void solve(int s){
	coe[s]={1,0};
	queue<int> que;
	vis[s]=1;
	que.push(s);
	stop=0;
	while(que.size()){
		int u=que.front();
		sta[++stop]=u;
		que.pop();
		for(int e=last[u];e;e=d[e].p){
			int v=d[e].to,w=d[e].w;
			pii ev={-coe[u].first,w-coe[u].second};
			if(vis[v]){
				if(ev==coe[v])continue;
				if(ev.first==coe[v].first)exit(puts("NO")&0);
				double uu;
				uu=1.00*(coe[v].second-ev.second)/(1.00*(ev.first-coe[v].first));
				if(!calc[s])ans[s]=uu,calc[s]=1;
				else if(fabs(ans[s]-uu)>eps)exit(puts("NO")&0);
			}
			else{
				vis[v]=1;
				coe[v]=ev;
				que.push(v);
			}
		}
	}
	if(!calc[s]){
		for(int i=1;i<=stop;i++)
			mvp[i]=-coe[sta[i]].second/coe[sta[i]].first;
		sort(mvp+1,mvp+stop+1);
		ans[s]=mvp[(stop+1)/2];calc[s]=1;
	}
	for(int i=2;i<=stop;i++){
		ans[sta[i]]=coe[sta[i]].first*ans[s]+coe[sta[i]].second;
	}
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		if(use[mpr(x,y)]){
			if(use[mpr(x,y)]!=z)
				exit(0&puts("NO"));
			continue;
		}
		use[mpr(x,y)]=use[mpr(y,x)]=z;
		charu(x,y,z),charu(y,x,z);
	}
	for(int i=1;i<=n;i++)if(!vis[i])solve(i);
	puts("YES");
	for(int i=1;i<=n;i++)printf("%lf ",ans[i]);
}
```

> 事实证明，码力很重要的

---

## 作者：zjw806903 (赞：1)

# 0. 前言
由于已知题解的解释多少都有点......，所以这里主要是补个解释。

[题目链接](https://www.luogu.com.cn/problem/CF1387A)
## 1.1 改变题目

不难发现，如果我们设每个点点权为 $x_i$，那么原图可以看成若干个方程，我们可以将连通的点丢进一个方程组里面。

观察到显然这是一个一元一次方程组。也就是说，它实际上可以看成第一个点点权为 $x$，其他点点权是 $ax+b$，每条边就是一个方程。

那么，对于每条边，它连接的点的和一定为边权，所以我们可以推出所有点的点权。

接下来讲一个其他题解没讲到的部分。

## 1.2 如果有一个点可以被多个方程组表示

此时，他会出现这种情况：$a1x+b1=a2x+b2$，那么，我们可以直接移项，然后解出 $x$。此时 $x$ 就是固定的了。

## 1.3 计算 $x$

如果在 $1.2$ 中我们没有计算出 $x$，我们就需要这一步了。观察到最后的方程式可能 $x$ 的系数有正有负，所以通过绝对值的性质，我们可以将 $x$ 的系数都改成正的（如 $\left\vert -x-b_i\right\vert \rightarrow \left\vert x+b_i\right\vert$），接下来就是中位数最优，结束。

## 2. 代码

自认为讲得比较清晰了，就不给注释了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,c,flag[100005],edge[200005],len,hd[100005],gls=0;
double x=-11451419,ans[100005],num[100005][3],lq[100005];
struct l{
	int mb,qz,bh;
};
vector<l>lb[100005];
void dfs(int now){
	if(!flag[now]){
		hd[++len]=now;
	}
	flag[now]=1;
	for(int i=0;i<lb[now].size();i++){
		if(edge[lb[now][i].bh]){
			continue;
		}
		else{
			gls=1;
			edge[lb[now][i].bh]=1;
			int n1=-num[now][0],n2=lb[now][i].qz-num[now][1];
			if(int(num[lb[now][i].mb][2])){
				if((n2-num[lb[now][i].mb][1])==0&&0==(num[lb[now][i].mb][0]-n1)){
					continue;
				}
				if((num[lb[now][i].mb][0]-n1)==0){
					printf("NO");
					exit(0);
				}
				double nx=1.0*(n2-num[lb[now][i].mb][1])/(num[lb[now][i].mb][0]-n1);
				if(x==-11451419){
					x=nx;
				}
				if(x!=nx){
					printf("NO");
					exit(0);
				}
			}
			else{
				num[lb[now][i].mb][2]=1;
				num[lb[now][i].mb][0]=n1;
				num[lb[now][i].mb][1]=n2;
			}
			dfs(lb[now][i].mb);
		}
	}
} 
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		lb[a].push_back({b,c,i});
		lb[b].push_back({a,c,i});
	}
	for(int i=1;i<=n;i++){
		if(!flag[i]){
			x=-11451419;
			num[i][0]=1;
			len=0;
			gls=0;
			num[i][2]=1;
			dfs(i);
			if(gls==0){
				ans[hd[1]]=0;
				continue;
			}
			for(int j=1;j<=len;j++){
				ans[hd[j]]=num[hd[j]][1];
				lq[j]=-(num[hd[j]][1])*num[hd[j]][0];
			}
			sort(lq+1,lq+len+1);
			if(x==-11451419){
				x=lq[(len+1)/2];
			}
			for(int j=1;j<=len;j++){
				ans[hd[j]]=ans[hd[j]]+x*num[hd[j]][0];
				
			}
		}
	}
	printf("YES\n");
	for(int i=1;i<=n;i++){
		printf("%.6lf ",ans[i]);
	}//
	return 0;
} 
```

---

## 作者：Zikl (赞：1)

题目链接：[Graph](https://www.luogu.com.cn/problem/CF1387A)

闲话：本题唯一题解的马蜂太炸裂了。

------------
题解：

首先我们考虑什么情况不合法，显然，当两点之间同时出现 $1$ 和 $2$ 边时，不合法。除此之外，均有解。（可以考虑一个点为 $0$ 一个点为边权即可轻松构造）

接下来我们考虑怎么样构造最优方案。

首先，对于孤立的点，赋值为 $0$，然后处理剩下的联通块，我们给每个点两个量 $a$，$b$。我们随便找一个点（该点值为 $x$），使它的 $a = 1 $，$b = 0$。剩余的其他点，他们的值为 $a \times x + b$。假设我们从已知节点 $u$ 转移至 $v$，那么当边为 $1$ 时，$a_{v} = - a_{u}$，$b_{v} = 1 - b_{u}$，当边为 $2$ 时，$a_{v} = - a_{u}$，$b_{v} = 2 - b_{u}$。如果此时 $v$ 早已被更新，那我们检查它与所需赋的值是否矛盾，如果中途矛盾，那不合法。（矛盾的情况具体看代码）

如果我们已经找完，没有矛盾，那么 $x$ 为中位数时最优。（初中知识不做证明，并且第一篇题解此处已经讲得很好了）

my code：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue> 
#include<cmath>
#define pa pair<int,int>
#define mk make_pair 
#define fi first
#define sd second
#define F(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;
const int N=100005;
int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
int n,m;
int vis[N],a[N],b[N],top,flag,stack_[N],sum[N],ans[N],X;
vector<pa>e[N];
void dfs(int x){
	vis[x]=1;
	stack_[++top]=x;int dd=e[x].size()-1;
	F(i,0,dd){
		int y=e[x][i].fi,w=e[x][i].sd;
		if(vis[y]){
			if(a[x]+a[y]==0&&b[x]+b[y]!=w){
				printf("NO");
				exit(0);
			}//为什么a[x]+a[y]!=0可能合法呢，因为他们同时加减 x，所以改变 x 的值就行。 
			if(a[x]+a[y]!=0){
				int delta=(w-b[x]-b[y])/(a[x]+a[y]); 
				if(flag==1&&delta!=X){
				printf("NO");
				exit(0);
				}
				flag=1,X=delta; 
			}
		}
		else a[y]=-a[x],b[y]=w-b[x],dfs(y);
	}
}
signed main(){
	n=read(),m=read();
	F(i,1,m){
		int u=read(),v=read(),w=read();
		e[u].push_back(mk(v,w*2));
		e[v].push_back(mk(u,w*2));
	}
	F(i,1,n){
		if(vis[i]) continue;
		F(j,1,top) stack_[i]=0; 
		a[i]=1,b[i]=top=flag=0;
		dfs(i);
		//如果x在其中没有矛盾，那么取中位数 
		//不过sum数组不是这个意思
		//sum 让每个数加上 X 后尽量小，所以让 X 前的系数取了反 
		if(!flag){
			F(j,1,top)
			sum[j]=(-b[stack_[j]])/a[stack_[j]]; 
			sort(sum+1,sum+1+top);
			X=sum[(top+1)/2];//这个地方要注意 top 可能等于 1。
		}
		F(j,1,top) ans[stack_[j]]=b[stack_[j]]+a[stack_[j]]*X;
	}
	printf("YES\n");
	F(i,1,n)
	printf("%.2lf ",1.0*ans[i]/2);
	return 0;
} 	
```
感谢观看。（笔者不擅长使用 $\LaTeX$ 公式，所以语言表述不是很好，请各位见谅。

---

