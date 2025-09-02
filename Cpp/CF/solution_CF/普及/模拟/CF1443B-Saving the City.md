# Saving the City

## 题目描述

Bertown is a city with $ n $ buildings in a straight line.

The city's security service discovered that some buildings were mined. A map was compiled, which is a string of length $ n $ , where the $ i $ -th character is "1" if there is a mine under the building number $ i $ and "0" otherwise.

Bertown's best sapper knows how to activate mines so that the buildings above them are not damaged. When a mine under the building numbered $ x $ is activated, it explodes and activates two adjacent mines under the buildings numbered $ x-1 $ and $ x+1 $ (if there were no mines under the building, then nothing happens). Thus, it is enough to activate any one mine on a continuous segment of mines to activate all the mines of this segment. For manual activation of one mine, the sapper takes $ a $ coins. He can repeat this operation as many times as you want.

Also, a sapper can place a mine under a building if it wasn't there. For such an operation, he takes $ b $ coins. He can also repeat this operation as many times as you want.

The sapper can carry out operations in any order.

You want to blow up all the mines in the city to make it safe. Find the minimum number of coins that the sapper will have to pay so that after his actions there are no mines left in the city.

## 说明/提示

In the second test case, if we place a mine under the fourth building and then activate it, then all mines on the field are activated. The cost of such operations is six, $ b=1 $ coin for placing a mine and $ a=5 $ coins for activating.

## 样例 #1

### 输入

```
2
1 1
01000010
5 1
01101110```

### 输出

```
2
6```

# 题解

## 作者：Suuon_Kanderu (赞：4)

当成一个比较简单的线性 DP 入门题来做了。

首先 $dp_i$ 表示将前 i 个字符全部变为 0 的代价。

我们从前往后扫，遇到 `1` 时有两种选择：

1. 顺延最近的一个 A 操作（显然我们要从前面最近的一个 1 顺延），但我们需要把这两个 `1` 中间的 `0` 全部用 B 操作染色。
2. 另起炉灶，从这个位置开始，使用一个新的 A 操作。

还有一个注意事项，第一个 `1` 只能用一个 A 操作。

所以状态转移方程就出来了：

$$ dp_i = \begin{cases} dp_{i-1} &\text{if }(s_i = 0)\\dp_{k} + \min((i - k - 1)\cdot B , A) &\text{if }(s_i=1) \end{cases} $$

(P.S. $k$ 为 $i$ 前面最近的 1 的位置, $s$ 为字符串。)

```
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
string s;
int last = 0;
int dp[N]; 
void solve() {
	int a , b;scanf("%d%d" , &a , &b);
	cin >> s;
	int last = 0 ,  i;
	for(i = 0; i < s.size(); i++)
		if(s[i] == '1') 
		{dp[i] = a; last = i;break;}
	for(i++; i < s.size(); i++) {
		if(s[i] == '0')dp[i] = dp[i - 1];
		else  {
			dp[i] = dp[last] + min(a , (i - last - 1) * b);
			last = i;	
		}
	}
	printf("%d\n" , dp[s.size() - 1]);
} 
int main() {
	int t;scanf("%d" , &t);
	while(t--) {solve();}
}
```


---

## 作者：MYCui (赞：3)

[$MYCui's$ $blog$](https://www.cnblogs.com/MYCui/p/13947754.html#CF1443B)
### 前言：

本人这篇题解按照规范的DP思路走。

所以会讲得比较模式化，希望能够理解。

### 做法：

采用线性的$dp$的方法，时间复杂度O($n$)，额外空间复杂度O($2*n$)

首先是一个小小的贪心。

去掉给出的串的前缀的0以及后缀的0，因为我们不需要处理这些0.

然后$dp$进行处理

+ #### 设立状态

$dp[i][0]$(这个状态是对于第$i$位字符为$0$的时候特有的状态)表示到第$i$位，不把第$i$位上的$0$变成$1$进行处理，将前面的串全部变为$0$所需要的最少费用。

$dp[i][1]$表示的是将当前位变为$1$进行处理(假如是$1$就不需要变)，将前面的串变为$0$所需要的最小费用

+ #### 状态转移方程

分两种情况：

$Case1$:**当前字符为$1$**

分情况讨论：

假如前一个字符为$1$

$dp[i][1] = dp[i - 1][1];$

假如前一个字符为$0$

$dp[i][1] = min(dp[i - 1][0] + A,dp[i - 1][1])$

(因为如果前一个是$0$，不把它变为$1$，那么我们不能承接前面的情况，只能把当前的$1$作为接下来连续的$1$组成的串的开头，费用加上A。不然就可以接上前面的)

$Case2$：**当前字符为$0$**

$dp[i][1] = dp[i - 1][1] + B$

对于此种情况下对于$dp[i][0]$我们再结合当前字符的前一个字符进行分类讨论。

前一个字符为$1$，$dp[i][0] = dp[i - 1][1]$

否则$dp[i][0] = dp[i - 1][0]$(前一个字符变为$1$但是这个字符不变为$1$显然没有意义。)

状态转移方程到此结束。

+ #### 边界的设立
 $dp[start][1] = A$(这里是$start$是指第一个$1$出现的位置)
 
 最后的答案会是$dp[len][1]$(这里的$len$是最后一个$1$出现的位置)
 
 思路讲解到此结束。
 
#### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
int A,B;
int dp[100005][2];
char s[100005];
int main()
{
	cin >> T;
	for(int v = 1 ; v <= T ; v ++)
	{
		cin >> A >> B;
		cin >> s + 1;
		int len = strlen(s + 1);
		int start = 1;
		while(s[start] == '0')start ++;
		while(s[len] == '0')len --;
		dp[start][1] = A;
		for(int i = start + 1 ; i <= len ; i ++)
		{
			dp[i][1] = dp[i][0] = 0;
            //状态转移，前文已经介绍的很清楚了，不再赘述
			if(s[i] == '1')
			{
				if(s[i - 1] == '1')
				dp[i][1] = dp[i - 1][1];
				else dp[i][1] = min(dp[i - 1][1] , dp[i - 1][0] + A);
			}
			else 
			{
				dp[i][1] = dp[i - 1][1] + B;
				if(s[i - 1] == '1')
				dp[i][0] = dp[i - 1][1];
				else dp[i][0] = dp[i - 1][0];
			}
		}
		cout << dp[len][1] << endl;
	}
	return 0;
}
```

#### 后话

这个做法一开始我没敢保证是对的，仔细想想感觉没有什么问题，然后Hack了自己几组数据，没有Hack成功，要是哪位仁兄Hack 掉了我，及时私信我，我会做出修改。

---

## 作者：ACtheQ (赞：2)

思路：

这是一道简单 dp 题，本题显然是一维 dp，时间复杂度 $O(n)$。

状态定义：$dp_i$ 表示前 $i$ 个数全部开启的最小代价。

若 $a_i=0$ 则 $dp_i=dp_{i-1}$，因为不需要变。

否则，考虑两种情况，直接变，$dp_i=dp_{i-1}+a$。

第二种情况：把 先把中间的 $0$ 变成 $1$，再把 $1$ 和前面的 $1$ 一块变。设上一个 $0$ 的下标为 $cnt$，则 $dp_i=dp_{cnt}+b\times(i-cnt-1)$。

完整代码

```c++
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int f[N];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
        int x,y;
        cin>>x>>y;
        string s;
		cin>>s;
		memset(f,0,sizeof(f));
		for(int i=0;i<s.size();i++)
		{
			if(s[i]=='0') f[i]=f[i-1];
			else
			{
				int cnt=-1;
				for(int j=i-1;j>=0;j--)
				{
					if(s[j]=='1')
					{
						cnt=j;
						break;
					}
				}
				if(cnt!=-1) f[i]=min(f[i-1]+x,f[cnt]+(i-cnt-1)*y);
				else f[i]=f[i-1]+x;
			}
		}
        cout<<f[s.size()-1]<<endl;
	}
	return 0;
}
```

---

## 作者：raincity (赞：1)

## 分析
这是一道显然的 DP。

设 $dp_i$ 为把前 $i$ 个字符都改成 0 所需要的最小代价。$sum_i$ 为前 $i$ 个字符中 0 的个数。设这个字符串为 $s$。

当 $s_i=0$ 时，$dp_i=dp_{i-1}$。

当 $s_i=1$ 时，$dp_i=\min_{j=1}^{i-1}(dp_j+a+b\times(sum_i-sum_j))$。

这是个 $O(n^2)$ 的算法。

拆一下：$dp_j+a+b\times(sum_i-sum_j)=(a+b\times sum_i)+(dp_j-b\times sum_j)$。

所以维护 $dp_j-b\times sum_j$ 的前缀 $\max$ 就可以做到。

用单调队列可以解决 1 变 0 有长度限制的题。

## 解决
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

string s;
int a, b, T, dp[100005], sum[100005];

int main() {
	cin >> T;
	while (T--) {
		cin >> a >> b >> s;
		int mini = 0, len = s.size();
		for (int i = 0; i < len; i++) sum[i] = i == 0 ? 1 - s[i] + '0' : sum[i - 1] + 1 - s[i] + '0';
		for (int i = 0; i < len; mini = min(mini, dp[i] - b * sum[i]), i++)
			if (s[i] == '0')
				dp[i] = i == 0 ? 0 : dp[i - 1];
			else
				dp[i] = a + b * sum[i] + mini;
		cout << dp[len - 1] << endl;
	}
	return 0;
}
```

---

## 作者：chenxinyang2006 (赞：1)

并没有想到贪心，想的是一个简单的 dp

思考一下这个 $0$ 变 $1$ 有什么用，显然是把一些 $0$ 变成 $1$ 以后形成一个大的 $1$ 联通块，然后用一次 $1$ 变 $0$ 全部消掉

所以我们可以把这个字符串划分为一些部分，每个部分要么全是 $0$，即没有花费，要么是要把所有 $0$ 变成 $1$，然后 $1$ 全部变为 $0$

设 $dp_i$ 为划分完 $[1,i]$ 的最小花费，设 $sum_i$ 为 $[1,i]$ 中有多少个 $0$

那么如果 $s_i$ 为 $0$，$dp_i = dp_{i-1}$，如果 $s_i = 1$，那么枚举分割点将 $[j+1,i]$ 划分为一段，$dp_i = \min(dp_j + (sum_i - sum_j) \times b + a),j < i$

~~但是这个是 $n ^ 2$ 的~~

不难发现，这个式子可以化为 $dp_i = \min(dp_j - sum_j \times b) + b \times sum_i + a$，而 $dp_j - sum_j \times b$ 的值与 $i$ 无关，可以直接用前缀 $\min$ 维护

这个做法大概可以处理对于二操作有长度限制的情况，把前缀 $\min$ 换成单调队列就完事了

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int T,n,a,b;
char s[100005];

int sum[100005],dp[100005];//dp[i] 表示把 [1,i] 全都变成 0 的最小花费 
/*
dp[i] = min(dp[j] + (sum[i] - sum[j]) * b) + a
dp[i] = min(dp[j] - sum[j] * b) + sum[i] * b + a
*/

void solve(){
	scanf("%d%d",&a,&b);
	scanf("%s",s + 1);
	n = strlen(s + 1);
	for(int i = 1;i <= n;i++) sum[i] = sum[i - 1] + (s[i] == '0');
	int mn = 0;
	dp[0] = 0;
	for(int i = 1;i <= n;i++){
		if(s[i] == '0'){
			dp[i] = dp[i - 1];
		}else{
			dp[i] = mn + sum[i] * b + a;
		}
    	mn = min(mn,dp[i] - sum[i] * b);
		//printf("%d ",dp[i]); 
	}
	//printf("\n");
	printf("%d\n",dp[n]);
}

int main(){
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```


---

## 作者：江户川·萝卜 (赞：1)

简化题意：给定一个01串，以及a和b，其中a,b的意义如下：  

a：将**一串连续**的1改成0需要的花费。（设为a操作）
b：将**一个**0改成1需要的花费。（设为b操作）

求最少花费多少才能将01串变为0串（即全是0）。

----
这道题感觉有些麻烦啊。

一开始我先想到了将01串化为[这道题](https://www.luogu.com.cn/problem/P1320)的形式，然后a操作不动，b操作变成：`将一串0改成1需要花费b*len`（len为0子串的长度）。

接下来就不会了,背包？or 贪心？

思索一下，背包空间时间都会炸，不行。那么就剩下贪心了？

我们分别考虑全是0的子串和全是1的子串（设最终结果为`cost`）：
1. 全是1的子串：那好办，a操作一下，`cost+=a`即可。
2. 全是0的子串：发现如果将0子串改为1子串将会将两端的1子串连起来并减少一次a操作。
	1. 如果 $a>b\times len$ ，即这样做是值得的，`cost+=b*len-a`。
    2. 否则，这样做是不值得的，不用动。

模拟一下即可，注意两端0情况。
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int a,b,T,len,k,m;
bool f;
int d[100001];
int dp[100001];//这个是我一开始写的后来没动。
string str;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&a,&b);cin>>str;
		len=str.length();memset(d,0,sizeof(d)),memset(dp,0,sizeof(dp));
		k=1;f=str[0]-'0';d[k]++;
		for(int i=1;i<len;i++)
			if(str[i]-'0'==f) d[k]++;
			else f^=1,d[++k]++;
		m=0;f=str[0]-'0';
		for(int i=1;i<=k;i++){
			if((i&1)==f){
				m+=a;
			}
			else{
				if(i!=1&&i!=k&&a>b*d[i]) m+=b*d[i]-a;
			}
		}
		printf("%d\n",m);
	}
	return 0;
}
```


---

## 作者：zmza (赞：1)

这道题可以用贪心做。

我们定义数组$lt$、$rt$，分别代表连续1的序列的左边和右边。我们将它们预处理出来后，再定义一个$cnt$数组，表示两个连续一之间0的个数，再将$cnt$排序。为什么要排序呢？

举个例子。比如说`1010010001`，和`1000100101`的答案是一样的。如果不排序，那么第二个答案就会更大。所以我们要排序。

最后我们就计算最大的答案即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int sum = 0,ne = 1;char tmp;
	for(tmp = getchar(); (tmp < '0' || tmp > '9') && tmp != '-'; tmp = getchar());
	if(tmp == '-')ne = -1,tmp = getchar();
	for(; tmp >= '0' && tmp <= '9'; tmp = getchar())sum = (sum << 3) + (sum << 1) + tmp - '0';
	return sum * ne;
}
char str[100005];
int lt[100005],rt[100005],cnt,sum111[100005];
int main()
{
	int t = read();
	while(t--)
	{
		cnt = 0;
		int a = read(),b = read();
		scanf("%s",str + 1);
		int len = strlen(str + 1);
		bool flag = 0;
		for(int i = 1; i <= len; i++)//算出每一个连续一的串。
		{
			if(str[i] == '1' && flag == 0)flag = 1,lt[++cnt] = i;
			if(str[i] == '0' && flag == 1)flag = 0,rt[cnt] = i - 1;
		}
		for(int i = 2; i <= cnt; i++)//算出两个连续1串中有几个0，再将答案乘上1变0要的代价。要从二开始。
			sum111[i] = (lt[i] - rt[i - 1] - 1) * b;
		sort(sum111 + 1,sum111 + 1 + cnt);//排序
		int ans = 0;
		int minn = 1e9;
		for(int i = 2; i <= cnt; i++)
		{
			ans += sum111[i];
			minn = min(minn,ans + (cnt - i + 1) * a);//算出答案。
		}
		ans += a;
		minn = min(minn,min(ans,a * cnt));//最后还要特判全用A。
		printf("%d\n",minn);
	}
	return 0;
}
```

---

## 作者：yzx3195 (赞：0)

# 题目大意
你有一段 $01$ 串，你可以选择花费 $B$ 的代价将一个 $0$ 变为 $1$，也可以花费 $A$ 的代价将一段连续的 $1$ 变为 $0$，问你最少需要多少代价，才能把整个串都变为 $0$。
# 思路
显然，我们可以设计一个 DP，设 $f_i$ 表示当前处理到第 $i$ 位的最小代价。

考虑 $f_i$ 可以从哪里转移。

  当 $s_i =0$ 时，此时 $f_i=f_{i-1}$，否则，$f_i$ 有两种途径转移，第一种是如果我们直接将这个 $1$ 变成 $0$，或者将 $0$ 先全部变成 $1$ 再整段消掉。详见代码。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e05 + 7;

int n;

int T;

char s[MAXN];

int a, b;

int f[MAXN];

signed main()
{
	cin >> T;
	
	while(T--)
	{
		cin >> a >> b;
		scanf("%s", s + 1);
		n = strlen(s + 1);
		int cnt = -1;
		for(int i = 1; i <= n; i++)
		{
			if(s[i] == '0')
			{
				f[i] = f[i - 1];
			}
			else
			{
				if(cnt != -1)
					f[i] = min(f[i - 1] + a, f[cnt] + (i - cnt - 1) * b);
				else
					f[i] = f[i - 1] + a;
				cnt = i;
			}
		}
		printf("%d\n", f[n]);
		for(int i = 1; i <= n; i++)
		{
			f[i] = 0;
		}
	}
	
	return 0;
}
```

---

## 作者：OIerZhang (赞：0)

# [CF1443B Saving the City](https://www.luogu.com.cn/problem/CF1443B) 题解

DP 好题。

## 思路

我的思路和[楼下大佬的思路](https://www.luogu.com.cn/article/d33ivpy4)差不多, 就是当一个线性 DP 来做。

### 设计状态

由于题目问最少需要多少代价，才能把整个串都变为 $0$，所以很容易想到将 $dp_i$ 表示为把前 $i$ 个数字全部变为 $0$ 的代价。

### 设计状态转移方程

这里我们分类讨论：

- 第 $i$ 个数为 $0$。
- 第 $i$ 个数为 $1$。

第一种情况中，$0$ 是无需变换的，所以状态转移方程为 $dp_i = dp_{i - 1}$。

第二种情况中，有两种方式可行：

1. 一次性将第 $i$ 个数变为 $0$，耗费 $a$ 的代价。
1. 将 $[pos, i]$ 区间中所有 $0$ 变为 $1$，再一次性变为 $0$，耗费 $k \cdot b$ 的代价。至于为什么没有加上 $a$，是因为在执行第一步后，$[pos, i]$ 中所有数字均为 $1$，只需执行一次第二步就可以了，而第二步的费用已经在 $pos$ 处算过一遍，所以不用再次加 $a$。($pos$ 为上一个 $1$ 的位置，$k$ 为 $[pos, i]$ 区间中 $0$ 的个数)

所以第二种情况的状态转移方程为 $dp_i = \min(dp_{i - 1} + a, dp_{pos} + (i - pos - 1) \cdot b)$。

核心部分讲解完毕，上代码！

## 代码

有很多细节要特判，本蒟蒻调了几个小时才调出来~~我太菜了~~。

```cpp
#include <bits/stdc++.h>
using namespace std;

int dp[100005];

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0); // 输入输出优化，告别 scanf/printf
    int t;
    cin >> t;
    while (t--) // 多组数据
    {
        string s; // 01 字符串
        int a, b, n, j; // n: 字符串长度 j: 见思路部分 pos
        cin >> a >> b >> s;
        n = s.size();
        s = " " + s; // 下标要从 1 开始，不然会很麻烦
        if (s[1] == '0') // 这几个特判非常重要！
            dp[0] = a, dp[1] = 0, j = 0; // 第一个数字为 0 时的边界
        else
            dp[1] = a, j = 1;
        for (int i = 2; i <= n; i++)
        {
            if (s[i] == '0')
                dp[i] = dp[i - 1]; // 第一种情况
            else
            {
                dp[i] = min(dp[i - 1] + a, dp[j] + (i - j - 1) * b); // 第二种情况
                j = i; // 记录 1 的位置
            }
        }
        cout << dp[n] << endl; // 输出
    }
    return 0;
}

```

---

## 作者：zsyyyy (赞：0)

# CF1443B 1300 dp

## 题意

你有一段01串，你可以选择花费B的代价将一个0变为1，也可以花费A的代价将一段连续的1变为0，问你最少需要多少代价，才能把整个串都变为0。

## 思路

$dp_{i}{0}$：当前为1且执行A操作

$dp_{i}{1}$：当前为0且执行B操作 

$dp_{i}{2}$：当前为0且不执行操作

$book_{i}$：将当前0改为1后是否在一段连续的1中

核心代码：
```cpp
if(book[i-1]==1)  dp[i-1][1]-=a;
dp[i][0]=min(min(dp[i-1][2],dp[i-1][1])+a,dp[i-1][0]);
dp[i][1]=min(min(dp[i-1][1],dp[i-1][0]),dp[i-1][2]+a)+b;
dp[i][2]=min(dp[i-1][0],min(dp[i-1][1],dp[i-1][2]));
```
注意不要在INF上加数导致溢出。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAX=100005;
int T,a,b,len,dp[MAX][5];
//0:a(1111-0) 1:b(0-1) 2:0-no operation
bool book[MAX],flag;
char s[MAX];
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		memset(book,0,sizeof(book));
		flag=0;
		scanf("%lld%lld",&a,&b);
		scanf("%s",(s+1));
		len=strlen(s+1);
		for(int i=1;i<=len;i++)  dp[i][0]=dp[i][1]=dp[i][2]=LONG_LONG_MAX;
		for(int i=1;i<=len;i++)
		{
			if(s[i]=='0'&&!flag)
			{
				dp[i][2]=0;
				continue;
			}
			flag=1;
			if(s[i]=='1'&&i!=1)
			{
				if(book[i-1]==1)  dp[i-1][1]-=a;
				if(min(dp[i-1][2],dp[i-1][1])!=LONG_LONG_MAX)  dp[i][0]=min(min(dp[i-1][2],dp[i-1][1])+a,dp[i-1][0]);
				else  dp[i][0]=dp[i-1][0];
			}
			else if(i==1)  dp[i][0]=a;
			else  dp[i][0]=LONG_LONG_MAX;
			if(s[i]=='0')
			{
				if(dp[i-1][2]!=LONG_LONG_MAX&&min(min(dp[i-1][1],dp[i-1][0]),dp[i-1][2]+a)!=LONG_LONG_MAX)
					dp[i][1]=min(min(dp[i-1][1],dp[i-1][0]),dp[i-1][2]+a)+b;
				else if(min(dp[i-1][1],dp[i-1][0])!=LONG_LONG_MAX)
					dp[i][1]=min(dp[i-1][1],dp[i-1][0])+b;
				if(dp[i][1]==dp[i-1][0]+b||book[i-1]&&dp[i][1]==dp[i-1][1]+b)  book[i]=1;
			}
			else  dp[i][1]=LONG_LONG_MAX;
			if(s[i]=='0')  dp[i][2]=min(dp[i-1][0],min(dp[i-1][1],dp[i-1][2]));
			else  dp[i][2]=LONG_LONG_MAX;
		}
		printf("%lld\n",min(dp[len][0],min(dp[len][1],dp[len][2])));
	}
	return 0;
}
```


---

## 作者：Cylete (赞：0)

首先可以很套路地写出一个$O(n^2)$的暴力DP

$dp[i] = min(dp[j] + (sum[i] - sum[j]) * b + a), j < i,s[i] == '1'$

$dp[i] = dp[i - 1], s[i] == '0'$

其中$dp[i]$表示将$[1, i]$都变为0的最小代价，$sum[i]$表示0个数的前缀和

每次找一个最小的$j$，将$[j + 1, i]$之间的0全部变为1,再一起变为0

但是这样会T

考虑转换式子，把无关的$i$提出来

$dp[i] = min(dp[j] - sum[j] * b) + sum[i] * b + a$

每次得到新的$dp[i]$时更新$min$值即可

```cpp
const int N = 1e5 + 10;

int T;
int n, a, b, minn;
int sum[N], dp[N];
char s[N];

signed main()
{
	cin >> T;
	while(T--)
	{
		cin >> a >> b;
		cin >> s + 1;
		n = strlen(s + 1);
		minn = 0;
		for(R int i = 1; i <= n; i++) sum[i] = sum[i - 1] + (s[i] == '0');
		for(R int i = 1; i <= n; i++)
		{
			if(s[i] == '0') dp[i] = dp[i - 1];
			else dp[i] = minn + sum[i] * b + a;
			minn = min(minn, dp[i] - sum[i] * b);
		}
		writeln(dp[n]);
	}
	return 0;
}
```

---

