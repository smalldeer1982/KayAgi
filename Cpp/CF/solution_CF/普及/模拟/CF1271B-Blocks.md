# Blocks

## 题目描述

There are $ n $ blocks arranged in a row and numbered from left to right, starting from one. Each block is either black or white.

You may perform the following operation zero or more times: choose two adjacent blocks and invert their colors (white block becomes black, and vice versa).

You want to find a sequence of operations, such that they make all the blocks having the same color. You don't have to minimize the number of operations, but it should not exceed $ 3 \cdot n $ . If it is impossible to find such a sequence of operations, you need to report it.

## 说明/提示

In the first example, it is possible to make all blocks black in $ 3 $ operations. Start with changing blocks $ 6 $ and $ 7 $ , so the sequence is "BWWWWBBB". Then change blocks $ 2 $ and $ 3 $ , so the sequence is "BBBWWBB". And finally, change blocks $ 4 $ and $ 5 $ , so all blocks are black.

It is impossible to make all colors equal in the second example.

All blocks are already white in the third example.

In the fourth example it is possible to make all blocks white in two operations: first operation is to change blocks $ 2 $ and $ 3 $ (so the sequence is "BBW"), and then change blocks $ 1 $ and $ 2 $ (so all blocks are white).

## 样例 #1

### 输入

```
8
BWWWWWWB
```

### 输出

```
3
6 2 4
```

## 样例 #2

### 输入

```
4
BWBB
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5
WWWWW
```

### 输出

```
0
```

## 样例 #4

### 输入

```
3
BWB
```

### 输出

```
2
2 1 
```

# 题解

## 作者：破壁人五号 (赞：3)

## 题意

- 有一行 $n$ 个方块，每个方块是黑色或者白色；
- 你可以进行多次操作（也可以不操作），每次操作制定相邻两个方块，使其颜色各自取反；
- 现在要求在 $3n$ 次操作以内把所有方块变为同一颜色，判断是否可行并输出方案（不要求操作最少）。

## 题解

既然不要求操作最少我们就可以乱搞了，为了实现方便，我的策略如下：

- 枚举 $[1,n)$ 的所有方块，只要是黑色就把它与它后面的方块取反；
- 最后一个方块可能仍然是黑色，此时：
  - 假如 $n$ 是奇数，我们把前面 $n-1$ 个格子一对一对地变成黑色；
  - 假如 $n$ 是偶数，无解。（证明：把黑色设为 $1$，白色设为 $0$，显然目标状态为 $\sum a_i=0\ \text{or}\ n$；每次操作不会改变 $\sum a_i$ 的奇偶性，也就无法把 $\sum a_i=1$ 操作成 $0$。）

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int getint(){
    int ans=0,f=1;
    char c=getchar();
    while(c>'9'||c<'0'){
        if(c=='-')f=-1;
        c=getchar();
	}
    while(c>='0'&&c<='9'){
        ans=ans*10+c-'0';
        c=getchar();
    }
    return ans*f;
}
 
int a[1000];
vector<int>sol;
int main(){
    int n=getint();
    for(int i=1;i<=n;i++){
        char c=' ';
        cin>>c;
        a[i]=(c=='W'?0:1);
    }
    for(int i=1;i<n;i++){
        if(a[i]){
            sol.push_back(i);
            a[i]=1-a[i];
            a[i+1]=1-a[i+1];
        }
    }
    if(a[n]){
        if(n&1){
            for(int i=1;i<n;i+=2){
                sol.push_back(i);
            }
        }else{
            puts("-1");
            return 0;
        }
    }
    cout<<sol.size()<<endl;
    for(int i=0;i<sol.size();i++){
        cout<<sol[i]<<" ";
    }
    return 0;
}

```


---

## 作者：过氧化氢_syq0057 (赞：1)

仔细观察题面，我们可以发现不需要最小化操作步数，而且只需要在 $3n$ 步以内完成就行。

思考最暴力的方法，我们从左到右把黑色的方块和他的下一个方块翻转，一直到最后一个方块，这样前 $n-1$ 个方块为白色，我们只需要讨论第 $n$ 个方块的颜色。

若为白色，显然完成；若为黑色，则看 $n-1$ 是否为偶数，若为偶数，我们将前 $n-1$ 个方块一对一对翻转，若为奇数，则无解。

可以证明最劣情况下步数不大于 $2n$。

这方法其实很暴力。

对于全是 ```B``` 的数据，它会翻转一遍再翻转回来，但更优答案显然为 $0$。

感觉可以降橙。

### Code

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>
using namespace std;
const int N = 205;
const int M = 605;
#define ll long long
const int INF = 0x3f3f3f3f;
const int mod = 1000000007;
int n;
char s[N];
int ans[M], op;
int main() {
	scanf("%d%s", &n, s);
	for (int i=0; i<n-1; i++) {//不能到最后一个
		if (s[i] == 'B') {
			s[i] = 'W';
			ans[++op] = i;
			if (s[i + 1] == 'B') s[i + 1] = 'W';
			else s[i + 1] = 'B';
		}
	}
	if (s[n - 1] != 'W') {
		if (n & 1) {
			for (int i=0; i<n-1; i+=2)
				ans[++op] = i;
		}
		else {
			printf("-1\n");
			return 0;
		}
	}
	printf("%d\n", op);
	for (int i=1; i<=op; i++)
		printf("%d ", ans[i] + 1);//程序中字符串下标从0开始，题目要求从1
	return 0;
}
```

---

## 作者：IYSY2009I (赞：1)

首先容易发现，操作前后颜色的格子数量的奇偶性不变。因此想要让格子全部变成一种颜色，必须清除格子数量为偶数的颜色，如果两种颜色的格子都有奇数个，直接输出 `-1`。

其次可以发现 $3n$ 的操作次数限制不会对答案造成任何约束。因为同两个相邻格子操作多次是没有意义的，所以操作次数最多为 $n-1$。

稍加思考就可以得到一种操作方法：从左往右扫一遍格子，一旦发现一个想要改变的格子，就将其与右边的格子进行一次操作。显然的，在有解的情况下，这种方法一定可以得到一种方案。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
int op[605];
int main(){
	int n=read();
	string s;
	cin>>s;
	int b=0,w=0;
	for(int i=0;i<s.size();i++){
		if(s[i]=='B') b++;
		else w++;
	}
	if(b%2&&w%2){
		printf("-1");
		return 0;
	}
	int cnt=0;
	if(b%2==0){
		for(int i=0;i<s.size();i++)
			if(s[i]=='B'){
				cnt++;
				op[cnt]=i+1;
				s[i]='W';
				if(s[i+1]=='W') s[i+1]='B';
				else s[i+1]='W';				
			}
		printf("%d\n",cnt);
		for(int i=1;i<=cnt;i++)
			printf("%d ",op[i]);
		return 0;
	}
	for(int i=0;i<s.size();i++)
		if(s[i]=='W'){
			cnt++;
			op[cnt]=i+1;
			s[i]='B';
			if(s[i+1]=='W') s[i+1]='B';
			else s[i+1]='W';				
		}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)
		printf("%d ",op[i]);
	return 0;
}
```


---

## 作者：Hooch (赞：1)

### 判断无解

我们的读了题之后发现一个颜色序列想要变成纯色的，就必须有一种颜色的**数量是偶数**。

为什么必须是偶数呢？因为如果是奇数那么最后**无论操作多少次，都会至少剩下一个**。

是偶数的话就可以刚好两个两个地操作完。

### 处理操作序列

我们可以将**把 `W` 消除**与**把 `B` 消除**分类处理步数。

将其中一种颜色消除就是**每有两个相邻的颜色时就直接消除**。

否则**将这一格一格一格地翻转过去**。

如样例 1：

```
BWWWWWWB
```

当我们考虑消除 `B` 时。

处理到一个单独的 `B`，我们就如下操作翻转过去了：

```
BWWWWWWB->
WBWWWWWB->
WWBWWWWB->
...
WWWWWWBB
```

然后我们就能消除最后两个 `B` 了。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n; string s;
struct node {int tot, xl[205];} b, w;
//两个结构体记录消除两种颜色分别的步数和答案序列
inline void work(node &p, char a) {
	p.tot = 0;
	for (int i(0); i < n;) {
		if (s[i] == a) {
			if (s[i + 1] == a) p.xl[++p.tot] = i, i += 2; //两个相同颜色相邻
			else {
				int j = i + 1;
				for (; s[j] != a; ++j) ;
				for (int k = i; k < j - 1; ++k) p.xl[++p.tot] = k; //往后翻转并记录入答案序列
				p.xl[++p.tot] = j - 1;
				i = j + 1; 
			}
		} else ++i;
	}
}
main() {
	ios::sync_with_stdio(0);
	cin >> n >> s;
	int W = 0, B = 0;
	for (int i(0); i < n; ++i) if (s[i] == 'B') ++B; else ++W;
	if ((W & 1) && (B & 1)) return (cout << "-1"), 0; b.tot = w.tot = 0x3f3f3f3f;
	if (!(B & 1)) work(b, 'B');
	if (!(W & 1)) work(w, 'W');
	if (b.tot < w.tot) {
		cout << b.tot << endl;
		for (int i = 1; i <= b.tot; ++i) cout << b.xl[i] + 1 << " ";
	} else {
		cout << w.tot << endl;
		for (int i = 1; i <= w.tot; ++i) cout << w.xl[i] + 1 << " ";
	}
} 
```



---

## 作者：andyli (赞：1)

考虑使用动态规划，分两次计算，第一次计算全部变为B的最小操作次数，第二次计算全部变为W的最小操作次数，并在dp过程中求出操作位置。  

$dp(i, 0)$（以下简写为$dp(i)$）表示把前$i$个方块都变为B的最小操作次数，分三种情况考虑。  

1. 当$s_i$为B时，其中$s$表示初始方块的颜色序列，则转移至$dp(i-1)$，此时无需任何变换。  

2. 当$s_{i-1}$与$s_i$均为W时，可转移至$dp(i-2)+1$，此时i-1位需变换1次。  

3. 当$s_{i-1}$为B，且$s_i$为W时，通过观察发现转移为$dp(t - 1) + i - t$，其中$t$为前i个方块反序后第一次出现W的位置。此时以t~i-1位左操作方块，都需变换1次。  

全变为W的$dp(i, 1)$同理。  
在程序实现中，先预处理对于$1\leq i\leq n$情况的每一个$i$对应的$t$的值。注意dp边界条件。  
主要代码如下：  
```cpp
const int maxn = 205, INF = 0x3f3f3f3f;
const char* r = "BW";

char str[maxn];
int t[2][maxn], n;
vector<int> ans[2];
int dp(int i, int f)
{
    if (i < 1)
        return 0;
    if (i == 1)
        return str[i] == r[f] ? 0 : INF;
    if (i == 2) {
        if (str[2] == r[f])
            return dp(1, f);
        if (str[1] == r[f])
            return INF;
        ans[f].push_back(1);
        return 1;
    }
    if (str[i] == r[f])
        return dp(i - 1, f);
    if (str[i - 1] == r[f]) {
        if (str[i - 2] == r[f ^ 1]) { // 情况1的特殊情况
            int d = dp(i - 3, f) + 2;
            ans[f].push_back(i - 2), ans[f].push_back(i - 1);
            return d;
        }
        if (t[f][i] != -1) {
            int d = dp(t[f][i] - 1, f) + i - t[f][i];
            for (int j = t[f][i]; j < i; j++)
                ans[f].push_back(j); // t~i-1各操作1次
            return d;
        }
        return INF;
    }
    ans[f].push_back(i - 1);
    return dp(i - 2, f) + 1;
}
void init(int f)
{
    int p = -1;
    for (int i = 1; i <= n; i++)
        if (t[f][i] = p; str[i] == r[f ^ 1])
            p = i;
}
void print(int f)
{
    for (int i = 0; i < ans[f].size(); i++)
        io.write(ans[f][i], " \n"[i == ans[f].size() - 1]);
}
int main()
{
    io.read(n);
    io.read(str + 1);
    init(0), init(1);
    int d0 = dp(n, 0), d1 = dp(n, 1);
    if (d0 < INF || d1 < INF) {
        writeln(min(d0, d1));
        print(d0 >= d1);
    } else
        writeln(-1);
    return 0;
}
```

---

## 作者：YLWang (赞：1)

我们从左往右遍历，每遇见一个B，就翻转当前这个B和下一个字母。

容易发现这样一遍遍历之后，只有可能有两种情况。

第一种，全部都是W。完了。

第二种，最后一个是B，前$n-1$个数都是w，所以直接讨论可不可以把这些都变成B就可以了。如果$n-1$是偶数，那么就可以实现。否则不能实现。

```cpp
#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define ll long long
#define reaD() read()
#define pb push_back
#define mkp make_pair
#define mst(a,b) memset(a,b,sizeof(a))
#define foR(i, k, j) for(register int i = (k); i >= (j); i--)
#define For(i, k, j) for(register int i = (k); i <= (j); i++)
#define DEBUG fprintf(stderr, "***IAKIOI***\n")
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
const int MOD = 998244353; //
using namespace std;
inline void ckmax(int &a, int b) {a = max(a, b);}
inline void ckmin(int &a, int b) {a = min(a, b);}
inline void addmod(int &a, int b) {int t = a + b; a = (t >= MOD ? t - MOD : t); }
inline int read() {
    int num=0,flag=1;char c=' ';
    for(;c>'9'||c<'0';c=getchar()) if(c=='-') flag=-1;
    for(;c>='0'&&c<='9';num=num*10+c-48,c=getchar());
    return num*flag;
}
int n, a[206], q = 0;
string s;
signed main()
{
	cin >> n >> s;
	s = ' ' + s;
	For(i, 1, n)
		a[i] = s[i] == 'B', q += a[i] == 1 ? 1 : -1;
	if(abs(q) % 2 != n % 2) {
		printf("-1\n");
		return 0;
	}
	vector < int > ans;
	ans.clear();
	For(i, 1, n-1) {
		if(a[i] == 1) {
			a[i] ^= 1, a[i+1] ^= 1;
			ans.pb(i);
		}
	}
	if(!a[n]) {
		cout << ans.size() << endl;
		for(auto v : ans)
			cout << v << ' ';
		return 0;
	} else {
		if(n % 2 == 0) {
			printf("-1\n");
			return 0;
		}
		for(int i = 1; i < n; i += 2) {
			a[i] ^= 1, a[i+1] ^= 1;
			ans.pb(i);
		}
		cout << ans.size() << endl;
		for(auto v : ans)
			cout << v << ' ';
		return 0;
	}
    return 0;
}
```

---

## 作者：LZYAC (赞：0)

## 思路

注意到题目的关键：不要求次数最少。

于是发现此题为典型的**开关问题**。

开关问题的最重要的特性：

**一个点最多被开一次：因为偶数次不变，奇数次跟开一次相同。**

所以其实题目给的 $3n$ 是没有必要的，每个点最多操作一次，不可能重复操作。

所以策略就显而易见了：分析两种颜色，如果不是我们想要的颜色就翻转它和它的下一个。最后判断最后一个是否是我们想要的颜色。（因为已经保证前面的所有颜色都是我们想要的）

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
vector<int> ans;
string s;
signed main(){
	cin>>n>>s;
	for(int i=0;i<n-1;i++){
		if(s[i]!='W'){
			s[i]='W';
			ans.push_back(i+1);
			s[i+1]=(s[i+1]=='W'?'B':'W');
		}
	}
	if(s[n-1]=='W'){
		printf("%d\n",ans.size());
		for(int i=0;i<ans.size();i++) printf("%d ",ans[i]);
		return 0;
	}
	for(int i=0;i<n-1;i++){
		if(s[i]!='B'){
			s[i]='B';
			ans.push_back(i+1);
			s[i+1]=(s[i+1]=='W'?'B':'W');
		}
	}
	if(s[n-1]=='B'){
		printf("%d\n",ans.size());
		for(int i=0;i<ans.size();i++) printf("%d ",ans[i]);
		return 0;
	}
	printf("-1");
	return 0;
}
```

---

## 作者：Zaku (赞：0)

这是一题开关问题，属于标准的递推问题。它和 [翻硬币](https://www.luogu.com.cn/problem/P8597) 以及 [费解的开关](http://noi-test.zzstep.com/contest/0x00%E3%80%8C%E5%9F%BA%E6%9C%AC%E7%AE%97%E6%B3%95%E3%80%8D%E4%BE%8B%E9%A2%98/0201%20%E8%B4%B9%E8%A7%A3%E7%9A%84%E5%BC%80%E5%85%B3) 非常像，建议看一看。

### 解法：
这里以 ```BWWWWWWB``` 为例。

题目要求只能**选择两个相邻的方块**，所以可操作的位置只有 $n-1$ 个。同时，每个位置只有**操作**和**不操作**两种可能，因为操作两次等价于未操作，操作三次等价于操作一次。

因此，我们只需要考虑每块砖是否操作即可。让我们看向样例：

假设我们要把它置为全白。

由于第一块砖只会被第一次操作影响，所以必须被操作，变成 ```WBWWWWWB```。

第二块砖此时为黑，所以也必须被操作，变成 ```WWBWWWWB```。

以此类推，最后只需判断最后一块砖的颜色是否与第一块砖相同即可。

时间复杂度是线性的。

当然也可以高斯消元，但~~我不会~~用在这里有些杀鸡用牛刀了。

代码：
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int n;
void update(char &c){//转换函数
    if (c == 'W') c = 'B';
    else c = 'W';
}
bool check(string s, char c){//判断合法
    vector<int> ans;//存储操作
    for (int i = 0; i < n - 1; i ++ ){//n-1次操作
        if (s[i] != c){//不相等，就转换s[i]与s[i+1]
            update(s[i]);
            update(s[i + 1]);
            ans.push_back(i);//把操作装入容器
        }
    }
    if (s[n - 1] != s[0]) return false;//头尾元素不相等即不合法
    cout << ans.size() << '\n';//输出操作数
    for (auto x : ans)//输出每个操作
        cout << x + 1 << ' ';//注意，操作是从1开始的
    if (ans.size()) cout << '\n';//如果还有就换行
    return true;
}
int main()
{
    cin >> n;
    string s;
    cin >> s;
    if (!check(s, 'W') && !check(s, 'B'))//当全变白不行并且全变黑不行，无解
        printf("-1\n");
    return 0;
}
```

---

## 作者：YYen (赞：0)

### 思路：模拟
只有两种情况，方块最终调整为全部白色，或者最终调整为全部黑色，两种情况都不行则 $ -1 $ 。

因此可以从第 $ 1 $ 个方块枚举到第 $ n - 1 $ 个方块，只要枚举到的第 $ i $ 个方块不是想要的最终颜色，就把第 $ i $ 和第 $ i + 1 $ 个方块翻转颜色。枚举结束后，如果第 $ n $ 个方块是最终颜色，则调整为该颜色的方案可行，否则不可行。

### 代码
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

char s1[205], s2[205];

void change(int idx, char s[])
{
    if (s[idx] == 'B') s[idx] = 'W';
    else s[idx] = 'B';
}

string rev(int num)
{
    string ans = "";
    while (num)
    {
        ans += num % 10 + '0';
        num /= 10;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main()
{
    int n, flag = 0, ans;
    string s;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> s1[i];
        s2[i] = s1[i];
    }
	
    // 第1次模拟全部换为W
    s = "", ans = 0;
    for (int i = 1; i <= n - 1; i++)
    {
        if (s1[i] == 'B') change(i, s1), change(i + 1, s1), ans++, s += rev(i) + ' ';
    }
    if (s1[n] == 'W')
    {
        cout << ans << endl;
        if (ans) cout << s << endl;
        return 0;
    }
	
    // 第2次模拟全部换为B
    s = "", ans = 0;
    for (int i = 1; i <= n - 1; i++)
    {
        if (s2[i] == 'W') change(i, s2), change(i + 1, s2), ans++, s += rev(i) + ' ';
    }
    if (s2[n] == 'B')
    {
        cout << ans << endl;
        if (ans) cout << s << endl;
        return 0;
    }
    cout << -1 << endl;
    return 0;
}
```


---

