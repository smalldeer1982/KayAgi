# String and Operations

## 题目描述

You are given a string $ s $ consisting of $ n $ characters. These characters are among the first $ k $ lowercase letters of the Latin alphabet. You have to perform $ n $ operations with the string.

During the $ i $ -th operation, you take the character that initially occupied the $ i $ -th position, and perform one of the following actions with it:

- swap it with the previous character in the string (if it exists). This operation is represented as L;
- swap it with the next character in the string (if it exists). This operation is represented as R;
- cyclically change it to the previous character in the alphabet (b becomes a, c becomes b, and so on; a becomes the $ k $ -th letter of the Latin alphabet). This operation is represented as D;
- cyclically change it to the next character in the alphabet (a becomes b, b becomes c, and so on; the $ k $ -th letter of the Latin alphabet becomes a). This operation is represented as U;
- do nothing. This operation is represented as 0.

For example, suppose the initial string is test, $ k = 20 $ , and the sequence of operations is URLD. Then the string is transformed as follows:

1. the first operation is U, so we change the underlined letter in test to the next one in the first $ 20 $ Latin letters, which is a. The string is now aest;
2. the second operation is R, so we swap the underlined letter with the next one in the string aest. The string is now aset;
3. the third operation is L, so we swap the underlined letter with the previous one in the string aset (note that this is now the $ 2 $ -nd character of the string, but it was initially the $ 3 $ -rd one, so the $ 3 $ -rd operation is performed to it). The resulting string is saet;
4. the fourth operation is D, so we change the underlined letter in saet to the previous one in the first $ 20 $ Latin letters, which is s. The string is now saes.

The result of performing the sequence of operations is saes.

Given the string $ s $ and the value of $ k $ , find the lexicographically smallest string that can be obtained after applying a sequence of operations to $ s $ .

## 样例 #1

### 输入

```
6
4 2
bbab
7 5
cceddda
6 5
ecdaed
7 4
dcdbdaa
8 3
ccabbaca
5 7
eabba```

### 输出

```
aaaa
baccacd
aabdac
aabacad
aaaaaaaa
abadb```

# 题解

## 作者：ywy_c_asm (赞：5)

这题的重点在于交换相邻项后，第$i$个字符就不会在$i$位置，然而我们还是要对这个字符进行操作。不过我们可以发现，当执行完前$i-1$个操作后，字符$i$要么位于$i$，要么位于$i-1$位置，所以可以考虑把这个计入dp状态。

另一个有用性质是，进行第$i$次操作的时候是不会影响前缀$[1,i-3]$的，此时这个前缀的字典序应该是最小的。并且也一定不会影响到后缀$[i+2,n]$，那么我们只需要考虑$[i-2,i+1]$这4个字符，这是操作$i$能够影响到的。

于是我们在进行操作$i$时，短期目标是让$i-2$位置的字符最小，长期目标是让$[i-2,i+1]$这4个字符字典序最小，考虑把这个做成dp。$dp[i][0/1]$为，在保证$[1,i-3]$字典序最小的前提下，字符$i+1$是否在位置$i$上（否则它还在$i+1$位置上），字典序最小的$[i-2,i+1]$（这4个字符按位压在一个int内，并且从高位到低位排列，这样字典序最小可以等价为这个数最小）。

转移的时候要保证最高位的字符最小，讨论一下位置即可。注意边界细节以及特判$n=1$和$n=2$。时间复杂度$O(n)$

上代码~

```cpp
#pragma GCC optimize(2)
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 555
#define upmin(_a,_b) _a=min(_a,_b)
using namespace std;
namespace ywy{
	typedef unsigned char byte;
	void sget(char *s){
		int n=1;char c;while((c=getchar())||23333)if(c>='a'&&c<='z')break;
		s[n]=c-'a';n++;while((c=getchar())||23333){
			if(c>='a'&&c<='z')s[n]=c-'a',n++;else return;
		}
	}char str[N],anss[N];int dp[N][2];
	inline int getb(int x,int bit){
		byte *p=(byte*)&x;return(p[bit]);	
	}
	inline int setb(int x,int bit,int y){
		byte *p=(byte*)&x;p[bit]=y;return(x);	
	}
	inline int xchg(int x,int i,int j){
		byte *p=(byte*)&x;swap(p[i],p[j]);return(x);	
	}
	void ywymain(){
		int t;cin>>t;while(t){
			t--;int n,k;cin>>n>>k;sget(str);str[n+1]=str[n+2]=0;
			memset(dp,0x7f,sizeof(dp));dp[0][0]=str[1];
			for(register int i=1;i<=n;i++){
				int minn;if(i>3){
					minn=min(getb(dp[i-1][0],3),getb(dp[i-1][1],3));
				}else minn=0;if(i>3)putchar(minn+'a');
				if(getb(dp[i-1][0],3)==minn){//now str[i] is on bit0
					int me=(dp[i-1][0]<<8)|str[i+1];
					upmin(dp[i][0],me);
					upmin(dp[i][0],setb(me,1,(str[i]+1)%k));
					upmin(dp[i][0],setb(me,1,(str[i]+k-1)%k));
					if(i!=1)upmin(dp[i][0],xchg(me,1,2));
					if(i!=n)upmin(dp[i][1],xchg(me,0,1));
				}if(getb(dp[i-1][1],3)==minn){//now str[i] is on bit1
					int me=(dp[i-1][1]<<8)|str[i+1];upmin(dp[i][0],me);
					upmin(dp[i][0],setb(me,2,(str[i]+1)%k));
					upmin(dp[i][0],setb(me,2,(str[i]+k-1)%k));
					if(i-1!=1)upmin(dp[i][0],xchg(me,2,3));
					upmin(dp[i][0],xchg(me,1,2));	
				}
			}int ans=min(dp[n][0],dp[n][1]);if(n==1){
				putchar(getb(ans,1)+'a');	
			}if(n==2){
				putchar(getb(ans,2)+'a');putchar(getb(ans,1)+'a');	
			}if(n>=3){
				putchar(getb(ans,3)+'a');putchar(getb(ans,2)+'a');putchar(getb(ans,1)+'a');	
			}cout<<endl;
		}
	}
}
int main(){
	ywy::ywymain();return(0);	
}
```

---

## 作者：PineappleSummer (赞：1)

字符串 DP。

设 $dp_i$ 为为前 $i$ 个字符操作后的字典序最小的**字符串**，那么 $dp_i$ 向前最多与 $dp_{i-2}$ 有关，因为一个字符最多向左移动 $2$ 个单位，其操作序列形如 `RL`，即在 $i-1$ 位置使用 `R`，在 $i$ 位置使用 `L`。

对于原来第 $i$ 个字符使用什么，分类讨论一下：
- 第 $i$ 个位置使用 `O/D/U` 且 $i-1$ 位置的操作与第 $i$ 个位置无关，此时 $dp_i$ 仅由 $dp_{i-1}$ 转移而来。
- 第 $i$ 个位置使用 `O/D/U` 且 $i-1$ 位置的操作为 `R`，则 $dp_i$ 应由 $dp_{i-2}$ 与 $s_{i-1}$ 转移而来。
- 第 $i$ 个位置使用 `L`，则 $dp_i$ 为将 $s_i$ 插入到 $dp_{i-1}$ 的第 $i-1$ 位。
- 第 $i-1$ 个位置使用 `R` 且第 $i$ 个位置使用 `L`，则 $dp_i$ 为将 $s_i$ 插入进 $dp_{i-2}$ 的第 $i-2$ 位最后再拼接上 $s_{i-1}$。

最后答案即为 $dp_n$，单组数据时间复杂度 $\mathcal O(n)$。

```cpp
string s, dp[N];
// 设 dp[i] 为前 i 个字符操作后字典序最小的字符串 
char calc (char ch, int d) { return 'a' + (ch -'a' + d + m) % m; }
void chkmin (string &str, string str2) { str = min (str, str2); }
void solve () {
	cin >> n >> m >> s;
	s = " " + s;
	for (int i = 1; i <= n; i++) {
		char ch = min ({s[i], calc (s[i], 1), calc (s[i], -1)});
		dp[i] = dp[i - 1] + ch; // i 时使用 O/D/U 
		if (i >= 2) {
			chkmin (dp[i], dp[i - 2] + ch + s[i - 1]);  // i - 1 时使用 R  
			chkmin (dp[i], dp[i - 1].substr (0, i - 2) + s[i] + dp[i - 1][i - 2]); // i 时使用 L
		}
		if (i >= 3) chkmin (dp[i], dp[i - 2].substr (0, i - 3) + s[i] + dp[i - 2][i - 3] + s[i - 1]); // i - 1 时使用 R i 时使用 L 
	}
	cout << dp[n] << '\n';
}
```

---

## 作者：tribool4_in (赞：0)

很有意思的字符串 dp。

首先设 $dp_i$ 表示前 $i$ 个字符进行操作后字典序最小的字符串。发现如果一个字符往前移动可能会对前面的字符造成影响，不过容易发现位于 $i$ 的字符至多只会向前移动到 $i-2$ 位置（操作序列形如 `RL`），因此 $dp_{i+1}$ 最左只会从 $dp_{i-1}$ 转移。

考虑如何转移到 $dp_{i+1}$，大力分类讨论（“当前位置”为最初在 $s_{i+1}$ 的字符）。

- 当前位置进行 `D/U/O` 操作且前一个位置未进行 `R` 操作，可以直接转移 $dp_i\to dp_{i+1}$，考虑哪个操作最优即可。
- 操作序列形如 `R D/U/O`，则可以直接在 $dp_{i-1}$ 后拼接。
- 当前进行 `L` 操作且前一个位置未进行 `R` 操作，则只需要将当前字符插入到 $dp_i$ 的 $i-1$ 位转移。
- 操作序列形如 `R L`，则此时当前位置会被移动到 $i-2$ 位置，需要从 $dp_{i-1}$ 转移并考虑 $dp_{i-1}$ 的最后一位。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int T;
int n, m;
string s, dp[N];
char trans(char ch, int d) { return 'a' + (ch - 'a' + m + d) % m; }
void chkmin(string &x, string v) { x = min(x, v); }
void work() {
    cin >> n >> m >> s;
    for (int i = 0; i < n; i++) {
        char ts = min(s[i], min(trans(s[i], 1), trans(s[i], -1)));
        dp[i + 1] = dp[i] + ts; // O / D / U
        if (i > 0) {
            chkmin(dp[i + 1], dp[i - 1] + ts + s[i - 1]); // R O/D/U
            chkmin(dp[i + 1], dp[i].substr(0, i - 1) + s[i] + dp[i][i - 1]); // ? L
        }
        if (i > 1) chkmin(dp[i + 1], dp[i - 1].substr(0, i - 2) + s[i] + dp[i - 1][i - 2] + s[i - 1]); // ? R L
    }
    cout << dp[n] << '\n';
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> T;
    while (T--) work();
    return 0;
}
```

---

## 作者：7KByte (赞：0)

很有意思的动态规划。

这道题的关键点在于想到用 ``string`` 作为动态规划的 $f$ 数组。

首先前 $i$ 次操作只能影响前 $i+1$ 个位置，所以我们定义状态 $f[i]$ 表示前 $i$ 次操作，前 $i+1$ 个位置字典序最小的串。

对于 ``OUDR`` 操作，直接模拟一下即可。

但是对于 ``L`` 操作，我们发现还会影响前面的位置。

但是观察到第 $i$ 个操作最多影响到位置 $i-2$ ，而只有连续的 ``RL`` 操作可以做到。

所以我们再记录一下上一个操作是不是 ``R`` 即可。时间复杂度 $\mathcal{O}(T n^2)$ 。事实上只用记录最后三位即可做到 $\mathcal{O}(Tn)$，但是细节太多就弃了/doge 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 505
using namespace std;
int n,k;char s[N];string f[N][2];
char nx(char ch){return 'a' + (ch - 'a' + 1) % k;}
char pr(char ch){return 'a' + (ch - 'a' + k - 1) % k;}
string g(string x,int i,int op){
	if(x == "~")return x;
	if(!op) x[i-1] = nx(x[i-1]);
	else x[i-1] = pr(x[i-1]);
	return x;
}
string sp(string x,int i){
	if(x == "~")return x;
	swap(x[i-1],x[i-2]);
	return x;
}
void solve(){
	scanf("%d%d",&n,&k);
	scanf("%s",s + 1);
	f[0][0] = "";f[0][1] = "~";
	f[0][0] += s[1];
	rep(i, 1, n){
		// O
		f[i][0] = min(f[i-1][1], f[i-1][0]);
		// U
		f[i][0] = min(f[i][0], min(g(f[i-1][0], i, 0), g(f[i-1][1], i-1, 0)));
		// D
		f[i][0] = min(f[i][0], min(g(f[i-1][0], i, 1), g(f[i-1][1], i-1, 1)));
		// L
		if(i > 1)f[i][0] = min(f[i][0], sp(f[i-1][0], i));
		if(i > 2)f[i][0] = min(f[i][0], sp(f[i-1][1], i-1));
		// R
		if(i < n)f[i][1] = sp(f[i - 1][0] + s[i + 1],i + 1);
		
		if(i < n)f[i][0] += s[i + 1];
	}
	cout<< f[n][0] <<endl;
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：orz_z (赞：0)



注意到进行完前 $i$ 次操作之后，$s_{i+1}$ 要么在 $i$，要么在 $i+1$，取决于上一次 $s_i$ 是否在 $i$ 位置且上一次执行的是否是 `R` 操作。

因此设 $dp_{i,0/1}$ 表示进行完前 $i$ 次操作后，$s_{i+1}$ 否/是被移到了 $i$ 位置后最小的字典序，转移就分 `OUDLR` 五种情况转移即可，时间复杂度 $\mathcal O(n^2)$。

注意到每次操作影响的区间极小，可维护，时间复杂度优化至 $\mathcal O(n)$。

---

