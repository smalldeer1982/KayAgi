# Tests Renumeration

## 题目描述

全伯兰德国家信息学奥林匹克竞赛刚刚结束！弗拉基米尔想把这场竞赛上传到一个受欢迎的网站 Codehorses 上作为练习题。

然而，竞赛的存档文件非常混乱，比如，测试文件都是随意命名的，毫无规律。

弗拉基米尔希望重命名这些测试文件，使它们的名称是从 1 开始的连续整数命名，即 "1", "2", ..., " $ n $ "，其中 $ n $ 是测试文件的总数。

有些文件包含示例测试（样例），另外一些则是常规测试。可能所有测试都是示例，也可能没有示例。弗拉基米尔想要通过重命名文件，使示例测试排在前面，后面的全是常规测试。

弗拉基米尔可以使用的唯一操作是“move”命令。他想编写一个脚本文件，格式为每行 "move file\_1 file\_2"——表示将文件 "file\_1" 重命名为 "file\_2"。若在执行命令时已存在文件 "file\_2"，就覆盖它。执行后，"file\_1" 将不存在，而 "file\_2" 拥有原本 "file\_1" 的内容。

请帮助弗拉基米尔编写一个脚本文件，使得执行后的结果：

- 所有示例测试的文件名为 "1", "2", ..., " $ e $ "，其中 $ e $ 是示例测试的数量；
- 其余是常规测试文件，文件名为 " $ e+1 $ ", " $ e+2 $ ", ..., " $ n $ "，其中 $ n $ 是所有测试文件的总数。

## 样例 #1

### 输入

```
5
01 0
2 1
2extra 0
3 1
99 0
```

### 输出

```
4
move 3 1
move 01 5
move 2extra 4
move 99 3
```

## 样例 #2

### 输入

```
2
1 0
2 1
```

### 输出

```
3
move 1 3
move 2 1
move 3 2```

## 样例 #3

### 输入

```
5
1 0
11 1
111 0
1111 1
11111 0
```

### 输出

```
5
move 1 5
move 11 1
move 1111 2
move 111 4
move 11111 3
```

# 题解

## 作者：iyaang (赞：2)

[心动的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17640446.html)

[题目链接](https://www.luogu.com.cn/problem/CF858E)

一点模拟下下火。首先一定不能覆盖的，只能一点一点挪。将已经在合法位置上的去掉，剩下的测试分为四类：

1. 不碍事的样例测试。
2. 不碍事的常规测试。
3. 占据了样例测试位置的常规测试。
4. 占据了常规测试位置的样例测试。

将 $1 \sim n$ 中还未使用的空闲位置记录下来，结论是**只需要**至少一个空闲位置我们就能以最优秀的方案构造移动方法。假如说有一个空闲位置，那么我们选择位置对应的那一类测试中的某一个放入其中（例如这个空闲位置本应放样例测试，那么我们可以从 $1$ 或 $4$ 类测试中挑选一个放到这个位置）。显然一定存在至少一个这种测试，否则局面一定全部合法。那么就会导致两种情况：释放出了一个另一类测试的空闲位置（例如选择 $4$ 类测试，就会释放出一个常规测试的位置），或者这个位置被使用，消耗掉了一个空闲位置（选择 $1$ 类测试）。因此只要优先调整 $3/4$ 类测试，最后再放 $1/2$ 类测试即可，事实上每个 $1/2$ 类测试都会对应一个空余的位置。如果起初局面并不存在空闲的位置，那么就需要手动先腾出来一个空闲位置（话说这个位置的名称怎么只能六位啊，不能整活了）。记最初有 $k$ 个位置不合法，按照上述操作只需要 $k$ 或 $k+1$ 轮操作就能解决问题。这个轮数显然是最优的，因为不可能以少于 $k$ 轮的方案完成任务，需要额外一次操作当且仅当初始局面不合法且没有空位。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
#define gcd(x,y) (__gcd((x),(y)))
#define lcm(x,y) ((x)*(y)/gcd((x),(y)))
#define lg(x,y)  (__lg((x),(y)))
using namespace std;
 
namespace FastIO
{
    template<typename T=int> inline T read()
    {
        T s=0,w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        return s*w;
    }
    template<typename T> inline void read(T &s)
    {
        s=0; int w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        s=s*w;
    }
    template<typename T,typename... Args> inline void read(T &x,Args &...args)
    {
        read(x),read(args...);
    }
    template<typename T> inline void write(T x,char ch)
    {
        if(x<0) x=-x,putchar('-');
        static char stk[25]; int top=0;
        do {stk[top++]=x%10+'0',x/=10;} while(x);
        while(top) putchar(stk[--top]);
        if(ch!='~') putchar(ch);
        return;
    }
}
using namespace FastIO;

namespace MTool
{   
    #define TA template<typename T,typename... Args>
    #define TT template<typename T>
    static const int Mod=1e9+7;
    TT inline void Swp(T &a,T &b) {T t=a;a=b;b=t;}
    TT inline void cmax(T &a,T b) {a=max(a,b);}
    TT inline void cmin(T &a,T b) {a=min(a,b);}
    TA inline void cmax(T &a,T b,Args... args) {a=max({a,b,args...});}
    TA inline void cmin(T &a,T b,Args... args) {a=min({a,b,args...});}
    TT inline void Madd(T &a,T b) {a=a+b>=Mod?a+b-Mod:a+b;}
    TT inline void Mdel(T &a,T b) {a=a-b<0?a-b+Mod:a-b;}
    TT inline void Mmul(T &a,T b) {a=a*b%Mod;}
    TT inline void Mmod(T &a) {a=(a%Mod+Mod)%Mod;}
    TT inline T Cadd(T a,T b) {return a+b>=Mod?a+b-Mod:a+b;}
    TT inline T Cdel(T a,T b) {return a-b<0?a-b+Mod:a-b;}
    TT inline T Cmul(T a,T b) {return a*b%Mod;}
    TT inline T Cmod(T a) {return (a%Mod+Mod)%Mod;}
    TA inline void Madd(T &a,T b,Args... args) {Madd(a,Cadd(b,args...));}
    TA inline void Mdel(T &a,T b,Args... args) {Mdel(a,Cadd(b,args...));}
    TA inline void Mmul(T &a,T b,Args... args) {Mmul(a,Cmul(b,args...));}
    TA inline T Cadd(T a,T b,Args... args) {return Cadd(Cadd(a,b),args...);}
    TA inline T Cdel(T a,T b,Args... args) {return Cdel(Cdel(a,b),args...);}
    TA inline T Cmul(T a,T b,Args... args) {return Cmul(Cmul(a,b),args...);}
    TT inline T qpow(T a,T b) {int res=1; while(b) {if(b&1) Mmul(res,a); Mmul(a,a); b>>=1;} return res;}
    TT inline T qmul(T a,T b) {int res=0; while(b) {if(b&1) Madd(res,a); Madd(a,a); b>>=1;} return res;}
    TT inline T spow(T a,T b) {int res=1; while(b) {if(b&1) res=qmul(res,a); a=qmul(a,a); b>>=1;} return res;}
    TT inline void exgcd(T A,T B,T &X,T &Y) {if(!B) return X=1,Y=0,void(); exgcd(B,A%B,Y,X),Y-=X*(A/B);}
    TT inline T Ginv(T x) {T A=0,B=0; exgcd(x,Mod,A,B); return Cmod(A);}
    #undef TT
    #undef TA
}
using namespace MTool;
 
inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    return;
}
 
bool Mbe;
 
namespace LgxTpre
{
    static const int MAX=100010;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    
    int n,exanum,flag,con,ans;
    bool used[MAX];
    pair<string,int> a[MAX];
    queue<int> qualidreg,qualidexa,exceedreg,exceedexa;
    queue<int> resreg,resexa;
    
    inline void lmy_forever()
    {
    	auto get=[&](string s)->int
    	{
    		int len=s.size(),num=0;
    		for(int i=0;i<len;++i) if(!isdigit(s[i])) return 0;
    		if(s[0]=='0') return 0;
    		for(int i=0;i<len;++i) (num*=10)+=(s[i]^48);
    		return num;
		};
		
    	cin>>n,con=1;
    	for(int i=1;i<=n;++i) cin>>a[i].fi>>a[i].se,exanum+=a[i].se;
    	for(int i=1;i<=n;++i)
		{
			int num=get(a[i].fi);
			if(num>0&&num<=n)
			{
				used[num]=1;
				if(num<=exanum&&a[i].se==0) qualidreg.emplace(num);
				if(num> exanum&&a[i].se==1) qualidexa.emplace(num);
			}
			else
			{
				if(a[i].se==0) exceedreg.emplace(i);
				if(a[i].se==1) exceedexa.emplace(i);
			}
		}
		ostringstream ccout;
		for(int i=1;i<=n;++i) if(!used[i]) i<=exanum?resexa.emplace(i):resreg.emplace(i);
		if(resreg.empty()&&resexa.empty()&&qualidreg.size()&&qualidexa.size()) ++ans,flag=1,ccout<<"move "<<qualidreg.front()<<" lmy999"<<endl,resexa.emplace(qualidreg.front()),qualidreg.pop();
		while(con)
		{
			con=0;
			while(resexa.size()&&qualidexa.size()) con=1,++ans,ccout<<"move "<<qualidexa.front()<<" "<<resexa.front()<<endl,resreg.emplace(qualidexa.front()),qualidexa.pop(),resexa.pop();
			while(resreg.size()&&qualidreg.size()) con=1,++ans,ccout<<"move "<<qualidreg.front()<<" "<<resreg.front()<<endl,resexa.emplace(qualidreg.front()),qualidreg.pop(),resreg.pop();
		}
		while(exceedreg.size()) ++ans,ccout<<"move "<<a[exceedreg.front()].fi<<" "<<resreg.front()<<endl,exceedreg.pop(),resreg.pop();
		while(exceedexa.size()) ++ans,ccout<<"move "<<a[exceedexa.front()].fi<<" "<<resexa.front()<<endl,exceedexa.pop(),resexa.pop();
		if(flag) ++ans,ccout<<"move lmy999 "<<resreg.front()<<endl;
		cout<<ans<<endl<<ccout.str()<<endl;
	}
}

bool Med;

signed main() 
{
//  file();
    fprintf(stderr,"%.3lf MB\n",abs(&Med-&Mbe)/1048576.0);
    int Tbe=clock();
    LgxTpre::lmy_forever();
    int Ted=clock();
    cerr<<1e3*(Ted-Tbe)/CLOCKS_PER_SEC<<" ms\n";
    return (0-0);
}
```

---

