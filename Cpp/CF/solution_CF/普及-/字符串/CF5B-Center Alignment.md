# Center Alignment

## 题目描述

几乎每一个文本编辑器都有文字居中对齐的功能，因此Berland的著名文本编辑器Textpad的开发者们希望在产品的第四次更新中加入此功能。

您的任务是尽快编写一个文本居中对齐的原型程序，祝您好运!

## 样例 #1

### 输入

```
This  is

Codeforces
Beta
Round
5
```

### 输出

```
************
* This  is *
*          *
*Codeforces*
*   Beta   *
*  Round   *
*     5    *
************
```

## 样例 #2

### 输入

```
welcome to the
Codeforces
Beta
Round 5

and
good luck
```

### 输出

```
****************
*welcome to the*
*  Codeforces  *
*     Beta     *
*   Round 5    *
*              *
*      and     *
*  good luck   *
****************
```

# 题解

## 作者：恨穹不是妹 (赞：8)

哇，那位dalao用的方法太难懂了，蒟蒻看不懂啊！

下面给大家介绍一种比较清奇的码风

思路就是强行模拟，（它甚至不配做橙题）

废话不多说，上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int q[10001],max=0,o=1;
    /*q是计算每行字符的长度，
    max是找出最长的一行字符个数，
    o就是来计算当不能完美对齐时的左偏还是右偏*/
	char a[1001][1001];//存放读入的字符
	int j=1;
	while(gets(a[j]))
	{
		q[j]=strlen(a[j]);
		if(q[j]>max)
		max=q[j];
		j++;
	}
	j--;
	for(int i=1;i<=max+2;i++)
	cout<<"*";
	cout<<endl;//第一行全是*
	for(int i=1;i<=j;i++)
	{
		cout<<"*";
		if(max%2!=q[i]%2)
		{
		o=-o;//判断正负
		for(int k=1;k<=(max-q[i]+o)/2;k++)
	    cout<<" ";
	    cout<<a[i];
		for(int k=1;k<=(max-q[i]-o)/2;k++)
	    cout<<" ";
	    cout<<"*";
	    cout<<endl;
		}
		else
		{
		for(int k=1;k<=(max-q[i])/2;k++)
	    cout<<" ";
	    cout<<a[i];
		for(int k=1;k<=(max-q[i])/2;k++)
	    cout<<" ";
	    cout<<"*";
	    cout<<endl;
		}
	}
	for(int i=1;i<=max+2;i++)
	cout<<"*";//最后一行行全是*
	return 0;
}
```

---

## 作者：耶耶小朋友 (赞：7)

### 做法:
此题就是模拟的典型题目，直接强制模拟即可。
读入后按题意模拟即可。

### 特判:
①：对于有空行的情况：在读入时获取最长的长度 $mx$，直接输出一个 $*$、$mx$ 个空格和一个 $*$。

②：对于题目条件 “第一次遇到此类情况时将该行文本向左微调，下一次向右，在下一次向左…” 进行模拟。

### 提示:
$cnt$ 表示行数。
	
$mx$ 表示最长的长度。

$bt$ 记录当出现无法实现完美的居中对齐，false表示向左调，true表示向右调。
	
$a$ 表示首行及尾行的包含 $*$ 的字符串。

## Code:
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1010;
char str[N][N];
int len[N];
int main () {
	int cnt = 0,mx = -1;
	while(gets(str[cnt])) {
        len[cnt] = strlen(str[cnt]);
        mx = max(mx,len[cnt]);
        cnt++;
    }
    cnt--;
    string a(mx+2,'*');
    cout << a << endl;
    bool bt = false;
    for (int i = 0;i <= cnt;i++) {
    	cout << '*';
    	if (len[i] == 0) {
    		for (int j = 1;j <= mx;j++) cout << " ";
		} else {
    		int mid;
    		if ((mx - len[i]) % 2 == 1) {
	    		if (bt == false) {
	    			mid = (mx - len[i] - 1) / 2;
	    			for (int j = 1;j <= mid;j++)  cout << " ";
					cout << str[i];
					for (int j = 1;j <= mid+1;j++)  cout << " ";
					bt = true;
				} else {
					mid = (mx - len[i] + 1) / 2;
	    			for (int j = 1;j <= mid;j++) cout << " ";
					cout << str[i];
					for (int j = 1;j <= mid-1;j++) cout << " ";
					bt = false;
				}
			} else {
				mid = (mx - len[i]) / 2;
				for (int j = 1;j <= mid;j++) cout << " ";
				cout << str[i];
				for (int j = 1;j <= mid;j++) cout << " ";
			}
		}
		cout << "*\n";
	}
	cout << a << endl;
	return 0;
}

```

---

## 作者：SIXIANG32 (赞：4)

这题不是很难，大体思路就是```while(getline(cin,str))```这样读入（若干行要用```while```，因为有空格要用```getline```），边读入边更新最大值。  

然后挨个处理每个字符串要加多少空格，这是这道题的重头戏：  

- 如果可以刚好对齐（即$0 \equiv (maxn-len_i) \pmod 2$的情况）就可以左边的和右边的都要填充$\dfrac{max-len_i}{2}$个空格。  

- 如果无法刚好对齐（即$1 \equiv (maxn-len_i) \pmod 2$的情况）就需要根据出现这个的次数来决定左边的空格
和右边的空格数量，这就会出现下面两种情况： 

	- 如果出现这种情况的次数不是2的倍数，左边少了一个，那么左边有$\left\lfloor\dfrac{maxn-len_i}{2}\right\rfloor$个，右边则有 $\left\lfloor\dfrac{maxn-len_i}{2}\right\rfloor+1$个。  

	- 如果出现这种情况的次数是2的倍数，右边少了一个，那么左边有$\left\lfloor\dfrac{maxn-len_i}{2}+1\right\rfloor$个，右边则有$\left\lfloor\dfrac{maxn-len_i}{2}\right\rfloor$个。
    
- 还有一种情况，那就是空行，如果是这样我们直接生成一个和最长长度一样长的空行即可。

题目已经分析完了，上代码！  
```cpp
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
string str[10010];
int main()
{
    int tot=0,cnt=0,maxn=0,k;
    /*tot是多少行要处理的字符串
    cnt是出现无法刚好对齐的次数
    maxn是长度最大字符串的长度
    k临时存储每个字符串的长度。*/
    while(getline(cin,str[++tot]))//循环读入
        k=str[tot].size(),maxn=max(k,maxn);//更新最长
    string ud(maxn+2,'*');tot-=1;//ud是边框
    //这里我们会多读入一个东东，所以tot要-1
    cout<<ud<<endl;//输出边框
    for(int p=1;p<=tot;p++)
        if(str[p].size()==0)//特判为空行的情况
        {
            string s(maxn,' ');
            cout<<"*"<<s<<"*"<<endl;
        }
        else
            if((maxn-str[p].size())%2==0) //可以完美对齐
            {
                string s((maxn-str[p].size())/2,' ');
                cout<<"*"<<s<<str[p]<<s<<"*"<<endl;
            }
            else//不能完美对齐
            {
                string s((maxn-str[p].size())/2,' ');
                cnt++;//出现不能完美对齐的次数+1
                if(cnt%2)//如果不是2的倍数靠左
                	cout<<"*"<<s<<str[p]<<s<<" *"<<endl;
                else//否则靠右
                	cout<<"* "<<s<<str[p]<<s<<"*"<<endl;
            }
    cout<<ud<<endl;
}
```

---

## 作者：outis_crypt (赞：4)

提供一种我认为比较简单的写法 ( **不要看代码比较长，还是很容易看懂的** )：

**C++的 String 中有一种生成字符串的方法 :** 

**string str( length , char ) ;**

**length : 为要生成字符串的长度。**

**char ： 单个字符（字符串str仅包含这个字符）**

例如：

**string s( 6, 'a' ) ;**

**此时 s="aaaaaa"**

这题我用的是纯模拟，按题目要求来写就行了。

代码如下：

```cpp
#include<iostream>
#include<string>
using namespace std;
string s[1005];          //存字符串
int main()
{
	int i = 0, max_length = 0;   // max_length找最长的字符串长度
	while (getline(cin,s[i]))  //注意要用getline(), 因为字符串中可能存在空格
	{
		max_length = max_length > s[i].length() ? max_length : s[i].length();
		i++;
	}
	string e(max_length+2,'*');   //生成首尾的max_length+2个 '*'
	cout <<e<< endl;         //输出首行的一排'*'
	int right=0, left=1;       //无法对称时用来左右调整的,初始向左调整
	for (int j = 0; j < i; j++)
	{
		if (s[j].length() == 0)  //如果字符串为空时,输出max_length个空格，首尾各加一个'*'
		{
			string back(max_length,' '); //back用来生成空格的，下文同
			cout << '*' << back << '*' << endl;
			continue;
		}
		if (s[j].length() < max_length&&s[j].length()) //如果小于最大长度
		{
			int t = max_length - s[j].length(); //t是与最大长度相比的剩余空间
			if (t % 2 == 0)  //能完美对齐
			{
				string back(t / 2,' ');
				cout << '*' <<back<< s[j]<<back << '*' <<endl;
			}
			else    //不能完美对齐，需要左右调整
			{
				if (left) //向左调整，左边少一个空格
				{
					string back((t-1)/ 2,' ');
					left = 0, right = 1;  //下次该向右调整了
					cout <<"*"<< back << s[j] << back<<" " << "*" <<endl;   //手动在右边补一个空格，下文左边同
					continue;
				}
				if (right)  //向右调整，右边少一个空格
				{
					string back((t - 1) / 2,' ');
					right = 0; left = 1;
					cout << "*" <<" "<< back << s[j] << back<< "*" << endl;
				}
			}
		}
		if (s[j].length() == max_length) //等于最大长度的时候输出就行了
		{
			cout << "*" << s[j] << "*" << endl;
		}
	}
	cout << e << endl;  //收尾，补上max_length+2个*
	return 0;     //结束
}
```






---

## 作者：Lucifer_Bartholomew (赞：2)

# ~~模拟~~
直接模拟：读入字符串，矩阵宽度=字符串最长长度+2，输出字符串+边框
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[1005][1005];
int sl[1005];
int main()
{
    int num=0,msl=0;
    while(gets(s[num])!=NULL)//读入要特别注意一下
    {
        sl[num]=strlen(s[num]);
        msl=max(msl,sl[num]);
        num++;
    }
    for(int i=1;i<msl+3;++i)//头行
        putchar('*');
    puts("");
    bool lr=1;//控制左缩进还是右缩进
    for(int i=0;i<num;++i)
    {
        putchar('*');
        if((msl-sl[i])&1)//字符串长度为奇数
        {
            if(lr)
            {
                for(int j=0;j<(msl-sl[i])>>1;++j)//边框
                    putchar(' ');
                printf("%s",s[i]);
                for(int j=0;j<=(msl-sl[i])>>1;++j)//边框
                    putchar(' ');
            }
            else
            {
                for(int j=0;j<=(msl-sl[i])>>1;++j)//边框
                    putchar(' ');
                printf("%s",s[i]);
                for(int j=0;j<(msl-sl[i])>>1;++j)//边框
                    putchar(' ');
            }
            lr=!lr;//交换缩进方向
        }
        else
        {
            for(int j=0;j<(msl-sl[i])>>1;++j)//边框
                putchar(' ');
            printf("%s",s[i]);
            for(int j=0;j<(msl-sl[i])>>1;++j)//边框
                putchar(' ');
        }
        puts("*");
    }
    for(int i=1;i<msl+3;++i)//尾行
        putchar('*');
    puts("");
    return 0;
}
```
~~我是蒟蒻~~

---

## 作者：PC_DOS (赞：2)

题目要求为字符串居中对齐，那么对于每一个字符串的处理，就有两种情况:


1. 恰好可以居中对齐，也就是最大长度(记为iMaxLen，下同)iMaxLen-该字符串长度(记为iLen，下同)iLen为偶数，只需要再这个字符串两边分别补上(iMaxLen-iLen)/2和空格并各加上一个星号即可。


2. 无法居中对齐，也就是iMaxLen-iLen为奇数，这时题目要求"先向左缩进一格，再向右缩进一格，再向左缩进一格..."，也就是先在原字符串两边加上(iMaxLen-iLen)/2和空格，之后再在左侧或右侧补一个空格即可，可以使用一个布尔型变量isLeftPlus记录。


此外还有一个需要注意的地方: 输出的时候可能会多一行由于EOF导致的空(W)白(A)。


由此得到代码:

```cpp
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std; //头文件和命名空间
string CreateRequiedString(long long nCount, char chrChrarater){
    int i;
    string sAns;
    for (i = 1; i <= nCount; ++i)
        sAns += chrChrarater;
    return sAns;
} //用于创建特定长度的由特定字符组成的字符串的函数
bool isEven(long long iNum){
    return (iNum % 2 == 0);
} //判断奇偶
int main(){
    ios::sync_with_stdio(false); //关闭与STDIO的同步，加快输入输出速度
    vector<string> arrStrings; //动态数组，存放输入的字符
    string sInput; //暂存目前输入的字符串
    bool isLeftPlus = false; //布尔变量，确定是否向右缩进，默认为False，表示想左缩进
    long long iLengthMax = 0,i; //iLengthMax保存最长字符串长度，i为循环计数器
    while (!cin.eof()){ //没到EOF
        getline(cin, sInput); //读入当前行
        if (sInput.length() > iLengthMax){ //如果当前字符串长度比已有最大长度大
            iLengthMax = sInput.length(); //当前字符串长度为最大
        }
        arrStrings.push_back(sInput); //压入动态数组
    }
    cout << CreateRequiedString(iLengthMax + 2, '*')<<endl; //输出头部的一串星号
    for (i = 0; i <= arrStrings.size() - 2; ++i){ //开始循环，注意只需要循环到(动态数组大小-2)的位置，否则输出会多一行
        if (isEven(iLengthMax - arrStrings[i].length())) //如果iMaxLen-iLen为偶数，只需要再这个字符串两边分别补上(iMaxLen-iLen)/2和空格即可
            arrStrings[i] = CreateRequiedString((iLengthMax - arrStrings[i].length())/2, ' ') + arrStrings[i] + CreateRequiedString((iLengthMax - arrStrings[i].length())/2, ' ');
        else{ //如果iMaxLen-iLen为奇数，这时题目要求"先向左缩进一格，再向右缩进一格，再向左缩进一格..."，也就是先在原字符串两边加上(iMaxLen-iLen)/2和空格，之后再在左侧或右侧补一个空格即可，可以使用一个布尔型变量isLeftPlus记录。
            if (isLeftPlus){ //如果需要左侧多一个空格
                arrStrings[i] = CreateRequiedString((iLengthMax - arrStrings[i].length()) / 2+1, ' ') + arrStrings[i] + CreateRequiedString((iLengthMax - arrStrings[i].length()) / 2, ' '); //左侧多补一个空格
                isLeftPlus = false; //判断变量取反，下一次右侧多一个空格
            }
            else{ //否则
                arrStrings[i] = CreateRequiedString((iLengthMax - arrStrings[i].length()) / 2, ' ') + arrStrings[i] + CreateRequiedString((iLengthMax - arrStrings[i].length()) / 2+1, ' '); //右侧多一个空格
                isLeftPlus = true; //判断变量取反，下一次左侧多一个空格
            }
        }
        cout << '*' << arrStrings[i] << '*' << endl; //输出左右星号和处理过的字符串
    }
    cout << CreateRequiedString(iLengthMax + 2, '*') << endl; //输出末尾一串星号
    return 0; //结束
}
```

---

## 作者：离散小波变换° (赞：1)

## 题目大意

给出一个文本，要求居中，并用星号围起来。若无法准确居中，则第一次向左偏，第二次向右偏……依次类推。**可能有空行**。

## 题解

楼上大多用了较为繁琐的直接模拟，这里就介绍两个函数 $\tt memset$ 和 $\tt memcpy$ 吧。

### $\tt memset$ 函数

**函数原型**：$\verb!void* memset(void* dest,int ch,std::size_t count);!$

它的含义是，从位置 $\tt dest$ 开始，向后 $\tt count$ 位全部填充 $\tt ch$ 字符。虽然大多数人将其用作数组清空、赋值一个很大的数，但他的本来的用途的确是填充字符。举个例子：

假设有字符数组 $S$，下标从 $0$ 开始，

$$S=\texttt{\{a b c d d d a s e f g a\}}$$

我们现在需要从第 $3$ 位向后填充 $5$ 个$\tt e$，那么只需要执行 $\verb!memset(S+3,'e',5);!$ 即可。最终的结果为：

$$S=\texttt{\{a b c e e e e e e f g a\}}$$

用 $\tt memset$ 函数的好处是，填充第一行和最后一行的星号十分方便，并且中间内容初始化上空格也十分方便。

### $\tt memcpy$ 函数

**函数原型**：$\verb!void* memcpy(void* dest,const void* src, std::size_t count);!$

它的含义是，从位置 $\tt dest$ 开始，向后 $\tt count$ 位按位填充 $\tt src$ 的对应字符。同样地，我们举一个例子：

$$\begin{aligned}S&=\texttt{\{a b c d d d a s h f g a\}}\cr T&=\texttt{\{a p p l e\}}\end{aligned}$$

此时我们希望从 $S$ 的第 $4$ 位，填充从 $T$ 的第 $0$ 位开始的 $4$ 个字符 $\tt appl$，也就是 $\verb!memcpy(S+4,T+0,4);!$ 执行后的结果为：

$$S=\texttt{\{a b c d a p p l h f g a\}}$$

这个函数可以很方便地帮助我们向结果串里复制文本串。

### 读入整行

由于本题会出现空行，于是我们以 $\verb!`\n'!$ 作为分割线，每次读入整行，直到遇到 $\tt EOF$（即文件末尾，$\text{End Of File}$）。从中遇到的合法字符都读入到字符串内。同时，我们统计总行数 $n$，以及最长的字符串长度 $m$。

### 居中操作

这是本题比较重要的一个操作。具体而言，我们现在需要填充第 $i$ 个字符串 $S$，那么我们就需要找到这个字符串的开头应该填在哪里。记 $l$ 为 $S$ 的长度，那么当 $m-l\equiv 0\pmod 2$ 时，说明恰好可以填充，字符串第一位应该在 $1+\left\lfloor\frac{m}{2}\right\rfloor-\left\lfloor\frac{l}{2}\right\rfloor$。否则，如果无法恰好填充，那么就需要进行微调。记录一个布尔变量$d$，表示当前应该向左缩进还是向右缩进。特别要注意下取整等问题。

最后的代码其实非常简短。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
bool flg=true;
int readln(char *s){
    int len=0,c; while((c=getchar())!=10&&c!=EOF)
    if(c!=13) s[len++]=c; if(c==EOF) flg=false;
    return len;
}
const int MAXN =1000+2+3;
int L[MAXN],n,m;
char S[MAXN][MAXN],T[MAXN][MAXN]; bool d;
int main(){
    while(flg) ++n,L[n]=readln(S[n]),m=max(m,L[n]); --n;
    memset(T[0],'*',m+2),memset(T[n+1],'*',m+2); 
    up(1,n,i){
        memset(T[i]+1,' ',m),T[i][0]=T[i][m+1]='*';
        int ps=1+m/2-(L[i])/2; if((m-L[i])&1){
            if(m&1) ps+=d,d=!d; else d=!d,ps-=d;
        }
        memcpy(T[i]+ps,S[i],L[i]);
    }
    up(0,n+1,i) printf("%s\n",T[i]); puts("");
    return 0;
}
```

---

## 作者：Limit (赞：0)

CF老题..
质量比较一般,没有校验器要死了.
大概就是对准中间的时候第一个没法准确对准点向左一个,第二个向右...
```cpp
#include<bits/stdc++.h>
#define rap(i,first,last) for(int i=first;i<=last;++i)
using namespace std;
char s[1000][10000];//数组记录
int people=0,answer=0;
int main()
{
	int now=0;
	while(gets(s[++now]));//读入
	int textwide=0;//文本的宽度
	rap(i,1,now)textwide=max(textwide,(int)(strlen(s[i])+1));//得到最终的文本的的宽度
	rap(i,1,textwide+1)printf("*");//输出第一行的'*'
	printf("\n");
	int left,right,len;//分别为左边的空格数,右边的空格数,字符串的长度
	int check=0;
	rap(i,1,now-1)
	{
		left=0;right=0;
		len=strlen(s[i])+1;
		if((textwide-len)%2==0)
		{
			left=(textwide-len)/2;
			right=(textwide-len)/2;
		}
		else//如果没法对准
		{
			check=!check;//左右翻一下
			left=(textwide-len)/2+!check;//一个加0一个加1
			right=(textwide-len)/2+check;
		}
		printf("*");
		rap(j,1,left)printf(" ");
		printf("%s",s[i]);
		rap(j,1,right)printf(" ");
		printf("*\n");
	}
	rap(i,1,textwide+1)printf("*");//输出最后一行
	return 0;
}
```


---

