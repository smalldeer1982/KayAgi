# Yes-Yes?

## 题目描述

你和 Polycarp 进行了交谈，并向他提出了一个问题。你知道，当他想回答“yes”时，他会连续重复多次 Yes。

由于噪音的影响，你只听到了答案中的一部分——即他的回答的某个子串。也就是说，如果他的回答是 YesYes，那么你可能会听到 esY、YesYes、sYes、e，但你不会听到 Yess、YES 或 se。

请判断给定的字符串 $s$ 是否是 YesYesYes...（Yes 连续重复多次）的一个子串。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
12
YES
esYes
codeforces
es
se
YesY
esYesYesYesYesYesYe
seY
Yess
sY
o
Yes```

### 输出

```
NO
YES
NO
YES
NO
YES
YES
NO
NO
YES
NO
YES```

# 题解

## 作者：yeshubo_qwq (赞：1)

做法多种多样。

## Solution1

题目中每个字母前的字母顺序是固定的，可以据此判断。

```cpp
void go(){
    cin>>S,n=S.size();
    for (i=0;i<n;i++)
        if (S[i]!='Y' && S[i]!='e' && S[i]!='s'){
            cout<<"NO\n";
            return ;
        }
    //YesYes
    for (i=1;i<n;i++)
        if ((S[i]=='Y' && S[i-1]!='s') || (S[i]=='s' && S[i-1]!='e') || (S[i]=='e' && S[i-1]!='Y')){
            cout<<"NO\n";
            return ;
        }
    cout<<"YES\n";
}
```


## Solution2

可以直接构造出 `YesYes...`，然后判断用 `find` 函数判断是否是它的子串。

```cpp
string S,Yes="YesYesYesYesYesYesYesYesYesYesYesYesYesYesYesYesYesYes";
void go(){
    cin>>S;
    cout<<(Yes.find(S)==string::npos?"NO\n":"YES\n");
}
```


---

## 作者：ShanCreeperPro (赞：1)

## CF1759A Yes-Yes? 題解

### 题意

给定 $t$ 个字符串，求该字符串是否是 `YesYesYes...`（多个 Yes） 的字串。

### 解析

我们可以使用 `std::string` 来解决问题。

在其中，有一个神奇的函数，叫做 `find(std::string)`，可以查询一个字符串中是否包含括号中的字串，若没有则返回 `string::nope`。

所以，我们可以定义一个常量 `S`，存 `YesYesYes...`，然后使用 `S.find(str)!=string::nope` 来判断是否包含字串。

### 代码

核心代码如下：

```cpp
int t;
std::string str;
const std::string S = "YesYesYesYesYesYesYesYesYesYesYesYesYesYesYesYesYesYesYesYes";
// 题目中 S 的长度最长为 50
for(int i = 1; i <= t; i++){
	getline(std::cin, str);
    puts(S.find(str) != string::nope ? "Yes" : "No);
}
```

---

## 作者：封禁用户 (赞：0)

这是本蒟蒻的第 $41$ 篇题解，CF1759A。

题目可以看成在一个特别长的由无数个 `Yes` 组成的字符串中寻找一个输入的字符串，能找到就输出 `YES`，反之输出 `NO`。

注意到 $1 \le |s| \le 50$，那么就建立一个打表字符串即可。

代码：（这里使用了一个 `string::npos`，是 `string` STL 库中的一个寻找子串函数 `*.find(*)` 中找不到的返回标志。）

```cpp
#include <bits/stdc++.h>
#define notfound string::npos
using namespace std;

string kkk="YesYesYesYesYesYesYesYesYesYesYesYesYesYesYesYesYesYesYes";
int rin;

int main(){
    cin>>rin;
    for (string s; rin; rin--){
        cin>>s;
        if (kkk.find(s)==notfound) cout<<"NO"<<endl; // npos
        else cout<<"YES"<<endl;
    }
    return 0;
}
```

---

## 作者：Engulf (赞：0)

> 给定字符串 $s$，判断其是否为多个 $\tt{Yes}$ 连接而成的字串。

按照题意，先创建一个字符串 $t$ 为多个 $\tt{Yes}$ 连接而成，且 $|t| > |s|$，然后判断 $s$ 是不是 $t$ 的字串即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int tt;
	cin >> tt;
	while (tt -- )
	{
		string s;
		cin >> s;
		string t;
		while (t.size() < s.size()) t += "Yes";
		t += "Yes";
		puts(t.find(s) != string::npos ? "YES" : "NO");
	}
	return 0;
}
```

---

## 作者：VitrelosTia (赞：0)

题链：[CF](https://codeforces.com/contest/1759/problem/A)/[Luogu](https://www.luogu.com.cn/problem/CF1759A)

### 题意
给你一个字符串，求这个字符串是否是 `YesYesYesYesYes……` 的子串。

### 思路
不妨先把问题简单化，认为字符串一定是从 `Y` 开始的。这种情况下代码的主体部分是很显然的。
```
for(int i=0;i<s.size();i++){
		if((i%3==0)&&s[i]!='Y'){cout<<"NO"<<endl;return;}
		if((i%3==1)&&s[i]!='e'){cout<<"NO"<<endl;return;}
		if((i%3==2)&&s[i]!='s'){cout<<"NO"<<endl;return;}
	}
```
但是问题没有这么简单，有可能在 `Y` 前面还有 `es` 或者 `s`，这都有可能是符合条件的。但是也就只有这两种了，分别特殊处理就可以了。

假如最前面是 `es`，事实上只需要在遍历字符串时从第三个字符开始就可以了，`s` 的情况同理，从第二个开始即可。

特别的，这种情况下判不到字符串就是 `e` 的情况，所以在最开始特判即可。

显然每次判断特殊情况后分别操作有些麻烦，不妨用临时变量记录这个字符串应该从第几个开始遍历。

### code
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
int t,n,x,a[10005];
string s;
void solve(){
	int tt=0;//临时变量记录从第几个开始遍历，默认为0
	cin>>s;
	if(s=="e"){cout<<"YES"<<endl;return;}//特判
	if(s[0]=='e'&&s[1]=='s') tt=2;//es 开头的情况
	else if(s[0]=='s') tt=1;//s 开头的情况
	for(int i=tt;i<s.size();i++){
		int tmp=i-tt;//由于开始遍历的位置变了，所以需要多减一次tt
		if((tmp%3==0)&&s[i]!='Y'){cout<<"NO"<<endl;return;}
		if((tmp%3==1)&&s[i]!='e'){cout<<"NO"<<endl;return;}
		if((tmp%3==2)&&s[i]!='s'){cout<<"NO"<<endl;return;}
		//任何一个位置不满足都要直接输出NO
	}
	cout<<"YES"<<endl;//最后还没有输出NO就输出YES
}
int main(){
	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	cin>>t;
	while(t--) solve(); 
}

```


---

