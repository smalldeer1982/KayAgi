# ICPC Team Strategy

## 题目描述

ICPC（International Collegiate Programming Contest，国际大学生程序设计比赛），就像你所知道的那样，是大学生抱团参加的程序设计比赛。各个团队由 $3$ 个人组成，而他们将会解决一些程序设计问题。

安迪，布迪和坎达拉计划抱团参加 ICPC，至于团队策略，他们仨想到一个简易策略：

+ 在五个小时的比赛的前二十分钟，他们想要读所有的题目，而后他们三个人每个人给每一道题目标一个数字，即某个人 AC 某道题的最小时间，并且一定会 AC。
+ 每个队伍只有一台电脑，因而让一个队伍同时肝两道题是不可能的。
+ 为避免大脑烧毁或心肺骤停（他们比赛过太多次了），他们决定在每道题后交换角色，这样没有人会连续做两道题目。
+ 他们想要尽量多做题目，做题的顺序则无关紧要。

## 样例 #1

### 输入

```
2
3
100 100 80
190 120 90
120 150 100
4
50 20 300 300
200 100 30 250
140 120 100 100```

### 输出

```
2
4```

# 题解

## 作者：AlexandreLea (赞：4)

## 题目大意

三人打 ICPC，有 $n$ 道题目，每个人只能连续做一道题，并且每个人对于每道题可以花费一定时间 AC。求在 $280$ 分钟内能 AC 多少道题目。

## 题目思路

一开始的想法是用 dfs 求得最多能 AC 多少道题目，然而不幸的是，$12!\times 3^{12}$ 的计算次数让我们应付不过来。

因为题目的数量非常之少，并且解题的人也非常之少，因此我们当然可以用动态规划。接下来我们看看如何设状态。

首先，由于我们不能重复解一道题，因此我们需要把已经解完了的题目压进一个 int 里；而后，由于一个人不能连续解两道题目，因此我们需要保存最后一个解题的人；由于对时间有限制，因此，我们需要一维保存时间。

那么怎么转移呢？由于 dfs 的做法已经给了我们提示，我们当然可以采用记忆化转移，然后增加一个表来储存一些计算出来的数据。你可以对接下来解题的人和要解的题目进行枚举，而后进行记忆化搜索即可。

请注意，不要使用 `map`，因为这样会 TLE。代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t[4][15],memo[1<<15][4][300];
int dp(int sol,int las,int tot){
    if(tot>=280) return 0;
    if(las!=0&&memo[sol][las][tot]!=-1) return memo[sol][las][tot];
    // for(int i=n;i>=1;i--) cout<<!!(sol&(1<<(i-1)));
    // cout<<" "<<las<<" "<<tot<<endl;
    int ans=0;
    for(int i=1;i<=3;++i) if(i!=las){
        for(int j=1;j<=n;++j) if((sol&(1<<(j-1)))==0&&tot+t[i][j]<=280){
            ans=max(ans,1+dp(sol|(1<<(j-1)),i,tot+t[i][j]));
        }
    }
    if(las==0) return ans;
    return memo[sol][las][tot]=ans;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=3;++i) for(int j=1;j<=n;++j) cin>>t[i][j];
        memset(memo,-1,sizeof(memo));
        cout<<dp(0,0,0)<<endl;
    }
    return 0;
}
```

**EOF**

---

## 作者：coding_goat (赞：1)

[可能更好的阅读体验](https://www.cnblogs.com/CodingGoat/p/18474031)

看到 $n \le 12$，考虑搜索。但是过不去，于是加上记忆化搜索即可。因为 $n$ 不大，选了什么题可以状压进一个数里面。我们用二进制的第 $i$ 位表示第 $i$ 个物品是否被选择。

注意如果你在搜索的时候不判是否满足时间，那么你在 dfs 函数开头判断超时应该返回 $-1$ 及以下。

剩下的按照题意模拟即可。

代码：

```cpp
int n,a[4][maxn];
int ans;
int f[(1<<12)+5][305][4];
int dfs(int S,int t,int lst) {
	if(t>300) return -114514;
	if(f[S][t][lst]!=-1) return f[S][t][lst];
	int ans=0;
	For(j,1,3) {
		if(j!=lst) {
			For(i,1,n) {
				if(!((S>>(i-1))&1))
					ans=max(ans,1+dfs((S|(1<<(i-1))),t+a[j][i],j));
			}
		}
	}
	return (f[S][t][lst]=ans);
}
void work() {
	ans=0;
	in1(n);
	For(i,1,3) For(j,1,n) in1(a[i][j]);
	mem(f,-1);
	cout<<dfs(0,20,0)<<'\n';
}
```

---

## 作者：Big_Dinosaur (赞：0)

状压。

将三个人记为 $1,2,3$。

若第 $i$ 题通过，则对应状态二进制位中第 $i$ 位为 $1$。

设状态为 $n$，目前最后一题由 $j$ 完成的最少用时为 $dp_{n,j}$，则若 $dp_{n,j}\le 280$，该解合法，完成了 $\operatorname{popcount}(n)$ 题。

不难列出转移方程：

$$dp_{i,1}=\max(\max_{i \operatorname{and} 2^j = 2^j} dp_{i\oplus 2^j,2},\max_{i \operatorname{and} 2^j = 2^j} dp_{i\oplus 2^j,3})$$

$$dp_{i,2}=\max(\max_{i \operatorname{and} 2^j = 2^j} dp_{i\oplus 2^j,1},\max_{i \operatorname{and} 2^j = 2^j} dp_{i\oplus 2^j,3})$$

$$dp_{i,3}=\max(\max_{i \operatorname{and} 2^j = 2^j} dp_{i\oplus 2^j,1},\max_{i \operatorname{and} 2^j = 2^j} dp_{i\oplus 2^j,2})$$

```cpp
#include<bits/stdc++.h>
#define int long long
#define ri register int
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second
using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
		#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
 	#else
		#define gh() getchar()
	#endif
	inline int r(){
		int o=1,p=0;
		char q=gh();
		while(q<'0'||q>'9'){if(q=='-')o=-1;q=gh();}
		while(q>='0'&&q<='9'){p=(p<<1)+(p<<3)+(q^48);q=gh();}
		return o*p;
	}
	inline char gc(){char q=gh();while(q<=' ')q=gh();return q;}
	inline string gs(){string s="";char g=gh();while(g<=' ')g=gh();while(g>' '){s+=g;g=gh();}return s;}
	inline void Wi(int E){
		if(E==0)return;if(E<0){E=-E;putchar('-');}
		Wi(E/10);putchar((E%10)^48);
	}
	inline void wln(int J){if(J==0)putchar('0');else Wi(J);putchar('\n');}
	inline void w(int J){if(J==0)putchar('0');else Wi(J);}
	inline void ww(int J){if(J==0)putchar('0');else Wi(J);putchar(' ');}
}
using namespace IO;
namespace D1n0{
	int dp[(1<<12)+9][4];
	int T,a[4][20],n,Ans;
	inline int cnt(int x){
		int S=0;
		while(x){
			if(x&1)++S;
			x>>=1;
		}
		return S;
	}
	inline void zyt(){
		T=r();
		while(T--){
			n=r();
			memset(dp,1,sizeof dp);
			dp[0][1]=dp[0][2]=dp[0][3]=0;
			Ans=0;
			for(ri i=1;i<=3;++i){
				for(ri j=1;j<=n;++j)a[i][j]=r();
			}
			for(ri i=1;i<(1<<n);++i){
				for(ri k=1;k<=n;++k)if((i>>k-1)&1){
					dp[i][1]=min(dp[i][1],min(dp[i^(1<<k-1)][2],dp[i^(1<<k-1)][3])+a[1][k]);
					dp[i][2]=min(dp[i][2],min(dp[i^(1<<k-1)][1],dp[i^(1<<k-1)][3])+a[2][k]);
					dp[i][3]=min(dp[i][3],min(dp[i^(1<<k-1)][1],dp[i^(1<<k-1)][2])+a[3][k]);
				}
				if(min(min(dp[i][1],dp[i][2]),dp[i][3])<=280)Ans=max(Ans,cnt(i));
			}
			wln(Ans);
		}
	}
}
signed main(){
	D1n0::zyt();
}
```

---

