# 道路網

## 题目描述

[problemUrl]: https://atcoder.jp/contests/ddcc2016-qual/tasks/ddcc_2016_qual_d

$ N $ 個の都市と $ N-1 $ 個の道からなる国があります。各都市には $ 1,\ \,\ 2,\ \,\ …\ \,\ ,\ \,\ N $ と番号がついています。 $ i(1\ ≦\ i\ ≦\ N-1) $ 番目の道は都市 $ A_i $ と都市 $ B_i $ を長さ $ C_i $ でつないでいます。 道は双方向に移動可能で、どの都市同士も何本かの道を通って互いに行き来することが可能です。

ある日、$ 1≦i\ <\ j≦N $ を満たす $ 2 $ つの都市 $ i,\ \,\ j $ について都市 $ i $ と 都市 $ j $ を直接つなぐ道が存在しない場合、都市 $ i $ と 都市 $ j $ を直接つなぐ長さ $ X $ の道を追加する、という操作が行われました。

$ d(u,\ \,\ v) $ を都市 $ u $ から都市 $ v $ までの最短距離として、 $ 1≦i\ <\ j≦N $ を満たす $ 2 $ つの都市 $ i,\ \,\ j $ について $ d(i,\ \,\ j) $ をそれぞれ求め、その総和を出力してください。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 10^{5} $
- $ 1\ ≦\ A_i,\ \,\ B_i\ ≦\ N(1\ ≦\ i\ ≦\ N-1) $
- $ 1\ ≦\ C_i\ ≦\ 10^{5}(1\ ≦\ i\ ≦\ N-1) $
- $ 1\ ≦\ X\ ≦\ 10^5 $
- 操作が行われる以前の時点において、どの $ 2 $ つの都市同士も何本かの道をたどって移動可能
- $ C_i,\ \,\ X $ はいずれも整数

### Sample Explanation 1

以下の図は都市と道の関係を表します。青い実線は元々あった $ N-1 $ 本の道を、黒い破線は操作により新たに追加された長さ $ 3 $ の道を表しています。 

![9461ca7dead16c099ef63ac3b181699f.png](https://atcoder.jp/img/ddcc2016-qual/9461ca7dead16c099ef63ac3b181699f.png)

## 样例 #1

### 输入

```
6 3
1 2 2
2 3 3
4 1 4
6 4 10
5 4 8```

### 输出

```
51```

## 样例 #2

### 输入

```
20 68
12 10 34
12 14 35
12 9 15
17 9 37
1 17 47
1 2 12
11 2 7
11 15 32
13 11 15
13 4 2
5 1 35
20 5 51
3 4 39
16 11 21
3 18 70
17 8 68
20 7 2
6 3 34
19 2 5```

### 输出

```
11278```

# 题解

## 作者：Inui_Sana (赞：1)

先假设对于所有 $(i,j)$ 之间都连一条长度为 $X$ 的边，则问题转换成：只保留树边，记 $D(i,j)$ 表示 $\min(dis(i,j),X)$，求 $\sum D(i,j)$。

考虑套路点分治，算出 $\sum_i\sum_{j>i}[dis(i,j)<X]=A,\sum_i\sum_{j>i}[dis(i,j)<X]\times dis(i,j)=B$，则 $ans=B+(\binom n2-A)\times X$。算的方式就是将当前处理的以 $rt$ 为根的子树中所有点 $i$ 的 $dis(i,rt)$ 排序后双指针。

这一部分是一个板子，不做赘述。只需要注意点分治常见错误，如求重心某些地方写成 $n$ 而不是 $siz$ 即可（我怎么又踩坑啊）。

但是注意到如果有树边 $(u,v)$，则实际上不会再连 $(i,j,X)$，但是此时直接走 $(u,v)$ 不一定是最短路。于是分情况讨论：

- $deg_u=n-1\vee deg_v=n-1$

此时不管怎么都是不能只走非树边的，但是可能先走非树边到另一个点 $x$ 再走到 $v$。于是令 $deg_v=n-1,c_i=\min_{(i,j,w)\in E}w$，$(u,v)$ 边权为 $W$，则 $D(u,v)=\min(W,X+c_v)$。

- $deg_u+deg_v=n$

此时由于没有点同时不与 $u,v$ 相邻，所以也无法走两条非树边到。但是发现可以走三条到，或者先走非树边到另一个点，再一步到 $v$。则有 $D(u,v)=\min(W,3X,X+\min(c_u,c_v))$。

- $deg_u+deg_v<n$

此时可以走两条非树边到，但是也不能漏了 $deg_u+deg_v=n$ 时就可行的一些情况，有 $D(u,v)=\min(W,2X,X+\min(c_u,c_v))$。

于是解决了。时间复杂度 $O(n\log^2n)$。

code：

```cpp
int n,m,rt,siz[N],deg[N],c[N];
bool vis[N];
ll cnt,ans,dis[N];
vector<ll> g,h;
int tot,head[N];
struct node{
	int to,nxt,cw;
}e[N<<1];
il void add(int u,int v,int w){
	e[++tot]={v,head[u],w},head[u]=tot;
}
void getRt(int u,int f,int s){
	siz[u]=1;
	int mx=0;
	go(i,u){
		int v=e[i].to;
		if(v==f||vis[v]){
			continue;
		}
		getRt(v,u,s);
		siz[u]+=siz[v];
		mx=max(mx,siz[v]);
	}
	mx=max(mx,s-siz[u]);
	if(mx<=s/2){
		rt=u;
	}
}
void getSiz(int u,int f){
	siz[u]=1;
	go(i,u){
		int v=e[i].to;
		if(v==f||vis[v]){
			continue;
		}
		getSiz(v,u);
		siz[u]+=siz[v];
	}
}
void dfs(int u,int f){
	g.eb(dis[u]),h.eb(dis[u]);
	go(i,u){
		int v=e[i].to;
		if(v==f||vis[v]){
			continue;
		}
		dis[v]=dis[u]+e[i].cw;
		dfs(v,u);
	}
}
void calcD(){
	sort(g.begin(),g.end());
	int p=-1;
	vector<ll> pre;
	pre.eb(*g.begin());
	rep(i,1,(int)g.size()-1){
		pre.eb(g[i]+pre[i-1]);
	}
	drep(i,(int)g.size()-1,0){
		while(p<i-1&&g[p+1]+g[i]<m){
			p++;
		}
		while(p>=i){
			p--;
		}
		if(p>=0){
			ans-=g[i]*(p+1)+pre[p];
			cnt-=p+1;
		}
	}
}
void calcA(){
	sort(h.begin(),h.end());
	int p=-1;
	vector<ll> pre;
	pre.eb(*h.begin());
	rep(i,1,(int)h.size()-1){
		pre.eb(h[i]+pre[i-1]);
	}
	drep(i,(int)h.size()-1,0){
		while(p<i-1&&h[p+1]+h[i]<m){
			p++;
		}
		while(p>=i){
			p--;
		}
		if(p>=0){
			ans+=h[i]*(p+1)+pre[p];
			cnt+=p+1;
		}
	}
}
void solve(int u){
	vis[u]=1,dis[u]=0;
	h.clear(),h.eb(0);
	go(i,u){
		int v=e[i].to;
		if(vis[v]){
			continue;
		}
		g.clear();
		dis[v]=e[i].cw,dfs(v,u);
		calcD();
	}
	calcA();
	getSiz(u,0);
	go(i,u){
		int v=e[i].to;
		if(vis[v]){
			continue;
		}
		getRt(v,u,siz[v]);
		solve(rt);
	}
}
void Yorushika(){
	read(n,m);
	rep(i,1,n-1){
		int u,v,w;read(u,v,w);
		add(u,v,w),add(v,u,w);
		deg[u]++,deg[v]++;
	}
	rep(u,1,n){
		c[u]=inf;
		go(i,u){
			c[u]=min(c[u],e[i].cw);
		}
	}
	getRt(1,0,n);
	solve(rt);
	ans+=(1ll*n*(n-1)/2-cnt)*m;
	for(int i=2;i<=tot;i+=2){
		int u=e[i].to,v=e[i-1].to;
		if(e[i].cw>m){
			if(deg[u]+deg[v]==n){
				if(deg[u]==n-1){
					ans+=min(e[i].cw,c[u]+m)-m;
				}else if(deg[v]==n-1){
					ans+=min(e[i].cw,c[v]+m)-m;
				}else{
					ans+=min({e[i].cw,m+m+m,c[v]+m,c[u]+m})-m;
				}
			}else{
				ans+=min({e[i].cw,m+m,c[u]+m,c[v]+m})-m;
			}
		}
	}
	printf("%lld\n",ans);
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

