# [ABC393D] Swap to Gather

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc393/tasks/abc393_d

给定一个由 `0` 和 `1` 组成的长度为 $ N $ 的字符串 $ S $。保证 $ S $ 中至少包含一个 `1`。

你可以重复以下操作任意次数（包括零次）：

- 选择一个满足 $ 1 \leq i \leq N-1 $ 的整数 $ i $，交换 $ S $ 的第 $ i $ 个字符和第 $ i+1 $ 个字符。

求使所有 `1` 聚集在一起所需的最小操作次数。

这里，所有 `1` 聚集在一起的定义是：存在整数 $ l, r \ (1 \leq l \leq r \leq N) $，使得对于 $ S $ 的第 $ i $ 个字符，当且仅当 $ l \leq i \leq r $ 时为 `1`，否则为 `0`。

## 说明/提示

### 约束条件

- $ 2 \leq N \leq 5 \times 10^5 $
- $ N $ 为整数
- $ S $ 是由 `0` 和 `1` 组成的长度为 $ N $ 的字符串
- $ S $ 中至少包含一个 `1`

### 样例解释 1

例如，按以下步骤进行 $ 3 $ 次操作后，所有 `1` 将聚集在一起：
- 选择 $ i=2 $，交换 $ S $ 的第 $ 2 $ 和第 $ 3 $ 个字符，此时 $ S= $ `0011001`；
- 选择 $ i=6 $，交换 $ S $ 的第 $ 6 $ 和第 $ 7 $ 个字符，此时 $ S= $ `0011010`；
- 选择 $ i=5 $，交换 $ S $ 的第 $ 5 $ 和第 $ 6 $ 个字符，此时 $ S= $ `0011100`。  
由于无法在 $ 2 $ 次或更少操作内完成，因此答案为 $ 3 $。

### 样例解释 2

所有 `1` 已经聚集在一起，因此无需任何操作。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
7
0101001```

### 输出

```
3```

## 样例 #2

### 输入

```
3
100```

### 输出

```
0```

## 样例 #3

### 输入

```
10
0101001001```

### 输出

```
7```

# 题解

## 作者：da_ke (赞：6)

注：本文涉及大量推导，如果读者发现谬误请批评指正！

## Solution

> fyy 是一个非常珂愛的女孩子。
> 
> fyy 认为一个 $01$ 序列中如果所有 $1$ 都是连续的，那么这个序列很珂愛。fyy 想通过有限次操作使得一个序列变得珂愛。对于每次操作，她只能交换两个相邻的数。
>
> fyy 问妳最少的操作次数是多少？

> 讲一下一个假的做法。看到这个题立马想到 ABC 以前的一道题，把所有的 $1$ 都往最左边的一个移动。错误很显然。

这个问题很**迷惑**，实际上所有 $0$ 都是没用的，只需考虑 $1$。

钦定最优情况一定是选择一个 $1$ 作为合并的起始点，将其两边的 $1$ 逐渐合并。$0$ 的情况参见后面的「一个补充证明」。

形式化的说，序列中给出了 $M$ 个 $1$，其中第 $i$ 个 $1$ 的位置是 $X_i$。选定第 $k$ 个 $1$。

求

$$\sum\limits_{i=1}^{k-1} \left[X_k-X_i-(k-i)\right]+\sum \limits_{i=k+1}^{M} \left[X_i-X_k-(i-k)\right]$$

的最小值（其实上式也可写成绝对值形式）。

> 不妨考虑一个子问题。给定 $M$ 个数轴上的点 $(X_1,X_2,\dots,X_M)$。设 $x$ 为任意一点。求 $\sum\limits_{i\in[1,M]}|x-X_i|$ 的最小值。运用几何直观，显然当且仅当 $x$ 在中间两点所成区间（包含区间端点）内时取得最小值（如果 $M$ 为奇数那么 $x=X_{mid}$，$mid$ 为 $1\sim M$ 的中间值 $\left\lfloor \frac{M}{2}\right\rfloor+1$）。
>
> 对此的证明可以翻开你的人教版七年级第一章有理数的各种教辅资料，应该都有这种题目。

下面证明 $\sum\limits_{i\in [1,M]} |k-i|$ 为定值：

$\sum\limits_{i\in [1,M]} |k-i|=\sum\limits_{i\in [1,k-1]} (k-i)+\sum\limits_{i\in [k+1,M]}(i-k)=1+2+\dots+k-1+1+2+\cdots+M-k$。其中 $k$ 被消了，与 $k$ 无关。

于是我们的这个问题和子问题的取最小值的条件是类似的。所以我们可以找到一个使得原式取得最小值的点，即为 $X_{\left\lfloor \frac{M}{2}\right\rfloor+1}$。

于是我们解决了这个问题。下面形式化做法：

- 找出所有点 $(X_1,X_2,\dots,X_M)$，找出中间点为合并初始点，也就是 $X_{\left\lfloor \frac{M}{2}\right\rfloor+1}$。这个点记为 $X_{mid}$。
- 求出 $\sum\limits_{i=1}^{mid} \left[X_{mid}-X_i-(k-i)\right]+\sum \limits_{i=mid+1}^{M} \left[X_i-X_{mid}-(i-k)\right]$ 的值。

### Code

下面是代码：

```cpp
int main()
{
    int N; string S;
    cin>>N>>S;
    S=' '+S;
    int mid,M=0,cnt=0;
    rep(i,1,N)
        if(S[i]=='1') M++;
    rep(i,1,N)
        if(S[i]=='1')
        {
            cnt++;
            if(cnt==M/2+1){mid=i; break;}
        }
    M=M/2+1;
    ll ans=0; cnt=0;
    rep(i,1,mid-1)
        if(S[i]=='1')
        {
            cnt++;
            ans+=mid-i;
            ans-=(M-cnt);
        }
    cnt=M;
    rep(i,mid+1,N)
        if(S[i]=='1')
        {
            cnt++;
            ans+=i-mid;
            ans-=(cnt-M);
        }
    cout<<ans<<endl;
}

// 路虽远行则将至，事虽难做则必成。
// 代码省略缺省源（所以直接交上去会 CE），完整代码放在底下。
```

AC 记录：<https://atcoder.jp/contests/abc393/submissions/62799606>

### 一个补充证明

我们刚开始钦定了选 $1$ 是根据**直觉**的。下面详细说明 $0$ 的情况

如果选的 $0$ 的点为 $X_0$，在这个点左侧有 $l$ 个 $1$，右侧有 $M-l$ 个 $1$。$M$ 个 $1$ 点为 $(X_1,X_2,\dots,X_M)$。

类似的列出最终的式子：

$$\sum\limits_{i\in [1,l]} [X_0-X_i-1-(l-i)]+\sum\limits_{i\in [l+1,M]} [X_i-X_0-1-(i-l-1)]$$

这表明，如果 $M$ 为偶数，选 $0$ 也能得到最小值；若为奇数，则得不到最小值。

---

## 作者：ryf2011 (赞：3)

# 题目思路
关注到 $N$ 的范围很大，我们无法暴力。

我们用一个数组记录字符串中每个字符 $1$ 的位置。记录完成后，我们找到所有的 $1$ 中最中间的那一个，这一步要保证准确性。以这个 $1$ 为基准，分别向左半部分和右半部分枚举，在这期间记录答案。

对于左半部分，我们将答案加上一个值，这个值是当前这个 $1$ 的位置与上一个的位置的差再减 $1$ 得来的。随后，我们将当前 $1$ 的位置改为交换完成后应当所在的位置。右半部分同理。

需要注意的是，向左半部分枚举时，顺序是从右往左，向右半部分枚举则是从左往右。因为只有按照这种顺序枚举才能保证对当前的 $1$ 做操作时它的上一个 $1$ 已经做完了操作，才不会出错。

最后注意，答案有可能超出 $\texttt{int}$ 的存储范围，所以要开 $\texttt{long long}$ 才能保证通过此题。

# 代码
注：本代码不保证为最简写法，仅供参考。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define int long long //一定注意开 long long！ 
using namespace std;
int n,swapmid,ans,cnt,omid;
//swapmid：所有 "1" 中最中间的 "1" 的值；ans：答案；cnt:字符串中 "1" 的个数；omid：所有 "1" 中最中间的 "1" 的位置 
char s[500005];
int onel[500005]; //记录每个 "1" 所在的位置 
signed main(){
	//输入 
	scanf("%lld",&n);
	scanf("%s",s+1);
	//计算 
	for(int i=1;i<=n;i++){
		if(s[i]=='1'){ //记录每个 "1" 的位置 
			cnt++;
			onel[cnt]=i;
		}
	}
	//保证记录最中间 "1" 的位置的变量值是准确的，避免误差 
	if(cnt%2==0){
		omid=cnt/2;
	}
	else{ //如果 cnt 是奇数，为保证准确性，cnt 除以 2 后再加 1 
		omid=cnt/2+1;
	}
	swapmid=onel[omid]; //最中间的 "1" 的值 
	for(int i=omid-1;i>=1;i--){ //枚举左半部分 
		ans+=(abs(onel[i]-onel[i+1])-1); //注意：减去的值是上一个移动完的 "1" 的值，而不是 swapmid 
		onel[i]=onel[i+1]-1; //把当前 "1" 的位置转移至交换完成的位置 
	}
	for(int i=omid+1;i<=cnt;i++){ //枚举右半部分 
		ans+=(abs(onel[i]-onel[i-1])-1);
		onel[i]=onel[i-1]+1;
	}
	//输出 
	printf("%lld\n",ans);
	return 0;
}
```

#### 后记
更多内容，请移步至 [$\color{red}\texttt{ryf2011}$](https://www.luogu.com.cn/user/1151973 "点我进入ryf2011")。

---

## 作者：Tomwsc (赞：2)

# AT_abc393_d [ABC393D] Swap to Gather 题解

[Myblog](https://blog.csdn.net/Popandsoss2022/article/details/145789735?sharetype=blogdetail&sharerId=145789735&sharerefer=PC&sharesource=Popandsoss2022&spm=1011.2480.3001.8118)

## 题意

给定一串只有 ```0``` 和 ```1``` 的字符串，可以将相邻的两个字符交换，问至少需要多少步才能让所有的 ```1``` 相邻。

## 思路

非常结论的一道题目。

设有 $m$ 个 ```1```，则把所有的 ```1``` 都移到与第 $\frac{m}{2}+1$ 个 ```1``` 相邻的位置有最优解。

为什么，举例说明一下：

若 $m$ 为奇数。

假设有这么一串数：

$$1\underbrace{0\cdots 0}_{a个0}1\underbrace{0\cdots 0}_{b个0}1$$

若把所有的 ```1``` 都移到与中间那个 ```1```相邻的位置，则所需步数为：$a+b$。

若要把所有的 ```1``` 都移到与两旁的 ```1``` 相邻的位置，则所需步数为：$a+2\times b$ 或 $2\times a+b$。

很显然，这两个答案一定都会比 $a+b$ 大。所以，在 $m$ 为奇数时，把所有的 ```1``` 都移到与第 $\frac{m}{2}+1$ 个 ```1``` 相邻的位置时有最优解。

若 $m$ 为偶数。

假设有这么一串数：

$$1\underbrace{0\cdots 0}_{a个0}1\underbrace{0\cdots 0}_{b个0}1\underbrace{0\cdots 0}_{c个0}1$$

若要移到与第一个 ```1``` 相邻的位置，则所需步数为：$a\times 3+b\times 2+c$。

若要移到与第二个 ```1``` 相邻的位置，则所需步数为：$a+b\times 2+c$。同理，移到与第三个 ```1``` 相邻的位置所需步数也是：$a+b\times 2+c$。

若要移到与第四个 ```1``` 相邻的位置，则所需步数为：$a+b\times 2+c\times 3$。

此时，可以发现把所有的 ```1``` 都移到与第 $\frac{m}{2}$ 个 ```1``` 到第 $\frac{m}{2}+1$ 个 ```1``` 相邻的位置时都有最优解。所以不妨也把所有的 ```1``` 都移到与第 $\frac{m}{2}+1$ 个 ```1``` 相邻的位置。

其实这题就是一个绝对值方程求最值。

## 代码

直接模拟即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 5e5 + 10;
int n;
char a[MAXN];
int num;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(register int i = 1;i <= n;i ++) {
		cin >> a[i];
		if(a[i] == '1')
			num ++;	
	}
	int k , cnt = 0 , ans = 0;
	for(register int j = 0 , i = 1;j < num / 2 + 1;i ++)
		if(a[i] == '1') {
			k = i;
			j ++;
		}
	for(register int i = k - 1;i >= 1;i --)
		if(a[i] == '1') {
			ans += (k - i - 1 - cnt);
			cnt ++;
		}
	cnt = 0;
	for(register int i = k + 1;i <= n;i ++)
		if(a[i] == '1') {
			ans += (i - k - 1 - cnt);
			cnt ++;
		}
	cout << ans;
}
```

---

## 作者：xingkong1 (赞：2)

# 题意
可能有写的不对的地方，求大佬指正。

[abc393_d](https://atcoder.jp/contests/abc393/tasks/abc393_d)

[luogu_abc393_d](https://www.luogu.com.cn/problem/AT_abc393_d)

题目大意是给我们一个数字 $n$，然后给我们长度为 $n$ 的 $01$ 字符串，可以把相邻两个字符互换，让我们求让所有的 **1** 相邻的最少步数。

## 思路
我们先建立一个变量 $n$ 和字符串 $s$， $n$ 用来存储字符串长度，字符串 $s$ 用来存储 $01$ 字符串。
我们可以再建立一个数组 $b$ 来存储每个 $1$ 都在什么位置，用变量 $e$ 来表示有几个 $1$，用 $mid$ 表示最中间的 $1$ 是第几个。

由于我们要求最少步数，就可以把其他的 $1$ 往最中间的 $1$ 靠拢，这样所需步数一定是最小的，如图：
![](https://tailchat-nightly.moonrailgun.com/static/files/66a88e7f49ed234d1301485c/4be2b979579ace5add61e9d4aea68690.png)

黄字需要步数为 $8$ 步，而往中间靠拢只需要 $5$ 步。

对于每一个不是最中间的 $1$ ，我们先计算出他和最中间的 $1$ 的距离，再减去他和最中间的 $1$ 相隔的 $1$ 的数量，就可以得出需要的步数，用变量 $ans$ 存储，最后输出就行啦。

[AC链接](https://www.luogu.com.cn/record/204138138)

### 代码
```cpp
#include<bits/stdc++.h>
#define  cfs cout << fixed << setprecision
#define ll unsigned long long
#define int long long
#define endl '\n'
using namespace std;
char s[500010];
int a[500010];//定义不用说了吧
int e;
signed main()
{
	int n;
	cin >> n;
	cin >> s;//输入

	for(int i=0;i<n;i++)
	{
		if(s[i]=='1')//如果是1，则储存位置
		{
			a[++e]=i;
		}
	}

	int mid=(e+1)/2;//计算中间的1是第几个
	int ans=0;

	for(int i=1;i<=e;i++)
	{
        if(i==mid)//中间的1不需要判断
		{
			continue;
		}

		ans+=abs(a[mid]-a[i]);//计算距离
	    ans-=1;//由于是相邻，无需重合，所以减1

        ans-=abs(mid-i);//这个1与最中间的1中间有几个1
        ans+=1;//由于会把自己也算差一个，所以会多减1步，所以加回来
        //↑上面的计算和前面计算相反，可以都省略
	}

	cout << ans;//输出~
	return 0;//完结撒花的好习惯
}
```

---

## 作者：__Floyd__ (赞：1)

麻烦管理员大大通过一下 $QWQ$
## 题目大意
给定一个 $0/1$ 字符串 $s$ ，在 $i$ 位置的字符可以花费 $1$ 代价移动到与它相邻的位置 $( i - 1 $ 和 $i+1)$，请求出把 $s$ 中所有字符 $1$ 变成一段连续的子串的最小代价
## 正解
有一个很显然的贪心：我们应该选定一个位置 $x$ ，让所有在 $x$ 右方的 $1$ 向左移到与它相邻，在 $x$ 左方的 $1$ 向右移到与它相邻，大致是这样：

原数组 $($ 这里假定选择的 $x = 5$ $)$


|下标|1|2|3|4|5|6|7|8|9|10|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|字符 (0/1)|1| 0|0|1|1|0|1|0|1|1|

移动后


|下标|1|2|3|4|5|6|7|8|9|10|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|字符 （0/1）|0|0|1|1|1|1|1|1|0|0|

在上面这组样例中：
$1$ 位置的 $1$ 移动到了 $3$ 位置

$4$ 位置的 $1$ 移动到了 $4$ 位置

$7$ 位置的 $1$ 移动到了 $6$ 位置

$9$ 位置的 $1$ 移动到了 $7$ 位置

$10$ 位置的 $1$ 移动到了 $8$ 位置

所以付出的总代价 `Val=abs(3-1)+abs(4-4)+abs(6-7)+abs(7-9)+abs(8-10)=7`

我们把上面这个式子整理一下可得

`Val=( (3+4) - (1+4) ) + ( (7+9+10) - (6+7+8) ) = (左边的初始位置下标之和 - 左边的结束位置下标之和) + (右边的结束位置下标之和 - 右边的初始位置下标之和) = last_l - first_l + first_r - last_r`

显然，初始位置可以用一个前缀和数组 $dis$ 记录

同时我们发现，结束位置构成了一个公差为 $1$ 的等差数列，且长度为序列中 $1$ 的数量

设 $cnt_i$ 表示 $i$ 位置之前 $1$ 的数量 $($ 包括它本身 $)$ ，则依据等差数列之和的计算公式可得  `last_l = ( ( i - 1 ) + ( i - cnt[i-1] ) ) * ( cnt[i-1] ) / 2`

同理，`last_r = ( ( ( cnt[n] - cnt[i] ) + i ) + ( i + 1 ) ) * ( cnt[n] - cnt[i] ) / 2`

那么，这道题我们就做完了，接下来我们只要对每一个位置计算贡献，取最小值即可

### Here is the code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read(){
	ll x;scanf("%lld",&x);return x;
} 
const ll N=1e6+10;
ll cnt[N],dis[N],n,ans=1e18;
string s;
int main(){
	n=read();
	cin>>s;
	s=' '+s;
	for(int i=1;i<=n;i++){
		cnt[i]=cnt[i-1];
		if(s[i]=='1') cnt[i]++;
	}
	for(int i=1;i<=n;i++){
		dis[i]=dis[i-1];
		if(s[i]=='1') dis[i]+=i;
	}
	for(int i=1;i<=n;i++){
		if(s[i]=='1'){
			ll l=cnt[i-1],r=cnt[n]-cnt[i],sum1=dis[i-1],sum2=dis[n]-dis[i];
			ll now1=(i-1+(i-l))*l/2,now2=((r+i)+(i+1))*r/2; 
			ans=min(ans,now1-sum1+sum2-now2);
		}
	}
	cout<<ans<<endl;
	return 0;
}

---

## 作者：cqbzhzf (赞：1)

[vjudge 中文翻译](https://vjudge.net/problem/AtCoder-abc393_d#author=GPT_zh)
### 思路
  贪心思想。想要移动距离最小，肯定是向中间靠拢，可显然正解并不是直接在原数组中取最中间的数。
  
首先记录下 $S_i=1$ 的位置 $id_j$。其次计算出 $id_j-j$，$tt_i$，即每个 $1$ 的预期移动距离。此时，在 $tt$ 数组中找到中位数并计算答案。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,id[N],cnt,ans;
string s;
vector<int> tt;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>s;
	s=' '+s;
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='1')
			id[++cnt]=i;
	}
	for(int i=1;i<=cnt;i++)
		tt.push_back(id[i]-i);
	sort(tt.begin(),tt.end());
	int mid=tt[cnt/2];
	for(int i:tt)
		ans+=abs(i-mid);
	cout<<ans;
	return 0;
}
```

---

## 作者：4041nofoundGeoge (赞：1)

## 思路

不难看出最优解可以为一下答案：

对于每个 `0` 在 $S$ 中，考虑其左侧的 `1` 数量（设为 $l$ ）和右侧的 `1` 数量（设为 $r$ ）。如果 $l<r$ ，则将 `0` 移至 `1` 块左侧更好。如果 $l>r$ ，则将 `0` 移至 `1` 块右侧更好。因此，答案是所有 $\min\{l,r\}$ 的总和。

证明：

设 $C_0$ 为 $S$ 中的 `0` 的数量， $C_1$ 为 `1` $(=N-C_0)$ 的数量。

对于每个 $i\ (1\leq i\leq C_0)$ ，令 $d_i$ 为从左数第 $i$ 个 `0` 右侧的 `1` 的数量。为了方便，定义 $d_0=0$ 和 $d_{C_0+1}=C_1$ 。然后 $d_0 \leq d_1\leq d_2\leq \dots \leq d_{C_0}\leq d_{C_0+1}$ 。

让我们根据值 $d_i$ 重新解释这个问题。首先，交换相同的字符是没有意义的，因此原始问题陈述中的操作等价于对 $d_i$ 执行以下操作之一：

-   选择一个 $i\ (1\leq i\leq C_0)$ ，并减少 $d_i$ 的 $1$ 。
-   选择一个 $i\ (1\leq i\leq C_0)$ ，并增加 $d_i<d_{i+1}$ 的 $d_i$ 。

终止条件如下：

- 存在一个 $p\ (0\leq p\leq C_0)$ ，使得 $0=d_1=\dots=d_p$ 和 $d_{p+1}=\dots=d_{C_0}=C_1$ 。

一个操作将 $d_i$ 增加或减少一，因此显然至少需要 $K$ 次操作，其中

$$
K=\displaystyle\sum_{i=1}^{C_0} \min\{d_i, C_1-d_i\}.
$$

另一方面，由于 $d_i$ 是单调递增的，因此总是可以通过 $K$ 操作满足终止条件，所以答案是 $K$ 。（可以令 $p$ 为具有 $i$ 的最大 $d_i < C_1-d_i$ ，或者如果不存在，则为 $0$ 。）

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;
    int c1 = 0;
    for (char c: s) {
        if (c == '1') ++c1;
    }
    int now = 0;
    long long ans = 0;
    for (char c: s) {
        if (c == '0') {
            ans += min(now, c1 - now);
        } else {
            ++now;
        }
    }
    cout << ans << endl;
}

```

---

## 作者：zaolong (赞：1)

## 思路

首先我们可以通过打暴力代码发现步数最少的移动方案一定是往中间的 $1$ 的位置去移动，因为你把移动位置 $+1$ 还是 $-1$ 都是要大于往中间的 $1$ 的位置去移动的步数。\
所以我们就可以首先记录对于每一个 $1$，第 $i$ 个 $1$ 的位置 $a_i$，再找出中间数，再通过循环枚举出总共的步数即可。

## 代码

时间复杂度：$\mathcal{O}(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,ans,a[5000005];
main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		char x;
		cin>>x;
		if(x=='1'){
			a[++k]=i;
		}
	}
	int s=(k+1)/2;
	for(int i=1;i<s;i++){
		ans+=(a[s]-a[i]-s+i);//注意不是堆在一起，是要放在前一个的后面。 
	}
	for(int i=s+1;i<=k;i++){
		ans+=(a[i]-a[s]+s-i);//同上 
	}
	cout<<ans;
}
```

---

## 作者：dingxiongyue (赞：1)

# 题解：AT_abc393_d [ABC393D] Swap to Gather  

## Description：
给定一个长度为 $N$ 的 $01$ 字符串 $S$，可将该字符串相邻的两个字符交换。求使所有 $1$ 连续的最小操作次数。  

## Analysis：
遍历字符串，保存最中间的 $1$ 的位置，即所有 $1$ 的位置的中位数，将所有的 $1$ 都移动至该位置，即可使操作次数最小。  

时间复杂度 $O(N)$。

## Code：
[AC记录](https://www.luogu.com.cn/record/204019751)  
```cpp
#include <iostream>
#include <vector>
#define int long long
const int N = 5e5 + 10;
int n;
int ans;
int cnt;
int k;
int tmp;
int t[N];
char a[N];
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

signed main() {
	n = read();
	scanf("%s", a + 1);
	for (int i = 1; i <= n; i++) 
		if (a[i] == '1') t[++cnt] = i;
	k = t[cnt / 2 + 1];
	for (int i = k; i > 0; i--) 
		if (a[i] == '1') ans += k - i - tmp, tmp++;
	tmp = 0;
	for (int i = k; i <= n; i++) 
		if (a[i] == '1') ans += i - k - tmp, tmp++;
	write(ans);
	printf("\n");
	return 0;
}
```

---

## 作者：lfxxx_ (赞：1)

我们对于每个 $i$，记录一个 $cost_i$ 表示在 $i$ 上的 $1$ 和 $i$ 后面的 $1$ 都连在一起的总耗费。

如何求出 $cost_i$？我们从后往前扫，到第 $i$ 个位置时记录一个 $cnt1$ 表示 $i$ 后面 $1$ 的个数，$cnt$ 表示 $cost_i$ 到 $i$ 的时候的值。

如果 $S_i=1$，那么我们令 $cost_i \gets cnt$,$cnt1 \gets cnt1+1$。

否则，我们令 $cnt \gets cnt+cnt1$。

从前到后同理，取最小值即可。

时间复杂度 $O(N)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int cost[N];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    string s;
    cin>>n>>s;
    s="#"+s;
    int cnt=0,cnt1=0,ans=0x3f3f3f3f3f3f3f3f;
    for(int i=n;i>=1;--i)
    {
        if(s[i]=='1')
        {
            ++cnt1;
            cost[i]=cnt;
        }
        else
            cnt+=cnt1;
            
    }
    cnt=cnt1=0;
    for(int st=0,i=1;i<=n;++i)
    {
        if(s[i]=='1')
        {
            ++cnt1;
            ans=min(ans,cnt+cost[i]);
        }
        else
            cnt+=cnt1;
    }
    cout<<ans;
}
```

---

## 作者：getchar_unlocked (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc393_d)

### 思路

首先将所有 `1` 的下标统计在序列 $A$ 中，记为 $A_0,A_1,\dots,A_{M-1}$。为了最小化操作次数，应该将所有的数都移到最中间的 `1` 的位置上，即 $A_{\lfloor\frac{M}{2}\rfloor}$。

然后统计所有 `1` 移到中间所需交换次数，得到序列 $B$，则 $B_i\gets A_{\lfloor\frac{M}{2}\rfloor}-\lfloor\frac{M}{2}\rfloor+i$。

最后统计次数总和，即 $\sum\lvert A_i-B_i\rvert$。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=5e5+10;
char s[N];
int a[N],b[N];
signed main(){
	int n=read();
	scanf("%s",s);
	int m=0;
	for(int i=0;i<n;++i)
		if(s[i]=='1')
			a[m++]=i;
	for(int i=0;i<m;++i)
		b[i]=a[m/2]-m/2+i;
	int ans=0;
	for(int i=0;i<m;++i)
		ans+=(int)abs(a[i]-b[i]);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Cosine_Func (赞：1)

简单贪心。

看到题目容易想到一种做法：先确定字符聚集的中心位置再统计。手玩以下可以发现，当中心位置 $m$ 满足 $\sum_{i=1}^ms_i$ 与 $\sum_{i=m+1}^Ns_i$ 的差的绝对值小于等于 $1$ 时最优。因此做一遍前缀和再求出中心位置，剩余部分直接求距离即可。核心代码如下：
```cpp
for(int i=1;i<=n;i++)
	s[i]=s[i-1]+signed(c[i]-'0');
for(int i=1;i<=n;i++)
	if(s[i]==s[n]/2)
		m=i;
j=m;
for(int i=m;i>=1;i--)
	if(c[i]=='1'){
		ans+=abs(j-i),j--;
j=m+1;
for(int i=m+1;i<=n;i++)
	if(c[i]=='1')
		ans+=abs(i-j),j++;
cout<<ans;
```
[参考代码](https://atcoder.jp/contests/abc393/submissions/62781822)

---

## 作者：Tiger_Rory (赞：1)

主要思路：让位于正中间的 $1$ 不动，两边的 $1$ 逐次向中间靠拢即可达到最优。这是本题的贪心策略。

证明：这可以转化为在数轴上选取一个定点，使得多个数轴上的其他点到这个点的距离之和最短的数学问题，而显然选取位于正中间的点作为定点最优。

参考代码如下。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
ll ans;  
string s; 
vector<int>vec;
int main() {
	cin.tie(0)->sync_with_stdio(0);cout.tie(0);
	cin>>n;
	cin>>s; 
	int len=s.size();
	for(int i=0;i<len;i++){
		if(s[i]=='1')vec.push_back(i); //记录1的位置
	}
	int pos=(int)vec.size()/2;//正中间的1在vec中的位置
	int l=pos-1; 
	while(l>=0){
		ans+=1ll*(vec[pos]-vec[l]-1-(pos-l-1)); 
		l--;
	}
	int r=pos+1; 
	while(r<vec.size()){
		ans+=1ll*(vec[r]-vec[pos]-1-(r-pos-1)); 
		r++;
	}	//依次靠拢
	cout<<ans<<'\n'; 
	return 0;
}
```

---

## 作者：linjinkun (赞：0)

> 大概评级：黄。

签到题。

显然，我们需要找到所有的 $1$ 的位置，然后看其它的 $1$ 靠拢过来需要几次操作，然后对于每个位置的答案取个最小值就好了。

直接暴力肯定是不行的，考虑优化计算其它的 $1$ 靠拢过来需要几次操作的过程，首先为了方便，我们将当前位置设为 $i$，将 $i$ 左边的 $1$ 的位置组成的集合称为 $a$，将 $i$ 右边的 $1$ 的位置组成的集合称为 $b$，集合 $a$ 的大小称为 $as$，集合 $b$ 的大小称为 $bs$，那么集合 $a$ 的贡献就是：

$$\sum_{j = 1}^{as} i-a_j-(as-j)$$
$$ = \sum_{j = 1}^{as} a_j-as \times i-\sum_{j = 1}^{as-1} j$$

至于一开始的式子为什么还要减去 $as-j$ 是因为每次 $i$ 左边的一个 $1$ 靠拢过来后，下一个 $1$ 靠拢过来需要的次数就会少 $1$。

继续正题，我们发现这个式子化简后是可以使用两个前缀和维护的。

额……其实集合 $b$ 贡献也是差不多的：

$$\sum_{j = 1}^{bs} b_j-i-(bs-j)$$
$$ = bs \times i-\sum_{j = 1}^{bs} b_j-\sum_{j = 1}^{bs-1} j$$

可以用两个后缀和维护。

**十年 OI 一场空，不开 long long 见祖宗。**

总时间复杂度：$O(N+N) = O(N)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int N = 5e5+5;
char a[N];
int sum1[N];
int sum2[N];
signed main()
{
	int n;
	scanf("%lld",&n);
	scanf("%s",a+1);
	for(int i = n;i;i--)
	{
		sum1[i] = sum1[i+1]+(a[i] == '1');
		sum2[i] = sum2[i+1]+(a[i] == '1')*i;
	}
	int minn = 1e18;
	int pre1 = 0,pre2 = 0;
	for(int i = 1;i<=n;i++)
	{
		pre1+=(a[i] == '1');
		pre2+=(a[i] == '1')*i;
		if(a[i] == '1')
		{
			minn = min(minn,(pre1-1)*i-(pre2-i)-(pre1-1)-(pre1-1)*(pre1-2)/2+(sum2[i]-i)-(sum1[i]-1)*i-(sum1[i]-1)-(sum1[i]-1)*(sum1[i]-2)/2);
		}
	}
	printf("%lld",minn);
	return 0;
}
```

---

## 作者：__assassin_ (赞：0)

# 题目大意：

给你一个只由 $0$ 和 $1$ 组成的字符串，每次可以交换相邻两个字符，问你至少需要交换多少次才可以是所有 $1$ 都在一块。
a
# 思路：

这道题其实就是一道模拟题。首先，我们将字符串 $s$ 中的所有 $1$ 的位置储存下来，再求出最中间的 $1$ 的位置（如果有偶数个 $1$，那就取第总数除以 $2$ 给 $1$ 的位置），然后分别向左右两边模拟，最后输出答案 $ans$ 即可。

先来看向左的做法，我们以 $l$ 为当前查询的点，$ll$ 为当前答案块的左端点，那当 $s_{l}$ 为 $1$ 时，答案 $ans$ 就加上 $\lvert l-ll \rvert -1$ 的值，并且 $ll \gets ll-1$。而且每一次循环都要使 $l \gets l-1$，直到 $l<0$ 时。

再来看向右的做法，我们以 $r$ 为当前查询的点，$rr$ 为当前答案块的右端点，那当 $s_{r}$ 为 $1$ 时，答案 $ans$ 就加上 $\lvert r-rr \rvert -1$ 的值，并且 $rr \gets rr-1$。而且每一次循环都要使 $r \gets r-1$，直到 $r \ge n$ 时。

# AC 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans,w[500010],wi,x,l,r,ll,rr;//n为字符串的长度，w[i]为第i个1的位置，wi代表1的个数，x为最中间的1的位置，l、r、ll、rr的意思为上文所属 
string s;//原字符串 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>s;
	for(int i=0;i<s.size();i++) if(s[i]=='1') w[++wi]=i;//存储每个1的位置 
	x=w[(wi+1)/2];//求最中间那个1的位置 
	l=x-1,r=x+1,ll=rr=x;//初始化l、r、ll、rr 
	while(l>=0){
		if(s[l]=='1') ans+=abs(l-ll)-1,ll--;//当s[l]为1时，ans加上|l-ll|-1，然后ll向前一位 
		l--;//l向前一位 
	}
	while(r<n){
		if(s[r]=='1') ans+=abs(r-rr)-1,rr++;//当s[r]为1时，ans加上|r-rr|-1，然后rr向前一位 
		r++;//r向前一位
	} 
	cout<<ans;//输出最终答案 
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### 解决思路  
$1.$ 记录 $1$ 的位置：  
- 记录字符串中所有 $1$ 的索引。设这些索引为 $p_1,p_2,
…,p_k$，其中 $k$ 是 1 的数量。
 
$2.$ 确定目标区间：
- $1$ 的目标区间应该是一个大小为 $k$ 的连续块。
- 最优的目标区间是使所有 $1$ 移动到该区间所需交换次数最少的区间

$3.$ 计算交换次数：
- 对于每个位于位置 $p_i$ 的 $1$，其在目标区间中的目标位置为 $l+i−1$，其中 $l$ 是目标区间的起始位置。
- 计算每个 $1$ 移动到其目标位置所需的交换次数，并累加得到总交换次数。
#### 代码实现  

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int N;
    string S;
    cin >> N >> S;
    vector<int> ones;
    for (int i = 0; i < N; ++i) 
        if (S[i] == '1') ones.push_back(i + 1); 
    int m = ones.size();
    vector<int> b;
    for (int i = 0; i < m; ++i) b.push_back(ones[i] - i);
    sort(b.begin(), b.end());
    int mid = b[m / 2];
    long long ans = 0;
    for (int num : b) ans += abs(num - mid);
    cout << ans << endl;
    return 0;
}
```

---

## 作者：chaqjs (赞：0)

### 题目翻译

给定长度为 $n$ 的字符串 $S$，由 `0` 和 `1` 组成。

每次可以交换相邻的两个字符，问最少经过多少次操作才能使所有的 `1` 连续。

### 思路

由题意知，每次操作只能交换相邻字符，因此移动一个字符的成本即为其位置的变化量。

为了使所有的 `1` 连续，我们考虑将所有 `1` 集中到**中间位置**，来最小化操作次数。

这也就意味着我们只要找到所有 `1` 的位置的中位数，并以此为目标位置，计算所有 `1` 到该目标位置的距离之和即为答案。

### 代码

    #include <bits/stdc++.h>
    using namespace std;
    
    int n;
    string S;
    vector<int> vec;
    
    int main() {
        cin.tie(0)->sync_with_stdio(0);
    
        cin >> n;
        cin >> S;
    
        for (int i = 0; i < n; ++i)// 将所有1的位置找到压入vector
            if (S[i] == '1')
                vec.push_back(i);
    
        sort(vec.begin(), vec.end());// 这里要注意，中位数一定要先排序！
    
        int k = vec.size();
        int mid = vec[k / 2];
        long long ans = 0;
        for (int i = 0; i < k; ++i) {
            int x = mid - (k / 2) + i;// 找到目标位置，即中位数左右第几个
            ans += abs(vec[i] - x);// 累加答案
        }
    
        cout << ans;
    
        return 0;
    }

---

## 作者：Alexoip (赞：0)

题意：给你一个字符串 $S$，每次可以交换相邻的两个字符，你需要最小化操作次数，使得所有的 $1$ 是连续的。

做法：贪心地考虑，我们肯定固定一个 $1$ 不动，其余都向它靠近，与重心类似，我们容易想到规定中间的 $1$ 不动，答案即为其它的 $1$ 和它的距离的和。

代码如下：
```cpp
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;
using u128 = unsigned __int128;

constexpr int N = 5e5 + 10;

int p[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	string s;
	cin >> n >> s;
	int k = 0;
	for (int i = 0; i < n; i++) if (s[i] == '1') {
		p[++k] = i;
	}
	int m = (k + 1) / 2, c = 0;
	i64 ans = 0;
	for (int i = p[m] - 1; i >= 0; i--) {
		if (s[i] == '1') {
			c++;
			ans += p[m] - c - i;
		}
	}
	c = 0;
	for (int i = p[m] + 1; i < n; i++) {
		if (s[i] == '1') {
			c++;
			ans += i - p[m] - c;
		}
	}
	cout << ans << "\n";
    return 0;
}

---

## 作者：lilong (赞：0)

有一个显然的结论，即最中间的 $1$ 是固定不动的。考虑反证，假设左右各有 $k$ 个 $1$，且所有 $1$ 不是往正中间的 $1$ 移动，那么一侧 $k$ 个移动距离减小，另一侧 $k$ 个移动距离增加，显然不会更优，因此结论得证。$n$ 为奇数时，最中间只有一个 $1$，计算一次即可；$n$ 为偶数时，最中间有两个 $1$，需要计算两次。

时间复杂度 $O(n)$，代码就不放了。

---

## 作者：FXLIR (赞：0)

### 思路

显然，每一次交换必然是交换某一个 $1$ 和某一个 $0$。

进一步思考可以发现，若想最小化移动次数，移动过程中，必然是某一个 $1$ 不动，其它的 $1$ 向这个 $1$ 的方向移动。

我们发现，这个问题似乎有些眼熟……？对了，这和[货仓选址](https://www.luogu.com.cn/problem/P10452)很像！只不过这个问题是其它点向一个点，货仓选址是一个点向其它点。也就是说，那个不动的 $1$ 必然是中间的一个。

于是考虑先预处理所有边的数量，再跑一遍货仓选址，于是这道题就结束了……吗？很遗憾，用这个思路写出的代码连样例都过不了。原因很简单——货仓选址的答案是每个点到中间点的距离之和，但每一个 $1$ 所需的移动次数并不是它到中间点的距离之和。

观察可以发现，中间点左边，离该点最近的一个点所需的移动次数是是它到中间点的距离减 $1$，第二近的点所需的次数是到中间点的距离减 $2$，以此类推。中间点右边的点同理。所以，可以用距离之和减去多出的次数。

于是这道题就真的做完了。
### 代码
```
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int N=5e5+5,INF=1e9;
string s;
int n,ans,a[N],tot;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>s;
	s=' '+s;
	for(int i=1;i<=n;i++){
		if(s[i]=='1'){
			a[++tot]=i;
		}
	}
	for(int i=1;i<=tot;i++){
		ans+=abs(a[i]-a[tot/2+1]);
	}
	cout<<ans-(tot/2)*(tot/2+1)/2-(tot-tot/2-1)*(tot-tot/2)/2;
	return 0;
}
```

---

## 作者：Frank_G (赞：0)

[题目传送门](https://atcoder.jp/contests/abc393/tasks/abc393_d)

# 简化题意

给定一个字符串，定义交换相邻两个字符的位置为一次操作，求出让这个字符串中的字符 $1$ 全部连续所需要的最小操作次数。

# 做法

定义字符串中字符 $1$ 的个数为 $cnt$，且字符串中第 $i$ 个 $1$ 的位置是 $x_{i-1}$，

那么我们有下面这个式子：若最终连续段的左端点为 $l$，则最终的代价数为 $\sum_{i=0}^{cnt-1}{\left|x_i-(l+i)\right|}$。

若最终操作后字符 $1$ 的连续串的左右端点为 $l,r$，那么让 $\left\lfloor\frac{l+r}{2}\right\rfloor=x_{\left\lfloor\frac{cnt}{2}\right\rfloor}$ 即可。

即 $\left\lfloor\frac{l+(l+cnt-1)}{2}\right\rfloor=x_{\left\lfloor\frac{cnt}{2}\right\rfloor}$。

经典中位数贪心，证明比较简单，与[这题](https://www.luogu.com.cn/problem/P10452)类似，此处不加赘述。

# 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
string s; 
int n;
long long ans;
vector<int> x;
int main(){
	cin >> n; 
	cin >> s;
	for(int i=0;i<n;i++){
		if(s[i]=='1') x.push_back(i);
	}
	int l=x.size();
	for(int i=l/2;i>=0;i--){
		ans+=abs(x[i]-(x[l/2]-(l/2-i)));
	}
	for(int i=l/2+1;i<l;i++){
		ans+=abs(x[i]-(x[l/2]+(i-l/2)));
	} 
	cout << ans;
	return 0;
}
```

[场切记录](https://atcoder.jp/contests/abc393/submissions/62785603)。

---

## 作者：MutU (赞：0)

### [原题传送门](https://www.luogu.com.cn/problem/AT_abc393_d)

不会结论，但是会枚举。

显然最后要将某个 $1$ 左右两边的 $1$ 移到这个点旁边。

那么枚举这个中点，逐个计算交换次数，方法多样。

我这里令 $p_i$ 表示第 $i$ 个 $1$ 的位置，$f_i$ 表示将第 $i$ 个 $1$ 左边的 $1$ 移到第 $i$ 个旁边的交换次数，有 $f_i=f_{i-1}+(i-1)*(p_i-p_{i-1}-1)$。

反向再做一遍，两边结果相加即为一个中点的交换次数。

### Code


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 500100;
int n,ans=1e18,pre[N],lst[N];
int cnt,p[N];
string st;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>st;
	for(int i=n;i>=1;i--) st[i]=st[i-1];
	for(int i=1;i<=n;i++) if(st[i]=='1') p[++cnt]=i;
	for(int i=1;i<=cnt;i++) pre[i]=pre[i-1]+(i-1)*(p[i]-p[i-1]-1);
	for(int i=cnt;i>=1;i--) lst[i]=lst[i+1]+(cnt-i)*(p[i+1]-p[i]-1);
	for(int i=1;i<=cnt;i++) ans=min(ans,pre[i]+lst[i]);
	cout<<ans;
	return 0;
}
```

[提交记录](https://atcoder.jp/contests/abc393/submissions/62779992)

---

