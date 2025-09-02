# Quick Sort

## 题目描述

You are given a permutation $ ^\dagger $ $ p $ of length $ n $ and a positive integer $ k \le n $ .

In one operation, you:

- Choose $ k $ distinct elements $ p_{i_1}, p_{i_2}, \ldots, p_{i_k} $ .
- Remove them and then add them sorted in increasing order to the end of the permutation.

For example, if $ p = [2,5,1,3,4] $ and $ k = 2 $ and you choose $ 5 $ and $ 3 $ as the elements for the operation, then $ [2, \color{red}{5}, 1, \color{red}{3}, 4] \rightarrow [2, 1, 4, \color{red}{3},\color{red}{5}] $ .

Find the minimum number of operations needed to sort the permutation in increasing order. It can be proven that it is always possible to do so.

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, the permutation is already sorted.

In the second test case, you can choose element $ 3 $ , and the permutation will become sorted as follows: $ [\color{red}{3}, 1, 2] \rightarrow [1, 2, \color{red}{3}] $ .

In the third test case, you can choose elements $ 3 $ and $ 4 $ , and the permutation will become sorted as follows: $ [1, \color{red}{3}, 2, \color{red}{4}] \rightarrow [1, 2, \color{red}{3},\color{red}{4}] $ .

In the fourth test case, it can be shown that it is impossible to sort the permutation in $ 1 $ operation. However, if you choose elements $ 2 $ and $ 1 $ in the first operation, and choose elements $ 3 $ and $ 4 $ in the second operation, the permutation will become sorted as follows: $ [\color{red}{2}, 3, \color{red}{1}, 4] \rightarrow [\color{blue}{3}, \color{blue}{4}, \color{red}{1}, \color{red}{2}] \rightarrow [1,2, \color{blue}{3}, \color{blue}{4}] $ .

## 样例 #1

### 输入

```
4
3 2
1 2 3
3 1
3 1 2
4 2
1 3 2 4
4 2
2 3 1 4```

### 输出

```
0
1
1
2```

# 题解

## 作者：0zhouyq (赞：6)

### CF1768B 题解

[传送门](https://www.luogu.com.cn/problem/CF1768B)

### 思路

我们发现，一开始 $1$ 前面的数字一定是要被选到后面排序的，否则 $1$ 就不会被排到最前面。同样的，$1$ 到 $2$ 之间的数字也要被选到后面排序。这样，只有原序列中的从 $1$ 开始的连续递增的子序列不用被选上，所以输入的时候统计一下这个子序列的长度就行了。

最后剩下的那些数字就是要被选取排序的。选的时候从这些数字中从小到大选，每个数都被选一次就可以排好序了。假设一共有 $x$ 个数要被选去排序，那么答案就会是 $\lceil\dfrac{x}{k}\rceil$。

### AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	ll t;
	scanf("%lld",&t);
	while(t--){
		ll n,k,x;
		scanf("%lld %lld",&n,&k);
		ll now=0;
		for(ll i=1;i<=n;i++){
			scanf("%lld",&x);
			if(x==now+1) now++;
		}
		n-=now;//操作后n是需要被选择去排序的数的个数
		if(n%k==0) printf("%lld\n",n/k);
		else printf("%lld\n",n/k+1);//上取整输出
	}
	return 0;
}
```

---

## 作者：xiaruize (赞：1)

**思路**

按照 $1 \rightarrow n$ 的顺序遍历每个数

因为每次操作是将 $k$ 个数放在数组末尾， 所以在 $x$ 上一旦使用这个操作，那么 $x-n$ 中的所有数都需要经过一次操作

所以要最大化 $x$ ，即求形如 $1,2,3\cdots$ 的子序列的最大长度

**Code**

```cpp
/*
    Name:
    Author: xiaruize
    Date:
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define ALL(a) (a).begin(), (a).end()
#define pb push_back
#define mk make_pair
#define pii pair<int, int>
#define pis pair<int, string>
#define sec second
#define fir first
#define sz(a) int((a).size())
#define rep(i, x, y) for (int i = x; i <= y; i++)
#define repp(i, x, y) for (int i = x; i >= y; i--)
#define Yes cout << "Yes" << endl
#define YES cout << "YES" << endl
#define No cout << "No" << endl
#define NO cout << "NO" << endl
#define debug(x) cerr << #x << ": " << x << endl
#define double long double
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;
const int N = 1e5 + 10;

// bool st;
int t;
int n, k;
int a[N];
int pos[N];
// bool en;

void solve()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pos[a[i]] = i;
    }
    int x = 1;
    int res = 0;
    for (int i = 1; i < n; i++)
    {
        if (pos[i + 1] > pos[i])//不需要操作
            continue;
        //因为下一位在当前位前面，所以不得不进行操作
        cout << (n - i + k - 1) / k << endl;
        return;
    }
    //递增
    cout << "0" << endl;
}

signed main()
{
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // cerr<<(&en-&st)/1024.0/1024.0<<endl;
    // auto t_1=chrono::high_resolution_clock::now();
    cin >> t;
    while (t--)
        solve();
    // auto t_2=chrono::high_resolution_clock::now();
    // cout <<". Elapsed (ms): " << chrono::duration_cast<chrono::milliseconds>(t_2 - t_1).count() << endl;
    return 0;
}
```

---

## 作者：shinzanmono (赞：0)

# 题意：
给定一个长度为 $n$ 的排列，你可以每次选择任意 $k$ 个数，把他们从排列中删除，并按照升序放到排列的后面，求最少操作几次后，排列变为升序。

# Solution:
对于一个排列，升序肯定是 $\{1,2,3,4,\cdots,n\}$，我们考虑贪心算法，对于原排列来说，每次选出 $k$ 个数按升序放到末尾的最好方法就是删除最大的 $mk(m\in[1,\lfloor \frac nk\rfloor])$ 个数，只要剩余的数满足一个数列：$\{1,2,3,4,\cdots,n-\lfloor \frac nk\rfloor\}$，那么求出最小的 $m$ 即可。


我们选择一种 $\Theta(n)$ 的算法：求出以 $1$ 开头的最长的上升连续子序列的长度 $len$，剩下的数字即可被选出，所以答案就是 $\lceil\frac{n-len}k\rceil$。

# Code:
```cpp
#include<iostream>
#include<cmath>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n, k;
        std::cin >> n >> k;
        int arr[n + 1];
        for (int i = 1; i <= n; i++) std::cin >> arr[i];
        int cur = 0;
        for (int i = 1; i <= n; i++)
            if (arr[i] == cur + 1) cur++;
        std::cout << static_cast<int>(std::ceil(1. * (n - cur) / k)) << "\n";
    }
    return 0;
}
```

---

## 作者：zajasi (赞：0)

## 解题思路
我们只能做一个操作：选定最多 $k$ 个数，将它们扔到最后排个序。如果你扔了一个小的数到大的数后面，很明显是不行的，因为会多两次无关的操作。也就是说，我们只能把大的数扔到小的数后面去。先举个例子：
```
5 2
3 4 1 5 2
```
操作如下：
```
1.将 3 和 4 扔到后面，排序，原数组变为 1 5 2 3 4。
2.将 5 扔到后面，排序，原数组变为 1 2 3 4 5。
结束，共两次操作。
```
我们发现：按 **顺序** 排列的 $1\ 2\ 3 \cdots$ 且必须从 $1$ 开始的数组是不用改变位置的，其他的都要扔一遍。（如上面的例子按顺序排列的只有 $1\ 2$。）为什么呢？因为原数组 $p$ 是一个排列，除了这些数以外，其他的数后面肯定有比它小的，自然要扔一遍。

贪心发现：我们一次能扔 $k$ 个数就扔 $k$ 个数，若还需要扔的个数小于 $k$，没办法，只好单独扔一次。也就是说，我们只需要统计一下要扔的数字的个数，这道题就迎刃而解了。而我的代码中为了方便，记的是不要扔的个数，最后减一下也都一样。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int n,k;
int a[100010];
main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		int c=1,z=0;//z 记录不要扔的个数，c 记录现在这个排列应该到几了
		for(int i=1;i<=n;i++){
			if(a[i]==c){//属于这个顺序的排列就不要扔
				z++;
				c++;
			}
		}
		int x=n-z;
		cout<<x/k+(x%k!=0)<<"\n";//计算要扔的次数
	}
	return 0;
}
 
```

---

## 作者：KKKZOZ (赞：0)

## 题目分析

先看数据范围， $2 \le n \le 10^5$。

解法可选的几种时间复杂度：
+ $O(NlogN)$
+ $O(N)$

多在纸上模拟几次后，其实可以总结出**只需要对没有按照从小到大排好序（从1开始算）的元素进行操作即可**。

设需要操作的元素个数为 $m$，那么最后的操作数为 $\lceil\dfrac{m}{2}\rceil$。

具体是怎么操作的，请看下面这个例子（ $n=6,k=2$）：

$6\quad \color{Green}\text{1} \quad \color{Black}\text{4} \quad \color{Green}\text{2} \quad \color{Green}\text{3} \quad \color{Black}\text{5}$

操作一次后可以变为（移动 $4$ 和 $5$）：

$\color{Black}\text{6} \quad \color{Green}\text{1} \quad \color{Green}\text{2} \quad \color{Green}\text{3} \quad \color{Red}\text{4} \quad \color{Red}\text{5}$

再操作一次（移动 $5$ 和 $6$）：

$\color{Green}\text{1} \quad \color{Green}\text{2} \quad \color{Green}\text{3} \quad \color{Red}\text{4} \quad \color{Blue}\text{5} \quad \color{Blue}\text{6}$

## 代码
```java
import java.io.*;

public class Main {

    static BufferedReader buf = new BufferedReader(new InputStreamReader(System.in));
    static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    static PrintWriter cout = new PrintWriter(bw);
    static StreamTokenizer st = new StreamTokenizer(buf);

    public static int nextInt() throws IOException {
        st.nextToken();
        return (int) st.nval;
    }


    static int n,k,t;
    public static void main(String[] args) throws IOException {
        t = nextInt();
        for(int tt=1;tt<=t;tt++){
            n = nextInt();
            k = nextInt();
            int[] a = new int[n + 1];
            for(int i=1;i<=n;i++)
                a[i]=nextInt();
            int cur=1,m=0;
            for(int i=1;i<=n;i++){
                if(a[i]==cur)
                    cur++;
                else
                    m++;
            }
            int ans = (int)Math.ceil(m*1.0/k);
            cout.println(ans);
        }
        cout.flush();
    } // End of main
}
```

---

## 作者：abensyl (赞：0)

原题：[CF1769B Quick Sort](https://www.luogu.com.cn/problem/CF1768B)。

## 思路

显而易见，先统计计算出有多少数字已经在自己应该在的位置上了，此处可以不用用 set 或者 multiset，是因为 permutation 就保证了顺序为 $1\sim n$。

剩余的元素可以分为 $k$ 个一组，分组进行操作，也就是说每次操作处理 $k$ 个数字。

所以总的操作数为 $\lceil n/k\rceil$，为避免被卡精度，也可写作 $\lfloor n+k-1/k \rfloor$，但事实证明两种方法均可过。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[(int)1e6+3];
void myfunc() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> a[i];
    int ans = n, cur = 1;
    for (int i = 0; i < n; ++i)
        if (a[i] == cur) --ans, ++cur;
    ans = (ans + k - 1) / k;
    cout << ans << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) myfunc();
    return 0;
}
```
AC记录：[洛谷](https://www.luogu.com.cn/record/98989853) |  [CF](https://codeforces.com/contest/1768/submission/188373595)。

---

## 作者：ExplodingKonjac (赞：0)

**[【原题链接】](https://www.luogu.com.cn/problem/CF1768B)**

## 题目分析

因为拍好后元素放到了最后面，所以保持不变的元素必然是前面的若干个，也就是最长的 $1,2,\dots$ 子序列。不难发现剩下的元素必须全部用操作才能排好。假设最长的 $1,2,\dots$ 子序列长度为 $l$，答案就是 $\lceil(n-l)/k\rceil$。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

// 快读

using LL=long long;
using LD=long double;
using UI=unsigned int;
using ULL=unsigned long long;

int T,n,k,p[100005];
int main()
{
	qin>>T;
	while(T--)
	{
		qin>>n>>k;
		for(int i=1;i<=n;i++) qin>>p[i];
		int lst=0;
		for(int i=1;i<=n;i++) if(p[i]==lst+1) lst++;
		qout.writeln((n-lst+k-1)/k);
	}
	return 0;
}
```

---

## 作者：tZEROちゃん (赞：0)

注意到一个从 $1$ 开始的递增子序列（其中数字连续）是可以不用移动的，那么不在这个子序列里的数就是要移动的，我们设不在这个子序列的数的个数是 $s$，每次可以移动 $k$ 个，那么就要移动 $\lceil \dfrac{s}{k} \rceil$ 次。

举个例子，$n = 6, k = 2, p = [1, 3, 2, 4, 6, 5]$，我们发现 $1, 2$ 是一个从 $1$ 开始的数字连续的递增子序列，那么就选择 $3, 4$ 第一次移动，$6, 5$ 第二次移动，然后就完成了这个操作。

```cpp
#include<bits/stdc++.h>
using namespace std;
 
const int N = 1e6 + 10;
 
#define int long long
 
void solve() {
   int n, k; cin >> n >> k;
   vector<int> a(n);
   for (auto &i : a) cin >> i;
   int cnt = 0;
   for (auto &i : a) cnt += (i == cnt + 1);
   int tot = (n - cnt + k - 1);
   cout << tot / k << endl;
}

signed main() {
   int q; cin >> q;
   while (q--) solve();
}
```

---

## 作者：_Remake_ (赞：0)

首先可以发现我们一定不会对 `1` 进行操作，然后可以发现如果 `2` 的位置在 `1`之后，我们也不会对 `2` 进行操作，因为我们可以挑出所有在第一个位置到 `1` 的位置之前的数，以及在 `1` 和 `2` 之间的数，以及 `2` 之后的数，把它们全部放到末尾，正确性显然。

以此类推可得一个结论：找到从 `1` 开始最长的连续上升子序列，设序列长度为 $len$，总共需要移动的元素数量即为 $n-len$。

然后有一个问题：一次移动 $k$ 个元素可能会导致出现步数剩余，但可以发现的是：先执行 $\left \lceil \frac{(n-len)}{k} \right \rceil-1 $ 次操作，最后一次操作时除剩余需要排序的元素外再把剩余步数使用在当前序列末尾的几个数字上就可以解决这个问题。

所以我们使用 $\left \lceil \frac{(n-len)}{k} \right \rceil $ 次操作完成了题目的要求。

代码：

```cpp
#include<bits/stdc++.h>
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define debug puts("51522jqwlwdbb");
//#define int long long
int read()
{
    int n=0,k=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
        {
            k=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        n=n*10+ch-'0';
        ch=getchar();
    }
    return n*k;
}
int n,m;
int A[200001];
int B[200001];
char C[200001];
int t;
namespace qwq
{
    void main()
    {
    	t=read();
    	while(t--)
    	{
    		n=read();
    		m=read();
    		int X;
    		for(int r=1;r<=n;r++)
    		{
    			A[r]=read();
    			if(A[r]==1)
    			{
    				X=r;
    			}
    		}
    		int len=1;
    		for(int f=X+1;f<=n;f++)
    		{
    			if(A[f]==len+1)
    			{
    				len++;
    			}
    		}
    		printf("%d\n",(n-len+m-1)/m);
    	}
        return;
    }
}
signed main()
{
    //freopen("qwq.in","r",stdin);
    //freopen("qwq.out","w",stdout);
    qwq::main();
    return 0;
}
```


---

## 作者：_JF_ (赞：0)

## CF1768B Quick Sort 

[题目传送门](https://www.luogu.com.cn/problem/CF1768B)

一道思维题。

由于他要求的是使得操作次数最小，那么显然就是要使要被操作的数最少。

我们考虑绝对不用交换的数，那么就是如果是 $[1,n]$ 之间的递增且差值为 $1$ 的序列的话，就绝对不需要进行任何操作了，因为他是 $[1,n]$ 之间的一个排列，所以我们应该尽可能找到一个从 $1$ 开始的，差值为 $1$ 的递增的最大的一个序列。

一定要找差值为 $1$ 的原因是如果差值不是 $1$ 的话，假设 $[i,j]$ 差值不是 $1$，那么中间肯定还有一些数可以进行插入，所以就浪费一次操作了。 

然后对于剩下的数，我们把他加到末尾以后，我们就可以对他贪心的选择 $k$ 个数进行操作，也就是按照题意排序，这样就可以使整个序列有序了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
int a[N];
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int n,m,t;
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		int step=1;
		for(int i=1;i<=n;i++)
			if(a[i]==step)
				step++;
		step--;
		int last=n-step;
		if((last%m)==0)
			cout<<last/m<<endl;
		else
			cout<<last/m+1<<endl;
	}
	return 0;
}

```


---

## 作者：ztlh (赞：0)

~~赛时第一次提交因为没输入 $k$ 喜提 $\text{RE}$~~

# Solution

首先观察：

- **在 $1$ 前面**的数一定要被挪到最后。

- 如果 $2$ 在 $1$ 后面，那么**两者之间**的数都要被挪到最后。

- 如果 $3$ 在 $2$ 后面，那么**两者之间**的数都要被挪到最后。

- 以此类推

因此，只要先找出 $1$ 的位置，然后**从这里开始**遍历，统计**从 $1$ 开始的连续正整数**一共有多少个，再稍加计算（具体见代码）就行了。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k,p,q;
int a[100005];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k); p=1;
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(int i=1;i<=n;i++) //这个循环找 1 的位置
			if(a[i]==1){
				q=i;
				break;
			}
		for(int i=q+1;i<=n;i++)
			if(a[i]==p+1) p++; //找到下一个正整数
		p=n-p; //需要被挪动的数量
		printf("%d\n",(p%k==0)?(p/k):(p/k+1));
	}
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

首先我们思考什么数是不用排序的。

显然，序列中一个由 $1$ 开始，每次递增 $1$ 的子序列是不用排序的。

为什么呢？

因为我们把其他数按从大到小排好后这个子序列刚好构成排好序后的数列的前缀。

因为当我们把除此以外的其他数字选出来后，这些数字构成排序后的数组的前缀，其他数字被后置到数组末尾构成后缀。

然后，假定有 $m$ 个数不需要排序。那么每次可以排序 $k$ 个数，故答案为 $(n-m)/k$ （需要上取整）。

```cpp
#include<bits/stdc++.h>
//#define int long long
//#define lowbit(x) (x&-(x))
using namespace std;
const int maxn = 1e5+10;
int t;
int a[maxn];
void work(){
	int ans=0;
	stack<int> op;
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int now=0;
	for(int i=1;i<=n;i++){
		if(a[i]==now+1){
			now++;
		}
	}

	cout<<ceil((n-now)*1.0/k)<<'\n';
}
int main(){
ios::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);
int t;
cin>>t;
while(t--){
	work();
}

return 0;
}

```


---

## 作者：c20231020 (赞：0)

### 题目链接
[luogu](https://www.luogu.com.cn/problem/CF1768B)

[codeforces](https://codeforces.com/contest/1768/problem/B)

### 题目大意
给你一个长度为 $n$ 的排列 $^\dagger$ $p$ 和一个正整数 $k \le n$。

在一次操作中，你要

- 选择 $ k $ 个不同的元素 $p_{i_1}, p_{i_2}, \ldots, p_{i_k}$。
- 从排列中移除它们，然后将它们按照递增的顺序添加到排列的末尾。

例如，如果 $p=[2,5,1,3,4],k=2$，你选择 $5$ 和 $3$ 作为操作的元素，那么 $[2,\color{red}{5}\color{black}{,1,}\ \color{red}{3}\color{black}{,4}] \rightarrow [2,1,4,\color{red}{3},\color{red}{5}\color{black}]$。

找出将这个排列按递增顺序排序所需的最少操作数。可以证明，总是可以这样做的。

$^\dagger$ 一个长度为 $n$ 的排列是一个由 $1$ 到 $n$ 的不同整数按任意顺序组成的数列。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（$2$ 在数列中出现两次），$[1,3,4]$ 也不是排列（$n=3$ 但在数列中有 $4$）。

### 思路
一个事实：若原来的排列中存在一个长度为 $m$ 的子序列（不一定连续）形如  $1,2,\ldots,m$，则其他数一定会被操作，且这些数最多辅助其他数操作。

所以每次都可以最多将 $k$ 个数完成排序，答案就是 $\lceil \frac{n-m}{k} \rceil$。

#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[100010],m;
void solve(){
	cin>>n>>k;m=1;
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=1;i<=n;++i)if(a[i]==m)++m;//求 1~m 子序列
	--m;//注意 m 会多加一次
	cout<<ceil(1.0*(n-m)/k)<<'\n';
	return;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t=1;cin>>t;
	while(t--)solve();
	return 0;
}
```

CF 真的都是思维题啊。。。

---

