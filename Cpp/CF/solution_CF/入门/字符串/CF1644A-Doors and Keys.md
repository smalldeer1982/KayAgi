# Doors and Keys

## 题目描述

The knight is standing in front of a long and narrow hallway. A princess is waiting at the end of it.

In a hallway there are three doors: a red door, a green door and a blue door. The doors are placed one after another, however, possibly in a different order. To proceed to the next door, the knight must first open the door before.

Each door can be only opened with a key of the corresponding color. So three keys: a red key, a green key and a blue key — are also placed somewhere in the hallway. To open the door, the knight should first pick up the key of its color.

The knight has a map of the hallway. It can be transcribed as a string, consisting of six characters:

- R, G, B — denoting red, green and blue doors, respectively;
- r, g, b — denoting red, green and blue keys, respectively.

Each of these six characters appears in the string exactly once.

The knight is standing at the beginning of the hallway — on the left on the map.

Given a map of the hallway, determine if the knight can open all doors and meet the princess at the end of the hallway.

## 说明/提示

In the first testcase, the knight first collects all keys, then opens all doors with them.

In the second testcase, there is a red door right in front of the knight, but he doesn't have a key for it.

In the third testcase, the key to each door is in front of each respective door, so the knight collects the key and uses it immediately three times.

In the fourth testcase, the knight can't open the blue door.

## 样例 #1

### 输入

```
4
rgbBRG
RgbrBG
bBrRgG
rgRGBb```

### 输出

```
YES
NO
YES
NO```

# 题解

## 作者：Eason_AC (赞：7)

## Content
有一个骑士站在一条走廊的左端，在走廊的右端，一位公主正在等待他的到来。

在来到这里之前，骑士就了解到，这条走廊一共有三扇门：红门、绿门和蓝门。分别对应这三扇门的钥匙分别是红钥匙、绿钥匙和蓝钥匙。他还拥有一张这条走廊的地图，其可以转化成一个仅包含以下 $6$ 个字符的字符串：

- `R`、`G`、`B`：分别表示红门、绿门和蓝门。
- `r`、`g`、`b`：分别表示红钥匙、绿钥匙和蓝钥匙。

骑士能够经过一扇门，当且仅当骑士拥有与其对应的钥匙。由于公主不愿意等太久，因此骑士**只能一直向右端走，不能回头**。

请判断骑士能否走到走廊的右端和公主会合。

**数据范围：$t$ 组数据，$1\leqslant t\leqslant 720$。**
## Solution
我们注意到题面中这段内容：

> 骑士能够经过一扇门，当且仅当骑士拥有与其对应的钥匙。由于公主不愿意等太久，因此骑士**只能一直向右端走，不能回头**。

然后我们发现，骑士能够走到右端，当且仅当每扇门对应的钥匙都出现在门的左边。因此，我们直接记录每扇门和每把钥匙的位置，然后判断即可。

`find()` 函数可以很轻松的做到记录字符串中某个字符的位置，因为该函数在某个字符存在的时候，返回的就是该字符第一次出现的位置。
## Code
```cpp
namespace Solution {
	int Tnum;
	string s;
	
	void Main() {
		read(Tnum);
		while(Tnum--) {
			cin >> s;
			if(s.find("r") > s.find("R")
			|| s.find("b") > s.find("B")
			|| s.find("g") > s.find("G"))
				puts("NO");
			else
				puts("YES");
		}
		return;
	}
}
```

---

## 作者：SunSkydp (赞：3)

[可能会有更好的阅读体验](https://www.cnblogs.com/sunskydp/p/solution-cf1644a.html)

### 思路
模拟，首先定义三个布尔变量，分别表示三个颜色的钥匙是否拿到，然后遍历字符串，如果是小写字母，就标记以下布尔变量，如果是大写字母，则查找其钥匙是否拿到，没拿到就用 flag 标记，最后判断输出即可。

### 代码

因为这里要判断每一个字符的 $6$ 种情况，所以用 switch 语句更方便，然后注意下每组数据的变量要清零。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
bool r, g, b;
string s;
int main() {
	scanf("%d", &t);
	while(t--) {
		cin >> s;
		bool flag = true;
		r = 0, g = 0, b = 0;
		for(int i = 0; i < s.size(); i++) {
			switch (s[i]) {
				case 'r':r = 1;break;
				case 'g':g = 1;break;
				case 'b':b = 1;break;
				case 'R':if(r == 0)flag = false;break;
				case 'G':if(g == 0)flag = false;break;
				case 'B':if(b == 0)flag = false;break;
			}
			if(!flag) break;
		}
		if(flag) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```


---

## 作者：xieyikai2333 (赞：3)

- [题目传送门](https://www.luogu.com.cn/problem/CF1644A)

---

### 思路分析

- 骑士只能从左往右走，所以骑士可以走到走廊尽头的充要条件是：每种颜色的钥匙都在对应颜色的门左边。

于是，我们只要从左往右标记已经拿到的钥匙，如果遇到门，就判断有没有对应的钥匙即可。

---

### 具体做法

对于每组数据：

1. 读入；

2. 从左往右扫描整个字符串：

- 如果是小写字母：$key_{s_i-97} \gets 1$；（$\texttt{a}$ 的 ASCII 码是 $97$）

- 如果是大写字母：如果 $key_{s_i-65} \neq 1$，直接输出 $\texttt{NO}$；（$\texttt{A}$ 的 ASCII 码是 $65$）

3. 如果到最后扫描完了整个字符串，那么输出 $\texttt{YES}$。

---

注意：

- 本题有多组数据，所以每次一定要**清空数组**。

---

### 代码实现


**AC 代码**：

```cpp
#include <bits/stdc++.h>
using namespace std;
bool key[26];
bool solve()
{
	memset(key,false,sizeof(key));
	string s;
	cin>>s;
	for(int i=0;i<6;i++)
	{
		if('a'<=s[i]&&s[i]<='z')key[s[i]-'a']=true;
		else if(!key[s[i]-'A'])return false;
	}
	return true;
}
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		if(solve())puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

**AC 记录**：

![](https://cdn.luogu.com.cn/upload/image_hosting/wcis4z6m.png)

---

## 作者：cqbztz2 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1644A)

[不会更好的阅读体验](https://www.luogu.com.cn/blog/493271/solution-cf1644a)

# Thinking

发现骑士能否走到走廊的右端和公主会合与红门、绿门和蓝门的出现情况以及红钥匙、绿钥匙和蓝钥匙有关，因此遍历走廊。

用三个变量分别记录红钥匙、绿钥匙和蓝钥匙的数量，当遇见各自的门的时候，判断红钥匙、绿钥匙和蓝钥匙的数量是否足够即可。

注意，开启一次门会减少一把对应的钥匙。多组测试数据，记得初始化。

# Coding

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  string s;
  int t,len,r,g,b;
  signed main(){
      scanf("%d",&t);
      while(t--){
          r=g=b=0;
          cin>>s;
          len=s.length();
          bool flag=true;
          for(int i=0;i<len;i++){
              if(s[i]=='r'){
                  r++;
              }
              if(s[i]=='g'){
                  g++;
              }
              if(s[i]=='b'){
                  b++;
              }
              if(s[i]=='R'){
                  if(r){
                      r--;
                  }
                  else{
                      flag=false;
                      break;
                  }
              }
              if(s[i]=='G'){
                  if(g){
                      g--;
                  }
                  else{
                      flag=false;
                      break;
                  }
              }
              if(s[i]=='B'){
                  if(b){
                      b--;
                  }
                  else{
                      flag=false;
                      break;
                  }
              }
          }
          if(flag==true){
              puts("YES");
          }
          else{
              puts("NO");
          }
      }
      return 0;
  }
```


---

## 作者：c20231020 (赞：1)

### 题目链接
[洛谷](https://www.luogu.com.cn/problem/CF1644A)

[Codeforces](https://codeforces.ml/problemset/problem/1644/A)
### 题面大意
现有一个长度为 $6$ 的字符串，其中包含 R, G, B, r, g, b 六个字符，问每个小写字符是否均出现在对应的大写字符前。
### 思路
我们可以用三个标记 f1, f2, f3 分别记录 r, g, b 字符是否出现过，若该标记为 $1$ 则表示出现过，为 $0$ 则表示没有。

所以，判断不合法的条件为：当前的大写字母对应的小写字母的标记为 $0$。

这样，我们就可以从左往右扫一遍字符串，边扫边判断即可。

#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[10],f1,f2,f3,f;
int t;
int main(){
	scanf("%d",&t);
	while(t--){
		f=1;
		f1=f2=f3=0;                       //初始化 
		scanf("%s",s+1);                  //建议不使用scanf("%c")和getchar，以防止空白符干扰。 
		for(int i=1;i<=6;i++){
			if(s[i]=='r')f1=1;
			else if(s[i]=='g')f2=1;
			else if(s[i]=='b')f3=1;       //标记 
			else if((s[i]=='R'&&f1==0)
				  ||(s[i]=='G'&&f2==0)
				  ||(s[i]=='B'&&f3==0)){  //判断不合法 
				printf("NO\n");
				f=0;                      //不合法标记 
				break;
			}
		}
		if(f)printf("YES\n");             //合法情况 
	}
	return 0;
}
```

写的有点烂，欢迎大家~~爆踩我~~提出建议。

---

## 作者：_ZhouYuHan_ (赞：0)

这道题可以用字符串存储，再用数组计数。

把三种钥匙分别设为 $1$ , $2$ , $3$ 即可计数。

如果经过门时未拥有此种颜色的钥匙，直接输出 ```NO``` ，然后进入下一次循环。

最后再输出 ```YES``` 即可。

AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int t;
	cin>>t;
	while(t--) {
		bool b[4]= {0},flag=1;
		string str;
		cin>>str;
		for(int i=0; i<str.size(); i++) {
			switch(str[i]) {
				case 'r':
					b[1]=1;
					break;
				case 'g':
					b[2]=1;
					break;
				case 'b':
					b[3]=1;
					break;
				case 'R':
					if(b[1]!=1) {
						flag=0;
						cout<<"NO\n";
					}
					break;
				case 'G':
					if(b[2]!=1) {
						flag=0;
						cout<<"NO\n";
					}
					break;
				case 'B':
					if(b[3]!=1) {
						flag=0;
						cout<<"NO\n";
					}
					break;
			}
			if(!flag)
				break;
		}
		if(flag)
			cout<<"YES\n";
	}
	return 0;
}
```


---

## 作者：清烛 (赞：0)

题意：$3$ 种颜色的门和钥匙，需要先遇到小写字母的钥匙后打开大写字母的门，问能不能通过去。

简单模拟即可，当存在一个小写字母的时候记录一下，遇到大写字母的时候检查其对应的小写字母是否存在。

参考实现 1：
```cpp
char s[7];

int main() {
    int T; read(T);
    while (T--) {
        read(s);
        bool vis[3] = {0, 0, 0}, flg = 1;
        FOR(i, 0, 5) {
            if (s[i] == 'r') vis[0] = 1;
            else if (s[i] == 'g') vis[1] = 1;
            else if (s[i] == 'b') vis[2] = 1;
            else if (s[i] == 'R') flg &= vis[0];
            else if (s[i] == 'G') flg &= vis[1];
            else if (s[i] == 'B') flg &= vis[2];
        }
        print(flg ? "YES" : "NO");
    }
    return output(), 0;
}
```

参考实现 2：
```cpp
int main()
{
    int t;cin>>t;
    rep(kase,1,t)
    {
        set<char> S;
        string str;cin>>str;
        bool flg=1;
        for(auto &c:str)
        {
            S.insert(c);
            if(isupper(c)&&!S.count(tolower(c)))
            {
                flg=0;
                break;
            }
        }
        cout<<(flg?"YES":"NO")<<'\n';
    }
    return 0;
}
```

---

## 作者：sycqwq (赞：0)

__题意：__

在一条走廊上，每一个位置可以是一个门或者一个钥匙。

每个门都有对应的颜色，拿到对应颜色的钥匙后可以通过这扇门。

读入一个字符串。

大写字母 `R`、`G`、`B` 表示三种颜色的门。

小写字母 `r`、`g`、`b` 表示三种颜色的钥匙。

求是否可以走到走廊的尽头（即通过所有的门）。

__思路：__

因为题目中给的是一个走廊，所以可以直接模拟。

对于每一个门，只有这他之前出现过和他相同颜色的钥匙，才可能通过。

当然如果有一个门无法通过，那么答案就是 `NO`。

__代码：__

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,bk[10005];
int main()
{
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        memset(bk,0,sizeof bk);
        string a;
        cin>>a;
        int k=0;
        for(int i=0;i<a.size();i++)
        {
            ++bk[a[i]];
            if(a[i]<'a'&&!bk[a[i]-'A'+'a'])
            {
                puts("NO");
                k=1;
                break;
            }
            
        }   
        if(!k)
        {
            puts("YES");
        }    
    }
    return 0;
}
```

---

## 作者：rai1gun (赞：0)

### 1.题目思路

没啥好说的，分别弄 $3$ 个标记，表示每个颜色先前是否出现过，当遇到大写字母时，判断即可。

### 2.题目代码

```c++
#include<bits/stdc++.h>
#define map unordered_map
#define F1(a,b,k) for(int i=a;i<=b;i+=k)
#define F2(a,b,k) for(int i=a;i>=b;i-=k)
using namespace std;
inline int read(){
	int now=0,nev=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')nev=-1;c=getchar();}
	while(c>='0'&&c<='9'){now=(now<<1)+(now<<3)+(c&15);c=getchar();}
	return now*nev;
}
int T;
string s;
bool r,b,g;
int main(){
	bool flg=false;
	T=read();
	while(T--){
		r=b=g=0;
		string s;
		cin>>s;
		F1(0,s.size()-1,1){
			if(s[i]=='r') r=1;
			if(s[i]=='b') b=1;
			if(s[i]=='g') g=1;
			if(s[i]=='R')
				if(!r){puts("NO"); goto d1;} 
			if(s[i]=='B')
				if(!b){puts("NO"); goto d1;} 
			if(s[i]=='G')
				if(!g){puts("NO"); goto d1;} 
		}
		puts("YES");
		d1:;
	}
	return 0;
}

```

---

## 作者：ForeverCC (赞：0)

题意：`R` `B` `G` 是否都分别在它们小写字母之后，如果是输出 `YES`，否则输出 `NO`。

因为字符串长度只有 $6$，所以直接模拟，用一个 `bool` 数组记录小写字母是否出现，在遍历到大写字母时判断即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
bool f[3];
char s[10];
signed main(){
	scanf("%d",&t);
	while(t--){
		memset(f,0,sizeof(f));
		scanf("%s",s);
		bool flag=1;
		for(int i=0;s[i];i++){
			if(s[i]=='r')f[0]=1;//小写字母记录
			if(s[i]=='b')f[1]=1;
			if(s[i]=='g')f[2]=1;
			if(s[i]=='R'&&!f[0])flag=0;//大写字母判断
			if(s[i]=='B'&&!f[1])flag=0;
			if(s[i]=='G'&&!f[2])flag=0;
		}
		if(flag)puts("YES");
		else puts("NO");
	}
	return 0;
}
```


---

## 作者：qfpjm (赞：0)

# 题目翻译

- 有 $T(1\leq T\leq 720)$ 个由 $r, b, g, R, B, G$ 六个字符组成的字符串,判断每个字符串是否满足：对于 $R, B, G$ 三个字符之前有没有出现与其对应的小写字母。有则输出 `YES`，否则输出 `NO`。

# 题解

- 当遇到小写字符时，记录下来；当遇到大写字符时，判断其对应的小写字符是否出现过即可。

- 时间复杂度 $O(6\times T)$，$6$ 倍的常数可以忽略，所以时间复杂度为 $O(T)$。

- 当然有 $O(36\times T)$ 的做法，但是更加麻烦，没必要。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
	int T;
	cin >> T;
	while (T --)
	{
		string str;
		cin >> str;
		bool r = 0, g = 0, b = 0, flag = 0;
		for (int i = 0 ; i < str.size() ; i ++)
		{
			if (str[i] == 'r')
			{
				r = 1;
			}
			if (str[i] == 'g')
			{
				g = 1;
			}
			if (str[i] == 'b')
			{
				b = 1;
			}
			if ((str[i] == 'R' && !r) || (str[i] == 'G' && !g) ||(str[i] == 'B' && !b))
			{
				puts("NO");
				flag = 1;
				break;
			}
		}
		if (!flag)
		{
			puts("YES");
		}
	}
}
```


---

## 作者：__KrNalty__ (赞：0)

### 题意简述：

多组输入，每组输入给你一个字符串，由六个字符组成：

- R、G、B —— 分别表示红色、绿色和蓝色的门；

- r、g、b —— 分别表示红色、绿色和蓝色的钥匙。

每一种颜色的钥匙可以打开对应颜色的门，问你能不能打开所有的门走到最后。

### 做题思路：

简单的模拟。

我们可以用三个变量来存储有没有遇到过这种颜色的钥匙，如果碰到了这扇门还没有拿到过对应颜色的钥匙，则说明我们走不到最后，输出 NO。如果成功打开了三扇门，则说明走到了最后，输出 YES 即可。

### 完整代码供参考：

```
#include <bits/stdc++.h>
using namespace std;
int t;
int main()
{
	cin >> t;
	while (t--)
	{
		string s;
		cin >> s;
		bool flagr = 0, flagg = 0, flagb = 0; // 分别表示对应颜色的钥匙有没有拿到 
		bool ans = 1; // 最后的结果 
		for (int i = 0; i < 6; i++)
		{
			if (s[i] == 'r')
			{
				flagr = 1;
			}
			if (s[i] == 'g')
			{
				flagg = 1;
			}
			if (s[i] == 'b')
			{
				flagb = 1;
			}
			if (s[i] == 'R' && !flagr)
			{
				ans = 0;
			}
			if (s[i] == 'G' && !flagg)
			{
				ans = 0;
			}
			if (s[i] == 'B' && !flagb)
			{
				ans = 0;
			}
		}
		if (ans)
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}
	return 0;
}
```

---

## 作者：Elgo87 (赞：0)

一道比较经典的模拟题。

用三个变量 $r,g,b$ 分别记录三种钥匙的个数，遇到门时发现没钥匙了就输出 `NO`，否则把这个钥匙减一。

如果能走到尽头就输出 `YES` 即可。

参考代码：

```cpp
# include <bits/stdc++.h>
# define max(a,b) ((a)>(b) ? (a) : (b))
# define min(a,b) ((a)<(b) ? (a) : (b))
# define abs(a,b) ((a)> 0  ? (a) : -(a))
# define endl putchar('\n')
# define space putchar(' ');
# define begining {
# define ending }
# define int long long
using namespace std;

inline int read() {
	int num = 0; int nev = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') nev = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { num = (num<<1) + (num<<3) + (ch ^ 48); ch = getchar(); }
	return num * nev;
}

inline void print(const int& x) {
	if (x < 0) { putchar('-'); print(-x); return ; }
	if (x < 10) { putchar(x+'0'); return ;}
	print(x/10), putchar(x%10 + '0'); return ;
}

signed main() 
{
	int T = read();
	while (T --)
	{
		string s;
		getline(cin, s);
		int r = 0, g = 0, b = 0, flag = 0;
		for (int i = 0; s[i]; i ++)
		{
			if (s[i] == 'r') {
				r ++;
			}
			if (s[i] == 'g') {
				g ++;
			}
			if (s[i] == 'b') {
				b ++;
			}
			if (s[i] == 'R') {
				r --;
			}
			if (s[i] == 'G') {
				g --;
			}
			if (s[i] == 'B') {
				b --;
			}
			if (r < 0 || g < 0 || b < 0) {
				flag = 1;
				break;
			}
		}
		if (flag) {
			puts("NO");
		} else {
			puts("YES");
		}
	}
	return 0;
}
 
```


---

## 作者：windflower (赞：0)

简要题意：  
>给定字符串 RGBrgb 的一个排列，判断是否所有小写字母都出现在它对应的大写字母之前。

很朴素的解法：  
从左到右遍历，遇到小写字母标记，遇到大写字母检查它对应的小写字母是否被标记即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string s;
int main(){
	cin>>t;
	while(t--){
		cin>>s;
		int flag=0,r=0,g=0,b=0;
		for(int i=0;i<s.size();i++){
			if(s[i]=='r')r++;
			if(s[i]=='g')g++;
			if(s[i]=='b')b++;
			if(s[i]=='R'&&r==0)flag=1;
			if(s[i]=='G'&&g==0)flag=1;
			if(s[i]=='B'&&b==0)flag=1;
		} 
		if(flag)cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}
	return (0-0);
}
```


---

## 作者：_Fatalis_ (赞：0)

### 题意简化

六个字母，任意一字母大写若出现在小写的前面，输出 `NO`，否则输出 `YES`。

### Solution

字典暴力模拟，这样能够减少代码量。使用 `toupper()` ~~使代码更整洁。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
bool flag[130];

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		memset(flag,0,sizeof(flag));
		string str;
		int t=0;
		cin>>str;
		for(int i=0;i<str.length();i++)
			if(isupper(str[i]))
			{
				if(!flag[str[i]]) {cout<<"NO\n";t=1;break;}
			}
			else flag[toupper(str[i])]=true;
		if(t==0) cout<<"YES\n";
	}
	return 0;
}
```

---

## 作者：Dr_Gilbert (赞：0)

## 题目大意

骑士站在走廊的开端，而美丽的公主正在走廊末端等他。走廊里有三扇门，分别为红色、绿色和蓝色。要通过门，骑士必须拿到对应颜色的钥匙。骑士有一幅地图，包含`R,G,B,r,g,b`六个字符。其中，`R,G,B`分别表示一扇红色、绿色、蓝色的门，`r,g,b`分别表示一把红色、绿色、蓝色的钥匙。问骑士能否走到走廊尽头。

## 题目分析

根据题意模拟即可，为了省事，可以开一个布尔数组，记录是否有对应颜色的钥匙，遇到门时判断即可。代码中有比较详细的注释。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
bool k[500];//是否有对应钥匙
int main(){
	int t;
	cin>>t;//数据组数
	for (int j=1;j<=t;j++){
		memset(k,0,sizeof(k));//清空标记
		string m;bool flag=0;//flag用于判断是否因为没有钥匙跳出了循环
		cin>>m;//走廊的地图
		for (int i=0;i<=5;i++){
			if (m[i]>='a'&&m[i]<='z'){
				k[m[i]]=1;//省事操作
			}else{
				if (!k[m[i]-'A'+'a']){
					cout<<"NO"<<endl;
					flag=1;break;//没有当前门的钥匙，不能穿过
				}
			}
		}
		if (!flag) cout<<"YES"<<endl;
	}
	return 0;
}
```



---

## 作者：miao5 (赞：0)

暴力查询即可。

我们从 $1$ 到 $6$ 枚举一遍序列，同时维护三个布尔变量 $r,g,b$ 表示是否出现过对应的钥匙。

当我们发现一扇门的时候，我们判断这个颜色的钥匙是否已经找到了，如果找到就可以通过，继续枚举序列，否则就是不能通过了，就输出 ```NO```，如果一直没有这样的情况输出 ```YES```。

```
#include<iostream>
using namespace std;
char c[10];
int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>c;
		bool r,g,b,flag;
		flag=r=g=b=0;
		for(int i=0;i<6;i++){
			if(c[i]=='r') r=1;
			if(c[i]=='g') g=1;
			if(c[i]=='b') b=1;
			if(c[i]=='R'){
				if(!r){
					cout<<"NO"<<endl;
					flag=1;
					break;
				}
			}
			if(c[i]=='G'){
				if(!g){
					cout<<"NO"<<endl;
					flag=1;
					break;
				}
			}
			if(c[i]=='B'){
				if(!b){
					cout<<"NO"<<endl;
					flag=1;
					break;
				}
			}
		}
		if(!flag) cout<<"YES"<<endl;
	}
}
```

---

## 作者：ttq012 (赞：0)

模拟题。

我们可以记录三个变量 `fr`，`fb`，`fg` 三个变量。

然后我们枚举输入的六个字符，当遇到字符 `b` 的时候，我们令 `fb = true`。

同理，遇到 `g` 就令 `fg = true`，遇到 `r` 就令 `fr = true`。

当我们遇到字符 `B` 并且 `fb = false` 的时候，就代表我们无法进入相应的门内，无解。

同理，遇到 `G` 且 `fg = false`，或者遇到 `R` 而且 `fr = false` 的时候，也代表无解。

最后如果有解输出 `Yes`，无解输出 `No` 即可。

**Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

signed main() {
    int t;
    cin >> t;
    while (t --) {
        string s;
        cin >> s;
        bool fr = false, fb = false, fg = false;
        bool ans = true;
        for (int i = 0; i < 6; i ++) {
            if (s[i] == 'b') fb = true;
            else if (s[i] == 'g') fg = true;
            else if (s[i] == 'r') fr = true;
            else if (s[i] == 'B') {
                if (! fb) {
                    ans = false;
                    break;
                }
            }
            else if (s[i] == 'R') {
                if (! fr) {
                    ans = false;
                    break;
                }
            }
            else if (s[i] == 'G') {
                if (! fg) {
                    ans = false;
                    break;
                }
            }
        }
        if (ans) puts("YES");
        else puts("NO");
    }
    return 0;
}

```


---

## 作者：zhongcy (赞：0)

[CF Problem](https://codeforces.com/problemset/problem/1644/A)

------------

一名骑士要通过走廊。走廊有三种颜色的门与钥匙。门用 $ \texttt{R,G,B} $ 表示，钥匙用 $ \texttt{r,g,b} $ 表示。骑士能捡起钥匙，打开与之匹配的门。现给出一个字符串表示走廊，问骑士能否通过走廊。


### Solution

------------

题目思路很简单：寻找 $ \texttt{R,G,B,r,g,b} $ 出现的位置，小写字母是否排在大写字母之前。显然，如果是，就输出 `YES`，否则输出 `NO`。


### Code

------------

这里可以使用 STL 中的一个函数 `s.find(c)`，表示字符串中某个字符出现的位置，大大减小码量。

时间复杂度 $ \Theta(t|s|) $。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--)
	{
		string s;cin>>s;
		if(s.find('r')<s.find('R')&&s.find('g')<s.find('G')&&s.find('b')<s.find('B'))
			cout<<"YES\n";
		else
			cout<<"NO\n";
	}
	return 0;
}
```


---

