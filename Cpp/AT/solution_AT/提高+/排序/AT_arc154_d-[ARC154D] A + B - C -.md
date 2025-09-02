# [ARC154D] A + B > C ?

## 题目描述

PCT 君有一个 $ (1,2,\dots,N) $ 的排列 $ (P_1,P_2,\dots,P_N) $。你只知道 $ N $ 的值。

你可以向 PCT 君最多询问 $ 25000 $ 次以下的问题：

- 指定满足 $ 1\le i,j,k\le N $ 的整数三元组 $ (i,j,k) $，询问 $ P_i+P_j>P_k $ 是否成立。

请你求出 $ P_1,P_2,\dots,P_N $ 的全部值。

## 说明/提示

## 限制

- $ 1\le N\le 2000 $
- $ P $ 在程序与评测程序开始交互前已确定。

## 评测说明

- **每次输出后请务必刷新输出缓冲区，否则可能会因 TLE 被判为不正确。**
- 输出答案（或收到 `-1`）后请立即正常退出程序，否则评测结果不确定。
- 多余的换行会被视为输出格式错误。

## 输入输出样例

以下为 $ N=4,P=(3,1,2,4) $ 时的交互示例。

| 输入 | 输出 | 说明 |
|:---:|:---:|:---|
| `4` |     | $ N $ 被给出。 |
|     | `? 1 2 3` | 第 1 次提问，询问 $ P_1+P_2>P_3 $ 是否成立。 |
| `Yes` |     | $ P_1+P_2=4,P_3=2 $，因此返回 `Yes`。 |
|     | `? 2 3 3` | 第 2 次提问，询问 $ P_2+P_3>P_3 $ 是否成立。 |
| `Yes` |     | $ P_2+P_3=3,P_3=2 $，因此返回 `Yes`。 |
|     | `? 2 3 4` | 第 3 次提问，询问 $ P_2+P_3>P_4 $ 是否成立。 |
| `No` |     | $ P_2+P_3=3,P_4=4 $，因此返回 `No`。 |
|     | `! 3 1 2 4` | 输出 $ P_1,P_2,P_3,P_4 $。实际排列为 $ (3,1,2,4) $，因此 AC。 |

由 ChatGPT 4.1 翻译

# 题解

## 作者：rui_er (赞：8)

显然 $1+1>x$ 对任意大于 $1$ 的正整数 $x$ 都不成立。利用这一点，我们可以在 $n-1$ 次询问内问出 $1$ 的位置。具体地，首先假设 $p_1$ 为 $1$，记我们假设的为 $1$ 位置为 $k$。依次枚举 $2\sim n$ 的每个数 $x$，问 $p_k+p_k>p_x$ 是否成立。若成立，意味着 $p_k>1$，令 $k\gets x$ 然后继续循环；若不成立，意味着 $p_x>1$，继续循环。循环结束后，$p_k=1$ 一定成立。

注意到 $p_i+1>p_j\iff p_i\ge p_j$，我们有了比较操作，只需对 $p$ 进行排序即可。可以手写归并排序，但更方便的方法是写一个比较函数传进 `stable_sort` 里面。注意这里用 `sort` 可能会被卡，原因是 `sort` 递归到 $n$ 小后就会使用插入排序，导致比较次数超限（次数限制比较紧）。

```cpp
// Problem: D - A + B > C ?
// Contest: AtCoder - AtCoder Regular Contest 154
// URL: https://atcoder.jp/contests/arc154/tasks/arc154_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const int N = 2e3+5;

int n, a[N], p[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
int ask(int x, int y, int z) {
	printf("? %d %d %d\n", x, y, z);
	fflush(stdout);
	char s[4];
	scanf("%s", s);
	return s[0] == 'Y';
}
void give(int* p, int n) {
	printf("! ");
	rep(i, 1, n) printf("%d%c", p[i], " \n"[i==n]);
	fflush(stdout);
}

int main() {
	scanf("%d", &n);
	int pos1 = 1;
	rep(i, 2, n) if(ask(pos1, pos1, i)) pos1 = i;
	rep(i, 1, n) a[i] = i;
	stable_sort(a+1, a+1+n, [=](int i, int j) {
		return !ask(i, pos1, j);
	});
	rep(i, 1, n) p[a[i]] = i;
	give(p, n);
	// system("pause");
	return 0;
}
```

---

## 作者：Register_int (赞：2)

~~会 D 不会 C 什么概念~~

如果可以求出 $1$，那么我们就可以通过查询 $a+1>b$ 来获取 $a,b$ 的大小关系了。可以进行归并排序后输出，操作次数 $n\times\left\lfloor\log_2 n\right\rfloor=22000$ 次。

考虑如何找到 $1$。思考如下一个柿子：$i+i>j$。显然，当 $i=1$ 时，该询问返回结果不可能为真，因为 $j$ 最小为 $2$，而 $1+1\le2$。当 $j=1$ 时，$i$ 最小为 $2$，而 $2+2>1$，所以返回结果不可能为假。因此，可以得出如下算法：

1. $p\rightarrow1$，$j\rightarrow2$
2. 如果 $p+p>j$，则 $p\rightarrow j$。
3. $j\rightarrow j+1$
4. 重复 $2\sim 3$ 操作直到 $j>n$。

总次数为 $n-1=1999$ 次，总操作次数为 $23999$ 次，符合要求。

# AC 代码

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int MAXN = 2e3 + 10;
 
char s[5];
 
inline 
bool query(int i, int j, int k) {
	cout << "? " << i << ' ' << j << ' ' << k << endl, scanf("%s", s);
	return *s == 'Y';
}
 
int n, p, a[MAXN], b[MAXN]; bool vis[MAXN];
 
void merge(int l, int r){
	if (l == r) return ;
	int mid = l + r >> 1; merge(l, mid), merge(mid + 1, r);
	int i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r) b[k++] = query(p, a[i], a[j]) ? a[j++] : a[i++];
	while (i <= mid) b[k++] = a[i++]; while (j <= r) b[k++] = a[j++];
	for(int i = l; i <= r; i++) a[i] = b[i];
}
 
int main() {
	scanf("%d", &n), p = 1;
	for (int i = 2; i <= n; i++) query(p, p, i) && (p = i);
	for (int i = 1; i <= n; i++) a[i] = i; merge(1, n);
	for (int i = 1; i <= n; i++) b[a[i]] = i; cout << '!';
	for (int i = 1; i <= n; i++) cout << ' ' << b[i]; cout << endl;
}
```

---

## 作者：tZEROちゃん (赞：2)

好玩的交互题。

> 给定一个 $(1, 2, \dots, N)$ 的排列 $P$，给定 $N$。
>
> 你可以询问 $25000$ 次，每次询问一个三元组 $(i, j, k)$ 是否满足 $P_i + P_j = P_k$。
> 
> 求 $P$。

首先我们先找到一个数 $x$，使 $P_x=1$。这个可以用 $N-1$ 次询问得出：

- 每次询问 $(i, i, x)$，若答案是 `No`，那么令 $x = i$。

此时最终的 $x$ 就满足 $P_x=1$。

注意到，若 $a\neq b$，$a+1>b$ 当且仅当 $a>b$。那么我们询问 $P_a+P_x>P_b$ 就可以获得 $a, b$ 的大小关系。

考虑归并排序，显然只需要询问 $N \log_2(N)$ 次，所以总询问次数是 $N-1+N \log_2(N)$，可以通过本题。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); ++i)

int ask(int i, int j, int k) {
  cout << "? " << i << ' ' << j << ' ' << k << endl;
  string s; cin >> s;
  if (s == "Yes") return true;
  else return false;
}

const int N = 2e3 + 10;
int id[N], a[N];
int now = 1;

bool cmp(int x, int y) {
  if (ask(x, now, y)) return 0;
  else return 1;
}

int main() {
  int n; cin >> n;  
  rep (i, 2, n) {
    if (!ask(i, i, now)) now = i;
  }
  rep (i, 1, n) {
    id[i] = i;
  }
  stable_sort(id + 1, id + n + 1, cmp);
  rep (i, 1, n) a[id[i]] = i;
  cout << "! ";
  rep (i, 1, n) cout << a[i] << ' ';
  cout << endl;
}
```

---

## 作者：VitrelosTia (赞：1)

首先排列的有一个非常美妙的性质是两个数肯定不会相等。然后又发现小于等于可以转化为不大于，就可以结合性质还有 $1$ 干一些事情了。

然后一个非常美妙的性质是 $1 + 1 < x (x > 1)$，发现小于等于等同于不大于，然后你就可以用这个东西找到 $1$ 的位置，过程类似取 max/min 时候的打擂台。

另一个非常美妙的性质是 $1 + x \le y (y > x)$，我们已经知道了 $1$ 的位置，那就可以直接知道两个位置的前后关系了。

找 $1$ 的时候只需要 $n$ 次询问，排序的时候使用稳定的归并排序需要 $n\log n$ 次询问，足够通过。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2005;
int n, p[N], o[N];
int pos = 1;

bool ask(int i, int j, int k) {
	cout << '?' << ' ' << i << ' ' << j << ' ' << k << '\n';
	string s; cin >> s; return s[0] == 'Y';
}

int main() {
	cin >> n;
	for (int i = 2; i <= n; i++) if (ask(pos, pos, i))
		pos = i;
	for (int i = 1; i <= n; i++) o[i] = i;
	stable_sort(o + 1, o + n + 1, [](int x, int y) { return !ask(x, pos, y); });
	for (int i = 1; i <= n; i++) p[o[i]] = i;
	cout << '!'; for (int i = 1; i <= n; i++) cout << ' ' << p[i]; cout << endl;
	return 0;
}
```

---

## 作者：happybob (赞：1)

如果我们可以知道对任意 $i,j$，$p_i$ 和 $p_j$ 的大小关系，那么我们可以用基于比较的排序算法，在 $O(n \log n)$ 的时间复杂度求出 $p$ 序列。

考虑怎么求出 $p_i$ 和 $p_j$ 大小关系，若 $p_i < p_j$，那么 $p_i +1 \leq p_j$，如果我们知道 $p$ 中 $1$ 的位置，那么我们可以通过一次询问求出 $p_i$ 和 $p_j$ 的关系。

如何求出 $1$ 的位置，我们不妨每次从剩下的数中选两个数 $i,j$，询问 `? i i j`，若结果是 `Yes`，那么 $p_i \neq 1$，若是 `No`，那么 $p_j \neq 1$。最终只会剩下一个数，就是 $1$ 的位置。

时间复杂度 $O(n \log n)$，询问次数约为 $n-1+n\log n$，可以通过。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N = 2e5 + 5, INF = 2e9, MOD = 1e9 + 7;

inline int read()
{
	int op = 1, x = 0;
	char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	while (ch == '-')
	{
		op = -op;
		ch = getchar();
	}
	while (ch >= '0' and ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * op;
}

inline void write(int x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, m, t;
int a[N], ans[N];
set<int> st;
int pos;

bool check_if(int x, int y)
{
	// a[x]<a[y]?
	printf("? %d %d %d\n", x, pos, y);
	fflush(stdout);
	string s;
	cin >> s;
	return (s[0] == 'N');
}

void merge_sort(int l, int r)
{
	if (l == r)
	{
		return;
	}
	int mid = l + r >> 1;
	merge_sort(l, mid);
	merge_sort(mid + 1, r);
	int la = l, lb = mid + 1;
	vector<int> v;
	v.clear();
	while (la <= mid && lb <= r)
	{
		if (check_if(ans[la], ans[lb]))
		{
			v.emplace_back(ans[la++]);
		}
		else
		{
			v.emplace_back(ans[lb++]);
		}
	}
	while (la <= mid) v.emplace_back(ans[la++]);
	while (lb <= r) v.emplace_back(ans[lb++]);
	int c = 0;
	for (int i = l; i <= r; i++) ans[i] = v[c++];
}
int ara[N];

int main()
{
	// freopen("*.in", "r", stdin);
	// freopen("*.out", "w", stdout);
	n=read();
	for(int i=1;i<=n;i++)
	{
		st.insert(i);
		ans[i]=i;
	}
	while(st.size()>=2)
	{
		int x=*(st.begin());
		st.erase(st.begin());
		int y=*(st.begin());
		st.erase(st.begin());
		printf("? %d %d %d\n", x, x, y);
		fflush(stdout);
		string s;
		cin >> s;
		if (s[0] == 'Y') st.insert(y);
		else st.insert(x);
	}
	pos = *(st.begin());
	merge_sort(1, n);
	for (int i = 1; i <= n; i++) ara[ans[i]] = i;
	printf("! ");
	for (int i = 1; i <= n; i++) printf("%d ", ara[i]);
	fflush(stdout);
	printf("\n");
	return 0;
}
```


---

## 作者：_Kenma_ (赞：1)

# arc154_d 解题报告

## 前言

好玩题。

## 思路分析

考虑先确定序列中的一个值。

发现只有最小值比较好确定。

具体地，最小值和自己相加，和其他任意一个数比较，结果都为 No。

所以可以进行 $n$ 次形如 $(min,min,i)$ 的询问操作，确定最小值的位置为 $min$，即 $P_{min}$ 是最小值。

然后就可以进行正常排序了，具体地，每次询问 $(i,min,j)$，可以确定 $P_i$ 和 $P_j$ 相对大小关系。

在实现时，可以直接用 sort 函数，自定义 cmp 函数排序。

具体实现可以看代码。

思路瓶颈在于怎样确定两个数的相对大小关系。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int n,dfn[2005],p[2005],minn;
string s;
bool cmp(int x,int y){
	cout<<"? "<<x<<' '<<minn<<' '<<y<<endl;
	cin>>s;
	if(s[0]=='Y') return false;
	else return true; 
}
int main(){
	cin>>n;
	minn=1; 
	for(int i=2;i<=n;i++){
		cout<<"? "<<i<<' '<<i<<' '<<minn<<endl;
		cin>>s;
		if(s[0]=='N'){
			minn=i; 
		}
	}
	for(int i=1;i<=n;i++){
		dfn[i]=i;
	}
	shuffle(dfn+1,dfn+1+n,rnd);
	stable_sort(dfn+1,dfn+1+n,cmp);
	for(int i=1;i<=n;i++){
		p[dfn[i]]=i;
	}
	cout<<"! ";
	for(int i=1;i<=n;i++){
		cout<<p[i]<<' ';
	}
	cout<<endl;
	return 0;
}
```

## 后记

虽然交互题很好玩，但是希望 CSP 还是不要出非传统题。

---

## 作者：Nephren_Sakura (赞：0)

首先观察到序列是一个排列，而题目要求我们询问出这个排列的信息，容易想到等同于给这个排列进行排序，同时在排序前记录每个数的位置，这样排序后第 $i$ 个数的值就是 $i$，而其在原序列中的位置为一开始记录的 $pos_i$。

于是问题转化为如何为这个序列进行排序。

序列长度不超过 $2000$，可以用 $25000$ 次询问，也就是说只要我们知道如何比较两个数的大小，我们可以直接用快排排出答案，只需要用 $n \times \log n$ 的询问次数。

问题转化为如何比较两个数。

观察题目给出的询问形式，$P_i+P_j>P_k$，也就是说，如果 $i=1$，那么询问便转化为 $P_i + 1 > P_k$，也就是 $P_i \ge P_k$，问题转化为如何在排列中询问出 $1$ 的位置。

然后发现对于任意的不等于一的数 $x$，都有 $1+1 \le x$ 且 $x+x \ge 1$。

于是我们从前往后枚举每个数，设当前假设的 1 的位置为 $k$，对 $k,k,now$ 进行询问，如果返回 Yes 则将 $k$ 更新为 $now$，这样在 $P_{now}=1$ 时 $k$ 必然会被更新为 $now$，可以找到 $1$ 的位置，问题得以解决。

时间复杂度为 $O(n \log n)$，询问次数为 $n \log n + n$。

最后注意一点就是本题的询问限制比较紧，普通的 sort 可能过不掉，最好使用 stable_sort 或者手写归并。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,p[1000005],a[1000005];
bool query(int i,int j,int k){
	cout<<"? "<<i<<' '<<j<<' '<<k<<'\n';
	fflush(stdout);
	string s;
	cin>>s;
	return s=="Yes";
}
int nw=1;
bool cmp(int i,int j){
	return !query(i,nw,j);
}
signed main(){
	cin>>n;
	for(int i=1; i<=n; i++) a[i]=i;
	for(int i=2; i<=n; i++)
		if(query(nw,nw,i))
			nw=i;
	stable_sort(a+1,a+n+1,cmp);
	for(int i=1; i<=n; i++) p[a[i]]=i;
	cout<<"! ";
	for(int i=1; i<=n; i++)
		cout<<p[i]<<' ';
    return 0;
}
```

---

## 作者：AC_love (赞：0)

注意到 $1 + 1$ 不会大于任何其他数，因此我们可以先用 $n - 1$ 次询问确定 $1$ 的位置。

具体做法是：当前假定为 $1$ 的位置为 $x$，询问的位置为 $y$。若 $x + x > y$ 成立则将假定为 $1$ 的位置改成 $y$，继续向后询问。这样 $n - 1$ 次询问后就能确定 $1$ 的位置。

然后注意到若 $x + 1 > y$ 则 $x > y$，同理若 $x + 1 \le y$ 则 $x < y$。借助 $1$ 的帮助能让我们快速判断其他数的大小关系。

这样的话直接模拟一种 $O(n \log n)$ 的排序排一下就可以了，也可以直接用 `stable_sort` 然后自定义比较函数直接排好。

[code](https://atcoder.jp/contests/arc154/submissions/59075301)

---

## 作者：phil071128 (赞：0)

### [ARC154D] A + B > C ?

> 交互题。有一个未知的**排列**，你每次可以询问交互库 `? a b c`，交互库会回答 $p_a+p_b>p_c$ 是否成立，请在 $n\log n$ 次询问中得到排列。

有三个参数实际上并不好做，如果有两个参数，那就相当于重载了大于号的运算符，这样的话，我们用基于比较的 $O(n\log n)$ 排序算法即可得到原排列。

如何把三个参数变成两个参数？我们**习惯性**地去找 $1$（因为通常 $1$ 是好找的），因为 $p_a+1 >p_b$ 和 $p_a>p_b$ 是完全等价的，因为这是个排列。

找 $1$ 的过程可以在 $O(n)$ 时间内完成：只有 $1$ 满足 $1+1>p_i$ 对所有 $p_i\ne 1$ 都不成立。我们不断用当前可能为 $1$ 的位置和一个未知的位置去比较，可以用双指针扫一遍得到。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int read(){
	char c=getchar();int h=0,tag=1;
	while(!isdigit(c)) tag=(c=='-'?-1:1),c=getchar();
	while(isdigit(c)) h=(h<<1)+(h<<3)+(c^48),c=getchar();
	return h*tag;
}
void fil(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
}
const int N=5e5+50;
int pos1;
bool cmp(int a,int b) { //[a<b]
	cout<<"? "<<a<<" "<<pos1<<" "<<b<<endl;
	string s;
	cin>>s;
	if(s=="Yes") {
		return 0;
	}else{
		return 1;
	}
}
int p[N];
void merge(int l,int r) {
	if(l==r) {
		return ;
	}
	int mid=(l+r>>1);
	merge(l,mid);merge(mid+1,r);
	vector<int>t;
	int j,k;
	for(j=l,k=mid+1;j<=mid&&k<=r;) {
		if(cmp(p[j],p[k])) t.push_back(p[j]),j++;
		else t.push_back(p[k]),k++;
	}
	if(j<=mid) for(;j<=mid;j++) {
		t.push_back(p[j]);
	} 
	if(k<=r) for(;k<=r;k++) t.push_back(p[k]);
	int cnt=0;
	for(int x:t) {
		p[cnt+l]=x;cnt++;
	}
}
int a[N];
int main(){
//	fil();
	int n=read();
	int _i=1;
	for(	int i=1,k=2;i<=n&&k<=n;k++) {
		_i=i;
		cout<<"? "<<i<<" "<<i<<" "<<k<<endl;
		string s;
		cin>>s;
		if(s=="Yes") {
			i=k;
		}else{
		}
		_i=i;
	}
	pos1=_i;
	for(int i=1;i<=n;i++) p[i]=i;
	merge(1,n);
	for(int i=1;i<=n;i++) a[p[i]]=i;
	cout<<"! ";for(int i=1;i<=n;i++) cout<<a[i]<<" ";
	cout<<endl;
	
	return 0;
}

```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

直接做肯定是不好做的，考虑一下有没有什么办法让排序更简单。

显然有，如果 $a_i>a_j$，那么一定有 $a_i+1> a_j$，也就是说，假如说 $a_p=1,a_i>a_j$，那么输出 $\texttt{? i p k}$ 一定返回 `Yes`。可以证明若 $a_i<a_j$，则返回 `No`。

因此，我们只需要找出 $1$ 的位置就行了。而且，令 $a_p=1$，我们显然有 $a_p+a_p\le a_i(i\ne p),a_i+a_i>a_p(i\ne p)$。

所以说我们假设其位置为 $p=1$，然后向后扫一遍，如果查询 $\texttt{p p i}$ 返回 `Yes`，则将 $p$ 更新为 $i$。由上面的两个引理显然可得这个位置就是 $1$。

思路理清了。代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
char c[5];
inline bool que(const int&l,const int&r,const int&v){
	cout<<"? "<<l<<" "<<r<<" "<<v<<endl;
	cin>>c; return c[0]=='Y';
}
int n,mp,a[2005],at[2005];
int main(){
	cin>>n; mp=1;
	for(int i=2;i<=n;++i)
		if(que(mp,mp,i)) mp=i;
	for(int i=1;i<=n;++i) a[i]=i;
	stable_sort(a+1,a+n+1,[](const int&l,const int&r){
		return que(r,mp,l);
	});cout<<"! ";
	for(int i=1;i<=n;++i) at[a[i]]=i;
	for(int i=1;i<=n;++i) cout<<at[i]<<" ";
	fflush(stdout);
}
```

---

## 作者：Muse_Dash (赞：0)

注意题目里没说 $i\neq j\neq k$，这也许减小了本题的难度。

当 $a_j=1$ 时，$a_i+a_j>a_k$ 在本题中相当于 $a_i\geq a_k$，因为 $a$ 是排列，所以等价于 $a_i>a_k$。考虑将询问过程写在快速排序的 `comp` 里面，由于 `sort` 有时会被换成插入排序，导致询问次数超限，故选用科技 `stable_sort`（函数名改改就行）或者手写归并排序。

考虑找到这个 $j$，发现 $1+1> i\in\{[2,n]\cap N^*\}$ 永远不成立，所以通过这个性质可以线性地找出 $j$。

[代码](https://www.luogu.com.cn/paste/2unbktf0)。

---

## 作者：Francais_Drake (赞：0)

一个不优秀的做法。

注意到可以询问 $(i,i,j)$ 以得出 $2i$ 和 $j$ 之间的大小关系。我们可以通过询问 $\forall i,(1,1,i)$，这样可以得出所有 $\le \frac {P_1}2$ 的数（或者是得出 $P_1=1$）。然后在 $\le \frac{P_1}2$ 的数内再次寻找直到找到 $1$ 所在的位置。由于每次询问对应序列长度一定至少减半，所以这部分询问次数不超过 $2n$。这个时候询问 $P_i+1>P_j$ 是否成立等效于询问 $P_i\ge P_j$ 是否成立；而 $P_i\ne P_j$ 所以这次操作直接等效于询问 $P_i>P_j$ 是否成立。然后就可以使用某些比较次数不超过 $n\log_2 n$ 的排序算法过掉本题。（因为试图考虑如何得出 $P_i$ 的具体值而被误导了很久）（注意内省排序 `sort` 极端情况下会 $\log_2 n$ 遍遍历整个数组才会转成堆排序，询问次数会超限，所以可以使用 `stable_sort` 或手写归并）（过掉的原因很可能是归并排序跑不满 $n\log_2 n$ 次比较）

~~听说 [$\sout{{\color{black}\rm Z}{\color{red}{\rm{MJ}}}}$](https://www.luogu.com.cn/user/680980) 奆佬在 5 分钟内切掉还自认为很正常，学不来学不来。~~
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2010;
int n,i,d,u,t,c[maxn],p[maxn]; char s[5];
inline bool cmp(const int &x,const int &y){
	printf("? %d %d %d\n",x,u,y);
	fflush(stdout); scanf("%s",s+1);
	return s[1]=='N';
}
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;++i) p[i]=i;
	for(d=n;u=p[1],d!=1;){
		t=0;
		for(i=2;i<=d;++i){
			printf("? %d %d %d\n",p[i],p[i],u);
			fflush(stdout); scanf("%s",s+1);
			if(s[1]=='N') c[++t]=i;
		}
		if(!t) break; d=t;
		for(i=1;i<=t;++i) p[i]=p[c[i]];
	}
	for(i=d=1;i<=n;++i) if(i!=u) p[++d]=i;
	stable_sort(p+2,p+n+1,cmp); 
	for(i=1;i<=n;++i) c[p[i]]=i; printf("! "); 
	for(i=1;i<=n;++i) printf("%d ",c[i]);
}
```

---

