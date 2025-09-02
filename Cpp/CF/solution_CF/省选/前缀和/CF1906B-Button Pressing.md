# Button Pressing

## 题目描述

You are given $ N $ buttons (numbered from $ 1 $ to $ N $ ) and $ N $ lamps (numbered from $ 1 $ to $ N $ ). Each lamp can either be on or off. Initially, lamp $ i $ is on if $ A_i = 1 $ , and off if $ A_i = 0 $ .

Button $ i $ is connected to lamp $ i - 1 $ (if $ i > 1 $ ) and lamp $ i + 1 $ (if $ i < N $ ). In one move, you can press a button $ i $ only if lamp $ i $ is on. When a button is pressed, the state of the lamps connected to this button is toggled. Formally, the lamps will be on if it was off previously, and the lamps will be off if it was on previously. Note that lamp $ i $ is not connected to button $ i $ , thus, the state of lamp $ i $ does not change if button $ i $ is pressed.

After zero or more moves, you want lamp $ i $ to be on if $ B_i = 1 $ , and off if $ B_i = 0 $ . Determine if it is possible to achieve this task.

## 说明/提示

Explanation for the sample input/output #1

For the first test case, by pressing the buttons $ 4, 2, 4, 3, 1, 2 $ in sequence, the condition of the buttons changes as: $ 0101 \rightarrow 0111 \rightarrow 1101 \rightarrow 1111 \rightarrow 1010 \rightarrow 1110 \rightarrow 0100 $ .

For the second test case, you are unable to press any button, hence it is impossible to reach the final state.

## 样例 #1

### 输入

```
2
4
0101
0100
3
000
010```

### 输出

```
YES
NO```

## 样例 #2

### 输入

```
5
7
0101011
1111010
5
11111
00000
4
1101
1101
6
101010
100100
3
000
000```

### 输出

```
NO
NO
YES
YES
YES```

# 题解

## 作者：FFTotoro (赞：8)

## 前言

很水的 $\color{Red}{^*2600}$，赛时没做可惜了。

## 解法

将灯的 $01$ 状态转换到异或前缀和序列 $s$ 的角度上进行观察，考虑一次操作的意义：即交换 $s$ 中一对相邻的元素，具体地，设进行操作的灯是 $i\color{Red}(i>1)$，那么异或前缀和序列中要么 $s_{i-1}=0,s_i=1$，要么 $s_{i-1}=1,s_i=0$；而进行完操作后，很显然 $s_{i-1},s_i$ 会交换，其他元素都不会变。

又根据冒泡排序的经典结论，即在进行上述操作的情况下，能将一个上面那样的异或前缀和序列任意重排——也就是说如果 $a$ 的异或前缀和序列与 $b$ 的异或前缀和序列中 $0$ 的个数相等（此时 $1$ 个数也相等），那么 $a$ 就可以转换为 $b$（即我们不需考虑元素的顺序）。

现在在考虑操作 $i=1$ 的情况。注意到此时没有 $p_{i-1}$ 与其进行交换，所以它直接变为 $0$，容易得知此时整个异或前缀和序列除了 $p_1$ 所有元素都翻转了（即 $0$ 变 $1$，$1$ 变 $0$）！用这个方法可以将异或前缀和序列中 $1$ 的个数 $c$ 变为 $n-c+1$。

最终结论容易得到。

放代码（全场 Shortest）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n; string a,b; cin>>n>>a>>b;
    auto f=[&](string s){
      int c=0,p=0;
      for(char i:s)c+=p^=i&1;
      // 异或前缀和
      return min(c,n-c+1);
      // 实际上只需考虑两者中较小值
    };
    cout<<(f(a)==f(b)?"YES\n":"NO\n");
  }
  return 0;
}
```

---

## 作者：Error_Yuan (赞：4)

怄火，撞我一年前出的题。

强化版指路：[P8864 「KDOI-03」序列变换](/problem/P8864)。

要想做这题，首先你需要发现操作的本质。这里援引 P8864 题解中的第一句话：

> 观察题意得，我们对序列 $a$ 做前缀异或和得到 $s$ 后，每次操作相当于交换 $s_i$ 和 $s_{i-1}$。

事实上观察本题的题意，可以发现和 P8864 的操作 **几乎** 完全一致。本题规定了选择的必须满足 $a_i=1$，事实上在原题中选择 $a_i=0$ 不会产生任何效果，因此它们等价，差别在于，本题中规定了选择下标为 $1$ 时的行为也合法。在这种情况下，操作的本质其实是，把 $s_2,s_3,\ldots s_n$ 全部取反。

这启示我们考虑 $(cnt_0,cnt_1)$ 表示 $s$ 数组中 $0$ 的个数和 $1$ 的个数。若某次操作后 $(cnt_0,cnt_1)$ 和 $b$ 数组的前缀异或和数组 $t$ 中的 $0,1$ 个数相等，则一定可以通过选择若干次下标 $\ge 2$ 的灯进行操作，使得二者相等。当选择 $1$ 时，有 $(cnt_0,cnt_1)\gets (n-cnt_0-1,cnt_0+1)$。观察可知，进行两次操作 $1$ 后影响相互抵消，因此直接判断 $(cnt_0,cnt_1)$ 和 $(n-cnt_0-1,cnt_0+1)$ 中是否有一者和 $t$ 中的 $0,1$ 个数相等即可。

注意，需要特判无法对 $1$ 进行操作的可能性，此时 $cnt_0=n$。

## 鲜花

这里再次援引 P8864 题解中的鲜花部分：

> 本题赛时最高得分为 $36$，似乎大家都没有想到题解的第一句话。。。

我们可以发现，题解的第一句话在 CF 上的评分是 *2600。（

## AC 代码

```cpp
// Problem: B. Button Pressing
// Contest: Codeforces - 2023-2024 ICPC, Asia Jakarta Regional Contest (Online Mirror, Unrated, ICPC Rules, Teams Preferred)
// URL: https://codeforces.com/contest/1906/problem/B
// Memory Limit: 1024 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)
 
#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
using namespace std;
using ll = long long;
using ull = unsigned long long;
 
const int _N = 1e5 + 5;
 
int T;
 
void solve() {
	int n; cin >> n;
	string s, t; cin >> s >> t;
	vector<int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i++) {
		a[i] = (s[i - 1] == '1');
		b[i] = (t[i - 1] == '1');
	}
	for (int i = 1; i <= n; i++) a[i] ^= a[i - 1];
	for (int i = 1; i <= n; i++) b[i] ^= b[i - 1];
	a[0] = b[0] = -1;
	if (count(all(a), 0) == count(all(b), 0)) cout << "YES" << '\n';
	else if (count(all(a), 0) == n) cout << "NO" << '\n';
	else if (count(all(a), 0) + 1 == count(all(b), 1)) cout << "YES" << '\n';
	else cout << "NO" << '\n';
	return;
}
 
int main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> T;
	while (T--) {
		solve();
	}
}
```

---

## 作者：Sunny郭 (赞：1)

原序列不好操作，我们把原序列转换为前缀异或和序列。

记异或和序列为 $s$。

考虑按一次按钮产生的贡献：

- 当 $i$ 不等于 $1$ 时，相当于交换 $s_i$ 和 $s_{i-1}$。

- 当 $i$ 等于 $1$ 时，没有 $s_0$ 与它交换，通过实际操作发现，只有当 $s_1$ 等于 $1$ 时相当于对 $2$ 开始到结尾的异或和取反。如果 $s_1$ 不为 $1$，但 $s$ 中有 $1$ 的话，我们可以通过上面的操作换一个过来。

当两个异或和序列可以通过上述操作变得相等时，输出 `YES`。

---

## 作者：Petit_Souris (赞：0)

遇到这种题肯定是考虑看前缀和或者差分。这个题显然是前缀和更加靠谱一点，容易发现操作等价于前缀异或数组 $s$ 中的相邻两个元素 $s_{i},s_{i-1}\color{red}{(i>1)}$，因为操作要求 $a_i=1$，所以 $s_{i}\neq s_{i-1}$，同时 flip 即交换。

但是还有 $i=1$ 的情况没有考虑。这时候发现实际上是把整个 $s[2,n]$ 取反了。这样操作就从繁琐的两次取反变成了简单的交换和取反。

我们发现用第一种操作可以得到任何原序列 $s$ 的排列。那么思路就很清晰了，分类讨论一下 $s_i=1$ 的是否存在，是否要移动一个到 $i=1$ 进行操作，剩下的部分只需要 $0$ 的个数和 $1$ 的个数对应相等就行了。时间复杂度 $\mathcal O(n)$。

```cpp
#include<bits/stdc++.h>
#define debug(x) cerr<<(#x)<<" "<<(x)<<endl
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe; 
ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void write(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
const ll N=1e6+9;
ll T,n,a[N],b[N];
char s[N],t[N];
void solve(){
	n=read();
	scanf("%s%s",s+1,t+1);
	rep(i,1,n)a[i]=a[i-1]^(s[i]=='1');
	rep(i,1,n)b[i]=b[i-1]^(t[i]=='1');
	ll cnt1=0,cnt2=0;
	rep(i,1,n)cnt1+=(a[i]==1),cnt2+=(b[i]==1);
	if(!cnt1){
		if(!cnt2)puts("YES");
		else puts("NO");
		return ;
	}
	if(cnt1==cnt2||n-(cnt1-1)==cnt2)puts("YES");
	else puts("NO");
}
bool Med;
int main(){
	cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
	T=read();
	while(T--)solve();
	return 0;
}
```

---

## 作者：Rainsleep (赞：0)

先考虑转化到前缀和上，然后考虑操作意义。

+ $i \neq 1$

因为需要保证 $a_i = 1$，所以 $s_i \neq s_{i - 1}$，操作相当于让 $s_i$ 和 $s_{i - 1}$ 翻转，并且因为原来不同所以操作可以视作交换了 $s_i$ 和 $s_{i - 1}$。所以如果 $1$ 个数相等可以通过冒泡得到 $b$。

+ $i = 1$

考虑对 $i = 1$ 的操作，相当于对 $i \in [2, n]$ 的 $s_i$ 进行翻转，设原 $1$ 的数量为 $t$，翻转后 $n - t + 1 \to t$，此时数量相等也可以。

>如果 $a_1 = 0$，可以考虑把 $1$ 交换到 $a_1$ 进行操作。而如果全 $0$ 则会在第一种情况内被判掉。  

[code](https://www.luogu.com.cn/paste/zf3bo3t7)

---

## 作者：WhisperingWillow (赞：0)

[CF1906B Button Pressing](https://www.luogu.com.cn/problem/CF1906B)

[CF 链接](https://codeforces.com/contest/1906/problem/B)

套路题，不懂为什么赛时切的人很少。

套路的，我们观察 $a$ 的前缀异或序列为 $s$ 的性质。

当 $a=\{ 1,0,1,0\}$ 时，$s=\{1,1,0,0 \}$。

选择 $3$ 进行操作，则有 $a=\{1,1,1,1 \},s=\{1,0,1,0 \}$。

发现相当于交换 $s_i,s_{i-1}$。

再选择 $1$ 进行操作，则有 $a=\{1,0,1,1 \},s=\{1,1,0,1 \}$。

发现相当于将 $s_{2\sim n}$ 取反。

也就是说，$a$ 能在若干次操作后等于 $b$，当且仅当 $a$ 的前缀异或序列中 $0$ 的数量恰好等于 $b$ 的前缀异或序列中 $0$ 的数量或者 $1$ 的数量。


```
#include <bits/stdc++.h>
#define f(c,a,b) for(c=a;c<=b;++c)
#define fd(c,a,b)for(c=b;c>=a;--c)
#define ll unsigned long long
#define int long long
#define mp make_pair
#define il inline
#define ri register
#define co const
using namespace std;
const int N=1e6+5;
int n,m,k,i,j;

il int read() {
	ri int ans=0;
	ri char c=getchar();
	ri bool neg=0;
	while(!isdigit(c)) neg|=(c=='-'),c=getchar();
	while(isdigit(c)) ans=(ans<<3)+(ans<<1)+c-48,c=getchar();
	return neg?-ans:ans;
}
il void write(ri int x) {
	if(x<0)x=-x,putchar('-');
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
il void writes(ri int x){write(x);putchar(' ');}
il void writed(ri int x){write(x);putchar('\n');}
int a[N];
bool solve(int x,int y){
	if(!y) return 0;
	if(x/y==1) return !solve(y,x%y);
	return 1;
}
inline int ff(string s){
	int Xor_sum=0,sum=0;
	for(auto i:s) {
		Xor_sum^=i%2;
		sum+=Xor_sum;
	}
	return sum;
}
il void solve(){
	n=read();
	string s,y;
	cin>>s>>y;
	puts(ff(s)==ff(y)||ff(s)==n-ff(y)+1?"YES":"NO");
}

signed main() {
	ri int t=read();
	++t;
	while(--t) solve();
	return 0;
}
```

---

