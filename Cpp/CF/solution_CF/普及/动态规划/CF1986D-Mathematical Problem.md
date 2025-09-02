# Mathematical Problem

## 题目描述

你有一个长度 $n > 1$ 的字符串 $s$，由数字 $0$ 到 $9$ 组成，你要将 $n - 2$ 个运算符（$+$ 或 $\times$）插入至 $s$ 中，形成一个合法的表达式。

很明显，任何一个运算符都不应插入在 $s_0$ 前或 $s_{n - 1}$ 后，因为这样构不成一个合法的表达式。还有一点：字符串中数字的位置不能变。

假设 $s = \tt 987009$，可以获得以下几种表达式：

- $ 9 \times 8 + 70 \times 0 + 9 = 81 $ 
- $ 98 \times 7 \times 0 + 0 \times 9 = 0 $
- $ 9 + 8 + 7 + 0 + 09 = 33 $  
表达式里的数被允许含有前导零，例子中的 $09$ 可以被转换为 $9$。

从该字符串中，无法获得以下几种表达式：
- $+ 9 \times 8 \times 70 + 09$（符号只能放在数字之间）
- $98 \times 70 + 0 + 9$（因为有 $6$ 个数字，所以必须正好有 $4$ 个符号）

## 样例 #1

### 输入

```
18
2
10
2
74
2
00
2
01
3
901
3
101
5
23311
6
987009
7
1111111
20
99999999999999999999
20
00000000000000000000
4
0212
18
057235283621345395
4
1112
20
19811678487321784121
4
1121
4
2221
3
011```

### 输出

```
10
74
0
1
9
1
19
0
11
261
0
0
0
12
93
12
24
0```

# 题解

## 作者：AqrDAD (赞：16)

~~$n\le20$ 这是 $O(n^2)$ ？NO!~~ 

非 DP 整体复杂度 $O(n)$ 可做！可以当成并不困难的规律题做。

## 思路分析：

首先我们要想到一些特殊情况（原因在代码注释中解释）：
1. $n=2$ 时直接输出原数；
1. $n=3$ 时，若第一位或第三位数为 0，则答案为 0；
3. $n>3$ 时，有 0 则答案为 0。

此题有一个显而易见的性质：**对于已知的一组数，除了 0 和 1 之外的数直接加和答案最小。**

证明：显然。其他题解中对于这一条已有很好的解释，这里不再多做叙述了，也可以自己手膜一下容易发现。

在想到这条性质后，那么我们需要做的就是分出一个二位数使答案最优，以下我们称要找的这个二位数为**最优二位数**。

按照容易想到的 $O(n^2)$ 做法，就是遍历出所有二位数，对每一个二位数，都求一遍 1 以为的数的加和，答案即为所有和的最小值。

那么我们能不能直接 $O(n)$ 找出最优二位数呢，再仔细分析一下，又发现以下性质：

（若两个二位数 $a,b$，有 $a$ 优于 $b$，则我们写成 $a>b$）于是有如下“优排列”（注意 11，21 等个位数为 1 的数的位置）

$ 12=13=14=15=16=17=18=19>11=22=...=29>21>...$ 
以此类推。（不含个位数为 0 的， 因为特殊情况中 0 已经考虑）即**十位数相同的所有二位数，个位数不为 1 的数要优于个位数为 1 的。**

为什么呢？我们假定将原数列除 1 之外的总和为 $sum$，找出最优二位数之后除 1 之外的总和为 $you$，最优二位数为 12 时，则 $you$ 相比于 $sum$ 增加了 $12-2=10$，（$sum$ 中只加了 2 ，而 $you$ 中加了 12，对于所有十位数为 1 的二位数，$you-sum$ 的值都为 10，而对于 11 ，$you-sum=11-0=11$ (因为 1 在 $sum$ 都不进行计算)。$11>10$，所以十位数相同时，个位数不为 1 的要优于个位数为 1 的。那么十位数为 2、个位数不为 1 时，$you-sum=18$，对于 21，$you-sum=20$，同理，便得出了上述“优排列”。

这样我们就可以 $O(n)$ 找出最优二位数了，之后直接计算即可。

处理的时候我们可以分别找出最小的各位为 1 的二位数和各位不为 1 的二位数，比较它们十位数即可。

## 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
 
const int N = 25;
 
int t, n, a[N];
 
int main(){
    // freopen("in.in", "r", stdin); freopen("out.out", "w", stdout);
    
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n); bool if_end = false;
        for(int i=1; i<=n; i++){
            scanf("%1d", &a[i]);
        }
 
        if(n == 2){ //n-2=0，即不需要添加运算符，直接输出
            int ans = 0;
            ans = a[1] * 10 + a[2];
            printf("%d\n", ans);
            continue;
        }
        if(n == 3){
            if(a[1] == 0 or a[3] == 0){//特判0
                puts("0");
                continue;
            }
            if(a[2] == 0){//n=3，只能有一个运算符，第二位数为0答案不为0
                if(a[1] == 1) printf("%d\n", a[3]);
                else if(a[3] == 1) printf("%d\n", a[1]);
                else printf("%d\n", a[1]+a[3]);
                continue;
            }
        }
 
        int sm = 2008, id = 0;//记个位数不为1的最小二位数及位置
        int _1 = 2008, id_1 = 0;//个位数为1的最小二位数及位置
        for(int i=1; i<=n; i++){
            if(n > 3 and a[i] == 0){ //有0，全部相乘便为0
                puts("0"); if_end = true; break;
            }

            int now = a[i-1] * 10 + a[i];
            if(i > 1 and a[i] == 1){
                if(_1 > now) _1 = now, id_1 = i;
            }
            if(i > 1 and a[i] != 1){
                if(sm > now) id = i, sm = now;
            }
        }
        if(if_end) continue;
 
        int y = sm - sm % 10;//y为个位数不为1的最小二位数的十位数
        if(_1 < y and _1) sm = _1, id = id_1;//此时最优二位数为最小的个位数为1的二位数
 
        int ans = sm;
        for(int i=1; i<=n; i++){ //1之外的加和
            if(i == id or i == id - 1 or a[i] == 1) continue;
            ans += a[i];
        }
 
        printf("%d\n", ans);
 
    }
 
    return 0;
}
```

---

## 作者：liuqichen121 (赞：8)

# CF1986D Mathematical Problem 题解

[题目连接](https://www.luogu.com.cn/problem/CF1986D)

本题并不是很难，有多种方法可供参考实现。 ~~（蒟蒻的第一篇题解，望支持）~~

## 题意

* 大致的题意可以简化为：
  * 将 $n$ 个数字其中相邻的两个拆分成 $1$ 个两位数，其他的每个数字相加或相乘，使答案更小。
* 发现数据量不是很大，数字个数只有 $20$，无论是循环还是数组都能开下。

## 贪心做法

### 思路

* 首先不考虑那一个两位数，我们先来讨论在每个个位数（为方便在下文将其称为“散数”）上处理的最优方式。

  * 当散数存在为 $0$ 时，将所有的数相乘，由于 $0$ 乘以任何数均为 $0$，即可使所有数相乘，表达式结果为 $0$，且当前最小。

    > 由于所有数均为非负数，且运算仅有 加、乘法 ，可以证明表达式的结果为非负数，因此没有比 $0$ 更小的结果。

  * 当散数为 $1$ 时，将其加入表达式的结果比将其乘入表达式的结果大 $1$，因此将 $1$ 乘入其相邻的数中为最优的结果。

  * 当散数为 $0$ 和 $1$ 之外的数时，可以证明，不会相加的情况不劣于相乘的情况。

    > 保证散数中没有 $0$ 时，设当前散数为 $x(x\ge2)$，前面散数的最优解为 $sum(sum\ge1)$，可以发现始终满足 $sum+x\ge sum\times x$

* 对于两位数的最优组合，我们可以提供一个“负担”的概念：

  * 负担：选择当前数作为两位数后增大的答案。
  * 用式子形象化的讲，则是 负担=两位数的值-作为散数时对答案造成的影响。
  * 挑出负担最小的数组成两位数，即使最优解。

* 另外地，还有一些特殊情况需要考察：

  * $n=2$ 时，数列本身就是一个两位数，**去掉前导零后**直接输出即可。
  * $n=3$ 时，将四种排列直接挑小的输出即可。

### code

```cpp
int main(){
    int t=read();
    while(t--){
        int n=read();
        scanf("%s",s+1);
        bool flag=false;
        for(int i=1;i<=n;i++){//判断散数中是否存在0
            if(s[i]=='0'){
                flag=true;
                break;
            }
        }
        if(flag){
            if(n==2)//判断特殊情况
            printf("%d\n",(s[1]-'0')*10+s[2]-'0');
            else if(n==3&&s[1]!='0'&&s[2]=='0'&&s[3]!='0')
            printf("%d\n",(s[1]=='1'||s[3]=='1')?(s[1]-'0')*(s[3]-'0'):(s[1]-'0')+(s[3]-'0'));
            else
            printf("0\n");
            continue;
        }
        int minn=110,p=-1;
        for(int i=1;i<n;i++){
            int x=0;//计算“负担”
            if(s[i]=='1')
            x+=10;
            else
            x+=(s[i]-'0')*9;
            if(s[i+1]=='1')
            x+=1;
            if(x<minn)
            minn=x,p=i;
        }
        int ans=0;//计算最终答案
        for(int i=1;i<=n;i++){
            if(i!=p){
                if(s[i]!='1'||i==p+1)
                ans+=s[i]-'0';
            }else{
                ans+=(s[i]-'0')*10;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

## dp 做法

### 思路

* 由于数据并不大，因此我们可以使用 dp 算法较为“暴力”地过掉此题。

  * 定义 $dp$ 数组：`dp[截至第i位][flag（前面是否存在两位数）]最小值`

  * 转移式为：

    $dp_{i,0}=\min(dp_{i-1,0}\times a_i,dp_{i-1,0}+a_i)$；

    $dp_{i,1}=\min(\min(dp_{i-1,1}\times a_i,dp_{i-1,1}+a_i),\min(dp_{i-2}\times a_{(i-1,i)},dp_{i-2}+a_{(i-1,i)}))$。

### code

```cpp
int main(){
    int t=read();
    while(t--){
        int n=read();
        scanf("%s",s+1);

        //特殊情况同贪心时
        if(n==2){
            printf("%d\n",(s[1]-'0')*10+s[2]-'0');
            continue;
        }else if(n==3){
            printf("%d\n",min(min((s[1]-'0')*10+s[2]-'0'+s[3]-'0',((s[1]-'0')*10+s[2]-'0')*(s[3]-'0')),min((s[2]-'0')*10+s[3]-'0'+s[1]-'0',((s[2]-'0')*10+s[3]-'0')*(s[1]-'0'))));
            continue;
        }

        dp[0][0]=1;//一定要注意dp的初始状态
        dp[1][0]=s[1]-'0';
        dp[1][1]=INF;

        for(int i=2;i<=n;i++){//按照方程转移
            dp[i][0]=min(dp[i-1][0]*(s[i]-'0'),dp[i-1][0]+(s[i]-'0'));
            dp[i][1]=min(min(dp[i-1][1]*(s[i]-'0'),dp[i-1][1]+(s[i]-'0')),min(dp[i-2][0]*((s[i-1]-'0')*10+s[i]-'0'),dp[i-2][0]+((s[i-1]-'0')*10+s[i]-'0')));
        }

        //最终的结果一定要存在一个两位数
        //因此答案一定是dp[n][1]
        printf("%d\n",dp[n][1]);
    }
    return 0;
}
```

---

## 作者：Pursuewind (赞：5)

首先可以发现一个性质：假设两个数字 $a$ 与 $b$ 相邻，如果：

- $a \le 1$ 或 $b \le 1$，往它们之间插入乘号更优。
- 否则插入加号。

然后我们可以发现，总有两个字符之间没有插入运算符，又看到 $n$ 很小，考虑暴力枚举没有运算符的位置，从而通过上面的性质解题。

注意特判一些情况：

- 如果 $n=2$，原样输出即可。
- 如果 $n=3$，且 $s_1$ 或 $s_3$ 等于 `0`，则答案是 $0$。
- 如果 $n>3$，且字符串 $s$ 中含有字符 `0`，则答案是 $0$。

其它的细节见代码，单次复杂度为 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
string s; 
void solve()
{
	cin >> n >> s;
	if (n == 2){
		cout << (s[0] - '0') * 10 + s[1] - '0' << "\n";
	}
	else if (n > 3 && s.find("0") != -1){
		cout << "0\n";
	}
	else if (n == 3 && (s[0] == '0' || s[2] == '0')){
		cout << "0\n";
	}
	else{
		int res = 1e18;
	    for (int i = 0; i < n - 1; i ++){
	        int ans = 0, lst = 1;
	        for (int j = 0; j < n; j ++){
	            int c = s[j] - '0';
	            if (j == i + 1){
	                continue;
	            }
	            if (j == i){ //找到断点
	                c = c * 10 + s[j + 1] - '0';
	            }
	            if (c == 1){ //字符为 1，跳过
	                continue;
	            }
	            if (lst != 1) ans += lst; //累加答案
	            lst = c;
	        }
			res = min(res, ans + lst);
	    }
	    cout << res << "\n";
	}
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while (t --) solve();
	return 0;
}
/*
311312
3*1+1*3+12 = 18
3+11+3*1+2 = 19

901
*/
```

---

## 作者：2huk (赞：4)

> - 给定一个长度为 $n$ 的数字串。你需要在 $n - 1$ 个空中选择 $n - 2$ 个空插入运算符 $+$ 或 $\times$。求表达式的最小值。
> - $t \le 10^4$，$n \le 20$。

显然 $\mathcal O(n)$ 枚举哪个空不放运算符。然后就可以得到总共的 $n - 1$ 个数字。

显然 DP。设 $f(i)$ 表示前 $i$ 个数字构成的表达式的最小值。转移可以枚举 $j$ 表示最后一个加号在 $[j - 1, j]$ 之间。即：
$$
f(i) = \min_{j=1}^{i} (f_{j-1} + \prod_{k=j}^i a_k)
$$

```cpp
int f[N];
int mul[N][N];

int calc() {
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	
	for (int i = 1; i < n; ++ i ) {
		int res = 1;
		for (int j = i; j < n; ++ j ) {
			res *= a[j];
			mul[i][j] = res;
		}
	}
	
	for (int i = 1; i < n; ++ i ) {
		for (int j = 1; j <= i; ++ j ) {
			f[i] = min(f[i], f[j - 1] + mul[j][i]);
		}
	}
	return f[n - 1];
}

int solve() {
	fin >> n;
	for (int i = 1; i <= n; ++ i ) cin >> s[i];
	
	int res = 1e18;
	for (int i = 1; i < n; ++ i ) {
		int cnt = 0;
		for (int j = 1; j <= n; ++ j )
			if (i == j) a[ ++ cnt] = (s[i] - '0') * 10 + (s[i + 1] - '0'), ++ j;
			else a[ ++ cnt] = s[j] - '0';
		
		res = min(res, calc());
	}
	
	return res;
}
```

---

## 作者：wloving (赞：4)

## 题目分析

题目已知目的为：求出算术表达式的最小结果。

该算术表达式只能使用加号以及乘号，且只有 $n-2$ 个符号。由符号的个数可以推出该算术表达式一定存在一个两位数，其他都是一位数。针对每个数字无非两种情况将该数字做加法或乘法，我们选取结果最小的。

我们设 $dp_{(i,0/1)}$ 为到第 $i$ 个位置结束时，表达式的未出现两位数/出现两位数的最小值。

对于 $dp_{(i,0)}$ 只能是第 $i$ 个元素是一位数，且前面的式子中不存在两位数，从乘法与加法选较小的。转移方程为：$dp_{(i,j)}=\max(dp_{(i-1,0)}+num,dp_{(i-1,0)}\times num)$。其实对于大于 $1$ 的数字来说，只要前面的值不是 $0$，必然是加法来得更小的。

对于 $dp_{(i,0)}$ 存在两种情况，一种是前面的式子中存在两位数，当前一定是一位数；一种是前面的式子中不存在两位数，当前是个两位数。转移方程为：$dp_{(i,1)}=\max(dp_{(i-1,1)}+num,dp_{(i-1,1)}\times  num,dp_{(i-2,0)}+num2,dp_{(i-2,0)}\times num2)$。

总体的时间复杂度为 $O(Tn)$。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int N = 1e5 + 5;
stack<i64> ans;
int dp[25][2];  // dp[结束位置][是否存在两位数]
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t, n;
  string s;
  cin >> t;
  while (t--) {
    cin >> n;
    cin >> s;
    dp[0][0] = s[0] - '0';
    dp[1][0] = min(dp[0][0] + s[1] - '0', dp[0][0] * (s[1] - '0'));
    dp[1][1] = (s[0] - '0') * 10 + s[1] - '0';
    for (int i = 2; i < n; i++) {
      int num = s[i] - '0';                           // s[i]对应的一位数
      int num2 = (s[i - 1] - '0') * 10 + s[i] - '0';  // s[i-1]与s[i]对应的两位数
      // 1.没有两位数
      dp[i][0] = min(dp[i - 1][0] + num, dp[i - 1][0] * num);
      // 2.存在两位数
      dp[i][1] = min(min(dp[i - 1][1] + num, dp[i - 1][1] * num),
                     min(dp[i - 2][0] + num2, dp[i - 2][0] * num2));
    }
    cout << dp[n - 1][1] << "\n";
  }
  return 0;
}
```

---

## 作者：GeXiaoWei (赞：2)

# CF1986D Mathematical Problem
## 解析
先看一下数据，$2≤n≤20$，似乎可以用 $O(n^2)$ 的时间处理每一组测试数据，但正解其实是 $O(n)$ 的。

设 $dp_{i,0/1}$ 表示到字符串 $s$ 前 $i$ 位时，表达式只有一位数与表达式还有两位数时的最小结果。

先看 $dp_{i,0}$，因为只有一位数，所以只能从 $i-1$ 的位置得来，不是乘一个数就是加一个数，得公式 $dp_{i,0}=\max(dp_{i−1,0}+a_{i},dp_{i−1,0}×a_{i})$。

再看 $dp_{i,1}$，因为要有两位数，所以可以从 $i-2$ 的位置配上两位数，或是 $i-1$ 的位置配一位数，得公式 
$dp_{i,1}=\max(dp_{i-1,1}+a_{i},dp_{i-1,1}\times a_{i},dp_{i-2,0}+a_{i-1}\times10+a_{i},dp_{i-2,0}\times(a_{i-1}\times10+a_{i}))$。

整个代码时间复杂度为 $O(Tn)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[25],dp[25][10];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%1d",&a[i]);
		dp[1][0]=a[1],dp[2][0]=min(a[1]+a[2],a[1]*a[2]),dp[2][1]=a[1]*10+a[2];
		for(int i=3;i<=n;i++){
			dp[i][0]=min(dp[i-1][0]+a[i],dp[i-1][0]*a[i]);
			dp[i][1]=min(min(dp[i-1][1]+a[i],dp[i-1][1]*a[i]),min(dp[i-2][0]+a[i-1]*10+a[i],dp[i-2][0]*(a[i-1]*10+a[i])));
		}
		printf("%d\n",dp[n][1]);
	}
	return 0;
} 
```

---

## 作者：Weekoder (赞：1)

要素：模拟，分类讨论。

### 形式化题意

给定一个长度为 $n(n\ge2)$ 的数字串，在字符串中插入**正好** $n-2$ 个运算符号（加法 $+$ 或乘法 $\times$）构成一个算式，求这个算式的最小值。也就是说，必须要从数字串中分离出一个长度为 $2$ 的单独数字，但这个数不一定是二位数，如 $01$。

### 思路

观察样例，我们明显可以得出答案为 $0$ 的情况：当 $n\ge4$ 并且数字串中有 $0$ 的时候，答案一定为 $0$。而 $n=3$ 时，则需要要求 $0$ 出现在两端中的一端，答案才为 $0$。$n=2$ 时，只有字符串为 $00$ 时，答案才为 $0$。事实上，当 $n=2$ 时，答案就是数字串本身，因为不会进行任何运算。

接着处理 $n=3$ 时的一般情况。假设数字串为 $abc$，则答案为 $ab\ c$ 和 $a\ bc$ 中的较小值。这里有一个结论：若 $a,b>1$，则有 $a+b<a\times b$。并不难证。如果分割成的两个数 $x,y$ 均大于 $1$，则答案为 $x+y$。否则，答案为 $x\times y$。我们可以将 $x,y$ 中等于 $1$ 的数设为 $0$，则答案依旧为 $x+y$，可以统一格式。注意，若 $x=y=1$，则答案为 $1$，不能输出 $0$。 

最后处理 $n\ge4$ 时的一般情况。由于要有一个数长度为 $2$，所以我们可以枚举这个数并暴力统计答案。这时候，数字串中一定没有 $0$。于是，我们累加所有不为 $1$ 的数字（数字为 $1$ 可以乘在一个数上），取最小值即为答案。

代码：

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 25;

int T, n, ans;

string s;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
	cin >> T;
	while (T --) {
		cin >> n >> s;
		bool flag = 0;
		int idmin = 25, idmax = -1, cnt = 0;
		s = '#' + s;
		for (int i = 1; i <= n; i++) if (s[i] == '0') {
			cnt++;
			flag = 1;
			idmin = min(idmin, i);
			idmax = max(idmax, i);
		}
		if (cnt == n || flag && n >= 4 || flag && n == 3 && (idmin == 1 || idmax == n)) {
			cout << "0\n";
			continue;
		}
		if (n == 2) {
			cout << (s[2] - '0') + (s[1] - '0') * 10 << "\n";
			continue;
		}
		if (n == 3) {
			int x = s[3] - '0', y = s[1] - '0', _x = (s[2] - '0') + (s[1] - '0') * 10, _y = (s[3] - '0') + (s[2] - '0') * 10;
			if (x == 1) x = 0;
			if (y == 1) y = 0;
			if (_x == 1 && x) _x = 0;
			if (_y == 1 && y) _y = 0;
			cout << min(_x + x, _y + y) << "\n";
			continue;
		}
		ans = 1e18;
		for (int i = 2; i <= n; i++) {
			int sum = (s[i] - '0') + (s[i - 1] - '0') * 10;
			for (int j = 1; j <= n; j++) {
				if (j == i - 1 || j == i || s[j] == '1')
					continue;
				sum += s[j] - '0';
			}
			ans = min(ans, sum);
		}
		cout << ans << "\n";
	}
    return 0;
}
```

---

## 作者：bryce (赞：0)

## 思路
这道题目需要分类讨论一下，首先当 $n = 2$ 时，直接去掉前导零，输出答案。

当 $n > 2$ 时，枚举有两个字符的断点，将每个段的数存下来，去掉前导零，如果某个段有 $0$，那么答案就是 $0$，如果没有 $0$，那么如果某个段有 $1$ 时，肯定与前面或者后面的数相乘，这样才能让答案最小。

接下来就是模拟的时间。
## 代码

```cpp
#include<iostream>

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}
inline void write(int x){if (x < 0) putchar('-'), x = -x;if (x > 9) write(x / 10);putchar(x % 10 + '0');}

const int N = 25;
int T, n, ans;
char c[N];
int a[N];
int get(int l, int r){//去掉前导零，获得数字
    int pos = l, res = 0;
    for (pos = l; pos < r; pos++){
        if (c[pos] != '0') break;
    }
    for (int i = pos; i <= r; i++) res = res * 10 + (c[i] - '0');
    return res;
}

int main(){
    T = read();
    while (T--){
        n = read(), ans = 0x7fffffff;
        cin >> (c + 1);
        if (n == 2){//特判
            cout << get(1, n) << '\n';
            continue;
        }
        bool flag = 0;
        for (int i = 1; i < n; i++){
            int cnt = 0;
            bool f = 0;
            for (int j = 1; j <= n; j++){
                if (j == i) a[++cnt] = get(j, j + 1), j++;
                else a[++cnt] = get(j, j);
                if (a[cnt] == 0){
                    f = 1;
                    cout << 0 << '\n';//有 0 答案最小就为 0
                    break;
                }
            }
            if (f){
                flag = 1;
                break;
            }
            int res = 0;
            bool d = 0;
            for (int j = 1; j <= cnt; j++){
                if (a[j] == 1){//有 1 相当于不加，乘起来还是为前面或后面的数的值
                    continue;
                }else d = 1;
                res += a[j];
            }
            if (!d) ans = min(ans, 1);//特判如果整个全为 1
            else ans = min(ans, res);
        }
        if (flag) continue;
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：Daniel_yao (赞：0)

# Solve

考虑搜索，$O(T2^n)$ 显然过不了。

先枚举相邻合并段，分析答案贡献的情况：先默认全加，发现答案上限为 $19\times9 + 99=261$。然后将一部分序列改为乘法操作。

设 $f_i$ 表示前 $i$ 个数组成的序列的最小答案，初始设为 $[1,i]$ 的数值和。向前枚举 $j$，考虑将 $[j+1,i]$ 这一段改为乘法操作，于是就有 $f[i]=\min\limits_{j=0}^{i-1}f[j]+\prod\limits_{k=j+1}^{i}a_k$，显然后半部分可以预处理，于是就能做 $O(n^3)$ 的动态规划了。

因为乘法运算结果很大，所以当答案超过 $261$ 时，就取 $261$ 即可。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)
#define mod 262

using namespace std;

const int N = 25;

char a[N];

int T, n, num[N], sum[N], dp[N], ans = 261, fuck_you_code_bug_tot;

void solve() {
  cin >> n;
  int len = n-1, cnt0 = 0;
  ans = 261;
  For(i,1,n) cin >> a[i];
  For(i,1,n-1) {
    memset(num, 0, sizeof num);
    For(j,1,i-1) num[j] = a[j] - '0', sum[j] = sum[j-1] + num[j];
    num[i] = (a[i] - '0') * 10 + (a[i+1] - '0');
    sum[i] = sum[i-1] + num[i];
    For(j,i+2,n) num[j-1] = a[j] - '0', sum[j-1] = sum[j-2] + num[j-1];
    For(j,1,len) {
      cnt0 += (num[j] == 0);
      dp[j] = sum[j];
      int mul = num[j];
      FOR(k,j-1,0) {
        dp[j] = min(dp[j], dp[k] + mul);
        mul *= num[k];
        if(dp[j] > 261 || mul > 261) {
          break;
        } 
      }
    }
    ans = min({ans, dp[len], (cnt0 > 0ll ? 0ll : 261ll)});
  }
  cout << ans << '\n';
  return ;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while(T--) solve();
  return 0;
}
```

---

## 作者：CJ_Fu (赞：0)

## [CF1986D Mathematical Problem](https://www.luogu.com.cn/problem/CF1986D)

题意：

在长度为 $n$ 的数字串中插入 $n-2$ 个运算符（$+$ 或 $\times$）使得该串的运算结果最小，多组询问。$T\le 10^4,n\le 20$。

题解：

手模一下样例可以发现，对于 $n\ge 4$ 的串，如果出现了 $0$，则总能插入 $n-2$ 个乘号，使得该式的最小值为 $0$；对于 $n=3$ 的串，可以直接暴力判断插入的符号；对于 $n=2$ 的串，不需要任何操作，只需要去除前导零输出原数即可。

先理解一个比较显然的东西：对于两个**相邻位置上**的两个数 $a,b\in[1,9]$，当 $a,b\neq 1$ 时 $ab>a+b$，否则 $ab\le a+b$。

由于只有 $n-2$ 个操作符，而可以放操作符的位置有 $n-1$ 个，所以对于没有出现 $0$ 且 $n\ge 4$ 的串，我们就可以先暴力枚举之间没有符号的位置，把这两位合并成一个两位数，然后循环统计答案：
- 当前位置的值 $>1$，统计答案，加上该位置的值；
- 当前位置的值 $=1$，不进行任何操作（相当于把 $1$ 乘到另一个数上）。

可以结合样例 $7$ 理解一下：

```
S=23311
i=1
23 3 1 1 --- ans=23+3*1*1=26
i=2
2 33 1 1 --- ans=2+33*1*1=35
i=3
2 3 31 1 --- ans=2+3+31*1=36
i=4
2 3 3 11 --- ans=2+3+3+11=19
minans=19
```

总时间复杂度 $O(Tn^2)$。代码实现可能略有不同。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int T,n,a[33];
char s[33];
signed main(){
    cin>>T;
    while(T--){
        cin>>n;
        cin>>s;
        if(n==2){
            cout<<(s[0]-'0')*10+s[1]-'0'<<'\n';
            continue;
        }
        if(n==3){
            int s1=s[0]-'0',s2=s[1]-'0',s3=s[2]-'0';
            cout<<min(min(s1+s2*10+s3,s1*(s2*10+s3)),min(s1*10+s2+s3,(s1*10+s2)*s3))<<'\n';
            continue;
        }
        int f0=0;
        for(int i=0;s[i];i++){
            if(s[i]=='0') f0=1;
        }
        if(f0){
            cout<<"0\n";
            continue;
        }
        int ans=0x3f3f3f3f3f3f3f3f;
        for(int i=1;i<n;i++){
            a[i]=(s[i-1]-'0')*10+s[i]-'0';
            for(int j=1;j<i;j++){
                a[j]=s[j-1]-'0';
            }
            for(int j=i+1;j<n;j++){
                a[j]=s[j]-'0';
            }
            int cnt=0;
            for(int j=1;j<n;j++){
                while(a[j]==1&&j<n) j++;
                if(j<n) cnt+=a[j];
                /* 这里可以改成
                if(a[j]!=1) cnt+=a[j];
                */
            }
            ans=min(ans,cnt);
        }
        cout<<ans<<'\n';
    }
    return 0-0;
}
```

---

## 作者：MrPython (赞：0)

$n\le20$，我们可以轻易地枚举中间没有插入符号的空位。每次枚举可以确定一个数列。若数列中存在 $0$，则显然全部乘起来答案最优（为 $0$）。否则，剩下的数都是正整数。设 $b$ 为任意正整数，则当 $a=1$ 时保证有 $ab\le a+b$。考虑在其他位置全部插入加号，在 $1$ 的左侧或右侧插入乘号，将它乘进两边，就可以使总和减小掉这个 $1$。特别地，若数列中全部为 $1$，则其值应为 $1$。

```cpp
#include <bits/extc++.h>
using namespace std;
namespace pbds = __gnu_pbds;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
using uc = unsigned char;
int main(void) {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    size_t T;
    cin >> T;
    while (T--) {
        size_t n;
        cin >> n;
        vector<char> c(n);
        for (char &i : c)
            cin >> i;
        if (n == 2) {
            cout << ((c[0] - '0') * 10 + (c[1] - '0')) << '\n';
            continue;
        }
        ui ans = numeric_limits<ui>::max();
        for (size_t i = 0; i < n - 1; ++i) {
            vector<uc> p;
            for (size_t j = 0; j < n; ++j)
                if (j == i) {
                    p.emplace_back((c[j] - '0') * 10 + (c[j + 1] - '0'));
                    ++j;
                } else
                    p.emplace_back(c[j] - '0');
            if (count(p.begin(), p.end(), 0)) {
                cout << "0\n";
                goto end;
            } else
                ans = min(ans,
                          max<ui>(accumulate(p.begin(), p.end(), ui(0)) - count(p.begin(), p.end(), 1), 1));
        }
        cout << ans << '\n';
    end:;
    }
    return 0;
}
```

---

## 作者：liugh_ (赞：0)

[CF1986D Mathematical Problem](https://www.luogu.com.cn/problem/CF1986D)

赛时被卡了好一会，后面发现是自己想假了，改了以后一发过......

---

对于每组数据，给定一个长度为 $n$ 的仅包含数字的字符串，你要在其 $n-1$ 个空隙中插入 $n-2$ 个 $+$ 或 $\times$ 使得算式的结果最小。

$t\le 10^4,n\le 20$。

---

若 $n=2$ 或 $n=3$，直接特判，后面的情况会很好写。当 $n\ge 4$ 时，如果序列中存在 $0$，那么答案直接就是 $0$ 了，故我们假设序列中不存在 $0$。注意到插入 $n-2$ 个符号，且 $n$ 较小，考虑枚举由两个字符组成的这个数在哪里。接下来，在剩余位上插入 $+$ 或 $\times$，插拿个更优？下面给一个可能比较严谨的证明：


$$
\begin{aligned}
\forall a,b\in \{x|x\in\mathbb{N^*},x\in[1,9]\}，&不妨设 ab<a+b，则 \\
ab<a+b &\Rightarrow a<\frac{a+b}{b} \\
&\Rightarrow a-\frac{a}{b}<1 \\
&\Rightarrow a(b-1)<b \\
&\Rightarrow a=1 \\
&\end{aligned}
$$

故下一位是 $1$ 时，当前空隙插 $\times$，否则插 $+$。

时间复杂度 $O(tn^2)$。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(3,"Ofast","inline","-fgcse","-fgcse-lm","-fipa-sra","-ftree-pre","-ftree-vrp","-fpeephole2","-ffast-math","-fsched-spec","unroll-loops","-falign-jumps","-falign-loops","-falign-labels","-fdevirtualize","-fcaller-saves","-fcrossjumping","-fthread-jumps","-funroll-loops","-freorder-blocks","-fschedule-insns","inline-functions","-ftree-tail-merge","-fschedule-insns2","-fstrict-aliasing","-falign-functions","-fcse-follow-jumps","-fsched-interblock","-fpartial-inlining","no-stack-protector","-freorder-functions","-findirect-inlining","-fhoist-adjacent-loads","-frerun-cse-after-loop","inline-small-functions","-finline-small-functions","-ftree-switch-conversion","-foptimize-sibling-calls","-fexpensive-optimizations","inline-functions-called-once","-fdelete-null-pointer-checks")
#pragma GCC target("abm","avx","avx2","f16c","fma","mmx","popcnt","sse","sse2","sse3","sse4","ssse3")
#define inline inline __attribute__((always_inline))
#define getchar() (_p==_q&&(_q=(_p=_b)+fread(_b,1,_s,stdin),_p==_q)?-1:*_p++)
using namespace std;const int _s=1<<20;char _b[_s],*_p=_b,*_q=_b;template<class T>inline void fr(T&x){x=0;char c=0;do{}while(c=getchar(),c<48||c>57);do x=x*10+c-48;while(c=getchar(),c>47&&c<58);}inline void debug(){cout<<endl;}template<class T,class...Argv>inline void debug(const T&x,const Argv&...argv){cout<<' '<<x;debug(argv...);}template<class T>inline void Debug(const string&s,const T l,const T r){cout<<' '<<s;for(T it=l;it!=r;++it)cout<<' '<<*it;cout<<endl;}template<class T>inline void Debug(const T l,const T r){for(T it=l;it!=r;++it)cout<<' '<<*it;cout<<endl;}

const int Maxn = 20 + 3;

int N;
string a;

bool check0() {
	for (auto c : a) if (c == '0') return 1;
	return 0;
}

int ctoi(char c) {
	return c - 48;
}

signed main() {
	// freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int Case; cin >> Case; while (Case--) {
		cin >> N;
		cin >> a;
		int ans = 1e9;
		if (N == 2) {
			cout << stoi(a) << '\n';
			continue;
		}
		if (N == 3) {
			ans = min(ans, stoi(a.substr(0, 1)) * stoi(a.substr(1, 2)));
			ans = min(ans, stoi(a.substr(0, 1)) + stoi(a.substr(1, 2)));
			ans = min(ans, stoi(a.substr(0, 2)) * stoi(a.substr(2, 1)));
			ans = min(ans, stoi(a.substr(0, 2)) + stoi(a.substr(2, 1)));
			cout << ans << '\n';
			continue;
		}
		if (check0()) {
			cout << 0 << '\n';
			continue;
		}
		for (int key = 0; key < N - 1; ++key) {
			int res = 0;
			for (int i = 0; i < N; ++i) {
				if (i == key) {
					res += ctoi(a[i]) * 10 + ctoi(a[i + 1]);
					++i;
					continue;
				}
				if (a[i] != '1') res += ctoi(a[i]);
			}
			ans = min(ans, res);
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：linjinkun (赞：0)

还是贪心。

分情况讨论，设答案为 $ans$，那么有如下情况。

$$ \left\{
\begin{aligned}
ans &= 0 & a \supseteq \left\{0\right\} \\
ans &= 1 & a_i = 1(1 \le i \le n-1) \\
ans &= \sum_{i = 1}^{n-1}(a_i \not= 1)\times a_i
\end{aligned}
\right.
$$

这里的 $a$ 指的是用 $n-2$ 个运算符隔开的 $n-1$ 个数组成的集合。

我们来分析一下括号里的内容，如果 $a$ 中至少有一个 $0$，就是包含 $0$，那么直接把 $n-2$ 个运算符全部设置成 $\times$，答案就是 $0$，这个东西毋庸置疑，一定是最小答案，而当 $a$ 全部都是 $1$ 时，那么肯定不能加，只能全部设置成 $\times$，那么最小答案就是 $1$，最后一种情况，就是普通情况，肯定是全部（除了 $a_i$ 为 $1$ 的）设置成 $+$，因为对于任何两个大于 $1$ 的整数相加一定不会小于这两个整数相乘，而当 $a_i = 1$ 的情况，直接把它设置成 $\times$ 就行了。

分析完括号后，来看前面的处理，由于如果在 $n$ 个数内插入运算符，运算符的个数一定是 $n-1$ 个，但题目要求 $n-2$ 个，所以一定有一个数是两位数，所以只需要遍历 $n$ 个数，看在哪里组成两位数就好了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[25];
int num[25];
signed main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		scanf("%s",a+1);
		int sum;//和
		int k;//数字个数（n-1个）
		int minn = 1e9;//最小值设成最大
		for(int i = 1;i<=n-1;i++)//枚举i到
		{
			sum = 0;//初始化
			k = 0;
			for(int j = 1;j<=n;j++)
			{
				if(j == i)
				{
					num[++k] = (a[j]-'0')*10+a[j+1]-'0';//合并
					j++;
				}
				else
				{
					num[++k] = a[j]-'0';
				}
			}
			bool flag = 1;
			for(int i = 1;i<=k;i++)
			{
				if(num[i] == 0)//如果有一个是0
				{
					flag = 0;
					break;
				}
				if(num[i] == 1)//为1，不加入sum
				{
					continue;
				}
				sum+=num[i];//加上
			}
			if(flag == 0)//如果这次答案0
			{
				minn = 0;//最小答案一定为0
				break;
			}
			if(sum == 0)
			{
				minn = min(minn,1);//这次答案为1
			}
			else
			{
				minn = min(minn,sum);
			}
		}
		printf("%d\n",minn);
	}
	return 0;
}
```

---

## 作者：Harrylzh (赞：0)

## 思路


看到样例马上想到如果输入中有 $0$，则最小结果一定是 $0$。但可以被 $101$ 和 $10$ 等卡掉，因为其中的 $0$ 一定是要被“捆绑”的，所以特判他们，其他输出 $0$。剩下的是没有 $0$ 的，考虑将最小的两个数“捆绑”成两位数后其他数都加起来，碰见 $1$ 则乘。但如果是 $2221$ 等数据的话，可以把 $21$ 的 $1$ 让出去作乘法，会使答案减少。所以，在按上述规则计算一遍“捆绑”的两位数中个位不为 $1$ 的，两者取最小值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t;
long long n;
string s;
long long a[1000000+5],cur=0;
void sol()
{
	cin>>n;
	if(n==2)
	{
		long long tmp;
		cin>>tmp;
		cout<<tmp<<"\n";
		return ;
	}//特判 
	cin>>s;
	s=' '+s;
	if(n==3&&s[2]=='0')
	{
		cout<<min((s[1]-'0')+(s[3]-'0'),(s[1]-'0')*(s[3]-'0'))<<"\n";
		return ;
	}//特判 
	for(long long i=1;i<=n;i++)
	{
		if(s[i]=='0')
		{
			cout<<"0\n";
			return;
		}
	}//特判
	
	//以下处理没有0的字符串 
	 
	long long minn=2e9;
	for(long long i=1;i<n;i++)
	{
		minn=min(minn,1ll*(s[i]-'0')*10+(s[i+1]-'0'));
	}
	long long mind=0;
	for(long long i=1;i<=n;i++)
	{
		if((s[i]-'0')*10+(s[i+1]-'0')==minn)
		{
			mind=i;
			break;
		}
	}//第一种 
	long long minn1=2e9;
	for(long long i=1;i<n;i++)
	{
		if(s[i+1]!='1')minn1=min(minn1,1ll*(s[i]-'0')*10+(s[i+1]-'0'));
	}
	long long mind1=0;
	for(long long i=1;i<=n;i++)
	{
		if((s[i]-'0')*10+(s[i+1]-'0')==minn1)
		{
			mind1=i;
			break;
		}
	}//第二种（两位数个位不为1） 
	cur=0;
	for(long long i=1;i<=n;i++)
	{
		if(i==mind)
		{
			a[++cur]=(s[i]-'0')*10+(s[i+1]-'0');
			i++;
		}
		else
		{
			if(s[i]!='1')a[++cur]=s[i]-'0';
		}
	}
	long long ans=0;
	for(long long i=1;i<=cur;i++) ans+=a[i];//第一种算答案 
	if(mind1==0)//第二种找不到，取第一种答案 
	{
		cout<<ans<<"\n";
		return;
	}
	cur=0;
	for(long long i=1;i<=n;i++)
	{
		if(i==mind1)
		{
			a[++cur]=(s[i]-'0')*10+(s[i+1]-'0');
			i++;
		}
		else
		{
			if(s[i]!='1')a[++cur]=s[i]-'0';
		}
	}
	long long ans2=0;
	for(long long i=1;i<=cur;i++) ans2+=a[i];
	cout<<min(ans,ans2)<<"\n";//取最小 
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		sol();
	}
	return 0;
}
```

---

## 作者：yshpdyt (赞：0)

## 题意
长为 $n$ 只有数字的字符串，你可以在 $n-1$ 空隙里选择 $n-2$ 个，在其中添加加号或乘号，最小化字符串构成的逻辑表达式运算结果。

## Sol
看似 $n$ 最大只有 $20$，但是最多是 $O(n^2)$ 的算法。
 
先不管不选哪个空隙，考虑这样的问题：给定 $m$ 个数，在 $m-1$ 个空隙中插入加号或乘号，让运算结果最小。

如果某一位置为 $0$ 就不用考虑了，答案直接就是 $0$。

考虑其它情况，根据~~九九乘法表~~不难得出，对于 $a+b< ab$
在 $a\ge 2$ 且 $b> 2$ 时成立。

所以考虑贪心，如果 $a_i=1$ 就放乘号，答案一定不会变大，如果 $a_i\ge 2$ ，放加号变大的程度小于放乘号，以上操作进行一次是线性的。

然后考虑题目的某一空隙不放符号的问题，如果题目中对任意位置恰好进行一次操作，通常可以考虑枚举这个特殊位置，并递推处理贡献，在本题中即把左右两个数合并成一个数，然后 $n$ 个数填 $n-2$ 个空隙变成 $n-1$ 个数填 $n-2$ 个空隙，就变成了刚才的问题。

时间复杂度 $O(Tn^2)$。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll n,m,a[N],b[N];
string s;
ll calc(){
    ll res=0;
    for(int i=1;i<=n;i++){
        if(b[i]==0)return 0;
        if(b[i]==1)continue;
        res+=b[i];
    }
    if(res==0)res=1;
    return res;
}
void sol(){
    cin>>n>>s;
    s=" "+s;
    for(int i=1;i<=n;i++){
        a[i]=s[i]-'0';
        b[i]=a[i];
    }
    ll res=inf;
    for(int i=2;i<=n;i++){
        b[i-1]=a[i-1]*10+a[i];
        b[i]=1;
        res=min(calc(),res);
        b[i-1]=a[i-1];
        b[i]=a[i];
    }
    cout<<res<<endl;
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}
```

---

