# [ARC119C] ARC Wrecker 2

## 题目描述

---

给出一个长度为 $n$ $(2\le n\le 3\times 10^5)$ 的正整数序列 $A_i$ $(1\le A_i\le 10^9)$，您可以进行以下两种操作：

- 操作 $1$：选定整数 x $(l\le x<r)$，$A_x \leftarrow A_x+1$，$A_{x+1} \leftarrow A_{x+1}+1$

- 操作 $2$：选定整数 x $(l\le x<r)$，$A_x \leftarrow A_x-1$，$A_{x+1} \leftarrow A_{x+1}-1$

**您需要保证任意时刻 $A_i$ 非负**。求问有多少个数对 $(l,r)$ 满足可以通过任意次操作使得 $A_l,A_{l+1}\ ...\ A_r$ 均为零？操作之间不互相影响。

翻译 by wukaichen888

## 样例 #1

### 输入

```
5
5 8 8 6 6```

### 输出

```
3```

## 样例 #2

### 输入

```
7
12 8 11 3 3 13 2```

### 输出

```
3```

## 样例 #3

### 输入

```
10
8 6 3 9 5 4 7 2 1 10```

### 输出

```
1```

## 样例 #4

### 输入

```
14
630551244 683685976 249199599 863395255 667330388 617766025 564631293 614195656 944865979 277535591 390222868 527065404 136842536 971731491```

### 输出

```
8```

# 题解

## 作者：灵茶山艾府 (赞：12)

遇到这种一次会改变多个数的题目，往往入手点在「不变量」上，也就是操作不会改变什么。

**交错和**是不变的。

那么题目就变成有多少个区间的交错和等于 $0$。

这是个经典问题，做法与「和为 $0$ 的子数组个数」是一样的，用前缀和 + 哈希表解决。

### AC 代码（Golang）

```go
package main
import ("bufio";."fmt";"os")

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, v, s, ans int
	cnt := map[int]int{0: 1}
	for Fscan(in, &n); n > 0; n-- {
		Fscan(in, &v)
		s += v * (n%2*2 - 1) // 奇数为 1，偶数为 -1
		ans += cnt[s]
		cnt[s]++
	}
	Print(ans)
}
```

### 复杂度分析

- 时间复杂度：$O(n)$。
- 空间复杂度：$O(n)$。


---

## 作者：jnyz2021109122116 (赞：2)

## Part 0
本题思考过程是最重要的，而解法很显然。  

**题意**：选定一个区间 $(l,r)$，使这个区间内任意**相邻**两座楼房的高度同时加 $1$ 或减 $1$，要求使区间内所有楼房的高度都变为 $0$。请求出有多少个满足要求的区间。  

Ps：下文称高度加 $1$ 为“增加”，高度减 $1$ 为“削减”。
## Part 1
我们先从最简单的情况开始分析。  
- 当区间长度为 $2$ 时，当且仅当两座楼高度相等时满足要求。
- 当区间长度为 $3$ 时，我们知道：对于两端的楼房，其操作必定为“削减”，这就要求中间楼房的高度恰好等于两端楼房的高度和。
- 当区间长度为 $4$ 时,我们设四座楼房的高度分别为
	$$a\ \ b\ \ c\ \ d$$  
  对两端的楼房“削减”后变成  
  	$$0\ \ b-a\ \ c-d\ \ 0$$
	是不是有点眼熟？我们把它变成了情况1。令 
   $$b-a=c-d$$
   可得
   $$a+c=b+d$$
- 当区间长度为 $5$ 时，设五座楼房的高度分别为
	$$a\ \ b\ \ c\ \ d\ \ e$$ 
   同理，对两端的楼房“削减”后变成  
  	$$0\ \ b-a\ \ c\ \ d-e\ \ 0$$
	梅开二度，我们把它变成了情况2。令 
   $$c=(b-a)+(d-e)$$
   可得
   $$a+c+e=b+d$$

**总结一下**，我们发现了啥？
- 对于任意长度大于等于 $2$ 的区间，都可以把它变成前 $2$ 种情况。
- 对于一个合法区间，其奇数位置上楼房的高度和必定等于偶数位置上楼房的高度和。 

那有同学就要问了：万一有的楼高度不够减怎么办？
我们大可放心“减”，上面的讨论已经包含可能出现的高度为负的情况。~~毕竟对负高度楼房来说，“增加”即“削减”。~~  

## Part 3
我们现在知道了这一结论，不妨把奇数或偶数位置上楼房的高度乘以 $-1$，于是区间和就变成了 $0$！
>我翻开算法书一查，这代码没有年代，歪歪斜斜的每页上都写着“我是蒟蒻”几个字。我横竖睡不着，仔细看了半夜，才从字缝里看出字来，满本都写着三个字是“前缀和”！

设前缀和数组为 $a_i$，对于合法区间 $(l,r)$，$a_{l-1}=a_r$。也就是说，如果前缀和数组中出现两个相同的数字，那么就对应一个合法区间。  
那出现三个甚至更多怎么办？——排列组合  
怎样记录数字出现的次数？——Map  

**Tips：**  
- long long
- 不要忘记前缀和数组第一项为 $0$。

>Talk is cheap,show me the code.

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll n,sum,ans; 
unordered_map<ll,int> v;
int main(){
	cin>>n;
	v[0]=1;
	for(int i=1;i<=n;i++){
		sum+=read()*(i%2? 1:-1);//省略快读
		ans+=v[sum]++;
	}
	cout<<ans<<'\n';
	return 0;
}
```


---

## 作者：Shizaki_Crazy_Three (赞：1)

# [ 题目链接](https://www.luogu.com.cn/problem/AT_arc119_c)

经典 trick ，不难发现满足要求的区间内的交错和是相等的，即奇数位的和等于偶数位的和。

因此我们可以将偶数位的数字乘上一个 $-1$ ，问题便转化为子数组和为 $0$ 的个数，用前缀和和 map 处理一下即可。

时间复杂度 $O(n\log_{}{n})$ ，记得开 long long 。

### code


```cpp
int n;
int a[N];
map<ll,int> m;
inline void solve(){
    ll ans=0;
    read(n);
    for(int i=1;i<=n;++i){
    	read(a[i]);
    	if((i&1)==0) a[i]*=-1;
    }
    ll sum=0;
    m[sum]++;
    for(int i=1;i<=n;++i){
    	sum+=a[i];
    	ans+=m[sum];
    	m[sum]++;
    }
    write(ans);
}
```

---

## 作者：Kevin911 (赞：1)

经典小学奥数题。
## 思路
可知每次操作后，奇数下标上和偶数下标上数之和的差不变，所以当且仅当 $l$ 到 $r$ 的区间上奇数下标上和偶数下标上数之和相等才能实现目标。

具体只需计算两种前缀和即可，统计时把前面所有的差都丢进 map 里即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=3e5+10;
int a[maxn],b[maxn];
map<int,int> mp;
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		if(i%2) a[i]=x;
		else b[i]=x;
		a[i]+=a[i-1],b[i]+=b[i-1];
	}
	int ans=0;
	mp[0]++;
	for(int i=1;i<=n;i++)
	{
		ans+=mp[a[i]-b[i]];
		mp[a[i]-b[i]]++;
	}
	cout<<ans;
}
```


---

## 作者：Jerry_heng (赞：1)

（一）

这题明显 $O(n)$ 复杂度，那么就找不变的东西。

我们发现，数列中变化的都是相邻的数，且变化量相同。

即 $A_1+A_3+ \dots +A_{2\times k-1}=A_2+A_4+ \dots +A_{2\times k}$。

记录前缀 $sum$。对于 $i\bmod 2=1$，$sum=sum+A_i$。

否则 $sum=sum-A_i$。

用 map 记录处理到每一位时的 $sum$。

（二）

AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long x,sum,ans;
map<long long,int> mp;
int main(){
	cin>>n;
	mp[0]=1;
	for(int i=1;i<=n;i++){
		cin>>x;
		if(i%2)sum+=x;
		else sum-=x;
		ans+=mp[sum];
		mp[sum]++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：HHC883 (赞：0)

# 题目分析
容易发现，我们可以直接从某个区间的第一个数开始操作，因为我们可以通过调整顺序使得任意时刻 $A_i$ 非负。于是，我们从 $i = l$ 开始，将 $A_i$ 加上 $-A_i$（因为要变成 $0$），那么 $A_{i+1}$ 也要加上 $-A_i$，到最后判断是否有 $A_r = 0$ 即可知道该区间是否可以。我们尝试将所有修改都累积到 $A_r$ 上，就能发现一个区间可以的条件为 $A_r - A_{r-1} + A_{r-2} - \cdots = 0$，其实就是**奇项和等于偶项和**。

下面来看如何判断一个区间是否满足奇项和等于偶项和。显然我们可以预处理前缀奇项和（记为 $prea$）与前缀偶项和（记为 $preb$），然后计算有多少对 $l , r$ 满足 $prea_r - prea_{l-1} = preb_r - preb_{l-1}$，移项得 $prea_r - preb_r = prea_{l-1} - preb_{l-1}$。于是记 $pre_i = prea_i - preb_i$，问题变为有多少对相同的 $pre_i$（注意 $i$ 可以为 $0$）。我们可以先排序，然后对每个极长相同数段分别求解。

时间复杂度为 $O(n \log n)$。
# 参考代码
```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int n,a[(int)3e5+5];
int pre[(int)3e5+5];
int ans;
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		if(i&1) pre[i]=pre[i-1]+a[i];
		else pre[i]=pre[i-1]-a[i];
	}
	sort(pre,pre+n+1);
	for(int i=0;i<=n;i++){
		int cnt=1;
		while(i<n&&pre[i]==pre[i+1]) cnt++,i++;
		ans+=cnt*(cnt-1)/2;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

# [ARC119C] ARC Wrecker 2

## 题面整理

给出一个长度为 $n$ $(2\le n\le 3\times 10^5)$ 的正整数序列 $A_i$ $(1\le A_i\le 10^9)$，进行以下两种操作：

- 操作 $1$：将 $A_x,A_{x+1}$ 各 $+1$。$(l\le x<r)$

- 操作 $2$：将 $A_x,A_{x+1}$ 各 $-1$。$(l\le x<r)$

**需要保证任意时刻 $A_i$ 非负**。求问有多少个数对 $(l,r)$ 满足可以通过任意次操作使得 $A_l,A_{l+1}\ \dots\ A_r$ 均为零？（注意我们不记录子区间，即在操作后 $(l,r)$ 是满足的，但要将其作为答案，要满足 $A_{l-1}≠0,A_{r+1}≠0$）

## 思路

乍一看时间复杂度，直接枚举区间肯定是不行的，况且即使枚举了区间，我们又应该怎么判断呢？所以当务之急，我们需要找到符合条件的区间都有怎么样的共性。

**先给结论**

若一个区间偶数位上的数之和和奇数位上的数之和相同时，此区间满足要求。

接下来我们来证明这个结论：

**推理法**

我们先看特殊情况：

1. 当区间长度为 $2$ 时，当且仅当 $a_1=a_2$ 时区间成立。
 
2. 当区间长度为 $3$ 时，当且仅当 $a_1+a_3=a_2$ 时区间成立。

接下来我们通过归纳法来推。

- 长度为 $4$：

设区间为 $a_1,a_2,a_3,a_4$。

我们先将两边减成 $ 0$→$0,a_2-a_1,a_3-a_4,0$，这时 根据上方的特殊情况，得知当且仅当 $a_2-a_1=a_3-a_4 $ 时区间成立，交换一下就是 $ a_1+a_3=a_2+a_4$——即偶数位和奇数位和相等。

- 长度为 $5$：

同理看步骤：

$a_1,a_2,a_3,a_4,a_5$ 

$\Rightarrow 0,a_2-a_1,a_3,a_4-a_5,0$

当 $a_2-a_1+a_4-a_5=a_3$，即 $a_2+a_4=a_1+a_3+a_5$ 成立时，区间成立。

- 长度为 $2\times n$：

同理看步骤：

$a_1,a_2,a_3,\dots\ ,a_{2n}$

$\Rightarrow 0,a_2-a_1,a_3,\dots\ ,a_{2n-2},a_{2n-1}-a_{2n},0 $

$\Rightarrow 0,0,a_3-a_2+a_1,\dots\ ,a_{2n-2}-a_{2n-1}+a_{2n},0,0 $

$\Rightarrow 0,\dots\ ,0,a_n-a_{n-1}+a_{n-2}-\dots-a_{2}+a_1,a_{n+1}-a_{n+2}+a_{n+3}-\dots-a_{2n-1}+a_{2n},0,\dots\ ,0 $

整理一下，得到充分必要条件：$a_n-a_{n-1}+a_{n-2}-\dots-a_{2}+a_1,a_{n+1}-a_{n+2}+a_{n+3}-\dots-a_{2n-1}+a_{2n}$

即：

$a_{1}+a_3+\dots+a_{2n-1}=a_2+a_4+\dots+a_{2n}$

- 长度为 $2\times n+1$

这里就不再说明了。

这样就得到了最初的结论。

**代码实现**

那么如何统计答案？实际上只需要用前缀和的方式，但是需要**奇加偶减（或者奇减偶加）**，再统计之前出现过这个前缀和的次数（即区间和为 $0$），这个统计过程由于值域较大需要离散化。


我们记录前缀和数组为 $qzh$，当 $qzh_i=qzh_j(i<j)$ 时，$[i+1,j]$ 是一个满足条件的区间。特别的，因为 $qzh_0$ 不会被扫描到，所以一开始就要在离散化数组 $mp$ 中初始化 $mp_0=1$。

## Code

```C++
#include<bits/stdc++.h>
#define int long long
#define db double
#define rtn return
#define i1n int i=1;i<=n;i++
#define in1 int i=n;i>=1;i--
using namespace std;

const int N=3e5+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

int n,k,a[N],cny,cnt,ans, qzh[N];//qzh是前缀和
map<int,int> mp;

signed main(){
    cin>>n;
    mp[0] = 1;//初始化,当前面某个前缀和值为i,第二次扫描到某个前缀和值为i时,产生一个答案.当
    for(int i = 1 ; i <= n ; ++ i)
    {
        cin>>a[i];
        if(i&1) qzh[i] += qzh[i - 1] + a[i]; //奇加偶减,i&1等效于i%2
        else qzh[i] += qzh[i - 1] - a[i];
        ans+=mp[qzh[i]];
		mp[qzh[i]]++;
    }
    cout<<ans<<endl;
    return 0;
}
```




---

## 作者：I_am_sb___ (赞：0)

此题有一个~~一眼~~结论，如果一个区间偶数位上的数之和和奇数位上的数之和相同时，这个区间就可以成立，由于本人是个蒟蒻，并不能一眼看出这个结论，所以还是老实的推结论吧。

虽然之前一眼看出那个结论有点太快了，但是有两个结论是显然的：

1. 当区间长度为 $2$ 时，当且仅当两个数相等时区间成立；
2. 当区间长度为 $3$ 时，当且仅当两端的数和与中间相等时区间成立；
 
这两个结论显然都符合我们需要的最终结论，是否可以通过归纳法来确定区间长度为 $N$ 时结论是否成立呢。

可以先看看区间长度为 $4$ 时结论是否成立：设四个大小为 $abcd$，然后先将两边减成 $0$，就变成了 $0,b-a,c-d,0$，这时当且仅当 $b-a=c-d$ 区间才有成立，这个式子换一下就是 $b+d=c+a$——即偶数位和奇数位和相等时，区间才会成立。我们以这种方式换，当且仅当奇数位和与偶数位和相同时，区间才成立——这样就得到了最初讲的一眼结论。

那么如何统计答案？实际上只需要用前缀和的方式，但是当统计到偶数（或奇数）时前缀和减掉这一位，再统计之前出现过这个前缀和的次数（简单组合），这个统计过程由于值域较大需要离散化。

~~就一个前缀和还想要代码~~

code：
```cpp
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <cmath>
#include <queue>
#include <vector>
#include <map>
#include <set>

#define int long long

using namespace std;

template<typename T>inline void read(T &FF){
	T RR=1;FF=0;char CH=getchar();
	for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
	for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
	FF*=RR;
}

template<typename T>inline void write(T x){
	if(x<0)putchar('-'),x*=-1;
	if(x>9)write(x/10);
	putchar(x%10+48);
}

const int N = 300007;
const int M = 1000007;
const int mod = 1e9 + 7;

int n;
int ans;
int a[N] , s[N];
map<int , int> p;

signed main(){
    read(n);
    p[0] = 1;
    for(int i = 1 ; i <= n ; ++ i)
    {
        read(a[i]);
        if(i % 2) s[i] += s[i - 1] + a[i]; 
        else s[i] += s[i - 1] - a[i];
        ans += p[s[i]] ++;
    }
    write(ans);
    return 0;
}
```

---

## 作者：ivyjiao (赞：0)

- 当 $r-l=1$ 时，当且仅当 $a_{l}=a_{r}$ 时符合条件，这显然两个数只能全部操作 $2$。
- 当 $r-l=2$ 时，当且仅当 $a_{l}+a_{r}=a_{l+1}$ 时符合条件，这不那么显然了：因为对于 $a_{l}$ 和 $a_{r}$，其操作必然全是操作 $2$，也就是说，$a_{l+1}$ 要被减 $a_{l}+a_{r}$ 次。
- 当 $r-l=3$ 时，我们还是对两侧的数字不断执行操作 $2$ 直至 $a_{l}=a_{r}=0$，这时 $a_{l}=0,a_{l+1}=a_{l+1}-a_{l},a_{r-1}=a_{r-1}-a_{r},a_{r}=0$ 这不就可以转化成 $r-l=1$ 的情况吗！此时，当且仅当 $a_{l+1}=a_{r-1}$ 时，符合条件。
- 当 $r-l=4$ 时，我们仍然对两侧的数字不断执行操作 $2$ 直至 $a_{l}=a_{r}=0$，这时 $a_{l}=0,a_{l+1}=a_{l+1}-a_{l},a_{l+2}=a_{l+2},a_{r-1}=a_{r-1}-a_{r},a_{r}=0$ 这不就可以转化成 $r-l=2$ 的情况吗！此时，当且仅当 $a_{l+1}+a_{r-1}=a_{l+2}$ 时，符合条件。
- 性质出来了：对于每个 $r-l>2$，我们均可以将其转化成 $r-l=1$ 或 $r-l=2$ 的形式！
- 准确的：对于每个 $(r-l)\bmod 2=1$，我们均可以将其转化为 $r-l=1$ 形式；对于每个 $(r-l)\bmod 2=0$，我们均可以将其转化为 $r-l=2$ 形式。
- 那么这题规律就出来了：对于一个区间当且仅当其奇数下标上楼房的高度和等于偶数下标上楼房的高度和。
- 用前缀和解，设前缀和数组为 $b$，对于任何合法区间 $(l,r)$，$b_{l-1}=b_{r}$，也就是若 $b$ 中出现 $2$ 个相同的数字，那么就是一个符合条件的区间。
- $\geq 3$ 个怎么办？排列组合！
- map 存数字。
- 不开 long long 见祖宗。
- 时间复杂度 $O(n)$。

```
#include<iostream>
#include<map>
using namespace std;
long long n,a,cnt,ans,f;
map <long long,long long> q;
int main(){
    cin>>n;
    q[0]=1;
    for(int i=1;i<=n;i++){
        cin>>a;
        if(i%2==0) f=1;
        else f=-1;
        cnt+=a*f;
        ans+=q[cnt];
        q[cnt]++;
    }
    cout<<ans;
}
```

---

