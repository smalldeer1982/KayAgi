# Encoder and Decoder

## 题目描述

### 题意简述
给定一串字符(长度$\le80$)，如果它是明文，转成密文，如果它是密文，转成明文。  
明文中只会出现以下字符：大小写字母，感叹号，逗号，句号，空格，冒号，分号，问号(均为英文标点)。  
加密方式是：把每个字符转换成对应的ASCII码，然后整体反转。  
e.g. 对于明文`abc`，首先将其转成对应的ASCII码：`97 98 99`，去除中间的空格：`979899`，整体反转输出：`998979`。

## 样例 #1

### 输入

```
abc
798999
Have a Nice Day !```

### 输出

```
998979
cba
332312179862310199501872379231018117927```

# 题解

## 作者：MrZombie_409 (赞：0)

## 思路
这是一道简单的模拟题，按照题目要求编写代码即可。
### 1.字符串反转
定义一个与原字符串相同的字符串 $s$，然后倒着遍历原字符串，再将字符串 $s$ 的每一项存到原字符串 $n$ 中。由于是倒着遍历的，所以也会将原字符串的内容反转。
```cpp
string s=n;
for(int i=0;i<n.length();i++)
    n[i]=s[n.length()-1-i];
```

### 2.判断
如果原字符串第一位是 $1$，则是密文，否则是明文。
```cpp
if(n[i]=='1')
```
### 3.明密文互换
模拟题意。
#### 1.明文
```cpp
string s=n;
for(int i=0;i<n.length();i++){
	n[i]=s[n.length()-1-i];
	int y=n[i];
	for(int i=0;i<2;i++){
		cout<<y%10;
		y/=10;
	}
}
cout<<endl;
```
#### 2.密文
```
string s=n;
for(int i=0;i<n.length();i++)
	n[i]=s[n.length()-1-i];
	for(int i=0;i<n.length();i+=2){
		short x;
		if(n[i]=='1'){
			x=(n[i]-'0')*100+(n[i+1]-'0')*10+n[i+2]-'0';
			i++;
			cout<<(char)x;
		}
		else{
			x=(n[i]-'0')*10+n[i+1]-'0';
			cout<<(char)x;
		}
	}
	cout<<endl;
```
## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string n;
int main(){
	while(1){
		getline(cin,n);
		if(n[0]>='0'&&n[0]<='9'){
			string s=n;
			for(int i=0;i<n.length();i++)
				n[i]=s[n.length()-1-i];
			for(int i=0;i<n.length();i+=2){
				short x;
				if(n[i]=='1'){
					x=(n[i]-'0')*100+(n[i+1]-'0')*10+n[i+2]-'0';
					i++;
					cout<<(char)x;
				}
				else{
					x=(n[i]-'0')*10+n[i+1]-'0';
					cout<<(char)x;
				}
			}
			cout<<endl;
		}
		else{
			string s=n;
			for(int i=0;i<n.length();i++){
				n[i]=s[n.length()-1-i];
				int y=n[i];
				for(int i=0;i<2;i++){
					cout<<y%10;
					y/=10;
				}
			}
			cout<<endl;
		}
	}
	return 0;
} 
```


---

## 作者：封禁用户 (赞：0)

# 题意
输入若干个字符串，对于每个字符串，如果是明文转换为密文，如果是密文则转换成名文。

明文中只会出现以下字符：大小写字母，感叹号，逗号，句号，空格，冒号，分号，问号(均为英文标点)。
加密方式是：把每个字符转换成对应的 ASCII 码，然后整体反转。

# 思路
本题由于要倒序，所以先要写一个反转字符串的函数，如下：
```cpp
string upsidedown(string x){
	string y(200,' ');//这里初始化字符串
	int sum=x.size();
	for(int i=0;i<sum;i++){
		y[i]=x[sum-i-1];
	}
	return y;
}
```
之后我们需要判断明文和密文。如果第一位是数字，是密文，否则就是明文。判断方法如下：
```cpp
if(s[0]>='0'&&s[0]<='9'){//如果是密文
	//转换部分
}else{//如果是明文
	//转换部分
}
```
# Code：
```
#include<bits/stdc++.h>
using namespace std;
string s;
int ssize;
string upsidedown(string x){//字符串反转
	string y(200,' ');//字符串初始化
	int sum=x.size();
	for(int i=0;i<sum;i++){
		y[i]=x[sum-i-1];
	}
	return y;
}
int main(){
	while(cin>>s){
		ssize=s.size();
		if(s[0]>='0'&&s[0]<='9'){//密文
			s=upsidedown(s);
			for(int i=0;i<ssize;i+=2){
				int cnt=s[i]-'0';
				cnt*=10;
				cnt+=s[i+1]-'0';
				cout<<(char)cnt;//依次输出
			}
		}else{//明文
			string s2(ssize*2,' '); //初始化
			for(int i=0;i<ssize;i++){
				int cnt=s[i];
				int sum=cnt%10;//个位 
				cnt/=10;//十位 
				s2[i*2]=cnt+'0';//将数字转换为字符
				s2[i*2+1]=sum+'0';
			}
			cout<<upsidedown(s2);
		}
		cout<<endl;//换行
	}
	return 0;
} 
```



---

## 作者：sunyizhe (赞：0)

这题其实很简单，只需模拟。

## 一、题意

输入一串明文或密文，需相互转换（明文和密文需自己判断）。随后输出明文或密文。明文只有大小写字母、逗号、句号、**空格**、冒号、分号、问号（均为英文）。

## 二、思路

其实明白这题意思，代码基本上能 $5$ 分钟写出来。UVA 这题输入输出都很友好，算是 UVA 里不多的题了。

对于每个字符串 $s$，我们用 ```getline``` 读入，因为有空格。根据题意，我们发现：明文不包含数字，密文不包含字母和符号。因此，我们判断 $s$ 首位是否为数字。如果不是，则 $s$ 为明文；否则为密文。

### 2.1 $s$ 为明文

由于要反转输出，所以我们将 $s$ 的每个字符的 ASCII 码压入栈中。输出时取栈顶元素弹出，再将这个数反转输出，就加密成了密文。

### 2.2 $s$ 为密文

这个情况有点难办。我们细细观察题目中给的字符，发现当 ASCII 码为 $3$ 位时，百位一定为 $1$。不然一定是两位 ASCII 码。密文是反过来的 ASCII 码，所以我们将 $s$ 反转回来。此后，我们扫一遍 $s$。当 $s_i=\texttt{1}$，就是三位数，读取三位 ASCII 码，转换成字符输出，最后得到明文。

## 三、代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	while(getline(cin,s))
	{
		if(!isdigit(s[0]))//是否为明文 
		{
			stack<int> p; //由于反向输出，所以用栈。 
			for(int i=0;i<s.size();i++)
				p.push(int(s[i])); //将明文每个字符的ASCII码压入栈中 
			while(!p.empty())
			{
				int t=p.top();
				p.pop();
				while(t)//每个字符的ASCII码也反向输出 
				{
					cout<<t%10;
					t/=10;
				}
			}
			cout<<endl;
		}
		else
		{
			reverse(s.begin(),s.end());//先反转字符串 
			for(int i=0;i<s.size();i++)
				if(s[i]=='1')//说明是三位ASCII码 
				{
					char ch=char((s[i]-'0')*100+(s[i+1]-'0')*10+(s[i+2]-'0')*1);
					cout<<ch;
					i+=2;
				}
				else //不然就是两位ASCII码 
				{
					char ch=char((s[i]-'0')*10+(s[i+1]-'0')*1);
					cout<<ch;
					i+=1;
				}
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/UVA444)    
水题。     
我们如何确定这个字符串是不是密文呢？    
在题目描述中，可以看到明文不可能出现数字。所以只要输入的字符串里的某一位是数字，就可以确定是密文了。      
这里先讲密文如何解密。我们读入密文后，先反转，再逐段看。如果这一段开头是 ```1```，那么这一段就是三位的 ASCII 码值，否则是两位的 ASCII 码值。我们直接读取到这个 ASCII 码值，之后跳过这一段，到下一段即可。    
接下来讲如何加密。我们先把每一个字符的 ASCII 码值求出，拼接起来放到一个字符串里，再反转即可。     
CODE:    
```cpp
#include <iostream>
#include <string>
using namespace std;
string string_reverse(string s){//反转字符串
	string a(s);
	for(int i=0;i<s.length();i++){
		a[i]=s[s.length()-1-i];
	}
	return a;
}
string its(int x){//数字转字符串
	string s;
	while(x!=0){
		char ca[2]={x%10+'0'};
		s.insert(0,ca);
		x/=10;
	}
	return s;
}
string crtosr(char a){//字符转字符串
	char c[2]={a};
	return c;
}
string s,ans;
int i,pn,p[100];
int main(void){
    while(getline(cin,s)){//用getline不断输入
    	ans="";//清空
    	if(s[0]>='0'&&s[0]<='9'){//判断是不是密文
    		s=string_reverse(s);//先反转
    		for(int i=0;i<s.length();i++){//求明文
    			if(s[i]=='1'){//3位数
					ans.append(crtosr(char((s[i]-'0')*100+(s[i+1]-'0')*10+(s[i+2]-'0'))));
					i+=2;
				}else{//2位数
					ans.append(crtosr(char((s[i]-'0')*10+(s[i+1]-'0'))));
					i++;
				}
			}
		}else{//否则为明文
			for(int i=0;i<s.length();i++){//求ASCII码值
				ans.append(its((int)s[i]));
			}
			s=ans;//反转操作
			s=string_reverse(s);
			ans=s;
		}
		cout<<ans<<endl;//输出结果
	}
}
```


---

## 作者：昒昕 (赞：0)

**题意简述**

给定一个字符串，如果只含数字就是密文，需解密成明文；否则就是明文，需加密为密文。

加密方式为：把每个字符都转换为对应的 ASCII 码，然后整体翻转。

**题目分析**

加密：对于一个字符，可以将它转换为 ASCII 码，一位一位依次入栈，然后翻转输出。

解密：对于某一 ASCII 码的第一位，如果该数字为 $1$，则代表它是一个三位 ASCII 码，则弹出三个数字存到临时变量中；否则，如果是两位 ASCII 码，则弹出两个数字。最后把临时变量存储的 ASCII 码转换为字符输出。

```cpp
#include <bits/stdc++.h>
using namespace std;

string str;
stack <int> s;

int main() {
	while (getline(cin,str)) { //getline可以读入一整行，包括空格，读到EOF后会返回0 
		bool f=1;
		for (int i=0;i<(int)str.size();i++) {
			if (!isdigit(str[i])) { //如果s中有非数字字符，就代表s是明文 
				f=0; break;
			}
		}
		if (!f) { //明文 
			for (int i=0;i<(int)str.size();i++) {
				if ((int)str[i]>=100)	{ //三位数 
					s.push((int)str[i]/100); //百位 
					s.push(((int)str[i]-(int)str[i]/100*100)/10); //十位 
					s.push(str[i]%10); //个位 
				} else { //如果是二位数 
					s.push((int)str[i]/10); //十位 
					s.push((int)str[i]%10); //个位 
				}
			}
			while (!s.empty()) { //因为栈是先进后出，也相当于翻转了一遍 
				printf("%d",s.top()); s.pop();
			}
		} else { //密文 
			for (int i=0;i<(int)str.size();i++)
				s.push((int)str[i]-'0'); //存入栈中，既可以相当于翻转又可以方便删除 
			while (!s.empty()) {
				int t=0;
				for (int i=s.top()==1?0:1;i<=2;i++) { //如果一个数是1开头的，就代表是三位数，则需要取3次 
					t=t*10+s.top();
					s.pop();
				}
				printf("%c",(char)t); //将分离出的ASCII码转为字符输出 
			}
		}
		puts("");
	}
	return 0;
}

```

---

