# Balance the Bits

## 题目描述

A sequence of brackets is called balanced if one can turn it into a valid math expression by adding characters '+' and '1'. For example, sequences '(())()', '()', and '(()(()))' are balanced, while ')(', '(()', and '(()))(' are not.

You are given a binary string $ s $ of length $ n $ . Construct two balanced bracket sequences $ a $ and $ b $ of length $ n $ such that for all $ 1\le i\le n $ :

- if $ s_i=1 $ , then $ a_i=b_i $
- if $ s_i=0 $ , then $ a_i\ne b_i $

If it is impossible, you should report about it.

## 说明/提示

In the first test case, $ a= $ "()()()" and $ b= $ "((()))". The characters are equal in positions $ 1 $ , $ 3 $ , $ 4 $ , and $ 6 $ , which are the exact same positions where $ s_i=1 $ .

In the second test case, $ a= $ "()()((()))" and $ b= $ "(())()()()". The characters are equal in positions $ 1 $ , $ 4 $ , $ 5 $ , $ 7 $ , $ 8 $ , $ 10 $ , which are the exact same positions where $ s_i=1 $ .

In the third test case, there is no solution.

## 样例 #1

### 输入

```
3
6
101101
10
1001101101
4
1100```

### 输出

```
YES
()()()
((()))
YES
()()((()))
(())()()()
NO```

# 题解

## 作者：hhoppitree (赞：29)

### 题意简述：  

- 给定数列 $s$，试构造与 $s$ 同长的括号串 $a,b$ 使得 $a,b$ 均为合法括号串且 $[a_i=b_i]=s_i$；
- $|s|$ 为偶数且 $|s|\le2\times10^5$，其中 $s_i\in\{0,1\}$。

### 题目解法：

记 $|s|=n$，则当 $s_1=0$ 或 $s_n=0$ 时易得无满足条件的字符串 $a,b$。

由于 $a,b$ 中 $\texttt{(}$ 和 $\texttt{)}$ 的数量均一样，所以字符 $\texttt{(}$ 和 $\texttt{)}$ 在 $a$ 和 $b$ 中出现的**总次数**是一样的。

由于 $a_i=b_i$ 当且仅当 $s_i=1$，所以当 $s_i=1$ 时，$\texttt{(}$ 的数量减去 $\texttt{)}$ 的数量要么加上 $2$，要么减去 $2$。

所以满足 $s_i=1$ 的 $i$ 的数量必然是偶数。

所以无解的充分条件为 $[s_1=0]\;{\rm or}\;[s_n=0]\;{\rm or}\;2\nmid\sum\limits_{i=1}^{n}s_i$，所以有解的必要条件为 $[s_1=1]\;{\rm and}\;[s_n=1]\;{\rm and}\;2\mid\sum\limits_{i=1}^{n}s_i$，开始时可以直接判掉。

下面来说明当特判这些条件后必有解。

考虑构造 $a,b$，其中对于 $s_i=1$ 的位置，假设有 $k$ 个，则 $a$ 和 $b$ 在这 $k$ 个 $s_i=1$ 的前 $\dfrac{k}{2}$ 个位置中都填 $\texttt{(}$，其余后 $\dfrac{k}{2}$ 的位置上都填 $\texttt{)}$。

譬如，当 $s=\{1,1,0,1,1,1,0,0,0,1\}$ 时，此时对应的 $a$ 和 $b$ 为 $a=b=\texttt{((?())???)}$，其中 $\texttt{?}$ 中的字符待定。

然后，对于 $\texttt{?}$ 所代表的字符**间接染色**，具体地，对于字符串 $a$，将第一个 $\texttt{?}$ 设置为 $\texttt{(}$，第二个 $\texttt{?}$ 设置为 $\texttt{)}$，第三个 $\texttt{?}$ 设置为 $\texttt{(}$，以此类推。$b$ 同理，只不过将 $\texttt{(}$ 和 $\texttt{)}$ 的位置互换了。

还是前面的例子，当 $s=\{1,1,0,1,1,1,0,0,0,1\}$ 时，$a=\texttt{(((()))()},b=\texttt{(()())()()}$，符合条件。

再举几个例子：

- 当 $s=\{1,0,0,1\}$ 时，$a=\texttt{(())},b=\texttt{()()}$；
- 当 $s=\{1,0,1,0,1,1\}$ 时，$a=\texttt{((()))},b=\texttt{()(())}$；
- 当 $s=\{1,0,0,1,1,0,1,1,0,1\}$ 时，$a=\texttt{(()((())))},b=\texttt{()((()))()}$；
- $\cdots\cdots$

下面来证明这种做法的正确性。

因为字符串 ${\rm str}(|{\rm str}|=m,2|m)$ 为合法的括号串的充要条件是 ${\rm cnt}_{m,\texttt{(}}-{\rm cnt}_{m,\texttt{)}}=0$（条件 $1$）且对于任意 $1\le i\le m,\sum\limits_{j=1}^{i}{\rm cnt}_{j,\texttt{(}}\ge\sum\limits_{j=1}^{i}{\rm cnt}_{j,\texttt{)}}$，其中 ${\rm cnt}_{i,j}$ 表示 $\rm str$ 前 $i$ 个字符中为 $j$ 的字符的数量（条件 $2$）。

条件 $1$ 是显而易见满足的，因为 $a$ 和 $b$ 在 $s_i=0$ 或 $s_i=1$ 的两种情况下所对应的 $k$ 或 $n-k$ 个位置上的 $\texttt{(}$ 和 $\texttt{)}$ 的数量都相等，所以总和也是相等的。

条件 $2$ 具体不好说，感性理解即可（

这样就构造出了满足题意的括号串 $a$ 和 $b$，总时间复杂度 $\mathcal{O}(\sum n)$。

### 正确代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

signed main(){
	int T;
	scanf("%d", &T);
	
	while (T--) {
		int n;
		scanf("%d", &n);
		string s;
		cin>>s;
		
		if (s[0] != '1' || s[n - 1] != '1') {
			puts("NO");
			continue;
		}
		
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			if (s[i] == '1') {
				++cnt;
			}
		}
		if (cnt & 1) {
			puts("NO");
			continue;
		}
		
		puts("YES");
		
		char a[N], b[N];
		cnt >>= 1;
		for (int i = 0; i < n; ++i) {
			if (s[i] == '1') {
				if(cnt) {
					a[i] = b[i] = '(';
					--cnt;
				} else{
					a[i] = b[i] = ')';
				}
			}
		}
		
		char now = '(';
		for (int i = 0; i < n; ++i) {
			if (s[i] == '0') {
				a[i] = now;
				now ^= '(' ^ ')';
				b[i] = now;
			}
		}
		
		for (int i = 0; i < n; ++i) {
			putchar(a[i]);
		}
		puts("");
		for (int i = 0; i < n; ++i) {
			putchar(b[i]);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：33aaron (赞：3)


## 题目大意
你有一个只包含 $0$ 和 $1$ 的字符串，你现在要把这个字符串转化为两个合法的只带有小括号的合法的字符串。（这里的合法指的是每个括号都有与其对应的前括号或者后括号）。

要求：这两个只带有小括号的字符串中位于原串中所对应 $1$ 的括号应当相同，对应 $0$ 的括号应该相反。

若可以满足要求，输出 $YES$ 并输出这两个只带有小括号的字符串；若无法满足要求，则输出 $NO$。
## 题目分析
首先想无解的情况，手动模拟一下，我们可以发现：

1、原串两头为 $0$。

2、原串有奇数个 $0$。

若有解，我们可以数出原串中前半部分的 $1$ 对应左括号，后半部分则对应右括号来处理 $1$。同时 $0$ 可以一个对应左括号一个对应右括号的处理。实现的时候，模拟此过程即可。

太蒟蒻了，第一次自己想出思路，独立做出div2 C题。可是因为每组数据处理前没有初始化答案导致上一组数据的答案未被清理掉而未在赛时AC。注意在多组测试数据中间进行初始化。
## AC Code
```Cpp
#include <iostream>
#include <string>
using namespace std;
int times;
string in, ans = "";
int l;
int main() {
    cin >> times;
    while (times--) {
        cin >> l;
        cin >> in;
        int count1 = 0, count2 = 0, d1 = 0, d2 = 0;
        if (in[0] - 48 && in[l - 1] - 48) {
            for (int i = 0; i < l; ans += " ", ++i)
                if (in[i] - 48)
                    count1++;
            if (count1 & 1) {
                cout << "NO\n";
                continue;
            }
            for (int i = 0; i < l; ++i)
                if (in[i] - 48) {
                    d1++;
                    if (d1 <= count1 / 2) ans[i] = '(';
                    else ans[i] = ')';
                } else {
                    d2++;
                    if (d2 & 1) ans[i] = '(';
                    else ans[i] = ')';
                }
            cout << "YES\n";
            cout << ans << endl;
            for (int i = 0; i < l; ++i)
                if (in[i] - 48 == 0) {
                    if (ans[i] == ')') ans[i] = '(';
                    else ans[i] = ')';
                }
            cout << ans << endl;
            ans = ""; //答案清零
       } else cout << "NO\n";
    }
    return 0;
}
```

---

## 作者：Cry_For_theMoon (赞：3)

[传送门](https://codeforces.ml/contest/1503/problem/A)

这个 1600* 的2C 比我做过的几个 2000 构造都难感觉。（但是听说大家都乱搞过去了）。

这个位置的构造题的套路：

1. 先去判几个naive的无解的情况。

2. 当你无解找的差不多的时候就直接构造。

思考后得出四种无解情况：

- $s_1\neq1$

- $s_n\neq1$

- $2\nmid n$

- $2\nmid \sum [s_i=1]$

显然它们构造不出合法括号。

可能第四点不太显然，但我们稍后会再次提到它。

经典性质：对于一个括号串，我们扫描它，左括号 $+1$，右括号 $-1$。则这个括号串合法等价于在任何时候和都非负，且扫描结束后和为 $0$.

条件 $2$ 告诉我们：左括号和右括号数量一样，由此推导出上面第三条。如果 $1$ 的数量为奇数，$1$ 部分求和是奇数，则 $0$ 部分的结果和 $0$ 部分的结果反转都得是奇数，而这是不可能的，因此也就无法做到整题和为 $0$. 所以三四条得到了证明。 

那么剩下的情况我们怎么去构造一个解呢。这里我发现我比赛的写法和官方题解竟出奇地想象。

对于 $1$ 的位置，前一半我们填左括号，后一半我们填右括号。

对于 $0$ 的位置，我们交替在 $a$ 中填（第一个填右括号，第二个填左括号，以此类推）。$b$ 即是 $a$ 取反的结果。

不难发现它既保证了全局和为 $0$，也保证了不管什么时候和都非负。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=2e5+10;
pi a[MAXN];
ll n,ans,idx,pre[MAXN]; 
int LowerBound(int val){
	//最后一个小于等于val的 
	int L=1,R=n,ans=n;
	while(L<=R){
		int mid=(L+R)>>1;
		if(a[mid].fr<=val){
			ans=mid;
			L=mid+1;
		}else{
			R=mid-1;
		}
	}
	return ans;
}
int main(){
	cin>>n;
	rep(i,1,n){
		cin>>a[i].fr>>a[i].se;ans+=a[i].se;
	} 
	sort(a+1,a+1+n);
	rep(i,1,n){
		pre[i]=Max(pre[i-1],a[i].fr+a[i].se);
	}
	idx=1;
	while(idx<n){
		int pos=LowerBound(pre[idx]);
		if(pos==n)break;
		//拓展到pos+1
		ans+=Max(0,a[pos+1].fr-pre[pos]); 
		idx=pos+1;
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：lzy120406 (赞：1)

## [原题](https://codeforces.com/problemset/problem/1294/D)
我们需要构造两个平衡的括号序列 $a$ 和 $b$，使得：

- 如果 $s_i = 1$，则 $a_i = b_i$。

- 如果 $s_i = 0$，则 $a_i \ne b_i$。

## 思路
平衡的括号序列需要满足每个左括号 `(` 都有一个对应的右括号 `)`。

- 对于 $s_i = 1$ 的位置，则 $a_i$ 和 $b_i$ 必须相同。

- 对于 $s_i = 0$ 的位置，则 $a_i$ 和 $b_i$ 必须不同。

显然，如果 $s$ 中 `1` 的数量是奇数，则无法构造满足条件的序列，因为每个 `1` 需要成对出现。

容易想到一种构造方法：

1. 将 $s$ 中的 `1` 分成两半，前一半为 `(`，后一半为 `)`。

2. 将 $s$ 中的 `0` 交替分配给 $a$ 和 $b$。

具体细节看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
	int n;
	string s;
	cin >> n >> s;
	// 统计 1 的数量
	int count1 = 0;
	for (char c : s) {
		if (c == '1') {
			count1++;
		}
	}
	// 如果 1 的数量是奇数，无法构造
	if (count1 % 2 != 0) {
		cout << "NO\n";
		return;
	}
	// 构造 a 和 b
	string a(n, ' '), b(n, ' ');
	int half1 = count1 / 2;
	int flip = 0;
	for (int i = 0; i < n; ++i) {
		if (s[i] == '1') {
			if (half1 > 0) {
				a[i] = '(';
				b[i] = '(';
				half1--;
			} else {
				a[i] = ')';
				b[i] = ')';
			}
		} else {
			if (flip == 0) {
				a[i] = '(';
				b[i] = ')';
			} else {
				a[i] = ')';
				b[i] = '(';
			}
			flip = 1 - flip;
		}
	}
	// 检查 a 和 b 是否平衡
	int balanceA = 0, balanceB = 0;
	for (int i = 0; i < n; ++i) {
		if (a[i] == '(') {
			balanceA++;
		} else {
			balanceA--;
		}
		if (b[i] == '(') {
			balanceB++;
		} else {
			balanceB--;
		}
		if (balanceA < 0 || balanceB < 0) {
			cout << "NO\n";
			return;
		}
	}
	if (balanceA != 0 || balanceB != 0) {
		cout << "NO\n";
		return;
	}
	cout << "YES\n";
	cout << a << '\n';
	cout << b << '\n';
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
```
时间复杂度 $ \mathcal{O}(tn) $，本题中 $\sum{n} \leq 2 \times 10^5$，可以通过本题。

---

## 作者：Wallacewwz (赞：1)

# CF1503A Balance the Bits 题解

## 题目大意

给定一个长度为 $n$ 的数组 $s$，要求构造两个由括号组成的序列 $a$ 和 $b$。

这两个序列需要满足以下条件：

1. 序列 $a$ 和 $b$ 均为合法括号序列，例如 $()$ 是合法的，而 $)($ 是不合法的。
2. 当 $s[i] = 1$ 时，$a[i] = b[i]$；当 $s[i] = 0$ 时，$a[i] \neq b[i]$。

## 解题思路

首先，我们需要进行特判，排除无法构造的情况：

- 如果 $s$ 数组的首元素或尾元素为 $0$，则无法构造合法的括号序列。因为首元素必须是左括号，尾元素必须是右括号，因此两个序列的头尾必须一致，不能出现不一致的情况。
- 如果 $s$ 数组中 $1$ 的数量为奇数，则无法满足条件 $a[i] = b[i]$。因为 $a$ 和 $b$ 中对应位置的括号需要保持一致，而 $1$ 的数量为奇数时无法均分。

在排除掉上述不合法的情况之后，我们可以开始构造序列。

我们可以先构造序列 $a$：

- 对于 $s[i] = 1$ 的情况，如果该 $1$ 在所有 $1$ 中的前半部分，则使用左括号 `(`，否则使用右括号 `)`。（即前半部分使用左括号，后半部分使用右括号）
- 对于 $s[i] = 0$ 的情况，按照奇数个和偶数个的顺序，依次使用左括号 `(` 或右括号 `)`。

构造完序列 $a$ 后，再根据 $s$ 数组中的值进行转换，得到序列 $b$。

## 代码

```cpp
#include <bits/stdc++.h>
//#pragma GCC optimize(2)
//#define int long long
#define endl '\n'
#define ll long long
#define ull unsigned long long
using namespace std;

vector<char> ans;

void solve() {
    int n;
    string s;
    
    cin >> n;
    cin >> s;
    
    s = ' ' + s;  // 让下标从 1 开始，个人习惯
    
    // 特判：头尾为 0
    if (s[1] == '0' || s[n] == '0') {
        cout << "NO" << endl;
        return;
    }
    
    int cnt = 0;
    
    // 统计 1 的数量
    for (int i = 1; i <= n; i++) {
        if (s[i] == '1') cnt++;
    }
    
    // 特判：1 的数量为奇数
    if (cnt % 2 == 1) {
        cout << "NO" << endl;
        return;
    }

    ans.clear();  // 清空 ans，ans 用于记录序列 a，以便后续生成序列 b
    
    cout << "YES" << endl;
    
    // 构造序列 a
    int cnt1 = 0, cnt2 = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] == '1') {
            cnt1++;
            if (cnt1 <= cnt / 2) {
                cout << "(";
                ans.push_back('(');
            } else {
                cout << ")";
                ans.push_back(')');
            }
        } else {
            cnt2++;
            if (cnt2 % 2 == 1) {
                cout << "(";
                ans.push_back('(');
            } else {
                cout << ")";
                ans.push_back(')');
            }
        }
    }
    cout << endl;
    
    // 根据序列 a 转换为序列 b
    for (int i = 0; i < ans.size(); i++) {
        if (s[i + 1] == '1') {
            cout << ans[i];
        } else {
            if (ans[i] == '(') cout << ")";
            else cout << "(";
        }
    }
    cout << endl;
    return;
}

signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    
    // 多组测试
    while (T--) {
        solve();
    }
    
    return 0;
}

---

## 作者：Hooch (赞：0)

### 题目大意

给定一个长度为 $n$ 的 01 字符串 $s$。要求你构造两个**合法的括号序列** $a$ 和 $b$。

对于每一个 $s_i=1$，要求 $a_i=b_i$，反之 $s_i=0$，要求 $a_i\ne b_i$。

### 思路

我们用 $f_{0,i}$ 表示 $a_i$ 的括号序列状态。

还需要左括号就 $-1$，否则需要右括号 $+1$。

用 $f_{1,i}$​ 表示 $b_i$​ 的括号序列状态。

我们可以发现当 $s_i=0$​​ 时，两个括号序列中的一个的 $[1,i-1]$ 一定是不合法的。

 也就是说 $f_{0,i}>0$ 或者 $f_{1,i}>0$。

如果 $f_{0,i} > f_{1,i}$​ 就在 $b$ 放左括号，在 $a$ 放右括号。​ 

同理可得 $f_{0,i} < f_{1,i}$ 时。

当 $s_i=1$ 时，我们不难想到一个**贪心策略**​​。

当 $f_{0,i}>0$ 且 $f_{1,i}>0$ 时，两边都放右括号。

否则都放左括号。

说白了就是：**能放就放**。

但是还有一个漏洞，就是这种情况：

`110101`

能放就放的话就会发现 $i=3$ 时没处放了。

于是我们要**特判** $s_{i+1}=0$ 时的情况。

### 代码

实现按照上述思路即可。

代码：

```cpp
#include <bits/stdc++.h>
#define rep1(i, j, n) for (register int i = j; i <= int(n); ++i)
#define rep2(i, j, n) for (register int i = j; i >= int(n); --i)
using namespace std;
const int Buffer_Size = 1 << 10;
char buffer[Buffer_Size], *ihead = buffer + Buffer_Size, *itail = ihead;
inline char Next_Char() {
    if (ihead == itail) fread(buffer, 1, Buffer_Size, stdin), ihead = buffer;
    return *ihead++;
}
template <typename T>
inline void read(T &x) {
    x = 0; T f = 1; char ch = Next_Char();
    while (!isdigit(ch)) {if (ch == '-') f = -1; ch = Next_Char();}
    while (isdigit(ch)) {x = (x << 1) + (x << 3) + (ch & 15); ch = Next_Char();} x *= f;
}
inline void readstr(string &s) {
    s = ""; char ch = Next_Char();
    while (ch == ' ' || ch == '\n') ch = Next_Char();
    while (ch ^ ' ' && ch ^ '\n') s += ch, ch = Next_Char();
}
const int N = 2e5 + 5, inf = 0x3f3f3f3f, mod = 1;
int t, n, f1, f2; string s, ans1, ans2;
signed main(void) {
	read(t); 
	while (t--) {
		read(n); readstr(s); ans1 = ans2 = ""; f1 = f2 = 0; bool flg = 0;
		s[n] = 'f';
		rep1(i, 0, n - 1) 
			if (s[i] == '0') //s[i]=0时
				if (f1 == f2 && f1 == 0) {flg = 1; break;}//不能放了
				else if (f1 < f2) {
					ans1 += '(';
					ans2 += ')';
					--f2; ++f1;
				} else {
					ans2 += '(';
					ans1 += ')';
					++f2; --f1;
				}
			else 
				if (f1 && f2 && !(f1 == 1 && f2 == 1 && s[i + 1] == '0')) { // 特判特殊情况
					--f1; --f2;
					ans1 += ')'; // 能放就放
					ans2 += ')';
				} else {
					++f1; ++f2;
					ans1 += '(';
					ans2 += '(';
				}
		if (!f1 && !f2 && !flg) { //判断括号序列合法
			puts("YES");
			cout << ans1 << endl;
			cout << ans2 << endl;
		} else puts("NO");
	}
}
```

---

## 作者：Werner_Yin (赞：0)


[Cnblogs](https://www.cnblogs.com/werner-yin/p/14782905.html)

[CSDN](https://blog.csdn.net/m0_45912574/article/details/117001702)
# Problem
[CF](https://codeforces.com/contest/1504/problem/C)

[luogu](https://www.luogu.com.cn/problem/CF1503A)

# Solution
提供一种奇怪的乱搞做法，~~求叉~~

没有怎么找特殊性质，就是边构造边判断。

考虑一个无解的充分条件，从左往右构造，把所有 1 都给两个串都填上左括号，所有 0  给当前未匹配的左括号少的串填上左括号，另一个填上右括号，如果最终还有未匹配的右括号时，一定无解。

这一部分的代码：
```cpp
int lef1 = 0,lef2 = 0;
for(int i = 1;i <= n;i++)
	if(s[i] == '1'){
		a[i] = b[i] = '(';
		lef1++; lef2++;
	}else{
		if(lef1 && lef2){
			if(lef1 > lef2){
				a[i] = ')'; b[i] = '(';
				lef1--; lef2++;
			}else{
				a[i] = '('; b[i] = ')';
				lef1++; lef2--;
			}
		}else if(lef1){a[i] = ')'; b[i] = '('; lef1--; lef2++;}
		else if(lef2){a[i] = '('; b[i] = ')'; lef1++; lef2--;}
		else return puts("NO"),void();
	}	
```

考虑让这个串合法：

从右往左扫，把同时填了两个 ```(```的位置改为两个 ```)```，直到满足条件，
最后再判断一下无解的情况即可。

大概是因为修改更后面的对于前面的影响更小。

# Code
```cpp
#define in read()

const int N = 2e5+10;

int n;
char s[N],a[N],b[N];

void solve(){
	n = in; scanf("%s",s + 1); 
	int lef1 = 0,lef2 = 0;
	for(int i = 1;i <= n;i++)
		if(s[i] == '1'){
			a[i] = b[i] = '(';
			lef1++; lef2++;
		}else{
			if(lef1 && lef2){
				if(lef1 > lef2){
					a[i] = ')'; b[i] = '(';
					lef1--; lef2++;
				}else{
					a[i] = '('; b[i] = ')';
					lef1++; lef2--;
				}
			}else if(lef1){a[i] = ')'; b[i] = '('; lef1--; lef2++;}
			else if(lef2){a[i] = '('; b[i] = ')'; lef1++; lef2--;}
			else return puts("NO"),void();
		}
	int g1 = lef1,g2 = lef2; if(g1 != g2) return puts("NO"),void();
	lef1 = lef2 = 0;
	for(int i = n;i >= 1;i--){
		if(a[i] == b[i] && b[i] == '('){
			if(g1 && g2) g1 -= 2,g2 -= 2,a[i] = ')',b[i] = ')';
		}
		
	}
	lef1 = lef2 = 0;
	for(int i = 1;i <= n;i++){
		if(a[i] == '(') lef1++; else lef1--;
		if(b[i] == '(') lef2++; else lef2--;
		if(lef1 < 0 || lef2 < 0) return puts("NO"),void();
	}
	if(lef1 || lef2 || g1 || g2) return puts("NO"),void();
	puts("YES");
	for(int i = 1;i <= n;i++) putchar(a[i]); puts("");
	for(int i = 1;i <= n;i++) putchar(b[i]); puts("");
}

int main(){
	for(int t = in;t;t--) solve();
	return 0;
}
```

顺便一问，有人能叉掉这种做法吗 ？

---

## 作者：kradcigam (赞：0)

题目翻译：

构造两个合法的括号序列，使得这两个括号序列第 $i$ 个字符相同当且仅当 $a_i=1$。

做法：

假设 $a$ 中有 $s1$ 个 $0$，$s2$ 个 $1$。两个括号序列字符总量是一样的，所以两个括号序列左括号个数也是一样的。$s2$ 中的字符是一样的，所以 $s1$ 必须是偶数。

然后考虑边构造边判断，尽量让两个字符串的左括号个数相等，所以就给第一个字符串添加一个左括号，给第二个字符串添加一个右括号、给第一个字符串添加一个右括号，给第二个字符串添加一个左括号……$s2$ 中先把左括号添完，然后在添右括号。

代码：
```cpp
#include<bits/stdc++.h>
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define LL long long
#define mp make_pair
#define SZ(x) ((int)x.size()-1)
#define ms(a,b) memset(a,b,sizeof a)
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define DF(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read(){
	char ch=getchar(); int w=1,c=0;
	for(;!isdigit(ch);ch=getchar()) if (ch=='-') w=-1;
	for(;isdigit(ch);ch=getchar()) c=(c<<1)+(c<<3)+(ch^48);
	return w*c;
}
const int N=2e5+10;
int a[N],f1[N],f2[N];
int main(){
	int _=read();while(_--){
		int n=read(),s1=0,s2=0;
		string a;
		cin>>a;
		F(i,0,SZ(a))
			if(a[i]=='1')s2++;
			else s1++;
		if(s1&1)puts("NO");
		else{
			int x1=0,x2=0;
			string st1="",st2="";
			int l1=0,l2=0;bool fg=true;
			F(i,0,SZ(a)){
				if(a[i]=='1'){
					if(++x2<=s2/2)f1[i]=f2[i]=1,l1++,l2++;
					else f1[i]=f2[i]=0,l1--,l2--;
				}else{
					if((++x1)&1)f1[i]=1,f2[i]=0,l1++,l2--;
					else f1[i]=0,f2[i]=1,l1--,l2++;
				}
				if(l1<0||l2<0){
					fg=false;
					break;
				}
			}
			if(fg&&l1==0&&l2==0){
				puts("YES");
				F(i,0,SZ(a))
					if(f1[i])putchar('(');
					else putchar(')');
				puts("");
				F(i,0,SZ(a))
					if(f2[i])putchar('(');
					else putchar(')');
				puts("");
			}else puts("NO");
		}
	}
	return 0;
}
```

---

