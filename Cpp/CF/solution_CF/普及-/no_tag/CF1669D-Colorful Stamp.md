# Colorful Stamp

## 题目描述

A row of $ n $ cells is given, all initially white. Using a stamp, you can stamp any two neighboring cells such that one becomes red and the other becomes blue. A stamp can be rotated, i.e. it can be used in both ways: as $ \color{blue}{\texttt{B}}\color{red}{\texttt{R}} $ and as $ \color{red}{\texttt{R}}\color{blue}{\texttt{B}} $ .

During use, the stamp must completely fit on the given $ n $ cells (it cannot be partially outside the cells). The stamp can be applied multiple times to the same cell. Each usage of the stamp recolors both cells that are under the stamp.

For example, one possible sequence of stamps to make the picture $ \color{blue}{\texttt{B}}\color{red}{\texttt{R}}\color{blue}{\texttt{B}}\color{blue}{\texttt{B}}\texttt{W} $ could be $ \texttt{WWWWW} \to \texttt{WW}\color{brown}{\underline{\color{red}{\texttt{R}}\color{blue}{\texttt{B}}}}\texttt{W} \to \color{brown}{\underline{\color{blue}{\texttt{B}}\color{red}{\texttt{R}}}}\color{red}{\texttt{R}}\color{blue}{\texttt{B}}\texttt{W} \to \color{blue}{\texttt{B}}\color{brown}{\underline{\color{red}{\texttt{R}}\color{blue}{\texttt{B}}}}\color{blue}{\texttt{B}}\texttt{W} $ . Here $ \texttt{W} $ , $ \color{red}{\texttt{R}} $ , and $ \color{blue}{\texttt{B}} $ represent a white, red, or blue cell, respectively, and the cells that the stamp is used on are marked with an underline.

Given a final picture, is it possible to make it using the stamp zero or more times?

## 说明/提示

The first test case is explained in the statement.

For the second, third, and fourth test cases, it is not possible to stamp a single cell, so the answer is "NO".

For the fifth test case, you can use the stamp as follows: $ \texttt{WWW} \to \texttt{W}\color{brown}{\underline{\color{red}{\texttt{R}}\color{blue}{\texttt{B}}}} \to \color{brown}{\underline{\color{blue}{\texttt{B}}\color{red}{\texttt{R}}}}\color{blue}{\texttt{B}} $ .

For the sixth test case, you can use the stamp as follows: $ \texttt{WWW} \to \texttt{W}\color{brown}{\underline{\color{red}{\texttt{R}}\color{blue}{\texttt{B}}}} \to \color{brown}{\underline{\color{red}{\texttt{R}}\color{blue}{\texttt{B}}}}\color{blue}{\texttt{B}} $ .

For the seventh test case, you don't need to use the stamp at all.

## 样例 #1

### 输入

```
12
5
BRBBW
1
B
2
WB
2
RW
3
BRB
3
RBB
7
WWWWWWW
9
RBWBWRRBW
10
BRBRBRBRRB
12
BBBRWWRRRWBR
10
BRBRBRBRBW
5
RBWBW```

### 输出

```
YES
NO
NO
NO
YES
YES
YES
NO
YES
NO
YES
NO```

# 题解

## 作者：GI录像机 (赞：3)

## 思路简述：

因为两种颜色实际上等价，所以我们只考虑一种颜色。

长度为一时，显然无解。

全部同色时，显然无解。

当字符串为 $\textcolor{blue}{B}\textcolor{red}{R}$ 时，我们考虑往两侧添加颜色。

- 向右添加 $\textcolor{red}{R}$ 时，我们只需提前在右两格印上 $\textcolor{blue}{B}\textcolor{red}{R}$ ；

+ 向右添加 $\textcolor{blue}{B}$ 时，我们只需提前在右两格印上 $\textcolor{red}{R}\textcolor{blue}{B}$ ；

* 向左添加 $\textcolor{blue}{B}$ 时，我们只需提前在左两格印上 $\textcolor{blue}{B}\textcolor{red}{R}$ ；

+ 向左添加 $\textcolor{red}{R}$ 时，我们只需提前在左两格印上 $\textcolor{red}{R}\textcolor{blue}{B}$ ；

故长度大于一的非全部同色的任意连续有色字符串（非白色）都有解。

至此，我们可以把问题给出的字符串以 $\textcolor{gray}{W}$ 为分界线，分成若干个连续地有色字符串，若有字符串长度为一或全部同色，则无解，否则有解。

## 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(long long x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
int t = read();
int main() {
	while (t--) {
		int n = read(), b = 0, r = 0;
		string s;
		cin >> s;
		for (int i = 0; i < n; i++) {
			if (s[i] == 'B')b++;
			else if (s[i] == 'R')r++;
			else {
				if (b == 0 && r == 0)continue;
				if (r && b) {
					b = r = 0;
					continue;
				}
				break;
			}
		}
		if (((!b) && r) || ((!r) && b))puts("NO");
		else puts("YES");
	}
	return 0;
}
```


---

## 作者：0xFF (赞：2)

#### 题目大意


------------
给定一个长度为 $n$ 的字符串由 ```R B W``` 三种字符组成（```R``` 表示红色，```B``` 表示蓝色,```W```表示无色）。

一开始的字符串全由 ```W``` 组成，每次可以选中两个相邻的位置将这两个位置变成 ```BR``` 或者 ```RB```，问能否将字符串变为题目所给定的样子。

#### 题目分析


------------
由于每次可以选中两个位置操作，所以一段由 ```R B``` 组成的子串只要同时有 ```R``` 和 ```B``` 必然可以得到。

故只需从第一个位置开始找出每一段有 ```R B``` 组成的子串，判断是否同时有 ```R B``` 即可。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>

#define int long long
#define N 500015
using namespace std;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}
int a[N],arr[N],cnt;
char str[N];
signed main(){
	int T = read();
	while(T--){
		int n = read();
		scanf("%s",str+1);
		cnt=0;
		arr[++cnt]=0;
		for(int i=1,nw=0;i<=n;i++){
			if(str[i]=='W') arr[++cnt]=i;
		}
		bool flag = 1;
		arr[++cnt] = n+1;
		for(int i=1;i<cnt;i++){
			bool r = 0,b = 0;
			if(arr[i] + 1 > arr[i+1] - 1) continue;
			for(int j=arr[i]+1;j<=arr[i+1]-1;j++){
				if(str[j] == 'R') r = 1;
				if(str[j] == 'B') b = 1; 
			}
			if(!r || !b) flag = 0;
			if(flag==0) break;
		}
		if(flag==0) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
```


---

## 作者：happy_dengziyue (赞：1)

### 1 思路

我们可以发现，任何一个盖章都不能触碰 `W`。所以，我们可以对每一段进行分别处理。

我们定义“极大子串”为目标字符串的子串，满足这个子串不含 `W`，但是它的左边和右边都必须为 `W` 或边界。

我们可以证明，当且仅当每个极大子串都同时拥有 `R` 和 `B` 时有解。

设这个极大子串为 $s$，长度为 $len$，字符从 $1$ 到 $len$ 编号。

我们可以依次枚举 $i(1\le i<len)$，如果 $s[i]$ 为 `R` 则对 $i$ 和 $i+1$ 执行 `RB` 操作，否则执行 `BR` 操作。

那么问题来了，如果 $s[len-1]$ 和 $s[len]$ 相同怎么办呢？

很简单，如果 $s[len]$ 为 `R`，设 $i$ 满足 $s[i-1]$ 为 `B` 并且 $s[i]$ 到 $s[len]$ 均为 `R`，那么从大到小枚举 $j(i-1\le j<len)$，对于 $j$ 和 $j+1$ 执行 `BR` 操作；反之亦然。

然后我们分别解决完所有的极大子串，问题就完成了。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 200000
int t;
int n;
char s[max_n+2];
int a[max_n+2];
int ai;
bool ansr;
bool ansb;
bool ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1669D_1.in","r",stdin);
	freopen("CF1669D_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%s",&n,s+1);
		a[ai=1]=0;
		for(int i=1;i<=n;++i){
			if(s[i]=='W')a[++ai]=i;
		}
		a[++ai]=n+1;
		ans=true;
		for(int i=1;i<ai;++i){
			if(a[i+1]-a[i]<=1)continue;
			ansr=false;
			ansb=false;
			for(int j=a[i]+1;j<a[i+1];++j){
				if(s[j]=='R')ansr=true;
				if(s[j]=='B')ansb=true;
			}
			if((!ansr)||(!ansb)){
				ans=false;
				break;
			}
		}
		if(ans)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/74393563)

By **dengziyue**

---

