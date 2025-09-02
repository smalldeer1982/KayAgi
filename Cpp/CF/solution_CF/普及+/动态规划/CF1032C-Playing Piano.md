# Playing Piano

## 题目描述

Little Paul wants to learn how to play piano. He already has a melody he wants to start with. For simplicity he represented this melody as a sequence $ a_1, a_2, \ldots, a_n $ of key numbers: the more a number is, the closer it is to the right end of the piano keyboard.

Paul is very clever and knows that the essential thing is to properly assign fingers to notes he's going to play. If he chooses an inconvenient fingering, he will then waste a lot of time trying to learn how to play the melody by these fingers and he will probably not succeed.

Let's denote the fingers of hand by numbers from $ 1 $ to $ 5 $ . We call a fingering any sequence $ b_1, \ldots, b_n $ of fingers numbers. A fingering is convenient if for all $ 1\leq i \leq n - 1 $ the following holds:

- if $ a_i < a_{i+1} $ then $ b_i < b_{i+1} $ , because otherwise Paul needs to take his hand off the keyboard to play the $ (i+1) $ -st note;
- if $ a_i > a_{i+1} $ then $ b_i > b_{i+1} $ , because of the same;
- if $ a_i = a_{i+1} $ then $ b_i\neq b_{i+1} $ , because using the same finger twice in a row is dumb. Please note that there is $ \neq $ , not $ = $ between $ b_i $ and $ b_{i+1} $ .

Please provide any convenient fingering or find out that there is none.

## 说明/提示

The third sample test is kinda "Non stop" song by Reflex.

## 样例 #1

### 输入

```
5
1 1 4 2 2
```

### 输出

```
1 4 5 4 5 ```

## 样例 #2

### 输入

```
7
1 5 7 8 10 3 1
```

### 输出

```
1 2 3 4 5 4 3 ```

## 样例 #3

### 输入

```
19
3 3 7 9 8 8 8 8 7 7 7 7 5 3 3 3 3 8 8
```

### 输出

```
1 3 4 5 4 5 4 5 4 5 4 5 4 3 5 4 3 5 4 ```

# 题解

## 作者：zbbfans (赞：7)

# 思路：贪心+模拟
其实这题看作模拟的话还是挺简单的。


---

#### 首先考虑 $a_i>a_{i-1}$ 的情况：
如果 $a_i>a_{i+1}$ 那说明 $a_i$ 是一个转折点，即最大值，所以我们让 $ans_i$ 直接等于 $5$ 即可。

但是我们要判断一下 $ans_{i-1}$ 是否已经为 $5$ 如果是的话就说明我们这里不能再放 $5$ 了，直接输出 $-1$ 即可。

当 $a_i<=a_{i+1}$ 的时候就说明这时还是递增的，所有直接让 $ans_i=ans_{i-1}+1$ 就行了。
#### 再考虑 $a_i<a_{i-1}$ 的情况：
其实还是跟上一种情况差不多的做法。

如果 $a_i<a_{i+1}$ 那说明 $a_i$ 也是一个转折点，即最小值，所以我们让 $ans_i$ 直接等于 $1$ 即可。

我们仍然需要判断 $ans_{i-1}=1$ 的情况,如果是，则输出 $-1$。 

如果 $a_i>a_{i+1}$ 则 $ans_i=ans_{i-1}-1$。
#### 考虑最后一种情况 $a_i=a_{i-1}$ 时。
在这里我们要用到贪心的思想。

当 $a_i>a_{i+1}$ 时，如果 $ans_{i-1}$ 不等于 $5$ 我们就让 $ans_i=5$，反之我们让 $ans_i=4$。

解释一下：
假如说我们后面全是单调递减的，那我们肯定希望我们能减的多一点，所以我们在这里让 $ans_i$ 尽可能的大。

当 $a_i<a_{i+1}$ 的时候，其实思路跟上面差不多了，我们要让 $ans_i$ 尽可能的小。

最后考虑 $a_i=a_{i+1}$ 其实这种情况比较随便了，只要让 $ans_i$ 不等于 $ans_{i-1}$ 就行了。

但是以防我们跟上面的情况冲突，所以我们不让 $ans_i$ 等于 $1$ 或 $5$ 所以我们让他尽量的往中间靠。


---

本题的越界情况也好判断，只要 $ans_i<1$ 或者是 $ans_i>5$ 就直接输出 $-1$ 就行了。
# Code
```cpp
#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
inline long long read(){
	long long f=1,k=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-f;
		c=getchar();
	}
	while(c>='0'&&c<='9') k=k*10+c-'0',c=getchar();
	return f*k;
}
inline void print(long long x){
	if(x<0) putchar('-'),x=-x;
	if(x<10) putchar(x+'0');
	else print(x/10),putchar(x%10+'0');
}
long long n,a[200010],ans[200010];
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	if(a[1]>a[2]) ans[1]=5;
	else if(a[1]<a[2]) ans[1]=1;
	else ans[1]=3;
	for(int i=2;i<n;i++){
		if(a[i]>a[i-1]){
			if(a[i]>a[i+1]){
				if(ans[i-1]==5){
					print(-1);
					return 0;
				}
				ans[i]=5;
			}
			else ans[i]=ans[i-1]+1;
		}else if(a[i]<a[i-1]){
			if(a[i]<a[i+1]){
				if(ans[i-1]==1){
					print(-1);
					return 0;
				}
				ans[i]=1;
			}else ans[i]=ans[i-1]-1;
		}else{
			if(a[i]<a[i+1]){
				if(ans[i-1]==1) ans[i]=2;
				else ans[i]=1;
			}else if(a[i]>a[i+1]){
				if(ans[i-1]==5) ans[i]=4;
				else ans[i]=5;
			}else{
				if(ans[i-1]<=2) ans[i]=ans[i-1]+1;
				else ans[i]=ans[i-1]-1;
			}
		}
		if(ans[i]<=0||ans[i]>5){
			print(-1);
			return 0;
		}
	}
	if(a[n]>a[n-1]){
		if(ans[n-1]==5){
			print(-1);
			return 0;
		}
		ans[n]=5;
	}else if(a[n]<a[n-1]){
		if(ans[n-1]==1){
			print(-1);
			return 0;
		}
		ans[n]=1;
	}else{
		if(ans[n-1]==1) ans[n]=2;
		else if(ans[n-1]==5) ans[n]=4;
		else ans[n]=5;
	}
	for(int i=1;i<=n;i++){
		print(ans[i]);putchar(' ');
	}
	return 0;
} 
```

---

## 作者：Infinite_Eternity (赞：3)

# Description

[CF1032C Playing Piano](https://www.luogu.com.cn/problem/CF1032C)

给定长为 $n$ 的序列 $a$，要求给定长为 $n$ 的序列 $b$ 满足：

- $1\le b_i\le 5$
- 如果 $a_i<a_{i+1}$，则 $b_i<b_{i+1}$；
- 如果 $a_i>a_{i+1}$，则 $b_i>b_{i+1}$；
- 如果 $a_i=a_{i+1}$，则 $b_i\ne b_{i+1}$。

给出一个 $b$，或说明不存在，输出 $-1$。

数据范围：$1 \le n \le 10^5$，$1 \le a_i \le 2 \times 10^5$。

# Analysis

~~一道很水的紫题，可以降绿。~~

做法：DP + 构造。

$dp[i][j]=k$ 表示：第 $i$ 位填 $j$ 的情况是由第 $i-1$ 位填 $k$ 的状态转移过来的。若 $k=0$，则表示不可到达。

对于一个 $i \in [1,5]$，若 $dp[n][i]$ 都等于 $0$，则无解；否则，逆序记录答案并输出即可。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
int n, a[MAXN], dp[MAXN][5];
inline int read()
{
    register char c = getchar();
    register int x = 0, f = 1;
    while (c < '0' || c > '9') {if (c == '-') f = -1;c = getchar();}
    while (c >= '0' && c <= '9') {x = (x << 3) + (x << 1) + c - 48;c = getchar();}
    return x * f;
}
int main()
{
    n=read();
    for (register int i = 0; i < n; ++i) 
        a[i]=read();
    for (register int i = 1; i <= 5; ++i) 
        dp[0][i] = 1;
    for (register int i = 0; i < n-1; ++i)
    {
        for (register int j = 1; j <= 5; ++j)
        {
            for (register int k = 1; k <= 5; ++k)
            {
                if (!dp[i][k]) continue;
                if (a[i] < a[i+1] && k < j) dp[i+1][j] = k;
                if (a[i] > a[i+1] && k > j) dp[i+1][j] = k;
                if (a[i] == a[i+1] && k != j) dp[i+1][j] = k;
            }
        }
    }
    vector<int> ans;
    for (register int j = 1; j <= 5; ++j)
    {
        if (dp[n-1][j])
        {
            ans.push_back(j);
            for (register int i = n-1; i > 0; --i)
            {
                j = dp[i][j];
                ans.push_back(j);
            }
            break;
        }
    }
    if (ans.size() == 0) printf("-1\n");
    else
    {
        for (register int i = ans.size()-1; i >= 0; --i)
            printf("%d ", ans[i]);
    }
    return 0;
}
```

---

## 作者：Night_sea_64 (赞：3)

因为此题只能填 $1\sim5$，所以每次可以直接枚举填哪个，暴力 dp 就可以。

状态：$f_{i,j}$ 是 bool 类型，表示有没有可能在第 $i$ 个位置放 $j$。

转移：假设当前想填 $j$，而上一个填 $k$，而且 $j,k$ 满足要求（题目中写的 $j>k,j<k,j\ne k$ 的要求）。每个 $j$ 可能由之前的很多 $k$ 转移来。如果这些状态中至少有一个成立，这个状态就成立。

最后是找答案，我们倒着扫。因为正着扫，当前成立的答案可能对应不到后面的方案。每次都寻找上一个 $k$，随便找一个满足相邻的要求并且有方案的 $k$ 就行了，因为他是 spj。

代码如下：

```cpp
#include<iostream>
using namespace std;
int a[100010];
bool f[100010][10];
int path[100010];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    f[1][1]=1,f[1][2]=1,f[1][3]=1,f[1][4]=1,f[1][5]=1;
    for(int i=2;i<=n;i++)
    {
        if(a[i]<a[i-1])
            for(int j=1;j<=5;j++)
                for(int k=j+1;k<=5;k++)
                    f[i][j]|=f[i-1][k];
        else if(a[i]>a[i-1])
            for(int j=1;j<=5;j++)
                for(int k=1;k<j;k++)
                    f[i][j]|=f[i-1][k];
        else for(int j=1;j<=5;j++)
                for(int k=1;k<=5;k++)
                    if(j!=k)f[i][j]|=f[i-1][k];
    }
    int now=0;
    for(int i=1;i<=5;i++)
        if(f[n][i])
        {
            now=i,path[n]=now;
            break;
        }
    if(now==0)
    {
        cout<<-1<<endl;
        return 0;
    }
    for(int i=n-1;i>=1;i--)
    {
        if(a[i]<a[i+1])
        {
            for(int j=1;j<now;j++)
                if(f[i][j])
                {
                    now=j;
                    break;
                }
        }
        else if(a[i]>a[i+1])
        {
            for(int j=now+1;j<=5;j++)
                if(f[i][j])
                {
                    now=j;
                    break;
                }
        }
        else
        {
            for(int j=1;j<=5;j++)
                if(j!=now&&f[i][j])
                {
                    now=j;
                    break;
                }
        }
        path[i]=now;
    }
    for(int i=1;i<=n;i++)cout<<path[i]<<" ";
    cout<<endl;
    return 0;
}
```

---

## 作者：IceKylin (赞：1)

# CF1032C Playing Piano 题解

本题有一种 **严格 $O(n)$** 的做法，即比 $O(5^2n)$ 的 DP 做法时间复杂度更优。

为方便描述，下文称原序列为 $\{a_n\}$，称答案序列为 $\{ans_n\}$。

考虑根据大小关系构造，显然有以下结论：

1. 当 $a_{i-1}<a_i\wedge a_i>a_{i+1}$ 时，$ans_i=5$。

2. 当 $a_{i-1}<a_i\wedge a_i<a_{i+1}$ 时，$ans_i=ans_{i-1}+1$。

3. 当 $a_{i-1}>a_i\wedge a_i<a_{i+1}$ 时，$ans_i=1$。

4. 当 $a_{i-1}>a_i\wedge a_i>a_{i+1}$ 时，$ans_i=ans_{i-1}-1$。

然后考虑相等的情况，相对复杂一些：

1. 当 $a_{i-1}=a_{i}\wedge a_i>a_{i+1}$ 时，分两种情况：

	1.1 当 $ans_{i-1}=5$ 时，$ans_{i}=4$。
    
   1.2 当 $ans_{i-1}\ne 5$ 时，$ans_i=5$。
   
2. 当 $a_{i-1}=a_i=a_{i+1}$ 时，分两种情况：

	2.1 当 $ans_{i-1}\le 2$ 时，$ans_i=ans_{i-1}+1$。
    
   2.2 当 $ans_{i-1}\ge 3$ 时，$ans_i=ans_{i-1}-1$。
   
3. 当 $a_{i-1}=a_{i}\wedge a_i<a_{i+1}$，分两种情况：

	3.1 当 $ans_{i-1}=1$ 时，$ans_i=2$。
    
   3.2 当 $ans_{i-1}\ne 1$ 时，$ans_i=1$。

边界构造如下：

```cpp
if(a[1]>a[2])ans[1]=5;
else if(a[1]<a[2])ans[1]=1;
else ans[1]=3;
```

```cpp
if(a[n]>a[n-1])ans[n]=5;
else if(a[n]<a[n-1])ans[n]=1;
else{
	if(ans[n-1]==5)ans[n]=1;
	else ans[n]=ans[n-1]+1;
}
```

可以证明，以上构造方式是 **最优** 的，所以如果出现 $ ans_i\notin [1,5]$ 或者 $ans_i$ 不符合题意的情况，那么该组数据一定 **无解** 。

代码按照上述过程模拟即可。

P.S. 分类讨论建议自己再思考一下，或者推一遍样例，加深理解。

## AC 代码
```cpp
//By IceKylin
#include<bits/stdc++.h>
#define maxn 100050
#define ios ios::sync_with_stdio(false)
using namespace std;
int n,a[maxn],ans[maxn];
int main(){
  ios;
  cin>>n;
  for(int i=1;i<=n;++i)cin>>a[i];
  if(a[1]>a[2])ans[1]=5;
  else if(a[1]<a[2])ans[1]=1;
  else ans[1]=3;
  for(int i=2;i<n;++i){
    if(a[i]>a[i-1]){
      if(a[i]>a[i+1])ans[i]=5;
      else ans[i]=ans[i-1]+1;
    }
    else if(a[i]<a[i-1]){
      if(a[i]<a[i+1])ans[i]=1;
      else ans[i]=ans[i-1]-1;
    }
    else{
      if(a[i]>a[i+1]){
        if(ans[i-1]==5)ans[i]=4;
        else ans[i]=5;
      }
      else if(a[i]<a[i+1]){
        if(ans[i-1]==1)ans[i]=2;
        else ans[i]=1;
      }
      else{
        if(ans[i-1]<=2)ans[i]=ans[i-1]+1;
        else ans[i]=ans[i-1]-1;
      }
    }
    if(ans[i]<1||ans[i]>5){
      cout<<-1;
      return 0;
    }
  }
  if(a[n]>a[n-1])ans[n]=5;
  else if(a[n]<a[n-1])ans[n]=1;
  else{
    if(ans[n-1]==5)ans[n]=1;
    else ans[n]=ans[n-1]+1;
  }
  for(int i=2;i<=n;++i){
    if(a[i]>a[i-1]&&ans[i]<=ans[i-1]||a[i]<a[i-1]&&ans[i]>=ans[i-1]||a[i]==a[i-1]&&ans[i]==ans[i-1]){
      cout<<-1;
      return 0;
    }
  }
  for(int i=1;i<=n;++i)cout<<ans[i]<<' ';
  return 0;
}
```

---

## 作者：Him_shu (赞：0)

## 题意

给定长为 $n$ 的序列 $a$，要求给定长为 $n$ 的序列 $b$ 满足：

- $1\le b_i\le 5$
- 如果 $a_i<a_{i+1}$，则 $b_i<b_{i+1}$；
- 如果 $a_i>a_{i+1}$，则 $b_i>b_{i+1}$；
- 如果 $a_i=a_{i+1}$，则 $b_i\ne b_{i+1}$。

给出一个 $b$，或说明不存在，输出 $-1$。

## 分析

考虑动态规划：

- 状态：$dp_{i,j}$ 表示 $b_i=j$ 的可行性。
- 转移：分 $3$ 种情况：

  - 当 $a_i=a_i-1$ 时，$dp_{i,j}|=dp_{i-1,k}(k \ne j \ $且 $ \ 1 \le k \le 5)$。
  - 当 $a_i>a_i-1$ 时，$dp_{i,j}|=dp_{i-1,k}(1 \le k < j)$。
  - 当 $a_i<a_i-1$ 时，$dp_{i,j}|=dp_{i-1,k}(j < k \le 5)$。
- 初始值：$dp_{1,j}=1(1 \le j \le 5)$

细节：

- 因为给出一个 $b$，所以要记录前置，考虑 $pre_{i,j}$ 为 $dp_{i,j}$ 的前置的 $j$，要在转移时把其中的一个可行的用 $pre_{i,j}$ 去标记。~~不懂的话看代码的详细解释~~

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){f=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0',ch=getchar();}return x*f;}
void write(int x){if(x<0){putchar('-'),x=-x;}if(x>9){write(x/10);} putchar(x%10+'0');return;}
//不用在意 是我的快读
const int N=2e5+5,inf=1e14;
int n;
int a[N];
int dp[N][6];//进行转移
int pre[N][6];//记录前置
vector<int>ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	dp[1][1]=dp[1][2]=dp[1][3]=dp[1][4]=dp[1][5]=1;//赋初值
	for(int i=2;i<=n;i++){
		if(a[i]==a[i-1]){//第一种情况
			for(int j=1;j<=5;j++){
				for(int k=1;k<=5;k++){
					if(k!=j){
						if(dp[i-1][k]){//判断是否可行
							pre[i][j]=k;//标记前置
							dp[i][j]|=dp[i-1][k];
							break;//没有用的优化
						}
					}
				}
			}
		}
		else if(a[i]>a[i-1]){
			for(int j=2;j<=5;j++){
				for(int k=1;k<j;k++){
					if(dp[i-1][k]){//判断是否可行
						pre[i][j]=k;//标记前置
						dp[i][j]|=dp[i-1][k];
						break;//没有用的优化
					}
				}
			}
		}
		else{
			for(int j=1;j<=4;j++){
				for(int k=j+1;k<=5;k++){
					if(dp[i-1][k]){//判断是否可行
						pre[i][j]=k;//标记前置
						dp[i][j]|=dp[i-1][k];
						break;//没有用的优化
					}
				}
			}
		}
	}
	int flat=-1;
	for(int i=1;i<=5;i++){//判断是否存在
		if(dp[n][i]){
			flat=i;
			break;
		}
	}
	if(flat==-1){cout<<"-1\n";return;}//不存在，输出-1
	ans.push_back(flat);
	for(int i=n,k=pre[i][flat];i>=1&&k!=0;i--,k=pre[i][k]){//把前置加入答案中
		ans.push_back(k);
	}reverse(ans.begin(),ans.end());//此时答案是反的，因为是i从n->1,所以要翻转
	for(auto i:ans){
		cout<<i<<' ';
	}//输出
	return 0;
}
```

## 感受

凭绿有点高了，但是不难。

---

## 作者：QWQ_123 (赞：0)

设 $f_{i,j}$ 表示前 $i$ 个数，当前数为 $j$ 是否可行。

然后每次枚举 $i$，然后根据 $a_i$ 和 $a_{i+1}$ 的大小关系更新 $f_{i+1}$，然后每次用 $g$ 记录一下当前是从那个数字更新的然后最后一直往前跳即可。

这能 $\texttt {*1700}$！

---

## 作者：scp020 (赞：0)

题目翻译已经很简洁了，这里不再多说什么了。

观察数据范围，$1 \le b_i \le 5$，说明 $b_i$ 的取值范围很有限，不难想到递推或爆搜。

现在设 $f_{i,j}$ 表示 $b_i$ 是否可以取到 $j$。下面为递推方法：

- 若 $a_i < a_{i+1}$ 且 $f_{i,j} = 1$，则对所有 $k > j$，有 $f_{i+1,k} = 1$。

- 若 $a_i > a_{i+1}$ 且 $f_{i,j} = 1$，则对所有 $k < j$，有 $f_{i+1,k} = 1$。

- 若 $a_i = a_{i+1}$ 且 $f_{i,j} = 1$，则对所有 $k \neq j$，有 $f_{i+1,k} = 1$。

若对于 $i \in [1,5]$，$\exists f_{n,i}=1$，则表示有答案，否则表示无答案。

对于有答案的情况，我们考虑倒序寻找答案。如果 $f_{i,j} = 1$，则对于 $k \in [1,5]$，$\exists f_{i-1,k}=1$。故一定能找到一组答案。

代码如下。

``` cpp
#include<bits/stdc++.h>
using namespace std;
#define Getchar() p1==p2 and (p2=(p1=Inf)+fread(Inf,1,1<<21,stdin),p1==p2)?EOF:*p1++
#define Putchar(c) p3==p4 and (fwrite(Ouf,1,1<<21,stdout),p3=Ouf),*p3++=c
char Inf[1<<21],Ouf[1<<21],*p1,*p2,*p3=Ouf,*p4=Ouf+(1<<21);
inline void read(int &x,char c=Getchar())
{
	bool f=c!='-';
	x=0;
	while(c<48 or c>57) c=Getchar(),f&=c!='-';
	while(c>=48 and c<=57) x=(x<<3)+(x<<1)+(c^48),c=Getchar();
	x=f?x:-x;
}
inline void write(int x)
{
	if(x<0) Putchar('-'),x=-x;
	if(x>=10) write(x/10),x%=10;
	Putchar(x^48);
}
int n,a[100010],ans[100010];
bool f[100010][6];
int main()
{
	read(n),f[1][1]=f[1][2]=f[1][3]=f[1][4]=f[1][5]=1;
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=2;i<=n;i++)
		if(a[i]>a[i-1]) for(int j=2;j<=5;j++) for(int k=1;k<j;k++) f[i][j]|=f[i-1][k];
		else if(a[i]<a[i-1]) for(int j=1;j<=4;j++) for(int k=j+1;k<=5;k++) f[i][j]|=f[i-1][k];
		else for(int j=1;j<=5;j++) for(int k=1;k<=5;k++) if(j!=k) f[i][j]|=f[i-1][k];
	if(!f[n][1] && !f[n][2] && !f[n][3] && !f[n][4] && !f[n][5])
	{
		cout<<-1;
		return 0;
	}
	for(int i=1;i<=5;i++) if(f[n][i]) ans[n]=i;
	for(int i=n-1;i;i--)
	{
		if(a[i]<a[i+1])
		{
			for(int j=1;j<ans[i+1];j++) if(f[i][j]) ans[i]=j;
		}else if(a[i]>a[i+1])
		{
			for(int j=ans[i+1]+1;j<=5;j++) if(f[i][j]) ans[i]=j;
		}else
		{
			for(int j=1;j<=5;j++) if(f[i][j] && j!=ans[i+1]) ans[i]=j;
		}
	}
	for(int i=1;i<=n;i++) write(ans[i]),Putchar(' ');
	fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
	return 0;
}
```



---

## 作者：dbxxx (赞：0)

[欢迎到我的博客查看本文，谢谢！](https://www.cnblogs.com/crab-in-the-northeast/p/cf1032c.html)

[CF1032C Playing Piano - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/CF1032C)。

题目大意是：能否构造一个长度为 $n$ 的值域为 $[1, 5]$ 的整数序列 $b$，使得相邻两个数之间的大小关系满足给定的大小关系。

给定的大小关系可能是大于、小于、不等于。

CF 官方给的 dp 做法是假的。实际上只需要一个橙色难度的简单构造。而且这个做法时空复杂度和 $b$ 的值域完全无关。dp 就相对受限了。

把序列拆分为连续大于段，连续小于段和连续不等段。

贪心地，连续大于段从 $5$ 开始，填 $(5, 4, 3, 2, 1)$。连续小于段从 $1$ 开始，填 $(1, 2, 3, 4, 5)$。填不下去了就是连续长度大于 $5$ 了，报个无解。

连续不等段直接在 $2, 3$ 之间振荡。$3, 4$ 之间，$2, 4$ 之间也可以，但不要涉及到 $1, 5$，看后面就知道原因了。

然后考虑一下段和段的边界。

先小于后大于 $a < b < c > d > e$。发现 $c$ 明显应该填 $5$，也就是跟随后面那个段，因为要让后面尽可能连续下去。按照上面的贪心填法对应的构造方案是 $(1, 2, 5, 4, 3)$。

先大于后小于同理，跟后面。

先不等后小于 $a \ne b \ne c < d < e$。会发现 $c$ 应该填 $1$ 最好，也是跟随后面。这里就是为什么不等段的振荡最好不涉及 $1$ 和 $5$，否则可能影响边界。

先不等后大于同理，跟后面。

先小于后不等 $a < b < c \ne d \ne e$，这个 $c$ 应该跟前面。

先大于后不等同理，跟前面。

但是这样会有一个问题：$\cdots >  a > b > c \ne d < e < f < \cdots$。$d$ 应该怎么填？如果 $c$ 没填 $1$ 自然老办法 $d$ 填 $1$，如果 $c$ 填了 $1$ 呢？

不难发现，此时 $d$ 只能填 $2$。因为根据我们的贪心想法，$c$ 此时都为 $1$ 了就说明前面必有一段 $5 > 4 > 3 >2 >1$ 的链，将 $c$ 修改为 $2$ 前面就会不合法。大小于号翻过来后情况也是类似的。

注意 $n = 1$ 可能需要特判，根据你咋写的。

复杂度 $\Theta(n)$。

```cpp
/*
 * @Author: crab-in-the-northeast 
 * @Date: 2023-01-07 01:36:54 
 * @Last Modified by: crab-in-the-northeast
 * @Last Modified time: 2023-01-07 02:23:00
 */
#include <bits/stdc++.h>
inline int read() {
    int x = 0;
    bool f = true;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            f = false;
    for (; isdigit(ch); ch = getchar())
        x = (x << 1) + (x << 3) + ch - '0';
    return f ? x : (~(x - 1));
}

const int maxn = (int)1e5 + 5;

int a[maxn];
char b[maxn]; // b[i] 表示 b[i] 和 b[i + 1] 的大小关系

int main() {
    int n = read();
    if (n == 1) {
        puts("1");
        return 0;
    }
    
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    for (int i = 1; i < n; ++i) {
        if (a[i] < a[i + 1])
            b[i] = '<';
        else if (a[i] > a[i + 1])
            b[i] = '>';
        else
            b[i] = '!';
    }
    
    int lst = 1;
    if (b[1] == '>')
        lst = 5;
    else if (b[1] == '!')
        lst = 2;
    
    std :: vector <int> ans = {lst};
    
    for (int i = 2; i < n; ++i) {
        int now;
        char p = b[i - 1], q = b[i];
        if (p == '<') {
            if (lst == 5)
                break;
            now = lst + 1;
            if (q == '>')
                now = 5;
        } else if (p == '>') {
            if (lst == 1)
                break;
            now = lst - 1;
            if (q == '<')
                now = 1;
        } else if (p == '!') {
            if (q == '!') {
                now = 3;
                if (lst == 3)
                    now = 2;
            } else if (q == '<') {
                now = 1;
                if (lst == 1)
                    now = 2;
            } else if (q == '>') {
                now = 5;
                if (lst == 5)
                    now = 4;
            }
        }

        ans.push_back(lst = now);
    }

    if (b[n - 1] == '<')
        ans.push_back(5);
    else if (b[n - 1] == '>')
        ans.push_back(1);
    else
        ans.push_back(lst == 5 ? 4 : 5);
    
    if ((int)ans.size() == n)
        for (int x : ans)
            printf("%d ", x);
    else
        printf("-1");
    puts("");
    return 0;
}
```

---

## 作者：crn1 (赞：0)

## 题目大意
给定长度为 $n$ 的序列 $a$，构造一个序列 $b$ 满足：
- $b_i\in [1,5]$
- 如果 $a_i<a_{i+1}$，$b_i<b_{i+1}$
- 如果 $a_i>a_{i+1}$，$b_i>b_{i+1}$
- 如果 $a_i=a_{i+1}$，$b_i\neq b_{i+1}$

## 题解

### DP

考虑 dp，设 dp 状态 $dp[i][j]$ 表示构造出来的序列 $b$ 的第 $i$ 位可否为 $j$。

1. $a_i<a_{i+1}$：

则 $b_i<b_{i+1}$，$f[i+1][j]$ 可以由 $f[i][k]\ (1\leq k\lt j)$ 转移。

2. $a_i>a_{i+1}$：

同理，$f[i+1][j]$ 可以由 $f[i][k]\ (j\lt k\leq 5)$ 转移。

3. $a_i=a_{i+1}$：

只要求 $b_i\neq b_{i+1}$，所以对于每个 $f[i][k]=1$，都可以转移到 $f[i+1][j]\ (j\neq k)$。

### 构造

如果 $f[n][i]\ (1\leq i\leq 5)$ 全都为 $0$，说明最后一位不能是 $1$ 到 $5$ 中任意一个数，无解，否则根据序列 $a$ 倒推答案。

## 代码

```cpp
#include <cstdio>

const int N = 100005;
int a[N], b[N]; bool f[N][6];

int main(void) {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (int i = 1; i <= 5; ++i) f[1][i] = 1; // 初始化，第一位可以是任意数
	for (int i = 2; i <= n; ++i)
		if (a[i - 1] < a[i]) {
			for (int j = 1; j <= 5; ++j)
				if (f[i - 1][j]) {
					for (int k = j + 1; k <= 5; ++k) f[i][k] = 1;
					break; // 后面全部标记了，直接退出
				}
		} else if (a[i - 1] > a[i]) {
			for (int j = 5; j; --j)
				if (f[i - 1][j]) {
					for (int k = j - 1; k; --k) f[i][k] = 1;
					break; // 前面全部标记了，直接退出
				}
		} else {
			for (int j = 1; j <= 5; j++)
				for (int k = 1; f[i - 1][j] && k <= 5; ++k)
					f[i][k] |= j != k; // 注意是 |= 不然会被覆盖
		}
	for (int i = 5; i; --i) if (f[n][i]) { b[n] = i; break; }
	if (!b[n]) {
		puts("-1"); // 无解
		return 0;
	}
	for (int i = n - 1; i; --i) {
		if (a[i] < a[i + 1]) {
			for (int j = b[i + 1] - 1; j; --j) // 其实正着和倒着不影响
				if (f[i][j]) { b[i] = j; break; }
		} else if (a[i] > a[i + 1]) {
			for (int j = b[i + 1] + 1; j <= 5; ++j)
				if (f[i][j]) { b[i] = j; break; }
		} else {
			for (int j = 1; j <= 5; ++j)
				if (f[i][j] && j != b[i + 1]) { b[i] = j; break; }
		}
	}
	for (int i = 1; i <= n; ++i) printf("%d ", b[i]);
	return 0;
}
```

---

## 作者：灵茶山艾府 (赞：0)

一个复杂度和 $b_i$ 范围无关的构造方法。

首先，为了方便处理只有一个元素或最后两个元素相等的情况，在 $a$ 的末尾添加一个值为 $a_n$ 的元素。

把数组分成若干水平段、下降段和上升段：

1. 水平段，$b_i$ 可以取 $2$ 或者 $3$，保证和 $b_{i-1}$  不同即可。
2. 下降段，$b_i$ 可以从 $5$ 开始，如果 $b_{i-1}$ 也是 $5$，那就从 $4$ 开始，然后每次减少 $1$。
3. 上升段，$b_i$ 可以从 $1$ 开始，如果 $b_{i-1}$ 也是 $1$，那就从 $2$ 开始，然后每次增加 $1$。

如果上述过程产生了不在 $[1,5]$ 中的数则输出 $-1$。

复杂度为 $O(n)$。

AC 代码（Golang）：

```go
package main
import("bufio";."fmt";"os")

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var n int
	Fscan(in, &n)
	a := make([]int, n, n+1)
	for i := range a {
		Fscan(in, &a[i])
	}
	a = append(a, a[n-1]) // 末尾加个哨兵，方便处理只有一个元素 or 最后两个元素相等的情况
	b := make([]int, n)
	for i := 0; i < n; {
		if a[i] == a[i+1] {
			if b[i] == 0 {
				b[i] = 2
				if i > 0 && b[i-1] == 2 {
					b[i] = 3
				}
			}
			i++
			continue
		}
		st := i
		// 处理连续下降段或连续上升段
		for i += 2; i < n && a[i] != a[i-1] && a[i] < a[i-1] == (a[i-1] < a[i-2]); i++ {
		}
		if a[st] > a[st+1] {
			b[st] = 5
			if st > 0 && b[st-1] == 5 {
				b[st] = 4
			}
			for st++; st < i; st++ {
				b[st] = b[st-1] - 1
			}
		} else {
			b[st] = 1
			if st > 0 && b[st-1] == 1 {
				b[st] = 2
			}
			for st++; st < i; st++ {
				b[st] = b[st-1] + 1
			}
		}
		i--
		if b[i] < 1 || b[i] > 5 {
			Fprint(out, -1)
			return
		}
	}
	for _, v := range b {
		Fprint(out, v, " ")
	}
}
```


---

