# LOPOV - Lopov

## 题目描述

国家经济形势艰难，政府的农业补贴资金减少，Mirko不得不再次转行，这次他的职业是——小偷。

他的第一票是打劫一家珠宝店。
这家珠宝店有$N$件首饰，每件首饰都有它的质量$M[i]$和价值$V[i]$。Mirko有$K$个袋子来存放他的战利品。每个袋子可以容纳的最大质量是$C[i]$。他计划将所有的战利品存放在这些袋子中，为了防止逃跑时首饰之间互相磨损，每个袋子只放一件首饰。

请你计算出Mirko可以偷到的最大珠宝价值。

## 说明/提示

Mirko将第一件首饰放入第二个包，第三件放入第一个包。
## 【数据规模】
对于15%的数据：$1\le N,K\le 1,000$；

对于25%的数据：$1\le N,K\le 50,000$；

对于100%的数据：$1\le N,K\le 300,000$；$0\le M[i],V[i]\le 1,000,000$；$1\le C[i]\le 100,000,000$；

## 样例 #1

### 输入

```
2 1 
5 10 
100 100 
11```

### 输出

```
10```

# 题解

## 作者：hicc0305 (赞：3)

很简单的一个贪心，就是在背包容量内的物品尽量塞价值大的。

具体做法就是，把背包和物品都按容量排一个序，然后弄两个指针i和j，O(n)扫一遍，对于每一个背包，就塞进去比它容量小且没被选过的物品价值最大的，用优先队列就可以维护了。

```
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int n,m;
int c[300100],f[300100];
struct Book
{
    int w,v,f;
}b[300100];
priority_queue <int> q;
bool cmp1(Book x,Book y) {return x.w==y.w?x.v<y.v:x.w<y.w;}
int read()
{
    int x=0,flag=0;
    char ch=getchar();
    if(ch=='-') flag=1;
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x*=10,x+=ch-'0',ch=getchar();
    if(flag) return -x;
    return x;
}
signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
        b[i].w=read(),b[i].v=read();
    for(int i=1;i<=m;i++)
        c[i]=read();
    sort(b+1,b+n+1,cmp1);
    sort(c+1,c+m+1);
    int j=1,ans=0;b[n+1].w=0x7fffffff;
    for(int i=1;i<=n+1;i++)
    {
        while(b[i].w>c[j])//当前物品容量比背包大了，就把优先队列里面的物品往背包里面塞
        {
            if(!q.empty()) ans+=q.top(),q.pop();
            j++;if(j>m) break;
        }
        if(j>m) break;
        q.push(b[i].v);
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：天权3940 (赞：2)

 这是本蒟蒻看了楼上[@hicc0305](https://www.luogu.com.cn/user/21874)的题解后打的（~~一毛一样的~~）代码，根据个人理解自己加的一些注释

可本蒟蒻还是有些地方不是很理解，望给位大佬指点





```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
#define re register int 
using namespace std;
const int MAX=300001;
struct tq
{
	int m,v;
}q[MAX];
int c[MAX],n,k; 
long long ans;
priority_queue <int> r;
int cmp(tq a,tq b)
{
	if(a.m!=b.m)
		return a.m<b.m;//按m从小到大排 
	return a.v<b.v;//v相等时按m从小到大排 
}
int main()
{
	scanf("%d%d",&n,&k);
	for(re i=1;i<=n;++i)	
		scanf("%d%d",&q[i].m,&q[i].v);
	for(re i=1;i<=k;++i)
		scanf("%d",&c[i]);
	sort(q+1,q+n+1,cmp);
	sort(c+1,c+k+1);//c从小到大排 
  	re j=1;
  	q[n+1].m=0x7fffffff;//将n+1的置为无穷大
	//当i=n+1时，while就不会停下来，就会一直填包直到包填完（j>k) 
	for(re i=1;i<=n+1;++i)
	{
		while(q[i].m>c[j])//第i个物体放不进第j个包 
		{
			if(!r.empty())
				ans+=r.top(),r.pop(); 
			//从优先队列（默认大根堆）中取出里面最大v的放入包中（贪心，贪满足c[j]的物体中v最大的）
			//由于物体按m从小到大排，c也是从小到大
			//取出的物体是在因小于当时的c[j]时放入优队的，其m一定<=现在的c[j] 
			++j;//下一个包 
			if(j>k)
				break;//如果包全部放完的话就break 
		} 
		if(j>k)
			break;//如果包全部放完的话就break 
		r.push(q[i].v); //当q[i]能放入c[j]时，先不急放，将它先放入优队中 
		 
	}
	printf("%lld",ans); 
	
}
```
蒟蒻第一次发题解，望通过

---

## 作者：CQ_Bab (赞：1)

# 思路
我们可以发现一个规律就是我们对于一个袋子一定要放能往其中放中的价值最大的那一个，那么我们就可以得到一种贪心思路。我们先将 $c$ 从小到大排序然后再讲袋子的重量从小到大排序，然后我们就可以用双指针了。

我们用一个大根堆来存能被当前袋子装下的最大价值，然后这里我们可以用大根堆处理即可。

细节见代码。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define w(x)  while(x--)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int n,k;
struct node{
	int m,v;
	friend bool operator < (const node&a,const node&b) {
		if(a.m!=b.m) return a.m<b.m;
		else return a.v>b.v;
	}
}s[300100];
int c[300100];
fire main() {
	in(n),in(k);
	rep(i,1,n) {
		in(s[i].m);
		in(s[i].v);
	}
	rep(i,1,k) in(c[i]);
	sort(c+1,c+1+k);
	priority_queue<int>q;
	sort(s+1,s+1+n);
	int res=false;
	int j=1;
	rep(i,1,k) {
		for(;j<=n&&s[j].m<=c[i];j++) q.push(s[j].v);
		if(q.size()) {
			res+=q.top();
			q.pop();
		}
	}
	cout<<res<<endl;
	return false;
}

```

---

## 作者：yangdezuo (赞：0)

## 思路
根据题意分析，明显可以发现，这是一道贪心题，并且有三种贪心方法：按珠宝重量，按珠宝价值，和按麻袋。

如果按照珠宝重量贪心，那很明显无法确定取到最值。

所以，我们有两种贪心方法：按珠宝价值或按麻袋载重量。
## 1. 按照珠宝价值贪心
也就是说，尽可能地装价值大的珠宝，装每个珠宝选用尽可能小的麻袋。

在这个过程中可以用 set 和一个 cnt 数组维护。

时间复杂度 $O(n \log_2 n)$。
### 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans,x;
struct Node{
	int v,w;
}a[300005];
set<int>s;
int scnt[1000005];
bool cmp(Node x,Node y){
	return (x.w!=y.w?x.w>y.w:x.v<y.v);
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i].v>>a[i].w;
	for(int i=1;i<=m;i++){
		cin>>x;
		s.insert(x);
		scnt[x]++;
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		set<int>::iterator it=s.lower_bound(a[i].v);
		if(it!=s.end()){
			x=*it;
			ans+=a[i].w;
			scnt[x]--;
			if(!scnt[x])s.erase(x);
		}
	}
	cout<<ans;
}
```
## 2. 按照麻袋贪心
对于每一个麻袋，在能装得下的且未被装的珠宝中，尽可能选择价值大的装。

可以用 set 或者 priority_queue 维护
### 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,b[300005],pos=1,ans;
struct node{
	int m,v;
	bool operator<(node &A){//重载运算符
		return m<A.m;
	}
}a[300005];
priority_queue<int>pq;
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i].m>>a[i].v;
	for(int i=1;i<=k;i++) cin>>b[i];
	sort(a+1,a+1+n);
	sort(b+1,b+1+k);
	for(int i=1;i<=k;i++){
		while(pos<=n&&a[pos].m<=b[i]) pq.push(a[pos++].v);
		if(pq.size()){
			ans+=pq.top();
			pq.pop();
		}
	}
	cout<<ans;
}
```

---

## 作者：No21 (赞：0)

### 解题思路

背包？不不不，这显然是一道贪心。

我们要求的是能获得的最大价值，因此我们先以价值排序。对于一个质量为 $M$ 的珠宝，我们将其装进一个容量大于 $M$ 的袋子中容量最小的袋子显然最优（因为已经按照价值排序）。然后我们考虑怎么找到合适的袋子。

1. 暴力找，时间复杂度 $\mathcal O(NK)$，不多讲，一个一个扫，显然是不可取的。

2. 常规二分,对于每个珠宝，二分找上文所说的最优的袋子，但每个袋子只能用一次，所以时间复杂度可能被卡到 $\mathcal O(NK)$，蒟蒻开始也这么想的（找到一个答案后向上查找第一个没被用过的），但是被机房大佬卡了 qwq。

3. 可重集，STL 里自带的一种容器 multiset，一个可以有重复元素的集合，由于底层是红黑树，因此无论是删除还是查找复杂度都很优秀（肯定不会超过 $\mathcal O(\log K)$），因此时间复杂度为 $\mathcal O(\log K)$，$10^6$ 数据可过。

```
#include<bits/stdc++.h>
using namespace std;
namespace TO
{
    const int N=1e6+21;
    int n,k;
    long long ans;
    struct node
    {
        int v,m;
    }au[N];
    int cc;
    multiset <int> c;
    bool cmp(node x,node y)
    {
        return x.v>y.v;
    }
    int mian()
    {
        cin>>n>>k;
        for(int i=1;i<=n;i++)
            cin>>au[i].m>>au[i].v;
        for(int i=1;i<=k;i++)
        {
            cin>>cc;
            c.insert(cc);
        }
        sort(au+1,au+1+n,cmp);
        for(int i=1;i<=n;i++)
        {
            auto it=c.lower_bound(au[i].m);
            if(it==c.end())
                continue;
            else
                c.erase(it);
            ans+=au[i].v;
        }
        cout<<ans<<'\n';
        return 0;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    return TO::mian();
}
```

---

## 作者：lovely_hyzhuo (赞：0)

双倍经验 P6538。

这题双倍经验我交了两页，写篇题解纪念一下。

本来点着背包标签进来的，结果是贪心。

先将物品按照价值从大到小排序，再枚举每个物品。对于每个物品找到第一个容积比它的体积大的背包，放进去，然后 $O(nk)$ 处理。

这样就有 64pts-72pts 的好成绩。

正解是用优先队列。

排序就是将物品按照质量从大到小排序，质量相同就价值大的放到前面。

背包质量从大到小排。

对于一个背包，找一个它能装的且没选过的价值最大的物品，装进去。所以优先队列维护价值最大值，然后模拟。

复杂度 $O(n \log n)$。

代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int v,w;
}a[1000010];
int n,k;
int m[1000010];
int v[1000010];
bool cmp(node a,node b)
{
	if(a.v==b.v)
		return a.w<b.w;
	else
		return a.v<b.v;
}
inline void write(int x)
{
    if(x<0)
	{
    	putchar('-');
		x=-x;
	}
    if(x>9)
    {
    	write(x/10);
	}
    putchar(x%10+'0');
}
inline int read() 
{
     bool f=false; 
	 int x=0;
     char ch=getchar();
     while(ch<'0'||ch>'9') 
	 {
         if(ch=='-') 
		 {
		 	f=true;
		 }
         ch=getchar();
     }
     while(ch>='0'&&ch<='9') 
	 {
         x=(x<<1)+(x<<3)+ch-'0';
         ch=getchar();
     }
     return f?-x:x;
 }
priority_queue <int,vector<int>,less<int> >q;
signed main()
{
	n=read(),k=read();
	for(int i=1;i<=n;i++)
		a[i].v=read(),a[i].w=read();
	for(int i=1;i<=k;i++)
		m[i]=read();
	sort(a+1,a+n+1,cmp);
	sort(m+1,m+k+1);
	int j=1;
	int ans=0;
	for(int i=1;i<=k;i++)
	{
		for(;j<=n&&m[i]>=a[j].v;j++)
			q.push(a[j].w);
		if(!q.empty())
			ans+=q.top(),q.pop();
	}
	write(ans);
	return 0;
}
```


---

