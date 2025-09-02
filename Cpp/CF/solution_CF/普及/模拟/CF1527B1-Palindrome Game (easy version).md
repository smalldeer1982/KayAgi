# Palindrome Game (easy version)

## 题目描述

The only difference between the easy and hard versions is that the given string $ s $ in the easy version is initially a palindrome, this condition is not always true for the hard version.

A palindrome is a string that reads the same left to right and right to left. For example, "101101" is a palindrome, while "0101" is not.

Alice and Bob are playing a game on a string $ s $ (which is initially a palindrome in this version) of length $ n $ consisting of the characters '0' and '1'. Both players take alternate turns with Alice going first.

In each turn, the player can perform one of the following operations:

1. Choose any $ i $ ( $ 1 \le i \le n $ ), where $ s[i] = $ '0' and change $ s[i] $ to '1'. Pay 1 dollar.
2. Reverse the whole string, pay 0 dollars. This operation is only allowed if the string is currently not a palindrome, and the last operation was not reverse. That is, if Alice reverses the string, then Bob can't reverse in the next move, and vice versa.

Reversing a string means reordering its letters from the last to the first. For example, "01001" becomes "10010" after reversing.

The game ends when every character of string becomes '1'. The player who spends minimum dollars till this point wins the game and it is a draw if both spend equal dollars. If both players play optimally, output whether Alice wins, Bob wins, or if it is a draw.

## 说明/提示

In the first test case of the example,

- in the $ 1 $ -st move Alice has to perform the $ 1 $ -st operation, since the string is currently a palindrome.
- in the $ 2 $ -nd move Bob reverses the string.
- in the $ 3 $ -rd move Alice again has to perform the $ 1 $ -st operation. All characters of the string are '1', game over.

 Alice spends $ 2 $ dollars while Bob spends $ 0 $ dollars. Hence, Bob always wins.

## 样例 #1

### 输入

```
2
4
1001
1
0```

### 输出

```
BOB
BOB```

# 题解

## 作者：Aw顿顿 (赞：21)

## 题意

给定一个回文串，A 和 B 分别操作，可以将一个 $0$ 改成 $1$ 消耗 $1$ 咕值，也可以反转整个串不消耗咕值。A 纤手，问谁能赢？

## 解法

由于这是一个回文串，翻转不影响其长相，所以我们可以把它看做一个“缓招”，这样进行依次先后手的互换（我能修改，但我就不改，哎，就是玩儿）。

对于有偶数个 $0$ 的情况，A 在哪里修改，B 也可以在其对应的位置修改保证回文串一直是一个回文串，等到还剩下两个零的时候，A 修改一个，B 翻转一次，A 再修改一次，B 比 A 少两次，赢了。

对于有奇数个 $0$，如果只有一个 $0$ 在正中间，B 就赢了。如果不止的话，A 修改完之后就进入了上一种情况，A 肯定能赢。


所以在 $0$ 有奇数个且大于一的情况下，A 能赢，反之 B 能赢。

所以代码不难实现了。

---

## 作者：灵茶山艾府 (赞：10)

下文用 A 表示 Alice，B 表示 Bob。

从 $\texttt{0}$ 的个数的奇偶性讨论（博弈论套路），记 $\texttt{0}$ 的个数为 $c$。

若 $c$ 为偶数，则无论 A 在哪里修改，B 就在对应的位置修改，使得 B 修改完后 $s$ 仍然是回文。如此反复直到剩下 $2$ 个 $\texttt{0}$ 时，A 修改完后 B 可以翻转 $s$，这样必然会使 A 修改的次数比 B 多 $2$，B 获胜。

若 $c$ 为奇数，那么当 $c=1$ 时 B 显然必胜；当 $c>1$ 时，A 可以修改 $s$ 正中间的 $\texttt{0}$，这样丢给 B 的局面就是 $c$ 为偶数的情况，从而最终 B 修改的次数比 A 多 $1$，A 获胜。

因此当 $c$ 为奇数且 $c>1$ 时 A 必胜，否则 B 必胜。

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
		c := Count(s, "0")
		if c&1 > 0 && c > 1 {
			Println("ALICE")
		} else {
			Println("BOB")
		}
	}
}
```


---

## 作者：Ryan_Yu (赞：4)

大佬们的思路都很好，对此，我在思路的基础上举例子来促进大家理解。

由于本题的修改方式都与 $0$ 的个数产生了巨大联系，在此，我们来讨论 $0$ 的个数。

我们设先手为 $A$ ，后手为 $B$ 。

1.只有一个 $0$ 。

如：`101`

由于给出的字符串是回文的， $A$ 不能进行翻转，只能改 $0$ 为 $1$ 。

此时， $B$ 能量值减少 $0$ ， $A$ 的能量值减少 $1$ ， $B$ 胜利。

2.没有 $0$ 。

如：`111111`

$A$ 和 $B$ 都没有操作，平局。

3.有奇数个 $0$ ，但是 $0$ 的个数不为一。

如：`10001`

$A$ 不能进行翻转，为了最优解， $A$ 会将第三个改 $0$ 为 $1$ 。

由于此时字符串依旧回文（`10101`）， $B$ 只能改掉其中一个 $0$ ，此时，字符串不回文， $A$ 便翻转字符串， $A$ 翻转后 $B$ 不能翻转，只得再次改 $0$ 为 $1$ 。

此时， $B$ 能量值减少 $2$ ， $A$ 的能量值减少 $1$ ， $A$ 胜利。

总结：当有奇数个 $0$ 时， $A$ 可以把最中间的 $0$ 化为 $1$ 。

在 $B$ 进行下一次改 $0$ 为 $1$ 后，进行翻转，使得 $A$ 的能量值比 $B$ 少消耗 $1$ 。

4.有偶数个 $0$ 。

如：`1001`

$A$ 不能进行翻转，只能改掉其中一个 $0$ 为 $1$ 。

由于此时，字符串不回文， $B$ 便翻转字符串， $B$ 翻转后 $A$ 不能翻转，只得再次改 $0$ 为 $1$ 。

此时， $B$ 能量值减少 $0$ ， $A$ 的能量值减少 $1$ ， $B$ 胜利。

总结：当有偶数个 $0$ 时， $A$ 只得将 $0$ 化为 $1$ 。

此时 $B$ 进行翻转， $B$ 比 $A$ 的能量值少消耗二。

综上所述:

没有 $0$ 时，双方平局。

只有一个 $0$ 或 $0$ 的个数为偶数时，后者胜。

$0$ 的个数为奇数时，前者胜。

$\texttt{Code:}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int i,t,cnt,j,al;
string a;
int main()
{
	cin>>t;
	for(j=1; j<=t; j++)
		{
			cnt=0;
	//这里着重强调一下，由于数据是多组输入，每一轮结束后，cnt都要置0。
			cin>>al>>a;
			for(i=0; i<al; i++)
				if(a[i]=='0')
					cnt++;
			if(cnt==0)
				cout<<"draw"<<endl;
			else if(cnt%2==0||cnt==1)
				cout<<"BOB"<<endl;
			else
				cout<<"ALICE"<<endl;
		}
}
```


---

## 作者：zlqwq (赞：2)

直接分类讨论即可。

如果有偶数个 $0$，$A$ 最开始必须翻转，$B$ 就可以修改，$A$ 继续翻转，$B$ 胜。

如果有奇数个 $0$，$B$ 最开始必须翻转，$A$ 就可以修改，$B$ 继续翻转，$A$ 胜。

如果没有 $0$，则输出"DRAW"。

代码直接判断即可，说实话真的很水，个人认为不应该评黄。

---

## 作者：sto_5k_orz (赞：1)

如果全是 `1`，就直接平局了。

否则的话，分类讨论：

当只存在一个 `0` 时，显然 Bob 胜。

当 `0` 的个数为偶数时，Alice 在哪里改，Bob 就在对面改，于是最后一定是 Bob 胜。

否则，Alice 先修改一个，`0` 的个数变成偶数，可以看成 Alice 后手，Bob 先手，Alice 必胜。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define CI const int
#define gc getchar
#define Mt(a, b) memset(a, b, sizeof a)
#define pc putchar
#define W while
#define I inline
#define pb push_back
#define ll long long
#define mk_p make_pair
#define pii pair<int, int>
namespace SlowIO {
	I int read() {
		int x = 0, f = 1; char ch = gc();
		W(ch < '0' || ch > '9') {if(ch == '-') f = -f; ch = gc();}
		W(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gc();
		return x * f;
	}
	I void Read(int &x) {x = read();}
	I void Read(int &x, int &y) {Read(x), Read(y);}
	I void write(int x) {
		if(x < 0) pc('-'), x = -x;
		if(x > 9) write(x / 10);
		pc(x % 10 + '0');
	}
	I void writeln(int x) {write(x); pc('\n');}
	I void Write(int x) {write(x); pc(' ');}
} using namespace SlowIO;
CI N = 1010; int v[N], a[N], w[N], k[N];
signed main() {
	int t; Read(t); W(t--) {
		string s; int n; cin >> n >> s; int cnt = 0;
		for(int i= 0; i < n; i++) if(s[i] == '0') cnt++;
		if(!cnt) puts("DRAW"); else if(cnt == 1 || cnt % 2 == 0) puts("BOB"); else puts("ALICE");
		
	}
	return 0;
}
```

---

## 作者：joy2010WonderMaker (赞：1)

### 题目分析

我们可以分三种情况考虑。

+ 0的个数为偶数个
 
`Alice` 取走一个0，`Bob` 取走一个0。如果只剩下2个0，那么就在 `Alice` 取走一个0后翻转。这时，`Bob` 必胜。

+ 0的个数为奇数个

如果0只有1个，那 `Bob` 胜。

如果0不止1个，那么 `Alice` 取走一个0后，必然会进入0的个数是偶数个的情况。但这时是 `Alice` 必胜。

+ 没有0

很明显，输出 `DRAW`。

### AC Code

```cpp
#include<cstdio>
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        int sum=0;//计0的个数
        char a[1005];
        scanf("%s",&a);
        for(int i=0;i<n;i++)if(a[i]=='0')sum++;
        if(sum==0)printf("DRAW\n");
        else{
           if(sum%2==0||sum==1)printf("BOB\n");
	        else printf("ALICE\n");
        }
    }
    return 0;
}
```


---

## 作者：Cocoly1990 (赞：1)

分类讨论

当有偶数个$0$时，$A$最开始不能翻转，只能修改，之后$B$就翻转，$A$又只能修改，就没有然后了，$B$胜

当有奇数个$0$时，$B$最开始不能翻转，只能修改，之后$A$就翻转，$B$又只能修改，就没有然后了，$A$胜

特别的，当只有$1$个$0$时，$B$稳赢，因为$A$最开始不能翻转，只能修改唯一一个$0$

---

## 作者：wmrqwq (赞：0)

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

## 作者：YANGHU4299 (赞：0)

# CF1527B1题解

### 题目传送门：[CF1527B1](https://www.luogu.com.cn/problem/CF1527B1)

### 关键点：
  #### 输入的字符串是回文。  
### 解题思路:
  - 如果刚开始就全部是 $1$，则输出 DRAW。
  - 否则，每次 ALICE 取走一个 $0$，BOB 就可以取走一个对称位置的 $0$，直到只剩最后两个 $0$，此时他们的花费是一样的。
  - 如果 ALICE 取走了倒数第二个 $0$，这时 BOB 将字符串反转即可获胜。但是如果串的长度是奇数，就需要额外判断中间那个。

------------
### Code：
```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
int N;
string S;
int Array[1001],Count;
int main(void)
{
	BetterIO;
	#ifndef ONLINE_JUDGE
	freopen("SampleIN.in","r",stdin);
	#endif
	register int Case;cin>>Case;
	while(Case--)
	{
		register int i;cin>>N;
		Count=0;cin>>S;
		for(i=0;i<N;i++)Array[i+1]=S[i]-'0';
		register int Flag=0;
		for(i=1;i<=N;i++)if(!Array[i])Flag++;
		if(!Flag)cout<<"DRAW"<<endl;
		else
		{
			if(N&1)
			{
				if(Array[N/2+1]||Flag==1)cout<<"BOB"<<endl;
				else cout<<"ALICE"<<endl;
			}
			else cout<<"BOB"<<endl;
		}
	}
	return 0;
}
```




---

## 作者：yimuhua (赞：0)

**题意：**

给定一个回文串，$A$ 和 $B$ 分别操作，可以将一个 $0$ 改成 $1$ 消耗 $1$ 能量，也可以反转整个串不消耗能量。$A$ 先手，问谁能赢？

**思路：**

翻转这个串不影响值，可以理解为缓招，于是分三种情况考虑。

$0$ 的个数为偶数个：

$Alice$ 取走一个$0$，$Bob$ 取走一个 $0$。如果只剩下 $2$ 个 $0$，那么就在 $Alice$ 取走一个 $0$ 后翻转。这时，$Bob$ 必胜。

$0$ 的个数为奇数个：

1.如果 $0$ 只有 $1$ 个，那 $Bob$ 胜。

2.如果 $0$ 不止 $1$ 个，那么 $Alice$ 取走一个 $0$ 后，必然会进入 $0$ 的个数是偶数个的情况。这时 $Alice$ 必胜。

没有 $0$：

很明显，输出 "DRAW"。

**AC代码：**

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n;
string s;
int main() {
    cin >> t;
    while(t--) {
        int sum = 0;//统计0的个数 
        cin >> n >> s;
        for(int i = 0; i < n; i++)
            if(s[i] == '0')
                sum++;
        if(!sum)//没有0 
            cout << "DRAW\n";
        else if(!(sum % 2) || sum == 1)//0的个数为偶数个或0只有1个 
            cout << "BOB\n";
        else//0的个数为奇数个且0不止1个 
            cout << "ALICE\n";
    }
    return 0;
}
```


---

## 作者：_Clown_ (赞：0)

# 概述
|题号|难度|$AC$时间及记录|
| :----: | :----: | :----: |
|$\texttt{CF1527B1}$|$\texttt{洛谷难度:暂无评定}$|[$\texttt{On 2021/05/22}$](https://www.luogu.com.cn/record/51014982)|
# 解析
这道题目题目意思不难理解，

我们关注题目中给出了一个性质：给入的字符串回文。

那么我们可以这样考虑:

(如果刚开始就全部是 $1$，那么是 DRAW。)

否则，每一次 ALICE 取走一个 $0$，BOB 就可以取走和他对称的一个 $0$。

直到只剩最后两个 $0$，此时他们的花费是一样的。

ALICE 取走了倒数第二个 $0$，这时 BOB 将字符串反转即可获胜。

但是如果串串的长度是奇数，就要特判一下中间那个。

```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
int N;
string S;
int Array[1001],Count;
int main(void)
{
	BetterIO;
	#ifndef ONLINE_JUDGE
	freopen("SampleIN.in","r",stdin);
	#endif
	register int Case;cin>>Case;
	while(Case--)
	{
		register int i;cin>>N;
		Count=0;cin>>S;
		for(i=0;i<N;i++)Array[i+1]=S[i]-'0';
		register int Flag=0;
		for(i=1;i<=N;i++)if(!Array[i])Flag++;
		if(!Flag)cout<<"DRAW"<<endl;
		else
		{
			if(N&1)
			{
				if(Array[N/2+1]||Flag==1)cout<<"BOB"<<endl;
				else cout<<"ALICE"<<endl;
			}
			else cout<<"BOB"<<endl;
		}
	}
	return 0;
}
```

---

