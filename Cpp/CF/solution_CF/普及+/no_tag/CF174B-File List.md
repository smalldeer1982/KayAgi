# File List

## 题目描述

Eudokimus, a system administrator is in trouble again. As a result of an error in some script, a list of names of very important files has been damaged. Since they were files in the BerFS file system, it is known that each file name has a form "name.ext", where:

- name is a string consisting of lowercase Latin letters, its length is from 1 to 8 characters;
- ext is a string consisting of lowercase Latin letters, its length is from 1 to 3 characters.

For example, "read.me", "example.txt" and "b.cpp" are valid file names and "version.info", "ntldr" and "contestdata.zip" are not.

Damage to the list meant that all the file names were recorded one after another, without any separators. So now Eudokimus has a single string.

Eudokimus needs to set everything right as soon as possible. He should divide the resulting string into parts so that each part would be a valid file name in BerFS. Since Eudokimus has already proved that he is not good at programming, help him. The resulting file list can contain the same file names.

## 样例 #1

### 输入

```
read.meexample.txtb.cpp
```

### 输出

```
YES
read.m
eexample.t
xtb.cpp
```

## 样例 #2

### 输入

```
version.infontldrcontestdata.zip
```

### 输出

```
NO
```

# 题解

## 作者：By_Ha (赞：4)



> [题面跳转](https://www.luogu.org/problemnew/show/CF174B)

---

- 题目大体意思是让我们把接下来的字符串分割成很多文件名,使文件名前缀不超过8个字符,文件名后缀不超过3个字符。我们只需要找到每两个`.`之间的字符数,如果大于11或者小于2就输出`NO`,再对开头结尾做一个特判,判断其是否超过3个,8个字符长的限制,这题就能过。

- 注意:模拟题绝对不能不打草稿直接写

	- 反正我是爆炸了

- 接下来结合代码讲解(分割字符=='.')

```cpp
#include <iostream>
#include <string>
#include <cstdio>//头文件,打死不用stdc++.h，反正我觉得会让代码变慢

using namespace std;

string s; //读入字符串

bool isOK() {//判断函数，用于判断字符串是否可以分割
	int len = 0;//长度，存储两个分割字符之间的字符数量
	int plc = 1;//位于第几块，以'.'区分块
	int i;//循环变量
	for(i = 0; s[i]!='\0'; i++) {//从头读到尾
		if(s[i] == '.') {//如果找到分割字符'.'
			if(plc == 1) {//恰好是第一块,也就是开头
				if(len == 0||len>8)//开头直接是分割字符或者长度超限
					return false;//选择退役
			} else if(len <=1 || len >= 12) {//再中间的几块中字符长度如果太小太大
				return false;//退役
			}
			len = 0;//读到分割字符后记得重置长度
			plc ++;//顺便把分块(不是算法分块)的编号加上
			continue;
		}
		len ++;//不是分割字符只加上该字符的长度1，不做运算
	}
	//如果最后一块有字符,并且长度小于等于3，返回true，否则返回false，这里写得非常随意，其实可以通过len判断，但我懒啊
	return s[i-1] != '.'&&(s[i-2]=='.'||s[i-3]=='.'||s[i-4]=='.');
}

int main() {//伟大的主函数
	cin >> s;//标准方法读入，只有'.'这个字符的话不用getline
	if(isOK())//如果可以分割
		cout << "YES" << endl;//NOI大喊CCF选我 Cu -> Au
	else {
		cout << "NO" <<endl;//选择退役
		return 0;//注意退役退到底
	}
            //开始输出内容
	int i,j;//因为循环变量在之后要用到计算，所以要存下来，不能作为for循环局部变量
	for(i = 0; s[i]!='\0'; i++) {//对于s中的每一个字符
		if(s[i]=='.') {//我们判断是否为分割字符
			putchar(s[i]);//如果是的我们先把他输出了
			for(j = 1; s[i+j]!='\0'; j++)//这里注意是i+j我有好几遍都是j然后WA，RE暴毙，这个主要功能是数有多少个字母在'.'之间
				if(s[i+j] == '.')//如果扫到了'.'，退出循环
					break;
			j--;//由于我们会把最后一个'.'计入答案,所以要减去一个
			if(j>3)//如果j的长度超过一次能输出的上限,也就是3个
				j = 3;//把j赋值3
			else if(s[i+j+1]!='\0') j--;//如果这里不是字符串末尾还要给后面留一个输出的字符，例如aaa.bc.aa 我们会拆成aaa.b 和 c.aa 中间的bc留一个给后面当头用
			for(int k = 1; k<=j; k++) {
				if(!isalpha(s[i+k]))//好像没什么用
					continue;
				putchar(s[i+k]);//输出
			}
			i+=j;//加上已经输出的
			putchar('\n');//注意换行
			continue;//不要再执行putchar了，所以continue
		}
		putchar(s[i]);//如果不是分割的'.'字符，直接输出
	}
	return 0;//告诉CCF   您AK NOI
}
```

# 最后，祝各位NOIp2019 RP++

---

## 作者：Eason_AC (赞：2)

## Content
给定一个只包含小写字母和 `.` 的字符串 $S$，请你将其分割成若干个形如 `A.B` 的字符串（$A$ 为一个长度不超过 $8$ 的字符串，$B$ 为一个长度不超过 $3$ 的字符串），或者报告不存在合法的分割方案。

**数据范围：$|S|\leqslant 4\times 10^5$。**
## Solution
好吧，我承认这题目确实不难，但是很多坑点……下面把我在做这道题目的时候踩过的坑跟大家讲讲，主要也就这下面四个点：

1. 在分割的时候，如果你临时存储分割的部分在扫完一遍字符串之后还存储着一些字符，首先需要判断其是否合法，不合法就判定无解（Test 48），否则得要把这个字符串再弹进去……（Test 4）
2. 在扫到 `.` 的时候，一定要注意以下两点：
    - 后面是否紧跟着一个 `.`（Test 6）或者一个字母加一个 `.`。
    - 这个 `.` 是否是 $S$ 的第一个字符（Test 8）或者最后一个字符（Test 8/10）。
3. 只有一个点而没有其他字母也是无解的。（Test 8）
4. 只有字母而没有点也是无解的。（Test 9）

然后讲讲分割的策略：如果你当前扫到了 `.`，那么你后面应当扫越多的字符进入 $B$ 部分越好，但是不能把 $A$ 部分的字符全部都给抢光了。

就这些，然后你就可以做出这道题目了。
## Code
```cpp
namespace Solution {
	string s, tmp;
	vector<string> vec;
	int fl, flg, cnta, cntb;
	
	iv Main() {
		cin >> s;
		F(int, i, 0, (int)s.size() - 1) {
			tmp += s[i];
			if(s[i] != '.') {
				{if(!flg) cnta++; else cntb++;}
				if(cnta == 8 && !flg && i != (int)s.size() - 1 && isalpha(s[i + 1])) {NO; return;}
				if(cntb && (cntb == 3 || (cntb < 3 && i != (int)s.size() - 2 && isalpha(s[i + 1]) && s[i + 2] == '.'))) vec.push_back(tmp), cnta = cntb = flg = 0, tmp = "";
			} else {
				flg = fl = 1;
				if(s[i + 1] == '.' || !cnta || (i != (int)s.size() - 2 && isalpha(s[i + 1]) && s[i + 2] == '.') || i == (int)s.size() - 1) {NO; return;}
			}
		}
		if(!fl) {NO; return;}
		if(tmp != "") {
			if(!flg || !cntb) {NO; return;}
			vec.push_back(tmp);
		}
		YES;
		F(int, i, 0, (int)vec.size() - 1) cout << vec[i] << endl;
		return;
	}
}
```

---

## 作者：Allen123456hello (赞：1)

# 思路

首先我们要排除一些不合法的字符串：

- 开头或结尾就是 ```.``` 的。
- **没有 ```.``` 的。**~(这里坑了一下我)~
- 连续两个 ```.``` 的。(注：如果你特判了开头、结尾长度 $\lt 1$ 就不会有这种情况)
- 开头到第一个 ```.``` 以前长度 $\lt 1$ 或 $\gt 8$ 的。
- 最后一个 ```.``` 后一个字符到结尾长度 $\lt 1$ 或 $\gt 3$ 的。
- 除开头和结尾以外用 ```.``` 分割的子串长度 $\lt 2$ 或 $\gt 11$ 的。

然后剩余的按题意模拟即可。

参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define NO return puts("NO"),0;
char s[400005];
int n,pos=0,cnt=0;
vector<int> len;
int main(){
    scanf("%s",s+1);
    n=strlen(s+1);
    if (s[1]=='.'||s[n]=='.'){NO;}
    for (int i=1,pre=1;i<=n+1;++i){
        if (s[i]=='.'||s[i]=='\0'){++cnt;len.push_back(i-pre);pre=i+1;}
    }
    if (cnt<2){NO;}
    if (len.front()>8||len.back()>3||len.front()<1||len.back()<1){NO;}
    for (int i=1;i<cnt-1;++i){
        if (len[i]<=1||len[i]>11){NO;}
    }
    puts("YES");
    for (int i=1;i<=len.front();++i){putchar(s[i]);}
    pos=len.front();
    for (int i=1;i<cnt-1;++i){
        ++pos;putchar('.');
        if (len[i]<=9){
            putchar(s[pos+1]);putchar('\n');
            for (int j=2;j<=len[i];++j){putchar(s[pos+j]);}
            pos+=len[i];
        }else{
            for (int j=1;j<=len[i];++j){if (len[i]-j+1==8){putchar('\n');}putchar(s[++pos]);}
        }
    }
    puts(s+n-len.back());
    return 0;
}
```

---

## 作者：Graph_Theory (赞：0)

## 思路

### 判断是否成立

记录点的距离，如果两点距离大于 $4$ 或者小于 $2$ 直接输出答案。

记录边和点的距离如果距离等于 $0$ 直接输出答案。如果最左点和边的距离大于 $8$ 直接输出答案。如果最右点和边的距离大于 $3$ 直接输出答案。

### 分割

从左往右取，屁股尽可能长，头由上一个串决定。

这里一定注意下标
```cpp
#include <bits/stdc++.h>
using namespace std;
string a;
int dot[400009],len=1,dt=0,now=0,sum=0;
int main()
{
	cin>>a;
	len=a.length()-1;
	for(int i=0;i<len;i++)
		if(a[i]=='.')
			dot[++dt]=i;
	if(dot[1]==0||dot[1]>=9)
	{
		cout<<"NO";
		return 0;
	}
	if(abs(dot[dt]-len)==0||abs(dot[dt]-len)>=4)
	{
		cout<<"NO";
		return 0;
	  }
	for(int i=2;i<=dt;i++)
	{
		if(abs(dot[i]-dot[i-1]-1)<2||abs(dot[i]-dot[i-1]-1)>11)
		{
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES"<<endl;
	while(now<=len)
	{
		int i=now,start=now;
		for(;i<now+8;i++)
		{
			if(a[i+1]=='.')
			{
				break;	
			}
		}
		i+=1;
		int endf=i+3;
		for(;i<min(endf,len);i++){
			if(a[i+2]=='.')
			{
				break;
			}
		}
		now=i+1;
		for(;start<=i;start++) cout<<a[start];
		cout<<endl;
	}
	return 0;
}
```


---

