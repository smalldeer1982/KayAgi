# Ahahahahahahahaha

## 题目描述

Alexandra 有一个由若干$0$和$1$组成的数组$a$，且数组$a$的长度$n$为偶数，数列中所有元素的编号依次为$1$ ~ $n$。她希望在数组中删除一些元素，来使得奇数编号位置上的数字之和等于偶数编号位置上的数字之和（$a_1 - a_2 + a_3 - a_4 + ... = 0$），最多删除$\frac{n}{2}$个元素且删除的元素不必是连续的

例如，如果原数组$a$ =  $\left[1,0,1,0,0,0\right]$,且她删除了原数列中的第$2$个和第$4$个元素，那么数组$a$将变成$\left[1,1,0,0\right]$，并且奇数编号位置上的数字之和等于偶数编号位置上的数字之和。

帮帮她解决这个问题吧！

## 样例 #1

### 输入

```
4
2
1 0
2
0 0
4
0 1 1 1
4
1 1 0 0```

### 输出

```
1
0
1
0
2
1 1
4
1 1 0 0```

# 题解

## 作者：wsyhb (赞：6)

## 题意简述

从长度为**偶数** $n$ 的**01序列**中选出一个长度**不小于** $\frac{n}{2}$ 的**子序列**，满足**奇数编号位置上数字之和**等于**偶数编号位置上数字之和**。

数据范围：$n \leq 10^3$

## 题目分析 & 解法

这是一道 `Codeforces Div.2` 的 `A` 题，以经验来说一定是**特殊的构造**，那么我们就考虑——哪种形式简单的子序列一定满足题意呢？

答案很简单：**数字相同**的子序列。具体来说，即**任意长度**的全 $0$ 序列，和**偶数长度**的全 $1$ 序列。

记 $0$ 的个数为 $cnt_0$，$1$ 的个数为 $cnt_1$，则 $cnt_0+cnt_1=n$，进行如下讨论：

若 $cnt_0 \geq \frac{n}{2}$，只需从中选 $\frac{n}{2}$ 个 $0$ 即可。

否则，$cnt_0 \leq \frac{n}{2}-1$，因此 $cnt_1=n-cnt_0 \geq \frac{n}{2}+1$，至少有两种全 $1$ 的选法：选 $\frac{n}{2}$ 个或 $\frac{n}{2}+1$ 个。由于这两种选法的子序列长度**奇偶性不同**，必为一奇一偶，选其中之一即可。

## 代码实现

我们整理一遍思路：

1. 统计 $0$ 和 $1$ 的个数，记为 $cnt_0$ 和 $cnt_1$。

2. 若 $cnt_0 \geq \frac{n}{2}$，输出 $\frac{n}{2}$ 个 $0$；

3. 否则判断 $\frac{n}{2}$ 和 $\frac{n}{2}+1$ 哪一个为偶数，输出对应个数的 $1$。

最后贴一份**代码**：

``` cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		int cnt0=0,cnt1=0;
		for(int i=1;i<=n;++i)
		{
			int x;
			scanf("%d",&x);
			if(x==0) ++cnt0;
			else ++cnt1;
		}
		if(cnt0>=n/2)
		{
			printf("%d\n",n/2);
			for(int i=1;i<=n/2;++i)
				printf("%d%c",0,i<n/2?' ':'\n');
		}
		else
		{
			int ans;
			if(n/2%2==1) ans=n/2+1;
			else ans=n/2;
			printf("%d\n",ans);
			for(int i=1;i<=ans;++i)
				printf("%d%c",1,i<ans?' ':'\n');
		}
	}
	return 0;
}

```

---

## 作者：onglu (赞：3)

## A. Ahahahahahahahaha  
### 题目大意  
给定一个长度为$n$的$01$串，要求至多删去$\frac{n}{2}$个字符，使得剩下的串中**奇数位的数之和 = 偶数位之和**， 要求输出删去后剩下的串。  

### 思路  
一开始没有啥头绪，直到注意到$\frac{n}{2}$有什么意义。  
由于只有$0$和$1$，所以数量比较少的那一个必不超过$\frac{n}{2}$。  

分两类讨论：  

如果$1$比较少，那么删除所有的$1$剩下的只有$0$，和肯定相等。  

如果$0$比较少，那么删除所有的$0$之后剩下有两种情况：奇数个$1$和偶数个$1$。  

如果是奇数个$1$那么再删去一个就变成偶数个$1$。  

注意还有一点$tips$，由于$n$不保证是$4$的倍数，所以如果$0$和$1$相等的时候如果删去了$0$可能剩下$\frac{n}{2}$（奇数）个$1$所以要先考虑删除$1$的情况。  

时间复杂度为$O(n)$

### 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

int read(){
	char c; int num, f = 1;
	while(c = getchar(),!isdigit(c)) if(c == '-')f = -1; num = c - '0';
	while(c = getchar(), isdigit(c)) num = num * 10 + c - '0';
	return num * f;
}
int n, cnt[2];
void work(){
	n = read(); cnt[0] = 0; cnt[1] = 0;
	for(int i = 1; i <= n; i++){
		cnt[read()]++;
	}
	if(cnt[0] >= cnt[1]){
		printf("%d\n", cnt[0]);
		for(int i = 1; i <= cnt[0]; i++)
			printf("0 ");
		printf("\n");
	}else {
		if(cnt[1] & 1)cnt[1]--;
		printf("%d\n", cnt[1]);
		for(int i = 1;i <= cnt[1]; i++)
			printf("1 ");
		printf("\n");
	}
}
int main()
{
	int Case = read();
	while(Case--)work();
	return 0;
}
```

---

## 作者：过往梦魇之殇 (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/CF1407A)

**思路简述：**

首先观察到这两句话：

```
最多删除n/2个元素且删除的元素不必是连续的。
对于每组样例，第一行输出k，用来表示经过删除操作后数组a中剩下的元素个数(n/2<=k<=n)。
```
而且数组中只会有$0$和$1$，所以必然至少有一种数$(0,1)$的出现次数小于等于$\dfrac{n}{2}$

所以我们考虑“最后只剩下一种数（$0,1$）”的策略。

然后我们分两种情况讨论：

$1.$ 

$0$出现的次数大于等于$1:$

因为$(0+0+\ldots+0)-(0+0+\ldots+0)=0$

所以删完所有的$1$后，数组必然合法，输出即可。

$2.$

$0$出现的次数小于$1:$

这里较第一种稍微复杂了些，因为当$1$出现了奇数次，还应该删掉一个$1$。

而再删一个$1$并不会导致剩下的数的个数小于$\dfrac{n}{2},$

因为在讨论的时候，我们已经把这种情况归到留$0$删$1$里面去了。

若$1$出现偶数次，则正常操作即可。

讨论完毕。

------------
**代码展示：**

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
int T,k,cnt[2];
int main(){
    scanf("%d",&T);
    while(T--){
        cnt[0]=cnt[1]=0;
        scanf("%d",&k);
        for(re int i=1;i<=k;++i){
            int a;
            scanf("%d",&a);
            ++cnt[a];
        }
        if(cnt[0]>=cnt[1]){
            printf("%d\n",cnt[0]);
            for(re int i=1;i<=cnt[0];++i){
                printf("0 ");
            }
            puts("");
        }
        else{
            if(cnt[1]%2){
                --cnt[1];
            }
            printf("%d\n",cnt[1]);
            for(re int i=1;i<=cnt[1];++i){
                printf("1 ");
            }
            puts("");
        }
    }
    return 0;
}
```
>$Thanks$ $For$ $Watching!$

---

## 作者：HeCao2008 (赞：1)

给出一种和 [tourist](https://search.bilibili.com/all?keyword=tourist&from_source=webtop_search&spm_id_from=333.1007&search_source=5) 一样的解法。

[更好的阅读体验](https://www.luogu.com.cn/blog/C-SHANGHAI/solution-cf1407a)

[题目传送门](https://www.luogu.com.cn/problem/CF1407A)

### 思路

一道**构造题**，显然我们可以充分利用删除数的条件来进行**分类讨论**。

我们可以把这些数分成四个四个一组，判断每一组的和：

如果这些数的和大于等于二，那么其中**必然会有两个 $1$** ，把两个 $1$ 加进答案数组。

如果不是，那么其中**必然会有两个 $0$** （实际上如果等于 $2$ 还是会有两个 $0$ ，不过上面已经讨论过了），把两个 $0$ 加进答案数组。

如果不是四个四个一组，那么由题肯定会剩下两个数，我们可以用同样的方式判断：

如果这两个数的和等于 $2$ ，那么这两个数肯定全是 $1$ ，把它们加进答案数组。

否则，要么就是一个 $1$ 一个 $0$，或者是两个 $0$，对于这两种情况，我们可以用一种统一的解法：直接插入一个 $0$ 就可以了，不影响答案。

### 代码

相信有了上面的解法，都能得出代码，思路是非常清晰的：

```cpp
#include<bits/stdc++.h>
using namespace std;
int tt,n;
int main(){
	ios::sync_with_stdio(false);
	cin>>tt;
	while(tt--){
		int a[1145];
		vector< int > ans;
		cin>>n; 
		for(int i=0;i<n;i++)cin>>a[i];
		for(int i=0;i<n;i+=4){
			if(i+4<=n){
				int now=a[i]+a[i+1]+a[i+2]+a[i+3];
				if(now>=2){
					ans.push_back(1);
					ans.push_back(1);
				}else{
					ans.push_back(0);
					ans.push_back(0);
				}
			}else{
				int now=a[i]+a[i+1];
				if(now==2){
					ans.push_back(1);
					ans.push_back(1);
				}else{
					ans.push_back(0);
				}
			}
		}
		cout<<ans.size()<<"\n";
		for(int i=0;i<ans.size();i++){
			if(i>0)cout<<" ";
			cout<<ans[i];
		}
		cout<<"\n";
	}
	return 0;
}
```

**谢谢大家的阅读！**

---

## 作者：孤芒星河233 (赞：1)

# CF1407A Ahaha

[Codeforces 原题面](https://codeforces.com/problemset/problem/1407/A)

[洛谷原题面](https://www.luogu.com.cn/problem/CF1407A)

## 题意理解

输入T组数据。使得一个长度为 $n$ 由 $0$ 和 $1$ 组成的数组删除 $m$ 个数后，奇数下标的数字之和等于偶数下标的数字之和。$(0\leq m\leq \frac{n}{2})$

输出剩下的数组长度 $k$ 和剩下的所有数字。 $( \frac{n}{2} \leq k\leq n)$

## 思路

设 $0$ 的数量为 $x$ ，$1$ 的数量为 $y$ 。既然这个数组只由 $0$ 和 $1$ 组成，那么要么是 $x<\frac{n}{2}<y$ ，要么是 $y\leq \frac{n}{2}\leq x$

所以当 $y\leq x$ 时，我们直接把所有的 $1$ 全部删掉，剩下的数全部为 $0$ ，显然满足条件；当 $x<y$ 时，直接把所有的 $0$ 删掉，此时 $k$ 必须为偶数，不为偶数再删去一个 $1$ 即可

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e3+9;
int T,n,x,one,zer;//one是1的数量,zer是2的数量

int main(){
    scanf("%d",&T);
    while(T--){
        one=zer=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&x);
            if(x==0) zer++;
            else one++;
        }
        if(one>zer){
            if((n-zer)%2!=0) n--;
            printf("%d\n",n-zer);
            for(int i=1;i<=n-zer;i++) printf("1 ");
            putchar('\n'); 
        }
        else{
            printf("%d\n",n-one);
            for(int i=1;i<=n-one;i++) printf("0 ");
            putchar('\n');
        }
    }
    return 0;
}
```

---

## 作者：lory1608 (赞：1)

我这道题目做了 $40$ 分钟。

这道题特别明显的贪心，我没有想到，写了一个超级难写的 $dp$ 。

显然，我们可以记 $dp[i][j][k]$ 表示前 $i$ 个元素，选了 $j$ 个元素，和为$k$ 是否可达，然后转移即可。

最后只用找到一个 $dp[t][i][0]=1(k/2 \leq n \leq k)$ 的情况再回溯即可。

注意到这里复杂度是 $\Theta(n^3)$ 的并不能通过，所以再加一个bitset就行了。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<vector>
#include<set>
#include<bitset>
#define IN inline
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define REP(u) for(int i=p[u];i!=-1;i=e[i].nxt)
#define ll long long
#define ull unsigned long long
#define PII pair<int,int>
using namespace std;
inline int getint()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return (f==1)?x:-x;
}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int maxn=1005;
bitset<2005>dp[maxn][maxn];///Ç°iÎ»£¬Ñ¡ÁËj¸ö£¬ºÍµÄÖÖÀàÊý 
int T,n,a[maxn];
int main()
{
	T=getint();
	while(T--)
	{
		n=getint();
		dp[0][0][n]=1;
		FOR(i,1,n)
		{
			a[i]=getint();
			FOR(j,0,i)
			{
				dp[i][j]|=dp[i-1][j];
				if(j%2==0)dp[i][j+1]|=dp[i-1][j]<<a[i];
				else dp[i][j+1]|=dp[i-1][j]>>a[i];
			}
		}
		for(int i=n;i>=n/2;--i)
		{
			if(dp[n][i][n])
			{
				printf("%d\n",i);
				vector<int>v;
				int cho=i,now=n;
				for(int j=n;j>=1;--j)
				{
					if(cho>=1&&dp[j-1][cho-1][now]&&a[j]==0)v.push_back(0),cho--;
					else if(a[j]==1&&cho>=1)
					{
						if(cho%2==0)
						{
							if(dp[j-1][cho-1][now+1])cho--,now++,v.push_back(1);
						}
						else
						{
							if(dp[j-1][cho-1][now-1])cho--,now--,v.push_back(1);
						}
					}
				}
				reverse(v.begin(),v.end());
				FOR(j,0,(int)(v.size())-1)printf("%d ",v[j]);
				printf("\n");
				break;
			}
		}
		FOR(i,0,n)FOR(j,0,i)dp[i][j]=0;
	}
	return 0;
}
```

---

## 作者：寒鸽儿 (赞：1)

对于奇数个 $1$ , 应该舍掉 $1$ 个。  
然后对于偶数个 $1$ , 应该轮流分配给两家。这要求每两个 $1$ 之间的 $0$ 的个数为偶数。如果有奇数个 $0$ , 应当舍掉一个。  
易证 , 中间连续的 $0$ 的段数不超过 $\frac{n}{2} - 1$ , 再加上可能出现奇数个 $1$ , 至多舍掉 $\frac{n}{2}$ 个数据。  
```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 1234;
vector<int> a , ans;
 
int main() {
    int tests;
    cin >> tests;
    while(tests--) {
        a.clear();
        int n , sum = 0;
        scanf("%d", &n);
        a.resize(n + 1);
        for(int i = 1; i <= n; ++i) scanf("%d" , &a[i]) , sum += a[i];
        if(sum % 2 != 0) {
           for(vector<int>::iterator it = a.begin(); it != a.end();++it)
                if(*it) {
                    a.erase(it); --n;
                    break;
                } 
        }
        if(n == 1) {
            printf("1\n0\n");
            continue;
        }
        ans.clear();
        int l = -1;
        for(int i = 1; i <= n; ++i) {
            if(a[i]) {
                if(~l) {
                    if((i-1-l+1) % 2 == 0)
                        for(int j = l; j < i; ++j) ans.push_back(0);
                    else 
                        for(int j = l; j < i - 1; ++j) ans.push_back(0);
                }
                ans.push_back(1);
                l = -1;
            } else {
                if(!~l) l = i;
            }
        }
        if(~l) for(int i = l; i <= n; ++i) ans.push_back(0);
        int sz = ans.size();
        printf("%d\n" , sz);
        for(int i = 0; i < sz; ++i) printf("%d ", ans[i]);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：引领天下 (赞：0)

显然如果全部是 $1$，则直接取 $n_0(n_0\le n\text{且}n_0\text{是偶数})$ 个 $1$ 即可。

如果 $1$ 的个数多于一半，则直接取 $\lfloor \frac{n}{2} \rfloor $ 个 $1$ 就可以满足题意。

否则 $0$ 的个数必然多于一半，取 $\lfloor \frac{n}{2} \rfloor $ 个 $0$ 即完成构造。


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[1004];
int main(){
    scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
        int sum=0;
        for(int i=1;i<=n;i++)scanf("%d",&a[i]),sum+=a[i];
		if(sum==n)		{
			int k=(n&1)?n-1:n;
			printf("%d\n",k);
			for (int i=1;i<=k;i++)printf("1 ");puts("");
			continue;
		}
		if(sum>(n>>1)){
			int k=((n>>1)&1)?(n>>1)+1:(n>>1);
			printf("%d\n",k);
			for (int i=1;i<=k;i++)printf("1 ");puts("");
		}
		else{
			printf("%d\n",(n>>1));
			for (int i=1;i<=(n>>1);i++)printf("0 ");puts("");
		}
	}
    return 0;
}
```

---

