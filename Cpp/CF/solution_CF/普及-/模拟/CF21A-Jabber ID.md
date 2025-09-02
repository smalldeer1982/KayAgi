# Jabber ID

## 题目描述

一个地址由 `<username>@<hostname>[/resource]` 组成，其中 `[/resource]` 可以被省略。

- `<username>` 字段允许大写、小写字母，数字、下划线，其长度应在 $1$ 到 $16$ 之间。
- `<hostname>` 字段允许用 `.` 来分隔。每一段的要求同  `<username>` 字段，分隔出的每一部分长度在 $1$ 到 $16$，`<hostname>` 字段的总长度在 $1$ 到 $32$ 之间。
- `<resource>` 字段要求同 `<username>` 字段。


给出一个地址，询问是否合法。

## 样例 #1

### 输入

```
mike@codeforces.com
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
john.smith@codeforces.ru/contest.icpc/12
```

### 输出

```
NO
```

# 题解

## 作者：andyli (赞：4)

可以使用正则表达式进行匹配。  
```regex
^\w{1,16}@\w{1,16}(\.\w{1,16})*(\/\w{1,16})?$
```
`^` 和 `$` 分别表示一行的开始和结束；  
`\w{1,16}` 表示 `\w`（即题目中的大写、小写字母，数字、下划线）重复 $1$ 到 $16$ 次；  
`(\.\w{1,16})*` 匹配题目中的 `<hostname>` 用 `.` 分割的第二个部分。  
`(\/\w{1,16})?` 匹配 `/resource` 部分，`?` 表示 $0$ 次或 $1$ 次。  
`.` 和 `/` 为特殊字符故用 `\` 标记
```python
import re
print(re.match(r'^\w{1,16}@\w{1,16}(\.\w{1,16})*(\/\w{1,16})?$', input()) and 'YES' or 'NO')
```

---

## 作者：SIXIANG32 (赞：3)

一道神仙模拟题……  
闲话少说，切入正题：


------------
我们先拿样例做个例子：  
（由于第一个正确样例没有```[/resource]```字段，于是补了一段）  
$\texttt{mike\color{red}@\color{black}codeforces.com\color{red}/\color{black}WANH}$  

这样我们可以清楚的看到，这串地址由三个部分组成，也就是题目中说的```<username>@<hostname>[/resource]```，我们以```@```作为```<username>```的结束符，```/```作为```<hostname>```的结束符，剩下的就是```[/resource]```字段。  

先分割出每个字段，然后根据题目描述进行判断就可以啦！  


------------
你以为一道CF模拟题会这么轻易的让你过吗？（邪魅一笑  
CF群众的HACK力量真是强大，一道这么老的模拟题都有很多神仙数据/kk  
下面让本蒟蒻总结自己走过的坑点吧：  

1. ```<username>```和```<hostname>```必须要有！  
2. ```@```不算在数量之内。  
3. ```[/resource]```结束符不能是```/```和```.```。
4. 在```<hostname>```中，不能有相邻的```.```，但允许有多个```.```（这一点题目描述的翻译没有说明/fad）。   
5. ```<hostname>```的开头不能是```.```。  
6. ```[/resource]```没有长度限制。
7. ```[/resource]```的结束不能是```/```。

扯完了这么多，上代码！  
```cpp
//注：这三个字段均带了结束符！
#include<iostream>
#include<string>
using namespace std;
bool checkone(string str)//检查username
{
	if(str.size()>=17||str.size()==1)return 0;//长度判断，这里str.size()==1判断了是不是空的
	for(int p=0;p<str.size();p++)
		if(str[p]!='@')
			if(!((str[p]>='A'&&str[p]<='Z')||(str[p]>='a'&&str[p]<='z')||(str[p]>='0'&str[p]<='9')||(str[p]=='_')))return 0;//如果不合法，直接返回 
	return 1;//不然就是合法的
}
bool checktwo(string str)//检查hostname
{
	int sum=0;
	if(str[0]=='.')return 0;//特判如果第一个字符是.
	if(str.size()==0)return 0;//如果是空的
	if(str.size()>=33|| (str.size()==1&&str[0]=='/'))return 0;//特判长度
	for(int p=0;p<str.size();p++)//然后是挨个判断
	{
		if(str[p]=='.'&&str[p+1]=='.')//有相邻的.
			return 0;
		if(str[p]!='.')
			if(!((str[p]>='A'&&str[p]<='Z')||(str[p]>='a'&&str[p]<='z')||(str[p]>='0'&str[p]<='9')||(str[p]=='_')))return 0;
	}
	return 1;
}
bool checkthree(string str)//检查resource
{
	if(str[0]=='/'&&str.size()==1)return 0; //特判只有/的情况
	for(int p=0;p<str.size();p++)//挨个判断
		if(str[p]!='/')
			if(!((str[p]>='A'&&str[p]<='Z')||(str[p]>='a'&&str[p]<='z')||(str[p]>='0'&str[p]<='9')||(str[p]=='_')))return 0;
	return 1;//返回
}
int main()
{
	string str;
	getline(cin,str);
	if(str.find('@')==string::npos)//如果连@都没有，肯定直接输出
	{
		cout<<"NO"<<endl;
		return 0;
	}
	string so1=str.substr(0,str.find('@')+1);//username字段
	string so2=str.substr(str.find('@')+1,str.find('/')-str.find('@')-1);//hostname字段
	string so3=((str.find('/')!=string::npos)?(str.substr(str.find('/'),str.size()-str.find('/'))):(""));//resource
	if(checkone(so1)&&checktwo(so2)&&checkthree(so3)&&str[str.size()-1]!='.'&&so1.size()+so2.size()+so3.size()==str.size())//最后一个字符不能是.
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
}
```

---

## 作者：yzx72424 (赞：2)

这是一道神模拟题..(￣▽￣)／
我打了2h

对于每一块分别处理，如果不符合要求直接NO，最后输出YES即可。

坑点：

1.没有第二部分

2.把 . / @ 计入到字符长度中

3.把判断时的 _ 打成 - (可能只有本蒟蒻犯这么傻的问题)

程序中p,pp,ppp记录长度,ok是输出yes,ko是输出no,

优化:总长度大于70直接ko

```
#include<bits/stdc++.h>
using namespace std;
#define ok {printf("YES");return 0; }
#define ko {printf("NO");return 0; }
char s[205];
int pd(char c){
	if((c>='0'&&c<='9')||(c>='A'&&c<='Z')||(c>='a'&&c<='z')||c=='_')return 1;
	return 0;
}
int main(){
    scanf("%s",s);
    int n=strlen(s),p=0,pp=0,ppp=0;
    if(n>70)ko
	while(p<n&& s[p]!='@')p++;
	if(p==n)ko
	if(p<1||p>16)ko
	for(int i=0;i<p;i++)if(!pd(s[i]))ko
	 pp=p+1;
	while(p<n&&s[p]!='/')p++;
	if(p-pp<1||p-pp>32)ko
	for(int i = pp; i < p; i++){
	if(s[i]=='.') {
			if(ppp<1||ppp>16)ko  
            ppp= 0;
		 }	
	else{
		 if(!pd(s[i]))ko  
		 ppp++;
		}
	}
	if(ppp<1||ppp>16)ko 
	if(p < n){
        ppp= 0;
		for(int i = p+1; i < n; i++){
				if(s[i]=='/'){
				  if(ppp<1 ||ppp>16)ko  
                  ppp = 0;
                }
				else{
				   if(!pd(s[i]))ko 
                     ppp++;
                }
       }
	   if(ppp<1||ppp>16)ko  
	   }
	ok  
}
```



---

## 作者：LYqwq (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF21A)
# 题目大意
给定一个地址，由 `<username>`，`<hostname>` 和 `<resource>` 三个字符串组成。地址结构：`<username>@<hostname>/<resource>`。其中 `/<resource>` 可省略。  
- 对于 `<username>`，约束如下：  
对于每个字符，只允许大写，小写字母，数字和下划线。  
其长度应在 $1$ 到 $16$ 之间。
- 对于 `<hostname>`，约束如下：  
可用 `.` 分隔成多段，每段约束同 `<username>`。  
总长度应在 $1$ 到 $32$ 之间。
- 对于 `<resource>`，约束同 `<username>`

# 思路
~~众所周知，CF题没有一道不坑的。~~  
我们直接输入整个字符串 $s$，并拆成三个字符段，每个字符串用一个新的 $string$ 来存。分别命名为 $u,h,r$。  
## 拆分字段
如何拆分呢？  
我们先定位符号 `@` 的位置和 `/` 的位置，用 $string$ 自带的 $find$ 函数。$find$ 函数返回字符在字符串中的下标，如果没找到，返回 $string::npos$ 这个值。因此可以很方便地定位符号。
再使用 $string$ 的 $substr$ 函数截取字符串，传入两个参数：起始下标和截取字符个数。
- `<username>` 字段要从 $0$ 开始截取到符号 `@` 的位置，所以要截取 `@` 符号下标个字符，所以这个字段就是 $s.substr(0,s.find('@'))$。
- `<hostname>` 字段要从 $s.find('@')+1$ 处开始截取，我们假设有 `resource` 字段，这个字段开始下标为 $s.find('/')+1$，减去 $s.find('@')+1$ 就是要截取的字符个数了，是不是？那么这个字段就是 $s.substr(s.find('@')+1,s.find('/')-(find('@')+1))$ 了。  
那如果没有 `resource` 字段呢？那 $s.find('/')$ 就是 $string::npos$ 了啊，是不是要加个判断？其实不需要！$string::npos$ 的取值是一个较大的数，减去 $find('@')+1$ 后依然很大，会超出范围。但是，万能的 $STL$ 帮了我们，$substr$ 函数如果发现你要截取的字符超出范围，那么它自动截取到最后一个，刚好就是 `<hostname>` 字段了！
- `<resource>` 字段很简单，先判断是否有这个字段，也就是 $s.find('/')!=string::npos$ 时说明有这个字段。起始下标为 $s.find('/')+1$，截取字符个数自然是到末尾了，也就是 $s.size()-(s.find('/')+1)$ 了。这个字段就是 $s.substr(s.find('/')+1,s.size()-(s.find('/')+1))$。

为了节省时间，使用 $sz$ 存储 $s.size()$，用 $fd1$ 存储 $s.find('@')$，用 $fd2$ 存储 $s.find('/')$。

拆分代码如下：
```cpp
u=s.substr(0,fd1); // username 串
h=s.substr(fd1+1,fd2-(fd1+1)); // hostname 串
if(fd2!=string::npos){ // 如果有 resoure，就取。r 默认为空
    r=s.substr(fd2+1,sz-fd2);
}
```

## 判断不规范情况
接下来，我们定义三个函数，分别判断三个字符串是否合法，如果不合法，直接在函数内输出并结束程序即可，函数都调用完后如果一直没退出程序，说明一切正常，输出 `YES` 即可。  
这三个字段分别有什么限制呢？也就是函数中如何判断呢？  
- `<username>` 字段：
  - 需要判断长度，长度小于 $1$ 时，说明字段为空，直接判断长度是否为 $0$ 即可，由于下标从 $0$ 开始，结束下标最多是 $15$，所以判断 $u.size()>=16$ 就行了。
  - 字段中只允许大写，小写字母，数字和下划线，直接遍历一遍寻找违规字符即可。
  - 代码：
    ```cpp
    void username(){ // 判断 username 是否合法
            int l=u.size(); // l 记录长度，因为多次求长度，所以多开一个变量
            if(l==0 || l>=16) N; // 判断长度是否超限
            for(int i=0; i<l; i++){ // 遍历一遍，寻找是否有不允许字符
                if(!(u[i]>='A' && u[i]<='Z' || 
                u[i]>='a' && u[i]<='z' || 
                u[i]>='0' && u[i]<='9' || 
                u[i]=='_')) N;
            }
        }
    ```
- `<hostname>` 字段：
  - 第一位不能为 `.`，等于判断第一个被 `.` 分割的段是否为空。
  - 长度同 `<username>` 字段，不能为 $0$ 或大于等于 $32$，但是如果判断 $s.size()>=32$ 会 $WA$，改成 $33$ 就行了，看上去是要算入 `@` 符号。
  - 遍历一遍查找违规字符，前提是当前这个字符不是 `.`，那么我们就要先判断当前字符是 `.` 的情况，如果是这样，那么下一位就不能是 `.`，因为每段长度不能为 $0$。还有一个问题：判断分割字段为空时，也就是是否有连续两个 `.` 时，可能越界。我们可以在主函数中判断一下，这里暂时不解释。
  - 代码：
    ```cpp
    void hostname(){ // 判断 hostname 是否合法
            int l=h.size(); // 同 username()，记录长度
            // 第一项为 '.'，长度超限或为 0，都不行
            // P.S. 长度好像要算 '@' 符号qwq
            if(h[0]=='.' || l==0 || l>=33) N;
            for(int i=0; i<l; i++){
                // 因为主函数中已经确保最后一位不是 '.' 所以不会越界。照样找一遍不允许字符
                if(h[i]=='.' && h[i+1]=='.' || // 每一段不能为空，也就是不能有相邻的 '.'
                h[i]!='.' && // 否则可以有 '.'，不等于 '.' 时才判断是否有不允许字符
                !(h[i]>='A' && h[i]<='Z' || 
                h[i]>='a' && h[i]<='z' || 
                h[i]>='0' && h[i]<='9' || 
                h[i]=='_')) N;
            }
        }
    ```
- `<resource>` 字段：
  - 如果长度为 $0$，则代表没有该字段，返回即可，注意不是非法情况！
  - 最后一项不能为 `/` 或 `.`。
  - 算上字符 `/`，长度不应大于等于 $17$，为空情况前面已经判断了，所以无需判断。
  - 遍历一遍查找不规范字符，同 `<username>` 字段。
  - 代码：
    ```cpp
    void resoure(){  // 判断 resoure 是否合法
            int l=r.size();
            if(!l) return; // 没有 resoure 字段，直接返回
            // 最后一项为 '/' 或 '.' 都不行
            if(r[l-1]=='/') N;
            if(l>=17) N; // 算上 '/' 字符的长度不能大于等于 17
            // 其余和 username() 一样，不再解释
            for(int i=0; i<l; i++){
                if(!(r[i]>='A' && r[i]<='Z' || 
                r[i]>='a' && r[i]<='z' || 
                r[i]>='0' && r[i]<='9' || 
                r[i]=='_')) N;
            }
        }
    ```
- 主函数中：
  - 首先，如果没有 `@` 字符肯定不行。
  - 不管有没有 `<resource>`，最后一位都不能为 `.` 字符。
  - 如果有 `<resource>` 字段，整个字段不能只有一个 `/` 字符。
  - 代码：
    ```cpp
    int main(){
            cin >> s;
            // 初始化长度，'@' 符位置和 '/' 符位置
            sz=s.size(),fd1=s.find('@'),fd2=s.find('/');
            // 没有 '@' 符情况和最后一位为 '.' 的情况非法
            if(fd1==string::npos || s[sz-1]=='.') N;
            u=s.substr(0,fd1); // username 串
            h=s.substr(fd1+1,fd2-(fd1+1)); // hostname 串
            if(fd2!=string::npos){ // 如果有 resource，就取，r 默认为空
                if(s.substr(fd2,sz-fd2)=="/") N; // 判断 resource 只有 '/' 的情况
                r=s.substr(fd2+1,sz-fd2);
            }
            // 判断各个字段是否有违规，只要找到了就直接输出并退出程序
            username(),hostname(),resoure();
            puts("YES"); // 都没找到，ok
            return 0;
        }
    ```

好了，只要上面这些都注意到了，这道~~毒瘤~~题也就圆满 $AC$ 了qwq。

# 代码
```cpp
#include <iostream>
#define N puts("NO"),exit(0) // 处理非法情况，只要非法就结束程序(其实是偷懒doge)
using namespace std;
int sz,fd1,fd2; // sz 存原串长度，fd1 存 '@' 符号的位置，fd2 存 '/' 符号的位置
string s,u,h,r; // 分别为：原串，username 串，hostname 串，resource 串

void username(){ // 判断 username 是否合法
    int l=u.size(); // l 记录长度，因为多次求长度，所以多开一个变量
    if(l==0 || l>=16) N; // 判断长度是否超限
    for(int i=0; i<l; i++){ // 遍历一遍，寻找是否有不允许字符
        if(!(u[i]>='A' && u[i]<='Z' || 
        u[i]>='a' && u[i]<='z' || 
        u[i]>='0' && u[i]<='9' || 
        u[i]=='_')) N;
    }
}

void hostname(){ // 判断 hostname 是否合法
    int l=h.size(); // 同 username()，记录长度
    // 第一项为 '.'，长度超限或为 0，都不行
    // P.S. 长度好像要算 '@' 符号qwq
    if(h[0]=='.' || l==0 || l>=33) N;
    for(int i=0; i<l; i++){
        // 因为主函数中已经确保最后一位不是 '.' 所以不会越界。照样找一遍不允许字符
        if(h[i]=='.' && h[i+1]=='.' || // 每一段不能为空，也就是不能有相邻的 '.'
        h[i]!='.' && // 否则可以有 '.'，不等于 '.' 时才判断是否有不允许字符
        !(h[i]>='A' && h[i]<='Z' || 
        h[i]>='a' && h[i]<='z' || 
        h[i]>='0' && h[i]<='9' || 
        h[i]=='_')) N;
    }
}

void resource(){  // 判断 resource 是否合法
    int l=r.size();
    if(!l) return; // 没有 resource 字段，直接返回
    // 最后一项为 '/' 或 '.' 都不行
    if(r[l-1]=='/') N;
    if(l>=17) N; // 算上 '/' 字符的长度不能大于等于 17
    // 其余和 username() 一样，不再解释
    for(int i=0; i<l; i++){
        if(!(r[i]>='A' && r[i]<='Z' || 
        r[i]>='a' && r[i]<='z' || 
        r[i]>='0' && r[i]<='9' || 
        r[i]=='_')) N;
    }
}

int main(){
    cin >> s;
    // 初始化长度，'@' 符位置和 '/' 符位置
    sz=s.size(),fd1=s.find('@'),fd2=s.find('/');
    // 没有 '@' 符情况和最后一位为 '.' 的情况非法
    if(fd1==string::npos || s[sz-1]=='.') N;
    u=s.substr(0,fd1); // username 串
    h=s.substr(fd1+1,fd2-(fd1+1)); // hostname 串
    if(fd2!=string::npos){ // 如果有 resource，就取，r 默认为空
        if(s.substr(fd2,sz-fd2)=="/") N; // 判断 resource 只有 '/' 的情况
        r=s.substr(fd2+1,sz-fd2);
    }
    // 判断各个字段是否有违规，只要找到了就直接输出并退出程序
    username(),hostname(),resoure();
    puts("YES"); // 都没找到，ok
	return 0;
}
```

---

## 作者：Ag2WO4 (赞：1)

## 解题方法
这是一道模拟题，所以按照题目要求判定即可。

**以下步骤，如果其中有任何一步出现不符合题意的情况，输出 ```NO``` ，否则输出 ```YES``` 。**

首先切分拿到的字符串。这个字符串必要的要素是 ```@``` ，所以先判定有没有它。

如果有，接下来，判断第一个 ```@``` 之前子串（对应 <username> ）的长度是否合法，判断子串中每一个字符是否在题目给定的范围内。

接下来，判断 ```@``` 之后有没有 ```/``` （即有没有 <resource> ）。如果有，第一个 ```/``` 之前的是 <hostname> ，之后的是 <resource> ；如果没有， ```@``` 之后的子串全是 <hostname> 。

对于 <resource> ，判断方法和 <username> 完全相同。对于 <hostname> ，先判断总长度（是带 ```.``` 的完整子串总长度）是否合法，再以 ```.``` 进行切分，对所有小子串分别判断，判断方式同 <username> 。
## 参考代码
用 ```def``` 语句和 ```exit()``` 函数做了简化。
```python
def r():
    print('NO')
    exit()
a=input().strip()
if '@' not in a:
    r()
#只用判定有没有'@'就行，如果多出来'@'到后面会因为不是u的子串自动淘汰
b,u='','1234567890qwertyuiopasdfghjklzxcvbnnmQWERTYUIOPASDFGHJKLZXCVBNM_'
for i in a:
    if i=='@':
        break
    if i not in u:
        r()
    b+=i
if len(b) not in range(1,17):
    r()
a=a[len(b)+1:]
c=0
if '/' in a:
    a,b=a.split('/',1)
    c=1
#和'@'同理，不必担心有多个'/'的情况
if len(a) not in range(1,33):
    r()
x=a.split('.')
for i in x:
    if len(i) not in range(1,17):
        r()
    for j in i:
        if j not in u:
            r()
if c:
    if len(b) not in range(1,17):
        r()
    for i in b:
        if i not in u:
            r()
print('YES')
```

---

## 作者：hanyuchen2019 (赞：1)

### 2021-1-19：改了亿点东西
### [原题传送门](https://www.luogu.com.cn/problem/CF21A)

毒瘤模拟。 

首先，这题的坑点：

1. 没有判断字符串长度；
2. 没有判断顺序错误（乱入）的分隔符（`@ . /`）；
3. 没有判断末尾字符；
4. 没有判断省略部分的情况；
5. 把 `@ . /` 算进字符串长度；
6. 低级错误（例如 `string` 越界）。

这道题我的思路是线性的，除判断非法字符外，从头到尾**只扫描一遍**，沿途判断，错误跳出，一直扫描到结尾，输出 `YES`，否则输出 `NO`。

好，讲完了，直接上代码，都在注释里解释 ^_^。
```cpp
#include<iostream>
#include<cstring>
using namespace std;

#define F false//简化代码
#define T true

void print(bool t)//简化代码*2 一个输出函数
{
	if(t)cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	return;
}
bool r(char ch)//简化代码*3 一个判断字符是否全部合法的函数
{
	if( (ch>='A'&&ch<='Z') || (ch>='a'&&ch<='z') || (ch>='0'&&ch<='9') || (ch=='_') )return T;
	else return F;
}
int main()
{
	#define PF {print(false);return 0;}//简化代码*4
	int i=0,cnt=1;//i为现在扫描的位置，cnt为当前字符串长度
	string s;
	cin>>s;

	for(i=0;i<s.length();i++)
            if(!(r(s[i])||s[i]=='@'||s[i]=='.'||s[i]=='/'))PF
            //扫一遍，看是否合法

	if(s.length()>68||r(s[s.length()-1])==false)PF//判断长度&末尾

	for(i=0,cnt=1;i<s.length();i++,cnt++)//‘@’之前的部分
	{
		//cout<<i<<":"<<cnt<<endl;DEBUG
		if(s[i]=='@')
		{
			cnt--;//不算‘@’
			if(cnt=0||cnt>=17)//防抄袭 判断长度
				PF
			else
			{
				i++;
				break;
			}
		}
		else if(s[i]=='.'||s[i]=='/')PF//防其它字符乱入
	}

	if(i==s.length())PF//到底了
	for(cnt=0;i<s.length();i++,cnt++)//‘@’和‘.’中间的部分
	{
		if(s[i]=='.')//同理
		{

			if(cnt==0||cnt>=17||i==s.length())PF
			else
				cnt=-1;
		}
		else if(s[i]=='/')//发现下一阶段字符
		{
			if(cnt==0||cnt>=17||i==s.length()) PF//判断长度+防止出现‘.’‘/’贴合
			else
			{
				i++;//进入第三部分
				break;
			}
		}
		else if(s[i]=='@') PF
	}
	
	if(i==s.length())//到底了
	{
		if(i=='.')PF
		else print(T);
		return 0;
	}

	for(cnt=1;i<s.length();i++)//处理掉结尾
	{
		if(s[i]=='.'&&(cnt==0||cnt>=17))PF
	}
	if(cnt==0||cnt>=17)PF
	
	if(i==s.length())//到底了
	{
		print(T);
		return 0;
	}
	for(cnt=1;i<s.length();i++,cnt++)//‘/’的部分
	{
		if(s[i]=='/')
		{
			if(cnt==0||cnt>=17||i==s.length())PF
			else
				cnt=0;
		}
		else if(s[i]=='@'||s[i]=='.')PF
	}
	print(T);//符合所有要求，输出！
	return 0;//ACed!
}
```
希望大家喜欢这篇题解 ^_^！ Bye~

---

## 作者：Chinshyo (赞：0)

# 思路
这道题完全是一道字符串模拟的题。他的重点就在于我们如何把整个字符串 $s$ 分割成 $<username>$ , $<hostname>$ 以及 $[/resource]$ 我们不妨直接将整个输入进来的字符串 $s$ 用循环扫一遍，找到 $“@”$所在的位置。这就找到了 $<username>$。接着，我们可以将余下的部分扫一遍，如果发现有 $“.”$ ，那么就要看前一部分的长度。由于所有 $<hostname>$ 之间的**字串最长不得超过16**，所以我们就要判断前一段的字串是否合法。在结束时也要判断**整个长度不得超过32**。
# "蒟"例说明
 例如本题的样例1，我们就可以分割成这样
  ```
mike|@|codeforces.com
```
 当然，也不排除题目中没有的情况：
 ```
lbwnb|@|.com
	     ↑	
```
 $<hostname>$是**不能直接以 $ . $ 开头的**

# 代码
 ```
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin >> s;
	int nw = 0;//hostname的开头元素-1
	while(s[nw]!='@'){
		if(isalpha(s[nw]) || isalnum(s[nw]) || s[nw] == '_') nw++;
		else{//不合法
			cout << "NO" << endl;
			return 0;
		}
	}
	if(nw - 1 > 16 || nw - 1 < 1){//username长度是否合法
		cout << "NO" << endl;
		return 0;
	}
	if(s.size() - nw + 1 <= 0){//hostname长度是否合法
		cout << "NO" << endl;
		return 0;
	}
	
	int cnt = 0, acnt = 0, sta = -114514;
	for(int i = nw + 1; i < s.size(); i++){
		cnt++;
		if(s[i] == '.'){
			if(cnt <= 1 || cnt > 16){
				cout << "NO" << endl;
				return 0;
			}
			cnt = 0;
		} else if(isalnum(s[i]) || isalpha(s[i]) || s[nw] == '_'){
			continue;
		} else if(s[i] == '/'){
			if(cnt < 0 || cnt > 16){
				cout << "NO" << endl;
				return 0;
			} else {
				sta = i + 1;
				break;
			}
		} else {
			cout << "NO" << endl;
			return 0;
		}
	}
	if(sta != -114514)//确实有[/resource]
		for(int i = sta; i < s.size(); i++){
			if(isalnum(s[i]) || isalpha(s[i]) || s[nw] == '_') continue;
			else {
				cout << "NO" << endl;
				return 0;
			}
		}
	
	cout << "YES" << endl;
	return 0;
} 
```


---

## 作者：hmzclimc (赞：0)

这是一道模拟题,思路很简单,但是坑很多。


------------


思路：遍历整个字符串,判断每个部分是否合法。


------------


坑点: 

1 两个分隔符不能挨在一起

2 @ / 不算到长度里
     
3 <hostname> 和 <username> 是必须有的 
  

------------

  
完整[AC](https://www.luogu.com.cn/record/42981518)代码: 
```cpp
#include<iostream>
#include<string>
using namespace std;
string s;
bool b(char x){//判断字符是否合法 
	if((x>='A'&&x<='Z')||(x>='a'&&x<='z')||(x>='0'&&x<='9')||(x=='_')){
		return true;
	}
	return false;
}
int main(){
	cin>>s;
	if(s[0]=='@'){
		cout<<"NO";
		return 0;
	}
	bool flag1=true,flag2=false,flag3=false,flag_last=false;//用于判断是在 <username> , <hostname> , <resource>中的哪一部分 
	int tot1=0,tot2=0,tot_dit=0;//用于统计长度是否太长 
	if(s.find("@")==string::npos){//如果字符串里没有@,那么说明它是一定不合法的 
		cout<<"NO";
		return 0;
	} 
	for(int i=0;i<s.size();i++){//遍历每一个字符 
		if(flag1){//  <username> 
			if(s[i]=='@'){//进入<hostname>部分 
				if(i==0){
					cout<<"NO";
					return 0;
				}
				flag2=true;
				flag1=false;
				continue;
			}else{
				tot1++;
				if(tot1>16){//判断是否超长 
					cout<<"NO";
					return 0;
				}
				if(!b(s[i])){//判断是否合法 
					cout<<"NO";
					return 0;
				}
			}
		}else if(flag2){//<hostname> 
			if(s[i]=='/'){// 进入<resource>部分 
				flag3=true;
				flag2=false;
				if(s[i-1]=='.'){//注意特判 
					cout<<"NO";
					return 0;
				}
				if(s[i-1]=='/'){//注意特判 
					cout<<"NO";
					return 0;
				}
				continue;
			}else{
				tot2++;
				tot_dit++;
				if(s[i]=='.'){
					tot_dit=0;
					if(s[i-1]=='@'){
						cout<<"NO"; 
						return 0;
					}
					if(s[i+1]=='.'){
						cout<<"NO"; 
						return 0;
					}
					if(tot2==1){//<hostname>部分 的第一个字符不能为 . 
						cout<<"NO";
						return 0;
					}
				}else{
					if(tot2>32){//判断是否超长 
						cout<<"NO";
						return 0;
					}
					if(tot_dit>16){//判断是否超长
						cout<<"NO";
						return 0;
					} 
					if(!b(s[i])){//判断是否合法 
						cout<<"NO";
						return 0;
					}
				} 
			}
		}else if(flag3){// <resource>
			if(s[i-1]=='@'){
				cout<<"NO";
				return 0;
			}
			if(s[i]=='/'){
				continue;
			}else{
				if(!b(s[i])&&s[i]!='.'){//判断是否合法 
					cout<<"NO";
					return 0;
				}
			}
		}
	}	
	if(s[s.size()-1]=='/'||s[s.size()-1]=='@'||s[s.size()-1]=='.'){//注意特判字符串的末尾 
		cout<<"NO";
		return 0;
	}
	cout<<"YES";
    return 0;
}
```




---

## 作者：RBI_GL (赞：0)

### 题意：

给定一个字符串，问是否满足这个格式：

$<username>@<hostname>[/resource]$

其中 $<username>$ 是一个只包含 字母或数字或下划线 的长度为 $1 - 16$ 的字符串。
  
  
 $<hostname>$ 是一个由 若干个以字符 $“ . ”$ 进行分隔的单词 组成的长度为 $1 - 32$ 的字符串，其中单词的限制和 $<username>$ 一样。
  
  
 $resource$ 的限制与 $<username>$ 一样  $[/resource]$ 的意思是 $<hostname>$ 后面可以跟多个 $/resource$
  
 **注意**：$[/resource]$ 可以省略。
  
  
-------------
  
### 思路：
  
  
遍历字符串, 统计相关信息。

**注意：**
  
  
- 根据题目意思， $@$ 是一定要有的, $@$ 前和 $@$ 后必须至少有一个合法的字符字符。
- 例如 $<username>@h1.h2.h3/r1$  字符串 $h1,h2,h3,r1$ 均不能为空。
  
-----------
  
  
### Code：
  
```cpp
#include <bits/stdc++.h>
using namespace std;
char str[1000];
char s[100][100];

int main() {
	while(scanf("%s", str) != EOF) {
		int len = strlen(str);
		bool f1 = false;
		bool f2 = true;
		int k = 0, i;
		for( i=0; i<len; i++ ) {
			if(str[i] == '@') {
				f1 = true;
				break;
			} 
			else {
				if(!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') ||(str[i]>='0'&&str[i]<='9')|| str[i] == '_')) {
					f2 = false;
					break;
				} 
				else k++;
				if(k > 16) {
					f2 = false;
					break;
				}
			}
		}
		if(f1 == false || f2 == false || k < 1) {
			printf("NO\n");
			continue;
		}
		k = 0;
		int k2 = 0;
		for( i=i+1; i<len; i++ ) {
			if(str[i] == '/') {
				break;
			} else if(str[i] == '.') {
				if(k2 == 0) {
					f2 = false;
					break;
				}
				k2 = 0;
				continue;
			} else {
				if(!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')||(str[i]>='0'&&str[i]<='9') || str[i] == '_')) {
					f2 = false;
					break;
				} else k++, k2++;
				if(k2 > 16 || k > 32) {
					f2 = false;
					break;
				}
			}
		}
		if(f2 == false || k2 == 0 || k == 0) {
			printf("NO\n");
			continue;
		}
		if(i == len) {
			printf("YES\n");
			continue;
		}
		k = 0;
		for( i=i+1; i<len; i++ ) {
			if(str[i] == '/') {
				if(k == 0) {
					f2 = false;
					break;
				}
				k = 0;
				continue;
			} 
			else {
				if(!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')||(str[i]>='0'&&str[i]<='9') || str[i] == '_')) {
					f2 = false;
					break;
				} 
				else k++;
				if(k > 16) {
					f2 = false;
					break;
				}
			}
		}
		if(f2 == false || k == 0) cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}
	return 0;
}
```

---

## 作者：Need_No_Name (赞：0)

# Solution For CF21A

## 题意：

给定一个地址，判断是否合法（合法输出 'YES' ,否则 'NO'）

一个地址由 $username$ , @ , $hostname$ 以及可有可无的 $[/resource]$ 构成
  
**1.**$username$ 仅能由数字，大小写字母，下划线构成
 
**2.**$username$ 和 $hostname$ 被一个 '@' 隔绝，一个字符串内只能有一个 '@'
  
**3.**$hostname$ 仅能由一个像网址一样的东西一样，为```xxx.xxx.xxx.xxx```之类的构成, 能有多个 '.' 隔绝，而 'x' 的部分也像 $username$ 部分一样。需要注意， $hostname$ 里面**必须**有 '.' 。  

**4.**$resource$ 由一个 '/' 构成，只能有一个 '/' ，其余部分和 $username$ 部分相同。
  
## 思路

我们可以按段去判断以上四个条件。

先找 '@' 符号，分解出 $username$ 和 $hostname$ 与 $resource$ ，再分段检查一下即可。

只是大模拟调起来很累人以及要注意细节，做起来还是挺费劲的（这道题磨掉了lz两个小时...）

## 代码

```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
const int N = 105;
char ch[N];
int len;
int atnum = 0;
int atpos = -1;
int hostnamelen = 0;
inline bool atcheck()
{
	for(int i = 1; i <= len; i++)
	{
		if(ch[i] == '@')
		{
			atnum++;
			if(atpos == -1) atpos = i;
		}
	}
	if(atnum >= 2) return false;
	else if(atnum == 0 && atpos == -1) return false;
	else return true;
}
inline bool usernamecheck()
{
	if((atpos - 1) >= 17 || (atpos - 1) < 1)
	{
		return false;
	}
	for(int i = 1; i < atpos; i++)
	{
		if(!((ch[i] >= 'A' && ch[i] <= 'Z') || (ch[i] >= 'a' && ch[i] <= 'z') || (ch[i] >= '0' && ch[i] <= '9') || (ch[i] == '_'))) return false;
	}
	return true;
}
inline bool hostnamecheck()
{
	if(ch[atpos + 1] == '.') return false;
	if(atpos == len) return false;
	int cnt = atpos + 1;
	int tmp = 0;
	while(ch[cnt] != '/' && cnt <= len)
	{
		tmp++;
		cnt++;
	}
	if (tmp > 32 || tmp < 1) return false;
	if(ch[cnt - 1] == '.') return false;
	if(cnt >= len) cnt = len;
	hostnamelen = tmp;
	for(int i = atpos + 1; i < cnt; i++)
	{
		if(ch[i] != '.')
		{
			if(!((ch[i] >= 'A' && ch[i] <= 'Z') || (ch[i] >= 'a' && ch[i] <= 'z') || (ch[i] >= '0' && ch[i] <= '9') || (ch[i] == '_')))
			{
				return false;
			}
		}
		if(ch[i] == '.' && ch[i + 1] == '.') return false;
	}
	return true;
}
inline bool resourcecheck()
{
	if(atpos + hostnamelen >= len) return true;
	if(len - (atpos + hostnamelen) == 1) return false;
	int begn = atpos + hostnamelen + 1;
	for(int i = begn; i <= len; i++)
	{
		if(ch[i] != '/')
		{
			if(!((ch[i] >= 'A' && ch[i] <= 'Z') || (ch[i] >= 'a' && ch[i] <= 'z') || (ch[i] >= '0' && ch[i] <= '9') || (ch[i] == '_'))) return false;
		}
		else
		{
			if (i < len && i != begn) return false;
		}
	}
	return true;
}
signed main()
{
	cin >> (ch + 1);
	len = strlen(ch + 1);
	if(len > 70)
	{
		cout << "NO" << endl;
		return 0;
	}
	bool f1 = atcheck();
	bool f2 = usernamecheck();
	bool f3 = hostnamecheck();
	bool f4 = resourcecheck();
	if(!f1 || !f2 || !f3 || !f4)
	{
		cout << "NO" << endl;
		return 0;
	}
	cout << "YES" << endl;
	return 0;
}
```


---

