# Rings

## 题目描述

Frodo was caught by Saruman. He tore a pouch from Frodo's neck, shook out its contents —there was a pile of different rings: gold and silver..."How am I to tell which is the One?!" the mage howled.

"Throw them one by one into the Cracks of Doom and watch when Mordor falls!"





Somewhere in a parallel Middle-earth, when Saruman caught Frodo, he only found $ n $ rings. And the $ i $ -th ring was either gold or silver. For convenience Saruman wrote down a binary string $ s $ of $ n $ characters, where the $ i $ -th character was 0 if the $ i $ -th ring was gold, and 1 if it was silver.

Saruman has a magic function $ f $ , which takes a binary string and returns a number obtained by converting the string into a binary number and then converting the binary number into a decimal number. For example, $ f(001010) = 10, f(111) = 7, f(11011101) = 221 $ .

Saruman, however, thinks that the order of the rings plays some important role. He wants to find $ 2 $ pairs of integers $ (l_1, r_1), (l_2, r_2) $ , such that:

- $ 1 \le l_1 \le n $ , $ 1 \le r_1 \le n $ , $ r_1-l_1+1\ge \lfloor \frac{n}{2} \rfloor $
- $ 1 \le l_2 \le n $ , $ 1 \le r_2 \le n $ , $ r_2-l_2+1\ge \lfloor \frac{n}{2} \rfloor $
- Pairs $ (l_1, r_1) $ and $ (l_2, r_2) $ are distinct. That is, at least one of $ l_1 \neq l_2 $ and $ r_1 \neq r_2 $ must hold.
- Let $ t $ be the substring $ s[l_1:r_1] $ of $ s $ , and $ w $ be the substring $ s[l_2:r_2] $ of $ s $ . Then there exists non-negative integer $ k $ , such that $ f(t) = f(w) \cdot k $ .

Here substring $ s[l:r] $ denotes $ s_ls_{l+1}\ldots s_{r-1}s_r $ , and $ \lfloor x \rfloor $ denotes rounding the number down to the nearest integer.

Help Saruman solve this problem! It is guaranteed that under the constraints of the problem at least one solution exists.

## 说明/提示

In the first testcase $ f(t) = f(1111) = 15 $ , $ f(w) = f(101) = 5 $ .

In the second testcase $ f(t) = f(111000111) = 455 $ , $ f(w) = f(000111) = 7 $ .

In the third testcase $ f(t) = f(0000) = 0 $ , $ f(w) = f(1000) = 8 $ .

In the fourth testcase $ f(t) = f(11011) = 27 $ , $ f(w) = f(011) = 3 $ .

In the fifth testcase $ f(t) = f(001111) = 15 $ , $ f(w) = f(011) = 3 $ .

## 样例 #1

### 输入

```
7
6
101111
9
111000111
8
10000000
5
11011
6
001111
3
101
30
100000000000000100000000000000```

### 输出

```
3 6 1 3
1 9 4 9
5 8 1 4
1 5 3 5
1 6 2 4
1 2 2 3
1 15 16 30```

# 题解

## 作者：Jairon314 (赞：5)

$ Solution $

----------

诈骗题，千万不要想多了。

注意到任何一个数字的二进制左边或者右边填 $ 0 $ 之后的结果都是原数字的倍数，例如

$ \color{red} (10010)_2 * (2)_{10} = (100100)_2 $

$ \color{red} (10010)_2 = (1001)_2 * (2)_{10} $

（设第一个串为 $ t $ , 第二个串为 $ m $）

于是找到第一个 $ 0 $ 出现的位置就可以解决这个问题了，因为如果它第一个出现的位置 $ pos_0 $ 在前一半，构造 $ t[pos:n] $ ， $ m[pos+1:n] $ ； 否则构造 $ t[1:pos] $ ， $ m[1:pos-1] $即可满足条件

注意如果整个数列都是 $ 1 $ ，构造 $ t $ 为整个数列， $ m $ 为任何一个长度大于等于 $ \lfloor \frac{n}{2} \rfloor $ 的连续的子串即可满足条件

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
 
#define $int long long
 
/***************快读***************/
 
namespace IO {
char buf[1<<21], *p1 = buf, *p2 = buf, buf1[1<<21];
inline char gc () {return p1 == p2 && (p2 = (p1 = buf) + fread (buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;}
 
#ifndef ONLINE_JUDGE
#endif
 
#define gc getchar
 
template<class I>
inline void read(I &x) {
    x = 0; I f = 1; char c = gc();
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = gc(); }
    while(c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = gc(); }
    x *= f;
}
 
template<class I>
inline void write(I x) {
    if(x == 0) {putchar('0'); return;}
    I tmp = x > 0 ? x : -x;
    if(x < 0) putchar('-');
    int cnt = 0;
    while(tmp > 0) {
        buf1[cnt++] = tmp % 10 + '0';
        tmp /= 10;
    }
    while(cnt > 0) putchar(buf1[--cnt]);
}
 
#define in(x) read(x)
#define outn(x) write(x), putchar('\n')
#define out(x) write(x), putchar(' ')
 
} using namespace IO;
 
/***************快读***************/
 
#define maxn 1000010
 
int T,n;
char s[maxn];
int pos_0;
 
int main(){
	read(T);
	while(T--){
		pos_0=-1;
		read(n);
		::cin>>(s+1);
		for(int i=1;i<=n;i++){if(s[i]=='0'){pos_0=i;i=n+1;}}
		if(pos_0==-1){
			out(1),out(2*(n/2)),out(1),outn(n/2);
		} else if(pos_0<=(n/2)){
			out(pos_0),out(n),out(pos_0+1),outn(n);
		} else{
			out(1),out(pos_0),out(1),outn(pos_0-1);
		}
	}
	return 0;
}
```


---

## 作者：Chouquet (赞：5)

由于 $0$ 是任何非 $0$ 整数的倍数，一个数本身也是自己的倍数，所以：

+ 如果该字符串中有大于等于 $\lfloor \frac{n}{2} \rfloor$ 的连续子串全为 $0$，那么另找一个长度大于 $\lfloor \frac{n}{2} \rfloor$ 的连续子串即可。

+ 如果该字符串中有两个长度大于等于 $\lfloor \frac{n}{2} \rfloor$ 的连续子串，或者是有一个长度大于等于 $\frac{n}{2}$ 的连续子串且该字串前面一位或数位为 $0$，那么也是一组解。

+ 如果一个字符串有一个长度大于等于 $\lfloor \frac{n}{2} \rfloor$ 的连续子串，它的后面一位或数位为 $0$，说明包括后面的 $0$ 的子串一定是该子串的 $2$ 倍，是一组解。

+ 否则说明该字符串全为 $1$，符合上面的第二种情况。事实上，上面第一种情况也可以归到第二、三两种情况里。

所以本题一定有解。

代码：

```cpp
#include <cstdio>
int t, n;
char s[20003];
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%s", &n, s + 1);
        bool ok = 0;//0表示符合情况4
        for (int i = 1; i <= n; i++)
            if (s[i] == '0'){
                ok = 1;
                if (i > (n >> 1))//此时[1,i-1]长度大于等于[n/2]
                    printf("1 %d 1 %d\n", i, i - 1);
                else//否则[i+1,n]长度大于等于[n/2]
                    printf("%d %d %d %d\n", i, n, i + 1, n);
                break;
            }
        if (!ok)//此时两个子串[1,n-1],[2,n]长度相同，且数值一样
            printf("1 %d 2 %d\n", n - 1, n);
    }
    return 0;
}
```

---

## 作者：FoXreign (赞：1)

## 题意
给你一个长为 $n$ 的二进制字符串，你可以从中截取不同区间且长度均 $ \geq \lfloor \frac{n}{2} \rfloor$ 的两段，但要保证这两段子串转换为十进制后成倍数关系，问应该截取哪两段？

## 题目分析
根据序列是否为非零序列，可以分为以下两种情况：

- 若序列中大于 $\frac{n}{2}$ 的位置有 $pos$ 出现过 $0$ ，则截取的两段分别为 $[1,pos]$ 与 $[1,pos+1]$ ，小于 $\frac{n}{2}$ 同理。

- 若序列为非零序列（即全由 $1$ 组成），则截取的两段分别为 $[1,\lfloor \frac{n}{2} \rfloor]$ 与 $[1,2 \times \lfloor \frac{n}{2} \rfloor]$

为什么这样取呢，因为若存在 $0$ ，我们可以利用位移一位相乘/相除 $2$ 的关系构造一组解，若不存在 $0$ ，就截取 $\lfloor \frac{n}{2} \rfloor$ 长度的 $1$ 与 $2\times \lfloor \frac{n}{2} \rfloor$ 长度的 $1$ ，比如有这样一个序列：$111111111$ ，我们可以截取 $4$ 个 $1$ 和 $8$ 个 $1$ ， $8$ 个 $1$ 可以看作是 $4$ 个 $1$ 左移四位再加上自己后得到，从而形成了倍数关系。

需要注意本题是向下取整，这点十分重要。

## AC代码
```
#include <bits/stdc++.h>
#define rep(i, x, y) for (register int i = (x); i <= (y); i++)
#define down(i, x, y) for (register int i = (x); i >= (y); i--)
using namespace std;

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T, n;
    cin >> T;
    while (T--)
    {
        string s;
        cin >> n >> s;
        int flag = 0, pos = 0;
        rep(i, 0, n - 1) if (s[i] - '0' == 0)
        {
            flag = 1;
            pos = i;
            break;
        }
        flag ? printf("%d %d %d %d\n", pos >= n / 2 ? 1, pos + 1, 1, pos : pos + 1, n, pos + 2, n) : printf("%d %d %d %d\n", n <= 3 ? 1, n, 1, 1 : 1, n / 2 * 2, 1, n / 2);
    }
    return 0;
}
```

---

## 作者：KSToki (赞：1)

# 题目大意
给定一个 $01$ 串，你需要求出 $l1$，$r1$，$l2$，$r2$，满足 $r1-l1+1\geq\lfloor\frac{n}{2}\rfloor$，$r2-l2+1\geq\lfloor\frac{n}{2}\rfloor$，且由 $l1$ 到 $r1$ 组成的二进制数转为十进制后是 $l2$ 到 $r2$ 组成的二进制数转为十进制的非负整数倍，允许有前导零。
# 题目分析
乍一看很复杂，但这个允许有前导零就成了我们下手的地方，取前导零和不取不就是正确答案了吗？对于长度的限制，可以在前半段找 $0$，有就输出，没有就说明前半段全是 $1$。这时分类讨论，如果长度 $n$ 为奇数，那么可以直接前半段错开一位；如果长度 $n$ 为偶数，如果下一位是 $1$ 则错开一位，是 $0$ 则取为 $l1$ 和 $r1$，这时大数是小数的两倍。
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,Mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,a[20001];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		For(i,1,n)
			scanf("%1d",&a[i]);
		For(i,1,n-n/2)
			if(a[i]==0)
			{
				printf("%d %d %d %d\n",i,n,i+1,n);
				goto over;
			}
		if(n&1)
		{
			printf("%d %d %d %d\n",1,n-n/2-1,2,n-n/2);
		}
		else
		{
			if(a[n-n/2+1]==1)
				printf("%d %d %d %d\n",1,n-n/2,2,n-n/2+1);
			else
				printf("%d %d %d %d\n",1,n-n/2+1,1,n-n/2);
		}
		over:;
	}
	return 0;
}

```

---

## 作者：cszhpdx (赞：0)

这题其实不难，但是样例真的很迷惑，这题最大的难点是抛弃样例。

这题和前面几题一样，先考虑特殊情况， 特殊情况容易想到 $k=2^t$，这样也就是多 t 个 0，再特殊一点 $k=2$，也就是多一个 0，我们发现其实这题最大的限制是 $r-l+1\ge \lfloor \frac{n}{2} \rfloor$，我们考虑如果 $a_x=0~\&~x\gt \lfloor \frac{n}{2} \rfloor$，很明显答案可以是 $1,x,1,x-1$。

相应的，考虑当 $a_x=0~\&~x\le \lfloor \frac{n}{2} \rfloor$，答案可以是 $x,n,x+1,n$。

显然如果有 0，那么已经覆盖了所有情况，否则就都是 1，这时我们可以 $1,n,2,n-1$，相等，于是所有情况都被考虑完了，于是这道题就结束了。

代码：

```cpp
#include<bitset>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define mem(a, x) memset(a, x, sizeof(a))
#define rps(i, b, e) for(int i=(b);i<=(e);i++)
#define prs(i, e, b) for(int i=(e);i>=(b);i--)
#define rp(i, e) rps(i, 1, e)
#define pr(i, e) prs(i, e, 1)
#define rp0(i, e) rps(i, 0, (e)-1)
#define pr0(i, e) prs(i, (e)-1, 0)
#define rpg(i, x) for(int i=head[x];i;i=e[i].nxt)
#define opf(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)
using namespace std;
const int NR=2e4+10;
int T, n;
bitset<NR>a;
int main()
{
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		char cht;
		int l0=0, r0=0;
        //l0表示最左边的0
        //r0表示最右边的0
		rp(i, n) {
			scanf(" %c", &cht);
			a[i]=cht-'0';
			if(!a[i]) {
				if(!l0)l0=i;
				r0=i;
			}
		}
		if(!l0) {
			printf("1 %d 2 %d\n", n-1, n);
			continue;
		}
		if(r0>n/2) {
			printf("1 %d 1 %d\n", r0, r0-1);
			continue;
		}
		if(l0<n-n/2+1) {
			printf("%d %d %d %d\n", l0, n, l0+1, n);
			continue;
		}
	}
	return 0;
}
```



---

## 作者：BotDand (赞：0)

# $\text{Problems}$

定义 $f(x)$ 表示将二进制数 $x$ 转为十进制数的值。

给出序列 $s$，找出两对整数 $(l_{1},r_{1})$，$(l_{2},r_{2})$，满足 $1\le l\le r\le n$ 且 $r-l+1\ge \left \lfloor \frac{n}{2} \right \rfloor $，其中 $l_{1}\neq l_{2}$ 或 $r_{1}\neq r_{2}$。

设 $t$ 为 $s\left[l_{1} : r_{1}\right]$，$w$ 为 $s\left[l_{2} : r_{2}\right]$，则存在一个非负整数 $k$，满足 $f(t)=f(w)\times k$。

其中，$s[l:r]$ 的定义为 $s$ 中 $l$ 至 $r$ 的字串。

求 $l_{1}$，$r_{1}$，$l_{2}$，$r_{2}$。

若有多组解，输出一组即可。

# $\text{Answer}$

不难发现 $f(x)=f(x+0)\times k$。

于是可以找 $0$，如果 $0$ 的位置在 $\left[\left \lfloor \frac{n}{2} \right \rfloor+1,n\right]$，则结果为 $(1,x)$，$(1,x-1)$。如果 $0$ 的位置在 $\left[1,\left \lfloor \frac{n}{2} \right \rfloor\right]$，则结果为 $(x,n)$，$(x+1,n)$。

如果全为 $1$，输出 $(1,n-1)$，$(2,n)$ 即可。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
int a[20002];
char ch;
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline void print(int a,int b,int c,int d)
{
    write(a);
    putchar(' ');
    write(b);
    putchar(' ');
    write(c);
    putchar(' ');
    write(d);
    putchar('\n');
}
inline void work()
{
    n=read();
    for(int i=1;i<=n;++i)
    {
        ch=getchar();
        a[i]=ch-48;
    }
    for(int i=n/2+1;i<=n;++i)
        if(a[i]==0)
        {
            print(1,i,1,i-1);
            return;
        }
    for(int i=1;i<=n/2;++i)
        if(a[i]==0)
        {
            print(i,n,i+1,n);
            return;
        }
    print(2,n,1,n-1);
}
int main()
{
    t=read();
    while(t--) work();
    return 0;
}
```


---

## 作者：reailikezhu (赞：0)

结论题。

如果有 $0$，设第一个 $0$ 的位置是 $i$.

$i$ 如果出现在了 $[1,n/2]$ 这个区间之间，那么输出 $i,n,i+1,n$。

此时 $k=1$（$k$ 见题意）。

如果出现在了后面，那就输出 $1,i,1,i-1$。

此时 $k=2$。

如果全是 $1$，那就输出 $1,n/2·2,1,n/2$。

同样满足题意。
代码：
```
#include<stdio.h>

int t;
int n;
char s[20010];
int a[20010];

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		scanf("%s",s+1);
		bool flag=0;
		for(int i=1;i<=n/2;i++){
			if(s[i]=='0'){
				printf("%d %d %d %d\n",i,n,i+1,n);
				flag=1;
				break;
			}
		}
		if(flag==1) continue;
		for(int i=n/2+1;i<=n;i++){
			if(s[i]=='0'){
				printf("%d %d %d %d\n",1,i,1,i-1);
				flag=1;
				break;
			}
		}
		if(flag==1) continue;
		printf("%d %d %d %d\n",1,n/2*2,1,n/2);
	}
	return 0;
}
```

---

## 作者：laboba (赞：0)

挺有意思的一道题，赛时一开始没什么思路就在T3T4之间反复横跳，虽然最后都过了但是得分还没有T2高。。

首先直接从二进制形式思考倍数关系是比较难的，而转化成十进制复杂度过高无法操作。因此考虑从 $k$ 切入，显然直接枚举 $k$ 是不行的，可以想到取特殊的 $k$ 进行分析：$k=1$  时，$t$ 和 $w$ 只能在前导零个数上有区别； $k=2^x$ 时，   $t$ 和 $w$ 只有末尾零的个数不同。发现这两种情况有相似之处——$t$ 和 $w$ 只在开头和末尾的零有区别，感觉这样的 $t$ 和 $w$ 应该是不难构造的。进而想到这样的构造方法：对于满足$a_i=0$的 $i$，$s_1s_2...s_{i}=2\times s_1s_2...s_{i-1}$，$s_is_{i+1}...s_n=s_{i+1}s_{i+2}...s_n$，两种构造均满足题意，题目中还有关于子串长度的限制，因为 $\left\lfloor\dfrac{n}{2}\right\rfloor\times2\le n$ ，所以上面的两种构造中必然有一个满足长度限制。注意要特判全是 $1$ 的情况。

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int a[300100];
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%1d",&a[i]);
		int tmp=0;
		for(int i=n;i>=1;i--){
			if(!a[i]){
				tmp=i;
				break;
			}//所有0都是等价的，不妨直接取最右边的。 
		}
		if(!tmp){
			if(n%2)printf("%d %d %d %d\n",1,n-1,1,n/2);
			else printf("%d %d %d %d\n",1,n,1,n/2);
			continue;
		}//特判：取n/2*2个1和n/2个1
		if(tmp>(n+1)/2)printf("%d %d %d %d\n",1,tmp,1,tmp-1);
		else printf("%d %d %d %d\n",tmp,n,tmp+1,n);//判断选取哪一种构造 
	}
}
```


---

## 作者：LRL65 (赞：0)

### 题意：

有一个长度为 $n$ 的二进制串。需要找到两个字串，使得子串长度都大于 $\lfloor \frac{n}{2} \rfloor$ ，并且子串 $S_1$ 的十进制数是子串 $S_2$ 的十进制数的 $k$ 倍（ $k$ 为非负整数 ）。输出 $S_1$ 的左右端点 $l_1 ,r_1$ ，$S_1$ 的左右端点 $l_2,r_2$ 。只需一组即可。

### 思路：

1. 如果这个二进制串中，包含至少一个 $0$ ，设一个 $0$ 的位置为 $x$ 。
	- 如果 $x-1>\lfloor \frac{n}{2} \rfloor$ 时，那么  $1\sim x ,1\sim x-1$ 为一组解。因为 $S_{1\sim x}$ 的十进制数为 $S_{1\sim x-1}$ 的 $2$ 倍。
	- 否则 $x\sim n ,x+1\sim n$ 为一组解。因为这两个字串的十进制数相等。（ $k$ 取 $1$ ）

1. 否则这个二进制串全是 $1$ ，$1\sim \lfloor \frac{n}{2} \rfloor ,2\sim \lfloor \frac{n}{2} \rfloor+1$ 为一组解。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
string s;
int main() {
    cin>>t;
    while(t--) {
        cin>>n>>s;
        bool flag=0;
        for(int i=1;i<=n;i++) {
            if(s[i-1]=='0') {
                if(i-1>=n/2)cout<<1<<" "<<i<<" "<<1<<" "<<i-1<<endl;
                else cout<<i<<" "<<n<<" "<<i+1<<" "<<n<<endl;
                flag=1;
                break;
            }
        }
        if(flag==0)cout<<1<<" "<<n/2<<" "<<2<<" "<<n/2+1<<endl;
    }
}
```


---

