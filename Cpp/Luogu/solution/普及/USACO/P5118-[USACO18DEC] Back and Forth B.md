# [USACO18DEC] Back and Forth B

## 题目描述

Farmer John 有两个挤奶棚，每个挤奶棚里各有一个奶罐和一个装有 $10$ 个各种尺寸的桶的储物柜。他喜欢将在两个挤奶棚之间来回运送牛奶作为一种锻炼方式。

周一，Farmer John 量了恰好 $1000$ 加仑的牛奶放在第一个挤奶棚的奶罐里，又量了恰好 $1000$ 加仑的牛奶放在第二个挤奶棚的奶罐里。

周二，他从第一个挤奶棚里取出一个桶，并装满牛奶，然后将牛奶运到第二个挤奶棚，并将牛奶倒进奶罐。他把这个桶留在了第二个挤奶棚。

周三，他从第二个挤奶棚里取出一个桶（可能是周二留在这里的），并装满牛奶，然后将牛奶运到第一个挤奶棚，并将牛奶倒进奶罐。他把这个桶留在了第一个挤奶棚。

周四，他从第一个挤奶棚里取出一个桶（可能是周三留在这里的），并装满牛奶，然后将牛奶运到第二个挤奶棚，并将牛奶倒进奶罐。他把这个桶留在了第二个挤奶棚。

周五，他从第二个挤奶棚里取出一个桶（可能是周二或周四留在这里的），并装满牛奶，然后将牛奶运到第一个挤奶棚，并将牛奶倒进奶罐。他把这个桶留在了第一个挤奶棚。

此时 Farmer John 测量了第一个挤奶棚的奶罐里的牛奶。他总共可能得到多少种不同的读数？


## 说明/提示

在这个例子中，最后第一个挤奶棚的奶罐中的牛奶量总共有 $5$ 种可能的结果：

$1000$：FJ 可以在每次往返的时候都携带同一个桶，从而不会改变第一个挤奶棚的奶罐的牛奶量。

$1003$：FJ 可以在周二运送 $2$ 个单位，周三 $5$ 个单位，周四 $1$ 个单位，周五 $1$ 个单位。

$1004$：FJ 可以在周二运送 $1$ 个单位，周三 $5$ 个单位，周四 $1$ 个单位，周五 $1$ 个单位。

$1007$：FJ 可以在周二运送 $1$ 个单位，周三 $5$ 个单位，周四 $2$ 个单位，周五 $5$ 个单位。

$1008$：FJ 可以在周二运送 $1$ 个单位，周三 $5$ 个单位，周四 $1$ 个单位，周五 $5$ 个单位。

## 样例 #1

### 输入

```
1 1 1 1 1 1 1 1 1 2
5 5 5 5 5 5 5 5 5 5```

### 输出

```
5```

# 题解

## 作者：Alex_Wei (赞：15)

大致思路：$\mathrm{dfs}\ +$ 模拟。

用数组存储每个桶当前所在的位置（$1$ 或 $2$），模拟每一天会发生的情况。

用一个 $\mathrm{vector}$ 存答案（最后一天第一个奶罐里的牛奶量），最后输出这个 $\mathrm{vector}$ 的大小就行了。

---

实现细节见代码

```cpp
#include<bits/stdc++.h>
using namespace std;
vector <int> ans;//最后一天第一个奶罐里的牛奶量
int pd[22],t[22];//pd数组存储位置，t数组存储容积
void dfs(int w,int m)//w是星期几，m是第一个奶罐中的牛奶量
{
	if(w/6){//如果到了星期六
		for(int x=0;x<ans.size();x++)//遍历整个ans数组
			if(m==ans[x])return;//如果重复，就返回
		ans.push_back(m);//否则将这一种情况压入答案
		return;
	}
	for(int x=1;x<=20;x++){
		if(w%2==0&&pd[x]==1){//如果星期是双数（也就是从第一个挤奶棚前往第二个挤奶棚），并且这个桶在第一个挤奶棚
			pd[x]=2;//就把这个桶装满带到第二个挤奶棚
			dfs(w+1,m-t[x]);//dfs下一天，因为带出第一个奶棚，所以是 "-"
			pd[x]=1;//记得要回到原来的状态！
		}
		if(w%2==1&&pd[x]==2){//如果星期是单数，并且这个桶在第二个挤奶棚
			pd[x]=1;//装满，带回第一个挤奶棚
			dfs(w+1,m+t[x]);//dfs下一天，带回第一个奶棚，用 "+"
			pd[x]=2;//回溯
		}
	}
}
int main()
{
	for(int x=1;x<=20;x++)cin>>t[x],pd[x]=x<11?1:2;//输入，如果是后10个就在第二个奶棚
	dfs(2,1000);//从星期二开始，第一个奶罐里有1000牛奶
	cout<<ans.size();//输出答案总数
	return 0;
}
```

$\mathrm{Upd:2019.12.11:}$ 添加 $\mathrm{Latex}$，美化文章。

---

## 作者：Polarnova (赞：9)

有个可以过但不严谨思路：  
先定义$a_1$到$a_{10}$为第一个挤奶棚里的桶，$a_{11}$到$a_{20}$为第二个挤奶棚里的桶  
然后分类讨论:  
  
1. 四天都拿不一样的桶  
2. 第一、二天拿一样的桶(奶罐里的牛奶没变化)
3. 第三、四天 或 第二、三天 拿一样的桶

暴力枚举每一种情况  
用$set$储存结果，就不怕重复了
  
```cpp
#include<cstdio>
#include<set>
std::set<int> s;
int a[25];
int main() {
    for(int i=1;i<=20;i++)scanf("%d",&a[i]);
    for(int i=1;i<=10;i++) {
        for(int j=11;j<=20;j++)
            for(int k=i+1;k<=10;k++)
                for(int l=11;l<=20;l++)if(l!=j)s.insert(-a[i]+a[j]-a[k]+a[l]);
        for(int k=i;k<=10;k++)
                for(int l=11;l<=20;l++)s.insert(-a[k]+a[l]);
        for(int j=11;j<=20;j++)s.insert(-a[i]+a[j]);
        s.insert(0);
    }
    printf("%d",s.size());
    return 0;
}
```

---

## 作者：lzqy_ (赞：6)

## DFS+模拟，给大家一个暴力的做法

### 题意：


两个挤奶棚里分别有$10$个奶桶、$1000$加仑的奶，给出各自的容积。

星期一挤奶棚一装满一个奶桶送往挤奶棚二；

星期二挤奶棚二装满一个奶桶送往挤奶棚一（可以是星期一运送过来的奶桶）

……

问星期五的时候挤奶棚一中的奶量有几种可能性。

---
这道题目里基本上都是小常数，$10$个奶桶、星期五……所以直接$DFS$。

### 如何搜索

要搜索相信大家都知道，但是如何进行DFS呢？

我们不要用$DFS$枚举奶量，因为这样$DFS$会写的很复杂且不好调试，所以我们在$DFS$的时候，只枚举序号就好了。

什么意思呢？

就是说，我们把每个桶都编一个号,然后枚举每一种编号的排列组合就好。如1—— 1—— 1—— 1——1。

### 如何模拟

在$DFS$的时候，我们为了简便，只枚举了序号，那么怎么模拟呢？一般我们都会循环五次求奶量，但是我这里是直接不用循环地模拟出每一天（很麻烦，但是很容易写）。

### 代码实现

对于这种暴力题目，我们还是结合代码一起来理解吧：
```
#include <bits/stdc++.h>
using namespace std;
int aa[10],bb[11],s[6],ans;
bool k[10000];
void moni()//模拟部分
{
  int a[10],b[11];
  for(int i=0; i<10; i++)
    a[i]=aa[i],b[i]=bb[i];//转移到另一个数组来操作
  //暴力模拟部分
  b[10]=a[s[1]];
  a[s[1]]=0;
  a[s[1]]=b[s[2]];
  b[s[2]]=0;
  b[s[2]]=a[s[3]];
  a[s[3]]=0;
  a[s[3]]=b[s[4]];
  b[s[4]]=0;
 if(!k[a[0]+a[1]+a[2]+a[3]+a[4]+a[5]+a[6]+a[7]+a[8]+a[9]])       
//判断这种奶量是否出现 
ans++,k[a[0]+a[1]+a[2]+a[3]+a[4]+a[5]+a[6]+a[7]+a[8]+a[9]]=1;
}
void dfs(int n)
{
  if(n==5)//若星期五枚举完毕
    moni();
  else
    for(int i=0; i<11; i++)
    {
      if(n%2==1&&i==10)
      //这是一个小细节
      //对于挤奶棚1来说，是不可能有第11个奶罐的
        break; 
      s[n]=i;
      dfs(n+1);//搜索
    }
}
int main()
{
  for(int i=0; i<10; i++) 
    cin>>aa[i];
  for(int i=0; i<10; i++) 
    cin>>bb[i];//读入
  dfs(1);
  cout<<ans;//输出
  return 0;
}

```

**建议**：

如果你对于$DFS$还没有到达滚瓜烂熟的地步（比如我），那么，枚举的事情尽量简单，因为$DFS$非常难调试。

### 祝大家AC愉快~


---

## 作者：Akoasm_X (赞：3)

我们把周二周三看作一次交换，周四周五看作一次交换，这样的话我们计算两次差值，在第一次交换的用swap操作即可，与dfs的感觉是差不多的，不过我把他写成了循环，**复杂度是O(1e4)，如果有不懂的可以看注释**

让我们看看代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[12],b[12];
int ans;//记方案数 
bool vis[2020];
int main()
{
	for(int i=1;i<=10;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=10;i++)
		scanf("%d",&b[i]);
	sort(a+1,a+11);//进行排序，可以减少无用的计算 
	sort(b+1,b+11);
	for(int i=1;i<=10;i++)
	{
		if(a[i] == a[i-1])
			continue;
		for(int j=1;j<=10;j++)
		{
			if(b[j] == b[j-1])
				continue;
			//枚举第一回合的交换情况，第一个奶棚得到的是 b[j] - a[i] 
			int m = 1000 + b[j] - a[i];
			swap(a[i],b[j]);//两个桶也换过来 
			for(int ii=1;ii<=10;ii++)
			{
				if(a[ii] == a[ii-1])
					continue;
				for(int jj=1;jj<=10;jj++)
				{
					if(!vis[m + b[jj] - a[ii]])
					{
						vis[m + b[jj] - a[ii]] = 1;
						ans++;
					}
				}
			}
			swap(a[i],b[j]);//记得还原最初的状态 
		}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Guess00 (赞：3)

#### ~~dalao们的方法,让本蒟蒻瑟瑟发抖~~
#### 我蒻到只能四重循环暴力枚举~~(当做DFS也可以)~~
#### 详细注释见代码.
```cpp
//代码有点丑,dalao们凑合看吧
#include <bits/stdc++.h>
using namespace std;
int i,j,k,p,ans=1000,cnt,a[15],b[15];
//ans为第一个挤奶棚的存奶量
map<int,bool> m;   //标记ans的种数
int main()
{
    for (i=1;i<11;i++)
        cin>>a[i];         //读入第一个挤奶棚的桶
    for (i=1;i<11;i++)
        cin>>b[i];         //读入第二个挤奶棚的桶
    for (i=1;i<11;i++)     //Tuesday  1-->2 
    {
        b[11]=a[i];
        ans-=a[i];
        for (j=1;j<12;j++) //Wednesday  2-->1
        {
            a[11]=b[j];
            ans+=b[j];
            for (k=1;k<12;k++)    //Thursday  1-->2 
            {
                if (k==i)           //特判,有可能拿到周二拿走的 
                    continue;
                b[12]=a[k];
                ans-=a[k];
                for (p=1;p<13;p++)  //Friday  2-->1
                {
                    if (p==j)       //特判,有可能拿到周三拿走的 
                        continue;
                    ans+=b[p];
                    if (!m[ans])
                        m[ans]=true,cnt++;
                    ans-=b[p];
                }
                ans+=a[k];
            }
            ans-=b[j];
        }
        ans+=a[i];
        /*最后4步ans的操作是dfs的返回*/
    }
    /*可能是我习惯不好,dalao们可以把我的循环改成DFS的递归*/
    cout<<cnt;
    return 0;
} 
```

---

## 作者：Ark__Skadi (赞：3)

### 为什么你们的代码都那么长？

---

本题模拟

二重循环+四重循环枚举每种情况即可。

用一个map来记录牛奶的加仑数有没有得到过

下面贴丑陋的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[11],b[11],ans;
map<int,bool> vis;
int main()
{
	//freopen("backforth.in","r",stdin);
	//freopen("backforth.out","w",stdout);
	for(int i=1;i<=10;i++) 
		cin>>a[i];
	for(int i=1;i<=10;i++)
		cin>>b[i];
	vis[1000]=true;
	for(int i=1;i<=10;i++)
		for(int j=1;j<=10;j++)
			vis[1000+b[i]-a[j]]=true;
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
			for(int k=i+1;k<=10;k++)
				for(int l=j+1;l<=10;l++)
					vis[1000+b[i]-a[j]+b[k]-a[l]]=true;
	for(int i=1000-198;i<=1000+198;i++)
		if(vis[i]==true) ans++;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：chengni (赞：2)

这道题实际上只有四次操作

既然操作数那么少，就可以直接暴力枚举所有情况了

~~虽然这样似乎很蠢~~

开一个结构体，存储每个桶当前在哪一个挤奶棚，然后直接暴力 $dfs$ 加回溯即可

然后最后计一下不同的数就行了

代码如下

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

inline ll read(){
	char ch=getchar();ll x=0,f=1;
    while(ch<'0' || ch>'9') {
       if(ch=='-') f=-1;
	  	  ch=getchar();
	}
    while(ch<='9' && ch>='0') {
	   x=x*10+ch-'0';
	   ch=getchar();
	}
    return x*f;
}

int a[2002];

struct node{
	int f[21];//记录第 i 个桶在 1 还是 2
};

int mp[202002];
int ans=0;

void dfs(int t,node x,int ma,int mb){//纯暴力 dfs，这个 mb 似乎没啥用
	//正常的暴力套路，封顶回溯
    if(t==6){
		if(mp[ma]==0){
			mp[ma]=1;
			ans++;
		}
		return;
	}
	if(t==2 || t==4){
		for(int i=1;i<=20;i++){
			if(x.f[i]==1){
				ma-=a[i];
				mb+=a[i];
				x.f[i]=2;
				dfs(t+1,x,ma,mb);
				x.f[i]=1;
				ma+=a[i];
				mb-=a[i];
			}
		}
	}
	if(t==3 || t==5){
		for(int i=1;i<=20;i++){
			if(x.f[i]==2){
				mb-=a[i];
				ma+=a[i];
				x.f[i]=1;
				dfs(t+1,x,ma,mb);
				x.f[i]=2;
				mb+=a[i];
				ma-=a[i];
			}
		}
	}
}

int main(){
	node x;
	for(int i=1;i<=10;i++){
		a[i]=read();
		x.f[i]=1;
	}
	for(int i=11;i<=20;i++){
		a[i]=read();
		x.f[i]=2;
	}
	dfs(2,x,1000,1000);//dfs走起
	cout<<ans;
	return 0;
}


```

---

## 作者：__Hacheylight__ (赞：1)

T3 Back and Forth

【题意】

有两个10个元素的数组A和B，你可以进行四次操作，每次操作你可以讲A或B中的一个一个元素移到另一个数组中（可以移动原来移动过的），问最终A的元素和有几种可能性。

【分析】

dfs肯定没脑子而且时间复杂度过得去，但是好像移动元素比较费劲，我们考虑直接枚举移动元素。

首先要分一下讨论。

1. 两个回合B都把上次A移过来的移会去，答案肯定为0
2. 有一个回合B都把上次A移过来的移会去，枚举剩下一回合A和B移啥
3. 没有一个回合B都把上次A移过来的移会去，枚举两个回合。

注意两个细节。一个是答案可能有重复，要记录去重；二是答案可能会有负数，要加上一个相对大的数。

然后就做完了。

【代码】

```cpp
#include <bits/stdc++.h>
using namespace std ;

#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define Rep(i, a, b) for (int (i) = (a) - 1; (i) < (b); (i)++)
#define REP(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define Sort(a, len, cmp) sort(a + 1, a + len + 1, cmp)
#define ass(a, sum) memset(a, sum, sizeof(a))

#define ls ((rt) << 1)
#define rs ((rt) << 1 | 1)
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define ENDL cout << endl
#define SZ(x) ((int)x.size())

typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef pair <int, int> pii ;
typedef pair <ll, ll> pll ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
typedef map <ll, ll> mll ;
typedef multiset <int> si ;

const int N = 100010 ;
const double eps = 1e-8 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const double dinf = 1e30 ;
const int MOD = 1000000007 ;

inline int read(){
    int X = 0, w = 0 ;
    char ch = 0 ;
    while (!isdigit(ch)) { w |= ch == '-' ; ch = getchar() ; }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar() ;
    return w ? - X : X ;
}

void write(int x){
     if (x < 0) putchar('-'), x = - x ;
     if (x > 9) write(x / 10) ;
     putchar(x % 10 + '0') ;
}

void print(int x) {
    cout << x << endl ;
    exit(0) ;
}

void PRINT(string x) {
    cout << x << endl ;
    exit(0) ;
}

void douout(double x){
     printf("%lf\n", x + 0.0000000001) ;
}

int vis[N << 1], a[20], b[20] ;
int n, ans ;

int main() {
	n = 10 ;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]) ;
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]) ;
	ans = 1 ; vis[0 + N] = 1 ;
	for (int i = 1; i <= n; i++)  // 有一回合拿过来又送回去的 
	for (int j = 1; j <= n; j++)
	if (!vis[b[j] - a[i] + N]) vis[b[j] -a[i] + N] = 1, ans++ ;
	for (int i = 1; i <= n; i++)
	for (int j = 1; j <= n; j++)
	for (int ii = 1; ii <= n; ii++)
	for (int  jj = 1; jj <= n; jj++) 
	if (ii != i && jj != j) 
	if (!vis[b[j] - a[i] + b[jj] - a[ii] + N]) vis[b[j] - a[i] + b[jj] - a[ii] + N] = 1, ans++ ;
	printf("%d\n", ans) ;
}
```

---

## 作者：封禁用户 (赞：1)

本来想写在`vector`里`dfs`呢。。。

结果不是很会写`vector`的在某个位置删除，插入之类的操作。。。

反正只有$5$个桶，不递归也不难写。（可能还好写

原理是一样的。
```cpp
/*
ID: Anfangen
LANG: C++
PROG: backforth
*/
#include <cstdio>
#include <iostream>
#include <stack>
#include <utility>
#include <algorithm>
#include <set>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#define rep(i,a,b) for(int i=(a);i<=(b);++i) 
#define dec(i,a,b) for(int i=(a);i>=(b);--i)
#define gc() getchar()
#define endll putchar('\n')
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef long double ld;
inline ll read(){
	char ch=gc();
	ll x=0,f=1;
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=gc();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=gc();
	}
	return x*f;
}
inline void print(ll k){
	if(k<0) k=-k,putchar('-');
	if(k>9) print(k/10);
	putchar(k%10+48);
}
inline void println(ll k){
	print(k);
	endll;
}
inline void printsp(ll k){
	print(k);
	putchar(' ');
}
set<int> se;
int b1=1000,b2=1000;
int a[113],b[113];
vector<int> vec2;
int main(){
	rep(i,1,10) a[i]=read();
	rep(i,1,10) b[i]=read();
	rep(i,1,10){
		int t1=a[i];
		b1-=t1;
		a[i]=0;
		b[11]=t1;
		b2+=t1;
		rep(j,1,11){
			int t2=b[j];
			b2-=t2;
			b[j]=0;
			a[11]=t2;
			b1+=t2;
			rep(k,1,11){
				int t3=a[k];
				if(t3==0) continue;
				b1-=t3;
				a[k]=0;
				b[12]=t3;
				b2+=t3;
				rep(l,1,12){
					int t4=b[l];
					if(t4==0) continue;
					se.insert(b1+t4);
				}
				b2-=t3;
				b[12]=0;
				b1+=t3;
				a[k]=t3;
			}
			b1-=t2;
			b2+=t2;
			a[11]=0;
			b[j]=t2;
		}
		b1+=t1;
		b2-=t1;
		b[11]=0;
		a[i]=t1;
	}
	println(se.size());
	return 0;
}
```

---

## 作者：Luck_Fool (赞：1)

# P5118 [USACO18DEC]Back and Forth B题解  

## Step 1
简化题意：有两个集合，你可以进行四次操作。

* 第一次操作，把集合 $\{ G_1 \}$ (表示第一个奶棚)中的一个元素移到集合 $\{ G_2 \}$ 中  
第二次操作，把集合 $\{ G_2 \}$中的一个元素移到集合 $\{ G_1 \}$ 中  
第三次操作，把集合 $\{ G_1 \}$中的一个元素移到集合 $\{ G_2 \}$ 中  
第四次操作，把集合 $\{ G_2 \}$中的一个元素移到集合 $\{ G_1 \}$ 中  

问你最后 $\{ G_1 \}$ 中所有元素的总和可能的情况有几种。  

## Step 2  
因为一共只进行四次操作，且每个集合中最大被使用的元素只有两个，所以我们就可以枚举所有可能的情况。  
设 $\{ G_1 \}$ 中被操作的元素为 $a,b$，$\{ G_2 \}$ 中被操作的元素为 $A,B$，那么，一共有以下几种情况：   



| $-a$ | $+a$ |$-a$  | $+a$ |
| :----------: | :----------: | :----------: | :----------: |
| $-a$ |$+a$  | $-a$ | $+A$ |
| $-a$ | $+a$ | $-a$ | $+B$ |
| $-a$ | $+a$ | $-b$ | $+A$ |
| $-a$ | $+a$ | $-b$ | $+B$ |
| $-a$ | $+a$ | $-b$ | $+b$ |
| $-a$ | $+A$ | $-A$ | $+a$ |
| $-a$ | $+A$ | $-A$ | $+A$ |
| $-a$ | $+A$ | $-a$ | $+a$ |
| $-a$ | $+A$ | $-b$ | $+b$ |
| $-a$ | $+A$ | $-b$ | $+B$ |
  
化简就变成了：    


| $0$ |  
| :----------: |
| $-a \quad +A$  |
| $-a \quad +B$ |
| $-b \quad +A$ |
| $-b \quad +B$ |
| $-a \quad +A \quad -b \quad +B$ |

## Step 3
确立思路后，考虑代码实现，因为这题的 $n$ 非常小，挨个枚举即可，理论复杂度是优于目前所有做法，答案开桶记录。  
#### code:
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int all=1000;
int t1[11],t2[11],visit[5000],v[10000],tot;
int tot1,ans;

struct node{
	int x,y;
}qk[100000],qk1[100000];//记录所有可能的情况

void work(int a,int b,int A,int B) {
	visit[all-a+A]=true;
	visit[all-a+B]=true;
	visit[all-b+A]=true;
	visit[all-b+B]=true;
	visit[all-a+A-b+B]=true;
}

int main() {
	for(int i=1;i<=10;i++)
		scanf("%d",&t1[i]);
	for(int i=1;i<=10;i++)
		scanf("%d",&t2[i]);
	for(register int i=1;i<=10;i++)//记录情况
		for(register int j=i;j<=10;j++)
			if(i!=j)
				qk[++tot].x=t1[i],qk[tot].y=t1[j];
	for(register int i=1;i<=10;i++)
		for(int j=i;j<=10;j++)
			if(i!=j)
				qk1[++tot1].x=t2[i],qk1[tot1].y=t2[j];
	for(register int i=1;i<=tot;i++)//记录答案
		for(register int j=1;j<=tot1;j++)
			work(qk[i].x,qk[i].y,qk1[j].x,qk1[j].y);
	visit[1000]=true;
	for(int i=0;i<=2000;i++)
		if(visit[i])
			ans++;
	printf("%d",ans);
}
```  
如果可以的话，复杂度还可以进一步降低到 $O(n^2)$

---

## 作者：swl3992 (赞：0)

# DFS纯暴力搜索

# 暴力DFS模拟每一次倒牛奶，用vector储存桶的大小

$\color{yellow}\texttt{直接上代码}$

```cpp
#include <bits/stdc++.h>	//万能头文件
using namespace std;
vector<int> a,b; 	//初始桶的大小
bool vis[2000];	//判断这个答案有没有过，也可以用一个set
int ans;	//答案
void dfs(vector<int> a,vector<int> b,int when,int A,int B)	//爆搜函数,a代表第一个牛奶棚里的桶的容量，b同理，when代表星期几，A代表第一个牛奶棚里的奶罐的牛奶????，B同理
{
	if(when==6)	//递归边界
	{
		if(!vis[A])	//如果没有过这个答案
		{
			ans++;	//答案加1
			vis[A]=true;	//设为true
		}
		return;	//返回
	}
	if(when%2==0)	//A->B
	{
		for(int i=0;i<a.size();i++)	//暴力枚举
		{
			A-=a[i];
			B+=a[i];	//倒牛奶
			vector<int> temp1(a),temp2(b);	//移动桶
			temp1.erase(temp1.begin()+i);	//移除
			temp2.push_back(a[i]);	//添加
			dfs(temp1,temp2,when+1,A,B);	//递归搜索
			A+=a[i];	//记住！要倒回去
			B-=a[i];
		}
	}
	else
	{
		for(int i=0;i<b.size();i++)	//这个和上面的同理
		{
			A+=b[i];
			B-=b[i];
			vector<int> temp1(a),temp2(b);
			temp2.erase(temp2.begin()+i);
			temp1.push_back(b[i]);
			dfs(temp1,temp2,when+1,A,B);
			A-=b[i];
			B+=b[i];
		}
	}
}
int main ()
{
	ios::sync_with_stdio(0);	//cin,cout加速
	a.resize(10);
	b.resize(10);	//重新设定大小
	for(int i=0;i<10;i++)	//读入
	{
		cin>>a[i];
	}
	for(int i=0;i<10;i++)
	{
		cin>>b[i];
	}
	dfs(a,b,2,1000,1000);	//开始爆搜
	cout<<ans<<endl;	//输出
	return 0;
}

```

# The End


---

## 作者：_aeolian (赞：0)

```cpp
#include<bits/stdc++.h>
using namespace std;
set<int>an;
int a[21];
int main(){
	for(int i=1;i<=20;i++)std::cin>>a[i];
	for(int i=1;i<=10;i++){
		for(int j=11;j<=20;j++)
			for(int k=1;k<=10;k++)
				for(int y=11;y<=20;y++)
				if(y!=j&&k!=i)an.insert(-a[i]+a[j]-a[k]+a[y]);
//		for(int j=11;j<=20;j++)
//				for(int k=1;k<=10;k++)
//				if(k!=i)an.insert(-a[k]+a[j]);
				for(int j=11;j<=20;j++)
				an.insert(-a[i]+a[j]);
				an.insert(0); 
		}
		
		cout<<an.size();
		return 0;
}

```
论楼下巨佬的分类讨论其实可以变成:  
1.四天相同   
2.两天相同  
代码思路与楼下巨佬一样

---

## 作者：damage (赞：0)

### 题解

```USACO 2018.12月赛 铜组 第三题```

### 本题深搜即可！

我们用两个向量（可变化大小的数组```vector```）分别表示两个挤奶棚里桶的容积。

我们用```dfs(int chg,vector pill[2],bool to,int deep)```来表示深搜的四个状态：

- ```chg```表示第一个挤奶棚里牛奶数量的变化量

- ```vector pill[2]```表示两个挤奶棚里桶的容量

- ```bool```型变量```to```为```true```时表示从第一个挤奶棚运牛奶到第二个，反之亦然

- ```deep```表示第几次运牛奶，用来作为深搜的结束标志

开始时```dfs(0,sized,true,0)```开始深搜，其中```sized```就是初始时输入的两个挤奶棚里牛奶的数量，表示一开始第一个牛奶棚的变化量为$0$，将牛奶第一次运进第二个挤奶棚。

过程就很简单了：

1. 若```deep```$\geq{4}$，即运完了所有的四次牛奶，此时我（蒟蒻）用的是一个```map<int,bool>```映射来记录并去除重复结果

2. 根据```to```来遍历相应的挤奶棚里桶的容积（连去重剪枝都可以没有），然后模拟（即从原牛奶棚里去掉，再在目标牛奶棚里添加，改变第一个挤奶棚里牛奶的改变量```chg```，然后改变运送方向以及次数```deep```加$1$，记得还原状态）即可

最后输出即输出记录答案的```map```映射（假设叫```used```）的大小即可，即```used.size()```。

---

### 代码

```cpp
#include<stdio.h>
#include<map>
#include<vector>
using namespace std;
int x,res;
vector<int> sized[2];
map<int,bool> used;
void dfs(int chg,vector<int> pill[2],bool to,int deep)
{
    if(deep>=4) //达到4次就结束
    {
        used[chg]=true; //记录状态
        return ;
    }
    if(to) //运到第二个挤奶棚
    {
        int s=pill[0].size(); //将所有桶遍历一遍
        while(s--)
        {
            int temp=pill[0][0];
            pill[0].erase(pill[0].begin()); //模拟运输
            pill[1].push_back(temp);
            dfs(chg-temp,sized,false,deep+1); 
            pill[0].push_back(temp); //记得还原状态
            pill[1].erase(pill[1].end()-1);
        }
    }
    else //运到第一个挤奶棚
    {
        int s=pill[1].size(); //这里和上面一样（其实可以合并起来用!to代替）
        while(s--)
        {
            int temp=pill[1][0];
            pill[1].erase(pill[1].begin());
            pill[0].push_back(temp);
            dfs(chg+temp,sized,true,deep+1);
            pill[1].push_back(temp);
            pill[0].erase(pill[0].end()-1);
        }
    }
    return ;
}
int main()
{
    for(register int j=0;j<10;++j) //按输入放桶
    {
        scanf("%d",&x);
        sized[0].push_back(x);
    }
    for(register int j=0;j<10;++j) //同上
    {
        scanf("%d",&x);
        sized[1].push_back(x);
    }
    dfs(0,sized,true,0); //开始搜索
    printf("%d\n",used.size()); //输出结果
    return 0;
}
```

---

