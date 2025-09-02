# 「GMOI R2-T2」猫耳小

## 题目背景

**本题与 [加强版](https://www.luogu.com.cn/problem/P9202) 的区别在于数据范围和输出格式。在这一版本中，$n\le 5\times 10^3$，值域为 $5\times 10^3$，你不需要给出构造。**

![](https://cdn.luogu.com.cn/upload/image_hosting/r8a6ylx3.png)

## 题目描述

小 R 是一个可爱的猫耳女孩子，她喜欢研究数列的 $\operatorname{mex}\text{*}$。

现在她有一个长度为 $n$ 的数列 $a$。她讨厌整数 $k$，因此她希望修改数列 $a$ 的若干个元素为任意**自然数**，使得 $a$ 的任意**连续非空子串**的 $\operatorname{mex}$ 都不等于 $k$。

请你求出最少需要修改多少个元素。

$\text{*}$ 本题中，数列的 $\operatorname{mex}$ 被定义为数列中最小未出现的**自然数**，例如：

- $\operatorname{mex}\{1,2,3\}=0$，因为 $0$ 是自然数。
- $\operatorname{mex}\{0,1,3\}=2$。
- $\operatorname{mex}\{0,1,2\}=3$。

## 说明/提示

**样例解释**

一种方案是将 $\{1,0,1,3,0\}$ 改为 $\{1,1,1,3,2\}$，共改动两个元素。

可以证明不存在更优的方案。

---

**本题使用 Subtask 捆绑测试。**

| Subtask | $n\le$ | $k\le$ | $a_i\le$ | 特殊性质 | 对应测试点 | 总分 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $0$ | $6$ | $6$ | $6$ | $-$ | $1\sim 2$ | $10$ |
| $1$ | $100$ | $5\times 10^3$ | $5\times 10^3$ | $-$ | $3\sim 5$ | $20$ |
| $2$ | $5\times 10^3$ | $1$ | $5\times 10^3$ | $-$ | $6\sim 10$ | $20$ |
| $3$ | $5\times 10^3$ | $5\times 10^3$ | $5\times 10^3$ | $\bf A$ | $11\sim 15$ | $20$ |
| $4$ | $5\times 10^3$ | $5\times 10^3$ | $5\times 10^3$ | $-$ | $16\sim 20$ | $30$ |

特殊性质 $\bf A$：保证 $a_i < k$。

对于 $100\%$ 的数据，$1\le n\le 5\times 10^3$，$0\le k,a_i\le 5\times 10^3$。

## 样例 #1

### 输入

```
5 2
1 0 1 3 0```

### 输出

```
2```

# 题解

## 作者：rui_er (赞：24)

首先特判 $k=0$ 的情况，此时的答案为非 $0$ 数的个数，改法是将它们全改成 $0$。

再特判 $k$ 较大的情况，此时的答案为 $0$。

否则，对于 $k$ 大小适中的情况，我们从前往后遍历数组，同时维护当前区间的 $\operatorname{mex}$ 值。根据 $\operatorname{mex}$ 的定义，显然对于左端点相同的区间，右端点不断右移的过程中 $\operatorname{mex}$ 单调不降。因此，如果 $\operatorname{mex}$ 值在某一时刻超过了 $k$（一定是遍历到一个 $k$ 导致的），则继续右移是没有意义的，此时清空维护的区间。如果 $\operatorname{mex}$ 值在某一时刻等于 $k$，则将此时区间右端点改为 $k$。

时间复杂度 $\mathcal O(n)$。

$k=0$ 或 $k$ 较大的正确性是显然的，下面证明上述 $k$ 适中贪心算法的正确性。

引理一：存在一种最优方案，使得所有修改的位置都被改为 $k$。

证明：考虑任意一种最优方案，如果一个位置被修改，使得不存在 $\operatorname{mex}$ 为 $k$ 的区间，则将它改为 $k$ 也不存在。原因是包含 $k$ 的区间的 $\operatorname{mex}$ 一定不等于 $k$，而从这个位置将数列分开，根据方案合法性，剩余的部分的 $\operatorname{mex}$ 也一定不是 $k$。$\square$

因此，我们只需要考虑将所有修改的位置都改为 $k$ 的情况。

同样的理由，我们不需要考虑原数列中包含 $k$ 的连续子段，因此可以将原数列按照 $a_i=k$ 的位置分为若干段，每一段都不包含 $k$。另外，显而易见地，大于 $k$ 的 $a_i$ 没有意义。综上，只要我们解决了子任务三（保证 $a_i < k$），原问题得解。

在子任务三中，一段区间的 $\operatorname{mex}$ 等于 $k$，当且仅当这段区间包含 $0\sim k-1$ 的所有数。我们找到最靠左的这样的区间，则这段区间内至少要有一个数被改为 $k$。在改为 $k$ 后，从被修改的位置往右是一个子问题。

引理二：存在一种最优方案，使得所有被修改的位置都是上述区间的右端点。

证明：考虑任意一种最优方案，假设一次修改没有改右端点，则改右端点一定不劣。原因是这样可以尽量缩减问题的规模，由于 $\operatorname{mex}$ 有单调性，这么操作并不会使得下一个修改位置提前，只可能使得下一个修改位置延后。$\square$

子任务三的贪心算法正确性得证。根据上述推理，原问题的贪心算法正确性得证。

代码：

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
#define likely(exp) __builtin_expect(!!(exp), 1)
#define unlikely(exp) __builtin_expect(!!(exp), 0)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
	uniform_int_distribution<int> dist(L, R);
	return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const int N = 1e6+5;

int n, k, a[N], b[N], cnt[N], mex, ans;

int read() {
	int x = 0, k = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') k *= -1;
	for(; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	return x * k;
}

void write(int x, char end = 0) {
	if(x < 0) putchar('-'), x = -x;
	if(x < 10) putchar(x ^ 48);
	else {
		write(x / 10);
		putchar((x % 10) ^ 48);
	}
	if(end) putchar(end);
}

int main() {
	n = read(); k = read();
	rep(i, 1, n) a[i] = read();
	if(!k) {
		rep(i, 1, n) if(a[i]) ++ans;
		rep(i, 1, n) b[i] = 0;
	}
	else if(k > n + 1) {
		rep(i, 1, n) b[i] = a[i];
	}
	else {
		rep(i, 1, n) b[i] = a[i];
		for(int l = 0, r = 1; r <= n; r++) {
			if(a[r] > k) continue;
			if(a[r] == k) {
				while(++l < r) if(a[l] < k) --cnt[a[l]];
				mex = 0;
			}
			else {
				++cnt[a[r]];
				while(cnt[mex]) ++mex;
				if(mex == k) {
					++ans;
					while(++l < r) if(a[l] < k) --cnt[a[l]];
					--cnt[a[r]];
					b[r] = k;
					mex = 0;
				}
			}
		}
	}
	write(ans, '\n');
	rep(i, 1, n) write(b[i], " \n"[i==n]);
	return 0;
}
```

---

## 作者：ncwzdlsd (赞：4)

不好想。

从特殊性质 $\textbf A$ 入手，考虑对于一个子串，如果含有 $[0,k-1]$ 中的每个数且不含 $k$，则区间的 $\text{mex}$ 一定不等于 $k$。而对于子串中大于 $k$ 的元素，对 $\text{mex}$ 没有影响。

我们遍历整个数列，统计小于 $k$ 的元素种类数，如果有 $k$ 个了（即集齐了 $[0,k-1]$ 的所有数），那么这一段子串必须要修改一个元素为 $k$ 使得其 $\text{mex}$ 不为 $k$。如果当前元素为 $k$，那么它可以抵消掉它前面的任意包含它的子串和后面的任意包含它的子串，直接清空所有访问标记开始新一轮标记即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=5005;
int a[maxn];
bool vis[maxn];

int main()
{
	int n,k;cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	int tot=0,ans=0;
	for(int i=1;i<=n;i++)
	{
		// if(a[i]>k) continue;
		if(a[i]==k){memset(vis,0,sizeof vis),tot=0;continue;}
		if(a[i]<k&&!vis[a[i]]) tot++,vis[a[i]]=1;
		if(tot==k) ans++,memset(vis,0,sizeof vis),tot=0;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：lianchanghua (赞：2)

#### 题目大意

给你一个长度为 $n$ 的序列，要求你对序列进行修改，使得这个序列的每一个非空字串所不含有的最小自然数不能为 $k$，请你输出最小步数。

#### 题目思路

我们可以遍历一遍序列，在遇到 $a_i = k$ 时，说明含这个 $a_i$ 的子序列不可能不包含的最小自然数为 $k$，我们就可以跳过。否则要对 $i$ 到 $1$ 进行遍历。设置一个计数器，表示比 $k$ 小的数的个数，容易得知：比 $k$ 小的数值有 $k$ 种时，那么前面就一定有一个序列，它的未出现的最小自然数为 $k$，所以我们进行遍历时如果$a_j$ 这个数值之前没有遍历过并且 $a_j$ 这个数值比 $k$ 还小，那么我们就让计数器增加 $1$。当计数器值加到 $k$ 时，我们的 $ans$ 就会增加一个，并对 $a_i$ 做出修改，改为 $k$ 保证 $k$ 不是当前子序列的未出现的最小自然数。最后输出 $ans$ 即可。

#### AC code（之前写的，马蜂可能有点奇怪）
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a[5005];
int cnt,ans;
signed main(){
	ios::sync_with_stdio(false);
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]!=k){
			bool f[5005]={};
            cnt=0;
            for(int j=i;j>=1;j--){
                if(a[j]==k)		break;
                if(!f[a[j]]&&a[j]<k){
                    f[a[j]]=1;
                    cnt++;
                }
                if(cnt==k){
                    a[i]=k;
                    ans++;
                    break;
                }
            }
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：sto_5k_orz (赞：2)

$1\leq a_i,n,k\leq 5000$，什么情况？

盲猜复杂度 $O(nk)$。

考虑贪心求解。

显然，假如一段中缺少了任何一个 $<k$ 的数，则不成立。

或者 $k$ 在集合中，依旧不成立。

那么从 $1$ 到 $n$ 枚举一遍，什么时候成立了就改一次，然后接着试。

判断成不成立可以考虑用 set。先把 $0$ 到 $k-1$ 全推进去，然后把 $a_i$ 删掉。

什么时候 $a_i=k$ 了就把 $0$ 到 $k-1$ 推回去。

集合空时说明需要修改。

复杂度 $O(nk\log k)$，当且仅当所有 $a_i=k$ 时取到。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define gc getchar
#define W while
#define I inline
namespace SlowIO{
    I int read() {
        int x = 0, f = 1; char ch = gc();
        W(ch < '0' || ch > '9') {if(ch == '-') f = -f; ch = gc();}
        W(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gc();
        return x * f;
    }
    I void Read(int &x) {x = read();}
} using namespace SlowIO;
const int N = 5010;
int n, k; int a[N], cnt[N]; set<int> st;
signed main() {
	cin >> n >> k; int ans = 0;
	for(int i = 1; i <= n; i++) Read(a[i]);
	for(int i = 0; i < k; i++) st.insert(i); // 初始化
	for(int i = 1; i <= n; i++) {
		if(a[i] == k) { // = k,全部推回去
			for(int i = 0; i < k; i++) st.insert(i);
			continue;
		}
		st.erase(a[i]); // 删掉
		if(st.empty()) { // 删完
			ans++; // 修改一次
			for(int i = 0; i < k; i++) st.insert(i); // 重新开始
		}
	}
	cout << ans;
    return 0;
}
```

---

## 作者：wwxxbb (赞：0)

~~原来猫耳小的梗来自这道题，现在才知道。~~

### $\mathcal{O}(n)$ 思路

如果没有什么思路可以想一下 $\operatorname{mex}$ 的定义：数列中最小未出现的**自然数**。

所以 $k = 0$ 的时候，答案为序列中不为 $0$ 的元素数量； $k > n$ 的时候，答案为 $0$。

如果不想分类讨论，就使 $k \leftarrow \min(k, n + 1)$。

我们从 $1$ 到 $n$ 遍历序列，如果数 $x < k$ 且 $x$ 未出现过，那么说明小于 $k$ 的数量加 $1$，如果这个数量加到 $k$ 了，说明当前遍历到的区间的 $\operatorname{mex}$ 为 $k$，解决方案就是将当前的数变为 $k$。这样做的好处是：

题目要求任意**连续非空子串**的 $\operatorname{mex⁡}$ 都不等于 $k$，而我们把这个数改成 $k$ 了，那么包含这个数的区间的 $\operatorname{mex}$ 就不可能是 $k$。

所以就可以重新开始记录了。

实现的时候，可以用一个桶 $a$ 和计数器 $cnt$，遇到一个没出现过的数，就加到桶里，并 $cnt \leftarrow cnt + 1$，如果遇到一个数是 $k$ 了，就清空桶和计数器。

但这样做是不优的。如果序列中所有数都是 $k$，那么复杂度会退化到 $\mathcal{O}(nk)$，解决方法是，再开个桶 $b$，记录 $< k$ 的数，清空的时候不需要将整个桶 $a$ 清空完，只需要将在桶 $b$ 里出现过的数在 $a$ 中清掉，这样就能保证复杂度是对的，同时也能通过加强版。

### 代码

#### 本题

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 5010;

int n, k, b[N], top, cnt, ans;
bitset<N> st;

inline void clear() {
    while (top) st[b[top --]] = 0;
    cnt = 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> k; k = min(k, n + 1);
    for (int i = 1, x; i <= n; i ++) {
        cin >> x;
        if (x == k) { clear(); continue; }
        if (x < k && !st[x]) {
            st[x] = 1;
            b[++ top] = x;
            ++ cnt;
        }
        if (cnt == k) {
            ++ ans;
            clear();
        }
    }
    return cout << ans, 0;
}
```

#### 加强版

一开始以为卡常，用了快读。

```cpp
const int N = 1000010;

int n, k, a[N], b[N], top, cnt, ans;
bitset<N> st;

inline void clear() {
    while (top) st[b[top --]] = 0;
    cnt = 0;
}

int main() {
    read(n, k); k = min(k, n + 1);
    for (int i = 1, x; i <= n; i ++) {
        read(x); a[i] = x;
        if (x == k) { clear(); continue; }
        if (x < k && !st[x]) {
            st[x] = 1;
            b[++ top] = x;
            ++ cnt;
        }
        if (cnt == k) {
            ++ ans;
            a[i] = k;
            clear();
        }
    }
    writeln(ans);
    for (int i = 1; i <= n; i ++)
        writesp(a[i]);
    return 0;
}
```

---

## 作者：ny_jerry2 (赞：0)

## 题意
给定一个序列  $a$ 与一个值 $k$，让你改变 $a$ 中的一些值，使得序列中**任意连续子串的 $mex$ 值不为 $k$**。求出**最小的修改次数**。
***

## 思路
一眼看见数据范围 $n \le 5 \times 10^3 $，$k \le 5 \times 10^3$ 就觉得是一个 $O(n^2)$ 级别的算法，但实际上在线性的时间内就能解决这个问题。

首先设置一个计数器 $cnt$ 与一个判断一个元素是否重复的数组 $v$ 来辅助我们求答案。

对于 当前遍历到的元素，我们分类讨论（设该元素为 $x$）：

- 若 $x > k$  
  很明显，该情况对答案没有贡献，忽略即可。
- 若 $x = k$   
  也很显然，含有该元素的子序列的 $mex$ 值一定不会是 $k$，于是计数器清零，并将判重数组清空。因为前面的所有子串肯定都满足条件，对答案不会产生贡献，直接重置 $cnt$ 与 $v$ 数组即可。
- 否则为 $x<k$  
  因为该元素可能对答案有贡献，所以我们先判断一下该元素是否出现过，如果没有，将计数器的值加一。

每次结束后，我们判断一下 $cnt$ 是否等于 $k$。等于的话就将答案加一，并重置 $cnt$ 与 $v$ 数组。这相当于是一种贪心的操作，即**将该元素变为 $k$**。  

这其实很好理解，将该元素变为 $k$ 同时也使得以该元素开头的子串一定满足条件。

最后输出答案即可。

这道题总体来说还是有点考验思维难度的，代码则不是特别复杂。
***

## 时间复杂度
每个元素只会遍历一遍，很明显是 $O(n)$ 级别的。
***

## 代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int n,m;
const int N=1e6+10;
int a[N];
bool v[N];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	if(m==0){
		int cnt=0;
		for(int i=1;i<=n;i++){
			if(a[i]){
				cnt++;	
			}
		}
		cout<<cnt;
		return 0;
	}
	
	int cnt=0,ans=0;
	//cnt:计数器，用来判断是否找到了不满足条件的子串的个数
	//ans:计算最小代价 
	for(int i=1;i<=n;i++){
		if(a[i]>m){
			continue;
		}//情况1 
		
		if(a[i]==m){
			cnt=0;
			memset(v,0,sizeof v);
			continue;
		}//情况2 
		
		if(a[i]<m){
			if(!v[a[i]]){
				v[a[i]]=1;
				cnt++;
			}
		}// 情况3 
		
		if(cnt==m){
			cnt=0;
			ans++;
			memset(v,0,sizeof v);
		}//计数 
	}
	cout<<ans;
}
```

---

## 作者：qzhwlzy (赞：0)

### 题目大意

给定一个长度为 $n$ 的序列 $a$。问最少要修改多少个元素才能让整个序列的所有子串的 $\operatorname{mex}$ 都不为 $k$。

### 思路

首先，包含 $k$ 的子串的 $\operatorname{mex}$ 一定不为 $k$，那么我们可以把原序列按照 $k$ 划分成若干段来计算答案。

对于某一段，假设其 $\operatorname{mex}$ 不是 $k$，那么我们无需考虑。接下来考虑若一段的 $\operatorname{mex}=k$：

我们可以从前往后遍历这一个子串 $a_l,a_{l+1},\ldots,a_r$，假设在某个 $a_i$ 处发现有 $\operatorname{mex}\{a_l,a_{l+1},\ldots,a_i\} = k$，那么我们必须要更改其中的一个数。那么改哪一个数最合适呢？显然更改 $a_i = k$ 最好。因为 $\operatorname{mex}\{a_l,a_{l+1},\ldots,a_{i-1}\} \neq k$，于是更改 $a_i$ 能最大化减少 $a_l\sim a_{i-1}$ 对后面子串的影响；而更改为 $k$ 能使 $a_{i+1}\sim a_r$ 成为新的一段，能减小 $a_i$ 对后面的影响。

至于求 $\operatorname{mex}$，可以直接开一个桶维护。

时间复杂度 $\mathcal{O}(n)$。

### 代码

~~代码注释掉的内容是加强版的输出方案。~~

```cpp
#include<iostream>
#include<cstdio>
#define maxn 1000005
using namespace std;
int n,k,a[maxn],b[maxn],mex=0,cnt=0;
int main(){
	scanf("%d%d",&n,&k); for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	if(k==0){ // k=0 时整个序列不能出现非 0 数
		for(int i=1;i<=n;i++) if(a[i]) cnt++;
		printf("%d\n",cnt); /* for(int i=1;i<=n;i++) printf("0 ");*/ return 0;
	}
	for(int i=1;i<=n;i++){
		if(a[i]==k){mex=0; for(int j=i-1;a[j]!=k&&j>0;j--) if(a[j]<=k) b[a[j]]--; continue;}
		if(a[i]>k||a[i]>n) continue;
		b[a[i]]++; while(b[mex]) mex++;
		if(mex==k){
			for(int j=i;a[j]!=k&&j>0;j--) if(a[j]<=k) b[a[j]]--;
			mex=0; cnt++; a[i]=k;
		}
	} printf("%d\n",cnt); // for(int i=1;i<=n;i++) printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：Clarinet (赞：0)

[博客食用观感更佳](https://www.luogu.com.cn/blog/Czel-X/ti-xie-15-post)
# 简要题意
给出一个长度为 $n$ 的数列 $a$，求一个最小修改次数使每个连续非空子串的最小未出现自然数不等于 $k$。
# 分析
由于数据比较宽松，我们直接遍历数组。对于每个未出现过且在 $0$ 到 $k-1$ 范围内的数，我们就记录一下，使 sum 加一；如果 sum 等于 $k$，也就是前面已经有 $0$ 到 $k-1$ 范围内的所有数了，那么就必须更改一次，也就是答案加一。

更改一次后，我们使 sum 变为 $0$，从头开始计算。

值得注意的是如果出现了一个等于 $k$ 的数，那么之前所有待结算的部分都会因为这个 $k$ 的出现而无法构成 mex 为 $k$的情况。因此之前的计数也要清空。

至于最优性的证明应该很好想。我们输入时就从前往后进行计算，一旦出现了所有的数就代表此时不得不更改一次了，不然这个子串的 mex 就会变成 $k$，因此这样计算也一定是最优的（贪心思路）。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[5010],t[5010],ans,sum=0;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==k){
			memset(t,0,sizeof(t));
			sum=0;
			continue;
		}
		if(a[i]<k&&!t[a[i]]){
			sum++;
			t[a[i]]=1;
		}
		if(sum==k){
			ans++;
			memset(t,0,sizeof(t));
			sum=0;
		}
	}
	cout<<ans;
	return 0;
}
```
感谢阅读！

---

