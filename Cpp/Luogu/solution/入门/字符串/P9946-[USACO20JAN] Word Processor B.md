# [USACO20JAN] Word Processor B

## 题目描述

奶牛 Bessie 正在完成她的写作课的一篇作文。由于她写字很难看，她决定用一个文字处理器来输入这篇作文。

这篇作文共有 $N$ 个单词（$1\le N\le 100$），用空格分隔。每个单词的长度在 $1$ 到 $15$ 之间，仅由大写和小写字母组成。根据作业的要求，这篇作文需要用一种特别的方式排版：每一行包含的字符不超过 $K$ 个（$1\le K\le 80$），空格不计。幸好 Bessie 的文字处理器能够处理这样的要求，它会按照如下的方式：

 - 如果 Bessie 输入了一个单词，这个单词能够放进当前行，就放在当前行。
 - 否则，将这个单词放到下一行，然后继续向下一行添加单词。

当然，同一行中的单词之间仍然用一个空格分隔。每一行的结尾都不应当有空格。

很不幸，Bessie 的文字处理器刚好坏了。请帮助她正确地排版她的作文！ 

## 说明/提示

### 样例解释 1

第一行包含 $7$ 个非空格字符，包括 `hello` 以及 `my`。再加入 `name` 会使得第一行包含 $11>7$ 个非空格字符，所以这个单词会被放到下一行。

## 样例 #1

### 输入

```
10 7
hello my name is Bessie and this is my essay```

### 输出

```
hello my
name is
Bessie
and this
is my
essay```

# 题解

## 作者：FurippuWRY (赞：6)

用数组 $a$ 存储单词，数组 $b$ 存储对应单词的长度，然后用一个变量 $cnt$ 循环加上 $b_i$，如果此时 $cnt \le k$，输出 $a_i$；否则，换行输出 $a_i$，并清空 $cnt$，再加上此时的 $b_i$。

```cpp
#include<bits/stdc++.h>

using namespace std;

string a[105];
int n, k, b[1145141], cnt = 0;

int main() {
    
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        b[i] = a[i].size();
    }
    for (int i = 1; i <= n; ++i) {
        cnt += b[i];
        if (cnt <= k) cout << a[i] << ' ';
        else {
            cout << '\n' << a[i] << ' ';
            cnt = 0;
            cnt += b[i];
        }
    }
    
    return 0;
    
}
```

---

## 作者：_fallen_leaves_ (赞：2)

## 思路
这么水的题不需要题解吧，输入每一个字符串，这就会有两种可能性。

- 如果加上这个数没有超，就把这个数输出，并让 $ans$ 加上它的长度。
- 否则，就输出换行并输出这个数，并让 $ans$ 改为它的长度。

贴代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,k,ans=0;
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
    	string s;
    	cin>>s;
    	if(ans+s.size()<=k)//如果加上这个数没有超，
		{
			cout<<s<<" ";//就把这个数输出，
			ans+=s.size();//并让 ans 加上它的长度。
		}
    	else//否则，
		{
			cout<<endl<<s<<" ";//就输出换行并输出这个数，
			ans=s.size();//并让 ans 改为它的长度。 
		}
	}
    return 0;
}
```

---

## 作者：continueOI (赞：1)

简单题，直接按题意模拟即可。

看到字符串 $s$ 有空格，考虑一个一个单词读入，维护 `len` 值，如果当前读入的单词长度加上这一行已有的长度超过 $k$，那就换行。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
string s;
int len;
int main(){
	cin>>n>>k;
	while(n--){
		cin>>s;
		if(len+s.size()>k) cout<<'\n',len=0;
		cout<<s<<' ';
		len+=s.size();
	}
	return 0;
}
```


---

## 作者：some_ICE_ANK (赞：0)

[原题地址](https://www.luogu.com.cn/problem/P9946)

## 题意
输入 $N$ 个单词，保证一行中单词的字符数不大于 $K$ 个。

## 思路
用 $sum$ 变量来存储**当前一行**有的字符数，当 $sum$ **大于** $K$ 时换到下一行，并将 $sum$ 变量**重赋值为下一行的第一个单词的字符数**。

## 代码
```cpp
#include<iostream>
#include<cstring>
using namespace std;
string s[101];
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	int sum=0;
	for(int i=1;i<=n;i++){
		sum+=s[i].length();//加上字符数
		if(sum>k){
			cout<<endl;//换行
			cout<<s[i]<<' ';
			sum=s[i].length();//重赋值
			continue;
		}
		cout<<s[i]<<' ';
	}
	return 0;
}
```

---

## 作者：juruo_zhanshen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9946)。
# 正文
用数组记录每一个单词。对于未超过本行上限的单词，可以直接加上单词的长度并输出。否则记录的变量等于当前单词的长度并输出。

本题较为简单，仁慈的我想了又想，就直接放代码吧。
```cpp
#include <bits/stdc++.h>
using namespace std;
string s[105];
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    //freopen(".in", "r", stdin);
    //freopen(".out", "w", stdout);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++){
        cin >> s[i];
    }
    int tmp = 0;
    for (int i = 1; i <= n; i++){
        if (s[i].size() + tmp > k){
            tmp = s[i].size();
            cout << endl;
            cout << s[i] << " ";
        }
        else{
            cout << s[i] << " ";
            tmp += s[i].size();
        }
    }
    cout << endl;
    return 0;
}               /* ----------  end of function main  ---------- */
```
本题复杂度可以优化，对于这个代码，可以不存在数组里，读入后直接判断输出，由读者自行思考。

---

## 作者：littleqwq (赞：0)

# P9946 [USACO20JAN] Word Processor B 题解

### 题目意思：

给你 $n$ 个单词，按顺序放，要求每行除了空格外的所有字符，不超过 $k$ 个，如果超过了，就放到下一行。

### 大致思路：

建一个变量 $idx$，记录每行字符数，每次输入进去先让 $idx$ 加上当前字符的长度，如果超过了 $k$ 个字符，那么先换行在输出这个单词，将 $idx$ 设为当前字符串的长度，如果没超过，那么直接输出本个单词，以此类推。

### 代码实现：

```
#include<bits/stdc++.h>
using namespace std;
int n,k,idx;
string s;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>s;
		int l=s.size();
		idx+=l;
		if(idx>k){
			cout<<endl;
			cout<<s<<" ";
			idx=l;
		}else{
			cout<<s<<" ";
		}
	}
	return 0;
}
```

这样这道题就完成啦，如有什么不足，欢迎在评论区评论。

---

## 作者：b1tset (赞：0)

很简单的模拟题。维护好当前行的**字符个数**并处理好**换行**以及**空格**的输出即可。由于没什么思维难度就直接上代码了。关键的地方会有注释。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    
    string s;
    int len = 0; //代表当前行的字符数
    while (n--)
    {
        cin >> s;
        len += s.size(); //加上当前单词的字符数
        if (len <= k) //如果没超过k，直接输出即可，注意空格
            cout << s << " ";
        else
        {
            cout << '\n' << s << " "; //超过了就换行，注意换行及空格
            len = s.size(); //新的一行的字符数为当前字母的字符数
        }
    }
    return 0; //优雅地结束~
}
```


---

## 作者：__O_v_O__ (赞：0)

此题做法很简单，只需记录本行已经输入的字符数，每输入一个单词后，判断本行长度是否超过 $k$，如果超过则换行后输出，否则直接输出，注意每次输出完要修改本行字符数。

**AC code:**
```cpp
#include<bits/extc++.h>
using namespace std;
#define BTS 0
#define STB 1
#define afor(i,n,m,dir) for(int i=n;dir?i<=m:i>=m;dir?i++:i--)
#define int long long
int n,k,no;string x;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>k;//输入
	afor(i,1,n,STB){//循环
		cin>>x;//输入
		if(no+x.size()>k){//如果字符数超过
			cout<<'\n'<<x<<' ';//换行再输出
			no=x.size();
		}else{
			cout<<x<<' ';//直接输出
			no+=x.size();
		}
	}
	return 0;
}
```

---

## 作者：tder (赞：0)

模拟即可。

---

令 $p$ 表示当前行已有字符数，那么，对于一个单词 $s$，令 $|s|$ 表示 $s$ 的长度：

- 当本行能放下，即 $p+|s|\le k$，放在本行：
  - 若原来本行无单词，即 $p=0$，输出 $s$，$p\leftarrow (p+|s|)$；
  - 若原来本行无单词，即 $p>0$，输出空格和 $s$，$p\leftarrow (p+|s|)$；
- 反之，当本行不能放下，即 $p+|s|>k$，放在下一行，换行并输出 $s$，$p\leftarrow|s|$。

时间复杂度 $O(n)$。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 5;
int n, k, p;
string s;
signed main() {
	cin>>n>>k;
	while(n--) {
		cin>>s;
		if(p + s.length() <= k) {
			if(p) cout<<" ";
			cout<<s;
			p += s.length();	
		} else {
			cout<<endl<<s;
			p = s.length();
		}
	}
	return 0;
}
```

---

## 作者：Clarinet (赞：0)

[更好的食用体验](https://www.luogu.com.cn/blog/Czel-X/ti-xie-19-post) [原题链接](https://www.luogu.com.cn/problem/P9946)
# 简要题意
给出一篇有 $N$ 个单词的作文，要求以每行不超过 $K$ 个字符的方式输出，不计算空格。
# 分析
很简单的题目。我们输入单词的同时计算这一行的单词数并判断是否需要输出换行就行了。记得要在每行清空已有的字符数量。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
int n,k,l;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a;
		if(a.size()+l>k)cout<<endl,l=0;
		cout<<a<<" ";
		l+=a.size();
	}
	return 0;
}
```
感谢阅读！

---

