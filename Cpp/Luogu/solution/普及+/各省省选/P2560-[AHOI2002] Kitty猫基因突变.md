# [AHOI2002] Kitty猫基因突变

## 题目描述

 ![](https://cdn.luogu.com.cn/upload/pic/1682.png) 

![](https://cdn.luogu.com.cn/upload/pic/1683.png)


## 样例 #1

### 输入

```
3 2
11000101
10 10 5 6 3 2 1 2```

### 输出

```
9```

# 题解

## 作者：The_Stalker (赞：3)

奋斗两小时A了人生第一道紫题，写篇题解纪念一下。

--------

先讲一下T(s)的处理

因为题目给出了二叉树的深度k+1，所以可以直接用二叉树处理。

为什么在可以递归解决的情况下要用二叉树呢？因为这在解决本题时有极大的好处(下文解释

输入的字符串先进行预处理，0->"A",1->"B"，然后把这个字符串逐个输入到树的第k+1层，然后逐层向上递推。因为是二叉树所以当前结点i的两个儿子为 2i 和 2i+1,当两个儿子相同时即为儿子，不同时即为"C"+左儿子+右儿子。具体请见本题的[前置题](https://www.luogu.org/problemnew/show/P2562)。

附代码

```cpp
#include<bits/stdc++.h>

using namespace std;

string s;
string ss[1000];
int k;

int main()
{
	cin>>k;
	cin>>s;
	int n=1;
	for(int i=1;i<=k;i++)
		n*=2;
	for(int i=n;i<=n*2-1;i++){
		if(s[i-n]=='0')ss[i]="A";
		else ss[i]="B";
	}//预处理(建树
	for(int i=n-1;i>=1;i--){
		if(ss[i*2]==ss[i*2+1]&&ss[i*2]=="A")
			ss[i]="A";
		else if(ss[i*2]==ss[i*2+1]&&ss[i*2]=="B")
			ss[i]="B";
		else
			ss[i]="C"+ss[i*2]+ss[i*2+1];
	}//递推
	cout<<ss[1];//树根为答案
	return 0;
}
```

以上为前置知识

--------------------

下面是这道题的题解

这题变量极多，单纯数组比较麻烦，因此建议使用结构体解决。

定义二维数组结构体f[i][j]来存储数据，创建四个成员变量s,c,t,a对应于题干中的s,c,t,a。其中i为结点编号，j为当前进行的突变次数。在开始时初始化t,a,c为无限。

定义状态之后是状态转移。

因为2^7只有256因此我们可以大胆挥霍时间。

对于当前状态f[i][j]进行枚举,枚举它的两个儿子f[2i][l]和f[2i+1][j-l] (l<=j) 的每个状态，然后使用一个临时结点tmp记录数据，数据从两个儿子继承(s按照上文方法进行计算。c=c1+c2,t=s.length(),a=t+c)。

继承时需要注意，**并不是每个状态都可用！**再说一遍，**并不是每个状态都可用！**这点非常重要。因为j表示**突变**的次数，而本来就是B的是**不能突变**的，因此在计算突变次数时不能使用，需要特殊处理。

因此在预处理时将最后一层为A的f[i][0]对应的f[i][1]的c改为给出的c,a改为c+1(只有一个字符)。将最后一层为B的f[i][1]不作处理，然后在后面递推时进行特判。

继承之后需要判断优劣以及状态转移。本人使用的是函数进行判定，以a为第一关键字，t为第二关键字进行判断优劣(当然各位大佬可以选择重载小于号。

当临时结点tmp比当前结点f[i][j]更优时更新数据。

一直从树叶更新到树根时树根的a值即为答案。

附代码

```cpp
#include<bits/stdc++.h>

using namespace std;

struct node
{
	string s;
	int t;
	int c;
	int a;
}f[260][31];//定义状态

int k;
int w;
string s;
int c[260];//记录题目给出的c值，与结构体中的c不同

bool cmp(node a,node b)
{
	if(a.a!=b.a)
		return a.a<b.a;
	else
		return a.t<b.t;
}//比较函数

int main()
{
	cin>>k>>w;
	int n=1;
	for(int i=1;i<=k;i++)
		n*=2;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=w;j++)
			f[i][j].a=f[i][j].c=f[i][j].t=9999999;//初始化
	cin>>s;
	for(int i=n;i<=n*2-1;i++){
		if(s[i-n]=='0') f[i][0].s="A";
		else f[i][0].s="B";
	}//预处理
	for(int i=1;i<=n;i++)
		cin>>c[i];
	for(int i=n;i<=n*2-1;i++){
		if(f[i][0].s=="A"){
			f[i][1].c=c[i-n+1];
			f[i][1].s="B";
			f[i][1].t=1;
			f[i][1].a=1+f[i][1].c;
		}
		f[i][0].t=1;
		f[i][0].a=f[i][0].c+f[i][0].t;
	}//预处理
	int cnt=1;
	while(n>=1)
	{
		n/=2;
		cnt*=2;
		for(int i=n;i<=n*2-1;i++){//这里这个循环有点麻烦，本意是逐层进行，结果发现直接n->1就可以了(=ω=；)
			if(f[i*2][0].s==f[i*2+1][0].s&&f[i*2][0].s=="A")
				f[i][0].s="A";
			else if(f[i*2][0].s==f[i*2+1][0].s&&f[i*2][0].s=="B")
				f[i][0].s="B";
			else f[i][0].s="C"+f[i*2][0].s+f[i*2+1][0].s;
			f[i][0].t=f[i][0].s.length();
			f[i][0].c=0;
			f[i][0].a=f[i][0].t;//自己的程序在运行时莫名其妙经常忽略f[i][0],因此专门进行处理(欢迎大佬指出问题原因
			for(int j=1;j<=min(w,cnt);j++){
				for(int l=j;l>=0;l--){//枚举突变次数总和为j的每个儿子节点状态
					node temp;//新建临时结点
					if(f[i*2][l].s.length()==0||f[i*2+1][j-l].s.length()==0)
						continue;
                    //特判儿子中有一个不能突变时的情况，直接跳过
					if(f[i*2][l].s==f[i*2+1][j-l].s&&f[i*2][l].s=="A")
						temp.s="A";
					else if(f[i*2][l].s==f[i*2+1][j-l].s&&f[i*2][l].s=="B")
						temp.s="B";
					else temp.s="C"+f[i*2][l].s+f[i*2+1][j-l].s;
                    /*
                    此处说明上文中说用二叉树解决T(s)问题的好处
                    1.这是一道树形DP，可以直接借用二叉树的结构，直接使用上文方法求出s，进而得出t值。
                    2.如果使用递归等方法第一费时间，第二麻烦(我恰好相当懒)因此使用二叉树解决s的问题
                    */
                    temp.t=temp.s.length();//T(s)
					temp.c=f[i*2][l].c+f[i*2+1][j-l].c;//c值直接继承
					temp.a=temp.c+temp.t;//计算a值
					if(cmp(temp,f[i][j])) f[i][j]=temp;//状态转移
				}
			}
		}
	}
	cout<<f[1][w].a;//得出答案
	return 0;//好习惯
}
```

OI新人，写的不好望大佬们见谅。

欢迎大佬指正问题！

---

## 作者：WA鸭鸭 (赞：2)

以下设 $n=2^k$

首先分析 $T$ 函数性质，我们可以将 $T$ 函数抽象为在线段树上求解，每次如果整个区间全 $0$ 或全 $1$ 则 `cnt++` 并返回（其实就是按照题意模拟）。那么 `cnt` 的值就是  $T$ 序列内 $A$ 与 $B$ 的个数和。
  
$C$ 的个数为 $cnt-1$ ，这一点很好证明。所以 $T$ 的价值就可以通过 $cnt$ 直接确定，我们的目标就是让 $A(s,s')=2\times cnt-1+C(s,s')$ 最小。（ $C(s,s')$ 为修改代价）由于式子里的 `-1` 很麻烦，所以我们先求出 $A(s,s')+1$，输出时再将答案 `-1` 。

按照套路，设 $f_{i,j}$ 表示前 $i$ 个基因单元，修改了 $j$ 个 的 $A(s,s')$ 最小值。

记 `sum1[]` 为 前 $i$ 个基因单位全部修改为 $1$ 的代价和， `sum2[]` 为 前 $i$ 个基因单位里 $0$ 的个数。

选择一段区间，全部修改为 $1$ ：

$$f_{i,j}=\min_{\text{p转移到i合法}}f_{p,j-(sum2[i]-sum2[p])}+(sum1[i]-sum1[p])+2$$

选择一段区间，全部修改为 $0$ ：

$$f_{i,j}=\min_{\text{p转移到i合法且区间[p+1,i]内全为0}}f_{p,j}+2$$

最后的问题是如何求出 $p$ 转移到 $i$ 是否合法。

我们可以发现只有线段树上的区间转移是合法的，我们仿照建树过程，将所有合法转移求出。

```cpp

void build(int l,int r)
{
	t[l-1].push_back(r);//t[x]表示x可以往后转移的点
	if(l==r)return;
	int mid=(l+r)>>1;
	build(l,mid);
	build(mid+1,r);
}

```

复杂度 $O(nw)$ ，可以轻松通过。


全部代码（请注意这里的 `sum2[]` 是 `1` 的个数，转移使用的是从前往后推，非上述）：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
int n,w;
int c[100001],sum1[100001],sum2[100001];
vector<int>t[100001];
int f[1001][31];
void build(int l,int r)
{
	t[l-1].push_back(r);
	if(l==r)return;
	int mid=(l+r)>>1;
	build(l,mid);
	build(mid+1,r);
}
int main()
{
	memset(f,0x3f,sizeof(f));
	cin>>n>>w;
	n=(1<<n);
	for(int i=1;i<=n;i++)
	{
		scanf("%1d",&c[i]);
	}
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		sum1[i]=sum1[i-1]+(!c[i])*x;
		sum2[i]=sum2[i-1]+c[i];
	} 
	build(1,n);
	f[0][0]=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<=w;j++)
		{
			for(int k=0;k<t[i].size();k++)
			{
				int r=t[i][k];
				if(sum2[r]==sum2[i])f[r][j]=min(f[r][j],f[i][j]+2);
				int s=r-i-(sum2[r]-sum2[i]);
				if(j+s<=w)f[r][j+s]=min(f[r][j+s],f[i][j]+(sum1[r]-sum1[i])+2);
			}
		}
	}
	cout<<f[n][w]-1;
	return 0;
} 
```

---

## 作者：summ1t (赞：0)

[原题链接](https://www.luogu.com.cn/problem/P2560)

蛮冷门的一道题，虽然题面很长，但只要认真读完，你就会发现这个题的做法直接都明摆着给你了。

观察数据范围，很容易想到转为二叉树上 dp，设 $f_{x,j,0/1/2}$ 表示在二叉树上 $x$ 号节点代表的区间，有 $j$ 个 $0$ 进行突变，最终得到类型为 $0$（全为 $0$ 区间），$1$（全为 $1$ 区间），$2$（$0/1$ 混合区间）的最小价值。

dfs 一遍子树，然后合并 $x$ 的左右儿子即可。初始化和转移极其简单，如果还不会就见代码。

时间复杂度 $O(nw^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rd read()
#define mid ((l+r)>>1)
#define FOR(i,j,k) for(int i=j;i<=k;i++)
#define ROF(i,j,k) for(int i=j;i>=k;i--)
int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*f;
}
const int N=200,INF=1e6;
int n,w,c[N],f[N*4][N][3],a[N];
void dfs(int x,int l,int r){
	if(l==r){
		if(a[l]==0) f[x][0][0]=1,f[x][1][1]=c[l]+1,f[x][0][2]=1,f[x][1][2]=c[l]+1;
		else f[x][0][1]=1,f[x][0][2]=1;
		return;
	}
	dfs(x<<1,l,mid),dfs(x<<1|1,mid+1,r);
	FOR(i,0,w){
		FOR(j,0,i){
			f[x][i][0]=min(f[x][i][0],f[x<<1][j][0]+f[x<<1|1][i-j][0]-1);
			f[x][i][1]=min(f[x][i][1],f[x<<1][j][1]+f[x<<1|1][i-j][1]-1);
			f[x][i][2]=min(f[x][i][2],f[x<<1][j][2]+f[x<<1|1][i-j][2]+1);
		}
		f[x][i][2]=min(f[x][i][2],min(f[x][i][0],f[x][i][1]));
	}
}
int main(){
	n=rd,w=rd;n=(1<<n);FOR(i,0,n*4) FOR(j,0,w) FOR(k,0,2) f[i][j][k]=INF;
	FOR(i,1,n) scanf("%1d",&a[i]);
	FOR(i,1,n) c[i]=rd;
	dfs(1,1,n);
	printf("%d\n",min(f[1][w][0],min(f[1][w][1],f[1][w][2])));
	return 0;
}
```

---

## 作者：_Revenge_ (赞：0)

我们不妨将所有权值打到一棵树上，这很容易想到。

考虑暴力，如果我们选择了 $w$ 个点，修改后我们会从叶子节点依次合并去计算贡献。

很显然我们可以动态规划维护。

$ f_{p,}{_{w,}}_{0/1/2} $ 表示选了 $w$ 个点，后整个区间的状态。

- `0` 和 `1` 表示整个区间全为这个数。
- `2` 表示混合区间，但也包含前两个状态。

特殊的，进行合并时，注意左右区间可以合并时，减去合并贡献。

注意每个节点都有贡献。

至此，此题得解。

具体复杂度 $ \mathcal{O}(2^k w^2) $ 。

这道题少有人做，但是希望对您有用，谢谢。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N = 500;
const int M = 80;
const int Mod = 1e9 + 7;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

int n, w;

char s[N];

int c[N];

int f[N][M][3];

// 0 1 01

int ls(int p) { return p << 1; }
int rs(int p) { return p << 1 | 1; }

void dfs(int p, int l, int r)
{
    if (l == r)
    {
        if (s[l] == '1')
        {
            f[p][0][1] = 1;
            f[p][0][2] = 1;
        }
        else
        {
            f[p][0][0] = 1;
            f[p][1][1] = c[l] + 1;
            f[p][0][2] = 1;
            f[p][1][2] = c[l] + 1;
        }
        return;
    }
    int mid = l + r >> 1;
    dfs(ls(p), l, mid);
    dfs(rs(p), mid + 1, r);
    for (int i = 0; i <= w; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            for (int u = 0; u <= 2; ++u)
            {
                for (int v = 0; v <= 2; ++v)
                {
                    f[p][i][2] = min(f[p][i][2], f[ls(p)][j][u] + f[rs(p)][i - j][v] + 1);
                }
            }
            f[p][i][0] = min(f[p][i][0], f[ls(p)][j][0] + f[rs(p)][i - j][0] - 2 + 1);
            f[p][i][1] = min(f[p][i][1], f[ls(p)][j][1] + f[rs(p)][i - j][1] - 2 + 1);
            f[p][i][2] = min(f[p][i][2], min(f[p][i][0], f[p][i][1]));
        }
    }
}

int main()
{
    memset(f, Mod, sizeof(f));
    n = read(), w = read();
    scanf("%s", s + 1);
    n = 1 << n;
    for (int i = 1; i <= n; ++i)
    {
        c[i] = read();
        if (s[i] == '1')
            c[i] = 0;
    }
    dfs(1, 1, n);
    printf("%d\n", min(min(f[1][w][0], f[1][w][1]), f[1][w][2]));
    return 0;
}
```

---

