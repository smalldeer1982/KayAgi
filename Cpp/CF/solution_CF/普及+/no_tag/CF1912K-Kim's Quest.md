# Kim's Quest

## 题目描述

In the long-forgotten halls of Kombinatoria's ancient academy, a gifted mathematician named Kim is faced with an unusual challenge. They found an old sequence of integers, which is believed to be a cryptic message from the legendary Kombinatoria's Oracle, and Kim wants to decipher its hidden meaning.

Kim's mission is to find specific patterns within the sequence, known as Harmonious Subsequences. These are extraordinary subsequences where the sum of every three consecutive numbers is even, and each subsequence must be at least three numbers in length.

Given a sequence $ a_i $ ( $ 1 \le i \le n $ ) of length $ n $ , its subsequence of length $ m $ is equal to $ a_{b_1}, a_{b_2}, \ldots, a_{b_m} $ and is uniquely defined by a set of $ m $ indices $ b_j $ , such that $ 1 \le b_1 < b_2 < \ldots < b_m \le n $ . Subsequences given by different sets of indices $ b_j $ are considered different.

There's a twist in Kim's quest: the number of these Harmonious Subsequences could be overwhelming. To report the findings effectively, Kim must calculate the total number of these subsequences, presenting the answer as a remainder after dividing by the number $ 998\,244\,353 $ .

## 说明/提示

In the provided input data for the fifth sample, the sequence of numbers is split into three separate lines for clarity, but it should be understood that in the actual test data, the sequence is given in one line. The actual number of Harmonious Subsequences in this example is $ 4\,991\,221\,765 = 5 \times 998\,244\,353 $ , hence the output is zero as a result of finding its remainder after dividing by the number $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
1```

## 样例 #2

### 输入

```
5
2 8 2 6 4```

### 输出

```
16```

## 样例 #3

### 输入

```
5
5 7 1 3 5```

### 输出

```
0```

## 样例 #4

### 输入

```
11
3 1 4 1 5 9 2 6 5 3 6```

### 输出

```
386```

## 样例 #5

### 输入

```
54
2 1 1 1 1 2 1 2 2 2 2 1 1 1 2 1 1 2
2 1 2 2 2 2 2 2 2 1 1 1 2 2 1 1 1 1
2 2 1 1 2 2 2 2 2 1 1 1 2 2 1 2 1 1```

### 输出

```
0```

# 题解

## 作者：sordio (赞：4)

首先将题目简化，由于判断是否为偶数，所以可以将每个数取模，只保存零一串。

因为发现每一个合法子序列中，只有后两位会对后面的子序列产生影响，所以可以存下子序列的后两位，使用数位DP。

令 $dp _ {i,j} $ 表示前 $i$ 为数字中，最后两位位为 $j$（这里使用了状态压缩的思想，将两个二进制数压缩到一个十进制数中），于是可以将 $a_i$ 和 $j$ 分类讨论，具体转移过程见代码。

还需要给每个 $dp_{i,j}$ 赋一个初始权值，为加上这个节点新加的值。这就需要保存前 $i-1$ 的序列中 $01$，$10$，$11$，$00$ 的个数。

整体时间复杂度 $O(n)$。

下面是具体代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,mod=998244353;
int n,ans;
int s0,s1,s01,s10; //分别为0，1，10，11串个数
int a[N];
int dp[N][4];
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        a[i]=a[i]%2; 
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<4;j++) dp[i][j]=dp[i-1][j]; //整体赋值
        if(a[i]==0){
            dp[i][2]+=dp[i-1][3];
            dp[i][0]+=dp[i-1][0];
            if(s0>=2) dp[i][0]+=(s0*(s0-1)/2)%mod;
            if(s1>=2) dp[i][2]+=(s1*(s1-1)/2)%mod;
            s0++;s10=(s10+s1)%mod;
        }else{
            dp[i][1]+=dp[i-1][2]+s10;
            dp[i][3]+=dp[i-1][1]+s01;
            s1++;s01=(s0+s01)%mod;
        } //分类讨论转移
        for(int j=0;j<4;j++) dp[i][j]%=mod; //整体取模
    }
    for(int i=0;i<4;i++) ans=(ans+dp[n][i])%mod;
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：IGA_Indigo (赞：4)

## 题目大意
提议非常好理解，就是给你一个长度为 $n$ 的序列问你多少个 子序列满足任意三个相邻的数都为偶数。

输入输出格式没有翻译，我来简单说一下。
### 输入格式
第一行一个正整数 $n$，表示序列长度（$3\le n\le 2\cdot 10^5$）。

第二行 $n$ 个正整数，用空格隔开，表示这个序列。
### 输出格式
一个整数（方案数），对 $998244353$ 取模。
## 大体思路
我们考虑暴力转移的 DP。

$f_{i,j}$ 中 $i$ 表示长度，我们发现子序列的长度没有限制，只需要任意三个**连续**的是偶数即可。

注意，是连续的，那么我们根本不需要考虑长度大于三的序列了，举个例子，长度为 4 的序列可以拆成两个长度为 3 的，长度为 5 的序列可以拆成三个长度为 3 的，而答案没有影响。

$j$ 表示哪种可以组成三个数加起来是偶数的方案。

0 表示偶数，1 表示奇数的话，根据小学数学，可以得出四种满足三个数加起来是偶数的情况：

$f_{i,0}$：0 0 0；

$f_{i,1}$：1 1 0；

$f_{i,2}$：1 0 1；

$f_{i,3}$：0 1 1。

所以就得到转移方程：

如果 $a_i$ 为偶数：

$f_{3,0}=f_{3,0}+f_{3,0}+f_{2,0}$；

$f_{3,1}=f_{3,1}+f_{2,1}+f_{3,3}$；

$f_{2,0}=f_{2,0}+f_{1,0}$；

$f_{2,2}=f_{2,2}+f_{1,2}$；

$f_{1,0}=f_{1,0}+1$；

$f_{1,3}=f_{1,3}+1$。

如果 $a_i$ 为奇数：

$f_{3,3}=f_{3,3}+f_{2,3}+f_{3,2}$；

$f_{3,2}=f_{3,2}+f_{3,1}+f_{2,2}$；

$f_{2,1}=f_{2,1}+f_{110}$；

$f_{2,3}=f_{2,3}+f_{1,3}$；

$f_{1,1}=f_{1,1}+1$；

$f_{1,2}=f_{1,2}+1$。

最后答案就是 $f_{3,0}+f_{3,1}+f_{3,2}+f_{3,3}$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std; 
int mod=998244353;
int a[200005];
long long f[5][5];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		if(a[i]%2==0){
			f[3][0]=(f[3][0]+f[3][0]+f[2][0])%mod;
			f[3][1]=(f[3][1]+f[2][1]+f[3][3])%mod;
			f[2][0]=(f[2][0]+f[1][0])%mod;
			f[2][2]=(f[2][2]+f[1][2])%mod;
			f[1][0]=(f[1][0]+1)%mod;
			f[1][3]=(f[1][3]+1)%mod;
		}
		else{
			f[3][3]=(f[3][3]+f[2][3]+f[3][2])%mod;
			f[3][2]=(f[3][2]+f[3][1]+f[2][2])%mod;
			f[2][1]=(f[2][1]+f[1][1])%mod;
			f[2][3]=(f[2][3]+f[1][3])%mod;
			f[1][1]=(f[1][1]+1)%mod;
			f[1][2]=(f[1][2]+1)%mod;
		}
	}
	cout<<(f[3][0]+f[3][1]+f[3][2]+f[3][3])%mod<<endl;
	return 0;
}
```

---

## 作者：zhouzihang1 (赞：1)

# CF1912K Kim's Quest 题解

[洛谷传送门](https://www.luogu.com.cn/problem/CF1912K)

## 思路

首先，对于 $1 \le n \le 10^5$ 的数据范围，一定需要使用 $O(n)$ 的时间复杂度来解决。

如果我们使用 $0,1$ 来表示当前数字是奇数还是偶数，很明显可以使用状态压缩 dp 来解决此题。

如果 $1$ 表示奇数，$0$ 表示偶数，则对于三个数来说，有如下的合法状态。

$000,011,101,110$，其十进制下分别是 $0,3,5,6$。

## 做法

那么，我们定义 $f$ 数组，其中 $f_{3,j}$ 就表示对三个数来说，当前结尾的状态为 $j$ 的所有合法状态数的数量。

但是显然，仅仅使用长度为 $3$ 的状态并不能完整转移操作。

于是乎，我们有了 $f_{2,j}$ 表示以当前结尾的状态为 $j$ 的长度为 $2$ 的子序列所有合法数量。

同样的，$f_{1,j}$ 表示以当前结尾的所有数中为 $j$ 的数量。

但是，统计时会发现这会有两个循环即 $O(n^2)$ 的时间复杂度。

所以就有了前缀和优化，简单说就是把上次的方案数存下来，然后运算过程中累加。

## Code

```cpp
if(x&1)
{
	f[3][3]+=f[2][1]+f[3][5];f[3][3]%=Mod;
	f[3][5]+=f[2][2]+f[3][6];f[3][5]%=Mod;
	f[2][1]+=f[1][0];f[2][1]%=Mod;
	f[2][3]+=f[1][1];f[2][3]%=Mod;
	f[1][1]++;
}
else
{
	f[3][6]+=f[2][3]+f[3][3];f[3][6]%=Mod;
	f[3][0]+=f[2][0]+f[3][0];f[3][0]%=Mod;
	f[2][2]+=f[1][1];f[2][2]%=Mod;
	f[2][0]+=f[1][0];f[2][0]%=Mod;
	f[1][0]++;
}
```

---

