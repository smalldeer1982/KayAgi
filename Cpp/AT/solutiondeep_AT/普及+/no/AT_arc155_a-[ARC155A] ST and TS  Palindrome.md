# 题目信息

# [ARC155A] ST and TS  Palindrome

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc155/tasks/arc155_a

英小文字からなる長さ $ N $ の文字列 $ S $ と正整数 $ K $ が与えられます。

以下の条件を満たす長さ $ K $ の文字列 $ S' $ が存在するか判定してください。

- $ S,\ S' $ をこの順に結合して得られる文字列は回文である
- $ S',\ S $ をこの順に結合して得られる文字列は回文である
 
$ T $ 個のテストケースが与えられるのでそれぞれについて判定してください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 10^5 $
- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ K\ \leq\ 10^{18} $
- $ S $ は英小文字からなる長さ $ N $ の文字列
- 入力される数値はすべて整数
- $ 1 $ つの入力に含まれるテストケースについて、 $ N $ の総和は $ 2\ \times\ 10^5 $ 以下
 
### Sample Explanation 1

$ 1 $ 番目のテストケースについて、例えば $ S'\ =\ {} $`ba` とすると $ S,S' $ をこの順に結合して得られる文字列 `abbaabba` は回文になっています。また、 $ S',S $ をこの順に結合して得られる文字列 `baabbaab` も回文になっています。以上より $ S'\ =\ {} $`ba` は条件を満たすので答えは `Yes` になります。 $ 2 $ 番目のテストケースについては、条件を満たす $ S' $ が存在しないことが証明できます。

## 样例 #1

### 输入

```
2

6 2

abbaab

5 3

abcbb```

### 输出

```
Yes

No```

## 样例 #2

### 输入

```
3

12 400378271514996652

njvhhvjnnjvh

10 884633988115575508

rrhiyvrrur

36 71630165869626180

vsxmxajrrduhhudrrjaxmxsvvsxmxajrrduh```

### 输出

```
Yes

No

Yes```

# AI分析结果

### 题目翻译

[ARC155A] ST and TS 回文

#### 题目描述

给定一个由小写字母组成的长度为 $N$ 的字符串 $S$ 和一个正整数 $K$。

请判断是否存在一个长度为 $K$ 的字符串 $S'$，满足以下条件：

- 将 $S$ 和 $S'$ 按顺序拼接得到的字符串是回文串。
- 将 $S'$ 和 $S$ 按顺序拼接得到的字符串是回文串。

给定 $T$ 个测试用例，请对每个测试用例进行判断。

#### 说明/提示

##### 约束

- $1 \leq T \leq 10^5$
- $1 \leq N \leq 2 \times 10^5$
- $1 \leq K \leq 10^{18}$
- $S$ 是由小写字母组成的长度为 $N$ 的字符串。
- 输入的所有数值均为整数。
- 单个输入中的所有测试用例的 $N$ 的总和不超过 $2 \times 10^5$。

##### 样例解释 1

对于第一个测试用例，例如 $S' = \text{ba}$，则 $S$ 和 $S'$ 按顺序拼接得到的字符串 `abbaabba` 是回文串。同时，$S'$ 和 $S$ 按顺序拼接得到的字符串 `baabbaab` 也是回文串。因此，$S' = \text{ba}$ 满足条件，答案为 `Yes`。对于第二个测试用例，可以证明不存在满足条件的 $S'$。

#### 样例 #1

##### 输入

```
2

6 2

abbaab

5 3

abcbb
```

##### 输出

```
Yes

No
```

#### 样例 #2

##### 输入

```
3

12 400378271514996652

njvhhvjnnjvh

10 884633988115575508

rrhiyvrrur

36 71630165869626180

vsxmxajrrduhhudrrjaxmxsvvsxmxajrrduh
```

##### 输出

```
Yes

No

Yes
```

### 算法分类
字符串

### 题解分析与结论

题目要求判断是否存在一个长度为 $K$ 的字符串 $S'$，使得 $S + S'$ 和 $S' + S$ 都是回文串。题解主要集中在如何通过字符串的循环节和回文性质来判断是否存在这样的 $S'$。

### 精选题解

#### 题解1：aiquaerjie (5星)

**关键亮点**：
- 通过KMP算法找到字符串的循环节，并利用循环节的性质判断是否存在满足条件的 $S'$。
- 详细分析了 $S$ 本身是回文串和 $S$ 不是回文串的情况，并给出了相应的判断条件。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=2e5+4;
char s[NN];
int ne[NN];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		long long k;
		scanf("%d%lld%s",&n,&k,s+1);
		ne[0]=-1;
		for(int i=2,j=0;i<=n;i++)
		{
			while(j&&s[i]!=s[j+1])
				j=ne[j];
			if(s[i]==s[j+1])
				j++;
			ne[i]=j;
		}
		bool ok=false;
		for(int i=ne[n];~i;i=ne[i])
		{
			int x=n-i;
			if(!(x%2))
			{
				x/=2;
				if(n%x||k%x||(k+n)/x%2)
					continue;
				bool flag=true;
				for(int j=1;j<=x;j++)
					if(s[j]!=s[x*2-j+1])
					{
						flag=false;
						break;
					}
				if(flag)
				{
					ok=true;
					break;
				}
			}
			else
			{
				if(n%x||k%x)
					continue;
				bool flag=true;
				for(int j=1;j<=x;j++)
					if(s[j]!=s[x-j+1])
					{
						flag=false;
						break;
					}
				if(flag)
				{
					ok=true;
					break;
				}
			}
		}
		puts(ok||!(k%n)&&!((k+n)/n%2)?"Yes":"No");
	}
	return 0;
}
```

#### 题解2：Rushroom (4星)

**关键亮点**：
- 通过将 $k$ 模 $2n$ 来简化问题，并分情况讨论 $k$ 的不同范围。
- 代码简洁，逻辑清晰，适合快速理解问题。

**核心代码**：
```cpp
ll n, k;
string s, t;
bool ans;
bool check(string st) {
    rep(i, st.size())if (st[i] != st[st.size() - 1 - i])return 0;
    return 1;
}
void solve() {
    cin >> n >> k >> s;
    k %= 2 * n;
    if (!k)ans = check(s);
    else if (k <= n) {
        t = s.substr(0, k);
        reverse(t.begin(), t.end());
        ans = check(s + t) & check(t + s);
    }
    else {
        t = "";
        rep(i, k)t += '1';
        rep(i, n)t[i] = s[n - 1 - i];
        ans = 1;
        rep(i, n) {
            if (t[k - 1 - i] != '1' && t[k - 1 - i] != s[i])ans = 0;
            t[k - 1 - i] = s[i];
        }
        if (ans)ans = check(s + t) & check(t + s);
    }
    if (ans)cout << "Yes\n";
    else cout << "No\n";
}
```

#### 题解3：golden_brick (4星)

**关键亮点**：
- 分情况讨论 $k$ 与 $n$ 的关系，通过字符串的子串和回文性质来判断是否存在满足条件的 $S'$。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
#include <bits/stdc++.h>
#define int ll
#define endl '\n'
#define il inline
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
string s;
int n, k;
il bool hw(string s) // 判回文
{
    for (int i = 0; i < s.size(); i++)
        if (s[i] != s[s.size() - i - 1])
            return 0;
    return 1;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n >> k >> s;
        if ((k / n) & 1) // 情况三
        {
            k -= n;
            string t;
            for (int i = 0; i < s.size(); i++)
                t += s[s.size() - i - 1];
            s = t + s, n *= 2;
        }
        k %= n; // 情况二
        if (s.substr(0, k) == s.substr(n - k, k)) // 情况一
            cout << (hw(s.substr(k, n - k)) && hw(s.substr(0, n - k)) ? "Yes" : "No") << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
```

### 最优关键思路

1. **KMP算法找循环节**：通过KMP算法找到字符串的循环节，利用循环节的性质判断是否存在满足条件的 $S'$。
2. **模运算简化问题**：通过将 $k$ 模 $2n$ 来简化问题，分情况讨论 $k$ 的不同范围。
3. **分情况讨论**：根据 $k$ 与 $n$ 的关系，分情况讨论并利用字符串的子串和回文性质进行判断。

### 可拓展之处

- 类似的问题可以扩展到多个字符串的拼接回文问题，或者扩展到更复杂的字符串操作。
- 可以结合其他字符串算法（如Manacher算法）来进一步优化判断回文的过程。

### 推荐题目

1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3805 【模板】Manacher算法](https://www.luogu.com.cn/problem/P3805)
3. [P3449 [POI2006]PAL-Palindromes](https://www.luogu.com.cn/problem/P3449)

---
处理用时：53.53秒