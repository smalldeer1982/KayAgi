# [COTS 2012] 网格覆盖 / ARHIPELAG

## 题目描述

给定一个 $n\times m$ 的网格，每个网格上有一个数字。开始的时候所有的网格都是黑色。

但是过了 $t$ 秒后，所有网格上数字 $\le t$ 的网格会变为白色。

多组询问，每次给出一个 $t$，希望你求出 $t$ 秒后，有多少对黑色的四连通块的形状完全相同（不可旋转、对称）？

## 说明/提示


【样例解释】

![](https://cdn.luogu.com.cn/upload/image_hosting/4jk7c6se.png)

这是关于样例 $2$ 的图片解释。

【数据范围与约定】

记网格中 $(i,j)$ 位置的数为 $a_{i,j}$。

对于 $50 \%$ 的数据，满足 $n,m,q \le 50$。

对于 $100 \%$ 的数据，满足 $3\le n,m \le 10^3,1 \le Q \le 10^5,0\le a_{i,j}\le10^9$。



## 样例 #1

### 输入

```
5 6 
100 2 3 4 5 6  
20 4 45 12 3 4  
0 0 1 2 3 0  
0 0 0 0 0 0 
0 0 1 2 3 0 
3 
1 4 10 ```

### 输出

```
0
1
0
```

## 样例 #2

### 输入

```
7 6 
5 8 0 9 7 6 
7 0 0 9 2 6 
8 0 6 7 9 7 
0 0 8 7 0 0 
0 5 0 0 3 2 
0 9 0 0 6 0 
8 1 0 0 7 0 
1 
5 ```

### 输出

```
4```

# 题解

## 作者：Shunpower (赞：0)

哈希题。

----------

显然的想法：我们时光倒流，于是只需合并。每次对一个点周围的连通块进行合并最多只会改变 $\mathcal O(1)$ 个连通块，所以可以直接在桶里修改，动态维护 $cnt\choose 2$ 即可。

考虑我们需要把相同形状的连通块放在一个同里。显然需要用哈希维护连通块的形状，并且还要支持简单地合并。

因为相同只关心形状，所以我们需要先把每个点的坐标变成与在网格图上的位置无关。考虑维护相对位置：我们钦定一个连通块的基准点是 $(x_{\min},y_{\min})$ 这个点（这个点不必在连通块上），据此生成所有点的相对坐标。这样刻画之后相同形状的连通块等价于相对坐标的集合是相同的。

考虑集合哈希。我们通常用 $\sum A^x$ 进行 1D 的集合哈希，类似地我们使用 $\sum A^xB^y$ 进行 2D 的集合哈希，取 $A,B$ 均为 $1000$ 以上的质数后正确性就能得到保证了。

于是就做完了。在并查集合并的时候维护一下基准点即可，每次只需给一个连通块的哈希值整体乘上 $A^{\Delta x}B^{\Delta y}$ 表示基准点的偏移。因为基准点的两个坐标总是小于等于所有连通块内的点坐标，所以不会出现 $\Delta<0$ 的情况，所以可以使用自然溢出，常数很小。

----------

代码里面基准点取得不好，搞出来逆元了。不过也无所谓。

```cpp
const ll A=1013,B=1009;
const ll mod=2007072007;
int n,m;
int Q;
int q[N*N];
pii sta[N*N];
ll hsh[N*N];
map <int,int> bol;
int a[N][N];
bool col[N][N];
int tot;
map <int,int> lsh;
ll ans;
vector <pii> ofl[N*N];
vector <int> qry[N*N];
ll res[N*N];
int dx[]={0,1,-1,0},dy[]={1,0,0,-1};
il int tonum(int i,int j){
	return (i-1)*m+j;
}
ll C(int x){
	return 1ll*x*(x-1)/2;
}
void add(int x){
	ans-=C(bol[x]);
	bol[x]++;
	ans+=C(bol[x]);
}
void des(int x){
	ans-=C(bol[x]);
	bol[x]--;
	ans+=C(bol[x]);
}
int f[N*N];
int find(int x){return (f[x]==x?f[x]:f[x]=find(f[x]));}
ll qpow(ll b,int p){
	if(!p) return 1;
	if(p<0) return qpow(qpow(b,mod-2),-p);
	ll d=qpow(b,p>>1);
	if(p&1) return d*d%mod*b%mod;
	else return d*d%mod;
}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y) return;
	des(hsh[y]);
	des(hsh[x]);
	if(sta[x]<sta[y]){
		int xdel=sta[x].fi-sta[y].fi,ydel=sta[x].se-sta[y].se;
		sta[y]=sta[x];
		hsh[y]=(hsh[x]+hsh[y]*qpow(A,xdel)%mod*qpow(B,ydel)%mod)%mod;
	}
	else{
		int xdel=sta[y].fi-sta[x].fi,ydel=sta[y].se-sta[x].se;
		hsh[y]=(hsh[y]+hsh[x]*qpow(A,xdel)%mod*qpow(B,ydel)%mod)%mod;
	}
	add(hsh[y]);
	f[x]=y;
}
int main(){
#ifdef Shun
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	ios::sync_with_stdio(false);
	cin>>n>>m;
	fr1(i,1,n) fr1(j,1,m) cin>>a[i][j];
	fr1(i,1,n){
		fr1(j,1,m){
			sta[tonum(i,j)]=mp(i,j);
			hsh[tonum(i,j)]=A*B;
			lsh[a[i][j]]=1;
			f[tonum(i,j)]=tonum(i,j);
		}
	}
	for(auto &i:lsh){
		tot++;
		i.se=tot;
	}
	fr1(i,1,n) fr1(j,1,m) a[i][j]=lsh[a[i][j]];
	cin>>Q;
	fr1(i,1,Q){
		cin>>q[i];
		auto it=lsh.upper_bound(q[i]);
		if(it==lsh.end()) q[i]=-1;
		else q[i]=it->se;
		if(~q[i]) qry[q[i]].pb(i);
	}
	lsh.clear();
	fr1(i,1,n) fr1(j,1,m) ofl[a[i][j]].pb(mp(i,j));
	fr2(i,tot,1){
		for(auto j:ofl[i]){
			int x=j.fi,y=j.se;
			col[x][y]=1;
			add(hsh[tonum(x,y)]);
			fr1(k,0,3){
				if(x+dx[k]<1||x+dx[k]>n||y+dy[k]<1||y+dy[k]>m) continue;
				int nx=x+dx[k],ny=y+dy[k];
				if(col[nx][ny]) merge(tonum(x,y),tonum(nx,ny));
			}
		}
		for(auto j:qry[i]) res[j]=ans;
	}
	fr1(i,1,Q){
		if(~q[i]) cout<<res[i]<<'\n';
		else cout<<0<<'\n';
	}
	ET;
}
//ALL FOR Zhang Junhao.
```

---

