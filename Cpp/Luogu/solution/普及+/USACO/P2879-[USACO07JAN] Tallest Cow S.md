# [USACO07JAN] Tallest Cow S

## 题目描述

FarmerJohn 有n头牛，它们按顺序排成一列。FarmerJohn 只知道其中最高的奶牛的序号及它的高度，其他奶牛的高度都是未知的。现在 FarmerJohn 手上有 $R$ 条信息，每条信息上有两头奶牛的序号（$a$ 和 $b$），其中 $b$ 奶牛的高度一定大于等于 $a$ 奶牛的高度，且 $a, b$之间的所有奶牛的高度都比 $a$ 小。现在 FarmerJohn 想让你根据这些信息求出每一头奶牛的可能的最大的高度。（数据保证有解）

## 说明/提示

$1 \le n \le 10000$，$1 \le h \le 1000000$，$0 \le R \le 10000$

Translate provided by @酥皮

## 样例 #1

### 输入

```
9 3 5 5
1 3
5 3
4 3
3 7
9 8```

### 输出

```
5
4
5
3
4
4
5
5
5```

# 题解

## 作者：Teddy_Di (赞：27)

大佬们的什么差分数组，线段树本蒟蒻其实都没学过嘤嘤嘤。。。
然后我的大概思路就是某巨佬老师讲的那样，先把所有牛的高度设为最高值，如果某两头牛之间能互相看到的话，那直接把中间所有牛都砍一刀（中间这些牛的高度都减一）然后最后输出就可以了。。
```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
struct node {
    int first;
    int second;
}h[10005];
int kdl[10005][10005];//这个用于去重
int n, f[10005], hest, r, t, a, b, c, d;//c，d貌似没用上。。
int main() {
    scanf("%d%d%d%d", &n, &t, &hest, &r);
    for (int i = 1; i <= n; i++) {
        f[i] = hest;
    }
    for (int i = 1; i <= r; i++) {
        scanf("%d%d", &a, &b);
        h[i].first = min(a, b);
        h[i].second = max(a, b);//让这二者中小的赋给first，大的赋给second
        if (kdl[a][b] == 1)continue;
        kdl[a][b] = 1;//如果已经算过一次就跳过，没算过就标记并运算
        for(int j=h[i].first+1;j<h[i].second;j++)f[j]--;
    }//把中间所有牛的高度减一
    for(int i=1;i<=n;i++)printf("%d\n",f[i]);
    return 0;
}
```

---

## 作者：追梦_Chen (赞：25)

较简单的一道题，唯一要注意的是：当x和y相同时，我们不能重复进行操作，也就是说，我们需要判重。但是如果要用二维bool数组判重的话，对于100000的二维数组，显然要超空间。所以我们可以巧妙的运用库函数'map'的内容，自己映射一个二维数组！


刚刚有小伙伴提问d[i]数组的含义，这里具体解释一下，首先我们用数组c[i]表示第i头牛的高度,d[i]=c[i]-c[i-1],相邻两头牛之间的高度差，如果我们对x和y区间的牛进行操作，相当于c[x+1]到c[y-1]减了1,所以d[x+1]的值减了1，d[y]的值加了1啊啊啊啊。这样做就可以不用对区间进行操作，而是对两个点进行操作了，节约时间，从你我做起！！！！！（此致敬礼！）
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>	
#include <utility>
using namespace std;
int d[100005];      			 //牛
int n,l,h,r;
int x,y;
map<pair<int,int>,bool>book;   //由两个Int类型的映射bool数组

int main(){
    scanf("%d%d%d%d",&n,&l,&h,&r);
    for(int i=1;i<=r;i++){
        scanf("%d%d",&x,&y);    
        if(x>y)  swap(x,y);   //当x>y时记得交换
        if(book[make_pair(x,y)])    continue;  //判重
        d[x+1]--;   //前缀和操作
        d[y]++;    
        book[make_pair(x,y)]=true;
    }
    for(int i=1;i<=n;i++){
        d[i]=d[i-1]+d[i];            
        printf("%d\n",h+d[i]);
    }
    return 0;
}
```

---

## 作者：Chloris (赞：15)

### 前缀和
```cpp
sum[i]表示前i个数的和
每次读入a[i]的时候
sum[i] = sum[i - 1] + a[i];

查询l ~ r区间的和： sum[r] - sum[l - 1]
```

### 差分

```cpp
即前缀和的修改操作
我们定义pre[i]表示前i个数需要改变的值
则对一个区间l ~ r + k的操作是
pre[r] + k; pre[l - 1] - k;
则多算的1 ~ l - 1部分就抵消，等价与l ~ r + k;
```

### 本题
```cpp
初始将身高看作单位0
因为最后的身高要最高
对l ~ r区间进行差分 -1
要注意两个端点都不需要 -1 或 +1
最后再加上初始的h高度即可
```

### 需注意
```cpp
map或hash判重
两个奶牛的下标不一定A < B
开始给定的I没有用处
```



---

## 作者：小年轻w (赞：8)

这题我们可以将他看成是括号序列,  如果x能看到 y  则围一个x--y的括号， 括号不可能出现跨越的情况，因为不可能出现a x b y即x能看到y，a又能看到b的情况，然后用  f[x]表示x这位 以及y后面几位都要进行的操作，如果x到 y围了一个括号  则f[x]-- ;  f[y]++    为了防止相同的条件重复减  用个map 记录一下， 但还是会出现3 7 和7 3这种本质相同的操作，所以要交换一下。





```cpp
#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;
const int maxn = 100001 ;
map<int,int> mp[maxn] ;
int n,m,id,h,x,y ;
int f[maxn] ;
int main()
{
    scanf("%d%d%d%d",&n,&id,&h,&m ) ;
    for(int i=1;i<=m;i++) 
    {
        scanf("%d%d",&x,&y) ;
        if(x>y) swap(x,y) ; 
        if(mp[x][y]) continue ;
            else mp[x][y]=1 ;
        f[x+1]--;   f[y]++;
    }
    for(int i=1;i<=n;i++) 
    {
        f[i] = f[i]+f[i-1] ;
        printf("%d\n",f[i]+h) ;
    }
    return 0;
}
```

---

## 作者：Sakura_nameless (赞：7)

1.我们可以用数组cow处理哪一个区间的牛比两边的牛矮（找可以对视的牛，每对可以对视的牛之间的牛一定比它们矮，cow[a+1]~cow[b]），最后再加上最高的牛的身高则为解，但是输入每一对是用一个for来标记的话，时间复杂度为n*m,会爆！！！所以我们要换一种方法来预处理。

我们可以先在两端打上标记，在 _cow[a+1]_ 的位置标上-1，在 _cow[b] _(__  不是b-1！！)的位置标上+1（cow[ ]：000-10000+100）

然后一个for跑前缀和统计（cow[ ]:000-1-1-1-1-1000）

  ~(≧▽≦)/~最后再加上最高的牛的身高就ojbk啦~(≧▽≦)/~
  
**  最后提示，**两头牛的对视关系(a,b)可能会重复输入，要特判！！！！！

AC代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
 
using namespace std;
int n,p,h,m,line[10001],cow[10001],x,y;
bool check[10001][10001];
int main()
{
	
	scanf("%d%d%d%d",&n,&p,&h,&m);
	cow[p]=h;
	
	for(int i=1;i<=m;i++)
	{
	    scanf("%d%d",&x,&y);
	    if(x>y) swap(x,y);
	    if (not(check[x][y]))//去重
	    {
	        line[x+1]--; line[y]++;//标记两端
	        check[x][y]=not(check[x][y]);
	    }
    }
    for(int i=1;i<=n;i++)
    {
    	cow[i]=cow[i-1]+line[i];//前缀和
    	printf("%d\n",cow[i]+h);//加入牛的身高，求出每头牛的最大身高
    }
}

```

---

## 作者：Pheasant_YQ (赞：5)


许多dalao的什么 map 差分数组 线段树 蒟蒻都不懂得
~~是我太蒟了 还是您们太dalao辽~~ ~~为什么我感觉就是大模拟~~

这道题第一眼看上去 比较简单
唯一需要注意的点 当x和y相同时 我们不能重复地进行操作 意思也就是 我们必须要判重。

如果 高度a大于高度b的话 则交换一下高度
然后用 sort从小到大排序一下 
接下来判重

```
     if (a [i].x == a [i - 1].x && a [i].y == a [i - 1].y)
	continue;
        cow_height [a [i].x + 1] ++;
        cow_height [a [i].y] --;
```


最后华丽丽地输出

```
        for(int i = 1; i <= n; i ++){
        sum += cow_height [i];
        printf ("%d\n",height - sum);
     }
```


AC代码如下

```
#include<set>  
#include<map>  
#include<list>  
#include<queue> 
#include<fstream> 
#include<stack>  
#include<string>  
#include<cmath>  
#include<ctime>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<cstdio>  
#include<sstream>  
#include<iostream>  
#include<cstdlib>  
#include<cstring> 
#include<iomanip>  
#include<algorithm> 
//气势磅礴的头文件

using namespace std;

int n,l,height,r,cow_height[10005],sum;

int read()
{
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9')
	{
        if(c=='-')
        f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
	{
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}//快读输入 防止被卡

struct yq{
	int x,y;
}a[10005];
/*
a奶牛的高度 x
b奶牛的高度 y
*/

bool cmtp(yq a,yq b)
{
	if(a.x==b.x)
	return a.y<b.y;
	return a.x<b.x;
}
//结构体中的sort快读转化

int main(){	
     n = read ();
	  l = read ();
	  height = read ();
	  r = read ();
     //
     for (int i = 1; i <= r; i ++){
       a [i].x = read ();
	    a [i].y = read ();
       if (a [i].x>a [i].y)
	    swap (a [i].x,a [i].y);
     }
     sort (a + 1,a + r + 1,cmtp);
     for (int i = 1; i <= r; i ++){
        if (a [i].x == a [i - 1].x && a [i].y == a [i - 1].y)
		   continue;
        cow_height [a [i].x + 1] ++;
		   cow_height [a [i].y] --;
     }
     for(int i = 1; i <= n; i ++){
        sum += cow_height [i];
        printf ("%d\n",height - sum);
     }
     return 0;//好习惯
}
```


---

## 作者：suxxsfe (赞：5)

## [P2879 【[USACO07JAN]区间统计Tallest Cow】](https://www.luogu.com.cn/problem/P2879)  
其实我是刚学完哈希用标签搜哈希进来的，但打开一看觉得是个图论....  
看了题解才知道，~~确实和哈希没啥关系~~其实就是用map判重，然而我还是建图跑的拓扑   
看题解区只有一篇类似的做法还不是特详细，~~就赶紧来水一篇~~

-----  
有n只牛，给你r条信息和最高的牛的高度，每条信息$(a,b)$表示$h_a\leq h_b$，且a,b之间所有牛高度比$h_a$低，求每头牛最大高度  
建图时从高的牛连向低的牛，小于的情况边权为1（高度至少要低1）  
对于小于等于的情况当然要让它取等（因为要求最大高度），所以边权应为0  
拓扑时，对于边$(u,v)$，让$h[v]=min(h[v],h[u]-w[i])$，其中$w[i]$是当前边边权  
然后发现这样建图边数是$Rn$的，所以考虑用[线段树优化](https://www.luogu.com.cn/blog/suxxsfe/xian-duan-shu-you-hua-jian-bian)  
在线段树中的点是从$n+1$开始编号，对应我代码里的nn  
最后注意线段树中的边边权也要为0就行了  
```cpp  
#include<cstdio>
#include<algorithm>
#include<queue>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstring>
#define reg register
#define EN std::puts("")
#define LL long long
inline int read(){
	int x=0,y=1;
	char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
int n,nn,maxh,m;
int h[30006],fir[30006],in[30006];
int nex[200006],to[200006],w[200006],edge;
struct tr{
	tr *ls,*rs;
	int id;
}dizhi[20006],*root=&dizhi[0];
int tot;
inline void add(int u,int v,int tmp){
	to[++edge]=v;w[edge]=tmp;
	nex[edge]=fir[u];fir[u]=edge;
}
void build(tr *tree,int l,int r){
	if(l==r) return tree->id=l,void();
	int mid=(l+r)>>1;
	tree->ls=&dizhi[++tot];tree->rs=&dizhi[++tot];
	build(tree->ls,l,mid);build(tree->rs,mid+1,r);
	tree->id=++nn;
	add(tree->id,tree->ls->id,0);add(tree->id,tree->rs->id,0);
	in[tree->ls->id]++;in[tree->rs->id]++;
}
void addtree(tr *tree,int l,int r,int ql,int qr,int u){
	if(ql<=l&&r<=qr) return add(u,tree->id,1),in[tree->id]++,void();
	int mid=(l+r)>>1;
	if(ql<=mid) addtree(tree->ls,l,mid,ql,qr,u);
	if(qr>mid) addtree(tree->rs,mid+1,r,ql,qr,u);
}
std::queue<int>q;
inline void topo(){
	for(reg int i=1;i<=nn;i++){
		h[i]=maxh;
		if(!in[i]) q.push(i);
	}
	while(!q.empty()){
		reg int u=q.front();q.pop();
		for(reg int v,i=fir[u];i;i=nex[i]){
			v=to[i];
			h[v]=std::min(h[v],h[u]-w[i]);
			if(!--in[v]) q.push(v);
		}
	}
}
int main(){
	n=nn=read();read();maxh=read();m=read();//那个输入的i并没有什么用，直接read()掉就行，代码里的m就是题里的R
	reg int a,b;
	build(root,1,n);
	while(m--){
		a=read();b=read();
		add(b,a,0);in[a]++;
		reg int minn=std::min(a,b),maxx=std::max(a,b);
		if(minn<maxx-1) addtree(root,1,n,minn+1,maxx-1,a);//a,b之间至少有一头牛
	}
	topo();
	for(reg int i=1;i<=n;i++) std::printf("%d\n",h[i]);
	return 0;
}

```  
[还有一个相似的题](https://www.luogu.com.cn/problem/P3588)可以去写一下  
[题解](https://www.luogu.com.cn/blog/suxxsfe/solution-p3588)  
那个题是求一种可行方案，但其实就可以当最大值做

---

## 作者：maple_tzc (赞：4)

发一波代码，，参考过多位大佬的博客后，，终于打出来了

我们建立一个数组c，数组中起初全为0.若一条关系A和B可以互相看见，那么则把数组c中A+1到B-1的数都减去1，意思是在A和B中间的牛，身高至少要比他们小1.因为第p头牛是最高的，所以最终c[p]一定为0.其他的牛与第p头牛的身高差距就体现在数组c中。

换而言之，最后第i头牛的身高就等于H+c[i]。
------------
我们之后可以用前缀和进行优化，优化之后的算法

****把对一个区间操作转化为左，右两个端点上的操作，再通过前缀和得到问题的解，算法时间复杂度为O(N+M).****

感谢LYD神犇的算法竞赛进阶指南，各位有兴趣的可以看看  QAQ
~~~~
#include<bits/stdc++.h>
using namespace std;
int c[10010],d[10010];
map<pair<int ,int>,bool> eee;
int main(){
	int n,p,h,m;
	scanf("%d%d%d%d",&n,&p,&h,&m);
	for (int i=1; i<=m; i++){
		int a,b;
		scanf("%d%d",&a,&b);
		if(a>b) swap(a,b);
		if (eee[make_pair(a,b)]) continue;
		d[a+1]--,d[b]++;
		eee[make_pair(a,b)]=true;
	}
	for (int i=1; i<=n; i++){
		c[i]=c[i-1]+d[i];
		printf("%d\n",h+c[i]);
	}
	cout<<endl;
	return 0;
}
~~~~

---

## 作者：木木！ (赞：2)

首先，题目条件里面很麻烦的一点是它要求(a,b)里面b>=a，而目前的种种模型里面对此并没有合适的建模。

但是，仔细思考就会发现，这个条件并不会影响答案。

如果b<a的话，说明一定有一个数c，使得b<c<=a，否则由于题目要求最大，可以将b调整到b=a而不影响题意。

然后我们对c的位置进行分类讨论

1. c在(a,b)上
2. c在ab外，离b较近
3. c在ab外，离a较近

可以看出，第一种情况肯定不成立，因为要求(a,b)中每一个数x都满足x<a<=b，因此必有x<b。

第二种情况，如果c与ab无关，那么就可以将b调整到b=a，所以必然存在一个关系使得b<c。同时要满足c<=a，由于不存在区间交错的情况（证明略），只能是因为存在一个关系(c,x)，其中x位于(a,b)中或a上。

这里就会有x>=b，然而b>=a>=x，所以唯一可能的关系只有a=b=x。

第三种情况，证明略。

因此，b>=a条件并不会影响答案，可以开心愉快地套模板了。

## 方案1：线段树建边+拓扑排序

由于这里给的是偏序关系，因此可以考虑拓扑排序（拓扑排序=差分约束系统+单边权图中BFS求最短路）

然而，直接建边是$\Theta(RN)$的，肯定会炸，这时候就要考虑线段树建边。

具体不阐述，代码没有，时间复杂度$\Theta((R+N)logN)$

## 方案2：朴素暴力算法

我们每次考虑一个关系。

对于一个数组A和一个关系(a,b)，如果A满足在其之前的所有关系R'，可以通过操作使A满足(a,b)同时不破坏R'

稍微想想就能知道，如果要插入一个新关系，那么只需要将(a,b)中间的数都-1，且最小-1。

证明略。

再考虑到我们需要R次区间减，所以可以直接上差分数组，$\Theta(R+N)$解决问题。再加上map判重，$\Theta(RlogR+N)$

代码：

```cpp
#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;

int loi[10005];

map<int,map<int,bool> > mmp;

int main()
{
	int n,i,h,r;
	scanf("%d%d%d%d",&n,&i,&h,&r);
	for(int i=1; i<=r; ++i)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		if(a>b)
		{
			swap(a,b);
		}

		if(!mmp[a][b])
		{
			mmp[a][b] = 1;
			--loi[a+1];
			++loi[b];
		}
	}

	int cur = 0;
	for(int i=1; i<=n; ++i)
	{
		cur += loi[i];
		printf("%d\n",h+cur);
	}
}
```

---

## 作者：world_romantic_xebec (赞：2)

这道题之前没有判重，所以50分，这次加了一个mp数组就过了，标记是否有这个，比如5  7和 7  5是一样的，思路很简单，就是每次将牛a+1和牛b-1，因为这样可以让他们看见，仅此而已，简略朴素。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=10010;
int c[maxn];
int main (){
	int n,p,h,m;
	cin>>n>>p>>h>>m;
	memset(c,0,sizeof(c));
	for (int i=1;i<=m;i++)
	{
		int a,b;
		cin>>a>>b;
		 for (int j=a+1;j<=b-1;j++)
		 {
		 	c[j]++;
		 }
	}
	
	for (int i=1;i<=n;i++)
	{
		cout<<h-c[i]<<endl;
	}
}
```

---

## 作者：清风我已逝 (赞：1)

我并不认为我的程序是正解，反而感觉洛谷的数据太水了，居然没把我卡掉

算法： 贪心+模拟

贪心：按照区间大小排序

```cpp
bool cmp(node A,node B){
	return (A.a2-A.a1)>(B.a2-B.a1);
}
```

模拟：显然，记录两头端点，中间值要小于端点最小值

```cpp
#include<bits/stdc++.h>

using namespace std;

int n,I,H,r,h[20005];
struct node{
	int a1,a2;
}e[20005];

bool cmp(node A,node B){
//	if(A.a1!=B.a1) return A.a1<B.a1;
//	else return A.a2>B.a2;
	return (A.a2-A.a1)>(B.a2-B.a1);
}

int main()
{
	cin>>n>>I>>H>>r;
//	memset(h,H,sizeof(h));
	for(int i=1;i<=n;i++) h[i]=H;
	for(int i=1;i<=r;i++){
		cin>>e[i].a1>>e[i].a2;
		if(e[i].a1>e[i].a2) swap(e[i].a1,e[i].a2);
	}sort(e+1,e+1+n,cmp);
	for(int i=1;i<=r;i++){
		int u=e[i].a1,v=e[i].a2,w;
		w=min(h[u],h[v]);
		for(int i=u+1;i<v;i++){
			if(h[i]>=h[u]||h[i]>=h[v]) h[i]=w-1;
		}
	}
	for(int i=1;i<=n;i++) printf("%d\n",h[i]);
	return 0;
}
```

---

## 作者：ViXbob (赞：0)


想学更多姿势就进入我的博客来查看吧[戳这里(\*/ω＼*)吧](http://www.vixbob-lwc.pw)

## 解题思路

一颗支持区间最值和区间修改的线段树+贪心

贪心思路就是先处理长的区间，因为长的区间更容易去影响其他的区间

在就是对每个区间进行处理，首先查询两个端点$left$和$right$的值，如果$left>right$修改$left$,因为右端点可以看见左端点，所以$left \leq right$

再对$[left+1,right-1]$中的的每一个值进行修改就好了，最后递归输出每一个值

## 实现代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
using namespace std;
const int MAXN=1e4+10;
int N,I,H,R,num[MAXN];
struct NODE{int l,r,c;}e[MAXN];
struct node{int sum,tag;}t[MAXN<<2];
inline int read(){
    char ch=getchar();int u=0,f=1;
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){u=u*10+ch-48;ch=getchar();}return u*f;
}
inline bool cmp(NODE x,NODE y){return x.c>y.c;}
inline void pushup(int p){
    t[p].sum=max(t[ls].sum,t[rs].sum);
}
inline void pushdown(int p){
    if(t[p].tag==0)return;
    if(t[ls].sum>t[p].tag)t[ls].sum=t[p].tag,t[ls].tag=t[p].tag;
    if(t[rs].sum>t[p].tag)t[rs].sum=t[p].tag,t[rs].tag=t[p].tag;
    t[p].tag=0;
}
inline void build(int l,int r,int p){
    t[p].sum=H;if(l==r){num[r]=p;return;}
    build(l,mid,ls);build(mid+1,r,rs);
}
inline void modify(int l,int r,int ql,int qr,int p,int x){
    if(ql>qr)return;
    if(l==ql&&r==qr){if(t[p].sum>x)t[p].sum=x,t[p].tag=x;return;}
    pushdown(p);
    if(qr<=mid)modify(l,mid,ql,qr,ls,x);
    else if(ql>mid)modify(mid+1,r,ql,qr,rs,x);
    else modify(l,mid,ql,mid,ls,x),modify(mid+1,r,mid+1,qr,rs,x);
}
inline int query(int l,int r,int ql,int qr,int p){
    if(ql>qr)return -1;
    if(l==ql&&r==qr)return t[p].sum;
    pushdown(p);
    if(qr<=mid)return query(l,mid,ql,qr,ls);
    else if(ql>mid)return query(mid+1,r,ql,qr,rs);
    else return max(query(l,mid,ql,mid,ls),query(mid+1,r,mid+1,qr,rs));
}
inline void print(int l,int r,int p){
    if(l==r){printf("%d\n",t[p].sum);return;}
    pushdown(p);
    print(l,mid,ls);print(mid+1,r,rs);
}
int main(){
    N=read();I=read();H=read();R=read();
    for(register int i=1;i<=R;i++){
        e[i].l=read();e[i].r=read();e[i].c=max(e[i].r,e[i].l)-min(e[i].r,e[i].l)+1;
    }
    sort(e+1,e+1+R,cmp);build(1,N,1);
    for(register int i=1;i<=R;i++){
        int r=max(e[i].r,e[i].l),l=min(e[i].r,e[i].l);
        int pos=query(1,N,l+1,r-1,1);
        int left=query(1,N,e[i].l,e[i].l,1);
        int right=query(1,N,e[i].r,e[i].r,1);
        if(left>right){
            t[num[e[i].l]].sum=left=right;
            modify(1,N,e[i].l,e[i].l,1,left);
        }
        modify(1,N,l+1,r-1,1,left-1);
    }
    print(1,N,1);
    return 0;
}
```

---

## 作者：ezоixx130 (赞：0)

本题其实可以转换理解：

把每一个区间[a,b](a<b)从a+1到b连一条线段，最后每个点的最高高度就是**(H-该点被线段覆盖数)**。

所以我们可以用前缀和的思想去快速求出每个点被线段覆盖的次数，具体做法是：

开一个数组c，对于区间[a,b]则**++c[a+1],--c[b];**这样我们只要扫一遍，用ans记录c数组的和，就可以知道每个点被线段覆盖的次数了。


注意：本题的区间有可能出现a>b的情况，需要交换，而且需要去重（C++可以用set，Pascal可以排序一遍后去重）。


C++代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
    int x,y;
    node(int a,int b):x(a),y(b){}
    friend bool operator<(const node &n1,const node &n2)
    {
        return n1.x==n2.x?n1.y<n2.y:n1.x<n2.x;
    }
};
set<node> s;
int n,I,h,r,a,b,c[10001],ans;
int main()
{
    scanf("%d%d%d%d",&n,&I,&h,&r);
    for(int i=1;i<=r;++i)
    {
        scanf("%d%d",&a,&b);
        s.insert(node(min(a,b),max(a,b)));
    }
    for(set<node>::iterator it=s.begin();it!=s.end();++it)
    {
        ++c[(*it).x+1];
        --c[(*it).y];
    }
    for(int i=1;i<=n;++i)
    {
        printf("%d\n",h-(ans+=c[i]));
    }
}
```
Pascal代码：

```pascal
type node=record
            x,y:longint;
          end;
var
  a:array[1..10000]of node;
  c:array[1..10000]of longint;
  n,i,j,p,h,r,t,sum:longint;
procedure sort(l,r:longint);
var
  i,j,x:longint;
  t:node;
begin
  i:=l;
  j:=r;
  x:=a[(l+r)div 2].x;
  repeat
    while a[i].x<x do
      inc(i);
    while a[j].x>x do
      dec(j);
    if i<=j then
    begin
      t:=a[i];
      a[i]:=a[j];
      a[j]:=t;
      inc(i);
      dec(j);
    end;
  until i>j;
  if i<r then sort(i,r);
  if l<j then sort(l,j);
end;
begin
  readln(n,p,h,r);
  for i:=1 to r do
  begin
    readln(a[i].x,a[i].y);
    if(a[i].x>a[i].y)then
    begin
      t:=a[i].x;
      a[i].x:=a[i].y;
      a[i].y:=t;
    end;
  end;
  sort(1,r);
  for i:=1 to r do
  begin
    if((a[i].x<>a[i+1].x) or (a[i].y<>a[i+1].y))then
    begin
      inc(c[a[i].x+1]);
      dec(c[a[i].y]);
    end;
  end;
  sum:=0;
  for i:=1 to n do
  begin
    inc(sum,c[i]);
    writeln(h-sum);
  end;
end.
```

---

