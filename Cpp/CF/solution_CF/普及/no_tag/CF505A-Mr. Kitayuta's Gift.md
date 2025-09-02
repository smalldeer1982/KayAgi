# Mr. Kitayuta's Gift

## 题目描述

Mr. Kitayuta has kindly given you a string $ s $ consisting of lowercase English letters. You are asked to insert exactly one lowercase English letter into $ s $ to make it a palindrome. A palindrome is a string that reads the same forward and backward. For example, "noon", "testset" and "a" are all palindromes, while "test" and "kitayuta" are not.

You can choose any lowercase English letter, and insert it to any position of $ s $ , possibly to the beginning or the end of $ s $ . You have to insert a letter even if the given string is already a palindrome.

If it is possible to insert one lowercase English letter into $ s $ so that the resulting string will be a palindrome, print the string after the insertion. Otherwise, print "NA" (without quotes, case-sensitive). In case there is more than one palindrome that can be obtained, you are allowed to print any of them.

## 说明/提示

For the first sample, insert 'r' to the end of "revive" to obtain a palindrome "reviver".

For the second sample, there is more than one solution. For example, "eve" will also be accepted.

For the third sample, it is not possible to turn "kitayuta" into a palindrome by just inserting one letter.

## 样例 #1

### 输入

```
revive
```

### 输出

```
reviver
```

## 样例 #2

### 输入

```
ee
```

### 输出

```
eye```

## 样例 #3

### 输入

```
kitayuta
```

### 输出

```
NA
```

# 题解

## 作者：AveMarina (赞：1)

## 使用双指针算法旋转字符串
__考虑一下怎么旋转一个字符串__:
1. $O(n)$从尾扫到头
2. 用STL里的reverse函数
3. $O(log\,n)$每次交换头尾两个字符

这篇题解用的就是第三种方法啦...

__实现原理__:

对于任意非空字符串，其长度必定是奇数或者偶数。我们考虑使用两个指针，一个指向字符串头（左指针），一个指向字符串尾（右指针）。每次交换这两个指针所指的字符，直到这两个指针相撞为止。__对于奇数长度的字符串中间的字符一定是左指针和右指针相遇的地方，因此该字符不会发生改变，对于偶数长度的字符串，两个指针一定会在交换完最后两个字符相遇，所以可以完全旋转该字符串。__

__可以看到双指针的效率还是很不错的__

~~这好像是本蒟蒻第一个最优解，当然是因为这个题没什么人做啦~~
![运行效率](https://cdn.luogu.com.cn/upload/image_hosting/n5tj60su.png)

## 代码
__因为字符串长度很短，所以我们可以暴力枚举每个位置，插入每种字符__
```cpp
#include <iostream>
using namespace std;
// 手写一个swap函数，当然也可以用algorithm里的 
void sp(char &a, char &b) {
	char temp = a;
	a = b;
	b = temp;
}
// 双指针旋转字符串 
bool solve(string str) {
	string temp = str;
	// 定义左右指针的位置 
	int l = 0, r = str.size() - 1;
	// 指针对撞 
	while (l < r) sp(temp[l++], temp[r--]);
	// 如果是回文字符串，就说明产生了一个答案 
	return str == temp;
}
int main() {
	string str;
	cin >> str;
	string temp;
	int sLen = str.size();
	// 在每个位置枚举可以插入的字符 
	for (char i = 'a'; i <= 'z'; i++) {
		for (int j = 0; j <= sLen; j++) {
			temp = str;
			// insert方法可以在j这个位置插入长度为1的字符i 
			temp.insert(j, 1, i); 
			// 产生了答案直接退出 
			if (solve(temp)) {
				cout << temp << endl;
				return 0;
			}
		}
	}
	cout << "NA" << endl;
	return 0;
}
```

__这个题其实也是SJ，所以答案顺序并不重要__

---

## 作者：lovely_fcukh (赞：0)

## 题目大意
在原字符串上加一个小写字母使得字符串回文。如果可以，输出回文数；否则，输出 NA。
## 思路
我们可以发现数据量很小，$s$ 的长度仅为 10，所以我们可以考虑模拟加穷举。

我们从最开头到最末尾这 $n+1$ 个位置模拟一下，每一次穷举 $a$ 到 $z$，将穷举到的字母插入模拟到的位置，如果这样组成的字符串满足回文的条件，就输出。如果枚举完了还没有输出，代表不能满足条件，输出 NA。
## AC代码
```
#include<bits/stdc++.h>
using namespace std;
string s;
bool f(string x){
	for(int i=0,j=x.size()-1;i<j;i++,j--)
		if(x[i]!=x[j])return 0;
	return 1;
}
int main(){
	cin>>s;
	for(int i=0;i<=s.size();i++){
		for(char j='a';j<='z';j++){
			string c="";
			for(int j=0;j<i;j++)c+=s[j];
			c+=j;
			for(int j=i;j<s.size();j++)c+=s[j];	
			if(f(c)){
				cout<<c;
				return 0;
			}
		}
	}
	cout<<"NA";
	return 0;
}
```

---

## 作者：Keroshi (赞：0)

# 题意
在字符串里添加一个字符，判断能否使其变为回文串。
# 解题思路
一个长度为 $n$ 的字符串有 $n+1$ 个位置可以插入字符，   
那么先枚举在这些位置插入字符，判断插入后的字符串是否回文。  
可以在字符串内插入特殊字符，再在函数内特判，时间复杂度降到 $O(n^2)$。
# 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
string a,b; 
bool check(string x){ // 判断回文
    for(int i=0;i<x.size()/2;i++){
        int j=x.size()-i-1;
        // 注意特判
        if(x[i]!='?'&&x[j]!='?'&&x[i]!=x[j]) return 0;
    }
    return 1;
}
int main(){
    cin >> a;
    for(int i=0;i<=a.size();i++){
        b=a;
        b.insert(i,"?"); // 插入特殊字符
        if(check(b)){
            b[i]=b[b.size()-i-1]; // 将特殊字符替换掉
            cout << b;
            return 0;
        }
    }
    cout << "NA";
    return 0;
}
```

---

## 作者：708151_qwq (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/CF505A)

# 题意简述

给定一个字符串，加上一个小写字母使其回文。如果可以，输出修改后的字符串；否则，输出 `NA`。

# Solution

因为这题数据范围太小，所以直接暴力枚举即可。

在每一个位置枚举插入 `a` ~ `z`，如果可以，直接输出答案。最后如果无解，输出 `NA`。

# AC Code

```cpp
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
int main(){
	string s; cin>>s;
	for(int i=0; i<s.size(); i++) {//枚举每个位置 
		for(char c='a'; c<='z'; c++) {//枚举插入a~z 
			string str=s, str1;//str为插入字符后的字符串，str1为备份字符串
			str.insert(i+1, 1, c);//在 i+1 的位置前插入 c，即在 i 的位置插入 c 
			str1=str;//备份，保存 
			reverse(str.begin(), str.end());//反转 
			if(str == str1) {//如果找到答案 
				cout<<str1;//输出 
				return 0;//提前结束程序 
			}
		}
	}
	printf("NA");//如果没找到答案，输出 NA 
	return 0;//完结撒花 
}
```

---

## 作者：Franka (赞：0)

### **题目**
一个字符串**加上**一个**小写字母**后，使得字符串变成**回文字符串**：

如果可以，输出这个回文数；

否则，输出NA。
### **思路**
仔细一看字符串的长度，发现$|s|≤10$，因此可以用无脑模拟。

先介绍一下Pascal中的插入函数：insert。
~~（其实键盘上有的）~~

#### 作用：$insert(x,y,t)$表示将$x$插入到$y$的第$t$位。

#### 举例：$x='abc';$ $insert('12',x,2);$，$x$为$'a12bc'$。
### **代码**
```pascal
var ch:char;n,m:string;i:longint;//定义
function pd(n:string):boolean;//判断是否是回文数的一个函数
var
 i:longint;
 m:string;
begin
 m:='';
 for i:=length(n) downto 1 do m:=m+n[i];//反转
 if n=m then exit(true);//如果是回文数，返回TRUE
 exit(false);//否则返回FALSE
end;
begin
 readln(n);//读入n
 for i:=1 to length(n)+1 do//因为到length(n)位的时候把最后一位漏了，所以加一
  for ch:='a' to 'z' do//a到z
   begin
    m:=n;//找个替身
    insert(ch,m,i);//插入
    if pd(m) then//判断回文
     begin
      writeln(m);exit;//如果是，则输出m并结束程序
     end;
   end;
 writeln('NA');//没有
end.
```


---

## 作者：hensier (赞：0)

这道题直接枚举模拟即可。我们可以不停地插入字符，然后不停地判断，最终一满足条件就输出。

这里用到了一个函数，叫做$reverse()$。例如，有一个字符串$s$，我们现在要把它反转，那么只需要执行$reverse(s.begin(),s.end());$即可。当然也可以局部反转。具体可以看这里：[传送门](http://www.cplusplus.com/reference/algorithm/reverse/)。

我们还需要用到$string.insert()$函数，这里用到的是：$string.insert(pos,times,char)$，即在$pos$处插入$times$个字符$char$（上述参数是自己为了更好演示自己加的，不是原库的参数）。对于其他用法可以看这里：[传送门](http://www.cplusplus.com/reference/string/string/insert/)。

上述两种函数均属于$STL$库，需要调用头文件$algorithm$。~~万能头文件就行了。~~

$AC$代码：

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
string s,S;
bool check(string x)//一个check函数
{
    string X=x;//先复制
    reverse(X.begin(),X.end());//反转任意一个字符串
    if(X==x)return 1;//判断与另一个是否相同
    return 0;
}
int main()
{
    cin>>s;//输入
    S=s;//复制
    for(int i=0;i<=s.size();i++)//注意，这里如果不用小于等于的话会漏情况（样例1提醒了我们）
    {
        for(char j='a';j<='z';j++)//可以用char变量进行直接循环，这样就不需要用ASCII处理了
        {
            s.insert(i,1,j);//insert函数
            if(check(s))//只要满足就输出
            {
                cout<<s;
                return 0;//退出程序
            }
            s=S;//这里要重新赋值（当然也可以s.erase(i,1)）
        }
    }
    cout<<"NA";//输出NA
}
```

---

## 作者：MrFish (赞：0)

#### 整体思路：枚举所有位置，判断插入a-z行不行。
我们在判断回文时可以用这个函数：
```latex
reverse(s.begin(),s.end());
```
它的作用就是把字符串s翻转。
很实用的函数。
#### 奉上AC代码：
```cpp
#include<bits\stdc++.h>

using namespace std;

int main()
{
    string s;
    cin>>s;
    for(int i=0;i<=s.size();i++)//枚举每一个位置
    {
        for(char j='a';j<='z';j++)//枚举a-z
        {
            string k=s; //k为s插入字符后的字符串
            string tmp;
            k.insert(i,1,j);//在i的位置插入j
            tmp=k;//做备份
            reverse(k.begin(),k.end());//翻转
            if(tmp==k)//如果回文
            {
                cout<<k<<endl;
                return 0;
            }
        }
    }
    cout<<"NA"<<endl;//没有答案
    return 0;
}
```
拜拜！

---

## 作者：Loxilante (赞：0)

本蒟蒻第一次发题解 qwq


------------

我的思路就是穷举字符a-z在字符串的每一个位置插入并判断它是否回文
### Code：
```cpp
#include<iostream>
#include<string>
using namespace std;
bool is_pal(string& str) //判断字符串str是否回文 
{
	int l = str.length()-1;  
	int half = l/2; // str长度的一半 
	for(int i = 0; i <= half; i++)
		if (str[i] != str[l-i]) // 判断正数第i个字符是否与倒数第i个字符相同 如果不相同就不是回文字符串 
			return false; 
	return true;
}
int mian()
{
	string str;
	cin>>str;
	for(int i = 0; i <= str.length(); i++) // 因为可能在末尾插字符 所以要循环str的长度+1次 
		for(char ch = 'a'; ch <= 'z'; ch++) // 穷举每个字符插在每个位置是否回文 
		{
			string ans = str;
			ans.insert(i, 1, ch); // 在字符串str的第i个位置插入一个字符ch 
			if (is_pal(ans)) // 判断是否回文 
			{
				cout<<ans;
				return 0;
			}
		}
	cout<<"NA";  
	return 0
}
```



---

