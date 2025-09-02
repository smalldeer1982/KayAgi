# A TRUE Battle

## 题目描述

Alice and Bob are playing a game. There is a list of $ n $ booleans, each of which is either true or false, given as a binary string $ ^{\text{∗}} $ of length $ n $ (where $ \texttt{1} $ represents true, and $ \texttt{0} $ represents false). Initially, there are no operators between the booleans.

Alice and Bob will take alternate turns placing and or or between the booleans, with Alice going first. Thus, the game will consist of $ n-1 $ turns since there are $ n $ booleans. Alice aims for the final statement to evaluate to true, while Bob aims for it to evaluate to false. Given the list of boolean values, determine whether Alice will win if both players play optimally.

To evaluate the final expression, repeatedly perform the following steps until the statement consists of a single true or false:

- If the statement contains an and operator, choose any one and replace the subexpression surrounding it with its evaluation.
- Otherwise, the statement contains an or operator. Choose any one and replace the subexpression surrounding the or with its evaluation.

 For example, the expression true or false and false is evaluated as true or (false and false) $ = $ true or false $ = $ true. It can be shown that the result of any compound statement is unique. $ ^{\text{∗}} $ A binary string is a string that only consists of characters $ \texttt{0} $ and $ \texttt{1} $

## 说明/提示

In the first testcase, Alice can place and between the two booleans. The game ends as there are no other places to place operators, and Alice wins because true and true is true.

In the second testcase, Alice can place or between the middle true and the left false. Bob can place and between the middle true and the right false. The statement false or true and false is false.

Note that these examples may not be the best strategies for either Alice or Bob.

## 样例 #1

### 输入

```
5
2
11
3
010
12
101111111100
10
0111111011
8
01000010```

### 输出

```
YES
NO
YES
YES
NO```

# 题解

## 作者：jubaoyi2011 (赞：3)

## 思路

这题的 and 的优先级比 or 的高是一个突破口

首先，Alice 可以把 or 放在两个连续的 $1$ 之间，然后无论 Bob 接下来把 and 放在哪里，Alice 总有一个 $1$ 的另外一侧是空的，可以再放一个 or，然后赢得比赛。所以头尾有 $1$ 的情况是显然的。

然后，如果所以如果 Alice 能够在两个 or 中间放置一个值为真的表达式，那么 Alice 就一定会赢。最简单的方式就是想办法把两个 or 放在一个 $1$ 的两侧。

最后，如果头尾没有 $1$ 也没有相邻的两个 $1$。这个时候，如果 Alice 把 or 放在一个 $1$ 的一侧，Bob 可以把 and 放在这个 $1$ 的另一侧，因为 and 的优先级比 or 的高，所以这个 $1$ 就率先与 and 另一侧的 $0$ 进行运算从而得到假,所以当且仅当上述两种条件下，Alice 才能获胜。

## 代码


```cpp
#include<bits/stdc++.h>
int T,n;
char ch[100005];
signed main(){
	cin>>T;
	while(T--){
		scanf("%d",&n);
		scanf("%s",ch+1);
		bool f=0;
		if(ch[1]=='1'||ch[n]=='1'){
			puts("YES");
			continue;
		}
		for(int i=1;i<n;i++){
			if(ch[i]=='1'&&ch[i+1]=='1'){
				f=1;
				break;
			}
		}
		if(f) puts("YES");
		else puts("NO");
	}
}
```

---

## 作者：Yxy7952 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF2030C)


## 关于题意

两个注意点：

1.  **Alice 先走**。
2.  **两个数之间最多有一个操作，并且式子前后不可使用操作**。

## 思路

我们注意到翻译里这句话：

> Alice 希望最后运算的值为 $1$，Bob 希望它为 $0$。

那 Alice 肯定使用 $\operatorname{or}$ 操作，价值最大，因为除了在 $0\operatorname{or}0$ 情况下会变成 $0$，其他情况都会变成 $1$。

而 Bob 肯定使用 $\operatorname{and}$ 操作，价值最大，因为除了在 $1\operatorname{and}1$ 情况下会变成 $1$，其他情况都会变成 $0$。

我们就可以简化一下题目，方便思考。

这道题显然是找规律题，我们思考什么时候 Alice 必赢，或者必输？

### 1.

先来看最简单的情况，因为：

>式子前后不可使用操作。

所以如果第一个数或者最后一个数是 $1$，Alice 先放一个 $\operatorname{or}$ 在旁边。那不管 Bob 在哪里放 $\operatorname{and}$ 最后都会剩下一个 $1$。

比如：$1\operatorname{or}(0\operatorname{and}1)$。

### 2.
假设有一种情况 $A\operatorname{or}1\operatorname{or}B$，那么显然，不管 $A$ 和 $B$ 的值是什么，这个表达式的值都为 $1$。

如果一表达式中有连续的两个 $1$，比如 $0110$，那么 Alice 可以在两个 $1$ 中间放一个 $\operatorname{or}$，之后不管 Bob 消掉了哪个方向的 $1$，Alice 都可以取胜。

比如：$(0\operatorname{and}1)\operatorname{or}1\operatorname{or}0$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int T,n;
string s; 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>T;
	while(T--){
		bool f=0;
		cin>>n>>s;
		if(s[0]=='1'||s[n-1]=='1'){
			cout<<"YES\n";
			continue;
		}
		for(int i=1;i<n;i++){
			if(s[i]=='1'&&s[i-1]=='1'){
				cout<<"YES\n";
				f=1;
				break;
			}
		}
		if(!f) cout<<"NO\n";
	}
	return 0;
}
```
-----------
2024.11.5：修改了一些错误。

---

## 作者：Sakura_Emilia (赞：1)

# Solution

一般这种 Codeforces 前面的博弈论问题都不会太难，往往是近乎于结论题。检查给定数据，几种情况下是 Alice 必胜，其余的是 Bob 胜。

由于与运算先进行，最后将结果或起来。一堆或运算的数，只要有一个为 $1$，最终的结果即是 $1$。

因此先手的 Alice 的策略是，只要将一个 $1$ 给使用或运算符围起来，使这个 $1$ 参与最后的将结果或起来，即可获胜；而 Bob 就是阻止 Alice 达成这个目标。

由于 Alice 先手，只要有某一个 $1$ 位于左右两个端点，只需要一个或运算符即可保护下来这个 $1$。或者是输入数据全部都是 $1$ ~~废话~~，或者是存在某个长度大于等于 $2$ 的全部为 $1$ 的连续子串，这种情况下 Alice 一定可以保护下来其中一个端点上的 $1$。

# Code

```cpp
#include <bits/stdc++.h>
#define Ciallo main
#define int long long
using namespace std;

int T, n;
string s;

inline void solve() {
    cin >> n >> s;
    int zeroNum = 0, oneNum = 0, temp = 0;
    for(char ch : s)
        if(ch == '0')
            zeroNum++, temp = 0;
        else{
            temp++;
            oneNum = max(oneNum, temp);
        }

    if(zeroNum == 0 || oneNum >= 2 || s[0] == '1' || s[n-1] == '1')
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}

signed Ciallo() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> T;
    while(T--)
        solve();

    return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

由于与比或优先级高，而且是双方放完运算符再进行计算结果，所以首尾有 $1$ 的情况下，Alice 总可以在其旁边放上或运算，使得最后算出的答案为 $1$，获得胜利。

这个结论能够通过样例，但是会 WA on test 2。

哪里有问题？再次观察样例，发现若有连续的 $1$ 也能获胜，这是因为 Alice 在其中间先放上或运算符，然后 Bob 不管在两边哪里放与运算符，Alice 只需要在另一边放或运算符就可以了。

---

## 作者：Wide_Master (赞：0)

博弈论。

同时，因为 and 比 or 的优先级高。

那么，Alice 可以将 or 放在两个连续的 $1$ 之间，这样的话，Alice 的表达式的值总有一边为 $1$。然后无论 Bob 接下来把 and 放在哪里，Alice 在神之一手，直接抬走。然后，如果所以如果 Alice 能够在两个 or 中间放置一个结果为真的表达式，那么 Alice 就能将 Bob 直接抬走，那我们知道 or 想要值为真只要一边为 $1$ 就够了，所以直接在一个 $1$ 的两旁放 or 就能神之一手，直接抬走了。

最后，如果头尾均没有 $1$ 切没有相邻的 $1$，那么这个时候，如果 Alice 把 or 放在一个 $1$ 的一侧，那么 Bob 可以在另一侧放 and，因为 and 的优先级比 or 高，所以最后表达式会为假。所以当且仅当上述两种条件下，Alice 才能获胜。

代码：

```cpp
//By Wide_Master
#include<bits/stdc++.h>
using namespace std;
int T,n,f;
string s;
signed main()
{
	cin>>T;
	while(T--){
		cin>>n;
        cin>>s;
        s=" "+s;
		f=0;
		if(s[1]=='1'||s[n]=='1'){
			puts("YES");
			continue;
		}
		for(int i=1;i<n;i++){
			if(s[i]=='1'&&s[i+1]=='1'){
				f=1;
				break;
			}
		}
		if(f) puts("YES");
		else puts("NO");
	}
}
``````

---

## 作者：Dollartree (赞：0)

### 解题思路

**注意**

1. Alice 先走。

2. Alice 希望最后运算的值为 $1$，Bob 希望它为 $0$。

3. 优先级满足 $\operatorname{and}>\operatorname{or}$。

**解题过程**

1. 研究 $\operatorname{and}$ 和 $\operatorname{or}$ 对相邻两个 $0$ 或 $1$ 的影响，发现相邻两个 $0$ 或 $1$，只有四种情况，$0$ 和 $1$、$1$ 和 $0$、$0$ 和 $0$、$1$ 和 $1$。而且只有一种情况 $1$ 和 $1$ 会使得经过 $\operatorname{and}$ 运算后结果为 $1$，同时只有一种情况 $0$ 和 $0$ 会使得经过 $\operatorname{or}$ 运算后结果为 $0$。根据题意 Alice 使用的肯定是 $\operatorname{or}$，Bob 使用的肯定是 $\operatorname{and}$。

2. 又看到注意的第三点，可以发现只要开头或结尾有 $1$，例如 $100$ 在 $1$ 的后面填上 $\operatorname{or}$ 无论接下来填什么，结果均为 $1$，$001$ 把 $\operatorname{or}$ 填在 $1$ 前面，同理。

3. 但是还有一种特殊情况，如果表达式中有两个连续的 $1$，例如 $001100$，那么 Alice 可以在两个 $1$ 中间放一个 $\operatorname{or}$，之后无论 Bob 用 $\operatorname{and}$ 操作令左右其中一个方向为 $1$，表达式均得出 $1$，Alice 可以取胜。

### 代码

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
//const int INF=99999999;
int main()
{

	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int t;
	cin>>t;
	while(t--)//注意多组数据。
	{
		int n;
		string s;
		cin>>n>>s;
		int flag=0;//0为表达式为0，1为表达式为1。
		if(s[0]=='1'||s[s.length()-1]=='1')
		{
			flag=1;
		 } 
		for(int i=0;i<s.length()-1;++i)//因只有n-1个长度为2的序列，因此遍历至n-1即可。
		{
			if(s[i]=='1'&&s[i+1]=='1')
			{
				flag=1;
			}
		}
		if(flag==1)
		{
			cout<<"YES\n";//要回车。
		}
		else
		{
			cout<<"No\n";
		}
	}
}
```

[提交](https://codeforces.com/problemset/submission/2030/304504568)

---

## 作者：omclude (赞：0)

## [Luogu Link](https://www.luogu.com.cn/problem/CF2030C) | [Codeforces Link](https://codeforces.com/problemset/problem/2030/C)

## $\texttt{Describe}$

给一个长度为 $n$ 的二进制序列，Alice 和 Bob 在相邻两个 0/1 中间 **分别** 加 $\operatorname{or}$ 或 $\operatorname{and}$ 操作，优先级满足 $\operatorname{and} > \operatorname{or}$。

Alice 希望最后运算的值为 $1$，Bob 希望它为 $0$。

若双方进行最优操作，问最后值为 $0$ （ `YES` ）还是 $1$ （ `NO` ）。

## $\texttt{Solution}$

### Hits 1: 观察首尾性质





注意到当序列首是 $1$ 的时候，只要 Alice 在后面加个 $\operatorname{or}$，整个序列的值 **一定** 为 $1$。

同理当序列尾是 $1$ 的时候，值也为 $1$。

另外，当序列出现了 $\dots 11 \dots$ 的时候，Alice 一定可以构造出 $\dots \operatorname{or} 1 \dots 1 \operatorname{or}$ 或者 $\dots 1 \operatorname{or} 1 \operatorname{or} \dots$ 的形式使得整个序列为 $1$。

其余的情况一定不可以。

## $\texttt{Code}$


```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e5 + 10;

void solve() {
	int n; cin >> n;
	string s; cin >> s;
	if ((s.back() == '1' || s.front() == '1') || s.find("11") != s.npos) {
		cout << "YES\n";
	}else {
		cout << "NO\n";
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
	
	int T; cin >> T; while (T --) solve();
	return 0;
}
```

---

## 作者：zsfzhjf (赞：0)

因为与的运算级比或高

那么每一次用在 $1$ 边用一个或都可以被与分隔开

最后就是只有开头或结尾是 $1$ 或者有连续的 $1$ 就是必胜的


```cpp
#include<bits/stdc++.h>
const int MAXN=2e5+5;
int T,n;
char ch[MAXN];
signed main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		scanf("%s",ch+1);
		bool f=0;
		if(ch[1]=='1'||ch[n]=='1'){
			puts("YES");
			continue;
		}
		for(int i=1;i<n;i++){
			if(ch[i]=='1'&&ch[i+1]=='1'){
				f=1;
				break;
			}
		}
		if(f) puts("YES");
		else puts("NO");
	}
}
```

---

## 作者：HNOIRPplusplus (赞：0)

由于 or 的优先级小于 and，所以如果 Alice 能够在两个 or 中间放置一个值为 true 的表达式，那么 Alice 就一定会赢。最简单的方式就是想办法把两个 or 放在一个 1 的两侧。

结论：如果有两个连续的 1，或者头尾有 1，则答案为 YES，否则为 NO。

充分性证明：Alice 可以把 or 放在两个连续的 1 之间，然后无论 Bob 接下来把 and 放在哪里，Alice 总有一个 1 的另外一侧是空的，可以再放一个 or，然后赢得比赛。头尾有 1 的情况是显然的。

必要性证明：如果没有上述条件，则头尾没有 1 也没有相邻的两个 1。这个时候，如果 Alice 把 or 放在一个 1 的一侧，Bob 可以把 and 放在这个 1 的另一侧，然后这个 1 就率先与 and 另一侧的 0 进行运算从而得到 false。

得到了上面的结论，我们就可以很简单地解决这个问题了。

代码：

``` cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1005;

int a[N];

void solve() {
  int n;
  string s;
  cin >> n >> s;
  s = ' ' + s;
  if(s[1] == '1' || s[n] == '1') {
    cout << "YES\n";
    return;
  }
  for(int i = 1; i < n; i++) {
    if(s[i] == '1' && s[i + 1] == '1') {
      cout << "YES\n";
      return;
    }
  }
  cout << "NO\n";
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    solve();
  }
}
```

---

## 作者：114514xxx (赞：0)

## 做法
注意到 $\operatorname{and}$ 的优先级是比 $\operatorname{or}$ 更高的，这是解决这道题目首先需要知道的。

于是我们可以大胆猜结论：序列首尾有 $1$ 或者中间有两个及以上的连续的 $1$ 时，Alice 可以胜利，反之 Bob 可以胜利。

如何得到这个结论呢？我们可以发现当首尾为 $1$ 时，因为 Alice 先手，必定可以在首尾上插入 $\operatorname{or}$ 使得序列最终为 $1$。

当中间有两个及以上的连续的 $1$ 时，在两个连续的 $1$ 中间插入 $\operatorname{or}$ 即可。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+25;
int n,minn,maxn,t;
bool a[N];
char ch;
inline void solve(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>ch,a[i]=(ch=='1');
    if(a[1]||a[n]){
        cout<<"YES\n";
        return;
    }
    for(int i=2;i<=n;i++){
        if(a[i]==a[i-1]&&a[i]==1){
            cout<<"YES\n";
            return;
        }
    }
    cout<<"NO\n";
}
int main(){
    cin>>t;
    while(t--)solve();
    return 0;
}

```

---

