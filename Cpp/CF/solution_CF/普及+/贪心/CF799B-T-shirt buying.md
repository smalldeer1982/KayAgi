# T-shirt buying

## 题目描述

A new pack of $ n $ t-shirts came to a shop. Each of the t-shirts is characterized by three integers $ p_{i} $ , $ a_{i} $ and $ b_{i} $ , where $ p_{i} $ is the price of the $ i $ -th t-shirt, $ a_{i} $ is front color of the $ i $ -th t-shirt and $ b_{i} $ is back color of the $ i $ -th t-shirt. All values $ p_{i} $ are distinct, and values $ a_{i} $ and $ b_{i} $ are integers from $ 1 $ to $ 3 $ .

 $ m $ buyers will come to the shop. Each of them wants to buy exactly one t-shirt. For the $ j $ -th buyer we know his favorite color $ c_{j} $ .

A buyer agrees to buy a t-shirt, if at least one side (front or back) is painted in his favorite color. Among all t-shirts that have colors acceptable to this buyer he will choose the cheapest one. If there are no such t-shirts, the buyer won't buy anything. Assume that the buyers come one by one, and each buyer is served only after the previous one is served.

You are to compute the prices each buyer will pay for t-shirts.

## 样例 #1

### 输入

```
5
300 200 400 500 911
1 2 1 2 3
2 1 3 2 1
6
2 3 1 2 1 1
```

### 输出

```
200 400 300 500 911 -1 
```

## 样例 #2

### 输入

```
2
1000000000 1
1 1
1 2
2
2 1
```

### 输出

```
1 1000000000 
```

# 题解

## 作者：爬行者小郑 (赞：5)

## STL:priority_queue做法

### 一定要注意正反面颜色相同的衣服，在一个优先队列里面不要放两次！（这样没有必要）

主要思路就是按照颜色将衣服放到一个优先队列里面，衣服需要用一个结构体来存储。

结构体里面需要记录编号和价钱，以及正反面的颜色。

买衣服就是从相应优先队列里面拿出来价钱最小的一个。

我们还需要一个数组来记录编号为i的衣服是否被买过。

如果堆顶的衣服被买过，直接pop掉

代码：

```cpp
#include <iostream>//基本输入输出
#include <queue>//一会要用到优先队列
using namespace std;
const int MAXN=200005;
struct Node//衣服
{
	int id,v,col1,col2;//编号，价钱，两个颜色
	bool operator < (const Node &a)const//重载运算符
	{
		return v>a.v;//优先队列默认是大顶堆，所以小于号要变成大于号
	}
}t[MAXN];
priority_queue<Node>q1;//这里我傻了一下……优先队列是可以弄成一个数组的
priority_queue<Node>q2;
priority_queue<Node>q3;
int n,m;
bool vis[MAXN];
int main()
{
	cin>>n;//个数
	for(int i=1;i<=n;i++)cin>>t[i].v;//价钱
	for(int i=1;i<=n;i++)cin>>t[i].col1;//正面颜色
	for(int i=1;i<=n;i++)cin>>t[i].col2;//反面颜色
	for(int i=1;i<=n;i++)
	{
		t[i].id=i;/记录编号
		bool v1=0,v2=0,v3=0;//防止正反面一样被放两次
		if(t[i].col1==1)q1.push(t[i]),v1=1;
		if(t[i].col2==1&&v1==0)q1.push(t[i]);//放过就不要再放了
		if(t[i].col1==2)q2.push(t[i]),v2=1;
		if(t[i].col2==2&&v2==0)q2.push(t[i]);
		if(t[i].col1==3)q3.push(t[i]),v3=1;
		if(t[i].col2==3&&v3==0)q3.push(t[i]);
	}
	cin>>m;//买的个数
	for(int i=1;i<=m;i++)
	{
		int x;
		cin>>x;//要买什么颜色
		
		if(x==1)
		{
			bool flag=0;//看一眼是否可以买到
			while(!q1.empty())
			{
				Node tmp=q1.top();//取出来堆顶
				if(vis[tmp.id])q1.pop();//如果买过就pop掉
				else
				{
					cout<<tmp.v<<" ";flag=1;//成功买到，记录flag
					vis[tmp.id]=1;//记录买过了
					q1.pop();//pop掉
					break;//递前退出while(!q1.empty())的循环
				}
			}
			if(!flag)//没买成
			cout<<-1<<" ";//输出-1（买不到）
		}
		else if(x==2)//其余同理
		{
			bool flag=0;
			while(!q2.empty())
			{
				Node tmp=q2.top();
				if(vis[tmp.id])q2.pop();
				else
				{
					cout<<tmp.v<<" ";
					vis[tmp.id]=1;
					q2.pop();
					flag=1;
					break;
				}
			}
			if(!flag)
			cout<<-1<<" ";
		}
		else if(x==3)//其余同理
		{
			bool flag=0;
			while(!q3.empty())
			{
				Node tmp=q3.top();
				if(vis[tmp.id])q3.pop();
				else
				{
					cout<<tmp.v<<" ";
					vis[tmp.id]=1;
					q3.pop();
					flag=1;
					break;
				}
			}
			if(!flag)
			cout<<-1<<" ";
		}
	}
	return 0;//养成好习惯，竞赛中没有直接爆零
}
```
谢谢大家

---

## 作者：AuroraIris (赞：4)

这题可以用三个排序，同时记录一个bool数组pd,表示当前这件衣服是否被选择
```pascal
var n,m,i,tmp,x,minx,p1,p2,p3,h1,h2,h3:longint;
    a,b,c,d,num,cx,cy,b1,c1,d1:array[0..200001]of longint;
    px:boolean;
    pd:array[0..200001] of boolean;
        procedure sort1(l,r: longint);
      var
         i,j,x,y: longint;
      begin
         i:=l;
         j:=r;
         x:=b[(l+r) div 2];
         repeat
           while b[i]<x do
            inc(i);
           while x<b[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=b[i];
                b[i]:=b[j];
                b[j]:=y;
                y:=b1[i];
                b1[i]:=b1[j];
                b1[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort1(l,j);
         if i<r then
           sort1(i,r);
      end;
    procedure sort2(l,r: longint);
      var
         i,j,x,y: longint;
      begin
         i:=l;
         j:=r;
         x:=c[(l+r) div 2];
         repeat
           while c[i]<x do
            inc(i);
           while x<c[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=c[i];
                c[i]:=c[j];
                c[j]:=y;
                y:=c1[i];
                c1[i]:=c1[j];
                c1[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort2(l,j);
         if i<r then
           sort2(i,r);
      end;
    procedure sort3(l,r: longint);
      var
         i,j,x,y: longint;
      begin
         i:=l;
         j:=r;
         x:=d[(l+r) div 2];
         repeat
           while d[i]<x do
            inc(i);
           while x<d[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=d[i];
                d[i]:=d[j];
                d[j]:=y;
                y:=d1[i];
                d1[i]:=d1[j];
                d1[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort3(l,j);
         if i<r then
           sort3(i,r);
      end;
begin
    readln(n);
    for i:=1 to n do
        read(a[i]);
    readln;
    for i:=1 to n do
        read(cx[i]);
    readln;
    for i:=1 to n do
        read(cy[i]);
    readln;
    readln(m);
    for i:=1 to m do
        read(num[i]);
    for i:=1 to n do
        if (cx[i]=1) or (cy[i]=1) then
            begin
                inc(p1);
                b[p1]:=a[i];
                b1[p1]:=i;//当前这件衣服在原数组中的位置
            end;
    for i:=1 to n do
        if (cx[i]=2) or (cy[i]=2) then
            begin
                inc(p2);
                c[p2]:=a[i];
                c1[p2]:=i;
            end;
    for i:=1 to n do
        if (cx[i]=3) or (cy[i]=3) then
            begin
                inc(p3);
                d[p3]:=a[i];
                d1[p3]:=i;
            end;
    fillchar(pd,sizeof(pd),false);
    sort1(1,p1);
    sort2(1,p2);
    sort3(1,p3);
    h1:=1;
    h2:=1;
    h3:=1;//三个指向当前这种颜色的最低价格的衣服在各自数组中的位置
    for i:=1 to m do
        begin
            if num[i]=1 then
                begin
                    while pd[b1[h1]] do inc(h1);//这件衣服如果被选了，那么往下找第一件没有选择的
                    if h1>p1 then begin write(-1,' '); continue; end;//如果没衣服了，输出-1
                    write(b[h1],' ');
                    pd[b1[h1]]:=true;//这件衣服选了
                    inc(h1);//到下一件衣服
                end;//下面的同理
            if num[i]=2 then
                begin
                    while pd[c1[h2]] do inc(h2);
                    if h2>p2 then begin write(-1,' '); continue; end;
                    write(c[h2],' ');
                    pd[c1[h2]]:=true;
                    inc(h2);
                end;
            if num[i]=3 then
                begin
                    while pd[d1[h3]] do inc(h3);
                    if h3>p3 then begin write(-1,' '); continue; end;
                    write(d[h3],' ');
                    pd[d1[h3]]:=true;
                    inc(h3);
                end;
        end;
end.
```

---

## 作者：CaiXY06 (赞：3)

裸的模拟题，我们按顺序将 T-shirt 售出给顾客，然后将这件 T-shirt 打上标记，表示已售。

为了保证价格最便宜，我们可以使用 **STL** 中的 **优先队列** ，对于每种颜色都开一个小根堆。

```
人类的本质是什么？ 那就是偷懒。——佚名
```

由于优先队列默认是大根堆，为了避免写重载运算符，我们可以将价格取相反数，并用 **pair** 记录价格和编号，实现偷懒。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,x,p[200010];
bool vis[200010];
priority_queue<pair<int,int> >Q[5];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&p[i]);
	for(int i=1;i<=n;i++)scanf("%d",&x),Q[x].push(make_pair(-p[i],i));
	for(int i=1;i<=n;i++)scanf("%d",&x),Q[x].push(make_pair(-p[i],i));
	scanf("%d",&q);
	while(q--){
		for(int i=1;i<=3;i++)while(!Q[i].empty()&&vis[Q[i].top().second])Q[i].pop();
		scanf("%d",&x);
		if(Q[x].empty())printf("-1 ");
		else{
			printf("%d ",-Q[x].top().first);
			vis[Q[x].top().second]=1;
		} 
	}
	return 0;
}
```

---

## 作者：优少 (赞：1)

**STL大法好!!!**

**用三个优先级队列记录每件衣服的价钱，堆里存放价钱**

**因为是按照顺序买衣服**

**所以每次取堆里最小的就好了**

**但是一个问题浮现了出来**

**如何处理别人已经拿过的衣服？？？**

**于是就将优先级队里存放的改为一个结构体，记录价钱和编号**

**用vis数组记录是否已经被取走**

**如果堆空就输出-1**

# 细节见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct SYM{
	int p,id;
	bool operator<(const SYM &a)const{
		return a.p<p;
	}
}clo[200010];
int vis[200010],c,n,m;
priority_queue<SYM> q[4];
int main(){
	//freopen("c.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%d",&clo[i].p);
    	clo[i].id=i;
    }
    for(int i=1;i<=2*n;i++){
        scanf("%d",&c);
		if(i>n) q[c].push(clo[i-n]);   //怼到堆里
		else q[c].push(clo[i]);
	}
    scanf("%d",&m);
	for(int i=1;i<=m;i++){
		int hh=1;
    	scanf("%d",&c);
    	if(q[c].empty()){
		      printf("-1 ");
		      continue ;
		}
    	while(vis[q[c].top().id]){ 
		      q[c].pop();          //如果已经拿过就弹出拿下一个
		      if(q[c].empty()){         
		         printf("-1 ");
		         hh=0;
		         break;
			  }
        }
    	if(hh) printf("%d ",q[c].top().p),vis[q[c].top().id]=1,q[c].pop();    //买最便宜衣服，记录衣服已经买过，弹出这件衣服
    }
    return 0;
} 
```



---

## 作者：xin700 (赞：0)

这个题目并不是一道很难的题目，但是信息量还是不小。

东西比较多，处理起来比较麻烦。

但是我并没有用像其他题解所说的 `priority_queue`，因为这样会非常慢。

我们发现颜色数量很少，所以我们就开 $3$ 个 `vector` 来记录一下所有的衬衫。

然后分别用三个**单调指针**来扫就行了。

因为每个顾客只会考虑自己，所以我们对于每个询问只需要查询他所想要的那个 `vector` 里面的区间就行了。

一个细节就是说在移动完单调指针之后，要注意 `vector` 越界问题，特殊判断一下就行了。

```cpp
#include<bits/stdc++.h>
using std::cout; using std::endl;
#define try(i,a,b) for(register signed i=a;i<=b;++i)
#define throw(i,a,b) for(register signed i=a;i>=b;--i)
#define go(i,x) for(register signed i=head[x],y=edge[i].ver;i;i=edge[i].next,y=edge[i].ver)
namespace xin_io
{
	#define file(a) FILE *FI = freopen(#a".in","r",stdin); FI = freopen(#a".out","w",stdout)
	#define sb(x) cout<<#x" = "<<x<<' '
	#define jb(x) cout<<#x" = "<<x<<endl
	#define debug cout<<"debug"<<endl
	#define gc() p1 == p2 and (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin),p1 == p2) ? EOF : *p1++
	#define scanf ak = scanf
	char buf[1<<20],*p1 = buf,*p2 = buf; int ak; typedef long long ll; typedef unsigned long long ull;
	class xin_stream{public:template<typename type>inline xin_stream &operator >> (type &s)
	{
		register int f = 0;s = 0; register char ch = gc();
		while(!isdigit(ch)) {f |= ch == '-'; ch = gc();}
		while( isdigit(ch)) s = (s << 1) + (s << 3) + (ch  xor 48),ch = gc(); return s = f ? -s : s,*this;
	}}io;
}
using namespace xin_io;static const int maxn = 1e6+10,inf = 1e9+7;const ll llinf = 1e18+7;
#define int long long
auto max = [](int x,int y) -> int{return x > y ? x : y;}; auto min = [](int x,int y) -> int{return x < y ? x : y;};
namespace xin
{
	int n,m;
	int p[maxn],a[maxn],b[maxn];
	int zhi[10];
	class xin_data
	{
		private:
			friend bool operator < (xin_data x,xin_data y)
			{return x.pri < y.pri;}
		public:
			int pri,id;
			xin_data(){}
			xin_data(int pri,int id):pri(pri),id(id){}
	};
	bool vis[maxn];
	std::vector<xin_data>ton[10];
	inline short main()
	{
		io >> n;
		try(i,1,n) io >> p[i];
		try(i,1,n) io >> a[i];
		try(i,1,n) io >> b[i];
		

		try(i,1,3) ton[i].reserve(n+2);
		try(i,1,n)
		{
			ton[a[i]].push_back(xin_data(p[i],i));
			ton[b[i]].push_back(xin_data(p[i],i));
		}
		try(i,1,3) std::sort(ton[i].begin(),ton[i].end());

		io >> m;
		try(i,1,m)
		{
			register int x; io >> x;
			while(zhi[x] < ton[x].size() and vis[ton[x][zhi[x]].id]) zhi[x] ++;
			if(zhi[x] < ton[x].size()) vis[ton[x][zhi[x]].id] = 1;
			if(zhi[x] == ton[x].size()) printf("-1 ");
			else printf("%lld ",ton[x][zhi[x]].pri);
		}

		return 0;
	}
}
signed main() {return xin::main();}
```

---

## 作者：王熙文 (赞：0)

这是一篇桶 + 排序（注意不是桶排序）的题解。

## 解题思路：

因为 $a_i$ 和 $b_i$ 都只有 $3$ 种可能，所以一共只有 $6$ 种（当 $a_i$ 和 $b_i$ 不同时，两种排列算一种）：$(1,1),(1,2),(1,3),(2,2),(2,3),(3,3)$。可以考虑对每一种情况暴力开桶，一共要开 $6$ 个桶，分别为每件 T 恤颜色的组合。桶里面存放的是这样的所有组合的价格。

将每个桶中的价钱从小到大排序，因为每个顾客来的时候要选价格最小的。

要定义 $6$ 个指针，表示当前这 $6$ 个桶中的元素最早的哪一个还没有被买，这些指针的初始值为 $1$。

还要将每个桶的最后一个元素的下一个设为一个比较大的值，这样方便求最小值，因为每次求最小值如果要特判这个桶内的元素是否都被买了太麻烦了。

对于每一个顾客，会有 $3$ 个桶来选择，每一次选这三个桶当前值最小的那个 T 恤。特别的，当三个桶都没有元素的时候（这三个桶的三个指针都为元素值加一的时候），输出 `-1`。



## 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxX=1e9+1e8;

int p[200010],a[200010],b[200010];

int prc1[200010],prc2[200010],prc3[200010],prc12[200010],prc23[200010],prc13[100010]; // 6 个桶，存放当前颜色组合的所有 T 恤的价格

int main()
{
    int n,m,x;
    int zz1=0,zz2=0,zz3=0,zz12=0,zz23=0,zz13=0;
    int p1=1,p2=1,p3=1,p12=1,p23=1,p13=1;
    scanf("%d",&n);
    for(int i=1; i<=n; ++i) scanf("%d",&p[i]);
    for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
    for(int i=1; i<=n; ++i) scanf("%d",&b[i]);
    for(int i=1; i<=n; ++i) // 分类讨论每一种组合，放到对应的桶里
    {
        if(a[i]==1 && b[i]==1) prc1[++zz1]=p[i];
        if(a[i]==2 && b[i]==2) prc2[++zz2]=p[i];
        if(a[i]==3 && b[i]==3) prc3[++zz3]=p[i];
        if((a[i]==1 && b[i]==2) || (a[i]==2 && b[i]==1)) prc12[++zz12]=p[i];
        if((a[i]==2 && b[i]==3) || (a[i]==3 && b[i]==2)) prc23[++zz23]=p[i];
        if((a[i]==1 && b[i]==3) || (a[i]==3 && b[i]==1)) prc13[++zz13]=p[i];
    }
    sort(prc1+1,prc1+zz1+1); // 将每个桶中元素从小到大排序
    sort(prc2+1,prc2+zz2+1);
    sort(prc3+1,prc3+zz3+1);
    sort(prc12+1,prc12+zz12+1);
    sort(prc23+1,prc23+zz23+1);
    sort(prc13+1,prc13+zz13+1);
    prc1[zz1+1]=maxX,prc2[zz2+1]=maxX,prc3[zz3+1]=maxX,prc12[zz12+1]=maxX,prc23[zz23+1]=maxX,prc13[zz13+1]=maxX; // 最后元素的下一个元素设成比较大的值
    cin>>m;
    for(int i=1; i<=m; ++i)
    {
        cin>>x;
        if(x==1) // 分类讨论每一种颜色，比如 1 就有 1、12、13 这三种
        {
            if(p1>zz1 && p12>zz12 && p13>zz13) printf("-1 ");
            else
            {
                if(prc1[p1]<prc12[p12] && prc1[p1]<prc13[p13]) printf("%d ",prc1[p1++]);
                else if(prc12[p12]<prc1[p1] && prc12[p12]<prc13[p13]) printf("%d ",prc12[p12++]);
                else printf("%d ",prc13[p13++]);
            }
        }
        if(x==2)
        {
            if(p2>zz2 && p12>zz12 && p23>zz23) printf("-1 ");
            else
            {
                if(prc2[p2]<prc12[p12] && prc2[p2]<prc23[p23]) printf("%d ",prc2[p2++]);
                else if(prc12[p12]<prc2[p2] && prc12[p12]<prc23[p23]) printf("%d ",prc12[p12++]);
                else printf("%d ",prc23[p23++]);
            }
        }
        if(x==3)
        {
            if(p3>zz3 && p23>zz23 && p13>zz13) printf("-1 ");
            else
            {
                if(prc3[p3]<prc23[p23] && prc3[p3]<prc13[p13]) printf("%d ",prc3[p3++]);
                else if(prc23[p23]<prc3[p3] && prc23[p23]<prc13[p13]) printf("%d ",prc23[p23++]);
                else printf("%d ",prc13[p13++]);
            }
        }
    }
    return 0;
}
```

---

## 作者：_stellar (赞：0)

我们开若干个优先队列来存储各个颜色的价值，需要顾客选择的时候就依次遍历该颜色所在的队列，遇到被选过的衣服就跳过，输出队首元素值即可。

特判全部都被选择过的情况，输出-1。

注意$priority\_queue$的使用技巧就行了。

```
#include<bits/stdc++.h>
using namespace std;
#define N 200005
#define rep(i,l,k) for(int i=l;i<=k;i++)
int n,m,c[N];
bool vis[N];
struct Neko{
    int a,b,p,id;
    bool operator < (const Neko &zech)const {
        return p>zech.p||(p==zech.p&&id>zech.id);
    }
}E[N];
priority_queue<Neko>q[4];
int ip(){
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)) w|=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return w?-x:x;
}
int main(){
    n=ip();
    rep(i,1,n) E[i].p=ip(),E[i].id=i;
    rep(i,1,n) E[i].a=ip();
    rep(i,1,n) E[i].b=ip();
    rep(i,1,n) q[E[i].a].push(E[i]),q[E[i].b].push(E[i]);
    m=ip();rep(i,1,m){
        c[i]=ip();
        if(q[c[i]].empty()) {puts("-1");continue;}
        int u=q[c[i]].top().id;
        while(vis[u]&&!q[c[i]].empty()){
            q[c[i]].pop();u=q[c[i]].top().id;
        }
        if(q[c[i]].empty()) {puts("-1");continue;}
        printf("%d ",q[c[i]].top().p);vis[q[c[i]].top().id]=1;
    }
    return 0;
}
```


---

