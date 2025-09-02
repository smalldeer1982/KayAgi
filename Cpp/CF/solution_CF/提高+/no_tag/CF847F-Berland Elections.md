# Berland Elections

## 题目描述

The elections to Berland parliament are happening today. Voting is in full swing!

Totally there are $ n $ candidates, they are numbered from $ 1 $ to $ n $ . Based on election results $ k $ ( $ 1<=k<=n $ ) top candidates will take seats in the parliament.

After the end of the voting the number of votes for each candidate is calculated. In the resulting table the candidates are ordered by the number of votes. In case of tie (equal number of votes) they are ordered by the time of the last vote given. The candidate with ealier last vote stands higher in the resulting table.

So in the resulting table candidates are sorted by the number of votes (more votes stand for the higher place) and if two candidates have equal number of votes they are sorted by the time of last vote (earlier last vote stands for the higher place).

There is no way for a candidate with zero votes to take a seat in the parliament. So it is possible that less than $ k $ candidates will take a seat in the parliament.

In Berland there are $ m $ citizens who can vote. Each of them will vote for some candidate. Each citizen will give a vote to exactly one of $ n $ candidates. There is no option "against everyone" on the elections. It is not accepted to spoil bulletins or not to go to elections. So each of $ m $ citizens will vote for exactly one of $ n $ candidates.

At the moment $ a $ citizens have voted already ( $ 1<=a<=m $ ). This is an open election, so for each citizen it is known the candidate for which the citizen has voted. Formally, the $ j $ -th citizen voted for the candidate $ g_{j} $ . The citizens who already voted are numbered in chronological order; i.e. the $ (j+1) $ -th citizen voted after the $ j $ -th.

The remaining $ m-a $ citizens will vote before the end of elections, each of them will vote for one of $ n $ candidates.

Your task is to determine for each of $ n $ candidates one of the three possible outcomes:

- a candidate will be elected to the parliament regardless of votes of the remaining $ m-a $ citizens;
- a candidate has chance to be elected to the parliament after all $ n $ citizens have voted;
- a candidate has no chances to be elected to the parliament regardless of votes of the remaining $ m-a $ citizens.

## 样例 #1

### 输入

```
3 1 5 4
1 2 1 3
```

### 输出

```
1 3 3 ```

## 样例 #2

### 输入

```
3 1 5 3
1 3 1
```

### 输出

```
2 3 2 ```

## 样例 #3

### 输入

```
3 2 5 3
1 3 1
```

### 输出

```
1 2 2 ```

# 题解

## 作者：xzggzh1 (赞：2)

题意：

$m$ 个人给 $n$ 个候选人投票，票数前 $k$ 的候选人可以被选中，若票数相同则最后一票的时间早的人在前，无票者不能被选中。

已知前 $a$ 个人的投票，问 $n$ 个候选人是下面三种情况的哪种。

1. 无论剩下的 $m-a$ 人选谁，都能被选中。 

1. 有机会被选中。 

1. 无论剩下的 $m-a$ 人选谁，都不能被选中。 

$n,m\leq 100$ 。

---

对于 $1$ ，尽量分配票给当前选手后的第一位，最后是否能被挤出前 $k$ 。

对于 $3$ ，剩余票全部分配给自己，最后是否能进入前 $k$ 。

若不是 $1$ ，$3$ 那么就是 $2$ 。

由于数据范围较小，直接模拟即可。

---

核心代码：

```cpp
int n,k,m,p,now,pos,tid,x;
struct A{
	int cnt,las,id;
}a[233],b[233];
bool cmp(A a1,A a2){return a1.cnt==a2.cnt? a1.las<a2.las: a1.cnt>a2.cnt;}
int doit(){
	for (int i=1;i<=n;i++) b[i]=a[i];
	for (pos=1;b[pos].id!=now;pos++);
	b[pos].cnt+=p;if (p) b[pos].las=(tid=m)+p;
	sort(b+1,b+n+1,cmp);
	for (pos=1;b[pos].id!=now;pos++);
	if (pos>k||b[pos].cnt==0) return 0*printf("3 ");
	for (int i=1;i<=n;i++) b[i]=a[i];
	for (pos=1;b[pos].id!=now;pos++);
	for (int l=p,the=pos+1;l&&the<=n;the++)
	for (;l&&(b[the].cnt==b[pos].cnt? b[the].las>=b[pos].las: b[the].cnt<b[pos].cnt);l--)
	b[the].cnt++,b[the].las=++tid;	
	sort(b+1,b+n+1,cmp);
	for (pos=1;b[pos].id!=now;pos++);
	if (pos>k||b[pos].cnt==0) return 0*printf("2 ");
	printf("1 ");
} 
int main(){
	scanf("%d%d%d%d",&n,&k,&p,&m);p-=m;
	for (int i=1;i<=m;i++){
		scanf("%d",&x);
		a[x].cnt++;
		a[x].las=i;
	}
	for (int i=1;i<=n;i++)a[i].id=i;
	sort(a+1,a+n+1,cmp);now=1;
	for (int i=1;i<=n;i++,now=i)doit();
}
```

---

## 作者：QQH08 (赞：0)

首先看数据范围，看到 $n,m$ 只有 $100$ ，果断想暴力（贪心策略）。

下面是解题思路:
1. 对于答案为 $1$ 的情况，我们考虑让尽量多原先比 $i$ 小的都加票到比 $i$ 大。所以我们先按票数和时间对原序列排序，票数从大到小，时间从前到后。

	- 对于每一个在 $i$ 之前的数，显然满足要求，所以不用管。

	- 对于每一个在 $i$ 之后的数，让它加到 $i$ 的票数 $+1$ （因为它的时间晚，所以要比 $i$ 多 $1$ ），看剩下的票数够几个人挤到 $i$ 的前面去，能否让 $i$ 还保持前 $k$。、

2. 对于答案为 $3$ 的情况，我们把剩下的票数全给 $i$，看它能不能进前 $k$ 即可（注意它的时间是最晚的）。

3. 剩下的就是 $2$ 啦。

注意事项：无票者不能被选中（特判即可）。

下面就是代码了：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=105;
struct node{
	int val,id,tim;
}s[N];
int n,k,m,a,p[N],ans[N];
bool cmp(node a,node b){
	if(a.val==b.val)return a.tim<b.tim;
	else return a.val>b.val;
}
int main(){
	scanf("%d%d%d%d",&n,&k,&m,&a);
	for(int i=1;i<=n;i++)s[i].id=i,s[i].tim=0;
	for(int i=1;i<=a;i++){
		scanf("%d",&p[i]);
		s[p[i]].val++;
		s[p[i]].tim=i;
	}
	sort(s+1,s+n+1,cmp);
	for(int i=1;i<=n;i++){
		int s1=s[i].val,res=i-1,tmp=m-a;
		for(int j=i+1;j<=n;j++){
			int y=s1-s[j].val+1;
			if(y>tmp)break;
			tmp-=y;
			res++;
		}
		if(res<k&&s[i].val!=0){
			ans[s[i].id]=1;
			continue;
		}
		res=0;
		s[i].val+=(m-a);
		for(int j=1;j<=n;j++)
			if(s[j].val>=s[i].val&&i!=j)res++;
		if(res>=k||s[i].val==0)ans[s[i].id]=3;
		else ans[s[i].id]=2;
		s[i].val=s1;
	}
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	return 0;
}
```


---

