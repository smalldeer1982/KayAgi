# Array Transformer

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=242&page=show_problem&problem=3154

[PDF](https://uva.onlinejudge.org/external/120/p12003.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA12003/50f071c57d8ce0e0ecfd82014a1327d7ceae7ed2.png)

## 样例 #1

### 输入

```
10 1 11
1
2
3
4
5
6
7
8
9
10
2 8 6 10```

### 输出

```
1
2
3
4
5
6
7
8
9
6
Explanation: There is only one instruction: L = 2, R = 8, v = 6, p = 10. There are 4 numbers
(2,3,4,5) less than 6, so k = 4. The new number in A[10] is 11 ∗ 4/(8 − 2 + 1) = 44/7 = 6.```

# 题解

## 作者：broniazaichek (赞：8)

#### ~~各位大佬都是用线段树做的，蒟蒻我就只会用分块$QAQ$~~
我们可以将数列分成 $\sqrt{\smash[b]{n}}$ 个块，然后建一个辅助数组，辅助排序用二分找小于 $v$ 的第一个数的下标，统计后得到 $k$，然后单点修改

$pos[i]:$ 表示 $i$ 属于第几个块

$b[i]:$ 辅助数组，用来排序以及找小于 $v$ 的值的个数

$L[i],R[i]:$ 第 $i$ 个块的左右端点的下标

记住一定要用 **lower_bound** 而不能用 upper_bound

不然样例的第 $10$ 个数输出的就会是 $7$ 而不是 $6$（因为upper_bound 会多统计一个数，我就是因为这样而 WA 的) 

```cpp
#include<bits/stdc++.h>
#define int long long 
const int M=5e5+100;
using namespace std;
int a[M],b[M],pos[M]; //原数列，辅助数组，块
int L[M],R[M],e; //左右端点的两个数组
int n,m,u,t,k;
inline int Check_injust(int x,int y,int v)
{ 
	int w=0;
	if(pos[x]==pos[y])
    {		
		for(int i=x;i<=y;i++) if(a[i]<v) w++;
		return w; //同一个块内的直接暴力
	}
	for(int i=x;i<=R[pos[x]];i++) if(a[i]<v) w++; 
	for(int i=L[pos[y]];i<=y;i++) if(a[i]<v) w++; 
	for(int i=pos[x]+1;i<=pos[y]-1;i++) 
		w+=(lower_bound(b+L[i],b+R[i]+1,v)-b)-L[i]; //二分找小于v的值 
	return w; 
}
inline void change(int z,int v)
{
	int ls=a[z];
	a[z]=v; //暴力修改
	for(int i=L[pos[z]];i<=R[pos[z]];i++)
    { 
		if(b[i]==ls)
        {
			b[i]=v;
			break;  //辅助数组单点修改
		}
	}
	sort(b+L[pos[z]],b+R[pos[z]]+1); //重新排序
}
signed main()
{ 
	scanf("%lld%lld%lld",&n,&m,&e); 
	t=(int)sqrt(n); k=n/t;
	for(int i=1;i<=k;i++) L[i]=(i-1)*t+1,R[i]=L[i]+t-1;
	R[k]=n;
	for(int i=1;i<=k;i++) 
		for(int j=L[i];j<=R[i];j++) 
        		pos[j]=i; //分块预处理部分
	for(int i=1;i<=n;i++)
    {
		scanf("%lld",&a[i]);
		b[i]=a[i];
	}
	for(int i=1;i<=k;i++) 
    sort(b+L[i],b+R[i]+1); //辅助数组sort排序
	while(m--)
    {
		int x,y,v,p;
		scanf("%lld%lld%lld%lld",&x,&y,&v,&p);
    	change(p,(int)((e*Check_injust(x,y,v))/(y-x+1)));//单点修改
	}
  for(int i=1;i<=n;i++)
    cout<<a[i]<<endl;//输出
	return 0;
}


```
[AC记录](https://www.luogu.com.cn/record/94290780)


---

## 作者：EuphoricStar (赞：7)

## 思路

分块。

预设一个整数值 $size$（一般把 $size$ 设为 $\sqrt{n}$），然后每 $size$ 个元素分成一块，分别排好序，则查询 $(L,R,v,p)$ 的执行可以分为两步：

1. 先找出 $L$ 和 $R$ 所在块，逐一比较出有多少个元素比 $v$ 小，然后对于中间的那些块直接用二分查找，相加后得到 $k$。
2. 在 $p$ 所在块中找到修改前的 $A_p$，改成 $u \times k\ /\ (R - L + 1)$，然后不断交换相邻元素，直到该块重新排好序。

时间复杂度小于 $O(n \sqrt{n} \log{n})$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 300100, SIZE = 512;

int n, m, u, a[maxn], block[maxn / SIZE + 1][SIZE];

int query(int l, int r, int v) {
    int lb = l / SIZE, rb = r / SIZE, k = 0;
    if (lb == rb) {
        for (int i = l; i <= r; ++i) {
            if (a[i] < v) {
                ++k;
            }
        }
    } else {
        for (int i = l; i < (lb + 1) * SIZE; ++i) {
            if (a[i] < v) {
                ++k;
            }
        }
        for (int i = rb * SIZE; i <= r; ++i) {
            if (a[i] < v) {
                ++k;
            }
        }
        for (int b = lb + 1; b < rb; ++b) {
            k += lower_bound(block[b], block[b] + SIZE, v) - block[b];
        }
    }
    return k;
}

void update(int p, int x) {
    if (a[p] == x) {
        return;
    }
    int old = a[p], pos = 0, *B = &block[p / SIZE][0];
    a[p] = x;
    while (B[pos] < old) {
        ++pos;
    }
    B[pos] = x;
    if (x > old) {
        while (pos < (SIZE - 1) && B[pos] > B[pos + 1]) {
            swap(B[pos + 1], B[pos]);
            ++pos;
        }
    } else {
        while (pos > 0 && B[pos] < B[pos - 1]) {
            swap(B[pos], B[pos - 1]);
            --pos;
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &u);
    int b = 0, j = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        block[b][j] = a[i];
        if (++j == SIZE) {
            ++b;
            j = 0;
        }
    }
    for (int i = 0; i < b; ++i) {
        sort(block[i], block[i] + SIZE);
    }
    if (j) {
        sort(block[b], block[b] + j);
    }
    while (m--) {
        int l, r, v, p;
        scanf("%d%d%d%d", &l, &r, &v, &p);
        int k = query(l - 1, r - 1, v);
        update(p - 1, 1LL * u * k / (r - l + 1));
    }
    for (int i = 0; i < n; ++i) {
        printf("%d\n", a[i]);
    }
    return 0;
}
```


---

## 作者：Doqin07 (赞：3)

 ### 一篇分块的题解
预处理：
把元素压到 $vector$ 里排好序

查询操作：在块内二分查询，可以使用 $lowerbound$ 函数简化代码（ $STL$ 大法好啊！） 

修改操作：记录改变之前的值的位置，在替换成要改变的值，然后在重新排序


### Code:
```cpp
/*Coder:DongYinuo*/
#include <bits/stdc++.h>
using namespace std;
namespace Pre_work{
    int readNum(){
        char c; int x = 0, f = 1;
        while (c = getchar()){ if (c == '-') f = -1;if (isdigit(c)) break;}
        while (isdigit(c)){ x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();}
        return x * f;
    }
    template <typename T>
    void Rd(T& arg){
        arg = readNum();
    }
    template <typename T,typename...Types>
    void Rd(T& arg,Types&...args){
        arg = readNum();
        Rd(args...);
    }
}
using namespace Pre_work;
namespace I_Love_{
    typedef long long ll;
    const int N = 5e5 + 5;
    const int mod = 1e9 + 7;
    #define F(i,l,r) for (int i = l; i <= r; ++i)
    #define REP(i,r,l) for (int i = r; i >= l; --i)
    #define mem(a,b) memset(a, b, sizeof(a));
    #define MP make_pair
    #define PB push_back
    #define PII pair<int, int>
    #define PLL pair<ll, ll>
    #define all(a) begin(a),end(a)
    #define sz(a) a.size()
    #define lson ind * 2
    #define rson ind * 2 + 1
    
    vector<int> b[N];
    int n, m, u, a[N], len, id[N];
    
    ll get_ans(int l, int r, int v){
        int sid = id[l], eid = id[r], ans = 0;
        if (sid == eid){
            F (i, l, r){
                if (a[i] < v){
                    ans ++;
                }
            }
            return ans;
        } 
        for (int i = l; id[i] == sid; ++i){
            if (a[i] < v){
                ans ++;
            }
        }
        for (int i = sid + 1; i < eid; ++i){
            ans += lower_bound(all(b[i]) ,v) - b[i].begin();
        }
        for (int i = r; id[i] == eid; --i){
            if (a[i] < v){
                ans ++;
            }
        }
        return ans;
    }
    
    void run(){
        Rd(n, m, u);
        len = sqrt(n);
        F (i, 1, n){
            Rd(a[i]);
            id[i] = (i - 1) / len + 1;
            b[id[i]].PB(a[i]);
        }
        F(i, 1, n){
            sort(all(b[i]));
        }
        while (m--){
            int L, R, v, p;
            Rd(L, R, v, p);
            int tmp = a[p];
            a[p] = u * get_ans(L, R, v) / (R - L + 1);
            *lower_bound(all(b[id[p]]), tmp) = a[p];
            sort(all(b[id[p]]));
        }
        F (i, 1, n){
            printf("%d\n", a[i]);
        }
    }
    
    void OI(){
        run();
    }
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
#endif
    I_Love_::OI();
    return 0;
}
```


---

## 作者：zhengrunzhe (赞：3)

### 为什么要分块？

### 树套树天下第一

**题意：给定全局参数u，m次操作[l,r]有几个比v小的数(记作k)，单点修改p值为u*k/(r-l+1)**

显然树套树，我选择线段树套Treap
```cpp
#include<cstdio>
#include<cstdlib>
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();bool f=0;
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
template<class type>inline const void write(type out)
{
	if (out>9)write(out/10);
	putchar(out%10+48);
}
template<class type>inline const void writeln(type out)
{
	if (out<0)putchar('-'),out=-out;
	write(out);
	putchar('\n');
}
typedef long long ll;
const int N=3e5+10;
int a[N],n,u,m;
namespace Treap
{
	struct tree
	{
		int val,size,priority,cnt;
		tree *son[2];
		inline const void pushup()
		{
			size=son[0]->size+cnt+son[1]->size;
		}
	}memory_pool[N<<5],*tail,*null;
	inline const void init()
	{
		tail=memory_pool;
		null=tail++;
		null->son[0]=null->son[1]=null;
	}
	inline tree *spawn(int key)
	{
		tree *p=tail++;
		p->val=key;
		p->cnt=p->size=1;
		p->priority=rand();
		p->son[0]=p->son[1]=null;
		return p;
	}
	inline const void rotate(tree *&fa,bool f)
	{
		tree *p=fa->son[f];
		fa->son[f]=p->son[f^1];
		p->son[f^1]=fa;
		fa->pushup();(fa=p)->pushup();
	}
	inline const void insert(tree *&p,int key)
	{
		if (p==null)return p=spawn(key),void();
		p->size++;
		if (p->val==key)return p->cnt++,void();
		bool f=p->val<key;
		insert(p->son[f],key);
		if (p->priority>p->son[f]->priority)rotate(p,f);
	}
	inline const void remove(tree *&p,int key)
	{
		if (p==null)return;
		if (p->val==key)
		{
			if (p->cnt>1)return p->cnt--,p->size--,void();
			if (p->son[0]==null&&p->son[1]==null)return p=null,void();
			if (p->son[0]==null)return p=p->son[1],void();
			if (p->son[1]==null)return p=p->son[0],void();
			bool f=p->son[0]->priority>p->son[1]->priority;
			rotate(p,f);remove(p,key);
		}
		else p->size--,remove(p->son[p->val<key],key);
	}
	inline const int less(tree *p,int key)
	{
		if (p==null)return 0;
		if (key==p->val)return p->son[0]->size;
		if (key<p->val)return less(p->son[0],key);
		return less(p->son[1],key)+p->son[0]->size+p->cnt;
	}
}using namespace Treap;
class Segment_Tree
{
	private:
		struct tree
		{
			Treap::tree *root;
			tree *lson,*rson;
			inline const void update(int l,int r,int pos,int key)
			{
				remove(root,a[pos]);insert(root,key);
				if (l==r)return;
				int mid=l+r>>1;
				if (pos<=mid)lson->update(l,mid,pos,key);
				else rson->update(mid+1,r,pos,key);
			}
			inline const int query(int l,int r,int L,int R,int key)
			{
				if (l>R||r<L)return 0;
				if (l>=L&&r<=R)return less(root,key);
				int mid=l+r>>1;
				return lson->query(l,mid,L,R,key)+rson->query(mid+1,r,L,R,key);
			}
		}*root,memory_pool[N<<1],*tail;
		inline const void build(tree *&p,int l,int r)
		{
			p=tail++;p->root=null;
			for (int i=l;i<=r;i++)insert(p->root,a[i]);
			if (l==r)return;
			int mid=l+r>>1;
			build(p->lson,l,mid);
			build(p->rson,mid+1,r);
		}
	public:
		inline const void build()
		{
			init();tail=memory_pool;build(root,1,n);
		}
		inline const void modify(int l,int r,int v,int p)
		{
			int k=(ll)root->query(1,n,l,r,v)*u/(r-l+1);
			root->update(1,n,p,k);
			a[p]=k;
		}
}sgt;
int main()
{
	read(n);read(m);read(u);
	for (int i=1;i<=n;i++)read(a[i]);
	sgt.build();
	for (int l,r,v,p;m--;)read(l),read(r),read(v),read(p),sgt.modify(l,r,v,p);
	for (int i=1;i<=n;i++)writeln(a[i]);
	return 0;
}
```

---

## 作者：zyh888 (赞：2)

[P2801](https://www.luogu.com.cn/problem/P2801) [SP18185](https://www.luogu.com.cn/problem/SP18185) [UVA12003](https://www.luogu.com.cn/problem/UVA12003) [SP3261](https://www.luogu.com.cn/problem/SP3261) ~~四倍经验~~

# 题意
给定一个序列，两个操作：单点修改和区间查询(不过这两个操作是连起来的)。

# 思路
对于这种不满足区间加的区间查询，我们首先考虑分块。

将每 $\sqrt{n}$ 个数分成一个块，如果剩下几个数，就把它们分到最后一个块中。

对于操作二，我们开一个辅助数组，先将这个辅助数组每个块内排好序，将不在整块的数处理了。在整块里的，二分出块内第一个小于等于 $k$ 的数，用这个块的右端点减去它加 $1$，就是这个块对答案的贡献。

对于操作一，不仅要将原数组的 $A_{i}$ 修改，也要在辅助数组中找到 $A_{i}$，将其修改，再将辅助数组排好序，为了下次查询整块区间更方便。（看代码更好理解些）
# code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define int long long 
const int N=5*1e5+10;
using namespace std;
ll w[N],b[N]; 
int kuai[N]; //w是原数组，b是辅助数组，kuai[i]代表第i个元素在第几块
int l[N],r[N]; //每个区间的左右端点
int n,m,u,len,k;
int query(int x,int y,int v){
	int res=0;
	if(kuai[x]==kuai[y]){		
		for(int i=x;i<=y;i++) if(w[i]<v) res++; //块内直接暴力
		return res;
	}
	for(int i=x;i<=r[kuai[x]];i++) if(w[i]<v) res++;
	for(int i=y;i>=l[kuai[y]];i--) if(w[i]<v) res++; //不在一整块的直接暴力
	for(int i=kuai[x]+1;i<=kuai[y]-1;i++)
		res+=(lower_bound(b+l[i],b+r[i]+1,v)-b)-l[i]; //每个完整的块利用辅助数组的单调性求出答案	
	return res; 
}
void change(int hh,ll v){
	int temp=w[hh];
	w[hh]=v; //原数组修改
	for(int i=l[kuai[hh]];i<=r[kuai[hh]];i++){ //在辅助数组中寻找 w[i],并将它修改
		if(b[i]==temp){
			b[i]=v;
			break;
		}
	}
	sort(b+l[kuai[hh]],b+r[kuai[hh]]+1);
}
signed main(){ 
	scanf("%lld%lld%lld",&n,&m,&u); 
	len=sqrt(n);
	k=n/len;
	for(int i=1;i<=k;i++) l[i]=(i-1)*len+1,r[i]=l[i]+len-1;
	r[k]=n;
	for(int i=1;i<=k;i++) 
		for(int j=l[i];j<=r[i];j++) kuai[j]=i; //分块
	for(int i=1;i<=n;i++){
		scanf("%lld",&w[i]);
		b[i]=w[i];
	}
	for(int i=1;i<=k;i++) sort(b+l[i],b+r[i]+1); //将辅助数组按块排序
	while(m--){
		int x,y,v,p,ans;
		scanf("%lld%lld%lld%lld",&x,&y,&v,&p);
		ans=query(x,y,v);
		change(p,(ll)u*ans/(y-x+1));
	}	
	for(int i=1;i<=n;i++) printf("%lld\n",w[i]);
	return 0;
}
```

---

## 作者：jia_shengyuan (赞：2)

## 前言

很不错的一道分块入门题，看到其他分块题解复杂度都不够优后决定写一篇理论最优的分块做法。截至目前我的代码也是本题的最优解。

## 做法

考虑分块，块长为 $B$，同一块内排序。询问时，两端的散块暴力，中间的整块二分。修改时，在排好序的数组中找到原值，将其修改为新值，并不断交换相邻两项就可以在线性时间内重新排序了。

这一做法下单次操作时间复杂度为 $O(B+\frac{n}{B}\log n)$（$\log n$ 和 $\log B$ 没区别）。运用均值不等式相关知识，我们可以知道 $B=\frac{n}{B}\log n$ 即 $B=\sqrt{n\log n}$ 时复杂度最优，总时间复杂度为 $O(m\sqrt{n\log n})$。若像其他题解一样取 $B=\sqrt n$，则时间复杂度会退化成 $O(m\sqrt n\log n)$，慢了四倍左右。进一步优化可以使用树套树，达到 $O(m\log^2n)$。

代码中使用了自己的快读库。

```cpp
#include <fastio.hpp>
#include <algorithm>
#include <vector>
#include <cmath>

const int maxn = 3e5+9;
using namespace std;

int a[maxn],bid[maxn],n,m,u;
vector<int> b[600];
double siz;

void Read(){
    read(n,m,u);
    siz = sqrt(n*log2(n)+1);//+1是为了防止n=1时块长取0
    bid[0] = -1;
    for(int i=1; i<=n; i++){
        read(a[i]);
        bid[i] = round(i/siz);
        b[bid[i]].push_back(a[i]);
    }
    bid[n+1] = bid[n]+1;
    for(int i=0; i<=bid[n]; i++) sort(b[i].begin(),b[i].end());
}

inline int Query(int l, int r, int v){
    int res=0;
    if(bid[l] == bid[r]){
        for(int i=l; i<=r; i++){
            if(a[i] < v) res++;
        }
        return res;
    }
    for(int i=l; bid[i] == bid[l]; i++) {
        if(a[i] < v) res++;
    }
    for(int i=r; bid[i] == bid[r]; i--) {
        if(a[i] < v) res++;
    }
    for(int i=bid[l]+1; i<bid[r]; i++){
        res += lower_bound(b[i].begin(),b[i].end(),v)-b[i].begin();
    }
    return res;
}
inline void Modify(int pos, int val){
    vector<int> &v = b[bid[pos]];
    int vpos = lower_bound(v.begin(),v.end(),a[pos])-v.begin();
    v[vpos] = val;
    while(vpos > 0 && v[vpos] < v[vpos-1]) {
        swap(v[vpos],v[vpos-1]);
        --vpos;
    }
    while(vpos < v.size()-1 && v[vpos] > v[vpos+1]){
        swap(v[vpos],v[vpos+1]);
        ++vpos;
    }
    a[pos] = val;
}

int main(){
    Read();
    int l,r,v,p,ans;
    while(m--){
        read(l,r,v,p);
        ans = Query(l,r,v);
        Modify(p,1ll*u*ans/(r-l+1));//开ll
    }
    for(int i=1; i<=n; i++) writeln(a[i]);
    fastio_flush();
    return 0;
}
```


---

## 作者：houpingze (赞：1)

由于 $ m\leq 5\times10^4 $ ，时间限制 $ 5 \text{s} $ ，我们考虑分块（什

具体思路：

$ \sqrt{n} $ 一块，每块用一个 $ \text{vector} $ 维护**当前块的递增有序序列**，每次询问的时候，对于零散块，我们可以暴力统计。对于每一个完整的块，由于我们有有序的 $ \text{vector} $ ，可以使用 $ \text{lower\_bound} $ 函数计算**严格小于** $ v $ 的数的个数。

最后按照题意单点修改 $ a_p $ 即可，注意此时块内和 $ a $ 数组都要修改，块内还需要重新排序。具体实现：

```cpp
int t=a[p];
a[p]=u*k/(r-l+1);
*lower_bound(vc[id[p]].begin(),vc[id[p]].end(),t)=a[p];
sort(vc[id[p]].begin(),vc[id[p]].end());
```

其中 $ id_i $ 表示 $ a_i $ 所在的块下标， $ vc_i $ 里的元素是块 $i$ 的有序序列。

总体时间复杂度： $ \mathcal{O(m \sqrt{n} \log \sqrt{n})} $ 

---

## 作者：银河AI (赞：1)

## 解题思路

写一篇不用 vector 的分块题解。

我们用一个辅助数组 $b$，来存储每个块的排序结果。

对于查找区间内所有小于 $v$ 的个数：

同一个块暴力修改，不同块的边角暴力，块内二分。

同块暴力修改应该不用多说了。

对于不同块的块内二分，
直接用 lower_bound 查找块内第一个比 $v$ 大的数。

下面是查找代码：

```cpp
for(int i=bel[l]+1;i<bel[r];i++) k+=lower_bound(b+st[i],b+ed[i]+1,v)-b-st[i];
```

暴力单点修改，但要注意的是， $b$ 数组要重新赋值，然后要重新排序。

注意：如果 RE 了的话把数组开大一点。
 
## AC代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+1;
int n,m,u,k;
int len,block,bel[N],a[N],b[N],st[N],ed[N];
inline void init(){
	block=sqrt(n);len=ceil((double)n/block);
	for(int i=1;i<=len;i++){
		for(int j=(i-1)*block+1;j<=i*block;j++) bel[j]=i;
		st[i]=(i-1)*block+1,ed[i]=i*block;
		if(i==len) ed[i]=n;
		sort(b+st[i],b+ed[i]+1);
	}
}
inline void ask(int l,int r,int v){
	if(bel[l]==bel[r]){
		for(int i=l;i<=r;i++) if(a[i]<v) k++;
		return ;
	}
	for(int i=l;i<=ed[bel[l]];i++) if(a[i]<v) k++;
	for(int i=st[bel[r]];i<=r;i++) if(a[i]<v) k++;
	for(int i=bel[l]+1;i<bel[r];i++) k+=lower_bound(b+st[i],b+ed[i]+1,v)-b-st[i];
}
inline void change(int x,int q){
	a[x]=q;
	for(int i=st[bel[x]];i<=ed[bel[x]];i++) b[i]=a[i];
	sort(b+st[bel[x]],b+ed[bel[x]]+1);
}
int l,r,v,p;
signed main(){
	scanf("%lld%lld%lld",&n,&m,&u);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),b[i]=a[i];
	init();
	while(m--){
		scanf("%lld%lld%d%lld",&l,&r,&v,&p);
		ask(l,r,v);
		change(p,u*k/(r-l+1));
		k=0;
	}
	for(int i=1;i<=n;i++) printf("%lld\n",a[i]); 
}
```


---

## 作者：RuntimeErr (赞：1)

# 超级暴力的分块做法！

我们把每个元素都存进 $vector$ 里提前排好序。

对于查询操作，我们块内使用 $lower\_bound$ 二分，边角暴力，单次时间复杂度 $O(\sqrt{n}\log{(\sqrt{n})})$ 。

对于修改操作，我们直接暴力清空其块的 $vector$ 再重新加进去排序，单次时间复杂度 $O(\sqrt{n}+n\log{n})$ （有点不太会算，如果不对请大佬们指出谢谢QAQ）。

简单明了的题解 $over$！

### $Show\ you\ the\ code$

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
#define N (int)(3e5+10)
#define int long long
#define re register
#define fp(i,l,r) for(re int i=(l);i<=(r);++i)
inline void read(int &x){
	x=0;re int f=1;re char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^'0'),ch=getchar();
	x*=f;
}

vector<int>b[N];//块内vector
int n,m,u,a[N];
int B,bl[N],L[N],R[N];//分块必备

int get(int l,int r,int v){
	int ans=0;
	if(bl[l]!=bl[r]){//块内二分边角暴力
		fp(i,bl[l]+1,bl[r]-1)ans+=lower_bound(b[i].begin(),b[i].end(),v)-b[i].begin();
		fp(i,l,R[bl[l]])if(a[i]<v)++ans;
		fp(i,L[bl[r]],r)if(a[i]<v)++ans;
	}else fp(i,l,r)if(a[i]<v)++ans;
	
	return ans;
}
inline void reset(int x){//整个清空再重新加回去排序
	b[x].clear();
	fp(i,L[x],R[x])b[x].push_back(a[i]);
	sort(b[x].begin(),b[x].end());
}

signed main(){
	read(n);read(m);read(u);
	B=pow(n,0.455);int tmp; 
	fp(i,1,n){//init
		bl[i]=(i-1)/B+1;
		if(tmp!=bl[i])L[bl[i]]=i,tmp=bl[i];
		else R[bl[i]]=i;
		read(a[i]);
		b[bl[i]].push_back(a[i]);
	}
	fp(i,1,n)sort(b[i].begin(),b[i].end());
	fp(i,1,m){
		int l,r,v,p;
		read(l);read(r);read(v);read(p);
		a[p]=u*get(l,r,v)/(r-l+1);//直接修改
		reset(bl[p]);//暴力更新
	}
	fp(i,1,n)printf("%lld\n",a[i]);
	return 0;
}
```


---

## 作者：5k_sync_closer (赞：0)

平板电视做法，码量很小。

需要维护带单点修改的二维偏序，考虑树套树。

手写太麻烦了，考虑树状数组套 `__gnu_pbds::tree`。

用 `tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update> c` 定义一棵元素类型为 `T` 的红黑树。

本题中需要用到的操作：

- `c.insert(x)`：在 `c` 中插入 `x`。
- `c.erase(x)`：在 `c` 中删除 `x`。
- `c.order_of_key(x)`：返回 `c` 中小于 `x` 的元素个数。
- `c.lower_bound(x)`：返回 `c` 中大于等于 `x` 的最小元素的迭代器。

但是 `__gnu_pbds::tree` 存不了重复元素，所以用 `std::pair` 区分重复元素。

`__gnu_pbds::tree` 不能整体加减，所以最后输出答案时得二分一下值域。

然后正常地写树状数组套平衡树即可。

```cpp
#include <cstdio>
#include <algorithm>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
int n, m, u, z, a[300050];
struct T
{
    tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> c;
    void C(int x, int k)
    {
        if (k)
            c.insert({x, ++z});
        else
            c.erase(c.lower_bound({x, 1}));
    }
    int Q(int y) { return c.order_of_key({y, 1}); }
} c[300050];
void C(int x, int y, int k)
{
    for (; x <= n; x += x & -x)
        c[x].C(y, k);
}
int Q(int x, int y, int s)
{
    int q = 0;
    for (--x; y > x; y &= y - 1)
        q += c[y].Q(s);
    for (; x > y; x &= x - 1)
        q -= c[x].Q(s);
    return q;
}
int main()
{
    scanf("%d%d%d", &n, &m, &u);
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i), C(i, a[i], 1);
    for (int i = 0, x, y, k, p; i < m; ++i)
    {
        scanf("%d%d%d%d", &x, &y, &k, &p);
        k = 1ll * u * Q(x, y, k) / (y - x + 1);
        C(p, a[p], 0);
        C(p, a[p] = k, 1);
    }
    for (int i = 1, l, r, m; i <= n; ++i)
    {
        l = 0;
        r = 1e9;
        while (l <= r)
            if (Q(i, i, m = l + r >> 1))
                r = m - 1;
            else
                l = m + 1;
        printf("%d\n", r);
    }
    return 0;
}
```


---

## 作者：让风忽悠你 (赞：0)

和 [数列分块 2](https://loj.ac/p/6278) 没啥区别。

要提高块内查找的效率最容易的办法就是二分，所以只需要开个 $vector$ 存下块内的每个数然后排序，直接暴力修改然后更新整个块。

数组记得开大一些，还有就是要开 ll。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cmath>
#define ll long long
#define N 500005

using namespace std;

int n,m,len;
ll u,a[N],id[N];
vector <ll> ve[N];

void change(int x){
	
	ve[x].clear();
	
	for(int i=(x-1)*len+1;i<=x*len;i++)
	
		ve[x].push_back(a[i]);
	
	sort(ve[x].begin(),ve[x].end());
	
}

ll solve(ll l,ll r,ll v){
	
	ll res=0ll;
	int st=id[l],ed=id[r];
	
	if(st==ed){
		
		for(int i=l;i<=r;i++)
			
			if(a[i]<v)
			
				++res;
		
		return res;
		
	}
	
	for(int i=l;id[i]==st;i++)
	
		if(a[i]<v)
		
			++res;
			
	for(int i=st+1;i<ed;i++)
		
		res+=lower_bound(ve[i].begin(),ve[i].end(),v)-ve[i].begin();
	
	for(int i=r;id[i]==ed;i--)
		
		if(a[i]<v)
			
			++res;
	
	return res;
	
}

int main(){
	
	scanf("%d%d%lld",&n,&m,&u);
	
	len=sqrt(n);
	for(int i=1;i<=n;i++){
		
		scanf("%lld",&a[i]);
		
		id[i]=(i-1)/len+1;
		ve[id[i]].push_back(a[i]);
		
	}
	
	for(int i=1;i<=id[n];i++)
		
		sort(ve[i].begin(),ve[i].end());
		
	ll l,r,v,p;
	
	while(m--){
		
		scanf("%lld%lld%lld%lld",&l,&r,&v,&p);
		
		ll k=solve(l,r,v);
		a[p]=u*k/(r-l+1);
		change(id[p]);
		
	}
	
	for(int i=1;i<=n;i++)
		
		printf("%lld\n",a[i]);
	
	return 0;
	
}
```


---

## 作者：happybob (赞：0)

## 题意

给定一个序列 $a$，支持两种操作：

1. 求区间 $a_l, a_{l+1}, \cdots, a_r$ 中严格小于 $v$ 的数的个数。

1. 单点修改。

## 解法

块内二分模板题。

考虑每一个块维护一个有序的 `vector` 或者其他容器，块内查询用 `lower_bound`，块外暴力。单点修改时修改数组的值并且用 $O(\sqrt{n} \log{\sqrt{n}})$ 重新排序该块。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

#define int long long

constexpr int N(3e5 + 5), M(585);

int n, m, u, len, a[N];
vector<int> p[M];

inline int get(int x)
{
	if (x == 0) return 0;
	return (x - 1) / len + 1;
}

inline int lplace(int x)
{
	return (x - 1) * len + 1;
}

inline int rplace(int x)
{
	return x * len;
}

signed main()
{
	scanf("%lld%lld%lld", &n, &m, &u);
	len = sqrt(n);
	for (register int i(1); i <= n; ++i)
	{
		scanf("%lld", &a[i]);
		p[get(i)].push_back(a[i]);
	}
	for (register int i(1); i <= len + 1; i++)
	{
		sort(p[i].begin(), p[i].end());
	}
	while (m--)
	{
		int l, r, v, pg, ans(0);
		scanf("%lld%lld%lld%lld", &l, &r, &v, &pg);
		if (get(l) == get(r))
		{
			for (int i(l); i <= r; i++) ans += a[i] < v;
		}
		else
		{
			int lp(get(l) + 1), rp(get(r) - 1);
			for (int i(lp); i <= rp; i++)
			{
				vector<int>::iterator it = lower_bound(p[i].begin(), p[i].end(), v);
				ans += (it - p[i].begin());
			}
			int lk(lplace(lp)), rk(rplace(rp));
			for (int i(l); i < lk; i++) ans += a[i] < v;
			for (int i(rk + 1); i <= r; i++) ans += a[i] < v;
		}
		int k(a[pg]);
		a[pg] = u * ans / (r - l + 1);
		*lower_bound(p[get(pg)].begin(), p[get(pg)].end(), k) = a[pg];
		//cout << ans << endl;
		sort(p[get(pg)].begin(), p[get(pg)].end());
	}
	for (int i(1); i <= n; i++) printf("%lld\n", a[i]);
	return 0;
}
```


---

## 作者：dingshengyang (赞：0)

块内排序加二分。

首先读入各数，然后用 $block_{b,j}$ 保存第 $b$ 块第 $j$ 个数。

读入后 `sort` 一下。

然后每次二分查找。懒癌患者用 `lower_bound`。

然后是修改。先修改数组 $A$，然后在块内找到合适位置插入（类似于插入排序）。

没什么好讲的了，顺便说一下，块长本来应该取 $\sqrt{n}$，但是取 $4096$ 可以卡常（`>>12`，编译器应该已经自动优化了，最优解 rank $4$）。

好，上代码！

```cpp#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 300000 + 10;
const int SIZE = 4096;

int n,m,u,A[maxn],block[maxn/SIZE+1][SIZE];
void init(){
	scanf("%d%d%d",&n,&m,&u);
	int b = 0,j = 0;
	for(int i = 0;i < n;i ++){
		scanf("%d",&A[i]);
		block[b][j] = A[i];
		if(++j == SIZE){
			b++;j = 0;
		}
	}
	for(int i = 0;i < b;i ++)sort(block[i],block[i]+SIZE);
	if(j) sort(block[b],block[b]+j);
	return;
}

int query(int L,int R,int v){
	int lb = L/SIZE,rb = R/SIZE;
	int k = 0;
	if(lb == rb){
		for(int i = L;i <= R;i ++)
			if(A[i] < v)
				k ++;
	} else{
		for(int i = L;i < (lb+1)*SIZE;i ++)
			if(A[i] < v)
				k ++;
		for(int i = rb*SIZE;i <= R;i ++)
			if(A[i] < v)
				k ++;
		for(int b = lb+1;b < rb;b ++)
			k += lower_bound(block[b],block[b]+SIZE,v)-block[b];
	}
	return k;
}

void change(int p,int x){
	if(A[p] == x)return;
	int old = A[p],pos = 0,*B = &block[p/SIZE][0];
	A[p] = x;
	while(B[pos] < old)pos ++;B[pos] = x;
	if(x > old){
		while(pos < SIZE-1 && B[pos] > B[pos+1]){
			swap(B[pos+1],B[pos]);
			pos++;
		}
	}qq
		
	else{
		while(pos > 0 && B[pos] < B[pos-1]){
			swap(B[pos-1],B[pos]);
			pos--;
		}
	}
		
	return;
}

int main(){
	init();
	while(m--){
		int L,R,v,p;
		scanf("%d%d%d%d",&L,&R,&v,&p);L--;R--;p--;
		int k = query(L,R,v);
		change(p,(long long)u*k/(R-L+1));
	}
	for(int i = 0;i < n;i ++)
		printf("%d\n",A[i]);
	return 0;
}
```

---

## 作者：ez_lcw (赞：0)

我们考虑用分块来~~水~~过此题

我们先将原序列进行分块，对于某个块 $B$ 内的数，我们把它们放进一个数组 $block[B][\ ]$ 里，再对数组进行排序。那么我们就得到了 $\sqrt{n}$ 个有序数组 $block[\ ][\ ]$。

然后对于修改操作，例如把 $x$ 位置上的数 $y$ 修改成 $z$，我们找到 $x$ 所在的块 $B$，并在 $block[B][\ ]$内找到 $y$，然后把 $y$ 修改成 $z$，然后再重新排一下序。

对于询问操作，我们先将边角暴力求解出来，也就是不能凑成块的询问范围暴力。而对于某个块，如果它完全在询问范围内，我们采用二分的方式求解。当然，我们可以用$lower\_bound()$来省略这段代码。所以说整个询问的求解方式就是“**边角暴力，块内二分**”。

所以整体时间复杂度为$O(n\sqrt{n}\log(\sqrt{n}))$。~~我也不知道是怎么跑过去的~~

代码如下：

```cpp
#include<bits/stdc++.h>

#define N 300010
#define SN 550

using namespace std;

int n,m,u,a[N];
int len,lastlen,block[SN][SN];

int get(int x)
{
	return (x-1)/len+1;
}

int query(int l,int r,int v)
{
	int lb=get(l),rb=get(r),ans=0;
	if(lb==rb)
	{
		for(int i=l;i<=r;i++)
			ans+=(a[i]<v);
		return ans;
	}
	for(int i=l;i<=lb*len;i++)
		ans+=(a[i]<v);
	for(int i=(rb-1)*len+1;i<=r;i++)
		ans+=(a[i]<v);
	for(int i=lb+1;i<=rb-1;i++)
		ans+=lower_bound(block[i]+1,block[i]+len+1,v)-block[i]-1;
	return ans;
}

void update(int x,int val)
{
	int bl=get(x),now=1;
	while(block[bl][now]<a[x]) now++;
	block[bl][now]=val;
	while(now<block[bl][0]&&block[bl][now]>block[bl][now+1]) 
	{
		swap(block[bl][now],block[bl][now+1]);
		now++;
	}
	while(now>1&&block[bl][now-1]>block[bl][now])
	{
		swap(block[bl][now],block[bl][now-1]);
		now--;
	}
	a[x]=val;
}

int main()
{
	scanf("%d%d%d",&n,&m,&u);
	len=sqrt(n);
	for(int i=1,b=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		block[b][++block[b][0]]=a[i];
		if(block[b][0]==len)b++;
	}
	for(int i=1;i<=len;i++)
		sort(block[i]+1,block[i]+block[i][0]+1);
	if(len*len<n) sort(block[len+1]+1,block[len+1]+block[len+1][0]+1);
	while(m--)
	{
		int l,r,v,p;
		scanf("%d%d%d%d",&l,&r,&v,&p);
		int k=query(l,r,v);
		update(p,(1ll*u*k)/(r-l+1));//注意这里要longlong
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",a[i]);
	return 0;
} 
```


---

## 作者：_zjr (赞：0)

# 众所周知，分块一种~~极简单~~的神仙数据结构

那么，分块的基本思想是什么呢？

其实，他的名字已经很明显了，就是把你会的（数组，链表，~~线段树~~啊什么的）数据结构分成一块一块的来进行高级处理。

那怎么分才能达到我们用它取代**某树套某树**这种毒瘤数据结构呢？

**每$\sqrt n$一块！**

为什么呢？~~因为我也不知道~~

谈谈我的个人理解：

> 这种数据结构需要兼顾时间和空间，因此需要找一个值，使得总的数据规模除以这个值之后能达到一种时间与空间上的平衡。因为我们事先不知道这样的值，所以只能从他自身找，而又不能是自身（就成普通数组了啊qwq）所以，我们选择$\sqrt n$

~~瞎逼逼完毕~~

然后我们来看一下这道题

```cpp
#include <bits/stdc++.h>
#define ll long long
#define R register
#define I inline
#define Ri R int
using namespace std;

const int maxn = 300010, siz = 4096;
int n, m, u, a[maxn];
int block[maxn / siz + 1][siz];

void init()
{
    scanf("%d %d %d", &n, &m, &u);
    int b = 0, j = 0;
    for(Ri i = 0; i < n; ++i)
    {
        scanf("%d", &a[i]);
        block[b][j] = a[i];
        if(++j == siz) {j = 0; ++b;}
    }
    for(Ri i = 0; i < b; ++i) sort(block[i], block[i] + siz);
    if(j) sort(block[b], block[b] + j);
}
I int query(int l, int r, int v)
{
    int lb = l / siz, rb = r / siz;
    int k = 0;
    if(lb == rb) {for(Ri i = l; i <= r; ++i) if(a[i] < v) ++k; return k;}
    for(Ri i = l; i < (lb + 1) * siz; ++i) if(a[i] < v) ++k;
    for(Ri i = rb * siz; i <= r; ++i) if(a[i] < v) ++k;
    for(Ri b = lb + 1; b < rb; ++b) k += lower_bound(block[b], block[b] + siz, v) - block[b];
    return k;
}
void change(int p, int x)
{
    if(a[p] == x) return;
    int old = a[p], pos = 0, *b = &block[p / siz][0];
    a[p] = x;

    while(b[pos] < old) ++pos;
    b[pos] = x;
    if(x > old)
        while(pos < siz - 1 && b[pos] > b[pos + 1])
        {swap(b[pos], b[pos + 1]); ++pos;}
    else
        while(pos > 0 && b[pos] < b[pos - 1])
        {swap(b[pos], b[pos - 1]); --pos;}
}

int main()
{
    init();
    while(m--)
    {
        int l, r, p, v;
        scanf("%d %d %d %d", &l, &r, &v, &p); l--; r--; p--;
        int k = query(l, r, v);
        change(p, (ll)u * k / (r - l + 1));
    }
    for(Ri i = 0; i < n; ++i) printf("%d\n", a[i]);
    return 0;
}
```

---

