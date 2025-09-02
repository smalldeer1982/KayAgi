# [ARC175B] Parenthesis Arrangement

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc175/tasks/arc175_b

長さ $ 2N $ の `(`, `)` からなる文字列 $ S $ が与えられます．$ S $ の左から $ i $ 番目の文字を $ S_i $ と表します．

あなたは以下の $ 2 $ 種類の操作を好きな順番で $ 0 $ 回以上好きな回数行うことができます．

- $ 1\leq\ i\ <\ j\ \leq\ 2N $ を満たす整数組 $ (i,j) $ を選ぶ．$ S_i $ と $ S_j $ を入れ替える．この操作にはコストが $ A $ かかる．
- $ 1\leq\ i\ \leq\ 2N $ を満たす整数 $ i $ を選ぶ．$ S_i $ を `(` または `)` で置き換える．この操作にはコストが $ B $ かかる．
 
あなたの目標は $ S $ を正しい括弧列にすることです．目標を達成するために必要なコストの総和の最小値を求めてください．なお，有限回の操作で必ず目標を達成できることが証明できます．

  正しい括弧列とは 正しい括弧列とは，以下のいずれかの条件を満たす文字列です． - 空文字列
- ある正しい括弧列 $ A $ が存在して，`(`, $ A $, `)` をこの順に結合した文字列
- ある空でない正しい括弧列 $ S,T $ が存在して，$ S,T $ をこの順に結合した文字列

## 说明/提示

### 制約

- 入力される数値は全て整数
- $ 1\ \leq\ N\ \leq\ 5\times\ 10^5 $
- $ 1\leq\ A,B\leq\ 10^9 $
- $ S $ は長さ $ 2N $ の `(`, `)` からなる文字列
 
### Sample Explanation 1

操作の一例を示します． - $ S_3 $ と $ S_4 $ を入れ替える．$ S $ は `))()()` となる．コストが $ 3 $ かかる． - $ S_1 $ を `(` で置き換える．$ S $ は `()()()` となり，これは正しい括弧列である．コストが $ 2 $ かかる． この例では，$ S $ を正しい括弧列にするのにかかったコストの総和が $ 5 $ です．コストの総和が $ 5 $ 未満で $ S $ を正しい括弧列にする操作方法は存在しません．

### Sample Explanation 2

入力の $ S $ は既に正しい括弧列なので，操作を行う必要はありません．

## 样例 #1

### 输入

```
3 3 2
)))(()```

### 输出

```
5```

## 样例 #2

### 输入

```
1 175 1000000000
()```

### 输出

```
0```

## 样例 #3

### 输入

```
7 2622 26092458
))()((((()()((```

### 输出

```
52187538```

# 题解

## 作者：whrwlx (赞：3)

# 题意

给出一个括号序列 $s$，有两种操作方式，交换两个字符需要花费 $A$，直接修改一个字符需要花费 $B$，求使这个序列合法需要的最小花费。

# 分析

我们可以先将 $s$ 中能匹配的括号序列消除掉（即括号匹配）。

最后的字符串会由 $l$ 个 `)` 和 $r$ 个 `(` 组成。

这个时候我们可以发现交换两个字符和在原串交换是等价的。

那么我们可以贪心。

我们可以考虑：

- 先把可以交换的交换，然后替换剩下不可交换的。

- 全部替换。

最后取最小值即可。

```c++
#include<bits/stdc++.h>
#define int long long
#define fd(i,a,b) for(int i=a;i<=b;i=-~i)
using namespace std;
int a,b,n,l,r,tot=0;
char s[10001000],q[10001000];
//自带的stack会RE(考后才发现)
//1e7 会爆栈！！！
void push(char ch){q[++tot]=ch;}
char top(){return q[tot];}
void pop(){if(tot>0) --tot;}
bool empty(){return tot>0?0:1;}
//以上是手写栈（dalao勿喷）
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>a>>b;
	cin>>s[1];
	push(s[1]);
	fd(i,2,n*2)
	{
		cin>>s[i];
		if(top()=='('&&s[i]==')') pop();
		else push(s[i]);
	}
	if(empty())
	{
		cout<<0;
		return 0;
	}
	while(!empty())
	{
		if(top()=='(') r++;
		else l++;
		pop();
	}
	if(l>r) swap(l,r);
	if(l&1) cout<<min((l+1)/2*a+(r-l)/2*b,(l+r)/2*b+b);
	else cout<<min((l+1)/2*a+(r-l)/2*b,(l+r)/2*b);
	return 0;
}
```

---

## 作者：tXX_F (赞：3)

# Parenthesis Arrangement

## 解题思路

先用一个字符串顺序存下不符合题目要求的括号，然后分别记录下其中左括号和有括号的数量。如果交换括号对的代价小于改变一对括号的代价，即 $A < B \times 2$，那么就交换否则替换。若交换后仍然有剩余的括号，则只能进行替换。若剩下的左括号数量不为 $2$ 的倍数，则须再单独取出一个括号替换。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
long long N, A, B;
string S;
long long Answer;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0), cin >> N >> A >> B >> S;
	string s;
	for (int i = 0, count_left = 0; i < S.size(); i++) {
		if (S[i] == '(') count_left++, s.push_back('(');
		if (S[i] == ')') if (count_left >= 1) count_left--, s.pop_back();
			else s.push_back(')');
	}
	long long left_count = 0, right_count = 0;
	for (int i = 0; i < s.size(); i++) if (s[i] == '(') left_count++;
		else if (s[i] == ')') right_count++;
	if (left_count && right_count && A < B * 2) {
		int _min = min(left_count, right_count);
		Answer += _min / 2 * A;
		if (_min % 2 == 1) Answer += A;
		left_count -= _min, right_count -= _min;
	}
	if (left_count) Answer += left_count / 2 * B;
	if (right_count) Answer += right_count / 2 * B;
	if (left_count & 1) Answer += 2 * B;
	cout << Answer << endl;
	return 0;
}
```

---

## 作者：tXX_F (赞：3)

# Parenthesis Arrangement

## 解题思路

先用一个字符串顺序存下不符合题目要求的括号，然后分别记录下其中左括号和有括号的数量。如果交换括号对的代价小于改变一对括号的代价，即 $A < B \times 2$，那么就交换否则替换。若交换后仍然有剩余的括号，则只能进行替换。若剩下的左括号数量不为 $2$ 的倍数，则须再单独取出一个括号替换。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
long long N, A, B;
string S;
long long Answer;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0), cin >> N >> A >> B >> S;
	string s;
	for (int i = 0, count_left = 0; i < S.size(); i++) {
		if (S[i] == '(') count_left++, s.push_back('(');
		if (S[i] == ')') if (count_left >= 1) count_left--, s.pop_back();
			else s.push_back(')');
	}
	long long left_count = 0, right_count = 0;
	for (int i = 0; i < s.size(); i++) if (s[i] == '(') left_count++;
		else if (s[i] == ')') right_count++;
	if (left_count && right_count && A < B * 2) {
		int _min = min(left_count, right_count);
		Answer += _min / 2 * A;
		if (_min % 2 == 1) Answer += A;
		left_count -= _min, right_count -= _min;
	}
	if (left_count) Answer += left_count / 2 * B;
	if (right_count) Answer += right_count / 2 * B;
	if (left_count & 1) Answer += 2 * B;
	cout << Answer << endl;
	return 0;
}
```

---

## 作者：KSCD_ (赞：2)

# 题意
给出一个括号序列，有两种操作方式，交换两个字符需要 $A$ 的代价，直接修改一个字符需要 $B$ 的代价，求使这个序列合法需要的最小代价。
# 思路
这题看上去好像是dp，但是复杂度显然不太对。

我们发现，交换相当于两次修改；而若把一个左括号改成右括号，再把一个右括号改成左括号，就相当于把这两个字符交换。

这样就可以先无脑修改，记录下修改为左括号和右括号的次数，最后再处理一下可以转换成交换操作的数量即可。

因此从左到右操作，若碰到左括号则压入栈中；碰到右括号时，若栈中有左括号则弹出一个与之匹配，若没有则只能修改成左括号并压入栈中，同时记录一下修改为左括号的次数。

最后若栈中还剩 $k$ 个左括号，显然此时 $k$ 一定为偶数。那么需要把其中 $\frac{k}{2}$ 个改成右括号以令其匹配，那么 $\frac{k}{2}$ 就是修改为右括号的次数。

此处由于只有左括号会被压入栈中，所以不需要开栈存储，只需要记录一下栈中的左括号数量即可。

最后可以把两种修改各一次转换为交换，贪心求出答案即可。
# 代码
```cpp
#include<iostream>
#define int long long
using namespace std;
const int N=1e6+10;
int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){ if(ch=='-') w=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){ s=s*10+ch-'0'; ch=getchar();}
    return s*w;
}
int n,a,b,sl,sr,sn;//sl sr为修改为左/右括号的次数，sn为栈中的左括号数量 
char s[N];
signed main()
{
	n=read(),a=read(),b=read();
	cin>>s;
	for(int i=0;i<2*n;i++)
	{
		if(s[i]==')')
		{
			if(sn) sn--;
			else sl++,sn++;
		}
		else sn++;
	}//如上述，记录修改为左括号次数 
	if(sn) sr=sn/2;//计算修改为右括号次数 
	if(sl<sr) swap(sl,sr);//使sl为较大值 
	if(b*2<=a) cout<<(sl+sr)*b;//若两次修改代价小于交换，则全用修改 
	else cout<<sr*a+(sl-sr)*b;//否则把能转换的修改全部转换 
	return 0;
}
```

---

## 作者：JuRuoOIer (赞：1)

# 题解 ARC175B - Parenthesis Arrangement

[**A 题题解**](https://www.luogu.com.cn/article/uo5w1jmg/)

前排提示：本题解为 **贪心** 做法。

### 题意

已提交翻译。

给定长度为 $2n$ 的只包含左右小括号的字符串 $S$，现在可以进行任意次操作，每次操作可以：
- 选择 $1 \le i,j \le 2n$，并交换 $S_i$ 和 $S_j$，代价为 $a$。
- 选择 $1 \le i \le 2n$，并修改 $S_i$ 的值，代价为 $b$。

求使 $S$ 成为括号匹配串的最小代价。

数据范围：$n \le 5\times10^5,a,b \le 2\times10^9$。

### 做法

首先我们看一下 $S$ 中左右括号数量是否相同，若不同则对多的那种进行修改直到两种一样。这里我们为了后面交换尽量少，
- 如果需要把 `(` 变成 `)`，则从后往前找；
- 如果需要把 `)` 变成 `(`，则从前往后找。

这样我们可以尽量的使左括号到前面，右括号到后面。

接着进入交换阶段。

首先如果 $a>2b$ 则 $a\leftarrow 2b$，因为此时交换还不如把两边都修改了。

接着开始扫，记录一个 `cnt` 表示当前未匹配上的左括号处，同时记录一个指针 `p` 表示最右边的左括号的位置。如果某一时刻 `cnt<0`，则当前位置的右括号要与最右边的左括号进行交换（还是尽量让右括号往右），同时将 `p` 移到上一个左括号的位置。

扫的时候顺手统计下答案，就结束了。因为一共只扫了几遍字符串，所以时空复杂度均为 $O(n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
#include<vector>
#include<map>
#include<set>
#include<cstring>
#include<string>
#define ll long long
#define ull unsigned long long
#define lf double
#define ld long double
using namespace std;
ll n,a,b,ans,cnt,pos;
char s[1000010];
int main(){
	cin>>n>>a>>b>>s;
	n*=2;
	pos=n-1;
	a=min(a,b*2);
	//扫一遍看需要修改哪些
	for(int i=0;i<n;i++){
		if(s[i]=='(')cnt++;
		else cnt--;
	}
	ans=abs(cnt/2)*b;
	//修改时尽量让左括号往左，右括号往右
	if(cnt<0){
		cnt=-cnt;
		for(int i=0;i<n;i++){
			if(s[i]==')'){
				s[i]='(';
				cnt-=2;
				if(!cnt)break;
			}
		}
	}
	else if(cnt>0){
		for(int i=n-1;i>=0;i--){
			if(s[i]=='('){
				s[i]=')';
				cnt-=2;
				if(!cnt)break;
			}
		}
	}
	cnt=0;
	for(int i=0;i<n;i++){
		if(s[i]=='(')cnt++;
		else{
			cnt--;
			if(cnt<0){
				while(s[pos]!='('){
					pos--;//找到最右边的左括号
				}
				swap(s[pos],s[i]);//交换
				ans+=a;
				cnt+=2;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：zcr0202 (赞：0)

## 题目大意

给你一个括号序，有两种操作，每种操作有不同的代价，求使它变成一个合法的括号序。

## 解题思路

这道题可以用贪心。首先我们把左括号和右括号的个数变相同，同时变左括号要尽量靠左，右括号同理。之后我们再用栈来判断哪一个右括号不合法，那我们就把它和从右往左数的第一个左括号交换，那么代价可以证明是最优的。

## Code

```
#include<bits/stdc++.h>
#define int long long
#define ready() ios::sync_with_stdio(0), cout.tie(0), cout.tie(0);
#define fre(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout);
#define up(i, a, b) for(int i = a; i <= b; i++)
#define down(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 5e5 + 5;
const int mod = 1e9 + 9;
int l, s1, s2, ans, ss1, ss2, sum;
string a;
signed main() {
	cin >> l >> ss2 >> ss1;
	cin >> a;
	a = ' ' + a;
	l *= 2;
	up(i, 1, l) {
		if(a[i] == '(') s1++;
		if(a[i] == ')') s2++;
	}
	sum = (s1 - s2) / 2;
	if(sum < 0) {
		sum = abs(sum);
		up(i, 1, l) {
			if(sum == 0) break;
			if(a[i] == ')') {
				a[i] = '(';
				ans += ss1;
				sum--;
			}
		}
	}
	else if(sum > 0) {
		down(i, l, 1) {
			if(sum == 0) break;
			if(a[i] == '(') {
				a[i] = ')';
				ans += ss1;
				sum--;
			}
		}
	}
	up(i, 1, l) {
		if(a[i] == '(') sum++;
		if(a[i] == ')') sum--;
		if(sum < 0) {
			int t = l;
			while(1) {
				if(a[t] == '(') {
					swap(a[i], a[t]);
					ans += ss2;
					sum += 2;
					break;
				}
				t--;
			}
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：CodingOIer (赞：0)

## [ARC175B] Parenthesis Arrangement 题解

### 思路分析

由于交换两个**不同**元素相当于对其各自取反，所以 $a = \min(a, 2 \times b)$。

接着，我们可以将原来的序列化简成 $\texttt{))))))))((((((}$ 的形式，使用栈实现。

```cpp
for (int i = 1; i <= n; i++)
{
    if (!stack.empty() && stack.top() == '(' && s[i] == ')')
    {
        stack.pop();
    }
    else
    {
        stack.push(s[i]);
    }
}
int m = stack.size();
for (int i = m; i >= 1; i--)
{
    t[i] = stack.top();
    stack.pop();
}
```

我们便可以将现在的序列化简为 $left$ 和 $right$，分别表示左括号和右括号的个数。

考虑这个列子：

$\texttt{)))(((((}$

此时，我们交换 $s_1$ 与 $s_8$，即消去 $4$ 个序列元素， $left \gets left - 2, right \gets right - 2, answer \gets answer + a$。

接着，我们会得到：

$\texttt{)(((}$

由于上文对 $a$ 取了最小值，所以交换一定优于修改，所以交换 $s_1$ 与 $s_4$，消去 $2$ 个序列元素，$left \gets left - 1, right \gets right - 1, answer \gets answer + a$。

最后，一定是一段仅有 $\texttt{(}$ 或 $\texttt{)}$ 的序列，我们只能修改 $\frac{|t|}{2}$ 次来使其匹配。所以 $answer \gets answer + \frac{left + right}{2} \times b$。

### 代码实现

记得开 `long long`。

```cpp
#include <cmath>
#include <cstdio>
#include <stack>
constexpr int MaxN = 1e6 + 5;
int n, a, b;
char s[MaxN];
char t[MaxN];
std::stack<char> stack;
int main()
{
    scanf("%d%d%d", &n, &a, &b);
    n *= 2;
    scanf("%s", s + 1);
    a = std::min(a, 2 * b);
    for (int i = 1; i <= n; i++)
    {
        if (!stack.empty() && stack.top() == '(' && s[i] == ')')
        {
            stack.pop();
        }
        else
        {
            stack.push(s[i]);
        }
    }
    int m = stack.size();
    for (int i = m; i >= 1; i--)
    {
        t[i] = stack.top();
        stack.pop();
    }
    int left, right;
    left = 0;
    right = 0;
    for (int i = 1; i <= m; i++)
    {
        if (t[i] == '(')
        {
            left++;
        }
        else if (t[i] == ')')
        {
            right++;
        }
    }
    long long answer = 0;
    long long use = abs(m / 2 - left);
    for (; right >= 2 && left >= 2;)
    {
        right -= 2;
        left -= 2;
        answer += a;
    }
    if (left > 0 && right > 0)
    {
        left--;
        right--;
        answer += a;
    }
    long long still = left + right;
    still /= 2;
    answer += still * b;
    printf("%lld\n", answer);
    return 0;
}
```

---

## 作者：I_will_AKIOI (赞：0)

太菜了，只会 B，来写题解纪念了。

### 题目大意

给你一个长度为 $2n$ 的括号序列 $s$，你可以花费 $a$ 的代价交换 $s$ 中的两个字符，或者花费 $b$ 的代价修改 $s$ 中的一个字符。求将这个串变成合法括号序列的最小花费。

首先我们发现我们可以先将 $s$ 中能匹配的括号序列消除掉。最后的字符串会由 $x$ 个 `)` 和 $y$ 个 `(` 拼成。这个时候交换两个字符和在原串交换是等价的。

接下来我们把这个串给变成合法串。首先如果 $x\ge y$，那么先交换。然后若 $x>1$，我们则考虑一次消掉两对括号。例如样例 $3$，可以变成 `))((((((`。这个时候交换第 $1$ 个和第 $4$ 个，就可以消掉两对括号。最后使用第二种操作消掉剩下的括号。

或者我们可以直接全部用第二种操作，花费是 $\displaystyle y\lfloor\frac{x+y}{2}\rfloor$。然后二者取最小值即可。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,y,len,cnt1,cnt2,ans1,ans2;
char a[1000005];
signed main()
{
  ios::sync_with_stdio(0);
  cin>>n>>x>>y;
  n*=2;
  for(int i=1;i<=n;i++)
  {
    char c;
    cin>>c;
    if(len>0&&a[len]=='('&&c==')') len--;
    else a[++len]=c;
  }//消除合法串
  for(int i=1;i<=len;i++)
  {
    if(a[i]==')') cnt1++;
    else cnt2++;
  }
  if(cnt1>cnt2) swap(cnt1,cnt2);
  ans1=x*(cnt1/2+cnt1%2)+(cnt2-cnt1)/2*y;//第一种操作
  ans2=(cnt1+cnt2)/2*y;//第二种操作
  if(cnt1&1) ans2+=y;
  cout<<min(ans1,ans2);
  return 0;
}
```

---

## 作者：JackMerryYoung (赞：0)

# 前言

怎么感觉比 A 简单。

# 正文

把 `(` 视作 $1$，把 `)` 视作 $-1$，此时我们发现括号序列匹配的条件是：

1. `(` 与 `)` 数目必然相等

2. 括号序列最小和为 $0$

那么显然，交换括号的操作不改变第一个条件的满足情况。问题就落在如何用改变括号的操作满足第二个条件。

设 `(` 个数为 $cnt_l$，`)` 个数为 $cnt_r$，那么显然改变括号的操作必然有 $\dfrac{|cnt_l - cnt_r|}{2}$

显然，如果我们要把 `(` 改成 `)`，一定是从右往左改；如果我们要把 `)` 改成 `(`，一定是从左往右改。

接下来考虑第二个条件：对于每一个交换，都是最左的 `)` 与最右的 `(`，此操作会让括号序列最小和加上 $2$。

设操作完后括号序列最小和为 $p$，因此需要步数为 $\lceil\dfrac{-p}{2}\rceil$。

还有一个需要特判的点：两个修改等同于一次交换，因此还需要特判一下。（有人因为这个吃了 $4$ 发罚时警钟长鸣）

# 代码

赛时代码写了依托乱七八糟的东西。

``` cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

stack<int> STACK;
ll pos[1000005];
ll cnt, N, A, B, len, tmp, k;
string str, cstr;

signed main()
{
	cin >> N >> A >> B >> str;
	for(int i = 0; i < (N << 1); ++ i)
	{
		if(str[i] == '(') STACK.push(i);
		else
		{
			if(!STACK.empty())
			{
				pos[++ cnt] = STACK.top();
				pos[++ cnt] = i;
				STACK.pop();
			}
		}
	}
	
	if(cnt)
	{
		sort(pos + 1, pos + cnt + 1);
		for(int i = 0, j = 1; i < (N << 1); ++ i)
			if(i == pos[j])
				++ j;
			else
				cstr[++ len] = str[i];
	}
	else 
	{
		len = str.size();
		for(int i = 1; i <= len; ++ i) cstr[i] = str[i - 1];
	}
	
	for(int i = 1; i <= len; ++ i)
	{
		if(cstr[i] == '(') 
		{
			k = i;
			break;
		}
	}
	
	if(k <= 1)
		cout << ((B * len) >> 1) << endl;
	else 
	{
		tmp = min(k - 1, len - k + 1);
		cout << (min(A, B << 1) * ((tmp + 1) >> 1) + ((B * (len - (tmp << 1))) >> 1)) << endl;
	}
	
	return 0;
} 
```

# 后言

~~代码采用了位运算，可读性大大降低，望见谅。~~

---

## 作者：Sorato_ (赞：0)

# ARC175B Parenthesis Arrangement

## 题目大意

给定一个长度为 $2n$ 括号序列，对这个括号序列进行若干次以下操作，使得括号匹配。

- 交换序列中的任意两个元素，代价为 $a$。
- 修改序列中的任意一个元素，代价为 $b$。

## Solve

小贪一波。

首先记序列中左括号个数为 $cnt$，则：

- 若 $cnt<n$ 即左括号不够，则我们从左端开始填，将前 $n-cnt$ 个右括号改为左括号是最优的。
- 若 $cnt>n$ 即右括号不够，则我们从右端开始填，将后 $cnt-n$ 个左括号改为右括号是最优的。

显然这些操作二是必要的，代价为 $|n-cnt|\times b$。

接下来，对于处理出的左右括号数量相等的序列，将 $a$ 与 $2b$ 取 $\min$ 后，执行交换操作一定比执行修改操作要优，这是显然的，因为修改一个元素一定要修改另一个元素使得左右括号数量相等，而这就相当于一次交换操作。

考虑将左括号设为 $-1$，右括号设为 $1$。遍历序列，记录一个前缀和 $sum$。若遍历至第 $i$ 位时 $sum>0$，则说明需要进行操作，那么考虑贪心：

将这个右括号与最后一个左括号交换一定是最优的。因为交换前后序列的所有括号匹配数一定不会减少且会加 $1$。而与任何一个其他位置的左括号交换，括号匹配数有可能减少/不变/加 $1$。

## Code

```c++
// LUOGU_RID: 153163957
#include<bits/stdc++.h>
#pragma GCC optimize(1,2,3,"Ofast","inline")
using namespace std;
#define int long long
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
int n,a,b,cnt,ans,sum=0,res=0;
string s;
signed main()
{
	n=read();a=read();b=read();
	a=min(a,b<<1);cin>>s;
	for(int i=0;i<s.size();i=-~i)	if(s[i]=='(')	cnt=-~cnt;
	if(cnt<n)
		for(int i=0,j=0;i<s.size()&&j<n-cnt;i=-~i)
			if(s[i]==')')	s[i]='(',j=-~j;
	if(cnt>n)
		for(int i=s.size()-1,j=0;i&&j<cnt-n;i--)
			if(s[i]=='(')	j=-~j,s[i]=')';
	for(int l=0,r=s.size()-1;l<s.size()&&l<r;l=-~l)
	{
		if(s[l]=='(')	sum--;
		else	sum=-~sum;
		if(sum>0)
		{
			while(s[r]==')'&&r>l)	r--;
			if(r>l)	res=-~res,sum-=2;
		}
	}
	return printf("%lld",abs(n-cnt)*b+res*a),0;
}
```

---

