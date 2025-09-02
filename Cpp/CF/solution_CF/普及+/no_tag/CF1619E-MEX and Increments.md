# MEX and Increments

## 题目描述

Dmitry has an array of $ n $ non-negative integers $ a_1, a_2, \dots, a_n $ .

In one operation, Dmitry can choose any index $ j $ ( $ 1 \le j \le n $ ) and increase the value of the element $ a_j $ by $ 1 $ . He can choose the same index $ j $ multiple times.

For each $ i $ from $ 0 $ to $ n $ , determine whether Dmitry can make the $ \mathrm{MEX} $ of the array equal to exactly $ i $ . If it is possible, then determine the minimum number of operations to do it.

The $ \mathrm{MEX} $ of the array is equal to the minimum non-negative integer that is not in the array. For example, the $ \mathrm{MEX} $ of the array $ [3, 1, 0] $ is equal to $ 2 $ , and the array $ [3, 3, 1, 4] $ is equal to $ 0 $ .

## 说明/提示

In the first set of example inputs, $ n=3 $ :

- to get $ \mathrm{MEX}=0 $ , it is enough to perform one increment: $ a_1 $ ++;
- to get $ \mathrm{MEX}=1 $ , it is enough to perform one increment: $ a_2 $ ++;
- $ \mathrm{MEX}=2 $ for a given array, so there is no need to perform increments;
- it is impossible to get $ \mathrm{MEX}=3 $ by performing increments.

## 样例 #1

### 输入

```
5
3
0 1 3
7
0 1 2 3 4 3 2
4
3 0 0 0
7
4 6 2 3 5 0 5
5
4 0 1 0 4```

### 输出

```
1 1 0 -1 
1 1 2 2 1 0 2 6 
3 0 1 4 3 
1 0 -1 -1 -1 -1 -1 -1 
2 1 0 2 -1 -1```

# 题解

## 作者：Otomachi_Una_ (赞：10)

一道很珂爱的喵喵题

## 题目简述
- 定义操作为给某一个数加一。
- 给一个数列 $\{a_n\}$ 问要进行多少次的操作才可以让 $\text{mex}(a_1,a_2\dots a_n)=i$。
- 输出 $i$ 从 $0$ 到 $n$ 遍历的结果。
- 多组数据，$t\leq10^4,\sum n\leq2\times 10^5$。

## 解题思路

想要 $\text{mex}(a_1,a_2\dots a_n)=i$，本质上就是要 $a_i$ 中满足下列条件：

1. $0,1,2\dots i-1$ 均在 $a_k$ 中出现。
2. $i$ 不在 $a_k$ 中出现。

首先我们考虑第二个条件，也就是我们只要把所有 $a_k$ 中数值是 $i$ 的全部操作一次即可。

**我们下列的仅讨论满足 1 条件的操作**

显然这个时候 $ans$ 是递增的。这提示我们要利用前面的答案。

当 $i=i-1$ 转移到 $i=i$ 时，我们要寻找一个 $a_k$ 操作到 $i-1$。我们自然会找**最大但不超过 $i-1$ 的**而且**之前没有使用过**的 $a_k$ 进行。

维护这样的 $a_k$ 是比较简单的。

我这里用了一个栈操作。每次首先加入数值为 $i-1$ 的元素（可能没有）。如果当前栈为空，也就是小于 $i$ 的全部使用过了，这时后面的答案都是 `-1` 了。

否则直接取出栈首增加答案即可。

## 参考代码

```cpp
#include<iostream>
using namespace std;
#define ll long long
const int MAXN=2e5+5;
int t,n;
int a[MAXN],cnt[MAXN];
int st[MAXN],tail=0;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			cnt[a[i]]++;
		}
		cout<<cnt[0]<<" ";
		ll ans=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=cnt[i-1];j++)
				st[++tail]=i-1;
			if(tail==0){
				for(int j=1;j<=n-i+1;j++)
					cout<<"-1 ";
				break;
			}
			else{
				ans+=(i-1-st[tail--]);
				cout<<ans+cnt[i]<<" ";
			}
		}
		for(int i=1;i<=n;i++)
			cnt[a[i]]=0;
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：Awlgot (赞：3)

#### 一条简单性质：

一个数 $x$ 若要成为 $\text{MEX}$，那么必须要有 $0$ 至 $x-1$ 的所有元素。

那么可知只要当前 $x$ 无法被得到，则所有 $\ge x$ 的数就都无法被得到。

### 如何计算答案？

考虑记下每个数出现次数，若一个数未出现，则若要得到比该数大的数，那么至少有一个比该数小的数经过操作得到该数。

我们可以开一个栈来使得上述操作最优。

复杂度 $O(n)$。

#### 具体操作：
1. 若当前数前一个数未出现，考虑从栈中拿出一个数来。

2. 若栈中无数可借，则该大于等于该数的数都无法被得到。

3. 把使得该数成立的代价作为答案输出。


### 代码：


 ```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define pii pair<int,int>
using namespace std;
const int N=2e5+5;
int n;
int a[N],cnt[N];
pii g[N];
void ____(){
	cin>>n;
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;i++){
		cin>>a[i];
		cnt[a[i]]++;
	}
	bool fl=0;
	int sum=0,top=0;
	if(cnt[0]==0){
		cout<<"0 ";
		for(int i=1;i<=n;i++) cout<<"-1 ";
		cout<<"\n";
		return ;
	}
	for(int i=0;i<=n;i++){
		if(i>0){
			if(cnt[i-1]>0){
				if(cnt[i-1]>1) g[++top]={i-1,cnt[i-1]-1};
			}
			else{
				if(top==0) fl=1;
				sum+=(i-1)-g[top].fi;
				if((--g[top].se)==0) top--;
			}
		}
		if(fl){cout<<"-1 ";continue;}
		cout<<sum+cnt[i]<<" ";
	}
	cout<<"\n";
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	std::ios::sync_with_stdio(0);
	int T=1;
	cin>>T;
	while(T--) ____();
	return 0;
}

```


---

## 作者：Ericby666 (赞：2)

## [题目链接](https://www.luogu.com.cn/problem/CF1619E)
本题其实就是让每个 $a_i$ 满足两个条件：

1.$0$ 到 $i-1$ 均在 $a_k$ 中出现。

2.$i$ 不在 $a_k$ 中出现。

如果想满足第 $1$ 个条件且使得操作次数最少。我们可以使用一个栈将 $0$ 到 $i-1$ 中的多余的数存起来，当需要时将栈顶取出，此时增加的代价为需要用的数减去栈顶。

如果想满足第 $2$ 个条件，只需将每个 $i$ 加上 $1$，此时增加的代价为 $i$ 的个数。

此处还有一个性质：当到某个 $i$ 无法满足条件时，那 $i+1$ 到 $n$ 都无法满足条件。

AC 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,x,cnt[200005],ans;
stack<int>q;//使用栈维护
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		memset(cnt,0,sizeof cnt);
		ans=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>x;
			cnt[x]++;
		}
		cout<<cnt[0]<<' ';//只需0的个数次操作就可使0满足条件
		for(int i=1;i<=n;i++){
			for(int j=1;j<=cnt[i-1];j++)q.push(i-1);
			if(q.empty()){
				for(int j=1;j<=n-i+1;j++)cout<<"-1 ";//后面全无法满足要求
				break;
			}
			else{
				ans+=(i-1)-q.top();//转换的代价
				q.pop();
				cout<<ans+cnt[i]<<' ';//最终答案
			}
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Eazin_star (赞：1)

### 思路
一个数如果要成为数列中没有出现的最小的非负整数，那比他小的所有非负整数都要出现在数列中。所以我们可以知道，如果一个数不能成为数列中没有出现的最小的非负整数那么比他大的数一定都不能做到。

所以我们可以开一个数组来记录数列中每个数出现的次数，若我们需要的数未出现，那一定需要一个比他小的数进行操作得到我们想要的数。如果没有可以进行操作的数，那么说明所以比我们需要的数大的数都不能成为数列中没有出现的最小非负整数。

### 代码
```cpp
#include <bits/stdc++.h>
#define int long long //一定要开longlong，不然第4个点过不去
using namespace std;

int t, n;
int a[200005]; 
pair <int, int> s[200005];

signed main() {
	scanf("%lld", &t);
	while (t--) {
		memset(a, 0, sizeof a);
		scanf("%lld", &n);
		for (int i = 1, x; i <= n; i++) {
			scanf("%lld", &x);
			a[x]++;
		}
		if (!a[0]) {
			printf("0 ");
			for (int i = 1; i <= n; i++) printf("-1 ");
			putchar('\n'); //如果没有0，直接全部输出-1
			continue;
		}
		int sum = 0, top = 0;
		bool flag = 0;
		for (int i = 0; i <= n; i++) {
			if (i) {
				if (a[i-1]) {
					if (a[i-1] > 1) s[++top] = {i-1, a[i-1]-1}; 
				}
				else {
					if (!top) flag = 1;
					sum += (i-1)-s[top].first; //记录代价
					if (!(--s[top].second)) top--;
				}
			}
			if (flag) { //如果做不到输出-1
				printf("-1 ");
				continue;
			}
			printf("%lld ", sum+a[i]); //输出答案
		}
		putchar('\n');
		
	}	
	return 0;
}
```


---

## 作者：Priestess_SLG (赞：0)

要让原数组的 $\text{mex}$ 值为 $i$ 则需要让 $0\sim i-1$ 中每一个数至少出现一次且 $i$ 一次也不出现。

因此考虑对于每一个没有出现过的数，在其之前找到一个出现了至少两次的数并将其的一个数改为这个数。若找不到则无解。最后将答案加上 $i$ 出现的次数即将所有 $i$ 元素修改为 $i+1$ 的代价。具体可以使用一个栈来维护上述信息。

时间复杂度为 $O(n)$，可以通过。

[代码](https://codeforces.com/contest/1619/submission/281132046)。

---

## 作者：hjfjwl (赞：0)

题解思路：

这道题说你一次操作可以给一个数加 $1$，对于每一个数求让这个数成为队列中最小非负整数的操作次数，有个特性是若果这个数不行，以后的也不行。
初始答案 $tot$ 为 $cnt_{id} + t$, 其中 $cnt_{id}$ 为值为 $id$ 的个数而 $t$ 是让队列出现 $0$ 到 $id - 2$ 的操作次数。若果 $cnt_{id - 1}$ 是正数就要判断了，若果当前没有数能够替换就输出 $-1$，否则就替换。~~具体看代码理解~~

Ac code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//注意不然第4个点会Wa
#define pii pair<int,int>
int cnt[200005];
signed main()
{
	int t;
	scanf("%lld",&t);
	while(t--)
	{
		int n;
		scanf("%lld",&n);
		memset(cnt,0,sizeof(cnt));
		priority_queue<pii>q;
		for(int i = 1;i <= n;i++)
		{
			int x;
			scanf("%lld",&x);
			cnt[x]++;
		}
		int id;
		int t = 0;
		for(id = 0;id <= n;id++)
		{
			int tot = cnt[id] + t;
			if(id)
			{
				if(!cnt[id - 1])
				{
					if(q.empty())
					{
						break;
					}
					else
					{
						int a = q.top().first;
						int b = q.top().second;
						q.pop();
						tot += id - 1 - a;
						t += id - 1 - a;
						b--;
						if(b)q.push({a,b});
					}
				}
			}
			if(cnt[id] > 1)q.push({id,cnt[id] - 1});
			printf("%lld ",tot);
		}
		for(id;id <= n;id++)
		{
			printf("-1 ");
		}
		puts("");
		
	}
	return 0;
}
```

---

