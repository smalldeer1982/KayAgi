# Divisibility by 25

## 题目描述

You are given an integer $ n $ from $ 1 $ to $ 10^{18} $ without leading zeroes.

In one move you can swap any two adjacent digits in the given number in such a way that the resulting number will not contain leading zeroes. In other words, after each move the number you have cannot contain any leading zeroes.

What is the minimum number of moves you have to make to obtain a number that is divisible by $ 25 $ ? Print -1 if it is impossible to obtain a number that is divisible by $ 25 $ .

## 说明/提示

In the first example one of the possible sequences of moves is 5071 $ \rightarrow $ 5701 $ \rightarrow $ 7501 $ \rightarrow $ 7510 $ \rightarrow $ 7150.

## 样例 #1

### 输入

```
5071
```

### 输出

```
4
```

## 样例 #2

### 输入

```
705
```

### 输出

```
1
```

## 样例 #3

### 输入

```
1241367
```

### 输出

```
-1
```

# 题解

## 作者：CGDGAD (赞：7)

### 题解 $\text{CF988E}$

### 题目大意

给定你一个数，你每次可以交换相邻两个数位上的数，且交换完不含前导零。问最少交换几次可以使这个数能被 $25$ 整除。

### 解题思路

这道题使用**字符串**。

将原题换个说法：

> 给定你一个字符串，你每次可以交换相邻两个位置上的字符，且交换完前缀不是 `0`。问最少交换几次可以使这个字符串的后缀是 `00` `25` `50` `75` 。

那么具体怎么做呢？我们拿一个数 $4235816$ 来举例。

这个数长度 $len$ 为 $7$，且在这个数中， $5$ 的下标 $pos1$ 为 $3$， $2$ 的下标 $pos2$ 为 $1$ 。

很显然这个数最后要变成 `xxxxx25` 的形式。问题是，把 $2$ $5$ 移到右边需要几步。

先把 $5$ 移到最后一个位置:

```plain
0: 4235816
1: 4238516
2: 4238156
3: 4238165
```

移动了 $(7 - 3) - 1$ 次。再把 $2$ 移动到倒数第二个位置：

```plain
3: 4238165
4: 4328165
5: 4382165
6: 4381265
7: 4381625
```

这一部分移动了 $(7 - 1) - 2$ 次。结束。

不难发现，上述过程的移动次数为 $(len - pos1 - 1) + (len - pos2 - 2)$。

接下来可以定义一个函数。上述过程在这里可以表示为 `f('2', '5')`。

```cpp
// f(a, b): 将字符串后缀变成 'ab' 所需的最少步数
int f(char a,char b) {
    // x 为该字符串。
    int len = x.size(); // 字符串长度
    int p1 = x.rfind(b); // 从字符串的右边开始找b第一次出现的位置
    if (p1 == -1) return 99999999; // 如果没找到则返回
    x.erase(p1, 1); // 删除字符串的第p1个字符（即删除第一次出现的b）
    int p2 = x.rfind(a); // 同理
    if (p2 == -1) return 99999999;
    x.erase(p2, 1);
    // 处理前导零
    int sum = 0;
    while (x[sum] == '0') sum += 1;
    return sum + (len - 1 - p1) + (len - 2 - p2);
}
```

完整代码：

```cpp
#include <cstdio>
#include <iostream>
#include <string>
std::string s;
int f(char a,char b) {
    std::string x = s; // x为s的副本。防止在操作中更改s的值。
    int len = x.size();
    int p1 = x.rfind(b);
    if (p1 == -1) return 99999999;
    x.erase(p1, 1);
    int p2 = x.rfind(a);
    if (p2 == -1) return 99999999;
    x.erase(p2, 1);
    int sum = 0;
    while (x[sum] == '0') sum += 1;
    return sum + (len - 1 - p1) + (len - 2 - p2);
}
int main() {
    std::cin >> s;
    int ans = std::min( f('0', '0'), std::min( f('2', '5'), std::min( f('5', '0'), f('7', '5') ) ) );
    if (ans == 99999999) {
        printf("-1\n");
    } else {
        printf("%d\n", ans);
    }
    return 0;
}
```





---

## 作者：Pecco (赞：2)

这黄题想了我半天……

如果没有前导0其实是很简单的。众所周知能被25整除的数一定以00，25，50或75结尾，所以只需要分这四种情况，对每种情况分别找到最靠右的相应数对，那么把它们交换到结尾处即可，答案就是它们到结尾的数字个数之和。但是如果它们在数字串里的顺序与目标是反的，那么要再加上1。

但是这个前导0怎么处理呢？假设我们要交换到结尾的数是`i`和`j`，我们希望最终没有前导零，那么我们要把除了`i`和`j`以外、最靠左边的一个非零数`k`交换到最左边，这样才能保证整个过程中都不出现前导零。不过这个过程只需要统计0的数量，因为`i`/`j`和`k`交换不用计数——它们本来就要交换到`k`的右边，不需要额外的步数。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int D[20], m;
void fac(ll n)
{
    if (n >= 10)
        fac(n / 10);
    D[m++] = n % 10;
}
int run(int a, int b)
{
    int lasta = -1, lastb = -1;
    for (int i = m - 1; i >= 0; --i)
        if (D[i] == b)
        {
            lastb = i;
            break;
        }
    for (int i = m - 1; i >= 0; --i)
        if (D[i] == a && i != lastb)
        {
            lasta = i;
            break;
        }
    if (lasta == -1 || lastb == -1)
        return INT_MAX;
    int extra = 0;
    for (int i = 0; i < m && D[i] == 0 || i == lasta || i == lastb; i++)
        extra += (i != lasta && i != lastb);
    return m - lasta - 2 + m - lastb - 1 + extra + (lasta > lastb);
}
int main()
{
    ll n, x, y, mi = INT_MAX, extra = 0;
    cin >> n;
    if (n <= 24)
    {
        cout << -1 << endl;
        return 0;
    }
    fac(n);
    mi = min({run(0, 0), run(2, 5), run(5, 0), run(7, 5)});
    cout << (mi == INT_MAX ? -1 : mi) << endl;
    return 0;
}
```

---

## 作者：_edge_ (赞：1)

分类讨论！不存在的！

本篇题解不用任何分类讨论的技巧，不用任何细节，来造福后人。

~~但是有点小卡常。~~

首先，该题解需要用到状压 DP，不会请自行学习，或者写分类讨论。

我们可以认为，确定一个数即为确定每个数字所在的位置。

那么也就是说需要确定每个数字在的位置，这样求个类似于逆序对的即可。

更具体的，我们让每个数字有个不同的排名，然后按这个排名做排序。

然后问题就转换成了如何分配排名，同时使得在模 $25$ 下等于 $0$，求最小逆序对。

这东西是经典的状压 DP，我们设 $f_{S,i}$ 表示 $S$ 集合里面的数都被分配掉了，然后在模 $25$ 意义下是 $i$。

转移可以枚举下一个填什么，然后 $i$ 整体乘 $10$ 即可。

当然还有个逆序对的东西，这东西可以用前面已经确定的数来计算当前对前面产生的贡献。

具体的，如果当前这个数在已经分配了的数前面就要加上 $1$ 的贡献。

算完这些之后会发现复杂度有点小小爆炸 $O(2^n \times n^2 \times m)$，其中 $m$ 是 $25$ 级别的。

可以发现，逆序对这东西可以枚举状态的时候就预处理掉，变成了 $O(2^n 
\times n \times m)$。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int INF=19;
const int INFN=35;
int f[1<<INF][INFN],n,P[INF];
string s1;
signed main()
{
	memset(f,63,sizeof f);
	ios::sync_with_stdio(false);
	cin>>s1;n=s1.size();
	f[0][0]=0;
	for (int i=0;i<(1<<n);i++) {
		int xx=i,s=0;
		while (xx) {xx-=xx&-xx;s++;}
		for (int j=0;j<n;j++) P[j]=0;
		for (int j=0;j<n;j++) {
			if ((i&(1<<j))) continue;
			for (int k=0;k<n;k++)
				if (i&(1<<k) && k>j) P[j]++; 
		}
		
		
		for (int j=0;j<n;j++) {
			if (i&(1<<j)) continue;
			if (!i && (s1[j]=='0')) continue;
			for (int l=0;l<25;l++) {
				int sum=0,L=(l*10+s1[j]-'0')%25;
				f[i|(1<<j)][L]=min(f[i|(1<<j)][L],f[i][l]+P[j]);
			}
		}
	}
	if (f[(1<<n)-1][0]>1e8) cout<<"-1\n";
	else cout<<f[(1<<n)-1][0]<<"\n";
	return 0;
}
```


---

## 作者：xsI666 (赞：1)

本题是数论好题！

首先我们需要了解一个关于数论的性质：

		一个数只要后两位能被25（或4）整除，这个数就能被25（或4）整除。
        同理，后三位：125（或8）、后四位：625（或16）亦是如此。
   
所以，我们只需要判断n中有没有能被25整除的两位数即可。

注意：由于需要判断有没有能被25整除的两位数，应暴力枚举两个数在n中的位置，因此n最好采用C++中的string类型存储。

这里只给出字符串转数字的代码：

```cpp
int stos(string st)//把字符串转为数字
{
    int s=0;//最终转换成的数
    for (int i=0;i<st.size();i++)//按位置转换
    {
        s=s*10+(st[i]-'0');//转换这个数
    }
    return s;//返回它
}
```

部分 from @fmj_123

# 没有完整代码！

---

## 作者：cmll02 (赞：0)

首先这题显然是一个分类讨论，然而这个细节非常 ![](//啧.tk/tuu)。

于是我们就 bfs。

然而 bfs 一定会 T。

那么先把重复的扔掉，用 pbds 可以很快做到。

接下来我们发现 $2,7$ 没有区别，$1,3,4,6,8,9$ 没区别。

然后就过了？。

最坏情况下是 $\dfrac{18!}{4!5!4!5!}$ 次，约 $7\times 10^8$，CF 机子可过，并且卡不满。

```cpp
//#pragma GCC optimize(3)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <unordered_map>
#include <map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
#define int unsigned long long
inline int read()
{
    int num=0,f=1;char c=getchar();
    while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
    while(c>47&&c<58)num=(num<<3)+(num<<1)+(c^48),c=getchar();
    return num*f;
}
inline int min(int a,int b){return a<b?a:b;}
int a[20],l;
struct Node{
    int x,d;
}x;
std::queue<Node>q;
#define end {puts("-1");return 0;}
int cengyiceng[22];
inline int digit(int x,int pos)
{
    int q=cengyiceng[pos];
    return (x/q)%10;
}
inline int modi(int x,int pos,int y)
{
    int q=1,p=x;
    q=cengyiceng[pos];
    int qwq=digit(x,pos);
    p-=qwq*q;
    p+=y*q;
    return p;
}
int ok(int p)
{
    return (p==1||p==3||p==4||p==6||p==8||p==9);
}
gp_hash_table<int,bool> mp;
signed main()
{
    int n=read();
    cengyiceng[0]=1;
    for(int i=1;i<=20;i++)cengyiceng[i]=cengyiceng[i-1]*10;
    l=n;
    while(l)a[l%10]++,l/=10;
    if(a[0]>=2)goto ok;
    if(a[0]&&a[5])goto ok;
    if(a[5]&&a[2])goto ok;
    if(a[5]&&a[7])goto ok;
    end;
    ok:;
    int pos=1,deg=0;
    while(pos*10<=n)pos*=10,deg++;
    for(int i=0;i<=deg;i++)
    {
    	int p=digit(n,i);
    	if(ok(p))n=modi(n,i,1);
    	else if(p==2)n=modi(n,i,7);
    	if((a[5]==0)&&(p==2||p==7))n=modi(n,i,1);
    //	printf("%llu\n",p);
	}
	//printf("%llu\n",n);
	//700777111111222222
    x.x=n,x.d=0;
    q.push(x);
    mp[n+171487]=1;
    while(!q.empty())
    {
        x=q.front();q.pop();
        int u=x.x,d=x.d;
        if(u%25==0){printf("%llu\n",d);return 0;}
        for(int i=1;i<=deg;i++)
        {
            int hi=digit(u,i),lo=digit(u,i-1);
            if(ok(hi)&&ok(lo))continue;
            if(hi==lo)continue;
            int v=u;
            v=modi(v,i,lo);
            v=modi(v,i-1,hi);
            if(v>=pos&&mp[v+171487]==0)mp[v+171487]=1,q.push((Node){v,d+1});
        }
    }
    end;
}
```

---

## 作者：STOcjyORZ (赞：0)


### 大致思路
枚举+模拟；
简单在于好想；
难在于找匹配能被25整除的数；

#### 代码+注释如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans=999999,sum,tot;
char c[21];
bool pipei[11];//判断0，2，7，5是否用过了，选择最优的，所以只用用一次就行
int sou(int,int);
int tongji[11]={0};//开一个统计数组用于统计0--9各出现了几次（ps.是25倍数的
数字末两位一定是00或25或50或75，因此0、2、7、5数字个数上一定要满足基本的条
件，否则直接输出-1；）
int b[21]={0};//存储每一位上的数字
int main()
{
	memset(pipei,false,sizeof(pipei));//赋初值全没用过
	scanf("%s",c);
	 tot=strlen(c);
	for(int i=0;i<=tot-1;i++)
	{
		b[i+1]=c[i]-48;//转化为数字
		tongji[b[i+1]]++;//统计
	}
	long long  mo=b[tot-1]*10+b[tot];//刚开始是25倍数的话就不用挪了
	if(mo%25==0){
		cout<<0<<endl;
		return 0;
	}
	if(tongji[0]>=2||(tongji[2]>=1&&tongji[5]>=1)||(tongji[5]>=1&&tongji[0]>=1)||(tongji[7]>=1&&tongji[5]>=1))
	{	
		for(int i=tot;i>=1;i--)//从末尾开始找前面才能最优
		{
			if((b[i]==0||b[i]==2||b[i]==5||b[i]==7)&&pipei[b[i]]==false)
			{
				if(sou(b[i],i)<ans)ans=sou(b[i],i);//取小的答案存储
				else continue;
			}
		}
		cout<<ans;
	}
	else
	cout<<-1;//数字个数不满足的话直接输出-1
return 0;
}
int sou(int z,int w)//z是数值，w是b[]数组当前下标
{
	pipei[z]=true;
	if(z==0)
	{
		for(int i=w-1;i>=1;i--)
		{
			if(b[1]==5&&b[2]==0&&w!=2)
			break;
			else 
			{
				if(b[i]==0||b[i]==5)
				{
				sum=tot-w+tot-1-i;
				return sum;
				}
			}
		}
		return 99999;
	}
	else if(z==2||z==7)
	{
		for(int i=w-1;i>=1;i--)
		{
		
			if(b[i]==5)
			{
				if(i==1){
					int s=0;
					for(int j=2;j<=w-1;j++)//这个循
                  环于处理50687类似的数据
					{
						if(b[j]==0)s++;
					}
					sum=tot-i+tot-1-w+1+s;
				}
				else sum=tot-i+tot-1-w+1;
				return sum;
			}
		}
	return 99999;
	}
	else if(z==5)//依次找
	{
		for(int i=w-1;i>=1;i--)
		{
			if(b[i]==2||b[i]==7)//5找2、7能构成25、75
			{
				
				sum=tot-w+tot-1-i;
				return sum;
			}
			else if(b[i]==0)//5找0能构成50
			{
				
				sum=tot-w+tot-1-i+1;//位数处理，自己画一下模拟一下
				return sum;
			}
		}
		return 99999;
	}
}
```



---

