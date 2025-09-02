# Sum of Medians

## 题目描述

In one well-known algorithm of finding the $ k $ -th order statistics we should divide all elements into groups of five consecutive elements and find the median of each five. A median is called the middle element of a sorted array (it's the third largest element for a group of five). To increase the algorithm's performance speed on a modern video card, you should be able to find a sum of medians in each five of the array.

A sum of medians of a sorted $ k $ -element set $ S={a_{1},a_{2},...,a_{k}} $ , where $ a_{1}&lt;a_{2}&lt;a_{3}&lt;...&lt;a_{k} $ , will be understood by as

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF85D/ade3397df6e8978ddadfc100b4ccb88beefd1e3f.png)The ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF85D/99fd5677ca5c02520be7595d9b1eaf3e9972e601.png) operator stands for taking the remainder, that is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF85D/cb1d84ad58154eb7ea26b65d1ae0039570db9bb6.png) stands for the remainder of dividing $ x $ by $ y $ .

To organize exercise testing quickly calculating the sum of medians for a changing set was needed.

## 样例 #1

### 输入

```
6
add 4
add 5
add 1
add 2
add 3
sum
```

### 输出

```
3
```

## 样例 #2

### 输入

```
14
add 1
add 7
add 2
add 5
sum
add 6
add 8
add 9
add 3
add 4
add 10
sum
del 1
sum
```

### 输出

```
5
11
13
```

# 题解

## 作者：chenxia25 (赞：20)

>### [洛谷题目页面传送门](https://www.luogu.org/problem/CF85D) & [CodeForces题目页面传送门](https://codeforces.com/contest/85/problem/D)

>有一个集合$s$，你需要支持以下$3$种$q$次操作：
>1. $\texttt{add}\ x$：令$s=s\cup\{x\}$，保证在执行之前$x\notin s$，$x\in\left[1,10^9\right]$；
>2. $\texttt{del}\ x$：令$s=s-\{x\}$，保证在执行之前$x\in s$，$x\in\left[1,10^9\right]$；
>3. $\texttt{sum}$：设将$s$中所有元素排序后得到1-indexed序列$a$，查询$\sum\limits_{i\in[1,|a|],i\bmod5=3}a_i$。

>$q\in\left[1,10^5\right]$。

这其实是一个比较简单的DS题，毕竟难度只有$^*2200$。只不过这题比较nb，一题四解。

### 解法$1$：离散化+线段树

考虑建一棵值域线段树，设节点$i$表示区间$[l_i,r_i]$，那么节点$i$存储$[l_i,r_i]$内$\in s$的数的数量$cnt_i$，和$\forall j\in[0,5)$，区间$[l_i,r_i]$内所有$\in s$的元素排序后所有下标$\bmod5=j$的数的和$sum_{i,j}$。那么上传时令$cnt_i=cnt_{lson_i}+cnt_{rson_i},sum_{i,j}=sum_{lson_i,j}+sum_{rson_i,\left(j-cnt_{lson_i}\right)\bmod5}$即可。一次上传时间复杂度$\mathrm O(1)$。

由于值域大小为$10^9$，我们可以将所有操作离线下来并离散化所有数值。

此时$\texttt{add},\texttt{del}$操作都是简单的单点修改，$\mathrm O(\log q)$；$\texttt{sum}$操作是整体查询，直接调用$sum_{root,3}$即可，$\mathrm O(1)$。

总空间复杂度$\mathrm O(q)$，时间复杂度$\mathrm O(q\log q)$。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
const int QU=100000;
int qu;//操作数 
struct query{int tp,x;}qry[QU+1];//操作 
vector<int> nums;//离散化数组 
void discrete(){//离散化 
	sort(nums.begin(),nums.end());
	nums.resize(unique(nums.begin(),nums.end())-nums.begin());
	for(int i=1;i<=qu;i++)if(qry[i].tp!=2)qry[i].x=lower_bound(nums.begin(),nums.end(),qry[i].x)-nums.begin();
}
struct segtree{//线段树 
	struct node{int l,r,sum[5],cnt;}nd[QU<<2];
	#define l(p) nd[p].l
	#define r(p) nd[p].r
	#define sum(p) nd[p].sum
	#define cnt(p) nd[p].cnt
	void bld(int l=0,int r=(int)(nums.size())-1,int p=1){//建树 
		if(l>r)return;
		l(p)=l;r(p)=r;sum(p)[0]=sum(p)[1]=sum(p)[2]=sum(p)[3]=sum(p)[4]=cnt(p)=0;
		if(l==r)return;
		int mid=l+r>>1;
		bld(l,mid,p<<1);bld(mid+1,r,p<<1|1);
	} 
	void init(){bld();}//线段树初始化 
	void sprup(int p){//上传 
		cnt(p)=cnt(p<<1)+cnt(p<<1|1);
		for(int i=0;i<5;i++)sum(p)[i]=sum(p<<1)[i]+sum(p<<1|1)[(((i-cnt(p<<1))%5)+5)%5];
	}
	void add(int x,int p=1){//add操作 
		if(l(p)==r(p))return sum(p)[1]=nums[x],cnt(p)=1/*此数in s*/,void();
		int mid=l(p)+r(p)>>1;
		add(x,p<<1|(x>mid));
		sprup(p);
	}
	void del(int x,int p=1){//del操作 
		if(l(p)==r(p))return sum(p)[1]=cnt(p)=0/*此数notin s*/,void();
		int mid=l(p)+r(p)>>1;
		del(x,p<<1|(x>mid));
		sprup(p);
	}
	int _sum()/*sum操作*/{return nums.size()?sum(1)[3]:0;} 
}segt;
signed main(){
	cin>>qu;
	for(int i=1;i<=qu;i++){//离线 
		string tp;
		cin>>tp;
		if(tp=="add")qry[i].tp=0,cin>>qry[i].x,nums.pb(qry[i].x);
		else if(tp=="del")qry[i].tp=1,cin>>qry[i].x,nums.pb(qry[i].x);
		else qry[i].tp=2;
	}
	discrete();//离散化 
	segt.init();//线段树初始化 
	for(int i=1;i<=qu;i++){ 
		int tp=qry[i].tp,x=qry[i].x;
		if(tp==0)segt.add(x);
		else if(tp==1)segt.del(x);
		else cout<<segt._sum()<<"\n";
	}
	return 0;
}
```

### 解法$2$：动态开点线段树

线段树部分的思路与解法$1$完全一样，不过此方法利用动态开点来处理值域过大问题，实现了在线执行操作。

总空间复杂度$\mathrm O(q\log q)$，时间复杂度$\mathrm O(q\log q)$。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int QU=100000,A_I=1000000000,LOG_A_I=30;
int qu;//操作数 
struct segtree{//动态开点线段树 
	int sz;//点数 
	struct node{int l,r,lson,rson,sum[5],cnt;}nd[QU*LOG_A_I+1];
	#define l(p) nd[p].l
	#define r(p) nd[p].r
	#define lson(p) nd[p].lson
	#define rson(p) nd[p].rson
	#define sum(p) nd[p].sum
	#define cnt(p) nd[p].cnt
	int nwnd(int l=1,int r=A_I){return nd[++sz]=node({l,r,0,0,{0,0,0,0,0},0}),sz;}//新建节点 
	void init(){nd[0]=node({0,0,0,0,{0,0,0,0,0},0});sz=0;nwnd();}//线段树初始化 
	void sprup(int p){//上传 
		cnt(p)=cnt(lson(p))+cnt(rson(p));
		for(int i=0;i<5;i++)sum(p)[i]=sum(lson(p))[i]+sum(rson(p))[(((i-cnt(lson(p)))%5)+5)%5];
	}
	void add(int x,int p=1){//add操作 
		if(l(p)==r(p))return sum(p)[1]=x,cnt(p)=1/*此数in s*/,void();
		int mid=l(p)+r(p)>>1;
		if(x<=mid)add(x,lson(p)=lson(p)?lson(p):nwnd(l(p),mid));
		else add(x,rson(p)=rson(p)?rson(p):nwnd(mid+1,r(p)));
		sprup(p);
	}
	void del(int x,int p=1){//del操作 
		if(l(p)==r(p))return sum(p)[1]=cnt(p)=0/*此数notin s*/,void();
		int mid=l(p)+r(p)>>1;
		if(x<=mid)del(x,lson(p)=lson(p)?lson(p):nwnd(l(p),mid));
		else del(x,rson(p)=rson(p)?rson(p):nwnd(mid+1,r(p)));
		sprup(p);
	}
	int _sum()/*sum操作*/{return sum(1)[3];} 
}segt;
signed main(){
	cin>>qu;
	segt.init();//线段树初始化 
	while(qu--){
		string tp;int x;
		cin>>tp;
		if(tp=="add")cin>>x,segt.add(x);
		else if(tp=="del")cin>>x,segt.del(x);
		else cout<<segt._sum()<<"\n";
	}
	return 0;
}
```

### 解法$3$：分块

~~分块是无所不能的~~

其实上面那句话在某种程度上是正确的

考虑对$s$中所有元素排序后得到的1-indexed序列$a$分块。由于有插入、删除操作，所以这是一个动态调整块内元素的分块。

考虑维护`set`$s$。块$i$内存$a$的某一个子段$a'_i$，和$\forall j\in[0,5)$，该1-indexed子段$a'_i$内所有下标$\bmod5=j$的数的和$sum_{i,j}$。

扫描：调整所有块内元素使得每块内元素数量不超过$sz1$。从左往右依次扫描每个块$i$，如果$|a'_i|>sz1$（此时必然有$|a'_i|=sz1+1$，因为每次$\texttt{add}$操作之后都进行扫描），那么将$a'_{i,|a'_i|}$放到$a'_{i+1}$的前面，并$\mathrm O(1)$重算$sum_i,sum_{i+1}$。由于要在两端操作，所以$a'_i$应该定义为`deque<int>`。时间复杂度$\mathrm O\!\left(\dfrac q{sz1}\right)$。

对于$\texttt{add}$操作：通过$s$二分找到距离$x$最近的$\in s$的元素$x'$，找到$x'$所在块并将$x$插入该块且维护有序性。暴力重算该块内的$sum$。更新$s$。扫描一遍。时间复杂度$\mathrm O\!\left(\log q+sz1+\dfrac q{sz1}\right)$。

对于$\texttt{del}$操作：找到$x$所在块并将$x$删除。暴力重算该块内的$sum$。更新$s$。扫描一遍。时间复杂度$\mathrm O\!\left(sz1+\dfrac q{sz1}\right)$。

对于$\texttt{sum}$操作：从左往右让每个块贡献答案即可，这样是$\mathrm O\!\left(\dfrac q{sz1}\right)$的。然鹅其实可以优化到$\mathrm O(1)$，就是每次扫描时顺便算出答案并记录下来，这样就可以直接调用。

令$sz1=\left\lfloor \sqrt q\right\rfloor$，这样总时间复杂度$\mathrm O(q\sqrt q)$。空间复杂度$\mathrm O(q)$。

然后开开森森的交上去，T了？是因为这巨大的复杂度乘上巨大的常数。于是开始卡常。

先将$\texttt{add},\texttt{del}$内的“暴力重算该块内的$sum$”用指针寻址优化一下（因为`deque`的随机访问很慢）。此时$\texttt{add},\texttt{del}$前面一部分的常数与最后的扫描的常数形成了鲜明的对比，因为扫描还带一个$5$的常数。于是调参要从娃娃抓起，我们将$sz1$稍微调大一点，来实现常数上的尽量平衡。令$sz1=3\left\lfloor \sqrt q\right\rfloor$即可AC。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pf push_front
#define ppb pop_back
#define pb push_back
const int QU=100000,DB_SZ=500;
int qu;
struct dvdblk{//分块 
	int sz1,ans/*任意时刻的答案*/;
	struct block{
		deque<int> a;int sum[5];
		block(){sum[0]=sum[1]=sum[2]=sum[3]=sum[4]=0;}
	}blk[DB_SZ];
	#define a(p) blk[p].a
	#define sum(p) blk[p].sum
	set<int> all;
	void init(){ans=0;sz1=3*sqrt(qu);}//分块初始化 
	void scn(){//扫描 
		int now=0;
		ans=0;
		for(int i=1;i<=(qu+sz1-1)/sz1;i++){
			if(a(i).size()>sz1){
				a(i+1).pf(a(i).back());//将此块的最后一个元素放到后面一块 
				int tmp[]={sum(i+1)[0],sum(i+1)[1],sum(i+1)[2],sum(i+1)[3],sum(i+1)[4]};
				for(int j=0;j<5;j++)sum(i+1)[j]=tmp[(j-1+5)%5];
				sum(i+1)[1]+=a(i+1)[0];//O(1)调整sum[i+1] 
				sum(i)[a(i).size()%5]-=a(i).back();//O(1)调整sum[i] 
				a(i).ppb();//将此块的最后一个元素放到后面一块  
			}
			ans+=sum(i)[((3-now)%5+5)%5];//计算当前的答案 
			now+=a(i).size();
		}
	}
	void add(int x){//add操作 
		if(all.empty())a(1).pb(x),sum(1)[1]=x;//特判s为空的情况 
		else{
			set<int>::iterator fd=all.lower_bound(x);
			if(fd==all.end())fd--;
			int p;
			for(int i=1;;i++)if(a(i)[0]<=*fd&&*fd<=a(i).back()){p=i;break;}//找到即将插入的块 
			a(p).insert(lower_bound(a(p).begin(),a(p).end(),x),x);//插入 
			sum(p)[0]=sum(p)[1]=sum(p)[2]=sum(p)[3]=sum(p)[4]=0;
			int now=1;
			deque<int>::iterator end=a(p).end();
			for(deque<int>::iterator i=a(p).begin();i!=end;++i,++now,now==5&&(now=0))sum(p)[now]+=*i;//暴力重算sum[p]（寻址优化后） 
		}
		all.insert(x);//维护s 
		scn();//扫描 
	}
	void del(int x){//del操作 
		int p;
		for(int i=1;;i++)if(a(i)[0]<=x&&x<=a(i).back()){p=i;break;}//找到即将插入的块 
		a(p).erase(lower_bound(a(p).begin(),a(p).end(),x));//删除 
		sum(p)[0]=sum(p)[1]=sum(p)[2]=sum(p)[3]=sum(p)[4]=0;
		int now=1;
		deque<int>::iterator end=a(p).end();
		for(deque<int>::iterator i=a(p).begin();i!=end;++i,++now,now==5&&(now=0))sum(p)[now]+=*i;//暴力重算sum[p]（寻址优化后） 
		all.erase(x);//维护s 
		scn();//扫描 
	}
	int _sum()/*sum操作*/{return ans;}
}db;
signed main(){
	cin>>qu;
	db.init();//分块初始化 
	for(int i=1;i<=qu;i++){ 
		string tp;int x;
		cin>>tp;
		if(tp=="add")cin>>x,db.add(x);
		else if(tp=="del")cin>>x,db.del(x);
		else cout<<db._sum()<<"\n";
	}
	return 0;
}
```

### 解法$4$：平衡树

看到往集合里添加、删除，不难想到平衡树。这里使用fhq-Treap。

节点$i$存储此节点的权值$v_i$，以$i$为根的子树的大小$sz_i$，和$\forall j\in[0,5)$，以$i$为根的子树内所有元素排序后所有下标$\bmod5=j$的数的和$sum_{i,j}$。那么上传时令$sz_i=sz_{lson_i}+1+sz_{rson_i},sum_{i,j}=sum_{lson_i,j}+[j=sz_{lson_i}+1]v_i+sum_{rson_i,\left(j-cnt_{lson_i}-1\right)\bmod5}$即可。一次上传时间复杂度$\mathrm O(1)$。

此时$\texttt{add},\texttt{del}$操作都是简单的单点插入/删除，$\mathrm O(\log q)$；$\texttt{sum}$操作是整体查询，直接调用$sum_{root,3}$即可，$\mathrm O(1)$。

总空间复杂度$\mathrm O(q)$，时间复杂度$\mathrm O(q\log q)$。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define mp make_pair
#define X first
#define Y second
mt19937 rng(20060617/*信仰优化*/);
const int QU=100000;
int qu;//操作数
struct fhq_treap{//fhq-Treap 
	int sz/*点数*/,root/*根*/;
	struct node{unsigned key;int lson,rson,sz,v,sum[5];}nd[QU+1];
	#define key(p) nd[p].key
	#define lson(p) nd[p].lson
	#define rson(p) nd[p].rson
	#define sz(p) nd[p].sz
	#define v(p) nd[p].v
	#define sum(p) nd[p].sum
	void init(){nd[sz=root=0]=node({0,0,0,0,0,{0,0,0,0,0}});}//fhq-Treap初始化 
	void sprup(int p){//上传 
		sz(p)=sz(lson(p))+1+sz(rson(p));
		for(int i=0;i<5;i++)sum(p)[i]=sum(lson(p))[i]+sum(rson(p))[(((i-sz(lson(p))-1)%5)+5)%5];
		sum(p)[(sz(lson(p))+1)%5]+=v(p);
	}
	pair<int,int> split(int x,int p=-1){~p||(p=root); 
		if(!x)return mp(0,p);
		pair<int,int> sp;
		if(x<=sz(lson(p)))return sp=split(x,lson(p)),lson(p)=sp.Y,sprup(p),mp(sp.X,p);
		return sp=split(x-sz(lson(p))-1,rson(p)),rson(p)=sp.X,sprup(p),mp(p,sp.Y);
	}
	int mrg(int p,int q){
		if(!p||!q)return p|q;
		if(key(p)<key(q))return rson(p)=mrg(rson(p),q),sprup(p),p;
		return lson(q)=mrg(p,lson(q)),sprup(q),q;
	}
	int lss(int v,int p=-1/*比v小的数的个数*/){~p||(p=root); 
		if(!p)return 0;
		if(v(p)<v)return sz(lson(p))+1+lss(v,rson(p));
		return lss(v,lson(p));
	}
	int nwnd(int v){return nd[++sz]=node({rng(),0,0,1,v,{0,v,0,0,0}}),sz;}//新建节点 
	void add(int v){//add操作 
		pair<int,int> sp=split(lss(v));
		root=mrg(mrg(sp.X,nwnd(v)),sp.Y);
	}
	void del(int v){//del操作 
		pair<int,int> sp=split(lss(v)),sp0=split(1,sp.Y);
		root=mrg(sp.X,sp0.Y);
	}
	int _sum()/*sum操作*/{return sum(root)[3];}
}trp;
signed main(){
	cin>>qu;
	trp.init();//fhq-Treap初始化 
	while(qu--){
		string tp;int x;
		cin>>tp;
		if(tp=="add")cin>>x,trp.add(x);
		else if(tp=="del")cin>>x,trp.del(x);
		else cout<<trp._sum()<<"\n";
	}
	return 0;
}
```

### $4$种解法的比较

||离散化+线段树|动态开点线段树|分块|平衡树|
|:-:|:-:|:-:|:-:|:-:|
|**操作相应时间**|离线|在线|在线|在线|
|**时间复杂度**|$\mathrm O(q\log q)$|$\mathrm O(q\log q)$|$\mathrm O(q\sqrt q)$|$\mathrm O(q\log q)$
|**空间复杂度**|$\mathrm O(q)$|$\mathrm O(q\log q)$|$\mathrm O(q)$|$\mathrm O(q)$
|**最慢的点运行时长**|$996\mathrm{ms}$|$1340\mathrm{ms}$|$2494\mathrm{ms}$|$1746\mathrm{ms}$|

看起来平衡树全方位吊打其他所有解法，但是它的常数还是比不过线段树。

---

## 作者：Erin非陌 (赞：8)

原本与某人约定@lisuier是我写线段树她写vector的，但由于本人过于蒟蒻，对于那个超级麻烦的线段树无能为力，还是退而求其次，介绍一下vector的超级暴力写法(OI生涯第三次写vector纪念)

------------

先介绍一下将要用到的几个函数:
1.lower_bound：

在algorithm库里。

```cpp
int a[100001],n,x,pos;
pos=lower_bound(a+1,a+n+1,x)-a;
//括号里a+1,a+n+1是因为我的习惯是数组从1开始存,详情含义参见sort函数中的同样的一部分
```

当a数组为一个递增数组时将会返回第一个a[i]>=x的i（即上式中的pos）。

如果是vector写法为：
```cpp
lower_bound(v.begin(),v.end(),x)//(不必-v),但也不能int pos=lower_bound(v.begin(),v.end(),x);
```

2.vector中的insert函数

简而言之就是：

```cpp
//伪代码
vector<int>v;
v.insert(插入之后该数的下标/*即该数你想要插在哪里*/,要插入的那个数);
```

3.vector中的erase函数

还是直接上伪代码：

```cpp
vector<int>v;
v.erase(你想要删除的该数的下标);
```

------------

言归正传，回到这道题。说白了就是一个序列，add就是添加一个数，del就是删除一个数,sum让你求将该序列从小到大排序后所有v[i](i%5==3)的v[i]的和。
那么，就暴力吧。
用lower_bound查找出它的下标(或插入并排序后它的下标),然后insert或del.
查和更暴力一点：因为vector是从0开始的，那么跑个for循环,i=2;i<v.size();i+=5把每一个v[i]加起来，结束了。

------------

异常暴力的写法，时效还过得去……

------------

上代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
vector <int> v;
int n;
void solve(){
	scanf("%d",&n);
	while(n--){
		int x;
		char op[3];
		scanf("%s",op);
		if(op[0]=='a'){
			scanf("%d",&x);
			v.insert(lower_bound(v.begin(),v.end(),x),x);
		}
		if(op[0]=='d'){
			int x;
			scanf("%d",&x);
			v.erase(lower_bound(v.begin(),v.end(),x));
		}
		if(op[0]=='s'){
			long long ans=0;//一定要开long long，否则会卡在90分
			for(int i=2;i<v.size();i+=5)
					ans+=v[i];
			printf("%lld\n",ans);
		}
	}
}
int main(){
	solve();
	return 0;
}
```

------------

后记：
好暴力啊……不过能过。写的时候还是十分顺利的，卡了没几次：第一次是选择lower_bound或upper_bound；第二次是写vector的lower_bound；第三次是long long……
STL大赞！！！！！！！

---

## 作者：枉却东风 (赞：7)

### 某丁姓大佬在一个水班中提到了这一题花了一个小时终于艰难地用线段树a了qwq
### ~~然而写这篇狗屁不通的题解又花了一个小时~~
### 这道题应该一看就是可以用线段树的 问题是怎么维护每个数的下标mod5的值
### 那么先来思考一下插入一个数的时候其他数的下标的变化。我们会惊（xian）奇（ran）地发现只有比这个数大的数下标才会加一，比这个数小的数的下标是不会发生变化的~再深入思考一下，当一个数的坐标右移5位时与没有移一样！！！（MOD5的值一样嘛qwq）
### 又因为题目中说每个数加入集合时集合没有相同的数QAQ
## 所以我们可以用一个以五个单元为一个叶子节点的线段树维护这些数的下标MOD5的位置！
### 那五个单元存的是一个数当前下标mod5的情况这些单元在没有插入它对应大小的数时可以是空的
### （ex：当插入1时第一个叶子节点内情况：0，1，0，0，0，0；此时集合：1 
### 插入3时第二个叶子节点情况：0 ，0，3，0，0，0 此时集合：1，3  ~~当然在刚开始插进去的时候其实3在第一位这个要看代码~~）
### 那么我们再思考在线段树能怎么更新每个子节点因为前面插入的节点而移动的位数呢？
### 答案是引进数组num代表线段树中某节点的数向右移的位数。每插入一个数时维护该数的叶子节点num值加一（插入1时涵盖1的叶子节点0,1,0,0,0 num值加一），在一路回溯的过程中每个节点的num值都会被更新(线段树的pushup过程)
### 在回溯过程中通过num值维护当前节点下标mod5余i的数之和（左子树不发生移动，右子树当前下标mod5余i的数前位置应该等于i-左子树移动位数~~即左子树num~~）
### 至于为什么离线请看一下数据范围就懂了应该不用多说qwq
### 呼。。第一次发题解大概就是这样吧。。小渣滓请大佬们轻喷QAQ

```
#include <iostream>
#include <string.h>
#include<cstdlib>
#include <map>
#include <algorithm>
#define ll long long
using namespace std;
ll n,x;
ll tree[800005][6],add[400005],pan[400005],shu[400005];
ll num[800005];
char a[10];
map <ll,ll> id;
inline ll read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
ll ls(ll k)
{
	return k<<1;
}
ll rs(ll k)
{
	return k<<1|1;
}
void push_up(ll i)
{
	num[i]=num[ls(i)]+num[rs(i)];//更新右移位数
	for(ll j=0;j<=4;j++)
	{
		tree[i][j]=tree[ls(i)][j]+tree[rs(i)][((j-num[ls(i)])%5+5)%5];//更新当前下标余i的数之和
	}
 } 
inline void in(ll left,ll right,ll i,ll wei,ll wor,ll sum)
{
	if(left==right)
	{
		tree[i][1]+=wor;
		num[i]+=sum;
		return;//单点更新
	}
	else
	{
		ll mid=(left+right)/2;
		if(wei<=mid) in(left,mid,ls(i),wei,wor,sum);
		else in(mid+1,right,rs(i),wei,wor,sum);
		push_up(i);
	}
}
int main()
{
	ll cnt=0;
	n=read();
	for(ll i=1;i<=n;i++)
	{
		cin>>a;
		if(a[0]=='a') 
		{
		    x=read();
			add[++cnt]=x;
			shu[i]=x;
			pan[i]=1;
		}
		if(a[0]=='d')
		{
			x=read();
			shu[i]=x;
			pan[i]=-1;
		}
	 } //离线 
	 sort(add+1,add+cnt+1);
	 ll sum=1;
	 for(ll i=1;i<=cnt;i++)
	 {
	 	if(id[add[i]]==0) 
		 {
		 	id[add[i]]=sum;
	 		sum++;
	 	}
	 }//离散化 
	 for(ll i=1;i<=n;i++)
	 {
	 	if(pan[i]==0) printf("%lld\n",tree[1][3]);
	 	else
	 	{
	 		in(1,n,1,id[shu[i]],pan[i]*shu[i],pan[i]);
		 }
	 }
	 return 0;
}
```

---

## 作者：zrzluck99 (赞：3)

来一发十分暴力的做法

我们先来看 $add$ 操作，容易发现插入 $x$ 之后，在 $x$ 后面的节点排名 $\%5$ 都恰好增加了 $1$。

考虑对所有排名 $\%5$ 同余的节点各建一棵 $Treap$，这就相当于把每棵树在 $x$ 处分裂为 $A_i$ 和 $B_i$，并将 $B_i$ 整体后移一位。$del$ 操作同理，反过来就行了。

具体实现看代码：

---

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/* FHQ_Treap */

#define HIM 19260817
ll seed = HIM;
ll rnd() {seed ^= seed << 13; seed ^= seed >> 7; seed ^= seed << 5; return seed;}

#define M 3000007
ll val[M],sum[M],rd[M];
int sz[M],ch[M][2],tot=0;

#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
int newnode(ll v) {tot++; rd[tot] = rnd(); val[tot] = sum[tot] = v; lc(tot) = rc(tot) = 0; sz[tot] = 1; return tot;}
int pushup(int now) {sz[now] = sz[lc(now)] + sz[rc(now)] + 1; sum[now] = sum[lc(now)] + sum[rc(now)] + val[now];}
void split_size(int now,int k,int &x,int &y){
    if (!now) return void(x=y=0);
    if (sz[lc(now)]+1<=k) x = now, split_size(rc(now),k-sz[lc(now)]-1,rc(x),y); else y = now, split_size(lc(now),k,x,lc(y));
    pushup(now);
}
void split_val(int now,ll k,int &x,int &y){
    if (!now) return void(x=y=0);
    if (val[now]<=k) x = now, split_val(rc(now),k,rc(x),y); else y = now, split_val(lc(now),k,x,lc(y));
    pushup(now);
}
int merge(int x,int y){
    if (!x||!y) return x|y; int ret;
    if (rd[x]<rd[y]) ret = x, rc(ret) = merge(rc(x),y); else ret = y, lc(ret) = merge(x,lc(y));
    pushup(ret); return ret;
}

int T[5];

#define pre(x) (((x)+4)%5)
#define suc(x) (((x)+1)%5)

void add(ll x){
    int A[5],B[5],C[5],D[5];
    for (int i=0;i<5;i++) split_val(T[i],x,A[i],B[i]);
    for (int i=0;i<5;i++) split_size(A[i],sz[A[i]]-1,C[i],D[i]);
    int tmp = 0; for (int i=0;i<5;i++) tmp = val[D[i]]>val[D[tmp]]?i:tmp; tmp = suc(tmp); //找到插入位置
    for (int i=0;i<5;i++) A[i] = merge(C[i],D[i]); A[tmp] = merge(A[tmp],newnode(x)); //插入节点
    for (int i=0;i<5;i++) T[i] = merge(A[i],B[pre(i)]); //整体后移
}

void del(ll x){
    int A[5],B[5],C[5],D[5];
    for (int i=0;i<5;i++) split_val(T[i],x,A[i],B[i]);
    for (int i=0;i<5;i++) split_size(A[i],sz[A[i]]-1,C[i],D[i]);
    int tmp = 0; for (int i=0;i<5;i++) tmp = val[D[i]]>val[D[tmp]]?i:tmp; //找到删除位置
    for (int i=0;i<5;i++) A[i] = i==tmp?C[i]:merge(C[i],D[i]); //删除节点
    for (int i=0;i<5;i++) T[i] = merge(A[i],B[suc(i)]); //整体前移
}

ll getsum(){
    return sum[T[3]]; //由于按余数建树，直接算就好了
}

int n;

signed main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        char opt[10]; ll x;
        scanf("%s",opt);
        switch(opt[0]){
            case 'a' : scanf("%I64d",&x); add(x); break;
            case 'd' : scanf("%I64d",&x); del(x); break;
            case 's' : printf("%I64d\n",getsum()); break;
        }
    }
    return 0;
}

```


---

## 作者：Lily_White (赞：3)

~~所以这个题哪要什么数据结构啊暴力不就行了吗~~

我们教练布置了这个题后说了一句：

> 这个题可以用分块做，不过标准做法是线段树。

我：

> 完蛋我都写不对那我写暴力吧。

结果：

$$\large\color{limegreen}\text{Happy New Year!}$$

这个题的暴力思路其实很简单：

维护一个 ```std::vector```。

- 对于 `add` 操作，在 `vector` 中二分查找出应当插入的位置。

- 对于 `del` 操作，在 `vector` 中二分查找出应当删除的位置。

- 对于 `sum` 询问，在 `vector` 中暴力相加。

实际上，通过二分位置，我们保证了 `vector` 是始终有序的，因此直接找第三个加就可以了。

时间复杂度如下：

定义 $s$ 为此时集合的大小。

对于插入和删除操作：二分位置 $O(\log s)$，插入/删除最坏是 $O(s)$。整体最坏是 $O(s)$。

对于查询：直接相加$O(s)$。

总体最坏复杂度 $O(ns)$。但是 $s$ 的值在随机情况下是非常小的。插入的数的位置也通常不会在最前面。常数非常小。

CF 上的极限数据是 $10^5$ 个 `add` 操作。我的代码运行时间是 $1622ms$。作为参考，分块的 $O(n\sqrt{n})$ 做法运行时间大约在 $400ms$ 左右。线段树的 $O(n \log n)$ 做法大约在 $200 -300ms$。

代码如下：

```
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define pb push_back
#define mp make_pair
#define lsh(i) (1 << (i))
#define lshll(i) (1LL << (i))
#define repn(i, n) for (int (i) = 1; (i) <= (int)n; (i)++)
#define rep(i, n) for (int (i) = 0; (i) < (int)n; (i)++)
const int INF = 0x3f3f3f3f;
const long double EPS = 1e-6;
const int BL = 5;
const int N = 100010;
int size = 0;
vector <int> a;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	while (n--) {
		string op; cin >> op;
		if (op == "add") {
			int x;
			cin >> x;
			a.insert(lower_bound(a.begin(), a.end(), x), x);
		}
		else if (op == "del") {
			int x;
			cin >> x;
			a.erase(lower_bound(a.begin(), a.end(), x));
		}
		else if (op == "sum") {
			long long ans = 0;
			for (int i = 2; i < (int)a.size(); i += 5) ans += a[i];
			cout << ans << endl;
		}
	}
	return 0;
}
```

---

## 作者：幻影星坚强 (赞：1)

~~听说 @hater 用分块，然后瞄一眼题解没有操作分块，于是补一下。~~

首先我们直接扫一遍当前所有的值那么单次复杂度 $O(n)$ ，总复杂度 $O(nq)$，然后我们也可以将所有询问离线，预处理出每一个模后结果所对应位置的前缀和，之后对于两个相邻的被修改的值之间没有被修改过的值我们可以利用前缀和很快的算出，对于所有被修改的值我们暴力计算，单次复杂度 $O(n)$ ，总复杂度 $O(nq)$。

然后我们考虑每 $B$ 次操作重新扫一遍当前的值，这样我们重新扫单次复杂度 $O(n)$ ，总复杂度 $O(n\times\frac{q}{B})$，之后每次修改的值的位置就只有 $O(B)$ 个，于是我们可以单次 $O(B)$ 求出答案，总复杂度 $O(q\times B)$，理论上 $B = \sqrt{n}$ 最优，时间复杂度为 $O(n\sqrt{n})$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
const int block = 900;
int t, n;
int v[N], num;
int op[N], X[N];
long long qzh[N][5], sum[N];
int vis[N];
int now[block + 10];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++ i)
	{
		char now[10];
		cin >> now;
		if(now[0] == 'a')
		{
			op[i] = 1;
			cin >> X[i];
			v[++ num] = X[i];
		}
		else
		if(now[0] == 'd')
		{
			op[i] = 2;
			cin >> X[i];
		}
		else
		op[i] = 3;
	}
	sort(v + 1, v + 1 + num);
	int tot = unique(v + 1, v + 1 + num) - v - 1;
	for (int i = 1; i <= n; ++ i)
		X[i] = lower_bound(v + 1, v + 1 + tot, X[i]) - v;
	for (int l = 1; l <= n; l += block)
	{
		int r = min(n, l + block - 1);
		num = 0;
		for (int i = l; i <= r; ++ i)
		{
			if(op[i] <= 2)
			now[++ num] = X[i];
		}
		now[++ num] = tot + 1;
		sort(now + 1, now + 1 + num);
		num = unique(now + 1, now + 1 + num) - now - 1;
		for (int i = l; i <= r; ++ i)
		{
			if(op[i] == 1)
			{
				vis[X[i]] = 1;
			}
			if(op[i] == 2)
			{
				vis[X[i]] = 0;
			}
			if(op[i] == 3)
			{
				int zz = 0;
				long long ans = 0;
				for (int i = 1; i <= num; ++ i)
				{
					ans += qzh[now[i] - 1][(3 - zz % 5 + 5) % 5] - qzh[now[i - 1]][(3 - zz % 5 + 5) % 5];
					if(vis[now[i]] != sum[now[i]] - sum[now[i] - 1])
					{
						if(vis[now[i]] == 0)
						-- zz;
						else
						++ zz;
					}
					if(vis[now[i]])
					{
						if((sum[now[i]] + zz) % 5 == 3)
						ans += v[now[i]];
					}
				}
				cout << ans << "\n";
			}
		}
		for (int i = 1; i <= n; ++ i)
		{
			sum[i] = sum[i - 1] + vis[i];
			for (int j = 0; j < 5; ++ j)
			qzh[i][j] = qzh[i - 1][j];
			if(vis[i])
			qzh[i][sum[i] % 5] += v[i];
		}
	}
}
```


---

## 作者：XenonKnight (赞：1)

> Codeforces 85D

> - 维护一个集合 $S$
> - 支持插入和删除，和查询
> $$\sum_{i \bmod 5 =3} a_i$$
> $\quad\ \ $的值
> - 其中 $a$ 为 $S$ 排好序后的数组，下标从 $1$ 开始
> - 操作数不超过 $10^5$

欸好像没有 $\texttt{fhq-treap}$ 的题解，来发一篇。

看到这种插入删除的操作，又要支持排序，不难可以想到 $\texttt{fhq-treap}$ 的 $\texttt{split}$ 和 $\texttt{merge}$ 操作。按权值分裂应该是 $\texttt{fhq-treap}$ 的常规操作吧。

对于查询，我们对每个节点维护一个长度为 $5$ 的数组 $sum$，分别维护以当前节点为根，中序遍历中下标模 $5$ 余 $0,1,2,3,4$ 的值的和。发现这个 $sum$ 的更新只和它左右儿子的 $sum$ 和左子树大小有关，因此还需维护子树大小，这样更新就是常数级别的。查询的结果就是根节点的 $sum_2$ 的值。

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
struct node{
	int ind,sz,val,sum[5],ch[2],add_lz,key;
} s[100005];
int ncnt=0,root=0;
inline void pushup(int k){
	if(!k)	return;
	s[k].sz=s[s[k].ch[0]].sz+s[s[k].ch[1]].sz+1;
	fz(i,0,4){
		s[k].sum[i]=s[s[k].ch[0]].sum[i];
	}	
	s[k].sum[s[s[k].ch[0]].sz%5]+=s[k].val;
	fz(i,0,4){
		s[k].sum[(i+s[s[k].ch[0]].sz+1)%5]+=s[s[k].ch[1]].sum[i];
	}
}
inline void split(int k,int val,int &a,int &b){
	pushup(k);
	if(!k){
		a=b=0;
		return;
	}
	if(val<s[k].val){
		b=k;split(s[k].ch[0],val,a,s[k].ch[0]);
	}
	else{
		a=k;split(s[k].ch[1],val,s[k].ch[1],b);
	}
	pushup(a);
	pushup(b);
}
inline int merge(int a,int b){
	if(!a||!b)	return a+b;
	pushup(a);pushup(b);
	if(s[a].key<s[b].key){
		s[a].ch[1]=merge(s[a].ch[1],b);
		pushup(a);return a;
	}
	else{
		s[b].ch[0]=merge(a,s[b].ch[0]);
		pushup(b);return b;
	}
}
inline int newnode(int val,int ind){
	s[++ncnt].val=val;
	s[ncnt].key=rand()<<15|rand();
	s[ncnt].sum[ind%5]=val;
	s[ncnt].sz=1;
	return ncnt;
}
inline void insert(int val){
	int k1,k2;
	split(root,val,k1,k2);
	root=merge(merge(k1,newnode(val,s[k1].sz)),k2);
//	cout<<k1<<" "<<k2<<" "<<root<<" "<<s[root].sum[1]<<endl;
}
inline void del(int val){
	int k1,k2,k3;
	split(root,val-1,k1,k2);
	split(k2,val,k2,k3);
	root=merge(k1,k3);
}
signed main(){
	int T=read();
	while(T--){
		char opt[5];cin>>opt+1;
		if(opt[1]=='a'){
			int x=read();
			insert(x); 
		}
		if(opt[1]=='d'){
			int x=read();del(x);
		}
		if(opt[1]=='s'){
			cout<<s[root].sum[2]<<endl;
		}
	}
	return 0;
}
```

~~我为什么要写这么水的题的题解~~

---

## 作者：cirnovsky (赞：1)

## Description

让你维护一个类似std::set的东西，实现一个支持插入、删除、查询升序排序后的 $\sum_{i=1}^{n}[i\operatorname{mod}5=3]\times A_{i}$ 的不可重集合。

## Solution

正解线段树没跑。但是我们看到3S的时限 $10^{5}$ 的数据以及一贯的CF数据。我们有理由认为这道题vector模拟能过（滑稽

然后就真的能过，std::lower_bound查找插入以及删除的位置。查询的话就 $i$ 从2开始（vector下标从0开始，所以要减一），每次 $i=i+5$ 然后累加 $A_{i}$ 即可。

```cpp
#include <bits/stdc++.h>

std::vector < int > vect;

signed main() {
	int n;
	scanf("%d", &n);
	for (int i = 0, x; i < n; ++i) {
		char str[5];
		scanf("%s", str);
		if (*str == 'a') {
			scanf("%d", &x);
			vect.insert(std::lower_bound(vect.begin(), vect.end(), x), x);
		} else if (*str == 'd') {
			scanf("%d", &x);
			vect.erase(std::lower_bound(vect.begin(), vect.end(), x));
		} else {
			long long res = 0;
			for (unsigned i = 2; i < vect.size(); i += 5) res += vect[i];
			printf("%lld\n", res);
		}
	}
	return 0;
}
```

---

## 作者：hater (赞：1)

有一位巨佬说老师教了他们分块 布置了3道练习 

他说这道紫题太水了 以至于他不想写 之后就让窝来写呢

显然线段树贼好做 但是分块也很基础

思路 ： 

先把所有的操作的数读入 离散化 分块 

之后定义 $Sum_{i}$ 为第i块的贡献 

但是由于前面数的个数不同 产生的贡献也是不同的 

显然 在一个块的前面 有1个数 或是 6数 这个块的贡献是一样的

这个时候只需要再加一位 表示前面数的个数%5 

之后就很简单了 随手切 

```cpp
#include <bits/stdc++.h> 
#define Rg register 
#define MAX 100005 
#define LL long long  
#define MAXK 5005 
using namespace std ; 
int n , pos[MAX] , pio[MAXK] , p[MAX] , len , _n ; 
LL Sum[MAXK][5] , b[MAX] , Tot[MAXK] , All[MAX] ;   
struct Node { 
   int opt ;  LL num ; 
} a[MAX] ; 
void Add( LL A ) { 
   int t = lower_bound( b+1 , b+1+_n , A ) - b ; 
   int w = pos[t] ; Tot[w] ++ ;  All[t] = A ; 
   memset( Sum[w] , 0 , sizeof(Sum[w] ) ) ;  
   if( pio[w] == -1 || t < pio[w] ) p[t] = pio[w] , pio[w] = t ; 
   Rg int cnt = 3 ;  
   for( Rg int i = pio[w] ; ; ) { 
      if( i == -1 ) return ; 
   	  cnt = cnt == 0 ? 4 : cnt-1 ; 
   	  Sum[w][cnt] += All[i] ; 
   	  if( i < t && ( p[i] == -1 || t < p[i] ) ) 
   	    p[t] = p[i] , p[i] = t ; 
   	  i = p[i] ; 
   } return ; 
} 
void Del( LL A ) {  
   int t = lower_bound( b+1 , b+1+_n , A ) - b ; 
   int w = pos[t] ; Tot[w] -- ;  All[t] = 0 ; 
   memset( Sum[w] , 0 , sizeof(Sum[w] ) ) ; 
   if( t == pio[w] )   pio[w] = p[t] , p[t] = -1 ; 
   Rg int cnt = 3 ;  
   for( Rg int i = pio[w] ; ; ) { 
      if( i == -1 ) return ; 
   	  cnt = cnt == 0 ? 4 : cnt-1 ; 
   	  Sum[w][cnt] += All[i] ; 
   	  if( p[i] == t ) p[i] = p[t] , p[t] = -1 ;  
	  i = p[i] ;   
   } 
} 
LL Ask( ) {  
   int cnt = 0 ; LL Ans = 0 ; 
   for(Rg int i=1; i<=pos[_n] ; i++ )  
     Ans += Sum[i][cnt] , cnt = ( cnt+Tot[i] ) % 5 ; 
	return Ans ;  
} 
signed main() { string S ; 
  ios::sync_with_stdio(false) ; 
  cin.tie(0) ; cout.tie(0) ; 
  memset( p , -1 , sizeof(p) ) ; 
  memset( pio , -1 , sizeof(pio) ) ; 
  cin >> n ; 
  for(Rg int i=1; i<=n; i++) { 
    cin >> S  ;  
    if( S[0] == 's' ) a[i].opt = 3 ;  
    if( S[0] == 'a' ) a[i].opt = 1 , cin >> a[i].num , b[++len] = a[i].num ; 
    if( S[0] == 'd' ) a[i].opt = 2 , cin >> a[i].num ; 
  } sort( b+1 , b+1+len ) ; 
  _n = unique( b+1 , b+1+len ) -b-1 ; 
  Rg int block = sqrt( _n ) ; 
  for(Rg int i=1; i<=_n; i++) 
    pos[i] = (i-1)/block+1 ; 
  for(Rg int i=1; i<=n; i++) { 
    if( a[i].opt == 3 ) cout << Ask() << endl; 
    if( a[i].opt == 1 ) Add( a[i].num ) ; 
    if( a[i].opt == 2 ) Del( a[i].num ) ; 
  } 
  return 0 ; 
}
```




---

## 作者：vеctorwyx (赞：0)

## 值域线段树做法

~~[qvzeyang](https://www.luogu.com.cn/user/422299)说：“就这**题也能紫？顶多是个绿的！”~~

值域线段树（动态开点），每个点维护一个数组 $d[i][j](j \le 5)$，表示在点 $i$ 对应的区间内第 $k \times 5 + j (k \in   N)$ 个数的值的和。

#### 如何 pushup？

设当先处理到点 $x$ 了，左儿子记作 $ls$， 右儿子记作 $rs$， $sz[i]$ 表示 $i$ 对应区间内的点的个数。

先看 $ls$， 显然有 $d[x][j] = d[ls][j]$；

如果 $sz[ls] = 0$，直接有 $d[x][j] = d[rs][j]$；

如果 $sz[ls] = 1$，那么右儿子要空 4 个位置，有 $d[x][j] = d[ls][j] + d[rs][(j + 5) \mod 5]$；

如果 $sz[ls] = 2$，右儿子要空 3 个位置，有 $d[x][j] = d[ls][j] + d[rs][(j + 4) \mod 5]$；

依此类推。。。

易得 $d[x][j] = d[ls][j] + d[rs][(j + (6 - sz[ls] \mod 5) \mod 5) \mod 5] $。

剩下的就是个普普通通的值域线段树了。

code:

```
#include<bits/stdc++.h>
#define int long long
//#define ls(x) x << 1
//#define rs(x) x << 1 | 1
using namespace std;
int n, m, root;
char c[20];
int ch[2000010][2];
int d[2000010][6], cnt, sz[2000010];
void pushup(int x, int l, int r){//核心代码
	int rr = (6 - sz[ch[x][0]] % 5) % 5;
	for(int i = 1, j = rr; i <= 5; i++){
		d[x][i] = d[ch[x][0]][i] + d[ch[x][1]][j];
		j++;
		j %= 5;
	}
	d[x][0] = d[x][5];
	sz[x] = sz[ch[x][0]] + sz[ch[x][1]];
}
void add(int &x, int l, int r, int pl, int dat){
	if(!x)//动态开点
		x = ++cnt;
	if(l == r){
		d[x][1] = dat == 1 ? pl : 0;//注意别忘了删除操作
		sz[x] += dat;
		return;
	}
	int mid = l + r >> 1;
	if(pl <= mid)
		add(ch[x][0], l, mid, pl, dat);
	else
		add(ch[x][1], mid + 1, r, pl, dat);
	pushup(x, l, r);
}
signed main(){
	scanf("%lld", &n);
	while(n--){
		scanf("%s", c + 1);
		if(c[1] == 'a'){
			int x;
			scanf("%lld", &x);
			add(root, 1, 1000000000, x, 1);
		}
		else if(c[1] == 'd'){
			int x;
			scanf("%lld", &x);
			add(root, 1, 1000000000, x, -1);
		}
		else{
			printf("%lld\n", d[root][3]);
		}
	}
}
```

---

## 作者：FutaRimeWoawaSete (赞：0)

考虑维护的东西和排序后的下标在 $5$ 的模意义下有关。           

维护平衡树上每个节点，在当前子树内数排序生成的序列上的数的下标在模 $5$ 为 $[0,4]$ 时的和。           

然后任意两个儿子加上父亲可以以如下方式合并：

```cpp
void update(int x)
{
	fhq[x].siz = fhq[fhq[x].l].siz + fhq[fhq[x].r].siz + 1;
	for(int i = 0 ; i < 5 ; i ++) fhq[x].sum[i] = fhq[fhq[x].l].sum[i];
	for(int i = 0 ; i < 5 ; i ++) fhq[x].sum[(fhq[fhq[x].l].siz + 1 + i) % 5] += fhq[fhq[x].r].sum[i];
	fhq[x].sum[(fhq[fhq[x].l].siz + 1) % 5] += fhq[x].val;
}
```

然后就做完了，时间复杂度 $O(n \log n)$。



---

## 作者：Night_Bringer (赞：0)

# 前言
[博客园体验更佳](https://www.cnblogs.com/C202202chenkelin/p/15002494.html)

[题目链接：CodeForces](https://codeforces.com/problemset/problem/85/D)

码完之后去看题解，代码都好短……

终于没有用快读啦~
# 题意
对于一个初始为空的集合，有三种操作：
1. add：向集合里加入数 $x$ ，保证加入前集合中没有数 $x$ ；
2. del：从集合中删除数 $x$ ，保证删除前集合中有 $x$ ；
3. sum：询问将集合里的数从小到大排序后，求下标 $i$ 满足 $5$ 余 $3$ 的数的和。

现有 $n$ 次操作，对于每个查询操作，输出答案。
# 思路
看到插入、删除、区间操作而且不考虑序列的顺序，首先就想到了平衡树（splay）。

先来说 splay 中节点包含的信息：
* $wei[5]$ ：当前节点排序后的下标对于 $5$ 取模后为 $wei$ 的下标，并存入该点的权值。简单来说， $wei[j]$ 就是当前节点对于下标 $i$ 满足 $5$ 余 $j$ 的数的和的单点贡献。
* $sum[5]$ ：当前节点排序后，子树中的 $wei$ 的和。
* 其他的就是平常的 splay 了，能打懒标记就行。

在向上 update 重塑节点信息的时候 ： 

$sum[pos]=sum[ls] + sum[rs] + wei[pos]$
		
首先对于 $1$ 操作，二话不说首先 insert 。

应当考虑当前节点的贡献 $wei$ 。贡献的大小 $x$ 已知，只需要弄清楚权值对 $1$ ~ $5$ 哪一个 $wei$ 做贡献的问题了。只需要查询 $x$ 前驱的排名加 $1$ 即可。

再是考虑插入 $x$ 对于其他点的影响。可以发现，插入 $x$ 对于大于 $x$ 的数有影响，会使得这些点的 $sum[i]$ 和 $wei[i]$ 变为 $sum[(i+1)\mod5]$ 和 $wei[(i+1)\mod5]$ 。将权值为 $x$ 的点 splay 到根节点，大于 $x$ 的数全都在其右子树中了。然后只用修改右儿子的 $wei$ 和 $sum$ ，对于右儿子美美地打上懒标记就行了。

然后是删除操作，现将他 splay 到根节点，把他的所有有关权值的信息清空了，避免对于之后的删除操作造成毁灭性的影响。

可以发现，删除 $x$ 对于大于 $x$ 的数有影响，会使得这些点的 $sum[i]$ 和 $wei[i]$ 变为 $sum[(i-1)\mod5]$ 和 $wei[(i-1)\mod5]$ 。接下来的操作就类似于操作1里面的操作了。

最后，就是最简单的查询操作了，直接访问根节点的信息就行了。
# Code
时间复杂度为 $O(5n\log n)$ ，最慢的点 $1372ms$ 。
```cpp
#include <cstdio>
#define INF 1e15
#define int long long
const int MAXN = 1e5 + 5;
struct Splay_Node {
	int fa, cnt, siz, val, tag, son[2], wei[5], sum[5];
	#define ls t[pos].son[0]
	#define rs t[pos].son[1]
};
struct Splay_Tree {
	Splay_Node t[MAXN];
	int root, tot, Top, stk[MAXN];
	bool Ident(int pos) {
		return t[t[pos].fa].son[1] == pos;
	}
	void New(int val, int fa) {
		t[++tot].fa = fa;
		t[tot].val = val;
		t[tot].cnt = t[tot].siz = 1;
	}
	void Build() {
		New(-INF, 0);
		root = tot;
		New(INF, root);
		t[root].son[1] = tot;
	}
	void Update(int pos) {
		for(int i = 0; i < 5; i++) t[pos].sum[i] = t[ls].sum[i] + t[rs].sum[i] + t[pos].wei[i];
		t[pos].siz = t[ls].siz + t[rs].siz + t[pos].cnt;
	}
	void Connect(int pos, int fa, int how) {
		t[pos].fa = fa;
		t[fa].son[how] = pos;
	}
	void Push_Down(int pos) {
		if(!t[pos].tag) return;
		int tmp[5];
		if(ls) {
			for(int i = 0; i < 5; i++) tmp[(i + t[pos].tag + 5) % 5] = t[ls].sum[i];
			for(int i = 0; i < 5; i++) t[ls].sum[i] = tmp[i];
			for(int i = 0; i < 5; i++) tmp[(i + t[pos].tag + 5) % 5] = t[ls].wei[i];
			for(int i = 0; i < 5; i++) t[ls].wei[i] = tmp[i];
			t[ls].tag = (t[ls].tag + t[pos].tag + 5) % 5;
		}
		if(rs) {
			for(int i = 0; i < 5; i++) tmp[(i + t[pos].tag + 5) % 5] = t[rs].sum[i];
			for(int i = 0; i < 5; i++) t[rs].sum[i] = tmp[i];
			for(int i = 0; i < 5; i++) tmp[(i + t[pos].tag + 5) % 5] = t[rs].wei[i];
			for(int i = 0; i < 5; i++) t[rs].wei[i] = tmp[i];
			t[rs].tag = (t[rs].tag + t[pos].tag + 5) % 5;
		}
		t[pos].tag = 0;
	}
	void Rotate(int pos) {
		int fa = t[pos].fa, grand = t[fa].fa;
		int how1 = Ident(pos), how2 = Ident(fa);
		Connect(pos, grand, how2);
		Connect(t[pos].son[how1 ^ 1], fa, how1);
		Connect(fa, pos, how1 ^ 1);
		Update(fa);
		Update(pos);
	}
	void Splay(int pos, int to) {
		int tmp = pos;
		Top = 0;
		stk[++Top] = tmp;
		while(tmp) stk[++Top] = tmp = t[tmp].fa;
		while(Top) Push_Down(stk[Top--]);
		for(int fa = t[pos].fa; t[pos].fa != to; Rotate(pos), fa = t[pos].fa)
			if(t[fa].fa != to) Ident(pos) == Ident(fa) ? Rotate(fa) : Rotate(pos);
		if(!to) root = pos;
	}
	int Find(int pos, int val) {
		if(!pos) return 0;
		Push_Down(pos);
		if(val == t[pos].val) return pos;
		else if(val < t[pos].val) return Find(ls, val);
		return Find(rs, val);
	}
	void Insert(int &pos, int val, int fa) {
		if(!pos) {
			New(val, fa);
			Splay(pos = tot, 0);
			return;
		}
		Push_Down(pos);
		if(val == t[pos].val) {
			t[pos].cnt++;
			Splay(pos, 0);
		}
		else if(val < t[pos].val) Insert(ls, val, pos);
		else Insert(rs, val, pos);
	}
	void Erase(int val) {
		int pos = Find(root, val);
		if(!pos) return;
		if(t[pos].cnt > 1) {
			t[pos].cnt--;
			Splay(pos, 0);
			return;
		}
		Splay(pos, 0);
		int l = ls, r = rs;
		while(t[l].son[1]) l = t[l].son[1];
		while(t[r].son[0]) r = t[r].son[0];
		Splay(l, 0);
		Splay(r, l);
		t[r].son[0] = 0;
	}
	int Query_Rank(int pos, int val) {
		if(!pos) return 0;
		if(val == t[pos].val) {
			int res = t[ls].siz + 1;
			Splay(pos, 0);
			return res;
		}
		else if(val < t[pos].val) return Query_Rank(ls, val);
		int res = t[ls].siz + t[pos].cnt;
		return Query_Rank(rs, val) + res;
	}
	int Query_Pre(int val) {
		int pos, res, newroot;
		pos = newroot = root;
		while(pos) {
			Push_Down(pos);
			if(t[pos].val < val) {
				res = t[pos].val;
				pos = rs;
			}
			else pos = ls;
		}
		Splay(newroot, 0);
		return res;
	}
};
Splay_Tree tree;
int n;
signed main() {
	tree.Build();
	scanf("%lld", &n);
	char opt[3];
	for(int i = 1, x; i <= n; i++) {
		scanf("%s", opt);
		if(opt[0] == 'a') {
			scanf("%lld", &x);
			tree.Insert(tree.root, x, 0);
			int pre = tree.Query_Pre(x);
			int pos = tree.Find(tree.root, x);
			int prerk = tree.Query_Rank(tree.root, pre);
			prerk %= 5;
			tree.Splay(pos, 0);
			tree.t[pos].wei[prerk] = tree.t[pos].sum[prerk] = x;
			int tmp[5];
			if(tree.rs) {
				for(int i = 0; i < 5; i++) tmp[(i + 1) % 5] = tree.t[tree.rs].sum[i];
				for(int i = 0; i < 5; i++) tree.t[tree.rs].sum[i] = tmp[i];
				for(int i = 0; i < 5; i++) tmp[(i + 1) % 5] = tree.t[tree.rs].wei[i];
				for(int i = 0; i < 5; i++) tree.t[tree.rs].wei[i] = tmp[i];
				tree.t[tree.rs].tag += tree.t[pos].tag;
			}
			tree.t[tree.rs].tag++;
			tree.Update(pos);
		}
		else if(opt[0] == 'd') {
			scanf("%lld", &x);
			int pos = tree.Find(tree.root, x);
			tree.Splay(pos, 0);
			int tmp[5];
			for(int i = 0; i < 5; i++) tree.t[pos].wei[i] = tree.t[pos].sum[i] = 0;
			if(tree.rs) {
				for(int i = 0; i < 5; i++) tmp[(i + 4) % 5] = tree.t[tree.rs].sum[i];
				for(int i = 0; i < 5; i++) tree.t[tree.rs].sum[i] = tmp[i];
				for(int i = 0; i < 5; i++) tmp[(i + 4) % 5] = tree.t[tree.rs].wei[i];
				for(int i = 0; i < 5; i++) tree.t[tree.rs].wei[i] = tmp[i];
				tree.t[tree.rs].tag += tree.t[pos].tag;
			}
			tree.t[tree.rs].tag--;
			tree.Erase(x);
		}
		else printf("%lld\n", tree.t[tree.root].sum[3]);
	}
	return 0;
}
```

---

## 作者：Cylete (赞：0)

因为$sum$操作是按从小到大排序后统计答案的

于是我们考虑权值线段树

$1 <= x <= 10^9$所以我们可以 **离线离散化** 或者 **在线动态开点**

先定义数组吧

$num[o]$表示这一段权值中的序列大小

$tree[o][i]$表示这一段权值中的序列 % 5 == $i$的和

$ls[o],rs[o]$动态开点的左右儿子

加点删点没什么好说的

我们重点考虑如何维护$\sum{a_i}$其中$i$ % 5 == 3

考虑线段树向上合并

首先自然是$num[o] = num[ls[o]] += num[rs[o]]$

然后是$tree[o][i]$

因为线段树是按照值域建立的

所以左子树的$tree[ls[o]][i]$可以直接加到$tree[o][i]$上

右子树的序列在当前$o$的序号应该是$num[lson] + pos$，$pos$表示它在原来右子树中的序号

所以右子树的合并就是$tree[rs[o]][(i + num[ls[o]])$% 5 $]$

最后答案就是$tree[1][3]$啦！

注意空间应该是$nlog_2n$

```cpp
#define int long long
#define mid ((l+r)>>1)
#define lson (o<<1)
#define rson (o<<1|1)
#define R register

const int MAXN = 1e5 + 10;
const int N = 1e9;

int T;
int tree[MAXN << 5][5], num[MAXN << 5], ls[MAXN << 5], rs[MAXN << 5], tot;

inline void pushup(int o)
{
	num[o] = num[ls[o]] + num[rs[o]];
	for(R int i = 0; i < 5; i++) tree[o][i] = tree[ls[o]][i] + tree[rs[o]][((i - num[ls[o]]) % 5 + 5) % 5];
}

inline void add(int &o, int l, int r, int val)
{
	if(!o) o = ++tot;
	if(l == r)
	{
		num[o] = 1;
		tree[o][1] = val;
		return;
	}
	if(val <= mid) add(ls[o], l, mid, val);
	else add(rs[o], mid + 1, r, val);
	pushup(o);
}

inline void del(int o, int l, int r, int val)
{
	if(l == r)
	{
		num[o] = 0;
		tree[o][1] = 0;
		return;
	}
	if(val <= mid) del(ls[o], l, mid, val);
	else del(rs[o], mid + 1, r, val);
	pushup(o);
}

char opt[10];
int x, root;

signed main()
{
	into();
	cin >> T;
	while(T--)
	{
		cin >> opt;
		if(opt[0] == 'a') cin >> x, add(root, 1, N, x);
		if(opt[0] == 'd') cin >> x, del(root, 1, N, x);
		if(opt[0] == 's') writeln(tree[1][3]);
	}
	return 0;
}
```

---

## 作者：X2H_tato (赞：0)

你要维护一个集合，支持加入或删除一个数（保证任意时刻元素都没有重复，且待删除的数一定在集合里）

然后每次询问，你要回答排序后（从小到大）下标（从1开始）\(\% 5=3\)的所有数的和。

所有数为正整数且不超过\(10^9\)

下面大概是一个不要动脑子的做法（

首先建一棵权值线段树，然后每个节点维护几个东西

- \(cnt\)，即这个节点所代表的值域区间里有多少个数
- \(s[0..4]\)，\(s[i]\)表示这个节点内的所有数排序后下标\(\% 5=i\)的数的和
上面两个东西随便算算就好了（具体看代码...）

然后\(10^9\)炸了...那就动态开点呗...

非常~~无脑~~且~~好~~写的代码：
```
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 1e5 + 10;

struct node {
  int lc, rc;
  ll s[5]; int cnt;
} t[N * 40];
int rt = 0, siz = 0;

void pushup(int x) {
  int lc = t[x].lc, rc = t[x].rc, ls = t[lc].cnt;
  // 讨论左右节点
  for (int i = 0; i < 5; i++) t[x].s[i] = t[lc].s[i];
  for (int i = 0; i < 5; i++) t[x].s[(i + ls) % 5] += t[rc].s[i]; // 维护s[0..4]
  t[x].cnt = t[lc].cnt + t[rc].cnt;
}

void insert(int &x, int l, int r, int p, int v) { // p插入的数的值，v=-1删除，v=1加入
  if (!x) x = ++siz; // 动态开点 
  if (l == r) {
    t[x].cnt += v;
    t[x].s[1] += 1ll * l * v;
    return;
  }
  int mid = (l + r) >> 1;
  if (p <= mid) insert(t[x].lc, l, mid, p, v);
  else insert(t[x].rc, mid + 1, r, p, v);
  pushup(x);
}

int main() {
  char s[23];
  int _; for (scanf("%d", &_); _; _--) {
    scanf("%s", s);
    if (s[0] == 's') printf("%lld\n", t[rt].s[3]);
    else {
      int d = s[0] == 'd' ? -1 : 1, v;
      scanf("%d", &v);
      insert(rt, 1, 1e9, v, d);
    }
  }
  return 0;
}

```


---

## 作者：Sakurajima_Mai (赞：0)

看到CF上RNG的神奇线段树，过来安利一波


#### 前置一波技能
1. 先看一下题目我们发现你每插入一个数，对于比他小的是不会有任何影响的，影响的只有比他大的，也就是右半边的数。
2. 明确一点，如果一个数被移了5的整数倍次那相当没移

	(5个一划取正中，这个数只不过被移到了另一组的相同的位置而已，对于最终答案的贡献是没有改变的)
    
    -->所以我们得到一个结论:一个数被移的次数相当于对5取模厚度后结果 即 $cnt[i]mod 5 $ 
3. 因为插入中夹杂着求和操作，所以你无法预测到最终具体哪个数会成为最终的$middle$。那么，我们开始维护时，就要维护所有对5取余后每位上的具体值是多少。
   没错，我们线段树维护每个节点维护5个值，即区间中所有下标所对应的值。
4. 对于插入和删除操作的话，可以离线处理.

    
接着就进入正题

 观察题目，题目中保证没有重复的数，且只包含两种操作：插入和单点查询这两种操作 ，而且这个查询还是
  **对于堆顶的单点查询(划重点)**
  
 那么我们就可以构想初这样一颗线段树，将所谓的$update$ 和$query$
 全部转换成	直接对叶子节点的单点修改，和直接对堆顶的查询，至于$pushup$的话直接自底向上直接维护即可
 
 Code:
 ```
 
#include<algorithm>
#include<cstring>
#include<iostream>
#define mk make_pair
#define foreach(c ,itr) for(__typeof((c).begin())itr=((c).begin());itr!=(c).end();itr++)
#include <cstdio>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1<<17;
int T;
int n;
string s;
vector<pair<int,int>>query;//first: 表示对应的操作 second：表示对应的操作值
map<int,int>mp;
int a[N];
int cnt[N<<1];
ll sum[N<<1][5];
int pm[100005];
void pushup(int root){
    int l = 2*root;
    int r = 2*root+1;
    cnt[root] = cnt[l]+cnt[r];
    for(int i=0;i<5;i++){
        sum[root][i] = sum[l][i] + sum[r][(i-cnt[l]%5+5)%5];//当前位置所对应的值等于没有受到影响的左半边和在移动位置前的值的和。
    }
}
int main(){
    int tmp;
    scanf("%d\n",&n);
    for(int i=0;i<n;i++){
        cin>>s;
        if(s[0]=='s'){
           query.push_back(mk(2,0));//打标记，表示当前求和操作
        }else{
             scanf("%d\n",&tmp);
            if(s[0]=='a')
                query.push_back(mk(0,tmp));//打标记，表示add操作
            else
                query.push_back(mk(1,tmp));//打标记，表示del操作
            mp[tmp]=0;//表示当前数字存在于mp中
        } 
    }
    foreach(mp,itr){//离散化
        (itr->second)=T;pm[T]=(itr->first);T++;
    }
    for(int i=0;i<n;i++){
        int type = query[i].first,x = query[i].second;
        if(type == 2){//遇到求和操作，直接输出堆顶值即可
            printf("%lld\n",sum[1][2]);
        }else {
            int id = N + mp[x];//表示从叶子节点开始
            cnt[id] = 1 - type;//对叶子节点的修改
            sum[id][0]=(1-type)*x;
            for(int j=id/2;j>=1;j/=2)pushup(j);//自底向上一次更新
        }
    }
    return 0;
}
 ```
 
 

---

