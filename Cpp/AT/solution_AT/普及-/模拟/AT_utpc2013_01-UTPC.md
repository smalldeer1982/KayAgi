# UTPC

## 题目描述

### 题目背景
鳗鱼王国的国王计划举办一场名为 Unagi The synthesis Programming Contest（简称UTPC）的比赛。因此，国王征集了一个很酷的 UTPC 标志。然而，国王的眼睛非常不好，只能通过字母中孔的数量来区分字符串。
给定一个由大写字母组成且长度为 $4$ 的字符串 $s$。回答 $s$ 是否与字符串"UTPC"在“孔的数量意义上相等”。"孔的数量意义上相等"指的是，对应位置的 $2$ 个字母的孔的数量相等。其中，孔的数量为 $0$ 的字母是 `CEFGHIJKLMNSTUVWXYZ`，孔的数量为 $1$ 的字母是 `ADOPQR`，孔的数量为 $2$ 的字母是 `B`。

## 样例 #1

### 输入

```
KUPC
```

### 输出

```
yes
```

## 样例 #2

### 输入

```
UTPC
```

### 输出

```
yes
```

## 样例 #3

### 输入

```
UTBC
```

### 输出

```
no
```

# 题解

## 作者：LiveZoom (赞：3)

# 题解 AT836 【UTPC】
本题是对字符串和打表的考察。

- 定义部分

先定义一个基准数组s，表示"UTPC"：

```cpp
string s = "UTPC";
```

- 打表部分

这个部分是这个程序中最重要的部分了：

用一个数组a，来表示每个字符有多少个洞
$$\texttt{ABCDEFGHIJKLMNOPQRSTUVWXYZ} $$
$$\texttt{12010000000000111100000000}$$
这是字符的洞的数量的对应，那么我们可以这样写：

```cpp
int a[26] = {1,2,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0};//我们用a[i]表示i+'A'这个字符的洞数
```

- 主函数

```cpp
int main() {
	for (int i = 0; i < 4; i++) {
		char c = getchar();
		if (a[c - 'A'] != a[s[i] - 'A']) {puts("no"); return 0;}//如果c的洞数与s[i]的洞数不同，就提前结束了
	}
	puts("yes");//所有的都相同就输出yes
	return 0;
}
```

- 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[26] = {1,2,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0};
string s = "UTPC";

int main() {
	for (int i = 0; i < 4; i++) {
		char c = getchar();
		if (a[c - 'A'] != a[s[i] - 'A']) {puts("no"); return 0;}
	}
	puts("yes");
	return 0;
}
```

请勿抄袭。

求通过

---

## 作者：该起什么名字 (赞：2)

依照题意模拟就好啦(鬼知道我怎么过了第21个点)
由于在“UTPC”中第1,2,4个字母都没有洞，所以直接判断输入的字符串中在这几个字母上有没有洞就好了
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
	std::ios::sync_with_stdio(false);
	cin>>s;
	for(int i=0;i<4;i++)
	{
		if(i==2)
		{
			if(s[i]=='A'||s[i]=='D'||s[i]=='O'||s[i]=='P'||s[i]=='Q'||s[i]=='R') continue;
			//“UTPC”中第三个字母有一个洞，判断输入的字符的第三个字母是不是有个洞就好了
            else
			{
				cout<<"no"<<endl;
				return 0;
			}
		}
		else
		{
			if(s[i]=='A'||s[i]=='D'||s[i]=='O'||s[i]=='P'||s[i]=='Q'||s[i]=='R'||s[i]=='B')
			{
				cout<<"no"<<endl;
				return 0;
			}
		}
	}
	cout<<"yes"<<endl;//如果上面一直没退出就说明符合条件
	return 0;
}

```

---

## 作者：打表大蒟蒻 (赞：2)

这道题呢，我和一些dalao想得不太一样，因为题意要逐个判断每个字母，所以我们把0洞数的存进一个字符串内，称为s1，因为我们知道UTPC这四个字母中U、T和C均是0洞数，所以，一旦下标到了0、1、3就把这个读入的待判断字符串中的这个字母在s1中查找，若找不到，直接输出no。同理，对于下标2也是如此。另外，我们为了提高效率（~~虽然也没什么用~~），因为有2个洞数的只有B，所以一旦检测到待判断字符串中有B，也是直接输出no。

压行版代码：
```
#include <bits/stdc++.h>
using namespace std;
string s1="CEFGHIJKLMNSTUVWXYZ", s2="ADOPQR", s;
int main ()
{
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(s[i]=='B') {cout<<"no"<<endl;return 0;}
		bool pd=false;
		if(i==0||i==1||i==3){for(int j=0;j<s1.size();j++) if(s[i]==s1[j]){pd=true;break;}}
		else {for(int j=0;j<s2.size();j++) if(s[i]==s2[j]){pd=true;break;}}
		if(!pd) {cout<<"no"<<endl;return 0;}
	}
	cout<<"yes"<<endl;return 0;
} 
```
正常版代码：
```cpp
#include <bits/stdc++.h>  //万能头
using namespace std;  //名字空间
strings1="CEFGHIJKLMNSTUVWXYZ",
s2="ADOPQR",s; //存一下，在题目中Ctrl+C，Ctrl+V
int main ()
{
	cin>>s;  //标准读入
	for(int i=0;i<s.size();i++){
		if(s[i]=='B') {  //特判
			cout<<"no"<<endl;
			return 0;  //结束
		}
		bool pd=false;
		if(i==0||i==1||i==3){
			for(int j=0;j<s1.size();j++)//开始查找 
				if(s[i]==s1[j])  //如果找到了
				{
					pd=true;   //标记一下
					break;  //退出
				}
		}
		else {
		for(int j=0;j<s2.size();j++) //开始查找
			if(s[i]==s2[j])  //如果找到了
			{
				pd=true;  //标记一下
				break;  //退出
			}
		}
		if(!pd) {  //每一次都判断，以提高效率
			cout<<"no"<<endl;
			return 0;  //结束
		}
	}
	cout<<"yes"<<endl;  //如果所有检测都通过了，输出yes
	return 0;   //完美结束
} 
```


---

## 作者：happybob (赞：1)

STL大法好

map不好吗

map也是打表，但最好的一点在于只要存圈圈为1和2的7个，因为map没有赋值的自动设为0，与题意一样

注意这个题目是这样的，并不是只是圈圈数于UTPC一样，每一位也要一样，这就是为什么有人过不了#21的原因

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <map>
using namespace std;

map<char, int> mp;

char ch;

int main()
{
    mp['A'] = mp['D'] = mp['O'] = mp['P'] = mp['Q'] = mp['R'] = 1;
    mp['B'] = 2;
    int sum = 0, cnt = 1;
    while(scanf("%c", &ch) != EOF)
    {
        if(cnt == 1 || cnt == 2 || cnt == 4)
        {
            if(mp[ch])
            {
                cout << "no\n";
                return 0;
            }
        }
        else if(cnt == 3)
        {
            if(!mp[ch] || mp[ch] == 2)
            {
                cout << "no\n";
                return 0;
            }
        }
        sum += mp[ch];
        if(sum >= 2)
        {
            cout << "no\n";
            return 0;
        }
        cnt++;
    }
    cout << "yes\n";
    return 0;
}
```


---

## 作者：jeremyjy (赞：1)

Although my code is wrong,我还是要发题解

暴力枚举每个字母，加一加，加出孔数

是1yes，否则no

上代码↓↓↓
```
#include<bits/stdc++.h>//万能库
using namespace std;//使用名字空间
int main()//主程序
{
	string s;//定义
	int i,ans=0;//同上
	cin>>s;//读入
	for(i=0;i<4;i++)//加一加孔数
	{
		if(s[i]=='B')
		{
			ans+=2;
			continue;
		}
			if(s[i]=='A'||s[i]=='D'||s[i]=='O'||s[i]=='P'||s[i]=='Q'||s[i]=='R')
		{
			ans+=1;
			continue;
		}
	}
	if(ans==1)//算完啦，PD
		cout<<"yes"<<endl;
	else
		cout<<"no"<<endl;
	return 0;//华丽结束
}
```

另：蒟蒻#21爆零啦，如果有人知道如何AC本题，欢迎发评论或私信给我！

---

## 作者：Dream_hjf (赞：0)

# 本蒟蒻的第一篇题解

------------
没过第21个点的，全都没有仔细看题！！！
题目中要求是每一个字母的洞数都与‘UTPC’相同，因此，第一个字母是0个洞，第二个字母是0个洞，第三个字母是1个洞，第四个字母是0个洞，最终只比较每个字母的洞数加起来是否为1就会WA一个点

下面是代码

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[26]={1,2,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0};//打表大法，得出每个字母的洞数
string d;
int cnt[4];//cnt代表每一个字母对应的洞数
int main(){
	getline(cin,d);//读入
	int b=d.size();//求字符串长度（然而并没有用，都说了是4个字母）
	for(int i=0;i<b;++i){
		cnt[i]+=a[d[i]-='A'];//得出每个字母的洞数
	}
	if(cnt[2]==1&&cnt[0]==0&&cnt[1]==0&&cnt[3]==0){
        cout<<"yes"<<endl;
        }else{
		cout<<"no"<<endl;
	}//最后的判断
	return 0;//好习惯
}
```

---

## 作者：Cambridge (赞：0)


蒟蒻又来发题解了！

这道题我才用的就是打表，毕竟也就4位数。我们要注意一个坑点，不是洞数是1就输出yes，是要每一个字母的洞数跟UTPC的洞数都一样，这样才是对的。~~本蒟蒻前几次提交就因此WA~~

思路就讲到这里，代码如下：

```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>//文件头不解释
using namespace std;
string st1;
int main()
{
cin>>st1;
for(int i=0; i<st1.size(); i++)
	if(st1[i]=='B')//因为出现了B，即两个洞，所以直接不行
	{
		cout<<"no"<<endl;
		return 0;
	}
if(st1[0]=='A'||st1[0]=='D'||st1[0]=='O'||st1[0]=='P'||st1[0]=='Q'||st1[0]=='R')//打表第一位
{
	cout<<"no"<<endl;
	return 0;
}
if(st1[1]=='A'||st1[1]=='D'||st1[1]=='O'||st1[1]=='P'||st1[1]=='Q'||st1[1]=='R')//打表第二位
{
	cout<<"no"<<endl;
	return 0;
}
if(st1[2]!='A'&&st1[2]!='D'&&st1[2]!='O'&&st1[2]!='P'&&st1[2]!='Q'&&st1[2]!='R')//打表第三位
{
	cout<<"no"<<endl;
	return 0;
}
if(st1[3]=='A'||st1[3]=='D'||st1[3]=='O'||st1[3]=='P'||st1[3]=='Q'||st1[3]=='R')//打表第四位
{
	cout<<"no"<<endl;
	return 0;
}
cout<<"yes"<<endl;//如果符合要求就输出
    return 0;
}

```

好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

