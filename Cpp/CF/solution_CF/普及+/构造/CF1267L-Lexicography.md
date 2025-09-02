# Lexicography

## 题目描述

Lucy likes letters. She studied the definition of the lexicographical order at school and plays with it.

At first, she tried to construct the lexicographically smallest word out of given letters. It was so easy! Then she tried to build multiple words and minimize one of them. This was much harder!

Formally, Lucy wants to make $ n $ words of length $ l $ each out of the given $ n \cdot l $ letters, so that the $ k $ -th of them in the lexicographic order is lexicographically as small as possible.

## 样例 #1

### 输入

```
3 2 2
abcdef
```

### 输出

```
af
bc
ed```

## 样例 #2

### 输入

```
2 3 1
abcabc
```

### 输出

```
aab
bcc
```

# 题解

## 作者：灵茶山艾府 (赞：9)

### 提示 1

假设输入的是 $\texttt{aaabbcccc}$，$k=3$。

按照

$$
\begin{aligned}
&\texttt{aaa}\\
&\texttt{bbc}\\
&\texttt{ccc}
\end{aligned}
$$

去构造，不如按照

$$
\begin{aligned}
&\texttt{abc}\\
&\texttt{abc}\\
&\texttt{acc}
\end{aligned}
$$

去构造。

也就是说，尽量「均匀地」分配字母，会让第 $k$ 个字符串的字典序尽量小。所以竖着填字母更合理。

### 提示 2

假设输入的是 $\texttt{aaabccdef}$，$k=3$。

按照

$$
\begin{aligned}
&\texttt{abd}\\
&\texttt{ace}\\
&\texttt{acf}
\end{aligned}
$$

去构造，不如按照

$$
\begin{aligned}
&\texttt{abf}\\
&\texttt{acd}\\
&\texttt{ace}
\end{aligned}
$$

去构造。

当某一列填的字母不一样时，对于字典序小的字符串，后面可以暂时不填（留到最后再填），即

$$
\begin{aligned}
&\texttt{ab\_}\\
&\texttt{acd}\\
&\texttt{ace}
\end{aligned}
$$

对于第三列，先从第二个字符串开始竖着填。

所以在竖着填的时候，额外维护这一列从哪个字符串开始填（代码中的 $i_0$）。

```go
package main
import("bufio";."fmt";"os";"sort")

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, m, k, p, i0 int
	var s []byte
	Fscan(in, &n, &m, &k, &s)
	sort.Slice(s, func(i, j int) bool { return s[i] < s[j] })

	ans := make([][]byte, n)
	for i := range ans {
		ans[i] = make([]byte, m)
	}
	for j := 0; j < m; j++ {
		for i := i0; i < k; i++ { // 第 j 列从第 i0 行开始填
			ans[i][j] = s[p]
			if i > i0 && s[p] != s[p-1] {
				i0 = i
			}
			p++
		}
	}

	for _, t := range ans {
		for j, b := range t {
			if b == 0 { // 剩余没填的字母
				t[j] = s[p]
				p++
			}
		}
		Printf("%s\n", t)
	}
}
```

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)


---

## 作者：yuzhechuan (赞：1)

需要一点点思维的基础构造题

---

### 题解：

首先贪心并且显然的，字符是要从小到大确定各自位置的

其次，在确定单词时我们只需要可以确定前k个，其余的不用管，且要在合法的前提下，使得串k的各位最小

考虑字典序，发现只要高位小就可以无视低位是啥，因此我们可以在确定前面的串一定会小于k后就将它们“无视”掉，从而将原本应该分配给他们的较小字符分给k，而“无视掉”的串的低位由于对k没有影响（反正高位已经小于了），就可以按顺序插较大字符了

因此对于从高到低的每一位都是从k-1到1，倒着扫一遍哪些是“有可能”大于等于k的，刻意插小字符就好了（另外，显然的，这个“有可能”的区间一定是连贯的呢）

---

照着数据手玩几组应该就可以很快搞懂下面的代码：

---

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}
template<class t> inline void write(t x){
	if(x<0) putchar('-'),write(-x);
	else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int N=1005;
char s[N*N],ans[N][N];
int n,l,k,use;

signed main(){
	read(n);read(l);read(k);;
	scanf("%s",s+1);
	sort(s+1,s+1+n*l); //贪心的排个序
	for(int i=1;i<=l;i++){
		int pos=k; //区间[pos,k-1]都是有可能大于等于k的串，因此要特意插小字符把他们扼杀掉
		while(pos>=2&&ans[pos-1][i-1]==ans[k][i-1]) pos--;
		for(int j=pos;j<=k;j++) ans[j][i]=s[++use]; //按顺序插小字符
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=l;j++) if(ans[i][j]=='\0') //这个位置上没有字符
			ans[i][j]=s[++use];
	for(int i=1;i<=n;i++) printf("%s\n",ans[i]+1);
}
```

---

## 作者：gyh20 (赞：1)

贪心，尽量把大的留给第k个，假设当前枚举到第i个，则只需要将字符从小到大排列在前i-1个都与第k个相同且位置小于k的，可以证明这样是最优的。输出时如果当前位置有字符则输出该字符，否则输出未使用字符最小的一个。

代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#define in inline
#define re register
using namespace std;
in int read() {
	re int t=0;
	re char v=getchar();	
	while(v<'0'||v>'9'){
	v=getchar();
	}	
	while(v>='0'&&v<='9'){		
	t=(t<<3)+(t<<1)+(v^48);		
	v=getchar();	}
	return t;
}
char ans[1002][1002],s[1000002];
int n,l,k,cnt[2006],fst[2006],tot;
inline void work(re int x,re int a){
	if(x>l)return;
	memset(fst,0,sizeof(fst));
	for(re int i=a;i<=k;++i){
		ans[i][x]=s[tot++];
		if(!fst[s[tot-1]])fst[s[tot-1]]=i;
	}
	work(x+1,fst[ans[k][x]]);
}
int main(){
	scanf("%d %d %d",&n,&l,&k);	scanf("%s",s);
	sort(s,s+n*l);
	work(1,1);
	for(re int i=1;i<=n;++i){
		for(re int j=1;j<=l;++j){
			if(ans[i][j])putchar(ans[i][j]);
			else putchar(s[tot++]);
		}
		putchar('\n');
	}
}
```


---

## 作者：Cry_For_theMoon (赞：0)

[传送门](https://codeforces.com/contest/1267/problem/L)

##### 题意：

给定 $n \times l$ 个小写字母（可能重复），将所有字母恰好用一次，构造出 $n$ 个长度为 $l$ 的字符串，使得按字典序排列后，第 $k$ 个字符串的字典序尽可能小。输出这 $n$ 个串，如果有多种构造方案，输出任意一种。

Data range：$1 \le n,l \le 1000,k \le n$.

##### 分析：

字典序的话直接莽从前往后贪心构造即可。

一个很 naive 的思路是，我们一位一位决策。用一个桶维护当前可用的字符数量。注意到 $s_{k+1 \sim n}$ 是无关紧要的，永远填当前最大的字符。（但是要注意这部分从后往前枚举 $s_i$ 填字符，这样才能保证 $s_i\le s_{i+1}$）我们只需要考虑满足 $s_1\le s_2\le...\le s_k$ 这个约束。容易想到从小往大枚举 $s_k$ 中当前这一位能否为字符 $c$ 。

容易想到这样的判断方法，如果 $bucket[c] \ge k$ 那么一定可以，否则我们把当前未定的最前面的 $bucket[c]$ 个字符串填上字符 $c$.

但是这是有问题的，考虑字典序的定义，发现两个字符串的字典序大小是由第一个不同的位决定的。也就是说可能 $s_1$ 在之前的某一位就已经小于 $s_k$ 了，那么当前这一位就不一定需要小于等于 $s_k$.

容易发现这样的字符串一定位于最开头，构成连续一段。即不可能有 $s_i$ 满足这个条件而 $s_{i-1}$ 不满足 $(i<k)$。所以假设当前 $s_{1\sim L}(L<k)$ 都是前面已经小于 $s_k$ 的串，此时就可以把它们归入到 $s_{k+1 \sim n}$ 中一起构造。而枚举 $c$ 的过程中，如果 $bucket[c]$ 不够让 $s_{L+1\sim k}$ 都填上，我们就让 $s_{L+1 \sim L+bucket[c]-1}$ 填上 $c$ 并且令 $L \leftarrow L+bucket[c]$ 即可。

~~这里有个把bucket用char存的爆零人~~

```C++
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=1010,MAXM=1e6+10;
int n,k,l,bucket[26];
char s,ret[MAXN][MAXN];
int main(){
	cin>>n>>l>>k;
	rep(i,1,n*l){
		cin>>s;
		bucket[s-'a']++;
	}
	int L=0;
	rep(i,1,l){
		per(x,n,1){if(x>L && x<=k)continue;
			per(j,25,0){
				if(bucket[j]){
					ret[x][i]='a'+j;
					bucket[j]--;
					break;
				}
			}
		}
		rep(j,0,25){
			if(bucket[j]>=k-L){
				rep(x,L+1,k){
					ret[x][i]='a'+j;
				}
				bucket[j]-=(k-L);
				break;
			}else{
				rep(x,L+1,L+bucket[j]){
					ret[x][i]='a'+j;
				}
				L+=bucket[j];
				bucket[j]=0;
			}
		}
	}
	rep(i,1,n){
		printf("%s\n",ret[i]+1);
	}
	return 0;
}
```

 

---

