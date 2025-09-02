# [NOISG 2019 Prelim] Experimental Charges

## 题目背景

翻译自 [NOISG2019 Prelim C.Experimental Charges](https://github.com/noisg/sg_noi_archive/blob/master/2019_prelim/)。

## 题目描述

现有 $N$ 个带电粒子，带正电子的粒子会和带负电子的粒子相互吸引，而带同一种电子的粒子会相互排斥。

有 $Q$ 次操作，每次操作表示为 $T_i,A_i,B_i$，可根据 $T_i$ 的不同分为三种类型：
- `A` 操作代表 $A_i,B_i$ 互相吸引。
- `R` 操作代表 $A_i,B_i$ 互相排斥。
- `Q` 操作询问按照目前已知的信息，如果 $A_i,B_i$ 放在一起，会发生什么。

对于每个 `Q` 操作，如果互相吸引，输出 `A`；如果互相排斥，输出 `R`；如果无法确定，输出 `?`。

保证至少有一种可能使得所有操作不冲突。

## 说明/提示

### 【样例 #1 解释】
对于第一次询问，并不能确定 $1,2$ 之间的关系，输出 `?`。

对于第二次询问，可以确定 $1,2$ 相斥，输出 `R`。
### 【数据范围】
| $\text{Subtask}$ | 分值 | $N,Q$ | $T_i,A_i,B_i$ |
| :----------: | :----------: | :----------: | :----------: |
| $0$ | $7$ | $N=2,Q\leq 10$ | 无 |
| $1$ | $11$ | 无 | $A_i=1$ 或 $B_i=1$ |
| $2$ | $14$ | 无 | $T_i$ 仅可能为 `R` 或 `Q` |
| $3$ | $12$ | 无 | 所有关系给出后才有查询操作 |
| $4$ | $25$ | $1\leq N,Q \leq 10^3$ | 无 |
| $5$ | $31$ | 无 | 无 |

对于 $100\%$ 的数据：
- $1 \leq N,Q \leq 10^5$
- $1 \leq A_i \neq B_i \leq N$
- $T_i$ 仅可能为 `A`，`R` 或 `Q`。

## 样例 #1

### 输入

```
2 3
Q 1 2
R 1 2
Q 1 2```

### 输出

```
?
R```

## 样例 #2

### 输入

```
4 5
R 1 2
A 2 3
A 1 4
Q 2 4
Q 1 3```

### 输出

```
A
A```

# 题解

## 作者：wcy110614 (赞：9)

**前置知识：并查集。**

虽然这道题并不算太难，但是没见过这个套路还是有难度的。

考虑将每个点加一个对应的虚点，比如 $A\rightarrow A'$ 表示 $A'$ 的所带的电荷和 $A$ 相反。

1. 如果 $A,B$ 互相吸引，那么 $A,B$ 所对应的集合相反，则 $A - B',B-A'$ 连边。

2. 如果 $A,B$ 互相排斥，说明 $A,B$ 所在的集合相同，则 $A - B,A'-B'$ 连边。

3. 分类讨论判断 $A,B$ 所在的集合。如果 $A,B$ 之间有边，$A,B$ 就会有相同电荷，排斥。如果 $A,B'$ 之间有边，$A,B$ 就会有不同电荷，吸引。如果这两条边都没有，那就完全得不到任何关系，这个时候输出 `?`。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
int n,m,f[N];
int gf(int x){return x==f[x]?f[x]:f[x]=gf(f[x]);}
void link(int x,int y){
	int u=gf(x),v=gf(y);
	f[u]=v;
}
int main(){
	for(int i=1;i<N;++i)f[i]=i;
	cin>>n>>m;
	while(m--){
		char op;int a,b;
		cin>>op>>a>>b;
		if(op=='A')link(a,b+n),link(a+n,b);
		else if(op=='R')link(a,b),link(a+n,b+n);
		else{
			int fl=0;
			if(gf(a)==gf(b)||gf(a+n)==gf(b+n))cout<<'R';
			else if(gf(a+n)==gf(b)||gf(a)==gf(b+n))cout<<'A';
			else cout<<'?';
			cout<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：yx666 (赞：2)

# 题解：P10734 Experimental Charges
$$\text{Description}$$

有 $N$ 个带电粒子，带正电子的会和带负电子的相互吸引，而带同一种电子的会相互排斥。

有 $Q$ 次操作，每次操作为 $T_i,A_i,B_i$，可根据 $op$ 的不同分为三种类型：

- `A`：$A_i,B_i$ 互相吸引。

- `R`：$A_i,B_i$ 互相排斥。
- `Q`：按照目前已知的信息，如果 $A_i,B_i$ 放在一起，会发生什么。

对于每个 `Q` 操作，互相吸引，输出 `A`；互相排斥，输出 `R`；无法确定，输出 `?`（每个输出均占一行）。

对于所有数据，$1 \leq N,Q \leq 10^5$。

$$\text{Solution}$$

拓展域并查集（**并查集**加**反集**），例题：[团伙](https://www.luogu.com.cn/problem/P1892)。

应用到本题中，即为：

记 $f_i$ 表示并查集数组，其中 $\forall i\in [1,n]$ 表示题目中给出的粒子，$\forall i\in[n+1,2n]$ 表示虚构出来的粒子。

对于原有的粒子 $a$，粒子 $a+n$ 与其正负相反（正就是带正电子，负就是带负电子，下同）。

相应的，合并策略也会有更改：对于一对粒子 $(a,b)$，有：

1. $(a,b)$ 互相吸引（$op$ 为 `A`），即 $(a+n,b)$ 正负相同，$(a,b+n)$ 正负相同，合并 $(a,b+n),(a+n,b)$。

2. $(a,b)$ 互相排斥（$op$ 为 `R`），即 $(a,b)$ 正负相同，$(a+n,b+n)$ 正负相同，合并 $(a,b),(a+n,b+n)$。

对于每次查询的一对粒子 $(a,b)$，有三种情况：

1. 知道 $(a,b)$ 正负相反，即 $f_a=f_{b+n}$ 时，输出 `A`，互相吸引。

2. 知道 $(a,b)$ 正负相同，即 $f_a=f_b$ 时，输出 `R` ，互相排斥。

3. 不知 $(a,b)$ 正负是否相同，即 $f_a\ne f_b$ 且 $f_a\ne f_{b+n}$ 时，输出 `?`，不知道。

$$\text{Code}$$

需要注意两点：

1. 并查集数组要开两倍，初始化也是两倍。

2. 输出时，同极相斥，正负相同输出 `R`。

``` cpp
#include<stdio.h>

#define gc() getchar()
#define pc(x) putchar(x)

#define N 100005

int n,q,fa[N<<1];
static inline int getFa(int x){		// 非递归式路径压缩找爸爸
	int rx=x,t=x;
	while(rx!=fa[rx]) rx=fa[rx];
	while(fa[x]!=rx){
		t=fa[x];
		fa[x]=rx;
		x=t;
	}return rx;
}
static inline void merge(int x,int y){	// 合并 (x,y)
	fa[getFa(x)]=getFa(y);
}

signed main(){
	n=read(),q=read();
	for(int i=n<<1;i;--i)		// 初始化并查集 
		fa[i]=i; 
	
	int ch,a,b;
	while(q--){
		do{
			ch=gc();
		}while(ch!='Q'&&ch!='R'&&ch!='A');
		
		a=read(),b=read();
		
		switch (ch) {
		case 'A':		// 相吸（正负相反）
			merge(a,b+n),merge(a+n,b);
			
			break;
		case 'R':		// 相斥（正负相同）
			merge(a,b),merge(a+n,b+n);
			
			break;
		case 'Q':		// 询问
			if(getFa(a)==getFa(b+n)) 			// 正负相反，相吸
				pc('A');
			else if(getFa(a)==getFa(b))			// 正负相同，相斥 
				pc('R');
			else								// 无法判断 
				pc('?');
			
			pc('\n');
			break;
		}
	}
	
	return 0;
}
```

---

## 作者：hard_learn (赞：1)

# 简要题意
题目要求处理一系列操作，这些操作涉及对粒子之间关系的管理和查询。初始时有 $N$ 个粒子，有 $Q$ 个操作，每个操作可以是以下三种之一：

- `A i j`: 表示粒子 $i$ 和粒子 $j$ 之间存在吸引关系。

- `R i j`: 表示粒子 $i$ 和粒子 $j$ 之间存在斥力关系。

- `Q i j`: 查询粒子 $i$ 和粒子 $j$ 之间的关系，可能是吸引 `A`、斥力 `R` 或者不确定 `?`。

通过这些操作，需要动态地维护和查询粒子之间的关系，并输出每个查询操作的结果。

# 思路
当为 `A` 操作时，$a$ 的正电子与 $b$ 的负电子吸引，$b$ 的正电子与 $a$ 的负电子吸引。所以 $a$ 的正电子和 $b$ 的负电子在同一集合，$b$ 的正电子和 $a$ 的负电子在同一集合,进行合并表示吸引。

当为 `R` 操作时，$a$ 的正电子与 $b$ 的正电子排斥，$b$ 的负电子与 $a$ 的负电子排斥。所以 $a$ 的正电子和 $b$ 正的电子在同一集合，$a$ 的负电子和 $b$ 的负电子在同一集合，进行合并表示排斥。

当为 `Q` 操作时，查询 $a$ 的正电子与 $b$ 的正电子的关系，$a$ 的负电子与 $b$ 的负电子的关系，$a$ 的正电子与 $b$ 的负电子的关系，$a$ 的负电子与 $b$ 的正电子的关系。

# 注意
- 因为该方法只用了一个并查集，所以初始化时应该为 $1$ 到 $2 \times n$。

- 正，负分子的表示方法代码中已经解释。
# 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q;
int a[200005];
int find(int x){
	if(a[x]==x){
		return x;
	}
	else{
		return a[x]=find(a[x]);//路径压缩（更快） 
	}
}//寻找 
void unit(int i,int j){
	a[find(i)]=find(j); 
}//合并 
signed main(){
	cin>>n>>q;
	for(int i=1;i<=2*n;i++){
		a[i]=i;
	}//1~n为正电子，n+1~2*n为负电子 
	while(q--){
		char t;
		cin>>t;
		int a,b;
		cin>>a>>b;
		if(t=='A'){
			unit(a,b+n);
			unit(a+n,b);
		}
		else if(t=='R'){
			unit(a,b); 
			unit(a+n,b+n); 
		}//27~33行 带正电子的粒子会和带负电子的粒子相互吸引，而带同一种电子的粒子会相互排斥。
		else{
			if(find(a)==find(b)||find(a+n)==find(b+n)){
				cout<<"R"<<endl;
			}
			else if(find(a)==find(b+n)||find(a+n)==find(b)){
				cout<<"A"<<endl;
			}
			else{
				cout<<"?"<<endl;
			}
		}
	}
	return 0;
}
```

---

## 作者：junee (赞：1)

# P10734 题解

## 前置知识

并查集。

## 题目分析

这题基本跟 [团伙](https://www.luogu.com.cn/problem/P1892) 一样，都是反集的题目，当两个粒子排斥时，说明他们是一个集合的，当两个粒子吸引时，说明他们互相在对方的反集里面，用一个数组记录他们相反的粒子的集合。

## Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int N=2e5+10;
int p[N],e[N];
int find(int x){
	if(p[x]!=x)p[x]=find(p[x]);
	return p[x];
}
void merge(int u,int v){
	u=find(u),v=find(v);
	if(u!=v)p[u]=v;
}
int n,q;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=2*n;i++)p[i]=i,e[i]=i+n;
	while(q--){
		char op;
		int u,v;
		cin>>op>>u>>v;
		if(op=='Q'){
			if(find(u)==find(v)){
				cout<<'R'<<'\n';
			}
			else if(find(u)==find(e[v])||find(v)==find(e[u])){
				cout<<'A'<<'\n';
			}
			else cout<<"?"<<'\n';
		}
		else if(op=='A'){
			merge(e[u],v);
			merge(e[v],u);
		}
		else if(op=='R'){
			merge(u,v);
			merge(e[u],e[v]);
		}
	}
	return 0;
}
```

---

## 作者：maomao233 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10734)

反集题。  
我们可以将这 $N$ 个带电粒子各虚构出一个带电粒子，其电性与原来的带电粒子相反。  
具体地，我们将表示父亲节点的数组大小开到 $2N$，其前 $N$ 个元素为原来的带电粒子，后 $N$ 个元素为与原来的带电粒子电性相反的带电粒子。  
令表示父亲节点的数组名为 $fa$。结合题意我们得知“同性相斥，异性相吸”，那么结合上文可以得到对于每个 $1\le i\le N$，带电粒子 $fa_i$ 与 $fa_{i+N}$ 互相吸引。

如果带电粒子 $A_i,B_i$ 互相吸引，那么 $A_i,B_i$ 的电性相反，所以 $A_{i+N},B_i$ 的电性相同或 $B_{i+N},A_i$ 的电性相同。于是我们合并 $(A_{i+N},B_i)$、$(B_{i+N},A_i)$ 这两对带电粒子。  
如果带电粒子 $A_i,B_i$ 互相排斥，那么 $A_i,B_i$ 的电性相同，所以 $A_{i+N},B_{i+N}$ 的电性也相同。于是我们合并 $(A_i,B_i)$、$(A_{i+N},B_{i+N})$ 这两对带电粒子。

询问时，我们将上述结论反过来。  
如果 $A_{i+N},B_i$ 的电性相同或 $B_{i+N},A_i$ 的电性相同（实际只用判断一个即可），那么带电粒子 $A_i,B_i$ 互相吸引；  
如果 $A_i,B_i$ 的电性相同，那么带电粒子 $A_i,B_i$ 互相排斥；  
如果两者都不满足，则无法确定带电粒子 $A_i,B_i$ 的关系。

过程套并查集模板即可。

```cpp
int fa[200010];
inline int fd(int x)
{
	if(x==fa[x])
	{
		return x;
	}
	return fa[x]=fd(fa[x]);
}
signed main()
{
	int n,q;
	rd(n,q);
	for(int i=1;i<=n*2;i++)
	{
		fa[i]=i;
	}
	while(q--)
	{
		char c;
		int a,b;
		cin>>c,rd(a,b);
		if(c=='A')
		{
			int x=fd(a+n),y=fd(b);
			fa[x]=y;
			x=fd(b+n),y=fd(a);
			fa[x]=y;
		}
		else if(c=='R')
		{
			int x=fd(a),y=fd(b);
			fa[x]=y;
			x=fd(a+n),y=fd(b+n);
			fa[x]=y;
		}
		else
		{
			puts(fd(a+n)==fd(b)||fd(b+n)==fd(a)?"A":fd(a)==fd(b)?"R":"?");
		}
	}
	return 0;
}
```

---

## 作者：LG086 (赞：1)

### 分析
并查集。

首先搞清楚的是：同极相斥，异极相吸。  
于是数组长度要搞成 $2\times N$ 以上，前 $N$ 个带电粒子与后 $N$ 个想象出来的粒子分别相吸引，即对于每个带电粒子 $f_i (i\le N)$，有 $f_i$ 与 $f_{i+N}$ 相吸。

把同极粒子归到一个集合里。  
若两个粒子相吸，则合并 $A_i$ 和 $B_{i+N}$，$A_{i+N}$ 和 $B_i$。否则合并 $A_i$ 和 $B_{i}$，$A_{i+N}$ 和 $B_{i+N}$。

在查询时，如果 $A_i$ 与 $B_{i+N}$ 有同极，则 $A_i$ 和 $B_i$ 相吸引；若 $A_i$ 与 $B_{i}$ 有同极，则两个粒子相排斥；若压根不知道两个粒子是否同极，反手输出一个 `?` 即可。

------------
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,a,b,f[1919810];char t;
int find(int x){
    if(f[x]==x)return x;
    return f[x]=find(f[x]);
}
void com(int a,int b){
    f[find(a)]=find(b);
    return;
}
void init(int n){
    for(int i(1);i<=n*2;i++)
    f[i]=i;return;
}
int main(){
    cin>>n>>q;
    init(n);
    while(q--){
        cin>>t>>a>>b;
        if(t=='A')
        com(a,b+n),com(b,a+n);
        else if(t=='R')
        com(a,b),com(a+n,b+n);
        else{
            if(find(a)==find(b+n))puts("A");
            else if(find(a)==find(b))puts("R");
            else puts("?");
        }
    }
}
```

---

## 作者：xxseven (赞：1)

种类并查集入门题。

我们发现合并操作有两种：两个粒子相同电性或相反电性。为了表示电性的相同和相反，我们需要引入反集。

具体地，我们的并查集数组需要开到 $2 \times n$，其中 $1$ 到 $n$ 表示原来的粒子， $n+1$ 到 $n+n$ 表示的是我们虚构出来的粒子，其中 $x+n$ 与 $x$ 的电性相反。

在合并的时候，如果 $x,y$ 电性相同，那么我们将 $(x,y)$ 和 $(x+n,y+n)$ 这两对粒子分别合并，如果 $x,y$ 电性相反，我们将 $(x,y+n)$ 和 $(x+n,y)$ 这两对粒子分别合并。  
在查询的时候，如果 $x,y$ 的祖先相同，说明 $x,y$ 电性相同，如果 $x,y+n$ 的祖先相同，说明 $x,y$ 电性相反。
  
另外本题还有一个小坑点：相斥是相同电性，相容是不同电性，如果你写反了会通不过样例 2。

完成这道题后，可以继续完成更多种类并查集的题目。  
[P1892 [BOI2003] 团伙](https://www.luogu.com.cn/problem/P1892)  
[P1525 [NOIP2010 提高组] 关押罪犯](https://www.luogu.com.cn/problem/P1525)  
[P2024 [NOI2001] 食物链](https://www.luogu.com.cn/problem/P2024)

下面是完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+6;
int pre[N<<1],n,m;//并查集数组要开到两倍
int find(int x){
	return pre[x]==x?x:pre[x]=find(pre[x]);
}
void unity(int x,int y){
	pre[find(x)]=find(y);
}
char op;
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n*2;++i) pre[i]=i;//初始化也要两倍
	for(int x,y,i=1;i<=m;++i){
		cin>>op>>x>>y;
		if(op=='A'){
			unity(x,y+n); unity(x+n,y);
		}
		if(op=='R'){
			unity(x,y); unity(x+n,y+n); 
		}
		if(op=='Q'){
			if(find(x)==find(y+n)) cout<<"A\n";
			else if(find(x)==find(y)) cout<<"R\n";
			else cout<<"?\n";
		}
	}
	return 0;
}

```

希望这篇题解能够帮到你！

---

## 作者：cmask4869 (赞：0)

## 思路
一眼望上去并查集，类似于 P1892。两种操作，当两种粒子互相吸引时，将 $(a,b+n)$ 和 $(a+n,b)$ 合并。当相互排斥时，将 $(a,b)$ 和 $(a+n,b+n)$ 合并。查询时判断 $(x,y)$ 祖先和 $(x,y+n)$ 祖先就可以完成操作了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std ;
typedef long long ll ;
const int N=200005 ;
int fa[N] ;
int n,m ;

int find(int x){ //找根 
	if (fa[x]==x) return x ;
	return fa[x]=find(fa[x]) ; // 并查集板子，这样做效率高一些 ; 
}

void merge(int a,int b){
	int pa=find(a),pb=find(b) ;
	fa[pa]=pb ;
}

int main(){
	cin >> n >> m ;
	for (int i=1 ; i<=n*2 ; i++) fa[i]=i ;
	while (m--){
		char p[2] ;
		int a,b ;
		scanf("%s %d %d", p, &a, &b) ;
		if (p[0]=='A'){
			merge(a,b+n) ; merge(a+n,b) ; 
		} 
		if (p[0]=='R'){
			merge(a,b) ; merge(a+n,b+n) ;
		}
		if (p[0]=='Q'){
			if (find(a)==find(b+n)) cout << "A" << "\n" ;
			else if (find(a)==find(b)) cout << "R" << "\n" ;
			else cout << "?" << "\n" ;
		}
	}
	return 0 ;
}
```

---

