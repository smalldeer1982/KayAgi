# GodFly的求导工具

## 题目背景

“求得导中导，方为人上人。”作为一名铁头娃，$GodFly$已不满足于简单的求导了。

## 题目描述

$GodFly$为了证明自己的头铁，决定挑战一项任务：求一个具有大整数系数的$n$次多项式函数的$k$阶导。现在他希望聪明的你能够…静静地坐在那里看他求导。要知道，他可是能与神威-太湖之光匹敌的男人。

作为$GodFly$的朋友，$xhx$希望你能帮他写一个程序，与$GodFly$一同计算导函数及导数。如果你的程序能跑过他的手算，$xhx$会敲一下$GodFly$的铁头。

*关于导数的几个运算法则：

若$f(x)=ax^n$，则$f'(x)=anx^{n-1}$；

若$F(x)=f(x)+g(x)$，则$F'(x)=f'(x)+g'(x)$；

其中$f'(x)$，$g'(x)$，$F'(x)$分别表示$f(x)$，$g(x)$，$F(x)$的导函数。

**不要被导数吓到，本题考点不在此**

**设$g(x)=ax^3+bx^2+c$，则$g(x_0)=ax_0^3+bx_0^2+c$。**

**$k$阶导即求$k$次导数。**

**新样例：https://pan.baidu.com/s/1w64WmnnGtKyAluxrX3PkNg； 数据已更新。**

## 说明/提示

**【数据范围】**

对于$30$%的数据，$n<=5$，$a_i<=100$，$x_0<=100$，且对于任意$0<=i<=n$，$a_ix^i$出现有且仅有一次，且保证数据以$i$为关键字降序排列；

另有$10$%的数据，$k=0$；

另有$10$%的数据，$k=1$；

另有$10$%的数据，$n=k$；

对于$100$%的数据，$n<=100$，$k<=n$，$m<=10$，$a_i<=10^5$，$x_0<=10^5$；

样例数据在**data.zip\derivative\**中。

**【样例说明】**

对$f(x)$求导，则一阶导$f'(x)=3x^2+4x+1$；求二阶导，即对$f'(x)$再求导，得$f''(x)=6x+4$；故所求$f(0)=6*0+4=4$，$f(1)=6*1+4=10$。

**【提示】**

$PS$：担心大家抱怨代码量大（出题人懒），较原题简化了许多。

如果你提前$AK$了，不妨看看一段铁头娃之间的对决：

《冯所长三导导死郑拔蚌》

冯所长······扑的只一导，正导在分式上，导得郑蚌头晕眼花，参数歪在半边，却便似开了个初等函数表，平方，根号，对勾一发都导出来。郑铁头算不过来，那把答案也丢在一边，口里只叫：“导得好！”冯所长骂道：“铁头娃！还敢应口！”提起笔来就分子只一导，导得火星四溅，头破血流，也似开了个二项式定理，三次、四次、五次都绽将出来。
两边看的人惧怕冯所长，谁敢向前来劝。

郑蚌导不出，讨饶。冯所长喝道：“咄！你是个铁头娃！若只和俺分类讨论到底，洒家倒饶了你！你如今对俺讨饶，洒家偏要分离参数！”又只一导，新函数上正着，却似做了一个常用导数表，指数，对数，分子分母一齐响。所长看时，只见郑蚌倒在地上，口里只有出的气，没了入的气，动弹不得。

冯所长假意道：“你这厮诈死，洒家再导！”只见头渐渐的没了。所长寻思道：“俺只指望消费这厮一顿，不想三导真个导死了他。洒家须扣分，又没题做，不如及早撒开。”拔步便走，回头指着试卷道：“这废题，洒家跳过！”一头算，一头大踏步去了。

## 样例 #1

### 输入

```
3 2
f(x)=x^3+2x^2+x^1+x^0
2
0
1```

### 输出

```
4
10```

# 题解

## 作者：__K2FeO4 (赞：1)

来水一波 Python 题解（自带高精度的功能好爽，而且本题不用 FFT）

这题读入很毒瘤，不是直接读入系数，而是读入整个函数！更令人意想不到的是函数**还有同类项！！！**（我当时就是因为这个 WA 的）我在我的代码中还加入了负系数，以及一次项与常数项指数的省略。虽然本题不需要，但是这份代码可以供我后续做数学题所需。

不过读入后面的事情就小菜一碟了。求导可以用：

$$\begin{aligned}
f(x)&=a_nx^n+a_{n-1}x^{n-1}+a_{n-2}x^{n-2}\dots+a_1x+a_0
\\f^{(k)}(x)&=a_nn^{\underline{k}}x^{n-k}+a_{n-1}(n-1)^{\underline{k}}x^{n-k-1}+a_{n-2}(n-2)^{\underline{k}}x^{n-k-2}+\dots+a_{k+1}(k+1)^{\underline{k}}x+a_kk!
\end{aligned}$$

暴力求解即可。时间复杂度 $O(n^2)$。

带入计算时，为尽可能运用分配律，我们可以选择 **[秦九韶算法](https://baike.baidu.com/item/秦九韶算法/449196)**，也就是：

$$\begin{aligned}
f(x)&=a_nx^n+a_{n-1}x^{n-1}+a_{n-2}x^{n-2}\dots+a_1x+a_0
\\&=x(x(\dots (x(x\times a_n+a_{n-1})+a_{n-2})\dots)+ a_1)+a_0
\end{aligned}$$

所有询问时间复杂度总和 $O(nm)$。

所以总时间复杂度 $O(n^2+nm)$。真实时间复杂度要更高，因为有高精（尽管 Python 自带），然而 Python 能过。

代码如下：

```python
n,k=input().split(' ')
n,k=int(n),int(k)
f=input()
g=[0 for i in range(n+1)]
i=5
while i<len(f):
  d=1
  sign=1
  while i<len(f) and (ord(f[i])<48 or ord(f[i])>=58) and f[i]!='-' and f[i]!='x':
    i+=1
  if f[i]=='-':
    sign=-1
    i+=1
  x=i
  while i<len(f):
    try:
      d=int(f[x:i+1])
    except:
      break
    i+=1
  if d==0:
    d=1
  d*=sign
  e=0
  if i<len(f) and f[i]=='x':
    e=1
  while i<len(f) and (ord(f[i])<48 or ord(f[i])>=58) and f[i]!='+' and f[i]!='-':
    i+=1
  x=i
  while i<len(f):
    try:
      e=int(f[x:i+1])
    except:
      break
    i+=1
  g[e]+=d #I wrote g[e]=d and got a WA!
# print(g)
for i in range(k,n+1):
  for j in range(i,i-k,-1):
    g[i]*=j
del g[0:k]
# print(g)
m=int(input())
for i in range(m):
  x=int(input())
  s=0
  for j in g[::-1]:
    s=s*x+j
  print(s)
```


---

## 作者：yzxoi (赞：1)

[$$\large\texttt{My Blog}$$](https://yzxoi.top/archives/1615)

## Description
> [题目链接](https://www.luogu.com.cn/problem/P4893)

给定一个 $n$ 次整系数函数 $f(x)$，问 $f(x)$ 的 $k$ 阶导在 $x_i$ 处的导数。

$1\leq n \leq 100,k\leq n,m\leq 10,a_i\leq 10^5,x_i\leq 10^5$
## Solution
很好奇这题是怎么评紫的（？

咳咳，对于这道题，你先要有**亿**点**简单**高等数学知识。

- $f(x)=x^p$ 的 $k$ 阶导函数为 $f^{(k)}(x)=\prod_{i=1}^k(p-i+1)x^{p-k}$
- $f(x)=g(x)+h(x)$ 的 $k$ 阶导函数为 $f^{(k)}(x)=g^{(k)}(x)+h^{(k)}(x)$

证明略（

假设你已经熟知了以上结论，那么就可以愉快的把这道题切掉了。

直接暴力拆出每一项的系数，暴力进行求导，找到其 $k$ 阶导函数，对于每个询问，直接暴力带入即可。

因为 $a_i\leq 10^5,x_i \leq 10^5$ 可能会导致答案爆 $int$，所以你还要~~耐心地写一个高精~~套一个高精模板。

## Code
```cpp
#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
#define W while
#define I inline
#define RI register int
#define LL long long
#define Cn const
#define gc getchar
#define DD isdigit(c=gc())
#define pc(c) putchar((c))
#define min(x,y) ((x)<(y)?(x):(y))
#define max(x,y) ((x)>(y)?(x):(y))
using namespace std;
namespace Debug{
	Tp I void _debug(Cn char* f,Ty t){cerr<<f<<'='<<t<<endl;}
	Ts I void _debug(Cn char* f,Ty x,Ar... y){W(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	Tp ostream& operator<<(ostream& os,Cn vector<Ty>& V){os<<"[";for(Cn auto& vv:V) os<<vv<<",";os<<"]";return os;}
	#define gdb(...) _debug(#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
namespace FastIO{
	Tp I void read(Ty& x){char c;int f=1;x=0;W(!DD) f=c^'-'?1:-1;W(x=(x<<3)+(x<<1)+(c&15),DD);x*=f;}
	Ts I void read(Ty& x,Ar&... y){read(x),read(y...);}
	Tp I void write(Ty x){x<0&&(pc('-'),x=-x,0),x<10?(pc(x+'0'),0):(write(x/10),pc(x%10+'0'),0);}
	Tp I void writeln(Cn Ty& x){write(x),pc('\n');}
}using namespace FastIO;
Cn int N=110;
class Int{//Manchery的高精模板
	#define BASE 1000000000
	public:
	typedef long long value;
	void New(size_t l){
		if (a!=NULL)delete[] a;a=new value[l];
		len=1;a[0]=0;sign=1;
	}
	Int():a(NULL),base(BASE){New(1);}
	Int(value x):a(NULL),base(BASE){New(1);*this=x;}
	Int(value x,value _base):a(NULL),base(_base){New(1);*this=x;}
	Int(const Int &B):a(NULL),base(BASE){New(1);*this=B;}
	~Int(){delete[] a;}
	Int& operator =(value x){
		size_t l=1;for (value x1=max(x,-x);x1>=base;++l,x1/=base);New(l);
		if (x<0)x=-x,sign=0;else sign=1;
		len=0;while (x)a[len++]=x%base,x/=base;
		if (!len)a[len++]=0;
		return *this;
	}
	Int& operator =(const Int &A){
		New(A.len);len=A.len;memcpy(a,A.a,sizeof(value)*len);
		base=A.base;sign=A.sign;return *this;
	}
	friend Int operator -(Int A){A.sign=1-A.sign;return A;}
	bool operator !(){if (len==1&&a[0]==0)return 1;else return 0;}
	friend Int operator +(Int A,Int B){
		if (A.sign!=B.sign){B.sign=1-B.sign;return A-B;}
		if (A.base!=B.base)
			if (A.base>B.base)B.set_base(A.base);
			else A.set_base(B.base);
		Int res;res.set_base(A.base); int len=A.len>B.len?A.len:B.len;
		res.New(len+1);res.sign=A.sign;
		memset(res.a,0,(len+1)*sizeof(value));
		for (int i=0;i<len;++i){
			if (i<A.len)res.a[i]+=A.a[i];
			if (i<B.len)res.a[i]+=B.a[i];
		}
		for (int i=0;i<len;++i)
			if (res.a[i]>=res.base)++res.a[i+1],res.a[i]-=res.base;
		if (res.a[len])res.len=len+1;else res.len=len;
		if (!res)res.sign=1;return res;
	}
	friend Int operator -(Int A,Int B){
		if (A.sign!=B.sign){B.sign=1-B.sign;return A+B;}
		if (A.base!=B.base)
			if (A.base>B.base)B.set_base(A.base);
			else A.set_base(B.base);
		if (small(A,B))swap(A,B),A.sign=1-A.sign;
		Int res;res.set_base(A.base); int len=A.len>B.len?A.len:B.len;
		res.New(len);res.sign=A.sign;
		memset(res.a,0,len*sizeof(value));
		for (int i=0;i<len;++i){
			if (i>=B.len)res.a[i]+=A.a[i];
			else res.a[i]+=A.a[i]-B.a[i];
			if (res.a[i]<0)res.a[i]+=res.base,--res.a[i+1];
		}
		while (len>1&&!res.a[len-1])--len;res.len=len;
		if (!res)res.sign=1;return res;
	}
	friend Int operator *(Int A,Int B){
		if (A.base!=B.base)
			if (A.base>B.base)B.set_base(A.base);
			else A.set_base(B.base);
		Int res;res.set_base(A.base); int len=A.len+B.len;
		res.New(len);res.sign=(A.sign==B.sign);
		memset(res.a,0,len*sizeof(value));
		for (int i=0;i<A.len;++i)
			for (int j=0;j<B.len;++j){
				res.a[i+j]+=A.a[i]*B.a[j];
				res.a[i+j+1]+=res.a[i+j]/res.base;
				res.a[i+j]%=res.base;
			}
		/*
		for (int i=0;i<A.len;++i)
			for (int j=0;j<B.len;++j)res.a[i+j]+=A.a[i]*B.a[j];
		for (int i=0;i<len-1;++i)res.a[i+1]+=res.a[i]/res.base,res.a[i]%=res.base;
		*/
		while (len>1&&!res.a[len-1])--len;res.len=len;
		return res;
	}
	friend pair<Int,Int> divide(Int A,Int B){
		if (!B){puts("error:div zero!");for (;;);}
		if (A.base!=B.base)
			if (A.base>B.base)B.set_base(A.base);
			else A.set_base(B.base);
		if (small(A,B))return make_pair(Int(0),A);
		Int C,D;C.set_base(A.base);D.set_base(A.base);C.New(A.len);C.len=A.len;
		bool Csign=(A.sign==B.sign),Dsign=A.sign;A.sign=B.sign=1;
		for (int i=A.len-1;i>=0;--i){
			C.a[i]=0;D=D*D.base;D.a[0]=A.a[i];
			int l=0,r=A.base-1,mid;
			while (l<r){
				mid=(l+r+1)>>1;
				if (small(B*mid,D+1))l=mid;
					else r=mid-1;
			}
			C.a[i]=l;D=D-B*l;
		}
		C.sign=Csign;D.sign=Dsign;if (!D)D.sign=1;
		while (C.len>1&&!C.a[C.len-1])--C.len;
		return make_pair(C,D);
	}
	Int operator /(value x){
		if (!x){puts("error:div zero!");for (;;);}
		value d=0;Int res;res.set_base(base);res.New(len);res.len=len;
		if (x<0)x=-x,res.sign=(sign==0);
		else res.sign=(sign==1);
		for (int i=len-1;i>=0;--i)
			d=d*base+a[i],res.a[i]=d/x,d%=x;
		while (res.len>1&&!res.a[res.len-1])--res.len;
		return res;
	}
	Int operator %(value x){
		value d=0;if (x<0)x=-x;
		for (int i=len-1;i>=0;--i)d=(d*base+a[i])%x;
		return d;
	}
	friend Int abs(Int A){A.sign=1;return A;}
	friend bool small(Int A,Int B){
		if (A.base!=B.base)
			if (A.base>B.base)B.set_base(A.base);
			else A.set_base(B.base);
		if (A.len!=B.len)return A.len<B.len;
		for (int i=A.len-1;i>=0;--i)
			if (A.a[i]!=B.a[i])return A.a[i]<B.a[i];
		return 0;
	}
	friend bool operator <(Int A,Int B){
		if (A.sign!=B.sign)return A.sign<B.sign;
		return A.sign==1?small(A,B):small(B,A);
	}
	friend bool operator ==(Int A,Int B){
		if (A.base!=B.base)
			if (A.base>B.base)B.set_base(A.base);
			else A.set_base(B.base);
		if (A.sign!=B.sign||A.len!=B.len)return 0;
		for (int i=0;i<A.len;++i)if (A.a[i]!=B.a[i])return 0;
		return 1;
	}
	friend bool operator !=(Int A,Int B){return !(A==B);}
	friend bool operator >(Int A,Int B){return !(A<B||A==B);}
	friend bool operator <=(Int A,Int B){return A<B||A==B;}
	friend bool operator >=(Int A,Int B){return A>B||A==B;}
	Int operator /(Int B){return divide(*this,B).first;}
	Int operator %(Int B){return divide(*this,B).second;}
	Int& operator +=(Int B){*this=*this+B;return *this;}
	Int& operator -=(Int B){*this=*this-B;return *this;}
	Int& operator *=(Int B){*this=*this*B;return *this;}
	Int& operator /=(Int B){*this=*this/B;return *this;}
	Int& operator %=(Int B){*this=*this%B;return *this;}
	Int& operator ++(){*this=*this+1;return *this;}
	Int& operator --(){*this=*this-1;return *this;}
	Int operator ++(int){Int res(*this);*this=*this+1;return res;}
	Int operator --(int){Int res(*this);*this=*this-1;return res;}
	Int operator +(value x){return *this+Int(x,this->base);}
	Int operator -(value x){return *this-Int(x,this->base);}
	Int operator *(value x){return *this*Int(x,this->base);}
	//Int operator /(value x){Int T;T=x;return *this/T;}
	//Int operator %(value x){Int T;T=x;return *this%T;}
	Int& operator *=(value x){*this=*this*x;return *this;}
	Int& operator +=(value x){*this=*this+x;return *this;}
	Int& operator -=(value x){*this=*this-x;return *this;}
	Int& operator /=(value x){*this=*this/x;return *this;}
	Int& operator %=(value x){*this=*this%x;return *this;}
	bool operator ==(value x){return *this==Int(x,this->base);}
	bool operator !=(value x){return *this!=Int(x,this->base);}
	bool operator <=(value x){return *this<=Int(x,this->base);}
	bool operator >=(value x){return *this>=Int(x,this->base);}
	bool operator <(value x){return *this<Int(x,this->base);}
	bool operator >(value x){return *this>Int(x,this->base);}
	friend Int gcd(Int x,Int y){
		Int t;int cnt=0;
		while (1){
			if (x<y)t=x,x=y,y=t;
			if (y==0){
				while (cnt--)x*=2;
				return x;
			}
			if (x%2==0&&y%2==0)x/=2,y/=2,++cnt;
			else if (x%2==0)x/=2;
			else if (y%2==0)y/=2;
			else {t=x;x=y;y=t-y;}
		}
	}
	void to_arr(char *c){
		char *c1=c;
		for (int i=0;i<len-1;++i)
			for (value x=a[i],b=base/10;b>=1;b/=10)*c1++='0'+x%10,x/=10;
		for (value x=a[len-1];x>0;x/=10)*c1++='0'+x%10;
		if (len==1&&a[len]==0)*c1++='0';
		if (sign==0)*c1++='-';*c1=0;reverse(c,c1);
	}
	void from_arr(char *c){
		size_t base_l=get_basel(),b=1;int cl=strlen(c);value x=0;
		New((cl+base_l-1)/base_l);len=0;
		if (*c=='-')sign=0,++c,--cl;else sign=1;
		while (--cl>=0){
			x+=(c[cl]-'0')*b;b*=10;if (b==base)a[len++]=x,x=0,b=1;
		}
		if (!len||x)a[len++]=x;
		while (len>1&&!a[len-1])--len;
	}
	void set_base(int _base){
		if (base==_base)return;
		char *c=new char[len*get_basel()+1];
		to_arr(c);base=_base;from_arr(c);
		delete[] c;
	}
	void set_basel(int _l){
		size_t _base=1;while (_l--)_base*=10;set_base(_base);
	}
	void read(){
		vector<char> s;char ch;
		scanf(" %c",&ch);if (ch=='-')s.push_back('-'),ch=getchar();
		for (;ch>='0'&&ch<='9';ch=getchar())s.push_back(ch);
		char *c=new char[s.size()+1];
		for (int i=0;i<s.size();++i)c[i]=s[i];c[s.size()]=0;
		from_arr(c);delete[] c;
		if (!*this)this->sign=1;
	}
	void print(){
		if (!sign)putchar('-');
		printf("%d",int(a[len-1]));
		for (int i=len-2;i>=0;--i){
			for (int j=base/10;j>=10;j/=10)
				if (a[i]<j)putchar('0');
					else break;
			printf("%d",(int)a[i]);
		}
	}
	void println(){print();putchar('\n');}
	private:
	value *a,base;int len;bool sign;  //0="-"
	size_t get_basel()const{
		size_t res=0;for (int b=base/10;b>=1;b/=10,++res);
		return res;
	}
	#undef BASE
};
Int num[N],Ans[N],top=1,ans;
int n,m,k,len;
string str;
I Int fpow(int a,int b){Int A=a,s=1;W(b!=0){if(b%2==1) s*=A;A*=A;b=b/2;}return s;}//高精快速幂
int main(){
	RI i,j,s;for(read(n,k),cin>>str,len=str.length(),i=5;i<len;)
		if(isdigit(str[i])){j=i+1;s=str[i]-'0';W(j<len&&isdigit(str[j])) s=s*10+str[j]-'0',j++;top=s,i=j;}//处理系数
		else if(str[i]=='x'){j=i+1;s=0;W(j<len&&str[j]!='^') ++j;j++;W(j<len&&isdigit(str[j])) s=s*10+str[j]-'0',++j;num[s]+=top;top=1;i=j;}//处理次数
		else i++;
	for(i=0;i<=n;i++)
		if(i-k>=0) for(Ans[i-k]=num[i],j=1;j<=k;j++) Ans[i-k]*=i-j+1;//直接求导套公式
	for(read(m);m--;){for(read(s),ans=j=0;j<=n;j++) ans=ans+Ans[j]*fpow(s,j);ans.println();}//对于每个询问直接暴力计算
	return 0;
}
```

---

