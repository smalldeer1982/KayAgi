# [USACO1.3] 号码锁 Combination Lock

## 题目背景

感谢 @[Fond_Dream](https://www.luogu.com.cn/user/321680) 提供五道 USACO 题目的标准题面。

## 题目描述

农夫约翰的奶牛不停地从他的农场中逃出来，导致了很多损害。为了防止它们再逃出来，他买了一只很大的号码锁以防止奶牛们打开牧场的门。

农夫约翰知道他的奶牛很聪明，所以他希望确保它们不会在简单地试了很多不同的号码组合之后就能轻易开锁。锁上有三个转盘，每个上面有数字 $1$ ~ $n$，因为转盘是圆的，所以 $1$ 和 $n$ 是相邻的。有两种能开锁的号码组合，一种是农夫约翰设定的，还有一种“预设”号码组合是锁匠设定的。但是，锁有一定的容错性，所以，在每个转盘上的数字都与一个合法的号码组合中相应的数字相距两个位置以内时，锁也会打开。

比如说，如果农夫约翰的号码组合是 ( $1$ , $2$ , $3$ )，预设号码组合是 ( $4$ , $5$ , $6$ )，在转盘被设定为 ( $1$ , $4$ , $5$)（因为这和农夫约翰的号码组合足够接近）或 ( $2$ , $4$ , $8$ )（因为这和预设号码组合足够接近）时可以打开锁。注意，( $1$ , $5$ , $6$ )并不会打开锁，因为它与任一号码组合都不够接近。

给出农夫约翰的号码组合和预设号码组合，请计算能够开锁的不同的号码组合的数目。号码是有序的，所以 ( $1$ , $2$ , $3$ ) 与 ( $3$ , $2$ , $1$ ) 不同。


## 说明/提示

#### 输入输出样例 1 解释

每个转盘的标号是 $1$ ~ $50$。农夫约翰的号码组合是 ( $1$ , $2$ , $3$ )，预设号码组合是 ( $5$ , $6$ , $7$ )。

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \leq n \leq 100$，$1 \leq x, y, z, a, b, c \leq n$。

## 样例 #1

### 输入

```
50
1 2 3
5 6 7
```

### 输出

```
249```

# 题解

## 作者：小白一枚 (赞：28)

枚举所有可能的锁，放心，不超时：



```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a, b, c, d, e, f, ans;
bool bo[105][105][105];
int main() {
    cin >> n;
    cin >> a >> b >> c;
    cin >> d >> e >> f;
    for (int i=a-2;i<=a+2;++i)
        for (int j=b-2;j<=b+2;++j)    \\循环数可能多了一些。
            for (int k=c-2;k<=c+2;++k)  \\但是放心，我试过了，不超时。
                if (!bo[(i+n)%n][(j+n)%n][(k+n)%n])
                    ans++, bo[(i+n)%n][(j+n)%n][(k+n)%n]=true;
    for (int i=d-2;i<=d+2;++i)
        for (int j=e-2;j<=e+2;++j)
            for (int k=f-2;k<=f+2;++k)
                if (!bo[(i+n)%n][(j+n)%n][(k+n)%n])
                    ans++, bo[(i+n)%n][(j+n)%n][(k+n)%n]=true;
    cout << ans << endl;
}
```

---

## 作者：VSEJGFB (赞：24)

题目问有多少种开锁的方法，显然如果没有重复的话，总方法数一定是5\*5\*2=**250**种。

因为有重复的所以要减去，问题就转化为**250-重复的数量**。

那么怎么计算重复的呢？

首先可以看出，约翰的号码和预设号码对应数字相距4以内才有可能重复。

比如样例中：约翰的号码的第一位的合法数字有49 50 1 2 3，预设号码第一位合法数字有3 4 5 6 7，重复了一个3；

根据**乘法原理**：一共重复的就是（第一位重复的数量）\*（第二位重复的数量）\*（第三位重复的数量）

这样代码就很简单了。。

另外**注意n<5**时要特判，答案是$n^3$

**代码**

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    int n,a[3],b[3];
    cin>>n;
    for(int i=0;i<3;i++) cin>>a[i];
    for(int i=0;i<3;i++) cin>>b[i];
    if(n<5){ cout<<n*n*n<<endl;return 0;} //特判 
    int ans=1;
    for(int i=0;i<3;i++){
        if(a[i]>b[i]) swap(a[i],b[i]);
        int k=min(b[i]-a[i],a[i]+n-b[i]);//计算距离
        if(k<5) ans*=(5-k);//如果距离<5，乘上重复的数量
        else ans=0;//否则没有重复的
    }
    cout<<250-ans<<endl;
    return 0;
}
```


---

## 作者：兰陵王 (赞：14)

其实这题只要从1-n循环3次，判断差是不是小于2或大于n-2（∵1与n首尾相连），
用几个abs就搞定。劝大家跟着我的思路来，别抄题解。

具体见代码：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main(){
    int n,a,b,c,d,e,f,i,j,k,sum=0;
    cin>>n;
    cin>>a>>b>>c>>d>>e>>f;
    for(i=1;i<=n;++i)
        for(j=1;j<=n;++j)
            for(k=1;k<=n;++k)  //循环查找符合情况
        if(((abs(i-a)<=2||abs(i-a)>=n-2)&&(abs(j-b)<=2||abs(j-b)>=n-2)&&(abs(k-c)<=2||abs(k-c)>=n-2))||((abs(i-d)<=2||abs(i-d)>=n-2)&&(abs(j-e)<=2||abs(j-e)>=n-2)&&(abs(k-f)<=2||abs(k-f)>=n-2)))sum++;
    //判断是否满足打开情况    
            cout<<sum;//输出情况数
            return 0;
}
```

还是很简单的啦!

[t01c05ca2ade4ec4fd4](桌面)

---

## 作者：zzqDeco (赞：4)

### 仔细看看题解，发现我的判断方法没人要（好像还要简单）
### 通过abs绝对值函数来做超简单！！！
```cpp
#include<iostream>
#include<cmath>//abs（）必须要用这个头文件
using namespace std;
struct X
{
	int x,y,z;
}A,B;
int N,ans;
bool a[110][110][110];
bool Compare(int i,int j,int k)
{
	if(abs(i-A.x)>=N-2||abs(i-A.x)<=2)//绝对值差小于2或者绝对值差大于n-2
	if(abs(j-A.y)>=N-2||abs(j-A.y)<=2)//同上 
	if(abs(k-A.z)>=N-2||abs(k-A.z)<=2)//同上
	{
		return 1;
	}
	if(abs(i-B.x)>=N-2||abs(i-B.x)<=2)//同上
	if(abs(j-B.y)>=N-2||abs(j-B.y)<=2)//同上
	if(abs(k-B.z)>=N-2||abs(k-B.z)<=2)//同上
	{
		return 1;
	}
	return 0;//不行返回0 
}
int main()
{
	cin>>N>>A.x>>A.y>>A.z>>B.x>>B.y>>B.z;
	for(int i=1;i<=N;i++)
	for(int j=1;j<=N;j++)
	for(int k=1;k<=N;k++)//范围太小，否则就要模拟
	{
		if(Compare(i,j,k))//判断 
		ans++;
	}
	cout<<ans;
}
```
### 当然模拟也不难
### 在允许值的上下2就可以（小心两个允许值的混用！！！）
### 大家也可以用那种方法做一做
~~垃圾的远古码风大家将就一下~~
（管理。。。原来的题解改了一点点为什么就过不了了）

---

## 作者：SKTT1Faker (赞：2)

连个p党的都没有，我来一个吧。

首先，这道题数据不大，100的3次方可以过，如果再大一点，就要用大神的数论了。

我们先3重循环，暴力搜，可以去除重复。

要注意的事：在1。。a的地方要特判。


```cpp
var
a,a1,a2,a3,a4,a5,a6,i,j,v,ans:longint;   俩个三组数据。
function ab(x,y:longint):longint;
begin
  if ((x=1) and (y=a)) or ((x=a) and (y=1)) then exit(1); ...................判1和a
  if ((x=1) and (y=a-1)) or ((x=a-1) and (y=1)) then exit(2);............. 判1和a-1.
  if ((x=2) and (y=a)) or ((x=a) and (y=2)) then exit(2);...................判2和a
  exit(abs(x-y));
end;
function pd(x,y,z:longint):boolean;
begin
  if (ab(x,a1)<=2) and (ab(y,a2)<=2) and (ab(z,a3)<=2) then exit(true);
  if (ab(x,a4)<=2) and (ab(y,a5)<=2) and (ab(z,a6)<=2) then exit(true);
  exit(false);
end;
begin
  readln(a);
  readln(a1,a2,a3);
  readln(a4,a5,a6);
  for i:=1 to a do
  for j:=1 to a do
  for v:=1 to a do
  if pd(i,j,v) then ans:=ans+1;   暴力，计数
  write(ans);..............输出
end.

```

---

## 作者：SUNCHAOYI (赞：1)

## 直接打暴力AC
```
#include<iostream>
#include<cmath>
//#include<fstream> 
using namespace std;
int main()
{
	//ifstream fin ("combo.in");
    //ofstream fout ("combo.out");
	int n,a,b,c,d,e,f,ans=0;
	cin>>n;
	cin>>a>>b>>c>>d>>e>>f;
	 for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k=1;k<=n;k++)
            {
            	if(((abs(i-a)<=2||abs(i-a)>=n-2)&&(abs(j-b)<=2||abs(j-b)>=n-2)&&(abs(k-c)<=2||abs(k-c)>=n-2))||((abs(i-d)<=2||abs(i-d)>=n-2)&&(abs(j-e)<=2||abs(j-e)>=n-2)&&(abs(k-f)<=2||abs(k-f)>=n-2)))ans++;//由题意得，符合条件，方案数加一 
			}
	cout<<ans<<endl;
	return 0; 
 } 
```


---

## 作者：Vatyr (赞：1)

看看题解貌似大家都是靠减或者乘的？我来发个不一样的~

先处理农夫的密码，再处理预设的，设d[i][j][k]表示（i j k )是否可开锁，能就设成1，否则是0.

把两个密码左两个右两个枚举一遍所有可以开锁的组合，最后在跑个n^3的大枚举。

因为n很小，所以时间很短（14ms！！！）但不希望加强数据，不然这个就跑不过了（逃

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int d[101][101][101];
int n;
inline int chg(int x)//用来处理环形所带来的一些烦人事
{
    if(x<=0)x=(5*n+x)%n;
    if(x==0)return n;
    if(x>n)return x%n;
    return x;
}
int main()
{
    cin>>n;
    int an=0;
    if(n==1)
    {
        cout<<1;
        return 0;
    }
    int a,b,c;
    cin>>a>>b>>c;
    for(int j=a-2;j<=a+2;j++)
    {
        for(int k=b-2;k<=b+2;k++)
        {
            for(int l=c-2;l<=c+2;l++)
            {
                int j1=chg(j);
                int k1=chg(k);
                int l1=chg(l);
                d[j1][k1][l1]=1;
            }
        }
    }
    cin>>a>>b>>c;
    for(int j=a-2;j<=a+2;j++)
    {
        for(int k=b-2;k<=b+2;k++)
        {
            for(int l=c-2;l<=c+2;l++)
            {
                int j1=chg(j);
                int k1=chg(k);
                int l1=chg(l);
                d[j1][k1][l1]=1;
            }
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k=1;k<=n;k++)
            an+=d[i][j][k];
    cout<<an;
    return 0;
}
```

---

## 作者：Violette (赞：0)

#### 设置布尔类型的三维数组flag，

在三重循环中，把误差在2以内的数所对应的三维数组的位置赋值为true。

最后，再用三重循环遍历所有可能的号码（1 <= N <= 100，三重循环不会超时），
累计它们的数量。

### （为了解决因此题起始值为1，模n之后可能会等于0，故可以设置一个函数，当这个值为0或负数，让它在取余之后再加上一个n）

函数代码如下：
```cpp
int gg(int m) 
{ 
if (m>0) return m%n?m%n:n;
else return (m%n)+n; 
}
```
最后，附上AC代码：

```cpp
#include<iostream>
using namespace std;
int n;
bool flag[110][110][110];
int gg(int m)
{ 
    if (m>0) return m%n?m%n:n;
    else return (m%n)+n;
}
int main() {
	cin>>n;
	int a,b,c,d,e,f,g;
	cin>>a>>b>>c>>d>>e>>f;
	for(int i=-2;i<=2;i++){
    	for(int j=-2;j<=2;j++){
       		for(int k=-2;k<=2;k++){
            	flag[gg(a+i)][gg(b+j)][gg(c+k)]=true;
            	flag[gg(d+i)][gg(e+j)][gg(f+k)]=true;
        	}
    	}
	} 
	int ans=0;
	for(int i=1;i<=n;i++){
    	for(int j=1;j<=n;j++){
        	for(int k=1;k<=n;k++){
            	if(flag[i][j][k]==true) ans++;
        	}
    	    }
	}
	cout<<ans;
    return 0;
}

```


---

## 作者：claire_cc (赞：0)

枚举所有可能，每种情况都可以看成是n进制的一个数
```
#include<iostream>
#include<algorithm>
#define pi 3.1415926535
#define ll long long
using namespace std;
int n;
set<ll>s;
ll transfer(int a,int b,int c)
{
    return c+b*n+a*n*n;
}
int main()
{
    int x,y,z,t,a,b,c;
    cin>>n;
    t=2;
    while(t--)
    {
        cin>>x>>y>>z;
        for(int i=-2;i<=2;i++)
        {
            for(int j=-2;j<=2;j++)
            {
                for(int k=-2;k<=2;k++)
                {
                    a=(i+x+n)%n;
                    b=(j+y+n)%n;
                    c=(k+z+n)%n;
                    s.insert(transfer(a,b,c));
                }

            }
        }
    }
    cout<<s.size();
    return 0;
}
```


---

## 作者：封禁用户 (赞：0)

此题最多只有250种情况，所以可以采用暴力方法求解。

那么我们只需要去重。

去重最简单的方法当然是使用`set`。

注意，在`set`内使用自定义类型时，必须重载`<`运算符。
```cpp
/*
ID: Anfangen
LANG: C++
PROG: combo
*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <stack>
#include <utility>
#include <functional>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define dec(i,a,b) for(int i=(a);i>=(b);--i)
#define endll putchar('\n');
#define RI register int 
#define gc() getchar()
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
inline ll read(){
    char ch=getchar();ll x=0,f=1;
    while(ch<'0'||ch >'9') {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while('0'<=ch&&ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
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
inline void printsp(ll p){
    print(p);
    putchar(' ');
}
struct trip{
	int first,second,third;
	trip(int _first,int _second,int _third){first=_first;second=_second;third=_third;}
	trip(){}
	//两个构造函数，用起来比较方便。
};
bool operator < (const trip &a,const trip &b){
	if(a.first!=b.first) return a.first<b.first;
	if(a.first==b.first&&a.second!=b.second) return a.second<b.second;
	if(a.first==b.first&&a.second==b.second) return a.third<b.third;
}//set如果使用自定义类型必须重载<运算符。
set<trip> st;//使用set去重
trip fj,de;
int n;	
int main(){
	n=read();
	fj.first=read(),fj.second=read(),fj.third=read();
	de.first=read(),de.second=read(),de.third=read();
	rep(i,fj.first-2,fj.first+2)
		rep(j,fj.second-2,fj.second+2)
			rep(k,fj.third-2,fj.third+2)
				st.insert(trip((i+n)%n,(j+n)%n,(k+n)%n));
	rep(i,de.first-2,de.first+2)
		rep(j,de.second-2,de.second+2)
			rep(k,de.third-2,de.third+2)
				st.insert(trip((i+n)%n,(j+n)%n,(k+n)%n));
	println(st.size());//只须输出集合内元素个数
	return 0;
}
```

---

## 作者：Shan＿Xian (赞：0)

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <cstdlib>
using namespace std;
int n,a[3],b[3],k=0,ans;
bool s(int x, int y)//枚举函数 
{
    int y1, y2, y3, y4;
    y1=y-2;
    if(y1<=0) y1+=n;
    y2=y-1;
    if(y2<=0) y2+=n;
    y3=y+1;
    if(y3>n) y3-=n;
    y4=y+2;
    if(y4>n) y4-=n;
    if(x==y1 || x==y2 || x==y || x==y3 || x==y4) return 1;//判断是否可以 
    return 0;
}
void init(){//输入 
    scanf("%d",&n);
    for(int i=1;i<=3;i++){
        scanf("%d",&a[i]);
    }
    for(int j=1;j<=3;j++){
        scanf("%d",&b[j]);
    }
}
void work(){//暴力枚举 
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int g=1;g<=n;g++){
                if(s(i,a[1])&&s(j,a[2])&&s(g,a[3])||s(i,b[1])&&s(j,b[2])&&s(g,b[3]))//判断条件 
                ans++;
                }
            }
        }
    }
        void output(){
            printf("%d",ans);
        }
int main(){
    //freopen("Combination Lock.in","r",stdin);
    //freopen("Combination Lock.out","w",stdout);
    init();
    work();
    output();
}
//这题没什么技术含量，主要是枚举条件要正确。
```

---

## 作者：f112358 (赞：0)

这道题还枚举的话就太懒了...（比我还懒）

主要是因为这题的时间复杂度不是O(n^3),不是O(n^2),也不是O(n)

而是根本跟n没关系.....

其实对于n>=5的情况，不考虑重叠，都是250种可能（2\*5^3）

只是两种密码重叠部分算重复了，减掉即可

最多只要计算不到150次

30行代码如下


```cpp
#include <iostream>
#include <cmath>
using namespace std;
int a[3][4][6];
int t[4];
int n;
bool restriction=true;
int main()
{
    cin>>n;
    for(int k=1;k<=2;k++)
        for(int i=1;i<=3;i++){ cin>>a[k][i][3]; if(a[k][i][3]>n) restriction=false; }
    if(!restriction) {cout<<0<<endl; return 0;    }
    if(n<5) {cout<<n*n*n<<endl; return 0;}
    for(int k=1;k<=2;k++)
        for(int i=1;i<=3;i++)
            for(int j=-2;j<=2;j++)
            {
                int x=a[k][i][3]+j; if(x==0) x=n; if(x==-1) x=n-1; if(x==n+1) x=1; if(x==n+2) x=2;
                a[k][i][j+3]=x;
            }
    for(int i=1;i<=3;i++)
        for(int j=1;j<=5;j++)
            for(int k=1;k<=5;k++)
                if(a[1][i][j]==a[2][i][k]) { t[i]++; continue;}
    cout<<250-t[1]*t[2]*t[3];
    return 0;
}

```

---

## 作者：a___ (赞：0)

此题不难

数据太弱，看楼下3重1~n循环居然没超时，建议加强n值>100

思路：从每个密码输-2~+2依次过一遍，这样只有2\*4\*4\*4的循环

```cpp
#include <iostream>
using namespace std;
bool bo[110][110][110];//记录是否记录过（避免重合）
int a1,a2,a3,//密码①
b1,b2,b3,//密码②
n,t;//n，n；t，密码数量
inline int gf (int a)//此函数将a值确定在1~n内（因为（因为是圆的，所以1前是n，n后是1））
{
    if (a>0)return a%n?a%n:n;//对于一个正数，只考虑大于n的出界。这时，直接%n即可。但，当整除时，应按n算（举个例子：a:100,n:100,此时a应为100而非0）
    else return (a%n)+n;//对于一个负数，只考虑<1越界。这时，需%n+n（例：a:-3,n:3,a=(a%n)+n=0+3=3）
} 
int main()
{
    cin>>n>>a1>>a2>>a3>>b1>>b2>>b3;//输入
    int i,j,k,ii,jj,kk;//前三循环变量，后三为前三规范数
    for (i=a1-2;i<=a1+2;i++)
    {
        ii=gf(i);//规范i
        for (j=a2-2;j<=a2+2;j++)
        {
            jj=gf(j);//规范j
            for (k=a3-2;k<=a3+2;k++)
            {
                kk=gf(k);//规范k
                if (!bo[ii][jj][kk])t++,bo[ii][jj][kk]=1;//若没加过，加一次
            }
        }
    }
    for (i=b1-2;i<=b1+2;i++)
    {
        ii=gf(i);
        for (j=b2-2;j<=b2+2;j++)
        {
            jj=gf(j);
            for (k=b3-2;k<=b3+2;k++)
            {
                kk=gf(k);                                                                                     //同上
                if (!bo[ii][jj][kk])t++,bo[ii][jj][kk]=1;
            }
        }
    }
    cout<<t<<endl;//输出
    return 0;
}
```

---

## 作者：「QQ红包」 (赞：0)

这题怎可可以没有题解



/\*
ID: ylx14274

PROG: combo

LANG: C++

\*/
```cpp
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
int a[7];//存密码，1~3约翰的号码组合，4~6预设号码组合
int n,i,j,k,sum=0; 
int pd (int nn,int bb)//判断是否位置差在2个之间 
{
    int hehe=abs(a[bb]-nn);//记得加绝对值 
    if ((hehe<=2)||(hehe)>=n-2)//如果与号码组合的这一位位置差在2个以内 
        return 1;//返回1
    return 0; 
} 
int main() 
{
    freopen("combo.in","r",stdin);
    freopen("combo.out","w",stdout); //自行删
    scanf("%d",&n);//读锁的数字个数
    if (n<=5)//此时所有位置离正确的数字位置相差不会超过2。 
    {
        cout<<n*n*n<<endl;//输出n的三次方 
        return 0;//退出 
    }
    for (i=1;i<=6;i++)
        scanf("%d",&a[i]);//读密码 
    for (i=1;i<=n;i++)//疯狂的枚举 
        for (j=1;j<=n;j++)
            for (k=1;k<=n;k++)
            {
                if (((pd(i,1)==1)&&(pd(j,2)==1)&&(pd(k,3)==1))//如果三个数字和约翰的号码组合位置差在2个以内
                ||/*或者*/((pd(i,4)==1)&&(pd(j,5)==1)&&(pd(k,6)==1))) //如果三个数字和设号码组合位置差在2个以内
                sum++;//计数 
            } 
    cout<<sum<<endl; 
    return 0;
}

```

---

