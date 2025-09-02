# Tanya and Toys

## 题目描述

In Berland recently a new collection of toys went on sale. This collection consists of $ 10^{9} $ types of toys, numbered with integers from $ 1 $ to $ 10^{9} $ . A toy from the new collection of the $ i $ -th type costs $ i $ bourles.

Tania has managed to collect $ n $ different types of toys $ a_{1},a_{2},...,a_{n} $ from the new collection. Today is Tanya's birthday, and her mother decided to spend no more than $ m $ bourles on the gift to the daughter. Tanya will choose several different types of toys from the new collection as a gift. Of course, she does not want to get a type of toy which she already has.

Tanya wants to have as many distinct types of toys in her collection as possible as the result. The new collection is too diverse, and Tanya is too little, so she asks you to help her in this.

## 说明/提示

In the first sample mom should buy two toys: one toy of the $ 2 $ -nd type and one toy of the $ 5 $ -th type. At any other purchase for $ 7 $ bourles (assuming that the toys of types $ 1 $ , $ 3 $ and $ 4 $ have already been bought), it is impossible to buy two and more toys.

## 样例 #1

### 输入

```
3 7
1 3 4
```

### 输出

```
2
2 5 
```

## 样例 #2

### 输入

```
4 14
4 6 12 8
```

### 输出

```
4
7 2 3 1
```

# 题解

## 作者：柳下惠 (赞：11)

[题目链接](https://www.luogu.com.cn/problem/CF659C)。

### 题目大意

给你两数 $n$ 和 $m$，$n$ 代表你拥有的玩具个数，$m$ 为你所有的钱数。告诉你你已经有的玩具编号，求你最多可以买多少个玩具，要求和你已经有的玩具不能重复，输出任意一组解即可。

### sol

考虑贪心。因为玩具的编号即为玩具的价钱，所以从小到大扫一遍即可，如果这个玩具已经买过就跳过，如果没买过并且你还有钱就入队，如果你的钱数不够了就跳出循环。

### code

```cpp
	n=read(),m=read();
	for(int i=1,t;i<=n;i++)
	{
		t=read();
		a[t]=1;
	}
	for(int i=1;i<=200000;i++)
	{
		if(a[i]) continue;
		m-=i;
		if(m<0) break;
		q.push(i);
	}
	printf("%lld\n",q.size());
	int w=q.size(); 
	for(int i=1;i<=w;i++)
	{
		printf("%lld ",q.front());
		q.pop();
	}
```

---

## 作者：liuyongle (赞：2)

#### 题意简述

> 有无数种商品，第 $i$ 个商品价值 $i$ 元，现在你已经有了 $n$ 个商品（并且知道这些商品的编号 $a_i$），你需要使用 $m$ 元去买尽量多的不同的商品，问你应该买哪些物品。

#### 思路分析

考虑贪心。既然已经有两篇题解写了 `map` 在本题的应用，那这篇就用 `vector` 写。

大致步骤：

1. 输入并从小到大排序；
2. 选取尽可能便宜的商品不断存入 `vector`；
3. 输出 `vector` 的 `size` 和 每一项。

代码：

```cpp
#include<bits/stdc++.h>
typedef long long LL;

using namespace std;

const int max=1e5+5;

int n,m,cas=1,T;
LL a[maxn];
vector<int> ans;

int main() {
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	for(int i=1,j=1;;++i) {
		if(j<=n && i==a[j])
			++j;
		else if(m<i)
			break;
		else
			m-=i,ans.push_back(i);
	}
    printf("%d\n",ans.size());
	for(int i=0;i<ans.size();++i)
        printf("%d ",ans[i]);
	return 0;
}
```

#### 后记

本题中的代码对于 `vector` 的遍历使用的是：

```cpp
for(int i=0;i<ans.size();++i)
```

而对于 C++11 及以上的标准，可以采用以下语句实现遍历：

```cpp
for(auto i:ans)
```

---

## 作者：Lucifer_Bartholomew (赞：2)

# 贪心
对于每个已经拥有了的玩具,用一个bool数组标记,从1开始往后看,没被标记过就取,取到m值小于0为止。
```cpp
#include <map>
#include <cstdio>
#include <algorithm>
#define rr register int
#define ll long long
using namespace std;
inline int read()
{
	char ch=getchar();
	int f=1,x=0;
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int a[100001];//记录取了哪些
map<int,bool> ma;//范围1e9,所以用map映射标记,也可以用bitset
int main()
{
	int n=read(),m=read();
	for(rr i=1;i<=n;++i)
		ma[read()]=1;//标记
	int sum=0;//记取了多少个
	for(rr i=1;;++i)
		if(!ma[i])//没被标记过的就取
		{
			m-=i;
			if(m<0)//取完就处理
			{
				printf("%d\n",sum);
				break;
			}
			else a[++sum]=i;
		}
	for(rr i=1;i<=sum;++i)//输出取了的数
		printf("%d ",a[i]);
	return 0;
}
```
~~我是蒟蒻~~

---

## 作者：WCG2025 (赞：1)

zhuo的~~水~~题


------------

就是这个人他已经有n个玩具和m元钱，每种玩具的价钱就等于它的序号，问他最多能有多少种玩具，并输出新增玩具的数量和编号

没什么思路好说的，就是直接贪，从价钱最少的扫一遍，总和大于m的时候就直接输出就好了

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    char ch=getchar();
    int x=0,f=1;
    while(ch<'0'||ch>'9')
    {
       if(ch=='-') f=-1;
       ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
       x=x*10+ch-'0';
       ch=getchar();
    }
    return x*f;
}
bool cmp(int a,int b)
{
	return a<b;
}
int n,m;
int sum;
int ans;
int cnt;
int x[100005];//用于存储答案
int a[100005];
map<int,bool> f;//用于存储是否已经提前拥有
int main()
{
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		f[a[i]]=1;
	}
	for(int i=1;;i++)//从最小的开始贪
	{
		if(f[i]==1)//已经有了的就直接跳过
		continue;
		else
		{
			if(i+sum<=m)
			{
				x[++cnt]=i;//记录答案
				sum+=i;
				ans++;
			}
			else
			break;//目前都不够以后更不够，直接跳
		}
	}
	printf("%d\n",ans);
	for(int i=1;i<=cnt;i++)
	{
		printf("%d ",x[i]);
	}
	return 0;
}
```


---

## 作者：MuYC (赞：1)

#### 水话
这道题一开始，我看成了是要把钱花完，后来一看，根本不需要强制把钱花完。

#### 思路&做法
首先很显然的一点，就是我们显然要先选编号小的，因为对于每一个玩具，它们对答案的贡献是一样的，但是编号小的花费就小，那为什么不买小的？

（倘若强制要求钱恰好花完，这个贪心的正确性就没了，因为不能保证有解)

我们可以很容易的证明答案显然不会超过$\sqrt{2*m}$，假设答案是最多买$k$个，因为每一个玩具只能买一次，就算按照$1,2,3,4,5,6,7,8...k - 2 , k - 1 , k$这样子买，这个式子的答案就是$\frac{k*(k-1)}{2}$，这个$k$也不会大于$\sqrt{2*10^9}$

倘若你换做更劣的购买方式，那么答案显然还会更小。

那么大于$2 * 10^5$的数我们还需要保存吗？很显然不用。因为在$2*10^5$任意取$10^5$个数，它们的和就一定可以大于$10^9$了，我何必去枚举大于$2*10^5$的数?为什么要开到$2*10^5$，是因为可能所有的一开始已经有了的玩具的编号都小于等于$2*10^5$！

所以按照这个方式扫一遍，最坏时间复杂度是O$(n + \sqrt{m})$的，这也就是为什么我能跑到运行时间$Rank1$.......。用$map$者最坏$O(nlog(n) + \sqrt{m}$ * $map$的大常数)，数据大点不怕会挂吗.......

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int MAXN = 200005,Max = 200000;
bool book[200005];//用于标记哪一些是已经有了的。
int arr[100005],n,tail = 0,M;

inline int read()
{
	int x = 0 , flag = 1;
	char ch = getchar();
	for( ; ch > '9' || ch < '0' ; ch = getchar());
	for( ; ch >= '0' && ch <= '9' ; ch = getchar())x = (x << 3) + (x << 1) + ch - '0';
	return x * flag;
}

int main()
{
	n = read() , M = read();
	for(int i = 1 ; i <= n ; i ++)
	{
		int x = read();
		if(x <= Max)//如果x > 2e5就没必要存了
		book[x] = 1;
	}
	for(int i = 1 ; i <= Max ; i ++)
	{
		if(book[i])continue;
		M -= i;
		if(M < 0)break;//买不起了，就弹出来。
		tail ++ , arr[tail] = i;//进入答案队列
	}
	printf("%d\n",tail);
	for(int i = 1 ; i <= tail ; i ++)
		printf("%d ",arr[i]);
	return 0;
}
```

题外话：

建议这道题注明$SPJ$！一开始我差点被吓得不敢交，因为这道题貌似没有注明是$SPJ$

另外这道题作为蓝题确实数据水了点，建议$m$增大到$5*10^{13}$,$n$增大到$8*10^6$，或者可以把这道题的难度评分下调。

---

## 作者：Jeremiahy (赞：0)

# 分析

考虑一种贪心策略：从小到大选没选过的。因为已有的玩具不能选，并且要想买最多的玩具只能尽量挑便宜的。

我用 ```set``` 来维护每个数字是否出现过，主要步骤如下：

1. 输入已有的玩具编号，并加入集合中。

1. 从 $1$ 开始枚举，遇见没有的玩具并且能够买这个玩具时（钱足够），将它买下，记录答案。

1. 直到钱不够了，输出。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, a[100005], sum, h, tot;//a 数组记录答案，sum是已花的钱，h用来输入已有的玩具，tot是能买到多少玩具
set<int> s;//集合 s
signed main() {
    cin >> n >> m;
    for (register int i = 1; i <= n; i++) 
		cin >> h, s.insert(h);//输入已有玩具并存储
    for (register int i = 1; ; i++)
    	if (sum + i <= m) {//有钱买
    		if (!s.count(i))//没有这个玩具
    			sum += i, a[++tot] = i;//买了，记录答案
		}
    	else//钱不够就停止
			break;
	cout << tot << "\n";//输出方案
	for (register int i = 1; i <= tot; i++)
		cout << a[i] << ' ';
    return 0;
}
```


---

## 作者：GacHen (赞：0)

贪心，用 `set` 去维护。

将已有的值插入 `set` 中。

之后枚举每一种价格，对于没出现过的，用已有的钱减去这种价格并记录答案，当已有的钱无法满足当前价格时退出。

最后按格式输出即可。

```
#include<bits/stdc++.h>
using namespace std;
const int M = 1e6+7;
int f,ans[M],js = 1,tot;
set<int>s;
int main() {
    int n,m;
    cin>>n>>m;
    for(int i = 1;i <= n;++ i) scanf("%d",&f),s.insert(f);
    while(m - js >= 0) {
        if(!s.count(js)) m -= js,ans[++tot] = js;
        js ++;
    }
    printf("%d\n",tot);
    for(int i = 1;i <= tot;++ i) printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：Rmax (赞：0)

### 题目大意

给你两个数 $ n $ $ m $ ，$ n $ 代表你拥有的玩具个数，$ m $ 为你所有的钱数。告诉你你有的玩具的编号，求你最多能买的玩具个数，要求和你已经有的玩具不能重复。

------------



### 思路


------------

考虑贪心。从小到大扫一遍，因为玩具的价格等于它的编号，如果玩具买过就跳过它，如果没买过并且你还有钱就入队，如果你的钱数不够就跳出循环。

------------


### 代码


------------

```
#include<bits/stdc++.h>
#include<map>
#include<cmath>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define reg register
using namespace std;
const int N=1e6+5;

int n,m,num,a;//num用来记录你还可以买的玩具数 
int toy[N],p[N];//p用来标记哪些玩具已经有了 

int main()
{
	freopen("toys.in","r",stdin);
	freopen("toys.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=n;i++)
	scanf("%d",&a),p[a]=1;//输入已有玩具编号并在p中标记 
	for(reg int i=1;;i++)
	{
		if(p[i]) continue;//如果已经有了就直接跳过 
		m-=i;
		if(m<0)//钱花完了 
		{
			printf("%d\n",num);//输出还可以买的玩具的个数 
			break;//终止循环 
		}
		num++,toy[num]=i;//可以买的玩具的个数++，并在toy数组中记录该玩具的编号 
	}
	for(reg int i=1;i<=num;i++)//买的玩具数 
	printf("%d ",toy[i]);//输出买的玩具的编号 
	return 0;
}
```

---

## 作者：Aisaka_Taiga (赞：0)

## 基本思路

本题主要用到的是贪心的思想，具体方法是把买过的玩具标记一下，然后从一块的往后一直找，没买过的买上，买超了退出循环，退掉最后多出来的那一个，输出后来买的玩具数量和买的玩具编号就好了。

答应我，一定要开 long long。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
map<int,int>q;//map自带离散化 存放当前值有没有用过 
int n,m,ww,sum=0,a[10000100],cnt=0;//sum计算当前选上的玩具的价钱和，cnt计算拿了多少玩具，a存放后来买的玩具 
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&ww);
		q[ww]=1;//把已经有的玩具标记 
	}
	for(int i=1;i<=m;i++)//从第一个开始往后一个一个找 
	{
		if(!q[i])//如果没买过 
		{
			sum+=i;//买! 
			a[++cnt]=i;//存进a里 
		}
		if(sum>m)//如果大于了 
		break;//钱不够了退出 
	}
	cnt--;//退掉最后买的 
	cout<<cnt<<endl;//输出 
	for(int i=1;i<=cnt;i++)
	cout<<a[i]<<" ";//输出买了哪些玩具 
	return 0;//好习惯 
 } 
```


---

## 作者：bloodstalk (赞：0)

~~这个题最多橙题吧~~

## 题目大意
你有 $n$ 个已经买了的玩具，还有 $m$ 元，求最多还可以买多少个不重复的玩具（玩具的编号等于花费）。

## 思路
### 贪心
要买最多个，就要使得玩具的价值最小。于是我们就从最小的 $1$ 开始枚举，找到没买的就加上，一直加到总价值大于 $m$ 为止。

考虑数据范围， $m \leq 10^9$ 单纯用数组来模拟桶肯定不行，所以我们考虑用 map ,用 map 来做，暴力解决问题。

## 代码实现

```
#include<bits/stdc++.h>
using namespace std;

map <int,int> mp;/*存已经出现过的玩具*/
map <int,int> cun;/*存要购买的玩具*/
int n,m,cnt;
long long tot;/*保险起见，开long long*/

int main()
{
	/*freopen("toys.in","r",stdin);
	freopen("toys.out","w",stdout);*/
	scanf("%d%d",&n,&m);
	int a;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a);
		mp[a]=1;/*之前买了，就不能买重复的了*/
	}
	for(int i=1;i<=1e9;i++)/*1到1e9扫一遍*/
	{
		if(mp[i] == 0)/*贪心，没买过就加上*/
		{
			if(tot+i <= m)
			{
				cun[++cnt]=i;
				tot+=i;
			}
			else/*超出限制了就输出*/
			{
				printf("%d\n",cnt);/*买的物品个数*/ 
				for(int j=1;j<=cnt;j++)
					printf("%d ",cun[j]);/*物品编号*/
				return 0;	
			}
		}	
	}
	return 0;
}
```


---

## 作者：Low_key_smile (赞：0)


#### 思路：（这里是思路）
这道题就是用一个桶来装下现在有的，然后从 $1$ 开始枚举到输入的点 $m$ ，因为不可能大于 $m$ (这个是因为玩具编号等于价格，而价格最大数肯定不能超过所最大的玩具编号，即最大价格)，所以到当前你输入的店即可，然后就用一个变量记录一下总和，如果超过了 $m$ ，那就停下来输出记录下当前的位置，一会循环直接输出全部。
    
    
### code（纯代码）
```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=2e5+5;
int a[N];
int n,m;
int k;
int c, Ans;

inline char readchar() {static char buf[100000], *p1 = buf, *p2 = buf; return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;}
inline int read() {int res = 0, f = 0; char ch = readchar(); for(; !isdigit(ch); ch = readchar()) if(ch == '-')f = 1; for(; isdigit(ch); ch = readchar()) res = (res << 1) + (res << 3) + (ch ^ '0'); return f ? -res : res;}

signed main() 
{
	//freopen("toys.in" , "r" ,stdin);
	//freopen("toys.out" , "w", stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++ ) 
	{
		k=read(); 	
		a[k]++;	
	}	
	for(int i=1;i<=m;i++)  
	{
		if(a[i]==0 and Ans+i<=m) 
		{
				Ans+=i;
				c++;
				a[c]=i;
		}
		if(Ans+i>m) 
		break;
	}		
	cout<<c<<endl;
	for(int i=1;i<=c;i++)
	{
		cout<<a[i]<<" ";
	}
	fclose(stdin);
	fclose(stdout);
	
	return 0;
}
```

---

## 作者：Sternenlicht (赞：0)

恶意评分了，应该是黄题。

思路：贪心。

先读入数据，用 map 映射，读入的玩具说明是已有的，标记为 1。

循环，若第 $i$ 个玩具没有被标记，说明是没有的，取走，令 $m$ 减去玩具价格 $i$。

若减完后 $m<0$，已经没钱了，退出循环。否则，用 ans 数组记录当前玩具编号，记录玩具个数的 cnt 加 1。

循环结束后，输出 cnt 的值，代表一共取了几个玩具，再输出取的玩具编号。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define endl '\n'
#define lowbit(x) (x&-x)
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define INF 0x3f3f3f3f
namespace IO{
	inline LL read(){
	    LL x=0,f=1;char ch=getchar();
	    for (;!isdigit(ch);ch=getchar())if (ch=='-')f=-1;
	    for (;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+(ch^48);
	    return x*f;
	}
	inline void write(LL x,char c='\n'){
	    if (x){
	    	if (x<0)x=-x,putchar('-');
	    	char a[30];short l;
	    	for (l=0;x;x/=10)a[l++]=x%10^48;
	    	for (l--;l>=0;l--)putchar(a[l]);
		}
		else putchar('0');putchar(c);
	}
	inline char getc(){
		char ch=getchar();
		while (isspace(ch))ch=getchar();
		return ch;
	}
}
using namespace IO;
using namespace std;

const int N = 1e5+10;
map<int,bool> mp;//用map映射，mp[i]表示第i个玩具有没有取 
int ans[N],cnt,n,m;//ans数组记录答案，cnt记录取的玩具数量 
int main(){
	n=read(),m=read();
	for (int i=1;i<=n;i++)mp[read()]=1;//给有的玩具打上标记 
	for (int i=1;;i++)
		if (!mp[i]){//没有当前玩具 
			m-=i;//减去钱数 
			if (m<0)break;//取完了，退出循环 
			else ans[++cnt]=i;//否则存入ans数组 
		}
	write(cnt);//输出玩具数量 
	for (int i=1;i<=cnt;i++)write(ans[i],' ');//输出取的玩具 
	return 0;
}
```

---

## 作者：CuSO4_and_5H2O (赞：0)

### ~~水话~~

题目难度最多是个黄啊，为什么是蓝啊喂！

这个题目过于简单，下边的题解已经讲的清楚了，但是我觉得还能再优化以时间，让他跑的更快（适合于这个题的思路已经会了的童鞋），这个思路有很多场景的应用。

首先你要知道为什么这个题目用不普通的桶不行，因为太大了，十亿的话空间肯定会没，所以有的小机灵鬼就会说:"我会 map！"。对，map 可以解决空间的问题，但是 map 时间复杂度太高了，数据强的话会超时。但我们转念一想，十亿好像是钱数诶，所以如果前边的全都买的话就只买 $44721$ 个钱就不够花了，那么这样的话空间开到 $44722$ 就可以了，这个数是怎么算出来的呢？当然不是手算啊，你不是有计算机吗！

```
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main(){
	int i=1,j=0;
	for(i=1;j<=1e9;i++,j+=i);
	cout<<i;
	
}

```
自己写个简单的代码就能算出来的。但你如果空间开到这个数如果数据强一点的话也会被爆（不是指范围变大，而是再范围内数据变强），为什么呢，不是最多 $44721$ 吗？那万一之前买的物品是前十万呢，按就要买到 $109545$ 个才行，怎么算出来的呢？就是把上边的代码的 `i=1` 换成 `i=1e5` 就可以了。

剩下的就贪心就行了。

```
#include<bits/stdc++.h>
#define int long long
const int N=119540;//开大一万，安心 
using namespace std;

int n,m,x,t[N],a[44722],ans;
 
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&x);
		t[x]=1;
	}
	for(int i=1;i<=m;i++)
	{
			if(t[i]==0)
			a[++ans]=i,m-=i;
	}
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++) printf("%lld ",a[i]);
	return 0;
}

```


---

