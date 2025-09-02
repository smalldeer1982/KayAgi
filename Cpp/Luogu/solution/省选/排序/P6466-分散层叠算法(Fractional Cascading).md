# 分散层叠算法(Fractional Cascading)

## 题目背景

`Fractional Cascading` 算法，国内多译为“分散层叠”。

本题仅提供一个简单而经典的方式给算法验证正确性，原则上会尽量卡掉比较暴力的做法，但不保证乱搞一定无法通过。

## 题目描述

给出 $k$ 个长度为 $n$ 的**有序数组**。

现在有 $q$ 个查询 : 给出数 $x$，分别求出每个数组中大于等于 $x$ 的最小的数(非严格后继)。

若后继不存在，则定义为 $0$。

每个查询的答案定义为 $k$ 个后继的**异或和**。

你需要**在线地**回答这些询问。

由于输出太多不好，给出参数 $d$，你只需要输出编号为 $d$ 的倍数的询问的答案。询问从 $1$ 开始编号。



## 说明/提示

#### 样例解释

对于样例 1，解密后的数据为:

```cpp
6 3 8 1
1 4 6 7 10 20
2 3 8 11 14 18
5 9 12 13 15 17
20
18
15
13
10
8
5
2
```
---
#### 数据规模的与约定
- 对于 $20\%$ 的数据，$k\leq 10$，$n\leq 1000$，$q\leq 1000$。
- 对于 $50\%$ 的数据，$k\leq 10$，$q\leq 2\times 10^5$。
- 对于 $100\%$ 的数据，$1 \leq k\leq 100$，$2\leq n\leq 10^4$，$q\leq 5\times 10^5$，$1\leq d\leq 10$，解密后输入中出现的数均在 $[1,5\times 10^8)$ 范围内。

## 样例 #1

### 输入

```
6 3 8 1
1 4 6 7 10 20 
2 3 8 11 14 18 
5 9 12 13 15 17 
20
6
9
4
29
5
14
9```

### 输出

```
20
6
9
23
13
11
11
3```

## 样例 #2

### 输入

```
2 4 1 1
64 65
25 26
44 62
35 81
81```

### 输出

```
81```

## 样例 #3

### 输入

```
20 4 10 1
553 897 1333 1949 2261 2541 2901 3133 3209 3713 4373 4749 5761 7405 8733 10417 13013 15185 16825 16981 
246 750 806 1534 2274 2470 2486 3278 3954 4618 5306 5638 6114 6310 7106 7522 7734 8170 8702 8974 
1047 1275 2347 2711 3607 4719 5911 6051 7099 7519 8087 8435 8499 8687 8835 10151 10491 11159 11915 12483 
548 1392 2188 3260 3404 3768 5076 5668 5732 6612 7284 7492 8900 9008 9536 9768 11160 12096 12300 13100 
3133
3331
4139
2685
2229
1163
3228
2694
3913
7058```

### 输出

```
600
8156
676
1176
600
3800
8
432
8156
320```

# 题解

## 作者：FutaRimeWoawaSete (赞：29)

# 前言          

wjc 那天有个分块题被我找到原题然后叉掉了。          

没有做出来，然后去找了个题解。          

翻了翻找到一篇 分散叠层加分块的 $O(n \sqrt {nlog_n})$题解，没想到此题还有~~如此优秀的~~复杂度？这分散叠层又是个什么玩意儿？抱着无聊的本质上网搜了一下发现可以用在一些题里面优化分块，就去学了学。                

# 正文                

# P1 何为“分层”思想         

就是字面意思。       

分散层叠算法的英语为 ```Fractional Cascading```，```Fractional```的意思是零碎的微小的，```Cascade```即小瀑布。其提出者这么命名，也许就是想说小瀑布会汇聚成大瀑布吧（ 。            

用中文来说，~~小黄河汇聚成大黄河~~~，诶这都不重要，感性理解成把我们需要的东西拆成很多层,然后我们相邻的两层之间都有一些联系，可以是我们分散叠层中，利用前一个序列推向后一个序列的nxt指向方法，也可以是我们跳表中通过抽样缩小查询的分层方法……    

# P2 分散叠层到底是个什么东西           

我们先来想一道题：现在有 k 个有序序列，每个序列长为 n ，且保证 $nk \leq 2 \times 10 ^ 6$ ，现在我们有 m 个数，我们对于每一个数，想要知道它在这 $k$ 个序列中的非严格后继。          

首先我们要裸一下，有序，后继，这不直接对每个序列二分一下不就好了，时间复杂度 $O(mklog_n)$ ，你看这 $O(mk)$ 啊，岂是可取之材？扔了扔了。          

接着我们发现这个算法的唯一劣势就是时间复杂度太高了，我们为何不去优化一下呢？我们直接考虑暴力揉团团，把这 k 个序列揉成一个序列，对于大序列的每一个元素我们跟 k 个数字，第 i 个数字表示当我们二分查找大序列时，如果找到了当前这个元素，那么在第 i 个序列二分查找时对应的位置就应该是第 i 个数字，这个可以用 k 个序列进行归并 $O(nk)$ 得到，时间复杂度 $O(log_n + k)$ ，但是空间复杂度 $O(nk ^ 2)$ 真的不敢恭维。           

现在我们有了两个算法，一个时间爆炸一个空间爆炸，如果我们可以融合一下，诶这不就解决了？            

为了更好说明，我们先来举一个例子，假如有 k 个序列，我们先令 ```L[i]``` 为第 i 个序列的原序列， ```M[i]``` 为第 i 个序列的新序列（后面会讲解这个 $M$ 有什么用） 。         

假设 $k = 3$ ，原序列分别为：          

```L[1] = {1 4 6 7 10 20}```        

```L[2] = {2 3 8 11 14 18}```        

```L[3] = {5 9 12 13 15 17}```          

现在，我们 ```M[i]``` 里面的元素都跟了两个数字 ```now[j] , nxt[j]``` ，第一个表示的是如若在 ```M[i]``` 里二分找到了当前的 ```M[i][j]``` ，那么在原 ```L[i]``` 序列里面二分应该找到 ```now[j]``` 这个位置，而在 ```M[i + 1]``` 里二分就应该找到 ```nxt[j]``` 这个位置。            

我们从下往上依次处理每个 ```M[i]``` 序列，具体而言，我们如若得到 ```M[i + 1]``` 现在想要得到 ```M[i]``` ，我们就从 ```M[i + 1]``` 里面每隔一个元素就抽出来一个元素，然后和 ```L[i]``` 进行归并得到：           

```M[1] = {1[1,2],3[2,2],4[2,4],6[3,4],7[4,4],9[5,4],10[5,6],13[6,6],17[6,8],20[6,8]}```

```M[2] = {2[1,2],3[2,2],8[3,2],9[4,2],11[4,4],13[5,4],14[5,6],17[6,6],18[6,6]}```

```M[3] = {5[1,0],9[2,0],12[3,0],13[4,0],15[5,0],17[6,0]}```             

这里的从下往上处理过程也并不困难，我们首先可以得到 ```M[3]``` ，接着我们在归并时一个个往上面放即可，伪代码一下：         

```cpp
pks.clear() ; v[i].push_back(pks);
int siz = v[i + 1].size() - 1 , l = 1 , ll = 1 , cnt = 0;
for(int j = 2 ; j <= siz ; j += 2) 
{
	Used[++ cnt] = v[i + 1][j];
	Used[cnt].now = j; 
}
while(l <= cnt && ll <= n)//这里的x对应的就是now[j],y就是nxt[j]
{
	if(Used[l].val < a[i][ll])
	{
		pks.val = Used[l].val , pks.y = Used[l].now , pks.x = ll;
		v[i].push_back(pks);
		l ++;
	}
	else 
	{
		pks.val = a[i][ll] , pks.y = Used[l].now , pks.x = ll;
		v[i].push_back(pks);
		ll ++;		
   }
}
while(l <= cnt){pks.val = Used[l].val , pks.y = Used[l].now , pks.x = ll; v[i].push_back(pks);l ++;}
while(ll <= n){pks.val = a[i][ll] , pks.y = Used[l - 1].now , pks.x = ll; v[i].push_back(pks);ll ++;}
```

如果我们要查询一个数时，我们只要在 ```M[1]``` 里面做一次二分，然后通过 ```nxt``` 数组找到 ```M[2]``` 里面对应的位置，只不过这时我们需要遍历一下前后看一下当前答案是否合法，接着我们在去 ```M_3……``` 而每个 ```M[i]``` 数组里面找到的元素的第一维就是我们想要的答案，时间复杂度 $O(log_n + k)$ 。     
而空间复杂度呢？我们可以这么证明，由于每次我们都是折半取出，然后空间复杂度就是 $O(1 + \frac{1}{2} + \frac{1}{4} + ……) = O(2n)$ ，空间复杂度也极其优秀。         

证明了这个时空复杂度后，那为什么这个做法是对的呢？         

我们可以很显然地使用数学归纳法证明，```M[k]``` 的答案很显然是对的，那么我们在任意的 ```M[i + 1]``` 是正确的情况下，由于我们是从 ```M[i + 1]``` 里面以 $\frac{1}{2}$ 的比例提取，所以假设 ```M[i + 1]``` 里的两个位置 ```pos , pos + 2``` 所以我们如若在 ```M[i]``` 里面找到一个数，如若它指向 ```pos + 2``` 的话，由于我们把 ```pos``` 插入进去了，所以答案肯定在 ```pos + 1``` 和 ```pos + 2``` 之间，这不就得证了？可以抽象理解成我们一段数的端点插入进去了，就自然而然把区间查找范围缩小到了一个程度，所以我们如果以 $frac{1}{D}$ 的比例提取，那么我们在 ```M[i + 1]``` 里面还需要查询的区件长度就为 ```D``` ，所以说我们分散叠层的单次时间复杂度为 $O(log_n + klog_D)$ ，只不过这个 ```D``` 我们选取时就已经很小了，这个 $log_D$  真的很鸡肋……        

这样，这道题的分散叠层算法就到此结束。        

接下来先附上模板题的代码，如果您仅限于模板题的学习可以到此为止了。         

不过由于网上现在也没有一个成型的分散叠层算法的学习体系，所以这个模板是我自己打的……如果挂掉了评论区喷就好了。         

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
const int Len = 2e4 + 5;
int n,k,q,d,a[105][10005];
struct node
{
	int x,y,val,now;
	inline void clear(){x = 0 , y = 0 , val = 0;}
}pks;
node Used[20005];
vector<node> v[105];
void Init()
{
	pks.clear() ; v[k].push_back(pks);
	for(int j = 1 ; j <= n ; j ++) 
	{
		pks.x = j , pks.y = 0;
		pks.val = a[k][j];
		v[k].push_back(pks);
	}
	for(int i = k - 1 ; i >= 1 ; i --)
	{
		pks.clear() ; v[i].push_back(pks);
		int siz = v[i + 1].size() - 1 , l = 1 , ll = 1 , cnt = 0;
		for(int j = 2 ; j <= siz ; j += 2) 
		{
			Used[++ cnt] = v[i + 1][j];
			Used[cnt].now = j; 
		}
		while(l <= cnt && ll <= n)
		{
			if(Used[l].val < a[i][ll])
			{
				pks.val = Used[l].val , pks.y = Used[l].now , pks.x = ll;
				v[i].push_back(pks);
				l ++;
			}
			else 
			{
				pks.val = a[i][ll] , pks.y = Used[l].now , pks.x = ll;
				v[i].push_back(pks);
				ll ++;
			}
		}
		while(l <= cnt){pks.val = Used[l].val , pks.y = Used[l].now , pks.x = ll; v[i].push_back(pks);l ++;}
		while(ll <= n){pks.val = a[i][ll] , pks.y = Used[l - 1].now , pks.x = ll; v[i].push_back(pks);ll ++;}
	}
} 
int Find(int Ins)
{
	int l = 1 , r = v[1].size() - 1 , pos = 0 , res = 0 , to;
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(v[1][mid].val >= Ins) pos = mid , r = mid - 1;
		else l = mid + 1;
	}
	if(!pos) res ^= 0 , pos = v[1].size() - 1;
	else res ^= a[1][v[1][pos].x];
//	printf("%d\n",a[1][v[1][pos].x]);
	to = v[1][pos].y;
	for(int i = 2 ; i <= k ; i ++)
	{
		int siz = v[i].size() - 1;
		if(to >= 2 && v[i][to - 1].val >= Ins) to --;
		else if(v[i][to].val < Ins && to + 1 <= siz && v[i][to + 1].val >= Ins) to ++;
		else if(to + 1 <= siz && v[i][to + 1].val <= Ins) to ++;
		if(to == siz && v[i][to].val < Ins) 
			res ^= 0 , to = v[i][to].y;
		else res ^= a[i][v[i][to].x] , to = v[i][to].y ;
		
	}
	return res;
} 
int main()
{
	scanf("%d %d %d %d",&n,&k,&q,&d);
	for(int i = 1 ; i <= k ; i ++) 
		for(int j = 1 ; j <= n ; j ++) scanf("%d",&a[i][j]);
	Init();
	int lstans = 0;
	for(int i = 1 ; i <= k ; i ++)
	{
		int siz = v[i].size() - 1;
		for(int j = 1 ; j <= siz ; j ++) printf("%d[%d,%d],",v[i][j].val,v[i][j].x,v[i][j].y);
		puts("");
	}
	for(int i = 1 ; i <= q ; i ++)
	{
		int Ins;scanf("%d",&Ins);
		Ins ^= lstans;
		lstans = Find(Ins);
		if(i % d == 0) printf("%d\n",lstans);
	}
	return 0;
}
```

# P3 分散叠层算法的普遍现象         

这里我们可以把这个题目抽象一下，假如我们有一个 $DAG$ ，这个 $DAG$ 上的每个点都有一个有序序列，且每个点的入度出度在常数 $d$ 之内现在我们想对任意的一个路径查询，我们模板题的一个问题。         

很明显，这里的分散叠层得变一下，我们发现其实大体框架还是没变，变的只是我们的选取比例 $\frac{1}{D}$ ，这里其实就得结合题目了，去尽量均衡时空复杂度即可。         

设路径长为 $len$ 。       

单次时间复杂度 $O(log_n + len  log_D)$  

空间复杂度为 $O(nd)$ 。       

这里可能也不是很严谨，具体的可以再参考一下 20年集训队论文，蒋明润《浅谈利用分散层叠算法对经典分块问题的优化》 。          

# P4 一些个人感想         

分散叠层的实用性其实确实不好，而且有点难码，一般还是很难运用到题目中，不过其思想还是有很多运用在了当今 OI 领域，例如跳表，Range Tree ……           

总的来说，冲这个思想，你说他难又不难，还挺好理解的，还是很有价值的一个算法。         

---

## 作者：AThousandSuns (赞：15)

在我的博客看效果更佳：[点这里](https://www.cnblogs.com/1000Suns/p/14048210.html)

---

本文主要参考 IOI 2020 中国国家候选队论文《浅谈利用分散层叠算法对经典分块问题的优化》。

本文仅描述了该算法的基本思想及实现，更深入的理论及应用请在论文中查阅。（或者哪天我有闲心了来写

本文提供的代码并没有经过精细实现，同时依赖于模板题的一些特殊限制，所以不推荐作为模板使用，也不保证在一般情况下仍然有正确性。

---

分散层叠算法可以解决下述问题：

- 给定 $k$ 个有序序列，长度的和为 $n$。$q$ 次询问，每次给定数 $x$，求出其在每个序列的后继。下文中认为，这个后继是非严格的。

对于 $k=1$ 是一个经典的二分算法，可以做到 $O(n)-O(\log n)$。

这个算法做 $k$ 次即有 $O(n)-O(k\log\frac{n}{k})$ 的复杂度。

另一种常见算法，是将这 $k$ 个序列归并成一个长为 $n$ 的序列，同时对于每个元素记录其后面第一个来自第 $i$ 个序列的数是哪个。那么每次查询都可以在大序列中二分，通过在大序列的后继记录的信息得到在每个序列的后继。

这个算法的复杂度为 $O(nk)-O(k+\log n)$，同时空间复杂度也是 $O(nk)$。

分散层叠算法可以 $O(n)-O(k+\log n)$ 解决这个问题，且空间复杂度是 $O(n)$。

---

我们将一开始给出的第 $i$ 个序列叫做 $L_i$。然后预处理另外 $k$ 个有序序列 $M_i$。

$M_k=L_k$，而对于 $i<k$，$M_i$ 由 $L_i$ 和 $M_{i+1}'$ 归并得到。其中 $M_{i+1}'$ 只包含了 $M_{i+1}$ 下标为偶数的元素。

比如，$L_2=[3,8,11,14,18],M_3=[9,12,13,15,17]$，那么 $M_2=[3,8,11,12,14,15,18]$。其中的 $12$ 和 $15$ 来自 $M_3$。

同时，对于 $M_i$ 中的每一个元素，维护在 $L_i$ 和 $M_{i+1}$ 的后继的下标（如果没有，也记录下来）。这个可以在归并的时候维护。

预处理的时间复杂度，注意到 $L_i$ 会在归并 $M_i$ 时贡献 $1$，归并 $M_{i-1}$ 时贡献 $\frac{1}{2}$，等等。所以每个序列的总贡献系数不超过 $2$，也即时空复杂度均为 $O(n)$。

---

对于一次询问，先二分出 $x$ 在 $M_1$ 中的后继，设为 $y$（如果没有，还要特判）。

注意到 $L_1$ 的元素在 $M_1$ 中均有出现，所以 $y$ 在 $L_1$ 的后继就是 $x$ 在 $L_1$ 的后继。

我们也知道 $y$ 在 $M_2$ 的后继。注意到 $y$ 在 $M_2$ 的后继和 $x$ 在 $M_2$ 的后继下标相差是 $O(1)$ 的。

这是因为 $x$ 在 $M_2$ 的后继，和这个后继的后一个元素，恰好一个在 $M_1$ 中出现，所以 $y$ 肯定不会大于 $x$ 在 $M_2$ 的后继的后一个，$y$ 在 $M_2$ 的后继也不会。

所以如果我们知道 $x$ 在 $M_i$ 的后继，就可以 $O(1)$ 求出 $x$ 在 $M_{i+1}$ 和 $L_i$ 的后继。

此时我们就做到了 $O(n)-O(k+\log n)$ 的复杂度。

---

下面给出洛谷 P6466 的代码实现，时间复杂度为 $O(nk+qk+q\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int maxn=22222,maxk=111,mod=998244353;
#define MP make_pair
#define PB push_back
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline ll read(){
	char ch=getchar();ll x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
struct node{
	int v,nxt1,nxt2;
};
int n,k,q,d,lstans,a[maxk][maxn],tl,len[maxk],hhh[maxn];
node b[maxk][maxn],tmp[maxn];
void build(){
	len[k]=n;
	FOR(i,1,len[k]) b[k][i]=(node){a[k][i],i,0};
	ROF(i,k-1,1){
		tl=0;
		FOR(j,1,len[i+1]) if(j%2==0) tmp[++tl]=b[i+1][j],tmp[tl].nxt2=j;
		int cur=1,cur2=1;
		FOR(j,1,n){
			while(cur<=tl && tmp[cur].v<=a[i][j]){
				tmp[cur].nxt1=j;
				b[i][++len[i]]=tmp[cur];
				cur++;
			}
			while(cur2<=len[i+1] && b[i+1][cur2].v<=a[i][j]) cur2++;
			b[i][++len[i]]=(node){a[i][j],j,cur2};
		}
		while(cur<=tl){
			tmp[cur].nxt1=n+1;
			b[i][++len[i]]=tmp[cur];
			cur++;
		}
	}
	FOR(i,1,len[1]) hhh[i]=b[1][i].v;
/*	FOR(i,1,k){
		FOR(j,1,len[i]) printf("(%d,%d,%d) ",b[i][j].v,b[i][j].nxt1,b[i][j].nxt2);
		puts("");
	}*/
}
int main(){
	n=read();k=read();q=read();d=read();
	FOR(i,1,k) FOR(j,1,n) a[i][j]=read();
	build();
	FOR(_,1,q){
		int x=read()^lstans;
//		printf("work %d\n",x);
		lstans=0;
		int p=lower_bound(hhh+1,hhh+len[1]+1,x)-hhh;
//		printf("first at %d\n",p);
		FOR(i,1,k){
			while(p<=len[i] && b[i][p].v<x) p++;
			while(p>=2 && b[i][p-1].v>=x) p--;
			if(p<=len[i]){
				lstans^=a[i][b[i][p].nxt1];
				p=b[i][p].nxt2;
			}
			else{
				p=len[i+1]+1;
			}
		}
		if(_%d==0) printf("%d\n",lstans);
	}
}
```

---

## 作者：1saunoya (赞：10)

不会这个算法，自己 yy 了一种做法。

考虑简单分块，分成 $n$ 个块，$s_{i,j}$ 表示 $[i, n]$ 这些块的当前答案。

大块可以 $O(1)$ 得出答案，然后每个块大小就是 $k$ 了，暴力即可。

复杂度 $O (n \times k + q \times (k + \log))$。

```cpp
/*
 _      _  _ _ _ _ _   _      _
\_\   /_/ \_\_\_\_\_\ \_\   /_/
 \_\ /_/      \_\      \_\ /_/
  \_\_/       \_\       \_\_/
   \_\         \_\       \_\
   \_\     \_\ \_\       \_\
   \_\      \_\\_\       \_\
*/
//#pragma GCC optimize ("O3")
//#pragma GCC target ("sse4")
#include <bits/stdc++.h>
//#define int ll
using ll = int64_t;
using uint = uint32_t;
using ull = uint64_t;
using str = std::string;
#define fi first
#define se second
using pii = std::pair<int, int>;
using pil = std::pair<int, ll>;
using pli = std::pair<ll, int>;
template<class T> using V = std::vector<T>;
struct _ { _() { std::ios::sync_with_stdio(false), std::cin.tie(nullptr); } };
template<class T> void rd(T &x) { std::cin >> x; }
template<class T> void pt(const T &x, const str &s = "") { std::cout << x << s; }
template<class T, class ...Args> void rd(T &x, Args &...args) { rd(x); rd(args...); }
template<class T> V<T> rdV(int N) { V<T> A(N); for (auto &x: A) { rd(x); } return A; }
#define gV(T, x) rdV<T>(x)
#define V(T, x) V<T>(x)
template<class T> void pt(const V<T> &A) { for (auto x : A) { pt(x, " "); } pt('\n'); }
template<class T> void cmax(T &x, const T &y) { x = (x > y) ? x : y; }
template<class T> void cmin(T &x, const T &y) { x = (x < y) ? x : y; }
template<class T> T maxV(const V<T> &A) { T res = *A.begin(); for (auto x : A) cmax(res, x); return res; }
template<class T> T minV(const V<T> &A) { T res = *A.begin(); for (auto x : A) cmin(res, x); return res; }
#define sz(V) (int)V.size()
#define all(V) V.begin(), V.end()
#define pb emplace_back
#define rp(i, n) for (int i = 0; i < n; i++)
#define pr(i, n) for (int i = n - 1; i >= 0; i--)
#define rep(i, x, y) for (int i = x; i <= y; i++)
#define per(i, x, y) for (int i = x; i >= y; i--)
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
int n, k, q, d;
int belong(int p) { return p / k; }
const int N = 10000;
const int K = 100;
int s[N][K];
struct node { int x, i; } v[N * K], tmp[N * K];
int b[N * K], vl = 0;
int cnt[1 << 15];
int nowans[K];
int main() {
	rd(n, k, q, d);
	rp (i, k) {
		rp (j, n) { int x; rd(x); v[vl++] = (node){x, i}; }
	}
	rp (i, vl) cnt[v[i].x & 32767]++;
	for (int i = 1; i < 32768; i++) cnt[i] += cnt[i - 1];
	pr (i, vl) tmp[--cnt[v[i].x & 32767]] = v[i];
	rp (i, vl) v[i] = tmp[i];
	memset(cnt, 0, 1 << 17);
	rp (i, vl) cnt[v[i].x >> 15]++;
	for (int i = 1; i < 32768; i++) cnt[i] += cnt[i - 1];
	pr (i, vl) tmp[--cnt[v[i].x >> 15]] = v[i];
	rp (i, vl) v[i] = tmp[i];
	rp (i, vl) b[i] = v[i].x;
	pr (i, n) {
		memcpy(s[i], s[i + 1], k << 2);
		int ll = i * k, rr = (i + 1) * k - 1;
		per (j, rr, ll) s[i][v[j].i] = v[j].x;
	}
	int ans = 0;
	rep (i, 1, q) {
		int x;
		rd(x); x ^= ans;
		int p = std::lower_bound(b, b + vl, x) - b;
		int rr = (belong(p) + 1) * k - 1;
		cmin(rr, n * k - 1);
		ans = 0;
		memcpy(nowans, s[belong(p) + 1], k << 2);
		per (j, rr, p) nowans[v[j].i] = v[j].x;
		rp (j, k) ans ^= nowans[j];
		if (i % d == 0) pt(ans, "\n");
	}
	return 0;
}
```

---

## 作者：a326820068122c (赞：8)

提供一个常数小且相当好写的做法，总用时不到 $1s$

~~（这题貌似可以不用分散层叠算法）~~

这里为了方便令 $c=n*k$

这个做法启发于本题另一篇题解：

>我们直接考虑暴力揉团团，把这 $k$ 个序列揉成一个序列，对于大序列的每一个元素我们跟 $k$ 个数字，第 $i$ 个数字表示当我们二分查找序列时，如果找到了当前这个元素，那么在第 $i$ 个序列二分查找时对应的位置就应该是第 $i$ 个数字

于是首先可以按所有数和它们的位置装到结构体里从大到小进行排序 $O(c\log c)$

然后从后往前预处理出以每个位置为的亦或和，由于每次只改变一个位置，且亦或存在逆运算 ( 亦或本身 ) ，这里可以 $O(1)$ 预处理出每一个临界状态的后缀亦或和 $O(c)$

然后对一每个询问，答案就是它非严格后继的 (大于等于它的最小的数)，为了方便可以直接用 `lower_bound()` $O(m \log c)$



总复杂度 $O((c+m)\log c)$

最后放一下代码，超短！

```cpp
#include <bits/stdc++.h>
#define for1(i,n) for(i=1;i<=(n);i++)
using namespace std;
int n,m,q,d,a[105][10005],ans[1000005],c,v,g[1000005];
struct node{
	int x,y,w;
	bool operator<(const node &nd){return w<nd.w;}
}s[1000005];
int main(){
	int i,j,x;
	scanf("%d%d%d%d",&n,&m,&q,&d);
	for1(i,m) for1(j,n) scanf("%d",&a[i][j]),s[++c]={i,j,a[i][j]};
	sort(s+1,s+c+1);
	for1(i,c) g[i]=s[i].w;
	for(i=c;i;i--) ans[i]=ans[i+1]^g[i]^a[s[i].x][s[i].y+1];
	for1(i,q){
		scanf("%d",&x);
		v=ans[lower_bound(g+1,g+c+1,x^v)-g];
		if(!(i%d)) printf("%d\n",v);
	}
	return 0;
}
```

~~本想着乱搞，结果一不小心就跑成了最优解，比正解还快~~

如果你是来学分散层叠的，还是看看别的题解吧

---

## 作者：小柯 (赞：8)

题意：
给定 $k$ 个序列，$q$ 次询问每个序列里 $x$ 的后继。

首先，~~本蒟蒻并没有学过分散层叠算法，于是去百度，又看不懂，再去 OIWiki ，又没有...于是决定自己想该怎么做...（主要是看到这道紫题还没有题解）~~

如果还是把所有序列分开处理的话，是很难突破 $O(klogn)$ 的下界的（二分查找），因为这是强制在线的。

所以考虑将这 $k$ 个序列归并到一起，形成一个序列 $A$。

归并的时候可以采用胜/败者树提高效率，当然也可以全部丢掉一起基数排序一下，所以预处理只需要 $O(nk)$。

考虑询问 $x$ 在每个序列里的后继，很明显，如果只要 $A$ 里面的值是远远不够的，还应该知道每个值原来是属于哪个序列的。所以预处理的时候维护另一个序列 $B$，表示 $A_i$ 是属于第 $B_i$ 个序列的。

继续考虑询问 $x$，首先肯定能在 $A$ 序列中找到一个位置 $pos$，使得 $A_{pos}$ 为 $x$ 的后继（如果有解的话），那么每个序列里 $x$ 的后继在 $A$ 序列里都应该在 $pos$ 后面。

于是考虑从 $pos$ 处逐一往后找，直到找齐 $1$ ~ $k$ 的 $B_i$ ，再将对应的 $A_i$ 异或起来即可。

在数列非常均匀的情况下，大约 $k$ 次就能找齐。但是数列如果不均匀，可能退化成 $nk$ 次，所以考虑优化。

如果要从前往后逐一找 $k$ 个确定的目标，那么可以考虑维护指针，以直接跳到该位置。所以维护 $nxt_{i,j}$ 表示 $i$ 后面第一个 $B_x$ 为 $j$ 的 $x$。那么一旦确定 $pos$，那么只需要访问 $A_{nxt_{pos,1}},A_{nxt_{pos,2}},A_{nxt_{pos,3}}...$ 即可找齐 $k$ 个原序列里的后继。

但是这样做有一个问题，也就是预处理 $nxt_{i.j}$ 空间复杂度和时间复杂度都有可能吃不消，那就放弃这个算法？不，考虑冗余在哪里。

很明显 $nxt_{i,j}$ 与 $nxt_{i+1,j}$ 有很大程度上可能是相同的，也就是说 $nxt$ 中存在大量的重复，那么是否可以减少 $nxt_i$ 存储的 $j$ 呢？答案是肯定的。

定义 $Nxt_i$ 表示 $nxt_{i,i\%k+1}$ ，那么显然，将 $Nxt_{i+k-1}$ ~ $Nxt_i$ 凑起来，就能得到 $nxt_i$。但是有个问题，有可能 $A_i$ ~ $A_{i+k-1}$ 被漏掉了，那么解决方法也很简单，考虑 $A_{Nxt_i}$ ~ $A_{Nxt_{i+k-1}}$ 的时候，同时也考虑 $A_i$ ~ $A_{i+k-1}$ ，总之，先到先得即可。

单次询问的复杂度为 $O(log(nk)+k)$。

所以最终复杂度为 $O(nk+qlog(nk)+qk)$，空间复杂度为 $O(nk)$，~~好像和分散层叠算法的时间复杂度和空间复杂度一样？~~

最后，放一下代码:

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<queue>
#define INF 999999999
using namespace std;
int k,n,q,d;
int lastans,x;
int a[105][20005];
int A[2000005];
int B[2000005];
int nxt[2000005];
//此处nxt[i]的含义为原文的A[Nxt[i]]，主要是为了方便
int num[105];
//预处理nxt时用的临时数组 
int rest[105];
//rest[i]表示每次询问的时候第i个原序列的后继是否已经找到 
struct node{
	int x,y,z;
	node(){}
	node(int _x,int _y,int _z):
		x(_x),y(_y),z(_z){}
}now;
bool operator <(node a,node b){
	return a.x>b.x;
}
priority_queue<node>Q;
int main(){
	scanf("%d%d%d%d",&n,&k,&q,&d);
	for(int i=1;i<=k;a[i][n+1]=INF,i++)for(int j=1;j<=n;j++)scanf("%d",&a[i][j]);
//在a[i][n+1]处放个极大值是为了避免等下归并的时候出现特殊情况
	for(int i=1;i<=k;i++)Q.push(node(a[i][1],i,1));
	
	for(int i=1;i<=n*k;i++){
		now=Q.top();Q.pop();
		
		A[i]=now.x,B[i]=now.y;
		
		Q.push(node(a[now.y][now.z+1],now.y,now.z+1));
	}
//这里的归并懒得用胜者树，直接用堆，但是用基排才是正确的复杂度，不过既然不会TEL，用堆更方便（

	for(int i=n*k;i;i--){                                        //注意倒序枚举i，因为求的是后继 
		num[B[i]]=A[i];
		
		nxt[i]=num[i%k+1];
	}
	for(int i=1;i<=q;i++){
		scanf("%d",&x);x^=lastans;
		
		lastans=0;
		
		for(int j=1;j<=k;j++)rest[j]=0;                          //注意清零 
		
		int pos=lower_bound(A+1,A+n*k+1,x)-A;                    //lower_bound大法好！ 
		
		for(int j=pos;j<pos+k&&j<=n*k;j++){
			if(!rest[B[j]])rest[B[j]]=A[j];                      //考虑A[i]~A[i+k-1] 
			
			if(!rest[j%k+1])rest[j%k+1]=nxt[j];                  //考虑A[Nxt[i]]~A[Nxt[i+k-1]] 
		}
		
		for(int j=1;j<=k;j++)lastans^=rest[j];                   //计算答案 
		
		if(i%d==0)printf("%d\n",lastans);
	}
	return 0;
}
```

立个 flag，一定要学会分散层叠算法（

（我学了半天就学会了划分树/kk）

---

## 作者：Anita_Hailey (赞：4)

# 分散层叠(Fractional Cascading) 算法

## 简介

在计算机科学中，分散层叠是一种在多个按照有序的数列中对于一个数进行加速二分查找的技术。

## 例题

以洛谷例题为例[P6466](https://www.luogu.com.cn/problem/P6466)，题意很清楚，给你 $k$ 个长度为 $n$ 有序的序列，然后每次问 $x$ 在所有序列中的不严格后继的值。

一个显然的方法就是对于每个序列都二分，那么复杂度可以做到 $O(nk)-O(k\log n)$ 显然不够好。

那么我们可以利用分散层叠算法优化这个东西，具体地说，我们定义 $M$

其中 $M_k = L_k$ ,对于 $1\le i < k$,$M_i$ 我们是由 $L_i$ 和 $M_{i+1}$ 中偶数下标的位置归并而来。

我们定义数据类型 $a[b,c]$ 表示这个数是 $a$ ，在这个序列 $M_i$ 中 $L_i$ 的后继的下标为 $b$ ，不存在则记为 $n+1$，在 $M_{i+1}$ 中的后继位置是 $c$ 不存在则记为 $\text{size}(M_{i+1})+1$ 。

比如下边的例子（完全照抄论文）

$$
L_1=24,64,65,80\\
L_2=23,25,26\\
L_3=13,44,62,66\\
L_4=11,35,46,79,81
$$

 那么应该就有
 

$$
M_1=24[0,1],25[1,1],35[1,3],64[1,5],65[2,5],79[3,5],80[3,6],93[4,6]\\
M_2=23[0,1],25[1,1],26[2,1],35[3,1],62[3,3],79[3,5]\\
M_3=13[0,1],35[1,1],44[1,2],62[2,3],66[3,3],79[4,3]\\
M_4=11[0,0],35[1,0],46[2,0],79[3,0],81[4,0]
$$

然后我们可以证明，在第一个 $M_1$ 上二分得到的 $pos$ 的话，他为 $a[b,c]$ 那么在 $M_2$ 上的东西只可能比 $c$ 要来的小。因为 $a$ 已经是 $x$ 的后继，$c$ 所代表的东西是 $x$ 的后继，一定比 $a$ 大，然后同时不可能超过一个位置，因为 $c$ 的前一个也在 $M_1$ 中。

这就证明了位置变换是 $O(1)$ 的。

那么细节参考代码

```cpp
#include <bits/stdc++.h>
const int N = 1e4 + 10, K = 105;
int n, k, q, d, A[K][N], len[K], h[N * 2];
std::tuple<int, int, int> L[K][N * 2], tmp[N];
int main() {
	scanf("%d %d %d %d", &n, &k, &q, &d);
	for (int i = 1; i <= k; ++i) {
		for (int j = 1; j <= n; ++j) {
			scanf("%d", &A[i][j]);
		}
	}
	len[k] = n;
	for (int i = 1; i <= n; ++i) {
		L[k][i] = std::make_tuple(A[k][i], i, 0);
	}
	for (int i = k - 1; i; --i) {
		int tot = 0;
		for (int j = 2; j <= len[i + 1]; j += 2) {
			tmp[++tot] = std::make_tuple(std::get<0>(L[i + 1][j]), std::get<1>(L[i + 1][j]), j);
		}
		int cur1 = 1, cur2 = 1;
		for (int j = 1; j <= n; ++j) {
			while (cur1 <= tot && std::get<0>(tmp[cur1]) <= A[i][j]) {
				L[i][++len[i]] = std::make_tuple(std::get<0>(tmp[cur1]), j, std::get<2>(tmp[cur1]));
				++cur1;
			}
			while (cur2 <= len[i + 1] && std::get<0>(L[i + 1][cur2]) < A[i][j]) {
				++cur2;
			}
			L[i][++len[i]] = std::make_tuple(A[i][j], j, cur2);
		}
		while (cur1 <= tot) {
			L[i][++len[i]] = std::make_tuple(std::get<0>(tmp[cur1]), n + 1, std::get<2>(tmp[cur1]));
			++cur1;
		}
	}
	for (int i = 1; i <= len[1]; ++i) {
		h[i] = std::get<0>(L[1][i]);
	}
	for (int Case = 1, lstans = 0, x; Case <= q; ++Case) {
		scanf("%d", &x);
		x ^= lstans;
		lstans = 0;
		int pos = std::lower_bound(h + 1, h + 1 + len[1], x) - h;
		for (int i = 1; i <= k; ++i) {
			if (pos >= 2 && std::get<0>(L[i][pos - 1]) >= x) {
				--pos;
			}
			if (pos <= len[i]) {
				lstans ^= A[i][std::get<1>(L[i][pos])];
				pos = std::get<2>(L[i][pos]);
			}
			else {
				pos = len[i + 1] + 1;
			}
		}
		if (Case % d == 0) {
			printf("%d\n", lstans);
		}
	}
	return 0;
}
```

---

## 作者：DPair (赞：3)

提供一种十分好写但是常数更大的写法。

喜提暴力以外的最劣解。

## 思路
我们对于所有序列建线段树，然后每一个节点取出所有偶数位上的数，然后对于一个父亲节点我们 **归并排序** 两个子节点 **取出后的序列** 得到一个新序列。

这部分复杂度是序列总长，即 $O(nk)$ 。

对于每一个父亲节点的序列，我们维护这个位置在两个儿子中对应的后继在 **儿子取出后的序列中的下标** ，这显然可以在归并排序时一起处理掉。

之后我们在根节点二分，得到了一个位置，之后我们扫遍整个线段树，显然我们在父亲节点中得到的位置与真实的后继距离不会超过 $1$ ，所以这部分直接暴力即可，故每一个节点 $O(1)$ ，单次询问应该能达到 $O(k+\log n)$ 。

其实已经做完了，但是常数很大，直接最劣解。

## 代码实现
```cpp
//繁星流动的痕迹纺织出所有的心愿，与希望一起充满这个世界吧！
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define rep(i,s,t) for(int i=(s);i<=(t);++i)
#define per(i,t,s) for(int i=(t);i>=(s);--i)
#define REP(i,s,t) for(int i=(s);i<(t);++i)
#define PER(i,t,s) for(int i=(t);i>(s);--i)
// 省略了不重要的快读
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL INFll = 0x3f3f3f3f3f3f3f3fll;
/* My Code begins here */
const int p = 2;

int n, k, d, q, *a[405], BUFF[4000005], *ed = BUFF + sizeof(BUFF) / sizeof(int), sz[405];
struct DPair{
    int x, y;
    DPair(int x = 0, int y = 0) : x(x), y(y) {}
}BUF[2000005], *b[405], *ED = BUF + sizeof(BUF) / sizeof(DPair);

inline int *alloc(int siz){return ed -= siz;}
inline DPair *Alloc(int siz){return ED -= siz;}

void build(int rt, int l, int r){
    if(l == r) {a[rt] = alloc((sz[rt] = n) + 1);return read(a[rt], a[rt] + n);}
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid);build(rt << 1 | 1, mid + 1, r);
    sz[rt] = (sz[rt << 1] - 1) / p + 1 + (sz[rt << 1 | 1] - 1) / p + 1;
    a[rt] = alloc(sz[rt] + 1);b[rt] = Alloc(sz[rt] + 1);
    int i = 0, j = 0, k = 0;
    while(i < sz[rt << 1] && j < sz[rt << 1 | 1]){
        if(a[rt << 1][i] < a[rt << 1 | 1][j]){
            a[rt][k] = a[rt << 1][i];
            b[rt][k ++] = DPair(i, j);i += p;
        }
        else{
            a[rt][k] = a[rt << 1 | 1][j];
            b[rt][k ++] = DPair(i, j);j += p;
        }
    }
    while(i < sz[rt << 1]) {
        a[rt][k] = a[rt << 1][i];
        b[rt][k ++] = DPair(i, sz[rt << 1 | 1]);i += p;
    }
    while(j < sz[rt << 1 | 1]){
        a[rt][k] = a[rt << 1 | 1][j];
        b[rt][k ++] = DPair(sz[rt << 1], j);j += p;
    }
    b[rt][k] = DPair(sz[rt << 1], sz[rt << 1 | 1]);
}

int ans = 0;
void query(int rt, int l, int r, int key, int x){
    if(key && a[rt][key - 1] >= x) -- key;
    if(l == r) return ans ^= a[rt][key], void();
    int mid = (l + r) >> 1;
    query(rt << 1, l, mid, b[rt][key].x, x);
    query(rt << 1 | 1, mid + 1, r, b[rt][key].y, x);
}


int main(){
    read(n, k, q, d);build(1, 1, k);
    if(sz[1] > 16){
        rep(t, 1, q){
            int x = read() ^ ans;ans = 0;
            query(1, 1, k, std :: lower_bound(a[1], a[1] + sz[1], x) - a[1], x);
            if(t % d == 0) print(ans);
        }
    }
    else{
        rep(t, 1, q){
            int x = read() ^ ans;ans = 0;
            int pos = sz[1];
            rep(i, 0, pos - 1) if(a[1][i] >= x) {pos = i;break;}
            query(1, 1, k, pos, x);
            if(t % d == 0) print(ans);
        }
    }
}
```

---

## 作者：囧仙 (赞：3)

## 题目大意

> $k$ 个单调递增序列，每个序列长度为 $n$ 。有 $q$ 次询问，每次查询**所有**序列中第 $x$ 大的数字。强制在线。  
> $1\le k\le 100;2\le n\le 10^4;q\le 5\times 10^5$ 。

## 题解

**注**：这是一篇**谔谔卡常题解**（并且极容易卡掉）。如果你想学习**分散层叠算法**或者其他复杂度正确的算法，请参见其他题解。

考虑到二分的效率不是很高，我们考虑复杂度相同的**倍增算法**。

事实上，市面上流传的倍增算法效率一般比较低下，导致在通常情况下会被二分吊打。那种常见写法一般如下：

```cpp
int p=1,k=1;
while(k) if(A[p|k]<x) p|=k,k<<=1; else k>>=1;
ans=A[p+1];
```

这种做法考虑到最终的 $p$ 可能很小，于是每次倍增 $k$ 。但事实上，出题人可能会非常毒瘤，导致最终的 $p$ 很大，于是常数随之变大。但其实，当第一次出现 $A_{p+k}> x$ 时， $k$ 就一直处于只减不增的状态了。但是上述做法仍然存在 $k$ 倍增的情况。考虑下面这种简单粗暴的做法：

```cpp
int r=0; for(int i=13;i>=0;--i) if(W[r|(1<<i)]<w) r|=1<<i;
```

由于节省了非常多无意义的判断，所以这种写法的常数明显小于前者。在一些二分测试中，效率也普遍高于一般二分写法。在该题中，即使不加上其他常数优化，也能拿到不错的分数。

于是，我们卡常的第一步大功告成。

---

下一步考虑怎么进一步降低常数。考虑 [$\texttt{[WC2017]挑战}$](https://www.luogu.com.cn/problem/P4604) ，我们只要写一手循环展开，再加上比较常见的 $\text{inline,register}$ 优化，提交上去就能 $\text{AC}$ 了。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(register int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(register int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN =1e4+3,MAXM=1e2+5+3;
int n,k,q,d,t=13,o;
int A[MAXM][MAXN];
inline int get(int *W,int w){
    if(w>W[n]) return 0;
    int r=0; dn(t,0,i) if(W[r|(1<<i)]<w) r|=1<<i; return W[r+1];
}
inline int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
int main(){
    n=qread(),k=qread(),q=qread(),d=qread();
    up(1,k,i) up(1,MAXN,j) A[i][j]=INF;
    up(1,k,i) up(1,n,j) A[i][j]=qread();
    up(1,q,i){
        int x=qread()^o,s1=0,s2=0,s3=0,s4=0,s5=0,s6=0;
        for(int j=1;j<=k;j+=6){
            s1^=get(A[j  ],x);s2^=get(A[j+1],x),
            s3^=get(A[j+2],x);s4^=get(A[j+3],x);
            s5^=get(A[j+4],x);s6^=get(A[j+5],x);
        }
        o=s1^s2^s3^s4^s5^s6; if(i%d==0) printf("%d\n",o);
    }
    return 0;
}
```

---

## 作者：cyffff (赞：2)

[$\text{Link}$](https://www.luogu.com.cn/problem/P6466)
## 题意

给出 $k$ 个长为 $n$ 的有序数组，$q$ 次查询，每次给出数 $x$，分别求出每个数组中 $x$ 的非严格后继，输出它们的异或和。强制在线。

$k\leq 100$，$n\leq 10^4$，$q\leq 5\times 10^5$。
## 思路
分散层叠算法，可以在 $O(k+\log n)$ 的时间复杂度内完成对 $k$ 个长为 $n$ 的序列求某个数的前驱后继。

考虑对 $k$ 个序列建线段树，每个节点维护一个有序数组。对于叶子结点，第 $i$ 个叶子结点的数组即为给出的序列 $i$。

我们定下来一个常数 $p$，对于一个非叶子结点，我们将其左儿子的序列从大到小，每隔 $p$ 个取出一个数，得到数组 $L$（从小到大排），同理得到数组 $R$。

我们将 $L$ 与 $R$ 归并起来，得到此结点的数组，同时我们还需要记录数组中每个数来自左儿子（设为红色）还是右儿子（设为蓝色），位于左儿子（右儿子）的数组中的哪个位置。

对于一次询问，我们在根节点数组上二分出 $x$ 的后继 $t$，考虑如何得到左儿子和右儿子中 $x$ 的后继。假设 $t$ 为红色，在左儿子中的位置为 $i$，则左儿子中，$x$ 的后继的位置一定在 $(i-p,i]$ 中（$i-p$ 位置在此结点的数组中，显然它小于 $x$）。同理找出 $x$ 在根节点上的数组中第一个蓝色后继，令它在右儿子中的位置为 $j$，则右儿子中 $x$ 的后继的位置一定在 $(j-p,j]$ 中。于是我们 $O(p)$ 向前枚举 $x$ 后继位置，向左右儿子递归即可。注意到我们需要求出数组中每个数后面第一个与它异色的数的位置，可以在 `pushup` 时求出。

令 $p$ 为大于等于 $2$ 的常数，则我们发现所有数组长度之和为 $O(nk)$，单次询问每个结点贡献均为常数，总时间复杂度为 $O(nk+q(k+\log n))$。

线段树方法的优势在于可以支持修改和区间查询，更方便维护一些分块中多块二分的问题，例如[由乃打扑克](https://www.luogu.com.cn/problem/P5356)。

代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=100+10,L=1e4+10;
int n,k,q,d,s[N][L];
struct Segment_Tree{
	#define ls (rt<<1)
	#define rs (rt<<1|1)
	const int K=2;
	struct node{
		int val,pos,xp;
		bool s;
		node(int v=0,int p=0,int o=0){ val=v,pos=p,s=o,xp=-1; }
		inline friend bool operator<(const node &a,const node &b){
			return a.val<b.val;
		}
	};
	node pol[N*L*2],*now=pol;
	node *a[N<<2];
	int siz[N<<2]; 
	inline void pushup(int rt){
		static node l[L],r[L];
		int c1=0,c2=0;
		for(int i=siz[ls]-1;i>=0;i-=K)
			l[c1++]=node(a[ls][i].val,i,0);
		for(int i=siz[rs]-1;i>=0;i-=K)
			r[c2++]=node(a[rs][i].val,i,1);
		reverse(l,l+c1);
		reverse(r,r+c2);
		siz[rt]=c1+c2;
		a[rt]=now,now+=siz[rt];
		merge(l,l+c1,r,r+c2,a[rt]);
		for(int lsl=-1,lsr=-1,i=siz[rt]-1;i>=0;i--){
			if(!a[rt][i].s) lsl=i,a[rt][i].xp=lsr;
			else lsr=i,a[rt][i].xp=lsl;
		}
	}
	inline void build(int rt,int l,int r){
		if(l==r){
			siz[rt]=n;
			a[rt]=now,now+=siz[rt];
			for(int i=0;i<siz[rt];i++)
				a[rt][i]=node(s[l][i],i);
			return ;
		}
		int mid=l+r>>1;
		build(ls,l,mid),build(rs,mid+1,r);
		pushup(rt);
	}
	int ans;
	inline void query(int rt,int l,int r,int p,int x){
		while(p&&a[rt][p-1].val>=x) p--;
		if(l==r){
			ans^=a[rt][p].val;
			return ;
		}
		int mid=l+r>>1;
		if(!a[rt][p].s){
			query(ls,l,mid,a[rt][p].pos,x);
			if(a[rt][p].xp!=-1) query(rs,mid+1,r,a[rt][a[rt][p].xp].pos,x);
		}else{
			if(a[rt][p].xp!=-1) query(ls,l,mid,a[rt][a[rt][p].xp].pos,x);
			query(rs,mid+1,r,a[rt][p].pos,x);
		}
	}
	inline int query(int x){
		ans=0;
		int p=lower_bound(a[1],a[1]+siz[1],node(x))-a[1];
		query(1,1,k,p,x);
		return ans;
	}
}T;
int main(){
	n=read(),k=read(),q=read(),d=read();
	for(int i=1;i<=k;i++)
		for(int j=0;j<n;j++)
			s[i][j]=read();
	T.build(1,1,k);
	for(int i=1,lst=0;i<=q;i++){
		lst=T.query(read()^lst);
		if(i%d==0) write(lst),putc('\n');
	}
	flush();
}
```


---

## 作者：critnos (赞：2)

一个优化暴力。

这道题如果按照题意模拟二分，那么只能拿到 81 pts。

所以考虑把所有数组放在一起搞，排下序，存下每个数位于第几行。

好处就是只用二分一次，然后呢？

我们只用暴力从二分到的位置往后扫，把每行碰到的第一个数加进去就可以了。。记得把那些查询结果为 $0$ 的行，即这一行的最大值都小于 $x$ 的特判一下。

用基数排序会比 sort 快一些，归并应该也是，没写过。

复杂度。。不太会算期望复杂度，但是是很容易卡到 $qnk$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s;
}
struct num
{
	int x,p;
	num(){}
	num(int x_,int p_)
	{
		x=x_,p=p_;
	}
	friend bool operator <(num x,num y)
	{
		return x.p<y.p;
	}
}a[1000005];
bool b[105];
int mx[105];
int main()
{
	int n=read(),k=read(),q=read(),d=read(),t,i,j,last=0,x,cnt=0,w,sum;
	for(i=1;i<=k;i++)
	{
		for(j=1;j<=n;j++)
			a[++cnt].p=read(),a[cnt].x=i;
		mx[i]=a[cnt].p;
	}	
	sort(a+1,a+1+cnt);
	for(t=1;t<=q;t++)
	{
		x=read()^last;
		last=0;
		w=0;
		for(i=1<<19;i>=1;i>>=1)//倍增更好
			if(w+i<=cnt&&a[w+i].p<x)
				w+=i;
		memset(b,0,sizeof(b));
		sum=0;
		for(i=1;i<=k;i++)
			sum+=mx[i]>=x;
		for(i=w+1;sum;i++)
			if(!b[a[i].x])
			{
				sum--;
				b[a[i].x]=1;
				last^=a[i].p;
			}
		if(t%d==0) printf("%d\n",last);
	}
}
```


---

