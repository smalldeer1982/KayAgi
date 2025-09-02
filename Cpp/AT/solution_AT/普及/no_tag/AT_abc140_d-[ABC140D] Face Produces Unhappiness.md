# [ABC140D] Face Produces Unhappiness

## 题目描述

有 $N$ 个人从东向西排成一排，每个人的状态用一个字符串 $S$ 表示，第i个字符 $s_i$

 表示从西边数起第 $i$ 个人的朝向```L```
表示面朝西， ```R``` 表示面朝东。

对于队伍中的每个人，如果自己面前的人的朝向和自己一样，那么这个人就会感到幸福。如果面前的人朝向和自己不一样，或者面前没有人，这个人就感到不幸福。

你可以进行以下操作最多 $K$ 次（也可以一次都不进行）：

选择整数$l,r（1≤l≤r≤N）$，让从西边数起第 $l,l+1,⋯,r$ 个人转身180度。

经过最多 $K$ 次操作后，感到幸福的人最多有多少人？

## 样例 #1

### 输入

```
6 1
LRLRRL```

### 输出

```
3```

## 样例 #2

### 输入

```
13 3
LRRLRLRRLRLLR```

### 输出

```
9```

## 样例 #3

### 输入

```
10 1
LLLLLRRRRR```

### 输出

```
9```

## 样例 #4

### 输入

```
9 2
RRRLRLRLL```

### 输出

```
7```

# 题解

## 作者：_Life_ (赞：10)

给出一种基于 **异或差分** 的思路

我们先将 $\texttt{LR}$ 串转换为 $\texttt{01}$ 串

异或差分的代码为 $x_{i}=x_{i}\ xor\ x_{i+1}\ (i>=0)$

通过手玩容易发现：翻转原区间 $[L,R]$ 等价于在差分序列中翻转 $x_{L-1},x_{R}$

在差分序列中，$\texttt{0}$ 代表相邻两个人的方向相同，代表有一个幸福的人。我们的目标是最大化幸福的人数，等价于让 $\texttt{0}$ 的数量最大化。

所以就有了一个显然的贪心：在每次的翻转操作中，我们都在差分序列中选取两个为 $\texttt{1}$ 的位置进行翻转，这样每次操作都会有两个 $\texttt{1}$ 变成 $\texttt{0}$ 

注意：答案的最大值只能为 $n-1$ ，记得特判

总时间复杂度 $O(n)$

```cpp
#include<cstdio>
using namespace std;
char str[100005];
int n,k,x[100005],ans;
int main()
{
	scanf("%d %d %s",&n,&k,str+1);
	for(int i=1;i<=n;i++)
		x[i]=(str[i]=='L');
	for(int i=0;i<=n;i++)
		x[i]^=x[i+1];
	for(int i=1;i<n;i++)
		ans+=(x[i]==0);
	ans+=2*k;
	if(ans>=n)
		ans=n-1;
	printf("%d",ans);
}
```

---

## 作者：small_john (赞：5)

## 思路

其实挺简单的。

由于每次翻转，不会改变内部情况，只会把左端点的状态和右端点的状态改变。所以每次操作最大贡献是 $2$。

先统计原来满意的人数 $sum$，最后答案就是 $\min\{n-1,sum+2\times k\}$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans;
string s;
signed main()
{
	cin>>n>>k>>s;
	for(int i = 0;i<s.size()-1;i++)
		if(s[i]==s[i+1])
			ans++;
	cout<<min(n-1,ans+k*2);
	return 0;
}
```

---

## 作者：Lydia1010__ (赞：5)

## 本题思路：
这道题其实很简单，因为他每一次变化就会将 $l$ 到 $r$ 的所有字母反过来，然后顺序调换。这样我们为了保持结果的最大值，那么我们就可以先记录当前的值，然后把相同且相邻的合成一个数，接着排序，最后选出最长的 $k$ 段，每段再加二即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[114514];
struct f{
	int x,y;
}b[114514];     
int y(f x,f y)
{
	return x.x>y.x;
}
int main()
{
	long long n,k,m=0,ans=0;
	cin>>n>>k;
	cin>>a+1;
	for(int i=2;i<=n;i++) 
	{
		if(a[i]==a[i-1]) ans++;
	}
	long long o=1,cnt=0;
	for(int i=2;i<=n;i++)
	{
		if(a[i]!=a[i-1]) b[++cnt].x=o,o=1;
		else o++;
	}
	sort(b+1,b+1+cnt,y);
	for(int i=1;i<=min(k,cnt);i++) ans+=2;
	cout<<min(n-1,ans);
	return 0;
}
```


---

## 作者：Parat_rooper (赞：3)

# 题意描述：
有N个人自西往东站成一排，给定长为N的字符串S表示每个人的方向，L表示面朝西，R表示面朝东。如果一个人前面有人并且朝向跟他一样，那么他会开心。
你现在可以最多进行K次操作，每次可以选择连续的一段l到r并翻转这些人的站位以及朝向，求最多有多少人可以开心。

# 输入格式
人数$n$, 操作次数$k$ 以及一串字符（朝向）

## 解题思路：（大佬勿喷）
首先我们可以对题目稍加简化:

给你一个01串，要求你在反转k个区间及其值后，有多少个$i$,$j$满足 $a_i$ = $a_j$ 且abs($i$ - $j$) = 1

然后我们明确本题做法：

# ~~贪心~~  简单模拟
~~虽然我也不知道算不算~~
	


------------

好，既然明确了做法我们就来谈谈具体的实现思路：~~（应该是对的）~~

首先我们可以发现，位置这个属性对结果其实没有什么影响   ~~（反正我没考虑）~~， 所以，我们只要尽可能多的将序列的值变得相同就行了。

然后代码就很好写了，每次遇到与之前不同的值就取反（注意此处指的是整个值不同的区间），然后$k-1$


# 再然后这题就结束了，

~~轻松加愉快~~



------------


上代码：


```cpp
#include <iostream>

using namespace std;

const int kMaxN = 1e5 + 1;

int n, k, ans;
char str[kMaxN];
bool a[kMaxN];

int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> str[i];
    if (str[i] == 'L') {
      a[i] = 0;//01串简化
    } else {
      a[i] = 1;
    }
  }
  for (int i = 1; i <= n && k > 0; i++) {
    if (a[i + 1] != a[i]) {//与之前的值不同
      k--;
      i++;
      a[i] = !a[i];
      while (str[i] == str[i + 1]) {//整个区间取反
        i++;
        a[i] = !a[i];
      }
    }
  }
  for (int i = 2; i <= n; i++) {
    if (a[i] == a[i - 1]) {//统计变形后序列中开心人数
      ans++;
    }
  }
  cout << ans;
  return 0;
}


---

## 作者：洛璟 (赞：2)

这道题目作为模拟赛的T2……确实……挺有思维难度的……考场上推了好久……

## Solution

我们观察这个序列，可以发现，对于每一堆连续的 $L$ 与 $R$ ，如果我们将其翻转，和另外一个 $R$ 或 $L$ 连续的序列连在一起，那么只有可能增加两个“幸福”的人。
```
sample 1：

6 1
LRLRRL
```
我们观察这个样例，可以发现，一开始，已有一个人是幸福的，那么，我们去翻转一下第二个 $R$ 可以发现，被翻转的 $R$ 及第三个 $L$ 都幸福了，也就是说有4人幸福了。

换一个人，我们翻转第四个至第五这个区间的两个 $R$ 可以发现，两个 $R$ 翻转成 $L$后这个小区间其中一个仍然幸福，并且多出了两个幸福的人，也就是第四到第五这个小区间中的一个人及第三个人。

也就是说，如果我们每一次翻转两端均不相同的一段人（形如 $LLRRRRRL$ 中的 $R$ 那一段），那么就会增加两个幸福的人，并且由于这一段所有人都一样，所以相当于翻转了所有人的朝向，位置不变。

这样我们就可以得出，我们每一次翻转增加的幸福的人数，与序列长度无关，也就是说我们可以直接忽略连续子序列的长度，只需要知道其属于 $L$ 或 $R$ .

那如果没有被夹住的一段人了呢？

很简单，说明剩下的序列形如$sample\space2$，只剩下了两段不同的序列了，那么我们如果此时还有剩下的操作次数，我们便可以一次性翻转到整个序列完全一致，达到最优状态，此时答案为 $n-1$。

哦对了，对于每一长段，需要进行离散化，形如把 $RRRRLLLRR$  变为 $RLR$，方便进行判别。

可以结合代码食用qwq。
## Code： 
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, cnt, ans;
int c[100010];
int l[100010];
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
int main()
{
    n = read();
    m = read();
    memset(c, 0x7fffffff, sizeof(c));//初始化，int下为-1
    memset(l, 0x7fffffff, sizeof(l));
    char ch = getchar();
    while (ch != 'R' && ch != 'L')
    {
        ch = getchar();
    }
    for (int i = 1;i <= n;++i)
    {
        c[i] = ch == 'R' ? 1 : 0;//可有可无的转化
        ch = getchar();
    }
    int qwq = 1;
    for (int i = 1;i <= n;)
    {
        while (c[i] == c[i + 1])
        {
            i++;
        }
        l[qwq++] = c[i];//l数组中记载离散化后的序列
        i++;
    }
    for (int i = 1;i <= n;++i)
    {
        if (c[i] == 1 && c[i + 1] == 1)//统计初始序列中幸福的人数
        {
            ans++;
        }
        if (c[i] == 0 && c[i - 1] == 0)
        {
            ans++;
        }
    }
    qwq--;
    for (int i = 2;i < qwq;++i)
    {
        if (l[i] != l[i - 1] && l[i] != l[i + 1])//判断是否被不同的序列夹在中间
        {
            ans += 2;//若是，则翻转，幸福人数加2
            cnt++;
            l[i] = l[i - 1];
        }
        if (cnt >= m) break;//超过限制次数则break
    }
    if (cnt < m) ans = n - 1;//若没有了被夹在中间的序列，并且还有操作机会，则达到最优状态
    printf("%d", ans);
    return 0;
}
```

---

## 作者：fp0cy1tz6mn4rd_ (赞：1)

## 思路
每次翻转，只会改变左端点和右端点的状态，所以每次翻转都只会增加 $2$。当然，要想让感到幸福的人最多，那就得转 $k$ 次，一共就会增加 $2\times k$ 个人。除了这些还要考虑到第一个人前面是没人的，所以在作比较时必须是 $n-1$。

## 代码
```cpp
#include<iostream>
using namespace std;
int main(){
	int n,k,res=0;
	string s;
    cin>>n>>k>>s;
    for(int i=0;i<n;i++)
        if(s[i]==s[i-1])
            res++;
    res=min(ans+2*k,n-1);
    cout<<res<<endl;
    return 0;
}
```

---

## 作者：_7Mr (赞：1)

# 思路

**一个不太一样的思路**

首先我们将当前已经幸福的人数统计出来，因为这些人不管我们怎么翻转，都是幸福的。接下来我们将不幸福的人数统计出来，然后我们判断不幸福的人数的 $\frac{1}{2}$ 与 $k$ 的大小，我们取最小值，然后让答案加上这个最小值的 $2$ 倍，也就是我们翻转后幸福的人数，但是有个特殊情况，如果不幸福的人数是个偶数，又小于 $k$ 也就是说明 $R$ 或者 $L$ 有一个在边上，这是我们将会多统计一个，答案也就要减去 $1$。
# ACcode
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF INT_MAX
using namespace std;
const int maxn=1e5+5;
int n,k,ans;
char s[maxn];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>s[i];
    for(int i=1;i<=n;i++) {
        if(i>1 && s[i]=='L' && s[i-1]=='L') ans++;//统计已经幸福的人数
        if(i<n && s[i]=='R' && s[i+1]=='R') ans++;	
    }
    int p=1;
    for(int i=2;i<=n;i++) if(s[i]!=s[i-1]) p++;//当前还不幸福的人数
    ans+=(min(k,p/2)*2);//取最小值的2倍
    if(p%2==0 && p/2<=k) ans--;//特殊情况
    cout<<ans<<endl;
	return 0;
}

```

---

## 作者：VERACITY (赞：1)

## 思路
当结论题写的。    
考虑翻转一个左右两端不同的区间，手玩样例发现每次转完之后，两端的人变得幸福，那么答案增加 $2$，想让幸福的人最多，那就转 $k$ 次，一共增加 $2 \times k$ 个人。将原来就幸福的人加上转完之后变得幸福的人就是最终答案。注意一点，因为有个人他面前是没有人的，所以答案最大是 $n-1$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,cnt;
string s;
int main()
{
	cin >> n >> k >> s;
	for(int i=0;i<n;i++) 
		if(s[i]==s[i-1]) 
			cnt++;
	cout<<min(n-1,cnt+2*k);
	return 0;
}
```

---

## 作者：CodingOIer (赞：0)

## AtCoder ABC140 D 题解

### 思路分析

对于这道题，每次翻转之后的结果的中间部分的幸福的人数和原来没有任何区别，只有两边的人可能会和旁边的人产生新的幸福的人，下面是一个例子：

Before：

```
LLLRRLLRLRRLL
```

After：

```
RRRLLRRLRLLRR
```

Before 的幸福的人数为 $6$。

After 的幸福的人数依然为 $6$。

在 $K$ 次翻转中，我们只需要选取两个旁边不符的位置，翻转这一段即可得到 $2$ 个新的幸福的人数。

就算最后没有了，也可以翻转单个人来获得 $1$ 个新的幸福的人。

写模拟？不，我们再分析一下规律：

- 当 $N$ 足够大时，增加的幸福的人最多为 $2 \times K$。

- 在一组数据中，幸福的人最多为 $N - 1$。

所以，设数据中初始的幸福的人为 $answer$，则答案为：

$$
\min(answer + 2 \times K, N - 1)
$$

### 代码实现

先统计出初始的幸福的人，后面直接输出 $\min(answer + 2 \times K, N - 1)$。

```cpp
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#define debug printf("Debug\n")
typedef long long ll;
const int inf = 0x3f3f3f3f;
const int MaxN = 1e5 + 5;
int n, k;
int answer;
char s[MaxN];
int main()
{
    scanf("%d%d", &n, &k);
    getchar();
    scanf("%s", s);
    for (int i = 1; i < n; i++)
    {
        if (s[i] == s[i - 1])
        {
            answer++;
        }
    }
    printf("%d\n", std::min(answer + 2 * k, n - 1));
    return 0;
}
```

---

