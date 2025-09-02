# Classy Numbers

## 题目描述

Let's call some positive integer classy if its decimal representation contains no more than $ 3 $ non-zero digits. For example, numbers $ 4 $ , $ 200000 $ , $ 10203 $ are classy and numbers $ 4231 $ , $ 102306 $ , $ 7277420000 $ are not.

You are given a segment $ [L; R] $ . Count the number of classy integers $ x $ such that $ L \le x \le R $ .

Each testcase contains several segments, for each of them you are required to solve the problem separately.

## 样例 #1

### 输入

```
4
1 1000
1024 1024
65536 65536
999999 1000001
```

### 输出

```
1000
1
0
2
```

# 题解

## 作者：mydiplomacy (赞：17)

算法：裸数位dp

一般地，数位dp可以用来解决下面的问题：
给定一个结果为bool类型的函数f(x)，求$[L,R]$内有多少个数满足$f(x)$是真。其中一般$L,R<=1e7$或更大，且f(x)与数位相关。

本题中，用$dp[i][j]$代表考虑前i个数位，当前i位中有j个非零数位时，有多少个数满足条件。

这样我们就很容易处理$[1,pow(10,t)]$中的答案。

现在假设我们需要求$[1,3812]$的答案。当我们从第一位开始dfs时，从0遍历到3（最高位最大为3），如果第一位是0或1或2，则后面的数据无需考虑限制，都可以从0遍历到9。如果第一位是3，则第二位最大是8。我们使用数组上界变量代表这个限制，如果变量为0代表这一位无需考虑限制，否则代表这一位需要考虑限制。

具体注释见代码。

```
#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;//数位dp的题目一般都需要long long

ll a[20]; //代表当前处理的区间的上界的各个数位的值，也就是说取值在[0,9]之间
ll dp[20][5]; //dp数组，记忆化搜索

ll dfs(ll pos/*当前处理到第pos位*/, ll st/*当前有多少个非零位*/, bool limit/*代表数组上界变量*/) //用dfs进行记忆化搜索
{
	if(pos==-1) return 1; //如果dp完每一位，则这个数成立。我的程序最小位编号为0
	if(!limit && dp[pos][st]!=-1) return dp[pos][st]; //记忆化搜索，如果无需考虑限制，之前又算过，则直接返回答案
	ll up=limit?a[pos]:9; //代表这位的最大值是多少
	ll ans=0; //这一位的答案
	for(ll i=0;i<=up;i++)
	{
		if(i==0) ans+=dfs(pos-1,st,limit&&a[pos]==i); //如果这位是零，则st无需加1
		else if(st!=3) ans+=dfs(pos-1,st+1,limit&&a[pos]==i);
    }
    if(!limit) dp[pos][st]=ans; //记忆化搜索
    return ans;
}

ll solve(ll x) //计算[1,x]的答案
{
	ll tot=0;
    //处理出每一位
	while(x>0)
	{
		a[tot++]=x%10;
		x/=10;
    }
    return dfs(tot-1,0,true);
}

int main()
{
	memset(dp,-1,sizeof(dp));
	ll T; 
	cin>>T;
	while(T--)
	{
		ll l,r;
		cin>>l>>r;
		cout<<solve(r)-solve(l-1)<<endl;
        //程序其实有一个问题，就是把零算到了答案里面。但是solve(r)与solve(l-1)都比正确结果大了1，算出来的最终答案还是正确的。
	}
	return 0;
}
```

---

## 作者：dzysc (赞：13)

怎么各位大佬都写的是数位dp，感觉这题打表就可以无脑通过了

首先是生成法打表，然后通过STL查找R和L在其中的位置（生成法的优点）

就可以通过了。

~~然后洛谷每次我提交显示在cf上ac洛谷总是unknown error~~
```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

vector<long long>num;
void prework(int numindex,int cntindex,long long number)
{
	if(numindex==18)
	{
		num.push_back(number);
		return;
	}
	//add 0 
	prework(numindex+1,cntindex,number*10);
	//add 1-9
	if(cntindex<3)
		for(int i=1;i<=9;i++)
			prework(numindex+1,cntindex+1,number*10+i);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	prework(0,0,0);
	num.push_back(1000000000000000000);
	int T;
	cin>>T;
	for(int t=1;t<=T;t++)
	{
		long long L,R;
		cin>>L>>R;
		printf("%d\n",int(upper_bound(num.begin(),num.end(),R)-lower_bound(num.begin(),num.end(),L)));
	}
}
```

---

## 作者：wxzzzz (赞：7)

### 思路

数位 DP。

设 $f_{i,j,k}$ 表示所有位数为 $i$，最高位为 $j$，有 $k$ 个数位上的数字为 $1\sim 9$ 的数字个数。

转移：

$f_{i,j,k}=\begin{cases}\displaystyle\sum_{c=0}^9 f_{i-1,c,k}\ (j=0)\\
\displaystyle\sum_{c=0}^9 f_{i-1,c,k-1}\ (j\ne 0,k\ne 0)\end{cases}$

初始值：$f_{1,0,0}=1,f_{1,1\sim 9,1}=1$。

定义 $len(x)$ 表示 $x$ 的位数，$d(x,i)$ 表示 $x$ 的第 $i$ 为上的数字，$query(x)$ 表示 $1\sim x-1$ 中有多少个“好数”，答案为 $query(r+1)-query(l)$。

$query(x)$ 由两部分组成：

1. 位数为 $1\sim len(x)-1$ 的“好数”。
	
    总数为 $\displaystyle\sum_{i=1}^{len(x)-1}\sum_{j=1}^9\sum_{k=1}^3 f_{i,j,k}$。

1. 位数为 ${len}(x)$ 的“好数”，因为要去掉前导零，把最高位单独考虑：
	
	- 考虑第 $1\sim len(x)-1$ 位都与 $x$ 相同，且第 $len(x)$ 位不超过 $d(x,len(x))$ 的“好数”，总数为 $\displaystyle\sum_{i=1}^{d(x,len(x))-1}\sum_{j=0}^3 f_{len(x),i,j}$。
    
    - 考虑第 $1\sim i$ 位都与 $x$ 相同，且第 $i$ 位不超过 $d(x,i)$ 的“好数”，总数为 $\displaystyle\sum_{i=1}^{len(x)-1}\sum_{j=0}^{d(x,i)-1}\sum_{k=0}^{3-cnt(i)}f_{i,j,k}$，其中 $cnt(i)$ 表示 $x$ 的 $i\sim len(x)-1$ 位中有多少位为 $1\sim 9$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, d[25];
long long l, r, f[25][25][25];
long long query(long long x) {
    int len = 0;
	long long ret = 0;

    while (x)
        d[++len] = x % 10, x /= 10;

    for (int i = 1; i < len; i++)
        for (int j = 1; j <= 9; j++)
            for (int k = 0; k <= 3; k++)
                ret += f[i][j][k];

    for (int i = 1; i < d[len]; i++)
        for (int j = 0; j <= 3; j++)
            ret += f[len][i][j];

    for (int i = len - 1, cnt = 0; i >= 1; i--) {
        if (d[i])
            cnt++;

        for (int j = 0; j < d[i]; j++)
            for (int k = 0; k <= 3 - cnt; k++)
                ret += f[i][j][k];
    }

    return ret;
}
int main() {
    cin >> t;
    f[1][0][0] = 1;

    for (int i = 1; i <= 9; i++)
        f[1][i][1] = 1;

    for (int i = 2; i <= 19; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k <= 3; k++) {
                for (int c = 0; c <= 9; c++) {
                    if (!j)
                        f[i][j][k] += f[i - 1][c][k];
                    else if (k)
                        f[i][j][k] += f[i - 1][c][k - 1];
                }
            }
        }
    }

    while (t--) {
        cin >> l >> r;
        cout << query(r + 1) - query(l) << '\n';
    }

    return 0;
}
```

---

## 作者：flora715 (赞：7)

数位DP。用dp[cnt][pos]表示当前位pos(加上限制后)、出现过cnt个非0数、的个数。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<deque>
#include<cmath>
using namespace std;
typedef unsigned long long ll;

void reads(ll &x){ //读入优化（正负整数）
	int fx=1;x=0;char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')fx=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
	x*=fx; //正负号
}

/*【C.Classy Numbers】
给T组询问，每组询问有L和R两个数，要求[L,R]区间中有多少个数字满足条件。
条件：数字中最多含有3个非0数。比如1230,200,340等等，而12345则不符合条件。*/

/*【分析】数位DP。*/


ll dp[10][25],a[25]; 
//dp[cnt][pos]：当前位pos(加上限制后)、出现过cnt个非0数、的个数

ll dfs(ll pos,ll limit,ll cnt){ //dfs中进行数位DP
    if(cnt>3) return 0; //非零数已经超过了三个
    if(pos==-1) return 1; //寻找完了（注意从第0位开始）
    if(!limit&&dp[cnt][pos]!=-1) return dp[cnt][pos];
    ll tmp=0, up = limit?a[pos]:9;
    for(int i=0;i<=up;i++)
        tmp+=dfs(pos-1,limit&&(i==up),cnt+(i>0));
    dp[cnt][pos]=tmp; return tmp;
}

ll solve(ll maxx){ //上界
    memset(dp,-1,sizeof(dp));
    ll pos=0; //存每一位的上界限制
    while(maxx){ a[pos++]=maxx%10; maxx/=10; }
    return dfs(pos-1,1,0); //位数，此时顶住上界(limit为1)，出现过的非零数个数
}

int main(){
    ll T; reads(T);
    while(T--){
        ll l,r; reads(l),reads(r);
        cout<<solve(r)-solve(l-1)<<endl;
    } //↑↑↑数位DP基本性质：区间可减性
    return 0;
}
```

---

## 作者：fjy666 (赞：5)

### CF1036C Classy Numbers 题解
链接：[CF1036C Classy Numbers](https://www.luogu.com.cn/problem/CF1036C)

------------
题目大意：给你$l,r$，请你求出$[l,r]$中，**非零**数位$\le3$的数字的个数  
思路：数位DP  
数位dp一般用来统计一个区间$[l,r]$中满足一些条件的数的个数  
我们可以在`dfs`的参数中添加一个`cnt`，用`cnt`来记录**非0数位**的个数，若`cnt>3`则直接返回0。（因为已经不满足条件了）剩下直接用普通的数位dp即可。  
还是一道比较简单的数位dp的题吧  
下面放代码

------------
```cpp
#include <cstring>
#include <cstdio>
using namespace std;
long long dp[20][4];
int num[20];
int dfs(int pos,int cnt,bool _0,bool _l)
{
	if(!_0&&!_l&&dp[pos][cnt]!=-1)return dp[pos][cnt];
	if(cnt>3)return 0;
	if(pos==0)return 1;
	int limit=(_l?num[pos]:9);
	long long ans(0);
	for(int i=0;i<=limit;++i)
		ans+=dfs(pos-1,cnt+(i!=0),_0&&!i,_l&&(i==num[pos]));
	if(!_0&&!_l)
		dp[pos][cnt]=ans;
	return ans;
} 
long long solve(long long k)
{
	int len=0;
	while(k)
	{
		num[++len]=k%10;
		k/=10;
	}
	return dfs(len,0,1,1);
}
int main()
{
	memset(dp,-1,sizeof(dp));
	long long l,r;
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld%lld",&l,&r);
		printf("%lld\n",solve(r)-solve(l-1));
	}
	return 0;
}
```
注意点
1. `_0`用来表示新数的前导0的个数
2. `_l`用来表示新数目前是否等于原数


---

## 作者：ADay (赞：4)

[更好的阅读体验](https://www.cnblogs.com/aday526/p/solution-cf1063c.html)

## 数位DP

### Solution

首先将询问 $[l,r]$ 分为两个前缀和相减 $[1,r]-[1,l-1]$ 方便计算。

考虑一个数成为 Classy Number 的限制：数字 $1-9$ 的个数，记为 $tot$，然后可以带进数位DP记搜模板：

```cpp
int dfs(int pos/*位数*/,int .../*传的各种限制和变量*/,bool lim/*上限*/) 
{
    if(pos==0)return 1;//一般返回1
    if(!lim&&f[pos][...]!=-1)
    return f[pos][...];//搜过且不是上限就返回搜过的答案
    int up=lim?a[pos]:9;//确定枚举上限
    int res=0; 
    for(int i=0;i<=up;i++)
    {
        if(...)//限制条件 
        res+=dfs(pos-1,...,lim&&i==up);//如果本位已经枚举到上限就把上限往后传 
    } 
    if(!lim)f[pos][...]=res;//因为如果枚举到上限则答案并不是这一位上所有的和，所以就不更新 
    return res; 
}
```

那么函数中的限制变量只有 $tot$ ，枚举时判断它是否小于 $3$ 即可。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ll long long
#define TT template<typename T>
namespace io{static streambuf *inbuf=cin.rdbuf();static streambuf *outbuf=cout.rdbuf();char buf[1<<21],*p1=buf,*p2=buf;inline char gc(){return (p1==p2&&(p2=(p1=buf)+inbuf->sgetn(buf,1<<21),p1==p2)?EOF:*p1++);}inline void pc(const char x){static streambuf *outbuf=cout.rdbuf();outbuf->sputc(x);}
inline int read(){register int _s=0,_f=1;register char _ch=gc();for(;!isdigit(_ch);_ch=gc())if(_ch=='-')_f=-1;for(;isdigit(_ch);_ch=gc())_s=_s*10+_ch-'0';return _s*_f;}TT inline void read(T &x){x=0;register int _f=1;register char _ch=gc();for(;!isdigit(_ch);_ch=gc())if(_ch=='-')_f=-1;for(;isdigit(_ch);_ch=gc())x=x*10+_ch-'0';x*=_f;}
TT inline void write(T _x1){if(_x1<0)pc('-'),_x1=-_x1;static char _sta[20];int _p=0;do{_sta[_p++]=_x1%10^48;_x1/=10;}while(_x1);while(_p--)pc(_sta[_p]);}TT inline void writeln(const T _x){write(_x);pc(10);}TT inline void writesp(const T _x){write(_x);pc(' ');}}using namespace io;
//io优化
ll f[20][4];//f[pos][tot]
int a[20],len;//将x分解为每一位
ll dfs(int pos,int tot,bool lim){
    if(!pos)return 1;//枚举成功，加1
    if(!lim&&f[pos][tot]!=-1)return f[pos][tot];
    //只有包括全部才能直接记忆化
    int up=lim?a[pos]:9;
    ll res=0;
    for(int i=0;i<=up;i++){
        if(i&&tot==3)continue;//tot不能超过3
        res+=dfs(pos-1,i?tot+1:tot,lim&&i==up);
    }if(!lim)f[pos][tot]=res;
    return res;
}
ll solve(ll x){
    len=0;
    do{//分解x
        a[++len]=x%10;
        x/=10;
    }while(x);
    return dfs(len,0,1);
}
int main(){
    memset(f,-1,sizeof(f));
    for(int T=read();T;T--){
        ll l,r;read(l);read(r);
        writeln(solve(r)-solve(l-1));
    }
    return 0;
}
```

$trick:$ 记忆化数组 $f$ 只用赋值一次 $-1$ 因为这些状态在所有询问中都适用

---

## 作者：redegg (赞：3)

看了一下大家好像是递归搜索写法，这里提供一种非递归的直接$dp$的写法。

我们可以求出$[0,r]$的数量和$[0,l-1]$的数量，前项减去后项就是答案了。

$dp[i][j][k]$表示第做到第$i$位，已经选出$j$个不为$0$的数字，现在是$k$状态的方案数。

我们假设现在求$[0,a]$。

$k=0$代表此位选$0$,$k=1$代表此位选择$[1,9]$且保证前面这$i$个数字单独取下来后的大小小于我们上界数字$a$取出前$i$位的十进制数的大小，$k=2$代表前$i$位的十进制数和上界$a$前$i$位完全一样的方案。

那么转移分两种情况，$a[i]=0$时需要特殊转移$k=0,2$的情况。$k=1$的转移是通用的，详情见代码：

（读入是直接读入的数组，用类似快读的方式）

```cpp
#include <bits/stdc++.h>
using namespace std;

void read(int *s,int &l)
{
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')l++,s[l]=ch-'0',ch=getchar();
}

int num=0;
int maxn[22],lmax,minn[22],lmin;

long long dp[22][4][3];

long long run(int *a,int len)
{
    memset(dp,0,sizeof(dp));
    dp[1][1][2]=1;
    dp[1][1][1]=a[1]-1;
    dp[1][0][0]=1;
    for(int i=2;i<=len;i++)
    {
        if(a[i]==0){
            for(int k=0;k<=3;k++){
                dp[i][k][2]+=dp[i-1][k][2];
                dp[i][k][0]+=dp[i-1][k][1];
                dp[i][k][0]+=dp[i-1][k][0];
            }
        }
        else{
            for(int k=1;k<=3;k++)
                dp[i][k][2]+=dp[i-1][k-1][2];
            for(int k=0;k<=3;k++)
                dp[i][k][0]+=(dp[i-1][k][1]+dp[i-1][k][0]+dp[i-1][k][2]);
        }
        for(int k=1;k<=3;k++)
            dp[i][k][1]+=(dp[i-1][k-1][1]+dp[i-1][k-1][0])*9+(dp[i-1][k-1][2])*max(a[i]-1,0);
    }
    long long ans=0;
    for(int k=0;k<=3;k++)
        for(int j=0;j<=2;j++)
            ans+=dp[len][k][j];
    return ans;
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        num=0;
        lmax=lmin=0;
        read(minn,lmin);
        for(int i=1;i<=lmin;i++)
            if(minn[i]!=0)num++;
        read(maxn,lmax);
        long long ans=run(maxn,lmax)-run(minn,lmin);
        if(num<4)ans++;
        printf("%lld\n",ans);
    }
    return 0;
}

```


---

## 作者：陈晋衍 (赞：3)

挂链接：[DP学习笔记](https://www.luogu.org/blog/chenjinyan/DP-xue-xi-bi-ji)


数位DP正常题目。(裸题。因为太明显了，这道题难度下降不少)

在数位DP中，我们一般套模板（dfs记忆化做法）（三函数，一个1维数组，一个多维数组）

数位DP中心思想：从最高位开始搜，判断每一个数位，保证每一位都会被搜到。
如果搜到最后一位符合条件，就返回这个数是符合条件的。

因为他没有每个数字都搜到，所以在数量大的时候，配上记忆化，他的效率是很高的。

DP模板：
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int a[101],f[100];
int dfs(int k,int ok)
{
	if(k==0)return 1;//当搜索到最后一位时返回
	int end=ok?a[k]:9;//保证不会多搜，当它在高位时不会搜出a[k]
	int s=0;
	if(!ok&&f[k]!=0)//返回记忆化
		return f[k];
	for(int i=0;i<=end;i++)//从0搜到end
	{
		if(1)//条件 
		{
			s+=dfs(k-1,ok&&i==end);//把后面一位的数的数量累加起来。
		}
	}
	f[k]=s;//进行记忆化
	return s;
}
int chai(int n)//把一个数拆掉，拆到a数组中
{
	memset(a,0,sizeof(a));
	memset(f,0,sizeof(f));
	int i=0;
	while(n!=0)
	{
		i++;
		a[i]=n%10;
		n/=10;
	}
	return dfs(i,1);
}
int main()
{
	int n,m;
	cin>>n>>m;
	cout<<chai(m)-chai(n-1)<<endl;
	return 0;//结束
}
```

前面那个程序其实是一个b-a problem.它没有任何条件，把搜到的每一个数都返回了。

而本题有一个限制条件：

>它的十进制表示下有不超过3个数字1∼9

所以要开2维数组。（一维为第几个数字，二维为有几个数字。）

当返回时，也要做一个判断：当非0数字个数sum<=3时才返回1；

注意：本题要开long long（坑了我半 ~~秒~~  小时）,还要做适当的剪枝（简单的剪枝）。

注释在代码里

```
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
long long a[101],t[100][100],f[10];
//long long 注意
//这道题条件只有2个。1:第几个2：有几个非0数字
long long dfs(int k,bool ok,int sum)
//k：第几个数字、ok：是否到达极值点、sum：统计里面有几个数字。
//dfs函数
//用于数位DP,记忆化搜索
{
	if(sum>3)return 0;;//（简单的）剪枝，当已经有3种以上时是不行滴
	if(k==0)//结束条件
	{
		if(sum<=3)//如果搜到的这个数符合题目给出的条件
			return 1;//返回这个数是可行的。
		else
			return 0;//返回这个数是不可行的。
	}
	int end=ok?a[k]:9;//判断是否到达极值点
	long long s=0;//清零，初始化
	if(!ok&&t[k][sum]!=-1)return t[k][sum];//返回记忆化
	for(int i=0;i<=end;i++)//在每一个数位上从0搜到9，保证一个数不多，一个数不少。
	{
		int ko=0;
		if(i!=0){//当i不是0时
			ko=1;//把这个数个数加上
		}
		s+=dfs(k-1,(ok)&&(i==end),sum+ko);
        //把返回的每个数都加上，就是统计以搜到的这个数为前缀的符合条件的数的总数
        //递归，搜索下一个数位直到最后一位
	}
	if(!ok)t[k][sum]=s;//保存记忆化
	return s;//返回个数
}
long long chai(long long n)//把数拆开
{
	//if(n==0)return 0;
	memset(a,0,sizeof(a));
	memset(t,-1,sizeof(t));
	memset(f,0,sizeof(f));
    //初始化，全部清空
	int i=0;
	while(n!=0)//把数拆开，存在a数组里
	{
		i++;
		a[i]=n%10;
		n/=10;//把n分离每一个数位，直到n=0。一直把n/10
	}
	return dfs(i,1,0);
}
int main()
{
	int t;cin>>t;
	for(int i=1;i<=t;i++)//这道题是要多次输入
	{
		long long n,m;//这道题一定要开longlong！！严重警告！！
		cin>>n>>m;
		cout<<chai(m)-chai(n-1)<<endl;
	}
	return 0;
}
```

---

## 作者：_lxy_ (赞：2)

### 题意
问从 $l$ 到 $r$ 有多少个数的十进制表示有不超过 $3$ 个非零位。
### 分析
一道数位 dp 的模板题。从后向前枚举每一位，如果这一位放 $0$ ，就从前一位、非零位个数相同转移，否则从前一位，非零位个数 $+1$ 转移。
### 代码
```cpp
#include <bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a));
#define elif else if
using namespace std;
typedef long long ll;
ll T,l,r,dp[27][7];
vector<int>a;
ll dfs(int pos,int cnt,bool limit)
{
    if(pos==-1) return 1; //枚举到头了
    if(!limit&&dp[pos][cnt]!=-1) return dp[pos][cnt]; //如果之前已经得出答案了
    ll ans=0;
    int up=limit?a[pos]:9; //如果之前放满了，这一位就只能枚举到a[pos]，否则能枚举到9
    for(int i=0;i<=up;i++)
    {
        if(i==0)
        {
            ans+=dfs(pos-1,cnt,limit&&i==a[pos]); //如果这一位放0，就从前一位、非零位个数相同转移
        }
        elif(cnt<3) ans+=dfs(pos-1,cnt+1,limit&&i==a[pos]); //如果不放0，就从前一位，非零位个数+1转移
    }
    return limit?ans:dp[pos][cnt]=ans; 
}
ll solve(ll x)
{
    a.clear();
    int pos=0;
    while(x) //拆位
    {
        a.push_back(x%10);
        x/=10;
        pos++;
    }
    return dfs(a.size()-1,0,true); //从后向前枚举
}
int main()
{
    scanf("%lld",&T);
    mem(dp,-1); //赋一下初始值，方便记忆化
    while(T--)
    {
        scanf("%lld%lld",&l,&r);
        printf("%lld\n",solve(r)-solve(l-1));
    }
    return 0;
}
```


---

