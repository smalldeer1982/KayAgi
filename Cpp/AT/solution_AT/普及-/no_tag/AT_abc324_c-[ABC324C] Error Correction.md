# [ABC324C] Error Correction

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc324/tasks/abc324_c

高橋君は英小文字からなる文字列 $ T $ を青木君に向けて送りました。その結果、青木君は英小文字からなる文字列 $ T' $ を受信しました。

$ T' $ は $ T $ から一部が変更されてしまっている可能性があり、具体的には、下記の $ 4 $ つのうちのちょうど $ 1 $ つが成り立つことがわかっています。

- $ T' $ は、$ T $ と等しい。
- $ T' $ は、$ T $ のいずれか $ 1 $ つの位置（先頭と末尾も含む）に英小文字を $ 1 $ つ挿入して得られる文字列である。
- $ T' $ は、$ T $ からある $ 1 $ 文字を削除して得られる文字列である。
- $ T' $ は、$ T $ のある $ 1 $ 文字を別の英小文字に変更して得られる文字列である。
 
青木君が受信した文字列 $ T' $ と、英小文字からなる $ N $ 個の文字列 $ S_1,\ S_2,\ \ldots,\ S_N $ が入力として与えられるので、 $ S_1,\ S_2,\ \ldots,\ S_N $ のうち、高橋君が送った文字列 $ T $ と等しい可能性があるものをすべて求めてください。

## 说明/提示

### 制約

- $ N $ は整数
- $ 1\ \leq\ N\ \leq\ 5\ \times\ 10^5 $
- $ S_i $ と $ T' $ は英小文字からなる長さ $ 1 $ 以上 $ 5\ \times\ 10^5 $ 以下の文字列
- $ S_1,\ S_2,\ \ldots,\ S_N $ の長さの総和は $ 5\ \times\ 10^5 $ 以下
 
### Sample Explanation 1

$ S_1,\ S_2,\ \ldots,\ S_5 $ のうち、$ T $ と等しい可能性があるものは $ S_1,\ S_2,\ S_3,\ S_4 $ の $ 4 $ つであることが下記の通りわかります。 - $ S_1 $ は $ T $ と等しい可能性があります。なぜなら、$ T'\ = $ `ababc` は $ S_1\ = $ `ababc` と等しいからです。 - $ S_2 $ は $ T $ と等しい可能性があります。なぜなら、$ T'\ = $ `ababc` は $ S_2\ = $ `babc` の先頭に文字 `a` を挿入して得られる文字列だからです。 - $ S_3 $ は $ T $ と等しい可能性があります。なぜなら、$ T'\ = $ `ababc` は $ S_3\ = $ `abacbc` から $ 4 $ 文字目の `c` を削除して得られる文字列だからです。 - $ S_4 $ は $ T $ と等しい可能性があります。なぜなら、$ T'\ = $ `ababc` は $ S_4\ = $ `abdbc` の $ 3 $ 文字目の `d` を `b` に変更して得られる文字列だからです。 - $ S_5 $ は $ T $ と等しい可能性はありません。なぜなら、$ S_5\ = $ `abbac` を $ T $ としたとき、$ T'\ = $ `ababc` は問題文中の $ 4 $ つの条件をいずれも満たさないからです。

## 样例 #1

### 输入

```
5 ababc
ababc
babc
abacbc
abdbc
abbac```

### 输出

```
4
1 2 3 4```

## 样例 #2

### 输入

```
1 aoki
takahashi```

### 输出

```
0```

## 样例 #3

### 输入

```
9 atcoder
atoder
atcode
athqcoder
atcoder
tacoder
jttcoder
atoder
atceoder
atcoer```

### 输出

```
6
1 2 4 7 8 9```

# 题解

## 作者：yszkddzyh (赞：3)

### 题目大意

给出一个字符串 $T$ 和 $n$ 个字符串 $S_1,S_2,\cdots,S_n$（字符串只包含小写字母），问 $S_1,S_2,\cdots,S_n$ 中有多少个字符串**恰好**满足以下条件中的一个：

- 与 $T$ 相同。
- 是 $T$ 在任意位置添上一个小写字母所得的串。
- 是 $T$ 删去任意一个字符所得的串。
- 是把 $T$ 的任意一个位置修改成另一个小写字母所得的串。

输出所有恰好满足上述条件中的一个的字符串的编号。

### 题目分析

字符串基础题。

输入每个字符串，依次判断即可，主要考验新手的码力。

直接讲不直观，所以看代码吧，注释很详细。

### 代码

```cpp
/* STO %%% 「syksykCCC」 %%% Orz */

#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;
int n, tot, cnt, ans[N];
//cnt是满足条件的字符串的个数
//tot的作用后面再说 
//ans数组记录满足条件的字符串的编号 
string s, t;
//因为s是读入时立即处理，所以无需开数组 

bool check1(){//是否满足条件1 
	return s == t;
}
bool check2(){//是否满足条件2 
	int ls = s.size(), lt = t.size();
	if(ls != lt + 1) return 0;
	//以上是特判，如果长度不符合就直接返回 
	//因为如果是插入一个字符，那么新串的长度一定会加1 
	string res = "";
	//res是临时变量 
	int p = ls - 1;
	for(int i = 0; i < lt; i++){
		if(s[i] != t[i]){
			p = i;
			break;
		}
	}
	//用p记录第一个s与t不相等的位置 
	//其实如果s与t满足条件2，那么这个不相等的字符一定就是添加的 
	//所以我们将这个字符从s中删掉，所得字符串应该是与t相同的 
	//好好理解一下 
	//再想一想为什么p初始化成ls-1 
	for(int i = 0; i < ls; i++){
		if(i != p) res += s[i];
	}
	//用res记录s去掉第一个与t不相等的字符后所得串 
	return t == res;
}
bool check3(){//是否满足条件3 
	int ls = s.size(), lt = t.size();
	if(ls != lt - 1) return 0;
	//特判，同check2函数 
	string res = "";
	//同check2 
	int p = lt - 1;
	for(int i = 0; i < ls; i++){
		if(s[i] != t[i]){
			p = i;
			break;
		}
	}
	//p的含义同check2 
	for(int i = 0; i < lt; i++){
		if(i != p) res += t[i];
	}
	//如果s是将t删去一个字符所得的串，那么将t中第一个与s不等的字符去掉，所得串应该与s相同 
	//其实与check2类似 
	return s == res;
}
bool check4(){//是否满足条件4 
	int ls = s.size(), lt = t.size();
	if(ls != lt) return 0;
	//特判，长度不相等直接返回 
	int f = 0;
	//f记录s与t不相等的字符的个数 
	for(int i = 0; i < ls; i++){
		if(s[i] != t[i]){
			if(f) return 0;
			//如果已经有一个字符不相等了，不符条件 
			else f = 1;
			//否则将f设为1 
		}
	}
	return f;
	//不能写成return 1，是因为如果s等于t，那么不符合条件4，但check4仍会返回1 
}
bool check(){
	int f1 = check1();
	int f2 = check2();
	int f3 = check3();
	int f4 = check4();
	return f1 + f2 + f3 + f4 == 1;//判断是否恰好满足一个 
}

int main(){
	
	cin >> n >> t;
	for(int i = 1; i <= n; i++){
		cin >> s;
		if(check()){
			ans[++tot] = i;
			//其实tot就是用来记录ans现在有多少个元素了 
			cnt++;
		}
	}
	cout << cnt << endl;
	for(int i = 1; i <= tot; i++)
		cout << ans[i] << ' ';
	
	return 0;
}

/* MADE IN CHINA */
```

---

## 作者：WhisperingWillow (赞：1)

这道题很水，但赛时炸了。

判断的四个条件分别维护：

1. 直接判断即可
2. 考虑对于一个 $s_i\ne t_i$，删掉 $s_i$，答案就是 $[s==t]$
3. 和上个情况相同。
4. 对于每个 $|s|=|t|$ 的字符串，判断 $[\sum_{i=1}^n[ s_i\ne t_i]==1]$

满足任意一个我们就输出。

值得注意的是，将 $t$ 复制 $n$ 次会时间超限。

我们选择将其放在全局变量。


[提交记录](https://atcoder.jp/contests/abc324/submissions/46586466)

---

## 作者：robertuu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc324_c)

差点被降智，难度居然是棕！

思路非常奇怪，和官方题解出入很大。官方题解是用公共前缀和后缀处理的，我的思路是动态规划。

由于 $\sum|S_i| \le 5 \times 10^5$，因此可以对每个 $S_i$ 分别进行动态规划，定义 $dp_{i,j}$ 表示处理到 $S$ 的第 $i$ 个字符，且操作类型为 $j$ 时的最少不匹配字符。

- $j = 0$ 表示不进行任何操作。
- $j = 1$ 表示 $S$ 已经比 $T$ 多了一个字符。
- $j = 2$ 表示 $S$ 已经比 $T$ 少了一个字符。

转移方程也分为三种情况：

- $dp_{i,0} = dp_{i-1,0} + \operatorname{cmp}(i,i)$
- $dp_{i,1} = \min(dp_{i-1,1},dp_{i-2,0}) + \operatorname{cmp}(i,i-1)$ （$i-1 \le |T|$）
- $dp_{i,2} = \min(dp_{i-1,0},dp_{i-1,2}) + \operatorname{cmp}(i,i+1)$ （$i+1 \le |T|$）

最后一个字符添加或者删除是一种特殊情况，需要特判：

- $dp_{m-1,2} = \min(dp_{m-1,2},dp_{m-1,0})$
- $dp_{m-1,1} = \min(dp_{m-1,1},dp_{m-2,0})$

答案也分为三种情况：

- $|T| = |S|$ 时：若 $dp_{|S|,0} \le 1$ 说明可行
- $|T| = |S| - 1$ 时：若 $dp_{|S|,1} = 0$ 说明可行
- $|T| = |S| + 1$ 时：若 $dp_{|S|,2} = 0$ 说明可行

如果判断为可行就加入答案数组，最后输出答案数组元素个数和数组值即可。

AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[500001],sz,dp[500001][3];
int main()
{
	int n,m,T;
	string s,t;
	cin >> n >> t;
	T = t.length();
	for(int i = 1;i <= n;i++)
	{
		cin >> s;
		m = s.length();
		for(int j = 0;j < m;j++) dp[j][0] = dp[j][1] = dp[j][2] = 1e9; // 初始化，注意 memset 会超时！
		dp[0][0] = (s[0] != t[0]);
		dp[0][1] = 0;
		dp[0][2] = (s[0] != t[1]);
		for(int j = 1;j < m;j++) // 状态转移，注意转移条件，防止越界！
		{
			if(j < T) dp[j][0] = dp[j-1][0] + (s[j] != t[j]);
			if(j-1 < T) dp[j][1] = min(dp[j-1][1],dp[j-2][0]) + (s[j] != t[j-1]);
			if(j+1 < T) dp[j][2] = min(dp[j-1][0],dp[j-1][2]) + (s[j] != t[j+1]);
		}
		dp[m-1][2] = min(dp[m-1][2],dp[m-1][0]); // 特判
		dp[m-1][1] = min(dp[m-1][1],dp[m-2][0]); // 特判
		if(m == T && dp[m-1][0] <= 1 || m == T+1 && dp[m-1][1] == 0 || m == T-1 && dp[m-1][2] == 0) ans[++sz] = i; // 判断答案
	}
	printf("%d\n",sz);
	for(int i = 1;i <= sz;i++)
		printf("%d ",ans[i]);
	return 0;
}
```


---

