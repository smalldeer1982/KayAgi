# [USACO24OPEN] Grass Segments G

## 题目描述

Bessie 正在数轴的正半轴上种一些草。她有 $N$（$2\le N\le 2\cdot 10^5$）个不同的栽培品种，并将把第 $i$ 个品种种植在区间 $[l_i,r_i]$（$0<l_i<r_i\le 10^9$）内。

此外，品种 $i$ 会在存在某个品种 $j$（$j\neq i$）使得品种 $j$ 与品种 $i$ 重叠至少 $k_i$（$0<k_i\le r_i-l_i$）长度时生长得更好。Bessie 想要评估她所有的品种。对于每一个 $i$，计算 $j\neq i$ 的数量，使得 $j$ 与 $i$ 重叠至少 $k_i$ 长度。 

## 说明/提示

### 样例解释 1

两品种的重叠部分为 $[4,6]$，长度为 $2$，不小于 $2$ 但并非不小于 $3$。

### 测试点性质

- 测试点 $4-5$：$N\le 5000$。
- 测试点 $6-11$：$k$ 对于所有的区间均相同。
- 测试点 $12-20$：没有额外限制。

此外，对于测试点 $5$，$7$，……，$19$，对于所有 $i$ 有 $r_i\le 2N$。 

## 样例 #1

### 输入

```
2
3 6 3
4 7 2```

### 输出

```
0
1```

## 样例 #2

### 输入

```
4
3 6 1
2 5 1
4 10 1
1 4 1```

### 输出

```
3
3
2
2```

## 样例 #3

### 输入

```
5
8 10 2
4 9 2
3 7 4
5 7 1
2 7 1```

### 输出

```
0
3
1
3
3```

# 题解

## 作者：FFTotoro (赞：13)

考虑对于一个区间 $[l_i,r_i]$，最少重叠长度为 $k_i$，怎样的区间 $[l_j,r_j]$ 可以与前者产生贡献；首先 $r_j-l_j\ge k_i$，在满足这个条件的情况下需要有 $r_j\ge l_i+k_i\land l_j\le r_i-k_i$，这里 $\land$ 表示[合取](https://baike.baidu.com/item/%E5%90%88%E5%8F%96/2841151)，即 C++ 中的 $\mathrm{and}$。正难则反，考虑用长度 $\ge k_i$ 的区间数量减去 $r_j<l_i+k_i$ 以及 $l_j>r_i-k_i$ 的区间数量和；容易得知后两部分是不交的，可以分开计算。

统计这个数量这是一个经典的二维数点问题。直接将待处理的数组按照 $k$ 降序排序，复制一份按照 $r-l$ 排序。扫前者的同时从后者里面把满足 $r-l\ge k$ 的区间不断加入答案，用 `__gnu_pbds::tree` 插入元素、统计答案即可。可以参考代码实现。

放代码：

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
typedef pair<int,int> pii;
typedef tuple<int,int,int,int> tpi;
int main(){
  ios::sync_with_stdio(false);
  int n,p=0; cin>>n;
  vector<tpi> a(n),b;
  for(int i=0;i<n;i++){
    auto &[l,r,k,x]=a[i]; cin>>l>>r>>k,x=i;
  }
  sort(a.begin(),a.end(),[](tpi x,tpi y){
    return get<2>(x)>get<2>(y);
  });
  b=a,sort(b.begin(),b.end(),[](tpi x,tpi y){
    return get<1>(x)-get<0>(x)>get<1>(y)-get<0>(y);
  }); // 两种排序
  tree<pii,null_type,greater<>,rb_tree_tag,tree_order_statistics_node_update> L;
  tree<pii,null_type,less<>,rb_tree_tag,tree_order_statistics_node_update> R;
  vector<int> s(n);
  for(auto [l,r,k,x]:a){
    while(p<n&&get<1>(b[p])-get<0>(b[p])>=k)
      L.insert(make_pair(get<0>(b[p]),p)),R.insert(make_pair(get<1>(b[p]),p)),p++;
    // 加入可能成为答案的元素
    s[x]=L.size()-R.order_of_key(make_pair(l+k,0))-L.order_of_key(make_pair(r-k,n));
    // 使用 order_of_key 查排名，进行统计
  }
  for(int i:s)cout<<i-1<<'\n';
  return 0;
}
```

---

## 作者：EnofTaiPeople (赞：10)

1.9 小时通关金组，你值得拥有！

尝试找出偏序关系。

考虑一个三元组 $(l,r,k)$，区间 $[L,R]$ 对它产生贡献的条件为 $k\le\min\{r,R\}-\max\{l,L\}$，可以拆成以下四种条件：

1. $k\le r-l$（题面给定）；
2. $k\le r-L$，改写成 $L\le r-k$；
3. $k\le R-l$，改写成 $l+k\le R$;
4. $k\le R-L$。

发现这是一个【模板】三维偏序（陌上花开），使用你喜欢的方式维护即可。

我的做法是先按条件 $4$ 排序，然后归并时保证条件 $3$ 的顺序，再将序列提出来分治，归并时保证条件 $2$ 的顺序，同时计算答案，时间复杂度 $O(n\log^2n)$，空间 $O(n)$：
```cpp
#define cmpvv [&](int x,int y){return vv[x]==vv[y]?x<y:vv[x]<vv[y];}
#define cmpv2 [&](int x,int y){return v2[x]==v2[y]?x>y:v2[x]<v2[y];}
int n,K,vv[N],v2[N],p[N];
struct dat{
    int l,r,k;
    void rd(){cin>>l>>r>>k;}
}d[N];
int b1[N],t1,b2[N],t2,b3[N],t3,ans[N];
void cdq3(int l,int r){
    if(l>=r)return;
    int md=l+r>>1,i,p,K;
    cdq3(l,md),cdq3(md+1,r);
    for(i=l,p=md+1,K=0;i<=md;++i){
        while(p<=r&&v2[b3[p]]<=v2[b3[i]])K+=b3[p++]>n;
        if(b3[i]<=n)ans[b3[i]]+=K;
    }
    inplace_merge(b3+l,b3+md+1,b3+r+1,cmpv2);
}
void cdq(int l,int r){
    if(l>=r)return;
    int md=l+r>>1,i;
    cdq(l,md),cdq(md+1,r);
    t1=t2=0;
    for(i=l;i<=md;++i)
        if(p[i]<=n)b1[++t1]=p[i];
    for(i=md+1;i<=r;++i)
        if(p[i]>n)b2[++t2]=p[i];
    if(t1&&t2){
        t3=t1+t2;
        merge(b1+1,b1+t1+1,b2+1,b2+t2+1,b3+1,cmpvv);
        cdq3(1,t3);
    }
    inplace_merge(p+l,p+md+1,p+r+1,cmpvv);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int i,j,k,l,r,x,y,z;
    cin>>n;
    for(x=1;x<=n;++x)d[x].rd();
    for(x=1;x<=n;++x)vv[x]=d[x].k,vv[x+n]=d[x].r-d[x].l;
    for(x=1;x<=n+n;++x)p[x]=x;
    sort(p+1,p+n+n+1,cmpvv);
    for(x=1;x<=n;++x){
        vv[x]=d[x].l+d[x].k,vv[x+n]=d[x].r;
        v2[x]=d[x].r-d[x].k,v2[x+n]=d[x].l;
    }
    cdq(1,n+n);
    for(x=1;x<=n;++x)printf("%d\n",ans[x]-1);
    return 0;
}
```

---

## 作者：Genius_Star (赞：9)

### 思路：

对于 $(l_i,r_i,k_i)$，有 $(l_j,r_j)$ 满足条件当且仅当：

$$k_i \le \min(r_i,r_j)-\max(l_i,l_j)$$

相当于满足：

$$\begin{cases} k_i\le r_i-l_j \\ k_i \le r_j-l_i \\ k_i \le r_j-l_j\end{cases}$$

可以转化为：

$$\begin{cases} l_j \le r_i-k_i \\ r_j \ge l_i + k_i \\ r_j-l_j \ge  k_i \end{cases}$$

那么初始可以先按照 $k_i$ 从大到小排序，然后再复制一份按照 $r_j-l_j$ 从大到小排序，此时在复制的数组上走指针即可，每次将满足 $r_j-l_j \ge k_i$ 的加入集合。

此时我们要在集合中找满足 $r_j \ge l_i+k$ 且 $l_j \le r_i-k$ 的数量，是一个二维数点问题，可以使用树状数组套动态开点解决。

即维护前缀 $[1,x]$ 范围内 $l_j$ 的线段树，发现可以差分一下，就相当于 $[1,n] - [1,r_j-1]$ 的答案。

时空复杂度均为 $O(N \log^2 N)$。

这样我们会得到一大串的 MLE，于是考虑使用 cdq 分治算法。

但是现在我们发现条件好像无法直接维护，考虑新建 $n$ 个虚点，其 $k$ 的值为 $r_j-l_j$，此时按照 $k$ 的值从小到大进行排序即可。

此时我们要求的是右区间对左区间的贡献，考虑左区间按照 $l_i+k$ 从大到小排序，右区间按照 $r_j$ 从大到小排序，每次走指针时将满足条件的虚点的 $l_j$ 加入树状数组，最后对于每一个实点，求出 $[1,r_i-k]$ 内的点的数量即可。

时间复杂度为 $O(N \log^2 N)$，空间复杂度为 $O(N)$。

**注意离散化；且当 $k$ 相同时，应当编号较小的放到前面。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define lowbit(x) x&(-x)
using namespace std;
typedef double db;
const int N=400400;
inline int read(){
    register int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(register int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
int n,cnt;
int s[N],ans[N];
struct Node{
	int l,r;
	int k;
	int len;
	int id;
	int x,y;
}a[N];
class Tree{
public:
	int a[N];
	void add(int x){
		for(int i=x;i<=cnt;i+=lowbit(i))
		  a[i]++;
	}
	int qurey(int x){
		int ans=0;
		for(int i=x;i;i-=lowbit(i))
		  ans+=a[i];
		return ans;
	}
	void del(int x){
		for(int i=x;i<=cnt;i+=lowbit(i))
		  a[i]=0;
	}
}T;
bool cmp1(Node a,Node b){
	if(a.k==b.k)
	  return a.id<b.id;
	return a.k<b.k;
}
bool cmp2(Node a,Node b){
	if(a.x==b.x)
	  return a.id<b.id;
	return a.x>b.x;
}
bool cmp3(Node a,Node b){
	if(a.r==b.r)
	  return a.id<b.id;
	return a.r>b.r;
}
void cdq(int l,int r){
	if(l==r)
	  return ;
	int mid=(l+r)>>1;
	cdq(l,mid),cdq(mid+1,r);
	sort(a+l,a+mid+1,cmp2);
	sort(a+mid+1,a+r+1,cmp3);
	int i=l,j=mid+1;
	for(;i<=mid;i++){
		while(a[j].r>=a[i].x&&j<=r){
			if(a[j].id>n)
			  T.add(a[j].l);
			j++;
		}
		if(a[i].id<=n)
		  ans[a[i].id]+=T.qurey(a[i].y);
	}
	for(int i=mid+1;i<j;i++)
	  if(a[i].id>n)
	    T.del(a[i].l);
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]={read(),read(),read(),0,i};
		a[i].len=a[i].r-a[i].l;
		a[i].x=a[i].l+a[i].k;
		a[i].y=a[i].r-a[i].k;
		s[++cnt]=a[i].l;
		s[++cnt]=a[i].y;
	}
	sort(s+1,s+cnt+1);
	cnt=unique(s+1,s+cnt+1)-(s+1);
	for(int i=1;i<=n;i++){
		a[i].l=lower_bound(s+1,s+cnt+1,a[i].l)-s;
		a[i].y=lower_bound(s+1,s+cnt+1,a[i].y)-s;
		a[n+i]=a[i];
		a[n+i].k=a[i].len;
		a[n+i].id+=n;
	}
	sort(a+1,a+n+n+1,cmp1);
//	for(int i=1;i<=2*n;i++){
//		cerr<<a[i].l<<' '<<a[i].r<<' '<<a[i].k<<' '<<a[i].id<<'\n';
//	}
	cdq(1,2*n);
	for(int i=1;i<=n;i++){
		write(ans[i]-1);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：RDFZchenyy (赞：5)

| 时间限制 | 空间限制 | 链接 |
| :----------: | :----------: | :----------: |
| 2.00s | 256.00MB | [link](https://www.luogu.com.cn/problem/P10281) |

**【声明】**

由于不够完善的 Katex，本文中的所有几何图像均在 [Geogebra](https://geogebra.org/) 上完成制作。

本题解对应的 Classroom 代码：[AQEA XW23](https://www.geogebra.org/classroom/aqeaxw23)。

**【题意简述】**

我们在数轴上有 $n$ 条线段，每条线段有三个参数 $l_i,r_i,k_i$，表示这是一条从 $l_i$ 到 $r_i$ 的线段。对于每条线段 $i$，请求出与其重叠部分长度大于等于 $k_i$ 的线段条数。

数据范围：$1\le n\le 2\times 10^5,1\le l_i<r_i\le 10^9,1\le k_i\le r_i-l_i$。

**【做法分析】**

由于二维平面的优越性，我们规定一个区间 $[l_i,r_i]$ 对应点 $(l_i,r_i)$。

我们先考虑一个区间可以落在怎样的位置上：

+ 区间对应的点必然落在主对角线以上，这是因为 $l<r$。
+ 区间对应的点必定落在左端点边界及右端点边界的右下方，这是因为 $l,r\le 10^9$，图例中 $10^9$ 被缩小为 $10$。

让我们不妨考虑能符合 $(l_i,r_i,k_i)$ 这一线段条件的区域。请观察 Geogebra 上给出的图示，我们可以发现符合条件的区域大致可以分为四个部分：

+ 区域 A：在这个区域内的线段完全覆盖线段 $i$，必然符合。
+ 区域 B：在这个区域内的线段的左端点最右在线段 $i$ 右端点左侧 $k_i$ 的位置，符合。
+ 区域 C：在这个区域内的线段的右端点最左在线段 $i$ 左端点右侧 $k_i$ 的位置，符合。
+ 区域 D：在这个区域内的线段的长度至少为 $k_i$，且被线段 $i$ 完全覆盖，符合。

![图例](https://cdn.luogu.com.cn/upload/image_hosting/jre3hqte.png)

这些直线分别是 $x=l_i,y=r_i,x=l_i+k,y=r_i-k,y=x+k_i$，你可以在 Classroom 中拖动滑动条来测试。如图是 $(2,8,2)$ 所对应的区域。

接着，请考虑如何查询对应的点的数量。直接求出是不易的，我们注意到可以用整体减空白。换而言之，用“分界线3”、“左端点边界”和“右端点边界”围成的三角形中点的个数减去右上角及左下角剩下的两块中点的个数。

我们考虑维护每一条与主对角线平行的直线上的点的个数，这样“整体”的点的个数是容易用数据结构求出的。接着我们考虑如何求出“空白”的点的个数，以下面空白三角为例，我们按照 $(l_i+k_i)$ 从小到大处理每个询问，然后按 $r_i$ 从小到大把 $(l_i,r_i)$ 加入数据结构，然后用相同于“整体”的方式求出即可。

数据结构可以选取动态开点线段树，也可以使用树状数组。我们在这里选取树状数组，但其需要解决值域不够存的问题。

提供一个小 Trick：我们用 `unordered_map` 存储树状数组，这可以节省空间。

这个做法的时间复杂度和空间复杂度均是 $O(nw)$，其中 $w=30$，是值域的对数。

然而 `unordered_map` 具有非常差的常数，这导致时间复杂度正确的算法无法通过。我们在做这个问题时的空间略有结余，此处可以再使用一个 Trick：我们在 `unordered_map` 初始化后规定一个参数 `ump.max_load_factor`。这个参数越小，就会使用越多的空间换取越优的时间。我的代码中取到了 $0.3$，可以通过本题。

**【代码示例】**

对于树状数组实现：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAXN 200005 

struct BT{
	const int sz=1000000001;
	unordered_map<int,int> t;
	int sum;
	BT(){
		sum=0;
		t.max_load_factor(0.3);
	}
	void clear(){
	    t.clear(); sum=0;
		t.max_load_factor(0.3);
	}
	static int lowbit(int x){
		return x&(-x);
	}
	void add(int pos,int x){
		sum+=x;
		while(pos<=sz){
			t[pos]+=x;
			pos+=lowbit(pos);
		}
		return;
	}
	inline int query(int pos){
		int ret=0;
		while(pos){
			ret+=t[pos];
			pos-=lowbit(pos);
		}
		return ret;
	}
	inline int rquery(int pos){
		return sum-query(pos-1);
	}
}t1;

int n;
struct Query{
	int l,r,k;
};
Query q[MAXN];

int ans[MAXN];
int prk[MAXN],qrk[MAXN];

bool cmpr(int a,int b){
	return q[a].r<q[b].r;
}
bool cmplk(int a,int b){
	return q[a].l+q[a].k<q[b].l+q[b].k;
}
bool cmpl(int a,int b){
	return q[a].l>q[b].l;
}
bool cmprk(int a,int b){
	return q[a].r-q[a].k>q[b].r-q[b].k;
}

int main(){
	ios::sync_with_stdio(false);
	
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>q[i].l>>q[i].r>>q[i].k;
	}
	for(int i=1;i<=n;i++){
		prk[i]=qrk[i]=i;
	}
	
	sort(prk+1,prk+n+1,cmpr);
	sort(qrk+1,qrk+n+1,cmplk);
	int p=1;
	for(int i=1;i<=n;i++){
		while(p<=n){
			if(q[prk[p]].r>=q[qrk[i]].l+q[qrk[i]].k){
				break;
			}
			t1.add(q[prk[p]].r-q[prk[p]].l,1);
			p++;
		}
		ans[qrk[i]]-=t1.rquery(q[qrk[i]].k);
	}
	while(p<=n){
		t1.add(q[prk[p]].r-q[prk[p]].l,1);
		p++;
	}
	for(int i=1;i<=n;i++){
		ans[i]+=t1.rquery(q[i].k);
	}
	
	sort(prk+1,prk+n+1,cmpl);
	sort(qrk+1,qrk+n+1,cmprk);
	p=1;
	t1.clear();
	for(int i=1;i<=n;i++){
		while(p<=n){
			if(q[prk[p]].l<=q[qrk[i]].r-q[qrk[i]].k){
				break;
			}
			t1.add(q[prk[p]].r-q[prk[p]].l,1);
			p++;
		}
		ans[qrk[i]]-=t1.rquery(q[qrk[i]].k);
	}	
	
	for(int i=1;i<=n;i++){
		cout<<ans[i]-1<<endl;	
	}
	
	return 0;
}
```

对于动态开点线段树，可以参考 @[oyzr](https://www.luogu.com.cn/user/573215) 和 @[oyzr2238](https://www.luogu.com.cn/user/112155) 两位同学（注意，确实是两位同学）的代码，他们的提交记录如下：

+ <https://www.luogu.com.cn/record/152857551>
+ <https://www.luogu.com.cn/record/152857974>

---

## 作者：xyvsvg (赞：4)

提供一种单 $\log$ 做法。

对于考虑对于一个 $(l_i,\ r_i)$，什么样的 $(l_j,\ r_j)$ 会对他造成贡献？分讨一下：
$$case\ 1:l_j<l_i\ \wedge\ r_j\geq l_i+k_i$$

$$case\ 2:l_i\leq l_j\leq r_i-k_i\ \wedge\ r_j-l_j\geq k_i$$

分开考虑两种情况的贡献。对于第一种，我们将所有区间按左端点排序，不断将右端点加入树状数组，直接查询即可。对于第二种，我们可以将所有区间按 $r_i-l_i$ 降序排序，将所有询问按 $k_i$ 降序排序，放在同一个数组，这样便保证了对于一个询问，当前维护的区间长度都大于等于 $k_i$，于是我们将遇到区间时，将其右端点放入树状数组，遇到询问时，直接查询即可。

由于值域较大，需要离散化。由于区间自身会被统计，所以答案需要减一。

复杂度为 $O(n\log n)$，代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
typedef array<int,3> A;
typedef array<int,4> A4;
struct Fenwick
{
    int n;
    vector<int>bit;
    Fenwick(int n_)
    {
        n=n_;
        bit.resize(n+10);
    }
    void add(int i,int x)
    {
        for(;i<=n;bit[i]+=x,i+=i&-i);
    }
    int sum(int i)
    {
        int ret=0;
        for(;i;ret+=bit[i],i&=i-1);
        return ret;
    }
    int sum(int l,int r)
    {
        return sum(r)-sum(l-1);
    }
};
signed main()
{
    int n;
    cin>>n;
    vector<int>disc;
    vector<A>a(n);
    vector<int>ans(n);
    vector<P>b;
    for(auto&[x,y,k]:a)
    {
        cin>>x>>y>>k;
        disc.push_back(x);
        disc.push_back(y);
        disc.push_back(y-k);
        disc.push_back(x+k);
        b.push_back({x,y});
    }
    sort(b.begin(),b.end());
    sort(disc.begin(),disc.end());
    disc.erase(unique(disc.begin(),disc.end()),disc.end());
    auto rnk=[&](int x)
    {
        return upper_bound(disc.begin(),disc.end(),x)-disc.begin();
    };
    int m=disc.size();
    /*LS*/
    {
        Fenwick bit(m);
        vector<int>p(n);
        iota(p.begin(),p.end(),0);
        sort(p.begin(),p.end(),[&](int i,int j)
             {
                 return a[i]<a[j];
             });
        int j=0;
        for(int i:p)
        {
            auto[l,r,k]=a[i];
//            cout<<l<<' '<<r<<' '<<k<<endl;
            while(j<n&&b[j].first<l)
                bit.add(rnk(b[j++].second),1);
            ans[i]=bit.sum(rnk(l+k),m);
        }
    }
    // SEC
    {
        Fenwick bit(m);
        vector<A4>qs;
        for(int i=0;i<n;++i)
        {
            auto[l,r,k]=a[i];
            qs.push_back({i,l,r-k,k});
            qs.push_back({-1,l,-1,r-l});
        }
        sort(qs.begin(),qs.end(),[&](const A4&x,const A4&y)
             {
                 return x[3]>y[3]||x[3]==y[3]&&x[0]<y[0];
             });
        for(auto[i,x,y,d]:qs)
        {
//            cout<<i<<' '<<x<<' '<<y<<' '<<d<<endl;
            if(~i)
                ans[i]+=bit.sum(rnk(x),rnk(y));
            else
                bit.add(rnk(x),1);
        }
    }
    for(int x:ans)
        cout<<x-1<<endl;
    return 0;
}

```

---

## 作者：Claire0918 (赞：3)

对于 $[l_i, r_i]$，能够使得 $[l_j, r_j]$ 与其重叠至少 $k_i$ 的充分必要条件是
$$
\begin{cases}
r_j - l_j \geq k & A\\
l_j \leq r_i - k & B\\
r_j \geq l_i + k & C\\
\end{cases}
$$
可以直接使用三维偏序，时间复杂度 $\mathcal{O}(n \log^2n)$。此处有一种更优的做法。

我们化简答案的式子
$$
\begin{aligned}
res_i &= \sum_{j \neq i} [A \wedge B \wedge C]\\
&= \sum_{j \neq i} [A] - \sum_{j \neq i} [A \wedge \neg(B \wedge C)]\\
&= \sum_{j \neq i} [A] - \sum_{j \neq i} [A \wedge (\neg B \vee \neg C)]\\
\end{aligned}
$$
注意到 $\neg B$ 是 $l_j > r_i - k$，$\neg C$ 是 $r_j < l_i + k$。如果 $\neg B$ 和 $\neg C$ 同时成立，那么将两式相加即可得到 $r_i - l_i + r_j - l_j < 2k$。题目保证了 $r_i - l_i \geq k$，$A$ 要求 $r_j - l_j \geq k$，从而 $r_i - l_i + r_j - l_j \geq 2k$，这与 $\neg B$ 和 $\neg C$ 同时成立矛盾，所以当 $[A] = 1$ 时，$[\neg B \wedge \neg C] = 0$。

从而
$$
\begin{aligned}
res_i
&= \sum_{j \neq i} [A] - \sum_{j \neq i} [A \wedge (\neg B \vee \neg C)]\\
&= \sum_{j \neq i} [A] - \sum_{j \neq i} [A \wedge \neg B] - \sum_{j \neq i} [A \wedge \neg C] + \sum_{j \neq i} [A \wedge (\neg B \wedge \neg C)]\\
&= \sum_{j \neq i} [A] - \sum_{j \neq i} [A \wedge \neg B] - \sum_{j \neq i} [A \wedge \neg C]\\
\end{aligned}
$$
分别对 $A \wedge \neg B$ 和 $A \wedge \neg C$ 做二维偏序即可。排序维护 $A$。维护 $B$ 和 $C$ 需要支持插入和查询排名的数据结构，离散化后使用普通线段树即可。时间复杂度 $\mathcal{O}(n \log n)$。

实现时注意条件中的不等号是否能取等。注意 $j \neq i$，所以 $i$ 不能计入答案。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 2e5 + 10;

struct seg{
    int l, r, k, idx;
} a[maxn], b[maxn];

struct{
    struct{
        int l, r, val;
    } tree[maxn << 3];

    inline void build(int index, int l, int r){
        tree[index].l = l, tree[index].r = r;
        if (l == r){
            return;
        }
        const int mid = l + r >> 1;
        build(index << 1, l, mid), build(index << 1 | 1, mid + 1, r);
    }

    inline void modify(int index, int x){
        tree[index].val++;
        if (tree[index].l == tree[index].r){
            return;
        }
        const int mid = tree[index].l + tree[index].r >> 1;
        modify(index << 1 | (x > mid), x);
    }

    inline int query(int index, int l, int r){
        if (l <= tree[index].l && r >= tree[index].r){
            return tree[index].val;
        }
        const int mid = tree[index].l + tree[index].r >> 1;
        int res = 0;
        if (l <= mid){
            res += query(index << 1, l, r);
        }
        if (r > mid){
            res += query(index << 1 | 1, l, r);
        }
        return res;
    }
} L, R;

int n;
vector<int> temp;
int res[maxn];

inline int find(int x){
    return lower_bound(temp.begin(), temp.end(), x) - temp.begin() + 1;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d %d %d", &a[i].l, &a[i].r, &a[i].k), a[i].idx = i, b[i] = a[i];
        temp.push_back(a[i].l), temp.push_back(a[i].r);
    }
    sort(temp.begin(), temp.end()), temp.erase(unique(temp.begin(), temp.end()), temp.end());
    sort(a + 1, a + n + 1, [](seg x, seg y){return x.k > y.k;});
    sort(b + 1, b + n + 1, [](seg x, seg y){return x.r - x.l > y.r - y.l;});
    L.build(1, 1, n << 1), R.build(1, 1, n << 1);
    for (int i = 1, p = 1; i <= n; i++){
        const int l = a[i].l, r = a[i].r, k = a[i].k;
        while (p <= n && b[p].r - b[p].l >= k){
            L.modify(1, find(b[p].l)), R.modify(1, find(b[p].r)), p++;
        }
        res[a[i].idx] = (p - 1) - L.query(1, find(r - k + 1), n << 1) - R.query(1, 1, find(l + k) - 1) - 1;
    }
    for (int i = 1; i <= n; i++){
        printf("%d\n", res[i]);
    }

return 0;
}
```

---

我们注意到除了上文提及的条件，如果满足下列二条件之一，也有 $|[l_i, r_i] \cap [l_j, r_j]| \geq k_i$ 
$$
A: r_j \geq r_i, l_j \leq r_i - k_i\\
B: l_i + k_i \leq r_j < r_i, r_j - l_j \geq k_i\\
$$
并且因为 $A$ 要求 $r_j \geq r_i$，$B$ 要求 $r_j < r_i$，所以 $[A \wedge B] = 0$。

从而答案
$$
\begin{aligned}
res_i &= \sum_{j \neq i} [A \vee B]\\
&= \sum_{j \neq i} [A] + \sum_{j \neq i} [B] - \sum_{j \neq i} [A \wedge B]\\
&= \sum_{j \neq i} [A] + \sum_{j \neq i} [B]
\end{aligned}
$$
分别维护两个二维偏序即可，时间复杂度 $\mathcal{O}(n\log n)$。因为比第一种做法少一棵线段树，所以常数略优。

注意到第一种做法的式子化简需要所求的值具有可差分性，但是如果需要维护不具有可差分性的值（如给 $[l_i, r_i]$ 赋权，求所有满足 $|[l_i, r_i] \cap [l_j, r_j]| \geq k_i$ 的 $[l_j, r_j]$ 权值最大值，即 [NOIP2024](https://www.luogu.com.cn/problem/P11364)），那么就不再能使用第一种做法，而必须使用第二种做法。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 2e5 + 10;

struct seg{
    int l, r, k, idx;
} a[maxn], b[maxn];

namespace segtree{
    int tree[maxn << 3];
    inline void modify(int index, int L, int R, int x){
        tree[index]++;
        if (L == R){
            return;
        }
        const int mid = L + R >> 1;
        if (x <= mid){
            modify(index << 1, L, mid, x);
        }else{
            modify(index << 1 | 1, mid + 1, R, x);
        }
    }
    inline int query(int index, int L, int R, int l, int r){
        if (l <=L && r >= R){
            return tree[index];
        }
        const int mid = L + R >> 1;
        int res = 0;
        if (l <= mid){
            res += query(index << 1, L, mid, l, r);
        }
        if (r > mid){
            res += query(index << 1 | 1, mid + 1, R, l, r);
        }
        return res;
    }
};

int n;
vector<int> temp;
int res[maxn];

inline int find(int x){
    return lower_bound(temp.begin(), temp.end(), x) - temp.begin() + 1;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d %d %d", &a[i].l, &a[i].r, &a[i].k), a[i].idx = i, b[i] = a[i];
        temp.push_back(a[i].l), temp.push_back(a[i].r);
    }
    sort(temp.begin(), temp.end()), temp.erase(unique(temp.begin(), temp.end()), temp.end());
    sort(a + 1, a + n + 1, [](seg x, seg y){return x.r - x.k < y.r - y.k;});
    sort(b + 1, b + n + 1, [](seg x, seg y){return x.l < y.l;});
    for (int i = 1, p = 1; i <= n; i++){
        const int l = a[i].l, r = a[i].r, k = a[i].k;
        while (p <= n && b[p].l <= r - k){
            segtree::modify(1, 1, n << 1, find(b[p].r)), p++;
        }
        res[a[i].idx] = segtree::query(1, 1, n << 1, find(r), n << 1);
    }
    mem(segtree::tree, 0);
    sort(a + 1, a + n + 1, [](seg x, seg y){return x.k > y.k;});
    sort(b + 1, b + n + 1, [](seg x, seg y){return x.r - x.l > y.r - y.l;});
    for (int i = 1, p = 1; i <= n; i++){
        const int l = a[i].l, r = a[i].r, k = a[i].k;
        while (p <= n && b[p].r - b[p].l >= k){
            segtree::modify(1, 1, n << 1, find(b[p].r)), p++;
        }
        res[a[i].idx] += segtree::query(1, 1, n << 1, find(l + k), find(r) - 1);
    }
    for (int i = 1; i <= n; i++){
        printf("%d\n", res[i] - 1);
    }

return 0;
}
```

---

## 作者：qwer6 (赞：2)

## 1.25Pts

暴力判断两个区间是否符合条件即可。

```c++
for(int i=1,res;i<=n;i++){
    res=0;
    for(int j=1;j<=n;j++){
        if(i==j)continue;
        if(cal(i,j)>=a[i].k)res++;
    }
    write(res),Nxt;
}	
```

## 2.55Pts

我们考虑当所有 $k$ 相等的时候怎么做。

我们知道求交集之长就是最小的右端点减去最大的左端点，因此我们考虑当 $(i,j)$ 为一对合法区间时，必然满足：$\min(r_i,r_j)-\max(l_i,l_j)\ge k$。

所以我们可以得到四条不等式：
$$
r_i-l_i\ge k\\
r_i-l_j\ge k\\
r_j-l_i\ge k\\
r_j-l_j\ge k\\
$$
而又因为所有的 $r_i-l_i \ge k$，所以我们可以认为第一条不等式和第四条不等式一定成立，那么我们只需要考虑二，三两条不等式即可。

我们对两条不等式做一次移项：
$$
r_i-k\ge l_j\\
l_i+k\le r_j
$$
也就说，我们建立一个虚点 $x_i=(r_i-k,l_i+k)$，我们只需要找到有多少个区间满足 $l_j$ 大于 $x_i$ 的左端点，$r_j$ 小于 $x_i$ 的左端点，就是 $i$ 这个区间的答案。

这很显然是一个二维数点问题，使用树状数组解决即可。

不过注意最后答案要减一，因为 $(i,i)$ 也会被记为一对合法区间，其实上是不合法的。

```c++
namespace Pts30{
	const int M=4e5+5;
	int totl,tot;
	int l[N],r[N],k[N],ans[N],tmpl[M];
	struct Node{
		int l,r,id,tp;
		bool operator <(const Node &a)const{
			if(r!=a.r)return r<a.r;
			return id<a.id;
		}
		bool operator >(const Node &a)const{
			if(r!=a.r)return r>a.r;
			return id<a.id;
		}
	}q[M];
	struct Bitnary_tree{
		int a[M];
		inline int lowbit(int x){
			return x&-x;
		}
		void add(int x,int v){
			for(int i=x;i<=totl;i+=lowbit(i))a[i]+=v;
		}
		int query(int x){
			int res=0;
			for(int i=x;i;i-=lowbit(i))res+=a[i];
			return res;
		}
		int query(int l,int r){
			return query(r)-query(l-1);
		}
	}bit;
	void main(){
		for(int i=1;i<=n;i++){
			read(l[i]),read(r[i]),read(k[i]);
			q[++tot]={l[i],r[i],0,0};
			q[++tot]={r[i]-k[i],l[i]+k[i],i,1};
		}
		sort(q+1,q+tot+1,greater<Node>());
		for(int i=1;i<=tot;i++)tmpl[i]=q[i].l;
		sort(tmpl+1,tmpl+tot+1);
		totl=unique(tmpl+1,tmpl+tot+1)-tmpl-1;
		for(int i=1;i<=tot;i++)q[i].l=lower_bound(tmpl+1,tmpl+totl+1,q[i].l)-tmpl;
		for(int i=1;i<=tot;i++){
			if(!q[i].id)bit.add(q[i].l,1);
			else ans[q[i].id]+=bit.query(q[i].l);
		}
		for(int i=1;i<=n;i++)write(ans[i]-1),Nxt;	
	}
}
```

## 3.100Pts

这个时候我们上面说到的四条不等式中：
$$
r_i-l_i\ge k\\
r_i-l_j\ge k\\
r_j-l_i\ge k\\
r_j-l_j\ge k\\
$$
第一条仍然恒成立，但是第四条变成了不一定成立的条件，怎么办呢？

我们考虑将这个问题转换成三维偏序问题，假设点 $x=(l_i,r_i,k_i)$，很显然，当我们将所有点按 $k$ 从大到小排序之后，第四条不等式又变成了恒成立的条件，所以我们就可以使用 CDQ 分治解决这个三维偏序问题。

建议先写：[三维偏序模板](https://www.luogu.com.cn/problem/P3810)。

我们就可以写出正解代码了。

```c++
#include<bits/stdc++.h>
#define Nxt puts("")
#define Spa putchar(32)
namespace FastIO{
	inline void read(int &a){
		char c=getchar();
		int f=1;
		a=0;
		while(!isdigit(c)){
			if(c=='-')f=-1;
			c=getchar();
		}
		while(isdigit(c)){
			a=(a<<1)+(a<<3)+(c^48);
			c=getchar();
		}
		a*=f;
		return ;
	}
	inline void write(int x){
		if(x<0)putchar('-'),x=-x;
		int a[20];
		a[0]=0;
		do{
		   a[++a[0]]=x%10;
		   x/=10;
		}while(x);
		for(int i=a[0];i;i--)putchar(a[i]+'0');
		return ;
	}
	inline bool tomax(int &a,int b){
		if(a<b){
			a=b;
			return true;
		}
		return false;
	}
	inline bool tomin(int &a,int b){
		if(a>b){
			a=b;
			return true;
		}
		return false;
	}
}
using namespace FastIO;
using namespace std;
const int N=2e5+5,M=4e5+5;
int n,tot,cntl;
int l[N],r[N],k[N],tmp[M],ans[N];
struct Bitnary_tree{
	int a[M],t[M],T=-1;
	inline int lowbit(int x){
		return x&-x;
	}
	void clear(){
		T++;
	}
	void add(int x,int v){
		for(int i=x;i<=cntl;i+=lowbit(i)){
			if(tomax(t[i],T))a[i]=v;
			else a[i]+=v;
		}
	}
	int query(int x){
		int res=0;
		for(int i=x;i;i-=lowbit(i))
			if(t[i]==T)
				res+=a[i];
		return res;
	}
	int query(int l,int r){
		return query(r)-query(l-1);
	}
}bit;
struct Node{
	int l,r,k,id;
	bool operator <(const Node &a)const{
		if(k!=a.k)return k>a.k;
		return id<a.id;
	}
	bool operator >=(const Node &a)const{
		return r>=a.r;
	}
}q[M],c[M];
void CDQ(int l,int r){
	if(l==r)return ;
	int mid=l+r>>1;
	CDQ(l,mid),CDQ(mid+1,r);
	bit.clear();
	for(int i=l,L=l,R=mid+1;i<=r;i++){
		if(R>r||(L<=mid&&q[L]>=q[R])){
			c[i]=q[L++];
			if(!c[i].id)bit.add(c[i].l,1);
		}else{
			c[i]=q[R++];
			if(c[i].id)ans[c[i].id]+=bit.query(c[i].l);
		}
	}
	for(int i=l;i<=r;i++)q[i]=c[i];
	return ;
}
signed main(){
	read(n);
	for(int i=1;i<=n;i++){
		read(l[i]),read(r[i]),read(k[i]);
		q[++tot]={l[i],r[i],r[i]-l[i],0};
		q[++tot]={r[i]-k[i],l[i]+k[i],k[i],i};
		tmp[++cntl]=l[i];
		tmp[++cntl]=r[i]-k[i];
	}
	sort(q+1,q+tot+1);
	sort(tmp+1,tmp+cntl+1);
	cntl=unique(tmp+1,tmp+cntl+1)-tmp-1;
	for(int i=1;i<=tot;i++)q[i].l=lower_bound(tmp+1,tmp+cntl+1,q[i].l)-tmp;
	CDQ(1,tot); 	
	for(int i=1;i<=n;i++)write(ans[i]-1),Nxt;
}
```

---

## 作者：huhangqi (赞：1)

## 15pts ##

判断样例即可。

## 25pts ##

$O(n^2)$ 的暴力枚举即可。

## 55pts ##

满足条件为 $\min(r_i,r_j)-\max(l_i,l_j) \ge k_i$ 时，第 $i$ 个可获得一个品种。

由于被减数取最小值，减数取最大值，那么就必定成立。

+ $r_i-l_i \ge k_i$（已知条件）

+ $r_j-l_j \ge k_i$

+ $r_i-l_j \ge k_i$

+ $r_j-l_i \ge k_i$

在所有的 $k_i$ 均相等时，第二条式子也是必定成立的。

此时这个问题就是一个二维偏序问题了。

那么就可以直接使用树状数组或者归并排序求出，即可解决这一性质的部分。

与前一部分的 $O(n^2)$ 放在一起即可。

代码:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+5;
int n,l[N],r[N],k[N],ans[N],tmp[N*2],cnt;
void solve1(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			if(min(r[i],r[j])-max(l[i],l[j])>=k[i])ans[i]++;
		}
	}
}
int lowbit(int x){
	return x&-x;
}
struct BT{
	int c[N];
	void init(){
		memset(c,0,sizeof(c));
	}
	void add(int x,int y){
		for(int i=x;i<=cnt;i+=lowbit(i))c[i]+=y;
	}
	int query(int x){
		int ans=0;
		for(int i=x;i>=1;i-=lowbit(i))ans+=c[i];
		return ans;
	}
}bit;
struct P{
	int l,r,id;
}a[N];
bool cmp(P a,P b){
	if(a.r==b.r)return a.id>b.id;
	return a.r>b.r;
}
void solve2(){
	for(int i=1;i<=n;i++){
		a[++cnt]={r[i]-k[i],l[i]+k[i],i};
		a[++cnt]={l[i],r[i],n+i};
	}
	sort(a+1,a+2*n+1,cmp);
	for(int i=1;i<=2*n;i++)tmp[++cnt]=a[i].l;
	sort(tmp+1,tmp+cnt+1);
	cnt=unique(tmp+1,tmp+cnt+1)-tmp-1;
	for(int i=1;i<=2*n;i++)a[i].l=lower_bound(tmp+1,tmp+cnt+1,a[i].l)-tmp;
	for(int i=1;i<=2*n;i++){
		if(a[i].id>n)bit.add(a[i].l,1);
		else ans[a[i].id]+=bit.query(a[i].l);
	}
	for(int i=1;i<=n;i++)ans[i]--;
}
signed main(){
	cin>>n;
	cnt=0;
	for(int i=1;i<=n;i++){
		cin>>l[i]>>r[i]>>k[i];
	}
	if(n<=5000){
		solve1();
	}
	else {
		solve2();
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<endl;
	return 0;
}
``````

## 100pts ##
根据上一步分析，多出了一个 $r_j-l_j \ge k_i$，那么就可以直接考虑使用三维偏序。

做三维偏序时，通常使用 CDQ 分治算法。

相较于常规的二维偏序而言，CDQ 分治算法解决三维偏序相当于可以通过树状数组在归并排序中得到每一个点的取值。

我们在存储时建立一组作为被相交形成答案的线段，一组作为查询答案的线段。

在存储结构体时直接将两部分对应的值加入到结构体的对应位置，这样就可以快速地排序处理了。

在清理树状数组时，由于范围较大，直接清空可能会超时，除了使用时间戳优化还可以直接进行逆操作，将之前添加的值删除以此完成清空。

具体细节看又香又短的代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+5;
int n,tmp[N],ans[N],cnt;
struct P{
	int l,r,k,id;
}a[N],b[N];
bool cmp(P a,P b){
	if(a.k==b.k)return a.id<b.id;
	return a.k>b.k;
}
int lowbit(int x){
	return x&-x;
}
struct BT{
	int c[N];
	void init(){
		memset(c,0,sizeof(c));
	}
	void add(int x,int y){
		for(int i=x;i<=cnt;i+=lowbit(i))c[i]+=y;
	}
	int query(int x){
		int ans=0;
		for(int i=x;i>=1;i-=lowbit(i))ans+=c[i];
		return ans;
	}
}bit;
void CDQ(int l,int r){
	if(l==r)return ;
	int mid=(l+r)/2;
	CDQ(l,mid);
	CDQ(mid+1,r);
	int L=l,R=mid+1;
	for(int i=l;i<=r;i++){
		if(R>r||L<=mid&&a[L].r>=a[R].r){
			b[i]=a[L];
			if(!a[L].id)bit.add(a[L].l,1);
			L++;
		}
		else {
			b[i]=a[R];
			if(a[R].id)ans[a[R].id]+=bit.query(a[R].l);
			R++;
		}
	}
	for(int i=l;i<=mid;i++)if(!a[i].id)bit.add(a[i].l,-1);
	for(int i=l;i<=r;i++)a[i]=b[i];
}
signed main(){
	cin>>n;
	for(int i=1,l,r,k;i<=n;i++){
		cin>>l>>r>>k;
		a[i]={r-k,l+k,k,i};
		a[n+i]={l,r,r-l,0};
	}
	for(int i=1;i<=2*n;i++)tmp[i]=a[i].l;
	sort(tmp+1,tmp+2*n+1);
	cnt=unique(tmp+1,tmp+2*n+1)-tmp-1;
	for(int i=1;i<=2*n;i++)a[i].l=lower_bound(tmp+1,tmp+cnt+1,a[i].l)-tmp;
	sort(a+1,a+2*n+1,cmp);
	CDQ(1,2*n);
	for(int i=1;i<=n;i++)cout<<ans[i]-1<<endl;
	return 0;
}
``````

---

## 作者：Soh_paramEEMS (赞：0)

## 题意
Bessie 正在数轴的正半轴上种一些草。她有 $n$ 个不同的栽培品种，并将把第 $i$ 个品种种植在区间 $[l_i,r_i]$ 内。

此外，品种 $i$ 会在存在另外某个品种 $j$，使得品种 $j$ 与品种 $i$ 重叠至少 $k_i$ 长度时生长得更好。Bessie 想要评估她所有的品种。对于每一个 $i$，计算 $j\neq i$ 的数量，使得 $j$ 与 $i$ 重叠至少 $k_i$ 长度。

$2\le n\le 2\times 10^5$，$0<l_i<r_i\le 10^9$，$0<k_i\le r_i-l_i$。
## 思路
条件形式化表达就是存在 $j$，$\min(r_i,r_j)-\max(l_i,l_j)\ge k_i$。

我们拆开 $\max$ 和 $\min$，然后移项，就是全部满足：
$$\left\{\begin{matrix}
r_j-l_j\ge k_i\\ 
r_j\ge l_i+k_i\\ 
l_j\le r_i-k_i
\end{matrix}\right.$$

这是一个三维偏序，我们整一个三元组 $(l,r,k)$，根据上面的不等式组，每个条件都可以整出两个三元组分别作为**条件和询问**（询问有多少满足不等式组的答案）。三元组的含义可以理解为合法左端点、合法右端点、合法长度。
$$\left\{\begin{matrix}
k_j\ge k_i\\ 
r_j\ge r_i\\ 
l_j\le l_i
\end{matrix}\right.$$

我们依然考虑左区间部分 $p$ 对右区间 $q$ 的贡献：我们对 $k$ 关键字排序搞定第一维，从大到小排序（$k_p\le k_q$）。然后按照剩下两个偏序关系，维护 $q$ 的贡献、维护树状数组、查询 $q$ 的总贡献就好了。对于 $r_p\le r_q$，看到第三维的条件，如果是“条件”我们才把 $l_p$ 扔上树状数组；否则计算 $q$ 的总贡献，查询小于等于 $l_q$ 的有多少满足前两维，是“查询”才添加对应下标的贡献。

因为“条件”本身肯定能满足对应的询问，所以最后记得把自己减掉。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=4e5+9;
ll n,LIM;
ll nn,aa[N];
ll ans[N];
struct node
{
	ll ti,l,r,k;//合法左端点 合法右端点 合法长度 
}a[N],b[N];
bool cmp0(node x,node y)
{
	if(x.k!=y.k)return x.k>y.k;
	return x.ti<y.ti;
}
struct BT
{
	ll T[N];
	ll lowbit(ll x)
	{
		return x&(-x);
	}
	void add(ll x,ll k)
	{
		for(int i=x;i<=nn;i+=lowbit(i))
		T[i]+=k;
	}
	ll query(ll x)
	{
		ll ret=0;
		for(int i=x;i>=1;i-=lowbit(i))
		ret+=T[i];
		return ret;
	}
}B;
void cdq(ll l,ll r)
{
	if(l>=r)return;
	ll mid=(l+r)>>1;
	cdq(l,mid);
	cdq(mid+1,r);
	ll i=l,p=l,q=mid+1;
	while(p<=mid&&q<=r)
	{
		if(a[p].r>=a[q].r)
		{
			if(!a[p].ti)B.add(a[p].l,1);
			b[i++]=a[p++];
		}
		else
		{
			if(a[q].ti)ans[a[q].ti]+=B.query(a[q].l);
			b[i++]=a[q++];
		}
	}
	while(p<=mid)
	{
		if(!a[p].ti)B.add(a[p].l,1);
		b[i++]=a[p++];
	}
	while(q<=r)
	{
		if(a[q].ti)ans[a[q].ti]+=B.query(a[q].l);
		b[i++]=a[q++];
	}
	for(int o=l;o<=mid;o++)
	if(!a[o].ti)B.add(a[o].l,-1);
	for(int o=l;o<=r;o++)
	a[o]=b[o];
}
int main()
{
	scanf("%lld",&n);
	ll tot=0;
	for(int i=1;i<=n;i++)
	{
		ll l,r,k;
		scanf("%lld%lld%lld",&l,&r,&k);
		a[i*2-1]=(node){0,l,r,r-l};
		a[i*2]=(node){i,r-k,l+k,k};
		aa[++tot]=l,aa[++tot]=r-k;		
	}
	sort(aa+1,aa+tot+1);
	nn=unique(aa+1,aa+tot+1)-aa-1;
	for(int i=1;i<=2*n;i++)
	a[i].l=lower_bound(aa+1,aa+nn+1,a[i].l)-aa;
	sort(a+1,a+n*2+1,cmp0);
	cdq(1,2*n);
	for(int i=1;i<=n;i++)
	printf("%lld\n",ans[i]-1);//减去自己 
	return 0;
}
```

---

## 作者：hnczy (赞：0)

由题很容易知道：

题目求 $\min(R,r_i)-\max(L,l_i) \ge K$ 的数量。

这里的 $R$ 是指现在的数的右端点，$L$ 是指左端点。

进行分类得：

$l_i\le R-K$，$r_i\ge L+K$，$r_i-l_i \ge K$ 。

## pts55

$K$ 都相等 $\Rightarrow $ $l_i\le R-K$，$r_i\ge L+K$ $\Rightarrow $ 二维偏序即可。

## pts100

就直接一个三维偏序用 cdq 分治即可解决。

cdq 分治就是一排序，二归并，三树状的做法。

即先用排序来消除一维影响，再用归并排序做出第二维的影响，在使用一个树状数组来解决即可。

核心代码：

```c++
void cdq(int l,int r) {
	if(l==r)return;
	int mid=l+r>>1;
	cdq(l,mid),cdq(mid+1,r);
	for(int i=l,L=l,R=mid+1; i<=r; i++) {
		if(R>r||a[L].y >=a[R].y&&L<=mid) {
			u[i]=a[L++];//与归并不同的地方
			if(!u[i].id)bit.add(u[i].x,1);
		} else {
			u[i]=a[R++];
			if(u[i].id)cnt[u[i].id]+=bit.query(u[i].x);//与归并不同的地方
		}
	}
	for(int i=l; i<=r; i++)a[i]=u[i];
	bit.clear();
}
```

这边建议询问和点分开处理，就像这里的有无 $id$ 一样，更加方便简洁，不用脑子。

完整代码：

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=8e5+5;
int n,tot,cnt[N],b[N];
struct node {
	int x,y,z,id,res;
} a[N],u[N];
struct B_tree {
	int c[N],t[N],T;
	void clear() {
		T++;
	}
	inline int lowbit(int x) {
		return x&-x;
	}
	inline void add(int x,int v) {
		while(x<=tot) {
			if(t[x]==T)c[x]+=v;
			else t[x]=T,c[x]=v;
			x+=lowbit(x);
		}
	}
	inline int query(int x) {
		int res=0;
		while(x) {
			if(t[x]==T)res+=c[x];
			x-=lowbit(x);
		}
		return res;
	}
	inline int query(int l,int r) {
		return query(r)-query(l-1);
	}
} bit;
bool cmp(node a,node b) {
	if(a.z!=b.z )return a.z>b.z;
	return a.id <b.id;
}
void cdq(int l,int r) {
	if(l==r)return;
	int mid=l+r>>1;
	cdq(l,mid),cdq(mid+1,r);
	for(int i=l,L=l,R=mid+1; i<=r; i++) {
		if(R>r||a[L].y >=a[R].y&&L<=mid) {
			u[i]=a[L++];
			if(!u[i].id)bit.add(u[i].x,1);
		} else {
			u[i]=a[R++];
			if(u[i].id)cnt[u[i].id]+=bit.query(u[i].x);
		}
	}
	for(int i=l; i<=r; i++)
		a[i]=u[i];
	bit.clear();
}
int main() {
	scanf("%d",&n);
	for(int i=1,l,r,k; i<=n; i++) {
		scanf("%d%d%d",&l,&r,&k);
		a[i]= {l,r,r-l,0};
		a[i+n]= {r-k,l+k,k,i};
		b[++tot]=l;
		b[++tot]=r-k;
	}
	sort(b+1,b+tot+1);
	tot=unique(b+1,b+tot+1)-b-1;
	for(int i=1; i<=2*n; i++)
		a[i].x=lower_bound(b+1,b+tot+1,a[i].x)-b;
	sort(a+1,a+2*n+1,cmp);//对z排序
	cdq(1,2*n);
	for(int i=1; i<=n; i++)
		printf("%d\n",cnt[i]-1);
	return 0;
}
```

---

