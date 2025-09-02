# 「CROI · R2」01-string

## 题目描述

给定两个长度为 $n$ 的 $01$ 串 $S,T$，你可以对串 $S$ 执行无限次操作，每次都可以从以下操作中任选一个执行：

- 选择两个正整数 $l,r(1\le l\le r\le n)$，将 $S_l\dots S_r \ 01$ 反转。

- 选择两个正整数 $l,r(1\le l\le r\le n)$，将 $S_l\dots S_r $ 全部改为 $0$。

- 选择两个正整数 $l,r(1\le l\le r\le n)$，将 $S_l\dots S_r $ 全部改为 $1$。

你需要回答最少使用几次操作才能把 $S$ 变成 $T$。

## 说明/提示

**【样例解释】**

以下提供样例三组数据的合法方案之一：

对于第一组数据，选取 $l=1,r=5$，将 $S_l\dots S_r$ 全部变成 $1$。

对于第二组数据，选取 $l=1,r=5$，将 $S_l\dots S_r \ 01$ 反转。

对于第三组数据，先选取 $l=4,r=8$，将 $S_l\dots S_r$ $01$ 反转，再选取 $l=5,r=8$，将 $S_l\dots S_r$ 全部变成 $0$。

**【数据范围】**

**本题采用捆绑测试**。

- Sub 0（10 points）：$n\le 5$。
- Sub 1（10 points）：$n\le 18$。
- Sub 2（30 points）：$n\le 2000$。
- Sub 3（50 points）：无特殊限制。

对于所有的数据，$1\le T \le 10$，$1\le n\le 5\times 10^5$。


## 样例 #1

### 输入

```
3
00000
11111
10101
01010
11100101
11110000 ```

### 输出

```
1
1
2```

# 题解

## 作者：Link_Cut_Y (赞：22)

怎么会有这么蠢的紫题。

首先挖掘一下题目的性质。首先一个比较典的就是，翻转区间之间互不相交，覆盖区间之间互不相交。另外比较难观察的是，所有覆盖都可以在翻转后再进行，他们可以在相同步数内得到相同结果。

为什么是这样呢？假设覆盖的区间包含在翻转的区间内，假设先翻转，再覆盖成 $0$，显然我也可以用先覆盖成 $1$，在翻转来完成，他们有同样的效果。对于相交的情况也是一样的。

所以我们考虑，将原序列先全用覆盖操作，变成形如若干段与 $t$ 串相反和与 $t$ 串相同的串交替拼接的串。比如如果 $t = \{0, 0, 0, \cdots , 0\}$，可以先用覆盖把 $s$ 变成 $\{0, 0, 0, \cdots , 0, 1, 1, 1, \cdots, 0, 0, 0, \cdots\}$ 的形式，再用翻转操作，把 $1$ 都变成 $0$。当然这个例子举的不好。

由于翻转可以全在覆盖后做，我们不妨设 $f_{i, j, k}$，其中 $i \le n, j \in \{0, 1\}, k \in \{0, 1, 2\}$，表示已经考虑完了前 $i$ 个序列的覆盖操作，第 $i$ 个数和 $t_i$ 相同 $0$ 或相反 $1$，第 $i$ 个数被 $0$ 覆盖还是被 $1$ 覆盖还是没被覆盖 $2$。

分类讨论进行转移，这里的分类讨论就不细说了，大概就是如果 $i$ 被覆盖了，$j$ 也可以顺便接着覆盖而不需要代价，如果 $i$ 和 $t_i$ 相同而想让 $i + 1$ 和 $t_{i + 1}$ 相反就需要额外话翻转的代价等等。代码贴一下给大家参考吧，虽然考场上匆忙实现的有点丑。

```cpp
read(n);
scanf("%s", s + 1);
scanf("%s", t + 1);
memset(f, 0x3f, sizeof f);
f[0][0][2] = 0;
rop(i, 0, n) {
	if (s[i + 1] == t[i + 1]) {
		if (s[i + 1] == '0') {
			chkmin(f[i + 1][0][0], f[i][0][0]);
			rep(j, 0, 2) chkmin(f[i + 1][0][2], f[i][0][j]);
			chkmin(f[i + 1][0][0], f[i][1][0]);
			rep(j, 0, 2) chkmin(f[i + 1][0][2], f[i][1][j]);
			chkmin(f[i + 1][1][1], f[i][1][1]);
			chkmin(f[i + 1][1][1], f[i][1][0] + 1);
			chkmin(f[i + 1][1][1], f[i][1][2] + 1);
			chkmin(f[i + 1][1][1], f[i][0][1] + 1);
			chkmin(f[i + 1][1][1], f[i][0][0] + 2);
			chkmin(f[i + 1][1][1], f[i][0][2] + 2);
		} else if (s[i + 1] == '1') {
			chkmin(f[i + 1][0][1], f[i][0][1]);
			rep(j, 0, 2) chkmin(f[i + 1][0][2], f[i][0][j]);
			chkmin(f[i + 1][0][1], f[i][1][1]);
			rep(j, 0, 2) chkmin(f[i + 1][0][2], f[i][1][j]);
			chkmin(f[i + 1][1][0], f[i][1][0]);
			chkmin(f[i + 1][1][0], f[i][1][1] + 1);
			chkmin(f[i + 1][1][0], f[i][1][2] + 1);
			chkmin(f[i + 1][1][0], f[i][0][0] + 1);
			chkmin(f[i + 1][1][0], f[i][0][1] + 2);
			chkmin(f[i + 1][1][0], f[i][0][2] + 2);
		}
	} else {
		if (s[i + 1] == '0') {
			chkmin(f[i + 1][1][0], f[i][1][0]);
			rep(j, 0, 2) chkmin(f[i + 1][1][2], f[i][1][j]);
			chkmin(f[i + 1][1][0], f[i][0][0] + 1);
			rep(j, 0, 2) chkmin(f[i + 1][1][2], f[i][0][j] + 1);
			chkmin(f[i + 1][0][1], f[i][1][1]);
			chkmin(f[i + 1][0][1], f[i][1][0] + 1);
			chkmin(f[i + 1][0][1], f[i][1][2] + 1);
			chkmin(f[i + 1][0][1], f[i][0][1]);
			chkmin(f[i + 1][0][1], f[i][0][0] + 1);
			chkmin(f[i + 1][0][1], f[i][0][2] + 1);
		} else if (s[i + 1] == '1') {
			chkmin(f[i + 1][1][1], f[i][1][1]);
			rep(j, 0, 2) chkmin(f[i + 1][1][2], f[i][1][j]);
			chkmin(f[i + 1][1][1], f[i][0][1] + 1);
			rep(j, 0, 2) chkmin(f[i + 1][1][2], f[i][0][j] + 1);
			chkmin(f[i + 1][0][0], f[i][1][0]);
			chkmin(f[i + 1][0][0], f[i][1][1] + 1);
			chkmin(f[i + 1][0][0], f[i][1][2] + 1);
			chkmin(f[i + 1][0][0], f[i][0][0]);
			chkmin(f[i + 1][0][0], f[i][0][1] + 1);
			chkmin(f[i + 1][0][0], f[i][0][2] + 1);
		}
	}
} 
int ans = 0x3f3f3f3f;
rep(j, 0, 1) rep(k, 0, 2) chkmin(ans, f[n][j][k]);
printf("%lld\n", ans);
```

我真是分类讨论大师。

---

## 作者：shuqiang (赞：21)

这是一个简单的 DP。

考虑 6 个操作：
- 操作 $1$：不变。
- 操作 $2$：改为 $0$。
- 操作 $3$：改为 $1$。
- 操作 $4$：反转。
- 操作 $5$：先改为 $0$ 后反转。
- 操作 $6$：先改为 $1$ 后反转。

设 $f_{i,0/1/2/3/4/5}$ 表示第 $i$ 个数进行上述操作后把 $S$ 的前 $i$ 个数变成 $T$ 需要的最少次数，转移方程是简单的。

AC 代码:
```cpp
#include<iostream>
#include<string>

using namespace std;

const int N = 5 * 1e5 + 10, inf = 1e9;
int t, f[N][6];
//f[i][0/1/2/3/4/5]
string a, b;

int min6(int x1, int x2, int x3, int x4, int x5, int x6){
	return min(min(min(x1, x2), x3), min(min(x4, x5), x6));
}

int main(){
	cin >> t;
	while(t--){
		cin >> a >> b;
		f[0][0] = 0, f[0][1] = f[0][2] = f[0][3] = 1, f[0][4] = f[0][5] = 2;
		for(int i = 1; i <= a.size(); i++){
			int u0 = f[i-1][0], u1 = f[i-1][1], u2 = f[i-1][2], u3 = f[i-1][3], u4 = f[i-1][4], u5 = f[i-1][5];
			if(a[i-1] == b[i-1]) f[i][0] = min6(u0, u1, u2, u3, u4, u5), f[i][3] = inf;
			else f[i][0] = inf, f[i][3] = min6(u0+1, u1+1, u2+1, u3, u4, u5);
			
			if(b[i-1] == '0') f[i][1] = min6(u0+1, u1, u2+1, u3+1, u4, u5+1), f[i][2] = inf;
			else f[i][1] = inf, f[i][2] = min6(u0+1, u1+1, u2, u3+1, u4+1, u5);
			
			if(b[i-1] == '0') f[i][5] = min6(u0+2, u1+2, u2+1, u3+1, u4+1, u5), f[i][4] = inf;
			else f[i][5] = inf, f[i][4] = min6(u0+2, u1+1, u2+2, u3+1, u4, u5+1);
		}
		cout << min6(f[a.size()][0], f[a.size()][1], f[a.size()][2], f[a.size()][3], f[a.size()][4], f[a.size()][5]) << endl;
	}
    return 0;
}
```

---

## 作者：xyin (赞：18)

## 题目大意
给定 $01$ 串 $S$, $T$  ，每次操作可以对 $S$ 进行区间覆盖（~~覆盖为1或0~~）或区间取反，求把 $S$ 变为 $T$ 需要的最小操作数。
## 思路分析
观察题目性质，比较轻易能得到的是：取反操作的区间内部互不相交，覆盖操作的区间内部互不相交。

接下来就是考虑取反操作和覆盖操作之间有没有什么关系，我们发现：如果操作中存在两个**相邻**（~~指操作区间相邻~~）的操作是**先取反再覆盖**我们可以通过一定方法先覆盖再取反。

例如：如果这两个取反和覆盖操作的区间**不相交**，那么就可以直接交换顺序；如果这两个取反和覆盖的区间**相交**，那么就将取反操作的区间扩展到二者的并集，覆盖操作同样可以由取反操作替代。

所以我们就能 先通过覆盖操作 将 $S$ 串变成一个内部要么与 $T$ 串相同要么与 $T$ 串相反，再通过取反操作把它变得与 $T$ 串相同，于是我们的操作顺序就变成了**先覆盖再取反**的形式。

考虑 DP 枚举上一位的覆盖情况  $f_{i,k}$ ，表示考虑了前 $i$ 位,进行的覆盖操作为 $k$ ( $0$ 为用 $0$ 覆盖，$1$ 为用 $1$ 覆盖，$2$ 为不覆盖保持与 $T$ 串一样）时需要的最小操作数。

### 代码分析
* 初始化
```cpp
f[1][0] = 1 + ( t[1] == '1' );
f[1][1] = 1 + ( t[1] == '0' );
f[1][2] = ( s[1] != t[1] );
```

以 $f_{1,0}$ 为例：因为要用 $0$ 覆盖，所以我们要打一个覆盖标记，操作数 $+1$ ；如果对应的 $T$ 串位置为 $1$ 的话，我们需要覆盖后在这个位置取反，操作数 $+1$ 。
* DP 转移

同样以 $f_{i,0}$ 为例：
```cpp
if ( t[i] == '0' ) 
  f[i][0] = min( f[i - 1][0] , min( f[i - 1][1] + 1 , f[i - 1][2] + 1 ) )
  ```

当对应的 $T$ 串位置为 $0$ 时：此时 $T$ 串为 $0$ ，覆盖为 $0$ ，不用考虑取反操作。

1. 由 $f_{i-1,0}$ 转移：由于前面用 $0$ 覆盖时已经打过覆盖标记，所以操作数不变。

1. 由 $f_{i-1,1}$ 转移：由于前面的覆盖标记为 $1$ ，我们要重新用 $0$ 覆盖，需要再打一次 $0$ 的覆盖标记。

1. 由 $f_{i-1,2}$ 转移：由于前面没有覆盖标记，我们要重新用 $0$ 覆盖，需要再打一次 $0$ 的覆盖标记。

```cpp
else f[i][0] = min( f[i - 1][0] + ( t[i - 1] == '0' ) , min( f[i - 1][1] + (t[i - 1] == '1' ) + 1 , f[i - 1][2] + ( s[i - 1] == t[i - 1]) + 1 ) ) ;
```

否则（对应 $T$ 串位置为 $1$ 时）：此时 $T$ 串为 $1$ ，覆盖为 $0$，要考虑取反操作。

1. 由 $f_{i-1,0}$ 转移：

（1）前面的覆盖标记为 $0$，所以覆盖操作不变 ；

（2）如果前面的 $T$ 串位置为 $1$ （前面的覆盖也为 $0$ ），那么前面肯定有过取反操作，根据我们最后取反的思想，这个位置可以和前面的取反操作一起取反，取反操作不变；

（3）如果前面的 $T$ 串位置为 $0$ （前面的覆盖也为 $0$ ），那么此时就没办法和前面一起取反，此时取反操作 $+1$ ；

2. 由 $f_{i-1,1}$ 转移：

（1)前面的覆盖操作为 $0$ ，所以覆盖操作 $+1$ ;
 
（2）上面已经讨论的很清楚了，这里就只说一下取反操作 $+1$ 的情况：前面的 $T$ 串位置为 $1$ （前面的覆盖为 $1$ ），则前面没有取反操作，此时取反操作 $+1$ ；

3. 由 $f_{i-1,2}$ 转移：

（1）前面没有覆盖操作，所以覆盖操作 $+1$ ；

（2）（~~如果不清楚就参考上面 $f_{i-1,0}$ 的讨论~~）前面的 $T$ 串位置与 $S$ 串位置相等，则前面没有取反操作，此时取反操作 $+1$ ；

其余 $f_{i,1}$ 和 $f_{i,2}$ 的讨论这里就不赘述了，可以自己手推一下。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,f=1;char c=getchar();
	while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0'&&c<='9') {x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
const int maxn=1e6+10;
int T,len,f[maxn][3];
char s[maxn],t[maxn];
signed main()
{
	T=read();
	while (T--)
	{
		scanf("%s%s",s+1,t+1);
		len=strlen(s+1); 
		memset(f,0x3f,sizeof(f));
		f[1][0]=1+(t[1]=='1');
		f[1][1]=1+(t[1]=='0');
		f[1][2]=(s[1]!=t[1]);
		for (int i=2;i<=len;i++)
		{
			if (t[i]=='0') f[i][0]=min(f[i-1][0],min(f[i-1][1]+1,f[i-1][2]+1));
			else f[i][0]=min(f[i-1][0]+(t[i-1]=='0'),min(f[i-1][1]+(t[i-1]=='1')+1,f[i-1][2]+(s[i-1]==t[i-1])+1));
			  
			if (t[i]=='1')  f[i][1]=min(f[i-1][1],min(f[i-1][0]+1,f[i-1][2]+1));
			else f[i][1]=min(f[i-1][1]+(t[i-1]=='1'),min(f[i-1][0]+(t[i-1]=='0')+1,f[i-1][2]+(s[i-1]==t[i-1])+1));
			 
			if (s[i]==t[i]) f[i][2]=min(f[i-1][2],min(f[i-1][0],f[i-1][1]));
			else f[i][2]=min(f[i-1][2]+(s[i-1]==t[i-1]),min(f[i-1][0]+(t[i-1]=='0'),f[i-1][1]+(t[i-1]=='1')));
		}
		printf("%d\n",min(f[len][0],min(f[len][1],f[len][2])));
	}
	return 0;
}
```
第一次写题解，写的不好轻喷。

---

## 作者：_fairytale_ (赞：11)

由于我们的操作过于自由，考虑找到一种操作，使得其他操作都可以简化为它，用来方便考虑问题。

**下文的所有讨论都是简单的，建议读者看完引理尝试自己证明。**

引理 $1:$ 对于操作区间有交的先反转再推平操作，先推平再反转不劣于先反转再推平。

证明：

考虑“先反转再推平”方案中反转区间为 $S_1$，推平区间为 $S_2$，假设推平成 $1$（推 $0$ 是等价的），接下来分类讨论：

1. $S_2\subseteq S_1$，先把 $S_2$ 推平成 $0$，再反转 $S_1$。
2. 两个区间有交但不包含：设相交区间为 $S$，那么 $S_1\gets S_1\setminus S$，两区间无交。
3. $S_1\subseteq S_2$，相当于没反转，去掉反转操作即可。

引理 $2:$ 对于操作区间有交的两次推平操作，先推平再反转不劣于连续两次推平。

证明：

同样地，考虑第一次推平区间为 $S_1$，第二次推平区间为 $S_2$。

1. $S_2\subseteq S_1$，先推 $S_1$，再反转 $S_2$。
2. 两个区间有交但不包含：设相交区间为 $S$，那么 $S_1\gets S_1\setminus S$，两区间无交。
3. $S_1\subseteq S_2$，相当于第一次没推，去掉第一次操作即可。

不难发现，对于连续 $n$ 次有交的推平（不考虑情况 $2$），可以转化为长度 $\le n$ 的一段先推平一次再反转若干次的操作序列。

引理 $3:$ 存在一种最优方案，同一个位置最多被反转一次。

证明：

只需证明不会被反转两次，然后归纳证明即可。考虑第一次反转区间为 $S_1=[l_1,r_1]$，第二次反转区间为 $S_2=[l_2,r_2]$。

1. $S_2\subseteq S_1$，先反转 $[l_1,l_2-1]$，再反转 $[r_2+1,r_1]$。
2. 两个区间有交但不包含：设相交区间为 $S$，那么 $S_1\gets S_1\setminus S,S_2\gets S_2\setminus S$，两区间无交。
3. $S_1\subseteq S_2$，交换 $S_1,S_2$，变为情况 $1$。

因此，对于一个位置而言，覆盖它的操作最多只有一次推平和一次反转，且反转在推平之后。

接下来设 $f[i][0/1/2][0/1]$ 表示考虑前 $i$ 个位置，现在 不在推平 $/$ 在推 $0/$ 在推 $1$ 区间内，不在 $/$ 在反转区间内，使 $S_1\dots S_i$ 与 $T_1\dots T_i$ 相同的最小操作次数，转移方程是简单的。

---

## 作者：YingDragon_wjq (赞：9)

# [P10766 「CROI · R2」01-string](https://www.luogu.com.cn/problem/P10766)

~~看到只有12篇题解，本蒟蒻也要来水一发！~~

[前置知识：什么是 DP？](https://www.so.com/s?q=DP+C%2B%2B&src=srp&ssid=&fr=360se7_addr&sp=a8b&cp=022a2c0026&psid=9259459fc036ea4357792dd042ec1c2f)
## 题目大意

给你两个只由 $0$ 和 $1$ 组成的长度为 $n$ 的字符串 $S$、$T$，你可以对 $S$ 做以下操作：
- 选择一个区间，将区间内所有的字符覆盖成 $0$。
- 选择一个区间，将区间内所有的字符覆盖成 $1$。
- 选择一个区间，将区间内所有为 $1$ 的字符变成 $0$，为 $0$ 的字符变成 $1$。（相当于取反）

问：最少多少步才能将 $S$ 变成 $T$ ？

## 思路

由于 $n$ 太大了（ $n≤5×10^5$ ），所以用 DFS 肯定会爆 TLE ，又因为每一位上的状态比较好表示和转移，只需用前一位的状态更新，于是考虑 DP。

我们定义： $f_{i,j}$ 表示在第 $i$ 位是第 $j$ 种状态时，前 $i$ 位的最优解。

那么，就可以得到状态转移式：（注：具体解释见 AC 代码注释）

```cpp
if(b[i]=='0') f[i][0]=MIN(f[i-1][0],f[i-1][1]+1,f[i-1][2]+1);
else f[i][0]=MIN(f[i-1][0]+(b[i-1]=='0'),f[i-1][1]+(b[i-1]=='1')+1,f[i-1][2]+(a[i-1]==b[i-1])+1);
if(b[i]=='1') f[i][1]=MIN(f[i-1][1],f[i-1][0]+1,f[i-1][2]+1);
else f[i][1]=MIN(f[i-1][1]+(b[i-1]=='1'),f[i-1][0]+(b[i-1]=='0')+1,f[i-1][2]+(a[i-1]==b[i-1])+1);
if(b[i]==a[i]) f[i][2]=MIN(f[i-1][0],f[i-1][1],f[i-1][2]);
else f[i][2]=MIN(f[i-1][0]+(b[i-1]=='0'),f[i-1][1]+(b[i-1]=='1'),f[i-1][2]+(a[i-1]==b[i-1]));
```
求 MIN 函数:（方便使用）

```cpp

int MIN(int a,int b,int c){
	int minn=min(a,b);
	minn=min(minn,c);
	return minn;
}
```




------------------------------------------------------------

**下面就是大家最期待的 AC 代码了！**
## AC 代码
```cpp
#include<bits/stdc++.h>
#define N 500005
using namespace std;

string a,b;
int n,f[N][3],t;
//f数组为前i位的最优解。第i位的覆盖状态0，1，2分别表示：用0覆盖，用1覆盖，保持原样。

//求最小值函数
int MIN(int a,int b,int c){
	int minn=min(a,b);
	minn=min(minn,c);
	return minn;
}

int main()
{
	cin>>t;
	while(t--){
		cin>>a>>b;
		
		//初始化
		memset(f,0x3f,sizeof(f));
		f[0][0]=1+(b[0]!='0');
		f[0][1]=1+(b[0]!='1');
		f[0][2]=(a[0]!=b[0]);
		n=a.size();
		
		//代码主体
		for(int i=1;i<n;i++){
			
			if(b[i]=='0') f[i][0]=MIN(f[i-1][0],f[i-1][1]+1,f[i-1][2]+1);
			/*
			如果第i位需要变成0，那么就选f[i-1][0]、f[i-1][1]+1和f[i-1][2]+1之间的最小值。
			但是为什么f[i-1][1]和f[i-1][2]要加1呢？因为它们的状态不一样，所以需要消耗次数转移。
			*/
			else f[i][0]=MIN(f[i-1][0]+(b[i-1]=='0'),f[i-1][1]+(b[i-1]=='1')+1,f[i-1][2]+(a[i-1]==b[i-1])+1);
			/*
			因为b[i]不是0了，所以如果b[i-1]是0，那么翻转，并且答案加1；但是如果b[i-1]不是0，那么就是覆盖操作，
			那么之前就应该加过1了。
			至于后面的f[i-1][1]和f[i-1][2]都加1的原因刚才已经讲过了。
			*/
			
			if(b[i]=='1') f[i][1]=MIN(f[i-1][1],f[i-1][0]+1,f[i-1][2]+1);
			else f[i][1]=MIN(f[i-1][1]+(b[i-1]=='1'),f[i-1][0]+(b[i-1]=='0')+1,f[i-1][2]+(a[i-1]==b[i-1])+1);
			//这部分可以类比上面的注释。
			
			if(b[i]==a[i]) f[i][2]=MIN(f[i-1][0],f[i-1][1],f[i-1][2]);
			else f[i][2]=MIN(f[i-1][0]+(b[i-1]=='0'),f[i-1][1]+(b[i-1]=='1'),f[i-1][2]+(a[i-1]==b[i-1]));
			//这部分代码转移状态时没有加1，原因就是f[][2]表示的是不做操作。
		}
		cout<<MIN(f[n-1][0],f[n-1][1],f[n-1][2])<<endl;//求最优解
	}
	return 0;
}//借鉴了其他巨佬的题解，勿喷。
```
如果发现题解有任何错误，请找我私聊或评论，**欢迎大家找错！！！**

---

## 作者：incra (赞：8)

### Solution
简单 DP，不知道赛时过的人为什么这么少。

设 $f_{i,j=0/1,k=0/1/2}$，表示前 $i$ 个数，最后是否存在反转标记（$j=0$ 表示没有，$j=1$ 表示有），最后一个数是否使用了覆盖操作（$k=0$ 表示覆盖 $0$，$k=1$ 表示覆盖 $1$，$k=2$ 表示不覆盖）。

注意这个状态的定义是建立在先覆盖，后反转的基础上的。

那么 $f_{i,j,k}=\displaystyle\min_{j'\in[0,1],k'\in[0,2],且状态合法}\{f_{i-1,j',k'}+[j \neq j' \land j=1]+[k \neq k'\land k\neq 2]\}$。


### Code
代码自认为清新。
```
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#include <chrono>
#include <random>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
#define IOS ios :: sync_with_stdio (false),cin.tie (0),cout.tie (0)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
//int fastio = (IOS,0);
//#define puts(s) cout << s << endl
const int N = 500010,INF = 0x3f3f3f3f;
int n;
char s[N],t[N];
int a[N],b[N];
int f[N][2][3];
int main () {
	int T;
	scanf ("%d",&T);
	while (T--) {
		scanf ("%s%s",s + 1,t + 1);
		n = strlen (s + 1);
		for (int i = 1;i <= n;i++) {
			a[i] = s[i] - '0';
			b[i] = t[i] - '0';
			for (int j = 0;j < 2;j++) {
				for (int k = 0;k < 3;k++) f[i][j][k] = INF;
			}
		}
		for (int i = 0;i < 2;i++) {
			int num = a[1] ^ i;
			if (num == b[1]) f[1][i][2] = i;
			f[1][i][b[1]] = i + 1;
		}
		for (int i = 2;i <= n;i++) {
			for (int j1 = 0;j1 < 2;j1++) {
				for (int j2 = 0;j2 < 2;j2++) {
					for (int k1 = 0;k1 < 3;k1++) {
						for (int k2 = 0;k2 < 3;k2++) {
							int x = (k1 == 2 ? a[i - 1] : k1) ^ j1;
							int y = (k2 == 2 ? a[i] : k2) ^ j2;
							if (x != b[i - 1] || y != b[i]) continue;
							tomin (f[i][j2][k2],f[i - 1][j1][k1] + (j1 != j2 && j2 == 1) + (k1 != k2 && k2 != 2));
						}
					}
				}
			}
		}
		int ans = INF;
		for (int i = 0;i < 2;i++) {
			for (int j = 0;j < 3;j++) tomin (ans,f[n][i][j]);
		}
		printf ("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：fede (赞：6)

# 正文

## 分析

题目有三种操作，简单点说：

1. 区间 $\text{01}$ 翻转。

2. 区间全部变 $\text{0}$。

3. 区间全部变 $\text{1}$。

怎么理解呢，举个栗子。![](https://img.lanxixiaowu.com/data/attachment/forum/201807/31/101906pt8uf14ttmttfmdx.gif)

我们假设初始状态为 $\text{11011100}$，目标状态为 $\text{01101001}$。

我们可以这么操作：

![](https://cdn.luogu.com.cn/upload/image_hosting/1jm9cha7.png)

为了方便讲述，把第一种操作称之为翻转操作，把第二、三种统称为变化操作。

在这里，我们需要知道**两点**：

- **如果这一位已经进行过变化操作，那么后续的变化操作会让前面的变化操作无效**（这一位先变 $1$，后来又变 $0$，那么第一次变 $1$ 的操作就无效了）。

- **如果这一位已经进行过翻转操作，那么接下来的翻转操作会让前一次的翻转操作无效**（这一位翻转，后来又翻转，那么最终的结果就变成原来的样子，两次都无效）。

这是先进行翻转操作，再进行变化操作。能否先进性变化操作，再进行翻转操作呢？

当然可以！

还是以刚才的例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/4evgq2dt.png)

因此，我们知道：**翻转操作和变化操作的顺序并不影响答案。**

分析部分完毕，撒花✿✿ヽ(°▽°)ノ✿

## 思路

题目说：“你需要回答**最少**使用几次操作才能把 $S$ 变成 $T$ 。”

关注“最少”二字，可以想到**动态规划**。

显然二维即可。

我们定义二维数组 $dp[6\times10^5][3]$，其中：

- $dp_{i,0}$ 表示前 $i$ 位在第 $i$ 位变 $\text{0}$ 需要的最小操作数；

- $dp_{i,1}$ 表示前 $i$ 位在第 $i$ 位变 $\text{1}$ 需要的最小操作数；

- $dp_{i,2}$ 表示前 $i$ 位在第 $i$ 位不变需要的最小操作数。

这里只考虑了变化操作，翻转操作呢？

以刚才的例子，我们来模拟一下动态规划的流程：

初始状态：$\text{11011100}$

目标状态：$\text{01101001}$

$dp_{1,0}$ 需变 $\text{0}$，无需翻转，无需继承，截止目前操作数为 $1$。

$dp_{1,1}$ 需变 $\text{1}$，需翻转，无需继承，截止目前操作数为 $2$。

$dp_{1,2}$ 不操作，需翻转，无需继承，截止目前操作数为 $1$。

$dp_{2,0}$ 需变 $\text{0}$，需翻转，需继承，截止目前操作数为 $2$。

$dp_{2,1}$ 需变 $\text{1}$，无需翻转，需继承，截止目前操作数为 $2$。

$dp_{2,2}$ 不操作，无需翻转，需继承，截止目前操作数为 $1$。

……

$dp_{8,0}$ 需变 $\text{0}$，需翻转，需继承，截止目前操作数为 $4$。

$dp_{8,1}$ 需变 $\text{1}$，无需翻转，需继承，截止目前操作数为 $4$。

$dp_{8,2}$ 不操作，需翻转，需继承，截止目前操作数为 $4$。

因此，我们在考虑变化操作时，就将翻转操作考虑进去了。

思路部分完毕，撒花✿✿ヽ(°▽°)ノ✿

## 代码

其实还有一个重要的点，不管怎么样，$dp$中变$\text{0}$操作和变$\text{1}$操作都要进行，不会因为原本是$\text{0}$就不进行变$\text{0}$操作了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=1e6+10;
int dp[N][3];
int min3(int x,int y,int z){
	return min(x,min(y,z));
}
void solve(){
	memset(dp,0,sizeof(dp));
	string a,b;
	cin>>a>>b;
	int n=a.size();
	a=' '+a;
	b=' '+b; 
	dp[1][0]=(b[1]!='0')+1;																							//初始化 ，怎样都要变 0，因此+1 
	dp[1][1]=(b[1]!='1')+1;																							//初始化 ，怎样都要变 1，因此+1 
	dp[1][2]=(b[1]!=a[1]);																							//初始化 
	for(int i=2;i<=n;i++){
		if(b[i]=='0'){																								//变 0 
			dp[i][0]=min3(dp[i-1][0],				dp[i-1][1]+1,				dp[i-1][2]+1					);	//不翻转的可能 
		}else{
			dp[i][0]=min3(dp[i-1][0]+(b[i-1]=='0'),	dp[i-1][1]+(b[i-1]=='1')+1,	dp[i-1][2]+(a[i-1]==b[i-1])+1	);	//  翻转的可能 
		}
		if(b[i]=='1'){																								//变 1 
			dp[i][1]=min3(dp[i-1][1],				dp[i-1][0]+1,				dp[i-1][2]+1					);	//不翻转的可能 
		}else{
			dp[i][1]=min3(dp[i-1][1]+(b[i-1]=='1'),	dp[i-1][0]+(b[i-1]=='0')+1,	dp[i-1][2]+(a[i-1]==b[i-1])+1	);	//	翻转的可能 
		}
		if(a[i]==b[i]){																								//不变 
			dp[i][2]=min3(dp[i-1][0],				dp[i-1][1],					dp[i-1][2]);						//不翻转的可能 
		}else{
			dp[i][2]=min3(dp[i-1][0]+(b[i-1]=='0'),	dp[i-1][1]+(b[i-1]=='1'),	dp[i-1][2]+(a[i-1]==b[i-1])		);	//  翻转的可能 
		}
	}
//	for(int i=0;i<=2;i++){
//		for(int j=1;j<=n;j++){
//			cout<<dp[j][i]<<' ';
//		}
//		cout<<endl;
//	}
	cout<<min3(dp[n][0],dp[n][1],dp[n][2])<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

我们还可以做些优化，让空间复杂度变得更优。

因为已经足以通过本题，不再做过多阐述。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=1e6+10;
int dp[2][3];				//空间变成O(1)了！！
int min3(int x,int y,int z){
	return min(x,min(y,z));
}
void solve(){
	memset(dp,0,sizeof(dp));
	string a,b;	
	cin>>a>>b;
	int n=a.size();
	a=' '+a;
	b=' '+b; 
	dp[0][0]=(b[1]!='0')+1;																							//初始化 ，怎样都要变 0，因此+1 
	dp[0][1]=(b[1]!='1')+1;																							//初始化 ，怎样都要变 1，因此+1 
	dp[0][2]=(b[1]!=a[1]);																							//初始化 
	for(int i=2;i<=n;i++){
		if(b[i]=='0'){																								//变 0 
			dp[1][0]=min3(dp[0][0],					dp[0][1]+1,					dp[0][2]+1					);	//不翻转的可能 
		}else{
			dp[1][0]=min3(dp[0][0]+(b[i-1]=='0'),	dp[0][1]+(b[i-1]=='1')+1,	dp[0][2]+(a[i-1]==b[i-1])+1	);	//  翻转的可能 
		}
		if(b[i]=='1'){																								//变 1 
			dp[1][1]=min3(dp[0][1],					dp[0][0]+1,					dp[0][2]+1					);	//不翻转的可能 
		}else{
			dp[1][1]=min3(dp[0][1]+(b[i-1]=='1'),	dp[0][0]+(b[i-1]=='0')+1,	dp[0][2]+(a[i-1]==b[i-1])+1	);	//	翻转的可能 
		}
		if(a[i]==b[i]){																								//不变 
			dp[1][2]=min3(dp[0][0],					dp[0][1],					dp[0][2]);						//不翻转的可能 
		}else{
			dp[1][2]=min3(dp[0][0]+(b[i-1]=='0'),	dp[0][1]+(b[i-1]=='1'),		dp[0][2]+(a[i-1]==b[i-1])		);	//  翻转的可能 
		}
		dp[0][0]=dp[1][0];
		dp[0][1]=dp[1][1];
		dp[0][2]=dp[1][2];
	}
//	for(int i=0;i<=2;i++){
//		for(int j=1;j<=n;j++){
//			cout<<dp[j][i]<<' ';
//		}
//		cout<<endl;
//	}
	cout<<min3(dp[0][0],dp[0][1],dp[0][2])<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

时间复杂度 $O(n)$，空间复杂度 $O(n)$。

代码部分完毕，撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：dyc2022 (赞：5)

首先，我们可以得到一些显而易见的性质：

1. 一个位置不可能进行 $>1$ 次取反操作。
2. 一个区间推平之后，前面所有操作无效。

从而，我们能够得到一个推论：若两个操作区间是部分重合的，那么除非是先推平后反转，否则都是没用的。

原因显然，若有先后两次操作 $(l_1,r_1)$ 和 $(l_2,r_2)$ 满足 $r_1 > l_2$ 且第二次为推平操作，那么效果是和先 $(l_1,l_2-1)$ 再 $(l_2,r_2)$ 一致的。

由此，我们得出一个点只可能有以下五种状态：

1. 不操作。
2. 推平成 $0$。
3. 推平成 $1$。
4. 取反一次。
5. 推平成 $0$ 再取反成 $1$。
6. 推平成 $1$ 再取反成 $0$。

那么到这里为止我们就做完了。令 $f_{i,opt}$ 表示仅考虑长为 $i$ 的前缀，第 $i$ 个位置的操作种类为 $opt$ 的最优解。转移基本是显然的，就是考虑 $i$ 的操作能否和 $i-1$ 合并，分类讨论进行转移即可。

那么这题就做完了，代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define N 500006
using namespace std;
/* 0: 0 1: 1 2: ~ 3: 0 ~ 4: 1 ~ 5: */
char s[N],t[N];
int T,n,dp[N][6];
void chkmin(int &x,int y){x=x>y?y:x;}
main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%s%s",s+1,t+1),n=strlen(s+1);
		memset(dp,0x3f,sizeof(dp));
		dp[0][0]=dp[0][1]=dp[0][2]=1,dp[0][3]=dp[0][4]=2,dp[0][5]=0;
		for(int i=1;i<=n;i++)
		{
			if(s[i]==t[i])
			{
				int bas[]={0,0,0,0,0,0};
				for(int j=0;j<6;j++)chkmin(dp[i][5],bas[j]+dp[i-1][j]);
			}
			else
			{
				int bas[]={1,1,0,0,0,1};
				for(int j=0;j<6;j++)chkmin(dp[i][2],bas[j]+dp[i-1][j]);
			}
			if(t[i]=='0')
			{
				int bas[]={0,1,1,0,1,1};
				for(int j=0;j<6;j++)chkmin(dp[i][0],bas[j]+dp[i-1][j]);
				int bas2[]={2,1,1,1,0,2};
				for(int j=0;j<6;j++)chkmin(dp[i][4],bas2[j]+dp[i-1][j]);
			}
			else
			{
				int bas[]={1,0,1,1,0,1};
				for(int j=0;j<6;j++)chkmin(dp[i][1],bas[j]+dp[i-1][j]);
				int bas2[]={1,2,1,0,1,2};
				for(int j=0;j<6;j++)chkmin(dp[i][3],bas2[j]+dp[i-1][j]);
			}
		}
		int ans=1e15;
		for(int i=0;i<6;i++)chkmin(ans,dp[n][i]);
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：_O_v_O_ (赞：4)

写这种大分讨 dp 只要保持专注力就行了吧。

我们注意到一个区间最多被做 $2$ 次操作且操作最多为一次推平加一次取反。


---


证明：

若一个区间被做更多操作那么假如是连续的两次推平那么显然可以转化为一次推平一次取反。

如果连续两次取反那么等价于对两边的小区间取反，即假如要取反 $[l_1,r_1],[l_2,r_2](l_1\le l_2\le r_1\le r_2)$ 那么等价于 $[l_1,l_2],[r_1,r_2]$。

然后假如要做取反加推平等价于对推平的区间推平为另外一个数再做取反，即假如要对区间 $[l_1,r_1]$ 取反，再对 $[l_2,r_2]$ 推平为 $x$，那么等价于推平 $[l_2,r_2]$ 为 $x\oplus 1$ 再对 $[l_1,r_1]$ 取反。


---


那么我们就设 $dp_{i,0/1/2/3/4/5}$ 为这个位置做了以下操作后达成目标：

- 啥都没做
- 取反
- 推平为 $0$
- 推平为 $1$
- 推平为 $0$ 再取反
- 推平为 $1$ 再取反

那么转移就直接大力分讨就行了。


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e7+5;
string s,t;
int n,dp[N][7];
void solve(){
	cin>>n>>s>>t;n=s.size();s=' '+s,t=' '+t;
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0,dp[0][1]=dp[0][2]=dp[0][3]=1,dp[0][4]=dp[0][5]=2;
	for(int i=1;i<=n;i++){
		if(s[i]==t[i]){
			dp[i][0]=min({dp[i-1][0]+0,dp[i-1][1]+0,dp[i-1][2]+0,dp[i-1][3]+0,dp[i-1][4]+0,dp[i-1][5]+0});
		}
		else{
			dp[i][1]=min({dp[i-1][0]+1,dp[i-1][1]+0,dp[i-1][2]+1,dp[i-1][3]+1,dp[i-1][4]+0,dp[i-1][5]+0});
		}
		if(t[i]=='0'){
			dp[i][2]=min({dp[i-1][0]+1,dp[i-1][1]+1,dp[i-1][2]+0,dp[i-1][3]+1,dp[i-1][4]+0,dp[i-1][5]+1});
			dp[i][5]=min({dp[i-1][0]+2,dp[i-1][1]+1,dp[i-1][2]+2,dp[i-1][3]+1,dp[i-1][4]+1,dp[i-1][5]+0});
		}
		if(t[i]=='1'){
			dp[i][3]=min({dp[i-1][0]+1,dp[i-1][1]+1,dp[i-1][2]+1,dp[i-1][3]+0,dp[i-1][4]+1,dp[i-1][5]+0});
			dp[i][4]=min({dp[i-1][0]+2,dp[i-1][1]+1,dp[i-1][2]+1,dp[i-1][2]+2,dp[i-1][4]+0,dp[i-1][5]+1});
		}
	}
	cout<<min({dp[n][0],dp[n][1],dp[n][2],dp[n][3],dp[n][4],dp[n][5]})<<endl;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T=1;while(T--) solve();
	return 0;
}
```

---

## 作者：wizardMarshall (赞：4)

回溯一下考场的思路。

由于操作间有先后顺序，从左到右转移不可以直接用布尔状态记录操作。考虑 16 个状态的大力动态规划。即截至第 $i$ 个点，有：

1. 只有覆盖 $0$ 操作
2. 只有覆盖 $1$ 操作
3. 只有取反操作
4. 先覆盖 $0$ 再取反操作
5. 先覆盖 $1$ 再取反操作
6. ……

等等。转移到下一个时判断一下哪些操作终止了，哪些操作新加了（加代价）。可做但麻烦，而且状态太多时间不足。

之后又有一个性质：翻转区间之间互不相交（对于相交的部分负负得正，不如不做），而且覆盖区间之间互不相交（相交的部分只需要做时间靠后的操作即可）。这样可以去掉所有上述含有 3 个操作的状态。

考场思路到这里截止。代码：

```c++
#include <bits/stdc++.h>
using namespace std;

bool s[500005], t[500005];
int dp[500005][10];
/*
0.（截至目前）无操作
1.覆盖0（下简称0）
2.覆盖1（下简称1）
3.取反（下简称01）
4.0后01
5.1后01
6.01后0
7.01后1
8.0后1
9.1后0

*/
inline char check(bool s, short op) {//字符s经过状态op操作后的结果
	if (op == 0) {
		return s;
	}
	if (op == 1 || op == 5 || op == 6 || op == 9) {
		return 0;
	}
	if (op == 2 || op == 4 || op == 7 || op == 8) {
		return 1;
	}
	if (op == 3) {
		return !s;
	}
}
inline short cnt(short op) {//状态op的操作个数
	if (op == 0)return 0;
	if (op <= 3)return 1;
	return 2;
}
inline short change(short op1, short op2) {//从op1变到op2，变化的个数（代价）
	if (op1 == 0) {
		return cnt(op2);//全是新增
	}
	if (op2 == 0 || op1 == op2) {//全无，或全等
		return 0;
	}
	bool v1 = (op1 == 1 || op1 == 4 || op1 == 6 || op1 == 8 || op1 == 9),
	v2 = (op1 == 2 || op1 == 5 || op1 == 7 || op1 == 8 || op1 == 9),
	v3 = (op1 == 3 || op1 == 4 || op1 == 5 || op1 == 6 || op1 == 7);
	
	bool v4 = (op2 == 1 || op2 == 4 || op2 == 6 || op2 == 8 || op2 == 9),
	v5 = (op2 == 2 || op2 == 5 || op2 == 7 || op2 == 8 || op2 == 9),
	v6 = (op2 == 3 || op2 == 4 || op2 == 5 || op2 == 6 || op2 == 7);
	return (v1 != v4 && v4 == 1) + (v2 != v5 && v5 == 1) + (v3 != v6 && v6 == 1);//变化的（并且是原来没有现在有的操作）
}
signed main() {
	short T;
	cin >> T;
	while (T--) {
		char ch = getchar();
		while (ch!= '0' && ch != '1') {
			ch = getchar();
		}int n = 0, tn = 0;
		while (ch == '0' || ch == '1') {
			s[++n] = ch - '0';
			ch = getchar();
		}
		while (ch!= '0' && ch != '1') {
			ch = getchar();
		}
		while (ch == '0' || ch == '1') {
			t[++tn] = ch - '0';
			ch = getchar();
		}
		int ans = 1e9;
		for (int i = 1; i <= n; i++) {
			if (i == 1) {//第一位，初始化操作
				for (short j = 0; j <= 9; j++) {
					if (check(s[i], j) == t[i]) {
						dp[i][j] = cnt(j);//全是新增
					}else dp[i][j] = 1e9;
				}
			}else {
				for (short j = 0; j <= 9; j++) {
					dp[i][j] = 1e9;
					if (check(s[i], j) == t[i]) {//保证操作过后符合ti状态
						for (short k = 0; k <= 9; k++) {//枚举第i-1位的状态
							dp[i][j] = min(dp[i][j], dp[i - 1][k] + change(k, j));//加上改变带来的代价
						}if (i == n) {//记录答案
							ans = min(ans, dp[i][j]);
						}
					}
				}
			}
		}printf("%d\n", ans);
	}
    return 0;
}
```

后注：

其实上述代码还可以再优化，由于覆盖操作间不重复，所以倒数两个操作可以舍去。

还有一个比较不容易发现的性质：覆盖操作都可以放在取反后进行（若先进行覆盖，再去反，则开始时覆盖相反的值可以达到同一个效果）。因此，先后顺序不同的状态都可以舍去。最终可以只剩 5 个状态。

---

## 作者：_Dolphin_ (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P10766)

## Solution

### Part 1

考虑增加一个操作：

- 操作 $1$：反转；
- 操作 $2$：不变；
- 操作 $3$：改为 $0$；
- 操作 $4$：改为 $1$。

设 $f(i,opt)$ 表示到第 $i$ 位且第 $i$ 位操作为 $opt$ 的最小操作数，其中 $opt\in\{1,2,3,4\}$。

那么就有：

$f(i,1)=\begin{cases}1&i=1,a_i\neq b_i\\\begin{aligned}\min\{&f(i-1,1),f(i-1,2)+1,\\&f(i-1,3)+1,f(i-1,4)+1\}\end{aligned}&2\leq i\leq n,a_i\neq b_i\\\infty&otherwise\end{cases}$

$f(i,2)=\begin{cases}0&i=1,a_i=b_i\\\begin{aligned}\min\{&f(i-1,1),f(i-1,2),\\&f(i-1,3),f(i-1,4)\}\end{aligned}&2\leq i\leq n,a_i=b_i\\\infty&otherwise\end{cases}$

$f(i,3)=\begin{cases}1&i=1,b_i=0\\\begin{aligned}\min\{&f(i-1,1)+1,f(i-1,2)+1,\\&f(i-1,3),f(i-1,4)+1\}\end{aligned}&2\leq i\leq n,b_i=0\\\infty&otherwise\end{cases}$

$f(i,3)=\begin{cases}1&i=1,b_i=1\\\begin{aligned}\min\{&f(i-1,1)+1,f(i-1,2)+1,\\&f(i-1,3)+1,f(i-1,4)\}\end{aligned}&2\leq i\leq n,b_i=1\\\infty&otherwise\end{cases}$

看上去没有问题是吧。

一交，哇，$10$ 分。

### Part 2

为什么会挂呢？因为每个点只执行一个操作不一定是最优的，而将操作的区间适当重叠可能会更优。

定义 $f(i,a,b,c)$ 表示到第 $i$ 位且第 $i$ 位反转/不反转，改为/不改为 $0$，改为/不改为 $1$ 的最小操作数，其中 $a,b,c\in\{0,1\}$，且 $b,c$ 不全为 $1$，改为 $0/1$ 的操作优先于反转的操作。

那么就有：

$f(i,1,0,0)=\begin{cases}1&i=1,a_i\not=b_i\\\begin{aligned}\min\{&f(i-1,1,0,0),f(i-1,0,0,0)+1,\\&f(i-1,0,1,0)+1,f(i-1,1,0,1),\\&f(i-1,0,0,1)+1,f(i-1,1,1,0)\}\end{aligned}&2\leq i\leq n,a_i\not=b_i\\\infty&otherwise\end{cases}$

$f(i,0,0,0)=\begin{cases}0&i=1,a_i=b_i\\\begin{aligned}\min\{&f(i-1,1,0,0),f(i-1,0,0,0),\\&f(i-1,0,1,0),f(i-1,1,0,1),\\&f(i-1,0,0,1),f(i-1,1,1,0)\}\end{aligned}&2\leq i\leq n,a_i=b_i\\\infty&otherwise\end{cases}$

$f(i,0,1,0)=\begin{cases}1&i=1,b_i=0\\\begin{aligned}\min\{&f(i-1,1,0,0)+1,f(i-1,0,0,0)+1,\\&f(i-1,0,1,0),f(i-1,1,0,1)+1,\\&f(i-1,0,0,1)+1,f(i-1,1,1,0)\}\end{aligned}&2\leq i\leq n,b_i=0\\\infty&otherwise\end{cases}$

$f(i,1,0,1)=\begin{cases}1&i=1,b_i=0\\\begin{aligned}\min\{&f(i-1,1,0,0)+1,f(i-1,0,0,0)+2,\\&f(i-1,0,1,0)+2,f(i-1,1,0,1),\\&f(i-1,0,0,1)+1,f(i-1,1,1,0)+1\}\end{aligned}&2\leq i\leq n,b_i=0\\\infty&otherwise\end{cases}$

$f(i,0,0,1)=\begin{cases}1&i=1,b_i=1\\\begin{aligned}\min\{&f(i-1,1,0,0)+1,f(i-1,0,0,0)+1,\\&f(i-1,0,1,0)+1,f(i-1,1,0,1),\\&f(i-1,0,0,1),f(i-1,1,1,0)+1\}\end{aligned}&2\leq i\leq n,b_i=1\\\infty&otherwise\end{cases}$

$f(i,1,0,1)=\begin{cases}1&i=1,b_i=1\\\begin{aligned}\min\{&f(i-1,1,0,0)+1,f(i-1,0,0,0)+2,\\&f(i-1,0,1,0)+1,f(i-1,1,0,1)+1,\\&f(i-1,0,0,1)+2,f(i-1,1,1,0)\}\end{aligned}&2\leq i\leq n,b_i=1\\\infty&otherwise\end{cases}$

好复杂啊……考场写的时候调了好久。

### Code(100 pts):

```cpp
#include<bits/stdc++.h>
#define afor(x,y,z) for(int x=y;x<=z;x++)
#define bfor(x,y,z) for(int x=y;x>=z;x--)
#define cfor(x,y) for(int x=head[y];x;x=nxt[x])
using namespace std;
typedef long long ll;
typedef const int cint;
cint N=5e5+10;
int t,f[N][2][2][2];
char a[N],b[N];
int main() {
	scanf("%d",&t);
	while(t--) {
		memset(f,0x3f,sizeof f);
		scanf("%s%s",a+1,b+1);
		int n=strlen(a+1);
		if(a[1]!=b[1]) f[1][1][0][0]=1;
		else f[1][0][0][0]=0;
		if(b[1]=='0') f[1][0][1][0]=1,f[1][1][0][1]=2;
		else f[1][0][0][1]=1,f[1][1][1][0]=2;
		afor(i,2,n) {
			if(a[i]!=b[i]) f[i][1][0][0]=min({f[i-1][1][0][0],f[i-1][0][0][0]+1,f[i-1][0][1][0]+1,
				f[i-1][1][0][1],f[i-1][0][0][1]+1,f[i-1][1][1][0]});
			else f[i][0][0][0]=min({f[i-1][1][0][0],f[i-1][0][0][0],f[i-1][0][1][0],
				f[i-1][1][0][1],f[i-1][0][0][1],f[i-1][1][1][0]});
			if(b[i]=='0') {
				f[i][0][1][0]=min({f[i-1][1][0][0]+1,f[i-1][0][0][0]+1,f[i-1][0][1][0],
					f[i-1][1][0][1]+1,f[i-1][0][0][1]+1,f[i-1][1][1][0]}),
				f[i][1][0][1]=min({f[i-1][1][0][0]+1,f[i-1][0][0][0]+2,f[i-1][0][1][0]+2,
					f[i-1][1][0][1],f[i-1][0][0][1]+1,f[i-1][1][1][0]+1});
			}
			else {
				f[i][0][0][1]=min({f[i-1][1][0][0]+1,f[i-1][0][0][0]+1,f[i-1][0][1][0]+1,
					f[i-1][1][0][1],f[i-1][0][0][1],f[i-1][1][1][0]+1});
				f[i][1][1][0]=min({f[i-1][1][0][0]+1,f[i-1][0][0][0]+2,f[i-1][0][1][0]+1,
					f[i-1][1][0][1]+1,f[i-1][0][0][1]+2,f[i-1][1][1][0]});
			}
		}
		printf("%d\n",min({f[n][1][0][0],f[n][0][0][0],f[n][0][1][0],
			f[n][1][0][1],f[n][0][0][1],f[n][1][1][0]}));
	}
	return 0;
}
```

---

## 作者：luxiaomao (赞：3)

## [P10766](https://www.luogu.com.cn/problem/P10766)
 
赛时写贪心但是只骗了十分嘤嘤嘤。听说重题了，赛后仔细研究了一下还是不难的。

## Solution

题意不难理解，我们可以理解为有区间覆盖和区间反转两种操作。

并且同一种操作之间是不会有交集的（比如：反转 $[1,3]$ 和 $[2,4]$ 等价于反转 $[1,1]$ 和 $[4,4]$，这样就没有交集了）

没有交集就可以进行动态规划了，但是还有一种存在交集的情况，就是区间覆盖和区间反转两种操作之间。

**如果先反转，再覆盖（这两个操作有交集），那就等价于先覆盖，再反转没被覆盖的部分**。这样，我们就把整个操作序列转化为先覆盖，再反转的形式，可以进行动态规划了。

我们记 $f_{i,0/1/2}$ 表示考虑到前 $i$ 位：

- $f_{i,0}$ 这一位被 $0$ 覆盖的最小操作数。

- $f_{i,1}$ 这一位被 $1$ 覆盖的最小操作数。

- $f_{i,2}$ 这一位不进行覆盖操作的最小操作数。

（注意这里是针对覆盖操作而言，还要再加上反转成为目标串的方案数，**比如 $f_{1,2}$ 也可能是 $1$，因为不覆盖，但是待会要反转，所以加上一**）

## Code

```cpp
#include<bits/stdc++.h>
#define N 1000005
using namespace std;

int n;
char s[N],t[N];
int f[N][3];

int main()
{
	scanf("%d%s%s",&n,s+1,t+1);
	memset(f,0x3f3f,sizeof f);
	f[1][0] = 1+(t[1]=='1');
	f[1][1] = 1+(t[1]=='0');
	f[1][2] = s[1]!=t[1];
	for(int i = 2;i <= n;i++)
		for(int j = 0;j <= 2;j++)
		for(int k = 0;k <= 2;k++)
		{
			int x = f[i-1][j];
			if(j != k && k != 2)x++;//这里算的是要不要新开一个覆盖操作
			char A = j==2?s[i-1]:(j+'0');
			char B = k==2?s[i]:(k+'0');
			if(t[i-1] == A && t[i] != B)x++;//这里算的是要不要新开一个反转操作
			f[i][k] = min(f[i][k],x);
		}
	printf("%d\n",min(min(f[n][0],f[n][1]),f[n][2]));
	return 0;
}
```

---

## 作者：ty_mxzhn (赞：2)

# 题意简述

你可以对 01 串做区间反转覆盖两种操作，让 $S$ 变成 $T$。求最小操作次数。

# 题解

注意到一些题目信息：

1. 假设我们反转的区间相交，那么我们可以把这两个区间变成不相交的情况。重复调整可以让任意两个反转的区间不交。
2. 假设我们覆盖的区间相交，也可以通过调整让任意两个覆盖的区间不交。
3. 假设我们在反转之后还有覆盖，那么不如直接覆盖后反转。所以我们的操作一定先覆盖再反转。

有点清晰了。假设我们已经制定了哪些位置要覆盖的方案，那么剩下的就是通过反转来达到目标的。

考虑 dp。考虑前 $i$ 个位置往后造成的贡献在哪里。无论如何这些贡献都只有两个留下来了。

设置 $f_{i,0/1/2,0/1}$ 表示先考虑前 $i$ 个位置已经匹配好了，覆盖成 0/ 覆盖成 1/ 没有覆盖，没有反转 / 有反转的向后贡献。

总结：问题转化为对不交区间染色后再 dp，贪心的排除掉了一些不优的情况以来减少 dp 状态。是一道不错的蓝或紫题。

---

## 作者：zjh111111 (赞：2)

来一篇代码简洁点的题解。

发现一定存在一种最优解使翻转区间不交，覆盖区间不交，翻转全在覆盖后进行。

考虑**线性 dp**。

$f_{i,0/1/2}$ 表示匹配前 $i$ 个字符，对第 $i$ 个字符的操作是覆盖成 $0/1$ 还是不变 $(2)$ 的最小代价。由于 $S_i$ 操作后要和 $T_i$ 相等，所以可以推出第 $i$ 个字符有没有取反操作。

转移时在每个操作的左端点计上次数。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <typename T>
inline void read(T &x) {
	int w = 1; x = 0; char c = getchar();
	while (!isdigit(c))
		(c == '-') && (w = -w), c = getchar();
	while (isdigit(c))
		x = (x << 1) + (x << 3) + (c ^ '0'), c = getchar();
}

const int N = 500005;
int Q, n, f[N][3];
char S[N], T[N];
inline int get_num(int x, int co) {
	return (co == 2) ? x : co;
}
signed main() {
	read(Q);
	while (Q -- > 0) {
		scanf("%s", S+1);
		scanf("%s", T+1);
		n = strlen(S+1);
		for (int i=0; i<=n; ++i) {
			for (int j=0; j<3; ++j) {
				f[i][j] = n;
			}
		}
		f[0][2] = 0;
		for (int i=1; i<=n; ++i) {
			for (int lst=0; lst<3; ++lst) {
				int sr = (i == 1) ? 0 : (get_num(S[i-1]-'0', lst) ^ (T[i-1]-'0')); //i-1 是否取反
				for (int now=0; now<3; ++now) {
					int tr = (get_num(S[i]-'0', now) ^ (T[i]-'0')); //i 是否取反
					f[i][now] = min(f[i][now], f[i-1][lst] + (now != 2 && lst != now) + (!sr && tr));
				}
			}
		}
		printf("%d\n", min(min(f[n][0], f[n][1]), f[n][2]));
	}
	return 0;
}
```

---

## 作者：NEKO_Daze (赞：2)

好久没练 DP 了，有点生疏。

洛谷题目传送门：[P10766](https://www.luogu.com.cn/problem/P10766)

## 简要题意

给出两个长度相同的 $01$ 串 $S,T$，可以对 $S$ 进行任意次下面三种操作，问最少多少次操作后 $S = T$。

1. 选择一个区间，将其中的 $0,1$ 反转；
2. 选择一个区间，将所有项改为 $0$；
2. 选择一个区间，将所有项改为 $1$；

## 思路

赛时千紫万红，第二天睡一觉才发现就是动态规划。

定义一个二维数组 `dp[500005][3]`，其中 $dp_{i,0}$ 代表前 $i$ 段里，第 $i$ 段的操作为全改 $0$，$dp_{i,1}$ 代表前 $i$ 段里，第 $i$ 段的操作为全改 $1$，$dp_{i,2}$ 代表前 $i$ 段里，第 $i$ 段不进行操作。显然满足最优子结构和无后效性，于是上 $dp$。

另外，本题[双倍经验](https://www.luogu.com.cn/problem/AT_joisc2019_h)。

```cpp
//By NEKO_Daze 2024-7-14 19:37
#include<bits/stdc++.h>
using namespace std;
int min3(int a, int b, int c) {return min(a, min(b, c));}
int t;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> t;
	while (t--)
	{
		string a, b;
		int dp[500005][3];
		memset(dp, 0, sizeof(dp));
		cin >> a >> b;
		int l = a.length();
		if (b[0] == '1') dp[1][0] = 2, dp[1][1] = 1;
		else dp[1][0] = 1, dp[1][1] = 2;
		if (a[0] == b[0]) dp[1][2] = 0;
		else dp[1][2] = 1;
		for(int i = 2;i <= l;i++) {
			if(b[i - 1] == '0') dp[i][0] = min3(dp[i - 1][0], dp[i - 1][1] + 1, dp[i - 1][2] + 1), dp[i][1] = min3(dp[i - 1][1] + (b[i - 2] == '1'), dp[i - 1][0] + (b[i - 2] == '0') + 1, dp[i - 1][2] + (b[i - 2] == a[i - 2]) + 1);
			else dp[i][0] = min3(dp[i - 1][0] + (b[i - 2] == '0'), dp[i - 1][1] + (b[i - 2] == '1') + 1, dp[i - 1][2] + (b[i - 2] == a[i - 2]) + 1), dp[i][1] = min3(dp[i - 1][1], dp[i - 1][0] + 1, dp[i - 1][2] + 1);
			if (a[i - 1] == b[i - 1]) dp[i][2] = min3(dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]);
			else dp[i][2] = min3(dp[i - 1][0] + (b[i - 2] == '0'), dp[i - 1][1] + (b[i - 2] == '1'), dp[i - 1][2] + (b[i - 2] == a[i - 2]));
		}
		printf("%d\n", min3(dp[l][0], dp[l][1], dp[l][2]));
	}
	return 0;
}
```

---

## 作者：Jorisy (赞：0)

由于区间推平对区间的影响非常大，所以一个点如果又被推平又被取反，一定是先被取反再被推平。

于是就有状态 $f_{i,[0,5]}$ 表示长度为 $i$ 的前缀，当前修改的类型为 $[0,5]$ 的最小修改次数。其中 $[0,5]$ 分别表示：
- 不修改；
- 推平为 $\tt 0$；
- 推平为 $\tt 1$；
- 取反；
- 取反后推平为 $\tt 0$；
- 取反后推平为 $\tt 1$。

方程是简单的，详见代码。
```cpp
#include<bits/stdc++.h>
#define fun(p0,p1,p2,p3,p4,p5) min({f[i-1][0]+p0,f[i-1][1]+p1,f[i-1][2]+p2,f[i-1][3]+p3,f[i-1][4]+p4,f[i-1][5]+p5})
using namespace std;

string s,t;
int n,f[500005][10];
/*
0: -
1: 0
2: 1
3: ~
4: 0 ~
5: 1 ~
*/
void sol()
{
	cin>>s>>t;
	n=s.size();
	s=' '+s;
	t=' '+t;
	f[0][0]=0;
	f[0][1]=f[0][2]=f[0][3]=1;
	f[0][4]=f[0][5]=2;
	for(int i=1;i<=n;i++)
	{
		if(s[i]==t[i])
		{
			f[i][0]=fun(0,0,0,0,0,0);
			f[i][3]=1e9;
		}
		else
		{
			f[i][0]=1e9;
			f[i][3]=fun(1,1,1,0,0,0);
		}
		if(t[i]=='0')
		{
			f[i][1]=fun(1,0,1,1,0,1);
			f[i][2]=1e9;
			f[i][4]=1e9;
			f[i][5]=fun(2,2,1,1,1,0);
		}
		else
		{
			f[i][1]=1e9;
			f[i][2]=fun(1,1,0,1,1,0);
			f[i][4]=fun(2,1,2,1,0,1);
			f[i][5]=1e9;
		}
	}
	int ans=1e9;
	for(int i=0;i<6;i++) ans=min(ans,f[n][i]);
	cout<<ans<<endl;
}

int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--) sol();
	return 0;
}
```

---

## 作者：wei2013 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10766)
## 思路：
首先，同类操作区间一定不相交（分为覆盖和取反）。

然后，对于一个覆盖和一个取反操作显然是可以颠倒顺序的。

发现以上性质之后就可以开始考虑 dp 了。

状态定义：$dp_{i,j}$ 表示前 $i$ 个已符合且最后一次用了 $j$ 号操作的最小步数（$0,1,2$ 分别表示覆盖为 $0,1$ 和取反操作）。

状态转移方程：见代码。

答案：$\min{dp_{n,0},dp_{n,1},dp_{n,2}}$。

时间复杂度：$\mathcal{O(n)}$。
## code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=1e6+5;
int T,dp[MAXN][3];
char s[MAXN],t[MAXN];
signed main(){
	cin>>T;
	while(T--){
		cin>>s+1>>t+1;
		memset(dp,0x3f,sizeof(dp));
		dp[1][0]=(t[1]=='1')+1;
		dp[1][1]=(t[1]=='0')+1;
		dp[1][2]=(t[1]!=s[1]);
		int n=strlen(s+1);
		for(int i=2;i<=n;i++){
			if(t[i]=='0'){
				dp[i][0]=min(dp[i-1][0],min(dp[i-1][1]+1,dp[i-1][2]+1));
			}else{
				dp[i][0]=min(dp[i-1][0]+(t[i-1]=='0'),min(dp[i-1][1]+(t[i-1]=='1')+1,dp[i-1][2]+(t[i-1]==s[i-1])+1));
			}
			if(t[i]=='1'){
				dp[i][1]=min(dp[i-1][1],min(dp[i-1][0]+1,dp[i-1][2]+1));
			}else{
				dp[i][1]=min(dp[i-1][1]+(t[i-1]=='1'),min(dp[i-1][0]+(t[i-1]=='0')+1,dp[i-1][2]+(t[i-1]==s[i-1])+1));
			}
			if(t[i]==s[i]){
				dp[i][2]=min(dp[i-1][0],min(dp[i-1][1],dp[i-1][2]));
			}else{
				dp[i][2]=min(dp[i-1][0]+(t[i-1]=='0'),min(dp[i-1][1]+(t[i-1]=='1'),dp[i-1][2]+(t[i-1]==s[i-1])));
			}
		}
		cout<<min(dp[n][0],min(dp[n][1],dp[n][2]))<<endl;
	}
	return 0;
} 
```

---

## 作者：Tsuki091117 (赞：0)

很明显这是一道DP问题（[双倍经验](https://www.luogu.com.cn/problem/AT_joisc2019_h)）。

## 题意分析（来源于[赛后题解](https://www.luogu.com.cn/article/az8x551b)）

#### 我们可以发现以下几个性质。
- 先覆盖再翻转优于先翻转再覆盖。
- 先覆盖再翻转优于连续覆盖。
- 同一个位置，最多被翻转一次（~~翻转多次相当于白干~~）。
##### 证明见[赛后题解](https://www.luogu.com.cn/article/az8x551b)。

## 状态表示
- 首先定义一个数 $dp(i,j,k)$，$i$ 表示对第 $i$ 个字符进行操作，$j$ 表示是否覆盖，$k$ 表示是否翻转。
- 然后进行初始化，**除了 $dp(0，2，0)=0$，其余全部初始化成 $10^{7}$**，便于之后取最小值。
- 之后将输入的字符串转化成数字，便于取最小值，然后进行状态转移。
- 状态转移方程如下: 
$$dp(i,j,k)=\min(dp(i,j,k),ans)$$ 
- 注意：**状态转移前要判断当前字符翻转后是否能变成目标字符。**
- 最后在几种操作中取最小值即可。

# $Code$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int T;
int a[N],b[N];//将字符转化成数字 
int dp[N][3][2];//记录状态 
/*
dp[i][j][k]:<1>i表示对于第i个字符来说 
	    <2>j表示是否进行覆盖  0:覆盖0  1:覆盖1  2:不做处理  
	    <3>k表示是否进行反转 0代表翻转 1代表翻转 
*/  
char s1[N],s2[N]; 
signed main(){
	cin>>T;
	while(T--){
		scanf("%s%s",s1+1,s2+1);//输入字符串 
		int n=strlen(s1+1);//计算长度 
		for(int j=0;j<3;j++){
			for(int k=0;k<2;k++){
				dp[0][j][k]=1e7;//初始化 
			}
		}
		dp[0][2][0]=0;//不做处理时操作次数为0 
		for(int i=1;i<=n;i++){
			a[i]=s1[i]-'0';
			b[i]=s2[i]-'0';//转化 
			for(int j=0;j<3;j++){
				for(int k=0;k<2;k++){
					dp[i][j][k]=1e7;//初始化 
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=0;j<3;j++){
				for(int k=0;k<2;k++){
					for(int jj=0;jj<3;jj++){
						for(int kk=0;kk<2;kk++){
							if(jj==2&&(a[i]^kk)!=b[i]) continue;//看a[i]翻转后是否可以变为b[i] 
							if(jj!=2&&(jj^kk)!=b[i]) continue;//看jj翻转后是否可以变成b[i]; 
							int ans=dp[i-1][j][k];
							if(jj!=2&&jj!=j) ans++; //如果进行了覆盖且j!=jj，操作数++ 
							if(kk&&!k) ans++;//如果反转了，操作数++ 
							dp[i][jj][kk]=min(dp[i][jj][kk],ans);//取最小值 
						}
					}
				}
			}
		}
		int ans=1e7;
		for(int j=0;j<3;j++){
			for(int k=0;k<2;k++){
				ans=min(ans,dp[n][j][k]);//取最小值 
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

