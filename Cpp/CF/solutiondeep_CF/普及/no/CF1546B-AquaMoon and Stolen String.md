# 题目信息

# AquaMoon and Stolen String

## 题目描述

AquaMoon had $ n $ strings of length $ m $ each. $ n $ is an odd number.

When AquaMoon was gone, Cirno tried to pair these $ n $ strings together. After making $ \frac{n-1}{2} $ pairs, she found out that there was exactly one string without the pair!

In her rage, she disrupted each pair of strings. For each pair, she selected some positions (at least $ 1 $ and at most $ m $ ) and swapped the letters in the two strings of this pair at the selected positions.

For example, if $ m = 6 $ and two strings "abcdef" and "xyzklm" are in one pair and Cirno selected positions $ 2 $ , $ 3 $ and $ 6 $ she will swap 'b' with 'y', 'c' with 'z' and 'f' with 'm'. The resulting strings will be "ayzdem" and "xbcklf".

Cirno then stole away the string without pair and shuffled all remaining strings in arbitrary order.

AquaMoon found the remaining $ n-1 $ strings in complete disarray. Also, she remembers the initial $ n $ strings. She wants to know which string was stolen, but she is not good at programming. Can you help her?

## 说明/提示

In the first test case, "aaaaa" and "bbbbb" exchanged all positions, and "ccccc" is the stolen string.

In the second test case, "aaaa" and "bbbb" exchanged two first positions, and "cccc" is the stolen string.

This is the first test in the hack format:

```
<pre class="verbatim"><br></br>3<br></br>3 5<br></br>aaaaa<br></br>bbbbb<br></br>ccccc<br></br>1 2 5 1 2 3 4 5<br></br>2 1 3<br></br>3 4<br></br>aaaa<br></br>bbbb<br></br>cccc<br></br>1 2 2 1 2<br></br>2 1 3<br></br>5 6<br></br>abcdef<br></br>uuuuuu<br></br>kekeke<br></br>ekekek<br></br>xyzklm<br></br>1 5 3 2 3 6<br></br>2 4 3 2 4 6<br></br>5 4 1 2 3<br></br>
```

## 样例 #1

### 输入

```
3
3 5
aaaaa
bbbbb
ccccc
aaaaa
bbbbb
3 4
aaaa
bbbb
cccc
aabb
bbaa
5 6
abcdef
uuuuuu
kekeke
ekekek
xyzklm
xbcklf
eueueu
ayzdem
ukukuk```

### 输出

```
ccccc
cccc
kekeke```

# AI分析结果

### 题目内容重写

# AquaMoon 和被盗的字符串

## 题目描述

AquaMoon 有 $n$ 个长度为 $m$ 的字符串。$n$ 是一个奇数。

当 AquaMoon 离开时，Cirno 尝试将这些 $n$ 个字符串配对。在配对了 $\frac{n-1}{2}$ 对后，她发现恰好有一个字符串没有配对！

在愤怒中，她打乱了每一对字符串。对于每一对字符串，她选择了一些位置（至少 $1$ 个，最多 $m$ 个），并在这些位置上交换了两个字符串中的字母。

例如，如果 $m = 6$，且两个字符串 "abcdef" 和 "xyzklm" 是一对，Cirno 选择了位置 $2$、$3$ 和 $6$，她将交换 'b' 和 'y'，'c' 和 'z'，以及 'f' 和 'm'。结果字符串将变为 "ayzdem" 和 "xbcklf"。

然后，Cirno 偷走了没有配对的字符串，并将所有剩余的字符串任意打乱顺序。

AquaMoon 发现了剩下的 $n-1$ 个字符串，完全混乱了。她还记得最初的 $n$ 个字符串。她想知道哪个字符串被偷了，但她不擅长编程。你能帮助她吗？

## 说明/提示

在第一个测试用例中，"aaaaa" 和 "bbbbb" 交换了所有位置，而 "ccccc" 是被偷的字符串。

在第二个测试用例中，"aaaa" 和 "bbbb" 交换了前两个位置，而 "cccc" 是被偷的字符串。

### 样例 #1

#### 输入

```
3
3 5
aaaaa
bbbbb
ccccc
aaaaa
bbbbb
3 4
aaaa
bbbb
cccc
aabb
bbaa
5 6
abcdef
uuuuuu
kekeke
ekekek
xyzklm
xbcklf
eueueu
ayzdem
ukukuk
```

#### 输出

```
ccccc
cccc
kekeke
```

### 算法分类

位运算

### 题解分析与结论

本题的核心思路是通过位运算（异或）来找出被偷的字符串。由于被偷的字符串在每一位上只出现一次，而其他字符串在每一位上出现偶数次，因此可以通过异或操作来快速找到被偷的字符串。

### 所选高分题解

#### 题解1：作者：Acc_Robin (赞：9)

**星级：5星**

**关键亮点：**
- 使用异或操作快速找出被偷的字符串，时间复杂度为 $O(nm)$。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
    const int N = 2e5+10;
    string s[N];
    int n,m,i,j,x;
    void work(){
        cin>>n>>m,n=n*2-1;
        for(i=1;i<=n;++i)cin>>s[i];
        for(i=0;i<m;++i,putchar(x))for(x=0,j=1;j<=n;j++)x^=s[j][i];
    }
}
int main(){
    int T;for(cin>>T;T--;putchar(10))Acc::work();
}
```

#### 题解2：作者：xkcdjerry (赞：1)

**星级：4星**

**关键亮点：**
- 同样使用异或操作，思路清晰。
- 代码简洁，易于理解。

**核心代码：**
```cpp
#include <cstdio>
#include <cstdlib>

#define int long long
#define N 100010
#define M 100010
char s[M];
int XOR[M];
void once()
{
    int n,m;
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<2*n;i++)
	{
		scanf("%s",s);
		for(int j=0;j<m;j++)
			XOR[j]^=s[j];
	}
	for(int i=0;i<m;i++)
	{
		putchar(XOR[i]);
		XOR[i]=0;
	}
	putchar('\n');
	fflush(stdout);
}
#undef int

int main()
{
    int t;
    scanf("%d",&t);
    while(t--) once();
    return 0;
}
```

#### 题解3：作者：fsy_juruo (赞：0)

**星级：4星**

**关键亮点：**
- 使用统计字符出现次数的方法，思路清晰。
- 代码简洁，易于理解。

**核心代码：**
```cpp
#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
#define LD long double
#define reg register
#define _rep(i, x, y) for(int i = x; i <= y; i++)
#define _per(i, x, y) for(int i = x; i >= y; i--)
template <typename T>
inline void read(T &x) {
	x = 0; T f = (T) 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) {if(c == '-') f = -f;}
	for(; isdigit(c); c = getchar()) x = x * 10 + c - 48;
	x *= f;
}
template <typename T, typename... Args>
inline void read(T& x, Args&... args) {
    read(x); read(args...);
}
template <typename T>
inline void write(T x) {
	if(x < 0) {x = -x; putchar('-');}
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T>
inline void writesp(T x, char sp = ' ') {write(x); putchar(sp);}

const int maxN = 1e5 + 10;
int t, n, m;
int buk[maxN];

int main() {
	std::cin >> t;
	while(t--) {
		std::cin >> n >> m;
		std::string s;
		_rep(i, 1, n) {
			std::cin >> s;
			_rep(j, 0, m - 1) buk[j] += s[j] - 'a';
		}
		_rep(i, 1, n - 1) {
			std::cin >> s;
			_rep(j, 0, m - 1) buk[j] -= s[j] - 'a';
		}
		_rep(i, 1, m) {
			putchar(buk[i - 1] + 'a');
			buk[i - 1] = 0; 
		}
		std::cout << std::endl;
		fflush(stdout);
	}
	return 0;
}
```

### 最优关键思路或技巧

使用异或操作来快速找出被偷的字符串，因为异或操作具有以下性质：
- 异或两次相同的数相当于没有异或。
- 异或操作满足交换律和结合律。

### 可拓展之处

类似的问题可以通过位运算来解决，尤其是在需要找出唯一出现一次的元素时。例如，找出数组中唯一出现一次的数字等问题。

### 推荐题目

1. [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)
2. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
3. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)

---
处理用时：49.57秒