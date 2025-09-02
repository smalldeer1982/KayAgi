# [ABC324D] Square Permutation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc324/tasks/abc324_d

数字のみからなる、長さ $ N $ の文字列 $ S $ が与えられます。

$ S $ を並べ替えてできる文字列を十進法の整数として解釈したもののうち、平方数であるようなものがいくつあるか求めてください。

より厳密には、次のようになります。

$ S $ の先頭から $ i $ 番目 $ (1\leq\ i\leq\ N) $ の数字に対応する数を $ s\ _\ i $ とします。

$ (1,\ \ldots,\ N) $ の順列 $ P=(p\ _\ 1,p\ _\ 2,\ldots,p\ _\ N) $ によって $ \displaystyle\ \sum\ _\ {i=1}\ ^\ N\ s\ _\ {p\ _\ i}10\ ^\ {N-i} $ と書ける整数のうち、平方数であるようなものがいくつあるか求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 13 $
- $ S $ は数字のみからなる長さ $ N $ の文字列
- $ N $ は整数
 
### Sample Explanation 1

$ P=(4,2,3,1) $ とすると、$ s\ _\ 4\times10\ ^\ 3+s\ _\ 2\times10\ ^\ 2+s\ _\ 3\times10\ ^\ 1+s\ _\ 1=324=18\ ^\ 2 $ となります。 $ P=(3,2,4,1) $ とすると、$ s\ _\ 3\times10\ ^\ 3+s\ _\ 2\times10\ ^\ 2+s\ _\ 4\times10\ ^\ 1+s\ _\ 1=2304=48\ ^\ 2 $ となります。 これら以外の並べ替え方では平方数にならないため、$ 2 $ を出力してください。

### Sample Explanation 2

$ P=(1,3,2) $ もしくは $ P=(3,1,2) $ とすると、$ \displaystyle\sum\ _\ {i=1}\ ^\ Ns\ _\ {p\ _\ i}10\ ^\ {N-i}=1=1\ ^\ 2 $ となります。 $ P=(2,1,3) $ もしくは $ P=(2,3,1) $ とすると、$ \displaystyle\sum\ _\ {i=1}\ ^\ Ns\ _\ {p\ _\ i}10\ ^\ {N-i}=100=10\ ^\ 2 $ となります。 これら以外の並べ替え方では平方数にならないため、$ 2 $ を出力してください。 異なる並べ替え方でも、並べ替えた結果の数が同じなら $ 1 $ つと数えることに注意してください。

## 样例 #1

### 输入

```
4
4320```

### 输出

```
2```

## 样例 #2

### 输入

```
3
010```

### 输出

```
2```

## 样例 #3

### 输入

```
13
8694027811503```

### 输出

```
840```

# 题解

## 作者：include13_fAKe (赞：6)

## 前言
CSP 前最后一场 ABC，想要 AT 绿名，却没能成功。（但是我是卡在 T3 和 T5 上面的！！！！！）
## 题意
- 给定一个长度为 $N$ 的数字串。问有多少个平方数是这个数字串的排列（允许有前导零）
- $1\le N\le13$

## 思路
首先，枚举全排列复杂度太高 $O(N!)$，不可取。

考虑枚举每一个自然数的平方。

其实，最多从 $\color{red}0$ 枚举到 $\sqrt{10^{13}}$ 就可以了。也可以通过检测自然数的平方的位数是否超过了 $N$ 来决定是否结束枚举。

枚举每一个数的平方，然后用前导零补全位数，然后判断这个数的平方的数码是否与给出的数字串一致即可。
## 坑点
一定要从 $\color{red}0$ 开始枚举！！！！！（蒟蒻在这里卡了 $\color{red}25$ 分钟，交了 $\color{red}8$ 次错误代码，加罚了 $\color{red}40$ 分钟的时间）
## 代码
```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;

int N;
string s;
int ans[12];
int b[12];
int final;
signed main(){
	cin>>N;
	cin>>s;
	for(int i=0;i<N;i++){
		ans[s[i]-'0']++;
	}
	for(int i=0;i<=3162300;i++){
		int o=0;
		int k=1ll*i*i;
		memset(b,0,sizeof(b));
		while(k>0){
			b[k%10]++;
			k/=10;
			o++;
		}
		bool flag=true;
		if(o>N){
//			cout<<i<<endl;
			cout<<final<<endl;
			return 0; 
		}
		if(ans[0]<b[0])	flag=false;
		for(int j=1;j<=9;j++){
			if(ans[j]!=b[j])	flag=false;
		} 
		if(flag==true)	final++;
	}
	cout<<final<<endl;
	return 0;
}
```
## 结语
正如这道题一样，在一条路走不通的情况下，可以试试其他的路走不走得通。

最后的最后，也祝大家 **CSP-J/S 2023 第二轮 RP++**！

---

## 作者：2huk (赞：3)

$\mathcal O(n!)$ 枚举全排列显然会寄，因此考虑枚举所有的完全平方数，总共数量不会超过 $\sqrt n$。

那么对于一个完全平方数 $x$，首先它的位数不能比给定的数多，但可以比给定的位数少（当然也可以相同），因为这是前导零在捣乱。然后判断是否存在一种原数的排列与 $x$ 相同。

完成这件事的经典做法就是将两个数按照数位排序，然后按位比较是否相同即可。

```cpp
int n, res, a[N], b[N];

int calc(int x)
{
	int res = 0;
	while (x)
	{
		++ res;
		x /= 10;
	}
	return res;
}

bool chk(int x)
{
	for (int i = 1; i <= n; ++ i )
	{
		b[i] = x % 10;
		x /= 10;
	}
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; ++ i )
		if (a[i] != b[i])
			return false;
	return true;
}

main()
{
	n = read();
	
	for (int i = 1; i <= n; ++ i )
	{
		char c;
		cin >> c;
		a[i] = c - '0';
	}
	
	if (n == 1 && !a[1]) return puts("1"), 0;
	
	sort(a + 1, a + n + 1);
	
	for (int i = 1; i <= 1e7; ++ i )
	{
		int x = i * i, y = calc(x);
		if (y > n) break;
		res += chk(x);
	}
	
	wel(res);
	
  return 0;
}
```

---

## 作者：WhisperingWillow (赞：1)

显然不能直接枚举全排列，我们考虑枚举所有可能的 $i^2$。


如果其按位分解后（不足的补零）每位相同，那么答案就会多一个。

最后特判 $s=0$ 的情况。

[提交记录](https://atcoder.jp/contests/abc324/submissions/46566622)

---

## 作者：Airposs (赞：1)

## 题意概括：

给出一个字符串，需要使用字符串中的数重新排列成一个十进制数，查询有多少个数为平方数。

## 解题思路：

暴力是 $O(n!)$ ，但是对于 $n$ 为 12 和 13 的情况会 T，考虑优化。

由于 $n$ 最多为13，所以完全平方数最多有 $10^7$ 个，每个数判断一下是否可以由给出的字符串拼成即可。

## code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long M=15;
long long n,ans;
long long num[15],sum[15];
char s[M];
inline long long read(){
    long long x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<3)+(x<<1)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
inline bool check(){
    for(long long i=0;i<=9;i++){
        if(num[i]!=sum[i]){
            return 0;
        }
    }
    return 1;
}
int main(){
    n=read(); scanf("%s",s+1);
    for(long long i=1;i<=n;i++){
        sum[s[i]-'0']++;
    }
    for(long long i=0;i<=10000000;i++){
        long long now=i*i;
        for(long long j=0;j<=9;j++){
            num[j]=0;
        }
        for(long long j=1;j<=n;j++){
            long long x=now%10;
            num[x]++;
            now=now/10;
        }
        if(now){
            continue;
        }
        if(check()){
            ans++;
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：_lqs_ (赞：1)

首先看到这题容易想到的是 dfs，暴力枚举所有的排列然后计算完全平方数的个数，这种写法复杂度是 $O(n!)$，当 $n=13$ 时会去到 $6 \times 10^9$ 左右，复杂度并不正确。

因此我们考虑枚举所有可能的完全平方数，然后看序列 $s$ 是否能匹配。具体地，对于枚举的所有完全平方数 $i$，我们分解所有数位，序列 $s$ 能够匹配当且仅当除 $0$ 外的所有数字出现次数相同、$s$ 中 $0$ 的个数大于等于 $i$ 中 $0$ 的个数（因为多余的 $0$ 可以放在开头）。

所以我们只需枚举平方数的平方根 $k=\sqrt i$ 即可，时间复杂度 $O(n \sqrt {10^n})$。

最后别忘了从 $0$ 枚举，否则多吃 2 发罚时。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 20
#define int long long
int n,m,i,j,ans,a[N],u[N],cnt[N],ss[N];
char s[N];
bool check(int x){
	for(int i=0;i<=9;i++) ss[i]=0;
	while(x) ss[x%10ll]++,x/=10;
	if(ss[0]>cnt[0]) return false;
	for(int i=1;i<=9;i++) if(ss[i]!=cnt[i]) return false;
	return true;
}
signed main(){
	scanf("%lld%s",&n,s+1);
	for(i=1;i<=n;i++) a[i]=s[i]-'0',cnt[a[i]]++;
	for(i=0;i<=100000000;i++){
		if(check(i*i)) ans++;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：qejwdi (赞：0)

首先枚举全排列 `13!` 这就很炸裂，那么就动点小脑筋，对于每一个平方数来判断是否是给定的数的排列即可。

判的方法很多，这里给出一个方法：

把题目给的每一个数把数的出现次数记到一个 `cnt` 里面，对于一个平方数也存一个 `cnt`，然后直接对两个 `cnt` 判一下就好了。注意前导零，即不够的位都补成 0。

# 代码：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
#define rep(i,l,r) for (int i = (l); i <= (r); i++)
#define per(i,r,l) for (int i = (r); i >= (l); i--)
#define debug(x) cout << #x << '=' << x << '\n'
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int, int> PII;
typedef double db;
void tomax(int& a, int b) {a = max(a, b);}
void tomin(int& a, int b) {a = min(a, b);}
const int D = 10;
int cnt1[D], cnt2[D];
int len;
ll number;
int main() {
	scanf("%d", &len);
	for (int i = 0, x; i < len; i ++ ) {
        char c; cin >> c;
        number += c-'0';
		cnt1[c-'0']++;
	}
	if (!number) {
		cout << 1;
		return 0;
	}
	int ans = 0;
	for (int i = 1; i <= 10000000; i ++ ) {
		ll z = 1ll * i * i, ll = 0;
		rep(j,0,9) cnt2[j] = 0;
		while (z) {
			++ll;
			cnt2[z%10]++;
			z /= 10;
		}
		if (ll > len) break;
		bool f = 1;
		rep(j,0,9) {
			int t = cnt2[j];
			if (!j)
				t += len-ll;
			f &= t==cnt1[j];
		}
		if (f)
			++ans;
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：MornStar (赞：0)

# [ABC324D] Square Permutation 题解
## 题目大意
给定一个长度为 $n$ 的只有数字的集合 $S$。

问，$S$ 的全排列能组合出多少个**不同的**平方数。
## 思路
首先我们会想到枚举全排列，但是时间复杂度是阶乘量级，$n_{max}=13$，所以无法通过。

正难则反，既然枚举全排列不行，那我们就枚举平方数，这时我们发现十三位数内，平方数只有 $\sqrt{10^{13}}\approx 3162277$ 个。

这不就可以做了，我们只需要枚举平方数，再判断与集合内数字是否相同就行了，注意前导零。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,num[15],now[15],ans,sum1,ze;
string s;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>s;
	for(int i=1;i<=n;i++)	num[i]=s[i-1]^48;
	sort(num+1,num+n+1);
	for(int i=1;i<=n;i++)	sum1=sum1*10+num[i],ze+=(num[i]==0);
//  拆位排序后重新组合，方便比较
	for(long long i=0;i<=3162278;i++){
		long long tmp=i*i,cnt=0,sum2=0,z=0;
		while(tmp){
			now[++cnt]=tmp%10;
			tmp/=10;
		}
		sort(now+1,now+cnt+1);
		for(int j=1;j<=cnt;j++)	sum2=sum2*10+now[j],z+=(now[j]==0);
		ans+=(sum1==sum2&&ze>=z);
//		if(sum1==sum2&&ze>=z)	cout<<sum1<<" "<<sum2<<" "<<i<<" "<<i*i<<"\n";
	}
	cout<<ans;
}
```


---

## 作者：Sincerin (赞：0)

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc324_d)

[更好的阅读体验？](https://www.luogu.com.cn/blog/sincerin520/solution-at-abc324-d)

## 题意

给定 $n$ 和一个长度为 $n$ 的由数字组成的字符串 $s$，求得有多少种 $(1,\dots,n)$ 的排列 $p$，使得 $\large \sum_{i=1}^n{(s_{p_i}) \times10^{n-i}}$ 是一个完全平方数。

- $1 \leq n \leq 13 $。

人话：求用给定字符串中的 $n$ 个数字能够拼成多少个完全平方数？**前导零不需要进行计算**。


## 解析

首先根据题意模拟，我们不难写出以下代码。


```cpp
map<int,bool>existed;
ans=0;
do{
	res=0;
	for(ri i=1;i<=n;++i) res+=((s[p[i]]^48)*powl(10,n-i));
	ri k=sqrtl(res); 
	if(k*k==res) 
	{
		//注意，字符串中的重复数字会导致重复的完全平方数生成。 
		if(existed.find(res)!=existed.end()) continue;
		++ans;
		existed[res]=true;
	}
}while(next_permutation(p+1,p+1+n));//STL全排列 
```

但是我们知道，全排列有 $n!$ 种，每次排列的判定是 $\Theta(n+\log_2{n!})$ 的，所以时间复杂度为 $\Theta(n! \times(n+\log_2{n!}))$ 的。‬$13!=6227020800$，显然复杂度逆天，完全过不掉。

反过来考虑，虽然排列很多，但大部分都不是完全平方数。所以我们可以枚举 $k\in[1,n]$ 位完全平方数，因为小于等于 $13$ 位的完全平方数只有 $3162278$ 个，逐一判断是否正好由字符串 $s$ 中的数构成并统计答案即可，判断函数的运行次数为该数的位数。

注意正好由字符串 $s$ 中的数构成指的是**除 $0$ 外**的所有数都用上。


## AC Code

```cpp
// C++20 912B 152ms 35.51MB
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cmath> 
using namespace std;
#define int long long//防止见祖宗
#define ri register int 
int n,m,k,t,res,ans,vis[10],cnt[10]; 
char s[14]; 
vector<int>v;//完全平方数
inline bool check(int x)
{
	t=0;
	while(x)
	{
		if(!vis[x%10]) return false;//出现了字符串没有的数字
		x/=10; ++t;
	}
	if(t>n) return false;//位数不对
	return true;
}
inline bool judge(int x)
{
	for(ri i=0;i<=9;++i) cnt[i]=vis[i];
	while(x)
	{
		if(cnt[x%10]==0) return false;
		--cnt[x%10]; x/=10;
	}
	for(ri i=1;i<=9;++i) if(cnt[i]) return false;//没用完
	return true;
}
signed main(void)
{  
	scanf("%lld%s",&n,s+1);
	for(ri i=1;i<=n;++i) ++vis[s[i]^48]; 
	for(ri i=0;i<=3200000;++i)
	{
		k=i*i*1ll;
		if(check(k)) v.emplace_back(k); 
	}
	for(ri i=0;i<v.size();++i) if(judge(v[i])) ++ans; 
	printf("%lld\n",ans);
	return 0;
} 
```

[AC Record](https://www.luogu.com.cn/record/129442252)


---

## 作者：Loser_Syx (赞：0)

考虑 $\sqrt{n}$ 枚举凑成的平方数，然后对该平方数进行数位拆分，如果各个数的次数与给定字符串都相等或仅有 $0$ 部分小于给定字符串的个数，就是方案。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
#define int long long
#define open(x) freopen(#x".in", "r", stdin);freopen(#x".out", "w", stdout);
#define close fclose(stdin);fclose(stdout);
#define all(x) x.begin(), x.end()
namespace FastIO {
	template <typename T = int>
	inline T read() {
		T s = 0, w = 1;
		char c = getchar();
		while (!isdigit(c)) {
			if (c == '-') w = -1;
			c = getchar();
		}
		while (isdigit(c)) s = (s << 1) + (s << 3) + (c ^ 48), c = getchar();
		return s * w;
	}
	template <typename T>
	inline void read(T &s) {
		s = 0;
		int w = 1;
		char c = getchar();
		while (!isdigit(c)) {
			if (c == '-') w = -1;
			c = getchar();
		}
		while (isdigit(c)) s = (s << 1) + (s << 3) + (c ^ 48), c = getchar();
		s = s * w;
	}
	template <typename T, typename... Args> inline void read(T &x, Args &...args) {
		read(x), read(args...);
	}
	template <typename T>
	inline void write(T x, char ch) {
		if (x < 0) x = -x, putchar('-');
		static char stk[25];
		int top = 0;
		do {
			stk[top++] = x % 10 + '0', x /= 10;
		} while (x);
		while (top) putchar(stk[--top]);
		putchar(ch);
		return;
	}
} using namespace FastIO;
int t[10];
signed main() {
	int n = read(), cnt =0;
	string s;
	cin >> s;
	vector<int> a(10);
	for (int i = 0; i < n; ++i) a[s[i] - '0']++;
	for (int i = 0; i <= 1e7; ++i) {
		for (int j = 0; j < 10; ++j) t[j] = 0;
		int j = i * i;
		while (j) {
			t[j % 10] ++;
			j /= 10;
		}
		int flg = 1;
		for (int k = 0; k <= 9; ++k) if (a[k] != t[k] && (k != 0 || t[k] > a[k])) {
			flg = 0;
			break;
		}
		if (flg) ++ cnt;
	}
	write(cnt, '\n');
	return 0;
}
```

---

## 作者：ACtheQ (赞：0)

### 题目翻译
给定长度为 $N$ 的字符串 $S$，$S$ 的每个字符都是数字字符。
现在你可以任意重排 $S$ 的每个字符，显然一共有 $N$的阶乘种排列。
请你计算其中有多少种排列满足把重排后的 $S$ 看成十进制数之后，是完全平方数。

### 题目思路

$S$ 最大到 $10 \times 10 ^{12}$ 不到。

这样假如重排后的的 $S$ 为平方数的话，重排后的的 $S$ 的算术平方根 $\le 4000000$。

$10^n$ 次方范围内枚举完全平方数。

分离完全平方数的各位数字，统计完全平方数中 $0 \sim 9$ 的个数与字符串 $S$ 中 $0 \sim 9$ 的个数是否相同

---

## 作者：Uuuuuur_ (赞：0)

这道题范围感觉像是暴力的，但其实搜索 $O(n!)$，不能过。

搜索比较麻烦，我们发现完全平方数比较少，只要枚举 $N$ 位以内的完全平方数，看看是不是原字符串的一个排列即可。

时间复杂度 $O(10^{\frac{N}{2}}N)$。

我用了哈希来判断当前数是不是原字符串的排列。这是要注意前导零，要算出 $N$ 位的哈希值。

```cpp
#include <bits/stdc++.h>
#define int unsigned long long
#pragma GCC optimize(2)

using namespace std;
int st;
int n;
int a[15];
int ans;
bool vis[15];
vector<int> t;
int has[15];
signed main() {
    srand(time(0));
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    int sum = 0;
    for (int i = 0; i <= 9; i++) has[i] = rand() + (i + 3) * 114 - 514 + 212244 * i;
    for (int i = 1; i <= n; i++) {
        char x;
        cin >> x;
        a[i] = x - '0';
        sum += has[a[i]];
        
    }
    int lim = pow(10, n);
    for (int i = 0; i * i < lim; i++) {
        int res = 0;
        int p = i * i;
        for (int j = 1; j <= n; j++) {
            res += has[p % 10];
            p /= 10;
        }
        if (res == sum) ans++;
    }
    cout << ans;
    return 0;
}
```


---

## 作者：_liuyi_ (赞：0)

# 题意
给定一个字符串，问它的全排列中有几个完全平方数。
# 思路
$1\le n \le 13$，枚举全排列肯定会超时，我们考虑枚举完全平方数，打表后发现小于 $10^{13}$ 的完全平方数其实只有 $31622781$ 个，可以将字符串按字典序排序后，二分找到大于等于它的完全平方数再判断，判断的时候有几个坑点，注意对 $0$ 的特判。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define fi first
#define se second
#define pb push_back
#define mem(a,x) memset(a,x,sizeof(a))
#define all(x) x.begin(),x.end()
#define lisan(x) {sort(all(x));x.erase(unique(all(x)),x.end());}
#define SZ(x) ((int)((x).size()))
#define debug(x) cout<<#x<<"="<<x<<"\n";
typedef long long ll;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
typedef vector<int> VI;
typedef vector<vector<int>> VII;
typedef vector<ll> VL;
typedef vector<vector<ll>> VLL;
typedef unsigned long long ull;
typedef double db;
template<typename T> inline void cmax(T &a,const T b){if(a<b) a=b;}
template<typename T> inline void cmin(T &a,const T b){if(a>b) a=b;}
template<typename T> inline T gcd(T a,T b){return b?gcd(b,a%b):a;}
template<typename T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}
constexpr int N=1e6+10;
constexpr int mod=1e9+7;
//constexpr int mod=998244353;
int n,cnt[N],ans;
string s;
VL pos;
map<int,int> mp;
inline void solve(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    cin>>n>>s;
    for(int i=0;1ll*i*i<=1e13;i++) pos.pb(1ll*i*i);
    rep(i,0,SZ(s)-1) mp[s[i]-'0']++;
    sort(all(s));
    ll sum=0;
    rep(i,0,SZ(s)-1) sum=sum*10+s[i]-'0';
    int id=lower_bound(all(pos),sum)-pos.begin();
    rep(i,id,SZ(pos)-1){
        ll x=pos[i];
        rep(i,0,9) cnt[i]=0;
        while(x){
            cnt[x%10]++;
            x/=10;
        }
        bool ok=true;
        rep(i,1,9)  if(mp[i]!=cnt[i]) ok=false;
        if(ok&&cnt[0]<=mp[0]) ans++;
    }
    printf("%d",ans);

}
int main(){
    int T=1;
    //scanf("%d",&T);
    while(T--) solve();
}
```



---

## 作者：_zzzzzzy_ (赞：0)

# 思路

这里我们枚举所有的完全平方数，然后判断是否相等。

这里主要是怎么快速写出来是否相等，因为当你对给出的字符串排完序之后 $0$ 都变到后面了，所以我们可以把枚举的完全平方数变成字符串，然后排一遍序，然后假如是的话一定会是给出字符串的前缀，并且后面多出来的一定是零。

然后就很好判断了。

# 代码

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define per(i, l, r) for (int i = (r); i >= (l); i++)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
using namespace std;
using i64 = long long;
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);

	int n, cnt = 0;
	string str;
	cin >> n >> str;
	sort(str.begin(), str.end(), greater<int>());
	for (i64 i = 0; i * i <= 1e13; i++) {
		i64 now = i * i;
		string s = to_string(now), str1 = str;
		sort(s.begin(), s.end(), greater<char>());
		while (str1.size() > s.size()) {
			if (str1 != s) {
				if (str1[str1.size() - 1] == '0') {
					str1.pop_back();
				} else {
					break;
				}
			}
		}
		if (str1 == s) {
			cnt++;
		}
	}
	cout << cnt << "\n";
	return 0;
}

```

主体部分只有 $20$ 行。

---

## 作者：yhx0322 (赞：0)

## 题目翻译
给你一个长度为 $N$ 的字符串 $S$。

求：在字符串 $S$ 的所有排列中，有多少个排列转换为数字之后是平方数。

平方数的定义：是一个数的平方。

例：$324 = 18 ^ 2,2304 = 48 ^ 2$。

## 思路
这道题 $N \le 13$，说明字符串 $S$ 最多有 $13$ 位。

如果暴力搜索全排列的话，最多有 $13!$ 种方案，显然时间复杂度超限。

我们可以换一种角度思考：既然不能枚举全排列，那能不能枚举平方数的根呢？

因为 $S$ 转成整数最多就是 $10^{13}$，$\sqrt{10^{13}} \approx 10^6$，时间复杂度是可以过去的。

所以，我们就可以枚举平方数的根，从而算出平方数，再倒退平方数是否可以由 $S$ 的排列得到。

## 代码
```cpp
#include <bits/stdc++.h>


using namespace std;
using ll = long long;

const int N = 20;
char s[N];
int n, cnt[N], new_cnt[N];
ll ans = 0;
int main() {
	cin >> n >> s;
	for (int i = 0, len = strlen(s); i < len; i++) cnt[s[i] - '0']++;
	for (int w = 0; ; w++) {
		memset(new_cnt, 0, sizeof(new_cnt));
		int m = 0;
		for (ll t = 1LL * w * w; t; t /= 10) new_cnt[t % 10]++, m++;
		if (m > n) break;
		new_cnt[0] += n - m;
		int i;
		for (i = 0 ; i < 10; i++)
			if (cnt[i] != new_cnt[i])
				break;
		if (i == 10) ans++;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：FL_sleake (赞：0)

## 题意简述

给定一个数字 $s$，你可以对 $s$ 每一位的数字重新进行排列，问最多可以得到多少个不同的 $s$，满足 $s$ 是一个完全平方数。

## 解题思路

虽然有 $n \leq 13$，然而直接进行排列仍然会 TLE。不妨从完全平方数入手，预处理出每个完全平方数各自包含多少个 $1$，多少个 $2$，$\dots$，多少个 $9$。这是因为交换两个字符不会改变字符本身。

最后还要注意，$0$ 出现的次数不定。即，若 $s$ 中 $0$ 出现 $m$ 次，则 $0$ 出现 $0$ 至 $m$ 次的情况都要考虑进去（这是因为，我们可以把 $0$ 放到开头消除其对答案的影响）。

## 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
map<int,int> ans;
int main(){
	cin>>n>>s;
	for(int i=0;i<=3500000;i++){//3500000*3500000>9999999999999
		int num=i*i;
		int a[20];
		for(int i=0;i<=9;i++) a[i]=0;
		while(num) a[num%10]++,num/=10;
		int cnt=1;
		for(int i=0;i<=9;i++) cnt=cnt*10+a[i];
		ans[cnt]++;//将0~9出现的次数状压进cnt中存起来 
	}
	int num=0,Ans=0;
	for(int i=0;i<s.size();i++) if(s[i]=='0') num++;
	for(int i=0;i<=num;i++){//0可出现0~num次 
		multiset<int> x;
		for(int i=0;i<s.size();i++) x.insert(s[i]-'0');
		int cnt=1;
		cnt=cnt*10+num-i;
		for(int i=1;i<=9;i++) cnt=cnt*10+x.count(i);
		Ans+=ans[cnt];//统计答案 
	}
	cout<<Ans<<endl;
	return 0;
}
```

---

## 作者：uid_647775 (赞：0)

### 题意
给定一个有数字组成的字符串，求该字符串的全排列所对应的数字中，有多少个，是完全平方数。
### 思路
很明显，直接枚举该字符串的全排列会 TLE 。  
可以枚举枚举位数小于等于 $n$ 的完全平方数，统计每个数出现次数，对比出现次数，统计答案。  
对比出现次数时，需要注意：

- 由于可以有前导零，所以枚举的完全平方数中 $0$ 的数量只需要小于字符串中 $0$ 的数量。
- 其他数字的数量必须与输入的字符串一样。
- 注意清空数据。

### Code 
由于我的码风很丑，这里只给出 [链接](https://atcoder.jp/contests/abc324/submissions/46590212) 。

---

## 作者：1n1c5c5z (赞：0)

## 题意
给定一个 $N (1 \le N \le 13)$ 位的数，求将其各位重排后能产生完全平方数的个数。
## Solution
初步想法是考虑暴力枚举每一种重排方式统计答案，但无法通过此题，需要优化。  
优化方式很多，比如利用完全平方数模 $100$ （即取末二位），模 $8$ （后三位）等取模的方法排除掉很多不可能得到完全平方数的排列，由于时限很宽泛，很容易过。  
当然，枚举完全平方数，然后判定是否合法是一个更优，更好写的解法。
## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

int arr[14];
int cnt = 0, n;
int buc[10];
long long ans = 0;

void Iterate(int a, int b)
{
	cnt = 0;
	if (a == b) 
	{
		if (buc[a] < 2) return;
	}
	else if (!buc[a] || !buc[b]) return;
	buc[a]--;
	buc[b]--;
	for (int i = 0; i <= 9; i++)
	{
		for (int j = 1; j <= buc[i]; j++)
		{
			arr[++cnt] = i;
		}
	}
	do
	{
		int _ = arr[cnt] * 100 + a * 10 + b;
		if (_ % 8 != 0 && _ % 8 != 1 && _ % 8 != 4) continue;
		long long cur = 0;
		for (int j = 1; j <= cnt; j++)
		{
			cur *= 10ll;
			cur += (long long)arr[j];
		}
		cur = cur * 100ll + a * 10ll + b * 1ll;
		long long sc = sqrtl(cur);
		if (sc * sc == cur) ans++;
	}
	while (next_permutation(arr + 1, arr + cnt + 1));
	buc[a]++;
	buc[b]++;
}

int main() 
{
	string str;
	cin >> n >> str;
	if (n == 1) //特判
	{
		if (str == "0" || str == "1" || str == "4" || str == "9")
		{
			cout << 1 << endl;
		}
		else cout << 0 << endl;
		return 0;
	}
	for (int i = 0; i < str.length(); i++) buc[str[i] - '0']++;
	Iterate(0, 0);
	Iterate(0, 1);
	Iterate(0, 4);
	Iterate(0, 9);
	Iterate(1, 6);
	Iterate(2, 1);
	Iterate(2, 4);
	Iterate(2, 5);
	Iterate(2, 9);
	Iterate(3, 6);
	Iterate(4, 1);
	Iterate(4, 4);
	Iterate(4, 9);
	Iterate(5, 6);
	Iterate(6, 1);
	Iterate(6, 4);
	Iterate(6, 9);
	Iterate(7, 6);
	Iterate(8, 1);
	Iterate(8, 4);
	Iterate(8, 9);
	Iterate(9, 6);
	cout << ans << endl;
    return 0;
}

```

---

## 作者：xxr___ (赞：0)

**思路**

枚举每个平方数，统计它每个数出现的次数，判断是否和原数出现的次数相等即可。

因为有前导 $0$，所以在统计时要循环够 $N$ 次。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t1[10],t2[10];
signed main(){
	int n,a;
	cin>>n>>a;
	for(int i=1;i<=n;i++){
		t1[a%10]++;
		a/=10;
//		要循环够N次 
	}
	int maxn=0;
	for(int i=9;i>=0;i--){
		for(int j=1;j<=t1[i];j++){
			maxn=maxn*10+i;
//			求出最大的边界 
		}
	}
	int ans=0;
	for(int i=0;i*i<=maxn;i++){
		for(int j=0;j<10;j++){
			t2[j]=0;
//			清空 
		}
		int p=i*i;
		for(int j=1;j<=n;j++){
			t2[p%10]++;
			p/=10;
//			统计每个数出现的次数 
		}
		bool flag=true;
		for(int j=0;j<10;j++){
			if(t1[j]!=t2[j]){
				flag=false;
				break;
//				不满足条件，标记flag 
			}
		}
		if(flag==true)ans++;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

