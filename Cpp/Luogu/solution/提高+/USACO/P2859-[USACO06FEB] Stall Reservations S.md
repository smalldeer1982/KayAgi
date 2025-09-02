# [USACO06FEB] Stall Reservations S

## 题目描述

约翰的 $N$（$1\leq N\leq 50000$）头奶牛实在是太难伺候了，她们甚至有自己独特的产奶时段。对于某一头奶牛，她每天的产奶时段是固定的时间段 $[A,B]$（即 $A$ 到 $B$，包括 $A$ 和 $B$）。这使得约翰必须开发一个调控系统来决定每头奶牛应该被安排到哪个牛棚去挤奶，因为奶牛们并不希望在挤奶时被其它奶牛看见。

请帮约翰计算：如果要满足奶牛们的要求，并且每天每头奶牛都要被挤过奶，至少需要多少牛棚和每头牛应该在哪个牛棚被挤奶。如果有多种答案，输出任意一种均可。

## 说明/提示

由 @FlierKing 提供 SPJ。

## 样例 #1

### 输入

```
5
1 10
2 4
3 6
5 8
4 7```

### 输出

```
4
1
2
3
2
4```

# 题解

## 作者：sy_zmq_001 (赞：29)

代码解释如下
```c++
#include <iostream>
#include <cstdio> 
#include <algorithm>
#include <queue>
using namespace std;

int n,num=1;
struct llo{
	int begin,end,xu,used;
} cow[50008];
priority_queue<pair <int,int> > q;
//用 priority_queue实现小根堆有两种方式：一是插入相反数，而是重载运算符，这里介绍前一种
//对于c++内置数据类型（如int，float），可以把要插入的数的相反数插入，在堆中取出后再取负得到原来的数，
//例如：要插入1,2,3，可以插入-1，-2，-3，那么从堆中会取出最大数-1，再取负就可得到1 

bool cmp1(llo x,llo y){
	return x.begin<y.begin;
}
bool cmp2(llo x,llo y){
	return x.xu<y.xu;
}
//每一头牛都必须从编号为未知的牛棚挤奶，那我们在挤奶前假设需要一个牛棚（最优），再不断往上加牛棚
// 1. 为神马以开始时间排序呢，因为每两头牛之间只存在互斥（不能在一个牛棚）和相容（可以在一个牛棚）两种关系 
//那么易得：当相容时，开始时间早的必须先开始；当互斥时，两牛棚互不影响，此时不如让开始时间早的先挤奶
// 2.因为题目具有全覆盖性，所以当存在两牛均可以在某个牛棚挤奶时（或开始时间相同）必须有一牛再开一个牛棚，而此时两牛挤奶的截止时间都会被保存下来，
//对以后的选择没有影响 

int main(){
	scanf("%d",&n);//输入 
	for(int i=1;i<=n;i++){
		scanf("%d%d",&cow[i].begin,&cow[i].end);
		cow[i].xu=i;//捆绑序号，开始，结束，和使用哪个牛棚
	}
	sort(cow+1,cow+n+1,cmp1);//按开始端点排序 
	q.push(make_pair(-cow[1].end,num));//小根堆存数对，num牛棚现在截止的时间 和牛棚号码 
	cow[1].used=1;//第一头牛使用一号牛栏 
	for(int i=2;i<=n;i++){//从第二个开始，看是否需要新建牛棚 
		int x=-q.top().first;//取最早的截止时间 
		int num_q=q.top().second;//取最早截止时间的牛棚号 
		if(cow[i].begin>x){//当前牛使用之前牛腾出来的 
			q.pop();//将现牛棚的截止时期和num再更新一遍 
			q.push(make_pair(-cow[i].end,num_q));
			cow[i].used=num_q;//当前牛入住此牛棚，记录 
		}
		else{//当前牛必须自己再搞一个 
			num++;//牛栏数加一个 
			cow[i].used=num;//当前牛入住此牛棚，记录
			q.push(make_pair(-cow[i].end,num));//将新牛棚和num存入 
		}
	}
	printf("%d\n",num);
	sort(cow+1,cow+n+1,cmp2);//按序号重新排一遍 ，因为最后是让按序号输出 
	//很显然答案有很多种，只要让该在一个牛棚挤奶的牛的输出号码一样就行，所以保证输出编号和输入编号一致是必要的 
	for(int i=1;i<=n;i++)
		printf("%d\n",cow[i].used);//取每个牛使用的牛棚编号 
	return 0;
}
```


---

## 作者：foreverlasting (赞：28)

看到这题的题解要么超级复杂，要么不完整。所以就过来水一个题解了。

思路是差分。对于一段时间的维护，原本需要将这一段时间都标记上这头牛，但经过差分后就只用标记两个端点，这样时间复杂度就降下来了。然后至于输出，就大暴力枚举吧，时间上其实是绰绰有余的。

code：
```
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define res register int
#define inf 0x3f3f3f3f
inline int read(){
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return s*w;
}
const int N=1e5+10,M=1e6+10;
int pos[M],n,maxx,ans,tim[N],pen[N];
//pos存差分数组，tim存输出，pen指每个牛棚使用到的时间
struct mdzz{
	int l,r,id;
}seg[N];
inline bool cmp(mdzz a,mdzz b){
	return a.l<b.l;
}
int main(){
    n=read();
    for(res i=1;i<=n;i++){
    	int x=read(),y=read();
    	seg[i]=(mdzz){x,y,i};
    	pos[x]++,pos[y+1]--;
    	maxx=max(maxx,y);
	}
	int a=0;
    for(res i=1;i<=maxx;i++){
    	a+=pos[i];
    	ans=max(ans,a);
	}
	printf("%d\n",ans);
	sort(seg+1,seg+1+n,cmp);
    //这里肯定排个序，应该没问题吧
	for(res i=1;i<=n;i++)
		for(res k=1;k<=ans;k++)
		    if(pen[k]<seg[i].l){
		        pen[k]=seg[i].r,tim[seg[i].id]=k;break;
			}
	for(res i=1;i<=n;i++)
	   printf("%d\n",tim[i]);
    return 0;
}
```

---

## 作者：Rye_Catcher (赞：13)

- 题目链接：

   https://www.luogu.org/problemnew/show/P2859

- 思路：
 
   - 首先大家会想到这是典型的贪心，类似区间覆盖问题的思路，我们要将每段时间的左端点从小到大排序，然后一个个插入，插入时比较是否先前的牛棚中已经有牛挤完了奶，如果没有就新增一个牛棚，否则用挤完奶的牛棚。
   
   - 如果插入时扫描一遍找可用的牛棚的话肯定是会超时的，那么我们就要用一个**priority_queue（当然你手写堆也可以）维护先前插入的牛棚中最早挤完奶，即右端点最小的**那个。
   
- Tips：

  - 注意排序后奶牛的顺序可能是混乱的，而输出是要按原来输入的顺序。我们可以**用一个index记录每头奶牛先前的数组下标**，以便在记录摊位位置时不会出错。
  
  - 如何判断每头奶牛在哪个摊位？？？
  
    - 虽然感觉第一篇题解的二分+树状数组好神奇但是我看不懂
    - 感觉第三篇的差分好神奇但我还是看不懂
    
    于是就用了土方法
    
    我们用一个be数组记录每个奶牛对应的摊位，如果前面没有可插入的奶牛，则新增一个。如果前面有一个奶牛挤完了奶，那么我们就用它的牛棚，具体请看代码实现。
    
    
- 代码：

```
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <queue>
using namespace std;
const int maxn=50005;
int n,be[maxn],cnt=0;
struct Cow{
	int s,e,index;
}cow[maxn];
struct Num{    //优先队列记录下标
	int x;
	bool operator < (const Num &a) const{
	return cow[x].e>cow[a.x].e;
	}
};
inline bool cmp1(const Cow &a,const Cow &b){
	return a.s<b.s;
}
priority_queue< Num,vector<Num>>poi;
int main()
{
	cin>>n;
	for(register int i=1;i<=n;i++){
		scanf("%d %d",&cow[i].s,&cow[i].e);
		cow[i].index=i;
	}
	sort(cow+1,cow+1+n,cmp1);
	for(register int i=1;i<=n;i++){
		Num k;k.x=i;
		if(!poi.empty()){  
			Num p=poi.top();//取出队首时间最短的
			if(cow[p.x].e>=cow[i].s){
				cnt++;
				poi.push(k);
				be[cow[i].index]=cnt;  //注意是index值
			}
			else {//如果前面有挤完奶的
				poi.pop();//注意要pop出来
                poi.push(k);
                be[cow[i].index]=be[cow[p.x].index];				//注意这句话，仔细想一想为什么
			}
		}
		else {//如果是第一头牛
			poi.push(k);
			cnt++;
			be[cow[i].index]=cnt;
		}
	}
	cout<<cnt<<endl;
	for(register int i=1;i<=n;i++){
		printf("%d\n",be[i]);
	}
	return 0;
}
```
- 总结：

  思维难度一般，考验一些小技巧的使用

---

## 作者：sjie (赞：7)

看到这题感觉要用到树状数组查分来写，后来觉得奶牛编号不太好求，于是想到以下贪心：

	将奶牛的左端点单独存一个数组
    将奶牛的右端点单独存一个数组	
    左端点从小到大排序
    右端点从小到大排序
    
    右端点从小到大枚举;
    若该右端点的牛没有牛棚，该牛的牛棚为:牛棚数量+1;
    然后找左端点第一个比这个右端点大的牛，放上与该右端点的牛相同的牛棚
    (这里第一个比右端点大，指的是该左端点坐标大于该右端点坐标，且该左端点的牛还没有牛棚）
    我们枚举右端点的时候顺便可以带着左端点的位置一起走
    所以这里是O(n)
    再加上排序的O(n log n)
    然后这题就很简单的做完了.
  
```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=1000000;
const int M=50009;
int n,num=0;
int ans[M];
struct P{int val,id;}a[M],b[M];
int read(){
	int rex=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){rex=rex*10+ch-'0';ch=getchar();}
	return rex*f;
}
bool cmp(const P &l,const P &r){
	return l.val<r.val;
}
int main(){
	n=read();
	for(int i=1;i<=n;++i){
		a[i].val=read(),a[i].id=i;
		b[i].val=read(),b[i].id=i;
	}
	sort(a+1,a+n+1,cmp);
	sort(b+1,b+n+1,cmp);
	for(int i=1,j=1;i<=n;++i){
		if(j<=n)j++;// |左端点排名为j|的牛已经成为了与|右端点排名为i-1|相同的牛棚，所以j++
		//此时j++之后的j一定是还没有牛棚 
		if(!ans[b[i].id])ans[b[i].id]=++num;
		while(a[j].val<=b[i].val&&j<=n)j++;
		ans[a[j].id]=ans[b[i].id];
	}
	printf("%d\n",num);
	for(int i=1;i<=n;++i)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：phmaprostrate (赞：5)

CSP-S 受害选手写一发题解，作为 T1 的简化版此题只需要扫一遍即可。

## 分析
先假设有无限个牛棚，这样最后仍要使得牛棚数最少就需要尽可能让牛往编号小的牛棚里塞。举个例子：

![](https://pic.imgdb.cn/item/61780d052ab3f51d912d5887.png)

显然，新加的牛在 $1$ 或 $2$ 号棚子待着都是可以的，但要保证尽量少的牛棚，所以要在一号牛棚里。

所以，我们可以用一个优先队列来维护牛棚的编号，来保证牛进了编号最小的牛棚。再用一个优先队列来维护牛离开的最后时间和它所在的牛棚编号，这样可以得到奶牛可以进的所有牛棚的编号。

每一次，执行以上操作，要注意牛进入的时间是单调递增的，所以要先排序，这样会使牛的编号打乱，所以还要记录编号最后按照编号排序，最后输出。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e4 + 10;
int n;
struct node {
	int be,en;
	int id,last;
} a[N];
bool cmp(node aa,node bb) {
	return aa.be < bb.be;
}
struct node2 {
	int id,last;
	bool operator < (const node2 aa) const {
		return last > aa.last;
	}
};
bool cmp2(node aa,node bb) {
	return aa.id < bb.id;
}
priority_queue<node2> q;
priority_queue<int,vector<int>,greater<int> > ida;
int num = 0;
int main() {
	cin >> n;
	for(int i = 1 ; i <= n ; i ++) cin >> a[i].be >> a[i].en,a[i].id = i;
	sort(a + 1,a + 1 + n,cmp);
	for(int i = 1 ; i <= n ; i ++) ida.push(i);
	for(int i = 1 ; i <= n ; i ++) {
		while(!q.empty() && a[i].be > q.top().last) {
			node2 x = q.top();
			q.pop();
			ida.push(x.id);
		}//把所有可行的解取出来，扔进队列里维护编号最小
		int x = ida.top();
		ida.pop();
		a[i].last = x;
		q.push({x,a[i].en});//取出编号最小的，记录，把新的牛入队。

	}
	sort(a + 1,a + 1 + n,cmp2);
	for(int i = 1 ; i <= n ; i ++) num = max(num,a[i].last);
	cout <<num <<endl;//最大的牛棚就为需要的牛棚数
	for(int i = 1 ; i <= n ; i ++) cout << a[i].last << endl;
	return 0;

}
```




---

## 作者：二哥喝可乐 (赞：4)

哈哈哈哈哈$\mathcal O(n^2)$ 过50000，太刺激了。

加了个欧松，开个o2就过了。

我们有一个想法，用一个数组存下每个牛棚最后一头牛的结束时间每头牛找到一个结束时间大于他的牛棚就进去，找不到就新开一间。

但是这样好像不能保证最优，有可能我们的一头奶牛他比现在所有牛棚里的那头牛开始时间要早但是结束时间也早，也就是他应该先挤奶。这个时候我们就被hack了。

那么如果我们先按照每头牛的开始时间排个序可以保证比当前这头奶牛开始时间早的奶牛一定已经在牛棚里了，这样可以保证最优。

那么我们用愉快的n方过了他($O(n^2)$参考lyd的蓝书)

实在卡不过去还是用堆老老实实优化一下找牛棚的过程吧
```cpp
#include <bits/stdc++.h>
using namespace std;

inline char gc(){
	static char buf[1<<20],*p1=buf,*p2=buf;
	if(p1==p2){
		p2=(p1=buf)+fread(buf,1,1<<20,stdin);
		if(p1==p2) return EOF;
	}
	return *p1++;
}

//#define gc getchar

inline int read(){
	int x=0;bool f=0;char p=gc();
	while(!isdigit(p)) f|=(p=='-'),p=gc();
	while(isdigit(p)) x=x*10+p-'0',p=gc();
	return (f)?-x:x;
}


const int N=5e4+5;
int S[N],id[N];
struct node {
	int L,R,id;
	inline bool operator < (const node &nt) const {
		if(L!=nt.L) return L<nt.L;
		return R<nt.R;
	}
} a[N];

int main(){
	int n=read();
	for(int i=1;i<=n;++i) 
		a[i].L=read(),a[i].R=read(),a[i].id=i;
	sort(a+1,a+n+1);
	int num=0;
	for(register int i=1;i<=n;++i){
		id[a[i].id]=-1;
		for(register int j=1;j<=num;++j)
			if(a[S[j]].R<a[i].L){
				id[a[i].id]=j;
				break;
			} 
		if(id[a[i].id]==-1) S[++num]=i,id[a[i].id]=num;
		else S[id[a[i].id]]=i;
	}
	printf("%d\n",num);
	for(int i=1;i<=n;++i) printf("%d\n",id[i]);
	return 0;
}
```

---

## 作者：Gaode_Sean (赞：3)

这题运用的算法是贪心算法。

我们先按每头牛开始挤奶的时间开始排序，注意要在结构体里对每头牛打上一个编号（排序后顺序打乱了）。

对于每头牛，我们找出一下之前的牛用过的调控系统中最早结束使用的，如果结束时间小于当前奶牛开始挤奶时间，我们就将当前奶牛加入这个调控系统。否则，新建一个调控系统。

实现过程中我们用优先队列存一下当前最早结束挤奶的调控系统。

效率 $O(n \log n)$。

## AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int s,e,num;
}c[50001];
bool operator <(const node a,const node b){
        //return a.e<b.e||a.e==b.e&&a.s>b.s;
        return a.e>b.e;
}
bool cmp(node a,node b)
{
	return a.s<b.s||a.s==b.s&&a.e<b.e;
}
int ans,n,i,a[50001];
priority_queue<node> q;
int main()
{
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>c[i].s>>c[i].e;
		c[i].num=i;
	}
	sort(c+1,c+1+n,cmp);
	q.push(c[1]);
	a[c[1].num]=ans=1;
	for(i=2;i<=n;i++){
		if(q.top().e<c[i].s){
			a[c[i].num]=a[q.top().num];
			q.pop();
		}
		else{
			ans++;
			a[c[i].num]=ans;
		}
		q.push(c[i]);
	}
	cout<<ans<<endl;
	for(i=1;i<=n;i++) cout<<a[i]<<endl;
	return 0;
}
```

---

## 作者：1沃尔克 (赞：3)

看到这道题，类似于区间覆盖，但显然不是，不过可以类比推理，相当于求解重合区间的最大个数，并记录每个区间的位置（即牛棚序号）。

将区间存入a结构体，并按左端点a.l递增排序，定义一个指针（不一定要是指针变量）zzs，单独将右端点拎出来存入r（作为zzs的运动轨道），建一个队列记录空牛棚的序号。cow数组表示每头牛挤奶牛棚。

开始枚举，若a[i].l<=zzs,表示此时没有牛挤完奶，从队列中（已经建立的空牛棚），若队列为空，则新建一个牛棚，并且cow[a[i].id]=maxx+1;（maxx为已建牛棚数，a.id为牛的排序前的原始序号）;相反a[i].l>zzs,说明有牛挤完奶了，将空出来的牛棚加入队列，num--（在挤奶的牛数），指针右移。枚举到n输出即可。

## code
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int n,L,R,num,maxx;
struct ll
{
	int l,r,id;
}a[50004];
struct kk
{
	int r,id;
}rx[50004];
int cow[50004];
queue<int> q;
bool cmp(ll x,ll y)
{
	return x.l<y.l;
}
bool cmp2(kk x,kk y)
{
	return x.r<y.r;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d%d",&a[i].l,&a[i].r),rx[i].r=a[i].r,a[i].id=i,rx[i].id=i;
	sort(a+1,a+n+1,cmp);
	sort(rx+1,rx+n+1,cmp2);	
	int zzs=rx[1].r;int j=1;
	for(int i=1;i<=n;i++)
	{
		if(a[i].l<=zzs)
		{
			num++;
			if(q.empty()) cow[a[i].id]=maxx+1;
			else cow[a[i].id]=q.front(),q.pop();
		}
		else
		{
			maxx=max(maxx,num);
			while(rx[j].r<a[i].l)
			{
				q.push(cow[rx[j].id]);
				num--;j++;	
			}
			num++;
			zzs=rx[j].r;
			cow[a[i].id]=q.front();q.pop();
		}
		maxx=max(maxx,num);
	}
	maxx=max(maxx,num);
	printf("%d\n",maxx);
	for(int i=1;i<=n;i++)
	printf("%d\n",cow[i]);
	return 0;
}
```
致谢

---

## 作者：wmxwmx (赞：3)

看到题解不多，就过来凑个热闹。

这道题我是这么做的。

- 首先，大的思路是贪心，大概就是按着时间先后顺序把牛放入stall，假如stall满了，那么就牛棚数cnt++。

- 但是又不想整个时间线for一遍毕竟太长了，那么就选择**for一遍牛的左端点**好了，所以就要**对左端点排序**。- 0.

- 然后在for的过程中，我们又会遇到牛出stall，所以右端点也需要排序，但是由于左端点for完之后就没有右端点的事儿了，所以给右端点全部排序是没有必要的，所以我们选择**用堆维护右端点**。（堆排）

- 最后还有一个问题，就是当我们需要把牛塞到空stall里面的时候，我们塞哪个？于是我选择用树状数组维护stall，**用二分cnt的方法，把（stall前缀和与mid相比较）**找到最小的那个空stall，然后通过树状数组的change填满那个stall。BTW，其中涉及到一个不常见的树状数组操作，就是新增加一个stall，关于新增结点的管辖范围。

```cpp
cnt++;
st[cnt]=sum(cnt-1)-sum(cnt-lowbit(cnt))+1;
```
- 解决了以上问题，OK主程序就是**for左端点**+**for的里面一定要记得先“出堆”**+**fill stall**+**记录每个cow的stall编号！**然后输出就好了。下面是本人写的代码，加了一点注释，不过是pascal的= =

其中le，ri分别左端点，右端点。

lm是左端点排序时牛编号，rm是右端点入堆时牛编号

st是stall的树状数组。

cow是每头牛的stall编号

len是堆的数目

cnt是stall的数目也是树状数组的上界

em是最小empty stall的编号，和check（二分求最小empty stall）函数一起用的。

就酱！

```pascal
const maxn=50000;
var n,i,len,cnt,em:longint;
    le,ri,lm,rm,st,cow:array[1..maxn]of longint;

procedure swap(var x,y:longint);//swap number
var t:longint;
begin   
    t:=x;
    x:=y;
    y:=t;
end;

procedure qs(l,r:longint);//ascend quicksort
var x,y,k:longint;
begin
    x:=l;y:=r;
    k:=le[(l+r)shr 1];
    repeat
        while le[x]<k do inc(x);
        while le[y]>k do dec(y);
        if x<=y then
        begin
            swap(le[x],le[y]);
            swap(lm[x],lm[y]);
            inc(x);
            dec(y);
        end;
    until x>y;
    if l<y then qs(l,y);
    if r>x then qs(x,r);
end;
//小根堆
procedure down(x:longint);
var t:longint;
begin
    t:=x shl 1;
    if t>len then exit
    else if (t<len)and(ri[t]>ri[t+1]) then inc(t);
    if ri[t]<ri[x] then
    begin
        swap(ri[x],ri[t]);
        swap(rm[x],rm[t]);
        down(t);
    end;
end;

procedure delete(x:longint);
begin
    ri[x]:=ri[len];
    rm[x]:=rm[len];
    dec(len);
    down(x);
end;
//小根堆
//BIT for stalls
function lowbit(x:longint):longint;
begin
    exit(x and (-x));
end;

procedure change(x,y:longint);
begin
    while x<=cnt do
    begin
        inc(st[x],y);
        inc(x,lowbit(x));
    end;
end;

function sum(x:longint):longint;
begin
    sum:=0;
    while x>0 do
    begin
        inc(sum,st[x]);
        dec(x,lowbit(x));
    end;
end;
//BIT for stalls
//Binary Search for the empty stall
function check(l,r:longint):longint;
var mid:longint;
begin
    while l<r do
    begin
        mid:=(l+r)shr 1;
        if sum(mid)=mid then l:=mid+1
        else r:=mid;
    end;
    exit(r);
end;

//main
begin
    readln(n);
    for i:=1 to n do
    begin
        readln(le[i],ri[i]);
        lm[i]:=i;
        rm[i]:=i;
    end;
    qs(1,n);//左端点排序
    len:=n;//len for heap
    for i:=n shr 1 downto 1 do//右端点入堆
    down(i);
    cnt:=0;//cnt for BIT
    for i:=1 to n do
    begin
        while ri[1]<le[i] do//need to empty stall first
        begin
            change(cow[rm[1]],-1);//empty stall
            delete(1);
        end;
        if sum(cnt)=cnt then
        begin
            inc(cnt);
            st[cnt]:=sum(cnt-1)-sum(cnt-lowbit(cnt))+1;
            cow[lm[i]]:=cnt;
        end//stall is full
        else
        begin
            em:=check(1,cnt);//find the smallest empty stall;
            cow[lm[i]]:=em;
            change(em,1);//fill the empty stall;
        end;
    end;
    writeln(cnt);
    for i:=1 to n do
    writeln(cow[i]);
end.
```

---

## 作者：SegTre (赞：2)

## 思路
考虑贪心啦。下文中 $l_i$ 表示第 $i$ 头牛挤奶开始时间，$r_i$ 表示结束时间，$\min$ 表示前 $i-1$ 头牛中最早结束挤奶的时间。我们可以以**开始时间**为关键字给奶牛们**排序**，然后依次考虑每头奶牛。到第 $i$ 头牛时分下面两种情况：

1. $l_i\leq\min$ 这头奶牛就没地方挤奶了，需要新开一间牛棚，答案++；
2. $l_i>\min$ 可以找个结束挤奶的牛棚进去挤奶。但是如果有多个牛棚处于空闲状态呢？其实随便找一个就行了。因为对于任意 $j>i$，都有 $l_j>l_i$（我们自己排好序了），即当前奶牛 $i$ 能去的牛棚奶牛 $j$ 都能去，谁先去都一样的。为了方便用堆维护，我们就让它去最早结束挤奶的牛棚。


放个样例的图理解一下

![](https://cdn.luogu.com.cn/upload/image_hosting/nyod6ph7.png)

## Code
代码实现的话，用小根堆维护 $\min$，假装你们都会重载运算符（不会也可以现学）。还要注意一点：题目让我们输出每头奶牛去的牛棚编号，所以我们要在排序前记录一个值 $first$ 表示每头奶牛的初始编号。
```cpp
#include<cstdio>
#include<cctype>
#include<queue>
#include<algorithm>
using namespace std;
inline int read() {
	int res;char c;
	while(!isdigit(c=getchar()));res=c^48;
	while(isdigit(c=getchar())) res=(res<<3)+(res<<1)+(c^48);
	return res;
}
struct Time { // 牛挤奶的时间段 
	int first,l,r; 
}a[50005];
struct stall { // 牛棚 
	int num,last;
};
bool operator <(const stall &alpha,const stall &beta) { // 重载运算符 
	return alpha.last>beta.last;
}
bool cmp(Time alpha,Time beta) {
	return alpha.l<beta.l;
}
priority_queue<stall> q; // 小根堆 
int tot,ans[50005]; // 答案存这儿 
int main() {
	int n=read();
	for(int i=1;i<=n;++i) a[i].first=i,a[i].l=read(),a[i].r=read();
	sort(a+1,a+n+1,cmp);
	stall x;
	x.num=++tot;
	x.last=a[1].r;
	ans[a[1].first]=1;
	q.push(x);
	for(int i=2;i<=n;++i) {
		if(a[i].l<=q.top().last) {
			ans[a[i].first]=++tot;
			x.num=tot;
			x.last=a[i].r;
			q.push(x);
		}
		else {
			x=q.top();
			ans[a[i].first]=x.num;
			q.pop();
			x.num=ans[a[i].first];
			x.last=a[i].r;
			q.push(x);
		}
	}
	printf("%d\n",tot);
	for(int i=1;i<=n;++i) printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：Santiego (赞：2)

> $n$头牛，每头牛占用时间区间$[l_i,r_i]$，一个牛棚每个时间点只能被一头牛占用，问最少新建多少个牛棚，并且每头牛在哪个牛棚里？

比较巧的$O(n)$扫一遍做法，用一个**小跟堆**维护所有牛棚最后一个牛占用的时间（即$r_i$），贪心的想，如果最先结束的那个牛棚都不能满足当前牛，那么我们只能新开一个牛棚，并继续维护小根堆；如果那个牛棚满足，那么这个牛就去那个牛棚，更新当前牛棚最后占用时间。

```cpp
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
inline int read(){
    char ch=getchar();int s=0;
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') s=s*10+(ch^'0'), ch=getchar();
    return s;
}
struct nod{
    int cnt,last;
    const bool operator < (const nod &a) const{
        return last>a.last; // 小根堆
    }
    nod(int cnt, int last):cnt(cnt),last(last){}
};
#define MAXN 50005
struct nod2{
    int l,r,id;
    const bool operator < (const nod2 &a) const{
        if(l==a.l) return r<a.r;
        return l<a.l;
    }
} a[MAXN];
int ans[MAXN];
priority_queue<nod> q;
int n;
int sum=0;
int main(){
    n=read();
    for(int i=1;i<=n;++i) a[i].id=i,a[i].l=read(),a[i].r=read();
    sort(a+1, a+1+n);
    q.push(nod(1, a[1].r));
    ans[a[1].id]=1;
    ++sum;
    for(int i=2;i<=n;++i){
        nod cur=q.top();
        if(cur.last>=a[i].l){
            ++sum; // 新开牛棚
            ans[a[i].id]=sum;
            q.push(nod(sum, a[i].r));
        }else{
            q.pop(); // 更新牛棚最后结束时间
            ans[a[i].id]=cur.cnt;
            q.push(nod(cur.cnt, a[i].r));
        }
    }
    printf("%d\n", sum);
    for(int i=1;i<=n;++i) printf("%d\n", ans[i]);
    return 0;
}

```




---

## 作者：Adove (赞：2)

这题可以暴力；

排序+二分+暴力dfs染色==AC；

排序+二分+dfs是很多题目的通解，单独拿出二分+dfs也能在复杂度不正确的情况下水掉不少题，甚至有可能拿到最优解，例如【SDOI2008】Sandy的卡片；

上代码吧↓

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int MAXN=1<<17;

int n;
int clr;
struct rpg{
    int l,r,id,clr;
}p[MAXN];

inline int read(){
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x;
}

bool cmp1(rpg a,rpg b){
    if(a.l==b.l) return a.r<b.r;
    return a.l<b.l;
}bool cmp2(rpg a,rpg b){
    return a.id<b.id;
}

void dfs(int k){
	int l=k+1,r=n;
	while(l<r){
		int mid=l+r>>1;
		if(p[mid].l>p[k].r) r=mid;
		else l=mid+1;
	}for(int i=l;i<=n;++i){
		if(!p[i].clr&&p[i].l>p[k].r){
			p[i].clr=p[k].clr;
			dfs(i);
			return;
		}
	}return;
}

void init(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        p[i].l=read(),p[i].r=read();
        p[i].id=i;
    }return;
}

void solve(){
    sort(p+1,p+n+1,cmp1);
    for(register int i=1;i<=n;++i){
        if(!p[i].clr){
        	p[i].clr=++clr;
        	dfs(i);
		}
    }sort(p+1,p+n+1,cmp2);
    return;
}

void write(){
    printf("%d\n",clr);
    for(int i=1;i<=n;++i){
        printf("%d\n",p[i].clr);
    }return;
}

int main(){
    init();
    solve();
    write();
    return 0;
}
```

---

## 作者：c2020HXW (赞：0)

# 我选择，模拟！！
因为此题时间段A和B的范围都可以承受，（太大了也可以离散化），不妨以时间为序来模拟这个简单过程

直接开一个栈，依次加入N-->1,表示要用的牛棚的编号（最多会用n个）

对于每一头牛，用类似前向星链表的方式在他起点的时间加一个编号为i的儿子

同理，在结束位置也加一个编号为i的儿子（用另一套链表）

然后就按照时间顺序简单模拟：

不管啥的先读进来加入链表

对于每一个时间点
   
	1.从链表取出在当时要牛棚的牛，把栈顶的牛棚给他：

	2.ans与已经拿去用的牛棚数量（就是(n-top) )取max;

	3.从链表取出当时要离开牛棚的牛，把该牛用的牛棚（就是ans[i]）塞回栈顶

然后输出，快乐的结束！

code:
```cpp
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;
//#define int long long
const int Maxx=1000005,Maxn=2001,INF=0x3f3f3f3f,Mod=1e9+7;
inline int read()
{
	int res=0,bj=0;char ch=getchar();
	while(ch<'0'||ch>'9')bj|=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9')res=(res<<3)+(res<<1)+(ch^48),ch=getchar();
	return bj?-res:res;
}
void print(int x)
{
	if(x>9)print(x/10);
	putchar(x%10^48);
}
inline void printnum(int x,char ch)
{
	if(x<0)putchar('-'),x=-x;
	print(x),putchar(ch);
}
int n,x,y,tp,ans,sum,Maxnum=-INF,Minnum=INF,stk[Maxx],as[Maxx];
int hx[Maxx],nx[Maxx],hy[Maxx],ny[Maxx];
signed main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)
	{
		Minnum=min(Minnum,x=read());
		Maxnum=max(Maxnum,y=read());
		nx[i]=hx[x],hx[x]=i;
		ny[i]=hy[y],hy[y]=i;
		//读入，加入链表，因为如果按邻接表的来，to[i]=i,于是就干脆把to[]省了…… 
		stk[i]=(n-i+1);
	}tp=n;
	for(int i=Minnum;i<=Maxnum;i++)
	{
		for(int j=hx[i];j;j=nx[j])as[j]=stk[tp--];
		ans=max(ans,n-tp);
		for(int j=hy[i];j;j=ny[j])stk[++tp]=as[j];
	}
	printnum(ans,'\n');
	for(int i=1;i<=n;i++)printnum(as[i],'\n');
	return 0;
}
```

---

## 作者：太阳骑士 (赞：0)

考虑贪心。我们可以将每头牛的起始时间从小到大排序，然后再建一个小根堆，记录每个牛棚的牛挤完奶的时间和这个牛棚的编号。

我们扫描排好序的每头牛，如果堆顶牛棚的$time$晚于当前的牛的$begin$，则一定要新建一个牛棚给这个牛挤奶；否则，直接将堆顶牛棚的$time$修改为当前牛的$end$，即把当前牛放到了堆顶牛棚中挤奶，我们记录下这个牛的牛棚编号为堆顶牛棚编号即可。由于要按序号输出，所以还要记录每个牛的序号，最后记录答案时直接$ans[cow[i].id]=$牛棚编号就行了。

```cpp
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define il inline
#define re register
#define tie0 cin.tie(0),cout.tie(0)
#define fastio ios::sync_with_stdio(false)
#define File(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout)
using namespace std;
typedef long long ll;

template <typename T> inline void read(T &x) {
	T f = 1; x = 0; char c;
    for (c = getchar(); !isdigit(c); c = getchar()) if (c == '-') f = -1;
    for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x *= f;
}

struct eat {
	int begin, end, id;
} cow[50003];

struct period {
	int time, num;//分别是牛棚可以空出的时间和牛棚编号
	bool operator < (const period& x)const{return x.time < time;}//按时间排序
} now;

priority_queue <period> q;

int n, tot;
int ans[50003];

bool cmp(eat milk, eat grass) {
	return milk.begin == grass.begin ? milk.end < grass.end : milk.begin < grass.begin;
}

int main() {
//	File("testdata");
	read(n);
	for (int i = 1; i <= n; ++i) read(cow[i].begin), read(cow[i].end), cow[i].id = i;
	sort(cow + 1, cow + 1 + n, cmp);//排序
	for (int i = 1; i <= n; ++i) {
		if (q.empty() || q.top().time >= cow[i].begin) {//第一头牛和不能放进堆顶牛棚的牛要新建一个牛棚
			now.time = cow[i].end, now.num = ++tot;
			q.push(now); ans[cow[i].id] = now.num;
		}
		else {//修改堆顶元素
			now = q.top(); q.pop();
			now.time = cow[i].end, ans[cow[i].id] = now.num;
			q.push(now);
		}
	}
	printf("%d\n", tot);
	for (int i = 1; i <= n; ++i) printf("%d\n", ans[i]);//输出答案
	return 0;
}
```

---

## 作者：陷语 (赞：0)

## 摊位预定

**思路：**

我们可以按牛开始挤奶的顺序从小到大排序一遍，接着我们可以用小根堆来维护每个牛棚牛结束挤奶的时间，如果有某头牛开始吃草的时间大于堆首结束的时间就将其替换，如果没有就新增一个牛棚。

**证明：**

设x < y
那会有这三种情况：

1.x和y均可以选择

2.x可以选择，y不可以选择

3.两者均不可选择

很显然选择x对答案的贡献更大。

代码：
```cpp
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;
const int N = 50050;

int n, t, ans[N];

struct cow {
	int id, x, y;
	bool operator < (const cow & a) const{
		return x < a.x;
	}
} a[N];

struct cmp {
	int id, y;
	bool operator < (const cmp & a) const{
		return y > a.y;
	}
};

priority_queue <cmp> que;//小根堆 

int main() {
	
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d %d", &a[i].x, &a[i].y), a[i].id = i;
	
	sort(a + 1, a + 1 + n);
	
	for(int i = 1; i <= n; ++i) {
		
		if(que.empty() || que.top().y >= a[i].x) {
			t++;//新增一个牛棚 
			que.push((cmp) {t, a[i].y});
			ans[a[i].id] = t;
		}
		else {
			int id = que.top().id;
			que.pop();//牛可以在这里挤奶，将这个结束时间替换 
			que.push((cmp) {id, a[i].y});
			ans[a[i].id] = id;
		}
	}
	
	printf("%d\n", t);
	for(int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
	return 0;
}
```

**感谢机房dalao（Mogu）对我提供的思路。**

---

## 作者：mol茶蛋糕 (赞：0)

这道题就是一道**贪心**题目

可以根据每头牛开始的时间排序,然后顺序枚举时，每一次扫描已有的牛棚，如果这个奶牛能在已有牛棚中挤奶，那么就把这个牛棚更新一下结束时间就好（注意不需要选择结束得最晚的牛棚更新结束时间，因为奶牛挤奶的起始时间已经排好序了，下一个奶牛挤奶的起始时间一定比这一头奶牛晚，所以更新哪一个牛棚都没有关系），如果不能，那么就新开一个牛棚。  

最后得到牛棚数量和每头牛挤奶的地方~

~~~
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
struct node{
    int st,ed,adr,pla;
}q[50005];
bool cmp_st(node a,node b)
{
    return a.st<b.st;
}
bool cmp_adr(node a,node b)
{
    return a.adr<b.adr;
}
int c[50005];
inline void read(int & x)
{
	x=0; int f=1; char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') 
	{x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	x*=f;
}
inline void print(int x)
{
	if(x<0) {x=-x;putchar('-');}
	if(x>9) print(x/10);
	putchar(x%10+48);
}
int main()
{
    int n;
    read(n);
    for(int i=1;i<=n;i++)
    {
    	read(q[i].st),read(q[i].ed); 
        q[i].adr=i;
    }
    stable_sort(q+1,q+1+n,cmp_st);
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        int k=0;
        for(int j=1;j<=ans;j++)
        {
            if(c[j]<q[i].st)
            {
                c[j]=q[i].ed;
                q[i].pla=j;
                k=1;
                break;
            }
        }
        if(!k)
        {
            ans++;
            c[ans]=q[i].ed;
            q[i].pla=ans;
        }
    }
    print(ans),putchar('\n');
    stable_sort(q+1,q+n+1,cmp_adr);
    for(int i=1;i<=n;i++)
        print(q[i].pla),putchar('\n');
    return 0;
}
~~~

---

## 作者：FFFurther (赞：0)

//没想到差分怎么打印牛在哪个牛棚，就用了贪心，多了一个niu[]数组，把s[i].id当下标记录i就好









```cpp
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int N = 50010;
struct Segment{
    int l, r, id;
    Segment(int l = 0, int r = 0, int id = 0) : l(l), r(r), id(id){}
} s[N];
inline int read(){
    char ch = getchar(); int ans = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') ans = ans * 10 + ch - '0', ch = getchar();
    return ans;
}
bool cmp(const Segment &a, const Segment &b){
    return a.l < b.l;
}
int num, stall[N]; //现在至少有几个井已经用了，每个井最后的使用时间 
struct D{
    int time, pos;
    D(int t, int p) : time(t), pos(p){}
    bool friend operator<(const D &a, const D &b){
        return a.time > b.time;
    }
};
priority_queue<D> que;
//vector<int> vec[N];
int niu[N];
int main(){
    //freopen("a.in", "r", stdin);
    //freopen("a.out", "w", stdout);
    int n;
    n = read();
    for(int i = 1; i <= n; ++i){
        int a, b;
        a = read(), b = read();
        if(a > b) swap(a, b);
        s[i] = Segment(a, b, i);
    }
    sort(s + 1, s + n + 1, cmp);
    stall[++num] = s[1].r;
    que.push(D(stall[1], 1));
    //vec[1].push_back(s[1].id);
    niu[s[1].id] = num;
    for(int i = 2; i <= n; ++i){
        D a = que.top();
        if(s[i].l <= a.time){
            stall[++num] = s[i].r;
            que.push(D(stall[num], num));
            niu[s[i].id] = num;
//printf("%%%%%%%%%%%%%%\n");                    
        }
        else{
            que.pop();
            stall[a.pos] = s[i].r;
            que.push(D(stall[a.pos], a.pos));
            niu[s[i].id] = a.pos;
        }
        //vec[num].push_back(s[i].id);
    }
    printf("%d\n", num);
    for(register int i = 1; i <= n; ++i){
        printf("%d\n", niu[i]);
    }
    return 0;
}
```

---

## 作者：柠青哟 (赞：0)

既然是贪心的题就用贪心的思想，先按照每个奶牛挤奶的开始时间从小到大排个序，再为第一头奶牛新建一个牛棚，接着处理后续奶牛，我们设Si为第i头奶牛的开始时间，设Ex为牛棚的结束时间,牛棚的结束时间，意思既是在该牛棚挤奶的奶牛x的结束时间，将已知Ex按照从小到大的时间排序。那么，在处理第i头奶牛时，查看已有牛棚中结束时间最早的牛棚Ea 若Ea<Sa，则不用新建牛棚，第i头奶牛进入该牛棚，修改Ea为Ei.
若Ea>Si，则新建牛棚，记Eb=Ei.
关于Ex的排序，那就借助优先队列啦
```c
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstdio>
using namespace std;
struct cows{
	int a,b;
	int No;
	bool operator<(const cows & c)const{
		return a<c.a;
	}
} cow[50100];
int pos[50100];
struct stall{
	int end;
	int No;
	bool operator<(const stall & x)const{
		return end>x.end;
	}
	stall(int e,int n):end(e),No(n) {}
};
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&cow[i].a,&cow[i].b);
		cow[i].No=i;
	}
	sort(cow+1,cow+1+n);
	int tot=0;
	priority_queue<stall>pq;
	for(int i=1;i<=n;i++){
		if(pq.empty()){
			tot++;
			pq.push(stall(cow[i].b,tot));
			pos[cow[i].No]=tot;
		}
		else{
			stall t=pq.top();
			if(t.end<cow[i].a){
				pos[cow[i].No]=t.No;
				pq.pop();
				pq.push(stall(cow[i].b,t.No));
			}
			else{
				tot++;
				pos[cow[i].No]=tot;
				pq.push(stall(cow[i].b,tot));
			}
		}
	}
	cout<<tot<<endl;
	for(int i=1;i<=n;i++){
		printf("%d\n",pos[i]);
	}	
}
```


---

