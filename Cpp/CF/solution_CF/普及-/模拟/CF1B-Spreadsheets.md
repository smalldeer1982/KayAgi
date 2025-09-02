# Spreadsheets

## 题目描述

In the popular spreadsheets systems (for example, in Excel) the following numeration of columns is used. The first column has number A, the second — number B, etc. till column 26 that is marked by Z. Then there are two-letter numbers: column 27 has number AA, 28 — AB, column 52 is marked by AZ. After ZZ there follow three-letter numbers, etc.

The rows are marked by integer numbers starting with 1. The cell name is the concatenation of the column and the row numbers. For example, BC23 is the name for the cell that is in column 55, row 23.

Sometimes another numeration system is used: RXCY, where X and Y are integer numbers, showing the column and the row numbers respectfully. For instance, R23C55 is the cell from the previous example.

Your task is to write a program that reads the given sequence of cell coordinates and produce each item written according to the rules of another numeration system.


## 样例 #1

### 输入

```
2
R23C55
BC23
```

### 输出

```
BC23
R23C55
```

# 题解

## 作者：Loner_Knowledge (赞：27)

这是一道字符串模拟题

---

题目给出了两种行列位置的表示方法，一个是`Excel`表示法，一个是`(R,C)`坐标表示法，我们要做的就是将输入的一种表示转换成另一种表示再输出。


`Excel`表示法：用`A`~`Z`的大写字母表示列，用数字表示行，比如`A2`表示第2行第1列，`AA12`表示第12行第27列。


`(R,C)`坐标表示法：用数字表示行列，比如`R2C1`表示第2行第1列，`R12C27`表示第12行第27列。


看完题目就应该想到用`26进制(字母)`与`10进制(数字)`互相转换解决问题，然而这里的`26进制`不同的是`A`表示`1`,`B`表示`2`...`Z`表示`26`，没有用来表示`0`的字母，需要注意当`num%26==0`时应该是`Z`，注意特判。


```cpp
#include<cstdio>
#include<cctype>
const char *Const=" ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char s[101];
void Solve1() {
    int i=0,j=0,num1=0,num2=0;
    int t[101];
    for(++i;isdigit(s[i]);++i)
        (num2*=10)+=s[i]-'0';
    for(++i;s[i];++i)
        (num1*=10)+=s[i]-'0';
    for(;num1;num1=num1/26-!(num1%26)) {    //特判
        if(num1%26)
            t[++j]=num1%26;
        else
            t[++j]=26;    //特判
    }
    for(;j;--j)
        putchar(Const[t[j]]);
    printf("%d\n",num2);
}
void Solve2() {
    int i=0,num1=0,num2=0;
    for(;isupper(s[i]);++i)
        (num2*=26)+=s[i]-'A'+1;    //注意这个加一，A表示1而不是0
    for(;s[i];++i)
        (num1*=10)+=s[i]-'0';
    printf("R%dC%d\n",num1,num2);
}
int main() {
    int n;
    bool flag;
    for(scanf("%d",&n);n;--n) {
        scanf("%s",s);
        flag=0;
        for(int i=0;s[i]&&!flag;++i)
            if(i&&isdigit(s[i-1])&&isupper(s[i]))
            //这里利用了两种表示法的特殊性来判断是哪种表示法，(R,C)表示法在数字后有可能有字母，然而Excel表示法一定不可能
                flag=1;
        if(flag)
            Solve1();
        else
            Solve2();
    }
    return 0;
}
```

---

---

## 作者：Sayori (赞：9)

## [传送门](https://www.luogu.org/problem/CF1B)  
这道codeforces的题的出题人简直是~~太不友好~~了  
作为一道字符串模拟的题目，细节还是比较多的  
### 比如  
26（Z）是能被输出的，而0（@）是不能输出的。来自一个蒟蒻的教训。  
先贴一下我一开始写的代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string str;
bool check(string str){
    int len = str.size(), k = 1, f = 0;
    while(k < len){if(isdigit(str[k]) && !isdigit(str[k - 1])) ++f; ++k;}
    if(f == 2) return 1; return 0;
}
void print_char(int x){ //就是这个地方没有考虑到0不能被输出，导致出现了@
	if(x > 26){
		print_char(x / 26);
		putchar(x % 26 + 'A' - 1);
	}
	else putchar(x + 'A' - 1);
}
void print_1(string str){
    string a = "0";
    int len = str.size(), k = 0, ans = 0, sum = 0;
    while(!isdigit(str[k])) a += str[k], ++k;
    for(int i = 1; i < a.size(); ++i)
        sum = sum * 26 + a[i] - 'A' + 1;
    for(int i = k; i < len; ++i)
        ans = ans * 10 + str[i] - '0';
    cout << 'R' << ans << 'C' << sum << endl;
}
void print_2(string str){
     string a = "0";
     char x;
     int len = str.size(), k = 0, ans = 0, sum = 0;
     while(str[k] != 'C') ++k; ++k;
     for(int i = k; i < len; ++i)
        ans = ans * 10 + str[i] - '0';
    print_char(ans);
    for(int i = 1;; ++i){
        if(str[i] == 'C'){puts("");break;}
        cout << str[i];
    }
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; ++i){   
        cin >> str;
        bool f = check(str);
        if(f)
            print_2(str);
        else
            print_1(str);
    }
}
```  
在第6个点就蛙声一片了  
在思索了一番后，终于是A了这道题  
下面是完整的注释code：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string str;
bool check(string str){
    int len = str.size(), k = 1, f = 0;
    while(k < len){if(isdigit(str[k]) && !isdigit(str[k - 1])) ++f; ++k;}//isdigit是判断字符是否是数字的函数，可以以此判断是哪种形式的坐标 
    if(f == 2) return 1; return 0;//如果前面那个不是数字而后面那个是的话，则f++，出现两个就是RC坐标系 
}
void print_char(int x){
	if(x > 26){//当x>26时，则还有不止一层 
		if(x % 26 == 0)
			print_char(x / 26 - 1), putchar('Z');//特判 
		else
			print_char(x / 26), putchar(x % 26 + 'A' - 1);//递归输出 
	}
	else putchar(x + 'A' - 1);//把最后一个输出 
}
void print_1(string str){
    string a = "0";
    int len = str.size(), k = 0, ans = 0, sum = 0;
    while(!isdigit(str[k])) a += str[k], ++k;//把字符都提到a里面 
    for(int i = 1; i < a.size(); ++i)
        sum = sum * 26 + a[i] - 'A' + 1;
    for(int i = k; i < len; ++i)
        ans = ans * 10 + str[i] - '0';
    cout << 'R' << ans << 'C' << sum << endl;
}
void print_2(string str){
     string a = "0";//这个0仅起占位作用 
     char x;
     int len = str.size(), k = 0, ans = 0, sum = 0;
     while(str[k] != 'C') ++k; ++k;
     for(int i = k; i < len; ++i)
        ans = ans * 10 + str[i] - '0';
    print_char(ans);
    for(int i = 1;; ++i){
        if(str[i] == 'C'){puts("");break;}
        cout << str[i]; 
    }
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; ++i){   
        cin >> str;
        bool f = check(str);//判断是哪种形式 
        if(f) print_2(str);
        else print_1(str);//输出 
    }
}
```
速度有点小慢，擦着线过了   
### [我的AC记录](https://www.luogu.org/record/24721075)


---

## 作者：Drifting (赞：9)

##  一道不错的字符串/模拟题
（第一次发CF题的题解，很激动）

这道题的实质是一种字母与数字之间的转化，其关键在于26进制的字母与十进制的数字之间的进制转换。
相信对进制转换比较熟悉的同学不会有什么问题。但本题有一些比较特殊的细节处理。

**思路**

类比二进制到十进制/十进制到二进制的转换，（详细可以去翻翻书）

对于一个26进制数，A即为1，B即为2，Z即为26，以此类推。

但是需要注意的是这26个字母中没有一个会用来表示0；
（所以它实际上是一个27进制数，只是少了0的表示而已）。

个人比较喜欢用STL，代码会简单，但是速度会变慢。


------------


**下面贴出代码：**

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
string str;
int n,len;
void trans(bool mode)
{
	char apt[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //alphabet 字母表 
	int col = 0,row = 0; //col为列号，row为行号; 
	if(mode)	//mode 1: RXCY转Excel式 
	{
		int R = str.find("R"),C = str.find("C");  //使用find()函数，找到R与C所在的位置; 
		for(int i = R + 1;i < C;i++)	//从R的下一位开始遍历，下同; 
			row = row * 10 + str[i] - '0';	//字符串转十进制数字 
		for(int i = C + 1;i < len;i++)
			col = col * 10 + str[i] - '0';	
		string ans;
		while(col > 0)
		{
			int temp = col % 26; //除26取余，下同; 
			if(temp == 0)	temp = 26,col -= 26; //当col对应字母为'Z' 时，需要进行特判; 
			ans += apt[temp]; //利用apt[]将数字重新转为对应字母,使用ans字符串储存答案; 
			col /= 26;
		}
		reverse(ans.begin(),ans.end());	
		//此时得到的ans是按从低位到高位存储的，
		//我们需要将ans反转，使其按高位到低位存储，从而符合题目要求; 
		cout<<ans<<row<<endl;//直接输出即可;
		/*（如果不对ans进行反转，则输出应改为：）
			for(int i = ans.length() - 1;i >= 0;i--)	cout<<ans[i];
			cout<<row<<endl; 
		*/ 
	}
	else //mode 2: Excel式转为RXCY式; 
	{
		for(int i = 0;i < len;i++)	//遍历字符串 
		{
			if(!isdigit(str[i])) 
				col = col * 26 + str[i] - 'A' + 1;	//26进制字符串转十进制数字; 
			else row = row * 10 + str[i] - '0'; //同上; 
		}
		printf("R%dC%d\n",row,col);
	}
} 
int main()
{
	scanf("%d",&n);	
	for(int i = 1;i <= n;i++)
	{
		cin>>str;	//使用string类型,以便下面利用一些STL的特性;
		bool flag = 0,mode = 0;		//本题是多组数据，需要初始化; 
		len = str.length();
		for(int i = 0;i < len;i++)	//遍历整个字符串，利用两种表示方式的不同来判断; 
		{
			if(isdigit(str[i]))	flag = 1;	//flag用来标记数字是否已经出现; 
			if(flag&&str[i] == 'C')		//在RXCY表示法中一定会出现字母C，且C之前一定会有数字出现， 
			{							//而在另一种表示法中，数字的后面不可能存在字母; 
				mode = 1; 
				break;					//一旦判断出相应的表示方式，直接跳出即可; 
			}
		}
		trans(mode);// mode = 1 或 0，区分两种不同的转换; 
	}
	return 0;
}

```

---

## 作者：sandwich (赞：8)

### 这一题就是~~简单~~的二十六进制与十进制之间的转换（也就做了WA十几遍）
二十六进制与十进制之间的转换可以采用余数倒输的方法，这里就不再多讲了

具体参考网上

[链接](https://blog.csdn.net/A123333333333/article/details/83414339)

最主要的注意点是Z
### 因为是二十六进制，所以满26就一定会进一位
就比如：R23C26

如果不加判断

就会输出：A@23

就是这样

```c
#include <bits/stdc++.h>
using namespace std;
char x[1000010];
int main()
{
	int n,i,j,k;
	
	cin>>n;
	for(i=1;i<=n;i++)
	{
		bool tt=true;
		cin>>x;
		int l=strlen(x);
		if(x[0]=='R'&&'1'<=x[1]&&x[1]<='9')
		for(int j=2;j<l;j++)
		if(x[j]=='C') {k=j;tt=false;break;}//判断格式 
		if(tt)
		{
			int a[10];
			int sum=0,j=0;
			while(x[j]>='A'&&x[j]<='Z')
			j++,a[j]=x[j-1]-'A'+1;
			int k=j;
			//cout<<a[1]<<endl;;
			for(int i=1;i<=j;i++)
			{
				int ans=1;
				for(int k=1;k<=j-i;k++)
				ans*=26;
				sum+=a[i]*ans;
				//cout<<sum<<endl;
				
			}
			cout<<"R";
			j--;
			for(int i=j+1;i<l;i++)
			cout<<x[i];
			cout<<"C"<<sum;
			cout<<endl;
		}
		if(!tt)
		{
			int a,b,x1[10];
			a=x[k+1]-'0';b=x[1]-'0';
			for(int i=k+2;i<l;i++)
			a=a*10+x[i]-'0';
			for(int i=2;i<k;i++)
			b=b*10+x[i]-'0';
			int sum=0,sum1=0;
			//cout<<a<<" "<<b<<endl;
			int k=0;
			while(a!=0)
			{
			    k++;
			    if(a%26!=0)x1[k]=a%26,a/=26;
			    //z的特殊判断 
				else x1[k]=26,a=a/26-1;
				
			}
			for(int i=k;i>=1;i--)
			{
				cout<<char(x1[i]+'A'-1);
			}
			cout<<b;
			cout<<endl;
		} 
	}
	return 0;
}

/*
1
ABD815
1
R23C494
*/
```


---

## 作者：LeonhardtWang (赞：6)

col_to_num：将excel表示法转换成数字形式（类似于二进制转换成十进制）   
num_to_col：将数字转换成excel表示法（类似十进制转换成二进制，短除法，但要注意余数不能为0，只能为为1-26）  
xy_to_excel：将X-Y表示法的字符串转换成excel表示法的字符串  
excel_to_xy：将excel表示法的字符串转换成X-Y表示法  
is_xy：识别输入是否为X-Y表示法  



```
n = int(input().strip())

def col_to_num(col):
    carry = 0
    res = 0
    while col:
        cur = col[-1]
        res += (ord(cur) - 64) * 26 ** carry
        col = col[:-1]
        carry += 1
    return str(res)
    
def num_to_col(num):
    num = int(num)
    res = ''
    while num:
        mod = num % 26
        if mod == 0:
            res = 'Z' + res
            num = num // 26 - 1
        else:
            num //= 26
            res = chr(mod+64) + res
    return res
    
def xy_to_excel(string):
    y = string.split('C')[-1]
    x = string.split('C')[0].split('R')[-1]
    return num_to_col(y)+x

def excel_to_xy(string):
    for i in range(len(string)):
        if '1' <= string[i] <= '9':
            break
    col = string[:i]
    row = string[i:]
    return 'R'+row+'C'+col_to_num(col)
    
def is_xy(string):
    if string[0] == 'R' and '1' <= string[1] <= '9':
        for s in string[2:]:
            if s == 'C':
                return True
    return False
    
for _ in range(n):
    string = input().strip()
    if is_xy(string):
        print(xy_to_excel(string))
    else:
        print(excel_to_xy(string))
    
```


---

## 作者：BBD186587 (赞：5)

## 模拟题 ##
首先，我们要分情况讨论。

情况一 由RXCY转化

情况二 转化为RXCY型

然后再调一调，就可以AC啦!

（因为我挂了六发，所以来讲解一下典型错误代码）

第一发 WA on test6
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<stack>
using namespace std;
int T,tot,xx,yy,kkk;
char a[100];
bool number(char x)
{
	return x>='0'&&x<='9';
}
bool check()
{
	return a[0]=='R'&&number(a[1]);
}
int pow_(int x,int y)
{
	int sum=1;
	for(int i=1;i<=y;i++) sum*=x;
	return sum;
}
stack <char> ans;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		cin>>a;
		if(check())
		{
			xx=0,yy=0,tot=0;
			int k=strlen(a)-1;
			for(;;k--)
			{
				if(a[k]=='C') break;
				yy+=pow_(10,tot++)*(a[k]-'0');
			}
			tot=0,k--;
			for(;;k--)
			{
				if(a[k]=='R') break;
				xx+=pow_(10,tot++)*(a[k]-'0');
			}
			//cout<<xx<<' '<<yy<<endl;
			while(yy) ans.push(yy%26+'A'-1),yy/=26;
			while(!ans.empty()) cout<<ans.top(),ans.pop();
			printf("%d\n",xx);
		}
		else
		{
			tot=0,xx=0,yy=0;
			while(!number(a[tot])) tot++;
			//cout<<tot<<endl;
			tot--;
			for(int i=0;i<=tot;i++)
				xx+=pow_(26,tot-i)*(a[i]-'A'+1);
			//cout<<xx<<endl;
			kkk=strlen(a)-tot-1;
			for(int i=tot+1;i<strlen(a);i++)
				yy+=pow_(10,kkk-i+tot)*(a[i]-'0');
			printf("R%dC%d\n",yy,xx);
		}
	}
	return 0;
}
```
这发是因为没判Z，输出了@

第二发~第五发 WA on test6/test7
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<stack>
using namespace std;
int T,tot,xx,yy,kkk;
bool flag;
char a[100];
bool number(char x)
{
	return x>='0'&&x<='9';
}
bool check()
{
	return a[0]=='R'&&number(a[1]);
}
int pow_(int x,int y)
{
	int sum=1;
	for(int i=1;i<=y;i++) sum*=x;
	return sum;
}
stack <char> ans;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		cin>>a;
		if(check())
		{
			xx=0,yy=0,tot=0,flag=false;
			int k=strlen(a)-1;
			for(;;k--)
			{
				if(a[k]=='C') break;
				yy+=pow_(10,tot++)*(a[k]-'0');
			}
			tot=0,k--;
			for(;;k--)
			{
				if(a[k]=='R') break;
				xx+=pow_(10,tot++)*(a[k]-'0');
			}
			//cout<<xx<<' '<<yy<<endl;
			while(yy)
			{
				if(yy%26==0) ans.push('Z'),flag=true;
				else ans.push(yy%26+'A'-1);
				yy/=26;yy-=flag;flag=false;
			}
			while(!ans.empty()) cout<<ans.top(),ans.pop();
			printf("%d\n",xx);
		}
		else
		{
			tot=0,xx=0,yy=0;
			while(!number(a[tot])) tot++;
			//cout<<tot<<endl;
			tot--;
			for(int i=0;i<=tot;i++)
				xx+=pow_(26,tot-i)*(a[i]-'A'+1);
			//cout<<xx<<endl;
			kkk=strlen(a)-tot-1;
			for(int i=tot+1;i<strlen(a);i++)
				yy+=pow_(10,kkk-i+tot)*(a[i]-'0');
			printf("R%dC%d\n",yy,xx);
		}
	}
	return 0;
}
```
这些是因为判属于哪种情况时判错了

接下来，AC代码闪亮登场~
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<stack>
using namespace std;
int T,tot,xx,yy,kkk;
bool flag;
char a[100];
bool number(char x)
{
	return x>='0'&&x<='9';
}
bool check()
{
	if(a[0]!='R') return false;
	if(!number(a[1])) return false;
	for(int i=2;i<strlen(a)-1;i++)
	{
		if(a[i]=='C') return true;
		else if(!number(a[i])) return false;
	}
	return false;
}//判属于哪种情况
int pow_(int x,int y)
{
	int sum=1;
	for(int i=1;i<=y;i++) sum*=x;
	return sum;
}
stack <char> ans;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		cin>>a;
		if(check())
		{
			xx=0,yy=0,tot=0,flag=false;
			int k=strlen(a)-1;
			for(;;k--)
			{
				if(a[k]=='C') break;
				yy+=pow_(10,tot++)*(a[k]-'0');
			}
			tot=0,k--;
			for(;;k--)
			{
				if(a[k]=='R') break;
				xx+=pow_(10,tot++)*(a[k]-'0');
			}
			//cout<<xx<<' '<<yy<<endl;
			while(yy)
			{
				if(yy%26==0) ans.push('Z'),flag=true;
				else ans.push(yy%26+'A'-1);
				yy/=26;yy-=flag;flag=false;
			}//栈模拟，比较短。也可换为数组模拟
			while(!ans.empty()) cout<<ans.top(),ans.pop();
			printf("%d\n",xx);
		}//情况一
		else
		{
			tot=0,xx=0,yy=0;
			while(!number(a[tot])) tot++;
			//cout<<tot<<endl;
			tot--;
			for(int i=0;i<=tot;i++)
				xx+=pow_(26,tot-i)*(a[i]-'A'+1);
			//cout<<xx<<endl;
			kkk=strlen(a)-tot-1;
			for(int i=tot+1;i<strlen(a);i++)
				yy+=pow_(10,kkk-i+tot)*(a[i]-'0');
			printf("R%dC%d\n",yy,xx);
		}//情况二
	}
	return 0;
}
```
完结撒花~

---

## 作者：叶枫 (赞：3)

这个题。。。 ~~是一道模拟题吧~~

### $Be~careful$
不要用`#deinfe int long long+signed main()`

$\color{white}\sout\text{sb的我因为这玩意儿交了好多次}$
### $Idea$
题意有两种标记行列的方式

行号都是一致的其实就是列号的转化

但是要注意这个跟26进制是有一点区别的

### $Code$

```cpp
也没多难哈~~
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<string>
#define ll long long
#define maxn 110
#define inf 2147483647
#define mod 998244353
#define eps 1e-8
using namespace std; 
inline int read(){
    int x=0,f=1; char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)) {x=x*10+ch-48;ch=getchar();}
    return x*f;
}
char s[maxn],ss[maxn];
signed main(){
	int t=read();
    while(t--){
        cin>>s;
        int num1=0,num2=0;
        if(s[0]=='R'){
            int i=1;
            while(isdigit(s[i])) num1=num1*10+s[i++]-'0';
            if(i>1&&s[i]=='C'){
                i++;
                while(isdigit(s[i])) num2=num2*10+s[i++]-'0';
                int j=0;
                while(num2>0){
                    ss[++j]=(num2-1)%26+'A';
                    if(num2%26==0) num2=num2/26-1;
                    else num2/=26;
            	}
                for(;j>=1;j--)
                    if('A'<=ss[j]&&ss[j]<='Z')
                    cout<<ss[j];
                printf("%d\n",num1);
                continue;
            }
        }
        int i=0;
        num1=0,num2=0;
        while('A'<=s[i]&&s[i]<='Z') num2=num2*26+s[i++]-'A'+1;
        while(isdigit(s[i])) num1=num1*10+s[i++]-'0';
        printf("R%dC%d\n",num1,num2);
    }
    return 0;
}
```

---

## 作者：Houraisan_Kaguya (赞：2)

推荐[博客查看](https://www.luogu.com.cn/blog/9u46-MX/Solution-CF1B)，不保证题解界面文章显示质量。

- 给出 $n$ 个字符串，题目中给定两种格式，相互转换。

- 考虑 `RxxCxx` 转换成 `LLLddd`。

	- 考虑将 `Cxx` 转换成 `LLL`。

	- 考虑把 `LLL` 看成二十六进制，`A` 为 $0$。我们发现 `A` 和 `AA` 相等。所以这种方法不行。
    
    - 但我们发现，在长度相等的情况下，可以这么做。
    
    - 考虑确定长度。
    
    - 用 $f_i$ 表示在长度为 $i$ 的字母串能表示的最小数（即 $\begin{matrix}\underbrace{AAA \cdots A}\\i\_A\end{matrix}$ 表示的数），故 $f_i = f_{i - 1} + 26^{i - 1}$（少一位能表示的最小数加上少一位的数量）。
    
    - 因为 $f_i$ 以指数级别增长，故可以以 $O(log)$ 的复杂度求出答案位数。
    
    - 因为一个字母串的首位（不为 `Z`）增加一，表示的数就增加 $26^{length - 1}$，所以可以用除 $26^{length - 1}$ 判断首位。
    
    - 之后再用进制转换即可。
    
- 其他细节比较简单，别的题解写的也很详细。可以看代码。

```cpp
enum X { X = 26 }; // 字母数量（enum 定义常量）
using namespace std;
# include <cctype> // 包含判断数字字符的 isdigit 函数
# include <iostream>
# include <string>

void const inline LD_to_RC(string const s) {
    short unsigned int digit(0);
    while (not isdigit(s[digit])) ++digit; // 找到第一个数字位置
    string const letter(s.substr(0, digit)), R(s.substr(digit)); // 分离字母与数字
    unsigned int C(0), base(1);
    for (short signed int register i(letter.length() - 1); i >= 0; --i)
        C += (letter[i] - 'A' + 1) * base, base *= X; // 直接套进制转换
    cout << 'R' << R << 'C' << C << endl;
}
void const inline RC_to_LD(string const s) {
    unsigned int l(stoul(s.substr(s.find('C') + 1))); string const D(s.substr(1, s.find('C') - 1)); // stoul 函数将 string 转成 unsigned long
    unsigned int sum(0), base(1); short signed int cnt(0);
    while ((sum += base) <= l) base *= 26, ++cnt;
    l -= (sum -= base), --cnt; // 求出在 [1, l] 中与答案位数相同的字母串的数量
    string L; L.clear();
    char t((l / (base /= 26)) + 'A'); // 答案的第一位，加一减一可以试一下
    l %= base, --cnt; // cnt 表示位数，要减2
    for (short signed int register i(0); i <= cnt; ++i) L = (char)(l % 26 + 'A') + L, l /= 26; // 因为可能还没除完就变成0了，所以要用 for 循环强制算 cnt 次
    cout << t + L << D << endl;
}

unsigned int n;
signed int main() {
    cin >> n;
    for (unsigned int register i(0); i < n; ++i) {
        string s; cin >> s;
        s[0] == 'R' && isdigit(s[1]) && s.find('C') != string::npos ? RC_to_LD(s) : LD_to_RC(s);
    }
    return 0;
}
```

---

## 作者：恶灬心 (赞：2)

本题，两种转换形式

RxxCxx转为字母+数字

字母+数字转为RxxCxx

我们可以明显感觉到 当输入R时要小心Rxx的情况，这是需要判别的。

还有，由于pow的不稳定性，我们也应该手写一个powl函数代替pow。

最后，将数字转换成字母时，当%26=0时，应自动退位，也就是取前面的一个1变为Z。
于是转化时应判断一下，并检验是否退位。

```cpp
#include <bits/stdc++.h>
using namespace std;
string c;
int hang[50],l[5];
int powl(int a,int b)
{
	int ans=1;
	while(b--)
	 ans*=a;
	return ans;
}

bool Check() 
{
	if(c[0] != 'R')
		return false;
	if(!isdigit(c[1]))
		return false;
	for(int i=2;i<c.size();i++)
	{
		if(c[i]=='C')
			return true;
	}
	return false;
}

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>c;
		int ms=0;
		memset(l,0,sizeof(l));
		if(Check()) ms=1;
		if(ms)
		{
			int zz=0,tot=0;
			for(int i=1;i<=2;i++)
			{
				while(c[zz]<'0'||c[zz]>'9') zz++;
				while(c[zz]>='0'&&c[zz]<='9') l[i]=l[i]*10+c[zz]-'0',zz++; 
			}
			while(l[2])
			{
				tot++;
				hang[tot]=(l[2]%26?l[2]%26 : 26);
				l[2]=l[2]/26-!(l[2]%26);
			}
			for(int i=tot;i>=1;i--) cout<<(char)(hang[i]+'A'-1);
			cout<<l[1];
		}
		else
		{
			int zz=0,tot=0;
			while(c[zz]<'0'||c[zz]>'9') 
			hang[++tot]=(int)c[zz],zz++;
			while(c[zz]>='0'&&c[zz]<='9') l[1]=l[1]*10+c[zz]-'0',zz++; 
			cout<<"R"<<l[1];
			for(int i=tot,j=1;i>=1,j<=tot;i--,j++)
			l[2]+=powl(26,i-1)*(hang[j]-'A'+1);
			cout<<"C"<<l[2];
		}	
		cout<<endl;
	}
	
}
```


---

## 作者：blackzoo (赞：1)

开始刷Codeforces了，内心有一些小激动。就这一题而言，Wrong了不少次，很多

细节没有注意到，下次还需要努力呀。好了，废话不多说了，开始进入题解。

这道题主要考察的是进制的转换，当然还有一些细节：例如两种不同坐标系统的区

分。0不能输出，而26可以被输出，字符串的截取。下面给出题解。

```cpp
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;

bool isRC(const string& s)        //判断是否为RC形式的坐标系统
{
	if (s[0] != 'R') return false;
	unsigned i = 1;
	for ( ; i < s.size() && 'A' <= s[i] && s[i] <= 'Z'; i++);    //判断首字母为‘R'的字符串是否为RC坐标系统
	for ( ; i < s.size() && '0' <= s[i] && s[i] <= '9'; i++);
	if (i >= s.size() || s[i] != 'C') return false;   //筛选出类似“RC11"和”R1“两种类型都不是RC坐标系统
	return true;
}


int main()
{
    int i,t,n,l,row;
    string s,ans;
    cin>>n;
    while(n--)
    {
        row=0;
        cin>>s;
        l=s.size();
        if(isRC(s))      //RC型坐标系统
        {
            for(i=1;i<l;i++)
            {
                if(s[i]>'9')
                {
                    t=i;          //找到’C‘的位置
                    break;
                }
            }
            string sub=s.substr(1,t-1);   //截取’R'与‘C’之间的数字
            for(i=t+1;i<l;i++)
                row=row*10+s[i]-'0';       
            while(row)               //10进制转化为26进制（重要）
            {
                int r=row%26;
                row=row/26;
                if(!r)             //r=0无法表示，转化为26表示成‘Z’
                {
                    r=26;
                    row=row-1;
                }
                ans+=(char)(r+'A'-1);
            }
            int en=ans.size();
            for(i=en-1;i>=0;i--)
                cout<<ans[i];            //逆序输出进制转换后的数
            cout<<sub<<endl;             
            ans.clear();              //循环输入时注意清空
        }
        else
        {
            for(i=0;i<l;i++)
            {
                if(s[i]<='9')    //找到数字开始位置
                {
                    t=i;
                    break;
                }
            }
            string sub=s.substr(t,l);      //截取数字
            for(i=0;i<t;i++)
                row=row*26+s[i]-'A'+1;         //26进制转换为10进制
            cout<<"R"<<sub<<"C"<<row<<endl;
        }
        s.clear();         //清空
    }
    return 0;
}

```

---

## 作者：icebird (赞：0)

## [题目链接](https://www.luogu.org/problemnew/show/CF1B)


------------
### 题解：
#### 算是一道很麻烦的字符模拟题~~（感受到codeforces的深深恶意）~~，
#### 其中还包含了26进制和10进制的转化，但同时也是对基础能力的一次极佳的试炼！

现在让我们来战胜它！

```cpp
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int main()
{
    long long n;

    cin>>n;
    char c[1000010];	
    
    for(int i=1;i<=n;i++)
      {	
      int flag1=0,flag2=0;
      	scanf("%s",&c);//输入字符串
      long long  length;
      	length=strlen(c);//获得字符串长度，以便于后面的判断。
    
      	for(int j=1;j<length;j++)
      	{
      		if(c[j]<'A') flag1=1;
      		
      		if(c[j]=='C'&&flag1==1) flag2=1;
      	}//两个flag变量用于判断类型 
      	
      	if(flag2==0)//转化为RXCY类型，较简单~
    {
        long long t=0,row=0,column=0;
        while(c[t]>='A')//将其转化为数字
        {
            column=column*26+c[t]-'A'+1;
            t++;
        }
        
       while(t<length)
       {
       	row=row*10+c[t]-'0';
       	t++;
       }
       cout<<"R"<<row<<"C"<<column<<endl;
    }  
     
       if(flag2==1)//主要难点
       {
       	
       	long long  t=1,row=0,column=0;
       	while(c[t]!='C')//得到第一个数
       	{
           row=row*10+c[t]-'0';
           t++;
        }
          t++;
          while(t<length)//得到第二个数
          {
          	column=column*10+c[t]-'0';
            t++;
          }
         	int zz=0;
           int num[100010];   
           memset(num,0,sizeof(num));//清零操作
           while(column>0)//获得26进制下的数
          {
   	         num[zz]=column%26;
         	column=column/26;
         	zz++;
         }
         zz--;
         int pp=0;char kky[100100];    
        for(int q=0;q<=zz;q++)//转化为字母，小心退位操作
        {
   	

   	     if(q==zz&&num[q]==0&&num[q+1]==0) break;
         	if(num[q]==0) {num[q+1]--;kky[pp]='Z';pp++;}
   	        else {
   	        	if(num[q]<0) {num[q+1]--;num[q]=25;}
               kky[pp]=num[q]+'A'-1;pp++;
               }
   	    
         }
       for(int gg=pp-1;gg>=0;gg--)//最终输出
           cout<<kky[gg];
          cout<<row<<endl;
     	}
         
         
     }
} 
```

---

