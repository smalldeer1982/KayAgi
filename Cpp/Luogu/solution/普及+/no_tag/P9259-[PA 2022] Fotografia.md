# [PA 2022] Fotografia

## 题目描述

**题目译自 [PA 2022](https://sio2.mimuw.edu.pl/c/pa-2022-1/dashboard/) Runda 3 [Fotografia](https://sio2.mimuw.edu.pl/c/pa-2022-1/p/fot/)**

字节科技学校（*Bajtockiej Szkoły Technicznej*, BST）的毕业生们聚集在学校前面的广场上拍摄纪念照。他们排成一排，其位置从左到右编号为 $1$ 至 $n$，其中 $n$ 是今年毕业生的人数。

摄影师决定重新安排这些人的位置，让他们按身高升序排列。最矮的人在最左边，最高的人在最右边。幸运的是，今年的毕业生中没有任意两人身高相同。

为了避免混乱，安排位置将按一定方式进行。在一次操作中，摄影师将喊出一串位置编号。在这些位置上的人将按所喊到的顺序出列并走到广场中间。然后，摄影师将重复同样的数字列表。广场中间的人将他们出列顺序的**逆序**，依次回到摄影师所喊出的位置。

我们希望用尽可能少的操作将所有毕业生按身高的升序排列。你的工作是规划重新安排的方案，并告诉摄影师在第几次操作让哪些毕业生出列。

## 说明/提示

对于 $100\%$ 的数据，满足：

$1\le n\le 3 \times 10 ^ 3, 1\le h_i\le 3 \times 10 ^ 3, 1\le p_i\le n$。

## 样例 #1

### 输入

```
5
1670
2011
1560
1232
1447
```

### 输出

```
1
5
2 1 3 4 5
```

## 样例 #2

### 输入

```
6
1556
1449
1863
2014
1333
1220
```

### 输出

```
2
5
5 6 1 4 3
4
1 2 3 4
```

# 题解

## 作者：dutianchen1 (赞：1)

# [PA 2022] Fotografia

### 题意概括

给一个序列 $a$。有无数次操作，每次操作可以选取 $p_{1},p_{2},\dots p_{n}$，让 $a_{p_{i}} \gets a_{p_{n-i+1}}$。我们要让原序列升序排列，求最少操作次数。

### 思路简析

对题意分析，我们可以知道：对序列排序后，整个序列其实是由一个个环组成，每个环都是由要相互交换的元素组成，而我们的目的就是让原序列形成一个个自环。

用样例 $1$ 说明一下：

原序列（转化为序号后）：$4,5,3,1,2$，我们的目标：$1,2,3,4,5$。

这个样例中 $1$ 和 $4$ 形成了一个环，$2$ 和 $5$ 形成了一个环。

而我们每次的操作本质就是破环或合并环。

贪心考虑，我们不会合并环，于是考虑如何拆环最优。

显然，当环由两个元素组成时，直接拆分便可。

当环长 $\ge 3$ 时，我们可以发现，一次操作必然能把一个大环拆成若干个环长 $\le2$，再进行一次操作就可以把所有环长为 $2$ 的环都拆分成自环。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6+5;
inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return x*f;
}
struct node{
	ll val,id;
}num[N];
bool cmp(node a,node b){
	return a.val<b.val;
}
ll opt[N];
ll n,top;
bool vis[N];
ll c[N];//记录环 
vector<vector<ll>> ans;
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		num[i].val=read();num[i].id=i;
	}
	sort(num+1,num+1+n,cmp);
	for(int i=1;i<=n;i++)opt[num[i].id]=i;//记录环 
	while(true){
		vector<ll> a,b;
		memset(vis,false,sizeof(vis));
		for(int i=1;i<=n;i++){//跑环 
			if(vis[i])continue;
			top=0;
			ll x=i;
			while(!vis[x]){
				c[++top]=x;
				vis[x]=true;
				x=opt[x];
			} 
			ll l=1,r=top;
			while(l<r){
				swap(opt[c[l]],opt[c[r]]);
				a.push_back(c[l]);
				b.push_back(c[r]);
				l++;r--;
			}
		}
		reverse(a.begin(),a.end());
		a.insert(a.end(),b.begin(),b.end());
		if(a.empty())break;
		ans.push_back(a);
	} 
	cout<<ans.size()<<'\n';
	for(int i=0;i<ans.size();i++){
		cout<<ans[i].size()<<'\n';
		for(int j=0;j<ans[i].size();j++){
			cout<<ans[i][j]<<' ';
		}cout<<'\n';
	}
    return 0;  
}
```

---

