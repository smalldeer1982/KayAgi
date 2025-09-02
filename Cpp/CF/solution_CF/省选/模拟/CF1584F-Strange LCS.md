# Strange LCS

## 题目描述

You are given $ n $ strings $ s_1, s_2, \ldots, s_n $ , each consisting of lowercase and uppercase English letters. In addition, it's guaranteed that each character occurs in each string at most twice. Find the longest common subsequence of these strings.

A string $ t $ is a subsequence of a string $ s $ if $ t $ can be obtained from $ s $ by deletion of several (possibly, zero or all) symbols.

## 说明/提示

In the first test case, the longest common subsequence is "A". There are no common subsequences of length $ 2 $ .

In the second test case, sets of characters of strings don't intersect, so any non-empty string can't be a common subsequence.

## 样例 #1

### 输入

```
4
2
ABC
CBA
2
bacab
defed
3
abcde
aBcDe
ace
2
codeforces
technocup```

### 输出

```
1
A
0

3
ace
3
coc```

# 题解

## 作者：xh39 (赞：15)

## 前言
如果有看不懂，或者题解中有错误，欢迎指出。

本篇题解讲得比较详细，可能比较啰嗦，如果想看更简单了请移步其它题解或跳读。
## 前置算法

请先学习 状态压缩 dp

建议学习[动态规划（dp）求最长公共子序列](https://www.luogu.com.cn/problem/AT4527)。会 $O(n^3)$ 的做法即可。~~（其实这题我也没做）~~

## 题目大意
求 $n$ 个字符串的最长公共子序列。

数据范围：$n\le10$，每个字符在同一个字符串中最多出现 $2$ 次。只会出现 $52$ 个英文大小写字母。大小写敏感。

## 注：
1. 为方便状态压缩，除特殊说明外，以下所有编号从 $0$ 开始。
4. 为避免下标、括号过多造成困扰，有些数组用中括号代替下标。$a[x]$ 表示 $a_x$。
5. 所有 "之后" 都不包含当前。比如 $3$ 之后 指 $4,5,6,\ldots$ 而不包含 $3$。
6. $s_k$ 表示第 $k$ 个字符串。
7. 字母表大小指出现的字符种类数。比如对于本题，只会出现 $52$ 种字符，则字母表大小为 $52$。

经管理员反馈，暴力做法有些多余。所以放到[这里](https://www.luogu.com.cn/training/129033)，供有需要的看。
## 简化题目：每个字符在同一个字符串中最多出现 $1$ 次。

只出现 $1$ 次，让我们想到了**用元素来表示下标**。

设 $f[i]$ 表示所有字符串都删掉字符 $i$ 之后的字符，剩下的字符串的最长公共子序列。。其中 $i$ 可以为字母表内任意字母，此处为 'a'~'z' 和 'A'~'Z'。

则 $f[i]=max\{f[j]\}+1$（$j$ 在所有的字符串都出现在 $i$ 位置的前面）

如果看了之前暴力的解法，这个状态转移方程也是同样的思路。故不多解释。

## 原题正解

每个字符在同一个字符串中最多出现 $2$ 次。

还是采用同样的思路：用元素表示下标。

但是元素有重复了，怎么办？方法是**记录第几次出现**。

设 $f[i][j_0][j_1][j_2]\ldots[j_{n-1}]$ 表示对于 $s_k$，删掉第 $j_k$ 次出现的 $i$ 之后的所有字符。其中 $i$ 取英文字母，$j$ 取 $0$ 或 $1$。

状态转移方程：$f[i][j_0][j_1][j_2]\ldots[j_{n-1}]=max\{f[c][d_0][d_1][d_2]\ldots[d_{n-1}]\}+1$ ($d$ 要满足 $s_k$ 中，字符 $c$ 在第 $d_k$ 次出现在 字符 $i$ 第 $j_k$ 次 前面）

但是这怎么转移呢，难道枚举 $d$？这样是可以的，因为 $n\le10$。时间复杂度为 $O(52\times 4^n)$ 但是不优，代码也比较难写。考虑继续优化。

## 继续优化

**采用贪心的策略。对于 $s_k$，如果有 $d_k=1$ 的转移，则 $d_k=0$ 一定不比 $d_k=1$ 优。**

因为第 $0$ 次出现一定比第 $1$ 次前面。删除第 $1$ 次后面的情况包含了删除 $0$  次之后的情况。因为在第 $0$ 次与第 $1$ 次之间的字符可以不选。

所以在转移的时候枚举完 $c$ 就可以计算出 $d$。看 $s_k$ 出现当前位置（字符 $i$ 第 $j_k$ 次出现的位置）之前有多少个 $c$ 字符。如果有 $2$ 个则 $d_k=1$，有 $1$ 个则 $d_k=0$，如果没有说明这个字符 $c$ 不合法，无法进行状态转移。

时间复杂度：共 $2^n$ 个状态，转移需要枚举第一维的字符，并需要 $O(n)$ 求出 $d$ 数组实现后面许多维的转移，所以是这两个乘起来，看代码就很快能分析复杂度。所以在本题中，复杂度(字母表大小 $52$ 的常数不省略)为 $O(52\times n\times 2^n)$。

如果将本题拓展一下，每个字符在同一个字符串中最多出现 $ci$ 次。且字母表大小为 $bet$。此时 $d$ 数组的取值就为 $0$~$(ci-1)$ 那么复杂度为 $O(bet\times n\times ci^n)$。

## 具体实现

$f[i][j_0][j_1][j_2]\ldots[j_{n-1}]$ 这是一个 $(n+1)$ 维的状态。并且 $n$ 的值还可以变。所以转移起来相当麻烦。

$j=0或1$，这让我们想到了**状态压缩**。具体地，**用一个 $n$ 位二进制数表示 $n$ 个状态**。设这个数为 $g$，则 $g=2^0\times j_0+2^1\times j_1+2^2\times j_2+\ldots+2^{n-1}\times j_{n-1}$。可以发现，每一个 $g$ 表示了唯一的 $j$。

那么 $f[i][g]=max\{f[c][h]\}+1$。（$h$ 可以通过 继续优化 板块中的方法先计算 $d$ 数组，然后计算得出，$c$ 为任意合法的字符）

---

输出方案：每个状态都**记录它是从哪个状态转移过来的**。

具体地，可以记录字符 $x(i,g)$ 和整数 $y(i,g)$ 表示 $f[x(i,g)][y(i,g)]$ 是最大值。（$f[i][g]=max\{f[c][h]\}+1$ 中找出最大的 $f[c][h]$，然后，$x(i,g)=c,y(i,g)=h$）

具体见代码。

---

由于 $i$ 是字符，转移不方便。所以将字符对应成数字。代码中 'a'~'z' 对应 0~25；'A'~'Z' 对应 26~51。

---

统计答案与转移类似。如果一个字符在 $s_k$ 中出现了 $2$ 次，则 $d_k=1$，$1$ 次则 $d_k=0$，$0$ 次则不合法。

## 代码

由于还是有很多无用状态，并且不方便按调用的先后顺序递推，于是用记忆化递归实现。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int m[25],f[105][10005],tkr0[105][10005],tkr1[105][10005],id[2][25][105],n,ykb;
//m:字符串长度。ykb:pow(2,n)。
//id[0][i][j]:第i个串中第0次出现类型j的字符的位置。id[1][i][j]:第1次。
//shu[i][j][k]:第i个串第j个位置前有几个类型k的字符。
//tkr0,tkr1分别表示题解中讲到的 x(i,g) 和 y(i,g)。
string s[25];
int fyr(int zifu,int ci,int step){ //zifu:最后一个公共字符。ci:出现几次的集合,就是题目中的g。这个就表示了 f[i][g]。step是调试的时候用的，请忽略。
	if(f[zifu][ci]>=0){
		return f[zifu][ci];
	}
	int i,j,Max=0,maxid=-1,s_; //s_表示通过d数组计算出的g。实际上并不需要把d数组存下来,可以依次求其每一位,同时更新s_的值。具体见下。
	for(i=0;i<52;i++){ //枚举转移的字符。
		s_=0; 
		for(j=0;j<n;j++){ //依次判断每个字符串。 
			if(id[0][j][i]>=id[(bool)(ci&(1<<j))][j][zifu]){ //如果之前没有出现过这个字符。
				break;
			}
			if(id[1][j][i]<id[(bool)(ci&(1<<j))][j][zifu]){ //如果出现过2次。此时d_k=1,否则d_k=0。 
				s_|=(1<<j); //将第j位修改为1。由于初始时s_=0，所以未修改的位默认为0。
			}
		}
		if(j==n&&fyr(i,s_,step+1)>=Max){ //前一个for循环正常结束时j应该等于n。如果j!=n则说明提前break了，说明有一个字符串之前没出现过此字符。
			Max=f[i][s_]+1;
			tkr0[zifu][ci]=i; //存下从哪里转移过来的。
			tkr1[zifu][ci]=s_;
		}
	}
	f[zifu][ci]=Max;
	return Max;
}
void out(int aaa,int bbb){ //输出方案部分。
	if(tkr0[aaa][bbb]>=0){ //如果等于-1说明没有前一个状态了。就是以这个状态为开头(即此时f=1)。
		out(tkr0[aaa][bbb],tkr1[aaa][bbb]);
	}
	if(aaa<26){ //用递归模拟栈输出aaa。
		cout<<(char)(aaa+'a');
	}else{
		cout<<(char)(aaa-26+'A');
	}
}
void Main(){
	cin>>n;
	ykb=(1<<n);
	memset(id,39,sizeof(id));
	memset(f,-1,sizeof(f));
	memset(tkr0,-1,sizeof(tkr0));
	int i,j,Max=0,maxid0=-1,maxid1=-1,s_;
	for(i=0;i<n;i++){
		cin>>s[i];
		m[i]=s[i].size();
		for(j=0;j<m[i];j++){
			if(islower(s[i][j])){ //将字符转化为数字。
				s[i][j]=s[i][j]-'a';
			}else{
				s[i][j]=s[i][j]-'A'+26;
			}
			if(id[0][i][s[i][j]]>12345){ //如果>12345，说明是没有被存储过的,此时是第0次出现，否则是第1次出现。
				id[0][i][s[i][j]]=j;
			}else{
				id[1][i][s[i][j]]=j;
			}
		}
	}
    //统计答案部分。与转移类似,不详细解释。
	for(i=0;i<52;i++){
		s_=0;
		for(j=0;j<n;j++){ //依次判断每个字符串。 
			if(id[0][j][i]>12345){ //如果没有出现过这个字符。 
				break;
			}
			if(id[1][j][i]<12345){ //如果可以选第 1 个。 
				s_|=(1<<j);
			}
		}
		if(j==n&&fyr(i,s_,0)>=Max){
			Max=f[i][s_]+1;
			maxid0=i;
			maxid1=s_;
		}
	}
	cout<<Max<<endl;
	if(maxid0!=-1){ //maxid0==-1说明没找到比0大的，即Max=0。
		out(maxid0,maxid1);
	}
	cout<<endl;
}
int main(){
	int t,i;
	cin>>t;
	for(i=0;i<t;i++){
		Main();
	}
	return 0;
}
```
## 题外话
分享一下(赛时/赛后)做这题的心路历程和代码中的一些细节。

40分钟做完 ABC，然后看 D，思考许久，还是感觉不可做。看 E，感觉可做，但就是一直想不出来。直到看完F,才发现 F 比 D,E 要简单许多。大概一眼就能想到大概的解法。但是对于今年提高组 24 分连三等奖都没拿到的我，在剩下不到一小时的时间内做完是不可能的。最后在 18:00 左右的时候才调出来。

所以下次比赛还是应该看完所有题目再挑最容易的做。（如果一眼想到正解可以马上开始写）

一开始，在求 $d$ 数组那一部分我没想到贪心转移的细节，然后就想用类似轮廓线的方法转移。后面发现贪心就可以了。

然后，一年多没 AC 过状态压缩，所以写出了一堆错误。这里只举三个典型一点的错误：

```id[(bool)(ci&(1<<j))][j][zifu]``` 这里我一开始没加 ```(bool)```，就是把位运算看成了逻辑运算，然后就数组越界了，调了很久。

然后，我认为只需要输出字符即可，所以记录方案时只记录了代码中的 tkr0,然后发现根本无法转移，所以卡了一会儿。

接着，统计答案部分我也写错了，就认为对于原问题 $d$ 数组所有元素都为 $1$(相当于 $g=2^n-1$)，调用时直接写 ```if(j==n&&fyr(i,ykb-1,0)>=Max){``` 。后面才发现 **不一定所有字符都出现了 $2$ 次。所以统计答案时也要求 $d$ 数组。**

---

## 作者：Alex_Wei (赞：13)

> CF1584F. [Strange LCS](https://codeforces.ml/problemset/problem/1584/F) *2600

仍然是**从简化版入手**。考虑弱化版 “每个字符只出现一次” 怎么做：对于两个字符 $x,y$，如果它们在第一个字符中的出现位置 $p_x,p_y$ 有 $p_x>p_y$，那么 $x$ 不可能转移到 $y$。这给予我们 DP 的顺序：枚举从 $1$ 到 $l_1$ 的所有位置 $i,j\ (1\leq i< j\leq l_1)$，若 $s_{1,i}$ 在每个字符串的出现位置都在 $s_{1,j}$ 之前，那么 $i$ 可以转移到 $j$，$\mathrm{checkmax}(f_j,f_i+1)$，其中 $f_i$ 表示 $s_{1,1\sim i}$ 与其他所有字符串的 LCS 长度最大值。

不难将其扩展到本题的做法：只需要再记录一个 `mask` $S$，$f_{i,S}$ 表示匹配到每个字符串 $s_{1,i}$ 的前一个出现位置还是后一个出现位置。转移时枚举下一个字符 $j$ 求出 **最小的** `mask`（这里用了贪心的思想，能靠前尽量靠前显然更优）即可。时间复杂度 $\mathcal{O}(Tn|\Sigma|^22^n)$，代码写起来还是很舒服的。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define mem(x, v, s) memset(x, v, sizeof(x[0]) * (s)) 
const int N = 10;
const int S = 110;

int T, n, ap, aS, len[N], mp[1 << N];
int f[S][1 << N], buc[N][S], p[N][S][2];
pii tr[S][1 << N];
char s[N][S];
void print(int i, int S) {
	if(!i) return;
	print(tr[i][S].first, tr[i][S].second), putchar(s[0][i - 1]);
}
int main(){
	for(int i = 0; i < 26; i++) mp['a' + i] = i;
	for(int i = 0; i < 26; i++) mp['A' + i] = i + 26;
	cin >> T;
	while(T--) {
		cin >> n, mem(f, 0, S), mem(buc, 0, N), ap = aS = 0;
		for(int i = 0; i < n; i++) {
			cin >> s[i], len[i] = strlen(s[i]);
			for(int j = 0; j < len[i]; j++) {
				int id = mp[s[i][j]];
				p[i][id][buc[i][id]++] = j;
			}
		} for(int i = 0; i < len[0]; i++)
			for(int S = 0; S < 1 << n; S++) if(!i || f[i][S])
				for(int j = i + 1; j <= len[0]; j++) {
					int ok = 1, msk = 0, pr = i ? mp[s[0][i - 1]] : 0, su = mp[s[0][j - 1]];
					for(int q = 0; q < n && ok; q++) {
						int b = S >> q & 1;
						if(!buc[q][su] || i && buc[q][pr] <= b) {ok = 0; break;}
						if(!i) continue;
						int cp = p[q][pr][b], fd = -1;
						for(int k = 0; k < buc[q][su] && fd == -1; k++)
							if(p[q][su][k] > cp) fd = k;
						fd == -1 ? ok = 0 : msk |= fd << q;
					} int v = !i ? 1 : f[i][S] + 1;
					if(ok && f[j][msk] < v) {
						f[j][msk] = v, tr[j][msk] = {i, S};
						if(v > f[ap][aS]) ap = j, aS = msk;
					}
				} cout << f[ap][aS] << "\n", print(ap, aS), puts("");
	}
	return 0;
}
```

---

## 作者：灵茶山艾府 (赞：8)

首先思考：如果每个字母至多出现一次，要怎么做？

如果对于每个字符串，字母 $x$ 都出现在字母 $y$ 的左边，那么就在 $x$ 到 $y$ 之间连一条有向边。

问题变成求有向无环图（DAG）的最长路，这可以用记忆化搜索（或者拓扑排序）解决。

回到本题。

比如有两个字符串，字母 $x$ 的在第一个字符串的下标为 $i_1$ 和 $i_2$，在第二个字符串中的下标为 $j_1$ 和 $j_2$，那么字母 $x$ 就有 $4$ 种不同的位置组合：

1. 位置为 $(i_1, j_1)$ 的 $x$。
2. 位置为 $(i_1, j_2)$ 的 $x$。
3. 位置为 $(i_2, j_1)$ 的 $x$。
4. 位置为 $(i_2, j_2)$ 的 $x$。

推广到 $n$ 个字符串，每个字母至多有 $2^n$ 种不同的位置组合。

用二进制数 $\textit{mask}$ 记录字母 $c$ 在各个字符串中的位置，记作 $(\textit{mask},c)$。

- $\textit{mask}$ 二进制从低到高第 $i$ 位为 $0$，表示 $c$ 位于 $s[i]$ 中的左边那个 $c$ 的下标。
- $\textit{mask}$ 二进制从低到高第 $i$ 位为 $1$，表示 $c$ 位于 $s[i]$ 中的右边那个 $c$ 的下标。

如果对于每个字符串，字母 $x$（位置组合为 $\textit{mask}$）都出现在字母 $y$（位置组合为 $\textit{mask}_2$）的左边，那么就在 $(\textit{mask},x)$ 到 $(\textit{mask}_2,y)$ 之间连一条有向边。同样地，问题变成求有向无环图（DAG）的最长路，这可以用记忆化搜索（或者拓扑排序）解决。

考虑用记忆化搜索计算。定义 $\textit{dfs}(\textit{mask},c)$ 表示 LCS 首字母为 $c$，位置组合为 $\textit{mask}$ 时的 LCS 长度。

枚举下一个字母 $\textit{ch}$，设 $\textit{ch}$ 在各个字符串中的位置为 $\textit{mask}_2$，则用 $\textit{dfs}(\textit{mask}_2,\textit{ch}) + 1$ 更新答案的最大值（下面代码把 $+1$ 放在返回前计算）。

注意这里 $\textit{mask}_2$ 要贪心地计算，如果两个 $\textit{ch}$ 都满足要求，优先取左边的。

答案为 $\textit{dfs}(0,0)-1$，这里取字符 `'\0'` 作为 LCS 的首字母，这样就无需在 $\textit{dfs}$ 外面枚举 LCS 的首字母了。（假设 `'\0'` 在各个字符串中的下标是 $-1$。）

为了输出具体方案，可以用一个 $\textit{from}$ 数组，在 $\textit{dfs}$ 中记录转移来源。

```go
package main
import ."fmt"

func main() {
	var T, n int
	var s string
	for Scan(&T); T > 0; T-- {
		Scan(&n)
		pos := [123][10][]int{}
		for i := 0; i < n; i++ {
			pos[0][i] = []int{-1} // 假定在 LCS 前面还有个字符 '\0'，下标为 -1
			Scan(&s)
			for j, b := range s {
				pos[b][i] = append(pos[b][i], j) // 记录字母 b 在字符串 s[i] 中的出现位置 j
			}
		}

		memo := make([][123]int, 1<<n)
		for i := range memo {
			for j := range memo[i] {
				memo[i][j] = -1
			}
		}
		type pair struct{ mask int; c byte }
		from := make([][123]pair, 1<<n) // 记录转移来源
		var dfs func(int, byte) int
		dfs = func(mask int, c byte) (res int) {
			p := &memo[mask][c]
			if *p != -1 {
				return *p
			}
			var frm pair
			// 枚举 LCS 的下一个字母 ch
			// 要求：ch 在所有字符串中的下标 > c 在对应字符串中的下标
			// 如果有两个 ch 都满足要求，优先取左边的，对应下面代码中的 p[0] > cur
			for ch := byte('A'); ch <= 'z'; {
				mask2 := 0
				for i, p := range pos[ch][:n] {
					if p == nil {
						goto nxt
					}
					cur := pos[c][i][mask>>i&1] // 当前字母 c 的下标
					// p[0] 或者 p[1] 是下一个字母 ch 的下标
					if p[0] > cur {
						// 0
					} else if len(p) > 1 && p[1] > cur {
						mask2 |= 1 << i
					} else {
						goto nxt
					}
				}
				if r := dfs(mask2, ch); r > res {
					res = r
					frm.mask = mask2 // 记录转移来源
					frm.c = ch
				}
			nxt:
				if ch == 'Z' {
					ch = 'a'
				} else {
					ch++
				}
			}
			from[mask][c] = frm
			res++
			*p = res
			return
		}
		Println(dfs(0, 0) - 1)

		lcs := []byte{}
		for p := from[0][0]; p.c > 0; p = from[p.mask][p.c] {
			lcs = append(lcs, p.c)
		}
		Printf("%s\n", lcs)
	}
}
```

时间复杂度：$\mathcal{O}(n2^n|\Sigma|^2)$。其中 $|\Sigma|$ 为字符集合的大小，本题 $|\Sigma|=52$。

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)

---

## 作者：xzzduang (赞：4)

[传送门](https://codeforces.com/problemset/problem/1584/F)

考虑平时我们是怎么判断 T 是否是 S 的子序列的，现在找完了 T 中的前 $i$ 个，显然是在 S 中贪心地找到最近的下一个。

现在考虑模拟这个过程，$f[p_1][p_2][p_3]...[p_n]$ 表示现在在各串中分别匹配到了第 $p_i$ 个的最大答案。显然这样存不下，但我们其实记了很多冗余信息，而且每个字符最多出现两次的条件也没用到。于是优化得状态 $f_{c,msk}$ 代表目前最后一个匹配到的字符是 $c$，这个字符在各串中分别是前面/后面那个（因为每种字符最多出现两遍）。转移的话枚举下一个要匹配的字符就好了。

这题枚举状态如果直接 for 的话是不好弄的，可以用一个队列，类似于 bfs。

```CPP
#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<vector>
#include<queue>
using namespace std;
inline int read(){
	int x=0,f=0; char ch=getchar();
	while(!isdigit(ch)) f|=(ch==45),ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return f?-x:x;
}
int n,f[60][1<<10],ans,nows,nowc;
char s[15][200];
inline int tran(char c){
	if('a'<=c && c<='z') return c-'a';
	return c-'A'+26;
}
inline char rev(int x){
	if(x<26) return char(x+'a');
	else return char(x-26+'A');
}
vector <int> mp[15][60];
struct node{
	int s,c;
}pre[60][1<<10];
queue <node> q;
void print(){
	if(nowc==-1) return;
	int C=nowc,S=nows;
	nowc=pre[C][S].c,nows=pre[C][S].s;
		// cout<<nows<<' '<<nowc<<endl;
	print();
	putchar(rev(C));
}
int main(){
	for(int cas=read();cas--;){
		n=read();
		for(int i=1;i<=n;++i){
			scanf("%s",s[i]+1);
			int len=strlen(s[i]+1);
			for(int j=0;j<60;++j) mp[i][j].clear();
			for(int j=1;j<=len;++j){
				mp[i][tran(s[i][j])].push_back(j);
			}
		}
		ans=0;
		memset(f,0,sizeof(f));
		for(int c=0;c<52;++c)for(int s=0;s<(1<<n);++s)
			q.push({s,c}),pre[c][s]={-1,-1};
		while(!q.empty()){
			int s=q.front().s,c=q.front().c;q.pop();
			int ok=1;
			for(int i=1;i<=n;++i) if(((s>>i-1)&1)>=mp[i][c].size()) ok=0;
			if(!ok) continue;
			f[c][s]=max(f[c][s],1);
			if(f[c][s]>ans){
				ans=f[c][s];
				nows=s,nowc=c;
			}
			for(int t=0;t<52;++t){
				int flag=1,to=0;
				for(int i=1;i<=n;++i){
					int k=((s>>i-1)&1);
					k=mp[i][c][k];
					int p=0;
					for(;p<mp[i][t].size();++p){
						if(mp[i][t][p]>k) break; 
					}
					if(p>=mp[i][t].size()){flag=0;break;}
					if(p==1) to|=(1<<i-1);
				}
				if(!flag) continue;
				if(f[t][to]<f[c][s]+1){
					f[t][to]=f[c][s]+1;
					pre[t][to]={s,c};
					q.push({to,t});
				}
			}
		} 
		cout<<ans<<endl;
		print();
		putchar('\n');
	}
	return 0;
}

```



---

## 作者：xishanmeigao (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1584F)

先考虑每种字母只出现一次怎么做。

此时如果我们枚举 LCS 的末尾，则可以直接定位到某个字符串的某个具体位置，直接将子问题的范围限制住了，非常的舒服。于是可以设 $f_{i,j}$ 表示长度为 $i$ 的 LCS，结尾为 $j$ 是否可行。定位到 $n$ 个字符串 $j$ 所在的位置，然后枚举上一个字符 $k$，看在 $n$ 个字符串里， $k$ 是否均在 $j$ 的前面，若可以，则 $f_{i-1,k}\to f_{i,j}$。答案即最大的 $i$ 满足 $\exist j,s.t.f_{i,j}=1$。时间复杂度 $\mathcal{O}(Tlen\times |\Sigma|^2n)$。

当出现两次后，直接记录最后一个字符是什么显然不行，还需记录最后一个字符是第 $i$ 个字符串的第一个还是第二个。这个可以直接状压出来，于是我们将状态改为 $f_{i,j,s}$ 表示长度为 $i$ 的 LCS，结尾为 $j$，状压出来的状态是 $s$ 是否可行。像上述方法一样转移：枚举上一个字符 $k$，贪心地优先取第二个，不合法才取第一个。然后 $f_{i-1,k,s'}\to f_{i,j,s}$。时间复杂度 $\mathcal{O}(Tlen \times |\Sigma|^2n2^n)$。

这样仍然无法通过。注意到 $f$ 的转移是存在顺序的，将其看作子序列自动机就是一个 DAG。于是可以省去第一维，直接记 $f_{j,s}$ 表示以 $j$ 结尾，状态为 $s$ 的最长长度。为了满足转移顺序，使用记忆化搜索，时间复杂度 $\mathcal{O}(T|\Sigma|^2n2^n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;

const int N=210,M=55,S=(1<<10)+10,INF=1e7;

int n,sta;
int pos[12][M][2];
int f[M][S],vis[M][S],pd[M][S];
pii pr[M][S];
char str[12][N];
vector <int> use[M];

pii chk[N];

int id(char c)
{
	if(c>='a' && c<='z') return c-'a'+1;
	return 26+c-'A'+1;
}

void print(int t)
{
	if(t>=1 && t<=26) putchar(t+'a'-1);
	else putchar(t-26+'A'-1);
}

void dfs(int j,int k)
{
	if(!j) return;
	dfs(pr[j][k].fi,pr[j][k].se);
	print(j);
}

int F(int j,int s)
{
	if(vis[j][s]) return f[j][s];
	vis[j][s]=1;
	if(!pd[j][s]) return f[j][s]=-INF;
	for(int jj=0; jj<=52; jj++)
	{
		int ss=0;
		if(j==jj && s!=sta) continue;
		for(int o=1; o<=n; o++)
		{
			int tmp=(s>>(o-1))&1;
			int p=pos[o][j][tmp];
			int q=pos[o][jj][1],qq=1;
			if(q==-1 || q>p) q=pos[o][jj][0], qq=0;
			if(j==jj) q=pos[o][j][0], qq=0;
			if(q==-1 || q>p) goto Nxt;
			ss+=qq*(1<<(o-1));
		}
		F(jj,ss);
		if(f[jj][ss]+1>f[j][s]) 
			f[j][s]=f[jj][ss]+1, pr[j][s]={jj,ss};
		Nxt:;
	}
	return f[j][s];
}

void mian()
{
	scanf("%d",&n); int Mn=N;

	for(int i=0; i<=n; i++)
		for(int j=0; j<=52; j++)
			for(int k=0; k<2; k++)
				pos[i][j][k]=-1;

	for(int i=1; i<=n; i++)
	{
		scanf("%s",str[i]+1);
		int len=strlen(str[i]+1); Mn=min(Mn,len);
		for(int j=1; j<=len; j++)
		{
			int t=id(str[i][j]);
			if(pos[i][t][0]>0) pos[i][t][1]=j;
			else pos[i][t][0]=j;
		}
	}

	sta=(1<<n)-1;
	for(int i=1; i<=52; i++)
	{
		for(int s=0; s<=sta; s++)
		{
			pd[i][s]=0;
			for(int j=1; j<=n; j++)
			{
				int k=(s>>(j-1))&1;
				if(pos[j][i][k]==-1) goto nxt;
			}
			use[i].push_back(s);
			pd[i][s]=1;
			nxt:;
		}
	}

	for(int j=0; j<=52; j++)
		for(int k=0; k<=sta; k++)
			f[j][k]=-INF, vis[j][k]=0;
	f[0][0]=0;
	for(int s=0; s<=sta; s++)
		vis[0][s]=1, pd[0][s]=0;
	pd[0][0]=1;
	for(int i=1; i<=n; i++)
		pos[i][0][0]=0;

	int ans=0; pii lst={0,0};
	for(int j=1; j<=52; j++)
	{
		for(int s:use[j])
		{
			if(!vis[j][s]) f[j][s]=F(j,s);
			if(f[j][s]>ans) ans=f[j][s], lst={j,s};
		}
	}

	printf("%d\n",ans);
	if(ans)
		dfs(lst.fi,lst.se);
	puts("");
}

int main()
{
	// freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);

	int T; scanf("%d",&T);
	while(T--) mian();
	 
	return 0;
}
```

---

## 作者：OldDriverTree (赞：0)

好题。

# Solution

直接 $\text{DP}$ 是 $O(n\vert\Sigma\vert^n)$ 的，显然过不了。考虑子序列自动机上 $\text{DP}$，设 $f_{p_1,p_2,\dots,p_n}$ 表示当前子序列在 $n$ 个子序列自动机上匹配到的位置分别为 $p_1,p_2,\dots,p_n$，当前子序列后面最多还能添加多少个字符（由于实现用的是记忆化搜索，为了方便状态就设计成这样），转移就枚举下一个字符填什么即可。

这种做法的时间复杂度看似更劣了，实际上这样遍历到的状态数只有 $O(2^n\vert\Sigma\vert)$，因为对于一个状态 $p_1,p_2,\dots,p_n$ 这 $n$ 个位置中在 $n$ 个串中的字符都是一样的，而对于同一种字符，最多只会有 $2^n$ 种状态，所以遍历到的状态数就只有 $O(2^n\vert\Sigma\vert)$，再乘上转移的时间复杂度 $O(n\vert\Sigma\vert)$，总时间复杂度就为 $O(2^n\times n\vert\Sigma\vert^2)$，可以通过。

# Code
```c++
//when you use vector or deque,pay attention to the size of it.
//by OldDirverTree
#include<bits/stdc++.h>
//#include<atcoder/all>
#define P pair<int,int>
#define int long long
#define mid (l+r>>1)
using namespace std;
//using namespace atcoder;
const int N=10,M=105,V=52;
map<vector<int>,P> f;
int T,n,nxt[N][M][V];
string s[N][M];

int read() {
	int x=0; bool f=true; char c=0;
	while (!isdigit(c) ) f&=(c!='-'),c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return f?x:-x;
}
int solve(vector<int> p)
{
	if (f.find(p)!=f.end() ) return f[p].first;
	f[p].second=-1;
	for (int i=0;i<52;i++)
	{
		vector<int> q;
		for (int j=0;j<n;j++) if (nxt[j][p[j] ][i])
		q.push_back(nxt[j][p[j] ][i]); else break;
		if (q.size()==n) {
			int res=solve(q)+1; if (res>f[p].first)
			f[p].first=res,f[p].second=i;
		}
	}
	return f[p].first;
}
main()
{
	cin.tie(0),cin>>T;
	while (T--)
	{
		cin>>n; vector<int> S;
		auto qwq=[](char c)->int { return islower(c)?c-'a':c-'A'+26; };
		auto qaq=[](int x)->int { return x<26?x+'a':x-26+'A'; };
		for (int i=0;i<n;i++)
		{
			string s; cin>>s,S.push_back(0);
			for (int j=0;j<52;j++) nxt[i][s.size()][j]=0;
			for (int j=s.size()-1;~j;j--) {
				for (int k=0;k<52;k++)
				nxt[i][j][k]=nxt[i][j+1][k];
				nxt[i][j][qwq(s[j])]=j+1;
			}
		}
		printf("%lld\n",solve(S) );
		while (~f[S].second) {
			int c=f[S].second; putchar(qaq(c) );
			for (int i=0;i<n;i++) S[i]=nxt[i][S[i] ][c];
		}
		putchar('\n'),f.clear();
	}
	return 0;
}
```

---

## 作者：pengyule (赞：0)

> 给你 $n$ 个由大小写字母构成的字符串，求它们的最长公共子序列。输出长度及字符串（任意一个）。
>
> - $n\le 10$
> - 在每个字符串中，每个字符至多出现 2 次

【***Intuition***】

一个字符串为最长公共子序列：

![image57e78660a99589b5.png](https://z4请更换图床a.net/images/2022/02/07/image57e78660a99589b5.png)

如果我们现在的对象是 `t1` 那么就可以通过 `t2` 来转移。

所以可以 dp。设一个表示分别从 `s1,s2,…,sn` 的 `p1,p2,…,pn` 位置起头（`s1[p1]=s2[p2]=…=sn[pn]`）能够跳的 LCS。

【***Solution***】

由于各串每个字符至多出现 2 次，可以将它们依次标记为 0,1。如果少于 2 次就不用标全。

枚举 $t$ 当前字符 $i$，用一个 bitmask $j$ 表示 $s_p(1\le p\le n)$ 各自选的是 $i$ 的几号位置。

设 $f_{i,j}$ 表示上述情况下，从各自的位置开始的 LCS（长度）。用 `(string)` $g_{i,j}$ 顺带记录字符串。

枚举 $i$ 后面的 $t$ 的字符 $k$。显然有 $f_{i,j}=\max (1+f_{k,N[i][j][k]})$。其中 $N[i][j][k]$ 表示对于每个状态 $(i,j)$ 中的位置，往后找第一个 $k$ 出现的位置，这些位置的号码构成的新状态 $(k,N[i][j][k])$。

注意边界；预处理 $N[i][j][k]$。

时间复杂度 $O(52\cdot 2^n\cdot 52\cdot n)$。后面的 $\cdot n$ 为预处理中产生，可以通过枚举子集省去，但不省去也可通过，如下；空间复杂度 $O(52\cdot 2^n\cdot 52)$。

【[***Submission***](https://codeforces.ml/problemset/submission/1584/145510805)】



---

