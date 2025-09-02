# Kachina's Favorite Binary String

## 题目描述

这是一道交互题。

卡齐娜有一个长为 $n$ 的 01 串 $s$。她定义 $f(l,r)$ 为子段 $s_ls_{l+1}\cdots s_r$ 中等于 $\texttt{01}$ 的子序列的个数。子序列不要求连续；两个位置不同的子序列被认为是 **不同** 的，即便它们含有相同的字符序列。

你需要通过向卡齐娜提问来猜出 $s$。每次提问，你可以选择两个下标 $l,r(1\le l < r\le n)$，询问她 $f(l,r)$ 的值。你最多提问 $n$ 次。如果 $s$ 不可能在 $n$ 次询问内确定，输出 $\texttt{IMPOSSIBLE}$。

## 说明/提示

**第一个样例：**

第一次提问中，你询问卡齐娜 $f(1,5)$ 的值，她向输入流中返回 $4$。

第二次提问中，你询问卡齐娜 $f(2,4)$ 的值。因为在 $\texttt{100}$ 中没有等于 $\texttt{01}$ 的子序列，她向输入流中返回 $0$。

提问四次后，你输出正确答案 $\texttt{01001}$。

**第二个样例：**

第一次提问中，你询问卡齐娜 $f(1,2)$ 的值，她向输入流中返回 $0$。

注意到你除了 $\texttt{? 1 2}$ 提不出别的问题了，但 01 串 $\texttt{00}$ 和 $\texttt{11}$ 的答案都是 $0$，无法确定唯一答案，所以输出 $\texttt{IMPOSSIBLE}$。

样例仅用于展示交互格式，不代表正解方法。

## 样例 #1

### 输入

```
2
5

4

0

1

2

2

0```

### 输出

```
? 1 5

? 2 4

? 4 5

? 3 5

! 01001

? 1 2

! IMPOSSIBLE```

# 题解

## 作者：_mi_ka_ (赞：4)

~~是可爱的卡齐娜耶！！！~~

## 题目大意

交互题（不会交互题的可以去做洛谷的板子 [P1733](https://www.luogu.com.cn/problem/P1733)），$T$ 组交互，每次交互库会指定一个长度为 $n$ 的 $01$ 字符串（只由 $0$ 和 $1$ 组成），你最多询问 $n$ 次，每次询问你给出一个区间 $[l,r]$，交互库会给出指定字符串的 `01` 子串的个数（`0` 和 `1` 可以不相连，且 `0` 和 `1` 只要有其一位置不同都将会认为成不同的 `01` 子串）。在最多 $n$ 次询问后，确定这个字符串，或者输出 IMPOSSIBLE 代表无论怎样 $n$ 次询问都不能确定这个字符串。

## 解题思路

考虑字符串中的每个字符都要得到，每次询问至少要确定一个字符。要实现这种询问，**考虑询问 $n-1$ 次，第 $i$ 次询问询问区间 $[1,1+i]$**，当 $i$ 增大时，如果答案变大，说明这一位是 `1` 且答案的增量 $\Delta ans$ 为当前位之前的 `0` 的个数。如果答案不变，说明这一位为 `0` 或者这一位之前 `0` 的个数为 $0$。

假如说在第 $i$ 次询问 $[1,i+1]$ 的答案 $ans_i$ 第一次非零，那么第 $i+1$ 位为 `1` 并且再次之前一定只有一种可能：

$$\underbrace{1\dots1}_{i-ans_i\ 个}\underbrace{0\dots0}_{ans_i\ 个}$$

再之后，`0` 的个数被确定，记录一下当前零的个数，那么如果之后答案不变，当位就一定是 `0`，更新当前零的个数，如果答案变大，变大的一定是前面的零的个数，如果不是，那么这个序列**不可能存在（不合法）**，直接输出 IMPOSSIBLE 即可。

进行完这 $n-1$ 次询问后，只有三种情况：

- 这个序列已经被确定
- 这个序列不合法，已经输出 IMPOSSIBLE
- 这个序列从头到尾交互库给出的所有数都是 $0$，此时这个序列肯定是由 $k$ 个连续的 `1` 和 $n-k$ 个连续的 `0` 拼接而成，其中 $0\le k\le n$，此时再进行任何区间的询问得到的答案都肯定是 $0$，第 $n$ 次询问可有可无，都无法确定序列，输出 IMPOSSIBLE。

## AC Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#include<queue>
#include<vector>
using namespace std;
int T,n;
int re()//防止作弊不放快读快写
void wr(int x)
signed main()
{
	T=re();
	while(T--)
	{
		n=re();
		string s="";//当前确定的序列 
		int last=0,zero=0;//前一个的答案和当前 0 的个数 
		for(int i=2;i<=n;i++)
		{
			printf("? 1 %d\n",i);
			fflush(stdout);
			int x=re();
			if(last==0)
			{
				if(x==0)
					continue;//如果 x 不等于 0，则此处为 ans 的第一次非零，此时序列确定 
				for(int j=1;j<=i-1-x;j++)
					s+='1';
				for(int j=1;j<=x;j++)
					s+='0';
				s+='1';
				zero=last=x;
			}
			else
			{
				int cha=x-last;//ans 的增量 
				if(cha==0)
					zero++,s+='0';
				else if(cha==zero)
					s+='1',last=x;
				else//不合法 
					break;
			}
		}
		if(s.length()!=n)//后两种情况 
			puts("! IMPOSSIBLE");
		else
			cout<<"! "<<s<<'\n';
		fflush(stdout);
	}
	return 0;
}
```

---

## 作者：postpone (赞：1)

先问一遍整个区间 $01$ 子序列的数量。如果没有，那序列无法确定：形如 $11$、$10$ 和 $00$ 都不包含 $01$ 子序列。

然后枚举 $i$ 从 $2$ 到 $n-1$，每次询问 $[i, n]$ 中 01 子序列的数量，一步步缩小区间。

对于询问的结果，进行如下分类讨论：

1. 若本次询问的结果与上次询问相同，说明位置 $i-1$ 为 $1$；

2. 若不同且不为 $0$，说明位置 $i-1$ 为 $0$；

3. 若结果为 $0$，那么剩下所有位置都确定了——左边是连续 $x$ 个 $1$，其中 $x$ 为上次询问的结果，右边全是 $0$。

```cpp
ll query(int l, int r) {
    if (r - l <= 1) {
        return 0;
    }
    cout << "? " << l + 1 << " " << r << endl;
    ll x;
    cin >> x;
    return x;
}
 
void solve() {
    int n;
    cin >> n;
 
    int x = query(0, n);
    if (x == 0) {
        cout << "! IMPOSSIBLE" << endl;
        return;
    }
 
    string s{};
    for (int i = 1; i < n; i++) {
        ll y = query(i, n);
        if (y == x) {
            s += "1";
        } else {
            s += "0";
            if (y == 0) {
                s += string(x, '1');
                s.resize(n, '0');
                break;
            }
            x = y;
        }
    }
    cout << "! " << s << endl;
}
```

---

## 作者：Hanggoash (赞：1)

# CF2037E 题解

## 题意

给定一个长度为 $n$ 的 $01$ 串，定义 $f(l,r)$ 为 $l$ 到 $r$ 区间内 $01$ **子序列**的数量，通过最多 $n$ 次交互，确定这个 $01$ 串的构成。

## 分析

可以从莫队的思想，也就是**增量**，来思考如何解决。

如果说我们已经知道了 $f(l,r)=ans$，接下来我们询问 $f(l,r+1)$ 的值，相当于往 $[l,r]$ 的串的后面接了一个字符上去。

- 如果这一次询问的答案不同于 $ans$，说明有新的 $01$ 子序列产生，那么一定是引入了一个 $1$ 导致的。
- 如果这一次询问的答案和 $ans$ 相同，那么有两种情况。
  1. $r+1$ 位引入的是一个 $0$。
  2. $r+1$ 位引入的是一个 $1$，但是 $[l,r]$ 内一个 $0$ 也没有。

为了方便，我们直接利用上述原理从左到右构建这个串，也就是从小到大地询问 $f(1,i),2\le i\le n$ 的答案。

那么首先需处理第一个答案非零的位置，这说明当前这一位一定是 $1$，并且前面是 $11...100..0$ 的结构（因为前面的询问得到的答案都是 $0$ ），具体来说，前面 $0$ 的个数就是当前这一次询问的答案（注意前面不一定有 $1$，但一定有 $0$）。

接着我们就可以继续安心地询问了，由于我们确保了已经有若干个 $0$ 出现在串中，那么如果当前得到的答案和上一次相同，当前位就一定是 $0$；否则就是 $1$。

唯一一种无解的情况，就是我们始终没有询问到一个非零的答案，这样的话这个串可能是 $1111..1111$，或者 $000..000$，亦或是 $11..11000...000$，所以是无法确定的。

## Code

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
inline int q(int l,int r){cout<<"? "<<l<<' '<<r<<endl;int ans;cin>>ans;return ans;}
char s[100010];
inline void solve()
{
    cin>>n;
    int p=2,las_ans;
    while(p<=n)
    {
        int ans=q(1,p);
        if(ans!=0)
        {
            s[p]='1';
            for(int i=1;i<=p-1-ans;++i)s[i]='1';
            for(int i=p-ans;i<=p-1;++i)s[i]='0';
            las_ans=ans;
            p++;
            goto NEXTSTEP;
        }
        p++;
    }
    cout<<"! IMPOSSIBLE"<<endl;return ;
    NEXTSTEP:;
    while(p<=n)
    {
        int ans=q(1,p);
        if(ans==las_ans)
        {
            s[p]='0';
        }
        else 
        {
            s[p]='1';
            las_ans=ans;
        }
        p++;
    }
    cout<<"! ";
    for(int i=1;i<=n;++i)cout<<s[i];
    cout<<endl;
}
signed main()
{
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：Chen_Johnny (赞：0)

## 理解题意
### 什么是交互题？
“交互题”指的是在运行过程中，你可以问一些问题，然后他会给你答案。比如你要猜一个数，那么你就二分对不对？然后你告诉他你猜的数，他回答你你猜的是大了还是小了。
### 交互题的注意事项
每一次问问题之后，不要忘记刷新输出流，否则会出现 ILE。其中最简单的方式就是行末打在输出的时候加一个：
```cpp
<< endl;
```
### 题意
Kachina 心里想了一个 $01$ 串，然后你去询问这个字串第 $i$ 到第 $j$ 位的 $01$ 字串的数量，最多问 $n$ 次，请你猜出这个字串。
## 思路
### 1. 分析 $f$ 函数
根据题意，$f_{(i,j)}$ 函数代表 $i$ 到第 $j$ 位的 $01$ 字串的数量。

显然，$f_{(i,j)}$ 随着 $j$ 的增加而增加或不变。那么，如果第 $j$ 位是 $1$，则显然：$f_{(i,j - 1)} < f_{(i,j)}$,如果是 $0$ 则 $f_{(i,j - 1)} = f_{(i,j)}$，所以我们得到了我们的策略：分别询问 $f(1,i)$ 的值。
### 2. $f$ 函数为 $0$ 的情况
显然，当且仅当一个字串是很多 $1$ 后面接很多 $0$ 的一个字符串。而现在，我们并不能使用上面的规则。
#### 1°$f$ 函数值全为 $0$
如果所有 $f$ 均为 $0$，则他的字符串也是由很多 $1$ 后面接很多 $0$ 组成的，而我们并没有办法判断 $1,0$ 的数量，可能是 $1$ 个 $1$ 后面接 $5$ 个 $0$……

所以我们输出 Imposible。
#### 2° $f$ 函数前 $k$ 个为 $0$
那就是前 $k$ 个数为前面说的字符串。虽然我们仅仅通过这几个无法判断前面 $1,0$ 的数量，但是,$f_{(1,k+1)}$ 就是前面 $0$ 的数量，为什么？

因为既然 $f_{(1,k+1)}$, 它字符串中的值就为 $1$, 而 $01$ 字串的 $1$ 只能是第 $k+1$ 个位的 $1$。

因此，我们完全可以重组前面 $k$ 个数。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std; 
void solve () {
    int n; cin >> n;
    int i, v;
    for (i = 2; i <= n; i ++) {
        cout << "? " << 1 << " " << i << endl;
    	cin >> v;
        if (v != 0) break;
    }
    if (i == n + 1) {
        cout << "! IMPOSSIBLE" << endl;
        return;
    } string ans;
    for (int j = 1; j <= i - v - 1; j ++) ans += '1';
    for (int j = 1; j <= v; j ++) ans += '0';
    ans += '1';
    for (int j = i + 1; j <= n; j ++) {
    	int t;
       	cout << "? " << 1 << " " << j << endl;
       	cin >> t;
        if (t > v) {
            v = t;
            ans += '1';
        }else ans += '0';
    }
    cout << "! " << ans << endl;
}
int main () {
    int t; cin >> t;
    while (t --) solve (); 
    return 0;
}
```

---

## 作者：zhouruoheng (赞：0)

交互题，记得用 `endl` 或者 `cout.flush()` 清空缓存区。

询问次数最大为 $n$，设 $k_i=f(1,i)$ $(2 \le i \le n)$。  
先考虑无解的情况，显然是 $k_n=0$ 时不能确定答案。  
然后遍历 $k$，考虑如果 $s_i=0$，则一定有 $k_i=k_{i-1}$。所以当 $k_i>k{i-1}$ 时，$s_i=1$。但这样有一个问题，如果 $s$ 为 $\mathtt{111\dots000\dots1\dots}$，那么开头的 $1$ 也都不会有贡献。所以找到第一个不等于 $0$ 的 $k_i$，说明 $[1,i-1]$ 中有 $k_i$ 个 $0$，所以开头就有 $i-1-k_i$ 个 $1$。

``` cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <map>

using namespace std;
typedef long long ll;
const int N=1e4+5;
int n;
int s[N];
int query(int l,int r)
{
    int x;
    cout<<"? "<<l<<" "<<r<<' '<<endl;
    cin>>x;
    return x;
}
int k[N];
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) s[i]=0;
    for(int i=2;i<=n;i++) k[i]=query(1,i);
    if(k[n]==0)
    {
        cout<<"! IMPOSSIBLE "<<endl;
        return ;
    }
    for(int i=2;i<=n;i++) if(k[i]>k[i-1]) s[i]=1;
    for(int i=2;i<=n;i++)
        if(s[i])
        {
            for(int j=1;j<=i-1-k[i];j++) s[j]=1;
            break;
        }
    cout<<"! "; 
    for(int i=1;i<=n;i++) cout<<s[i];
    cout<<' '<<endl;
}
int main ()
{
    #ifndef ONLINE_JUDGE 
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：Melo_qwq (赞：0)

不错的题。

首先，不能这么做：

- 尝试把原来的序列分成若干个小序列。

- 尝试对小序列进行大分讨。

这样做的不足之处：

- 分类讨论情况太多了，询问次数会超。

- 断成若干个小序列，等于忽略了不同序列之间的条件，导致答案错误。

我们发现最多询问 $n$ 次，那么整体就是线性的，我们不妨考虑如何 $\Theta(n)$ 地进行推导。接下来设 $f(l,r)$ 表示对 $[l,r]$ 的询问。

可以发现如果 $f(1,i)=0$ 但是 $f(1,i + 1)=k,k>0$ 的话，我们可以得到如下结论：

- 由于 $f(1,i + 1)\ne 0$，所以 $[1,i]$ 中一定存在 $0$。
- 由于 $f(1,i)=0$，那么这一段一定没有任何一个 $0$ 在 $1$ 的前面。

综上，我们可以得出：此时 $[1,i]$ 一定是由一段前缀的 $1$ 和一段后缀的 $0$ 组成，可以没有 $1$。

那么后缀的 $0$ 的长度是多少呢？可以发现，如果 $i+1$ 仍然是 $0$，那么 $f(1,i+1)=0$，所以位置 $i+1$ 一定是 $1$；由于 $f(1,i+1)=k$，那么意味着（注意到只有这个 $1$ 才有机会和前面的 $0$ 匹配）这个 $1$ 和 $k$ 个 $0$ 匹配了，所以后缀的 $0$ 的长度是 $k$，然后顺便直接把前面的 $1$ 填进去就好了。

之后该怎么办呢？注意到另一件事，就是左端点不动，右端点单增时，答案不可能变小，那么我们找到第一个满足上述条件的位置 $i$，之后对于 $i$ 后面的位置 $j$：

- 如果 $f(1,j)=f(1,j-1)$，那么说明 $j$ 这个位置一定无法和前面配对，由于我们的 $i$ 符合刚才说的条件，那么此时 $j$ 前面一定有 $0$ 存在，如果它没有配成，说明这个位置一定是 $0$（要是是 $1$ 一定可以和前面的 $0$ 做出贡献）。

- 反之则为 $1$。

那么我们直接再扫一遍就可以了。

什么时候没有唯一解呢？就是没有找到 $i$ 的时候，很好理解。

代码：


```cpp
#include <bits/stdc++.h>
#define f(i ,m ,n ,x) for (int i = (m) ; i <= (n) ; i += (x))
using std :: cin ; using std :: cout ; using std :: endl ;
int t ,n ,ch[10007] ; 
int main () {
	cin >> t ;
	while (t --) {
		cin >> n ;
		int ans = 0 ; bool flag (0) ;
		cout << "? " << 1 << ' ' << 2 << endl ;
		cin >> ans ;
		if (ans == 1) { ch[1] = 0 , ch[2] = 1 ,flag = true ;}
		f (i ,3 ,n ,1) {
			cout << "? " << 1 << ' ' << i << endl ;
			int res ; cin >> res ;
			if (flag == false) {
				if (res ^ 0) {
					f (j ,1 ,i - 1 - res ,1) ch[j] = 1 ;
					f (j ,i - res ,i - 1 ,1) ch[j] = 0 ;
					ch[i] = 1 , flag = true ;
				} 
				ans = res ;
			} else {
				if (res == ans) ch[i] = 0 ;
				else ch[i] = 1 ;
				ans = res ;
			}
		}
		if (ans == 0) cout << "! IMPOSSIBLE" << endl ;
		else {
			cout << "! " ;
			f (i ,1 ,n ,1) cout << ch[i] ; cout << endl ;
		}
	}
	return 0 ;
}
```

---

