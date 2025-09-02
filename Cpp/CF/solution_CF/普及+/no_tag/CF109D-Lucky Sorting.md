# Lucky Sorting

## 题目描述

现在你有一个长度为$n$的数列,现在你要把他排成一个不递减的数列,想要交换两个数必须满足:其中至少有一个数是幸运数字.

这里对于幸运数字的定义是:只由$4$和$7$组成的数字,如:$47,744,4$,但是$5,17,467$就不是幸运数字.

如果不能达到要求,输出$-1$,否则输出任意一种交换方案,注意:你不需要最小化交换次数.

## 说明/提示

$n \le 10^5$

## 样例 #1

### 输入

```
2
4 7
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3
4 2 1
```

### 输出

```
1
1 3
```

## 样例 #3

### 输入

```
7
77 66 55 44 33 22 11
```

### 输出

```
7
1 7
7 2
2 6
6 7
3 4
5 3
4 5
```

# 题解

## 作者：wmrqwq (赞：1)

# 题目链接

[CF109D Lucky Sorting *2000 (*1800)](https://www.luogu.com.cn/problem/CF109D)

# 解题思路

我们考虑现将原序列离散化成排列，此时约束条件严格强于原题目，然后只找一个可以交换的数字，此时约束条件依然强于原题目。

那么此时我们考虑如何操作，设可以操作的数字为 $id$：

- 如果此时数字 $i$ 所在的位置为 $i$，那么此时不需要交换。

- 如果此时数字 $i$ 所在的位置不为 $i$，且数字 $id$ 所在的位置为 $i$，那么此时交换 $i,id$ 两个数字的位置。

- 如果此时数字 $i$ 所在的位置不为 $i$，且数字 $id$ 所在的位置不为 $i$，设位置 $i$ 此时的数字为 $id2$，那么此时先交换 $id,id2$ 两个数字的位置。那么此时交换 $id,i$ 两个数字的位置。

操作次数严格不大于 $2n$。

# 参考代码

```cpp
ll n,id;
ll a[1000010];
ll b[1000010];
map<ll,ll>mp,mp2;
ll pos[1000010];
bool f(ll x)
{
    ll pd=1;
    while(x)
        pd&=x%10==4 || x%10==7,
        x/=10;
    return pd;
}
vector<pii>ans;
void swp(ll x,ll y)
{
    if(x==y)
        return ;
    swap(a[x],a[y]);
    swap(pos[a[x]],pos[a[y]]);
    ans.pb({x,y});
}
void _clear(){}
void solve()
{
    _clear();
    cin>>n;
    forl(i,1,n)
        cin>>a[i],
        f(a[i])?id=i:id=id;
    forr(i,n,1)
        b[i]=a[i];
    sort(b+1,b+1+n);
    ll pd=1;
    forl(i,1,n)
        pd&=a[i]==b[i];
    if(pd)
    {
        cout<<0<<endl;
        return ;
    }
    ll k=1;
    forl(i,1,n)
        mp[a[i]]++;
    for(auto i:mp)
        mp2[i.x]=k,
        k+=i.y;
    forl(i,1,n)
        a[i]=mp2[a[i]]++;
    if(id==0)
    {
        cout<<-1<<endl;
        return ;
    }
//    forl(i,1,n)
//        cout<<a[i]<<' ';
//    cout<<endl;
    forl(i,1,n)
        pos[a[i]]=i;
    id=a[id];
    forl(i,1,n)
    {
        if(pos[i]==i)
            continue;
        if(pos[id]==i)
            swp(i,pos[i]);
        else
            swp(pos[id],i),
            swp(i,pos[i]);
    }
    cout<<ans.size()<<endl;
    for(auto i:ans)
        cout<<i.x<<' '<<i.y<<endl;
}
```

---

## 作者：_Felix (赞：1)

将这个序列变成最终序列。

```cpp
77 66 55 44 33 22 11
11 22 33 44 55 66 77
```

可以形成一些闭环。

```cpp
77-11
66-22
55-33
44
```

当我们要 `swap(i,j)` 但他们都不是幸运数时，我们使用一个中介数 $k$ 。

`swap(i,k)` 现在 $i$ 里装的是 $k$ 的灵魂。

`swap(i,j)` $i$ 里 $j$ 的灵魂， $j$ 里 $k$ 的灵魂。

`swap(j,k)` 最后换了回去。

我们先将你选择的作为整个过程的中介数的幸运数所在闭环给解决掉。（挨个换）

然后再把中介数和另一个闭环的头 `swap` 然后像处理幸运数所在闭环时一样处理，最后再换回来即可。

我的中介数选择的是最小的幸运数。代码可能有点细节。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,tot,vis[N],bg[N],b[N],ok[N];
vector<pair<int,int> >ans;
struct node{
    int id,val,fl,mb;
}a[N<<1];
bool check(int x){
    while(x>0){
        if(x%10!=4&&x%10!=7) return 0;
        x/=10;
    }
    return 1;
}
bool cmp(int x,int y){
    return a[x].val<a[y].val;
}
void print(int x,int y){
    if(x>y) swap(x,y);
    if(x!=y) ans.push_back(make_pair(x,y));
}
void work(int x){
    bg[++tot]=x;
   // cout<<x;
    int nw=a[x].mb; vis[nw]=tot;
    while(nw!=x){
  //      cout<<"-"<<nw;
        nw=a[nw].mb; vis[nw]=tot;
    }
   // cout<<endl;
    return;
}
void solve(int bh,int k){
    //a[k] 与头交换
    ok[bh]=1;
   // cout<<"*"<<bh<<" "<<bg[bh]<<endl;
    print(k,bg[bh]);
    int i=bg[bh];
    while(a[i].mb!=bg[bh]){
        //cout<<"i: "<<i<<" "<<a[i].mb<<endl;
        print(i,a[i].mb);
        i=a[i].mb;
    }
    print(k,i);
}
int main(){
    scanf("%d",&n);
    bool flg=1; int k=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i].val);
        a[i].id=i; b[i]=i;
        if(check(a[i].val)) {
            a[i].fl=1;
            if(a[i].val<a[k].val||k==0) k=a[i].id;
        }
        if(i>1&&a[i-1].val>a[i].val) flg=0;
    }
    if(flg){ puts("0"); return 0; }
    if(k==0) { puts("-1"); return 0; }
    sort(b+1,b+n+1,cmp);
    for(int i=1;i<=n;i++) a[i].mb=b[i];//,cout<<"*"<<b[i]<<" "<<i<<endl;
    for(int i=1;i<=n;i++)
        if(!vis[i]) work(i);

    ok[vis[k]]=1;
    //操作数所在环，先用操作数搞好。
  //  cout<<a[k].val<<" "<<"***"<<endl;
    int i=k;
    while(a[i].mb!=k){
       // cout<<i<<endl;
        print(i,a[i].mb);
        i=a[i].mb;
    }
    k=i; //操作数来到目标位置

 //   cout<<"***"<<ans.size()<<endl;
    //其他环
    for(int i=1;i<=tot;i++)
        if(!ok[i]) solve(i,k);
    cout<<ans.size()<<endl;
    for(int i=0;i<ans.size();i++)
        printf("%d %d\n",ans[i].first,ans[i].second);
    return 0;
}
```

~~（趁估值掉完之前水一发cf题解）~~

---

## 作者：木木！ (赞：0)

如果这一题要求步数最小，会更好做一点？

如果要求步数最小的话，使 $n$ 个数排完序且交换次数最小的排序方法是 [Circle Sorting](https://bbs.csdn.net/topics/200027652)。

在 Circle Sorting 的基础上加上交换限制很简单：对于每一个环，如果其中有幸运数，直接从幸运数开始做就好了；否则将一个幸运数换到环里，排完再换回来即可。

先输出次数再输出方案有点难搞，因为本题输出长度是 $\Theta(n\log n)$，数组能开下，因此以下代码使用了缓存，先将交换信息输出到缓存再输出到标准输出。

附 AC 代码：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int islucky(int x)
{
	if(!x) return false;
	for(; x; x/=10)
	{
		if((x%10)!=4 && (x%10)!=7) return false;
	}
	return true;
}

int ai[100005];
int st[100005];

bool cmp(int a,int b) { return ai[a] < ai[b]; }

void calcst(int n)
{
	for(int i=1; i<=n; ++i)
	{
		st[i] = i;
	}
	
	sort(st+1,st+1+n,cmp);
}

int vis[100005];
char buf[10000005],*buftop=buf;

int solveselfcircle(int pos,int& k)
{
	int j = pos;
	for(; st[j]!=pos; j=st[j])
	{
		++k;
		buftop += sprintf(buftop,"%d %d\n",j,st[j]);
		vis[j] = 1;
	}
	vis[j] = 1;
	return j;
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
	{
		scanf("%d",ai+i);
	}

	int tli = 0;
	for(int i=1; i<=n; ++i)
	{
		if(islucky(ai[i]))
		{
			tli = i;
			break;
		}
	}

	if(!tli)
	{
		for(int i=1; i<n; ++i)
		{
			if(ai[i] > ai[i+1])
			{
				printf("-1\n");
				return 0;
			}
		}
		printf("0\n");
		return 0;
	}

	calcst(n);

	int k = 0;
	tli = solveselfcircle(tli,k);

	for(int i=1; i<=n; ++i)
	{
		if(!vis[i] && i!=st[i])
		{
			++k;
			buftop += sprintf(buftop,"%d %d\n",i,tli);

			int j = i;
			for(; st[j]!=i; j=st[j])
			{
				++k;
				buftop += sprintf(buftop,"%d %d\n",j,st[j]);
				vis[j] = 1;
			}
			vis[j] = 1;

			++k;
			buftop += sprintf(buftop,"%d %d\n",j,tli);
		}
	}

	printf("%d\n%s",k,buf);
}
```

---

