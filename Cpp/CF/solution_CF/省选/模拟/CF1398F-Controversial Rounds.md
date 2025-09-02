# Controversial Rounds

## 题目描述

Alice和Bob在玩游戏。整个游戏过程包含若干**组**游戏。每一**组**游戏会进行若干**轮**。在每一**轮**游戏中，要么Alice赢要么Bob赢。一**组**游戏结束，当且仅当Alice和Bob中的`1`个人在这一**组**游戏中赢了**连续**的`x`**轮**。

你现在知道，Alice和Bob一共进行了`n`**轮**游戏，并且知道其中若干**轮**游戏的结果。

对于每一个`x`（`x`的定义在上文，且`1<=x<=n`），要求你计算出Alice和Bob能进行的游戏**组**数的最大值。如果在一种方案中，最后一**组**游戏并不能刚好结束，那么这组游戏不计入该方案。

## 样例 #1

### 输入

```
6
11?000```

### 输出

```
6 3 2 1 0 0```

## 样例 #2

### 输入

```
5
01?01```

### 输出

```
5 1 0 0 0```

## 样例 #3

### 输入

```
12
???1??????1?```

### 输出

```
12 6 4 3 2 2 1 1 1 1 1 1```

# 题解

## 作者：klii (赞：12)

 [$\texttt{link}$](https://www.luogu.com.cn/problem/CF1398F)
 
 一种题解区没有的并查集写法（（
 
 记全是 $'0'$ 或 全是 $'1'$ 的字符串为**合法串**。
 
 首先对于每个 $i\in[1,n]$，预处理出以 $i$ 为起点的**可能的最长合法串**，长度记作 $len_i$，这个可以双指针解决。
 
 然后从小到大枚举 $x=i$，考虑维护一个并查集，若当前 $fa_i=i$ 则表示以 $i$ 为起点存在一个可能的长度至少为 $x$ 的合法串，否则 $fa_i$ 指向下一个合法的位置（若没有则设为 $n+1$）。
 
 当 $x=i$ 时答案的上界为 $n/x$，则总答案的上界为 $\sum\limits_{i=1}^n\dfrac n i = n\ln n$ 的。
 
 由此我们可以考虑每次利用 $fa$ 数组每次都从头开始暴力跳，总次数是 $\mathrm{O(n\ln n)}$ 的，可以通过。
 
 然后考虑维护 $x\longrightarrow x+1$ 时 $fa$ 数组的变化，只需要将预处理出的 $len_i = x$ 的 $fa_i$ 设为 $i+1$ 即可。
 
 总时间复杂度 $\mathrm{O(n\ln n + n\log n)}$ 。
 
 $\texttt{Code:}$
 ```cpp
 #include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
char s[maxn];
int n, sum0[maxn], sum1[maxn], fa[maxn], len[maxn], num[maxn];
bool chk(int l, int r) {return (sum1[r] - sum1[l - 1] == 0) || (sum0[r] - sum0[l - 1] == 0);}
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
bool cmp(int a, int b) {return len[a] < len[b];}
int main() {
    scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; i++) sum1[i] = sum1[i - 1] + (s[i] == '1');
    for (int i = 1; i <= n; i++) sum0[i] = sum0[i - 1] + (s[i] == '0');
    for (int i = 1; i <= n; i++) {
        len[i] = max(0, len[i - 1] - 1);
        while (i + len[i] <= n && chk(i, i + len[i])) len[i]++;
    }
    for (int i = 1; i <= n; i++) num[i] = fa[i] = i;
    fa[n + 1] = n + 1;
    sort(num + 1, num + n + 1, cmp);
    int p = 1;
    for (int i = 1; i <= n; i++) {
        while (p <= n && len[num[p]] < i) fa[num[p]] = num[p] + 1, p++;
        int ans = 0, cur = 1;
        while (1) {
            cur = find(cur);
            if (cur == n + 1) break;
            ans++; cur += i;
        }
        printf("%d ", ans);
    }
    return 0;
}
 ```

---

## 作者：ctq1999 (赞：9)

## 题面简述

给你一串 `01` 或 `?` 组成的字符串，询问对于每个 $len$ （$1\leq len \leq n$），若有连续 $len$ 个相同的字符组成的子字符串，那么就从中删去，问最多可以删多少次。

`?` 表示这个可以认为是 `0`，也可以认为是 `1`。

## 思路

*参考了 Codeforces 上代码长度最短的代码。*

考虑时间复杂度，发现若对于每一个 $len$，遍历字符串 $s$ 时的下标 $pos$ 每次加 $len$，那么总时间复杂度是 $O(n\ln n)$，可以通过本题。

那么就是模拟每个 $len$ 的情况了。可以发现，对于一串连续相同的子串，尽可能地多取是最优的。那么会出现剩余小于 $len$ 的，没法再取的情况了。这时下标 $pos$ 要跳到下一个连续相同的子串的开头位置的下标。

那么我们现在需要判断当前子串中是否还能取，和不能取的情况下，如何记录下一个连续相同的子串的开头位置的下标。

先讲后者如何记录。一个子串的开头的位置的下标，一定是从其开头的值转移过来的。

定义 $pre_{i,j}$ 的值为包含第 $i$ 位为 $j$ 的子串的开头的位置的下标。我们可以这样转移（当前的数字为 $c$，$0\leq i < n$）：

- 现在把 $pre_{i,0}$ 和 $pre_{i,1}$ 转移到 $pre_{i+1,0}$ 和 $pre_{i+1,1}$。

- 若 $s_i \neq$ `?`，把 $pre_{i+1,c\oplus 1}$ 的值赋为 $i+1$

为何这样转移待会解释。先看怎么遍历时如何判可以取，和不能取的情况。

若子串相同的字符为 `0`，那么 $pre_{pos,0}$ 的值一定和 $pre_{pos+len,0}$ 的值相等，因为转移时没改变前面的值。而此时 $pre_{pos,1}$ 和 $pre_{pos+len,1}$ 的值相差 $len$。因为转移中，相反的字符的 $pre$ 的值会不与上一个对应的 $pre$ 相等。$pos$ 加上 $len$。

对于不能取的情况，$pos$ 要到 $pre_{pos,c}$ 中，其中 $c$ 的值为 $0$ 或 $1$。至于 $c$ 如何取值，留给读者思考。不会的可以评论 $@$ 我。/kk

## 代码

```cpp
#include<bits/stdc++.h>

#define ll long long
#define y1 caibictq
#define P pair<int, int>
#define fi first
#define se second

using namespace std;

const int MAXN = 2000010;
const int MAXM = 100010;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;

int n, m, k;
int tot, cnt, ans;

int pre[MAXN][2];

string s;

int main() {
	int T;
	scanf("%d", &n);
	cin >> s;
	for (int i = 0; i < n; i++) {
		pre[i + 1][0] = pre[i][0];
		pre[i + 1][1] = pre[i][1];
		if (s[i] == '?') continue;
		pre[i + 1][s[i] & 1 ^ 1] = i + 1;
	}
	for (int len = 1; len <= n; len++) {
		int pos = 0; ans = 0;
		while (pos + len <= n)
			if (pre[pos + len][0] == pre[pos][0] || pre[pos + len][1] == pre[pos][1]) pos += len, ++ans;
			else pos = pre[pos + len][pre[pos + len][1] < pre[pos + len][0]];
		printf("%d ", ans);
	}
	return 0;
}

```




---

## 作者：cunzai_zsy0531 (赞：3)

### CF1398F 题解

by cunzai_zsy0531

[题面](https://www.luogu.com.cn/problem/CF1398F)

---

贡献一个官方题解做法的详细解释。

首先注意到一个贪心的思路，从前往后如果能够使某一段长度 $=x$ 就一定会使其 $= x$ 或 $\geq x$。

考虑设一个函数 $f(pos,x)=npos$ 表示当限制长度为 $x$ 时，从 $pos$ 这个位置开始往后，第一个能够出现连续 $x$ 个 `0` 或 `1` 的位置为 $npos-1$。如果能够 $O(1)$ 求出这个函数的值，那么每一次都令 $pos=npos$ 继续往下做，由于每一次至少会加 $x$，所以这样的复杂度就是 $O(n\ln n)$。

如何求这个函数的值呢？再考虑设两个数组 $nxt0_i,nxt1_i$ 分别表示从 $i$ 开始的最长 `0` 段和 `1` 段的长度。这个可以倒序递推求得。再设 $p0_x$ 存下所有的下标 $i$ 满足 $i$ 开始往后有连续的 $x$ 个 `0`，且 $i=1$（开头）或者 $s_{i-1}=1$，$p1_x$ 同理。

考虑对于某个 $x$，从 $1$ 开始走，设当前走到 $now$，如果 $nxt0_{now}\geq x$，则 $npos=now+x$；否则就找到 $p0_x$ 中 $\geq now$ 的最小的位置（使用双指针实现），设其为 $tmp$，则 $npos=tmp+x$。对 $nxt1$ 和 $p1$ 的处理同理，这样就能做到最开始的 $O(1)$ 求得 $f(pos,x)$，所以总复杂度是 $O(n\ln n)$。

本人代码过于冗长，就不贴 code 了，[CF官方题解](https://codeforces.com/blog/entry/81506)上的代码写的比我要好。

---

## 作者：fade_away (赞：2)

~~**这是一篇提交四次都没过审的思博题解。**~~

~~**它不配出现在题解区，只配在这个犄角旮旯之处吃灰。**~~

还是过审比较香。

## Solution

我又来贡献暴力做法了。。。~~听说两只 log 不可能过 1e6 ?~~

有一个显然的想法是：

我们先预处理一个 $a_i$ 表示第 $i$ 个位置的最长后缀长度，满足该后缀中不同时存在 0 和 1 。

假设我们要求 $x=i$ 的答案，那么一个位置 $j$ 可以作为一轮的结束点当且仅当 $a_j\geq i$ ，而一个结束位置序列 $p_1<p_2<...<p_k$ 合法当且仅当每一个 $p_j$ 都是合法结束点并且相邻两个元素的差至少为$i$（保证不重合）。

因此我们会贪心地从第一个满足 $a_j\geq i$ 的 $j$ 开始，每次找一个最小的 $j'$ ，满足 $j'\geq j+i$ 且 $a_{j'}\geq i$ ，然后从 $j$ 跳到 $j'$ ，最终的答案就是跳的步数。

这显然可以直接对 $a_i$ 建区间线段树，维护区间内的 $max$ ，线段树上二分求出 $j'$ 。

这个方法的时间复杂度为 $O(\sum ans_i\;\log n)$ ，而 $ans_i\leq \lfloor\frac{n}{i}\rfloor$ ，因此总时间复杂度 $O(n\ln n\log n)$ ，注意常数即可。

（PS：别用偷懒用 set 维护，常数起飞，实测接近线段树的三倍）。


## Update 4.5 23:30

上面的代码跑了 $1890ms$ ，我们觉得它不够优秀，于是冷静分析一下它慢在哪里，发现全 1 的数据就可以把它卡满，这是为什么呢？这是因为我们在长长的没有 0 的段里面做了很多次 query ，这其实是不必要的，我们同样可以预处理以每个位置开始的最长段。这样就可以 $O(1)$ 计算整个段的贡献。

我们提交后发现它只跑了 $249ms$ ！

理性分析一下它的时间复杂度，相当于整个序列被01分割为若干段，跳到一个段就可以 $O(1)$ 计算答案并且 $O(\log n)$ 跳到下一个段，这样每一段会有 $O(len)$ 次贡献（因为每一个长度大于 $i$ 的段才可能产生贡献），每次贡献为 $O(\log n)$ ，因此总时间复杂度为 $O(n\log n)$ ！

## Updated code
```cpp
void build(int x, int l, int r) {
	if (l == r) { mx[x] = a[l]; return; }
	int mid = (l + r) >> 1;
	build(x << 1, l, mid);
	build(x << 1 | 1, mid + 1, r);
	mx[x] = max(mx[x << 1], mx[x << 1 | 1]);
}
int query(int x, int l, int r, int L, int y) {
	if (mx[x] < y) return -1;
	if (l == r) return l;
	int mid = (l + r) >> 1;
	if (L > mid) return query(x << 1 | 1, mid + 1, r, L, y);
	else {
		int t = query(x << 1, l, mid, L, y);
		if (t != -1) return t;
		return query(x << 1 | 1, mid + 1, r, mid + 1, y);
	}
}
signed main() {
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
#endif
	int n, cnt0 = 0, cnt1 = 0;
	read(n), reads(st);
	for (int i = 1, l = 1; i <= n ; ++ i) {
		auto add = [&](char x, int y) {
			if (x == '0') cnt0 += y; 
			if (x == '1') cnt1 += y;
		};
		add(st[i], 1);
		while (cnt0 && cnt1) add(st[l ++], -1);
		a[i] = i - l + 1;
	}
	cnt0 = 0, cnt1 = 0;
	for (int i = n, r = n; i >= 1 ; -- i) {
		auto add = [&](char x, int y) {
			if (x == '0') cnt0 += y; 
			if (x == '1') cnt1 += y;
		};
		add(st[i], 1);
		while (cnt0 && cnt1) add(st[r --], -1);
		b[i] = r - i;
	}
	build(1, 1, n);
	for (int i = 1; i <= n ; ++ i) {
		int cnt = 0, r = 1;
		for (; r <= n ;) {
			r = query(1, 1, n, r, i);
			if (r == -1) break;
			int p = b[r] / i;
			cnt += p + 1, r += i * (p + 1);
		}
		print(cnt), putc(' ');
	}
	return 0;
}

```


---

## 作者：demon_yao (赞：2)

### 题意
- 给定一串$01$串,其中有一些$?$可以任意变换为$0$或$1$。,给定一些$len$,若有连续$len$个相同的字符组成的子字符串，那么就删去，问最多可以删多少次。

### 思路
- 我们记$pre[i][j]$为第$i$个字符为$j$($j=0$或$1$)的开头位置的下标。我们可以考虑如何转移$pre$;仔细一想，我们可以得到$pre[i+1][0]=pre[i][0]$;$pre[i+1][1]=pre[i][1]$;$pre[i+1][s[i]_{opposite}]=i+1;$

- 得到了$pre$之后，我们就可以开始愉快的计算了！遍历整个数组，如果发现连续$len$个数相等，那么就$ans++$,并且把$pos+=len$。如果不相等，那么我们就跳到$pos=pre[pos+len][pre[pos+len][1]<pre[pos+len][0]]$。如此遍历，这样就可以计算出答案了。

- PS:思路借鉴了$ctq1999$大佬的，$code$很简洁，应该能明白叭qwq!

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int N=1e7+5;int n,pre[N][2];
string s;
int main(){
	cin>>n;cin>>s;
	for (int i=0;i<n;i++){
		pre[i+1][0]=pre[i][0];pre[i+1][1]=pre[i][1];
		if (s[i]=='?') continue;
		pre[i+1][s[i]&1^1]=i+1;
	}
	for (int len=1;len<=n;len++) {int pos=0,ans=0;
		while(pos+len<=n)
			if (pre[pos+len][0]==pre[pos][0] || pre[pos+len][1]==pre[pos][1]) pos+=len,++ans;
			else pos=pre[pos+len][pre[pos+len][1]<pre[pos+len][0]];
		printf("%d ",ans);
	}	
	return 0;
}

```


---

## 作者：Liang_9 (赞：1)

## 题意分析
给定一个由 $0$ 或 $1$ 或 ? 构成的字符串，对于 $1$ 到 $n$ 每一个数，求出最多有多少个长度为 $x$ 的连续段。

## 做法详解
对于寻找最大的连续段数，可以先将整个数组强制划分成若干个由 $1$ 或 $0$ 开始的最长可连续段（将 ? 与前一段 $0$ 或 $1$ 划分在一起）。  

$pret_i$：记录 $i$ 当前所处段的开头。  
$a_i$：记录由 $i$ 开头的段的最大长度。  
$b_i$：记录由 $i$ 开头的段，末尾最长连续 $?$ 段的长度。

对于一个连续段的答案构成，分为两部分：上一段没用完的?和这一段拼在一起。  
一个长度为 $l$ 的段对于 $x$ 答案的贡献是 $\lceil \frac{l}{x} \rceil $。  
若对于当前 $x$ 的答案为 $0$,那么比 $x$ 更大的答案也一定是 $0$，就可以直接跳过了。

## 代码详解
```
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n;
char s[N];
int a[N],b[N],pret[N];

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>s[i];
        //输入，初始化
        if(i==1)
        {
            pret[i]=i,a[i]=1;
            if(s[i]=='?') b[i]=1;
            continue;
        }
        if(s[i-1]==s[i]) {
            pret[i]=pret[i-1],a[pret[i]]++;
            if(s[i]=='?') b[pret[i]]++;
        }else if(s[i-1]=='?')
        {
            if(s[pret[i-1]]==s[i]) pret[i]=pret[i-1],a[pret[i]]++,b[pret[i]]=0;
            else pret[i]=i,a[i]=1;
        }else if(s[i]=='?')
        {
            pret[i]=pret[i-1],a[pret[i]]++,b[pret[i]]=1;
        }else {
            pret[i]=i,a[i]=1;
        }
    }
    
    
    bool flag=0;
    for(int i=1;i<=n;i++)//枚举长度
    {
        if(flag) {
            //直接跳过
            cout<<0<<' ';
            continue;
        }
        int numw=0,l=1,len=0,ans=0;
        //numw存上一段剩下的?
        while(l<=n)
        {
            len=a[l]+numw;
            ans+=len/i;//答案
            len=len%i;
            numw=min(b[l],len);//剩下的
            l=l+a[l];//跳到下一段
        }
        cout<<ans<<' ';
        if(ans==0) flag=1;
    }
}
```

---

## 作者：bsdsdb (赞：1)

题意：字符串 $s$，$\Sigma=\{0,1,?\}$，对于一个 $k$ 和位置 $x$，如果有可能 $s_{[x,x+k)}$ 全相同，那么 $x$ 就「跳」到 $x+k$，否则就「走」到 $x+1$，$x>n$ 时停止。问对于每个 $k\in[1,n]$，$x$ 从 $1$ 开始能跳几次。

预处理离每个位置最近的 $0$ 和 $1$，记作 $\gdef\nxt{\mathrm{nxt}}\mathrm{nxt} _{0/1}$。如果 $\max(\nxt_{0,i},\nxt_{1,i})<i+k$，那么 $i$ 一定是要走的，走到 $\min(\nxt_{0,i},\nxt_{1,i})+1$。如果 $k=y$ 的时候在 $i$ 这里一直走，走到了 $j$，那么显然 $k=y+1$ 的时候到了 $i$ 也要至少走到 $j$，路径压缩。复杂度 $\Omicron(\sum\gdef\ans{\mathrm{ans}}\ans)=\Omicron(n\log n)$，极限情况为全问号。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pq priority_queue
#define emp emplace

string s;
ll n, a[1000005], n0[1000005], n1[1000005], K, ans = 0, nxt[1000005], cnt;

ll ijustwannajump(ll x) {
	++cnt;
	if (x + K - 1 > n) return n + 1;
	ll r = x + K - 1;
	if (n0[x] <= r && n1[x] <= r) {
		nxt[x] = max(nxt[x], min(n0[x], n1[x]) + 1);
		return nxt[x] = ijustwannajump(nxt[x]);
	}
	if (nxt[x]) {
		return ijustwannajump(nxt[x]);
	}
	++ans;
	ll next = r + 1;
	ijustwannajump(next);
	return x;
}

int main() {
	cin >> n >> s;
	for (ll i = 1; i <= n; ++i) a[i] = (s[i - 1] == '?' ? -1 : (s[i - 1] - 48));
	n0[n + 1] = n1[n + 1] = n + 1;
	for (ll i = n; i; --i) {
		if (a[i] == 1) n1[i] = i; else n1[i] = n1[i + 1];
		if (a[i] == 0) n0[i] = i; else n0[i] = n0[i + 1];
	}
	cout << n << ' ';
	for (K = 2; K <= n; ++K) {
		ll one = 1;
		ans = 0;
		ijustwannajump(one);
		cout << ans << ' ';
	}
	cout << endl;
	cerr << cnt << endl;
	return 0;
}
```

看到犇犇里面有人说这题不是 1500\*，评价是：

> 什么事情都要找找自己问题。——小明剑魔
>
> 要断章取义。——《不要断章取义》

---

## 作者：TernaryTree (赞：1)

简单贪。鉴定为 1500。

对于一个 $x$，我们显然从 $1$ 开始走，如果后面能走连续相同的 $x$ 个就走，走不了就跳到下一个能走的地方。这个贪心正确性显然。

于是我们预处理出 $c_i$ 表示从 $i$ 开始，只走相同的，最长能走多远。发现存在形如 `1?0` 这样的结构，不太好转移，所以改记 $b_{i,0/1}$ 表示从 $i$ 开始，只走 $0/1$，最长能走多远。这样就好做了，我们有 $c_i=\max(b_{i,0},b_{i,1})$。转移是这样的：

```cpp
for (int i = n; i >= 1; i--) {
	if (~a[i]) b[i][a[i]] = b[i + 1][a[i]] + 1, b[i][!a[i]] = 0;
	else b[i][0] = b[i + 1][0] + 1, b[i][1] = b[i + 1][1] + 1;
	c[i] = max(b[i][0], b[i][1]);
}
```

然后可以想到，上面那个贪心暴力做是完全可行的，因为我们有 $\Theta(\sum\limits_{i=1}^n \dfrac{n}i)=\Theta(n\log n)$。唯一需要做的就是快速找到下一个符合条件（即 $c_i\ge x$）的位置。

此时去观察 $x\to x+1$ 时，这些“下一个位置”会发生什么变化。那些 $c_i=x$ 的位置被舍弃掉了，相当于本来这个点指向自己，后来被迫指向别人了。这可以看做一个连边关系。于是用并查集维护之即可。

```cpp
for (int x = 1; x <= n; x++) {
	int i = 1, k = 0;
	while (i <= n) {
		if (find(i) == n + 1) break;
		i = find(i) + x;
		++k;
	}
	cout << k << " ";
	for (int j : p[x]) nxt[j] = find(j + 1);
}
```

---

## 作者：LJ07 (赞：1)

很容易将题意转化为对于 $k\in[1, n]$，求出能选出最多的互不相交的长度为 $k$ 连续段个数。

观察了一会发现有一个隐藏的调和级数，所以我们可以直接模拟只要保证复杂度基于答案即可。因为答案最坏为 $O(n\ln n)$ 级别。

考虑给出一个 $k$ 咋做，发现贪心是对的。也就是从前往后能凑成 $k$ 连续段的尽可能凑，这样一定是不劣的。

考虑如何优化这一过程，假设当前位置是 $p$：
1. 如果 $s_{p\cdots p+k-1}$ 最多存在 ```0``` 和 ```1``` 两个字符中的一个，那么当前可以是一个 $k$ 连续段。
1. 否则尝试找到下一个能够找到一个长度为 $k$ 的连续段的段，这样的段应该形如 ： ```1[???000?]1``` 这种。

这样的段是能够预处理并且快速查找的。这样的段应该是什么样的：段前 $1$ 个和段后 $1$ 个字符相同（并且不能是 ```?```）并且中间不存在和他们相同的字符。预处理直接 $O(n)$ 扫。

那么只要段长 $\ge k$ 就是合法的段。查找如果暴力二分查找是 $O(\log n)$，复杂度为 $O(n\ln n\log n)$，非常糟糕。

但是我们可以单指针扫一遍：只要每次都只扫长度合法的段，这样复杂度也是对的，原因也是调和级数。

最后我们就可以 $O(n\log n+n\ln n)$ 解决此题。

[code](https://www.luogu.com.cn/paste/rx99i67f)

---

## 作者：intel_core (赞：1)

我们先考虑如何求 $x=k$ 时的答案：

贪心的，如果当前数往后数 $k$ 个能做到全都一样，那么答案 $+1$，位置 $+k$；否则位置 $+1$。

来证一下为什么这个贪心是对的：

* 首先，如果 $s'$ 是 $s$ 的前缀或者后缀，那么 $s'$ 上的答案不大于 $s$ 上的。

* 如果连续一段数都可以变成 `1`（`0` 同理），设这段区间是 $[l,r]$，那么 $a_{l-1}$ 和 $a_{r+1}$ 都必然是 `0` 。在 $[l,r]$ 内选定的区间越靠前，那么剩下的数就越多，那么答案必然不会更小，而且 $l-1,r+1$ 也不会对 $[l,r]$ 贡献产生影响。

如果要跑 $n$ 次的话，还是太慢了。

刚才的贪心我们浪费了大量时间寻找下一个连续 $k$ 个能做到相同的位置，现在我们考虑优化这个过程。

一个比较无脑的做法是先处理出一个点最多能往后延伸多少，记为 $d_i$，初始的时候把所有数扔进一个 `STL::set` 里，在枚举到 $d_{i+1}$ 的时候找出 $i$ 在 `set` 中的前驱 $s$ 和后继 $t$，然后把 $[s+1,i]$ 区间覆盖为 $t$。

单次查询是 $O(\log n)$ 的，外层查询 $O(n \sum\limits_{i\le n} \frac{1}{i})=O(n \ln n)$ 次，所以复杂度 $O(n \log n \ln n)$，不太好卡。

观察到如果 $s_i$ 与 $s_{i+1}$ 不相反的话，那么 $d_i \ge d_{i+1}$；即若 $d_i \ge 2$，有 $d_i \ge d_{i+1}$。

所以在刚才这种方法修改 $i$ 时，如果 $d_i \not\equiv 1$，那么 $d_{i+1}$ 已经从 `set` 里删掉了。

这启示我们用并查集维护，求到 $d_i+1$ 时把 $d_i$ 在并查集上指向 $i+1$ 即可。

每次查询的时候一次 `get` 就可以。

复杂度 $O(n \ln n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e6+10;
int n,m,suf[NR],fa[NR];
char s[NR];
vector<int>v[NR];
#define pb push_back 

void init(){
	for(int i=1;i<=n+1;i++)fa[i]=i;
}
int get(int x){
	if(fa[x]==x)return x;
	return fa[x]=get(fa[x]);
}

int main(){
	cin>>n;init();
	scanf(" %s",s+1);
	int x=0,y=0,now=n;
	for(int i=n;i>=1;i--){
		if(s[i]=='0')x++;
		if(s[i]=='1')y++;
		while(x&&y){
			if(s[now]=='0')x--;
			if(s[now]=='1')y--;
			now--;
		}
		v[suf[i]=now-i+1].pb(i);
	}
	for(int i=1;i<=n;i++){
		for(int x:v[i-1])fa[x]=x+1;
		int pos=1,res=0;
		while(1){
			pos=get(pos);
			if(pos>n)break;
			res++;pos+=i;
		}
		printf("%d ",res);
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

考虑一个暴力，记录从这个位置最长延伸多远，那么对于每个 $x=i$，我们可以从 $1$ 开始暴力往后走，如果最长延伸大于等于 $i$ 就将位置加上 $i$，并将答案加 $1$，否则向后移动 $1$。这样做是 $O(n^2)$ 的。

考虑优化，$n\leq10^6$ 的数据范围很容易让人想到小常数 $n\log^2n$。我们会发现最长延伸大于等于 $i$ 的时候每次会跳至少 $i$ 步，这是好的，因为答案显然不超过 $\sum_{i=1}^n\frac{n}{i}=O(n\ln n)$。那么困难点就变成如何找下一个满足最长延伸大于等于 $x$ 的位置。从大到小枚举，用一棵线段树维护每个点下一个满足要求的位置即可。总复杂度 $O(n\log^2n)$。有一个很简单的常数优化就是设最长延伸为 $p$，那么一次性跳 $\lfloor\frac{p}{i}\rfloor$ 步。

```cpp
#pragma GCC optimize("Ofast","inline")
#include <bits/stdc++.h>
#define min(i,j) ((i<j)?i:j)
#define mid ((l+r)>>1)
#define add(i,j) ((i+j>=mod)?i+j-mod:i+j)
using namespace std;
struct sgt{
	int f[4000005];
	void pushdown(int i){
		f[i*2]=min(f[i*2],f[i]);
		f[i*2+1]=min(f[i*2+1],f[i]);
	}
	void change(int i,int l,int r,int ql,int qr,int cg){
		if(ql<=l&&r<=qr){
			f[i]=min(f[i],cg);
			return ;
		}
		pushdown(i);
		if(ql<=mid) change(i*2,l,mid,ql,qr,cg);
		if(qr>mid) change(i*2+1,mid+1,r,ql,qr,cg);
	}
	int qry(int i,int l,int r,int pos){
		if(l==r) return f[i];
		pushdown(i);
		if(pos<=mid) return qry(i*2,l,mid,pos);
		else return qry(i*2+1,mid+1,r,pos);
	}
}tree;
char c[1000005];
int ext[1000005],ans[1000005];
vector<int> vc[1000005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	memset(tree.f,1,sizeof(tree.f));
	int n; cin>>n;
	for(int i=1;i<=n;i++) cin>>c[i];
	int lst0=n+1,lst1=n+1;
	for(int i=n;i>=1;i--){
		if(c[i]=='0') lst0=i;
		if(c[i]=='1') lst1=i;
		ext[i]=max(lst0,lst1)-i;
	}
	for(int i=1;i<=n;i++) vc[ext[i]].push_back(i);
	for(int i=n;i>=1;i--){
		for(auto v:vc[i]) tree.change(1,1,n,1,v,v);
		int now=tree.qry(1,1,n,1);
		while(now<=n){
			ans[i]+=ext[now]/i;
			now+=i*(ext[now]/i);
			if(now>n) break;
			now=tree.qry(1,1,n,now);
		}
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	return 0;
}
```

---

