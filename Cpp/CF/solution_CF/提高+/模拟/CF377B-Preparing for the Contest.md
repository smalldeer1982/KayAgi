# Preparing for the Contest

## 题目描述

Soon there will be held the world's largest programming contest, but the testing system still has $ m $ bugs. The contest organizer, a well-known university, has no choice but to attract university students to fix all the bugs. The university has $ n $ students able to perform such work. The students realize that they are the only hope of the organizers, so they don't want to work for free: the $ i $ -th student wants to get $ c_{i} $ 'passes' in his subjects (regardless of the volume of his work).

Bugs, like students, are not the same: every bug is characterized by complexity $ a_{j} $ , and every student has the level of his abilities $ b_{i} $ . Student $ i $ can fix a bug $ j $ only if the level of his abilities is not less than the complexity of the bug: $ b_{i}>=a_{j} $ , and he does it in one day. Otherwise, the bug will have to be fixed by another student. Of course, no student can work on a few bugs in one day. All bugs are not dependent on each other, so they can be corrected in any order, and different students can work simultaneously.

The university wants to fix all the bugs as quickly as possible, but giving the students the total of not more than $ s $ passes. Determine which students to use for that and come up with the schedule of work saying which student should fix which bug.

## 说明/提示

Consider the first sample.

The third student (with level 3) must fix the 2nd and 4th bugs (complexities 3 and 2 correspondingly) and the second student (with level 1) must fix the 1st and 3rd bugs (their complexity also equals 1). Fixing each bug takes one day for each student, so it takes 2 days to fix all bugs (the students can work in parallel).

The second student wants 3 passes for his assistance, the third student wants 6 passes. It meets the university's capabilities as it is ready to give at most 9 passes.

## 样例 #1

### 输入

```
3 4 9
1 3 1 2
2 1 3
4 3 6
```

### 输出

```
YES
2 3 2 3
```

## 样例 #2

### 输入

```
3 4 10
2 3 1 2
2 1 3
4 3 6
```

### 输出

```
YES
1 3 1 3
```

## 样例 #3

### 输入

```
3 4 9
2 3 1 2
2 1 3
4 3 6
```

### 输出

```
YES
3 3 2 3
```

## 样例 #4

### 输入

```
3 4 5
1 3 1 2
2 1 3
5 3 6
```

### 输出

```
NO
```

# 题解

## 作者：万弘 (赞：5)

本人太菜，只会2log的做法。

首先这题的单调性是显然的：对于一种选法，若$x$天内能完成，那么$x+1$天内也能完成。

于是考虑二分答案。假设现在在判断$k$天内能否完成。   

$k$天内能完成$\rightarrow$每个被选的学生至多修$k$个bug。    
（在二分前）将bug按$a$（复杂度）排序，学生按$b$（实力）排序。  
按复杂度从大到小考虑bug $i$：能修复这个bug的学生集合，就是$b_j\ge a_i$的$j$（且$j$修复的bug不足$k$个）.排序之后这是很好维护的。  
如果某个bug的可选集合为空，那么显然不行。  
考虑贪心，从可选集合中选$c_j$最小（或者已经选了但用了不足$k$次）的来修复他。这可以用一个以$c_j$为关键字的小根堆维护。同时我们不需要记录次数，再贪心一下，让$c_j$最小的$j$把$[i-k+1,i]$都修掉。这样check的时间是$\mathcal O(m\log n)$的。

总时间复杂度是$\mathcal O(m\log m\log n)$的。如果大佬有低于2log的做法，欢迎前来吊打我。
```cpp
/**********/
#define MAXN 100011
struct one
{
	ll b,c,dex;
	bool operator <(const one& t)
	const
	{
		return c>t.c;
	}
}p[MAXN];
pll a[MAXN];
ll f[MAXN],n,m,s;
bool check(ll k)
{
    std::priority_queue<one>q,emp;
    ll sum=0,it=n;
    for(ll i=m;i>0;--i)
    {
		while(it&&p[it].b>=a[i].first)q.push(p[it--]);
		if(q.empty())return 0;
		sum+=q.top().c;
		for(ll j=i;j>max(i-k,0);--j)f[a[j].second]=q.top().dex;
		q.pop();
		i-=k-1;
    }
	return sum<=s;
}
bool cmp(one a,one b)
{
	return a.b<b.b;
}
int main()
{
    n=read(),m=read(),s=read();
    for(ll i=1;i<=m;++i)a[i]=pll(read(),i);
    for(ll i=1;i<=n;++i)p[i].b=read();
    for(ll i=1;i<=n;++i)p[i].c=read(),p[i].dex=i;
    std::sort(a+1,a+m+1),std::sort(p+1,p+n+1,cmp);
    un l=0,r=m+1,mid;
    while(l<r)
    {
        mid=(l+r)>>1;
        if(check(mid))r=mid;
		else l=mid+1;
    }
	if(r==m+1)puts("NO");
	else
	{
		puts("YES");
		check(l);
		for(ll i=1;i<=m;++i)printf("%lld ",f[i]);
	}
	return 0;
}
```

---

## 作者：Bbaka (赞：1)

### 题意

有 $n$ 个人，$m$ 个问题，第 $i$ 个问题有一个难度值 $a_i$ ，第 $i$ 个人有一个能力值 $b_i$ 和聘请费用 $c_i$，一个人只能解决难度值不超过自己能力值的问题，一个人一天只能解决一题，但是同一天可以有多个人解题，问满足聘请费用和不超过给定的 $s$ 的情况下最小需要时间。

### 思路

由题意可知，我们相当于要把问题划分为若干集合，在满足条件下使得集合大小的最大值尽量小，同时易得当集合大小最大值变大时，一个人可能可以分配到更多的任务，即所需要的价钱会变小，而相反最大值变小时所需要的价钱会增加，即满足单调性，故考虑使用二分答案。

已经我们可以先将问题按难度升序排序，人按能力值升序排序，然后二分集合的最大值，二分中依次遍历所有的问题，对于一个问题如果所有符合条件的人都没被分配到任何问题，那么我们肯定要把当前问题分配给最便宜的人，而当我们给一个人分配到问题后，因为钱已经花出去了，我们之后肯定优先让他继续做题，直到他能被分配的题数量满了或者难度超过他能力值了。

因为要找最便宜的，我们可以用个堆来维护，每次从后往前遍历数组，把能力值大于当前难度的人都丢入堆中，然后把当前问题分配给堆顶的人，最后判断当前花费和 $s$ 的大小来调整二分边界即可。

二分的 ``check`` 函数复杂度是 $\mathcal{O}(m\log{n})$，故总的复杂度是 $\mathcal{O}(m\log{m}\log{n})$。
### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+9;
int n,m;
long long s;
int Ans[N],tmp[N],num[N];
struct Quest {
    int id;
    long long val;
    bool operator <( const Quest &x) const {
        return val<x.val;
    }
}a[N];
struct Student {
    int id;
    int num;
    long long val;
    long long cost;
    bool operator <( const Student &x) const {
        if (x.num==num) return cost>x.cost;
        else return num<x.num;
    }
}b[N];
bool cmp (Student x,Student y) {
    return x.val==y.val?x.cost<y.cost:x.val<y.val;
}
bool check (int x) {
    priority_queue<Student> q;
    for (int i=1;i<=n;++i) {
        b[i].num=0;
    }
    long long res=0;
    for (int i=m,j=n;i;i-=1) {
        while (b[j].val>=a[i].val&&j) {
            q.push (b[j]);
            j-=1;
        }
        while ((!q.empty ())&&q.top ().num>=x) {
            q.pop ();
        }
        if (q.empty ()) return false;
        Student t=q.top ();
        q.pop ();
        if (t.num==0) res+=t.cost;
        t.num++;
        tmp[a[i].id]=t.id;
        q.push (t);
    }
    if (res>s) return false;
    for (int i=1;i<=m;++i) Ans[i]=tmp[i];
    return true;
}
int main () {
    ios::sync_with_stdio (false); cin.tie (0); cout.tie (0);
    cin>>n>>m>>s;
    for (int i=1;i<=m;++i) {
        cin>>a[i].val;
        a[i].id=i;
    }
    sort (a+1,a+m+1);
    for (int i=1;i<=n;++i) {
        cin>>b[i].val;
        b[i].id=i;
    }
    for (int i=1;i<=n;++i) 
        cin>>b[i].cost;
    sort (b+1,b+n+1,cmp);
    int l=1,r=m+1,ans=-1;
    while (l<=r) {
        int mid=(l+r)>>1;
        if (check (mid)) {
            ans=mid;
            r=mid-1;
        }
        else {
            l=mid+1;
        }
    }
    if (ans==-1) {
        cout<<"NO"<<endl;
        return 0;
    }
    cout<<"YES"<<endl;
    for (int i=1;i<=m;++i) cout<<Ans[i]<<" ";
}
```


---

