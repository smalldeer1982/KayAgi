# [GCPC 2023] German Conference for Public Counting

## 题目描述

Greta 热爱计数。她一年中的每一天都在练习。
根据季节不同，她会数落叶、雨滴、雪花，甚至新长出的嫩叶。然而，夏天有一个活动胜过一切：德国公众计数大会（GCPC）。

在这个活动中，Greta 遇到了来自全国各地的计数爱好者，进行为期一周的计数...他们一起参加“迷人的竞技性公众计数”和“盛大的混乱公共计数”。在临近结束前，他们都试图赢得“公众计数金杯”。她最喜欢的是“温和平静公众计数”：人群在沉默中计数，试图和谐同步，力求在同一精确时刻达到目标数字。

![](https://cdn.luogu.com.cn/upload/image_hosting/k9laqt9y.png)

:::align{center}
图 G.1: 工作人员举起数字牌用来显示倒计时。
:::

为了增强紧张感并为“温和平静公共计数”做准备，GCPC 主办方计划以无声倒计时开场。舞台上的工作人员将随时通过举起数字牌来显示当前数字（如图 G.1）。每个牌子只显示一个十进制数字。大于 $9$ 的数字需要通过并列举起多个牌子来展示。每个数字都使用尽可能少的牌子展示，且不会在左侧补零。这样，舞台上的人将从 $n$ 开始展示，依次显示 $n, n-1, n-2, \dots$ 直到最终显示 $0$。由于 GCPC 即将举行，主办方希望尽快完成准备工作。请问他们至少需要准备多少个数字牌才能完成从 $n$ 到 $0$ 的整个倒计时？

## 说明/提示

在第一个样例中，组织者需要数字 $0$ 到 $5$ 各一个，共 $6$ 个数字牌。在第二个样例中，除数字 $1$ 外每个数字需要一个数字牌，数字 $1$ 需要两个数字牌，总共需要 $9+2=11$ 个数字牌。

## 样例 #1

### 输入

```
5```

### 输出

```
6```

## 样例 #2

### 输入

```
20```

### 输出

```
11```

## 样例 #3

### 输入

```
44```

### 输出

```
14```

## 样例 #4

### 输入

```
271828182```

### 输出

```
82```

## 样例 #5

### 输入

```
314159265```

### 输出

```
82```

# 题解

## 作者：__szh_DNCB__ (赞：4)

蒟蒻的第九篇题解。


我们假设一个 $k$ 位数 $n$ 从左往右每一位数字分别记作 $n_0,n_1,\cdots,n_{k-1}$。

文中 $p(n)$ 表示对一个多位数 $n$ 从左向右遍历所出现的第一次 $n_i ≠ n_{i+1}$ 时 $n_{i+1}$ 是否大于 $n_i$。若是则 $p(n)=1$，不是则 $p(n)=0$。特别地，如果一个 $n$ 所有数位都相等，即 $n_0 = n_1 = \cdots = n_{k-1}$ 时，规定 $p(n)=-1$。

那么我们可以分为以下三种情况讨论：

+ $p(n)=-1$。这种时候容易想到需要的数字牌有 $k-1$ 个 $0$ 到 $9$，和另外的 $n_0$ 个数字牌（数值从 $1$ 到 $n_0$）
+ $p(n)=1$。容易想到与 $p(n)=1$ 时情况完全相同。
+ $p(n)=0$。则需要 $k-1$ 个 $0$ 到 $9$，和另外的 $n_0-1$ 张数字牌，数值为 $1$ 至 $n_0-1$。

按照以上思路进行模拟即可。需要注意到如果 $1 \le n < 10$，则直接输出 $n+1$。这一点需要进行特判。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin >> n;
	string st_n = to_string(n);
	int len = st_n.length();
	int firstly = st_n[0];
	int big = -1;
	if (len == 1){
		cout << n+1;
		return 0;
	}
	for (int i=0;i<len-1;i++){
		if (st_n[i+1] > st_n[i]){
			big = 1;
			break;
		}
		else if (st_n[i+1] < st_n[i]){
			big = 0;
			break;
		}
	}
	if (big == -1){
		cout << (len-1)*10+(st_n[0]-'0');
	}else if (big == 1){
		cout << (len-1)*10+(st_n[0]-'0');
	}else{
		cout << (len-1)*10+(st_n[0]-'0'-1);
	}
}
```

---

## 作者：volatile (赞：4)

# 思路

将 $n$ 作为字符串。

首先特判 $n$ 为一位数，那么直接输出 $n+1$ 即可，加一是因为包括 $0$。

容易发现，随便举一个例子：$1919810$，则一定会存在 $111111$、$222222$ 一直到 $999999$，如果记 $n$ 的长度为 $l$，则一定会需要准备 $(l-1)\times10$ 个数字（考虑到 $1000000$）。然后再看第一位，记为 $n_0$（以下同理），一定会需要先准备 $n_0-1$ 个数字，至于 $n_0$ 这个数是否要准备，可以先分类讨论。

如果 $n_0<n_1$（$1<9$），则也一定会另外存在 $\overline{n_0n_0\dots{n_0}}$ 这样的组合（如 $1111111$），此时答案应该加一。

否则，如果 $n_0=n_1$，此时从 $n_2$ 开始遍历，如果 存在 $n_i$ 小于 $n_0$，则一定不会有 $\overline{n_0n_0\dots{n_0}}$ 这种情况，反之，答案加一。

然后就这么过了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string n;
    cin>>n;
    if(n.size()==1) cout<<n[0]-'0'+1;
    else{
        int ans=n[0]-'0'+(n.size()-1)*10-1;
        if(n[1]>n[0]) ans++;
        else if(n[1]==n[0]){
            ans++;
            for(int i=2;i<n.size();i++){
                if(n[i]<n[0]){
                    ans--;
                    break;
                }
            }
        }
        cout<<ans;
    }
    return 0;
}
```

---

## 作者：DFs_YYDS (赞：3)

# 题目大意
给你一个数字 $n$，问你至少需要多少个数字牌才能表示出从 $n$ 到 $0$ 的所有数。
# 具体思路
显然，一个数字只要不是多次出现在同一个数字，就可以重复使用。例如 $14$ 和 $514$ 中的 $1$ 可以是同一个数字牌，因此只需要一个。但是 $114$ 中的 $1$ 出现了两次，至少需要两个数字牌。

因此，每一个数字需要的数字牌数量就应该是它在 $0$ 到 $n$ 中的所有数字中出现的该数字最多的数字中出现的次数。

举个例子，数字 $1$ 在 $0$ 到 $114514$ 中需要数字牌的数量为是 $6$，也就是 $111111$。

同样的场景，$2$ 需要的数字牌数量只有 $5$，因为 $222222$ 不在范围内，最多的是 $22222$。

具体代码思路就出来了。

我们遍历每个数字，看把 $n$ 的每一位数字都换成这个数字是否在范围内。比如 $n$ 为 $1919810$ 时，遍历 $1$ 时发现 $1111111$ 在范围内，则 $1$ 需要的数量为 $7$（$n$ 的位数）。遍历 $2$ 时发现 $2222222$ 不在范围内，则 $2$ 需要的数量为 $6$（$n$ 的位数减一）。

# 完整代码
好了，我们可以写出代码了。

注意 $0$ 的情况，因为数字首位不能为 $0$，所以 $0$ 的数量一定是 $n$ 的位数减一（$n$ 的位数为 $1$ 时除外，最少需要一个）。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int ans,n;
int main(){
	cin>>s;	//用字符串处理方便一点。 
	n=s.size();
	ans=max(n-1,1);//如上，处理0。 
	for(int i=1;i<10;i++){
		string x(n,i+'0');//在定义的时候赋值为n个i。 
		//判断是否在范围内。 
		if(x>s)ans+=n-1; 
		else ans+=n;
	}
	cout<<ans;
	return 0;//完结撒花！ 
}
```

---

## 作者：qzyz_ymh (赞：2)

# 题目大意
题目大意非常简单：题目给出一个正整数 $n$，问从 $1$ 到 $n$ 至少需要多少个数字牌。（$n \le 10^9$）。

说明：组成一个 $12345$，需要 $1,2,3,4,5$ 的牌子各一张。组成 $1111$，需要 $4$ 张数字 $1$ 的牌子。

# 思路

不难发现若 $n$ 是一个 $m$ 位的正整数，那 $0 \sim 9$ 的数字牌前面一定会各用到 $m-1$ 个，若 $n$ 会大于 $11111\cdots，22222\cdots，33333\cdots$ 之类的有 $m$ 个相同数字牌组成的数，就把对应数字牌的数量加上去。

其中我们可以用 $\log 10()$ 来算出 $n$ 的位数，用 $\frac{n}{11111\cdots}$ 来算出需要额外添加的数字牌的个数，（可以特判一下 $n<10$ 的情况，此时输出 $n+1$）。

# Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
signed main() {
	std::cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	if (n < 10) {
		cout << n + 1;
		return 0;
	}
	int ans = 1;
	for (int i = 1; i <= (int)log10(n); i++) {
		ans *= 10;
		ans += 1;
	}
	cout << n / ans + (int)log10(n) * 10;
	return 0;
}
```

---

## 作者：TLE_qwq (赞：2)

### 关键思路
- 数字位数
	- 很简单，倒计时中数字的位数从 $ n $ 的位数减少到 $1$ 位。~~简不简单~~。
   
- 数字出现次数
   - 数字 $0$：由于没有前置零嘛，$0$ 的最大出现次数与 $n$ 的位数 $len$ 相关。不难看出，如果 $len=1$，$0$ 只在数字 $0$ 中出现 $1$ 次，若 $len>1$，$0$ 最多出现在 $len-1$ 个位置。 ~~可以理解吗。~~
   - 其他数字：对于数字 $d$，由 $len$ 个 $d$ 组成的数，如果不超过 $n$，哪 $d$ 的最大出现次数肯定为 $len$ 呀，不然最大次数为 $len-1$。


### 代码
```cpp
#include <iostream>
using namespace std;
int main() {
    long long n;
    cin >> n;
    int len = 0;
    long long j = n;
    while (j > 0) {
        len++;
        j /= 10;
    }
    int cnt = (len == 1) ? 1 : len - 1;
    long long one = 0;
    for (int i = 0; i < len; i++) {
        one = one * 10 + 1;
    }
    int sum = cnt; 
    for (int d = 1; d <= 9; d++) {
        long long num = d * one;
        if (num <= n) {
            sum += len; 
        } else {
            sum += (len - 1);
        }
    }
    cout << sum << endl;
    return 0;
}

```

---

## 作者：wangziyang202511036 (赞：2)

# 题解：P13672 [GCPC 2023] German Conference for Public Counting  
## 题目大意  
给定 $n$，若干人将通过举起带有数字的标牌来显示当前倒计时，每个标牌上只有一个十进制**数字**，大于 $10$ 的数将通过并排举起多个标牌显示，且无前导零。  
倒计时从 $n$ 开始，需要用标牌依次显示 $n$，$n-1$，$n-2\dots 0$。求至少需要准备多少个标牌才能显示整个倒计时？
## 思路  
此题的关键点在于：标牌**可以重复使用**，但同一时间显示一个数字时，必须保证有足够的对应数字标牌。  
这样说可能难以理解，举几个例子：  
若 $n=9$ 或 $n=10$，我们需要的标牌都只有 $10$ 个，因为 $0$ 到 $9$ 中已经有了 $1$ 和 $0$，所以 $10$ 不用准备另外的牌子了。但是，当 $n=11$ 时应准备 $11$ 个标牌，因为 $11$ 需要两个数字 $1$ 标牌。


看懂了题目，我们再来想该如何求出最少需要准备的标牌数。  
有一种思路容易想到：分别求出 $0$ 到 $9$ 每个数字所需要的**最多**的标牌数（即最大出现次数）再累加。由于其它倒计时所需要的数量都不会大于最大出现次数，那么在任意时刻都可以保证有足够的标牌使用。此答案一定是最优解，因为其它更小的答案都无法保证标牌数量在每个倒计时都够用。

那么，怎么统计每个数字最多的出现次数呢？观察以下针对数字 $1$ 的例子：
- $n=10$ 时，$1$ 需要的标牌 $1$ 最多。
- $n=100$ 时，$11$ 需要的标牌 $1$ 最多。
- $n=1000$ 时，$111$ 需要的标牌 $1$ 最多。
- $n=10000$ 时，$1111$ 需要的标牌 $1$ 最多。

这样我们就知道如何实现了。枚举数字 $i$，对于每个 $i$，找到最大的 $cnt$，使得由 $cnt$ 个 $i$ 拼接组成的数不超过 $n$，答案为 $0$ 至 $9$ 的最大标牌数量的和。

特别地，对于 $0$ 我们需要特判，因为不存在如 $0000$ 这样的数。我们发现，对于一个位数大于 $1$ 的数 $n$ ，只需要把除了 $n$ 的首位外的其它数字都换成 $0$，这些 $0$ 的数量就是 $0$ 的最大出现次数。因为倒计时最终会回到 $0$，所以当 $n$ 只有 $1$ 位时 $0$ 的最大出现次数应该为 $1$。

最后，不要忘记开 `long long`！
## 完整代码  
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    int n;
    cin>>n;
    int len=to_string(n).size()-1;//to_string很方便，很多类型都能直接转成字符串
    int zero=max(1,len);
    ll ans=zero;
    for(int i=1;i<=9;i++)//枚举1到9
    {
        ll cur=i;
        int cnt=1;
        while(cur<=n)
        {
            cnt++;
            cur=cur*10+i;
        }
        ans+=cnt-1;//实际上应该加上退出循环之前的cnt-1,cnt是cur大于n后的结果
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：a_computers (赞：2)

## 题意解释

求将 $0$ 到 $n$ 用 $0$ 到 $9$ 的一位数字卡片表示出来，最少需要多少张卡片。

## 解法分析

可以考虑到要用的单个数字 $x$ 卡牌最大数量肯定为整个数只有 $x$ 组成的数字。设 $m=n$ 的位数，我们可以先算出在 $m$ 位时有几个数只由一个数字组成，然后直接求即可。其他讲解见注释。

### Tip：可以用字符串存 $n$。

```cpp
#include<bits/stdc++.h>
#define AC a_computers
using namespace std;
int main(){
    string s;
    cin>>s;//使用字符串
    if(s.size()<2) return cout<<s[0]-'0'+1,0;//如果是一位数，直接输出
    int cnt=s[0]-'0';
    //寻找第一位不等于s[0]的数字，如其<s[0],证明有cnt-1个，否则有cnt个
    for(int i=0;i<s.size();i++){
        if(s[i]>s[0]) break;
        if(s[i]<s[0]){
            cnt--;
            break;
        }
    }
    cout<<s.size()*10+cnt-10;//默认所有数字都是，然后再减去(10-cnt),即为在m位时有多少数是只由一个数字组合成的
    return 0;
}
```

---

## 作者：YiskyGame (赞：2)

## 大意

给出一个数 $n$, 求出在 $n$ 到 $0$ 之间每个数中数字 $0$ 到 $9$ **最多**出现次数的和。为什么是最多呢？因为一个数字牌可反复使用多次。

## 解析

### 非优化思路

我们可以想出一个最朴素的思路：

1. 枚举 $n$ 到 $0$ 之间的数；
2. 统计每个数中 $0$ 到 $9$ 最多出现次数的和；
3. 将现在的答案与之前存储的答案比较；
4. 求和，输出。

很容易写出以下代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int ans[10] = {1}, cnt[10];
int main() {
	int n, sum = 0;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x = i;
		memset(cnt, 0, sizeof(cnt));
		while (x) {
			cnt[x % 10]++;
			x /= 10;
		}
		for (int j = 0; j <= 9; j++)
			ans[j] = max(cnt[j], ans[j]);
	}
	for (int i = 0; i <= 9; i++)
		sum += ans[i];
	cout << sum;
	return 0;
}
```

但是，[超时了](https://www.luogu.com.cn/record/229940828)……

### 时间复杂度

为什么呢？我们可以计算一下它的时间复杂度——光枚举 $n$ 到 $0$ 之间的数就达到了 $O(N)$ 级别，最多可达 $10 ^ 9$ 次，可计算机一秒最多运算 $2 \times 10 ^ 8$ 次，更别说其它步骤了！

因此，我们需要更优的思路。

### 优化思路

### 对于 $1$ 到 $9$

我们仔细想想：假设一个数为 $x$, 那么在 $x$ 中每个数字（不包括 $0$）最多出现多少次？答案很显然，是 $\operatorname{len}(x)$, 其中 $\operatorname{len}(x)$ 表示 $x$ 的数位个数。为什么是这个答案呢？我们将 $x$ 的每一位都填这个数字即可。但请注意！填满后的数必须小于等于 $n$.

那这个问题和本题有什么关系呢？我们可以构造填满后的数，例如 $1, 11, 111, 1111, \dots$ 直到填满后的数大于 $n$.

### 对于 $0$

$0$ 最多出现多少个呢？我们找找规律。

+ $n < 10 ^ 1$: 仅 $1$ 个 $0$.
+ $n < 10 ^ 2$: $10, 20, 30, \dots$ 但这些数仅有 $1$ 个 $0$.
+ $n < 10 ^ 3$: $100, 200, 300, \dots$ 这些数都有 $2$ 个 $0$.
+ $n < 10 ^ 4$: $1000, 2000, 3000, \dots$ 这些数都有 $3$ 个 $0$.
+ $\dots$

发现了吗？在 $n < 10 ^ 2$ 时，都仅有 $1$ 个 $0$, 否则有 $\operatorname{len}(n) - 1$ 个 $0$.

### 时间复杂度

时间复杂度：与 $\operatorname{len}(n)$ 有关。这个复杂度可以通过此题。

[过了。](https://www.luogu.com.cn/record/229949041)记得开 `long long`, 因为 $1 \le n \le 10 ^ 9$, 在 $n = 10 ^ 9$ 时，枚举到 $10 ^ {10}$ 时要退出 `while` 循环，此时这个数超过了 `int` 类型的最大值 $2 ^ {31} - 1$.

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	int n, ans = 0;
	cin >> n;
	for (int i = 1; i <= 9; i++) {
		int x = i; //防止 i 值发生变化。
		while (x <= n) {
			ans++;
			x = x * 10 + i; //构造 1, 11, 111, 1111... 等数。
		}
	}
	if (n < 100)
		cout << ans + 1; //当 n 小于 100 时，仅有 1 个 0.
	else {
		int x = 0;
		while (n) {
			n /= 10;
			x++;
		}
		cout << ans + x - 1; //否则统计 0 的数量，因为最高位不能为 0, 所以要 - 1. 
	}
	return 0;
}
```

---

## 作者：ingo_dtw (赞：1)

# P13672 [GCPC 2023] German Conference for Public Counting

### 解题思路：
- 我们可以把问题转换为：对于每个数字 $d$，找出在区间 $[0, n]$ 的所有整数中，$d$ 在任意一个整数中出现次数的最大值 $f(d)$。最终答案是所有 $f(d)$ 的总和。
- 对于每个 $d$，从大到小枚举可能的出现次数 $k$（从数字的最大位数到 $1$），检查是否存在一个不超过 $n$ 的整数，其中 $d$ 至少出现 $k$ 次。
- 考虑记忆化搜索从高位到低位逐位确定数字，同时记录：
  - 当前已统计的 $d$ 的出现次数 $cnt$。
  - 是否已小于 $n$。
  - 是否仍处于前导零状态。
- 当所有位都确定后，如果整个数字为 $0$，则 $d=0$ 时出现 $1$ 次，否则为 $0$ 次；非零数字直接使用计数结果。

### Ac Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#ifdef __linux__
#define gc getchar_unlocked
#define pc putchar_unlocked
#else
#define gc _getchar_nolock
#define pc _putchar_nolock
#endif
#define int long long
#define R register
#define rint register int
#define _ read<int>()
inline bool blank(const char x)
{
    return !(x^9)||!(x^13)||!(x^10)||!(x^32);
}
template<class T>inline T read()
{
    T r=0,f=1;R char c=gc();
    while(!isdigit(c))
    {
        if(c=='-') f=-1;
        c=gc();
    }
    while(isdigit(c)) r=(r<<1)+(r<<3)+(c^48),c=gc();
    return f*r;
}
inline void out(int x)
{
    if(x<0) pc('-'),x=-x;
    if(x<10) pc(x+'0');
    else out(x/10),pc(x%10+'0');
}
inline void read(char &x)
{
    for(x=gc();blank(x)&&(x^-1);x=gc());
}

int n,le;
int dp[11][2][2][11];
bool dfs(rint po,rint ct,bool fl,bool ze,rint d,rint k,string &s)
{
    if(ct>=k) return 1;
    if(po==le)
    {
        if(ze)
        {
            if(d==0) return (1>=k);
            else return 0;
        }
        else
        {
            return (ct>=k);
        }
    }
    if(dp[po][fl][ze][ct]!=-1) return dp[po][fl][ze][ct];
    rint up=fl?9:(s[po]-'0');
    bool re=0;
    for(rint i=0;i<=up;i++)
    {
        bool nz=ze&&(i==0);
        bool nf=fl||(i<up);
        rint nc=ct;
        if(i==d)
        {
            if(d==0)
            {
                if(!ze) nc++;
            }
            else nc++;
        }
        if(dfs(po+1,nc,nf,nz,d,k,s))
        {
            re=1;
            break;
        }
    }
    return dp[po][fl][ze][ct]=re;
}
signed main()
{
    n=_;
    string s=to_string(n);
    le=s.size();
    rint ans=0;
    for(rint d=0;d<=9;d++)
    {
        rint mx=0;
        for(rint k=min(le,10ll);k>=1;k--)
        {
            memset(dp,-1,sizeof(dp));
            if(dfs(0,0,0,1,d,k,s))
            {
                mx=k;
                break;
            }
        }
        ans+=mx;
    }
    out(ans);
    pc('\n');
    return 0;
}
```

---

## 作者：Doraeman (赞：1)

## 思路
当某个数包含相同的数字，此时需要多种这样的数字牌子。  
例如：如果要表示出 $33333$，那么必须要有至少 $5$ 个数字 $3$ 牌子。

也就是说，对于除了 $0$ 之外的所有的数字 $a\isin[1,9]$，我们要找最大的 $0\le\overline{aa\cdots a}\le n$（共 $b$ 个 $a$）。  
此时，需要至少 $b$ 个 $a$ 数字牌子来表示这个数 $\overline{aa\cdots a}$，为答案贡献 $b$。

## 具体统计方法
可以首先求出最大的 $0<\overline{11\cdots1}\le n$，设有 $c$ 个 $1$。

接下来，将这个数分别 $\times1,\times2,\dots,\times9$，得到 $\overline{11\cdots1},\ \overline{22\cdots2},\dots,\ \overline{99\cdots9}$。  
注：每个数都包含 $c$ 个数字。

再分别将这些数从大到小与 $n$ 比大小，如果小于等于 $n$ 就结束比较。这样就可以找到最大的 $\overline{aa\cdots a}$ 以及其对应的 $b$，此处显然满足 $b=c$。

找到这个 $a$ 之后，可以发现：
- $0\sim n$ 的倒计时中包含 $\overline{11\cdots 1}\sim\overline{aa\cdots a}$（$c$ 个数字），所以它们一共需要 $a\times c$ 个数字牌。  
- $0\sim n$ 的倒计时中也包含 $\overline{(a+1)(a+1)\cdots(a+1)}\sim\overline{99\cdots9}$（$c-1$ 个数字），所以它们一共需要 $(9-a)\times(c-1)$ 个数字牌。  
- 这个倒计时中还包含 $\overline{100\cdots0}$（$c-1$ 个 $0$），所以还额外需要 $(c-1)$ 个数字牌。

最后求出答案：$a\times c+(9-a)\times(c-1)+(c-1)=ac+(10-a)c$。

## 特判
如果 $n$ 是一位数，即 $b=c=1$，我们的统计方法没有统计 $0$，应该加上。

为了避免麻烦，可以直接算出来：当 $n$ 是一位数时，需要 $(n+1)$ 个数字牌。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

// 求 b 
int digit(int x){
    int sum = 0;
    while(x) x/=10, sum++;
    return sum;
}

int main(){
    int x; cin >> x;
    int d = digit(x);

    // 特殊处理 
    if(d == 1){
        cout << x + 1;
        return 0;
    }

    // 求最大的 11...1≤n
    int base = 0;
    for(int i=1; i<=d; i++)
        base *= 10, base++;

    // 直接相除得到对应的 a
    int t = x / base;
    // 答案 // b=c
    int ans = t*d + (10-t)*(d-1);
    cout << ans;
}
```

---

## 作者：Little_d (赞：1)

## 思路
先特判 $0$ 最少要几张数字牌，因为数字不会包含前导零，如果数字的位数大于 $1$ 在 $0$ 到 $n$ 的数字中就一定会出现 $10^{|n|}$，所以最少要的纸牌就是 $|n|-1$，其中 $|n|$ 表示 $n$ 的位数，因为我们把 $n$ 当成字符串输入。

接着判断 $1$ 到 $9$ 最少要用几张牌，如果 $n$ 大于全是当前数字的情况，说明会存在全部是当前数字的情况，这个数字就最少要用 $n$ 的位数张牌，否则说明不包含，但是依然需要 $|n|-1$ 个数字牌。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string n;
int cnt[10];
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    cnt[0]=1;
    if(n.size()>1)cnt[0]=n.size()-1;
    for(int i=1;i<=9;i++){
        bool flag=true;
        for(int j=0;j<n.size();j++){
            if(n[j]<char(i+'0')){
                flag=false;
                break;
            }
            if(n[j]>char(i+'0'))break;
        }
        if(flag)cnt[i]=n.size();
        else cnt[i]=n.size()-1;
    }
    int ans=0;
    for(int i=0;i<10;i++)ans+=cnt[i];
    cout<<ans;
    return 0;
}
```

---

## 作者：lizihan15550390562 (赞：1)

## 题意解释
输入一个数字 $n$，输出 $0$ 到 $n$ 之间每个数字一到九的数字出现的最大次数的和。
## 题目分析
提示：十年 OI 一场空，不开 long long 见祖宗！  
首先，我们想到的是暴力枚举，但是 ~~经过我的亲身测试~~，会超时的，所以我们应该找一下规律。  
设 $n$ 有 $m$ 位，那么至少有 $m-1$ 个 $1$ 到 $9$，而且一定存在 $\max(1,m-1)$ 个，不用证明了吧。那么数字 $l$ 在当 $\sum_{i=1}^{m} l\times10^{i-1}\leq n$ 的时候，总数加一。  
理论存在，实践开始。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[101];
void n0(long long uu,long long num){
	if(uu==1) a[0]=1;
	else a[0]=uu-1;
}
void n1(long long uu,long long num){
	for(int k=1;k<=9;k++){
		long long u=0;  //计算和 
		a[k]=uu-1;
		for(int i=1;i<=uu;i++){
			u+=k*pow(10,i-1);
		} 
		if(num>=u) a[k]++;
	}
}
int main(){
	long long num,sum=0,wei=0;  //开 long long! 
	cin>>num;
	long long uu=num;
	while(uu){
		uu/=10;wei++;
	}
	//计算位数 
	n0(wei,num);  //计算0 
	n1(wei,num);  //计算1到9 
	for(int i=0;i<=9;i++) sum+=a[i];
	cout<<sum;
	return 0;
}
```

---

## 作者：EnochLiu2012 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13672)

题目大意：现有若干张 $0\sim9$ 的数字牌，若要表示 $0\sim n$ 所有的数字，至少需要多少张数字牌？

算法：贪心

思路：对于单个数字，我们将它不断地累加，当累加的数字大于了 $n$，那么这个数字所需的数字牌数量就是累加的次数。例如：$n=114514$，此时数字为 $1$，起初让 $sum=1$，当 $sum=1111111$ 时，它就比 $n$ 大了，累加次数为 $6$，所以数字牌 $1$ 至少需要 $6$ 张。

注意：

- 如果将 0 不断地累加，它永远是 0，就会 TLE。所以，我们让 $sum=100$（2 个 0），让 $cnt=1$（最后的单个数字 0），再进行累加。
- 俗话说[十年 OI 一场空，不开 long long 见祖宗](https://www.luogu.com.cn/record/229915273)。因为累加的数字可能出现 10 个 2，10 个 3 等情况，会爆 int，所以**一定要开 long long**。

上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans,sum;
signed main(){
    cin>>n;
    ans=1;  //考虑到单个 0 的情况 
    sum=100;
    while (sum<=n){
        ans++;
        sum*=10;
    }
    for (int i=1; i<=9; i++){
        int sum=i;
        while (sum<=n){
            ans++;  //次数累加
            sum=sum*10+i;  //数字累加
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Xjj2013_0405 (赞：0)

## 题意

这题很神奇，题面是英文 ~~（我刚开始看的一脸懵，为什么没翻译！）~~ ，后来我去翻译了，~~废话一堆~~，主要意思就是问要拼成 0 到 $n$ 需要多少数字。

## 思路

题目不难，稍加思考，不难想到其实就是计算每种数字在每个数字中出现的最大次数的和。那么问题来了，如何计算每种数字在每个数字中出现的最大次数，又如何记录再相加呢？计算每种数字在每个数字中出现的最大次数计算每种数字在每个数字中出现的最大次数分两种，第一种就是 0 ，众所周知，出现 0 最多的肯定是 10 的次方数，通过观察可知 10 的 $n$ 次方中有 $n-1$ 个 0 ，所以我们先算出 $n$ 的位数，就是 10 的最大次方数了，再减一就是 0 的最大次数。第二种就是其他数字，这种情况需要造叠数，一位一位地加，如果太大就结束增加，并计算最大值。至于如何记录再相加，用数组记录起来，最后求和就行了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//个人习惯 
int n,sum=0,a[10];
int len(int n)//位数计算函数
{
	int l=0;
	while(n!=0){
		l++;
		n/=10;
	}
	return l;
}
signed main()
{
	cin>>n;//输入 
	for(int i=0;i<=9;i++) 
		if(i<=n) a[i]=1;//不管什么数字，比n小的数字都至少要用一次 
	for(int i=0;i<=9;i++)//计算叠数中同一个数出现的最大次数 
	{
		if(i==0){//等于0时特判 
			int l=len(n)-1;//用最大位数（n的位数）减一算出0的最多个数 
			a[i]=max(a[i],l);//算最大 
			continue;
		}
		int num=0;//算叠数 
		for(int j=1;1;j++)//叠数位数 
		{
			num=num*10+i;//增加一位数 
			if(num>n) break;//太大就跳出 
			a[i]=max(a[i],j);//算最大值 
		}
	}
	for(int i=0;i<=9;i++) sum+=a[i];//计算总和 
	cout<<sum;//输出 
	return 0;
}
```

---

## 作者：hlb44 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13672)

前置知识点：

$x$ 的位数数学表示。

对于数字是 $i$（$0 \le i \le 9$）的数字牌，它的出现次数应该最大化，比如 $n = 1241$ 时，$1$ 数字牌应该这样枚举：$1,11,111,1111$，当我们枚举到 $11111$ 时，因为 $11111 > n$，所以结束枚举。特殊的 $i = 0$ 时，出现次数应该是 $1$ 和 $m$ 取较大值，其中 $m$ 是 $n$ 的位数 $- 1$。

具体见代码注释（禁止复制）：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans;
signed main(){
	int x,p;//x:同数字组成的数;p:计数
	//处理1-9:计算每个数字的最大出现次数
	cin>>n;
	for(int d=1;d<=9;++d){
		for(x=d,p=1;x<=n;x=x*10LL+d,++p);//生成d,dd,ddd...直到超过n
		ans+=p-1;//累加最长同数字串长度
	}
	ans+=max(1LL,(int)log10(n));//0至少出现1次(数字0本身)
	cout<<ans;
}
```

---

## 作者：furina_yyds (赞：0)

## 题解：P13672 \[GCPC 2023] German Conference for Public Counting

这题有点偏思维。

## 思路

对于给定的数 $n$，不妨假设它有 $k$ 位，他的最高位是 $s$。

不难得出，$0 \sim 9$ 都至少要 $k - 1$ 个牌子，若 $n > \underbrace{a \, a \, \cdots \, a}_{k \text{个}}$，则 $a$ 需要 $k$ 个牌子。以此模拟即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, ans;
int wei(long long x){
	int cnt = 0;
	while(x){
		x /= 10;
		cnt++;
	}
	return cnt;
}
long long shu(int a, int b){
	long long cnt = 0;
	while(a--){
		cnt = cnt * 10 + b;
	}
	return cnt;
}
int main(){
	scanf("%lld", &n);
	if(n < 10){
		printf("%lld", n + 1);
		return 0;
	}
	int w = wei(n), w10 = pow(10, w - 1), shou = n / w10, ans = 0;
	if(n < shu(w, shou))shou--;
	ans = shou * w + (10 - shou) * (w - 1);
	printf("%d", ans);
	return 0;
}
```

---

