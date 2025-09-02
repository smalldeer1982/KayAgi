# [ABC378C] Repeating

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc378/tasks/abc378_c

给定一个长度为 $N$ 的正数序列  $A = (A_1, A_2, \ldots, A_N)$，请找出按照以下定义的长度为 $N$ 的序列 $B = (B_1, B_2, \ldots, B_N)$。

- 对于 $ i = 1, 2, \ldots, N$，给出 $B_i$ 定义如下：
  
  - 与 $A_i$ 相等的元素在 $i$ 之前出现的位置为 $b$。如果不存在这样的位置，则 $B_i = -1$。
  - 更具体地说，如果存在正整数 $j$，使得 $A_i = A_j$ 且 $j<i$ 存在，则 $B_i$ 是所有这样的 $j$ 中的最大值。如果不存在这样的 $j$，则 $B_i = -1$。。

## 说明/提示

### 约定

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 输入均为整数

### 样例解释

- $ i=1$：$A_1=1$ 前没有 $1$ 出现，因此 $B_1=-1$。
- $ i=2 $：$A_1=2$ 前没有 $2$ 出现，因此 $B_2=-1$。
- $ i=1 $：$A_1=1$ 前 $1$ 出现在 $A_1$，因此 $B_3=1$。
- $ i=1 $：$A_1=1$ 前 $1$ 出现在 $A_3$，因此 $B_4=3$。
- $ i=5 $：$A_5=3$ 前没有 $3$ 出现，因此 $B_5=-1$。

## 样例 #1

### 输入

```
5
1 2 1 1 3```

### 输出

```
-1 -1 1 3 -1```

## 样例 #2

### 输入

```
4
1 1000000000 1000000000 1```

### 输出

```
-1 -1 2 1```

# 题解

## 作者：ikunTLE (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc378_c)

### 思路

定义一个 `map` 或者 `unordered_map`，设其为 $m$，定义 $m_i$ 为数字 $i$ 在 $A$ 中最后出现的下标。

遍历 $1$ 到 $n$：

- 如果能在 $m$ 中找到 $A_i$，输出 $m_i$，并更新 $m_i$ 的值为 $i$。
- 否则输出 `-1`。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=2e5+10;
int a[N],b[N];
unordered_map<int,int>mp;
int main(){
	memset(b,-1,sizeof(b));
	int n=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	for(int i=1;i<=n;++i){
		if(mp.find(a[i])!=mp.end())
			b[i]=mp[a[i]];
		mp[a[i]]=i;
	}
	for(int i=1;i<=n;++i)
		printf("%d ",b[i]);
	printf("\n");
	return 0;
}
```

---

## 作者：xyz123 (赞：4)

本题需要维护一个 $10^9$ 的数组动态记录每个数上一次出现的位置。显然 $10^9$ 的数组开不下，因此使用动态开点线段树。如果想节约内存也能用平衡树。

Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200010;
int tree[N<<5],ls[N<<5],rs[N<<5],idx;
int n;
int a[N];
int query(int k,int l,int r,int x){
	if(l==r)	return tree[k];
	int mid=(l+r)>>1;
	if(x<=mid){
		if(ls[k])	return query(ls[k],l,mid,x);
		else	return -1;
	}
	else{
		if(rs[k])	return query(rs[k],mid+1,r,x);
		else	return -1;
	}
}
void update(int&k,int l,int r,int x,int v){
	if(!k)	k=++idx;
	if(l==r){
		tree[k]=v;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)	update(ls[k],l,mid,x,v);
	else	update(rs[k],mid+1,r,x,v);
}
int main(){
	idx=1;int rt=1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		printf("%d ",query(1,1,1000000000,a[i]));
		update(rt,1,1000000000,a[i],i);
	}
	return 0;
}
```

---

## 作者：Chenyanxi0829 (赞：1)

从前往后扫一遍，用 map 记录下之前出现过的所有值最后出现的位置，如果 map 里之前没有这个值就输出 `-1`，否则就输出 map 里存的这个值最后出现的位置。

### 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

int n, a;
map<int, int> h;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a, cout << (h.count(a) ? h[a] : -1) << ' ', h[a] = i;
  }
  return 0;
}
```

---

## 作者：WA2025 (赞：1)

## 题目传送门

[Luogu](/problem/AT_abc378_c) | [AtCoder](https://atcoder.jp/contests/abc378/tasks/abc378_c)

## 题意

给定长度为 $n$ 的数组 $A$，求出对于每个 $i(1\le i\le n)$，最后一个满足条件 $A_i=A_j$ 的 $j(1\le j\le n)$。

## 思路

用数组统计每一个数最后出现的位置，但是注意到题意 $1\le A_i\le 10^9$，也就是说，不能开大小为 $10^9$ 的数组，所以我们可以用 map 代替。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define Fast         ios::sync_with_stdio(false)
#define Made         return
#define By           0
#define TheSoundOfWA ;

unordered_map<int, int> mp;

int main() {
    Fast;

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        if (mp[x] == 0) cout << -1 << ' ';
        else cout << mp[x] << ' ';
        mp[x] = i;
    }

    Made By TheSoundOfWA
}
```

---

## 作者：sjh0626 (赞：1)

## 题意概括

给定你一个长度为 $N$ 的序列 $a$，对于每个 $a_i$ 都有一个对应的 $b_j$，$b_j$ 满足以下条件：

- 若 $b_j$ 存在，那么一定 $1 \le j < i$，并且 $b_j = a_i$.
- 若 $b_j$ 不存在，那么 $b_j$ 为 $-1$。

## 思路分析

可以使用 `unordered_map` 或者 `map` 来存储 $a_i$ 最后一次存在的位置，如果不存在则位置为 $0$。

## 代码解析

```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
using namespace std;
int n,a[200010];
unordered_map<int,int>m; //下标存储 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(m[a[i]]==0)cout<<-1; //若不存在 
		else cout<<m[a[i]]; //若存在 
		m[a[i]]=i; //存储下标 
		cout<<" ";
	}
	sjh0626s code;
}
```

---

## 作者：PineappleSummer (赞：1)

红题。

设 $f_x$ 为数字 $x$ 上一次出现的位置，判断 $f_{a_i}$ 是否为 $0$，如果不为 $0$，$b_i=f_{a_i}$，否则 $b_i=-1$。然后将 $f_{a_i}$ 更新为 $i$。

$f$ 用 `unordered_map` 实现即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
int n, a[N], b[N];
unordered_map <int, int> f;
signed main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (f[a[i]]) b[i] = f[a[i]];
        else b[i] = -1;
        f[a[i]] = i;
    }
    for (int i = 1; i <= n; ++i) cout << b[i] << ' ';
    return 0;
}
```

---

## 作者：hjyowl (赞：1)

### 题目大意

给定一个序列 $a$，求出 $a_i$ 之前第一个等于 $a_i$ 的值，记为 $b_i$，若没有，$b_i$ 等于 $-1$。

### 思路

首先暴力肯定是会超时的，$\Theta(n^2)$ 会炸。

我们可以用一个哈希表，对于 $x$ 映射在当前最后一次出现的位置。

然后我们只需要动态更新和维护哈希表就可以了。

时间复杂度 $\Theta(n \log n)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
int a[N],b[N];
map<int,int>mp;
map<int,bool>st;
bool debug = 0;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1;i <= n; i ++ ){
		cin >> a[i];
		if (!st[a[i]]){
			b[i] = -1;
		}
		else{
			b[i] = mp[a[i]];
		}
		st[a[i]] = 1;
		mp[a[i]] = i;
	}
	for (int i = 1; i <= n; i ++ ){
		cout << b[i] << " ";
	}
	return 0;
}
```

---

## 作者：hzxphy (赞：1)

妥妥的 ump 题。

# 大致结构
读入了 $n$ 个数，每一次记录读入的那个数的值的下表进行更新，由于数据很大，考虑用 umap 解决问题。

然后？就没有然后了。
```cpp
#include<bits/stdc++.h>
using namespace std;
unordered_map<int,int>ump;
int n;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int ai;scanf("%d",&ai);
        if(!ump.count(ai)){
            printf("-1 ");
            ump[ai]=i;
            continue;
        }
        printf("%d ",ump[ai]);
        ump[ai]=i;
    }
    return 0;
}

```

---

## 作者：jerry139com (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc378_c)

~~这道题也太简单了吧，不配放在 ABC 的 C 题。~~

首先先开个数组 $q_i$，存储 $i$ 上一次出现的下标。

初始值全部为 $-1$。（为了方便写代码，代码上的初始值为 $0$，并且在输出时特判）

每次输出后，把 $q_{a_i}$ 设为 $i$，也就是把上一个出现 $a_i$ 的下标更新。

由于这个数组要存很大的数组下标，所以使用 `map` 存放。

放上代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n,a[200009];
map<ll,ll> q;
int main() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) {
		if(q[a[i]]==0) cout<<"-1 ";
		else cout<<q[a[i]]<<" ";
		q[a[i]]=i;
	}
	return 0;
}
```

---

## 作者：kikilong_mamba (赞：0)

# [AT_abc378_c](https://atcoder.jp/contests/abc378/tasks/abc378_c)题解
## 解法分析
我们可以维护一个 unordered_map，记录每个值上一次出现的位置（如果是 $0$ 就表示没出现过），然后在查询的时候直接输出。

记得特判 $-1$。
## AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define rint register int
using namespace std;
inline int read()
{
	int a=0,b=0,c=getchar();
	while(!isdigit(c) && c!=-1) b|=(c==45),c=getchar();
	while(isdigit(c)) a=a*10+(c^48),c=getchar();
	return b?~(a-1):a;
}
void write(int a)
{
	if(a<0) putchar(45),a=-a;
	if(a>=10) write(a/10);
	putchar(a%10^48);
}
const int N=1e6+2;
//这上面的都不用看
int n,a;
unordered_map<int,int>m;
signed main()
{
	n=read();
	for(rint i=1;i<=n;++i)
	{
		a=read(); //输入a[i]
		write(m[a]?m[a]:-1); //输出答案，用三目运算符特判
		putchar(32); //换行
		m[a]=i; //更新
	}
}
```

---

## 作者：cyq32ent (赞：0)

题意：求每个数在数列中上次出现的位置。

方法：直接动态维护一个映射表，其中存储每个值上一次出现的位置即可。

下面的代码用到了一个特性：如果 `M` 中没有 `a` 这个键值，那么 `M[a]` 为 $0$。

```cpp
#include<iostream>
#include<map>
using namespace std;
int N,a,i=1;map<int,int>M;
int main(){
  cin>>N;
  for(;i<=N;i++){
    cin>>a;
    cout<<M[a]-1<<' ';
    M[a]=i+1;
  }
}

---

## 作者：Redamancy_Lydic (赞：0)

这道题让我们找到每个位置的数字前一次出现的位置。

我们显然可以遇到一个数字就存储其位置，然后动态的更新和查询。

我们可以开一个 `map` 容器来维护这个信息。让第一关键字为数值，第二关键字为下标，每次查询该元素在里面的第二关键字的值然后动态更新位置即可。

[提交记录](https://atcoder.jp/contests/abc378/submissions/59360051)

---

## 作者：Heldivis (赞：0)

## [ABC378C] Repeating

考虑用一个数组 `a[x]` 表示上一次 $x$ 出现的位置，初值为 $-1$，每次读入一个数更新 `a[x]` 数组即可。

但是题目要求 $1\le A_i \le 10^9$，不能开数组，使用 `std::map<int, int>` 记录，每次使用 `mp.count(x)` 查询是否出现过 $x$，如果出现输出 `mp[x]` 表示上一次出现的位置，否则输出 `-1` 表示没有出现过，同时每次更新 `mp[x]`。

时间复杂度 $O(n\log n)$。

代码：[赛时提交记录](https://atcoder.jp/contests/abc378/submissions/59358768)。

---

## 作者：MingRi_Doctor (赞：0)

## 思路:
本题可以使用 map。

先定义一个 map 数组 $mp$，并输入 $a_1,a_2,a_3,\cdots,a_n$。

判断 $mp_{a_i}$ 是否等于 $0$。如果不是，说明之前出现过与 $a_i$ 相同的数，输出 $mp_{a_i}$。最后将 $mp_a$ 设为 $i$，说明数字 $a_i$ 在第 $i$ 个出现了。
## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a;
map<int,int> mp;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		if(mp[a]!=0) cout<<mp[a]<<" ";//判断之前有没有出现过a
		else cout<<-1<<" ";
		mp[a]=i;//表示出现过a，并记录下标
	}
	return 0;
} 
```

---

## 作者：wuyouawa (赞：0)

### 题目大意

给定一个长度为 $N$ 的序列 $A$，对于每一个 $i(1 \le i \le n)$，找出一个 $j(1 \le j \le i)$，使得 $A_j=A_i$，不存在输出 $-1$。

### 思路

 map 模板题。

每输入一个数，判断在不在 map 里，如果在，就直接输出值，不在输出 $-1$。

再把这个数存到 map 里，注意是下标。

### CODE

[提交记录及代码](https://atcoder.jp/contests/abc378/submissions/59399292)

---

## 作者：sherry_lover (赞：0)

# AT_abc378_c [ABC378C] Repeating 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc378_c)

## 简要题意

给定一个序列 $A$，对每个 $A_i$ 求最大的 $j$ 满足 $A_i = A_j$，若不存在输出 $-1$。

## 思路

我们可以开一个 map 来记录下每个数上一次出现的位置，输出完答案更新一下即可。

代码很简单，时间复杂度 $O(n \log n)$，哈希完可以优化到线性。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
map<int,int> lst;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i = 1,x;i <= n;i++)
    {
        cin >> x;
        if(!lst[x]) cout << -1 << " ";
        else cout << lst[x] << " ";
        lst[x] = i;
    }
    return 0;
}
```

---

## 作者：Daniel_yao (赞：0)

# [[ABC378C] Repeating](https://www.luogu.com.cn/problem/AT_abc378_c)

用 $last_i$ 数组记录上一次 $a_i$ 出现的位置，每次动态更新，动态输出即可。

发现值域到达 $10^9$，直接无脑丢进 `map` 完事。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)

using namespace std;

const int N = 2e5 + 10;

int n, a[N];

map<int, int> last;

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n;
  For(i,1,n) cin >> a[i];
  For(i,1,n) {
    if(!last[a[i]]) {
      cout << "-1 ";
    } else cout << last[a[i]] << ' ';
    last[a[i]] = i;
  }
  return 0;
}
```

---

## 作者：bryce (赞：0)

## [C - Repeating](https://atcoder.jp/contests/abc378/tasks/abc378_c)
### 思路
设 $q_{a_i}$ 表示 $a_i$ 在当前扫描的前缀里出现最后的位置，如果遇到 $a_i$ 输出 $q_{a_i}$，然后将 $q_{a_i}$ 更新为 $i$，由于 $a_i$ 太大，用个 map 即可。
### 代码
```cpp
#include<iostream>
#include<algorithm>
#include<map>

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}

const int N = 2e5 + 10;
int n;
int a[N];
map<int, int> q;

signed main(){
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= n; i++){
        cout << (q[a[i]] == 0 ? -1 : q[a[i]]) << ' ';
        q[a[i]] = i;
    }
    return 0;
}
```

---

## 作者：Jasoncwx (赞：0)

[题目传送门！](/problem/AT_abc378_c)
## 题目思路
先定义一个 $b$ 数组，用 `map` 记录上一次出现的位置，刚开始没出现过的话就默认是 `-1`。

遍历的时候就把这个位置赋值到 $b$ 数组里。
## 代码

```cpp
map<int,int>mp;
int n=read();
int a[200005],b[200005];
for(int i=1;i<=n;i++)a[i]=read(),mp[a[i]]=-1;
for(int i=1;i<=n;i++){
	b[i]=mp[a[i]];
	mp[a[i]]=i;
}
for(int i=1;i<=n;i++)cout<<b[i]<<" ";
```

---

## 作者：lucasincyber (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc378_c)
## 思路
因为 $B$ 数组要求每一个数最后一次出现的下标，所以我们可以维护每一个数最后出现的下标，可因为 $a_i \le 10^9$，数组开不下，所以用 map 储存。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n;
int a[N], b[N];
map<int, int> lastPos;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++)
	{
		if (lastPos.count(a[i])) b[i] = lastPos[a[i]];
		else b[i] = -1;
		lastPos[a[i]] = i;
	}
	for (int i = 1; i <= n; i++) printf("%d ", b[i]);
	return 0;
}
```

---

## 作者：Binah_cyc (赞：0)

对于每一个数，一个十分直观的想法就是开一个数组记录每一个数上一次出现的位置。但是值域达到了 $10^9$，数组开不下。

介绍一个十分有用的封装数据结构：`map`。定义方式为 `map<Key Type,Value Type> name`，其中`Key Type`表示下标的数据类型，`Value Type`表示存储的数据类型，`name`表示名称，比如`map<int,int> x`，就是一个下标与存储的值均为`int`类型的数组。又比如`map<string,bool> vis`，就是一个下标为`string`，存储的值为`bool`的数组。

警告：`map`查询的复杂度为 $O(\log n)$，所以能用数组还是多用数组。

知道了这个，这个题就方便多了。直接使用`map`存储每一个数上一次出现的位置，遇到一个值的时候更新出现的位置即可。
代码：
```
// Problem: C - Repeating
// Contest: AtCoder - AtCoder Beginner Contest 378
// URL: https://atcoder.jp/contests/abc378/tasks/abc378_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Author: Binah_cyc

#include<bits/stdc++.h>
using namespace std;
int n;
map<int,int> pre;//pre[i]表示i位置上一次出现的位置
signed main(signed argc,char** argv)
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1,x;i<=n;i++)
	{
		cin>>x;
		if(!pre[x]) cout<<-1<<' ';//从来没有出现过，输出-1，避免了初始化
		else cout<<pre[x]<<' ';
		pre[x]=i;//更新上一次出现的位置
	}
	return 0;
}
```

---

## 作者：linjinkun (赞：0)

是一道非常简单（不过如果你不用 ```STL``` 应该不好写）的 ```STL``` 应用题。

需要应用的 ```STL``` 库函数：```map```。

[想知道 ```map``` 的用法，点这里。](https://blog.csdn.net/qq_48508278/article/details/118531197)

知道了 ```map``` 的用法后，这题就变得十分简单了，直接上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int>s;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		if(s.find(x) == s.end())//如果当前左边没有和自己相同的数字
		{
			printf("-1 ");//此时的b[i]值为-1
		}
		else
		{
			printf("%d ",s[x]);//此时b[i]值为离i最近的数的位置
		}
		s[x] = i;//然后直接更新当前数字目前最靠后的位置
	}
	return 0;
}
```

---

## 作者：sxm131011 (赞：0)

这题肯定不能暴力，需要开一个桶记最后出现位置。然后更新一下就行了。细节自己看程序。
```cpp
#include <bits/stdc++.h>
using namespace std;

int a[200005];

int main(){
	int n;
	cin>>n;
	
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	
	map<int,int> m;//记位置
	for(int i=1;i<=n;i++) m[a[i]]=-1;//赋值成-1，方便后面直接输出
	
	for(int i=1;i<=n;i++){
		cout<<m[a[i]]<<" ";
		m[a[i]]=i;//时时更新
	}
	
	return 0;
}
``````

---

