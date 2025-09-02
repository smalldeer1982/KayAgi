# [SNCPC2024] chmod

## 题目描述

$\text{chmod}$ 是一个用于更改文件或目录权限的命令，它是 Linux 和其他类 Unix 操作系统中的常用命令之一。$\text{chmod}$ 命令允许用户为文件或目录设置不同的权限，以控制谁可以读取，写入或执行这些文件。

在 Linux 系统中，每个文件或目录都有与之相关联的权限, 这些权限决定了谁可以对文件进行何种操作。用户被分为三类：所有者（owner），所属组（group）和其他人（others）。每类用户又都有读 （r），写（w）和执行（x）三种权限。这 $9$ 种权限可以分别指定。我们称**权限字符串**是一个长度为 $9$ 的字符串，按顺序分别对应以上提到的 $9$ 种权限，如果具有此权限，则为 $\text{r}$，$\text{w}$，$\text{x}$ 中相应的那一个，否则为 $\text{-}$。

例如**权限字符串** $\text{rwxr-x-}\text{-x}$ 说明，该文件对于所有者具有全部权限，对于所属组用户只具有读和执行权限，而对于其他人只具有执行权限。

使用 $\text{chmod}$ 命令时，你可以提供模式串来修改权限。在本题，我们只考虑长度为 $3$ 的由不大于 $7$ 的数字组成的模式串，其三个数字从左往右依次代表所有者（owner），所属组（group）和其他人（others）的权限。对于每个数字，其最低三个二进制位从高向低分别表示了该类用户是否具有读（r），写（w）和执行（x）权限。

例如：执行 $\text{chmod 760 file.txt}$ 后, 表示文件的**权限字符串**为 $\text{rwxrw-}\text{-}\text{-}\text{-}$。

给出若干合法的模式串，每次读入一条模式串后，你需要输出修改后文件的**权限字符串**。

## 样例 #1

### 输入

```
3
356
114
514
```

### 输出

```
-wxr-xrw-
--x--xr--
r-x--xr--
```

# 题解

## 作者：wangbinfeng (赞：6)

[![](https://img.shields.io/badge/题目-P10691_[SNCPC2024]_chmod-yellow)
![](https://img.shields.io/badge/难度-入门-red)
![](https://img.shields.io/badge/考点-二进制-blue)
![](https://img.shields.io/badge/题型-传统题-green)](https://www.luogu.com.cn/problem/P10691)
[![](https://img.shields.io/badge/作者-wangbinfeng(387009)-purple)](https://www.luogu.com.cn/user/387009)

------------
本题是比赛的签到题，线下赛共计 $117$ 个队伍通过。

给出一个三位的十进制数表示一个文件的权限。由于三位十进制数分别代表三种用户的权限，不难想到把他拆成三位分别处理。

对于每一位的十进制数，将其转换为二进制，如果对应位是 $1$ 则分别输出 `r,w,x` 即可。

具体地，拆分十进制数的代码如下：第一位：`n/100`；第二位：`n/10%10`；第三位：`n%10`。   
对于每一位十进制数：第一位：`x/4`；第二位：`x/2%2`；第三位：`x%2`。 


------------

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,ans,n;
inline void get(const int x){
	if(x/4==1)cout<<"r";else cout<<"-"; 
	if(x/2%2==1)cout<<"w";else cout<<"-"; 
	if(x%2==1)cout<<"x";else cout<<"-"; 
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
	for(cin>>t;t--;ans=0){
		cin>>n;
		get(n/100),get(n/10%10),get(n%10);
		cout<<"\n"; 
	}
}
```

---

## 作者：dlzlj_2010 (赞：2)

直接按题意模拟。  
对于每一组数据，先拆开数字的每一位，再拆出二进制位，按题意添加字符即可。
## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
typedef int itn;
typedef int tin;
string s;
void work(int a){//拆二进制位
	if(a>>2)s+='r';
	else s+='-';
	if((a%4)>>1)s+='w';
	else s+='-';
	if(a&1)s+='x';
	else s+='-';
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		int tt;
		cin>>tt;
		int a=tt/100,b=tt%100/10,c=tt%10;//拆十进制位
		s="";
		work(a);//每一位都进行处理
		work(b);
		work(c);
		cout<<s<<'\n';//输出
	}
    return 0;
}
```

---

## 作者：WydnksqhbD (赞：2)

# [P10691 [SNCPC2024] chmod](https://www.luogu.com.cn/problem/P10691) 题解

## 题意

给一个十进制数，转换为二进制，并按题目格式输出。

## 思路

### Step 1 转换二进制

采用**短除法**。

每次除以 $2$，将余数收集起来。等到 $\le1$ 时，将所有余数按照收集时的逆序组合成二进制数。

```cpp
int toBinary(int n) {
    int binary = 0;
    int number, i = 1;
    while (n) {
        number = n % 2;
        n /= 2;
        binary += number * i;
        i *= 10;
    }
    return binary;
}
```

### Step 2 `bitset`

更多内容详见 [OI - wiki](https://oi-wiki.org/lang/csl/bitset/)。

`bitset` 的构造函数可以将整数每一位作为 `bool` 值初始化 `bitset`。则

```cpp
bitset<9> b(toBinary(n));
```

就是把 $n$ 转换成了二进制后赋值给了 `bitset`。

### Step 3 打表检查

写循环也可以。

```cpp
if (b[2]) cout << 'r';
else cout << '-';
if (b[1]) cout << 'w';
else cout << '-';
if (b[0]) cout << 'x';
else cout << '-';
if (c[2]) cout << 'r';
else cout << '-';
if (c[1]) cout << 'w';
else cout << '-';
if (c[0]) cout << 'x';
else cout << '-';
if (d[2]) cout << 'r';
else cout << '-';
if (d[1]) cout << 'w';
else cout << '-';
if (d[0]) cout << 'x';
else cout << '-';
```

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long // int 替换为 long long

using namespace std;

int T;

int toBinary(int n) { // 转二进制
    int binary = 0; // 结果
    int number; // 余数
    int i = 1; // 收集的时候需要乘的数(总是 10 的次幂)
    while (n) {
        number = n % 2;
        n /= 2;
        binary += number * i;
        i *= 10;
    }
    return binary;
}

signed main() {
	for (cin >> T; T--; ) {
		int n;
		cin >> n;
		bitset<9> b(toBinary(n / 100)); // 注意这里分位数转换
		bitset<9> c(toBinary(n / 10 % 10));
		bitset<9> d(toBinary(n % 10));
      // 打表
		if (b[2]) cout << 'r';
		else cout << '-';
		if (b[1]) cout << 'w';
		else cout << '-';
		if (b[0]) cout << 'x';
		else cout << '-';
		if (c[2]) cout << 'r';
		else cout << '-';
		if (c[1]) cout << 'w';
		else cout << '-';
		if (c[0]) cout << 'x';
		else cout << '-';
		if (d[2]) cout << 'r';
		else cout << '-';
		if (d[1]) cout << 'w';
		else cout << '-';
		if (d[0]) cout << 'x';
		else cout << '-';
		putchar('\n'); // 换行
	}
	return 0;
}
```

---

## 作者：Bc2_ChickenDreamer (赞：2)

## P10691

### Sol

这道题很简单，直接模拟就可以了。可是，这样子的话吗，码量较多。我们可以把 $0 \sim 7$ 的二进制以三位数的形式列出来，分别是 $[000, 001, 010, 011, 100, 101, 110]$，我们把二进制变成权限串存在数组里就是 `string s[8] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"}` 这样子。

这样子，我们就方便很多了，我们只需把模式串拆分成 $3$ 个数 $a, b, c$，输出 $s_a, s_b, s_c$ 即可。不需隔开。

### Code

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
 
using namespace std;
 
using ll = long long;
 
const int kMaxN = 220, kInf = (((1 << 30) - 1) << 1) + 1, kMod = 998244353;
const ll kLInf = 9.22e18;

string s[8] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  for (cin >> t; t; -- t) {
    char x, y, z;
    cin >> x >> y >> z;
    ll a = x - 48, b = y - 48, c = z - 48; // 字符转数字
    cout << s[a] << s[b] << s[c] << '\n';
  }
  return 0;
}
```

---

## 作者：Programming_Konjac (赞：1)

# 思路
这题抽象打表，所以首先观察样例：

$356$ 为 `-wxr-xrw-`，那么 $3=$`-wx`，$5=$`r-x`，$6=$`rw-`。

$514$ 为 `r-x--xr--`，那么 $5=$`r-x`，$1=$`--x`，$4=$`r--`。

$760$ 为 `rwxrw----`，那么 $7=$`rwx`，$6=$`rw-`，$0=$`---`。

虽然没有 $2$，但是我们可以构造一下，发现 $r=4,w=2,x=1$，所以 $2=$`-w-`。

随后数位分离，每次判断输出即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	ios::sync_with_stdio(false); 
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int a=n/100,b=n/10%10,c=n%10;
		if(a==7) cout<<"rwx";
		else if(a==6) cout<<"rw-";
		else if(a==5) cout<<"r-x";
		else if(a==4) cout<<"r--";
		else if(a==3) cout<<"-wx";
		else if(a==2) cout<<"-w-";
		else if(a==1) cout<<"--x";
		else cout<<"---";
		a=b;
		if(a==7) cout<<"rwx";
		else if(a==6) cout<<"rw-";
		else if(a==5) cout<<"r-x";
		else if(a==4) cout<<"r--";
		else if(a==3) cout<<"-wx";
		else if(a==2) cout<<"-w-";
		else if(a==1) cout<<"--x";
		else cout<<"---";
		a=c;
		if(a==7) cout<<"rwx";
		else if(a==6) cout<<"rw-";
		else if(a==5) cout<<"r-x";
		else if(a==4) cout<<"r--";
		else if(a==3) cout<<"-wx";
		else if(a==2) cout<<"-w-";
		else if(a==1) cout<<"--x";
		else cout<<"---";
		cout<<"\n";
	}
	return 0;
}
``

---

## 作者：Atserckcn (赞：1)

## [P10691 [SNCPC2024] chmod](https://www.luogu.com.cn/problem/P10691) 题解

### 题目简述

给定一个三位数，将每个数位转化为二进制后会得到一个 $01$ 串，若为 $1$ 则代表有这个权限，$0$​ 则没有。

这题题目蛮冗长的，但是中心意思就这么一行……

举个例子：样例的第一个数据：$356$。

将其挨个拆开，$(3)_{10}=(011)_{2}$，所以第一位用户（不管他是什么身份），没有权限 $1$，但有权限 $2$、$3$。输出为：`-wx`。

同理，剩下两位用户分别为 $101$ 和 $110$，分别输出 `r-x`、`rw-`。

### 思路简述

问题很简单了，就是判断每一位是否为零。关键是如何转换成二进制呢？

在这题上，因为我当时没什么时间，赶着上课，所以懒得打二进制转化代码，直接无脑枚举（最大也才 $7$ 嘛）。

核心代码：

```cpp 
void work()
{
    //对应的每种情况，a代码出来后，bc直接复制粘贴即可
	if(a==0)
		a1=a2=a3=0;
	if(a==1)
	{
		a1=a2=0;
		a3=1;
	}
	if(a==2)
	{
		a1=a3=0;
		a2=1;
	}
	if(a==3)
	{
		a1=0;
		a2=a3=1;
	}
	if(a==4)
	{
		a1=1;
		a2=a3=0;
	}
	if(a==5)
	{
		a1=a3=1;
		a2=0;
	}
	if(a==6)
	{
		a1=a2=1;
		a3=0; 
	}
	if(a==7)
		a1=a2=a3=1;
	if(b==0)
		bb1=b2=b3=0;
	if(b==1)
	{
		bb1=b2=0;
		b3=1;
	}
	if(b==2)
	{
		bb1=b3=0;
		b2=1;
	}
	if(b==3)
	{
		bb1=0;
		b2=b3=1;
	}
	if(b==4)
	{
		bb1=1;
		b2=b3=0;
	}
	if(b==5)
	{
		bb1=b3=1;
		b2=0;
	}
	if(b==6)
	{
		bb1=b2=1;
		b3=0; 
	}
	if(b==7)
		bb1=b2=b3=1;
	if(c==0)
		c1=c2=c3=0;
	if(c==1)
	{
		c1=c2=0;
		c3=1;
	}
	if(c==2)
	{
		c1=c3=0;
		c2=1;
	}
	if(c==3)
	{
		c1=0;
		c2=c3=1;
	}
	if(c==4)
	{
		c1=1;
		c2=c3=0;
	}
	if(c==5)
	{
		c1=c3=1;
		c2=0;
	}
	if(c==6)
	{
		c1=c2=1;
		c3=0; 
	}
	if(c==7)
		c1=c2=c3=1;
	return;
}
```

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string s;
int a,b,c;
int a1,a2,a3,bb1,b2,b3,c1,c2,c3;//注意注意！！千万不能是b1，因为b1是iostream里的函数
void work()
{
	if(a==0)
		a1=a2=a3=0;
	if(a==1)
	{
		a1=a2=0;
		a3=1;
	}
	if(a==2)
	{
		a1=a3=0;
		a2=1;
	}
	if(a==3)
	{
		a1=0;
		a2=a3=1;
	}
	if(a==4)
	{
		a1=1;
		a2=a3=0;
	}
	if(a==5)
	{
		a1=a3=1;
		a2=0;
	}
	if(a==6)
	{
		a1=a2=1;
		a3=0; 
	}
	if(a==7)
		a1=a2=a3=1;
	if(b==0)
		bb1=b2=b3=0;
	if(b==1)
	{
		bb1=b2=0;
		b3=1;
	}
	if(b==2)
	{
		bb1=b3=0;
		b2=1;
	}
	if(b==3)
	{
		bb1=0;
		b2=b3=1;
	}
	if(b==4)
	{
		bb1=1;
		b2=b3=0;
	}
	if(b==5)
	{
		bb1=b3=1;
		b2=0;
	}
	if(b==6)
	{
		bb1=b2=1;
		b3=0; 
	}
	if(b==7)
		bb1=b2=b3=1;
	if(c==0)
		c1=c2=c3=0;
	if(c==1)
	{
		c1=c2=0;
		c3=1;
	}
	if(c==2)
	{
		c1=c3=0;
		c2=1;
	}
	if(c==3)
	{
		c1=0;
		c2=c3=1;
	}
	if(c==4)
	{
		c1=1;
		c2=c3=0;
	}
	if(c==5)
	{
		c1=c3=1;
		c2=0;
	}
	if(c==6)
	{
		c1=c2=1;
		c3=0; 
	}
	if(c==7)
		c1=c2=c3=1;
	return;
}
int main(){
	scanf("%d",&t);
	while(t--)
	{
		cin >> s;
		a=s[0]-'0';
		b=s[1]-'0';
		c=s[2]-'0';
		work();
		if(a1==1)
			putchar('r');
		else putchar('-');
		if(a2==1)
			putchar('w');
		else putchar('-');
		if(a3==1)
			putchar('x');
		else putchar('-');
		if(bb1==1)
			putchar('r');
		else putchar('-');
		if(b2==1)
			putchar('w');
		else putchar('-');
		if(b3==1)
			putchar('x');
		else putchar('-');
		if(c1==1)
			putchar('r');
		else putchar('-');
		if(c2==1)
			putchar('w');
		else putchar('-');
		if(c3==1)
			putchar('x');
		else putchar('-');
		printf("\n");
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10691)

每次输入一个字符串 $s$，一位一位地看，把 $s_i$ 转换成二进制数（保留三位就可以，不足补 $0$），然后依次判断每一位是不是 $0$，如果是输出 `-`，否则按下标输出 `r`、`w` 或 `x`。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

char p[] = {'r', 'w', 'x'};

string Turn(int x) {
    string s = "";
    int cnt = 0;
    while (x) {
        s += (x % 2 + '0');
        x >>= 1, cnt++;
        if (cnt == 3) break; // 如果已经够了三位
    }
    if (s.size() < 3) { // 一个很笨的补零方法
        for (int i = 0; i < 3; i++) {
            s += '0';
            if (s.size() == 3) break;
        }
    }
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        for (int i = 0; i < s.size(); i++) {
            int x = s[i] - '0';
            string t = Turn(x);
            for (int j = 0; j < 3; j++)
                if (t[j] == '0') cout << '-';
                else cout << p[j];
        }
        cout << "\n";
    }
    return 0;
}
```

---

## 作者：zhengpie (赞：1)

### 1.思路

按照题意模拟即可。

我们建立一个映射表 $mp$，使得它有如下的对应关系：

```cpp
mp[0] = "---";
mp[1] = "--x";
mp[2] = "-w-";
mp[3] = "-wx";
mp[4] = "r--";
mp[5] = "r-x";
mp[6] = "rw-";
mp[7] = "rwx";
```

然后对于输入的每一个数字 $i$，输出 $mp_i$ 即可。

### 2.代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
map<int,string> mp;
string s;
signed main()
{
	cin>>n;
	mp[0] = "---";
	mp[1] = "--x";
	mp[2] = "-w-";
	mp[3] = "-wx";
	mp[4] = "r--";
	mp[5] = "r-x";
	mp[6] = "rw-";
	mp[7] = "rwx";
	while(n--)
	{
		cin>>s;
		cout<<mp[s[0] - 48]<<mp[s[1] - 48]<<mp[s[2] - 48]<<"\n";//注意要减48，也就是减'0'
	}
	return 0;
	
}
```

---

## 作者：_Deer_Peach_ (赞：1)

按照题意去模拟即可。

先理解一下题意：

有三种用户，分别是所有者，所属组和其他人，每一种用户有读写执行三种权限，用字母表示为 $rwx$。给出模式串，每个模式串有三个数字，分别指所有者，所属组和其他人。

那我们就可以先将这三个数字分别转成二进制。比如所有者所属组与其他人的模式串为 $356$，转成二进制分别就是：
```
011 101 110
```
那么权限字符串为：
```
-wxr-xrw-
```
不难理解，那么我们就可以写代码了。

代码如下：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
string owner="rwx",group="rwx",others="rwx";//三种用户的权限
signed main(){
	cin>>t;//多组数据
	for(int i=1;i<=t;i++){
		char a,b,c;//三个数字
		cin>>a>>b>>c;
		int x,y,z;//输入的三个数字是一个字符串，所以分别转成三个数字
		x=(int)(a-'0');//转成数字
		y=(int)(b-'0');//转成数字
		z=(int)(c-'0');//转成数字
		int q[3]={0,0,0},w[3]={0,0,0},e[3]={0,0,0},cnt=2;//转成二进制判断是否有某一种权限
		while(x){//所有者
			q[cnt]=x%2;
			x/=2;
			cnt--;
		}cnt=2;
		while(y){//所属组
			w[cnt]=y%2;
			y/=2;
			cnt--;
		}cnt=2;
		while(z){//其他人
			e[cnt]=z%2;
			z/=2;
			cnt--;
		}for(int j=0;j<3;j++){
			if(q[j])cout<<owner[j];//输出，根据是否有权限来输出
			else cout<<"-";
		}for(int j=0;j<3;j++){
			if(w[j])cout<<group[j];
			else cout<<"-";
		}for(int j=0;j<3;j++){
			if(e[j])cout<<others[j];
			else cout<<"-";
		}cout<<endl;
	}
	return 0;
}
```

---

## 作者：luogu_gza (赞：1)

直接模拟。

值得注意的是，我们可以把处理每一位，每一个数字的函数都写出来，会大大减小码量。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace gza{
	#define pb push_back
	#define MT int TTT=R;while(TTT--)
	#define pc putchar
	#define R read()
	#define fo(i,a,b) for(int i=a;i<=b;i++)
	#define rep(i,a,b) for(int i=a;i>=b;i--)
	#define m1(a,b) memset(a,b,sizeof a)
	namespace IO
	{
		inline int read()
		{
		    int x=0;
		    char ch=getchar();
		    bool f=0;
		    while(!isdigit(ch)){if(ch=='-') f=1;ch=getchar();}
		    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
		    if(f) x=-x;
		    return x;    
		}
		template<typename T> inline void write(T x)
		{
		    if(x<0) pc('-'),x=-x;
		    if(x>9) write(x/10);
		    pc(x%10+'0');
		}
	};
	using namespace IO;
	
	void wor(int p,int x)
	{
		if(p==1)
		{
			if(x) pc('r');
			else pc('-');
		}
		if(p==2)
		{
			if(x) pc('w');
			else pc('-');
		}
		if(p==3)
		{
			if(x) pc('x');
			else pc('-');
		}
		
	}
	void work(int x)
	{
		wor(1,x/4),wor(2,x/2%2),wor(3,x%2);
	}
	void solve()
	{
		int n=R;
		work(n/100),work(n/10%10),work(n%10);
		puts("");
	}
	void main(){
		MT solve();
	}
}
signed main(){
	// freopen("template.in","r",stdin);
	// freopen("template.out","w",stdout);
	gza::main();
}
```

---

## 作者：Guo1 (赞：0)

### 思路

第一眼，我们把每个数字提取出来，然后转换成二进制，如果是 $1$ 则输出数字，不然就输出减号。

我的方法则是，提取出每个数字，然后对它们进行判断。由于有很多可能，每个可能只对应一个输出语句，因此我们就不需要写一大长串判断。

### 坑

怎么提取出一个三位数的每一位？

以 $114$ 为例，百位就是除以 $100$，十位是除以 $10$ 再对 $10$ 取模，个位就是对 $10$ 取模。

### 代码

别抄袭！

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,s;
int main()
{
	cin>>T;
    while(T--)
    {
    	cin>>s;
    	int a[3]={s/100,s/10%10,s%10};
    	for(int i=0;i<3;i++)
    	{
    		int m=a[i];
    		switch(m)
    		{
    			case 0:cout<<"---";break;
    			case 1:cout<<"--x";break;
    			case 2:cout<<"-w-";break;
				case 3:cout<<"-wx";break;
				case 4:cout<<"r--";break;
				case 5:cout<<"r-x";break;
				case 6:cout<<"rw-";break;//记得break
				case 7:cout<<"rwx";
			}
		}
		puts("");
	}
    return 0;
}
```

### 总结

本题考查模拟，小细节要注意。比如结尾要换行。

---

## 作者：LatitudeCrosser (赞：0)

> 建议在阅读本文前先了解 shell 脚本中 `chmod` 的使用。

`chmod` 接受八进制整数或者字符串作为权限输入，这里需要把八进制转为二进制，然后按照 `rwxrwxrwx` 的顺序进行比较，如果二进制为 $1$ 就输出这个字符串中的对应项，否则输出 `-` 。

而我们知道，一位八进制等于三位二进制，而输入八进制总长固定，所以可使用简单的 `switch case` 映射来转换到二进制，接下来 `for` 循环遍历即可。为了方便，推荐使用 `string` 类型或者字符数组处理二进制。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
string oct2bin(int n)
{
	switch(n)
	{
		case 0:return "000";break;
		case 1:return "001";break;
		case 2:return "010";break;
		case 3:return "011";break;
		case 4:return "100";break;
		case 5:return "101";break;
		case 6:return "110";break;
		case 7:return "111";break;
	}
}
string res(int n)
{
	string ans;
  	ans=oct2bin(n/100%10)+oct2bin(n/10%10)+oct2bin(n%10);
	string str="";
	for(int i=0;i<9;i+=3)
	{
		if(ans[i]=='1') str+="r";
		else str+="-";
		if(ans[i+1]=='1') str+="w";
		else str+="-";
		if(ans[i+2]=='1') str+="x";
		else str+="-";
	}
	return str;
}
int main()
{
	int n;
	cin>>n;
	while(n--)
	{
		int m;
		cin>>m;
		cout<<res(m)<<endl;
	}
}
```

---

## 作者：Eason_cyx (赞：0)

观察题目可以发现，答案就是将输入的**三个一位数**转为二进制后的结果。那么我们就将其转为二进制，然后逐位判断是否为 $1$ 即可。

单组时间复杂度 $\Theta(1)$。

代码太丑了，不贴了。

---

## 作者：Jorisy (赞：0)

学会阅读理解。

简要题意：给出三个不大于 $7$ 的数，分别输出其二进制，对于 $2^2,2^1,2^0$ 为 $1$ 的分别用 $\tt r,w,x$ 替代，为 $0$ 的都用 $\texttt-$ 替代。

那么就很显然了。

直接对每一位除即可。

注意数位为 $0$ 的情况。
```cpp
#include<bits/stdc++.h>
using namespace std;

const string S="xwr";

void sol()
{
	int x;
	cin>>x;
	string ans="";
	while(x)
	{
		int t=x%10,i=0;
		string s="";
		while(t)
		{
			s=((t&1)?S[i]:'-')+s;
			i++;
			t>>=1;
		}
		while(s.size()<3) s="-"+s;
		ans=s+ans;
		x/=10;
	}
	while(ans.size()<9) ans="---"+ans;
	cout<<ans<<endl;
}

int main()
{
	int t;
	cin>>t;
	while(t--) sol();
 	return 0;
}
```

---

## 作者：postpone (赞：0)

对于每个三位数，把个十百三个数字提取出来，由于只有 8 种情况，全部列出来判断即可。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define endl '\n'
const int N = 1e3 + 100;

int a[N];
string s2(int x)
{
    string str;
    switch (x)
    {
    case 0:
        str = "---";
        break;
    case 1:
        str = "--x";
        break;
    case 2:
        str = "-w-";
        break;
    case 3:
        str = "-wx";
        break;
    case 4:
        str = "r--";
        break;
    case 5:
        str = "r-x";
        break;
    case 6:
        str = "rw-";
        break;
    case 7:
        str = "rwx";
        break;
    default:
        break;
    }
    return str;
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
    {
        int x1 = a[i] / 100;
        int z1 = a[i] % 10;
        int y1 = (a[i] - x1 * 100 - z1) / 10;
        cout << s2(x1) << s2(y1) << s2(z1) << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
    while (_--)
        solve();
    return 0;
}
```

---

## 作者：chenlongli (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10691)
### 思路
我们枚举每位上的数字，可以通过 $8$ 个条件判断语句进行判断，首先将这个数字转换成二进制数，如果这位上是 $1$，就输出对应的字母，否则就输出 $-$。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	for (int i=0;i<t;i++)
	{
		string a;
		cin>>a;
		for (int j=0;j<3;j++)
		{
		    if (a[j]=='0')
		    {
		        cout<<"---";
		    }
			if (a[j]=='1')
			{
				cout<<"--x";
			}
			if (a[j]=='2')
			{
				cout<<"-w-";
			}
			if (a[j]=='3')
			{
				cout<<"-wx";
			}
			if (a[j]=='4')
			{
				cout<<"r--";
			}
			if (a[j]=='5')
			{
				cout<<"r-x";
			}
			if (a[j]=='6')
			{
				cout<<"rw-";
			}
			if (a[j]=='7')
			{
				cout<<"rwx";
			}
		}
		cout<<endl;
	}
}
```

---

## 作者：lcfollower (赞：0)

签到题，对于每一位 $s_i$，只需要分情况讨论并输出即可。

| $s_i$ | $\text{对应字符串}$ |
| -----------: | -----------: |
| $0$ | $\texttt{---}$ |
| $1$ | $\texttt{--x}$ |
| $2$ | $\texttt{-w-}$ |
| $3$ | $\texttt{-wx}$ |
| $4$ | $\texttt{r--}$ |
| $5$ | $\texttt{r-x}$ |
| $6$ | $\texttt{rw-}$ |
| $7$ | $\texttt{rwx}$ |


```cpp
#include<bits/stdc++.h>
#define int long long
#define little_dog puts("OvO,2021zjhs005 is better than me.")
#define lcfollower break
#define _2021zjhs005 continue
#define inf 0x3f3f3f3f
#define infi 0x3f3f3f3f3f3f3f3fll
#define up(i,x,y) for(register int i=x;i<=y;++i)
#define dn(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();return x*f;}
inline void write(int x){if(x<0)putchar('-'),x=-x;if(x>9)write(x/10);putchar(x%10|48);}
inline void writeln(int x){write(x),putchar('\n');}
inline void writesp(int x){write(x),putchar(' ');}

int T;

signed main(){
  T = read();
  while(T --){
    string s;
    cin >> s;
    for(int i = 0;i < s.size();i ++)
      if(s[i] == '0') cout << "---";
      else if(s[i] == '1') cout << "--x";
      else if(s[i] == '2') cout << "-w-";
      else if(s[i] == '3') cout << "-wx";
      else if(s[i] == '4') cout << "r--";
      else if(s[i] == '5') cout << "r-x";
      else if(s[i] == '6') cout << "rw-";
      else if(s[i] == '7') cout << "rwx";
    cout << endl;
  }
  return 0;
}
```

---

## 作者：ggylz49 (赞：0)

## 思路分析
对用到的函数进行分析。
### 1. 二进制
输入的三个数需要转成二进制来代表对应的权限。有了一个数 $x$，用一个字符串 $s$ 来逐位存储 $x \bmod 2$ 的值，每存储一次 $x$ 就除以 $2$，得到一个 $01$ 数字串，翻转后就是 $s$ 的二进制。我们可以使用 algorithm 库中的 `reverse` 函数，翻转时的头尾分别是 `s.begin()` 和 `s.end()`，即字符串头尾的地址。
```cpp
string zhuan(char c)
{
    int x=c-'0';//输入的字符转成数字x，配合如下主函数的说明
    string s="";
    while(x>0)s+=(x%2)+'0',x/=2;
    reverse(s.begin(),s.end());//翻转
    while(s.size()<3)s.insert(0,"0");//保留末三位数，不足三位在数组的头补0
    return s;
}
```
### 2. 输出
有了字符串 $s$，输出就十分方便了。若 $s_0=1$，输出 $\texttt{r}$，否则输出 $\texttt{-}$；若 $s_1=1$，输出 $\texttt{w}$，否则输出 $\texttt{-}$；若 $s_2=1$，输出 $\texttt{x}$，否则输出 $\texttt{-}$。
```cpp
void print(string x)
{
    if (x[0]=='1')cout<<'r';
    else cout<<'-';
    if (x[1]=='1')cout<<'w';
    else cout<<'-';
    if (x[2]=='1')cout<<'x';
    else cout<<'-';
}
```
### 3. 主函数
输入了数据组数，对于每一组数据：

1. 因为三个数之间没有空格，所以使用 char 读入。
2. 对于三个数，分别转成二进制存储进字符串（调用 `zhuan` 函数）。
3. 使用 `print` 函数输出对应的权限字符串。
## Code
```cpp
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
string zhuan(char c)
{
    int x=c-'0';
    string s="";
    while(x>0)s+=(x%2)+'0',x/=2;
    reverse(s.begin(),s.end());
    while(s.size()<3)s.insert(0,"0");
    return s;
}
void print(string x)
{
    if (x[0]=='1')cout<<'r';
    else cout<<'-';
    if (x[1]=='1')cout<<'w';
    else cout<<'-';
    if (x[2]=='1')cout<<'x';
    else cout<<'-';
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        char a,b,c;
        cin>>a>>b>>c;
        string x=zhuan(a),y=zhuan(b),z=zhuan(c);
        print(x);
        print(y);
        print(z);
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：JYX0924 (赞：0)

根据题意模拟即可。

可以使用位运算，将 $1$ 左移 $0$ 位、$1$ 位、$2$ 位后分别与原数进行与运算。如果运算返回值不为 $0$，输出题目中的字母，否则输出 $-$ 号。

下面是我的 AC 代码。

```c
#include<bits/stdc++.h>
using namespace std;
int T;
char s;
int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>T;
	while(T--)
	{
		for(int i=1;i<=3;i++)
		{
			cin>>s; int now=s-'0';
			if(((1<<2)&now)!=0) cout<<"r";
			else cout<<"-";
			if(((1<<1)&now)!=0) cout<<"w";
			else cout<<"-";
			if(((1<<0)&now)!=0) cout<<"x";
			else cout<<"-";
		}
		cout<<"\n";
	}
	return 0;
}
```
谢谢大家！！！

---

## 作者：TemplateClass (赞：0)

我们将输入的数整数拆分，然后每一位分别按位与上 $2 ^ 2$，$2 ^ 1$ 和 $2 ^ 0$，即为末尾的 $3$ 位数字，再按照题目要求输出即可。

```cpp
#include<cstdio>
#include<iostream>
#include<string>
//#define int long long

const int N = 1e6 + 5;
const int MOD1 = 998244353;
const int MOD2 = 1e9 + 7;
int n;

int t = 1;
void solve();

signed main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0);
	
	std::cin >> t;
	while(t--) solve();
	
	return 0;
}

void solve(){
	std::string s;
	std::cin >> s;
	
	for(const auto& c : s) {
		int now = c - '0';
		
		if(now & 4) std::cout << "r";
		else std::cout << "-";
		
		if(now & 2) std::cout << "w";
		else std::cout << "-";
		
		if(now & 1) std::cout << "x";
		else std::cout << "-";
		
	}
	std::cout << "\n";
}

```

---

## 作者：xzz_0611 (赞：0)

[题目传送门](/problem/P10691)
### 分析
一个十进制数转二进制数的办法很简单，如下：
- 算出这个数除以二的结果，余数写在一边，将商覆盖原数，重复此操作，直到该数等于 $0$ 为止，然后将其的余数按从前到后的顺序从右至左排成的数就是最终的结果。

而我们只需要这个数字的后 $3$ 位，也就是说明只需要除以 $3$ 次 $2$，由于顺序问题，第一次的商对应着 `x`，第二次的商对应着 `w`，第三次的商对应着 `r`。
### Code
```cpp
#include<iostream>
using namespace std;
void abc(int x) {
	string ans="---";//初始设为“---”
	//进行判断，记得要除以2
	if(x%2) ans[2]='x';
	x/=2;
	if(x%2) ans[1]='w';
	x/=2;
	if(x%2) ans[0]='r';
	cout<<ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--) {
		int n;
		cin>>n;
		int a=n/100,b=n/10%10,c=n%10;//提取百位、十位、和个位
		abc(a),abc(b),abc(c);
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：luckyqwq (赞：0)

# P10691 [SNCPC2024] chmod 题解

### 大致思路：

直接按照题意模拟即可，模式串的每一位，都转成 $2$ 进制，翻转一下，不足三位的，用 $0$ 填补，最后按位判断和输出即可。

### 代码实现：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
string p = "1rwx";
signed main(){
	cin >> T;
	while (T --)
	{
		int a[5], b[5], c[5], c1 = 0, c2 = 0, c3 = 0;
		string s;
		cin >> s;
		int x = s[0] - '0';
		int xx = s[1] - '0';
		int xxx = s[2] - '0';
		while(x > 0)
		{
			a[ ++ c1] = x % 2;
			//cout << a[c1];
			x /= 2;
		}
		if(c1 < 3)
		{
			for(int i = c1 + 1;i <= 3; ++ i)
			{
				a[i] = 0;
			}
		}
		while(xx > 0)
		{
			b[ ++ c2] = xx % 2;
			//cout << b[c2];
			xx /= 2;
		}
		if(c2 < 3)
		{
			for(int i = c2 + 1;i <= 3; ++ i)
			{
				b[i] = 0;
			}
		}
		while(xxx > 0)
		{
			c[ ++ c3] = xxx % 2;
			//cout << c[c3];
			xxx /= 2;
		}
		if(c3 < 3)
		{
			for(int i = c3 + 1;i <= 3; ++ i)
			{
				c[i] = 0;
			}
		}
		for (int i = 3;i >= 1; -- i)
		{
			if(a[i] == 0)
			{
				cout << "-";
			}
			else
			{
				cout << p[3 - i + 1];
			}
		}
		for (int i = 3;i >= 1; -- i)
		{
			if(b[i] == 0)
			{
				cout << "-";
			}
			else
			{
				cout << p[3 - i + 1];
			}
		}
		for (int i = 3;i >= 1; -- i)
		{
			if(c[i] == 0)
			{
				cout << "-";
			}
			else
			{
				cout << p[3 - i + 1];
			}
		}
		cout << "\n";
	}
}
```

---

## 作者：jiangyunuo (赞：0)

### 题目大意：
本题其实就是让我们转化二进制，然后再根据转化的二进制得到答案。比如样例中的数据一 $356$，转化成二进制分别是 $011$、$101$、$110$，而三个位数分别对应 $\text{r}$、$\text{w}$、$\text{x}$，因此，$3$ 表示的权限是 $\text{-wx}$，$5$ 表示的权限是 $\text{r-x}$，$6$ 表示的权限是 $\text{rw-}$，组合起来就是 $\text{-wxr-xrw-}$，注意 $0$ 用 $\text{-}$ 代替，$1$ 就看这一位应该是什么，这一位对应 $\text{w}$，就输出 $\text{w}$，对应 $\text{x}$，就输出 $\text{x}$。
### 主要思路：
这种题目，一般思路就是转化为二进制，然后根据二进制来做，但这题其实还有更加简单的做法，这种做法后面再说。
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin>>t;
    bool z=0,d[3];  //z 判断后面 a%2 是否出现两次 1 出现两次就该让 a 变成 0，数组 d 表示转化的二进制。
    int a;
    string ch;
    char sh[3]={'r','w','x'};
    for(int i=0;i<t;i++){
    	cin>>ch;
    	for(int j=0;j<3;j++){
    		a=ch[j]-48;   //把输入的字符串变成整型变量。
    		z=0;
    		for(int k=0;k<3;k++){   //转化二进制。
    			if(a==1&&z==0)z=1;  //判断 1 出现的次数是否超过一次，超过 a 变成 0。
    			else if(a==1&&z)a=0;
    			d[k]=a%2;
    			a/=2;
			}
			for(int k=2;k>=0;k--){   //把顺序改正并真确输出。
				if(d[k])cout<<sh[2-k];
				else cout<<"-";
			}
		}
		cout<<endl;
	}
	return 0;
}
```
这个就是一般的做法，下面还有第二种做法。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int t,a;
    string ch,sh[8]={"---","--x","-w-","-wx","r--","r-x","rw-","rwx"};   //存储好各种情况的结果。
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>ch;
		for(int j=0;j<3;j++){
			cout<<sh[ch[j]-48];  //通过数字，直接输出对应的结果。
		}
		cout<<endl;
	}
	return 0;
}
```
没错，我用一个字符串把所有情况给储存了起来，到时候对应的数字直接就可以输出对应的结果，这个程序就比上一个程序简洁多了，也好懂多了，直接不需要用二进制了。

---

## 作者：Mason123456 (赞：0)

# P10691 题解

### 题面翻译

对于每次输入，给定一个数 $x$，取 $x$ 的前三位 $a,b,c$，在 $a, b, c$ 二进制下的后三位的数分别代表了 owner，group，others 三个人的 $\text{r, w, x}$ 权限，并按顺序输出。

### 思路

按照题意，将 $x$ 转换成 $a, b, c$，再将 $a, b, c$​ 转换成二进制判断后面三位即可。

代码中使用了 `>>`，右移，表示数在二进制下右移任意位，是位运算。`& 1` 则是判断了在二进制下最右边的数是不是为 $1$。

### Code

```cpp
#include <iostream>
using namespace std;
int main() {
    int n;
    cin>>n;
    while(n--){
        string str;
        cin>>str;
        int a = str[0] - '0';
        int b = str[1] - '0';
        int c = str[2] - '0';
        if((a >> 2) & 1)
            cout<<"r";
        else
            cout<<"-";
        if((a >> 1) & 1)
            cout<<"w";
        else
            cout<<"-";
        if(a & 1)
            cout<<"x";
        else
            cout<<"-";
        if((b >> 2) & 1)
            cout<<"r";
        else
            cout<<"-";
        if((b >> 1) & 1)
            cout<<"w";
        else
            cout<<"-";
        if(b & 1)
            cout<<"x";
        else
            cout<<"-";
        if((c >> 2) & 1)
            cout<<"r";
        else
            cout<<"-";
        if((c >> 1) & 1)
            cout<<"w";
        else
            cout<<"-";
        if(c & 1)
            cout<<"x";
        else
            cout<<"-";
        cout<<"\n";
    }
    return 0;
}

```

~~赛时 7 min 理解题面，1 min 打代码。~~

---

## 作者：fried_chicken (赞：0)

模拟题。

题意已经写的很清楚了，这里不多赘述。

首先，我们可以从题目要求里知道三个数字肯定都小于 $7$，因此，我们可以预处理 $7$ 种情况，再对三个数字分别输出相应内容即可。

代码：
```cpp
//请搭配我的缺省源食用
//https://www.luogu.com.cn/paste/k7jvhrwa
map<int,string> mp;
void init() {
	srand(time(NULL));
	
}
void slove() {//单测
	init();
	cin>>s;
	rep(i,0,len(s)){//对每个数字判断
		cout<<mp[s[i]];
	}LF;

}

signed main() {
//file("");//ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	mp['0']="---";mp['1']="--x";mp['2']="-w-";mp['3']="-wx";mp['4']="r--";mp['5']="r-x";mp['6']="rw-";mp['7']="rwx";//预处理
	int T=rd();while(T--){slove();}//多测
//	slove();
	return 0;
}

```

---

## 作者：Scean_Tong (赞：0)

## P10691 [SNCPC2024] chmod 题解

## 题意

除了 $F$ 最简单的题。

根据给出的三个数字的二进制后 $3$ 位，$0$ 即为无权限，$1$ 即为有权限，确定字符串。

## 思路
因为给定的数字都小于等于 $7$，显然它们的二进制数都是三位，所以可以开一个数组记录这 $7$ 个数的二进制，先设每个组都有所有权限。

枚举二进制数 $s1$，如果 $s1_i$ 为 $0$，就把 $s_i$ 改为 `-`。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string q[8]={"000","001","010","011","100","101","110","111"};
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	
	cin>>t;
	while(t--){
		string s="rwxrwxrwx";
		int x;
		cin>>x;
		int a=x/100;
		int b=x%100/10;
		int c=x%10;
		string s1=q[a]+q[b]+q[c];
		for(int i=0;i<9;i++){
			if(s1[i]=='0') s[i]='-';
		}
		cout<<s<<'\n';
		
	}
	
	return 0; 
} 
```

---

## 作者：abc1856896 (赞：0)

# solution
签到题。

按题意直接把三位数每一位转成**三位**二进制，再按题目要求输出即可。

# code
```cpp
void solve(){
    char c;
    cin>>c;
    if(c=='0') cout<<"---";
    if(c=='1') cout<<"--x";
    if(c=='2') cout<<"-w-";
    if(c=='3') cout<<"-wx";
    if(c=='4') cout<<"r--";
    if(c=='5') cout<<"r-x";
    if(c=='6') cout<<"rw-";
    if(c=='7') cout<<"rwx";
    cin>>c;
    if(c=='0') cout<<"---";
    if(c=='1') cout<<"--x";
    if(c=='2') cout<<"-w-";
    if(c=='3') cout<<"-wx";
    if(c=='4') cout<<"r--";
    if(c=='5') cout<<"r-x";
    if(c=='6') cout<<"rw-";
    if(c=='7') cout<<"rwx";
    cin>>c;
    if(c=='0') cout<<"---";
    if(c=='1') cout<<"--x";
    if(c=='2') cout<<"-w-";
    if(c=='3') cout<<"-wx";
    if(c=='4') cout<<"r--";
    if(c=='5') cout<<"r-x";
    if(c=='6') cout<<"rw-";
    if(c=='7') cout<<"rwx";
    cout<<endl;
}
```

---

## 作者：Last_kiss_Snow_Dog6 (赞：0)

### 第一步：拆解输入
首先根据题意可知每次输入是一个三位数，我们可以用字符串输入然后把三个数分开存储，分别对应所有者，所属组和其他人。

### 转化成二进制
每一位单独转，转完直接判断，分别输出即可。

### 代码（本人不习惯写注释可私信）
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		string t;
		cin>>t;
		int a=t[0]-'0',b=t[1]-'0',c=t[2]-'0';
		char x[10];
		x[2]=a%2,a/=2,x[1]=a%2,a/=2,x[0]=a;
		x[5]=b%2,b/=2,x[4]=b%2,b/=2,x[3]=b;
		x[8]=c%2,c/=2,x[7]=c%2,c/=2,x[6]=c;
		for(int i=0;i<9;i++){
			if((i+1)%3==1&&x[i]) cout<<'r';
			else if((i+1)%3==2&&x[i]) cout<<'w';
			else if((i+1)%3==0&&x[i]) cout<<'x';
			else cout<<"-";
		}
		cout<<endl;
	}
}
//ღゝ◡╹)ノ♡
```

---

