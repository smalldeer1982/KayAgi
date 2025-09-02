# Palindrome-phobia

## 题目描述

[problemUrl]: https://atcoder.jp/contests/cf17-final/tasks/cf17_final_b

すぬけ君は `a`、`b`、`c` の $ 3 $ 種類の文字のみからなる文字列 $ S $ を持っています。

回文恐怖症のすぬけ君は $ S $ の文字を自由に並び替えて、$ 2 $ 文字以上の回文を部分文字列として含まないようにしようと思いました。 これが可能かどうかを判定して下さい。

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 10^5 $
- $ S $ は `a`、`b`、`c` 以外の文字を含まない。

### Sample Explanation 1

このままだと `aba` という回文を含みますが、例えば `acba` のように並び替えると $ 2 $ 文字以上の回文を含まなくなります。

## 样例 #1

### 输入

```
abac```

### 输出

```
YES```

## 样例 #2

### 输入

```
aba```

### 输出

```
NO```

## 样例 #3

### 输入

```
babacccabab```

### 输出

```
YES```

# 题解

## 作者：Kvaratskhelia (赞：3)

### 题目大意

有一个只包含 ```a```，```b```，```c``` 的字符串，判断其是否能经过交换字符串中字符的位置，使其不包含两个及以上字符组成的回文子串。

### 思路

因为可以随便交换，所以可以考虑把所有字符串都变成类似 ```abcabcabc``` 这种循环的形式。

这时容易发现，要形成回文串，必须在 ```abcabcabc``` 的后面出现连续的两个字符。

所以可以把这个字符串做一个计数桶，统计每个字符出现的次数，然后从小到大排个序。然后，当最大出现次数和最小出现次数的差小于 $2$ 的时候，说明符合条件。

**注意：岛国题要换行！！！！**

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string st;
int a[23];
int main()
{
	getline(cin,st);
	for(int i=0;i<st.size();i++) a[st[i]-'a']++;
	sort(a,a+3);
	if(a[2]-a[0]<2) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	return 0;
}
```


---

## 作者：wdgm4 (赞：0)

### 思路

提供一个比较好想的思路，我们可以先把字符串拼成```abcabc...abc```这个样子，直到三个字符中数量最少的被用完，因为这样的字符串可以保证不包含有任何两个或两个以上字符组成的回文子串。

之后只会剩下两种字符（也可能会剩下一种或没有剩下的），这两种字符之中只要有一种字符的数量 $\ge 2$，那么就一定会出现回文子串，那就输出```NO```，否则输出```YES```。

### 代码

```
#include<bits/stdc++.h>
#define XD 114514
#define yee 1919810

using namespace std;
string s;
int a[10];//表示字符a,b,c出现的个数 
int main() {
	cin>>s;
	for(int i=0;i<s.length();i++) {
		if(s[i]=='a') a[1]++;
		if(s[i]=='b') a[2]++;
		if(s[i]=='c') a[3]++;
	}
	sort(a+1,a+4);
	a[3]-=a[1];
	a[2]-=a[1];
	if(a[3]>=2 or a[2]>=2) cout<<"NO\n";
	else cout<<"YES\n";
	return 0;
}

```


---

## 作者：封禁用户 (赞：0)

**思路:**
出现的次数最多的字符与其他两个字符数量的差不能大于 1。

**举例：**
1. abacab 出现的次数最多的字符与其他两个字符数量的差大于 1，故不符合。
1. abcbac 出现的次数最多的字符与其他两个字符数量的差不大于 1，故符合。
1. abbccaa 出现的次数最多的字符与其他两个字符数量的差等于 1，故符合。
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll maxn=14e4;
char s[maxn];
int a[maxn];
bool ok=true;
int main()
{
      cin>>s;
      for(int i=0;i<strlen(s);++i)
      {
          a[s[i]-'a']++;
      }
      sort(a,a+3);
      if(a[2]-a[0]>1)//大于1就false
      {
          ok=false;
      }
      if(a[2]-a[1]>1)//大于1就false
      {
          ok=false;
      }
      cout<<(ok?"YES":"NO");
      return 0;
}
```

---

