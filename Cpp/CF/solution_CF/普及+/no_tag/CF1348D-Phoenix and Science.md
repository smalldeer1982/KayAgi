# Phoenix and Science

## 题目描述

Phoenix has decided to become a scientist! He is currently investigating the growth of bacteria.

Initially, on day $ 1 $ , there is one bacterium with mass $ 1 $ .

Every day, some number of bacteria will split (possibly zero or all). When a bacterium of mass $ m $ splits, it becomes two bacteria of mass $ \frac{m}{2} $ each. For example, a bacterium of mass $ 3 $ can split into two bacteria of mass $ 1.5 $ .

Also, every night, the mass of every bacteria will increase by one.

Phoenix is wondering if it is possible for the total mass of all the bacteria to be exactly $ n $ . If it is possible, he is interested in the way to obtain that mass using the minimum possible number of nights. Help him become the best scientist!

## 说明/提示

In the first test case, the following process results in bacteria with total mass $ 9 $ :

- Day $ 1 $ : The bacterium with mass $ 1 $ splits. There are now two bacteria with mass $ 0.5 $ each.
- Night $ 1 $ : All bacteria's mass increases by one. There are now two bacteria with mass $ 1.5 $ .
- Day $ 2 $ : None split.
- Night $ 2 $ : There are now two bacteria with mass $ 2.5 $ .
- Day $ 3 $ : Both bacteria split. There are now four bacteria with mass $ 1.25 $ .
- Night $ 3 $ : There are now four bacteria with mass $ 2.25 $ .

 The total mass is $ 2.25+2.25+2.25+2.25=9 $ . It can be proved that $ 3 $ is the minimum number of nights needed. There are also other ways to obtain total mass 9 in 3 nights.  $   $

In the second test case, the following process results in bacteria with total mass $ 11 $ :

- Day $ 1 $ : The bacterium with mass $ 1 $ splits. There are now two bacteria with mass $ 0.5 $ .
- Night $ 1 $ : There are now two bacteria with mass $ 1.5 $ .
- Day $ 2 $ : One bacterium splits. There are now three bacteria with masses $ 0.75 $ , $ 0.75 $ , and $ 1.5 $ .
- Night $ 2 $ : There are now three bacteria with masses $ 1.75 $ , $ 1.75 $ , and $ 2.5 $ .
- Day $ 3 $ : The bacteria with mass $ 1.75 $ and the bacteria with mass $ 2.5 $ split. There are now five bacteria with masses $ 0.875 $ , $ 0.875 $ , $ 1.25 $ , $ 1.25 $ , and $ 1.75 $ .
- Night $ 3 $ : There are now five bacteria with masses $ 1.875 $ , $ 1.875 $ , $ 2.25 $ , $ 2.25 $ , and $ 2.75 $ .

 The total mass is $ 1.875+1.875+2.25+2.25+2.75=11 $ . It can be proved that $ 3 $ is the minimum number of nights needed. There are also other ways to obtain total mass 11 in 3 nights.  $   $

In the third test case, the bacterium does not split on day $ 1 $ , and then grows to mass $ 2 $ during night $ 1 $ .

## 样例 #1

### 输入

```
3
9
11
2```

### 输出

```
3
1 0 2 
3
1 1 2
1
0```

# 题解

## 作者：dp_everyday (赞：18)

首先要抓住题目的性质，把题目所问的提炼以下，就变成了这样的描述
### 题目描述
给定一个数 x = 1，初始sum = 1，每次可对x进行操作，将其值变为[x, x * 2]之间的任意一个数，然后将sum加上现在的x，问最少需要几次操作可以变成给定的数字n，同时对于每次操作输出 x 的改变量。
### 思路
要达到最少次数，贪心的想每次肯定加上最多的量 x * 2，然而每次最少加上变化过的x，所以最后一次加的数可能小于当前的x，但是没关系，可以让这次加上的那个小于x的数尽可能的往前移直到前一个数小于等于它，然后按照顺序求一遍答案即可。
具体看代码就通俗易懂了。
### 代码
```cpp
void solve() {
	int n;
	scanf("%d", &n);
	vector<int> v;
	int x = 1;
	while(n > 0) {
		if(n > x) v.push_back(x);
		else v.push_back(n);
		n -= x;
		x <<= 1;
	}
	sort(v.begin(), v.end());
	printf("%d\n", v.size() - 1);
	for(int i = 1; i < v.size(); i++) {
		printf("%d ", v[i] - v[i - 1]);
	}
	puts("");
}

---

## 作者：huayucaiji (赞：3)

这道题很有意思的~

首先我们发现，$d$ 的值其实很好想。我们先考虑在第 $d$ 天的最多数量（长度），也就是每个晚上所有的都分裂。

|1|2|3|4|5|....|d|
|----|----|----|----|----|----|----|
|1|3|7|15|31|....|$2^d-1$|

所以说给定 $n$，我们可以求出 $d=\log n$。这一点很好想到，但是我们的难点就在如何去构造答案。

我们还可以知道一点，如果我们在第 $i$ 天分裂 $p_i$ 个病毒，我们对最终 $n$ 的贡献为 $(d-i+1)\cdot p_i$。而且我们要明确，~~病毒的防治要越早越好~~我们的病毒越早分裂越好控制，到后面数量多了，反而不好控制，所以我们尽量让病毒在前期分裂。

所以整个算法的思路就很简单了，我们尽量在每一天分裂最多的病毒，也就是 $\min (\frac{left}{d-i+1},hold)$，$left$ 表示我们还要多少的长度，$now$ 表示我们现在有多少病毒。如果最后我们处理下来 $n\neq 0$，就代表无解，输出 $-1$ 即可，否则输出我们的答案数组。

做个总结，我们的宗旨就是尽量在前期控制，如果是从后往前推很容易脱节，找不到答案，那就失败了。所以行前往后在这里反而是一种最好的选择。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

int n,p[100001];

signed main() {
	int t=read();
    while (t--) {
        n=read();
        int d=0,tot=0,t=1;
        for (;tot<n;d++,t<<=1) {
            tot+=t;
        }
        d--;
        n=n-1-d;
        int hold=1,k;
        for (int i=d;i>=1;--i) {
            k=min(n/i,hold);
            p[d-i+1]=k;
            n-=k*i;
            hold+=k;
        }
        
        if (n!=0) {
            cout<<-1<<endl;
        } 
		else {
            cout<<d<<endl;
            for(int i=1;i<=d;++i)
                cout<<p[i]<< " ";
            cout<<endl;
        }
    }
	return 0;
}
```

---

## 作者：fedoralxy (赞：1)

## 解题思路

| 天数 | 1 | 2 | 3 | 4 | $\cdots$ | $n$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 增加 | 1 | 3 | 7 | 15 | $\cdots$ | $2^{n-1}$ |

不难列表发现，第 $i$ 天最多能增加 $2^{i-1}$ 
个细菌。

接下来，我们采用贪心策略，即可。

查找时，为加快速度，此处采用二分。

最后注意一点：细菌**从小到大**扩展。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define d lld
using namespace std;
const int N=1e5+10;
struct cplus
{
	ll t,n,day,a[N],now,pre,tmp;
	ll l,r,mid;
	
	
	void init()
	{
		day=0,a[0]=1;
		while(a[day]<=1e9)
		{
			day++;
			a[day]=a[day-1]<<1;
		}
	}
	
	
	ll find(ll k)
	{
		l=1,r=day;
		while(l<=r)
		{
			mid=(l+r)/2;
			if(a[mid]>k)
				r=mid-1;
			else
				l=mid+1;
		}
		return r;
	}
}goin;
int main()
{
	goin.init();
	scanf("%d",&goin.t);
	while(goin.t--)
	{
		scanf("%d",&goin.n);
		goin.now=goin.find(goin.n);
		printf("%d\n",goin.now);
		
		
		goin.n=goin.n-1-goin.now;
		goin.pre=1;
		
		
		for(ll i=goin.now;i>=1;i--)
		{
			goin.tmp=min(goin.pre,goin.n/i);
			goin.pre+=goin.tmp;
			goin.n-=goin.tmp*i;
			printf("%d ",goin.tmp);
		}
		
		
		puts("");
	}
	return 0;
}
```

---

## 作者：_JF_ (赞：0)

[CF1348D Phoenix and Science](https://www.luogu.com.cn/problem/CF1348D)


结论的猜。

首先先转化题意，观察到我们不必在乎每个细菌的质量是多少，每天产生的贡献其实就是细菌的数量。我们把重心放在这个贡献上。

如果你这个分裂想象成一个树的话，那其实分裂一次就是把一个点连上两个儿子，然后每天的贡献就是叶子的数量。

注意到这个无解肯定是假的，我再不行我让一个细菌生长 $n$ 天即可。

然后我们注意到，其实我们如果每天都把所有细菌分裂的话，我们每天就能拿到 $2^{i}$ 个贡献，这样一定是优秀的，因为要求为 $n$ 个，注意到 $n \le10^9$，所以，天数不会太多。

首先有一个经典的结论，对于任何一个 $x$，都能被表示成 $2^0+2^1+2^2+...+2^k+p$，先忽略这个 $p$，看成贡献就是 $k$ 天，每个细菌都分裂。

假设 $2^x \le p \le 2^{x+1}$，那么我们在做出来 $x$ 以后，注意到现在是 $2^x$ 个叶子，我们只用在今明两天分裂 $p-2^x,2^{x+1}-p$ 个细菌即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long
int ans[N],tot,n;
priority_queue<int,vector<int>,greater<int> > q;
signed main(){
	int t;
	cin>>t;
	while(t--){
		while(!q.empty())	q.pop();
		tot=0;
		cin>>n; int dus=1,Now=-1;
		while(1){
			if(n>=dus){
				n-=dus,q.push(dus);
				if(n==0)	break;
			}
			else{Now=n,q.push(n); break;}
			dus*=2;
		} 
		q.pop(); int lst=1,predis=0;  
		while(!q.empty()){
			int now=q.top(); q.pop();
			if(now==lst*2)	ans[++tot]=lst,lst*=2;
			else{
				predis++;
				if(predis==1)	ans[++tot]=now-lst,lst=now;	
				else	ans[++tot]=(now/2-(lst-now/2)),lst=now;
			}
		}
		cout<<tot<<endl;
		for(int i=1;i<=tot;i++)	cout<<ans[i]<<' ';
		cout<<endl;
	}
	return 0;
}

```

---

## 作者：Wander_E (赞：0)

此题考虑**贪心**，策略其实非常简单，第 $i$ 天最多能够**增加** $2^{i-1}$ 个细菌，能加就加，最后将方案从小到大排序输出即可（因为实际情况是从小到大扩展）。

附上 AC 代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
 
const int N = 1e6 + 5;
const int INF = 0x3f3f3f3f;
int n;
int ans[N], id;
bool first = 0;
int sum = 0;

signed main()
{
	int T;
	cin >> T;
	while(T--)
	{
		memset(ans, 0 ,sizeof ans);
		id = 0;
		cin >> n;
		if(n == 2)
		{
			cout << "1\n0\n";
			goto END;
		}
		for(int i = 0; i <= 30; i++)
		{
			if(n > (1 << i)) ans[++id] = (1 << i), n -= (1 << i);
			else
			{
				ans[++id] = n;
				break;
			}
		}
		sort(ans + 1, ans + id + 1);
		cout << id - 1 << endl;
		for(int i = 2; i <= id; i++)
			cout << ans[i] - ans[i - 1] << ' ';
		cout << endl;
		END:continue;
	}
	return 0;
}
```

---

