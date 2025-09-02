# Balanced Bitstring

## 题目描述

A bitstring is a string consisting only of the characters 0 and 1. A bitstring is called $ k $ -balanced if every substring of size $ k $ of this bitstring has an equal amount of 0 and 1 characters ( $ \frac{k}{2} $ of each).

You are given an integer $ k $ and a string $ s $ which is composed only of characters 0, 1, and ?. You need to determine whether you can make a $ k $ -balanced bitstring by replacing every ? characters in $ s $ with either 0 or 1.

A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

## 说明/提示

For the first test case, the string is already a $ 4 $ -balanced bitstring.

For the second test case, the string can be transformed into 101.

For the fourth test case, the string can be transformed into 0110.

For the fifth test case, the string can be transformed into 1100110.

## 样例 #1

### 输入

```
9
6 4
100110
3 2
1?1
3 2
1?0
4 4
????
7 4
1?0??1?
10 10
11??11??11
4 2
1??1
4 4
?0?0
6 2
????00```

### 输出

```
YES
YES
NO
YES
YES
NO
NO
YES
NO```

# 题解

## 作者：DPair (赞：6)

一道真正的水题，考场上居然没看出来还想了 $30$ 多分钟......

## 【题意】
给你一个字符串和一个数 $k(k\in\{k|k=2t,t\in Z\})$ ， 字符串中所有的 $?$ 都可以替换成 $0,1$ 中的一个，问能否使得这个串中的每一个 $k$ 长子串中 $0,1$ 数量相同。

## 【思路】
有一个很显然（~~但我这个蒟蒻看了半个多小时才看出来~~）的性质：

对于一个符合题意的长度为 $n$ 的字符串 $a$ ,应该要有：

$$
a[i]=a[i+k]=a[i+2k]=\dots=a[i+pk](\forall i\in[1,k],i+pk\leq n)
$$

这是显然的，因为若 $a$ 符合题意，有：
$$
a[i]+a[i+1]+\dots+a[i+k-1]=\frac{k}{2}
$$
$$
a[i+1]+a[i+1]+\dots+a[i+k]=\frac{k}{2}
$$

两式作差得：

$$
a[i]=a[i+k]
$$

那么如果不能满足这个性质，就可以再见了。

有了这个性质还不够，还需要保证：
$$
a[i]+a[i+1]+\dots+a[i+k-1]=\frac{k}{2}
$$
首先，由于要满足上面那个性质，所有 **模k后余数相同的位置上的字符** 都应该相同，并且可以确定是哪一个数字（或者是 $?$）。

那么只要使得这一些字符之和为 $\frac{k}{2}$ 就行了。

考虑记录这些字符中有 $cnt$ 个 $?$ ，$num$ 个 $1$ 。

那么最终 $1$ 个数的取值范围就是 $[num,num+cnt]$ ，判断 $\frac k2$ 在不在这个范围内即可。

## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k;
int c[300005];
char s[300005];
int main(){
	int t;scanf("%d", &t);
	while(t --){
		scanf("%d%d", &n, &k);
		for (register int i = 0;i < k;i ++) c[i] = -1;//-1表示不确定
		scanf("%s", s + 1);
		bool ck = 1;
		for (register int i = 1;i <= n;i ++){
			if(s[i] == '1'){
				if(c[i % k] == 0){
					ck = 0;
					break;
				}
				c[i % k] = 1;
			}
			if(s[i] == '0'){
				if(c[i % k] == 1){
					ck = 0;
					break;
				}
				c[i % k] = 0;
			}
		}
		int cnt = 0, num = 0;
		if(!ck) {printf("NO\n");continue;}
		for (register int i = 0;i < k;i ++){
			if(~c[i]) num += c[i];
			else cnt ++;
		}
		if(num > (k >> 1)){
			printf("NO\n");
			continue;
		}
		if(num + cnt >= (k >> 1)){
			printf("YES\n");
		}
		else printf("NO\n");
	}
}
```

---

## 作者：tommymio (赞：2)

发现移动一次区间，即从 $[i-k,i-1]$ 到 $[i-k+1,i]$，这两个区间共用了 $[i-k+1,i-1]$，于是可以得到 $s_{i-k}=s_i$。一般化的表示，$\forall i\in[1,n],s_i=s_{i\bmod k}$。

转化为 $k$ 个等价系，每个等价系内 $s_i$ 值相等。尝试给每个等价系赋一个值。只需要考虑 $k$ 个等价系的值是否合法，并且判断等价系内部是否存在冲突即可。正确性基于每个等价系内的 $s_i$ 都是相同的，时间复杂度为 $O(n)$。

```cpp
#include<cstdio>
char s[300005];
int t[300005];
int main() {
	int T;
	scanf("%d",&T);
	while(T--) {
		int n,k,flag=1;
		scanf("%d%d%s",&n,&k,s+1);
		for(register int i=1;i<=k;++i) t[i]=-1;
		for(register int i=1;i<=n;++i) {
			int x=(i-1)%k+1;
			if(s[i]=='?') {continue;}
			if(t[x]!=-1&&s[i]-'0'!=t[x]) {flag=0;break;}
			if(t[x]==-1) {t[x]=s[i]-'0';}
		}
		int cnt0=0,cnt1=0;
		for(register int i=1;i<=k;++i) {if(t[i]!=-1) s[i]=t[i]+'0'; cnt0+=(s[i]-'0'==0);cnt1+=(s[i]-'0'==1);}
		if(cnt0<=k/2&&cnt1<=k/2&&flag) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：引领天下 (赞：2)

首先，对于一个合理的 $s$ ，一定有 $s_i=s_{i+k}$（因为 $\left[i,i+k-1\right],\left[i+1,i+k\right]$ 共用了 $\left[i+1,i+k-1\right]$）。

所以所有的 $s_i,s_{i+k},s_{i+2k}\dots$ 都相等。

于是我们可以根据这个性质确定 $s_i$ 可能的取值。

确定了 $s_i$ 可能的取值之后，我们就可以统计一下 $[1,k]$ 中有多少个 $0$，多少个 $1$，如果都 $\le \frac{k}{2}$ 则是合法的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
string s,s1;
int main(){
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--){
        bool ok=1;
        cin>>n>>k>>s1;s=" "+s1;
        for(register int i=1;i<=k&&ok;i++){
            int z=s[i]=='?'?-1:s[i]-'0';
            for(register int j=1;j*k+i<=n&&ok;j++)if(z==-1)z=s[j*k+i]=='?'?-1:s[j*k+i]-'0';
            else if(s[j*k+i]!='?'&&s[j*k+i]-'0'!=z)ok=0;//出现矛盾
            s[i]=z==-1?'?':z+'0';//记下可能的取值
        }
        if(!ok){puts("NO");continue;}
        register int cnt1=0,cnt2=0;
        for(register int i=1;i<=k;i++)if(s[i]=='0')cnt1++;else if(s[i]=='1') cnt2++;
        if(cnt1>(k>>1)||cnt2>(k>>1))ok=0;//合理
        puts(ok?"YES":"NO");
    }
    return 0;
}
```

---

## 作者：Licykoc (赞：0)

# 题意：

给定一个包含 $1,\ 2,\ ?$ 的字符串，$?$ 处字符可以为 $1,\ 2$  求问该字符串所有长度为 $m$ **连续子串**是否都满足 `包含的0和1数目相等` 。

# $\mathcal{Sol:}$

我们先不考虑有带 $?$ 的情况。

题意中说：`包含的0和1数目相等` 其实可以看作每一个 **子串的和** 相等。怎么样？这个问题是不是有点眼熟？

没错，在小学奥数题中就有类似问题，而做法也很简单：


设字符串长度为 $n$ ，则将其划分为  $\left\lfloor\dfrac{n}{m}\right\rfloor\ \ $段加上 $n \mod m$ 个单独的字符。每一段中数字都**完全相同**，即数值与次序都相等。

好了再回到本题，由以上延伸可得在字符串中的第 $i$ 位必定与 $i+m$ 位相同。

这样的话我们就可以构造出一个序列，并在没有 $?$ 的情况下可以在 $\mathcal{O(n)}$ 的复杂度下解决问题。

那么现在我们来分析有 $?$ 的情况：

其实也很简单，因为在构造序列时我们会遇到三种情况：

1. 第 $i$ 位 与 第 $i+m$ 位都为数字。直接判断即可。

2. 第 $i$ 位 与 第 $i+m$ 位一位为数字，一位为 $?$  。根据条件，将 $?$ 直接转换为另外那个数字即可。

3. 第 $i$ 位 与 第 $i+m$ 位都为 $?$ ，无法直接得出答案。

考虑如何解决第三种情况：蒟蒻在这里也卡了很久，还是在参考了第一篇题解搞懂得Orz。

我们稍微转化一下，即可得到以下等式：

$$st[i] + st[i+1] + ... + st[i+m-1] = \frac{m}{2}$$

(`st`数组为原字符串)

这下问题就简单了，我们可以统计在 $st_{i...i+m-1}$ 中 $?$ 的个数，与 $\sum\limits_{k=i}^{i+m-1} st[k]$ 相判断：

1. 如果$(\sum\limits_{k=i}^{i+m-1} st[k]) \times 2 > m$ 结果肯定为 `NO` 。

2. **如果$(\sum\limits_{k=i}^{i+m-1} st[k]) \times 2 < m - ?$ 的个数，表示如果所有的 $?$ 即使都转化为 $1$ 也无济于事，输出 `NO` 。**

3. 以上都不满足的话输出 `YES` 。

至此，本题结束。

# $Code:$
```cpp11
//Code by Licykoc  2021.1.12
#include <bits/stdc++.h>
using namespace std;
const int MAXN=3e5+10;
int T,n,m;
char st[MAXN];
int now[MAXN];
int main () {
	scanf("%d",&T);
	while (T--) {
		int flag(0),s1(0),s2(0); //flag为构造是否成功标记
		scanf("%d%d%s",&n,&m,st+1);
		for (int i=1;i<=m;++i) now[i]=-1;
		for (int i=1;i<=m;++i) {
			for (int j=i;j<=n;j+=m) {
				if (st[j]=='0') {
					if (now[i]==1) {flag=1; break;}
					now[i]=0;
				}
				if (st[j]=='1') {
					if (now[i]==0) {flag=1; break;}
					now[i]=1;
				}
			}
			if (flag) break;
		}
		if (flag) {puts("NO"); continue;}
      //如果连构造都无法满足，直接输出NO
		for (int i=1;i<=m;++i) s1+=(now[i]==1),s2+=(now[i]==-1);
		if (s1*2>m) {puts("NO"); continue;}
		if ((s1+s2)*2<m) {puts("NO"); continue;}
		puts("YES");
	}
   return 0;
}
```

---

## 作者：钓鱼王子 (赞：0)

首先我们先考虑满足所有区间和相等，也就是说，$a_i=a_{i-n}$，没有限制的标为 $?$ 即可，最后判断一下是否可以满足 $1$ 和 $0$ 相等即可，即 $1$ 与 $0$ 的绝对值之差不超过 $?$ 的个数。

```
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t; 
}
int t,n,m,a[1000002],ia,b[1000002];
char s[1000002];
int main(){
	t=read();
	while(t--){
		n=read(),m=read();
		scanf("%s",s+1);ia=0;
		for(re int i=m+1;i<=n;++i){
			if(s[i]=='?')s[i]=s[i-m];
			if(s[i-m]=='?'||s[i]==s[i-m])continue;
			ia=1;break;
		}
		for(re int i=1;i<=n;++i)a[i]=a[i-1]+(s[i]=='1'?1:(s[i]=='0'?-1:0))-(s[i>=m?i-m:0]=='1'?1:(s[i>=m?i-m:0]=='0'?-1:0)),b[i]=b[i-1]+(s[i]=='?')-(s[i>=m?i-m:0]=='?');
		for(re int i=m;i<=n;++i)if(abs(a[i])>b[i])ia=1;
		puts(ia?"NO":"YES");
	}
}
```


---

## 作者：SSerxhs (赞：0)

$\sum\limits_{i=j}^{j+k-1}s_i=\frac{k}{2}=\sum\limits_{i=j+1}^{j+k}s_i$

可证 $s_j=s_{j+k}$

只要保证这一点成立，就只需考虑 $s_1$ 到 $s_k$ 成立即可

所以判断 $s_1$ 到 $s_k$ 中 $0$ 和 $1$ 的数量是否不满足即可

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3e5+2;
int a[N];
int n,c,fh,i,t,x,m;
inline void read(int &x)
{
	c=getchar();fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
int main()
{
	read(t);
	while (t--)
	{
		read(n);read(m);
		while (((c<48)||(c>49))&&(c!='?')) c=getchar();
		a[1]=c;x=0;
		for (i=2;i<=n;i++) a[i]=getchar();
		for (i=1;i<=n-m;i++) if (a[i]!='?')
		{
			if (a[i+m]==(a[i]^1)) {puts("NO");x=1;break;} else a[i+m]=a[i];
		}
		if (x) continue;
		for (i=n;i>m;i--) if (a[i]!='?')
		{
			if (a[i-m]==(a[i]^1)) {puts("NO");x=1;break;} else a[i-m]=a[i];
		}
		if (x) continue;n=0;
		for (i=1;i<=m;i++) if (a[i]==48) ++n; else if (a[i]==49) ++x;
		m>>=1;if ((x>m)||(n>m)) puts("NO"); else puts("YES");
	}
}
```

---

