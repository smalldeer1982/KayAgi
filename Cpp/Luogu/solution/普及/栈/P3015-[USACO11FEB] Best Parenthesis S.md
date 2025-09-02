# [USACO11FEB] Best Parenthesis S

## 题目描述

Recently, the cows have been competing with strings of balanced parentheses and comparing them with each other to see who has the best one.

Such strings are scored as follows (all strings are balanced): the string '()' has score 1; if 'A' has score s(A) then '(A)' has score 2\*s(A); and if 'A' and 'B' have scores s(A) and s(B), respectively, then 'AB' has score s(A)+s(B). For example, s('(())()') = s('(())')+s('()') = 2\*s('()')+1 = 2\*1+1 = 3.

Bessie wants to beat all of her fellow cows, so she needs to calculate the score of some strings. Given a string of balanced parentheses of length N (2 <= N <= 100,000), help Bessie compute its score.

给定一个只包含左右括号的字符串，得分规则如下：

如果一对括号内没有括号，那么这对括号的得分为1；如果两对括号互不包含（即并列存在），那这两对括号的得分相加；如果括号内包含一对括号，那么这个括号的得分纪为内部括号序列的得分\*2。

例如：对于这样一个字符串："() ()"，两对括号并列存在，则得分为1+1=2;

而对于这样一个字符串："(())"，最外层的括号内层包含一对括号，则得分为2\*1=2.


Bessie想击败所有同事的牛，所以她需要计算某个字符串的评分。给定一个长度为n、只包含括号的字符串（2≤N≤100000），计算其得分帮助Bessie。


## 说明/提示

This corresponds to the string "(())()". 

As discussed above.

输出答案要mod12345678910


## 样例 #1

### 输入

```
6 
0 
0 
1 
1 
0 
1 
```

### 输出

```
3 
```

# 题解

## 作者：kkxhh (赞：15)

给一个比较好理解的代码

```cpp
#include <cstdio>
using namespace std;

typedef long long ll;

const ll mod=12345678910;
ll n,t=0,s[50010]={0},a;

int main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a);
        if(!a) t++;
        else{
            if(!s[t]) s[t-1]=(s[t-1]+1)%mod,s[t--]=0;
            else s[t-1]=(s[t-1]+s[t]*2)%mod,s[t--]=0;
        }
    }
    printf("%lld",s[0]);
    return 0;
}
```

### s[i] 表示第i层目前的数值

**读到左括号时就直接增加一层**，读到右括号时则分为两种情况，如果**s[t]等于0**，说明这一层是一个直接的“（）”，于是就**直接给上一层加1**，否则**s[t]不等于0**，说明这一层的括号内还有其他括号，于是把**s[t]乘上2后加到上一层**。

最后答案就是**s[0]**了

---

## 作者：king_xbz (赞：3)

题目翻译不完全，这是许多国外oj拿过来的题的通病，所以我来补充翻译一下

输入格式：
```cpp
第一行，n；
接下来n行，每行0或1，0对应“（”；1对应“）”
```
输出格式
```cpp
得分对12345678910取模的结果
```
然后再用一个式子简单推一下样例
```cpp
s（'（（））（）'）=s（'（（））'）+s（'（）'=2*s（'（）'+1=2*1+1=3。
```
英文渣渣，翻译的不好请见谅。

别的东西题目上说的已经很清楚了；

接下来是做题的思路->

我们可以用定义一个整型变量tops来模拟栈顶指针。

当输入为‘（’入栈，tops++；

当输入为“）”出栈，tops--；

若这一位是‘）’但上一位是‘（’进行x_mod，即计算2^tops次方，并累加入tot；

最后输出tot值即可。

需要注意的是：

1.取模的12345678910会爆int，所以开long long。

2.注意每一步都取模，别因为少%而丢失部分分

最后，上代码，自以为还是蛮简洁易懂的。
```cpp
#include<bits/stdc++.h>
#define p 345345
#define h 5001
#define fint register int
#define int long long
#define mods 12345678910
using namespace std;
int a[p],tops,tot;
inline int read();
inline int x_mod(int x,int y);
signed main()
{
	int n;
	n=read();
	for(fint i=1;i<=n;i++)
	a[i]=read();
	for(fint i=1;i<=n;i++)
		if(a[i]==0)
		tops++;
		else
		{
		tops--;
		if(a[i-1]==0)
		tot+=x_mod(1,tops),tot%=mods;
		}
	cout<<tot%mods;
	return 0;
}

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

inline int x_mod(int x,int y)
{
	for(fint i=1;i<=y;i++)
		x*=2,x%=mods;
	return x;
}
```
总体来说这道题主要还是模拟，只要理解题意难度还是不大的。祝大家AC！

---

## 作者：Magi_karp (赞：3)

我是用栈做的……也不是很长……


大体就是一个运算符栈f，一个数字栈a，


（完全的中缀表达式求值的思路）  （管理员麻烦帮忙删一下前一个QAQ，我写的前缀表达式）


这里我将左括号存为0，加号存为1，（自己随便定）


右括号因为一旦出现就要找到左括号匹配掉，所以不用存到栈里。


乘法是一定跟着右括号出现的，也就是一旦出现立即运算


所以也不用存到栈里。


但是我实现了很长时间，


反正如果有能力的大佬看到这里应该就不要看下去啦


自己实现的时候会发现很多有意思的细节


···
```cpp
#include<cstdio>
#define mod 12345678910LL //这个12345678910已经超过了int的范围所以要加LL
using namespace std;
int n,t,tt,f[500005],x[500005];
long long a[500005];
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&x[i]);
        if (x[i])   //如果读入的是1，就是右括号
        {
            while (f[tt])  //要把从这里到最近的左括号都匹配干净算成一个数
                a[t-1]=(a[t-1]+a[t])%mod,t--,tt--;   //栈里面不是左括号就肯定是加号啦
            tt--;     //左括号弹掉
            if (x[i-1]) a[t]=a[t]*2%mod;  //既然是一个括号了就要把里面的值翻倍
            else a[++t]=1;            //但是如果括号里面没东西（就是左右括号连续出现）
                                                         //就再开一个数字栈的值为1
        }
        else
        {
            if (x[i-1]) f[++tt]=1;   //如果上一个读进来的是右括号，
                                                       //说明上一项和将要算的这项是相加的关系
                                                       //就压进栈里一个加号
            f[++tt]=0;                 //再把左括号压进去，不能只写tt++！！！！！因为退栈的时候没清零
        }
    }
    for (int i=2;i<=t;i++)
        a[1]=(a[1]+a[i])%mod;     //最后因为肯定各项都是相加的关系了，记得求个和
    printf("%lld",a[1]);
}
```

---

## 作者：Loser_King (赞：2)

表达式计算练手题。

评分似乎虚高，个人觉得在黄~绿之间。

## 题意

> 定义一个合法括号串的分值为：如果一对括号之间还有括号对，那么这对括号的分值为内部括号序列的分值乘以二，否则就为一。总分值为所有互不包含的括号的分值和。给定一个合法括号串，求分值。

## 做法

是一道表达式求值的变形。

可以看出其实就是给定数个一，做加法和乘以二的操作。

我的代码采用递归实现：

首先使用栈预处理出所有左括号对应的右括号（在代码中表示成`brk[i]`）；

然后每次搜索 `solve(l,r)`，

对于每个`i(l<=i<=r)`，判断`brk[i]`和`i+1`是否相等（即是否为`()`这样的形式）。

若是，总得分加一；否则总得分加上`solve(i+1,brk[i]-1)*2`。

最后取模即可。

## 代码

```c++
//P3015 AC Code
//written by Loster_King(159686)
//43ms /  6.48MB / 502B C++ O2
#include<bits/stdc++.h>
#define int long long//int已经不足以存下了
using namespace std;
int const MOD=12345678910ll;
int n,a[233333],brk[233333];
stack<int>s;
int solve(int l,int r){
	int ans=0;
	for(int i=l;i<=r;i=brk[i]+1)//i=brk[i]+1：枚举下一个左括号
		if(brk[i]==i+1)ans++;
		else ans+=solve(i+1,brk[i]-1)*2,ans%=MOD;
	return ans%MOD;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(!a[i])s.push(i);
		else brk[s.top()]=i,s.pop();
	}
	cout<<solve(1,n);
}
```



---

## 作者：juseice (赞：2)

其实这题能用多项式那种方法做，就是先做完乘法再做加法。比如说(())(())就是1\*2+1\*2，观察可以发现，()代表的是1，而连续读入的)就是\*2（因为左括号在()之前），那么只要把左括号记录在栈中，读入第一个右括号时把这层栈赋为1，读入连续括号时退栈并把上面的数翻倍拿下来，就能做完乘法。和多项式不一样的是，因为加法只要括号并列就能加，而不会因为后面读入的括号影响（前面的括号数已经固定了），所以在栈中，只要两个数之间没有左括号，那么他们就能相加。最后栈顶就是答案，记住模一下就好了。

```pascal
program luogu3015;
const oo=12345678910;
var n,m,i,j,t,top:longint;
    flag:boolean;
    a:array[0..200000] of int64;
procedure insert;
begin
  inc(top);
  a[top]:=0;
  flag:=true;
end;
procedure work;
begin
  if flag then a[top]:=1
   else if a[top-1]=0 then begin dec(top);a[top]:=(a[top+1]*2)mod oo;end;
  while a[top-1]>0 do begin dec(top);a[top]:=(a[top]+a[top+1])mod oo;end;
  flag:=false;
end;
begin
  readln(n);
  for i:=1 to n do
   begin
    readln(t);
    case t of
     0:insert;
     1:work;
    end;
   end;
  write(a[1]mod oo);
end.
```

---

## 作者：moosssi (赞：1)

模拟大水题，大致思路：

用一个数组存一下每个位置得分是多少，再用个栈存一下左括号的位置，遍历数组。

如果是左括号就存到栈里。

如果是右括号，和最后入栈的左括号匹配，分两种情况：

匹配的括号之间，如果没得分，就更新为前一个位置的得分加一；

否则，利用前缀和思想，括号间得分乘二加上左括号位置的得分，就是当前位置的得分。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100005;
int num[N],n,stk[N],top;
ll sco[N],mod=12345678910;//记得取模long long 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&num[i]);
	}
	for(int i=1;i<=n;i++){
		if(num[i]){//左括号 
			if(i==stk[top]+1)sco[i]=(sco[i-1]+1)%mod;//分情况讨论 
			else sco[i]=(sco[stk[top]]+(sco[i-1]-sco[stk[top]]+mod)*2%mod)%mod;//前缀和思想求值 
			top--;//记得把匹配的括号踢出栈 
		}
		else {//右括号 
			sco[i]=sco[i-1];
			stk[++top]=i;
		}
	}
	printf("%lld",sco[n]);
	return 0;
}
```





---

## 作者：RioBlu (赞：1)

~~好像没有比我短代码的了~~

# 讲解:
用pow%100错！

cout<<pow(2,50000)<<endl;

是1.#INF

需要自己打一个类似pow的代码还需要边乘边mod
## 附上代码
```
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,k,m;
bool d[100005];//太大了怕爆数组
int main()
{
	cin>>a;//输入
	for(int s=0;s<a;s++)
	{
		cin>>d[s];
		if(d[s]==0)c++;//检测是否是括号'('
		else//是')'
		{
			c--;//要1
			if(d[s-1]==0)
			{
				m=1;//承担Pow的代码
				for(int v=0;v<c;v++)
				{
					m=m*2;//次次*2
					m=m%12345678910;//边乘编mod
				}
				k+=m;
			}
		}
		k=k%12345678910;//再次mod
	}
	cout<<k<<endl;//上面有mod，无需再mod耗时间
	return 0;//结束
}
```

---

## 作者：CReatiQ (赞：0)

### 题意概述

读入一个长为 $n$ 的 $01$ 串，一对内部不包含其它字符的 $01$ 贡献为 $1$ ，并列的 $01$ 序列贡献为两序列贡献之和，嵌套的 $01$ 序列，贡献为其内部 $01$ 序列贡献的两倍，求整个 $01$ 串的贡献。

---

### 思路

用栈存储待匹配的 $0$ 所对应的 $01$ 序列的贡献。

当遇到 $0$ 时，直接将一个 $0$ 压入栈中。

当遇到 $1$ 时，如果栈顶的 $0$ 无贡献，可以确定它孑然一身，直接与其配对，将其从栈顶弹出，并将新栈顶的贡献加上 $1$ ；

如果栈顶的 $0$ 有贡献，说明它内部包含有 $01$ 序列，与其配对，将其从栈顶弹出，并把它的贡献的两倍加到新的栈顶上。

---

### Code

手写栈：（ 55ms ）

```cpp
#include <cstdio>
#include <cstring>
#define int long long

const int MAXN=1e5+10,mod=12345678910;
int n,in,tmp,tmp2;

struct stack
{
	int poi,array[MAXN];
	
	inline int top() { return array[poi]; }
	
	inline void push(int a) { array[++poi]=a; }
	
	inline void pop() { if (poi) poi--; }
	
	inline bool empty() { return poi==0; }
	
	inline int size() { return poi; }
	
	stack() { poi=0,memset(array,0,sizeof(array)); }
} s;

signed main()
{
	scanf("%lld",&n);
	s.push(0);
	for (int i=1;i<=n;i++)
	{
		scanf("%lld",&in);
		if (in)
		{
			if (s.top())
			{
				tmp=(s.top()<<1)%mod;
				s.pop();
				tmp2=tmp+s.top();
				s.pop();
				s.push(tmp2);
			}
			else
			{
				s.pop();
				tmp=s.top()+1;
				s.pop();
				s.push(tmp);
			}
		}
		else s.push(0);
	}
	printf("%lld",s.top()%mod);
	return 0;
}
```

STL栈：（ 64ms ）

```cpp
#include <stack>
#include <cstdio>
#define int long long
using namespace std;

const int mod=12345678910;
int n,in,tmp,tmp2;
stack<int> s;

signed main()
{
	scanf("%lld",&n);
	s.push(0);
	for (int i=1;i<=n;i++)
	{
		scanf("%lld",&in);
		if (in)
		{
			if (s.top())
			{
				tmp=(s.top()<<1)%mod;
				s.pop();
				tmp2=tmp+s.top();
				s.pop();
				s.push(tmp2);
			}
			else
			{
				s.pop();
				tmp=s.top()+1;
				s.pop();
				s.push(tmp);
			}
		}
		else s.push(0);
	}
	printf("%lld",s.top()%mod);
	return 0;
}
```


---

## 作者：Minclxc (赞：0)

看到没题解，就发一个

这题一看裸模拟，但是递归有些多，所以还是调试了很久

递归思路是看到一个“（）”就加1，“（”但后面不跟“）”就进入下一层，加上两倍将传回来的结果

因为是递归，所以程序还是挺短的

```cpp
#include<cstdio>
using namespace std;
#define fo(a,b,c) for(int a=b;a<=c;a++)
#define go(a,b,c) for(int a=b;a>=c;a--)
#define LL long long
int read(){
    int a=0,f=0;char c=getchar();
    for(;c<'0'||c>'9';c=getchar())if(c=='-')f=1;
    for(;c>='0'&&c<='9';c=getchar())a=a*10+c-'0';
    return f?-a:a;
}
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
const LL mo=12345678910;
const int maxn=1e5+2;
int a[maxn],n;
LL dfs(int &x){
    LL sum=0;
    while(!a[++x]){
        if(a[x+1])sum++,x++;
        else sum=(sum+2*dfs(x))%mo;
    }
    return sum;
}
int main(){
    //freopen("in.txt","r",stdin);
    n=read();fo(i,1,n)a[i]=read();a[n+1]=1;
    int i=0;
    printf("%lld",dfs(i));
    return 0;
}
```

---

## 作者：依依 (赞：0)

正解：分治。

预处理出每个左括号所对应的右括号的所在位置。

然后对于整个问题，分治，用搜索得到部分解，然后更新答案。
[代码](http://www.cnblogs.com/adelalove/p/8569683.html)

---

