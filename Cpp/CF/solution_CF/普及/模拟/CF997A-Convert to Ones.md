# Convert to Ones

## 题目描述

You've got a string $ a_1, a_2, \dots, a_n $ , consisting of zeros and ones.

Let's call a sequence of consecutive elements $ a_i, a_{i + 1}, \ldots, a_j $ ( $ 1\leq i\leq j\leq n $ ) a substring of string $ a $ .

You can apply the following operations any number of times:

- Choose some substring of string $ a $ (for example, you can choose entire string) and reverse it, paying $ x $ coins for it (for example, «0101101» $ \to $ «0111001»);
- Choose some substring of string $ a $ (for example, you can choose entire string or just one symbol) and replace each symbol to the opposite one (zeros are replaced by ones, and ones — by zeros), paying $ y $ coins for it (for example, «0101101» $ \to $ «0110001»).

You can apply these operations in any order. It is allowed to apply the operations multiple times to the same substring.

What is the minimum number of coins you need to spend to get a string consisting only of ones?

## 说明/提示

In the first sample, at first you need to reverse substring $ [1 \dots 2] $ , and then you need to invert substring $ [2 \dots 5] $ .

Then the string was changed as follows:

«01000» $ \to $ «10000» $ \to $ «11111».

The total cost of operations is $ 1 + 10 = 11 $ .

In the second sample, at first you need to invert substring $ [1 \dots 1] $ , and then you need to invert substring $ [3 \dots 5] $ .

Then the string was changed as follows:

«01000» $ \to $ «11000» $ \to $ «11111».

The overall cost is $ 1 + 1 = 2 $ .

In the third example, string already consists only of ones, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
5 1 10
01000
```

### 输出

```
11
```

## 样例 #2

### 输入

```
5 10 1
01000
```

### 输出

```
2
```

## 样例 #3

### 输入

```
7 2 3
1111111
```

### 输出

```
0
```

# 题解

## 作者：torque (赞：5)

# CF997A Convert to Ones

## 题解
对于这道题，我们要做的就是在最小花费内将给定的字符串变成全是1的串

操作1：并不能减少0

操作2：为了最小的步数，根据贪心的思想，每次都要选择连续的一段(全是0)，并且左右没有更多的0

鉴于我们刚刚的贪心思想，实际上比如**Sample#1**，01000等价于010，也就是说连续的一段可以视为一个数

也就是说我们要减少0的段数

操作1：可以减少一段，条件是存在两段以上的0(可以把他们转到一起)

操作2：减少一段0

也就是说，当0的段数大于等于2时操作1、2等价，贪心选最小

代价：

#### min(A,B)*段数

以及最后要加上操作2

记0的段数为x，则答案为

#### min(A,B)*(x-1)+B

字符串不大，暴力求x即可

具体细节见代码

## 代码
```cpp
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define N 400001
#define ll long long
#define rnt register int
using namespace std;
char s[N];
ll n,x,y,cnt;
int main(){
	cin>>n>>x>>y;
	scanf("%s",s+1);s[0]='1';
	for(rnt i=1;i<=n;i=-~i) if(s[i]=='0' && s[i-1]=='1') cnt=-~cnt;
	if(!cnt) cout<<"0";
	else cout<<y+(cnt-1)*min(x,y);
	return 0;
}
```

---

## 作者：如履薄冰 (赞：3)

# 思路
我们可以将给出的字符串 $edit$ 压缩一下，也就是将一段连续的相同字符压缩成一个这样的字符，比如将字符串 $1000110$ 压缩成 $1010$。我们可以花费 $x$ 元，执行一次翻转操作，也就是将压缩后的字符串中的一个 $01$ 或 $10$ 消掉。我们还可以花费 $y$ 元，执行一次取反操作，也就是将压缩后的字符串中的一个 $0$ 消掉。因此我们可以想到两种有可能是最优解的解法。
## 第一种解法：暴力取反
我们直接不考虑翻转操作，直接把字符串中所有 $0$ 变成 $1$。这种操作花费 $cnt \times y$ 元，其中 $cnt$ 表示压缩后的字符串中 $0$ 的个数。
## 第二种解法：消消乐
我们先执行 $cnt - 1$ 次翻转操作，把压缩后的字符串变成 $01$ 或 $10$，然后再执行一次取反操作，将压缩后的字符串中的 $0$ 去掉。这种操作花费 $(cnt-1) \times x + y$ 元，其中 $cnt$ 表示压缩后的字符串中 $0$ 的个数。
## 答案
综上所述，答案为 $cnt \times y$ 与 $(cnt-1) \times x + y$ 中的最小值。
## 补充注意点
我们在统计压缩后的字符串中 $0$ 的个数 $cnt$ 时，还要查看一下 $edit$ 中最后一个字符是否为 $0$，如果是，将 $cnt$ 加 $1$。
## 特判
如果压缩后的字符串中 $0$ 的个数为 $0$，表示没有 $0$，直接输出 $0$，因为不需要修改。
# 代码
```cpp
#include<iostream>
#include<string>
using namespace std;
long long cnt,n,x,y;
string edit;
int main(){
	cin>>n>>x>>y;
	cin>>edit;
	for(int i=0;i<edit.size();i++){
		if(edit[i]=='0'&&edit[i+1]=='1'){
			cnt++;
		}
	}
	if(edit[edit.size()-1]=='0'){
		cnt++;
	}
	if(cnt==0){
		cout<<0;
	}else{
		cout<<min(cnt*y,(cnt-1)*x+y);
	}
	return 0;
} 
```

---

## 作者：Laoda_Bryant (赞：1)

## 题意
给定一个长度为 $n$ 的01字符串，有以下两种操作：  
1. 将一个子串翻转，花费 $X$
2. 将一个子串进行取反，花费 $Y$  

求把原字符串变为全是 $1$ 的字符串的最小代价。
## 思路
### 只有 $2$ 操作的情况下  
贪心策略。考虑到任意范围取反的花费相同，我们可以将相同的部分合并，如下图  
![](https://cdn.luogu.com.cn/upload/image_hosting/rne75b7m.png)    
合并以后，会形成一个如 $101010\dots$ 一样的字符串，每个 $0$ 和 $1$ 代表一个区间。此时，每个 $0$ 代表一次操作。如果有 $K$ 个 $0$,那么总共花费为 $K \times Y$。
### 有 $1$ 操作
刚刚的方法并不能保证是最小花费。  
执行 $1$ 操作，将其中的一个 $1$ 和 $0$ 进行翻转后，如下图
![](https://cdn.luogu.com.cn/upload/image_hosting/cis7uv7r.png)  
把相同的合并
![](https://cdn.luogu.com.cn/upload/image_hosting/irpk0ang.png)  
就在刚刚的操作中减少了一个 $0$，这相当于把一个 $0$ 直接取反
![](https://cdn.luogu.com.cn/upload/image_hosting/ji9ci9f0.png)  
**所以，一个 $1$ 操作和一个 $2$ 操作本质上是相同的。**  
当然，执行到最后只剩下一个 $0$ 时，必须使用一次 $2$ 操作，使原字符串全部为 $1$。  
得本题的答案为  
设：原字符串中有 $k$ 段 $0$，$A$ 和 $B$ 代表操作 $1$ 和 $2$
$$
\min(A,B)\times(k-1)+B
$$
## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
long long n,x,y,sum=0;
int main(){
	cin>>n>>x>>y;
	cin>>s;
	s[n]='1';
	for(int i=0;i<n;i++){
		if(s[i]=='0'&&s[i+1]=='1') sum++;
	}
	if(sum==0) cout<<0;
	else cout<<(sum-1)*min(x,y)+y;
	return 0;
}
```
## 注意
要开 `long long`，如果没有原字符串中没有 $0$，则直接输出 $0$。

---

## 作者：Su_Zipei (赞：1)

## 分析
求最小花费让整个字符串变成1，看到最小花费，是不是想到了$Dp$，想到$Dp$就条坑里去了，用$Dp$的话，你会发现状态没法转移，因为它既涉及到了区间反转，又涉及到了区间更新。

　　两种操作还要分类讨论，很麻烦，这两种操作有什么内在联系呢？手动模拟一下会发现，反转一段区间，可以将两段0合并成一段，而区间更新没有限制，除了是一段连续区间外，所以，反转区间和合并区间的操作是等价的，故如果有$k$段0需要处理，可以先将它们合并成1段，再集中处理，最后一次更新区间肯定是要用的，因为0不可能平白无故变成1，所以讨论一下$k-1$次处理的选择方式就好，显然是取最小值，因为答案让求最小嘛。	
```
#include<iostream>
const int N=3e5+10;
char a[N];
using namespace std;
int main(){
    int n,x,y;
    cin>>n>>x>>y>>a+1;
    long long cnt=0ll;
    a[0]='1';
    for(int i=1;i<=n;i++)
        if(a[i]=='0'&&a[i-1]=='1')
            cnt++;
    if(cnt==0)cout<<0;
    else cout<<(cnt-1)*min(x,y)+y;
}
```

---

## 作者：傅思维666 (赞：1)

## 题解：
做法都是差不多，但我的讲解更详细一些：

我们要把01串变成1串，本质上是做什么?

最朴实的做法，是把所有0全部取反。

但是我们要求最小代价，所以这么裸着做肯定是不行。

所以我们开始认真看一下这个“翻转”操作。

什么时候我们用反转是比较优惠的呢？

就是，因为每次变化是不限量的，所以我们出于贪心考虑，一定是把这个串的0都归拢到一起，这样就可以用一次取反操作直接变成1串。

所以我们取反，其实就是归拢0的一个过程。

但是我们还会考虑这么一个问题：就是当我们的x比y大的话，取反就特别浪费。我们还莫不如直接把他们直接一段段取反，这样还会比反转后取反节约一点。

所以我们统计1之间夹0的段数，用long long 输出即可。

代码：

```c++
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
#define maxn 300001
using namespace std;
int cnt,n,x,y;
char str[maxn];
int main()
{
    scanf("%d%d%d",&n,&x,&y);
    scanf("%s",str+1); 
    str[0]='1';
    for(int i=1;i<=n;i++)
        if(str[i]=='0' && str[i-1]=='1')
            cnt++;
    if(cnt==0)
        puts("0");
    else 
        printf("%lld\n",(ll)(cnt-1)*min(x,y)+y);
    return 0;
} 
```



---

## 作者：guoxinda (赞：0)

## 思路
可以把 $0$ 合并成一段，然后执行 $2$ 操作。\
发现不仅 $1$ 操作可以实现合并， $2$ 操作也可以（因为只要变成一段，无论 $0$ 有多少都只用一次 $2$ 操作），于是：\
$a$ 原来的段数 $-1\times$ 两个操作花费的最小值 $+2$ 操作花费的 $=$ 最小花费数。\
注意，要减一再乘，因为有一段本身是要被其他段合并成一大段的。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
string a;
int n,x,y,ans;//ans储存字符串a的段数 
int main(){ 
	cin>>n>>x>>y>>a;
	for(int i=0;i<a.size();i++){
		if(i==0||a[i]=='0'&&a[i-1]=='1')ans++;
	}
	if(ans==0)cout<<0;//全为1
	cout<<(ans-1)*min(x,y)+y;//min(x,y)是因为用2操作和用1操作都可以合并，有一段不用操作，所以是ans-1 
	return 0; 
} 
```

---

## 作者：OIerZhang (赞：0)

# [CF997A Convert to Ones](https://www.luogu.com.cn/problem/CF997A)

## 思路

纯纯思维题。

通过观察，我们可以发现操作的子串的长度和它的代价是无关的，也就是 $011100101100001$ 等价于 $01010101$。

那么也可以推断出两种操作也是等价的，因为它们都可以合并两段区间。

这样，我们就用贪心思想，选取两种操作中代价小的来合并区间，最后用操作二将所有 $0$ 反转。设有 $n$ 段，则最终代价为 $\min(x, y) \times (n - 1) + y$。

相信各位大佬应该会求数字串有几段吧，实在不会就去看楼上。

注意有个特判，当数字串里全是 $1$ 时，不需要代价。

## 核心代码

结果最大 $3 \times {10}^{14}$，记得开 `long long`。

```cpp
if (cnt == 0)
{
    printf("0");
    return 0;
}
printf("%lld", min(x, y) * (cnt - 1) + y); // cnt 为段数
```

---

## 作者：浮光掠影 (赞：0)

### 思路

(目测普及-，做完后变成入门题)

可以发现操作总数一定等于 $0$ 的“段”数。因为每次翻转一段相当于合并一段 $0$，覆盖一段 $0$ 也相当于消去一段 $0$。

特判一下全 $1$ 的情况就对了。

### Code


```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=300005;
int x,y,cnt,n;
char s[N];
ll ans;
int main()
{
    scanf("%d%d%d",&n,&x,&y);
    scanf("%s",s+1); s[0]='1';
    for(int i=1; i<=n; i++)
	{
        if(s[i]=='0'&&s[i-1]=='1') cnt++;
    }
    if (!cnt) puts("0"); else printf("%lld\n",1ll*(cnt-1)*min(x,y)+y);
    return 0;
} 

```

---

## 作者：asas111 (赞：0)

## 思路
因为只有操作 $1$ 可以把 $0$ 变成 $1$，所以只要字符串中有 $0$，至少会执行一次操作 $2$。

对于其他连续的 $0$，用操作 $1$ 可以将它与另一段 $0$ 合并，用操作 $2$ 可以将这段 $0$ 删除，所以本质上它们是等价的，都可以减少一段 $0$。这样只需要比较哪个操作的花费少就行了，操作次数都是 $0$ 的段数减 $1$。

时间复杂度 $O(n)$，可以通过此题，记得开 long long。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string k;
int n,x,y,z=1,l=0;
signed main(){
	cin>>n>>x>>y>>k;
	for(int i=0;i<n;i++)
		if(k[i]=='0'&&z)l++,z=0;
		else if(k[i]=='1')z=1;
	cout<<(l?min(x,y)*(l-1)+y:0);
	return 0;
}
```


---

## 作者：大菜鸡fks (赞：0)

可以发现操作总数一定等于0的“段”数。因为每次翻转一段相当于合并一段0，覆盖一段0也相当于消去一段0。

特判一下全1的情况就ok了

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=300005;
int x,y,cnt,n;
char s[N];
ll ans;
int main(){
	scanf("%d%d%d",&n,&x,&y);
	scanf("%s",s+1); s[0]='1';
	for (int i=1;i<=n;i++){
		if (s[i]=='0'&&s[i-1]=='1'){
			cnt++;
		}
	}
	if (!cnt) puts("0"); else printf("%I64d\n",1ll*(cnt-1)*min(x,y)+y);
	return 0;
} 
```

---

## 作者：star_magic_young (赞：0)

~~虽然没打这场cf,但,,,这道题不难啊~~

### 思路
稍微考虑一下,如果这个串中有0,就必须用到第二个操作(取反操作).并且因为这个题目里操作子串可以任意选取,我们可以不用考虑连续的一段0或1的个数.所以可以先把0的段数$a$统计出来,对于每段0(除了最后一段),可以使用两种操作删掉这段0

举个例子

**0001**00 → **1000**00

**000**100 → **111**100

操作一次可以删掉一段0,所以选择花费最小的操作进行$(a-1)$次就行(好像从前往后删就没错),最后剩下一段只能用第二个操作(取反操作)

#### code
```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#define LL long long
#define il inline
#define re register

using namespace std;
const LL mod=998244353;
il LL rd()
{
    re LL x=0,w=1;re char ch;
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*w;
}
LL n,x,y,a;	//a为0的段数
char cc[300010];

int main()
{
  n=rd(),x=rd(),y=rd();
  cin>>cc;
  a+=cc[0]=='0';
  for(int i=1;i<n;i++)
    if(cc[i-1]=='1'&&cc[i]=='0') ++a;
  if(a==0) printf("0\n");
  else cout<<1ll*min(x,y)*(a-1)+y;
  return 0;
}

```

---

~~那啥,有反例欢迎举出~~

---

## 作者：dhpzy (赞：0)

# 题目
给你一个长度为 $n$ 的 $01$ 串( $n$ $\leq$ $3$ $\times$ $10^5$)，你有两种操作：
1. 将一个子串翻转，花费 $X$。
2. 将一个子串中的 $0$ 变成 $1$，$1$ 变成 $0$，花费 $Y$。\
求你将这个 $01$ 串变成全是 $1$ 的串的最少花费。
# 思路
先输入字符串的长度 $n$，然后再输入 $X$ 和 $Y$，最后输入字符串 $s$。\
对于字符串中的 $0$，我们肯定会执行一次操作 $2$，如果有连续的 $0$，那么就将它翻转，这样子可以减少一个 $0$。然后再比较两个操作花费的比较少就可以了，并且操作次数是 $0$ 的段数减 $1$。\
时间复杂度为 $O(n)$，最后记得开 long long。 
# AC代码
```
#include<bits/stdc++.h>
using namespace std;
string s;
long long n,x,y,sum=0;
int main()
{
	cin>>n>>x>>y>>s;
	if(s[0]=='0') sum++;
	for(int i=0;i<s.size();i++)
		if(s[i]=='0'&&s[i-1]=='1') sum++;
	if(!sum) cout<<0;
	else cout<<(sum-1)*min(x,y)+y;
}
```


---

