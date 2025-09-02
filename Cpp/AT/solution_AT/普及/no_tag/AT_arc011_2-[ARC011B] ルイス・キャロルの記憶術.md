# [ARC011B] ルイス・キャロルの記憶術

## 题目描述

例如，莫扎特的生卒年可以通过记忆句子 `Mozart plays magic.` 来记住。其中，词 $ plays $ 转换成 $ 756 $，词 $ magic $ 转换成 $ 791 $，从而得到 $ 1756 $ 年至 $ 1791 $ 年。你的任务是，编写一个程序，根据输入的记忆句子，从左到右逐个词进行转换，输出转换得到的数字。

# 题解

## 作者：wizardMarshall (赞：2)

首先吐槽一波没修的题面，还找了原题来看……

[博客食用效果更佳](https://www.luogu.com.cn/blog/wizardMarshall/solution-at-arc011-2)

## 题意

句子由单词组成，所有辅音字母（不分大小写）可以转换成数字。转换规则见题面图片。求转换后的字符串。

## 思路

大致做法还是很简单的，枚举判断就好。坑点就在输出细节上。大致总结一下：

- 末尾换行

- 全是元音字母或标点符号的单词**不用输出**

- 末尾没有多余空格

由于这些原因，空格要放在每个单词前输出，且第一个不用输出。具体见代码注释。

## 代码

```

#include <bits/stdc++.h>
using namespace std;
bool is_ch(char c) {//判断合法函数
	if (c >= 'A' && c <= 'Z') {
		c -= 'A';
		c += 'a';
	}
	if (c >= 'a' && c <= 'z') {
		if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' && c != 'y') {
			return 1;
		}
	}return 0;
}
char change(char c) {//转换函数
	if (c >= 'A' && c <= 'Z') {
		c -= 'A';
		c += 'a';
	}
	if (c == 'b' || c == 'c') {
		return '1';
	}
	if (c == 'd' || c == 'w') {
		return '2';
	}
	if (c == 't' || c == 'j') {
		return '3';
	}
	if (c == 'f' || c == 'q') {
		return '4';
	}
	if (c == 'l' || c == 'v') {
		return '5';
	}
	if (c == 's' || c == 'x') {
		return '6';
	}
	if (c == 'p' || c == 'm') {
		return '7';
	}
	if (c == 'h' || c == 'k') {
		return '8';
	}
	if (c == 'n' || c == 'g') {
		return '9';
	}
	if (c == 'z' || c == 'r') {
		return '0';
	}
}
int main() {
	int n;
	cin >> n;
	int op = 0;
	for (int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		string t = "";//输出的数字序列
		int len = s.size();
		for (int i = 0; i < len; i++) {
			if (is_ch(s[i])) {
				t += change(s[i]);
			}
		}
		if (!t.empty()) {//如果是空序列就不用输出了
			if (op) {//前面加空格（除非是第一个非空的单词）
				putchar(' ');
			}op = 1;
			cout << t;
		}
	}cout << endl;//行末换行
	return 0;
}

```

---

## 作者：Gaoyx (赞：1)

### 题意
输入几个句子，如果这个单词是辅音就转化成数字。

转化方式请看[题面](https://www.luogu.com.cn/problem/AT_arc011_2)。

### 思路

很简单，就是模拟，问题主要出在一些细节。

例如： 

- 最后一个输出要 ***换行***（本蒟蒻因没换行反复去世）。

- 除最后一个输出其余输出要 ***空格***。

- 不区分 ***大小写***。

- 全都不符合条件的 ***不用输出***。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
int n, tot;
string a, s; 
int main()
{
	cin >> n;
	for(int k=1;k<=n;k++)
	{
		s = "";
		cin >> a;
		for(int i=0;i<a.size();i++)
		{
			if(a[i] >= 'A'&&a[i] <= 'Z') 
			{
				a[i] -= 'A';
				a[i] += 'a';
			}
			if(a[i] != 'a'&&a[i] != 'e'&&a[i] != 'i'&&a[i] != 'o'&&a[i] != 'u'&&a[i] != 'y'&&a[i] >= 'a'&& a[i] <= 'z')
			{
				if (a[i] == 'b' || a[i] == 'c')
				{
					s +='1';
				}
				if (a[i] == 'd' || a[i] == 'w') 
				{
					s += '2';
				}
				if (a[i] == 't' || a[i] == 'j')
				 {
					s += '3';
				}
				if (a[i] == 'f' || a[i] == 'q') 
				{
					s += '4';
				}
				if (a[i] == 'l' || a[i] == 'v') 
				{
					s +='5';
				}
				if (a[i] == 's' || a[i] == 'x') 
				{
					
					s += '6';
				}
				if (a[i] == 'p' || a[i] == 'm') 
				{
					s += '7';
				}
				if (a[i] == 'h' || a[i] == 'k') 
				{
					s += '8';
				}
				if (a[i] == 'n' || a[i] == 'g')
				 {
					s += '9';
				}
				if (a[i] == 'z' || a[i] == 'r') 
				{
					s += '0';
				}
			}
		}
		if(!s.empty()){
            if(tot) cout << " "; 
            else tot = 1;
            cout << s;
        }
	}
	cout << "\n"; //一定要换行 
}
```


---

## 作者：hmh100211 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_arc011_2)

# 题意分析：

~~先吐槽一波题面，是真的难看懂啊~~

给定单词数 $ n $ 和 $ n $ 个单词 $ w_1,w_2,\dots,w_n $， 两个**辅音**字母（除去 a，e，i，o，u，y 的字母）对应 $ 0 $ 到 $ 9 $ 的一个数，求单词经过转换后的结果。

这道题很水，但有一些坑点：

- 所有非辅音字符（**包括空格**）都将被忽略。

- 处理字母时**不区分大小写**。

- 输出末尾**无空格**，**要换行**。

# 思路：

了解了坑点，按题意模拟即可。

# AC Code：

```cpp
#include<bits/stdc++.h>
#define iff(a,b,c);\
if(w[i]==a||w[i]==b) ans+=c;
//用了宏定义来偷懒
using namespace std;
int n;
string w;
int main() {
    cin>>n;
    while(n--){
        string ans=""; //答案字符串
        cin>>w; //输入单词
        for(int i=0;i<w.length();i++){
            if(isupper(w[i])){
                w[i]+=('a'-'A'); //统一处理成小写字母
            }
        }
        for(int i=0;i<w.length();i++){
            if(!isalpha(w[i])||w[i]=='a'||w[i]=='e'||w[i]=='i'||w[i]=='o'||w[i]=='u'||w[i]=='y'){
                continue; //不是字母或是元音字母，忽略
            }
            iff('b','c','1'); //等价于 if(w[i]=='b'||w[i]=='c') ans+='1';
            iff('d','w','2');
            iff('t','j','3');
            iff('f','q','4');
            iff('l','v','5');
            iff('s','x','6');
            iff('p','m','7');
            iff('h','k','8');
            iff('n','g','9');
            iff('z','r','0');
            //偷懒
        }
        if(!ans.empty()){ //答案字符串非空
            if(n>=1){ //不是最后一个，输出空格
                cout<<ans<<' ';
            }
            else if(n==0){ //是最后一个，输出换行
                cout<<ans<<endl;
            }
        }
    }
	return 0;
} 
```


---

