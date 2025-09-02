# Union Find

## 题目描述

[problemUrl]: https://atcoder.jp/contests/atc001/tasks/unionfind_a

この問題は、講座用問題です。ページ下部に解説が掲載されています。

$ N $ 頂点の、単純とは限らない無向グラフを考えます。 初期状態では、頂点のみが存在し、辺は全く存在せず、全ての頂点が孤立しているとします。 以下の $ 2 $ 種類のクエリが、$ Q $ 回与えられます。

- 連結クエリ： 頂点 $ A $ と、頂点 $ B $ を繋ぐ辺を追加します。
- 判定クエリ： 頂点 $ A $ と、頂点 $ B $ が、連結であるかどうか判定します。連結であれば `Yes`、そうでなければ `No` を出力します。

クエリを順番に処理し、判定クエリへの回答を出力して下さい。 この際、同じ辺が何度も追加されることや、自分自身への辺が追加されることもある事に注意してください。

連結であるとは、頂点 $ A $ から頂点 $ B $ まで辺をたどって到達可能であることを意味します。 $ A $ と $ B $ が同じ頂点の場合、連結であると定義します。 グラフは無向であるため、連結クエリによって頂点 $ A,\ B $ 間の辺が追加されると、$ A $ から $ B $ へも $ B $ から $ A $ へも辿れるようになります。

## 说明/提示

### 解説

  **[Union find(素集合データ構造)](https://www.slideshare.net/secret/CIWAduFPvzGrrE "Union find(素集合データ構造)")**  from **[AtCoder Inc.](http://www.slideshare.net/chokudai)** 

### Sample Explanation 1

以下のような手順で実行されます。 - $ 1 $ つ目のクエリで、頂点 $ 1 $ と頂点 $ 2 $ を繋ぎます。 - $ 2 $ つ目のクエリで、頂点 $ 3 $ と頂点 $ 2 $ を繋ぎます。 - $ 3 $ つ目のクエリで、頂点 $ 1 $ と頂点 $ 3 $ の連結判定を行います。連結しているので、`Yes`と出力します。 - $ 4 $ つ目のクエリで、頂点 $ 1 $ と頂点 $ 4 $ の連結判定を行います。連結していないので、`No`と出力します。 - $ 5 $ つ目のクエリで、頂点 $ 2 $ と頂点 $ 4 $ を繋ぎます。 - $ 6 $ つ目のクエリで、頂点 $ 4 $ と頂点 $ 1 $ の連結判定を行います。連結しているで、`Yes`と出力します。 - $ 7 $ つ目のクエリで、頂点 $ 4 $ と頂点 $ 2 $ を繋ぎます。これらは既に繋がれていますが、多重辺が出来ることもあります。 - $ 8 $ つ目のクエリで、頂点 $ 0 $ と頂点 $ 0 $ を繋ぎます。これらは同じ頂点ですが、自己ループが出来ることもあります。 - $ 9 $ つ目のクエリで、頂点 $ 0 $ と頂点 $ 0 $ の連結判定を行います。同じ頂点は常に連結していると見做せるので、`Yes`と出力します。

## 样例 #1

### 输入

```
8 9
0 1 2
0 3 2
1 1 3
1 1 4
0 2 4
1 4 1
0 4 2
0 0 0
1 0 0```

### 输出

```
Yes
No
Yes
Yes```

# 题解

## 作者：HsKr (赞：5)

UPDATE:

2020-02-16 新增了种类并查集。

> 并查集是一种树型的数据结构，用于处理一些不相交集合（Disjoint Sets）的**合并**及**查询**问题。常常在使用中以森林来表示。					
				
                										--摘自百度百科

-  [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)


我们假设题目中$P_i$和$P_j$这种关系是父子关系。

老祖先没有父亲，他是天生的。

### 并查集的初始化

```cpp
int fa[5010];//fa[i]表示i的父亲，祖先的父亲即为自己
void init(){//初始化
	for(int i=0;i<5005;i++){
		fa[i]=i;//每一个人都是他家族的祖先
	}
}
```

### 并查集的查询

如何才能判断两个人有无亲戚关系呢？只要他们的祖先相同，他们就有亲戚关系。

下面就是找祖先和查询的代码。

```cpp
int find(int x){//找祖先 
	if(fa[x]==x) return x;//x就是该家族的祖先
	return find(fa[x]);//x父亲的祖先就是x的祖先
}
bool ask(int x,int y){//查询 
	return find(x)==find(y);//如果x的祖先也是y的祖先，那么他们就是亲戚 
}
```

### 并查集的合并

加入b想加入家族a，那么就要将他们合并，但并不是把b加入a家族就行了，b的整个家族都要挪到家族a。

如果让b的祖先当a的祖先的儿子，这样查询b原亲戚中时，必回查到b的祖先，然后查到a的祖先。

```cpp
void uni(int x,int y){//合并两个家族 。
	fa[find(x)]=find(y);//让x的祖先当y的祖先的孩子，就完成了x,y两家族的合并 
}
```

### P1551代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int fa[5010];//fa[i]表示i的父亲，祖先的父亲即为自己
void init(){//初始化
	for(int i=0;i<5005;i++) {
		fa[i]=i;//每一个人都是他家族的祖先
	}
}
int find(int x){//找祖先 
	if(fa[x]==x) return x;//x就是该家族的祖先
	return find(fa[x]);//x父亲的祖先就是x的祖先
}
bool ask(int x,int y){//查询 
	return find(x)==find(y);//如果x的祖先也是y的祖先，那么他们就是亲戚 
}
void uni(int x,int y){//合并两个家族 
	fa[find(x)]=find(y);//让x的祖先当y的祖先的孩子，就完成了x,y两家族的合并 
}
int main(){
	int n,m,p,x,y;
	init();
	scanf("%d%d%d",&n,&m,&p);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		uni(x,y);
	}
	for(int i=1;i<=p;i++){
		scanf("%d%d",&x,&y);
		if(ask(x,y)) puts("Yes");
		else puts("No");
	}
	return 0;
}

```

- [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)

这回，用上述并查集就TLE了，需要考虑优化。

### 并查集的路径压缩

上述并查集如果数据成一条链，那么每次查询复杂度是$O(n)$，如果每一个人都当老祖先的儿子，那么在find中，询问一次就能得到结果了。

```cpp
int find(int x){//找祖先 
	if(fa[x]==x) return x;//x就是该家族的祖先
	return fa[x]=find(fa[x]);//记录，直接让x做x的祖先的儿子 
}
```

一行并查集会不会更优雅呢？

```cpp
int find(int x){//找祖先 
	return fa[x]=fa[x]==x?x:find(fa[x]);
}
```

AC代码。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int fa[10010];//fa[i]表示i的父亲，祖先的父亲即为自己
void init(){//初始化
	for(int i=0;i<10000;i++) {
		fa[i]=i;//每一个人都是他家族的祖先
	}
}
int find(int x){//找祖先 
	return fa[x]=fa[x]==x?x:find(fa[x]);
}
bool ask(int x,int y){//查询 
	return find(x)==find(y);//如果x的祖先也是y的祖先，那么他们就是亲戚 
}
void uni(int x,int y){//合并两个家族 
	fa[find(x)]=find(y);//让x的祖先当y的祖先的孩子，就完成了x,y两家族的合并 
}
int main(){
	int n,m,x,y,z;
	init();
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&z,&x,&y);
		if(z==1) uni(x,y);
		else puts(ask(x,y)?"Y":"N");
	}
	return 0;
}
```

### 并查集的启发式合并（按秩合并）

如果让小家族合并到大家族，那么速度还会更快。

AC代码。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int fa[10010];//fa[i]表示i的父亲，祖先的父亲即为自己
int size[10010];//size[i]表示i家族的人数 
void init(){//初始化
	for(int i=0;i<10000;i++) {
		fa[i]=i;//每一个人都是他家族的祖先
		size[i]=1;//每一个家族只有1个人 
	}
}
int find(int x){//找祖先 
	return fa[x]=fa[x]==x?x:find(fa[x]);
}
bool ask(int x,int y){//查询 
	return find(x)==find(y);//如果x的祖先也是y的祖先，那么他们就是亲戚 
}
void uni(int x,int y){//合并两个家族 
	int fx=find(x),fy=find(y);
	if(fx==fy) return;//已经是一个亲戚直接返回
	if(size[fx]>size[fy]) swap(fx,fy);//小家族加入大家族
	fa[fx]=fy;//让小家族的祖先当大家族祖先的儿子 
	size[fy]+=size[fx];//大家族人数加上小家族人数 
}
int main(){
	int n,m,x,y,z;
	init();
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&z,&x,&y);
		if(z==1) uni(x,y);
		else puts(ask(x,y)?"Y":"N");
	}
	return 0;
}
```

每个操作平均时间$O(α(n))$，小于$O(log\,n)$。

### 模板

```cpp
const int MAXN=10000;
struct Union_Find{
	int fa[MAXN+10];
	int size[MAXN+10];
	Union_Find(){
		for(int i=0;i<MAXN;i++) {
			fa[i]=i;
			size[i]=1;
		}
	}
	int find(int x){
		return fa[x]=fa[x]==x?x:find(fa[x]);
	}
	bool ask(int x,int y){
		return find(x)==find(y);
	}
	void uni(int x,int y){
		int fx=find(x),fy=find(y);
		if(fx==fy) return;
		if(size[fx]>size[fy]) swap(fx,fy);
		fa[fx]=fy;
		size[fy]+=size[fx];
	}
};
```

- [AT1339 Union Find](https://www.luogu.com.cn/problem/AT1339)

代码：

```cpp
#include<iostream>
using namespace std;
const int MAXN=100010;
int n,m,z,x,y;
struct unionFind{
    int fa[MAXN];
    unionFind(){
        for(int i=1;i<=MAXN;i++) fa[i]=i;
    }
    int find(int k){
        return fa[k]=fa[k]==k?k:find(fa[k]);
    }
    void uni(int x,int y){
        fa[find(x)]=find(y);
    }
    bool ask(int x,int y){
        return find(x)==find(y);
    }
}U;
int main(){
    cin>>n>>m;
    while(m--){
        cin>>z>>x>>y;
        if(z==0) U.uni(x,y);
        else cout<<(U.ask(x,y)?"Yes":"No")<<endl;
    }
    return 0;
}
```

### 应用：

最小生成树-Kruskal。

### 例题：

##### 简单：

- [P3420 [POI2005]SKA-Piggy Banks](https://www.luogu.com.cn/problem/P3420)

- [P1111 修复公路](https://www.luogu.com.cn/problem/P1111)

- [P1195 口袋的天空](https://www.luogu.com.cn/problem/P1195)

- [P1536 村村通](https://www.luogu.com.cn/problem/P1536)

- [P1547 Out of Hay](https://www.luogu.com.cn/problem/P1547)

- [P1546 最短网络 Agri-Net](https://www.luogu.com.cn/problem/P1546)

##### 较难：

- [P1196 [NOI2002]银河英雄传说](https://www.luogu.com.cn/problem/P1196)

- [P1621 集合](https://www.luogu.com.cn/problem/P1621)

## 种类并查集

好像也有题解管叫反集的。

- [P1892 [BOI2003]团伙](https://www.luogu.com.cn/problem/P1892)

开一个两倍大的并查集，如果$a$和$b$是敌人，就将$a$与$b+n$，$b$与$a+n$连在一起。再假若$a$和$c$也是敌人，那么将$a$与$c+n$，$c$与$a+n$连在一起。这样$b$这个集合里面有$b$,$c$,$a+n$，也就是说$b$和$c$是朋友，他们被间接地被$a+n$给连在一起，实现了敌人的敌人是朋友。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
const int MAXN=1010;
struct unionFind{
    int fa[MAXN*2];//两倍空间 
    unionFind(){
        for(int i=1;i<=MAXN*2;i++) fa[i]=i;//两倍初始化 
    }
    int find(int k){
        return fa[k]=fa[k]==k?k:find(fa[k]);
    }
    void uni(int x,int y){
        fa[find(x)]=find(y);
    }
    bool ask(int x,int y){
        return find(x)==find(y);
    }
}U;
int main(){
	int n,m,x,y,ans=0;
	char c;
	cin>>n>>m;
	for(int i=0;i<m;i++){
		cin>>c>>x>>y;
		if(c=='F'){
			U.uni(x,y);
		}
		else{
			U.uni(y+n,x);//注意：不能写反，下面查祖先只到n，要让n之前的（原数）当祖先 
			U.uni(x+n,y);
		}
	}
	for(int i=1;i<=n;i++){//查找祖先个数 
		if(U.fa[i]==i){
			ans++;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

- [P1525 关押罪犯](https://www.luogu.com.cn/problem/P1525)

思路：对怨气值从大到小排序，尽量把怨气值大的隔开，如果不得不合起来，那这就是最坏的结果。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
const int MAXN=20010;
struct unionFind{
    int fa[MAXN*2];//两倍空间 
    unionFind(){
        for(int i=1;i<=MAXN*2;i++) fa[i]=i;//两倍初始化 
    }
    int find(int k){
        return fa[k]=fa[k]==k?k:find(fa[k]);
    }
    void uni(int x,int y){
        fa[find(x)]=find(y);
    }
    bool ask(int x,int y){
        return find(x)==find(y);
    }
}U;
struct node{
	int u,v,w;
}t[100010];
bool cmp(node a,node b){
	return a.w>b.w;
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++)
		cin>>t[i].u>>t[i].v>>t[i].w;
	sort(t,t+m,cmp);//怨气值从大到小排序 
	for(int i=0;i<m;i++){//从大到小枚举怨气值
		if(U.ask(t[i].u,t[i].v)){//这两个人通过间接方式连成朋友（可以待在一块），但通过直接方式连成仇敌（必须分开）->必须待在一个监狱->完蛋 
			cout<<t[i].w<<endl;
			return 0;//小怨气值不管了，随便分 
		}
		U.uni(t[i].u,t[i].v+n);//连成仇敌 
		U.uni(t[i].v,t[i].u+n);
	}
	cout<<0<<endl;//天下太平 
	return 0;
}

```

- [P2024 [NOI2001]食物链](https://www.luogu.com.cn/problem/P2024)

思路：3倍并查集：$x+n$表示$x$的猎物，$x+2n$表示$x$的天敌。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
const int MAXN=50010;
struct unionFind{
    int fa[MAXN*3];//3倍空间 
    unionFind(){
        for(int i=1;i<=MAXN*3;i++) fa[i]=i;//3倍初始化 
    }
    int find(int k){
        return fa[k]=fa[k]==k?k:find(fa[k]);
    }
    void uni(int x,int y){
        fa[find(x)]=find(y);
    }
    bool ask(int x,int y){
        return find(x)==find(y);
    }
}U;
int n,k,type,x,y,ans;
int main(){
	cin>>n>>k;
	for(int i=0;i<k;i++){
		cin>>type>>x>>y;
		if(x>n || y>n){//假话第二条 
			ans++;
			continue;
		}
		if(type==1){//x,y为同族 
			if(U.ask(x,y+n) || U.ask(x,y+2*n)){//同类不能互吃 
				ans++;
			}
			else{
				U.uni(x,y);//同族连起来 
				U.uni(x+n,y+n);//你的猎物就是我的猎物
				U.uni(x+2*n,y+2*n);//你的天敌就是我的天敌 
			}
		}
		else{//x吃y 
			if(U.ask(x,y) || U.ask(x+2*n,y)){//同族不能互吃，两族不能互吃 
				ans++;
			}
			else{
				U.uni(x,y+2*n);//y的天敌是x 
				U.uni(x+n,y);//y是x的猎物 
				U.uni(x+2*n,y+n);//y的猎物是x的天敌（三种族循环吃） 
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：asasas (赞：3)

这题考察的是：**并查集**

并查集是一种**树型**的**数据结构**，用于处理一些**不相交集合**的**合并及查询**问题。常常在使用中以**森林**来表示。——百度百科

并查集是一种高效，易懂且码量很小的一种高效算法。

在做之前，我们假设$F_i$和$F_j$是父子关系，便于后面解释。

并查集有以下几步环节：

1. 初始化

```cpp
int f[100005];//有多少个点数组就开多大
for (int i=1;i<=n;i++) f[i]=i;//开始，先将自己的父亲设为自己
```
2. 找自己的祖先

```cpp
int find(int x){
	if (f[x]!=x) return f[x]=find(f[x]);//如果祖先不是自己，说明还能在往下找
	return f[x];//当f[x]=x时，说明不能再往下找了，就返回f[x]的值。
}
```

3. 合并（最重要一步）
```cpp
int u(int x,int y){
	f[y]=x;//把y设为x的祖先
}
```
4. 查询
```c
if (f[find(b)]!=f[find(c)]) u(find(b),find(c));//如果祖先不一样，就合并，如果祖先一样就跳过
```
模板题：[P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)和[P1151 亲戚](https://www.luogu.com.cn/problem/P1551)推荐大家练练手。

本题完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int f[500005];//注意数据范围
int find(int x){//查询
	if (f[x]!=x) return f[x]=find(f[x]);
	return f[x];
}
int u(int x,int y){//合并
	f[y]=x;
}
int main(){
	 int n,m,p;
	 cin >> n >> m;
	 int a,b,c;
	 for (int i=1;i<=n;i++) f[i]=i;
	 for (int i=1;i<=m;i++){
	 	cin >> a >> b >> c;
	 	if (a==0){//是0就合并
	 		if (f[find(b)]!=f[find(c)]) 
                        u(find(b),find(c));
	 	}
	 		if (a==1){// 是1就判断
	 		if (f[find(b)]==f[find(c)]) cout << "Yes\n";//判断祖先是否一样
	 		else cout << "No\n";
	 	}
	 }
} 
```


---

## 作者：1lgorithm (赞：1)

#### 这是一道并查集模板题！

并查集，看上去是一个高大上的名字，实际上就是三个函数，这三个函数可以总结成一个借手表的故事。

-------

先说$find$函数。

在一个~~月黑风高~~晚上，大家一起去剧院看戏，这时候有一位同学$a_1$没带表，只能问他的朋友$a_2$.

这时候，如果$a_2$带表了，他就可以告诉$a_1$时间了；但是如果他也没带表，他就只能去问他的朋友$a_3$.

同理，$a_3$也会做$a_2$做过的事，直到有一个人$a_m$他戴手表（主要是没朋友了）了，他就可以把时间告诉$a_1$了。

$find$函数附带着一个数组$f$,存储的就是每一个i的朋友，而$find$函数返回的就是带手表的$m$。

也就是说，$find$函数返回的是他能找到的第一个没朋友的人。

代码:

```cpp
int f[100001];
int findf(int n){
	if(f[n]==n) return n;
	return findf(f[n]);
}
```


--------------

然后就是$merge$函数了。

$merge$函数指的就是给$find(x)$找个朋友$find(y)$,

那样$find(x)$就可以心安理得地扔掉自己的手表，而且想知道时间就可以问$find(y)$了。

代码：

```cpp
void merge(int x,int y){
	if(findf(x)!=findf(y))
		f[findf(x)]=findf(y);
}
```


--------------

最后是$query$函数，它返回的是$find(x)$等不等于$find(y)$.

代码：

```cpp
int query(int x,int y){
	return findf(x)==findf(y);
}
```


----------

讲的那么多，当你把之前我讲的都打上去，你就会发现：

![](http://chuantu.xyz/t6/741/1609515860x-1404755418.png)

--------

优化：路径压缩

路径压缩之际上就是记住谁有表，那样以后再借表就不用一个一个问了。

代码：

```cpp
int findf(int n){
	if(f[n]==n) return n;
	return f[n]=findf(f[n]);
}
```
------

最后别忘了AT特色换行就行了。

总代码：

```cpp
#include<iostream>
using namespace std;
int f[100001];
int findf(int n){
	if(f[n]==n) return n;
	return f[n]=findf(f[n]);
}
void merge(int x,int y){
	if(findf(x)!=findf(y))
		f[findf(x)]=findf(y);
}
int query(int x,int y){
	return findf(x)==findf(y);
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) f[i]=i;
	while(m--){
		int op;
		cin>>op;
		if(op==0){
			int x,y;
			cin>>x>>y;
			merge(x,y);
		}
		else{
			int x,y;
			cin>>x>>y;
			if(query(x,y)==1) cout<<"Yes\n";
			else cout<<"No\n";
		}
	}
}
```



---

## 作者：Raw_Aya9285 (赞：1)

看到题目第一句话了吗？

**“这是并查集的模板题”**

所以答案很显而易见，我们只用手打一份并查集代码就可以轻松AC，而且还可以斩获双倍经验什么的。

先读一读题：

**给出n个点,m个操作.一开始每一个点单独为一个连通块.**

接下来m行,每行一个操作编号,**如果是0,表示连接两个点所在的连通块;如果是1,表示询问两个点是否在一个联通块里,输出"Yes"或者"No".**

也就是说，我们要加一个判断，如果输入了0，那么连接两个元素，否则输出两个元素是否连接。

详情见代码，因为是并查集模板题，就不做太多解释了，大家自行参考代码吧。

---

```cpp
#include<iostream>
using namespace std;
const int Max=200001;
int f[Max];  //储存元素信息的数组

int getf(int v){  //查找根的函数
    if(f[v]==v)  return v;
    else{
        f[v]=getf(f[v]);
        return f[v];
    }
}

void merge(int x,int y){  //将两个元素连接
    int t1,t2;
    t1=getf(x);
    t2=getf(y);
    if(t1!=t2)  f[t2]=t1;
    return;
}

//以上两个函数是并查集的基础，如果看不懂请自行学习并查集
//我就不多解释了

int main(){
    int a,b,x,y,z;
    cin>>a>>b;  //首先输入第一行的两个数
    for(int i=0;i<a;i++)  f[i]=i;  //初始化元素
	
    for(int i=0;i<b;i++){  //对于b次操作的中的每一次，输入操作的种类和操作用到的元素
        cin>>x>>y>>z;
		
        if(x==0){  //如果操作类型是0，则连接两个元素
            int r1=getf(y);
            int r2=getf(z);
            if(r1!=r2)  merge(r1,r2);  //调用函数*1
        }else if(x==1){  //如果操作类型是1，则检测两个元素是否有连接
            if(getf(y)==getf(z))  cout<<"Yes"<<endl;
            else cout<<"No"<<endl;  //调用函数*2
        }
        
    }
    while(1);
    return 0;  //好习惯
}
```
---

大概难度：普及。可以先学习二叉树，再看并查集。

---

## 作者：Snow_Dreams (赞：0)

这道题其实也是一个并查集的裸题，这里主要告诉大家并查集的几个用法（和第一篇题解一样（真.诚信））

初始化：每个节点都是每个节点的父亲，所以：
~~~cpp
for(int i = 1;i <= N;i++) fa[i] = i;
~~~
查找（不压缩）：

~~~cpp
while(x!=fa[x]) x = fa[x];
return x;
~~~

查找（压缩路径）：
```cpp
int find(int x)
{
	int a = x;
    while(x != fa[x]) x = fa[x];
    while(a != fa[a]){
    	int y = a;a = fa[a];fa[y] = x;
	}
	return x;
}
```
原理：每个节点直接导向根节点

合并：

~~~cpp
x = find(x), y = find(y);
fa[x] = y;
~~~

带权并查集：P5092

这道题是明显的并查集，但和普通的并查集不太一样

题意：
```latex
移动（M）：将包含 X 的立方柱移动到包含 Y 的立方柱上。
统计（C）：统计含 X 的立方柱中，在 X 下方的方块数目。
```
然后就不难发现，M操作是将两个积木堆合并，也就是并查集的合并操作，C操作是一个查询工作

这个地方要用带权并查集的思路去做，因为C操作不是去求集合里面的元素个数而是部分，所以就需要用一个另外的方式来维护这些信息

下面先放一下代码：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int N = 500010;
int t;
int fa[N], d[N], size[N];
int find(int x)
{
	if(fa[x] == x) return x;
	int root = fa[x];
	fa[x] = find(fa[x]);
	size[x] = size[fa[x]];
	d[x] += d[root];
	return fa[x];
}
int main()
{
	for(int i = 1;i <= N;i++) fa[i] = i, size[i] = 1;
	scanf("%d",&t);
	for(int i = 1;i <= t;i++){
		char s;cin >> s;
		int x, y;
		if(s == 'M'){
			scanf("%d%d",&x, &y);
			x = find(x), y = find(y);
			fa[x] = y;
			d[x] = size[y];
			size[y] += size[x];
			size[x] = size[y];
		}else{
			scanf("%d",&x);
			find(x);
			printf("%d\n",d[x]);
		}
	}
	return 0;
}
```
在这里，fa数组表示节点父亲，d数组表示边权，d[i]保存了位于编号i的积木下方的积木个数

size数组则表示每个集合的大小

还有一个我要建议的是增强代码可读性，不要把一些操作写在一起，不容易调试

种类并查集：食物链，团伙(代码就不展示了)

最后，这道题的标程：
```cpp
#include<cstdio>
const int N = 2e6+5;
int n, m;
int fa[N];
int find(int x)
{
	int a = x;
    while(x != fa[x]) x = fa[x];
    while(a != fa[a]){
    	int y = a;a = fa[a];fa[y] = x;
	}
	return x;
}
int main()
{
   	scanf("%d%d",&n, &m);
    for(int i = 1;i <= n;i++) fa[i] = i;
    for(int i = 1;i <= m;i++){
        int opt, x, y;scanf("%d%d%d",&opt, &x, &y);
        if(opt == 0) fa[find(x)] = find(y);
        else{
            if(find(x) == find(y)) printf("Yes\n");
            else printf("No\n");
        }
    }
    return 0;
}
```


---

## 作者：谷民 (赞：0)

## 并查集模板+双优化详解

本题为AT中的并查集模板，与洛谷的有三点区别，第一为输出Yes，No（洛谷是YN）。第二为洛谷模板1为合并，本题0为合并。第三数据范围大了。

简介（百度百科）：
>并查集，在一些有N个元素的集合应用问题中，我们通常是在开始时让每个元素构成一个单元素的集合，然后按一定顺序将属于同一组的元素所在的集合合并，其间要反复查找一个元素在哪个集合中。这一类问题近几年来反复出现在信息学的国际国内赛题中，其特点是看似并不复杂，但数据量极大，若用正常的数据结构来描述的话，往往在空间上过大，计算机无法承受；即使在空间上勉强通过，运行的时间复杂度也极高，根本就不可能在比赛规定的运行时间（1～3秒）内计算出试题需要的结果，只能用并查集来描述。

因此并查集由两部分构成——并，查。先讲并，并查集合并是指把两个集合合并，也就是把祖先合并就可以了。查，即为查两个集合祖先是否相同。举个例子：A是B的孩子（B为A父亲），A的爷爷和B的父亲是同一个人，而A与C爷爷是同一个人，他们一定是亲戚。

所以，我们需要写一个函数寻找祖先，我们用递归来写（也可以写记忆化路径压缩优化）

还有合并，我这里写的启发式合并优化，即为合并祖先与秩的一种优化。

详见代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,m,q,b,c,d;
int fa[200005]; //存祖先
int siz[200005]; //存秩
int read(){//快读，可忽略
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int getfa(int x){//查祖先
	if(x!=fa[x]){//逐层递归
		return fa[x]=getfa(fa[x]);//记忆化
	}
	return x;
}
void merge(int x,int y){//合并
	int s1=getfa(x),s2=getfa(y);//找到祖先
	if(s1!=s2){//合并集合即为合并祖先
		if(siz[s1]<siz[s2]){//按秩合并优化
			fa[s1]=s2;
		}
		if(siz[s1]>siz[s2]){
			fa[s2]=s1;
		}
		if(siz[s1]==siz[s2]){
			fa[s2]=s1;
			siz[s2]++;
		}
	}
}
int main(){
	n=read();//快读输入
	m=read();
	for(int i=1;i<=n;i++){//初始化，每个点合并前祖先都是自己，大小为1
		fa[i]=i;
		siz[i]=1;
	}
	for(int i=1;i<=m;i++){
		b=read();
		c=read();
		d=read();
		if(b==0){//合并祖先
			int x=getfa(c),y=getfa(d);
			merge(x,y);
		}
		else{//查祖先是否相同
			if(getfa(c)==getfa(d)){
				printf("Yes\n");
			}
			else{
				printf("No\n");	
			}
		}
	}
	
	return 0;
}
```


---

## 作者：时律 (赞：0)

~~很显然，一道裸的并查集模板~~

~~不知道几倍经验了呢~~

这次讲一讲结构体内的函数，方便写模板：~~这不你谷每个人都会吗~~

一般定义结构体都这样：

```cpp
struct data{
   int a,b;
   char c;
   ...
};
```

加了函数：

```cpp
struct data{
   int a,b;
   char c;
   int plus()
   {
      return a+b;   
   }
   ...
};
```

然后就可以直接这样用：
```cpp
data a;
cin>>a.a>>a.b;
cout<<a.plus();
```

于是写了个模板过这道题：

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int LLLL=100005;
struct BCJ{//并查集模板 
	int u[LLLL];
	void init(int n)//初始化 
	{
		for(int i=0;i<n;i++)
			u[i]=i;
	}
	int find(int s)
	{
		if(u[s]!=s) u[s]=find(u[s]);
		return u[s];
	}
	void merge(int s,int w)//合并 
	{
		u[find(s)]=find(w);
	}
}x;
int main()
{
	int a,b;
	cin>>a>>b;
	x.init(a);
	for(int i=1;i<=b;i++)
	{
		int q,w,e;
		scanf("%d%d%d",&q,&w,&e);
		if(q==0)
			x.merge(w,e);
		if(q==1)
			if(x.find(w)==x.find(e))
				puts("Yes");
			else
				puts("No");
	}
}
```

---

## 作者：xyf007 (赞：0)

# [并查集](https://baike.baidu.com/item/%E5%B9%B6%E6%9F%A5%E9%9B%86/9388442?fr=aladdin)裸题
~~因此不多做解释~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int father[100005];
inline int find(int x)//查找根
{
	if(father[x]!=x)
	  father[x]=find(father[x]);//路径压缩
	return father[x];
}
inline void merge(int x,int y)//合并
{
	x=find(x);
	y=find(y);
	father[y]=x;
} 
inline bool judge(int x,int y)//判断
{
	if(find(x)==find(y))
	  return true;
	else
	  return false;
}
inline void init(int n)//初始化
{
	for(int i=1;i<=n;i++)
	  father[i]=i;
}
int main()
{
	int n,m,z,a,b;
	scanf("%d%d",&n,&m);
	init(n);
	for(int i=1;i<=m;i++)
	  {
	  	scanf("%d%d%d",&z,&a,&b);
	  	if(!z)
	  	  merge(a,b);
	  	else
	  	  if(judge(a,b))
	  	    printf("Yes\n");
	  	  else
	  	    printf("No\n");
	  }
	return 0;
}
```
## 其他例题：
[1.畅通工程](http://acm.hdu.edu.cn/showproblem.php?pid=1232)

[2.亲戚](https://www.luogu.org/problemnew/show/P1551)

[3.Kruskal:还是畅通工程](http://acm.hdu.edu.cn/showproblem.php?pid=1233)

[4.Kruskal:畅通工程再续](http://acm.hdu.edu.cn/showproblem.php?pid=1875)

---

