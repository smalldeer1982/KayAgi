# Booking System

## 题目描述

Innovation technologies are on a victorious march around the planet. They integrate into all spheres of human activity!

A restaurant called "Dijkstra's Place" has started thinking about optimizing the booking system.

There are $ n $ booking requests received by now. Each request is characterized by two numbers: $ c_{i} $ and $ p_{i} $ — the size of the group of visitors who will come via this request and the total sum of money they will spend in the restaurant, correspondingly.

We know that for each request, all $ c_{i} $ people want to sit at the same table and are going to spend the whole evening in the restaurant, from the opening moment at 18:00 to the closing moment.

Unfortunately, there only are $ k $ tables in the restaurant. For each table, we know $ r_{i} $ — the maximum number of people who can sit at it. A table can have only people from the same group sitting at it. If you cannot find a large enough table for the whole group, then all visitors leave and naturally, pay nothing.

Your task is: given the tables and the requests, decide which requests to accept and which requests to decline so that the money paid by the happy and full visitors was maximum.

## 样例 #1

### 输入

```
3
10 50
2 100
5 30
3
4 6 9
```

### 输出

```
2 130
2 1
3 2
```

# 题解

## 作者：skyskyCCC (赞：1)

## 前言。
可能是我的最后的几篇题解了。本题要求最大的盈利额，而包括可能的付的钱数和能够容纳的个数，这个好比在一个容器内填充，然后求能填充的最大贡献，显然的贪心。
## 分析。
可以先排除掉人数比所有的座位数都大的数，因为根本坐不开。

首先我们不难想到肯定要让预定金尽可能大的人入座，这样赚到的钱才可能多，如果人数一样，我们就对人数排序，因为我们要尽量让更多的人入座，所以我们要将人数从小到大排序，我们将一组数据分配到所有的桌子中符合要求的最贴近的桌子，可以证明这样是最优的。

如何证明这是最优的呢？我们可以发现，现在我们选取的桌子是局部最优解，因为我们是根据人数排序的，所以在金额相同的情况下，我们可以保证这样使得空出的位子尽可能多来容纳更多的人。如果金额不同，那么因为我们选的是最小的桌子，所以在当前请求后面不可能出现比这个金额更大的情况，即我们现在事实上是局部的贪心最优解，如果更大，人数相近，替换即可。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,k;
int ans,max_p; 
struct node{
	int num;//因为要统计序列，所以记录顺序。 
	int c,p;
	int table,ask=0;
}a[10005];
struct node2{
	int num,lag;
	int ask2=0;
}r[10000];
//上面的两个ask是用来看用没用的。 
bool cmp1(node x,node y){
    return (x.p==y.p)?x.c<y.c:x.p>y.p;
}
bool cmp2(node2 x,node2 y){
	return x.lag<y.lag;
}
//排序人数，金额和桌子的大小。 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].c>>a[i].p;
		a[i].num=i;
	}
	cin>>k;
	for(int i=1;i<=k;i++){
		cin>>r[i].lag;
		r[i].num=i;
	}
	sort(a+1,a+1+n,cmp1);
	sort(r+1,r+1+k,cmp2);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k;j++){
			if(!r[j].ask2&&r[j].lag>=a[i].c){
				//如果没有被占用而且能坐开人。 
				ans++;
				max_p+=a[i].p;
				a[i].ask=r[j].ask2=1;
				a[i].table=r[j].num;
				//注意标记。 
				break;
			}
		}
	}
	cout<<ans<<" "<<max_p<<"\n"; 
	for(int i=1;i<=n;i++){
		if(a[i].ask){
			//被容许吃饭。 
			cout<<a[i].num<<" "<<a[i].table<<"\n";
		}
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：feiji_code (赞：1)

# 题意：
这一道题目，先输入 $n$ 组人数和花的钱，再输入 $k$ 张桌子能坐多少人，让你求出老板如何安排能赚最多钱。很明显，用到贪心算法。（~~刚开始我看成 DP 了~~）

贪心的本质是局部最优解，所以只需要对 $a$ 和 $b$ 数组按照以下规则排序再枚举 $a_i$ 和 $b_i$ 找出满足桌子没占用且能坐下这个条件的元素可以了。
```
bool cmpa(node1 x,node1 y){
	if(x.p==y.p) return x.c<y.c;
	return x.p>y.p;
}
```
```
bool cmpb(node2 x,node2 y){
	return x.x<y.x;
}
```

这道题不算难，所以我先放代码，代码有注释，请放心观看。

## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node1{
	int c,p,id,num;//人数，钱，编号 
	int b=0;//是否同意申请 
}a[10000];
struct node2{//桌子 
	int x,num;//人数，编号 
	bool b=0;//是否有人 
}b[10000];
bool cmpa(node1 x,node1 y){
	if(x.p==y.p) return x.c<y.c;
	return x.p>y.p;
}
bool cmpb(node2 x,node2 y){
	return x.x<y.x;
}
int n,k,sum,ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){//输入 
		cin>>a[i].c>>a[i].p;
		a[i].id=i;
	} 
	cin>>k;
	for(int i=1;i<=k;i++){
		cin>>b[i].x;
		b[i].num=i;
	}
	sort(a+1,a+1+n,cmpa);
	sort(b+1,b+1+k,cmpb);
	for(int i=1;i<=n;i++){//贪心 
		for(int j=1;j<=k;j++){
			if(!b[j].b&&b[j].x>=a[i].c){//桌子没占用且能坐下 
				sum++;
				ans+=a[i].p;
				b[j].b=1;//打标记 
				a[i].b=1;//打标记 
				a[i].num = b[j].num;
				break;//判断下一组
			}
		}
	}
	cout<<sum<<" "<<ans<<endl;
	for(int i=1;i<=n;i++){
		if(a[i].b==1){
			cout<<a[i].id<<" "<<a[i].num<<endl;//输出 
		}
	}
 	return 0;
}

```


---

## 作者：lhs_chris (赞：0)

# 思路
贪心。按照订单金额从大到小排序，金额相同时按照人数从小到大排序。同时桌子按照人数从小到大排序，让订单匹配与其人数最相近的桌子。

# 代码

```cpp
#include<bits/stdc++.h>
#include<cstring>
#include<queue>
#include<set>
#include<stack>
#include<vector>
#include<map>
#define ll long long
#define lhs printf("\n");
using namespace std;
const int N=1e5+10;
const int M=2024;
const int inf=0x3f3f3f3f;
int n,m;
int v[N];
int sum,k;
struct nodea
{
	int x,y,ans=0;
	int id;
}a[N];
struct nodeb
{
	int x;
	int id;
}b[N];
bool cmp(nodea xx,nodea yy)
{
	if(xx.y==yy.y)return xx.x<yy.x;
	else return xx.y>yy.y;
}
bool cmp2(nodea xx,nodea yy)
{
	return xx.id<yy.id;
}
bool cmp1(nodeb xx,nodeb yy)
{
	return xx.x<yy.x;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i].id=i;
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&b[i].x);
		b[i].id=i;
	}
	sort(a+1,a+n+1,cmp);
	sort(b+1,b+m+1,cmp1); 
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(b[j].x>=a[i].x and !v[j])//匹配与其最接近的订单。找到就跳出循环
			{
				v[j]=1;//标记
				a[i].ans=b[j].id;
				k++;
				sum+=a[i].y;
				break;
			}
		}
	}
	sort(a+1,a+n+1,cmp2);
	printf("%d %d\n",k,sum);
	for(int i=1;i<=n;i++)
	{
		if(a[i].ans)//输出
		{
			printf("%d %d\n",a[i].id,a[i].ans);
		}
	}
	return 0;
}
```

---

## 作者：Rubedo_N (赞：0)

# 思路
先对数组进行排序：以金额 $p$ 为第一关键字，如果金额一样，则对人数 $c$ 排序。因为入座人数越多，利润越多，所以要将人数从小到大排序。将人数数组分配到桌子中够大的最小的桌子。如果可以分配，可用餐人群数 $+1$，利润加上 $p_i$，同时标记 $i$，使后来人群无法占用。  
最后遍历输出时，此桌若未被占用且坐得下，输出人群编号和桌子编号。
# AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
int num_table,num_p; 
struct node{int num,c,p,table;bool flag=0;}a[10005];
struct node2{int num,table_size;bool flag2=0;}r[10000];
bool cmp1(node x,node y){return x.p>y.p||(x.p==y.p&&x.c<y.c);}//按人数和钱数排序 
bool cmp2(node2 x,node2 y){return x.table_size<y.table_size;}//按桌子的大小排序 
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].c>>a[i].p;
		a[i].num=i;
	}
	cin>>k;
	for(int i=1;i<=k;i++){
		cin>>r[i].table_size;
		r[i].num=i;
	}
	sort(a+1,a+1+n,cmp1);
	sort(r+1,r+1+k,cmp2);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k;j++){
			if(!r[j].flag2&&r[j].table_size>=a[i].c){//此桌未被占用且坐得下。 
				num_table++;//多一桌 
				num_p+=a[i].p;//盈利数加上这群人钱数 
				a[i].flag=r[j].flag2=1;//已占用 
				a[i].table=r[j].num;//这群人用此桌 
				break;
			}
		}
	}
	cout<<num_table<<" "<<num_p<<endl; //输出可用餐人群数和最大利润 
	for(int i=1;i<=n;i++)if(a[i].flag)cout<<a[i].num<<" "<<a[i].table<<endl;//未被占用且坐得下，输出人群编号和桌子编号。
	return 0;
}
```

---

## 作者：Ag2WO4 (赞：0)

题意：桌对人一对一匹配，人数不得多于桌承受能力，求分配人最大收入。

考虑贪心。对于承受能力从小到大排序的桌子，每张桌子只需考虑自己能承受的人，从中取收入最大值。这不影响后面的选择。

本题解使用 Python 编写，通过附加赋予编号的形式对号入座。数据很水，可以偏暴力。本算法复杂度为平方。
```python
a=sorted([list(map(int,input().split()))+[i+1]for i in range(int(input()))])#输入人，编号，按人数排序方便后期人数对标承受能力。
input()#由于 Python 一行 split 无需预知数量，过行。
c=list(map(int,input().split()))#输入桌子。
d={i+1:[]for i in range(1000)}
for i in range(len(c)):
	d[c[i]].append(i+1)#一边编号一边统计各种承受能力的桌子数量。
f=[]
g=0#统计答案。
for i in d:
	for j in range(len(d[i])):
		e=[]
			for k in a:
				if k[0]>i:
					break
				else:
					e.append(k)#归拢可以承受的人。
			e.sort(key=lambda i:[-i[1],i[0]])#按收入排序。
			if e:
				a.remove(e[0])
				f.append([e[0][2],d[i].pop()])
				g+=e[0][1]#对号入座。
print(len(f),g)
for i in sorted(f):
	print(i[0],i[1])#输出答案。
```

---

## 作者：Ryder00 (赞：0)

题意清晰，不再阐述。

## 思路
由于一台桌子只能接收一家人，所以考虑贪心。按照消费金额贪心地从大到小排序，在 set 里查找满足这条询问的桌子即可。为什么这样是对的呢？如果两个预约，占用的人数相近，那么使用桌子的承受量级相近，都需要占用 $1$ 台桌子。但消费金额不同，那么显然选择消费金额更大的更优。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define db double
#define mkp make_pair
#define pb push_back
#define P pair<int,int>
#define _ 0
const int N=1e5+10,mod=1e9+7,MOD=1e9+123,inf=1e18;
int T=1,n,m,anss[N];
multiset<int> s,mp[N];
struct node{
    int c,p,id;
}a[N];
bool cmp(node x,node y){
    return x.p>y.p;
}
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].c>>a[i].p;
        a[i].id=i;
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        int x;
        cin>>x;
        s.insert(x);
        mp[x].insert(i);
    }
    sort(a+1,a+1+n,cmp);
    int ans=0,cnt=0;
    for(int i=1;i<=n;i++){
        int c=a[i].c,p=a[i].p,id=a[i].id;
        auto it=s.lower_bound(c);
        if(it!=s.end()&&*it<=*s.rbegin()){
            ans+=p,cnt++;
            anss[id]=*mp[*it].begin();
            mp[*it].erase(mp[*it].begin());
            s.erase(it);
        }
    }
    cout<<cnt<<" "<<ans<<endl;
    for(int i=1;i<=n;i++){
        if(anss[i]){
            cout<<i<<" "<<anss[i]<<endl;
        }
    }
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // ios::sync_with_stdio(false),cin.tie(0);
    while(T--){
        solve();
    }
    // cerr<<endl<<"Time: "<<1.0*clock()/CLOCKS_PER_SEC<<" s";
    return ~~(0^_^0);
}
```

---

## 作者：qzcbw (赞：0)

## 题目分析
很明显的贪心。

输入时将每一个数标号以方便输出。
将每个人的消费量与桌子的大小进行排序后，
枚举每一份预约的客户和每一张桌子。

判断该桌是否有人坐并且桌子是否能够使所有人坐下。
如果可以，那就标记该桌子已经有人坐了，并记录下当前客户的序号与桌子的序号，并累加餐厅最大盈利的估计值；
如果不行，那么就跳过循环。

最终输出答案。

## code
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
struct node1{
	int x,y,num;
}a[100039];
struct node2{
	int x,num;
}b[100039];
inline bool cmp1(node1 x,node1 y){return x.y>y.y;}
inline bool cmp2(node2 x,node2 y){return x.x<y.x;}
int n,m,ans,tot;
int flag[100039],ans1[100039],ans2[100039];
int main(){
//	freopen("booking.in","r",stdin);
//	freopen("booking.out","w",stdout);
	register int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i].num=i;	//标记
	}
	sort(a+1,a+n+1,cmp1);	//将每个人的消费量排序
	scanf("%d",&m);
	for(i=1;i<=m;i++){
		scanf("%d",&b[i].x);
		b[i].num=i;	//标记
	}
	sort(b+1,b+m+1,cmp2);	//将桌子的大小排序
	for(i=1;i<=n;i++)	//贪心
		for(j=1;j<=m;j++)
			if(!flag[j]/*判断该桌是否有人坐*/&&a[i].x<=b[j].x/*判断桌子是否能够使所有人坐下*/){
           			flag[j]=1;	//标记该桌已经有人坐了
				ans+=a[i].y;	//记录答案
				tot++;
				ans1[tot]=a[i].num;
				ans2[tot]=b[j].num;
				break;
			}
//	printf("%d",ans);
	printf("%d %d\n",tot,ans);	//输出答案
	for(i=1;i<=tot;i++)
		printf("%d %d\n",ans1[i],ans2[i]);
	return 0;
}
```

---

## 作者：流绪 (赞：0)

赚最多的钱!很明显的贪心,我们把价格从大到小排,相同的话人数少的在前面,桌子按从小到大排,然后暴力双重循环枚举每一组和桌子,能够符合的就记录下来

一些变量的解释和核心代码都有注释,应该很好理解!

下面是 AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int num,cnt,w;//第几组,人数,钱
	int id,v=0;//安排的桌子id,接不接受申请
}a[10000];
struct desk
{
	int num,p;//编号,桌子大小
	bool v=0;//有没有被选过
}b[10000];
bool cmp1(node a,node b)
{
	if(a.w == b.w)
		return a.cnt < b.cnt;
	return a.w > b.w;
}//按价格从大到小排,相同则人数少的优先
bool cmp2(desk a,desk b)
{
	return a.p < b.p;
}//桌子从小到大排
int main()
{
	int n;
	cin >>n;
	for(int i=1;i<=n;i++)
	{
		cin >> a[i].cnt >> a[i].w;
		a[i].num = i;
	}
	int k;
	cin >> k;
	for(int i=1;i<=k;i++)
	{
		cin >> b[i].p;
		b[i].num = i;
	}
	sort(a+1,a+1+n,cmp1);
	sort(b+1,b+1+k,cmp2);
	int ans = 0,sum=0;
	for(int i=1;i<=n;i++)
	{//暴力枚举每一组和每一个桌子
		for(int j=1;j<=k;j++)
		{
		//	cout << b[j].p << " " << a[i].cnt<<endl;
			if(!b[j].v && b[j].p >= a[i].cnt)
			{
				ans++;
				sum+=a[i].w;
				b[j].v = 1;//记录被选过
				a[i].v = 1;//记录接受申请
				a[i].id = b[j].num ;//记录id
				break;
			}
		}
	}
	cout << ans << " " <<sum <<endl; 
	for(int i=1;i<=n;i++)
		if(a[i].v)
			cout << a[i].num  << " " << a[i].id<<endl; 
}
```


---

