# 题目信息

# [ARC180A] ABA and BAB

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc180/tasks/arc180_a

`A`, `B` からなる長さ $ N $ の文字列 $ S $ が与えられます．

あなたは以下の $ 2 $ 種類の操作を好きな順序で $ 0 $ 回以上繰り返すことができます．

- $ S $ の中で `ABA` となっている (連続した) 部分を選び，それを `A` で置き換える．
- $ S $ の中で `BAB` となっている (連続した) 部分を選び，それを `B` で置き換える．
 
操作後の $ S $ としてあり得る文字列の個数を $ 10^9+7 $ で割ったあまりを求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 250000 $
- $ S $ は `A`, `B` からなる長さ $ N $ の文字列
 
### Sample Explanation 1

操作後の $ S $ としてあり得るのは以下の $ 2 $ 種類の文字列です． - `ABAB`: $ 0 $ 回の操作を行うことでこの文字列を得ることができます． - `AB`: $ S= $`ABAB` の $ 1 $ 文字目から $ 3 $ 文字目までが `ABA` となっています．これを `A` で置き換えると $ S= $`AB` となります． なお，$ S= $`ABAB` の $ 2 $ 文字目から $ 4 $ 文字目までが `BAB` となっているので，これを `B` に置き換える操作も可能です． ただし，その結果得られる `AB` は重複して数えないことに注意してください．

### Sample Explanation 2

操作を $ 1 $ 度も行うことができません．

### Sample Explanation 4

$ 10^9+7 $ で割ったあまりを求めるのを忘れないようにしてください．

## 样例 #1

### 输入

```
4

ABAB```

### 输出

```
2```

## 样例 #2

### 输入

```
1

A```

### 输出

```
1```

## 样例 #3

### 输入

```
17

BBABABAABABAAAABA```

### 输出

```
18```

## 样例 #4

### 输入

```
100

ABAABAABABBABAABAABAABABBABBABBABBABBABBABBABBABBABBABBABBABBABBABAABABAABABBABBABABBABAABAABAABAABA```

### 输出

```
415919090```

# AI分析结果

### 题目内容
[ARC180A] ABA and BAB

#### 题目描述
给定一个由 `A` 和 `B` 组成的长度为 $N$ 的字符串 $S$。你可以进行以下两种操作任意次（包括 0 次）：

- 将 $S$ 中的 `ABA` 替换为 `A`。
- 将 $S$ 中的 `BAB` 替换为 `B`。

求操作后 $S$ 可能的不同字符串的个数，结果对 $10^9+7$ 取模。

#### 说明/提示
- $1 \leq N \leq 250000$
- $S$ 是由 `A` 和 `B` 组成的长度为 $N$ 的字符串。

### 题解分析与结论

#### 综合分析与结论
本题的核心思路是将字符串分解为多个独立的“交叉字符串”（即 `ABAB...` 或 `BABA...` 的形式），然后计算每个交叉字符串的可能变化数，最后通过乘法原理得到总的变化数。难点在于如何高效地分解字符串并计算每个交叉字符串的变化数。

#### 最优关键思路或技巧
1. **字符串分解**：将字符串分解为多个独立的交叉字符串，每个交叉字符串的变化数互不影响。
2. **变化数计算**：对于长度为 $l$ 的交叉字符串，其变化数为 $\lceil \frac{l}{2} \rceil$。
3. **乘法原理**：将所有交叉字符串的变化数相乘，得到最终结果。

#### 可拓展之处
类似的问题可以通过分解字符串为独立部分，然后分别计算每部分的变化数，最后通过乘法原理得到总结果。这种思路适用于许多字符串操作问题。

#### 推荐题目
1. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)
2. [P1063 能量项链](https://www.luogu.com.cn/problem/P1063)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 精选题解

#### 题解1：作者：Ratio_Y (赞：15)
**星级**：★★★★★  
**关键亮点**：通过分解字符串为独立事件，并利用乘法原理计算总变化数，代码简洁高效。  
**个人心得**：通过打表找规律，发现交叉字符串的变化数为 $\lceil \frac{n}{2} \rceil$，这一发现大大简化了问题。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Ratio=0;
const int N=250005;
const int mod=1e9+7;
int len,n,tot,w[N];
char ch[N];
bool flag;
long long ans=1;
void Wsolve()
{
	if(n&1) n++;int res=n/2;//手动向上取整
	w[++tot]=res; 
}
int main()
{
	scanf("%d",&len);cin>>ch;n=1;
	if(ch[0]=='A') flag=1;
	else flag=0;
	for(int i=1;i<len;i++)
		if((flag&&ch[i]=='B')||(!flag&&ch[i]=='A')) flag^=1,n++;
		else Wsolve(),n=1;
	Wsolve();//最后可能有未截止的独立事件
	for(int i=1;i<=tot;i++)
		ans=ans*w[i]%mod;
	printf("%lld\n",ans);
	return Ratio; 
}
```

#### 题解2：作者：longhaoyuan (赞：2)
**星级**：★★★★  
**关键亮点**：通过分析交叉字符串的性质，发现其变化数为 $\frac{长度}{2}$，并通过乘法原理计算总变化数。  
**个人心得**：通过简单情况的分析，发现交叉字符串的变化规律，从而简化了问题。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double dbl;
const ll mod = 1e9+7;

ll n;
string s;
ll ans = 1LL;

int main(){
	scanf("%lld", &n); cin >> s;
	s = s + s.back(); n++;
	int last = 0;
	for (int i = 1; i < n; i++){
		if (s[i] == s[i-1]){
			int dis = i - last;
			ans *= (dis + 1) / 2;
			ans %= mod;
			last = i;
		}
	}
	printf("%lld", ans);
    return 0;
}
```

#### 题解3：作者：Binah_cyc (赞：2)
**星级**：★★★★  
**关键亮点**：通过递推公式 $f_l = f_{l-2}+1$ 计算交叉字符串的变化数，并通过乘法原理得到总变化数。  
**个人心得**：通过递推公式简化了变化数的计算，代码实现简洁。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//不开long long见祖宗
const int mod=1e9+7;
int n,ans=1;
char c[250005];
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	int sze=0;
	for(int i=1; i<=n; i++)
	{
		cin>>c[i];
		if(c[i]!=c[i-1]) sze++;//计算该模板串的长度
		else ans=(((sze/2)%mod+sze&1)%mod*ans)%mod,sze=1;//计算贡献
	}
	ans=(((sze/2)+sze&1)%mod*ans)%mod;//别忘了最后一个模板串的贡献
	cout<<ans;
	return 0;
}
```

---
处理用时：50.93秒