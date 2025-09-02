# [ABC146F] Sugoroku

## 题目描述

ABC146F 双六


高桥君在玩双六棋，棋盘格由用$0$到$N$编号的共$N+1$个格子构成。每一回合，高桥君会扔一个点数$1$到$M$的骰子。如果高桥君当前在第$i$格，骰子扔出$k$点，高桥君就前进到第$i+k$格。 如果此时$i+k > N$，高桥君立刻输掉。另外，棋盘上还有若干个“GameOver格”，如果高桥停在这些格子，也立刻输掉游戏。

假设高桥君可以自由控制骰子的点数，那么他从$0$号格子出发，到达$N$号格子，最短需要多少回合？输出用最短回合到达$N$格时，每回合骰子的点数组成的序列；如果无法到达$N$号格子，输出-1。

## 说明/提示

按$1,3,2,3$的顺序扔出骰子的点数，高桥君会经过第$1,4,6$格最终到达第$9$格。

无法在$3$次以内到达第$9$格。$1,3,2,3$是所有$4$次到达第$9$格的点数序列中，字典序最小的。


$1 \le N \le 10^5$

$1 \le M \le 10^5$

$S$长度为$N+1$，只由字符'0'和'1'组成，保证$S_0=0$，$S_N=0$。

## 样例 #1

### 输入

```
9 3
0001000100```

### 输出

```
1 3 2 3```

## 样例 #2

### 输入

```
5 4
011110```

### 输出

```
-1```

## 样例 #3

### 输入

```
6 6
0101010```

### 输出

```
6```

# 题解

## 作者：zjc5 (赞：9)

[题目链接](https://www.luogu.com.cn/problem/AT_abc146_f)

**思路：**

如果这题只是要求最少的步数，应该怎么做？

很明显，可以用贪心。对于第 $i$ 个点，只要到达 $s_{i+1}...s_{i+m}$ 中最后一个 $0$ 的位置。

但是这种方法求出的字典序肯定是最大的，但题目要求的是字典序最小。那么就可以**倒序**枚举，使第 $i$ 个位置变成第 $n-i$ 个位置，字典序就是最小的了。

代码时间复杂度 $O(n)$。

```cpp
#include<stdio.h>
int n,m,t,p,i,ans[100010],tot;
char s[100010];
int main(){
	scanf("%d%d%s",&n,&m,s+1);
	n++;//这里把下标看成1~n+1
	t=p=n;
	for(i=n;i>m;){
		for(;p>=i-m;p--)
			if(s[p]=='0') t=p;
		if(t>=i){//无法再跳
			puts("-1");
			return 0;
		}
		ans[++tot]=i-t;
		i=t;
	}
	if(i>1) printf("%d ",i-1);//未到达，再跳一步
	for(int j=tot;j;j--)
		printf("%d ",ans[j]);
	return 0;
}
```

---

## 作者：ace_amuro (赞：2)

# 题目翻译

ABC146F 双六

【题目描述】

高桥君在玩双六棋，棋盘格由用 $0$ 到 $N$ 编号的共 $N+1$ 个格子构成。每一回合，高桥君会扔一个点数 $1$ 到 $M$ 的骰子。如果高桥君当前在第 $i$ 格，骰子扔出 $k$ 点，高桥君就前进到第 $i+k$ 格。 如果此时 $i+k > N$ ，高桥君立刻输掉。另外，棋盘上还有若干个“GameOver格”，如果高桥停在这些格子，也立刻输掉游戏。

假设高桥君可以自由控制骰子的点数，那么他从 $0$ 号格子出发，到达 $N$ 号格子，最短需要多少回合？输出用最短回合到达 $N$ 格时，每回合骰子的点数组成的序列；如果无法到达 $N$ 号格子，输出-1。

【输入格式】

第1行，两个正整数 $N,M$ 

第2行，一个长为 $N+1$ 的字符串 $S$ 。 $S_i=0$ 表示第 $i$ 格是一个普通格子； $S_i=1$ 表示第 $i$ 格是一个GameOver格。

【输出格式】

输出用最短回合到达 $N$ 格时，每回合骰子的点数组成的序列，若有多种序列回合数都是最短，输出其中字典序最小的。

如果无法到达 $N$ 号格子，输出-1。

【输入样例\#1】

```
9 3
0001000100
```

【输出样例\#1】

```
1 3 2 3
```

【样例\#1说明】

按 $1,3,2,3$ 的顺序扔出骰子的点数，高桥君会经过第 $1,4,6$ 格最终到达第 $9$ 格。

无法在 $3$ 次以内到达第 $9$ 格。 $1,3,2,3$ 是所有 $4$ 次到达第 $9$ 格的点数序列中，字典序最小的。

【数据说明】

 $1 \le N \le 10^5$ 

 $1 \le M \le 10^5$ 

 $S$ 长度为 $N+1$ ，只由字符'0'和'1'组成，保证 $S_0=0$ ， $S_N=0$ 。

# 题目解析

如果 $S$ 中存在连续的'1'组成的长度大于等于 $M$ 的区间，答案显然是-1。如果不存在，那么一定有路径。

我们将移动关系看成一个图，从第 $i$ 点到第 $i+1,i+2,\cdots,i+M$ 连边。问题变成求终点 $N$ 到其他各点最短路问题。因为边很多，直接用单源最短路算法会超时。记 $f[x]$ 为“从点 $x$ 出发到点 $N$ 的最短路长度”，那么
 $$f[x]=\min\{f[x+1],f[x+2],\cdots,f[x+M]\}+1$$
利用可以求区间最小值的数据结构（比如单调队列）就可以算出所有 $f$ 。（对于Gameover点或是超过 $N$ 的点， $f$ 的值设为无穷大）

# 另解

因为随着点编号 $x$ 增加， $f[x]$ 不会增加，利用这个性质。对每个 $d$ 记录“到点 $N$ 最短路长为 $d$ 的点中，编号最小的点”。
设 $idx[d]$ 表示到点 $N$ 的最短路长为 $d$ 的点中，编号最小的点。然后我们从大到小遍历所有点去求最短路。

对每个点 $i$ ，求出它到 $N$ 的最短路方法为：在 $idx$ 数组中，找到“使得点 $i$ 能走到点 $idx[d]$ 的最小的 $d$ ”，则点 $i$ 到 $N$ 的最短路长为 $d+1$ 。然后 $idx[d+1]$ 就可以暂时赋值为 $i$ （这里说“暂时”是因为后边可能有更小的 $i$ 会覆盖掉 $idx[d+1]$ ）。因为随着 $i$ 的减小，这个最小的 $d$ 不会减小，所以可以用尺取法。

求出所有最短路后，从点 $0$ 开始，每次移动到最短路减少的点中编号最小的点，就可以得到字典序最小的序列。

# 代码
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
using namespace std;
typedef long long LL;
const int MR=1e5+10;
int n,m;
string s;
int idx[MR];
//idx[d]表示到点n的最短路长为d的点中，编号最小的点。
int main(){
    cin>>n>>m;
    cin>>s;
    memset(idx,-1,sizeof(idx));
    idx[0]=n;
    int d=0;
    for(int i=n-1;i>=0;i--){
        if(s[i]=='1') continue;
        for(;idx[d]!=-1;d++){
            //如果点i和idx[d]距离不超过m
            //到点n最短路长为d+1的点就暂定为i
            if(idx[d]-i<=m){
                idx[d+1]=i;
                break;
            }
        }
        //如果到这里发现idx[d]==-1
        //说明上面for循环里idx[d]-i<=m不成立
        //那么说明点i和后面的点距离超过m了
        if(idx[d]==-1){
            printf("-1\n");
            return 0;
        }
    }
    //最后倒着输出每步的间隔
    for(int k=d;k>=0;k--){
        printf("%d ",idx[k]-idx[k+1]);
    }
    printf("\n");

    return 0;
}

```


---

## 作者：phigy (赞：1)

题目大意是说开始从 $1$ 号位置每次能跳到 $i+k(0<k<=m)$ 。

不能调到为 $1$ 的地方 。

怎么跳完步数最少，字典序最小 。

设 $dp[i]$ 表示跳到 $i$ 的步数 。

若 $s[i]!=1$ 则 $dp[i]= min(dp[j])(i-j<=m)+1$ 。

若 $s[i]=1$ 则 $dp[i]= -99999999$ (不可能到) 。

显然枚举 $j$ 的复杂度是 $O(nm)$

可以维护一个 $j$ 递增 $dp[j]$ 递增的单调队列。

每次取堆头将复杂度降至 $O(n)$。

再用数组 $fa[i]$ 记录从哪里跳到 $i$ 步数最少。

最后从 $fa[n]$ 开始往回记录跳的位置差最终输出。

因为单调队列的逐渐增加性质每次选取跳的步数一定是字典序最小的 。

---

## 作者：easy42 (赞：0)

### 思路
如果这题只是要求最少的步数，应该怎么做？

很明显，可以用贪心，特别简单。

答案要求输出最小步数中字典序最小的方案。我们知道，步数最小需要每一步尽量大，直接模拟即可。

但是这种方法求出的字典序肯定是最大的，但题目要求的是字典序最小。

所以我们想“正难则反”，采用**倒序枚举**，这样，就可以求出字典序肯定是最小的了。

注意：可以用栈来存储。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char s[100005];
stack<int>st;
int main(){
	cin>>n>>m>>s;
	int l=n;
	bool flag=true;
	while(l>0){
		int w=max(0,l-m);
		while(s[w]=='1') w++;
		if(l==w){
			flag=false;
			break;
		}
		st.push(l-w);
		l=w;
	}
	if(!flag) cout<<-1;
	else{
		while(!st.empty()){
			cout<<st.top()<<" ",st.pop();
		}
	}
	return 0;
}
```

---

## 作者：Dizha (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc146_f)

### 24/6/13 修改了一些错误。

让我们把问题简化一下：高桥君可以任意选择在 $1\sim m$ 间的前进步数，问如何在**不走到障碍物**的情况下从$0$ 点走到点 $n$。

这题可以想出是动规，但数据范围又把我暴力动规的想法打了回去。$n,m\lt10^{5}$ 的范围，两重循环必 T 无疑。

但这时候可以引入一个叫做[单调队列](https://oi-wiki.org/ds/monotonous-queue/)的东西，这个数据结构可以在 $O(n)$ 的时间复杂度中求区间最值。

然后推动规方程：每一个点应均可以由它的前 $m$ 个点得来，所以易得方程： 

$$dp_i=\min(dp_j+1)$$

其中 $i,j$ 均不为 gameover 点，且 $i-m\lt j\lt i$。

解决完动规部分，我们应该要考虑输出路径了。

我们可以先考虑正推，对于每一个 $dp_i$，找到一个 $k$，使 $i< k< \min(i+m,n)$，$dp_k=dp_i+1$，输出路径长度 $k-i$，然后把每一次的 $i$ 赋值为 $k$。这样确实可以得到一个最短路径，但这样会导致每一次投掷步数最大，也就是字典序最大。题目要求字典序最小，所以正推相对会比较难麻烦。

所以我们考虑倒着来。对于每一个 $dp_i$，找到一个 $k$，使 $i> k>\min(i-m,0)$，$dp_k=dp_i+1$，其余操作同上。

这样不仅能找到最小路径，也能保证字典序的最小。

AC Coding:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=1e6+7,inf=9187201950435737471;
ll n,m,f[N],ans[N],l;
string mp;
deque<ll>dq;
int main(){
	memset(f,127,sizeof(f));
	f[0]=0;
	scanf("%lld%lld",&n,&m);
	cin>>mp;
	dq.push_back(0);
	for(ll i=1;i<=n;i++){
		if(mp[i]=='1')continue;
		while(!dq.empty()&&dq.back()<i-m)dq.pop_back();
		if(!dq.empty())f[i]=min(f[i],f[dq.back()]+1);
		while(!dq.empty()&&f[dq.front()]>f[i])dq.pop_front();
		dq.push_front(i);
	}
	if(f[n]==inf){
		printf("-1\n");
		return 0;
	}
	for(ll i=n;i>0;){
		ll t;
		for(ll j=m;j>=1;j--){
			if(i-j<0)continue;
			if(f[i-j]==f[i]-1){
				t=j;
				break;
			}
		}
		i-=t;
		ans[++l]=t; 
	}
	for(ll i=l;i>=1;i--)printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：Antiluna (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc146_f)

比较简单的线性 DP，方程很好推，关键在于输出字典序最小的路径。

显然，每两个值不一样的 $f_i$ 之间都可以构成一条路径，所以我们找字典序最下的路径就是找每个 $i$ 尽量前且 $f_i$ 互不相同的路径，但是并不能正推，因为无法确定是否会到终点，所以要倒推。

数据较水，实测不用单调队列优化也能对。

```
#include<bits/stdc++.h>
using namespace std;
int n,m,dp[100010],ans[100010];
string s;
signed main()
{
	scanf("%d %d",bitand n,bitand m);
	cin>>s;
	dp[0]=0;
	for(int i=1;i<=n;i++)
	{
		dp[i]=2147483646;
		if(s[i]=='1')continue;
		for(int j=i-1;j>=max(0,i-m);j--)
		{
			dp[i]=min(dp[i],dp[j]+1);
		}
	}
	if(dp[n]==2147483646)
	{
		printf("-1");
		return 0;
	}
	int k=n;
	for(int i=dp[n];i>=1;i--)
	{
		for(int j=max(k-m,0);j<k;j++)
		{
			if(dp[j]==dp[k]-1)
			{
				ans[i]=k-j;
				k=j;
				break;
			}
		}
	}
	for(int i=1;i<=dp[n];i++)printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：xukehg (赞：0)

直接从 $1$ 跳到 $n$ 不太好想，考虑反过来，从 $n$ 跳到 $1$。

因为我们要让跳的次数尽量少，因此每一步都尽可能跳最远。我们可以倒序遍历数组，记录上一个 $0$ 的位置 $last$，如果这个点是 $0$，$last$ 更新为 $i$。记录一个 $num$ 数组存上一个 $0$ 的位置，则遍历时当时的 $last$ 就是 $num_i$。然后贪心的从 $n$ 往 $1$ 跳，每次跳 $num_{j - m}$ 就可以了。若遇到 $num_{j - m} \leq j$，则无解。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;

int n,m;
string s;
int a[N],num[N];
int main(){
	cin >> n >> m >> s;
	for (int i = 0;i <= n;i++) a[i] = s[i] - '0';
	int last = n;
	for (int i = n;i >= 0;i--){
		if (a[i] == 0){
			num[i] = i;
			last = i;
		}
		else num[i] = last;
	}
	int j = n,cnt = 0;
	vector<int> v;
	while (j > 0){
		if (j < m){
			v.push_back(j);
			cnt++;
			break;
		}
		if (num[j - m] == j){
			cout << -1 << endl;
			return 0;
		}
		v.push_back(j - num[j - m]);
		j = num[j - m];
		cnt++;
	}
	for (int i = v.size() - 1;i >= 0;i--) cout << v[i] << " ";
}
```

---

## 作者：kinglf (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc146_f)
### 题目解析：
      答案要求输出最小步数中字典序最小的方案。我们知道，步数最小需要每一步尽量大，所以可以得出一下程序：
### 代码：
```c
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=1e5+10;
ll n,m,top,t,a[N],stk[N];
char c;
int main(){
	scanf ("%lld%lld\n",&n,&m);
	for (ll i=0;i<=n;i++){
		scanf ("%c",&c);
		a[i]=c-'0';
	}
	if (a[0]==1){
		printf ("-1");
		return 0;//防止初始位置为 1 
	}
	for (ll i=0;i<n;){
		ll op=-1;//标记是否能跳 
		for (ll j=min(i+m,n);j>i;j--)//min的作用是防止下标越界 
			if (a[j]==0){
				stk[++top]=j-i;
				i=j;
				op=1;//标记为可跳 
				break;
			}
		if (op==-1){
			printf ("-1");
			return 0;//跳不了输出 -1 
		}
	}
	for (ll i=1;i<=top;i++)
		printf ("%lld ",stk[i]);

	return 0;
}
```
但是，这种做法肯定是不能 AC 的，因为输出的是字典序最大的方案，而不是题目所要求的字典序最小。
# 正确思路：
	由最小步数和字典序最小，由前面的步数要尽量小但总步数要尽量大，可以推断，后面的步数要尽量大，那为什么不从后往前模拟呢？
    
由此，得出以下代码：
```c
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=1e5+10;
ll n,m,top,t,a[N],stk[N];
char c;
int main(){
	scanf ("%lld%lld\n",&n,&m);
	for (ll i=0;i<=n;i++){
		scanf ("%c",&c);
		a[i]=c-'0';
	}
	t=n;//从后往前跳 
	if (a[t]==1){ 
		printf ("-1");
		return 0;//防止终点为-1 
	}
	while (t!=0){
		ll u=-1;
		for (ll i=max(t-m,0ll);i<t;i++){
			if (a[i]==0){
				u=i;//标记为可跳 
				stk[++top]=t-i; 
				break;
			}
		}
		if (u==-1){
			printf ("-1");
			return 0;//不可跳就退出 
		}
		t=u;
	}
	for (ll i=top;i>=1;i--){
		printf ("%lld ",stk[i]);
	}

	return 0;
}

```


---

