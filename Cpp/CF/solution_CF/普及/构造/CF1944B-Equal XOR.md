# Equal XOR

## 题目描述

You are given an array $ a $ of length $ 2n $ , consisting of each integer from $ 1 $ to $ n $ exactly twice.

You are also given an integer $ k $ ( $ 1 \leq k \leq \lfloor \frac{n}{2} \rfloor  $ ).

You need to find two arrays $ l $ and $ r $ each of length $ \mathbf{2k} $ such that:

- $ l $ is a subset $ ^\dagger $ of $ [a_1, a_2, \ldots a_n] $
- $ r $ is a subset of $ [a_{n+1}, a_{n+2}, \ldots a_{2n}] $
- [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of elements of $ l $ is equal to the bitwise XOR of elements of $ r $ ; in other words, $ l_1 \oplus l_2 \oplus \ldots \oplus l_{2k} = r_1 \oplus r_2 \oplus \ldots \oplus r_{2k} $

It can be proved that at least one pair of $ l $ and $ r $ always exists. If there are multiple solutions, you may output any one of them.

 $ ^\dagger $ A sequence $ x $ is a subset of a sequence $ y $ if $ x $ can be obtained by deleting several (possibly none or all) elements of $ y $ and rearranging the elements in any order. For example, $ [3,1,2,1] $ , $ [1, 2, 3] $ , $ [1, 1] $ and $ [3, 2] $ are subsets of $ [1, 1, 2, 3] $ but $ [4] $ and $ [2, 2] $ are not subsets of $ [1, 1, 2, 3] $ .

## 说明/提示

In the first test case, we choose $ l=[2,1] $ and $ r=[2,1] $ . $ [2, 1] $ is a subset of $ [a_1, a_2] $ and $ [2, 1] $ is a subset of $ [a_3, a_4] $ , and $ 2 \oplus 1 = 2 \oplus 1 = 3 $ .

In the second test case, $ 6 \oplus 4 = 1 \oplus 3 = 2 $ .

## 样例 #1

### 输入

```
4
2 1
1 2 2 1
6 1
6 4 2 1 2 3 1 6 3 5 5 4
4 1
1 2 3 4 1 2 3 4
6 2
5 1 3 3 5 1 2 6 4 6 4 2```

### 输出

```
2 1
2 1
6 4
1 3
1 2
1 2
5 1 3 3
6 4 2 4```

# 题解

## 作者：jiangchen1234 (赞：7)

## Part 1 思路

对于这道题，我们先要发现一下几个规律。

首先在这个长度为 $2 \times n$ 的序列中 $1 \sim n$ 都出现了两次。

我们发现如果前 $1 \sim n$ 中出现了 $k$ 组两个相同的数字，那么前 $n + 1 \sim 2 \times n$ 中也恰好有 $k$ 组两个相同的数字。

我们也能发现前 $1 \sim n$ 个数中所有只出现了 $1$ 次的数字，在前 $n + 1 \sim 2 \times n $ 个数中也只出现了一次。

有了这些条件还不够。

我们还要知道 $x \oplus x = 0$。

有了这些我们看一下如何构造。

我们需要找到两个长度为 $2 \times k$ 的序列。

因为 $x \oplus x = 0$，所以我们可以将两边出现了两次的数字加入到我们所要找的序列中。

做完以上操作后我们会发现两边的结果都为 $0$。

如果我们发现还有地方没有填满的话，我们可以向两个序列加入同时加入一个相同的数字（这个数字只能在前 $1 \sim n$ 个数中出现过一次），这样两边的结果仍然相等。

所以，我们的构造结束了。

## Part 2 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define rg register
#define F(i,l,r) for(int i=l,i##end=r;i<=i##end;++i)
#define G(i,l,r) for(int i=l,i##end=r;i>=i##end;--i)
#define endl '\n'
using namespace std;
il int read() {
	int s = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-')w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
	return s * w;
}
il void write(int x) {
	if(0<=x&&x<=9) {
		putchar(x + '0');
		return ;
	}
	write(x/10);
	putchar(x%10+'0');
}
il int max(int a,int b) {
	return a > b ? a : b;
}
il int min(int a,int b) {
	return a < b ? a : b;
}
int a[50005],b[50005];
int ans1[50005],ans2[50005];
map<int,int> mp1;
map<int,int> mp2;
int cnt1,cnt2,len1,len2;
il void solve(){
	mp1.clear();
	mp2.clear();
	cnt1 = 0;
	cnt2 = 0;
	len1 = 0;
	len2 = 0;
	int n = read(),k = read();
	F(i,1,n){
		a[i] = read();
		++mp1[a[i]];
	}
	F(i,1,n){
		b[i] = read();
		++mp2[b[i]];
	}
	F(i,1,n){
		if(mp1[a[i]] == 2 && len1 <= 2 * k - 2){
			mp1[a[i]] = 0;
			++cnt1;
			len1 += 2;
			ans1[len1 - 1] = ans1[len1] = a[i];
		}
	}
	F(i,1,n){
		if(mp2[b[i]] == 2 && len2 <= 2 * k - 2){
			mp2[b[i]] = 0;
			++cnt2;
			len2 += 2;
			ans2[len2 - 1] = ans2[len2] = b[i];
		}
	}
	F(i,1,n){
		if(len1 < 2 * k && mp1[a[i]] == 1){
			++len1,++len2;
			ans1[len1] = ans2[len2] = a[i];
		}
	}
	F(i,1,2 * k){
		cout<<ans1[i]<<" ";
	}
	cout<<endl;
	F(i,1,2 * k){
		cout<<ans2[i]<<" ";
	}
	cout<<endl;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int T = read();
    while(T--){
        solve();
    }
	return 0;
}
```

[提交记录](https://codeforces.com/contest/1944/submission/251733312)

---

## 作者：cute_overmind (赞：3)

考虑构造。

注意到每个数字都出现 $2$ 次，那么对于一个数 $x$ 分讨即可。

为了方便，将前 $n$ 个称为 $a$，后 $n$ 个称为 $b$。
- 都在 $a$ 中，我们将它都拿直到等于 $k$。
- 都在 $b$ 中，我们将它都拿直到等于 $k$。

此时 $a$ 中的数量与 $b$ 中数量显然相等。
且由于我们加入的方式，两侧异或和都为 $0$。

接下来考虑一个在 $a$，一个在 $b$，两边同时加入即可。

尝试证明：

由于一个数 $x$ 不是在 $a$，就是在 $b$，故我们最多可以拿满 $n$，且一定成立。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200010;

int a[N];
void solve(){
	int n;
	map<int, int> h, t;
	cin >> n;
	for(int i = 1 ; i <= n ; i ++)
		cin >> a[i];
	int z = 0, l = n + 1, r = 0;
	for(int i = 1 ; i <= n ; i ++)
		if(a[i] == 0) z ++, l = min(l, i), r = max(r, i);
	if(z == 0){
		cout << n << '\n';
		for(int i = 1 ; i <= n ; i ++)
			cout << i  << ' ' << i << '\n';
	}
	else if(z == 1) cout << "-1\n";
	else{
		for(int i = 1 ; i <= l ; i ++) h[a[i]] = 1;
		for(int i = n ; i >= r ; i --) t[a[i]] = 1;
		int now = 1;
		while(l < r){
			if(! h[now]) while(a[++ l] != now && l < r) h[a[l]] = 1;
			if(l != r) h[a[l]] = 1;
			if(! t[now]) while(a[-- r] != now && l < r) t[a[r]] = 1;
			if(l != r) t[a[r]] = 1;
			now ++;
		}
		now = 1;
		while(h[now] && t[now]) now ++;
		if(h[now] || t[now]) cout << "-1\n";
		else cout << 2 << '\n' << 1 << ' ' << l - 1 << '\n' << l << ' ' << n << '\n';
	}
}

signed main(){
	int t;
	cin >> t;
	while(t --)
		solve();

	return 0;
}
```

---

## 作者：Shadow_T (赞：3)

### 解题思路

这题的重点是每个数只出现 $2$ 次。

先用 map 统计下 $a_i$ 出现次数。

- 如果一个数在前半段出现 $1$ 次，后半段 $1$ 次，那么我们把他加入前面的异或序列 $1$ 次，后面的 $1$ 次。

- 若在前半段出现 $2$ 次，我们知道 $x \oplus x=0$ 且 $x \oplus 0=x$，所以直接把他加入前面的异或序列 $2$ 次，对异或和没有影响。

- 若在后半段出现 $2$ 次，同理；把他加入后面的异或序列 $2$ 次。

因为他让我们输出左边 $2k$ 个，右边 $2k$ 个。我们输出异或序列前 $2k$ 个。为了防止把加入 $2$ 次的拆散，所以如果两边都加入的数的总数为奇数，就拿出其中一个。

时间复杂度 $\mathcal{O}(n\log n)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int a[maxn],b[maxn];
void solve()
{
	int n,k;
	cin>>n>>k;
	map<int,int>mp1,mp2;
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]),mp1[a[i]]++;
	for(int i=1;i<=n;i++)
	scanf("%d",&b[i]),mp2[b[i]]++;
	vector<int> ansa,ansb;
	for(int i=1;i<=n;i++)
	if(mp1[i]==1) ansa.push_back(i),ansb.push_back(i);
	if(ansa.size()<2*k&&ansa.size()%2==1) ansa.pop_back(),ansb.pop_back();
	for(int i=1;i<=n;i++)
	if(mp1[i]==2) ansa.push_back(i),ansa.push_back(i);
	for(int i=1;i<=n;i++)
	if(mp2[i]==2) ansb.push_back(i),ansb.push_back(i);
	for(int i=0;i<2*k;i++)
	cout<<ansa[i]<<" ";
	cout<<"\n";
	for(int i=0;i<2*k;i++)
	cout<<ansb[i]<<" ";
	cout<<"\n";
}
int main()
{
	int t;
	cin>>t;
	while(t--) solve(); 
}
```

---

## 作者：Blikewsr (赞：2)

### [CF1944B - Luogu](https://www.luogu.com.cn/problem/CF1944B)

### [CF1944B - CodeForces](https://codeforces.com/problemset/problem/1944/B)

### 题目简述

**理解**一下题目：

给定一个数列 $A_{2n}$，其中 $[1, n]$ 之间的整数在数列中均出现 **两次**。给定一个整数 $k$，需要在数列的 **前半段** 和 **后半段** 各找出 $2k$ 个数，使得前半段找出的数的 **异或和** 等于后半段找出的数的  **异或和**。

### 思路分析

首先，我们知道一个基本事实，对于一个数 $x$，有 $x \operatorname{xor} x = 0$ 恒成立。

同时，我们还可以知道，前半段和后半段在出现 $1$ 次和 $2$ 次的数量上是对称的。

**证明：**

> 假设：前半段中出现过 **两次** 的数的个数为 $x (x \le \frac{n}{2})$，后半段中出现过 **两次** 的数的个数为 $y$，则
>
> 前半段仅出现过 **一次** 的数的个数为 $\frac{n}{2} - x$
> 
> 所以，后半段仅出现过 **一次** 的数的个数也为 $\frac{n}{2} - x$
> 
> 所以，$y = \frac{n}{2} - (\frac{n}{2} - x) = x$

所以，我们只需要先把前半段和后半段的出现过 $2$ 次的数记录进答案，使得这些数的 **异或和** 为 $0$，如果数量达到了题目要求，直接输出即可。

那如果数量没有达到，我们直接把剩下之出现过 $1$ 次的数加入答案就好了。

**其他细节见代码注释**

### 代码实现

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e4 + 5;
int T, n, k, cntA, cntB, mp[2][N], v[2][N], A[N << 1], B[N << 1];
signed main() {
    cin >> T;
    while (T --) {   // 多测
        cin >> n >> k; cntA = 0, cntB = 0;
        memset(v, 0, sizeof(v));  // 初始化 
        for (int i = 1; i <= n; ++ i) {
            cin >> mp[0][i];
            ++ v[0][mp[0][i]];  // 记录数列左半边每一个数在左边出现的次数
        }
        for (int i = 1; i <= n; ++ i) {
            cin >> mp[1][i];
            ++ v[1][mp[1][i]];  // 记录数列右半边每一个数在右边出现的次数
        }
        for (int i = 1; i <= n; ++ i) {
            if (v[0][i] == 2) {  // 左边出现了 2 次的，直接异或得到 0，对答案没有影响
                A[++ cntA] = i;
                A[++ cntA] = i; // 记录下这些数
            }
            if (v[1][i] == 2) {  // 右边出现了 2 次的，同上
                B[++ cntB] = i;
                B[++ cntB] = i;
            }
        }
        if (cntA >= k * 2) {
            // 每一个数只在一半边出现
            for (int i = 1; i <= k * 2; ++ i)
                cout << A[i] << ' ';
            cout << '\n';  // 左边
            for (int i = 1; i <= k * 2; ++ i)
                cout << B[i] << ' ';
            cout << '\n';  // 右边
        }
        else {
            // 有一些数在两半边都有
            for (int i = 1; i <= n; ++ i) {
                if (cntA >= k * 2) break;
                if (v[0][i] == 1) A[++ cntA] = i, B[++ cntB] = i;
                // 把这些之出现一次的数记录下来
            }
            for (int i = 1; i <= k * 2; ++ i) 
                cout << A[i] << ' ';
            cout << '\n';
            // 输出这两种数（左边）
            for (int i = 1; i <= k * 2; ++ i) 
                cout << B[i] << ' ';
            cout << '\n';
            // 右边
        }
    }
    return 0;
}
```

[**CodeForces 提交记录**](https://codeforces.com/contest/1944/submission/288915310)

---

## 作者：zcr0202 (赞：2)

## 题目大意

给你一个长度为 $2 \times n$ 的序列，前 $n$ 个为序列 $A$，后 $n$ 个为序列 $B$。让你从这两个序列中各取出 $2 \times k$ 个数，要求它们的异或和相等。求这两串数。

## 解题思路

首先我们要知道两个结论。

- 如果 $a=b$，那么 $a \oplus c=b \oplus c$
  
- $a=a \oplus b \oplus b$
  

因为这个序列的数的范围在 $1 \sim n$，每个数只出现了两次。所以两个相同的数要么在序列 $A$ 或序列 $B$，要么一个在序列 $A$，一个在序列 $B$。当他们在同一个序列时，就直接异或，结果不变。否则就两边各异或一个数，结果也不变。所以就做完了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e4 + 5;
int n, k;
int a[N], b[N];
int s1[N], s2[N];
int d1, d2;
int bz1[N], bz2[N];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;
	cin >> T;
	while(T--) {
		memset(bz1, 0, sizeof(bz1));
		memset(bz2, 0, sizeof(bz2));
		memset(s1, 0, sizeof(s1));
		memset(s2, 0, sizeof(s2));
		d1 = d2 = 0;
		cin >> n >> k;
		k *= 2;
		for(int i = 1; i <= n; i++) {
			cin >> a[i];
			bz1[a[i]]++;
		}
		for(int i = 1; i <= n; i++) {
			cin >> b[i];
			bz2[b[i]]++;
		}
		for(int i = 1; i <= n; i++) {
			if(bz1[i] == 2 && d1 < k) {
				s1[++d1] = i;
				s1[++d1] = i;
			}
			if(bz2[i] == 2 && d2 < k) {
				s2[++d2] = i;
				s2[++d2] = i;
			}
		}
		if(d1 > d2) {
			d1 = d2;
		}
		else {
			d2 = d1;
		}
		for(int i = 1; i <= n; i++) {
			if(bz1[i] == 1 && bz2[i] == 1 && d1 < k && d2 < k) {
				s1[++d1] = i;
				s2[++d2] = i;
			}
		}
		for(int i = 1; i <= d1; i++) {
			cout << s1[i] << " ";
		} cout << '\n';
		for(int i = 1; i <= d2; i++) {
			cout << s2[i] << " ";
		} cout << '\n';
	}
}
```

---

## 作者：Red_river (赞：1)

## 题目大意
题目中说明了会给你一个长度为 $2n$ 的数组，然后让你求使得前 $n$ 个之中的 $2k$ 个数的异或和与后 $n$ 个之中的 $2k$ 个数的异或和相等。
### 分析题意
其实我们可以发现，当两个数相等时，他们的异或和相同，也就是说不会影响到结果，我们就可以直接输出相等的情况，而剩下也就只有不相等的了，但是也就说明每组中的数都各有一个这种数，所以也是直接特判并输出。因为毕竟两边的数都相等了，那肯定异或和也就相等了。
### CODE
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register int
#define N 50005
#define INF 2147483647
#define f(x,k,y,z) for(int x=k;x<=y;x+=z)
using namespace std;
int n,m,k,jk,ans,sum,num;
int tot,a[N],b[N],dis[N],vis[N],bz[N];
void read(int &x)
{
	x=0;int ff=1;
	char ch=getchar();
	while (ch<'0'||ch>'9')
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	x*=ff;return;
}

void write(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}

void qsort(int i,int j)
{
    int mid=a[(i+j)/2+1],l=i,r=j;
    while(i<=j)
    {
        while(a[i]<mid)i++;
        while(a[j]>mid)j--;
        if(i<=j)
        {
            swap(a[i],a[j]);
            i++,j--;
        }
    }
    if(l<j) qsort(l,j);
    if(i<r) qsort(i,r);
}

void qsort1(int i,int j)
{
    int mid=b[(i+j)/2+1],l=i,r=j;
    while(i<=j)
    {
        while(b[i]<mid)i++;
        while(b[j]>mid)j--;
        if(i<=j)
        {
            swap(b[i],b[j]);
            i++,j--;
        }
    }
    if(l<j) qsort1(l,j);
    if(i<r) qsort1(i,r);
}

int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(tot);
	while(tot--)
	{
		read(n),read(m);int x,y;jk=k=x=y=0;
		for(int i=1;i<=n;i++) dis[i]=vis[i]=bz[i]=0;
		for(int i=1;i<=n;i++) read(a[i]),dis[a[i]]++;
		for(int i=1;i<=n;i++) read(b[i]),vis[b[i]]++;
		for(int i=1;i<=n;i++)
		if(dis[i]==2&&x<2*m)
		x+=2,printf("%d %d ",i,i);
		for(int i=1;i<=n;i++)
		if(dis[i]==1&&bz[i]==0&&x<2*m&&y<2*m)
		bz[i]=1,x++,y++,printf("%d ",i);
		printf("\n");
		for(int i=1;i<=n;i++)
		if(vis[i]==2&&y<2*m)
		y+=2,printf("%d %d ",i,i);
		for(int i=1;i<=n;i++)
		if(vis[i]==1&&bz[i]==0&&x<2*m&&y<2*m)
		bz[i]=1,x++,y++,printf("%d ",i);
		else if(bz[i]==1) printf("%d ",i);
		printf("\n");
	}
	return 0;
}

```

---

## 作者：Eason_cyx (赞：1)

将 $1\sim n$ 分为 $3$ 类：第一类是两个 $i$ 都在前半部分；第二类是两个 $i$ 都在后半部分；第三类是一个 $i$ 在前半部分，另一个 $i$ 在后半部分。

我们可以先尽量往答案里添加两个数在同一部分的数 $i$，因为两个相同的数异或值为 $0$，所以可以保证整体异或值相等。如果数量不够，再添加一个在前，一个在后的数 $j$，当两边异或值都为 $0$ 时，同时添加一个相等的数，此时异或值也不变。

单组时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005];
int z[100005];
int num[100005];
int ansa[50005],ansb[50005];
int main() {
    int t; cin >> t;
    while(t--) {
    	memset(num,0,sizeof num);
        int n,k; cin >> n >> k;
        for(int i = 1;i <= n;i++) {
            cin >> a[i];
            num[a[i]]++;
        }
        for(int i = 1;i <= n;i++) {
            if(num[i] == 2) {
                z[i] = 1;
            }
            else if(num[i] == 0) {
                z[i] = 2;
            }
            else {
                z[i] = 0;
            }
        }
        for(int i = n+1;i <= 2 * n;i++) cin >> a[i];
        int cura = 0,curb = 0;
        for(int i = 1;i <= n;i++) {
            if(z[i] == 1) {
                if(cura >= 2 * k - 1) continue;
                ansa[++cura] = i;
                ansa[++cura] = i;
            }
            else if(z[i] == 2) {
                if(curb >= 2 * k - 1) continue;
                ansb[++curb] = i;
                ansb[++curb] = i;
            }
        }
        cura = min(cura,curb); curb = min(cura,curb);
        int cha = 2 * k - cura;
        for(int i = 1;i <= n;i++) {
            if(z[i] == 0) {
                if(cura >= 2 * k) break;
                ansa[++cura] = i;
                ansb[++curb] = i;
            }
        }
        // for(int i = 1;i <= n;i++) {
        	// cout << z[i] << " \n"[i == n];
        // }
        // cout << endl;
        for(int i = 1;i <= cura;i++) cout << ansa[i] << " \n"[i == cura];
        for(int i = 1;i <= curb;i++) cout << ansb[i] << " \n"[i == curb];
    }
    return 0;
}
```

记得 `memset`。

[AC Record:Time 151ms,Memory 1576KB](https://codeforces.com/contest/1944/submission/251767396)

---

## 作者：wxzzzz (赞：1)

### 题意

给定一个长度为 $2n$ 的序列 $a$，其中 $a_i\in[1,n]$，且 $1\sim n$ 中任意一个数字恰好在 $a$ 中出现两次。

从 $a_1\sim a_n$ 中取一个长度为 $2k$ 的子集 $l$，从 $a_{n+1}\sim a_{2n}$ 中取一个长度为 $2k$ 的子集 $r$，使得 $l_1\oplus l_2\oplus\cdots\oplus l_{2k}=r_1\oplus r_2\oplus\cdots\oplus r_{2k}$。可以证明一定有解。

### 思路

考虑对所有 $a_1\sim a_n$ 分类讨论。

1. 对于所有在 $a_1\sim a_n$ 出现了两次的 $a_i$，可以将其两次选入 $l$。因为 $a_i\oplus a_i=0$，所以 $l$ 异或和不变。

1. 对于所有在 $a_1\sim a_n$ 出现了一次的 $a_i$，可以将其分别选入 $l,r$。两个集合的异或和同时异或一个数，仍然相等。

因此，可以将所有 $a_i$ 分类存起来，依次选入 $l,r$ 使得 $l,r$ 异或和相等，具体详见代码。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, k, cnt1, cnt2, a[100005], b[100005], c[100005], d[100005], cnt[100005];
bitset<100005> flag;
int main() {
    cin >> t;

    while (t--) {
        cin >> n >> k;
        cnt1 = cnt2 = 0;

        for (int i = 1; i <= n; i++)
            cnt[i] = flag[i] = 0;

        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            cnt[a[i]]++;

            if (cnt[a[i]] == 2)
                c[++cnt1] = a[i];
        }

        for (int i = 1; i <= n; i++)
            cnt[i] = 0;

        for (int i = 1; i <= n; i++) {
            cin >> b[i];
            cnt[b[i]]++;

            if (cnt[b[i]] == 2)
                d[++cnt2] = b[i];
        }

        int now = k * 2;

        for (int i = 1; i <= min(cnt1, cnt2) && now >= 2; i++) {
            flag[c[i]] = 1;
            cout << c[i] << ' ';
            cout << c[i] << ' ';
            now -= 2;
        }

        for (int i = 1; i <= n && now; i++) {
            if (!flag[a[i]]) {
                cout << a[i] << ' ';
                now--;
            }
        }

        cout << '\n';
        now = k * 2;

        for (int i = 1; i <= min(cnt1, cnt2) && now >= 2; i++) {
            cout << d[i] << ' ';
            cout << d[i] << ' ';
            now -= 2;
        }

        for (int i = 1; i <= n && now; i++) {
            if (!flag[a[i]]) {
                cout << a[i] << ' ';
                now--;
            }
        }

        cout << '\n';
    }

    return 0;
}
```

---

## 作者：114514xxx (赞：1)

先考虑 $[{a_1, a_2,\ldots a_n}]$ 和 $[a_{n+1}, a_{n+2}, \ldots a_{2n}]$ 中每个数出现的次数。若数 $x$ 出现了 $2$ 次，则根据 $x \oplus x =0$，那么 $x$ 可以成对加入 $l$ 或 $r$ 且不影响异或和。

我们又可以注意到如果有 $m$ 种数字在 $[{a_1, a_2,\ldots a_n}]$ 出现了两次，那么也会有 $m$ 种数字在 $[a_{n+1}, a_{n+2}, \ldots a_{2n}]$ 出现了两次。此时直接将这 $2m$ 个数字分别加入 $l$ 和 $r$ 当中。

若此时还有剩余空位可以加入，那么往 $l$ 和 $r$ 中直接加入相同的且只出现一次的数字即可。具体做法详见代码。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+25;
int a[N];
map<int,int>mp1,mp2;
int l[N],r[N];
int main(){
    std::ios::sync_with_stdio(0);
    int t;
    cin>>t;
    while(t--){
        mp1.clear(),mp2.clear();
        int cnt1=0,cnt2=0;
        int n,k;
        cin>>n>>k;
        for(int i=1;i<=2*n;i++)
            cin>>a[i];
        for(int i=1;i<=n;i++){
            ++mp1[a[i]];
            if(mp1[a[i]]==2)
                l[++cnt1]=a[i],l[++cnt1]=a[i];
        }
        for(int i=n+1;i<=2*n;i++){
            ++mp2[a[i]];
            if(mp2[a[i]]==2)
                r[++cnt2]=a[i],r[++cnt2]=a[i];
        }
        if(cnt1){
            int num=cnt1;
            for(int i=1;i<=n;i++){
                if(mp1[a[i]]==1){
                    ++cnt1;
                    l[cnt1]=a[i];
            }
                if(cnt1==2*k)break;
            }
            for(int i=num+1;i<=2*k;i++)
                r[i]=l[i];
            for(int i=1;i<=2*k;i++)
                cout<<l[i]<<' ';
            cout<<endl;
            for(int i=1;i<=2*k;i++)
                cout<<r[i]<<' ';
            cout<<endl;
        }else{
            //若两边所有数字只出现了一次
            for(int i=1;i<=2*k;i++)
                cout<<i<<" ";
            cout<<endl;
            for(int i=1;i<=2*k;i++)
                cout<<i<<' ';
            cout<<endl;
        }
    }
}

```

---

## 作者：Special_Tony (赞：1)

# 异或的性质
1. $x$ 异或 $x$ 等于 $0$；
2. $0$ 异或 $x$ 是 $x$。

# 思路
注意题目中说每个数恰好出现 $2$ 次，所以每个数可能在两边各出现一个，这种情况要两边一起选，使结果里多这个数；也可能在同一边出现两次，这样需要把它们两个数一起选，但对这个数不起作用。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int t, n, x, k, v1[50005], v2[50005], tot1, tot2;
bitset <50005> vis1, vis2;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> k;
		for (int i = 1; i <= n; ++ i)
			vis1[i] = vis2[i] = 0;
		for (int i = 1; i <= n; ++ i)
			cin >> x, vis1[x] = 1;
		for (int i = 1; i <= n; ++ i)
			cin >> x, vis2[x] = 1;
		tot1 = tot2 = 0;
		for (int i = 1; i <= n; ++ i)
			if (vis1[i] && ! vis2[i])
				v1[++ tot1] = i;
			else if (vis2[i] && ! vis1[i])
				v2[++ tot2] = i; 
		if (tot1 >= k) {
			for (int i = 1; i <= k; ++ i)
				cout << v1[i] << ' ' << v1[i] << ' ';
			cout << '\n';
			for (int i = 1; i <= k; ++ i)
				cout << v2[i] << ' ' << v2[i] << ' ';
			cout << '\n';
		} else {
			for (int i = 1; i <= n; ++ i)
				if (vis1[i] && vis2[i])
					++ tot2, v1[tot2] = v2[tot2] = i;
			tot2 = k * 2 - tot1;
			for (int i = 1; i <= tot1; ++ i)
				cout << v1[i] << ' ' << v1[i] << ' ';
			for (int i = tot1 + 1; i <= tot2; ++ i)
				cout << v1[i] << ' ';
			cout << '\n';
			for (int i = 1; i <= tot1; ++ i)
				cout << v2[i] << ' ' << v2[i] << ' ';
			for (int i = tot1 + 1; i <= tot2; ++ i)
				cout << v2[i] << ' ';
			cout << '\n';
		}
	}
	return 0;
}
```

---

## 作者：xuyiyang (赞：0)

### Solution
发现一个数异或自己不变，所以先尽量在序列中出现两次的扔进去。然后在将左右各出现一次的数扔进去。由于序列出现两次的数的组数一定相同，且先放出现两次的不会出现两个数被前面奇数个数放不进的可能，于是算法正确性得证。时空复杂度线性。
### Code
```cpp
void solve() {
	scanf("%d%d", &n, &k); for (int i = 1; i <= n; i ++ ) c1[i] = c2[i] = vector<int>();
	for (int i = 1, x; i <= n; i ++ ) scanf("%d", &x), c1[x].push_back(i);
	for (int i = 1, x; i <= n; i ++ ) scanf("%d", &x), c2[x].push_back(i);
	vector<PII> L, R;
	for (int i = 1; i <= n; i ++ ) if (c1[i].size() == 2) while (c1[i].size()) L.push_back({c1[i].back(), i}), c1[i].pop_back();
	for (int i = 1; i <= n; i ++ ) if (c2[i].size() == 2) while (c2[i].size()) R.push_back({c2[i].back(), i}), c2[i].pop_back();
	for (int i = 1; i <= n; i ++ ) if (c1[i].size() == c2[i].size()) 
		while (c1[i].size()) {
			L.push_back({c1[i].back(), i}), R.push_back({c2[i].back(), i});
			c1[i].pop_back(), c2[i].pop_back();
		}
	L.erase(L.begin() + 2 * k, L.end()); R.erase(R.begin() + 2 * k, R.end());
	sort(L.begin(), L.end()), sort(R.begin(), R.end());
	for (PII v : L) printf("%d ", v.second); puts("");
	for (PII v : R) printf("%d ", v.second); puts("");
}
```

---

## 作者：Wf_yjqd (赞：0)

写慢了。

------------

考虑每个数两次出现的位置。

无论是两边各一个还是都在同一边，我们都将两个捆绑选。

那么前者相当于让两个长度 $+1$，后者相当于其中一个 $+2$。

题目要求长度为偶，所以将两个 $+1$ 捆绑，然后随便凑出 $2k$ 即可。

------------

代码中采用的方法是先尽可能多取 $+2$，剩下的用 $+1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+26;
int T,n,k,a,l[maxn],r[maxn],ans[2][maxn],top[2];
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
            l[i]=r[i]=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a);
            l[a]=1;
        }
        for(int i=1;i<=n;i++){
            scanf("%d",&a);
            r[a]=1;
        }
        top[0]=top[1]=0;
        for(int i=1;i<=n;i++)
            if(l[i]&&!r[i]){
                ans[0][++top[0]]=i;
                ans[0][++top[0]]=i;
            }
            else if(!l[i]&&r[i]){
                ans[1][++top[1]]=i;
                ans[1][++top[1]]=i;
            }
        top[0]=top[1]=min(top[0],top[1]);
        if(top[0]<k*2)
            for(int i=1;i<=n;i++)
                if(l[i]&&r[i]){
                    ans[0][++top[0]]=i;
                    ans[1][++top[1]]=i;
                }
        for(int i=1;i<=k*2;i++)
            printf("%d ",ans[0][i]);
        puts("");
        for(int i=1;i<=k*2;i++)
            printf("%d ",ans[1][i]);
        puts("");
    }
    return 0;
}
```

---

## 作者：SJH__qwq (赞：0)

有史以来最难写的 Div2 B 题，纪念一下。

首先考虑按位异或（$\tt{xor}$）运算的性质。

+ $x\ {\tt{xor}}\ 0=x$
+ $x\ {\tt{xor}}\ x=0$
+ $(a\ {\tt{xor}}\ x)\ {\tt{xor}}\ b=a\ {\tt{xor}}\ (x\ {\tt{xor}}\ b)$
+ $a\ {\tt{xor}}\ x=b\ {\tt{xor}}\ x$ 可以和 $a=b$ 互推。

考虑使用这些性质来解决问题。

首先考虑在序列的两边分别搞事情。因为选择两个相同的数对于异或运算而言不构成贡献，所以能选两个相邻的数，就一定要选两个相邻的数。

但是这样不一定能够把 $2k$ 个数全部凑完。所以考虑运用最后一条性质，把两边均恰好出现 $1$ 次的数利用起来选择。容易证明这样一定能够得到一组合法的方案。

直接构造即可。单组数据的时间复杂度为 $O(n)$。

---

## 作者：hh弟中弟 (赞：0)

把整个序列中的前 $n$ 个数看做序列 $A$，后半部分看做序列 $B$，因为 $1$ 到 $n$ 每个数都只会出现两次，所以有如下情况：
- 数字 $x$ 在序列 $A$ 和序列 $B$ 中分别出现一次。
- 数字 $x$ 只在一个序列中出现了两次，此时必然有数字 $y$ 只在另一个序列中出现了两次。

根据上面两种情况，我们可以统计每个数在两个序列中分别出现的次数，使最后的异或结果为 $0$。

因为两个序列中出现两次的数的个数显然是相等的，并且一个序列中只出现一次的数必然也会在另一个序列中出现一次。

设出现两次的数的个数为 $size$，当 $k\le size$ 时，我们可以全部选取出现两次的数，他们的异或和为 $0$。

当 $k>size$ 时，可以选取所有出现两次的数，然后剩下的数选择在两个序列中只出现一次的同样的数即可。

具体实现看代码
```cpp
#include<bits/stdc++.h>
inline int read(){
	char ch=getchar();int x=0,f=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
const int N=1e5+10;
int a[N],b[N],t1[N],t2[N];
std::vector<int> x,y;
int main(){
	// freopen("in.in","r",stdin),freopen("out.out","w",stdout);
	std::ios::sync_with_stdio(false);std::cin.tie(0),std::cout.tie(0);
	int T=read();
	while(T--){
		int n=read(),k=read();
		int ans=0;
		for(int i=1;i<=n;++i){a[i]=read(),t1[a[i]]++;if(t1[a[i]]==2)x.push_back(a[i]);}
		for(int i=1;i<=n;++i){b[i]=read(),t2[b[i]]++;if(t2[b[i]]==2)y.push_back(b[i]);}
      		//储存每个序列中出现两次的数
		if(x.size()>=k){//分类讨论
			for(int i=0;i<k;++i)std::cout<<x[i]<<' '<<x[i]<<' ';std::cout<<'\n';
			for(int i=0;i<k;++i)std::cout<<y[i]<<' '<<y[i]<<' ';std::cout<<'\n';
		}else{
			for(int i:x)std::cout<<i<<' '<<i<<' ';
			k=k*2-x.size()*2;int tot=0;
			for(int i=1;i<=n;++i){
				if(t1[i]==1)std::cout<<i<<' ',tot++;
				if(tot==k)break;
			}std::cout<<'\n';tot=0;
			for(int i:y)std::cout<<i<<' '<<i<<' ';
			for(int i=1;i<=n;++i){
				if(t2[i]==1)std::cout<<i<<' ',tot++;
				if(tot==k)break;
			}std::cout<<'\n';
		}
		x.clear(),y.clear();
		for(int i=1;i<=n;++i)t1[i]=t2[i]=0;
      		//清空数组
	}
}
```

---

