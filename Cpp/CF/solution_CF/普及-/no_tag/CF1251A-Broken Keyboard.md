# Broken Keyboard

## 题目描述

Recently Polycarp noticed that some of the buttons of his keyboard are malfunctioning. For simplicity, we assume that Polycarp's keyboard contains $ 26 $ buttons (one for each letter of the Latin alphabet). Each button is either working fine or malfunctioning.

To check which buttons need replacement, Polycarp pressed some buttons in sequence, and a string $ s $ appeared on the screen. When Polycarp presses a button with character $ c $ , one of the following events happened:

- if the button was working correctly, a character $ c $ appeared at the end of the string Polycarp was typing;
- if the button was malfunctioning, two characters $ c $ appeared at the end of the string.

For example, suppose the buttons corresponding to characters a and c are working correctly, and the button corresponding to b is malfunctioning. If Polycarp presses the buttons in the order a, b, a, c, a, b, a, then the string he is typing changes as follows: a $ \rightarrow $ abb $ \rightarrow $ abba $ \rightarrow $ abbac $ \rightarrow $ abbaca $ \rightarrow $ abbacabb $ \rightarrow $ abbacabba.

You are given a string $ s $ which appeared on the screen after Polycarp pressed some buttons. Help Polycarp to determine which buttons are working correctly for sure (that is, this string could not appear on the screen if any of these buttons was malfunctioning).

You may assume that the buttons don't start malfunctioning when Polycarp types the string: each button either works correctly throughout the whole process, or malfunctions throughout the whole process.

## 样例 #1

### 输入

```
4
a
zzaaz
ccff
cbddbb
```

### 输出

```
a
z

bc
```

# 题解

## 作者：lianchanghua (赞：2)

#### 题目大意：
现在键盘上有 $26$ 个字母对应的按键。出现问题的按键按下一次会出现**两个**相同的该字母。现在给你一个字符串，请你判断有哪些字母所对应的按键一定是正常工作的。

#### 审题：
请注意：这里按键如果出问题了，只会重复**两遍**，如果是奇数遍的话，如**三遍**是不算出现问题的按键的，这一点，我发现题解区有好多人没有注意。所以在这里申明一下。

#### 思路：
我们可以先数出重复的字母的个数 $n$，然后再判断这个 $n$ 是否为奇数，如果是奇数，就是我们的其中一个答案，否则就继续往下搜。

#### 代码实现：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool f[30];
signed main(){
	ios::sync_with_stdio(false);
    string s;
    int T;
    cin>>T;
    while(T--){
        cin>>s;
        memset(f,0,sizeof(f));
        int l=s.size()-1;
        for(int i=0;i<=l;i++){
        	int j=i;
            while(s[i]==s[j])	j++;//数出重复的个数
            if((j-i)%2==0);
			else				f[s[i]-'a']=1;
			i=j-1;//这里注意：由于i后面要++,所以这里是j-1而不是j
        }
        for(int i=0;i<26;i++)	if(f[i]==1)	cout<<char(i+'a');
        cout<<"\n";
    }
    return 0;
}

```

---

## 作者：_tommysun_ (赞：2)

**思路**  
由于每一个按钮要么在整个过程中都可以正常工作，要么在整个过程中都出现问题，因此如果这个按钮坏了，在整个字符串中这个字符是不会单独出现的。所以只需要记录有多少个字符单独出现过即可。    
**代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    string s;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>s;
        bool flag[26]={0}; //记录单独出现的字符。
        for(int len=0;len<s.size();len++){
            if(s[len]==s[len+1]){ //如果连续出现就跳过。
                len++;
            }
            else flag[s[len]-'a']=1; //如果是单独出现，就记录。
        }
        for(int j=0;j<26;j++){
            if(flag[j]==1) {cout<<char(j+'a');} //输出。
        }
        cout<<endl;
    }
    return 0;
}
```


---

## 作者：夙愿扬 (赞：2)

### CF1251A
现在键盘上有$26$个字母对应的按键，一些可以正常工作，一些出现了问题。出现问题的按键按下一次会出现两个相同的该字母。如果$c$出现问题，那么我们按下它就会出现$cc$。现在给你一个字符串，请你判断有哪些字母所对应的按键一定是正常工作的。

------------

先读入字符串（本人认为用cin读入是最没有锅的），然后把字符串扫一遍，主要判断连续出现的字母个数有没有为奇数的，我的处理方法是，如果有两个连续的字母，就直接循环++跳过，然后如果落单就是奇数，同理如果只有一个单独的字母也直接统计，加入一个字符数组内，然后因为要按字典序输出要排序，输出前去重就可以了，具体细节见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main ()
{
    string s;
    int n,m;
    char c[510];
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        m=0;//多测不清空，爆零两行泪
        cin>>s;
        for(int j=0;j<=s.size()-1;j++)
        {
            if(s[j]==s[j+1])//判断是否连续
            j++;
            else
            c[++m]=s[j];//统计进数组
        }
        sort(c+1,c+1+m);//排序
        c[m+1]='0';//思考一下，去重时防止出锅
        for(int j=1;j<=m;j++)
        {
            if(c[j]!=c[j+1])//去重输出
            printf("%c",c[j]);
        }
        cout<<endl;
    }
    return 0;
} 
```
###### The End--2019/10/27 20:30

---

## 作者：Clyfort (赞：1)

# Solution
由题目可知，$t \le 100, |s| \le 500$，看这数据范围，很容易想到直接模拟。

怎样模拟呢，举一个例子：

`a b b c d d`

![](https://hydro.ac/file/3261/CF1251A1.PNG)

首先从第一个字符开始比较，这时 $i = 0$，发现 $s_i \neq s_{i+1}$，则把 $s_i$ 计入答案。

![](https://hydro.ac/file/3261/CF1251A2.PNG)

此时 $i = 1$，发现 $s_i = s_{i +1}$，跳过。跳过需要跳过两轮循环，即再循环的基础上再 $i = i + 1$。

![](https://hydro.ac/file/3261/CF1251A3.PNG)

跳过后 $i = 3$，发现 $s_i \neq s_{i+1}$，则把 $s_i$ 计入答案。

![](https://hydro.ac/file/3261/CF1251A4.PNG)

此时 $i = 4$，发现 $s_i = s_{i + 1}$，$i = i + 1$。

跳过后，$i = 6$，则退出循环。此时答案为 `ac`。

注意，题目要求按照字母顺序输出，所以方便起见，可以用 `set` 维护答案。

# Code
```c++
#include <bits/stdc++.h>
using namespace std;

set <char> ans;

void solve()
{
    ans.clear();
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); i ++)
    {
        if (s[i] != s[i + 1])
            ans.insert(s[i]);
        else
            i ++;
    }
    for (auto c : ans)
        cout << c;
    cout << endl;
}

int main()
{
    int tt = 1;
    cin >> tt;
    while (tt --)
        solve();
    return 0;
}
```

---

## 作者：_Lionel (赞：0)

## 思路：
思路：

- 当输入的字符串长度小于 $2$ 时，可以直接输出。

- 当输入的字符串长度大于等于 $2$ 时，可以利用 $0-25$ 来计数，最后按顺序查表输出。
## Code:
```cpp
#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
using namespace std;
int main() {
	char a[100006];
	int k = 0;
	scanf ("%d", &k);
	for (int i = 0; i < k; i ++) {
		int n[26] = {0};//建立一个用于查表的数组
		scanf ("%s", a);
		int lase = strlen(a);
		if (lase < 2) {//如果字母个数<2，则这个键一定是好的
			printf ("%s\n", a);
			continue;
		}
		for (int j = 0; j < lase; ) {
			if (a[j] == a[j + 1]) {//连续的就跳过
				j += 2;
				continue;
			}
			n [a[j] - 'a'] ++;//不是连续的存储，说明是好的
			j ++;
		}
		for (int j = 0; j < 26; j ++) {
			if (n [j] >= 1) {//查表
				printf ("%c", j + 'a');//输出
			}
		}
		printf ("\n");
	}
	return 0;//完美结束
}
```


---

## 作者：Accteped (赞：0)

### 思路
因为题目说只要这个按键是坏的，只要按一下就会出现两个字母

所以我们只要判断是否有单独出现的字母，若有，就判定这个字母没问题

算法:模拟
***
### Code
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;//n组数据 
	string s;
	while(n--){
		cin>>s;
		int p[30]={};//统计26个字母按键是否正常
		for(int i=0;i<s.size();++i){//遍历
			if(s[i]==s[i+1]){//如果有两个一样的字母挨着出现
				i++;//跳过这两个字母 
				continue;
			}//如果有两个相同的字母就跳过 
			p[s[i]-'a']=1;//单独出现就说明是正常的 
		}
		for(int i=0;i<26;++i){
			if(!p[i])continue;//不正常就跳过 
			cout<<char(i+97);//是正常就输出 
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：ShineEternal (赞：0)

[$My\ blog$](https://blog.csdn.net/kkkksc03)

## description:

现在键盘上有$26$个字母对应的按键，一些可以正常工作，一些出现了问题。出现问题的按键按下一次会出现两个相同的该字母。如果$c$出现问题，那么我们按下它就会出现$cc$。现在给你一个字符串，请你判断有哪些字母所对应的按键一定是正常工作的。

## solution：

~~我们发现，这像极了直接复制$LaTeX$发生的错误~~

---

运用桶排，巧妙的跳过重复计算的字符。

但是题目里面还是有些坑的：

* 输出时要按ASCII码由小到大输出

* 正常工作的标准是什么？刚开始我以为是出现了奇数次。但这时我默认将同一种字符都连在一起了，所以其实是要手动判断跳过连着的字符。

```cpp
if(s[i]==s[i+1])i++;

```




## code:



```cpp
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
#include<iostream>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);
	while(n--)
	{
		map<char,int>m;
		char s[1005];
		cin>>s;
		int str=strlen(s);
		for(int i=0;i<str;i++)
		{
			if(s[i]==s[i+1])i++;
			else
			m[s[i]]=1;
		}
		for(int i='a';i<='z';i++)
		{
			if(m[i]==1)printf("%c",i);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：盧鋅 (赞：0)

？？？

水题一个，很明显一个桶排。
```cpp
if(a[i]==a[i+1])i++;
else can[a[i]-'a']=1;
```
加上这个特判就好了。

纯模拟，原理就是题干。

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
using namespace std;
bool can[100];
string a;
signed main(){
	int r;
	cin>>r;
	while(r--){
		memset(can,0,sizeof(can));
		cin>>a;
		for(int i=0;i<a.length();++i){
			if(a[i]==a[i+1])i++;
			else can[a[i]-'a']=1;
		}
		for(int i=0;i<=30;i++)if(can[i])cout<<char(i+'a');
		puts("");
	}
	return 0;
} 
```



---

