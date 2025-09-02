# Zebra-like Numbers

## 题目描述

我们称一个正整数为斑马数（zebra-like），如果它的二进制表示从最高有效位开始是交替的比特位，并且最低有效位等于 $1$。例如，数字 $1$、$5$ 和 $21$ 都是斑马数，因为它们的二进制表示 $1$、$101$ 和 $10101$ 满足要求，而数字 $10$ 不是斑马数，因为它的二进制表示 $1010$ 的最低有效位是 $0$。

我们定义一个正整数 $e$ 的斑马值为最小的整数 $p$，使得 $e$ 可以表示为 $p$ 个斑马数（可以相同也可以不同）的和。

给定三个整数 $l$、$r$ 和 $k$，计算满足 $l \le x \le r$ 且 $x$ 的斑马值等于 $k$ 的整数 $x$ 的数量。

## 说明/提示

- 在第一个测试用例中，有 $13$ 个符合条件的数字：$3, 7, 11, 15, 23, 27, 31, 43, 47, 63, 87, 91, 95$。每个数字都可以表示为 $3$ 个斑马数的和。
- 在第二个测试用例中，数字 $1$ 的斑马值为 $1$，因此输出 $1$。
- 在第四个测试用例中，区间 $[2, 10]$ 内没有数字的斑马值为 $100$，因此输出 $0$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
1 100 3
1 1 1
15 77 2
2 10 100
1234567 123456789101112131 12```

### 输出

```
13
1
3
0
4246658701```

# 题解

## 作者：heyicong (赞：7)

确简单的啊，可是自己就是想不到。

考虑计算一个数的斑马值。贪心地，尽量选大的斑马数减即可。

考虑 DP，设 $dp_{i, j}$ 表示 $[1, i]$ 中斑马值为 $j$ 的数的个数。那么显然有 $dp_{i, j} = dp_{i - mx, j - 1} + dp_{mx - 1, j}$，其中 $mx$ 是不大于 $i$ 的最大的斑马数。具体地，$dp_{i - mx, j - 1}$ 表示 $[mx, i]$ 中斑马值为 $j$ 的数的个数，$dp_{mx - 1, j}$ 表示 $1, mx - 1$ 中斑马值为 $j$ 的数的个数。

记搜即可。

---

## 作者：_O_v_O_ (赞：5)

我们发现，最多只有 $30$ 个 $\le 10^{18}$ 的「斑马数」。

我们设从小到大第 $i$ 个为 $t_i$，很显然，$t_i=t_{i-1}\times 4+1$。  
我们设 $x$ 可以表示为 $\sum_{i=1}^{30} v_i\times t_i$，我们发现，$\max\{v_i\}\le 4$，因为若一个 $v_i>4$，那么不如换成一个 $v_{i+1}$。  
同时，我们发现若有 $v_i=4$，那么 $v_{i-1}=v_{i-2}=\cdots =v_1=0$，因为如果有的话也可以换算成一个更高位的数。

那么我们不妨把 $x$ 放在一个特殊的进制下考虑，第 $i$ 位的进制为 $v_i$，然后我们就发现这个东西可以数位 dp，具体的，我们设 $dp_{pos,limit_1,sum,limit_2}$ 为当前来到了 $pos$ 位，有/没有抵着数位，当前的数位和，前面是否有 $4$，的方案数，转移是容易的。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int l,r,k;
int t[40],dp[40][2][90][2],dig[40];

int dfs(int pos,bool limit,int sum,bool limit2){
	if(sum>k) return 0;
	if(pos==0) return sum==k;
	if(dp[pos][limit][sum][limit2]!=-1) return dp[pos][limit][sum][limit2];
	int up;
	if(limit2) up=0;
	else if(limit) up=dig[pos];
	else up=4;
	int ans=0;
	for(int i=0;i<=up;i++){
		ans+=dfs(pos-1,(limit&&i==up),sum+i,(limit2||i==4));
	}
	return dp[pos][limit][sum][limit2]=ans;
}

int solve(int x){
	memset(dp,-1,sizeof dp);
	int cnt=30;
	for(int i=30;i>=1;i--){
		dig[i]=0;
		while(x>=t[i]) x-=t[i],dig[i]++;
	}
	return dfs(30,1,0,0);
} 

signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	t[1]=1;for(int i=2;i<=30;i++) t[i]=4*t[i-1]+1;
	int T;cin>>T;while(T--){
		cin>>l>>r>>k;
		cout<<solve(r)-solve(l-1)<<endl;
	}
	return 0;
}

```

---

## 作者：dayz_break404 (赞：2)

一道不那么板的数位 DP，感觉思路很清奇。

显然斑马数不超过 $30$ 个，记斑马数为 $num_i$，那么答案是一个多项式的形式，考虑将其转化为进制的形式。

考虑这个进制，由于斑马值是最小的系数和，从高位到低位贪心一定是最优的。并且由于有 $num_i=num_{i-1}\times 4+1$，所以每一位上的数值都不大于 $4$，并且如果有一位为 $4$，则它的更低位一定是 $0$。

那么 DP 状态为 $dp_{i,j,lim1,lim2}$，表示当前 $pos$ 位，数位和为 $j$，是否达到数值限制，是否出现了 $4$，转移即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*f;
}
bool mbs;
ll t,l,r,k,num[32],val[32],dp[32][100][2][2];
ll dfs(int pos,int sum,int lim1,int lim2){
	if(!pos) return sum==k;
	if(dp[pos][sum][lim1][lim2]!=-1) return dp[pos][sum][lim1][lim2];
	int up=4;ll res=0;
	if(lim2) up=0;
	else if(lim1) up=val[pos];
	for(int i=0;i<=up;i++) res+=dfs(pos-1,sum+i,lim1&&i==val[pos],lim2||i==4);
	return dp[pos][sum][lim1][lim2]=res;
}
inline ll get_val(ll x){
	for(int i=30;i>=1;i--) val[i]=(x/num[i]),x-=(x/num[i])*num[i];
	memset(dp,-1,sizeof(dp));
	return dfs(30,0,1,0);
}
inline void solve(){
	l=read(),r=read(),k=read();
	printf("%lld\n",get_val(r)-get_val(l-1));
}
bool mbt;
int main(){
//	cout<<(&mbs-&mbt)/1024.0/1024.0<<endl;
	num[1]=1;
	for(int i=2;i<=30;i++) num[i]=num[i-1]*4+1;
	t=read();
	while(t--) solve();
	return 0;
}
```

---

## 作者：zhangbo1000 (赞：0)

首先，容易发现 $10^{18}$ 以内的 Zebra-like number 就 $30$ 个，设从小到大第 $i$ 个为 $a_i$，由定义易得 $a_i=4a_{i-1}+1$。

然后发现问题：用大的 $a_i$ 总是不劣的，因为我们省掉了 $4\times a_{i-1}$，而“去掉”$1$ 带来的影响无非就是拆掉一个 $a_j$ 换成 $4\times a_{j-1}$。

所以“计算一个数的 zebra value”这个问题具有贪心性质。

考虑记忆化搜索，设 $v_{i,j}$ 表示 $i$ 以内 zebra value 为 $j$ 的数的个数，那么设 $a_x$ 为小于 $i$ 的最大的 Zebra-like number，则 $v_{i,j}=v_{i-a_x,j-1}+v_{a_x,j}$，这个式子的含义是：$[a_x,i]$ 以内的数的 zebra value 可以先贪心的除去一个最大值，变为 $[0,i-a_x]$ 内的数，再加一，其余的数直接递归处理。$a_x$ 不会小于 $\frac{i}{4}$，$a_x-1={4a_{x-1}}$，所以两次递归后 $i$ 必然缩小最少 $\frac{1}{4}$，递归层数是 $O(\log n)$ 的，理论上能卡到 $O(r\log r)$ 直接 $10^{20}$ TLE 飞，但实际上完全跑不满，再加上记忆化，实际快的飞起，卡满在 CF 评测机上大概 $60\operatorname{ms}$。

[代码及评测记录。](https://codeforces.com/contest/2086/submission/317550743)

### 关于复杂度

“跑不满”当然是一个很不严谨的说法，所以接下来让我们具体证一下。

首先，根据上面的贪心性质，易知一个数最多由 $30\times 4=120$ 个 Zebra-like number 组成（实际上这个界也不满），更严谨的说，是 $O(\log V)$ 个（其中 $V$ 为值域），因为这个界内最多 $O(\log V)$ 个 Zebra-like number，一个数中每个不超过 $4$ 次。

所以 $k$ 的（有意义的）范围是 $O(\log V)$ 的，具体多少就不算了。

对于 $v_{a_x-1,j}$，我们一旦算出了所有 $v_{a_x-1,j}$，这部分就 $O(1)$ 了，所以我们每次实际上相当于只往一侧递归，$x,j$ 的范围又是 $O(\log V)$ 的，所以我们的总复杂度实际上控制在了 $O(\log ^2V)$ 左右。

---

