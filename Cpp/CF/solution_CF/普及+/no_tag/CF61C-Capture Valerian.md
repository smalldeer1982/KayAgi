# Capture Valerian

## 题目描述

It's now $ 260 $ AD. Shapur, being extremely smart, became the King of Persia. He is now called Shapur, His majesty King of kings of Iran and Aniran.

Recently the Romans declared war on Persia. They dreamed to occupy Armenia. In the recent war, the Romans were badly defeated. Now their senior army general, Philip is captured by Shapur and Shapur is now going to capture Valerian, the Roman emperor.

Being defeated, the cowardly Valerian hid in a room at the top of one of his castles. To capture him, Shapur has to open many doors. Fortunately Valerian was too scared to make impenetrable locks for the doors.

Each door has $ 4 $ parts. The first part is an integer number $ a $ . The second part is either an integer number $ b $ or some really odd sign which looks like R. The third one is an integer $ c $ and the fourth part is empty! As if it was laid for writing something. Being extremely gifted, after opening the first few doors, Shapur found out the secret behind the locks.

 $ c $ is an integer written in base $ a $ , to open the door we should write it in base $ b $ . The only bad news is that this R is some sort of special numbering system that is used only in Roman empire, so opening the doors is not just a piece of cake!

Here's an explanation of this really weird number system that even doesn't have zero:

Roman numerals are based on seven symbols: a stroke (identified with the letter I) for a unit, a chevron (identified with the letter V) for a five, a cross-stroke (identified with the letter X) for a ten, a C (identified as an abbreviation of Centum) for a hundred, etc.:

- I= $ 1 $
- V= $ 5 $
- X= $ 10 $
- L= $ 50 $
- C= $ 100 $
- D= $ 500 $
- M= $ 1000 $

Symbols are iterated to produce multiples of the decimal ( $ 1 $ , $ 10 $ , $ 100 $ , $ 1,000 $ ) values, with V, L, D substituted for a multiple of five, and the iteration continuing: I $ 1 $ , II $ 2 $ , III $ 3 $ , V $ 5 $ , VI $ 6 $ , VII $ 7 $ , etc., and the same for other bases: X $ 10 $ , XX $ 20 $ , XXX $ 30 $ , L $ 50 $ , LXXX $ 80 $ ; CC $ 200 $ , DCC $ 700 $ , etc. At the fourth and ninth iteration, a subtractive principle must be employed, with the base placed before the higher base: IV $ 4 $ , IX $ 9 $ , XL $ 40 $ , XC $ 90 $ , CD $ 400 $ , CM $ 900 $ .

Also in bases greater than $ 10 $ we use A for $ 10 $ , B for $ 11 $ , etc.

Help Shapur capture Valerian and bring peace back to Persia, especially Armenia.

## 说明/提示

You can find more information about roman numerals here: http://en.wikipedia.org/wiki/Roman\_numerals

## 样例 #1

### 输入

```
10 2
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
16 R
5
```

### 输出

```
V
```

## 样例 #3

### 输入

```
5 R
4
```

### 输出

```
IV
```

## 样例 #4

### 输入

```
2 2
1111001
```

### 输出

```
1111001
```

## 样例 #5

### 输入

```
12 13
A
```

### 输出

```
A
```

# 题解

## 作者：___define___ (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF61C)

题意这里就不说了，翻译中已经说的很清楚了。

## 思路

这题难就难在与罗马进制之间的转换，至于普通的进制转换可以去做[这题](https://www.luogu.com.cn/problem/P1143)。

仔细观察下表就可以发现，其实罗马数字是一个数位一个数位组合起来的，例如：$29$ 是由 $20$（`XX`）和 $9$（`IX`）组合起来得成的。

![](https://cdn.luogu.com.cn/upload/image_hosting/0f21qx9c.png)

而原题中说保证转罗马进制的数 $0 \le a \le (3000)_{10}$ 。我们不难发现，不管在什么数位上， $1 \sim 9$ 的格式是一定的。

结合以上几点，再根据题目中给出的关于罗马进制的小提示，我们便可以写出十进制转罗马进制的代码了。

最后套 [P1143](https://www.luogu.com.cn/problem/P1143) 的代码再修改一下，特判罗马进制的情况，这道题就可以做出来了。

![](https://cdn.luogu.com.cn/upload/image_hosting/ffeb397d.png)

```
#include<bits/stdc++.h>
#define ll long long

#define xh(x,y) for(ll i=x;i<=y;i++)
#define dxh(x,y) for(ll i=x;i>=y;i--)

using namespace std;
ll x,y,sh,ans,z[1919810];
bool b=0;
string s,ls[10]{"","I","II","III","IV","V","VI","VII","VIII","IX"};
string sw[10]{"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"};
string bw[10]{"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};
string qw[4]{"","M","MM","MMM"};
string lm;
void zs(){
	dxh(s.size()-1,0)
	if(s[i]>='0'&&s[i]<='9') sh+=(long long)((long long)(s[i]-'0')*(long long)(pow(x,s.size()-1-i)));
	else sh+=(long long)(s[i]-'A'+10)*(long long)(pow(x,s.size()-1-i));
}
void zy(){
	if(y<11){
		for(;sh>0;sh/=y)
			z[++ans]=sh%y;
		dxh(ans,1)
		cout<<z[i];
	}
	else {
		for(;sh>0;sh/=y)
			if(sh%y>9) z[++ans]=sh%y+55;
		else z[++ans]=sh%y;
		dxh(ans,1)
		if(z[i]>9) cout<<char(z[i]);
		else cout<<z[i];
	}
}
int main(){
	cin>>x>>lm>>s;
	
	int num_0=0;
	for(int i=0;i<s.size();i++)
		if(s[i]=='0') num_0++;
	if(num_0==s.size())
	{
		return cout<< "0" , 0;
	}

	if(lm=="R"){
		if(x!=10) zs();
		else
			xh(0,s.size()-1)
			sh*=10,sh+=s[i]-'0';
		if(sh/1000!=0) cout<<qw[sh/1000];
		if(sh/100!=0) cout<<bw[sh/100%10];
		if(sh/10!=0) cout<<sw[sh/10%10];
		cout<<ls[sh%10];
		return 0;
	}
	else 
		if(lm.size()>1) y=(lm[0]-'0')*10+(lm[1]-'0');
	else y=lm[0]-'0';
	if(x!=10) zs();
	else{
		xh(0,s.size()-1)
		sh*=10,sh+=s[i]-'0';
	}
	zy();
	return 0;
}
```

温馨提示：要开 `long long`。

---

## 作者：__UrFnr__ (赞：2)

**题目大意：**

不用说，已经很清晰了，就是 $x$ 进制转 $y$ 进制，多加一种罗马进制。

**题目思路：**

普通的进制转换，只需将转换的结果倒序输出，详见[这里](https://www.luogu.com.cn/problem/P1143)，只要会了这个，这道题就解决一大半了。

罗马进制可以上网查找一下资料，大概明白后就可以了（在原题面上有每个字符代表的数字）

如果你还不懂，那就[看这个](https://baike.baidu.com/item/%E7%BD%97%E9%A9%AC%E8%AE%B0%E6%95%B0%E6%B3%95/22761410?fr=ge_ala)。

由于需要转换的数范围是 $0\le n \le (3000)_{10}$，所需最大的符号就是 ```M```（代表 $1000$），然后把一下的符号全部找出来，再找出对应大小，模拟即可。

代码如下：


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int rz[13] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};//罗马计数法字符对应的大小
string rs[13] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};//罗马计数法的字符
int n, mm, x, t = 1;
string b;
char m;
signed main () {
    cin >> n >> m;
    if (m != 'R') {
        mm = m - '0';
        mm *= 10;
        m = getchar ();
        if (m != '\n') mm += m - '0';
        else mm /= 10;
    }//处理进制的大小（由于可能是 R，所以是字符）
    cin >> b;
    for (int i = b.size () - 1; i >= 0; i --) {
        int w = 0;
        if (b[i] >= 'A') w = b[i] - 'A' + 10; 
        else w = b[i] - '0';
        x += w * t;
        t *= n;
    }//把这个数算出来
    if (m == 'R') {
        for (int i = 12; i >= 0; i --) {
            while (x / rz[i] > 0) {
                cout << rs[i];
                x -= rz[i];
            }
        }
        return 0;
    }//转换为罗马进制输出，结束
    stack <char> s;//用栈储存转换后的数，可以倒序输出
    while (x > 0) {//处理
        int k = x % mm;
        if (k >= 10) s.push (k + 55);
        else s.push (k + '0');
        x /= mm;
    }
    if (s.empty ()) {//特判
        cout << 0;
        return 0;
    }
    while (! s.empty ()) {//倒序输出
        cout << s.top ();
        s.pop ();
   }
}
```

还是那句老话：要开 ```long long```。

---

## 作者：Chbin (赞：0)

[题面跳转](https://www.luogu.com.cn/problem/CF61C)

## 题目大意
把 $a$ 进制数 $c$ 转换成 $b$ 进制或使用罗马数字表示。

## 思路
1. 把 $a$ 进制数 $c$ 转换成十进制。这一步可使用“[按权相加法](https://www.baidu.com/s?wd=%E6%8C%89%E6%9D%83%E7%9B%B8%E5%8A%A0%E6%B3%95&rsv_spt=1&rsv_iqid=0xd3ffecef0094da55&issp=1&f=3&rsv_bp=1&rsv_idx=2&ie=utf-8&tn=68018901_17_pg&rsv_enter=1&rsv_dl=ih_1&rsv_sug3=1&rsv_sug1=1&rsv_sug7=001&rsv_sug2=1&rsv_btype=i&rsp=1&rsv_sug9=es_2_1&rsv_sug4=1299&rsv_sug=2)”，即“乘位权”。把每一位都乘上这一位的位权，再把积相加即可。

2. 把十进制数 $c$ 转成 $b$ 进制或转换成罗马数字表示（具体转换成什么题目有说）。若要转换成 $b$ 进制数，可以使用“[除 $k$ 取余法](https://baike.baidu.com/item/%E9%99%A4k%E5%8F%96%E4%BD%99%E6%B3%95/19385576?fr=ge_ala)”。把 $c$ 除以 $b$，将得到的商记录下来。重复执行这一操作，直到商为 $0$ 才结束循环。再将之前得到商倒序输出（先输出最后一个得到的，然后一直输出它的前一个，直到第一个商已输出）若要转换成罗马数字表示，由于方法较复杂，建议[找度娘](https://www.baidu.com/s?ie=utf-8&f=3&rsv_bp=1&rsv_idx=2&tn=68018901_17_pg&wd=%E9%98%BF%E6%8B%89%E4%BC%AF%E6%95%B0%E5%AD%97%E8%BD%AC%E7%BD%97%E9%A9%AC%E6%95%B0%E5%AD%97%E7%9A%84%E6%96%B9%E6%B3%95&rsv_spt=1&oq=%25E9%2598%25BF%25E6%258B%2589%25E4%25BC%25AF%25E6%2595%25B0%25E5%25AD%2597%25E8%25BD%25AC%25E7%25BD%2597%25E9%25A9%25AC%25E6%2595%25B0%25E5%25AD%2597&rsv_pq=b0b1a9e90053cce2&rsv_t=11afvZzSLCBlM4WVfJn6BjQ83ZaZKnbrXc2%2BA%2F0MR2UFl3z%2BiFCIWGh3i4b8J9j%2Bvp2RFHg&rqlang=cn&rsv_enter=1&rsv_dl=ts_4&rsv_btype=t&rsv_sug3=27&rsv_sug1=26&rsv_sug7=100&rsv_sug2=1&prefixsug=%25E9%2598%25BF%25E6%258B%2589%25E4%25BC%25AF%25E6%2595%25B0%25E5%25AD%2597%25E8%25BD%25AC%25E7%25BD%2597%25E9%25A9%25AC%25E6%2595%25B0%25E5%25AD%2597&rsp=4&rsv_sug4=2317&rsv_sug=1)。

## 注意
要使用 `long long`，因为 $c$ 可能会超出 `int` 范围，达到 $10^{15}$。

## AC Code (C++)

![](https://cdn.luogu.com.cn/upload/image_hosting/wa75mqub.png)

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a;
string b,c;
string rome[10005]={"","I","II","III","IV","V","VI","VII","VIII","IX","X"};//将1~10的表示方法放入数组中，方便查找 
int main(){
	cin>>a>>b>>c;
	long long d=1,num=0;//d用于计算位权，num用于记录最终结果 
	for(long long i=c.size()-1;i>=0;i--)
	{
		if(c[i]<='9') num+=(c[i]-48)*d;
		else num+=(c[i]-65+10)*d;
		d*=a;
	}//转换为十进制数 
	if(num==0)
	{
		cout<<0;
		return 0;
	}//若结果为0，直接输出0并结束运行 
	if(b[0]!='R')//判断是否需要转成罗马数字（b[0]=='R'表示需要转成罗马数字）。 
	{
		long long jz=0,num2n=0; 
		char num2[10005];
		if(b.size()==1) jz=b[0]-48;
		else jz=(b[0]-48)*10+(b[1]-48);
		for(;num>0;num/=jz)
		{
			if(num%jz<=9) num2[++num2n]=char(num%jz+48);
			else num2[++num2n]=char(num%jz+65-10);
		}
		for(long long i=num2n;i>=1;i--)
			cout<<num2[i];
		return 0;
	}//将num转成b进制数
	//以下部分用于将num转换成罗马数字 
	if(num>=1000)
	{
		for(long long i=1;i<=num/1000;i++)
			cout<<"M";
		num%=1000;
	}
	if(num>=100 && num<1000)
	{
		if(num>=500)
		{
			if(num<900)
			{
				cout<<"D";
				for(long long i=6;i<=num/100;i++)
					cout<<"C";
			}
			else cout<<"CM";
		}
		else
		{
			if(num<400)
			{
				for(long long i=1;i<=num/100;i++)
					cout<<"C";
			}
			else cout<<"CD";
		}
		num%=100;
	}
	if(num<100)
	{
		if(num>=50)
		{
			if(num<90)
			{
				cout<<"L";
				for(long long i=6;i<=num/10;i++)
					cout<<"X";
			}
			else cout<<"XC";
		}
		else
		{
			if(num<40)
			{
				for(long long i=1;i<=num/10;i++)
					cout<<"X";
			}
			else cout<<"XL";
		}
		num%=10;
	}
	cout<<rome[num];
	return 0;
}
```

---

## 作者：Nightsky_Stars (赞：0)

题目说的很清楚了，这里我就不过多赘述了。

这道题很简单，直接暴力依题意模拟就完事了。

# CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[13]={1,4,5,9,10,40,50,90,100,400,500,900,1000};
string r[13]={"I","IV","V","IX","X","XL","L","XC","C","CD","D","CM","M"};
ll n,x,s,t=1;
string b;
char m;
int main(){
	cin>>n>>m;
	if(m!='R'){//如果不是罗马进制
		x=m-'0';
		x*=10;
		m=getchar();
		if(m=='\n')x/=10;
		else x+=m-'0';
	}
	cin>>b;
	for(int i=b.size()-1;i>=0;i--){
		int u=0;
		if(b[i]>='A') u=b[i]-'A'+10;
		else u=b[i]-'0';
		s+=u*t;
		t*=n;
	}
	if(m=='R'){
		for(int i=12;i>=0;i--){
			while(s>=a[i]){
				cout<<r[i];
				s-=a[i];
			}
		}
		return 0;
	}
    stack<char> q;//栈逆序输出
    while(s>0){
    	int k=s%x;
    	if(k>=10) q.push(k+55); 
		else q.push(k+'0');
		s/=x;
	}
	if(q.empty()){
		cout<<0<<"\n";
		return 0;
	}
	while(!q.empty()){
		cout<<q.top();
		q.pop();
	}
	return 0;
}
```

---

## 作者：__Cby___ (赞：0)

## 题意
`k` 进制转 `k2` 进制，多一种罗马进制。　
## 思路
### 存储方式
楼下表示会 `MLE`，这里提供一个技巧。  
边算边输出。~~它不香吗又不用存~~
### 罗马进制处理
```cpp
int O[13]={1,4,5,9,10,40,50,90,100,400,500,900,1000};
string R[13]={"I","IV","V","IX","X","XL","L","XC","C","CD","D","CM","M"};
	if(m=='R'){
		for(int i=12;i>=0;i--){
			while(s>=O[i]){
				cout<<R[i];
				s-=O[i];
			}
		}
		return 0;
	}
```
~~打表大法好~~  
要从大往小处理，注意，表中须有 `IV` 或 `IX` 之类的数据，否则 $4$ 会输出 `IIII`。同时可以用 `map` 储存。~~但我懒得用~~
## 普通进制转换
网上教程多的去了，详情见[这](https://www.luogu.com.cn/problem/solution/P1143)。
# 代码
```cpp
#include <iostream>
#include <stack>
using namespace std;
int O[13]={1,4,5,9,10,40,50,90,100,400,500,900,1000};
string R[13]={"I","IV","V","IX","X","XL","L","XC","C","CD","D","CM","M"};
int main(int argc,char **argv){
	int n;
	char m;
	int m2=0;
	cin>>n>>m;
	if(m!='R'){//若非罗马进制
		m2=m-'0';
		m2*=10;
		m=getchar();
		if(m=='\n')m2/=10;//前面乘了10,要除回去
		else m2+=m-'0';
	}
	string b;
	cin>>b;
	long long int s=0;//记得开long long
	long long int t=1;
	for(int i=b.length()-1;i>=0;i--){
		int u=0;
		if(b[i]>='A'){
			u=b[i]-'A'+10;
		}
		else{
			u=b[i]-'0';
		}
		s+=u*t;
		t*=n;
	}
	if(m=='R'){
		for(int i=12;i>=0;i--){
			while(s>=O[i]){
				cout<<R[i];//直接输出
				s-=O[i];
			}
		}
		return 0;
	}
    stack<char> q;//stack逆序输出
    while(s>0){
    	int e=s%m2;
    	if(e>=10){
    		q.push(e+55); 
		} 
		else {
			q.push(e+'0');
		}
		s/=m2;
	}
	if(q.empty()){
		cout<<0<<endl;
		return 0;
	} 
	while(!q.empty()){
		cout<<q.top();
		q.pop();
	}
	
	return 0;
}

```


---

## 作者：chang_an_1029 (赞：0)

**题意**

给定一个 $ n $ 进制的数，将它转换为 $ m $ 进制或罗马进制



------------


**大致思路**

容易想到，可以分两种情况来处理。判断 $ m $ 是否等于 $ R $ 。如果 $ m=R $ ，输出罗马进制，否则转换为 $ m $ 进制 $ (m{=}\mathllap{/\,}R) $ 。

首先我们处理转换为 $ m $ 进制的情况。将 $ n $ 进制转换为 $ m $ 进制，需要把 $ n $ 进制先转化为 $ 10 $ 进制，再从 $ 10 $ 进制转化为 $ m $ 进制。

$ n $ 进制转 $ 10 $ 进制的方法：

** _按权相加法_ **

把 $ n $ 进制数先写成加权系数展开式，

然后再按 $ 10 $ 进制的加法求和，

得到 $ 10 $ 进制数。

例:将 $ 8 $ 进制数转为 $ 10 $ 进制，计算过程如下:

$$ (1234)_8=1\times8\times8\times8+2\times8\times8+3\times8\times8+4 $$

即:

$$ (abcde......)_n=a\times(n^{len-1})+b\times(n^{len-2})+...... $$


```
int to_10(string s,int n){
	int _10=0;//存储转换为十进制后的结果
	for(int i=0;i<s.size();i++){
		if(s[i]>='0'&&s[i]<='9') _10+=(s[i]-'0')*pow(n,s.size()-i-1);//当这一位在0到9之间,直接套进制转换模板
		else _10+=(s[i]-'A'+10)*pow(n,s.size()-i-1);//否则处理后再使用按权相加法
	}
	return _10;
}
```

以上便是 $ n $ 进制转换为 $ 10 $ 进制的示例代码

接下来要处理 $ 10 $ 进制转换为 $ m $ 进制



------------



$ 10 $ 进制转 $ m $ 进制,须除 $ m $ 取余,逆序排列:

用 $ m $ 除要进行转换的 $ 10 $ 进制数,

得到一个商和余数,

再用 $ m $ 除以商得到又一个商和余数

一直继续下去,直到商为 $ 0 $ ,

逆序排列,

得到 $ m $ 进制数

```c
string change(string s,int n,int m){
	vector<int>t;//用于存储n进制转换为10进制后的数
	int _10=to_10(s,n);//处理十进制
	while(_10){
		t.push_back(_10%m);
		_10/=m;
	}//存入vector,除n取余
	int l=0,r=t.size()-1;
	while(l<r){
		l++,r--;
		swap(t[l],t[r]);
	}
	string res;//存储转换结果
	for(int i=0;i<=t.size()-1;i++){
		char x;
		if(t[i]>=10) x=t[i]-10+'A';
		else x=t[i]-0+'0';
		res+=x;
	}
	return res;//转化为m进制,逆序排列
}
```


------------


处理完 $ n $ 进制转化为 $ m $ 进制,现在处理 $ R $ 进制



------------


```c
vector<int>ten={1,4,5,9,10,40,50,90,100,400,500,900,1000};//存储十进制数字
vector<string>R={"I","IV","V","IX","X","XL","L","XC","C","CD","D","CM","M"};//存储罗马进制
string change2(int _10){//十进制转罗马进制
	string res;
	for(int i=ten.size()-1;i>=0;i--){
		while(_10>=ten[i]) res+=R[i],_10-=ten[i];
	}//由于是正序储存,所以需要倒序枚举
	return res;
}
```



------------


**读入**

下面给出一种处理方式:

```c
string s;
int n;
char m;
cin>>n>>m>>s;
if(m=='R'){
	cout<<change2(to_10(s,n));
	return 0;
}
s=change(s,n,m-'0');
cout<<s;
```

拒绝 Ctrl+C 

------------

如果你还没有看到这里就将代码复制并且提交,你会发现出现了 MLE 。显然,上述程序的空间并不是最优。


关于更优处理 ( 参考  Confringo ) :


首先去除开头空格，


是负号则记录，


然后删去，转为 $ 10 $ 进制。


最后把 $ 10 $ 进制转化为目标进制，


然后如果记录过负号,


则再连接一个负号


当然，对于空间复杂度优化的方式并不是只此一种，在此处就不一一赘述了。


文末附上题目链接：


https://www.luogu.com.cn/problem/CF61C





------------



**The End**



---

## 作者：Confringo (赞：0)

### 提示
本题解介绍比较详细，若觉得代码要点过于简单，可粗略浏览。

---

### 题意简述

输入三个字符串，分两种情况：（以下称第一个为 $A$ ，第二个为 $B$ ，以此类推）  
1. 当 $B$ 为字母 R 时，把 $A$ 进制下的数 $C$ 转为罗马数字；
2. 当 $B$ 为数字时，把 $A$ 进制下的数 $C$ 转为 $B$ 进制下的数。

---

### 考点剖析
本题考察的是罗马数字和阿拉伯数字的转换，以及不同进制数字的转换。

---

### 代码要点
Q1: 输入应该用什么类型？  
A1: 输入格式应该为整数 $A$ 和字符串 $B$ 和 $C$。  
同时，为了应对 $B$ 不是字母 R 的情况，应该定义一个字符串转整型的函数。

此处我们使用了istringstream的特性，从字符串中输入一个整数。（和从cin中输入一个道理）
```cpp
long long str2int(string str){
	istringstream is(str);
	int i;
	is>>i;
	return i;
}
```

Q2: 如何进行进制转换？（建议配合下文 notR 函数阅读）  
A2: 首先去除开头空格，如果是负号记录一下，然后去掉，转为十进制。最后把十进制转化为目标进制，然后如果记录过负号再连接一个负号上去即可。
```cpp
string notR(int a,int b,string str){
    bool negative=false;
    if (!str.empty()) str.erase(0,str.find_first_not_of(" "));
    if (str[0]=='+') str=str.substr(1,str.length()-1);
    else if (str[0]=='-'){
        negative=true;
        str=str.substr(1,str.length()-1);
    }
    long long y=0,aa=1;
    for (int i=str.length()-1;i>=0;i--){
        y=y+toInt(str[i])*aa;
        aa=aa*a;
    }
    string res;
    string tmp;
    do{
        tmp=toChar(y%b);
        y=y/b;
        res=tmp+res;
    }while (y!=0);
    if (negative) res='-'+res;
    return res;
}
```
Q3: 进制转换中出现的 toInt 和 toChar 是什么意思？  
A3: toInt 是把一个字符转化成十进制值，例如A会被转化为10等；toChar 是把一个十进制值转化为字符。代码实现如下：  
```cpp
char toChar(int num){
	if (num<10) return char(int('0')+num);
	else{
		return char(int('A')+num-10);
	}
}
```
```cpp
int toInt(char c){
    if (c>='0' && c<='9') return c-'0';
    else if (c>='a' && c<='z') return c-'a'+10;
    else return c-'A'+10;
}
```

Q4: 如何转化为罗马数字？  
A4: 首先我们列出一张阿拉伯数字和罗马数字的对应表，如下面代码的 values 和 strs 两个 vector 里的内容。接着，如果当前剩余的 num 大于等于 values 里的当前值，则把代表自此值的字符串和之前的结果拼接在一次，然后把 num 减掉该值。  

代码实现如下：
```cpp
string R(int num){
	vector<int>values={1000,900,500,400,100,90,50,40,10,9,5,4,1}; 
	vector<string>strs={"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
	string res;
	for (int i=0;i<values.size();i++){
		while (num>=values[i]){
			res+=strs[i];
			num-=values[i];
		}
	}
	return res;
}
```

Q5: ~~我代码水平太差了，主函数不会写怎么办？~~  
A5: ~~上代码，如果是R就先用 notR 转化成10进制再转罗马数字，如果不是R就直接用 notR 转换成目标进制。~~
```cpp
int main(){
	long long a;
	string b,c;
	cin>>a>>b>>c;
	if (b=="R"){
		cout<<R(str2int(notR(a,10,c)));
	}
	else{
		cout<<notR(a,str2int(b),c);
	}
	return 0;
}
//此代码已在CF原站评测通过。
```

---

