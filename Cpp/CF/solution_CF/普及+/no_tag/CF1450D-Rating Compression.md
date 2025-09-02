# Rating Compression

## 题目描述

On the competitive programming platform CodeCook, every person has a rating graph described by an array of integers $ a $ of length $ n $ . You are now updating the infrastructure, so you've created a program to compress these graphs.

The program works as follows. Given an integer parameter $ k $ , the program takes the minimum of each contiguous subarray of length $ k $ in $ a $ .

More formally, for an array $ a $ of length $ n $ and an integer $ k $ , define the $ k $ -compression array of $ a $ as an array $ b $ of length $ n-k+1 $ , such that $ $$$b_j =\min_{j\le i\le j+k-1}a_i $ $ </p><p>For example, the  $ 3 $ -compression array of  $ \[1, 3, 4, 5, 2\] $  is  $ \[\\min\\{1, 3, 4\\}, \\min\\{3, 4, 5\\}, \\min\\{4, 5, 2\\}\]=\[1, 3, 2\]. $ </p><p>A permutation of length  $ m $  is an array consisting of  $ m $  distinct integers from  $ 1 $  to  $ m $  in arbitrary order. For example,  $ \[2,3,1,5,4\] $  is a permutation, but  $ \[1,2,2\] $  is not a permutation ( $ 2 $  appears twice in the array) and  $ \[1,3,4\] $  is also not a permutation ( $ m=3 $  but there is  $ 4 $  in the array).</p><p>A  $ k $ -compression array will make CodeCook users happy if it will be a permutation. Given an array  $ a $ , determine for all  $ 1\\leq k\\leq n $  if CookCook users will be happy after a  $ k$$$-compression of this array or not.

## 说明/提示

In the first test case, $ a=[1, 5, 3, 4, 2] $ .

- The $ 1 $ -compression of $ a $ is $ [1, 5, 3, 4, 2] $ and it is a permutation.
- The $ 2 $ -compression of $ a $ is $ [1, 3, 3, 2] $ and it is not a permutation, since $ 3 $ appears twice.
- The $ 3 $ -compression of $ a $ is $ [1, 3, 2] $ and it is a permutation.
- The $ 4 $ -compression of $ a $ is $ [1, 2] $ and it is a permutation.
- The $ 5 $ -compression of $ a $ is $ [1] $ and it is a permutation.

## 样例 #1

### 输入

```
5
5
1 5 3 4 2
4
1 3 2 1
5
1 3 3 3 2
10
1 2 3 4 5 6 7 8 9 10
3
3 3 2```

### 输出

```
10111
0001
00111
1111111111
000```

# 题解

## 作者：Eibon (赞：4)

可以理解这道题为，一个长度为 $k$ 的滑块在数组上滑动，滑块的值为滑块所在区间内最小值。判断滑块的值构成的数组是否是一个排列。

### 方法一

如果 $k=1$ ,那么这个数组必须是 $1$ 到 $n$ 的一个排列。

如果 $k=n$ ,那么这个数组必须要有 $1$。

从 $k=n-1$ 思考，发现 $1$ 必须只能出现在所有区间的首部或尾部，不然 $1$ 一定会出现两次，然后让 $2$ 在另外一个区间即可。

考虑 $k=n-2$ ,因为1已经考虑过所以不再考虑，同理，发现 $2$ 在剩余的区间中只能取头或尾。以此类推。

容易想到，如果 $k$ 不可行，则接下来一定也不可行，因为接下来的区间会涵盖之前的值，并且可能会产生新的不合法情况。

最后特判 $1$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=3e5+5;
const int mod=998244353;
int T,n,m,ans,flag;
int a[maxn],st[maxn][20],num[maxn];
signed main()
{
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			num[i]=0;
		}
		flag=1;
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			num[a[i]]++;
			if(num[a[i]]>1){
				flag=0;
			}
		}
		int d=1,l=1,r=n;
		printf("%lld",flag);
		for(int i=n-1;i>=2;i--){
			if(num[n-i]!=1||(a[l]!=n-i&&a[r]!=n-i)||!num[n-i+1]){
				d=i;
				break;
			}
			if(a[l]==n-i){
				l++;
			}
			else{
				r--;
			}
		}
		for(int i=2;i<=n-1;i++){
			if(i>d){
				printf("1");
			}
			else{
				printf("0");
			}
		}
		if(n==1){
			printf("\n");
			continue;
		}
		if(num[1]){
			printf("1");
		}
		else{
			printf("0");
		}
		printf("\n");
	}
	return 0;
}
//dyyyyds
```

### 方法二

一个区间的最小值，很容易让人联想到 st 表。

不妨二分区间长度 $k$。用 st 表预处理区间最小值。

同样需特判 $1$ 。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=3e5+5;
const int mod=998244353;
int T,n,m,ans,flag,l,r;
int a[maxn],st[maxn][20],num[maxn];
int VIP(int l,int r)
{
	int num=log2(r-l+1);
	return min(st[l][num],st[r-(1<<num)+1][num]);
}
void VVIP()
{
	for(int i=1;i<=n;i++)st[i][0]=a[i];
	for(int x=1;x<=20;x++){
		for(int i=1;i+(1<<x)-1<=n;i++){
			st[i][x]=min(st[i][x-1],st[i+(1<<(x-1))][x-1]);
		}
	}
}
bool check(int x)
{
	for(int i=1;i<=n;i++){
		num[i]=0;
	}
	for(int i=1;i+x-1<=n;i++){
		int j=i+x-1;
		int m=VIP(i,j);
		num[m]++;
		if(num[m]>1)return 0;
	}
	for(int i=1;i<=n-x+1;i++){
		if(!num[i]){
			return 0;
		}
	}
	return 1;
}
signed main()
{
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
		}
		VVIP();
		l=2,r=n;
		ans=1e18;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid)){
				ans=mid;
				r=mid-1;
			}
			else{
				l=mid+1;
			}
		}
		if(check(1)){
			printf("1");
		}
		else{
			printf("0");
		}
		for(int i=2;i<=n;i++){
			if(i>=ans){
				printf("1");
			}
			else{
				printf("0");
			}
		}
		printf("\n");
	}
	return 0;
}
//dyyyyds
```

---

## 作者：minecraft_herobrine (赞：3)

一个 k 的分解实质上就是按照上面的式子留下 $n-k+1$ 个数字，而当 $k=1$ 时，$c$ 中 仅有一个数字就是 $1$ 时才能满足

而当 $k=n$ 时，$c$ 数列和 $a$ 数列时完全相同的，也就是说当 $a$ 就是 $1-n$ 的一个排列时它才满足是好的压缩数列。

我们在这里用一个双端队列，初始先统计一下 $a$ 中每个数字都出现了多少次，再将 $a$ 的元素由 $1$ 至 $n$ 从前端插入双端队列。由 $1$ 到 $n$ 依次枚举 $c$ 数组的长度，若一个数字 i 在 a 中出现了两次及以上或没有出现时，则长度为 $i$ 及以上的所有 $c$ 数组都时不好的了，应当直 接跳出循环。 如果这个 $i$ 恰好在 $a$ 中出现一次，就看它在双端队列中时处在队头还是队尾。找到后把 它弹出队列。但如果它既不是队头也不是队尾时，那当前的 $i$ 时最后一个好的 $c$ 数列。这里 可以这样理解一下：第一次出现这种情况时，一定不再$i=1$的时候，并且 $i$ 两边的数一定都 比 $i$ 大（因为比 $i$ 小的数都已经出队了），这样的话 $i$ 一定在至少两个区间中取得最小值，比 $i$ 大的任何数就都不满足题意了。 在循环中把所有的 $i$ 取得的结果都按顺序放入一个答案数组中，最后倒序输出即可。

# code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll MAXN=3e5+10;
deque<ll> q;
ll cnt[MAXN],res[MAXN];
int main()
{
	ll T,n,m,i,j;
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n);
		memset(res,0,sizeof(res));
		memset(cnt,0,sizeof(cnt));
		while(!q.empty()) q.pop_back();
		for(i=1;i<=n;i++)
		{
			scanf("%lld",&m);
			q.push_front(m);
			cnt[m]++;
		}
		for(i=1;i<=n;i++)
		{
			if(cnt[i]==0) break;
			res[i]=1;
			if(cnt[i]>1) break;
			if(q.front()==i) q.pop_front();
			else if(q.back()==i) q.pop_back();
			else break;
		}
		ll s=1;
		for(i=1;i<=n;i++)
			if(cnt[i]!=1) s=0;
		res[n]=s;
		for(i=n;i>=1;i--) printf("%lld",res[i]);
		printf("\n");
	}
	return 0;
}

```


---

## 作者：JWRuixi (赞：1)

~~是不是我写法太蠢，我跳了好久……~~
- 题意

给定长度为 $n$ 的序列 $a$ 和正整数 $k$，一如下方式生成 $b$：

$$b_j=\min\limits_{i=j}^{j+k-1}a_i$$ 

给定 $a$，求有那些 $k\le n$，使得生成的 $b$ 是一个排列，输出答案的第 $i$ 位为 $1$ 表示 $k=i$ 时满足条件。

- 分析

先讨论好搞的，$k=1$ 时显然时判定序列是否为排列，$k=n$ 时显然是判定最小值是否为 $1$。

对于 $1 < k < n$，显然 $1$ 只能出现 $1$ 此，那么它就只能选择最极端的位置，即 $1$ 或 $n$。然后考虑去掉 $1$ 之后，显然 $2$ 是最小的，所以它也只能出现在两极。

于是这启发我们做这样一件事，对于区间 $[l,r]$ 如果当前判定到 $k$ 的位置，若 $a_l=n-k+1$ 或 $a_r=n-k+1$ 且 $\min\limits_{i=l}^{r}a_i=n-k+1$ 则 $k$ 可行，否则从此之后的 $k$ 都不行。

注意到这个时候有个特殊情况，即 $r-l+1=k$ 这个时候只用要求 $\min\limits_{i=l}^{r}a_i=n-k+1$ 即可。

- code

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
 	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9')   t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn = 3e5 + 500;
int T, n, a[maxn], ans[maxn], vis[maxn];

int main () {
	T = read();
	while (T--) {
		n = read();
		priority_queue <int, vector<int>, greater<int> > q;
		for (int i = 1; i <= n; i++) a[i] = read(), ans[i] = 0, vis[i] = 0;
		for (int i = 1; i <= n; i++) vis[a[i]]++;
		int res = 0;
		for (int i = 1; i <= n; i++) res += (vis[i] == 1);
		ans[1] = (res == n); 
		for (int i = 1; i <= n; i++) q.push(a[i]);
		if (q.top() == 1) ans[n] = 1;
		int l = 1, r = n, i = 1;
		while (i <= n) {
//			printf("%d %d %d %d\n", i, a[l], a[r], q.top());
			if (q.top() != i) break;
			if (a[l] == i) l++, ans[n - i + 1] = 1;
			else if (a[r] == i) r--, ans[n - i + 1] = 1;
			else break;
			i++, q.pop();
		}
		if (q.top() == i && r - l + 1 == n - i + 1) ans[n - i + 1] = 1;
		for (int i = 1; i <= n; i++) write(ans[i]);
		puts("");
	}
}
```

---

## 作者：LYY_yyyy (赞：0)

先特判 $k=1$ 和 $k=n$ 的情况。（注意特判 $n=1$）

之后我们考虑其他情况。我们发现，区间内最小值如果有至少 $2$ 个，或者最小值不在头尾，那么一定会有至少 $2$ 个区间的值为该最小值。我们从 $n-1$ 考虑到 $2$。$n-1$ 的时候只有两个区间，我们只需要判断 $1$ 是否只出现一次，且是否在头尾，以及是否存在 $2$ 即可。我们发现该判断方法可以推广到 $n-2$，只需要把 $1$ 扬了，然后就只剩两个区间了。此时再判断 $2$ 是否只出现一次，是否在头尾，以及是否存在 $3$ 即可。同时，我们可以观察到，可行的 $k$ 肯定是一段后缀，因为若上一个 $k$ 不行，可以根据判断条件推得这个 $k$ 肯定也不行。于是像这样从后往前扫一遍判断即可。

代码：
```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define pb emplace_back
using namespace std;
int T,n;
int a[300010],cnt[300010];
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n;for(int i=1;i<=n;i++) cnt[i]=0;
		bool f=1;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(cnt[a[i]]) f=0;
			cnt[a[i]]++;
		}int d=1,l=1,r=n;
		cout<<f;
		for(int i=n-1;i>=2;i--)
		{
			if(cnt[n-i]!=1||(a[l]!=n-i&&a[r]!=n-i)||!cnt[n-i+1])
			{
				d=i;break;
			}
			if(a[l]==n-i) l++;
			else r--;
		}
		for(int i=2;i<=n-1;i++) if(i>d) cout<<1;else cout<<0;
		if(n==1)
		{
			cout<<"\n";continue;
		}
		if(cnt[1]) cout<<1;else cout<<0;cout<<"\n";
	}
	return 0;
}
```

---

## 作者：AsunderSquall (赞：0)

前言：这是个很烦很垃圾还需要 $3$ 个特判的做法，不想看的可以跳了  
# 题意  
给一个长度为 $n$ 的序列，求任意长度为 $k$ 的滑动窗口最小值序列是否是一个排列。  

# 题解

我这个垃圾做法需要特判 $k=1,k=n$ 的情况。  
对于其他情况：  
首先考虑如果这样的一个序列是一个排列，那么 $1$ 只能在原序列中出现一次，并且在开头或结尾。  
因为如果不在开头，那么肯定不止一个滑动窗口覆盖到了这个 $1$。  
除去 $1$ 的位置后， $2$ 也只能出现 $1$ 次，并且在除了 $1$ 的情况的开头或者结尾。  
一直到 $n-k$ 为止都必须满足这个条件。  
除此之外，$n-k+1$，必须在剩下的区间里面存在。  
显然，如果 $k$ 满足这个条件，那么 $k+1$ 也满足这个条件，因为更大的限制越宽。  
哦，实现细节上还有第 $3$ 个特判，就是如果循环到底了，那么说明都可以。


代码    
```cpp
#include<bits/stdc++.h>
#define int long long
#define rd(x) x=read()
using namespace std;
const int N=3e5+5;
const int M=5005;
const int mod=998244353;
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int ksm(int x,int y){int ret=1;while (y){if (y&1) ret=(ret*x)%mod;x=(x*x)%mod;y>>=1;}return ret;}
 
int n,id,l,r;
int a[N];
int ans[N];
vector<int> vec[N];
signed main()
{
	int T;
	cin>>T;
	while (T--)
	{
		rd(n);
		for (int i=1;i<=n;i++) vec[i].clear();
		for (int i=1;i<=n;i++) ans[i]=0;
		for (int i=1;i<=n;i++) rd(a[i]);
		for (int i=1;i<=n;i++) vec[a[i]].push_back(i);
		l=1,r=n,id=0;
        int k;
		for (k=1;k<=n;k++)
		{
			if (vec[k].size()==0){id=k-1;break;}
			if (vec[k].size()>1){id=k;break;}
			if (vec[k][0]==l){l++;continue;}
			if (vec[k][0]==r){r--;continue;}
			id=k;break;
		} 
        if (k==n+1) id=n;
		for (int i=n-id+1;i<=n-1;i++) ans[i]=1;
		if (vec[1].size()>0) ans[n]=1;
		ans[1]=1;
		for (int i=1;i<=n;i++) if (vec[i].size()!=1) ans[1]=0;
		for (int i=1;i<=n;i++) cout<<ans[i];cout<<endl;
	}
}
```

---

