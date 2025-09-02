# [ICPC 2020 Shanghai R] Sum of Log

## 题目描述

给定两个非负整数 $X$ 和 $Y$，计算以下值：  
$$ \sum_{i=0}^{X}\sum_{j=[i=0]}^{Y}[i\&j=0]\lfloor\log_2(i+j)+1\rfloor $$  
对 $10^9+7$ 取模，其中  
- $\&$ 表示按位与运算；  
- $[A]$ 的值为 1 如果 $A$ 为真，否则为 0；  
- $\lfloor x\rfloor$ 表示不大于 $x$ 的最大整数。

## 说明/提示

对于第一个测试用例：  
- 两个 $(i,j)$ 对使得和增加 1：$(0, 1), (1, 0)$  
- 六个 $(i,j)$ 对使得和增加 2：$(0, 2), (0, 3), (1, 2), (2, 0), (2, 1), (3, 0)$  

所以答案是 $1\times 2 + 2\times 6 = 14$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3
3 3
19 26
8 17```

### 输出

```
14
814
278```

# 题解

## 作者：int_R (赞：4)

[原题链接](https://www.luogu.com.cn/problem/P9821)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/P9821.html)

题意，求：
$$ \sum_{i=0}^{X}\sum_{j=[i=0]}^{Y}[i\operatorname{bitand}j=0]\lfloor\log_2(i+j)+1\rfloor $$

为简洁，记 $\lg(x)=\lfloor\log_2(x)\rfloor,n=\max(X,Y)$

由于 $i\&j=0$ 则 $i+j=i\operatorname{bitor}j$ 则 $\lg(i+j)=\lg(i\operatorname{bitor}j)=\lg(\max(i,j))$。

考虑枚举 $\lg(\max(i,j))$：

$$\sum_{k=0}^{\lg(n)} (k+1)\sum_{i=0}^{X}\sum_{j=0}^{Y}[i\operatorname{bitand}j=0][\lg(\max(i,j))=k]$$

考虑枚举 $k$，后面那一坨相当于计数。

考虑 $[i\&j=0]$ 的意义是 $i$ 与 $j$ 每一二进制位上不能同时为 $1$。

考虑 $[\lg(\max(i,j))=k]$ 的意义是 $i$ 与 $j$ 的第 $k$ 二进制位上必须有且仅有一个数为 $1$ 且第 $k$ 位以上全为 $0$。

这个东西就可以数位 DP 统计，记 $f_{pos,0/1,0/1}$ 为考虑第 $pos$ 位时，$i,j$ 是否被限制（这个“被限制”类比数位 DP）时的方案数。 

状态数 $O(\log n)$ 级别，转移 $O(1)$ 级别，时间复杂度 $O(T\log n)$。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
const int MOD=1e9+7;
int T,X,Y;long long f[50][2][2],ANS;
int dfs(int pos,bool a,bool b)//a,b 表示第一个数和第二个数是否被限制
{
    if(pos<0) return 1;
    if(f[pos][a][b]!=-1) return f[pos][a][b];
    long long ans=0;
    for(int x=0;x<=(a?((X>>pos)&1):1);++x)
        for(int y=0;y<=(b?((Y>>pos)&1):1);++y)
        {
            if(x&&y) continue;//不能同时为 1
            ans+=dfs(pos-1,a&(x==((X>>pos)&1)),b&(y==((Y>>pos)&1)));
        }
    return f[pos][a][b]=ans%MOD;
}
int main()
{
#ifdef ONLINE_JUDGE
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
#endif
    cin>>T;
    while(T--)
    {
        cin>>X>>Y;ANS=0;
        memset(f,-1,sizeof(f));
        for(int i=0;i<=30;++i)//枚举上文中的 k
        {
            long long ans=0;
            if((1<<i)<=X) ans+=dfs(i-1,(X-(1<<i))<(1<<i),Y<(1<<i));//使第一个数第 k 位为 1
            if((1<<i)<=Y) ans+=dfs(i-1,X<(1<<i),(Y-(1<<i))<(1<<i));//使第二个数第 k 位为 1
            ANS+=ans*(i+1)%MOD;
        }
        cout<<ANS%MOD<<'\n';
    }
}
```

---

## 作者：chen_zhe (赞：3)

以下内容转载自官方题解：

考虑数位 DP。设 $dp[i][\mathrm{state}]$ 表示当前考虑到第 $i$ 位，$\mathrm{state}$ 包含的状态有：当前 $x$ 是否卡住 $X$ 的上界、当前 $y$ 是否卡住 $Y$ 的上界、当前数字是否为 0，在这基础上的答案。然后从高到低枚举 $i$，再枚举 $x,y$ 在第 $i$ 位上的状态，可以维护出后继状态，然后转移即可。

---

## 作者：Diaоsi (赞：2)

[[ICPC2020 Shanghai R] Sum of Log](https://codeforces.com/gym/102900/problem/C)

两个数与运算为 $0$ 这个条件很好转化，就是这两个数在二进制下没有相同的 $1$，而 $\left\lfloor\log_2(i+j)+1\right\rfloor$ 就是 $i+j$ 在最高位的 $1$ 的位数加一。

直接对 $i+j$ 进行数位 $\mathtt{dp}$，设 $f_{i,0/1,0/1,0/1}$ 表示当前填到第 $i$ 位，当前是否达到了 $X$ 的上限，是否达到了 $Y$ 的上限，当前位之前是否全为 $0$ 时对答案的贡献。

若当前位为最高位，需要在转移时乘上 $\left\lfloor\log_2(i+j)+1\right\rfloor$ 对答案的贡献，剩下的就是比较套路的数位 $\mathtt{dp}$，最后记得减去 $(0,0)$ 的情况。

```Code:```

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=100010,M=1000010,p=1e9+7;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int T,x[31],y[31],f[31][2][2][2];
int dfs(int pos,int l1,int l2,int l3){//x y zero
	if(!pos)return 1;
	if(f[pos][l1][l2][l3]!=-1)return f[pos][l1][l2][l3];
	int res=0;
	int up1=l1?x[pos]:1,up2=l2?y[pos]:1;
	for(int i=0;i<=up1;i++)
		for(int j=0;j<=up2;j++){
			if(i&j)continue;
			int lg=l3&&(i||j)?pos:1;
			res=(res+1ll*lg*dfs(pos-1,l1&&i==up1,l2&&j==up2,l3&&!i&&!j)%p)%p;
		}
	f[pos][l1][l2][l3]=res;
	return res;
}
void solve(){
	int X,Y;
	scanf("%d%d",&X,&Y);
	memset(x,0,sizeof(x));
	memset(y,0,sizeof(y));
	memset(f,-1,sizeof(f));
	for(int i=1;X;i++)x[i]=X&1,X>>=1;
	for(int i=1;Y;i++)y[i]=Y&1,Y>>=1;
	printf("%d\n",(dfs(30,1,1,1)-1+p)%p);
}
int main(){
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```


---

## 作者：DengDuck (赞：1)

有一个 Trick 是不能忘记的，$a\operatorname{and} b=0$ 的情况下，$a\operatorname{or} b=a+b$。

所以 $\lfloor \log_2(i+j)\rfloor=\lfloor\log_2(i\operatorname{or} j)\rfloor=\lfloor\max(\log_2(i),\log_2(j))\rfloor$，这个式子很守序善良。

然后考虑枚举 $\lfloor\max(\log_2(i),\log_2(j))\rfloor$ 然后大力数位 DP 统计方案，假设这一位是 $k$，那么前面的必须都是 $0$，$k$ 这一位必须是一个 $1$ 一个 $0$，其他位也要保证不会出现两个 $1$。

然后就直接做就行了。

通常的数位 DP 题都是时间很充裕的，这题数据组数很多很卡常，所以需要卡卡。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
//#define fir first
//#define sec second
using namespace std;
//const LL inf;
const LL N=35;
const LL M=31;
const LL mod=1e9+7;
//const LF eps;
//const LL P;
LL T,f[N][2][2];
LL gt(LL x,LL k)
{
	return (x>>(k-1))&1;
}
LL dfs(LL x,LL k,LL lima,LL limb,LL X,LL Y)
{
	if(x==0)return 1;
	if(f[x][lima][limb]!=-1)return f[x][lima][limb]; 
	LL ans=0;
	for(int i=0;i<=1;i++)	
	{
		if(lima&&i>gt(X,x))continue;
		if(x>k&&i)continue;
		for(int j=0;j<=1;j++)
		{
			if(i+j==2)continue;
			if(k==x&&i+j==0)continue;
			if(x>k&&j)continue;
			if(limb&&j>gt(Y,x))continue;
			ans=(ans+dfs(x-1,k,lima&&(i==gt(X,x)),limb&&(j==gt(Y,x)),X,Y))%mod;
		}
	}
	//cout<<x<<' '<<lima<<' '<<limb<<' '<<ans<<' '<<Y<<endl;
	return f[x][lima][limb]=ans;	
}
LL work(LL x,LL y)
{
	LL ans=0;
	memset(f,-1,sizeof(f));
	for(int i=M;i>=1;i--)
	{
		if(x<(1ll<<(i-1))&&y<(1ll<<(i-1)))continue;
		f[i][0][0]=f[i][1][1]=f[i][1][0]=f[i][0][1]=-1;
		ans=(ans+dfs(i,i,x<(1ll<<i),y<(1ll<<i),x,y)*i)%mod;
	}
	return ans;
}
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		LL x,y;
		scanf("%lld%lld",&x,&y);
		printf("%lld\n",work(x,y));
	}
	return 0;
}
//RP++
```

---

## 作者：_anll_ (赞：0)

惊讶地发现自己将数位 dp 忘得一干二净。这篇当作回顾，顺便初赛 rp++。

## 思路
一个很一眼的结论是当 $i \& j=0$，则 $a|b=a+b$。理由是当两个数按位与为 $0$ 时，在二进制下任意一位均不会同时出现两个 $1$。因此 $\log_2(i+j)=\log_2(i|j)=\max(\log_2(i),\log_2(j))$。

不妨对 $i\& j$ 进行数位 dp。具体地，令 $dp[x][0/1][0/1][0/1]$ 表示当枚举到第 $x$ 位时，$i$ 是否抵着上界，$j$ 是否抵着上界，当前位之前是否出现过 $1$。实现时需要根据最后一维计算贡献，如果为当前位为第一个 $1$ 则需要额外乘上 $x$，否则计算方案数即可。最后统计答案时需要额外减去 $(0,0)$ 的方案。

## 代码
```cpp
#include<cmath>
#include<cstring>
#include<iostream>
#define int long long
using namespace std;
const int N=35,mod=1e9+7;;
int t,n,m,dp[N][2][2][2];
int dfs(int x,int a,int b,int z){
	if(!x) return 1;
	if(dp[x][a][b][z]!=-1) return dp[x][a][b][z];
	int r1=a?(n>>x-1&1):1,r2=b?(m>>x-1&1):1;
	int an=0;
	for(int i=0;i<=r1;i++)
		for(int j=0;j<=r2;j++){
			if(i&j) continue;
			int val=(z&&(i||j))?x:1;
			an=(an+val*dfs(x-1,a&&i==r1,b&&j==r2,z&&!i&&!j)%mod)%mod;
		}
	dp[x][a][b][z]=an;return an;
}
void solve(){
	memset(dp,-1,sizeof(dp));
	cin>>n>>m;
	int ans=dfs(30,1,1,1);
	cout<<(ans-1+mod)%mod<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;while(t--) solve();
	return 0;
}
```

---

