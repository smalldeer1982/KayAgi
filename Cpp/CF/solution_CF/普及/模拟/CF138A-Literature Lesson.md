# Literature Lesson

## 题目描述

Vera adores poems. All the poems Vera knows are divided into quatrains (groups of four lines) and in each quatrain some lines contain rhymes.

Let's consider that all lines in the poems consist of lowercase Latin letters (without spaces). Letters "a", "e", "i", "o", "u" are considered vowels.

Two lines rhyme if their suffixes that start from the $ k $ -th vowels (counting from the end) match. If a line has less than $ k $ vowels, then such line can't rhyme with any other line. For example, if $ k=1 $ , lines $ commit $ and $ hermit $ rhyme (the corresponding suffixes equal $ it $ ), and if $ k=2 $ , they do not rhyme ( $ ommit≠ermit $ ).

Today on a literature lesson Vera learned that quatrains can contain four different schemes of rhymes, namely the following ones (the same letters stand for rhyming lines):

- Clerihew ( $ aabb $ );
- Alternating ( $ abab $ );
- Enclosed ( $ abba $ ).

If all lines of a quatrain pairwise rhyme, then the quatrain can belong to any rhyme scheme (this situation is represented by $ aaaa $ ).

If all quatrains of a poem belong to the same rhyme scheme, then we can assume that the whole poem belongs to this rhyme scheme. If in each quatrain all lines pairwise rhyme, then the rhyme scheme of the poem is $ aaaa $ . Let us note that it doesn't matter whether lines from different quatrains rhyme with each other or not. In other words, it is possible that different quatrains aren't connected by a rhyme.

Vera got a long poem as a home task. The girl has to analyse it and find the poem rhyme scheme. Help Vera cope with the task.

## 说明/提示

In the last sample both quatrains have rhymes but finding the common scheme is impossible, so the answer is "NO".

## 样例 #1

### 输入

```
1 1
day
may
sun
fun
```

### 输出

```
aabb
```

## 样例 #2

### 输入

```
1 1
day
may
gray
way
```

### 输出

```
aaaa
```

## 样例 #3

### 输入

```
2 1
a
a
a
a
a
a
e
e
```

### 输出

```
aabb
```

## 样例 #4

### 输入

```
2 1
day
may
sun
fun
test
hill
fest
thrill
```

### 输出

```
NO
```

# 题解

## 作者：斜揽残箫 (赞：3)

**【题目大意】**

感觉看翻译都看不懂。（逃

给定 $n$ 首四行诗组成的长诗，对于每首四行诗判断是否为 $(aaaa)$，$(abab) $，$(abab)$，$(abba)$ 中的一种，再判断由 $n$ 首四行诗组成的长诗是不是为那四种的一种，是的话输出类型，否则输出 $NO$。

**【解题思路】**

对于每首四行诗的类型判断 ： 寻找每句从后往前数第 $k$ 个元音字母，找到后，从这个元音字母到这句结尾的字符串就是这句的押韵方式，如果找不到 $k$ 个元音字母，就不成立，直接输出 $NO$ 即可。

比较一首四行诗的四句押韵的类型，得出这首四行诗压的什么韵。

再比较全篇压的什么韵。得出答案。

感觉就是一环套一环，看每个句子是否有解，再看一首四行诗是否有解，最后看全篇是否有解，有解输出答案，无解输出 $NO$ 。

**【Code】**

```cpp
#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
/*================================================*/

int n,k;
string s[5];//每句诗的后缀。
bool flag[5],err;//每一首四行诗压的韵。

/*================================================*/
inline bool judge(char c) {//判断元音
  if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') 
    return true;
  
  return false;
}

inline int search(string a,int lim) {//寻找第 k 个元音
  for(int i = a.size() - 1;i >= 0;i --) {
    if(judge(a[i])) -- lim;
    if(lim == 0) return i;//返回现在的位置
  }
  return -1;//无解，那么全篇有一个不押韵的，肯定不押韵。
}

string suf(string a,int t) {
    //取出从后往前数第 k 个元音的位置到末尾的字符串.
  string b = "";
  for(int i = a.size() - 1;i >= t;i --) {
    b += a[i];
  }
  return b;
}

void check()
{
  err = false;// error 错误
  //  flag从 1 到 4 分别为 aaaa ，aabb ， abab ，abba .
  if(s[1] == s[2] && s[2] == s[3] && s[3] == s[4]) flag[1] = true;
  else if(s[1] == s[2] && s[3] == s[4]) flag[2] = true;
  else if(s[1] == s[3] && s[2] == s[4]) flag[3] = true;
  else if(s[1] == s[4] && s[2] == s[3]) flag[4] = true;
  else err = true;//不属于任何一种类型，此首不押韵，全都不押韵。
}
/*=================================================*/

signed main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
  scanf("%d%d",&n,&k);
  while(n --) {
    for(int i = 1;i <= 4;i ++) {
      string a; cin >> a;
      int id = search(a,k);
      if(id == -1) {
        printf("NO\n");
        return 0;
      } else {
        s[i] = suf(a,id);
      }
    }
    check();
    if(err) {
      printf("NO\n");
      return 0;
    }
  }
  if(flag[1] && !flag[2] && !flag[3] && !flag[4]) printf("aaaa\n");
  // 满足有一首为四句压韵相同，那么输出 aaaa
  else if(flag[2] && !flag[3] && !flag[4]) printf("aabb\n");
  // 满足都为 aabb。 
  else if(flag[3] && !flag[2] && !flag[4]) printf("abab\n");
  // 满足都为 abab。 
  else if(flag[4] && !flag[2] && !flag[3]) printf("abba\n");
  // 满足都为 abba。 
  else printf("NO\n");
  // 有多种类型，不属于任何一种押韵方式。
  return 0;
}
```

---

## 作者：forgotmyhandle (赞：1)

## 题目

[你谷传送门](https://www.luogu.com.cn/problem/CF138A)

[原题传送门](https://codeforces.com/problemset/problem/138/A)

~~这边建议能看懂英文的直接看原题，别看翻译~~

## 分析
既然题目要求求出所有四行诗共同的形态，那我们就想到可以用位运算。
我们用二的次方来表示每一种形态，然后把每一篇诗的形态或起来，就可以得到最终的形态。输出的时候再拿个函数转一下就行了。

有了基本框架，我们就可以开始构造特殊情况。题目中说到如果有 aaaa 这种类型，那么它可以等同于任何别的类型。根据这个特征，我们可以规定这种类型为 0，这样它对答案就没有影响。题目中又说如果几篇四行诗中只要有一篇不属于任何类型，那这几篇四行诗就都不属于任何类型。所以可以将不属于任何类型的四行诗归为 7，也就是二进制 111，这样无论谁跟他或，都还是错误。

对于别的类型，如果在给出的几篇四行诗中有任意两篇类型不同，那或出来的答案就不是二的次方，所以在最终翻译答案的函数中，可以只翻译所有二的次方，其他一概判错。当然还要记得 aaaa 这种类型。

## 代码
```cpp
#include <iostream>
using namespace std;
int n, k;
string err = "";
string getsuf(string str) { // 《大 膜 你》，如题目要求 
    int sise = str.size(), vcnt = 0;
    string ret;
    for (int i = sise - 1; i >= 0; i--) {
        vcnt += (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u');
        ret += str[i];
        if (vcnt == k) {
            return ret;
        }
    }
    err += "/"; // 元音不够，返回错误，但是错误每次都要改变，不然可能会误判 
    return err;
}
struct poem { // 结构体用于存储每一篇四行诗 
    int r;    // r 代表该四行诗的类型 
    string s1, s2, s3, s4; // 四行诗，所以四行（笑
    void getr() {          // 用于获取当前四行诗的类型 
        string j1 = getsuf(s1), j2 = getsuf(s2), j3 = getsuf(s3), j4 = getsuf(s4); // 每句话的后缀 
        if (j1 == j2 && j2 == j3 && j3 == j4)                                      // 每个后缀都相等，aaaa 
            r = 0;
        else if (j1 == j2 && j3 == j4) 
            r = 1;
        else if (j1 == j3 && j2 == j4) 
            r = 2;
        else if (j1 == j4 && j2 == j3) 
            r = 4;
        else                                                                       // 不属于任何类型，错误 
            r = 7;
    }
} ps[2505];
string conv(int tp) { // 用于把整形的答案转成输出的答案 
    return (tp == 1 ? "aabb" : (tp == 2 ? "abab" : (tp == 4 ? "abba" : (tp == 0 ? "aaaa" : "NO"))));
}
int main() {
    int ans = 0;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> ps[i].s1 >> ps[i].s2 >> ps[i].s3 >> ps[i].s4;
        ps[i].getr();
        ans |= ps[i].r; // 好东西 
    }
    cout << conv(ans);
    return 0;
}
```

---

## 作者：Michael1234 (赞：1)

- 本题可以使用**模拟**的思路：

- 将每组字符串的后缀取出，判断该组字符串的类型。

- 注意特判每组字符串的类型是否互相兼容，例如：`aaaa` 兼容 `abab`。

- 同时还需特判元音不足的情况即可，代码实现难度不大。

## CODE

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5,aabb=1,abba=2,abab=3,aaaa=4,NO=0;
char s[5][N],now1[N],now2[N],now3[N],now4[N];
int type,n,k,cnt,tmp;
inline bool istrue(char a)
{//判断元音
	if(a=='a'||a=='e'||a=='i'||a=='o'||a=='u')
	{
		return true;
	}
	return false;
}
inline void pre()
{//清空所有数组
	memset(now1,'\0',sizeof(now1));
	memset(now2,'\0',sizeof(now2));
	memset(now3,'\0',sizeof(now3));
	memset(now4,'\0',sizeof(now4));
	for(int i=0;i<5;i++) memset(s[i],'\0',sizeof(s[i]));
	return;
}
inline bool correct(int a,int b)
{//两个字符串是否兼容
	if(a==aaaa||b==aaaa||a==b)
	{
		return true;
	}
	return false;
}
inline int mini(int a,int b)
{//取其中被兼容的字符串（我懒）
	if(a==aaaa)
	{
		return b;
	}
	return a;
}
inline bool same(char a[],char b[])
{//判断两个字符串是否相等
	if(strlen(a)!=strlen(b))
	{
		return NO;
	}
	for(int i=0;i<strlen(a);i++)
	{
		if(a[i]!=b[i])
		{
			return false;
		}
	}
	return true;
}
inline int check()
{//判断字符串的类型
	for(int i=strlen(s[1])-1;i>=0;i--)
	{
		if(istrue(s[1][i])) ++cnt;
		if(cnt==k)
		{
			for(int j=i;j<strlen(s[1]);j++)
			{
				now1[j-i]=s[1][j];
			}
			cnt=0;
			break;
		}
	}
	for(int i=strlen(s[2])-1;i>=0;i--)
	{
		if(istrue(s[2][i])) ++cnt;
		if(cnt==k)
		{
			for(int j=i;j<strlen(s[2]);j++)
			{
				now2[j-i]=s[2][j];
			}
			cnt=0;
			break;
		}
	}
	for(int i=strlen(s[3])-1;i>=0;i--)
	{
		if(istrue(s[3][i])) ++cnt;
		if(cnt==k)
		{
			for(int j=i;j<strlen(s[3]);j++)
			{
				now3[j-i]=s[3][j];
			}
			cnt=0;
			break;
		}
	}
	for(int i=strlen(s[4])-1;i>=0;i--)
	{
		if(istrue(s[4][i])) ++cnt;
		if(cnt==k)
		{
			for(int j=i;j<strlen(s[4]);j++)
			{
				now4[j-i]=s[4][j];
			}
			cnt=0;
			break;
		}
	}
  	if(same(now1,now2)&&same(now2,now3)&&same(now3,now4))
	{
		return aaaa;
	}
	else if(same(now1,now2)&&same(now3,now4))
	{
		return aabb;
	}
	else if(same(now1,now3)&&same(now2,now4))
	{
		return abab;
	}
	else if(same(now1,now4)&&same(now2,now3))
	{
		return abba;
	}
	else
	{
		return NO;
	}//分类
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>k>>s[1]>>s[2]>>s[3]>>s[4];
	type=check();//先取出第一组，方便后面作比较
	if(!type)
	{
		cout<<"NO";
		return 0;
	}
	for(int q=2;q<=n;q++)
	{
		pre();//记得预处理
		cin>>s[1]>>s[2]>>s[3]>>s[4];
		for(int i=1;i<=4;i++)
		{
			tmp=0;
			for(int j=0;j<strlen(s[i]);j++)
			{
				if(istrue(s[i][j]))
				{
					++tmp;
				}
			}
			if(tmp<k)//判断元音是否足够
			{
				cout<<"NO";
				return 0;
			}
		}
		if(!correct(type,check()))
		{//当两个字符串不兼容
			cout<<"NO";
			return 0;
		}
		else
		{//否则取被兼容者
			type=mini(type,check());
		}
	}
	if(type==aaaa)
	{
		cout<<"aaaa";
	}
	else if(type==aabb)
	{
		cout<<"aabb";
	}
	else if(type==abba)
	{
		cout<<"abba";
	}
	else if(type==abab)
	{
		cout<<"abab";
	}
	else
	{
		cout<<"NO";
	}
	return 0;
}

~~~

---

## 作者：Jerrywang09 (赞：1)

# 先说几句

这个难度不对，我看应该是 普及/提高-。
这是我第一篇题解，如有错误，请及时提出。
希望过审，谢谢！

# 解题思路

先是两个函数，分别是判断元音字母和诗的形态的。不用多说。
特别注意 judgeType 函数的顺序，千万不能错。

关键在于主函数。
读入数据，不用多说。我用的是二维 string 数组。
其中，第一维表示第几个四行，第二维表示每个四句话中的每一行。

我又新建的 y 数组，结构同上。用于保存每一句话的“韵”，方便之后的判断。
详细的解释看注释。

特别的，substr 函数，第二个参数可以省略不写，不写，就表示取到底。
例如：
```cpp
string s="I love Luogu";
```
则，s.substr($7$) 所取出的内容就是 " Luogu "。

接下来，是最关键的部分了。
先对每一个四行绝句判断形态。如果出现不明形态（函数返回 No ），直接结束程序。

最后，建立集合 $S$ 。遍历 $a$ 数组。如果出现 aaaa：

我们知道， **aaaa 可以看作 aabb 、abab 、abba。**
所以，aaaa 就可以看作“百搭”，不用管它。无论之后出现怎样的形态， aaaa 都可以匹配上。
其余的，都放进集合 $S$ 里。只要集合 $S$ 出现 $2$ 个元素，说明不能统一全诗的形态，就结束程序。

如果没法结束程序：
## S为空
就说明都是 aaaa，直接 continue 掉了，以至于没有元素可以放进集合。输出 aaaa 即可。
## S有且仅有一个元素
输出那个唯一的形态即可。

注意，iterator 也是可以按照指针处理的，可以用 \* 号访问内存中的值。
# 奉上代码
千万不要抄，小心棕名！
```cpp
// 138A Literature Lesson
#include <bits/stdc++.h>
#define var long long
using namespace std;

inline bool isYuanYin(char c)
{
	return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';
}
 
inline string judgeType(string a[])
{
	if(a[0]==a[1] && a[1]==a[2] && a[2]==a[3])
		return "aaaa";
	if(a[0]==a[1] && a[2]==a[3])
		return "aabb";
	if(a[0]==a[3] && a[1]==a[2])
		return "abba";
	if(a[0]==a[2] && a[1]==a[3])
		return "abab";
	return "NO";
}
 
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n; cin>>n;
	int m; cin>>m;
	cin.get();
	string s[n][4];
	for(int i=0; i<n; i++)
		for(int j=0; j<4; j++)
			cin>>s[i][j];
	
	string y[n][4];
	for(int i=0; i<n; i++)
		for(int j=0; j<4; j++)
		{
			int cnt=0;
			int k;
			for(k=s[i][j].size(); k>=0; k--)
				if(isYuanYin(s[i][j][k]))
				{
					cnt++;
					if(cnt==m) break；
				}
			if(cnt==m)
				y[i][j]=s[i][j].substr(k);
			else
			{
				puts("NO");
				//return 1;
				return 0;
			}
		}
		
	/*
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<4; j++)
			cout<<y[i][j]<<endl;
		cout<<endl;
	}
	*/	
	
	string a[n];
	for(int i=0; i<n; i++)
	{
		a[i]=judgeType(y[i]);
		if(a[i]=="NO")
		{
			puts("NO");
			//return 2;
			return 0;
		}
	}
	
	set<string> S;
	for(int i=0; i<n; i++)
	{
		if(a[i]=="aaaa")
			continue;
		S.insert(a[i]);
		if(S.size()>=2)
		{
			puts("NO");
			//return 3;
			return 0;
		}
	}
	
	if(S.empty())
		puts("aaaa");
	else
		cout<<*S.begin();
 
    return 0;
}

```

---

## 作者：zym20249_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF138A)

## 题意
行诗的形态有四种，相同的字母表示两个单词从后往前数第 $k$ 个元音之后的后缀相同（不是元音相同）。后缀都为空视为不相等。现给定 $n$ 篇四行诗和一个正整数 $k$，输出每首四行诗的共同类型，如果没有，输出 `NO`。

## 思路
简单的来说就是要先找到每四行诗压的是什么韵（元音字母就是 `a` `e` `i` `o` `u`）。我们只需要从枚举从后往前 $k$ 个数，分与雨接下来的几行分别对比之后就可以了，基本就是个最简单的套娃。这里需要注意一下 `aaaa` 其实就是 `abba` `aabb` `abab` 的特殊情况。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int k,n;
vector<string> poem;
string f(string s)
{
	const string yy="aeiou";
	int cnt=0;
	for(int i=s.size()-1;i>=0;i--)
		if(yy.find(s[i])!=-1)
		{
			cnt++;
			if(cnt==k) return s.substr(i);
		}
	return "NO";
}
string kind()
{
	string r[4];
	for(int i=0;i<4;i++) r[i]=f(poem[i]);
	if(r[0]=="NO"||r[1]=="NO"||r[2]=="NO"||r[3]=="NO") return "NO";
	if(r[0]==r[1]&&r[1]==r[2]&&r[2]==r[3]) return "aaaa";
	if(r[0]==r[1]&&r[2]==r[3]) return "aabb";
	if(r[0]==r[2]&&r[1]==r[3]) return "abab";
	if(r[0]==r[3]&&r[1]==r[2]) return "abba";
	return "NO";
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	poem.resize(4);
	cin>>n>>k;
	string bb="aaaa",aa;
	string cc;
	while(n--)
	{
		for(int i=0;i<4;i++) cin>>poem[i];
		aa=kind();
		if(aa!=bb&&(bb=="aaaa"||aa=="aaaa"))
		{
			if(bb=="aaaa") cc=bb=aa;
			else cc=aa=bb;
			continue;
		}
		if((aa!=bb&&bb!="aaaa")||aa=="NO")
		{
			puts("NO");
			return 0;
		}
		else bb=aa;
	}
	if(cc=="")cout<<aa;
	else cout<<cc;
	return 0;
}
```

---

## 作者：czh___ (赞：0)

题目比较长，大概意思是：多组样例，每组第一个数字是小节数 $n$，$4$ 行单词一个小节第二个是第几个元音 $k$（从单词结尾往前面数）。

接下来是 $4 \times n$ 行：

如果一个小节的 $4$ 个单词从第 $k$ 个元音到单词结尾都一样，那这个小节就是 `aaaa` 型。

第一个和第三个一样，第二个和第四个一样就是 `abab` 型。

同理还有 `aabb` 型，`abba` 型。 

否则就不是韵文。

如果给出的所有小节都有同样的类型（`aaaa` 可以看成是 `abba`，`aabb`，`abab` 的特殊情况）就输出这首诗的类型否则输出 `NO`。

模拟一下，没用什么算法。我写的比较长：


```cpp
#include <iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int type[2505];
int rymic(string ,string ,string,string,int);
int main (void){
    int n,k,i;
    string s1,s2,s3,s4;
    cin>>n>>k;
    for(i=0;i<n;i++)//	分为n组 每组4句   分别决定每组的rymic 第i组的rymic为 type[i] 
    {
        cin>>s1>>s2>>s3>>s4;
        type[i]=rymic(s1,s2,s3,s4,k);
    }
	int tmp[5]={0};
	 
        for(i=0;i<n;i++)
			tmp[type[i]]++;
		
        if(tmp[4]==n)
            cout<<"aaaa"<<endl;
        else if(tmp[1]+tmp[4]==n)
            cout<<"aabb"<<endl;
        else if(tmp[2]+tmp[4]==n)
            cout<<"abab"<<endl;
        else if(tmp[3]+tmp[4]==n)
            cout<<"abba"<<endl;
    	else
        cout<<"NO"<<endl;
return 0;
}
 
int rymic(string s1,string s2,string s3,string s4,int k){
    int i,j,cnt,flag;
    if(k==0) return 0;
        cnt=0;
        flag=0;
        for(j=s1.length()-1;j>=0;j--)
        {
            if(s1[j]=='a'||s1[j]=='e'||s1[j]=='i'||s1[j]=='o'||s1[j]=='u')
            cnt++;
            
            if(cnt==k)
            {    flag=1;
                break;
            }
        }//j点标记第n个元音的地方 
        if(flag==0) return 0;//非标记退出  说明找不到目标元音  
 
        s1=s1.substr(j);//从第n个元音往后 
      
		cnt=0;
        flag=0;
        for(j=s2.length()-1;j>=0;j--)
        {
            if(s2[j]=='a'||s2[j]=='e'||s2[j]=='i'||s2[j]=='o'||s2[j]=='u')
            cnt++;
            if(cnt==k)
            {    flag=1;
                break;
            }
        }
        if(flag==0) return 0;
 
        s2=s2.substr(j);
  
        cnt=0;
        flag=0;
        for(j=s3.length()-1;j>=0;j--)
        {
            if(s3[j]=='a'||s3[j]=='e'||s3[j]=='i'||s3[j]=='o'||s3[j]=='u')
            cnt++;
            if(cnt==k)
            {    flag=1;
                break;
            }
        }
        if(flag==0) return 0;
 
        s3=s3.substr(j);  
    
        cnt=0;
        flag=0;
        for(j=s4.length()-1;j>=0;j--)
        {
            if(s4[j]=='a'||s4[j]=='e'||s4[j]=='i'||s4[j]=='o'||s4[j]=='u')
            cnt++;
            if(cnt==k)
            {    flag=1;
                break;
            }
        }
        if(flag==0) return 0;
 
        s4=s4.substr(j);
 
            if(s1==s2&&s2==s3&&s3==s4)
            	return 4;
 
            if(s1==s2&&s3==s4)
            return 1;//aabb
 
            if(s1==s3&&s2==s4)
            return 2;//abab
 
            if(s1==s4&&s2==s3)
            return 3;
 
        return 0;//abba
}
```


[出自](https://blog.csdn.net/qq_35003691/article/details/76163010?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522CF9AB1D4-8D4C-4FC9-95BF-F1A3F332391E%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=CF9AB1D4-8D4C-4FC9-95BF-F1A3F332391E&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-76163010-null-null.142^v100^pc_search_result_base5&utm_term=Literature%20Lesson&spm=1018.2226.3001.4187)

---

## 作者：FireFy (赞：0)

### 题目大意

共有 $n$ 个四行诗，诗歌中的所有行都由小写的拉丁字母组成（不包含空格）。

字母 'a'，'e'，'i'，'o'，'u' 是元音字母。

- 如果两行的后缀从第 $ k $ 个元音字母（从末尾开始计数）开始相同，则这两行**押韵**。
- 如果一行的元音字母少于 $k$ 个，则该行无法与其他行押韵。

##### **举个栗子：**

如果 $k=1$，`commit` 和 `hermit` 押韵（相应的后缀相等于 `it` ）。

如果 $k=2$，则它们不押韵（`ommit` $\neq$  `ermit`）。



四行诗可以包含四种不同的押韵方案，即以下几种（相同的字母代表押韵的行）：

- `aabb`
- `abab`
- `abba`

如果四行诗的所有行全部押韵，则四行诗可以属于任何押韵方案（这种情况用 aaaa 表示）。

如果诗歌的所有四行诗属于相同的押韵方案，那么我们可以认为整首诗属于这种押韵方案。

请你判断给出的一首长诗中的押韵方式是什么。

### 思路

#### **大模拟**

遍历每个四行诗，找到每行诗中倒数第 $k$ 个元音。

```cpp
int vowel(int v,int u)//判断元音并返回目标元音的位置 
{
	int sum=0,i;
	for(i=v;i>=1;i--)
	{
		if(s[u][i]=='a'||s[u][i]=='e'||s[u][i]=='i'||s[u][i]=='o'||s[u][i]=='u') sum++;
		if(sum==k) break;
	}
	return i;
}
```

判断押韵方式。

```cpp
int rym(int s1,int s2,int s3,int s4)//判断四行诗的押韵方式 
{
	//cout<<s[1].substr(vowel(s1,1),s1-vowel(s1,1))<<" "<<s[2].substr(vowel(s2,2),s2-vowel(s2,2))<<" "<<s[3].substr(vowel(s3,3),s3-vowel(s3,3))<<" "<<s[4].substr(vowel(s4,4),s4-vowel(s4,4))<<endl;
	if(s[1].substr(vowel(s1,1),s1-vowel(s1,1))==s[2].substr(vowel(s2,2),s2-vowel(s2,2))&&s[3].substr(vowel(s3,3),s3-vowel(s3,3))==s[4].substr(vowel(s4,4),s4-vowel(s4,4)))
	{
		if(s[2].substr(vowel(s2,2),s2-vowel(s2,2))==s[3].substr(vowel(s3,3),s3-vowel(s3,3))) return 1;//aaaa
		else return 2;//aabb
	}
	else if(s[1].substr(vowel(s1,1),s1-vowel(s1,1))==s[3].substr(vowel(s3,3),s3-vowel(s3,3))&&s[2].substr(vowel(s2,2),s2-vowel(s2,2))==s[4].substr(vowel(s4,4),s4-vowel(s4,4))) return 3;//abab
	else if(s[1].substr(vowel(s1,1),s1-vowel(s1,1))==s[4].substr(vowel(s4,4),s4-vowel(s4,4))&&s[2].substr(vowel(s2,2),s2-vowel(s2,2))==s[3].substr(vowel(s3,3),s3-vowel(s3,3))) return 4;//abba
	else 
	{
		cout<<"NO";
		return -1;
	}
}
```

然后将每个四行诗的押韵方式存储起来，对比一致就输出 `YES`，不一致就输出 `NO`。

### AC CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
string s[5];
int book[3010];
int n,k;
int vowel(int v,int u)//判断元音并返回目标元音的位置 
{
	int sum=0,i;
	for(i=v;i>=1;i--)
	{
		if(s[u][i]=='a'||s[u][i]=='e'||s[u][i]=='i'||s[u][i]=='o'||s[u][i]=='u') sum++;
		if(sum==k) break;
	}
	return i;
}
int rym(int s1,int s2,int s3,int s4)//判断四行诗的押韵方式 
{
	//cout<<s[1].substr(vowel(s1,1),s1-vowel(s1,1))<<" "<<s[2].substr(vowel(s2,2),s2-vowel(s2,2))<<" "<<s[3].substr(vowel(s3,3),s3-vowel(s3,3))<<" "<<s[4].substr(vowel(s4,4),s4-vowel(s4,4))<<endl;
	if(s[1].substr(vowel(s1,1),s1-vowel(s1,1))==s[2].substr(vowel(s2,2),s2-vowel(s2,2))&&s[3].substr(vowel(s3,3),s3-vowel(s3,3))==s[4].substr(vowel(s4,4),s4-vowel(s4,4)))
	{
		if(s[2].substr(vowel(s2,2),s2-vowel(s2,2))==s[3].substr(vowel(s3,3),s3-vowel(s3,3))) return 1;//aaaa
		else return 2;//aabb
	}
	else if(s[1].substr(vowel(s1,1),s1-vowel(s1,1))==s[3].substr(vowel(s3,3),s3-vowel(s3,3))&&s[2].substr(vowel(s2,2),s2-vowel(s2,2))==s[4].substr(vowel(s4,4),s4-vowel(s4,4))) return 3;//abab
	else if(s[1].substr(vowel(s1,1),s1-vowel(s1,1))==s[4].substr(vowel(s4,4),s4-vowel(s4,4))&&s[2].substr(vowel(s2,2),s2-vowel(s2,2))==s[3].substr(vowel(s3,3),s3-vowel(s3,3))) return 4;//abba
	else 
	{
		cout<<"NO";
		return -1;
	}
}
void trans(int t)
{
	if(t==1) cout<<"aaaa";
	if(t==2) cout<<"aabb";
	if(t==3) cout<<"abab";
	if(t==4) cout<<"abba";
}
int main()
{
	int i,j,m,s1,s2,s3,s4;
	cin>>n>>k;
	for(i=1;i<=n;i++)
	{
		cin>>s[1]>>s[2]>>s[3]>>s[4];
		s1=s[1].size(),s2=s[2].size(),s3=s[3].size(),s4=s[4].size();
		if(k>s1||k>s2||k>s3||k>s4)//特判目标元音位置是否大于当前序列 
		{
			cout<<"NO";
			return 0;
		}	
		book[i]=rym(s1,s2,s3,s4);//book[i]存储当前四行诗的押韵方式 
		if(book[i]==-1) return 0;
	}
	//for(i=1;i<=n;i++) cout<<book[i]<<" ";
	//cout<<endl;
	int temp,aa=1;
	if(n==1) //特判是否只有一个四行诗 
	{
		trans(book[1]);
		return 0;
	}
	for(i=1;i<=n;i++) if(book[i]!=1) aa=0;//特判全诗是否都是aaaa的类型 
	for(i=n;i>=1;i--) //记录下最靠末尾的不是aaaa类型的四行诗 
	{
		if(book[i]!=1) temp=book[i];
	}
	for(i=2;i<=n;i++)
	{
		if(book[i]==1) continue;
		if(book[i-1]!=book[i]&&book[i-1]!=1)
		{
			cout<<"NO";
			return 0;
		} 
	}
	if(aa) cout<<"aaaa";
	else if(book[n]==1) trans(temp);
	else trans(book[n]);
	
} 
/*
2 1
day
may
gray
way
hay
foray
lay
bay*/
```

#### 完结撒花！！！

---

## 作者：weihaozhen2010 (赞：0)

# 题意：

[CF138A](https://www.luogu.com.cn/problem/CF138A)

# 思路：

- 纯纯是一道模拟题。

- 每四句诗为一组，每句诗都从后往前模拟到第 $k$ 个元音，用 [substr](https://blog.csdn.net/weixin_42240667/article/details/103131329) 截取出它之后的字符串。

- 如果有一句诗没有第 $k$ 个元音则要输出 `NO`。

- 接着就可以判断是哪种类型即可：`aaaa`，`aabb`，`abba`，`abab`。依次统计每种类型的数量。

- 如果哪一种类型都不是的话需要输出 `NO`。

- 当模拟完所有的诗句之后，就可以输出了。

- 如果仅有一种类型有数量：

  `if(aaaa>0&&aabb==0&&abba==0&&abab==0) cout<<"aaaa";`
  
  `if(aaaa==0&&aabb>0&&abba==0&&abab==0) cout<<"aabb";`
  
  `if(aaaa==0&&aabb==0&&abba>0&&abab==0) cout<<"abba";`
  
  `if(aaaa==0&&aabb==0&&abba==0&&abab>0) cout<<"abab";`

  输出即可。

- 如果 `aaaa` 的数量有多个，并且其他类型的仅有一种类型有数量：

  `if(aaaa>0&&aabb>0&&abba==0&&abab==0) cout<<"aabb";`
  
  `if(aaaa>0&&aabb==0&&abba>0&&abab==0) cout<<"abba";`
  
  `if(aaaa>0&&aabb==0&&abba==0&&abab>0) cout<<"abab";`

  就直接输出除 `aaaa` 的那种类型即可。因为 `aaaa` 可以与其他任意一种类型搭配。
  
- 都不是的话则输出 `NO`。

# 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,k,sum=0;
int aaaa=0;
int aabb=0;
int abab=0;
int abba=0;
bool flag1=0;
bool flag2=0;
bool flag3=0;
bool flag4=0;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		string a,b,c,d;
		string x1,x2,x3,x4;
		cin>>a>>b>>c>>d;
		sum=0;
		for(int j=a.size()-1;j>=0;j--)
		{
			if(a[j]=='a'||a[j]=='e'||a[j]=='i'||a[j]=='o'||a[j]=='u') 
			{
				sum++;
			}
			if(sum==k)
			{
				x1=a.substr(j,a.size()-j);
				flag1=1;
				break;
			}
		}
		sum=0;
		for(int j=b.size()-1;j>=0;j--)
		{
			if(b[j]=='a'||b[j]=='e'||b[j]=='i'||b[j]=='o'||b[j]=='u') 
			{
				sum++;
			}
			if(sum==k)
			{
				x2=b.substr(j,b.size()-j);
				flag2=1;
				break;
			}
		}
		sum=0;
		for(int j=c.size()-1;j>=0;j--)
		{
			if(c[j]=='a'||c[j]=='e'||c[j]=='i'||c[j]=='o'||c[j]=='u') 
			{
				sum++;
			}
			if(sum==k)
			{
				x3=c.substr(j,c.size()-j);
				flag3=1;
				break;
			}
		}
		sum=0;
		for(int j=d.size()-1;j>=0;j--)
		{
			if(d[j]=='a'||d[j]=='e'||d[j]=='i'||d[j]=='o'||d[j]=='u') 
			{
				sum++;
			}
			if(sum==k)
			{
				x4=d.substr(j,d.size()-j);
				flag4=1;
				break;
			}
		}
		if(flag1==0||flag2==0||flag3==0||flag4==0)
		{
			cout<<"NO";
			return 0; 
		}
		if(x1==x2&&x2==x3&&x3==x4) aaaa++;
		else if(x1==x2&&x2!=x3&&x3==x4) aabb++;
		else if(x1!=x2&&x2==x3&&x3!=x4) abba++;
		else if(x1==x3&&x2==x4&&x1!=x2) abab++;
		else 
		{
			cout<<"NO";
			return 0;
		}
	}
	if(aaaa>0&&aabb==0&&abba==0&&abab==0) cout<<"aaaa";
	else if(aaaa==0&&aabb>0&&abba==0&&abab==0) cout<<"aabb";
	else if(aaaa==0&&aabb==0&&abba>0&&abab==0) cout<<"abba";
	else if(aaaa==0&&aabb==0&&abba==0&&abab>0) cout<<"abab";
	else if(aaaa>0&&aabb>0&&abba==0&&abab==0) cout<<"aabb";
	else if(aaaa>0&&aabb==0&&abba>0&&abab==0) cout<<"abba";
	else if(aaaa>0&&aabb==0&&abba==0&&abab>0) cout<<"abab";
	else cout<<"NO";
	return 0;
}
```

---

## 作者：liuli688 (赞：0)

### 思路：
本题基本没有难点，难度主要在于代码实现能力。

直接暴力从后往前扫，扫到第 $k$ 个元音字母时退出，用 substr 截取后缀，再进行判断。

最难的部分是处理押韵，细节很多。一开始将答案设为空串，表示未确定类型；对于每段诗，确定类型后判断，如果是空串，则变为这个类型；因为 aaaa 型可以和任意类型搭配，所以遇到 aaaa 时也要变为这个类型；另外有一个坑是如果答案是当前类型则不变，不输出 `NO`。否则输出 `NO`，结束程序。
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std; 

#define fp(i,a,b) for(i = a;i < b;i++)
#define fm(i,a,b) for(i = a;i > b;i--)
#define fl(i,a,b) for(i = a;i <= b;i++)
#define fg(i,a,b) for(i = a;i >= b;i--)
#define bk break
#define ctn continue
#define reg register

#define rhyme(out); if(ans == "" || ans == "aaaa" || ans == out){ans = out;ctn;}else{writel("NO");return 0;}//更新押韵，注意有三种情况不会不押韵

template <typename T>
inline void read(T &x)//快读
{
    x = 0;
    reg int f = 1;
    reg char ch = getchar();
	while(ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -f;
        ch = getchar();
    }
	while(ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
	x *= f;
}

inline void readl(string &x)//读入字符串
{
    x = "";
    reg char ch = getchar();
    while(ch != '\n')
    {
        x = x + ch;
        ch = getchar();
    }
}

inline void writel(string x)//写出字符串
{
    reg int i;
    int len = x.length();
    fp(i,0,len)
    	putchar(x[i]);
    putchar('\n');
}

bool check(char ch)//判断是否为元音
{
    if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
        return true;
    return false;
}

bool same(string s1,string s2)//比较两个字符串是否相等，特判空串
{
	if(s1 == s2 && s1 != "")
		return true;
	return false;
}

int n,k,cnt;
string s[4],h[4],ans = "";

signed main()
{
    reg int i,j;
    read(n);
    read(k);
    while(n--)
    {
        fp(i,0,4)//输入
            readl(s[i]);
        fp(i,0,4)//处理后缀
        {
        	cnt = 0;
            h[i] = "";//初始为空串
        	fg(j,s[i].length()-1,0)//倒着搜
            {
                if(check(s[i][j]))//对每个字符进行判断
                    cnt++;
                if(cnt == k)
                {
                	h[i] = s[i].substr(j,s[i].length());//截取字符串
                    bk;
                }
            }
		}
        //直接调用函数判断即可。
        if(same(h[0],h[1]) && same(h[0],h[2]) && same(h[2],h[3]))
            if(ans == "")
            {
                ans = "aaaa";
                ctn;
            }
            else
            	ctn;
        if(same(h[0],h[1]) && same(h[2],h[3]))
        	{rhyme("aabb");}
        if(same(h[0],h[2]) && same(h[1],h[3]))
        	{rhyme("abab");}
        if(same(h[0],h[3]) && same(h[1],h[2]))
        	{rhyme("abba");}
        writel("NO");
        return 0;
    }
    writel(ans);
    return 0;
}
```

---

## 作者：sickbot (赞：0)

依次判断每个四行诗的押韵方式，注意遇到 aaaa 要特判。

```cpp
#include <bits/stdc++.h>
using namespace std;
int k,n;
vector<string> poem;
string rhyme(string s){
	const string allvowels="aeiou";
	int cnt=0;
	for(int i=s.size()-1;i>=0;i--){
		if(allvowels.find(s[i])!=-1){
			cnt++;
			if(cnt==k) return s.substr(i);
		}
	}
	return "NO";
}
string kind(){
	string r[4];
	for(int i=0;i<4;i++) r[i]=rhyme(poem[i]);
	if(r[0]=="NO"||r[1]=="NO"||r[2]=="NO"||r[3]=="NO") return "NO";
	if(r[0]==r[1]&&r[1]==r[2]&&r[2]==r[3]) return "aaaa";
	if(r[0]==r[1]&&r[2]==r[3]) return "aabb";
	if(r[0]==r[2]&&r[1]==r[3]) return "abab";
	if(r[0]==r[3]&&r[1]==r[2]) return "abba";
	return "NO";
}
int main(){
ios::sync_with_stdio(0);
cin.tie(0);
	poem.resize(4);
	cin>>n>>k;
	string lastkind="aaaa",thiskind;
	string rm;
	while(n--){
		for(int i=0;i<4;i++) cin>>poem[i];
		thiskind=kind();
		if(thiskind!=lastkind&&(lastkind=="aaaa"||thiskind=="aaaa")){
			if(lastkind=="aaaa") rm=lastkind=thiskind;
			else rm=thiskind=lastkind;
			continue;
		}
		if((thiskind!=lastkind&&lastkind!="aaaa")||thiskind=="NO"){
			puts("NO");
			return 0;
		}
		else lastkind=thiskind;
	}
	if(rm=="")cout<<thiskind;
	else cout<<rm;
	return 0;
}
```


---

## 作者：多米 (赞：0)

题目意思有点难懂，代买有点丑

```
#include<iostream>
using namespace std;
int n,m,a[4],num,sum;
string s[4],str;
bool check(char ch){return ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u';} // 判断是不是元音
int work()
{
	sum=0;
	for(int i=str.length()-1;i>=0;i--)
	{
		sum+=check(str[i]);
		if(sum==m)return i;
	}
	return -1; // 元音字母个数<m
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<4;j++)
		{
			cin>>str;
			num=work(); // 寻找后缀
			if(!~num)
			{
				puts("NO");
				return 0;
			}
			s[j]=str.substr(num); // 得到后缀
		}
		if(s[0]==s[1]&&s[1]==s[2]&&s[2]==s[3])a[0]=1; // aaaa的情况
		else if(s[0]==s[1]&&s[2]==s[3])a[1]=1; // aabb的情况
		else if(s[0]==s[2]&&s[1]==s[3])a[2]=1; // abab的情况
		else if(s[0]==s[3]&&s[1]==s[2])a[3]=1; // abba的情况
		else
		{
			puts("NO");
			return 0;
		}
	}
	if(a[0]&&!(a[1]||a[2]||a[3]))puts("aaaa"); // 全部都是aaaa
	else if(a[1]&&!(a[2]||a[3]))puts("aabb"); // 除aaaa外只有aabb
	else if(a[2]&&!(a[1]||a[3]))puts("abab"); // 除aaaa外只有abab
	else if(a[3]&&!(a[1]||a[2]))puts("abba"); // 除aaaa外只有abba
	else puts("NO"); // 没有满足的条件
	return 0;
}
```

望大佬指点

---

