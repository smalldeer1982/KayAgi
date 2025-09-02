# [LMXOI Round 1] Placer

## 题目背景

LMX 最近迷上了括号序列，她尤其钟爱合法括号序列。

LMX 为了检验 HQZ 的真诚，于是她出一道题准备考验下 HQZ。


## 题目描述

LMX 给出了一个长度为 $n$ 括号序列 $S$，以及一个长度为 $n$ 的序列 $a_i$。

定义 $w(l,r)=
\begin{cases}
a_r-a_l, & S_{l..r} \text{为合法括号序列}\\
\ 0 & \text{otherwise}
\end{cases}$

你可以将序列分成若干非空子段，定义整个序列的美丽度为每段的 $w(l , r)$ 之和。

求美丽度最大为多少。

## 说明/提示

**样例解释 #1**

原串可以划分成三个区间：$[1,2],[3,3],[4,5]$。贡献为 $(a_2-a_1)+0+(a_5-a_4)=(3-1)+0+(5-3)=4$

| 子任务编号 | $n$ | 特殊性质 | 分值 |
| :--------: | :--------: | :-------------: | :--: |
| Subtask #1 | $\le 5000$ | 无 | $30$ |
| Subtask #2 | $\le 10 ^ 5$ | 无 | $20$ |
| Subtask #3 | $\le 3 \times 10 ^ 6$ | 括号序列为 $()()\dots()$ | $15$ |
| Subtask #4 | $\le 3 \times 10 ^ 6$ | 无 | $35$ |

对于 $100\%$ 的数据，$1\le a_i \le 10^9$。

## 样例 #1

### 输入

```
5
()(()
1 3 2 3 5```

### 输出

```
4```

## 样例 #2

### 输入

```
10
()((())())
2 4 1 7 3 2 8 4 9 5```

### 输出

```
8```

# 题解

## 作者：_XHY20180718_ (赞：16)

本来觉得这题挺不错的，但数据被暴力草过去了，所以给 $7$ 分。

## 简要题意：
给你一个括号序列和 $\{a\}$ 数组，将其分成连续的若干组。

每个组的权值：若括号序列合法，则为 $a_r-a_l$，否则为 $0$。

求组的权值之和的最大值。

## 主要思路：

先写暴力，设 $f_i$ 表示在当前位置 $i$ 后分组 $1\sim i$ 之间所有组的最大权值。

易得转移方程：
$$
f_i=\max_{j=1}^{i-1}\{f_j+w_{i,j}\}
$$
我们将合法与不合法情况分开来讨论：

当我们从不合法情况来转移时：
$$
f_i=\max_{[j+1,i]\text{为非法区间}}\{f_j\}
$$
由于 $f_i$ 本身单调递增，所以说：
$$
f_i=f_{i-1}
$$

而当我们从合法的情况来转移时：
$$
f_i=(\max_{[j+1,i]\text{为合法区间}}\{f_j-a_{j+1}\})+a_i
$$

于是我们将 $f_j-a_{j+1}$ 打包，因为其对于每个 $j$ 都是不变的。

对于每一个 $i$，用 $c_i$ 来维护他：
$$
c_i=\max_{j|[j+1,i]\text{为合法区间}}\{f_j-a_{j+1}\}
$$
将上面两种情况比较即可，也就是说：
$$
f_i=\max \{c_i+a_i,f_{i-1}\}
$$
接下来要讨论的问题是如何快速算出 $c_i$：

设 $A$，$B$ 为合法括号序列，则所有合法括号序列满足以下情况：
1. $()$，最基本的括号序列。
2. $(A)$，一个括号将一个合法括号序列括起来依然是合法括号序列。
3. $AB$，两个合法括号序列拼起来依然是合法括号序列。

对于作为一个右括号的 $S_i$ 来说，我们完全可以通过栈找出与他合起来的最近左括号，其位置记为 $lst_i$。

所以，对于一个 $i$，我们完全可以找出 $lst_i$，除了第三种情况都可以解决，然后就能套上面的式子，给 $c_i$ 赋初值：$f_{lst_{i-1}}-a_{lst_i}$。

而对于第三种情况，由于两个括号序列可以合成一个新序列，那我们的 $c_i$ 就能从 $c_{lst_i-1}$ 转移过来，因为集合 $j|[j+1,i]\text{为合法区间}$ 将严格包含集合 $j|[j+1,lst_i-1]\text{为合法区间}$，唯一多的元素便是 $lst_i$。

所以：
$$
c_i=\max\{c_{lst_i-1},f_{lst_{i-1}}-a_{lst_i}\}
$$
结合：
$$
f_i=\max\{c_i+a_i,f_{i-1}\}
$$
于是这题我们就做完了。
## 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e6+5,inf=1e18;
int n,a[N],lst[N],r;
int f[N],st[N],c[N];
bool b[N];
string S;
signed main(){
    // freopen("test.in","r",stdin);
    // freopen("std.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>S;
    for(int i=1; i<=n; ++i)
        cin>>a[i],b[i]=(S[i-1]=='(');
    for(int i=1; i<=n; ++i)
        if(!b[i]&&r)lst[i]=st[r--];
        else if(b[i])st[++r]=i;
    for(int i=0; i<=n; ++i)
        f[i]=c[i]=-inf;f[0]=0;
    for(int i=1; i<=n; ++i){
        f[i]=f[i-1];
        if(lst[i]){
            c[i]=max(c[lst[i]-1],f[lst[i]-1]-a[lst[i]]);
            f[i]=max(c[i]+a[i],f[i]);
        }
    }cout<<f[n];
    return 0;
}
```

---

## 作者：L_zaa_L (赞：11)

## 思路
我们知道括号匹配有以下性质：

1. 若 $A,B$ 是合法匹配，则 $AB$ 也是合法匹配。

2. 若 $A$ 为合法匹配，则 $(A)$ 也是合法匹配。

由第二个可以逆推，若 $A,B$ 是合法匹配，且 $A=BC$，则 $C$ 也是合法匹配。

然后再看题面，设 $dp_i$ 为当前最大值，则对于每次更新 $dp$ 的时候，只需要找到第一个跟它合法的即可。

如何查找第一个跟它合法的位置？

我们可以记录一个 $lst$ 表示上一个和它匹配的位置，则 $lst$ 的计算可以暴力跳，通过左右相同的上一个合法匹配的前一个的保存值转移的，如果上一个不匹配，就需要继续向前匹配，如此重复，总复杂度是 $O(n)$。

至于前面和这个位置可以匹配的，因为现在的合法匹配是连起来的，我们可以直接记录一个 $c$，表示这个连起来中价值最大的。但是每次 $a$ 可能会影响最优的解，所以我们要考虑更新。

设当前位置为 $i$，合法匹配的位置为 $j$，则 $dp_i=c_{i}-a_j+a_i$，不妨直接 $c_{j-1}$ 给加上 $a_j$ 就可以直接得到可以转移的最优的解了。然后 $c_i$ 就可以更新为 $\max(dp_{p_i-1}-a_{p_i},c_{p_i-1})$ 即可。

时间复杂度：$O(n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while('0'<=c&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int n;
char s[4000005];
int a[4000005],p[4000005],x;
ll dp[4000005];
ll c[4000005];
inline int max(int x,int y){
	return (x<y)?y:x;
}
inline int min(int x,int y){
	return (x<y)?x:y;
}
signed main(){
	n=read();
	scanf("%s",s+1);
	for(register int i=1;i<=n;i++) a[i]=read();
    for(register int i=1;i<=n;i++)
        if(s[i]==')'&&s[i-1]=='(') p[i]=i-1;
    for(register int i=1;i<=n;i++){
    	if(s[i]=='(') continue;
    	if(p[i]) continue;
        x=i-1;
        while(p[x]){
            x=p[x]-1;
            if(s[x]=='('){
                p[i]=x;
                break;
            }
        }
	}
	ll maxx=0;
	memset(c,-0x3f,sizeof(c));
	for(register int i=1;i<=n;i++){
		dp[i]=maxx;
		if(p[i]){
			c[i]=max(dp[p[i]-1]-a[p[i]],c[p[i]-1]);//更新
			dp[i]=max(maxx,c[i]+a[i]);
			maxx=max(maxx,dp[i]);//因为可以取不合法的，每次答案可以取到前面的最值（其他的值没用）。
		}
	}
	printf("%lld",dp[n]);
	return 0;
}

```

---

## 作者：K_J_M (赞：3)

刚刚 A 了这道题，作为蒟蒻的我来写一篇题解加深一下印象。首先，题目意思是给你一个字符串和一个序列 $a$，问最大的美丽值。美丽值是由一段一段的价值累计得到的，而这个价值定义为:
$$w(l,r)=
\begin{cases}
a_r-a_l, & S_{l\dots r}  \text{为合法括号序列}\\
\ 0 & \text{otherwise}\\
\end{cases}$$
定义:
$$dp_i=\max_{1≤j≤k,1≤pos_j<i}\{w(1,pos_1)+w(pos_1+1,pos_2)+\dots +w(pos_k+1,i)\}$$
那么 $dp_i$ 应该从前面的地方 $j$ 转移过来（并且是最大的美丽值的地方），
$$dp_i=\max\{dp_j+w(j+1,i)\}$$
那么这又可以分为两种情况
$$dp_i=
\begin{cases}
\max\{dp_j+a_i-a_{j+1}\} &S_{j+1\dots i} \text{为合法括号序列}\\
\max\{dp_j\} & \text{otherwise}
\end{cases}$$
同时又注意到 $dp_i$ 的值应该是单调不减的，所以我们的$\max\{dp_j\}=dp_{i-1}$,又可以改为 $dp_i=dp_{i-1}$。综上，我们的方程为
$$dp_i=
\begin{cases}
\max\{dp_j+a_i-a_{j+1}\} &S_{j+1\dots i} \text{为合法括号序列}\\
dp_{i-1}  & \text{otherwise}
\end{cases}$$
但是这样子做的话，时间复杂度为 $O(n^2)$，妥妥的超时，现在考虑优化。注意到方程中 $dp_j+a_j-a_{j+1}$，$a_i$ 对于计算 $dp_i$ 而言是一个常量，可以提取出来，于是又变成了
$$dp_i=\max\{dp_j-a_{j+1}\}+a_i$$
现在我们令
$$c_i=\max\{dp_j-a_{j+1}\}$$
那么我们的方程又可以转化为
$$dp_i=
\begin{cases}
c_i+a_i &S_{j+\dots i} \text{为合法括号序列}\\
dp_{i-1}  & \text{otherwise}\\
\end{cases}$$
这个的时间复杂度为 $O(n)$，绰绰有余。那么现在的问题又转移到了**求解**$c_i$。考虑到
$$c_i=\max\{dp_i-a_i\}$$
我们记 $pre_i$ 表示
$$\max_{j<i,S_{j\dots i}\text{为合法括号序列}}^{}\{j\}$$
那么
$$c_i=
\begin{cases}
\max(c_{pre_i-1},dp_{pre_i-1}-a_{pre_i})  &pre_i >0\\
-∞ &pre_i=0\\
\end{cases}
$$
这个处理也是 $O(n)$ 的，也就是我们可以 $O(n)$ 完成转移了。至于处理 $pre_i$ 的方法考虑使用**栈**，具体见代码。\
[Ac Code](https://www.luogu.com.cn/paste/cemkcgf0)

---

## 作者：BrotherCall (赞：3)

挺有意思的题目，难度应该是绿左右。

看到这题第一反应是设 $f_i$ 代表前 $i$ 个括号的最大美丽度。

一时间应该会想到从该右端点匹配的左端点转移过来，设这个左端点为 $l$，即 $f_i = \max (f_{i-1} , f_{l-1} + a_i - a_l)$。

想了一会就会发现这漏了情况，形如 `()()()` 这样的，按上面的转移就是 $f_2$ 从 $f_1$ 转移过来，$f_4$ 从 $f_3$ 转移过来，$f_6$ 从 $f_5$ 转移过来。

但是 $f_6$ 也可以从 $f_1$ 和 $f_3$ 转移过来。

因此发现一个右端点可以从它前面与它**同层**的任意一个左端点转移过来。

**同层**的解释：相同层数且在同一外层中。

相同层数很好理解，举个例子说明什么叫**在同一外层中**。

`(())(())`，八个位置的层数分别为 1 2 2 1 1 2 2 1。但两个第二层的括号并不在同一外层中。

`(()())`，六个位置的层数分别为 1 2 2 2 2 1。此时两个第二层的括号在同一外层中。

到这里，我们就可以写出 $O(n^2)$ 的 dp 了：对于每个右端点 $i$，枚举所有同层的左端点 $j$。则 $f_i = \max (f_{i-1} , f_{j-1} + a_i - a_j)$。时间复杂度 $O(n^2)$。

观察这个转移方程我们可以把 $f_{j-1} - a_j$ 放到其对应层数的优先队列里，每次转移取优先队列里最大的数。可将复杂度降为 $O(n\log n)$。

最后一个重要的点是直接这么做会让优先队列里存在**不在同一外层中**的数，解决方法是退第 $i$ 层后把 $i+1$ 层的优先队列清空。

[Code](https://www.luogu.com.cn/paste/y2c8ktyu)

---

## 作者：LCat90 (赞：3)

假设这个题我们会 $n^2$ DP。接下来肯定是要优化这个转移的过程。

先讲一讲特殊性质，这里我们发现所有右括号（待转移点）和左括号（可转移点）的位置非常确定，于是我们用优先队列维护这些可转移点的最大值即可。

设 $dp_i$ 表示将 $[1,i]$ 进行划分后的最大价值。首先，单独个这个位置划一个，则 $dp_i=dp_{i-1}$；否则，$i$ 需要由前面的 $j$ 转移过来，且 $[j,i]$ 组成的括号序列合法。

发现这个 $j$ 的数量可能很多，怎么办？比赛的时候就傻傻罚坐了……

我们不妨**找到最近的一个合法的 $j=p_i$，然后加入一个 dp 数组 $b$ 来维护前面的所有 $j$ 对 $p_i$ 的贡献**。此时我们将状态方程改写为：$dp_i=a_i+b_i$。（因为 $a_i$ 不变）

第一种情况，$i$ 和 $p_i$ 配对。则 $b_i=dp_{p_i-1}-a_{p_i}$。

另外一种情况，$i$ 和 $p_i$ 之前的一个位置配对（这个位置到 $i$ 是合法的）。由括号序列的性质，此时只有可能是两个合法的合并而来。所以我们直接让 $b_i$ 继承 $b_{p_i-1}$ 即可。

建议评绿，730B 代码如下。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e6 + 5; 
int n, a[N], dp[N], p[N], b[N]; char c[N];
struct node { char ch; int id; };
signed main() {
	cin >> n; scanf("%s", c + 1);
	for(int i = 1;i <= n; ++i) scanf("%d", &a[i]); stack <node> st;
	for(int i = 1;i <= n; ++i) {
		if(!st.empty() and st.top().ch == '(' and c[i] == ')') {
			p[i] = st.top().id; // nxt
			st.pop();
		} else st.push((node){c[i], i});
	} 
	memset(b, 0xf3, sizeof b);
	for(int i = 1;i <= n; ++i) {
		dp[i] = max(dp[i - 1], dp[i]);
		if(p[i]) {
			b[i] = max(dp[p[i] - 1] - a[p[i]], b[p[i] - 1]); // 1. 当前转移，2. 和前面的位置转移 
			dp[i] = max(dp[i], a[i] + b[i]);
		}
	}
	cout << dp[n];
    return 0;
}
```

---

## 作者：Bing_bai (赞：2)

# $dp$：
## Subtask $1$：
对于 Subtask $1$，我们很容易想到 $O(n^2)$ 的 ```dp``` 思路。

定义 $dp_{i}$ 表示 $w(1,i)$ 的最大值。

分两种情况，

$$
dp_i = \max\begin{cases}
  dp_{i-1} & \text{将自己分为一个子段,贡献为}0 \\
  \max(dp_{j-1} + a[i] - a[j]) & \text{找到一个合法的括号序列}S_{j..i} \text{，将其拆为一个子段，使其贡献最大，贡献为}a_i-a_j
\end{cases}
$$

### 关于括号匹配：
建一个栈 $st$，从后往前遍历，如果遇到右括号就进栈，遇到左括号分两种情况:
+ 当栈为空，不合法。
+ 当栈里有元素，```pop``` 掉，如果删除栈顶元素后栈为空，则该区间为合法括号。

建议先做[P1241 括号序列](https://www.luogu.com.cn/problem/P1739)  ~~水字数，用栈是因为之后要用~~。
 
### code：
```cpp
for(int i=1;i<=n;i++){
    stack<ll> st;
    f[i] = f[i-1];              //把自己拆为一段
    bool fs = true;
    if(s[i] == ')')st.push(i);  //随便加个数就行
    for(int j=i-1;j>=1;j--){    //从后往前遍历
        if(s[j] == ')')st.push(j);
        else if(st.size() != 0){
            st.pop();
            if(st.size() == 0 && s[i] != '(' && fs){  //判断是非为合法括号序列
                f[i] = max(f[i],f[j-1] + a[i] - a[j]);
            }
        }
        else fs = false;
    }
}
```


## Subtask $3$：
$n \le 3 \times 10^6$ 考虑 $O(n)$ 做法。

不难发现 ```S = ()()...```，

即对于任意 $i \le j$，都有 $S_{2i-1 \sim 2j}$ 为合法括号序列 $(1 \le 2i-1 \le 2j \le n)$。

对于 $\max(dp_{j-1} + a[i] - a[j])$，将 $a_i$ 提出，

即 $\max(dp_{j-1} - a[j]) + a[i]$，遍历时将 $dp_{j-1} - a[j]$ 处理即可。

### code：
```
ll maxk = -1 * a[1];
for(int i=1;i<=n;i++){
    f[i] = f[i-1];
    if(i % 2 == 0){
    	f[i] = max(max(f[i],maxk + a[i]),f[i-1]);
        maxk = max(maxk,f[i] - a[i+1]);
    }
}
```

## 正解：~~(可能吧)~~
结合前文的解法，尝试将 $O(n^2)$ 尽可能优化到 $O(n$ $\log$ $n)$。

关于括号匹配，容易联想到[P9753 [CSP-S 2023] 消消乐](https://www.luogu.com.cn/problem/P9753)

稍微借鉴一下，易证得，如果 $1 \sim l$ 和 $1 \sim r$ 的栈的状态，栈里括号的序号均相同，那么 $l+1 \sim r$ 为合法括号序列。

所以用 ```map``` 存储同种栈的状态时 $dp_{j-1} - a[j]$ 的最大值。

详细细节建议先做 消消乐。

这里粗略讲讲：

比如说 ```S = (()())(```，

$i=1$ 和 $i=3,i=5$ 时的栈的状态相等，均为 $S_1$ 的左括号，

而 $i=7$ 时，栈里的左括号是 $S_7$ 的，与 $i=1$ 状态不相同。

代码解决和消消乐相似，把每个括号均赋一个 ```rand``` 即可。~~虽然随机数不靠谱就是~~。
### 主要代码：
```cpp
unordered_map<ll,ll> m;
m[0] = -1 * a[1];              //初始化
for(register int i=1;i<=n;i++){
    d = 1e12 - 373*i;          //随机数有风险
    if(s[i-1] == '('){
    	st.push(d);
    	ans += d;
    }
    else if(st.size() != 0){
        ans -= st.top();
        st.pop();
    }
    else ans += d;
    dp[i] = maxs(dp[i-1],m[ans] + a[i]);
    m[ans] = maxs(m[ans],dp[i] - a[i+1]);
}
```
记得初始化 ```map -1e18```，不然会死得很惨。

完结撒花。

---

## 作者：快斗游鹿 (赞：2)

## 思路

设 $dp_i$ 表示前 $i$ 个括号产生的最大代价，那么我们可以枚举第 $i$ 个括号第一个匹配的位置 $j$，则有转移 $dp_i=\max(dp_i,dp_{j-1}+a_i-a_j)$，一种想法是每次暴力跳 $j$，直到开头，但可能会被卡到 $O(n^2)$。

注意到合法的括号序列都是一段区间，可以设 $c_i$ 表示以第 $i$ 个括号结尾的合法括号序列中可以产生的最大代价。那么 $c_i$ 有转移 $c_i=\max(c_{j-1},dp_{j-1}-a_{j})$，那么有 $dp_i=c_{i}+a_i$。

## 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e6+5;
int n,a[N],p[N],dp[N],c[N];
stack<int>st;
string s;	
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
signed main(){
	memset(c,-0x3f,sizeof(c));
	memset(dp,-0x3f,sizeof(dp));
	n=read();
	cin>>s;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		if(s[i-1]=='('){
			st.push(i);
		}
		else{
			if(!st.empty())p[i]=st.top(),st.pop();
		}
	}
	dp[0]=0;
	for(int i=1;i<=n;i++){
		dp[i]=max(dp[i],dp[i-1]);
		int j=p[i];
		//while(1){
			if(p[i]){
				c[i]=max(c[j-1],dp[j-1]-a[j]);
				dp[i]=max(dp[i],c[i]+a[i]);
			}
			//j=p[j-1]; 
			//if(!j)break;
		//}
	} 
	/*for(int i=1;i<=n;i++)cout<<c[i]<<" ";
	cout<<endl;
	for(int i=1;i<=n;i++)cout<<dp[i]<<" ";*/
	cout<<dp[n];
}

```


---

## 作者：封禁用户 (赞：2)

# 解题思路
本题是一道关于括号序列和动态规划的题目。关键在于理解如何将序列分割为子段，以便最大化美丽度。由于序列的美丽度取决于子段内元素的差值，我们需要找到一种方法来确定哪些子段应该被合并以获得更大的美丽度。

首先，我们可以遍历整个序列，对于每个位置 $i$，我们检查从开始到当前位置的所有子段，即对于每个 $l \leq i$，计算 $w_{l,i}$。如果当前子段是合法的括号序列，那么我们将其加入到结果中，并且更新当前的最大美丽度。

然后，我们继续遍历序列，对于每一个新的位置 $i$，我们考虑是否能够将前面的子段与当前位置合并以获得更大的美丽度。为此，我们维护一个堆（优先队列），存储前面所有子段的结束位置和对应的美丽度。对于每一个新的位置 $i$，我们弹出堆顶的元素，如果新的子段 $w_{l,i}$ 比之前的最大美丽度还要大，那么我们就更新最大美丽度，并且将新的子段加入到堆中。

这样，我们就可以在遍历序列的过程中，动态地更新最大美丽度，最终得到结果。

# 复杂度分析
由于我们需要遍历整个序列，因此时间复杂度为 $O(n)$。空间复杂度主要取决于堆的大小，由于堆的大小不会超过序列的长度，因此空间复杂度也为 $O(n)$。

---

## 作者：云雷心柠檬听 (赞：1)

[博客食用更佳](https://www.cnblogs.com/lemon-cyy/p/17993846)

#### 题意简述
给定一个括号序列，求整个序列的美丽值最大。

#### 思维路径
见到序列和权值，很容易想到需要用 DP。

我们定义 $f[i][j]$ 表示第 $1$ 到 $i$ 个括号产生的美丽值最大值，其中 $j=0$ 表示第 $i$ 个括号本身不参与美丽值贡献，$j=1$ 表示第 $i$ 个括号本身参与美丽值贡献。

接下来分情况讨论。

若 $j=0$ 说明 $i$ 本身就不参与美丽值增加，贡献为 $0$，因此可以得到转移方程 $f[i][0]=\max_{0\le j \le 1}{f[i-1][j]}$。

若 $j=1$ 说明 $i$ 本身参与美丽值增加，定义产生贡献的括号序列为 $u$ 到 $i$，要求这一段括号序列为合法的。定义 $p[i]$表示与 $i$ 匹配的括号，那么 $u$ 的第一个取值为 $p[i]$，之后可以通过 $u=p[u-1]$ 遍历所有可能的转移。由此可以得到转移方程 $f[i][1]=\max_{0\le j \le 1}{f[u][j]}$。

#### 实现细节
$j=1$ 的情况种遍历 $u$ 的方式仍然是需要较长时间的，我们定义一个数组 $mx[i]$ 表示 $i$ 之前可能作为转移的值中的最大值。

假设当前 $f[i][1]$ 的转移遍历到 $u$，若 $mx[u-1]+a[i] \le f[i][1]$，则可以证明此时的 $f[i][1]$ 一定是最大值，可以停止遍历。

#### AC 代码
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=4000009;
const ll INF=1e18+9;
ll n,a[N],f[N][2],p[N],stk[N],nT,mx[N];
string s;

void input(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	cin>>s;
	for(ll i=1;i<=n;i++) cin>>a[i];
}

void solve(){
	for(ll i=0;i<(ll)s.size();i++){
		if(s[i]=='('){
			stk[++nT]=i+1;
		}
		else if(nT>0){
			p[i+1]=stk[nT];
			nT--;
		}
	}
	for(ll i=1;i<=n;i++){
		if(p[i]!=0){
			ll u=p[i];
			while(u){
				f[i][1]=max(f[i][1],max(f[u-1][1],f[u-1][0])+a[i]-a[u]);
				u=p[u-1];
				if(mx[u]+a[i]<=f[i][1]) break;
			}
		}
		mx[i]=max(mx[i-1],f[i][1]);
		f[i][0]=max(f[i-1][1],f[i-1][0]);
		mx[i]=max(mx[i],f[i][0]);
	}
	cout<<mx[n];
}

int main(){
	input();
	solve();
	return 0;
}
```

---

## 作者：Tipsy_bamboo (赞：0)

# I.题目大意
其它不用多说，注意一下区间 $[l,r]$ 的贡献是 $a_r - a_l$ 而不是 $a_{r} - a_{l - 1}$ 就行。
# II.初次尝试
很显然，这题是个区间 dp, 
令 $dp_{i,j}$ 为区间 $[i,j]$ 的答案，枚举分割点 $k$ 后，容易得到以下转移方程:   
1.当 $[k + 1, j]$ 合法时：$dp_{i,j} = \max (dp_{i,k} + a_j - a_{k + 1}, dp_{i, j}) $。  
2.当 $[k + 1, j]$ 不合法时：$dp_{i,j} = \max (dp_{i, k}, dp_{i, j})$。              
 至于怎么判断是否合法，直接用栈就可以了。
# III.优化判断
对于括号序列如何判断合法，之前我们知道，对于整个括号序列，可以使用栈来判断。    
所以我们可以使用中间状态来判断是否合法。
假设现在有两个点 $l, r$ ，假设栈的状态在点 $l, r$ 上是相同的，我们很容易知道区间 $[l + 1, r]$ 是合法的区间。（因为区间 $[l, r]$ 里的元素全部相互抵消了）。                 
下一步，我们很明显应该思考如何保存状态。一个很简单的想法就是用栈里括号的位置序列进行哈希。   
另外一种想法，是使用栈顶括号的位置。很明显，如果后面的括号没有消掉，那么一定有括号入栈，栈顶位置发生变化。如果后面的括号消掉了，栈顶的括号位置不发生变化。
# IV.优化动态规划
显然，二维的动态规划无论怎么优化都是不可能通过的，所以必须把 dp 重新定义成一维的。   
令 $dp_i$ 表示区间 $[l,r]$ 的答案，这个时候我们会发现，转移时仍然需要枚举分割点 k , 得出：     
1.当 $[k + 1, i]$ 合法时：$dp_i = \max (dp_k + a_i- a_{k + 1}, dp_i) $。                            
2.当 $[k + 1, j]$ 不合法时：$dp_i = \max (dp_k, dp_i)$。         
 因为一旦加入判断，必定得一个一个枚举，所以我们分情况讨论。
### I.若区间 $[k + 1, j]$ 合法  
我们有 $dp_i = \max (dp_i, dp_k + a[i] - a[k + 1])$。                                            
不难发现，$dp_k - a_{k + 1}$ 对于所有 $k$ 具有相同的格式，所以考虑定义数组 $w$，$w_i$ 表示栈状态为 $i$ 的所有 k 的 $dp_k - a_{k + 1}$ 的最大值。   
为什么要定义数组？？？ 
因为只有当区间合法时才能这样转移，如何合法？   
当然就是之前所说的状态相同，所以很显然：$dp_i = \max (dp_i, w[state_i] + dp[i])$
### II.若区间 $[k + 1, j]$ 不合法
肯定对于任意 $j < i $ 有 $dp_i = \max (dp_i, dp_j) $。
但是真的需要枚举吗？？  
我们不难发现整个 dp 数组一定是单调不降的，因为区间 $[i, i + 1]$ 一定是不合法的，所以每次增加的至少是0。   
所以很容易可以想到，直接和 $dp_{i - 1}$ 取最大值就行了。
# V.代码
```cpp
#include<bits/stdc++.h>
using namespace std;


const long long M = 1e7 + 5, P = 1e6 + 33;

long long a[M], hsh[M], dp[M], temp[M], w[M], s[M], top;

int main () {
    ios :: sync_with_stdio (false);
    cin.tie (0);
    cout.tie (0);
    long long n;
    string bracket;
    cin >> n >> bracket;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        if (top == 0 || bracket[s[top] - 1] == ')' || bracket[i - 1] == '(') {
            s[++top] = i;
            hsh[i] = hsh[i - 1] * P + i;
        }
        else {
            --top;
            if (top != 0) hsh[i] = hsh[s[top]];
        }
        temp[i] = hsh[i];
    }
    for (int i = 1; i <= n; ++i) dp[i] = LONG_LONG_MIN;
    temp[n + 1] = 0;
    sort (temp + 1, temp + 2 + n);
    for (int i = 1; i <= n; ++i) hsh[i] = lower_bound (temp + 1, temp + 2 + n, hsh[i]) - temp;
    for (int i = 1; i <= n; ++i) w[hsh[i]] = LONG_LONG_MIN;
    dp[1] = 0, w[hsh[1]] = -a[2], w[lower_bound (temp + 1, temp + 2 + n, 0) - temp] = -a[1];
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1];
        dp[i] = max (dp[i], w[hsh[i]] + a[i]);
        w[hsh[i]] = max (w[hsh[i]], dp[i] - a[i + 1]);
    }
    cout << dp[n] << endl;
    return 0;
}
```
不过不建议用哈希蛤，容易冲突……还是用栈顶的好。

---

## 作者：_zuoqingyuan (赞：0)

# 题目大意
[传送门。](https://www.luogu.com.cn/problem/P10115)

 给出了一个长度为 $n$ 括号序列 $S$，以及一个长度为 $n$ 的序列 $a_i$。

定义 $w(l,r)=
\begin{cases}
a_r-a_l, & S_{l..r} \text{为合法括号序列}\\
\ 0 & \text{其他情况}
\end{cases}$

你可以将序列分成若干非空子段，定义整个序列的美丽度为每段的 $w(l , r)$ 之和，求美丽度最大为多少。

# 思路分析
一个合法的括号序列满足以下条件：
1. $A=()$，则 $A$ 是合法括号序列。
2. 若 $A$ 是合法括号序列，则 $(A)$ 是合法括号序列。
3. 若 $A,B$ 是合法括号序列，则 $AB$ 是合法括号序列。

根据合法括号序列的定义，我们发下，如果 $S_{1,r},S_{1,l-1}$ 均为合法括号序列，那么 $S_{l,r}$ 也是合法括号序列。这与 [CSP-S T2](https://www.luogu.com.cn/problem/P9753) 的情况类似，我们就可以在 $O(n)$ 的时间里求出 $pre_i$，满足 $S_{pre_i,i}$ 为一个合法括号序列。

我们另 $dp_i$ 表示 $S_{1,i}$ 的最大美丽度。那么分情况，如果 $S_i$ 对答案没有贡献，则 $dp_i=dp_{i-1}$。否则 $dp_i=dp_j+w(j+1,i)$。综上。
$dp_i=
\begin{cases}
dp_i-1\\
\max dp_j+a_i-a_{j+1}&S_{i,j+1}\text{是合法括号序列}
\end{cases}$

我们重点研究第二种情况。

$$ dp_i=a_i+\max dp_j-a_{j+1}$$

我们只需不断跳 $pre$ 就可以枚举所用情况，时间复杂度 $O(n^2)$，无法通过该题 $3\times 10^6$ 的数据。

我们考虑进一步优化，另 $c_i=\max\limits_{S_{i,j} \text{合法}}dp_j-a_{j+1}$。如果 $S_{pre_i,j}$ 合法，那么 $S_{i,j}$ 一定合法，因为 “若 $A,B$ 是合法括号序列，则 $AB$ 是合法括号序列。”。

$c_i=
\begin{cases}
\max(c_{pre_i-1},dp_{pre_{i-1}}-a_{pre_i})
&pre_i\ne 0\\
-a_{i+1}& \text{其他情况}
\end{cases}$

我们只需在求 $dp_i$ 前先求出 $c_i$，直接转移就行。时间复杂度 $O(n)$。
# Code
```cpp
#include <iostream>
using namespace std;
const int N=5e6+10;
typedef long long ll;
ll n,a[N],p[N],c[N],dp[N];
char s[N];
int main(){
    scanf("%lld",&n);
    scanf("%s",s+1);
    for(int i=1;i<=n;i++)scanf("%lld",a+i);
    for(int i=1;i<n;i++)if(s[i]=='('&&s[i+1]==')')p[i+1]=i;
    for(int i=1;i<=n;i++){
        if(p[i]||s[i]=='(')continue;
        for(int j=i-1;j>0;j--){
            if(s[j]=='('){
                p[i]=j;
                break;
            }
            j=p[j];
        }
    }
    c[0]=-a[1];
    for(int i=1;i<=n;i++){
        dp[i]=dp[i-1];
        if(p[i]){
            c[i]=max(c[p[i]-1],dp[p[i]-1]-a[p[i]]);
            dp[i]=max(dp[i],a[i]+c[i]);
        }else c[i]=-a[i+1];
    }
    printf("%lld\n",dp[n]);
    return 0;
}
```
[AC 记录。](https://www.luogu.com.cn/record/145892465)

如有错误，请指出。

---

## 作者：hcywoi (赞：0)

考虑括号匹配的过程：

- 建立一个栈维护左括号的位置。
- 对于 $s_i$ 为 `(`，将 $i$ 入栈，对于 $s_i$ 为 `)`，弹出栈头元素 $j$。

我们发现，对于 $s_i$ 为 `)` 时，$s_{j\sim i}$ 一定是合法的括号序列且对于 $\forall k(j<k\le i)s_{k\sim i}$ 一定是不合法的括号序列。

进一步，根据合法括号序列的性质，以 $i$ 结尾的合法括号序列一定是由若干段合法的括号序列和 $s_{j\sim i}$ 拼接而成。

由此，我们记 $dp_{i, 0/1}$ 表示 $i$ 是否选时的最大美丽度。

考虑转移，显然地，$dp_{i, 0}=\max\{dp_{i-1, 0}, dp_{i-1,1}\}$。

对于 $dp_{i, 1}$，考虑 $i$ 是否与前一段合法括号序列合并，得到 $dp_{i, 1}=\max\{\max\{dp_{j-1, 0}, dp_{j-1,1}\}+a_i-a_j, dp_{j - 1, 1}+a_i-a_{j-1}\}$。

时间/空间复杂度：$\mathcal O(n)$。

---

### 代码

```cpp
#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 inf = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    std::vector<int> a(n);
    for (int i = 0; i < n; i ++ ) {
        std::cin >> a[i];
    }

    std::vector<std::array<i64, 2>> f(n + 1, {-inf, -inf});
    f[0][0] = f[0][1] = 0;
    std::vector<int> stk;
    for (int i = 0; i < n; i ++ ) {
        f[i + 1][0] = std::max(f[i][0], f[i][1]);
        if (s[i] == '(') {
            stk.push_back(i);
        } else if (!stk.empty()) {
            int x = stk.back();
            f[i + 1][1] = std::max(std::max(f[x][0], f[x][1]) + a[i] - a[x], x ? f[x][1] + a[i] - a[x - 1] : -inf);
            stk.pop_back();
        }
    }
    std::cout << std::max(f[n][0], f[n][1]) << "\n";

    return 0;
}
````

---

## 作者：EricWan (赞：0)

简单的括号序列处理与 DP。

首先，我们维护这样三个数组：

$dp_i$ 为恰好有一个分段在 $i$ 结束的方案的最大价值。

$maxn_i$ 为 $\max_{i=1}^idp_i$。

$lst_i$ 为以 $i$ 结束的最短的合法括号序列的起始位置。

维护 $lst_i$，可以通过

```cpp
int now = i - 1;
while (s[now] != '(')
{
	now = lst[now] - 1;
	if (now <= 0)
	{
		break;
	}
}
```

暴力跳，可以证明这是线性的。

如果 $lst_i$ 不存在（`now <= 0`）：

```cpp
dp[i] = -INF;
maxn[i] = maxn[i - 1];
continue;
```

否则：

```cpp
lst[i] = now;
dp[i] = max(maxn[lst[i] - 1] + a[i] - a[lst[i]], dp[lst[i] - 1] - a[lst[i] - 1] + a[i]);
maxn[i] = max(maxn[i - 1], dp[i]);
```

解释一下：

`maxn[lst[i] - 1] + a[i] - a[lst[i]]` 为开一个新段的最优答案。

`dp[lst[i] - 1] - a[lst[i] - 1] + a[i]` 为接着上一段的最优答案。

之后我们就愉快地解决了。

---

## 作者：锦依卫小生 (赞：0)

# P10115  
## 思路与做法  
采用动态规划的方法。令 $f(i)$ 表示 序列 $1$ 到 $i$ 的最大美丽度，不难得到转移方程：$f(i)=\max(f(j)+a(i)-a(j+1),f(i-1))$。其中序列 $j+1$ 到 $i$ 为合法括号序列，取最大值函数前者表示枚举 $i$ 所在合法括号序列的起始位置，后者表示 $i$ 不加入合法序列，即自己为一个子序列。  
可以用栈的方式来确定每个右半括号相对的左半括号，其位置记为 $d(i)$。（详见代码，这里不再赘述）。显然，对每个 $i$ 直接枚举 $j$ 的方法会使得时间复杂度过高。
进一步分析，对每一次状态转移，可以将转移方程写为 $f(j)-a(j+1)+a(i)$。这就意味着当前 $f(i)$ 是由 $f(j)-a(j+1)$ 中最大的项得到的。令 $g(i)$ 表示从 $i$ 开始向前所有合法序列（以 $i$ 结尾）中 $f(j)-a(j+1)$ 最大值，则 $f(i)=\max(g(d(i)-1)+a(i),f(i-1))$ ，并且每一次状态转移都更新维护 $g(i)$。这样时间复杂度就变成 $O(n)$。（这个思路与单调队列优化的一些处理类似，但是本题没用单调队列那么复杂）
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX=3e6+5;
int n,a[MAX],d[MAX];
string ss;
stack<int> s;
long long f[MAX],g[MAX];
int read(){
	int f=1,k=0;
	char c=getchar(); 
	
	while(c<'0'||c>'9'){
		if(c=='-') 
		f=-1;
		c=getchar(); 
	}

	while(c>='0'&&c<='9'){
		k=k*10+c-'0';
		c=getchar();
	}
	return f*k;
	
}
int main(){
	cin>>n>>ss;
	for(int i=1;i<=n;++i)
		a[i]=read();
	for(int i=0;i<=n-1;++i){
		if(ss[i]=='('){
			s.push(i);
		}
		else{
			if(!s.empty()){
				d[i+1]=s.top()+1;
				s.pop();
			}
			else{
				d[i+1]=-1;
			}
		}
	}
	g[0]=-a[1];
	for(int i=1;i<=n;++i){
		if(ss[i-1]=='('){
			f[i]=f[i-1];
			g[i]=f[i]-a[i+1];
		} 
		else{
			if(d[i]!=-1){
				f[i]=max(g[d[i]-1]+a[i],f[i-1]);
				g[i]=max(g[d[i]-1],f[i]-a[i+1]);
			}
			else{
				f[i]=f[i-1];
				g[i]=f[i]-a[i+1];
			}
				
		}
	}
	cout<<f[n];
} 

```




---

## 作者：sbno333 (赞：0)

我们发现这道题与 `Csp2023-S T2` 都是匹配，因此可以模仿。

对于每一个位置，我们记录其作为合法括号序列的末尾时合法括号序列（可能是多个合法的末尾）前一位左括号的下标最大值，特别的，左括号记录自己。

这样我们可以通过调用前一个括号记录来获得以本次括号为末尾的合法序列左括号下标最大值，显然每一个合法序列都是通过这些若干最短合法序列构成。

我们记录一个答案表示以当前为结尾的答案，显然可以自己为一个子段，即可以等于前一个括号记录的答案。而难题在于以自己为末尾时的答案，显然自己需要能够构成合法序列才行，而答案为每一个自己的权值减去合法的左括号的权值加上左括号前一位的答案的最大值，考虑维护合法括号右端点答案减去接下来的左括号权值的最大值，这样可以直接加，而对于每一个左括号，都等于 **上一个连续的** 合法序列后左括号权值和当前合法序列减去自己最大值。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct st{
	char t;
	int sum;
	int ans;
	int xb;	
}sd[3000009];
int a[3000009];
string tt;
signed main(){
	int n;
	cin>>n;
	cin>>tt;
	for(int i=1;i<=n;i++){
		sd[i].t=tt[i-1];//数据出大锅，否则直接cin
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int ans;
	ans=0;
	for(int i=1;i<=n;i++){
		if(sd[i].t=='('){
			sd[i].ans=sd[i-1].ans;//直接转移
			sd[i].xb=i;//左括号更新为自己，方便后续
			if(!sd[i].sum){//维护的权值没有
				sd[i].sum=sd[i-1].ans-a[i];//答案减去权值
			}
		}else{
			if(sd[i-1].xb==0){//没有合法括号
				sd[i].sum=0;//没得可维护的，因为合法序列需要连续的合法序列组成
				sd[i].ans=sd[i-1].ans;
				continue;
			}
			sd[i].xb=sd[sd[i-1].xb-1].xb;//上一个前部括号的在以前合法的括号
			sd[i].ans=max(sd[i-1].ans,sd[sd[i-1].xb].sum+a[i]);//前一个答案或者之前的最大维护的值
			sd[i+1].sum=max(sd[i].ans-a[i+1],sd[sd[i-1].xb].sum);//更新下一个括号维护的值，显然这个维护的值至于左括号相关，但这里不特判程序不会出错
		}
	}
	cout<<sd[n].ans;
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 思路


首先我们考虑暴力 dp。

记 $f_i$ 表示子序列 $a_{1\sim i}$ 的最大美丽度。那么转移就是：

$f_i=\max(f_i,f_j+a_i-a_{j+1})$，满足 $s_{j\sim i}$ 为一个合法括号序列。

那么我们可以尝试枚举 $j$。为了判定 $s_{j\sim i}$ 是否为一个合法括号序列，我们先计算 $s$ 的前缀和，将 `(` 看成 $1$，`)` 看成 $-1$，然后处理出前缀和数组 $q$。那么若 $s_{j\sim i}$ 为一个合法括号序列，当且仅当 $q_{j-1}=q_i$ 且 $\min\limits_{k\in[j-1,i]}q_k=q_i$。

为了快速判断，我们可以使用 ST 表。由于笔者比较喜欢线段树，所以给出线段树代码。

```C++

int n,ans;
int s[N],a[N];
int f[N];
int tr[N];

void pushup(int x){
  tr[x]=min(tr[x<<1],tr[x<<1|1]);
}

void build(int x,int l,int r){
  if(l==r){
    tr[x]=s[l];
    return ;
  }
  int mid=l+r>>1;
  build(x<<1,l,mid);
  build(x<<1|1,mid+1,r);
  pushup(x);
}

int query(int x,int l,int r,int pl,int pr){
  if(l>=pl&&r<=pr){
    return tr[x];
  }
  int mid=l+r>>1;
  int res=INF;
  if(pl<=mid)res=min(res,query(x<<1,l,mid,pl,pr));
  if(pr>mid)res=min(res,query(x<<1|1,mid+1,r,pl,pr));
  return res;
}

signed main(){
  n=rd;
  for(int i=1;i<=n;i++){
    char c;
    cin>>c;
    if(c=='(')s[i]=1;
    else s[i]=-1;
    s[i]=s[i-1]+s[i];//前缀和
  }

  build(1,1,n);
  for(int i=1;i<=n;i++){
    a[i]=rd;
  }
  for(int i=1;i<=n;i++){
    f[i]=max(f[i-1],0ll);
    for(int j=0;j<i-1;j++){

      if(s[j]==s[i]&&query(1,1,n,j,i)>=s[i]){
        //说明[j+1,i]是一个合法序列
        f[i]=max(f[i],f[j]+a[i]-a[j+1]);
      }
    }
  }
  cout<<f[n]<<endl;
}
```


但很显然这会超时，我们应该优化掉枚举 $j$ 的过程。

我们考虑做括号序列的流程——我们要维护一个栈，当来了一个 `(` 时将其入栈，当来了一个 `)` 时将栈顶弹出。接下来我们考虑当前枚举到的字符 $s_i$。

- 若 $s_i $ 为 `(`，那么 $f_i$ 一定继承 $f_{i-1}$ 的值。

- 若 $s_i$ 为 `)`，那么我们要枚举其所有的满足匹配的位置。但是很显然有一些位置我们是不需要的。

如果我们可以从 $3$ 处的元素匹配，那么我们是不是也可以只和 $1$ 处或 $2$ 处（下面例子）的栈顶元素匹配呢？很显然是的。把上面的变成具体的例子就是：

```Plain Text
...(...)(...)(...)   ... 代表合法的括号序列
       1    2    3
```


于是我们发现如果用数组模拟栈且栈底编号为 $1$ 的话，那么当前要弹出的元素是编号为 $k$ 的元素，则以往处在 $k$ 的元素都可以转移到当前的 $f_i$。

于是我们在把 `(` 入栈时其实是把当前的 $i$ 入栈，并且在栈的每一个位置开一个 vector 记录所有压在这个位置的 $i$，这样我们就可以在下一次需要知道这个位置有哪些 $i$ 可供我们转移了。

但是我们可以优化掉这个 vector。我们观察 dp 转移方程，我们发现只需要让 $f_j+a_{j+1}$ 尽可能大就行了（这里的 $j$ 就是 vector 中记录的那些 $i$）。于是我们把 vector 去掉，只保留原来记录的那些 $i$ 中使 $f_i+-a_{i+1}$ 最大的那个 $i$ 即可。

但是有一点我们要排除——我们还要保证两个处在栈中 $k$ 处的元素中间的括号序列是合法的！你可能会有疑问：不是处于同一个位置就保证了中间的括号序列左右括号数量相同吗？可是我们还要考虑类似 `))((` 的情况。

此时以往的一些信息就了，因为如果取了，最终取到的区间就会包含上面的那个低谷，就会出现上述类似的情况。

于是我们开一个标记 $fl$ 表示 $fl$ 以上的信息作废（也相当于 $mx$ 的栈顶吧），因此我们需要维护一个真实信息栈 $stk$，并把上面优化掉 vector 的那个栈记为 $mx$。

- 若 $s_i$ 为 `)`，则当目前的 $s_i$ 要弹出栈中的那个元素在栈中的下标 $≤fl$ 时，才可以使用 $mx$ 中记录的信息。

- 若 $s_i$ 为 `(`，则加入 $stk$ 并尝试更新 $mx$ 中的相应位置。

---

```C++
/*
CB Ntsc
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define pf first
#define ps second

#define err cerr<<"Error"
#define rd read()
// #define nl putc('\n')
#define ot write
#define nl putchar('\n')
inline int rd
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}

const int INF = 1e13;
const int N = 3e6+5;
const int M = 1e6+5;
const int S=1e6+5;
const int maxlog = 10;

int n,ans;
int s[N],a[N];
int f[N];
int stk[N],top;
int mx[N];
int q[N];

signed main(){
  n=rd;
  for(int i=1;i<=n;i++){
    char c;
    cin>>c;
    if(c=='(')s[i]=1;
    else s[i]=-1;
    q[i]=q[i-1]+s[i];//前缀和
  }

  for(int i=1;i<=n;i++){
    a[i]=rd;
  }
  int fl=0;

  for(int i=1;i<=n;i++){
    f[i]=max(f[i-1],0ll);
    if(s[i]==1){
      stk[++top]=i;
      if(fl>=top){
        if(a[i]-f[i-1]<=a[mx[top]]-f[mx[top]-1])mx[top]=i;
      }else{
        mx[top]=i,fl=top;
      }
    }
    else{
      if(top){
        int l;
        l=stk[top];
        f[i]=max(f[i],f[l-1]+a[i]-a[l]);
        if(fl>=top)l=mx[top],
        f[i]=max(f[i],f[l-1]+a[i]-a[l]);
        fl=min(fl,top);
        top--;
      }else{
        fl=0;
      }
    }
    
  }
  cout<<f[n];

}

/*
4
()()
1 -1 5 11

4
()()
1 6 5 11
*/
```




---

## 作者：D2T1 (赞：0)

首先用栈求出对于每个 $i$，在它前面最近的一个位置 $le_i$ 使得 $S[le_i,i]$ 为一个合法的括号序列，那么所有以 $i$ 结尾的合法括号序列就是 $S[le_i,i],S[le_{le_i-1},i]$ 等等。

设 $f_i$ 表示以 $i$ 结尾且选择一个以 $i$ 结尾的括号串的最大美丽度；$g_i$ 表示以 $i$ 结尾，包含 $i$ 的不一定是括号串的最大美丽度。因为我们可能选一个类似 `()()` 的串，所以还需要一个 $h_i$ 表示选择一个后缀作为已经匹配的括号串，但这个括号串还没有结束的最大美丽度（这时 $h_i$ 就不用加上 $a_i$）。

转移很简单：

$h_i=\max(g_{le_i-1}-a_{le_i},h_{le_i-1})$

$f_i=\max(h_i+a_i,g_{le_i-1}+a_i-a_{le_i})$

$g_i=\max(g_{i-1},f_i)$

注意 $h,f$ 的转移都要在 $le_i$ 存在时再进行。

```cpp
//P10115
#include <bits/stdc++.h>
using namespace std; typedef long long ll;
void solve();int main(){ solve(); return 0; }

const int N = 6e6 + 10;
ll f[N], g[N], h[N], a[N];
int n, le[N], st[N], tp;
char s[N];

void solve(){
	scanf("%d%s", &n, s+1);
	for(int i = 1; i <= n; ++ i){
		scanf("%d", &a[i]);
	}
	for(int i = 1; i <= n; ++ i){
		if(s[i] == '\('){
			st[++tp] = i;
		} else {
			if(tp){
				le[i] = st[tp];
				-- tp;
			}
		}
	}
	memset(f, 0xcf, sizeof(f));
	memset(g, 0xcf, sizeof(g));
	memset(h, 0xcf, sizeof(h));
	f[0] = g[0] = 0;
	for(int i = 1; i <= n; ++ i){
		if(le[i]){
			h[i] = max(g[le[i]-1] - a[le[i]], h[le[i]-1]);
			f[i] = max(h[i] + a[i], g[le[i]-1] + a[i] - a[le[i]]);
		}
		g[i] = max(g[i-1], f[i]);
	}
	printf("%lld\n", g[n]);
}
```

---

## 作者：ljjl (赞：0)

# 题目大意

给定一个括号串 $S$ 和一个数组 $a$ 并将 $S$ 分成若干个合法括号子串，子串 $S_{l,r}$ 的贡献是 $a_r - a_l$，求各子串贡献和最大多少。

# 思路

考虑动态规划，$f_i$ 表示 $S_{1,i}$ 最多可以产生多少贡献。

## 转移方程

用 $l_i$ 表示最大且 $S_{l_i,i}$ 为合法串的坐标，$l$ 数组可以用栈求。很明显，$S_{l_i,i}$ 可以与 $S_{l_{l_i-1},l_i-1}$ 合并成一个合法串，考虑用链表枚举所有合并串的 $l$（设为 $j$），那么每个 $j$ 就会产生一个转移方程 $f_i = a_i - a_j + f_{j-1}$。取它们 $f_{i-1}$ 的最大值就是结果。

# 优化

上面的方法是可以卡到 $O(n^2)$ 的，推一下跳链表的经过，透过现象看本质，对于跳了两次时 $l$，那么其实本质上就是将跳第一次时的 $a_r$ 替换了一下，$a_l$ 没有变化，而 $a_r$ 就是 $a_i$，所以不论怎么跳，$a_l$ 从一开始就是确定好的，于是我们只需要讨论不跳与跳一次的情况。

但这与上面方法还是有差别的，因为 $f_i$ 的结果可能与 $a_i$ 无关（也就是 $f_{i-1}$）。因此我们还要一个数组 $f2$ 记录下 $a_i$ 有产生贡献时的情况。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e6+5;
int n,a[N],f[N],f2[N],ans,l[N],maxx;
string s;
stack<int> stk;
signed main(){
	std::ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>s;
	s=" "+s;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++){
		if(s[i]=='(')
			stk.push(i);
		else if(s[i]==')')
			if(!stk.empty()){
				l[i]=stk.top();
				stk.pop();
			}
	}
	a[0]=1e18;
	for(int i=1;i<=n;i++){
		f[i]=f[i-1];
		if(l[i]==0)
			continue;
		f2[i]=f[l[i]-1]+a[i]-a[l[i]];// 不选择跳的情况 
		if(l[l[i]-1]!=0)// 保证可以跳 
			f2[i]=max(f2[i],f2[l[i]-1]+(a[i]-a[l[i]-1]));// 将a[r]从a[l[i]-1]换成a[i]，那么结果自然就比f[l[i]-1]多(a[i]-a[l[i]-1])
		f[i]=max(f[i],f2[i]);
	}
	cout<<f[n];
	return 0; 
}
```

---

