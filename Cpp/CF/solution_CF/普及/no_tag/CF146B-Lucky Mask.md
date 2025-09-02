# Lucky Mask

## 题目描述

Petya loves lucky numbers very much. Everybody knows that lucky numbers are positive integers whose decimal record contains only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

Petya calls a mask of a positive integer $ n $ the number that is obtained after successive writing of all lucky digits of number $ n $ from the left to the right. For example, the mask of number $ 72174994 $ is number $ 7744 $ , the mask of $ 7 $ is $ 7 $ , the mask of $ 9999047 $ is $ 47 $ . Obviously, mask of any number is always a lucky number.

Petya has two numbers — an arbitrary integer $ a $ and a lucky number $ b $ . Help him find the minimum number $ c $ $ (c&gt;a) $ such that the mask of number $ c $ equals $ b $ .

## 样例 #1

### 输入

```
1 7
```

### 输出

```
7
```

## 样例 #2

### 输入

```
100 47
```

### 输出

```
147
```

# 题解

## 作者：L_zaa_L (赞：5)

## 分析
[题目链接](https://www.luogu.com.cn/problem/CF146B)


我们要 $a+1$ 开始计算，算到 $i$ 的“面罩数”是不是为 $b$，如果是，直接输出。

那我们也就可以直接暴力枚举了，因为最大 $i=177777$（这也就意味着，暴力枚举不会超时）。

而求 $i$ 的“面罩数”该怎么进行呢——我们可以直接从末尾开始判断末尾是不是 4 或 7 这个数，如果是，直接存加在一个数中，在去掉末尾，当下次在满足条件时，直接将记录的数乘上十，我们也就可以得到这个数的“面罩数”反过来的数（因为我们是倒着求的），再倒过来即可。

## Code
听了那么久 ~~（我自己都看不懂我写了什么）~~，还是要上代码的。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b;
int pd(long long s){//这个函数就是求i的“面罩数”了
	long long x=s,t=0,h=0;
	while(x!=0){
		if(x%10==4||x%10==7)
			h=h*10+x%10;
		x/=10;//去掉末尾的数
	}“面罩数”反过来的数
	while(h>0)
    {
        t=t*10+h%10;
        h=h/10;
    }//将求出的数倒过来
	return t;
}
int main(){
	cin>>a>>b;
	for(long long i=a+1;i<=177777;i++){//a+1开始是因为要比a大
		if(pd(i)==b){
			cout<<i;
			return 0;
		}
	}
} 
```
也没有太大的困难点，大概是 $\color{Goldenrod}\small\texttt{橘题（普及-）}$ 吧。

---

## 作者：2024sdhkdj (赞：4)

**[题面传送门](https://www.luogu.com.cn/problem/CF146B)**

## 题目大意：
定义一个数字为幸运数字，当且仅当一个数只有 $4$ 和 $7$ 这两种数字组成（当然也可以只包含一种数字）;再定义一个“面罩”，指按**高位到低位**的顺序选取这个数中的 $4$ 和 $7$ 组成的序列。给定两个数 $a$ 和 $b$，要求比 $a$ 大的、以 $b$ 为“面罩”的数字 $c$。
## 算法分析：
~~这是一道纯**模拟题**~~

原本我想的是**构造**这样一个满足条件的数字，但操作起来太过麻烦。再看一眼数据范围，$1 \le a,b \le 10^5$。可以直接**暴力枚举**！！！于是乎，我们可以从 $a + 1$  开始枚举，直到找到第一个满足条件的点时跳出。因为根据题意保证有解，所以不需要考虑无解的情况，不怕死循环。
## AC代码：
~~~
#include<bits/stdc++.h>
using namespace std;
int a,b,x;
bool check(int k){//检查其是否为给出的“面罩”
	int c=k,n=0,m=0;
	while(c){//求出当前数字的反“面罩”
		if(c%10==4||c%10==7)
			m=m*10+c%10;
		c/=10;
	}
	while(m){//求出当前数字的正“面罩”
		n=n*10+m%10;
		m/=10;
	}
	if(n==b)//如果符合条件
		return true;
	return false;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>a>>b;
	x=a+1;//从a+1开始枚举
	while(!check(x))//如果不满足条件
		x++;//继续枚举
	cout<<x;
	return 0;
}
~~~
[AC记录](https://www.luogu.com.cn/record/120711284)

~~[不要脸的推广一下我的BLOG](https://www.luogu.com.cn/blog/hsb0507/)~~


---

## 作者：Bpds1110 (赞：3)

[**原题传送门**](https://www.luogu.com.cn/problem/CF146B)
# 题面：
给出一个 $a$ 和 $b$，求出大于 $a$ 的一个数 $c$，要求 $c$ 包含 $4$ 或 $7$ 的最长子序列是 $b$，并且满足条件中要最小。
# Solution:
一道暴力枚举的水题。枚举每一个大于 $a$ 的数，如果这个数满足条件，就直接输出。至于如何判断是否满足条件，先把这个数包含 $4$ 或 $7$ 的最长子序列求出来，再判断它和 $b$ 是否相等。时间复杂度 $O(n)$，暴力不会超时。
# Code:
```
#include<bits/stdc++.h>
using namespace std;
int a,b;
bool check(int x)
{
	int s=0,ans=0,num;
	while(x!=0)
	{
		num=x%10;//取出个位 
		x/=10;//去掉个位 
		if(num!=4&&num!=7) continue;//如果不是4或7就跳过 
		s=(s<<1)+(s<<3)+num;//保存，相当于s=s*10+num 
	}
	while(s!=0)//把这个整数翻转 
	{
		num=s%10;//取出个位 
		s/=10;//去掉个位 
		ans=(ans<<1)+(ans<<3)+num;//保存
	}
	return ans==b;//返回子序列是否和b相等 
}
signed main()
{
	cin>>a>>b;
	a++;
	while(!check(a)) a++;//枚举每一个大于a的数 
	cout<<a;
	return 0;
}

```


---

## 作者：xiangshengtao (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF146B)
## 大意
寻找一个大于 $a$ 的数，且这个数中所有 $4$ 和 $7$ 按顺序拼起来是 $b$。
## 思路
我相信很多人都和我一样，刚看完题是有点懵逼的，但一看数据范围 $1 \leq a,b \leq 10^5$，或许就顿时明朗了许多，这是你就会马上想到暴力。
### 分析
那为什么就可以暴力呢？这不难想，其实最大也就只有 $177777$，时间绰绰有余！
### 方法
剩下的就只剩判断了，判断暴力到的数符不符合要求。首先取出各个数位，如果是 $4$ 和 $7$ 的其中一个就保存下来，然后重组，与 $b$ 判断就完工了。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long//务必开long long，不然会前功尽弃
using namespace std;
int a,b,f[1010];
bool pd(int x){
	int n=0,i,s=0,t,w;
	while (x>0){
		if (x%10==4||x%10==7) f[++n]=x%10;
		x=x/10;
	}
	t=1;w=n;
	while (t<=w) swap(f[t],f[w]),t++,w--;//取出的数是反的，一定要倒过来
	for (i=1;i<=n;i++) s=s*10+f[i];
	return s==b;
}
signed main(){
	scanf("%lld%lld",&a,&b);
	a++;//既然是大于，我们就从a+1开始
	while (!pd(a)) a++;
	printf("%lld\n",a);
	return 0;
}
```


---

## 作者：ssSSSss_sunhaojia (赞：1)

[**原题传送门**](https://www.luogu.com.cn/problem/CF146B)
# 题意简述：
给定两个数 $a$ 和 $b$，要求求出一个最小的 $c$，使得 $c<a$ 且当 $b$ 只保留 $4$ 和 $7$ 后与 $c$ 相等。
# 思路：
因为 $1 \leqslant a,b \leqslant 10^5$，所以 $c$ 不会超过 $177777$，我们就可以用暴力做这道题。先暴力枚举每种可能的 $c$，对于每一个可能的 $c$，我们判断它是否与只保留 $4$ 和 $7$ 后的 $b$ 相等。若相等，则直接输出；若不相等，则继续枚举。
# 代码：
```
#include <bits/stdc++.h>
using namespace std;
#define in inline
#define re register
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long LL;
LL a, b, top, top2, num[6], ans;
in bool check(LL x) {
    top = 0; top2 = 0, ans = 0; //注意清零
    while(x) num[++ top] = x % 10, x /= 10; //把x打散成数组的形式
    for(re int i = top; i >= 1; i --) //这里倒着遍历是因为打散后的x是倒过来的
        if(num[i] == 7 || num[i] == 4) ans = ans * 10 + num[i]; 
    return (ans == b); 
}
int main(){
    IOS;
    cin >> a >> b; 
    for(re int i =  a + 1; i; i ++) //暴力枚举
        if(check(i)) {cout << i; break; }
    return 0;
}
```

---

## 作者：gloomy_ (赞：1)

暴力枚举。
对于一个数来说，将它按数位拆分，如果是 $4$ 或 $7$ 就存到数组里。  
```cpp
while(x>0)
{
	if(x%10==4||x%10==7)
	{
		t[i]=x%10;
		i++;
	}
	x/=10;
}
```
特别要注意，这种方法是从个位开始找的，所以最后需要再正过来，并存在一个整型中。例如 $t$ 数组为 `1、2、3、4、5`，$s$ 存储面罩，从 $t_4$ 开始，$s$ 加上 $t_4$，再乘 $10$，给下一位留出位置，以此类推。全部结束后，$s$ 除以 $10$，去掉不要的空位。
```cpp
int s=0;
for(int j=i;j>=1;j--)
{
	s=(s+t[j])*10;
}
s/=10;
```
由此写一下面罩函数。
```cpp
int mianzhao(int x)
{
	int t[10]={0},i=1;//t数组倒序存储面罩 
	while(x>0)
	{
		if(x%10==4||x%10==7)
		{
			t[i]=x%10;
			i++;
		}
		x/=10;
	}
	int s=0;
	for(int j=i;j>=1;j--)
	{
		s=(s+t[j])*10;
	}
	s/=10;//利用位值原理正过来 
	return s;
}
```  
**AC Code**  
```cpp
#include<bits/stdc++.h>
using namespace std;
int mianzhao(int x)
{
	int t[10]={0},i=1;//t数组倒序存储面罩 
	while(x>0)
	{
		if(x%10==4||x%10==7)
		{
			t[i]=x%10;
			i++;
		}
		x/=10;
	}
	int s=0;
	for(int j=i;j>=1;j--)
	{
		s=(s+t[j])*10;
	}
	s/=10;//利用位值原理正过来 
	return s;
}
int main()
{
	int a,b;
	cin>>a>>b;
	int i;
	for(i=a+1;mianzhao(i)!=b;i++);
	cout<<i;
	return 0;
} 
```



---

## 作者：zwy__ (赞：1)

### 题意
只要一个数它的构成只有 $4$ 和 $7$，我们就说这个数是幸运数字。并且定义一个数的面罩为这个数从高到低每一位是 $4$ 或 $7$ 的数。比如： $2147483647$ 的面罩为 $47447$。先给出你两个变量 $a$ 和 $b$，求一个数，保证这个数比 $a$ 大一个 $b$ 的面罩的数，并且保证这个数最小。
### 思路
一道非常简单的暴力枚举题。按照以下步骤做题即可。
1. 我们写一个输出一个数的面罩的函数，以便我们后续操作。
2. 因为要求的答案要比 $a$ 大，所以枚举的范围从 $a+1$ 开始。

明确了这些要求，我们就可以开始做题了。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,x,t,h;
int f(int s)//写出一个数面罩的值的函数 
{
	x=s;
	t=0;
	h=0;
	while(x!=0)
	{
		if(x%10==4||x%10==7)h=h*10+x%10;
		x/=10;
	}
	while(h>0)
    {
        t=t*10+h%10;
        h=h/10;
    }
	return t;
}
int main()
{
	cin>>a>>b;
	for(int i=a+1;; i++)//循环找答案 
	{
		if(f(i)==b)
		{
			cout<<i;
			return 0;
		}
	}
	return 0; 
} 
```


---

## 作者：Ninelife_Cat (赞：1)

~~更暴力的~~暴力枚举。

考虑最坏情况 $ans=177777$ 最多枚举不超过 $2e5$ 个数。

所以从 $a+1$ 开始枚举，将每个数的“面罩”记录下来并与 $b$ 比较，如果找到相同的就直接输出。

~~卡常大法好！！1~~

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define ri register//奇怪的卡常技巧1
#define int long long
#define inf 2147483647
#define mp(x,y) make_pair((x),(y))
#define reset(x,y) memset((x),(y),sizeof((x)))
using namespace std;
inline int read()
{
	int x=0;bool f=false;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') f=true;c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^'0');c=getchar();}
	return f?-x:x;
}//奇怪的卡常技巧2
int a,b;
inline int Pow(int a,int b)
{
	ri int ans=1;
	while(b)
	{
		if(b&1) ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}//奇怪的卡常技巧3
//快速幂(用自带的pow函数会T飞
signed main()
{
	a=read();b=read();
	if(b>a) return cout<<b,0;
   	//小优化,如果b比a大那么符合条件的数一定是b
	for(ri int i=a+1;;++i)
	{
		ri int p=i,q=0,cnt=0;
		while(p)
		{
			if(p%10==7) q+=7*Pow(10,cnt),++cnt;
			if(p%10==4) q+=4*Pow(10,cnt),++cnt;
			p/=10;
		}
       		//分离出每个数的“面罩”
		if(q==b) return cout<<i,0;
	}
	return 0;
}

---

## 作者：liukangyi (赞：0)

# 题目大意
定义：“幸运数”指各个数位上全是 $4$ 与 $7$ 的数，“面罩”指一个数从高位到低位所有为 $4$ 或 $7$ 的数字串起来得到的一个数。

------------
现在给你数字 $a$ 与 数字 $b$ ，现在请你输出大于 $a$ 的“面罩”是 $b$ 的最小的数。


------------
# 分析
这道题因为是要大于 $a$ 的数，所以我们可以从 $a + 1$ 开始不断往上枚举，但是我在判断一个数是否满足条件时，是将它先转为字符串，然后从左到右遍历每一个字符，如果是 $4$ 或 $7$ 的话就将它加入成为“面罩”的一部分，最后看看“面罩”是否与 $b$ 一样（注意： $b$ 要定义为 string 类型）。


------------
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
//定义变量 
int a;
string b;

//转换为字符串 
string Change(int num){
	string ans="";
	while(num){
		char ch=num%10+'0'; //把当前数位上的数变为字符 
		ans=ch+ans;
		num/=10;
	}
	return ans;
}

//判断“面罩”是否与题目所给的要求“面罩”b相等 
bool Check(string s){
	string sum="";
	for(int i=0;i<s.size();i++)
		if(s[i]=='4'||s[i]=='7') //如果当前字符是4或7 
			sum+=s[i];
	return sum==b;
}
int main(){
	cin>>a>>b;
	for(int i=a+1;;i++){
		string tmp=Change(i); //用tmp存储将数字转换后的结果 
		if(Check(tmp)){ //判断是否符合条件 
			cout<<i;
			return 0;
		}
	}
	return 0;
} 
```


---

## 作者：alex_liu (赞：0)

这道题连我这个蒟蒻也觉得挺简单的。

注意寻找“面罩”时的细节。

# 前置芝士： 
当你把一个数按数位拆分时（举 $114514$ 为例），就可以分成这样：

$$114514=1*100000+1*100000+4*1000+5*100+1*10+4*1$$

如果设当前位在数中为第 $n$ 个数。

那么当前拆分的这位数在原数中的值为：

当前数 $\times 10^{n-1}$ 

# AC Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b;
inline int read(){
	int x=0;bool f=false;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=true;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^'0');c=getchar();}
	return f?-x:x;
}//快读。
inline int Pow(int a,int b){
	int ans=1;
	while(b!=0){
		if(b&1)ans*=a;
		a*=a;
		b>>=1;
	}
	return ans;
}//快速幂。 
signed main(){
	a=read();b=read();//输入。
	if(b>a){//特判。 
		cout<<b<<endl;//输出。
		return 0;//结束程序。
	}else{
		for(int i=1+a;;i++){//枚举比a大的数。 
			int p=i,q=0,cnt=0;//p为当前数（为了不改变i的值），q为“面具”数值，cnt为一共有多少位“面具”。
			while(p!=0){//每一位按照题目要求判断。 
				if(p%10==7){//当前位为7。
					q+=7*Pow(10,cnt);//“面具”数值增加（前置芝士里说了）。
					cnt++;//计数器+1。
				}
				if(p%10==4){//当前位为4。 
					q+=4*Pow(10,cnt);//“面具”数值增加（前置芝士里说了）。
					cnt++;//计数器+1。
				}
				p/=10;//下一位。 
			}
			if(q==b){//符合要求。
				cout<<i<<endl;//输出。
				return 0;//结束程序。
			}
		}
	}
	return 0;//完结撒花！
}
```

祝您早日AC！！！

 ^(￣(oo)￣)^ 

---

## 作者：Lylighte (赞：0)

没人来啊？这么简单的暴力枚举……

题意：找出大于 $a$ 的最小整数 $c$，使 $c$ 从最高位到最低位的所有 $7$ 和 $4$ 拼起来的数等于 $b$，$1\le a,b\le 10^5$。

先说下我推出的时间复杂度：$O(n\log_{10}n)$，$n<2\times 10^6$。

考虑构造一个数 $d$，在 $b$ 的最高位前添上 $1$，得到数 $d$，显然 $d$ 的 mask 是 $b$。反复在 $d$ 前面添上 $1$，直到 $d>a$。

因为 $a\le 10^5$，所以得出 $a < d<2\times 10^6$ 这个 $d$ 的范围（最坏情况或许是 $b=777777$，此时 $d=1777777$，没到 $2\times 10^6$），那么 $a<c\le d$，得出枚举范围。

求 mask 就是反复取最低位，是 $4$ 或 $7$ 就记录一下，然后舍去最低位。

求一个数的 mask 时间复杂度为 $O(\log_{10}n)$，比较的复杂度为 $O(1)$，总体来说是 $O(n\log_{10}n)$，不会超的……

贴代码（看注释）:

```cpp
#include <bits/stdc++.h>
using namespace std;
int a, b;
int Make(int x){//求一个数的 翻转后的 mask
    int ans=0;
    while(x>0){
        if(x%10==4||x%10==7)//我为什么要用时间换空间(因为取模是O(1)的运算?)
            ans = ans*10+(x%10);//发现没，mask 翻转了一遍，不影响，我也不想改，因此有了下面的语句
        x /= 10;
    }
    return ans;
}
int main(){
    cin >> a >> b;
    int bt = Make(b);//所以有了这一句
    for(int i=a+1;;i++){//没有终止条件，退出全靠下面的 break
        int t = Make(i);
        if(t==bt){//根据上面的分析，可以在一定的范围内找出 c(程序中的 t)
            cout << i << endl;
            break;
        }
    }
    return 0;
}
```

难度大约是橙？

---

