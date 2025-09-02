# [NWRRC 2023] Missing Vowels

## 题目描述

在纸上书写一个单词有很多方式。例如，一些书写系统（如阿拉伯语和希伯来语）会省略大多数元音，尽管它们会写出其中的一些。

在本题中，我们只考虑由英文字母和连字符组成的字符串。字母 $\tt{a}$、$\tt{e}$、$\tt{i}$、$\tt{o}$、$\tt{u}$ 和 $\tt{y}$ 被视为元音，而连字符和所有其他字母都被视为辅音。所有比较均不区分大小写：同一个字母的大写和小写视为相同。

给定两个字符串 $s$ 和 $f$，分别称为“短名”和“全名”。你的任务是判断，是否可以通过从全名 $f$ 中省略一些元音（可能一个也不省略），得到短名 $s$。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
Shrm-el-Shikh
Sharm-el-Sheikh```

### 输出

```
Same```

## 样例 #2

### 输入

```
Eilot
Eilat```

### 输出

```
Different```

## 样例 #3

### 输入

```
Saint-Petersburg
Saint-Petersburg```

### 输出

```
Same```

## 样例 #4

### 输入

```
Bcdfghjklmnpqrstvwxz
Abcdefghijklmnopqrstuvwxzyy```

### 输出

```
Same```

## 样例 #5

### 输入

```
Aa
aaaA```

### 输出

```
Same```

## 样例 #6

### 输入

```
Etis-Atis-Amatis
Etis-Atis-Animatis```

### 输出

```
Different```

## 样例 #7

### 输入

```
will-the-wisp
will-o-the-wisp```

### 输出

```
Different```

## 样例 #8

### 输入

```
--a-very-short-name--
long-name```

### 输出

```
Different```

# 题解

## 作者：abc1234shi (赞：1)

# 分析
可以用双指针解决这题。
# 思路
将两串统一为小写，不然大小写混杂在一起很麻烦。

设短串指针 $i$，全串指针 $j$，接下来进行操作：
- 如果两个指针指向字符相同则 $i$ 与 $j$ 同时加 $1$。
- 如果两个指针指向字符不同，但全串当前字符为元音则跳过该元音，相当于将 $j$ 加 $1$。
- 如果两个指针指向的字符不同且全串指向字符不为元音字母直接输出 `Different`。

遍历结束后，如果全串中还有剩余字母，那么必须只能是元音，如果不是元音直接输出 `Different`。

若两指针同时到达末尾输出 `Same`，否则输出 `Different`。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	string s, f;
	cin>>s>>f;
	for (int i = 0; i < s.size(); ++i)
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
	for (int i = 0; i < f.size(); ++i)
		if (f[i] >= 'A' && f[i] <= 'Z')
			f[i] += 32;
	int i = 0, j = 0;
	while (i < s.size() && j < f.size()) {
		if (s[i] == f[j]) {
			++i;
			++j;
		} else {
			if (f[j] == 'a' || f[j] == 'e' || f[j] == 'i' ||
			        f[j] == 'o' || f[j] == 'u' || f[j] == 'y') {
				++j;
			} else {
				cout << "Different";
				return 0;
			}
		}
	}
	while (j < f.size()) {
		char c = f[j];
		if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y')
			++j;
		else
			break;
	}
	if (i == s.size() && j == f.size())
		cout << "Same";
	else
		cout << "Different";
	return 0;
}
```

---

## 作者：guoshengyu1231 (赞：1)

由于本题比较简单，直接模拟即可，所以这里我直接讲解题步骤。
# 解题步骤
- 由于本题不需要区分大小写，所以这里就提前将字符串内的大写字母转成小写字母
- 接下来是主要部分，定义两个指针 $i_1$ 和 $i_2$。初始均为 $0$。
- 之后两个指针将两个字符串扫一遍，会遇到一下情况。
  - 如果 ${s_1}_{i_1}={s_2}_{i_2}$，则两个指针分别往前移动一位。
  - 否则判断 ${s_2}_{i_2}$ 是否为元音字母，如果是则单独移动 $i_2$ 一位。否则的话说明无法通过从全名中省略一些元音得到短名，按原题要求操作即可。
- 当其中一个指针扫完了自己所属的字符串，则跳出循环。
- 此时我们判断 $i_1$ 是否小于 $n$，其中 $n$ 是字符串 $s1$ 的长度。
- 如果 $i_1<n$，说明此时依然无法满足题目的要求，同样按原题要求操作即可。
- 否则不断往前移动 $i_2$ 直到遍历完整个字符串 $s_2$，如果过程中遇到了非元音字母，说明此时无法满足题目的要求。
- 当我们遍历完了整个字符串 $s_2$，说明此时可以通过从全名中省略一些元音得到短名 s。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
int n,m;
char f(char x)
{
    if(x>='A'&&x<='Z') return x-'A'+'a';
    return x;
}//将大写转换成小写
bool ck(char x)
{
    return (x=='a'||x=='e'||x=='i'||x=='o'||x=='u'||x=='y');
}//判断是否为元音
int main()
{
    cin>>s1>>s2;
    n=s1.size();m=s2.size();
    int i1,i2;i1=i2=0;
    while(i1<n&&i2<m)
     if(f(s1[i1])==f(s2[i2])) i1++,i2++;
     else 
      {
         if(ck(f(s2[i2]))) i2++;
         else {cout<<"Different";return 0;}
      }
    if(i1<n) cout<<"Different";
    else 
    {
        while(i2<m)
         {
           if(ck(f(s2[i2]))) i2++;
           else {cout<<"Different";return 0;}
         }
        cout<<"Same";
    }
    return 0;
}
```

---

## 作者：linhanmo (赞：1)

# 题解：P13593 [NWRRC 2023] Missing Vowels

**以下将 $s,f$ 称为 $a,b$。**

双指针、贪心。

维护两个下标 $i,j$，分别对应 $a$ 和 $b$。

每次尝试贪心匹配 $i,j$，若可以，匹配下一对，若不行尝试将 $j$ 往后移。

::::success[证明正确性]{open}

反证法。

假如有两个指针 $i,j$ 可以匹配上但无法使整个字符串匹配，而当 $i$ 和 $k$（$k>j$）可以匹配上且可以使整个字符串匹配。

$\because a_i=a_j$ 且 $a_i=a_k$：

$\therefore b_j=b_k$。

又 $\because$ 可以从 $i$ 跳到 $k$：

$\therefore a_j\sim a_k$ 都是元音；

$\therefore$ 将 $i$ 和 $j$ 匹配时可以省略 $b_{i+1}\sim b_{k}$，即可以与将 $i$ 和 $k$ 匹配等价；

$\therefore i,j$ 匹配上且可以使整个字符串匹配。

矛盾！故不存在这样的 $i,j,k$。
::::

## 坑点

- $\texttt{y}$ 也是元音；
- $i$ 到达 $a$ 的末尾时要判断 $j$ 后是否都是元音。

## code

```cpp lines=15-25 line-numbers
#include <bits/stdc++.h>
using namespace std;
unordered_set<char> SET = {'a', 'e', 'i', 'o', 'u', 'y'};

string a, b;
int main(void) {
    cin.tie(nullptr) -> sync_with_stdio(false),
    cin >> a >> b;

    // 转化成小写
	for (char &i : a) if (isupper(i)) i = tolower(i);
	for (char &i : b) if (isupper(i)) i = tolower(i);

    // 双指针
	size_t i = 0, j = 0;
	for (; i < a.length(); ++i, ++j) {
		while (a[i] != b[j] && j < b.length() && SET.count(b[j])) ++j;
		if (j == b.length() || a[i] != b[j]) return cout << "Different", 0;
    }

    // 处理剩余部分
	if (i == a.length())
		while (++j < b.length())
		    if (!SET.count(b[j])) return cout << "Different", 0;
    cout << "Same";
    return 0;
}
```

---

## 作者：Starry_Knight (赞：1)

### 题目分析

这道题就是给我们两个字符串 $s$ 和 $f$，说我们是否在 $f$ 中删除一些元音元素（当然可以不删除），（字母 $\tt{a}$、$\tt{e}$、$\tt{i}$、$\tt{o}$、$\tt{u}$ 和 $\tt{y}$ 被视为元音），让 $f$ 变成 $s$。

---

### 思路分析

开始我还是这么想的：就是把这两个字符串转为小写之后，把 $f$ 的所有元音去掉，然后把这个新的 $f$ 和 $s$ 比较，看看是否一样。但是显然这个思路是错误的，因为题目说了是省略一些元音，不是所有的。

那么我又想出了一个思路：用双指针。

具体实现过程是这样的：

1. 定义 $i$ 和 $j$，就分别指向两个字符串的当前字符；
2. 遍历 $f$ 的字符：
   1. 如果当前字符是元音字符（前提不同），那么可以跳过（就是 $j + 1$）；
   2. 否则，这个字符必须和 $s_i$ 匹配，然后 $i$ 和 $j$ 都前进。
3. 判断 $i$ 是不是指向 $s$ 的末尾，是的话就代表成功，否则代表失败。

---

### 代码展示


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool v(char ch){
	//判断是否是元音
	return ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u'||ch=='y';
}
string s,f;
int i=0,j=0;
signed main(){
	getline(cin,s);
	getline(cin,f);
	while(i<s.size()&&j<f.size()){
		//不区分大小写，都转成小写
		if(s[i]>='A'&&s[i]<='Z'){
			s[i]=s[i]-'A'+'a';
		}
		if(f[j]>='A'&&f[j]<='Z'){
			f[j]=f[j]-'A'+'a';
		}
		if(v(f[j])&&f[j]!=s[i]) j++;
		//虽然不同，但是这个事元音，跳过（就是删除）
		else if(f[j]==s[i]) i++,j++;
		//可以，两个都前进！
		else{
			cout<<"Different";
			return 0;
			//这个已经不同了，不必要再循环
		}
	}
	if(i<s.size()){
		//两个字符串不同
		cout<<"Different";
		return 0;
	}
	while(j<f.size()){
		//这是一个特判
		if(f[j]>='A'&&f[j]<='Z'){
			f[j]=f[j]-'A'+'a';
		}
		if(v(f[j])==0){
			cout<<"Different";
			return 0;
		}
		j++;
		//是元音呀，可以删除
	}
	cout<<"Same";
	return 0;
}
```

好了，这样子就可以通过本题了。（真心求过！）

---

## 作者：__szh_DNCB__ (赞：1)

蒟蒻的第几篇题解忘了。好像是第九篇。

上来先说一下坑点，如果使用双指针错误的可以对照一下：

+ 判断 $f$ 是否所有字母都是元音（WA on #111）
+ 如果还没开始判断或指针判断到一半发现 $f$ 字符串剩下的长度已经小于 $s$ 字符串剩下的长度，即 $len_f - i < len_s - j$（其中 $len_x$ 表示字符串 $x$ 的长度，$i$ 与 $j$ 分别表示字符串 $f$ 与 $s$ 的指针）（WA on #116 或 #117）

看到题目就想到了双指针。首先先把两个字符串都改成小写。我们可以定义两个指针 $i$ 和 $j$，如果 $f_i = s_j$ 就让两个指针都自增 $1$；若 $f_i ≠ s_j$ 且 $f_i$ 是元音就让 $i$ 自增 $1$；若 $f_i ≠ s_j$ 并且 $f_i$ 也不是元音那么就可以直接输出 `Different`。

那我们兴致勃勃的交上去，然后就会发现，WA 了！原来如果 $f$ 的所有字母都是元音那么我们的程序就一定会输出 `Same`。所以我们要对 $f$ 全是元音的情况特判，分为以下两类：

+ 若 $s$ 字符串也全是元音，则判断 $f$ 字符串中每个元音的数量是否各自大于 $s$ 字符串中这个元音的数量。若是则输出 `Same`；反之 `Different`。
+ 若 $s$ 字符串不全是元音，直接输出 `Different`。

好了，bug 修完了！再度提交，为什么还是 WA 呢！原来如果在输入时或者指针判断到一半时 $f$ 字符串剩下的长度已经小于 $s$ 字符串剩下的长度，即 $len_f - i < len_s - j$（其中 $len_x$ 表示字符串 $x$ 的长度，$i$ 与 $j$ 分别表示字符串 $f$ 与 $s$ 的指针），那么也必须立刻终止程序并输出 `Different`。

终于，经历了很多困难，我们终于 AC 了这道黄题。以下是代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
bool vowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}
int svowel[7],fvowel[7];
int main() {
    string s, f;
    cin >> s >> f;
    int flen = f.length();
    int slen = s.length();
    if (flen < slen){
    	puts("Different");
    	return 0;
	}
    bool s_allvowel=1,f_allvowel=1;
    for (auto &c : s){
    	c = tolower(c);
    	if (c == 'a')svowel[1]++;
    	else if (c == 'e')svowel[2]++;
    	else if (c == 'i')svowel[3]++;
    	else if (c == 'o')svowel[4]++;
    	else if (c == 'u')svowel[5]++;
    	else if (c == 'y')svowel[6]++;
    	else s_allvowel=0;
	}
    for (auto &c : f){
		c = tolower(c);
    	if (c == 'a')fvowel[1]++;
    	else if (c == 'e')fvowel[2]++;
    	else if (c == 'i')fvowel[3]++;
    	else if (c == 'o')fvowel[4]++;
    	else if (c == 'u')fvowel[5]++;
    	else if (c == 'y')fvowel[6]++;
    	else f_allvowel=0;
	}
	if (f_allvowel){
		if (s_allvowel){
			for (int i=1;i<=6;i++){
				if (svowel[i] > fvowel[i]){
					puts("Different");
					return 0;
				}
			}
			puts("Same");
			return 0;
		}else {
			puts("Different");
			return 0;
		}
	}
    bool flag = 0;
    int i=0,j=0;
    for (;i<flen;i++){
        if (f[i] == s[j])j++;
        else{
            if (!vowel(f[i])){
                flag = true;
                break;
            }
        }
        if (flen-i < slen-j){
            puts("Different");
            return 0;
        }
    }
    if (flag)puts("Different");
    else puts("Same");
    return 0;
}
```

附：

+ [错误提交 1](https://www.luogu.com.cn/record/229264927)（错因为没有特判 $f$ 全元音情况）
+ [错误提交 2](https://www.luogu.com.cn/record/229283255)（错因为没有判断 $f$ 的剩余长度是否小于 $s$ 的）
+ [错误提交 3](https://www.luogu.com.cn/record/229283477)（错因同错误提交 2）
+ [AC 记录](https://www.luogu.com.cn/record/229286774)

感谢您看到这里，我是即将在 2025 年 CSP 退役的蒟蒻选手 [__szh_DNCB__](https://www.luogu.com.cn/user/1073754)。希望您能点个关注或者点个赞，谢谢喵！

---

## 作者：ZBXAPCY (赞：1)

**题目大意**：

给定两个字符串 $s$ 和 $f$，求从 $f$ 中删去一些元音能否得到 $s$。定义元音为 $\tt{a}$、$\tt{e}$、$\tt{i}$、$\tt{o}$、$\tt{u}$ 和 $\tt{y}$。同时在所有比较中不区分大小写。

**小提醒**：本文中的“匹配”一词表示一个字符串通过删除一些元音字母与另一个字符串相同。

用通俗但不严谨的话来说：假设我们已将前 $j$ 位 $f$ 通过操作变的与前 $i$ 位 $s$ 一样，并且是最优解（用最短的 $f$ 子串匹配了），那我们只需将 $i$ 的下一位与 $f$ 后面的位子相匹配，下一个子问题就解决了，只要解决了一个个子问题就可以得出最终解。而对于题目，我们只需确定在最优的情况下是否能将 $f$ 转化为 $s$ 即可。

通过观察，我们发现可以确定两个变量 $i$ 和 $j$，表示我们用前 $j$ 个 $f$ 的字符匹配了前 $i$ 个 $s$ 的字符。你们是不是想到了动态规划？其实不用那么麻烦，因为我们的子问题最优解总是依赖于上一个子问题的最优解，整个过程是线性的。用变量 $i$ 和 $j$ 直接贪心即可，贪心策略为尽可能用少的 $j$ 来匹配尽可能多的 $i$，因为如果我们用更多的 $j$ 匹配了更少的 $i$ 只有可能是我们删去额外了元音字母，而那些那些删去的元音字母，对于目前的子问题是可有可无的，但对于之后的子问题还可能有帮助，所以用刚刚推导出来的贪心策略，至少不会得到更劣解。

这样时间复杂度和空间复杂度都是线性的。（包括储存输入的字串的数组）

下面我写不下去了，直接放代码吧。

```cpp
#include <bits/stdc++.h>
using namespace std;
string s,f;//s和f如题目所说 
bool pd(char c){
	return c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||c=='y';
	//判断字符是否为元音 
}
int main(){
	cin>>s>>f;
	if(f.size()<s.size()){
		//题目的要求是只能删，如果目标字串比现在的长，那肯定不能匹配 
		cout<<"Different\n"; 
		return 0;
	}
	for(int i=0;i<s.size();i++)
		if(s[i]>='A'&&s[i]<='Z')
			s[i]+=32;//将所有大写字母转化为小写 
	for(int i=0;i<f.size();i++)
		if(f[i]>='A'&&f[i]<='Z')
			f[i]+=32;//同上 
	int i=0,j=0;//i,j和之前讲的一样 
	for(;i<s.size();i++,j++){
	/*
	建议先看下面的注释再看这条解释i++,j++的 
	i++很好理解，就是我们要让f一一匹配s的每一位，所以遍历s
	j++是因为下面我们让j跑到了第一个能和i匹配的位置，
	显然我们不能重复用一个位置
	所以j++，从下一个位置来跑j
	*/ 
		if(s[i]==f[j])
			continue;/*如果他们直接匹配上了，就跳过
		否则一直删除元音字母直到匹配上了或不能删了	
		*/
		while(j<f.size()&&s[i]!=f[j]&&pd(f[j]))
			j++;
		if(j>=f.size()||s[i]!=f[j]){
		//如果删到不能删或还没匹配上就输出Different
			cout<<"Different\n";
			return 0;
		}
	}
	while(j<f.size()&&pd(f[j]))
		j++;
	/*一个小细节，如果我们已经让f的前j个字符匹配了s,那么剩下的字符
	也要检查，如果剩下的全是元音，直接去掉即可，但如果有辅音，
	显然s与f最终是不能匹配上的。 
	*/
	cout<<(j==f.size()?"Same":"Different")<<'\n';
	/*等同于
	if(j==f.size())cout<<"Same";
	else cout<<""Different";
	cout<<'\n';
	 */
	return 0;
}
```

你们看懂了吗？看懂了就点个赞吧！！！

反正我无耻的认为此题解写的还算可以吧。

事实上，代码还可以写的更简洁一些：
```cpp
#include <bits/stdc++.h>
using namespace std;
string s,f;
bool pd(char c){
	return c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||c=='y';
}
int main(){
	cin>>s>>f;
	for(int i=0;i<s.size();i++)
		if(s[i]>='A'&&s[i]<='Z')
			s[i]+=32;
	for(int i=0;i<f.size();i++)
		if(f[i]>='A'&&f[i]<='Z')
			f[i]+=32;
	int i=0,j=0;
	for(;i<s.size();i++,j++){
		while(j<f.size()&&s[i]!=f[j]&&pd(f[j]))
			j++;
		if(j>=f.size()||s[i]!=f[j]){
			cout<<"Different\n";
			return 0;
		}
	}
	while(j<f.size()&&pd(f[j]))j++;
	cout<<(j==f.size()?"Same":"Different")<<'\n';
	return 0;
}
```
对于这份代码，大家就自己想想吧。


~~我还是太懒了~~

---

## 作者：litangzheng (赞：0)

### 思路：  

首先，我们在判断两个字符串 $a$ 与 $b$ 是否一样时，如果 $a$ 的第一个字符就与 $b$ 不同，那么 $a$ 与 $b$ 自然就是不一样的了。  

由这个性质，我们就能得出本题的结论：若分别在字符串 $f$ 与 $s$ 的同一位置的字符不一样，就只能把 $f$ 中的这一字符删去。如果这个字符无法删去（也就是辅音或连字符），直接输出 $\text{Different}$，否则在遍历完 $s$ 的所有字符后输出 $\text{Same}$。  

需要注意的是，你需要先把所有字母统一大小写再进行删字符的操作。然后在删完后，若被我们删去若干字符的字符串 $f$ 的长度与 $s$ 的长度不相等，还需要再检查一下能不能再把 $f$ 删到与 $s$ 一样，才能输出答案。  

思路就是这样，那让我们直接开始写代码罢！  

### 代码：  

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
int cnt;
int main(){
	cin>>a>>b;
	for(int i=0;i<a.length();i++){
		if(a[i]>='A'&&a[i]<='Z') a[i]=a[i]-'A'+'a';
	}
	for(int i=0;i<b.length();i++){
		if(b[i]>='A'&&b[i]<='Z') b[i]=b[i]-'A'+'a';
	}//统一大小写
	for(int i=0;i<a.length();i++){
		while(a[i]!=b[cnt]){//若字符不一样就开始删
			if(cnt>=b.length()){
				cout<<"Different";
				return 0;
			}//如果没的删了，输出不一样。
			if(b[cnt]!='a'&&b[cnt]!='e'&&b[cnt]!='i'&&b[cnt]!='o'&&b[cnt]!='u'&&b[cnt]!='y'){
				cout<<"Different";
				return 0;
			}//如果不能删，输出不一样。
			cnt++;
		} 
		cnt++;
	}
	if(cnt!=b.length()){
        for(int i=cnt;i<b.length();i++){
            if(b[i]!='a'&&b[i]!='e'&&b[i]!='i'&&b[i]!='o'&&b[i]!='u'&&b[i]!='y'){
				cout<<"Different";
				return 0;
			}//如果删后的长度与s不一样，再次进行判断
        }
        cout<<"Same";
    }
	else cout<<"Same";
}
```

---

## 作者：Jeeff (赞：0)

# 题解：P13593 [NWRRC 2023] Missing Vowels
## 一. 个人评价
从思路上来看其实不算黄，代码写起来也不难，但大家可以翻一下我的记录，这题坑点太多！  
## 二. 思路
这道题看能不能删除一些元音字母使得 $f$ 变成 $s$。一眼排除 dp 等~~高级~~算法，显然应该用贪心实现（应该……也不算吧）。  
首先先判断 $f$ 和 $s$ 的长度，若 $f$ 长度还小于 $s$，那么肯定不行，直接输出。（坑点1）  
然后对 $f$ 和 $s$ 大小写转化，这边我统一转成小写。记得还有个连字符要处理，不然有可能会出错（不太坑的点2）。  
接着直接用一个 $i$ 来遍历 $s$，同时记录一个 $j$ 表示现在 $s[i]$ 所对应的在字符串 $f$ 中的位置。若发现 $s[i]$ 不等于 $f[j]$，那么说明要删掉 $f[j]$ 这一位，此时如果 $f[j]$ 不是元音（坑点3，请注意元音有哪些），那么不符合题意，直接输出！否则，$j$ 往右一位继续比对，直到 $s[i]$ 等于 $f[j]$ 为止。  
记得**时刻**判断 $j$ 有没有越界（坑点4）！  
还有，注意到 $i$ 的循环结束后 $j$ 不一定结束了，此时 $f[j]$ 后面的都要删掉，假如后面有一个不是元音都不行，也是直接输出！（坑点5）
## 三. 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string l_s(string a)
{
	string ans;
	for(auto i:a)
		ans+=(i>='a' and i<='z' or i=='-'?i:i+32);
	return ans;
}
bool check(char c)
{
	return (c=='a'||c=='e'||c=='u'||c=='o'||c=='i'||c=='y');
}
int main()
{
	string s1,s2;
	cin>>s1>>s2;
	s1=l_s(s1);s2=l_s(s2);
	if(s1.size()>s2.size())return cout<<"Different",0;
	int j=0;
	for(int i=0;i<s1.size();i++)
	{
		if(j>=s2.size())return cout<<"Different",0;
		while(s2[j]!=s1[i])
		{
			if(j>=s2.size())return cout<<"Different",0;
			if(!check(s2[j]))return cout<<"Different",0;
			j++;
		}
		j++;
	}
	for(j;j<s2.size();j++)
		if(!check(s2[j]))
			return cout<<"Different",0;
	cout<<"Same";
}

```

---

## 作者：tang_c (赞：0)

# 题解：P13593 [NWRRC 2023] Missing Vowels

考验英语水平啊！

## 题意简述

能不能从全名 $f$ 中删除一些元音字母，来得到更短的短名 $s$，其中元音包括 $\tt{a}$、$\tt{e}$、$\tt{i}$、$\tt{o}$、$\tt{u}$ 和 $\tt{y}$，一定要好好审题，不要漏了字母，~~人家可有 120 个测试点~~。

## 解题思路

- 将字符串全部转化为小写字母，以便之后的判断。
- 对于全名 $f$，生成一个新的字符串，其中包含了所有的辅音和连词，以及那些还没有被删过的元音。简单点说就是确保新的字符串删除某些元音后能和短名 $s$ 匹配。
- 使用双指针遍历字符串，[双指针例题](https://www.luogu.com.cn/problem/P1102)。

## 代码及解释

先上代码：
```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isVowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

bool check(const string& s, const string& f) {
    int i = 0, j = 0;
    int n = s.size(), m = f.size();
    while (i < n && j < m) {
        if (tolower(s[i]) == tolower(f[j])) {
            i++;
            j++;
        } else if (isVowel(f[j])) {
            j++;
        } else {
            return false;
        }
    }
    while (j < m) {
        if (!isVowel(f[j])) {
            return false;
        }
        j++;
    }
    return i == n;
}

int main() {
    string s, f;
    getline(cin, s);
    getline(cin, f);
    if (check(s, f)) {
        cout << "Same" << endl;
    } else {
        cout << "Different" << endl;
    }
    return 0;
}

```

### 解释
- `isVowel`：用于判断元音。
- `check`：实现双指针，步骤如下：
  
    - 遍历 $f$，如果当前字母与 $s$ 的当前字母匹配，两个指针都向前一步。
    - 如果 $f$ 当前字母是元音字母，直接跳过也就是删除。
    - 如果当前 $f$ 的字母是辅音或者是连字符并且与 $s$ 不匹配，直接返回`false`。

时间复杂度为 $O(len(f))$。

---

## 作者：Co_Ce (赞：0)

# Solution

[link](https://www.luogu.com.cn/problem/P13593)

首先，将字符串中大写字母转化为小写字母。  
再进行匹配：  
1. 如果相同指针向后移。
2. 如果不同：如果 $f_j$ 是元音，指针后移，否则输出 `Different`。
3. 如果 $s$ 扫完， $f$ 后面都是元音，指针后移，否则输出 `Different`。  
4. 如果 $s$ 没扫完，输出 `Different`。  

最后输出 `Same`。  

## std：
```cpp
#include <bits/stdc++.h>

using namespace std;

inline string read() {
    char ch = getchar();
    string a;
    while(ch != '\n') {
        if(ch >= 'A' && ch <= 'Z') {
            ch += 32;
        }
        a = a + ch;
        ch = getchar();
    }
    return a;
}

string s, f;

int main() {
    s = read(), f = read();
    
    int i = 0, j = 0;
    int n = s.size(), m = f.size();
    
    while(i < n && j < m) {
        if(s[i] == f[j]) {
            i++;
            j++;
        } else {
            if(f[j] == 'a' || f[j] == 'e' || f[j] == 'i' || f[j] == 'o' || f[j] == 'u' || f[j] == 'y') {
                j++;
            } else {
                cout << "Different";
                return 0;
            }
        }
    }
    
    while(j < m) {
        if(!(f[j] == 'a' || f[j] == 'e' || f[j] == 'i' || f[j] == 'o' || f[j] == 'u' || f[j] == 'y')) {
            cout << "Different";
            return 0;
        }
        j++;
    }
    
    if(i == n) {
        cout << "Same";
    } else {
        cout << "Different";
    }
    
    return 0;
}
```

---

## 作者：jsisonx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13593

# 题目分析

题目要求判断能否在字符串 $s$ 中添加一些元音字母使得与 $f$ 相同。如果考虑如何添加元音字母的话，需要考虑的比较多，不如考虑从 $f$ 中删字母。

显然，如果从 $f$ 中找出一个子序列 $f'=s$，在 $f$ 中删去 $f'$ 的所有字符后剩下的全部是元音字母，那么 $s$ 必然可以通过添加一些元音字母而与 $f$ 相同。否则，如果剩下的不只有元音字母，或 $f'$ 根本就找不到，那么就不行。

对于 $f'$，我们可以枚举 $s$ 的每一个字符并在 $f$ 中找到最靠左的该字符并作为 $f'$ 中的一个字符删去。最后判断如果剩下的全部为元音字母就输出 Same，否则为 Different。

# 代码

```cpp
#include<bits/stdc++.h>
#define N 1005
using namespace std;
char s[N],f[N];
int judge(char c){
    if(c=='a'||c=='A'||c=='e'||c=='E'||c=='i'||c=='I'||c=='o'||c=='O'||c=='u'||c=='U'||c=='y'||c=='Y'){
        return 1;
    }
    return 0;
}
int main(){
    cin>>s>>f;
    int len1=strlen(s),len2=strlen(f);
    if(len2<len1){
        cout<<"Different";
        return 0;
    }
    for(int i=0;i<len1;i++){
        if(s[i]>='A'&&s[i]<='Z'){
            s[i]+=32;
        }
    }
    for(int i=0;i<len2;i++){
        if(f[i]>='A'&&f[i]<='Z'){
            f[i]+=32;
        }
    }
    int u=0;
    for(int i=0;i<len1;i++){
        int y=0;
        for(int j=u;j<len2;j++){
            if(f[j]==s[i]){
                f[j]='@';
                u=j+1;
                y=1;
                break;
            }
        }
        if(!y){
            cout<<"Different";
            return 0;
        }
    }
    for(int i=0;i<len2;i++){
        if(f[i]!='@'){
            if(!judge(f[i])){
                cout<<"Different";
                return 0;
            }
        }
    }
    cout<<"Same";
    return 0;
}
```

---

