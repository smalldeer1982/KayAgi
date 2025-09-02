# Unary

## 题目描述

Unary is a minimalistic Brainfuck dialect in which programs are written using only one token.

Brainfuck programs use 8 commands: "+", "-", "\[", "\]", "<", ">", "." and "," (their meaning is not important for the purposes of this problem). Unary programs are created from Brainfuck programs using the following algorithm. First, replace each command with a corresponding binary code, using the following conversion table:

- ">" $ → $ 1000,
- "<" $ → $ 1001,
- "+" $ → $ 1010,
- "-" $ → $ 1011,
- "." $ → $ 1100,
- "," $ → $ 1101,
- "\[" $ → $ 1110,
- "\]" $ → $ 1111.

Next, concatenate the resulting binary codes into one binary number in the same order as in the program. Finally, write this number using unary numeral system — this is the Unary program equivalent to the original Brainfuck one.

You are given a Brainfuck program. Your task is to calculate the size of the equivalent Unary program, and print it modulo $ 1000003 $ $ (10^{6}+3) $ .

## 说明/提示

To write a number $ n $ in unary numeral system, one simply has to write 1 $ n $ times. For example, 5 written in unary system will be 11111.

In the first example replacing Brainfuck commands with binary code will give us 1101 1100. After we concatenate the codes, we'll get 11011100 in binary system, or 220 in decimal. That's exactly the number of tokens in the equivalent Unary program.

## 样例 #1

### 输入

```
,.
```

### 输出

```
220
```

## 样例 #2

### 输入

```
++++[&gt;,.&lt;-]
```

### 输出

```
61425
```

# 题解

## 作者：Withershine (赞：6)

[题面](https://www.luogu.com.cn/problem/CF133B)

在考虑如何优化程序时，不要忽略了这题的纯暴力做法。

## 对于样例 2
此处样例 2 的输入应该是 `++++[>,.<-]`，也许是翻译问题，但并不重要。

## 思路
依据题意，将输入的字符串 $s$ 转为其对应的二进制串 $str$，在暴力将 $str$ 由二进制转为十进制即可。

## 代码
为了防止因为幂运算而超时，这里使用了快速幂，~~虽然并没有快多少~~。
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#include<stdio.h>
#define ll long long
#define inf 0x3f3f3f3f
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
using namespace std;
inline char gchar()
{
    static char buf[1000000] , *p1 = buf , *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf , 1 , 1000000 , stdin) , p1 == p2) ? EOF : *p1++;
}
inline ll read()
{
    ll x = 0 , f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	  {
        if(ch == '-')
        {
        	f = -1;
		}
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
	  {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
string s;
string str;
#define mod 1000003
ll a , b , sum;
inline ll quickPower(ll a , ll b)
{
	ll ans = 1, base = a;
	while(b > 0)
    {
		if(b & 1)
		{
			ans *= base;
			ans %= mod;
		}
        base *= base;
        base %= mod;
		b >>= 1;
	}
	return ans;
}
signed main()
{
    cin >> s;
    fr(i , 0 , s.size() - 1)
    {
        if(s[i] == '>')
        {
            str += "1000";
        }
        else if(s[i] == '<')
        {
            str += "1001";
        }
        else if(s[i] == '+')
        {
            str += "1010";
        }
        else if(s[i] == '-')
        {
            str += "1011";
        }
        else if(s[i] == '.')
        {
            str += "1100";
        }
        else if(s[i] == ',')
        {
            str += "1101";
        }
        else if(s[i] == '[')
        {
            str += "1110";
        }
        else if(s[i] == ']')
        {
            str += "1111";
        }
    }
    ll o = 0;
    // cout << str << endl;
    fo(i , str.size() - 1 , 0)
    {
        ll kkk = str[i] - '0';
        sum += kkk * quickPower(2 , o) % mod;
        o++;
    }
    printf("%lld" , sum % mod);
    system("pause");
    return 0;
}
```


---

## 作者：_xEr_ (赞：1)



### 先看题目

解谜类，题目中出现的符号是密文，对应的二进制就是明文。
把密文解密后得到的二进制数转化为十进制输出即可。

### 再想思路

自然而然，想到用 ```map``` 来存储这种字符和数字间的对应关系。

之后，不难发现明文都是一段一段**四位**二进制，这样便可以用初赛时学习的四位折断法（二进制转十六进制时，每四位一转换）把二进制转化为十六进制。


如下：
```cpp
map<char,int>a;
a['>']=8; a['<']=9;
a['+']=10; a['-']=11;
a['.']=12; a[',']=13;
a['[']=14; a[']']=15;
```

最后只需要吧十六进制转化为十进制便可以了，灰常的简单。

### 关于样例

$~~~~~~$ 需知：<https://www.luogu.com.cn/discuss/195525>

### THE CODE
```cpp
#include<iostream>
#include<map>
using namespace std;
map<char,int>a;
string c;
int sum=1,ans=0;
int main(){
	a['>']=8; a['<']=9;
	a['+']=10; a['-']=11;
	a['.']=12; a[',']=13;
	a['[']=14; a[']']=15;
	cin>>c;
	for(int i=c.size()-1;i>=0;i--){
		ans+=(sum*a[c[i]])%1000003;
		sum=(sum*16)%1000003; 
	}
	cout<<ans%1000003; 
}

```

---

## 作者：Back_Stuff (赞：1)

这题给我的第一印象就是**水**，建议降橙。

楼上的大佬们竟然用映射`map`，本蒟蒻哭笑不得，直接用数组不就行了吗！

题目大意：将字符改为二进制，算出这个二进制数的值。

改变规则如下：

```
	'<'	->	1001
	'+'	->	1010
	'-'	->	1011
	'.'	->	1100
	','	->	1101
	'['	->	1110
	']'	->	1111
```
水题不多说，直接上代码。代码很丑，不喜勿喷。

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int MOD=1e6+3;//由于结果有可能很大，所以要模1000003，也就是1e6+3
string s;
int k[200],sum_Unary;
void k_init(){//k数组初始化
    memset(k,0,sizeof(k));//k数组清零
    k['>']=8,k['<']=9;
    k['+']=10,k['-']=11;
    k['.']=12,k[',']=13;
    k['[']=14,k[']']=15;
}
int main(){
    //freopen(".in","r",stdin);文件操作模板，我想放上
    //freopen(".out","w",stdout);
    cin>>s;
    k_init();
    fo(i,0,s.size()-1)
        sum_Unary=((sum_Unary*16)%MOD+k[s[i]])%MOD;
    //注意，每次要乘上2^4，也就是乘上16，而且在里面和外面都要模MOD
    cout<<sum_Unary%MOD<<endl;
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}

```
求过awa

---

## 作者：tzjahinie (赞：0)

### 题目链接：[CF133B](https://www.luogu.com.cn/problem/CF133B)

### 题目大意：

将一个字符串根据映射关系转化为二进制数，再将二进制数转化为一个十进制数。

### 题目思路：

直接按题意暴力模拟。可将四位的二进制数转化为一位的十六进制数，即将一个字符转化为一个十六进制数。最后将十六进制数转化为十进制数。使用 map 提前存储字符与十进制数的对应关系。代码如下：

~~~cpp
mp['>']=8 ;mp['<']=9 ;mp['+']=10;mp['-']=11;mp['.']=12;mp[',']=13;mp['[']=14;mp[']']=15;
for (int i=1;i<=n;i++){k*=16;k%=mod;k+=mp[str[i]];k%=mod;}
~~~

### 提交记录

因为你古的 RemoteJudge 爆了，于是展示一下 CF 上的提交记录。

![提交记录](https://cdn.luogu.com.cn/upload/image_hosting/19belw7w.png)

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e6+3;
int n,m,k;
string str;
map<char,int>mp;
int main(){
	cin>>str;
	n=str.length();
	str=' '+str;
	mp['>']=8 ;mp['<']=9 ;mp['+']=10;mp['-']=11;mp['.']=12;mp[',']=13;mp['[']=14;mp[']']=15;
	for (int i=1;i<=n;i++){k*=16;k%=mod;k+=mp[str[i]];k%=mod;}
	printf("%d",k);
}
```

### 最后

样例二的输入由于 CF 射线 导致变异了，原样例为应为：
~~~
++++[>,.<-]
~~~

---

## 作者：xh001 (赞：0)

# 题意
给定一个只包含特定字符的字符串，每个字符对应一个 $4$ 位二进制数，求把所有二进制数连在一起后再转为十进制后的值。
# 思路
我们都知道，$4$ 位二进制数其实就可以转换成 $1$ 位十六进制数，所以我们只需要把所有符号都转成十六进制数，最后再转回十进制即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1e6+3;
ll a[1001];//记录转成十六进制后每一位的值。 
ll sum=1;//实时计算每一位对应的大小。 
ll ans;//记录答案。 
ll n;
char s[101],c;
int main()
{
	a['>']=8;
	a['<']=9;
	a['+']=10;
	a['-']=11;
	a['.']=12;
	a[',']=13;
	a['[']=14;
	a[']']=15;//预处理转成十六进制后每一位的值。 
	while((c=getchar())!='\n') s[++n]=c;
	for(ll i=n;i>=1;i--)
	{
		ans=(ans+sum*a[s[i]])%mod;//转回十进制。 
		sum=(sum*16)%mod;
	}
	cout<<ans; 
	return 0;
}
```


---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF133B)

## 思路

模拟加上 map 映射。

先读入一个字符串，然后循环遍历，找到每个字符所对应的题目中的二进制串值，放到数组中。之后再次遍历这个字符串，每次把存储答案的 ans 数组乘上 $16$，就是目前二进制串中 $1$ 的个数。然后再加上这个字符的二进制串值，最后输出 ans 即可。

- 别忘每次运算都要取模。

- 如果不开 long long 程序就会爆炸。
 
## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e6+3;
map<char,int>mp;
long long ans;
const char c[]={'>','<','+','-','.',',','[',']'};
string s;
int main(){
	cin>>s;
	for(int i=0;i<8;++i)mp[c[i]]=i+8;
	for(int i=0;i<s.length();++i)ans=(ans*16%mod+mp[s[i]])%mod;
	cout<<ans<<endl;
    return 0;
}
~~~

[已 AC](https://www.luogu.com.cn/record/97166727)

---

## 作者：Siteyava_145 (赞：0)

简化题意：将字符串中的每个字符转化为对应的数字，再连成一个大数输出。

字符对应数字方法：```map```

连数方法：与十进制一样，原值 $\times 2^4+$ 这一位的值（```m[s[i]]```）。

于是：

```cpp
#include<bits/stdc++.h>
using namespace std;
map <char,int> m;
int cnt;
int main(){
    char c[10]={'>','<','+','-','.',',','[',']'};
    string s;
    cin>>s;
    for(int i=8;i<=15;i++){
        m[c[i-8]]=i;
    }
    for(int i=0;i<s.size();i++){
        cnt=(cnt*16%1000003+m[s[i]]/*转化*/)%1000003;/*模数，记住不要打成100003
    }
    cout<<cnt;
    return 0;
}
```


---

## 作者：_HiKou_ (赞：0)

总的来说，用 $map$ 把对应的十进制数存起来就可以了，然后每次加上一个数把 $ans$ 乘上 $16$（即相当于在后面接上另外一个四位二进制数）

觉得这道题可以改进，加上只有三位，两位，甚至一位的数。（虽然改了也不会很难）

哦对了，我做的时候第二个样例是有问题的。题目是保证只有这八个字符的，所以如果你的程序输出 $678154$ 那么程序应该是没有问题的。

CODE：

```
#include<bits/stdc++.h>
using namespace std;
map <char,int> a;//map存数值
long long ans=0;//不开 long long 也是可以的
int main(){
	string s;
	cin>>s;
	a['>']=8;
	a['<']=9;
	a['+']=10;
	a['-']=11;
	a['.']=12;
	a[',']=13;
	a['[']=14;
	a[']']=15;
	for(int i=0;i<s.length();i++)
	ans=((ans*16)%1000003+a[s[i]])%1000003;//记得模数
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：TRZ_2007 (赞：0)

**题解 [CF133B 【Unary】](https://www.luogu.com.cn/problem/CF133B)**  

# Description  
就是给你一些字符，每一个字符都有它所代表的数字，代表的数字如下表：    

```	'>'  	->	1000
	'<'		->	1001
    '+'		->	1010
    '-'		->	1011
    '.'		->	1100
    ','		->	1101
    '['		->	1110
    ']'		->	1111
```


（blog里面的表格好像挂了，看题解界面上的吧）  
上述数字均为二进制数。把这些字符拼在一起，组成一个**巨大**的二进制数，求把它转换成十进制后对 $10^6+3$ 取模的值。  

# Solution  
既然要我们最后把它转成十进制，那就不妨先把字符代表的二进制数转为十进制。所以现在的难点就是拼接。  
仔细观察上面的二进制数，我们会发现它们都是四位的，于是对于之前拼接的结果设为 $ans$ ，对于每一次拼接，只需要将 $ans$ 向左移4位即可，不要忘记取模。  

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int mod = 1e6 + 3;

map<char,int> mp;

char ch;
int ans;

void init() {	//开一个map，把所有字符所代表的的值存到map里
	mp['>'] = 8; mp['<'] = 9;
	mp['+'] = 10; mp['-'] = 11;
	mp['.'] = 12; mp[','] = 13;
	mp['['] = 14; mp[']'] = 15;
}

int main() {
	init();
	while(scanf("%c",&ch) != EOF) {
		if(ch != '\n') ans = ((ans << 4) % mod + mp[ch]) % mod;	//注意，ans自身乘以16之后为了保险建议对这个值先进行一次取模，最后对总值进行一次取模
		else break;
	}
	printf("%d\n",(ans + mod) % mod);	//以防莫名其妙的负数出现，所以在多加一次取模，但是这题应该是不可能的
	return 0;
}
```

---

## 作者：wenge (赞：0)

一道计算题。

只需要把每个字符替换后取模即可。但是所有的二进制数要替换成十进制数，并且二进制每4位要乘以$2^4=16$，而不是10000.

AC代码：
```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <stack>
using namespace std;
int f[128];
string s;
int main(){
	f[(int)'>']=8;
	f[(int)'<']=9;
	f[(int)'+']=10;
	f[(int)'-']=11;
	f[(int)'.']=12;
	f[(int)',']=13;
	f[(int)'[']=14;
	f[(int)']']=15;
	cin>>s;
	int ans=0;
	for(int i=0;i<s.size();i++){
		ans=((ans*16)%1000003+f[(int)s[i]])%1000003;
	}
	cout<<ans;
    return 0;
}
```

---

