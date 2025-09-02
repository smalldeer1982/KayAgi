# [GCJ 2019 Qualification] Foregone Solution

## 题目描述

有人刚刚赢得了 Code Jam 彩票，我们需要支付给他们 $N$ 个 jamcoin！然而，当我们尝试打印一张超大支票时遇到了问题。$N$ 是一个整数，其中至少包含一个数字 $4$，而我们的超大支票打印机上的 $4$ 键坏了。

幸运的是，我们有一个解决办法：我们将给获奖者发送两张金额为正整数 $A$ 和 $B$ 的支票，使得 $A$ 和 $B$ 都不包含数字 $4$，并且 $A + B = N$。请帮助我们找到任意一组满足条件的 $A$ 和 $B$。

## 说明/提示

**样例解释**

在样例第 1 个测试用例中，注意 $A$ 和 $B$ 可以相同。唯一其他可能的答案是 1 3 和 3 1。

**数据范围**

- $1 \leq T \leq 100$。
- $N$ 的数字中至少有一个是 $4$。

**测试点 1（6 分，可见）**

- $1 < N < 10^5$。

**测试点 2（10 分，可见）**

- $1 < N < 10^9$。

解决前两个测试点即可获得大部分分数。第三个测试点仅额外给 1 分，适合挑战和炫耀！

**测试点 3（1 分，隐藏）**

- $1 < N < 10^{100}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
4
940
4444```

### 输出

```
Case #1: 2 2
Case #2: 852 88
Case #3: 667 3777```

# 题解

## 作者：chenzefan (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P13102)
## 前言
构造的黄题，今天刚好复习，竟然发现这题既简单又可以写题解，来水。
## 思路
题意：将 $T$ 个整数 $N$，对于每个 $N$，将其拆成两个不含 $4$ 的数相加。

注意到 $1 < N < 10^{100}$，所以立刻使用**字符串**存数。定义整数 $N$ 用字符串 $s$ 来表示。

对于 $s$ 的第 $i$ 位，可以分 $2$ 中状态来讨论：

- 若 $s_i$ 不是字符 $4$，则可以让一个数为 $0$，另一个是 $s_i$。
- 若 $s_i$ 是字符 $4$，则可以直接拆分，拆成 $2+2$ 或 $1+3$。

于是可以得到最后答案的两个数。

又因为可以涉及到前导零问题，所以要对答案进行去前导零操作。

于是可以得到代码。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	for(int j=1;j<=t;j++){
		string s,ans1="",ans2="";
		cin>>s;
		for(int i=0;i<s.size();i++){
			if(s[i]!='4') ans1+='0',ans2+=s[i];
			else ans1+='2',ans2+='2';
		}
		while(ans1[0]=='0') ans1.erase(0,1);
		cout<<"Case #"<<j<<": "<<ans1<<" "<<ans2<<"\n";
	} 
	return 0;
}

```
~~顺便夸赞一下这题的满分分数。（$17$ 分？）~~   
撒花！

---

## 作者：lihaojun120113 (赞：3)

### 前置准备

高精度。

### 题目解析与注意事项

> **测试集 3 (1 分，隐藏)**
> -   $1 < N < 10^{100}$。

于是我们判断算法为**高精度**。

由于 $N$ 包含至少一个 $4$，我们可以通过以下方式构造 $A$ 和 $B$：

1.**遍历 $N$ 的每一位：**
如果当前位是 $4$，则在 $A$ 中对应位设为 $1$，在 $B$ 中对应位设为 $3$；否则，在 $A$ 和 $B$ 中保留原数字。

2.**确保 $A$ 和 $B$ 都不为 $0$：**
由于 $N$ 至少有一个 $4$，$A$ 和 $B$ 至少有一位是 $2$，因此不会出现 $0$。(但本篇代码考虑了这个情况来保证思维闭环)

**注意**：高精度的前导零要去掉。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
void f(int x){
	string y;
	cin>>y;
	string A,B;
	for(int i=0;i<y.size();i++){
		char ch=y[i];
		if(ch=='4'){
			A+='2';
			B+='2';
		}else{
			A+=ch;
			B+='0';
		}
	}
	bool bj=0;
	for(int i=0;i<y.size();i++){
		char ch=B[i];
		if(ch!='0'){
			bj=1;
			break;
		}
	}
	if (bj) {
	    int top=0;
	    while(top<B.size()&&B[top]=='0'){
	        top++;
	    }
	    B=B.substr(top);
	}else{//原则上是不会出现的，但要有思维闭环 
    	B="0";
	}	
	cout<<"Case #"<<x<<": "<<A<<" "<<B<<endl;
}
int main(){
	cin>>T;
	for(int i=1;i<=T;i++){
		f(i);
	}
	return 0;
}
```

### 结束语

欢迎大家为本题解提出宝贵意见！

---

## 作者：huhengrui2013 (赞：2)

### 题解：P13102 [GCJ 2019 Qualification] Foregone Solution

~~吐槽：这题哪里黄了，这不大水题吗。~~

[传送门](https://www.luogu.com.cn/problem/P13102)

### 思路：

对于每个数字 $4$，将他拆成两个 $2$，让字符串 $a$，$b$ 分别加上；其余字符则让 $a$ 加上，$b$ 若不为空，加 $0$。

最后特判 $b$ 若为空，把 $b$ 设为 $0$。
### AC Code:

```cpp
#include<bits/stdc++.h>

using namespace std;

int t;
int main(){
    cin>>t;
    for(int i=1;i<=t;i++){
        string s,a,b;
        cin>>s;
        cout<<"Case #"<<i<<": ";
        for(char c:s){
            if(c=='4'){//如果是数字 4，将他拆成两个 2
                a+='2';
                b+='2';
            }else{//其余字符让 a 加上，b 若不为空，加 0 
                a+=c;
                if(b!="") b+='0';
            }
        }
        if(b=="") b="0";//若 b 为空，设为零
        cout<<a<<" "<<b<<endl;
    }
}
```

---

## 作者：_hud (赞：1)

# 题解：[P13102 \[GCJ 2019 Qualification\] Foregone Solution](https://www.luogu.com.cn/problem/P13102)

## 思路

简单构造题。

观察到数据范围 $N < 10^{100}$，故不难想到用字符串存储。由题意，$A$ 和 $B$ 中都不能出现 $4$，故我们从高位至低位遍历 $N$ 的每一位，若为 $4$ 则将其拆解（这里我将其拆解为 $1$ 和 $3$）。

那么这道题就迎刃而解了。还有一些实现的细节，具体可以看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T; cin >> T;
    for(int c = 1; c <= T; ++c) {
        string s, t = ""; cin >> s;
        bool f = 0; // f 表示 t 是否为空
        int len = s.length();
        for(int i = 0; i < len; ++i) {
            if(s[i] == '4') {
                s[i] = '1', t.push_back('3'); // 两者数字加起来和为 4 即可
                f = 1;
            } else if(f) t.push_back('0');
        }
        if(!f) t = "0"; // 特判
        cout << "Case #" << c << ": " << s << ' ' << t << '\n';
    }
    return 0;
}
```

---

## 作者：weapons (赞：1)

### 题意
  拆分一个数为两个数相加的形式，使这两个数每一位都不为 $4$ 。
### 思路
  既然每一位都不想让其为 $4$ ，那么遍历原字符串，如果有 $4$ ，则拆分为 $2$ $+$ $2$ 的形式，用两个字符串分别记录一个 $2$ 。一个还用来记录不为 $4$ 时的原串，另一个只记录为 $2$ 时的字符，其余位数用 $0$ 补齐，注意最高位不为零。详见代码：
  
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int t;
int main() {
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>s;
		int len=s.length();//原长
		string s1,s2;//s1记录包括拆分的2和原串，s2只记录拆分的2
		int pan=0;//避免最高位为零
		for(int j=0;j<len;j++){
			if(int(s[j]-'0')==4){
				s1+="2";
				s2+="2";// 拆分
				pan=1;
			}
			else{
				s1+=s[j];
				if(pan!=0){
					s2+="0";//不是最高位用0补齐
				}	
			}
		}
		cout<<"Case #"<<i<<": "<<s1<<' '<<s2<<endl;
	}
}
```

---

## 作者：Natural_Selection (赞：1)

# 题解：[P13102](https://www.luogu.com.cn/problem/P13102)

~~这题真的是黄题吗？感觉顶多一个橙~~

## 思路

首先，我们看到这题有 `Special Judge`，说明我们不一定一定要以样例为准，合理即可。

然后我们看到：
  -   $1 < N < 10^{100}$。
    
`long long` 肯定不行了，我们只能用 `string` 来存储。

所以我们可以选择一种最好想出的方法——见一个 $4$ 就拆成 $2+2$，剩下的全给 $a$，像这样（两个栗子）：

![picture](https://cdn.luogu.com.cn/upload/image_hosting/gjhb0k6e.png)

~~画的实在不咋的~~

然后去掉 $b$ 的前导零就行了。

## [AC](https://www.luogu.com.cn/record/223041897) Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    int k=0;
    while(t--){
        string str;
        cin>>str;
        printf("Case #%d: ",++k);  //格式
        string a="",b="";
        for(int i=0;i<str.size();i++){
            if(str[i]=='4'){
                a+='2',b+='2';
            }else{
                a+=str[i],b+='0';
            }
        }
        cout<<a<<" ";
        bool l=0;
        for(int i=0;i<b.size();i++){//b 会有前导零
            if(b[i]!='0') l=1;
            if(l==1){
                cout<<b[i];
            }
        }
        cout<<endl;
    }
    return 0;
}
```
第一次发黄题题解，若有不足多多包涵。

---

## 作者：yihang2011 (赞：0)

### [P13102 [GCJ 2019 Qualification] Foregone Solution](https://www.luogu.com.cn/problem/P13102)

注意到对于数字 $0$ 到 $9$，$4$ 可以拆分成 $1 + 3$，其它的数字都可以拆成 $0$ 与本数字。

拆分的前面数字作为第一个数 $a$，后面一个数作为第二个数 $b$，输出 $a$ 时记得消掉前导 $0$。

```cpp
#include <iostream>
using namespace std;

int T;
string A[] = {"0", "0", "0", "0", "1", "0", "0", "0", "0", "0"};
string B[] = {"0", "1", "2", "3", "3", "5", "6", "7", "8", "9"};

int main() {
    cin >> T;
    for (int i = 1; i <= T; i++) {
        string s;
        string a = "", b = "";
        cin >> s;
        for (int i = 0; i < s.size(); i++) {
            a += A[s[i] - '0'];
            b += B[s[i] - '0'];
        }
        printf("Case #%d: ", i);
        bool flag = false;
        for (int i = 0; i < a.size(); i++) {
            if (a[i] == '0' && !flag) {
                continue ;
            }
            flag = true;
            cout << a[i];
        }
        if (!flag) {
            cout << 0;
        }
        cout << " " << b << endl;
    }
    return 0;
}
```

[AC Record](https://www.luogu.com.cn/record/223451953)

---

## 作者：zhoujunchen (赞：0)

我们先假设 $A$ 和 $B$ 位数相同，并且相加没有进位。

那么 $A$ 和 $B$ 的位数等于 $N$ 的位数。

$N<10^{100}$ 必须使用字符串读入。

遍历 $N$，如果 $N_i=4$，那么 $a,b$ 中都不能有 $4$。


```cpp
if(s[i]=='4')a+="2",b+="2";//1 3,3 1 亦可
```

如果 $N_i$ 不为 $4$，那只需让 $A_i+B_i=N_i$ 即可。


```cpp
else a+=s[i],b+="0";
```

接下来就是给 $B$ 去前导零，然后按格式输出即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	for(int c=1;c<=t;c++){
		string s,a="",b="";
		cin>>s;
		for(int i=0;i<s.size();i++){
			if(s[i]=='4')a+="2",b+="2";//1 3,3 1 亦可
			else a+=s[i],b+="0";
		}
		string tmp=b;//去前导零，写的很屎
		reverse(tmp.begin(),tmp.end());
		while(tmp.size()&&tmp[tmp.size()-1]=='0')tmp.pop_back();
		if(tmp=="")tmp="0";
		reverse(tmp.begin(),tmp.end());
		b=tmp;
		cout<<"Case #"<<c<<": "<<a<<" "<<b<<"\n";
	}
	return 0;
}
```

---

## 作者：_fallen_leaves_ (赞：0)

[P13102 [GCJ 2019 Qualification] Foregone Solution](https://www.luogu.com.cn/problem/P13102)

## 题意
给你一个数，让你拆成两个数字，两个数字不能含有 $4$ 这个数字，让你输出一种方式。

## 思路
因为数字较大，我们可以用字符串存储两个数，依次遍历每个位上的数字，如果是 $4$，那就可以让两个数这个位上为 $1$ 和 $3$ 或 $2$ 和 $2$ 或 $3$ 和 $1$，如果不是 $4$，我们可以让一个数这个位上为 $0$，另一个数这个位上为这个数本身。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,step=0; 
char s[10005],s2[10005],s3[10005];
int main()
{
	cin>>t;
	while(t--)
	{
		step++;
		cin>>s;
		for(int i=0;i<strlen(s);i++)
		{
			if(s[i]=='4') s2[i]='1',s3[i]='3';
			else s2[i]=s[i],s3[i]='0';
		}
		cout<<"Case #"<<step<<": ";
		for(int i=0;i<strlen(s);i++) cout<<s2[i];
		cout<<" ";
		int flag=1;
		for(int i=0;i<strlen(s);i++)
			if(s3[i]=='0'&&flag) continue;
			else
			{
				flag=0;
				cout<<s3[i];
			}
		cout<<"\n";
	}
	return 0;
}

```

---

