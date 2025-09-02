# [ABC115D] Christmas

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc115/tasks/abc115_d

とある世界では、今日はクリスマスです。

高羽氏のパーティで、彼は多次元バーガーを作ることにしました。*レベル $ L $ バーガー* ($ L $ は $ 0 $ 以上の整数) とは次のようなものです。

- レベル $ 0 $ バーガーとは、パティ $ 1 $ 枚である。
- レベル $ L $ バーガー $ (L\ \geq\ 1) $ とは、バン $ 1 $ 枚、レベル $ L-1 $ バーガー、パティ $ 1 $ 枚、レベル $ L-1 $ バーガー、バン $ 1 $ 枚、をこの順に下から積み重ねたものである。

例えば、パティを `P`、バンを `B` で表すと、レベル $ 1 $ バーガーは `BPPPB` (を $ 90 $ 度回転したもの)、レベル $ 2 $ バーガーは `BBPPPBPBPPPBB` といった見た目になります。

高羽氏が作るのはレベル $ N $ バーガーです。ダックスフンドのルンルンは、このバーガーの下から $ X $ 層を食べます (パティまたはバン $ 1 $ 枚を $ 1 $ 層とします)。ルンルンはパティを何枚食べるでしょうか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 50 $
- $ 1\ \leq\ X\ \leq\ ( $ レベル $ N $ バーガーの層の総数 $ ) $
- $ N,\ X $ は整数である。

### Sample Explanation 1

レベル $ 2 $ バーガー (`BBPPPBPBPPPBB`) の下から $ 7 $ 層にはパティが $ 4 $ 枚含まれます。

### Sample Explanation 2

レベル $ 1 $ バーガーの一番下の層はバンです。

### Sample Explanation 3

レベル $ 50 $ バーガーは層の数が $ 32 $ ビット整数に収まらない程度に分厚いです。

## 样例 #1

### 输入

```
2 7```

### 输出

```
4```

## 样例 #2

### 输入

```
1 1```

### 输出

```
0```

## 样例 #3

### 输入

```
50 4321098765432109```

### 输出

```
2160549382716056```

# 题解

## 作者：sz_wsy (赞：5)


#### [AT_abc115_d 题目传送门](https://www.luogu.com.cn/problem/AT_abc115_d)

## 题目大意
对于一种字符串 $str_i$：

- 当 $i=0$ 时，$str_i=\verb!P!$。

- 当 $i>0$ 时，$str_i=\verb!B!+str_{i-1}+\verb!P!+str_{i-1}+\verb!B!$。

求字符串 $str_n$ 的前 $x$ 个字符中有多少个为 $\verb!P!$。

## 算法分析
很显然，这是一道分治题。我们先通过举几个例子来找规律：

- $i=0$ 时，$str_0=\verb!P!$。
- $i=1$ 时，$str_1=\verb!BPPPB!$。
- $i=2$ 时，$str_2=\verb!BBPPPBPBPPPBB!$。

以此类推。

通过找规律发现，每一个字符串的长度，以及 $\verb!P!$ 的个数都有规律。直观地用代码表示，即：
```cpp
len[0]=1,P[0]=1;
for(int i=1;i<=n;i++){
	len[i]=len[i-1]*2+3; //len[i]: str_i的长度
	P[i]=P[i-1]*2+1;    //P[i]: str_i中P的个数
} 
```
至于它们的用处，以后会提及。

那么，既然是~~找规律~~分治，我们就可以把每一个 $str_i$ 分为五部分，以 $str_2$ 为例：

$\verb!B BPPPB P BPPPB B!$

不难发现，第一、三、五部分是固定的单字符，第二、四部分是 $str_{i-1}$。

回审题目：字符串 $str_n$ 的前 $x$ 个字符中有多少个 $\verb!P!$？那么，我们只要求出这 $x$ 个字符涉及几个部分就可以了：

先来观察下表（对于每个字符串）：

| 部分 | 长度范围 | 内容 | $P$ 的个数 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $1$ | $\verb!B!$ | $0$ |
|$2$  |$2\sim len[n-1]+1$  | $str_{n-1}$ | $P[n-1]$ |
| $3$ | $len[n-1]+2$ | $\verb!P!$ | $1$ |
| $4$ | $len[n-1]+3\sim len[n]-1$ |$str_{n-1}$  |$P[n-1]$ |
| $5$ | $len[n]$ |$\verb!B!$ | $0$ |

相信你一定发现了什么吧。没错，不管 $x$ 在哪里，只要将其之前（包括它）部分 $\verb!P!$ 的个数累加，即可。据此，我们就可以写出核心代码：
```cpp
//x在5种范围内的5种情况
if(x==1) return 0;
if(x<=len[n-1]+1) return dfs(n-1,x-1);
if(x==len[n-1]+2) return P[n-1]+1;
if(x<=len[n]-1) return P[n-1]+1+dfs(n-1,x-len[n-1]-2);
if(x==len[n]) return P[n];
```
## 代码呈现
```cpp
#include <iostream>
typedef long long LL;
using namespace std;
int n;LL x;
LL len[55];  //len[i]: str_i的长度 
LL P[55];    //P[i]:   str_i中P的个数 
LL dfs(int n,LL x){  
	if(n==0) return 1; //别忘了加上这句 
	if(x==1) return 0;
	if(x<=len[n-1]+1) return dfs(n-1,x-1);
	if(x==len[n-1]+2) return P[n-1]+1;
	if(x<=len[n]-1) return P[n-1]+1+dfs(n-1,x-len[n-1]-2);
	if(x==len[n]) return P[n];
}
int main(){
	scanf("%d%lld",&n,&x);
	len[0]=1,P[0]=1;
	for(int i=1;i<=n;i++){
		len[i]=len[i-1]*2+3;
		P[i]=P[i-1]*2+1;
	} 
	printf("%lld",dfs(n,x));  
    return 0;
}
```




---

## 作者：qwerty12346 (赞：4)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc115_d)

## 题意

就是求字符串为 $f_{n}$ 的前 $x$ 个字符中有多少个为 $p$。

## 思路

直接深搜就行了。如果 $i=0$ 那么 $f_{i}=P$，如果 $i>0$ 那么 $f_{i}=B+f_{i-1}+P+f_{i-1}+B$。这就是递推式子，往深搜套就可以了。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[100005]={1},f[100005]={1};
long long dfs(long long n,long long m){//深搜
    if(n==0)return 1; 
    if(m>a[n-1]+2)return f[n-1]+1+dfs(n-1,m-a[n-1]-2);//套递推式
    if(m==a[n-1]+2)return f[n-1]+1;//套递推式
    if(m>1)return dfs(n-1,m-1); //回溯
    return 0;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        a[i]=a[i-1]*2+3;//提前计算
        f[i]=f[i-1]*2+1;//提前计算
    }
    cout<<dfs(n,m)<<endl;
    return 0;
}
```


---

## 作者：Esperance (赞：3)

简单搜索题。这里提供一种更简单的递归思路。

设 $str_i$ 为第 $i$ 级字符串，$a_i$ 为第 $i$ 级字符串的长度，$c_i$ 为 $\texttt{P}$ 的个数。

第 $0$ 级字符串：$str_0 = \texttt{P}$，$a_0 = 1$，$c_0 = 1$；

第 $1$ 级字符串：$str_1 = \texttt{B} + str_0 + \texttt{P} + str_0 + \texttt{B} = \texttt{BPPPB}$，$a_1 = a_0 \times 2 + 3$，$c_1 = c_0 \times 2 + 1$；

第 $i$ 级字符串：$str_i = \texttt{B} + str_{i-1} + \texttt{P} + str_{i-1} + \texttt{B}$，$a_i = a_{i-1} \times 2 + 3$，$c_i = c_{i-1} \times 2 + 1$；

求第 $n$ 级字符串前 $x$ 位中 $\texttt{P}$ 的个数。

其实仔细思考会发现前 $x$ 位只有 $4$ 种情况：

1. $\texttt{B}+str_{i-1}+\texttt{P}+str_{i-1}$ 的一部分或全部（结尾 $\texttt{B}$ 不影响结果）；
2.  $\texttt{B}+str_{i-1}+\texttt{P}$；
3. $\texttt{B}+str_{i-1}$ 的一部分或全部；
4. $\texttt{B}$；

如果遇到整体的上级字符串就返回，没有就继续往下搜。注意 $n=0$ 时返回 $1$。

###  Code
```cpp
#include <iostream>
using namespace std;
typedef long long ll; // 答案很大 一定要开 long long
ll a[55], c[55], n, x;
ll dfs(ll n, ll x) {
	if (n == 0) return 1; //递归边界
	if (x > a[n-1]+2) return c[n-1] + 1 + dfs(n-1, x-a[n-1]-2); //1.
	else if (x == a[n-1]+2) return c[n-1] + 1; //2.
	else if (x > 1) return dfs(n-1, x-1); //3.
	return 0; //4.
}
int main() {
	a[0] = c[0] = 1;
	cin >> n >> x;
	for (int i = 1; i <= n; i++) a[i] = a[i-1]*2 + 3, c[i] = c[i-1]*2 + 1; // 预处理
	cout << dfs(n, x);
	return 0;
}
```

---

## 作者：Hyc_ (赞：1)

由题中的式子可推出：$str_{50}$ 的长度为 $4503599627370493$，所以此题无法暴力。

由递推式得：$str_i = B+str_{i-1}+P+str_{i-1}+B$。

所以我们可以从 $str_n$ 到 $str_1$ 依次尝试，若 $str_i$ 完全在区间 $1\sim x$ 内，就加上 $str_i$ 中 $P$ 的数量，然后返回，若部分不在就递归尝试 $str_{i-1}$，若完全不在就直接返回。

时间复杂度 $O(n\log_2n)$。

注意：
- 区间 $l=r$ 时直接返回。
- 区间中点一定为 $P$ 且不会被更小区间包含所以区间不被完全包含当区间中点被包含时答案要加一。
- 不开`long long`见祖宗。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,x,ans;
struct node{ll h,b;}a[52];
//a[i].h为str[i]的长度
//a[i].b为str[i]中'P'的数量
ll find(ll s){//找长度为s的str中有几个'P'
	for(int i=0;i<=n;i++)
		if(a[i].h==s)
			return a[i].b;
	return 0;
}
void dfs(ll l,ll r){
	ll mid=(l+r)>>1;
	if(l>x)return;//左端点比x大，直接返回
	if(r<=x){//若l~r在1~x内一定是一个完整的str，停止向下递归
		ans+=find(r-l+1);
		return;
	}
	if(mid<=x)ans++;//此位置在str[i]的正中间一定为'P'，且不会被str[i-1]包含
	if(l==r)return;//考试时没写这行挂了25分TLE
	dfs(l+1,mid-1);//搜左侧的str[i-1]
	dfs(mid+1,r-1);//搜右侧的str[i-1]
} 
int main(){
	scanf("%lld%lld",&n,&x);
	a[0].h=a[0].b=1;
	for(int i=1;i<=n;i++){
		a[i].h=a[i-1].h*2+3;
		a[i].b=a[i-1].b*2+1;
	}//预处理str[i]的长度及其中'P'的数量
	dfs(1,a[n].h);
	printf("%lld\n",ans); 
	return 0;
}
```
AtCoder 的 [AC 记录](https://atcoder.jp/contests/abc115/submissions/41074346)。

---

## 作者：lfxxx (赞：1)

考虑一个显然的分治：

```cpp
    if(i==0){
        if(j==1) return 1;
        else return 0;
    }
    if(j==1){
        return 0;
    }
    else if(j<=1+c[i-1]){
        return solve(i-1,j-1);
    }
    else if(j==2+c[i-1]){
        return solve(i-1,c[i-1])+1;
    }
    else if(j<=2+2*c[i-1]){
        return (1+solve(i-1,c[i-1])+solve(i-1,j-c[i-1]-2));
    }
    else{
        return 2*solve(i-1,c[i-1])+1;
    }
```

$c_x$ 表示 $str_x$ 长度。

但是这样子最差情况下会递归 $2^n$ 层，过不了。

但是我们发现加入每次把问题拆成两个子问题，一定有一个子问题是查询 $str_x$ 总贡献。

因此可以考虑预处理总贡献。

那么最后就只会递归 $n$ 次，总复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int c[100];
int ans[100];
int solve(int i,int j){
    if(j==c[i]) return ans[i];
    if(i==0){
        if(j==1) return 1;
        else return 0;
    }
    if(j==1){
        return 0;
    }
    else if(j<=1+c[i-1]){
        return solve(i-1,j-1);
    }
    else if(j==2+c[i-1]){
        return solve(i-1,c[i-1])+1;
    }
    else if(j<=2+2*c[i-1]){
        return (1+solve(i-1,c[i-1])+solve(i-1,j-c[i-1]-2));
    }
    else{
        return 2*solve(i-1,c[i-1])+1;
    }
}
int n,x;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>x;
    c[0]=1;
    ans[0]=1;
    for(int i=1;i<=n;i++) c[i]=c[i-1]*2+3,ans[i]=ans[i-1]*2+1;
    cout<<solve(n,x);
}
```


---

## 作者：Nightingale_OI (赞：1)

### 大意

你有一个 $ n $ 级汉堡，一个汉堡由若干个模块组成，每个模块为肉或馍。

定义 $ 0 $ 级汉堡为：肉。

所有 $ i $ （ $ i \geq 1 $ ）级汉堡为：馍， $ i - 1 $ 级汉堡，肉， $ i - 1 $ 级汉堡，馍（字符串形式拼接起来）。

比如：

 $ 0 $ 级汉堡为：肉。

 $ 1 $ 级汉堡为：馍肉肉肉馍。

 $ 2 $ 级汉堡为：馍馍肉肉肉馍肉馍肉肉肉馍馍。

现在这个人要从后往前吃 $ x $ 个模块，求会吃到多少肉。

### 思路

按题意分治，把每个大汉堡分为小汉堡考虑。

这样显然过不了，可以发现绝大部分都是分治整个汉堡，可以预处理。

预处理出每种等级的汉堡有多少模块和有多少肉即可。

时间复杂度 $ O(n) $ 。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
long long a[51];
long long b[51];
long long doing(int x,long long k){
    if(k==0)return 0;
    if(k==a[x])return b[x];
    return doing(x-1,max(min(k-a[x-1]-2,a[x-1]),0ll))+(k>=a[x-1]+2)+doing(x-1,max(min(k-1,a[x-1]),0ll));
}
int main(){
    long long k;
    cin>>n>>k;
    a[0]=b[0]=1;
    f(i,1,n)a[i]=a[i-1]*2+3;
    f(i,1,n)b[i]=b[i-1]*2+1;
    printf("%lld",doing(n,k));
    return 0;
}
```

---

## 作者：μηδσ (赞：1)

## Definition

第$i$级汉堡是由一个$B$一个$i-1$级汉堡一个$P$一个$i-1$级汉堡一个$B$组成的。（其中$B$为面包，$P$为肉饼）

求第$n$级汉堡的前k层有多少肉饼（$P$）

## Solution

先从$1$到$n$找出第一个层数比$X$大的级别$a$，之后级别再高对答案的影响只有最前面那几个$B$，那就是暴力找$a$中的前$m-(n-a)$层里有几个肉，如果正在查找的个数包含一些整层还可以直接调用之前算的肉层数。

## Code

~~~cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;

ll n, m;						//定义n,m
ll a[100], b[100];
/***dfs核心代码(上面已经详细说过)***/
ll dfs(ll x,int y){
	if(x <= 0)
		return 0;
	if(y == 0)
		return 1;
	if(a[y] == x)
		return b[y];
	ll ans = 0;
	if(x >= a[y - 1] + 1){
		ans += b[y - 1];
		if(x >= a[y - 1] + 2){
			ans++;
			if(x > a[y - 1] + 2){
				x -= a[y - 1] + 2;
				int i;
				for(i = 0;i < y;i++)
					if(a[i] + (y - i - 1) >= x)
						break;
				ans += dfs(x - (y - i - 1), i);
			}
		}
		return ans;
	}
	else{
		int i;
		for(i = 0;i < y;i++)
			if(a[i] + (y - i) >= x)
				break;
		return dfs(x - (y - i), i);
	}
}

int main(){
	ll tmp1 = 1, tmp2 = 1;
	cin >> n >> m;
	int i;
	for(i = 0;i <= n;i++){
		a[i] = tmp1;
		b[i] = tmp2;
		if(a[i] >= m)
			break;
		tmp1 = tmp1 * 2 + 3;
		tmp2 = tmp2 * 2 + 1;
	}
	cout << dfs(m - (n - i), i);
	return 0;
}
~~~

---

## 作者：Walrus (赞：0)

## 题意
给你一个数 $n$，表示一个字符串 $str_n$，这个字符串按照以下要求构造：

- 若 $i=0$，则 $str_i=P$
- 若 $i>0$，则 $str_i=B+str_{i-1}+P+str_{i-1}+B$

再给你一个数 $x$，问你 $str_n$ 前 $x$ 个字符中有多少个字符 $P$。

后文中用“级数”一词来表达当前是第几个汉堡。用“肉”来表示 $P$，用“馍”来表示 $B$。

## 思路
看到 $1\leq n \leq 50$，不难发现，汉堡的总大小，也就是字符串的总长度增长是非常快的，不考虑首尾及中间的字符，每次相当于都会在前一个字符串的基础上**翻一倍**，这启示了我们肯定不能暴力枚举。

考虑先递推出每一级汉堡的总层数和肉数，这个递推式其实在构造要求中已经告诉你了，定义 $b_i$ 表示第 $i$ 级汉堡的大小，$a_i$ 表示第 $i$ 级汉堡肉的个数，也就是字符 $P$ 的个数。我们有：

- $b_i=3+b_{i-1}\times 2$
- $a_i=1+a_{i-1}\times 2$
- 其中 $a_0=b_0=1$

不难发现，每一级的增长都是呈对称的，这样我们就会想到**分治**的做法，下面给出一种貌似没出现过的新方法，虽然可能要用到一点 **STL**。

- ### 前置芝士
`map` 是一个**双关键字容器**，可以将一种数据类型映射成另一种数据类型，本题使用 `map` 起到一个标记的作用，因为层数是非常大的，线性数组显然开不下。所以我们用它来进行标记的作用。

这里我们用 `map` 来记录如果当前有 $x$ 层汉堡，里面有多少肉，为了方便，这里映射下标，用代码理解比较好一点。

```cpp
for (int i = 1ll; i <= n; i++) {
    b[i] = 3 + (b[i - 1] << 1ll);
    a[i] = 1 + (a[i - 1] << 1ll);
    mp[b[i]] = i;
}
```
为什么可以这么直接映射下标呢？因为我们处理的时候都是一整个整个处理的，它对应的 $a_i$ 和 $b_i$ 都是已知的，只是缺少下标。

在分治的时候，我们因为只记录端点位置，所以我们相当于只知道当前有多少层汉堡，所以我们用 `map` 映射**下标**。

因为新加进来的肉在正中间，而两边的馍也没用，所以分治时要将左端点加一，中间点减一再进行分治，不过右半边要注意分治时是否在范围内，如果不全在就要特殊处理。

考场时就是因为没注意右半边的问题导致挂分，所以一定要注意范围。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 55;
int n, x, ans, sum, flag, t;
string s[N];
int a[N], b[N]; 
map<int, int> mp;
void merge(int l, int r) {
    int mid = l + r >> 1ll;
    if (l >= x) {//当右半边分治下来时先判断范围
        return;
    }
    if (l >= 1 && r <= x) {
        ans += a[mp[r - l + 1]];
        return;
    } else {
        if (l + 1 == mid - 1) {
            if (l + 1 <= x)
                ++ans;
        } else
            merge(l + 1, mid - 1);
        if (mid <= x)//中间的肉
            ++ans;
        if (mid + 1 == r - 1) {
            if (r - 1 <= x)
                ++ans;
        } else
            merge(mid + 1, r - 1);
    }
}

signed main() {
    //	freopen("hamburger.in", "r", stdin);
    //	freopen("hamburger.out", "w", stdout);
    cin >> n >> x;
    a[0] = b[0] = 1ll;
    mp[1] = 0ll;
    for (int i = 1ll; i <= n; i++) {
        b[i] = 3 + (b[i - 1] << 1ll);
        a[i] = 1 + (a[i - 1] << 1ll);
        mp[b[i]] = i;
    }
    merge(1ll, b[n]);
    cout << ans;
    return 0;
}
```


---

## 作者：Dreamerly (赞：0)

## 题目：[ AT_abc115_d](https://www.luogu.com.cn/problem/AT_abc115_d)
## 思路：
首先，看规模，$1\leq n\leq50$，但要是纯构造就凉凉了，比如最后一个样例，显然空间不够。因此这里选择递归搜索的思路。

其次，由于变换规则相当于将 $str_i$ 复制成两份，再加上两个 $B$ 和 一个 $P$。因此不难得出 $p_i=p_{i-1}\times2+1$ 以及 $sum_i=sum_{i-1}\times2+3$。至此，在查询完整的 $str_n$ 即 $sum_n$ 时，我们可以很快得出答案就是 $p_n$。

然后，手模几个字符串。$str_0=\texttt{P}$，$str_1=\texttt{BPPPB}$，$str_2=\texttt{BBPPPBPBPPPBB}$。思考后发现在 $str_i$ 中查询前 $x$ 个字符，可以通过**特殊性质**或 $str_{i-1}$ 算出。

**特殊性质：**

1. 当此时位置为 $str_0$ 时，只有 $1$ 个 $P$。即 `if(pos==0) return 1`。
1. 当查询的字符长度 $len$ 小于等于 $1$，要么为首字符且只可能为 $B$，要么不存在。故没有 $P$。即 `if(len<=1) return 0`。

**递归思路：**

代码中注释有递归思路的情况。~~主要我觉得放这里太冗长了~~
## 代码：
```cpp
#include<bits/stdc++.h>
#define int long long//偷懒写法，但本题需使用long long 
using namespace std;
int read(){
	int num=0,sign=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') sign=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		num=(num<<3)+(num<<1)+(ch^48);
		ch=getchar();
	}
	return num*sign;
}
void write(int x){
	if(x<0) putchar('-'),x=-x; 
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}
int ans;
int p[51];//p[i]表示str[i]中有几个 ‘P’ 
int sum[51];//sum[i]表示str[i]中有几个字母 
int dfs(int pos,int len){
	if(pos==0) return 1;
	if(len<=1) return 0;
	
	if(len==sum[pos-1]+1) return p[pos-1];//'B'+str[i-1]
	if(len==sum[pos-1]+2) return p[pos-1]+1;//'B'+str[i-1]+'P'
	if(len==sum[pos]-1)   return p[pos];//'B'+str[i-1]+'P'+str[i-1]
	if(len==sum[pos])     return p[pos];//'B'+str[i-1]+'P'+str[i-1]+'B'
	if(len<sum[pos-1]+1)  return dfs(pos-1,len-1);//'B'+(str[i-1] 中的前若干个) 
	return p[pos-1]+1+dfs(pos-1,len-sum[pos-1]-2);//'B'+str[i-1]+'P'+(str[i-1] 中的前若干个) 
}
signed main(){ 
	int n=read(),k=read(); 
	p[0]=1,sum[0]=1;
	for(int i=1;i<=50;i++){ 
		p[i]=(p[i-1]<<1)+1; 
		sum[i]=(sum[i-1]<<1)+3;
	}
	write(dfs(n,k));
	return 0;
}
```


---

