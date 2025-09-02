# Jerry Loves Lines

## 题目背景

Jerry 很喜欢在纸上面画直线呢。

## 题目描述

Jerry 在纸上面画上了 $N$ 条直线，每一条直线都可以用 $y=k_ix+b_i$ 来表示。现在 Jerry 想知道对于 $M$ 条可以表示为 $X=A_j$ 的直线，从下往上数排名第 $K$ 的交点的 $y$ 坐标是多少。

如有 $x$ 条直线与一条 $X=A_j$ 的直线交于同一点，算 $x$ 个点。

## 说明/提示

对于 $30\%$ 的数据，$1 \leqslant N,M \leqslant 2000$；  
对于 $100\%$ 的数据，$1 \leqslant N \leqslant 2000$，$1 \leqslant M \leqslant 5\times10^5$。

其他所有读入的数全在 `int` 范围内，且保证 $1 \leqslant K \leqslant N$。

温馨提示：如果对自己的做法的常数感到不放心，请吸入氧气（食用 O2 优化）如果有着充足自信，尽管放手浪。

$\color{white}{\text{int*int会爆int!!!}}$

## 样例 #1

### 输入

```
2 3 1
1 2
2 1
0
1
2
```

### 输出

```
1
3
4```

# 题解

## 作者：CYJian (赞：6)

首先需要知道一个~~常识~~:两条直线相交后,这两条直线在交点右侧的大小关系就会改变.如果有多条直线计算排名,则会导致两条直线交换排名,且这两条直线在交点附近排名必然相邻.所以可以直接把这两条直线的一条排名+1,一条排名-1,这样就可以稳定过了..

~~这个应该算是常识吧..或者说很显然~~

然后对于这道题,我们就只要算出所有直线两两之间的交点并且按照$x$排好序,然后把询问离线排序处理.

先将所有点按照最靠左的询问排好序,然后每经过一个交点就把直线的排名更新一下.处理询问的时候就直接用排名为$k$的直线更新就好了.

[代码](https://www.luogu.org/paste/hp4loy5z)

Updata (2018.9.21):

感谢 @打脸不疼 提供的[Hack数据](https://www.luogu.org/discuss/show/65651?page=1)..

(但是数据中并没有加入这一组数据,请求管理员加入)

现在标算已修改,这里是[代码](https://www.luogu.org/paste/ui770vt7)

---

## 作者：Inui_Sana (赞：0)

基础的思路出题人已经说的很清楚了。就是考虑扫描线，动态维护每条直线当前排名。一共只有 $O(n^2)$ 个交点，每次遇到交点就修改排名。

但是这题主要难点在于有多条线相交于一点怎么处理。出题人给出了一种将一个排名 $+1$ 一个排名 $-1$ 的方法，挺妙的。

但是你发现每次排名变动的是一个区间 $[L,R]$ 且 $\sum (R-L+1)=O(n^2)$，所以直接取出来暴力排序就行。时间复杂度 $O(n^2\log n)$。

code：

```cpp
int n,m,k,s,p[M],rk[M];
ll ans[N];pair<ll,int> b[M];
struct Line{
	int k,b;
}l[M];
struct node{
	int x,u,v;
}a[N<<2];
il bool cmp(node x,node y){
	return x.x!=y.x?x.x<y.x:x.v<y.v;
}
void Yorushika(){
	scanf("%d%d%d",&n,&m,&k);
	rep(i,1,n){
		scanf("%d%d",&l[i].k,&l[i].b);
	}
	rep(i,1,n){
		rep(j,i+1,n){
			if(l[i].k==l[j].k){
				continue;
			}
			int x=floor(1.*(l[j].b-l[i].b)/(l[i].k-l[j].k));
			ll u=1ll*l[i].k*(x-1)+l[i].b,v=1ll*l[j].k*(x-1)+l[j].b;
			if(u>v){
				a[++s]={x,i,j};
			}else{
				a[++s]={x,j,i};
			}
		}
	}
	rep(i,1,m){
		int x;scanf("%d",&x);
		a[++s]={x,i,0};
	}
	sort(a+1,a+s+1,cmp);
	rep(i,1,n){
		b[i]=Mp(l[i].k*-(1ll<<31)+l[i].b,i);
	}
	sort(b+1,b+n+1);
	rep(i,1,n){
		p[b[i].se]=i,rk[i]=b[i].se;
	}
	rep(i,1,s){
		int j=i,L=inf,R=-inf;
		while(a[j].x==a[i].x){
			if(!a[j].v){
				ans[a[j].u]=1ll*l[rk[k]].k*a[j].x+l[rk[k]].b;
			}else{
				int x=a[j].u,y=a[j].v;
				L=min({L,p[x],p[y]}),R=max({R,p[x],p[y]});
			}
			j++;
		}
		if(L<1e9){
			rep(j,L,R){
				 b[j]=Mp(1ll*l[rk[j]].k*(a[i].x+1)+l[rk[j]].b,rk[j]);
			}
			sort(b+L,b+R+1);
			rep(j,L,R){
				p[b[j].se]=j,rk[j]=b[j].se;
			}
		}
		i=j-1;
	}
	rep(i,1,m){
		printf("%lld\n",ans[i]);
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

