# Equal Binary Subsequences

## 题目描述

给你一个长为 $2n$ 的01串 $s$ ，你需要将其分成两个相等的子序列。

在此之前你需要执行以下操作一次：

- 选一个 $s$ 的子序列（可能为空），然后将其向右循环移位一位。

具体来说，你可以选择一个下标序列 $b_1,b_2,\dots,b_m$ 满足 $1\le b_1<b_2<\dots<b_m\le 2n$ ，然后同时执行 $s_{b_1}=s_{b_m},s_{b_2}=s_{b_1},\dots,s_{b_m}=s_{b_{m-1}}$ 。

你能在执行以上操作一次后把 $s$ 分成两个相等的子序列吗？

#### Hint

把 $s$ 分成两个相等的子序列 $s^p$ 和 $s^q$ 是指找到两个下标序列 $p_1,p_2,\dots,p_n$ 和 $q_1,q_2,\dots,q_n$ ，使得从 $1$ 到 $2n$ 的每个整数都恰好在 $p$ 和 $q$ 中出现共一次，然后令 $s^p=s_{p_1}s_{p_2}\dots s_{p_n}$ ， 	$s^q=s_{q_1}s_{q_2}\dots s_{q_n}$ ，满足 $s^p=s^q$ 。

## 说明/提示

$1\le t\le 10^5,1\le n\le 10^5$ 。

保证同一测试点中所有数据的 $n$ 的和不超过 $10^5$ 。

## 样例 #1

### 输入

```
4
2
1010
3
100010
2
1111
2
1110```

### 输出

```
0
1 2
2 3 5
1 2 5
3 2 3 4
1 4
-1```

# 题解

## 作者：MoyunAllgorithm (赞：10)

自认为比其它题解说的更详细 qwq

### 题意

给你 $N(1 \le N \le 10^5)$，给你一个长度为 $2N$ 的只包含字符 `0` 和 `1` 的字符串。你要把它分成 $2$ 个相等的子序列。

我们称 $S$ 两个子序列（不一定连续） $a,b$ 是相等的，当且仅当：

- $|a|=|b|$；

- $S$ 的每个元素，要么在 $a$ 出现 $1$ 次，要么在 $b$ 出现 $1$ 次；

- 对于每个 $1 \le i \le N$，满足 $a_i=b_i$。

除此以外，你可以对字符串 $S$ 进行 $1$ 次操作：

选取 $S$ 的一个不一定连续的下标序列 $b_{1,2,\cdots ,M}$，让 $S_{b_1} \leftarrow  S_{b_M},S_{b_2} \leftarrow  S_{b_1},\cdots S_{b_M} \leftarrow  S_{b_M-1}$。也就是让这个子序列的所有元素旋转一位。

现在，对于给你的 $S$，如果它可以通过一次或零次操作得到两个相等的子序列，那么输出操作序列和最后两个相等的子序列中的一个的下标。如果不能，输出 `-1`。

### 分析

首先，显然 $S$ 中 `0` 和 `1` 的个数应为偶数，否则输出 `-1`。

之后我们发现，如果 $S$ 中 `0` 和 `1` 的个数为偶数，那么如果我们能够把 $S$ 变成这样的形式：

`1100111100000011......`（也就是说两个 `1` 挨着，两个 `0` 挨着）

那么由所有奇数下标构成的子序列显然等于所有偶数下标构成的子序列。

在上面的那个例子中就是：

`Odd:10110001......`

`Even:10110001......`

所以现在我们需要做的就是把 $S$ 字符串变成一个**让它的每一个奇数位等于这个奇数位的下一位**的字符串。这就用到旋转操作了。

我们以 `100111001010` 举例：

我们首先把字符串以 $2$ 为单位分隔开：`10|01|11|00|10|10`

其中第 $3$ 个单位和第 $4$ 个单位我们其实就不用处理了。

我们把第 $1,2,5,6$ 个单位拿出来：`10|01|10|10`

现在，我们想让每个单位内的字符相同。我们不妨强制让第一个单位只想要 `0`，那么里面有一个 `1` 被“排斥”了出来。我们强制第二个单位只想要 `1`，有一个 `0` 被排斥出来；强制第五个单位只想要 `0`，有一个 `1` 被排斥；这样一直循环下去。我们把所有被排斥出来的元素组成一个字符串：

`1010`

可以轻而易举的证明这是一个 `1` `0` 交替出现且长度为偶数的串。现在我们对这个串进行一次旋转操作，这个串就变成了

`0101`

现在我们把这个排斥串重新安到原来的串里，原来的串就变成了：

`00|11|00|11`

成为了一个满足奇数位和下一位相等条件的字符串。

也就是 **受到操作的下标子序列 $=$ 被“排斥”的元素的下标序列，最后的两个相同子序列中的一个的下标 $=$ $\{1,3,5,7,\cdots , 2N-1\}$**。

**AC CODE**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
int T,N;
int a[MAXN];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		int cnt0=0,cnt1=0;
		for(int i=1;i<=N*2;i++) 
		{
			scanf("%1d",&a[i]);
			if(a[i]) cnt1++;
			else cnt0++;
		}
		if(cnt1%2||cnt0%2)//如果无解
		{
			puts("-1");
			continue;
		}
		int select=1;
		int tot=0;
		int f[MAXN];
		for(int i=1;i<=N*2;i+=2)//每2个是一个单位
		{
			if(a[i]==a[i+1]) continue;//如果这个单位已经满足要求跳过
			if(a[i]==select) f[++tot]=i;
			else f[++tot]=i+1;
			select=1-select;//各个单位交替排斥0和1
		}
		printf("%d ",tot);
		for(int i=1;i<=tot;i++) printf("%d ",f[i]);//排斥序列==操作序列
		puts("");
		for(int i=1;i<=N*2;i+=2) printf("%d ",i);
		puts("");
	}
	return 0;
}
```




---

## 作者：hh弟中弟 (赞：1)

### [CF1736D Equal Binary Subsequences](https://www.luogu.com.cn/problem/CF1736D)
感觉是对脑电波题，能对上黄，对不上紫。\
首先对于 $1$ 和 $0$ 的个数是奇数的话一定不合法，特判掉即可。\
经过一些数据的模拟，我们好像并不能找出完全不合法的情况，这时可以大胆猜测如果数量不是奇数的话一定有解。\
考虑什么样的序列一定是合法的，不难发现，两位两位的进行分组，每组都一样的序列一定是合法的，如 `1111001100` 或 `0000111100`，对于答案 $p$，直接选奇数位就可以。\
事实上，对于任意一个可能合法的序列，都能构造出一种方案，使得他与上面序列同构。\
具体来说，我们扫描每一组，如果这两个数不一样，选出一个和上一个选择不一样的那一位（如果上次没选过就随便选），扫描完毕后，将选出的子序列右移一位。此时每组的两个数都相同，合法。\
考虑为什么第一组的数也一定相同：因为 $1$ 和 $0$ 的个数为偶数，所以选出来的数一定有偶数个 $0$ 和 $1$，并且他们是交错的，所以右移之后一定能使每一组的数都相同。
```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=2e5+10;
char s[N];
signed main(){
	// freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
	int T;std::cin>>T;
	while(T--){
		int n;std::cin>>n;n*=2;
		std::cin>>s+1;
		std::vector<int> v;
		int _1=0,_0=0;
		for(int i=1;i<=n;++i)_1+=s[i]=='1',_0+=s[i]=='0';
		for(int i=1;i<=n;i+=2){
			int x=i,y=i+1;
			if(s[x]!=s[y]){
				if(v.size()){
					if(s[x]!=s[v[v.size()-1]])v.push_back(x);
					else v.push_back(y);
				}
				else v.push_back(x);
			}
		}
		if(_1&1){std::cout<<-1<<'\n';continue;}
		std::cout<<v.size()<<' ';
		for(int x:v)std::cout<<x<<' ';
		std::cout<<'\n';
		for(int i=1;i<=n;i+=2)std::cout<<i<<' ';std::cout<<'\n';
	}
}
```

---

## 作者：E1_de5truct0r (赞：1)

显然，$1$ 的数量不是偶数一定无解（因为根本分不开一个 $1$）。

观察到相邻两个数 $2i-1,2i$ 只有两种情况：

1. $a_{2i-1}=a_{2i}$：则这样产生的 $1$ 的个数显然是偶数。

2. $a_{2i-1} \neq a_{2i}$：显然这样产生的 $1$ 的个数也是偶数。

所以我们对于奇数的第二种情况的对，取出它的 $0$ 那个数，而偶数的取出它的 $1$ 的那个数。

这样，就取出了一个 $0101\dots 0101$ 的序列。

我们把它右旋。变成了 $1010\dots 1010$ 的。

于是，每个 $2i-1,2i$ 的对里的数都相等了。

于是就做完了。

## 代码

```cpp
#include <bits/stdc++.h>

//缺省源

using namespace std;
const int MAXN=200005;

int a[MAXN],p[MAXN];

void solve(){
	int n;read(n);n<<=1;
	string s; readstr(s);
	int ans=0,tot=0;
	for(int i=0;i<n;i++) ans+=(s[i]&1);
	if(ans&1) return putstr("-1\n"),void();
	int cnt=0;
	for(int i=0;i<n;i+=2){
		if(s[i]!=s[i+1]){
			cnt++;
			if(cnt&1){
				if(s[i]=='1') p[++tot]=i;
				else p[++tot]=i+1;
			}else{
				if(s[i]=='1') p[++tot]=i+1;
				else p[++tot]=i;
			}
		}
	}
	wrt(tot); pc(32);
	for(int i=1;i<=tot;i++) wrt(p[i]+1),pc(32);
	pc(10);
	for(int i=1;i<=n;i+=2) wrt(i),pc(32);
	pc(10);
}

int main(){
	int T; read(T); while(T--){
		solve();
	}
	return flush(),0;
}
```

---

## 作者：Mirasycle (赞：0)

首先 $0~1$ 个数不相等肯定不行，我们可以大胆猜测一下个数相等的时候必然可以。其实我们也可以发现满足情况的可能很多，所以可能并不能直接找到一个通法。但这也说明了操作空间很大，我们可以钦定一种方案，强行构造。

肯定选择相对便利的方案尝试构造，如果两组中对应位置在 $s$ 中差距过大，那么必然难以操作。于是我们可以采取一些方法使得两组中对应位置相邻。效果就是类似 $0011001111110000$。考虑分组，分为 $(i,i+1)$，当 $s_i=s_{i+1}$ 显然可以，我们将不相等的位置提取出来，必定形如 $(1,0)~(0,1)$ 交替着选出 $0~1$ 然后平移即可。

---

## 作者：DaiRuiChen007 (赞：0)

# CF1736D 题解



## 思路分析

显然：`0` 和 `1` 出现的次数如果是奇数那么一定无解。

对于剩下的情况，注意到如下的观察：

> 观察：
>
> 我们定义第 $2i-1$ 位和第 $2i$ 位的字符构成一个“字符组”（$i\in[1,n]$），那么通过一次轮转操作，我们一定能使得原串中只含有字符组 `00` 和 `11`，下述操作方法：
>
> 以字符串 `000110111001` 为例：我们可以将其每两位进行划分得到 $6$ 个字符组：`00 | 01 | 10 | 11 | 10 | 01`。
>
> 显然对于字符组 `00` 和 `11` 没有操作的必要，而对于字符组 `10` 和字符组 `01`，我们对于每个字符组取出其中一个字符，并且满足我们取出的字符串是 `0` 和 `1` 交替的，由于需要取出字符的字符组中同时包含 `0` 和 `1`，所以一定存在这样的取出方案。
>
> 对于上面举的例子，我们对第 $2$ 个字符组取出第 $3$ 位 `0`，对第 $3$ 个字符组取出第 $5$ 位 `1`，对第 $5$ 个字符组取出第 $10$ 位 `0`，对第 $6$ 个字符组取出第 $12$ 位 `1`，最终得到取出的子序列 `0101`。
>
> 对取出的子序列右移一位，由于 `0` 和 `1` 出现的次数都是偶数，所以字符组 `01` 和字符组 `10` 的数量总和应该也为偶数，因此得到的子序列长度也是偶数，右移一位后恰好得到原序列取反，如例子中右移得到子序列 。`1010`
>
> 把取出的子序列放回去，那么被取出 `0` 的字符组有一个 `1` 没被操作，又获得了一个 `1`，那么我们就得到了字符组 `11`，同理，被取出 `1` 的字符组会变成字符组 `00`，如例子中得到了序列 `00 | 11 | 00 | 11 | 11 | 00 `。

根据观察中的构造方法，我们可以对于每个字符串通过右移使字符串仅由字符组 `00` 和 `11` 构成的，那么对于每个字符组，给 $S^p$ 和 $S^q$ 各一个字符即可。

时间复杂度 $\Theta(n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+1;
char str[MAXN];
inline void solve() {
	int n;
	scanf("%d%s",&n,str+1);
	vector <int> res;
	for(int i=1,op=0;i<=2*n;i+=2) {
		if(str[i]==str[i+1]) continue;
		op^=1;
		if(str[i]=='0'+op) res.push_back(i);
		else res.push_back(i+1);
	}
	if((int)res.size()%2==1) {
		puts("-1");
		return ;
	}
	printf("%d ",(int)res.size());
	for(int u:res) printf("%d ",u);
	puts("");
	for(int i=1;i<2*n;i+=2) printf("%d ",i);
	puts("");
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：hcywoi (赞：0)

## $\mathcal Solution$

$s^p = s^q$，即满足 $s$ 中可以划分成若干段连续序列，这些序列左半部分和右半部分相等。

### 【无解】

显然当 $0/1$ 的个数不是偶数时无解。

其他情况有解。

### 【证明】

**证明中的函数名请见下面【证明中的函数意义】。**

我们可以构造一组解：

把所有 $i \le n$，$a_{2i} \neq a_{2i + 1}$ 的 $2i$ 加入集合 $S$。

当 $i \le n$，$a_{2i} \neq a_{2i+1}$ 时。必然为 $\mathtt{01}$ 或者 $\mathtt{10}$。

则下标 $b_i$ 可以构造为 $\operatorname{one}(S_1), \operatorname{zero}(S_2), \operatorname{one}(S_3), \cdots$。

那么我们知道只有 $\operatorname{size}(S) \bmod 2 = 0$ 时成以上 $b_i$。

此题当有解时一定时 $\operatorname{size}(S) \bmod 2 = 0$。

证明：

当 $i \le n$，$a_{2i} = a_{2i+1}$ 时，$0/1$ 都是 $2$ 的倍数，不需考虑。

当 $i \le n$，$a_{2i} \neq a_{2i+1}$ 时。必然为 $\mathtt{01}$ 或者 $\mathtt{10}$。

当 $\operatorname{size}(S) \bmod 2 \neq 0$ 时，则 $i \le n$，$a_{2i} \neq a_{2i+1}$ 必然出现奇数次，即 $0/1$ 都是奇数次。

与 【无解】 情况矛盾。

最后 $p$ 即为 $1, 3, 5, \cdots, 2n - 1$。

时间复杂度为 $\Theta(n)$。

### 【证明中的函数意义】

$\operatorname{one}(i)$ 表示 $a_i$ 与 $a_{i+1}$ 是 $1$ 的位置。

$\operatorname{zero}(i)$ 表示 $a_i$ 与 $a_{i+1}$ 是 $0$ 的位置。

$\operatorname{size}(S)$ 表示集合 $S$ 的大小。

## $\mathcal Code$
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <cmath>
#include <sstream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

#define x first
#define y second
#define IOS ios::sync_with_stdio(false)
#define cit cin.tie(0)
#define cot cout.tie(0)

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;

const int N = 100010, M = 100010, MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;

void solve()
{
	int n;
	string str;
	cin >> n >> str;
	
	int sum = 0;
	for (auto x: str) sum += x == '0';
	if (sum & 1) cout << -1 << endl;
	else
	{
		vector<int> res;
		for (int i = 0; i < n * 2; i += 2)
			if (str[i] != str[i + 1])
			{
				if (str[i] - '0' == res.size() % 2) res.push_back(i + 1);
				else res.push_back(i + 2);
			}
		cout << res.size() << ' ';
		for (auto x: res) cout << x << ' ';
		cout << endl;
		
		for (int i = 1; i <= n * 2; i += 2) cout << i << ' ';
		cout << endl;
	}
}

int main()
{
	IOS;
	cit, cot;
	int T = 1;
	cin >> T;
	while (T -- ) solve();
	return 0;
}
```

---

## 作者：demonlover923 (赞：0)

首先有显然的必要条件是 $0$ 和 $1$ 的数量都得是偶数, 其实这也是必要条件, 考虑这样一种构造.

我们让 $s_{i}$ 和 $s_{i+1}$ 配对, 假设有 $x$ 个对 $s_i$ 和 $s_{i+1}$ 是不同的, 那么有 $n-x$ 个对是相同的, 其中 $x$ 一定为偶数, 给出简要证明, 设在 $n-x$ 对相同的中有 $y$ 对 $s_i$ 和 $s_{i+1}$ 均为 $1$ , 那么 $1$ 的总数为 $x+2y$ , 因为 $1$ 的个数总为偶数, 故 $x$ 为偶数.

现在我们的基础想法是让两个序列, 一个选 $s_{i}$ 另一个选 $s_{i+1}$ , 所以我们需要用给出的操作让那 $x$ 对也符合条件, 这是容易办到的.

我们仅需在这 $x$ 对中交替的选出 $01$ 即可, 例如我们有 $(s_{i}=1,s_{i+1}=0),(s_{j}=0,s_{j+1}=1),(s_{k}=0,s_{k+1}=1),(s_{l}=0,s_{l+1}=1)$ , 那么我们仅需操作下标 $i+1,j+1,k,l+1$ 即可, 这样轮换之后一定可以满足 $s_{i}=s_{i+1}$ .

最后取所有奇数即可, 时间复杂度 $\mathcal{O}(n)$ .

```cpp
inline bool main() {
	read(n);scanf("%s",s+1);
	vector <int> ().swap(res);
	int now = 0,tot = 0;
	for (int i = 1;i <= 2*n;i += 2)
		if (s[i] ^ s[i+1]) {
			tot++;
			res.push_back(i);
			if ((s[i]-'0') ^ now)res.back()++;
			now ^= 1;
		}
	if (tot&1)return puts("-1")&0;
	printf("%d",(int)res.size());
	for (auto it : res)printf(" %d",it);
	puts("");
	for (int i = 1;i <= 2*n;i += 2)printf("%d ",i);
	puts("");
	return 0;
}
```

---

