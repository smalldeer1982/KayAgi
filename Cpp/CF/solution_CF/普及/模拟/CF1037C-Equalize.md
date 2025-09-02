# Equalize

## 题目描述

You are given two binary strings $ a $ and $ b $ of the same length. You can perform the following two operations on the string $ a $ :

- Swap any two bits at indices $ i $ and $ j $ respectively ( $ 1 \le i, j \le n $ ), the cost of this operation is $ |i - j| $ , that is, the absolute difference between $ i $ and $ j $ .
- Select any arbitrary index $ i $ ( $ 1 \le i \le n $ ) and flip (change $ 0 $ to $ 1 $ or $ 1 $ to $ 0 $ ) the bit at this index. The cost of this operation is $ 1 $ .

Find the minimum cost to make the string $ a $ equal to $ b $ . It is not allowed to modify string $ b $ .

## 说明/提示

In the first example, one of the optimal solutions is to flip index $ 1 $ and index $ 3 $ , the string $ a $ changes in the following way: "100" $ \to $ "000" $ \to $ "001". The cost is $ 1 + 1 = 2 $ .

The other optimal solution is to swap bits and indices $ 1 $ and $ 3 $ , the string $ a $ changes then "100" $ \to $ "001", the cost is also $ |1 - 3| = 2 $ .

In the second example, the optimal solution is to swap bits at indices $ 2 $ and $ 3 $ , the string $ a $ changes as "0101" $ \to $ "0011". The cost is $ |2 - 3| = 1 $ .

## 样例 #1

### 输入

```
3
100
001
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
0101
0011
```

### 输出

```
1
```

# 题解

## 作者：雅儿贝德 (赞：3)

~~其实这道题没有蓝题这么难啊~~

直接讲思路：

从1~n扫一遍整个序列

对于当前的$a[i],a[i+1],b[i],b[i+1]$，如果需要并且可以交换（操作2），辣么就交换他们（花费代价为1），否则判断$a[i],b[i]$是否相同，如果不相同，则进行操作1（花费代价也为1）把两个数变成相同的，如果相同，那就不需要搞什么事情了

一句话：**操作1只在不能使用操作2的时候进行**，因为操作2可以将2个数字匹配，而操作1只能匹配1个，很明显要尽可能使用操作2

其实就是贪心嘛（我觉得）

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,ans=0;
char a[1000010],b[1000010];
int main()
{
	cin>>n;
	cin>>(a+1)>>(b+1);
	for(int i=1;i<=n;i++){
		if(a[i]!=b[i] && a[i+1]!=b[i+1] && a[i]!=a[i+1] && i+1<=n){
			ans++;
			i++;
		}else ans+=(a[i]!=b[i]);
	}
	printf("%d",ans);
    return 0;
}
```


---

## 作者：sto__Liyhzh__orz (赞：2)

应该是个贪心吧。

对于每个 $s1_i$，$s1_{i+1}$，$s2_i$，$s2_{i+1}$，是不是互不相同，若是的话做操作 2，不是的话若 $s1_i$ 不相等 $s2_i$ 做操作 1，否则啥也不做。

代码:
```cpp
#include<bits/stdc++.h>
using namespace std;

#define LL long long

int len;
string s1,s2;

int main()
{
    ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>len>>s1>>s2;
	int cnt=0;
	for(int i=0;i<=len-1;i++)
	{
		if(i<=len-2 && s1[i]!=s2[i] && s1[i]!=s1[i+1] && s1[i+1]!=s2[i+1])
		{
			cnt++;
			i++;
		}
		else cnt+=(s1[i]!=s2[i]);
	}
	cout<<cnt<<endl;
    return 0;
}

```

---

## 作者：Ousmane_Dembele (赞：2)

这是一道非常简单的贪心题
```
1操作就是用1个单位代价来将a数组的一位转化成b数组的那一位
2操作就是可以将两位交换位置

我们发现，只有当两个相邻位置，且都需要转化的时候用2操作才更实惠
于是 代码如下
```

```
#include<bits/stdc++.h>
using namespace std;
int n,sum;
char a[1000002];
char b[1000002];
int main(){
    cin>>n;
    cin>>a+1;
    cin>>b+1;
    for(int i=1;i<=n;i++){
        if(a[i]==b[i])continue;
        sum++;
        if(i==n)continue;
        if(a[i]==b[i+1]&&a[i+1]==b[i]){
            a[i]=b[i];
            a[i+1]=b[i+1];
        }
        
    }
    cout<<sum;
}
```


---

## 作者：linan04195 (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1037C)
---
## 题意
在一个序列中，有这两种更改方式：
1. 选择一个位置 $pos$，将 $a_{pos}$ 更改为 $1-a_{pos}$，代价为 $1$。
2. 选择两个位置 $pos1$ 和 $pos2$，将 $a_{pos1}$ 与 $a_{pos2}$ 交换，代价为 $\mid pos1-pos2 \mid$。

求把序列 $a$ 转化成序列 $b$ 的最小代价。

## 思路
如果有两个数可以配成一对，则用方式 $2$。其他则用方式 $1$。

## Code
```cpp

#include<bits/stdc++.h>
using namespace std;

int n,sum=0;
string a,b;

int main(){
	cin>>n;
	cin>>a>>b;
	
	for(int pos=0;pos<n;pos++){
		if(a[pos]!=b[pos]&&a[pos+1]!=b[pos+1]&&a[pos]!=a[pos+1]&&pos+1<=n) sum++,pos++; 
		else sum+=(a[pos]!=b[pos]);
	}
	
	cout<<sum<<endl;
    return 0;
}
```

---

## 作者：cz666 (赞：1)

## 首先两个数都是要用字符串读入的，不然就要写复杂的高精度（大雾）...

### 总共有两种变换方式（搬题）：

1. 在字符串 $ a $ 中选择一个位置 $ p $ ，将 $ a[p] $ 位置上的数从 $ 0 $ 变成 $ 1 $ 或者从 $ 1 $ 变成 $ 0 $ 。

2. 在字符串 $ a $ 中选择两个位置 $ p,q $ ，将 $ a[p] $ 和 $ a[q] $ 互换，代价为 $ | $ $ p-q $ $ | $ 。

都用第一种方法改变字符串 $ a $ ，那么代价稳定为字符串 $ a $ 和字符串 $ b $ 不一样的数量。

### 但如果使用第二种方法，我们就会发现它其实有优劣性之分：

1. 如果这两个数的位置相邻，那样交换的代价为 $ 1 $ ，比使用第一种方法处理这两个字符要节省 $ 1 $ 步，所以在这时第一种方法就会被舍去。

2. 如果这两个数的位置间隔一位，那样代价为 $ 2 $ ，也就是说这样是和第一种方法处理这两个字符代价一样，就不做任何事情。

3. 如果这两个数的位置相隔两个及以上，那样代价大于 $ 2 $ ，也就是说这时使用第二种方法处理这两个字符比第一种方法更劣，肯定会被舍去。

所以我们只要找一遍两个字符串中不同的位数个数，记录到答案变量 $ ans $ 中。

再一个循环，每次找到一个相邻出现的需要更改的字符就 $ sum $ 减一。

但要注意，可能每次答案减一都要把 $ a $ 中相邻字符的后一个变成相应的 $ b $ 中的字符，防止重复计算，导致答案偏小。

最后得到的 $ sum $ 就是正确的答案。

**（我的表达能力不怎么好，如果一时哪些地方有问题，欢迎在旁边讨论提出）**

### 下面贴上我的AC代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string a,b;
signed main(){
	int n;cin>>n;
	cin>>a>>b;
  //以字符串形式读入
	int len=a.length(),ans=0;
  //记录字符串长度和答案初始化
	if (a[0]!=b[0]) ans++;
	for (int i=1;i<len;i++) if (a[i]!=b[i]) ans++;
   //首先先全部当做做第一种方法来变换
	for (int i=1;i<len;i++)
	 if (a[i]!=b[i] && a[i-1]!=b[i-1] && a[i]==b[i-1]) ans--,a[i]=b[i];
  //如果相邻数位出现都需要变换的情况，就把变换方法换为第二种方法，答案减一。
  //a[i]的值改为b[i]，防止重复减去。
	printf("%lld\n",ans);
  //输出最后的答案
	return 0;
  //完美结束整个程序
}
```

[我的AC记录](https://www.luogu.org/recordnew/show/18116068)


---

## 作者：Zhuluoan (赞：0)

## 题目描述

给定两个长度为 $n$ 的 $01$ 序列 $a,b$。

每次可以执行如下操作：

1. 在 $a$ 中选择一个位置 $p$，将 $a_p$ 变为 $1-a_p$，代价是 $1$。
2. 在 $a$ 中选择两个位置 $p,q$，将 $a_p$ 和 $a_q$ 互换，代价是 $\lvert q-p \rvert$。

问最少需要多少代价才能将 $a$ 变成 $b$。

## 题目分析

对于操作二，仅当 $a_q \neq a_p$，$b_q \neq b_p$，并且 $a_q \neq b_q$ 时才能使用，此时代价为 $\lvert q-p \rvert$。同时它也可以等价为操作一，即在 $p$ 和 $q$ 位值各执行一次操作一，这样的代价为 $2$。所以只有 $\lvert q-p \rvert \lt 2$ 时执行操作二是优的，其他情况一律执行操作一。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define random(a,b) (rand()%(b-a+1)+a)
#define se second
#define fi first
#define pr pair<int,int>
#define pb push_back
#define ph push
#define ft front
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
#define mem(a,b) memset(a,b,sizeof a)
const int N=1e6+10;
int n,ans;
char a[N],b[N];
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>a+1>>b+1;
    For(i,1,n)
	{
		if(a[i]!=b[i]&&a[i+1]!=b[i+1]&&a[i]!=a[i+1])
		{
			i++;
			ans++;
		}
		else if(a[i]!=b[i]) ans++;
	} 
	cout<<ans;
	return 0;
}
```

---

## 作者：wuzijie (赞：0)

## 题面解释：
有两个 $01$ 序列，请问把 $a$ 变成 $b$ 的最小花费。

有两种操作：

1. 在 $a$ 中选择一个位置 $p$，将 $a_p$ 变为 $1-a_p$，代价是 $1$。

2. 在 $a$ 中选择两个位置 $p$，$q$，将 $a_p$ 和 $a_q$ 互换，代价是 $| p-q |$。

## 思路分析：
首先我们考虑只有操作 $1$ 的情况，这时候只需要统计两个序列不同的数的个数就好了，非常简单。

然后加入操作 $2$，为了使结果更优，我们只用考虑相同的效果更小的花费，而交换操作最多能使 $2$ 个数达到相同，最少能只有 $1$ 的代价，当这两个条件同时满足时，才会更优，否则只会相同或者更劣。

简单的贪心，把两种操作分开考虑就行。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,ans;
char a[N],b[N];
signed main() {
	scanf("%d%s%s",&n,a+1,b+1);
	for(int i=1; i<=n; i++)
		if(a[i]!=b[i]) {
			if(i<n&&a[i]!=a[i+1]&&a[i+1]!=b[i+1])ans++,i++;//处理操作2
			else ans++;//处理操作1 
		}
	printf("%d",ans);
	return 0;
}
```

谢谢！

---

## 作者：Arghariza (赞：0)

贪心。

操作 $1$ 可以看成取反，操作 $2$ 可以看做交换。

显然操作 $2$ 中只有当 $|p-q|=1$ 时更优（否则直接对 $p,\ q$ 进行 $1$ 操作即可）。

那我们直接遍历整个 $a$ 串，当 $a_i$ 与 $a_{i+1}$ 对于 $b_i,\ b_{i+1}$ 正好相反的时候直接进行 $2$ 操作，否则直接 $ans++$ 即可（反正这一位不影响下一位）。

```cpp
#include <bits/stdc++.h>
namespace mystd {
	inline int read() {
	    int w = 1, q = 0;
	    char ch = ' ';
	    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	    if (ch == '-') w = -1, ch = getchar();
	    while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
	    return w * q;
	}
	inline void write(int x) {
	    if (x < 0) {
	        x = ~(x - 1);
	        putchar('-');
	    }
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace std;
using namespace mystd;

int n, ans;
string s1, s2;

int main(){
	n = read();
	getline(cin, s1);
	getline(cin, s2);
	for (int i = 0; i < n; i++) {
		if (s1[i] != s2[i]) {
			ans++;
			if (i != n - 1 && s1[i] == s2[i + 1] && s1[i + 1] == s2[i]) {
				s1[i] = s2[i];
				s1[i + 1] = s2[i + 1];
			}
		}
	}
	write(ans);
	return 0;
}

```

---

## 作者：封禁用户 (赞：0)

## 思路
这是一道贪心水题，题目要求在序列 $a$ 中，每次可以执行如下操作：
- 在 $a$ 中选一个位置 $p$，将 $a_p$ 变为 $1-p$，代价是 $1$。
- 在 $a$ 中选两个位置 $p,q$，将 $a_p$ 和 $a_q$ 互换，代价是 $∣p−q∣$。
- 要求将 $a$ 变成 $b$，最小化代价。

如果有两个数可以配成一对，则用方式 $2$。其他则用方式 $1$。

---

## 作者：Forsaken2020 (赞：0)

先O(n)处理出所有不满足条件的0和1的位置，分别用两个set存起来。然后这个题有个重要的性质就是当且仅当|i-j|==1并且i和j位置上分别为0或者1时才互换，所以预处理出来直接暴力就没了。

```cpp
//author Eterna
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<utility>
#include<cmath>
#include<climits>
#include<deque>
#include<functional>
#include<complex>
#include<numeric>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define INF 0x7fffffff
#define Pi acos(-1.0)
#define maxn 1000000
#define eps 1e-15
#define MOD 1000000007
#define ABS(x) ((x)>=0?(x):(-(x)))
#define pb(x) push_back(x)
#define lowbit(x) (x&-x)
#define mid (L+R)/2
#define Lson (index*2)
#define Rson (index*2+1)
#define root arr[0].child[1]
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
inline int read_int() {
    char c;
    int ret = 0, sgn = 1;
    do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
    if (c == '-') sgn = -1; else ret = c - '0';
    while ((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    return sgn * ret;
}
inline ll read_ll() {
    char c;
    ll ret = 0, sgn = 1;
    do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
    if (c == '-') sgn = -1; else ret = c - '0';
    while ((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    return sgn * ret;
}
inline bool Get_Line(string& s) {
    s.clear();
    char ch;
    while ((ch = getchar()) && ch != '\n'&&ch != '\r') {
        if (ch == EOF)return false;
        s.push_back(ch);
    }
    return true;
}
char a[maxn + 5], b[maxn + 5];
set<int> s1, s0;
int len, cnt;
ll ans;
int main(void)
{
    len = read_int();
    scanf("%s", a + 1);
    scanf("%s", b + 1);
    for (int i = 1; i <= len; i++) {
        if (a[i] == b[i])continue;
        if (a[i] == '0')s0.insert(i);
        if (a[i] == '1')s1.insert(i);
    }
    for (auto iter = s1.begin(); iter != s1.end(); ++iter) {
        int k = *iter;
        if (s0.find(k - 1) != s0.end()) {
            ans += 1; s0.erase(k - 1); cnt++;
            continue;
        }
        if (s0.find(k + 1) != s0.end()) {
            ans += 1; s0.erase(k + 1); cnt++;
            continue;
        }
    }
    ans += s0.size() + s1.size() -  cnt;
    cout << ans << endl;
    //system("pause");
    return 0;
}
```

---

