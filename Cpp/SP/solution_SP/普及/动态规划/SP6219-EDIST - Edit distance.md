# EDIST - Edit distance

## 题目描述

给定两个字符串 $A$ 和 $B$。回答将 $A$ 转换为 $B$ 需要的最少操作次数是多少？

操作包括：

1. 从一个字符串中删除一个字母
2. 向一个字符串中插入一个字母
3. 将一个字符串中的一个字母替换为另一个字母

## 样例 #1

### 输入

```
1
FOOD
MONEY```

### 输出

```
4```

# 题解

## 作者：封禁用户 (赞：2)

这道题其实是[编辑距离](https://www.luogu.com.cn/problem/P2758)的双倍经验，需要用到 dp 解决。

## 思路

一眼 dp。

我们可以设 $dp_{i,j}$ 表示第一个字符串 $s_1$ 的前 $i$ 位和第二个字符串 $s_2$ 的前 $j$ 位对齐所需要的最小价值。

为了方便，下面把 ${s_1}$ 的第 $i$ 位简记为 $c_{i}$，把 $s_2$ 的第 $j$ 位简记为 $d_{j}$。

考虑以下情况：

- 如果 $c_{i}=d_{j}$，可以得到 $dp_{i,j}=dp_{i-1,j-1}$。

- 如果 $c_{i} \neq d_{j}$，则分为一下三种情况讨论：
	
	- 修改字符时，表示当前位置对齐，但 $c_{i} \neq d_{j}$，需要修改这一位，可得 $dp_{i,j}=dp_{i-1,j-1}+1$；

	- 添加字符时，表示要在 $s_{1}$ 中添加字符去补齐，可得 $dp_{i,j}=dp_{i-1,j}+1$；

	- 删除字符时，表示要在 $s_{1}$ 中删除字符去补齐，可得 $dp_{i,j}=dp_{i,j-1}+1$；
    
可得最终的状态转移方程为：

$$dp_{i,j}=\begin{cases}dp_{i-1,j-1}&c_{i}=d_{j}\\\min(dp_{i-1,j-1},dp_{i-1,j},dp_{i,j-1})+1&c_{i} \neq d_{j}\end{cases}$$

注意：本题有多组数据。

## 示例代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[2005][2005];
void work(){
	string s1,s2;
	cin>>s1>>s2;
	int len1=s1.size(),len2=s2.size();
	for(int i=1;i<=len1;++i) dp[i][0]=i;
	for(int i=1;i<=len2;++i) dp[0][i]=i;
	for(int i=1;i<=len1;++i){
		for(int j=1;j<=len2;++j){
			if(s1[i-1]==s2[j-1]){
				dp[i][j]=dp[i-1][j-1];
			}else{
				dp[i][j]=min({dp[i-1][j],dp[i][j-1],dp[i-1][j-1]})+1;
			}
		}
	}cout<<dp[len1][len2]<<endl;
	return ;
}
int main(){
    int t;
    cin>>t;
    while(t--){
        memset(dp,0,sizeof(dp));
        work();
    }
    return 0;
}
```

$\LaTeX$ 不易，管理求过！

---

## 作者：Pollococido (赞：0)

实际上你只需要看编辑距离就行了（。

### 思路

应该都能想到是 dp 吧。

我们规定：

- $s_i$ 表示 $s$ 的前 $i$ 位组成的字符串。
- $s_1 = l, s_2 = r$。

定义 $f_{i, j}$ 表示 $l_i$ 对齐 $r_j$ 时的最小操作次数，则有以下转移。

- 若 $l_i = r_j$，则 $f_{i, j} = f_{i - 1, j - 1}$。
- 否则 $f_{i, j} = \min(f_{i - 1, j}, f_{i, j - 1}, f_{i - 1, j - 1})$。

知道转移方程后很容易写出代码。注意下标即可。

---

## 作者：fly_and_goal (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP6219)

这道题其实是编辑距离，需要用到 dp 解决。
# 思路
有三种操作：
- 插入，状态是 $dp_{i-1,j}$，即将 $A_{i-1}$ 与 $B_{j}$ 对齐。
- 替换，状态是 $dp_{i-1,j-1}$，即要让 $A_i$ 与 $B_j$ 相同。
- 删除，状态是 $dp_{i,j-1}$，即将 $A_{i}$ 与 $B_{j-1}$ 对齐。

按照以上思路进行操作（每次选三者之中最少的值）即可。

---

## 作者：huangzilang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP6219)

**题目大意：**

先输入 $t$，表示有 $t$ 组数据，每组数据输入进来两个字符串，求将 $A$ 转换为 $B$ 需要的最少操作次数。

操作包括：
- 从一个字符串中删除一个字母。
- 向一个字符串中插入一个字母。
- 将一个字符串中的一个字母替换为另一个字母。

**思路：**

本题与[编辑距离](https://www.luogu.com.cn/problem/P2758)有异曲同工之妙。

本题我用了动态规划来做。

我是先找 $b_j$ 和 $a_i$，如果 $b_j$ 和 $a_i$ 相同，就让 $f_{i,j}$ 继承 $f_{i-1,j-1}$，是因为它们相同，不用修改。如果不同，就看是 $f_{i-1,j-1}$ 与 $f_{i-1,j}$ 和 $f_{i,j-1}$ 的最小值，$f_{i,j}$ 的值就是这三者的最小值加 $1$。

如果对上面有不懂的，可以私信问我，求管理员不要打回。

---

## 作者：Zskioaert1106 (赞：0)

题目传送门：[SP6219 EDIST - Edit distance](https://www.luogu.com.cn/problem/SP6219)

双倍经验：[P2758 编辑距离](https://www.luogu.com.cn/problem/P2758)

容易想到状态：$dp_{i,j}$ 为使 $A$ 的前 $i$ 位和 $B$ 的前 $j$ 位相同的最小代价。则如果 $A_i=B_j$，就不需要进行任何操作，即把 $dp_{i-1,j-1}$ 继承过来；否则我们可以从三种操作里选择最优的一种：

- 删除：即将 $A_{i}$ 与 $B_{j-1}$ 对齐，状态是 $dp_{i,j-1}$。

- 插入：即将 $A_{i-1}$ 与 $B_{j}$ 对齐，状态 $dp_{i-1,j}$。

- 替换：使 $A_i=B_j$，即上文的继承 $dp_{i-1,j-1}$。

从三者里取最优，即 $\min(dp_{i,j-1},dp_{i-1,j},dp_{i-1,j-1})$。

代码（码风奇诡）：

```cpp
#include<iostream>
using namespace std;
int dp[2001][2001];
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	int t;
	string a,b;
	for(cin>>t;t--;cout<<dp[a.size()][b.size()]<<'\n'){
    	cin>>a>>b;
    	for(int i=1;i<=a.size();i++)dp[i][0]=i;
    	for(int i=1;i<=b.size();i++)dp[0][i]=i;
    	for(int i=1;i<=a.size();i++){
    		for(int j=1;j<=b.size();j++){
    			if(a[i-1]==b[j-1])dp[i][j]=dp[i-1][j-1];
    			else dp[i][j]=min(min(dp[i][j-1],dp[i-1][j]),dp[i-1][j-1])+1;
    		}
    	}
	}
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/192198931)。

---

## 作者：drah_yrev (赞：0)

双倍经验好诶！

从题面上来看，从一个字符串中删除一个字母，向一个字符串中插入一个字母，将一个字符串中的一个字母替换为另一个字母，这就是动态规划的**编辑距离**原题！

来让我们回顾一下编辑距离的做法：
$dp_{ij}$ 表示 $A$ 串前 $i$ 个字符改变到 $B$ 串前 $j$ 个字符所需要的最少次数。

几个行动的动态转移方程如下：

不动：无需改变，$dp_{i,j}=dp_{i-1,j-1}$。

删除：将 $A$ 串删除一个字符，$i$ 要减一，多一步操作：$dp_{i,j}=dp_{i-1,j}+1$。

添加：将 $A$ 串添加一个字符，相当于将 $B$ 串删除一个字符，$j$ 要减一，多一步操作：$dp_{i,j}=dp_{i,j-1}+1$。

改变：相当于承接将上一步状态再改变，多一步操作：$dp_{i,j}=dp_{i-1,j-1}+1$。

整合一下：

如果 $a_i=b_i$：$dp_{i,j}=dp_{i-1,j-1}$。
否则：$dp_{i,j}=\min(dp_{i-1,j-1}+1,dp_{i-1,j}+1,dp_{i,j-1}+1)$。

代码：


```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
char a[2005],b[2005];
int x,y,dp[2005][2005],k;
int main() {
    cin>>a>>b;
    x=strlen(a),y=strlen(b);
    for(int i=x;i>=1;i--) a[i]=a[i-1];
    for(int i=y;i>=1;i--) b[i]=b[i-1];
    for(int i=0;i<=x;i++) dp[i][0]=i;
    for(int i=0;i<=y;i++) dp[0][i]=i;
    for(int i=1;i<=x;i++){
        for(int j=1;j<=y;j++){
            k=1;
            if(a[i]==b[j]) k=0;
            dp[i][j]=min(min(dp[i-1][j]+1,dp[i][j-1]+1),dp[i-1][j-1]+k);
        }
    }
    cout<<dp[x][y];
    return 0;
}
```

---

## 作者：Beacon_wolf (赞：0)

## 题目思路
建议先做 [P2758 编辑距离](https://www.luogu.com.cn/problem/P2758)。

一个 dp 题。定义 $dp_{i,j}$ 为把字符串 $A$ 的前 $i$ 个字符转换成 $B$ 的前 $j$ 个字符的最小操作数。

考虑四种情况：

- 当 $i=j$ 时，如果 $a[i] == a[j]$，就不需要修改，$dp_{i,j}=dp_{i-1,j-1}$；否则，$dp_{i,j}=dp_{i-1,j-1}+1$。
- 当 $i<j$ 时，需要添加字符，$dp_{i,j}=dp_{i-1,j}+1$。
- 当 $i<j$ 时，需要删除字符，$dp_{i,j}=dp_{i,j - 1}+1$。

则有状态转移方程：
$dp_{i,j}=\min(dp_{i-1,j-1}+(a[i]!=b[j]),dp_{i-1,j}+1,dp_{i,j-1}+1)$。

边界条件：当一个字符串长度为 $0$，另一个字符串长度为 $x$ 时，则需要 $x$ 的花费。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
string a,b;
int dp[2010][2010];
void test(){
	cin >> a >> b;
	for(int i = 0;i <= a.size();i++){
		for(int j = 1;j <= b.size();j++){
			dp[i][j] = 0;
		}
	}
	for(int i = 0;i <= a.size();i++) dp[i][0] = i;
	for(int i = 1;i <= b.size();i++) dp[0][i] = i;
	for(int i = 1;i <= a.size();i++){
		for(int j = 1;j <= b.size();j++){
			dp[i][j] = min(min(dp[i - 1][j - 1] + (a[i - 1] != b[j - 1]),dp[i - 1][j] + 1),dp[i][j - 1] + 1);
		}
	}
	cout << dp[a.size()][b.size()] << endl ;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        test();
    }
    return 0;
}
```

---

## 作者：Firstly (赞：0)

## **解题思路：**

本题是一道编辑距离的模板题，要求两个字符串的编辑距离，需要运用到动态规划的思想。以下是编辑距离的详解。

设 $f_{i,j}$ 表示 $S$ 的前 $i$ 位和 $T$ 的前 $j$ 位对齐之后的最小代价，那么考虑一下情况：

- 当 $S_i=T_j$ 时，那么很明显，$f_{i,j}$ 就是 $f_{i-1,j-1}$。
- 当 $S_i\not=T_j$ 时，又有以下三种情况：

1. 和 $S_i=T_j$ 时类似，但是需要修改当前字符，此时 $f_{i,j}=f_{i-1,j-1}+1$。
2. 当 $S$ 的第 $i$ 位和 $T$ 的第 $j-1$ 位对齐时，那么需要添加或删去字符，此时 $f_{i,j}=f_{i,j-1}+1$。


3. 当 $S$ 的第 $i-1$ 位与 $T$ 的第 $j$ 位对齐时，与前一种情况类似，此时 $f_{i,j}=f_{i-1,j}+1$。

以上三种情况取最小值即为最优值。那么总结下来，编辑距离的动态转移方程为：

$$f_{i,j}=
\begin{cases}
f_{i-1,j-1}& S_i=T_j\\
\min(f_{i-1,j},f_{i,j-1},f_{i-1,j-1})+1& S_i\not=T_j\\
\end{cases}$$

## **Code:**

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int f[2005][2005];
string a,b;
int main(){
    int t;cin>>t;
    while(t--){
        cin>>a>>b;
        int lena=a.size();
        int lenb=b.size();
        for(int i=1;i<=lena;i++)f[i][0]=i;
        for(int i=1;i<=lenb;i++)f[0][i]=i;
        for(int i=1;i<=lena;i++)
            for(int j=1;j<=lenb;j++)
                if(a[i-1]==b[j-1])f[i][j]=f[i-1][j-1];
                else f[i][j]=min(min(f[i][j-1],f[i-1][j]),f[i-1][j-1])+1;
        cout<<f[lena][lenb]<<endl;
    }
    return 0;
}
```

---

## 作者：i_dont_know_who_am_i (赞：0)

**题意简介**

给定两个字符串 $a,b$，求两个字符的编辑距离。

**解题思路**

用 $f_{i,j}$ 表示字符串 $a$ 从下标为 $0$ 到 $i$ 的子串字符串 $b$ 从下标为 $0$ 到 $j$ 的子串的编辑距离。

考虑以下四种情况：

- 当直接对应时，很明显 $a_{i}=b_{j}$，表示当前位置是对齐的，因此 $f_{i,j}=f_{i-1,j-1}$；

- 当需要修改字符时，表示当前位置对齐，但 $a_i\not=b_j$，此时需要修改这一位，因此 $f_{i,j}=f_{i-1,j-1}+1$；

- 当 $a$ 的前 $i-1$ 位和 $b$ 的前 $j$ 位已经处理完，需要在 $b$ 中添加字符来对齐，因此 $f_{i,j}=f_{i-1,j}+1$；

- 当 $a$ 的前 $i$ 位和 $b$ 的前 $j-1$ 位已经处理完，需要在 $b$ 中删除字符来对齐，因此 $f_{i,j}=f_{i,j-1}+1$。

可以发现递推式：

$$f_{i,j}=\begin{cases}f_{i-1,j-1}\qquad\qquad\qquad\qquad\;\;\;\;\;\,(a_{i}=b{i})\\\min(f_{i-1,j-1},f_{i-1,j},f_{i,j-1})+1(a_{i}\not=b_{i})\end{cases}$$

边界条件为：

$$\begin{cases}f_{0,j}=j\\f_{i,0}=i\end{cases}$$

这是因为对于 $a$ 的前 $0$ 个字符，只能把 $b$ 中的字符全部删去，反之亦然。

**代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[2010][2010];
string a,b;
void solve(){
    cin >>a>>b;
    int lena=a.size();
    int lenb=b.size();
    for(int i=1;i<=lena;i++){
        dp[i][0]=i;
    }
    for(int i=1;i<=lenb;i++){
        dp[0][i]=i;
    }
    for(int i=1;i<=lena;i++){
        for(int j=1;j<=lenb;j++){
            if(a[i-1]==b[j-1]){
                dp[i][j]=dp[i-1][j-1];
            }else{
                dp[i][j]=min(min(dp[i][j-1],dp[i-1][j]),dp[i-1][j-1])+1;
            }
        }
    }
    cout<<dp[lena][lenb]<<endl;
}
int main() {
    int t;
    cin >>t;
    while(t--){
        solve();
    }
    return 0;
}
```

---

## 作者：_Sky_Dream_ (赞：0)

# [传送门](https://www.luogu.com.cn/problem/SP6219)

在集训时做过，原题是[编辑距离](https://www.luogu.com.cn/problem/P2758)，这题可以说是套餐了。

## 设状态：

$dp_{i,j}$ 表示从前 $i$ 个变换到前 $j$ 个所需最少步数。

所以，我们就要求出 ``dp[a.size()][b.size()]`` 是多少。

## 转移方程：

### 不变：$dp_{i,j}=dp_{i-1,j-1}$；

因为最后相等才不变，即为前面所需步数。

### 删除：$dp_{i,j}=dp_{i-1,j}+1$；

因为这要把 $a$ 的 $1$ 个字符删去，删除需要一次步数。

### 添加：$dp_{i,j}=dp_{i,j-1}+1$；

相当于把 $b$ 的 $1$ 个字符删去，需要一次步数。

### 替换：$dp_{i,j}=dp_{i-1,j-1}+1$；

因为就差 $1$ 个字符，就是前一个状态再加一（需要一次步数）。

没了，就这些。

敲代码吧。

AC Code:
```cpp
//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define itn int
#define tni int
#define tin int
#define nit int//防手滑
#define nti int
#define int long long
using namespace std;
string A,B;
char a[2005],b[2005];//等价于A，B
int dick[2005][2005];//相当于dp
int T;//T次操作
int dp(int i,int j){ //dp
    if(dick[i][j]!=-1) return dick[i][j]; //记忆化，省时间
    if(i==0) return dick[i][j]=j;//初始状态
    if(j==0) return dick[i][j]=i;
    int s=1;
    if(a[i]==b[j])s=0;//全等不用步数
    return dick[i][j]=min(min(dp(i-1,j)+1,dp(i,j-1)+1),dp(i-1,j-1)+s);//记忆化+dp
    //替换与全等放在最后，看是否加1
    //不懂的看转移方程
}
void Main(){
	memset(dick,-1,sizeof(dick));//初始化
	cin>>A>>B;//读入，由于洛谷不支持gets，所以转一下
	for(int i=0;i<A.size();++i)a[i+1]=A[i];
	for(int i=0;i<A.size();++i)b[i+1]=B[i];
    //A=" "+A;B=" "+B;
    //也可以这样写
    dp(A.size(),B.size());//开始dp
	cout<<dick[A.size()][B.size()]<<endl;//输出要换行
}
void Enchanted(){
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>T;
	while(T--)Main();//T组数据
	exit(0);
}
signed main(){Enchanted();}
```




---

