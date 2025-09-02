# [POI 2016] Park wodny

## 题目描述

给出一个 $n\times n$ 的四连通的网格图，每个格子要么是 `A`，要么是 `B`，保证 `B` 的连通块的形状都是矩形。

现在你最多可以把两个 `A` 变成 `B`，问最大的 `B` 的连通块有多大。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 10^3$。

## 样例 #1

### 输入

```
5
BBBAB
BBBAB
AAAAA
BBABA
BBAAB```

### 输出

```
14
```

# 题解

## 作者：ttq012 (赞：5)

考虑分类讨论。

首先枚举每一个强连通 $B$ 块。

情况 $1$：

[![pPUUgxK.png](https://s1.ax1x.com/2023/08/27/pPUUgxK.png)](https://imgse.com/i/pPUUgxK)

+ 任意的一个连通块都无法通过扩展两个点的方式和其他的连通块连通。
+ 对于每一个这样的连通块，这个连通块得到的最大贡献是 $s+2$，其中 $s$ 是连通块的大小。

情况 $2$：

[![pPUUWrD.png](https://s1.ax1x.com/2023/08/27/pPUUWrD.png)](https://imgse.com/i/pPUUWrD)

+ 对于 `ABCDEF` 组成的连通块而言，可以通过对周围扩展和其他的两个连通块连接，贡献为 $3$ 个连通块的大小的和 $+2$。
+ 贪心选择两个最大的连通块即可。

情况 $3$：

[![pPUUIIA.png](https://s1.ax1x.com/2023/08/27/pPUUIIA.png)](https://imgse.com/i/pPUUIIA)

+ 上述的两个连通块可以通过扩展两个点来连通，贡献为两个连通块的大小 $+2$。

由于 $B$ 部分是矩形，所有矩形的周长的和是 $n^2$ 级别的，所以直接暴力模拟即可。

---

## 作者：Zpair (赞：2)

先把所有 B 连通块缩在一起，这一部分可以维护每一个点对应连通块的左上角实现，时间复杂度可以做到 $O(n^2)$。

首先有三种情况：两个 A 未对连通性产生影响的，两个 A 分别在两个位置连通若干个连通块的，两个 A 在一起连通若干个连通块的。

第一种情况只需将最大连通块大小 $+2$ 即可。

其余情况考虑暴力枚举一个 A 的位置。

对于第三种情况，第二个 A 一定在第一个 A 四连通的范围内，也可以暴力枚举。然后只需检查其四连通范围内连通块大小之和即可。

显然一三情况的部分时间复杂度为 $O(n^2)$。

考虑二情况，第一个加入的 A 最多只会合并 $4$ 个连通块，而且下一个 A 选择的位置一定会在其合并的连通块边界上，否则一定不优。

考虑对于每一个连通块，维护出其边界上将一个 A 变为 B 所带来的贡献，将所有不同类，也就是取这个 A 使得会连通性发生不同改变的情况丢到 `set` 里，`set` 中按它能合并的连通块大小之和从大到小排序。

我们不妨令：$S$ 为当前枚举的 A 能合并的连通块集合，$x$ 为其中任意一个元素。 

此时考虑 $S$ 对 $x$ 边界上 A 变为 B 贡献的影响，如果它原本能合并的连通块包含一部分 $S$，就会让它原本能合并的连通块中 $S$ 的部分直接变成一个。

这里给出一个观察：两个 B 构成的矩形，要求必须连通它们两个，则能带来不同连通性的 A 位置最多只有两个。

所以 $x$ 中受影响的点最多只有 $2(|S|-1)$ 个，也就是 $6$ 个，所以去除其影响只需维护 $7$ 个即可。

进一步的，当 $|S|$ 取 $4$ 时一定会有两个矩形相对，所以维护 $6$ 个即可。

但是这样可能会 MLE，注意到连通块个数不会超过 $\frac {n^2} 2$，所以第一维开 $\frac {n^2} 2$ 即可。

所以直接枚举 $S$，再枚举其 `set` 里的元素，将其对于 $S$ 的贡献去掉再取 $\max$ 即可。

时间复杂度为 $O(n^2)$。

这里给出一份参考实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
const int T=1e6+5;
int n,fa[T],siz[T];
int v(int x,int y){
	return (x-1)*n+y;
}
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
bool check(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=n;
}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(!x||!y||x==y)return;
	if(siz[x]<siz[y])swap(x,y);
	fa[y]=x,siz[x]+=siz[y];
}
char s[N][N];
struct node{
	int a[4],len,sum;
	node(){memset(a,0,sizeof(a)),len=sum=0;}
	bool operator <(const node &ret)const{
		return sum<ret.sum;
	}
	bool operator ==(const node &ret)const{
		if(len!=ret.len||sum!=ret.sum)return false;
		for(int i=0;i<len;++i)
			if(a[i]!=ret.a[i])
				return false;
		return true;
	}
};
node mx[T>>1][6];
int mp[T],tot;
int ans=2;
int fx[]={1,-1,0,0},fy[]={0,0,1,-1};
bool vis[T];
int ins(int i,int j){
	int sum=0;
	for(int k=0;k<4;++k){
		int x=i+fx[k],y=j+fy[k];
		if(!check(x,y)||s[x][y]!='B')continue;
		int f=find(v(x,y));
		if(!vis[f])vis[f]=1,sum+=siz[f];
	}
	return sum;
}
void clear(int i,int j){
	for(int k=0;k<4;++k){
		int x=i+fx[k],y=j+fy[k];
		if(!check(x,y)||s[x][y]!='B')continue;
		int f=find(v(x,y));vis[f]=0;
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;++i)
		scanf("%s",s[i]+1);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			fa[v(i,j)]=v(i,j),siz[v(i,j)]=1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(s[i][j]=='B'){
				if(i!=1&&s[i-1][j]=='B')merge(v(i-1,j),v(i,j));
				if(i!=n&&s[i+1][j]=='B')merge(v(i+1,j),v(i,j));
				if(j!=1&&s[i][j-1]=='B')merge(v(i,j-1),v(i,j));
				if(j!=n&&s[i][j+1]=='B')merge(v(i,j+1),v(i,j));
			}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(s[i][j]!='B'){
				node val;
				if(i!=1&&s[i-1][j]=='B')val.a[val.len++]=find(v(i-1,j));
				if(i!=n&&s[i+1][j]=='B')val.a[val.len++]=find(v(i+1,j));
				if(j!=1&&s[i][j-1]=='B')val.a[val.len++]=find(v(i,j-1));
				if(j!=n&&s[i][j+1]=='B')val.a[val.len++]=find(v(i,j+1));
				sort(val.a,val.a+val.len);
				for(int k=0;k<val.len;++k)
					val.sum+=siz[val.a[k]];
				for(int k=0;k<4;++k){
					int nx=i+fx[k],ny=j+fy[k];
					if(!check(nx,ny)||s[nx][ny]!='B')continue;
					int nv=find(v(nx,ny));
					if(!mp[nv])mp[nv]=++tot;
					nv=mp[nv];
					for(int l=0;l<6;++l){
						if(mx[nv][l]==val)
							break;
						if(mx[nv][l]<val){
							for(int t=4;t>=l;--t)
								mx[nv][t+1]=mx[nv][t];
							mx[nv][l]=val;
							break;
						}
					}
				}
			}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(s[i][j]=='B')
				ans=max(ans,siz[find(v(i,j))]+2);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(s[i][j]!='B')
				for(int k=0;k<4;++k){
					int x=i+fx[k],y=j+fy[k];
					if(!check(x,y)||s[x][y]=='B')continue;
					int sum=ins(i,j),sum2=ins(x,y);
					ans=max(ans,sum+sum2+2);
					clear(i,j),clear(x,y);
				}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j){
			if(s[i][j]!='B'){
				int sum=0;
				for(int k=0;k<4;++k){
					int nx=i+fx[k],ny=j+fy[k];
					if(!check(nx,ny)||s[nx][ny]!='B')continue;
					int nv=find(v(nx,ny));
					vis[nv]=1,sum+=siz[nv];
				}
				for(int k=0;k<4;++k){
					int nx=i+fx[k],ny=j+fy[k];
					if(!check(nx,ny)||s[nx][ny]!='B')continue;
					int nv=find(v(nx,ny));nv=mp[nv];
					for(int l=0;l<6;++l){
						int sum2=mx[nv][l].sum;
						for(int t=0;t<mx[nv][l].len;++t)
							if(vis[mx[nv][l].a[t]])
								sum2-=siz[mx[nv][l].a[t]];
						ans=max(ans,sum+2+sum2);
					}
				}
				for(int k=0;k<4;++k){
					int nx=i+fx[k],ny=j+fy[k];
					if(!check(nx,ny)||s[nx][ny]!='B')continue;
					int nv=find(v(nx,ny));
					vis[nv]=0;
				}
			}
		}
	cout<<min(ans,n*n);
}
```

实现中使用了并查集，也可以维护每个点左上角的 B 位置然后扫一遍做到严格 $O(n^2)$。

update：现在全 A 的 corner case 也可以过了。

---

