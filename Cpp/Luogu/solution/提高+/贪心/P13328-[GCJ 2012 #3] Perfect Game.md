# [GCJ 2012 #3] Perfect Game

## 题目描述

你正在玩一款电子游戏，如果能够连续通关所有关卡且中途没有死亡，你将获得一个成就。你可以以任意顺序游玩各个关卡，每次游玩某一关时，你要么通关，要么死亡。每一关都有一定的通关概率，并且每一关都需要一定的时间。不论你通关还是死亡，所用时间都相同。你应该以怎样的顺序游玩关卡，才能使获得成就所需的期望时间最小？假设每当你死亡后，会立刻从你设定的顺序的第一关重新开始。

**注意**：如果你未能通关某一关，你本人并不会真的死亡——只是游戏角色死亡而已。如果不是这样，恐怕只有极少数人会尝试获得这个成就。


## 说明/提示

**样例说明**

请注意，第二组和第三组样例并不满足小数据的约束条件。

**限制条件**

$1 \leq T \leq 100$。

$0 \leq P_i < 100$。

**测试集 1（3 分，结果可见）**

- $1 \leq N \leq 20$。
- $L_i = 1$。

**测试集 2（7 分，结果隐藏）**

- $1 \leq N \leq 1000$。
- $1 \leq L_i \leq 100$。

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
3
4
1 1 1 1
50 0 20 20
3
100 10 1
0 50 0
3
100 80 50
40 20 80```

### 输出

```
Case #1: 0 2 3 1
Case #2: 1 0 2
Case #3: 2 0 1```

# 题解

## 作者：FS_NEO (赞：2)

看完题，感觉是贪心。

-----------

若关卡数量为 $1$，解方程得期望时间 $T=\frac{L_i}{1-P_i}$

若关卡数量大于 $1$，由于期望的线性性，期望时间 $T=\large \frac{\frac{L_n}{1-P_n}+L_{n-1}}{1-P_{n-1}} \dots$（这个分式还有很多层，省略不写了。）

展开得 $T=\large \frac{\sum_{i=1}^{n} L_i \prod_{j=1}^{i-1} 1-P_j}{\prod_{i=1}^{n} 1-Pi}$

这个式子很可以贪心，于是使用临项交换法，得出将关卡按 $\frac{P_i}{L_i}$ 从大到小排序结果最优。

Code:


```cpp
/*

		2025.7.22
		
  * Happy Zenith Noises *
   
*/
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef pair<int,int>P;
const int MAXN=2005,mod=998244353;
int T,n;
struct node{
	int t,p,id;
}a[MAXN];
bool cmp(node x,node y){
	if(x.p*y.t!=x.t*y.p)return x.p*y.t>x.t*y.p;
	return x.id<y.id;
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].t;
	for(int i=1;i<=n;i++)cin>>a[i].p,a[i].id=i;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)cout<<a[i].id-1<<" ";
	cout<<"\n";
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>T;
	for(int i=1;i<=T;i++){
		cout<<"Case #"<<i<<": ";
		solve();
	}
	return 0;
}
```

---

