# Grammar Lessons

## 题目描述

Petya 发明了一种语言。这种语言的词有三种词性、两种性别。下面是每一种词性和性别的结尾表格：

|   |阳性|阴性|
|---|---|---|
|形容词|-lios|-liala|
|名词|-etr|-etra|
|动词|-initis|-inites|

这种语言的语法有以下几条：

1. 每个句子必须按照以下顺序书写：$0$ 个或多个形容词、$1$ 个名词、$0$ 个或多个动词。
2. 一个句子中所有单词的性别必须相同。
3. 每一个单词都以上述结尾来结尾，也就是说，不以上述的结尾来结尾的单词不符合语法。
4. **单独一个合法单词也可以组成一个合法的句子。**

现在 Petya 需要你来帮助他检查语法，如果正确输出 `YES`，否则输出 `NO`。

## 样例 #1

### 输入

```
petr
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
etis atis animatis etis atis amatis
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
nataliala kataliala vetra feinites
```

### 输出

```
YES
```

# 题解

## 作者：Timon080923 (赞：5)

这题其实不难，只要认真审题就行了。  
需要注意的点：  
1.句子中所有的词阴阳性是否一致    
2.形容词是否在名词前面，动词是否在名词后面  
3.名词是否只有一个
```cpp
#include<bits/stdc++.h>
using namespace std;
int f=-1,p,v;
inline int endex(string s){//判断后缀函数
    if(s.size()<3)return -1;
    string t=s.substr(s.size()-3);
    if(t=="etr")return 2;
    if(s.size()<4)return -1;
    t=s.substr(s.size()-4);
    if(t=="lios")return 0;
    if(t=="etra")return 3;
    if(s.size()<5)return -1;
    t=s.substr(s.size()-5);
    if(t=="liala")return 1;
    if(s.size()<6)return -1;
    t=s.substr(s.size()-6);
    if(t=="initis")return 4;
    if(t=="inites")return 5;
    return -1;
}
inline bool pam(string s){//判断单词是否合法
    int k=endex(s);
    if(k<0)return 0;//判断是否为Petya语言中的单词
    if(f==-1)f=k%2;
    else if(k%2!=f)return 0;//判断阴阳性是否一致
    if(p>k)return 0;//判断单词顺序
    if(k==2||k==3)p=4,v=1;//判断名词
    else p=k;
    return 1;
}
int main(){
    string s,t;
    getline(cin,s);
    int p=s.find(" "),i=0;
    if(p<0){//不是陈述句
        cout<<(endex(s)>-1?"YES":"NO");
        return 0;
    }
    p=0,s+=" ";
    while(p>-1){
        p=s.find(" ",i);
        if(p>-1){
            t=s.substr(i,p-i);
            if(!pam(t)){cout<<"NO";return 0;}
        }
        i=p+1;
    }
    cout<<(v?"YES":"NO");
}
```
谢谢观赏！

---

## 作者：serverkiller (赞：2)

别看这是A题，写着的心态和G题一样爆炸awa

其实也没有什么思维含量，就是十分纯粹的大模拟

将后缀转换成信号，具体地看程序好了

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int INF = 0x3f3f3f3f;
char s[100010];
char word[100010];
int num[100010];

int change()//正负区分男女，绝对值区分词性
{
	int len = strlen(word);
	if (len < 3) return 0;
	if (strcmp(word+len-4,"lios") == 0) return 1;
	if (strcmp(word+len-5,"liala") == 0) return -1;
	if (strcmp(word+len-3,"etr") == 0) return 2;
    if (strcmp(word+len-4,"etra") == 0) return -2;
	if (strcmp(word+len-6,"initis") == 0) return 3;
	if (strcmp(word+len-6,"inites") == 0) return -3;
	return 0;
}

int main()
{
	while (gets(s))
	{
		int tp = 0,flag = 1,len = strlen(s),t,p = 0,cnt = 0;
		for (int i = 0; i <= len; i++)
		{
			if (s[i] != ' ' && s[i] != '\0')
			{
				word[p++] = s[i];
			}
			else
			{
				word[p] = '\0';
				t = change();
				cnt++;
				if(t != 0) num[tp++]=t;
				else
				{
					flag = 0;
					break;
				}
			}
		}
		if (cnt == 1 && flag == 1)
		{
			printf("YES\n");
			continue;
		}
		if (flag == 0)
		{
			printf("NO\n");
			continue;
		}
		cnt = 0;
		for (int i = 0; i < tp; i++)
			if (abs(num[i]) == 2) cnt++;
		if (cnt!=1)
		{
			printf("NO\n");
			continue;
		}
		flag = 1;
		if (num[0] < 0)
		{
			for (int i = 1; i < tp; i++)
				if (num[i] > 0)
				{
					flag = 0;
				    break;
				}
		}
		else
		{
			for (int i = 1; i < tp; i++)
				if (num[i] < 0)
				{
					flag = 0;
				    break;
				}
		}
		if (flag == 0)
		{
			printf("NO\n");
			continue;
		}
		flag = 1;
		for (int i = 1; i < tp; i++)
		{
			if (abs(num[i])<abs(num[i-1]))
			{
				flag = 0;
				break;
			}
		}
		if (flag)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
```


---

## 作者：Cutler (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF113A)

一道 CF 的 A 题模拟，考虑的东西看着不多，其实暗藏玄机。

- 单独的一个合法单词组成的句子合法。
  
- 全部单词性别相同的句子合法。
  
- 可以没有形容词和动词，但必须有且只有一个名词。
  
- 三个词性的单词出现顺序必须是 形容词 -> 名词 -> 动词。
  

然后把这些写在代码里，稍微调试一下，就轻松解决了。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

int n, v, l(-1), cnt;
string s;

int num(string s){//判断单词类型
	string t;int l = s.size();
	if(l < 3) return 0;
	t = s.substr(l - 3);
	if(t == "etr") return 3;
	if(l < 4) return 0;
	t = s.substr(l - 4);
	if(t == "lios") return 1;
	if(t == "etra") return 4;
	if(l < 5) return 0;
	t = s.substr(l - 5);
	if(t == "liala") return 2;
	if(l < 6) return 0;
	t = s.substr(l - 6);
	if(t == "initis") return 5;
	if(t == "inites") return 6;
	return 0;
}

int main(){
	while(cin >> s){
		++ cnt;
		int t = num(s);//保存类型
		if(!t){puts("NO");return 0;}//出现未知单词，NO
		if(l != -1 && (t & 1 != l)) {puts("NO");return 0;}//性别不一，NO
		l = t & 1;
		if((t == 1 || t == 2) && (n || v)) {puts("NO");return 0;}//出现过名词动词，又出现形容词，NO
		if((t == 3 || t == 4) && (n || v)) {puts("NO");return 0;}//出现过动词，或已经有名词，又出现名词，NO
		if((t == 5 || t == 6) && !n) {puts("NO");return 0;}//还没出现名词就出现动词，NO
		if(t == 3 || t == 4) n = 1;//存储名词是否出现过
		if(t == 5 || t == 6) v = 1;//存储动词是否出现过
	}
	if(!n && cnt != 1) {puts("NO");return 0;}//没出现过名词且单词数不为一，NO
	puts("YES");//否则YES
	return 0;
}
```

优雅结束。

---

## 作者：Cappuccino_mjj (赞：0)

一道模拟题。

---
## [题目传送门](https://www.luogu.com.cn/problem/CF113A)
题目意思：

给你一个句子，让你检查这个句子的语法是否正确。（语法请自行在题目中查看）

---

思路：

就是模拟。依次判断这个句子是否符合每一条语法即可。但是细节很多就因为细节我错了好多次！具体看代码注释。

---

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
string a[N];
int cnt;
bool fh(string s)//判断单词是否合法
{
	int len=s.size();
	s=" "+s;
	if(s[len]=='s'&&s[len-1]=='o'&&s[len-2]=='i'&&s[len-3]=='l')
		return 1;
	if(s[len]=='r'&&s[len-1]=='t'&&s[len-2]=='e')
		return 1;
	if(s[len]=='s'&&s[len-1]=='i'&&s[len-2]=='t'&&s[len-3]=='i'&&s[len-4]=='n'&&s[len-5]=='i')
		return 1;
	if(s[len]=='a'&&s[len-1]=='l'&&s[len-2]=='a'&&s[len-3]=='i'&&s[len-4]=='l')
		return 1;
	if(s[len]=='a'&&s[len-1]=='r'&&s[len-2]=='t'&&s[len-3]=='e')
		return 1;
	if(s[len]=='s'&&s[len-1]=='e'&&s[len-2]=='t'&&s[len-3]=='i'&&s[len-4]=='n'&&s[len-5]=='i')
		return 1;
	return 0;
}
bool fx(string s)//判断单词的性别
{
	int len=s.size();
	s=" "+s;
	if(s[len]=='s'&&s[len-1]=='o'&&s[len-2]=='i'&&s[len-3]=='l')
		return 1;
	if(s[len]=='r'&&s[len-1]=='t'&&s[len-2]=='e')
		return 1;
	if(s[len]=='s'&&s[len-1]=='i'&&s[len-2]=='t'&&s[len-3]=='i'&&s[len-4]=='n'&&s[len-5]=='i')
		return 1;
	if(s[len]=='a'&&s[len-1]=='l'&&s[len-2]=='a'&&s[len-3]=='i'&&s[len-4]=='l')
		return 0;
	if(s[len]=='a'&&s[len-1]=='r'&&s[len-2]=='t'&&s[len-3]=='e')
		return 0;
	if(s[len]=='s'&&s[len-1]=='e'&&s[len-2]=='t'&&s[len-3]=='i'&&s[len-4]=='n'&&s[len-5]=='i')
		return 0;
}
int fc(string s)//判断单词的词性
{
	int len=s.size();
	s=" "+s;
	if(s[len]=='s'&&s[len-1]=='o'&&s[len-2]=='i'&&s[len-3]=='l')
		return 1;
	if(s[len]=='r'&&s[len-1]=='t'&&s[len-2]=='e')
		return 2;
	if(s[len]=='s'&&s[len-1]=='i'&&s[len-2]=='t'&&s[len-3]=='i'&&s[len-4]=='n'&&s[len-5]=='i')
		return 3;
	if(s[len]=='a'&&s[len-1]=='l'&&s[len-2]=='a'&&s[len-3]=='i'&&s[len-4]=='l')
		return 1;
	if(s[len]=='a'&&s[len-1]=='r'&&s[len-2]=='t'&&s[len-3]=='e')
		return 2;
	if(s[len]=='s'&&s[len-1]=='e'&&s[len-2]=='t'&&s[len-3]=='i'&&s[len-4]=='n'&&s[len-5]=='i')
		return 3;
}
int main()
{
	while(cin>>a[++cnt]);
	cnt--;
	int x=0,y=0;
	for(int i=1;i<=cnt;i++)
	{
		if(!fh(a[i]))//不合法直接输出NO
		{
			cout<<"NO";
			return 0;
		}
		if(fx(a[i]))x++;
		else y++;
	}
	if(!((!x&&y)||(x&&!y)))
	{//性别不一样输出NO
		cout<<"NO";
		return 0;
	}
	int num=0;
	if(cnt==1&&fh(a[1]))
	{
		cout<<"YES";
		return 0;
	}//只有一个合法单词输出YES
	if(cnt==2)
	{//只有两个单词的特殊情况
		if(fc(a[1])==1&&fc(a[2])!=2)
		{//第一个单词是形容词但是第二个单词不是名词
			cout<<"NO";
			return 0;
		}
		if(fc(a[1])==2&&fc(a[2])!=3)
		{//第一个单词是名词但是第二个单词不是动词
			cout<<"NO";
			return 0;
		}
		if(fc(a[1])==3)
		{//第一个单词是动词
			cout<<"NO";
			return 0;
		}
		cout<<"YES";
		return 0;
	}
	for(int i=2;i<cnt;i++)
	{
		if(fc(a[i])==1)
		{//如果当前单词是形容词
			if(fc(a[i-1])==1&&(fc(a[i+1])==1||fc(a[i+1])==2))
				continue;
			cout<<"NO";//如果形容词的上一个不是形容词或者形容词的下一个不是形容词或名词就输出NO
			return 0;
		}
		if(fc(a[i])==2)
		{//如果当前单词是名词
			if(fc(a[i-1])==1&&fc(a[i+1])==3)
				continue;
			cout<<"NO";//如果名词的上一个不是形容词或者名词的下一个不是动词就输出NO
			return 0;
		}
		if(fc(a[i])==3)
		{//如果当前单词是动词
			if((fc(a[i-1])==3||fc(a[i-1])==2)&&fc(a[i+1])==3)
				continue;
			cout<<"NO";//如果动词的上一个不是动词或名词，或者动词的下一个不是动词就输出NO
			return 0;
		}
	}
	for(int i=1;i<=cnt;i++)
		if(fc(a[i])==2)
			num++;//判断有多少个名词
	if(num!=1&&cnt>1)
	{//有多个名词就输出NO
		cout<<"NO";
		return 0;
	}
	cout<<"YES";//改句子符合语法，输出YES
	return 0;
}
```

---

完美撒花~

---

## 作者：blsya23a2 (赞：0)

## 分析
由题知，这道题在遍历输入时只有 7 种状态：

- 没有开始
- 阳性

  1. 输入了形容词
  1. 输入了名词
  1. 输入了动词
- 阴性
  同阳性

所以，我们可以设置一个变量，记录当前的状态，然后根据状态判断下一个单词是否合法。
- 没有开始，下一个单词可以为形容词或名词
- 阳性

  1. 状态 1，下一个单词可以为阳性形容词或名词
  2. 状态 2，下一个单词可以为阳性动词
  3. 状态 3，下一个单词可以为阳性动词
- 阴性
  1. 状态 1，下一个单词可以为阴性形容词或名词
  2. 状态 2，下一个单词可以为阴性动词
  3. 状态 3，下一个单词可以为阴性动词

注意，结束句子时必须是名词或动词。另外，输入只有一个任意合法单词时也特判为合法。
## 代码
```python
a = input().split()
c = 5 #设置一个变量，记录当前的状态
for b in a:
    if c == 5:
        if len(a) == 1: 
            if b[-4:] == 'lios' or b[-5:] == 'liala' or b[-3:] == 'etr' or b[-4:] == 'etra' or b[-6:] == 'initis' or b[-6:] == 'inites': #输入只有一个任意合法单词时也特判为合法
                c = 0
        elif b[-4:] == 'lios':
            c = 1
        elif b[-5:] == 'liala':
            c = 2
        elif b[-3:] == 'etr':
            c = 3
        elif b[-4:] == 'etra':
            c = 4
        else:
            break
    elif c == 1:
        if b[-4:] == 'lios':
            continue
        elif b[-3:] == 'etr':
            c = 3
        else:
            c = 5
            break
    elif c == 2:
        if b[-5:] == 'liala':
            continue
        elif b[-4:] == 'etra':
            c = 4
        else:
            c = 5
            break
    elif c == 3:
        if b[-6:] == 'initis':
            c = 6
        else:
            c = 5
            break
    elif c == 4:
        if b[-6:] == 'inites':
            c = 7
        else:
            c = 5
            break
    elif c == 6:
        if b[-6:] == 'initis':
            continue
        else:
            c = 5
            break
    else:
        if b[-6:] == 'inites':
            continue
        else:
            c = 5
            break
if c in (1,2,5): #结束句子时必须是名词或动词
    print('NO')
else:
    print('YES')
```
upd：提高了代码可读性（加了几个空格）

---

## 作者：liangbob (赞：0)

### CF113A 题解

#### 思路分析

模拟题。

首先，我们需要反复多次判断词性，于是可以把它封装成一个函数。

然后我们来逐个满足要求：

> 1. 每一个单词都以上述结尾来结尾，也就是说，不以上述的结尾来结尾的单词不符合语法。

这个在输入时就可以判断了，如果判断出词的种类啥也不是，那么就不满足，否则满足。

> 2. 一个句子中所有单词的性别必须相同。

这个可以转换为：阴性和阳性不能同时出现。

这个好办，开两个变量记录阴性阳性是否出现过，都出现就不满足，否则满足。

> 3. 单独一个合法单词也可以组成一个合法的句子

这个特判一下词数为一的情况就可以了。

> 4. 每个句子必须按照以下顺序书写：$0$ 个或多个形容词、$1$ 个名词、$0$ 个或多个动词。

这是难点。

我的思路是：以名词为分界点。

先遍历一遍，找到名词的位置。

然后再在前面和后面扫一遍，判断是否有其它词性的词出现就可以了。

#### 代码

```cpp
#include <iostream>
#include <string>
#define IL inline
using namespace std;
const int N = 1e5 + 10;

bool g; //词的性别，1阳性，2阴性 
int t; //词的种类，1 形容词，2名词，3动词 
int tp[N]; //每个词的种类 

void counting(string x) //判断一个词的词性 
{
	// x.substr(x.size()-i,i) 代表取 x 的末 i 位 
	if(x.size() >= 3)
	{
		string a = x.substr(x.size() - 3, 3);
		if(a == "etr")
		{
			g = true;
			t = 2;
			return;
		}
	}
	if(x.size() >= 4)
	{
		string b = x.substr(x.size() - 4, 4);
		if(b == "lios")
		{
			g = true;
			t = 1;
			return;
		}
		if(b == "etra")
		{
			g = false;
			t = 2;
			return;
		}
	}	
	if(x.size() >= 5)
	{
		string c = x.substr(x.size() - 5, 5);
		if(c == "liala")
		{
			g = false;
			t = 1;
			return;
		}
	}
	if(x.size() >= 6)
	{
		string d = x.substr(x.size() - 6, 6);
		if(d == "initis")
		{
			g = true;
			t = 3;
			return;
		}
		if(d == "inites")
		{
			g = false;
			t = 3;
			return;
		}		
	} 
	t = -1; //啥也不是 
	return;
}

int main()
{
	int q = 0, cnt = 0;
	bool cxt = false, cxf = false; //阴性是否出现，阳性是否出现 
	string s;
	while(cin >> s)
	{
		counting(s); //判断词性与种类 
		if(t == -1) //不合法（啥也不是） 
		{
			cout << "NO" << endl;
			return 0;
		} 
		else
		{
			cnt++;
			tp[cnt] = t; //记录该词的词性 
			if(g) cxt = true; //阳性 
			else cxf = true; //阴性 
		}
	}
	if(cnt == 1) //单独一个合法单词也可以组成一个合法的句子
	{
		cout << "YES" << endl;
		return 0;
	}
	if(cxt && cxf) //阴性阳性都出现过 
	{
		cout << "NO" << endl;
		return 0;
	}
	int mc = 0;
	int idx = 0;
	for(int i = 1;i <= cnt;i++)
	{
		if(tp[i] == 2) //如果名词 
		{
			mc++; //统计个数 
			idx = i; //记录最后一次出现的位置 
			if(mc >= 2) //多于一个 
			{
				cout << "NO" << endl;
				return 0;
			}
		}
	}
	if(mc == 0) //没有名词 
	{
		cout << "NO" << endl;
		return 0;
	}
	int ct = 0, cq = 0;
	for(int i = 1;i < idx;i++) //在名词前面找 
	{
		cq++; //总词数 
		if(tp[i] == 1)
		{
			ct++; //形容词数 
		}
	}
	if(cq != ct) //名词前面不全是形容词 
	{
		cout << "NO" << endl;
		return 0;
	}
	ct = cq = 0;
	//以下代码逻辑同上 
	for(int i = idx + 1;i <= cnt;i++)
	{
		cq++;
		if(tp[i] == 3)
		{
			ct++;
		}
	}
	if(cq != ct)
	{
		cout << "NO" << endl;
		return 0;
	}
	cout << "YES" << endl;
	return 0;
}
```



---

## 作者：Allanljx (赞：0)

## 题意
* $0$个或多个形容词、$1$个名词、$0$个或多个动词。
* 如果有动词就必须有$1$个名词。
* 所有单词要么都是阴性，要么都是阳性。
* 所有单词都的结尾必须是这六种结尾的一种。

如果满足上述条件就输出```YES```，否则输出```NO```。

## 思路
根据题意模拟，具体细节见代码注释。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string a;
int book[2][3],cnt,b[100005];//book记录性别和词性，cnt记录单词数量 ，b记录第cnt个单词的词性 
signed main()
{
	while(cin>>a)//一个一个单词输入 
	{
		int len=a.length();//取长度 
		if(len>=4&&a[len-1]=='s'&&a[len-2]=='o'&&a[len-3]=='i'&&a[len-4]=='l')//阳性形容词 
		{
			book[0][0]++;
			b[++cnt]=1;
		}
		else if(len>=5&&a[len-1]=='a'&&a[len-2]=='l'&&a[len-3]=='a'&&a[len-4]=='i'&&a[len-5]=='l')//阴性形容词 
		{
			book[1][0]++;
			b[++cnt]=1;
		}
		else if(len>=3&&a[len-1]=='r'&&a[len-2]=='t'&&a[len-3]=='e')//阳性名词 
		{
			book[0][1]++;
			b[++cnt]=2;
		}
		else if(len>=4&&a[len-1]=='a'&&a[len-2]=='r'&&a[len-3]=='t'&&a[len-4]=='e')//阴性名词 
		{
			book[1][1]++;
			b[++cnt]=2;
		}
		else if(len>=6&&a[len-1]=='s'&&a[len-2]=='i'&&a[len-3]=='t'&&a[len-4]=='i'&&a[len-5]=='n'&&a[len-6]=='i')//阳性动词 
		{
			book[0][2]++;
			b[++cnt]=3;
		}
		else if(len>=6&&a[len-1]=='s'&&a[len-2]=='e'&&a[len-3]=='t'&&a[len-4]=='i'&&a[len-5]=='n'&&a[len-6]=='i')//阴性动词 
		{
			book[1][2]++;
			b[++cnt]=3;
		}
		else//不是Petya单词 
		{
			cout<<"NO\n";return 0;
		}
		for(int i=0;i<len;i++) a[i]='0';
		if(getchar()=='\n') break;
	}
	if(cnt>1&&book[0][1]+book[1][1]!=1)//没有名词 
	{
		cout<<"NO\n";return 0;
	}
	int d;//上个词的词性 
	d=b[1];
	for(int i=2;i<=cnt;i++)
	{
		if(d==1)//上个词是形容词 
		{
			if(b[i]==3)//跳过了名词，直接是动词 
			{
				cout<<"NO\n";return 0;
			}
			d=b[i];
		}
		else if(d==2)//上个词是名词 
		{
			if(b[i]==2||b[i]==1)//名词后只能出现动词 
			{
				cout<<"NO\n";return 0;
			}
			d=b[i];
		}
		else if(d==3)//上个词是动词 
		{
			if(b[i]!=3)//动词后只能是动词 
			{
				cout<<"NO\n";return 0;
			}
		}
	}
	if(book[0][0]+book[0][1]+book[0][2]!=0&&book[1][0]+book[1][1]+book[1][2]!=0)//阳性和阴性都有 
	{
		cout<<"NO\n";return 0;
	}
	cout<<"YES\n";return 0;
    return 0;
}
```


---

