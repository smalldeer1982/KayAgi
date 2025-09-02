# Power Walking

## 题目描述

将 $n$ 个数 $a_1$ 至 $a_n$ 分成 $k$ 组，求每组中去重后的元素个数之和的最小值。

## 样例 #1

### 输入

```
2
3
1 1 2
6
5 1 2 2 2 4```

### 输出

```
2 2 3 
4 4 4 4 5 6```

# 题解

## 作者：cqbztz2 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1642B)

[不会更好的阅读体验](https://www.luogu.com.cn/blog/493271/solution-cf1642b)

# Thinking

样例观察题。

发现若电池有 $ p $ 种不同的类型，则$ k \leq p $ 时答案都为 $ p $ 。

若 $ k $ 继续增加，答案也依次增加 $ 1 $ 。

样例也可以观察出同样的规律。

比较水的 B 题。

# Coding

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  const int N=300005;
  int t,n,a[N],tot;
  map<int,int> m;
  signed main(){
      cin>>t;
      while(t--){
          tot=0;
          m.clear();
          scanf("%d",&n);
          for(int i=1;i<=n;i++){
              scanf("%d",&a[i]);
              if(m[a[i]]==0){
                  tot++;
              }
              m[a[i]]=1;
          }
          for(int i=1;i<=tot;i++){
              printf("%d ",tot);
          }
          for(int i=tot+1;i<=n;i++){
              printf("%d ",i);
          }
          putchar('\n');
      }
      return 0;
  }
```


---

## 作者：0xFF (赞：3)

#### 题目大意


------------
给定一个数字序列，将其分成 $k$ 个区间，定义每个区间的代价为其中不同数字的个数，最小化 $k$ 个区间的代价和。

$1 \leq n \leq 3 \cdot 10^{5}$，$1\le k \le n$。


#### 思路分析


------------
首先统计出初始区间中有多少个不同的元素设为 $cnt$，当 $k \le cnt$ 时答案为 $cnt$，因为我们可以把相同的元素尽量放在同一个的区间里所以答案为 $cnt$。当 $k>cnt$ 时，我们就不得不把相同的元素放在不同的集合当中了，所以此时的答案为 $k$。

可以使用 set 来统计区间内有多少个不同的元素，注意每次清空 set 即可。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#include<cstdlib>
#define ll long long
using namespace std;
const int N = 5e5 + 10;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
    return x*f;
}
set<int> s;
ll n,a[N];
int main(){
	int T = read();
	while(T--){
		s.clear();
		int n = read();
		for(int i=1;i<=n;i++){
			a[i] = read();
			s.insert(a[i]); 
		}
		int cnt = s.size();
		for(int i=1;i<=n;i++){
			if(i <= cnt) printf("%d",cnt);
			else printf("%d",i);
			putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：Suzt_ilymtics (赞：1)

### Description

> 给你 $n$ 个数，把它们分到 $k$ 个集合里，定义一个集合的价值为集合中有多少种不同的数。求出当 $k = 1,2,...,n$ 时划分得到的最小价值。注意，一个集合不能为空。

### Solution

显然，同一种数分到一个集合是最优的。

设数的种数为 $x$，对于每个 $k$ 的答案为 $\max \{ x, k \}$。

当集合数小于数的种数时，也不会有一种数分到两个集合的情况，所以答案时数的种数。

当集合数大于数的种数时，就要从其他集合里拿出一个来放进新集合，每个集合中只有一种数，所以答案是集合个数。

### Code

依旧是部分代码：

```cpp
int n;
int a[MAXN], date[MAXN];
int cnt[MAXN];

void Main() {
    n = read();
    for(int i = 1; i <= n; ++i) a[i] = date[i] = read();
    sort(date + 1, date + n + 1);
    int Cnt = unique(date + 1, date + n + 1) - date - 1;
    for(int i = 1; i <= n; ++i) a[i] = lower_bound(date + 1, date + Cnt + 1, a[i]) - date;
    for(int i = 1; i <= n; ++i) cnt[a[i]] ++;
    int res = 0;
    for(int i = 1; i <= n; ++i) {
        res += (cnt[i] > 0);
    }
    for(int i = 1; i <= n; ++i) {
        printf("%d ", max(i, res));
    }
    puts("");
    for(int i = 1; i <= n; ++i) cnt[a[i]] --;
}

int main()
{
    int T = read();
    while(T--) Main();
    return 0;
}
```

---

## 作者：hank0402 (赞：0)

~~比赛时没看懂，卡了好久~~其实是一道非常简单的题。

### 题目大意：

将 $n$ 个数分成 $k$ 组，求每一组不同元素个数之和的最小值，$k\in [1,n]$.

### 题解：

经过简单的思考，每组内都是相同的元素时，不管 $k$ 是多少，答案都是最优的，因为不可能有一组不同元素个数为 $0$. 

于是，我们记这 $n$ 个数共有 $res$ 个不同元素，经过上面的分析，若 $k\le res$ 答案都为 $res$.

此后，每增加一组，就从任意一个元素个数 $\ge2$ 的组里抽出一个给新增的组，答案加一。

### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 300005
typedef long long ll;
int T, a[N], n;
int main() {
	cin >> T;
	while(T --) {
		cin >> n;
		for(int i = 1; i <= n; ++i) cin >> a[i];
		sort(a + 1, a + n + 1);
		int res = 0;
		for(int i = 2; i <= n + 1; ++i) {
			if(a[i] != a[i - 1]) res ++; //算出res
		}
		for(int i = 1; i <= res; ++i) cout << res << ' '; 
		int lst = res;
		for(int i = res + 1; i <= n; ++i) {
			cout << lst + 1 << ' '; //按题解的方法计算
			lst ++;
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：c20231020 (赞：0)

### 题目链接
[luogu](https://www.luogu.com.cn/problem/CF1642B)

[codeforces](https://codeforces.ml/contest/1642/problem/B)

### 题目大意
给出一个长度为 $n$ 的集合 $a$，求出将这个集合分为 $1 \sim n$ 个集合时，每个集合不同元素之和的最小值。

**数据范围**：$1 \le t \le 3 \times 10^5,1 \le n \le 3 \times 10^5,1 \le a_i \le 10^9,1 \le \sum{n} \le 3 \times 10^5$。

### 思路
贪心思路可以想到，我们尽量将同一种元素放在一个集合中，实在不行才拆开。所以我们可以统计元素的种数 $m$，当集合数量 $k$ 不大于 $m$ 时输出 $m$，大于 $m$ 时输出 $k$。

举个栗子：$n = 7$，集合元素为 $1,1,1,2,2,3,4$。

+ $k = 1:\{1,1,1,2,2,3,4\},ans = m = 4$；
+ $k = 2:\{1,1,1,2,2,3\},\{4\},ans = m = 4$；
+ $k = 3:\{1,1,1,2,2\},\{3\},\{4\},ans = m = 4$；
+ $k = 4:\{1,1,1\},\{2,2\},\{3\},\{4\},ans = m = 4$；
+ $k = 5:\{1,1,1\},\{2\},\{2\},\{3\},\{4\},ans = k = 5$；
+ $k = 6:\{1,1\},\{1\},\{2\},\{2\},\{3\},\{4\},ans = k = 6$；
+ $k = 7:\{1\},\{1\},\{1\},\{2\},\{2\},\{3\},\{4\},ans = k = 7$；

$m$可以通过map标记得到。

时间复杂度：$O(\sum{n} \times log(\sum{n}))$。

---
上代码——
#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
map<ll,ll> mp;
ll n,a,t,m;
inline ll re(){
	ll x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return x;
}
int main(){
	t=re();
	while(t--){
		n=re();
		for(ll i=1;i<=n;i++){
			a=re();
			if(mp[a]==0)mp[a]++,m++;//标记，计算m
		}
		for(ll i=1;i<=n;i++){
			if(i>m)printf("%lld ",i);
			else printf("%lld ",m);
			//当集合数量 k 不大于 m 时输出 m，大于 m 时输出 k
		}
		printf("\n");
		mp.clear();
		m=0;
		a=0;
		//别忘了初始化！
	}
	return 0;
}
```

---

## 作者：windflower (赞：0)

简要题意：  
>把 n 个数分给 $k(1\le k\le n)$ 个小盆友，每个小盆友的力量就是他所拥有的数字的种类的数量，对每个 k 求出小盆友力量总和的最小值。

首先我们来看一下每个数加到一个小盆友手上时对总力量的贡献。若是小盆友没有这个数，则贡献为 1 ，反之贡献为 0 。为了让力量总和最少，将相同的数加到同一个小盆友手上总是最优的。而对于互不相同的数字，不论怎样分配，小盆友的力量总和总是固定的。因此我们可以将数字分成 t 堆，相同的数字放在同一堆，每一堆不论放在哪里它对总力量的贡献总是 1 。因此当堆数大于等于小盆友人数时，堆数就是总力量的最小值。当堆数跟小盆友人数一样后，随着小盆友人数的增多，势必要从某一堆中取出一个数给新的小盆友，而这个操作为使总力量 $+1$ ，因此每多出几个小盆友，总力量的最小值就增加多少。  
在对上述分析进行简化整合就可以得出最小总力量的公式： 
$$minstrength=\max(t,k)$$  
分堆过程可以用 STL 容器中的集合来很方便地实现  
附 AC 代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a;
int main(){
	cin>>t;
	while(t--){
		set<int> A;
		cin>>n;
		for(int i=0;i<n;i++){
			cin>>a;
			A.insert(a);
		}
		int m=A.size();
		for(int i=1;i<=n;i++)printf("%d%c",max(i,m)," \n"[i==n]);
	}
	return 0;
}
```


---

## 作者：ttq012 (赞：0)

思维题。

我们需要让儿童强度的和最小，那么我们可以将每一个儿童的道具尽可能的相同。

当 $k = 1$ 的时候，让 $1$ 号儿童得到所有的道具。

当 $k = 2$ 的时候，让 $2$ 号儿童得到所有的 $1$ 号儿童的编号最小的道具。

比如说，一开始 $1$ 号儿童得到了这些道具：$\texttt{1 1 2 3 3 3 4}$，让 $2$ 号儿童得到所有的 $1$ 号儿童的编号最小的道具 $1$ 之后，那么 $1$ 号儿童的道具变成了：$\texttt{2 3 3 3 4}$，$2$ 号儿童变成了 $\texttt{1 1}$。

同理，$3$ 号儿童得到所有的 $1$ 号儿童**当前**所有的编号最小的道具后，$1$ 号儿童变成 $\texttt{3 3 3 4}$，$3$ 号儿童变成 $2$。

$4$ 号儿童得到的所有 $1$ 号儿童**当前**所有编号最小的道具之后，$1$ 号儿童变成 $4$，$4$ 号儿童变成 $\texttt{3  3 3}$。

如果再来一个 $5$ 号儿童，拿走此时 $1$ 号儿童**当前**所有编号最小的道具，那么 $1$ 号儿童就没有道具了，是不可以的。

这个时候 $5$ 号儿童只能随便拿一个，那么拿走一个道具必然会令答案增加 $1$。

那么我们求出不同的道具的个数 $x$，并输出 $x$ 这个数 $x$ 次，剩下的每一次将 $x$ 自增 $1$ 并且输出即可。

**Code**

```cpp
//C++11
#include <bits/stdc++.h>

using namespace std;

struct node {
    int x, y;
    bool operator < (const node & _1) {
        return y < _1.y;
    }
};

node make_node(int a, int b) {
    node tt;
    tt.x = a, tt.y = b;
    return tt;
}

int a[1000010];

signed main() {
    int t;
    cin >> t;
    while (t --) {
        int n;
        scanf ("%d", &n);
        unordered_map <int, int> mp;
        for (int i = 1; i <= n; i ++) {
            scanf ("%d", &a[i]);
            mp[a[i]] ++;
        }
        vector <node> arr;
        int cnt = 0;
        for (auto [u, v] : mp) {
            cnt ++;
        }
        int j = 1;
        for (int i = 1; i <= cnt; i ++, j ++) printf ("%d ", cnt);
        for (; j <= n; j ++) printf ("%d ", ++ cnt);
        puts("");
    }
    return 0;
}
```


---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1642B)

题意：有 $n$ 个人，第 $i$ 个人的力量种类为 $a_i$。现在要把这些力量分给 $k$ 个人，要求每个人至少分到一种力量，并且所有力量都要分出去。每个人的力量值为他所拥有的力量的种类数量。现在对于每个 $1 \le k \le n$，输出分完之后所有人的力量值之和的最小值。

考虑线性或 1 log 解决这个问题。不难看出为了使答案最小，应该多把同种力量给一个人。

设 $n$ 个人中有 $s$ 种不同力量。那么当 $k \le s$ 时，答案就是 $s$，原因显然。

当 $k > s$ 时，可以把 $s$ 种力量分给 $s$ 个人，剩下的 $k-s$ 个人每个人分一种力量，再把同种力量分配给已有这种力量的人，所以每个人最多拿一种力量，答案为 $k$。

但是统计力量种数的时候要开个桶。这个题的 #7 刻意卡掉了 unordered_map 的哈希，所以只能开 map。

于是复杂度为 $O( \sum n \log n)$。

---

## 作者：IYSY2009I (赞：0)

我们考虑如何分配，才能使每一种相等 $a_i$ （原文那该怎么翻译有人知道吗）对小朋友的强度贡献之和最小。

很显然，当所有相等的 $a_i$ 都分配给一个小朋友的时候，$a_i$ 对小朋友强度贡献之和最小。所以答案就相当于有多少个不同的数字出现在了数组 $a$ 里。

但注意每个小朋友都至少有一个 $a_i$，所以答案要对 $k$ 取 $\max$。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
bool cmp(int x,int y){
	return x<y;
}
void cf(){
	int n=read();
	int a[300005];
	for(int i=1;i<=n;i++)	
		a[i]=read();
	sort(a+1,a+n+1,cmp);
	int num=0;
	for(int i=1;i<=n;i++)
		if(a[i]!=a[i-1]) num++;
	for(int k=1;k<=n;k++)
		printf("%d ",max(k,num));
	printf("\n");
}
int main(){
	int t=read();
	for(int i=1;i<=t;i++)
		cf();
	return 0;
}
```


---

## 作者：heaksicn (赞：0)

## 1 题意
将 $n$ 个数分成 $k$ 组，每组的贡献是这组中不同的数的个数。

对于从 $1$ 到 $n$ 的每个 $k$，最小化每组的贡献之和。

多组数据。
## 2 思路
考虑样例中的第二组数据。

首先将其排序，得到 $[1,2,2,2,4,5]$。

将每个数分成一组，得到 $[1],[2,2,2],[4],[5]$，此时 $k=4,ans=4$。

那么对于每个 $k$，如果 $k\leq4$，那么答案也一定为 $4$ （考虑将其中的几组合并）。

对于 $k>4$ 的情况，我们可以将 $[2,2,2]$ 拆成几组，此时答案为 $k$。

那么思路就显而易见了：

1. 找出不同的数的个数，设为 $x$。

2. 对于 $1$ 到 $x$ 的 $k$，输出 $x$。

3. 对于 $x+1$ 到 $n$ 的 $k$，输出 $k$。

时间复杂度 $O(Tn\log n)$。
## 3 code
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int T; 
int n,a[300001];
int main(){
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		sort(a+1,a+n+1);//排序
		int ans=0,lst=-1;
		for(int i=1;i<=n;i++){
			if(a[i]!=lst) ans++;//不同数的个数
			lst=a[i];
		}
		for(int i=1;i<=ans;i++) cout<<ans<<" ";//1-ans的情况输出ans
		for(int i=ans+1;i<=n;i++) cout<<i<<" ";//ans+1-n的情况输出i
		cout<<endl; 
	}
	return 0;
}

```


---

## 作者：jiangtaizhe001 (赞：0)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/15932365.html)  
[题目传送门](https://codeforces.com/problemset/problem/1642/B)  
## 题目大意
有一个长度为 $n$ 的数组 $a$，现在你需要把这个数组 $n$ 个的元素分成 $k$ 部分，每一段的对答案的贡献是这一部分不同的数的个数，最后的答案是所有的贡献之和。  
现在需要求 $k=1,2,\dots,n$ 的答案。   
数据范围：$n\le 3\times10^5,\sum n\le 3\times10^5,a_i\le10^9$
## 题目解析
首先我们先求出整个序列有几个不同的数字，假设这个数字为 $m$。
当 $k\le m$ 的时候，我们可以做到每个数字只出现在一个部分内，这样答案就是 $m$。  
当 $k>m$ 的时候，我们在 $k=m$ 构造的基础上将 $k-m$ 个元素单独放在一个部分内，答案就是 $k$。

核心代码：
```cpp
int n,m,a[maxn];
void work(){
	n=read(); int i; for(i=1;i<=n;i++) a[i]=read(); sort(a+1,a+n+1); m=1;
	for(i=2;i<=n;i++) if(a[i]!=a[i-1]) m++;
	for(i=1;i<=n;i++)
		if(i<=m) print(m),pc(' ');
		else print(i),pc(' ');
	pc('\n'); return;
}
```

---

