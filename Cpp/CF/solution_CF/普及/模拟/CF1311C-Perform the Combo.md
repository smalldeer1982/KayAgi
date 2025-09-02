# Perform the Combo

## 题目描述

一台机器准备要打印一篇文章，有 $m$ 个打印操作  

给出操作序列 $p_1,p_2, \dots ,p_m$ 和 长度为 $n$ 的字符串 $s$  
对于每个 $(1 \le i \le m)$，$p_i$ 表示该机器将位置 $1\sim p_i$ 上的所有字母打印了出来  
最后，在所有操作做完后，该机器又将整个字符串 $s$ 打印了出来

请求出字母表中每个字母在文章中出现了多少次

## 说明/提示

$1\le T \le 10^4$  
$2 \le  n \le 2 \cdot 10^5$  
$1 \le  m \le 2 \cdot 10^5$  
$\sum n,\sum m \le 2 \cdot 10^5$  
$1 \le p_i <n$

感谢 @[_Wolverine](https://www.luogu.com.cn/user/120362) 提供的翻译

## 样例 #1

### 输入

```
3
4 2
abca
1 3
10 5
codeforces
2 8 3 2 9
26 10
qwertyuioplkjhgfdsazxcvbnm
20 10 1 2 3 5 10 5 9 4```

### 输出

```
4 2 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 9 4 5 3 0 0 0 0 0 0 0 0 9 0 0 3 1 0 0 0 0 0 0 0 
2 1 1 2 9 2 2 2 5 2 2 2 1 1 5 4 11 8 2 7 5 1 10 1 5 2```

# 题解

## 作者：huayucaiji (赞：3)

### [C. Perform the Combo](https://codeforces.com/contest/1311/problem/C)

嗯看一眼就知道是一个水题，在每一个位置维护前缀每个字母的数量，在每次出错时，就把前缀加到答案里。但注意，他可能在同一个位置的上犯很多次错，所以要累加，另外，要开 long long，应为如果这个字符串全是一个字符，就会爆int。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=2e5+10; 

long long n,m,num[26],ans[26];
char c[maxn];
int wa[maxn];

int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	
	int t;
	cin>>t;
	while(t--) {
		cin>>n>>m;
		for(int i=1;i<=n;i++) {
			cin>>c[i];
		}
		for(int i=1;i<=m;i++) {
			int q;
			scanf("%d",&q);
			wa[q]++;
		}
		for(int i=1;i<=n;i++) {
			ans[c[i]-'a']++;
			num[c[i]-'a']++;
			
			if(wa[i]) {
				for(int j=0;j<26;j++) {
					ans[j]+=wa[i]*num[j];
				}
			}
		}
		
		for(int i=0;i<26;i++) {
			printf("%d ",ans[i]);
		}
		cout<<endl;
		memset(ans,0,sizeof(ans));
		memset(num,0,sizeof(num));
		fill(wa,wa+n+1,0);
	} 

	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
```

---

## 作者：Priori_Incantatem (赞：2)

一道比较有趣的前缀和练习题

可以看出，题目有多次求 $1\sim p_i$ 上每个字母的数量。我们可以很轻松的用前缀和解决，只是需要多开一维记录字母

设 $s[i][j]$ 为在字符串前 $i$ 位上，字典序为 $j$ 的字母出现的次数

那么，对于每一次操作 $p_i$，我们只需求出所有 $s[p_i][1\sim 26]$，就可以了

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int Maxn=200000+10,inf=0x3f3f3f3f;
int s[Maxn][30],a[30];
int n,m;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int T=read();
	
	while(T--)
	{
		n=read(),m=read();
		char opt[Maxn];
		scanf("%s",opt+1);
		for(int i=1;i<=n;++i)
		{
			for(int j=0;j<26;++j) // 这里为了方便，下标从 0 开始
			s[i][j]=s[i-1][j];
			s[i][opt[i]-'a']++;
		}
		for(int i=1;i<=m;++i)	
		{
			int x=read();
			for(int j=0;j<26;++j)
			a[j]+=s[x][j]; // 统计答案
		}
		for(int i=0;i<26;++i)
		a[i]+=s[n][i];
		for(int i=0;i<26;++i)
		{
			printf("%d ",a[i]);
			a[i]=0;
		}
		putchar('\n');
	}
	
	return 0;
}
```

仔细观察可以发现，每组数据最后并不需要 $\texttt{memset}$，加了反而 TLE

---

## 作者：andyli (赞：1)

对于每个$p_i$相当于把原字符串中$[1,p_i]$这一段中的所有的字符累加到答案中，可以统计原字符串每个位置上的字符要被统计的次数，设为$c_i$。显然，不能朴素的对每个$c_i$都进行操作，于是想到了差分。构造差分数组$r_i$使得$r_i=c_i-c_{i-1}, r_1=c_1$，于是，对于每个$p_i$，可令$r_1=r_1+1$，$r_{p_i+1} = r_{p_i+1}-1$，所有操作结束后可用$c_i=\sum\limits_{j=1}^i{r_j}$公式还原$c$数组。  
时间复杂度$\mathcal O(n+m+26)$。  

代码如下（[快读模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
const int maxn = 200005;

char str[maxn];
int A[maxn];
int cnt[maxn], ans[26];
int main()
{
    int q;
    io.read(q);
    while (q--) {
        int n, m;
        io.read(n, m);
        cnt[1] = 1;
        for (int i = 2; i <= n; i++)
            cnt[i] = 0;
        io.read(str + 1);
        for (int i = 1; i <= m; i++)
            io.read(A[i]);
        for (int i = 1; i <= m; i++)
            cnt[1]++, cnt[A[i] + 1]--;
        for (int i = 1; i <= n; i++)
            cnt[i] += cnt[i - 1];
        for (int i = 0; i < 26; i++)
            ans[i] = 0;
        for (int i = 1; i <= n; i++)
            ans[str[i] - 'a'] += cnt[i];
        for (int i = 0; i < 26; i++)
            io.write(ans[i], " ");
        writeln();
    }
    return 0;
}
```

---

## 作者：riker_moon (赞：0)

从后往前扫一遍维护一个后缀和就好，遇到一个标记就把后缀加一

注意先加再统计

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
#include<vector>
#include<cmath>
#define maxn 200007
#define ll long long  
using namespace std;
int T,n,m,b[maxn],sum,ans[27];
char s[maxn]; 
inline int read()
{
	int x = 0;
	int flag = 1;
	char ch;
	ch = getchar();
	while(!isdigit(ch)) 
	{
		if(ch == '-') flag = -1;
	ch = getchar();
	} 
	while(isdigit(ch))
	{
		x = (x<<1) + (x<<3) + ch - 48;
		ch = getchar();
	}
	return x * flag;
}


int main()
{
	T = read();
	while(T--)
	{
		n = read();
		m = read();
		sum = 0;
		scanf("%s",s);
		memset(b,0,sizeof(b));
		memset(ans,0,sizeof(ans));
		for(register int i = 1;i <= m;i++)
		{
			int x = read();
			b[x - 1]++;
		}
		for(register int i = n - 1;i >= 0;i--)
		{
			sum += b[i];
			ans[s[i] - 96] += sum;
			ans[s[i] - 96]++;
		}
		for(register int i = 1;i <= 26;i++)
		{
			printf("%d ",ans[i]);
		}
		puts("");
	}
	
	return 0;
}

```
另外好像要开ll，但出题人没有卡

---

## 作者：朝夕 (赞：0)

## 解题思路
读题易得，对于任意pi，字符串中1~pi的字母都会重复出现。所以就是要找字符串中的每个字符，位置比它后的pi有几个，那这个字符就会重复出现几次。

所以一种写法是，先将pi排序，然后对于每个字符，都二分查找最后一个可行的pi，取其下标即可，处理数据的时间复杂度为O(nlogn)。

这里介绍的是另一种写法：同样先将pi排序，放一个指针于数组头部。

然后对字符串进行顺序处理，记录当前的净出现次数（不考虑任何pi的情况），直到当前位置与p1重合，那么在此之前所有出现的字母，其出现次数都加上其净出现次数。pi数组指针后移。

这样处理数据的时间复杂度缩减到O（n+m），n前常数为26。

需要注意，出现次数的记录要开longlong，这次只是出题人好心没有卡。

## 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
long long v1[30];//净出现次数
long long v2[30];//总出现次数
int p[200005];
int main()
{
    ios::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--)
    {
        memset(v1,0,sizeof(v1));
        memset(v2,0,sizeof(v2));//初始化
        memset(p,0,sizeof(p));
        int n,m;
        cin>>n>>m;
        cin>>s;
        for(int i=1;i<=m;i++)
            cin>>p[i];
        sort(p+1,p+m+1);//对p数组排序
        int q=1;//指针放在头部
        for(int i=0;i<n;i++)
        {
            v1[s[i]-96]++;//每次处理，净出现次数和总出现次数都+1
            v2[s[i]-96]++;
            int add=0;
            while(p[q]-1==i) q++,add++;//如果与当前p重合，指针后移，由于同一位置可能有多个pi，这里用while处理
            for(int j=1;j<=26;j++)
                if(v2[j]) v2[j]+=add*v1[j];//总出现次数加上净出现次数
        }//时间复杂度为O（n+m）
        for(int i=1;i<=26;i++)
            cout<<v2[i]<<" ";
        cout<<endl;
    }
    return 0;
}

```


---

## 作者：ShineEternal (赞：0)

[更佳的阅读效果。](https://blog.csdn.net/kkkksc03/article/details/104504619)


## description：
- 给定一个长度为 $n$ 小写字母字符串 $s$。（这里默认下标从 $1$ 开始）
- 给定一个长度为 $m$ 的数列 $p_i$。
- 对于每一个 $p_i$，表示你要统计 $s_1\sim s_{p_i}$所对应的字母各一次。
- 最终，你还要统计整个字符串的字母各一次。
- 你需要求出 $26$ 个小写字母中每个字母被统计过的次数。
- **多组数据**，数据组数不超过 $10^4$，$2\le n\le 2\times 10^5$，$1\le m\le 2\times 10^5$。
- translate by @[ShineEternal](https://www.luogu.com.cn/user/45475)。

## solution：
数据范围比较大，我们没法一一枚举，于是可以使用前缀和。

用前缀和将每一个位置的各个字母的出现次数进行提前统计，遇到 $p_i$ 的时候 $O(1)$ 查询就行了。

## code：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int p[200005];
char s[200005];
int mp[200005][30];
int Mp[30];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		for(int i=1;i<=30;i++)Mp[i]=0;
		int n,m;
		scanf("%d%d",&n,&m);
		scanf("%s",s);
		//printf("%s\n",s);
		for(int i=1;i<=m;i++)
		{
			scanf("%d",&p[i]);
		}
		p[m+1]=n;
		m++;
		for(int i=1;i<=26;i++)mp[0][i]=0;
		mp[0][s[0]-'a'+1]++;
		for(int i=1;i<n;i++)
		{
			for(int j=1;j<=26;j++)mp[i][j]=mp[i-1][j];
			mp[i][s[i]-'a'+1]++;
		}
		for(int i=1;i<=m;i++)
		{
			for(int j=1;j<=26;j++)
			{
				Mp[j]+=mp[p[i]-1][j];
			}
		}
		for(int i=1;i<=26;i++)
		{
			printf("%d ",Mp[i]);
		}
		printf("\n");
	}
	return 0;
} 
```

---

## 作者：Ludo (赞：0)

## Part 0. 一句话题解

用差分统计。

## Part 1. 思考过程

个人从看的那一刻开始就觉得比B题简单。B题我写得很丑。

题目就是给些下标 $p_i$, 让你求出字符串 $s_{1 \cdots p_i}$ 各个字符出现次数之和嘛。

怎么统计就是关键。

如果把它看成将 $1$ 到 $p_i$ 上的字符全部按一次。

不看字符，那不就是个差分？

也就是说，我们 **统计位置 $j$ 上的字符被按了多少次** 就可以了。

**良心的出题人**没有卡掉没开long long的人，虽然我一开始就开了，但是跑出来错没错貌似还不一定。

## Part 2. 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
char s[200041];
int n,m,l;long long sum,ans[30],cf[200001];
int main(void)
{
	int t;
	scanf("%d",&t);
	while (t--)
	{
		scanf("%d%d",&n,&m);
		scanf("%s",s+1);
		for (int i=1;i<=n;i++) cf[i]=0;
		for (int i=1;i<=26;i++) ans[i]=0;
		sum=0;
		cf[1]++;cf[n+1]--;
		for (int i=1;i<=m;i++)
		{
			scanf("%d",&l);
			cf[l+1]--;
			cf[1]++;
		}
		for (int i=1;i<=n;i++)
		{
			sum+=cf[i];
			ans[s[i]-'a'+1]+=sum;
		}
		for (int i=1;i<=26;i++)
		{
			printf("%lld ",ans[i]);
		}
		printf("\n");
	}
}
```


---

