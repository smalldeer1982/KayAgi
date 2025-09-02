# Repeat Strings

## 题目描述

给定一个由字符 `a` 和 `b` 组成的字符串 $S$，你可以依次进行若干次以下操作：

- 从字符串 $S$ 中选择一个连续的区间 $[l, r]$。对于该区间内满足 $l \leq k \leq r$ 的每个位置 $k$，如果 $S_k$ 是 `a`，就将其变为 `b`；如果 $S_k$ 是 `b`，就将其变为 `a`。

接下来，有 $Q$ 个字符串 $T_i$，每个也是由 `a` 和 `b` 构成。将每个 $T_i$ 重复 $10^{100}$ 次，截取长度为 $|S| + 1$ 的前缀，得到一个新的字符串 $T'_i$。

你的任务是，对于每一个字符串 $T'_i$，计算将字符串 $S$ 变为 $T'_i$ 最少需要多少次操作。

## 样例 #1

### 输入

```
babaabbabab
4
abab
b
babaabba
aaaaaaaaaaab```

### 输出

```
2
4
0
5```

# 题解

## 作者：Masterwei (赞：6)

没有思维，只有套路。

题意：就是再说最开始给你一个 $AB$ 串 $S$，然后有 $Q$ 个询问，每次询问给你一个串 $T$，你需要将 $T$ 循环多次，得到长度和 $S$ 一样的串 $T'$（循环多的部分删掉），你可以对 $T'$ 进行区间取反，问你最少的操作次数使得 $T'$ 等于 $S$。

首先将 $S$ 转化为 $01$ 的形式，考虑差分，我们设 $a_i=S_{i-1}\oplus S_i$，$b_i=T'_{i-1}\oplus T'_i$，那么你就会发现区间取反操作变成了修改任意两个不同端点的值，如果我们设 $cnt$ 表示 $a$ 和 $b$ 中位置一致值不同的个数，那么最小操作次数即为 $\left \lceil \frac{cnt}{2} \right \rceil$。读者自证不难。

然后发现我们只用对于 $T$ 中每个位置，算出循环中它出现的位置在 $S$ 有几个不同。

考虑根号分治，设 $B=\sqrt{2\times 10^5}$，如果 $|T|<B$，那么我们预处理一个数组 $f_{i,j}$，表示在位置 $i$，跳的间距是 $j$，对应 $S$ 中 $1$ 的个数，$g$ 同理，为 $0$ 的个数。

如果 $|T|\ge B$，那么我们直接暴力跳就可以了。

注意差分时有一些细节要分讨，比如说 $T$ 在循环中首尾也要差分。


```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=2e5+5;
int n,q;
int a[2][Maxn];
char s[Maxn],t[Maxn];
int f[2][Maxn][305];
int g[2][Maxn][305];
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)a[0][i]=(s[i-1]=='a')^(s[i]=='a');//,printf("a[%d]=%d\n",i,a[0][i]);
	for(int i=n;i;i--){
		for(int j=1;j<=300;j++){
			f[0][i][j]=f[0][min(n+1,i+j)][j]+a[0][i];
			g[0][i][j]=g[0][min(n+1,i+j)][j]+(a[0][i]^1);
		}
	}
	s[0]='a';
	for(int i=1;i<=n;i++)a[1][i]=(s[i-1]=='a')^(s[i]=='a');
	for(int i=n;i;i--){
		for(int j=1;j<=300;j++){
			f[1][i][j]=f[1][min(n+1,i+j)][j]+a[1][i];
			g[1][i][j]=g[1][min(n+1,i+j)][j]+(a[1][i]^1);
		}
	}
	q=read();
	while(q--){
		scanf("%s",t+1);
		int len=strlen(t+1),op=(t[len]=='a');
		if(len<=300){
			 int cnt=0;
			 t[0]=t[len];
			 for(int i=1;i<=len;i++){
			 	int val=((t[i]=='a')^(t[i-1]=='a'));
//			 	printf("%d %d %d\n",i,val,g[op][i][len]);
			 	if(!val)cnt+=f[op][i][len];
			 	else cnt+=g[op][i][len];
			 }
//			 printf("%d\n",cnt);
			 printf("%d\n",(cnt+1)/2);
		}else{
			int cnt=0;
			t[0]=t[len];
			for(int i=1;i<=len;i++){
				int val=((t[i]=='a')^(t[i-1]=='a'));
				for(int j=i;j<=n;j+=len)cnt+=(val!=a[op][j]);
			}printf("%d\n",(cnt+1)/2);
		}
	}
	return 0;
}
/*
babaabbabab
1
abab
*/
```

---

## 作者：sunkuangzheng (赞：2)

$\textbf{AT\_qupc2018\_j}$

> - 有 $\texttt{01}$ 串 $a$ 和 $q$ 个 $\texttt{01}$ 串 $b_i$，对于每个 $b_i$，将其拼接 $10^{114154}$ 次后取前 $|a|$ 个字符。然后你可以进行任意次以下操作：
>   - 选择一个区间 $[l,r]$ 并把 $b_{l\ldots r}$ 区间 $\operatorname{XOR} 1$。
> - 问最少几次操作能把 $b_i$ 变成 $a$。
> - $1 \le q,|a|,\sum |b_i| \le 2 \cdot 10^5$。

令 $n = |a|$，首先考虑 $\mathcal O(nq)$ 做法。暴力拼接 $b_i$ 后求出 $a,b$ 的差分数组 $a',b'$，区间异或相当于在差分数组上对两个点单点异或。我们求出 $a',b'$ 数组不同的数量 $ct$，则答案是 $\lceil \dfrac{ct}{2} \rceil$。

考虑 bitset 优化，拼接过程可以倍增然后或上自己的左移做到 $\mathcal O(\dfrac{|t_i| \log n}{w})$，匹配时求出 $a' \oplus b'$ 里 $1$ 的个数即可。时间复杂度 $\mathcal O(\dfrac{nq \log n}{w})$，还是无法通过。

注意到本质不同的询问数量远达不到 $2 \cdot 10^5$，可以计算出本质不同的询问数量不超过 $2 \cdot 10^4$。记忆化即可。

---

## 作者：Miss_SGT (赞：1)

区间取反想到差分转成单点修改两次，然后答案就是不同位置数除以二向上取整，注意考虑边界。

因为有 $\sum |T| \le 2 \times 10^5$,所以考虑根号分治，设一个阈值 $B$。当 $|T| > B$ 时，这样的串只有 $\frac{n}{B}$ 个，直接暴力做是 $O(\frac{n^2}{B})$ 的。当小于 $B$ 时，我们可以预处理对于每个长度每一位 01 的个数，这部分 $O(nB)$，询问时随便算，然后就完了。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,M=300;
int n,q,m,cnt[M+1][M+1];
char s[N],t[N];
int main(){
	n=readstr(s)-s;
	for(int i=0;i<n;++i) s[i]-='a';
	for(int i=n-1;i;--i) s[i]^=s[i-1];
	for(int i=0;i<n;++i)if(!s[i])
		for(int j=1;j<=M;++j) ++cnt[j][i%j];
	read(q);
	while(q--){
		m=readstr(t)-t;
		for(int i=0;i<m;++i) t[i]-='a';
		int lst=t[m-1];
		for(int i=m-1;i;--i) t[i]^=t[i-1];
		t[0]^=lst;
		int ans=0;
		if(m<=M){
			for(int i=0;i<m;++i)
				ans+=(t[i]==0?(n/m+(n%m>=i+1))-cnt[m][i]:cnt[m][i]);
		}else{
			for(int i=0,j=0;i<n;++i,(++j==m)&&(j=0))
				ans+=(s[i]!=t[j]);
		}
		if(lst) ans+=(t[0]==s[0]?1:-1);
		print((ans+1)/2),pc('\n');
	}
	return 0;
}
```

---

