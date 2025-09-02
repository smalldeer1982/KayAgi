# Palindrome Game (hard version)

## 题目描述

The only difference between the easy and hard versions is that the given string $ s $ in the easy version is initially a palindrome, this condition is not always true for the hard version.

A palindrome is a string that reads the same left to right and right to left. For example, "101101" is a palindrome, while "0101" is not.

Alice and Bob are playing a game on a string $ s $ of length $ n $ consisting of the characters '0' and '1'. Both players take alternate turns with Alice going first.

In each turn, the player can perform one of the following operations:

1. Choose any $ i $ ( $ 1 \le i \le n $ ), where $ s[i] = $ '0' and change $ s[i] $ to '1'. Pay 1 dollar.
2. Reverse the whole string, pay 0 dollars. This operation is only allowed if the string is currently not a palindrome, and the last operation was not reverse. That is, if Alice reverses the string, then Bob can't reverse in the next move, and vice versa.

Reversing a string means reordering its letters from the last to the first. For example, "01001" becomes "10010" after reversing.

The game ends when every character of string becomes '1'. The player who spends minimum dollars till this point wins the game and it is a draw if both spend equal dollars. If both players play optimally, output whether Alice wins, Bob wins, or if it is a draw.

## 说明/提示

In the first test case of example,

- in the $ 1 $ -st move, Alice will use the $ 2 $ -nd operation to reverse the string, since doing the $ 1 $ -st operation will result in her loss anyway. This also forces Bob to use the $ 1 $ -st operation.
- in the $ 2 $ -nd move, Bob has to perform the $ 1 $ -st operation, since the $ 2 $ -nd operation cannot be performed twice in a row. All characters of the string are '1', game over.

 Alice spends $ 0 $ dollars while Bob spends $ 1 $ dollar. Hence, Alice wins.In the second test case of example,

- in the $ 1 $ -st move Alice has to perform the $ 1 $ -st operation, since the string is currently a palindrome.
- in the $ 2 $ -nd move Bob reverses the string.
- in the $ 3 $ -rd move Alice again has to perform the $ 1 $ -st operation. All characters of the string are '1', game over.

 Alice spends $ 2 $ dollars while Bob spends $ 0 $ dollars. Hence, Bob wins.

## 样例 #1

### 输入

```
3
3
110
2
00
4
1010```

### 输出

```
ALICE
BOB
ALICE```

# 题解

## 作者：灵茶山艾府 (赞：22)

下文用 A 表示 Alice，B 表示 Bob。

先讨论 $s$ 本身是回文的情况：

从 $\texttt{0}$ 的个数的奇偶性讨论（博弈论套路），记 $\texttt{0}$ 的个数为 $c$。

若 $c$ 为偶数，则无论 A 在哪里修改，B 就在对应的位置修改，使得 B 修改完后 $s$ 仍然是回文。如此反复直到剩下 $2$ 个 $\texttt{0}$ 时，A 修改完后 B 可以翻转 $s$，这样必然会使 A 修改的次数比 B 多 $2$，B 获胜。

若 $c$ 为奇数，那么当 $c=1$ 时 B 显然必胜；当 $c>1$ 时，A 可以修改 $s$ 正中间的 $\texttt{0}$，这样丢给 B 的局面就是 $c$ 为偶数的情况，从而最终 B 修改的次数比 A 多 $1$，A 获胜。

因此当 $c$ 为奇数且 $c>1$ 时 A 必胜，否则 B 必胜。

如果 $s$ 不是回文，那么根据 $n$ 的奇偶性来讨论：

若 $n$ 为偶数，则 A 总是可以先翻转字符串，那么 B 必然要优先将 $s$ 补成回文串，否则 A 可以一直执行翻转操作。A 只要让自己成为补成回文串的最后一手的人，那么丢给 B 的局面必然是上面所讨论的 $c$ 为偶数的情况，此时 A 必胜。

若 $n$ 为奇数，且 $s[n/2]$ 为 $\texttt{1}$，那么可以将 $s[n/2]$ 去掉，则与 $n$ 为偶数的情况是一样的。若 $s[n/2]$ 为 $\texttt{0}$，且 $c=2$，那么无论如何 A 和 B 都要修改一次，此时两人打成平手。若 $c>2$，那么 A 可以一直翻转字符串，等待 B 将 $s$ 修改成回文串时，修改 $s[n/2]$ 为 $\texttt{1}$，那么丢给 B 的局面必然是上面所讨论的 $c$ 为偶数的情况，此时 A 必胜。

因此，如果 $s$ 不是回文，则当且仅当 $n$ 为奇数且 $s[n/2]$ 为 $\texttt{0}$ 且 $c=2$ 时为平局，否则 A 必胜。

AC 代码：（Golang）

```go
package main
import("bufio";."fmt";."os";."strings")

func main() {
	in := bufio.NewReader(Stdin)
	var T, n int
	var s string
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &n, &s)
		isP := true
		for i := 0; i < n/2; i++ {
			if s[i] != s[n-1-i] {
				isP = false
				break
			}
		}
		c := Count(s, "0")
		if isP {
			if c&1 > 0 && c > 1 {
				Println("ALICE")
			} else {
				Println("BOB")
			}
		} else if n&1 > 0 && s[n/2] == '0' && c == 2 {
			Println("DRAW")
		} else {
			Println("ALICE")
		}
	}
}
```

---

## 作者：Mophie (赞：5)

前置：[B1](https://www.luogu.com.cn/blog/97304/solution-cf1527b1)

这个 B1 讲清楚了回文子串时的情况。

现在讲讲非回文子串时的情况。

首先我们发现先手要赢有两种情况：

- 让自己变成回文子串后成为后手且剩下偶数个 $0$，然后赢 $2$ 元钱。

- 让自己变成回文子串后成为先手并剩下奇数个且个数不为 $1$ 的 $0$，然后可以赢 $1$ 元钱。

然后如果时非回文子串的时候先手可以任意翻转，所以主动权掌握在先手手里。

考虑以下两种情况：

- 如果 $n$ 为偶数或者中间不为 $0$。

那么在 Alice 视角，可以无限翻转。然后当 Bob 一步就可以把原串变成回文子串的时候自己先变掉。那就拿到后手了。可以赢 $2$ 元钱。而前面最多落后 $1$ 元钱（只有一个不同的对），所以此时必胜。

- 如果 $n$ 为奇数且中间为 $0$。

那么和上面的策略一幕一样。但是如果当现在只有两个 $0$ 的话可以发现后面只能赢 $1$ 元钱，而前面却输了 $1$ 元钱，所以打平。

具体细节可以看代码实现。

```cpp
//红太阳zhouakngyang txdy!
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include<bits/stdc++.h>
#define Macesuted cout<<"kawaii"<<endl
#define MatrixCascade cout<<"npsl"<<endl
#define Karry5307 cout<<"nmsl"<<endl
using namespace std;
//#define int long long
inline int read()
{
	int sum=0,nega=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')nega=-1;ch=getchar();}
	while(ch<='9'&&ch>='0')sum=sum*10+ch-'0',ch=getchar();
	return sum*nega;
}
int n,cnt,flag;
char a[1009];
int main()
{
	int taxi=read();
	for(int ttt=1;ttt<=taxi;ttt++)
	{
		flag=0;
		n=read();cnt=0;
		scanf("%s",a+1);
		for(int i=1;i<=n;i++)
		{
			if(a[i]=='0')cnt++;
			if(a[i]!=a[n-i+1])flag=1;
		}
		if(!flag)
		{
			if(cnt==1||cnt%2==0)puts("BOB");
			else puts("ALICE");
		}
		else
		{
			if(cnt==2&&n%2==1&&a[n/2+1]=='0')puts("DRAW");
			else puts("ALICE");
		}
	}
	return 0;
}

``` 

---

## 作者：封禁用户 (赞：3)

# 1.前言
[CF链接](http://codeforces.com/contest/1527/problem/B2)

题目大意：输出 1 到 $n$ 的整数中，有多少个由相同数字组成的数。
# 2.题目解析：

这里有一个简单策略：对于一个回文串（最中间的数字不为 $0$），那么可以采取 A 填哪个位置，B 就填回文串对应的位置；

直到剩下 2 个 $0$ 的时候，A 填任何一个位置，B 选择 reverse；此时 A 只能再填一次 $0$，B必胜；
 先手者，除非回文串中间是 $0$（当有空格的部分大于 $1$ 时），否则必输。
 
这个题目中先手是可以 reverse 操作的，这是一个比较大的优势；

如果起手是回文串，那么可以用上面的逻辑。这里有一个很重要的点，先后手最大的差距是 2，就是 $1001$ 这种情况，因为都会采用最佳策略。
 
为了方便思考，我们引入函数 f，$f(str)$ 表示回文串str，先手会赢多少；
```
f(1001)=-2;
f(101)=-1; （仅有一个 0 的情况下）
f(10001)=1;
 ```
 
注意：除了没有 $0$，平局的情况是不存在的。
我们知道回文串的胜负，有两种结果：$-2/-1$ 和 $1$。

假如字符串没有任何位置可以操作 1 次，之后变成回文串，那么先手者 Alice 可以 reverse，等待后手者操作后，依旧可以执行 reverse。这种策略就可以占领 $1$ 的优势，因为后手在一直补齐。

直到存在一个操作，可以对某个位置 k 进行操作，并且操作之后字符串变成回文串 strK；

- 假如 $f(strK)=1$，则 Alice 可以继续执行 reverse 操作，因为 Bob 如果将字符串操作为 strK，对 Alice 是有收益的；

- 假如 $f(strK)=-1$，则 Alice 继续执行 reverse 会平局，因为 Bob 花费 $1$ 的代价让 alice 面临 $-1$ 的情况；（是否平局，取决于在达到下一步操作就能生成回文串的操作步数）

- 假如 $f(strK)=-2$，则 Alice 必胜，Alice 花费 $1$ 的代价可以让对手面临 $-2$ 的情况；
 
这里可以推出来，先手者必然不会输。（注意，这个前提是有 2 个 $0$ 以上）
 
所以问题是在于上面的情况 2，怎样快速找到平局。
 
我们知道这个追赶的步数，应该等于字符串中 $1$ 和 $0$ 按照回文串要求不对应的数量。

For Example:

10011 $\to$ 其中的 $str[1]$ 和 $str[3]$ 不一样，需要追赶，那么统计一下，这个数量，即可得到追赶的步数 $step$。

假如 $step=1$，则刚好和构成回文串 $strNew$ 之后，$f(strNew)$ 的 $-1$ 收益持平，此时会平局。
# 3.code
~~已去除头文件~~
```cpp
typedef long long lld;
class Solution {
    static const int N = 100010;
public:
    int n, m;
    string pubStr;
    bool isPalindrome(string &str) {
        bool isPalindrome = true;
        for (int i = 0; i < n / 2; ++i) {
            isPalindrome = isPalindrome && (str[i] == str[n - i - 1]);
        }
        return isPalindrome;
    }
    int getCount(string &str) {
        int ret = 0;
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (str[i] == '0') {
                ++cnt;
            }
        }
        if (cnt == 0) {
            ret = cnt;
        }
        else if (cnt == 1) {
            ret= cnt;
        }
        else if (cnt % 2) {
            ret = (str[(n - 1) / 2] == '0' ? -2 : 1);
        }
        else {
            ret = -2;
        }
        return ret;
    }
    
public:
    void solve() {
        int t;
        cin >> t;
        while (t--) {
            cin >> n;
            cin >> pubStr;
            
            int cnt = 0, step = 0;
            for (int i = 0; i < n; ++i) {
                if (pubStr[i] == '0') {
                    ++cnt;
                }
                if (i < n / 2 && pubStr[i] != pubStr[n - i - 1]) {
                    ++step;
                }
            }
            if (cnt == 0) {
                cout << "DRAW" << endl;
            }
            else if (cnt == 1) {
                if (isPalindrome(pubStr)) {
                    cout << "BOB" << endl;
                }
                else {
                    cout << "ALICE" << endl;
                }
            }
            else {
                if (isPalindrome(pubStr)) {
                    if (cnt % 2) {
                        cout << (pubStr[(n - 1) / 2] == '0' ? "ALICE" : "BOB") << endl;
                    }
                    else {
                        cout << "BOB" << endl;
                    }
                }
                else {
                    if (step == 1 && cnt == 2) {
                        cout << "DRAW" << endl;
                    }
                    else {
                        cout << "ALICE" << endl;
                    }
                }
            }
            
        }
    }
}
ac;

int main(){
    ac.solve();
    return 0;
}
```
Deirdre：When whales fall, everything lives.

---

## 作者：walk_alone (赞：3)

在做这个题之前应该先搞清楚 B1 的逻辑。这也是为什么这次要搞出一个 B1 与 B2 的原因——一步跨到这里来是很难的。

如果 B1 切掉的话，应该会注意到这么个事情：除了平局，``0`` 的个数为偶数的时候后手必胜，奇数的时候先手必胜。考虑 ``0`` 的个数模 $4$ 为 $0$  的情况。这个情况一开始卡了我半天，我以为都是平局，其实不然。

考虑B的操作：A 一开始随机挑一个对称的 ```00``` （即$\cdots 0 \cdots 0 \cdots $，下称 ```00```）填上一个 ```1```，B 也跟着填，在**对称的地方**也填上 ```1```，使得整个式子还是为回文串（注意，这里不要转！）。这样模 $4$ 余 $0$ 就变成了模 $4$ 余 $2$！后面这个情况自然不用多说肯定是 B 赢——A 填一次我就转一次，然后先后易手，$4$ 个一周期，怎么搞都是 A 输。当然也可以就参照这个思路——只要非对称个数（**下称 ```01```**）

分析一下刚刚这个操作的本质——**不要回文串！** 我尽可能地把回文串丢给对方，让对方拿到回文串，我就有可能赢。想想奇数，奇数的时候也是如此——A先把中间堵上就变成了回文串，退化到之前的偶数回文，而这种情况后手必胜。

（下面简称：```0``` 的个数为奇数的回文串（长度为奇同时中央为 ```0```）——奇回文；```0``` 的个数为偶数的回文串——偶回文）

正文开始：

先说结论：**只要不是平局，先手必胜**。

注意到多个 ```01``` 和 $1$ 个 ```01``` 本质是一样的，只是重复次数不同，因而下面只分析非回文只含一个 ```01``` 的情况。

1、差一个 ```01``` 奇回文

考虑先手必胜操作：**转**。这样留给 B 的就是和 A 一样的局面，而且 B 还不能转，他只能选取非对称的 ```01``` 或者中央的 ```0``` 填上。如果选择 ```01``` 中的 ```0``` 填，那么留给 A 的就是奇回文——A 先手必胜；如果填中央的 ```0```，此时 A 先手，情况退化到下面的 2 情况：

2、差一个 ```01``` 偶回文

此时 A 填上 ```01``` 中的 ```0```，变成偶回文，B 先手，此时 A 后手必胜。

多个 ```01``` 的情况类似——只需要转，让 B 填 ```01```，A 就一直转。直到留下最后一个 ```01```，再执行上面所说的操作即可。

估计看到这里还有一个疑问：A 在上面的操作中要比 B 多掏钱，怎么保证回文结论的适用性？

对于 1 情况，拢共的 ```0``` 个数为偶，B 必然比 A 多掏钱。

对于 2 情况，```0``` 个数为奇，预处理操作中 A 多填了一个 ```1```，但是在偶回文情况中，先手比后手掏的钱要大于等于 ```2```，因而 A 必胜。

现在再讨论最后一个情况：平局。

显然 ```001``` 和 ```100``` 是平局。如果此时再插入更多对称的 ```11```，也不影响——比如 ```11010```。因而，此类情况的判定是：长度为奇，```01``` 仅一个，没有 ```00```。

（附记：整理自yj的想法，叶老师yyds）

---

## 作者：Leap_Frog (赞：2)

### P.S.
来胡一下。  
只能膜拜其他人是博弈论大师  
还有这篇题解有 $\LaTeX$ 吗 ![](//xn--9zr.tk/xia)

### Solution.
首先，我们发现翻转操作一点用都没有。  
然后，我们发现每对对应位置上的字符顺序也对答案没有影响。  
同时，如果有一对数字已经变成 1-1 了，那它就完全没有作用了。  
那么我们可以考虑设计一个 `dp`。  
`dp[w=0/1][i][j][k=0/1][l=0/1]` 表示当前到第 $w$ 个人，有 $i$ 对 `0-1`，有 $j$ 对 `0-0`，最中间数字是 $k$，上一个人有没有翻转过（$l$）时的答案。  
然后直接模拟每个人可以做的事来转移即可。  
同时这个 dp 的答案每次不变，所以可以直接预处理。  
复杂度 $O(n^2)$

---

## 作者：wmrqwq (赞：1)

# 题目链接

[CF1527B1（luogu）](https://www.luogu.com.cn/problem/CF1527B1)

[CF1527B2（luogu）](https://www.luogu.com.cn/problem/CF1527B2)

[CF1527B1（codeforces）](https://codeforces.com/problemset/problem/1527/B1)

[CF1527B2（codeforces）](https://codeforces.com/problemset/problem/1527/B2)


# 解题思路

这篇题解分 B1，B2 两个部分来讲。

## B1 sol：

考虑字符串中 $0$ 的数量，设这个值为 $sum$：

- 若 $sum \equiv 0 \pmod{2}$，且字符串回文时，那么此时，后手可以一直模仿先手的操作，直到字符串含有最后一个 $0$ 时，后手可以反转这个字符串，那么此时后手的代价比先手要少 $2$，综上，后手此时必胜。

- 若 $sum \equiv 1 \pmod{2}$，且字符串回文时，那么此时，字符串的长度**一定**为**奇数**，且字符串中间的数字一定为 $0$，那么此时，先手可以将中间的 $0$ 变为 $1$，此时若还有剩余的 $0$，则先手必胜，否则后手必胜。

综上，这就是 B1 的做法。

## B2 sol：

仍然考虑字符串中 $0$ 的数量，设这个值为 $sum$：

若字符串已经回文，则直接按照 B1 的做法来做。

否则，先手一定可以反转字符串，直到后手把这个字符串变为回文，那么此时：

- 若 $n \equiv 0 \pmod{2}$，由于此时先手仍然可以一直模仿后手的操作，由于前期先手比后手付出的代价要少，因此可以得出先手必胜。

- 若 $n \equiv 1 \pmod{2}$，如果字符串中间的数字不为 $0$ 则先手仍然可以模仿后手的情况，此时先手必胜。否则，若此时 $sum = 2$，则后手去掉最外侧的 $0$，此时先手与后手平局，其余情况，我们发现先手的所需代价至少比后手少 $1$，先手必胜。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
ll _t_;
void _clear(){}
ll n;
string s;
bool check(string s)
{
	ll L=1,R=n;
	while(L<=R && s[L]==s[R])
		L++,R--;
	return L>=R;
}
/*
11010

11011 0:1

11111 1:1


1001101

1011001

1011101 0:1

1111101 1:1

1011111
*/
void solve()
{
	_clear();
	cin>>n>>s;
	s=' '+s;
	if(check(s))
	{
		ll sum=0;
		for(auto i:s)
			sum+=i=='0';
		if(sum%2==0)
		{
			cout<<"BOB\n";
			return ;
		}
		if(sum==1)
		{
			cout<<"BOB\n";
			return ;
		}
		cout<<"ALICE\n";
		return ;
	}
	ll sum=0;
	for(auto i:s)
		sum+=i=='0';
	if(n%2 && sum==2 && s[(n+1)/2]=='0')
		cout<<"DRAW\n";
	else
		cout<<"ALICE\n";
//	exit(-1);
}
int main()
{
//	freopen("tst.txt","r",stdin);
//	freopen("sans.txt","w",stdout);
	IOS;
	_t_=1;
 	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}
```

---

## 作者：Shellchen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1527B2)
### 题目介绍
这是一道思维题。
没有什么算法，就是分类讨论。
**注：后文均将 Alice 称为 A，将 Bob 称为 B。**
### 题目思路
我们首先考虑一种情况：$s$ 是回文串。

显然，在这种情况下，字符 `1` 是对局势不起影响的。所以我们只需考虑 `0` 的个数。
这里又分两种情况：字符 `0` 个数的奇偶性。

若 `0` 的个数是偶数，则可以证明，**在有字符`0`的情况下**，B 必胜。

证明如下：
如果有字符 `0`，则因为字符 `1` 不起作用，我们可以省略掉`1`，剩余部分大致如下：

```
0 0 0 0 ... 0 0 0 0
```
这时，整个字符串是回文串，因此 A 无法翻转。但无论 A 将哪个 `0` 变成 `1`：

```
0 0 1 0 ... 0 0 0 0
```
B 都可以将它对称位置的 `0` 变为 `1`：

```
0 0 1 0 ... 0 1 0 0
```
这样一直下去，A 永远无法翻转字符串，且 A 和 B 花的钱数永远相等。如果 B 一直采取这个策略，那么最终整个字符串会变成：

```
... 1 1 1 0 1 1 1 ... 1 1 1 0 1 1 1 ...
```
此时，A 仍然是别无选择，只可以将任意一个 `0` 变为  `1`：

```
... 1 1 1 1 1 1 1 ... 1 1 1 0 1 1 1 ...
```
之后，B 可以翻转字符串：

```
... 1 1 1 0 1 1 1 ... 1 1 1 1 1 1 1 ...
```
于是，由于 B 在上一回合已经翻转过，A 不能再翻转，只能将剩下的一个 `0` 改为 `1`：

```
... 1 1 1 1 1 1 1 ... 1 1 1 1 1 1 1 ...
```
此时，整个字符串已经全部变成 `1`。在上一回合，A 比 B 多花了 2 元，因此 B 是必赢的。

但如果 $s$ 中没有 `0`，则显然平局。

接下来考虑 `0` 的个数是奇数的情况。
这种情况和上一种也是类似的。先上结论：**在 `0` 的个数不为 1 的情况下**，A 必胜。

证明如下：
同上，我们可以省略 `1`：

```
0 0 0 0 ... 0 ... 0 0 0 0
```
其中，中间的 `0` 恰好在整个字符串的正中间，即 $s_{\lfloor \frac{n}{2} \rfloor}$。
这时，A 可以先将正中间的 `0` 变为 `1`：

```
0 0 0 0 ... 1 ... 0 0 0 0
```
之后，A 可以采用和上面与 B 类似的策略：B 无论将哪个位置的 `0` 改为 `1`，A 都可以将它对称位置的 `0` 改为 `1`。最后，和上面差不多，只会剩下 2 个 `0`：

```
... 1 1 1 0 1 1 1 ... 1 1 1 0 1 1 1 ...
```
此时，无论 B 修改的是哪个 `0`，A 都可以翻转整个字符串，逼迫 B 修改另一个 `0`。在这一回合，B 多花了 2 元，而 A 在第一回合只多花了 1 元，所以 A 必胜。

但是，如果只有 1 个 `0`，那么只能由 A 来修改，因此这种情况下，B 胜利。

接下来，我们就可以扩展到另一情况：$s$ 并不是回文串。

此时又要考虑 $n$ 的奇偶性。

若 $n$ 是偶数，A 可以一直执行翻转操作，逼迫 B 优先将 $s$ 改成回文串（否则 A 就可以一直执行翻转操作）。A 只要保证他做出将 $s$ 改成回文串的最后一步，这样丢给 B 的就是前面提到的 $s$ 是回文串且有偶数个 `0` 的情况，于是 A 必胜。

若 $n$ 是奇数，则又分两种情况：

若 $s_{\lfloor \frac{n}{2} \rfloor}$ 是 `1`，则这个 `1` 并不会影响游戏进程，我们大可将其省略，于是 $s$ 的长度变为偶数，A 必胜。

若 $s_{\lfloor \frac{n}{2} \rfloor}$ 是 `0`，则又会有一些情况：

若 $s$ 中只有 2 个 `0`，则无论如何，A 和 B 都会被迫修改一个，平局。

否则，A 可以一直翻转，让 B 把 $s$ 改成回文串，然后就会变成 $s$ 是回文串且有奇数个 `0` 的情况，A 必胜。

### 最终代码
综上所述，写出以下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10;
int b1[200],b2[200];
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		string s;
		cin>>n>>s;
		string r=s;
		reverse(r.begin(),r.end());
		int x=0;
		for(int i=0;i<n;i++) if(s[i]=='0') x++;
		if(s==r)
		{
			if(x%2==0)
			{
				if(x==0) cout<<"DRAW\n";
				else cout<<"BOB\n";
			}
			else
			{
				if(x==1) cout<<"BOB\n";
				else cout<<"ALICE\n";
			}
			continue;
		}
		if(n%2==0) cout<<"ALICE\n";
		if(n%2==1)
		{
			char ch=s[n/2];
			if(ch=='1') cout<<"ALICE\n";
			if(ch=='0')
			{
				if(x==2) cout<<"DRAW\n";
				else cout<<"ALICE\n";
			}
		}
	}
	return 0;
}
```
完结撒花。

---

## 作者：rainbow_cat (赞：0)

由于回文的情况在简单版中处理过，以下只讨论非回文。   
可以考虑一种策略，先手一直反转直到下一步后手就可以将字符串变为回文，此时先手率先将那一位变为 $1$。此时串变为回文串，先手只需一直模仿后手即可，此时先手胜，示例如下：
```
Or:1011110000
A:0000111101
B:1000111101
A:1011110001
B:1011111001
A:1011111101
B:1111111101
A:1111111111
```
但我们会发现一个问题，串长为奇数且只有两个 $0$，而一个恰好在中间时若按最优策略只可平局，特判即可。   
核心代码：
```cpp
if(s.size()%2&&s[s.size()/2]=='0'&&cnt==2)cout<<"DRAW\n";
```

---

## 作者：LLLLLL7381 (赞：0)

说在前面：本题代码交到 CF1527B1 是肯定 AC 的。

既然没有题意翻译，那么简单阐述一下题意。
# 题意
给定一个由 $0$ 和 $1$ 构成的字符串，两个人轮流对字符串进行处理，支持下面两种操作：  
1. 将其中一个 $0$ 修改为 $1$，但是需要消耗 $1￥$。
2. 如果字符串不是回文串，而且上一次没有执行这个操作的时候可以将字符串反转。

当所有的操作结束的时候，消耗代价最少的人胜出。

# 思路  

可以先判断一下给出的字符串是否已经满足回文串的条件，如果满足，直接变身 easy version。 
## 简单模式    
~~我们充分发扬人类智慧~~，如果已经满足回文串的条件，可以先统计一下字符串内 $0$ 的个数。    
显而易见的，如果 $0$ 的数量是偶数，显然后手不败，因为先手只能先修改字符串，这样后手在先手的“对称”位置修改必定不会败。等到仅仅剩余 $1$ 个 $0$ 的时候，直接反转字符串，这样先手只会多花 $2￥$ 去处理，显然后手会赢。  
如果是奇数，还是回文串，显而易见中间的数必定是 $0$。首先有一个特殊情况，就是有 $1$ 个 $0$，这样一来，显然是后手必胜。对于其他的情况，先手可以将中间的 $0$ 修改为 $1$，这样又一次回到了上面提到的情况，但是这一次是后手在先手修改完以后需要再多用 $2￥$完成相关修改（与上一段相同），显然是先手胜利。因为先手最后比后手少执行了一次操作 $1$。   
当你阅读到这里的时候，恭喜你学会了 easy version!    
## 困难模式
**很难不想到**如果不是回文串，那么先手就可以执行翻转操作，这样后手只能执行操作 $1$ 了。从上文可以得出当一个人面临偶数个 $0$ 且串是回文串时，对方一定有策略使接下来的操作自己会比对方多执行 $2$ 次操作 $1$。   
~~我们再一次发扬人类智慧~~，先手不断执行反转操作，直到还有一步就可以让字符串变为有偶数个 $0$ 的回文串的时候，进行操作 $1$。    
复盘一下，现在先手已经进行了一次操作 $1$，除了平局的情况后手至少一次，而且后续后手会多执行 $2$ 次操作 $1$，于是后手寄了。    
当你看到这里的时候，你应该好奇，怎么感觉少了什么？很显然我们没有考虑平局的情况。        
这个时候只需要特判一下非回文串中 $0$ 的个数小于等于 $2$ 的情况，如果只有 $2$ 个 $0$，而且有一个在中间的时候平局。   
完结撒花~~~~！

# 喜闻乐见的代码

```cpp
#include<bits/stdc++.h>
#define mian main
using namespace std;
inline int read()
{
   int x=0,f=1;
   char ch=getchar();
   while(ch<'0'||ch>'9')
   {
       if(ch=='-')
           f=-1;
       ch=getchar();
   }
   while(ch>='0' && ch<='9')
       x=x*10+ch-'0',ch=getchar();
   return x*f;
}
char s[1005];
inline bool check(int n)
{
	int m=(n>>1);
	for(int i=1;i<=m;i++)
	{
		if(s[i]!=s[n-i+1])
		{
			return false;
		}
	}
	return true;
}
int mian()
{
	int T=read();
	while(T--)
	{
		int n=read();
		scanf("%s",s+1);
		int cnt=0;
		for(int i=1;i<=n;i++)
		{
			if(s[i]=='0')
			{
				cnt++;
			}
		}
		if(check(n))
		{
			if(cnt%2==0)
			{
				puts("BOB");
			}
			else if(cnt==1)
			{
				puts("BOB");
			}
			else 
			{
				puts("ALICE");
			}
		}
		else
		{
			if(cnt==2 and (n&1) and s[n+1>>1]=='0')
			{
				puts("DRAW");
			}
			else 
			{
				puts("ALICE");
			}
		}
	}
	return 0;
}
```

---

## 作者：CQWDX (赞：0)

题意略。

手玩一下，发现 Bob 赢面不大。

本来想模拟的。考虑结论题。

由于计入代价的操作只有 $s_i=0\to1$ 一个，影响答案的关键因素只有 $0$ 的个数，可以统计 $0$ 的个数为 $cnt$。

~~由于这题和 Ezy Version 的唯一区别就是初始字符串是否为回文，很自然地想到对于初始串是否回文分类讨论。~~

若初始字符串为回文：

> 显然地，若 $cnt=1$，Bob 必胜。
>
> 再手玩几组，发现若 $2|cnt$，双方策略如下：
>
> - Alice 填入 1；
> - Bob 填入 1；
> - Alice 填入 1；
> - …
> - 当还有 2 个空可填时，Alice 填入 1；
> - Bob 翻转；
> - Alice 填入 1.
>
> 显然 Alice 的代价会始终比 Bob 多 $2$。
>
> 而当 $2\nmid cnt$ 的时候，相当于 $2\mid cnt$ 时 Bob 先手。Alice 必胜。

若初始字符串不为回文：

> 我们可以发现当 $2\nmid n$ 时 Alice 必胜。
>
> Alice 第一步就可以将其翻转。Bob 的目标是尽可能早地将其转为回文串。
>
> 但 Bob 在将串转为回文串的过程中，始终会比 Alice 多出一部分的代价。且回文后一定有 $cnt\geq 2$，代价挣不回来。
>
> 但如果回文后 $cnt=1$ 呢？回文后轮到 Alice，此时 Alice 只能填入 $1$，较 Bob 多花费 $1$ 的代价。此时最好的结果是平局，而平局的充要条件为 Bob 在使其回文的的过程中只花费了 $1$ 的代价。
>
> 显然只有一种字符串满足以上条件：$2\nmid n \wedge s_{\frac{n}{2}+1}=0\wedge cnt=2$。
>

综上，有

$$\begin{cases}\tt Bob&cnt=1\vee 2\mid cnt\\\tt Draw&2\nmid n\wedge s_{\frac n 2+1}=0\wedge cnt=2\\\tt Alice&\tt otherwise\end{cases}$$

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(3, "unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
const int maxn = 4020;
std::string s;
int n, T;
void solve() {
	bool fl = 0; int cnt = 0; 
	std::cin >> n >> s; s = " " + s;
	for(int i = 1; i <= n; i++){
		if(s[i] == '0') cnt++;
		if(s[i] != s[n - i + 1]) fl = 1;
	}
	if(fl == 0) {
		if(cnt % 2 == 0 || cnt == 1) printf("BOB\n");
		else printf("ALICE\n");
	}
	else {
		if(s[n / 2 + 1] == '0' && n % 2 == 1 && cnt == 2) printf("DRAW\n");
		else printf("ALICE\n");
	}
}
int main() {
	scanf("%d", &T);
	while(T--) solve();
	return 0;
}
```


---

## 作者：__LiChangChao__ (赞：0)

### 思路

分类讨论。

这道题的情况其实不是很复杂，只需要分为两类情况：

* 是回文串
	* 只有一个空时，Alice 只能填这个空，Bob 胜利。
	* 有偶数空时，Alice 先填一个空，破坏了回文，此时 Bob 再填一个空，再次回文，Alice 只能接着填，当还有一个空时，Alice 的花费一定比 Bob 多 $1$，此时 Bob 翻转，Alice 只能再填，失败。
	* 否则就是有奇数个空，采用偶数时 Bob 的方式，Alice 胜利。
* 不是回文串
	* 只有两个空，且长度为奇数，最中间是空时，Bob/Alice 可以填出一个回文串，Alice/Bob 必须填，花费均为 $1$，于是平局输出 `DRAW`。
	* 其他情况则 Alice 翻转，Bob 填空，当要填出回文串时，Alice 先填，此时构成回文串，Bob 只能填空，Alice 继续填对应的空，直到最后一个空时翻转，显然 Bob 的花费至少比 Alice 大 $1$。

然后对应特判即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e3+5;
int t;
char c[maxn];
int n,sum;
int main() {
	scanf("%d",&t);
	while(t--){
		sum=0;
		scanf("%d%s",&n,c+1);
		for(int i=1;i<=n;i++){
			if(c[i]=='0')sum++;
		}bool flag=1;
		for(int i=1;i<=n/2;i++){
			if(c[i]!=c[n-i+1]){
				flag=0;
				break;
			}
		}
		if(flag){
			if(sum%2==0||sum==1)puts("BOB");
			else puts("ALICE");
		}else{
			if(sum==2&&n%2==1&&c[(n+1)/2]=='0')puts("DRAW");
			else puts("ALICE");
		}
	}
}
```

---

