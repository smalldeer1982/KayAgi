# Do Not Be Distracted!

## 题目描述

Polycarp 有 $26$ 个任务。每一个任务都由一个大写字母来决定。

老师让 Polycarp 按以下规则做任务：如果 Polycarp 开始做某些任务，那么他必须一直做它，期间不能做其它任务，直到切换任务。但在切换到另一个任务之后，Polycarp 就不能再回到以前做过的任务了。

Polycarp 只能在一天内做一个任务。每一天他会写下他做了什么任务。现在老师想知道 Polycarp 是否遵守了他的规则。

举个例子，如果 Polycarp 以`DDBBCCCBBEZ`的顺序来做任务，那么老师就会知道在第三天 Polycarp 开始做任务`B`，然后在第五天他转移到做任务`C`，在第八天 Polycarp 又回到了做任务`B`，不符合老师的规则，老师就会怀疑他。老师会怀疑的的另外的例子有：`BAB`、`AABBCCDDEEBZZ`和`AAAAZAAAAA`。

如果 Polycarp 按照 `FFGZZZY` 的顺序来做，那么老师就没有任何怀疑。请注意 Polycarp 不必须完成所有的 $26$ 个任务。老师不会怀疑的其它例子有：`BA`、`AFFFCC`和`YYYYY`。

请你帮 Polycarp 指出他的老师是否会怀疑他。

## 样例 #1

### 输入

```
5
3
ABA
11
DDBBCCCBBEZ
7
FFGZZZY
1
Z
2
AB```

### 输出

```
NO
NO
YES
YES
YES```

# 题解

## 作者：BorisDimitri (赞：2)

# 题意
$t$ 组数据，每一组有一个长度小于 $50$ 的字符串 $str$ **(只包含大写字母)**。

如果有出现一个字母多次出现(连续的不算)，就输出 $\rm{NO}$, 否则输出 $\rm{YES}$。

# 题解
开个桶 $ton$，装这个字母有没有出现过。

枚举字符串中的所有字母，如果这个字母 **出现过**(即$ton[str[i]]>0$)，且它**前面的字母不是它** (即$str[i] != str[i-1]$)，则输出 $\rm{NO}$。

如果到最后都没有输出 $\rm{NO}$ ，就输出 $\rm{YES}$。

# code
```cpp
#include <bits/stdc++.h>
using namespace std;

int ton[50];

int main()
{
    int t;
    cin>>t;

    while(t--)
    {
        memset(ton,0,sizeof ton);
        int n;
        string str;
        cin>>n>>str;

        bool flag = 0;
        for(int i=0;i<n;i++)
        {
            if(ton[str[i]-'A'] > 0 && str[i-1]!=str[i]) 
            {
                flag = 1;
                cout<<"NO"<<endl;
                break;
            }
            ton[str[i]-'A'] ++;
        }
        if(!flag) cout<<"YES"<<endl;
    }

    return 0;
}

```

---

## 作者：信守天下 (赞：0)

## [CF传送门](https://codeforces.ml/contest/1520/problem/A)
## [洛谷传送门](https://www.luogu.com.cn/problem/CF1520A)
## 题目大意
判断字符串中的字符是否连续。
## 思路
枚举每一个字符。

如果一个字符和它的前一个字符不同，就有两种情况。

第一种：出现了一个新字符，记录下来。

第二种：出现了一个已经出现过的字符，直接跳出循环输出 NO 。

分类讨论即可。
## $code$
~~~cpp
#include <iostream>
using namespace std;
int t, l;
string s;
bool ch[26], f;
void Fill() {                      //清空标记数组
  for (int i = 0; i < 26; i++) {
    ch[i] = 0;
  }
  f = 0;
}
int main() {
  cin >> t;
  while (t--) {
    cin >> l >> s;
    ch[s[0] - 65] = 1;              //预处理防越界       
    for (int i = 1; i < l; i++) {
      if (s[i] != s[i - 1] && ch[s[i] - 65]) {
        f = 1;
        break;
      }
      if (s[i] != s[i - 1]) {
        ch[s[i] - 65] = 1;         //记录新字符
      }
    }
    cout << (f ? "NO" : "YES") << endl;
    Fill();
  }
  return 0;
}

~~~

---

## 作者：oimaster (赞：0)

题目翻译：判断字符串中相同字符是否连续。

我们可以每次记录当前字符是否在之前出现过。那么会有两种情况：
1. 没有出现过，我们就标记一下代表出现了
2. 出现过，我们判断前一个字符是不是和当前字符一样。如果不一样立刻结束循环，输出 `NO`。原因：我们每个字符产生的连续一段必定有一个开头。那么当我们扫描到开头时（当前字符不等于前面一个）我们就会验证。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		string s;
		cin>>s;
		bool is[200];
		fill(is,is+200,false);
		bool flag=false;
		for(int i=0;i<n;++i)
			if(!is[s[i]])
				is[s[i]]=true;
			else if(s[i-1]!=s[i]){
				flag=true;
				break;
			}
		if(flag==true)
			cout<<"NO"<<endl;
		else
			cout<<"YES"<<endl;
	}
}
```

---

## 作者：moqizhu2005 (赞：0)

### 题目大意

给定一个全为大写拉丁字母的字符串，判断是否有字符不连续出现。

### 解法

用一个数组储存字符是否出现，字符是否连续出现可以通过判断是否和上一个字符相等。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll t,n;
ll p[257];
int main(){
	scanf("%lld",&t);
	while(t--){
		for(int i='A';i<='Z';i++) p[i]=0;
		scanf("%lld",&n);
		char s[101];
		scanf("%s",s);
		ll b=0;
		p[s[0]]++;
		for(int i=1;i<n;i++){
			if(p[s[i]]&&s[i]!=s[i-1]){
				b=1;
				break;
			}
			else p[s[i]]=1;
		}
		if(b==1) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
```


---

## 作者：wheneveright (赞：0)

## 题意

给出 $T$ 个序列为 Polycarp 的工作顺序表。询问 Polycarp 是否在做一件事情分心， Polycarp 分心当且仅当他在做 $a$ 之后去做其他事情之后重新回来做 $a$。

## 分析

这道题也就是问我们对于一个给定的字符串，同一个字符是否连续。

所以可以考虑用一个 bool 类型的数组记录一个字符是否出现过，然后将每一次看到一个字符看看是否出现过，如果出现过，看看前一个字符是否与其相同，如果满足相同那么继续，不相同直接结束输出 `NO`。

## 代码

```cpp
# include <bits/stdc++.h>
using namespace std;

int T, N;
char s[55];
bool vis[55];

void check () {
	for (int i = 1; i <= N; i++) {
		if (vis[s[i] - 'A'] && s[i - 1] != s[i])
		{puts ("NO"); return ;} // 满足不连续，输出 no，结束
		vis[s[i] - 'A'] = true;
	}
	puts ("YES");
	return;
}

int main () {
	scanf ("%d", &T);
	while (T--) {
		scanf ("%d%s", &N, s + 1);
		memset (vis, 0, sizeof vis);
		check (); // 每一次 vis 数组要清空
	}
	return 0;
}
```

---

