# LITE - Light Switching

## 题目描述

  
Farmer John tries to keep the cows sharp by letting them play with intellectual toys. One of the larger toys is the lights in the barn. Each of the N (2 <= N <= 100,000) cow stalls conveniently numbered 1..N has a colorful light above it.  
  
At the beginning of the evening, all the lights are off. The cows control the lights with a set of N pushbutton switches that toggle the lights; pushing switch i changes the state of light i from off to on or from on to off.  
  
The cows read and execute a list of M (1 <= M <= 100,000) operations expressed as one of two integers (0 <= operation <= 1).  
  
The first kind of operation (denoted by a 0 command) includes two subsequent integers S\_i and E\_i (1 <= S\_i <= E\_i <= N) that indicate a starting switch and ending switch. They execute the operation by pushing each pushbutton from S\_i through E\_i inclusive exactly once.  
  
The second kind of operation (denoted by a 1 command) asks the cows to count how many lights are on in the range given by two integers S\_i and E\_i (1 <= S\_i <= E\_i <= N) which specify the inclusive range in which the cows should count the number of lights that are on.  
  
Help FJ ensure the cows are getting the correct answer by processing the list and producing the proper counts.

## 样例 #1

### 输入

```
4 5
0 1 2
0 2 4
1 2 3
0 2 4
1 1 4
```

### 输出

```
1
2```

# 题解

## 作者：dailt (赞：8)

## 就skr线段树模板题呀
First,解释一下题目大意,一开始有n盏暗着的灯,然后有m次操作,
操作有两种,一种是使x到y这段区间亮着的灯变暗，暗这的灯变亮，另一种是询问x到y这段区间里共有几盏灯是亮的，输出询问的答案。

下面是线段树节点的定义
```cpp
struct node{
	int sum,l,r,laz;
}t[801000<<2]; 
```
l，r表示该节点所覆盖的区间，sum表示这段区间中亮着的灯的个数，laz当然就是懒标记啦

这个题目有两个操作：一个是把x到y（包括x,y）中的亮的灯变灭，灭的灯变亮。另一个操作是查询x到y中（包括x,y）有多少盏灯是亮的。

对于第一个操作，我们要让这段区间中的sum取反，即t[root].sum=(t[root].r-t[root].l+1)-t[root].sum

上面这句话的意思是，让t[root].l到t[root].r这段区间中，亮着的灯变暗，暗着的灯变亮。那一开始亮着的有t[root].sum，暗着的有(t[root].r-t[root].l+1)-t[root].sum （总长度-亮着的=暗着的）。所以取反后亮着的就变成了(t[root].r-t[root].l+1)-t[root].sum

然后对于第二个操作，直接查询并输出就好了（模板呀）

下面附上代码

```
#include <iostream>
#include <cstdio>
#define re register
using namespace std;
string s;
int n,m;
struct node{
	int sum,l,r,laz;
}t[801000<<2]; 
void build(int root,int l,int r){
	t[root].l=l;
	t[root].r=r;
	t[root].laz=0;
	if(l==r){
		t[root].sum=0;
		return ;
	}
	int mid=l+r>>1;
	build(root<<1,l,mid);
	build(root<<1|1,mid+1,r);
	t[root].sum=(t[root<<1].sum+t[root<<1|1].sum);
	return ;
}
void pushdown(int root){
	int mid=(t[root].l+t[root].r)>>1;
	t[root<<1].sum=(mid-t[root].l+1)-t[root<<1].sum;
	t[root<<1|1].sum=(t[root].r-mid)-t[root<<1|1].sum;
	t[root].laz=0;
	t[root<<1].laz^=1,t[root<<1|1].laz^=1;
	return ;
}
void change(int root,int l,int r){
	if(t[root].l==l&&t[root].r==r){
		t[root].sum=(r-l+1)-t[root].sum;
		t[root].laz^=1;
		return ;
	}
	if(t[root].laz) pushdown(root);
	int mid=(t[root].l+t[root].r)>>1;
	if(mid>=r)	change(root<<1,l,r);
	else if(mid+1<=l)	change(root<<1|1,l,r);
	else{
		change(root<<1,l,mid);
		change(root<<1|1,mid+1,r);
	}	
	t[root].sum=(t[root<<1].sum+t[root<<1|1].sum);
	return ;
}
int query(int root,int l,int r){
	if(l==t[root].l&&r==t[root].r){
		return t[root].sum;
	}
	if(t[root].laz)	pushdown(root);
	if(t[root<<1].r>=r)	return query(root<<1,l,r);
	else if(t[root<<1|1].l<=l)	return query(root<<1|1,l,r);
	else{
		int mid=(t[root].l+t[root].r)>>1;
		return query(root<<1,l,mid)+query(root<<1|1,mid+1,r);
	}	
} 
int main(){
	scanf("%d%d",&n,&m);
	build(1,1,n);
	for(re int i=1;i<=m;i++){
		int chk;
		scanf("%d",&chk);
		if(chk==0){
			int x,y;
			scanf("%d%d",&x,&y);
			change(1,x,y);
		}
		if(chk==1){
			int x,y;
			scanf("%d%d",&x,&y);
			printf("%d\n",query(1,x,y));	
		}
	}
	return 0;
}
```

---

## 作者：My_666 (赞：5)

# 线段树区间异或

## 题目描述：

共 $n$ 盏灯（全暗）， $m$ 次操作：

- 对于操作 $0$：令 $l$，$r$之间的灯改变状态$($ $1$ 为亮，$0$ 为暗$)$。
- 对于操作 $1$：查询 $l$，$r$ 之间亮的灯的总数。

## 思路分析：

对于题目的区间修改，和区间求和，再配合数据范围，易想到用线段树来维护。

另外，对于 $1$, $0$ 之间的转换，我们可以用位运算——异或：$\operatorname{xor}$，来实现它。

### 对于异或运算：

- $1$ $\operatorname{xor}$ $1$ $=$ $0$
- $1$ $\operatorname{xor}$ $0$ $=$ $1$
- $0$ $\operatorname{xor}$ $1$ $=$ $1$
- $0$ $\operatorname{xor}$ $0$ $=$ $0$

显然符合题目描述。

此外，调整状态后，区间亮的灯的总数 $=$ 区间的总灯数 $-$ 原来亮的灯的总数。

然后再套上线段树区间异或的板子就好了。

**其他解释会在代码中标注**

## 代码如下：

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e6 + 5;

#define ms(a) memset(a, 0, sizeof(a))

#define ls p << 1 //求p的左儿子 
#define rs p << 1 | 1 //求p的右儿子

template<class T> void read(T &x) {
	x = 0; int f = 0; char ch = getchar();
	while (ch < '0' || ch > '9') {f |= (ch == '-'); ch = getchar();}
	while (ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar();}
	x = f ? -x : x;
	return;
}

int n, m;

int L[N * 4], R[N * 4], s[N * 4], add[N * 4]; // 此处用L[]，R[]存下每个节点的左右儿子，用空间换时间，以此提高效率，add[]为懒标记 

inline void pushup(int p) {
	s[p] = s[ls] + s[rs];
}

//此处为线段树区间异或的板子 （本人线段树为区间判等，可能和大家不太一样，其实还是很好理解的） 
inline void pushdown(int p) {
	if (!add[p]) return; //如果标记为0，则不许要进行操作 
	add[ls] ^= 1, add[rs] ^= 1;//对于此处：一个区间进行两次操作后是没有变化的，因此可以直接取消状态 
	s[ls] = (R[ls] - L[ls] + 1) - s[ls];//对于类似语句请看思路分析 
	s[rs] = (R[rs] - L[rs] + 1) - s[rs];
	add[p] = 0;
}

void build(int p, int l, int r) {
	L[p] = l, R[p] = r;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	pushup(p);
}

void modify(int p, int l, int r) {
	if (L[p] == l && R[p] == r) {
		add[p] ^= 1;
		s[p] = (r - l + 1) - s[p];
		return;
	}
	if (add[p]) pushdown(p);
	int mid = (L[p] + R[p]) >> 1;
	if (r <= mid) modify(ls, l, r);
	else if (l > mid) modify(rs, l, r);
	else modify(ls, l ,mid), modify(rs, mid + 1, r);
	pushup(p);
}

int query(int p, int l, int r) {
	if (L[p] == l && R[p] == r) return s[p];
	if (add[p]) pushdown(p);
	int mid = (L[p] + R[p]) >> 1;
	if (r <= mid) return query(ls, l, r);
	else if (l > mid) return query(rs, l, r);
	return query(ls, l ,mid) + query(rs, mid + 1, r);
}

int main() {
	read(n), read(m);
	build(1, 1, n);
	int q, l, r;
	for (int i = 1; i <= m; i++) {
		read(q), read(l), read(r);
		if (!q) modify(1, l, r);
		else cout << query(1, l ,r) << "\n";
	}
	return 0;
}
```

### 另外，给其实本题有五倍经验！！

1. [SP7259 LITE - Light Switching](https://www.luogu.org/problem/SP7259)

2. [P2846 USACO08NOV 光开关Light Switching](https://www.luogu.org/problem/P2846)

3. [P3870 TJOI2009 开关](https://www.luogu.org/problem/P3870)

4. [P2574 XOR的艺术](https://www.luogu.org/problem/P2574)

5. [P5057 CQOI2006 简单题](https://www.luogu.org/problem/P5057)

## 感谢阅读！

---

## 作者：米奇奇米 (赞：3)

## 哇，一眼分块好题！
### 首先告诉大家一个好秘密！这是一题四倍经验好题。
[经验一：SP7259 LITE - Light Switching](https://www.luogu.org/problemnew/show/SP7259)

[经验二：P3870 [TJOI2009]开关](https://www.luogu.org/problemnew/show/P3870)

[经验三：P2574 XOR的艺术](https://www.luogu.org/problemnew/show/P2574)

[经验四：P2846 [USACO08NOV]光开关Light Switching](https://www.luogu.org/problemnew/show/P2846)

### 接下来，我该大家介绍一下如何用优雅的暴力来解题
### $1.1$理解题目
题目就是让你设计一种数据结构，来支持两种操作，一种是把某一个区间里的灯取相反的状态，另一种就是询问在一个区间里面有几盏灯是亮着的。题目意思很清新！

### $1.2$思路解法
我们对于这题可以利用优雅的暴力——**分块**来解决。那么如何分块呢？很简单以$sqrt(n)$为每个块的长度，对于每个散块直接暴力修改，把整块的$tag$数组异或上$1$(即取反)。**如果修改次数为偶数，那么状态是不会改变的！** 然后就可以啦！

### $1.3$代码实现
```cpp
#include <bits/stdc++.h>
#define sqr(x) x*x
using namespace std;
const int N=2e5+5;
int n,m,Ans,L,R,cnt,size,opt;
int link[N],a[N],Add[N],res[N];
struct node {
    inline void modify(int l,int r) {
        int p=link[l],q=link[r];//在块中的位置
        for ( register int i=l;i<=min(r,p*size);i++ ) {
            res[p]-=a[i]^Add[p];
            a[i]^=1;
            res[p]+=a[i]^Add[p];
        }
        if(p!=q) 
            for ( register int i=(q-1)*size+1;i<=r;i++ ) {
            	res[q]-=a[i]^Add[q];
            	a[i]^=1;
            	res[q]+=a[i]^Add[q];
            }
        for ( register int i=p+1;i<=q-1;i++ ) {
            Add[i]^=1;
            res[i]=size-res[i];//对于剩余块，暴力修改
        }
    }
    inline int query(int l,int r) {
        int ans=0,p=link[l],q=link[r];
        for ( register int i=l;i<=min(r,p*size);i++ ) ans+=a[i]^Add[p];
        if(p!=q) 
            for ( register int i=(q-1)*size+1;i<=r;i++ ) ans+=a[i]^Add[q];
        for ( register int i=p+1;i<=q-1;i++ ) ans+=res[i];
        return ans;
    }
}kuai;
int main() {
    scanf("%d%d",&n,&m); 
    size=sqrt(n); if(sqr(size)<n) size+=1;//分块
    for ( register int i=1;i<=n;i++ ) link[i]=(i-1)/size+1;//记录每一个块的位置
    for ( register int t=1;t<=m;t++ ) {
        scanf("%d",&opt);
        if(opt==1) {
            scanf("%d%d",&L,&R);
            printf("%d\n",kuai.query(L,R));
        }
        if(!opt) {
            scanf("%d%d",&L,&R);
            kuai.modify(L,R);
        }
    }
    return 0;
}
```




---

## 作者：llzzxx712 (赞：2)

# SP7259
[传送门](https://www.luogu.com.cn/problem/SP7259)
## 题意简述
**把灯看成一个布尔值，亮为1，暗为0。**
- 开始时有一个全为0的串。
- 你需要进行两种操作。1.对区间$[S_i,E_i]$中的每一个数进行非运算（由0变为1,1变为0）。2.询问区间$[S_i,E_i]$中1的个数。
- $1≤n,m≤10^5,1≤S_i≤E_i≤n$

## 题目分析
  看到 $1≤n,m≤10^5$ 就可以知道每一次的修改和查询操作复杂度都需要是 $n \log n$ ，那么这就是一道区间修改+区间查询的线段树了。
  
### 建树
这是一个01串，所以一个区间中1的数目（亮着的灯的数目）就是这个区间和。所以我们的线段树可以维护4个值：左端点、右端点、区间和、下传标记。就是这个亚子：

```cpp
struct Tree{
	int le,r;
	ll sum,la2;
	#define le(x) a[x].le
	#define r(x) a[x].r
	#define sum(x) a[x].sum
	#define la2(x) a[x].la2 
}a[N*4];
```
建树嘛就按模板建就好了

```cpp
void build(int p,int le,int r){
	le(p)=le,r(p)=r;
	if(le==r){
		sum(p)=b[le];
		return ;
	}
	int mid=(le+r)/2;
	build(p*2,le,mid);
	build(p*2+1,mid+1,r);
	sum(p)=sum(p*2)+sum(p*2+1); 
}
```

### 修改

把区间里的每一个数由0变成1，1变成0，我们就发现，原来一个长度为L的区间里有a个1，操作后就有L-a个1。所以我们只要用区间长度 r-le+1 减掉原来的区间和 sum 就是新的 sum。

至于下传标记就更简单了。对于1个点，它只有两种状态：要修改和不要修改，所以只要用一个布尔变量存它要不要修改就可以了（当然int也可以）

综上，修改代码应该是：

```cpp
void spread(int p){	
	if(!la2(p)) return;
	sum(p*2)=r(p*2)-le(p*2)+1-sum(p*2);//区间长度减掉原区间和，下同 
	sum(p*2+1)=r(p*2+1)-le(p*2+1)+1-sum(p*2+1);
	la2(p*2)=!la2(p*2);la2(p*2+1)=!la2(p*2+1);//1代表要操作，0代表不要操作，两种操作的转换只要 ! 一下就好了 
	la2(p)=0;//清除标记 
}
void change(int p,int le,int r){
	if(le<=le(p)&&r>=r(p)){
		sum(p)=r(p)-le(p)+1-sum(p);//区间长度减掉原区间和
		la2(p)=!la2(p);
		return;
	}
	spread(p);
	int mid=(le(p)+r(p))/2;
	if(mid>=le) change(p*2,le,r);//处理左右 
	if(mid<r) change(p*2+1,le,r);
	sum(p)=sum(p*2+1)+sum(2*p);
}
```
### 询问

按模板打就好了，从下到上累计答案

```cpp
int ask(int p,int le,int r){
	int ans=0;
	if(le(p)>=le&&r(p)<=r){
		return sum(p); 	
	}
	spread(p);
	int mid=(le(p)+r(p))/2;
	if(mid>=le) ans=ans+ask(p*2,le,r);
	if(mid<r) ans=ans+ask(p*2+1,le,r);
	return ans;
}
```

## 完整代码

 ```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define N 200002
#define ll long long
using namespace std;
int n,m;
int b[N];
struct Tree{
	int le,r;
	ll sum,la2;
	#define le(x) a[x].le
	#define r(x) a[x].r
	#define sum(x) a[x].sum
	#define la2(x) a[x].la2 
}a[N*4];
void build(int p,int le,int r){
	le(p)=le,r(p)=r;
	if(le==r){
		sum(p)=b[le];
		return ;
	}
	int mid=(le+r)/2;
	build(p*2,le,mid);
	build(p*2+1,mid+1,r);
	sum(p)=sum(p*2)+sum(p*2+1); 
}
void spread(int p){	
	if(!la2(p)) return;
	sum(p*2)=r(p*2)-le(p*2)+1-sum(p*2);//区间长度减掉原区间和，下同 
	sum(p*2+1)=r(p*2+1)-le(p*2+1)+1-sum(p*2+1);
	la2(p*2)=!la2(p*2);la2(p*2+1)=!la2(p*2+1);//1代表要操作，0代表不要操作，两种操作的转换只要 ! 一下就好了 
	la2(p)=0;//清除标记 
}
void change(int p,int le,int r){
	if(le<=le(p)&&r>=r(p)){
		sum(p)=r(p)-le(p)+1-sum(p);//区间长度减掉原区间和
		la2(p)=!la2(p);
		return;
	}
	spread(p);
	int mid=(le(p)+r(p))/2;
	if(mid>=le) change(p*2,le,r);//处理左右 
	if(mid<r) change(p*2+1,le,r);
	sum(p)=sum(p*2+1)+sum(2*p);
}
int ask(int p,int le,int r){
	int ans=0;
	if(le(p)>=le&&r(p)<=r){
		return sum(p); 	
	}
	spread(p);
	int mid=(le(p)+r(p))/2;
	if(mid>=le) ans=ans+ask(p*2,le,r);
	if(mid<r) ans=ans+ask(p*2+1,le,r);
	return ans;
}
void read(int &x) {
    int f = 1; x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')   {if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
    x *= f;
}
int main()
{
    cin>>n>>m;
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int c,x,y,k;
		read(c),read(x),read(y);
		switch(c){
			case 0:change(1,x,y);break;
			case 1:printf("%d\n",ask(1,x,y));break;
		}
	}
	return 0;
}
	

```

~~**写题解不易，点个赞呗**~~



---

## 作者：唔啊唔 (赞：1)

## 喜获一道~~大水题~~（居然还是紫题）

就是一道稍作修改的线段树模板题

并且这道题还是四倍经验oh!!!

[P3870](https://www.luogu.org/problem/P3870),[P2846](https://www.luogu.org/problem/P2846),[P2574](https://www.luogu.org/problem/P2574)

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
struct Tree{
    int l,r,wan,hzy;	//wan为区间内打开的灯的数量,hzy为延迟标记 
}t[1000000];
inline void build(int l,int r,int k){	//很简单的建树模板 
    t[k].l=l,t[k].r=r;
    if(l==r){
        t[k].wan=0;
        return;
    }
    int mid=(l+r)/2;
    build(l,mid,2*k);
    build(mid+1,r,2*k+1);
    return;
}
inline void cbj(int k){	//传标记  qwq 
    if(t[k].hzy!=0){
        if(t[2*k].hzy==1) t[2*k].hzy=0;
        else t[2*k].hzy=1;
        if(t[2*k+1].hzy==1) t[2*k+1].hzy=0;
        else t[2*k+1].hzy=1;
        t[2*k].wan=t[2*k].r-t[2*k].l+1-t[2*k].wan;//每次传标记都将此区间翻转,关的开,开的关	
        t[2*k+1].wan=t[2*k+1].r-t[2*k+1].l+1-t[2*k+1].wan;
        t[k].hzy=0;
    }
}
inline void change(int l,int r,int k){	//修改 
    if(l<=t[k].l&&r>=t[k].r){	//区间被完全覆盖 
        t[k].wan=(t[k].r-t[k].l+1)-t[k].wan;	//翻转 
        if(t[k].hzy==1) t[k].hzy=0;	//打标记 
        else t[k].hzy=1;
        return;
    }
    cbj(k);
    int mid=(t[k].r+t[k].l)/2;
    if(l<=mid) change(l,r,2*k);
    if(r>mid) change(l,r,2*k+1);
    t[k].wan=t[2*k].wan+t[2*k+1].wan;
    return;
}
inline int ask(int l,int r,int k){	//询问 
    if(l<=t[k].l&&r>=t[k].r){
        return t[k].wan;
    }
    cbj(k);
    int mid=(t[k].l+t[k].r)/2;
    int lzf=0;
    if(l<=mid) lzf+=ask(l,r,2*k);
    if(r>mid) lzf+=ask(l,r,2*k+1);
    return lzf;
}
int main(){
    cin>>n>>m;
    build(1,n,1);
    for(register int i=1;i<=m;i++){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        if(x==0){
            change(y,z,1);
        }
        else{
            printf("%d\n",ask(y,z,1));
        }
    }
    return 0; 
} 
```


---

## 作者：Skeleton (赞：1)

首先，作为一个蒟蒻的我不得不先声明一下吗，这题有三道重题（算此题），~~所以，赶紧刷题啊~~（光速逃

首先，分析这道题，统计和时候，其实就是把1加起来就行了，因为灯开关有两种状态：0（关）1（开），所以就用这两种状态统计和就好了。

话不多说，本蒟蒻纯递归线段树，其实这题和那个XOR的艺术还是有几分相似，几乎就是改编题，直接上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=1e6+1;
int n,m;
int mark[Maxn];//lazy标记
int sum[Maxn];//记录区间开着的和

void markdown(int rt,int len)//len记录区间长度
{
    if(mark[rt])//如果父亲有lazy标记，则进行下放
    {
        mark[rt<<1]^=1;//异或，这里就是取反，开->关（或者，关->开）
        mark[rt<<1|1]^=1;//对右儿子也是一样下放
        sum[rt<<1]=len-(len>>1)-sum[rt<<1];//取反之后，就是原区间长度-原有的开着的灯数量，因为开着灯关了，关着灯开了，正好互补
        sum[rt<<1|1]=(len>>1)-sum[rt<<1|1];//对右儿子一样
        mark[rt]=0;//下放之后，标记为0
    }
}
void onoffupdate(int rt,int l,int r,int al,int ar)//更新
{
    if(ar<l||r<al)//无交集，则直接返回
    {
        return;
    }
    if(al<=l&&r<=ar)//包含关系，更新
    {
        mark[rt]^=1;//标记要取反
        sum[rt]=r-l+1-sum[rt];//处理sum，同上
        return;//别忘了返回，不然会炸裂
    }
    markdown(rt,r-l+1);//标记下放
    int mid=(l+r)>>1;//递归更新左子树和右子树
    onoffupdate(rt<<1,l,mid,al,ar);
    onoffupdate(rt<<1|1,mid+1,r,al,ar);
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];//自下而上更新sum
}
int asksum(int rt,int l,int r,int al,int ar)//区间询问
{
    if(ar<l||r<al)//无交集，直接返回0，对于加法无影响
    {
        return 0;
    }
    if(al<=l&&r<=ar)//包含关系，直接返回sum[rt]即可
    {
        return sum[rt];
    }
    markdown(rt,r-l+1);//标记下放
    int mid=(l+r)>>1;//递归求左子树和右子树的和
    return asksum(rt<<1,l,mid,al,ar)+asksum(rt<<1|1,mid+1,r,al,ar);
}
int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int opt,l,r;
        scanf("%d %d %d",&opt,&l,&r);
        if(!opt)
        {
            onoffupdate(1,1,n,l,r);
        }
        else
        {
            printf("%d\n",asksum(1,1,n,l,r));
        }
    }
    return 0;
} 
```

---

## 作者：SUNCHAOYI (赞：0)

**读完题目应该就能发现是一道线段树的板子题目。**

这道题目共有两个操作：
- 在一段区间内，把所有开的灯关了，再把关的灯打开。
- 在一段区间内，求开的灯的个数

对于第一个操作，也就是 $0->1,1->0$，是不是很容易想到 `^`。我们可以开两个数组，一个用于维护开的灯，另一个维护关的灯，分别记为 `tree1` 和 `tree2`。   
若有 $a$ 个灯是开的，$b$ 个灯是关的，则当进行操作一后，会有 $b$ 个灯是开的，$a$ 个灯是关的。也就是把 这两个数**交换**了一下。   
因为是区间更新，所以还要配合着**标记下传**的使用。标记很简单，每次**异或**一下就行，但需要记得最后的**标记清空**操作。

对于第二个操作，也就是查询操作。我们只需要查询该区间内有关 `tree2` 的值即可。把区间内符合条件的数组进行累加，最后输出就完事了。

----

完整代码：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int MAX = 100005;
int temp[MAX << 2],n,m,tree1[MAX << 2],tree2[MAX << 2];
//tree1 维护关灯的数量，tree2 维护开灯的数量 
void build (int cur,int l,int r);
void ch (int cur,int l,int r,int x,int y);
void pushdown (int cur);
int query (int cur,int l,int r,int x,int y);
int main ()
{ 
	scanf ("%d%d",&n,&m);
	build (1,1,n);
	for (int i = 1;i <= m;++i)
	{
		int type;
		scanf ("%d",&type);
		if (type == 0)
		{
			int x,y; 
			scanf ("%d%d",&x,&y);
			ch (1,1,n,x,y);
		}
		else 
		{
			int x,y;
			scanf ("%d%d",&x,&y);
			printf ("%d\n",query (1,1,n,x,y));
		}
	}
	return 0;
}
void build (int cur,int l,int r)
{
	if (l == r)
	{
		tree1[cur]++;//同理 tree[cur] = 1 
		return ;
	}
	int mid = (l + r) >> 1;
	build (cur << 1,l,mid);build (cur << 1 | 1,mid + 1,r);
	tree1[cur] = tree1[cur << 1] + tree1[cur << 1 | 1];
}
void ch (int cur,int l,int r,int x,int y)
{
	if (l >= x && r <= y)
	{
		temp[cur] ^= 1;//异或 
		swap (tree1[cur],tree2[cur]);//交换 
		return ;
	}
	int mid = (l + r) >> 1;
	pushdown (cur);
	if (x <= mid) ch (cur << 1,l,mid,x,y);
	if (y > mid) ch (cur << 1 | 1,mid + 1,r,x,y);
	tree1[cur] = tree1[cur << 1] + tree1[cur << 1 | 1];
	tree2[cur] = tree2[cur << 1] + tree2[cur << 1 | 1];//同时更新 
}
void pushdown (int cur)//标记下传 
{
	if (temp[cur] == 0) return ;
	swap (tree1[cur << 1],tree2[cur << 1]);
	swap (tree1[cur << 1 | 1],tree2[cur << 1 | 1]);//交换 
	temp[cur << 1] ^= 1,temp[cur << 1 | 1] ^= 1;//异或一下 
	temp[cur] = 0;//清空！！！ 
}
int query (int cur,int l,int r,int x,int y)
{
	if (l >= x && r <= y) return tree2[cur];//注意返回 tree2 的值 
	int mid = (l + r) >> 1;
	pushdown (cur);
	int ans = 0;
	if (x <= mid) ans += query (cur << 1,l,mid,x,y);
	if (y > mid) ans += query (cur << 1 | 1,mid + 1,r,x,y);
	return ans;
} 
```

---

## 作者：Na2PtCl6 (赞：0)

## 分析题目

这题是一个很模板的区间异或问题，我们用线段树维护区间和来解决。

## 代码
```cpp
#include<cstdio>
using namespace std;
const int maxn=200005;
int n,m,k;
int arr[maxn],tree[maxn<<2],tag[maxn<<2];

void push_down(int size,int node){  //区间长度，当前节点 
	int lnode=node<<1|1,rnode=(node<<1)+2;
	if(tag[node]){  //如果这个区间需要被更新 
		tag[lnode]^=1,tag[rnode]^=1;  //更新左右子节点的懒标记
		//维护区间和
		tree[lnode]=size-(size>>1)-tree[lnode];   
		tree[rnode]=(size>>1)-tree[rnode]; 
		tag[node]=0;  //清空懒标记 
	}
}

void update(int l,int r,int node,int start,int end){
	if(start<=l&&r<=end){
		tag[node]^=1;
		tree[node]=r-l+1-tree[node];  //维护异或后的区间和 
		return ; 
	}
	push_down(r-l+1,node);
	int mid=(l+r)>>1;
	int lnode=node<<1|1,rnode=(node<<1)+2;
	if(start<=mid)
		update(l,mid,lnode,start,end);
	if(end>mid)
		update(mid+1,r,rnode,start,end);
	tree[node]=tree[lnode]+tree[rnode];
}

int query(int l,int r,int node,int start,int end){
	if(start>r||end<l)
		return 0;
	if(l>=start&&r<=end)
		return tree[node];
	push_down(r-l+1,node);
	int mid=(l+r)>>1;
	int lnode=node<<1|1,rnode=(node<<1)+2;
	int lsum=query(l,mid,lnode,start,end);
	int rsum=query(mid+1,r,rnode,start,end);
	return lsum+rsum;
}

int main(){
	scanf("%d%d",&n,&m);
	int op,l,r;
	while(m--){
		scanf("%d%d%d",&op,&l,&r);
		if(!op)
			update(0,n-1,0,l-1,r-1);
		else
			printf("%d\n",query(0,n-1,0,l-1,r-1));
	}
	return 0;
}
```

---

## 作者：S1gMa (赞：0)

###### ~~讲真 感觉这题最多绿~~

我们由题可以知道： 此题为区间修改 / 求和性问题 可以用线段树来写。


------------


当指令为 $0$ 时将 $L  \sim R$ 这个区间的 $0$ 变为 $1$，反正变为 $0$。

很明显就是令 $L  \sim R$ 区间 所有数进行异或。

举个例子
```
0 1 1 0 1 0 1 0 1
```
令 $L = 2$, $R = 6$, 则此时原数列变为：
```
0 0 0 1 0 1 1 0 1
```



------------
当指令为 $1$ 时统计 $L  \sim R$ 这个区间 有多少个 $1$。

看到这里可以将问题转化一下 也是就求这个区间的和。


------------


知道以上思路就很好解了 接下来看代码：
```
#include <bits/stdc++.h>
using namespace std;
#define MAX_LEN 10000005

int arr[MAX_LEN];
int size1;
long long add[MAX_LEN];
long long tree[MAX_LEN] = {0};
int q, p, m;
long long k;
char s[10000001];

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

void push_down(int node, int m)
{
    if (add[node])
    {
        add[2 * node + 1] ^= 1;
        add[2 * node + 2] ^= 1;
        tree[2 * node + 1] = (m - (m >> 1)) - tree[2 * node + 1];
        tree[2 * node + 2] = (m >> 1) - tree[2 * node + 2];
        add[node] = 0;
    }
}//下标下移操作 也要进行异或

void build_tree(int node, int start, int end)
{
    add[node] = 0;
    if (start == end)
        tree[node] = arr[start];
    else
    {
        int mid = (start + end) / 2;
        int left_node = 2 * node + 1;
        int right_node = 2 * node + 2;
        build_tree(left_node, start, mid);
        build_tree(right_node, mid + 1, end);
        tree[node] = tree[left_node] + tree[right_node];
    }
}//建树
void arr_tree(int node, int start, int end, int L, int R)
{
    if (L <= start && end <= R)
    {
        add[node] ^= 1;//将标记数组异或
        tree[node] = end - start + 1 - tree[node];
        return;
    }
    push_down(node, end - start + 1);
    int mid = (start + end) / 2;
    int left_node = 2 * node + 1;
    int right_node = 2 * node + 2;
    if (L <= mid)
        arr_tree(left_node, start, mid, L, R);
    if (R > mid)
        arr_tree(right_node, mid + 1, end, L, R);
    tree[node] = tree[left_node] + tree[right_node];
}//修改L - R这个区间的值， 也就是取其异或的值

long long query_tree(int node, int start, int end, int L, int R)
{
    if (R < start || L > end)
        return 0;
    else if (L <= start && end <= R)
        return tree[node];
    else if (start == end)
        return tree[node];
    else
    {
        push_down(node, end - start + 1);
        int mid = (start + end) / 2;
        int left_node = 2 * node + 1;
        int right_node = 2 * node + 2;
        long long sum_left = query_tree(left_node, start, mid, L, R);
        long long sum_right = query_tree(right_node, mid + 1, end, L, R);
        return sum_left + sum_right;
    }
}

int main()
{
    size1 = read(), m = read();
    for (int i = 0; i < size1; i++)
        arr[i] = 0;//输入 ： 因为初始时灯都是关的
    build_tree(0, 0, size1 - 1);
    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        z = read();
        if (z == 0)
        {
            x = read(), y = read();
            arr_tree(0, 0, size1 - 1, x - 1, y - 1);
        }
        if (z == 1)
        {
            x = read(), y = read();
            long long sum = query_tree(0, 0, size1 - 1, x - 1, y - 1);
            cout << sum << endl;
        }
    }
    return 0;
}
```

---

## 作者：Erusel (赞：0)

~~据说这题好像有六倍经验~~

我们简单分析一下

我们令灯关着的时候是0，开着的时候是1

初始所有数都是0

题目要求支持两种操作，一种是区间异或1，还有一种是区间查询1的个数

考虑到所有数中只有0和1

所以查询可以改为查询区间和

区间异或1也可以从区间和的角度取考虑问题

---

假设我们原来有$k$个1，区间长度为$l$

现在就有$l-k$个1

所以$sum_{now}=l-sum_{pre}$

标记下传也可以维护了

时间复杂度就是维护一颗线段树的时间$O(nlogn)$

code:

```
#include<bits/stdc++.h>

#define rd(x) x=read()
#define N 200005 
 
using namespace std;

int n,m;
struct T{
	int l,r,mid,v,tag;
}t[N<<2];

inline int read()
{
    int f=1,x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    return x*f;
}

void pushdown(int rt,int len)
{
	if(t[rt].tag)
    {
        t[rt<<1].tag^=1; 
        t[rt<<1|1].tag^=1;
        t[rt<<1].v=(len-(len>>1))-t[rt<<1].v;
        t[rt<<1|1].v=(len>>1)-t[rt<<1|1].v;
        t[rt].tag=0;
    }
}

void build(int rt,int l,int r)
{
	int mid=(l+r)>>1;
	t[rt].l=l,t[rt].r=r,t[rt].mid=mid,t[rt].tag=0;
	if(l==r)
	{
		t[rt].v=0;
		return;
	}
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
	t[rt].v=t[rt<<1].v+t[rt<<1|1].v;
}

void update(int rt,int l,int r)
{
    if(l<=t[rt].l&&t[rt].r<=r)
    {
        t[rt].tag^=1;     
        t[rt].v=t[rt].r-t[rt].l+1-t[rt].v;    
        return;
    }
    pushdown(rt,t[rt].r-t[rt].l+1);
    if(l<=t[rt].mid)update(rt<<1,l,r);    
    if(t[rt].mid<r)update(rt<<1|1,l,r);        
    t[rt].v=t[rt<<1].v+t[rt<<1|1].v; 
}
int query(int rt,int l,int r)
{
    if(l<=t[rt].l&&t[rt].r<=r)return t[rt].v;
    pushdown(rt,t[rt].r-t[rt].l+1);
    int sum=0;
    if(l<=t[rt].mid)sum+=query(rt<<1,l,r); 
    if(t[rt].mid<r)sum+=query(rt<<1|1,l,r);        
    return sum;
}

int main()
{
	rd(n),rd(m);
	build(1,1,n);
	while(m--)
	{
		int opt,l,r;
		rd(opt),rd(l),rd(r);
		if(opt)printf("%d\n",query(1,l,r));
		else update(1,l,r);	
	}
	
	return 0;
}

```

---

## 作者：两年打铁 (赞：0)

我们将灯开着视为1，关着视为0。

那么一段区间开着的灯的数量就是这段区间的和，这样很容易就能想到用线段树来维护。

每次反转可以用懒标记来维护，

反转后开着的灯的数量就是这段区间的长度减去现在的这段区间开着的灯的数量

即 $f[k]=(r-l+1)-f[k]$;

比较好理解，可以当成线段树的入门题来做

```cpp
#include<bits/stdc++.h>
#define swap mswap
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
using namespace std;
int a[8000100],f[8000010],n,m;
char s[2000100];
void swap(int &x,int &y)
{
	x^=y^=x^=y;
}
void read(int &x)
{
	x=0;
	char ch=getchar();
	int pd=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			pd=-pd;
		}
		ch=getchar();
	}
	while(ch<='9'&&ch>='0')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=pd;
}
void write(const int &x)
{
	char f[100001];
	int s=0;
	int tmp=x;
	if(tmp==0)
	{
		putchar('0');
		return;
	}
	if(tmp<0)
	{
		tmp=-tmp;
		putchar('-');
	}
	while(tmp>0)
	{
		f[s++]=tmp%10+'0';
		tmp/=10;
	}
	while(s>0)
	{
		putchar(f[--s]);
	}
}
void build(int k,int l,int r)
{
	if(l==r)
	{
		a[k]=s[l]-'0';
		f[k]=a[k];
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	f[k]=f[k<<1]+f[k<<1|1];
}
void add(int k,int l,int r)
{
	a[k]^=1;
	f[k]=r-l+1-f[k];
}
void push_down(int k,int l,int r)
{
	int mid=(l+r)>>1;
	if(a[k]&1)
	{
		add(k<<1,l,mid);
		add((k<<1)|1,mid+1,r);
		add(k,l,r);
	}
	f[k]=f[k<<1]+f[(k<<1)|1];
}
void change(int k,int l,int r,int p,int q)
{
	
	if(l>q||r<p)return;
	if(l>=p&&r<=q)
	{
		a[k]^=1;
		push_down(k,l,r);
		return;
	}
	int mid=(l+r)>>1;
	push_down(k,l,r);
	change(k<<1,l,mid,p,q);
	change(k<<1|1,mid+1,r,p,q);
	f[k]=f[k<<1]+f[(k<<1)|1];
}
int query(int k,int l,int r,int p,int q)
{
	push_down(k,l,r);
	if(l>q||r<p)
	{
		return 0;
	}
	if(l>=p&&r<=q)
	{
		return f[k];
	}
	int ans=0;
	int mid=(l+r)>>1;
	if(p<=mid)
	{
		ans+=query(k<<1,l,mid,p,q);
	}
	if(q>mid)
	{
		ans+=query((k<<1)|1,mid+1,r,p,q);
	}
	return ans;
}
int main()
{
	memset(a,0,sizeof(a));
	memset(f,0,sizeof(f));
	read(n);
	read(m);
	for(register int i=1;i<=m;++i)
	{
		int z=0,x=0,y=0;
		read(z);
		read(x);
		read(y);
		if(z==0)
		{
			change(1,1,n,x,y);
		}
		else 
		{
			write(query(1,1,n,x,y));puts("");
		}
	}
}
```


---

## 作者：YLWang (赞：0)

这个题目其实挺简单的。

首先要明确题意：


给定一个全部为0的数列和两个操作（经过一定的转化）：

0 x y：将$[x, y]$ 区间内的数全部按位取反

1 x y: 求$[x, y]$ 的区间和


~~那么多简单啊~~

其实就是线段树裸题，只不过把P3372的加改成了取反

这里提供一种与一楼不同的线段树写法：把每次操作的区间l, r传进函数里

代码：

```
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define mst(a,b) memset(a,b,sizeof(a))
#define For(i, k, j) for(int i = (k); i <= (j); i++)
#define INF 2147483647/3
#define ll long long
using namespace std;
inline int read()
{
    int num = 0;char c=' ';
    for(;c>'9'||c<'0';c=getchar()) ;
    for(;c>='0'&&c<='9';num=(num<<1)+(num<<3)+c-48,c=getchar());
    return num;
}
int n, Qnum;
#define MAXN 400005
struct Seg {
    int val, lzy;
}c[MAXN<<2];
#define ls (k << 1)
#define rs (k << 1 | 1)
inline void pushdown(int k, int l, int r) {
    int mid = (l + r) >> 1;
    if(c[k].lzy & 1) {
        c[ls].val = (mid - l + 1) - c[ls].val;
        c[rs].val = (r - mid) - c[rs].val;
    }
    c[ls].lzy += c[k].lzy % 2; 
    c[rs].lzy += c[k].lzy % 2; 
    c[k].lzy = 0;
}
inline void pushup(int k) {
    c[k].val = c[ls].val + c[rs].val;
}	
//inline void debug(int k, int l, int r, int ul, int ur) {
//	For(i, 1, 7) {
//		printf("&&&%d %d %d\n", i, c[i].val, c[i].lzy);
//	}
//	
//}
inline void update(int k, int l, int r, int ul, int ur) {
    if(l != r) pushdown(k, l, r);
    if(l == ul && r == ur) {c[k].val = (r - l + 1) - c[k].val; c[k].lzy++; return;}
    int mid = (l + r) >> 1;
    if(mid  >= ur) {
        update(ls, l, mid, ul, ur);
    } else if(mid < ul) {
        update(rs, mid+1, r, ul, ur);
    } else {
        update(ls, l, mid, ul, mid);
        update(rs, mid+1, r, mid+1, ur);
    }
    pushup(k);

}
inline int query(int k, int l, int r, int ql, int qr) {
    if(l != r) pushdown(k, l, r);
    if(l == ql && r == qr) {
        return c[k].val;
    }
    int mid = (l + r) >> 1;
    if(mid >= qr) {
        return query(ls, l, mid, ql, qr);
    } else if(mid < ql) {
        return query(rs, mid+1, r, ql, qr);
    } else {
        return query(ls, l, mid, ql, mid) + query(rs, mid+1, r, mid+1, qr);
    }
}
int main()
{
    n = read(), Qnum = read();
    while(Qnum--) {
        int opt = read(), l = read(), r = read();
        if(opt) {
            printf("%d\n", query(1, 1, n, l, r));
//			debug(1, 1, n, l, r);
        } else {
            update(1, 1, n, l, r);
//			debug(1, 1, n, l, r);
        }
    }
    return 0;
}



```

---

