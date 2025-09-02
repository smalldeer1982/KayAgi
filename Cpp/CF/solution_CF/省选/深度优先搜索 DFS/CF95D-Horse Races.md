# Horse Races

## 题目描述

Petya likes horse racing very much. Horses numbered from $ l $ to $ r $ take part in the races. Petya wants to evaluate the probability of victory; for some reason, to do that he needs to know the amount of nearly lucky horses' numbers. A nearly lucky number is an integer number that has at least two lucky digits the distance between which does not exceed $ k $ . Petya learned from some of his mates from Lviv that lucky digits are digits $ 4 $ and $ 7 $ . The distance between the digits is the absolute difference between their positions in the number of a horse. For example, if $ k=2 $ , then numbers $ 412395497 $ , $ 404 $ , $ 4070400000070004007 $ are nearly lucky and numbers $ 4 $ , $ 4123954997 $ , $ 4007000040070004007 $ are not.

Petya prepared $ t $ intervals $ [l_{i},r_{i}] $ and invented number $ k $ , common for all of them. Your task is to find how many nearly happy numbers there are in each of these segments. Since the answers can be quite large, output them modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

In the first sample, the four nearly lucky numbers are 44, 47, 74, 77.

In the second sample, only 74 and 77 are in the given segment.

## 样例 #1

### 输入

```
1 2
1 100
```

### 输出

```
4
```

## 样例 #2

### 输入

```
1 2
70 77
```

### 输出

```
2
```

## 样例 #3

### 输入

```
2 1
1 20
80 100
```

### 输出

```
0
0
```

# 题解

## 作者：Pro_Rexxar (赞：2)

[题目](https://www.luogu.org/problemnew/show/CF95D)

~~作为全机房最菜的人居然做出了一道没有人做出的题目~~

很明显这是一道数位dp，l和r的范围表明先要用字符读进来。

而所求 $ans=sum_r-sum_{l-1}$

因为 $l-1$ 涉及到高精减 ~~我并不想打~~

所以我打算对 $l$ 加个特判

改成 $ans=sum_r-sum_l+check_l$ (如果 $l$ 符合要求，那么 $check_l$ 为1)

用记忆化搜索

```cpp
#include<bits/stdc++.h>
#define Mod 1000000007
using namespace std;
char s[1007];
int t,k,f[1007][1007][2],a[1007],l;
int dfs(int pos,int d,int q,int m)
//pos表示当前位置
//d表示k+1减去与前一个幸运数字的距离
//那么当d降到0时，它与前面的幸运数字的距离就超过k了
//q表示之前是否符合要求，符合要求为1，不符合为0
//m表示当前位能否取到9，即之前是否达到上界，达到上界就为1，没有就为0
{
	if (!pos) return q;
	if (!m&&f[pos][d][q]!=-1) return f[pos][d][q];
	int ans=0,MAX=m?a[pos]:9;
	for (int i=0;i<=MAX;i++)
	{
		if (i!=4&&i!=7)
			ans=(ans+dfs(pos-1,max(d-1,0),q,m&&i==MAX))%Mod;
		else ans=(ans+dfs(pos-1,k,q||d,m&&i==MAX))%Mod;
	}
	if (!m) f[pos][d][q]=ans;
	return ans;
}
int check()
{
	int LAST=2007;
	for (int i=l;i;i--)
	{
		if (a[i]==4||a[i]==7)
		{
			if (LAST-i<=k) return 1;
			LAST=i;
		}
	}
	return 0;
}
int main()
{
	scanf("%d%d",&t,&k);
	memset(f,-1,sizeof(f));
	while (t--)
	{
		scanf("%s",s);
		l=strlen(s);
		for (int i=l-1;i>=0;i--)
			a[l-i]=s[i]-'0';
		int ans=(dfs(l,0,0,1)-check()+Mod)%Mod;
		scanf("%s",s);
		l=strlen(s);
		for (int i=l-1;i>=0;i--)
			a[l-i]=s[i]-'0';
		ans=(dfs(l,0,0,1)+Mod-ans)%Mod;
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：waauto (赞：0)

坏了这下就我不是记忆化搜索是套路 dp。

说明我只会做套路题。

考虑一个简单的 dp，设 $f_{i,j}$ 表示考虑了几个数字，最近一次幸运数字在 $j$ 位置出现，并且没有形成幸运数的方案数。

转移是简单的，每次考虑一个新的位要么就放个没用的数直接转，要么就放个关键数从 $i-k-1$ 以及之前转移过来。

再设个 $g_i$ 表示考虑几个数形成幸运数的方案数，转移和上面一样，从出现过的 $f_{i,j-k}$ 及其以转，或者从 $g_{i-1}\times 10$ 转移过来，这是简单的。

我的代码中 $f_i,0$ 表示没有出现过幸运数。

```cpp
	f[0][0]=1;
	F(i,1,1000){
		F(j,0,i-1){
			f[i][j]=f[i-1][j]*8%mod;
		}
		f[i][i]=2*f[i-1][0];
		UF(j,i-k-1,1)(f[i][i]+=2*f[i-1][j])%=mod;
		g[i]=g[i-1]*10%mod;
		F(j,max(1ll,i-k),i-1)(g[i]+=f[i-1][j]*2)%=mod;
	}
```

然后经典数位 dp 考虑容斥。答案是 $F(r)-F(l-1)$。我们记一个 $calc(x)$ 表示 $[0,x-1]$ 的幸运数的个数，答案就是 $calc(r)-calc(l)+check(r)$。

$check(x)$ 是好写的。

```cpp
inline int check(string s){
	int res=0,pre=-1e9,i=0;
	for(auto v:s){
		if(v=='4' or v=='7'){
			if(i-pre<=k)res=1;
			pre=i;
		}
		++i;
	}
	return res;
}
```

$calc(x)$ 就考虑一个经典的套路，考虑有多少个顶着的位，挨个枚举，剩下的就可以随便填，问题在于你之前顶着的位和中间枚举过程中可能出现幸运数，你只需要对这个位置在每次操作的时候暴力往后枚举直到 $k$ 位，这样这个幸运数就是没有影响的了，否则这一段只要出现一个幸运数就行。

这个是更简单的，你只需要枚举幸运数出现的最高位，前面的全部填没用的数，后面随便填就好了。

注意一下如果前面已经形成了幸运的部分，那么剩下位置直接随便填就好了，就没必要去做以后的操作了。

```cpp
inline int calc(string s){
	int n=s.size(),pre=-1e9,ans=0,cnt=1;
	for(auto v:s){
		int now=v-'0';
		for(int i=0;i<now;++i){
			if(i==4 or i==7){
				if(cnt-pre<=k) (ans+=qpow(10,n-cnt,mod))%=mod;
				else {
					int tmp=1;
					F(j,1,k){
						if(n-cnt-j<0)break;
						(ans+=tmp*2*qpow(10,n-cnt-j,mod)%mod)%=mod,tmp=tmp*8%mod;
					}
					if(n-cnt-k>0)(ans+=tmp*g[n-cnt-k]%mod)%=mod;
				}
			}
			else {
				int tmp=1;
				F(j,1,k-cnt+pre){
					if(n-cnt-j<0)break;
					(ans+=tmp*2*qpow(10,n-cnt-j,mod)%mod)%=mod,tmp=tmp*8%mod;
				}
				if(min(n-cnt,n-pre-k)>0)(ans+=tmp*g[min(n-cnt,n-pre-k)]%mod)%=mod;
			}
		}
		if(now==4 or now==7){
			if(cnt-pre<=k){
				int tmp=0;
				for(int i=cnt;i<(int)s.size();i++)tmp=(tmp*10+s[i]-48)%mod;
				ans+=tmp;
				return ans%mod;
			}
			else pre=cnt;
		}
		++cnt;
	}
	return ans;
}
```

[完整代码链接](https://codeforces.com/contest/95/submission/240912371)

---

## 作者：Dimly_dust (赞：0)

### 【解题思路】


------------

一道比较~~基础~~的数位DP。

答案明显可以差分出来，$\large ans=calc(r)-calc(l-1)$ ，但是由于数据范围太大 $\large 1\leq l\leq r\leq 10^{1000}$，所以我们必须将 $\large l$ 单独拿出来判断一下。

至于 $\large calc(x)$ ，可以用数位dp来进行求解，定义 $\large dp_{i,j,k}$ 为在第 $\large i$ 位距上一个幸运数字距离为 $\large j$ 且是否满足条件的数的数量。

状态转移的过程可以用记忆化搜索来实现。之后就可以很简单的解决了。

**Code** (最近学坏了，压行的有些厉害)


------------

```
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
int dp[1005][1005][2];
int bits[1005];
int t,k;
long long dfs(int len,int lpos,int fg,bool border)
{
    if(!len) return fg == 1;
    if(!border && dp[len][lpos][fg]!=-1) return dp[len][lpos][fg];
    int up=border? bits[len]:9;
    long long res=0 ;
    for (int i=0; i<=up; i++)
    {
        if(i==4||i==7)
        {
            res += dfs(len-1,len,(lpos && lpos-len<=k)|fg,border&&i==up);
        }
        else res += dfs(len - 1, lpos, fg, border && i == up);
    }
    res %= mod;
    if(!border) dp[len][lpos][fg] = res;
    return res;
}
long long f(string s)
{
    int len=0;
    for (int i=s.size()-1; i>=0; i--)
    {
        bits[++ len] = s[i] - '0';
    }
    return dfs(len,0,0,1);
}
bool check(string &s)
{
    int p = 0;
    for (int i=1; i<=s.size(); i++)
    {
        if (s[i-1]=='4'||s[i-1]=='7')
        {
            if(!p||i-p>k) p=i;
            else if(i-p<=k) return true;
        }
    }
    return false;
}

int main()
{
    cin>>t>>k;
    string l,r;
    memset(dp, -1, sizeof(dp));
    for (int i=0; i<t; i++)
    {
        cin>>l>>r;
        long long ans=f(r)-f(l)+(check(l)?1:0);
        cout<<(ans%mod+mod)%mod<< endl;
    }
    return 0;
}

```


---

