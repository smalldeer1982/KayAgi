# 密码 Password

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=247&page=show_problem&problem=3703

[PDF](https://uva.onlinejudge.org/external/12/p1262.pdf)

# 题解

## 作者：末将Mojo (赞：10)

上面的题解全部都用了DFS或者STLvector，那么我这里提出一种新思想来做这道题。

[题面](https://www.luogu.com.cn/problem/UVA1262)

带着求排列顺序的思想做这道题会很方便。

先看一组样例：

```
1
114
A Y G S U
D O M R A
C P F A S
X B O D G
W D Y P K
P R X W O
C B O P T
D O S B G
G T R A R
A P M M S
W S X N U
E F G H I
```

我们先来用手（或者眼睛）来试一下，发现符合题目要求的字母分别是：

一列ACDW（4） 二列BOP（3）三列GOMX（4）四列AP（2）五列GSU（3）

根据乘法原理，我们可以知道，总共有4 × 3 × 4 × 2 × 3=288种，所以当K大于288时，直接输出NO即可

我们先来看第一位，因为一列有4种字母，所以后面4列共有288/4=72种情况，也就是说，第一位是A,C,D,W各有72种可能

根据字典序的定义，我们可以知道，字典序第1-72的一定由A开头，字典序第73-144一定由C开头……以此类推。

所以我们在每一位上重复这个操作，就可以得出每一位是哪一个字母了。

细节见代码！

## **CODE**

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ri register int

using namespace std;

int lie[100][100],tot[100],sum[100][100][100],k;
char mp[15][15][15];//数组大小随意开的，实际用不到这么大

inline void clean(){
	memset(sum,0,sizeof sum);
	memset(tot,0,sizeof tot);
	memset(lie,0,sizeof lie);
	return;
}

int main(){
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--){
		cin >> k;
		clean();//多组数据清空数组
		for(ri t = 0; t < 2; t++)
			for(ri i = 1; i <= 6; i++)
				for(ri j = 1; j <= 5; j++)
					cin >> mp[i][j][t];
		for(ri i = 1; i <= 6; i++)
			for(ri j = 1; j <= 5; j++){
				sum[mp[i][j][0]-'A'][j][0] = 1;
				sum[mp[i][j][1]-'A'][j][1] = 1;//判断字母是否出现在第j列
			}
		for(ri j = 1; j <= 5; j++)
			for(ri i = 0; i < 26; i++)
				if(sum[i][j][0] && sum[i][j][1])
					lie[j][++tot[j]] = i;//从0-25遍历自动按字典序排序
		int length = 1;//length为排列数
		for(ri i = 1; i <= 5; i++)
			length *= tot[i];//乘法原理
		if(k > length){
			cout << "NO\n";
			continue;
		}
		for(ri i = 1; i <= 5; i++){
			length /= tot[i];//第i列的每个字母还有多少排列
			cout << (char)(lie[i][(k-1)/length+1]+'A');//仔细想想为什么是k-1而不是k（）
			k -= (k-1)/length*length;//同样，思考一下为什么不直接取模
		}
		cout << "\n";//别忘了换行
	}
	return 0;
}
```

第一次乏题解，求管理员大大通过！

---

## 作者：cyh_toby (赞：4)

## 题目

原题链接：[这里](https://www.luogu.com.cn/problem/UVA1262)

~~总感觉不应该给蓝色难度~~

题意应该好理解，这里就不赘述了。

## 分析

这题显然是$dfs$深度优先搜索做：因为数据量小，所以$dfs$枚举。

### 大致思路

以列为单位进行搜索。在每次搜索中，找出当前列中两个矩阵同时拥有的字母，加入答案序列$res[]$，并向下一列递归。

### 细节处理

- 题目要求字典序第$k$小的密码，方便起见，我们就直接按字典序从小到大进行$dfs$，找到第$k$个就结束并输出；如果整个$dfs$结束都没有输出，那么无解。

- **如何按字典序搜索？** 我们可以事先做一些预处理，有两种方法：

1. 对每一列进行排序，$dfs$时从上往下匹配字母即可。但要注意，**如果存在重复字母，应跳过**，因为那只能算一种密码

2. 对每一列开一个大小为$26$的数组，记录当前列每个字母是否出现，$dfs$时遍历此数组即可，没有重复字母的问题

### 坑点注意

- 记得初始化

- 读入字符要小心，尽量不要各种读入函数混用，可能会坑死你。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define gc getchar
int a[10][30], b[10][30];
int k, tot = 0;
char res[10];//答案数组 
void dfs(int cur){
	if(cur>5){
		tot++;
		if(tot==k){
			for(int i = 1; i <= 5; i++){
				printf("%c", res[i]);
			}
			printf("\n");
		}
		return;
	}
	for(int i = 0; i < 26; i++){
		if(a[cur][i]&&b[cur][i]){
			res[cur] = i+'A';
			dfs(cur+1);
			if(tot>k) return;
		}
	}
	return;
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--){
		tot = 0;
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		scanf("%d", &k);
		gc();
		for(int i = 1; i <= 6; i++){
			for(int j = 1; j <= 5; j++){
				char c = gc();
				a[j][c-'A']++;
			}
			gc();
		}
		for(int i = 1; i <= 6; i++){
			for(int j = 1; j <= 5; j++){
				char c = gc();
				b[j][c-'A']++;
			}
			gc();
		}
		dfs(1);	
		if(tot<k) printf("NO\n");
	}
	return 0;
}

```


---

## 作者：_Day_Tao_ (赞：0)

题目意思就是在找出一个长度为 $5$ 的字符串，满足每一位的字符在给出的两个矩阵中的对应列都出现过，并且字典序是第 $k$ 大的。

这个题还是比较好想的。首先不难想到直接暴力枚举出所有满足条件的字符，对于样例来讲：

```
AYGSU
DOMRA
CPFAS
XBODG
WDYPK
PRXWO

CBOPT
DOSBG
GTRAR
APMMS
WSXNU
EFGHI
```

找到的就是 `ACDW` `BOP` `GMOX` `AP` `GSU`。

然后考虑怎么找出字典序第 $k$ 大的。考虑对于一位上向后选一个字符的贡献，其实就是到这一位的后一位的后缀个数积，这个也是比较好理解的，就是相当于固定了前面的字符然后后面的字符任选的贡献。为了方便，我们将这个后缀个数积向左偏移一位，这样对于该位向后选择一个字符的贡献就是当前位记录的值了。对于 $0$ 号为储存的自然就是总方案数，若 $k$ 比这个要大那么就肯定无解，否则就对于每一位尝试往后取，减去相应贡献，减不够就考虑下一位即可。

**Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define ls root << 1
#define rs root << 1 | 1
#define int long long
#define mid ((l+r)>>1)
inline int read(){
	int x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
const int mod = 998244353;
const int INF = 0x7fffffff;
const int MAX = 2e5 + 5;
char c1[7][6],c2[7][6];
bool flag[6][27];
int k,cnt[6];
vector<char>vec[6];
signed main()
{
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	int T=read();
	while(T--)
	{
		k=read();
		for(int i=1;i<=6;i++) for(int j=1;j<=5;j++) cin>>c1[i][j];
		for(int i=1;i<=6;i++) for(int j=1;j<=5;j++) cin>>c2[i][j];
		memset(flag,0,sizeof(flag));
		for(int i=1;i<=5;i++) vec[i].clear();
		for(int i=1;i<=5;i++) for(int j=1;j<=6;j++) for(int k=1;k<=6;k++) if(c1[j][i]==c2[k][i]) flag[i][c1[j][i]-'A'+1]=1;
		for(int i=1;i<=5;i++) for(int j=1;j<=26;j++) if(flag[i][j]) vec[i].push_back(j+'A'-1);
		for(int i=1;i<=5;i++,puts("")) for(char j:vec[i]) cout<<j;
		cnt[5]=1; // 记录后缀积
		for(int i=4;i>=0;i--) cnt[i]=vec[i+1].size()*cnt[i+1];
		if(cnt[0]<k) {puts("NO");continue;}
		string ans="";
		for(int i=1;i<=5;i++)
		{
			int j=0;
			while(k-cnt[i]>0) ++j,k-=cnt[i];
			ans+=vec[i][j];
		}
		cout<<ans<<endl;
	}
	system("pause");
	return 0;
}
```

---

## 作者：happyZYM (赞：0)

首先，先按列处理出所有合法的字母，按字典序排列。
# 注意！有可能会有相同的字母！
接下来，从左到右计算应该选那个字母（无解的情况预处理一下就行了）
```cpp
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int T,k;
bool found[7][128];
char x;
vector<char> can[7];
int last[7];
int main()
{
#ifdef local
	freopen("pro.in","r",stdin);
#endif
	scanf("%d",&T);
	while(T-->0)
	{
		memset(found,0,sizeof(found));
		for(int i=1;i<=5;i++) can[i].clear();
		cin>>k;
		for(int i=1;i<=6;i++)
			for(int j=1;j<=5;j++)
				found[j][cin>>x,x]=1;
		for(int i=1;i<=6;i++)
			for(int j=1;j<=5;j++)
				if(found[j][cin>>x,x])
				{
					can[j].push_back(x);
					found[j][x]=0;
				}
		for(int i=1;i<=5;i++) sort(can[i].begin(),can[i].end());
		last[5]=1;
		for(int i=4;i>=0;i--) last[i]=last[i+1]*can[i+1].size();
		if(k>last[0]) cout<<"NO"<<endl;
		else
		{
			for(int i=1;i<=5;i++)
			{
			    int j=ceil((double)k/last[i])-1;
                /*
                计算出该用哪个字母。
                ∵ 如果 last[i]*(j+1)>=k 则用当前字符
                ∴ 向上取整再减1就是下标。
                */
			    cout<<can[i][j];
			    k-=last[i]*j;
			}
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：小闸蟹 (赞：0)

```cpp
// 直接按照字典序从小到大的顺序递归一个一个地枚举
#include <iostream>
#include <string>
#include <array>

int k, cnt;
std::array<std::array<std::string, 6>, 2> p;
std::array<char, 9> Ans;

bool DFS(int Col)
{
    if (Col == 5)   // 因为是从0开始搜的，所以边界是4 + 1
    {
        if (++cnt == k) // 如果找到了k个了
        {
            for (int i = 0; i < Col; ++i)   // 那就把这第k个输出
            {
                std::putchar(Ans[i]);
            }
            std::putchar('\n');
            return true;
        }

        return false;
    }

    std::array<std::array<bool, 26>, 2> Existed{ false };
    for (int i = 0; i < 2; ++i) // 遍历两个图
    {
        for (int j = 0; j < 6; ++j) // 把这一列出现到的字母都标记起来
        {
            Existed[i][p[i][j][Col] - 'A'] = true;
        }
    }
    for (int i = 0; i < 26; ++i)    // 递归地枚举每一个字母
    {
        if (Existed[0][i] && Existed[1][i]) // 如果这个字母在两张图中的同一列都出现了
        {
            Ans[Col] = 'A' + i; // 标记一下
            if (DFS(Col + 1))   // 继续搜下一列
            {
                return true;
            }
        }
    }

    return false;   // 注意最后这个不能少
}

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        std::cin >> k;
        for (int i = 0; i < 2; ++i) // 把两个图读入
        {
            for (int j = 0; j < 6; ++j)
            {
                std::cin >> p[i][j];
            }
        }

        cnt = 0;    // 当前是第几个按字典序找到的密码
        if (!DFS(0))    // 如果找不到任何一种解决方案，再输出"NO"
        {
            std::puts("NO");
        }
    }

    return 0;
}
```

---

