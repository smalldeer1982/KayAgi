# [POI 2012] LIT-Letters

## 题目描述

给出两个长度相同的的只含大写字母的字符串 $a, b$，每次可以交换 $a$ 中相邻两个字符，求最少的交换次数，使得 $a$ 交换后的得到的字符串与 $b$ 相同。

## 说明/提示

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n \leq 10^3$。
- 对于 $100\%$ 的数据，$1 \leq n \leq 10^6$，$a, b$ 中只含大写字母，且数据保证 $a$ 可以变成 $b$。

## 样例 #1

### 输入

```
3
ABC
BCA
```

### 输出

```
2```

# 题解

## 作者：姬小路秋子 (赞：28)

交换相邻两个数就决定了是求逆序对

对于A中的一个字符在B中的位置，我们可以发现同一个字符肯定是按从前往后的顺序出现在B中的。

比如A串ABABA，B串BAABA

我们肯定是把A中的第一个A放在B中的第一个A上，依次类推。

因为如果第一个A放在了后面，那么就有可能产生更对逆序对（因为你把大的数放在了前面）。由此得证。

好吧其实也挺显然的，我也是无聊才来水水题解的。

下面是代码（楼上那位ZJa队爷不放真是可惜了）

```cpp
#include<bits/stdc++.h>
using namespace std;
int c[26][1000001],n,a[1000001],d[26];
long long f[1000001];
int lowbit(int x){
	return x&(-x);
}
void insert(int x){
	int i;
	for(i=x;i<=n;i+=lowbit(i))f[i]++;
}
long long query(int x){
	int i;
	long long ans=0;
	for(i=x;i;i-=lowbit(i))ans+=f[i];
	return ans;
}
int main(){
	long long ans=0;
	int i;
	char s[1000001],s1[1000001];
	scanf("%d",&n);
	scanf("%s",s);
	scanf("%s",s1);
	for(i=0;i<n;i++)
		c[s[i]-'A'][++c[s[i]-'A'][0]]=i;
	for(i=0;i<n;i++){
		a[i+1]=c[s1[i]-'A'][++d[s1[i]-'A']]+1;
	}	
	for(i=1;i<=n;i++){
		//printf("%d\n",i);
		ans+=query(n)-query(a[i]-1);
		//printf("%d\n",i);
		insert(a[i]);
	}
	printf("%lld",ans);
}
```

---

## 作者：陈刀仔 (赞：10)

# 逆序对
有没有发现和NOIP2013火柴排队很像

[传送门](https://www.luogu.org/problem/P1966)

相似的

设第一个串为a，第二个串为b

我们可以找出a串中第x次出现的字符c1与其在b中第x次出现的相同的字符c2的位置，计入p数组

此时只需求出p数组的逆序对即可

为什么？

因为我们要通过交换使得a串对应的p数组与b串的p数组相同

但a串与a串自身处理出来的p数组就是{1,2,3,4,...,n}

所以交换的次数等同于求逆序对

```cpp
#include <bits/stdc++.h>
using namespace std;
string a,b;
int n;
long long ans;
int p[10000050];
vector<int>v[27];
int tp[27];
int c[10000050];
int lowbit(int x)
{
	return x&-x;
}
void add(int i)
{
	while(i<=n)
	{
		c[i]++;
		i+=lowbit(i);
	}
}
int sum(int i)
{
	int res=0;
	while(i)
	{
		res+=c[i];
		i-=lowbit(i);
	}
	return res;
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	cin>>a>>b;
	memset(tp,-1,sizeof(tp));
	for(int i=0;i<n;i++)
		v[b[i]-'A'+1].push_back(i+1);
	for(int i=0;i<n;i++)
	{
		p[i+1]=v[a[i]-'A'+1][++tp[a[i]-'A'+1]];
	}
	for(int i=1;i<=n;i++)
	{
		add(p[i]);
		ans+=sum(n)-sum(p[i]);
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：attack (赞：7)

补一发归并排序的

归并排序求逆序对的方式很简单

归并排序是将数列a[l,h]分成两半a[l,mid]和a[mid+1,h]分别进行归并排序，然后再将这两半合并起来。

在合并的过程中（设l<=i<=mid，mid+1<=j<=h），当a[i]<=a[j]时，并不产生逆序数；当a[i]>a[j]时，在

前半部分中比a[i]大的数都比a[j]大，将a[j]放在a[i]前面的话，逆序数要加上mid+1-i


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<deque>
#include<queue>
#define LL long long 
#define lb(x)    ((x)&(-x))
using namespace std;
const int MAXN=40000001;
inline int read()
{
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9')    {if(c=='-')    f=-1;c=getchar();}
    while(c>='0'&&c<='9')    x=x*10+c-48,c=getchar();return x*f;
}
int n;
queue<int>q[28];
int a[MAXN];
int tree[MAXN];
long long ans=0;
int tmp[MAXN];
void Sort(int l,int r)
{
    if(l==r)    return ;
    int mid=l+r>>1;
    Sort(l,mid);Sort(mid+1,r);
    int nowl=l,nowr=mid+1,nowpos=l;
    while(nowl<=mid&&nowr<=r)
    {
        if(a[nowl]<=a[nowr])    tmp[nowpos++]=a[nowl],nowl++;
        else tmp[nowpos++]=a[nowr],nowr++,ans=ans+mid-nowl+1;
    }
    while(nowl<=mid)    tmp[nowpos++]=a[nowl],nowl++;
    while(nowr<=r)        tmp[nowpos++]=a[nowr],nowr++;
    for(int i=l;i<=r;i++)    a[i]=tmp[i];
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        char c=getchar();
        q[c-'A'].push(i);
    }
    char c=getchar();// 可恶的换行符 
    for(int i=1;i<=n;i++)
    {
        char c=getchar();
        a[i]=q[c-'A'].front();
        q[c-'A'].pop();
    }
    Sort(1,n);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Drug__Lover (赞：4)

**树状数组求逆序对**

**先对B序列编号**

**根据B序列的编号给A序列编号**

**注意相同的情况**

**B序列中在前面的编号小**

**A序列中也是在前面的编号小（对于相同的字母来说）**

**用链表维护上面的编号**

**求逆序对就可以了**


    
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<map> 
#include<vector>
#define maxn 1001001
#define ll long long
using namespace std;
int n;
vector<int>G[100];
int vis[maxn];
string a,b;
int c[maxn];
struct node
{
    int cost,place;
}num[maxn];
ll ans;  
int add(int x,int k)
{
    for(int i=x;i<=n;i+=i&(-i)) c[i]+=k;
}
int query(int x)
{
    int sum=0;
    for(int i=x;i>0;i-=i&(-i)) sum+=c[i];
    return sum;
}
int cmp(node x,node y)
{
    return x.cost>y.cost;
}
int main()
{
    cin>>n;
    cin>>a;
    cin>>b;
    int len=a.size();
    for(int i=0;i<len;i++) G[(int)b[i]].push_back(i+1);  //给B编号 
    for(int i=0;i<len;i++)
    {
        num[i+1].cost=G[(int)a[i]][vis[(int)a[i]]];     //根据B给A编号 
        vis[(int)a[i]]++;
        num[i+1].place=i+1;
    }
    //裸求逆序对 
    sort(num+1,num+n+1,cmp);
    for(int i=1;i<=n;i++)
    {
        add(num[i].place,1);
        ans+=query(num[i].place-1);
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：abandentsky (赞：2)

本来想学点新东西，结果看了半天Splay，没搞懂。只能来水题了。结果还不会做这个题目。看了题解才发现很简单，原来就是给第一个字符串编号，然后把这个编号对应到第二个字符串上，最后求逆序对就好了。比如这样：
A  B   C 对应编号为1,2,3
B  C   A 对应编号为2,3,1。
完了就是对2,3,1求一遍逆序对就完了。很简单是吧！
```c
#include<stdio.h>
#include<iostream>
#include<algorithm>
#define MAXN  1000005
typedef  long long  LL;
using namespace std;

char s1[MAXN];
char s2[MAXN];
int n;
int tt[26][MAXN],d[26],a[MAXN];
LL c[MAXN];

//数组说明：tt[i][j]表示第i个字母（A是第一个，B是第二个，以此类推）；
//d[i]表示第i个字母出现了几次
//a[i]数组就是重新对s2字符串进行编号。

void init()
{
    for(int i=0;i<n;i++)
    {
        tt[s1[i]-'A'][++tt[s1[i]-'A'][0]]=i;         //其中tt[i][j],当j等于0时，是一个计数单元，用来记录i这个字母出现了几次
                                                                        //i这个字母第tt[s1[i]-'A'][0]次出现的位置是
    }
    for(int i=0;i<n;i++)
    {
        a[i+1]=tt[s2[i]-'A'][++d[s2[i]-'A']]+1;       //给s1从1到n编号，然后每个字母对应到s2上，给s2编号。
    }                                                                             //要注意把脚标从0开始改到从1开始。
}

int lowbit(int x)
{
    return (x&((-1)*x));
}

void add(int x,int d)
{
    while(x<=n)
    {
        c[x]+=d;
        x+=lowbit(x);
    }
}

LL sum(int x)
{
    LL ans=0;
    while(x>0)
    {
        ans+=c[x];
        x-=lowbit(x);
    }
    return ans;
}

int main()
{
    scanf("%d",&n);
    scanf("%s",s1);
    scanf("%s",s2);
    init();
    LL ans=0;
    for(int i=1;i<=n;i++)       //求逆序对
    {
        ans+=sum(n)-sum(a[i]);
        add(a[i],1);
    }
    printf("%lld\n",ans);
    return 0;
}

```


---

## 作者：__charlie520__ (赞：1)

相邻交换-逆序对。

可以类比题目：[P1966 火柴排队](/problem/P1966)(NOIP2013)

$a$ 和 $b$ 排序后，希望调整 $b$ 的顺序，让 $b$ 中第 $i$ 小的位置 $idx$ 与 $a$ 中第 $i$ 小的位置 $idx$ 相同。

也就是：$q[a[i].idx] = b[i].idx$。

求q的逆序对。

相同数字按照出现的id从小到大依次排序即可。

```
#include <bits/stdc++.h>
using namespace std;
int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while(c<'0' || c>'9'){if(c=='-')f=-1; c = getchar();}
	while(c>='0'&&c<='9'){x = x*10+c-'0'; c = getchar();}
	return x*f;
}
/*
参考1966火柴排队
3531 POI2012 letters
xa:  1   2   3   4
ra： 4   1   3   2
 a： 73  13  43  23
 b： 11  31  21  71
xb:  1   2    3   4

a':  13 23  43  73
xa:  2  4   3    1


 b'： 11  21  31  71
xb':  1   3   2   4

q[xa[i]] = xb[i]
q:    4   1   2   3

*/
typedef long long LL;
const LL MAXN = 1000005;
struct Node
{
	char val;
	LL idx;
	bool operator < (const Node &t) const
	{
		if(val==t.val) return idx<t.idx;
		return val<t.val;
	}
}a[MAXN],b[MAXN];
LL q[MAXN],c[MAXN];
int N;
int lowbit(LL x){return x&(-x);}
LL sum(LL x)
{
	LL res = 0;
	while(x>0)
	{
		res += c[x];
		x-= lowbit(x);
	}
	return res;
}
void add(LL x, LL d)
{
	while(x<=N)
	{
		c[x] += d;
		x += lowbit(x);
	}
}
char str[MAXN];
int main()
{
	N = read();
	scanf("%s",str);
	for(LL i = 1; i<=N; i++)
	{
		a[i].val = str[i-1];
	 	a[i].idx = i;
    }
    scanf("%s",str);
    for(LL i = 1; i<=N; i++)
    {
		b[i].val = str[i-1];
		b[i].idx = i;
	}
	sort(a+1,a+N+1); sort(b+1,b+N+1);
	for(LL i = 1; i<=N; i++) q[a[i].idx] = b[i].idx;
	LL ans = 0;
	for(LL i = N; i>=1; i--)
	{
		ans += sum(q[i]-1);
		add(q[i],1);
	}
	cout << ans <<endl;
	return 0;
}

```

---

## 作者：kczno1 (赞：1)

由于相同的不会交换，所以A,B最后的对应关系我们是知道的。

把A中的元素换成他在B中的位置，求一下逆序对就是答案了。

```cpp
#include<bits/stdc++.h>

#define ll long long
#define N 1000100
char a[N],b[N];
int t[26],next[N];
int n,c[N];

int qiu(int i)
{
    int x=0;
    for (;i;i-=i&-i) x+=c[i];
    return x;
}

void add(int i)
{
    for (;i<=n;i+=i&-i) ++c[i];
}

int main()
{
    freopen("1.in","r",stdin);
    int i,x;
    scanf("%d",&n);
    scanf("%s%s",a+1,b+1);
    for (i=n;i;--i) 
    {
        x=b[i]-'a';
        next[i]=t[x]; t[x]=i;
    }
    ll ans=0;
    for (i=1;i<=n;++i)
    {
        x=a[i]-'a';
        int dy=t[x];t[x]=next[dy];
        dy=n-dy+1;
        ans+=qiu(dy);add(dy);
    }
    printf("%lld",ans);
}
```

---

## 作者：睿屿青衫 (赞：0)

几个题解说的都很不清楚，为什么是逆序对问题困扰了我几个小时，最后发现确实不太好说，自己多手模几组数据，你会发现答案和逆序对惊人的一致。

读入的时候有换行符（写法不同的话，具体我也不知道影响不影响）

ans一定要用long long不然会50，得出奇怪的结果（如负数
在这里用树状数组实现，给各位一个思路

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 6000000
#define ll long long
using namespace std;
int n,c[maxn],pp[maxn],q[maxn],qq[maxn];
ll ans;
char cc;
struct node
{
    int p;
    int num;
}a[maxn],b[maxn];
int cmp(node aa,node bb)
{
    if(aa.p==bb.p) return aa.num<bb.num;
    return aa.p<bb.p;
}
int lowbit(int x)
{
    return x&-x;
}
void add(int x,int y)
{
    for(int i=x;i<=n;i+=lowbit(i))
     c[i]+=y;
}
int sum(int x)
{
    int ss=0;
    for(int i=x;i>0;i-=lowbit(i))
     ss+=c[i];
    return ss;
}
int main()
{
    scanf("%d",&n);
    getchar();
    for(int i=1;i<=n;i++)
     {
         cin>>cc;
         a[i].p=cc-'A'+1;
         a[i].num=i;
     }
    getchar();
    for(int i=1;i<=n;i++)
     {
         cin>>cc;
         b[i].p=cc-'A'+1;
         b[i].num=i;
     }
    sort(a+1,a+1+n,cmp);
    sort(b+1,b+1+n,cmp);
    for(int i=1;i<=n;i++)
     pp[a[i].num]=b[i].num;
    for(int i=n;i>=1;i--)
     {
         ans+=sum(pp[i]-1);
         add(pp[i],1);
     }
    printf("%lld",ans);
    return 0;
}
```

---

