# Cat, Fox and the Lonely Array

## 题目描述

Today, Cat and Fox found an array $ a $ consisting of $ n $ non-negative integers.

Define the loneliness of $ a $ as the smallest positive integer $ k $ ( $ 1 \le k \le n $ ) such that for any two positive integers $ i $ and $ j $ ( $ 1 \leq i, j \leq n - k +1 $ ), the following holds: $ $$$a_i | a_{i+1} | \ldots | a_{i+k-1} = a_j | a_{j+1} | \ldots | a_{j+k-1}, $ $  where  $ x | y $  denotes the <a href="https://en.wikipedia.org/wiki/Bitwise_operation#OR">bitwise OR</a> of  $ x $  and  $ y $ . In other words, for every  $ k $  consecutive elements, their bitwise OR should be the same. Note that the loneliness of  $ a $  is well-defined, because for  $ k = n $  the condition is satisfied.</p><p>Cat and Fox want to know how lonely the array  $ a$$$ is. Help them calculate the loneliness of the found array.

## 说明/提示

In the first example, the loneliness of an array with a single element is always $ 1 $ , so the answer is $ 1 $ .

In the second example, the OR of each subarray of length $ k = 1 $ is $ 2 $ , so the loneliness of the whole array is $ 1 $ .

In the seventh example, it's true that $ (0 | 1 | 3) = (1 | 3 | 2) = (3 | 2 | 2) = (2 | 2 | 1) = (2 | 1 | 0) = (1 | 0 | 3) = 3 $ , so the condition is satisfied for $ k = 3 $ . We can verify that the condition is not true for any smaller $ k $ , so the answer is indeed $ 3 $ .

## 样例 #1

### 输入

```
7
1
0
3
2 2 2
3
1 0 2
5
3 0 1 4 2
5
2 0 4 0 2
7
0 0 0 0 1 2 4
8
0 1 3 2 2 1 0 3```

### 输出

```
1
1
3
4
4
7
3```

# 题解

## 作者：2huk (赞：7)

> - 给定一个长度为 $n$ 的数组 $a$，求最小的 $k$ 使得对于任意两个正整数 $i, j \in [1, n - k + 1]$ 都满足 $\operatorname{or}_{t=i}^{i+k-1} a_t = \operatorname{or}_{t=j}^{j+k-1} a_t$。
> - $n \le 10^5$，$0 \le a_i < 2^{20}$。

一种 $\Theta(n \log a_i)$ 的做法。

我们考虑 $0 \sim 19$ 这 $20$ 个二进制位中，如果某一位 $j$ 满足所有 $a_i$ 的这一位都为 $0$，那么就**不**需要靠考虑这一位对答案 $k$ 的影响了。因为无论 $k$ 如何取值，或和的第 $j$ 位一定为 $0$。

所以我们需要考虑的就是那些二进制位 $j$ 使得存在至少一个 $a_i$ 的第 $j$ 位为 $1$。注意到无论 $k$ 如何取值，或和的第 $j$ 位一定为 $1$。

所以我们需要的就是对于所有 $i$ 而言，将 $i \sim i + k - 1$ 的数或起来后，使得第 $j$ 位不为 $0$ 的最小的 $k$。那么对于每个 $i$ 求出的 $k$ 的最小值即为答案。再对于每个二进制位 $j$ 计算出最小的 $k$ 再取最小就是真正的答案。

例如所有 $a_i$ 的第 $j$ 位为：

$$
\begin{matrix} 0&0&1&0&0&0&1&0&1&0\end{matrix}
$$

显然如果 $k \le 3$ 的话 $i = 4$ 就是一个不合法的位置。因为 $a_4 \mid a_5 \mid a_6$ 的这一位为 $0$，但是 $i = 5$ 计算出的答案的这一位为 $1$。

所以 $k$ 就是最大的连续 $0$ 的数量加一。

```cpp
int n, a[N];
vector<int> s[30];
 
void Luogu_UID_748509() {
	for (int i = 0; i < 20; ++ i ) s[i].clear();
	
	fin >> n;
	for (int j = 0; j < 20; ++ j ) s[j].push_back(0);
	for (int i = 1; i <= n; ++ i ) {
		fin >> a[i];
		for (int j = 0; j < 20; ++ j )
			if (a[i] >> j & 1) s[j].push_back(i);
	}
	for (int j = 0; j < 20; ++ j ) s[j].push_back(n + 1);
	int res = 0;
	for (int i = 0; i < 20; ++ i )
		if (s[i].size() > 2) for (int a = 0, b = 1; b < s[i].size(); ++ a, ++ b )
			res = max(res, s[i][b] - s[i][a]);
	if (res == 0) res = 1;
	fout << res << '\n';
}
```

---

## 作者：Cute__yhb (赞：6)

## 思路

二分。

对于一段长度为 $k$ 的区间，考虑二进制上的每一位，如果整个数组二进制上这一位有数，而这个区间却没有，这就说明了一定有一个区间的按位或不同于这个区间。

反之，则说明 $k$ 可行。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define re register
#define ri register int
#define rll register long long
#define ld long double
#define endl '\n'
#define fi first
#define se second
#define pii pair<int,int>
#define p_q priority_queue
#define iter iterator
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define nep(i,a,b) for(int i=(a);i>=(b);i--)
#define popcount __builtin_popcount
#define pb push_back
#define mem(a,x) memset((a),x,sizeof(a))
#define eps 1e-8
#define oper operator
#define mk make_pair
int n,a[100005],b[31][100005];
bool check(int k){
	for(int i=0;i<=30;i++){
		if(b[i][n]!=0){//整个数组这一位上有数
			for(int j=k;j<=n;j++){//枚举区间右端点
				int l=j-k+1,r=j;//左、右端点
				if(b[i][r]-b[i][l-1]==0) return 0;//这个区间内这一位上没有数
			}
		}
	}
	return 1;//可行
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		for(int j=0;j<=30;j++){
			b[j][i]=(a[i]>>j)&1;//二进制每一位
		}
	}
	for(int i=0;i<=30;i++) for(int j=1;j<=n;j++) b[i][j]+=b[i][j-1];//处理前缀和
	int l=1,r=n,ans=n;
	while(l<=r){//二分
		int mid=(l+r)/2;
		if(check(mid)){
			r=mid-1;
			ans=mid;//记录答案
		}else l=mid+1;
	}
	cout<<ans<<endl;
}
int main(){
	int t;
	cin>>t;
	while(t--) solve();
    return 0;
}
```

---

## 作者：a18981826590 (赞：1)

# [Cat, Fox and the Lonely Array](https://www.luogu.com.cn/problem/CF1973B)
## 解题思路 $O(t n \log \max \{a_{i}\})$
因为所有长度为 $k$ 的子序列或和相等且或和第 $x(x \in[0,19])$ 位为 $1$，则每一个长度为 $k$ 的子序列包含至少 $1$ 个第 $x$ 位为 $1$ 的数。

若序列中有至少 $1$ 个第 $x$ 位为 $1$ 的数，则至少 $1$ 个长度为 $k$ 的子序列或和第 $x$ 位为 $1$；为使所有长度为 $k$ 的子序列或和相等，则相等的子序列或和第 $x$ 位为 $1$。

我们可以遍历每一位，找到原序列中两个第 $i$ 位为 $1$ 的数的距离 $m_{i}$，取最大值，这样所有长度为 $m_{i}$ 的子序列必然会覆盖至少 $1$ 个第 $i$ 位为 $1$ 的数，这样所有长度为 $m_{i}$ 的子序列或和第 $i$ 位必然为 $1$，这样所有长度为 $m_{i}$ 的子序列或和第 $i$ 位必然相等。

为使所有长度为 $k$ 的子序列或和相等，则或和每一位必然相等，取 $\max \{m_{i}\}$ 即可。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010],m,n,t,x,y;
bool z;
inline int read(){
	char c;
	int d=0,e=1;
	c=getchar_unlocked();
	while(!isdigit(c)){
		if(c=='-') e=-1;
		c=getchar_unlocked();
	}
	while(isdigit(c)){
		d=(d<<1)+(d<<3)+(c^48);
		c=getchar_unlocked();
	}
	return d*e;
}
void print(long long int d){
	if(d<0){
		putchar_unlocked('-');
		d=-d;
	}
	if(d<10) putchar_unlocked(d+48);
	else{
		print(d/10);
		putchar_unlocked(d%10+48);
	}
}
int main(){
	t=read();
	while(t--){
		n=read();
		m=1;
		for(int i=1;i<=n;i++) a[i]=read();
		for(int i=0;i<20;i++){
			x=y=z=0;
			for(int j=1;j<=n;j++){
				if((a[j]>>i)&1){
					x=max(x,j-y);
					y=j;
					z=1;
				}
			}
			if(z) x=max(x,n+1-y);
			m=max(m,x);
		}
		print(m);
        putchar('\n');
	}
	return 0;
}
```

---

## 作者：Engulf (赞：1)

很暴力的做法。

注意到答案是具有单调性的，若 $k$ 合法，$k+1$ 也合法，因为是或运算，相同的数多或上一个数结果是一样的。二分 $k$，每次检测相邻的两个区间的连续 $k$ 个数的或值是否相等，这个可以线段树解决。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 1e5 + 5;

int n;
int a[N];
int tr[N << 2];

void build(int p, int l, int r) {
    if (l == r) {tr[p] = a[l]; return;}
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    tr[p] = tr[p << 1] | tr[p << 1 | 1];
}
int query(int p, int l, int r, int L, int R) {
    if (l > R || r < L) return 0;
    if (L <= l && r <= R) return tr[p];
    int mid = l + r >> 1;
    return query(p << 1, l, mid, L, R) | query(p << 1 | 1, mid + 1, r, L, R);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        build(1, 1, n);

        int l = 1, r = n, res = -1;
        while (l <= r) {
            int mid = l + r >> 1;
            if ([=]() {
                for (int i = 1; i < n - mid + 1; i++)
                    if (query(1, 1, n, i, i + mid - 1) != query(1, 1, n, i + 1, i + mid))
                        return false;
                return true;
            }()) res = mid, r = mid - 1;
            else l = mid + 1;
        }
        assert(res != -1);

        cout << res << "\n";
    }
    return 0;
}
```

---

## 作者：kanzaki (赞：1)

## 思路
题目要求为或运算，考虑尝试按数位拆分寻找规律。发现要使任意长度为 $k$ 的子序列都满足要求，那么拆后每个数任意一位都要为 $1$（如果存在一个数该位为 $1$）。

例如 $1,4,2$。拆分后为 $1,100,10$。按数位对齐后第一位为分别为 $1,0,0$。则该位要求的最少长度为 $3$。因为如果最小长度为 $2$，$4 \mid 2 = 6$，$6$ 拆分后为 $110$，第一位不为 $1$。而 $1 \mid 4 = 5$，$5$ 拆分后为 $101$，第一位为一，无法满足题目要求。

那么满足每一位的 $k$ 就是所有位要求的的最大值。那么分别对每一位进行处理最后求出最大值即可。

观察例子，发现每一位要求的 $k$ 就是最长连续 $0$ 的长度加 $1$。这样可以保证子序列中至少有一个数该位为 $1$,取得 $k$ 在合法范围内的最小解。因为 $k$ 如果再小就会出现有数进行或运算后该位仍不为 $1$ 的情况。

需要注意的是，如果所有数在某一位都是 $0$，那么这一位要求的 $k$ 的长度就不是 $n$ 而是 $1$，需要特判。因为无论 $k$ 的值是多少，所有数在该位的值或后都为 $0$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
int a[maxn],res[maxn];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t,n;
	cin>>t;
	while(t--){
		cin>>n;
		int len=0,ans=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int j=0;j<=20;j++){
			len=0;
			for(int i=1;i<=n;i++){
				if(((a[i]>>j)&1)==0){
					len++;
				}
				else {
					res[j]=max(res[j],len);
					len=0;
				}
			}
			res[j]=max(res[j],len);
			if(len==n) res[j]=0;
		}
		for(int j=0;j<=20;j++){
			ans=max(ans,res[j]+1);
//			cout<<res[j]+1<<' ';
		}
//		cout<<'\n';
		cout<<ans<<'\n';
		memset(res,0,sizeof(res));
	}
}
```

---

## 作者：_Lightning_ (赞：1)

### 题目分析

这题我一看上去觉得眼花缭乱的，后来想了想，$2^{20}$ 可以用数组存，建一个 $a$ 数组，考虑 $a_0 \sim a_{19}$。

我们遍历每段长度为 $k$ 的范围，如果 $a_i$ 不为 $0$，但在这个范围内，并未出现这个数，明显行不通，否则就成立。这部分时间复杂度为 $O(n)$。

**注意：在此之前我们要先把每一位二进制，才能进行接下来的运算。**

其余部分考虑 $O(\log n)$，可以二分答案，总时间复杂度为 $O(n \log n)$。

### 代码（部分）

遍历判断部分：

```cpp
bool check(int k) {
	for(int i = 0; i <= 30; i++) {
		if(cnt[i][n] != 0) { //范围内这一位上有数
			for(int j = k; j <= n; j++) {//枚举整个范围的右端点
				int l = j - k + 1,r = j;//左、右端点
				if(cnt[i][r] - cnt[i][l - 1] == 0) return false;//这个区间内这一位上没有数，不行
			}
		}
	}
	return true;//判断后可以
}
```

二进制化部分：

```cpp
cnt[j][i] = (a[i] >> j) & 1;//二进制每一位
```

前缀和预处理部分：

```cpp
for(int i = 0; i <= 30; i++) 
	for(int j = 1; j <= n; j++) 
		b[i][j] += b[i][j - 1]; //前缀和处理
```

二分部分：

```cpp
int l = 1, r = n, ans = n;
while(l <= r) { //二分答案
	int mid = (l + r) / 2;
	if(check(mid)) {
		r = mid - 1;
		ans = mid;//记录答案
	} else l = mid + 1;
}
```

---

## 作者：toolong114514 (赞：1)

# CF1973B Cat, Fox and the Lonely Array 题解
## 题面翻译
给定一个长度为 $n$ 的数组 $a(a_1,a_2,\cdots,0\le a_n\le 10^9)$，定义其孤独值为满足以下定义的最小正整数 $k$：

$\forall 1\le i,j \le n-k+1,i,j\in N_+$，满足 $a_i|a_{i+1}|\cdots|a_{i+k-1}=a_j|a_{j+1}|\cdots|a_{j+k-1}$。（注意，运算符号“$|$”为按位或操作）

求出该数组的孤独值。

本题中单个测试点含有多组询问，保证所有的 $n$ 之和不超过 $10^5$。
## 解题思路
容易发现，在 $k$ 给定的情况下，可以快速验证这个 $k$ 是否满足题面的条件。

对 $a$ 建一个 ST 表，顺序扫一遍，求出每个长度为 $k$ 的区间的连续按位或值，判断是否全部相同即可。

现在，如果能证明答案的单调性，就可以使用二分答案解决。

### 赛时做法 
随便造了几组数据，对于每个 $k$ 都输出 check 函数的值，发现总是先为 $0$，后为 $1$（或者全部都是 $1$）。

由此一眼丁真，答案就是存在单调性。

交了几发，调了几下，过掉了 pretest，赛时和赛后都没有被 hack。
### 严格的证明
考虑任意的两组长度为 $k$ 的区间，发现对其延展一格，二进制位下是不会新增 $1$ 的。如果当前 $k$ 满足条件，那么所有的数在二进制之下，一定在一些地方都没有 $1$，这样才能使 $k$ 满足条件。

所以，如果 $k$ 成立，那么 $k+1$ 一定成立。
### 总结
因为答案 $k$ 具备单调性，所以直接二分答案，再按上述思路编写 check 函数即可。

求区间连续或值是典型的 RMQ（可重复贡献）问题，用 ST 表可以做到单次 $O(1)$ 查询，所以单次 check 的时间复杂度为 $O(n)$。

总的时间复杂度为 $O(n\log n)$。
## 参考代码
```cpp
#include<iostream>
#include<cmath>
using namespace std;
const int N=1e6+10;
int a[N],logg[N],st[N][30];
int n;
bool check(int x){
	//cout<<"AC\n";
	int last=0,ln=logg[x];
	for(int i=1;i<=x;i++){
		last|=a[i];
	}
	for(int i=1;i<=n-x+1;i++){
		int tmp=st[i][ln]|st[i+x-(1<<ln)][ln];
		if(tmp!=last) return false;
	}
	return true;
}
int t;
int main(){
	ios::sync_with_stdio(false);
	cin>>t;
	for(int i=2;i<=N-10;i++){
		logg[i]=logg[i/2]+1;
	}
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			st[i][0]=a[i];
		}
		int lg=logg[n]+1;
		for(int j=1;j<=lg;j++){
			for(int i=1;i<=n;i++){
				st[i][j]=0;
			}
		}
		for(int j=1;j<=lg;j++){
			for(int i=1;i<=n;i++){
				st[i][j]=st[i][j-1]|st[i+(1<<(j-1))][j-1];
			}
		}
		int ans=n+1;
		int l=1,r=n;
		while(l<=r){
			int mid=(l+r)/2;
			if(check(mid)){
				ans=min(ans,mid);
				r=mid-1;
			}else{
				l=mid+1;
			}
		}
 		cout<<ans<<'\n';
	}
	return 0;
}
```
[本代码可以通过 CF 的评测。](https://www.luogu.com.cn/record/159935206)
## 后记
似乎利用上文中“严格的证明”一节中的性质，可以拆位去做，不用二分答案。

Written by [toolong114514](https://www.luogu.com.cn/user/477821) on 2024/5/23.

---

## 作者：HasNoName (赞：0)

### 思路

因为答案满足单调性，所以考虑二分。

考虑如何验证任意长度数字串是否可行。

可以使用一个数组存储每位二进制，每与一个数做或运算，就将对应二进制相加。要撤销与一个数做的或运算时，就将每位二进制相减。要得到那个数时就将每一位数变为 `bool` 类型再计算。再判断是否与第一次的值相等。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int n,a[N],b[30];
int get()//得到那个数
{
    int sum=0,c=1;
    for(int i=0;i<25;i++)
    {
        sum+=(bool)(b[i])*c;
        c*=2;
    }
    return sum;
}
bool ok(int len)//check
{
    memset(b,0,sizeof(b));
    for(int i=1;i<=len;i++)
    {
        int c=a[i];
        for(int j=0;j<25;j++)//对应二进制相加
        {
            if(c&1)b[j]++;
            c>>=1;
        }
    }
    int t=get();
    for(int i=len+1;i<=n;i++)
    {
        int c=a[i-len];
        for(int j=0;j<25;j++)//对应二进制相减
        {
            if(c&1)b[j]--;
            c>>=1;
        }
        c=a[i];
        for(int j=0;j<25;j++)
        {
            if(c&1)b[j]++;
            c>>=1;
        }
        if(get()!=t)return 0;//不同
    }
    return 1;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin>>T;
    while(T--)
    {
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        int l=1,r=n,mid;//二分
        while(l<r)
        {
            mid=(l+r)>>1;
            if(ok(mid))r=mid;
            else l=mid+1;
        }
        cout<<r<<'\n';
    }
    return 0;
}

```

---

## 作者：lyhqwq (赞：0)

# Solution

异或问题考虑拆位。

若任意连续 $k$ 个数的异或和都相等，那么每一位上任意连续 $k$ 个数的异或也相等。

分别考虑每一位对 $k$ 的限制，若这一位上全为 $0$，则对 $k$ 没有限制，否则，$k$ 至少是两个相邻的 $1$ 之间 $0$ 的个数的最小值 $+1$。

把每一位的限制求出来最后取 $\max$ 即可，时间复杂度 $O(Tn\log V)$。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int _;
int n;
int a[N],Max[21],lst[21];
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d",&_);
	while(_--){
		scanf("%d",&n);
		for(int i=0;i<=20;i++) Max[i]=lst[i]=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			for(int j=0;j<=20;j++) if((a[i]>>j)&1) Max[j]=max(Max[j],i-lst[j]-1),lst[j]=i;
		}
		for(int j=0;j<=20;j++) if(lst[j]) Max[j]=max(Max[j],n-lst[j]);
		int ans=0;
		for(int i=0;i<=20;i++) ans=max(ans,Max[i]+1);
		printf("%d\n",ans); 
	}
	return 0;
}
     
```

---

