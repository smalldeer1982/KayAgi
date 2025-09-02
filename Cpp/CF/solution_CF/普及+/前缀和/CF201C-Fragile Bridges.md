# Fragile Bridges

## 题目描述

You are playing a video game and you have just reached the bonus level, where the only possible goal is to score as many points as possible. Being a perfectionist, you've decided that you won't leave this level until you've gained the maximum possible number of points there.

The bonus level consists of $ n $ small platforms placed in a line and numbered from $ 1 $ to $ n $ from left to right and ( $ n-1 $ ) bridges connecting adjacent platforms. The bridges between the platforms are very fragile, and for each bridge the number of times one can pass this bridge from one of its ends to the other before it collapses forever is known in advance.

The player's actions are as follows. First, he selects one of the platforms to be the starting position for his hero. After that the player can freely move the hero across the platforms moving by the undestroyed bridges. As soon as the hero finds himself on a platform with no undestroyed bridge attached to it, the level is automatically ended. The number of points scored by the player at the end of the level is calculated as the number of transitions made by the hero between the platforms. Note that if the hero started moving by a certain bridge, he has to continue moving in the same direction until he is on a platform.

Find how many points you need to score to be sure that nobody will beat your record, and move to the next level with a quiet heart.

## 说明/提示

One possibility of getting $ 5 $ points in the sample is starting from platform $ 3 $ and consequently moving to platforms $ 4 $ , $ 3 $ , $ 2 $ , $ 1 $ and $ 2 $ . After that the only undestroyed bridge is the bridge between platforms $ 4 $ and $ 5 $ , but this bridge is too far from platform $ 2 $ where the hero is located now.

## 样例 #1

### 输入

```
5
2 1 2 1
```

### 输出

```
5
```

# 题解

## 作者：pythoner713 (赞：3)

这题妙在**将路线拆成向左、向右两段，分别DP后合并答案**。

设 $f[i][0/1]$ 表示**从岛 $i$ 向左走 不保证 / 保证 回到岛 $i$ 的最大分数**

设 $g[i][0/1]$ 表示**从岛 $i$ 向右走 不保证 / 保证 回到岛 $i$ 的最大分数**

这个状态可能有些麻烦。可以自行理解一下，然后对样例模拟一遍，得到：

![](https://i.loli.net/2020/12/23/E6XxApSI2UP3R5k.png)

那么答案就是：$\max\{f[i][0]+g[i][1],f[i][1]+g[i][0]\}$

可以结合下图理解：

![无标题.png](https://i.loli.net/2020/12/24/2uNHIRr4MxOq8ma.png)

分别对应这个点：

- 先往右走，回到原点再往左走
- 先往左走，回到原点再往右走 

的两种情况。
这样便可以将一个不定的路线问题，拆成两个单向路径，然后通过线性 DP 分别求解 $f,g$。

先观察一边，$f[i][1]$ 是容易求的。因为要保证回到岛 $i$，因此也必然经过岛 $i-1$，如下图：

![无标题.png](https://i.loli.net/2020/12/23/aE7e2ITmgwv8xjR.png)

经过岛 $i-1$ 时的分数为 $f[i-1][1]$。经过桥 $a[i-1]$ 时，不难发现我们可以在这座桥上反复横跳直到把它榨干，从而得到 $\left\lfloor a[i-1]/2 \right\rfloor\times2$ 的分数（例如耐久度为 $7$ 时可以走 $6$ 次回到 $i$）。因此：

$$f[i][1]=f[i-1]+\left\lfloor a[i-1]/2 \right\rfloor\times2$$

而对于不保证回到岛 $i$ 的 $f[i][0]$，可以分以下三种情况：

$$f[i][0]=
\max
\begin{cases} f[i][1] & (1)
 \\ f[i - 1][0] + a[i - 1] - [a[i - 1] \text{ is even}] & (2)
 \\ f[i - 1][1] + a[i - 1] & (3)
\end{cases}$$

- 情况 $(1)$ 相当于直接回到岛 $i$。
- 情况 $(2)$ 相当于向左走到 $i-1$ 并不保证回来。那么对于中间这座桥 $a[i-1]$，不难发现如果其次数为偶则无法走满（因为不一定回来），则需特判减一。
- 情况 $(3)$ 相当于向左走并保证回来，那么对于中间这座桥必定可以走到它断，无需特判。

至此，我们已经把 $f$ 讨论完毕。对于 $g$ 只需照葫芦画瓢，将方向反过来即可，~~读者自证不难~~。

```cpp
#include<bits/stdc++.h>
#define int long long
#define nb 200010
using namespace std;

int ans, n, a[nb], f[nb][2], g[nb][2];

main(){
	cin >> n;
	for(int i = 1; i < n; cin >> a[i++]);
	for(int i = 2; i <= n; i++){
		if(a[i - 1] > 1) f[i][1] = f[i - 1][1] + a[i - 1] / 2 * 2;
		f[i][0] = max(f[i][1], f[i - 1][0] + a[i - 1] - !(a[i - 1] & 1));
		f[i][0] = max(f[i][0], f[i - 1][1] + a[i - 1]);
	}
	for(int i = n - 1; i; i--){
		if(a[i] > 1) g[i][1] = g[i + 1][1] + a[i] / 2 * 2;
		g[i][0] = max(g[i][1], g[i + 1][0] + a[i] - !(a[i] & 1));
		g[i][0] = max(g[i][0], g[i + 1][1] + a[i]);
	}
	for(int i = 1; i <= n; i++){
		ans = max(ans, max(f[i][0] + g[i][1], f[i][1] + g[i][0]));
	}
	cout << ans;
	return 0;
}
```



---

## 作者：Wf_yjqd (赞：2)

剩下几篇题解全一个思路，也挺好理解。

不过我就用官方做法吧（不想抄袭）。

------------

首先考虑这题最终路径的形态，类似于一个一笔画问题（好像也没啥关系）。

假如用 $i$ 表示起点，$j$ 表示终点。

我们认为 $i\le j$，否则就把 $i$ 和 $j$ 反过来也同理。

经过试验，$i$ 左边的以及 $j$ 右边的每个桥都经过了偶数次（可能为 $0$），中间的都经过了奇数次。

也好理解，两边的每出去 $1$ 次就需要折回来 $1$ 次，中间的就不用折回来。

那么我们考虑维护 $l_x$，$r_x$，$dis_{x,y}$ 分别表示从 $x$ 出发向左每个桥经过偶数次的最大答案，向右的最大答案和从 $x$ 到 $y$ 每个桥经过奇数次的最大答案。

易知给定 $i$，$j$ 时，答案为 $l_i+dis_{i,j}+r_j$。

这样的话复杂度就是 $\operatorname{O}(n^2)$，肯定过不了。

可以通过一个前缀和把两维的距离处理掉，用 $qzdis_x$ 表示 $1$ 到 $x$ 每个桥经过奇数次的最大答案，那么 $dis_{i,j}=qzdis_j-qzdis_i$。

我们枚举 $j$ 的同时，记录前缀最大的 $l_i-qzdis_i$，那复杂度就是 $\operatorname{O}(n)$ 的了。

------------

没理解的话就看代码吧。。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=1e5+84;
ll n,ans,a[maxn],tl[maxn],tr[maxn],qzdis[maxn],maxl;
inline ll se(ll x){
    return ll(x/2)*2;
}
int main(){
    scanf("%lld",&n);//也不知道为啥题目里说不能用
    n--;
    for(ll i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    for(ll i=2;i<=n;i++)
        tl[i]=(a[i-1]>1?tl[i-1]:0)+se(a[i-1]);
    for(ll i=n;i>=1;i--)
        tr[i]=(a[i]>1?tr[i+1]:0)+se(a[i]);
    for(ll i=1;i<=n;i++)
        qzdis[i]=qzdis[i-1]+se(a[i]+1)-1;
    maxl=tl[1];
    ans=tl[1]+tr[1];
    for(ll i=2;i<=n+1;i++){
        maxl=max(maxl,tl[i]-qzdis[i-1]);
        ans=max(ans,tr[i]+qzdis[i-1]+maxl);
    }
    printf("%lld Sherry",ans);
    return 0;
}
```


---

## 作者：Ghosty_Neutrino (赞：1)

~~怎么又是暴力啊。~~
## 题意
有 $n$ 个点，$n-1$ 座桥，每座桥最多通过 $a_i$ 次，每通过一次可以获得 $1$ 分。

然后问你怎么选择起点和路线，才能获得最多的分数。
## 分析
我们想想可以发现，我们令 $l_i$ 表示 $i$ 点向左边走，且最后回到 $i$ 点最多能得多少分，$r[i]$ 表示 $i$ 点向右走，且最后回到 $i$ 点最多能得多少分。

$odd_i$ 表示，从 $1$ 号桥开始，走到 $i$ 号桥，最多能得多少分。

显然，我们这道题要求的最大值，应该就是 $l_i-odd_i+r_j+odd_j$ 这个东西，使得这个东西最大就好了。

我们暴力枚举 $j$，然后每次用 set 去拿到最大的 $l_i-odd_i$ 就好了。

其实就是枚举和 set。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
template <class T1, class T2> inline void gmax(T1 &a, T2 b){a = max(a, b);}
long long l[maxn], r[maxn], odd[maxn];
//l[i]表示i点向左边走，且最后回到i点最多能得多少分
//r[i]表示i点向右走，且最后回到i点最多能得多少
//odd[i]表示,从1号桥开始，走到i号桥，最多能得多少分
//求l[i] - ood[i] + r[j] + ood[j]
int n;
long long a[maxn];
int cal(int x){
    if(x%2 == 1) return x-1;
    return x;
}
set<long long> s;
int main(){
    scanf("%d",&n);
    for(int i=0;i<n-1;i++) scanf("%lld",&a[i]);
    for(int i=1;i<n-1;i++){
        if(a[i-1]>1)l[i]=l[i-1]+cal(a[i-1]);
    }
    for(int i=n-2;i>=0;i--){
        if(a[i]>1){
            r[i]=r[i+1]+cal(a[i]);
        }
    }
    for(int i = 0; i < n - 1; i++){
        odd[i]+=cal(a[i]-1)+1;
        if(i>0) odd[i]+=odd[i-1];
    }
    long long ans=l[0]+r[0];
    s.insert(l[0]);
    for(int i=1; i<n;i++){
        s.insert(l[i]-odd[i-1]);
        long long x=*--s.lower_bound(1LL*1e16);
        gmax(ans,r[i]+odd[i-1]+x);
    }
    printf("%lld\n",ans);
    return 0;
}

```
量子表示：暴力和 dp 是我的一生。

---

## 作者：cqbzrjx (赞：0)

[原题传送门](https://codeforces.com/problemset/problem/201/C)

# 题意

这个游戏有 $n$ 个桥，每个桥连接两个平台。但分别每个桥只能走 $a_i$ 次，之后这个桥就不能在通行。求最大的走过桥的次数。

# 分析

开一个二维  ```dp``` ，第一维表示**当前位置**，第二维则表示**四种情况**。

1. ```dp[i][0]``` 表示当前平台**往左走并不回来**
1. ```dp[i][1]``` 表示当前平台**往左走并回来**
1. ```dp[i][2]``` 表示当前平台**往右走并不回来**
1. ```dp[i][3]``` 表示当前平台**往右走并回来**

  先**从前往后**顺着 $dp$ 一遍，再**从后往前**倒着一遍，最后把第 $0$ 段和第 $3$ 段合成一块，第 $1$ 段和第 $2$ 段合并一起，再求出一个最大值即可。

# AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;//数据范围
ll n,sum;//sum求最大值
ll a[maxn],dp[maxn][4];//a[i]为平台
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n;//输入
	for(ll i = 1;i < n;i++)
	{
		cin>>a[i];
	}
	for(ll i = 2;i <= n;i++)//往左走并决定是否来回
	{
		dp[i][0] = max(dp[i - 1][0],dp[i - 1][1]);
		if(a[i - 1] & 1) dp[i][0] += a[i - 1];
      	//a[i - 1] & 1 判断奇偶性
		else dp[i][0] += a[i - 1] - 1;//往前走时回来就会剩一次
		if(a[i - 1] > 1)//有可能走过桥就回不来
		{
			if(a[i - 1] & 1) dp[i][1] = dp[i - 1][1] + a[i - 1] - 1;//返回平台时，为奇数时回不来，需少一次
			else dp[i][1] = dp[i - 1][1] + a[i - 1];
		}
	}	
	for(ll i = n - 1;i >= 1;i--)//往右走并决定是否来回
	{
		dp[i][2] = max(dp[i + 1][2],dp[i + 1][3]);
		if(a[i] & 1) dp[i][2] += a[i];
		else dp[i][2] += a[i] - 1;//同理
		if(a[i] > 1)
		{
			if(a[i] & 1) dp[i][3] = dp[i + 1][3] + a[i] - 1;//同上面
			else dp[i][3] = dp[i + 1][3] + a[i];
		}
	}
	for(ll i = 1;i <= n;i++)
	{
		sum = max(sum,max(dp[i][0] + dp[i][3],dp[i][1] + dp[i][2]));//求最大值
	}
	cout<<sum;//输出最大值
	return 0;//完结，撒花
}
```

---

## 作者：cqbzhr (赞：0)

## 正解 $\operatorname{dp}$。

这个题属实非常的妙啊，本可以分两段 $0$ 或 $1$ 来解题，但本蒟蒻一个脑抽划了四层做，做完发现貌似更麻烦了……

### 正解

顺着 $\operatorname{dp}$ 一遍，再倒着来一遍，把两段分别求出的最大值相加：第 $0$ 段和第 $3$ 段合成一块，第 $1$ 段和第 $2$ 段合成一块，即，往左边走且不回来加往右边走且必须回来的最大分值，与左边走且必须回来加往右边走且不回来的最大分值，再求出一个最大值即可。

状态转移(三目运算符简写)：

```cpp
dp[i][0]=max(dp[i-1][0],dp[i-1][1])+((a[i-1]&1)?a[i-1]:(a[i-1]-1));
```

```
dp[i][1]=dp[i-1][1]+((a[i-1]&1)?(a[i-1]-1):a[i-1]);//a[i-1]>1
```

```cpp
dp[i][2]=max(dp[i+1][2],dp[i+1][3])+((a[i]&1)?a[i]:(a[i]-1));
```

```
dp[i][3]=dp[i+1][3]+((a[i]&1)?(a[i]-1):a[i])//a[i]>1
```

#### AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
long long a[100005],ans,dp[100005][5];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>a[i];
	}
	for(int i=2;i<=n-1;i++){
		if(a[i-1]&1)dp[i][0]=max(dp[i-1][0],dp[i-1][1])+a[i-1];
		else dp[i][0]=max(dp[i-1][0],dp[i-1][1])+a[i-1]-1;
		if(a[i-1]>1){
			if(a[i-1]&1)dp[i][1]=dp[i-1][1]+a[i-1]-1;
			else dp[i][1]=dp[i-1][1]+a[i-1];
		}
	}
	for(int i=n;i!=0;i--){
		if(a[i]&1)dp[i][2]=max(dp[i+1][2],dp[i+1][3])+a[i];
		else dp[i][2]=max(dp[i+1][2],dp[i+1][3])+a[i]-1;
		if(a[i]>1){
			if(a[i]&1)dp[i][3]=dp[i+1][3]+a[i]-1;
			else dp[i][3]=dp[i+1][3]+a[i];
		}
	}
	for(int i=1;i<=n;i++){
		ans=max(ans,max(dp[i][0]+dp[i][3],dp[i][1]+dp[i][2]));
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Liynw (赞：0)

### 前言

[题目链接](https://www.luogu.com.cn/problem/CF201C)

**正解：动态规划**

思路不是很好想，想出来了应该就没有多大问题了，但是需要处理的细节较多，~~再加上水水的样例~~，难度应该是偏难的。个人感觉应该是绿到蓝的亚子。

***

### 先说说思路的来源（错误解法，不想看请跳过）

中午打开题目，第一反应：这不是一个暴搜部分分到手吗？

打了个无脑暴搜，深搜+回溯，分别向往左走和往右走的方向进行搜索，只是需要注意变量初始化和判断是否可以走。

时间复杂度 $Θ(2^{n})$，校内 OJ $15pts$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans,a[100005];
int dfs(int i,int sum){
    int left=sum,right=sum;
    if(!a[i-1]&&!a[i+1]) return sum;
    if(a[i-1]){ //可以往左走
        a[i-1]--; //要耗费一次桥的耐久度
        left=dfs(i-1,sum+1);
        a[i-1]++; //回溯
    }
    if(a[i+1]){ //可以往右走
        a[i+1]--; //要耗费一次桥的耐久度
        right=dfs(i+1,sum+1);
        a[i+1]++; //回溯
    }
    return max(left,right); //返回最大值
}
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n-1;i++){
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=n-1;i++){
        ans=max(ans,dfs(i,0));
    }
    printf("%lld",ans);
    return 0;
} 
```

~~可是 CF 的题都是绑在一个点上的啊~~，于是~~还没把正解想出来的~~我开始想怎么优化。

我先想到了一个~~假~~优化：使用一个前缀和 $pre$ 数组统计一下前面最多可能得多少分，如果现在得的分 + 往左/右走能拿到的最多的分都不可以更新答案的话就不用搜这一边了。

程序不做展示，但是我发现样例竟然没过……

淦，那到底是哪里出问题了呢？

经过短暂的思考我们可以发现，完全有这么一种可能：

>假设你现在从第 $i$ 个平台往左走，在左边尽量赚到最多的分数之后回到第 $i$ 个平台，然后再往右边走，再在右边的平台结束游戏。

此时的得分完全是有可能高于 $pre_{i-1}+sum$ 或 $ans$ 的。

***

### 正解

上面的枝我们减错了，但是事情却有了一点眉目：

这道题好像每次的状态转移都与他**离开之后回不回来**有关系。

为了方便，我们将第 $i$ 与 $i+1$ 个平台中的桥定义为 $i$ 号桥，这也与输入的数组下标对应。

所以可以定义 $dp$ 数组意义如下：

- $dp_{i,0}$ 代表往左边走且不回来。

- $dp_{i,1}$ 代表往左边走且**必须**回来。

- $dp_{i,2}$ 代表往右边走且不回来。

- $dp_{i,3}$ 代表往右边走且必须回来。

PS：关于必须回来这一个点，现有的题解说的是**不保证回来**，那么就有两种情况，较难判断。所以设置绝对一点较好思考。

首先思考 $dp_{i,0}$ 的情况。如果我们从第 $i$ 个平台往左边走（而且可以走），就一定会走到第 $i-1$ 个桥上。

而因为不回第 $i$ 个平台，所以我们无需考虑到了第 $i-1$ 个平台后再往左走（不考虑直接返回），还能不能回到第 $i-1$ 的平台。因此，对于走到第 $i-1$ 个平台能获得的最大分数，就为 $dp_{i-1,0}$ 和 $dp_{i-1,1}$ 的最大值。

然后再求从第 $i$ 个平台到第 $i-1$ 个平台能获得的最大分数。

首先要明确，我们是不回来的，所以最优的方式就是把这座桥尽量“榨干”，即能走断就走断，在两个平台之间反复横跳。但是若是要走到对面，需要走桥的次数必须是奇数。所以，如果桥当前还能走的最大次数是偶数，那就必须留一次走的机会（不然就走回去走不过来了）。

所以可以得出，往返这两个平台间能获得的最大分数（暂时叫 $score$）为：

$$
  score= 
  \begin{cases}
   a_{i-1},2\not|\;a_{i-1}\\
	a_{i-1}-1,2\;|\;a_{i-1}
  \end{cases}
$$

在 c++ 中，我们可以用更加简洁的三目运算符表示。

```cpp
dp[i][0]=max(dp[i-1][0],dp[i-1][1])+((a[i-1]&1)?a[i-1]:(a[i-1]-1));
```

接着看必须回来的情况。如果要保证回到第 $i$ 个平台，那么必须保证要先回到第 $i-1$ 个平台，然后还要能从中间那座桥走过去。所以前面加上的是 $dp_{i-1,1}$，没有别的情况。

像之前那样考虑在中间走能拿到的最大分数。因为要回去，我们需要经过偶数次桥。如果当前桥能走的次数是奇数，那就只能浪费一次机会达到能回来的目的。

$$
  score= 
  \begin{cases}
   a_{i-1}-1,2\not|\;a_{i-1}\\
	a_{i-1},2\;|\;a_{i-1}
  \end{cases}
$$

同样可以用三目运算符解决。

```cpp
dp[i][1]=dp[i-1][1]+((a[i-1]&1)?(a[i-1]-1):a[i-1]);
```

不过这样还是不对，大家是否注意到这个程序没有关于**无法走动的判断**？现在这个判断来了！

如果这座桥能走的次数为 $1$，那我走过去这座桥就断了，无法回来。为此，我只能放弃前面的所有分数。

所以上述程序只有在 $a_i>1$ 时才能执行，当 $a_i=1$ 时，$dp_{i,1}$ 的值为 $0$（不用赋值）。

右边同理。只是循环要倒着枚举而已。

最后我们需要知道答案时什么。因为每一个平台都有可能作为出发点，所以需要枚举求解最优解。

那么，对于每一个点，我们可以先往左边走回来再往右边不回来，也可以先往右边回来再往左边不回来。所以答案就为：

$$ans=\max_{i=1}^{n}\{dp_{i,0}+dp_{i,3},dp_{i,1}+dp_{i,2}\}$$

**提示：打代码的时候一定要注意你的这个下标到底代表的是平台还是桥！** 在这道题中，$dp$ 数组代表的是平台，$a$ 数组代表的是桥。

### $Code$

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans,n,a[100005],dp[100005][4];
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n-1;i++) scanf("%lld",&a[i]);
	for(int i=2;i<=n-1;i++){
		dp[i][0]=max(dp[i-1][0],dp[i-1][1])+((a[i-1]&1)?a[i-1]:(a[i-1]-1));
		if(a[i-1]>1) dp[i][1]=dp[i-1][1]+((a[i-1]&1)?(a[i-1]-1):a[i-1]); //注意加特判 
	}
	for(int i=n;i;i--){
		dp[i][2]=max(dp[i+1][2],dp[i+1][3])+((a[i]&1)?a[i]:(a[i]-1));
		if(a[i]>1) dp[i][3]=dp[i+1][3]+((a[i]&1)?(a[i]-1):a[i]);
	}
	for(int i=1;i<=n;i++) ans=max(ans,max(dp[i][0]+dp[i][3],dp[i][1]+dp[i][2]));
	printf("%lld",ans);
	return 0;
}
```

~~比暴力还短吼~~

提交记录作证 qwq：[link](https://www.luogu.com.cn/record/51511192)

---

## 作者：LCat90 (赞：0)

因为我们可以以任何一个点作为起点对所有的点进行遍历，所以两个 $dp$ 数组来记录所有的答案其中 $dp1[1][i]$ 表示从 $i$ 开始，往左走最多能走多少步，$dp1[0][i]$ 表示从 $i$ 开始往左走并返回 $i$ 能走多少步，$dp2$ 同理记录方向朝右的所有答案。

那么，根据题意，可以得到以下这些状态转移方程式：

```cpp
if(a[i] % 2 == 1) dp1[0][i] = max(dp1[0][i], dp1[0][i - 1] + a[i]);
else dp1[0][i] = max(dp1[0][i], dp1[0][i - 1] + a[i] - 1);
if(a[i] >= 2) dp1[1][i] = dp1[1][i - 1] + a[i] / 2 * 2;
else dp1[1][i] = 0;
```


往右走的情况请自己按照往左走的情况推导一下，注意 ``for`` 循环的方向。

最终的答案就是每个点 $i$ **往左走返回再往右走**和**往右走返回再往左走**的最大值.

**参考代码**:

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int Maxn = 1e5 + 5;
typedef long long ll;
inline ll read();
ll n, a[Maxn], ans, dp1[2][Maxn], dp2[2][Maxn]; // 0: 回 1:不回
int main() { 
	scanf("%lld", &n);
	for(int i = 1;i < n; ++i) scanf("%lld", &a[i]);
	for(int i = 1;i < n; ++i) {
		dp1[1][i] = a[i] <= 1 ? 0 : dp1[1][i - 1] + a[i] / 2 * 2;
		if(a[i] % 2) dp1[0][i] = a[i] + dp1[0][i - 1];
		else dp1[0][i] = max(dp1[1][i], a[i] - 1 + dp1[0][i - 1]);
	}
	for(int i = n - 2;i >= 0; --i) {
		dp2[1][i] = a[i + 1] <= 1 ? 0 : dp2[1][i + 1] + a[i + 1] / 2 * 2;
		if(a[i + 1] % 2) dp2[0][i] = a[i + 1] + dp2[0][i + 1];
		else dp2[0][i] = max(dp2[1][i], a[i + 1] - 1 + dp2[0][i + 1]);
	}
	for(int i = 0;i < n; ++i) 
		ans = max(ans, max(max(dp1[0][i]+ dp2[1][i], dp1[1][i] + dp2[0][i]), dp1[1][i] + dp2[1][i]));
 	printf("%lld", ans);
	return 0;
}
```


---

## 作者：zhou_ziyi (赞：0)

### 题目大意

这个游戏包含 $n$ 个平台，从左到右编号为 $1 \sim n$，相邻的两个平台间有一座桥。这些桥十分脆弱，游戏中会给出每座桥最多能走过的次数，第 $i$ 座桥的次数为 $a_i$。如果走这座桥走了 $a_i$ 次后这座桥就回断裂，再也不能走了。

游戏的过程是这样的：

+ 首先找到一个起始的平台。

- 如果两边有桥，可以选择一边行走。如果走过一座桥之后走过的次数已经超过了 $a_i$，这座桥就会断裂。

* 如果当前所在的平台已经没有桥连接到另外任意一个平台，游戏结束。

在游戏结束时会计算分数。分数即为走过桥的次数。

请问最大的分数是多少？

### 题目分析

我们将第 $i$ 与 $i+1$ 个平台中的桥定义为 $i$ 号桥，这也与输入的数组下标对应。

所以可以定义 $dp$ 数组意义如下：

- $dp_{i,0}$，代表往左边走且**不回来**。
- $dp_{i,1}$，代表往左边走且**必须回来**。
- $dp_{i,2}$，代表往右边走且**不回来**。
- $dp_{i,3}$，代表往右边走且**必须回来**。

首先我们思考 $dp_{i,0}$ 的情况。如果我们从第 $i$ 个平台往左边走，就一定会走到第 $i-1$ 个桥上。

我们的答案就因该为 $ans=\max(dp_{i,0}+dp_{i,2},dp_{i,1}+dp_{i,3})$

而因为不回第 $i$ 个平台，所以我们无需考虑到了第 $i-1$ 个平台后再往左走，还能不能回到第 $i-1$ 的平台。因此，对于走到第 $i-1$ 个平台能获得的最大分数，就为 $dp_{i-1,0}$ 和 $dp_{i-1,1}$ 的最大值。

我们是要不回来的，所以我们应该在这座桥中尽量多走几次，所以走的次数必须是奇数。

$dp_{i,0}=\begin{cases}\max(dp_{i-1,0},dp_{i-1,1})+a_{i-1} & 2 \nmid a_{i-1} \\\max(dp_{i-1,0},dp_{i-1,1})+a_{i-1}-1 & 2 \mid a_{i-1}\end{cases}$

在 c++ 中我们可以这样写：

```cpp
dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]) + ((a[i - 1] & 1) ? a[i - 1] : (a[i - 1] - 1));
```

接着我们考虑 $dp_{i,1}$，如果要保证回到第 $i$ 个平台，那么必须保证要先回到第 $i-1$ 个平台，然后还要能从中间那座桥走过去。所以前面加上的是 $dp_{i-1,1}$，没有别的情况。

为了拿到最大分数，我们要像之前一样，因为要回去，我们需要经过偶数次桥。如果当前桥能走的次数是奇数，那就只能浪费一次机会达到能回来的目的。

$dp_{i,1}=\begin{cases} dp_{i-1,1}+a_{i-1}-1& 2 \nmid a_{i-1} \\dp_{i-1,1}+a_{i-1} & 2 \mid a_{i-1}\end{cases}$

在 c++ 中我们可以这样写：

```cpp
dp[i][1] = dp[i - 1][1] + ((a[i - 1] & 1) ? (a[i - 1] - 1) : a[i - 1]);
```

而 $dp_{i,2}$ 和 $dp_{i,3}$ 同理，不做赘述。

### Code

```cpp
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
const int MAXN = 1e5 + 5;
ll ans;
ll n, a[MAXN], dp[MAXN][4];
int main() {
	scanf("%lld", &n);
	for(int i = 1; i < n; i++)
		scanf("%lld", &a[i]);
	for(int i = 2; i <= n; i++) {
		dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]) + ((a[i - 1] & 1) ? a[i - 1] : (a[i - 1] - 1));
		if(a[i - 1] > 1)
			dp[i][1] = dp[i - 1][1] + ((a[i - 1] & 1) ? (a[i - 1] - 1) : a[i - 1]);
	}
	for(int i = n - 1; i >= 1; i--) {
		dp[i][2] = max(dp[i + 1][2], dp[i + 1][3]) + ((a[i] & 1) ? a[i] : (a[i] - 1));
		if(a[i] > 1)
			dp[i][3] = dp[i + 1][3] + ((a[i] & 1) ? (a[i] - 1) : a[i]);
	}
	for(int i = 1; i <= n; i++)
		ans = max(ans, max(dp[i][0] + dp[i][3], dp[i][1] + dp[i][2]));
	printf("%lld", ans);
	return 0;
}
```



---

