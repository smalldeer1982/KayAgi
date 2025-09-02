# 鏡文

## 题目描述

给出由b、d、p、q四种字符组成的字符串$S$。请判断$S$是不是“镜像字符串”。

这里的“镜像字符串”是指对字符串S进行以下操作后，可得到与原字符串相同的字符串。
1. 反转S。（例："bdpq"=>"qpdb"）
2. 改b为d，改d为b，改p为q，改q为p（不要搞错对应关系）

## 说明/提示

## 条件：
- $1≤|S|≤10^5$（$|S|$表示$S$的长度）
- $S$由且仅由b、d、p、q四种字符构成

感谢@std_cpp 提供的翻译

## 样例 #1

### 输入

```
pdbq```

### 输出

```
Yes```

## 样例 #2

### 输入

```
ppqb```

### 输出

```
No```

# 题解

## 作者：k2saki (赞：7)

这真的不配是个紫题。。。
简单的字符串就解决了。
真不了解前面几篇题解怎么写这么长的
# 先给你们介绍一种函数:reverse

```
reverse(a.begin(),a.end());
```



```cpp
string a;
cin>>a;
reverse(a.begin(),a.end());
cout<<a;
```

这个代码，如果输入为123456789abc,输出则为cba987654321.


既然有了reverse这个函数,这题也就迎刃而解了

## Code


```
#include<bits/stdc++.h>
using namespace std;
int main(){
	string a;
	cin>>a;
	string b=a;
	reverse(a.begin(),a.end());//交换
	for(int i=0;i<a.size();++i)
	{
		if(a[i]=='b') a[i]='d';//镜面对称
		else if(a[i]=='d') a[i]='b';//请注意,else一定要加,不然就白做了
		else if(a[i]=='p') a[i]='q';
		else if(a[i]=='q') a[i]='p';
	}
	if(a==b) cout<<"Yes";//判断
	else cout<<"No";
}
```

---

## 作者：PBCWZCC (赞：6)

或许是最短的题解？

这是个~~紫题难度的大~~模拟啊

这里是整个字符串的反转，所以如果我们从下标$1$开始存储，那么很显然，

$s[1]\ ->\ s[len]$

$s[2]\ ->\ s[len-1]$

$s[3]\ ->\ s[len-2]$

$...$

于是我们的第一步就完成了。

让每个字符对应一个值$val$，用转环的方式让它的对应改变：
```
0 1 2 3
b p d q
->
d q b p
```
可知$val[d] = (val[b]+2)\ \mathrm{mod}\ 4$，

$val[q] = (val[p]+2)\ \mathrm{mod}\ 4$

这样就处理了题目操作中的第二步啦

二话不多说，上代码~

```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
char s[100007];
int get[128];
int main()
{
	get['b'] = 0 , get['p'] = 1 , get['d'] = 2 , get['q'] = 3;
	scanf("%s",s+1); // 从 s[1] 开始的
	for(int l = strlen(s+1), i = 1; i <= (l>>1) + 1; ++i)
	{
		if(get[s[i]]^((get[s[l-i+1]]+2)%4)) return printf("No\n"),0;
	} // 这个 +2 %4 刚好让 b 转到 d 上， d 转到 b 上， p 转到 q 上， q 转到 p 上 
	return printf("Yes\n"),0;
}
```

---

## 作者：南苑沁青 (赞：5)

#### 基本上所有的字符串问题都能够用 Hash 来做 ~~(Hash 是万能的！)~~ 。

对于这题，只需要预处理出 Hash 函数值，先对原字符串正向做一遍 Hash ，再对更改后的字符串反向做一遍 Hash 。判断两次的 Hash 值是否相等就行了。
### Code:
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
#include<cstring>
#include<string>
#include<deque>
#include<map>
#include<cmath>
#include<stack>
#include<vector>
#include<queue>
#include<cstdlib>
using namespace std;
#define lck_max(a,b) ((a)>(b)?(a):(b))
#define lck_min(a,b) ((a)<(b)?(a):(b))
typedef long long LL;
const int maxn=1e6+7;
const int mod=998244353;
LL hash[maxn];
char s[maxn];
struct hh
{
	LL first,second;
}t;
inline void Hash()
{
	hash[0]=1;
	for(LL i=1;i<=maxn-1000;i++)
	{
		hash[i]=hash[i-1]*13%mod;
	}
}
inline void change(LL len)
{
	for(LL i=0;i<len;i++)
	{
		if(s[i]=='b') {s[i]='d';continue;}
		if(s[i]=='d') {s[i]='b';continue;}
		if(s[i]=='q') {s[i]='p';continue;}
		if(s[i]=='p') {s[i]='q';continue;}
	}
}
int main()
{
	Hash();
	scanf("%s",s);
	LL len=strlen(s);
	for(LL i=0;i<len;i++) t.first=(t.first+s[i]*hash[i])%mod;
	change(len);
	for(LL i=len-1;~i;i--) t.second=(t.second+s[i]*hash[len-i-1])%mod;
	if(t.first==t.second) puts("Yes");
	else puts("No");
return 0;
}
```

---

## 作者：xxckie (赞：3)

看到各位dalao的解法，本小学森也忍不住来发一篇题解^-^

本题是一道字符串模拟题，做起来还是比较简单的.

下面说说我滴思路：

1、先输入字符串，再反向储存一下

2、在反向储存的同时，也要注意变化规则：**改b为d，改d为b，改p为q，改q为p（不要搞错对应关系）**

3、一一比较每一位是否一样（因为本蒟蒻反向储存的是char数组，不知道为什么用string输出的是xxx.....）

大体思路就是这个样子的了.

代码献上：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>

using namespace std;
string st;
char ch[100000+10];
long long len;
int main()
{
	cin>>st;//输入字符串
	len=st.size();//记下st的长度
	for(int i=0;i<st.size();i++)
	{
		ch[len-i-1]=st[i];//先反向储存
		if(st[i]=='b')ch[len-i-1]='d';
		if(st[i]=='d')ch[len-i-1]='b';
		if(st[i]=='p')ch[len-i-1]='q';
		if(st[i]=='q')ch[len-i-1]='p';//如果是有特殊情况的四个字母，要用if来判断反向储存成什么样子
	}
	for(int i=0;i<len;i++)
		if(ch[i]!=st[i])//一一比较每一位是否一样，不一样的话...
		{
			cout<<"No"<<endl;//输出“No”（岛国题...换行（不过这题貌似不用））
			return 0;//结束程序
		}
	cout<<"Yes"<<endl;//如果全都一样的话，输出“Yes”
return 0;
}
```
这就是本题我的题解啦！若dalao觉得有什么不足的话，请在右边→评论区告诉我，蟹蟹\(^o^)/

---

## 作者：Spiritsu (赞：3)

rz题，没加break，学校的ide调试还炸了是我的错 

（淦，就我一个人拉低了这道破题的ac率对不起是我的错orz）


就是道水的不能再水的模拟，都能一遍a的（太菜了）

看下面就行了（我实在是太丢人了）
```
#include<cstdio>
#include<iostream>
#include<cstring>
#include<stack>
using namespace std;
stack<char>s;
string a;
int main(){
    cin>>a;
    int n=a.size();
    for(int i=0;i<n;i++){
        s.push(a[i]);
    }
    bool ju=1;
    for(int i=0;i<n;i++){
        char top=s.top();
        if(top=='b') top='d';
        else if(top=='d') top='b';
        else if(top=='p') top='q';
        else if(top=='q') top='p';
        if(top==a[i]) {
        	ju=1;
			s.pop();
		}
        else {
        	ju=0;
        	break;
		}
    }
    if(ju==0) printf("No");
    else printf("Yes");
    return 0;
}
```
抄了就抄了吧，不值得让这道rz题浪费各位dalao的时间

---

## 作者：Aliemo (赞：2)

# 其实这道题很简单 
### 可以先不用按他的来 可以

## 1.改b为d，改d为b，改p为q，改q为p（不要搞错对应关系）
## 2.反转S。（例："bdpq"=>"qpdb"）
#### 最后比较就可以了	QWQ

###### 代码中也有解释
代码  
```cpp
#include <cstdio>//头文件不解释
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iomanip>
#define rr register
#define int long long
#define f_for(i,a,b) for(rr int i=a;i<=b;i++)
using namespace std;
const int maxx=1e4;
int n,m;
string a,b;
signed main(){
	cin>>a;
	b=a;// 把原来的赋到b上最后比较
	bool t=true;
	int len=a.length()-1;
	for(rr int i=0; i<=len; i++)
		switch(a[i]){
			case 'q': a[i]='p';break;
			case 'p': a[i]='q';break;
			case 'b': a[i]='d';break;
			case 'd': a[i]='b';break;
		}
	for(rr int i=0;i<=len;i++)
		if(a[i]!=b[len-i])
			t=false;//我这里没有翻转，我把它倒过来比较更省时间。
	if(t)
		cout<<"Yes"<<endl;
	else
		cout<<"No"<<endl;//岛国题。。加回车
}
```

---

## 作者：Egg_eating_master (赞：1)

# STL大法好~
#### 三个STL连用~

string+map+reverse=AC~

string不多说，大家应该都知道 ~

reverse是一个函数，用法：
```
reverse(it1,it2);
```
表示反转左闭右开的[it1，it2)区间所有元素。

map翻译为映射，是STL中的常用元素。其实，数组就是一种映射。比如：a[5]=25;这就是将5映射到25。数组总是将int映射到其他类型。但是，我们有时希望将其他类型进行映射，比如将string映射到int，于是map登场了。

map的定义方式：
```
map<类型一,类型二>mp;
```
这就定义了一个从类型一到类型二的映射。

map的访问：
```
mp[变量一]=变量二;
```
是将变量一映射到变量二。

好啦，应该讲的比较清楚了吧。可以上代码了~
```
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
map<char,char>mp;//定义一个从char类型到char类型的映射
void init(){
	cin>>s1;
	s2=s1;
	mp['b']='d';mp['d']='b';mp['q']='p';mp['p']='q';
    //将b映射到d，将d映射到b，
    //将q映射到p，将p映射到q。
}
int main(){
	init();
	reverse(s2.begin(),s2.end());//反转整个string
	for(int i=0;i<s2.size();i++)
	    s2[i]=mp[s2[i]];//不断将字符进行映射
	if(s1==s2)//如果系列操作后还是原来的字符串
	    cout<<"Yes\n";//输出Yes
	else 
	    cout<<"No\n";否则输出No
	return 0;
}
```


---

## 作者：Bob_Wang (赞：1)

~~像我这样的人估计也只做得起这种“水题”了吧~~  
###### 弱弱的问一句，有用指针做的吗？    
初始时先定义一个head指针指向首字母，再定义一个tail指针指向尾字母，将tail指向的字母进行操作，与head指向的字母对比，直到循环结束，便可判断是否为镜文。

上代码：
```c
#include<cstdio>
#include<cstring>
#define maxn 100005
using namespace std;
char s[maxn];
int main()
{
	int len,flag=1;//flag打标记
	scanf("%s",s+1);
	len=strlen(s+1);
	int head=1,tail=len;//定义指针
	for(int i=1;i<=len;i++)
	{
		char n;
		if(s[tail]=='b')n='d';
		else if(s[tail]=='d')n='b';
		else if(s[tail]=='p')n='q';
		else if(s[tail]=='q')n='p';
		if(n!=s[head])
		{
			flag=0;
			break;
		}//遇到不匹配的字母
		head++;
		tail--;
	}
	if(flag)
	printf("Yes");
	else
	printf("No");
	return 0;
}
```

~~我觉得是入门难度的题。。。~~

---

## 作者：WKAHPM (赞：1)

一道简单的字符串模拟，~~刷难度真给力~~

#### 本蒟蒻的思路比较麻烦，但个人认为比较好理解

- 1 先将字符串倒序存放

- 2 按照规则改变字母

- 3 比较

## Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
char s1[100010],s2[100010];
int len;
int main()
{
	cin>>s1;
	for(int i=strlen(s1)-1; i>=0; i--)
	{
		s2[len++]=s1[i];//倒序存放
	}
	for(int i=0; i<strlen(s2); i++)
	{
		switch(s2[i])//按照规则改变字母
		{
			case 'b':
			{
				s2[i]='d';
				break;
			}
			case 'd':
			{
				s2[i]='b';
				break;
			}
			case 'p':
			{
				s2[i]='q';
				break;
			}
			case 'q':
			{
				s2[i]='p';
				break;
			}
		}
	}
	if(strcmp(s1,s2)==0) cout<<"Yes"<<endl;//比较，注意如果两个字符串一样，strcmp返回0
	else cout<<"No"<<endl;//记得换行
	return 0;
}

```

---

## 作者：捻红尘似水 (赞：1)

翻转后再比较，实际上相当于与将原字符串的第一个与最后一个比较。
如果字符串的字符数是奇数，则一定会在比较时有一个字符自己和自己比较，这样一定不是镜像字符串




```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>;
using namespace std;
char s[100010];
int main(){
    scanf("%s",&s);
    int k=strlen(s);
    if(k%2!=0){//如果项数是奇数，则一定不是镜像字符串 
        printf("No");
        return 0;
    }
    for(int i=0;i<k/2;i++){
    	int u=abs(s[i]-s[k-i-1]);
        if(u!=1&&u!=2){//两项的差要么为1，要么为2 
        	printf("No");//两项之差不为1，不为2，说明不是镜像字符串 
            return 0;
        }
    }
    printf("Yes");
    return 0;
}
```


---

## 作者：Yocim丶 (赞：1)

这题本来以为是紫题的，一看原来是刷的难度，AC题解一发，一起把题目拉回普及-，主要就是从开始和结尾找，记录一下，不一样就改变ok的值，然后按方案2改一遍（不知道需不需要按方案2，感觉不需要，方案1是明显没有用），继续找就行了
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin>>s;
	int n=s.size();
	int ok=0;
	for(int i=0;i<n;i++){
		int j=n-i-1;
		if(s[i]=='q'&&s[j]=='p'){}
		else {
		    if(s[i]=='b'&&s[j]=='d'){}
		    else {
			if(s[i]=='d'&&s[j]=='b'){}
		          else {if(s[i]=='p'&&s[j]=='q'){}
		          else ok=1;
	              }
            }
        }
    }
	if(ok==0){
		cout<<"Yes"<<endl;return 0;
	}
	ok=0;
	for(int i=0;i<n;i++){
		if(s[i]=='p')s[i]=='q';
		if(s[i]=='q')s[i]=='p';
		if(s[i]=='b')s[i]=='d';
		if(s[i]=='d')s[i]=='b';
	}
	for(int i=0;i<n;i++){
		int j=n-i-1;
		if(s[i]=='q'&&s[j]=='p'){}
		else {
		    if(s[i]=='b'&&s[j]=='d'){}
		    else {
			if(s[i]=='d'&&s[j]=='b'){}
		          else {if(s[i]=='p'&&s[j]=='q'){}
		          else ok=1;
	              }
            }
        }
    }
    if(ok==0)cout<<"Yes"<<endl;
    else cout<<"No";
	return 0;
}
```

---

## 作者：人间凡人 (赞：0)

这道题是一道字符串的模拟题。

假设输入的字符串为$s$。

首先，让我们来看一下操作$1$：翻转$s$。

这个其实很好实现，可以用$C++$中的$reverse$函数，当然也可以自己写：新定义一个字符串s1，逐次倒着加入。

```cpp
cin>>s;len=s.length();
for(int i=len-1;i>=0;i--)s1=s1+s[i];
```
操作$2$：改b为d，改d为b，改p为q，改q为p。(注意： 是在s1的基础上执行此操作！）

这想必大家也会的吧，依次判断即可。

```cpp
for(int i=0;i<len;i++){
		if(s1[i]=='b')s2=s2+'d';
		if(s1[i]=='d')s2=s2+'b';
		if(s1[i]=='p')s2=s2+'q';
		if(s1[i]=='q')s2=s2+'p';
	}
```
那么只要讲以上两个代码合并，判断一下就行了。

$Code:$

```cpp
#include <bits/stdc++.h>
using namespace std;
int len;string s,s1,s2;
int main() {
	cin>>s;len=s.length();
	for(int i=len-1;i>=0;i--)s1=s1+s[i];
	for(int i=0;i<len;i++){
		if(s1[i]=='b')s2=s2+'d';
		if(s1[i]=='d')s2=s2+'b';
		if(s1[i]=='p')s2=s2+'q';
		if(s1[i]=='q')s2=s2+'p';
	}
	if(s==s2)printf("Yes\n");
	else printf("No\n");
	return 0;
}

```


---

## 作者：七夜 (赞：0)

//首先声明，这个题只存在b,d,p,q，所以其他的不用考虑

//其次，因为镜像不只是改变了字母的样子，也改变了先后顺序。

//还有，提醒一下，有多个字符或者字符串的时候，别用scanf

//然后奉上本蒟蒻的代码

```
#include<bits/stdc++.h>//偷偷懒 
using namespace std;
inline int read() {
	char c = getchar(); int x = 0, f = 1;
	while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * f;
}//这是快读，我也是刚学会，想学的可以参考一下 ，不想的改成cin或者scanf一样，这里只是生命，代码里没用（缺省源） 
bool t=1;//判断是否相等 
string s;//读入的字符串 
char ss[5201314];//存储变化后的字符串 
int main()
{
	cin>>s;//这里不能用快读，具体为什么我也不知道，用了报错 
	int l=s.size();//求出长度 
	for(int i=0;i<s.size();++i)//循环存储变化后的 
	 {
	 	if(s[l-i-1]=='p')
	 	 ss[i]='q';
	 	if(s[l-i-1]=='q')
	 	 ss[i]='p';
	 	if(s[l-i-1]=='d')
	 	 ss[i]='b';
	 	if(s[l-i-1]=='b')
	 	 ss[i]='d';
	 }//因为是镜像，所以不仅要字母变化，前后顺序也需要变化 
	for(int i=0;i<l;++i)
	 {
	 	if(s[i]!=ss[i])
	 	 t=0;
	 }//判断，只要有一个不相等的，就不匹配 
	if(t==1)
	 cout<<"Yes\n";//匹配的答案，注意大小写 
	else
	 cout<<"No\n";//不匹配的答案，注意大小写 
	return 0;//完美落幕 
}
```
//还希望能过

---

## 作者：zws_hao (赞：0)

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char a[1000001],c[1000001];
int main(){
	int b,sum=0,l=0;
	cin>>a;
	b=strlen(a);
	for(int i=b-1;i>=0;i--) {
		c[sum]=a[i];
		if(c[sum]=='b') c[sum]='d';
		else if(c[sum]=='d') c[sum]='b';
		else if(c[sum]=='p') c[sum]='q';
		else if(c[sum]=='q') c[sum]='p';
		sum++;
	}
	for(int i=0;i<=b-1;i++) {
		//cout<<a[i]<<" "<<c[i]<<endl;
		if(a[i]!=c[i]){
			cout<<"No"<<endl;
			return 0;
		}
	}
	cout<<"Yes"<<endl;
	return 0;
}


---

## 作者：萌萌哒小女孩 (赞：0)

纯粹的一道刷难度的题(假紫题)

纯模拟(比我先写的Pascal是反转和修改一起做的，我的是分开做的)

AC代码：
```pascal
var s,s1:ansistring;i:longint;ch:char;
begin
  readln(s);s1:=s;
  for i:=1 to length(s) div 2 do   //反转(注意细节)
  begin
    ch:=s[i];
    s[i]:=s[length(s)-i+1];
    s[length(s)-i+1]:=ch;
  end;
  for i:=1 to length(s) do       //修改字符
    if s[i]='b' then s[i]:='d'
      else if s[i]='d' then s[i]:='b'
        else if s[i]='p' then s[i]:='q'
          else s[i]:='p';
  if s=s1 then writeln('Yes') else writeln('No');
end.
```


---

## 作者：zcl1024 (赞：0)

这是一道很水的模拟题，~~（不过很适合装逼）~~  
其实这道题没什么好讲的，就是按题意模拟即可  
献上cpp&&pascal代码

```
#include <iostream>
#include <string>
using namespace std;
int main(){
    string a;
    cin>>a;
    string b=a;
    a="";//记得把原字符串清0
    int x=b.size();
    int i;
    for (i=0;i<x;i++) a=b[i]+a;//把字符串倒过来
    for(int i=0;i<x;i++){//字符替换
        if (a[i]=='b') a[i]='d';
        else if (a[i]=='d') a[i]='b';
        else if (a[i]=='p') a[i]='q';
        else if (a[i]=='q') a[i]='p';
    }
    if(a==b) cout<<"Yes"<<endl;//判断是否相同
    else cout<<"No"<<endl;
    return 0;
}
```

-----------------

```
var i,n:longint;
    a,b:ansistring;//一定要用ansistring
begin
  readln(a);
  n:=length(a);
  for i:=1 to n do b:=a[i]+b;//新建一个a的翻转串
  for i:=1 to n do//字符替换
  if b[i]='b' then b[i]:='d'
  else if b[i]='d' then b[i]:='b'
  else if b[i]='p' then b[i]:='q'
  else b[i]:='p';
  if a=b then writeln('Yes')
  else writeln('No');
end.
```

---

## 作者：封禁用户 (赞：0)

看了一遍，没有Pascal的，就发一篇吧！ 

此题太水，怎么能称为紫题呢？（各人认为应该是橙题）

## 思路
### 1.输入
### 2.反转并替换
### 3.判断输出
输入不用说了吧

反转和替换可以分开做，也可以一起做（我用了一起做）

判断新生成的字符串是否与输入的字符串相同，相同输出Yes，不同输出No。

接下来献上Pascal代码
```
var s,s1:string;
    i,len:longint;
begin
 readln(s);
 len:=length(s);
 for i:=1 to len do
 case s[i] of
  'b':s1:='d'+s1;
  'd':s1:='b'+s1;
  'p':s1:='q'+s1;
  'q':s1:='p'+s1;
 end;
 if (s=s1) then writeln('Yes') else writeln('No');
end.
```
实在不会的那就算了，去看别的大佬的更简洁的算法吧（我是蒟蒻）

---

## 作者：xujian (赞：0)

~~又一道恶意评分的水题，感紧发下题解~~

## 主要用到的语句：reverse（楼下大佬解释过了就不重复了）、switch（开关语句）、三目运算符。

## switch简单的用法：

```
case 表达式:语句;break;
```
这样使语句更加方便，也比多行的嵌套if更加美观。

### 但要注意的是，语句后一定要break，否则会把下面所有语句执行。

三目运算符简单用法：
```
表达式?语句1:语句2
在表达式成立时执行语句1，否则执行语句2
```
这看起来比if没好什么，不过在有些时候会更方便。

比如：
```cpp
if(a<b)s+=a;
else s+=b;
```
就可以变为：
```
s+=a<b?a:b;
```
这样看来就方便多了。

### 正文到此为止，代码如下，求管理大大给过。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,b;
int main(){
    cin>>s;
    b=s;reverse(s.begin(),s.end());
    for(int i=0;i<s.size();i++)
        switch(s[i]){
            case 'b':s[i]='d';break;
            case 'd':s[i]='b';break;
            case 'p':s[i]='q';break;
            case 'q':s[i]='p';break;
        }
    s==b?puts("Yes"):puts("No");
    return 0;
}
```


---

## 作者：rui_er (赞：0)

首先，我们用字符串s1来进行操作，s用来对照。题目说1<=|s|<=10^5，因此数组开大一点。其次，容易想到，|s|是奇数时不可能满足条件，故加上：

```cpp
if(l&1)
{
	cout<<"No"<<endl;
    return 0;
}
```

其中```&```是```按位与运算```

之后，分两步，如题。

写出下列代码：

```cpp
for(int i=0;i<l;i++) s1[i] = s[l-i-1]; 
for(int i=0;i<l;i++)
{
	if(s1[i] == 'b') s1[i] = 'd';
	else if(s1[i] == 'd') s1[i] = 'b';
	else if(s1[i] == 'p') s1[i] = 'q';
	else s1[i] = 'p';
}
```

综合以上，判断字符串相等，使用```strcmp()```。

综合所有，下为完整代码：

```cpp
#include <iostream>
#include <string.h>
using namespace std;

char s[100010];
char s1[100010];

int main()
{
	cin>>s;
	int l = strlen(s);
	if(l&1)
	{
		cout<<"No"<<endl;
		return 0;
	}
	for(int i=0;i<l;i++) s1[i] = s[l-i-1]; 
	for(int i=0;i<l;i++)
	{
		if(s1[i] == 'b') s1[i] = 'd';
		else if(s1[i] == 'd') s1[i] = 'b';
		else if(s1[i] == 'p') s1[i] = 'q';
		else s1[i] = 'p';
	}
	if(!strcmp(s1, s)) cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
}
```

---

## 作者：wzm2007 (赞：0)

    需要判断长度是否为奇数,是的话直接输出No
    否则再判断

------------

    #include<bits/stdc++.h>
    using namespace std;
    char s[100010],s1[100010];
    int main()
    {
        cin>>s;
        int l=strlen(s);
        if(l&1)  //判断是否为奇数
        {
            cout<<"No";
            return 0;
        }
        for(int i=0;i<l;i++)s1[i]=s[l-i-1];  //翻转
        for(int i=0;i<l;i++)  //改字母
        {
            if(s1[i]=='b')s1[i]='d';
            else if(s1[i]=='d')s1[i]='b';
            else if(s1[i]=='p')s1[i]='q';
            else s1[i]='p';
        }
        if(!strcmp(s1,s))cout<<"Yes";  //比较
        else cout<<"No";
        return 0;
    }

---

## 作者：xixiup (赞：0)

话说这道题为什么是紫题呢？

直接用一个带了两个循环链的for外加一堆if判断就解决了嘛（~~逃~~。

上丑码 ~~if用多了~~

```

#include<bits/stdc++.h>//万能头QwQ
using namespace std;
char s[100050];//数组（有必要说吗？）
int l,i,j;
int main()//主函数QwQ
{
	gets(s);//输入
	l=strlen(s);//长度
	if(l%2){//如果长度为奇数，则中间那个无法匹配。
		puts("No");
		return 0;
	}
	for(i=0,j=l-1;i<j;i++,j--){//两个变量
/*海量的if，密集恐惧症者慎入QwQ*/
		if(s[i]=='p'&&s[j]!='q'){
			puts("No");
			return 0;
		}
		else{
			if(s[i]=='q'&&s[j]!='p'){
				puts("No");
				return 0;
			}
			else{
				if(s[i]=='b'&&s[j]!='d'){
					puts("No");
					return 0;
				}
				else{
					if(s[i]=='d'&&s[j]!='b'){
						puts("No"); 
						return 0;
					}
				}
			}
		}
	}
	puts("Yes");//回文串
	return 0;
}

```

---

