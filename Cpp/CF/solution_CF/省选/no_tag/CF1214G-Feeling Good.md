# Feeling Good

## 题目描述

最近，生物学家们得出了一个关于如何判断变色龙心情的有趣结论。我们可以将变色龙的身体看作一个 $n \times m$ 的矩形表格，每个格子可以是绿色或蓝色，并且可以在这两种颜色之间切换。我们用 $(x, y)$（$1 \leq x \leq n$，$1 \leq y \leq m$）表示第 $x$ 行第 $y$ 列的格子。

我们定义变色龙的“好心情证明”为：存在四个格子，它们是某个子矩形的四个角，并且这四个格子中，对角线上的格子颜色相同，但四个格子的颜色不全相同。形式化地说，就是存在四个格子 $(x_1, y_1)$、$(x_1, y_2)$、$(x_2, y_1)$、$(x_2, y_2)$，其中 $1 \leq x_1 < x_2 \leq n$，$1 \leq y_1 < y_2 \leq m$，满足 $(x_1, y_1)$ 和 $(x_2, y_2)$ 的颜色相同，$(x_1, y_2)$ 和 $(x_2, y_1)$ 的颜色相同，但这四个格子的颜色不全一样。研究发现，只要存在这样的四个格子，变色龙就是好心情；反之，如果不存在这样的四个格子，变色龙就是坏心情。

你的任务是帮助科学家编写一个程序，在每次颜色变化后判断变色龙的心情。如果变色龙是好心情，还需要输出任意一组满足条件的四个数 $x_1$、$y_1$、$x_2$、$y_2$，使得 $(x_1, y_1)$、$(x_1, y_2)$、$(x_2, y_1)$、$(x_2, y_2)$ 构成好心情证明。

初始时，变色龙身体的所有格子都是绿色。之后，变色龙的颜色会发生若干次变化。每次变化会将某一行的一个连续区间的颜色全部反转。具体来说，每次变化由三个整数 $a$、$l$、$r$（$1 \leq a \leq n$，$1 \leq l \leq r \leq m$）描述，将第 $a$ 行第 $l$ 列到第 $r$ 列之间的所有格子的颜色反转。

请你在每次变化后，输出变色龙的心情。如果是好心情，还要输出一组好心情证明。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 2 6
1 1 1
2 2 2
2 1 1
1 2 2
2 2 2
1 1 1
```

### 输出

```
-1
1 1 2 2
-1
-1
-1
1 1 2 2
```

## 样例 #2

### 输入

```
4 3 9
2 2 3
4 1 2
2 1 3
3 2 2
3 1 3
1 2 2
4 2 3
1 1 3
3 1 3
```

### 输出

```
-1
2 1 4 3
-1
2 1 3 2
3 2 4 3
1 1 2 2
1 1 2 2
-1
2 1 3 2
```

# 题解

## 作者：skydogli (赞：7)

题意：一个 $n\times m$ 的 $01$ 矩阵，每次操作为对一行的一段区间取反，每次输出一个矩阵，要求对角值不同,无解输出 $-1$ 。

关键性质：如果存在两行满足这两行的 $1$ 的位置集合没有包含关系，则这两行肯定可以构造出合法的矩阵，构造方法是左右端点分别为两行的第一次单独出现 $1$ 的位置，这个比较显然。

同时，按 $1$ 的个数从小到大排序，如果全局存在满足条件的两行，那么必有相邻两行满足条件。

证明：假设 $i<j<k$ 且 $S_i \cap S_k\neq S_i$ ，如果 $S_i\subset S_j$，则必有 $S_j\cap S_k\neq S_j$，否则 $S_i\cap S_j\ne S_i$。

于是用 ```set``` 维护 $1$ 的个数的大小关系以及 ```bitset``` 判断两行间的包含关系即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	int a=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while('0'<=c&&c<='9'){
		a=a*10+c-48;
		c=getchar();
	}
	return a;
}
#define MN 2005
#define pii pair<int,int>
#define mp make_pair
#define x first
#define y second
bitset<MN>tmp,qwq,bit[MN];
int n,m,q,cnt[MN];
struct cmp{
	bool operator () (const int &a,const int &b){
		if(cnt[a]==cnt[b])return a<b;
		return cnt[a]<cnt[b];
	}
};
set<int,cmp>S;
#define itset set<int,cmp>::iterator
int now;
set<pii >mat;
void INS(int a){
	S.insert(a);
	itset it=S.find(a),il=it,ir=it;
	il--;ir++;
	if(cnt[*il]&&ir!=S.end()&&((bit[*il]&bit[*ir])!=bit[*il]))
		mat.erase(mp(*il,*ir));
	if(cnt[*il]&&((bit[*il]&bit[*it])!=bit[*il])){
		mat.insert(mp((*il),(*it)));
	}
	if(ir!=S.end()&&((bit[*it]&bit[*ir])!=bit[*it])){
		mat.insert(mp(*it,*ir));
	}
}
void DEL(int a){
	itset it=S.find(a),il=it,ir=it;
	il--;ir++;
	if(cnt[*il]&&ir!=S.end()&&((bit[*il]&bit[*ir])!=bit[*il]))
		mat.insert(mp(*il,*ir));
	if(cnt[*il]&&((bit[*il]&bit[*it])!=bit[*il]))mat.erase(mp((*il),(*it)));
	if(ir!=S.end()&&((bit[*it]&bit[*ir])!=bit[*it]))mat.erase(mp(*it,*ir));
	S.erase(a);
}
int main(){

	n=read();m=read();q=read();
	for(int i=0;i<=n;++i)S.insert(i);
	for(int i=1;i<=q;++i){
		int a=read(),l=read(),r=read();
		tmp.set();tmp>>=(MN-(r-l+1));tmp<<=l;
		DEL(a);
		bit[a]^=tmp;
		cnt[a]=bit[a].count();
		INS(a);
		if(!mat.size())puts("-1");
		else{
			pii w=*mat.begin();
			int x1=w.x,x2=w.y;
			qwq=bit[w.x]^bit[w.y];
			int y1=(qwq&bit[w.x])._Find_first();
			int y2=(qwq&bit[w.y])._Find_first();
			if(x1>x2)swap(x1,x2);
			if(y1>y2)swap(y1,y2);
			printf("%d %d %d %d\n",x1,y1,x2,y2);
		}
	}
	return 0;
}

```

---

## 作者：ljc20020730 (赞：3)

## 题意

一个大小为$n\times m$的$01$矩阵，初始所有元素都为$0$。

每一次操作，形如$a \ l \ r$，其含义是将第$a$行的第$i\in[l,r]$的元素取反。

每一次操作以后，请你输出在该矩阵中的子矩阵，记为$(x_1,y_1,x_2,y_2)$

如果有不只$1$个答案，输出任意一个即可。

- 左上角坐标为$(x_1,y_1)$,右下角坐标为$(x_2,y_2)$
- $(x_1,y_1)$中的元素和$(x_2,y_2)$中的元素相同。
- $(x_1,y_2)$中的元素和$(x_2,y_1)$中的元素相同。
- $(x_1,y_1)$中的元素和$(x_2,y_1)$中的元素相反。

简单叙述为，一个左上角为$(x_1,y_1)$右下角为$(x_2,y_2)$的子矩阵（其中$1 \leq x_1 < x_2 \leq n ,1 \leq y_1 < y_2 \leq m$），满足
对角元素相同，同侧元素相反。

下列两个矩阵是合法的：

$\begin{matrix} 1 & 0\\  0 & 1 \end{matrix}\ \ \ \ \ \ $ 或者  $\ \ \ \ \ \  \begin{matrix} 0 & 1\\  1 & 0 \end{matrix}$

如果不存在这样一个子矩阵，则输出$-1$。

- 对于$100\%$的数据满足$1 \leq n,m \leq 2000 , 1 \leq q \leq 5\times 10^5$
- 时间限制：$3s$

## 题解

对于维护$01$序列，我们通常会采用$bitset$来试图优化时间复杂度。

我们这里对于$bitset$的具体用法将不再展开。

首先，对于每一行都建立一个$bitset$来维护该行中对应列的元素信息$0/1$。

假设，现在有两行的$bitset$为$A$和$B$，那么如何判断这两个行是否存在答案呢？

> 我们定义两个$bitset$的包含关系为： 假设$A$的所有$1$的位置$B$都有，则称$A$被$B$包含，记做$A \sqsubset B$。

显然，若$A \sqsubset  B$那么$A,B$这两行是不存在合法答案的。

如何简单的判断这个包含关系呢，我们只需要简单实用位运算即可。

利用$bitset$复杂度为$O(\frac{n}{w})$的优秀算法，我们可以进行如下操作：

> 若$(A \ or \ B) = B$则 $A \sqsubset B $

假设，现在有两行的$bitset$为$A$和$B$，那么如何输出任意两个位置使得$0-1$并且$1-0$  或者 $1-0$并且$0-1$呢？

我们可以先将同为$1$的地方找出来，$C = A \ and \ B$，然后对$A$执行$A \ xor \ C$的操作，这样如果是$1$那一位，必然是$A$中有$0$的那一位，恰好可以和$B$中的该位上的$1$位对应，对$B$进行同样的操作，就可以找出$B$中是$0$而$A$中是$1$的位置了。


接下来到了，本题的关键部分，如何找出并且维护合法的答案集合呢？

首先，我们发现，只有如下的一种可能，使得输出答案$-1$，即所有$bitset$都被某一个$bitset$包含。

所以，我们想到，可以按照$bitset$中$1$的个数排序，利用$\sqsubset$ 的传递性，即$A \sqsubset B , C \sqsubset A$则$C \sqsubset B$

如果输出$-1$那么，必然可以在按照$1$个数排序后，相邻两个$bitset$，前面一个被后面一个包含，否则，答案就是相邻两个$bitset$了，可以用上面交代的方法计算答案。

所以，本题我们可以开两个$set$，其中第一个$set$按照每个$bitset$中$1$的个数排序，而第二个则是保存答案集合。

每次只需维护这两个集合，然后输出的时候再答案集合里任取一个即可。

时间复杂度是$O(q (\frac{m}{w} + log_2 \ n))$

```cpp
# pragma GCC optimize(3)
# include<bits/stdc++.h>
using namespace std;
const int N=2005;
bitset<N>flp[N],a[N];
int n,m,q,size[N];
set< pair<int,int> >set1,set2;
inline int read()
{
    int X=0,w=0; char c=0;
    while(c<'0'||c>'9') {w|=c=='-';c=getchar();}
    while(c>='0'&&c<='9') X=(X<<3)+(X<<1)+(c^48),c=getchar();
    return w?-X:X;
}
void write(int x) {
	if (x<0) x=-x,putchar('-');
	if (x>9) write(x/10);
	putchar('0'+x%10);
}
bool Check(int p,int q) {
	return ((a[p]&a[q])!=a[p] && (a[p]&a[q])!=a[q]);
}
void Reserve(int p,int l,int r) {
	a[p]^=((flp[r]>>l)<<l);
	size[p]=a[p].count();
}
void Remove(int p) {
	set< pair<int,int> >::iterator it2=set1.find(make_pair(size[p],p)),eee=set1.end(),it1,it3;
	--eee; it1=it3=it2;
	bool flag1=false,flag2=false;
	if (it1!=set1.begin()) {
		--it1; flag1=true;
		int t1=it1->second,t2=p;
		set2.erase(make_pair(t1,t2));
	}
	if (it3!=eee) {
		++it3; flag2=true;
		int t2=it3->second,t1=p;
		set2.erase(make_pair(t1,t2));
	}
	if (flag1 && flag2 && Check(it1->second,it3->second)) {
		int t1=it1->second,t2=it3->second;
		set2.insert(make_pair(t1,t2));
	}
	set1.erase(make_pair(size[p],p));
}
void Insert(int p) {
	set1.insert(make_pair(size[p],p));
	set< pair<int,int> >::iterator it2=set1.find(make_pair(size[p],p)),eee=set1.end(),it1,it3;
	--eee; it1=it3=it2;
	bool flag1=false,flag2=false;
	if (it1!=set1.begin()) {
		--it1; flag1=true;
		int t1=it1->second,t2=p;
		if (Check(t1,t2)) set2.insert(make_pair(t1,t2));
	}
	if (it3!=eee) {
		++it3; flag2=true;
		int t2=it3->second,t1=p;
		if (Check(t1,t2)) set2.insert(make_pair(t1,t2));
	}
	if (flag1 && flag2 && Check(it1->second,it3->second)) {
		int t1=it1->second,t2=it3->second;
		set2.erase(make_pair(t1,t2));
	}
}
void work()
{
	if (!set2.size()) { write(-1);putchar('\n'); return;}
	int x1=set2.begin()->first,x2=set2.begin()->second;
	int y1=(a[x1]^(a[x1]&a[x2]))._Find_first();
	int y2=(a[x2]^(a[x1]&a[x2]))._Find_first();
	if (x1>x2) swap(x1,x2);
	if (y1>y2) swap(y1,y2);
	write(x1); putchar(' ');write(y1); putchar(' ');
	write(x2); putchar(' ');write(y2); putchar('\n');
}
int main() {
	n=read(); m=read(); q=read();
	for (int i=1;i<=n;i++) set1.insert(make_pair(0,i));
	for (int i=1;i<=m;i++) flp[i]=flp[i-1],flp[i][i]=1;
	while (q--) {
		int p=read(),l=read(),r=read();
		Remove(p); Reserve(p,l,r); Insert(p);
		work();
	}
	return 0;
}
```

---

