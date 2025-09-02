# [ABC375E] 3 Team Division

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc375/tasks/abc375_e

$ N $ 人の人がおり、$ 3 $ つのチームに分かれています。

人には $ 1,\ 2,\ \ldots,\ N $ の番号、チームには $ 1,\ 2,\ 3 $ の番号がついており、現在人 $ i $ はチーム $ A_i $ に所属しています。

各人には**強さ**という値が定まっており、人 $ i $ の強さは $ B_i $ です。また、チームの**強さ**をチームに所属する人の強さの和として定めます。

$ 0 $ 人以上の人が所属するチームを変更することですべてのチームの強さが等しくなるようにできるか判定してください。すべてのチームの強さが等しくなるようにできる場合は所属するチームを変更する人数として考えられる最小値を求めてください。

ただし、チーム $ 1,\ 2,\ 3 $ の他に新たにチームを作ることはできません。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 100 $
- $ A_i\ \in\ \lbrace\ 1,\ 2,\ 3\ \rbrace $
- 各 $ x\ \in\ \lbrace\ 1,\ 2,\ 3\ \rbrace $ に対し、ある $ i $ が存在して $ A_i\ =\ x $
- $ 1\ \leq\ B_i $
- $ \displaystyle\sum_{i\ =\ 1}^{N}\ B_i\ \leq\ 1500 $
- 入力される値はすべて整数
 
### Sample Explanation 1

人 $ 1 $ がチーム $ 3 $、人 $ 4 $ がチーム $ 2 $ へと所属するチームを変更することですべてのチームの強さが $ 8 $ となります。

## 样例 #1

### 输入

```
6
1 2
2 5
1 5
3 3
1 3
3 6```

### 输出

```
2```

## 样例 #2

### 输入

```
4
1 1
1 2
2 3
3 4```

### 输出

```
-1```

## 样例 #3

### 输入

```
3
1 1
2 1
3 1```

### 输出

```
0```

## 样例 #4

### 输入

```
12
2 5
1 4
3 3
2 3
3 9
1 2
2 2
3 9
2 6
1 9
1 1
3 1```

### 输出

```
3```

# 题解

## 作者：__Allen_123__ (赞：31)

你正在备战一场想象学竞赛。

> 你有 $n$ 块完整的空闲时间，长度为 $b_i$。初始时，每个时间都被提前安排了其用途 $a_i$，用 $1,2,3$ 来表示：
>
> 1. 学习想象学竞赛知识点；
> 2. 参加想象学模拟竞赛；
> 3. 通过 Grosphi 这款应用锻炼自己的想象能力。
>
> 你想知道，在这些完整的空闲时间不被拆开的情况下，能否改变一些时间原有的用途，使学习知识点、参加模拟赛、打开 Grosphi 的时间相同。如果可以做到，最少需要改变多少块时间的用途。

你马上想到，如果所有时间之和（记为 $sum$）不能被 $3$ 整除，那么只能让做每件事情的总时间为小数，显然不能做到。如果可以被 $3$ 整除，那做每件事情的时间就分别为 $\frac{sum}{3}$。

你考虑进行 dp。设 $dp_{i,j,k}$ 代表考虑了前 $i$ 段时间，分配给学习知识点、打模拟赛的时间分别为 $j,k$，则分配给 Grosphi 的时间显然可求。

考虑到第 $i$ 片时间时，你会枚举它分别用作三个用途对应的 dp 值。根据题意，你想到：

- 当用途为 $1$ 时，$dp_{i,j,k}=dp_{i-1,j-b_i,k}+[a_i\ne 1](j\ge b_i)$；
- 当用途为 $2$ 时，$dp_{i,j,k}=dp_{i-1,j,k-b_i}+[a_i\ne 2](j\ge b_i)$；
- 当用途为 $3$ 时，$dp_{i,j,k}=dp_{i-1,j,k}+[a_i\ne 3](sum-i-j\ge b_i)$。

根据题意，你进行了 dp，并合理地安排了自己的时间。[你的 AC 代码](https://atcoder.jp/contests/abc375/submissions/58713140)。

合理地安排了时间……是吗？

面对着自己不堪入目的成绩，你再次陷入了沉思。你对自己的时间安排十分满意，但这一切似乎只是表象。使三者的时间都相等，不尽科学，甚至有一部分时间还被用来浪费。纵观这一切，你水平之低源自于你的不合理的安排，才导致了如今的结果。你想回到过去重新来过，但一切已为时已晚。走到死胡同的尽头，你才顿悟：学习和练习才能充分提升自己的想象学竞赛水平。

所以，菜就多练。

---

## 作者：Binah_cyc (赞：5)

简单 DP，但是赛时没调出来，洪文了。

这个题看起来就很像 DP，我们尽量往这方面想。

首先，如果所有的能力总和不是 $3$ 的倍数时，显然无解。

设 $dp_{i,x,y,z}$ 表示考虑到第 $i$ 个数，三个队伍的能力值分别为 $x,y,z$，转移式子显然，分讨第 $i$ 个人会去哪一个队伍里面即可。

但是这样是 $O(n \times (\frac{sum}{3})^3)$，其中 $sum$ 表示 $\displaystyle \sum_{i=1}^{n} B_i$。但是这样的复杂度显然过不了，考虑优化。

我们注意到，当前两个队伍的能力值已经确定之后，第三个队伍的能力值也就确定了，因为能力值的总和是一定的。所以，$z$ 这一维就是没有用的，我们可以直接把它省略掉。这就是动态规划优化中的**状态优化**，或者**删除无用状态**。

这样，我们就可以设出新的状态了，设 $dp_{i,x,y}$ 表示考虑到第 $i$ 个数，前两个队伍的的能力值为 $x,y$，第三个队伍的能力值就是 $sum_k-x-y$，其中 $sum$ 数组表示 $B$ 数组的前缀和，转移的时候分讨第 $i$ 个人会去哪一个队伍里面，转移不难。

代码：
```c
// Problem: E - 3 Team Division
// Contest: AtCoder - Panasonic Programming Contest 2024（AtCoder Beginner Contest 375）
// URL: https://atcoder.jp/contests/abc375/tasks/abc375_e
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// Author: Binah_cyc

#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,sum,a[105],b[105],num[105];
int dp[105][505][505];
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i],sum+=b[i],num[i]=num[i-1]+b[i];//num表示前缀和数组
	if(sum%3) cout<<-1,exit(0);//判无解
	sum/=3;//每一个队伍能分得的能力值
	memset(dp,0x3f,sizeof(dp));
	dp[0][0][0]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=sum;j++)
		{
			for(int k=0;k<=sum;k++)
			{
				//直接使用逻辑表达式可以省很多的判断
				if(j>=b[i]) dp[i][j][k]=min(dp[i][j][k],dp[i-1][j-b[i]][k]+(a[i]!=1));//去第一个队伍
				if(k>=b[i]) dp[i][j][k]=min(dp[i][j][k],dp[i-1][j][k-b[i]]+(a[i]!=2));//去第二个队伍
				if(num[i]-j-k>=b[i]) dp[i][j][k]=min(dp[i][j][k],dp[i-1][j][k]+(a[i]!=3));//去第三个队伍
			}
		}
	}
	if(dp[n][sum][sum]<=n) cout<<dp[n][sum][sum];
	else cout<<-1;//在这里也要判无解，我就是在这里被卡掉的
	return 0;
}
```

---

## 作者：liuziqin (赞：3)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc375_e)

## 思路

由于总量保持不变，因此 $\sum_{i=1}^nB_i$ 一定要被 $3$ 整除。

由于 $\sum_{i=1}^nB_i$ 很小，考虑 $dp$ 。设 $f_{i,j,k}$ 为考虑到第 $i$ 个，队 $1$ 的实力为 $i$ ，队 $2$ 的实力为 $j$ 所需的变化次数。

接下来考虑如何转移 $dp$ 方程。

若 $A_i=1$ ，则 
$$
f_{i,j+B_i,k}=f_{i-1,j,k}
\\\\
f_{i,j,k+B_i}=f_{i-1,j,k}+1
\\\\
f_{i,j,k}=f_{i-1,j,k}+1
$$ 

若 $A_i=2$ ，则 

$$
f_{i,j+B_i,k}=f_{i-1,j,k}+1
\\\\
f_{i,j,k+B_i}=f_{i-1,j,k}
\\\\
f_{i,j,k}=f_{i-1,j,k}+1
$$ 

若 $A_i=3$ 则 

$$
f_{i,j+B_i,k}=f_{i-1,j,k}+1
\\\\
f_{i,j,k+B_i}=f_{i-1,j,k}+1
\\\\
f_{i,j,k}=f_{i-1,j,k}
$$ 

最后取答案 $\displaystyle f_{n,\frac{sum}{3},\frac{sum}{3}}$ 即可。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
int dp[105][505][505]; 
const int INF=0x3f;
int t[105],a[105];
int main(){
	memset(dp,INF,sizeof(dp));
	int n;
	cin>>n;
	dp[0][0][0]=0;
	int sum=0;
	for(int i=1;i<=n;i++){
		cin>>t[i]>>a[i];
		sum+=a[i];
	}
	if(sum%3!=0){
		cout<<"-1\n";
		return 0;
	}//特判
	for(int i=1;i<=n;i++){
		for(int j=0;j<=500;j++)
		for(int k=0;k<=500;k++){
			if(t[i]==1){
				if(j+a[i]<=500)dp[i][j+a[i]][k]=min(dp[i][j+a[i]][k],dp[i-1][j][k]);
				if(k+a[i]<=500)dp[i][j][k+a[i]]=min(dp[i][j][k+a[i]],dp[i-1][j][k]+1);
				dp[i][j][k]=min(dp[i][j][k],dp[i-1][j][k]+1);
			}
			else if(t[i]==2){
				if(j+a[i]<=500)dp[i][j+a[i]][k]=min(dp[i][j+a[i]][k],dp[i-1][j][k]+1);
				if(k+a[i]<=500)dp[i][j][k+a[i]]=min(dp[i][j][k+a[i]],dp[i-1][j][k]);
				dp[i][j][k]=min(dp[i][j][k],dp[i-1][j][k]+1);
			}
			else{
				if(j+a[i]<=500)dp[i][j+a[i]][k]=min(dp[i][j+a[i]][k],dp[i-1][j][k]+1);
				if(k+a[i]<=500)dp[i][j][k+a[i]]=min(dp[i][j][k+a[i]],dp[i-1][j][k]+1);
				dp[i][j][k]=min(dp[i][j][k],dp[i-1][j][k]);
			}//dp方程
		}
	}
	if(dp[n][sum/3][sum/3]>1e5){
		cout<<"-1\n";
		return 0;
	}//判断是否有解
	cout<<dp[n][sum/3][sum/3]<<"\n";//输出
	return 0;
}
```

---

## 作者：hjyowl (赞：2)

### 题目大意

有 $n$ 个人，每个人最先都有一个小组，每个人有一个分数 $b_i$，现在要求把他们重新划分，是的小组内的总分数都相同，只有 $3$ 个小组，如果无解，输出 ```-1```。

### 思路

考虑动态规划算法。

定义 $f_{i,j,k}$ 表示前面 $i$ 个，第一组的总和是 $j$，第二组是 $k$ 的最小值。

很明显，有以下几条状态转移：

```cpp
if (j >= b[i]){
					f[i][j][k] = min(f[i][j][k],f[i - 1][j - b[i]][k] + (a[i] != 1));
				}
				if (k >= b[i]){
					f[i][j][k] = min(f[i][j][k],f[i - 1][j][k - b[i]] + (a[i] != 2));
				}
				f[i][j][k] = min(f[i][j][k],f[i - 1][j][k] + (a[i] != 3));
```

初始值的话，很明显 $f_{0,0,0}=0$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
const int N = 100010;
vector<int>x[4];
bool debug = 0;
int f[510][510][510];
int a[N],b[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	int res = 0;
	int s1 = 0,s2 = 0;
	for (int i = 1; i <= n; i ++ ){
		cin >> a[i] >> b[i];
		res += b[i];
		if (a[i] == 1){
			s1 ++ ;
		}
		if (a[i] == 2){
			s2 ++ ;
		}
	}
	if (res % 3 != 0){
		cout << -1;
		return 0;
	}
	memset(f,0x3f,sizeof f);
	f[0][0][0] = 0;
//	f[1][s1][s2] = 0;
	for (int i = 1; i <= n; i ++ ){
		for (int j = 0; j <= 500; j ++ ){
			for (int k = 0; k <= 500; k ++ ){
				if (j >= b[i]){
					f[i][j][k] = min(f[i][j][k],f[i - 1][j - b[i]][k] + (a[i] != 1));
				}
				if (k >= b[i]){
					f[i][j][k] = min(f[i][j][k],f[i - 1][j][k - b[i]] + (a[i] != 2));
				}
				f[i][j][k] = min(f[i][j][k],f[i - 1][j][k] + (a[i] != 3));
			}
		}
	}
	if (f[n][res / 3][res / 3] > 0x3f3f3f3f / 2){
		cout << -1 << endl;
		return 0;
	}
	cout << f[n][res / 3][res / 3];
	return 0;
}
```

---

## 作者：Liuhy2996 (赞：1)

## 思路
$dp_{i,j,k}$ 表示考虑前 $i$ 个人的换队情况，使第一队强度为 $j$，第二队强度为 $k$ 最小换队次数。转移时枚举第 $i$ 个人最终在哪队就行。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n,sum,c[N],a[N],b[N],dp[105][1505][1505];
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i]>>b[i],c[a[i]]+=b[i],sum+=b[i];
	if(sum%3) return cout<<-1,0;
	for(int i=0;i<=n;++i)
		for(int j=0;j<=sum;++j)
			for(int k=0;k<=sum;++k) dp[i][j][k]=1e9;
	dp[0][c[1]][c[2]]=0;
	for(int i=1;i<=n;++i)
		for(int j=0;j<=sum;++j)
			for(int k=0;k<=sum;++k){
				int x[4]={0,j,k,sum-j-k};
				for(int p=1;p<=3;++p){
					x[p]-=b[i],x[a[i]]+=b[i];
					if(x[1]>=0&&x[2]>=0&&x[3]>=0) dp[i][j][k]=min(dp[i][j][k],dp[i-1][x[1]][x[2]]+(a[i]!=p));
					x[p]+=b[i],x[a[i]]-=b[i];
				}
			}
	if(dp[n][sum/3][sum/3]<1e9) cout<<dp[n][sum/3][sum/3];
	else cout<<-1;
	return 0;
}
```

---

## 作者：daitangchen2008 (赞：0)

## 题目大意
一共三组，每个队员属于一个组，每个队员有一个能力值。问是否有方案使得这些队员的组经过调换后能使每个组能力值总和一样。如果能输出最少调几个人，不能输出 $-1$ 。  
## 分析：
一眼背包。  
把能力值看成背包空间，把是否在这个组里看成一个转移代价。注意直接表示三个组背包会T，需要把第三个组压掉。于是可以令 $dp_{i,j,k}$ 为分配到第 $i$ 组时第一个组 $j$ 人第二个组 $k$ 人的最小代价。然后用背包转移即可。具体看代码。  
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=205;
struct node
{
	int a;
	int b;
}t[N];
int dp[105][505][505];
signed main()
{
	int n,sum=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>t[i].a>>t[i].b;
		sum+=t[i].b;
	}
	if(sum%3!=0)
	{
		cout<<-1<<endl;
		return 0;
	}
	int s=sum/3;
	for(int k=0;k<=n;k++)
	for(int i=0;i<=s;i++)
		for(int j=0;j<=s;j++)
				dp[k][i][j]=1e9;
	dp[0][0][0]=0;
	for(int i=1;i<=n;i++)
	{
		int aa,bb,cc;
		aa=bb=cc=1;
		if(t[i].a==1) aa=0;
		if(t[i].a==2) bb=0;
		if(t[i].a==3) cc=0;
		for(int j=s;j>=0;j--)
			for(int k=s;k>=0;k--)
			{
				int ans=1e9;
				if(j>=t[i].b)
				ans=min(ans,dp[i-1][j-t[i].b][k]+aa);
				if(k>=t[i].b)
				ans=min(ans,dp[i-1][j][k-t[i].b]+bb);
				ans=min(ans,dp[i-1][j][k]+cc);
				dp[i][j][k]=ans;
			}
	}
	if(dp[n][s][s]!=1e9)
		cout<<dp[n][s][s]<<endl;
	else
		cout<<-1<<endl;
	return 0;
}
```

---

## 作者：hzxphy (赞：0)

## Deepl 翻译 
有 $N$ 人分成三个小组。

人数编号为 $1, 2, \dots, N$，团队编号为 $1, 2, 3$。目前，$i$ 属于 $A_i$ 小组。

每个人都有一个叫做**强度**的值，人 $i$ 的强度为 $B_i$。一个团队的**强度**被定义为其成员强度的总和。

确定是否可能有零个或更多的人交换团队，从而使所有团队的实力相等。如果可能，求最少需要多少人换队才能达到这个目的。

除了 $1$、$2$、$3$ 以外，您不能创建新的团队。
## 思路
有 $dp[i][j][k]\gets$ 一组和为 $i$，二组和为 $j$，三组和为 $k$ 的交换最小值。

首先显然不行。

其次发现 $i+j+k=\sum\limits_{i=1}^nb_i$。

可以将第三位压掉,同时剩下的两个维度可以变成$\sum\limits_{i=1}^nb_i /3$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100;
const int MAXSC3=500;
int n;
int a[MAXN+1];
int b[MAXN+1];
int dp[2][MAXSC3+1][MAXSC3+1];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d%d",a+i,b+i);
    int sc3=0;
    for(int i=1;i<=n;i++)sc3+=b[i];
//    cout<<sc3<<"***\n";
    if(sc3%3!=0){
        printf("-1\n");
        return 0;
    }
    sc3/=3;
    memset(dp,0x3f,sizeof dp);
    dp[0][0][0]=0;
    for(int i=1;i<=n;i++){
        memset(dp[1],0x3f,sizeof dp[1]);
        for(int j=0;j<=500;j++){
            for(int k=0;k<=500;k++){
                if(a[i]==1){
                    if(j+b[i]<=500)dp[1][j+b[i]][k]=min(dp[1][j+b[i]][k],dp[0][j][k]);
                    if(k+b[i]<=500)dp[1][j][k+b[i]]=min(dp[1][j][k+b[i]],dp[0][j][k]+1);
                    dp[1][j][k]=min(dp[1][j][k],dp[0][j][k]+1);
                }
                else if(a[i]==2){
                    if(j+b[i]<=500)dp[1][j+b[i]][k]=min(dp[1][j+b[i]][k],dp[0][j][k]+1);
                    if(k+b[i]<=500)dp[1][j][k+b[i]]=min(dp[1][j][k+b[i]],dp[0][j][k]);
                    dp[1][j][k]=min(dp[1][j][k],dp[0][j][k]+1);
                }
                else{
                    if(j+b[i]<=500)dp[1][j+b[i]][k]=min(dp[1][j+b[i]][k],dp[0][j][k]+1);
                    if(k+b[i]<=500)dp[1][j][k+b[i]]=min(dp[1][j][k+b[i]],dp[0][j][k]+1);
                    dp[1][j][k]=min(dp[1][j][k],dp[0][j][k]);
                }
//                cout<<dp[1][j][k]<<' ';
            }
//            cout<<"***\n";
        }
//        cout<<"--------------------\n";
        memcpy(dp[0],dp[1],sizeof dp[1]);
    }
    cout<<(dp[0][sc3][sc3]==0x3f3f3f3f?-1:dp[0][sc3][sc3]);
    return 0;
}

```

---

