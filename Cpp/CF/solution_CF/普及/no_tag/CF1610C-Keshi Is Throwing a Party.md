# Keshi Is Throwing a Party

## 题目描述

Keshi is throwing a party and he wants everybody in the party to be happy.

He has $ n $ friends. His $ i $ -th friend has $ i $ dollars.

If you invite the $ i $ -th friend to the party, he will be happy only if at most $ a_i $ people in the party are strictly richer than him and at most $ b_i $ people are strictly poorer than him.

Keshi wants to invite as many people as possible. Find the maximum number of people he can invite to the party so that every invited person would be happy.

## 说明/提示

In the first test case, he invites the first and the second person. If he invites all of them, the third person won't be happy because there will be more than $ 1 $ person poorer than him.

## 样例 #1

### 输入

```
3
3
1 2
2 1
1 1
2
0 0
0 1
2
1 0
0 1```

### 输出

```
2
1
2```

# 题解

## 作者：huyangmu (赞：4)

这道题要用到二分。

二分赴宴的人数，第 $i$ 个人的钱肯定比他之前所有人的钱多，满足单调性。

赴宴的最少有一个人，但不会超过 $n$ 个人，所以就确定了二分的上界和下界。

然后就要写判断函数了,选了 $x$ 个人时，每次要判断 $b_{i}>x$,并且 $a_{i}>n-x-1$。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int NR=2e5+5;
int T,n,a[NR],b[NR];
bool check (int x){
	int cnt=0;
	for (int i=1;i<=n;++i){//枚举每个人。
		if (a[i]<x-cnt-1||b[i]<cnt) continue;
		++cnt;	//统计符合人数
	}
	return cnt>=x;
}
signed main (){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while (T--){
		cin>>n;
		for (int i=1;i<=n;++i) cin>>a[i]>>b[i];
		int l=1,r=n,ans;
		while (l<=r){
			int mid=l+r>>1;
			if (check(mid)){
				ans=mid;
				l=mid+1;
			}else r=mid-1;
		}//二分模板
		cout<<ans<<'\n';
	}
	return 0;
}


---

## 作者：Terraria (赞：3)

## $\text{Introduction}$

有 $n$ 个人，第 $i$ 个人有 $i$ 元。现在要邀请若干个人参加宴会，若

- 钱数大于 $i$ 的人小于等于 $a_i$，

- 钱数小于 $i$ 的人小于等于 $b_i$，

则这个人会高兴。

现在求最多邀请多少个人使得每个参加宴会的人都会高兴。

## $\text{Solution}$

看到题目中有“最大”、“最小”之类的字眼，可以考虑二分。

对什么进行二分呢？显然是能够参加的人数，因为如果存在邀请 $k$ 个人时每个人都开心的方案，那么邀请 $k-1,k-2,\cdots$ 个人都一定可以。反过来如果 $k$ 个人时就不行，那么 $k+1,k+2,\cdots$ 个人时都没有方案。

所以答案具有单调性，我们决定对能够参与的人数进行二分。

大致雏形有了，现在的目标是写出 $\text{O}(n)$ 的 `check()`。

换句话说，如果我们已经有确定的人数了，该如何选人来判断人数是否可行呢？

可以考虑贪心。

现在的目标是根据已选的总人数判断我们可以选出的最多人数。如果我们的 `check()` 从小到大扫一遍 $i$，记 $cnt$ 是目前已选人数，$sum$ 是期望选择人数（即传入 `check()` 的参数），那么对于第 $i$ 个人：

- $b_i\ge cnt$ 则表示从 $1 \sim i-1$ 这些人选择的 $cnt$ 个人的钱数少于第 $i$ 个人的数量小于等于 $b_i$；

- $a_i \leq sum-cnt-1$ 则表示从 $i+1 \sim n$ 这些人选择的 $sum-cnt-1$ 个人的钱数多于第 $i$ 个人的数量小于等于 $a_i$；

这个时候如果把 $i$ 邀请过来，他也会开心。那么我们就一定会邀请他。

所以这样子扫了一遍过后，我们就得到了实际选择的人数，将其与 $sum$ 比较即可。

## $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int a[200009];
int b[200009];
bool check(int sum){
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(b[i]>=cnt&&a[i]>=sum-cnt-1) cnt++;
	}
	return (cnt>=sum);
}
void solve(){
	int ans;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	int l=1,r=n;
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	cout<<ans<<endl;
}
int main(){
	cin>>t;
	while(t--) solve();
}
```


---

## 作者：kevin1616 (赞：2)

### 审题
当宴会上的人中至多有 $a_i$ 人的钱严格比蓝多，至多有 $b_i$ 人的钱严格比蓝少时，求出最多能邀请的人数。
***
### 方法
【二分答案】当所选人数 $\le k$ 均合法，而所选人数 $>k$ 均不合法时，可以发现 $k$ 即为此时的最多邀请人数。故可以想到使用二分答案得出所选人数。
***
### 思路
答案是在 $1 \sim n$ 之间，每次判断所有人是否符合要求。令总人数为 $n$，选择了 $x$ 个人时，只需要每次判断 $b_i>x$，$a_i>n-x-1$ 是否同时满足。此部分代码如下：
```cpp
bool check(int x){
    int cnt = 0;
    for(int i = 1;i <= n;i++){
        if(a[i] >= x - cnt - 1 && b[i] >= cnt) cnt++;
    }
    return (cnt >= x);
}
```
每次进行判断，直到锁定此时最多邀请人数（即范围内仅有一个数），即为答案。
***
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int l,r;
int a[200005];
int b[200005];
bool check(int x){ //判断该数是否可行
    int cnt = 0;
    for(int i = 1;i <= n;i++){
        if(a[i] >= x - cnt - 1 && b[i] >= cnt) cnt++; //统计符合情况
    }
    return (cnt >= x); //返回可不可行
}
int main(){
    cin >> t;
    while(t--){
        cin >> n;
        l = 1,r = n; //边界初始化
        for(int i = 1;i <= n;i++) cin >> a[i] >> b[i];
        while(l < r){ //二分查找
            int mid = (l + r + 1) / 2;
            if(check(mid)) l = mid; //改变边界
            else r = mid - 1;
        }
        cout << r << "\n";
    }
    return 0; //好习惯
}
```
不抄题解，从我做起！

---

## 作者：让风忽悠你 (赞：2)

## 做法

题目中提到**最多**，自然就会想到二分答案，可是要怎么判断当前的答案是否符合条件呢？题目中提到第 $i$ 个朋友的财产为 $i$，可以发现他们的财产也具有单调性，也就意味着对于第 $i$ 个人来说，第  $1 \sim (i-1)$ 个人的财产必然小于他，第 $(i+1) \sim n$ 个人的财产必然大于他。假设总人数为 $N$，那么当选择了 $x$ 个人时，只需要考虑 $b_i$ 是否大于 $x$，$a_i$ 是否大于 $N-x-1$。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
#define N 200005

using namespace std;

int T,n,res;
int a[N],b[N];

bool check(int x){
	int tot=0;
	for(int i=1;i<=n;i++){
		if(a[i]>=x-tot-1 && b[i]>=tot) ++tot;
		if(tot>=x) return 1;
	} 
	return 0;
}

int main(){
	scanf("%d",&T);
	while(T--){
		res=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d%d",&a[i],&b[i]);
		int l=1,r=n,mid;
		while(l<=r){
			mid=(l+r)>>1;
			if(check(mid)) l=mid+1,res=mid;
			else r=mid-1;
		}
		printf("%d\n",res);
	}
	return 0;
}
```


---

## 作者：XL4453 (赞：1)

### 解题思路：

二分，然后贪心判断。

我是先想到贪心然后想到而二分的。

从钱数少的往钱数大的考虑，对于一个钱数不多的人，它的限制条件有一个已经可以通过之前已经取了的人数直接判断，问题就在如何判断这之前是否会有不允许这个人取的情况。

发现直接处理不好弄，考虑确定取的人数，然后按照上面的贪心思路判断。这里的单调性很显然，如果一个人数能取，那么放走几个人一定可行，所以二分求解。

---

上面那个贪心的具体过程是这样的：在已经确定人数的之后如果一个人能加入到列表里，就直接加入，注意这里有两个限制条件。

这个贪心的证明也很简单。

往队伍里加人会削弱最比这个人大的人的数量的限制要求，所以若存在一个当前可以取而不取的情况，将这一个人的下一个和这个人交换后，可能会在这两者之间存在某一个新的可以加入列表的人，且在后来的那一个人之后的所有的人看来，这两个人所能提供的价值是一样的。

即在答案不劣的前提下增加了可能的选择空间，使得可能成为潜在的更大答案。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int T,n,a[200005],b[200005],l,r,ans;
bool check(int num){
	int now=0;
	for(int i=1;i<=n;i++){
		if(b[i]<now)continue;
		if(a[i]>=num-now-1)now++;
	}
	if(now>=num)return 1;
	return 0;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i],&b[i]);
		l=1;r=n;ans=0;
		while(l<=r){
			int mid=l+r>>1;
			if(check(mid))ans=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：include_BM (赞：1)

题意：

从 $n$ 个人中选一些人，要求所选的人中编号 $<i$ 的不超过 $b_i$ 个，编号 $>i$ 的不超过 $a_i$ 个，求最多能选多少人。

设最终答案为 $k$，则所选人数 $\le k$ 均合法，$>k$ 均不合法，故可以二分所选人数。

```cpp
const int N=2e5+10;
int n,a[N],b[N],ans;
inline bool check(int x){
    int tot=0;//目前已经选了的人
    for(int i=1;i<=n;++i){
        if(b[i]>=tot&&a[i]>=x-tot-1) ++tot;//能选就选
        if(tot>=x) return true;
    }
    return false;
}
signed main(){
	for(int T=read();T;--T){
		n=read(),ans=1;
		for(int i=1;i<=n;++i) a[i]=read(),b[i]=read();
		for(int l=1,r=n,mid;l<r;){//二分所选人数
			mid=(l+r+1)>>1;
			if(check(mid)) ans=l=mid;
			else r=mid-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：ArrogHie (赞：1)

二分+贪心


------------

二分答案，贪心选择，若选的数能达到二分的答案则答案合法，按下标从小到大枚举每个数，枚举到 $i$ ，已经选了 $x$ 个数，二分的答案为 $mid$ ，如果 $b[i]>x$ 且 $a[i]>mid-x-1$ ，则把这个数也选上，最后判断 $x$ 是否大于等于 $mid$ 即可

### 证明
若当前枚举的数 $i$ 不满足 $a[i]>mid-x-1$ ，若选它则一定不能选满 $mid$ 个数。若当前的数不满足 $b[i]>x$ ，想要选它就必须把前面已经选择的数删掉，这样对于最后选的数来说，是没啥变化的，因为最后选的数之前一定有 $mid-1$ 个数，而且选了可能导致后面的数不够 $mid-1$ 个，所以直接不选这个数。

---

## 作者：SMall_X_ (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF1610C)


---
## 题目大意

有 $n$ 个人，第 $i$ 个人有 $i$ 元。

当且仅当宴会上的人中至多有 $a_i$ 人严格比 $i$ 富有，至多有 $b_i$ 人严格比 $i$ 贫困，$i$ 才会来。

现在求最多能邀请多少人。

## 思路分析

根据“**最多**能邀请的人数”这句话，不难想到二分答案。

再根据“第 $i$ 个人有 $i$ 元”，即第 $i$ 个人的钱比前 $i-1$ 个人富有，符合单调性。

二分答案最多能邀请的人数，循环判断是否能来。

该题解的时间复杂度是 $\mathcal{O(n\log n)}$。

代码：
```cpp
/*Written by smx*/
#include<bits/stdc++.h>
using namespace std;
int a[200005],b[200005];
int n;
bool check(int t){
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(a[i]>=t-cnt-1&&b[i]>=cnt){
			cnt++;
		}
	}
	return cnt>=t;
}
int erfen(int l,int r){
	int mid;
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid)){
			l=mid+1;
		}else{
			r=mid-1;
		}
	}
	return r;
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i]>>b[i];
		}
		cout<<erfen(1,n)<<"\n";
	}
	return 0;
}
```

---

## 作者：huangmingyi (赞：0)

#### 前言：这题是一道很好的二分答案题目，这题难度不大基础的二分答案就可以做到。
#### 思路
##### $20$ 分思路：
这题可以用去重全排列暴力枚举每个人参加或不参加用去重全排列来做。   
$20$ 分代码：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5; 
struct node{
	int money,rich,poor;
}a[N];
int T,cnt=0,maxn=-1e18,n;
bool v[N];
bool check(){
	for(int i=1;i<n;i++){
		if(v[i]){
			int cnt=0;
			for(int j=i+1;j<=n;j++){
				if(v[j]){
					cnt++;
				}
			}
			if(cnt>a[i].rich){
				return 0;
			}
		}
	}
	return 1;
}
void dfs(int x,int cnt){
	if(x>n){
	if(check()){
			maxn=max(maxn,cnt);
		}
		return ;
	}
	if(cnt<=a[x].poor){
		v[x]=true;
		dfs(x+1,cnt+1);
		v[x]=0;
	}
	dfs(x+1,cnt);
	return ;
}
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		maxn=-1e18;
		for(int i=1;i<=n;i++){
			cin>>a[i].rich>>a[i].poor;
			a[i].money=i;
		}
		dfs(1,0);
		cout<<maxn<<"\n";
	}
	return 0;
}
```

#### $100$ 分思路
##### 这题是可以二分的，二分邀请的人数（我们能邀请 $n$ 个人（$n$ 不是一）那一定能邀请 $n-1$ 个人）
1. 二分枚举最多的人数，如果某个人数可以把区间缩小，直到确定最多的邀请人数。
2. 可不可以邀请 $x$ 个人的设计，看第 $i$ 人前面邀请了多少个人，邀请之前的人比 $a_i$ 小继续，在看 $x-cnt-1$ 是不是小于等于 $b_i$。
3. 可以 $lt=mid$，否则 $rt=mid$，输出 $lt$。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5; 
struct node{
	int money,rich,poor;
}a[N];
int T,maxn=-1e18,n;
bool v[N];
bool check(int d){
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(cnt<=a[i].poor && d-cnt-1<=a[i].rich){
			cnt++;
		}
	}
	return cnt>=d;
}
int dfs(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].rich>>a[i].poor;
		a[i].money=i;
	}
	int lt=0,rt=n+1;
	while(lt+1<rt){
		int mid=(lt+rt)/2;
		if(check(mid)){
			lt=mid;
		}else{
			rt=mid;
		}
	}
	return lt;
}
signed main(){
	cin>>T;
	while(T--){
		cout<<dfs()<<"\n";
	}
	return 0;
}
```


---

