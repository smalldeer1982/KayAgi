# [CEOI 1999] Parity Game

## 题目描述

Alice 和 Bob 在玩一个游戏：他写一个由 $0$ 和 $1$ 组成的序列。Alice 选其中的一段（比如第 $3$ 位到第 $5$ 位），问他这段里面有奇数个 $1$ 还是偶数个 $1$。Bob 回答你的问题，然后 Alice 继续问。Alice 要检查 Bob 的答案，指出在 Bob 的第几个回答一定有问题。有问题的意思就是存在一个 $01$ 序列满足这个回答前的所有回答，而且不存在序列满足这个回答前的所有回答及这个回答。

## 说明/提示

对于 $100\%$ 的数据，$1 \le  n \leq 10^9$，$m \leq 5 \times 10^3$。

## 样例 #1

### 输入

```
10
5
1 2 even
3 4 odd
5 6 even
1 6 even
7 10 odd```

### 输出

```
3```

# 题解

## 作者：houzhiyuan (赞：82)

# Parity Game

这题需要用到：种类并查集（也叫扩展域），离散化。

### [不了解并查集的请移步](https://www.luogu.com.cn/problem/P3367)

### 关于本题主要做法

由于数列中只有 $0$ 或 $1$，那么使先开一个 $s$ 数组表示前缀和，那么：

$s[j]-s[i-1]$ 是奇数时，则 $[i..j]$ 区间中的 $1$ 的个数为奇数，反之，为偶数。

区间的关系是已知的，而 $s$ 是未知的，那么就可以用区间的条件来限定前缀和，如果出现奇偶性的矛盾，就可以直接输出。

### 关于种类并查集

扩展域，顾名思义，就是将原来并查集扩大，已达到储存每个元素的多个关系。

如本题就要记录与自己相同的和与自己不同的，就将 $f$ 数组开大到原来的两倍，用 $f[i]$ 表示与自己奇偶性相同的集合，用 $f[i+n]$ 表示与 $i$ 奇偶性不同的元素集合。

代码实现：

合并相同的元素：

```cpp
if(getfather(x)==getfather(y)){//x和y不同，矛盾
	cout<<i-1;
	return 0;
}
else{
	hebing(x,y);
	hebing(x+n,y+n);//与x不同的集合也和y不同
}
```
合并不同的元素：
```cpp
if(getfather(x)==getfather(y)){//x和y相同，矛盾
	cout<<i-1;
	return 0;
}
else{
	hebing(x+n,y);
	hebing(x,y+n);//与x不同的集合和y相同，与y不同的集合和x相同
}
```

### 关于离散化

这是一个比较基础的算法。

当数据范围特别大时且真正用到的数有比较少的时候，就可以用当前元素排序后在数组中的编号来代替原来的元素。

首先需要认识两个 STL 函数（c 党的福利）。

unique：将数组去重，并返回去重后最后一个元素的地址。

lower_bound：对一个有序的序列，二分查找第一个大于等于当前值的元素的地址。

~~当然还要用 sort。~~

具体代码实现：
```cpp
for(int i=1;i<=n;i++){
   cin>>a[i];
   b[i]=a[i];
}
sort(b+1,b+n+1);
l=unique(b+1,b+n+1)-b-1;//l表示去重后剩下的元素个数
for(int i=1;i<=n;i++){
   cout<<lower_bound(b+1,b+l+1,a[i])-b;//查找序号并输出
}
```

## **下面给出AC代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
struct hzy{
	int x,y,z;
}a[200001];
int f[200001],n,m,b[200001],l;
int zuxian(int k){//并查集函数，注意路径压缩
	return f[k]==k?k:f[k]=zuxian(f[k]);
}
void hebing(int x,int y){//合并函数
	int x1=zuxian(x);
	int x2=zuxian(y);
	if(x1!=x2){
		f[x1]=x2;
	}
}
int main() {
	cin>>n>>m;
	string ch;
	for(int i=1; i<=m; i++) {
		cin>>a[i].x>>a[i].y>>ch;
		a[i].x--;//方便后面运算，这里直接减1
		if(ch[0]=='o') {//相同和不同要搞清楚
			a[i].z=1;
		} else {
			a[i].z=0;
		}
		b[++l]=a[i].x;
		b[++l]=a[i].y;
	}
	sort(b+1,b+l+1);
	l=unique(b+1,b+l+1)-b-1;
	for(int i=1;i<=l*2;i++){
		f[i]=i;
	}
	for(int i=1; i<=m; i++) {
		a[i].x=lower_bound(b+1,b+l+1,a[i].x)-b;//离散化
		a[i].y=lower_bound(b+1,b+l+1,a[i].y)-b;
		if(a[i].z==0){//种类并查集，分相同和不同操作
			if(zuxian(a[i].x)==zuxian(a[i].y+l)){//如果两个数奇偶性不同，矛盾，输出
				cout<<i-1;
				return 0;
			}
			else{//不然就合并集合
				hebing(a[i].x,a[i].y);
				hebing(a[i].x+l,a[i].y+l);
			}
		}
		else{
			if(zuxian(a[i].x)==zuxian(a[i].y)){//同理
				cout<<i-1;
				return 0;
			}
			else{
				hebing(a[i].x,a[i].y+l);
				hebing(a[i].x+l,a[i].y);
			}
		}
	}
	cout<<m;
	return 0;
}//完结撒花
```


---

## 作者：Eleven谦 (赞：41)

# P5937 [CEOI1999]Parity Game
[洛谷P5937 P5937 [CEOI1999]Parity Game](https://www.luogu.com.cn/problem/P5937)

------------
#### 前言：

个人感觉这道题初看想不到并查集啊！（~~说实话我题都没读懂，第二遍才读懂~~）

好了，转入正题，这道题我们可以用两种方法A掉：**种类并查集&带权并查集**

------------
#### 题目简述：

给定01序列的长度n，询问和答案的个数m

对于每行的询问和回答先给出两个整数，表示询问区间（闭区间）

再给出一个字符串回答：“odd”表示区间有奇数个1，“even”表示区间有偶数个1

如果存在一个01序列满足第1个到第x个的回答，不满足第x+1个回答，则输出x（如果m个回答都满足，那肯定就输出m）

#### 数据范围：

对于100%的数据，1≤N≤10^9，1≤M≤5×10^3

因为N有点大，所以我们需要使用到**离散化！** 来将大数据映射到小范围的小数据

-----------
#### 引入：

其实本题和[程序自动分析](https://www.luogu.com.cn/problem/P1955)这道题很像：都是给定若干个变量和关系，判断这些关系的**可满足性问题**

不过我们这道题的传递关系不止一种（涉及到了**奇偶性**）：

1. 若x1与x2的奇偶性相同，x2与x3的奇偶性相同，那么x1与x3的奇偶性相同

2. 若x1与x2的奇偶性相同，x2与x3的奇偶性不同，那么x1与x3的奇偶性不同

3. 若x1与x2的奇偶性不同，x2与x3的奇偶性不同，那么x1与x3的奇偶性不同

------------
#### 种类并查集：

（因为我认为这道题种类并查集比较好想也比较好理解，所以先讲种类并查集的做法ovo，下面通过问答的形式给出思路）


- 为什么想到种类并查集？

1. 本题需要记录与自己相同的和不同的，那么我们可以**将相同的理解为“朋友”，将不同的理解为“敌人”**

2. 而题目中的**奇偶性又具有传递性**（见上“引入部分”），所以我们还需要维护这种传递性——于是我们想到了**种类并查集**

- **怎么维护传递性&怎么判断回答是否正确？**

1. 每遇到一个回答，我们先判断当前两个区间端点的奇偶性：

①对于“even”回答，若左端点在右端点“敌人”的集合中或右端点在左端点“敌人”的集合中，则回答错误

②对于“odd”回答，若左端点在右端点“朋友”的集合中或右端点在左端点“朋友”的集合中，则回答错误

2. 如果回答是正确的，那我们就进行合并操作：

①对于“even”，我们将左端点和右端点的“朋友”、“敌人”集合分别合并

②对于“odd”，我们将左端点的“朋友”与右端点的“敌人”合并，将左端点的“敌人”与右端点的“朋友”合并

- 怎么离散化？

可见[浅谈离散化](https://www.cnblogs.com/Eleven-Qian-Shan/p/13157949.html)这篇博客qvq

- 下面给出种类并查集做法的完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,tot,res,b[100010],fa[100010];

struct node {
	int u,v;
	string op;
} a[100010];

inline int find(int x) {
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}

int main() {
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=m;i++) {
		scanf("%d%d",&a[i].u,&a[i].v);
		cin>>a[i].op;
		b[++tot]=a[i].u;
		b[++tot]=a[i].v;
	}
	sort(b+1,b+1+tot);
	res=unique(b+1,b+1+tot)-(b+1);
	for(register int i=1;i<=m;i++) {  //STL实现离散化的三部曲 
		a[i].u=lower_bound(b+1,b+1+res,a[i].u-1)-b;
		a[i].v=lower_bound(b+1,b+1+res,a[i].v)-b;
	} 
	for(register int i=1;i<=2*res;i++) fa[i]=i;
	for(register int i=1;i<=m;i++) {
		if(a[i].op=="even") {  //如果回答是偶数个 
			if(find(a[i].u)==find(a[i].v+res)||find(a[i].u+res)==find(a[i].v)) {  //判断奇偶性 
				printf("%d",i-1);  //注意是i-1而不是i 
				return 0;
			}
			fa[find(a[i].u)]=find(a[i].v);
			fa[find(a[i].u+res)]=find(a[i].v+res);
		}
		else {
			if(find(a[i].u)==find(a[i].v)||find(a[i].u+res)==find(a[i].v+res)) {
				printf("%d",i-1);
				return 0;
			}
			fa[find(a[i].u)]=find(a[i].v+res);
			fa[find(a[i].u+res)]=find(a[i].v);
		}
	}
	printf("%d",m);
	return 0;
} 
```

------------
#### 带权并查集：

- 怎么想到带权并查集？

我们不妨将区间转换为一棵树，然后用0/1来表示**边权**，如下草图：


![带权并查集转换图](https://cdn.luogu.com.cn/upload/image_hosting/smrthqif.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们可以发现，任意区间都可在在树上表示并求得区间的奇偶性（0/1连成字符串就好）


- **怎么转换为维护带权并查集？**

1. 我们将输入中的回答转换为0或1存储：“even”标记为0，“odd”标记为1

2. 我们**用dis[x]来记录x与fa[x]的奇偶性关系**：为0就相同，反之不同

3. 在路径压缩时，对x到根节点路径上的所有**边权做异或（xor）运算**，就可以得到x与root的奇偶性关系（都是0/1，所以想到异或）

如上图：dis[x]=1 xor 0 xor 1=0，dis[y]=0 xor 1 xor 1=0

4. 对于每个问题，先检查左右端点是否在同一个集合内（奇偶性是否已知）：

①在的话就计算**dis[l] xor dis[r]**（即两端点的奇偶性关系），若与回答相矛盾（dis[l] xor dis[r]≠ans），那么回答错误

②不在的话就进行合并操作。此时设两个集合的树根为xl、xr，令xl作为xr的孩子，那就要求出**dis[xl]=dis[l] xor dis[r] xor ans**

- 下面给出带权并查集做法的完整代码：



```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int n,m,tot,res;
int b[100010],fa[100010],dis[100010];

struct node {
	int u,v,op;
} a[100010];

inline int find(int x) {
	if(fa[x]==x) return x;
	int root=find(fa[x]);
	dis[x]^=dis[fa[x]];  //路径压缩求出x与树根的奇偶性关系 
	return fa[x]=root;
}

int main() {
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=m;i++) {
		scanf("%d%d",&a[i].u,&a[i].v);
		cin>>s;
		if(s=="even") a[i].op=0;  //转换回答 
		else a[i].op=1;
		b[++tot]=a[i].u;
		b[++tot]=a[i].v;
	}
	sort(b+1,b+1+tot);
	res=unique(b+1,b+1+tot)-(b+1);
	for(register int i=1;i<=2*res;i++) fa[i]=i;
	for(register int i=1;i<=m;i++) {
		int x=lower_bound(b+1,b+1+res,a[i].u-1)-b;  //直接判断一个取一个，就不用单独处理 
		int y=lower_bound(b+1,b+1+res,a[i].v)-b;
		int xx=find(x),yy=find(y);
		if(xx==yy) {  //在一个集合中 
			if((dis[x]^dis[y])!=a[i].op) {  //判断回答是否正确 
				printf("%d",i-1);
				return 0;
			}
		}
		else {
			fa[xx]=yy;
			dis[xx]=dis[x]^dis[y]^a[i].op;  //求左端点树根成为右端点树根孩子后的边权 
		}
	}
	printf("%d",m);
	return 0;
}
```


------------
然后，感谢一下[我的同桌](https://www.cnblogs.com/Poetic-Rain/p/13159504.html) 给我的指导（再~~无耻~~宣传一下[我的博客](https://www.cnblogs.com/Eleven-Qian-Shan/)）

最后，有什么问题欢迎各位dalao们指出来qwq

------------



---

## 作者：mot1ve (赞：18)

此题思维难度还是不小的，但如果你做过程序自动分析那道题你就会发现这俩很像。

首先，怎么想到用并查集？我们可以发现，这道题是有约束条件和传递关系的，和程序

自动分析的那道题的条件也很像，所以很自然想到使用并查集。

显然，这个题要使用**扩展域的并查集**，因为这个题的传递关系不像程序自动分析

那道题一样简单，不了解什么是扩展域的并查集的同学先移步食物链那道题。

下面分析一下这道题的传递和约束条件。（我们用 $sum$ 数组表示序列的前缀和）

$1.$ 如果 $[l,r]$ 有偶数个 $1$ ，那么 $sum[l-1]$ 和 $sum[r]$ 奇偶性相同

$2.$ 如果 $[l,r]$ 有奇数个 $1$ ，那么 $sum[l-1]$ 和 $sum[r]$ 奇偶性相反

这个非常好证明，我不再赘述。

我们这里的 $sum$ 数组其实并没有在程序中体现出来。这里一定要好好理解一下。

我们用两个端点+并查集维护这种关系而不是真的把他表示出来，因为我们不需要调用

这个 $sum$ 数组，我们只需要用这个约束条件来判断是否合法。

扩展域并查集大体思路就是把并查集空间开大n倍，表示n个关系，这里只需要表示正

面和反面的关系来判断是否合法， $a[i]$ 表示正面， $a[i+n]$ 表示反面，所以

只用开大两倍。食物链那道题需要表示天敌，自身，猎物三个关系，所以要开三倍。

如果 $[l,r]$ 中有奇数个 $1$ 

那么合并 $(a[i+n].x,a[i].y)$ ，合并 $(a[i].x,a[i+n].y)$

如果 $[l,r]$ 中有偶数个 $1$ 

那么合并 $(a[i].x,a[i].y)$ ，合并 $(a[i+n].x,a[i+n].y)$

此题N很大，M比N小很多，所以数组空间不可能全部用到，我们还要离散化一下。

离散化的操作这里也不赘述了。

自认为码风还可以QwQ
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int fa[100010],b[100010];
struct node{
	int x,y;
	string op;
}a[100010];
int find(int x)
{
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
void unionn(int x,int y)
{
	fa[find(x)]=find(y);
}
int tot,n,m;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		cin>>a[i].op;
		a[i].x--;
		b[++tot]=a[i].x;
		b[++tot]=a[i].y;
	}
	sort(b+1,b+1+tot);
	int cnt=unique(b+1,b+1+tot)-b-1;
	for(int i=1;i<=cnt*2;i++)
	{
		fa[i]=i;
	}
	for(int i=1;i<=m;i++)
	{
		a[i].x=lower_bound(b+1,b+1+cnt,a[i].x)-b;
		a[i].y=lower_bound(b+1,b+1+cnt,a[i].y)-b;
	}
	for(int i=1;i<=m;i++)//离散化完了，开始正常操作
	{
		if(a[i].op=="even")
		{
			if(find(a[i].x)==find(find(a[i].y+cnt)))
			{
				printf("%d",i-1);
				return 0;
			}
			else
			{
				unionn(a[i].x,a[i].y);
				unionn(a[i].x+cnt,a[i].y+cnt);
			}
		}
		else
		{
			if(find(a[i].x)==find(a[i].y))
			{
				printf("%d",i-1);
				return 0;
			}
			else
			{
				unionn(a[i].x,a[i].y+cnt);
				unionn(a[i].x+cnt,a[i].y);
			}
		}
	}
	cout<<m;
	return 0;
}

---

## 作者：NuoCarter (赞：12)

## 解法：扩展域+离散化

首先观察到：这个01序列的长度 n 为$10^9$

一个并查集的 fa 数组加上扩展域应该要开2倍空间，$10^9$肯定是开不下的

而 m 的范围仅仅为$5*10^3$

所以优先考虑对询问的 开始位置与结束位置 进行离散化

### 可以对题目条件进行一定的转化：

区间$[i,j]$中有多少个1

因为这是一个01序列

所以上面的问题等价于：

求出$sum_i-sum_{j-1}$（sum表示前缀和）

那么题目中给出的奇偶性也就等价于：

如果 区间$[i,j]$为 $odd$

可以转化为

$sum_i$与$sum_{j-1}$奇偶性不同

如果 区间$[i,j]$为 $even$ 

则

$sum_i$与$sum_{j-1}$奇偶性相同

### 上述转化就很明显得暗示了这是一个关于扩展域的并查集算法

代码1也很容易

#### code:


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
unordered_map<int,int> ha;
int fa[40005];
int tot;
int op[10005];
inline int get(int x){return fa[x]==x ? x : fa[x]=get(fa[x]);}
inline void merge(int x,int y){fa[get(x)]=get(y);return;}
int query1[10005];
int query2[10005];
int a[10005];
int b[10005];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		
		scanf("%d%d",&query1[i],&query2[i]);
		char t[10];
		scanf("%s",t);
		query1[i]-=1;
		if(t[0]=='e'){op[i]=2;}
		else{op[i]=1;}
		if(ha.count(query1[i])==0)	ha[query1[i]]=++tot;
		if(ha.count(query2[i])==0)	ha[query2[i]]=++tot;
		a[i]=ha[query1[i]];
		b[i]=ha[query2[i]];
	}		
	for(int i=1;i<=2*tot;++i){
		fa[i]=i;
	}
	for(int i=1;i<=m;++i){
		int x=a[i];
		int y=b[i];
		if(op[i]==2){
			if(get(x+tot)==get(y)||get(x)==get(y+tot)){
				printf("%d\n",i-1);
				return 0;
			}
			else{merge(x,y);merge(x+tot,y+tot);}
		}
		else{
			if(get(x)==get(y)||get(x+tot)==get(y+tot)){
				printf("%d\n",i-1);
				return 0;
			}
			merge(x+tot,y);
			merge(y+tot,x);
		}
	}
	printf("%d\n",m);
	return 0;
}
```



---

## 作者：bellmanford (赞：10)

小蒟蒻还是太菜了，并不会扩展域并查集/带权并查集，所以在这里提供一种思路简单粗暴但是效率更差的做法。

先考虑二分答案，这样问题就转换成对一串的答案进行判断正误了。

然后将这些答案按左端点从小到大排好序，如果左端点相同就按右端点从小到大排好序，依次枚举每一个答案 $i$，在过程中维护之前的一个左端点最大同时右端点尽量小的答案 $x$ ，那么有：

- 如果 $l_x<l_i$ ，往下枚举，因为在 $i$ 之前没有答案和 $i$ 有相同的左端点，那么无论在 $l_i$ 之后的区间的奇偶性如何，在 $l_i$ 之前都有一个长度至少为一的区间可以随意变换奇偶性，那么之前的答案一定会满足。

- 如果 $l_x=l_i$ 且 $r_x<r_i$ ，那么就可以衍生出一个新的答案需要判定，左端点为 $r_x+1$ ，右端点为 $r_i$ ，奇偶性为两者相减。

- 如果 $l_x=l_i$ 且 $r_x=r_i$ ，直接判断奇偶性是否相同，相同就继续。

对于这些操作，我是直接用优先队列来维护，但是可以被卡到 $\mathcal{O(n^2\log^2 n)}$ ，实际上跑不满。

有一些优化，对于左端点相同的答案，直接按上面操作会做平方的操作次数，但是可以发现每次操作完其实新衍生出的答案的左端点还是一样的，所以可以按右端点排序后相邻之间做差来衍生新的答案，那么操作就是线性的了，如果一开始用离散化端点还可以省去一个 $\log$ 。

下面是 $\mathcal{O(n^2\log^2 n)}$ 的垃圾做法，要开 ```O2``` 才能过。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int M=1e4+5;

int read(){
	int x=0,y=1;char ch=getchar();
	while(ch<'0'||ch>'9') y=(ch=='-')?-1:1,ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*y;
}

struct Reply{
	int l,r,jio;
	bool friend operator <(Reply x,Reply y){
		return x.l!=y.l?x.l>y.l:x.r>y.r;
	}
}re[M];
priority_queue<Reply> Q;

bool check(int x){
	while(!Q.empty()) Q.pop();
	for(int i=1;i<=x;i++) Q.push(re[i]);
	int nL=0,nR=0,njio=0;
	while(!Q.empty()){
		Reply u=Q.top();Q.pop();
		if(nL<u.l) nL=u.l,nR=u.r,njio=u.jio;
		else if(nR<u.r) Q.push((Reply){nR+1,u.r,(njio-u.jio+2)%2});
		else if(nR==u.r&&njio!=u.jio) return 0;
	}
	return 1;
}

void solve(){
	int n=read(),m=read();
	for(int i=1;i<=m;i++){
		int l=read(),r=read();
		char JoJo[15];scanf("%s",JoJo);
		re[i]=(Reply){l,r,(JoJo[0]=='o')};
	}
	int l=1,r=m,Ans=m;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1,Ans=mid;
		else r=mid-1;
	}
	printf("%d\n",Ans);
}

signed main(){
	solve();
}
```


---

## 作者：liangbowen (赞：7)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/P5937)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17254846.html)

提供一种不用并查集的，非常好想的做法。

## 思路

题目就是说给定一堆 $\sum\limits_{i=l}^r a_i \equiv w\pmod{2}$，判断哪个等式不合法。

这个形式明显可以前缀和优化：$s_r - s_{l-1} \equiv w \pmod{2}$，其中 $s_x = \sum\limits_{i=1}^x a_i$。

发现这玩意类似差分约束。于是考虑建图。

对于上面的形式，连边 $(l-1) \xrightarrow{ \ w\ } r$。

很自然地想到，如果当前查询的两个点 $(l - 1, r)$ 已经连通，他们可以直接计算出答案 $ans$：走正向边 $ans + w$，走反向边 $ans - w$。

进一步地， 由于 $ans$ 与 $w$ 都是 $0$ 或 $1$，不用考虑加减。**直接连双向边**，答案就是**两点的距离**。

最后就是如何计算两点的距离了：

1. 可以直接 01bfs。
2. 这个图在 $(u, v)$ 已经连通时不会再连边，说明它是一棵树。直接 dfs 即可。

记得离散化。时间复杂度 $O(m^2)$，由于不可能建满边，所以跑得比预期快很多。

## 另外的

由于是一个树，应该可以倍增 lca 来实现 $O(\log m)$ 加边与查询。

面前的大佬可以尝试写一下。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <algorithm>
using namespace std;
const int N = 10005;
struct Edge {int now, nxt, w;} e[N << 1];
int head[N], cur;
void add(int u, int v, int w)
{
	e[++cur].now = v, e[cur].nxt = head[u], e[cur].w = w;
	head[u] = cur;
}
struct Input {int l, r; string op;} input[N];
int tt[N << 1], tot;
int read()
{
	int x;
	cin >> x;
	tt[++tot] = x;
	return x;
}
int fin(int x) {return lower_bound(tt + 1, tt + tot + 1, x) - tt;}

bool vis[N];
int dis[N], emm[N];
void dfs(int u, int fa, int tag)
{
	emm[u] = tag;
	for (int i = head[u]; i; i = e[i].nxt)
	{
		int v = e[i].now;
		if (v == fa) continue;
		dis[v] = (dis[u] + e[i].w) % 2, dfs(v, u, tag);
	}
}
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) input[i].l = read(), input[i].r = read(), cin >> input[i].op;
	sort(tt + 1, tt + tot + 1), tot = unique(tt + 1, tt + tot + 1) - tt - 1;
	for (int i = 1; i <= m; i++) input[i].l = fin(input[i].l - 1), input[i].r = fin(input[i].r);
	
	for (int i = 1; i <= m; i++)
	{
		int u = input[i].l, v = input[i].r, w = (input[i].op == "even" ? 0 : 1);
		dis[u] = 0, dfs(u, 0, i);
		if (emm[v] == i) //联通 
		{
			if (dis[v] != w) return cout << i - 1, 0;
		}
		else add(u, v, w), add(v, u, w), vis[u] = true, vis[v] = true;
	}
	cout << m;
	return 0;
}
```

希望能帮助到大家！

---

## 作者：xhQYm (赞：6)

- 题目链接：[P5937 [CEOI1999]Parity Game](https://www.luogu.com.cn/problem/P5937)

~~刚刚学完离散化过来切题~~

这题我觉得出的非常好，考察了离散化（虽然`map`也可以水过），扩展域并查集的运用。

这题几乎很快就可以看出来要用到并查集，因为具有并查集的传递性。

并查集模板：

查找祖先：

```cpp
const int N=200010;
int p[N];
int find(int x){return p[x]==x?p[x]:find(p[x]);}
```

合并：

```cpp
const int N=200010;
int p[N];
void merge(int a,int b)
{
    a=find(a),b=find(b);
    if(a!=b) p[a]=b;
}
```
扩展域并查集实际上就是将一个点拆成两个点，分别是 $p_i$ 和 $p_{2\times i}$ 储存不同的信息。

那离散化是什么呢？

简单来说，就是把一个很大的数映射到一个很小的数。

模板题：[区间和](https://www.luogu.com.cn/problem/U116072)

至于映射的函数，当然可以用STL的二分函数`lower_bound`，我再这里提供一个模板：

```cpp
int check(int x,int alls[],int lenth)
{
    int l=1,r=lenth,mid;
    while(l<r)
    {
        mid=(l+r+1)>>1;
        if(alls[mid]<=x) l=mid;
        else r=mid-1;
    }
    return l;
}
```

（如果上面的不会，请百度搜索文章解释，建议OI-Wiki）

了解上面那些，那么这题就很简单了。

很容易得到以下结论：

- 如果区间 $l\rightarrow r$ 为奇数 ，区间 $l\rightarrow r$ 上的和为奇数。

- 如果区间 $l\rightarrow r$ 为偶数，区间 $l\rightarrow r$ 上的和为偶数。

对于上面两个情况，分别进行合并即可。



代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200010;
struct node
{
    int x,y,opt;
}a[N];
int n,m;
int p[N],h[N],cnt;
char op[10];
int find(int x){return p[x]==x?p[x]:find(p[x]);}
void merge(int a,int b)
{
    a=find(a),b=find(b);
    if(a!=b) p[a]=b;
}
int check(int x,int alls[],int lenth)
{
    int l=1,r=lenth,mid;
    while(l<r)
    {
        mid=(l+r+1)>>1;
        if(alls[mid]<=x) l=mid;
        else r=mid-1;
    }
    return l;
}
int main()
{
    scanf("%d%d",&n,&m);
    int l,r;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%s",&l,&r,op);
        a[i].x=l-1,a[i].y=r;
        if(*op=='o') a[i].opt=1;
        else a[i].opt=0;
        ++cnt,h[cnt]=a[i].x,++cnt,h[cnt]=a[i].y;
    }
    sort(h+1,h+cnt+1);
    cnt=unique(h+1,h+cnt+1)-h-1;
    for(int i=1;i<=cnt*2;i++) p[i]=i;
    for(int i=1;i<=m;i++)
    {
        a[i].x=check(a[i].x,h,cnt);
        a[i].y=check(a[i].y,h,cnt);
        if((!a[i].opt && find(a[i].x)==find(a[i].y+cnt)) || (a[i].opt && find(a[i].x)==find(a[i].y)))
        {
            printf("%d",i-1);
            return 0;
        }
        if(!a[i].opt)
            merge(a[i].x,a[i].y),merge(a[i].x+cnt,a[i].y+cnt);
        else
            merge(a[i].x,a[i].y+cnt),merge(a[i].x+cnt,a[i].y);
    }
    printf("%d",m);
    return 0;
}


```

如果有问题或者文章错误欢迎提出。




---

## 作者：wmy_goes_to_thu (赞：5)

这道题直接用一个并查集就可以了。

每次查询一个区间 $[l,r]$，可以把它转换成 $[1,r]-[1,l-1]$，所以把 $r$ 和 $l-1$ 合并就可以了。这里因为数据范围太大，所以我用 $map$ 实现。

代码：
```cpp
#include<iostream>
#include<cstring>
#include<map>
#include<cstdio>
using namespace std;
map<int,int>fa;
map<int,int>cnt;
int findfather(int v)
{
	if(fa[v]==0||fa[v]==v)return fa[v]=v;
	int pp=findfather(fa[v]);
	cnt[v]=cnt[v]+cnt[fa[v]];
	cnt[v]&=1;
	fa[v]=pp;
	return pp;
}
int main()
{
	int x,n;
	cin>>x>>n;
	for(int i=1;i<=n;i++)
	{
		int p,q;
		char r[15]={0};
		scanf("%d%d%s",&p,&q,r);
		q++;
		int flg=1;
		if(r[0]=='e')flg=0;
		int p1=findfather(p),q1=findfather(q);
		if(p1==q1)
		{
			if(cnt[p]!=((cnt[q]+flg)&1))printf("%d\n",i-1);
			else continue;
			return 0;
		}else
		{
			cnt[q1]=(cnt[q]!=flg);
			fa[q1]=p;
		}
	}
	printf("%d\n",n);
	return 0;
}
```


---

## 作者：_RainCappuccino_ (赞：2)

> $\texttt{TAG}$：并查集


一种不用种类 / 扩展域并查集的做法。~~因为我不会~~

首先，给定一个区间的奇偶性，那么相当于给定前缀和数组 $sum_{l - 1},sum_r$ 的奇偶性关系。如果该区间和为偶数，那么 $sum_l\equiv sum_r \pmod{2} $。如果该区间和为奇数，那么 $sum_l \equiv sum_r + 1 \pmod{2} $。如果不合法了，那么一定是奇偶性关系矛盾了，可以想到用并查集去维护。

但是呢，并查集只能维护相等的联通块，对于不等的情况如何处理？

我们发现，如果 $sum_i$ 与 $sum_0$ 没有给定奇偶性关系，那么其奇偶性是**未知**的，那么对于不等情况，除非 $sum_{l - 1}, sum_r$ 奇偶性确认相等，那么一定可以构造出奇偶关系。但是，如果在之后的询问中确定了 $sum_{l - 1}$ 或 $sum_{r}$ 的奇偶关系，那么此时还需要重新判断两个点的奇偶关系是否不等。

为了处理这个问题，我们不妨对于有不等关系的联通块之间连边，如果某个点的奇偶性确定了，那么就可以通过这些边进行遍历，把所有与其确认关系的点的奇偶性确定。每次合并把确认的奇偶性下放。

那么如果对于查询的两个点，两个点的奇偶性与给定奇偶性矛盾，那么就得到答案了。

注意对于相等关系，合并时要把边集也合并了。

每次下放时间复杂度 $O(m)$，合并时间复杂度 $O(m)$，总时间复杂度 $O(m ^ 2)$，有一定常数，注意需要离散化。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
const int N = 1e4 + 10;
typedef long long ll;
typedef pair<int, int> pi;
int n, m;
int f[N], col[N];
int find (int x) {
	if (f[x] == x) return x;
	return f[x] = find(f[x]);
}
vector<int> lsh;
int ql[N], qr[N], typ[N];
vector<int> g[N];
void updata (int x, int from) {
	for (auto v : g[x]) {
		v = find(v);
		if (v == from) continue;
		if (col[v] == (col[x] ^ 1)) continue; // 这样快一点
		col[v] = col[x] ^ 1;
		updata(v, x);
	}
}
void merge (int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx == fy) return;
	for (auto v : g[fx]) { // 实际上可以启发式合并优化一下
		g[fy].push_back(v);
	}
	g[fx].clear();
	sort(g[fy].begin(), g[fy].end());
	g[fy].erase(unique(g[fy].begin(), g[fy].end()), g[fy].end());
	if (col[fx] != -1) col[fy] = col[fx];
	f[fx] = fy;
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	f[0] = 0, col[0] = 0;
	lsh.push_back(0);
	for (int i = 1; i <= m; i ++) {
		int l, r;
		string t;
		cin >> l >> r >> t;
		lsh.push_back(l - 1), lsh.push_back(r);
		ql[i] = l, qr[i] = r, typ[i] = (t == "even" ? 0 : 1);
	}
	sort (lsh.begin(), lsh.end());
	lsh.erase(unique(lsh.begin(), lsh.end()), lsh.end());
	for (int i = 1; i <= m; i ++) ql[i] = lower_bound(lsh.begin(), lsh.end(), ql[i] - 1) - lsh.begin(), qr[i] = lower_bound(lsh.begin(), lsh.end(), qr[i]) - lsh.begin();
	for (int i = 0; i < lsh.size(); i ++) f[i] = i, col[i] = -1;
	col[0] = 0;
	for (int i = 1; i <= m; i ++) {
		int l = find(ql[i]), r = find(qr[i]);
		if (typ[i]) {
			if (col[l] != -1) updata(l, -1);
			if (col[r] != -1) updata(r, -1);
			if (l == r || (col[l] != -1 && col[r] != -1 && col[l] == col[r])) {
				cout << i - 1;
				return 0;
			}
			g[l].push_back(r), g[r].push_back(l);
		} else {
			if (col[l] != -1) updata(l, -1);
			if (col[r] != -1) updata(r, -1);
			if (col[l] != -1 && col[r] != -1 && col[l] != col[r]) {
				cout << i - 1;
				return 0;
			}
			merge(l, r);
		}
	}
	cout << m << endl;
	return 0;
}
```

---

## 作者：Develop (赞：2)

我们可以将题目中的条件$(i,j)$转化为$(1,i)$和$(1,j)$的区间奇偶性的异同；这样有利于我们使用并查集优美的传递性；其实就是对于每一个区间$(1,i)$开两种集合：奇偶性相同的虚拟的一个same，不同的虚拟的一个diff；然后扩展域合并就可以啦。

~~扩展域写错了好几遍，加$m$也是可以的，加$n$就不行了~~

这一些想法是从以下地方看到的：
//转载自$wanghandou$ blog CSDN

由于题设中说明这个长字串上每一位不是$0$就是$1$，所以就十分容易得到以下结论：

                    ->1.当区间（i，j）为even时，区间（i，j）上的和为偶数。
                    ->2.当区间（i，j）为odd 时，区间（i，j）上的和为奇数。

从而可以定义以下状态$sum(1,i)$，顾名思义就是前$i$位的和，而且显然有$sum(1,i-1)+sum(i,j)=sum(1,j)$。
那么对于情况$1$，$sum(i,j)$为偶，则$sum(1,i-1)$与$sum(1,j)$相同性质，同偶或同奇。
那么对于情况$2$，$sum(i,j)$为奇，则$sum(1,i-1)$与$sum(1,j)$相反性质，一奇一偶。

所以就可以这样想，对于第i位，有两个集合：与$sum(1,i-1)$相同奇偶性的$SAME$集合，以及与$sum(1,i-1)$相反奇偶性的$DIFF$集合。
每次输入提示语句，根据$sum(i,j)$的奇偶性进行集合的合并：

                    ->1.当区间（i，j）为even时，合并SAME[i-1]与SAME[j]，合并DIFF[i-1]与DIFF[j]。
                    ->2.当区间（i，j）为odd时，合并SAME[i-1]与DIFF[j]，合并DIFF[i-1]与SAME[j]。
                    
可以把$SAME$与$DIFF$放在同一数组$PAR$里，分成前半部分和后半部分即可，注意数组大小，开小会RE。

而产生矛盾的方法也很容易想到：每次合并完成后查询$SAME[ i - 1 ]$与$DIFF[ i - 1 ]$是否同根即可，如果同根就说明矛盾了。

```cpp
#include <cstdio>
#include <algorithm>
#define Freopen(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
#define ll long long
#define M m*2
using namespace std;
void solve();
int n,m,fa[20010];
int lxh[20010],cnt=0;
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
struct node {int f,t;char s[6];}seg[10005];
int main()
{
	//Freopen()
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%s",&seg[i].f,&seg[i].t,seg[i].s);
		seg[i].f--;
		lxh[++cnt]=seg[i].f;
		lxh[++cnt]=seg[i].t;
	}
	sort(lxh+1,lxh+cnt+1);
	cnt=unique(lxh+1,lxh+cnt+1)-lxh-1;
	//printf("[[]]%d]]",cnt);
	for(int i=1;i<=cnt+M;i++)fa[i]=i;
	solve();
	return 0;
}
void solve()
{
	for(int i=1;i<=m;i++)
	{
		int f=lower_bound(lxh+1,lxh+cnt+1,seg[i].f)-lxh;
		int t=lower_bound(lxh+1,lxh+cnt+1,seg[i].t)-lxh;
	//	printf("[%d %d]\n",f,t);
		if(seg[i].s[0]=='o')//odd
			fa[find(f+M)]=find(t),
			fa[find(f)]=find(t+M);
		//	printf("union %d-%d %d-%d",f+M,t,f,t+M);
		else if(seg[i].s[0]=='e')//even
			fa[find(f)]=find(t),
			fa[find(f+M)]=find(t+M);
		//	printf("union %d-%d %d-%d",f,t,f+M,t+M);
		if(find(f)==find(f+M))
		{
			printf("%d\n",i-1);
			return;
		}
	}
	printf("%d\n",m);
	return;
}
```


---

## 作者：LB_tq (赞：2)

# Solution
看到题解区都使用了扩展域并查集，我来提供一个**边带权并查集**的做法。

- 若区间 $[l,r]$ 中有奇数个 $1$ ，则说明区间 $[1,l]$ 与区间 $[1,r]$ 中 $1$ 的数量的奇偶性不同。

- 若区间 $[l,r]$ 中有偶数个 $1$ ，则说明区间 $[1,l]$ 与区间 $[1,r]$ 中 $1$ 的数量的奇偶性相同。
 
于是可以用 $0$ 表示相同，$1$ 表示不同，利用异或运算维护边权。

设$fa_i$表示 $i$ 的祖先节点，$d_i$表示 $i$ 节点到祖先的边权。

- 若 $x$ 与 $y$ 祖先相同，则判断 $d_x \oplus d_y$ 与给出的答案是否相同。

- 若 $x$ 与 $y$ 祖先不同，则合并二者所在集合，并将 $fa_x$ 到 $fa_y$ 的权值设为 $d_x \oplus d_y \oplus ans_i$。

可以在查找 $fa_i$ 时更新 $d_i$ 。另外注意到 $n$ 较大，而 $m$ 较小，所以对数据进行离散化。
# Code
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn=2e4+10;
int n,m,len,a[maxn],b[maxn],fa[maxn],d[maxn],c[maxn>>1][3];
bool f=false;
int Gtid(int x){
	int l=1,r=len,mid;
	while(l<r){
		mid=(l+r+1)>>1;
		if(b[mid]<=x)
			l=mid;
		else
			r=mid-1;
	}
	return l;
}
int Gtfa(int x){
	if(x==fa[x])
		return x;
	int y=Gtfa(fa[x]);
	d[x]^=d[fa[x]];
	return fa[x]=y;
}
int main(){
	int x,y,fx,fy;
	string s;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>c[i][0]>>c[i][1]>>s;
		if(s=="even")
			c[i][2]=0;
		else
			c[i][2]=1;
		c[i][0]--;
		a[i*2-1]=c[i][0];
		a[i*2]=c[i][1];
	}
	sort(a+1,a+2*m+1);
	for(int i=1;i<=2*m;i++)
		if(i==1||a[i]!=a[i-1])
			b[++len]=a[i];
	for(int i=1;i<=len;i++)
		fa[i]=i;
	for(int i=1;i<=m;i++){
		x=Gtid(c[i][0]);
		y=Gtid(c[i][1]);
		fx=Gtfa(x);
		fy=Gtfa(y);
		if(fx==fy){
			if((d[x]^d[y])!=c[i][2]){
				cout<<i-1;
				f=true;
				break;
			}
		}
		else{
			fa[fx]=fy;
			d[fx]=d[x]^d[y]^c[i][2];
		}
	}
	if(!f)
		cout<<m;
	return 0;
}
```


---

## 作者：rainbow_cat (赞：1)

为什么都用并查集呢，提供一种二分图的写法，定义前缀和数组 $s_1,s_2,\dots,s_n$。   
若 $x$ 到 $y$ 为 `even` 则 $s_y$ 与 $s_{x-1}$ 奇偶相同，否则不同。   
使用二分图的常见技巧，若相同，将两个点连接到一个虚点上，否则直接相连，每连一次边跑一次二分图染色，判断是否可行即可。    
由于值域过大，需要离散化。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,idx,mpidx,col[20010];
bool flag,vis[20010];
string s;
map<int,int>mp;
vector<int>e[20010];
void dfs(int u)
{
	vis[u]=1;
	for(auto i:e[u])
	{
		if(vis[i]&&col[i]==col[u])flag=1;
		else if(!vis[i])col[i]=col[u]^1,vis[i]=1,dfs(i);
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	idx=m;
	for(int i=1;i<=m;i++)
	{
		flag=0;
		cin>>x>>y>>s;
		if(!mp[x-1])mp[x-1]=++mpidx;
		if(!mp[y])mp[y]=++mpidx;
		if(s=="even")
		{			
			e[mp[x-1]].push_back(2*m+(++idx)),e[2*m+idx].push_back(mp[x-1]);
			e[2*m+idx].push_back(mp[y]),e[mp[y]].push_back(2*m+idx);
		}
		else e[mp[x-1]].push_back(mp[y]),e[mp[y]].push_back(mp[x-1]);
		for(int j=1;j<=mpidx;j++)vis[j]=col[j]=0;
		for(int j=2*m+1;j<=2*m+idx;j++)vis[j]=col[j]=0;
		for(int j=1;j<=mpidx;j++)
		{
			if(vis[j])continue;
			dfs(j);
			if(flag)
			{
				cout<<i-1;
				return 0;
			}
		}
		for(int j=2*m+1;j<=2*m+idx;j++)
		{
			if(vis[j])continue;
			dfs(j);
			if(flag)
			{
				cout<<i-1;
				return 0;
			}
		}
	}
	cout<<m;
	return 0;
}
```

---

## 作者：pengyule (赞：1)

###### update: 6.24 有一个地方写反了...已经修正，请管理员通过，谢谢
## 不一样的做法
其实这道题可以不需要结构体的，我们这样想：

- 定义数组 $sum$，$sum_i$ 代表第 $1\!\to\!i$ 个数当中一共有多少个1。
- 如果 $[i,j]$ 是偶数，那么把 $i-1$ 和 $j$（代表 $sum_{i-1},sum_j$ 同为偶数），$i-1+n$ 和 $j+n$（代表 $sum_{i-1},sum_j$ 同为奇数），放到一个集合里。
- 如果 $[i,j]$ 是奇数，那么把 $i-1$ 和 $j+n$（代表 $sum_{i-1}$ 为偶数，$sum_j$ 是奇数），$i-1+n$ 和 $j$（代表 $sum_{i-1}$ 为奇数，$sum_j$ 为偶数），放到一个集合里。
- 放到一个集合里的过程可以用并查集的 $Union()$ 完成，记得初始值 $father_i=i$。
- 以上在同一个并查集中完成不会出现矛盾，我们在判断 Bob 的回答是否成立的时候：
1. 如果是 `i j even`，我们看一下前面是不是出现过他们其实是 `odd` 的情况：判断 $i-1,j+n$、$i-1+n,j$ 是否在一个集合内，两点只要有一点满足可以代表另一点满足，可以用“或”连接。
2. 如果是 `i j odd`，我们看一下前面是不是出现过他们其实是 `even` 的情况：判断 $i-1,j$、$i-1+n,j+n$ 是否在一个集合内，两点只要有一点满足可以代表另一点满足，可以用“或”连接。
- 注意事项：
1. 开 long long，当 $j$ 取最大值 $n$ 时接近 int 边界。
2. 离散化，基础的步骤：首先把所有需要离散化的数据塞在一个 vector 里，然后对这个 vector 排序（好像也可以不用排序？）；用一个 map $D$ 来把原始的数据 $x$ 替换成它在 vector 中的下标，出现过多次的数统一用一个下标代替。最后所有需要用到这些数据的地方我们都用他的下标来代替它的存在，平均意义下每个数都会变小；调用一次 $D_x$ 复杂度是 $\log$ 的，然而 $m\log n$ 并不大，可以接受。
3. 对于 $[i,j]$ 我们刚才说的那个样子，我们明确地知道，$i=1$ 调用时 $sum_{1-1=0}$ 不可能是奇数（数都没有肯定是 $0$ 啦），所以在插入 vector、判断回答的时候都压根不需要管它了。

想必大家都差不多懂了，看代码吧。分析复杂度，应为 $O(m\log n)$。

```
#include <bits/stdc++.h>
using namespace std;
#define pb push_back 
typedef long long ll;
map <ll,ll> D;
vector <ll> v;
ll father[20005],l[10005],r[10005];
string str[10005];
ll Find(ll x){
    if(father[x]==x) return x;
    return father[x]=Find(father[x]);
}
void Unite(ll x,ll y){
    ll X=Find(x),Y=Find(y);
    if(X!=Y) father[X]=Y;
}
int main()
{
    ll n,Q;
    cin>>n>>Q;
    for(ll i=1;i<=Q;i++){
        cin>>l[i]>>r[i];
        if(l[i]!=1) v.pb(l[i]-1+n);
        v.pb(l[i]-1),v.pb(r[i]),v.pb(r[i]+n);
        cin>>str[i];
    }
    sort(v.begin(),v.end());
    for(ll i=0;i<v.size();i++) D[v[i]]=i+1;
    for(ll i=1;i<=(1ll*v.size());i++) father[i]=i;
    for(ll i=1;i<=Q;i++){
        if(str[i]=="even" && (Find(D[l[i]-1])==Find(D[r[i]+n])  || l[i]!=1 && Find(D[l[i]-1+n])==Find(D[r[i]]))) { cout<<i-1<<endl; return 0; }
        if(str[i]=="odd" && (Find(D[l[i]-1])==Find(D[r[i]]) || l[i]!=1 && Find(D[l[i]-1+n])==Find(D[r[i]+n]))) { cout<<i-1<<endl; return 0; }
        if(str[i]=="even"){
            Unite(D[l[i]-1],D[r[i]]);
            if(l[i]!=1) Unite(D[l[i]-1+n],D[r[i]+n]);
        }
        if(str[i]=="odd"){
            if(l[i]!=1) Unite(D[l[i]-1+n],D[r[i]]);
            Unite(D[l[i]-1],D[r[i]+n]);
        }
    }
    cout<<Q<<endl;
    return 0;
}
```

---

## 作者：二gou子 (赞：1)

[例题：P5937 [CEOI1999]Parity Game](https://www.luogu.com.cn/problem/P5937)

这道题既是扩展域的例题也是边带权的例题，是道优秀的练习题。下面通过两种不同的方法给出解决方法。

## 扩展域思路

前缀和的思路真的是非常妙啊

首先对于区间$[l,r]$，将它们的前缀和作为一个元素。那么如果说$[l,r]$有奇数个$1$，那么$sum_{l-1}$和$sum_r$的前缀和奇偶性必定不相等。那么我们可以使用扩展域并查集，将一个前缀和节点拆成两个，一个奇数一个偶数。

对于$odd$，说明奇偶性不相同。先判一下奇偶性是否相同，相同则不符合条件直接输出答案。反之则直接合并奇数和奇数，偶数和偶数。

对于$even$同理，然后只需要再离散化一下，这题就解决了。

## Code
```
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=50005;
int n,m,sum,tot; 
int fa[2*N],li[2*N];
struct Node{
	int x,y,op;
}a[2*N];
int get(int x){
	if(x==fa[x]) return x;
	else return fa[x]=get(fa[x]);
}
void merge(int x,int y){
	fa[get(x)]=get(y);
}
void lisan(){
	sort(li+1,li+1+tot);
	sum=unique(li+1,li+1+tot)-li;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		string s;
		scanf("%d%d",&a[i].x,&a[i].y);
		cin>>s;
		if(s=="odd"){
			a[i].op=1;
		}
		else{
			a[i].op=2;
		}
		li[++tot]=a[i].x;
		li[++tot]=a[i].y;
	}
	lisan();
	for(int i=1;i<=2*sum+2;i++){
		fa[i]=i;
	}
	for(int i=1;i<=m;i++){
		a[i].x=lower_bound(li+1,li+1+sum,a[i].x-1)-li;
		a[i].y=lower_bound(li+1,li+1+sum,a[i].y)-li;
	}
	for(int i=1;i<=m;i++){
		if(a[i].op==1){
			if(get(a[i].x)==get(a[i].y)){
				printf("%d\n",i-1);
				return 0;
			}
			merge(a[i].x,a[i].y+sum+1);
			merge(a[i].x+sum+1,a[i].y);
		}
		else{
			if(get(a[i].x)==get(a[i].y+sum+1)){
				printf("%d\n",i-1);
				return 0;
			}
			merge(a[i].x,a[i].y);
			merge(a[i].x+sum+1,a[i].y+sum+1);
		}
	}
	printf("%d\n",m);
	return 0;
}
```

## 细节

$1.lyd$的黑书代码貌似锅了？初始化$fa$数组的时候只循环到了$2n$，但是实际上在合并的时候，奇数和偶数分别是$x$和$x+n$。如果$x$恰好为$1$，那么$-1$之后$x=0$，$x+n=n$，此时应该表示一个$0$的偶数域。但是同时$n$也表示$n$的奇数域，所以冲突了。在初始化$fa$数组时应该循环到$2n+1$，然后在合并的时候用$x+n+1$来代表偶数域，这样就可以避免冲突。所以如果书中$n$代表离散化后的序列元素个数，的确是有问题的。

$2.$初始化别忘了循环到$2n+1$，而不是$n+1$。

## 边带权思路

注意到奇偶性可以用异或和来表达，那么就可以用边权为$1$的边来表示两个点的奇偶性不同，用$0$来表示奇偶性相同。

下面就是老套路了，先递归更新父节点，然后逐个更新。因为相对关系不变，所以$d_x$$^$$=d_{fa[x]}$。在合并的时候只需要手玩一下跟根节点的关系即可，然后再特判一下是否合法就可以了。

## Code
```
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=50005;
int n,m,sum,tot; 
int fa[2*N],li[2*N],d[2*N];
struct Node{
	int x,y,op;
}a[2*N];
int get(int x){
	if(x==fa[x]) return x;
	int root=get(fa[x]);
	d[x]^=d[fa[x]];
	return fa[x]=root;
}
void merge(int x,int y){
	fa[get(x)]=get(y);
}
void lisan(){
	sort(li+1,li+1+tot);
	sum=unique(li+1,li+1+tot)-li;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		string s;
		scanf("%d%d",&a[i].x,&a[i].y);
		cin>>s;
		if(s=="odd"){
			a[i].op=1;
		}
		else{
			a[i].op=2;
		}
		li[++tot]=a[i].x;
		li[++tot]=a[i].y;
	}
	lisan();
	for(int i=1;i<=sum+2;i++){
		fa[i]=i;
	}
	for(int i=1;i<=m;i++){
		a[i].x=lower_bound(li+1,li+1+sum,a[i].x-1)-li;
		a[i].y=lower_bound(li+1,li+1+sum,a[i].y)-li;
	}
	for(int i=1;i<=m;i++){
		if(a[i].op==1){
			int x=a[i].x,y=a[i].y;
			int p=get(x),q=get(y);
			if(p==q){
				if(d[x]^d[y]!=1){
					printf("%d\n",i-1);
					return 0;
				}
			}
			else{
				if(d[x]!=d[y]){
					d[p]=0;
					fa[p]=q;
				}
				else{
					d[p]=1;
					fa[p]=q;
				}
			}
		}
		else{
			int x=a[i].x,y=a[i].y;
			int p=get(x),q=get(y);
			if(p==q){
				if(d[x]^d[y]!=0){
					printf("%d\n",i-1);
					return 0;
				}
			}
			else{
				if(d[x]!=d[y]){
					d[p]=1;
					fa[p]=q;
				}
				else{
					d[p]=0;
					fa[p]=q;
				}
			}
		}
	}
	printf("%d\n",m);
	return 0;
}
```


---

## 作者：EternalEpic (赞：0)

本题为并查集入门者的必做好题，过者可以再去做一下[P2024 [NOI2001]食物链](https://www.luogu.com.cn/problem/P2024)

分析：

我们在序列S上可以建立前缀和数组pre(MaxS)。

若S(l ~ r)有偶数个1，则pre(l - 1)与pre(r)奇偶性相同；反之则相反。

而这些奇偶性的关系是可传递的，如果发生又同奇偶又异奇偶就能找到矛盾。

所以这道题我用并查集维护，提供两种思路。

idea 1：扩展域并查集

我们可以把每个节点$x$拆成$x_{odd}$和$x_{even}$。

如果pre(x)与pre(y)奇偶性相同就合并$x_{odd}$与$y_{odd}$，$x_{even}$与$y_{even}$

反之则相反。

如果条件要求同奇偶但$x_{odd} = y_{even}$，或要求异奇偶但$x_{odd} = y_{odd}$，就矛盾了，输出前一个条件的编号。

使用按秩合并和路径压缩可以把并查集部分单次操作优化到$O$($\alpha$)，但由于要离散化，所以复杂度还是有1个log，瓶颈在于离散化。


code: [代码太长放不下qwq。](https://www.luogu.com.cn/paste/7ik4ty0q)


idea 2: 边带权并查集

大体思路其实都差不多，这里使用边权异或值来维护奇偶性。

维护d(Maxm)数组，来阐述清楚节点x和getf(x)奇偶关系，间接表现同集合内两点奇偶关系。如果不在同一集合，进行合并，改变并入的那个集合的d(root)即可。

合并函数:

```cpp
inline void unionf(int x, int y, int op) {
	int fx = getf(x), fy = getf(y);
	if (sze[fx] <= sze[fy]) sze[fy] += sze[fx], f[fx] = fy, d[fx] = d[x] ^ d[y] ^ op;
	else sze[fx] += sze[fy], f[fy] = fx, d[fy] = d[x] ^ d[y] ^ op;
}

```

code：

```cpp
const int Maxm = 1e4 + 5;
int n, m, f[Maxm], d[Maxm], sze[Maxm], a[Maxm]; char cmd[15];

inline int getf(int x) {
	if (f[x] == x) return x;
	int root = getf(f[x]);
	d[x] ^= d[f[x]];
	return f[x] = root;
}

inline void unionf(int x, int y, int op) {
	int fx = getf(x), fy = getf(y);
	if (sze[fx] <= sze[fy]) sze[fy] += sze[fx], f[fx] = fy, d[fx] = d[x] ^ d[y] ^ op;
	else sze[fx] += sze[fy], f[fy] = fx, d[fy] = d[x] ^ d[y] ^ op;
}

struct State {
	int l, r, opt;
	State(int _l = 0, int _r = 0, int _op = 0) : l(_l), r(_r), opt(_op) {}
} que[Maxm / 2];

signed main(void) {
//	file("");
	read(n), read(m);
	for (int i = 1, x, y; i <= m; i++) {
		read(x), read(y), readstr(cmd);
		que[i] = State(x, y, cmd[0] == 'o');
		a[i] = x - 1; a[i + m] = y;
	} sort(a + 1, a + (m << 1) + 1);
	n = unique(a + 1, a + (m << 1) + 1) - (a + 1);
	for (int i = 1; i <= n << 1; i++) f[i] = i, sze[i] = 1, d[i] = 0;
	for (int i = 1, x, y; i <= m; i++) {
		x = lower_bound(a + 1, a + n + 1, que[i].l - 1) - a;
		y = lower_bound(a + 1, a + n + 1, que[i].r) - a;
		if (getf(x) == getf(y)) {
			if ((d[x] ^ d[y]) != que[i].opt) { writeln(i - 1); return 0; }
		} else unionf(x, y, que[i].opt);
	} writeln(m);
//	fwrite(pf, 1, o1 - pf, stdout);
	return 0;
}
```


---

## 作者：Natsume_Rin (赞：0)

写一篇并查集的题解。

首先，我们可以考虑 **对于每一次给出** 的区间 $[a,b]$，**把 $b$ 并入到 $a-1$ 所属的集合中**。同时维护 $b$ 到 $a-1$ **集合根节点路径长度的奇偶性**。

在原来的并查集基础上稍作修改（$be_i$ 表示 $i$ 到 $i$ 所处集合根节点路径的奇偶性）：

```cpp
inline int find(int x){
	if(fa[x]==x) return x;
	int fn=find(fa[x]);
	be[x]^=be[fa[x]];//更新be数组
	return fa[x]=fn;//路径压缩
}
inline void merge(int x, int y){
	fa[sev]=seu;
	be[sev]=be[v]^be[u]^re;//更新be数组
}
```

那么，我们怎么确定，对于一个区间 $[l,r]$ 它是否成立呢？？？

**明显，我们只需要知道区间 $[l,r]$ 的奇偶性，就可以了**，而这一个区间的奇偶性就等于 $be_{l-1} \oplus be_r$。

```
tmp=be[l-1]^be[r];
if(tmp!=re) {cout<<i-1;exit(0);}
```

这样子一来，就可以回答询问，判断是否和题目给出的相符。

完整代码：

```cpp
#include<bits/stdc++.h>
#define RI register int
using namespace std;
typedef long long ll;
int n, m, u, v, seu, sev, re;
string s;
map<int,int>be,fa;
map<int,bool>vis;//因为数据范围比较大，所以用map映射
inline int find(int x){
	if(fa[x]==x) return x;
	int fn=find(fa[x]);
	be[x]^=be[fa[x]];
	return fa[x]=fn;
}
inline void und(int x){
	if(vis[x]) return ;
	vis[x]=1;fa[x]=x;
	return ;
}
int main(){
	int tmp;
	cin>>n>>m;
	for(RI i=1;i<=m;++i){
		cin>>u>>v>>s;u--;re=(s=="odd"?1:0);
		und(u), und(v);
		seu=find(u), sev=find(v);
		if(seu!=sev) {
			fa[sev]=seu;
			be[sev]=be[v]^be[u]^re;
		}
		else{
			tmp=be[u]^be[v];
			if(tmp!=re) {cout<<i-1;exit(0);}
		}	
	}
	cout<<m;
	return 0;
}
```

---

