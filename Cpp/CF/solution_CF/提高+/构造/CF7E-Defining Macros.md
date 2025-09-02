# Defining Macros

## 题目描述

Most C/C++ programmers know about excellent opportunities that preprocessor #define directives give; but many know as well about the problems that can arise because of their careless use.

In this problem we consider the following model of #define constructions (also called macros). Each macro has its name and value. The generic syntax for declaring a macro is the following:

\#define macro\_name macro\_value

After the macro has been declared, "macro\_name" is replaced with "macro\_value" each time it is met in the program (only the whole tokens can be replaced; i.e. "macro\_name" is replaced only when it is surrounded by spaces or other non-alphabetic symbol). A "macro\_value" within our model can only be an arithmetic expression consisting of variables, four arithmetic operations, brackets, and also the names of previously declared macros (in this case replacement is performed sequentially). The process of replacing macros with their values is called substitution.

One of the main problems arising while using macros — the situation when as a result of substitution we get an arithmetic expression with the changed order of calculation because of different priorities of the operations.

Let's consider the following example. Say, we declared such a #define construction:

\#define sum x + y

and further in the program the expression "2 \* sum" is calculated. After macro substitution is performed we get "2 \* x + y", instead of intuitively expected "2 \* (x + y)".

Let's call the situation "suspicious", if after the macro substitution the order of calculation changes, falling outside the bounds of some macro. Thus, your task is to find out by the given set of #define definitions and the given expression if this expression is suspicious or not.

Let's speak more formally. We should perform an ordinary macros substitution in the given expression. Moreover, we should perform a "safe" macros substitution in the expression, putting in brackets each macro value; after this, guided by arithmetic rules of brackets expansion, we can omit some of the brackets. If there exist a way to get an expression, absolutely coinciding with the expression that is the result of an ordinary substitution (character-by-character, but ignoring spaces), then this expression and the macros system are called correct, otherwise — suspicious.

Note that we consider the "/" operation as the usual mathematical division, not the integer division like in C/C++. That's why, for example, in the expression "a\*(b/c)" we can omit brackets to get the expression "a\*b/c".

## 样例 #1

### 输入

```
1
#define sum x + y
1 * sum
```

### 输出

```
Suspicious
```

## 样例 #2

### 输入

```
1
#define sum  (x + y)
sum - sum
```

### 输出

```
OK
```

## 样例 #3

### 输入

```
4
#define sum  x + y
#define mul  a * b
#define div  a / b
#define expr sum + mul * div * mul
expr
```

### 输出

```
OK
```

## 样例 #4

### 输入

```
3
#define SumSafe   (a+b)
#define DivUnsafe  a/b
#define DenominatorUnsafe  a*b
((SumSafe) + DivUnsafe/DivUnsafe + x/DenominatorUnsafe)
```

### 输出

```
Suspicious
```

# 题解

## 作者：PHarr (赞：14)

本题按照我写题的全过程再写

首先看到题面，我知道要处理运算优先级的问题

所以对于宏定义中的每个运算我开一个$map$分别记录他的加减号，乘除号时候被括号括起来

在表达式中错误情况有三种

1.  前面是减号或乘除号，但后面的宏定义所有的加减没有被括起来
2.  前面是除号，但后面宏定义所有的乘除号没有被括起来
3.  前面是加减号没有被括起来的宏定义，后面是乘除号

当我们遍历到运算符时查看上一个相邻的时表达式还是宏定义，若是宏定义检查3

当我们遍历到宏定义时查看上一个相邻的是否是运算符，若是运算符检查1，2

然后就是处理括号的问题

我们对于括号的情况进行递归判断就好，若左括号递归到下一层，若右括号回溯到上一层

在计算表达式时，只要发现错误无论在那一层直接输出结果并`exit(0)`

然后我发现表达式中出现了变量（是字母，但并不是宏定义）

```
1
#define k ( a + b )
v/k
```



由于我用的是$map$，所以一旦遍历到字母我就利用$find()$函数判断是否是宏定义，如果是个变量就当作数字处理

然后还会有宏定义套宏定义的形式

```
#define sum x + y
#define mul a * sum
```

处理方法和表达式类似，要注意括号的形式

```
#define sum x + y 
#define mul a * ( sum )
```

此时递归操作比较困难，我采用了四个变量`aa,bb,cc,dd`分别表示上一个操作符是什么，判断即可

所以出现了第四种错误

4.  宏定义本身是错误的

但是会有这种情况

```
2
#define sum x + y
#define mul x * sum
sum + sum
```

本身没有调用错误的宏定义，所以对于每个宏定义，我在用一个$map$储存这个宏定义时候是正确的，在计算表达式的时候，顺便检查宏定义时候是正确的

然后本题还有些坑点

1.  `#  define    s+y`这类的有多余的空格所以不能从第$8$个位置直接开始运算，要逐一遍历
2.  `n=0`这种情况特判即可

```cpp
#include <bits/stdc++.h>
#define PBB pair< bool , bool >
#define F first 
#define S second
#define NO ("Suspicious")
#define STOP {puts(NO) , exit(0);}
using namespace std;


int n , bra , len;
string s , name , null;
map< string , PBB > def;
map< string , bool > vis; 

inline int work(int star )
{
	bool mul , add , del , dive , expr ; mul = add = del = dive = expr = 0;
	for( register int i = star , t ; i < len ; i ++ )
	{
		if( s[i] == ')' ) return i;
		if( s[i] == '(' ) { i = work( i + 1 ); add = del = dive = mul = 0; continue;}
		if( s[i] == ' ' ) continue ;
		if( s[i] >= '0' && s[i] <= '9' ) { add = del = dive = mul = 0; continue; }
		if( s[i] == '+' ) { add = 1 , expr = 0; continue; }
		if( s[i] == '-' ) { del = 1 , expr = 0; continue; }
		if( s[i] == '*' )
		{
			if( expr && !def[name].F ) STOP;
			mul = 1 , expr = 0;
			continue;
		}
		if( s[i] == '/' )
		{
			if( expr && ( !def[name].F  ) ) STOP;
			dive = 1 , expr = 0;
			continue;
		}
		
		name = null;
		if( !expr ) name = null ;
		while( s[i] != ' ' && s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/' && s[i] != ')' && s[i]!= '(' && i < len) name += s[i] , i ++ ; i--;
		
		if( def.find(name) == def.end() )
		{
			add = del = mul = dive = 0;
			
			continue;
		}
		if( !vis[name] ) STOP;
		expr = 1;
		if( del && !def[name].F ) STOP;
		if( ( mul || dive ) && !	def[name].F) STOP;
		if( dive && !def[name].S ) STOP;
		add = del = mul = dive = 0;
	}
	return 0;
}

int main()
{
	cin >> n;
	if( n == 0 ) puts("OK") , exit(0);
	getline( cin , s );
	bool add , mul , aa , bb , cc , dd , ac ;
	string cur;
	for( register int t , l ; n ; n -- )
	{
		getline( cin , s ) , len = s.size();
		l = 0;
		while( s[l] != 'd') l ++;
		l += 6;
		while( s[l] == ' ' ) l ++;
		t = l;
		while( s[t] != ' ' ) t ++;
		name = s.substr( l , t - l ) , add = 1 , mul = 1;
		aa = bb = cc = dd = 0 , ac = 1 ;
		for( t ++ ; t < len ; t ++ )
		{
			if( s[t] == '(' ) { bra ++; aa = bb = cc = dd = 0; continue; }
			if( s[t] == ')' ) { bra --; aa = bb = cc = dd = 0; continue; }
			if( s[t] == '+' ) aa = 1 , bb = cc = dd = 0;
			if( s[t] == '-' ) bb = 1 , aa = cc = dd = 0;
			if( s[t] == '*' ) cc = 1 , aa = bb = dd = 0;
			if( s[t] == '/' ) dd = 1 , aa = bb = cc = 0;
			if( !bra && ( s[t] == '+' || s[t] == '-' ) ) add = 0;
			if( !bra && ( s[t] == '*' || s[t] == '/' ) ) mul = 0;
			if( s[t] >= '0' && s[t] <= '9' ) aa = bb = cc = dd = 0;
			if( ( s[t] >= 'a' && s[t] <= 'z' ) || ( s[t] >= 'A' && s[t] <= 'Z' ) )
			{
				cur = null;
				while(s[t] != ' ' && s[t] != '+' && s[t] != '-' && s[t] != '*' && s[t] != '/' && s[t] != '(' && s[t] != ')' && t < len ) cur += s[t] , t ++;
				t -- ;
				if( def.find( cur ) != def.end() )
				{
					if( ( bb || cc || dd ) && !def[cur].F ) ac = 0;
					if( !vis[cur] ) ac = 0; 
					if( !bra && def[cur].F ) add = 0;
					if( !bra && def[cur].S ) mul = 0;
				}
			}
		}
		def.insert( { name , { add , mul } } );
		vis.insert( { name , ac } );
	}
	
	getline( cin , s ) , len = s.size();
	work(0);
	puts("OK");
	return 0;
}
```



---

## 作者：xlqs23 (赞：9)

**题意**

给你一些宏定义，判断最后的式子是否能正确表达原来的意思

**思路**

首先，对读入进行处理，可以忽略#include，运用1至2次$cin$进行这一步，然后再cin一次读到宏定义名字，再$getline$得到宏定义表达式，进行一下去空格。然后对每一个宏定义先进行判断，分为4种情况：

1、完全正确

2、完全不正确

3、只在与乘除相连或出现在减后的情况下不正确

4、只在出现在除后的情况下不正确。

我们找到一个宏定义表达式的最后一个运算符（从右向左找加减，没有加减再从右向左找乘除），把式子分为两部分，如果两部分都是第2种情况，那整个式子也是第2种，除此以外，如果运算符为加，整个式子会是第3种情况，如果运算符为减，则仅当右部是3时，整体为2，否则整体为3，如果运算符为乘，则在两部分至少有一个为3时，整体为2，否则整体为3，如果运算符为除，则在两部分至少有一个为3或右部为4时，整体为2，否则整体为3。最后考虑一下没有运算符的情况，这种情况字符串是变量或常量，如果两端有括号，先去括号，然后检查一下前边的宏定义里有没有这个字符串，有的话这个字符串的情况就已知了，没有的话就是1。最后对最后那个式子进行整体判断，如果是2，就是不正确，否则就是正确。

**代码**
```cpp
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <map>
using namespace std;
map<string,int> mp;
string s2;
string s3;
int judge(string s,int l,int r)
{
    int add=0,x,y,f=0;
    string ss;
    for(int i=r;i>=l;i--)
    {
        if(s[i]=='(')
            add++;
        else if(s[i]==')')
            add--;
        else if(add==0&&f==0&&(s[i]=='*'||s[i]=='/'))
            f=i;
        else if(add==0&&(s[i]=='+'||s[i]=='-'))
        {
            x=judge(s,l,i-1);
            y=judge(s,i+1,r);
            if(x==2||y==2)
                return 2;
            if(s[i]=='+')
                return 3;
            else if(s[i]=='-')
            {
                if(y==3)
                    return 2;
                else return 3;
            }
        }
    }
    if(f!=0)
    {
        x=judge(s,l,f-1);
        y=judge(s,f+1,r);
        if(x==2||y==2)
            return 2;
        if(s[f]=='*')
        {
            if(x==3||y==3)
                return 2;
            else return 4;
        }
        else if(s[f]=='/')
        {
            if(x==3||y==3||y==4)
                return 2;
            else return 4;
        }
    }
    else if(s[l]=='('&&s[r]==')')
    {
        if(judge(s,l+1,r-1)==2)
            return 2;
        else return 1;
    }
    else
    {
        ss="";
        for(int i=l;i<=r;i++)
            ss+=s[i];
        if(mp[ss]!=0)
            return mp[ss];
        else return 1;
    }
}
int main()
{
    int n;
    string s;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>s;
        if(s[s.length()-1]=='#')
            cin>>s;
        cin>>s;
        getline(cin,s2);
        s3="";
        for(int j=0;j<s2.length();j++)
            if(s2[j]!=' ')
                s3+=s2[j];
        mp[s]=judge(s3,0,s3.length()-1);
    }
    getline(cin,s2);
    s3="";
    for(int j=0;j<s2.length();j++)
        if(s2[j]!=' ')
            s3+=s2[j];
    if(judge(s3,0,s3.length()-1)!=2)
        cout<<"OK"<<endl;
    else cout<<"Suspicious"<<endl;
    return 0;
}

---

## 作者：kczno1 (赞：6)

考虑什么时候会$Suspicious$  
如果是$l/r$，  当$l$有$+or-$或$r$有$+or-or*or/$就会出错。  
(有指的是最外一层)  
其他同理。  
所以只要$dp$，记录最外一层是否存在$+or-,*or/$即可。  
预处理每个左括号对应的右括号。  
复杂度线性。  
读入有点麻烦。
```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
const int N=100+5;
map<string,int>dp;//1:+- 2:*/
string ns,s;int n;
int nex[N];
int is[256];
int merge(int l,int r,int t)
{
	if(l==-1||r==-1)return -1;
	if(t=='+')
	{
	}
	else
	if(t=='-')
	{
		if(r&1)return -1;
	}
	else
	if(t=='*')
	{
		if((l&1)||(r&1))return -1;
	}
	else
	{
		if((l&1)||r)return -1;
	}
//	printf("is=%d %d\n",is[t],l|r|(1<<is[t]-1));
	return l|r|(1<<is[t]-1);
}
int solve(int l,int r)
{
//	printf("%d %d %c %c\n",l,r,s[l],s[r]);
//	cout<<s<<endl;
	if(l<r&&nex[l]==r)
	{
		int ans=solve(l+1,r-1);
		if(ans==-1)return -1;
		return 0;
	}
	vector<int>st;
	for(int i=l;;)
	{	
		int v;
		if(!nex[i])
		{
			string ns;
			while(i<=r&&!is[s[i]])
			{
				ns.push_back(s[i]);
				++i;
			}
			if(dp.count(ns))v=dp[ns];
			else v=0;
		}
		else
		{
			v=solve(i,nex[i]);
			i=nex[i]+1;
		}
		if(!st.empty()&&is[st.back()]==2)
		{
			int t=st.back();
			st.pop_back();
			st.back()=merge(st.back(),v,t);
		}
		else
		{
			st.push_back(v);
		}
		if(i>r)break;
		st.push_back(s[i++]);
	}
	auto it=st.begin();
	while(it!=st.end()-1)
	{
		it+=2;
		*it=merge(*(it-2),*it,*(it-1));
	}
//	rep(i,l,r)printf("%c",s[i]);
//	printf(" %d\n",*it);
	return *it;
}
int get()
{
	n=0;
	s.clear();
	getline(cin,ns);
	for(auto i:ns)
	{
		if(i!=' ')s.push_back(i);
	}
	n=s.size();
	memset(nex,0,sizeof(nex));
	//cout<<s<<endl;
	static vector<int>st;
	per(i,n-1,0)
	if(s[i]==')')st.push_back(i);
	else 
	if(s[i]=='('){nex[i]=st.back();st.pop_back();} 
//	cout<<s<<endl;
	return solve(0,n-1);	
}

int main()
{
	freopen("1.in","r",stdin);
	is['+']=is['-']=1;
	is['*']=is['/']=2;
	int tt;
	cin>>tt;
	while(tt--)
	{
		int len=0;
		cin>>ns;
		while(/*cout<<ns<<endl,*/len+=ns.size(),len<7)cin>>ns;
		cin>>ns;
		dp[ns]=get();
	}
	if(get()!=-1)puts("OK");
	else puts("Suspicious");
}

```

---

## 作者：DennisPraet (赞：4)

[题目链接](http://codeforces.com/problemset/problem/7/E)
#### 题目大意
给你N个宏的定义（也就是#define XXX XXX）
这些宏包含一些变量和运算符号（+,-,*,/）。

再给出一个由这些宏组成的程序，让你判断这个程序是否有“危险”（也就是说会产生一些混乱）
比如样例4：

```cpp
3

#define SumSafe   (a+b)

#define DivUnsafe  a/b

#define DenominatorUnsafe  a*b

((SumSafe) + DivUnsafe/DivUnsafe + x/DenominatorUnsafe)
```

将这个程序翻译过来，就是
(((a+b))+a/b/a/b+x/a*b)

在这个程序中，a/b/a/b和x/a*b可能会出现错误，这是由运算符之间的关系造成的。

我们可以观察一下四种运算，可以发现情况可以分为四种。

1. 完全正确

1. 完全不正确

1. 在减号后或与乘除相连时出错

1. 在除号后出错

我们找到一个宏定义表达式的优先级最后运算符，把式子分为两部分，如果两部分都是第2种情况，那整个式子也是第2种。

如果运算符为加，整个式子会是第3种情况。

如果运算符为减，则仅当右部是第3种情况时，整体为第2种情况，否则整体为第3种情况。

如果运算符为乘，则在两部分至少有一个为第3种情况时，整体为第2种情况，否则整体为第3种情况。

如果运算符为除，则在两部分至少有一个为第3种情况或右部为第4种情况时，整体为第2种情况，否则整体为第3种情况。

如果两端有括号，先去括号，判断括号中的表达式的种类，没有的话就是第一种情况。

最后对最后那个程序进行判断，如果是第2种情况，就是不正确，否则就是正确

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
map<string,int> mapp;
int n,m;
string s,s1,s2,ss,s3;
int judge(int l,int r)
{
	int flag=0,pos=0;
	for (int i=r;i>=l;i--)
	{
		if (s[i]=='(') flag++;
		if (s[i]==')') flag--;
		if (pos==0&&flag==0&&(s[i]=='*'||s[i]=='/')) pos=i;
		if (flag==0&&(s[i]=='+'||s[i]=='-'))
		{
			int t1=judge(l,i-1),t2=judge(i+1,r);
			if (t1==2||t2==2) return 2;
			if (s[i]=='+') return 3;
			if (s[i]=='-'&&t2==3) return 2;
			if (s[i]=='-') return 3;
		}
	}
	if (pos!=0)
	{
		int t1=judge(l,pos-1),t2=judge(pos+1,r);
		if (t1==2||t2==2) return 2;
		if (s[pos]=='*'&&(t1==3||t2==3)) return 2;
		if (s[pos]=='*') return 4;
		if (s[pos]=='/'&&(t1==3||t2==3||t2==4)) return 2;
		if (s[pos]=='/') return 4;
	}
	else if (s[l]=='('&&s[r]==')')
	{
		if (judge(l+1,r-1)==2) return 2;
		else return 1;
	}
	else
	{
	  ss="";
	  for (int i=l;i<=r;i++)
      ss+=s[i];
      if (mapp[ss]!=0) return mapp[ss];
      else return 1;
    }
}
int main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		int tot=0;
		int t1=0,t2=0;
		int j=1;
		cin>>s1;
		if (s1[s1.length()-1]=='#') cin>>s1;
		cin>>s1;
		getline(cin,s2);
		s="";
		for (int j=0;j<=s2.length()-1;j++)
	    if (s2[j]!=' ') s+=s2[j];
		int ans=judge(0,s.length()-1);
		mapp[s1]=ans;
	}
	int tot=0;
	s3="";
	s="";
	getline(cin,s3);
	for (int i=0;i<s3.length();i++)
    if (s3[i]!=' ') s+=s3[i];
	int ans=judge(0,s.length()-1);
	if (ans!=2) printf("OK\n");
	else printf("Suspicious\n");
	return 0;
} 
```

---

## 作者：MCRS_lizi (赞：3)

[题目传送门CF7E](https://www.luogu.com.cn/problem/CF7E)
# 题目大意
给你一些宏（```#define```）定义，判断给定的表达式中每个变量是否都能被当做一个整体运算。

举个例子:
```c
#define sum x+y
2*sum
```
在这个式子中，原本要表达的意义是 $2*(x+y)$ ,可是经过宏定义后变成了 $2*x+y$ ，表达式意义发生了改变，现在我们就要判断表达式意义会不会发生这样的改变，会就输出Suspicious，否则输出OK。

# 题目分析
首先，在输入的时候要对每个宏定义进行预处理，处理后会有一下四种情况：

$1$ 、整个表达式为一个整体（如用括号括起来整个表达式或者整个表达式为单个变量或数字）我们称之为 $0$ 级表达式；

$2$ 、表达式括号外部存在 $+$ 或者 $-$ ，我们称之为$1$级表达式；

$3$ 、表达式括号外部只存在 $*$ 或者 $/$ ,我们称之为$2$级表达式；

$4$ 、表达式本身不符合题意，我们称之为不合法的表达式；

在进行预处理的时候，由于每个宏定义会用到前面的宏，所以这四种情况都是有可能的，如果某个表达式调用了不合法的宏定义，那么这个表达式一定是不合法的，所以我们主要分析前面三种情况。

如果一个表达式是 $0$ 级的，那么无论如何对它进行调用，都不会产生不合法的情况。

如果一个表达式是 $1$ 级的，那么我们不难发现，当它前面有 $*$ 、$/$ 、 $-$
三种符号或者后面有 $*$ 、$/$ 两种运算符号的时候，就会发生不合法的现象。

如果一个表达式是 $2$ 级的，那么当且仅当它前面有 $/$ 的时候会发生不合法现象（例如 $a/b*c$ 和 $a/(b*c)$ ）是不一样的。

那么接下来事情就好办了许多，我们只需要通过模拟来判断每个宏定义中是否用到之前的宏定义，再来判断其等级与是否合法就可以了。

同样的，用这种方式也可以判断最终的表达式是否合法。
# 实际操作
这里有许多注意事项，本人踩了一堆坑才过的，我会一一给你们列举。

首先我们在输入的时候要将前面的```#define```去掉，但是千万不要通过直接输入一个字符串来实现，因为可能会有这样的测试数据：
```c
# define sum a+b+c
```
所以要判断输入的有效字符个数。

接下来可以直接输入一个字符串，再用```getline```解决掉接下来的内容。

输入后我们需要定义一个 ```answer(int l,int r,int ce)``` 函数，来判断序号为$ce$的字符串从$l$到$r$是否合法，我们可以传址调用一个参数来传输表达式级别。

当遇到左括号时，先确定与它相匹配的右括号，注意，右括号并不是离左括号最近或最远的那个，需要用计数的方式进行判断，大致思路就是遇到左括号就压入栈，遇到右括号就弹出一个左括号与它匹配。

然后递归判断括号内的内容是否合法。

最后再调用函数判断最终的表达式是否合法。

还有，判断与当前表达式相邻的表达式要省去空格，或者你可以在读入时就先去掉空格。
#  _Code_ 
```c
#include<bits/stdc++.h>
using namespace std;
int n;
bool fake[1001];//标记宏定义是否合法
struct point//用结构体存之前每个宏定义的信息
{
	string x,y;
	int lenx,leny,lev;
}a[1001];
string f;
bool check(int u,int v,int lu,int ru,int lv,int rv)//判断该区间是否调用之前宏定义
{
	if(ru>=a[u].leny)
	{
		return 0;
	}
	if(ru-lu!=rv-lv)
	{
		return 0;
	}
	for(int i=lu;i<=ru;i++)
	{
		if(a[u].y[i]!=a[v].x[i+lv-lu])
		{
			return 0;
		}
	}
	return 1;
}
bool answer(int ce,int l,int r,int &cnt,bool flag)//检查等级与是否合法
{
	for(int i=l;i<=r;i++)
	{
		if(a[ce].y[i]=='(')//处理左括号
		{
			int s=i,num=1;
			i++;
			while(num>0)//计数寻找匹配的右括号
			{
				if(a[ce].y[i]=='(')
				{
					num++;
				}
				else if(a[ce].y[i]==')')
				{
					num--;
				}
				i++;
			}
			i--;
			if(!answer(ce,s+1,i-1,cnt,0))
			{
				return 0;
			}
		}
		else
		{
			for(int j=1;j<ce;j++)
			{
				if(check(ce,j,i,i+a[j].lenx-1,0,a[j].lenx-1))
				{
					if(fake[j])//如果调用不合法的表达式绝对不合法
					{
						return 0;
					}
					for(int k=i-1;k>=l;k--)//查找左右两边运算符
					{
						if(a[ce].y[k]==' ')
						{
							continue;
						}
						if(a[j].lev==1&&(a[ce].y[k]=='*'||a[ce].y[k]=='/'||a[ce].y[k]=='-'))
						{
							return 0;
						}
						else if(a[j].lev==2&&(a[ce].y[k]=='/'))
						{
							return 0;
						}
						break;
					}
					for(int k=i+a[j].lenx;k<=r;k++)
					{
						if(a[ce].y[k]==' ')
						{
							continue;
						}
						if(a[j].lev==1&&(a[ce].y[k]=='*'||a[ce].y[k]=='/'))
						{
							return 0;
						}
						break;
					}
				}
			}
			if(flag)//判断等级
			{
				if(a[ce].y[i]=='+'||a[ce].y[i]=='-')
				{
					cnt=1;
				}
				else if(a[ce].y[i]=='*'||a[ce].y[i]=='/')
				{
					if(cnt==0)
					{
						cnt=2;
					}
				}
			}
		}
	}
	return 1;//大难不死，必是合法
}
void gettmp()//读入#define
{
	int cnt=0;
	char ch;
	while(cnt<7)
	{
		cin>>ch;
		cnt++;
	}
}
void getdfn(int ce)//读入第ce个宏定义
{
	gettmp();
	cin>>a[ce].x;
	getline(cin,a[ce].y);
	a[ce].lenx=a[ce].x.length();
	a[ce].leny=a[ce].y.length();
	int cnt=0;
	if(!answer(ce,0,a[ce].leny-1,cnt,1))//判断是否合法
	{
		fake[ce]=1;
	}
	a[ce].lev=cnt;//传入等级
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		getdfn(i);
	}
	getline(cin,f);
	a[++n].y=f;
	a[n].leny=f.length();
	int tmp;
	if(answer(n,0,a[n].leny-1,tmp,0))//检查最终表达式
	{
		cout<<"OK";
	}
	else
	{
		cout<<"Suspicious";
	}
 	return 0;
}//码完收工
```
# 总结
题目难度不大，但很不好调，在此感谢[@UnyieldingTrilobite](https://www.luogu.com.cn/user/250637)为我提供的测试数据（不然真调不出来）。

完结撒花！！！


---

## 作者：李34 (赞：3)

原题链接[CF7E Defining Macros](https://www.luogu.com.cn/problem/CF7E)


~~这个黑题感觉好像不是很黑~~

## 1.理解题意

> 输入 **n** 个 **#define** 语句，然后给一个表达式，让你判断该表达式是不是 **'Suspicious'** 的。 **'Suspicious'** 的定义是某一个 **#define** 定义的东西被拆开来了。

> 如：
> 

```
#define haha ha+ha
#define p haha-haha
p
```

> 这是 **'Suspicious'** 的，因为第二个haha被拆开了。本来是：

```
 (ha+ha)-(ha+ha)
= ha+ha - ha-ha

```

> 现在是：

```
ha+ha-ha+ha
```





## 2.思路

> 对于一个表达式，在括号外面的最低级的运算符就是该表达式的优先级。比如说 $( x + y ) * z / p$ 的优先级就是 $ * $ 或者 $ / $ 。

> 我们把全在运算符括号里面（或者没有运算符）的表达式记为 $0$ 级， $+$ 或者 $-$ 为 $1$ 级， $*$ 或 $/$ 为 $2$ 级。

> 不难发现， $0$ 级的表达式是不可能被拆分的。

> $1$ 级的表达式的前面有 $*$ 或 $/$ 或 $-$ 会被干掉  或者  后面有 $*$ 或 $/$ 会被干掉。

> $2$ 级的表达式的前面有 $/$ 才会被干掉。

> **注意：这里的“有”指直接相邻。**

> 所以我们可以先 **预处理出所有表达式的优先级** ，然后我们惊奇地发现，所有表达式之间的调用关系为 **一张有向无环图！** 

> 所以我们可以从调用方到被调用方都连上边，然后愉快地**DFS** 。

> 然后就好了。

## 3.全解代码

```cpp
#include<cstdio>
#include<string>
#include<map>
#include<vector>
using namespace std;
const int N=110;
inline bool isCH(char ch){ return ch>='A'&&ch<='Z'||ch>='a'&&ch<='z'; }//判断是否为字母 
inline int read()//输入一个数字 
{
	int num=0;char ch=getchar();
	while (ch>'9'||ch<'0') ch=getchar();
	while (ch<='9'&&ch>='0') num=(num<<1)+(num<<3)+(ch^48),ch=getchar();
	return num;
}
inline void getdef()//把没用的#define过掉 
{
	char ch=getchar();
	while (ch!='#') ch=getchar();
	while (ch!='d') ch=getchar();
	while (ch>='a'&&ch<='z') ch=getchar();
	return;
}
inline string getS()//输入一个连续的字母串 
{
	char ch=getchar();string s="";
	while (ch==' ') ch=getchar();
	while (ch!=' ')	s+=ch,ch=getchar();
	return s;
}
inline string getL()//输入整行 
{
	char ch=getchar();string s="";
	while (ch!='\n'&&ch!=EOF)
	{
		if (ch!=' ') s+=ch;//去除空格 
		ch=getchar();
	}
	return s;
}
inline void put(string s){ for(int i=0;i<s.length();++i)putchar(s[i]);puts(""); }//输出一个字符串（供调试用） 

//以上为手写输入输出 

int n;//n
string op;//最后的表达式 
string A[N],B[N];//#define A B
map<string,int> mp;//记录A是几号表达式 
int C[N];//分级：0完全整体  1+-  2*/ 
vector<int> G[N];//图：G[i][j] 表示i的第j个调用点 
vector<char> L[N],R[N];//图：L[i][j] 表示i的第j个调用点左边的符号, R是右边的 
bool vis[N];//有没有到过该节点 
bool safe[N];//该节点是否安全 
inline void Dfs(int cur)//DFS
{
	for (int i=0;i<G[cur].size();++i)//遍历所有子节点 
	{
		int to=G[cur][i];char le=L[cur][i],ri=R[cur][i];//to指向的点，le左边的符号，ri右边的符号 
		if (!vis[to])//如果没有去过这个点就往下走 
		{
			vis[to]=1;
			Dfs(to);
		}
		if (C[to]==1)//如果子节点级别为1 
			if (le=='*'||le=='/'||le=='-'||ri=='*'||ri=='/')
				safe[cur]=0;//如果前面有*/-或后面有*/那当前节点不安全 
		else if (C[to]==2)//如果级别为2 
			if (le=='/') safe[cur]=0;//前面有/不安全 
		safe[cur]&=safe[to];//只要有一个子节点不安全就坏事 
	}
	return;
}
int main()
{
	n=read();//输入 
	for (int i=1;i<=n;++i)
	{
		getdef();//去除#define 
		A[i]=getS();//读入A 
		B[i]=getL();//读入B 
		mp[A[i]]=i;//记录A的编号 
		int inb=0;//在第几层括号 
		for (int j=0;j<B[i].length();++j)
		{
			if (B[i][j]=='(') ++inb;//如果遇到左括号加深一层 
			else if (B[i][j]==')') --inb;//如果遇到有括号降一层 
			else if (inb==0)//如果在最外层 
			{
				if (B[i][j]=='+'||B[i][j]=='-') C[i]=1;//如果是+-，那么是1级 
				else if (!C[i]&&(B[i][j]=='*'||B[i][j]=='/')) C[i]=2;//如果是*/，那么是2级 
			}//同时有+-和*/算+- 
		}//不然默认是0级 
	}
	//我不知道这算不算一个点，在C++中前面的#define也可以调用后面的#define 
	for (int i=1;i<=n;++i)
	{
		for (int j=0;j<B[i].length();++j) 
		{//找子表达式 
			if (!isCH(B[i][j])) continue; //表达式全是字母，所以不是字母就continue
			string s="";int now=0;
			int k=j;//从j往后找 
			while (k<B[i].length()&&isCH(B[i][k])) s+=B[i][k],++k;
			if (mp[s])//如果找出的字串是定义过的，那就连边 
			{
				L[i].push_back(j?B[i][j-1]:'#');//防止越界随便搞了一个字符 
				R[i].push_back(k<B[i].length()?B[i][k]:'#');//L和R分别是左边的运算符和右边的运算符 
				G[i].push_back(mp[s]);//像该节点连边 
			}
			j=k;
		}
		safe[i]=1;//初始设safe为1 
	}
	for (int i=1;i<=n;++i)
		if (!vis[i]) vis[i]=1,Dfs(i);//如果没有去过就DFS 
	op=getL();//输入最后的表达式 
	for (int j=0;j<op.length();++j)
	{//和之前那个循环很像（我是复制的） 
		if (!isCH(op[j])) continue;
		string s="";int now=0;
		int k=j;
		while (k<op.length()&&isCH(op[k])) s+=op[k],++k;
		if (mp[s])//同上 
		{
			if (!safe[mp[s]])//如果这个子表达式本生就不安全，直接输出 
			{
				puts("Suspicious");
				return 0;
			}
			else if (C[mp[s]]==2&&j&&op[j-1]=='/')//如果该表达式为2级，左边是/，也不安全 
			{
				puts("Suspicious");
				return 0;
			}
			else if (C[mp[s]]==1
				  &&(j&&(op[j-1]=='/'||op[j-1]=='*'||op[j-1]=='-')
				   ||k<op.length()&&(op[k]=='/'||op[k]=='*')))
			{//同上，如果表达式为1级，左边是/*-或右边是/*就不安全 
				puts("Suspicious");
				return 0;
			}
		}
		j=k;
	}
	puts("OK");//经历了以上一切还活着，输出OK 
	return 0;
}

```


---

## 作者：Cry_For_theMoon (赞：2)

[传送门](https://codeforces.com/contest/7/problem/E)

~~感觉这个2600评黑虚高~~

题意非常恶心，可以简化一下：

对于给定的表达式，判断对其中每个宏套上括号后运算的结果和不套是否相同。是则称其为合法，不是则不合法，判断表达式是否合法。

梳理得到，对于五种运算（加减乘除和括号），它们结果合法的必要条件是参与运算的所有表达式都合法，除此之外，注意到还有一些特殊条件：

- 对于加法和括号而言，只要参与运算的两个表达式合法结果也一定合法。

- 对于减法 $expr_1-expr_2$ 而言，结果合法还得满足 $expr_2$ 的最后一步是乘法/除法/括号运算。

- 对于乘法 $expr_1\times expr_2$ 而言，结果合法还得满足 $expr_1$ 和 $expr_2$ 的最后一步是乘法/除法/括号运算。

- 对于除法 $expr1/expr2$ 而言，结果合法还得满足 $expr_1$ 的最后一步是乘法/除法/括号运算，$expr_2$ 的最后一步是括号运算。

所以我们对一个表达式，可以按照其作用大小分成四类：

1. 完全合法。该类表达式可以参加任何运算

2. 减乘合法。该类表达式可以充当被减数，乘数，被除数，但不能作被除数

3. 加法合法。该类表达式只能作加数，被减数或者套括号。

4. 不合法。即本身不合法的表达式

所以前三类都是对“合法”的表达式的作用的进一步细分。接下来，考虑一个表达式最后一步运算对状态造成的影响，设 $f(x)$ 为表达式 $x$ 的类别，此时很容易推出：

$f(expr)<=3,f(\,(expr)\,)=1$，否则 $f(\,(expr)\,)=4$.

$f(expr_1),f(expr_2)<=3,f(\,expr_1+expr_2\,)=3$，否则 $f(\,expr_1+expr_2\,)=4$.

$f(expr_1)<=3,f(expr_2)<=2,f(\,expr_1-expr_2\,)=3$，否则 $f(\,expr_1-expr_2\,)=4$.

$f(expr_1),f(expr_2)<=2,f(\,expr_1\times expr_2\,)=2,$ 否则 $f(\,expr_1 \times expr_2\,)=4$.

$f(expr_1)<=2,f(expr_2)=1,f(\,expr_1/expr_2\,)=2,$ 否则 $f(\,expr_1/expr_2\,)=4$.

此时我们使用递归计算即可（我不知道为啥写的时候记忆化了然而没有什么用）

代码中一个值得注意的点是，不是表达式两侧分别是左右括号就一定整体被括起来，可能是()()的形式。不注意这里大概会在 #10 或者 #61 处 WA.

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define mapit map<int,int>::iterator
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=110;
il int Rev(char ch){
	if(ch>='a'&&ch<='z')return ch-'a';
	else return ch-'A'+26;
}
struct Trie{
	//得到每个标识符编号 
	int ch[MAXN*MAXN][52],pos[MAXN*MAXN],vis[MAXN*MAXN],tot;
	void Insert(const string& s,int idx){
		int u=0;
		for(int i=0,len=s.length();i<len;i++){
			if(!ch[u][Rev(s[i])])ch[u][Rev(s[i])]=++tot;
			u=ch[u][Rev(s[i])];
		} 
		pos[u]=idx;
	}
	int Find(const string& s){
		int u=0;
		for(int i=0,len=s.length();i<len;i++){
			if(!ch[u][Rev(s[i])])return -1;
			u=ch[u][Rev(s[i])];
		} 
		return pos[u];
	}
	void Reset(int u,int v){
		vis[u]=v;
	}
	int Get(int u){
		return vis[u];
	}
}trie;
struct Expr{
	string name; //标识符
	string exp; //表达式 
}expr[MAXN];
int n,f[MAXN][MAXN];
string tmp,e;
char ch;
int dp(const string& s,int L,int R){
	//计算s[L...R]状态 
	//判断是否为单元素
	if(f[L][R])return f[L][R];
	int flag=1,flag2=1,cnt=0,sum=0,pos=0;
	string tmp;tmp.clear();
	rep(j,L,R){tmp.append(1,s[j]);if(!isdigit(s[j]) && !islower(s[j]) && !isupper(s[j]))flag=0;}
	rep(j,L,R){if(!islower(s[j]) && !isupper(s[j]))flag2=0;}
	if(flag2 && trie.Find(tmp)!=-1){return f[L][R]=trie.Get(trie.Find(tmp));} //曾经出现的宏  
	if(flag){return f[L][R]=1;} //单独数字/变量
	//括号 
	rep(j,L+1,R-1){
		if(s[j]=='('){
			sum++;
		}
		else if(s[j]==')'){
			sum--;
		}
		if(sum<0)break;
	}
	if(sum==0 && s[L]=='(' & s[R]==')'){
		if(dp(s,L+1,R-1)!=4)return f[L][R]=1;
		return f[L][R]=4;
	}
	//寻找最后参与运算的字符
	sum=0;
	rep(j,L,R){
		if(s[j]=='(')sum++;
		else if(s[j]==')')sum--;
		else if(s[j]=='+' || s[j]=='-' || s[j]=='*' || s[j]=='/'){
			if(!sum){
				if(!pos)pos=j;
				else if(s[j]=='+' || s[j]=='-')pos=j;
				else if(s[pos]=='*' || s[pos]=='/')pos=j;
			}
		}
	}
	int lv=dp(s,L,pos-1),rv=dp(s,pos+1,R);
	if(s[pos]=='+'){
		if(lv<=3 && rv<=3)return f[L][R]=3;
		else return f[L][R]=4;
	}else if(s[pos]=='-'){
		if(lv<=3 && rv<=2)return f[L][R]=3;
		else return f[L][R]=4;
	}else if(s[pos]=='*'){
		if(lv<=2 && rv<=2)return f[L][R]=2;
		else return f[L][R]=4;
	}else if(s[pos]=='/'){
		if(lv<=2 && rv<=1)return f[L][R]=2;
		else return f[L][R]=4;
	}
}
int main(){
	cin>>n;
	rep(i,1,n){
		int cnt=0;
		while(ch=getchar()){
			if((ch=='#') || (ch>='a' && ch<='z'))cnt++;
			if(cnt>=7)break;
		}
		cin>>tmp;expr[i].name=tmp;trie.Insert(tmp,i);
		while((ch=getchar()) && ch!='\n')
			if(ch!=' ')expr[i].exp.append(1,ch);
	}
	while((ch=getchar()) && ch!='\n')if(ch!=' ')e.append(1,ch);
	rep(i,1,n){
		memset(f,0,sizeof f);
		trie.Reset(trie.Find(expr[i].name),dp(expr[i].exp,0,expr[i].exp.length()-1));
	}
	memset(f,0,sizeof f);
	printf("%s\n",(dp(e,0,e.length()-1)!=4)?"OK":"Suspicious");
	return 0;
}
```


---

## 作者：ZLCT (赞：0)

# CF7E Defining Macros
## 题目翻译
给定 $n$ 个宏定义，求一个表达式是否安全。\
一个表达式安全的定义为所有的宏定义在运算时都作为一个整体（或者说若在每个宏定义外层打括号后不会影响运算）。\
例如 `#define sum x + y` 后若执行 `2 * sum` 则会变成 `2 * x + y`，此时 `x + y` 就不是作为一个整体运算。
## 提前优化掉一步
看了这个题我们应该会很自然地想到如果把最后的表达式看作一个宏定义，那么我们其实只需要实现判断宏定义是否合法即可，这样可以令问题统一化。
## 简化版本1
我们先不要考虑四则运算搭配括号如此复杂的事情，一步步先考虑简单的事情。\
我们假设现在只有 $+-$ 两种运算，那么如何才能合法呢？\
因为我们考虑合法情况容易遗漏，所以我们考虑何时不合法。\
首先若当前是没有宏定义的运算，那么给宏定义打括号不影响当前运算，所以我们只考虑有宏定义参与的情况。\
根据小学知识，加减法只有两种情况需要括号，也就是形如 $a-(b-c)/a-(b+c)$ 的形式。但是为了严谨我们列出如下表格，此处默认宏定义里为 $b\oplus c$ 的形式，外层为 $a\oplus宏$ 的形式。
| 外层符号 | 宏定义符号 | 给宏定义打括号结果 | 不给宏定义打括号结果 |
|------------|----------|--------------------|:---------------------|
| $+$ | $+$ | $a+(b+c)=a+b+c$ | $a+b+c$ |
| $+$ | $-$ | $a+(b-c)=a+b-c$ | $a+b-c$ |
| $-$ | $+$ | $a-(b+c)=a-b-c$ | $a-b+c$ |
| $-$ | $-$ | $a-(b-c)=a-b+c$ | $a-b-c$|

事实证明的确当内层为 $+-$ 时前面只有为 $-$ 才会不合法，那么合法情况就是 $\neg 不合法情况$，也就是前面为 $+$。\
但是这里有一个特殊情况，假设我们 `define sum a`，那么这个宏定义其实就是一个变量，加不加括号没有意义，所以我们需要判断宏定义内是否有符号。\
考虑完前面我们考虑后面的情况。\
事实上我们不需要考虑这种情况，因为如果后面有些值导致不合法，那么在遍历到后面值时会算出来，那我们需要解决的问题就是宏定义的符号问题。\
注意我们现在简化版本还没有括号，只有加减，那么相同级别的运算一定是从左向右算，所以每算出一个结果后可以把它作为新的 $a$ 继续运算，所以我们不需要管宏定义内部的符号。\
这个版本还有最后一个需要注意的问题，我们的宏定义可能包含多个运算，比如 `#define sum = a + b - c`。那根据上面的表格，无论有多少运算，我们不合法情况只与外层符号有关，所以我们依旧不需要管宏定义内部。
## 简化版本2
我们类比加减，现在考虑只有乘除的情况。\
小学学过加减法之间的关系与乘除法之间的关系极为相似，所以我们可以推断此时非法情况。但是为了严谨我们还是打一个表格。
| 外层符号 | 宏定义符号 | 给宏定义打括号结果 | 不给宏定义打括号结果 |
|------------|:-----------|------------------------------------------|-----------------------|
| $\times$ | $\times$ | $a\times(b\times c)=a\times b\times c$ | $a\times b\times c$ |
| $\times$ | $\div$ | $a\times(b\div c)=a\times b\div c$ | $a\times b\div c$ |
| $\div$ | $\times$ | $a\div(b\times c)=a\div b\div c$ | $a\div b\times c$ |
| $\div$ | $\div$ | $a\div(b\div c)=a\div b\times c$ | $a\div b\div c$ |

对比后两项我们发现只有前面是 $\div$ 时才会不合法，那么合法情况就是前面为 $\times$。\
由于乘除法之间也是同级运算，所以我们依然可以从左往右计算认为当前计算的结果是下一个运算的 $a$。而后面符号导致不合法的情况也一定会在后面的计算中算出，并且不合法情况也只由外层符号决定，总之一切同加减法一样。
## 简化版本3
我们考虑只有 $+-()$ 的情况。\
根据运算顺序我们知道有 $()$ 先算 $()$ 里面的，所以我们可以把 $()$ 内看作一个单独的运算区间，这个运算区间内部不受这个括号的干扰，所以可以递归继续判断是否合法。而在括号外部，由于括号已经算完了，所以此时 $()$ 只相当于一个变量，和简化版本1一样运算即可。\
我们来整理一下这个版本，虽然感觉我们对于括号的处理是一堆正确的废话，但是它为我们提供了递归处理括号的优质思想。
## 简化版本4
我们考虑只有 $\times\div()$ 的情况。\
乘除之间的关系在简化版本2中我们发现了与加减之间的关系是相同的，所以我们利用简化版本3的方法，递归计算括号，其余套用简化版本2的方法即可。
## 简化版本5
我们先暂时放下关于括号的讨论，我们假设现在只有 $+-\times\div$ 四则运算的情况。\
在 $+-$ 与 $\times\div$ 之间不再过多赘述，下面来分析其混合运算的情况。\
非宏定义之间的计算我们在简化版本1中已经说明了无论什么运算一定是合法的，所以我们还是只考虑与宏定义之间的运算。\
这个时候因为运算符号的增加，我们已经不是很好“一眼看出”不合法的情况了，所以我们还是做一个表格。
| 外层符号 | 宏定义符号 | 给宏定义打括号结果 | 不给宏定义打括号结果 |
|------------|------------|--------------------|:---------------------|
| $+$ | $+$ | $a+(b+c)=a+b+c$ | $a+b+c$ |
| $+$ | $-$ | $a+(b-c)=a+b-c$ | $a+b-c$ |
| $+$ | $\times$ | $a+(b\times c)=a+b\times c$ | $a+b\times c$ |
| $+$ | $\div$ | $a+(b\div c)=a+b\div c$ | $a+b\div c$ |
| $-$ | $+$ | $a-(b+c)=a-b-c$ | $a-b+c$ |
| $-$ | $-$ | $a-(b-c)=a-b+c$ | $a-b-c$ |
| $-$ | $\times$ | $a-(b\times c)=a-b\times c$ | $a-b\times c$ |
| $-$ | $\div$ | $a-(b\div c)=a-b\div c$ | $a-b\div c$ |
| $\times$ | $+$ | $a\times(b+c)=a\times b+a\times c$ | $a\times b+c$ |
| $\times$ | $-$ | $a\times(b-c)=a\times b-a\times c$ | $a\times b-c$ |
| $\times$ | $\times$ | $a\times(b\times c)=a\times b\times c$ | $a\times b\times c$ |
| $\times$ | $\div$ | $a\times(b\div c)=a\times b\div c$ | $a\times b\div c$ |
| $\div$ | $+$ | $a\div(b+c)=\frac{a}{b+c}$ | $\frac{a}{b}+c$ |
| $\div$ | $-$ | $a\div(b-c)=\frac{a}{b-c}$ | $\frac{a}{b}-c$ |
| $\div$ | $\times$ | $a\div(b\times c)=a\div b\div c$ | $a\div b\times c$ |
| $\div$ | $\div$ | $a\div(b\div c)=a\div b\times c$ | $a\div b\div c$ |

我们对比右侧两列，发现只有 $8$ 种组合会不合法：$(-,+),(-,-),(\times,+),(\times,-),(\div,+),(\div,-),(\div,\times),(\div,\div)$。\
但是现在考虑了四则运算，所以又个特例，比如 `define sum=a+b`，然后表达式为 `sum*2`。\
此时也是不合法的，这一部分好理解，这是运算等级的差异导致的。\
通过与上面一样的列举思路我们可以发现有以下四种情况不合法（前为宏定义的符号，后为外层符号）：$(+,\times),(-,\times),(+,\div),(-,\div)$。\
我们前面已经说过了，宏定义内部只要与前面有一个不合法的结合就一定不合法，与后面同理，所以一个直观的思路就是我们记录每一个宏定义的内部是否有 $+-\times\div$，并与这十二种不合法情况一一对应。\
这当然是可以的，但是处理起来太麻烦了，我们做模拟题要充分利用题目条件。\
我们观察到宏定义里的符号都是 $(+,-)/(\times,\div)$ 两两为一组出现的，所以我们可以只记录是否出现 $+/-$ 以及是否出现 $\times/\div$。\
我们还可以进一步简化，注意到 $\times/\div$ 不合法的时候 $+-$ 也不合法，而 $+-$ 不合法的时候 $\times/\div$ 不一定不合法。所以我们若出现了 $+-$ 就不关心 $\times/\div$ 了。\
具体来说，我们可以把所有的宏定义分成四类：
1. 自身是合法的，出现了 $+-$。
2. 自身是合法的，没出现 $+-$，出现了 $\times\div$。
3. 自身是合法的，什么都没出现（就代表一个变量）。
4. 自身是不合法的。

对于第四种，只要出现了当前表达式一定不合法；否则如果是第三种，它就不会因为前后的符号而不合法；前两种之间第一种包含了第二种，我们只需要判断是否属于对应的 $12$ 个不合法状态即可，其中第二种不需要判断后面是否合法。
## 最终版本
我们考虑在上面的基础上加入括号的考虑。\
其实我们前面关于括号的考虑已经足够了，以防万一我们再验证一遍。\
如果遇到括号那我们递归判断括号里是否合法，如果不合法外层一定不合法，这个性质现在依旧可行。\
如果内层合法我们就把它作为一个变量，这个性质现在也可行。\
于是我们在简化版本5的基础上加入括号的递归处理这个题就彻底大功告成了。
## 对于状态的检验
我们这个状态实际上如果一步一步这么推过来是比较自然的，但是防止我们漏掉某些情况或者某些转移有误，我们引入状态机进行检验。\
首先要了解状态机一些基本结构。\
简单来说就是每个状态在遇到可能遇到的所有条件时都有一条唯一路径通往另一个状态。\
那为什么要满足上述条件呢？\
第一个，每个状态遇到所有可能碰到的条件都必须有出路，否则这个状态碰到该条件时就会无法转移。\
第二个，每个状态与每个条件都只能有一个转移路径，这个也是好理解的，否则一个状态它就不知道转移到哪个状态了。\
当然，还有第三个天然条件就是状态机里的所有状态要包含所有状态。\
那么我们来验证一下我们的状态。\
第三点是自然的，每个宏定义只有：合法/不合法两种状态。\
而不合法状态又分为：有符号/无符号两种。\
有符号又分为：$+-$ 和 $\times\div$ 两种。\
第二点根据我们的转移也是成立的，每种宏定义状态与每个外部符号结合后的转移都是唯一的。（注意这里外部符号分为前后两种）\
第一点在我们上文的状态转移中虽然有部分没有提及，但是也是隐藏的，就是如果合法（非那 $12$ 种情况），状态就转移到对应的 $1,2,3$ 号状态。\
这也就是为什么我们要把 $1,2$ 状态分离，这样才可以保证每种状态的转移路径唯一。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
map<string,string>mp;
map<string,int>rk;
bool issign(char c){
    return c=='+'||c=='-'||c=='*'||c=='/';
}
int srk(char c){
    if(c=='+')return 1;
    if(c=='-')return 2;
    if(c=='*')return 3;
    if(c=='/')return 4;
    return 0;
}
int check(string s){
    if(rk.count(s))return rk[s];
    int i=0;
    vector<int>sign;
    for(;i<s.size();++i){
        if(s[i]=='('){
            int cnt=1,j=i;
            string str;
            while(cnt){
                j++;
                if(s[j]==')'){
                    cnt--;
                    if(!cnt){
                        i=j;
                        int nsign=check(str);
                        if(nsign==-1)return -1;
                        break;
                    }
                }
                str+=s[j];
                if(s[j]=='(')cnt++;
            }
        }
        else{
            if(issign(s[i])){
                sign.push_back(srk(s[i]));
            }else{
                string now;
                while(i<s.size()&&(isalpha(s[i])||isdigit(s[i]))){
                    now+=s[i++];
                }
                i--;
                int nrk;
                if(rk.count(now))nrk=rk[now];
                else nrk=0;
                if(nrk==-1)return -1;
                if(nrk){
                    if(nrk==1){
                        if(!sign.empty()&&sign.back()!=1)return -1;
                        for(int ii=i+1;ii<s.size();++ii){
                            if(issign(s[ii])){
                                if(srk(s[ii])>2)return -1;
                                break;
                            }
                        }
                    }else{
                        if(!sign.empty()&&sign.back()==4)return -1;
                    }
                }
            }
        }
    }
    if(sign.empty())return 0;
    for(int p:sign){
        if(p<=2)return 1;
    }
    return 2;
}
signed main(){
    cin>>n;
    if(!n){
        cout<<"OK\n";
        return 0;
    }
    for(int i=1;i<=n;++i){
        string str;cin>>str;
        if(str=="#")cin>>str;
        cin>>str;
        string ss;getline(cin,ss);
        string s;
        for(char c:ss){
            if(c!=' ')s+=c;
        }
        mp[str]=s;
        int iu=check(s);
        rk[str]=iu;
    }
    string lst;
    getline(cin,lst);
    string LST;
    for(char c:lst){
        if(c!=' ')LST+=c;
    }
    if(check(LST)!=-1)cout<<"OK\n";
    else cout<<"Suspicious\n";
    return 0;
}
```

---

