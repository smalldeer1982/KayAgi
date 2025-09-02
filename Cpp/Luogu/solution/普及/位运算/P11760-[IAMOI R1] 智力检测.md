# [IAMOI R1] 智力检测

## 题目背景

小 C 拉小 L 去见岳父岳母。

岳父岳母决定考验小 L 的智商，于是他们出了一道题。

## 题目描述

岳父给定一个下标从 $1$ 开始的数组 $a$，初始时 $a_i = 2^{i-1}$。

岳母让小 L 对这个数组进行如下操作若干次：

第 $i$ 次操作中，选择两个数 $u_i,v_i\ (2 \le u_i<v_i)$，依次执行：

- $a_{v_i} \gets a_{v_i}+a_{u_i}+a_{u_i-1}$

- $a_{u_i} \gets -\infty$

- $a_{u_i-1} \gets -\infty$

对于第一次操作没有特殊限制，但对于之后的每一次操作，都必须保证 $v_i > v_{i-1}$。

给出 $T$ 次询问，每次两个数 $k$ 和 $x$，请回答能否通过有限次操作，使 $a_k = x$。

询问之间相互独立（即每次询问后应重置 $a$ 数组）。

## 说明/提示

对于 $100\%$ 的数据，$1\le T\le5\times10^6$，$1\le k \le 60$，$0\le x \le 4 \times 10^{18}$。

| 测试点编号 | $T$ | $k$ | 特殊性质 | 分数 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $\le100$ | $\le10$  | 无 | 20 |
| $2$ | $\le60$ | $\le60$ | A | 20 |
| $3$ | $\le1\times10^5$ | $\le60$ | 无 | 30 |
| $4$ | $\le5\times10^6$ | $\le60$ | 无 | 30 |


特殊性质 A：保证 $x=2^{k}-1$。

请注意您实现的常数复杂度。

时空限制均在标程（加快读优化）的 **2.5** 倍以上。

本题输入输出量较大，我们强烈建议您使用快速读入模板：

```cpp
char *p1,*p2,buf[1<<20];
inline char gc(){if(p1==p2)p2=(p1=buf)+fread(buf,1,1<<20,stdin);return p1==p2?' ':*p1++;}
inline long long read(){
	register long long s=0; register char c=gc();
	while(c<'0'||c>'9') c=gc();
	while(c>='0'&&c<='9') s=(s<<3)+(s<<1)+(c^48),c=gc();
	return s;
}

x = read() //读入x
```


## 样例 #1

### 输入

```
4
6 36
6 35
5 30
5 31```

### 输出

```
0101```

# 题解

## 作者：liangbob (赞：10)

感谢出题人 [Tian36309](https://www.luogu.com.cn/user/697945) 写下了此篇题解的初版，并对修改版提出了宝贵的修改意见。

## [IAMOI R1] 智力检测 题解

> **定义 I** 定义“用 $v$ 取 $a_u$”代表对 $u_i=u$，$v_i=v$ 进行题目所述的操作
>
> **定义 II** 定义“$a_u$ 被取”表示对于某个 $v$，用 $v$ 取了 $a_u$


>  **命题 I** 取数时，$a_u$ 不可能被重复取。

- 证明显然，反证法。考虑到如果取重复的 $a_u$ 会取到 $-\infty$，你后面无论怎么取，都无法取回一个非负数。同时题目保证 $x$ 是个非负数，矛盾，所以不能重复取。

>  **命题 II** 如果 $x < 2^{k-1} $ 或者 $x \ge 2^k$，那么本次询问无解。

- 根据命题 I，可以知道 $a_u$ 不能重复取，这意味着每个操作的 $a_u$ 和 $a_{u-1}$ 均非负，也就是说，经过多次操作之后，$a_k$ 必然只增不减，那么 $x<2^{k-1}$ 自然也就无解了。

- 继续根据命题 I，可以继续知道 $a_u$ 不能重复取，注意到最极限的情况显然是通过反复操作把 $2^0$，$2^1$，$2^2$，……，$2^k$ 取一次，也就是说 $a_k \le 2^k-1$，这显然不到 $2^k$，于是 $x\ge 2^k$ 无解。

**以下的分析令 $x \gets x - 2^{k-1}$。**（这一位二进制数不用取，因此不考虑）

> **命题 III** 可以通过若干次操作使 $a_k = x$，当且仅当如果 $x$ 二进制下不包含连续奇数个 $1$。

- 由于 $a$ 数组的特殊性质，我们把 $a$ 数组转换成二进制后发现，第一次取 $a_u$ 和 $a_{u-1}$ 就相当于把 $a_v$ 的第 $u$ 位和第 $u-1$ 位改为 $1$，而下一次操作中选的数如果是 $a_v$ 则这次操作后那一个数的第 $u-1,u,v,v-1$ 位都将变为 $1$。

- 由于 $u_i<v_i<v_{i-1}$，因此上述性质成立。

- 由于每次操作都是将两位改为 $1$，因此如果 $x$ 二进制下包含连续奇数个 $1$，那么必然无法操作得到。

那么我们就有了第一个思路：

- 对于每一次询问，将 $x$ 进行二进制拆分，如果发现存在连续奇数个 $1$ 输出 $0$，否则输出 $1$。

- 单次询问 $O(\log x)$，常数比较好的话可以获得 $90$ 分。（卡一卡没准可以拿满分）

> **命题 IV** 对于每一个合法的答案（即不出现连续奇数个 $1$，后同），其一定是 $3$ 的倍数。

证明平凡，因为相邻两个 $1$ 可以理解为 $x+2x$，而这个数很明显是 $3$ 的倍数。

> **命题 V** 对于每一个合法的答案，用它除以 $3$ 后进行二进制拆分，一定不会出现连续的 $1$。

- 观察到，除以 $3$ 相当于在除以 $(11)_2$，试一下就会发现，二进制下连续偶数个 $1$ 除以 $(11)_2$ 就等于 $(1010101\ldots)_2$。
- 而若一个不包含连续 $1$ 的二进制数乘 $3$，结果中一定只包含连续的偶数个 $1$（相当于将其右移一位再相加）。
- 综上，得证。

>  **命题 VI** 符合是 $3$ 的倍数和除以 $3$ 后进行二进制拆分，不会出现连续的 $1$ 的数必然是合法的答案。

- 显然，所有不含连续的 $1$ 的二进制数乘三都是合法答案。

那么，我们只需要判断如下两个条件即可：

- $x$ 是 $3$ 的倍数
- $x$ 除以 $3$ 后二进制下不含有连续的 $1$。

对于第二个条件，可以通过 $\lfloor\dfrac{x}{3}\rfloor$ 按位与 $\lfloor\dfrac{2x}{3}\rfloor$ 来判断。显然如果没有连续的 $1$，上述式子的结果是 $0$。

时间复杂度 $O(T)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,k,sum,mi[100];
inline long long read()
{
	char c=getchar();long long x=0,f=1;
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+c-48;
	return x*f;
}
int main(){
	T = read();
	mi[1] = 1;
	for(int i=2;i<=62;i++)mi[i] = mi[i-1]*2;
	while(T--){
		k = read();
		sum = read();
		if(sum >= mi[k+1] or sum < mi[k]){
			printf("0");
			continue;
		}
		sum -= mi[k];
		if(sum % 3 == 0 and (((sum/3) & (sum/3*2)) == 0))printf("1");
		else printf("0");
	}
	return 0;
}
```

---

## 作者：As_linzile (赞：2)

# [IAMOI R1] 智力检测题解


很简单的一道题，但赛时由于题目所给的快读无法正常运行，用了自己的快读，导致最后一个点被卡常。

## 思路
分析一下题目操作的含义：简单讲就是给定 $k$ 和 $x$，对于一个初始全为零，第 $k-1$ 位为 1 的二进制序列，每次操作可将连续两个位置变为 1，且操作位置必须递增，能否使其表示 $x$ 这个数。

因为第一次以后的操作位置要大于上一个，所以对于k以后的数没有任何用，故只考虑$k$以前的数。发现k这位数必须要取到，所以 $x\geq2^{k-1}$。

总结下，就是 $x\in[2^{k-1},2^k-1]$ 时才有可能符合条件。


发现当使一个位置被选为 $v_i$ 时，这个的上一位就一定不能取，因为若取上一位，就会取到这一位，即取到负无穷，所以形如 $10111$ 的数，即**二进制有连续的奇数个** $1$ 的数就**不符合**条件。



---

综上所述，只有 $x\in[2^{k-1},2^k-1]$，且其二进制只有有连续的偶数个 $1$，才成立。


---

一些小细节：

- 由于 $k\leq60$ ，所以要开 ```long long```。
- 由于只有遇见 $0$ 时才会判断，所以二进制拆分完后要再判断一下，似乎样例有这种情况。
- 一定要用题目给的快读(本人惨痛教训)。

时间复杂度 $O( T\times \log x )$，但跑得还挺快，具体常数优化见代码。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0')
	{
		x=x*10+c-'0',c=getchar();
	}
	return x*f;
}
int b[100]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,1073741824,2147483648,4294967296,8589934592,17179869184,34359738368,68719476736,137438953472,274877906944,549755813888,1099511627776,2199023255552,4398046511104,8796093022208,17592186044416,35184372088832,70368744177664,140737488355328,281474976710656,562949953421312,1125899906842624,2251799813685248,4503599627370496,9007199254740992,18014398509481984,36028797018963968,72057594037927936,144115188075855872,288230376151711744,576460752303423488,1152921504606846976};
//这里预处理出了2^60以内所有数，方便判断x范围
string ans;
signed main()
{
	int T;
	cin>>T;
	for(register int p=1;p<=T;++p)//听说++i要快于i++
	{
		int k,x;
		k=read(),x=read();
		if(b[k]-1<x||b[k-1]>x)
		{
			ans+='0';
			continue;
		}
		int cnt=0;//记录1的个数
		int flag=1;
		while((x>>1))//位运算常数小
		{
			if(x&1) cnt++;
			else
			{
				if(cnt&1)
				{
					flag=0;
					break;//不符合直接break
				}
				cnt=0;
			}
			x>>=1;
		}
		if(cnt&1) flag=0;
		ans+=(flag?'1':'0');//三目运算符要比if else快一些
	}
	cout<<ans;
	return 0;
}
```

## 感谢阅读，如有不足之处还请指出。

---

## 作者：Wreaths (赞：2)

一个带 $\log$ 的做法。

首先，比较明显的两个无解的判断 $x \ge 2^k$ 与 $x < 2^{k-1}$。第一个判断是因为题面中需要保证 $u_i<v_i$，那么那些比第 $k-1$ 位位数高的那些 $1$ 就无法被加到 $a_k$ 上，因此无解；第二个判断是因为如果 $x < 2^{k-1}$ 的话，那么在第 $k-1$ 位上就没有 $1$，即为 $0$，但是如果要使得 $a_k=x$ 的话，就必须保留第 $k-1$ 位上的 $1$，与前面的第 $k-1$ 位上没有 $1$ 矛盾了，因此无解。

其次，我们观察一下题面，当选中 $u_i$ 与 $u_i-1$ 后，$a_{u_i}$ 与 $a_{u_i-1}$ 就被赋值为 $-\infty$，那么就可以理解为 $a_{u_i}$ 与 $a_{u_i-1}$ 在这次询问中被删掉了。再整理一下就可以发现，由于每次删的是连续的 $2$ 个数，所以有解必须要保证 $x$ 在二进制下除开第 $k-1$ 位，每一段连续的 $1$ 的长度都要为偶数，不然就会落下几个 $1$ 死活加不到 $a_k$ 上，判为无解。

最后，我们得到了判断条件就要考虑如何去求得是否满足条件。于是我们就可以用一个叫做 bitset 的东西（对于 c++），将 $x$ 存下来，并按低位到高位去扫每一段连续的 $1$ 的长度是否为偶数，如果扫到了一段连续的 $1$ 的长度不是偶数，就打个无解标记，直接退出循环输出无解，否则扫完整个数的 $60$ 位后就输出有解。不过要注意的是，在从低往高扫的时候，可能第 $k-2$ 位是 $1$，所以在扫完后还要在判一下，同时这题有一点卡常，记得加快读快写。总体复杂度为 $O(T\log n)$。

代码如下：

```c++
T=read();
while(T--){
    k=read(),x=read();
    if(x>=(1ll<<k)||x<(1ll<<k-1)){
        putchar('0');
        continue;
    }
    bitset<70>tmp(x);
    bool f=1;
    int j=0;
    for(int i=0;i<=65;i++){
        if(tmp[i]==1){
            if(i!=k-1)
                j++;
        }else{
            if(j&1){
                f=0;
                break;
            }j=0;
        }
    }
    if(j&1)
        f=0;
    if(f)
        putchar('1');
    else 
        putchar('0');
}
```

---

## 作者：lzx111218 (赞：1)

# P11760 [IAMOI R1] 智力检测
[题目传送门](https://www.luogu.com.cn/problem/P11760)
## 思路
可爱卡常题。

考虑递归。

- 
   数组 $a$ 的初始值是：
   $a = [1, 2, 4, 8, 16, 32, \ldots]$
   其中 $a[i] = 2^{i-1}$，是一个从 1 开始的**指数级增长序列**。

- 
   每次操作的结果是
   $a[v_i] \gets a[v_i] + a[u_i] + a[u_i-1]$
   而 $a[u_i]$ 和 $a[u_i-1]$ 被置为负无穷，因此这些位置的值**无法再被修改**。

- 观察到每次操作基本是对数组值的累加，且对 $a[u_i]$ 和 $a[u_i-1]$ 的修改是**不可逆的**。

- 对于 $k$ 和 $x$，要检查能否通过对 $a[k]$ 的操作达到 $x$。
- 关键是要判断 $x$ 是否可以通过**某些组合**得到。

**时间/空间复杂度均为** $O(n)$。
### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, a[1145];
namespace fastIO{char *p1,*p2,buf[100000];
	#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
	inline void read(int&n){int x=0,f=1;char ch=nc();while(ch<48||ch>57){if(ch=='-'){f=-1;}ch=nc();}while(ch>=48&&ch<=57){x=(x<<3)+(x<<1)+(ch^48),ch=nc();}n=x*f;}
	inline void read(string&s){char ch=nc();while(ch==' '||ch=='\n'){ch=nc();}while(ch!=' '&&ch!='\n'){s+=ch,ch=nc();}}
	inline void read(char&ch){ch=nc();while(ch==' '||ch=='\n'){ch=nc();}}
	inline void write(int x){if(x<0){putchar('-'),x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');return;}
	inline void write(const string&s){for(register int i=0;i<(int)s.size();i++){putchar(s[i]);}}
	inline void write(const char&c){putchar(c);}
}using namespace fastIO;   
long long solve(int k, int sum){
    if(sum >= a[k+1] || sum < a[k]){
        return 0;
    }
    sum -= a[k];
    if(sum % 3 == 0 && (((sum / 3) & (sum / 3 * 2)) == 0)){
        return 1;
    }
    return 0;
}
void f(int T) {
    if(T == 0) return;
    int k, sum;
    read(k);
	read(sum); 
    write(solve(k, sum));
    f(T - 1);
}
signed main(){
    a[1] = 1;
    for(int i = 2; i <= 62; i++) a[i] = a[i-1] * 2;
    read(n);
    f(n);
    return 0;
}
```

---

## 作者：dingxiongyue (赞：1)

# 题解：P11760 [IAMOI R1] 智力检测

## Description：
[见题面](https://www.luogu.com.cn/problem/P11760)

## Analysis：
因为每次操作后会变为 $-\infty$，所以每个位置最多只会选择一次。数组 $a$ 初值均为 $2$ 的整数次幂，所以每次操作会使 $a_k$ 增加 $2^{i} + 2^{i - 1}$，在二进制中即为将连续两位加 $1$。  

令 $delta = a_k - x$，若 $delta$ 的二进制表示中所有连续的 $1$ 序列的长度为偶数，该询问即为可行，否则，即为不可行。  

详见代码。  

时间复杂度 $O(T \log x)$。  

## Code:
[AC记录](https://www.luogu.com.cn/record/203995085)  
```cpp
#include <iostream>
#include <vector>
#define int long long
int T;
int k, x;
int _x;
int del;
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

inline void write(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

bool check(int x) {
	while (x) {
		if (x & 1) {
			if (!((x >> 1) & 1)) return false;
			x >>= 1;
		}
		x >>= 1;
	}
	return true;
}

signed main() {
	T = read();
	while (T--) {
		k = read(), x = read();
		_x = (1ll << (k - 1));
		if (x < _x) {
			putchar('0');
			continue;
		}
		del = x - _x;
		if (check(del)) putchar('1');
		else putchar('0');
	}
	printf("\n");
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

#### 思路分析
本题的核心是判断能否通过给定的操作使数组中的 $a_k$ 变为 $x$。由于初始时 $a_i=2^{i-1}$，操作是将 $a_{u_i}$ 和 $a_{u_i-1}$ 的值累加到 $a_{u_i}$ 上，并将 $a_{u_i}$ 和 $a_{u_i-1}$ 置为 $-∞$，且后续操作的 $v_i$ 要严格递增。  
我们可以从二进制的角度来思考这个问题。初始数组 $a$ 的元素对应着二进制位，操作相当于合并相邻的二进制位。我们可以将 $x$ 转换为二进制，然后检查能否通过合并初始二进制位得到 $x$ 的二进制表示。  
#### 代码  

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;//不开long long见祖宗
char *p1, *p2, buf[1 << 20];
inline char gc() {
    if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin);
    return p1 == p2 ? ' ' : *p1++;
}
inline ull read() {//快读
    ull s = 0;
    char c = gc();
    while (c < '0' || c > '9') c = gc();
    while (c >= '0' && c <= '9') {
        s = (s << 3) + (s << 1) + (c ^ 48);
        c = gc();
    }
    return s;
}
ull pow2[61];
void p() {
    pow2[0] = 1;
    for (int i = 1; i <= 60; ++i) pow2[i] = pow2[i-1] << 1;
}
inline bool solve(ull k, ull x) {//二进制
    if (k == 1) return x == 1;
    ull base = pow2[k-1];
    if (x < base) return false;
    ull rem = x - base;
    if (rem % 3 != 0) return false;
    ull S = rem / 3;
    ull max_S = pow2[k-2];
    if (S >= max_S) return false;
    return (S & (S << 1)) == 0;
}
char op[5000005];
int oi = 0;
int main() {
    p();
    ull T = read();
    for (ull i = 0; i < T; ++i) {
        ull k = read();
        ull x = read();
        bool ans = solve(k, x);
        op[oi++] = ans ? '1' : '0';
    }
    op[oi] = '\0';
    puts(op);
    return 0;
}
```

---

## 作者：buowen123 (赞：1)

贪心结论题附着着数论的色彩，会不会显得有些割裂呢？

## 70 pts 做法

操作 $u_i,v_i$ 等价于将 $a_{u_i}$ 和 $a_{u_i-1}$ 销毁，原本的值加到 $a_{v_i}$ 上。因为销毁机制的存在，每个数至多算一次，因而所有二进制位不会互相影响。

---

- 结论 1：若 $x\ge 2^k$ 或 $x\lt 2^{k-1}$ 则无解。

因为 $a_k$ 不会继承 $a_{k+1},a_{k+2}\dots$ 的贡献，所以 $x\lt 2^k$。

$a_k$ 的初值为 $2^{k-1}$，所以 $x\ge 2^{k-1}$。

----

- 结论 2：设 $y=x-2^{k-1}$，则有解当且仅当在二进制表示下，$y$ 的所有的**极长 $1$ 连续段**长度均为偶数。

### 必要性

由于一个数不会贡献两次，不难发现操作可以画成一棵树的形式：

![](https://cdn.luogu.com.cn/upload/image_hosting/5i05ureh.png)

但这棵树的形态并不重要。重要的是，最终这棵树以 $k$ 为根，且树上每个非根节点对应的两个值，恰好为 $a_k$ 贡献一次。所以 $y$ 的值对应着若干个（不交的）$a_u+a_{u-1}$，也就是二进制下两位连续的 $1$。

由于这些 $1$ 不交且长度皆为 $2$，故她们的和在二进制下一定表现为长度为偶数的连续段。

### 充分性

如果 $y$ 满足必要性，将 $y$ 两位两位地拆分，并根据这些位构造树即可。

所以直接模拟，时间复杂度 $O(Tk)$。

> 事实上，该做法可以获得 100pts，~~数据组仍需努力~~。

## 100pts 做法

发现所有的贡献都形如 $2_u+2^{u-1}$ 的形式。注意到 $2^{u-1}\times3=2_u+2^{u-1}$，所以若有解，则 $y$ 必然是 $3$ 的倍数。

设 $z=\frac{y}{3}$。对于 $y$ 连续的两个 $11$，除以 $3$ 则会变为 $01$。类似的 $1111$ 变为 $0101$，$111111$ 变为 $010101$……

由此可以得到另外一个必要条件：
- 结论 4：$3|y$；$z$ 的二进制表达中，不存在连续的两个 $1$。

很显然，该条件也是充分的。

所以得到做法：求出 $z$，判断 $z$ 的二进制表达中是否存在连续的两个 $1$。这可以通过 $z$ 和 $\left\lfloor\dfrac{z}{2}\right\rfloor$ 的按位与是否非 $0$ 判断。

复杂度 $O(T)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
char  *p1,*p2,buf[1<<20];
inline char gc(){if(p1==p2)p2=(p1=buf)+fread(buf,1,1<<20,stdin);return p1==p2?' ':*p1++;}
inline long long read(){
	register long long s=0; register char c=gc();
	while(c<'0') c=gc();
	while(c>='0') s=(s<<3)+(s<<1)+(c^48),c=gc();
	return s;
}
long long T,x,k,y;
int main(){
	T=read();
	while(T--){
		k=read();x=read();y=x-(1ll<<k-1);
		if(x<(1ll<<k-1) || x>=(1ll<<k) || y%3) putchar('0');
		else putchar('0'+!((y/3)&(y/6)));
	}
}
```

---

## 作者：sbno333 (赞：0)

质量还行。

考虑若果需要操作，最后一次操作一定选取 $v=k$。

假设不是，当 $v<k$ 时相当于啥都没干。

如果 $v>k$ 这个操作要么将 $a_k$ 变成负无穷，要么等价于啥都没干，得证！

那么我们考虑操作其实就是一个数二进制意义下往里头添加 $1$。

由于每次操作是 $a_u+a_{u-1}$。

此时 $2^{u-1}$ 和 $2^{u-2}$ 两位一定存在。

除非最后一次操作让 $2^{v-1}$ 落单，否则二进制意义下的一都不是落单存在的。

然后考虑一个连续的 $1$ 的段有没有可能长度为奇数（不考虑 $2^{k-1}$）。

我们考虑操作过程，倒着看一遍。

每次操作分裂出两个相邻的 $1$。

由于被赋值为负无穷，所以不重叠。

于是都是长度为偶数。

那么是否不考虑 $2^{k-1}$ 一定可以呢？

其实是的。

我们把这些块在细分，分成若干长度为 $2$ 的连续 $1$ 的块。

每次块首选择上一个块的块为作为 $u$。

然后合并，由于 $u-1$ 也被选上，这回让上一个块都被选，然后上一个块首也是这样，于是都能选上。

最后考虑 $2^{k-1}$，操作就是选最后一个块块尾即可。

于是结论就是首先二进制意义下 $2^{k-1}$ 位必须有 $1$，也是最高位，**剩下的**长度必须是偶数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
char *p1,*p2,buf[1<<20];
inline char gc(){if(p1==p2)p2=(p1=buf)+fread(buf,1,1<<20,stdin);return p1==p2?' ':*p1++;}
inline long long read(){
	register long long s=0; register char c=gc();
	while(c<'0'||c>'9') c=gc();
	while(c>='0'&&c<='9') s=(s<<3)+(s<<1)+(c^48),c=gc();
	return s;
}

signed main(){
	std::ios::sync_with_stdio(0);
	int t;
	t=read();
	while(t--){
		int k,x;
		k=read();
		x=read();
		k--;
		if(x<(1ll<<k)||(1ll<<(k+1))<=x){
			putchar('0');
			continue;
		}
		x-=(1ll<<k);
		int g;
		g=0;
		for(int i=k-1;i>=0;i--){
			if(x&(1ll<<i)){
				g++;
			}else{
				if(g&1){
					break;
				}
				g=0;
			}
		}
		if(g&1){
			putchar('0');
		}else{
			putchar('1');
		}
	}
	return 0;
}
```

---

