# [ABC236D] Dance

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc236/tasks/abc236_d

$ 1,\ 2,\ \ldots,\ 2N $ と番号づけられた $ 2N $ 人の人が舞踏会に参加します。 彼らは $ N $ 個の $ 2 $ 人組にわかれてダンスを踊ります。

$ 2 $ 人組を構成する人のうち、番号の小さい方の人が人 $ i $ 、番号の大きい方の人が人 $ j $ のとき、 その $ 2 $ 人組の「相性」は $ A_{i,\ j} $ です。  
 $ N $ 個の $ 2 $ 人組の相性がそれぞれ $ B_1,\ B_2,\ \ldots,\ B_N $ であるとき、 「舞踏会全体の楽しさ」はそれらのビットごとの排他的論理和である $ B_1\ \oplus\ B_2\ \oplus\ \cdots\ \oplus\ B_N $ です。

「 $ 2N $ 人の参加者が $ N $ 個の $ 2 $ 人組に分かれる方法」を自由に選べるとき、「舞踏会全体の楽しさ」としてあり得る最大値を出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 8 $
- $ 0\ \leq\ A_{i,\ j}\ <\ 2^{30} $
- 入力はすべて整数

### Sample Explanation 1

人 $ i $ と人 $ j $ からなる $ 2 $ 人組を $ \lbrace\ i,\ j\rbrace $ で表します。 $ 4 $ 人が $ 2 $ 個の $ 2 $ 人組にわかれる方法は下記の $ 3 $ 通りです。 - $ \lbrace\ 1,\ 2\rbrace,\ \lbrace\ 3,\ 4\rbrace $ という $ 2 $ 組にわかれる。 このとき、舞踏会全体の楽しさは $ A_{1,\ 2}\ \oplus\ A_{3,\ 4}\ =\ 4\ \oplus\ 2\ =\ 6 $ です。 - $ \lbrace\ 1,\ 3\rbrace,\ \lbrace\ 2,\ 4\rbrace $ という $ 2 $ 組にわかれる。 このとき、舞踏会全体の楽しさは $ A_{1,\ 3}\ \oplus\ A_{2,\ 4}\ =\ 0\ \oplus\ 3\ =\ 3 $ です。 - $ \lbrace\ 1,\ 4\rbrace,\ \lbrace\ 2,\ 3\rbrace $ という $ 2 $ 組にわかれる。 このとき、舞踏会全体の楽しさは $ A_{1,\ 4}\ \oplus\ A_{2,\ 3}\ =\ 1\ \oplus\ 5\ =\ 4 $ です。 よって、舞踏会全体の楽しさとしてあり得る最大値は $ 6 $ です。

### Sample Explanation 2

人 $ 1 $ と人 $ 2 $ からなる $ 2 $ 人組のみが作られ、このときの舞踏会全体の楽しさは $ 5 $ です。

## 样例 #1

### 输入

```
2
4 0 1
5 3
2```

### 输出

```
6```

## 样例 #2

### 输入

```
1
5```

### 输出

```
5```

## 样例 #3

### 输入

```
5
900606388 317329110 665451442 1045743214 260775845 726039763 57365372 741277060 944347467
369646735 642395945 599952146 86221147 523579390 591944369 911198494 695097136
138172503 571268336 111747377 595746631 934427285 840101927 757856472
655483844 580613112 445614713 607825444 252585196 725229185
827291247 105489451 58628521 1032791417 152042357
919691140 703307785 100772330 370415195
666350287 691977663 987658020
1039679956 218233643
70938785```

### 输出

```
1073289207```

# 题解

## 作者：DYYqwq (赞：11)

tj 出锅了，重新交一遍。

# 题意简述
有 $2n$ 个人，随意两两人一组，每一组给定权值，求所有全部组队后最大的所有组权值异或和。
# $\texttt{Solution}$
首先注意数据范围。

> $1 \leq n \leq 8$

我们考虑暴力查找所有组队可能。

那么这种配对问题用 dfs 是再好不过了。

考虑在 dfs 中放入两个参数，一个表示目前配对的人，一个表示目前算出的答案。

如果目前配对的人是 $2n$，那就说明已经配了 $n$ 对，就需要计算答案（就是取 $\max$）了。

除此以外，我们还需要加入一个 bool 数组，记录某些点配对过，某些点没有。

给出代码与详细注释辅助理解。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n , a[20][20] , vis[20] , ans; // vis[u] = 1 就是点 u 配对过，反之就是没有。 ans 是用来统计答案的（取max）
void dfs(int u , int sum) // u 是当前配对点，注意！u 点没有人与其配对！    sum 是目前异或和。
{
	if(u == 2 * n) // 所有点配对完毕!
	{
		ans = max(ans , sum); // 统计答案。取max。
		return;
	}
	if(vis[u]) // 发现其实 u 配对完毕了。
	{
		dfs(u + 1 , sum); // 配对资格顺延（
		return;
	}
	for(int i = u + 1 ; i <= 2 * n ; i ++) // 向后遍历，找到一个和 u 配对的数 i。
	{
		if(!vis[i]) // i 没有和别人配对，可以和 u 配对。
		{
			vis[i] = 1; // 标记上，配过对了。
			dfs(u + 1 , sum ^ a[u][i]); // 再为 u + 1 配对。异或和再异或上 (u , i) 配对的权值。
			vis[i] = 0; // i 的算完了，给其他数留机会，解除标记。
		}
	}
}
signed main()
{
	scanf("%lld" , &n);
	for(int i = 1 ; i < 2 * n ; i ++)
	{
		for(int j = i + 1 ; j <= 2 * n ; j ++)
			scanf("%lld" , &a[i][j]) , a[j][i] = a[i][j]; // 注意这里，i 和 j 的配对权值与 j 和 i 的配对权值是一样的。
	}
	dfs(1 , 0); // 第一个配对的是 1,此时异或和是 0。
	printf("%lld" , ans);
	return 0;
}
```

还有不懂的私信问我呀 qwq

---

## 作者：cjh20090318 (赞：2)

简单搜索题。

## 题意

将 $2N$ 个人两两分组，每两个人配对会有一个快乐值，求快乐值异或最大。

## 分析

观察数据范围 $N \le 8$，很容易想到搜索。

又因为 $2N \le 16$，所以直接枚举全排列不可行，需要做一点优化。

第 $i$ 个人和第 $j$ 个人配对产生的快乐值，与第 $j$ 个人和第 $i$ 个人配对产生的快乐值是一样的。所以不妨设 $i < j$，可以减少掉冗余的 $i>j$ 的状态。

然后做上面这个剪枝就行了。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>
using namespace std;
int n;
int a[20][20];
bool vis[20];//标记是否已经配对。
int ans=0;
void dfs(const int pos,const int w){
	if(pos>n){ans=max(ans,w);return;}//更新答案。
	if(vis[pos]){dfs(pos+1,w);return;}//当前如果已经配对，枚举下一个。
	vis[pos]=1;
	for(int i=pos+1;i<=n;i++)if(!vis[i]) vis[i]=1,dfs(pos+1,w^a[pos][i]),vis[i]=0;//寻找配对的伙伴。
	vis[pos]=0;//注意标记清零。
}
int main(){
	scanf("%d",&n),n<<=1;
	for(int i=1;i<n;i++)for(int j=i+1;j<=n;j++) scanf("%d",&a[i][j]);
	dfs(1,0),printf("%d\n",ans);
	return 0;
}
```

---

## 作者：PikachuQAQ (赞：1)

## Description
[Link](https://www.luogu.com.cn/problem/AT_abc236_d)

## Solution
搭配问题，考虑 dp，写到一半发现：

- $1 \leq N \leq 8$。

好啊，直接上 dfs，剪枝和记忆化都不要。

dfs 思路大致如下：

设 $x$ 为当前异或值，$i$ 为深度。

如果已经搜了 $2N$ 次，答案取 $x$ 和答案的最大值。

又如果 $i$，也就是这个人已经配对过了，$x$ 直接和下一个配对。

否则遍历还没有配对的人，用还没有配对的人和 $x$ 配对。

## Code
```cpp
// 2023/4/21 Accept__

#include <iostream>

using namespace std;

const int kMaxN = 114;

int n, a[kMaxN][kMaxN], ans = -1;
bool vis[kMaxN];

void dfs(int x, int i) {
	if (i == n * 2) {
		ans = max(x, ans);
	} else if (vis[i]) {
		dfs(x, i + 1);
	} else {
		for (int j = i + 1; j <= 2 * n; j++) {
			if (!vis[j]) {
				vis[j] = 1, dfs(x ^ a[i][j], i + 1), vis[j] = 0;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= 2 * n - 1; i++) {
		for (int j = i + 1; j <= 2 * n; j++) {
			cin >> a[i][j];
		}
	}
	dfs(0, 1);
	cout << ans << '\n';
	
	return 0; 
}
```


---

## 作者：do_it_tomorrow (赞：1)

[更好的阅读体验](https://doittomorrow.xyz/post/abc236d-dance-ti-jie/)
# 题目大意
有 $2n$ 个人，每第 $i$ 个人与第 $j$ 个人一组会产生 $a_{i,j}$ 的价值，求所有价值异或的最大值，其中 $1\le n \le 8$。
# 思路
因为 $n$ 的数据范围十分人性，所以可以使用 dfs 进行暴搜通过这道题目。

在函数中传入两个参数 $x$ 与 $s$ 分别表示现在正在选择的人与获得的价值。

当 $x=2\times n+1$ 时，说明前面的 $2\times n$ 个人已经全部访问完了，就应该储存答案接着返回了。

为了使选择的人不重复，应该使用 $vis$ 数组记录已经选择的人，避免重复选择。

要注意，在操作中 $x$ 这个人不光可以选择别人还可以被别人选择，所以应该有直接访问下一层的操作。

# AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100;
int n,a[N][N],ans;
bool vis[N];
void dfs(int x,int s){
	if(x==n+1){
		for(int i=1;i<=n;i++) if(!vis[i]) return ;
		ans=max(ans,s);
		return;
	}if(vis[x]){dfs(x+1,s);return;} //已经被前面的人选择过了
	vis[x]=1;
	for(int i=1;i<x;i++){
		if(!vis[i]){
			vis[i]=1;
			dfs(x+1,s^a[min(x,i)][max(x,i)]); //因为输入的时候 j 全部大于 i
			vis[i]=0;
		}
	}vis[x]=0,dfs(x+1,s); //给别人选择自己的机会
}
void solve(){
	cin>>n;
	n*=2;
	for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) cin>>a[i][j];
	dfs(1,0);
	cout<<ans<<endl;
}signed main(){
	int T=1;//cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

首先观察到 $ N $ 很小，考虑暴力 dfs。

一个很容易想到的 dfs 是枚举所有全排列，之后两两配对计算答案，这样做最差是 $ 16! $ 的枚举量，难以通过。

但注意到很多枚举是本质相同的，如 $ (1,2) $ 和 $ (2,1) $ 是完全一样的。

所以我们改变枚举策略，枚举第一个数的时候顺带枚举第二个数，枚举第二个数的时候保证其永远比第一个数大即可。

这样做看上去还是无法通过，但实际上由于枚举完一对之后这一对就不再可用，所以最差情况下 $ 15 \times 13 \times 11 \times 9 \times 7 \times 5 \times 3 \times 1 $ 的枚举量足以通过此题。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
int n,b[20];
long long a[20][20],an;
void dfs(int k,long long no)
{
	if(k == 2*n)
	{
		an = max(an,no);
		return;
	}
	if(b[k])
	{
		dfs(k+1,no);
		return;
	} 
	for(int j = k+1;j <= 2*n;j++)
	{
		if(!b[j])
		{
			b[j] = 1;
			dfs(k+1,no^a[k][j]);
			b[j] = 0;
		}
	}
}
int main()
{
	cin >> n;
	for(int i = 1;i < 2*n;i++)
		for(int j = i+1;j <= 2*n;j++) 
		    cin >>a[i][j];
	dfs(1,0);
	cout << an;
} 
```


---

