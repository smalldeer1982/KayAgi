# Login Verification

## 题目描述

登录名是由小写和大写拉丁字母、数字和下划线符号“_”组成的任意序列。
如果登录名与已经存在的登录名类似，则禁止注册。
如果我们可以通过以下类型的操作组成的序列将S转化成T，则认为S,T是类似的。
- 将小写字母转换为大写字母，将大写字母转换为小写字母
- 将字母“O”更改为数字“0”,将数字“0”更改为字母“O”
- "1""l""L"相互转化
例如，
登录名«codeforces»和«codefwrces»，
«oo0oo00oo0oo0oo0oo_lol»和«oo0oo0oo0oo0oo0oo0oo0oo0oo_1oo»是类似的，
而«codeforces»和«code_forces»则不是。
给你一个登录名的列表,其中没有两个类似的登录名。
检查新登录名是否和已有登录名类似。

------------

## 样例 #1

### 输入

```
1_wat
2
2_wat
wat_1
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
000
3
00
ooA
oOo
```

### 输出

```
No
```

## 样例 #3

### 输入

```
_i_
3
__i_
_1_
I
```

### 输出

```
No
```

## 样例 #4

### 输入

```
La0
3
2a0
La1
1a0
```

### 输出

```
No
```

## 样例 #5

### 输入

```
abc
1
aBc
```

### 输出

```
No
```

## 样例 #6

### 输入

```
0Lil
2
LIL0
0Ril
```

### 输出

```
Yes
```

# 题解

## 作者：Miller2019 (赞：6)

思路：做一个参数为 $\ string$ ，返回值为 $\ string$ 的函数，用于将一个字符串按照规则转化。我们先读入要注册的用户名，转化之后存储下来。然后读入已有的用户名，转化后推入 $\ vector$ 。最后使用 $\ find$ 函数，检查是否重复。

```cpp
#include<cstdio>
#include<cctype>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std; 
string change(string str)
{
	string ans=str;int len=str.size();
	for(register int t=0;t<len;t++)
	{
		ans[t]=tolower(ans[t]); //位于<ctype.h> 偷吻件中，可以把一个字符转换成小写。
		switch(ans[t]) 
		{
			case 'o':
				ans[t]='0';break; //如果是 'o' ，变成 '0' 。
			case 'l':
				ans[t]='1';break; //如果是 'l' ，变成 '1' 。
			case 'i':
				ans[t]='1';break; //如果是 'i' ，变成 '1' 。
		}
	}
	return ans; //返回修改后的字符串。
}
vector<string>data;	//建立名叫 "data" 的 vector ，存储的元素类型是 string 。
string reg,old;int n;
int main()
{
    ios::sync_with_stdio(0);	//三行读入输出优化
    cin.tie(0);
    cout.tie(0);
	cin>>reg>>n;
	data.clear();	//清空 vector ，不写也行...好像加上这句更快...
	while(n--)
	{
		cin>>old;
		data.push_back(change(old));	//推入转化后的用户名。
	}
	cout<<(find(data.begin(),data.end(),change(reg))==data.end()?"Yes":"No");	//查询是否有跟有注册的用户名重复的。如果没有找到，则会返回 vector 结束的位置，输出即可。
	return 0;	//Don't forget this。
}
```

亲测：903ms /  248.00KB ，最优解。


蒟蒻的第 13 篇题解。

---

## 作者：pikabi (赞：2)

~~我只是来抢饭碗的~~

### 一道小水题，注意一下string可以直接比大小的！！模拟一下再比较就好了~~不需要map~~

一些细节见代码QAQ

```cpp
#include <iostream>
#include <cstdio>
#include <cctype> //toupper 和 islower的头文件

using namespace std;

string s, ss;

int n, fl;

int main(){
	getline(cin, s);
	scanf("%d\n",&n);
	for(int i = 0; i < s.length() ; i++)//模拟
	if(s[i] == '1' || s[i] == 'l'|| s[i] == 'i' || s[i] == 'I') s[i] = 'L';//建议弄个小函数套一下否则手贱多打一个s容易WA(比如我）
	else if(islower(s[i])) s[i] = toupper(s[i]);//islower判断大小写， toupper小写变大写
	else if(s[i] == '0') s[i] = 'O';
	for(int i = 1;i <= n; i++){
		getline(cin,ss);
		for(int j = 0; j < ss.length(); j++)//同上
		if(ss[j] == '1' || ss[j] == 'l' || ss[j] == 'i' || ss[j] == 'I') ss[j] = 'L';
		else if(islower(ss[j])) ss[j] = toupper(ss[j]);
		else if(ss[j] == '0') ss[j] = 'O';
		if(ss == s) fl = 1;//直接比较
	}
	if(fl) printf("No\n");
	else printf("Yes\n");
	return 0;
} 
```
#### 国庆快乐鸭ヾ(=･ω･=)o

---

## 作者：Sayori (赞：2)

这道题就是一道~~简单的~~字符串的题目。  
二话不说，直接上代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, f = 0;
string str;
map <string, bool> mp;//这个map用来判重 
void change(string &s){
    int len = s.size();// 
    for(int i = 0; i < len; ++i){
    	s[i] = toupper(s[i]);//toupper这个函数就是把小写字母变为大写字母 
		if(s[i] == '0') s[i] = 'O';
		if(s[i] == 'L') s[i] = '1';
		if(s[i] == 'I') s[i] = '1';//将同一个变换规则的所有字符变为一个相同的字符 
	}	
}
int main(){
	cin >> str;
	change(str);
	mp[str] = 1;
	cin >> n;
	for(int i = 1; i <= n; ++i){
		cin >> str;
		change(str);
		if(mp[str] == 1)//在这个字符串还没放入map中，已经出现相同的，则有重复，标记f 
			f = 1;
		mp[str] = 1;//将str放入map中 
	}
	if(f == 0) cout << "Yes";
	else cout << "No"; 
}
```


---

## 作者：xjngbnn (赞：0)

### CF928A Login Verification 
~~这道题目其实挺水的~~

蒟蒻的第一篇题解 QWQ

思路：
按照题意模拟，输入一个字符串，将其转换后存储下来，与其他字符串进行比较，如果相同就输出    ```No```,否则就输出  ```Yes```。
```cpp
#include<bits/stdc++.h> //万能头。 
using namespace std;
string check(string a) { //定义一个函数帮我们执行相同的步骤。
	int q=a.size(); //q代表a的长度。
	for(int i=0; i<q; i++) { //字符串下标从0开始，所以要从0开始枚举。
		if(a[i]>='a'&&a[i]<='z')
			a[i]-=32; //在ASCLL 码中，小写字母比大写字母大32，所以减去32。
		if(a[i]=='O')
			a[i]='0'; //按照题意模拟，将O转换为0。
		if(a[i]=='I'||a[i]=='L') //注意：这里只能用大写字母！因为前面已经将所有小写字母转换成了大写字母。
			a[i]='1'; //同样按照题意模拟。
	}
	return a;
}
int main() {
	string a,b; //a代表登录名，b代表已有的登录名。
	int n; //n是已有的登录名的数量。
	cin>>a;
	check(a); //将a进行转换。
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>b;
		check(b); //将b进行转换。
		if(a==b) {  //如果a与b相同。
			cout<<"No";
			return 0; //直接结束程序。
		}
	}
	cout<<"Yes"; //如果程序能够运行到这里，就证明这个用户名是不重复的。
	return 0;
}
```


---

## 作者：bigdoge (赞：0)

## 2021.4.27:

不说了，一切尽在代码里……
```
#include <bits/stdc++.h> // 懒人必备万能头
using namespace std; // c++党必备：调用命名空间std
int n;
string username; // 原用户名
bool success=true; // 用于判断是否有相似用户名
inline string check_username(string str){ // 将输入的所有用户名转换

    // 这道题主要的思路就是将所有新输入的用户名转换成单一一种用户名，然后进行比较
    // 字符串可以按照字典序进行比较、排序。
    // 这里就是将所有大写转换为小写、'o'转换为'0'，'l'转换为'1'，'i'转换为'1'。

	string temp_username=str; // 存储初始的用户名
        int temp_len=str.size() // 计算用户名长度
	for(int i=0;i<temp_len;i++){  // 每个字符进行遍历
		temp_username[i]=tolower(str[i]); // 将所有字符转换为小写
		switch(temp_username[i]){ // 使用switch判断特殊情况
			case 'o' : temp_username[i]='0'; // 如果是'o'就转换为'0'
			break;
			case 'l' : temp_username[i]='1'; // 如果是'l'就转换为'1'
			break;
			case 'i' : temp_username[i]='1'; // 如果是'i'就转换为'1'
		}
	}
	return temp_username; // 返回转换后的用户名
}
int main(){
	ios::sync_with_stdio(false); // 优化
	cin.tie(0); // 优化
	cout.tie(0); // 优化
	cin>>username; // 输入初始用户名
	cin>>n; // 输入用户名的数量
	for(int i=1;i<=n;i++){ // 循环输入
		string str; // 临时定义
		cin>>str; // 输入用户名
        //由于这个新用户名没有储存的必要，所以这里就没有用数组
		if(check_username(str)==username){ // 判断
                        //如果成立
			printf("No"); // 输出"No"
			success=false; // 将其改成false
			break; // 退出循环
		}
	}
	if(success) printf("Yes"); // 如果每个用户名都没有问题就输出"Yes"
	return 0; // 完结撒花
}
```
一提交，没对……


------------
## 2021.4.29
昨天考试，所以没有更新……

今天又来看了一遍上面的错误程序，又看了一遍样例。

发现：`username没有经过check_username的洗礼`

于是又有了下面的代码：
```
#include <bits/stdc++.h> // 懒人必备万能头
using namespace std; // c++党必备：调用命名空间std
int n;
string username; // 原用户名
bool success=true; // 用于判断是否有相似用户名
inline string check_username(string str){ // 将输入的所有用户名转换

    // 这道题主要的思路就是将所有新输入的用户名转换成单一一种用户名，然后进行比较
    // 字符串可以按照字典序进行比较、排序。
    // 这里就是将所有大写转换为小写、'o'转换为'0'，'l'转换为'1'，'i'转换为'1'。

	string temp_username=str; // 存储初始的用户名
	for(int i=0;i<temp_username.size();i++){  // 每个字符进行遍历
		temp_username[i]=tolower(temp_username[i]); // 将所有字符转换为小写
		switch(temp_username[i]){ // 使用switch判断特殊情况
			case 'o' : temp_username[i]='0'; // 如果是'o'就转换为'0'
			break;
			case 'l' : temp_username[i]='1'; // 如果是'l'就转换为'1'
			break;
			case 'i' : temp_username[i]='1'; // 如果是'i'就转换为'1'
			break;
		}
	}
	return temp_username; // 返回转换后的用户名
}
int main(){
	ios::sync_with_stdio(false); // 优化
	cin.tie(0); // 优化
	cout.tie(0); // 优化
	cin>>username; // 输入初始用户名
	username=check_username(username); // 就是缺了这个玩意才对不了…… 
	cin>>n; // 输入用户名的数量
	for(int i=1;i<=n;i++){ // 循环输入
		string str; // 临时定义
		cin>>str; // 输入用户名
        //由于这个新用户名没有储存的必要，所以这里就没有用数组
		if(check_username(str)==username){ // 判断
                        //如果成立
			printf("No"); // 输出"No"
			success=false; // 将其改成false
			break; // 退出循环
		}
	}
	if(success) printf("Yes"); // 如果每个用户名都没有问题就输出"Yes"
	return 0; // 完结撒花
}
```

---

## 作者：happybob (赞：0)

~~我有STL妄想症~~

STL大法好！

本题可以用STL的map，string，pair + algorithm中的transform做

将字符串全部转为大写，I，L转为1,0转为O

然后判断是否是重复的

这里注意，第一个读入的字符串也要转换

代码：

```cpp
#include <iostream>//读入输入
#include <utility>//pair，因为有map头文件，可加可不加
#include <map>//map
#include <cctype>//toupper
#include <algorithm>//transform
#include <cstring>//string
using namespace std;

map<string, bool> mp;//定义

string s, x;//定义

int main()
{
    cin >> s;
    transform(s.begin(), s.end(), s.begin(), ::toupper);//转大写
    for(string::iterator it = s.begin(); it != s.end(); ++it)//预处理，用迭代器
    {
        if(*it == '0')
        {
            *it = 'O';
        }
        else if(*it == 'L' || *it == 'I')
        {
            *it = '1';
        }
    }
    mp.insert(pair<string, bool>(s, true));//insert一下
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {//同上
        cin >> x;
        transform(x.begin(), x.end(), x.begin(), ::toupper);
        for(string::iterator it = x.begin(); it != x.end(); ++it)
        {
            if(*it == '0')
            {
                *it = 'O';
            }
            else if(*it == 'L' || *it == 'I')
            {
                *it = '1';
            }
        }
        if(mp[x])
        {
            cout << "No\n";
            return 0;
        }
        mp.insert(pair<string, bool>(x, true));
    }
    cout << "Yes\n";
    return 0;
}
```


---

## 作者：LiteratureCollege (赞：0)

首先要给大家提个醒，这题的翻译有问题，‘i’和‘I’也与‘L’同等，这是可以通过样例观察出来的。知道了这一点后代码就很好些了。

我们将所有的小写字母转化为大写字母，再将所有的‘i,I,l,1’都装换成大写的‘L’，将所有的‘0’都转化成‘O’，就可以直接将字符串进行比对了。

字符串比对可以使用多种方法，比如手写比较，string的stl函数，map等，我这里是手写的比较。

```cpp
#include<bits/stdc++.h> 
using namespace std;
string gy,s[1416];
int n,zjy=1;
bool zyq(string x,string y)//比较字符串 
{
	for(int i=0;i<x.length();i++)
	{
		if(x[i]!=y[i])
		{
			return 0;
		}
	}
	return 1;
}
void k(string &x)//转换函数 
{
	for(int j=0;j<x.length();j++)
	{
		if(x[j]>='a'&&x[j]<='z')
		{
			x[j]-=('a'-'A');
		}
		if(x[j]=='0')
		{
			x[j]='O';
		}
		if(x[j]=='1'||x[j]=='l'||x[j]=='i'||x[j]=='I')
		{
			x[j]='L';
		}
	}
}
int main()
{
	cin>>gy;
	k(gy);//记得注册的用户名也要转换 
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
		k(s[i]);
	}
	for(int i=1;i<=n;i++)
	{
		if(gy.length()!=s[i].length())//长度不相等的话当然不相似 
		{
			continue;
		}
		if(zyq(s[i],gy)==1)
		{
			zjy=0;
			break;
		}
	}
	if(zjy==1)
	{
		cout<<"Yes";
	}
	else
	{
		cout<<"No";
	}
    return 0;
}
```


---

## 作者：hensier (赞：0)

~~这道题的翻译貌似与原文不符（没有加入小写字母$i$的情况）~~

这道题我们可以写一个转换函数，返回值为$string$。

```cpp
string change(string s)
{
    for(int i=0;s[i];i++)//对字符串s的每一个字符进行操作
    {
        s[i]=tolower(s[i]);//直接变小写
        if(s[i]=='o')s[i]='0';//是o就统一变成0
        if(s[i]=='l'||s[i]=='i')s[i]='1';//是l、i就统一变成1
      	//注意！上面三个语句中的s[i]=tolower(s[i]);必须必须必须放在第一位！
    }
    return s;//返回s即可。
}
```

我们对第一个字符串进行处理之后，然后一边输入一边转换。只要有相同的就输出并结束程序。

对于$cin,cout$流，用$ios::sync\_with\_stdio(0);$可以关闭同步，节约一部分时间，与$scanf,printf$的时间相差无几。

你们最爱的无注释无损清晰$AC$代码：

```cpp
#include<iostream>
using namespace std;
string s,t;
string change(string s)
{
    for(int i=0;s[i];i++)
    {
        s[i]=tolower(s[i]);
        if(s[i]=='o')s[i]='0';
        if(s[i]=='l'||s[i]=='i')s[i]='1';
    }
    return s;
}
int n,i;
int main()
{
    ios::sync_with_stdio(0);
    cin>>s>>n;
    while(n--)
    {
        cin>>t;
        if(change(t)==change(s))
        {
            cout<<"No";
            return 0;
        }
    }
    cout<<"Yes";
}
```

---

## 作者：Gavin0576 (赞：0)

~~我也是跟上来混混的，蒟蒻的及其蒟蒻写的题解。~~  
#### map用不着，看看这题的数据暴力都行。。。而且暴力还挺快。。。  
基本思路就是一个一个字符拿出来进行比对，然后一个一个判断。~~没想到程序的运行时间还挺少~~  
详情的见代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>//函数库随便搞
  
using namespace std;
int main(){
	ios::sync_with_stdio(0);//提升cin和cout速度的语句
	char a[60],s[60];cin>>a;
	int n;cin>>n;
	bool f=true;//一会儿用来判断会不会有类似登录名，一开始默认没有，就是这个登录名可行
	for(int i=1;i<=n;i++){
		memset(s,0,sizeof(s));
		cin>>s;
		if(strlen(s)!=strlen(a)) continue;//长度都不一样的直接去掉，长度一样的再进行比较
		for(int j=0;j<strlen(s);j++){
			if(a[j]==s[j]){//如果完全一样那就用不到它的规则了，直接进行下一个比较
					if(j==strlen(s)-1) f=false;
					else continue;	
				}
			if(a[j]!=s[j]){
				if((isupper(a[j])&&tolower(a[j])==s[j])||(islower(a[j])&&toupper(a[j])==s[j])){//isupper判断是不是大写 的函数，是的话就是真，tolower就是大写变小写。islower和toupper自己类推
					if(j==strlen(s)-1) f=false;//到最后一个都是类似的话，那就有类似登录名了，直接f=false；
					else continue;//继续判断
				}
				if((a[j]=='0'||a[j]=='o'||a[j]=='O')&&(s[j]=='0'||s[j]=='o'||s[j]=='O')){//0，o，O的判断
					if(j==strlen(s)-1) f=false;
					else continue;	
				}
				if((a[j]=='1'||a[j]=='i'||a[j]=='I'||a[j]=='L'||a[j]=='l')&&(s[j]=='1'||s[j]=='i'||s[j]=='I'||s[j]=='L'||s[j]=='l')){//1，i，l的判断
					if(j==strlen(s)-1) f=false;
					else continue;	
				}
			break;
			}
		}
	}
	if(f==false) cout<<"No"<<endl;//f=false的话就不行了，说明有类似登录名，输出No
	else cout<<"Yes"<<endl;//反之输出Yes
	return 0;
} 
```


---

## 作者：EtOH_Lewis (赞：0)

第一篇题解......

```
#include<bits/stdc++.h>
using namespace std;
bool same(string a,string b)
{//判断函数
    if(a.size()!=b.size())return false;
    //必须长度一样才有可能相似
    int len=a.size();
    for(int i=0;i<len;i++)//反复求长度浪费时间
    {
        char x=a[i],y=b[i];
        if(abs(x-y)=='A'-'a')return true;
        //大小写
        if((x=='O' && y=='o') || (x=='o' && y=='O'))return true;
        //O-0判断
        char q='1',w='l',e='L';
        //1,l,L判断
        if((x==q || x==w || x==e) && (y==q || y==w || y==e))return true;
        return false;
    }
}
int main()
{
    string a;int n;cin>>a>>n;
    string b[n+1];
    for(int i=1;i<=n;i++)
    {
        cin>>b[i];
        if(same(b[i],a))//如果有一个相似了，就Yes，并且切断，直接return
        {
            cout<<"Yes"<<endl;
            return 0;
        }
    }
    //没有一个相似，No
    cout<<"No"<<endl;
}
```


---

