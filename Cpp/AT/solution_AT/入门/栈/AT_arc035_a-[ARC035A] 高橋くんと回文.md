# [ARC035A] 高橋くんと回文

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc035/tasks/arc035_a

高橋くんは、ある文字列を持っていました。あるとき、Cat Snuke がやってきて文字列の一部を食べてしまいました。

 高橋くんは元の文字列が回文であった可能性があるかを知りたいです。そこで、食べられた文字を適切に埋め合わせて、回文とすることができるか調べてください。食べられた文字それぞれを、どの文字で埋め合わせるかは自由に決められます。

## 说明/提示

### Sample Explanation 1

`\*` を `a` で埋め合わせると、`aba` となるので、元の文字列は回文であった可能性がある。

### Sample Explanation 2

`abc` は回文ではない。

### Sample Explanation 3

`acbca` と埋め合わせると回文となる。

## 样例 #1

### 输入

```
ab*```

### 输出

```
YES```

## 样例 #2

### 输入

```
abc```

### 输出

```
NO```

## 样例 #3

### 输入

```
a*bc*```

### 输出

```
YES```

## 样例 #4

### 输入

```
***```

### 输出

```
YES```

# 题解

## 作者：Komorebi_shine (赞：1)

~~终于得知代码是3·而不是1·后的首篇题解~~

代码修改于普通回文数。与楼下大佬们都不同的是，我是遇到*直接忽略，这样也不影响结果。

附~~UKE代码~~c++正解
```
// var
//  s:ansistring;
//  n,i:longint;
// begin
//  readln(s);
//  n:=length(s);
//  for i:=1 to n div 2 do
//   if (s[i]<>'*')and(s[n-i+1]<>'*')and(s[i]<>s[n-i+1]) 
//   then begin 
//          writeln("NO");
//          exit;
//         end;
//  writeln("YES");
// end.
#include<bits/stdc++.h>
using namespace std;
char s[1000];
int n,i;
int main()
{
    cin>>s;
    n=strlen(s);
    for (i=0;i<=n/2-1;i++)//从0开始
     if ((s[i]!='*')&&(s[n-i-1]!='*')&&(s[i]!=s[n-i-1]))//直接忽略，即使是两个*号也能正常输出。
     {
         cout<<"NO"<<endl;
         return 0;
     }
    cout<<"YES"<<endl;
}
```

---

## 作者：ShineEternal (赞：1)

本蒟蒻代码较朴素，大佬勿喷

------------

# 其实已经有一点贪心的味道了。。。

遇到**时，就把他赋值为对称的另一边的字符，
如果还是*就不用多做考虑。
```
#include<cstdio>
#include<cstring>
using namespace std;
char s[1001];
int main()
{
	gets(s);//直接一行
	int n=strlen(s);//记下长度，既简洁，又能减少运算次数
	for(int i=0;i<n;i++)
	{
		if(s[i]=='*')
		{
			s[i]=s[n-i-1];
		}//判断*赋何值
	}
	for(int i=0;i<n;i++)
	{
		if(s[i]!=s[n-1-i])
		{
			printf("NO\n");
			return 0;
		}//如果遇到一对字符不回文，整体一定不回文，打印NO之后可以跳出程序了。。。
	} 
	printf("YES\n");//既没打NO也没跳出，那一定回文了
	return 0;//再次结束程序
}
```

---

## 作者：CZQ_King (赞：0)

# 此题特~~难~~
与普通的回文题差不多,加个特判就行(我加了俩)，用了$2$个字符串,一个正的,一个反的(翻转后的)
。所以像我这种办法的话,不仅要判断第一个字符串的某一位是否是乘号(好像不是乘号这个意思,应该叫"任何数"),还要判断第二个字符串的某一位是不是任何数
##### $reverse$大法好
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
string a,b;//2个字符串
int main(){
    cin>>a;
    b=a;//复制
    reverse(b.begin(),b.end());//reverse翻转
    for(int i=0;i<a.length();i++){//依次判断
        if(a[i]!=b[i]&&a[i]!='*'&&b[i]!='*'){//普通判断+2*特判
            cout<<"NO"<<endl;//不符合就输出NO
            return 0;//完美结束*1
        }
    }
    cout<<"YES"<<endl;//全符合,输出YES
    return 0;//完美结束*2
}
```

---

## 作者：_Error (赞：0)

## 极水的一题，其实只要在判断回文数里面加一些特判，判断他是不是*号就可以了。
## 不说废话，来程序：
```cpp
//头文件
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;
string st;
int jl;
int main()
{
 cin>>st;//读入
 for (int i=0;i<=(st.size()-1)/2;i++)//截一半来循环
 {
 	if (st[i]!=st[st.size()-(i+1)])//判断，前面的和后面的是否相同
 	    if (st[i]=='*'||st[st.size()-(i+1)]=='*') ; else
 	        {jl=1;break;}//再判断，如果前面的和后面其中一个是*号就不理他，否则，记录他不能成为回文数并退出。
 }
 if (jl==0) cout<<"YES"<<endl; else cout<<"NO"<<endl;//判断，如果他是回文数就输出YES，否则输出NO。
 return 0;
}

```

---

## 作者：Ackoter (赞：0)

作为一个蒟蒻，我敢说这是一道非常~~简单~~难的题目

这道题和一般的回文题目差不多，唯一的差别就是多了个星号所以我们直接忽略判断星号和星号对应的字符就行了
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
string st;
int main()
{
	cin>>st;
	for(int i=0;i<st.size()/2;i++)
		if(st[i]!='*'&&st[st.size()-i-1]!='*'&&st[st.size()-i-1]!=st[i]) {cout<<"NO\n";return 0;}//忽略*，否则的话就判断对应字符是否相同，不同就输出NO后退出
    cout<<"YES\n";//如果没有NO的情况，那就是YES
	return 0;
}
```

---

## 作者：YooLc407 (赞：0)

~~*看到了楼上两位红名大佬的蒟蒻默默发抖....*~~

这道题就是检测回文字符串的升级版，没有什么特殊的地方，那么我们可以先把它**“降级”**回最初始的字符串。

因为"\*"字符可以替代为任何字符，我们就假设是最理想的状态，即把"\*"字符符全部替换成可以对称过去的字符。

**核心部分:**

```cpp

length--; //因为字符数组是从0开始的，所以减一
for(i=0;i<=length;i++)
{
    if(a[i]=='*' && a[length-i]!='*') //遇到*就替换（貌似不加&&后面的也可以）
     a[i]=a[length-i];//替换
}
    
```

**判断是否回文：**

```cpp
//flag初始为1;
for(i=length/2;i>=0;i--)//蒟蒻只能想到这种办法...可能有奇特的bug
{
    if(a[i]!=a[length-i])//如果发现不对称
    {
        flag=0;//设置为0
        break;//退出，后面就不徒劳了
    }
}
    
```

如果flag==1则输出"YES"

否则输出"N0"

**注意这里是全大写，至于换行，反正我加了~**

**附带蒟蒻的完整代码，没有注释~**

```cpp
#include <iostream>
#include <cstring>//需要获得字符串长度
using namespace std;
char a[1001];//本来打算把判断做成一个函数，就放在外面了
int main()
{
    cin>>a;//输入字符串
    int length=strlen(a),i,flag=1;
    //替换过程
	length--;
    for(i=0;i<=length;i++)
    {
        if(a[i]=='*' && a[length-i]!='*')
            a[i]=a[length-i];
    }
    //检测回文
    for(i=length/2;i>=0;i--)
    {
        if(a[i]!=a[length-i])
        {
            flag=0;
            break;
        }
    }
    //输出
    if(flag==1)
        cout<<"YES"<<endl;
    else
        cout<<"NO"<<endl;
    return 0;
    //牢骚部分#(滑稽)
    cout<<"我永远喜欢~~洛谷~~"<<endl;
}
```


---

## 作者：_Qer (赞：0)

题意：有一串字符，被吃掉了一部分（可能没有），被吃的地方用*代替。判断这串字符有没有可能是回文的（即正着读和反着一样），如果可能就输出YES，否则输出NO

可以使用一个string类型变量存储输入的字符串，因为这种类型可以通过下标方式来访问，所以我们可以很容易地做出来。

用一个循环，来遍历这个字符串的前半部分，然后与后半部分的对应字符进行对比，如果不符合，就直接退出并输出NO，如果判断到最后都没有发现不符合的就输出YES

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    string s;//输入的字符串
    int l;//字符串的长度
    cin>>s;//字符串可以直接使用cin输入
    l=s.length();//使用.length()函数取出字符串长度
    for(int i=0;i<l/2;++i){//循环前半部分
        if(s[i]==s[l-i]||s[i]=='*'||s[l-i]=='*'){
            continue;
//如果对应字符相同或者其中一个被吃了（为*）就继续循环
        }else{//否则即为不成立，输出NO后结束程序
            cout<<"NO"<<endl;
            return 0;
        }
    }
    cout<<"YES"<<endl;//一直没有发现不对的，输出YES
    return 0;
}
```

---

