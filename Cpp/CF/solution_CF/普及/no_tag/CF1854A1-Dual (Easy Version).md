# Dual (Easy Version)

## 题目描述

[Popskyy &amp; tiasu - Dual](https://soundcloud.com/popskyy/popskyy-tiasu-dual)

⠀



The only difference between the two versions of this problem is the constraint on the maximum number of operations. You can make hacks only if all versions of the problem are solved.

You are given an array $ a_1, a_2,\dots, a_n $ of integers (positive, negative or $ 0 $ ). You can perform multiple operations on the array (possibly $ 0 $ operations).

In one operation, you choose $ i, j $ ( $ 1 \leq i, j \leq n $ , they can be equal) and set $ a_i := a_i + a_j $ (i.e., add $ a_j $ to $ a_i $ ).

Make the array non-decreasing (i.e., $ a_i \leq a_{i+1} $ for $ 1 \leq i \leq n-1 $ ) in at most $ 50 $ operations. You do not need to minimize the number of operations.

## 说明/提示

In the first test case, by adding $ a_1 = 2 $ to $ a_2 $ , we get the array $ [2, 3] $ which is non-decreasing.

In the second test case, the array changes as:

- $ [1, 2, -10, 3] $
- $ [1, 2, -10, 6] $
- $ [1, 2, -10, 12] $
- $ [1, 2, 2, 12] $

In the third test case, the final array is $ [2, 3, 3, 3, 3] $ .

## 样例 #1

### 输入

```
10
2
2 1
4
1 2 -10 3
5
2 1 1 1 1
8
0 0 0 0 0 0 0 0
5
1 2 -4 3 -10
10
11 12 13 14 15 -15 -16 -17 -18 -19
7
1 9 3 -4 -3 -2 -1
3
10 9 8
20
1 -14 2 -10 6 -5 10 -13 10 7 -14 19 -5 19 1 18 -16 -7 12 8
20
-15 -17 -13 8 14 -13 10 -4 11 -4 -16 -6 15 -4 -2 7 -9 5 -5 17```

### 输出

```
1
2 1
3
4 4
4 4
3 4
4
2 1
3 1
4 1
5 1
0
7
3 4
3 4
5 4
5 4
5 4
5 4
5 4
15
6 1
6 1
6 1
7 2
7 2
7 2
8 3
8 3
8 3
9 4
9 4
9 4
10 5
10 5
10 5
8
3 4
3 4
2 4
2 4
2 4
2 4
1 4
1 4
3
2 1
3 1
3 1
31
14 1
18 7
13 11
15 11
6 4
5 17
19 6
19 12
10 5
11 12
1 17
15 19
16 10
14 2
16 11
20 7
7 6
9 5
3 6
6 14
17 18
18 14
12 3
17 16
8 18
13 16
9 8
14 8
16 2
11 8
12 7
31
5 12
19 13
9 1
5 17
18 19
6 16
15 8
6 9
15 14
7 10
19 7
17 20
14 4
15 20
4 3
1 8
16 12
16 15
5 6
12 10
11 15
20 3
20 19
13 14
11 14
18 10
7 3
12 17
4 7
13 2
11 13```

# 题解

## 作者：legend_cn (赞：13)

# 思路
有趣的构造题，代码简单，重在思考

可以进行分类
### 第一种情况：序列全部为 $0$
不需要任何操作，直接输出 $0$ 即可。

### 第二种情况：序列全部为非负数
让 $a_i = a_{i - 1} + a_i$，即可保证列从左往右不降，需要 $n - 1$ 次操作。

### 第三种情况：序列全部为负数
让 $a_i = a_{i + 1} + a_i$，即可保证数列从左到右不降，需要 $n - 1$ 次操作

###  第四种情况：序列中有非负数也有负数
考虑把序列变回 $2$ 和 $3$ 种情况。

我们可以把序列中的每个数加上绝对值最大的数（如果当前就是觉绝对值最大的数，就不用加了）。

- 当绝对值最大的数是非负数时，序列全部变为非负数
- 当绝对值最大的数是负数时，序列全部变为负数

需要 $n - 1$ 次操作

--------
所以最后的操作数最大为 $2n - 2$，不超过题目的操作数限制。

# 代码
易错部分加了注释
```cpp
# include <bits/stdc++.h>
using namespace std;
//# define lc u << 1
//# define rc u << 1 | 1
typedef long long ll;
typedef unsigned long long ull;
const int N = 35;

int n;
int a[N];
pair <int, int> ans[105]; int tot; // 操作数最多为 2n-2 需要多开 
signed main ()
{
//	freopen ("test.in", "r", stdin);
//	freopen ("test.out", "w", stdout);
	int T;
	scanf ("%d", &T);
	while (T -- )
	{
		scanf ("%d", &n);
		int mx = 0;
		int id = 0;
		for (int i = 1; i <= n; i ++ )
		{
			scanf ("%d", &a[i]);
			if (abs (a[i]) > abs (mx))
				mx = a[i], id = i;
		}
		if (!mx)
		{
			printf ("0\n"); // 注意换行
			continue;
		}
		tot = 0; // 清空 
		for (int i = 1; i <= n; i ++ )
		{
			if (i == id)
				continue;
			ans[ ++ tot] = {i, id};
			a[i] += a[id];
		}
		if (a[id] > 0)
		{
			for (int i = 2; i <= n; i ++ )
				ans[ ++ tot] = {i, i - 1};
		}
		else
		{
			for (int i = n; i > 1; i -- )
				ans[ ++ tot] = {i - 1, i};
		}
		printf ("%d\n", tot);
		for (int i = 1; i <= tot; i ++ )
			printf("%d %d\n", ans[i].first, ans[i].second);
	}
	return 0;
}
```


---

## 作者：引领天下 (赞：7)

有趣的构造题。

**提示：本做法只适用于 A1，但对 A2 的做法有一定启发作用，若要完整弄清构造方法，请配合 [A2 的题解](https://www.luogu.com.cn/blog/yltx/cf1854a2-post)食用。**

题意：

给定一个长度为 $n$ 的序列，现在可以进行以下操作：

- 选择 $i,j$（注意 $i$ 可以等于 $j$），将 $a_i\leftarrow a_i+a_j$。

思路：

处理原数列太麻烦了，我们考虑怎么让原数列不影响我们的构造。

分 3 类情况讨论：

1. $a_n>0$，此时我们考虑直接不断让 $a_n$ 翻倍到一个足够大的数字 $T$，然后在对 $a_1\sim a_{n-1}$ 加上一个首项为 $a_n$ 的一个公比为 $2$ 的等比数列，因为 $a_n$ 足够大，所以原始的 $a_i$ 对这个等比数列来说可以忽略不计，不影响单调性。最大操作次数为 $7+2(n-1)=2n+5\le45<50$（以 $T=128$ 计）。

2. $a_n<0$，此时我们仍然考虑不断让 $a_n$ 翻倍到一个足够小的数字 $T$。但是如果我们套用上面的等比数列做法，会发现这样的构造会导致 $a_1\sim a_{n-1}$ 单调递增，但是 $a_n$ 小的离谱。于是不能这么做。我们换成依次将 $a_i$ 加上 $a_n$，然后做一遍后缀和。因为 $a_n$ 很小，所以加完之后 $a_i$ 全部是负的，后缀和一遍自然是单调递增的。最大操作次数为 $7+2(n-1)=2n+5\le45<50$（以 $T=-128$ 计）。

3. $a_n=0$，此时我们考虑检索 $a_1\sim a_{n-1}$：若全为 $0$，那直接就满足题意，不用做了；否则任意挑选一个元素加到 $a_n$ 上，化为前两种情况。

这样就做完了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,a[25];
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        vector<pair<int,int>>ans;
        int f=-1;
        if(!a[n]){
            for(int i=1;i<n;i++)if(a[i]!=0)f=i;
            if(f==-1){cout<<0<<endl;continue;}
            ans.push_back(make_pair(n,f));a[n]=a[f];
        }
        if(a[n]>0){
            while(a[n]<128)a[n]*=2,ans.push_back(make_pair(n,n));
            for(int i=2;i<n;i++)ans.push_back(make_pair(i,n)),ans.push_back(make_pair(n,n));
        }else if(a[n]<0){
            while(a[n]>-20)a[n]*=2,ans.push_back(make_pair(n,n));
            for(int i=n-1;i>=1;i--)ans.push_back(make_pair(i,n));
            for(int i=n-1;i>=1;i--)ans.push_back(make_pair(i,i+1));
        }
        cout<<ans.size()<<endl;
        for(auto i:ans)cout<<i.first<<' '<<i.second<<endl;
    }
    return 0;
}
```

---

## 作者：信息向阳花木 (赞：3)

由于我太弱了，赛时打的是 Div.2，觉得 C1 还是放得比较开，操作数 $k \le 50$ 还是很容易卡过去的 QAQ。

首先，最容易想的一种情况：如果所有数都为 $0$，那么我们啥都不用干，直接输出 $0$ 即可。

接着，如果数列 $a$ 全为非负数或全为非正数，我们只需要对其进行前缀和或后缀和即可。举个例子，当 $a$ 全为非负数时，$a_i = a_{i-1} + a_i$。由于 $a_i \ge 0$，所以 $a_{i-1} + a_i \ge a_{i-1}$，即 $a_i \ge a_{i-1}$；反之，当 $a$ 全为非正数时，$a_i = a_{i+1} + a_i$。由于 $a_i \le 0$，所以 $a_{i+1}+a_i \le a_{i+1}$，即 $a_i \le a_{i+1}$。无论哪种情况，我们都可以保证 $a$ 序列是非递减的。

自然地，如果 $a$ 序列有正有负，我们会想到将 $a$ 序列变为 **全非负** 或 **全非正** 的情况来处理。我们可以找到 $a$ 序列中 **绝对值** 最大的数 $x$，将所有数都加上 $x$。由于 $x$ 的绝对值是最大的，所有数加上 $x$ 以后，正负性会和 $x$ 相同。这样我们又把问题转化为全非负或全非正的情况，问题变得可做。

将所有数加上 $x$ 的操作次数为 $n-1$（$x$ 本身可以不加），前（后）缀和的操作次数为 $n - 1$，总共的操作数为 $2n - 2$，$50$ 次完全够了。C2 的答案范围更小，需要考虑更多情况，但 C1 到这就够了。

```cpp
#include <iostream>
#include <cstdio>

#include <cmath>
#include <algorithm>

using namespace std;

const int N = 50;

inline void in(int &x)
{
	x = 0; bool f = 0; char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-') f = 1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c & 15);
		c = getchar();
	}
	x = f ? -x : x;
}

inline void out(int x)
{
	if(x < 0) putchar('-'), x = -x;
	if(x / 10) out(x / 10);
	putchar((x % 10) | 48);
}

int n, t, maxx, tot, k;
int a[N];
pair<int, int> ans[N];

int main()
{
	in(t);
	while (t -- )
	{
		in(n);
		
		maxx = tot = k = 0;
		for (int i = 1; i <= n; i ++ )
		{
			in(a[i]);
			if(abs(a[i]) > abs(maxx)) maxx = a[i], k = i;
		}
		if(maxx == 0)
		{
			puts("0");
			continue;
		}
		
		for (int i = 1; i <= n; i ++ )
		{
			if(i == k) continue;
			ans[++ tot] = {i, k};
			a[i] += a[k];
		}
		if(a[k] < 0) for (int i = n; i > 1; i -- ) ans[++ tot] = {i - 1, i};
		if(a[k] > 0) for (int i = 1; i < n; i ++ ) ans[++ tot] = {i + 1, i};
		
		printf("%d\n", tot);
		for (int i =  1; i <= tot; i ++ )
		{
			printf("%d %d\n", ans[i].first, ans[i].second);
		}
	}
	return 0;
}


```

---

## 作者：Wf_yjqd (赞：2)

比较简单的构造题。

------------

考虑若没有负数，直接让 $a_i$ 加上 $a_{i-1}$，求一个前缀和。

显然可以保证 $a_i\ge a_{i-1}(2\le i\le n)$。

没有负数则求后缀和，同理。

转换问题变成在 $51-n$ 次操作内消除所有负数或者正数。

考虑任意选一个非 $0$ 数 $a_i$ 倍增 $5$ 次后一定满足 $\left| a_i\right|>\left|a_j\right|(1\le j\le n,i\ne j)$。

则将所有符号与 $a_i$ 相反的数加上 $a_i$ 即可。

最大次数为 $43$。

------------

放个代码。

赛时好像把 $0$ 也当成符号相反的操作了，不过对此题没有影响。

注意特判全 $0$ 情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[23];
inline bool check(){
    for(int i=1;i<n;i++)
        if(a[i]>a[i+1])
            return 0;
    return 1;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        if(check()){
            puts("0");
            continue;
        }
        int maxx=-168,minn=168,maxid,minid,cntf=0,cntz=0,cnt0=0;
        for(int i=1;i<=n;i++){
            cntf+=(a[i]<0);
            cntz+=(a[i]>0);
            cnt0+=(a[i]==0);
            if(a[i]>maxx){
                maxx=a[i];
                maxid=i;
            }
            if(a[i]<minn){
                minn=a[i];
                minid=i;
            }
        }
        if(!cntf){
            printf("%d\n",cnt0+n-1);
            for(int i=1;i<=n;i++)
                if(!a[i])
                    printf("%d %d\n",i,maxid);
            for(int i=2;i<=n;i++)
                printf("%d %d\n",i,i-1);
        }
        else if(!cntz){
            printf("%d\n",cnt0+n-1);
            for(int i=1;i<=n;i++)
                if(!a[i])
                    printf("%d %d\n",i,minid);
            for(int i=n-1;i>=1;i--)
                printf("%d %d\n",i,i+1);
        }
        else{
            printf("%d\n",cnt0+cntf+n+4);
            for(int i=1;i<=5;i++)
                printf("%d %d\n",maxid,maxid);
            for(int i=1;i<=n;i++)
                if(a[i]<=0)
                    printf("%d %d\n",i,maxid);
            for(int i=2;i<=n;i++)
                printf("%d %d\n",i,i-1);
        }
    }
    return 0;
}
```


---

## 作者：船酱魔王 (赞：1)

# CF1854A1 Dual (Easy Version) 题解

## 题意回顾

长度为 $ n $ 的数列 $ a $，你每次可以让一个数加上另一个数（可以加本身），通过**最多** $ 50 $ 次操作使得数列不降。

$ n \le 20 $，$ |a_i| \le 20 $。

## 分析

毕竟是简单版本，$ 50 $ 次的限制感觉比较宽松，因此可以适当乱搞。

先考虑两种简单情况：

* 考虑全是非负数的情况，从前往后依次把每个数加上前一个数，即可实现不降。

* 全是非正数时，从后往前依次把每个数加上后一个数，即可实现不降。

最多 $ 20 $ 次即可达成目标。

如果我们有正有负，则考虑把所有数变成同号（含 $ 0 $），进入简单情况。可以发现正数加一个负大值即可变成负，负数加一个正大值即可变成正，最多 $ 20 $ 次即可同号。

如何构造极大值呢？考虑把一个数自加 $ 10 $ 次，这个数会变成 $ 1024 $ 倍。肯定够大。

本题解所用的代码在生成绝对值极大的值后把统一符号步骤和依次加上前/后一个数两步合并了，即用第一个数/最后一个数加上绝对值极大的值后每个数加上前/后一个数**两次**，本质上还是和前面描述等价的。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
const int N = 25;
int T;
int n;
long long a[N];
struct node {
	int x, y;
};
node make(int x2, int y2) {
	node res;
	res.x = x2;
	res.y = y2;
	return res;
}
vector<node> ans;
int ok = 1;
void out() {
	cout << ans.size() << endl;
	for(int i = 0; i < ans.size(); i++) {
		cout << ans[i].x << " " << ans[i].y << endl;
		a[ans[i].x] += a[ans[i].y];
	}
}
int main() {
	cin >> T;
	for(int ti = 1; ti <= T; ti++) {
		cin >> n;
		ans.clear();
		int pos = 0, ct = 0;
		for(int i = 1; i <= n; i++) {
			cin >> a[i];
			if(a[i] != 0) {
				ct++;
				if(ct == 1) pos = i;
			}
		}
		if(ct == 0) {
			out();
			continue;
		}
		for(int i = 1; i <= 10; i++) {
			ans.push_back(make(pos, pos));
		}
		if(a[pos] < 0) {
			ans.push_back(make(n, pos));
			ans.push_back(make(n, pos));
			for(int i = n - 1; i >= 1; i--) {
				ans.push_back(make(i, i + 1));
				ans.push_back(make(i, i + 1));
			}
		} else {
			ans.push_back(make(1, pos));
			ans.push_back(make(1, pos));
			for(int i = 2; i <= n; i++) {
				ans.push_back(make(i, i - 1));
				ans.push_back(make(i, i - 1));
			}
		}
		out();
	}
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：1)

easy version 和 hard version 都说一下。

首先注意到两条结论：

+ 如果 $\forall a_i$，有 $a_{i}\ge0$，则可以用 $(n-1)$ 操作进行前缀和完成。
+ 如果 $\forall a_i$，有 $a_{i}<0$，则可以用 $(n-1)$ 操作进行后缀和完成。

证明显然。第一条 $a_{i}\ge0\to a_{i}+a_{i+1}\ge a_{i+1}$，第二条同理。

所以只要全正或者全负，咱就赢了。

## How to solve Easy Version?

$50$ 次意味着我们可以有 $30$ 次操作使得原序列全正或者全负。

而这种操作是简单的，我们只要选出绝对值最大的 $k$，然后将它加给每一个和他符号相反的。这样所有数的符号都是 $k$ 的符号。这是最多 $n-1$ 次。

然后就是简单的，总共 $n-1+n-1=2n-2$ 次。

## How to solve Hard Version?

上面的构造依然是很优越的。

我们设和 $k$ 相同符号的数总共有 $m$ 个，操作次数为 $p=(n-m)+n-1=2n-m-1$。当 $m\ge 8$ 时，发现 $p\le 31$，赢！

当 $m<8$ 怎么办呢，我们只要让 $m\gets n-m$ 就好了。将与 $k$ 符号相反且绝对值最大的数 $k^\prime$，使其自增绝对值超过 $k$，然后转化为 $m\ge 8$ 的情况。

我们发现，自增是 $\log V$ 的，在此题最大为 $5$，第一种情况最大的操作次数是 $20\times 2-8-1=31$，正好符合要求。第二种情况呢？最大为 $p=7$，此时次数为 $20\times 2-(20-7)-1+5=31$，依然符合要求！

这样就解决了！只放 hard version 的代码了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,l,r) for(i=l;i<=r;++i)
#define req(i,r,l) for(i=r;i>=l;--i)
pair<int,int> ans[55],ans1[55],ans2[55];
int cnt1,cnt2;
int a[55];
int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		cnt1=cnt2=0;
		int ct=0;
		int n,i,mx=-(1<<30),mn=1<<30,psx,psn,psnn,mnn=1<<30,pos,psx2,cmx=-(1<<30);
		int cnt=0;
		scanf("%d",&n);
		rep(i,1,n)scanf("%d",a+i);
		rep(i,1,n)if(abs(a[i])>mx)mx=abs(a[i]),psx=i;
		rep(i,1,n)if(abs(a[i])<mx && abs(a[i])>cmx && a[i]*a[psx]<0) cmx=abs(a[i]),psx2=i;
//		printf("%d %d\n",psx2,psx);
		rep(i,1,n)if(a[i]<mn)mn=a[i],psn=i;
		rep(i,1,n)if(a[i]*a[psx]>0)++ct;
		if(ct>=8 || 2*n<=31)
		{
			rep(i,1,n)if(a[i]*a[psx]<0)ans[++cnt]={i,psx},a[i]+=a[psx];
			if(a[psx]>0)rep(i,2,n)ans[++cnt]={i,i-1};
			else req(i,n-1,1)ans[++cnt]={i,i+1};
		}else
		{
			while(abs(a[psx2])<abs(a[psx]))ans[++cnt]={psx2,psx2},a[psx2]+=a[psx2];
			rep(i,1,n)if(a[i]*a[psx2]<0)ans[++cnt]={i,psx2},a[i]+=a[psx2];
			if(a[psx2]>0)rep(i,2,n)ans[++cnt]={i,i-1};
			else req(i,n-1,1)ans[++cnt]={i,i+1};
		}
		printf("%d\n",cnt);
		rep(i,1,cnt)printf("%d %d\n",ans[i].first,ans[i].second);
	}
	return 0;
}
```

赛时代码，非常混乱。

---

## 作者：Zimo_666 (赞：0)

## C1 .Dual (Easy Version)

有意思的一道题。

考虑如果都是 `0` 那么显然就不用做。

如果都是正数或者复数显然直接从后往前推一遍类似前缀和或者从后往前推一边类似后缀和的东西也做完了。

下面考虑如果有有正有负怎么办。

那么我取数当中绝对值最大的那个，然后全序列都加上这个数，显然全序列正负性和那个目标数相同，然后就直接转化上去了。

最多操作次数是 $2n$ 级别的，可以通过。

[Code](https://www.luogu.com.cn/record/125279140)

附赠一个 `checker`：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
const int N=1e5+7;
int a[N];

int main(){
  // cin>>T;
  // while(T--){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    int q;
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
      int qwq,pwp;
      scanf("%d%d",&qwq,&pwp);
      a[qwq]+=a[pwp];
    }
    for(int i=1;i<=n;i++) printf("%d ",a[i]);
    puts("");
    bool flag=0;
    for(int i=2;i<=n;i++){
      if(a[i]<a[i-1]){flag=1;break;}
    }
    if(flag) printf("False\n");
    else printf("True\n");
  // }
    return 0;
}
```

---

## 作者：SakurajiamaMai (赞：0)

## **通用于简单版和困难版**

贪心地去想，我们一定尽可能让每次走的次数都具有价值。现在这样想，如果数组之内的正数多，那么我们让一个最大的数自增，增到什么程度呢？直到我们能把数组内的所有数变成正数为止。相反，如果负数多，那么我们把所有的数变为负数。显而易见，有一个规律：如果全部是正数，那么我们只需要用后一个数加上前一个数就可以了。

由于次数限制是 $31$ 次，我们每次相加需要消耗 $19$ 次。那么留给我们全部置负或者正的次数为 $12$ 次。如果正数多，就按正数来；如果负数多，就按负数来。**这里注意**，**如果此时数组里只有 $1$ 和 $-20$，那么我们的 $1$ 需要自增 $5$ 次才够**。显然不如直接用 $-20$ 来得快，可以省去这 $5$ 次。相同地，如果我们的正负数之差小于 $5$，可以按照其相反的次序来。

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<map>
using namespace std;
const int N=1e6+10,mod=1e9+7;
string s;
int n,t,a[N],res,num,ans,m,k_z,k_f;
int z,f,f_num,z_num,f_sum,z_sum;
int maxx,minn,max_id,min_id;
int cnt1[N],cnt2[N];
map<int,pair<int,int>>mp1,mp2;
bool vis[N];
void solve_z()
{
        minn=abs(minn);
        while(a[max_id]<minn) res++,a[max_id]+=a[max_id],z_num++;
        res+=(n-1);
        for(int i=1;i<=n;i++) if(a[i]<0) res++,cnt1[i]++,mp1[i]={i,max_id},a[i]+=a[max_id];
        cout<<res<<endl;
        while(z_num!=0) z_num--,cout<<k_z<<" "<<k_z<<endl;
        for(int i=1;i<=n;i++) while(cnt1[i]!=0) cnt1[i]--,cout<<mp1[i].first<<" "<<mp1[i].second<<endl;
        for(int i=1;i<=n-1;i++) cout<<i+1<<" "<<i<<endl;
}
void solve_f()
{
        while((-a[min_id])<maxx) a[min_id]+=a[min_id],res++,f_num++;
        res+=(n-1);
        for(int i=1;i<=n;i++) if(a[i]>0) res++,cnt1[i]++,mp1[i]={i,min_id},a[i]+=a[min_id];
        cout<<res<<endl;
        while(f_num!=0) f_num--,cout<<k_f<<" "<<k_f<<endl;
        for(int i=1;i<=n;i++) while(cnt1[i]!=0) cnt1[i]--,cout<<mp1[i].first<<" "<<mp1[i].second<<endl;
        for(int i=n;i>=2;i--) cout<<i-1<<" "<<i<<endl;
}
void solve()
{
    cin>>n;
    z=f=num=res=ans=m=z_num=f_num=z_sum=f_sum=0;
    mp1.clear();
    memset(cnt2,0,sizeof cnt2);
    a[0]=-30,maxx=-30,minn=30;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]>0) z++,z_sum+=a[i];
        else if(a[i]==0) ;
        else f++,f_sum+=a[i];
        if(maxx<a[i]) maxx=a[i],max_id=i,k_z=i;
        if(minn>a[i]) minn=a[i],min_id=i,k_f=i;
    }
    if(z>f) if(z_sum<abs(f_sum)&&abs(z-f)<=5) solve_f();
            else solve_z();
    else{
        if(z_sum>abs(f_sum)&&abs(z-f)<=5)solve_z();
        else solve_f();
    }
}
signed main()
{
    std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
```


---

## 作者：Rainsleep (赞：0)

考虑两种理想情况。
+ $\forall a[i] \ge 0$，即 $\displaystyle \min_{i=1}^n \ge 0$

此时我们令 $a[i] = a[i - 1] + a[i]$，由于 $a[i] \ge0$，所以 $a[i] \ge a[i- 1]$，满足单调不减的要求。

+ $\forall a[i] \le 0$，即 $\displaystyle \max_{i=1}^n \le 0$

此时我们令 $a[i] = a[i] + a[i + 1]$ ，因为 $a[i]\le 0$，所以 $a[i] + a[i +1] \le a[i + 1]$，满足单调不减的要求。

以上两种操作均只需要 $n - 1$ 次即可完成。

---

考虑实际情况，我们试图将所有的情况转化为上述两种。

以 $\displaystyle \max_{i=1}^n \le 0$ 的情况举例，用一些小贪心的思路，我们试图将所有的负数加上最大的正数使得其归正，然而有的负数的绝对值可能大于最大值，所以我们一直将最大数倍增，直到其大于 $|\displaystyle\min_{i=1}^n|$，这样的收益显然大于让最小值加两次。

对于另外一种情况也是同样的道理。我们发现最小次数是 $\left \lceil \log |V|\right \rceil = 5$。

对于 $\displaystyle \min_{i=1}^n \ge 0$ 的情况，实际上是对称的。在实际操作中，我们也会选择需要加操作次数少的进行，当负数正数平衡，即都为 $\dfrac{n}{2}$ 时，我们没有最优决策，最后的操作次数为 $k=5+10+(20-1)=34$。

--- 

我们考虑在一些步骤优化  ，使得步数达到 $31$ 步内。

我们设 $s1 = \displaystyle\sum_{i = 1}^n[a[i] > 0],s2 = \sum_{i = 1}^n[a[i] < 0]$，显然有 $s1 + s2 \le 20$。

考虑我们在倍增的时候的次数，设 $\max, \min$ 倍增合法次数分别为 $t1, t2$。

考虑感性了解，两者是一个平衡的状态，当我们想让 $\max$ 倍增次数尽量多时，$\max$ 尽量小；而当我们想让 $\min$ 倍增次数尽量多时，是让 $|\min|$ 尽量小。

事实上，由于平衡的关系，所以我们获得了一个关系：$t1 + t2 \le 5$。证明的话可以自己想一想，我不是很会比较形式化的。

总而言之，两式相加，得到 $(s1 + t1) + (s2 + t2) \le 25$，我们取较小者后 $+ 19$ 即为结果。

一般时，这两份我们任取较小那份即可，最坏情况时，我们将其划分为 $\{12, 13\} / \{13, 12\}$ 两个部分了，取最坏 $12$ 即可。

最后我们得到答案：

$$12 + 19 = 31$$


---

## 作者：Purslane (赞：0)

# Solution

构造太残暴了，而且 A1 和 A2 没什么差别啊。

考虑所有数是非负的可以做前缀和，所有数是非正的可以做后缀和，我们只需要 $n-1$ 次操作就可以解决战斗。

因此我们只需要把所有数变成非正或者非负。我们的假设应该是有正有负。

设最大的数是 $A$，最小的数是 $B$。如果 $A+B \ge 0$，可以考虑把所有负的数加上 $A$，这样变成全正；否则把所有正的数加上 $B$，这样变成全负。因此只需要最多 $2n-2$ 次操作就可以解决战斗，这样可以通过 Easy Version。

对于 Hard Version，我们最多有 $12$ 次操作让他们变为全正或全负。不妨设此时 $A+B \ge 0$。如果负数很少，有最多 $12$ 个，我们直接干；否则说明正数很少，最多 $7$ 个。然后我们惊奇的发现最大的负数 $-1$ 自我迭代 $5$ 次都可以到 $-32$，足以把所有正数打成负的，而剩余的 $7$ 次操作正好可以和那些正数挨个加一遍。于是就可以用 $31$ 次操作通过 Hard Version。

代码很好写，不贴了。

---

## 作者：sz_jinzikai (赞：0)

[洛谷传送门](/problem/CF1854A1) & [CF 传送门](//codeforces.com/problemset/problem/1854/A1)
# 思路
这题我们可以分为 $3$ 种情况分开讨论：
1. 全是自然数；
2. 全是非正数，即全是 $\le0$ 的数；
3. 有自然数也有负数。

接下来，我们看看这几种情况的解决方案：
1. 求一个前缀和即可；
2. 求一个后缀和即可；
3. 先将最大的数不停地加自己，直到 $\ge20$ 为止，然后将所有负数加上这个数，最后求前缀和即可。这样最坏情况会运算 $5+19+19=43$ 次，不会超过题目限制的 $50$ 次。

# 代码
```cpp
//CF1854A1
# include <bits/stdc++.h> //万能头 
using namespace std;
typedef pair <int, int> pii; //缩写
int t, n, a[25], maxi;
bool f;
vector <pii> v; //这是记录答案的 vector
int main () {
	cin >> t;
	while (t --) { //多组数据通用写法
		f = 1, maxi = 0; //多组数据要重置！
		cin >> n;
		for (int i = 1; i <= n; ++ i) {
			cin >> a[i];
			f &= (a[i] >= 0); //判断是不是全自然数
			if (a[i] > a[maxi])
				maxi = i;
		}
		if (f) { //全是自然数
			cout << n - 1 << '\n';
			for (int i = 1; i < n; ++ i)
				cout << i + 1 << ' ' << i << '\n'; //前缀和
			continue ;
		}
		if (a[maxi] <= 0) { //最大值小于等于 0，说明全部非负
			cout << n - 1 << '\n';
			for (int i = n; -- i;)
				cout << i << ' ' << i + 1 << '\n'; //后缀和
			continue ;
		}
		v.clear (); //多组数据要清空！
		while (a[maxi] < 20)
			v.push_back ({maxi, maxi}), a[maxi] <<= 1; //自乘最大值
		for (int i = 1; i <= n; ++ i)
			if (a[i] < 0)
				v.push_back ({i, maxi}); //所有负数加上最大值
		for (int i = 1; i < n; ++ i)
			v.push_back ({i + 1, i}); //前缀和
		cout << v.size () << '\n'; //输出长度
		for (pii i : v)
			cout << i.first << ' ' << i.second << '\n'; //输出方案
	}
	return 0; //结束程序
}
```

---

## 作者：Zkl21 (赞：0)


## 题目大意

给定一个长度为 $n(n\le 20)$ 的序列 $a$，其中 $|a_i|\le 20$。你可以随意选定一个数对 $(i,j)(1\le i,j\le n)$，令 $a_i=a_i+a_j$。请你构造一种方式，使得在不超过 $50$ 次以上操作将原序列变为不下降子序列，输出构造方式。

## 思路

首先我们简单考虑一下如何暴力构造，比较普通的方法就是遍历每一个数判断是否合法，如果不合法就加上一个正数，直到合法。

那么又如何保证次数不超过 $50$ 呢？

我们可以先找到一个正数 $a_x$，令 $a_x$ 自增到不小于 $20$，显然自增次数不会超过 $5$。然后我们找到第 $2$ 个数 $a_2$，令 $a_2=a_2+a_x$ 直到 $a_1\le a_2\wedge a_2>0$，显然该操作不会超过 $2$ 次。从 $a_3$ 开始同理，我们可以利用前缀和的思想，每次令 $a_i=a_i+a_{i-1}$，同样对于每个数的操作不会超过两次。
当 $n=20$ 时，最终操作次数为 $5+2(n-1)=5+2\times 19=43$ 次，显然合法。

如果我们没有办法找到一个正数，怎么办？同样利用前缀和的思想，由于所有数都不是正数，那么我们求完前缀和后一定能保证 $a_i\ge a_{i+1}$，我们要求的是不下降子序列，那么就求后缀和就好了。当 $n=20$ 时，最终操作次数为 $n-1=19$，显然合法。

## 代码
```cpp
#include<iostream>
using namespace std;
const int N=55;
int n,a[N],cnt;
typedef pair<int,int>PII;
#define x first
#define y second
PII ans[N];
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		int flag=0;
		for(int i=1;i<=n;i++)
			if(a[i]>0)flag=i;
		int res=0;
		if(flag)
		{
			cnt=0;
			for(int i=1;i<=5;i++)
			{
				a[flag]+=a[flag];
				ans[++cnt]={flag,flag};
			}
			if(n>1)
				for(int i=1;i<=2;i++)
				{
					a[2]+=a[flag];
					ans[++cnt]={2,flag};
				}
			for(int i=3;i<=n;i++)
			{
				a[i]+=a[i-1]*2;
				ans[++cnt]={i,i-1};
				ans[++cnt]={i,i-1};
			}
			cout<<cnt<<"\n";
			for(int i=1;i<=cnt;i++)cout<<ans[i].x<<' '<<ans[i].y<<'\n';
		}
		else 
		{
			cout<<n-1<<"\n";
			for(int i=n;i>1;i--)cout<<i-1<<' '<<i<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：rabbitohh (赞：0)

Hard version 请见：[CF1854A2 题解](https://www.luogu.com.cn/blog/zhangjianxi/solution-cf1854a2)  
首先，我们发现如果序列全正，那么只需要做一次前缀和即可。若序列全非正，做一次后缀和即可。  
那么我们考虑序列既不是全正，也不是全非正应该怎么办。注意到序列不是全非正，那么一定 $\forall a_i>0$，然后我们可以通过不断将 $a_i$ 加至 $a_i$ 来使得 $a_i>20$。因为 $2^5=32$，所以最多 $5$ 次操作即可做到这一点。然后我们将 $a_1$ 到 $a_n$ 全部加上 $a_i$ 即可，该部分操作次数为 $20$。然后序列就变为全正了，前缀和即可。总操作次数为 $5+20+19=44$。  
   
Code:
```cpp
#include<unordered_map>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<vector>
#include<cmath>
#include<queue>
#include<map>
#include<set>
#define int long long
using namespace __gnu_pbds;
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e5;
int a[N];
int cti[N],ctj[N],idx=0;
void add(int j,int i)
{
    cti[++idx]=i;
    ctj[idx]=j;
}

void ans()
{
    idx=0;
    int n;
    cin>>n;
    int flag=1;//是否全<=0
    int id=0;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]>0)
        {
            // cout<<'a'<<i<<'\n';
            id=i;
            flag=0;
        }
    }
    if(flag)//全<=0
    {
        for(int i=n-1;i>=1;i--)
        {
            add(i+1,i);
        }
    }
    else
    {
        while(a[id]<=20)
        {
            add(id,id);
            a[id]*=2;
        }
        for(int i=1;i<=n;i++)
        {
            add(id,i);
        }
        for(int i=1;i<=n-1;i++)
        {
            add(i,i+1);
        }
    }
    cout<<idx<<'\n';
    for(int i=1;i<=idx;i++)
    {
        cout<<cti[i]<<' '<<ctj[i]<<'\n';
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--)
    {
        ans();
    }
    return 0;
}

```


---

