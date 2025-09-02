# [USACO07DEC] Gourmet Grazers G

## 题目描述

约翰的奶牛对食物越来越挑剔了。现在，商店有 $m$ 份牧草可供出售，奶牛食量很大，每份牧草仅能供一头奶牛食用。第 $i$ 份牧草的价格为 $p_i$，口感为 $q_i$。

约翰一共有 $n$ 头奶牛，他要为每头奶牛订购一份牧草，第 $i$ 头奶牛要求 它的牧草价格不低于 $a_i$，口感不低于 $b_i$。请问，约翰应该如何为每头奶牛选择牧草，才能让他花的钱最少？

## 说明/提示

对于 $100\%$ 的数据，满足 $1\leqslant n\leqslant 10^5$，$1\leqslant a_i,b_i,c_i,d_i\leqslant 10^9$。

## 样例 #1

### 输入

```
4 7
1 1
2 3
1 4
4 2
3 2
2 1
4 3
5 2
5 4
2 6
4 4```

### 输出

```
12```

# 题解

## 作者：zac2010 (赞：9)

这道题目是溢水的蓝题（毕竟用 `multiset` 做就是如此）！！
### 思路
这道题我们通过排序来削掉口感那个指标！

首先，我们定义一个结构体（方便排序）

```cpp
struct A{
	int a,b,c;//a、b为题目中的意思，c=0表示当前的为牛，相反，c=1表示当前的为干草
}a[200010];

```

再定义一个可重集 `multiset` 。

```cpp
multiset<int>s;
```

所以我们先把草和牛按照口感从大到小排序

```cpp
bool cmp(A a,A b){
	if(a.b==b.b)
		return a.c>b.c;
	return a.b>b.b;
}
sort(a+1,a+n+1,cmp);
```

我们再从前往后遍历排序后的数组

1. 如果遇到了草，我们把它的价钱加进 `multiset` 里
```cpp
if(a[i].c==1)
	s.insert(a[i].a);
```


2. 如果遇到了牛，由于我们的第二个指标也就是口感满足一定大于等于当前牛的口感，所以不用管，毕竟我们已经排过序了（成功削掉一个指标）。然后我们呢再通过 `multiset` 的一系列操作得到最小的大于等于当前所需价钱的干草。

```cpp
else{
	set<int>::iterator it=s.lower_bound(a[i].a);
	if(s.empty()||it==s.end()){
		cout<<-1<<endl;
		return 0;
	}
	ans+=*it;
	s.erase(it);
}

```

最后输出所有干草价钱的和即可

### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct A{
	int a,b,c;
}a[200010];
int n,m,ans;
multiset<int>s;
bool cmp(A a,A b){
	if(a.b==b.b)
		return a.c>b.c;
	return a.b>b.b;
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&a[i].a,&a[i].b);
		a[i].c=0;
	}
	n+=m;
	for(int i=n-m+1;i<=n;i++){
		scanf("%lld%lld",&a[i].a,&a[i].b);
		a[i].c=1;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(a[i].c==1)
			s.insert(a[i].a);
		else{
			set<int>::iterator it=s.lower_bound(a[i].a);
			if(s.empty()||it==s.end()){
				cout<<-1<<endl;
				return 0;
			}
			ans+=*it;
			s.erase(it);
		}
	}
	cout<<ans<<endl;
}
```

---

## 作者：斗神_君莫笑 (赞：7)

明显本题按照w为关键字排序之后，问题转化为查找大于a[i].v的最小value   
由于是查找后继，所以需要一棵平衡树  
此处介绍一种STL——multiset  
支持对元素的插入，删除，以及查询后继  
```cpp
multiset<int>s;//定义   

s.insert(i);//插入  

s.find(i);//返回i在集合中所处的位置（迭代器）

s.erase(i);//如果i是数值，删除所有为i的元素
//如果i是迭代器，删除所指向的元素
//所以删除一个元素，写为s.erase(s.find(i));

s.count(i);//i元素在集合中数量

s.lower_bound(i);//查询i元素后继，返回迭代器
//注意不能写成lower_bound(s.begin(),s.end(),i);绝对错误
```
由此本题的代码就非常简洁了  
注意一下边界条件即可   
~~我才不会说是因为我懒得写非旋treap~~ 
```cpp
#include<bits/stdc++.h>
using namespace std;
multiset<int>s;
multiset<int>::iterator it;
struct Node{
	int v,w;//价格，口感 
}a[100010],b[100010];
bool cmp(const Node &x,const Node &y){
	//if(x.w==y.w)return x.v>y.v;
	return x.w>y.w;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&a[i].v,&a[i].w);
	for(int i=1;i<=m;++i) 
		scanf("%d%d",&b[i].v,&b[i].w);
	sort(a+1,a+n+1,cmp);
	sort(b+1,b+m+1,cmp);
	int now=1;
	long long ans=0;
	for(int i=1;i<=n;++i){
		while(now<=m&&b[now].w>=a[i].w)
			s.insert(b[now++].v);
		it=s.lower_bound(a[i].v);
		if(it==s.end()){
			printf("-1");
			return 0;
		}
		ans+=*it;
		s.erase(s.find(*it));
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Nemonade (赞：2)

用 `multiset` 的题解很多了，来一发 `FHQTreap`。

需要注意的是，和板子题相比这题的后继是可以包含本身的，注意一下。

贪心思路和其他题解一样了。~~不知道为什么我的平衡树跑得飞快，甚至进了最优解第一页~~。

下面的代码包含了平衡树板子：

```cpp
/*Source:T1.
**Coder:NemonadePanda
**Powered By VS-Code*/
#include<bits/stdc++.h>
typedef long long ll;
#define pfor(i,x,y) for(register int i=x;i<=y;++i)
#define mfor(i,x,y) for(register int i=x;i>=y;--i)
template<typename T=int>inline T read(){
  T x=0;bool f=false;char c=getchar();
  while(c<'0'||c>'9')f|=(c=='-'),c=getchar();
  while(c>='0'&&c<='9')x=x*10+c-48,c=getchar();
  return f?-x:x;}
template<typename T>inline void write(T x){
  if(x<0){putchar('-');x=-x;}if(x/10)
	write(x/10);putchar((x%10)^48);return;}
using std::max;using std::min;using std::abs;
using std::cin;using std::cout;using std::endl;
const int N=1e5+5,M=1e6+5,MOD=1e9+7,INF=0x3f3f3f3f;
#define int long long
struct Grass{int cost,taste;}a[N],b[N];
inline bool cmp(Grass a,Grass b){
	return a.taste>b.taste;
}
int n,m,res;
template<typename T>struct FhqTreapNode{int lch,rch,size,key;T data;};
template<typename T>class FhqTreap{
private:
	FhqTreapNode<T> t[N];int rt,tot,x,y,z;
	inline int Node(T d){t[++tot].data=d,t[tot].key=rand();t[tot].size=1;return tot;}
	inline void pushup(int p){t[p].size=t[t[p].lch].size+t[t[p].rch].size+1;return;}
	inline int data_(int p,int d){while(true){if(d==t[t[p].lch].size+1) return p;
		if(d<=t[t[p].lch].size) p=t[p].lch;else d-=t[t[p].lch].size+1,p=t[p].rch;}return 0;}
public:
	inline void split(int p,int &x,int &y,T d){
		if(!p){x=y=0;return;}if(t[p].data<=d) split(t[x=p].rch,t[p].rch,y,d);
		else split(t[y=p].lch,x,t[p].lch,d);pushup(p);return;}
	inline int merge(int x,int y){if(x==0||y==0) return x+y;
		if(t[x].key<t[y].key){t[x].rch=merge(t[x].rch,y);pushup(x);return x;}
		else{t[y].lch=merge(x,t[y].lch);pushup(y);return y;}return 0;}
	inline void insert(T d){split(rt,x,y,d);rt=merge(merge(x,Node(d)),y);return;}
	inline void erase(T d){split(rt,x,z,d),split(x,x,y,d-1);rt=merge(merge(x,merge(t[y].lch,t[y].rch)),z);return;}
	inline int rank(T d){split(rt,x,y,d-1);int res=t[x].size+1;rt=merge(x,y);return res;}
	inline T data(int d){return t[data_(rt,d)].data;}
	inline T pre(T d){split(rt,x,y,d-1);T res=t[data_(x,t[x].size)].data;rt=merge(x,y);return res;}
	inline T nxt(T d){split(rt,x,y,d-1/*这里要-1哦*/);T res=t[data_(y,1)].data;rt=merge(x,y);return res;}
};
FhqTreap<int> set;
signed main(){
	n=read(),m=read();
	pfor(i,1,n) a[i].cost=read(),a[i].taste=read();
	pfor(i,1,m) b[i].cost=read(),b[i].taste=read();
	std::sort(a+1,a+n+1,cmp);
	std::sort(b+1,b+m+1,cmp);
	int p=1;set.insert(INF);
	pfor(i,1,n){
		while(p<=m&&b[p].taste>=a[i].taste) set.insert(b[p++].cost);
		int it=set.nxt(a[i].cost);
		if(it==INF){puts("-1");return 0;}
		res+=it;set.erase(it);
	}
	cout<<res;
	return 0;
}
```

---

## 作者：DefFrancis (赞：2)

这题是个贪心，考虑一下按口感度降序排列可供的牧草和奶牛，

假如现在是第 i 头奶牛，

从降序排列的牧草中选择满足他口感的牧草，

加入某个数据结构中(雾)

然后贪心地找不低于他要求的价格的牧草中最小的

~~删除~~吃掉

可以发现对于下一头奶牛 j

现有数据结构中的牧草必定满足他的口感(因为是降序排序的)

这样就要求这个数据结构可以

1.加入某个数

2.删除某个数

3.求某个数的后继

所以我们可以直接上平衡树(STL也可以)

这里写的是FHQTreap


```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    char c=getchar();
    int x=0,f=1;
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
const int maxn=1e5+10;
int n,m;
struct E{
    int a,b;
}a[maxn],b[maxn];
bool cmp(E a,E b){
    return a.b>b.b;
}
long long ans;
int ch[maxn][2],sz[maxn],val[maxn],rnd[maxn],id,root,x,y,z;
inline void update(int now){
    sz[now]=1+sz[ch[now][1]]+sz[ch[now][0]];
}
inline int new_node(int x){
    sz[++id]=1;
    rnd[id]=rand();
    val[id]=x;
    return id;
}
inline int split(int now,int k,int &x,int &y){
    if(!now)x=y=0;
    else {
        if(val[now]<=k){
            x=now,split(ch[now][1],k,ch[now][1],y);
        }
        else {
            y=now,split(ch[now][0],k,x,ch[now][0]);
        }
        update(now);
    }
}
inline int merge(int x,int y){
    if(!x||!y)return x+y;
    if(rnd[x]<rnd[y]){
        ch[x][1]=merge(ch[x][1],y);
        update(x);
        return x;
    }
    else{
        ch[y][0]=merge(x,ch[y][0]);
        update(y);
        return y;
    }
}
int tmp=-1;
inline void find(int now,int a){
    while(now!=0){
        tmp=val[now];
        now=ch[now][0];
    }
    return;
}
int main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        a[i].a=read();
        a[i].b=read();
    }
    for(int i=1;i<=m;i++){
        b[i].a=read();
        b[i].b=read();
    }
    sort(a+1,a+1+n,cmp);
    sort(b+1,b+1+m,cmp);
    int j=1;
    for(int i=1;i<=n;i++){
        tmp=-1;
        while(b[j].b>=a[i].b&&j<=m){
            split(root,b[j].a,x,y);
            root=merge(merge(x,new_node(b[j].a)),y);
            j++;//插入
        }
        split(root,a[i].a-1,x,y);
        find(y,a[i].a);
        root=merge(x,y);//寻找
        if(tmp==-1){
            puts("-1");
            return 0;
        }
        ans+=tmp;
        split(root,tmp,x,z);
        split(x,tmp-1,x,y);
        y=merge(ch[y][0],ch[y][1]);
        root=merge(merge(x,y),z);//删除
    }
    cout<<ans;
}
```
常数惨不忍睹...

---

## 作者：zhzh2001 (赞：2)

## 思路


应该可以发现，这题可以用贪心。有两个值需要满足比较麻烦，我们考虑对询问和牧草按照口感（绿色值）排序。这样，对于一个询问(Ai,Bi)，只要从口感大于等于Bi的牧草中选出价格最小的且大于等于Ai的牧草，这样可以证明是最优的。如果没有符合条件的牧草，就是无解。


用multiset来维护牧草的价格很方便，支持所有操作，当然价格可以重复。时间复杂度$O(N\log N)$


## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
pair<int,int> cow[N],grass[N];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>cow[i].second>>cow[i].first;
    sort(cow+1,cow+n+1);
    for(int i=1;i<=m;i++)
        cin>>grass[i].second>>grass[i].first;
    sort(grass+1,grass+m+1);
    multiset<int> S;
    int j=m;
    long long ans=0;
  //注意用64位整数保存结果
    for(int i=n;i;i--)
    {
        for(;j&&grass[j].first>=cow[i].first;j--)
            S.insert(grass[j].second);
      //插入口感满足要求的牧草
        multiset<int>::iterator it=S.lower_bound(cow[i].second);
      //找到第一个价格的大于等于Ai的牧草
        if(it==S.end())
        {
            cout<<-1<<endl;
            return 0;
        }
        ans+=*it;
        S.erase(it);
      //别忘了删除
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：peixiaorui (赞：1)

## 思路
贪心。

因为所选的草的口感要大于等于奶牛要求，所以考虑以口感为关键字从大到小排序。因为要求价格最少，每一次选择符合条件的且价格最少的即可。

价格最少可以考虑用 `multiset` 维护。每一次加入所有新鲜度满足要求的，查找符合要求且价格最少的，记录答案并删除。没找到符合要求的输出 `-1` 即可。
因为按照新鲜度从高到低排序过，所以先加入的新鲜度一定满足后面的需求。

## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define ll long long
struct node{
	int a,b;//a为价格，b为新鲜度
}a[100100],b[100100];//a为牧草，b为奶牛
bool cmp(node x,node y){
	return x.b>y.b;
}
int main(){
	int n,m;cin>>n>>m;
	fo(i,1,n)cin>>a[i].a>>a[i].b;
	fo(i,1,m)cin>>b[i].a>>b[i].b;
	sort(a+1,a+n+1,cmp),sort(b+1,b+m+1,cmp);//按新鲜度排序
	int s=1;ll ans=0;
	multiset<int> mu;
	fo(i,1,n){
		while(s<=m&&b[s].b>=a[i].b)mu.insert(b[s++].a);//加入所有满足要求的
		multiset<int> ::iterator it=mu.lower_bound(a[i].a);
		if(mu.empty()||it==mu.end()){cout<<-1<<endl;return 0;}//没找到
		ans+=*it;
		mu.erase(it);//记录答案并删除
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：phmaprostrate (赞：1)

## 题意分析
此题限制条件较多，一眼看上去很懵，但知道一个原则，尽可能在满足牛的需求的情况下使价格最小。

我们考虑先将牛对草的新鲜程度和草的新鲜程度递减排序。

因为在价格相同时，新鲜程度对答案的最小限制没有影响，所以应该把最新鲜的草给要求最高的奶牛。

然后，新鲜程度在奶牛之前的是可以选择的，选择价格最小的即可。这样不会对之后的奶牛产生影响，因为奶牛之前的草都是满足要求的。

最后，查找过程可以用 $stl$ 来实现，对于可能有重复元素的序列要用可以存重复的队列。

一定要开 $long\ long$！
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
int n,m,ans = 0;
struct node{
    int deli,pri;
}a[N],b[N];//a 为牛数组，b 为草数组
multiset<int> p;
bool cmp(node aa,node bb){
    return aa.deli > bb.deli;
}//排序
signed main(){
   cin >> n >> m;
    for(int i = 1;  i <= n; i ++) cin >> a[i].pri >> a[i].deli;
    for(int i = 1; i <= m ; i ++) cin >> b[i].pri >> b[i].deli;
   sort(a + 1,a + 1 + n,cmp);
   sort(b + 1,b + 1 + m,cmp);
   int id = 1;
    for(int  i = 1 ; i <= n ; i ++){
        while(id <= m && b[id].deli >= a[i].deli){
                   p.insert(b[id++].pri);
        }//把符合的加入集合
        multiset<int>::iterator it = p.lower_bound(a[i].pri);//返回的是迭代器
        if(it == p.end()){cout << -1;return 0;}
        else {
            ans += *it;
            p.erase(it);
        } 
    }
     cout << ans;
}
```


---

## 作者：limi_sanhua (赞：1)

写此题时并不会multiset，就写了个树状数组

先把100,000,000的数据**离散化**了，最多就对映到1-200,000（理由见数据范围

开**权值树状数组**，即1-200,000的范围

排序后**贪心**思路是一样的，查询第1个大于等于是什么数时就**二分**

初始区间为

左端点：当前奶牛花钱最小值

右端点：N+M

树状数组查询区间**是否有数**（即**区间和**），有数就缩小右端点（区间和**不为零**），否则增大左端点

**无解**情况就是有一头奶牛**初始区间和为0**

不过multiset，确实方便许一些，~~而且快得多~~

```cpp
#include<iostream>
#include<cstdio>

#define ri register int
#define u long long

namespace opt {

	inline u in() {
		u x(0),f(1);
		char s(getchar());
		while(s<'0'||s>'9') {
			if(s=='-') f=-1;
			s=getchar();
		}
		while(s>='0'&&s<='9') {
			x=(x<<1)+(x<<3)+s-'0';
			s=getchar();
		}
		return x*f;
	}

}

using opt::in;

#define NN 200005

#include<algorithm>

namespace mainstay {

	u N,M,ans(0),now(1),t[NN],cnt,len,pre[NN],w[NN<<1];

	struct node {
		u x,y;
	} a[NN],b[NN];

	void add(const u &x,const u &y) {
		for(ri i(x); i<=N+M; i+=i&-i) t[i]+=y;
	}

	u ask(const u &x) {
		u _re(0);
		for(ri i(x); i>=1; i-=i&-i) _re+=t[i];
		return _re;
	}

	inline bool cmp(const node &x,const node &y) {
		return x.y>y.y;
	}

	void li_sanhua() {
		cnt=0;
		for(ri i(1); i<=N; ++i) w[++cnt]=a[i].x;
		for(ri i(1); i<=M; ++i) w[++cnt]=b[i].x;
		std::sort(w+1,w+cnt+1),len=std::unique(w+1,w+cnt+1)-w-1;
		for(ri i(1); i<=N; ++i) pre[std::lower_bound(w+1,w+len+1,a[i].x)-w]=a[i].x;
		for(ri i(1); i<=M; ++i) pre[std::lower_bound(w+1,w+len+1,b[i].x)-w]=b[i].x;
		for(ri i(1); i<=N; ++i) a[i].x=std::lower_bound(w+1,w+len+1,a[i].x)-w;
		for(ri i(1); i<=M; ++i) b[i].x=std::lower_bound(w+1,w+len+1,b[i].x)-w;
		cnt=0;
		for(ri i(1); i<=N; ++i) w[++cnt]=a[i].y;
		for(ri i(1); i<=M; ++i) w[++cnt]=b[i].y;
		std::sort(w+1,w+cnt+1),len=std::unique(w+1,w+cnt+1)-w-1;
		for(ri i(1); i<=N; ++i) a[i].y=std::lower_bound(w+1,w+len+1,a[i].y)-w;
		for(ri i(1); i<=M; ++i) b[i].y=std::lower_bound(w+1,w+len+1,b[i].y)-w;
	}

	inline void solve() {
		N=in(),M=in();
		for(ri i(1); i<=N; ++i) a[i].x=in(),a[i].y=in();
		for(ri i(1); i<=M; ++i) b[i].x=in(),b[i].y=in();
		li_sanhua(),std::sort(a+1,a+N+1,cmp),std::sort(b+1,b+M+1,cmp);
		for(ri i(1); i<=N; ++i) {
			while(b[now].y>=a[i].y) add(b[now].x,1),++now;
			u _re,_l(a[i].x),_r(N+M);
			if(!(ask(_r)-ask(_l-1))) {
				printf("-1");
				return;
			}
			while(_l<=_r) {
				u mid(_l+_r>>1);
				if((ask(mid)-ask(_l-1))>0) _r=mid-1,_re=mid;
				else _l=mid+1;
			}
			ans+=pre[_re],add(_re,-1);
		}
		std::cout<<ans;
	}

}

int main() {

	//freopen("food.in","r",stdin);
	//freopen("food.out","w",stdout);
	std::ios::sync_with_stdio(false);
	mainstay::solve();

}
```


---

## 作者：ZBH_123 (赞：0)

## 题目分析
### 思路
对于本题，我们可以维护一个集合，这个集合里的东西就是满足奶牛们口感需求的牧草所需要的价格，每次给一头奶牛买牧草时，就在集合里查找满足这头奶牛价格需求的价格最低的牧草。如果找不到，就代表无解。那么，如何快速的将满足口感需求的牧草放进集合里呢？我们可以先将奶牛和牧草按口感排序，这样，满足前面的奶牛口感需求的牧草一定满足后面的奶牛的口感需求。
### 代码实现
对于存放牧草价格的集合，由于两份牧草的价格有可能相同，所以我们不能用 `set`，而是使用 `multiset`。在集合中寻找满足价格需求的牧草使可以使用 `lower_bound`，在找到后将这份牧草从集合中删除。

**AC code：**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1e5;
int n,m,k;
ll ans;
multiset<ll>st;
struct node{
	ll a,b;
}c[maxn+5],g[maxn+5];
bool cmp(node x,node y){
	return x.b>y.b;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>c[i].a>>c[i].b;
	}
	for(int i=1;i<=m;i++){
		cin>>g[i].a>>g[i].b;
	}
	sort(c+1,c+n+1,cmp);
	sort(g+1,g+m+1,cmp);
	for(int i=1;i<=n;i++){
		for(int j=k+1;j<=m;j++){
			if(g[j].b<c[i].b){
				break;
			}
			st.insert(g[j].a);
			k=j;
		}
		multiset<ll>::iterator it=st.lower_bound(c[i].a);
		if(it==st.end()){
			cout<<-1;
			return 0;
		}
		ans+=(*it);
		st.erase(it);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ZnPdCo (赞：0)

先看数据范围，很大概率为 $\mathcal{O}(n\log n)$，所以我们考虑一个神奇的数据结构。

像其它题解一样，我们考虑贪心。我们先把草和牛按照口感从大到小排序，然后依次遍历。在遍历到草的时候，我们把它加进一个数据结构。在遍历到一个牛的时候，比它所要求的口感还要低的草还没有遍历到，这样就可以确保口感是比所要求的大。我们再找这个牛的价格后继，因为是后继，我们就可以保证总价格最小。

有什么数据结构可以做到在规定的时间复杂度且能够找到后继呢？

~~平衡树？！~~

不，**权值线段树**（绝对不是因为我只会这个）。

我们知道，权值线段树能够区间求和（$\text{query}$）、查找第 k 大问题（$\text{kth}$）。怎么用它解决找后继（一个区间有值的最左端）呢？

假设我们要找 $x$ 的后继，那么我们先可以求出 $k=\text{query}(1,x - 1)$（$1$ 到 $x-1$ 的区间和），然后求 $\text{kth}(k+1)$，这样就可以实现找到一个数的后继。

那么其他的就很好打了吧？不过记得离散化。

---

我打完题解才发现，我的代码没有判断 `-1`。

我竟然过了？？？！！！！

然后怎么判 `-1` 呢？

就是我们在查询第 k 大时，返回前顺便判断是否有值，有值就是对的，没有值就输出 `-1`。

```c++
#include <cstdio>
#include <algorithm>
using namespace std;
#define ll long long
#define ls(x) (x << 1)
#define rs(x) ((x << 1) | 1)
struct node {
    ll a, b;
    bool isCow;
    friend bool operator == (const node &x, const node &y) {
        return x.a == y.a;
    }
    friend bool operator < (const node &x, const node &y) {
        return x.a < y.a;
    }
    friend bool operator > (const node &x, const node &y) {
        return x.a > y.a;
    }
} c[200010], g[200010];
ll t[800010];
ll zip[200010];
ll n, m;
ll mx;
ll ans;
bool cmp(node x, node y) {
    return x.a < y.a;
}
bool cmp2(node x, node y) {
    if(x.b == y.b) return x.a > y.a;
    return x.b > y.b;
}

void push_up(ll pos) {
    t[pos] = t[ls(pos)] + t[rs(pos)];
}

void update(ll x, ll l, ll r, ll pos, ll k) {
    if(l == x && r == x) {
        t[pos] += k;
        return;
    }
    ll mid = (l + r) >> 1;
    if(l <= x && x <= mid) update(x, l, mid, ls(pos), k);
    if(mid < x && x <= r) update(x, mid + 1, r, rs(pos), k);
    push_up(pos);
}

ll query(ll nl, ll nr, ll l, ll r, ll pos) {
    if(nl <= l && r <= nr) {
        return t[pos];
    }
    ll mid = (l + r) >> 1;
    ll res = 0;
    if(nl <= mid)
        res += query(nl, nr, l, mid, ls(pos));
    if(mid < nr)
        res += query(nl, nr, mid + 1, r, rs(pos));
    return res;
}

ll kth(ll k, ll l, ll r, ll pos) {
    if(l == r) {
		if(t[pos] == 0) return -1;
		return l;
	}
    ll mid = (l + r) >> 1;
    if(t[ls(pos)] >= k) return kth(k, l, mid, ls(pos));
    return kth(k - t[ls(pos)], mid + 1, r, rs(pos));
}

int main() {
    scanf("%lld %lld", &n, &m);
    for(int i = 1; i <= n; i++) {
        scanf("%lld %lld", &c[i].a, &c[i].b);
        c[i].isCow = true;
        g[i] = c[i];
    }
    for(int i = 1; i <= m; i++) {
        scanf("%lld %lld", &c[i + n].a, &c[i + n].b);
        c[i + n].isCow = false;
        g[i + n] = c[i + n];
    }




	// 离散化
    sort(g + 1, g + 1 + n + m, cmp);
    ll e = unique(g + 1, g + 1 + n + m) - g - 1;
    for(ll i = 1; i <= n + m; i++) {
        ll to = lower_bound(g + 1, g + 1 + e, c[i]) - g;
        zip[to] = c[i].a;
        c[i].a = to;
        mx = max(mx, c[i].a);
    }




    sort(c + 1, c + 1 + n + m, cmp2);
    for(int i = 1; i <= n + m; i++) {
        if(c[i].isCow) {
            ll cnt = 0;
			if(c[i].a > 1)
				cnt = query(1, c[i].a - 1, 1, mx, 1);
            ll res = kth(cnt + 1, 1, mx, 1);

			if(res == -1) {
				printf("-1");
				return 0;
			}


            ans += zip[res];
            update(res, 1, mx, 1, -1);
        } else {
            update(c[i].a, 1, mx, 1, 1);
        }
    }



    printf("%lld", ans);
}
```

---

