# [ABC228D] Linear Probing

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc228/tasks/abc228_d

$ N\ =\ 2^{20} $ 項からなる数列 $ A\ =\ (A_0,\ A_1,\ \dots,\ A_{N\ -\ 1}) $ があります。はじめ、全ての要素は $ -1 $ です。

$ Q $ 個のクエリを順番に処理してください。$ i\ \,\ (1\ \leq\ i\ \leq\ Q) $ 個目のクエリは $ t_i\ =\ 1 $ または $ t_i\ =\ 2 $ を満たす整数 $ t_i $ および整数 $ x_i $ で表され、内容は以下の通りです。

- $ t_i\ =\ 1 $ のとき、以下の処理を順番に行う。
  1. 整数 $ h $ を $ h\ =\ x_i $ で定める。
  2. $ A_{h\ \bmod\ N}\ \neq\ -1 $ である間、$ h $ の値を $ 1 $ 増やすことを繰り返す。この問題の制約下でこの操作が有限回で終了することは証明できる。
  3. $ A_{h\ \bmod\ N} $ の値を $ x_i $ で書き換える。
- $ t_i\ =\ 2 $ のとき、その時点での $ A_{x_i\ \bmod\ N} $ の値を出力する。

なお、整数 $ a,\ b $ に対し、$ a $ を $ b $ で割った余りを $ a\ \bmod\ b $ と表します。

## 说明/提示

### 制約

- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ t_i\ \in\ \{\ 1,\ 2\ \}\ \,\ (1\ \leq\ i\ \leq\ Q) $
- $ 0\ \leq\ x_i\ \leq\ 10^{18}\ \,\ (1\ \leq\ i\ \leq\ Q) $
- $ t_i\ =\ 2 $ であるような $ i\ \,\ (1\ \leq\ i\ \leq\ Q) $ が $ 1 $ つ以上存在する。
- 入力は全て整数である。

### Sample Explanation 1

$ x_1\ \bmod\ N\ =\ 1 $ であるので、$ 1 $ 番目のクエリによって $ A_1\ =\ 1048577 $ となります。 $ 2 $ 番目のクエリにおいて、はじめ $ h\ =\ x_2 $ ですが、$ A_{h\ \bmod\ N}\ =\ A_{1}\ \neq\ -1 $ であるので $ h $ の値を $ 1 $ 増やします。すると $ A_{h\ \bmod\ N}\ =\ A_{2}\ =\ -1 $ となるので、このクエリによって $ A_2\ =\ 1 $ となります。 $ 3 $ 番目のクエリにおいて、$ A_{x_3\ \bmod\ N}\ =\ A_{1}\ =\ 1048577 $ を出力します。 $ 4 $ 番目のクエリにおいて、$ A_{x_4\ \bmod\ N}\ =\ A_{3}\ =\ -1 $ を出力します。 この問題において $ N\ =\ 2^{20}\ =\ 1048576 $ は定数であり、入力では与えられないことに注意してください。

## 样例 #1

### 输入

```
4
1 1048577
1 1
2 2097153
2 3```

### 输出

```
1048577
-1```

# 题解

## 作者：__UrFnr__ (赞：1)

**题目思路**：

这道题我们可以考虑用并查集，当下标为 $i$，我们设 $f_i$ 为 $i$ 右边第一个值为 $-1$ 的下标。

一开始，$f_i=i$。

当 $i$ 的值被操作 $1$ 改变后，$f_i=f_{i+1}\bmod2^{20}$。

程序实现复杂度实现远远不超过时间限制 4s，可以放心使用该解法。

---

## 作者：Autumn_Dream (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc228_d)

**思路：**

可以用并查集通过此题。设 $f_i$ 为下标为 $i$ 的右边第一个值为 ${-1}$ 的下标。对于 $f$:
- 初始时，$f_i=i$；
- 当 $i$ 的值被操作 $1$ 改动时，$f_i=f_{i+1}\bmod 2^{20}$。

本题时间限制为 $4\mathfrak{s}$，复杂度 $\mathcal{O} (2^{20}+q)$ 能过。

---

## 作者：CarroT5656 (赞：1)

问题在于如何快速查找某一个位置及其右面的第一个值为 $-1$ 的下标。

设当前下标为 $i$，下标 $i$ 及其右面第一个值为 $-1$ 的下表为 $f_i$。

如果 $i$ 的权值没有被改动，显然 $f_i=i$。

那么 $f_i$ 改动过后，显然需要更新 $f_i$ 的值。

因为 $a_i$ 已经不是 $-1$ 了，不难得到，$f_i$ 一定不是 $i$ 且在 $i$ 的右面。

根据 $f_i$ 的定义可以得到，$f_i=f_{(i+1)\bmod n}$。

观察 $f_i$ 的式子，发现相当于一个并查集。用并查集维护 $f$ 即可。

时间复杂度 $O(n+q)$，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 1050000
ll n=1048576,q,a[N],fa[N];
ll fnd(ll x){return (fa[x]==x?x:fa[x]=fnd(fa[x]));}
int main(){
	for(ll i=1;i<=n;i++) fa[i]=i,a[i]=-1;
	scanf("%lld",&q);
	while(q--){
		ll op,x,p;
		scanf("%lld%lld",&op,&x);
		p=fnd(x%n+1);
		if(op==1){
			if(a[p]==-1) a[p]=x;
			fa[p]=(p==n?1:p+1);
		}
		else printf("%lld\n",a[x%n+1]);
	}
	return 0;
}
```

---

## 作者：tsh_qwq (赞：0)

一道不错的题，~~居然还能写题解~~，考试时想了好久想出了用**并查集**优化此题。

本题的最大难点就是如何快速查找 $a_i$ 及其右面的第一个值为 $−1$ 的位置。

**划重点**，可以用数组 f 单独记录右侧第一个值为 $-1$ 的下标，可以简单理解为一个节点的**父亲节点**，初始化 $f_i=i$ 。

接下来只需要注意模就可以了。

可以得出：$f_i = f_{i+1} \bmod n$ 。

时间复杂度：$O(n+q)$ 。

给出代码，可以通过。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n=1<<20,q,a[1050000],fa[1050000];
int find(int x)//板子 
{
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
signed main()
{
	for(int i=1;i<=n;i++)fa[i]=i,a[i]=-1;
	cin>>q;
	while(q--)
	{
		int t,x,p;
		cin>>t>>x;
		p=find(x%n+1);
		if(t==1)
		{
			if(a[p]==-1) a[p]=x;
			if(p==n)fa[p]=1;
			else fa[p]=p+1;
		}
		else cout<<a[x%n+1]<<endl;
	}
	return 0;
}

```

蒟蒻的第一篇题解，望通过 qwq

---

## 作者：__Ginka__ (赞：0)

## 代码思路

### 数据结构初始化
使用一个 $set$ 结构 $st$ 来维护所有空槽的下标。$set$ 会保持下标的有序性，方便我们找到下一个可以填充的空槽。

### 操作1的实现
计算 $x \mod n$，得到当前操作的下标 $o$。
使用 $set$ 的二分查找方法查找大于等于 $o$ 的最小空槽下标。如果找不到合适的槽，则从 $set$ 的开头开始查找。

更新该槽为 $x$，并从 $set$ 中删除该下标，表示该位置已经被填充。

### 操作2的实现
对于查询操作，直接输出值。

### 时间复杂度
总的时间复杂度为 $O(q \log n)$。


代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1048576;  //N=2^20
ll a[N+5];             //数组a用于存储数列值
set<ll> st;            //用于存储当前可以填充的下标
ll q, t, x;
int main()
{
    memset(a,-1,sizeof(a)); 
    scanf("%lld",&q);
    // 初始时，所有下标[0, N-1]都是可用的，因此加入集合st中
    for(int i=0;i<N;i++) st.insert(i);
    while(q--)
	{
        scanf("%lld%lld",&t,&x);
        if(t==2) printf("%lld\n",a[x%N]);
        if(t==1)
		{
            ll o=x%N;
            //第一个大于等于o的下标
            set<ll>::iterator id=st.lower_bound(o);
            //找不到合适的下标，说明当前没有更大的下标，则回到集合的最小下标
            if(id==st.end()) id=st.begin();
            a[*id]=x;
            st.erase(*id);
            continue;
        }
    }
    return 0;
}

```

---

## 作者：__Creeper__ (赞：0)

### 思路

如果直接用 while 循环遍历，无疑会超时。我们发现，程序会每次从 $1$ 开始往后找 $−1$ 的点，但是这是会重复寻找的，我们可以直接跳过不为 $-1$ 的点。定义 $f_{i}$ 为下标 $i$ 及其右面第一个值为 $−1$ 的下标，初始值 $f_{i} = i$。当 $a_{i}$ 被改动时，显然需要更新 $f_{i}$ 的值。因为 $a_{i}$ 已经不是 $−1$ 了，不难得到，$f_{i}$ 一定不是 $i$ 且在 $i$ 的右面。根据 $f_{i}$ 的定义可以得到:
- $f_{i} = f_{i+1} \bmod n $（其实就是并查集）

### Code
```cpp
#include <bits/stdc++.h>
#define int long long // 开long long
using namespace std;

int n, m, q;
const int N = 1 << 20;
int f[N], a[N];

int find ( int x ) // 并查集
{
	if ( f[x] == x ) return x;
	return f[x] = find ( f[x] );
}

signed main()
{
	cin >> q;
	for ( int i = 0; i < N; i++ ) a[i] = -1, f[i] = i;
	while ( q-- )
	{
		int op, x;
		cin >> op >> x;
		if ( op == 1 )
		{
			int i = find ( x % N );
			a[i] = x;
			f[i] = find ( ( i + 1 ) % N );
		}
		else
		{
			cout << a[x % N] << '\n';
		}
	}
	return 0;
}
```

---

## 作者：lovely_qiqi (赞：0)

## 思路

分别对两个操作进行优化。

+ 操作 $1$

我们定义 $f_i$ 为从 $i$ 开始第一个为 $-1$ 的位置。

$a$ 为题目中的权值。

根据定义： $f_i=f_{i+1\bmod n}$ 

（如果 $f_i\neq i$ 时）

因为会更新权值时才满足这一公式。

$f_i$ 是从 $i$ 开始第一个为 $-1$ 的位置。

而 $f_{i+1}$ 是从 $i+1$ 开始第一个为 $-1$ 的位置。

至于为什么要对 $n$ 取模是因为可能在最后一个要回到第一个了。

同时更新 $a$ 的值。

+ 操作 $2$ 

如果操作 $1$ 理解了想必操作 $2$ 就不难了。

直接打印 $a$ 就完了。

其实就是并查集。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long//十年OI一场空，不开LONGLONG见祖宗
#define n 1048576//2^20
#define N 1500010//数组开得比n大一些
using namespace std;
int q,op,xx,p,fa[N],a[N];//fa并查集，a为值
int find(int x){//并查集板子
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
signed main(){//代码有错误（2）请勿抄袭，看了思路的应该能改
	scanf("%lld",&q);
	for(int i=1;i<=n;i++) fa[i]=i,a[i]=1;
	for(int i=1;i<=q;i++){
		scanf("%lld%lld",&op,&xx);
		p=find(xx%n+1);
		if(op==1){
			if(a[p]==-1) a[p]=xx;
			fa[p]=(p+1)%n;
		}
		else printf("%lld\n",a[xx%n]);
	}
    return 0;
}

```

---

## 作者：lhs_chris (赞：0)

[题目](https://www.luogu.com.cn/problem/AT_abc228_d)


首先我们读题目，会知道问题在于如何快速解决操作 `1 x`。
# 暴力
直接按照题目的意思，用 while 循环去枚举，当 $\texttt{h}$ 满足 $a_{h \bmod n}=-1$ 时，令 $a_{h\bmod n}=x$。

但是显然会超时的。
```cpp
#include<bits/stdc++.h>
#include<queue>
#include<set>
#include<stack>
#include<vector>
#define ll long long
using namespace std;
const int N=1048999;
const int M=1048576;//2^20
const int inf=0x3f3f3f3f;
ll a[N],n,x,s;
int main()
{
	scanf("%lld",&n);
	memset(a,-1,sizeof a);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&s,&x);
		if(s==1)
		{	
			ll h=x;
			ll q=h%M;
			while(a[q]!=-1)
			{
				q=h%M;
				h++;
			}
			a[q]=x;
		}
		else
		{
			ll q=x%M;
			printf("%lld\n",a[q]);
		}
	}
	return 0;
}
```
# 优化
我们发现，如果重复多次 `1 1` 的操作，程序会每次从 $1$ 开始往后找 $-1$ 的点，但是这是会**重复寻找**的。

例如：第一次 `1 1` 操作，找到的是 $1$ 这个点，第二次操作找到的是 $1$ **后面的** $2$，第三次操作找到的是 $2$ **后面的** $3$……

所以说当重复多次 `1 1` 操作之后，每次都会走一段重复的路，以寻找 $-1$，但是这段路我们之前走过，所以是清楚走过的这段路是绝对不可能为 $-1$ 的。如果我们可以不跑这段路，是不是可以快很多？

## 做法
我们用一个 $\texttt{to}$ 数组，记录当前点的下一个 $-1$ 点是多少。

那么，我们每一次寻找 $-1$ 的点可以直接去寻找当前点的 $\texttt{to}$，这样可以快很多。

# AC代码
```cpp
#include<bits/stdc++.h>
#include<queue>
#include<set>
#include<stack>
#include<vector>
#define ll long long
using namespace std;
const int N=1048999;
const int M=1048576;//2^20
const int inf=0x3f3f3f3f;
ll a[N],n,x,s,f,to[N];//to[i]代表 i 下一个 -1 点的下标 
void dfs(ll num,ll xx)
{
	if(a[num]==-1)//寻找 -1 点 
	{
		f=num;
		a[num]=xx;
		return;
	}
	dfs(to[num],xx);
	to[num]=f;//回来的时候顺便把路上的所有点的下一个 -1 点更新为 f(最新的-1点)。  
}
int main()
{
	scanf("%lld",&n);
	memset(a,-1,sizeof a);
	//初始化 
	for(int i=0;i<M-1;i++)to[i]=i+1;
	to[M-1]=0;//M-1的下一个点是M，但是M%M=0 ，所以m-1下一个点为0 
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&s,&x);
		if(s==1)
		{	
			ll h=x;
			ll q=h%M;
			dfs(q,x); 	
		}
		else
		{
			ll q=x%M;
			printf("%lld\n",a[q]);
		}
	}
	return 0;
}
```

---

## 作者：harmis_yz (赞：0)

## 分析

水题，为什么没人做。

令 $f_i$ 表示当 $x \bmod n=i$ 时，$i$ 最后能跳的的位置。则有初始时：$f_i=i$。对于修改操作，就是 $f_{x \bmod n}$，然后把 $val_{f_{x \bmod n}}$ 改成 $x$。由于现在的 $f_{n \bmod n}$ 上的值已经不是 $-1$ 了，根据题意，我们需要将 $i+1$ 然后继续跳。所以很显然就是 $f_{x \bmod n}$ 变成 $f_{(f_{n \bmod n}+1)\bmod n}$。其实就是个并查集模板。注意一下取模问题即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,int>
#define x first
#define y second

il int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}

const int N=1<<20|1;
int q,fa[N],val[N];

il int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
il void solve(){
	q=read();
	for(re int i=0;i<N;++i) fa[i]=i,val[i]=-1;
	while(q--){
		int op=read(),x=read();
		if(op==1) val[find(x%(N-1))]=x,fa[find(x%(N-1))]=find((find(x%(N-1))+1)%(N-1));
		else printf("%lld\n",val[x%(N-1)]);
	}
	return ;
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：loser_seele (赞：0)

首先如果朴素实现这个哈希表肯定会寄，因为可能的哈希冲突可能非常多。

注意到我们可以尝试更快速找到第一个 $ h \bmod n $ 后不为 $ -1 $ 的下标 $ p $，初始的时候显然有 $ p_h=h $。当 $ val_h $ 不为 $ -1 $ 的时候不断令 $ h=p_h $ 即可。

问题在于怎么更新 $ p $ 数组，当执行一次赋值操作的时候显然 $ h $ 的位置被占用了，于是要占用下一个位置，即 $ p_h=p(k+1) $。

这个过程类似于并查集找父亲的过程，于是直接并查集实现模拟上述过程即可。

时间复杂度 $ \mathcal{O}(n+q) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
#define int long long
const int SIZE=1<<20;
int value[SIZE],fa[SIZE];
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
signed main() 
{
    int q;
    cin>>q;
    for(int i=0;i<SIZE;i++)
    value[i]=-1,fa[i]=i;
    while(q--) 
    {
        int t,x;
        cin>>t>>x;
        if (t==1) 
        {
            int i=find(x%SIZE);
            value[i]=x;
            fa[i]=find((i+1)%SIZE);
        }
        else 
        cout<<value[x%SIZE]<<'\n';
    }
}
```


---

