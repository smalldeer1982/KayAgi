# Extra Element

## 题目描述

A sequence $ a_1, a_2, \dots, a_k $ is called an arithmetic progression if for each $ i $ from $ 1 $ to $ k $ elements satisfy the condition $ a_i = a_1 + c \cdot (i - 1) $ for some fixed $ c $ .

For example, these five sequences are arithmetic progressions: $ [5, 7, 9, 11] $ , $ [101] $ , $ [101, 100, 99] $ , $ [13, 97] $ and $ [5, 5, 5, 5, 5] $ . And these four sequences aren't arithmetic progressions: $ [3, 1, 2] $ , $ [1, 2, 4, 8] $ , $ [1, -1, 1, -1] $ and $ [1, 2, 3, 3, 3] $ .

You are given a sequence of integers $ b_1, b_2, \dots, b_n $ . Find any index $ j $ ( $ 1 \le j \le n $ ), such that if you delete $ b_j $ from the sequence, you can reorder the remaining $ n-1 $ elements, so that you will get an arithmetic progression. If there is no such index, output the number -1.

## 说明/提示

Note to the first example. If you delete the $ 4 $ -th element, you can get the arithmetic progression $ [2, 4, 6, 8] $ .

Note to the second example. The original sequence is already arithmetic progression, so you can delete $ 1 $ -st or last element and you will get an arithmetical progression again.

## 样例 #1

### 输入

```
5
2 6 8 7 4
```

### 输出

```
4```

## 样例 #2

### 输入

```
8
1 2 3 4 5 6 7 8
```

### 输出

```
1```

## 样例 #3

### 输入

```
4
1 2 4 8
```

### 输出

```
-1```

# 题解

## 作者：奇米 (赞：5)

## 题解 - $\mathrm{CF1185D\ Extra\ Element}$

### 题目意思

* 给你一个长为$n$的序列$a$，问你能否删除一个数后对数列重拍形成等差数列。如果能输出删除的位置。否则输出$\mathrm{-1}$

* $n\leq 2e5$

### $\mathrm{Sol}$

* 小清新**贪心**题

* 我们首先对原序列重排「就是排序」。然后我们思考如何会构成一个等差数列：打个比方，如果$a={2,4,6,7,8}$我们删除第$4$个数，那么它与相邻的差合并起来形成新的一个差值$x$。我们只要判断$x$是否为序列公差即可。

* 对于这个操作我们$O(n)$枚举去掉那个数。就是假装先删掉这个数然后判断一下再把值改回来，如果合法直接输出就好了。

* 时间复杂度$O(n \log\ mx)$，因为要开个$MAP$记录差值所以代只$\log$

### $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
#define For(i,a,b) for ( int i=(a);i<=(b);i++ )
#define Dow(i,b,a) for ( int i=(b);i>=(a);i-- )
#define GO(i,x) for ( int i=head[x];i;i=e[i].nex )
#define mem(x,s) memset(x,s,sizeof(x))
#define cpy(x,s) memcpy(x,s,sizeof(x))
#define YES return puts("YES"),0
#define NO return puts("NO"),0
#define GG return puts("-1"),0
#define pb push_back
#define int long long 
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int mod=1e9+7;
const int mo=998244353;
const int N=2e5+5;

int n,m,sum[N],b[N],flg,gs;
map<int,int> lyx,wyy;

struct Node
{
	int x,id;
	inline bool friend operator < (const Node&a,const Node&b)
	{
		return a.x<b.x;
	}
};
Node a[N];

signed main()
{
	n=read();
	For(i,1,n) a[i]=(Node){read(),i};
	sort(a+1,a+n+1);
	For(i,1,n-1) 
	{
		b[i]=a[i+1].x-a[i].x;
		lyx[b[i]]++;
	}
	if(a[1].x==a[n].x||lyx[b[1]]==n-1) return printf("%d\n",a[1].id),0;
	lyx[b[1]]--;
	if(lyx[b[2]]==n-2) return printf("%d\n",a[1].id),0;
	lyx[b[1]]++;
	
	lyx[b[n-1]]--;
	if(lyx[b[n-2]]==n-2) return printf("%d\n",a[n].id),0;
	lyx[b[n-1]]++;
	
	For(i,2,n-1) 
	{
		int x=b[i];
		int nxt=a[i+1].x-a[i-1].x;
		int pre=b[i-1];
		lyx[x]--,lyx[pre]--,lyx[nxt]++;
		if(lyx[nxt]==n-2) 
			return printf("%d\n",a[i].id),0;
		lyx[x]++,lyx[pre]++,lyx[nxt]--;
	}
	GG;
}
		
	
```


---

## 作者：DaiRuiChen007 (赞：4)

# $\text{CF1185D - Extra Element}$  题解



## 题目大意

 给定一个长度为 $n$ 的数组 $a$，问你能不能通过去掉其中的某个元素 $a_x$ 并且对于剩余的数列 $a$ 进行重排，使得 $a$ 成为一个等差数列，如果可以，输出 $x$，否则输出 $-1$。

数据范围保证 $n\le2\times10^5$。

## 思路分析

做题的时候很轻松秒了，看了一圈题解貌似没有这种的小清新解法，故来一发题解

首先 $a$ 排序之后必是单调递增的，所以可以在删除之前就对 $a$ 升序排序，考虑删除某个元素后能否使得 $a$ 是等差数列。

因为重排后的等差数列可以只通过前两项确定整个序列的形态，所以有以下三种情况：

1. 删除 $a_1$，以 $a_2,a_3$ 作为等差数列的前两项，检查剩余的序列是否是等差数列即可
2. 删除 $a_2$，以 $a_1,a_3$ 作为等差数列的前两项，检查剩余的序列是否是等差数列即可
3. 同时保留 $a_1,a_2$，在剩下的数列中找到第一对 $a_j,a_{j-1}$ 使得 $a_{j}-a_{j-1}\neq a_2-a_1$，此时 $a_j,a_{j-1}$ 不可能同时存在，所以分别枚举删除 $a_j,a_{j-1}$ 之后构不构成等差数列即可

如果以上四种删数情况均不满足要求，则无解

这种做法最多枚举四次删除操作，复杂度的瓶颈在排序上，复杂度 $\Theta(n\log n)$

## 代码分析

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+1;
struct node {
	int val,id;
	inline friend bool operator <(const node &x,const node &y) {
		return x.val<y.val;
	}
}	a[MAXN];
int n;
inline bool judge(int k) {
	//检查删除k后能不能构成等差数列 
	vector <int> seq;
	for(int i=1;i<=n;++i) if(i!=k) seq.push_back(a[i].val);
	int d=seq[1]-seq[0];
	for(int i=1;i<seq.size();++i) {
		if(seq[i]-seq[i-1]!=d) return false;
	}
	return true;
}
signed main() {
	scanf("%lld",&n);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i].val),a[i].id=i;
	if(n<=3) {
		puts("1");
		return 0;
	}
	sort(a+1,a+n+1);
	if(judge(1)) {
		//删除第一项 
		printf("%lld\n",a[1].id);
		return 0;
	}
	if(judge(2)) {
		//删除第二项 
		printf("%lld\n",a[2].id);
		return 0;
	}
	bool flg=true;
	int d=a[2].val-a[1].val,k=0;
	for(int i=3;i<=n;++i) {
		if(a[i].val-a[i-1].val!=d) {
			//找到不满足的两项删除 
			if(judge(i)) {
				printf("%lld\n",a[i].id);
				return 0;
			}
			if(judge(i-1)) {
				printf("%lld\n",a[i-1].id);
				return 0;
			}
			puts("-1");
			return 0;
		}
	}
	return 0;
}
```



---

## 作者：Sooke (赞：3)

#### 题意

从序列中删除一个数，使得剩下的数能重排成等差数列。

---

#### 解题思路

首先给序列排序，以代替删数之后的重排。

因为只保留 $n - 1$ 个数，显然如果要是等差数列，公差必须在排序后的序列 $n - 1$ 个相邻数的差中出现至少 $n - 3$ 次。（保留的 $n - 1$ 个数相邻有 $n - 2$ 个差，其中一个差可能在排序后的序列中拼合而成）

根据以上性质，我们把排序后序列的 $n - 1$ 个差放到 $\text{set}$ 里，然后其中出现 $n - 3$ 次的差当作公差 $\text{check}$ 一下。（不会超时，满足条件的数顶多 $\lfloor \dfrac{n}{n - 3}\rfloor$ 个）

至于怎么 $\text{check}$ ，我们只能删一个数，直接扫过去，遇到不满足公差的数删掉，如果删完还不行，那就不行了。如果不用删就满足条件，删首尾任意一个数。

---

## 作者：Xiphi (赞：1)

作为 D 题还是有点简单了...

首先需要从小到大排序，这一步不难想到，然后便是枚举“被删除元素”这一步了。考虑用 `map` 记录相邻两元素的差值，即 $a[2]-a[1],a[3]-a[2],...,a[n]-a[n-1]$。

接着，我们尝试考虑如何判断删除一个元素后，是否为等差数列。不难发现，去除一个元素后，还有 $n-2$ 个差值，如果他们都相同，剩下元素即为等差数列。对于每一次删除元素后，会消除 $2$ 个差值，并加入一个差值，也就是 $a[i+1]-a[i-1]$。

特别的，我们在枚举第 $1$ 个与第 $n$ 个时，需要特判。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    int v,id;
     
};
node a[200005];int n;
map<int,int> st;
bool cmp(node x,node y){
    return x.v<y.v;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i].v;
        a[i].id=i;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=2;i<=n;++i){
        st[a[i].v-a[i-1].v]++;
    }
    if(st[a[3].v-a[2].v]==n-1){
        cout<<a[1].id;
        return 0;
    }
    for(int i=1;i<=n;++i){
        if(i==1){
            st[a[2].v-a[1].v]--;
            if(st[a[3].v-a[2].v]==n-2){cout<<a[1].id<<' ';return 0;}
            st[a[2].v-a[1].v]++;
        }
        else if(i==n){
            st[a[n].v-a[n-1].v]--;
            if(n==2||st[a[2].v-a[1].v]==n-2){cout<<a[n].id;return 0;}
            st[a[n].v-a[n-1].v]++;
        }
        else{
            st[(a[i].v-a[i-1].v)]--,st[(a[i+1].v-a[i].v)]--,st[(a[i+1].v-a[i-1].v)]++;
            if(st[a[i+1].v-a[i-1].v]==n-2){cout<<a[i].id;return 0;}
            st[(a[i].v-a[i-1].v)]++,st[(a[i+1].v-a[i].v)]++,st[(a[i+1].v-a[i-1].v)]--;
        }
        
    }
    cout<<-1;
    return 0;
}
```

---

## 作者：lyzqs (赞：1)

楼上[Sooke大佬](https://www.luogu.org/blog/Sooke/solution-cf1185d)写的非常好，我这里就再补充一些Sooke大佬没写到的细节并附上代码实现。

### 1. 

注意一组数据：
```
5
1 2 2 3 4
```
其中公差出现的次数因为重复元素导致并不是$n-3$而是$n-2$

解决方法其实很简单，在$check$所有公差次数为$n-3$的时候再$check$一下所有公差为$n-2$的情况就好了

### 2.

再注意两组数据：
```
5
1 3 4 5 6
```
```
5
1 2 3 4 6
```
其中公差出现次数因为首项或者末项被删除，导致没有形成新的公差，而变成$n-2$.

解决方法：特判一下开头和结尾就好了

### 代码
```cpp
#include <bits/stdc++.h>
#define il inline
#define ll long long
#define Max 1000005
#define int long long
using namespace std;
il ll read()
{
	char c=getchar();
	ll x=0,f=1;
	while(c>'9'||c<'0')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int n;
struct node
{
	int id,x;
}e[Max];
il bool cmp(node a,node b)
{
	return a.x<b.x;
}
map<int,int> h,vst;
il void check(int k)
{
	int pos=0;
	for(int i=2;i<=n;i++) 
		if(e[i].x-e[i-1].x!=k)
		{
			if(!pos) pos=i,i++;
			else return;
		}
	if(e[pos+1].x-e[pos-1].x!=k) return;
	else cout<<e[pos].id<<endl,exit(0);
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++) e[i].id=i,e[i].x=read();
	sort(e+1,e+1+n,cmp);
	for(int i=1;i<n;i++) h[e[i+1].x-e[i].x]++;
	if(h[e[2].x-e[1].x]==n-1) cout<<e[1].id<<endl,exit(0); //特判不用删的情况
	if(h[e[2].x-e[1].x]==n-2&&e[n].x-e[n-1].x!=e[2].x-e[1].x) cout<<e[n].id<<endl,exit(0); //特判结尾删的情况
	if(h[e[3].x-e[2].x]==n-2&&e[2].x-e[1].x!=e[3].x-e[2].x) cout<<e[1].id<<endl,exit(0); //特判开头删的情况
	for(int i=1;i<n;i++) if((h[e[i+1].x-e[i].x]==n-3||h[e[i+1].x-e[i].x]==n-2)&&!vst[e[i+1].x-e[i].x]) vst[e[i+1].x-e[i].x]=1,check(e[i+1].x-e[i].x); //check公差次数为n-3和n-2的情况
	puts("-1");
}

```

---

## 作者：hzy_2012 (赞：0)

### 题目思路：模拟

~~有点简单~~  
我们只用先排序，然后依次对比然后计数判断即可。  
排序用 sort 即可，这一步不难大家都可以想到 。
然后依次考虑
```a[i]-a[i+1]!=a[i+1]-a[i+2]) && (a[i]-a[i+1]==a[i+1]-a[i+3])```
考虑在排序后的数组内删除数字以达到目的
## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[1001]; 
int pd(){
	int f=0,x=0;
	for(int i=1;i<=n;i++){
		if((a[i]-a[i+1]!=a[i+1]-a[i+2]) && (a[i]-a[i+1]==a[i+1]-a[i+3])) f++,x=i+1; 
		if(f>1)return -1;
	}
	return x;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	cout<<pd()+1;
	return 0;
}

```

---

## 作者：_Lazy_whr_ (赞：0)

直接贪心即可。

首先先特判一下答案是 $1$ 或 $2$ 的情况。

然后直接排序，看一下到了哪一个位置破坏了等差性，并判断能不能将它改成一个合适的数，如果能并且后面的序列都满足等差性答案就是这个位置，否则无解。
```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

int n;
pair <int, int> a[200010];

map <int, int> mp;

bool Cmp (const pair <int, int> &p, const pair <int, int> &q) {return p.second < q.second; }

bool Check() {
	for (int i = 3; i <= n; i++) {
		if (a[i].second - a[i - 1].second != a[2].second - a[1].second) return false;
	}
	return true;
}

bool Check_ans (int x) {
	vector <int> v;
	for (int i = 1; i <= n; i++) {
		if (i != x) v.push_back(a[i].second);
	}
	for (int i = 2; i < n - 1; i++) {
		if (v[i] - v[i - 1] != v[1] - v[0]) return false;
	}
	return true;
} 

main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].second;
		a[i].first = i;
	}
	sort(a + 1, a + 1 + n, Cmp);
	if (Check_ans(1)) {cout << a[1].first << endl; return 0; }
	if (Check_ans(2)) {cout << a[2].first << endl; return 0; }
	int d = a[2].second - a[1].second;
	int flag = 0;
	for (int i = 3; i <= n; i++) {
		if (a[i].second - a[i - 1].second != d) {
			if (i == n) {
				if (flag == 0) {cout << a[n].first << endl; return 0; }
				else {cout << -1 << endl; return 0; }
			} else {
				if (flag == 0 && a[i + 1].second - a[i - 1].second == d) {
					flag = i;
					i++;
				}
				else {cout << -1 << endl; return 0; }
			}
		}
	}
	cout << a[flag].first << endl;
	return 0;
}
```

---

## 作者：Disjoint_cat (赞：0)

题目传送门：[LG](https://www.luogu.com.cn/problem/CF1185D)，[CF](http://codeforces.com/problemset/problem/1185/D)

## CF1185D Extra Element

### 1. 题意

- 给你一个长度为 $n$ 的数列 $a$，问能否从 $a$ 中删除一个数，使剩下 $(n-1)$ 个数能重排成一个等差数列。（好像都没注意到原题中数列叫 $b$）

- $n\le2\times10^5,\left\vert a_i\right\vert\le10^9$

### 2. 解法

不会有人连要先排序都想不到吧。

这里给出一种**除去排序** $O(n)$ 的算法。

---

如果我们能确定数列中两个数的值，我们就可以求出公差，进而求出整个数列。

于是我们想到~~分论讨类~~分类讨论。

- 如果同时保留 $a_1$ 和 $a_2$：

此时，公差 $d=a_2-a_1$。此时，对于每个 $2\le i<n$，应有 $a_{i+1}-a_i=d$。

如果不满足，则说明应该删除 $a_{i+1}$，此时有 $a_{i+2}-a_i=d$。

若仍不满足，或已经删除了一个数，则说明此情况无解。

否则，记录删除位置 $pos=i+1$。

如果遍历到 $i=n-1$ 都没有产生矛盾，则说明此情况有解。如果 $pos$ 被更新过，直接返回 $pos$。否则说明 $a$ 本身就是等差数列，返回 $1$ 或 $n$ 都可以。

- 如果删除 $a_1$ 或 $a_2$：

如果删 $a_1$，则 $d=a_3-a_2$，如果删 $a_2$，则 $d=a_3-a_1$。

此时直接暴力检查，不需要记录 $pos$（因为已经删掉一个数了）。

---

复杂度分析：对于讨论的过程，前一种情况只需要扫一遍数组，后者扫两遍，时间复杂度为 $O(n)$。加上排序，总复杂度为 $O(n\log n)$。

### 3. 细节

1. 输入（省略 $n$）为 `1 2 3 4 6`，答案为 $5$。此时，前一种情况在 $i=4$ 时，$a_{i+1}-a_i\ne d$。此时 $a_{i+2}$ 不存在，不应计算 $a_{i+2}-a_i$，应直接按满足处理，或让 $a_{n+1}$ 等于 $a_{n-1}+d$（想想为啥可以这样）。

2. 题目让你输出**原数列中的下标**，不是删除的数值，更不是排序后数列的下标。

### 4. Code

> Talk is cheap, show me the code. ~~码风奇丑。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,a[N],pos,a_[N];
int sol()
{
	sort(a+1,a+n+1);
	int d=a[2]-a[1];//keep a[1] & a[2]
	a[n+1]=a[n-1]+d;//上面说的
	for(int i=2;i<n;i++)
		if(a[i+1]-a[i]!=d)
			if(a[i+2]-a[i]==d&&!pos)pos=++i;
			else
			{
				int ok=1;
				d=a[3]-a[2];//delete a[1]
				for(int i=4;i<=n;i++)
					if(a[i]-a[i-1]!=d)
					{
						ok=0;
						break;
					}
				if(ok)return 1;
				ok=1;
				d=a[3]-a[1];//delete a[2]
				for(int i=4;i<=n;i++)
					if(a[i]-a[i-1]!=d)
					{
						ok=0;
						break;
					}
				if(ok)return 2;
				return 1919810;//no solution
			}
	if(pos)return pos;
	else return n;
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	memcpy(a_,a,sizeof(a));
	int ans=sol();
	if(ans==1919810)puts("-1");
	else
	{
		for(int i=1;i<=n;i++)//输出原数组下标
			if(a_[i]==a[ans])return cout<<i,0;
	}
	return 0;
}
```

---

