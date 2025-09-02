# Queue

## 题目描述

In the Main Berland Bank $ n $ people stand in a queue at the cashier, everyone knows his/her height $ h_{i} $ , and the heights of the other people in the queue. Each of them keeps in mind number $ a_{i} $ — how many people who are taller than him/her and stand in queue in front of him.

After a while the cashier has a lunch break and the people in the queue seat on the chairs in the waiting room in a random order.

When the lunch break was over, it turned out that nobody can remember the exact order of the people in the queue, but everyone remembers his number $ a_{i} $ .

Your task is to restore the order in which the people stood in the queue if it is possible. There may be several acceptable orders, but you need to find any of them. Also, you need to print a possible set of numbers $ h_{i} $ — the heights of people in the queue, so that the numbers $ a_{i} $ are correct.

## 样例 #1

### 输入

```
4
a 0
b 2
c 0
d 0
```

### 输出

```
a 150
c 170
d 180
b 160
```

## 样例 #2

### 输入

```
4
vasya 0
petya 1
manya 3
dunay 3
```

### 输出

```
-1
```

# 题解

## 作者：莫奈的崖径 (赞：7)

qwq这道题我开始感觉不可做，然后右边dalao告诉我其实很简单，让我不要丧失信心，我就想到了，这个经验告诉我们，
~~蹭dalao仙气是很重要的！~~


------------
## 题意
n个人排队，我们不知道队列的顺序，但知道每个人前面有多少人比他高，现在要求我们求出队伍可能的一种序列，并且随机输出他们可能的身高。


------------
## 分析
一开始的我还是很雾的，以为要用单调队列来做，仔细思考后，发现其实是一道很有趣的思维题，这里我们用样例1举例。

建立一个结构体a,其中一个字符串s存储人名，num存储比他高的人。然后对结构体进行排序，具体compare函数如下：

```cpp
bool cmp(node a,node b)
{
	return a.num<b.num;
}
```
![](https://i.loli.net/2019/08/27/W5S2rD9JHBzpLnm.png)



第i个人前面有a[i].num个人比他高，那他前面就有i-1-a[i].num个人比他矮，我们可以在结构体里定义一个ans（作为最后的输出）用来存储比他矮的人，当然这里还是不要-1，因为可能会输出0，而身高范围是1~1e9，具体请往下看。


![](https://i.loli.net/2019/08/27/Gaiv3qB5KrFTSsg.png)

根据图片不难发现，若只看序列中a，c，d三项，结合题目看是合法的，但如果加上b就出了问题，本来应该有2个人比他高，但这样一来就只有一个人比他高了，这可怎么办呢？于是有了：
```cpp
	a[i].ans=i-a[i].num;
	for(int j=1;j<i;j++)
	{
		if(a[j].ans>=a[i].ans) a[j].ans++;
	}
```

这样一操作，就变成了：

![](https://i.loli.net/2019/08/27/OJzhyBDAufFGKex.png)

仔细观察，此操作不仅没有改变前三项的合法性，还让第四项变得合法，这样一来，我们就得到了这道题的合法序列，输出ans就可以了。

但如果我们找不到这样的一个合法序列该怎么判断呢？

如果一个人本身的序号i<=a[i].num的话，那么肯定无法形成合法的序列，直接输出-1再返回0。qwq这么简单就不用证明了吧。



------------
## AC代码
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 3005
using namespace std;
int n;
struct node
{
	char s[20];
	int num,ans;
}a[N];
bool cmp(node a,node b)
{
	return a.num<b.num;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%s %d",a[i].s,&a[i].num);
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		if(a[i].num>=i)
		{
			printf("-1\n");
			return 0;
		}
		a[i].ans=i-a[i].num;
		for(int j=1;j<i;j++)
		{
			if(a[j].ans>=a[i].ans) a[j].ans++;
		}
	}
	for(int i=1;i<=n;i++)
	printf("%s %d\n",a[i].s,a[i].ans);
	return 0;
}

```
不足之处请评论指正蒟蒻qwq


---

## 作者：__phiu (赞：4)

## Pro
给定一个序列，要求找到一种排列 $a$，可以赋值后得到数组 $p$，有 $\sum_{j=1} ^ {i-1} p_j>p_i=a_i $。

## Sol

首先把原数组排序，让 $a_i$ 大的在后面，这样更容易让比自己大的在前面。

无解：当一个人前面高的人比编号大的时候显然无解，因为他前面的人不够，如果与后面调换，后面的数到这个位置也一定不够。

然后从后往前做，因为后面不影响前面，每一位从 $n-a_i$ 开始往前循环，如果找到没有用过的数就赋给这一位。

正确性：把 $n-a_i+1$ 到 $n$ 这 $a_i$ 个数留给了前面，而用过的数虽然比当前值大，但是放在了后边，所以不影响这一位的答案。

## Code
```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define For(i,a,b,c) for(int i=a;i<=b;i+=c)
#define Rof(i,a,b,c) for(int i=a;i>=b;i-=c)
#define pb push_back
#define pii pair<int,int>
using namespace std;
const int mod=998244353;
const int N=2e6+50;
inline int read(){
	char c=getchar();
	int x=0,f=1;
	while(c<'0' or c>'9'){
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0' and c<='9')
		x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
int n;
struct person{
	string name;
	int ans;
	int num; 
	bool operator < (const person &a ){
		return num<a.num;
	}
}p[N];
bool vis[N];
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		cin>>p[i].name>>p[i].num;
	}
	sort(p+1,p+n+1);
	for(int i=n;i;i--){
		if(p[i].num>=i){
			puts("-1");
			return 0;
		}
		for(int j=n-p[i].num;j;j--){
			if(!vis[j]){
				vis[j]=1;
				p[i].ans=j;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++){
		cout<<p[i].name<<' '<<p[i].ans<<endl;
	}
	return 0;
}
```


---

## 作者：华容 (赞：3)

这道题是在比赛的时候做的，看到别人ac了就特别慌，于是打了个暴力，结果过了。。
------------
通过读题我们可以发现身高的范围其实可以缩小在【1，n】，
于是题目变为 

### **将1~n的数分配给n个人，每个人的身高满足前a个人比他高**
1. 首先我们要排序，把a比较大的放后面，这样可以保证结果尽可能的有解。
1. 然后我们从第n个人开始给他的身高赋值，因为后面无论怎么赋值都不会影响前面。
1. 从a~1开始赋值，因为前面有a个人比他高，所以要将a+1~n的值留给前面的人。 

**上代码**


------------

```c
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct qwer{
	char id[20];
	int a;
	int an;
}r[3005]; //用结构体来储存 
int s[3005];//用来标记这个数是否被使用过 被使用过了将值赋为 1 
bool cmp(qwer x,qwer y)//一个按照a的值从小到大排的函数 
{
	return x.a<y.a;
}
int main()
{
	int i,j,n;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%s%d",r[i].id,&r[i].a);
	}
	sort(r+1,r+1+n,cmp);//排序 
	for(i=n;i>=1;i--)
	{
		if(r[i].a>=i)//当i前面的比他高的人数大于等于i，可以发现这种情况是没有解的 ； 
		{
			printf("-1");
			return 0;
		}
		for(j=n-r[i].a;j>=1;j--)//从n-r[i].a开始找，找到第一个没有被使用的，将他的值赋给i ； 
		{
			if(s[j]==0)//找到了就结束循环，寻找下一个； 
			{
				r[i].an=j;
				s[j]=1;
				break;
			}
		}
	}
	for(i=1;i<=n;i++)
	{
		printf("%s %d\n",r[i].id,r[i].an);
	}
}

```
------------
~~第一篇题解完成（撒花） ~~不懂可以私信我


---

## 作者：shinkuu (赞：1)

其实这题数据开到 $n=10^6$ 都是可做的呢。

首先想到，把 $a_i$ 大的放后面，是更有可能构造出来的。所以先排一遍序。

然后就转化成了一个很典的问题：每次往一个序列中的第 $a_i$ 个数后面插入一个数。考虑从后往前做，先将每个位置值设成 $1$，每次找到前缀和为 $a_i+1$ 的位置 $j$，第 $i$ 个人高度即为 $n+1-j$，并将这个位置的值设为 $0$。可以线段树二分维护。

总时间复杂度为 $O(n\log n)$。

code：

```cpp
int n,m,ans[N];
struct node{
	int val,id;
}e[N];
string s[N];

int tr[N<<2];
inline void pushup(int o){
	tr[o]=tr[o<<1]+tr[o<<1|1];
}
void build(int l,int r,int o){
	if(l==r){
		tr[o]=1;
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,o<<1);
	build(mid+1,r,o<<1|1);
	pushup(o);
}
int update(int l,int r,int o,int x){
	if(l==r){
		tr[o]=0;
		return l;
	}
	int mid=(l+r)>>1,vl;
	if(tr[o<<1]<x){
		vl=update(mid+1,r,o<<1|1,x-tr[o<<1]);
	}else{
		vl=update(l,mid,o<<1,x);
	}
	pushup(o);
	return vl;
}

inline bool cmp(node x,node y){
	return x.val<y.val;
}
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>s[i];
		scanf("%d",&e[i].val);
		e[i].id=i;
	}
	sort(e+1,e+n+1,cmp);
	build(1,n,1);
	for(int i=n;i>=1;i--){
		if(tr[1]<=e[i].val){
			puts("-1");
			return;
		}
		ans[i]=update(1,n,1,e[i].val+1);
	}
	for(int i=1;i<=n;i++){
		cout<<s[e[i].id]<<" ";
		printf("%d\n",n+1-ans[i]);
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)solve();
}
```

---

## 作者：XL4453 (赞：0)

### 题目分析：

考虑直接构造这样的一组序列。

首先将每一个人按照站在前面比自己高的人的数目从小到大排序，这样要求的人数多的就放在后面。可以发现，如果这样排序还是不能得到答案的话那么一定就不存在一组解了，否则一定存在。

然后发现由于人的身高不能是负的，所以用比自己高的人的数目并不好处理，考虑将其转化为比自己矮的人的数目做，也就是将所有的 $a_i$ 转化为 $i-a_i-1$，这里将这样的一个值记作 $b_i$。

对于每一个新考虑的数，不妨直接将其高度设置为 $b_i$，然后将所有的大于或等于 $b_i$ 的数都要为这个新来的 $b_i$ 腾一个位置出来，也就是加一。

值得注意的是，在这种做法下，是有零的存在的，最后输出时需要加一。

----------

如果不进行这一步转化也是可以做的，本质上和上面的哪一种做法是一样的，不过可能更难理解一点。

也就是，对于每一个新加入的数，考虑将其高度直接设置为 $10^9-a_i$ 然后所有的小于或等于 $10^9-a_i$ 的高度都需要减一为其腾出位置。

---------
### 代码（后一种思路）：

```cpp
#include<cstdio>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
struct node{
	string s;
	int a,f;
	bool operator < (node x)const{
		return a<x.a;
	}
}x[3005];
int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	cin>>x[i].s>>x[i].a;
	sort(x+1,x+n+1);
	for(int i=1;i<=n;i++){
		if(x[i].a>=i){
			printf("-1\n");
			return 0;
		}
	}
	for(int i=1;i<=n;i++){
		x[i].f=1e9-x[i].a;
		for(int j=1;j<i;j++)
		if(x[j].f<=x[i].f)x[j].f--;
	}
	for(int i=1;i<=n;i++)
	cout<<x[i].s<<" "<<x[i].f<<endl;;
	return 0;
}
```


---

