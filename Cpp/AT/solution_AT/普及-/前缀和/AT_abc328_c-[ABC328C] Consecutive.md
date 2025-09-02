# [ABC328C] Consecutive

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc328/tasks/abc328_c

英小文字のみからなる長さ $ N $ の文字列 $ S\ =\ S_1S_2\ldots\ S_N $ が与えられます。

また、$ S $ に関する $ Q $ 個の質問が与えられます。 $ i\ =\ 1,\ 2,\ \ldots,\ Q $ について、$ i $ 番目の質問は $ 2 $ つの整数 $ l_i,\ r_i $ で表される下記の質問です。

> $ S $ の $ l_i $ 文字目から $ r_i $ 文字目までからなる部分文字列 $ S_{l_i}S_{l_i+1}\ldots\ S_{r_i} $ において、 同じ英小文字が $ 2 $ つ隣りあう箇所は何個ありますか？ すなわち、$ l_i\ \leq\ p\ \leq\ r_i-1 $ かつ $ S_p\ =\ S_{p+1} $を満たす整数 $ p $ は何個ありますか？

$ Q $ 個の質問それぞれの答えを出力してください。

## 说明/提示

### 制約

- $ N,\ Q $ は整数
- $ 1\ \leq\ N,\ Q\ \leq\ 3\ \times\ 10^5 $
- $ S $ は英小文字のみからなる長さ $ N $ の文字列
- $ l_i,\ r_i $ は整数
- $ 1\ \leq\ l_i\ \leq\ r_i\ \leq\ N $
 
### Sample Explanation 1

$ 4 $ 個の質問それぞれに対する答えは下記の通りです。 - $ 1 $ 個目の質問に関して、$ S_3S_4\ldots\ S_9\ = $ `ssissip` で同じ英小文字が隣り合う箇所は、$ S_3S_4\ = $ `ss` と $ S_6S_7\ = $ `ss` の $ 2 $ 個です。 - $ 2 $ 個目の質問に関して、$ S_4S_5\ldots\ S_{10}\ = $ `sissipp` で同じ英小文字が隣り合う箇所は、$ S_6S_7\ = $ `ss` と $ S_9S_{10}\ = $ `pp` の $ 2 $ 個です。 - $ 3 $ 個目の質問に関して、$ S_4S_5S_6\ = $ `sis` で同じ英小文字が隣り合う箇所は $ 0 $ 個です。 - $ 4 $ 個目の質問に関して、$ S_7\ = $ `s` で同じ英小文字が隣り合う箇所は $ 0 $ 個です。

### Sample Explanation 2

$ S_1S_2\ldots\ S_5\ = $ `aaaaa` で同じ英小文字が隣り合う箇所は、 $ S_1S_2\ = $ `aa` 、$ S_2S_3\ = $ `aa` 、$ S_3S_4\ = $ `aa` 、$ S_4S_5\ = $ `aa` の $ 4 $ 個です。

## 样例 #1

### 输入

```
11 4
mississippi
3 9
4 10
4 6
7 7```

### 输出

```
2
2
0
0```

## 样例 #2

### 输入

```
5 1
aaaaa
1 5```

### 输出

```
4```

# 题解

## 作者：zhangboyong (赞：4)

## 题目大意

给定一个长度为 $N$ 的字符串，有 $Q$ 次询问，每次询问给定 $l$ 与 $r$，输出在 $l$ 到 $r$ 这段区间中相邻两字符相同的个数。

## 思路

由于 $1 \leq N,Q \leq 3 \times 10^5$，我们考虑 $O(N)$ 求解。

先使用前缀和预处理出对于每个 $i$，从 $1$ 到 $i$ 所有满足条件的个数，询问时利用前缀和直接输出即可

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int len,q;
int d[300005];
string s;
signed main(){
	cin >> len >> q;
	cin >> s;
	for(int i = 1;i<len;i++){
		if(s[i]==s[i-1]) d[i]++;
	} 
	for(int i = 1;i<len;i++) d[i] += d[i-1];//预处理
	while(q--){
		int l,r;
		cin >> l >> r;
		cout << d[r-1]-d[l-1] << endl;//由于字符串下标从0开始，所以要-1
	}
}
```

---

## 作者：ACtheQ (赞：4)

本题思路清奇，可以使用前缀和。

首先我们预处理出来，如果这个数与前一个数相同，则把这个数用一个数组标记为 $1$。

```c++
for(int i=1;i<n;i++)
{
	if(s[i]==s[i-1]) a[i]=1;
}
```

接下来算遍前缀和，表示为 $b_i$ 为 $1 \sim i$ 有多少个相邻连续的数。

```c++
for(int i=1;i<n;i++) b[i]=b[i-1]+a[i];
```

最后 $q$ 遍查询就行了。

```c++
	while(q--)
	{
		int l,r;
		cin>>l>>r; 
		l--;
		r--;
		cout<<b[r]-b[l]<<endl;
	}
 ```
 总体代码如下。
 
 ```c++
 #include <bits/stdc++.h>
using namespace std;
string s;
int a[300005],b[300005];
int main()
{
    int n,q;
	cin>>n>>q;
	cin>>s;
	
	for(int i=1;i<n;i++)
	{
		if(s[i]==s[i-1]) a[i]=1;
	}
	for(int i=1;i<n;i++) b[i]=b[i-1]+a[i];
	while(q--)
	{
		int l,r;
		cin>>l>>r; 
		l--;
		r--;
		cout<<b[r]-b[l]<<endl;
	}
	return 0;
}
```

---

## 作者：CEFqwq (赞：2)

这道题很套路吧。。。

既然是求区间内某个东西的和，自然而然就能想到前缀和。

前缀和数组 $f_i$ 存的就是前 $i$ 个字符构成的字符串中满足条件的子串的个数。

那么预处理一下。时间复杂度 $O(n+T)$。

注意 AT 不支持 `cin>>(s+1)` 的输入方式，所以用一个循环输入字符串。

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[300005];
int qz[300005],n,t;
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>t;
	for(int i=1;i<=n;i++)cin>>s[i];//cin>>(s+1) 会报错
	s[0]='\0';//一定要把 s[0] 赋值成一个一定不等于 s[1] 的值，保险起见设为 \0
	for(int i=1;i<=n;i++)qz[i]=qz[i-1]+(int)(s[i]==s[i-1]);//求前缀和
	while(t-->0){
		int l,r;
		cin>>l>>r;
		cout<<qz[r]-qz[l]<<"\n";//O(1)查询做减法即可
	}
}
```

---

## 作者：HEzzz (赞：2)

[题目跳转键](https://www.luogu.com.cn/problem/AT_abc328_c)

## 思路

类似于前缀和的思路。

定义一个数组 $p[i]$ 表示 前 $i$ 个字符组成的对数个数。

那么对于每一组的 $l$ 和 $r$ 有

- 如果 $s[l]$ 和 $s[l-1]$ 一样，那么 $l-1$ 和 $l$ 这一组不能算，所以对答案的贡献为 $l+1$ 到 $r$ 这段区间的对数。即为 $p[r]-p[l]$。

- 如果 $s[l]$ 和 $s[l-1]$ 不一样，那么对答案的贡献为 $l$ 到 $r$ 这段区间的对数。即为 $p[r]-p[l-1]$。

## code
```cpp
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _antirep(i,a,b) for(int i=(a);i>=(b);i--)
cin>>n>>q;
scanf("%s",(s+1));
_rep(i,2,n) 
{
	if(s[i]==s[i-1]) p[i]=p[i-1]+1;
	else p[i]=p[i-1]; 
}
while(q--)
{
	cin>>l>>r;
	if(s[l]==s[l-1]) cout<<p[r]-p[l];
	else cout<<p[r]-p[l-1];
	cout<<'\n'; 
}
```


---

## 作者：_ZML_ (赞：1)

[链接](https://www.luogu.com.cn/problem/AT_abc328_c)

这道题是一个很明显的前缀和，我们把 $sum_i$ 表示为前 $i$ 个字符有多少个有重复，查询的时候就用 $sum_{r-1}-sum_{l-1}$ 就行了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int sum[300010];
int main()
{
	int n,q;
	cin>>n>>q>>s;
	for(int i=1;i<n;i++)
		s[i]==s[i-1]?sum[i]=sum[i-1]+1:sum[i]=sum[i-1];
	while(q--){
		int l,r;
		cin>>l>>r;
		cout<<sum[r]-sum[l]<<endl;
	}
	return 0;
}
```



---

## 作者：time_keeper (赞：1)

# 题意

给定一个长度为 $N$ 的字符串 $S$，以及 $Q$ 个关于字符串 $S$ 的查询。每个查询由两个整数 $l_i,r_i$ 表示，表示要求解的子串的起始位置和结束位置。

查询的目标是找出子串中有多少个位置出现了相同的连续小写英文字母。

# 思路

前缀和

定义一个 `sc` 数组表示从 $1$ 到 $i$ 的相连小写字母数

即
```cpp
for (int i = 1; i < N; ++i) {
   if (S[i] == S[i - 1]) {
       sc[i] = sc[i - 1] + 1;
   } else {
       sc[i] = sc[i - 1];
   }
}
```
查询时直接 `count = sc[r - 1] - sc[l - 1];`

$O(1)$ 查询，在 $3×10^5$ 下绝对没大问题

# 代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;

    // 建立辅助数组，记录每个位置与前一个位置是否相同
    vector<int> sc(N, 0);
    for (int i = 1; i < N; ++i) {
        if (S[i] == S[i - 1]) {
            sc[i] = sc[i - 1] + 1;
        } else {
            sc[i] = sc[i - 1];
        }
    }

    // 处理查询
    for (int i = 0; i < Q; ++i) {
        int l, r;
        cin >> l >> r;

        // 直接利用辅助数组计算答案
        int count = sc[r - 1] - sc[l - 1];
        cout << count << endl;
    }

    return 0;
}
```

---

## 作者：jqQt0220 (赞：0)

## 题目大意

给出一个字符串 $S$ 和 $Q$ 组询问，每组询问给出 $l_i,r_i$，求在 $S$ 的子串 $S_{l_i}S_{l_i+1}\dots S_{r_i}$ 中有多少组相邻两个字母相同。

## 思路

直接算肯定会超时，所以可以做一个类似前缀和 ~~（似乎就是前缀和）~~ 的预处理。设 $t_i$ 为 $S$ 的子串 $S_1S_2\dots S_i$ 有多少组相邻两个字母相同，可得 递推式为 $t_i=t_{i-1}+[S_i=S_{i+1}],t_0=0$。其中 $[]$ 为[艾佛森括号](https://baike.baidu.com/item/%E8%89%BE%E4%BD%9B%E6%A3%AE%E6%8B%AC%E5%8F%B7/22361197)（此知识源于 @[kkvyaivw](/user/647775) 的题解），括号中内容就是代码中布尔变量，因为 `(bool)true` 等价于 `(int)1`，`(bool)false` 等价于 `(int)0`，所以代码可以直接写 `(s[i]==s[i+1])`，注意括号是必需的，因为优先级问题。

预处理之后就可以直接输出了，答案为 $t_{r-1}-t_{l-1}$。$r-1$ 是不能算最后一个，$l-1$ 是要算上第一个。

省略了头文件和奇奇怪怪的初始化的 AC Code：（话说 AT 的 RMJ 啥时候能修好）
```cpp
int n,q;
string s;
int t[300003];
int main()
{
    ___();//不用管这个
    cin>>n>>q;
    cin>>s;
    for(int i=0;i<s.length();i++)//预处理
        t[i+1]=t[i]+(s[i]==s[i+1]);//一定要加括号！一定要加括号！一定要加括号！重要的事情说三遍
    while(q--)
    {
        int l,r;
        cin>>l>>r;
        cout<<t[r-1]-t[l-1]<<endl;//直接输出询问
    }
    return 0;//完美结束 QwQ
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc328_c)

## 思路

前缀和。

看数据范围，$1\le N,Q\le 3\times 10^5$，每次 $Q$ 都搜一遍字符串 $S$ 肯定过不了，于是我们考虑用前缀和来处理。

读入数据后将 $S$ 前加一个空格，防止越界。定义 ``sum[]`` 为前缀和数组，之后我们进行前缀和处理：

- 如果这位和上一位不同，那 ``sum[i]=sum[j]``。

- 如果这这一位和上一位相同，那 ``sum[i]=sum[j]+1``。

每次读入 $l$ 和 $r$ 后，输出 ``sum[r]-sum[l]`` 的值即可。**注意不是** ``sum[r]-sum[l-1]``，因为重复的位置必须被 $(l,r)$ **完整**包括进去。

## AC 代码

```cpp
#include<bits/stdc++.h>//万能头省心。
#define ll long long
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define fi first
#define se second
using namespace std;
inline ll read(){//快读。
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
inline void print(ll x){//快写。
    if(x<0){
        putchar('-');
        x=-x;
    }
    ll y=10,len=1;
    while(y<=x){
        y=(y<<1)+(y<<3);
        len++;
    }
    while(len--){
        y/=10;
        putchar(x/y+48);
        x%=y;
    }
}
const int N=3e5+10;//数组开大点防止越界。
int n,q,l,r,sum[N];
string s;
int main(){
	cin>>n>>q>>s;
	int len=s.size();
	s=' '+s;
	for(int i=2;i<=len;++i){
		sum[i]=sum[i-1];
		if(s[i]==s[i-1])++sum[i];
	}
	while(q--){
		l=read(),r=read();
		print(sum[r]-sum[l]);
		putchar('\n');//别忘换行。
	}
	return 0;
}
```

---

## 作者：WilliamFranklin (赞：0)

### 主要思路

尽然看到这是一个求区间的问题，并且是第三题，就知道，大概率要用前缀和。

注：在此题解中，满足条件的位置，都叫作好位置。

首先我们计算出 $pre_i$，表示从 $1$ 到 $i$ 中，有几个位置是好位置。

然后，在查询的时候，因为此时我们发现我们不能选择 $r$，因为 $r + 1$ 不在 $l$ 到 $r$ 这段区间中，所以答案就应该是 $pre_{r - 1} - pre_{l - 1}$。

好了，看下代码吧。

### AC Code

```
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); TI--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
int n, q;
string s;
int a[300005];
int pre[300005];
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> q;
	cin >> s;
	for (int i = 0; i < n - 1; i++) {
		if (s[i] == s[i + 1]) {
			a[i] = 1;
		}
	}
	For(i, 0, n - 1) pre[i] = pre[i - 1] + a[i];
	while (q--) {
		int l, r;
		cin >> l >> r;
		cout << pre[r - 2] - pre[l - 2] << endl; 
	}
	return 0;
} 
```

---

## 作者：xu222ux (赞：0)

## [[ABC328C] Consecutive](https://www.luogu.com.cn/problem/AT_abc328_c)


## 思路

本题是一道前缀和的板子。

$sum_i$ 是 $s_i$ 以前的合法个数。

问题是 $s_l$ 到 $s_r$ 之间的合法个数。

所以我就用 $sum_r-sum_{l-1}$。

但是开头位置要特判一下。


## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
string s;
int sum[300005];
int main(){
	cin>>n>>q>>s;
	for(int i=1;i<s.size();i++){//制作前缀和
		if(s[i]==s[i-1])sum[i+1]=1;
		sum[i+1]+=sum[i];
	}
	while(q--){
		int l,r;cin>>l>>r;
		int ans=sum[r]-sum[l-1];
		if(l!=1&&s[l-2]==s[l-1])ans--;//特判
		cout<<ans<<endl;
	}
	return 0;
}

```


---

## 作者：Dream_poetry (赞：0)

### 题目大意：

给定一个字符串 $S$，从 $S_l$ 截取到 $S_r$，求其中 $S_i =S_{i+1}$ 的个数（$l \le i < r$）。

### 解题思路：
很显然，就这个数据范围而言，暴力必然会 TLE。

考虑用前缀和优化。

用 $sum_i$ 表示从 $0$ 到 $i$ 的个数。

直接输出 $sum_r-sum_l$ 即可。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,q;
string s;
int l,r;
int sum[500005];

signed main(){
	cin>>n>>q;
	cin>>s;
	for (int i=1;i<n;i++){
		sum[i]=max(sum[i],sum[i-1]);
		if (s[i]==s[i-1]){
			sum[i+1]=sum[i]+1;
		}
	}
	while (q--){
		cin>>l>>r;
		cout<<sum[r]-sum[l]<<endl;
	}
	
	return 0;
}
```


---

## 作者：zhangzehao1 (赞：0)

**题意简述**

给定一个字符串，有 $Q$ 次询问，每次询问 $l$ 到 $r$ 区间内连续字母的个数。

字符串下标从 `1` 开始。

**思路**

我们可以直接从 $l$ 循环到 $r$，统计答案。

但是 $Q \le 3 \times 10^5$，直接循环会超时。

我们可以考虑一个前缀和的做法。

先循环一遍字符串，统计连续子母的个数。

然后再询问 $Q$ 次，每次输出 $a_r-a_l$ 即可。

**代码**

```
#include<bits/stdc++.h>
using namespace std;
const int M=1e5+5;
int n,q;
char s[M*3];
int a[M*3];//前缀和数组 
int main()
{
    cin>>n>>q;
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
		a[i]=a[i-1]+(s[i]==s[i-1]);
	while(q--)
	{
		int l,r;
		cin>>l>>r;
		cout<<a[r]-a[l];//O(1)查询 
	}	
	return 0;
}
```

---

## 作者：qifan_maker (赞：0)

### 题目链接
[洛谷](https://www.luogu.com.cn/problem/AT_abc328_c)

[AtCoder](https://atcoder.jp/contests/abc328/tasks/abc328_c)

### 题意简述
给定一个长度为 $N$ 的字符串 $S$，有 $Q$ 次查询，对于每次查询，求 $S_{l},S_{l+1},\ldots ,S_{r}$ 中有多少个整数 $p$ 满足 $S_p = S_{p+1}$？

**数据范围：**
- $1 \leq N, Q \leq 3 \times 10^5$；

- $S$ 由小写英文字母组成。

### 题目解法
每次从 $S_l$ 遍历到 $S_r$ 最坏情况下时间复杂度为 $\mathcal{O}(NQ)$，无法通过此题。

我们考虑用前缀和优化，先将满足 $S_p = S_{p+1}$ 的位置存入数组 $A$ 并计算前缀和，每次查询，我们只需要输出 $A_r-A_l$ 即可，时间复杂度 $\mathcal{O}(N+Q)$。

### [AC](https://atcoder.jp/contests/abc328/submissions/47476508) Code
```cpp
/*
Problem：
C
By：
qifan_maker
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
int a[300100];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int n,q;
	cin >> n >> q;
	string s;
	cin >> s;
	s = ' '+s;
	for (int i=1;i<s.size();i++){
		if (s[i] == s[i+1]){
			a[i+1] = 1;
		}
	}
	for (int i=1;i<s.size();i++){
		a[i] += a[i-1];
	}
	while (q--){
		int l,r;
		cin >> l >> r;
		cout << a[r]-a[l] << endl;
	}
	return 0;
}

```

---

## 作者：Expert_Dream (赞：0)

给一个长度为 $n$ 的字符串 $s$，$q$ 次询问，每一次 $l$ 和 $r$ 区间内有多少个 $s_i$ 等于 $s_{i-1}$。

$10^5$ 的数据 $O(N^2)$ 暴力肯定行不通。于是我们考虑预处理前缀和，处理到 $i$ 下标以及之前有多少个 $s_i$ 等于 $s_{i-1}$。

每一次查询 $O(1)$ 回答。注意要减去的边界是 $qzh_l$，因为 $qzh_l$ 其实是包含着 $s_l$ 与 $s_{l-1}$ 的贡献。所以这个不能算入这个区间的贡献中。因此前缀和的公式应该是 $qzh_r - qzh_l$。

[link](https://atcoder.jp/contests/abc328/submissions/47471737)。

---

## 作者：liuhl_weifang (赞：0)

这是一个练习前缀和的好题。

题面给了我们提示，提示我们的目标就是找到有多少个 $p$ 满足 $l \leq p \leq r-1$ 且 $s_{p}=s_{p+1}$。因此直接前缀和维护即可，时间复杂度 $\Theta(n+q)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,q;
char s[300010];
int p[300010];

signed main()
{
	cin >> n >> q;
	for (int i=1;i<=n;i++) cin >> s[i];
	for (int i=1;i<=n;i++)
	{
		if(s[i]==s[i+1]) p[i] = p[i-1]+1;
		else p[i] = p[i-1];
	}
	for (int i=1;i<=q;i++)
	{
		int l,r;
		cin >> l >> r;
		cout << p[r-1]-p[l-1] << "\n"; 
	}
	return 0;
}
```

---

## 作者：uid_647775 (赞：0)

前缀和优化。  
定义 $f_i$ 为 $S_{1,2\dots i}$ 的答案，那么可以得出递推关系：
$$f_1\gets 0,f_i\gets f_{i-1}+[S_i=S_{i-1}]$$
其中，$[]$ 为[艾佛森括号](https://baike.baidu.com/item/%E8%89%BE%E4%BD%9B%E6%A3%AE%E6%8B%AC%E5%8F%B7/22361197)，也就是当 $S_i=S_{i-1}$ 成立时，$[S_i=S_{i-1}]$ 值为 $1$ ，否则为 $0$。  
可以发现，对于一个询问 $(l,r)$，答案为 $f_r-f_l$。  
所以只需要先预处理出 $f_{1,2\dots n}$，对于每一个询问输出对应的答案即可。  
[Code](https://atcoder.jp/contests/abc328/submissions/47470538)

---

## 作者：yhx0322 (赞：0)

## Description
给你一个字符串 $S$，有 $Q$ 次询问，每次输入 $l, r$，求：$[S_l,S_r]$ 区间中有多少个相邻的字符是相等的。
## Solution
循环一遍字符串，看看 $s_i$ 是否等于 $s_{i+1}$，如果等于，记录前缀和数组 $pre$，$pre_i = pre_{i-1} + 1$，否则 $pre_i = pre_{i-1}$。

每次询问的时候只需要输出 $pre_{r - 1} - pre_{l - 1}$ 即可。
## Code
```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 3e5 + 10;

int n, t, l, r, len, c[N];
char s[N];

inline void solve() {
	scanf("%d%d", &l, &r);
	printf("%d\n", c[r - 1] - c[l - 1]);
}

signed main() {
	scanf("%d%d%s", &n, &t, s + 1);
	for (int i = 1; i <= n; i++) c[i] = c[i - 1] + (s[i] == s[i + 1]);
	while (t--) solve();
	return 0;
}
```

---

