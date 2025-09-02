# [BalticOI 2004] SCALES (Day 1)

## 题目描述

给您一个平衡的臂秤，一组砝码和一个物体。这些砝码的重量为 $1,3,9,27,81, \cdots$，即每个砝码的重量为 $3$ 的幂，对于每个整数 $k≥0$ 正好有一块砝码重量 $3^k$。物体的重量是 $m$，其中 $m$ 是正整数。你的任务是把物体放在左边的秤盘上，然后把一些砝码放在左右一个或两个秤盘上，使得秤平衡。  

## 说明/提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，$1 \le m \le 10^{100}$。
#### 题目说明  
来源于 [Baltic Olympiad in Informatics 2004](http://www.boi2004.lv/) 的 [Day 1:SCALES](http://www.boi2004.lv/Uzd_diena1.pdf)。  
由 @[求学的企鹅](/user/271784) 翻译整理。

## 样例 #1

### 输入

```
42```

### 输出

```
3 3 9 27
1 81```

## 样例 #2

### 输入

```
30```

### 输出

```
0
2 3 27```

# 题解

## 作者：E_D_ZYZE (赞：7)

推导部分：（高精见代码）

以样例#1为例，将 $(42)_{10}$ 三进制分解为 $(1120)_3$，从低位至高位遍历此数。

1. 第 $i$ 位为 $0$

直接跳过。

2. 第 $i$ 位为 $1$

在右盘放入质量为 $3^{i-1}$ 的砝码。

3. 第 $i$ 位为 $2$

由于每种质量的砝码只有一个，所以不可能同时在右盘放入两个质量为 $3^{i-1}$ 的砝码。解决方案：在左盘放入 $3^{i-1}$ 的砝码，在右盘放入 $3^{i}$ 的砝码，此时即相当于在右盘放入 $3^{i}-3^{i-1}=2\times 3^{i-1}$ 的砝码。

具体做法：在左盘放入质量为 $3^{i-1}$ 的砝码，并使 $i+1$ 位加 $1$（$i+1$ 位之后一并处理即可）。

4. 第 $i$ 位为 $3$

第 $i-1$ 位进位后可能得到第 $i$ 位为 $3$ 的情况，直接向 $i+1$ 位再次进位即可。

---

code:

```cpp
#include <bits/stdc++.h>
using namespace std;

struct node //专门处理 3 的幂用 
{
	int t[ 105 ] , len;
	
	node()
	{
		memset( t , 0 , sizeof t );
		t[ 1 ] = 1;
		len = 1;
	}

	void tim() //乘 3 
	{
		for( int i = 1 ; i <= len ; i ++ )
			t[ i ] *= 3;
		for( int i = 1 ; i <= len ; i ++ )
			t[ i + 1 ] += t[ i ] / 10 , t[ i ] %= 10;
		if( t[ len + 1 ] > 0 )
			len ++;
	}
	
	void print() //输出 
	{
		for( int i = len ; i >= 1 ; i -- )
			printf( "%d" , t[ i ] );
		putchar( ' ' );
	}
};

vector< int > a; //保存三进制的原数 
vector< node > l , r; //保存左右盘中的砝码 

char c[ 105 ];
int len;

int div() //计算商，返回余数 
{
	int t , num = 0;
	for( int i = 1 ; i <= len ; i ++ )
	{
		t = ( num + c[ i ] ) % 3;
		c[ i ] = ( num + c[ i ] ) / 3;
		num = t * 10;
	}
	return t;
}

bool ept()
{
	for( int i = 1 ; i <= len ; i ++ )
		if( c[ i ] > 0 )
			return false;
	return true;
}

void input() //读入高精整数并计算出其三进制的值 
{
	
	scanf( " %s" , c + 1 );
	len = strlen( c + 1 );
	for( int i = 1 ; i <= len ; i ++ )
		c[ i ] -= '0';
	while( ! ept() )
	{
		a.push_back( div() );
	}
	a.push_back( 0 );
}

signed main()
{
	input();
	
	node base;
	for( int i = 0 ; i < a.size() ; i ++ ) //见上文推导过程 
	{
		if( a[ i ] == 3 )
		{
			a[ i ] = 0;
			a[ i + 1 ] ++;
		}
		if( a[ i ] == 2 )
		{
			l.push_back( base );
			a[ i ] = 0;
			a[ i + 1 ] ++;
		}
		if( a[ i ] == 1 )
		{
			r.push_back( base );
		}
		base.tim();
	}
	
	printf( "%d " , l.size() );
	for( int i = 0 ; i < l.size() ; i ++ )
		l[ i ].print();
	printf( "\n%d " , r.size() );
	for( int i = 0 ; i < r.size() ; i ++ )
		r[ i ].print();
	return 0;
}
```

---

Thanks for watching.

---

## 作者：yz_zy (赞：2)

# [题解P7649 SCALES](https://www.luogu.com.cn/problem/P7649)
## 题意
天平左盘放置一个重量为 $m$ 的物品，要通过在天平左盘和右盘放置重量均为 $3^k$ 的砝码使天平平衡，每种砝码仅有一个。
## 分析
看到 $3^k$，不难想到要对 $m$ 进行 $3$ 进制转换。再次结合题目，发现每种砝码只有一个。可以想到，三进制转换后的 $m$ 每一位应要么为 $1$ 要么为 $0$，只有这样，才能保证在右盘放置砝码时只需要 $1$ 个或不需要。

再去思考，对于三进制下 $m$ 中 $2$ 应如何处理。很显然，假设这一位是第 $k$ 位，则很显然应放入一个重量为 $3^k$ 的砝码，使它进位，让第 $k+1$ 位 $+1$，此时要特别注意若下一位变成了 $3$，要令它继续进位。

那么这一题不就轻而易举的做出来了，是吗？

细看数据范围 $ 1 \le m \le 10^{100}$，则很显然需要高精，详细请看代码。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=301;
string s;
int n,a[N],b[N],c[N],m;
int p[N][N],cnt[N],h[N],now[N];
int ans[N],k,aans[N],kk;
void solve()//主要使用高精除低精，用 a 数组去除以 3  
{
	int d=0;
	for(int i=1;i<=n;i++)
	{
		b[i]=(d*10+a[i])/3;
		d=(d*10+a[i])%3;
	}
	int len=1;
	while(b[len]==0&&len<n) len++;
	memset(a,0,sizeof(a));
	int tt=n-len+1;
	for(int i=1,j=len;i<=tt,j<=n;i++,j++)
		a[i]=b[j],b[j]=0;
	n=tt;
	c[++m]=d;
}
void help(int x)// help 中需使用高精乘低精 
{
	int len1=cnt[x-1];
	for(int i=1;i<=len1;i++) h[i]=p[x-1][i];
	reverse(h+1,h+1+len1);
	h[len1+1]=0;
	int d=0;
	for(int i=1;i<=len1;i++)
	{
		h[i]*=3;
		h[i]+=d;
		d=h[i]/10;
		h[i]%=10;
	}
	h[len1+1]+=d;
	if(h[len1+1]) len1++;
	cnt[x]=len1;
	reverse(h+1,h+1+len1);
	for(int i=1;i<=len1;i++)
		p[x][i]=h[i];
}
int main()
{
	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>s;
	n=s.size();
	for(int i=1;i<=n;i++) a[i]=s[i-1]-'0';//将数组平移 
	while(1)//多次处理，拆分进制，出来的 c 数组即 m 的三进制拆分数组 
	{
		if(n==1&&a[n]==0) break;
		solve();
	}
	cnt[0]=1;
	p[0][1]=1;
	for(int i=1;i<=m+2;i++)//help 函数去辅助求 3 的 k 次方，p 数组为 3 的 k 次方答案数组，cnt 为长度数组 
		help(i);
	for(int i=1;i<=m;i++)//此 for 循环是用来处理数组中进位和每一个 2，ans 数组即为求出的每一位 2 
	{
		if(c[i]==2)
		{
			ans[++k]=i-1;
			c[i+1]++;
			c[i]=0;
		}
		if(c[i]==3)
		{
			c[i+1]++;
			c[i]=0;
		}
	}
	cout<<k<<' ';
	for(int i=1;i<=k;i++)
	{
		int pp=ans[i];
		for(int j=1;j<=cnt[pp];j++)
			cout<<p[pp][j];
		cout<<' ';
	}
	cout<<'\n';
	for(int i=1;i<=m+1;i++)//aans 数组为左盘放的砝码 
		if(c[i])
			aans[++kk]=i-1;
	cout<<kk<<' ';
	for(int i=1;i<=kk;i++)
	{
		int pp=aans[i];
		for(int j=1;j<=cnt[pp];j++)
			cout<<p[pp][j];
		cout<<' ';
	}
	return 0;
}
```

---

## 作者：sweet_melon (赞：2)

~~蒟蒻的第一篇题解。~~ \
[题目传送门](https://www.luogu.com.cn/problem/P7649)

---
## 形式化题意
给出一个正实数 $m$，要求构造集合 $A$、$B$，满足 $\forall x \in A, x=3^k \land \forall y \in B, y=3^l (k,l\in N) \land \sum A + m = \sum B $。\
输出 $\left| A \right|,\left| B \right|$ 及 $A,B$ 中的元素。

### 思路

显然，我们可以将 $m$ 转化为三进制来做，这里用几个例子来帮助理解。

当 $m=30$ 时 $(30)_{10}=(1010)_3$，很明显，集合 $B$ 的元素就是三进制下含 $1$ 的位所对应的十进制数，即 $\left \{ (10)_3 , (1000)_3 \right \}$ 所对应的十进制集合 $\left \{ 3 , 27 \right \}$。

当 $m=42$ 时 $(42)_{10}=(1120)_3$，此时，因为集合 $B$ 元素的互异性，我们不能选用两个 $(3)_{10}$，想到可以往集合 $A$ 中增加元素 $(3)_{10}$，使得等式左端总和变为 $(45)_{10}$，即 $(1200)_3$，此时就解决了三进制下第二位的问题。\
接下来再重复上述操作，将 $(42)_{10}$ 变为 $(81)_{10}$，即 $(10000)_3$，此时三进制中不含 $2$，则得出集合 $A=\left\{ 3,9,27\right\}$，集合 $B=\left\{ 81\right\}$。

我们可以写出伪代码：
```
input m
change 10进制m->3进制m

for (digit : m从低位到高位) {
  if(digit = 0) 不做处理
  if(digit = 1) 将(digit)所对应10进制数加入集合A
  if(digit = 2) {
    将(digit)所对应10进制数加入集合B
    把当前(digit)的高一位+1,当前位清零
  }
  if(digit = 3) 把当前(digit)的高一位+1
}

output (A.size , A.elements)
output (B.size , B.elements)
```

## 代码
思路很简单，但 $m \in \left[1, 10^{100} \right]$，所以我们要用高精实现，代码如下，细节看注释:(码风可能比较抽象，见谅)。
```cpp
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
#define int long long
#define System 3  //宏定义进制，增强代码可读性
using namespace std;

const int MAXN(1e3+5);

int num[MAXN], Tnum[MAXN], m; //num是输入的m， Tnum是m的三进制， m是Tnum的有效位长度
string Pow[MAXN]; //预处理放3^k
vector<string> Lans, Rans; //存答案leftans, rightans

inline string mul(string a){
	int l=a.size();
	for(int i=l-1;i>=0;i--) a[i]=(a[i]-'0')*System+'0';
	for(int i=l-1;i>=0;i--) 
		if(a[i]>'9')
			if(i==0){  a="0"+a; i+=2; continue;  } //这里可能比较抽象，自己手算模拟一下就明白了
			else a[i-1]+=(a[i]-'0')/10,   a[i]=(a[i]-'0')%10+'0';
	return a;
} // 这里是string * int用的函数

void init(int Max){
	string a="1";
	for(int i=0;i<=Max;i++)
		Pow[i]=a,  a=mul(a);
	return ;
}//预处理出Pow[]

void reverseA(){  for(int i=1;i*2<=(m+1);i++) swap(Tnum[i],Tnum[m-i+1]);  return; } //反转数组Tnum，这里是短除法的原理，最后需要倒着转为3进制

void change(int n){
	while(n){
		int k=0, sum=0, flag=0;
		for(int i=1;i<=n;i++){
			sum=sum*10+num[i];
			if((sum>=System)||flag)  num[++k]=sum/System,  sum%=System,  flag=1;
		}
		n=k, Tnum[++m]=sum;
	}
	reverseA();  return;
}//转换m为三进制

signed main(){
	IOS;
	
	init(210);//log3(10^100) = 100*log3(10) ≈ 209
	string s;  cin>>s;
	int n=s.size();
	for(int i=0;i<n;i++) num[i+1]=s[i]-'0';
	
	change(n);
	//下面在思路里讲过了
	for(int i=m;i>=0;i--){
		if(Tnum[i]==0) continue;
		else if(Tnum[i]==1) Rans.push_back(Pow[m-i]);
		else if(Tnum[i]==2) {
			Lans.push_back(Pow[m-i]);
			Tnum[i-1]++;
		}else if(Tnum[i]==3)
			Tnum[i-1]++, Tnum[i]=0;
	}
	
	cout<<Lans.size();
	for(int i=0;i<Lans.size();i++) cout<<' '<<Lans[i];
	cout<<endl;
	
	cout<<Rans.size();
	for(int i=0;i<Rans.size();i++) cout<<' '<<Rans[i];
	return 0;
}
```
~~这应该是最短代码吧。~~

---

## 作者：Liyhzh_Diary (赞：2)

[传送门](https://www.luogu.com.cn/problem/P7649)

由于本题楼上两位已经给出很详细的代码了，我就不给代码了（~~其实是懒，后期可能会补。~~）。

先讲解一下什么是三进制：

> 三进制是以 3 为底数的进位制，使用 0、1、2 三个数码表示数字，逢三进一。

对于一个数 $x$，肯定可以被表示为 $(\overline{x_1x_2 \cdots x_n})_3$，且保证 $x_i\in \{0,1,2\}$。

------------

对于一个三进制数 $(\overline{x_1x_2 \cdots x_n})_3$ 可以表示为 $x_1 \cdot3^{n-1}+x_2 \cdot 3 ^{n-2}+ \cdots +x_n$。

所以，对于每一个数，都可以表示成 $x_1 \cdot3^{n-1}+x_2 \cdot 3^{n-2}+ \cdots +x_n \cdot 3^0$ 的形式，所以这道题就迎刃而解了。

推荐一道相似题：[[CSP-J2020] 优秀的拆分](https://www.luogu.com.cn/problem/P7071)（只不过是二进制）。

这就是一道很基本的三进制的题，只不过加了高精。

所以就可以先把物体放在左盘。

显然可以把 $m$ 换成 $3$ 进制，设转换后为 $x$，位数有 $s$ 位。

当 $x_i \ne0$（$1\le i \le s$），则可以在右盘加 $3^{s-i}$ 重的砝码。

但是呢要注意：

1. 若 $x_i = 2$，则需将 $x_{i+1}$ 加一，左盘砝码加一，因为一个砝码只有一个。

2. 若 $x_i=3$，则将 $x_{i+1}$ 加一即可。

这题麻烦的其实是高精，注意细节。

调了两天才调出来的代码：

```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;

typedef long long ll;
typedef double db;
typedef __int128 III;
const db eqs=1e-6;
const int inf=1e9;
void cmax(int &a,int b){a=max(a,b);}
void cmin(int &a,int b){a=min(a,b);}
bool db_eq(db a,db b){return fabs(a-b)<eqs;}

const int MAXN=10000+5;
string s; 
vector<int>a,b;
vector<int>st,st2;
int c[MAXN][MAXN];

void clean1(){while(!a.empty()) a.pop_back();}
void clean2(){while(!b.empty()) b.pop_back();}

int div()
{
//	cout<<"514"<<endl;
	int yu=0,id,cur=-1;
	int len=a.size(),x=0;
	if(a.size()==1 && a[0]==1)
	{
		a[0]=0;
		return 1;
	}
	if(a.size()==1 && a[0]==2)
	{
		a[0]=0;
		return 2;
	}
	for(int i=0;i<len;i++)
	{
		if(x*10+a[i]>=3) 
		{
			id=i;
			break;
		}
		x=x*10+a[i];
	}
	yu=x;
//	cout<<id<<" "<<x<<" ";
	for(int i=id;i<len;i++)
	{
		b.push_back((a[i]+yu*10)/3);
		yu=(yu*10+a[i])%3;
	}
//	cout<<yu<<endl;
	clean1();
	for(int i=0;i<b.size();i++) a.push_back(b[i]);
	clean2();
	return yu;
}

void power()
{
	c[0][1]=1,c[0][2]=-1;
	for(int i=1;i<=st.size();i++)
	{
		int id;
		for(int j=1;;j++) 
		{
			if(c[i-1][j]==-1) 
			{
				id=j-1;
				break;
			}
		}
//		cout<<id<<endl;
		for(int j=id;j>=1;j--)
		{
			c[i][j]+=c[i-1][j]*3;
			if(c[i][j]>=10) c[i][j-1]+=c[i][j]/10,c[i][j]%=10;
		}
		if(c[i][0]>0)
		{
			for(int j=id;j>=0;j--) c[i][j+1]=c[i][j];
			c[i][id+2]=-1;
			c[i][0]=0;
		}
		else c[i][id+1]=-1;
	}
}

void print()
{
	for(int i=0;i<a.size();i++) cout<<a[i];
	cout<<endl;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>s;
//	cout<<s<<endl;
	int len=s.size();
	for(int i=0;i<len;i++) a.push_back(s[i]-'0');
//	print();
	while(a[0]!=0)
	{
		st.push_back(div());
//		print();
//		cout<<114<<endl;
	}/*
	while(!st.empty())
	{
		cout<<st.top()<<" ";
		st.pop();
	}
	cout<<endl;*/
	power();/*
	for(int i=0;i<st.size();i++) 
	{
		cout<<i<<" ";
		for(int j=1;;j++)
		{
			if(c[i][j]==-1)
			{
				cout<<endl;
				break;
			}
			cout<<c[i][j];
		}
	}*/
//	for(int i=0;i<st.size();i++) cout<<st[i]<<" ";cout<<endl;
	len=st.size();
	for(int i=0;i<len;i++)
	{
		if(st[i]==2)
		{
			if(i!=len-1) st[i+1]++;
			else st.push_back(1);
			st[i]=0;
			st2.push_back(i);
		}
		else if(st[i]==3)
		{
			st[i]=0;
			if(i!=len-1) st[i+1]++;
			else st.push_back(1);
		}
	}
	cout<<st2.size()<<" ";
	for(int i=0;i<st2.size();i++)
	{
		for(int j=1;;j++)
		{
			if(c[st2[i]][j]==-1) 
			{
				cout<<" ";
				break;
			}
			cout<<c[st2[i]][j];
		}
	}
	int cnt=0;
//	cout<<endl;
	for(int i=0;i<st.size();i++) cnt+=(st[i]>0);
	cout<<endl<<cnt<<" ";
	for(int i=0;i<st.size();i++)
	{
		if(st[i]==0) continue;
		for(int j=1;;j++)
		{
			if(c[i][j]==-1) 
			{
				cout<<" ";
				break;
			}
			cout<<c[i][j];
		}
	}
	cout<<endl;
	return 0;
}


```

---

## 作者：0x00AC3375 (赞：1)

## 1. 题意

- 本题的题目背景是使用砝码称量物体质量，所有砝码的质量皆为 $3$ 的整数次幂次。

- 现在要求对于一块质量已知，放在左盘区的物体，如何在左右盘中合理放置这些砝码使得天平平衡。

## 2. 分析

首先是托盘天平的读数方法。当物块放在左边，放置砝码使得天平平衡，那么用右边的砝码总质量减去左边砝码的总质量，差值就是物块的质量。

由此我们容易想到，对于一个砝码，如果放在右边就记为正值，放在左边记为负值，那么本题即可转化为将给定正整数转化为一些 $3$ 的幂次的和减去另一些 $3$ 的幂次的差。

上面这个过程的核心原理是**平衡三进制**。将初始输入的十进制值转化为平衡三进制即可求解。平衡三进制是一种使用 $-1,0,1$ 三个数码的计数体系。为书写方便，一般会使用字母 $\text{Z}$ 表示 $-1$ 的数位。

例如对于平衡三进制下的 $(1\text{Z}101)_\text{balance3}$，化为十进制的结果是：

$$(1\text{Z}101)_\text{balance3}=1\times3^4+(-1)\times3^3+1\times3^2+0\times3^1+1=64$$

从上面的结果很容易看出，$64$ 被拆分为了$81,-27,9,1$，也就是说将 $27$ 和质量为 $64$ 的物体放在左侧，将 $81,9,1$ 放在右侧即可平衡。

**参考：**

[1] [AT_past202107_g 题解](
https://www.luogu.com.cn/article/zxgefs4a)

[2] [平衡三进制 on OI-wiki](https://oi-wiki.org/math/balanced-ternary/)

[3] [平衡三进制](https://baike.baidu.com/item/%E5%B9%B3%E8%A1%A1%E4%B8%89%E8%BF%9B%E5%88%B6/9370144?fr=ge_ala)

## 3. 代码

### (1) Python

```python
# 将十进制转化为平衡三进制
def ToBalance3(decimal_value: int):
    current = decimal_value
    result = list()
    while current:
        result.append(current % 3)
        current //= 3
    result.append(0)
    for i in range(len(result) - 1):
        if result[i] == 2:
            result[i] = -1
            result[i + 1] += 1
        if result[i] == 3:
            result[i] = 0
            result[i + 1] += 1
    return result

# 将平衡三进制按照±1划分为左右部分
def LeftVsRight(balancebase3sequence: list):
    left = list()
    right = list()
    for i in range(len(balancebase3sequence)):
        if balancebase3sequence[i] == 1:
            right.append(i)
        elif balancebase3sequence[i] == -1:
            left.append(i)
        elif balancebase3sequence[i] == 0:
            continue
        else:
            raise ValueError("Invalid Balance Base 3 Sequence!")
    return left, right

if __name__ == "__main__":
    target = int(input())
    l, r = LeftVsRight(ToBalance3(target))
    print(len(l), end = " ")
    for i in range(len(l)):
        print(pow(3, l[i]), end = " ")
    print()
    print(len(r), end = " ")
    for i in range(len(r)):
        print(pow(3, r[i]), end = " ")

```

### (2) C#

```csharp
using System.Numerics;
using static System.Numerics.BigInteger;
using System.Collections.Generic;
namespace P7649
{
    public class P7649
    {
        public static List<int> BalanceBase3(BigInteger decimal_value)
        {
            BigInteger current = decimal_value;
            // 将十进制大整数转化为普通三进制, 下标小的是低位，下标大的是高位
            List<int> base3 = new List<int>();
            while (current > 0)
            {
                base3.Add((int)(current % 3));
                current /= 3;
            }
            // 最高位补一个0防止出现数组越界
            base3.Add(0);
            // 将普通三进制转化为平衡三进制
            for (int i = 0; i < base3.Count - 1; i++)
            {
                // 某一位是2，这一位变成-1，然后高位进1
                if (base3[i] == 2)
                {
                    base3[i] = -1;
                    base3[i + 1] += 1;
                }
                // 某一位因为刚才进位变成3，也需要进位，同时这一位变成0
                if (base3[i] == 3)
                {
                    base3[i] = 0;
                    base3[i + 1] += 1;
                }
            }
            return base3;
        }

        public static void Main(string[] args)
        {
            string? value = Console.ReadLine();
            if (value == null) return;
            BigInteger x = BigInteger.Parse(value);
            List<int> balance3 = BalanceBase3(x);
            // 左盘区和右盘区
            List<int> left_container = new List<int>();
            List<int> right_container = new List<int>();
            // 平衡三进制某一位为-1就将对应的砝码放在左盘区，否则放在右盘区
            for (int i = 0; i < balance3.Count; i++)
            {
                if (balance3[i] == 1) right_container.Add(i);
                else if (balance3[i] == -1) left_container.Add(i);
            }
            Console.Write(left_container.Count + " ");
            for (int i = 0; i < left_container.Count; i++) Console.Write(BigInteger.Pow(3, left_container[i]) + " ");
            Console.WriteLine();
            Console.Write(right_container.Count + " ");
            for (int i = 0; i < right_container.Count; i++) Console.Write(BigInteger.Pow(3, right_container[i]) + " ");
        }
    }
}
```

---

## 作者：AzzyZhe (赞：1)

## [题解 P7649 SCALES](https://www.luogu.com.cn/problem/P7649)

### 思路
----
根据题目，我们需要做的是通过在一个左边已有物体的天平两端放砝码以使它平衡，其中砝码重量必须是 $3$ 的次幂，且每个砝码只能放一次，

记 $m$ 为初始重量，简单抽象一下我们得到 ，
$$\sum\limits_{i \in B}3^i + m = \sum\limits_{i \in A}3^i \text{，其中}\begin{cases} A,B\subseteq
N\\A \cap B=\emptyset\end{cases} $$


即
$$m = -1×\sum\limits_{i \in A}3^i + 0×\sum\limits_{i \in B}3^i + 1×\sum\limits_{i \in C}3^i \text{，其中}\begin{cases}A\cap B\cap C=\emptyset\\A\cup B\cup C=N\end{cases} $$

也就是用加减单个 $3$ 的次幂得到 $m$ ，

大胆猜想：所有自然数都可以如此表示？

不妨考虑先表示 $0$ 到 $13$ 的数
```
+表示需要放在右边（加上） -表示放在左边（减去） /表示不需要
    931  附:三进制下表示
00  ///  000  111  13
01  //+  001  112  14
02  /+-  002  120  15
03  /+/  010  121  16
04  /++  011  122  17
05  +--  012  200  18
06  +-/  020  201  19
07  +-+  021  202  20
08  +/-  022  210  21
09  +//  100  211  22
10  +/+  101  212  23
11  ++-  102  220  24
12  ++/  110  221  25
13  +++  111  222  26
```

对于每个 $3$ 的次幂，都有放左边（减）、放右边（加）、不放，三种状态，

正与三进制下 $0$ 、 $2$ 、 $1$ 对应！

很好理解，只要需要用到的每个位上加一即得到，即加上三进制下的 $111...111$ ，

然后将变换后得到的 $m'$ 转化为三进制，检查每位是否为 $0$ （左）或 $2$ （右）即可,

即
$$m' = 0×\sum\limits_{i \in A}3^i + 1×\sum\limits_{i \in B}3^i + 2×\sum\limits_{i \in C}3^i \text{，其中}\begin{cases}A\cap B\cap C=\emptyset\\A\cup B\cup C=N\end{cases} $$

剩下的部分变成了一道高精题。

### 实现
----
有了思路，实现上注意的其实也还是满多的，

首先着眼于主体部分，将大数转化为三进制，为了使这一步来得更简单，我们考虑基于亿进制高精的思路，使用“ $3$ 的次幂进制”高精。

理解这一点，在以 $3$ 的次幂为基的进制下，一个数转化为 $3$ 进制，则其连续几位只与一位有关如，
`78(9) -> 2122(3)`

仔细考虑，这种情况下（基数小化基数大）从十进制转化为 $3$ 进制和平时的进制转换也没有区别，乘 $10$ 、加低位、进位即可。

而输出时则考虑直接用到 $10$ 的次幂进制即可。

### 代码
----
```cpp
#include<cstdio>
#include<cstring>
typedef unsigned long long uint64;
#define POW3_36 150094635296999121
#define POW10_17 100000000000000000
char buf[128];
template<uint64 base>//两个高精只有进制不同所以用模版类了
struct hyNum{
	uint64 dat[8];
	int hy()const //最高位的dat[]下标
	{
		int i=7;
		while(i>0&&dat[i]==0)
			i--;
		return i;
	}
	hyNum &operator*=(uint64 n)//大进制仅在此题下不会出锅
	{
		//if(n!=10&&n!=3)throw -1;
		uint64 add=0;
		int z=hy();
		for(int i=0;i<=z;i++)
			dat[i]*=n,
			dat[i]+=add,
			add=dat[i]/base,
			dat[i]%=base;
		dat[z+1]+=add;//之前脑抽这里进位写错了，直接20pts...
		return *this;
	}
	hyNum &operator+=(uint64 num)
	{
		for(int i=0;num;i++)
			dat[i]+=num,
			num=dat[i]/base,
			dat[i]%=base;		
		return *this;
	}
	hyNum &operator+=(const hyNum<base> &num)
	{
		for(int i=0,z=num.hy();i<=z;i++)
			dat[i]+=num.dat[i],
			dat[i+1]+=dat[i]/base,
			dat[i]%=base;
		return *this;
	}
	void init(const char *base10)//将10进制字符串数字转化为高精度数字
	{
		const char *p=base10;
		while(*p)
		{
			*this*=10;
			*this+=*p-'0';
			p++;
		}
	}
	bool operator>(const hyNum<base> &num)const
	{
		int h1=hy(),h2=num.hy();
		if(h1!=h2)
			return h1>h2;
		while(h1>0&&dat[h1]==num.dat[h1])
			h1--;
		return dat[h1]>num.dat[h1];
	}
};
hyNum<POW3_36> m0,pow3;
hyNum<POW10_17>prl,prr;
int selcbit[256],maxb=0;//三进制下从低到高每位的数字及最高位下标
void print(hyNum<POW10_17> num)//10次幂进制高精输出
{
	int hy=num.hy();
	printf("%llu",num.dat[hy]);
	for(int i=hy-1;i>=0;i--)
		printf("%017llu",num.dat[i]);
}
int mian()
{
	//输入
	scanf("%s",buf);
	prr.dat[0]=1,prl.dat[0]=1;
	pow3.dat[0]=1;
	m0.init(buf);
	
	//判断要加的具体11...11
	while(m0>pow3)
	{
		pow3*=3;
		pow3+=1;
	}
	m0+=pow3;
	
	//计算变换后数三进制下每位数字
	int z=m0.hy();
	for(int i=0;i<z;i++)
	{
		for(int j=0;j<36;j++)
			selcbit[maxb++]=m0.dat[i]%3,
			m0.dat[i]/=3;
	}
	while(m0.dat[z])
		selcbit[maxb++]=m0.dat[z]%3,
		m0.dat[z]/=3;
	
	//统计答案
	uint64 cntl=0,cntr=0;
	for(int i=0;i<maxb;i++)
		if(selcbit[i]==0)
			cntl++;
		else if(selcbit[i]==2)
			cntr++;
	
	//输出
	printf("%llu ",cntl);
	for(int i=0;i<maxb;i++)
	{
		if(selcbit[i]==0)
			print(prl),
			putchar(' ');
		prl*=3;
	}
	putchar('\n');
	printf("%llu ",cntr);
	for(int i=0;i<maxb;i++)
	{
		if(selcbit[i]==2)
			print(prr),
			putchar(' ');
		prr*=3;
	}
	putchar('\n');
	return 0;
}

```


---

## 作者：ZY_king_YB (赞：0)

~~本蒟蒻又来写题解啦哈哈哈哈……~~

# 0.三进制相关知识

在三进制下：

## 相关知识1

$$\forall x\in Z,x=(\overline{x_1x_2 \cdots x_n})$$

且 $x_i\in \{0,1,2\},x_i\in N_+$.

## 相关知识2

$$\forall x=(\overline{x_1x_2 \cdots x_n})_3,x=3^{n-1}x_1 +3^{n-2}x_2+ \cdots +x_n$$.

## 整合

$\therefore\forall x\in Z,x=3^{n-1}x_1+3^{n-2}x_2+ \cdots + 3^0x_n$.

# 1.题目实质

一道**很基本的三进制的题**，只不过运算时要用**高精**。

# 2.思路

优先考虑左盘。

可以先把 $m$ 转换为 $3$ 进制，设转换后的数为 $x$，位数为 $s$.

在 $1\le i \le s$ 且 $x_i \ne0$ 时，则可以在右盘加 $3^{s-i}$ 重的砝码。

## 注意

**第一**，若 $x_i = 2$，则需将 $x_{i+1}$ 加一，左盘砝码加一，因为此时砝码只有一个。

**第二**，若 $x_i=3$，则直接将 $x_{i+1}$ 加一即可。

这题核心算法部分其实很简单，麻烦的是高精。

# 3.代码

~~可给我手写废了（蒟蒻第一次写百行代码哈）。~~

```cpp
//P7649 亲测AC
//具体思路已经写得很清楚了，所以算法部分不再赘述
#include<bits/stdc++.h>
#define long long ll//用ll代替long long
#define INT __int128//用INT代替__int128
#define N 10005//常量N=10005
#define inf 1e9//常量inf=1e9
#define eqs 1e-6//常量eqs=1e6
using namespace std;
void iofast(){ios::sync_with_stdio(0);cin.tie(0);}
//关闭流同步，使cin cout的速度与scanf printf相当 
//注意!!!!关闭后 不!能!使!用scanf和printf!!!!!!! 
void cmax(int &a,int b){a=max(a,b);}
void cmin(int &a,int b){a=min(a,b);}
string s; 
vector<int>a,b;
vector<int>st,st2;
//动态数组 
int c[N][N];
int div(){//高精1
	int yu=0,id,cur=-1;
	int len=a.size(),x=0;
	if(a.size()==1&&a[0]==1){
		a[0]=0;
		return 1;
	}
	if(a.size()==1&&a[0]==2){
		a[0]=0;
		return 2;
	}
	for(int i=0;i<len;i++){
		if(x*10+a[i]>=3) {
			id=i;
			break;
		}
		x=x*10+a[i];
	}
	yu=x;
	for(int i=id;i<len;i++){
		b.push_back((a[i]+yu*10)/3);
		yu=(yu*10+a[i])%3;
	}
	while(!a.empty()) a.pop_back();
	for(int i=0;i<b.size();i++) a.push_back(b[i]);
	while(!b.empty()) b.pop_back();
	return yu;
}
void power(){//高精2
	c[0][1]=1;
	c[0][2]=-1;
	for(int i=1;i<=st.size();i++){
		int id;
		for(int j=1;;j++) {
			if(c[i-1][j]==-1) {
				id=j-1;
				break;
			}
		}
		for(int j=id;j>=1;j--){
			c[i][j]+=c[i-1][j]*3;
			if(c[i][j]>=10) c[i][j-1]+=c[i][j]/10,c[i][j]%=10;
		}
		if(c[i][0]>0){
			for(int j=id;j>=0;j--) c[i][j+1]=c[i][j];
			c[i][id+2]=-1;
			c[i][0]=0;
		}
		else c[i][id+1]=-1;
	}
}
void print(){//输出
	for(int i=0;i<a.size();i++) cout<<a[i];
	cout<<"\n";
}
int main(){
	iofast();//见第8行 
	cin>>s;
	int len=s.size();
	for(int i=0;i<len;i++) a.push_back(s[i]-'0');
	while(a[0]!=0){
		st.push_back(div());
	}
	power();
	len=st.size();
	for(int i=0;i<len;i++){
		if(st[i]==2){
			if(i!=len-1) st[i+1]++;
			else st.push_back(1);
			st[i]=0;
			st2.push_back(i);
		}
		else if(st[i]==3){
			st[i]=0;
			if(i!=len-1) st[i+1]++;
			else st.push_back(1);
		}
	}
	cout<<st2.size()<<" ";
	for(int i=0;i<st2.size();i++){
		for(int j=1;;j++){
			if(c[st2[i]][j]==-1) {
				cout<<" ";
				break;
			}
			cout<<c[st2[i]][j];
		}
	}
	int cnt=0;
	for(int i=0;i<st.size();i++) cnt+=(st[i]>0);
	cout<<"\n"<<cnt<<" ";
	for(int i=0;i<st.size();i++){
		if(st[i]==0) continue;
		for(int j=1;;j++){
			if(c[i][j]==-1){
				cout<<" ";
				break;
			}
			cout<<c[i][j];
		}
	}
	return 0;
}
```
打完收工！~~一定要过啊~~

---

