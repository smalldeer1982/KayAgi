# [ABC258E] Packing Potatoes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc258/tasks/abc258_e

ベルトコンベアに載って $ 10^{100} $ 個のじゃがいもが $ 1 $ 個ずつ流れてきます。流れてくるじゃがいもの重さは長さ $ N $ の数列 $ W\ =\ (W_0,\ \dots,\ W_{N-1}) $ で表され、$ i\ \,\ (1\ \leq\ i\ \leq\ 10^{100}) $ 番目に流れてくるじゃがいもの重さは $ W_{(i-1)\ \bmod\ N} $ です。ここで、$ (i-1)\ \bmod\ N $ は $ i\ -\ 1 $ を $ N $ で割った余りを表します。

高橋君は、まず空の箱を用意し、次のルールに従ってじゃがいもを順番に箱に詰めていきます。

- じゃがいもを箱に入れる。箱に入っているじゃがいもの重さの総和が $ X $ 以上になったら、その箱には蓋をし、新たに空の箱を用意する。

$ Q $ 個のクエリが与えられます。$ i\ \,\ (1\ \leq\ i\ \leq\ Q) $ 番目のクエリでは、正整数 $ K_i $ が与えられるので、$ K_i $ 番目に蓋をされた箱に入っているじゃがいもの個数を求めてください。問題の制約下で、蓋をされた箱が $ K_i $ 個以上存在することが証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ X\ \leq\ 10^9 $
- $ 1\ \leq\ W_i\ \leq\ 10^9\ \,\ (0\ \leq\ i\ \leq\ N\ -\ 1) $
- $ 1\ \leq\ K_i\ \leq\ 10^{12}\ \,\ (1\ \leq\ i\ \leq\ Q) $
- 入力は全て整数

### Sample Explanation 1

$ 2 $ つの箱に蓋をするまでの高橋くんの行動は以下の通りです。 - 空の箱を用意する。 - $ 1 $ 番目のじゃがいもを箱に入れる。箱に入っているじゃがいもの重さの総和は $ 3 $ である。 - $ 2 $ 番目のじゃがいもを箱に入れる。箱に入っているじゃがいもの重さの総和は $ 3\ +\ 4\ =\ 7 $ であり、$ X\ =\ 5 $ 以上になったのでこの箱には蓋をする。 - 新たに空の箱を用意する。 - $ 3 $ 番目のじゃがいもを箱に入れる。箱に入っているじゃがいもの重さの総和は $ 1 $ である。 - $ 4 $ 番目のじゃがいもを箱に入れる。箱に入っているじゃがいもの重さの総和は $ 1\ +\ 3\ =\ 4 $ である。 - $ 5 $ 番目のじゃがいもを箱に入れる。箱に入っているじゃがいもの重さの総和は $ 1\ +\ 3\ +\ 4\ =\ 8 $ であり、$ X\ =\ 5 $ 以上になったのでこの箱には蓋をする。 $ 1 $ 番目に蓋をされた箱には $ 2 $ つのじゃがいもが入っており、$ 2 $ 番目に蓋をされた箱には $ 3 $ つのじゃがいもが入っています。

## 样例 #1

### 输入

```
3 2 5
3 4 1
1
2```

### 输出

```
2
3```

## 样例 #2

### 输入

```
10 5 20
5 8 5 9 8 7 4 4 8 2
1
1000
1000000
1000000000
1000000000000```

### 输出

```
4
5
5
5
5```

# 题解

## 作者：xqh07 (赞：2)

# 具体思路：
  
首先，我们可以通过前缀和上二分，预处理出以每一个编号的土豆为开头，箱子最终装的土豆个数以及下一个箱子的第一个土豆编号。

根据抽屉原理，在装了至多 $n+1$ 个土豆后，必有循环节出现。

将循环开始的土豆编号和循环节长度记录下来，就可以做到 $O(1)$ 回答询问。

时间复杂度 $O(n\log_{}{n} +q)$。

## Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, q, x, a[200005], s[200005], nxt[200005], ans[200005], cnt;
int vis[200005], rve[200005], st, cyc;
signed main()
{
	scanf("%lld%lld%lld", &n, &q, &x);
	for(int i = 1; i <= n; i++) 
	{
		scanf("%lld", &a[i]);
		s[i] = s[i - 1] + a[i];
	}
	for(int i = 1; i <= n; i++)
	{
		int y = s[n] - s[i - 1], z = x;
		if(y >= x)
		{
			int pos = lower_bound(s + 1, s + n + 1, s[i - 1] + x) - s;
			nxt[i] = pos % n + 1;
			ans[i] = pos - i + 1;
		}
		else
		{
			ans[i] += n - i + 1;
			z -= y;
			ans[i] += n * (z / s[n]);
			z %= s[n];
			int pos = lower_bound(s + 1, s + n + 1, z) - s;
			ans[i] += pos;
			nxt[i] = pos % n + 1;
		}
	}
	int i = 1;
	vis[1] = rve[1] = cnt = 1;
	while(1)
	{
		i = nxt[i];
		++cnt;
		if(vis[i])
		{
			st = vis[i], cyc = cnt - vis[i];
			break;
		}
		vis[i] = cnt, rve[cnt] = i;
	}
	while(q--)
	{
		int y;
		scanf("%lld", &y);
		if(y <= st)
			printf("%lld\n", ans[rve[y]]);
		else
			printf("%lld\n", ans[rve[st + (y - st) % cyc]]);
	}
	return 0;
}

```


---

## 作者：FXT1110011010OI (赞：2)

## 具体思路

暴力很好想，就是模拟，装满就下一包，一直装到第 $k$ 袋。

但是我们可以发现，确定了起点，终点就是固定的，也就是说最多只有 $n$ 个起点和 $n$ 个终点。容易发现，前 $n + 1$ 次打包中一定有循环节（最差情况下，如果前 $n$ 次打包起点都不同，那第 $n + 1$ 次一定会与前面重复）。

我们可以模拟 $n$ 次找出 $n$ 个循环节，每次用二分找一下终点位置即可。具体见代码。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL N = 4e5 + 10;

LL n, q, x;
LL w[N], sum, s[N];
LL now, xh[N]; // now记录起点，xh记录前n项的答案
LL tmp, res[N], cnt; // res记录循环节的答案

int main()
{
    scanf("%lld%lld%lld", &n, &q, &x);
    for (LL i = 0; i < n; i ++ )
    {
        scanf("%lld", &w[i]);
        w[i + n] = w[i]; //因为是循环，所以要复制一遍
        sum += w[i];
    }
    for (LL i = 0; i < n * 2; i ++ ) s[i] = i == 0 ? w[i] : s[i - 1] + w[i]; // 前缀和
    for (LL i = 0; i < n; i ++ )
    {
        xh[i] = x / sum * n; // x > s
        LL t; // 终点位置
        if (x % sum) t = lower_bound(s + now, s + n * 2, (now == 0 ? x % sum : s[now - 1] + x % sum)) - s;
        else t = now - 1;
        xh[i] += t - now + 1;
        now = (t + 1) % n; // 更新起点
    }
    tmp = now; // 此时的now必与之前的某个起点相同
    while (1)
    {
        res[cnt] = x / sum * n;
        LL t;
        if (x % sum) t = lower_bound(s + now, s + n * 2, (now == 0 ? x % sum : s[now - 1] + x % sum)) - s;
        else t = now - 1;
        res[cnt ++ ] += t - now + 1;
        now = (t + 1) % n;
        if (tmp == now) break;
    }
    while (q -- )
    {
        LL k;
        scanf("%lld", &k);
        k -- ; // 从第0次开始才能取余！！！
        if (k < n) printf("%lld\n", xh[k]);
        else printf("%lld\n", res[(k - n) % cnt]); // 一定在循环节里
    }
    return 0;
}
```

---

## 作者：xzy090626 (赞：1)

猜个结论，显然每个箱子的重量会形成循环，而循环节长度是 $O(n)$ 的。实际上这一点也很容易证明，因为以每个土豆为起点的取法显然只有一种，那么总共的不同取法最多也就只有 $n$ 种，那么循环节最大也就是 $n$。

那么怎么快速求循环节呢？我们先断环为链，复制一遍；求了前缀和之后二分求第一个 $\geq X$ 的位置，就可以 $O(\log n)$ 求前 $n$ 个箱子的重量了。

但是有个问题：注意到 $X$ 可能会非常大，前缀和可能不够；这个时候我们用 $X$ 对 $n$ 个土豆质量总和取模，就避免了这一问题，可以发现它对于最终结果没有影响。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 4e5 + 7;
int n,q,x;
int a[N],s[N],w[N];
signed main(){
	cin>>n>>q>>x;
	for(int i=1;i<=n;++i){
		cin>>w[i];
		w[i+n] = w[i];//复制，断环为链
	}
	for(int i=1;i<=2*n;++i) w[i] += w[i-1];//前缀和
	int p = 1,len = 1;
	for(int i=1;!s[p];++i,++len){//找循环节
		// p 是每个箱子中第一个土豆
		s[p] = i;//s[p] 代表以 p 为第一个土豆的箱子的编号
		int d = lower_bound(w,w+2*n+1,w[p-1]+x%w[n])-w; //找到右端点的土豆位置
		a[i] = d - p + 1 + x/w[n]*n;//每个箱子装的数量
		p = d % n + 1;
	}
	int l = len - s[p], h = s[p];
	// l 是循环节的长度
	// h 是进入循环前面的箱子数量，它们只会出现一次
	while(q--){
		int k;cin>>k;
		if(k>=h) k = (k-h) % l + h;//找到编号，因为答案 a[] 下标是按照访问顺序来的
		cout<<a[k]<<'\n';
	}
  return 0;
}
```
找循环的过程其实比较复杂，可以结合代码进行理解。大致过程就是先通过二分确定每一个箱子的土豆数量，同时按访问顺序记录每一个箱子的答案。然后记录循环节长度和循环起始点，注意最开始访问的一段前缀可能不属于循环，要特殊处理。

---

## 作者：Tsawke (赞：1)

# [[ABC258E] Packing Potatoes](https://www.luogu.com.cn/problem/AT_abc258_e) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC258E)

## 题面

给定序列 $ W $，下标范围为 $ [0, n - 1] $。存在一个长度为 $ 10^{100} $ 的土豆序列，循环节为 $ n $，第 $ i $ 个土豆的重量为 $ W_{(i - 1) \bmod{n}} $。现在你需要用箱子装土豆，每个箱子装满则停止，即土豆重量恰好大于等于 $ X $ 时则停止。$ Q $ 组询问求第 $ k_i $ 个箱子装了多少个土豆。

## Solution

一道细节不少的找规律题。

首先不难发现，对于这个箱子，当你确定了从哪里开始装后，其最远能装到的位置也就确定了。我们考虑如何确定这个东西，不难想到做个前缀和然后二分，找到对应点开始的最长能取的长度，细节较多，如需要注意若长度仅为一初值需要判断。因为可能转回去所以可以将序列复制一份然后在这上面跑即可。

此时仍需要注意 $ X $ 可能很大以至于横跨多段，此处需要记录。此时我们即有 $ nxt $ 数组表示从该点开始取完土豆之后下一次需要从哪开始取。不难发现每个点有且仅有一条出边，则一定会成环，我们找到从 $ 1 $ 开始多少步后进入环，以及环长和每个位置的元素，最后对于每个询问判断一下是否进入环，未进入则直接调用，进入了则模一下找对应位置。中间细节很多，这道题本身的难度也就在细节上了，具体可以看代码。

复杂度卡在预处理上，最终复杂度 $ O(n \log n) $。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

int N, Q, X;
int W[410000];
ll sum[410000];
int nxt[210000];
ll siz[210000];
ll lftans(0);
bitset < 210000 > vis;
int pos[210000];
int mark[210000];
int pre[210000];

int main(){
    // freopen("in.txt", "r", stdin);
    N = read(), Q = read(), X = read();
    for(int i = 1; i <= N; ++i)sum[i] = sum[i - 1] + (W[i] = read());
    copy(W + 1, W + N + 1, W + N + 1);
    for(int i = N + 1; i <= N << 1; ++i)sum[i] = sum[i - 1] + W[i];
    ll tot = sum[N];
    lftans += ll(X / tot) * N;
    X %= tot;
    if(!X)lftans -= N, X += tot;
    for(int i = 1; i <= N; ++i){
        int l = i, r = N << 1, ans(i - 1);
        while(l <= r){
            int mid = (l + r) >> 1;
            if(sum[mid] - sum[i - 1] < X)ans = mid, l = mid + 1;
            else r = mid - 1;
        }nxt[i] = ans += 2;
        siz[i] = lftans + (nxt[i] - i);
        if(nxt[i] > N)nxt[i] -= N;
    }
    queue < int > path;
    int cur = 1, len = 0;
    while(!vis[cur]){
        path.push(cur);
        vis[cur] = true;
        mark[++len] = cur;
        cur = nxt[cur];
    }int cnt(0);
    while(path.front() != cur)pre[++cnt] = path.front(), path.pop();
    len = 0;
    while(!path.empty())pos[++len] = path.front(), path.pop();
    pos[0] = pos[len];
    while(Q--){
        ll K = read < ll >();
        if(K <= cnt)printf("%lld\n", siz[pre[K]]);
        else printf("%lld\n", siz[pos[(K - cnt) % len]]);
    }
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_12_13 初稿

---

## 作者：Claire0918 (赞：0)

我们注意到从一个位置 $i$ 开始装时，下一次开始装的位置是固定的，而最多只有 $n$ 个位置，在此之后会出现循环。我们只需要对于每一个位置处理出下一次开始装的位置即可。

我们注意到装的过程具有单调性，处理时考虑二分结束位置。

时间复杂度 $\mathcal{O}(n \log n)$。注意在开头可能有一些不进入循环。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 2e5 + 10;

int n, q, x, len;
int a[maxn], vis[maxn];
long long pre[maxn];
vector<int> res;

int main(){
    scanf("%d %d %d", &n, &q, &x);
    for (int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        pre[i] = pre[i - 1] + a[i];
        vis[i] = -1;
    }
    vis[n] = 0;
    for (int pos = 1;;){
        if (pre[n] - pre[pos - 1] >= x){
            const int nex = lower_bound(pre + pos, pre + n + 1, x + pre[pos - 1]) - pre;
            res.push_back(nex - pos + 1);
            if (~vis[nex]){
                len = vis[nex];
                break;
            }
            vis[nex] = res.size();
            pos = nex % n + 1;
        }else{
            const int left = x - pre[n] + pre[pos - 1];
            const int t = left / pre[n], r = lower_bound(pre, pre + n + 1, left - t * pre[n]) - pre;
            res.push_back(n - pos + 1 + t * n + r);
            if (~vis[(r + n + 1) % n - 1]){
                len = vis[(r + n + 1) % n - 1];
                break;
            }
            vis[(r + n + 1) % n - 1] = res.size();
            pos = r + 1;
        }
    }
    while (q--){
        long long k;
        scanf("%lld", &k);
        if (k <= len){
            printf("%lld\n", res[k - 1]);
        }else{
            k -= len;
            k = (k - 1) % (res.size() - len) + len;
            printf("%lld\n", res[k]);
        }
    }

return 0;
}
```

---

## 作者：Lydia1010__ (赞：0)

## 本题思路：
这道题其实就是一个找规律的题目，我们预处理出来从每个数字开始到哪一个数字的和比 $x$ 大，然后处理中间有多少个数字（注意他是环，可以循环着选，处理中间有多少数字是特判一下）。

然后一个一个跳找循环节就可以了。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int sum[2000005],siz[2010005],sl[2000005],vis[2000005],cnt;
int ls[2000005],pd[200005];
signed main(){
	int n,q,x;
	cin>>n>>q>>x;
	for(int i=1;i<=n;i++){cin>>sum[i];sum[i]+=sum[i-1];}
	for(int i=1;i<=n;i++){
		int num=sum[n]-sum[i-1];
		if(num>=x){
			int l=i,r=n,k=i;
			while(l<=r){
				int mid=(l+r)/2;
				if(sum[mid]-sum[i-1]<x)l=mid+1,k=mid;
				else r=mid-1;
			}
			if(sum[k]-sum[i-1]<x) k++;
			siz[i]=k+1;sl[i]=k-i+1;
			if(k==n) siz[i]=1;
		}
		else{
			sl[i]=n-i+1;
			int op=x;op=op-(sum[n]-sum[i-1]);
			sl[i]=(sl[i]+n*(op/sum[n]));
			op=op%sum[n];
			int l=1,r=n,k=n;
			while(l<=r){
				int mid=(l+r)/2;
				if(sum[mid]>=op) r=mid-1,k=mid;
				else l=mid+1;
			}
			if(k==1 && op==0) k=0;
			siz[i]=k%n+1;
			sl[i]+=k;
		}
//		cout<<siz[i]<<" "<<sl[i]<<endl;
	}
	int xh=0;
	for(int i=1;;i=siz[i]){
		if(vis[i]){xh=vis[i];break;}
		vis[i]=++cnt;
		pd[cnt]=i;
	}
	while(q--){
		int x;
		cin>>x;
		if(x<=cnt)cout<<sl[pd[x]]<<endl;
		else{
			x=x-(xh-1);
			int ans=0;
			int op=x%(cnt-xh+1);
			if(op==0) op=cnt-xh+1;
			cout<<sl[pd[xh-1+op]]<<endl;
		}
	}
	return 0;
}
```

---

## 作者：xukehg (赞：0)

简单题。

定义 $f_{i,j}$ 为从第 $i$ 个位置开始放 $2 ^ j$ 个箱子后，下一个箱子开始放的位置。$f_{i,0}$ 的计算是平凡的，简单二分即可。套路的倍增得 $f_{i,j} = f_{f_{i,j-1},j-1}$。对于每个 $k_i$ 求出从 $1$ 开始放 $k_i - 1$ 个箱子最终的位置并二分即可。

---

