# Infinite Prefixes

## 题目描述

You are given string $ s $ of length $ n $ consisting of 0-s and 1-s. You build an infinite string $ t $ as a concatenation of an infinite number of strings $ s $ , or $ t = ssss \dots $ For example, if $ s = $ 10010, then $ t = $ 100101001010010...

Calculate the number of prefixes of $ t $ with balance equal to $ x $ . The balance of some string $ q $ is equal to $ cnt_{0, q} - cnt_{1, q} $ , where $ cnt_{0, q} $ is the number of occurrences of 0 in $ q $ , and $ cnt_{1, q} $ is the number of occurrences of 1 in $ q $ . The number of such prefixes can be infinite; if it is so, you must say that.

A prefix is a string consisting of several first letters of a given string, without any reorders. An empty prefix is also a valid prefix. For example, the string "abcd" has 5 prefixes: empty string, "a", "ab", "abc" and "abcd".

## 说明/提示

In the first test case, there are 3 good prefixes of $ t $ : with length $ 28 $ , $ 30 $ and $ 32 $ .

## 样例 #1

### 输入

```
4
6 10
010010
5 3
10101
1 0
0
2 0
01```

### 输出

```
3
0
1
-1```

# 题解

## 作者：DepletedPrism (赞：5)

#### 题目思路

感觉这道题没有隔壁题解说的那么复杂...

对于串 $s$, 先算出来它前缀的 balance, 记作 $A_i$, 那么对于样例的第一种情况, 有

| Pos | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| s |  | 0 | 1 | 0 | 0 | 1 | 0 |
| $A_i$ | 0 | 1 | 0 | 1 | 2 | 1 | 2 |

注意到这里 $s$ 下标从 $1$ 开始, 并且 $A_0$ 值有意义, 为取空串的情况.

考虑 $t$ 由 $s$ 循环得到, 可看作数个完整的 $s$ 和零散的几个位置拼接而成, 不妨记 $A_n$ 为 $p$, 那么对于 $t$ 某一个位置的 balance 可记作

$$p \cdot m + A_i$$

其中 $m$ 为完整包含 $m$ 个 $s$, 余下 $i$ 个位置.

要统计 balance 为 $x$ 的数量, 即

$$p \cdot m + A_i = x$$

现在我们分类讨论

- $p \neq 0$
$$m = \dfrac{x - A_i}{p}$$

  统计 $(x - A_i)\mod p = 0$ 数量就是答案.

  有两个细节.
  
  1. $x = 0$, 此时取空串也是合法的一种答案.
  
  2. $x - A_i$ 和 $p$ 可能一正一负, 但是只有这两数正负性相同的时候才对答案有贡献. 也就是 $p \cdot (x - A_i) \geq 0$ 的时候.
  
- $p = 0$
  
  考虑 $p = 0$ 的意义, balance 兜了一圈又回来了.
  
  此时如果存在 $A_i = x$, 那么存在无限个答案.
  
  如果不存在 $A_i = x$, 那么不存在答案.

#### 代码实现

其实挺好写的, 细节也不是很多.

```cpp
// B
// DeP
#include <cstdio>

const int MAXN = 1e5+5;

int n, x;
int A[MAXN];
char S[MAXN];

int main() {
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
#endif
    int Ti;
    scanf("%d", &Ti);
    while (Ti--) {
        scanf("%d%d%s", &n, &x, S+1);
        A[0] = 0;
        for (int i = 1; i <= n; ++i) {
            if (S[i] == '0') A[i] = A[i-1] + 1;
            else A[i] = A[i-1] - 1;
        }
        int p = A[n];
        if (!p) {
            bool infty = false;
            for (int i = 0; i <= n && !infty; ++i)
                if (A[i] == x) infty = true;
            puts(infty? "-1": "0");
        } else {
            int ans = x == 0;
            for (int i = 1; i <= n; ++i)
                if (1LL * (x-A[i]) * p >= 0 && (x - A[i]) % p == 0) ++ans;
            printf("%d\n", ans);
        }
    }
    return 0;
}
```

---

## 作者：MyukiyoMekya (赞：1)

首先我就想到了前缀和，在 $0$ 的位置 $+1$ ，$1$ 的位置 $-1$，这里前缀和数组表示为 $f[i]=\sum _{j=1}^i a[j]$

然后，我们就可以 $O(n)$ 求出每加入一次 $s$ 后对整个字符串的贡献，也就是 $f[n]$

如果 $f[n]=0$，那么说明每个 $s$ 都可以被看作独立的，如果一个 $s$ 中存在符合要求的前缀，那么不管加上多少个 $s$ 都会有符合要求的前缀，于是输出 $-1$ ，如果没有输出 $0$，这里 $O(n)$ 扫

如果 $f[n]>0$，那么说明每加上一个 $s$ ，整个字符串的差分的最前面的“基准数”就被加上了 $f[n]$ ，那么我们只要算出每个 $f[i]$ 到 $x$ 的“距离”是不是 $f[n]$ 的**正**整数倍，如果是，那么答案 $+1$

也就是说，把 $i$ 从 $1$ 到 $n$ $for$一遍，碰到一个 $(x-f[i])\%f[n]==0$ 就把答案 $+1$

也是 $O(n)$ 扫

$f[n]<0$，的情况类似 $f[n]>0$

注意，$x=0$ 的时候要记得还有个空字符串

代码：

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
using namespace std;
const int MaxN=100050;
template <class t> inline void read(t &s)
{
	s=0;
	reg int f=1;
	reg char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	s*=f;
	return;
}
char s[MaxN];
int f[MaxN];
inline void work()
{
	memset(f,0,sizeof f);
	reg int n,k;
	read(n);read(k);
	scanf("%s",s+1);
	for(int i=1;i<=n;++i)
		if(s[i]=='0')
			f[i]=f[i-1]+1;
		else
			f[i]=f[i-1]-1;
	reg int ans=0;
	if(!k)
		++ans;
	if(!f[n])
	{
		reg int sum=0;
		if(!k)
		{
			puts("-1");
			return;
		}
		for(int i=1;i<=n;++i)
		{
			if(s[i]=='0')
				++sum;
			else
				--sum;
			if(sum==k)
			{
				puts("-1");
				return;
			}
		}
		printf("%d\n",ans);
		return;
	}
	if(f[n]>0)
	{
		for(int i=1;i<=n;++i)
		{
			if(f[i]>k)
				continue;
			if(!((k-f[i])%f[n]))
				++ans;
		}
		printf("%d\n",ans);
		return;
	}
	if(f[n]<0)
	{
		for(int i=1;i<=n;++i)
		{
			if(f[i]<k)
				continue;
			if(!((f[i]-k)%f[n]))
				++ans;
		}
		printf("%d\n",ans);
		return;
	}
	puts("珂朵莉天下第一可爱!");
	return;
}
signed main(void)
{
	int n;cin>>n;
	while(n--)
		work();
	return 0;
}
```

---

## 作者：fanfansann (赞：1)

题目表达的很难看懂，简单来说就是给一个长度已知可以无限重复的字符串，只有0和1两种字符，问有几个点可以使0比1多x个。

比如样例`1, 010010` 1个子串中0比1多2个，所以前四个子串结束后0一共比1多了8个，而0比1多10个将在下一个子串中出现，也就是第`28 30` 和`32`位的时候。

用一个前缀和`pre`数组来表示当前0和1的个数差值，然后特判即可。

具体的直接看代码就好。


```cpp
#include<bits/stdc++.h>
#define debug cout<<"ok"<<endl
using namespace std;
typedef long long ll;
const int N=1e5+7;
const int mod=1e9+7;
ll n,x,t,pre[N];
string s;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--)
    {
        cin>>n>>x>>s;
        ll ans=0;bool flag=0;pre[0]=0;
        for(int i=0;i<s.length();i++)
        {
            if(s[i]=='0')pre[i+1]=pre[i]+1;//前缀和数组，pre[i]表示0的个数与1的个数的差值
            else pre[i+1]=pre[i]-1;
        }
        ll date=pre[s.length()];
        for(int i=0;i<=s.length();i++)//要<=因为看走完如果是否满足题意
        {
            if(pre[i]==x)ans++;
            if(pre[i]==x&&date==0)flag=1;
            if(i!=0&&pre[i]<x&&date>0&&(x-pre[i])%date==0)ans++;
            if(i!=0&&pre[i]>x&&date<0&&(pre[i]-x)%(-date)==0)ans++;
        }
        if(!flag)
            cout<<ans<<endl;
        else cout<<-1<<endl;
    }
    return 0;
}

```




---

## 作者：Fu_Da_Ying (赞：0)

## [原题链接](https://www.luogu.com.cn/problem/CF1295B)
## 题意：
给定一个长度为 $n$ 的 $01$ 串 $s$，将它无限复制拼接得到一个无限长的 $01$ 串 $t=ssssss⋯$，对于 $t$ 的某个前缀定义它的权值为 $0$ 的个数减去 $1$ 的个数，求权值为 $x$ 的前缀的个数，如果无穷多输出 $-1$。
## 思路：
令前缀和中第 $i$ 个为 $pre_i$。

假设已经循环了 $y$ 次，当前位置是 $i$，那么当前的和就是 $m \times pre_n + pre_i$。

那么此问题为 $m \times pre_n + pre_i = x$ 的情况有几个。

显然，最好想的就是 $pre_n = 0$ 的情况。如果有任意一个 $pre_i = x$，那么就输出 $-1$，否则输出 $0$。

而 $pre_n \neq 0$ 呢？我们可以由 $m \times pre_n + pre_i = x$ 算出 $y$ 的取值：

$y=\frac{x - pre_i}{pre_n}$

显然，我们要求出 $y$ 的所有非负整数解。因此，我们只需要统计 $pre_n$ 整除 $x-pre_i$ 的数量即可。

最后注意一下 $x=0$ 的时候，空串也满足条件。
## Code:
```cpp
//非洛谷题_CodeForces_CF1295B_Infinite Prefixe
#include<bits/stdc++.h>
#pragma GCC/*G++*/ optimize(2)//O2
#pragma GCC/*G++*/ optimize(3)//O3
using namespace std;
long long t=0,n=0,x=0,pre[1919810]={}/*pre[i]表前s[i]的前缀和*/,y=0,sum=0;
bool flag=0;
char s;
int main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);//cin加速
    cin>>t;
    while(t--){
    	cin>>n>>x;
    	for(int i=1;i<=n;i++){
    		cin>>s;
    		if(s=='1'){
    			pre[i]=pre[i-1]-1;//如果s[i]此处为1,per[i]=pre[i-1]-1;
			}else{
				pre[i]=pre[i-1]+1;//否则per[i]=pre[i-1]+1;
			}
			if(pre[i]==x){
				flag=1;//有pre[i]==x时,记录下来,如果pre[i]==0时的判断t是否无限多个符合要求
			}
		}
		if(pre[n]==0){//如果pre[n]==0时
			if(flag==0){
				cout<<"0\n";//如果没有pre[i]==x时,没有t符合要求,输出0
			}else{
				cout<<"-1\n";//否则,t为无限多个符合要求,输出-1
			}
		}else{
			for(int i=1;i<=n;i++){
				y=(x-pre[i])/pre[n];//y的值为(x-pre[i])/pre[n]
				if(y>=0&&y*pre[n]+pre[i]==x){
					sum++;//如果满足y是正整数,答案加1 
				}
			}
			if(x==0){//x为0时有空串,所以答案需加1 
				sum++;
			}
			cout<<sum<<"\n";
		}
		sum=0;
		flag=0;
	}
    return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

又一道澄碧题。

## 思路

令 $pre_i$ 表示一个前缀和。


假设已经循环了 $m$ 次，当前位置是 $i$，那么当前的和就是 $m \times pre_n + pre_i$。我们需要算出所有的 $m \times pre_n + pre_i = x$ 的情况。

显然，最好想的就是 $pre_n = 0$ 的情况。如果有任意一个 $pre_i = x$，那么就输出 ```-1```，否则输出 ```0```。

而 $pre_n \neq 0$ 呢？我们可以算出 $m$ 的取值：

$$m = \frac{x-pre_i}{pre_n}$$ 

显然，我们要求出 $m$ 的所有正整数解。因此，我们只需要统计$pre_n$ 整除 $x-pre_i$ 的数量即可。

最后注意一下 $x=0$ 的时候，空串也满足条件。

显然时间复杂度为 $O(n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[100005];
int now[100005]; // 前缀和
int main()
{
	int T; scanf("%d",&T);
	while(T--)
	{
		int n,x; scanf("%d%d",&n,&x);
		scanf("%s",s+1);
		int ans,flag; ans=flag=(x==0); // 特判一下空串
		for(int i=1;i<=n;i++)
		{
			now[i]=now[i-1];
			if(s[i]=='0') now[i]++;
			else now[i]--;
			if(now[i]==x) flag=1;
		}
		if(now[n]==0) // 即上文的特判 pre[n]=0
		{
			if(flag) puts("-1");
			else puts("0");
			continue;
		}
		for(int i=1;i<=n;i++)
			if((x-now[i])%now[n]==0 && 1ll*(x-now[i])*now[n]>=0) ans++; // 统计答案
		printf("%d\n",ans);
	}
	return 0;
}
```

---

