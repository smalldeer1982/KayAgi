# [USACO18DEC] Convention II S

## 题目描述

虽然在接机上耽误了挺长时间，Farmer John 为吃草爱好牛们举行的大会至今为止都非常顺利。大会吸引了世界各地的奶牛。

然而大会的重头戏看起来却给 Farmer John 带来了一些新的安排上的困扰。他的农场上的一块非常小的牧草地出产一种据某些识货的奶牛说是世界上最美味的品种的草。因此，所有参会的 $N$ 头奶牛（$1\le N\le 10^5$）都想要品尝一下这种草。由于这块牧草地小到仅能容纳一头奶牛，这很有可能会导致排起长龙。

Farmer John 知道每头奶牛i计划到达这块特殊的牧草地的时间 $a_i$，以及当轮到她时，她计划品尝这种草花费的时间 $t_i$。当奶牛 $i$ 开始吃草时，她会在离开前花费全部 $t_i$ 的时间，此时其他到达的奶牛需要排队等候。如果这块牧草地空出来的时候多头奶牛同时在等候，那么资历最深的奶牛将会是下一头品尝鲜草的奶牛。在这里，恰好在另一头奶牛吃完草离开时到达的奶牛被认为是“在等待的”。类似地，如果当没有奶牛在吃草的时候有多头奶牛同时到达，那么资历最深的奶牛是下一头吃草的奶牛。

请帮助 FJ 计算所有奶牛中在队伍里等待的时间（$a_i$ 到这头奶牛开始吃草之间的时间）的最大值。

## 说明/提示

在这个例子中，我们有 $5$ 头奶牛（按输入中的顺序编号为 $1\dots 5$）。奶牛 $4$ 最先到达（时间 $10$），在她吃完之前（时间 $27$）奶牛 $1$ 和奶牛 $3$ 都到达了。由于奶牛 $1$ 拥有较深的资历，所以她先吃，从她到达开始共计等待了 $2$ 个单位时间。她在时间 $30$ 结束吃草，随后奶牛 $3$ 开始吃草，从她到达开始共计等待了 $10$ 单位时间。在一段没有奶牛吃草的时间过后，奶牛 $5$ 到达，在她正在吃草的时间里奶牛 $2$ 也到达了，在 $5$ 个单位时间之后能够吃到草。相比到达时间等待最久的奶牛是奶牛 $3$。

## 样例 #1

### 输入

```
5
25 3
105 30
20 50
10 17
100 10```

### 输出

```
10```

# 题解

## 作者：damage (赞：7)

### 题解

```USACO 2018.12月赛 银组 第二题```

其实就是道膜你题~~只会做膜你题的蒟蒻~~

注意到因为有资历程度不同导致的的吃草顺序不同，这里最方便的方法就是用优先队列```priority_queue```，当然要配合着结构体，这时候就要自定义友元结构内比较运算符了（详情见代码）。

然后只要输出了然后按照到达时间拍一下序，用一个变量```et```表示当前吃草的奶牛的结束时间，然后从第一头遍历到最后一头膜你即可（详情见代码注释）。

注意点：

1. 若没有等待的奶牛即直接让当前奶牛上去，不要```push()```再```pop()```了

2. 记得特判当结束时间还小于当前奶牛的到达时间时要```i--```再来一次

3. 遍历完最后记得将所有等待的奶牛一个个放进去吃草统计最大等待时间

---

### 代码

```cpp
#include<stdio.h>
#include<algorithm>
#include<queue>
using namespace std;
int n,et,temp,res;
struct _cow
{
    int a,t,old; //a表示到达时间，t表示吃草时间，old表示资历
    friend bool operator < (_cow x,_cow y) //自定义比较运算符
    {
        return x.old>y.old;
    }
}cow[100010];
bool cmp(_cow x,_cow y)
{
    return x.a<y.a; //按到达时间从先到后排列（先来后到）
}
priority_queue<_cow> wait;
int main()
{
    scanf("%d",&n);
    for(register int i=0;i<n;++i)
    {
        scanf("%d%d",&cow[i].a,&cow[i].t);
        cow[i].old=i; //按输入的先后记录资历
    }
    sort(cow,cow+n,cmp); //排序
    et=cow[0].a+cow[0].t; //记录第一头奶牛的吃草结束时间
    for(register int i=1;i<n;++i)
    {
        if(cow[i].a>=et) //如果这头奶牛可以进去吃了
        {
            if(wait.empty()) et=cow[i].a+cow[i].t; //注意点1
            else
            {
                temp=et-wait.top().a; //用它的结束时间（即这头奶牛的开始吃草时间）减去它的到达时间来计算等待时间
                if(temp>res) res=temp; //找出最大值
                et+=wait.top().t; //更新结束时间
                wait.pop();
                if(et<cow[i].a) --i; //注意点2
                else wait.push(cow[i]); //否则再等
            }
        }
        else wait.push(cow[i]);
    }
    while(!wait.empty()) //注意点3
    {
        temp=et-wait.top().a;
        if(temp>res) res=temp;
        et+=wait.top().t;
        wait.pop();
    }
    printf("%d\n",res);
    return 0;
}
```

---

## 作者：Zenith_Yeh (赞：4)

“要想知正解，就先看范围。”

一看范围，就知道可以用模拟来解决。

题面说：若到达时间一样，则资历大的先吃。所以我们可以用优先队列来排序(其中用结构体)。

**模拟分两步：**

- 将现在已到达的奶牛入优先队列，并计算等待时间更新答案。

- 将已吃完的奶牛弹出。

**代码：**
```cpp
#include<bits/stdc++.h>
#define read() Read<int>()
namespace pb_ds{//优美的快读。
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0;
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100];
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
struct bb
{	int id,arrive,t;
	bool operator <(bb b)const //重载运算符。
	{	return id>b.id;
	}
}op[100005];
int n,now_time,max_time,now;
priority_queue<bb> q;
inline bool cmp(bb a,bb b)//排序方式
{	return a.arrive<b.arrive;
}
int main()
{	cin>>n;
	for(register int i=1;i<=n;++i)op[i].id=i,cin>>op[i].arrive>>op[i].t;
	sort(op+1,op+n+1,cmp);
	now=1; 
	while(now!=(n+1))
	{	q.push(op[now]);
		now_time=op[now].arrive;
		now++;
		while(!q.empty())
		{	bb x=q.top();
			q.pop();
			max_time=max(max_time,now_time-x.arrive);//计算等待时间并更新答案。
			now_time+=x.t;
			for(register int i=now;i<=n;++i)
				if(op[now].arrive<=now_time)
				{	q.push(op[now]);//将已到达的奶牛加入优先队列。
					now++;
				}
				else break;
		}
	}
	cout<<max_time;
	return 0;
}

```


---

## 作者：45dino (赞：4)

做这道题时，我想到了[P2058 海港]，于是想到了可以借鉴的东西：优先队列。(https://www.luogu.com.cn/problem/P2058)

不同之处就在于优先队列在这里用于记录等待中的牛。

优先队列就不讲了（P2058的题解中有一个写得很详细的）~~其实是我写不出来~~先按来到草地的时间排序，再利用优先队列，每次出队时都用当前时间减去入队时间更新最长等待时间，注意如果队列为空但还有奶牛没来时要直接把奶牛加进去（不能让队列为空）

喜闻乐见的代码及部分注释：
```
#include<bits/stdc++.h>
using namespace std;
struct cow{
	int a,b,age;
	friend bool operator < (cow x,cow y)//重载运输符，定义在优先队列中“<”的意思。
	{
		return x.age>y.age;
	}
} c[100001];
bool cmp(cow x,cow y)//定义排序时的规则，任意两个相邻的数都要满足该函数。
{
	return x.a<y.a;
}
int n,cnt=2,now,ans;//now是目前操作的时间点，cnt是已经入队（包括已经出队的数量）
priority_queue<cow> waiting;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int t;
		cin>>c[i].a>>c[i].b;
		c[i].age=i;//由于优先队列是大数在前，小数在后，因为上文定义age是从小往大排，所以这里也要一样。
	}
	sort(c+1,c+n+1,cmp);
	waiting.push(c[1]);
	now=c[1].a;
	while(cnt<=n||!waiting.empty())//只有所以数都进过队列并且都出来了才能结束。
	{
		if(waiting.empty())//特判，如果现在草地上没牛，直接跳到下一头牛来的时间
		{
			waiting.push(c[cnt]);
			now=c[cnt].a;
			cnt++;
		}	
		cow f=waiting.top();//选出吃草的牛
//		cout<<f.age<<endl;
		ans=max(ans,now-f.a);//更新答案
		waiting.pop();
		now+=f.b;//更新时间，现在已经吃完草了
		for(cnt;c[cnt].a<=now&&cnt<=n;cnt++)//从2开始依次入队，直到超过前一头奶牛吃完草的时间
		{
			waiting.push(c[cnt]);
//			cout<<cnt<<" ";
		}
//		system("pause");	
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：chichichichi (赞：3)

一道模拟题

## 思路

大致就是分类讨论。根据**到达时间的先后顺序**考虑一头奶牛 $w$ 到达后的情况

1. 草地上没有奶牛在吃草。

	<1> 已经有奶牛在排队。
    
    让队首的奶牛去吃草，如果队首奶牛吃完草的时间仍然比 $w$ 的到达时间早，则重新讨论 $w$ 到达时的情况，否则让 $w$ 去排队。
    
    <2> 没有奶牛在排队。
    
    $w$ 可直接去吃草，不需要等待。

2. 草地上已经有奶牛在吃草。

	$w$ 要去排队。
    
#### 解释一下 `1.<1>`的情况下为什么要这么做。

因为我们只有在一头奶牛到达时才去看草地上有没有奶牛并进行出队操作，中间会间隔很长一段时间，出队操作相当于**延迟**了。

比如： 奶牛 **2**到达时奶牛 **1**在吃草，那么奶牛 **2**入队等待，直到 奶牛 **3** 到达时状态才会改变。假设奶牛 **3** 到达时间为 $10$，而奶牛 **2**在 $3$ 时就可以进去吃草，并在 $5$ 时吃完离开。奶牛**3** 在 $10$时 到达时状态仍是 奶牛**1** 在吃草，奶牛**2**在排队，但奶牛 **2** 实际上是吃完离开的，所以我们要像上面所说的去操作。

#### 如何判断有没有奶牛在草地上

在每个奶牛进入草地吃草时记录它吃完草离开的时间，若后来的奶牛到达时间 **大于** 这个时间，说明它已经离开了，草地上没有奶牛。反之则有。

#### 如何排队

题目说要根据资历来排队，我们就使用 STL 中的优先队列`priority_queue`，相当于大根堆。并将元素取反放入，让其实现小根堆的功能。

#### 答案的更新

在每个奶牛去吃草的时候计算一下它等待了多久，并更新答案。

注意在遍历完所有奶牛之后队伍中可能还有奶牛在排队，要将它们全部出队，并更新答案。



### Before the Code

因为思路和第二篇题解一样，代码就差不多，不想放来着……但是本题解主要是讲解思路，代码可以辅助理解并展示实现细节，就放上了。如果发现本题解中的错误或有疑问，欢迎评论或私信。

#### Enjoy the Code
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=100005;
int n,vis,ans;
struct node{
	int a,t,id,ed;
	bool operator <(const node x)const
	{
	if(x.a<a)
	return 0;
	if(x.a>a)
	return 1;
	return x.id>id;
	}
}c[maxn];
priority_queue<pair<int,int> >q;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&c[i].a,&c[i].t);
		c[i].id=i;
	}
	sort(c+1,c+1+n);
	int x;
	vis=c[1].a+c[1].t;
	for(int i=2;i<=n;i++)
	{
		if(c[i].a>=vis)// the last cow has done
		{
			if(!q.empty())//need wait
			{
				int x=q.top().second;
				q.pop();
				ans=max(ans,vis-c[x].a);
				vis+=c[x].t;
				if(vis<c[i].a)
				--i;
				else			
				q.push(make_pair(-c[i].id,i));
			}else// no need to wait
				vis=c[i].a+c[i].t;
		}
		else// the last cow hasn't done
		{
			q.push(make_pair(-c[i].id,i));
		}
	}
	while(!q.empty())
	{
		int x=q.top().second;
		q.pop();
		ans=max(vis-c[x].a,ans);
		vis+=c[x].t;
	}
	printf("%d",ans);
	return 0;
}
```

### See Ya ！
    

---

## 作者：sycqwq (赞：2)

分析：简单的暴力

根据题意模拟即可

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int id,a,t,s;
}a[1000005];
int n;
int cmp(node s1,node s2)
{
	if(s1.a!=s2.a)
	return s1.a<s2.a;
		return s1.id<s2.id;
}

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin>>n;
	
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].a>>a[i].t;
		a[i].s=a[i].t+a[i].a;
		a[i].id=i;
	}
	int s=0,k=1;
	sort(a+1,a+n+1,cmp);
//	for(int i=1;i<=n;i++)
//	{
//		cout<<a[i].a<<' ';
//		
//	}
	while(k<=n)
	{
		int tp=19260817,tt=0,t=k+1;
		for(int i=t;i<=n;i++)//找等候的奶牛中资历最深的
		{
//			cout<<i<<' ';
			if(a[i].a>a[k].s)
				break;
			if(a[i].id<tp)
			{
				tp=a[i].id;
				tt=i;
			}
		}
//		cout<<endl;
		if(tt!=0){//可能有为0的情况，代表没有奶牛等待
		s=max(s,a[k].s-a[tt].a);//等待时间
//		cout<<a[k].s<<' '<<a[tt].a<<' '<<a[tt].s<<' '<<a[tt].id<<' '<<s<<' '<<k<<' '<<tt<<' '<<tp<<endl;
		a[tt].s=a[k].s+a[tt].t;//吃完的结束时间
		swap(a[k+1],a[tt]);//因为享用的是奶牛tt，这是k+1好奶牛还没有享用，需要交换位置
		}
		++k;
	}
	cout<<s;
	return 0;
}


```

---

## 作者：slzs (赞：1)

目前最快代码。

这是一道比较简单的模拟题，只要按题意模拟就好了。

代码和注释：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <iomanip>
#define int long long 
using namespace std;
int n,top=0,maxn=0;
struct A{int tim,cost,lis;}a[101000];
inline bool cmp(A E,A F){return E.tim<F.tim;}
priority_queue<pair<int ,int > >q;
inline int read()
{
	int x=0,minus=0;char ch;
	while (!isdigit(ch=getchar())) minus|=(ch=='-');
	while (isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return minus?-x:x;
}
signed main()
{
	n=read();
	for (int i=1;i<=n;++i) a[i].tim=read(),a[i].cost=read(),a[i].lis=i;//lis为资历大小
	sort(a+1,a+1+n,cmp);//按到来时间的先后排序
	q.push(make_pair(-a[1].lis,1));//插入第一个
	for (int i=2;!q.empty();)//i从２开始
	{
		int x=q.top().second; q.pop();//取出当前　在排队且资历最大　或　无人排队且最先来的
		if (top<a[x].tim) top=a[x].tim+a[x].cost;//无人排队且最先来的花的时间
		else maxn=max(maxn,top-a[x].tim),top+=a[x].cost;//在排队且资历最大花的时间
		while (i<=n&&a[i].tim<=top) q.push(make_pair(-a[i].lis,i)),++i;//要排队
		if (i<=n&&q.empty()) q.push(make_pair(-a[i].lis,i)),++i;//不用排队
	}
	printf("%lld\n",maxn);
	return 0;
}
```


---

## 作者：__Hacheylight__ (赞：1)

T2 Convention II

【题意】

有n头奶牛到x地。他们有秩序的吃草。吃草顺序很特殊：如果你到时没有其他奶牛，那么你就会先吃；如果已经有其他奶牛等候了，下一头进食的是资历最高的奶牛。

每头奶牛进食长度不等，询问等候时间最长的奶牛等了多久。

【分析】

很容易想到优先队列

先对所有牛按照到达时间排序。

然后我们就按照时间发展这样枚举下去，

当一头牛吃好后，我们把已经在等待的牛领出来，扔进优先队列里头，优先队列按照资历排序依次出列，进队时顺便记录时间戳，然后和现在吃草时间做差取max

写代码细节有一些，慢慢调吧。

大概思路就是这样吧，也没有卡什么，数据也蛮水的。

【代码】

```cpp
#include <bits/stdc++.h>
using namespace std ;

#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define Rep(i, a, b) for (int (i) = (a) - 1; (i) < (b); (i)++)
#define REP(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define Sort(a, len, cmp) sort(a + 1, a + len + 1, cmp)
#define ass(a, sum) memset(a, sum, sizeof(a))

#define ls ((rt) << 1)
#define rs ((rt) << 1 | 1)
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define ENDL cout << endl
#define SZ(x) ((int)x.size())

typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef pair <int, int> pii ;
typedef pair <ll, ll> pll ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
typedef map <ll, ll> mll ;

const int N = 100010 ;
const double eps = 1e-8 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const double dinf = 1e30 ;
const int MOD = 1000000007 ;

inline int read(){
    int X = 0, w = 0 ;
    char ch = 0 ;
    while (!isdigit(ch)) { w |= ch == '-' ; ch = getchar() ; }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar() ;
    return w ? - X : X ;
}

void write(int x){
     if (x < 0) putchar('-'), x = - x ;
     if (x > 9) write(x / 10) ;
     putchar(x % 10 + '0') ;
}

void print(int x) {
    cout << x << endl ;
    exit(0) ;
}

void PRINT(string x) {
    cout << x << endl ;
    exit(0) ;
}

void douout(double x){
     printf("%lf\n", x + 0.0000000001) ;
}

struct cow {
	int tim, len, q ;
	bool operator <(const cow &a) const {
		return q > a.q ;
	}
} a[N << 1] ;

bool cmp(cow a, cow b) {
	if (a.tim == b.tim) return a.q < b.q ;
	else return a.tim < b.tim ;
}

int n, ans, cnt ;
priority_queue <cow> q ;

int main() {
	scanf("%d", &n) ;
	for (int i = 1, tim, len; i <= n; i++) {
		scanf("%d%d", &tim, &len) ;
		a[++cnt] = (cow) {tim, len, i} ;
	} 
	sort(a + 1, a + n + 1, cmp) ;
	int nowtim = 0, head = 1 ;
	while (head <= n) {
		while (!q.empty()) {
			cow now = q.top() ; q.pop() ;
			ans = max(ans, nowtim - now.tim) ;
			nowtim += now.len ;
			while (head <= n) {
				if (a[head].tim <= nowtim)  q.push(a[head]), head++ ;
				else break ;
			}
		}
		q.push(a[head]) ;
		if (head < n) head++ ;
		nowtim = q.top().tim ;
 	}
	printf("%d\n", ans) ;
}
```

---

## 作者：羚羊WANG (赞：0)

根据题目可知，$N <= 100000$ ,可以考虑$O ( n * log (n)) $时间复杂度的算法

把每一头奶牛到达的时间用结构体记录下来，按照到达时间来排序

每次等到当前奶牛吃完奶之后，我们可以将此时所有在排队的奶牛求出来，按照
经验值为关键字，加入一个优先队列，队列的队首就是下一个吃奶的奶牛

就按照这样的方法，我们可以一个一个的求出吃奶的奶牛

最后，总时间复杂度$O ( n * log (n)) $

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
struct node{
	int pos;
	int id;
	bool operator < (const node &x) const {
		return id>x.id;
	}
	bool operator > (const node &x) const {
		return id<x.id;
	}
};
int n;
int sum;
priority_queue<node> q;
struct Node{
	int drink_time;
	int drink_start;
	int arrive;
	int start_id;
}e[100010];
int total_duration;
int maxn;
inline bool cmp(Node a,Node b){
	if(a.arrive!=b.arrive)
		return a.arrive<b.arrive;
	return a.start_id<b.start_id;
}
signed main(){
	n=read();
	for(register int i=1;i<=n;i++)
		{
			e[i].arrive=read();
			e[i].drink_time=read();
			e[i].start_id=i;
		}
	sort(e+1,e+n+1,cmp);
	while(sum<n)	
		{
			sum++;
			node tmp;
			tmp.id=e[sum].start_id;
			tmp.pos=sum;
			total_duration=e[sum].arrive;
			q.push(tmp);
			while(!q.empty())
				{
					node Tmp;
					Tmp=q.top();
					q.pop();
					e[Tmp.pos].drink_start=total_duration;
					total_duration+=e[Tmp.pos].drink_time;
					while(e[sum+1].arrive<=total_duration)
						{
							if(sum==n)
								break;
							sum++;
							node l;
							l.pos=sum;
							l.id=e[sum].start_id;
							q.push(l);
						}
//					printf("%lld: %lld,%lld\n",e[Tmp.pos].start_id,e[Tmp.pos].drink_start,e[Tmp.pos].arrive);
				}
		}
	for(register int i=1;i<=n;i++)
		maxn=max(maxn,e[i].drink_start-e[i].arrive);
	write(maxn);
	return 0;
}

```


---

