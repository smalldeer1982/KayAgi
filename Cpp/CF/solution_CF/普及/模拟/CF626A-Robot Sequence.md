# Robot Sequence

## 题目描述

Calvin the robot lies in an infinite rectangular grid. Calvin's source code contains a list of $ n $ commands, each either 'U', 'R', 'D', or 'L' — instructions to move a single square up, right, down, or left, respectively. How many ways can Calvin execute a non-empty contiguous substrings of commands and return to the same square he starts in? Two substrings are considered different if they have different starting or ending indices.

## 说明/提示

In the first case, the entire source code works, as well as the "RL" substring in the second and third characters.

Note that, in the third case, the substring "LR" appears three times, and is therefore counted three times to the total result.

## 样例 #1

### 输入

```
6
URLLDR
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
DLUU
```

### 输出

```
0
```

## 样例 #3

### 输入

```
7
RLRLRLR
```

### 输出

```
12
```

# 题解

## 作者：Siteyava_145 (赞：3)

# 暴力

众所周知，本题 $n \le 200$。

初步思路：枚举每一段的开头和结尾，遍历字母统计次数，当上下抵消，左右抵消时，计数器 $+1$。时间复杂度：约 $O(n^3)$。
代入：运算 $8 \times 10^6$ 次，不会时间超限。

于是我们码出了下面的：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,cnt=0,u,r,d,l;
    cin>>n;
    char s[201];
    for(int i=1;i<=n;i++)cin>>s[i];//下面枚举的是从1开始的，就从1开始输入。
    for(int i=1;i<=n;i++){//开头
        for(int j=i;j<=n;j++){//结尾
            u=0,r=0,d=0,l=0;
            for(int x=i;x<=j;x++){
                if(s[x]=='U'){u++;}
                if(s[x]=='R'){r++;}
                if(s[x]=='D'){d++;}
                if(s[x]=='L'){l++;}
            }
            if(u==d && r==l){cnt++;}
        }
    }
    printf("%d",cnt);
    return 0;
}
```


---

## 作者：zplqwq (赞：3)

# CF626A

Hello! 

我又回来惹~~为了上橙名~~。

# Section 1 题目分析

## 题意

这道题的题目应该比较明确。

给你一个长度为n的字符串。

```txt
遇到U,坐标x向上移动一格

遇到D,坐标x向下移动一格

遇到L,坐标y向左移动一格

遇到R,坐标y向右移动一格
```

最后统计有多少个不同的非空连续子序列，能使得这一系列操作执行这个子序列命令后能回到起点。

## 做法

​	因为$1≤n≤200$ 而且时限 2s 所以暴力枚举问题不大。	

​	所以我们可以直接暴力三重循环枚举。

## 坑点

1. 注意啊，每次遍历新的坐标时注意要将坐标清0

# Section 2 代码

```c++
#include<bits/stdc++.h>//万能头
using namespace std;
const int N=100010;

char s[N];

int n,m;
int a[N];
int ans;//答案

int cnt,ret;//坐标

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
	}
	for(int i=1;i<n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			ret=0;//注意清零！！！！！
			cnt=0;
			for(int k=i;k<=j;k++)//三重超级大循环枚举字串
			{
				if(s[k]=='U') ret++;//移动坐标
				if(s[k]=='D') ret--;
				if(s[k]=='L') cnt--;
				if(s[k]=='R') cnt++;
			}
			if(ret==0 and cnt==0)//能回到原点
			{
				ans++;
			}
		}
	}
	cout<<ans<<endl;//输出
	
	return 0;
}
```



管理大大求过

---

## 作者：WsW_ (赞：2)

### 更新
这是一篇**已通过**的题解。
- $2024.12.12$ 更新老题解。

---
### 思路
#### 暴力
枚举每一个子段，统计每个字段中四个字母分别出现的次数，如果上下移动次数相同并且左右移动次数相同，则说明抵消回到起点。  

时间复杂度 $O(n^3)$。
代码就不贴了。  

#### 优化  
我们发现，暴力会有很多时间浪费在重复统计，例如对于：  
```
UDLR
```
先是统计了 ``UD`` ，后面又得要重新从第一个 ``U`` 统计到最后一个 ``R`` ，就浪费了重复统计 ``UD`` 的时间。  
直接去掉清空部分，每次新加入就进行判断，因为同时判断，所以不用清零，可以节省掉重复统计的时间。  

时间复杂度 $O(n^2)$。  

---

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,a[5];
char ch[203];
int main(){
	scanf("%d",&n);
	cin>>ch;
	for(int i=0;i<n;i++){
		for(int j=i;j<n;j++){
			if(ch[j]=='U')a[1]++;
			if(ch[j]=='D')a[2]++;
			if(ch[j]=='L')a[3]++;
			if(ch[j]=='R')a[4]++;
			if(a[1]==a[2]&&a[3]==a[4])ans++;//统计后直接判断，不再初始化，避免重复统计浪费时间
		}
		a[1]=0;//清零。
		a[2]=0;
		a[3]=0;
		a[4]=0;
	}
	printf("%d",ans);
	return 0;
}
```

---
### 后记
还可以用类似于[[CSP-S2023] 消消乐](https://www.luogu.com.cn/problem/P9753)一题的方法做到更好的复杂度，留给大家思考。

---

## 作者：codeLJH114514 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF626A)

# 题目大意

给你一个长度为 $n$ 的字符串 $s$，要你计算有多少个非空子串可以让 Calvin 的机器人从原点出发回到原点。

# 解题思路

## 算法 $1$ 暴力枚举 时间复杂度 $O(n ^ 3)$

具体思路 ：

枚举子串的左右两个端点，判断其是否满足条件。（条件判断即为该子串中 U 和 D 、 L 和 R 的个数是否一致）

没啥好说的，上代码！ (用 unordered_map 记录 U, D, L, R 的出现次数。)

```cpp
#include <unordered_map>
#include <iostream>
using namespace std;
int n, res;
string s;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> s; // 输入
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) { // 枚举 i, j
            int x = 0, y = 0;
            unordered_map<char, int> cnt;
            for (int k = i; k <= j; k++)
                cnt[s[k]] += 1; // 计算UDLR的出现次数
            if (cnt['U'] == cnt['D'] and cnt['L'] == cnt['R'])
                res += 1;
        }
    }
    cout << res << "\n"; // 输出res
    return 0;
}
```

由于该题评测数据水，所以该算法可以通过此题!

## 算法 $2$ 前缀和 时间复杂度 $O(n ^ 2)$

具体思路 :

基于算法 1，因为我们在最内层循环中用了 $O(n)$ 的时间统计 UDLR 的出现次数，所以可以考虑使用前缀和算法预处理出各个字母的出现次数，这样我们的算法的时间复杂度就由 $O(n ^ 3)$ 降到 $O(n ^ 2)$ 了。

```cpp
#include <iostream>
#define maxn 512
using namespace std;
int n, res;
string s;
int cnt[5][maxn];
string letter = "$UDLR";
int Count(int, int, int);
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> s; // 输入
    for (int i = 0; i < n; i++)
        for (int j = 1; j <= 4; j++)
            cnt[j][i] = cnt[j][i - 1] + (s[i] == letter[j]);
            // 前缀和预处理
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            if (Count(1, i, j) == Count(2, i, j) and Count(3, i, j) == Count(4, i, j))
                res += 1;
                // O(1) 计算是否满足条件
    cout << res << "\n"; // 直接输出
    return 0;
}
int Count(int alpha, int Left, int Right) {
// 函数功能 ：计算字母alpha在s的子串(Left, Right)中出现的次数
    return cnt[alpha][Right] - cnt[alpha][Left - 1];
}
```

（所有代码均可直接通过，请放心食用！）

---

## 作者：Cult_style (赞：2)

## 时间充裕，$O(n^3)$是小问题

用$(x,y)$表示坐标，一开始设为$(0,0)$如果最后的坐标还是$(0,0)$，那就符合条件，$ans++$

只要遇到$U$,坐标$x$向上移动一格

遇到$D$,坐标$x$向下移动一格

遇到$L$,坐标$y$向左移动一格

遇到$R$,坐标$y$向右移动一格

得出代码：

```
#include<bits/stdc++.h>
#define MN 205
using namespace std;
char s[MN];
int ans;
int main(){
	int n;
	scanf("%d%s",&n,s+1);
	for(int i=1;i<n;++i){
		for(int j=i+1;j<=n;++j){
			int x,y;
			x=y=0;
			for(int k=i;k<=j;++k){
				if(s[k]=='U') x++;
				if(s[k]=='D') x--;
				if(s[k]=='L') y--;
				if(s[k]=='R') y++;
			}
			if(x==0&&y==0){
				ans++;
			}
		}
	}
	printf("%d",ans);
	
	return 0;
}
```


---

## 作者：Daniel_yao (赞：1)

## 题目大意

随意输入了一串指令，求有多少个指令子段能使机器人回到原点。

### 具体思路

把整个操作系统看成一个直角坐标系，机器人向上走，则 $x$ 坐标增加一，向下走，则 $x$ 坐标减少一。以此类推，最后只需要把这个过程模拟出来就行了。

## AC Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define rint register int  
#define For(i,l,r) for(rint i=l;i<=r;i++)
#define FOR(i,r,l) for(rint i=r;i>=l;i--)
#define mod 1000000007
using namespace std;

inline int read() {
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}

const int N = 205;

char s[N];

int n, ans;

signed main() {
	n = read();
	scanf("%s", s + 1);
	For(i,1,n) {
		For(j,i,n) {
			int x, y;
			x = y = 0;
			For(k,i,j) {
				if(s[k] == 'U') x ++;
				if(s[k] == 'D') x --;
				if(s[k] == 'L') y --;
				if(s[k] == 'R') y ++; 
			}
			ans += x == 0 && y == 0;
		}
	}
	cout << ans << '\n';
	return 0;
} 
```

$O(N^3)$，秒切！

但还不够优美，仔细想一下，可省了内层枚举。

# AC Code 


```cpp
#include <bits/stdc++.h>
#define ll long long
#define rint register int  
#define For(i,l,r) for(rint i=l;i<=r;i++)
#define FOR(i,r,l) for(rint i=r;i>=l;i--)
#define mod 1000000007
using namespace std;

inline int read() {
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}

const int N = 205;

char s[N];

int n, ans;

signed main() {
	n = read();
	scanf("%s", s + 1);
	For(i,1,n) {
		int x, y;
		x = y = 0;
		For(j,i,n) {
			if(s[j] == 'U') x ++;
			if(s[j] == 'D') x --;
			if(s[j] == 'L') y --;
			if(s[j] == 'R') y ++; 
			ans += x == 0 && y == 0;
		}
	}
	cout << ans << '\n';
	return 0;
} 
```
$O(N^2)$，完美收官！

---

## 作者：_HiKou_ (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/CF626A)

这道题的思路和 [CF1059A](https://www.luogu.com.cn/problem/CF1059A) 思路是差不多的！都是三重循环！

因为 $(1\le n \le 200)$ 所以 $O(n^3)$ 的做法是完全可以接受的！

思路差不多，都是枚举开始和结束时间，然后遍历看坐标，看看是不是回到原点。

CODE:

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,ans,i,j,k;
string s;
int main(){
	scanf("%lld",&n);
	cin>>s;
	for(i=0;i<n;i++)//从0开始
	for(j=0;j<=i;j++)//单个的字符可以不考虑，当然加上等号也没事
	{
		ll x=0,y=0;
		for(k=j;k<=i;k++)
		{
			if(s[k]=='U')y++;
			if(s[k]=='D')y--;
			if(s[k]=='L')x--;
			if(s[k]=='R')x++;
		}
		if(x==0&&y==0)ans++;//如果回到原点就方案加一
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：sinsop90 (赞：1)

由于 $n \le 200$, 首先考虑一个暴力算法

注意到机器人能回到起点，当且仅当执行 $U$ 的次数和 $D$ 的次数相等，$L$ 的次数和 $R$ 的次数相等

因此,由于要求是连续子序列，我们直接查询每一个区间 $[l,r]$， 暴力判断里面 $U$ 的次数是否和 $D$ 相等， $L$ 的次数是否和 $R$ 相等

因此我们得到了 $O(n^{3})$ 的算法，是能够 AC 的

代码如下:

```
#include <bits/stdc++.h>
using namespace std;
int n, ans;
char mps[100005];
int main() {
	scanf("%d", &n);
	cin >> mps;
	for(int i = n;i >= 1;i--) {//个人喜爱
		mps[i] = mps[i - 1];
	}
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= n - i + 1;j++) {
			int a1 = 0, a2 = 0, a3 = 0, a4 = 0;
			for(int k = i;k <= i + j - 1;k++) {
				if(mps[k] == 'U') a1 ++;
				if(mps[k] == 'D') a2 ++;
				if(mps[k] == 'L') a3 ++;
				if(mps[k] == 'R') a4 ++;
			}
			if(a1 == a2 && a3 == a4) {
				ans ++;
			}
		}
	}
	cout << ans << endl;
}
```

但是做题就要精益求精,我们思考一下能否优化这个代码

显然 $O(n^{3})$ 在 $n$ 大的时候并不能 $AC$

于是,我们发现我们可以对查询区间 $[l,r]$ 的时候进行优化

我们考虑前缀和存,这样我们就可以 $O(1)$ 查询区间 $[l,r]$ 了

此时我们得到了一个 $O(n^{2})$ 的算法，~~非常优秀~~

代码如下:

```
#include <bits/stdc++.h>
using namespace std;
int n, ans;
int t[5][100005] = {0, 0, 0, 0, 0};//1 U 2 D 3 L 4 R
char mps[100005];
int main() {
	scanf("%d", &n);
	cin >> mps;
	for(int i = n;i >= 1;i--) {
		mps[i] = mps[i - 1];
	}
	for(int i = 1;i <= n;i++) {
		t[1][i] = t[1][i - 1] + (mps[i] == 'U');//前缀和
		t[2][i] = t[2][i - 1] + (mps[i] == 'D');
		t[3][i] = t[3][i - 1] + (mps[i] == 'L');
		t[4][i] = t[4][i - 1] + (mps[i] == 'R');
	}
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= n - i + 1;j++) {
			if(t[1][i + j - 1] - t[1][i - 1] == t[2][i + j - 1] - t[2][i - 1] && t[3][i + j - 1] - t[3][i - 1] == t[4][i + j - 1] - t[4][i - 1]) {
				ans ++;
			}
		}
	}
	cout << ans << endl;
}
```


---

## 作者：Apro1066 (赞：1)

这题其实没有黄题的难度吧。。

按照题意，只要向上与向下的次数相等并且向左或向右的次数相等就可以了，外面套2个循环，不断找子串，看能否匹配。

```cpp
#include <stdio.h>
#include <iostream>
using namespace std;
int n,s;
char a[1001];
inline bool check(int l,int r)//能否匹配？ 
{
	register int e,b,c,d,i;
	e=b=c=d=0;
	for(i=l;i<=r;i++)
	{
		if(a[i]=='U') e++;
		if(a[i]=='D') b++;
		if(a[i]=='L') c++;
		if(a[i]=='R') d++;
	}
	if(e==b && c==d)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	register int i,j,k;
	cin>>n>>a+1;
	for(i=1;i<=n;i++)//枚举左端点
	{
		for(j=i+1;j<=n;j++)//枚举右端点，这个就是不断找子串的过程 
		{
			if(check(i,j))
				s++;
		}
	}
	cout<<s<<endl;
	return 零;
} 
```


---

## 作者：GossWandering (赞：0)

居然在我之前所有的题解都是 $O(n^3)!$ ，那么由我来补充一个 $O(n^2)$ 的算法吧、

之前所有题解的思路都是：
- 暴力枚举起点、终点
- 暴力的 $\text{check}$ 一遍枚举出来的子序列是否合法。

那么究竟暴力算法的“效率低”是怎么造成的呢？

我们来模拟一下样例 $3$

在你程序中，你计算了一下两个子序列：

- `RL`（1~2个字符） 此时 $R$ 有 $1$ 个，$L$ 有 $1$ 个，$U/D$ 都是 $0$ 个。
- `RLRLRL` （1~6个字符），你会发现你的程序重复计算了1~2个字符 $R/L/U/D$ 的个数！

那怎么解决这个重复计算呢？我们考虑边枚举终点边加，算法流程如下：
- 暴力枚举起点，并开启 $4$ 个计数器，分别来计算 $R/L/U/D$ 的个数。
- 开始枚举终点，更新计数器，若 $R/L/U/D$ 个数都为 $0$ ，则答案加一。

我们发现我们不用暴力 $\text{check}$ 了！于是，成功从 $O(n^3)$ 优化到 $O(n^2)$.

下是程序：
```
for(int i=1;i<=n-1;i++){//起点
    int Su=0,Sd=0,Sl=0,Sr=0;//开计数器
    for(int j=i;j<=n;j++){//终点
        if(str[j]=='U') Su++;
        if(str[j]=='D') Sd++;
        if(str[j]=='L') Sl++;
        if(str[j]=='R') Sr++;
        if(Su==Sd && Sl==Sr) ans++;//满足条件
    }
}
```

---

## 作者：KillerXu (赞：0)

首先考虑什么时候能走回起点，不难想到，当向上走的次数等于向下走的次数，向左走的次数等于向右走的次数时就走回了起点。看一眼数据范围，$n≤200$,直接暴力枚举出每一段子序列，然后再分别暴力计算出这段子序列中向四个方向走的次数，最后判断一下是否符合上面所说的条件，是的话计数就行了。

## 代码

（最慢一个点31ms,还是比较快的）

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 205
using namespace std;
int f[4];//f[0]记录向上走的次数，f[1]记录向下，f[2]向左，f[3]向右 
int n;
char a[N];//记录指令 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];//读入指令 
	int ans=0;
	for(int i=1;i<n;i++)
	 for(int j=i+1;j<=n;j++){//暴力枚举出每一段子序列 
	 	memset(f,0,sizeof(f));//清零 
	    for(int k=i;k<=j;k++){//暴力计算向四个方向走的次数 
	  	    if(a[k]=='U') f[0]++;
	  	    if(a[k]=='D') f[1]++;
	  	    if(a[k]=='L') f[2]++;
	  	    if(a[k]=='R') f[3]++;
	    }
	    if(f[0]==f[1] && f[2]==f[3]) ans++;//如果向上走的次数等于向下走的次数，向左等于向右，说明回到了起点，计数 
	}
	cout<<ans; 
	return 0;
}
```


---

