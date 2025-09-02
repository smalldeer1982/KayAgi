# [USACO17OPEN] COWBASIC P

## 题目描述

Bessie 发明了一种新的编程语言，但由于还没有编译器，她需要你的帮助来实际运行她的程序。

COWBASIC 是一种简单而优雅的语言。它有两个关键特性：加法和 MOO 循环。Bessie 设计了一个巧妙的解决方案来处理溢出：所有的加法都是在模 $10^9+7$ 下进行的。但 Bessie 的真正成就是 MOO 循环，它可以固定次数地运行一段代码。当然，MOO 循环和加法可以嵌套。

给定一个 COWBASIC 程序，请帮助 Bessie 确定它返回的数字。

## 说明/提示

评分

在 20% 的测试用例中，MOO 循环不会嵌套。

在另外 20% 的测试用例中，程序只有一个变量。MOO 循环可以嵌套。

在剩余的测试用例中，没有进一步的限制。

## 样例 #1

### 输入

```
x = 1
10 MOO {
x = ( x ) + ( x )
}
RETURN x```

### 输出

```
1024```

## 样例 #2

### 输入

```
n = 1
nsq = 1
100000 MOO {
100000 MOO {
nsq = ( nsq ) + ( ( n ) + ( ( n ) + ( 1 ) ) )
n = ( n ) + ( 1 )
}
}
RETURN nsq```

### 输出

```
4761```

# 题解

## 作者：zhzh2001 (赞：5)

## 题解


初看这道题感觉十分难做，除了麻烦的语法分析，还需要优化循环。


[官方题解](http://www.usaco.org/current/data/sol\_cowbasic\_platinum\_open17.html)


### 循环不嵌套


此时直接模拟即可，最多只有50个循环。


### 只有一个变量


当只有一个变量的时候，可以得到一个通项公式，但实际**并不实用**。具体可参考官方题解。


### 使用矩阵乘法


理论上，通过公式也可以做这道题，但是用矩阵乘法更加简洁。


#### 构造转移矩阵


矩阵中包含各个变量的转移关系。对于矩阵A和B，先后执行等价于乘以A\*B。而A循环n次则等价于乘以$A^n$。


对于`nsq = ( nsq ) + ( ( n ) + ( ( n ) + ( 1 ) ) )`，构造矩阵为


```cpp
    1    n    nsq
1    1
n        1
nsq    1    2    1
```

注意转移**没有被赋值**的量。


另外，**直接忽略表达式中的括号**，因为加法没有优先级问题。


#### 处理嵌套循环


维护一个栈，保存每层循环的结果和循环次数。


有新循环时，压入一个单位矩阵；循环退出时，弹出栈顶，执行快速幂，并与下一层相乘。


#### 时间复杂度


矩阵大小不超过100x100，最多有50个循环，每个循环最多计算$log_2(10^5) \sim 17$次矩阵乘法。实际上运算量不到1亿，可以轻松通过。


## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105,MOD=1e9+7;
int n,cnt[N];
//cnt[]保存每层循环的次数
struct matrix
{
    long long mat[N][N];
    matrix()
    {
        memset(mat,0,sizeof(mat));
    }
    matrix operator*(const matrix& rhs)const
    {
        matrix ans;
        for(int i=1;i<=n;i++)
            for(int k=1;k<=n;k++)
                for(int j=1;j<=n;j++)
                {
                    ans.mat[i][j]=(ans.mat[i][j]+mat[i][k]*rhs.mat[k][j])%MOD;
                    assert(ans.mat[i][j]>=0);
                }
        return ans;
    }
    matrix operator*=(const matrix& rhs)
    {
        return *this=*this*rhs;
    }
}S[N];
//矩阵栈
matrix I()
{
    matrix ans;
    for(int i=1;i<=n;i++)
        ans.mat[i][i]=1;
    return ans;
}
//单位矩阵
matrix qpow(matrix a,int b)
{
    matrix ans=I();
    do
    {
        if(b&1)
            ans*=a;
        a*=a;
    }
    while(b/=2);
    return ans;
}
//矩阵快速幂
string code[N];
template<typename T>
inline T get_token(const string& s)
{
    stringstream ss(s);
    T ret;
    ss>>ret;
    return ret;
}
//将字符串s中的下一个内容转换为T
int main()
{
    map<string,int> var;
      //保存变量名对应的编号
    var["1"]=1;
    //没什么用
    int lines=0;
    n=1;
    while(getline(cin,code[++lines]))
        if(code[lines].find('=')!=string::npos)
        {
            string name=get_token<string>(code[lines]);
              //题目保证所有变量都会为左值
            if(var.find(name)==var.end())
                var[name]=++n;
        }
    lines--;
    int sp=1;
    S[sp]=I();
    for(int i=1;i<=lines;i++)
        if(code[i].substr(0,6)=="RETURN")
            cout<<S[sp].mat[var[get_token<string>(code[i].substr(6))]][1]<<endl;
            //运算结果保存在矩阵第一列中
        else
            if(code[i].find("MOO")!=string::npos)
              //新循环
            {
                S[++sp]=I();
                cnt[sp]=get_token<int>(code[i]);
            }
            else
                if(code[i].find('}')!=string::npos)
                  //循环结束
                {
                    S[sp-1]=qpow(S[sp],cnt[sp])*S[sp-1];
                    sp--;
                }
                else
                {
                    matrix now;
                    int row=var[get_token<string>(code[i])],p=code[i].find('=')+1;
                    stringstream ss(code[i].substr(p));
                    string token;
                    while(ss>>token)
                    {
                        if(isdigit(token[0]))
                            now.mat[row][1]+=get_token<int>(token);
                              //累加常数
                        else
                            if(isalpha(token[0]))
                                now.mat[row][var[token]]++;
                                  //累加变量
                    }
                    for(int i=1;i<=n;i++)
                        if(i!=row)
                            now.mat[i][i]=1;
                  //转移未赋值的量
                    S[sp]=now*S[sp];
                }
    return 0;
}
```

语法分析时应该充分利用空格，同时也要防止多余的空格。



---

## 作者：devout (赞：3)

## 手写栈一定要清空！！！
## 手写栈一定要清空！！！
## 手写栈一定要清空！！！

重要的事情说三遍

因为这个地方debug了2天...

[当然，还是博客内食用更佳](https://blog.csdn.net/devout_/article/details/104652659)

首先，我们应该把这些东西都读进来，因为在线读在线做的话不太好做

我第一天试着边读边做，应该也能弄，就是判断一下小括号和大括号数看看有没有换行就可以，但是细节挺多，交上去成功拿到了6分(样例分）

于是第二天我选择把所有东西都读进来做(~~洛谷运势：宜重构代码~~），然后猛然发现第一天脑子抽到没有想到string.find()，~~STL大法好~~

然后瞎搞（这种题能怎么说做法呢...），注意不能一次一次的加，需要矩阵乘法加速一下，因为有常数项的因素，所以我们的矩阵大小应该是变量数+1，还有一个1的位置

显然我们需要用栈来模拟循环

我们可以在外面套上一个虚拟的循环，这样就解决了那些奇奇怪怪的问题

我们把语法分成四种类型

**1.开始循环语句** 

判断方法：string.find('{')

做法：向栈顶压入一个单位矩阵记录下一个循环的答案

**2.结束循环语句**

判断方法：string.find('}')

做法：这个循环的上一个（栈顶-1）乘上这个循环的矩阵的循环次数次幂

**3.return语句**

判断方法：string.find("RETURN")

做法：输出

**4.赋值语句**

判断方法：else+else+else

做法：

因为一个赋值语句只占一行，所以我们先求出这个赋值语句的赋值变量是什么（第一个单词），然后每次去找，括号什么的直接略过，处理出这样一个矩阵，但是这个矩阵只维护了一个变量的信息，所以我们需要把这个矩阵其它的$a_{i,i}$都变成1，然后乘上这个矩阵所对应的答案

完成上面那些东西需要我们多写两个函数

$split(string,int)$

表示从string的int位置开始提取出一段连续的字符串，注意int传进去应该加一个&，因为那个变量写需要变

$todigit(string)$

表示把这个string转化成int类型（听说STL也能实现，然而我不会就只能自己动手写了qwq）

然后交上去，发现是0分

下载一下数据，发现有缩进！

于是我们再写一个$skip$表示跳过空格

然后再交上去，31分

调了2天，发现了问题，我写的是把矩阵数组整个当成一个栈了，所以这样的话我们需要每次开一个点的时候把这个点的矩阵清空一下，然后构造单位矩阵

代码：~~没删调试之前160行...~~

```cpp
# include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)
# define debug puts("QAQ");

typedef long long ll;
const int N=105;
const int mod=1e9+7;
const double eps=1e-7;

# define int long long

template <typename T> void read(T &x){
	x=0;int f=1;
	char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
	x*=f;
}

map<string,int> var;
int n,num,sum;
string s[N];
int inds[N];

struct matrix{
	int a[N][N];
	matrix(){memset(a,0,sizeof(a));}
	void build(){
        memset(a,0,sizeof(a));
		Rep(i,1,num)a[i][i]=1;	
	}
	void print(){
		Rep(i,1,num)
			Rep(j,1,num)
				printf("%d%c",a[i][j],j==num?'\n':' ');	
	}
	matrix operator * (const matrix &m)const{
		matrix res;
		Rep(i,1,num)
			Rep(j,1,num)
				Rep(k,1,num)
					res.a[i][j]=1ll*(res.a[i][j]+1ll*a[i][k]*m.a[k][j])%mod;
		return res;	
	}
}mat[N];

matrix Qpow(matrix base,int ind){
	matrix res;
	res.build();
	while(ind){
		if(ind&1)res=res*base;
		base=base*base;
		ind>>=1;
	}
	return res;
}

void skip(string s,int &p){
    while(p<s.size()&&!((s[p]>='0'&&s[p]<='9')||(s[p]>='a'&&s[p]<='z')||s[p]=='{'||s[p]=='}'||s[p]=='('||s[p]==')'))p++;
}

string split(string s,int &p){
	string res;
    skip(s,p);
	while(p<s.size()&&((s[p]>='0'&&s[p]<='9')||(s[p]>='a'&&s[p]<='z')||s[p]=='{'||s[p]=='}'||s[p]=='('||s[p]==')'))res+=s[p++];
	return res;	
}

int todigit(string s){
	int num=0;
	for(int i=0;i<s.size();i++)
		num=num*10+s[i]-'0';
	return num;	
}

signed main()
{
    num=1;
	while(getline(cin,s[++n]))
		if(s[n].find('=')!=string::npos){
			int zero=0;
			string vars=split(s[n],zero);
			if(!var[vars])
				var[vars]=++num;	
		}
	sum=1;
	mat[sum].build();
	Rep(i,1,n){
		int zero=0;
		if(s[i].find("RETURN")!=string::npos){
			int seven=7;
			printf("%lld\n",mat[sum].a[var[split(s[i],seven)]][1]);
			return 0;
		}
		else
			if(s[i].find('{')!=string::npos){
				mat[++sum].build();
                zero=0;
				inds[sum]=todigit(split(s[i],zero));
			}
			else
				if(s[i].find('}')!=string::npos){
					mat[sum-1]=Qpow(mat[sum],inds[sum])*mat[sum-1];
					sum--;
				}
				else{
					matrix A;
					int p=0;
					string t=split(s[i],p);
                    p=s[i].find('=')+1;
					int vars=var[t];
					for(;p<s[i].size();p++){
                        skip(s[i],p);
						if(isdigit(s[i][p])){
							A.a[vars][1]+=todigit(split(s[i],p));
                            A.a[vars][1]%=mod;
                        }
						else
							if(isalpha(s[i][p]))
								A.a[vars][var[split(s[i],p)]]++;
                    Rep(i,1,num)if(i!=vars)A.a[i][i]=1;
					mat[sum]=A*mat[sum];
				}
	}
	return 0;
}

```


---

## 作者：fydj (赞：1)

# 题解

### 题目大意

给你一段 CowBasic 语言的代码，要求输出返回的值。

---

### 算法

这一道题目的一大难点就是如何优化大量的循环。如果只有一个变量的话，可以构造公式，然而这对于多个变量的情况来说并不适用。

注意到每一个循环其实就是把一堆变量反复多次相互进行复杂的操作。那么思考一下就会想到用**矩阵**来处理。

具体来说，假设只有 $a$，$b$，$c$ 三个变量，那么可以构造出这样一个矩阵：

$$
Ans = \left [ {\begin{array}{cc}1 & a & b & c \\\end{array} } \right ]
$$

如果有一个赋值结构：$a=a+b+c+5$，那么可以构造出这样一个矩阵：

$$
opt = \left [ { \begin{array} {cc} 1 & 0 & 0 & 0 \\ 1 & 1 & 0 & 0 & \\ 1 & 0 & 1 & 0 & \\ 5 & 0 & 0 & 1 \\\end{array} } \right ]
$$

把它们相乘就得到进行完一次操作以后的矩阵了。

想清楚了这个，接下来的操作也就变得简单了。我们可以把每一个赋值结构看成一个矩阵，同一个循环里的多个赋值结构可以通过简单的矩阵乘法来把它们合并成一个矩阵，一个循环也可以在它里面的操作全部合并成一个矩阵了以后使用矩阵快速幂来化成一个矩阵，最后只要把剩下的几个矩阵和 $Ans$ 矩阵乘起来就得到答案了。

---

### 输入

输入不算一个难点，但是比较麻烦。观察到变量与变量之间、表达式与括号之间、符号与符号之间都有空格分开，这使得我们可以直接用 cin 读入 string 完成输入。

一边输入的时候还要一边判断，如果输入的是一个数字，那么就意味着有一个新的 $Moo$ 循环，读入两个没有用的标志符以后开始递归处理这一个循环。如果读到的是一个英文，这意味着正在读入一个赋值结构，然后递归读入后面的表达式就好了。如果读入的赋值结构的左值没有出现过，那么就把 $Ans$ 矩阵的宽度加一，再把 $opt$ 矩阵的高度和宽度都加一。

---

### 细节

打完代码以后在 jzoj 上交了一次，发现 RE 了。这说明有一些细节没有实现到位。

1. 一个矩阵要用二维 vector 进行存储，原因是在用到递归的时候，返回的矩阵大小太大，导致栈空间不够。

2. 矩阵快速幂不要用递归做，原因同上。

当然，栈空间不够的问题也可以用手动模拟栈的方式来解决。

---

### 代码

最后附上又臭又长的代码：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<cmath>
#include<unordered_map>
#define N 102
#define rei 
#define isnum(check_num) ((check_num)>47&&(check_num)<58)
#define Add(be_adder,adder) be_adder=(be_adder+(adder))%moder
using namespace std;
typedef long long ll;
char chart; bool fushu;
template <typename T> void read(T &a) { a=fushu=0; do chart=getchar(); while((chart<48||chart>57)&&chart!='-'); if(chart=='-') fushu=1,chart=getchar(); do a=(a<<1)+(a<<3)+(chart^48),chart=getchar(); while(chart>47&&chart<58); if(fushu) a=-a; return ; }
template <typename T,typename ...Args> void read(T &a,Args &...args) { read(a); read(args...); return ; }
const ll moder=1000000007;
string str;
unordered_map <string,int> Names={}; int sz=1;
ll kuai(ll a,ll b) { if(b==1) return a; ll t=kuai(a,b>>1); if(b&1) return t*t%moder*a%moder; else return t*t%moder; }
struct ju { int height,weight; vector<vector<ll>> a;
	void setju(int ht,int wt) { rei int i; height=ht,weight=wt; vector<ll> hang={}; for(i=0;i<=wt;++i) hang.push_back(0); for(i=0;i<=ht;++i) a.push_back(hang); return ; }
	void addlie() { rei int i; ++weight; for(i=0;i<=height;++i) a[i].push_back(0); return ; }
	void addhang() { rei int i; ++height; vector<ll> hang={}; for(i=0;i<=weight;++i) hang.push_back(0); a.push_back(hang); return ; }
	void print() { rei int i,j; printf("%d*%d\n",height,weight); for(i=1;i<=height;++i) { for(j=1;j<=weight;++j) printf("%lld ",a[i][j]); printf("\n"); } printf("\n"); return ; }
	friend ju operator * (const ju a,const ju b) {
		rei int i,j,k; ju ans={};
		ans.setju(a.height,b.weight);
		for(i=1;i<=ans.height;++i)
			for(j=1;j<=ans.weight;++j)
				for(k=1;k<=a.weight;++k)
					ans.a[i][j]=(ans.a[i][j]+(ll)a.a[i][k]*b.a[k][j]%moder)%moder;
		return ans;
	} 
} ans={},opt={};
int ka[N]={},ska;
ju kuai(ju a,int b) {
	ju rey=a;
	ska=0; while(b) ka[++ska]=b&1,b>>=1; --ska;
	while(ska) { rey=rey*rey; if(ka[ska]) rey=rey*a; --ska; }
	return rey;
}
struct line { int sz; vector<ll> a={};
	void print() { rei int i; for(i=1;i<=sz;++i) printf("%lld ",a[i]); printf("\n"); return ; }
	void setline(int lg) { rei int i; sz=lg; for(i=0;i<=sz;++i) a.push_back(0); return ; }
	friend line operator + (const line a,const line b) {
		rei int i; line ans={};
		ans.setline(a.sz);
		for(i=1;i<=ans.sz;++i) ans.a[i]=(a.a[i]+b.a[i])%moder;
		return ans;
	}
};
ll change(string str) { ll rey=0; rei int i,len; for(i=0,len=str.length();i<len;++i) if(isnum(str[i])) rey=(rey<<1)+(rey<<3)+(str[i]^48); else break; return rey; }
line shi() {
	line rey={};
	cin>>str; rey.setline(sz);
	if(isnum(str[0])) rey.a[1]=change(str);
	else if(str[0]=='(') rey=shi(),cin>>str>>str>>str,rey=rey+shi(),cin>>str;
	else rey.a[Names[str]]=1;
	return rey;
}
ju Shi(int lft) {
	ju rey={}; line ln=shi(); rei int i;
	rey.setju(sz,sz);
	for(i=1;i<=sz;++i) if(i!=lft) rey.a[i][i]=1;
	for(i=1;i<=sz;++i) rey.a[i][lft]=ln.a[i];
	return rey;
}
ju Moo(int times) {
	ju rey={}; ju opt={}; int i,d;
	rey.setju(sz,sz); for(i=1;i<=sz;++i) rey.a[i][i]=1; 
	cin>>str>>str;
	while(1) {
		cin>>str;
		if(str=="}") break;
		else if(isnum(str[0])) { opt=Moo(change(str)); while(rey.height!=sz) rey.addhang(),rey.addlie(); rey=rey*opt; }
		else { if(!Names.count(str)) { Names[str]=++sz,d=sz,ans.addlie(); rey.addhang(),rey.addlie(),rey.a[sz][sz]=1; }
			else d=Names[str];
			cin>>str; opt=Shi(d); rey=rey*opt; }
	}
	rey=kuai(rey,times);
	return rey;
}
int main()
{
//	freopen("cowbasic.in","r",stdin);
//	freopen("cowbasic.out","w",stdout);
	rei int d;
	ans.setju(1,1),ans.a[1][1]=1;
	while(1) {
		cin>>str;
		if(str=="RETURN") {
			cin>>str,d=Names[str];
			printf("%lld",ans.a[1][d]);
			return 0;
		} else if(isnum(str[0])) {
			opt=Moo(change(str));
			ans=ans*opt;
		} else {
			if(!Names.count(str))
				Names[str]=++sz,d=sz,ans.addlie();
			else d=Names[str];
			cin>>str;
			opt=Shi(d);
			ans=ans*opt;
		}
	}
}
```

---

## 作者：CrTsIr400 (赞：1)

# P3666 [USACO17OPEN] COWBASIC P 题解

## 前言

模拟赛考到了这个题目，比赛时候最后 $20$ 分钟想到了做法。

本文旨在解决算法流程和一些细节问题。

## 主要算法

首先，如何解决**循环嵌套**计算一些变量的值？

这个循环嵌套可能有**非常非常多**次，直接一个个暴力计算会非常慢。

暴力计算依据的是什么呢？我们需要**在内存之中**取其它变量的值，才能算出这个变量的答案。

暴力计算启发我们考虑赋值语句中**变量相互之间的关系**。

比如，考虑下面的语句：`a=a+b+b+a+c+1+1+1`（括号已经去掉）。

我们想想能不能**写成一个矩阵**的形式转移。即经过了这次操作之后，别的其它变量不变，而这个变量改变。

幸运的是，矩阵乘法就是符合这样条件的操作。

具体而言，假设我们原来内存中的变量有 $n$ 个，那么我设置一个 $(n+1)$ 维向量 $\vec A$，第一位存常数 $1$ 的系数，剩下 $n$ 位为各个变量的系数。那么复制操作就相当于对 $\vec A$ **乘上**（注意乘法顺序）一个指定的矩阵 $B$。

举例：对于上面那个 `a=a+b+b+a+c+1+1+1` 的语句而言，假设原来的向量为 

$$\vec A=\begin{bmatrix}1\\9\\1\\9\end{bmatrix}$$

，那么这条赋值语句**所对应的转移矩阵**就是 

$$B=\begin{bmatrix}1&0&0&0\\3&2&2&1\\0&0&1&0\\0&0&0&1\end{bmatrix}$$

，我们的转移就是 

$$B\times \vec A=\begin{bmatrix}1&0&0&0\\3&2&2&1\\0&0&1&0\\0&0&0&1\end{bmatrix}\times \begin{bmatrix}1\\9\\1\\9\end{bmatrix}$$

。注意在实际乘法的时候 $\vec A$ 在 $B$ 的右边。

于是赋值操作就转化成了这样一个东西：最初是一个对角矩阵，但是在**被赋值量**那一行比较特殊，转化成为了**和各个内存已知量的系数**。

值得注意的是，一个向量 $\vec A$ 两个赋值操作 $B1,B2$ 之后，这个向量应该是 $B2\times B1\times \vec A$。这里读起来很困惑，但是在具体程序编写的时候只需要注意：新变量在**乘号左边**，旧变量**在乘号右边**就可以解决问题了。

实际上我们甚至**不需要**维护向量，只需要维护这些**转移矩阵**的乘积就好了。

分析以下时间复杂度：$O(n^3\times 50\times \log 10^5)$，$n$ 为变量个数，实际上时间复杂度远不到 $9\times 10^8$ 这个规模。

所以应该可以通过。实际上飞快。

## 程序流程

在一切的之前，先**输入**。具体而言，使用一个字符**指针** `s` 读入所有**字符串**。

```cpp
char*s=new char[51419];
fread(s,1,51419,stdin);
```

然后我们就可以通过 `*s` 来访问当前的单字符了。用 `++s` 来访问下一个字符。

这样的读法可以**解决换行或是空格无法读入**的问题，使用 `fread` 可以直接读到 EOF 符号。

---

首先明确一个事实：我们的程序体本身就是需要**返回一个矩阵**的。

然后一个程序体的答案**初始**是**单位矩阵**，即对角线为 $1$。

当有**赋值操作**时候，乘上那个赋值矩阵；

当里面有**循环操作**的时候，递归进去，乘上这个递归所得答案矩阵的多少次方，即为答案。

当里面有 `RETURN` 指令的时候，直接输出答案。

当里面有 `}` 的时候，直接返回答案。

这里有一些实现技巧。

首先先把矩阵封装成为一个类，这不需要细讲。

其次，观察所有字符、指令都是由空格分隔开来的，所以我们可以编写这样一个 `Token()` 指令：

```cpp
string Token(){string ss;
	for(;*s<33;++s);//过滤前面空格/换行符
	for(;*s>32;ss+=*s++);//把非空格/换行符的字符一个个加进 ss 里面
	return ss;}
```

这样就可以得到一个过滤了空格的字符串了。

这里还需要编写一个函数 `Type`，判断一个字符串 `st` 的类型是什么。

```cpp
I Type(cs string&st){
	if(isdigit(st[0]))return 0;//表示是循环前的数字
	if(islower(st[0])){//表示是小写字母，这就是 assign 操作
		if(!m.count(st))m[st]=++n;//这里存入新的一个字符串
		return 1;}//表示这是一个字符串
	if(st[0]=='}')return 3;//表示终止标志
	if(st[0]=='R')return 2;//表示输出答案。
	return -1;}
```

那么，我们在这个循环体内部，不断得到 `Token`，对于类型判断一下，主循环部分就写完了。

```cpp
Ma FOR(){
	Ma re(1);
	for(string token;;){
		switch(Type(token=Token())){
		case 0:re=(FOR()^(stoi(token)))*re;break;//这是一个数字，证明有一个新的循环，应该递归下去。
                //这里就是内部递归下去的矩阵的 stoi(token) 次方，其中这个 stoi 指令代表字符串转成的 int 类型整数
		case 1:re=Expr(m[token])*re;break;//这是一个赋值操作，赋值操作应该递归下去。
                //Expr 是表达式函数，等会讲
		case 2:printf("%d",re.a[m[token=Token()]][0]);//这是 RETURN 操作，直接输出答案。
		case 3:return re;}}}//这是右括号，直接返回答案
//注：这里的矩阵乘法是右乘，即如果有一个新答案 new，那么 re=new*re。
```

然后，讨论 `Expr` 函数。它也需要返回一个矩阵。

考虑到只需要把这行全部读完就行了，然后判断读入的 `Type`，如果是小写字母或者数字就加上这个 `token` 的贡献。

```cpp
Ma Expr(I p){
	Ma re(1);re.a[p][p]=0;
	for(string token;;){
		switch(Type(token=Token())){//获取新的 token
		case 0:re.a[p][0]+=stoi(token);break;//获取数字
		case 1:re.a[p][m[token]]+=1;}//获取字母所对应的编号
		for(;*s<33&&*s!='\n';++s);//这里是一直读到换行
		if(*s=='\n'){return re;}}//如果换行就直接返回并且退出
}
```

于是这题的主要过程就结束啦！

汇总一下，总代码是这样的：

```cpp
#include<bits/stdc++.h>
#define fd(i,a,b) for(I i=(a);i>=(b);--i)
#define cs const 
#define O operator
using namespace std;typedef int I;
const I N=105,mod=1e9+7;
char*s=new char[51419];
I n;
struct Ma{I a[N][N];
	Ma(I t){memset(a,0,sizeof(a));fd(i,n,0)a[i][i]=t;}
	Ma O*(cs Ma b){Ma c(0);
		fd(i,n,0)fd(k,n,0)if(a[i][k])fd(j,n,0)c.a[i][j]+=1ll*a[i][k]*b.a[k][j]%mod,c.a[i][j]%=mod;
		return c;}
	Ma O ^(I k){Ma a(1),x(1);x=*this;
		for(;k;k>>=1,x=x*x)if(k&1)a=a*x;
		return a;}};
map<string,I>m;
string Token(){string ss;
	for(;*s<33;++s);
	for(;*s>32;ss+=*s++);
	return ss;}
I Type(cs string&st){
	if(isdigit(st[0]))return 0;
	if(islower(st[0])){
		if(!m.count(st))m[st]=++n;
		return 1;}
	if(st[0]=='}')return 3;
	if(st[0]=='R')return 2;
	return -1;}
Ma Expr(I p){
	Ma re(1);re.a[p][p]=0;
	for(string token;;){
		switch(Type(token=Token())){
		case 0:re.a[p][0]+=stoi(token);break;
		case 1:re.a[p][m[token]]+=1;}
		for(;*s<33&&*s!='\n';++s);
		if(*s=='\n'){return re;}}
}Ma FOR(){
	Ma re(1);
	for(string token;;){
		switch(Type(token=Token())){
		case 0:re=(FOR()^(stoi(token)))*re;break;
		case 1:re=Expr(m[token])*re;break;
		case 2:printf("%d",re.a[m[token=Token()]][0]);
		case 3:return re;}}}
I main(){
	fread(s,1,51419,stdin);FOR();
	return 0;
}
```

---

## 作者：船酱魔王 (赞：0)

# P3666 [USACO17OPEN] COWBASIC P 题解

## 题意回顾

给定一个 COWBASIC 语言代码，请判断出这个代码的结果。

COWBASIC 语言仅包含这几类语句：

* 常数次数的循环。

* 将一个值赋值为某几个变量加上常数的和。

* 返回某个变量作为程序的结果，这个语句仅在最后一行出现。

代码长度不超过 $ 100 $ 行。

## 分析

显然是不能暴力模拟的，循环嵌套可以让暴力模拟的复杂度上天。

将每个变量编号，特殊的，将常数变量编号为 $ 101 $。对于每条非返回语句，处理成以下三种格式：

* $ a_t \leftarrow \sum_{i=1}^{101} k_ia_i $。

* 循环 $ k $ 次。

* 结束循环。

显然，第一类语句是一个线性常系数齐次递推的结构，考虑建立矩阵优化转移。可以用一个矩阵 $ A $ 代表在运行完这些语句后，$ a_j\leftarrow \sum_{i=1}^{101} A_{i,j}a_i $。而显然相邻两条依次执行的语句的矩阵相乘即为他们依次执行带来的效果矩阵，一个循环内的若干条语句的矩阵乘方即为这个循环的效果矩阵。

此时，可以用表达式求值的方法来合并这些非返回语句，即可出解。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
using namespace std;
const int N = 105;
const int mod = 1e9 + 7;
const int B = 101;
int n;
string str[N];
struct matrix {
    int a[N][N];
} zero, one;
int typ[N];
matrix mat[N];
map<string, int> id;
int crt = 0;
long long rq[N][N];
matrix operator*(matrix p1, matrix p2) {
    matrix res;
    for(int i = 1; i <= B; i++) {
        for(int j = 1; j <= B; j++) {
            for(int k = 1; k <= B; k++) {
                rq[i][j] += (long long)p1.a[k][j] * p2.a[i][k];
            }
        }
    }
    for(int i = 1; i <= B; i++) {
        for(int j = 1; j <= B; j++) res.a[i][j] = rq[i][j] % mod, rq[i][j] = 0;
    }
    return res;
}
void out(matrix wzg) {
    for(int i = 1; i <= B; i++) {
        for(int j = 1; j <= B; j++) {
            cout << wzg.a[i][j] << " ";
        }
        cout << endl;
    }
}
matrix operator^(matrix p1, int p2) {
    matrix res = one;
    while(p2) {
        if(p2 & 1) res = res * p1;
        p1 = p1 * p1, p2 >>= 1;
    }
    return res;
}
int tran(string str) {
    int t = 0;
    for(int i = 0; i < str.size(); i++) t = t * 10 + str[i] - '0';
    return t;
}
matrix solve(int l, int r) {
    if(l > r) return one;
    matrix hzd = one;
    for(int i = l; i <= r; i++) {
        if(typ[i] == 0) hzd = hzd * mat[i];
        if(typ[i] != 0) {
            int j;
            int colo = 0;
            for(j = i; j <= r; j++) {
                if(typ[j] > 0) colo++;
                else if(typ[j] < 0) colo--;
                if(!colo) break;
            }
            hzd = hzd * (solve(i + 1, j - 1) ^ typ[i]);
            i = j;
        }
    }
    return hzd;
}
int main() {
    for(int i = 1; i <= B; i++) one.a[i][i] = 1;
    int whr = 0;
    for(int i = 1; i <= 100; i++) {
        getline(cin, str[i]);
        string now = "";
        str[i] += 'X';
        typ[i] = 0;
        vector<string> vec;
        vec.clear();
        for(int j = 0; j < str[i].size(); j++) {
            if(str[i][j] >= '0' && str[i][j] <= '9') now += str[i][j];
            else if(str[i][j] >= 'a' && str[i][j] <= 'z') now += str[i][j];
            else {
                if(now.size() > 0) vec.push_back(now), now = "";
            }
        }
        if(str[i].find("RETURN") != string::npos) {
            n = i;
            whr = id[vec[0]];
            break;
        }
        if(str[i].find("MOO") != string::npos) {
            typ[i] = tran(vec[0]);
            continue;
        }
        if(str[i].find("}") != string::npos) {
            typ[i] = -1;
            continue;
        }
        if(id.find(vec[0]) == id.end()) id[vec[0]] = ++crt;
        int gzh = id[vec[0]];
        for(int j = 1; j < vec.size(); j++) {
            if(vec[j][0] >= '0' && vec[j][0] <= '9') mat[i].a[gzh][B] = (mat[i].a[gzh][B] + tran(vec[j])) % mod;
            else {
                int cch = id[vec[j]];
                mat[i].a[gzh][cch] = (mat[i].a[gzh][cch] + 1) % mod;
            }
        }
        for(int j = 1; j <= B; j++) {
            if(j != gzh) mat[i].a[j][j] = 1;
        }
    }
    matrix ans = solve(1, n - 1);
    cout << ans.a[whr][B] << endl;
    return 0;
}
```

---

