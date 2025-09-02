# Vasya and Types

## 题目描述

Programmer Vasya is studying a new programming language &K\*. The &K\* language resembles the languages of the C family in its syntax. However, it is more powerful, which is why the rules of the actual C-like languages are unapplicable to it. To fully understand the statement, please read the language's description below carefully and follow it and not the similar rules in real programming languages.

There is a very powerful system of pointers on &K\* — you can add an asterisk to the right of the existing type $ X $ — that will result in new type $ X* $ . That is called pointer-definition operation. Also, there is the operation that does the opposite — to any type of $ X $ , which is a pointer, you can add an ampersand — that will result in a type $ &amp;X $ , to which refers $ X $ . That is called a dereference operation.

The &K\* language has only two basic data types — void and errtype. Also, the language has operators typedef and typeof.

- The operator "typedef $ A $ $ B $ " defines a new data type $ B $ , which is equivalent to $ A $ . $ A $ can have asterisks and ampersands, and $ B $ cannot have them. For example, the operator typedef void\*\* ptptvoid will create a new type ptptvoid, that can be used as void\*\*.
- The operator "typeof $ A $ " returns type of $ A $ , brought to void, that is, returns the type void\*\*...\*, equivalent to it with the necessary number of asterisks (the number can possibly be zero). That is, having defined the ptptvoid type, as shown above, the typeof ptptvoid operator will return void\*\*.

An attempt of dereferencing of the void type will lead to an error: to a special data type errtype. For errtype the following equation holds true: errtype\* $ = $ &errtype $ = $ errtype. An attempt to use the data type that hasn't been defined before that will also lead to the errtype.

Using typedef, we can define one type several times. Of all the definitions only the last one is valid. However, all the types that have been defined earlier using this type do not change.

Let us also note that the dereference operation has the lower priority that the pointer operation, in other words $ &amp;T* $ is always equal to $ T $ .

Note, that the operators are executed consecutively one by one. If we have two operators "typedef &void a" and "typedef a\* b", then at first a becomes errtype, and after that b becomes errtype\* = errtype, but not &void\* = void (see sample 2).

Vasya does not yet fully understand this powerful technology, that's why he asked you to help him. Write a program that analyzes these operators.

## 说明/提示

Let's look at the second sample.

After the first two queries typedef the b type is equivalent to void\*, and с — to void\*\*.

The next query typedef redefines b — it is now equal to &b = &void\* = void. At that, the с type doesn't change.

After that the с type is defined as &&b\* = &&void\* = &void = errtype. It doesn't influence the b type, that's why the next typedef defines c as &void\* = void.

Then the b type is again redefined as &void = errtype.

Please note that the c type in the next query is defined exactly as errtype\*\*\*\*\*\*\* = errtype, and not &void\*\*\*\*\*\*\* = void\*\*\*\*\*\*. The same happens in the last typedef.

## 样例 #1

### 输入

```
5
typedef void* ptv
typeof ptv
typedef &&ptv node
typeof node
typeof &ptv
```

### 输出

```
void*
errtype
void
```

## 样例 #2

### 输入

```
17
typedef void* b
typedef b* c
typeof b
typeof c
typedef &b b
typeof b
typeof c
typedef &&b* c
typeof c
typedef &b* c
typeof c
typedef &void b
typeof b
typedef b******* c
typeof c
typedef &&b* c
typeof c
```

### 输出

```
void*
void**
void
void**
errtype
void
errtype
errtype
errtype
```

# 题解

## 作者：Empty_Dream (赞：2)

# CF87B 解题报告

## 题意

&K* 是一种编程语言，语言只有两种基本数据类型 void 和 errtype。此外，该语言具有运算符 typedef 和 typeof。

typedef 和 typeof 具体含义见[题面](https://www.luogu.com.cn/problem/CF87B)，类似于 c++ 中的定义变量和查看变量对应变量类型，就是一个映射关系。

对于每一次 typeof，输出对应的类型，如果匹配不到，那么输出 `errtype`。

## 分析

很明显是一道模拟题，对于每一个 typedef 的定义，通过 map 记录对应类型 `*` 的个数和 `&` 的个数差。对于 typeof，将这个变量按 typedef 的方法看 map 中是否存储着对应的变量名，输出时还原 `*`。

对于不合法的情况，考虑样例，发现在变量类型前不能有 `&` 只能在后面有 `*`，所以在记录这两个字符个数差的时候，如果是负数，那么就是不合法的。这个发现也减少了代码量，在还原的时候只需要还原 `*` 就好了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
string act;
map<string,int> mp;

int type(string s){
	int cnt1 = 0, cnt2 = 0;
	while (s[0] == '&'){//题目确保了'&'一定在字符串前面，'*'在后面
		cnt1++;
		s.erase(0, 1);
	}
	while (s[s.size() - 1] == '*'){
		cnt2++;
		s.erase(s.size() - 1, 1);
	}
	if (mp.count(s) == 0) return -1;//之前没有定义过这种类型
	int t = mp[s];
	if (t == -1) return -1;//如果是errtype
	t += cnt2 - cnt1;//记录'*'和'&'的数量差
	if (t < 0) t = -1;//'*'比'&'少 不合法
	return t;
}

void run_typedef(){
	string s1, s2;
	cin >> s1 >> s2;
	mp[s2] = type(s1);
} 

void run_typeof(){
	string s;
	cin >> s;
	int t = type(s);//还原出要加多少个'*'或者不合法
	if (t == -1) cout << "errtype\n";
	else{
		cout << "void";
		for(int i = 1; i <= t; i++) cout << "*";
		cout << endl;
	}
}
int main(){
    mp["void"] = 0, mp["errtype"] = -1;
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> act;
		if (act == "typedef") run_typedef();
		if (act == "typeof") run_typeof();
	}
	return 0;
}
```

---

## 作者：The_Godfather (赞：2)

## Problem
[题目传送门](https://www.luogu.com.cn/problem/CF87B)

题目大意：&K* 是一种编程语言，&K* 语言只有两种基本数据类型 void 和 errtype 和两种运算符 * 和 &。
## Solution

有两种语言，分别是 ```typedef A B``` 和 ```typedef A```。

因为是模拟这里只是提供相关思路：

- 可以考虑对于某个定义类型，只需统计 ** 的个数。

- 对于 & 的个数，用 * 的个数减去。

- 最后对于某类型如果 * 的个数小于等于0，直接输出 errtype，如果个数大于0，输出 void 类型。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
namespace Dino {
    const int maxn = 500010;
    int n, ans, tmp, cnt;
    int a[maxn], c[maxn];
    char s[maxn], ss[maxn], sss[maxn];
    map<string, int> mp;
    string str1, str2;
    auto work = []()
    {
        while (scanf("%d", &n) != EOF)
        {
            mp.clear();
            mp["void"] = 1;
            for (int i = 0; i < n; i++)
            {
                scanf("%s", s);
                if (strcmp(s, "typedef") == 0)
                {
                    scanf("%s %s", ss, sss);
                    int l = strlen(ss);
                    int ans = 0, cnt = 0;
                    str1 = "";
                    for (int i = 0; i < l; i++)
                    {
                        if (ss[i] == '&')
                            ans--;
                        else if (ss[i] == '*')
                            ans++;
                        else
                            str1 += ss[i];
                    }
                    cnt = mp[str1];
                    if (cnt > 0)
                        cnt += ans;
                    else
                        cnt = 0;
                    mp[(string)sss] = cnt;
                }
                else
                {
                    scanf("%s", ss);
                    int l = strlen(ss);
                    int ans = 0, cnt = 0;
                    str1 = "";
                    for (int i = 0; i < l; i++)
                    {
                        if (ss[i] == '&')
                            ans--;
                        else if (ss[i] == '*')
                            ans++;
                        else
                            str1 += ss[i];
                    }
                    cnt = mp[str1];
                    if (cnt > 0)
                        cnt += ans;
                    else
                        cnt = 0;
                    if (cnt <= 0)
                        puts("errtype");
                    else
                    {
                        printf("void");
                        for (int i = 1; i < cnt; i++)
                            printf("*");
                        puts("");
                    }
                }
            }
        }
    };
}
int main()
{
    fastio;
    return Dino::work(), 0;
}
```

---

## 作者：_Lazy_zhr_ (赞：0)

字符串模拟题，~~自己因神秘 RE 卡了好久（后来发现是访问到下标为 $-1$……）。~~

我们用一个 map 记录每个类型 `*` 的个数。特别的，`errtype` 为 $-1$。

对于每个 `typedef` 操作，我们先将 $A$（$A$ 和 $B$ 的定义与题面相同。）左边的 `&` 和右边的 `*` 去掉，然后开始判断：如果 $A$ 类型未定义或 $A$ 类型为 `errtype`，那么 $A$ 类型和 $B$ 类型都为 `errtype`；否则 $B$ 类型的 `*` 个数为 $A$ 类型化简（指将 `*` 和 `&` 操作都执行了。）后的 `*` 个数，若这个个数小于 $0$，就说明 $B$ 类型为 `errtype`。

对于每个 `typeof` 操作，我们将 $A$ 化简，如果化简后为 `errtype`，就输出 `errtype`，否则输出 `void` 加 $A$ 类型化简后的 `*` 个数个 `*`。

[AC 记录](https://codeforces.com/contest/87/submission/307952325)。

code（C++20）（这里还用了 set，貌似多此一举了。）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid ((l+r)>>1)
#define pii pair<int,int>
#define lowbit(t) (t&(-t))
#define abs(x) ((x)>0?(x):(-(x)))
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define y1 yy1
mt19937_64 Rand(chrono::steady_clock::now().time_since_epoch().count());
const int mod1=998244353,mod2=1e9+7;
const int MAXN=2e5+5;
const int base=23333,mod_h=1e15+1e12+998244353+114514;
const int mx[4]={-1,1,0,0};
const int my[4]={0,0,-1,1};
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	} while(ch>='0'&&ch<='9'){
		x=x*10+ch-48;
		ch=getchar();
	} return x*f;
}
inline void write(int x){
	if(x<0) putchar('-'),x*=-1;
	if(x<10) putchar(x+'0');
	else write(x/10),putchar(x%10+'0');
}
unordered_map<int,int> hash_map;
bool ha(string str){
	int has=0;
	for(int i=0;i<(int)str.size();i++) has=(has*base+(int)str[i])%mod_h;
	if(!hash_map[has]){
		hash_map[has]++;
		return true;
	} else return false;
}
//以上为缺省源--------------------------------------------------
const string def="typedef",of="typeof",err="errtype";
int q;
set<string> s[10005],er;
map<string,int> f;
void solve(){
	cin>>q;
	s[0].insert("void");
	f["void"]=0;
	for(int t=1;t<=q;t++){
		string op,a,b;
		cin>>op>>a;
		if(op=="stop") return ;
		if(op==def){
			cin>>b;
			int _0=0,_1=0;
			string over="";//去除 & 和 * 后的 a。
			for(int i=0;i<a.size();i++) if(a[i]=='&') _0++;
			else if(a[i]=='*') _1++;
			else over=over+a[i];
			int cnt=f[over],w=f[b];
			if(cnt==-1){//a 是 err
				if(w==-1) er.erase(er.find(b));
				else if(s[w].find(b)!=s[w].end()) s[w].erase(s[w].find(b));//b 之前存在过。
				er.insert(b);
				f[b]=-1;
			} else if(s[cnt].find(over)==s[cnt].end()){//之前没 a。
				if(w==-1) er.erase(er.find(b));
				else if(s[w].find(b)!=s[w].end()) s[w].erase(s[w].find(b));//b 之前存在过。
				er.insert(b);
				f[b]=-1;
				er.insert(a);
				f[a]=-1;
			} else{//之前有 a
				if(w==-1) er.erase(er.find(b));
				else if(s[w].find(b)!=s[w].end()) s[w].erase(s[w].find(b));//b 之前存在过。
				int now=cnt+_1-_0;
				if(now<0){
					er.insert(b);
					f[b]=-1;
				} else{
					s[now].insert(b);
					f[b]=now;
				}
			}
		} else{
			int _0=0,_1=0;
			string over="";//去除 & 和 * 后的 a。
			for(int i=0;i<a.size();i++) if(a[i]=='&') _0++;
			else if(a[i]=='*') _1++;
			else over=over+a[i];
			int 不知道取什么=f[over];
			if(不知道取什么<0) cout<<err<<"\n";
			else if(s[不知道取什么].find(over)==s[不知道取什么].end()) cout<<err<<"\n";
			else{
				不知道取什么+=_1-_0;
				if(不知道取什么<0) cout<<err<<"\n";
				else{
					cout<<"void";
					while(不知道取什么--) cout<<'*';
					cout<<"\n";
				}
			}
		}
	} return ;
}
//以下为缺省源--------------------------------------------------
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
//	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
	int T=1;
//	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：PDAST (赞：0)

## 题意
一个人在学一种新的语言，在这个语言里，你可以做以下两种操作：
+ 给一个变量的赋值（`typedef` $A$ $B$）；
+ 输出这个变量。（`typeof` $A$）。

在这个语言里只有两种基础值：`void` 和 `errtype`。他还有强大的指针系统，你可以给一个变量用 `*` 加上若干个指针，也可以用 `&` 去掉若干个指针，赋值规则如下：
+ 当 `*` 的个数小于 `&` 的个数时，该变量会被永久赋值为 `errtype`；
+ 有一种行为被称为未定义行为，即你在这个变量未赋值时将其用于赋值；
+ 当你做了一个未定义行为时，被赋值和赋值或被输出的变量将被临时赋值为 `errtype`；
+ 任何对 `errtype` 进行的操作视为无效。

给定 $N$ 次操作，请输出每次 `typeof` 将输出的值。
## 思路
恶心的模拟。我们把每个变量的 `*` 数和 `&` 数记录下来，每次赋值，令被赋值变量的 `*` 数减 `&` 数加上新增的 `*` 数减 `&` 数为 $tmp$，如果 $tmp$ 小于零，则这个变量将会变成 `errtype`，否则就把这个数的值设为 $tmp$。最后输出 $tmp$ 个 `*` 就行了。
## 代码
```cpp
#include<bits/stdc++.h>
#define makepii pair<int,int>pii
using namespace std;
map<string,bool>f;
map<string,int>type;
pair<int,int>countnum(string st){
	int i=0,j=st.size()-1;
	while(i<j&&st[i]=='&')i++;
	while(j>i&&st[j]=='*')j--;
	return {i,st.size()-j-1};
}
string add(string st,int a,int b){
	while(a--)st="&"+st;
	while(b--)st+="*";
	return st;
}
string doit(int x){
	if(x<0)return "errtype";
	return add("void",0,x);
}
int main(){
	int T;
	cin>>T;
	f["void"]=1;
	type["void"]=0;
	while(T--){
		string s,a,b;
		cin>>s>>a;
		makepii=countnum(a);
		a=a.substr(pii.first,a.size()-pii.first-pii.second);
		if(s=="typeof"){
			if(!f[a])cout<<"errtype\n";
			else cout<<doit(type[a]+pii.second-pii.first)<<"\n";
		}else{
			cin>>b;
			type[b]=type[a]+pii.second-pii.first;
			if(!f[a])type[b]=-2147400000;
			if(type[b]<0)type[b]=-2147400000;
			f[b]=1;
		}
	}
} 
```

---

## 作者：Peaky (赞：0)

按照惯例，应该现有[传送门](https://www.luogu.com.cn/problem/CF87B)。  
### 简单的分析
这道题的 * 与 & 很像是括号匹配的左右括号，但是如果有多余的 & 就会把类型改为 errtype 。

### AC CODE
```cpp
#include<bits/stdc++.h>
#define f first
#define s second
using namespace std;
const int N=2e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/ 
int n,c1,c2;
string x,a,b;
map<string,pair<int,bool>>mp; 
int main(){
	mp["void"]={0,1};
	cin>>n;
	while(n--){
		cin>>x>>a;
		c1=c2=0;
		for(int i=0;i<a.size();++i)c1+=(a[i]=='&'),c2+=(a[i]=='*');
		a=a.substr(c1,a.size()-c1-c2);
		if(x=="typedef"){
			cin>>b;
			mp[b].f=mp[a].f+c2-c1;
			if(mp[b].f<0||!mp[a].s)mp[b].f=-2e9;
			mp[b].s=1;
		}
		else{
			if(mp[a].f<0||!mp[a].s||mp[a].f+c2-c1<0)puts("errtype");
			else{
				cout<<"void";
				for(int i=1;i<=mp[a].f+c2-c1;++i)cout<<'*';
				cout<<endl;
			}
		}
	}
	return 0;
}
```

---

## 作者：XCH_0803 (赞：0)

# 思路

大模拟，理清思路就简单了。这里用三个 map，一个用来存定义 $B$ 的类型 $A$，一个用来存 $B$ 里面星号的个数，vis 用于存储该类型是否出现过。每次先计算最后应该剩下的星号个数，如果小于 $0$，则说明该类型就是错误类型，如果星号个数大于等于 $0$ 则存入 map。处理完后判断是否只剩 `void `，如果只剩 `void` 则不用存 map，反之要存入定义他的 $A$ 类型和 $A$ 类型对应的星号个数 $+$ 现有的星号个数即可。

话不多说，上代码！！！ 

UPD ON 2023-4-17 修改了一处小错误

# 代码

```c
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
const int N=150;
const int inf=0x3f3f3f3f;
typedef long long ll;
map<string,int>mp;
map<string,string>mp1;
map<string,int>vis;
int main(){
	int t; 
	cin>>t;
	while(t--){
		string op;
		cin>>op;
		if(op=="typedef"){
			string a,b;
			cin>>a>>b;
			int l=0,r=a.size()-1,r1=0;
			while(a[l]=='&') {
				l++;
			}
			while(a[r]=='*'){
				r--,r1++;
			}
			string ty="";
			for(int i=l;i<=r;i++){//处理去掉&*后的类型名
			  ty+=a[i];
			}
			if(ty=="void"){//如果是void则不用加上父级的星号个数
				mp1[b]="void";
				mp[b]=r1-l;
				vis[b]=1;
			}
			else{//如果不是则需要加上父级个数，如果父级为errtype,那么他也是错误类型
				mp1[b]=ty;
				if(mp[ty]>=0&&vis[ty]){
				  mp[b]=mp[ty]+(r1-l);
				}
				else{ 
				  mp[b]=-1;
				}
				vis[b]=1;//标记是否出现过
			}
		}
		else{
			string a;
			cin>>a;
			int l=0,r=a.size()-1,r1=0;
			while(a[l]=='&'){
				l++;
			}
			while(a[r]=='*'){
				r--,r1 ++;
			}
			string ty="";
			for(int i=l;i<=r;i++){//这里还是先处理，处理完之后再加上父级的星号个数
			  ty+=a[i];
			}
			if(!vis[ty]){//如果没有出现过则需要判断是什么类型，不是void就是错误
				if(ty!="void"){
				  cout<<"errtype"<<endl;
				}
				else{
				  cout<<"void"<<endl;
				}
				continue;
			}
			if(mp[ty]<0||mp[ty]+(r1-l)<0){//如果父级小于0则无论再怎么操作都是错误的类型
			  cout<<"errtype"<<endl;
			}
			else{
				cout << "void";
				for(int i=1;i<=mp[ty]+(r1-l);i ++){
				  cout << "*";
				}
				cout<<endl;
			}
		}
	}
	return 0;
}
```


---

## 作者：IvanZhang2009 (赞：0)

一道简单的模拟题 [传送门](https://www.luogu.com.cn/problem/CF87B)

用 map 记录已标记的内容，需要注意的是需要在初始化的时候加一句

```cpp
map["void"]="void;
```

还有两个注意点:

1、存在 map 里的内容必须去除所有的 * 和 &。从 map 里取值的时候注意判断。

```cpp
if(mp.find(s)!=mp.end())
```

2、对于 errtype ,需要注意不管前面加了多少个 & 或后面加了多少个 * 都是 errtype 。

贴 dima

```cpp
#include<bits/stdc++.h>
#define int long long
#define REP(i,a,n) for(int i=a;i<(n);i++)
#define REP_sz(i,s) for(int i=0;i<s.size();i++)
#define gcd(a,b) __gcd(a,b)
#define RE return
#define FILL(a,b) memset(a,b,sizeof(a))
#define SO(a) sort(all(a))
#define all(a) a.begin(),a.end()
#define pb push_back
#define sz(a) (int)a.size()
#define V vector
#define ld long double
#define viit(a) vector<int>::iterator a
#define IT iterator
#define SET setprecision
#define FOR(i,a,n) for(int i=a;i<=(n);i++)
#define ER1(a) a.erase(a.begin())
#define ER0(a) a.erase(a.end())
#define pii pair<int,int>
#define pause system("PAUSE")
#define cls system("CLS")
#define mod1 1000000007
#define mod2 998244353
#define infmod 9223372036854775783
#define tc int t;cin>>t;while(t--)solve();
#define over(x) {cout<<x<<endl;return;}
#define intsz(x) (int)sz(to_string(x))
#define readgraph(g,n) REP(i,0,n){int x,y;cin>>x>>y;x--,y--;g[x].pb(y);g[y].pb(x);}
using namespace std;
map<string,string>mp;
void solve(){
	string s,t;
	cin>>s>>t;
	if(s=="typeof"){
		int x,y;
		x=y=0;
		s=t;
		while(s.size()&&s[0]=='&')s=s.substr(1,s.size()-1),x++;
		while(s.size()&&s[s.size()-1]=='*')s=s.substr(0,s.size()-1),y++;
		if(mp.find(s)==mp.end())over("errtype")
		x=y-x;
		string st=mp[s];
		if(st=="errtype"){
			cout<<"errtype"<<endl;
			return;
		}
		int z=0;
		for(int i=st.size()-1;i>=0&&st[i]=='*';i--)z++,st=st.substr(0,st.size()-1);
		if(z+x<0)cout<<"errtype\n";
		else{
			for(int i=0;i<z+x;i++)st+='*';
		}
		if(st==" "||st==" ")cout<<"errtype\n";
		else cout<<st<<endl;
	}else{
		cin>>s;
		swap(s,t);
		int x,y;
		x=y=0;
		while(s.size()&&s[0]=='&')s=s.substr(1,s.size()-1),x++;
		while(s.size()&&s[s.size()-1]=='*')s=s.substr(0,s.size()-1),y++;
		x=y-x;
		y=0;
		if(s=="errtype"){
			mp[t]="errtype";
			return;
		}
		if(mp.find(s)==mp.end()){
			mp[s]=mp[t]="errtype";
			return;
		}
		string st=mp[s];
		if(st=="errtype"){
			mp[t]="errtype";
			return ;
		}
		int z=0;
		for(int i=st.size()-1;i>=0&&st[i]=='*';i--)z++,st=st.substr(0,st.size()-1);
		if(z+x<0)mp[t]="errtype";
		else{
			for(int i=0;i<z+x;i++)st+='*';
			mp[t]=st;
		}
	}
}
signed main()
{
	ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    mp["void"]="void";
    mp["errtype"]="errtype";
	tc
    return 0;
}
```

---

