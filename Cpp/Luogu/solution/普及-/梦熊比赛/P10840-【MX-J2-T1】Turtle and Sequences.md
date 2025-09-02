# 【MX-J2-T1】Turtle and Sequences

## 题目背景

原题链接：<https://oier.team/problems/J2B>。

## 题目描述

给你一个序列 $a_1, a_2, \ldots, a_n$。你可以对这个序列进行若干次操作。

设一次操作前序列长度为 $m$，那么这次操作你可以选择一个整数 $i$ 使得 $1 \le i \le m - 1$ 且 $a_i \ne a_{i + 1}$，删除 $a_{i + 1}$ 并把 $a_i$ 的值设成**任意整数**。

求你最多能进行多少次操作。

## 说明/提示

#### 【样例解释 #1】

可以选择 $i = 1$，删除 $a_2$ 后把 $a_1$ 的值设成 $3$。此时 $a = [3]$，无法再进行任何操作。所以答案是 $1$。

#### 【样例解释 #2】

无法进行任何操作，所以答案是 $0$。

#### 【数据范围】

**本题采用捆绑测试且开启子任务依赖。**

| 子任务编号 | 分值 | $n \le$ | 特殊性质 | 子任务依赖 |
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $34$ | $2$ | 无 | 无 |
| $2$ | $19$ | $10^5$ | $a_1 = a_2 = \cdots = a_n$ | 无 |
| $3$ | $47$ | $10^5$ | 无 | $1, 2$ |

对于所有数据，满足 $1 \le n \le 10^5$，$1 \le a_i \le 10^9$。

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
1 1 45 14
```

### 输出

```
3
```

# 题解

## 作者：ydkxj (赞：6)

## P10840题解

#### 前言

回你咕打的你一场认真比赛？正好写一篇纪念一下。

### Solution

读题我们很容易得到：

- 修改后需要满足 $a_i \ne a_{i + 1}$ 。
- 如果其中每一个 $a_i$ 都相同的话，那就不能修改。
- 如果有两个 $a_i$ 不同的话，我们可以从左往右重置，那么重置的个数就是 $n-1$ 。

据此构建代码即可。

### CODE


```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[100005];
bool flag=0;
int main(){
	int m;
	cin>>m;
	cin>>a[1];
	for(int i=2;i<=m;i++){
		cin>>a[i];
		if(a[i]!=a[i-1])flag=1;
	}
	if(!flag)cout<<0;
	else cout<<m-1;
}
```

谢谢观看！

---

## 作者：yx666 (赞：6)

# P10840 题解
$$\text{Description}$$

给你一个序列 $a_1, a_2, \ldots, a_n$。你可以对这个序列进行若干次操作。

设一次操作前序列长度为 $m$，那么这次操作你可以选择一个整数 $i$ 使得 $1 \le i \le m - 1$ 且 $a_i \ne a_{i + 1}$，删除 $a_{i + 1}$ 并把 $a_i$ 的值设成**任意整数**。

求最多能进行多少次操作。

对于所有数据，满足 $1 \le n \le 10^5$，$1 \le a_i \le 10^9$。

$$\text{Solution}$$

先说结论。

## 结论
1. 如果 $\forall i\in[1,n-1],a_i=a_{i+1}$（即所有 $a_i$ 都相等），答案为 $0$。

2. 否则，答案为 $n-1$。

## 证明
结论 1，证明显然。

对于结论 2，归纳法可证（记 $f(i)$ 表示长度为 $i$ 时，至少存在一对不等的相邻数时，最大操作次数）：

- $n=1$ 时，$f(1)=0$，结论成立。

- $n>1$ 时，$f(n)=f(n-1)+1$，结论成立。因为我们可以通过每次操作，留下至少一对不等的相邻数（对于每次操作的 $i$，都将 $a_i$ 修改为一个没有出现过的数）。

$$\text{Code}$$

``` c
signed main(){
	int n=read(),tp=read();
	for(int i=1;i<n;++i){
		int t=read();
		if(t!=tp){
			printf("%d",n-1);
			return 0;
		}
	}putchar('0');
	return 0;
}
```

---

## 作者：thh_loser (赞：5)

# P10840 【MX-J2-T1】Turtle and Sequences 题解

[题目链接](https://www.luogu.com.cn/problem/P10840)

## 题意

给定一个长度为 $n$ 的序列，你可以对当前序列中任意 $a_i \ne a_{i + 1}$ 进行操作：删除 $a_{i + 1}$ 并把 $a_i$ 的值设成**任意整数**。求最多操作次数。

## 思路

通过观察，显然如果我们能够删掉 $a_{i+1}$，由于 $a_i$ 可以被赋为任意值，则对于 $a_i$ 与 $a_{i+2}$ 显然是能够做到不相同的，即可以再次消掉 $a_{i+2}$。同样的，$a_i$ 也可以与 $a_{i-1}$ 凑成一组，操作后删掉  $a_{i}$。

于是我们得到了一种思路，假如原序列中存在任意两个相邻的数不同，则可以操作至剩一个数，即 $n-1$ 次。否则为 $0$。

## code
```c++14
#include<bits/stdc++.h>
using namespace std;
int n,a[100010];
bool flag;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i]!=a[i-1]&&i!=1){//判断是否有不相同的
			flag=1;
		}
	}
	cout<<(flag?n-1:0);
	return 0;
}
```

---

## 作者：Louis_lxy (赞：3)

首先有一个结论，只要这个序列不是全部相同，那么答案就是 $n-1$，否则就是 $0$。

证明：先选择两个连续的不同的数，然后删掉后一个，前一个变成和它的前一个或者后一个不同的颜色，也就是 $\forall i\in[1,n]$，$a_i\ne a_{i+1}$，先删除 $a_{i+1}$，此时的 $a_{i+1}$ 变成原先的 $a_{i+2}$，然后当 $i\ne1$  $a_i\gets a_{i-1}+1$，反之 $a_i\gets a_{i+1}+1$（已经修改完后的），易得只要有两个数不相同，就能进行 $n-1$ 次消除操作（每次消除一个数，直到剩下一个数才会无法消除）。

AC 记录：https://www.luogu.com.cn/record/170479288

---

## 作者：___AaAa_bBcCd___ (赞：3)

题目：[P10840 【MX-J2-T1】Turtle and Sequences](https://www.luogu.com.cn/problem/P10840)

### 分析题目

我们观察题目发现，只要序列 $a$ 中所有的 $n$ 个数都一样，那就没有任意一个 $i$ 满足 $ a_i \neq  a_{i+1}$，一次都没法操作，只能输出 $0$。

只要有一个 $a_i$ 与其它的值不同，我们修改它时就可以把它变成一个极大且与序列 $a$ 中其它数都不同的数（例如 $10^9+i$）。当然我们不需要真正的记录下它，我们只要知道：这样的话，$a_{i-1}$ 也可以如此操作，$a_{i-2}$、$a_{i-3}$……一直到 $a_1$。向后看，$a_{i+1}$ 已经被删除了，我们继续操作 $a_i$，可以删除原来的 $a_{i+2}$、$a_{i+3}$……一直到 $a_n$。

如此操作下来，最终我们会止步于序列 $a$ 中只剩下一个元素的时候。而此时我们肯定是已经操作了 $n-1$ 次，所以最终答案就是 $n-1$。

### 编写代码

经过上面的推理，我们已经知道：当序列 $a$ 中所有元素都相同时，输出 $0$；否则输出 $n-1$。那接下来的代码编写就很轻松了：

```cpp
#include<iostream>
using namespace std;
int main(){
    int a[100001],n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=2;i<=n;i++){
        if(a[i]!=a[1]){
            cout<<n-1;
            return 0;
        }
    }
    cout<<0;
    return 0;
}
```

[如此我们便可以 AC 了。](https://www.luogu.com.cn/record/170554657)

---

## 作者：Zskioaert1106 (赞：1)

题目传送门：[P10840 【MX-J2-T1】Turtle and Sequences](https://www.luogu.com.cn/problem/P10840)

### 题目分析

由于只有在 $a_i \neq a_{i+1}$ 时才能对 $i$ 进行操作，所以如果序列中所有的序列都相同，就无法进行任何一次操作，输出 $0$ 即可。

对应子任务编号：$2$

但凡有一个 $i$ 可以操作，那我们就可以把 $a_i$ 设为任意一个不存在于序列 $a$ 中的整数。这样我们的下一次操作也可以顺利进行——毕竟这样 $a_i$ 和删除后新的 $a_{i+1}$ 也不同、$a_{i-1}$ 和 $a_i$ 也不同，都可以继续操作。如法炮制，直到序列中只剩下 $1$ 项，即可以进行 $n-1$ 次操作。

所以我们只要判断序列中是否所有元素都相同，如果是输出 $0$，如果不是输出 $n-1$ 就行了。

### 代码编写

```cpp
#include<iostream>
using namespace std;
int n,a[100005];
bool b=0;
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		if(i>0&&a[i]!=a[i-1])b=1;
	}
	if(b)cout<<n-1;
	else cout<<0;
    return 0;  
}
```

当然我们也可以不用数组存储，边输入边判断。

```cpp
#include<iostream>
using namespace std;
int n,a1,a2;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>a1;
	for(int i=1;i<n;i++){
		cin>>a2;
		if(a2!=a1){
			cout<<n-1;
			return 0;
		}
	}
	cout<<0;
    return 0;  
}
```

[AC 记录](https://www.luogu.com.cn/record/170484789)

---

## 作者：封禁用户 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10840)

先给出一个结论：如果 $a$ 数组的各项都相同，那么答案为 $0$，否则为 $n-1$。

为什么呢？我们可以举一个例子：比如 $a=\{1,1,1,1,5\}$ 的情况，我们可以进行如下操作：

1. $a_4\ne a_5$，把 $a_5$ 删除，把 $a_4$ 改为 $3$。此时 $a=\{1,1,1,3\}$
2. $a_3\ne a_4$，把 $a_4$ 删除，把 $a_3$ 改为 $3$。此时 $a=\{1,1,3\}$。
3. $a_2\ne a_3$，把 $a_3$ 删除，把 $a_2$ 改为 $3$。此时 $a=\{1,3\}$。
4. $a_1\ne a_2$，把 $a_2$ 删除，把 $a_1$ 改为 $3$。此时 $a=\{3\}$。

可以看出一共进行了 $4$ 次操作，也就是 $5-1$。另外如果 $a$ 数组各项相同的情况，我们就找不到 $a_i\ne a_{i+1}$ 的情况，所以一次操作都做不了。这样代码就很简单了。

```cpp
#include <iostream>
using namespace std;

const int N = 1e5 + 5;

int n, a[N];

bool Check()
{
    for (int i = 2; i <= n; i++)
    {
        if (a[i] != a[i - 1])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    if (Check()) cout << 0;
    else cout << n - 1;
    return 0;
}
```

---

## 作者：Ivan422 (赞：1)

考虑进行贪心。

首先，只要一个点可以把下一个点删掉，即 $a_i\neq a_i+1$，就可以把这个点改成任意数，进而让前面的满足条件。这时，先不着急把这个数删掉。我们发现，删掉下一个数并更改后，自己修改出来的数可以变的很大，后面的也可以全部删掉了。因此，我们得出来个惊人的结论：只要有一个点符合条件，答案就为 $n-1$，否则为 $0$。


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=1e6+10,M=1010,P=1e9+7,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
int n,a[N],ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<n;i++)if(a[i]!=a[i+1])ans=max(ans,i);
	if(ans==0)cout<<ans;
	else cout<<n-1;
    return 0;
}
//note:
```

---

## 作者：封禁用户 (赞：1)

这道题要求计算最多的次数，那么怎么计算呢？\
假设序列 $a_1,a_2, \cdots ,a_n$ 中所有的数都相等，即 $a_1 = a_2 =... = a_n $。\
因为对于任意的 $i (1 \le i \le n - 1)$，都有 $a_i = a_{i+1}$，不满足进行操作的条件 $a_i \ne a_{i + 1}$，所以无法进行任何操作，结果为 $0$。\
假设序列中存在至少一对不相等的相邻数，即存在 $i(1 \le i \le n - 1)$，使得 $a_i \ne a_{i + 1}$。\
从左到右进行操作，每次找到一对不相等的相邻数就进行操作。\
第一次操作后，序列长度减 $1$。\
第二次操作时，在新的序列中继续找到不相等的相邻数进行操作，序列长度又减 $1$。\
以此类推，每次操作都能使序列长度减 $1$，直到序列中只剩下一个数，此时共进行了 $n - 1$ 次操作。\
综上所述，当所有数都相等时，结果为 $0$；否则为 $n - 1$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,a[100001];
	cin >> n;
	for(int i=1;i<=n;i++) cin >> a[i];
	bool f=true;
	for(int i=1;i<n;i++){
		if(a[i]!=a[i+1]){
			f=false;
			break;
		}
	}
	if(f) cout << 0;
	else cout << n-1;
 	return 0;
}
```

---

## 作者：smydahaoren (赞：1)

### 题目思路

本题题意明确，可以用模拟的方式解决这道题。

有以下几种特殊情况：

-  $a$ 内数值全部相等。

-  删除 $a_{i+1}$ 后通过改变 $a_i$ 使得原本相等的 $a_{i-1}$ 和 $a_i$ 不再相等。

- 删除 $a_{i}$ 后通过删除使得原本不相邻的 $a_{i-1}$ 和 $a_{i+1}$ 相邻，增加可以删除的数量。

这三种情况的解决方法是：

-  加入一个判断函数，只有当数组中只剩下 $1$ 个数或者全部相等的时候跳出循环。

-  用随机数赋值 $a_i$。

-  循环操作。

解决后可以写出正确的代码。

### 代码

```
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define antirep(i,a,b) for(int i=a;i>=b;i--)
#define speed ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
const int N=1e6;
int n,a[N],ans;
bool check(int x){
	rep(i,1,x-1)
	if(a[i]!=a[i+1]) return 0;
	return 1;
} 
signed main(){
	speed;
	cin>>n;
	ans=0;
	rep(i,1,n) cin>>a[i];
	while(1){
		if(check(n)||n==1) break;
		antirep(i,n-1,1){
			if(a[i]!=a[i+1]){
				a[i]=rand();
				rep(j,i+1,n){
					a[j]=a[j+1];
				}
				n--;
				ans++;
			}
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：jiangyunuo (赞：0)

### 题目大意：
本题意思十分简单，就是有一长度为 $n$ 的序列，让你对这个序列进行一种操作，最后问你这个序列最多能做几次操作。
#### 操作方法：
每次操作都会选定一个整数 $i$，并且要保证 $a_i \ne a_{i + 1}$，接着我们会删除 $a_{i + 1}$，同时我们要把 $a_i$ 的值设成任意整数。
### 大体思路：
这题看起来很复杂，但实际上只要你发现答案其实就两种情况：  
1. 如果整个序列中没有哪两个数是不相等的，那么操作次数就是 $0$。  
2. 如果整个序列中至少有两个数是不相等的，那么操作次数就是 $n-1$。  

第一种情况很好理解，因为第一种情况根本就无法进行操作，可第二种操作我是怎么敢确定操作次数就是 $n-1$ 呢？只要我们从相邻的不相同的两个数入手（只要至少有两个数是不相等的，那么至少有两个相邻的数是不相同的），我们把这两个数分别设为 $a_i$ 和 $a_{i + 1}$，我们把 $a_{i + 1}$ 删除，接着我们把 $a_i$ 的值设为与相邻数字不同的就可以了，接着又可以重复以上过程，最终操作次数为 $n-1$。
### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    bool z=0;
    int a[n+1];
    for(int i=1;i<=n;i++){
    	cin>>a[i];
    	if(i!=1&&a[i]!=a[i-1])z=1;
	}
	if(z==1)cout<<n-1<<endl;
	else cout<<0<<endl;
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/170556276)

---

## 作者：Weekoder (赞：0)

### 思路

题意简化：给定一个数组 $a$，每次可以选择两个相邻且数值不同的元素合并，合并后可以用任意整数替换这两个数字。

由于可以用**任意整数**替换，所以一定可以替换成一个数组中没有出现的数字！不管是多少，$114514,2147483647,g_{g_{64}}......$ 总之，一定可以替换成一个整数 $x$，使得 $x$ 在任何时刻都不会与数组中其他元素相等。这意味着什么？这意味着，只要能合并一次，哪怕一次！就可以**无限制**地合并，直到只剩下一个数。更进一步，只要数组中存在**一个** $1\le i< n$ 使得 $a_i\ne a_{i+1}$，答案就为 $n-1$；否则，答案为 $0$。

代码如下：


```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

int n, a, b;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> a;
    bool flag = 0;
    for (int i = 1; i < n; i++) {
        cin >> b;
        if (a != b) flag = 1;
        a = b;
    }
    cout << (flag ? n - 1 : 0);
    return 0;
} 
```

---

## 作者：Ryzen_9_9950X3D (赞：0)

# 思路
不难发现，$1 \le N \le 10^5$，使用 $O(N^2)$ 时间复杂度的算法会超时。\
考虑使用类似于[地精排序](https://blog.csdn.net/zhizhengguan/article/details/104342818)的优化。\
将数组扫一遍，如果相邻两个数能够被操作，就对其进行操作，然后往前继续操作，直到相邻两个数不能被操作为止。
# 代码
我们可以通过以上的思路，得到以下的代码：
```cpp
#include <iostream>
using namespace std;
int s[1000005],nxt[1000005],pre[1000005];
int main()
{
    int a;
    cin >> a;
    for(int i = 1;i <= a;i++) cin >> s[i];
    for(int i = 1;i <= a;i++) nxt[i] = i + 1,pre[i] = i - 1;
    int k = 1,ans = 0;
    const int inf = 2000000000;
    int j;
    for(int i = 2;i <= a;i = nxt[j])
    {
    	j = i;
        while(i > 1 && s[pre[i]] != s[i])
        {
            i = pre[i];
            s[i] = inf + k;
            k++;
            ans++;
            nxt[i] = j + 1;
            pre[j + 1] = i;
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10840)

## 思路

先说结论：只要存在一个 $a_i\not =a_{i+1}\space (1\le i<m)$ 时即可删掉 $n-1$ 个数，否则一个都删不了。

证明：很容易构造出来，只要有至少一个 $a_i$ 与 $a_{i+1}\space (1\le i<m)$ 不同的时候，我们可以修改 $a_i$ 为任意一个数列中没出现过的数，删除 $a_{i+1}$，然后无限修改下去，到最终只剩一个数。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll read(){
	ll k=0;bool flag=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')flag=0;c=getchar();}
	while(c>='0'&&c<='9'){k=(k<<1)+(k<<3)+(c^48);c=getchar();}
	if(flag)return k;return -k;
}
const int N=1e5+10;
int a[N],n;
bool ok;
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		a[i]=read();
		if(i>1&&a[i]!=a[i-1])ok=1;
	}
	if(ok)cout<<n-1;
	else cout<<0;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/170551380)

---

## 作者：_H17_ (赞：0)

## 题目分析

如果全部相等：不能操作。

否则操作 $n-1$ 次，每次找一个不相等的相邻数对，然后把他们改成一个不相同与两边的数，然后可以继续操作，直到 $n=1$。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b;
int main(){
    cin>>n>>a;
    for(int i=2;i<=n;i++){
        cin>>b;
        if(b!=a){
            cout<<n-1;
            return 0;
        }
    }
    cout<<0;
    return 0;
}
```

---

## 作者：Archy_ (赞：0)

## 思路
很简单的分类讨论。

很明显，当数组所有数相同，那么一个数都不能修改，答案为 $0$。

反之，那么一定可以找到一个数使得与一个数不相等，那么这个数可更改为对应的负数，由于它后面的数与这个数一定不相同，则全部可以删除。它前面的一个数也和这个数不相同，所以前面的数也可以进行修改成对应的负数，删掉当前这个数。以此类推。最后只剩下第一个数。答案为 $n-1$。

例子：`1 1 2 5 6`

```
若选2
1 1 -2 6
1 1 -2  //我也可以不更改数
1 -1
1
```
## CODE

```cpp
#include<iostream>
using namespace std;
long long n, a, b, ans;
bool f;
int main(){
    cin >> n >> a;
	for(int i = 1; i <= n - 1; i++) {
		cin >> b;
		if(a != b) f = 1;
	}
	if(f)cout<<n-1;
	else cout <<0;
	return 0;
}
```

---

## 作者：zzx114514 (赞：0)

# 题目大意
给定一个序列，若该序列中有相邻两个元素不相等，则可以删去后一个，将前一个改为任意整数，问最多能操作几次。
# 解题思路
由于修改为任意整数，只要有相邻的元素不相等，则一定能将前一个元素能修改为与当前序列中任意一个元素都不相等的数，此时任意一个与其相邻的数都可以进行操作，最终可以操作 $n-1$ 次，只剩下一个数。如果所有元素都相等，则无法操作。   
即：若有相邻元素不相等，则可以操作 $n-1$ 次，否则可以操作 $0$ 次。
# 完整代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n,a[100005],ans;
int main()
{
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<n;i++)
		if (a[i]!=a[i+1])
		{
			cout<<n-1;
			return 0;
		}
	cout<<0;
	return 0;
}

```

---

## 作者：Tiger_Rory (赞：0)

我们可以从前往后模拟一遍，寻找思路。

这里使用样例三进行分析。

输入：```1 1 45 14```。
输出：```3```。

模拟过程：

第一次：到第三项时，删除 $45$，将 $1$ 改为 $2$；

第二次：删除这个 $2$，将 $1$ 改为 $13$；

第三次：删除 $14$，把 $13$ 改为 $2$，就结束操作了。


---


那么，我们发现，这是一个线性进行的过程，这让我想起了一个数据结构——队列。我们可以用队列来模拟这个过程。

我的思路：从第一项开始，将暂时删不掉的项入队（由于删不掉的必然与前一项相等，所以能保留在队列中的所有项都一定相等），接着当队尾遇到能被删除的项（就是与队尾不相等的项）时，立刻开始执行操作。因为之前能保留在队列中的所有项都相等，那么当我们追求最优，修改队尾的值时，队列中的所有项都可以被修改，那么此时还会有一个被修改的项存在队列里。我们不必关心此时它的值，因为它可以修改成任意整数，这就意味着从它开始，这个队列就只可能存在一个项，再往后模拟时，就只要一次一次加操作数就行了。因为它是任意的，所以之后的项肯定都会被其删掉。这道题就这样解决掉了。

由于每一项至多入队一次，所以时间复杂度为 $O(n)$，完全足以过掉这道题。详情见代码注释。

接下来是代码时间（代码比较拙劣，见谅）。


```cpp
#include<bits/stdc++.h>
#define maxn 100005
using namespace std; 

int n, ans; //ans计算操作数
int a[maxn]; 
queue<int> q; 

int main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0); 
	cin>>n; 
	bool ok=1; 
	for(int i=1;i<=n;i++) {
		cin>>a[i]; 
		if(i!=1&&a[i]!=a[i-1])ok=0;
	}
	if(ok) {//如果每一项都相等，就操作不了，输出0，对应第2个子任务
		cout<<0;return 0;
	}
	if(n<=2) {//一个小特判，对应第一个子任务
		if(n==1) cout<<0; //只有一项无法操作，输出0
		else cout<<1; //此时两项必然不相等，可以操作一次
                return 0; 
	}
        bool flag=0; //存储队首是否参与操作
	for(int i=1;i<=n;i++) {
		if(q.empty())q.push(a[i]);//如果队列为空就加入
		else if(a[i]==q.front()&&!flag)q.push(a[i]);  //如果和队首相等就删不了，要加入，但是如果队首之前参与过操作，这一项也得删除
		else {
			ans++; //要删，操作数加1
			while(q.size()>1){ //一次性操作到只剩一个
				flag=1;                  
				q.pop(); ans++; 
			}
		}
	}
        cout<<ans; //输出，一次过
	return 0; 
}
```
写作不易，还请各位点赞支持一下。

如有不足，还请指出，感谢各位观看。

---

## 作者：tanzexiaodezhonghao (赞：0)

# 思路
思维题。他其实这样的，从开头起，主打一个贪心思想，能操作的就操作。做个例子：

第一步先全部入列，如：变成 $\{1，2，45，14\}$。

第二部从头开始扫，如果头和头后面的元素不一样，删掉头即可，否则，把头和头后面的第一个元素删了，后面补充，再把原来的头加到队头。这一步相当于题目中的把下标为 $i + 1$ 的元素删掉，把下标为 $i$ 的元素变成任意整数。

那么问题来了，怎么不让新队头不与他的下一个元素相等呢？很简单，我们直接把原先下标为 $i+2$ 的元素多 $1$ 的数加进去即可。这样可能太抽象了，给一张图说明：

![](https://cdn.luogu.com.cn/upload/image_hosting/iiw3dlre.png)

然后同上持续操作，直到只剩一个元素不可操作为止。

看到上面的步骤，你会发现这就是一个双端队列的模拟。

但要注意有一点要特判，如果全部元素一样，无法操作，直接输出 $0$ 即可。

另外数据有点水，赛时我没加如果头和头后面的元素不一样，删掉头的判断也通过了。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int> m;
deque<int> Q;int n,x,cnt;
int main(){
	cin>>n;
	int cnt=0;cin>>x;n--;
	Q.push_back(x);m[x]++;bool flag=1;
	int flag1=0;
	while(Q.size()>1||flag==1){flag=0;
		if(n>=1){
			cin>>x;n--;if(x!=Q.back()) flag1=1;
			Q.push_back(x);
		}else{if(flag1==0){
			cout<<0;return 0;
		}
			int t=Q.front();Q.pop_front();
			cnt++;
			int t2=Q.front();
			if(t2==t) continue;Q.pop_front();
			Q.push_front(Q.front()+1);
		}
	}
	cout<<cnt;
	return 0;
}
```

---

## 作者：Bc2_ChickenDreamer (赞：0)

## P10840

### Sol

首先，全部相等的肯定是 $0$。

然后，我们分析一下。我们竟然有不相等的，我们必定会有操作，我们把它变为一个数组从未出现过的数字 $x_1$。这样操作后，数组还会有不相等的，就算 $n - 1$ 个数相等，如 $[3, 3, 3, 4]$ 把 $3, 4$ 改成 $5$ 数组会变成 $[3, 3, 5]$。也就是说，数组总会有不相等的。然后我们把这个数字 $x_1$ 去跟一个不相等的数字 $a_i$ 再改成 $x_2$。如 $[3, 3, 5]$，把 $3, 5$ 改成 $6$，变成 $[3, 6]$。我们以此类推，数组中总是会有不相等的，因为我们把数字改成了数组从未出现过的数字，所以说，答案为 $n - 1$。

### Code

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>

using namespace std;

using ll = long long;

const int kMaxN = 1e5 + 10, kInf = (((1 << 30) - 1) << 1) + 1;
const ll kLInf = 9.22e18;

ll n, a[kMaxN];

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++ i) {
    cin >> a[i];
  }
  bool f = 0;
  for (int i = 1; i < n; ++ i) {
    if (a[i] != a[i + 1]) {
      f = 1;
    }
  }
  cout << (!f? 0 : n - 1) << '\n';
  return 0;
}
```

---

## 作者：jiayixuan1205 (赞：0)

## 题解：P10840 【MX-J2-T1】Turtle and Sequences
### 分析
可以发现，所给数列中只要不全部相同，则相当于全部不同的情况，那么最多可修改的次数就是 $n-1$，反之，如果所给数列全部相同，那么最多可修改次数为 $0$。
### 代码展示
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 1e5+10;
int n,flag=0;
int a[N];

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=2;i<=n;i++)
	{
		if(a[i]!=a[i-1]) flag=1;
	}
	if(flag) cout<<n-1<<endl;
	else cout<<0<<endl;
	return 0;
}
```

---

## 作者：Getaway_Car_follower (赞：0)

我们注意到，只有 $a$ 相等时才不能分割，否则都行。

证明：

首先 $a$ 相等一定不行，因为我们不可能找到一个可以消掉的 $i$。

那么 $a$ 不等，我们一定可以找到一个 $x$，使得 $a_x\neq a_{x+1}$，我们就可以一直消掉最后一个满足条件的 $x$ 来消除整个 $a$。


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;
int n,a[N],fg;

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]!=a[i-1]&&i!=1) fg=1;
	}
	if(fg) cout<<n-1;
	else cout<<0;
	return 0;
}
```

---

## 作者：TemplateClass (赞：0)

不难得到如下性质：

1. 当 $a _ i$ 全部相等时，无法进行任何一次操作。
2. 只要 $a _ i$ 不是全部相等，就至少能进行 $1$ 次操作。
3. 存在无穷多个 $a _ i$，使得对于 $i \in [2, n - 1]$，有 $a _ i \neq a _ {i - 1}$ 且 $a _ i \neq a _ {i + 1}$。

所以由性质 2 和性质 3 可得只要 $a _ i$ 不是全部相等，就至少能进行 $1$ 次操作，而这次操作后又一定可以使 $a _ i$ 不是全部相等，就这样继续操作下去，可以只剩下一个元素。

所以得到：

- 如果 $a _ i$ 全部相等，输出 $0$。
- 否则，输出 $n - 1$。

```cpp
void solve(){
	std::cin >> n;
	for(int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}
	
	bool f = true; int x = a[1];
	for(int i = 2; i <= n; ++i) {
		if(a[i] != x) {
			f = 0; break;
		}
	}
	
	if(f) { std::cout << 0; return ; }
	
	std::cout << n - 1;
}
```

---

## 作者：block_in_mc (赞：0)

## 题目大意

对于一个序列 $a$，设当前长度为 $n$，定义**一次操作**为选择一个满足 $a_i\not=a_{i+1}$ 的正整数 $1\le i<n$ 且，删除 $a_{i+1}$ 并将 $a_i$ 变为任意整数。求最多能进行多少次操作。

## 解题思路

先给出结论：

- 若 $a_1=a_2=\cdot\cdot\cdot=a_n$，则最多操作次数为 $0$；
- 否则最多操作次数为 $n-1$（即最后可以只剩下一个数）。

接下来给出证明：

当 $a_1=a_2=\cdot\cdot\cdot=a_n$ 时，显然你无法找到一个 $i$ 使得 $a_i\not=a_{i+1}$，因此最大操作次数为 $0$。否则这个序列可以表示为：

$$\cdot\cdot\cdot,a_j,a_{j+1},\cdot\cdot\cdot$$

其中 $a_j\not=a_{j+1}$，因此我们可以删除 $a_{j+1}$，并将 $a_j$ 变为一个从未在序列中出现过的数。此时，对于 $a_j$ 前的数 $a_{j-1}$，有 $a_{j-1}\not=a_j$，可以删除 $a_j$ 并将 $a_{j-1}$ 的值改为 $a_j$，这等价于直接删除 $a_{j-1}$，不断进行此操作，可以删除 $a_j$ 前的全部数。同理，你也可以删除 $a_{j+1}$ 后的全部数。所以删除后只剩下 $a_{j}$，共进行了 $n-1$ 次操作。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100100];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    bool flag = true;
    for (int i = 1; i < n; i++)
        if (a[i] != a[i + 1])
            flag = false;
    if (!flag) printf("%d", n - 1);
    else printf("0");
    return 0;
}
```

---

