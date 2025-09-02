# [ARC181A] Sort Left and Right

## 题目描述

给你一个 $(1,2,\dots,N)$ 的排列 $P=(P_1,P_2,\dots,P_N)$。

你要通过执行以下操作零次或多次来满足所有 $i=1,2,\dots,N$ 的 $P_i=i$：

- 选择一个整数 $k$，使得 $1 \leq k \leq N$。如果是 $k \geq 2$，把第 $1$ 项到第 $(k-1)$ 项的 $P$ 按升序排序。然后，如果是 $k \leq N-1$，把 $P$ 的第 $(k+1)$ 项到第 $N$ 项按升序排序。

可以证明，在这个问题的约束条件下，对于任意 $P$，都可以用有限次的运算满足所有 $i=1,2,\dots,N$ 的 $P_i=i$。请求解所需的最小运算次数。

## 说明/提示

**样例解释**

对于第一个测试用例：

- 对 $k=1$ 执行操作后，$P$ 变成了 $(2,1,3,4,5)$。
    
- 执行 $k=2$ 操作后，$P$ 变为 $(2,1,3,4,5)$。
    
- 与 $k=3$ 进行运算，结果是 $P$ 变为 $(1,2,3,4,5)$。
    
- 与 $k=4$ 进行运算，结果是 $P$ 变为 $(1,2,3,5,4)$。
    
- 与 $k=5$ 进行运算，结果是 $P$ 变为 $(1,2,3,5,4)$。
    

具体来说，对 $k=3$ 进行运算的结果是 $P$ 满足所有 $i=1,2,\dots,5$ 的 $P_i=i$。因此，所需的最少运算次数为 $1$。

在第三个测试用例中，先执行 $k=4$ 操作，再执行 $k=3$ 操作，结果 $P$ 变为 $(3,2,1,7,5,6,4) \rightarrow (1,2,3,7,4,5,6) \rightarrow (1,2,3,4,5,6,7)$ 。


对于 $100\%$ 的测试数据，保证 $1 \leq T \leq 10^5$，$3 \leq N \leq 2 \times 10^5$，$P$ 是 $(1,2,\dots,N)$ 的排列。

## 样例 #1

### 输入

```
3
5
2 1 3 5 4
3
1 2 3
7
3 2 1 7 5 6 4```

### 输出

```
1
0
2```

# 题解

## 作者：Register_int (赞：12)

容易发现答案 $\le 3$，因为按顺序操作 $1,n,1$ 一定能排好。考虑如何判 $0,1,2$：

- 不用排序为 $0$。
- 存在一个 $i$，使得 $i$ 左边的数都小于他，右边的数都大于他为 $1$。
- $1$ 不在结尾或者 $n$ 不在开头，可以用一次排序把 $1$ 或 $n$ 拉到对应的位置，然后对着头或尾再排一次，次数为 $2$。
- 否则次数为 $3$。

复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 10;

int T, n, a[MAXN]; bool f = 0;

int pre[MAXN], suf[MAXN];

int main() {
	for (scanf("%d", &T); T--;) {
		scanf("%d", &n), f = 1, suf[n + 1] = n + 1;
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for (int i = 1; i <= n; i++) if (a[i] != i) f = 0;
		if (f) { puts("0"); continue; }
		for (int i = 1; i <= n; i++) pre[i] = max(pre[i - 1], a[i]);
		for (int i = n; i; i--) suf[i] = min(suf[i + 1], a[i]);
		for (int i = 1; i <= n; i++) {
			if (pre[i] == i && suf[i] == i && a[i] == i) { f = 1; break; }
		}
		if (f) { puts("1"); continue; }
		puts(a[1] == n && a[n] == 1 ? "3" : "2"); 
	}
}
```

---

## 作者：include13_fAKe (赞：4)

# ARC181A
第一次 ARC 不抱铃（也只会这一题），而且是 **vp** 的。

## 思路

**重大结论：答案一定不大于 $3$。**

答案为 $0$ 即已经有序了。可以用第二组样例验证。

答案为 $1$ 就枚举有没有合适的地方操作即可。

可以计算每一个前缀的最大值，当 $P_i=i$ 且 $Q_i=i$ 时成立，其中 $Q_i$ 是 $[1,i]$ 中的最大值。容易做到 $O(n)$。可以用第一组样例验证。

剩下的情况有一个重大结论：**只需要在第一个位置和最后一个位置操作即可**。~~但我也不会证~~。

当 $P_1=i$ 且 $P_i=1$ 时，需要做 $3$ 次，举例如下：

$$[7,6,5,4,3,2,1]$$

$$[\color{red}7\color{black},1,2,3,4,5,6]$$

$$[1,2,3,4,5,7,\color{red}6\color{black}]$$

$$[\color{red}1\color{black},2,3,4,5,6,7]$$

其他情况都只需要做 $2$ 次，举例如下（第三组样例）：

$$[3,2,1,7,5,6,4]$$

$$[\color{red}3\color{black},1,2,4,5,6,7]$$

$$[1,2,3,4,5,6,\color{red}7\color{black}]$$

然后这个题就很简单了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int p[2*114514];
int max1;
bool f1=true;
void solve(){
	f1=true;
	max1=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>p[i];
		if(p[i]!=i)	f1=false;
	}
	if(f1){
		puts("0");
		return;
	}
	for(int i=1;i<=n;i++){
		max1=max(max1,p[i]);
		if(p[i]==i&&max1==i){
			puts("1");
			return;
		}
	} 
	if(p[1]==n&&p[n]==1){
		puts("3");
		return;
	}
	puts("2");
	return;
}
int T;
int main(){
	cin>>T;
	while(T--)	solve();
	return 0;
}
```

---

## 作者：paper_ (赞：1)

### 题目大意

给定一个 $1 \sim n$ 的排列 $P$ 。每次操作可以选择一个 $i$，若 $i$ 不为 $1$ 则将 $P_1 \sim P_{i - 1}$ 从小到大排序，若 $i$ 不为 $n$ 则将 $P_{i + 1} \sim P_n$ 从小到大排序。求 $P$ 变为： $1,2,3\ldots n$ 的最小操作次数。

## 思路

较为简单的一道分类讨论题。

### 情况一

操作次数如果为 $0$ 直接判，不用说。

### 情况二

考虑如果有一个 $i$ 使得：

- $P_1 \sim P_{i - 1}$ 是一个 $1 \sim i - 1$ 的排列。
- $P_{i + 1} \sim P_n$ 是一个 $i + 1 \sim n$ 的排列。

那么就可以直接选择 $i$ 进行操作，答案为 $1$ 结束。

### 情况三

如果不存在这样的 $i$，我们可以找到 $1$ 所在的位置，选择它右边的一个数操作一次。

此时 $P_1 = 1$。接下来只需要选择 $1$ 操作一次就可以了。

如果 $1$ 在最右侧就可以把 $n$ 移到最右侧，方法同理。

这种情况的答案为 $2$。

### 情况四

还有一个特殊情况：$1$ 在最右侧且 $n$ 在最左侧。

此时选择 $1$ 进行操作。$P_{n - 1}$ 就会变成 $n$。在选择 $1$ 号位进行操作。

此时 $P_n = n$，操作一下 $n$ 就行了，总共操作 $3$ 次。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200010];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); 
	int T;cin >> T;
	while (T -- ) {
		int n;cin >> n;
		int ans = 0, ma = 0, can = 0;
		for (int i = 1; i <= n; i ++ ) {
			cin >> a[i];ma = max(ma, a[i]);
			if (a[i] == i) ans ++;
			if (a[i] == i && a[i] == ma) can = 1;
		}
		if (a[1] == n && a[n] == 1) cout << 3 << '\n';
		else if (ans == n) cout << 0 << '\n';
		else if (can) cout << 1 << '\n';
		else cout << 2 << '\n';
	}
	return 0;
}
```

---

## 作者：sh1kong (赞：1)

[In Luogu](https://www.luogu.com.cn/problem/AT_arc181_a)

一道思维题。

解：多造几组数据推一下，容易发现答案不会超过 $3$。

为什么呢？

假设现在 $p_1 = 1$，那么我们选择 $k=1$ 进行操作，那实际上会将 $p_2, p_3, \cdots p_n$ 进行升序排序，经过这次操作，$p$ 满足了条件。也就是说，当 $p_1=1$ 时，我们可以通过一次操作使排列 $p$ 满足条件。

类似地，若现在 $p_n=n$，我们选择 $k=n$ 进行操作，同样可以通过一次操作使排列 $p$ 满足条件。

那么我们考虑将 $p_1=1$ 或 $p_n =n$。

考虑怎么让 $p_1$ 变成 $1$。

找到 $1$ 在 $p$ 中的位置 $k$，那么我们在 $k+1 \sim n$ 中选择一个位置进行一次操作，就可以使 $p_1$ 变成 $1$。

将 $p_n$ 变成 $n$ 同理。

但是这样有个问题，就是当 $p_n=1$ 时或 $p_1=n$ 时，我们无法进行这样的操作，需要将 $1$ 从位置 $n$ 变到其它地方，再进行操作。那么此时答案就为 $3$ 了。

综上，当 $p_n=1$ 且 $p_1=n$ 时，答案为 $3$，否则答案为 $2$。

但是需要注意特判不需要操作的情况，以及类似样例的第一组数据的情况，即在对位置 $k+1 \sim n$ 进行操作后，$p$ 已经满足了条件。

讲的不是很清楚，具体细节见代码。

```cpp
cin >> t;
while (t -- )
{
	cin >> n;
	bool chk = false; T = 0;
	for (ll i = 1; i <= n; i ++ ) 
	{
		cin >> A[i]; B[i] = A[i];
		if (A[i] != i) chk = true;
	}
	if (!chk) { cout << "0\n"; continue; } // 不需要操作
	if (A[1] == 1 || A[n] == n) { cout << "1\n"; continue; } // 此时只需要对 1 或 n 进行操作即可
	
	if (A[1] == n && A[n] == 1) { cout << "3\n"; continue; }
  // 特判类似样例的第一组数据的情况，判断对 1 / n 操作后，p 是否满足条件。
	ll mx = 0; bool jud = false;
	for (ll i = 1; i <= n; i ++ )
	{
		if (A[i] == i && mx == (i - 1))
		{
			jud = true;
			break;
		}
		mx = max(mx, A[i]);
	}
	if (!jud) cout << "2\n";
	else cout << "1\n";
}
```

---

## 作者：MicroSun (赞：0)

分类讨论一下。

很容易判断 $0$ 次操作的情况。

否则，如果存在 $i$，满足 $P_i=i$，且 $1\sim i-1$ 可以重新排列为 $p_1,p_2,\dots,p_{i-1}$，则可以在 $i$ 上执行一次操作使得序列有序。

后面这个条件可以简单双指针一下。

如果以上两个条件都不满足，则如果 $a_1\ne n$ 或 $a_n\ne 1$ 则可以在不等的那个位置进行一次操作，操作后 $a_1=1$ 或 $a_n=n$，然后在这个相等的位置上再做一次操作就有序了。

否则需要三次操作，中间任意点操作一次，再转换成上一种情况。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
#define fst first
#define scd second
#define rep(i,s,e) for(int i=s;i<=e;i++)
#define dep(i,s,e) for(int i=s;i>=e;i--)

using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

const int N=2e5+10;

ll a[N];
bool vis[N];
void solve(){
	int n;
	cin>>n;
	rep(i,1,n){
		cin>>a[i];
		vis[i]=0;
	}
	bool flg=1;
	rep(i,2,n)
		if(a[i-1]>a[i]) flg=0;
	if(flg){
		cout<<"0\n";
		return;
	}
	int p=1;
	rep(i,1,n){
		if(p==i&&a[i]==i){
			cout<<"1\n";
			return;
		}
		vis[a[i]]=1;
		while(vis[p]) ++p;
	}
	if(a[1]==n&&a[n]==1) cout<<"3\n";
	else cout<<"2\n";
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t=1;
	cin>>t;
	while(t--) solve();
    return 0;
}
```

---

## 作者：scp020 (赞：0)

# AT_arc181_a Sort Left and Right 题解

赛时糖丸了，吃了 $5$ 发罚时才过。

## 解法

如果输入序列有序则答案一定为 $0$，这里不多讨论。

可以发现把序列还原可以通过两种方法，一种是在 $1$ 或者是 $n$ 已经还原的情况下通过 $1$ 步使整个序列还原，还有一种是通过选取一个在中间的和左右两边都不产生逆序对的数使序列还原。其实不难发现第一种方法是第二种方法的特殊情况。

第二种方法显然只能用一次，否则一定不会比第一种方法更优。

考虑第一种方法，如果 $1$ 或 $n$ 已经还原的话答案是 $1$。否则我们需要把 $1$ 或 $n$ 还原。

考虑极端情况，就是 $a_1 = n,a_n = 1$，那最少需要两步才能使 $1$ 或 $n$ 还原，所以答案是 $3$。

剩下的情况答案是 $2$，即通过 $1$ 步使 $1$ 或 $n$ 还原，然后通过 $1$ 一步使序列还原。

## 代码

```cpp
#include<bits/stdc++.h>
namespace fast_IO
{
    /**
     * useless fast IO
    */
};
using namespace fast_IO;
int t,n,a[200010],maxi[200010],mini[200010];
bool flag;
int main()
{
    in>>t;
    while(t--)
    {
        in>>n,flag=1;
        for(int i=1;i<=n;i++) in>>a[i],flag&=(a[i]==i);
        if(flag)
        {
            out<<"0\n";
            continue;
        }
        maxi[0]=INT_MIN,mini[n+1]=INT_MAX;
        for(int i=1;i<=n;i++) maxi[i]=std::max(maxi[i-1],a[i]);
        for(int i=n;i;i--) mini[i]=std::min(mini[i+1],a[i]);
        for(int i=1;i<=n;i++) if(maxi[i-1]<=a[i] && mini[i+1]>=a[i]) flag=1;
        if(flag) out<<"1\n";
        else if(a[1]==n && a[n]==1) out<<"3\n";
        else out<<"2\n";
    }
    fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
    return 0;
}
```

---

## 作者：Double_Light (赞：0)

首先，如果序列本身就是有序的，显然不需要排序，输出 $0$。

然后考虑枚举 $P$ 中的每一个位置。显然对于 $P_i$ 而言，对 $P_i$ 进行排序之后序列有序的充要条件是同时满足：

1. $P_1\sim P_{i-1}$ 的值排序后与 $1\sim i-1$ 一一对应。这等价于 $\sum_{j=1}^{i-1}P_j=\dfrac{i\times(i-1)}{2}$。
2. $P_i=i$。

随后考虑分类讨论。

- 如果 $P_1=n$ 且 $P_n=1$：对于 $P_2$ 排序，由于原先 $P_n=1$，所以排完序后 $P_3=1$。转化为第二种情况。

- 如果 $P_1\ne n$ 或 $P_n\ne1$：先对 $P_1$ 进行排序，然后对 $P_n$ 进行排序，最后显然总是有序的。

综上所述，最多会有 $3$ 次排序，所以直接按上述过程写代码即可。

```cpp
#include<iostream>
#define int long long
using namespace std;
int t,f,f2;
int n,a[200005],k;
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		f=1;k=0;f2=0;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++){
			if(a[i]!=i)f=0;
			if(k==(i-1)*i/2&&a[i]==i)f2=1;
			k+=a[i];
		}
		if(f==1)cout<<0<<endl;
		else if(f2==1)cout<<1<<endl;
		else if(a[1]!=n||a[n]!=1)cout<<2<<endl;
		else cout<<3<<endl;
	}
	return 0;
}
```

---

## 作者：xingshuyan000 (赞：0)

[题目传送带：[ARC181A] Sort Left and Right](https://www.luogu.com.cn/problem/AT_arc181_a)

# 题目大意

给你一个全都是正整数的从 $1$ 到 $N$ 的排列 $P$，你需要执行下述操作 $0$ 次或多次来满足所有的 $i=1,2,\dots,N$ 的 $P_i=i$：

- 选择一个整数 $k$，使得 $1 \le k \le N$。如果 $k \ge 2$，把 $P$ 的第 $1$ 项到第 $(k-1)$ 项按升序排序。然后，如果是 $k \le N-1$，把 $P$ 的第 $(k+1)$ 项到第 $N$ 项按升序排序。

现在请你输出最小的操作次数。

其中，$1 \leq T \leq 10^5$，$3 \leq N \leq 2 \times 10^5$。

[更详细的翻译请点这里](https://www.luogu.com.cn/paste/efuk5jxo)

# 题目分析

因为每次操作都会对这个序列的很大一部分进行排序，所以只需要少量的几次操作就可以满足题目要求。

- 先令 $k=1$，如果 $P_1=1$，那么这次操作后，整个序列就会排序为题目要求的形式；否则，如果 $P_1 \ne 1$ 了，在对序列进行操作后，我们会得到 $P_N \ne 1$。（因为若 $P_1 \ne 1$，那么 $1$ 就会在 $P_2$ 到 $P_N$ 中，而对 $P_2$ 到 $P_N$ 进行升序排列后，$1$ 就一定不在第 $N$ 个位置，所以 $P_N \ne 1$）

- 再令 $k=N$，因为先前的操作已经让 $P_N \ne 1$ 了，所以经过这次操作后，$P_1=1$。

- 最后，令 $k=1$，因为前面已经让 $P_1=1$ 了，所以经过这次操作后，整个序列就会满足题目要求了。

经过上述的分析，可以发现，无论最开始的序列 $P$ 怎么排列，最后只需要经过不超过 $3$ 次的操作，就可以得到题目要求的排列。

至于分别什么时候操作 $0,1,2,3$ 次呢？判断如下：

- 零次操作：如果最初的这个序列就已经满足了 $P_i=i$，那么这个序列就不需要操作，直接输出 `0` 即可。

- 一次操作：如果我们确定一个 $k$，在序列 $P_1,P_2,\dots,P_{k-1}$ 中的最小值和最大值如果是 $1$ 和 $k-1$，且 $P_k=k$，则只需要操作一次。

- 两次操作：若$P_N \ne 1$，那么就从上述操作中的第二个操作开始，这样序列经过两次操作后即可满足题意；同理，若 $P_1 \ne N$，也能通过两次操作，使得操作后的序列满足题意。

- 三次操作：如果 $P_1=N$ 且 $P_N=1$，那么 $1$ 和 $N$ 的相对位置就不会因为一次操作而改变，所以通过两次操作不能使得操作后的序列满足题目要求，需要三次操作。

单组数据的时间复杂度是 $O(N)$。一共不超过 $10^5$ 组数据，每组数据的 $3 \le N \le 2 \times 10^5$，时间限制是 2s，可以通过此题。

# Code


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+50;
int a[N];
int flag=0,mmax=-1,b=0;
int main()
{
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(a[i]!=i)flag=1;//如果有元素不在它该在的位置，flag记为1 
		}
		if(flag==0){//如果排列有序 
			cout<<0<<"\n";
			continue;
		}
		for(int i=1;i<=n;i++)
		{
			if(a[i]==i && mmax<i)b=1;//如果元素在正确位置而且大于之前记录的最大值，把b记为1 
			mmax=max(mmax,a[i]);
		}
		if(b==1){
			cout<<1<<"\n";
		}
		else if(a[1]==n and a[n]==1)cout<<3<<"\n";
		else cout<<2<<"\n";
		flag=0,b=0,mmax=-1;
		memset(a,0,sizeof(a));//多测记得清空数组和变量 
	}
	return 0;
}
```

**重要提示：数据千万条，清空第一条。多测不清空，爆零两行泪。**

#### 致歉

因为本蒟蒻能力有限，所以我写的这篇题解参考了一下 AT 官方给这道题的题解，并加入了自己的理解。官方题解链接已附在后面。

[AT 官方题解](https://atcoder.jp/contests/arc181/editorial/10612)

---

## 作者：D0000 (赞：0)

分类讨论一下：
1. 当且仅当原序列有序，最少操作操作 $0$ 次。（显然）
2. 当且仅当某个位置 $x$ 上的数字等于 $x$，并且 $x$ 左边的数都小于 $x$，$x$ 右边的数都大于 $x$，且不满足上述条件时，最少操作 $1$ 次。（显然）
3. 当且仅当第一个位置是 $n$ 且最后一个位置是 $1$ 时，最少操作 $3$ 次。
4. 否则最少操作 $2$ 次。

看来最后两点需要证明：

如果 $1$ 在最前面且 $n$ 在最后面，那么操作一次就行了（点 2）。那么我们很容易就能做到，只需要在数字 $1$ 后面某个位置做一次操作，或者在 $n$ 前面做一次操作就行了，一共就是 $2$ 次。

然而当 $1$ 在末尾，$n$ 在开头时，$1$ 后面没有任何数，$n$ 前面也没有任何数。先证明 $2$ 次一定不能完成，首先在 $1$ 或者 $n$ 操作不会有任何改善，我们在 $[2,n-1]$ 中某个位置 $x$ 操作，就算 $x$ 上的数是 $x$，发现左边有 $n$ 大于 $x$ 因此在操作 $1$ 次是完不成的。在证明操作 $3$ 次一定能完成，其实只需要稍稍把 $1$ 换到前面去，就可以再用 $2$ 次完成了。

证毕。

这道题也完了。

---

## 作者：__O_v_O__ (赞：0)

首先，我们有一个性质：任何序列都能通过不超过 $3$ 次操作满足要求。

这个性质很好证明：我们先对第一个数进行操作，此时序列中的 $1$ 一定在位置一或二。再对最后一个数进行操作，$1$ 一定成为了第一个数。最后对第一个数进行操作，序列就有序了。一共 $3$ 次操作。

接下来我们分别考虑每种情况的条件：

- $0$ 次：序列原来有序。

- $1$ 次：只要存在一个数，它前面的数都小于它，后面的数都大于它，则操作它一定使序列有序。

- $2$ 次：如果第一个数不为 $n$，则一定可以用一次操作把 $n$ 变为最后一个数。再操作最后一个数即可。同理，第 $n$ 个数不为 $1$，也能通过两次操作完成。

- $3$ 次：如果第一个数是 $n$ 且第 $n$ 个数是 $1$，就只能使用三次操作完成。

有了这些结论，这题就很容易实现了。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,a[200001],fl,mx;
signed main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>n,mx=0,fl=0;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)if(a[i]!=i)fl=true;
		if(!fl)cout<<0<<'\n';//0次
		else if(a[1]==n&&a[n]==1)cout<<3<<'\n';//3次
		else{
			for(int i=1;i<=n;i++){
				if(a[i]==i){
					if(mx==i-1){
						cout<<1<<'\n',fl=0;//1次
						break;
					}
				}mx=max(mx,a[i]);
			}
			if(fl)cout<<2<<'\n';//2次
		}
	}
	return 0;
}
```

---

## 作者：myyyIisq2R (赞：0)

> 题意：给定 $1 \sim n$ 的排列 $P$，每次操作选一个位置，前面递增排，后面递增排，问最少几次能使排列单调递增。

显然答案很小。一般情况下（假设 $1$ 不在排列末位），我把最后一位定住，排前面，那样 $1$ 就到位了，然后我再把 $1$ 定住，排后面，就全好了。所以一般情况只需要 $2$ 次就够了。

那当然考虑些特殊情况：$0$ 次，天然单调递增。$1$ 次，定一个位置后，前面一换后面一换刚好到位，说明 $P_i=i$，且 $1 \sim i-1$ 的数都在它前面，剩下的数都在它后面，排一次就行了。最恶心的：$3$ 次，当且仅当 $P_1=n,P_n=1$，必须先换一次把 $1$ 或者 $n$ 换出来，然后再进行 $2$ 次的一般操作。

唯一不太好弄的是 $1$ 次的情况，那既然 $1 \sim i-1$ 的数都在它前面，做个前缀和看看是不是等于 $\sum_{j=1}^{i-1} = \frac{i(i-1)}{2}$ 就行了。

```cpp
while(T--)
{
	int cnt{};
	int n = read();bool tg = false;bool tag0 = true;
	for(int i{1};i<=n;i++)
	{
		a[i] = read();if(a[i] == i) tg = true,pos[++cnt] = i;
		if(a[i] != i) tag0 = false;
		sum[i] = sum[i-1]+a[i];
	}
	if(tag0) {writeln(0);continue;}
	if(a[1] == n && a[n] == 1) {writeln(3);continue;}
	if(!tg) {writeln(2);continue;}
	for(int i{1};i<=cnt;i++)
	{
		int now = pos[i];
		int res = ((now * (1+now))>>1 );
		if(sum[now] == res)
		{writeln(1);tg = false;break;}
	}
	if(tg) writeln(2);
}
```

---

## 作者：zhlzt (赞：0)

### 题解

简单分讨竟然在赛时卡了我 30 多分钟。

考虑如下情况：

1. 排列 $p$ 已排序，需要 $0$ 次操作。

2. 存在 $i$ 使得 $p_i$ 左边所有元素均比它小，且右边所有元素均比它大，可令 $k=i$，需要 $1$ 次操作。

3. 不存在如上的 $i$，但是 $p_1\not = n$，可先令 $k=1$ 再令 $k=n$，需要 $2$ 次操作。

4. 不存在如上的 $i$，但是 $p_n\not = 1$，可先令 $k=n$ 再令 $k=1$，需要 $2$ 次操作。

5. $p_1=n$ 且 $p_n=1$，可令 $k=1$，即转化为情况 4，需要 $3$ 次操作。

只需要预处理前缀最大值，后缀最小值即可。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int p[maxn],dpl[maxn],dpr[maxn];
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n;scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",p+i);
		int tag=1;
		for(int i=1;i<n;i++) tag&=(p[i]<p[i+1]);
		if(tag){puts("0"); continue;}
		dpl[0]=0; dpr[n+1]=n+1;
		for(int i=1;i<=n;i++) dpl[i]=max(dpl[i-1],p[i]);
		for(int i=n;i>=1;i--) dpr[i]=min(dpr[i+1],p[i]);
		for(int i=1;i<=n;i++){
			tag|=(dpl[i-1]<p[i] and p[i]<dpr[i+1]);
		}
		if(tag) puts("1");
		else if(p[1]!=n or p[n]!=1) puts("2");
		else puts("3");
	}
	return 0;
}
```

---

## 作者：luogu_gza (赞：0)

不难注意到答案 $\leq 3$。

答案为 $0$ 不难。答案为 $1$ 等价于判定 $p_i=i$ 且 $p_{1 \sim i-1}=1 \sim i-1$。这部分可以采用类似于 P3792 的做法，维护和，异或和，平方和即可。

剩下的，若 $a_n=1$ 且 $a_1=n$，则答案为 $3$，否则答案为 $2$，读者可自行构造答案为 $2$ 如何构造。

[code](https://atcoder.jp/contests/arc181/submissions/56343444)。

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

给定一个包含 $1\sim N$ 的序列 $(P_1,P_2,\cdots,P_N)$，每一次操作可以选择一个 $1\le k\le N$，如果 $k\ge 2$ 就将 $P_{1\sim k-1}$ 从小到大排序，如果 $k\le N-1$ 就将 $P_{k+1\sim N}$ 从小到大排序，要使对于每个 $1\le i\le N$ 都有 $P_i=i$，求出 $k_{\min}$。

## 解题思路

首先，对于一个已经从小到大排好序的 $P$，其操作次数肯定是 $0$。再看，对于样例中的 $P=\{2,1,3,5,4\}$，能直接令 $k=3$，一次就可以了，可以发现如果在 $1$ 之后有至少一个数字在它应该在的位置上的话，可以直接让 $k$ 等于这个位置，一次就可以完成。

但是如果没有一个在位置上，或者是有至少一个在位置上，但是这个位置之前的数有的比当前位置要大，比如说样例中的 $P=\{3,2,1,7,5,6,4\}$，此时的 $5,6$ 都在位置上，但是 $5$ 之前有一个 $7>5$，所以当 $k=5$ 时 $P=\{1,2,3,7,5,4,6\}$，此时再令 $k=1$ 就可以排好了，所以这两种情况的次数应该为 $2$。

还有最后一种情况，就是 $P_1=N$ 并且 $P_N=1$ 的时候，此时把前 $N-1$ 个数排序需要一次，把 $N$ 归位需要一次，最后在排一次就可以了，次数就是 $3$，这样这道㵘题就做完了。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
using namespace std;

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    if(x<0) putchar('-'), x=-x;
    if(x>9) write(x/10);
    putchar(x%10+48); return;
}

ll t,n,a[200001],bz,bz2,bz3,p,q;

int main()
{
    t=read();
    
    while(t--)
    {
        n=read(); bz=0; bz2=0; bz3=0;

        for(int i=1; i<=n; ++i)
        {
            a[i]=read();
            if(a[i]!=i) ++bz2;
            if(a[i]<2) p=i;
            if(a[i]==n) q=i;
        }

        if(p==n && q<2) {write(3); endl; continue;}
        if(!bz2) {write(0); endl; continue;}
        bz2=0;

        for(int i=1; i<=n; ++i)
        {
            if(a[i]<2) ++bz;
            if(bz && bz2<i && a[i]==i)
            {write(1); endl; bz3=1; break;}
            bz2=max(bz2,a[i]);
        }

        if(bz3) continue;
        write(2); endl;
    }

    return 0;
}
```

---

