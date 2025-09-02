# Merge Equals

## 题目描述

You are given an array of positive integers. While there are at least two equal elements, we will perform the following operation. We choose the smallest value $ x $ that occurs in the array $ 2 $ or more times. Take the first two occurrences of $ x $ in this array (the two leftmost occurrences). Remove the left of these two occurrences, and the right one is replaced by the sum of this two values (that is, $ 2 \cdot x $ ).

Determine how the array will look after described operations are performed.

For example, consider the given array looks like $ [3, 4, 1, 2, 2, 1, 1] $ . It will be changed in the following way: $ [3, 4, 1, 2, 2, 1, 1]~\rightarrow~[3, 4, 2, 2, 2, 1]~\rightarrow~[3, 4, 4, 2, 1]~\rightarrow~[3, 8, 2, 1] $ .

If the given array is look like $ [1, 1, 3, 1, 1] $ it will be changed in the following way: $ [1, 1, 3, 1, 1]~\rightarrow~[2, 3, 1, 1]~\rightarrow~[2, 3, 2]~\rightarrow~[3, 4] $ .

## 说明/提示

The first two examples were considered in the statement.

In the third example all integers in the given array are distinct, so it will not change.

## 样例 #1

### 输入

```
7
3 4 1 2 2 1 1
```

### 输出

```
4
3 8 2 1 
```

## 样例 #2

### 输入

```
5
1 1 3 1 1
```

### 输出

```
2
3 4 
```

## 样例 #3

### 输入

```
5
10 40 20 50 30
```

### 输出

```
5
10 40 20 50 30 
```

# 题解

## 作者：Bitter_Tea (赞：4)

基本做法就是**模拟**

我们只需要按照题目要求做就$AC$了呢，有没有很神奇$!$

我们用堆来实现我们的模拟:

即每次选出来两个数值最小的数，如果发现它们相等，那么就需要进行合并了。否则就说明第一个数必然是最后序列中的数了，我们保存它的位置。然后让第二个数作为第一个数尝试匹配$......$

我们重载运算符的时候以数值大小为第一关键字，以原始位置为第二关键字，都是从小到大的，只不过我们用堆的话是反着来的。

最后我们把我们记录的在最终序列的数按照位置排序，直接输出就可以了。

注:记得开$long \ long$

$Code$
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;
const int N=150005;
struct D{
	ll a;int id;
	bool operator < (const D&x) const	//堆重载运算符应该反着来 
	{
		if(a!=x.a) return a>x.a;
		return id>x.id;
	}
}e,fir,sec;
struct C{int id;ll a;}h[N];
bool cmp(const C&x,const C&y) {return x.id<y.id;}
priority_queue<D> q;
int n,tot;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&e.a);
		e.id=i;
		q.push(e);
	}
	while(q.size())
	{
		fir=q.top();q.pop();
		if(q.empty())	//特判最后一个数 
		{
			h[++tot].a=fir.a;
			h[tot].id=fir.id;
			break;
		}
		sec=q.top();
		if(fir.a==sec.a)
		{
			q.pop();
			e.a=fir.a+sec.a;
			e.id=sec.id;
			q.push(e);
		}
		else
		{
			h[++tot].a=fir.a;
			h[tot].id=fir.id;
		}
	}
	printf("%d\n",tot);
	sort(h+1,h+tot+1,cmp);
	for(int i=1;i<=tot;i++)
	printf("%lld ",h[i].a);
	return 0;
}
```

---

## 作者：chenxia25 (赞：2)

>### [洛谷题目页面传送门](https://www.luogu.org/problemnew/show/CF962D) & [CodeForces题目页面传送门](https://codeforces.com/contest/962/problem/D)

>题意见洛谷里的翻译。

## 这道题有$2$种方法。
---
### 方法$1$：
把所有数以数本身为第一关键字，下标为第二关键字压入堆，这样所有相同的数就可以挨在一起了。当堆里还有至少$1$个元素时，不断地从堆顶取两个元素，如果相等，就将它们弹出并且将它们相加的和再压入堆中，否则说明再也没有数能够与第一个取的数合并了（因为以后取的数会更大，没有更大的数的两倍会变小），便将它弹出并压入答案序列里。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//防爆int
struct cmp{//堆的比较方式
	bool operator()(pair<int,int> x,pair<int,int> y){
		if(x.first!=y.first)return x.first>y.first;//以数本身为第一关键字
		return x.second>y.second;//下标为第二关键字
	}
};
priority_queue<pair<int,int>,vector<pair<int,int> >,cmp> q;//堆
struct cmp0{//存储答案的堆的比较方式
	bool operator()(pair<int,int> x,pair<int,int> y){
		return x.second>y.second;//以下标比较，以便从左往右输出
	}
};
priority_queue<pair<int,int>,vector<pair<int,int> >,cmp0> q0;//存储答案
signed/*int已经被define成long long了，只能用signed*/ main(){
	int n/*数的个数*/,i;cin>>n;
	for(i=1;i<=n;i++){
		int x;cin>>x;
		q.push(make_pair(x,i)/*数是pair的第一元，下标是第二元*/);//压入堆
	}
	while(q.size()>1){//当堆还剩至少2个元素时
		int x1/*数1*/=q.top().first,y1/*下标1*/=q.top().second;q.pop();//第一个数无论如何都要弹出，就先弹出了
		int x2/*数2*/=q.top().first,y2/*下标2*/=q.top().second;
		if(x1==x2)/*相等？*/q.pop()/*弹出第二个数*/,q.push(make_pair(x1<<1,y2/*保留第二个数的位置*/));//压入和
		else q0.push(make_pair(x1,y1));//第一个数进答案序列
	}
	q0.push(q.top());//堆中剩下的那个孤独的数也是要进答案序列的
	cout<<q0.size()<<"\n";
	while(q0.size())cout<<q0.top().first<<" ",q0.pop();
	return 0;
}
```
---
### 方法$2$：

先把所有的数中的因数$2$全部除干净，然后将原来的$0\sim n-1$的访问顺序进行以除了因数$2$之后的数为第一关键字、原数为第二关键字、下标为第三关键字排序，这样相当于做了一次分类，将可能能合并的，即除了因数$2$之后的数相同的数放在了一起，每一类中又将相同的数放在了一起。接下来访问每一类（这里不需要考虑顺序不合题意的问题，因为类与类之间不会互相干涉）。对于每一类，又分几轮访问，每轮访问访问相同的数。在每轮中，第奇数次访问时，如果已经访问完了，就将它加入答案序列（因为再也没有数可以与它合并了）并退出这一轮；第偶数次访问时，将前一次访问的数与它合并（因为访问顺序的第三关键字是下标，所以第偶数次的下标一定是比前一次大的中最小的，符合题意），此时它已经变成了原来的$2$倍，然后让它在下一轮被访问到。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int a[150000]/*原数*/,b[150000]/*除了因数2后的数*/,ord[150000]/*访问顺序*/,las[150000]/*上一轮加入到这一轮的下标*/,now[150000]/*这一轮要访问的下标*/,will_be_las[150000]/*即将加到下一轮的下标*/;
ll ans[150000];//答案序列
bitset<150000> isans;//是否加入了答案序列（用bitset比bool数组省空间）
bool cmp(int i,int j){//访问顺序的排序方式
	if(b[i]!=b[j])return b[i]<b[j];//以除了因数2后的数为第一关键字，可以让同类数挨在一起
	if(a[i]!=a[j])return a[i]<a[j];//以原数为第二关键字，可以让相等的数挨在一起
	return i<j;//以下标为第三关键字
}
int main(){
	int n/*数的个数*/,i,t=0/*答案个数*/,nlas/*las的大小*/,nnow/*now的大小*/,nwill_be_las/*
	will_be_las的大小*/;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d",a+i);
		b[i]=a[i];while((b[i]&1)==0)b[i]>>=1;//除光因数2
		ord[i]=i;//访问顺序一开始是0~n-1
	}
	sort(ord,ord+n,cmp);//对访问顺序排序
	for(int l=0/*目前的类的区间左端点*/,r=0/*右端点*/;l<n;l=r/*下一类*/){//区间前闭后开
		while(r<n&&b[ord[r]]==b[ord[l]])r++;//算出右端点
		nlas=0;//清空las
		ll val=a[ord[l]];//此轮的所有数的值
		int at=l;//此类的访问进度
		while(nlas/*即使at到了r，也可能有上一轮的余留*/||at<r){
			nnow=nwill_be_las=0;//清空
			while(at<r&&a[ord[at]]==val)now[nnow++]=ord[at++];//整理此轮要访问的下标
			int atlas=0,atnow=0;//las、now的访问进度
			while(atlas<nlas||atnow<nnow){//当还有东西可访问时继续访问
				int x;
				if(atlas<nlas/*las还有*/&&(atnow==nnow||las[atlas]<now[atnow])/*now没了或las的更先访问*/)x=las[atlas++];//于是访问las的
				else x=now[atnow++];//否则访问now的
				if(atlas==nlas&&atnow==nnow)/*奇数次时访问完，剩下了*/{isans.set(x);ans[x]=val;t++;/*加入答案序列*/break;/*退出*/}
				if(atlas<nlas&&(atnow==nnow||las[atlas]<now[atnow]))x=las[atlas++];
				else x=now[atnow++];//同上
				will_be_las[nwill_be_las++]=x;//合并，给下一轮
			}
			nlas=nwill_be_las;for(i=0;i<nwill_be_las;i++)las[i]=will_be_las[i];//即将加到下一轮的该加到下一轮了
		    val<<=1;//增大一倍
		}
	}
	printf("%d\n",t);
	for(i=0;i<n;i++)if(isans[i])printf("%lld ",ans[i]);
	return 0;
}
```
---
$2$种方法的时间复杂度都是$\mathrm{O}(n\log_2n)$，不过方法$2$的常数小一点（因为它的中间部分是$\mathrm{O}(n)$的，只是除光因数$2$和排序要了一点$\mathrm{O}(n\log_2n)$的时间而已，而方法$1$从头到尾一直多次使用堆，~~很显然~~是彻彻底底的$\mathrm{O}(n\log_2n)$）。方法$2$最大的一个测试点只用了$93\mathrm{ms}$，然而方法$1$~~也只~~用了$452\mathrm{ms}$。

---

## 作者：ChenJr (赞：2)

	题意：给你一个大小为n的数组，如果在数组中有数存在过两次或以上，那么，取数组中出现过两次或以上的数中最小的数，按照位置顺序选出两个，将位置相对另一个数左的数删除，位置相对于另一个数右的数乘2，直到不能再进行操作位置。
    最后需要输出操作后的数组的大小和数组。
    
    这道题的题意比较绕，所以让我们根据样例来更直观的阐述一下题意。
    对于第一个样例7\n 3 4 1 2 2 1 1
    在数组中1和2均在数组中出现过两次或以上，那么我们优先取这两个数中的最小的数1进行操作。
    于是我们按照1所在数组中的位置先选出处于位置3和位置6的数，将位置3的数删除，将位置为6的数乘2，此时的数组变为3 4 2 2 2 1
    因为数组中2在数组中出现了两次，因此继续对2进行操作，按顺序取出处于如今位置3的2和处于如今为位置4的2，删除前一个，后一个乘2，因此此时的数组变为3 4 4 2 1。
    因为4仍然满足调节，故继续对4进行操作，则数组变为3 8 2 1，而在此时，数组中不再存在一个出现过两次或以上的数，因此停止操作，输出数组大小4和数组元素3 8 2 1
    
    解法：因为我们需要每一次都需要对数组中最小的数进行分析，首先想到的应该是sort排序，但在这题看来可能会比较繁琐。因此我们想到可以通过**优先队列**对数列中最值进行高效的维护。
    因此我们可以开一个由数值和位置组成的结构体，让优先队列同时维护数值和位置。（注意当数值相同时，需要返回位置靠前的数，否则将会使位置靠后的数值删除）
    不断的pop出队首的两个数（此处有一个小小的注意点，详见代码）假如两个数相同，则舍弃前一个数，并将后一个数的数值*2并重新压入优先队列；假如两个数不同，意味着前一个数的值已经最优，故存入用来记录答案的ans数组，然后继续将后一个数重新压入队列。不断进行操作，直到无法操作。
    最后因为ans数组中所保存的数是乱的，因此只需要再按照位置进行排序即可。
    （注意可能会爆int，得用long long）！！！
    
```cpp
#include <bits/stdc++.h>
#define maxn 150005
using namespace std;
typedef long long ll;
struct number{//第一个结构体用来输入的数
    ll a;//用来记录数值
    int id;//用来记录位置
    bool operator<(const number &b) const{//优先队列重载
        if(b.a==a){//如果数值相同，则返位置靠前的数
            return b.id<id;
        }
        return b.a<a;//否则返回数值小的
    }
}q[maxn];
struct num{//第二个结构体用来记录答案
    ll ans;//答案的值
    int id;//答案所在的位置
}p[maxn];
bool cmp(num a,num b){//用来使最后的答案按位置升序排序
    return a.id<b.id;
}
int main()
{
    int n;
    cin>>n;
    priority_queue<number> que;//建立一个储存number的优先队列
    for(int i=1;i<=n;i++){
        cin>>q[i].a;//输入数值
        q[i].id=i;//记录位置
        que.push(q[i]);//压入优先队列
    }
    int cnt=0;//答案的大小
    while(que.size()>1){//因为要保证一直可以取到两个数，因此需要满足队列大小大于1，最后再把最后的数pop出即可
        number tmpa=que.top();//取队首第一个数
        que.pop();
        number tmpb=que.top();//取队首第二个数
        que.pop();
        if(tmpa.a!=tmpb.a){//如果两个数不相同，则统计a的答案，重新压入b
            p[cnt].ans=tmpa.a;
            p[cnt++].id=tmpa.id;
            que.push(tmpb);
            continue;
        }
        else if(tmpa.a==tmpb.a){//如果两个数相同，则不对a操作，更新b的值，并将b重新压入优先队列
            tmpb.a=tmpb.a*2;
            que.push(tmpb);
        }
    }
    while(!que.empty()){//把最后队列中一个数再记录下来
        number xx=que.top();
        que.pop();
        p[cnt].ans=xx.a;
        p[cnt++].id=xx.id;
    }
    sort(p,p+cnt,cmp);//将答案重新根据位置升序排序
    cout<<cnt<<endl;//输出操作后数组的大小
    for(int i=0;i<cnt;i++){//输出
        if(i==0) cout<<p[i].ans;
        else cout<<" "<<p[i].ans;
    }
    return 0;
}

```
    

---

## 作者：Milmon (赞：1)

[in Blog](//milk-lemon.blog.luogu.org/solution-CF962D) & [Problem](//www.luogu.com.cn/problem/CF962D)

## 题目大意

- 给定正整数序列 $a_1,\ a_2,\ \cdots,\ a_n$。

- 要求每次从序列中找出最小的 $x$，且出现次数至少为 $2$，再找到最小的 $i<j$，使得 $a_i=a_j=x$，接着将 $a_i$ 从序列中删除，最后将 $a_j$ 修改为 $2x$。

- 如此操作直到这个序列无法继续操作，输出这个序列。

- $2\leq n\leq 1.5\times 10^5$，$1\leq a_i\leq 10^9$

## 解题思路

首先将整个序列中每个数的下标（也就是 $1\sim n$）放入优先队列中，而该优先队列按照下标对应的值从小到大排序。

每次从优先队列中取出两个下标 $i,\ j$，则 $a_i,\ a_j$ 必为此时序列中最小的两个数，下面分类讨论：

- 若 $a_i=a_j$，则直接进行合并，将原序列的 $a_j$ 值替换为 $2a_j$；

- 若 $a_i\not=a_j$，由于 $a_i,\ a_j$ 是此时序列中最小的两个数，故序列中仅存在一个 $a_i$，每次操作数只会变大，那么此数无法合并。只需把它弹出队列，把下标加入答案数组即可。

最后队列中只剩下一个数，直接加入答案数组即可。

输出时，只需按照下标从小到大排序，再输出对应的数值即可。

时间复杂度 $\Theta(n\log n)$。

## AC 代码

```
#include<bits/stdc++.h>
using namespace std;

int n; long long a[150001];

struct Cmp{
    bool operator()(int x,int y){
        if(a[x]!=a[y])return a[x]>a[y];
        else return x>y;
    }
};
priority_queue<int,vector<int>,Cmp> Q;
vector<int> answer;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
        scanf("%lld",a+i),Q.push(i);
	while(Q.size()>=2){
		int x=Q.top(); Q.pop();
        int y=Q.top(); Q.pop();
        if(a[x]==a[y])a[y]<<=1,Q.push(y); // 数值翻倍再放回优先队列
        else Q.push(y),answer.push_back(x); // 直接加入答案序列
	}
    if(!Q.empty())answer.push_back(Q.top());
	printf("%d\n",int(answer.size()));
    sort(answer.begin(),answer.end()); //对下标排序
    for(int i : answer)
        printf("%lld ",a[i]);
    printf("\n");
	return 0;
}
```

---

## 作者：issue_is_fw (赞：1)



$用map记录每个数值出现的上一次下标$

$在枚举到a_i时,看一下map以前有没有a_i这个值,没有就把下标存进去$

$有的话就取出以前的那个下标,抹掉,自己翻倍,然后重复这个过程$

**可能你会疑惑,这里不是按照从小到大消除的,是一旦出现就消除,为什么对了呢?**

$因为这两个相同的数在最左边,迟早要消掉,与顺序无关$

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int n,a[maxn],s;
map<int,int>m;
signed main()
{
	cin >> n;
	int s=n;
	for(int i=1;i<=n;i++)
	{
		cin >> a[i];
		if( m[ a[i] ] )
		{
			while( m[ a[i] ])
			{
				int index = m[ a[i] ];
				a[index]=0,s--,m[ a[i] ] =0;//清空
				a[i] = 2*a[i];
			}
			m[ a[i] ]=i;
		}	
		else	m[ a[i] ]=i;
	}
	cout<<s<<endl;
	for(int i=1;i<=n;i++)
		if( a[i] )	cout<<a[i]<<" ";
}
```

---

## 作者：永不复行 (赞：1)

  给你n个数，然后如果同一个数出现过两次或以上的话，就把这两个数求和，并且替换掉这两个数的右边那个数的位置，左边那个数就移除，找出最终序列的变化(每次都要选最左边的两个)
    比如[3,4,1,2,2,1,1]->[3,4,2,2,2,1]->[3,4,4,2,1]->[3,8,2,1]
    比如[1,1,3,1,1]->[2,3,1,1]->[2,3,2]->[3,4]
    明显map桶 ，搞不好爆了数组
    错误演示
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[200001],i,j,place[50000001],x,tot;
bool num[50000001];
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	for(i=1;i<=n;i++){
		if(a[i]==0) continue;
		if(num[a[i]]==1){
			x=a[i];
			a[i]*=2;
			a[place[x]]=0;
			num[x]=0;
			--i;
		}
		else{
			num[a[i]]=1;
			place[a[i]]=i;
		}
	}
	for(i=1;i<=n;i++){
		if(a[i]!=0) ++tot;
	}
	printf("%d\n",tot);
	for(i=1;i<=n;i++){
		if(a[i]!=0) printf("%d ",a[i]);
	}
}

```
如果stl就爽了
~~反解~~
```cpp
 _#include<bits/stdc++.h>
using namespace std;
long long a[220000],n,len;
std::map<long long,int> p;
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",a+i);
		while(p[a[i]]){
			a[p[a[i]]]=0;
			p[a[i]]=0;
			a[i]*=2;
			len++;
		}
		p[a[i]]=i;
	}
	printf("%lld\n",n-len);
	for(int i=1;i<=n;i++) if(a[i]) printf("%lld ",a[i]);
}_ 
```

---

## 作者：hexu2010 (赞：1)

# CF962D Merge Equals 题解

## 题目大意

给定正整数序列 $a[1\dots N]$ ，每次你需要找到序列中出现次数 $>=2$ 的最小值 $x$ ，找到 $x$ 的 $2$ 个最小下标 $(i,j)$ ，删除 $a_i$，将 $a_j$ 改为 $2x$ 。反复进行如此操作，直到不能操作位置，求序列最终的形态。

## 解析

根据题意，我们知道我们要找的数，要满足以下条件：

```cpp
(1) 出现次数>=2
(2) 尽可能的小
```

对于条件2，我们很容易的想到用小根堆维护，也就是优先队列。但是题目中还需要用到这个数的下标，所以很容易想到维护点对 $pair(x,pos)$ ，其中 $x$ 表示值， $pos$ 表示 $x$ 在原数组中的位置。

我们把样例中数据排个序，得到的结果是：

$[1,3],[1,6],[1,7],[2,4],[2,5],[3,1],[4,2]$。很明显，我们要合并开头的两个数。

从刚才的例子中可以发现，**我们每次取数，只需要处理开头的两个元素即可**。我们就对开头的两个元素进行分类讨论：（设开头的两个元素分别为 $[x_1,p_1]$ 和 $[x_2,p_2]$ ，且 $x_1\leqslant x_2$）

（1） $x_1=x_2$

这种情况很简单，我们把 $[2x_1,p_2]$ 放入队列中即可。

（2）$x_1\ne x_2$

由于 $x_1\leqslant x_2$ ，且 $x_1\ne x_2$ ，可得 $x_1<x_2$ 。又因为 $x_1$ 和 $x_2$ 是优先队列中最小的数，所以 $x_1$ **不会找到跟他相等的数**，所以直接把 $x_1$ 放入答案序列中即可， $x_2$ 则要重新放回队列。

最后，在答案序列中输出即可。这里可能会碰到一个问题：因为之前的优先队列是根据**元素值**进行排序的，也就是说，**数组下标**可能是无序的。但是输出答案序列的时候，我们要求数组下标是**有序**的。所以，我们还可以新开一个优先队列，并让**下表位置**作为第一关键字即可。

## 算法流程

![](https://cdn.luogu.com.cn/upload/image_hosting/trflxnys.png)

（本来是用 $mermaid$ 流程图的，结果洛谷识别不了，只能上传图片）
## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int s = 0, w = 1;
	char ch = getchar();
	for(; ch < '0' || ch > '9'; w *= (ch == '-') ? -1 : 1, ch = getchar());
	for(; ch >= '0' && ch <= '9'; s = 10 * s + ch - '0', ch = getchar());
	return s * w;
}
int n;
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > ans;
signed main(){
	n = read();
	for(int i = 0; i < n; i++){
		int tmp = read();
		pq.push(make_pair(tmp, i));
	}
	while(pq.size() > 1){
		pair<int, int> a, b;
		a = pq.top(), pq.pop();
		b = pq.top(), pq.pop();
//		printf("(%d,%d) (%d,%d)\n", a.first, a.second, b.first, b.second);
		if(a.first == b.first){
//			printf("push(%d, %d)\n", a.first * 2, b.second);
			pq.push(make_pair(a.first * 2, b.second));
		} else {
			pq.push(b);
			ans.push(make_pair(a.second, a.first));
		}
	}
	ans.push(make_pair(pq.top().second, pq.top().first));
	cout << ans.size() << endl;
	while(!ans.empty()){
		pair<int, int> now = ans.top();
		ans.pop();
		cout << now.second << " ";
	}
	return 0;
}
```



---

## 作者：yuheng_wang080904 (赞：0)

## 题意
给定正整数序列 $a_1,a_2...a_N$，每次你需要找到序列中出现次数大于等于 2 的最小值 $x$，找到 $x$ 的两个最小下标 ${i,j}$，删除 $a_i$ 并将 $a_j$ 改为 $2x$。

反复进行如此操作，求序列最终的形态。

## 解法

**模拟！**

我们可以用 $set$ 来维护存在的下标，用优先队列 $pq$ 来维护一个小根堆，初始化 $set={1,2,…,n},pq={(a_1,1),(a_2,2),…,(a_n,n)}$。

直接模拟操作过程：每次拿 $pq$ 中的前两个 $pair$，如果这两个 $pair$ 的第一个值相同，那么合并，把合并的结果放回 $pq$，注意放回时 $pair$ 的第二个值为拿出的第二个 $pair$ 的第二个值。并将第一个 $pair$ 的第二个值从 $set$ 里删除。如果这两个 $pair$ 的第一个值不同，那么说明第一个 $pair$ 中的第一个值应当是一个结果，并按照 $set$ 中的顺序存储在 $ans$ 数组。并把取出的第二个 $pair$ 放回去。最后结束时注意只剩一个 $pair$ 的情况，特判一下然后退出。

## 代码

下面放无注释代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pll pair<long long,long long>
int n;
long long a[150005],ans[150005],inf=2e18;
set<int>s;
priority_queue<pll,vector<pll>,greater<pll> >pq;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
	cin>>a[i];
	s.insert(i);
	pq.push(make_pair(a[i],i));
    }
    for(int i=1;i<=n;i++)ans[i]=inf;
    while(!pq.empty()){
       pll a=pq.top();
       pq.pop();
       if(pq.empty()){
           ans[a.second]=a.first;
           break;
       }
       pll b=pq.top();
       pq.pop();
       if(a.first!=b.first){
           pq.push(b);
           ans[a.second]=a.first;
           continue;
       }
       s.erase(a.second);
       pq.push(make_pair(b.first*2,b.second));
   }
   cout<<s.size()<<endl;
   for(int i=1;i<=n;i++){
       if(ans[i]!=inf)cout<<ans[i]<<" ";
   }
   cout<<endl;
   return 0;
}
```


---

## 作者：QianianXY (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF962D)
## 题目分析

优先队列基础题。

注意到 `最小值`，`最小下标`，对两个关键字排序，考虑 `pair` 实现的优先队列。

开两个优先队列，`que` 维护仍有可能被修改的元素，`ans` 维护已经不可能修改的元素。

初始时将所有元素存进 `que` 内，以数值本身为第一关键字排序。

当一个元素在原序列中没有其它与之相同的元素时，它不可能被删除或修改，直接弹出并存进 `ans`。

否则按题目要求模拟，弹出最小值 $x$ 的两个最小下标元素 $a_i,a_j$, 将 $a_j\times2$ 后重新存入 `que`。

当 `que` 大小不再改变时，终止操作，并将 `que` 中所有元素存入 `ans`，即为最终序列。

由于需要按顺序输出最终序列，所以 `ans` 以下标为第一关键字排序。

注意开 `long long`。

## code
```cpp
#include <bits/stdc++.h>
#define rei register ll
#define N 200010
using namespace std;
typedef long long ll;

template <typename T> inline void read(T &x)
{
	x = 0; T f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

ll n, lst, tot;
pair<ll, ll> que[N];
priority_queue<pair<ll, ll> > q, Q;

int main()
{
	read(n);
	for (rei i = 1; i <= n; i++)
	{
		ll x; read(x);
		q.push(make_pair(-x, -i));
	}
	while (q.size())
	{
		if (lst == q.size()) break; lst = q.size();
		ll x = q.top().first, y = q.top().second; q.pop();
		if (!tot || que[tot].first != x)
		{
			if (tot) Q.push(make_pair(que[tot].second, que[tot].first));
			tot = 1;
			que[tot] = make_pair(x, y);
		}
		else if (tot && que[tot].first == x)
		{
			q.push(make_pair(x * 2, y)); lst = 0;
			tot = 0;
		}
	}
	if (tot) Q.push(make_pair(que[tot].second, que[tot].first));
	while (q.size()) Q.push(make_pair(q.top().second, q.top().first)), q.pop();
	printf("%lld\n", Q.size());
	while (Q.size()) printf("%lld ", -Q.top().second), Q.pop();
	return 0;
}
```


---

## 作者：pengyule (赞：0)

在洛谷上提交一直都是 waiting 的状态，终于在 Codeforces 上 AC 了。

看到下面的题解都好像没有讲得太清楚，希望我的这篇题解能够让更多的人做对这题。

## 数据结构
优先队列，map。

## 题目大意
这道题还是比较难读的，所以写一下题目大意。

有一个数列。我们每次需要取出两个相同的数，需要保证这两个数是数列中所有出现次数不少于两次的数中，数值最小的。如果数列中有多个这个数，我们需要拿取这些数中最靠左的两个，并把他们的和放在这两个数中位置靠右的数的那个位置上，并把另外的一个数删除。为了方便，我们就不把它删除了，直接把这一位赋为 $0$ 就好了，因为数列中没有小于等于 $0$ 的数。

## 思路

我们知道，如果一个数出现了多次，我们可以取他其中的两个，如果这个数剩下来的还可以取，我们就可以继续取它。所以相当于就是说，如果数列中最小的出现了多次的数，他的个数为奇数次，那么我们就可以把这个数从左到右第二次、第四次、第六次……出现的数给变成这个数的两倍，把从左到右第一次、第三次……出现的数赋成 $0$ ，但是最后出现的那个数是不能赋成 $0$ 的，因为那个时候只剩他一个了，我们不能取他。如果我说的不好懂，请参看下图。

![image.png](https://i.loli.net/2020/05/30/9EfhbomS85GFzXp.png)

于是，出现次数为偶数次的也是差不多的（其实在代码中我们是不需要判断奇偶性的，请看下面的代码）。
```
while(!q.empty()){//优先队列q存储数列中出现的数的种类且不重复，时时更新，每次取出来的都是最小的数的值，优先队列book[temp]是从小到大存储数temp在数列中出现的位置下标
	ll temp=q.top();
	while(book[temp].size()>1){//当满足要求还可以取的时候
		a[book[temp].top()]=0;//靠左的书要删除
		book[temp].pop();
		if(book[temp*2].empty()) q.push(temp*2);//如果我们2x是数列中没有出现过的，那么数列中又出现了一个数的种类
		book[temp*2].push(book[temp].top());//自己理解一下，2x的位置就是靠右的一个数的位置
		a[book[temp].top()]=temp*2;//数列改变了
		book[temp].pop();
	}
	q.pop();//下一次我们再不会拿这个数了，因为现在这个数只在数列中出现0或1次了
}
```
以上是核心代码，注释详尽，大家可以参考。
## 完整代码
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
map <ll,priority_queue <ll,vector <ll>,greater <ll> > > book;
priority_queue <ll,vector <ll>,greater <ll> > q;
ll a[150010];
int main()
{
	int n,cnt=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(book[a[i]].empty()) q.push(a[i]);
		book[a[i]].push(i);
	}
	while(!q.empty()){
		ll temp=q.top();
		while(book[temp].size()>1){
			a[book[temp].top()]=0;
			book[temp].pop();
			if(book[temp*2].empty()) q.push(temp*2);
			book[temp*2].push(book[temp].top());
			a[book[temp].top()]=temp*2;
			book[temp].pop();
		}
		q.pop();
	}
	for(int i=1;i<=n;i++) if(a[i]!=0) cnt++;
	printf("%d\n",cnt);
	for(int i=1;i<=n;i++) if(a[i]!=0) printf("%lld ",a[i]);
}
```
完结。

---

