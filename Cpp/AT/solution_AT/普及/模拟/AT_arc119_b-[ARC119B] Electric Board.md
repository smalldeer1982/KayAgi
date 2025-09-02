# [ARC119B] Electric Board

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc119/tasks/arc119_b

いま、電光掲示板に `0` と `1` から成る長さ $ N $ の文字列 $ S $ が表示されています。

あなたは次の操作を何回でも行うことができます。なお、ここでは電光掲示板に表示されている文字列の $ i $ $ (1\ \leq\ i\ \leq\ N) $ 文字目を $ S_i $ と表します。

> **操作** 整数 $ (l,\ r) $ $ (1\ \leq\ l\ <\ r\ \leq\ N) $ であって、次の条件のうちいずれかを満たすものを $ 1 $ 組選び、$ S_l $ と $ S_r $ を入れ替える。
> 
> - $ S_l= $ `0` かつ $ S_{l+1}=\cdots=S_r= $ `1` を満たす。
> - $ S_{l}=\cdots=S_{r-1}= $ `1` かつ $ S_r= $ `0` を満たす。

電光掲示板に表示されている文字列を $ T $ に一致させることができるか判定し、可能な場合は操作回数として考えられる最小の値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 500000 $
- $ S $ は `0` と `1` からなる長さ $ N $ の文字列である
- $ T $ は `0` と `1` からなる長さ $ N $ の文字列である

### Sample Explanation 1

例えば以下のように操作を行えば、$ 2 $ 回の操作で電光掲示板に表示されている文字列を `1010111` にすることができます。 - $ (l,\ r)\ =\ (2,\ 4) $ を選んで操作を行う。そのとき、電光掲示板の文字列は `1110110` から `1011110` に変化する。 - $ (l,\ r)\ =\ (4,\ 7) $ を選んで操作を行う。そのとき、電光掲示板の文字列は `1011110` から `1010111` に変化する。

### Sample Explanation 2

操作を行う前の時点で、電光掲示板に表示されている文字列が $ T $ であるため、答えは $ 0 $ となります。

### Sample Explanation 3

どのように操作を行っても、電光掲示板に文字列 $ T $ を表示させることが不可能な場合は、`-1` と出力してください。

## 样例 #1

### 输入

```
7
1110110
1010111```

### 输出

```
2```

## 样例 #2

### 输入

```
20
11111000000000011111
11111000000000011111```

### 输出

```
0```

## 样例 #3

### 输入

```
6
111100
111000```

### 输出

```
-1```

## 样例 #4

### 输入

```
119
10101111011101001011111000111111101011110011010111111111111111010111111111111110111111110111110111101111111111110111011
11111111111111111111111111011111101011111011110111110010100101001110111011110111111111110010011111101111111101110111011```

### 输出

```
22```

# 题解

## 作者：fengenrong (赞：3)

当我们看完题目，我们不难发现不管怎么样 $0$ 和 $1$ 的个数是不可能变化的。所以我们可以用两个变量 $o$ 和 $p$ 分别统计字符串 $a$ 和 $b$ 中 $0$ 的个数，只要它们个数是不相等的，它就是无解的，直接输出 `-1` 。否则，就是有解的，我们可以用一个 $sum$ 变量来统计答案，只要字符串 $a$ 和 $b$ 中的 $0$ 的位置不同，就 $sum \gets sum + 1$，最后输出 $sum$ 就行了。

```
#include<bits/stdc++.h>
using namespace std;
string a,b;
long long n;
long long o,p;//分别统计字符串a和b中0的数量
long long q[1000000],w[1000000];//分别记录字符串a和b中0的位置
int main() 
{
    cin>>n>>a>>b;
    for(long long i=0;i<=n-1;i++)
    {
    	if(a[i]=='0')
    	{
    		o++;//统计
    		q[o]=i;//记录位置
		}
		if(b[i]=='0')
		{
			p++;//统计
			w[p]=i;//记录位置
		}
	}
	if(o==p)//有解
	{
		long long sum=0;//统计答案
		for(long long i=0;i<=n-1;i++)
		{
			if(q[i]!=w[i])
			{
				sum++;//增加
			}
		}
		cout<<sum<<endl;
	}
	else//无解
	{
		cout<<"-1"<<endl;
	}
    return 0;
}
```

---

## 作者：ht__QAQ__ (赞：2)

## 题意：

- ~~[机翻](https://www.luogu.com.cn/paste/b2cs0ts9)。~~

- 一个长度为 $N$ 的字符串 $S$ 与 $T$，由 `0` 和 `1` 组成。现在，你可以将地 $S$ 字符串中 $S_l$ 与 $S_r$ 交换顺序。输出最小交换次数，如果不能交换，输出 `-1`。

---

## 思路：

### 方法1：

我们可以统计 $S_l$ 与 $S_r$ 之中 `0` 和 `1` 分别出现了多少次，如果不相等，则输出 `-1`；相等判断就哪些不一样，统计，输出即可。

```cpp
#include<bits/stdc++.h>
#define for(i,k) for(int i=0;i<k;i++) 
using namespace std;
string a,b;int n,q,w,ans;
signed main(){
	cin>>n>>a>>b;
	for(i,n){
		if(a[i]=='0') q++;
		if(b[i]=='0') w++;
	}
	if(q!=w){
		puts("-1");
		return 0;
	}
	for(i,n){
		if(a[i]!=b[i]) ans++;
	}
	printf("%d",ans);
	return 0;
}
```
~~这样就 WA 了。~~

分析为什么会 WA。

```样例
3
110
101
```
按常理来说，只需要把 `1` 与 `0` 交换，$1$ 次即可，可是，他会算两遍，所以得用桶。


---

### 方法2：

我们可以用桶来做，如果 $S_i$ 等于 `0` 或者 $T_i$ 等于 `0` 时，用桶装 $i$，如果装的坐标数量不同，输出 `-1`；如果坐标不同，答案加 $1$。

```cpp
#include<bits/stdc++.h>
#define for(i,k) for(int i=0;i<k;i++) 
using namespace std;
string a,b;int n,ans,y,x,sum[4005],sun[4005];
signed main(){
	cin>>n>>a>>b;
	for(i,n){
		if(a[i]=='0') sum[x++]=i;
		if(b[i]=='0') sun[y++]=i;
	}
	if(x!=y){
		puts("-1");
		return 0;
	}
	for(i,n){
		if(sum[i]!=sun[i]){
			ans++;
		}
	}
	cout<<ans;
	return 0;
}

```

**你觉得为什么内存限制设置成 1.00GB 吗（暗示）。**


---

## 作者：Fkxxx (赞：1)

### 题意

给出两个 01 串，你可以将第一个串中的 0 移动到左侧或右侧的一段**连续**的 1，求使两个串相等的最小步数。

### 算法
![](https://cdn.luogu.com.cn/upload/image_hosting/ij5n811f.png)

$$\text{例}1$$

上面的图是一个很好的例子。通过观察，我们不难发现，根据题意，第一个串中的 “0” 的顺序是不变的，并且只要 “0” 的顺序不变，对第一个串中 “0” 和 “1” 交换一定是可行的。
“0” 和 “1” 的数量相等，就一定有解。

根据以上结论，我们还发现 $a_i = b_i$（$a_i$ 为第一个串第 $i$ 个 “0” 的下标，$b_i$ 为第二个串第 $i$ 个 “0” 的下标）时根本不需要交换 “0” 的位置！

解法就是先判断是否有解，再把两个串的各个 “0” 的出现位置记下来，判断可以跳过几次交换，最后输出答案。

### 答案

[AC Link](https://atcoder.jp/contests/arc119/submissions/45504105)

---

## 作者：cff_0102 (赞：1)

$0$ 只能和一段 $1$ 交换，所以 $0$ 的相对位置不会改变。

所以按顺序比对每个 $0$ 出现的位置，如果不一样，移动次数就 $+1$。

当然，如果 $0$ 的个数不一样，想要变成相同序列就别想了。

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[514114],b[514114];
int zeroa[514114],zerob[514114];
int main(){
	ios::sync_with_stdio(false);
	int n;cin>>n>>a>>b;
	int sa=0,sb=0;//a 和 b 中 0 的个数
	for(int i=0;i<n;i++){
		if(a[i]=='0'){
			zeroa[sa++]=i;//记录在 a 数组中第 sa 个 0 出现在第 i 位 
		} 
	}
	for(int i=0;i<n;i++){
		if(b[i]=='0'){
			zerob[sb++]=i;//记录在 b 数组中第 sb 个 0 出现在第 i 位 
		} 
	}
	if(sa!=sb){
		cout<<-1;
		return 0;
	}
	int s=0;//记录两个 0 位置不同的次数 
	for(int i=0;i<sa;i++){
		if(zeroa[i]!=zerob[i])s++;
	}
	cout<<s; 
	return 0;
}
```

---

## 作者：Teto_etf (赞：0)

### 思路分析

容易发现操作不改变 $0$ 和 $1$ 的个数，所以如果两个串中 $0$ 的个数不相等，那么不可能完成任务。

其次我们发现每次操作**只能改变一个 $\textbf{0}$ 的位置**，所以当两个串中有 $0$ 的位置不同的地方就需要进行操作，最终的答案就是 $0$ 的位置不同的地方的个数。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
string s, t;
const int maxn = 5e5 + 10;
int s_cnt[maxn], t_cnt[maxn];

int main() {
    cin >> n >> s >> t;
    int s0 = 0, t0 = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') s0++, s_cnt[s0] = i;
        if (t[i] == '0') t0++, t_cnt[t0] = i;
    }
    if (s0 != t0) { // 无解
        cout << "-1" << endl;
        return 0;
    }
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (s_cnt[i] != t_cnt[i]) cnt++; // 0 的位置不同
    cout << cnt << endl;
    return 0;
}
```

---

## 作者：wzt2012 (赞：0)

### 题目大意

洛谷：[题目戳这里](https://www.luogu.com.cn/problem/AT_arc119_b)

AtCoder:：[题目戳这里](https://atcoder.jp/contests/arc119/tasks/arc119_b)

给定长度为 $N$ 两个字符串 $S,T$，要求通过最少的操作数把 $S$ 变成 $T$。

> 对于每次操作：

> 当 $S_l$ 和 $S_r$ 满足：

> - $S_l = 0$ 并且 $S_{l + 1} = S_{l + 2} = \dots = S_r = 1$

 > 或者
 
> - $S_l = 1$ 并且 $S_{l + 1} = S_{l + 2} = \dots = S_r = 0$

> 那么我们可以交换 $S_l$ 和 $S_r$。

---

### 解题方法

我们可以把所有 $0$ 换到应该的位置上，那么 $1$ 也就确定了。

$0$ 换过去的代价是**路上 $0$ 的数量**，**和 $1$ 就没关系了**，那么直接把 $S,T$ 的 $0$ 都取出来，相邻的配对即可。

---

### 代码及评测结果

[$\large\colorbox{#52C410}{\color{white}\texttt{ AC code \&\& commit record }}$](https://atcoder.jp/contests/arc119/submissions/46473916)


---

## 作者：Fu_Da_Ying (赞：0)

## [原题链接](https://www.luogu.com.cn/problem/AT_arc119_b)
## 题意：
给定两个长度为 $N$ 的 $0/1$ 串 $S$ 和 $T$，每次对第一个串：选一个 $0$ 移动到相邻的一段 $1$ 之前或之后或中间，求最少经过多少次能使两个串相同。无法使两个串相同则输出 $-1$。
## 思路：
用桶来储存 $S$ 串和 $T$ 串中的 $0$ 的个数，然后来判断$S$ 串和 $T$ 串的 $0$ 的是否坐标不同，如果不同答案加 $1$。
## Code:
```cpp
//非洛谷题_AtCoder_AT_arc119_b_[ARC119B] Electric Board
#include<bits/stdc++.h>
#pragma GCC/*G++*/ optimize(2)//O2
#pragma GCC/*G++*/ optimize(3)//O3
using namespace std;
long long n=0,sum,s0=0,t0=0,sums[500001]={},sumt[500001]={};//s0,t0分别对应s串中的0的个数，t串中的0的个数，sums为s串中的0的个数的桶，sumt为t串中的0的个数的桶
string s,t;
int main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);//cin加速 
    cin>>n>>s>>t;
    for(int i=0;i<n;i++){
    	if(s[i]=='0'){//s串中这个值是否为0，s串的0的个数加1，并用sums存储 
    		sums[++s0]=i;
		}
		if(t[i]=='0'){//t串中这个值是否为0，t串的0的个数加1，并用sumt存储 
    		sumt[++t0]=i;
	    }
	}
	if(t0!=s0){//s串和t串中的0的个数不相等，则无法使两个串相同，输出-1
		cout<<"-1";
		return 0;
	}
	for(int i=1;i<=max(s0,t0);i++){
    	if(sums[i]!=sumt[i]){//如果s串和t串的0的坐标不同，答案加1
    		sum++;
		}
	}
	cout<<sum;
    return 0;
}

---

## 作者：ivyjiao (赞：0)

首先，不难发现，一次操作只能交换一个 $0$ 以及它后面的一个 $1$，$0$ 的个数与 $1$ 的个数是不会变的，所以当且仅当 $S$ 中 $0$ 的个数与 $T$ 中 $0$ 的个数不相等时无解。

我们可以把两个字符串中所有 $0$ 的位置记录下来，因为一次操作只能交换一个 $0$，所以统计 $0$ 位置不同的地方就是答案。

```cpp
#include<iostream>
using namespace std;
int n,a0,b0,ans,a1[500001],b1[500001];
string a,b;
int main(){
    cin>>n>>a>>b;
    for(int i=0;i<n;i++) if(a[i]=='0') a1[++a0]=i;
    for(int i=0;i<n;i++) if(b[i]=='0') b1[++b0]=i;
    if(a0!=b0) return !puts("-1");
    for(int i=0;i<n;i++) if(a1[i]!=b1[i]) ans++;
    cout<<ans;
}
```


---

## 作者：zajasi (赞：0)

## 题意
给你两个字符串 $s$ 和 $t$，问能不能操作 $s$，将两个字符串变为相等。能则输出交换次数，不能则输出 `-1`。

操作：如果有 $l$ 和 $r$，满足 $s_l=0$ 且 $s_{l+1}=s_{l+2}=\cdots=a_r=1$ 或者 $s_r=0$ 且 $s_l=s_{l+1}=\cdots=a_{r-1}=1$，则可以交换。
## 解题思路
可以发现，不管怎么操作，$0$ 和 $1$ 的总个数都是不变的。所以无解的情况就只有上下 $0$ 或 $1$ 不相等。由于长度相同，所以只要统计 $1$ 的个数就可以了。

判完无解后，可以将所有 $0$ 的位置都找出来，然后进行一一对比。由于一次交换只能交换一个 $0$，所以统计一下位置不同的地方就是答案啦。

还不懂？上代码看看。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
string a,b;
int z1,z2;//统计上下 0 的个数
int z3;//统计 0 位置不同的总个数，即为答案
vector<int> x,y;//统计 0 的位置
main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>a>>b;
	for(int i=0;i<n;i++){
		if(a[i]=='0')z1++,x.push_back(i);
		if(b[i]=='0')z2++,y.push_back(i);
	}
	if(z1!=z2)cout<<"-1";//上下 0 个数不同即无解
	else{
		for(int i=0;i<x.size();i++){
			if(x[i]!=y[i])z3++;
		}
		cout<<z3;
	}
	return 0;
}
```

---

