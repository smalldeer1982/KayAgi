# Exams

## 题目描述

Vasiliy has an exam period which will continue for $ n $ days. He has to pass exams on $ m $ subjects. Subjects are numbered from 1 to $ m $ .

About every day we know exam for which one of $ m $ subjects can be passed on that day. Perhaps, some day you can't pass any exam. It is not allowed to pass more than one exam on any day.

On each day Vasiliy can either pass the exam of that day (it takes the whole day) or prepare all day for some exam or have a rest.

About each subject Vasiliy know a number $ a_{i} $ — the number of days he should prepare to pass the exam number $ i $ . Vasiliy can switch subjects while preparing for exams, it is not necessary to prepare continuously during $ a_{i} $ days for the exam number $ i $ . He can mix the order of preparation for exams in any way.

Your task is to determine the minimum number of days in which Vasiliy can pass all exams, or determine that it is impossible. Each exam should be passed exactly one time.

## 说明/提示

In the first example Vasiliy can behave as follows. On the first and the second day he can prepare for the exam number 1 and pass it on the fifth day, prepare for the exam number 2 on the third day and pass it on the fourth day.

In the second example Vasiliy should prepare for the exam number 3 during the first four days and pass it on the fifth day. Then on the sixth day he should prepare for the exam number 2 and then pass it on the seventh day. After that he needs to prepare for the exam number 1 on the eighth day and pass it on the ninth day.

In the third example Vasiliy can't pass the only exam because he hasn't anough time to prepare for it.

## 样例 #1

### 输入

```
7 2
0 1 0 2 1 0 2
2 1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
10 3
0 0 1 2 3 0 2 0 1 2
1 1 4
```

### 输出

```
9
```

## 样例 #3

### 输入

```
5 1
1 1 1 1 1
5
```

### 输出

```
-1
```

# 题解

## 作者：WCG2025 (赞：6)

题意：
	某人要考试，现在总共有n天m门考试，在这n天中有几天是可以考特定的科目的，题中的d数组会给出

比如

0 0 1 2 3 0 2 0 1 2

	表示在第3、9天可以考科目1。 4、7、10天可以考科目2.。。。标号为0的那天可以用来复习，如果不选择当天考试的话那天也可以用来复习

	但是每门考试都需要复习一定的天数ai才能考好，对复习天数的要求是不用连续，只要累计达到ai即可

	主人公想花最少的天数每门都考好，求最少天数，如果根本不可能输出－1
	这道题看似很像动态规划，但居然是二分搜索答案！真是没有想到，我感觉这个能想到的话就是要先确定我们能判断给在给定的这些考试要求的情况下t天是否可能完成要求。对于t可以确定其是否可能才能在1～n内做二分搜索啊！

	假定现在有t天，我们采取贪心的策略，每门科目都参加最后的那一场，那么前面就会有尽可能多的时间给自己复习，如果即使这样还是不能复习完的话，就不可能复习完，输出负一就好了

	能够确定t天能否达到要求后，就能在1～n天内二分了
```cpp
#include<bits/stdc++.h>
#define ll long long
#define maxn 100000
ll n,m,a[maxn],d[maxn];
bool flag[maxn];
ll ans=-1;
using namespace std;
int check(ll x)
{
    ll sum=0;
    memset(flag,0,sizeof(flag));
    for(int i=x;i>=1;i--)//从后往前扫，尽量参加最后一场
    {
        if(d[i]!=0&&flag[d[i]]==0)//如果有一天可以考试并且
        {//这门还没考，就把他考了（即加上复习天数）
            sum+=a[d[i]];
            flag[d[i]]=1;
        }
        else if(sum!=0)//如果今天没有考试，就可以拿一天
        sum--;//复习
    }
    if(sum!=0)//如果天数不是零，要么说明就还需要复习
    //当前天数不够
    return 0;
    for(int i=1;i<=m;i++)
    if(flag[i]==0)//有一门没考
    return 0;
    return 1;
}
int main()//二分常规操作
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    cin>>d[i];
    for(int i=1;i<=m;i++)
    cin>>a[i];
    ll down=m,up=n,mid;
    while(down<=up)
    {
        mid=(down+up)/2;
        if(check(mid)==1)
        {
            ans=mid;
            up=mid-1;
        }
        else
        down=mid+1;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Z_M__ (赞：4)

算法：二分、贪心
---
二分天数，$check$ 函数中要贪心，每一科都在二分出的天数中的最后一个考试日考掉，这样可以避免这样的数据，一门科要复习$a$日,且考试日只有第$a$日，但前$a$日中有能考的 后面还有考试日的 科目。


$AC code:$
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
int n, m, a[MAXN], d[MAXN], nex[MAXN], b[MAXN];
bool vis[MAXN];
bool check (int x)
{
	memset (vis, 0, sizeof (vis));
	memset (nex, 0, sizeof (nex));
	memset (b, 0, sizeof (b));
	for (int i = x; i >= 1; i--)
		if (d[i])
		{
			if (b[d[i]]) nex[i] = b[d[i]];
			else nex[i] = -1;
			b[d[i]] = i;
		}
	int cnt = 0, free = 0;
	for (int i = 1; i <= x; i++)
	{
		if (d[i] == 0 || vis[d[i]] || nex[i] != -1 || a[d[i]] > free) free++;
		else free -= a[d[i]], vis[d[i]] = 1, cnt++;
	}
	if (cnt == m) return 1;
	return 0;
}
int main ()
{
	ios :: sync_with_stdio (0), cin.tie (0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> d[i];
	for (int i = 1; i <= m; i++)
		cin >> a[i];
	int l = 1, r = n, mid, ans = -1;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check (mid)) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：觞羰涙 (赞：2)

# 考虑二分
记录每一科的考试时间
今天不考就增加可复习天数
今天考试就看前几天的可复习天数够不够
就可以写出check了
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<iomanip>
#define maxn 100005
typedef long long ll;
int n,m;
int d[maxn],a[maxn]; 
int vis[maxn];
using namespace std;
template <class T> void read(T &x)
{
	x=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	x*=f;
}
bool fuck(int x)
{
	int left_day=0,left_cla=m;
	memset(vis,0,sizeof(vis));
	for(int i=x;i>=1;i--)
	if(!vis[d[i]])vis[d[i]]=i;//每一科尽量晚点考 更容易满足条件 
	for(int i=1;i<=x;i++)
	{	//很强的check 
		if(d[i]==0||vis[d[i]]!=i)++left_day;//如果今天不考就复习一天 
		else
		{
			left_day-=a[d[i]];
			if(left_day<0)return false;
			--left_cla;
		}
	}
	return (!left_cla);//考完了剩余课程为0 
}
int main()
{
	//zzy
	read(n);read(m);
	for(int i=1;i<=n;i++)read(d[i]);
	for(int i=1;i<=m;i++)read(a[i]);
	int l=0,r=n,ans=-1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(fuck(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：灵乌路空 (赞：1)

最后无良宣传一下博客 $wwwwww$      
[文章列表 - 地灵殿 - 洛谷博客](https://www.luogu.org/blog/koishikoishi/) 


---

## 知识点: 贪心, 二分答案, 模拟 



### [原题面](https://www.luogu.org/problem/CF732D)


### 分析题意:

可以发现 , 复习的科目种类是没有影响的   
可根据考试的不同 调整复习课目  
只需要考虑复习天数是否足够即可   

若只考虑 能否完成所有考试:     
- 显然, 在一次考试最后一次出现时将其完成必然最优   
  因为这样有 最多的复习时间    
  
  若在上述情况下仍然无法将所有考试完成, 则必不合法    

由于答案满足单调性, 则可考虑二分答案 :

- 检查合法性时, 按照上述贪心策略,    
  在每一次考试 在二分量之前的最后一次出现位置 完成,   
  其余时间 都用来复习, 必然更优
  
  检查在考试天时, 复习天数是否足够完成考试即可
  
总复杂度 $O(n\log n)$

---

附 $AC$ 代码


```cpp
#include <cstdio>
#include <cstring>
#include <ctype.h>
#define int long long
const int MARX = 1e5 + 10;
//=============================================================
int N, M, first, ans, d[MARX], a[MARX], last[MARX], checker[MARX];
//=============================================================
inline int read()
{
    int s = 1, w = 0; char ch = getchar();
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') s = -1;
    for(; isdigit(ch); ch = getchar()) w = (w << 1) + (w << 3) + (ch ^ '0');
    return s * w;
}
bool check(int lim)//检查合法性 
{
	memset(checker, 0, sizeof(checker));
	for(int i = 1; i <= lim; i ++) last[d[i]] = i;//记录最后一次出现位置 
	for(int i = 1; i <= M; i ++) checker[last[i]] = a[i];//对进行考试的天进行标记 
	
	for(int i = 1, sum = 0; i <= lim; i ++)
	{
	  if(sum < checker[i]) return 0;//不合法 
	  if(! checker[i]) sum ++;//第i天复习 
	  else sum -= checker[i];//第i天考试 
	}
	return 1;
}
//=============================================================
signed main()
{
	N = read(), M = read();
	for(int i = 1; i <= N; i ++)  
	{
	  d[i] = read();
	  if(! last[d[i]]) first = i;
	  last[d[i]] = i;
	}
	for(int i = 1; i <= M; i ++)  
	{
	  a[i] = read();
	  //检查是否有一科考试, 在N天中都没有出现: 
	  if(! last[i]) {printf("-1"); return 0;} 
	}
	
	if(! check(N)) {printf("-1"); return 0;}//检查是否能完成 
	for(int l = first, r = N; l <= r;)//二分答案 
	{
	  int mid = (l + r) >> 1;
	  if(check(mid)) ans = mid, r = mid - 1;//检查, 调整边界 
	  else l = mid + 1;
	}
	printf("%lld", ans);
}
```


---

## 作者：EarthGiao (赞：1)

## 【思路】
二分答案 +贪心    

### 【题目大意】  
每一天你可以完成任务或者积攒能量     
每一个任务的完成都需要消耗一定的能量      
每一天都只能完成一个特定的任务或者不能完成任务       
求最早什么时候完成全部的任务     

### 【题目分析】
从题意中可以看出如果能够在第i天完成全部的任务   
那么一定能够在第i+1天完成全部的任务    
所以用二分答案就很显然了吧    

### 【核心思路】
二分完成需要的天数     
不过这里怎么判断某个天数到底行不行呢？    
因为只需要判断行不行而不需要判断优不优   
所以只需要知道能不能完成就可以了    
不管完成的过程优不优    
那就考虑最差的能够完成的情况    
就是在规定时间内    
每一个任务最后一次出现的时候能够把它完成掉就是可以的    
所以在不是最后一次出现的情况下就囤积能量    
在最后一次出现的地方就完成    
如果完成不了那就是不行   
到最后再检查一下一共m个任务是不是每一个任务都完成了       
## 【完整代码】
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long
using namespace std;

int read()
{
	int sum = 0,fg = 1;
	char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-')fg = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		sum = sum * 10 + c - '0';
		c = getchar();
	}
	return sum * fg;
}
const int Max = 100005;
int d[Max];
int a[Max];
int t[Max];
int n,m;
bool check(int x)
{
	memset(t,0,sizeof(t));
	int tot = 0;
	int acioi = 0;
	for(register int i = 1;i <= x;++ i)
		t[d[i]] ++;
	for(register int i = 1;i <= x;i ++)
	{
		if(d[i] != 0)
		{
			t[d[i]] -= 1;
			if(t[d[i]] == 0)
			{
				acioi ++;
				tot -= a[d[i]];
				if(tot < 0)
					return false;
			}
			else
				tot ++;
		}
		else
			tot ++;
	}
	for(register int i = 1;i <= m;++ i)
		if(t[i] != 0)
			return false;
	if(acioi == m)
		return true;
	else
		return false;
}

signed main()
{
//	freopen("generals.in","r",stdin);
//	freopen("generals.out","w",stdout);
	n = read(),m = read();
	for(register int i = 1;i <= n;++ i)
		d[i] = read();
	for(register int i = 1;i <= m;++ i)
		a[i] = read();
	int l = 1,r = n + 1;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(check(mid))r = mid;
		else	l = mid + 1;
	}
	if(l == n + 1)
	{
		cout << -1 << endl;
		return 0;
	}
	cout << l << endl;
	return 0;
}
```

---

## 作者：谦谦君子 (赞：1)

在此就写一下思路吧，~~代码可以请各位巨佬自己去交~~


------------

## 思路
#### 寻找最优位置的题目，联想用二分查找。枚举最优位置，判断即可，主要想到用二分就好做了！每次判断某个位置是否可行时，从后往前进行贪心的进行；遇到新的未通过的考试，则进入一个队列等待，遇到空的日期就把它用于当前队列最前位置的考试，直到满足m个考试就行了。

---

## 作者：斜揽残箫 (赞：0)

## Description

[传送门](https://www.luogu.com.cn/problem/CF732D)

给定一个序列，如果有考试，可以选择考试或者复习，否则只能复习，求最少第几天才能考完所有的考试。

$1 \leq n ,m\leq 10 ^ 5$。

考试的时候以为这是个 DP，但是不会处理重复情况，所以就 gg 了，考完后才知道可以二分 + 贪心做。

## Solution

本题知识点 : 二分，贪心。

首先来判断不合法情况，贪心的想，如果每场考试的最后的考试机会都没法通过考试的话，肯定是没法通过所有的考试，因为这样的情况攒的兵力是最多的，通过这样，就可以判断是否有解。

接下来考虑最优情况，如果最后一个考试能在前面完成且能够通过所有的考试，我们肯定是去考试而不是去复习。

所以我们可以二分一个值 ```Num```，表示在 ```Num``` 前的天之中是否能够完成所有的考试。

接下来是 check 的过程，判断是否合法，我们从最后一天往前枚举，如果碰到要考的考试就加上点数并打上标记，否则就积攒点数。

如果发现点数 $> 0$ 或者是有没有标记过的返回 ```false```，否则是 ```true```。

## Code
```
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1e5 + 10;
int a[MAXN],b[MAXN],id[MAXN],vis[MAXN];
int Ans = 0;
int n,m;
inline int read()
{
	int s = 0, f = 0;char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}
inline int Max(int x,int y) {return x > y ? x : y;}
inline int Min(int x,int y) {return x < y ? x : y;}
inline bool check(int Num)
{
  int res = 0;
  memset(vis,0,sizeof vis);
  for(int i = Num;i >= 1;i --) {
    if(a[i] != 0 && !vis[a[i]]) {
      res += b[a[i]];
      vis[a[i]] = true;
    } 
    else if(res != 0) res --;
  }
  if(res > 0) return false;
  for(int i = 1;i <= m;i ++) if(!vis[i]) return false;
  return true;
}
signed main()
{
//  freopen("generals.in","r",stdin);
//  freopen("generals.out","w",stdout);
  n = read(),m = read();
  for(int i = 1;i <= n;i ++) a[i] = read();
  for(int i = 1;i <= m;i ++) b[i] = read();
  int L = 1,R = n;
  while(L <= R) {
    int mid = (L + R) >> 1;
    if(check(mid)) R = mid - 1,Ans = mid;
    else L = mid + 1;
  }
  if(!Ans) puts("-1");
  else printf("%d\n",Ans);
//  fclose(stdin);
//  fclose(stdout);
  return 0;
}
```

---

## 作者：KEBrantily (赞：0)

今上午的模拟赛考了这道题，改了一下题面。

本来切掉了，考场源码交到 CF 上也过了，但是因为你教师机评测太牛逼硬是把我代码判错了，现在也不是很理解为什么。

- - -

用了一种和大多数人不一样的方法。

首先考虑什么时候无解。

显然，越晚攻击一个敌人，就越有可能击败他。也就是说，如果我们让所有敌人在最后出现时刻时被攻击，仍不能击败所有人，那么无解。

然后我们再考虑如何取最优答案。

让所有人在最后时刻被击败肯定是最劣的一种答案，那么想要使答案尽可能优，肯定要每次找出最后一个被消灭的敌人，使他的出现时刻变成上一个，再尝试能否全部击败。

接着考虑一下，移动一个敌人会产生什么影响。

我们先记录最劣情况下到每个时刻的士兵数量。

假设我们最后出现的敌人位置为 $x$，这个敌人的上一个出现位置是 $y$，消灭这个敌人需要花费 $v$ 的士兵。

那么我们把这个士兵从 $x$ 移走，显然 $[x,n]$ 位置的士兵数要在现在的基础上加 $v+1$ 个（攻击花费的 $v$ 个与走到 $x$ 位置时新增的 $1$ 个）。

然后我们把这个士兵插入到位置 $y$，那么 $[y,n]$ 的士兵数要在现在的基础上减去 $v+1$ 个，理由同上。

如何判断移动这个士兵合不合法呢？只需要判断减去这个值之后，$[y,n]$ 位置有没有出现负数即可，原因显然。具体操作时可以求出 $[y,n]$ 位置的最小值，判断一下是否大于等于 $v+1$。

所以我们只需要对序列进行区间加和区间求最小值两种操作，上线段树即可。

```cpp
bool vis[maxn];
int n,m,tot,Ans,all,a[maxn];
int lst[maxn],ck[maxn];
int pos[maxn],val[maxn];
deque<int> id[maxn];
struct node{int a,b;};
deque<node> q;

namespace Seg{
  #define ls x<<1
  #define rs x<<1|1
  int minx[maxn<<2],lazy[maxn<<2];
  
  void pushup(int x){
    minx[x]=min(minx[ls],minx[rs]);
  }
  
  void pushdown(int x){
    if(lazy[x]==0) return;
    lazy[ls]+=lazy[x];lazy[rs]+=lazy[x];
    minx[ls]+=lazy[x];minx[rs]+=lazy[x];
    lazy[x]=0;
  }
  
  void build(int x,int l,int r){
    if(l==r){
      minx[x]=a[l];
      return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(x);
  }
  
  void update1(int x,int l,int r,int L,int R,int val){
    if(L<=l&&R>=r){
      minx[x]+=val;
      lazy[x]+=val;
      return;
    }
    int mid=l+r>>1;pushdown(x);
    if(L<=mid) update1(ls,l,mid,L,R,val);
    if(R>=mid+1) update1(rs,mid+1,r,L,R,val);
    pushup(x);
  }
  
  int query(int x,int l,int r,int L,int R){
    if(L<=l&&R>=r) return minx[x];
    int mid=l+r>>1,ans=INF;pushdown(x);
    if(L<=mid) ans=min(ans,query(ls,l,mid,L,R));
    if(R>=mid+1) ans=min(ans,query(rs,mid+1,r,L,R));
    return ans;
  }
}

signed main(){
  n=read(); m=read();
  for(int i=1;i<=n;i++){
    pos[i]=read();
    if(pos[i]){
      id[pos[i]].push_front(i);
      q.push_front((node){i,pos[i]});
    }
  }
  for(int i=n;i>=1;i--){
    if(!vis[pos[i]]||!pos[i]){
      vis[pos[i]]=1;
      if(pos[i]) lst[i]=pos[i],id[pos[i]].pop_front(),Ans=max(Ans,i);
    }
    else lst[i]=0;  
  }
  for(int i=1;i<=m;i++) val[i]=read();
  for(int i=1;i<=n;i++){
    if(lst[i]){
      all++;
      tot-=val[lst[i]];
      if(tot<0) return puts("-1"),0; 
    }
    else tot++;
    a[i]=tot;
  }
  if(all<m) return puts("-1"),0;
  Seg::build(1,1,n);
  while(1){
    if(q.size()==m) break;
    node P=q.front();q.pop_front();
    
    int fir=P.a,sec=P.b;
    int nxt_pos=id[sec].front();  
    
    id[sec].pop_front();
    Seg::update1(1,1,n,fir,n,1+val[sec]);
    int minx=Seg::query(1,1,n,nxt_pos,n);
    
    if(minx<1+val[sec]||minx>=INF) return printf("%d\n",Ans),0;
    Seg::update1(1,1,n,nxt_pos,n,-1-val[sec]);Ans=q.front().a;
  }
  printf("%d\n",Ans);
  return 0;
}
```

---

## 作者：loceaner (赞：0)

这题可以用**二分答案**来做

那么为什么可以用二分答案呢？

**答案当然是满足了单调性。** 假设用$x$天能够考完所有试，那么用大于$x $天必定也能够考完所有试，所以满足了单调性，我们就可以二分答案

那么如何$check$呢？考虑一下贪心

贪心思路：在二分的$mid$天之前找到每一科考试可以考的最后一天，只在这一天去考这一门科目，其它时间积攒复习时间，若在$mid$前这个科目可考的最后一天出现了，而此时积攒的复习时间并不足以考过这门科目，则说明用$mid$天不能考完这些科目，否则就让计数器$cnt$的值加一，表示现在已经考了$cnt$门，最后检验一下$cnt$是否等于$m$，若不等于则说明还有科目在$mid$天前没有出现，增大范围，否则缩小范围，让$ans$等于$mid$。

代码如下

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int A = 1e5 + 11;
const int B = 1e6 + 11;

inline int read() {
	char c = getchar(); int x = 0, f = 1;
	for( ; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for( ; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	return x * f;
}

int n, m, all, cnt;
int d[A], w[A], a[A], la[A];

inline bool check(int x) {
	memset(la, 0, sizeof(la));
	for(int i = 1; i <= n; i++) a[i] = d[i];
	for(int i = 1; i <= x; i++) if(a[i]) a[la[a[i]]] = 0, la[a[i]] = i; 
	int tl = 0, cnt = 0;
	for(int i = 1; i <= x; i++) {
		if(a[i]) { tl -= w[a[i]]; if(tl < 0) return 0; else cnt++; }
		else tl++;
	}
	return cnt == m; 
}

int main() {
	n = read(), m = read();
	if(n < m) return puts("-1"), 0;
	for(int i = 1; i <= n; i++) d[i] = read();
	for(int i = 1; i <= m; i++) w[i] = read(), all += w[i];
	if(all > n) return puts("-1"), 0;
	int l = 0, r = n, ans = -1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	return cout << ans << '\n', 0;
}

---

## 作者：mol茶蛋糕 (赞：0)

这道题其实就是**贪心+二分**  
做这一道题时我才发现二分是多么暴力...或者是我想的太多了...  

开始时我一直考虑二分时碰到不用考试的时间点怎么办，而后才想到只要在存时间的变量减一时判断一下正数就好了，因为这样不仅可以避免把在考完了之后才来复习的时间当成考完之前复习的时间，还可以通过判断变量最后是否为0来看是否在考完前复习完所有科目。  

而至于找到最优时间，就交给二分菌吧！

~~~
#include<iostream>
#include<cstring>
using namespace std;
int day[100005],tst[100005],ans=-1,n,m;;
bool vis[100005];
void t_part(int l,int r)		//二分 
{
	while(l<=r)
	{
		int mid=(l+r)>>1;
		int cnt=0,tot=0;
		//cnt记录可以考的科目个数，tot记录总共需要花的时间 
		memset(vis,0,sizeof vis);
		for(int i=mid;i>=1;i--)
		{
			if(!vis[day[i]]&&day[i])
			{
				tot+=tst[day[i]];
				cnt++;
				vis[day[i]]=1;
			}
			else if(tot)
				tot--;
		}
		if(tot==0&&cnt==m)
		{
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&day[i]);
	for(int i=1;i<=m;i++)
		scanf("%d",&tst[i]);
	t_part(1,n);
	if(ans==-1) printf("-1");
	else printf("%d",ans);
	return 0;
}
~~~

---

