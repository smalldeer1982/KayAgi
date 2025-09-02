# スタンプラリー 2 (Collecting Stamps 2)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2016ho/tasks/joi2016ho_b

JOI 商店街には大通りに沿って $ N $ 個の店があり，JOI 商店街の入口から出口に向かってそれぞれ $ 1,\ 2,\ \ldots,\ N $ の番号が付けられている．JOI 商店街は一方通行で，入口から出口方向へしか移動することはできない．

まちおこしのため，JOI 商店街でスタンプラリーを行うことになった．このスタンプラリーでは，それぞれの店は `J`，`O`，`I` のいずれかのスタンプを用意し，店で買い物をした人はスタンプカードにスタンプを押してもらう．スタンプラリーに参加する人はちょうど $ 3 $ つの店に入る．商店街の入口では $ 3 $ つの欄のあるスタンプカードを配り，$ 1 $ 回目に入った店，$ 2 $ 回目に入った店，$ 3 $ 回目に入った店のスタンプを押してもらう．商店街の出口でスタンプカードを回収し，押されたスタンプが先に入った店のものから順に `J`，`O`，`I` になっているとき，出口で商品券がもらえるキャンペーンを実施することになった．押されたスタンプの種類や順番が異なるときは商品券はもらえない．

すでに $ N $ 個のすべての店はどのスタンプを用意するか決めたが，新たに $ 1 $ つの店を JOI 商店街に出すことになり，新しく出店する場所と，その店が用意するスタンプを決めることになった．新しい店を出す場所は，店 $ i $ と店 $ i\ +\ 1 $ の間 ($ 1\ \leqq\ i\ \leqq\ N\ -\ 1 $)，入口と店 $ 1 $ の間，店 $ N $ と出口の間のいずれかから決める．また，新しい店のスタンプは `J`，`O`，`I` の 3 通りから決める．

商品券をもらえるような店の選び方の数が大きいほど，スタンプラリーが盛り上がると商店街は考えた．そこで，新しく出す店の場所と用意するスタンプを決めたときの，上記の店の選び方の数の最大値を求めたい．

## 说明/提示

### 課題

JOI 商店街のすでにある店が用意したスタンプの情報が与えられたとき，新しく出す店の場所と用意するスタンプを決めたときの，商品券をもらえるような店の選び方の数の最大値を求めるプログラムを作成せよ．

- - - - - -

### 制限

すべての入力データは以下の条件を満たす．

- $ 3\ \leqq\ N\ \leqq\ 100\,000 $．

### 小課題

#### 小課題 1 \[30 点\]

- $ N\ \leqq\ 200 $ を満たす．

#### 小課題 2 \[20 点\]

- $ N\ \leqq\ 3\,000 $ を満たす．

#### 小課題 3 \[50 点\]

追加の制限はない．

- - - - - -

### Sample Explanation 1

入力例 $ 1 $ では，店 $ 1 $ と店 $ 2 $ の間に，スタンプ `J` を用意する新しい店を出したとき，店が用意したスタンプを入口から順に並べると `JJOIOI` となる． このとき，商品券をもらえるような店の選び方は以下の $ 6 $ 通りである． - $ 1,\ 3,\ 4 $ 番目の店に行く． - $ 1,\ 3,\ 6 $ 番目の店に行く． - $ 1,\ 5,\ 6 $ 番目の店に行く． - $ 2,\ 3,\ 4 $ 番目の店に行く． - $ 2,\ 3,\ 6 $ 番目の店に行く． - $ 2,\ 5,\ 6 $ 番目の店に行く． 入力例 $ 1 $ において，商品券をもらえるような店の選び方が $ 7 $ 通り以上になることはない． - - - - - -

### Sample Explanation 2

\- - - - - -

### Sample Explanation 3

入力例 $ 3 $ では，入口と店 $ 1 $ の間にスタンプ `J` を用意する新しい店を出したとき，商品券をもらえるような店の選び方の数が最大となる．

## 样例 #1

### 输入

```
5
JOIOI```

### 输出

```
6```

## 样例 #2

### 输入

```
7
JJJOIII```

### 输出

```
18```

## 样例 #3

### 输入

```
4
OIIJ```

### 输出

```
2```

# 题解

## 作者：Listedzero (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_joi2016ho_b)

[原题链接](https://atcoder.jp/contests/joi2016ho/tasks/joi2016ho_b)

### 题目分析

本题中，笔者认为有两个需要注意的地方：

- **求子串数**

暴力并不难，如何快速求出才是难点。这里因为有三个字母，所以最简便的方法就是去遍历字符串中的 `O` 字符，再用排列组合的思想去统计，这基本上就是这一类题的核心。如下样例所示：

```cpp
6
JJOIII
```

在本样例中，统计每个 `O` 字符左右的 `J` 字符和 `I` 字符数量，相乘即可，因此用**前缀和**统计那两个字符的数量即可快速得到某个区间的数量。

每处 `O` 字符都这样处理，所得的数量累计即可。

- **求最大值**

核心思路有了，我们还需要考虑那三个字符放在什么地方是最优的，照样来看样例：

```cpp
11
IJJOIIJOIIJ
```

我们刚刚的思路是分别统计每个 `O` 字符左右的 `J` 字符和 `I` 字符数量再相乘。可见，当向后枚举字符 `O` 时，先前统计过的字符 `J` 还会被接着统计，那么如果我们想要使得新增字符 `J` 的时候有最优解，就需要让新添加的字符每一次都尽可能的被统计到，所以考虑将字符 `J` 放在首位。直观地来说，样例中末尾处的字符 `J` 正是因此而无用。

同理，我们处理字符 `I` 的最大值情况也是这样考虑，放在末尾即可。

不要忘了考虑放置字符 `O` 的情况。这种情况下，我们直接枚举它放在某个点后模拟，再取其中的最大值即可。

### 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,cnt;
int cj[N],ci[N],num[N];
int ans_j,ans_o,ans_i;
char s[N];
signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		cj[i]=cj[i-1]+(s[i]=='J');
		ci[i]=ci[i-1]+(s[i]=='I');
		if(s[i]=='O') num[++cnt]=i;//这里直接记录了一下O字符所在位置
	}
	int max_o=0;
	for(int i=1;i<=cnt;i++){
		int pos=num[i];
		ans_j+=(cj[pos]+1)*(ci[n]-ci[pos]);
		ans_o+=cj[pos]*(ci[n]-ci[pos]);
		ans_i+=cj[pos]*(ci[n]-ci[pos]+1);
	}
	for(int i=1;i<=n;i++)//枚举插入一个O字符的最大值
		max_o=max(max_o,cj[i]*(ci[n]-ci[i]));
	ans_o+=max_o;
	cout<<max(ans_j,max(ans_o,ans_i))<<'\n';
	return 0;
}
```

### 后记

[月赛的类似题目](https://www.luogu.com.cn/problem/P12246)

---

## 作者：miraculously (赞：2)

分析：

这题是求加入一个字符后，最多有几个 JOI 子序列。将 J 放在开头最优，I放在末尾最优，O 放在前面 J 的个数乘后面 I 的个数最大的位置最优，然后比较三者大小取最大就是答案。只要求出开始的个数，再加上新加的个数就可以了。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,sum1[100010],sum2[100010],f[100010][3],maxn,ans,ans1,ans2;
//sum1记录J的前缀和，sum2记录I的前缀和，ans1算J在开头的方案，ans2算I在末尾的方案。
char c[100010];
signed main()
{
	scanf("%lld%s",&n,c+1);
	for(int i=1;i<=n;i++)
	{
		sum1[i]=sum1[i-1]+(c[i]=='J');
		sum2[i]=sum2[i-1]+(c[i]=='I');
	}
	for(int i=1;i<=n;i++)
	{
		maxn=max(maxn,sum1[i]*(sum2[n]-sum2[i]));//枚举O在i位置的贡献
		if(c[i]=='O')
		ans+=sum1[i]*(sum2[n]-sum2[i]);//统计开始的方案数
	}
	ans1=ans;
	for(int i=1;i<=n;i++)
	if(c[i]=='O')
	ans1+=sum2[n]-sum2[i];
	ans2=ans;
	for(int i=1;i<=n;i++)
	if(c[i]=='O')
	ans2+=sum1[i];
	ans=max(ans1,max(ans2,ans+maxn));
	printf("%lld\n",ans);
}
```


---

## 作者：PCCP (赞：1)

唉，竞赛。唉，模拟赛。

## 思路

模拟赛这题出在最后一题，但是我最后只有 10 分钟想，所以只写了暴力，还写挂了，反而这题全场最简单。

很容易想到枚举的 $ O(n^3) $ 暴力，但是不足以过。

考虑优化。首先考虑修改前的贡献，发现目标字符串是固定的，只有三个字符。只要我们固定了中间的 O，就可以利用前缀和快速算出两边的 J 和 I 的数量。

要新增一个字符，对于 J 来说，放在开头是最优的；对于 O 来说，放在中间某个位置，使得左边 J 的数量与右边 I 的数量的乘积最大，枚举插入位置即可；对于 I 来说，放在最后最优。

时间复杂度 $ O(n) $。

## 代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<stack>
#include<list>
#include<set>
using namespace std;
typedef pair<int,int> PII;
const int N=1e5+10;
const int MOD=998244353;
int n,cnt[N][3];
long long ans,inc1=0,inc2=0,inc3=0;
string s;
signed main(){
//	freopen("data.in", "r", stdin);
//	freopen("my.out", "w", stdout);
	cin>>n>>s;
	for(int i=1;i<=n;i++){
		for(int j=0;j<3;j++){
			cnt[i][j]=cnt[i-1][j];
		}
		if(s[i-1]=='J'){
			++cnt[i][0];
		}
		else if(s[i-1]=='O'){
			++cnt[i][1];
		}
		else{
			++cnt[i][2];
		}
	}
	for(int i=1;i<=n;i++){
		if(s[i-1]=='O'){
			ans+=1ll*cnt[i][0]*(cnt[n][2]-cnt[i][2]);
			inc1+=cnt[n][2]-cnt[i][2];
			inc3+=cnt[i][0];
		}
		inc2=max(inc2,1ll*cnt[i][0]*(cnt[n][2]-cnt[i][2]));
	}
	printf("%lld\n",1ll*max({inc1,inc2,inc3})+ans);
}
```


---

## 作者：yanmingqian (赞：0)

显然，如果没有插入的这个数，我们可以直接前缀和维护 J 的个数，后缀和维护 I 的个数，对于每个 O，对答案的贡献就是前缀 J 的个数乘后缀 I 的个数。不难写出下面的代码：
```cpp
	s=" "+s;
	for(int i=1;i<=n;i++){
		t1[i]=t1[i-1]+(s[i]=='N');
	} 
	for(int i=n;i>=1;i--){
		t2[i]=t2[i+1]+(s[i]=='I');
	}
    long long ans=0;
    for(int i=1;i<=n;i++){
        if(s[i]=='O'){
            ans+=t1[i]*t2[i];
        }
    }
```

在此基础上，考虑如何求解答案。

有下面三种情况：

1. 插入 J：显然，在最前面位置插入是最优的。

2. 插入 I：显然，在最后面位置插入是最优的。

3. 插入 O：枚举每个插入点即可，统计方式同上面不插入时。

这样我们就可以过掉这个题了。

代码：

```cpp
#include<iostream>
using namespace std;
const int N=1e5+10; 
long long t1[N],t2[N];
int main(){
	int n;
	string s;
	cin>>n>>s;
	s=" "+s;
	for(int i=1;i<=n;i++){
		t1[i]=t1[i-1]+(s[i]=='J');
	} 
	for(int i=n;i>=1;i--){
		t2[i]=t2[i+1]+(s[i]=='I');
	}
	long long ans1=0,ans2=0,ans3=0,maxx=0;
	for(int i=1;i<=n;i++){
		if(s[i]=='O'){
			ans1+=(t1[i]+1)*t2[i];
			ans2+=t1[i]*(t2[i]+1);
        	ans3+=t1[i]*t2[i];
		}maxx=max(maxx,t1[i]*t2[i]);
	}  
	cout<<max(max(ans1,ans2),ans3+maxx);
	return 0;
}
```

后话：

[双倍经验](https://www.luogu.com.cn/problem/P1371)

因此，本题建议降黄。

---

## 作者：Proxima_Centauri (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/AT_joi2016ho_b)
# 题意
一个只包含  `J`、`O`、`I` 三种字符的串，在里面的任意一个位置，加入一个字符（当然是这三种字符之一），求最多可以形成多少个 `JOI` 的子序列。
# 分析
考虑讨论插入的是哪种字符。

1. 对于 `J`、`I`

我们拿 `J` 举例。注意到：如果要在原序列中插入一个 `J`，那么一定在序列的最左端插入贡献最大。

所以我们只需要枚举序列中的每一个 `O`，计算左边 `J` 的个数以及右边 `I` 的个数，根据乘法原理相乘即可。
```
if (s[i - 1] != 'O') continue; // i 是字符串中的位置
ansJ += 1ll * (Jleft[i] + 1) * Iright[i]; // 统计贡献
```
注意不要忘记给 `J` 的个数加 $1$。

`I` 同理，不再赘述。

2. 对于 `O`

这种情况就比较复杂了。

首先，我们需要计算原序列中的每个 `O` 对答案的贡献：
```
ansO += 1ll * Jleft[i] * Iright[i];
```
其次我们枚举每一个原序列的位置，考虑从哪个位置插入得到的贡献最大。
```
for (int i = 1; i < n; i++) // 把O插在第i个位置之后
	temp = max(temp, 1ll * Jleft[i] * Iright[i + 1]);
```
最后的答案记录就是三种情况取最大值，注意将 $ansO + temp$ 和其它两个答案进行比较。

至于上文中统计个数的方法已经在刚刚贴的代码中有所体现，使用前、后缀和维护即可。
# AC code
代码中的注释是校内测试上写的。

```
// 统计每个位置左边J，右边I的个数
// 枚举插入的是J,O,I中的哪一个
// 若J，则对于每个O，(左边J个数+1)*右边I个数求和，I同理 
// 若O，则求对于每个插入位置，左边J个数*右边I个数的最大值，再加上每个O左边J个数*右边I个数的和
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;
int Jleft[100010], Iright[100010];
int main()
{
//	freopen("stamp.in", "r", stdin);
//	freopen("stamp.out", "w", stdout);
	int n;
	scanf("%d", &n);
	string s;
	cin >> s;
	for (int i = 1; i <= n; i++) Jleft[i] = Jleft[i - 1] + (s[i - 1] == 'J');
	for (int i = n; i >= 1; i--) Iright[i] = Iright[i + 1] + (s[i - 1] == 'I');
	long long ansJ = 0, ansI = 0, ansO = 0;
	for (int i = 1; i <= n; i++)
	{
		if (s[i - 1] != 'O') continue;
		ansJ += 1ll * (Jleft[i] + 1) * Iright[i];
		ansI += 1ll * (Iright[i] + 1) * Jleft[i];
		ansO += 1ll * Jleft[i] * Iright[i];
	}
	long long temp = 0;
	for (int i = 1; i < n; i++) // 把O插在第i个位置之后
		temp = max(temp, 1ll * Jleft[i] * Iright[i + 1]);
	printf("%lld\n", max(max(ansJ, ansI), ansO + temp));
	return 0;
}  
```
# 总结
本题实际没有蓝的难度，建议评黄，思路很简单，代码实现细节也不算多，很适合我这样的蒟蒻食用捏。

---

## 作者：安舒阳 (赞：0)

对于这道题，我们先明确一个问题：我插入一个字母，一定不会使得答案变小。想要证明很显然：插入字母并不会破坏原有的子串。

我们想让答案变大，那么我们就应该让插入字母所带来的收益尽可能得大。

我们在一个位置中插入不同的字母，他们所带来的收益是大概率不同的，所以我们需要分字母来考虑：

- 对于字母 `J`，插入后，它会和它后面的已经形成的  $cnt_{OI}$ 个子串 `OI` 组成 $cnt_{OI}$ 个新的 `JOI`，故这样带来的收益就是 $cnt_{OI}$。
- 对于字母 `I`，插入后，它会和它前面的已经形成的  $cnt_{JO}$ 个子串 `JO` 组成 $cnt_{JO}$ 个新的 `JOI`，故这样带来的收益就是 $cnt_{JO}$。
- 对于字母 `O`，就稍微麻烦点了，但是也好理解——加入一个 `O` 之后，它前面的每一个字母 `J` 都会找上门来，让这个 `O` 来当做跳板去和它后面的字母 `I` 组成一组新的 `JOI`。所以这样的收入是插入的 `O` 左边的 `J` 的个数 $cnt_J$ 与它右边的 `I` 的个数 $cnt_i$ 的乘积 $cnt_j \times cnt_i$。

很显然地能发现：如果决定插入字母 `J`，那么把它放到最前（也就是第一位）的地方是最好的，因为这样可以雨露均沾地包含后面所有的 `OI`。对于字母 `I` 也是这样，只需要把它放到最后就好了。这样的情况下我们可以很轻松地计算出插入字母 `J` 和 `I` 的最大收益。

而对于字母 `O`，确实是没有什么好办法，枚举一下它可以插入的每一个位置就好了。

在看代码之前，请务必注意，对于 AtCoder 的题，你需要**在文末输出一个换行**，AtCoder 对换行敏感！

同时，还需要注意本题中 $n \leq 10^5$，最优情况下（即前三分之一都是 `J`，中间是 `O`，最后三分之一都是 `I`），会产生 $(\frac{n}{3})^3$ 个答案，需要长整型。


```cpp
#include<bits/stdc++.h>
#define int long long//其实这个写法不太好，但是写的时候最开始没注意，没办法就define一下吧
using namespace std;
const int N=100005;
int n;
string s;
signed main(){//上面define int long long了，所以这里就不用int了
	int n;
	string s;
	cin>>n>>s;//数据不大，用cin就用吧，问题不大
	const int lenth=s.size();

  //算一下不插入的时候基础就有多少
	int cntd=0,cnta=0,ans=0;
	for(int i=0;i<lenth;i++){
		if(s[i]=='J'){
			cntd++;
		}
		if(s[i]=='O'){
			cnta+=cntd;
		}
		if(s[i]=='I'){
			ans+=cnta;
		}
	}
	
	int d=0;//放一个的贡献 
	//如果放D，放到最左边一定最优
	//这时，D的贡献是左边的所有子串AI
	int cnti=0,cntai=0;
	for(int i=lenth-1;i>=0;i--){
		if(s[i]=='I'){
			cnti++;
		}
		if(s[i]=='O'){
			cntai+=cnti;
		}
	} 
	d=cntai;
	//如果放I，放到最右边一定最优 
	//这时，I的贡献是左边的所有子串DA，上面已经算过了
	d=max(d,cnta);
	//放A的时候，贡献是左边D的数量与右边I的数量的乘积
	//用前缀和稍微处理一下
	int cd[N],ci[N];//左边D的数量和右边I的数量 
	for(int i=0;i<lenth;i++){
		if(i!=0){
			cd[i]=cd[i-1];
		}else{
			cd[i]=0;
		}
		if(s[i]=='J'){
			cd[i]++;
		}
	}
	for(int i=lenth-1;i>=0;i--){
		if(i!=lenth-1){
			ci[i]=ci[i+1];
		}else{
			ci[i]=0;
		}
		if(s[i]=='I'){
			ci[i]++;
		}
	}
	//枚举A的位置 
	for(int i=0;i<lenth;i++){
		d=max(d,ci[i]*cd[i]);
	}
	cout<<ans+d<<endl;//一定要加换行！！！！！
	return 0;
}
```

搞定。

---

## 作者：SnowFlavour (赞：0)

# [T1 スタンプラリー 2 (Collecting Stamps 2) ](https://www.luogu.com.cn/problem/AT_joi2016ho_b)

1. 算出原来有多少个方式能够取到 `JOI` 
2. 枚举在字符串中间插入一个 `O` 是否比当时大。如果是，那么更新。
3. 检查在最前面插入 `J` 是否更优
3. 检查在最后面插入 `I` 是否更优

这种方法的时间复杂度是 $O(n)$。

## Code Here：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int ke1[100];
int ke2[100];
long long f1[N][4];
long long f2[N][4];
int main(){
	int n;
	string t;
	cin>>n;
	cin>>t;
	ke1['I']=1;
	ke1['O']=2;
	ke1['J']=3;
	ke2['J']=1;
	ke2['O']=2;
	ke2['I']=3;
	for(int i=n;i>0;i--){
		f1[i][1]=f1[i+1][1];
		f1[i][2]=f1[i+1][2];
		f1[i][3]=f1[i+1][3];
		if(t[i-1]=='I')f1[i][1]++;
		else f1[i][ke1[t[i-1]]]=f1[i+1][ke1[t[i-1]]]+f1[i][ke1[t[i-1]]-1];
	}
	for(int i=1;i<=n;i++){
		f2[i][1]=f2[i-1][1];
		f2[i][2]=f2[i-1][2];
		f2[i][3]=f2[i-1][3];
		if(t[i-1]=='J')f2[i][1]++;
		else f2[i][ke2[t[i-1]]]=f2[i-1][ke2[t[i-1]]]+f2[i][ke2[t[i-1]]-1];
	}
	long long ans=0,ori=f2[n][3];
	for(int i=1;i<n;i++){
		ans=max(ans,ori+f2[i][1]*f1[i+1][1]);
	}
	ans=max(ans,ori+f1[1][2]);
	ans=max(ans,ori+f2[n][2]);
	cout<<ans<<endl;
}
```

---

## 作者：banned_wanyb (赞：0)

## 思路

[AT_joi2016ho_b](https://www.luogu.com.cn/problem/AT_joi2016ho_b)

首先要求出初始的 `JOI` 的个数，用 `O` 去划分，然后用 `O` 前面的 `J` 个数乘 `O` 后面的 `I` 个数。

显然，如果放 `J` 放最前面一定最优，结合以上式子可以很快证明，这里就不展开了，同理 I 放最末尾，计算的时候就是如果遇到 `O`，就加上前面的 `J` 的个数和后面 `I` 的个数。

对于放 `O` 的情况只需要每个位置都计算一下前面 `J` 个数乘后面 `I` 个数取最大就行。

最后再在三种情况中取最大加上原始的。

我觉得很简单啊，建议降绿。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,len,s[100005][3];
long long ans, ans1, ans2, ans3;
string a;
int main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin >> n >> a;
	a = " " + a;
	for (int i = 1; i <= n; i++) {
		s[i][0] = s[i-1][0] + (a[i] == 'J');
		s[i][1] = s[i-1][1] + (a[i] == 'O');
		s[i][2] = s[i-1][2] + (a[i] == 'I');
	}
	for (int i = 1; i <= n; i++) {//原来的JOI个数 
		if (a[i] == 'O') {
			ans += 1ll*s[i][0] * (s[n][2] - s[i][2]);
		}
	} 
	//J放开头,I放尾
	for (int i = 1; i <= n; i++) {
		if (a[i] == 'O') {
			ans1 += s[n][2] - s[i][2];//加上后面的I
			ans3 += s[i][0];//加上前面的J
		}
		ans2 = max(ans2, 1ll*s[i][0]*(s[n][2] - s[i][2]));//处理O
	} 
	cout << max({ans1,ans2,ans3}) + ans << "\n";
	return 0;
} 


```


---

## 作者：LinuF (赞：0)

### [原题链接](https://www.luogu.com.cn/problem/AT_joi2016ho_b)



------------
~~一道简单算贡献的题目。~~

### 思路
考虑先统计不放入其他字符的情况，只用找到 $O$ 并统计   $O$ 左边的 $J$ 数量和右边的 $I$ 数量，然后相乘即可。

同理插入 $O$ 也是统计当前空位前面的 $J$ 数量和后面的 $I$ 数量然后相乘。

考虑插入 $J$ 的情况，根据贪心肯定是放在第一个空位能与后面组成最多。考虑统计出所有 $O$ 后面 $I$ 的个数，求和即可。
 
考虑插入 $I$ 的情况，肯定是放在最后一个空位，统计所有 $O$ 前面 $J$ 的个数求和即可。

把三种插入情况取一次最大值即可。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
template<typename types>
inline void read(types &x){
    x = 0; char c = getchar(); int f = 1;
    while (!isdigit(c)){ if (c == '-') f = -1; c = getchar(); }
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    x *= f; return;
}
inline void read(){}
template<typename types, typename... Args>
void read(types &x, Args&... args){
    read(x), read(args...);
    return;
}
template<typename types>
void write(types x){
    if (x < 0) putchar('-'), x = -x;
    types k = x / 10;
    if (k) write(k);
    putchar(x - k * 10 + '0');
    return;
}
const int N=2e5+5;
int pre[N],suf[N],suf2[N],pre2[N],n,res=0,ans=0;//J,I,OI,JO
char c[N];
void solve(){
    read(n);
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    for(int i=1;i<=n;i++){
        pre[i]=pre[i-1];
        if(c[i]=='J') pre[i]++;
    }

    for(int i=n;i>=1;i--){
        suf[i]=suf[i+1];
        if(c[i]=='I'){
            suf[i]++;
        } 
    }
    for(int i=1;i<=n;i++){
        pre2[i]=pre2[i-1];
        if(c[i]=='O'){
            ans+=pre[i]*suf[i];
            pre2[i]+=pre[i];
            res=max(res,pre2[i]);
        }
    }
    for(int i=n;i>=1;i--){
        suf2[i]=suf2[i+1];
        if(c[i]=='O'){
            suf2[i]+=suf[i];
            res=max(res,suf2[i]);
        }
    }
    for(int i=1;i<=n;i++){
        res=max(res,pre[i]*suf[i+1]);
    }
    write(res+ans);puts("");
}
signed main(){
#ifndef ONLINE_JUDGE
    freopen(".in","r",stdin);
#endif
    solve();
    return 0;
}
```


---

## 作者：Ninelife_Cat (赞：0)

### 题目大意：

给出一个长度为 $n$ 只包含 ```J```，```O```，```I``` 的字符串 $S$。

定义一个串 $T$ 是好的，当且仅当 $T$ 存在一个位置满足删去这个位置的字符后 $T$ 与 $S$ 相同。

定义一个串的美丽值为满足删去除这个子序列外的字符后得到的串是 ```JOI``` 的子序列个数。

求所有好的串的美丽值的最大值。

### 思路：

因为可以插入的字符只有 ```J```，```O```，```I``` 三个，所以直接暴力枚举字符串的每一个位置插入什么字符，取最大值就行了。

但是手玩一下就会发现字符 ```J``` 放在开头一定最优，字符 ```I``` 放在末尾一定最优，所以实际上只需要枚举字符 ```O``` 放置的位置即可。

时间复杂度 $O(n)$。

### 核心代码：

```cpp
#define int long long
const int N=1e5+10;
int n,ans,J[N],I[N],sum,cnt1,cnt2;//cnt1 是子序列 [J] 的个数,cnt2 是子序列 [JO] 的个数
string s;
signed main()
{
	fastcin;cin>>n>>s;s=' '+s;
	for(ri int i=1;i<=n;++i)
		if(s[i]=='J') ++cnt1;
			else if(s[i]=='O') cnt2+=cnt1;
				else if(s[i]=='I') sum+=cnt2;
	ans=sum+cnt2;//末尾放 I 的情况
	for(ri int i=1;i<=n;++i)
		J[i]=J[i-1]+(s[i]=='J'),I[i]=I[i-1]+(s[i]=='I');//预处理前缀和,便于后续计算
	for(ri int i=0;i<=n;++i)
		ans=max(ans,sum+J[i]*(I[n]-I[i]));//中间放 O 的情况
	cnt1=1;cnt2=sum=0;
	for(ri int i=1;i<=n;++i)
		if(s[i]=='J') ++cnt1;
			else if(s[i]=='O') cnt2+=cnt1;
				else if(s[i]=='I') sum+=cnt2;//开头放 J 的情况
	cout<<max(ans,sum);
	return 0;
}
```

---

