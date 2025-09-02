# Alice and the Cake

## 题目描述

Alice has a cake, and she is going to cut it. She will perform the following operation $ n-1 $ times: choose a piece of the cake (initially, the cake is all one piece) with weight $ w\ge 2 $ and cut it into two smaller pieces of weight $ \lfloor\frac{w}{2}\rfloor $ and $ \lceil\frac{w}{2}\rceil $ ( $ \lfloor x \rfloor $ and $ \lceil x \rceil $ denote [floor and ceiling functions](https://en.wikipedia.org/wiki/Floor_and_ceiling_functions), respectively).

After cutting the cake in $ n $ pieces, she will line up these $ n $ pieces on a table in an arbitrary order. Let $ a_i $ be the weight of the $ i $ -th piece in the line.

You are given the array $ a $ . Determine whether there exists an initial weight and sequence of operations which results in $ a $ .

## 说明/提示

In the first test case, it's possible to get the array $ a $ by performing $ 0 $ operations on a cake with weight $ 327 $ .

In the second test case, it's not possible to get the array $ a $ .

In the third test case, it's possible to get the array $ a $ by performing $ 1 $ operation on a cake with weight $ 1\,970\,429\,473 $ :

- Cut it in half, so that the weights are $ [985\,214\,736, 985\,214\,737] $ .

 Note that the starting weight can be greater than $ 10^9 $ .In the fourth test case, it's possible to get the array $ a $ by performing $ 2 $ operations on a cake with weight $ 6 $ :

- Cut it in half, so that the weights are $ [3,3] $ .
- Cut one of the two pieces with weight $ 3 $ , so that the new weights are $ [1, 2, 3] $ which is equivalent to $ [2, 3, 1] $ up to reordering.

## 样例 #1

### 输入

```
14
1
327
2
869 541
2
985214736 985214737
3
2 3 1
3
2 3 3
6
1 1 1 1 1 1
6
100 100 100 100 100 100
8
100 100 100 100 100 100 100 100
8
2 16 1 8 64 1 4 32
10
1 2 4 7 1 1 1 1 7 2
10
7 1 1 1 3 1 3 3 2 3
10
1 4 4 1 1 1 3 3 3 1
10
2 3 2 2 1 2 2 2 2 2
4
999999999 999999999 999999999 999999999```

### 输出

```
YES
NO
YES
YES
NO
YES
NO
YES
YES
YES
YES
NO
NO
YES```

# 题解

## 作者：_Fatalis_ (赞：7)

### Solution

~~暴 力 是不可能不打的。~~

这道题目有两种暴力方法。

一种从合并角度看，将相邻的两个数依次合并，看是否能合并完成。

但我选择的是更直观的暴力打法。

将总和依次分解，想到每一次的分解结果要是有对应的数字就消掉，剩下的分解，那么用 `map` 维护当前还需要处理的对应数字，一个 `bfs` 可以解决。

请注意，若分解个数大于 $n$ 次后，必然是有些数字分解不了，那么这时候直接 `return`，以减小空间 & 时间。~~如果不处理会 TLE。~~

空间 $O(n)$，时间 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,sum;
map<int,int> fk;
queue<int>q;

bool bfs()
{
    while(!q.empty()) q.pop();
    q.push(sum);
    while(!q.empty())
    {
        int lst=q.front();q.pop();
        if(fk[lst]) fk[lst]--;
        else
        {
            if(lst==1||q.size()>2*n) return false;
            int hl=lst/2,hr=lst/2+(lst%2);
            q.push(hl),q.push(hr);
        }
    }
    return true;
}

signed main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int k;sum=0;fk.clear();
        cin>>n;
        for(int i=1;i<=n;i++) cin>>k,sum+=k,fk[k]++;
        if(bfs()) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
```

---

## 作者：RocksonLee (赞：3)


## Problem

[Luogu](https://www.luogu.com.cn/problem/CF1654C)

[Codeforces](https://codeforces.com/contest/1654/problem/C)

## Solution

给你一串数字，这串数字是由一个很大的数字分割出来的，然后你需要检查是否合法。

分割方式就是对半分，如果不能对半分，那么一个向上取整，一个向下取整。

你就会想着如何把数字合起来，如果没法合起来就是不合法。

然而这种做法有个问题。

> 1 1 1 1 1 1

类似这个串，就可以 ban 掉这个做法了。

所以我们换种思路。

一个数如果是奇数，那么可以分成两个数，而这两个数加起来就是原来的数，下面证一下：

如果是奇数，那么 $\lceil \frac {w}{2} \rceil + \lfloor \frac {w}{2} \rfloor = \frac {w+1}{2} + \frac {w-1}{2} = w$。

如果是偶数，那么 $\lceil \frac {w}{2} \rceil + \lfloor \frac {w}{2} \rfloor = \frac {w}{2} + \frac {w}{2} = w$。

所以我们将所有的数字加起来，然后一个一个分。

由于序列会很多种情况，我们需要来 **模拟** 他的思路分割。
。
我的串是 $q$，目标串是 $p$，用 $maxx(x)$ 代表某个 $x$ 串中最大的数

如果 $maxx(q) > maxx(p)$，那就是我这个最大的数还需要再细分，对半分完后还需要放回我自己的串中。

如果 $maxx(q) = maxx(p)$，那么这两个串中最大的数就是匹配好的数字，我们把他们从两个串中拿开。

如果 $maxx(q) < maxx(p)$，那么我就分不到他的情况了，连我最大的数都比目标串小了，再分就更小，剩下的数怎么细分也无济于事。

我们要怎么 **高效** 寻找这个最大的数字呢。

`multiset` 和 `priority queue` 都是比较好的选择。

我这里用的是 **优先队列** 。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define il inline
#define INF 0x3f3f3f3f
#define cl(a, b) memset(a, b, sizeof(a))
typedef long long ll;
typedef unsigned long long ull;

#define int ll

priority_queue<int> q, p;

int t, n, temp, tot;

bool flag;

signed main()
{
    scanf("%lld", &t);
    for (int kkz = 0; kkz < t; kkz++)
    {
        tot = 0;
        flag = true;
        while (!q.empty()) q.pop();
        while (!p.empty()) p.pop();
        scanf("%lld", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%lld", &temp);
            tot += temp;
            q.push(temp);
        }
        p.push(tot);
        while (!q.empty() && !p.empty() && flag)
        {
            if (q.top() == p.top()) q.pop(), p.pop();
            if (q.top() > p.top()) flag = false;
            if (q.top() < p.top())
            {
                p.push(p.top() % 2 == 0 ? p.top() / 2 : p.top() / 2);
                p.push(p.top() % 2 == 0 ? p.top() / 2 : p.top() / 2 + 1);
                p.pop();
            }
        }
        if (flag) printf("yes\n");
        else printf("no\n");
    }
    return 0;
}
```


---

## 作者：0xFF (赞：2)

#### 题目大意


------------
有一个重量为 $w$ 的蛋糕，每次切割会把这块蛋糕分成 $ \left\lfloor\frac{w}{2}\right\rfloor$ 和 $\left\lceil\frac{w}{2}\right\rceil$ 两块。现给定一个长度为 $n$ 的序列 $a$，问序列 $a$ 中的数能否拼出最开始重量为 $w$ 的蛋糕。

#### 思路分析


------------
统计出 $\sum a_i$，按题意 ```bfs``` 即可。将序列 $a$ 排序，首先将 $\sum a_i$ 入队，每次将取出队头判断，如果队头的数恰好与 $a_n$ 相等，就 ```n--```，然后拆分成 $ \left\lfloor\frac{w}{2}\right\rfloor$ 和 $\left\lceil\frac{w}{2}\right\rceil$ 两数放到对尾，若队头的数小于 $a_n$ 直接跳出即可。

#### 代码实现


------------
```cpp
#include<iostream>
#include<algorithm>
#include<queue>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}
int n;
int a[200010];
bool cmp(int x,int y){
	return x<y;
}
priority_queue<int> q;
int main(){
	int T = read();
	while(T--){
		n = read();
		int tot = 0;
		for(int i=1;i<=n;i++){
			a[i] = read();
			tot += a[i];
		}
		q.push(tot);
		sort(a + 1 , a + n + 1 , cmp);
		while(n>0){
			int k = q.top();
			if(k == a[n]){
				n--;
			}
			else if( k < a[n]){
				break;
			}
			else{
				q.push(k/2);
				q.push((k+1)/2);
			}
			q.pop();
		}
		if(q.empty()){
			printf("Yes\n");
		}
		else{
			printf("No\n");
			while(!q.empty()){
				q.pop();
			}
		}
	}
	return 0;
}
```


---

## 作者：Disjoint_cat (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1654C)

首先我们发现，因为 $\left\lfloor\frac{w}{2}\right\rfloor+\left\lceil\frac{w}{2}\right\rceil=w$，所以我们知道原蛋糕重量一定为 $\sum a_i$。所以，我们可以先从初始的 $1$ 块蛋糕开始模拟切。

为了降低复杂度，我们考虑将蛋糕的大小排序（这样方便查找），并用 ```priority_queue``` 储存现在的蛋糕。假设 $s$ 为要切出的最大的蛋糕重量，$t$ 为现有的最大的蛋糕的重量。

- $s>t$，则一定无解。
- $s=t$，则删除这两块蛋糕之后再执行。
- $s<t$，则切一下最大的蛋糕再执行。

不断执行此过程即可，直到 $s>t$ 或蛋糕切完。复杂度为 $O(nlogn)$。

**十年 OI 一场空，没开 ```long long``` 见祖宗！**

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int T,n,t;
ll a[200005],sum,fr;
priority_queue<ll>q;
int main()
{
	cin>>T;
	while(T--)
	{
		scanf("%d",&n);
		t=1,sum=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
			sum+=a[i];
		}
		sort(a+1,a+n+1,greater<ll>());
		q.push(sum);
		fr=sum;
		while(t<=n&&fr>=a[t])
		{
			while(!q.empty()&&t<=n&&q.top()==a[t])q.pop(),t++;
			if(q.empty()||t>n)break;
			fr=q.top();
			q.pop();
			q.push((ll)(fr/2.0));
			q.push(ceil(fr/2.0));
		}
		if(t==n+1&&q.empty())puts("yes");
		else puts("no");
		while(!q.empty())q.pop();
	}
	return 0;
}
```


---

## 作者：Avocadooo (赞：0)

### 1.审题

题目说一次操作将数 $ w \geq 2 $ 转换为 $ \lfloor\frac{w}{2}\rfloor $ 和 $ \lceil\frac{w}{2}\rceil $ 。

也就是偶数分为两个 $ \frac{w}{2} $，奇数分为最接近 $ \frac{w}{2} $ 的一个奇数一个偶数。

看是否能通过一个数得到这样一个序列。

### 2.基本思路

先考虑直接拿原数列合并检查可行性。

但是在合并时有一个问题：若要合并 $ x $ 和另外一个数，而序列里现在还有 $ w $ 和 $ w \pm 1 $ 这三个数，我们应该选哪一个来合并呢？这自然成了一个难以解决的问题。

故我们考虑将过程逆序，即求出序列和 $ S=\sum\limits_{i=1}^{n}a_i $，用 $ S $ 去拆分检查可行性。

### 3.进一步思考

思路即是在拆分 $ S $ 的过程中看原序列中是否存在这个数，若存在，将当前数与原序列中的数抵消，反之，再将其进行拆分。最后检查原序列所有数是否都被抵消即可。

考虑用一个大根堆维护 $ S $ 经过多次拆分得到的数，并将原序列按从大到小排序（不难理解，因为我们是由较大的数拆分为较小的数，抵消过程也一定是由大到小）。

另外，有一个细节值得注意。就是当被分解数值为 $ 1 $ 时，我们不可以将它再进行分解。

时间复杂度 $ \Theta(n \log n) $。

### 4.std

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
typedef long long ll;
int a[200005];
int n;
ll _and;
queue<ll> q;
priority_queue<ll> q2;
void check()
{
	while(!q.empty())
	{
		while(q.size() && q2.size() && q2.top()!=1 && q.front()<q2.top())
		{
			ll t=q2.top(); q2.pop();
			q2.push((t+1)>>1); q2.push(t>>1);
		}
		if(q.empty() || q2.empty()) return;
		if(q.front()==q2.top()) q.pop(),q2.pop();
		else return;
	}
}
signed main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		while(!q.empty()) q.pop();
		while(!q2.empty()) q2.pop();
		_and=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",a+i),_and+=a[i];
		if(n==1)//这里对 n=1 进行一个特判
		{
			puts("YES");
			continue;
		}
		sort(a+1,a+n+1);
		for(int i=n;i>=1;i--) q.push(a[i]);
		q2.push(_and);
		check();
		if(q.empty()) puts("YES");
		else puts("NO");
	}
}
```

---

## 作者：AsanoSaki (赞：0)

**【分析】**
****
假设存在某个重量为 $sum$ 的蛋糕能够切出所给的排列，那么 $sum=a_1+a_2+\dots +a_n$ 。我们记 $minv$ 为排列中的最小重量。

我们使用哈希表 $ids$ 记录排列中每一种重量出现的次数，也就是有几块这种重量的蛋糕，然后我们从 $sum$ 开始切，每次切出题意要求的两个重量 $a,b$ 。

 - 如果 $a,b$ 中的任何一个小于排列中的最小重量 $minv$ ，说明一定切不出这个排列了，就可以直接结束这个切蛋糕的过程了；
 - 如果 $ids[a]\ne0$ ，说明切出了排列中的某一块，那么将 $ids[a]--$ ，并记录切出了在排列中的蛋糕的块数 $cnt+1$ ，对于 $b$ 的处理也一样；
 - 如果 $ids[a]=0$ ，说明这一块不是在排列中出现的，那么加入到队列中，下次还要继续切。

由于切出了比 $minv$ 小的蛋糕就无解，因此我们可以使用一个小根堆，每次先切最小的蛋糕，这样如果是无解情况我们会最早发现。

当切完所有蛋糕后，如果切出的在排列中的蛋糕数 $cnt==n$ ，那么说明我们切出了这个排列，输出 `YES` ，否则输出 `NO` 。
****
**【代码】**
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <unordered_map>
#define LL long long
using namespace std;

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		int n;
		scanf("%d", &n);
		unordered_map<LL, int> ids;
		priority_queue<LL, vector<LL>, greater<LL>> Q;
		LL sum = 0;
		int minv = 1e9, cnt = 0;
		for (int i = 0; i < n; i++) { int x; scanf("%d", &x); sum += x; minv = min(minv, x); ids[x]++; }
		Q.push(sum);
		while (Q.size())
		{
			LL t = Q.top(); Q.pop();
			if (ids[t]) { ids[t]--, cnt++; continue; }
			LL a, b;
			if (t % 2) a = t / 2 + 1, b = t / 2;
			else a = b = t / 2;
			if (ids[a]) ids[a]--, cnt++;
			else if (a < minv) break;
			else Q.push(a);
			if (ids[b]) ids[b]--, cnt++;
			else if (b < minv) break;
			else Q.push(b);
		}
		if (cnt == n) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：0)

### Preface

典中典了属实是。

### Analysis

首先，每次合并最小的两个是错的，Hack：

```
6
1 1 1 1 1 1
```

发现我们很难合并，那我们就拆最终的数，判断是否能够拆成目前的这些数。

具体地，我们将一开始的数存入 `std::map` 并求和，将和进行拆分。当对于一个数 $x$ 拆分时，判断是否在 map 里：若有直接用掉，否则拆成 $\lfloor\frac{x}{2}\rfloor$ 和 $\lceil\frac{x}{2}\rceil$ 递归拆分。 

时间 $O(n\log n)$

### Code

[Link](https://codeforces.com/contest/1654/submission/150703782)

---

## 作者：听取MLE声一片 (赞：0)

一个很另类的做法。

很明显，蛋糕的总质量是不变的，而蛋糕拼合比较麻烦，所以我就想到了把蛋糕切。

首先把序列从大到小排序，然后把总质量扔到一个堆里面。每次操作取出堆的堆顶，切一下，然后把堆顶删除。如果两块新出现的蛋糕是当前序列最大，就把数列中最大的删除，否则加入堆。这样，如果当前堆的最大值比当前序列的最大值小，则显然无解。

正确性就是，这个过程保证了还原切的过程，如果当前蛋糕最大小于序列最大，显然无解。

其实可以写个 `map` 来不止删除最大值，可以更快，~~不过我懒就没写。~~

代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=2e5+10;
int n,m,a[N];
signed main()
{
	int T=read();
	while(T--){
		n=read();
		priority_queue<int>b;
		int flag=1;
		m=0;
		for(int i=1;i<=n;i++){
			a[i]=read();
			m+=a[i];
		}
		sort(a+1,a+n+1);
		b.push(m);
		int l=n;
		while(l&&!b.empty()){
			int u=b.top();
			b.pop();
            if(a[l]>u){
                flag=0;
                break;
            }
			if(a[l]==u){
				l--;
				continue;
			}
			int x=(u+1)/2,y=u/2;
			if(x!=a[l])
				b.push(x);
			if(x==a[l])
				l--;
			if(y!=a[l])
				b.push(y);	
			if(y==a[l])
				l--;
			//cout<<x<<' '<<y<<' '<<a[l]<<endl;
		}
		if(l!=0)
			flag=0;
		if(flag)
			cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}

```

---

## 作者：bmatrix (赞：0)

## 题意
有一些蛋糕，最开始只有一块。每次可以选择质量为 $x(x\ge2)$ 的一块，将其切成 $\left\lfloor\frac x2\right\rfloor$ 和 $\left\lceil\frac x2\right\rceil$ 两块。现在给定切 $n-1$ 次后的结果，判断能否通过最开始的一块切出来。
## 思路
容易发现，每切一次，总质量都不会改变。因此，可以一开始直接确定蛋糕初始质量 $s=\sum_{i=1}^na_i$。

将 $a$ 中的每个元素的出现次数存进一个 `map` 里。对于任意质量 $sum$ 进行以下分类讨论：

- 如果 $sum$ 在 `map` 里，则将其出现次数 $-1$，返回真。
- 如果 $sum$ 不在 `map` 里且 $sum=1$，由于不能再切了，即不可能再生成 `map` 里存在的元素，因此返回假。
- 如果 $sum$ 不在 `map` 里且 $sum\ge2$，则将其切开后分别递归处理，返回两次递归结果的逻辑与。

但这样裸的 DFS 显然会 TLE，因此还要另开一个全局变量 $m$，记录现在已经切出来了多少块，当 $m>n$ 时，直接返回假。

此外数据范围 $a_i\le1e9,n\le2e5$，加起来肯定会爆 `int`，所以要开 `long long`。
## 代码
```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
map<ll,int>mp;
int n,m;
inline void div(ll x,ll &a,ll &b){
    if(x&1)a=x/2,b=a+1;
    else a=b=x/2;
}
bool dfs(ll sum){
    if(mp[sum])return 1;
    else if(sum==1)return 0;
    ll x,y;div(sum,x,y);m++;
    if(m>n)return 0;
    bool ans=1;
    if(mp[x])mp[x]--;
    else ans&=dfs(x);
    if(mp[y])mp[y]--;
    else ans&=dfs(y);
    return ans;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    //freopen("out","w",stdout);
    int t;cin>>t;
    while(t--){
        cin>>n;ll sum=0;
        for(int i=1;i<=n;i++){int x;cin>>x;mp[x]++;sum+=x;}
        m=1;
        cout<<(dfs(sum)?"Yes\n":"No\n");
        mp.clear();
    }
    return 0;
}
```
时间复杂度：显然由于有 $m$ 的存在，递归的复杂度一定是 $O(n)$，外加 `map` 的一个 $\log$，总复杂度 $O(n\log n)$。

---

## 作者：__vector__ (赞：0)

## 题目大意：  
Alice 初始有一个蛋糕，之后将会进行 $n-1$ 次操作。她每次都会选一块蛋糕，设这块蛋糕的大小为 $w$，那么她就将这块蛋糕切成两块大小分别为 $\lfloor \frac{w}{2}\rfloor,\lceil \frac{w}{2} \rceil$ 的蛋糕。给定一个切好的蛋糕序列 $a$，$a_i$ 代表第 $i$ 个蛋糕的重量。问有没有一个初始的蛋糕，使得经过一定的操作可以得到这个蛋糕序列。  
## 题目分析：  
必须要知道的：$w = \lfloor \frac{w}{2}\rfloor + \lceil \frac{w}{2} \rceil$  
显然，初始的那个蛋糕的重量一定是现在已有的蛋糕重量的总和，记为 $sum$。  
可以使用 dfs 来求解。dfs 定义如下：  
```cpp
bool dfs(long long x)
```  
它的参数的意思就是当前切到的蛋糕的大小，首先判断当前蛋糕大小 $x$ 是否出现在给定的蛋糕序列中，如果确实出现，那么返回 ```1``` 即可，代表没问题。  
然后，判断 $x$ 是否小于等于 $1$，如果是，那么代表无法继续往下分，返回 ```0```，代表不行。  
下一步，就是分别 dfs 由当前蛋糕切成的两块蛋糕即可，也就是（$sum2$ 是 $x$ 除以 $2$ 下取整）：  
```cpp
return dfs(sum2+(x&1))&&dfs(sum2);
```     
其实 dfs 的本质就是模拟切的过程，一旦某一个蛋糕不能往下切而且对应不上给定的切完的蛋糕序列，那么给定的序列一定是错的。  
## 注意：  
最后的返回部分，要先判断 ```dfs(sum2+(x&1))``` 这个部分的返回值是否为 ```0```，如果是，那么不用执行 ```dfs(sum2)``` 这一部分了，不然复杂度爆炸。  
当然，写成这样：  
```cpp
return dfs(sum2+(x&1))&&dfs(sum2);
```   
也是可以的，因为 ```&&``` 运算符的特性，如果前面的返回 ```0``` 就不会执行后面的了。    
此处感谢 @VinstaG173 大佬。  
## AC 代码：  
```cpp
#include <bits/stdc++.h>//
using namespace std;
#define int long long
const int maxn=2e5+5;
int a[maxn];
int t;
int n;
int sum;
map<int,int> im;
bool dfs(int x)
{
    if(im[x])
    {
        im[x]--;
        return 1;
    }
    if(x==1)return 0;
    int sum2=x>>1;
     return dfs(sum2+(x&1))&&dfs(sum2);
}
signed main()
{
    scanf("%lld",&t);
    while(t--)
    {
        sum=0;
        scanf("%lld",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%lld",&a[i]);
            sum+=a[i];
            im[a[i]]++;
        }
        if(dfs(sum))printf("YES\n");
        else printf("NO\n");
        for(int i=1;i<=n;i++)
        {
            im[a[i]]=0;
        }
    }
    return 0;
}
```


---

