# Fountains

## 题目描述

Arkady想要建 $2$ 座喷泉，他有 $n$ 座可以选的喷泉，$c$ 个金币和 $d$个钻石， 每座喷泉可且仅可用金币或钻石一种货币来买，金币和钻石也不能以任何方式转化。现在要使两座喷泉美丽值总和最大且Arkady能买得起，求出最大美丽值。

## 样例 #1

### 输入

```
3 7 6
10 8 C
4 3 C
5 6 D
```

### 输出

```
9
```

## 样例 #2

### 输入

```
2 4 5
2 5 C
2 1 D
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3 10 10
5 5 C
5 5 C
10 11 D
```

### 输出

```
10
```

# 题解

## 作者：Limury (赞：4)

### 题意

有 $n$ 座喷泉，每座喷泉有一魅力值，可用金币或钻石一种货币来买，从喷泉中选 $2$ 座喷泉，使两座喷泉美丽值总和最大且买得起。

### 思路

看完题，我们可以轻松想到暴力做法，也就是两重循环枚举每一点并更新答案，但是很明显时间复杂度为 $O(n^2)$，是要超时的。

考虑优化一重循环，也就是 $O(n)$ 或者 $O(n\log_2n)$ 算法，这时就可以使用树状数组，以喷泉的金币或钻石数为下标，美丽度为权值建树状数组，然后就相当于每次剩余的钱中间，找到一个最大值，更新答案。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=100005;
int n,c,d,cnt1,cnt2,k[maxn];
int ans1=-1,ans2=-1;

struct node{
	int cnt,p;
}a1[maxn],a2[maxn];

int LowBit(int x){
	return x&-x;
}

void UpDate(int x,int y,int val){
	while(x<y){
		k[x]=max(k[x],val);
		x+=LowBit(x);
	}
}

int Sum(int x){
	int ans=0;
	while(x>0){
		ans=max(ans,k[x]);
		x-=LowBit(x);
	}
	return ans;
}

int main(){
	scanf("%d%d%d",&n,&c,&d);
	for(int i=0;i<n;i++){
		int b,p;
		char s;
		scanf("%d%d %c",&b,&p,&s);
		if(s=='C'){
			if(p<=c){
				a1[cnt1].cnt=b;
				a1[cnt1++].p=p;
				ans1=max(ans1,b);
			}
		}
		else{
			if(p<=d){
				a2[cnt2].cnt=b;
				a2[cnt2++].p=p;
				ans2=max(ans2,b);
			}
		}
	}
	int ans=0;
	if(ans1!=-1&&ans2!=-1){
		ans=ans1+ans2;
	}
	memset(k,0,sizeof(k));
	for(int i=0;i<cnt1;i++){
		int tot=Sum(c-a1[i].p);
		if(tot>0){
			ans=max(ans,tot+a1[i].cnt);
		}
		UpDate(a1[i].p,maxn,a1[i].cnt);
	}
	memset(k,0,sizeof(k)); 
	for(int i=0;i<cnt2;i++){
		int tot=Sum(d-a2[i].p);
		if(tot>0){
			ans=max(ans,tot+a2[i].cnt);
		}
		UpDate(a2[i].p,maxn,a2[i].cnt);
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：xzggzh1 (赞：2)

题意：

$n$ 个物品，每个都有价值和美观值，每种商品只能被金币和钻石其中之一购买。

你有 $x$ 个金币和 $y$ 个钻石，买两个物品做多可以有多少美观值。

---

题目拿到手直接分类讨论：把花金币的物品分为一类，把花钻石的物品分为一类，就有以下两种情况。

1. 两个物品不属于同一类。

1. 两个物品属于同一类。

情况 1 直接贪心取每类能买到的最大值即可，我们直接考虑情况 2 。

枚举先买那个物品，可以算出剩下货币的数量。然后找到剩下货币能买的物品里面美观最大的。

如何快速找：直接按照花费排序，然后建一个线段树维护区间最大美观度即可。

----

核心代码：（线段树部分略去）

```cpp
const int mac=1e5+10;
const int ends=1e5;
struct node
{
    int val,cost,tp;
    bool operator <(const node&a)const{
        return val>a.val;
    }
}a1[mac],a2[mac];
int main()
{
    int n,c,d;
    scanf ("%d%d%d",&n,&c,&d);
    char s[5];
    int cnt1=0,cnt2=0;
    for (int i=1; i<=n; i++){
        int x,y;
        scanf ("%d%d%s",&x,&y,s);
        if (s[0]=='C') a1[++cnt1]=node{x,y,0};
        else a2[++cnt2]=node{x,y,1};
    }
    sort(a1+1,a1+1+cnt1);
    sort(a2+1,a2+1+cnt2);
    int mk1,mk2,mk3,ans1,ans2,ans3;
    mk1=mk2=mk3=ans1=ans2=ans3=0;
    for (int i=1; i<=cnt1; i++) if (a1[i].cost<=c) {ans1+=a1[i].val;mk1++;break;}
    for (int i=1; i<=cnt2; i++) if (a2[i].cost<=d) {ans1+=a2[i].val;mk1++;break;}
    if (mk1<2) ans1=0;
    for (int i=1; i<=cnt1; i++){
        int mx=a1[i].val;
        if (c<=a1[i].cost) continue;
        int p=query(1,ends,1,1,c-a1[i].cost,0);
        update(1,ends,1,a1[i].cost,a1[i].val,0);
        if (!p) continue;
        else ans2=max(ans2,mx+p);
    }
    //下面的操作同上 
	for (int i=1; i<=cnt2; i++){int mx=a2[i].val;if (d<=a2[i].cost) continue;int p=query(1,ends,1,1,d-a2[i].cost,1);update(1,ends,1,a2[i].cost,a2[i].val,1);if (!p) continue;else ans3=max(ans3,mx+p);}
	printf("%d\n",max(ans1,max(ans2,ans3)));
}
```

---

## 作者：water_three (赞：1)

### 前置知识：

[二分](https://www.luogu.com.cn/problem/P2249)和分类讨论。

### 思路：

首先这道题目映入眼帘的必定是 $2$ 座喷泉，那么答案必定是下面三种中最优的:

1. 用金币买两座喷泉

1. 用钻石买两座喷泉

1. 用金币和钻石各买一座喷泉

对于第三种情况，直接取最优即可。

因为只用买 $2$ 座，所以我们考虑循环固定买一座，在剩下之中找最大价值的。

### 实现：

~~貌似写复杂了~~

首先将金币和钻石分开，在内部按照费用大小排序，记录下区间的最大值。然后二分查找，取最大价值。

```cpp
for(int i=1;i<=tot;i++){
        int ppp=c-a[i].p;
        int left=1,right=tot,res=-1;
        while(left<=right){
            int mid=(left+right)/2;
            if(a[mid].p<=ppp){
                res=mid;
                left=mid+1;
            }
            else{
                right=mid-1;
            }
        }
        if(res==i)res--;
        if(res==-1||res==0){
            continue;
        }
        else{
            if(a[i].b!=MAXX[res])
            ans=max(ans,a[i].b+MAXX[res]);
            else
            ans=max(ans,a[i].b+seMAXX[res]);
        }
    }
```

**但是这里会出现一个问题，就是不能造相同的两个喷泉，所以我们要记录次大值 $seMAX$。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c,d;
struct shu{
    long long b,p;
    char s;
}a[100221];
long long MAXX[100001],maxx[100001],seMAXX[100001],semaxx[100001];
long long ans=0;
int tot=0;
bool cmp(shu a,shu b){
    if(a.s!=b.s)return a.s<b.s;
    return a.p<b.p;
}
int main(){
    cin>>n>>c>>d;
    int pan1=0,pan2=0;
    for(int i=1;i<=n;i++){
        cin>>a[i].b>>a[i].p>>a[i].s;
        if(a[i].s=='C')tot++;
        if(a[i].s=='C'&&a[i].p<=c)pan1++;
        if(a[i].s=='D'&&a[i].p<=d)pan2++;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=tot;i++){
        if(MAXX[i-1]<a[i].b)seMAXX[i]=MAXX[i-1],MAXX[i]=a[i].b;
        else if(a[i].b>seMAXX[i-1])seMAXX[i]=a[i].b,MAXX[i]=MAXX[i-1];
        else seMAXX[i]=seMAXX[i-1],MAXX[i]=MAXX[i-1];
    }
    for(int i=tot+1;i<=n;i++){
        if(maxx[i-1]<a[i].b)semaxx[i]=maxx[i-1],maxx[i]=max(maxx[i-1],a[i].b);
		else if(a[i].b>semaxx[i-1])semaxx[i]=a[i].b,maxx[i]=maxx[i-1];
		else semaxx[i]=semaxx[i-1],maxx[i]=maxx[i-1];
    }
    if(pan1>=1)
    for(int i=1;i<=tot;i++){
        int ppp=c-a[i].p;
        int left=1,right=tot,res=-1;
        while(left<=right){
            int mid=(left+right)/2;
            if(a[mid].p<=ppp){
                res=mid;
                left=mid+1;
            }
            else{
                right=mid-1;
            }
        }
        if(res==i)res--;
        if(res==-1||res==0){
            continue;
        }
        else{
        	if(a[i].b!=MAXX[res])
            ans=max(ans,a[i].b+MAXX[res]);
            else
            ans=max(ans,a[i].b+seMAXX[res]);
        }
    }
    if(pan2>=1)
    for(int i=tot+1;i<=n;i++){
		int ppp=d-a[i].p;
		int left=tot+1,right=n,res=-1;
		while(left<=right){
		    int mid=(left+right)/2;
		    if(a[mid].p<=ppp){
		        res=mid;
		        left=mid+1;
		    }
		    else{
		        right=mid-1;
		    }
		}
		if(res==i)res--;
		if(res==-1||res==tot){
		    continue;
		}
		else{
		    if(a[i].b!=maxx[res])
			ans=max(ans,a[i].b+maxx[res]);
			else
			ans=max(ans,a[i].b+semaxx[res]);
		}
	}
	if(pan1>=1&&pan2>=1){
	long long h1=0,h2=0;
	for(int i=1;i<=tot;i++){
		if(a[i].p<=c)h1=max(h1,a[i].b);
		else break;
	}
	for(int i=tot+1;i<=n;i++){
		if(a[i].p<=d)h2=max(h2,a[i].b);
		else break;
	}
	ans=max(ans,h1+h2);
	}
	cout<<ans<<endl;
}
```


---

## 作者：staygone (赞：1)


考虑建了一个 'C' 一个 'D' 的情况答案就是 'C' , 'D' 中取满足 $cost$ 的最大值即可 'C' , 'C' 的情况，按 $cost$ 升序排序，维护 $sc_{i} =  cost \le i$ 的情况下,收益最大的值。

枚举每对 ${bi, pi}$ 并依次插入即可 'C' , 'C' 的最大值就算 $sc_{min(c-i,i)}$ 加上当前收益, 'D', 'D' 同理。

```cpp
#include<stdio.h>
#include <iostream>
#include<stdlib.h>
#include<algorithm>
#include<vector>
#include<deque>
#include<map>
#include<set>
#include<queue>
#include<math.h>
#include<string.h>
#include<string>

using namespace std;
#define ll long long
#define pii pair<int,int>

const int inf = 1e9 + 7;

const int N = 1e5+5;

vector<pii>cf,df;
int sc[N];
int sd[N];

int slove(int n,int c,int d){
    sort(cf.begin(),cf.end());
    sort(df.begin(),df.end());
    int cc=-inf;
    int lastIdx=0;
    for(int i=0;i<cf.size();++i){
        int cost=cf[i].first;
        int score=cf[i].second;
        for(int j=lastIdx+1;j<=cost;++j){
            sc[j]=max(sc[j],sc[j-1]);
        }
        int x=min(c-cost,cost);
        if(x>=0){
            cc=max(cc,sc[x]+score);
        }
        sc[cost]=max(sc[cost],score);
        lastIdx=cost;
    }
    for(int i=lastIdx+1;i<=c;++i){
        sc[i]=max(sc[i],sc[i-1]);
    }
    int dd=-inf;
    lastIdx=0;
    for(int i=0;i<df.size();++i){
        int cost=df[i].first;
        int score=df[i].second;
        for(int j=lastIdx+1;j<=cost;++j){
            sd[j]=max(sd[j],sd[j-1]);
        }
        int x=min(d-cost,cost);
        if(x>=0){
            dd=max(dd,sd[x]+score);
        }
        sd[cost]=max(sd[cost],score);
        lastIdx=cost;
    }
    for(int i=lastIdx+1;i<=d;++i){
        sd[i]=max(sd[i],sd[i-1]);
    }
    int cd=sc[c]+sd[d];
    return max(cc,max(dd,max(0,cd)));
}

int main()
{
    //freopen("/home/lu/Documents/r.txt","r",stdin);
    //freopen("/home/lu/Documents/w.txt","w",stdout);
    int n,c,d;
    while(~scanf("%d%d%d",&n,&c,&d)){
        fill(sc,sc+c+1,-inf);
        fill(sd,sd+d+1,-inf);
        cf.clear();
        df.clear();
        int score,cost;
        char ch;
        for(int i=0;i<n;++i){
            scanf("%d%d%*c%c",&score,&cost,&ch);
            if(ch=='C'){
                cf.push_back({cost,score});
            }
            else{
                df.push_back({cost,score});
            }
        }
        printf("%d\n",slove(n,c,d));
    }
    return 0;
}
```
感谢观看

---

## 作者：Zhao_daodao (赞：0)

# CF799C Fountains

## Description

有 $n$ 座喷泉，每一座喷泉可以用一定数量的金币或者钻石购买。

每一个喷泉有一个**美观度**，你手中有 $c$ 个金币和 $d$ 个钻石。

需要**恰好购买两座喷泉**，求购买的所有方案中美观度的最大值。

## Solution

不需要树状数组，复杂度 $O(n\log n)$，瓶颈在排序。

发现只用买两座喷泉，所以分类讨论。

如果购买一个金币喷泉，一个钻石喷泉，是简单的，直接取能买的最大值。

或者就是两个金币喷泉，或者两个钻石喷泉，两种情况类似，以金币喷泉为例。

设喷泉的属性为 $price$ 和 $beauty$。

则将每一个喷泉按照 $price$ 从大到小排序。

从前到后枚举每一个喷泉，发现另一个能够去到的喷泉一定是一个**后缀区间**。

但是发现喷泉不能重复，所以当前喷泉被包括在后缀区间的时候，不能够取到。

所以使用双指针的算法，记录后缀最大值和次大值即可。

## Code

```cpp
#include<bits/stdc++.h>
#define Pair pair<int,int>
using namespace std;
const int inf=1e9;
const int MAXN=1e5+5;
int n,c,d,ans;
Pair gold[MAXN],dimond[MAXN];
int tp1,tp2;
inline void refresh(int& mx1,int& mx2,int k){
    if(mx1<k){mx1=k;}
    else if(mx2<k){mx2=k;}
}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin>>n>>c>>d;
    for(int i=1;i<=n;i++){
        Pair now;
        cin>>now.first>>now.second;
        char k;cin>>k;
        if(k=='C'&&now.second<=c)gold[++tp1]=now;
        if(k=='D'&&now.second<=d)dimond[++tp2]=now;
    }
    int mx1=-inf,mx2=-inf;
    for(int i=1;i<=tp1;i++)mx1=max(mx1,gold[i].first);
    for(int i=1;i<=tp2;i++)mx2=max(mx2,dimond[i].first);
    ans=max(ans,mx1+mx2);
    sort(gold+1,gold+tp1+1,[](Pair a,Pair b){return a.second>b.second;});
    int now=tp1+1;
    mx1=-inf,mx2=-inf;
    for(int i=1;i<=tp1;i++){
        while(now-1>=1&&gold[i].second+gold[now-1].second<=c){
            refresh(mx1,mx2,gold[now-1].first);
            now--;
        }
        if(mx1!=gold[i].first)ans=max(ans,mx1+gold[i].first);
        else ans=max(ans,mx2+gold[i].first);
    }
    sort(dimond+1,dimond+tp2+1,[](Pair a,Pair b){return a.second>b.second;});
    now=tp2+1;
    mx1=-inf,mx2=-inf;
    for(int i=1;i<=tp2;i++){
        while(now-1>=1&&dimond[i].second+dimond[now-1].second<=d){
            refresh(mx1,mx2,dimond[now-1].first);
            now--;
        }
        if(mx1!=dimond[i].first)ans=max(ans,mx1+dimond[i].first);
        else ans=max(ans,mx2+dimond[i].first);
    }
    cout<<ans<<"\n";
}
```

---

## 作者：封禁用户 (赞：0)

不难想到贪心和暴力：因为只买 $2$ 座喷泉，所以有三种情况：

1. 两座喷泉都用金币买。

2. 两座喷泉都用钻石买。

3. 一座喷泉用金币买，另一座喷泉用钻石买。

所以只需要用两重循环枚举每一点并更新答案即可。时间复杂度 $O(n^2)$。显然超时。

观察数据范围可知，时间复杂度 $O(n\log^2n)$ 就可以过，所以考虑用树状数组维护喷泉的美丽值。即以喷泉的金币或钻石数为下标，美丽度为权值建树状数组，在剩余的钱中贪心，取得美丽值最大的两座喷泉。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c,d,ans1=-1,ans2=-1,x,x2,tree[100005];
struct node{
	int v,p;
}a1[100005],a2[100005];
int lowbit(int x){
	return x&-x;
}
void update(int x,int y,int k){
	while(x<=y){
		tree[x]=max(tree[x],k);
		x+=lowbit(x);
	}
}
int prefix(int x){
	int ans=0;
	while(x>0){
		ans=max(ans,tree[x]);
		x-=lowbit(x);
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>c>>d;
	for(int i=0;i<n;i++){
		int b,p;
		char s;
		cin>>b>>p>>s;
		if(s=='C'){
			if(p<=c){
				a1[x].v=b;
				a1[x++].p=p;
				ans1=max(ans1,b);
			}
		}
		else{
			if(p<=d){
				a2[x2].v=b;
				a2[x2++].p=p;
				ans2=max(ans2,b);
			}
		}
	}
	int ans=0;
	if(ans1!=-1&&ans2!=-1)ans=ans1+ans2;
	memset(tree,0,sizeof tree);
	for(int i=0;i<x;i++){
		int tot=prefix(c-a1[i].p);
		if(tot>0){
			ans=max(ans,tot+a1[i].v);
		}
		update(a1[i].p,100005,a1[i].v);
	}
	memset(tree,0,sizeof tree); 
	for(int i=0;i<x2;i++){
		int tot=prefix(d-a2[i].p);
		if(tot>0)ans=max(ans,tot+a2[i].v);
		update(a2[i].p,100005,a2[i].v);
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：cqbzhzf (赞：0)

[博客链接](https://www.luogu.com.cn/article/yvwi1rgh)

[洛谷链接](https://www.luogu.com.cn/problem/CF799C)
### 前置知识
[树状数组](https://blog.csdn.net/weq2011/article/details/128835460)
### 思路分析
读完题目很容易想到通过 $2$ 重循环暴力枚举每 $1$ 座喷泉并统计最大值。

从时间复杂度分析，$2\le n\le 100000$，$O(n^2)$ 的暴力明显不理想，考虑优化 $1$ 重循环，变成 $O(n \log_2n)$ 或 $O(n)$ 的时间复杂度。

我们再次思考，题目求最大的美丽度，所以我们可以以美丽度为权值，价格为下标建立树状数组，把时间复杂度优化为 $O(n \log_2n)$。

另外，两个最大值的选择有 $3$ 种：选 $2$ 座用金币买的，选 $2$ 座用钻石买的或者是用金币、钻石买的各 $1$ 座。先预处理出第 $1$、$2$ 种情况，再用树状数组计算第 $3$ 种，最后取 $\max$ 即可。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long//以防爆炸
using namespace std;
const int N=1e5+5;
int n,c,d,tot1,tot2,bit[N],ans,ans1=INT_MIN,ans2=INT_MIN;
struct node
{
	int tot,m;
}a1[N],a2[N];
int lowbit(int x)
{
	return x&(-x);
}
void update(int k,int x)
{
	while(k<N)
	{
		bit[k]=max(bit[k],x);
		k+=lowbit(k);
	}
}
int sum(int k)
{
	int t=0;
	while(k>0)
	{
		t=max(t,bit[k]);
		k-=lowbit(k);
	}
	return t;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>c>>d;
	while(n--)
	{
		int b,money;
		char opt;
		cin>>b>>money>>opt;
		if(opt=='C')
		{
			if(money<=c)
			{
				a1[++tot1].tot=b;
				a1[tot1].m=money;
				ans1=max(ans1,b);
			}
		}
		else
		{
			if(money<=d)
			{
				a2[++tot2].tot=b;
				a2[tot2].m=money;
				ans2=max(ans2,b);//输入时预处理
			}
		}
	}
	if(ans1!=INT_MIN&&ans2!=INT_MIN)
		ans=ans1+ans2;
	memset(bit,0,sizeof(bit));
	for(int i=1;i<=tot1;i++)
	{
		int s=sum(c-a1[i].m);
		if(s>0)
			ans=max(ans,s+a1[i].tot);
		update(a1[i].m,a1[i].tot);
	}
	memset(bit,0,sizeof(bit));
	for(int i=1;i<=tot2;i++)
	{
		int s=sum(d-a2[i].m);
		if(s>0)
			ans=max(ans,s+a2[i].tot);//统计答案
		update(a2[i].m,a2[i].tot);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：cqbzrjx (赞：0)

[原题传送门](https://codeforces.com/problemset/problem/799/C)

# 题意

有 $n$ 个物品，每个物品有一定的的美丽度 $b_i$。初始时有 $c$ 个金币和 $d$ 个钻石可用于购买。

接下来 $n$ 行，每行给出两个数字 $b_i$ 和 $p_i$ 和一个字母 $C$ 或者 $D$，表示第 $i$ 个喷泉的美丽度。

现在需要**恰好**购买两个喷泉，并且一座喷泉只能使用一种货币购买，求这两个喷泉美丽度之和的最大值。

# 分析

此题很容易想到的是**贪心和暴力**，但是时间复杂度是 $O(n^2)$，显然是会超时的。

对此，我们其实可以想到购买的两种情况：两种货币皆用或者只使用一种货币。

首先先想第一种，两种货币皆用，**贪心**地选择两种货币分别可以购买到的喷泉的 $\max$ 美丽度即可。

其次想一下第二种，可以先**枚举假设**买其中一个喷泉，再次转过来想一下，其实是可以使用**树状数组**进行维护美丽度，并在每次进行比较取 $\max$ 利润。

最后，给出两种情况的 $\max$ 即可。

# AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 1e5 + 5;
char s;
ll n,x,y,ans,c,d;
ll cnt[maxn],b[2][maxn],p[2][maxn],tot[2],res[2];
inline ll lowbit(ll x)
{
	return x & -x;
}
inline void update(ll x,ll v)
{
	while(x < maxn)
	{
		cnt[x] = max(cnt[x],v);
		x += lowbit(x);
	}
}
inline ll query(ll x)
{
	ll fx = 0;
	while(x)
	{
		fx = max(fx,cnt[x]);
		x -= lowbit(x);
	}
	return fx;
}
signed main()
{
//	freopen("b.in","r",stdin);
//	freopen("b.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>c>>d;
	for(ll i = 1;i <= n;i++)
	{
		cin>>x>>y>>s;
		if(s == 'C')
		{
			if(y <= c)
			{
				b[0][++tot[0]] = x;
				p[0][tot[0]] = y;	
			}
		}
		else
		{
			if(y <= d)
			{
				b[1][++tot[1]] = x;
				p[1][tot[1]] = y;
			}
		}
	}
	for(ll i = 0;i <= 1;i++)
	{
		for(ll j = 1;j <= tot[i];j++)
		{
			res[i] = max(res[i],b[i][j]);
		}
	}
	if(res[0] && res[1]) ans = res[0] + res[1];
	for(ll i = 0;i <= 1;i++)
	{
		for(ll j = 1;j <= tot[i];j++)
		{
			ll op;
			if(i == 0) op = query(c - p[i][j]);
			if(i == 1) op = query(d - p[i][j]);
			if(op) ans = max(ans,b[i][j] + op);
			update(p[i][j],b[i][j]);
		}
		memset(cnt,0,sizeof cnt);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：gyyyyx (赞：0)

[题面](https://www.luogu.com.cn/problem/CF799C)

这 nm 是蓝？

分类讨论一下。

第一种情况是两种货币都使用。

则选择两种货币分别可以购买到的美丽值最大的喷泉即可。

第二种情况是只使用一种货币。

可以先枚举买其中一个喷泉，然后用树状数组维护剩下的钱可以买到的美丽值最大的喷泉，加起来取个最大值就行。

最后两种情况取最优就行。

代码：

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,ct[2];
int b[2][N],p[2][N],tot[2];
int res[2],ans;
int c[N];
inline int lowbit(int x){return x&-x;}
inline void Update(int x,int v){
	while(x<N){
		c[x]=max(c[x],v);
		x+=lowbit(x);
	}
}
inline int Query(int x){
	int mx(0);
	while(x){
		mx=max(mx,c[x]);
		x-=lowbit(x);
	}
	return mx;
}
int main(){
	scanf("%d%d%d",&n,&ct[0],&ct[1]);
	for(int i(1);i<=n;++i){
		int x,y;char c;scanf("%d%d %c",&x,&y,&c);
		if(c=='C'){if(y<=ct[0]) b[0][++tot[0]]=x,p[0][tot[0]]=y;}
		else{if(y<=ct[1]) b[1][++tot[1]]=x,p[1][tot[1]]=y;}
	}
	for(int j(0);j<=1;++j)
		for(int i(1);i<=tot[j];++i)
			res[j]=max(res[j],b[j][i]);
	if(res[0]&&res[1]) ans=res[0]+res[1];
	for(int j(0);j<=1;++j){
		for(int i(1);i<=tot[j];++i){
			int mx(Query(ct[j]-p[j][i]));
			if(mx){ans=max(ans,b[j][i]+mx);}
			Update(p[j][i],b[j][i]);
		}
		memset(c,0,sizeof(c));
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Disjoint_cat (赞：0)

# [CF799C](https://www.luogu.com.cn/problem/CF799C)

## 题意

有 $n$ 个物品，每个物品有其自己的美丽度 $b_i$。

有两种货币 C 和 D，初始时你有 $C$ 个 C 货币和 $D$ 个 D 货币。

每个物品可以使用 $p_i$ 个 $t_i$ 货币来购买。

现在你需要购买**恰好**两个物品，求这两个物品美丽度之和的最大值，或报告无解。

数据范围：$n,C,D,p_i,b_i\le10^5$，$t_i\in\{\texttt{C},\texttt{D}\}$。

## 题解

以下称用 C 货币买的物品「C 种类物品」，D 货币买的同理。

分成三种情况：

- 一个 C 种类的，一个 D 种类的。

那么这两个物品互相独立，直接分别取一个美丽度最大且买得起的即可。

- 两个 C 种类的。

那么可以**从大到小**枚举**费用较大的**物品，然后用双指针维护能买的起的物品的左端点即可。

具体地，由于枚举的物品费用逐渐减小，那么留给第二个物品的钱会增加。则扫描并维护用剩下的钱买得起的物品的最大美丽度的物品即可。

注意实现细节，特别地，**不能购买相同的两个物品**。

- 两个 D 种类的。

同上。

---

于是这道题做完了。时间复杂度 $\Theta(n\log n)$，瓶颈在于排序。

## Code

```cpp
int n,C,D;
vector<PII>c,d;//pair<price,beauty>
VI cm,dm;
void Solve(int CASE)
{
	cin>>n>>C>>D;
	for(int i=1;i<=n;i++)
	{
		int p,b;char ch;
		cin>>b>>p>>ch;
		if(ch=='C')c.PB(p,b);
		else d.PB(p,b);
	}
	sort(ALL(c));
	sort(ALL(d));
	for(PII i:c)cm.PB(max(cm.empty()?0:cm.back(),i.se));
	for(PII i:d)dm.PB(max(dm.empty()?0:dm.back(),i.se));
	int ans=0;
	for(int i=(int)c.size()-1,j=0;i>0;i--)
	{
		while(j<c.size()&&c[j].fi+c[i].fi<=C)j++;
		if(j)ans=max(ans,cm[min(i,j)-1]+c[i].se);
	}
	for(int i=(int)d.size()-1,j=0;i>0;i--)
	{
		while(j<d.size()&&d[j].fi+d[i].fi<=D)j++;
		if(j)ans=max(ans,dm[min(i,j)-1]+d[i].se);
	}
	c.erase(upper_bound(ALL(c),MP(C+1,0)),c.end());
	d.erase(upper_bound(ALL(d),MP(D+1,0)),d.end());
	int mxc=0,mxd=0;
	for(PII i:c)mxc=max(mxc,i.se);
	for(PII i:d)mxd=max(mxd,i.se);
	if(mxc&&mxd)ans=max(ans,mxc+mxd);
	cout<<ans;
}
```

---

