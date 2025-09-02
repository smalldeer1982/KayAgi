# Sumsets

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1066

[PDF](https://uva.onlinejudge.org/external/101/p10125.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10125/29d92f1d32bdaefa1d311d7a2aa7e97895e4a322.png)

## 样例 #1

### 输入

```
5
2
3
5
7
12
5
2
16
64
256
1024
0```

### 输出

```
12
no solution```

# 题解

## 作者：panxz2009 (赞：5)

## 题意简述 
- 给一个集合 $S$，找一个最大的数 $d$ 满足 $a+b+c=d$，且 $a$，$b$，$c$，$d$ 是集合 $S$ 中不同的数。

## 解题思路

思路很简单，将 $a+b+c=d$ 中的 $c$ 移项到右边，变为 $a+b=d-c$。可以用 map 记录下所有可能的 $a+b$ 的值，再枚举所有的 $c$ 和 $d$，对于每一组 $c$ 和 $d$，计算出 $d-c$，并查找是否出现此值。如果出现过，并且 $a$，$b$，$c$，$d$ 是两两不相同的数，那么打擂台找出最大的 $d$ 即可。

注意当枚举结束后若没有任何数符合要求，要输出 no solution。

总的时间复杂度应该是 $O(tn^2)$，其中 $t$ 表示测试数据组数。本题数据中貌似 $t$ 很小，所以可以过。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010,INF=0x3f3f3f3f;
int n,a[N],c,x,y,res;
unordered_map<int,pair<int,int> > mp;
int main() {
	while(scanf("%d",&n),n) {
		mp.clear();
		res=-INF;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++) 
				mp[a[i]+a[j]]=make_pair(i,j);//记录下所有的a+b的值
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(i!=j) {
					c=a[i]-a[j];//计算出d-c
					if(mp[c].first!=0) {
						x=mp[c].first;
						y=mp[c].second;
						if(x==i || x==j || y==i || y==j) continue;
						res=max(res,a[i]);//打擂台求出最大的d
					}
				}
		if(res==-INF) printf("no solution\n");
		else printf("%d\n",res);
	}
	return 0;
}
```

---

## 作者：Surelysuper (赞：4)

这题数据非常玄学，可以通过暴力跑到最优解。。。

除了一些小细节几乎没有任何难度

讲解见注释
```
#include<iostream>
#include<algorithm>
using namespace std;
int n,a[10010];
bool ok;
int main()
{
    while(cin>>n&&n)//输入
    {
        ok=0;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        sort(a+1,a+n+1);//排序
        int maxn=-2147483648;//初始化max
        for(int i=n;i>=1;i--)//直接暴力四层循环
        {
            for(int j=1;j<=n;j++)
            {
                for(int k=j+1;k<=n;k++)
                {
                    for (int l=k+1;l<=n;l++)
                    {
                        if(a[j]+a[k]+a[l]==a[i]&&i!=j&&i!=k&&i!=l&&j!=k&&j!=l&&k!=l)//全代码最重要的判断
                        {
                            maxn=max(maxn,a[i]);
                            ok = 1;
                        }
                    }
                    if(ok)
                        break;
                }
                if(ok)
                    break;
            }
            if(ok)
                break;
        }
        if(!ok)
            cout<<"no solution"<<endl;//判断输出
        else
            cout<<maxn<<endl;
    }
    return 0;//完结撒花
}
```

---

## 作者：ygsldr (赞：3)

刘汝佳蓝书里的一道题，还是比较有趣的一道题。

应为要求输出最大的d,首先我们进行排序

首先考虑暴力解法，我们需要枚举a,b,c,d,复杂度达到O(n^4),显然是无法承受的

假如我们枚举a,b,c,二分查找d,复杂度也达到O(n^3logn),也就是说，假如枚举3个数，我们的时间复杂度始终存在O(n^3)的下限瓶颈，所以我们需要考虑只枚举两个数


将等式化为a+b=c-d,假如我们先枚举a,b，并将a+b其存入一个数据结构中，再枚举d,c,在这个数据结构中查找d-c,复杂度将降到O(n^2*(操作数据结构的常数))(a+b总共用n^2种可能)。这种方法就是中途相遇法。

那么选择什么样的数据结构呢?,假如使用map,那么时间复杂度将达到O(n^2logn^2),极端数据下复杂度达到10^8,显然是无法承受的，所以我们要考虑复杂度更低的数据结构——hash。通过hash将常数降到接近O(1)，总复杂度降为O(n^2),就可以愉快的AC了。

参考代码如下：
```cpp
#include <cstdio>
#include <set>
#include <cstring>
#include <algorithm>
using namespace std;

struct Hash
{
    int x;
    int apos,bpos;
    Hash *next;
};//挂链法防止冲突 

Hash hash[1123456],*first[21234567];


int hashval(int x)
{
    return ((x << 1) + (x >> 1)) & 16777215;
}//hash函数 

int hashmapnum(0);

void insert(int x,int pos1,int pos2)
{
    int ithash = hashval(x);
    ++hashmapnum;
    Hash &addhash = hash[hashmapnum];
    addhash.x = x;
    addhash.apos = pos1;
    addhash.bpos = pos2;
    addhash.next = first[ithash];
    first[ithash] = &addhash;
}//链表插入hash 


void init()
{
    hashmapnum = 0;
    memset(first,0,sizeof(first));
}//清空指针 


int s[1123];
int main()
{
    int n;
    while(scanf("%d",&n) != EOF && n != 0)
    {
        init();
        for(int i(1);i <= n;++i)
        {
            scanf("%d",&s[i]);
        }
        sort(s + 1,s + n + 1);
        for(int i(1);i < n;++i)
        {
            for(int j(i + 1);j <= n;++j)
            {
                insert(s[i] + s[j],i,j);
            }
        }//将a+b插入hash表
		
		 
        bool k(false);
        for(int d(n);d >= 1;--d)//从大往小枚举 
        {
            for(int c(1);c <= n;++c)
            {
                if(d == c)continue;
                int val = s[d] - s[c];
                int ithash = hashval(val);
                for(Hash *itr(first[ithash]);itr;itr = itr->next)
                {
                    if(itr->x == val)
                    {
                    	int pos1 = itr->apos,pos2 = itr->bpos;
                        if(pos1 != c && pos1 != d && pos2 != c && pos2 != d)
                        {
                            k = true;
                            printf("%d\n",s[d]);
                        }
                        break;
                    }
                }//在hash表中查找 
                if(k)break;
            }
            if(k)break;
        }
        if(!k)printf("no solution\n");
    }
    return 0;
}



```

---

## 作者：_Deer_Peach_ (赞：2)

题意：给一个有 $n$ 个数的集合 $S$，找出一个最大的 $d$ 满足 $a+b+c=d$，$a$，$b$，$c$，$d$ 为集合中不同的数。

思路：

首先，如果你暴力枚举四个数，理论上是会超时的，但是过了。

代码如下，只是加了一点小优化：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n;
int a[N];
signed main(){
	while(scanf("%d",&n)){
		if(n==0)break;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		sort(a+1,a+n+1,greater<int>());//从大到小排序，下面从大到小遍历
		bool flag=false;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(i==j)continue;//相同的数字
				for(int k=j+1;k<=n;k++){
					if(i==k)continue;//相同的数字
					for(int l=k+1;l<=n;l++){
						if(l==i)continue;//相同的数字
						if(a[i]==a[j]+a[k]+a[l]){//a[i]就是最大的d
							printf("%d\n",a[i]);
							flag=true;//找到答案标记
							break;
						}
					}
					if(flag)break;
				}
				if(flag)break;
			}
			if(flag)break;
		}
		if(!flag)printf("no solution\n");//未标记也就是无解
	}
	return 0;
}
```
这个方法应该都能想出来。[记录](https://www.luogu.com.cn/record/215547556)。

然后，$n \le 1000$，那么正解的时间复杂度应为 $\mathcal O( t n ^ 2)$。

很简单的，把 $c$ 移项到左边，使等式成为 $a+b=d-c$，枚举 $a+b$ 后并记录 $a$ 和 $b$。再枚举 $d-c$，再寻找有没有记录过相等的 $a+b$，再判断四个数是否不同。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n;
int s[N];
signed main(){
	while(scanf("%d",&n)){
		if(n==0)break;
		for(int i=1;i<=n;i++)scanf("%d",&s[i]);
		map<int,pair<int,int> >mp;
		sort(s+1,s+n+1);
		for(int i=1;i<=n;i++){//枚举a+b并记录
			for(int j=i+1;j<=n;j++){
				mp[s[i]+s[j]]={s[i],s[j]};
			}
		}
		bool flag=false;
		for(int i=n;i>=1;i--){//从大到小遍历d
			for(int j=1;j<=n;j++){
				if(i==j)continue;//相同的数字
				int a=mp[s[i]-s[j]].first;
				int b=mp[s[i]-s[j]].second;
				if(a+b!=s[i]-s[j]||a==s[i]||a==s[j]||b==s[i]||b==s[j])continue;//判断是否有a+b=d-c并判断是否有相同数字
				printf("%d\n",s[i]);
				flag=true;//标记
				break;
			}
			if(flag)break;
		}
		if(!flag)printf("no solution\n");//未标记即无解。
	}
	return 0;
}
```
[记录](https://www.luogu.com.cn/record/215547435)。大概是因为用 map，导致时间比暴力还慢。

---

## 作者：sun_qy (赞：2)

# UVA10125 Sumsets 题解

[洛谷原题链接](https://www.luogu.com.cn/problem/UVA10125)

[老师](https://www.luogu.com.cn/user/36176)刚讲完，写篇题解理一下思路。

## 题意简述

题意其实很明确，给定一个集合 $S$，寻找其中的四个元素 $a,b,c,d$ 使得 $a+b+c=d$ 且这四个数两两互异，求出 $d$ 的最大值。

## 思路

对于等式  $a+b+c=d$，直接枚举肯定会 TLE 飞，考虑将其变形为 $a+b=d-c$ 的形式以便于映射，通过链表的方式进行处理。

首先，对于链表中的每一个元素，考虑定义一个结构体以存储 $d,c$ 的值。另外对于每个元素可以建立一个**权值**的概念，用以存储 $d-c$ 即其对应 $a+b$ 的值，一会儿用于枚举。对于链表的储存，可以用哈希的小技巧。

```cpp
//链表的建立
int head[MOD];
struct node {
	int key, d, c;
	int nxt;
};
inline int hashe(int x) {
	return ((x % MOD) + MOD) % MOD;
}
node lis[MOD];
```

接着将储存答案的变量初始化为给定的最小值 $-536870912$，对于多组数据要清空。

```cpp
//初始化
int n, a[N], cnt, ans;
inline void init() {
	cnt = 0;
	ans = -536870912;
	memset(head, 0, sizeof(head));
}
```

接下来用上刚写的链表来维护所有的 $d-c$。有个细节，由于减法不具有交换律，内层循环应采取从 $j=1$ 开始，当 $i=j$ 的时候跳过本次循环的处理方式。

```cpp
//数据写入
for(int i = 1; i <= n; i ++) {
	for(int j = 1; j <= n; j ++) {
		if(i == j) continue;
		lis[++ cnt] = {a[i] - a[j], a[i], a[j], head[hashe(a[i] - a[j])]};
		head[hashe(a[i] - a[j])] = cnt;
	}
}
```

接下来遍历链表寻找符合条件的 $a+b$，打擂台找到最大的 $d$ 即可。注意：这里的 $a,b,c,d$ **两两互异**，应做出判断。

```cpp
for(int i = 1; i <= n; i ++) {
	for(int j = i + 1; j <= n; j ++) {
		if(!head[hashe(a[i] + a[j])]) continue;
		for(int x = head[hashe(a[i] + a[j])]; x; x = lis[x].nxt) {
			if(lis[x].key != a[i] + a[j]) continue;
			if(lis[x].d == a[i] || lis[x].c == a[i] || lis[x].d == a[j] || lis[x].c == a[j]) continue;
			ans = max(ans, lis[x].d);
		}
	}
}
```

最后输出答案即可，时间复杂度 $O(Tn^2)$，能过。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1002, MOD = 1000007;
int n, a[N], cnt, ans;
int head[MOD];
struct node {
	int key, d, c;
	int nxt;
};
inline int hashe(int x) {
	return ((x % MOD) + MOD) % MOD;
}
node lis[MOD];
inline void init() {
	cnt = 0;
	ans = -536870912;
	memset(head, 0, sizeof(head));
}
signed main() {
	ios :: sync_with_stdio(0), cin.tie(0);
	while(cin >> n && n) {
		init();
		for(int i = 1; i <= n; i ++) cin >> a[i];
		for(int i = 1; i <= n; i ++) {
			for(int j = 1; j <= n; j ++) {
				if(i == j) continue;
				lis[++ cnt] = {a[i] - a[j], a[i], a[j], head[hashe(a[i] - a[j])]};
				head[hashe(a[i] - a[j])] = cnt;
			}
		}
		for(int i = 1; i <= n; i ++) {
			for(int j = i + 1; j <= n; j ++) {
				if(!head[hashe(a[i] + a[j])]) continue;
				for(int x = head[hashe(a[i] + a[j])]; x; x = lis[x].nxt) {
					if(lis[x].key != a[i] + a[j]) continue;
					if(lis[x].d == a[i] || lis[x].c == a[i] || lis[x].d == a[j] || lis[x].c == a[j]) continue;
					ans = max(ans, lis[x].d);
				}
			}
		}
		if(ans == -536870912) printf("no solution\n");
		else printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：_cmh (赞：2)

[原题传送门](https://www.luogu.com.cn/problem/UVA10125)

## $\texttt{Description}$

多组数据。

给定一个序列，你需要找到 $a,b,c,d$，使得 $d=a+b+c$，且 $d$ 最大，$a,b,c,d$ 不重复。无解时输出 `no solution`。

## $\texttt{Solution}$

本题暴力跑得还挺快。

我用的是 **动态数组** 存的数列，**从大到小** 排序。

从第 $1$ 位开始枚举 $d$，并随即枚举 $a,b,c$，一旦找到解则更新最大值，后输出最大值。

需要注意，$a,b,c,d$ 不能为同一个数，需要判断。

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define ccf(a,b,c) a!=b&&b!=c&&c!=a
using namespace std;
int n;
void real_main(){
	int *a=new int[n];
	for(int i=0;i<n;i++)
		scanf("%d",a+i);
	sort(a,a+n,greater<int>());
	int maxn=INT_MIN;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			for(int k=j+1;k<n;k++){
				bool flag=0;
				for(int l=k+1;l<n;l++)
					if(a[i]==a[j]+a[k]+a[l]&&ccf(i,j,k)&&ccf(j,k,l)&&ccf(i,k,l)){
						maxn=max(maxn,a[i]);
						flag=1;
					}
				if(flag){
					printf("%d\n",maxn);
					return;
				}
			}
	puts("no solution");
	delete[] a;
}
int main(){
	while(scanf("%d",&n)&&n)
		real_main();
	return 0;
}
```

感谢观看。

---

## 作者：zhangzhaoke (赞：2)

极其难的map，调了整整一小时

话说还有更短的吗
```cpp
#include <cstdio>
#include <map>
#include <iostream>
using namespace std;
struct ala{
	int x,y;
};
int main(){
	int n;
	while (cin>>n==1 && n){
		long long q[1010];
		map<long long,ala>table;
		for (int i=0;i<n;i++)scanf("%lld",&q[i]);
		for (int i=0;i<n;i++)
		for (int j=0;j<n && j!=i;j++) {
			int l=q[i]+q[j];
			table[l]={i,j};
		}
	long long ans=-292772293125;
	for (int i=0;i<n;i++)
	for (int j=0;j<n && j!=i;j++)
		if (table.count(q[i]-q[j]) && table[q[i]-q[j]].x!=i && table[q[i]-q[j]].x!=j && table[q[i]-q[j]].y!=i && table[q[i]-q[j]].y!=j )ans=max(ans,q[i]);
		if (ans==-292772293125) printf("no solution\n");
        	else printf("%lld\n",ans);
		}
		return 0;
}

```


---

## 作者：mrclr (赞：2)

思路和楼下一样，只是想发一下用$map$的写法。（说明$map$还是能过的！）

开一个$map$,以$a,b$两数之和为下标。为了判重，$map$的第二个参数是一个$vector$，$vector$里面又存了两个数$a, b$。

这样先$O(n ^ 2)$跑一边$a, b$之和，存到$map$里，然后从大到小枚举$d$和$c$，遍历$map$中$d - c$的$vector$，如果四个数都没有一样的，就直接返回好了。

用$map$的最大好处是代码特别短。
```c++
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<vector>
#include<stack>
#include<queue>
#include<map>
using namespace std;
#define enter puts("") 
#define space putchar(' ')
#define Mem(a, x) memset(a, x, sizeof(a))
#define rg register
typedef long long ll;
typedef double db;
const int INF = 0x3f3f3f3f;
const db eps = 1e-8;
const int maxn = 1e3 + 5;
inline ll read()
{
  ll ans = 0;
  char ch = getchar(), last = ' ';
  while(!isdigit(ch)) last = ch, ch = getchar();
  while(isdigit(ch)) ans = (ans << 1) + (ans << 3) + ch - '0', ch = getchar();
  if(last == '-') ans = -ans;
  return ans;
}
inline void write(ll x)
{
  if(x < 0) x = -x, putchar('-');
  if(x >= 10) write(x / 10);
  putchar(x % 10 + '0');
}

int n, a[maxn];

struct Node
{
  int x, y;
};
map<int, vector<Node> > mp;

int solve()
{
  for(int i = n; i; --i)
      for(int j = 1; j < i; ++j)
	{
	  int sum = a[i] - a[j];
	  for(int k = 0; k < (int)mp[sum].size(); ++k)
	    {
	      int x = mp[sum][k].x, y = mp[sum][k].y;
	      if(a[i] != x && a[i] != y && a[j] != x && a[j] != y)
		return a[i];
	    }
	}
  return 536870912;
}

int main()
{
  while(scanf("%d", &n) && n)
    {
      mp.clear(); Mem(a, 0);
      for(int i = 1; i <= n; ++i) a[i] = read();
      sort(a + 1, a + n + 1);
      for(int i = 1; i < n; ++i)
	for(int j = i + 1; j <= n; ++j)
	  mp[a[i] + a[j]].push_back((Node){a[i], a[j]});
      int ans = solve();
      if(ans == 536870912) puts("no solution");
      else write(ans), enter;
    }
  return 0;
}
```

---

## 作者：jcf666 (赞：1)

# 题意
给定一个集合 $S$，找一个最大的数 $d$ 满足 $a+b+c=d$，要求 $a$，$b$，$c$，$d$ 都是集合中的不同数。
# 个人解题思路
## 算法一
在集合中枚举 $a$，$b$，$c$，$d$，总时间复杂度 $O(tn^4)$，一定会炸。
## 算法二
在集合中枚举 $a$，$b$，$c$，$d$ 用哈希表判断是否在集合中存在，总时间复杂度 $O(tn^3)$，还是不行。
## 算法三
将 $a+b+c=d$ 转化为 $a+b=d-c$ 进行求解。

先进行排序，把集合中每对数相加，并存入哈希表 $m$，记得要把这两个数在接种对应的下标也得存入，**不能重复存入同一对**，后续判断要用。

然后，在集合中从**大到小枚举**两个数，设它们的下标分别为 $i$，$j$，则如果 $S_i-S_j$ 在哈希表中存在，且 $i$ 和 $j$ 与哈希表中与其对应的 $x$ 和 $y$ 互不相同（写题时很容易忘记这一点，且样例也没有体现出来），这个时候直接记录答案 $S_i$ 并退出循环，因为是从大到小枚举，搜到即为最大值。

最后判断一下，如果答案没有被记录，输出 `no solution
`

**记得要清空哈希!!!**

总时间复杂度约为 $O(tn^2)$，可以通过此题

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1005],n;
unordered_map<int,pair<int,int> >m;//用map代替哈希表
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	while(cin>>n){
		if(!n)break;
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+1+n);
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++)m[a[i]+a[j]]={i,j};
		}
		bool flag=1;
		for(int i=n;i>=1;i--){
			for(int j=i-1;j>=1;j--){
				int tmp=a[i]-a[j];
				if(m[tmp]!=make_pair(0,0)&&i!=m[tmp].first&&i!=m[tmp].second&&j!=m[tmp].first&&j!=m[tmp].second){
					flag=0;
					cout<<a[i]<<"\n";
					break;
				}
			}
			if(!flag)break;
		}
		if(flag)cout<<"no solution\n";
		m.clear();
	}
	return 0;
}

```
当然，如果你是奆佬，你也可以将这题作为哈希函数和链表练习题，思路和上述差不多。

当用哈希函数时，一定要注意模数的取值，取太大的模数会超时或者超内存。


```cpp
#include<bits/stdc++.h>
#define hash dciusbicuidU//防止与内部函数冲突
#define N 1005
#define mod 5015307
using namespace std;
int a[N],n,h[mod],m;
int hash(int x){
	return (x%mod+mod)%mod;
}
struct Node{
	int r,i,j,x;
}lst[N*N];
void insert(int i,int j){
	int y=hash(a[i]+a[j]);
	if(h[y]==0){
		++m;
		lst[m].x=a[i]+a[j];
		lst[m].i=i;
		lst[m].j=j;
		h[y]=m;
		lst[m].r=0;
		return;
	}
	for(int idx=h[y];idx;idx=lst[idx].r){
		if(lst[idx].x==a[i]+a[j])return;
		if(lst[idx].r==0){
			++m;
			lst[m].x=a[i]+a[j];
			lst[m].i=i;
			lst[m].j=j;
			h[y]=m;
			lst[m].r=0;
			lst[idx].r=m;
		}
	}
}
bool check(int i,int j){
	int y=hash(a[j]-a[i]);
	for(int idx=h[y];idx;idx=lst[idx].r){
		if(lst[idx].x!=a[j]-a[i]||lst[idx].i==i||lst[idx].j==j||lst[idx].i==j||lst[idx].j==i)continue;
		return 1;
	}
	return 0;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	while(cin>>n&&n){
		m=0;
		memset(h,0,sizeof h);
		int ans=-INT_MAX;
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+1+n);
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++)insert(i,j);
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(i==j)continue;
				if(check(i,j))ans=max(ans,a[j]);
			}
		}
		if(ans==-INT_MAX)cout<<"no solution\n";
		else cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：wanganze (赞：1)

### 题意
给定一个集合，求对于互不相同的整数 $a,b,c,d$，满足 $a+b+c=d$ 的最大 $d$。

### 思路

移项，将原式化为 $a+b=d-c$，将左边和右边分别处理。

用 unordered_map 枚举记录 $a + b$，再枚举 $c,d$，$O(1)$ 判断，取最大值。

### 实现

**注意判断数字不能重复。**

运用 STL 的简洁代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
int a[N];
unordered_map<int,pair<int,int>> mp;
int main()
{
	int n;
	while(scanf("%d",&n),n)
	{
		mp.clear();
		for(int i = 1; i <= n; i ++) scanf("%d",&a[i]);
		for(int i = 1; i <= n; i ++)
			for(int j = i + 1; j <= n; j ++) mp[a[i] + a[j]] = {i,j};
		int res = -2e9;
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++)
				if(i != j && mp.count(a[j] - a[i]) && mp[a[j] - a[i]].first != i && mp[a[j] - a[i]].first != j && mp[a[j] - a[i]].second != i && mp[a[j] - a[i]].second != j) res = max(res,a[j]);
		if(res == -2e9) puts("no solution");
		else printf("%d\n",res);
	}
	return 0;
}

```

---

## 作者：Kelier_pkl (赞：1)

# Sumsets 题解

## 题意

给出一个整数集合 $S$，找到集合中最大的 $d$，让等式 $a+b+c=d$ 成立。

其中，$a,b,c,d$ 是集合 $S$ 中不同的元素。

## 题目解决

题目其实很有迷惑性。

经过稍稍的变形之后，可以转换为：$a+b=d-c$。

这时数据转换之后有所变小，就方便我们求解了。

对于左式，我们可以用 Hash 表存起来；对于右式，我们直接在左式的 Hash 里面查找即可。

```cpp
void insert(LL a,LL b){
	LL x=a+b;
	LL k=(x%mod+mod)%mod;//Hash函数
	G[k].push_back({a,b,a+b});//进行存储
}
bool search(LL d,LL c){
	LL x=d-c;
	LL k=(x%mod+mod)%mod;//Hash函数
	LL size=G[k].size();
	for(LL i=0;i<size;i++){
		if(G[k][i].sum==x){
			int a=G[k][i].a,b=G[k][i].b;
			if((a!=b&&a!=c&&a!=d)&&(b!=a&&b!=c&&b!=d)&&(c!=a&&c!=b&&c!=d)&&(d!=a&&d!=b&&d!=c)){//题目要求四个数不能相等
				return true;
			}
		}
	}
	return false;
}
```

特别注意：$a,b,c,d$ 是不同的数，这里可以用结构体来存一下 $a$ 和 $b$，以便后面判断:

```cpp
struct Node{
	LL a,b,sum;
};
```

所以，这道题就解决了。

## 完整代码

```cpp
//the code is from pkl
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define MAXN 1005
struct Node{
	LL a,b,sum;
};
LL n;
LL a[MAXN];
const LL mod=131113;//Hash函数设计，mod为大质数时，能有效避免一些哈希冲突
vector<Node> G[mod+17];
void clean(){
	for(LL i=0;i<mod;i++){
		G[i].clear();
	}
}//有多组数据，注意清空
void insert(LL a,LL b){
	LL x=a+b;
	LL k=(x%mod+mod)%mod;//Hash函数
	G[k].push_back({a,b,a+b});
}
bool search(LL d,LL c){
	LL x=d-c;
	LL k=(x%mod+mod)%mod;//Hash函数
	LL size=G[k].size();
	for(LL i=0;i<size;i++){
		if(G[k][i].sum==x){
			int a=G[k][i].a,b=G[k][i].b;
			if((a!=b&&a!=c&&a!=d)&&(b!=a&&b!=c&&b!=d)&&(c!=a&&c!=b&&c!=d)&&(d!=a&&d!=b&&d!=c)){//判断
				return true;
			}
		}
	}
	return false;
}
int main(){
	while(scanf("%lld",&n),n){
		clean();
		LL ans=-2e9;
		for(LL i=1;i<=n;i++){
			scanf("%lld",&a[i]);
		}//输入
		for(LL i=1;i<=n;i++){
			for(LL j=i+1;j<=n;j++){
				insert(a[i],a[j]);
			}
		}//对所有可能的a+b进行存储
		for(LL i=1;i<=n;i++){
			for(LL j=i+1;j<=n;j++){
				if(search(a[i],a[j])){
					ans=max(ans,a[i]);
				}
				if(search(a[j],a[i])){
					ans=max(ans,a[j]);
				}
			}
		}//查找a+b=d-c
		if(ans==-2e9){
			printf("no solution\n");
		}
		else{
			printf("%lld\n",ans);
		}
	}
}
```

---

## 作者：MorsLin (赞：1)

首先将式子变形成$a+b=d-c$  
接下就可以$O(n^2)$枚举$a+b$，并用$hash$记录下来，再$O(n^2)$枚举判断是否存在合法的$d,c$使得$d-c=a+b$

如果用$map$时间复杂度会有点爆炸  
但强大的$STL$里其实还有一个容器叫$unordered\_map$  
它是用$hash$实现的$map$，可以实现$O(1)$查询  
头文件为$unordered\_map$  
不过它是$C++11$的新特性，$NOIP$应该无法使用。

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <unordered_map>
#define LL long long
using namespace std;
LL read() {
    int k = 0, f = 1; char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-') f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9')
      k = k*10+c-48, c=getchar();
    return k*f;
}
struct zzz {
    int p1, p2; bool x;
};
unordered_map <LL,zzz> q;
LL a[1010];
void solve() {
    LL n = read(), ans = -0x7fffffff; q.clear();
    if(!n) exit(0);
    for(int i = 1; i <= n; ++i) a[i] = read();
    sort(a+1, a+n+1);
    for(int i = 1; i <= n; ++i)
      for(int j = 1; j < i; ++j)
        q[a[i]+a[j]].x = 1, q[a[i]+a[j]].p1=i, q[a[i]+a[j]].p2=j;
    
    for(int i = 1; i <= n; ++i)
      for(int j = 1; j < i; ++j)
        if(q[a[i]-a[j]].x && q[a[i]-a[j]].p1 != i && q[a[i]-a[j]].p2 != j && q[a[i]-a[j]].p1 != j && q[a[i]-a[j]].p2 != i)
          ans = max(ans, a[i]);  //a,b,c,d要为不同元素

    if(ans!=-0x7fffffff) printf("%d\n",ans);
    else printf("no solution\n");
}
int main() {
    while(1) solve();
    return 0;
}
```

---

## 作者：Test_A (赞：0)

## 前言
~~UVA似乎登不上去了，但题还是可以做的。~~
## 题目大意
一个集合中需要找到 $a,b,c,d$ 使得 $a+b+c=d$。
## 思路
首先排除暴力做法，因为复杂度过大会超时。相较于其他的 map 和 hash 做法，我们可以用一种更好理解的巧妙做法来完成。

类似于搜索的方法，首先因为要求和相等，我们可以排序，从最大的数开始倒序搜索，$a$ 同样如此。因为要满足 $a+b+c=d$，简单移项后就为 $b+c=d-a$。所以可以先求出 $d$ 与 $a$ 的差值，将 $b$ 和 $c$ 进行搜索，直到 $b<c$ 为止。那么如果 $b+c>d-a$，$b$ 就应该变小。同理，相反的情况时 $c$ 就应该变大。而 $b+c=d-a$ 时就是满足的情况。
## 代码
仅有20行易理解的代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int answer,a,b,c,d,n,a1[1005];
bool find(){
	for (a = n - 1; a >= 0; a--){
		for (b = n - 1; b > 0; b--){
			if (a == b)	continue;
	        answer = a1[a] - a1[b];
			for (c = 0, d = b - 1; c < d; ){
				if (a1[c] + a1[d] == answer) return true;
				else if (a1[c] + a1[d] < answer) c++;
				else d--;}}}
	return false;}
int main(){
	while ( cin>>n && n) {
		for (int i = 0; i < n; i++) cin>>a1[i];
		sort(a1, a1 + n);
		if (find()) cout<<a1[a]<<endl;
		else cout<<"no solution"<<endl;}
	return 0;}
```





---

## 作者：Tenshi (赞：0)

吐槽：没想到交一发直接拿到了次优解 hh。

## 分析
比较套路的一道题，将原式化为 $a+b=d-c$。

然后对于左式，我们用哈希存下来（键代表 $a+b$，值代表 $a,b$ 元素对应的下标），这里推荐用 `unordered_map<int, pii>` 实现，好写而且比 `map` 快。

然后我们枚举一下 $d,c$，看看是否存在不同的下标使得对应的值满足 $a+b=d-c$ 即可。

```cpp
#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;

#define endl '\n'
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)
#define INF 0x3f3f3f3f
using pii = pair<int, int>;

inline void read(int &x) {
    int s=0;x=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

#define x first
#define y second

const int N=1e6+5;

int n;
int w[N];

unordered_map<int, pii> buf;

int main(){
	while(cin>>n, n){
		buf.clear();
		rep(i,1,n) read(w[i]);
		rep(i,1,n) rep(j,i+1,n) buf[w[i]+w[j]]={i, j};
		
		int res=-INF;
		
		rep(i,1,n) rep(j,1,n) if(i!=j){
			int v=w[j]-w[i];
			if(buf.count(v)){
				int x=buf[v].x, y=buf[v].y;
				if(x!=i && x!=j && y!=i && y!=j) res=max(res, w[j]);
			}
		}
		
		if(res==-INF) puts("no solution");
		else cout<<res<<endl;
	}
    return 0;
}
```

---

