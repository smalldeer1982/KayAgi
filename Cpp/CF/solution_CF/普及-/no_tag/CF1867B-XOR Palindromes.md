# XOR Palindromes

## 题目描述

给出一个长度为 $n$ 的 $01$ 串(只含 $0,1$ 的字符串) $s$。定义一个数 $x$ 是好数，当仅当存在一个长度也为 $n$ 的 $01$ 串 $l$ 使得对于所有的 $s_i$ 被 $s_i\oplus l_i$ 替换后得到的 $01$ 串是一个回文串。

对于给出的一组 $n,s$ ，你需要给出一个长度为 $n+1$ 的 $01$ 串 $t$ ，$t_i=1$ 当仅当 $i$ 是一个好数。**注意，$t$ 从 $0$ 开始编号**

题目中 $\oplus$ 表示异或。

回文串指正着读反着读都相同的字符串，比如 $0110,01010,1111$ 都是回文串。

## 说明/提示

考虑第一个例子：

 $t_2=1$ 是因为我们可以选到 $l=010100$ ，异或后 $s$ 变成 $111111$ 成为一个回文串。
 
 $t_4=1$ 是因为我们可以选到 $l=101011$ 此时 $s$ 变成回文串 $000000$。
 
 可以证明其他任意的 $i$ 都不满足成为 “好数” 的条件，故其他所有的位置都是 $0$。

## 样例 #1

### 输入

```
5
6
101011
5
00000
9
100100011
3
100
1
1```

### 输出

```
0010100
111111
0011111100
0110
11```

# 题解

## 作者：Daniel_yao (赞：3)

## Problem
给定一个 $n$ 位二进制 $01$ 串。一个数 $x$ 是好的定义为：存在一个长度为 $n$ 二进制 $01$ 串 $l$，使得按位操作 $s_i \oplus l_i$ 后的串为回文串。

现有长度为 $n+1$ 答案串 $t$，第 $i(0\le i\le n+1)$ 位为 $1$ 表示数字 $i$ 是好的，为 $0$ 表示数字 $i$ 是不好的。求 $t$。
## Solve
首先，肯定是从小到大找答案。考虑最小的，合法（“好的”）的数 $x$ 为多少。也就是求将原串变为回文串的最小步数。

做法是从串的中点向左右扩展。若两数不同，则耗费一步数更改其中的一位。具体是哪一位不需要管。因为我们只需要将其变为回文串，不需要关心其形态。

然后知道最小的 $x$，考虑怎样将答案拓展。不难发现，当 $n$ 为奇数时，介于 $x\sim n-x$ 之间的数 $y$ 都是“好的”；当 $n$ 为偶数时，介于 $x\sim n-x$ 之间的数 $y$ 且 $y-x$ 为偶数都是“好的”。

证明很简单，当 $n$ 为偶数时，每次在中点的两边对称的地方同时更改不会改变其回文的状态。也就是说，当 $y-x$ 为偶数且 $y\in[x,n-x]$ 时，$y$ 是好的。奇数时同理，不过在中心改也不会改变其回文的状态，这样可以组合出 $[x,n-x]$ 的所有数，自然其中的所有数也都是“好的”。

最后模拟即可。

时间复杂度 $O(Tn)$。
## Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define H 19260817
#define rint register int
#define For(i,l,r) for(rint i=l;i<=r;++i)
#define FOR(i,r,l) for(rint i=r;i>=l;--i)
#define MOD 1000003
#define mod 1000000007

using namespace std;

namespace Read {
  template <typename T>
  inline void read(T &x) {
    x=0;T f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x*=f;
  }
  template <typename T, typename... Args>
  inline void read(T &t, Args&... args) {
    read(t), read(args...);
  }
}

using namespace Read;

void print(int x){
  if(x<0){putchar('-');x=-x;}
  if(x>9){print(x/10);putchar(x%10+'0');}
  else putchar(x+'0');
  return;
}

const int N = 1e5 + 10;

int T, n;

char a[N];

void solve() {
  read(n);
  For(i,1,n) cin >> a[i];
  if(n & 1) {
    int l = (1 + n) >> 1, r = l, ans1 = 0;
    while(l >= 1) {
      if(a[l] != a[r]) ans1++;
      l--, r++;
    }
    For(i,0,n) {
      if(i >= ans1 && i <= n - ans1) cout << 1;
      else cout << 0; 
    }
    cout << '\n';
  } else {
    int l = n >> 1, r = l + 1, ans1 = 0;
    while(l >= 1) {
      if(a[l] != a[r]) ans1++;
      l--, r++;
    }
    For(i,0,n) {
      if(i >= ans1 && i <= n - ans1 && (i - ans1) % 2 == 0) cout << 1;
      else cout << 0; 
    }
    cout << '\n';
  }
}

signed main() {
  read(T);
  while(T--) {
    solve();
  }
  return 0;
}
```

---

## 作者：One_JuRuo (赞：2)

## 思路

题目问的是改 $i$ 位，能不能让原串变成回文串，其中 $0\le i \le n$。

首先，我们可以统计前后对称位置不一样的对数，记为 $k$，那么至少也得改 $k$ 次，假设剩下前后对称位置一样的有 $m$ 对（如果 $n$ 为奇数，则最中间的一位不计入 $m$），那么在 $k$ 次的基础上，可以增加偶数次，即把两个对称位置一样的都改了，最多可以改到 $m$ 次，即 $k,k+2,k+4 \cdots k+m\times2$。

还需要考虑 $n$ 为奇数的时候，最中间的一位可以改或不改，所以能成功地有 $k,k+1,k+2\cdots k+m\times2+1$。

实现可以用一个数组记录答案，但是千万不要用 `memset`，因为如果用 `memset` 的话，就会 `TLE`，不要问我为什么知道（痛苦面具）。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,len,d,bd,ans[100005];
char ch[100005];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%s",&n,ch+1),d=bd=0;
		for(int i=0;i<=n;++i) ans[i]=0;
		for(int i=1;i*2<=n;++i)
		{
			if(ch[i]==ch[n+1-i]) ++d;
			else ++bd;
		}
		for(int i=0;i<=d;++i)
		{
			ans[bd+i*2]=1;
			if(n%2) ans[bd+i*2+1]=1;
		}
		for(int i=0;i<=n;++i) printf("%d",ans[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：Talkative (赞：0)

给出一个长度为 $n$ 的 $01$ 串(只含 $0,1$ 的字符串) $s$。定义一个数 $x$ 是好数，当仅当存在一个长度也为 $n$ 的 $01$ 串 $l$ 使得对于所有的 $s_i$ 被 $s_i\oplus l_i$ 替换后得到的 $01$ 串是一个回文串。对于给出的一组 $n,s$ ，你需要给出一个长度为 $n+1$ 的 $01$ 串 $t$ ，$t_i=1$ 当仅当 $i$ 是一个好数。注意，$t$ 从 $0$ 开始编号，题目中 $\oplus$ 表示异或。

分类讨论：

1. 当 $2\mid n$，我们观察本来已经对称的字符，每一对字符贡献为 $2$。
2. 当 $2\nmid n$，除了上述贡献以外，我们发现中位字符对合法的每次答案贡献是 $1$ 或者是 $0$。

---

## 作者：Chenxuhang_play (赞：0)

## 题目链接

<https://www.luogu.com.cn/problem/solution/CF1867B>

## 题目大意

给出一个长度为 $n$ 的 $01$ 串 $s$。只有存在一个长度也为 $n$ 的 $01$ 串 $l$ 使得对于所有的 $s_i$ 被 $s_i\oplus l_i$ 替换后得到的 $01$ 串是一个回文串时，才有数 $x$ 是好数。

对于给出的一组 $n,s$，你需要给出一个长度为 $n+1$ 的 $01$ 串 $t$,$t_i=1$ 当仅当 $i$ 是一个好数。注意，$t$ 从 $0$ 开始编号。

## 易错点 & 提示

+ 题目中 $\oplus$ 表示异或，同样表示异或的还有 xor。

+ 回文串的定义：从前往后与从后往前的串是一样的，不用人话说就是，当且仅当串 $N$ 有对于 $\forall i\in[0,L]$，有 $N_i=N_{L-i-1}$。

（对于回文串的定义，我看了一下其他题解，大部分并没有给出，这对一些基础较弱的OIer不是很友好，但是 floodfill 的题解给出的回文串定义我认为非常全面且合适，所以进行了借鉴，绝非抄袭）

## 思路

好吧实话说第一眼看题目的时候感觉还是蛮绕的……

在一个 $01$ 串 $N$ 中，设其长度为 $n$ （原则上来说题设中已经给出，但是为了减少不必要的混乱，在这里再次提出），对于 $i\in[0,L]$，设 $N_i \not= N_{L-i-1}$ 的组数为 $x$，那么操作次数 $\alpha$ 一定不小于 $x$。

当 $2 \mid x$ 时，显然，在已经确定了 $x$ 时，操作得到回文串的操作次数增加偶数次时，仍然可以实现，其方法为修改一对 $N_i = N_{L-i-1}$。设 $N_i = N_{L-i-1}$ 的组数为 $y$，那么

$$
\alpha=x+2k,k\in[0,y]
$$

当 $2 \nmid x$ 时，注意到实际上只是多了一个中间的 $N_{(n+1)/2}$，该字符无论是 $0$ 还是 $1$，只要满足了前后回文，整个总串仍是回文串。同样设 $N_i = N_{L-i-1}$ 的组数为 $y$，那么

$$
\alpha=x+k,k\in[0,2y+1]
$$

---

## 作者：floodfill (赞：0)

## CF1867B XOR Palindromes 题解
### 题目大意
  给一个 $n$ 位 $01$ 串 $s$。数 $x$ 是好数，当且仅当存在 $n$ 位 $01$ 串 $l$ 使得 $s_i \operatorname{xor} l_i$ 产生的串 $N$ 是回文串。记串 $N$ 的长度为 $L$，严格地，我们认为串 $N$ 是回文串，当且仅当对于 $∀ i\in[0,L]$ 都有 $N_i=N_{L-i-1}$ 成立。

  你应当给出一个 $n+1$ 位 $01$ 串 $t$，满足：若第 $i(i\in[0,n+1])$ 位为 $1$，则数 $i$ 是好数，反之，数 $i$ 不是好数。
### 大致思路
记前后对称位置不同的对数为 $d$，剩下前后对称位置相同的对数为 $q$，那么显然最少要操作 $d$ 次，在此基础上把两个前后对称位置相同的也进行操作，所以就又增加了偶数次。操作次数
$$tot=d+p$$
其中 $p\in[0,2q], p\bmod 2=0$。

再考虑 $n$ 为奇数时。中间的一位可以操作或不操作，所以操作次数
$$tot=d+p$$
其中 $p\in[0,2q+1]$。

---

## 作者：__O_w_O__ (赞：0)

做法：统计前后对称位置不一样的对数，记为 $k$。统计剩下前后对称位置一样的数的对数，记为 $m$（如果 $n$ 为奇数，则最中间的一位不计入 $m$），那么在 $k$ 次的基础上，可以增加偶数次，即把两个对称位置一样的都改了，最多可以改到 $m$ 次，即 $k, k+2, k+4...k+m\times2$。

考虑 $n$ 为奇数的时候，最中间的一位可以改或不改，所以能成功地有 $k, k+1, k+3...k+m\times2+1$。

[通过记录](https://codeforces.com/problemset/submission/1867/275881234)

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

char s[N];
int ans[N];
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n;
        scanf("%d%s", &n, s + 1);
        int k = 0, m = 0;
        for (int i = 0; i <= n; i++) ans[i] = 0;
        for (int i = 1; i * 2 <= n; i++) {
            if (s[i] == s[n - i + 1]) k++;
            else m++;
        }
        for (int i = 0; i <= k; i++) {
            ans[m + i * 2] = 1;
            if (n % 2) ans[m + i * 2 + 1] = 1;
        }
        for (int i = 0; i <= n; i++) {
            printf("%d", ans[i]);
        }
        printf("\n");
    }
	return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1867B)

# 题意：

给定长度为 $n$ 的 $01$ 串 $p$，
定义 $x$ 为好数：找到一个长度为 $n$ 的 $01$ 串 $s$，其中含有 $x$ 个 $1$，使 $p$ 和 $s$ 逐位异或，得到一个回文串。

你需要输出一个长度为 $n+1$ 的串，针对第 $y$ 位，如果存在好数 $y$ 则输出 $1$，如果不存在则输出 $0$。

# 思路：

显然最低满足要把所有不对称的改过来，分奇偶讨论。

1. 当 $n$ 为偶数，我们观察本来已经对称的字符，每一对字符贡献为 $2$。

2. 当 $n$ 为奇数，除了上述贡献以外，我们发现中位字符对合法的每次答案贡献是 $1$ 或 $0$。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int t,n,c;
string s;
signed main(){
    cin>>t;
    while(t--){
        cin>>n>>s;
        c=0;
        for(int i=0;i<n/2;i++){
            if(s[i]!=s[n-1-i]){
                c++;
            }
        }
        for(int i=0;i<=n;i++){
            if(i<c){
                cout<<0;
                continue;
            }
            int c1=i-c;
            if(!c1){
                cout<<1;
                continue;
            }
            if(n%2){
                if(c1%2){
                    c1--;
                }
                if(c1<=(n-1)-c*2){
                    cout<<1;
                }else{
                    cout<<0;
                }
            }else{
                if(c1%2==0&&c1<=n-c*2){
                    cout<<1;
                }else{
                    cout<<0;
                }
            }
        }
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：lukepanpyz (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1867B)

## **题目大意**

给出一个二进制数 $s$，问是否有一个 $i(0 \le i \le |s|)$ 位二进制数 $l$ 异或 $s$ 的结果是一个回文数，并用 `0` 和 `1` 记录在一个字符串中并输出。

**异或（半加）** 是一种位运算。  
###### **运算法则**：两个数在二进制下，每一位相同则结果的那一位为 1，不相同则为 0。简单来说，异或就是**不进位的加法。（注意，是在二进制中。）**

## 思路

异或可以将每一位的 $1$ 变成 $0$ (异或 $1$)，$0$ 变成 $1$（异或 $1$），也可以让这位数保持不变（异或 $0$），也就是它可以任意改变二进制数中的任意几位数字。  
**因此题目可以转化为**：对于一个数 $i$，需要计算出是否能改变二进制数 $s$ 中的任意 $i$ 个数字使它变为一个回文（二进制）数。

那我们先从 $s$ 中的 `1` 入手。如果一个二进制字符串是回文串，那么左右的 `1` 都是对称的（第 $i(0 \le i < n)$ 个 `1` 都对应第 $n-i$ 个 `1`），当一个二进制数前后的 `1` 不对应时，它就不是一个回文串。  
例如 `1010001`，第 2 个位置的 `1` 和第 4 个位置的 `0` 不对称。

如果要将它构造成一个回文串，**至少需要修改的数字的个数 $sum$ 就是左右不对称的数对数量**，因为你至少要把每一个不对称的数对的其中一个数字改成和另一边的数字相等，才能达到左右数字对称。  
还拿 `1010001` 来举例，最少应将第 4 个位置的 `0` 改为 `1` 才能使它变成一个回文数。

1. 对于一个偶数位的二进制数，修改完不对称的数位后，可以将其他的对称的数对都改成另一个数字，一对数中有两个数字，因此 $sum+2,sum+4\dots$ 也都是答案，直到 $sum$ 超过对称的数对中数字的总数。
2. 对于一个奇数位的二进制数，因为数对可能存在只有一个数的情况，那么这也算是对称，所以可能的 $sum$ 的开始和结束条件和偶数位的一样，但是答案是逐次加 $1$ 的。

## 上代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n,cnt = 0;
		string s,ans = "";
		cin >> n >> s;
		for(int i = 0;i <= n;i++)
		{
			ans += '0';
		}
		for(int i = 0;i < s.size();i++)
		{
			if(s[i] == '1' && s[n - i - 1] == '0')
			{
				cnt++;
			}
		}
		if(s.size() % 2 == 0)
		{
			for(int i = cnt;i <= n - cnt;i += 2)
			{
				ans[i] = '1';
			}
		}
		else
		{
			for(int i = cnt;i <= n - cnt;i++)
			{
				ans[i] = '1';
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：kczw (赞：0)

# 题意
共 $t$ 组数据。

每组数据给定一个长 $n$ 的 $01$ 串 $s$，问对于 $i(0\le i\le n)$ 是否有长 $n$ 且有 $i$ 个 $1$ 的 $01$ 串 $l$ 使得 $s$ 按位异或 $l$ 后能得到一个回文串，若有输出 `1`，否则输出 `0`。
# 思路
定义翻转为 `0` 和 `1` 间互相转换的过程。不妨将 $l$ 串有 $x$ 个 $1$ 看作 $s$ 串中有 $x$ 位强制翻转。

注意到有词**回文串**，意为对于翻转过后的 $s$ 有 $s_i=s_{n-1-i}$。

这个时候就需要分类讨论了。

若 $n$ 为偶数。

若有 $s_i\ne s_{n-1-i}$，意为仅对于 $(i,n-1-i)$ 此二元组至少须一次翻转，于是易得 $Min=\sum_{i=0}^{\frac{n-2}{2}}[s_i\ne s_{n-1-i}]$ 为最小须输出 `1` 的值。

若有 $s_i=s_{n-1-i}$，说明二元组 $(i,n-1-i)$ 不须翻转便已满足条件的同时也可以翻转两次，所以 $Max=\sum_{i=0}^{\frac{n-2}{2}}[s_i=s_{n-1-i}]\times2+Min$ 就是最大的满足回文串条件的 $x$ 了。

对于 $Min$ 到 $Max$ 的增长，是由 $s_i=s_{n-1-i}$ 的情况可以多消耗两次翻转但是仍然满足回文串局部条件而做到的。这也说明，对于所有 $Min+2\times k\le Max(k\in N)$，都是满足输出 `1` 的条件的，同时其他数只能就输出 `0` 了。

若 $n$ 为奇数。

$n$ 为奇数时，大多皆类似于 $n$ 为偶数的情况，除了 $s_{\frac{n-1}{2}}$。$s_{\frac{n-1}{2}}$ 就是中间的字符，无论它是多少，都对最终的 $s$ 是否为回文串没有影响。

首先不难算出 $Min=\sum_{i=0}^{\frac{n-2}{2}}[s_i\ne s_{n-1-i}]$，同时得到 $Max=\sum_{i=0}^{\frac{n-2}{2}}[s_i=s_{n-1-i}]\times2+Min+1$，这里比偶数的 $Max$ 多一个 $s_{\frac{n-1}{2}}$ 所贡献的 $1$。

其次，刚刚对于偶数 $n$ 的 $[Min,Max]$ 内答案的推导可以套用在此处，但是因为有 $s_{\frac{n-1}{2}}$，于是 $Min+2\times k\le Max(k\in N)$ 和 $Min+2\times k+1\le Max(k\in N)$ 都是满足输出 `1` 的条件的，合并一下易得 $[Min,Max]$ 皆满足输出 `1` 的条件。

综上所述：

- 对于偶数 $n$，所有 $Min\le x\le Max$ 且 $Min \equiv x\pmod 2$，输出 `1`，其他输出 `0`。

- 对于奇数 $n$，对于 $Min\le x\le Max$，输出 `1`，其他输出 `0`。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int t,n,mn;
void put0(){for(int i=0;i<mn;i++)printf("0");}
char s[N];
main(){
    scanf("%lld",&t);
    while(t--){
        mn=0;
        scanf("%lld%s",&n,s);
        for(int i=0;i<n/2;i++)
            mn+=(s[i]!=s[n-1-i]);
        if(n&1){
            put0();
            for(int i=0;i<n-mn-mn+1;i++)printf("1");
            put0();
        }
        else{
            put0();
            for(int i=0;i<=(n-mn-mn)/2;i++){
                printf("1");
                if(i<(n-mn-mn)/2)printf("0");
            }
            put0();
        }
        puts("");
    }
    return 0;
}
```

---

## 作者：Cloxier (赞：0)

其实挺好理解的，如果我们想将一个字符串变为回文字符串，对于长度为偶数的字符串，必须考虑使前后对应位置的字符两两匹配；而对于长度为奇数的字符串，我们是否操作最中间的字符对结果没有影响。

那么我们先统计一下原字符串所需要的操作次数，然后对于每个 $t_i$ 都根据奇偶性判断是否合法，从而输出 $0$ 或 $1$ 得到最终串 $t$ 即可解决这个问题。

这里附上赛时 AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int T;
	cin >> T;
	while(T--)
	{
		int n;
		cin >> n;
		string s;
		cin >> s;
		int sum = 0;
		for(int i = 0; i < n / 2; i++)
		{
			if(s[i] != s[n-i-1])
			{
				sum++;
			}
		}
		for(int i = 0; i <= n; i++)
		{
			if(i < sum)
			{
				cout << '0';
				continue;
			}
        		int tmp = i - sum;
			if(n % 2 == 0)
			{
				if(tmp % 2 == 0 && tmp <= n - sum * 2)
					cout << '1';
				else
					cout << '0';
				continue;
			}
			else
			{
				if(tmp % 2 != 0)
					tmp--;
				if(tmp <= (n - 1) - sum * 2)
					cout << '1';
				else
					cout << '0';
			}
		}
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：RemiliaScar1et (赞：0)

## XOR Palindromes 

### 题目大意

给出一个长度为 $n$ 的 $01$ 串(只含 $0,1$ 的字符串) $s$。定义一个数 $x$ 是好数，当仅当存在一个长度也为 $n$ 的 $01$ 串 $l$ 使得对于所有的 $s_i$ 被 $s_i\oplus l_i$ 替换后得到的 $01$ 串是一个回文串。

对于给出的一组 $n,s$ ，你需要给出一个长度为 $n+1$ 的 $01$ 串 $t$ ，$t_i=1$ 当仅当 $i$ 是一个好数。**注意，$t$ 从 $0$ 开始编号**

题目中 $\oplus$ 表示异或。

回文串指正着读反着读都相同的字符串，比如 $0110,01010,1111$ 都是回文串。

---

首先我们注意到，一个 $s_i\oplus 0$ 不会改变 $s_i$ 的大小，$\oplus 1$ 相当于给 $s_i$ 取反。

所以其实好数就是存在一种方案对 $s$ 的不同位置修改 $x$ 次之后 $s$ 可以变成一个回文串。

首先我们可以想到 **求出最少的修改次数 $x_0$，那么 $n-x_0$ 也一定满足条件**。因为修改 $1$ 和修改 $0$ 的方案是对称的：我们使用修改 $x_0$ 次的方案修改后再对整个串取反，将与 $x_0$ 的方案抵消的修改次数减去就是 $n-x_i$。这也意味着当 $x<x0$ 或 $x>n-x_0$ 时一定不满足条件。

其次我们可以想到，在上面 **范围内的任意 $x_k=2k+x_0 (k\in N)$ 也是可以成立** 的。因为可以在花 $x_0$ 的次数将 $s$ 操作成回文串之后花偶数次操作 **在两边对称修改** ，得到的还是回文串。

继续思考就会发现问题：如果 $x_k$ 构造完回文串之后还要奇数次操作呢？

对于一个长度 $n$ 为奇数的 $s$，因为它的对称中心刚好是 $\frac {n} {2}+1$ 位，所以当我们构建完回文串还剩奇数次操作时，可以 **对这个中心操作一次，转化为偶数次操作** 的情况；但是 $n$ **为偶数时无法进行这样的转化**，也就无法对称操作，那么 $x_k$ 就不是好数。

所以，我们可以按照如下方法判断：

首先求出将 $s$ 修改为回文串所需要的最小次数 $x_0$:将 $s$ 对折比较，找出不同位置数量即可。

然后对于一个整数 $x$ 判断：

- 若 $x$ 在范围 $[x_0,n-x_0]$ 内且 $n$ 是奇数时，$x$ 是好数。

- 若 $x$ 在范围 $[x_0,n-x_0]$ 内且 $n$ 是偶数时，如果 $x$ 的奇偶性与 $x_0$ 相同，则 $x$ 是好数。

- 其他都不是好数。

考场code:

```cpp

#include <bits/stdc++.h>
using namespace std;

const int N=1e5+10;

int s[N];

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		char tmp[N];
		scanf("%s",tmp);
		for(int i=0;i<n;i++)
		{
			s[i+1]=(int)(tmp[i]=='1');
		}
		int h1=0;
		for(int i=1;i<=n/2;i++)
			if(s[i]!=s[n-i+1]) h1++;
		if(n&1)//奇数
		{
			for(int i=0;i<=n;i++)
				if(h1<=i&&i<=n-h1) printf("1");
			else printf("0");
		}
		else {//偶数
			for(int i=0;i<=n;i++)
				if(h1<=i&&i<=n-h1&&(i&1)==(h1&1)) printf("1");
				else printf("0");
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Natori (赞：0)

>[CF1867B XOR Palindromes](https://www.luogu.com.cn/problem/CF1867B)

这里是一个关于 $n$ 的奇偶性分类讨论的做法。

------------
设最终的答案序列为 $\{ans_{n+1}\}$，它由 $0,1$ 组成。

首先计算出原序列中有序数对 $(i,n-i+1)$ 的个数，使得 $s_i \not= s_{n-i+1}$。记这个数为 $cnt$，显然 $cnt \le \lfloor\dfrac{n}{2}\rfloor$。

此时容易解决 $n$ 为奇数的情况。结论是：对于 $i \in [cnt,n-cnt]$，$ans_i=1$，否则 $ans_i=0$。

因为只需要让原本不匹配的 $cnt$ 对位置匹配。对于 $i>cnt$，如果 $i-cnt$ 为偶数，则可以让原本匹配的两个位置上的数同时取异或，显然这样仍然匹配。否则，可以让整个序列的中点上的数取异或，这样不影响其他位置，剩下的就与 $i-cnt$ 为偶数时相同。

但对于 $i>n-cnt$，上面的策略就不适用了。因为此时必然会将已经匹配好的一对位置变得不再匹配。

类比之前的做法，考虑 $n$ 为偶数的情况。

注意到 $n$ 为偶数与 $n$ 为奇数最大的区别就是没有了中间点，因此除开必须改变的 $cnt$ 对位置上的数，改变的数的数量必须为偶数。这相当于 $\forall i \in [cnt,n-cnt],i-cnt$ 为偶数。这又等价于在区间 $[cnt,n-cnt]$ 中，$ans$ 隔一个为 $1$。

于是在 $\mathcal{O}(n)$ 的时间复杂度内解决了问题。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool Mbegin;
namespace Fast_In_Out{
	char buf[1<<21],*P1=buf,*P2=buf;
	#define gc getchar()
	int read(){
		int f=1,x=0;
		char c=gc;
		while(c<'0'||c>'9'){
			if(c=='-')
			    f=-1;
			c=gc;
		}
		while(c>='0'&&c<='9'){
			x=x*10+c-'0';
			c=gc;
		}
		return f*x;
	}
	void write(int x){
		if(x<0)
			x=-x,putchar('-');
		if(x>9)
			write(x/10);
		putchar(x%10+'0');
	}
	#undef gc
}
using namespace Fast_In_Out;
const int N=1e5+8;
int n;
char str[N];
namespace odd{
	bool ans[N];
	void solve(){
		for(int i=0;i<=n;i++)
			ans[i]=0;
		int cnt=0;
		for(int i=1;i<=n/2;i++)
			if(str[i]!=str[n-i+1])
				cnt++;
		for(int i=cnt;i<=n-cnt;i++)
			ans[i]=1;
		for(int i=0;i<=n;i++)
			write(ans[i]);
		putchar('\n');
	}
}
namespace even{
	bool ans[N];
	void solve(){
		for(int i=0;i<=n;i++)
			ans[i]=0;
		int cnt=0;
		for(int i=1;i<=n/2;i++)
			if(str[i]!=str[n-i+1])
				cnt++;
		for(int i=cnt;i<=n-cnt;i+=2)
			ans[i]=1;
		for(int i=0;i<=n;i++)
			write(ans[i]);
		putchar('\n');
	}
}
void solve(){
	n=read();
	scanf("%s",str+1);
	if(n%2==1)
		odd::solve();
	else
		even::solve();
}
bool Mend;
int main(){
	fprintf(stderr,"%.3lf MB\n\n\n",(&Mbegin-&Mend)/1048576.0);
	int testnum=read();
	while(testnum--)
		solve();
	fprintf(stderr,"\n\n\n%.0lf ms",1e3*clock()/CLOCKS_PER_SEC);
	return 0;
}
```

---

