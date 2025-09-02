# [EC Final 2021] Fenwick Tree

## 题目描述

庞教授正在讲授关于 Fenwick 树（也称为二叉索引树）的课程。

在 Fenwick 树中，我们有一个长度为 $n$ 的数组 $c[1\ldots n]$，初始时全为零（对于任何 $1\le i\le n$，$c[i]=0$）。每次，庞教授可以对某个位置 $pos$（$1\leq pos \leq n$）和一个值 $val$ 调用以下过程：

```cpp
def update(pos, val):
    while (pos <= n):
        c[pos] += val
        pos += pos & (-pos)
```

注意，对于任何正整数 `pos`，`pos & (-pos)` 等于 `pos` 的最大 2 的幂。

在这个过程中，$val$ 可以是**任意实数**。在调用了若干次（零次或多次）后，庞教授忘记了数组 $c$ 中的确切值。他只记得对于每个从 $1$ 到 $n$ 的 $i$，$c[i]$ 是否为零。庞教授想知道，在假设他的记忆是准确的情况下，他调用该过程的最小可能次数。

## 说明/提示

对于第一个例子，庞教授可以依次调用 `update(1,1)`，`update(2,-1)`，`update(3,1)`。

对于第三个例子，庞教授可以依次调用 `update(1,1)`，`update(3,1)`，`update(5,1)`。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3
5
10110
5
00000
5
11111
```

### 输出

```
3
0
3
```

# 题解

## 作者：naroto2022 (赞：4)

# P9883题解

### 算法

- $c[]$ 其实就是树状数组，设其原数组是 $a[]$。
- 就是问 $a[]$ 最少有多少非零位置，才能使其生成的树状数组 $c[]$ 符合条件。
- $c[i]$ 的值实际上是所有使得 $j+(j \ \operatorname{and} \ (-j))=i$ 的 $c[j]$  的值加起来，再加上 $a[i]$。
- 如果 $j+(j \ \operatorname{and} \ (-j))=i$ 的 $c[j]$ 全是 $0$，但 $c[i]$ 非 $0$，那么 $a[i]$ 就必须非 $0$；
- 如果 $j+(j \ \operatorname{and} \ (-j))=i$ 的 $c[j]$ 只有一个非 $0$，但 $c[i]$ 为 $0$，那么 $a[i]$ 就必须非 $0$；
- 可以证明，其他情况下都可以让 $a[i]$ 为 $0$。

### 代码

```
#include<bits/stdc++.h>
const int N=1e5+5;
int n,a[N],b[N],ans;
char sc[N];
int main(){
	int T;
	scanf("%d",&T);
	for(;T--;){
	    scanf("%d %s",&n,sc+1);
	    ans=0;
	    for(int i=1; i<=n; i++) a[i]=sc[i]-'0',b[i]=0;
	    for(int i=1; i<=n; i++){
	        if(!b[i]&&a[i]||b[i]==1&&!a[i]) ++ans;
	        if(a[i]&&(i&-i)+i<=n) ++b[(i&-i)+i];
	    }
	    printf("%d\n",ans);
    }
	return 0;
}
```


---

## 作者：scp020 (赞：4)

# P9883 [EC Final 2021] Fenwick Tree 题解

本题首篇题解捏。

## 解法

显然，我们不可能在同一个位置上进行两次及以上的 `update(pos,val)` 操作，因为两次 `update(pos,val1)` 和 `update(pos,val2)` 操作等价于 `update(pos,val1+val2)` 操作，然后后者所用操作次数比前者少，所以更优。除此之外，显然我们不可能进行 `update(pos,0)` 操作，因为这对树状数组各位置的值没有影响。

我们设 $f_i$ 表示在所有 $j + j \& (-j) = i$ 有几个位置的目标状态是非 $0$。显然我们需要从 $f_1$ 计算到 $f_n$，因为位置 $i$ 是否进行 `update()` 影响到位置 $i + i \& (-i)$。现在分几种情况讨论。

1. 位置 $i$ 的目标状态是 $0$，且 $f_i = 0$。此时位置 $i$ 不需要修改。
2. 位置 $i$ 的目标状态是 $0$，且 $f_i = 1$。此时有一个位置对位置 $i$ 有影响，所以我们需要进行一次 `update(i,val)` 操作将值抵消掉。
3. 位置 $i$ 的目标状态是 $0$，且 $f_i \ge 2$，此时位置 $i$ 不需要修改，因为必定有方案使得这 $f_i$ 个值的和为 $0$。
4. 位置 $i$ 的目标状态是非 $0$，且 $f_i = 0$，此时需要进行一次 `update(i,val)` 操作将位置 $i$ 的值变为非 $0$。
5. 位置 $i$ 的目标状态是非 $0$，且 $f_i \ge 1$，此时位置 $i$ 不需要修改。

根据上述 $5$ 种情况整合后可得计算答案的方法：

```cpp
for(int i=1,j,cnt;i<=n;i++)
{
	if(st[i-1]=='1')
	{
		if(f[i]==0) ans++;
		if(i+lowbit(i)<=n) f[i+lowbit(i)]++;
	}else if(f[i]==1) ans++;
}
```

## 代码

```cpp
#include<bits/stdc++.h>
namespace fast_IO
{
	/**
	 * 快读快写
	*/
};
using namespace fast_IO;
int t,n,f[100010],ans;
std::string st;
inline int lowbit(int x)
{
	return x&(-x);
}
int main()
{
	in>>t;
	while(t--)
	{
		in>>n>>st,ans=0;
		for(int i=1;i<=n;i++) f[i]=0;
		for(int i=1,j,cnt;i<=n;i++)
		{
			if(st[i-1]=='1')
			{
				if(f[i]==0) ans++;
				if(i+lowbit(i)<=n) f[i+lowbit(i)]++;
			}else if(f[i]==1) ans++;
		}
		out<<ans<<'\n';
	}
	fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
	return 0;
}
```


---

## 作者：yl2026 (赞：3)

# 解决方法

1. `update` 函数其实是树状数组的修改功能  
2. $c[i]$ 其实就是树状数组  
3. `pos & (-pos)` 其实就是 `lowbit`  

维护一个 $cnt$ 数组，此时可以分类讨论一下：  

当 $c[i]$ 是 $0$ 时，对于 $cnt[i]$：  
$$
\begin{cases} 
  cnt[i] = 0 & \text{不改变}\\ 
  cnt[i] = 1 & \text{执行操作} \\ 
  cnt[i] \ge 2 & \text{不改变} 
\end{cases} 
$$  

因为当 $cnt[i]=1$ 时，需要把前面的影响抵消掉，如果 $cnt[i] \ge 2$，也可以抵消，他说是实数，所以 $0.5 + 0.5 = 1$ 是可行的。  

---  

当 $c[i]$ 是 $1$ 时，对于 $cnt[i]$：  
$$
\begin{cases} 
  cnt[i] = 0 & \text{执行操作}\\ 
  cnt[i] = 1 & \text{不改变} \\ 
  cnt[i] \ge 2 & \text{不改变} 
\end{cases} 
$$  

虽然执行 `update` 是要将所有 $lowbit \le n$ 都更新，但其实只要更新下一个，因为下一个也会给下一个的下一个更新 $\dots$，这样子，只需要 $O(1)$ 的时间复杂度就可以更新。  

记录一下 `ans` 就好了。  

---  

## 代码：  

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
const int MAXN = 1e5 + 7;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;

int t, n;
int cnt[MAXN], ans;

int lowbit(int x) {
    return x & -x;
}

string s;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> t;
    while (t--) {
        ans = 0;
        memset(cnt, 0, sizeof(cnt));
        cin >> n;
        cin >> s;
        for (int i = 1; i <= n; i++) {
            if (s[i - 1] == '0') {
                if (cnt[i] == 1)
                    ans++, cnt[i]++;
            } else {
                if (cnt[i] == 0)
                    ans++, cnt[i]++;
                int next = i + lowbit(i);
                if (next <= n)
                    cnt[next]++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

---

## 作者：tanruiqing (赞：1)

## 解题思路

有点贪心的味道。

这题我们可以考虑这几种情况：

对于这个点**初始**为 `1`：

1. 没有更改过，我们要将这里更改，答案累加。
2. 更改过 $1$ 次，我们不管（再改就无法维护最小次数）。
3. 更改过多次，只要为两次以上，我们就可以用任意数字抵消其增加的值（因为题目说可以增加任意实数），所以不用管。

对于这个**初始**点为 `0`：

1. 没改过，不管，如果更改，就会让答案非最优。
2. 改过一次，我们再改一次抵消差值，此时答案需要累加。
3. 改过多次，不管，只要为两次以上，我们就可以用任意数字抵消其增加的值（因为题目说可以增加任意实数），所以不用管。

综上所述，我们可以用一个 `cnt[i]` 记录这个位置更改过的次数，然后进行操作（上面已经总结出），最后输出答案（累加方法上面已经总结出）。

### AC 代码：

[AC 记录](https://www.luogu.com.cn/record/229355316)。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int t;
int a[500005];
int n,m;

int lb(int x){
	return x&-x;
}

string s;

int cnt[100005];//记录修改次数。

signed main(){
	cin.tie(0)->sync_with_stdio(false);
	cout.tie(0)->sync_with_stdio(false);
	cin>>t;//不用快读也可以过。
	while(t--){
		cin>>n;
		cin>>s;
		for(int i=1;i<=n;i++)cnt[i]=0;//多测需清空。
		int ans=0;//清空。
		for(int i=1;i<=n;i++){
			char c=s[i-1];//因为 lowbit 无法处理 0，所以需要将下标全部 +1。
			if(c=='1'){//如果这个位置是 1。
				if(cnt[i]==0)cnt[i]++,ans++;
				int nex=i+lb(i);
				if(nex<=n)cnt[nex]++;
			}else{//如果不是。
				if(cnt[i]==1)cnt[i]++,ans++;
			}
		}
		cout<<ans<<'\n';//输出。
	}
	return 0;
}
```

---

## 作者：SICKO (赞：1)

我们来看 Fenwick Tree，什么意思？翻译过来就是树状数组。

看到题目给出的伪代码，即使不知道英文意思也可以意识到这其实就是树状数组的修改问题。

不知道树状数组是什么的可以来看看我的博客。 

[树状数组学习日记](https://www.luogu.com.cn/blog/gjbd/shu-zhuang-shuo-zu-xue-xi-ri-ji-01-post)

但实际上即使你不知道树状数组是什么，也可以写这题。~~希寇就是当时不知道树状数组但写出来得~~。

好来看题目，题目告诉我们字符 `0` 表示这个数是零，`1` 表示这个数非零。我们思考：

- 修改当前的节点无论如何也**不会影响**到之前的节点，因为 lowbit 运算的结果最小为一（只影响父节点）。

- 如果一个节点被修改，立即还原接下来相连的父节点，那么被影响的节点**只有这个子节点**。

- 如果一个节点被修改两次且两次的**路径来源**（来自不同子树）不同，那么这个节点一定符合要求。

所以我们可以这么处理，我们先建一个树状数组，然后对给出的字符串，当当前位是 `1` 时，我们就修改其接下来相连的节点加上一（若是一个位置要修改但父节点不用，那么父节点处一定不匹配，如果子父节点都要而祖父节点不用，那么祖父节点处一定不匹配，这样处理我们可以将一个位置的修改与否仅关联到其子节点与当前位置要求）。

接下来让树与字符串两两匹配，如果树的当前位置结果大于等于 2，根据之前的处理，我们可以知道其一定符合我们思考的第三点，跳过当前位置即可，如果这两个值不同，说明我们就需要修改当前的位置，让操作数加一即可。

最后附上代码。

```c++
#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t; cin>>t;
    while(t--)
    {
        int n; string str;
        cin>>n>>str;
        vector<int> the_change(n+1);
        for(int i=1; i<=n; i++)
        {
            if(str[i-1] == '1' && i+(i&-i)<=n) the_change[i+(i&-i)]++;
        }
        long long ans=0;
        for(int i=1; i<=n; i++)
        {
            if(str[i-1] == '0' && the_change[i]==1) ans++;
            if(str[i-1] == '1' && the_change[i]==0) ans++;
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```


---

## 作者：Hhy140516 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9883)
# 分析
树状数组好题。

需要更新次数最少，所以最好是一个点更新完全，等其他点都已经发生了改变后再去修改，这样最后只需要修改一次。

按照上述原理，可以发现，一个上面的位置，一定会影响到后面的某些位置。

事实上每个点的变化只会向上传递。

然后观察目标串，无论如何最终答案都会和目标串相同。

所以我们只需要考虑最直接的牵制关系实现完成一步才能继续往后面推进，所以最终答案从左往右统计。

我们用 $cnt _ i$ 记录当前节点的最终目标 $s _ i$ 以及所有直接子节点的 $1$ 的个数。

接着分情况讨论。
## $s _ i = 0$
- $cnt _ i = 1$，子节点一定对 $i$ 产生了影响，为了抵消，花费一次操作 `res++`。
- $cnt _ i > 1$，多次操作，一定能够抵消。如 $cnt _ i = 3$，花两次减 $1$，那么最后花一次加 $2$，就一定能抵消。
- $cnt _ i = 0$，不用操作。
## $s _ i = 1$
- $cnt _ i = 1$，刚好子节点的操作可以上升到自己，所以不用额外操作。
- $cnt _ i > 1$，多次操作，同上。
- $cnt _ i = 0$，不用操作一定要抵消子节点的影响，所以 `res++`。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std ;
string s ;
int n ;
inline int read() //复制的，没意见吧（逃
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int lowbit(int x)
{
	return (x & -x) ;
}
int main()
{
	int t = read() ;
	while(t--)
	{
		n = read() ;
		cin >> s ;
		int res = 0 ;
		vector<int> cnt(n + 5) ;
		for( int i = 1 ; i <= n ; i++ )
		{
			if(s[i - 1] == '1')
			{
				if(cnt[i] == 0) res++ ;
				int low = i + lowbit(i) ;
				if(low <= n) cnt[low]++ ;
			}
			else
			{
				if(cnt[i] == 1) res++ ;
				int low = i - lowbit(i) ;
				if(low >= 1) cnt[low]++ ;
			}
		}
		cout << res << "\n" ;
	}
	return 0 ;
}
```

---

## 作者：sieve (赞：0)

## 题解：[P9883](https://www.luogu.com.cn/problem/P9883)

## 思路

- 如果最终目标 $s_i = 0$

  - $cnt_i = 1$ 子节点产生了影响，答案加一。
 
  - $cnt_i > 1$ 多次操作一定能够抵消。
 
  - $cnt_i = 0$ 不要操作。
 
- 如果最终目标 $s_i = 1$

  - $cnt_i = 1$ 正好可以上升到自己，不用操作。
 
  - $cnt_i > 1$ 多次操作。
 
  - $cnt_i = 0$ 为了抵消子节点的影响，答案加一。
 
然后这题就变成了字符串贪心题。

## Code:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5; 
int n, tree[N], a[N], cnt[N];
char num;
void update(int idx, int val) {
	for(; idx <= n; idx += idx & -idx) {
		tree[idx] += val;
	}
	return;
}
int query(int x) {
	int ans = 0;
	for (; x; x -= x & -x) {
		ans += tree[x];
	}
	return ans;
}
void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> num;
		a[i] = num - 48, cnt[i] = 0;
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (a[i]) {
			if (!cnt[i]) {
				ans++;
			}
			if (i + (i & -i) <= n) {
				cnt[i + (i & -i)]++;
			}
		} else {
			if (cnt[i] == 1) {
				ans++;
			}
		}
	}
	cout << ans << '\n';
	return;
}
signed main() {
	cin.tie(0)->sync_with_stdio(false);
	int T;
	for(cin >> T; T; --T) {
		solve();
	}
	return 0;
} 
```

---

## 作者：zheng_zx (赞：0)

## P9883 [EC Final 2021] Fenwick Tree

[题目传送门](https://www.luogu.com.cn/problem/P9883)

### 题意

---

给定一个初始全是 $0$ 的字符串，和一个 ```update``` 函数，然后输入是想要变成的字符串，（$0$ 表示为 $0$，$1$ 表示非 $0$），求最少需要多少步才能变成那样。

### 分析

---

观察 ```update``` 函数，对于一个位置而言，我们需要找他会从那几个位置跳到当前位置。

例如对于 $8(1000)$ 而言，我们最多可以通过 $4(100)6(110)7(111)$ 到这个点。表现形式就是找到最后一个 $1$，将其变 $0$，然后按顺序依次将后面的 $0$ 变成 $1$，即原数减去 $2^i$ 次，$i$ 是那几个位置。

然后我们观察发现，如果你当前的位置的期望状态是 $1$，而你前一个状态全是 $0$，那么就需要一步操作。

而如果你当前位置的期望状态是 $0$，而你的前一个状态只有一个是 $1$，那么你需要一步操作来抵消这个 $1$。

如果你前一个状态有多个 $1$，我们总会有一种策略使得当前点是 $0$ 或是 $1$。

---

