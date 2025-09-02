# Replace With the Previous, Minimize

## 题目描述

### 题意简述

有一个长度为 $n$ 的，只含小写字母的字符串 $s$，每次操作可以选择 $26$ 个字母之一，将字符串中所有该字母替换为上一个字母（如 $\texttt{c}\to\texttt{b},\texttt{b}\to\texttt{a}$，特殊地，$\texttt{a}\to\texttt{z}$）。在 $k$ 次操作**之内**，使得到的字符串的字典序最小。

## 样例 #1

### 输入

```
4
3 2
cba
4 5
fgde
7 5
gndcafb
4 19
ekyv```

### 输出

```
aaa
agaa
bnbbabb
aapp```

# 题解

## 作者：FFTotoro (赞：7)

观察题目，我们可以得到大致思路：

使用贪心，从前往后扫一遍，根据题意找到某种字符可以降到的下限，暴力地从前扫到后更新每个字符，最后再扫一遍，把没有完全更新的字符变成 a 即可。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n,k; string s; cin>>n>>k>>s; char c=97; // 初始化字符变量 c
    for(int i=0;i<n;i++)
      if(s[i]>c){ // 只有更大才有意义继续更新
        if(s[i]-97>k){
          k-=c-97; int mn=s[i]-k; // 找到最低可以降到多少
          for(char h=s[i];h>mn;h--)
            for(int j=0;j<n;j++)
              if(s[j]==h)s[j]=h-1; // 暴力地扫一遍，如果可以降那么就更新
          break;
        }
        else if(c<s[i])c=s[i]; // 更新最低的值，以便最后的更改
      }
    for(int i=0;i<n;i++)
      if(s[i]<=c)s[i]='a'; // 更新成 'a'
    cout<<s<<endl;
  }
  return 0;
}
```

---

## 作者：yanhao40340 (赞：1)

### 题意（复制了一下）
有一个长度为 $n$ 的，只含小写字母的字符串 $s$，每次操作可以选择 $26$ 个字母之一，将字符串中所有该字母替换为上一个字母（如 $\texttt{c} \to \texttt{b}$，$\texttt{b}\to\texttt{a}$，特殊地，$\texttt{a}\to\texttt{z}$）。在 $k$ 次操作之内，使得到的字符串的字典序最小。
### 分析
首先，我们可以发现 $\texttt{a}\to \texttt{z}$ 是肯定用不上的。

而且要想字典序最小，最终序列肯定是开头字母越小越好。

其次，可以发现操作有一个巧妙的性质：具有传递性。例如将 $\texttt{b}$ 替换为 $\texttt{a}$ 后，再想要将 $\texttt{c}$ 替换为 $\texttt{a}$，就可以直接先将 $\texttt{c}$ 替换为 $\texttt{b}$ ，然后将两个 $\texttt{b}$ 一起替换成 $\texttt{a}$。

有了这个性质，~~显而易见，（其实我也不知道为什么会想到）~~ 这道题可以用并查集来完成。把每一次操作都看作一次 $\texttt{merge}$ 操作即可。

因为字母越前面对字典序的影响越大，所以顺序进行操作。

代码很简单。时间复杂度看似 $O(k)$，实际上远远跑不到，大概只有 $O(n)$ 的级别。
### 代码
~~注：由于蒟蒻太懒，没写 $\texttt{merge}$ 函数，将就着看吧。~~
```
#include <iostream>
#include <string>
using namespace std;
string getstr(){
	string s;char f=getchar();
	while (f=='\n'||f=='\0'||f=='\r'||f==' ') f=getchar();
	while (f!='\n'&&f!='\r'&&f!='\0'&&f!=' ') s+=f,f=getchar();
	return s;
}
const int maxn=200020;
int f[30],a[maxn];
int findfa(int x){
	if (f[x]==x) return f[x];
	return f[x]=findfa(f[x]);
}
int main(){
	int t,n,k;scanf("%d",&t);
	while (t--){
		scanf("%d%d",&n,&k);
		string s=getstr();
		for (int i=1;i<=26;++i) f[i]=i;
		for (int i=0;i<n;++i) a[i]=s[i]-'a'+1;
		int tmp=0;
		while (k&&tmp<n){
			while (findfa(a[tmp])!=1&&k)
				f[findfa(a[tmp])]=findfa(findfa(a[tmp])-1),--k;
			++tmp;
		}
		for (int i=0;i<n;++i) putchar(findfa(a[i])+'a'-1);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：caibet (赞：1)

VP div.3 首次过 E，撰题解以祭之。

- 更新日志：

  - 2022.7.14：代码链接挂了，于是还是把代码贴进了题解里（悲）

- 题意：

  在一个长度为 $n$，仅含小写拉丁字母的字符串 $s$ 中，你可以进行最多 $k$ 次如下操作：
  
  - 在 $s$ 中选一个字符，把 $s$ 中所有该字符 ASCII 码 $-1$（特别地，若选定 `a`，则变为 `z`）。
  
  问最后能得到的字典序最小的字符串。
  
- 解法：

  首先，容易发现的贪心思路是：
  
  - 不选定字符 `a`（否则白白浪费了一次操作还变大了字典序）
  - 优先考虑 $s$ 中前面的字符（要使字典序最小）
  
  于是考虑从头到尾处理 $s$：看当前字符需要减多少次才能变成 `a`，并把 $k$ 减去需要的次数，直到 $k$ 不够为止。
  
  但这会导致一些问题。比如如下数据：
  
  ```
  4 2
  abcc
  ```
  
  我们的程序是这样处理的：
  
  - 第一个字符 `a`，字典序已经最小。
  - 第二个字符 `b`，操作 $1$ 次后变为 `a`，$k$ 还剩 $1$。
  - 第三个字符 `c`，操作 $2$ 次后可以变为 `a`，但 $k$ 只剩 $1$ 了，因此只能操作 $1$ 次变成 `b`。
  
  输出为：`aabc`。
  
  但实际上可以直接把所有 `c` 变成 `b`，再把所有 `b` 变成 `a`，形成 `aaaa`。
  
  问题有两个：
  
  - 没有考虑前面已经完成的操作。
  
    则可以记录一个值 $\text{last}$，表示之前选中过的字典序最大的字母。那么只要这次选中的字符 $c$ 能在 $k$ 次内删到 $\text{last}$，就能变成 `a`——因为之前最大也是从 $\text{last}$ 减到 `a`，既然又能从 $c$ 减到 $\text{last}$，那么还不如直接从 $c$ 减到 `a` 呢。
  - 没有把所有选择的字符 ASCII 都 $-1$。
  
    同样使用上面的 $\text{last}$。如果当前字符字典序比 $\text{last}$ 小，那么就已经被换成了 `a`。
    
    当 $k$ 不够把当前字符 $c$ 删到 `a` 时，就把 $s$ 中 ASCII 在 $(c-k,c]$ 内的字符全部变为 $c-k$——在最后的 $k$ 次里，$c$ 变为 $c-1$，$c-1$ 变为 $c-2$，$\dots$，$c-k+1$ 变为 $c-k$，所以上述区间内的字符都可以如此变化。  
    当然，在这个过程中也可以顺便把其它字典序比 $\text{last}$ 小的字符替换成 `a`。最后输出即可。
    
  于是就没有问题了。
  
  ```cpp
  namespace{
  	int T;
  	const int lim=2e5+3;
  	int n,k;
  	char a[lim],last;
  	void solve(){
  		n=read();k=read();
  		F(i,1,<=n) a[i]=readc();
  		last='a';
  		F(i,1,<=n){
  			if(a[i]<=last) a[i]='a';
  			else if(a[i]-last>=k){
  				F(j,1,<=n){
  					if(i!=j&&a[j]>a[i]-k&&a[j]<=a[i]){
  						a[j]=a[i]-k;
  					}
  					if(a[j]<=last){
  						a[j]='a';
  					}
  				}
  				a[i]-=k;
  				if(a[i]<=last) a[i]='a';
  				break;
  			}else{
  				k-=a[i]-last;
  				last=a[i];
  				a[i]='a';
  			}
  		}
  		F(i,1,<=n) putchar(a[i]);
  		endl;
  	}
  	void work(){
  		T=read();
  		while(T--) solve();
  	}
  }
  ```

---

## 作者：Hooch (赞：0)

### 题目大意

给定了两个正整数 $n$ 和 $k$，然后给定一个由小写字母组成的、长度为 $n$ 的字符串 $s$。定义一个操作，如下：

+ 选定一个小写字母 $c$，将 $s$ 中所有 $s_i=c$ 的 $s_i$ 变为 $s_i-1$，比如 `b` 变成 `a`，`c` 变成 `b`，若为 `a` 则变成 `z`。

现在你能对 $s$ 进行 $k$ 次操作，求出你能使得的新的 $s$ 字典序最小的 $s'$。

### 基本思路

我们先从它给定的字典序最小上手。字典序比较中字符串 $a < b$ 的定义是对于一个 $k$，$a_1=b_1,a_2=b_2\cdots a_{k-1}=b_{k-1}\land a_k<b_k0$。

那么我们就应使得前 $i$ 个 $s_i$ 为 `a`，且使 $i$ 最大化，这样构造出的方案一定是字典序最小方案。

### 代码

代码：

```cpp
#include <bits/stdc++.h>
#define rep1(i, l, r) for (register int i(l); i <= r; ++i)
#define rep2(i, l, r) for (register int i(l); i >= r; --i)
using namespace std;
const int N = 2e5 + 5;
int n, t, k; char s[N];
signed main(void) {
	scanf("%d", &t); while (t--) {
		scanf("%d%d", &n, &k); scanf("%s", s + 1);
		int mx = 0, flg = 0;
		rep1(i, 1, n) {
			if (s[i] - 'a' > k) {flg = i; break;}
			mx = max(mx, s[i] - 'a'); 
            //找出第一个无法变成 'a' 的 i
		}
		if (flg) {
			rep1(i, 1, n) {
				if (s[i] <= (mx + 'a')) s[i] = 'a';
                //让所有比能够成为 'a' 的字母都成为 a
			}
			char c = (s[flg] - k + mx);
			rep1(i, 1, n) {
				if (flg == i) continue;
				if (s[i] <= s[flg] && s[i] > c) s[i] = c;
			} s[flg] = c;
			puts(s + 1);
		} else {
			rep1(i, 1, n) putchar('a'); puts("");
		}
	}
}
```

---

## 作者：ryanright (赞：0)

## Description

已知一个小写拉丁字母字符串 $s$，每次可以选中 $s$ 中的一个字母，然后将所有与它相同的字母都变为其在字母表中的前一个字母。你最多只能进行 $k$ 次操作，求字典序最小的可以在 $k$ 次操作中生成的字符串。

## Solution

既然是字典序最小，那我们就优先降 $s_1$，往后看看还有哪些字母可以在 $k$ 次操作后降为 `a`。如果遇到不能的，就先放一放，因为我们优先把前面最小化，把前面的全部降成 `a`。剩下来还有操作次数就全部用在那个不能的，反正前面都是 `a`，这个字符越小，字典序越小。

## Code

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
char str[200005];
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, k;
		scanf("%d%d%s", &n, &k, str + 1);
		if (k >= 25)
			for (int i = 1; i <= n; i++)
				putchar('a');
		else {
			bool flag = 1;
			char maxx = 'a', top, bot;//小于等于maxx的全部降为a，在bot到top之间的全部降为bot，针对第一个要爆步数的
			for (int i = 1; i <= n; i++)
				if (flag) {
					if (str[i] <= 'a' + k) {
						maxx = max(maxx, str[i]);
						putchar('a');
					}
					else {
						top = str[i];
						bot = str[i] - k + maxx - 'a';
						putchar(bot);
						flag = 0;
					}
				}
				else
					if (str[i] <= maxx)
						putchar('a');
					else if (str[i] >= bot && str[i] <= top)
						putchar(bot);
					else
						putchar(str[i]);
		}
		puts("");
	}
	return 0;
}
```

---

