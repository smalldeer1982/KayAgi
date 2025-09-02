# [PA 2025] 砖块收集 / Zbieranie klocków

## 题目背景


PA 2025 R4B.

**警告：滥用本题评测一次即可封号。**

## 题目描述


有一个 $ n \times m $ 的矩形棋盘被划分为 $ n \times m $ 个正方形格子。有若干块立方体积木在棋盘上。积木的尺寸与格子相同，每块积木恰好占据一个格子。我们记第 $i$ 行第 $j$ 列的格子为 $(i,j)$。

现在小女孩 Algosia 要收积木。一块积木可以被收走，当且仅当：

- 这块积木的上面和下面没有相邻的积木；
- **或者**这块积木的左边和右边没有相邻的积木。

初始时棋盘上有 $k$ 块积木。$q$ 次操作，每次操作新增一个积木，或者移除一个积木（**这里的移除不受上述条件的限制**）。

对于 $i=1,2,\ldots,q+1$，Algosia 想要知道：在进行前 $(i-1)$ 次操作后，她最多可以**逐个**收走多少个积木。

注意，积木不会真的被收走。


## 说明/提示


### 样例解释

初始时的棋盘如下左图所示。棋盘上有 $22$ 块积木。

将一开始可以被收走的积木收走后，棋盘变成了下右图的样子。于是所有积木都可以被收走。

![](https://cdn.luogu.com.cn/upload/image_hosting/o2zqsgkw.png?x-oss-process=image/resize,m_lfit,h_150)
![](https://cdn.luogu.com.cn/upload/image_hosting/b39avzr2.png?x-oss-process=image/resize,m_lfit,h_150)

第 $1$ 次操作中，放上了一块新的积木（以红色标识）。这 $3\times 3$ 块积木就没办法收走了，最后只能收走 $14$ 块积木。

![](https://cdn.luogu.com.cn/upload/image_hosting/vuzf3mky.png?x-oss-process=image/resize,m_lfit,h_150)

继续进行第二次操作后，棋盘变成了下图的形状。此时只能收走 $6$ 块积木。

![](https://cdn.luogu.com.cn/upload/image_hosting/yfj4oie4.png?x-oss-process=image/resize,m_lfit,h_150)

继续进行第三次操作后，棋盘变成了下图的形状。答案为 $5$。


![](https://cdn.luogu.com.cn/upload/image_hosting/fvbomqzj.png?x-oss-process=image/resize,m_lfit,h_150)

### 子任务

解决 $q=1$ 的子任务可以获得大于 $0$ 分的部分分。

### 数据范围
- $ 1 \leq n, m \leq 2\times 10^5$；
- $1 \leq k, q \leq 75\, 000 $；
- $1\le x_i,x\le n$，$1\le y_i,y\le m$；
- $\forall 1\le i\lt j\le k$，$(x_i,y_i)\neq (x_j,y_j)$。


## 样例 #1

### 输入

```
5 7 22 3
1 1
1 2
1 3
2 3
3 3
3 2
2 1
3 1
4 1
5 1
1 5
1 6
1 7
2 5
2 7
3 5
3 6
3 7
4 5
5 5
4 7
5 7
2 2
2 6
5 1```

### 输出

```
22
14
6
5```

# 题解

## 作者：wrkwrkwrk (赞：1)

我们可以容易知道：若一个点在 $2 \times 2$ 的格子中，则不能被移除。

在确定以上条件的情况下，若一个点在两个上述格子之间，存在一条链按阶梯状递增，则也不能被移除。

容易证明上述为等价条件。且若一个格子不在 $2\times 2$ 方格中，且不能被移除，则至多在一个阶梯状中。

~~直接模拟上述过程即可。~~

这里使用 odt 维护阶梯。对每条平行于主对角线和副对角线分别维护。

一个点 $(x,y)$ 可以加入 $x+y,x+y-1$ 的副对角线和 $x-y$，$x-y-1$ 的主对角线。

考虑 odt 的内部顺序判断以方便，这里分别定义如下内容：
```
struct cmp1{
	bool operator()(node a,node b)const{
		auto p=a.first,q=b.first;
		return p.first==q.first?p.second<q.second:p.first>q.first; 
	}
};
struct cmp2{
	bool operator()(node a,node b)const{
		auto p=a.first,q=b.first;
		return p.first==q.first?p.second<q.second:p.first<q.first; 
	}
};
```
这样可以通过自定义比较函数的方式定义 odt。通过存储目前加入过的点的集合方便找到 +1 -1。

node 维护最前，后点，左，右侧是否封闭，当前是否不能被删除，当前是否是 $2 \times 2$ 格子中的点。在 $2 \times 2$ 格子中的点单独存储。

插入时注意判断前驱，后继是否相邻且是否是 $2 \times 2$ 格子中的点（距离是否等于1）。

标记点的时候注意判断本身是不是已经是不能被删除，两侧是否封闭。

清除标记判断左右两侧。注意指针不要指错。

删除点保留所在段左右侧的值。

如上都返回当前在阶梯状被认为不可删除的点的数量变化量。

剩下的直接判断，加入，标记，去除标记，删除即可。反正只会影响周边的点。

时间复杂度 $O((k+q)\log(k+q))$，常数巨大。

写的很长，7.1k，不清楚长度不超过 3k 的代码咋写的。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	pair<int,int>first,second;
	bool cntl,cntr,ue,uc;
};
struct cmp1{
	bool operator()(node a,node b)const{
		auto p=a.first,q=b.first;
		return p.first==q.first?p.second<q.second:p.first>q.first; 
	}
};
struct cmp2{
	bool operator()(node a,node b)const{
		auto p=a.first,q=b.first;
		return p.first==q.first?p.second<q.second:p.first<q.first; 
	}
};
int dis(pair<int,int>a,pair<int,int>b){
	return abs(a.first-b.first)+abs(a.second-b.second); 
}
template<class cmp>
struct odt{
	set<node,cmp>z;
	set<node,cmp>zc;
	int insert(pair<int,int>f){
		zc.insert({f});
		auto c=z.lower_bound({f,f,0,0,0,0});
		node nc={f,f,0,0,0,0};
		if(c!=z.begin()&&dis({prev(c)->second.first,prev(c)->second.second},f)==1){
			if(prev(c)->ue){
				nc.cntl=1;
			}else{
				nc.first=prev(c)->first;
				nc.cntl=prev(c)->cntl;
				z.erase(*prev(c));
			}
		}
		if(c!=z.end()&&dis({(c)->first.first,(c)->first.second},f)==1){
			if(c->ue){
				nc.cntr=1;
			}else{
				nc.second=c->second;
				nc.cntr=c->cntr;
				z.erase(*c);
			}
		}
		int res=0;
		if(nc.cntl&&nc.cntr){
			res=dis(nc.first,nc.second)+1;
			nc.ue=1;
		}
		z.insert(nc);
		return res;
	}
	int mark(pair<int,int>f){
		auto c=prev(z.upper_bound({f,f,0,0,0,0}));
		if(!c->ue){
			auto fc=*c;
			z.erase(fc);
			int res=0;
			z.insert({f,f,1,1,1,1}); 	
			if(fc.first!=f||fc.second!=f){
				if(fc.first!=f){
					auto w=prev(zc.lower_bound({f}))->first;
					auto zf=fc;
					zf.second=w;
					zf.cntr=1;
					if(zf.cntl){
						zf.ue=1;
						res+=dis(zf.first,zf.second)+1;
					}
					z.insert(zf);
				}
				if(fc.second!=f){
					auto w=next(zc.lower_bound({f}))->first;
					auto zf=fc;
					zf.first=w;
					zf.cntl=1;
					if(zf.cntr){
						zf.ue=1;
						res+=dis(zf.first,zf.second)+1;
					}
					z.insert(zf);
				}
			}
			return res;	
		}else if(!c->uc){
			auto fc=*c;
			z.erase(fc);
			z.insert({f,f,1,1,1,1});
			if(fc.first!=f){
				auto w=prev(zc.lower_bound({f}))->first;
				auto zf=fc;
				zf.second=w;
				z.insert(zf);
			}
			if(fc.second!=f){
				auto w=next(zc.lower_bound({f}))->first;
				auto zf=fc;
				zf.first=w;
				z.insert(zf);
			}
			return -1;
		}else{
			return 0;
		} 
		
	}
	int clearmark(pair<int,int>f){
		auto c=prev(z.upper_bound({f,f,0,0,0,0}));
		int res=0;
		node x={f,f,0,0,0,0};
		if(c!=z.begin()&&dis(prev(c)->second,f)==1){
			if(!prev(c)->uc){
				if(prev(c)->ue){
					res-=dis(prev(c)->first,prev(c)->second)+1;
				}
				x.first=prev(c)->first;
				x.cntl=prev(c)->cntl;
				z.erase(prev(c));
			}else{
				x.cntl=1;
			}
		}
		if(next(c)!=z.end()&&dis(next(c)->first,f)==1){
			if(!next(c)->uc){
					
				if(next(c)->ue)res-=dis(next(c)->first,next(c)->second)+1;
				x.second=next(c)->second;
				x.cntr=next(c)->cntr;
				z.erase(next(c)); 
			}else{
				x.cntr=1;
			}
		}
		z.erase(c);
		if(x.cntl&&x.cntr){
			x.ue=1;
			res+=dis(x.first,x.second)+1;
		}
		z.insert(x);
		return res;
	}
	int erase(pair<int,int>f){
		auto c=prev(z.upper_bound({f,f,0,0,0,0}));
		auto fc=*c;
		z.erase(c);
		int res=0;
		if(fc.ue){
			res-=dis(fc.first,fc.second)+1;
		}
		if(fc.first!=f){
			node x={};
			x.first=fc.first;
			x.second=prev(zc.lower_bound({f}))->first;
			x.cntl=fc.cntl;
			x.cntr=x.ue=x.uc=0;
			z.insert(x);
		}
		if(fc.second!=f){
			node x={};
			x.first=zc.upper_bound({f})->first;
			x.second=fc.second;
			x.cntl=0;
			x.cntr=fc.cntr;
			x.ue=x.uc=0;
			z.insert(x);
		}
		return res;
		
	}
	size_t size(){
		return z.size();
	}
};
template<class type,int l,int r>
struct pc_array{
	type w[r-l+1];
	type& operator[](int pos){
		return w[pos-l];
	}
};
pc_array<odt<cmp1>,0,400005>cl;
pc_array<odt<cmp2>,-200005,200005>cr;
struct has{
	unsigned long long operator()(pair<int,int>f)const{
		return (unsigned long long)f.first<<30|f.second;
	}
};
unordered_set<pair<int,int>,has>ff,fz;
int zc[5]; 
#define tot zc[0]
#define hap zc[1]
void insert1(int x,pair<int,int>y){
	hap=hap+cl[x].insert(y);
}
void insert2(int x,pair<int,int>y){
	hap=hap+cr[x].insert(y);
}
void mark1(int x,pair<int,int>y){
	hap=hap+cl[x].mark(y);
}
void mark2(int x,pair<int,int>y){
	hap=hap+cr[x].mark(y);
}
void clearmark1(int x,pair<int,int>y){
	hap=hap+cl[x].clearmark(y);
} 
void clearmark2(int x,pair<int,int>y){
	hap=hap+cr[x].clearmark(y);
} 
void erase1(int x,pair<int,int>y){
	hap=hap+cl[x].erase(y);
}
void erase2(int x,pair<int,int>y){
	hap=hap+cr[x].erase(y);
}
void insert(pair<int,int>wc){
	if(ff.find(wc)==ff.end()){
		ff.insert(wc);
		tot=tot+1;
		insert1(wc.first+wc.second-1,wc);
		insert1(wc.first+wc.second,wc);
		insert2(wc.first-wc.second-1,wc);
		insert2(wc.first-wc.second,wc);
	}
}
void mark(pair<int,int>wc){
	if(fz.find(wc)==fz.end()){
		mark1(wc.first+wc.second-1,wc);
		mark1(wc.first+wc.second,wc);
		mark2(wc.first-wc.second-1,wc);
		mark2(wc.first-wc.second,wc);
		fz.insert(wc);
	}
}
void clearmark(pair<int,int>wc){
	if(fz.find(wc)!=fz.end()){
		clearmark1(wc.first+wc.second-1,wc);
		clearmark1(wc.first+wc.second,wc);
		clearmark2(wc.first-wc.second-1,wc);
		clearmark2(wc.first-wc.second,wc);
		fz.erase(wc);
	}
}
void erase(pair<int,int>wc){
	if(ff.find(wc)!=ff.end()){
		tot=tot-1;
		erase1(wc.first+wc.second-1,wc);
		erase1(wc.first+wc.second,wc);
		erase2(wc.first-wc.second-1,wc);
		erase2(wc.first-wc.second,wc);
		ff.erase(wc);
	}
}
const vector<vector<pair<int,int>>>checkt={
	{{-1,-1},{-1,0},{0,-1},{0,0}},
	{{-1,0},{-1,1},{0,0},{0,1}},
	{{0,-1},{0,0},{1,-1},{1,0}},
	{{0,0},{0,1},{1,0},{1,1}},
};
const vector<pair<int,int>>rf={
	{-1,-1},{-1,0},{-1,1},
	{ 0,-1},	   { 0,1},
	{ 1,-1},{ 1,0},{ 1,1},

};
void adpoint(pair<int,int>x){
    insert(x);
    for(auto p:checkt){
	 	bool z=1;
	  	for(auto f:p){
	   		int xx=x.first+f.first,yy=x.second+f.second;
	  		if(ff.find({xx,yy})==ff.end()){
	   			z=0;
	   			break;
			}
		}
		if(z){
		   	for(auto f:p){
		   		int xx=x.first+f.first,yy=x.second+f.second;
		  		mark({xx,yy});
			}
		}
	}
}
void erasepoint(pair<int,int>x){
	clearmark(x);
	erase(x);
	for(auto f:rf){
		pair<int,int>nx={x.first+f.first,x.second+f.second};
		if(ff.find(nx)!=ff.end()){
			bool cf=0;
		    for(auto p:checkt){
			 	bool z=1;
			  	for(auto fc:p){
			   		int xx=nx.first+fc.first,yy=nx.second+fc.second;
			  		if(ff.find({xx,yy})==ff.end()){
			   			z=0;
			   			break;
					}
				}
				if(z){
					cf=1;
					break;
				}
			}
			if(!cf){
				clearmark(nx);
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n,m,k,q;
	cin>>n>>m>>k>>q;
	map<pair<int,int>,int>tl;
	for(int i=1;i<=k;i++){
		int a,b;
		cin>>a>>b; 
		tl[{a,b}]=1;
		adpoint({a,b});
	}
    cout<<tot-hap-fz.size()<<'\n';
	for(int i=1;i<=q;i++){
		int x,y;
		cin>>x>>y;
		if(!tl[{x,y}])adpoint({x,y});
		else erasepoint({x,y});
		tl[{x,y}]^=1;
		cout<<tot-hap-fz.size()<<'\n';
	}
	return 0;
}
```

---

