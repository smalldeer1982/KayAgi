# Deja Vu

## 题目描述

You are given an array $ a $ of length $ n $ , consisting of positive integers, and an array $ x $ of length $ q $ , also consisting of positive integers.

There are $ q $ modification. On the $ i $ -th modification ( $ 1 \leq i \leq q $ ), for each $ j $ ( $ 1 \leq j \leq n $ ), such that $ a_j $ is divisible by $ 2^{x_i} $ , you add $ 2^{x_i-1} $ to $ a_j $ . Note that $ x_i $ ( $ 1 \leq x_i \leq 30 $ ) is a positive integer not exceeding 30.

After all modification queries, you need to output the final array.

## 说明/提示

In the first test case, the first query will add $ 2 $ to the integers in positions $ 4 $ and $ 5 $ . After this addition, the array would be $ [1, 2, 3, 6, 6] $ . Other operations will not modify the array.

In the second test case, the first modification query does not change the array. The second modification query will add $ 8 $ to the integer in position $ 5 $ , so that the array would look like this: $ [7, 8, 12, 36, 56, 6, 3] $ . The third modification query will add $ 2 $ to the integers in positions $ 2, 3 $ , $ 4 $ and $ 5 $ . The array would then look like this: $ [7, 10, 14, 38, 58, 6, 3] $ .

## 样例 #1

### 输入

```
4
5 3
1 2 3 4 4
2 3 4
7 3
7 8 12 36 48 6 3
10 4 2
5 4
2 2 2 2 2
1 1 1 1
5 5
1 2 4 8 16
5 2 3 4 1```

### 输出

```
1 2 3 6 6 
7 10 14 38 58 6 3 
3 3 3 3 3 
1 3 7 11 19```

# 题解

## 作者：_mi_ka_ (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/CF1891B)

题意已经叙述的很清楚，这里不再赘述。

## 思路

在这里我第一眼的思路是分块或者是线段树，可能是数据结构题做多 了留下来的后遗症吧，但在这里这个题作为 B 题，肯定有不用高级数据结构的做法。

然后我就发现了一个性质，如果一个数是 $2^x$ 的倍数，那么它可以写成 $k\times 2^x=2k\times 2^{x-1}$，那么它加上 $2^{x-1}$ 之后就变成了 $(2k+1)\times 2^{x-1}$，由于 $2k-1$ 为奇数，那么它肯定不会再是 $2^x$ 的倍数（也必然不会是 $2$ 的更高次幂的倍数），而只是 $2^{x-1}$ 的倍数。

有了这个性质，那么假设一个数是 $2^{30}$ 的倍数，那么它最多进行 $30$ 次操作就不能进行任何操作，所以最好的复杂度就是每次只修改需要修改的数。

我们考虑把 $2^i(1\le i\le 30)$ 的倍数的下标给维护成一个队列 $i$（$2^0$ 的倍数由于不可能在进行任何操作，所以可以维护也可以不维护），每次操作取出所有大于等于 $x$ 的队列的所有下标进行操作，操作完之后扔到 $x-1$ 的队列中。

时间复杂度 $O(30\sum n)$。

## AC Code

```cpp
#include<iostream>
#include<queue>
#define N 100005
using namespace std;
int T,n,q;
int a[N];
queue<int>que[31];//第i个队列存2^i的倍数 
int re()//朴素的快读 
{
	int x=0,p=1;
	char y=getchar();
	for(;y>'9'||y<'0';y=getchar())
		if(y=='-')
			p=-p;
	for(;y>='0'&&y<='9';y=getchar())
		x=x*10+y-'0';
	return x*p;
}
void wr(int x)//朴素的快写 
{
	if(x<0)
		putchar('-'),x=-x;
	if(x>9)
		wr(x/10);
	putchar(x%10+'0');
}
signed main()
{
	T=re();
	while(T--)
	{
		n=re(),q=re();
		for(int i=1;i<=n;i++)//O(30n)
		{
			a[i]=re();
			int l=0;
			for(;l<=30;l++)
				if(a[i]%(1<<l))//找出第一个不满足为2^l倍数的数 
					break;
			que[l-1].push(i);
		}
		while(q--)
		{
			int x=re();
			for(int i=30;i>=x;i--)//O(30n)
				while(que[i].size())
				{
					int now=que[i].front();
					que[i].pop();
					a[now]+=(1<<(x-1));
					que[x-1].push(now);
				}
		}
		for(int i=1;i<=n;i++)
			wr(a[i]),putchar(' ');
		putchar('\n');
		for(int i=1;i<=30;i++)//用完清空，复杂度O(n) 
			while(que[i].size())
				que[i].pop();
	}
	return 0;
}

```

---

## 作者：qzhwlzy (赞：6)

### 题目大意

有一个长度为 $n$ 的序列 $a$，$q$ 次操作。每次操作给定一个 $x$，对于所有 $i$，假设 $a_i$ 被 $2^x$ 整除，则将 $a_i$ 加上 $2^{x-1}$。求最终序列。

### 思路

发现一个数 $p$ 整除 $2^x$ 的充要条件是 $p$ 在二进制下最后 $x$ 位全部都是 $0$，而在加上 $2^{x-1}$ 后 $p$ 在二进制下的后导零个数只剩下 $x-1$ 个，这意味着若 $x'\ge x$，则 $p$ 不会被 $x'$ 操作。也就是说，真正有用的 $x$ 一定是递减的。又由于题目里说 $x\le 30$，则找到这些有用的 $x$ 之后枚举所有 $a_i$ 更新即可。

复杂度 $\mathcal{O}(30n)$。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define maxn 100005
using namespace std;
int T,n,q,a[maxn],x,las;
int main(){
        scanf("%d",&T); while(T--){
		scanf("%d%d",&n,&q); for(int i=1;i<=n;i++) scanf("%d",&a[i]); las=-1;
		while(q--){
			scanf("%d",&x); if(x<las||las==-1)
				{las=x; for(int i=1;i<=n;i++) if(a[i]%(1<<x)==0) a[i]+=(1<<(x-1));}
		} for(int i=1;i<=n;i++) printf("%d%c",a[i]," \n"[i==n]);
	} return 0;
}
```


---

## 作者：Withershine (赞：2)

建议凭橙，思路橙，码量红到橙。
## 思路
### 一，暴力
直接依照题意模拟，复杂度 $O(tqn^2)$，看一眼数据范围，妥妥 T 飞，倒在第三个点。
### 二，逐步优化
看一眼数据发现，虽然 $q$ 很大，但实际上 $x$ 只有三十个值，因此首先预处理出从 $2^1$ 到 $2^{30}$ 的所有值，摘掉一个 $n$，复杂度 $O(tqn)$。

接下来不管怎样，即使把复杂度优化到 $O(tq)$，复杂度依旧非常的高。$t$ 组数据是不可能去掉的，因此考虑去掉 $q$。使复杂度变为 $O(tn)$ 或者 $O(tn)$ 的近似值。

考虑到对于每一个 $a_i$，当它满足某一个 $a_i \bmod 2^x=0$ 时。则 $(a_i+2^{x-1}) \bmod 2^x$ 此时一定不为 $0$。说人话就是当一个数被 $2^x$ 整除过后，它就**不会再能够**整除这个 $2^x$。

简单证明一下，当 $a_i \bmod 2^x=0$ 时，对于 $(a_i+2^{x-1}) \bmod 2^x$，等价于 $a_i \bmod 2^x+2^{x-1} \bmod 2^x$。很明显 $a_i \bmod 2^x=0$ 而 $2^{x-1} \bmod 2^x \ne 0$ 恒成立。即使在经过多个不同的 $2^x$ 的处理后，这个结论依旧成立。

所以在 $\text{AC}$ 代码中，对于每组数据，用一个数组 $\text{book}$ 记录 $x$ 是否出现过，复杂度 $O(tn)$。
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
using namespace std;
ll t , n , a[100005] , q , x;
ll qp[31] = {1 , 2 , 4 , 8 , 16 , 32 , 64 , 128 , 256 , 512 , 1024 , 2048 , 4096 , 8192 , 16384 , 32768 , 65536 , 131072 , 262144 , 524288 , 1048576 , 2097152 , 4194304 , 8388608 , 16777216 , 33554432 , 67108864 , 134217728 , 268435456 , 536870912 , 1073741824};
ll book[31];
//priority_queue<ll> q;
//priority_queue <ll , vector<ll> , greater<ll> > q;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n >> q;
		fr(i , 1 , n)
		{
			cin >> a[i];
		}
		while(q--)
		{
			cin >> x;
			if(book[x])
			{
				continue;
			}
			book[x] = 1;
			fr(i , 1 , n)
			{
				if(a[i] % qp[x] == 0)
				{
					a[i] += qp[x - 1];
				}
			}
		}
		memset(book , 0 , sizeof(book));
		fr(i , 1 , n)
		{
			cout << a[i] << ' ';
		}
		cout << '\n';
	}
 	return 0;
}
```


---

## 作者：aCssen (赞：1)

### Solution

注意到一个数在加上 $2^{x-1}$ 后，就不是任何 $2^i(i>x)$ 的倍数了，所以如果我们每次都只修改 $2^x$ 的倍数的话，一个数最多只会被修改 $30$ 次，那么复杂度就是对的。

具体的，我们维护 $30$ 个 `vector`，第 $i$ 个保存是 $2^i$ 的倍数的数的下标，对于关于第 $i$ 次修改给出的数 $x$，直接用第 $x$ 个 `vector` 更新 $a$，同时把第 $x$ 个 `vector` 中的数放到第 $x-1$ 个 `vector` 里。然后把 $x \sim 30$ 的所有 `vector` 都清空，因为第 $j+1$ 个 `vector` 中的元素肯定是第 $j$ 个 `vector` 的子集。然后再将第 $x-1$ 个 `vector` 中的元素去重，注意有新元素加入的时候才进行这步操作，否则复杂度会退化。

时间复杂度 $\mathcal{O}(\sum 30(n+q \log n))$,但跑不满。

### Code
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
const int maxn=1e5+5;
int n,q,x;
long long a[maxn];
vector<int>v[maxn];
void solve(){
	for(int i=0;i<=30;i++)
		v[i].clear();
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		for(int j=1;j<=30;j++){
			if(a[i]%(1<<j)==0) v[j].push_back(i);
		}
	}
	while(q--){
		int x;
		scanf("%d",&x);
		bool f=false;
		for(int p:v[x]){
			a[p]+=(1ll<<(x-1));
			v[x-1].push_back(p);
			f=true;//标记是否有新元素加入
		}
		if(f){
			sort(v[x-1].begin(),v[x-1].end());//排序后才能用 unique
			v[x-1].erase(unique(v[x-1].begin(),v[x-1].end()),v[x-1].end());//把多余的部分删去
		}
		for(int i=x;i<=30;i++) v[i].clear();
	}
	for(int i=1;i<=n;i++)
		printf("%lld ",a[i]);
	printf("\n");
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--) solve();
	return 0;
}
```

---

## 作者：66xyyd (赞：1)

## 题意

给出数列 $a$，每次修改把是 $2^x$ 的倍数的元素都加上 $2^{x-1}$，共 $q$ 次。输出最终数列。

## 题解

每次修改操作都是有特殊性质的，考虑把 $a$ 拆成二进制位。如题目中第一组数据的拆成：
```
001 010 011 100 100
```

我们发现一个数是 $2^x$ 次方的倍数，当且仅当这个数的二进制位的后 $x-1$ 位都是 $0$。那么加上数的操作就变成把这个数的第 $x-1$ 位改成 $1$。这说明什么？**能对一个数产生影响的 $x$ 是单调递减的。** 因为第 $x-1$ 位改成 $1$ 后所有大于等于 $x-1$ 的修改都不满足题目要求。

那我们只需要存下来一个单调递增的修改序列 $q$ 就可以了。然后对于每个存下来的 $x$ 进行修改。

```cpp
#include<iostream>
#include<queue>
using namespace std;
long long a[114514],n,cnt,q[35],qq;
int main(){
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--){
		q[0]=114;//存极大值保证第一个数放入的正确性
		cnt=0;
		cin >> n >> qq;
		for (int i=1;i<=n;i++){
			cin>>a[i];
		}
		for (int i=1;i<=qq;i++){
			int x;
			cin>>x;
			if (x<q[cnt]){//只有比q[cnt]小的数才会产生影响
				cnt++;
				q[cnt]=x;
			}
		}
		for (int i=1;i<=n;i++){
			for(int j=1;j<=cnt;j++){
				if(a[i]%(1<<q[j])==0){
					a[i]+=(1<<(q[j]-1));
				}
			}
			cout << a[i] << ' ';
		}
		cout << '\n';
	}
	cout << flush;
	return 0;
}
```

时间复杂度 $O(|q| n)$，其中 $|q|$ 表示存下来的 $q$ 数组长度，最大为 $30$。

---

## 作者：Aveiro7 (赞：0)

### 题意：
给你一个长度为 $n$ 的数组 $a$，接下来依次进行 $q$ 次修改，第 $i$ 次会给你一个数 $x$，你需要将 $a$ 中所有是 $2^x$ 的倍数的数加上 $2^{x-1}$，最后输出序列即可。有多组数据。

### 思路：

通过仔细的观察，我们能发现：把序列中的所有数看做二进制会方便很多，并且有一个非常有用的性质：如果一个数是 $2^x$ 的倍数，那么这个数换成二进制后，它至少有 $x-1$ 个后导零，也就是它的末尾 $x-1$ 位都是零。而将它加上 $2^{x-1}$，就是将这个数的第 $x-1$ 位改成 $1$ 即可。更改之后所有大于 $x-1$ 的修改就都不符合题意了。并且，所有有用的 $x$ 必定是单调递减的，所以我们只需要找出这些能用的 $x$ 随后去枚举就可以了。

---

## 作者：technopolis_2085 (赞：0)

这题有一个性质：

如果一个数是 $2^x$ 的倍数，如果这个数被操作了，则该数永远不会再变回 $2^x$ 的倍数。

这个性质很好证明。如果该数加了 $2^{x-1}$，则它变为 $2^{x-1}$ 的倍数，后面操作时只会将其变为 $2^{x-2}$ 的倍数，$2^{x-3}$ 的倍数，等等。

则可以考虑单调栈。

对于询问 $i$ 而言，每次找到第一个比 $x_i$ 小的数 $x_j$，然后进行操作，并跳到 $j$，因为对大于等于 $x_i$ 的数操作并不会影响该数。

时间复杂度为 $O(30 × q)$。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=2e5+10;
int a[maxn],x[maxn];
int first[32];

int nxt[maxn];

signed main(){
	int T;
	scanf("%lld",&T);
	
	while (T--){
		int n,q;
		scanf("%lld%lld",&n,&q);
		
		for (int i=0;i<=30;i++) first[i]=0;
		for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
		for (int i=1;i<=q;i++){
			scanf("%lld",&x[i]);
			if (first[x[i]]==0) first[x[i]]=i;
		}
		
		stack<int> st;
		while (!st.empty()) st.pop();
		for (int i=q;i>=1;i--){
			while (!st.empty()&&x[i]<=x[st.top()]) st.pop();
			if (st.empty()) nxt[i]=-1;
			else nxt[i]=st.top();
			st.push(i);
		}
		
		for (int i=1;i<=n;i++){
			int mi=1e9+7;
			for (int j=0;j<=30;j++){
				if (a[i]%(1<<j)==0&&first[j]!=0){
					if (first[j]<mi){
						mi=first[j];
					}
				}
			}
			
			if (mi==1e9+7){
				printf("%lld ",a[i]); continue;
			}
			
			int pos=mi;
			while (pos!=-1){
				a[i]+=(1<<(x[pos]-1));
				pos=nxt[pos];
			}
			
			printf("%lld ",a[i]);
		}
		
		printf("\n");
	}
	return 0;
}
```


---

## 作者：BugGod (赞：0)

首先，有一个结论：如果目前最小的 $x$（题目中的含义）比当前的操作数 $x$ 小，那么不需要更新。

证明：设所有为 $2^x$ 倍数的数为 $A_1,A_2,\cdots,A_k$，则设 $A_i=p_i2^x$，显然，当执行操作后，$A_i\leftarrow p_i2^x+2^{x-1}$，即 $A_i=(2p_i+1)2^{x-1}$，显然，$2p_i+1$ 是奇数，所以 $A_i$ 只对操作数字 $y$ 为 $x-1,x-2,\cdots,1$ 的情况下会变化，那么也就是说，所有含有质因子 $2$ 数量不小于 $x$ 操作后都只含有 $x-1$ 个质因子 $2$，那么所有大于最小的 $x-1$ 的操作都是无效的。

有了这个结论，就好写了，把暴力改一下就行了。

CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,q,a[100010],k=100,x;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		k=100;
		cin>>n>>q;
		for(int i=1;i<=n;i++)cin>>a[i];
		while(q--)
		{
			cin>>x;
			if(x>=k)continue;
			for(int i=1;i<=n;i++)if((a[i]%(1<<x))==0)a[i]+=(1<<x-1);
			k=x;
		}
		for(int i=1;i<=n;i++)cout<<a[i]<<" ";
		cout<<'\n';
	}
	return 0;
}
```

---

