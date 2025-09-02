# High School: Become Human

## 题目描述

### 题目大意
输入一个 $x$ ,一个 $y$ ，求是  $x^y$  大还是  $y^x$  大。 $(1≤x,y≤10^9)$

## 样例 #1

### 输入

```
5 8
```

### 输出

```
>
```

## 样例 #2

### 输入

```
10 3
```

### 输出

```
<
```

## 样例 #3

### 输入

```
6 6
```

### 输出

```
=
```

# 题解

## 作者：fzj2007 (赞：7)

## 第一步 读题

给定两个数 $x$，$y$，求是 $x^y$ 大还是 $y^x$ 大。

- 如果 $x^y \gt y^x$，则输出 $\gt$。
- 如果 $x^y \lt y^x$，则输出 $\lt$。
- 如果 $x^y = y^x$，则输出 $=$。

## 第二步 思路

思路一（大众化的思路）：我们的第一感都是直接高精快速幂乘的这种暴力吧......但是我们一看数据范围 $1 \le x,y \le 10 ^9$，发现这样写会超时吧......这题应该是个结论题（~~确信~~）。

----------
思路二：经历了思路一，我们要寻找规律来找结论。

我们发现幂可以取对数转化为乘数。即把 $x^y$ 转化为 $y \ln x$，把 $y^x$ 转化为 $x \ln y$，就把比较 $x^y$ 与 $y^x$ 的大小关系转化为比较 $y \ln x$ 与 $x \ln y$ 的大小关系。由于`C++`中的 $\log$ 是以 $e$ 为底的，所以我们可以直接使用。

## 第三步 代码

思路一的代码我还是贴上吧，虽然是`TLE`的很惨的......（作者用的是压位高精，大家慢慢食用~）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX=10001;
struct hp{
    int num[MAX];
    
    hp&operator=(const char*);
    hp&operator=(int);
    hp();
    hp(int);
    
    bool operator>(const hp&)const;
    bool operator<(const hp&)const;
    bool operator<=(const hp&)const;
    bool operator>=(const hp&)const;
    bool operator!=(const hp&)const;
    bool operator==(const hp&)const;

    hp operator+(const hp&)const;
    hp operator-(const hp&)const;
    hp operator*(const hp&)const;
    hp operator/(const hp&)const;
    hp operator%(const hp&)const;
    
    hp&operator+=(const hp&);
    hp&operator-=(const hp&);
    hp&operator*=(const hp&);
    hp&operator/=(const hp&);
    hp&operator%=(const hp&);
    hp&operator&(const hp&);
    hp&operator&(int);
    hp power(hp x,hp y);//x的y次方 
    hp sqrt(hp x,hp y);//x开y次方 
};
// num[0]用来保存数字位数。利用10000进制可以节省空间和时间。
hp&hp::operator=(const char* c){
    memset(num,0,sizeof(num));
    int n=strlen(c),j=1,k=1;
    for(int i=1;i<=n;i++){
        if(k==10000) j++,k=1;// 10000进制，4个数字才算1位。
        num[j]+=k*(c[n-i]-'0');
        k*=10;
    }
    num[0]=j;
    return *this;
}

hp&hp::operator=(int a){
    char s[MAX];
    sprintf(s,"%d",a);
    return *this=s;
}
hp::hp(){
	memset(num,0,sizeof(num)); 
	num[0]=1;
}
hp::hp(int n){
	*this=n;
}// 目的：支持“hp a=1;”之类的代码。

// 如果位数不等，大小是可以明显看出来的。如果位数相等，就需要逐位比较。
bool hp::operator > (const hp &b) const{
    if(num[0]!=b.num[0]) return num[0]>b.num[0];
    for(int i=num[0];i>=1;i--)
        if(num[i]!=b.num[i])
            return (num[i]>b.num[i]);
    return false;
}
bool hp::operator<(const hp &b)const{return b>*this;}
bool hp::operator<=(const hp &b)const{return !(*this>b);}
bool hp::operator>=(const hp &b)const{return !(b>*this);}
bool hp::operator!=(const hp &b)const{return (b>*this)||(*this>b);}
bool hp::operator==(const hp &b)const{return !(b>*this)&&!(*this>b);}
// 注意：最高位的位置和位数要匹配。
//加法 
hp hp::operator+(const hp&b)const{
    hp c;
    c.num[0]=max(num[0],b.num[0]);
    for(int i=1;i<=c.num[0];i++){
        c.num[i]+=num[i]+b.num[i];
        if(c.num[i]>=10000){// 进位
            c.num[i]-=10000;
            c.num[i+1]++;
        }
    }
    if(c.num[c.num[0]+1]>0) c.num[0]++;// 9999+1，计算完成后多了一位
    return c;
}
//减法 
hp hp::operator-(const hp&b)const{
   hp c;
   c.num[0]=num[0];
   for (int i=1;i<=c.num[0];i++){
       c.num[i]+=num[i]-b.num[i];
       if(c.num[i]<0){  // 退位
            c.num[i]+=10000;
            c.num[i+1]--;
        }
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;// 100000000-99999999
    return c;
}
//顺便声明 
hp&hp::operator+=(const hp &b){return *this=*this+b;}
hp&hp::operator-=(const hp &b){return *this=*this-b;}
//乘法 
hp hp::operator*(const hp&b)const{
    hp c;
    c.num[0]=num[0]+b.num[0]+1;
    for(int i=1;i<=num[0];i++){
        for(int j=1;j<=b.num[0];j++){
            c.num[i+j-1]+=num[i]*b.num[j];            // 和小学竖式的算法一模一样
            c.num[i+j]+=c.num[i+j-1]/10000;            // 进位
            c.num[i+j-1]%=10000;
        }
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999*0
    return c;
}
//同上 
hp&hp::operator*=(const hp &b){return *this=*this*b;}
hp hp::operator/(const hp&b)const{
    hp c, d;
    c.num[0]=num[0]+b.num[0]+1;
    d.num[0]=0;
    for(int i=num[0];i>=1;i--){
        // 以下三行的含义是：d=d*10000+num[i];
        memmove(d.num+2, d.num+1, sizeof(d.num)-sizeof(int)*2);
        if(d!=0) d.num[0]++;
        d.num[1]=num[i];

        // 以下循环的含义是：c.num[i]=d/b; d%=b; 利用二分查找求c.num[i]的上界。
        // 注意，这里是二分优化后除法和朴素除法的区别！
        int left=0,right=9999,mid;
        while(left<right){
            mid = (left+right)/2;
            if(b*hp(mid)<=d) left=mid+1;
            else right=mid;
        }
        c.num[i]=right-1;
        d=d-b*hp(right-1);
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999/99999999
    return c;            
}
hp hp::operator%(const hp&b)const{
    hp c, d;
    c.num[0]=num[0]+b.num[0]+1;
    d.num[0]=0;
    for(int i=num[0];i>=1;i--){
        // 以下三行的含义是：d=d*10000+num[i];
        memmove(d.num+2, d.num+1, sizeof(d.num)-sizeof(int)*2);
        if(d!=0) d.num[0]++;
        d.num[1]=num[i];

        // 以下循环的含义是：c.num[i]=d/b; d%=b; 利用二分查找求c.num[i]的上界。
        // 注意，这里是二分优化后除法和朴素除法的区别！
        int left=0,right=9999,mid;
        while(left<right){
            mid = (left+right)/2;
            if(b*hp(mid)<=d) left=mid+1;
            else right=mid;
        }
        c.num[i]=right-1;
        d=d-b*hp(right-1);
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999/99999999
    return d;            
}
hp&hp::operator/=(const hp &b){return *this=*this/b;}
hp&hp::operator%=(const hp &b){return *this=*this%b;}
inline hp power(hp x,hp y){//快速幂
	hp result=1;
	while(y>0){
		if(y%2==1) result=result*x;
		x=x*x;
		y/=2;
	}
	return result;
}
inline hp sqrt(hp x,hp y){//（超级慢的开根，虽然加了二分）
	if(x==1) return x;
	hp l=0,r=x+1;
	while(l<r){
		hp mid=(l+r)/2;
		if(power(mid,y)>x) r=mid;
		else l=mid+1;
	}
	return l-1;
}
inline hp factorial(hp x){//阶乘......
	hp ans=1;
	for(hp i=1;i<=x;i+=1) ans*=i;
	return ans;
}
istream & operator>>(istream &in, hp &n){//输入必备
    char s[MAX];
    in>>s;
    n=s;
    return in;
}
ostream&operator<<(ostream &o,hp n){//输出必备
    o<<n.num[n.num[0]];
    for(int i=n.num[0]-1;i>=1;i--){
        o.width(4);
        o.fill('0');
        o<<n.num[i];
    }
    return o;
}
inline hp read(){//快读QAQ
	hp ans=0,flag=1;
	char ch=getchar();
	while((ch>'9'||ch<'0')&&ch!='-') ch=getchar();
	if(ch=='-') flag=-1,ch=getchar();
	while(ch>='0'&&ch<='9'){
		ans=ans*10+ch-'0';
		ch=getchar();
	}
	return ans*flag;
}
hp a,b;//声明
int main(){
	a=read(),b=read();//快读
	if(power(a,b)>power(b,a)) cout<<">\n";//大于
	else if(power(a,b)<power(b,a)) cout<<"<\n";//小于
	else cout<<"=\n";//相等
	return 0;
}
```

思路2：
```cpp
#include<bits/stdc++.h>
using namespace std; 
using std::cin;
using std::cout;
using std::endl;
namespace IN{//这里不用管，一直到namespace OUT都是快读
    const int MAX_INPUT = 1000000;
    #define getc() (p1==p2&&(p2=(p1=buf)+inbuf->sgetn(buf,MAX_INPUT),p1==p2)?EOF:*p1++)
    char buf[MAX_INPUT],*p1,*p2;
    template<typename T>inline bool read(T &x) {
        static std::streambuf *inbuf=cin.rdbuf();
        x=0;
        register int f=0,flag=false;
        register char ch=getc();
        while(!isdigit(ch)){
            if (ch=='-') f=1;
        	ch=getc();
        }
        if(isdigit(ch)) x=x*10+ch-'0',ch=getc(),flag=true;
        while(isdigit(ch)) {
            x=x*10+ch-48;
            ch=getc();
        }
        x=f?-x:x;
        return flag;
    }
    template<typename T,typename ...Args>inline bool read(T& a,Args& ...args) {
       return read(a)&&read(args...);
    }
    #undef getc
}

namespace OUT{//这个结束就是主题了。。
    template<typename T>inline void put(T x){
        static std::streambuf *outbuf=cout.rdbuf();
        static char stack[21];
        static int top=0;
        if(x<0){
            outbuf->sputc('-');
            x=-x;
        }
        if(!x){
            outbuf->sputc('0');
            outbuf->sputc('\n');
            return;
        }
        while(x){
            stack[++top]=x%10+'0';
            x/=10;
        }
        while(top){
            outbuf->sputc(stack[top]);
            --top;
        }
        outbuf->sputc('\n');
    }
    inline void putc(const char ch){
        static std::streambuf *outbuf=cout.rdbuf();
        outbuf->sputc(ch);
    }
    inline void putstr(string s){
    	for(register int i=0;i<s.length();i++) putc(s[i]);
	}
    template<typename T>inline void put(const char ch,T x){
        static std::streambuf *outbuf=cout.rdbuf();
        static char stack[21];
        static int top = 0;
        if(x<0){
            outbuf->sputc('-');
            x=-x;
        }
        if(!x){
            outbuf->sputc('0');
            outbuf->sputc(ch);
            return;
        }
        while(x){
            stack[++top]=x%10+'0';
            x/=10;
        }
        while(top){
            outbuf->sputc(stack[top]);
            --top;
        }
        outbuf->sputc(ch);
    }
    template<typename T,typename ...Args> inline void put(T a,Args ...args){
        put(a);put(args...);
    }
    template<typename T,typename ...Args> inline void put(const char ch,T a,Args ...args){
        put(ch,a);put(ch,args...);
    }
}
using IN::read;
using OUT::put;
using OUT::putc;
using OUT::putstr;
long long x,y;//声明变量
int main(int argc, char const *argv[]){
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    read(x,y);//读入数据
    if(x==y) putc('=');//如果相等，直接输出
    else{
        if((double)y*log(x)>(double)x*log(y)) putc('>');//套公式.......
        else if((double)y*log(x)<(double)x*log(y)) putc('<');//反过来
        else putc('=');//还一样就输出=
    }
    return 0;//BYEBYE
}
```
这道题就讲解到这里了，下次见。

如果有帮助，请点赞，谢谢！！（撰文不易，dalao勿喷，写了300行......）

---

## 作者：wpy233 (赞：5)

这题是一个常识吧。。。~~小学森都知道~~

例如两个数，一个是2，另一个是189，很明显，$2^{189}$比$189^2$要来得大。

有一个神奇的结论：**直接比较它们的大小，数更大的就作为指数**。

但是不排除一些反例，例如`2`和`3`，它们就不满足这个结论。

还有一些很玄学的情况，例如：`1`和`2000000`？

这些情况都需要被一一考虑到，楼上的大佬们直接暴力if判断。。。

本蒟蒻弱弱地问一句：都这么暴力了，能不能再暴力一点？

偶的做法是这样的：对于$x \leq 5$且$y \leq 5$的情况，直接暴力算出来。。。

对于其他的情况，先判断两数中有没有1，没有的话就按照结论输出。

如果各位大佬觉得这题切掉不过瘾，可以来做做本萌新出的[这题](https://www.luogu.org/problem/U78885)

$Code$：
```
#include <bits/stdc++.h>//万能头文件
using namespace std;
int x,y;//定义
int main()
{
	cin>>x>>y;
	if(x<=5&&y<=5)//暴力^2！对于一些特殊情况直接暴力算出来比较
	{
		int s1=1;
		int s2=1;
		for(int i=1;i<=x;i++)
			s1*=y;//y^x
		for(int i=1;i<=y;i++)
			s2*=x;//x^y
		if(s2>s1)//比较
			cout<<">";
		else if(s2<s1)
			cout<<"<";
		else
		    cout<<"=";//输出
		exit(0);
	}
	else//两数均>5
		if(x==1||y==1)//判断两数中有没有1
			if(x==1)
				cout<<"<";
			else
				cout<<">";
		else//无特殊情况
			if(x>y)//按照结论判断
				cout<<"<";
			else if(x<y)
				cout<<">";
			else
				cout<<"=";//输出
	return 0;
}
```

---

## 作者：wky32768 (赞：3)

两个数都大于e的时候，直接判就可以了。
剩下的特判，欢迎大佬来hack.
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b;
	cin>>a>>b;
	if(a==b){cout<<"=";return 0;}
	else if(a>=3&&b>=3){
		if(a<b) cout<<">";
		else cout<<"<";
		return 0;
	} else if(a==3&&b==2){cout<<">";return 0;}
	else if(a==3&&b==1){cout<<">";return 0;}
	else if(a==2&&b==1){cout<<">";return 0;}
	else if(a==2&&b==3){cout<<"<";return 0;}
	else if(a==1&&b==3){cout<<"<";return 0;}
	else if(a==1&&b==2){cout<<"<";return 0;}
	else if(a==1) {cout<<"<";return 0;}
	else if(b==1){cout<<">";return 0;}
	else if(a==2&&b==4){cout<<"=";return 0;}
	else if(a==4&&b==2){cout<<"=";return 0;}
	else if(a==2) {cout<<">";return 0;}
	else if(b==2){cout<<"<";return 0;}
	
	return 0;

}


```

---

## 作者：帅到报警 (赞：2)

### 【题意描述】
输入两个数，比较 x ^ y 与 y ^ x 的大小关系。（如此简洁明了的题面 >_<）

### 【分析】
首先，要比较 x ^ y 与 y ^ x 的大小关系， 我们需要通过一些简洁的数学证明。（前面几篇题解并没有证明，所以在此补充）

我们要先在两式旁取对数，就是比较 ln x ^ y 与 ln y ^ x 的大小关系，先假设左式小于右式：（前方高能，请注意）

	ln x ^ y < ln y & x;
    即 y * ln x < x * lny;
    所以 ln x / x < ln y / y;
    那么通过归纳我们可以设 f (n) = ln n / n;
    取这个函数的导数，即  f'（n） = ( ln n - 1 )/ n ^ 2;
    那么当 f'（n）> 0 时， ln n > 1,
    所以当 x, y > e (因为是整数，相当于大于等于3)时，
    若 x > y, 则 x ^ y < y ^ x;
证明完成之后，我们就可以知道，**当给出的 x , y 大于 3 的时候，只需要判断 x 和 y 的大小关系即可，其他的只要特判就可以了**。

### 【核心代码】
判断过程
```cpp
if(x == y)
{
    cout << "=";
	return 0;
}
if(x == 1)
    cout << "<";
else if(y == 1)
    cout << ">";
else if(x == 2 && y == 3)
	cout << "<";
else if(x == 2 && y == 4)
    cout << "=";
else if(x == 3 && y == 2)
    cout << ">";
else if(x == 4 && y == 2)
	cout << "=";
else
{
    if(x > y)
        cout << "<";
    else
        cout << ">";
}
```

### 【正解】
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
// 	freopen("ftree.in","r",stdin);
// 	freopen("ftree.out","w",stdout);
    int x, y;
    cin >> x >> y;
    if(x == y)
    {
        cout << "=";
        return 0;
    }
    if(x == 1)
        cout << "<";
    else if(y == 1)
        cout << ">";
    else if(x == 2 && y == 3)
    	cout << "<";
    else if(x == 2 && y == 4)
        cout << "=";
    else if(x == 3 && y == 2)
        cout << ">";
    else if(x == 4 && y == 2)
		cout << "=";
    else
    {
        if(x > y)
            cout << "<";
        else
            cout << ">";
    }
    return 0;
}
```

---

## 作者：两年打铁 (赞：1)

蒟蒻并不会~~快速幂~~,不会~~数学~~,更不懂什么是~~OI~~
但是这道题的代码确实很

# 短
我们对于x的y次和y的x次，只需直接取log，再进行判断

# 显然
这是正确的
但是由于log有精度误差，所以在判断的时候要注意。


------------

```
#include<bits/stdc++.h>
using namespace std;
int x,y;
int main()
{
	cin>>x>>y;
	double a,b,c,d,e;
	a=x*log(y);
	b=y*log(x);
	if(a>b+1e-6)puts("<");//对log精度的补差
	else if(a+1e-6<b)puts(">");//对log精度的补差
	else puts("=");
}
```

---

## 作者：小菜鸟 (赞：1)

本题可以把x^y与y^x比较转为比log(x^y),log(y^x)  
由log性质可知log(x^y)=y log(x)………………  
话不多说，上无特判AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long x,y;
long double lx,ly;
int main(int argc,char **argv)
{
	scanf("%I64d%I64d",&x,&y);
	lx=y*log(x);
	ly=x*log(y);
	if(abs(lx-ly)<1e-7){putchar('=');return 0;}
	if(lx>ly){putchar('>');return 0;}
	if(lx<ly){putchar('<');return 0;}
}
```

---

## 作者：Cesare (赞：0)

看到这道题，第一反应是快速幂。

但一看数据范围，应该是一道推结论的题目。

手算了一些较小的数据，发现大于二的数，就是那个大的幂小。

最后特判一下几个点，就完成了这道题。
```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
typedef long long ll;

ll x,y;

// ll poww(ll a,ll b) {
//     ll ans=1;
//     while(b) {
//         if(b&1)ans=ans*a;
//         a=a*a;b>>=1;
//     }
//     return ans;
// }


int main(){
    cin>>x>>y;
    if(x==y || (x==2 && y==4) || (x==4 && y==2)){cout<<"="<<endl;return 0;}
    if(x==2 && y==3 || x==1){cout<<"<"<<endl;return 0;}
    if(x==3 && y==2 || y==1){cout<<">"<<endl;return 0;}
    else if(x<y){cout<<">"<<endl;return 0;}
    else if(x>y){cout<<"<"<<endl;return 0;}
    return 0;
}
```

---

## 作者：Apocalypsis (赞：0)

2和4,2和3以及1特判
```
#include<bits/stdc++.h>
using namespace std;
int x,y;
int main(){
    cin>>x>>y;
    if(x==y) cout<<"=";
    else if(x==2&&y==4) cout<<"=";
    else if(x==4&&y==2) cout<<"=";
    else if(x==2&&y==3) cout<<"<";
    else if(x==3&&y==2) cout<<">";
    else if(x==1&&y!=1) cout<<"<";
    else if(x!=1&&y==1) cout<<">";
    else if(x<y) cout<<">";
    else cout<<"<";
}
```

---

## 作者：ZLightS (赞：0)


###	看到许多人都用了很强的（在我看来）数学方法...可惜作为蒟蒻的我并不会...所以就用了一种非常玄学的方法过了此题...具体就是可以认为当max（X,Y）>=10时，小的就一定大于大的...还有关于1的特判就没了。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll x,y,k;
int main()
{
	scanf("%I64d%I64d",&x,&y);
	if (x==y) 
		{
			printf("=\n");
			return 0;
		}
	if (x==1)
		{
			printf("<\n");
			return 0;
		}
	if (y==1)
		{
			printf(">\n");
			return 0;
		}
	k=min(x,y);
	if (max(x,y)<=10)
		{
			ll sumx=1,sumy=1;
			for (int i=1;i<=y;i++) sumx=sumx*x;
			for (int i=1;i<=x;i++) sumy=sumy*y;
			if (sumx<sumy)
				printf("<\n");
			else
			if (sumx==sumy) printf("=\n");
			else
				printf(">\n");
			return 0;
		}  //特判
	if (x>y)
		printf("<\n");
	else
		printf(">\n"); //玄学奇迹再现
	return 0;
}

```


---

