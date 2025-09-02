# Wonderful Permutation

## 题目描述

## 题意描述

给你一个 $n$ 的排列 $p_i$ 以及 $k (k \le n)$。

在一次操作中，你可以选择两个编号 $i,j$ 并且交换 $p_i,p_j$。

求最少需要几次操作才能使 $\sum\limits_{i=1}\limits^{k} p_i$ 的值最小。

排列是指由 $n$ 个 $1$ 到 $n$ 的不同整数按任意顺序组成的序列，序列中不能有重复的数字，也不能有大于 $n$ 的数。

## 样例 #1

### 输入

```
4
3 1
2 3 1
3 3
1 2 3
4 2
3 4 1 2
1 1
1```

### 输出

```
1
0
2
0```

# 题解

## 作者：heptari (赞：9)

~~虽然我那天CF没打 但是这题确实挺水的~~

看题可以很容易得出，要 $\sum_{i=1}^{k}p_i$ 最小，那么就要求从 $1$ 到 $k$ 的元素要尽可能的小。又因为 $p_i$ 是个排列，所以一定有元素在 $[1,k]$ 中并且该元素 $>k$，所以我们可以将这部分元素与 $[k,n]$ 间的进行调换，并记录调换次数。

$AC\ code:$
```cpp
#include <bits/stdc++.h>
using namespace std;
void solve(){
    long long N,K;
    long long ans=0;
    cin>>N>>K;
    vector <long long> arr(N);
    for (long long i = 0; i < N; i++){
        cin>>arr[i];
    }
    for (long long i = 0; i < K; i++){
        if(arr[i]>K){
            ans++;
        }
    }
    cout<<ans<<"\n";
}
int main(){
    long long T;
    cin>>T;
    while (T--){
        solve();
    }
}
```


---

## 作者：FQR_ (赞：8)

### 题目大意

给定一个长度为 $n$ 的排列。进行若干次操作，每次操作需要交换任意两个数。

求至少交换多少次，才使

$$\sum_{i=1}^k a_i$$

最小。


___

### 分析

考虑到，长度为 $n$ 的排列由 $1 - n$ 组成。

若使前 $k$ 个数字之和最小，前 $k$ 个数字一定由 $1 - k$ 组成。

暴力枚举前 $k$ 个数字。

如果当前数字在 $1 - k$ 之间，表示这个数字应当出现在前 $k$ 个数字中，故不需要交换。

如果当前数字不在 $1 - k$ 之间，表示这个数字一定要被换走，答案加一。

___

### AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while(T--)
	{
		int n,k,a[105];
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i];
		int ans=0;
		for(int i=1;i<=k;i++)
			if(a[i]>k) ans++;//如果这个数字需要被换走，答案就加一
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：wzmzmhk (赞：2)

### 题目简述

给定一个长度为 $n$ 的排列，你可以交换任意两个数，使得前 $k$ 个数尽可能小，输出最少操作数量。

--------------------

首先注意到这是个排列（即这个数列中的数都是 $1\sim n$ 中的数，且没有重复），那么也就是说前 $k$ 个数尽可能小的话，前 $k$ 个数一定是 $1\sim k$，那么，前 $k$ 个数中不是 $1 \sim k$ 的数字的个数就是答案数量。

AC 代码：
```cpp
#include <iostream>

using namespace std;

const int N = 1010;

int T;

int main() {
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            int x; cin >> x;
            if (i > k && x <= k)  cnt++;
        }
        cout << cnt << endl;
    }
    return 0;
}
```

---

## 作者：wnsyou (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1712A)

题目大意:

有 $t$ 组询问,每组询问给出 $n$ 和 $k$ 以及 $n$ 个数,每次可以选择两个数 $a_i$ 和 $a_j$,交换这两个数,请求出让前 $k$ 个数全是 $1 \sim k$ 中的数最少需要多少次。

思路:

要让前 $k$ 个数是 $1 \sim k$ 中的数,只需知道前 $k$ 个数中有几个不在范围内,在读入中判断再输出结果即可

代码:
```cpp
#include <iostream>

using namespace std;

int t, n, k, ans, x;

int main() {
 for (cin >> t; t; t--) {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
   cin >> x;
   if (i <= k) { // 如果在前 k 个数中
     ans += (x > k); // 当这个数大于 k 时,它不在范围内,需要 1 次交换
   }
  }
  cout << ans << '\n';// 输出!
  ans = 0;// 归零
 }
 return 0;// 完美结束
}
```

---

## 作者：Dregen_Yor (赞：2)

# 题目大意

- 给定一个长度为 $n$ 的正整数序列 $ p_1,p_2,\ldots,p_n $ 和一个正整数 $k$。

- 可以进行若干次操作，每次操作选定两个正整数 $i$ 和 $j$，交换 $p_i$ 和 $p_j$。

- 求进行若干次操作后，求使 $\sum\limits_{i=1}^kp_i$ 的值最小需要进行的操作次数。

# 思路

要使使 $\sum\limits_{i=1}^kp_i$ 的值最小，只需把相对较小的值排在前 $k$ 个即可，直接用 sort 函数进行排序，排序的同时还要记录一下每个数排序前的位置，遍历排序后前 $k$ 个位置的数，比较他原先的位置是否在前 $k$ 位，若不在，则说明这个数需要进行一次操作交换到前 $k$ 位，若该数原先就在前 $k$ 位，则不需要进行操作。

最终统计排序后的前 $k$ 个数中原先不在前 $k$ 位的数的个数即可。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,k;
struct node{
	int w,s;
}a[110];
bool cmp(node x,node y){
	return x.w<y.w;
}
int main() {
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i].w);
			a[i].s=i;
		}
		sort(a+1,a+1+n,cmp);
		int ans=0;
		for(int i=1;i<=k;i++){
			if(a[i].s>k){
				ans++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
} 
```


---

## 作者：Chronomaly_Atlandis (赞：2)

**题目思路**

要 $\sum\limits_{i=1}^kp_i$ 最小，那前 $k$ 位的数也要尽可能小。

只要用 $sort$ 函数先进行排序，再暴力枚举一遍，如果位置不一样了就把答案 $+1$。

**Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	int w,id;
	bool operator <(const node &rhs) const{
	return w<rhs.w;
}
};
node no[110];
int main(){
	cin.tie(NULL);cout.tie(NULL);
	int T;
	cin >> T;
	while(T--){
		int n,k,ans=0;
		cin >> n >> k;
		for(int i=1;i<=n;i++){
			cin >> no[i].w;
			no[i].id=i;
		}
		sort(no+1,no+1+n);
		for(int i=1;i<=k;i++)if(no[i].id>k)ans++;
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：sgl654321 (赞：1)

### 题目大意
- 给定一个长度为 $n$ 的**排列** $a$ 和一个常数 $k$，每次可以交换其中任意两个元素 $a_i$ 与 $a_j$。
- 要使 $a_1+a_2+a_3+\cdots+a_{k-1}+a_k$ 最小，请问至少要交换几次？

### 解题思路
首先明确排列的概念：对于一个长度为 $n$ 的排列，必须出现 $[1,n]$ 中的所有自然数各一次。因此， $a_1+a_2+a_3+\cdots+a_{k-1}+a_k$ 的最小值就是 $1+2+3+\cdots+(k-1)+k$。

又因为所有的元素只出现一次，所以我们只需要扫描一遍 $a_1\sim a_k$，如果其中有一个数大于 $k$，那么就要交换一次。问题就转化为求 $a_1\sim a_k$ 中大于 $k$ 的元素个数了。

例如一个长度为 $5$ 的排列 $[1,5,3,2,4]$，要求 $k=3$，只需要交换 $5$ 和 $2$。
### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,k,a[10000],ans;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		ans=0;
		for(int i=1;i<=k;i++)
			if(a[i]>k)ans++;	
		cout<<ans<<endl;
	} 
	return 0;
} //aa
```

---

## 作者：Epi4any (赞：1)

很明显，要让 $p_{1}+p_{2}+\ldots +p_{n}$ 最小，就要使 $p_{1},p_{2},\ldots ,p_{n}$ 是 $1-n$ 中最小的 $k$ 个数。

所以，需要的交换次数就是给出的排列中前 $k$ 个数有多少个数不属于 $1-n$ 。

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

int t, n, k, ans;
int cnt[105], p[105];

void solve() {
	n = read(), k = read();
	for (int i = 1; i <= n; i++) p[i] = read();

	for (int i = 1; i <= k; i++) cnt[p[i]] = true;
	for (int i = 1; i <= k; i++) if (!cnt[i]) ans++;
	cout << ans << endl;
}

int main() {
	t = read();
	while (t--) {
		ans = 0;
		memset(cnt, 0, sizeof(cnt));
		solve();
	}
	return 0;
}
//结尾警告：理解思路，杜绝抄袭
```

---

## 作者：_saltFish_ (赞：1)

[博客食用效果更佳](https://www.cnblogs.com/ytxy-bolg/articles/16585103.html)。

题意简述：给出一个 $n$ 的排列，求最少要交换几次如 $p_i,p_j$ 这样的数对，才能使得 $\sum\limits_{i=1}\limits^{k}p_i$ 最小。

首先，我们思考一个事情：使得 $\sum\limits_{i=1}\limits^{k}p_i$ 最小的方法是什么？

很简单就能想到，当然是将 $p_i$ 中前 $k$ 小的数全都放在前面，这样一来 $\sum\limits_{i=1}\limits^{k}p_i$ 就是最小的了。

考虑到这是一个 $n$ 的排列，所以前 $k$ 小的数就是 $1 , 2 , 3 \dots k$。

好好想想不难得出一个结论，在交换 $p_i,p_j$ 时，除了 $p_i,p_j$ 以外的数都不会受到影响。

而 $\forall p_i|p_i \le k,i \le k$ 是不需要进行交换的，$\forall p_i|p_i > k,i \le k$ 都需要进行交换，由于交换并不会影响到除了交换双方以外的数，所以 $\forall p_i|p_i > k,i \le k$ 都只要与 $p_i|p_i \le k,i > k$ 的数进行一次交换，之后就不用管它了。

所以，$\forall p_i|p_i > k,i \le k$ 都会且仅会有一次关于它的交换，所以他们对答案的贡献为 $1$。

而前 $k$ 个数中小于 $k$ 的数是不会被交换的，所以它们对答案没有贡献。

综上所述，答案就是前 $k$ 个数中大于 $k$ 的数的个数。

由此我们便得到了一个 $\mathcal{O}(t n)$ 的算法。

但为什么有些 $\mathcal{O}(t n \log{n})$ 只要 $0$ 毫秒，我 $\mathcal{O}(t n)$ 却要 $15$ 毫秒。

```cpp
#include<iostream>
using namespace std;
const int N(105);
int t,n,k,p[N];
int main(){
	#ifdef ytxy
	freopen("in.txt","r",stdin);
	#endif
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		int sum=0;
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>p[i];
			if(i<=k&&p[i]>k) sum++;
		}
		cout<<sum<<'\n';
	}
}
```

---

## 作者：xiaomuyun (赞：1)

- [洛谷传送门](https://www.luogu.com.cn/problem/CF1712A)
- [CF 传送门](https://codeforces.com/problemset/problem/1712/A)

## 题目大意

给定一个 $1$ 到 $n$ 的排列 $p$，以及一个整数 $k$，定义一个操作为选定 $i$ 和 $j$（$1 \le i < j \le n$）并交换 $p_i$ 和 $p_j$。求至少需要多少操作才能使 $p_1+p_2+\dots+p_k$ 最小。

## 算法分析

为了让 $p_1+p_2+\dots+p_k$ 最小，我们可以发现，让这段排列变成 $1$ 到 $k$ 的排列时，和最小。

所以我们只需要从 $1$ 到 $k$ 都看一下，如果当前这个数已经在 $1$ 到 $k$ 里面了，就不用管；如果在 $k$ 之后，就花费一次操作，选一个 $a_1$ 到 $a_k$ 之间大于 $k$ 的交换即可（不过实际上不用真的选，因为最后 $a_1$ 到 $a_k$ 之间就是 $1$ 到 $k$ 的排列，如果还有 $1$ 到 $k$ 之间的数没有在这里面，就说明这里面肯定会有一个数大于 $k$）。

## 代码实现

唯一需要维护的是 $a_i$ 的位置，可以维护一个 $pos_{a_i}$。

```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn=1e2+1;
int t,n,k,a[maxn],pos[maxn],cnt;
int main(){
	scanf("%d",&t);
	while(t--){
		cnt=0;
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;++i){
			scanf("%d",&a[i]);
			pos[a[i]]=i;
		}
		for(int i=1;i<=k;++i){
			if(pos[i]>k) ++cnt;//如果在k之后就直接统计答案
		}
		printf("%d\n",cnt);
	}
	return 0;
}
```

---

## 作者：ran_qwq (赞：1)

对于一个排列，前 $k$ 个数字的总和在什么情况下最小呢？显然，在 $1\sim k$ 这 $k$ 个数都在前 $k$ 个数里面最小。

如果一个小于等于 $k$ 的 $i$ 使得 $a_i>k$，则这个数需要与后面的数交换一次。所以答案为 $\sum_{i=1}^k[a_i>k]$。

```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<queue>
#include<string>
#include<vector>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=1e5+10;
const double eps=1e-5;
int read()
{
	char ch=getchar();
	int x=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48,ch=getchar();}
	return x*f;
}
int T,n,k,a[N];
signed main()
{
	T=read();
	while(T--)
	{
		n=read(),k=read();
		for(int i=1;i<=n;i++)
			a[i]=read();
		int ans=0;
		for(int i=1;i<=k;i++)
			if(a[i]>k)
				ans++;
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：lrqlrq250 (赞：0)

## 解题思路
因为给出的序列一定是一个排列，因此前 $k$ 个的最小值一定在前 $k$ 个分别是 $1, 2, 3,···, k$ 的时候取到，而且与先后顺序无关。因此只需要统计数列中前 $k$ 个数中有多少个数大于 $k$，这些数都需要被交换成后面的小于等于 $k$ 的数，可以证明不存在步数更少的解决方案。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, a[101];


int main(){
	int t, ans;
	scanf("%d", &t);
	while (t--){
		scanf("%d%d", &n, &k);
		for (int i=1; i<=n; i++) scanf("%d", &a[i]);
		ans = 0;
		for (int i=1; i<=k; i++) if (a[i] > k) ans++;
		printf("%d\n", ans);
	}
	return 0;
}

```


---

## 作者：DANIEL_x_ (赞：0)

结论题
## 思路
显然，如果存在 $i \in [1,k]$ , $a[i]>k$ ，则这个 $a[i]$ 就应该被替换到后面。所以，我们只需要一个计数器，如果有 $a[i]>k$ ，那么计数器加一。最后输出计数器。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e2+5;
int main()
{
    int T,a[maxn],t;
    cin>>T;
    while(T--)
    {
        int n,k,a[maxn],b[maxn],ans=0,sum=0,cnt=0;
        cin>>n>>k;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=k;i++)
        {
            if(a[i]>k) ans++;
        }
        cout<<ans<<endl;
    }

    return 0;
}
```


---

## 作者：Nygglatho (赞：0)

要想 $\sum\limits_{i=1}^k a_i$ 最小，显然需要前 $k$ 个数是 $1 \sim k$ 的一个排列。

那么判断一下，如果 $a_i \le k(k < i \le n)$，我们就把它和前面任意一个大于 $k$ 的数交换一下，一轮以后，大于 $k$ 的数都到后面的位置上了，而小于等于 $k$ 的数还是在 $1 \sim k$ 的位置。而这种方法 **刚刚好** 可以把小于等于 $k$ 的数放在 $1 \sim k$ 的位置，不需要多余的交换，所以是最优的。

```cpp
#include <bits/stdc++.h>

#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define ll long long
#define ul unsigned long long

using namespace std;
int T, n, k, x, ans;
int main() {
	IOS
	cin >> T;
	while (T--) {
		cin >> n >> k;
		ans = 0;
		for (int i = 1; i <= n; ++i) {
			cin >> x;
			if (x <= k && i > k) ++ans;//如果发现 a[i] <= k 的数在后面就交换
		}
		cout << ans << endl;
	}
} 
```

---

## 作者：xiezihanAKIOI (赞：0)

题外话：这道题有点水啊，最多评个橙。

思路
=

这道题数据量很小，模拟即可。我们要使 $a_1+a_2+...+a_k$ 尽量小，那么我们就先输入数组 $a$，然后再定义个数组 $b$，将数组 $a$ 的值赋予他。为后面做准备。

接着 sort 排序，找出 $a$ 数组中前 $k$ 小的数。用桶排把他们都标记出来，然后对 $b$ 数组的前 $k$ 个数进行遍历。如果桶中没有 $b_i$，那么就表明现 $b$ 数组的值不是最优的。那么就需要将数组 $b$ 的值进行转变。操作数加一。

代码实现
=

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int t, n, k, cnt;
int a[105], b[105], vis[105];

signed main () {
	cin >> t;
	while (t--) {
		memset (vis, 0, sizeof (vis));
		memset (a, 0, sizeof (a));
		memset (b, 0, sizeof (b));
		cnt = 0;
		cin >> n >> k;
		for (int i = 1 ; i <= n ; i++) {
			cin >> a[i];
		}
		memcpy (b, a, sizeof (b));
		sort (a + 1, a + 1 + n);
		for (int i = 1 ; i <= k ; i++) {
			vis[a[i]] = 1;
		}
		for (int i = 1 ; i <= k ; i++) {
			if (!vis[b[i]]) cnt++;
		}
		cout << cnt << endl;
	}
	return 0;
}
```


---

## 作者：lilong (赞：0)

看完题目，很容易得知要使 $ \sum\limits_{i=1}^k p_i$ 最小，且 $p_i$ 是 $n$ 的一个排列，可以知道最终的答案为 $\sum\limits_{i=1}^k i$。现在我们考虑如何将原序列转化成答案序列。

得知答案后，我们要做的就是将所有的 $p_i \le k$ 移到序列的前 $k$ 位中。暴力枚举序列的前 $k$ 位，判断该位置上是否满足 $p_i \le k$，是则说明满足了条件，否则需要进行一次交换（说明后面有 $p_j \le k$）。

代码实现十分简单：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n,a,k,ans=0;
		cin>>n>>k;
		for(int i=1;i<=n;i++)
		{
			cin>>a;
			if(i<=k&&a>k)
				ans++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：GI录像机 (赞：0)

## 思路：

题目要求 $\sum\limits_{i=1}\limits^{k}p_i$ 最小，很容易想到要把排列中小于等于 $k$ 的数都放到排列的前 $k$ 个。考虑最小操作次数，前 $k$ 个数中如果有任意一个数大于 $k$，那就一定有一个小于等于 $k$ 的数不在前 $k$ 个数中，我们就能交换这两个数。因此答案为前 $k$ 个数中大于 $k$ 的数的数量。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 114514, MOD = 1919810, INF = 0x3f3f3f3f;
int t = read(), n, k;
signed main() {
	while (t--) {
		n = read();
		k = read();
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			int tmp = read();
			if (i <= k && tmp > k)cnt++;
		}
		write(cnt);
		putchar('\n');
	}
	return 0;
}

```


---

## 作者：云裳 (赞：0)

**题意**

给出长度为 $n$ 的**排列** $a$，每次可以交换其中任意两个值 $a_i,a_j$  ( $ 1 \le i < j \le n $ )，求使 $\sum\limits_{i=1}^ka_i$ 最小至少需要多少次交换。


------------

**思路**

由于给出了一个排列，所以 $\sum\limits_{i=1}^ka_i$ 的值肯定是 $\sum\limits_{i=1}^ki$。也就是说，我们要让 $a$ 的前 $k$ 个数为长度为 $k$  的排列。那么，问题就变为了求 $a$ 中前 $k$ 个数有多少个数是大于 $k$ 的。


------------

**代码**
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
int a[200];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);//优化cin cout 速度
    int t;
    cin>>t;
    while(t--){
        int n,k,ans=0;
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        for(int i=1;i<=k;i++) if(a[i]>k) ans++;
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1712A)

## 题意简述
给你一个长度为 $n$ 的排列，求要使得前 $k$ 个数为一个排列最少需要多少次操作，其中一次操作为交换序列中的任意两个数。

## 思路
考虑贪心：我们计算出前 $k$ 个数中小于等于 $k$ 的数的数量，记为 $cnt$，所以其他数都要交换一次，总共需要交换 $k-cnt$ 次，显然这是最优解。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=110;
inline int read(){
	int x=0;
	short f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
int t,n,k;
int a[N];
signed main(){
	t=read();
	while(t--){
		n=read(),k=read();
		for(int i=1;i<=n;i++)a[i]=read();
		int cnt=0;
		for(int i=1;i<=k;i++){
			if(a[i]<=k)cnt++;
		}
		cout<<k-cnt<<endl;
	}
	return 0;
}
```


---

## 作者：ztytql (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1712A)

## Description
给定正整数 $n, k,$ 以及一个元素值为 $[1,n]$ 且互不相同的序列 $a,$ 使得用最小的次数交换其中任意两个数，使得交换后的数组前 $k$ 个数的和最小。
## Solution
我们可以发现，交换后前 $k$ 个数的和最小，那么前 $k$ 个数必然是 $[1,k]$ 区间内的。

于是我们可以先将数组排序（其实就是一个 $1$ 到 $n$ 的数组），然后对于排序后数组的前 $k$ 个数字，判断 $a$ 数组的对应数字下标是否在 $k$ 以内即可。

注意**多组测试数据**。
## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
 
int t, n, k;
int a[110], b[110];
 
signed main()
{
	cin >> t;
	
	while (t --)
	{
		cin >> n >> k;
		for (int i = 1 ; i <= n ; i ++)
			cin >> a[i], b[i] = a[i];
		int ans = 0;
		sort(b + 1, b + n + 1); // 将数组排序
		for (int i = 1 ; i <= k ; i ++)
			for (int j = 1 ; j <= n ; j ++)
				if (a[j] == b[i] && j > k) // 判断 a 数组的对应元素是否在 k 以内
					ans ++;
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：chengning0909 (赞：0)

# CF1712A 题解
题目传送门：[这里](https://www.luogu.com.cn/problem/CF1712A)

## 题意
一共 $t$ 组数据，每次给你 $n$ 个数，$a_i$ 各不相同，每次可以选择两个下标 $i, j$ 并且交换 $a_i, a_j$，求出要使从 $1 \sim k$ 的所有 $a_i$ 的和最小。

## 思路
因为要使 $1 \sim k$ 的所有 $a_i$ 的和最小，所以和最小应该为 $1 \sim k$ 的和。

所以只要判断 $1 \sim k$ 的所有 $a_i$ 是否小于 $k$ 就可以了。

## 上代码

```cpp
#include <iostream>

using namespace std;

int t, n, k, p;

int main(){
  cin >> t;
  while (t--) {
    cin >> n >> k;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
      cin >> p;
      if (i <= k && p > k) {   // 判断是否小于 k
        cnt++;       // 次数累加
      }
    }
    cout << cnt << endl;
  }
  return 0;
}
```

---

## 作者：LazYQwQ (赞：0)

## 题意简述
- 给出一个正整数 $t$ 代表数据组数。

- 对于每一组数据给定一个长度为 $n$ 的序列以及一个小于等于 $n$  的正整数 $k$。

- 保证每个小于等于 $n$ 的正整数都在长度为 $n$ 的序列中出现了一次。

- 在一次操作中可以挑选两个下标 $i$ 与 $j$ 并交换下标对应位置的数字 $p_i$ 与 $p_j$。

- 求出最少操作数使前 $k$ 个数之和尽可能小。

## 解题思路

1. 可以想到对于一个给定的序列，使它满足要求的操作后的序列的前 $k$ 项是固定的，即原序列中最小的 $k$ 个数，也就是小于等于 $k$ 的所有正整数。

2. 不难发现原序列前 $k$ 个数中若有 $x$ 个数不属于目标序列，则原序列中第 $k$ 项后面的数中一定有 $x$ 个数属于目标序列，因此需要 $x$ 次交换操作。

3. 因此我们可以想到对读入的数进行判断，若读入的数的下标小于等于 $k$ 且读入的数大于 $k$ 则让计数器变大，最后输出计数器的大小即可。


## 参考代码如下
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,k,num=0,op;
		cin>>n>>k;
		for(int i=1;i<=n;i++)
		{
			cin>>op;
			if(i<=k and op>k)num++;
		}
		cout<<num<<endl;
	}
} 
```


---

## 作者：Jeremiahy (赞：0)

### 题意

给一个排列 $p$，每次可交换任意两项，询问将 $p$ 的前 $k$ 个元素之和弄到最小的最少操作次数。

## 分析

显然，前 $k$ 个元素之和最小就是前 $k$ 小个元素都在前 $k$ 个位置上（可以乱序），而题目又保证是一个排列，所以前 $k$ 个位置必然是长度为 $k$ 的排列。

那么只需要统计原排列 $p$ 的前 $k$ 个元素，遇见一个小于等于 $k$ 的元素，计数器 $num$ 就加 $1$，最后 $k-num$ 就是需要调换的次数，即答案啦。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, a[103], b[103], k;
signed main () {
	cin >> t;
	while (t--) {
		int num = 0;
		cin >> n >> k;
		for (register int i = 1; i <= n; i++) {
			cin >> a[i];
			if (a[i] <= k && i <= k)//满足条件
				num++;
		}
		cout << k - num << '\n';
	}
	return 0;
}
```


---

## 作者：Deft_t (赞：0)

# 题意
给定一个长度为 $n$ 的且由 $1$ 到 $n$ 组成的排列 $p_1,p_2,...,p_n$ 和一个正整数 $k$ 。   
每次操作可以任选一对 $p_i,p_j(1 \leq i,j \leq n)$ 交换。  
问最少几次操作可以使得 $p_1+p_2+...+p_k$ 最小。
# 思路
要使得 $ p_1+p_2+...+p_k $ 最小，就是要让 $1,2...,k$ 这 $k$ 个数都在区间 $[1,k]$ 范围中。  
因为交换的两个数的下标可以任选，所以只需要把每个初始 $[1,k]$ 范围内大于 $k$ 的数换成 $[k+1,n]$ 内的任意一个 $\leq k$ 的数即可。  
每个数只需要一次交换，所以答案就等于初始 $[1,k]$ 范围内 $> k$ 的数的个数。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
int a[105];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i = 1;i <= n;i++) cin>>a[i];
		int ans = 0;
		for(int i = 1;i <= k;i++){
			if(a[i]>k) ans++;
		}
		cout<<ans<<endl;
	}
	return 0;
}



```


---

## 作者：Scorilon (赞：0)

给定 $k$ 以及长度为 $n$ 的一个排列，定义一种操作为：选择两个位置 $i$ 与 $j$，交换 $a_i$ 与 $a_j$ 的值。

问最少经过多少次操作可以使得 $\sum^k_{i=1}a_i$ 的值最小。

这道题很简单，要使前 $k$ 项最小，只要使得数 $1 \sim k$ 都在这 $k$ 个位置里出现就好。

也就是统计前 $k$ 个位置，不是 $1 \sim k$ 的值有多少。

```cpp
#include <cstdio>
#include <iostream>

using namespace std;

int t,n,k;
bool a[105];//记录前k个位置出现的数

int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++) a[i]=false;
		for(int i=1;i<=n;i++) {
			int x;
			scanf("%d",&x);
			if(i<=k) a[x]=true;
		}
		int ans=0;
		for(int i=1;i<=k;i++) {
			if(!a[i]) ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
} 
```


---

## 作者：sw2022 (赞：0)

## 题意简析

给定一个排列 $p\ (|p|=n,n>0)$ 和一个数 $k$，定义交换排列 $p$ 中的两个数为一次操作，问最少需要多少次操作使得排列的前 $k$ 个数的和最小。

因为这是一个排列，即 $1\sim n$ 在排列中只出现一次，所以如果要选其中 $k$ 个数使它们的和最小，那就选择 $1\sim k$ 即可。所以我们只需要找出前 $k$ 个数中大于 $k$ 的数，用后 $n-k$ 个数中小于等于 $k$ 的数替换即可。

## 代码/解释
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t,n,k,p,s,i;
    cin>>t;
    while(t--)
    {
        cin>>n>>k;s=0;
        for(i=1;i<=n;i++)
        {
            cin>>p;
            if(i<=k&&p>k) s++;
        }
        printf("%d\n",s);
    }
    return 0;
}

---

## 作者：cachejtt (赞：0)

## 题意
给你一个 $n$ 的排列和一个正整数 $k$（$k\le n$），每次交换，你可以交换序列中任意两个数。最终目标是使得序列的 $a_1+a_2+\dots +a_k$ 最小，问你最少需要交换几次。

## 思路
要使得序列前 $k$ 个数之和最小，则必须前 $k$ 小的数都在前 $k$ 个。否则经过一次交换，就可以到前 $k$ 个中。

因此，交换次数即为前 $k$ 个数中不是前 $k$ 小的数的个数。由于序列是以排列形式给出的，所以前 $k$ 小的数就是小于等于 $k$ 的数。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define endl "\n"
using namespace std;
int t=1,n,k,a[105],sum;
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n>>k;
    sum=0;
    rep(i,1,n){
      cin>>a[i];
      if(i<=k && a[i]>k)sum++;
    }
    cout<<sum<<endl;
  }
  return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

![](bilibili:BV1DS4y1s7yL)

### 2 思路

我们可以发现，$\sum_{i=1}^kp_i$ 最小时，$p_1,p_2,...,p_k$ 本身就是 $1$ 到 $k$ 的排列。

所以，我们看看前 $k$ 个数中，有多少个数是大于 $k$ 的。直接将这些数跟后 $n-k$ 个数中不超过 $k$ 的数交换即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 100
int t;
int n;
int k;
int a[max_n+2];
int p[max_n+2];
int pi;
int ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1712A_1.in","r",stdin);
	freopen("CF1712A_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		ans=0;
		for(int i=1;i<=k;++i)if(a[i]>k)++ans;
		printf("%d\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/83727084)

By **dengziyue**

---

## 作者：zhicheng (赞：0)

### 思路

很明显，大前提是前 $k$ 个数最小，那么因为是排列，最小的和一定是 $\sum\limits_{i=1}^{k}i$。所以我们要把所有小于等于 $k$ 但是不在 $[1,k]$ 区间里的所有的数都放在这个区间里，那么操作数就是这些数的个数。写的再标准一点就是：$\sum\limits_{i=k+1}^n[a_i \leq k]$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,a,k,p,sum=0;
	scanf("%d",&n);
	while(n--){
		sum=0;
		scanf("%d%d",&a,&k);
		for(int i=1;i<=a;i++){
			scanf("%d",&p);  //边读边做
			if(i>k&&p<=k){
				sum++;  //直接上公式，求个数。
			}
		}
		printf("%d\n",sum);
	}
}
```

---

## 作者：Foofish (赞：0)

## 题意

你现在要对于一个全排列做若干次任意的交换操作让前 $k$ 项最小。求出最小交换次数。

## 思路

让前 $k$ 项最小，那么前 $k$ 项肯定是包含了 $[1,k]$ 里的所有数的。那么如果前 $k$ 项有一个 $>k$ 的数，那么肯定**最少也必须要**一次把它与  $a_i\leq k,i\in[k+1,n]$ 的这一项交换，就可以实现让他 $\leq k$。

那么最小性和必要性都证明了，答案肯定就是对于上述过程模拟一下就行了。

```cpp
#include <bits/stdc++.h>;
template <typename T>inline void read(T& t){t=0; register char ch=getchar(); register int fflag=1;while(!('0'<=ch&&ch<='9')) {if(ch=='-') fflag=-1;ch=getchar();}while(('0'<=ch&&ch<='9')){t=t*10+ch-'0'; ch=getchar();} t*=fflag;}
template <typename T,typename... Args> inline void read(T& t, Args&... args) {read(t);read(args...);}
using namespace std;
const int N=100000, inf=0x3f3f3f3f;

int T=1,n,a[N];

int main(){
    read(T);
    while(T--){
        int k,ans=0;
        read(n,k);
        for(int i=1;i<=n;++i) read(a[i]),ans+=(i<=k)*(a[i]>k);
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：arkerny (赞：0)

## 题意概要

使排列 $p$ 的前 $k$ 个数字的和最小，需要交换几次 $p$ 中的元素。

## 解题思路

加法满足交换律，使排列 $p$ 的前 $k$ 个数字的和最小，即使排列 $p$ 的前 $k$ 小的元素位于前 $k$ 个位置，如不在前 $k$ 个位置，则某一个的前 $k$ 小的元素前 $k$ 个位置故需与后面的元素交换，记一次交换次数。

代码如下：

``` cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define il inline

int T;
int n,k,a[110];
int ans;

void slove()
{
    ans=0;
    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=k;i++)
    {
        if(a[i]>k)
        {
            ans++;
        }
    }
    printf("%d\n",ans);
    return ;
}

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        slove();
    }
    return 0;
}
```

---

## 作者：osfly (赞：0)

挺简单的一道题。

要想使 $\sum\limits^k_{i=1}p_i$ 最小，很明显的，前 $k$ 个数必须为 $1\sim k$。设 $c_i$ 为 $i$ 在 $p$ 里出现的位置，则答案为 $\sum\limits^{k}_{i=1}[c_i>k]$。

```cpp
#include<cstdio>
int t;
int n,k;
int a[110],c[110];
int ans;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		ans=0;
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			c[a[i]]=i; 
		}
		for(int i=1;i<=k;i++)
			if(c[i]>k) ans++;
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：BorisDimitri (赞：0)

update 2022.8.14: 更正错误

## 题意
给出一个长为 $n$ 的排列 $p$，每一次操作可以交换任意两个位置的数，求使得 $p_1 + p_2 \cdots p_k$ 最小所需的最小操作次数。

## 思路
由于 $p$ 是一个排列，所以使得只要使得 $$\max_{i=1}^{k} a_i \le k$$ 即可。

所以我们统计一下从 $a_1$ 到 $a_k$ 中大于 $k$ 的数的个数即可。

注意多组数据。

```cpp
const int N = 105;
int a[N];
int n, k;
void solve()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	
	int ans = 0; 
	for(int i=1;i<=k;i++) 
	{
		if(a[i] > k) ans ++;
	}
	
	cout<<ans<<endl;
}
```

---

## 作者：zfx_VeXl6 (赞：0)

### 题目大意

多组数据。

每组数据给定 $k$，$n$ 和一个 $1$ 到 $n$ 的排列 $p$，每次操作可以交换 $p_i$ 和 $p_j$ $(i\ne j)$，求最少的操作数，使 $\sum\limits_{i=1}^kp_i$ 最小。

$1\le k\le n\le100$，$1\le p_i\le n$。

### 题解

这道题实际上就是求通过交换任意两个元素，把 $[p_1\cdots p_k]$ 转换为 $1$ 到 $k$ 的排列的最小交换数。

答案便是 $[p_1\cdots p_k]$ 中满足 $p_i>k$ 的 $p_i$ 的数量。

### 代码
```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int t,n,k,a[10001],ans;
    int main()
    {
        scanf("%d",&t);
        while(t--)
        {
            ans=0;
            scanf("%d%d",&n,&k);
            for(int i=1;i<=n;i++)
            {
                scanf("%d",&a[i]);
                if(i<=k&&a[i]>k)
                    ans++;
            }
            cout<<ans<<'\n';
        }
        return 0;
    }
```

---

## 作者：RAVE_LOVEo_O (赞：0)

这题感觉还是比较简单的，就是一道模拟

因为要到 $k$ 的和最小，就是要把小的调到前面，也就是每次累加就行了

题目说了输入的数组是 $n$ 的一个排列，所以实现也不是很难

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[105],s,n,i,k;//变量定义
int read()//快读
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+(ch-'0');
		ch=getchar();
	}
	return x*f;
}
void write(int x) {//快输
	if(x<0){
		putchar('-');
		write(-x);
		return;
	}
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
int main()
{
   t=read();
   while(t--)
   {
      s=0;
      n=read();k=read();
      for(i=1;i<=n;i++)//输入
         cin>>a[i];
      for(i=1;i<=k;i++)//这里可以和上面合并
         if(a[i]>k)s++;//如果超过了就累加
      write(s);//输出
      puts("");//快速换行
   }
   return 0;
}
```



---

