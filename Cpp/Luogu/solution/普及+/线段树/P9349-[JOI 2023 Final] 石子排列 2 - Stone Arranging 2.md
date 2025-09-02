# [JOI 2023 Final] 石子排列 2 / Stone Arranging 2

## 题目描述

JOI 君有 $N$ 颗围棋子。这些棋子从 $1$ 到 $N$ 编号。每颗棋子的颜色是一个介于 $1$ 和 $10^9$ 之间的整数（包含 $1$ 和 $10^9$）。一开始，第 $i$ 颗棋子（$1 \le i \le N$）的颜色是 $A_i$。

接下来，JOI 君将进行 $N$ 次操作。他会将棋子排成一行放在桌子上。第 $i$ 次操作（$1 \le i \le N$）将按如下方式进行：

1. JOI 君将第 $i$ 颗棋子放在第 $i-1$ 颗棋子的右边。但是，当 $i = 1$ 时，JOI 君会将第 1 颗棋子放在桌子上。
2. 如果在第 $1, 2, \cdots, i-1$ 颗棋子中有一颗棋子的当前颜色与第 $i$ 颗棋子的颜色相同，设 $j$ 为此类棋子的最大索引，JOI 君将用颜色 $A_i$ 涂色第 $j+1, j+2, \cdots, i-1$ 颗棋子。

为了确认操作是否正确执行，JOI 君想提前知道所有操作执行后棋子的颜色。

给定围棋子的相关信息，编写一个程序来确定 $N$ 次操作后棋子的颜色。

## 说明/提示

## 样例

### 样例 1

操作按下表执行。

![](https://cdn.luogu.com.cn/upload/image_hosting/0newqhzt.png)

最终，第 1, 2, 3, 4, 5, 6 颗棋子的颜色分别为 1, 1, 1, 2, 2, 2。

此样例输入满足子任务 1, 3 的约束。

### 样例 2

此样例输入满足所有子任务的约束。

## 约束

- $1 \le N \le 2 \times 10^5$。
- $1 \le A_i \le 10^9$ ($1 \le i \le N$)。
- 给定的值都是整数。

## 子任务

1. (25 分) $N \le 2 000$。
2. (35 分) $A_i \le 2$ ($1 \le i \le N$)。
3. (40 分) 无额外约束。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
6
1
2
1
2
3
2
```

### 输出

```
1
1
1
2
2
2
```

## 样例 #2

### 输入

```
10
1
1
2
2
1
2
2
1
1
2
```

### 输出

```
1
1
1
1
1
1
1
1
1
2
```

# 题解

## 作者：262620zzj (赞：5)

首先读题后，如果直接按照题目模拟，每次放置新棋子就寻找之前的同一颜色棋子，那么复杂度 $O(n^2)$ 显然超时了，不行。

## 低复杂度做法
定义**最后一个颜色是 $c$ 的棋子的位置**是 $last_c$，$1 \sim n$ 扫一遍数组，$i \sim last_{color[i]}$ 区间颜色均为 $color[i]$，并且不会被其他染色操作所影响。


那为什么这样是对的呢？(以下简称 $last_{color[i]}$ 为 $lci$）如果有其他的染色操作影响了 $i \sim lci$ 这个区间的话，设影响该区间的区间为 $l \sim r$。

- 如果 $l>lci$，则 $l \sim r$ 和 $i \sim lci$ 不相交。

- 如果 $l<lci$ 且 $r<lci$，则 $l \sim r$ 被 $i \sim lci$ 覆盖，可以略去。

- 如果 $l<lci$ 且 $r>lci$，则在遍历到 $r$ 之前， $i \sim lci$ 已经将 $l$ 染色，此种情况不可能出现。

综上所述，以此方法将一段区间染色后，区间内棋子不会再改变颜色，这样就可以在每次染色之后直接令 $i=lci+1$，总复杂度 $O(n)$。

最后注意 $A[i]\le10^9$，所以用一个 map 解决下标过大的问题。
## 代码
```
#include<cstdio>
#include<map>
using namespace std;
const int N=2e5+5;
int n,color[N];
map<int,int> last; 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&color[i]);
		last[color[i]]=i;
	}
	for(int i=1;i<=n;i++){
		int lci=last[color[i]];
		for(int j=i+1;j<lci;j++)color[j]=color[i];
		i=lci;
	}
	for(int i=1;i<=n;i++)printf("%d\n",color[i]);
	return 0;
}
```


---

## 作者：CheerJustice (赞：3)

### [点我传送](https://www.luogu.com.cn/problem/P9349)

## solution：

对于每个棋子的颜色 $ a_{i} $，如果每次都枚举满足题意的 $ j $，$ O(n^{2}) $ 显然超时，并且每种颜色我们处理了很多次。如果用草稿纸模拟几个数据，我们会发现一个规律：**每种颜色的涂色结果都是从最早出现的编号涂到最后出现的编号**。当然，每个棋子最早出现的编号是指**还没被别的棋子涂色**的最早编号。

所以我们可以在读入时预处理出桶 $ m[a_{i}] $，表示颜色为 $ a_{i} $ 的棋子的**最后出现的编号**。在遍历到 $ i $ 号棋子时，将第 $ i $ 到第 $ m[a_{i}] $ 号棋子全部涂色一遍即可，这样每种颜色一遍就可以全部处理好，总时间复杂度 $ O(n) $，具体细节请看注释。


PS：个人感觉应该是橙。

## code：
``` c++
#include <bits/stdc++.h>
using namespace std;
inline int in(){
	char c=getchar();int f=1;int x;
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-')f=-1,c=getchar();
	for(x=0;c>='0'&&c<='9';c=getchar())
		x=(x<<3)+(x<<1)+(c^48);
	return x*f;
}
template <typename T>
inline void in(T &x){
	char c=getchar();int f=1;
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-')f=-1,c=getchar();
	for(x=0;c>='0'&&c<='9';c=getchar())
		x=(x<<3)+(x<<1)+(c^48);
	x*=f;
}
//以上为快读，请允许我略~
const int N=200005;
int a[N];
map<int,int> m;// 因为a[i]<=1e9,所以开map
int main(){
	int n=in(); 
	for(int i=1;i<=n;i++) 
		in(a[i]),m[a[i]]=i;
	for(int i=1;i<=n;i=m[a[i]]+1)// 小细节,每次涂色之后i到m[a[i]]的颜色都一样，直接跳到末尾就好了
		for(int j=i;j<=m[a[i]];j++)
			a[j]=a[i];// 覆盖过程
	for(int i=1;i<=n;printf("%d\n",a[i++]));
	return 0;
}
```

---

## 作者：AkeRi (赞：3)

# Description
将 $n$ 个棋子从左到右依次排列，第 $i$ 个棋子的颜色是 $a_i$。

被同色的两个棋子夹住的棋子会变成同样的颜色。求各个棋子的最终颜色。

# Solution
简单题。
## 25pts
暴力扫一遍，时间复杂度 $\text{O}(n^2)$。

## 35pts
只有两种颜色，考虑对于一个棋子，从 $a_1$ 覆盖到**最右边**的第 $i$ 个棋子使得 $a_i=a_1$，扫一遍找到这个 $i$，左边的即为颜色 $1$，右边的即为颜色 $2$。

## 100pts

和 35 分做法一样，对于每个棋子都找到它最右边的颜色和他相同的棋子，记录一下直接覆盖即可。注意颜色值域最高到 $10^9$，所以需要离散化，或者用 `map`。

复杂度 $\text{O}(n\log n)$。

### Code
```cpp
int n=read(),a[KI];
int main()
{
    std::unordered_map<int,int>p;
    for(int i=1;i<=n;i++) a[i]=read(),p[a[i]]=i;
    for(int i=1;i<=n;i++) p[a[i]]=std::max(p[a[i]],i);
    for(int i=1;i<=n;i++)
    {
        int nxt=p[a[i]];
        for(int j=i;j<=nxt;j++) a[j]=a[i];
        i=nxt;
    }
    for(int i=1;i<=n;i++) std::cout<<a[i]<<'\n';
}
```

---

## 作者：comcopy (赞：0)

题意略。

显然~~数据结构学傻的~~我们发现区间覆盖，直接上线段树。

考虑 `lst[a[i]]` 表示当前点颜色相同的最大下标，当 `lst[a[i]]` 被覆盖的时候，可以保证之后到当前位置都不会有相同颜色的点出现，所以不用考虑被覆盖后的下标传递。

显然我们用区间覆盖，单点查询的线段树暴力维护，若发现前面的点没被覆盖，则覆盖这段区间。

是个常数巨大的 $O(n\log n)$。

```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<map>
using namespace std;
const int N=2e5+10,mod=1e4+7;

struct fffffyn{
	int tag[N<<2];
	#define MID(l,r) (((r-l)>>1)+l)
	#define ls (now<<1)
	#define rs (now<<1|1)
	inline void insert(int pos,int val,int nl,int nr,int now){
		if(nl==nr) return void(tag[now]=val);
		int mid(MID(nl,nr));
		pos<=mid?insert(pos,val,nl,mid,ls):insert(pos,val,mid+1,nr,rs);
		return pushup(now);
	}
	inline void pushdown(int now){
		if(tag[now]) tag[ls]=tag[rs]=tag[now];
		tag[now]=0;
	}
	inline void pushup(int now){
		tag[now]=(tag[ls]==tag[rs]?tag[ls]:0);
	}
	inline void update(int l,int r,int nl,int nr,int now,int val){
		if(l<=nl && nr<=r) return void(tag[now]=val);
		int mid(MID(nl,nr));
		pushdown(now);
		l<=mid&&(update(l,r,nl,mid,ls,val),1);
		mid<r&&(update(l,r,mid+1,nr,rs,val),1);
		return pushup(now);
	}
	inline int query(int l,int nl,int nr,int now){
		if(tag[now])return tag[now];
		int mid(MID(nl,nr));
		return l<=mid?query(l,nl,mid,ls):query(l,mid+1,nr,rs);
	} 
}tre;
int n;
map<int,int>lst;
signed main(){
	scanf("%d",&n);
	for(int i=1,x;i<=n;++i) {
		scanf("%d",&x);
		if(lst[x]&&(tre.query(lst[x],1,n,1)==x))tre.update(lst[x],i-1,1,n,1,x);
		tre.insert(i,x,1,n,1),lst[x]=i;
	}
	for(int i=1;i<=n;++i) printf("%d\n",tre.query(i,1,n,1));
	return(0-0);
}
```

---

## 作者：sxq9 (赞：0)

## 60分做法
在每一个棋子 $i$ 的时候，向前寻找最前面的 $j$ 号棋子，使得 

$$a_i=a_j$$

但是会有一个点超时。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010];map<int,int>m;
void c(int l,int r,int co){
	for(int i=l+1;i<r;i++){
		a[i]=co;
	}
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[m[a[i]]]==a[i])c(m[a[i]],i,a[i]);
		m[a[i]]=i;
	}
	for(int i=1;i<=n;i++){
		cout<<a[i]<<endl;
	}
    return 0;
}
```

## 满分方法

对于每一种颜色，记录该颜色的最大棋子，每一颗棋子遍历到时，将它到最大的棋子的区间染色，并直接跳至最大值。

AC code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010];map<int,int>r;
void c(int l,int r,int co){//染色
	for(int i=l+1;i<r;i++){
		a[i]=co;
	}
}
int main(){	
    int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		r[a[i]]=i;//记录最大值
	}
	for(int i=1;i<=n;i++){
		c(i,r[a[i]],a[i]);i=r[a[i]];
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",a[i]);
	}
    return 0;
}
```

$by\space sxq$

---

## 作者：zhuweiqi (赞：0)

$O(n^2)$ 的暴力枚举做法为花一重循环枚举每个 $i$（$1\leq i\leq n$），再花一重循环找到 $j$ 并修改 $a_{j+1}$ 至 $a_{i-1}$ 之间的所有元素或者发现根本不存在 $j$，我们考虑优化。

首先，考虑优化找到 $j$ 的时间复杂度。这个应该不难想到，我们可以用向量 $v_k$ 来存储**当前**颜色为 $k$ 的棋子出现的位置且 $v_k$ 应是升序排列的，这样一来，对于每个 $i$，如果 $v_{a_i}$ 是空的，就说明不存在 $j$；反之 $j$ 就是 $v_{a_i}$ 的最后一个元素。但是我们可以发现一个明显的问题，颜色 $k$ 是一个介于 $1$ 到 $10^9$ 之间的数，你要真开这么大的向量的话就爆内存了，但是不同的 $k$ 的个数又不会超过 $n$ 的范围，即 $2\times 10^5$，所以我们可以使用离散化来解决这个问题，记录每个离散化之前的值对应的离散化之后的值和每个离散化之后的值对应的离散化之前的值，为输出所用。

接下来，我们考虑优化修改 $a_{j+1}$ 至 $a_{i-1}$ 之间的所有元素的时间复杂度，欸？区间修改，这不线段树吗？就用你了！我们每次用线段树来维护区间修改的元素，设当前节点为 $k$，左端点为 $l$，右端点为 $r$，那么只有当 $j+1\leq l$ 并且 $r\leq i-1$ 才能把 $c_k$（线段树的值）赋值为 $a_i$，当然还需要一个记录修改的先后顺序的数组，令其为 $od$，因为后修改的元素永远不会被先修改的元素影响，后面会讲它的具体用法。

但是，线段树维护之后，颜色是修改了，可是我们的向量 v 还没修改呢！我们需要把所有的 $v_{a_p}$（$j+1\leq p\leq i-1$）的最后一个元素弹出，因为它们都被修改为了不同于自己原来的颜色 $a_i$，我们还需要把所有的 $p$ 插入到向量 $v_{a_i}$ 的末尾，这样一来时间复杂度不就又变成 $O(n^2)$ 了吗？

我们还需要优化！考虑优化使每个 $a_i$ 只会弹出或插入进对应的向量末尾一次。我们仔细分类讨论可以发现，对于任何一个 $newi$（$i<newi\leq n$），如果其存在一个 $newj$：如果在 $a_i$ 及之前存在一个与 $a_{newi}$ 相同的颜色，则 $i\leq newj$，反之则 $newj<j$，总之就是无论如何都与 $a_{i+1}$ 到 $a_{j-1}$ 这段区间无关，这段区间要改一起改，而且还是和 $a_i$ 和 $a_j$ 一起改，因为它们已经是相同的颜色了，所以我们在修改向量时根本没必要遍历它们，或者说是把他们看成一个整体，因此我们选择用一个链表数组（记为 $r$）来存储下一个需要遍历的元素的下标，初始化 $r_i$ 赋值为 $i+1$，$r_n$ 赋值为 $0$，我们每次只需要用一个 while 循环遍历 $j+1$ 至 $i-1$ 并修改对应的向量就可以了。每次操作结束后还要把 $i$ 插入进 $v_{a_i}$ 的末尾！

最后，就是我们访问线段树并得出答案的收尾工作啦，我们需要 $3$ 个变量 $k$、$l$ 和 $r$，分别表示线段树的节点编号，当前区间的左端点和右端点。如果 $l=r$：如果 $c_k\ne 0$，$ans_l$ 赋值为 $c_k$；否则说明 $a_l$ 根本没被修改过，$ans_l$ 赋值为 $a_l$；否则向 $2k$ 和 $2k+1$ 两个子节点继续遍历，其中需要判断，如果 $od_k>od_{2k}$，那么就需要把 $c_{2k}$ 赋值为 $c_k$，把 $od_{2k}$ 赋值为 $od_k$，$2k+1$ 同理。最后的最后，对于每个 $i$，我们只需要输出 $ans_i$ 其对应的在离散化之前的值就可以了。参考代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9'){
		n=(n<<3)+(n<<1)+(c^48);
		c=getchar();
	}
	return n;
}
int a[200002],r[200002];
map<int,int> num,now;
vector<int> v[200002];
int c[800002],od[800002];
void change(int k,int l,int r,int x,int y,int z,int t){
	if(y<l || r<x) return;
	if(x<=l && r<=y){
		c[k]=z,od[k]=t;
		return;
	}
	int mid=l+r>>1;
	change(k<<1,l,mid,x,y,z,t);
	change((k<<1)+1,mid+1,r,x,y,z,t);
	return;
}
int ans[200002];
void final(int k,int l,int r){
	if(l==r){
		if(c[k]==0) ans[l]=a[l];
		else ans[l]=c[k];
		return;
	}
	int mid=l+r>>1;
	if(c[k]){
		if(od[k<<1]<od[k]) c[k<<1]=c[k],od[k<<1]=od[k];
		if(od[(k<<1)+1]<od[k]) c[(k<<1)+1]=c[k],od[(k<<1)+1]=od[k];
	}
	final(k<<1,l,mid);
	final((k<<1)+1,mid+1,r);
	return;
}
int main(){
	int n=read(),cnt=0;
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(num[a[i]]==0) now[++cnt]=a[i],a[i]=num[a[i]]=cnt;
		else a[i]=num[a[i]];
		r[i]=i+1;
	}
	r[n]=0;
	for(int i=1;i<=n;i++){
		if(!v[a[i]].empty()){
			int last=v[a[i]].back();
			change(1,1,n,last+1,i-1,a[i],i);
			int st=last;
			while(r[st]<i){
				st=r[st];
				v[a[st]].pop_back();
			}
			r[last]=i;
		}
		v[a[i]].push_back(i);
	}
	final(1,1,n);
	for(int i=1;i<=n;i++) printf("%d\n",now[ans[i]]);
	return 0;
}
```

完结撒花！

---

