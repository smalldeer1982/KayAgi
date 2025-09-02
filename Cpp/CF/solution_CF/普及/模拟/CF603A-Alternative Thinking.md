# Alternative Thinking

## 题目描述

Kevin has just recevied his disappointing results on the USA Identification of Cows Olympiad (USAICO) in the form of a binary string of length $ n $ . Each character of Kevin's string represents Kevin's score on one of the $ n $ questions of the olympiad—'1' for a correctly identified cow and '0' otherwise.

However, all is not lost. Kevin is a big proponent of alternative thinking and believes that his score, instead of being the sum of his points, should be the length of the longest alternating subsequence of his string. Here, we define an alternating subsequence of a string as a not-necessarily contiguous subsequence where no two consecutive elements are equal. For example, $ {0,1,0,1} $ , $ {1,0,1} $ , and $ {1,0,1,0} $ are alternating sequences, while $ {1,0,0} $ and $ {0,1,0,1,1} $ are not.

Kevin, being the sneaky little puffball that he is, is willing to hack into the USAICO databases to improve his score. In order to be subtle, he decides that he will flip exactly one substring—that is, take a contiguous non-empty substring of his score and change all '0's in that substring to '1's and vice versa. After such an operation, Kevin wants to know the length of the longest possible alternating subsequence that his string could have.

## 说明/提示

In the first sample, Kevin can flip the bolded substring '10000011' and turn his string into '10011011', which has an alternating subsequence of length 5: '10011011'.

In the second sample, Kevin can flip the entire string and still have the same score.

## 样例 #1

### 输入

```
8
10000011
```

### 输出

```
5
```

## 样例 #2

### 输入

```
2
01
```

### 输出

```
2
```

# 题解

## 作者：zplqwq (赞：24)

考虑 `dp` .

我们令 $f_{i,0}$ 表示当前第 $i$ 个数字没有翻转，且前面无子串翻转的最大值。同理，$f_{i,1}$ 表示当前第 $i$ 个数字没有翻转，且前面有子串翻转的最大值。最后，$f_{i,2}$ 表示前 $i$ 个数字反转的最大值。答案即使三者取最大值。

一个小插曲，为什么想到这样设状态呢？

首先当然是因为题目就是这么问的。其次，我们分三个数组递推显然会很麻烦，不如用不同的 `j` 值来代表这三种情况。


既然如此，不难推出转移方程：

若 $a_i = a_{i-1}$ 则：

$$\left\{\begin{array}{l}f_{i,0}=f_{i-1,0}\\
f_{i,1}=\max( f_{i-1,2}+1,f_{i-1,1})\\
f_{i,2}=\max( f_{i-1,2},f_{i-1,0}+1)
\end{array}\right.
$$

否则，则：

$$\left\{\begin{array}{l}f_{i,0}=f_{i-1,0}+1\\
f_{i,1}=\max( f_{i-1,1}+1,f_{i-1,2})\\
f_{i,2}=\max( f_{i-1,2}+1,f_{i-1,0})
\end{array}\right.
$$


最后初值：

$$\left\{\begin{array}{l}f_{1,0}=1\\
f_{1,1}=1\\
f_{1,2}=1
\end{array}\right.
$$

完结撒花。


---

## 作者：查无此人 (赞：13)

机房巨佬都说这是一道规律题，可蒟蒻我推不出规律，只好打个dp

3个状态：

①$f[i][0]$表示当前第$i$个数字没有翻转，且前面无子串翻转的最大值

②$f[i][1]$表示当前第$i$个数字没有翻转，前面某一段翻转所得的最大值

③$f[i][2]$表示当前第$i$个数字翻转所得的最大值

很容易看出$f[i][0]$只能由$f[i-1][0]$转移过来

$f[i][1]$由$f[i-1][1]$(很之前一段翻转)与$f[i-1][2]$(前面一段翻转)转移来

$f[i][2]$由$f[i-1][2]$(连续一段翻转)与$f[i-1][0]$(前面没翻转)转移而来

详细状态转移方程见代码

```cpp
#include<cstdio>
#define max(x,y) ((x) > (y) ? (x) : (y))
int a[1000005],n,ans,f[1000005][3];

int main()
{
	register int i;
	scanf("%d",&n);
	for(i = 1;i <= n;++ i)
		scanf("%1d",&a[i]);
	f[1][0] = f[1][1] = f[1][2] = ans = 1;
	for(i = 2;i <= n;++ i)
	{
		bool flag = (a[i] == a[i - 1]);
		f[i][0] = (flag ? f[i - 1][0] : f[i - 1][0] + 1);
		f[i][1] = (flag ? max(f[i - 1][2] + 1,f[i - 1][1]) : max(f[i - 1][1] + 1,f[i - 1][2]));
		f[i][2] = (flag ? max(f[i - 1][2],f[i - 1][0] + 1) : max(f[i - 1][2] + 1,f[i - 1][0]));
		ans = max(f[i][0],max(f[i][1],f[i][2]));
	}
	printf("%d",ans);
	return 0;
}

```


---

## 作者：莫奈的崖径 (赞：9)

通过这道题我们可以发现，CF题目的难度真的很假qwq，至少不该是蓝题。
## 题意
给定一个01串，任选一个区间进行翻转（也就是对本区间内的每一个元素进行取反），求出一个最长的子串，满足这个子串相邻元素不相同。
## 分析
这个题可以找规律来做（同机房同场考试打dp的大佬我%%%），首先我们不对这个串进行翻转操作，直接寻找满足题目要求的这个子串，设长度为cnt。然后进行枚举，在原串中找到最长的连续相等子串，如果这个子串的长度>=3，cnt+=3；如果这个子串的长度为2且只有一个这样的子串，cnt+=1；如果有两个及以上的长度为2的连续相等子串，cnt+=2，最终输出。

这个题不是那么毒瘤的原因在于它只能选取一段区间翻转，如果我们把本来相邻且不相等的两个元素翻转了，我们的翻转就毫无意义，所以我们要寻找连续相等的子串，我们找到这个子串后发现，无论这个子串有多长（当然要大于1），最多只能给我们的答案贡献一个2。

对我这个dp弱惨的蒟蒻真是太友好了qwq。

## AC代码
```cpp
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
char a[1000000];
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        int output=1;
        scanf("%s",a);
        int maxn=0;
        int contz=1;
        int cont2=0;
        for(int i=0;i<n-1;i++)
        {
            if(a[i]==a[i+1])
            {
                contz++;
            }
            else
            {
                if(contz==2)cont2++;
                contz=1,output++;
            }
            maxn=max(contz,maxn);
        }
        if(contz==2)cont2++;
        if(maxn>=3)output+=2;
        if(maxn==2&&cont2>1)output+=2;
        if(maxn==2&&cont2==1)output+=1;
        printf("%d\n",output);
    }
}
```


---

## 作者：jch123 (赞：3)

## 题意

给定一个 $01$ 串，任选一个区间进行翻转（也就是对本区间内的每一个元素进行取反），求出一个最长的子串，满足这个子串相邻元素不相同，输出最大长度。

## 思路
贪心，找规律发现翻转后答案最多 $+2$。

- 如果有 $3$ 个及以上连续的 $+2$，$000$ 变成 $010$。
- 如果有 $2$ 段 $2$ 个 $+2$，$0011$ 变成 $0101$。
- 如果有 $1$ 段 $2$ 个 $+1$， $00$ 变成 $01$。
- 否则不变。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n,ans=1,flag=0,cnt=0;
	cin>>n;
	string s;
	cin>>s;
	for(int i=1;i<=n;i++) a[i]=s[i-1]-'0';
	for(int i=2;i<=n;i++) 
		if(a[i]!=a[i-1]) ans++;
	for(int i=2;i<=n;i++)
	{
		if(a[i]==a[i-1]) cnt++;
		if(a[i]==a[i-1]&&i<n&&a[i]==a[i+1]) flag=1;
	}
	if(flag) ans+=2;
	else if(cnt>=2) ans+=2;
	else if(cnt>=1) ans++;
	cout<<ans;
	return 0;
}
```

---

## 作者：zhangqiuyanAFOon2024 (赞：1)

思维题。

首先，我们得知道，操作之后，答案最多只能增加 $2$。

可以简单证明一下，操作就是把原来的分成三段，然后这三段内的显然是不变的，增加的，只能是第一段和第二段的交接处和第二段和第三段的交接处。

我们再思考一下，怎样才能增加 $2$。

其实就是有两个连续的两个 $0$ 或 $1$ 就行。

特别的，若有三个连续，只要转中间那个。

同理，增加 $1$ 的，只要有一个连续的两个 $0$ 或 $1$ 就行。

代码很简单。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n;string s;
	cin>>n>>s;
	int cnt=1,ans=0;
	for(int i=1;i<n;i++){
		if(s[i]!=s[i-1]) cnt++;
		else ans++;//判断连续
	}
	if(ans>=2) cout<<cnt+2;
	if(ans==1) cout<<cnt+1;
	if(ans==0) cout<<cnt;//输出
	return 0;
}
```

---

## 作者：Register_int (赞：1)

小分讨吧，难度不是很大。  
容易发现区间反转只对两端的贡献有影响。所以答案最多 $+2$。首先，如果有长度 $\ge3$ 的连续 $0/1$ 串，那么只要反转串的中间一位，就可以将答案 $+2$。否则，如果有两个长度 $=2$ 的连续 $0/1$ 串，将反转的区间两端设为这两个子串的中心，答案也可以增加 $2$。如果只有一个该串，则将左端点设为开头，答案会 $+1$。其他情况下，答案不变。  
判断完输出就好了。  
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 10;

int n, ans = 1, cnt1, cnt2;

char s[MAXN];

int main() {
	scanf("%d%s", &n, s);
	for (int i = 1; i < n; i++) {
		if (s[i] != s[i - 1]) ans++;
		else cnt2++;
		if (i < n - 1 && s[i - 1] == s[i] && s[i] == s[i + 1]) cnt1++;
	}
	printf("%d", cnt1 || cnt2 > 1 ? ans + 2 : cnt2 == 1 ? ans + 1 : ans);
}
```

---

## 作者：Chenziyong2011 (赞：1)

# 题意：
	题目给定一个串，要求只对一个区间内的字符进行翻转，求其中最长的间隔子串。
------------
# 思路：
题目乍一看是非常复杂的，但实际上答案最多只能多二，只要判断四种可能性就可以了。（可能性见下）

1. 多二：需要二个连续的字符。
2. 多一：需一个连续的字符。
3. 不变：无连续的字符。
4. 特例（多二）。
------------

# 代码
整体来说代码也是非常简单的。
```cpp
#include<iostream>

using namespace std;
long long n, sum = 0, num = 1;
char a[100010];
int main() {
	cin >> n;
	for (int i = 0;i < n;i++) {
		cin >> a[i];
	}
	for (int i = 1;i < n;i++) {
		if (a[i] != a[i - 1]) num++;
		else   sum++;
	}
	if (sum >= 2) {
		num += 2;
	}
	if (sum == 1) {
		num += 1;
	}
	cout << num;
	return 0;
}
```

---

## 作者：Zheng_iii (赞：0)

## 思路
~~你猜这个题为什么是 A 题？~~

很思维的解法。

只允许翻转一次，所以最多只会在原答案上加 $2$。

所以我们来讨论仅有的三种可能：

- 加 $2$，要有两段连续的 $0$ 或 $1$。
- 加 $1$，要有一段连续的 $0$ 或 $1$。
- 不加，没有连续的 $0$ 或 $1$。

我们的代码模拟上面的三种可能就好了。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
string s;
int n;

int main(){
	// freopen("text.in","r",stdin);
	// freopen("text.out","w",stdout);
	ios::sync_with_stdio(0),cout.tie(0),cin.tie(0);
	cin>>n>>s;
	int ans = 1;
	int ctn = 0;
	for(int i = 1;i < n;i++){
		if(s[i] != s[i-1]){
			ans++;
		}else{
			ctn++;
		} 
	}
	if(ctn >= 2)cout<<ans+2;
	if(ctn == 1)cout<<ans+1;
	else cout<<ans;
	return 0;
}
```

---

## 作者：lzdqwq (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF603A)

### 思路：

我们可以发现，答案最多只能增加 $2$ 。

所以分情况讨论即可：

1. 增加 $2$，需要一个连续的字符。

2. 增加 $1$，需要两个连续的字符。

3. 增加 $0$，无连续的字符。

4. 特殊情况，如果有三个连续，翻转中间的那个即可。

### 代码：

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define ll long long
using namespace std;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll n,sum1=1,sum2=0;
	string s;
	cin>>n>>s;
	for(int i=1;i<n;i++){
		if(s[i]!=s[i-1]) sum1++;
		else sum2++;
	}
	if(sum2>=2) cout<<sum1+2;
	if(sum2==1) cout<<sum1+1;
	if(sum2==0) cout<<sum1;
	return 0;
}
```

---

## 作者：lixuanxi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF603A)

本题只允许翻转一次，因此最多只会在原答案上增加 $2$。

分情况讨论：

$1$：答案增加 $2$，需要 $2$ 个连续 $0$ 或 $1$。

$2$：答案增加 $1$，需要 $1$ 个连续 $0$ 或 $1$。

$3$：答案增加 $0$，没有连续 $0$ 或 $1$。

特殊情况：$3$ 个连续的 $0$ 或 $1$，只需要翻中间的那个。

代码比较简单。

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,num=1,ans;//初始值 
char s[N];
int main(){
	cin>>n;
	for(int i=0;i<n;i++)cin>>s[i];
	for(int i=1;i<n;i++){
		if(s[i]!=s[i-1])num++;//判断非连续 
		else ans++;//判断连续 
	}
	if(ans>=2)num+=2;
	else if(ans==1)num++;
	cout<<num;
	return 0;
}
~~~

---

## 作者：little_cindy (赞：0)

此题考察算法： $\colorbox{#E74C3C}{\color{white}动态规划,dp}$。

## 思路

### 状态：

|定义|前面是否有子串翻转|当前第 $i$ 个数字是否反转|
|:-:|:-:|:-:|
|$dp_{i,0}$|否|否|
|$dp_{i,1}$|是|否|
|$dp_{i,2}$|否|是|

### 初始值

因为无论如何，第 $1$ 个形成的子序列长度是 $1$。所以

$$\begin{cases}dp_{1,0}=1\\dp_{1,1}=1\\dp_{1,2}=1\end{cases}$$

### 转移方程

对于所有满足条件的 $i(2\le i \le n)$，当 
$a_i=a_{i-1}$ 时：

1. $dp_{i,0}$

因为第 $i$ 个不反转，前面的也不翻转，得出递推式：

$$dp_{i,0}=dp_{i-1,0}$$

2. $dp_{i,1}$

因为第 $i$ 个不反转，前面的会翻转，要么第 $i-1$ 个翻转（他俩本相同，当前又不翻转，则不同，长度需加 $1$），要么第 $i-1$ 个之前早就翻转完了。得出递推式：

$$dp_{i,1}=\max\begin{cases}dp_{i-1,2}+1\\dp_{i-1,1}\end{cases}$$

3. $dp_{i,2}$

因为第 $i$ 个要反转，前面的都无法翻转，要么第 $i-1$ 个翻转，要么前面的都不翻转（他和前面的相同，前面的没翻转，则不同，长度需加 $1$）。得出递推式：

$$dp_{i,2}=\max\begin{cases}dp_{i-1,2}\\dp_{i-1,0}+1\end{cases}$$

对于 $a_i\not=a_{i-1}$ 时：

1. $dp_{i,0}$

因为第 $i$ 个不反转，前面的也不翻转，另外前面的与当前不同，长度需加 $1$，得出递推式：

$$dp_{i,0}=dp_{i-1,0}+1$$

2. $dp_{i,1}$

因为第 $i$ 个不反转，前面的会翻转，要么第 $i-1$ 个翻转，要么第 $i-1$ 个之前早就翻转完了（他和前面的不同，前面和当前的都没翻转，则还是不同，长度需加 $1$）。得出递推式：

$$dp_{i,1}=\max\begin{cases}dp_{i-1,2}\\dp_{i-1,1}+1\end{cases}$$

3. $dp_{i,2}$

因为第 $i$ 个要反转，前面的都无法翻转，要么第 $i-1$ 个翻转（他和前面的不同，前面和当前的都翻转了，则还是不同，长度需加 $1$），要么前面的都不翻转。得出递推式：

$$dp_{i,2}=\max\begin{cases}dp_{i-1,2}+1\\dp_{i-1,0}\end{cases}$$

综上所述，状态转移方程是：

$$\begin{cases}dp_{i,0}=\begin{cases}dp_{i-1,0}(a_i=a_{i-1})\\dp_{i-1,0}+1(a_i≠a_{i-1})\end{cases}\\dp_{i,1}=\begin{cases}\max\begin{cases}dp_{i-1,2}+1\\dp_{i-1,1}\end{cases}(a_i=a_{i-1})\\\max\begin{cases}dp_{i-1,2}\\dp_{i-1,1}+1\end{cases}(a_i≠a_{i-1})\end{cases}\\dp_{i,2}=\begin{cases}\max\begin{cases}dp_{i-1,2}\\dp_{i-1,0}+1\end{cases}(a_i=a_{i-1})\\\max\begin{cases}dp_{i-1,2}+1\\dp_{i-1,0}\end{cases}(a_i≠a_{i-1})\end{cases}\end{cases}$$

知道了上面那个奇怪无比的递推式，思路也就显而易见。

### 输出结果

由于每一种情况都已经考虑，所以只需要输出 $\max\begin{cases}dp_{n,0}\\dp_{n,1}\\dp_{n,2}\end{cases}$ 即可

## code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull usigned ll
#define inl inline
using namespace std;
const int maxn=0;
int a[1000005],dp[1000005][3],n;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){//单个字符读入
    	char ch;
    	cin>>ch;
    	a[i]=ch-'0';
	}
	dp[1][0]=dp[1][1]=dp[1][2]=1;//初始化
	for(int i=2;i<=n;i++){//动态规划
	    if(a[i]==a[i-1]){
	    	dp[i][0]=dp[i-1][0];
	    	dp[i][1]=max(dp[i-1][2]+1,dp[i-1][1]);
	    	dp[i][2]=max(dp[i-1][2],dp[i-1][0]+1);
		}
		else{
	    	dp[i][0]=dp[i-1][0]+1;
	    	dp[i][1]=max(dp[i-1][1]+1,dp[i-1][2]);
	    	dp[i][2]=max(dp[i-1][2]+1,dp[i-1][0]);
		}
	}
	cout<<max(max(dp[n][0],dp[n][1]),dp[n][2]);//输出最大值即可
	return 0;
}
```
### update timw:2021-8-10
修改了管理员提出的错误

---

