# STL

## 题目描述

Vasya used to be an accountant before the war began and he is one of the few who knows how to operate a computer, so he was assigned as the programmer.

We all know that programs often store sets of integers. For example, if we have a problem about a weighted directed graph, its edge can be represented by three integers: the number of the starting vertex, the number of the final vertex and the edge's weight. So, as Vasya was trying to represent characteristics of a recently invented robot in his program, he faced the following problem.

Vasya is not a programmer, so he asked his friend Gena, what the convenient way to store $ n $ integers is. Gena used to code in language X-- and so he can use only the types that occur in this language. Let's define, what a "type" is in language X--:

- First, a type is a string "int".
- Second, a type is a string that starts with "pair", then followed by angle brackets listing exactly two comma-separated other types of language X--. This record contains no spaces.
- No other strings can be regarded as types.

More formally: type := int | pair<type,type>. For example, Gena uses the following type for graph edges: pair<int,pair<int,int>>.

Gena was pleased to help Vasya, he dictated to Vasya a type of language X--, that stores $ n $ integers. Unfortunately, Gena was in a hurry, so he omitted the punctuation. Now Gena has already left and Vasya can't find the correct punctuation, resulting in a type of language X--, however hard he tries.

Help Vasya and add the punctuation marks so as to receive the valid type of language X--. Otherwise say that the task is impossible to perform.

## 样例 #1

### 输入

```
3
pair pair int int int
```

### 输出

```
pair<pair<int,int>,int>```

## 样例 #2

### 输入

```
1
pair int
```

### 输出

```
Error occurred```

# 题解

## 作者：Anguei (赞：20)

+ 因为题目要求输入带有嵌套的 `pair`，所以应该首先想到一个递归做法。

+ 由于可能有不成立的情况，所以要开一个字符串保存答案，最后特判。

注意到以上两点就可以了。详见代码。
```cpp
//【CF190C】STL - 洛谷 - Ac
#include <string>
#include <iostream>

bool ok = true;
std::string s, ans;

void input() // 简单的递归 
{
	if (std::cin >> s)
	{
		if (s == "pair")
		{
			ans += "pair<";
			input();
			ans += ",";
			input();
			ans += ">";
		}
		else if (s == "int")
			ans += "int";
	}
	else // 输入不全（意外终止） 
		ok = false;
}

int main()
{
	std::getline(std::cin, s); // 无用的一行输入，吃掉它 
    
	input();
    
	if (!ok)
		ans = "Error occurred";
        
	std::getline(std::cin, s);
	if (s.size()) // 输入有多余 
		ans = "Error occurred";
        
	std::cout << ans << std::endl;
}
```

---

## 作者：Acerkaio (赞：8)

## 题意 :

给出只会出现 pair 和 int 的字符串 , 要求按照给出 pair 和 int 的顺序 , 添加 ' < '   ,   ' > '  ,  ' , ' 这三个符号 , 使得给出的串成为一个合法的类型 。 

## 思路 :
- 根据题意 ， 可能输入带有 pair  , 所以本题采用递归求解 。 

- 输出 Error  occurred 的情况只为多输入或少输入 。

## CODE :


```cpp

#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
bool pd=1;           //用来判断是否出现不合法现象
string a,sum;         //a为每次输入的字符串，sum为总答案

void sd() {
	if(cin>>a) {
		if(a=="pair") {
			sum+="pair<",sd(),sum+=",",sd(),sum+=">";
		} else if(a=="int") {
			sum+="int";
		}
	} else             //如果少输入了，判断为否；
		pd=0;
}

int main() {
	cin>>a;
	sd();
	if(pd==0) {
		cout<<"Error occurred";
	} else {
		if (cin>>a)
			cout<<"Error occurred";
		else
			cout<<sum;
	}
	return 0;
}

```

---

## 作者：myee (赞：4)

#### 思路

大家貌似都是递归做的？

显然这题还可以用**栈**搞啊。

从左往右扫两遍，第一遍判可行，第二遍输出方案。

栈中类型设为 `bool`，表示处理到了每个 `pair` 的哪一项。

简单说，就是每次遇到 `pair` 就进栈并标记为 `false`，每次遇到 `int` 就反复出栈直至遇到 `false` 并把其改为 `true`。

这与**二叉树的中序遍历**类似，`int` 即叶结点，`pair` 即枝结点。

注意一些细节特判，如**根结点即叶子（测试点 `#10`）**、多棵二叉树等等。

#### Code

```cpp
#include <stack>
#include <stdio.h>
typedef long long llt;
typedef unsigned uint;typedef unsigned long long ullt;
typedef bool bol;typedef char chr;typedef void voi;
typedef double dbl;
template<typename T>bol _max(T&a,T b){return(a<b)?a=b,true:false;}
template<typename T>bol _min(T&a,T b){return(b<a)?a=b,true:false;}
std::stack<bol>S;chr C[10];bol Ok[300005];
int main()
{
    uint n=0;
    bol f=false;
    scanf("%*u");
    while(scanf("%s",C)==1)Ok[n++]=C[0]=='i';
    if(n==1)return puts(Ok[0]?"int":"Error occurred"),0;
    for(uint i=0;i<n;i++)
    {
        if(Ok[i])
        {
            if(S.empty()){puts("Error occurred");return 0;}
            while(!S.empty())if(S.top())S.pop();else{S.top()=true;break;}
        }
        else
        {
            if(S.empty()){if(f){puts("Error occurred");return 0;}else f=true;}
            S.push(false);
        }
    }
    if(!S.empty()){puts("Error occurred");return 0;}
    for(uint i=0;i<n;i++)
    {
        if(Ok[i]){printf("int");while(!S.empty()){if(S.top())putchar('>'),S.pop();else{putchar(','),S.top()=true;break;}}}
        else S.push(false),printf("pair<");
    }
    putchar('\n');
	return 0;
}
```


---

## 作者：Jiyuu_no_Tsubasa (赞：3)

首先因为处理时有 $pair$ 类型嵌套情况，

所以我们无法使用循环解决，因此想到递归，

即如下过程：

+ 若为 $pair$，则再依格式处理 $2$ 个字符串（可 $pair$ 可 $int$）
+ 若为 $int$，则直接计入答案

但题中还有一种情况：不合法。

不合法又细分为两种情况：

1. 读入不够
1. 有多余的读入

对于不够的情况，我们用一个 $bool$ 记录，在递归过程中判断；

对于多余的情况，我们在递归完成后再读入一个字符串，判断其是否为空，若不为空，则有多余的读入。

值得说明的一点是，此题不能在处理过程中直接输出，

因为还有不合法的情况，因此需要用一个字符串记录答案。

```
#include<bits/stdc++.h>
using namespace std;
string ans="";
bool flag=1;
void work(){//处理函数
    string s;
    cin>>s;
    if(s=="pair"){
        ans+="pair<";//字符串可以使用加法
        work();//递归
        ans+=",";
        work();
        ans+=">";
    }
    else if(s=="int")
        ans+="int";
    else flag=0;//判断是否不够
    //若需要输入但没有，则缺少输入
}
int main(){
    int n; cin>>n;
    work();
    string s; cin>>s;//判断是否多余
    if(flag==0) cout<<"Error occurred";//若不够
    else if(s.size()!=0 ) cout<<"Error occurred";//若多余
    else cout<<ans;
    return 0;
}

```

---

## 作者：玄学OIER荷蒻 (赞：2)

本蒟蒻 ~~第一次~~ 发题解

- 因为 pair 有嵌套输入要求，于是可以想到递归的做法
- 每一个 pair 就递归两次，没有输入就返回不成立
- 最后需要检查多出来的输入(我WA了一次)
- 由于中途可能出错，所以需要用 ans 字符串来暂时储存答案

最后上代码
```cpp
#include<bits/stdc++.h>//CF190C 
using namespace std;
string ans;//答案字符串 
bool read()
{
	string u;
	if (cin>>u)//是否存在输入 
	{	
		if (u=="pair")
		{
			ans+="pair<";
			if (read())//判断第一个有没有输入 
			{
				ans+=",";
				if (read())//判断第二个有没有输入 
				{
					ans+=">";
					return 1;//输入完以后返回 
				}//否则返回0 
				else return 0;
			}
			else return 0;
		}
		else//int 
		{
			ans+=u;
			return 1;//一个int也是输入完 
		}
	}
	else return 0;//没有输入 
}
int main()
{
	int n;
	cin>>n;//吃掉这个数字 
	bool b=read();
	if (cin>>ans) //额外输入 
	{
		cout<<"Error occurred";
		return 0;
	}
	if (b) cout<<ans;//判断是否正确输入 
	else cout<<"Error occurred";
	return 0;//结束 
}

```


---

## 作者：Xdl_rp (赞：0)

这道题可以递归求解。

我们可以定义一个函数，这个函数就是输出我们题目所要求的：

```cpp
void input() {
	if (cin >> a) {//如果能输入
		if (a == "pair") {//一定是pair或者int
			ans += "pair<";//接上pair
			input();//继续输入
			ans += ",";//加上逗号
			input();//因为pair有两个参数，所以要输入两遍
			ans += ">";//结尾加上
		}
		else {
			ans += "int";//如果是int就加上int
		}
	}
	else flag = 0;//判断，如果输入没了就一定是Error occurred
}
```

如果输入有多余的，就是 `Error occurred` 了。

```cpp
if (flag == 0 || cin >> a) cout << "Error occurred";
```

所以完整的代码就出来了：

```cpp
#include<bits/stdc++.h>
using namespace std;
string ans;
bool flag = 1;
string a;
void input() {
	if (cin >> a) {
		if (a == "pair") {
			ans += "pair<";
			input();
			ans += ",";
			input();
			ans += ">";
		}
		else {
			ans += "int";
		}
	}
	else flag = 0;
}
int read() {
	char c = getchar();
	int g = 0, flag = 1;
	while (!isdigit(c)) {
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c)) g = (g << 1) + (g << 3) + (c ^ 48), c = getchar();
	return g * flag;
}
int main() {
	read();
	input();
	if (flag == 0 || cin >> a) cout << "Error occurred";
	else cout << ans;
	return 0;
}
```


---

## 作者：zbk233 (赞：0)

## 解题思路

这道题明显要用递归实现，具体有几个难点：

如何判断是否合法？

事实上，递归是保证正确性的，出现不合法的情况就只有可能是因为缺少输入或输入过多。

如何输出答案？

因为有不合法的情况存在，所以显然不能直接输出答案，需要用字符串存储答案。

## 代码实现

```cpp
#include<iostream>
#include<cstring> 
using namespace std;
string str,ans,tmp;
int n,flag;
void solve(){
	if(cin>>str){
		if(str=="pair"){
			ans+="pair<";
			solve();
			ans+=',';
			solve();
			ans+='>';
		}
		else{
			ans+="int";
		}
	}
	else{
		flag=1;
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>str;
	solve();
	if(cin>>tmp) flag=1;
	if(flag) cout<<"Error occurred";
	else cout<<ans;
    return 0;
}
```


---

## 作者：Toorean (赞：0)

# 题意
- 给出仅出现 pair 和 int 的字符串，添加 ,、<、> 符号使字符串成为一个合法的数据类型；
- 如果可以成为一个合法的类型，输出修改后的字符串，否则输出 Error  occurred。

# 思路
第一眼看到这个题目，我首先想到的是**递归**来解，第一行输入没有用处，我们可以直接看第二行。因为字符串的数量是不固定的，因此我们可以一边输入一边做递归。如果当前输入的字符串是 pair，继续递归下去。否则跳出递归。如果在递归后仍有数据输入**或**在递归时没有字符串输入了，那么就代表了这一串是不合法的。

# AC CODE
```cpp
#include <iostream>
#include <string>

using namespace std;

int n;	// 无用输入
bool flag = true;	// 判断是否合法
string str, ans;	// ans : 获取答案

bool solve () {
    str = "";
    cin >> str;
    
    if (str == "pair") {
        ans += "pair<";
        if (solve ()) { // 返回 true 代表还有类型，否则不合法
            ans += ",";
        } else {
            flag = false;
        }
        if (solve ()) { 
            ans += ">";
        } else {
            flag = false;
        }
        return 1;
    } else if (str == "int") {
        ans += "int";
        return 1;
    }

    return 0;
}

int main (void) {

    cin >> n;
    solve ();
    if (cin >> str) { flag = false; } 
    // 如果递归完了还需要输入，那么就是不合法的

    if (flag) {
        cout << ans;
    } else {
        cout << "Error occurred";
    }

    return 0;
}
```

---

## 作者：shucai (赞：0)

观察样例，发现可能出现 pair 嵌套，考虑使用递归求解。

我们可以每次输入一个字符串，这个字符串可能为 int 或 pair：
1. 若为 pair，则我们的答案加上一个 `pair<`，然后继续执行递归，当我们这个递归执行完后（即处理完当前这个 pair 的左括号后，逗号前的字符串），我们给我们的答案加上一个 `,`，然后再执行一次递归（即处理逗号后，右括号前的字符串），给我们的答案加上一个 `>`。

可能有点抽象，就是这样：

|进度|答案字符串|
|---|----|---|
| 输入 pair|`pair<`  |
|执行一次递归，处理完这次递归后，得到了一个字符串 $s$|`pair<s`|
|再次执行一次递归，处理完这次递归后，得到了一个字符串 $k$|`pair<s,k>`|


2. 若为 int，直接给答案加上一个 `int` 即可。

当然，本题可能有不合法情况，即输出 `Error occurred` 的情况，有两种不合法的情况：

1. 输入的字符串少了，这种情况我们可以在递归时进行判断，即我们递归时，判断一下它是否有输入，若无，即是不合法情况。

2. 输入的字符串多了，我们可以在递归结束后，再进行一次判断，判断他是否还有输入，若有，即为不合法情况。

另外，由于我们递归完后还要判断它是否还有输入，所以我们不能边递归边输出，要用一个答案字符串存起来。

那么这题就写完了。

### code
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
string ans, s, k;
bool f;
void in(){
  if (cin >> s) {
    if (s == "int") ans += s;
    else 
      if(s == "pair") {
        ans += "pair<";
        in();
        ans += ',';
        in();
        ans += '>';
      }
  }
  else f = 1;
}
signed main(){
  getline(cin, k);
  in();
  getline(cin, s);
  if(f || s.size())
    cout << "Error occurred";
  else
    cout << ans << '\n';
  return 0;
}
```



---

## 作者：yimuhua (赞：0)

## 题意:

给出只会出现 pair 和 int 的字符串, 要求按照给出 pair 和 int 的顺序, 添加 ' < ' , ' > ' , ' , ' 这三个符号, 使得给出的串合法。

*	根据题意，输入带有嵌套的 pair, 所以本题采用递归求解。

*	输出 "Error occurred" 的情况只为多输入或少输入。

## 思路：

合法有两种情况：

*	若为 pair，则再依格式处理 $2$ 个字符串（可 pair 可 int)

*	若为 int，则直接计入答案

不合法又细分为两种情况：

*	对于不够的情况，我们用一个 bool 变量记录，在递归过程中判断；

*	对于多余的情况，我们在递归完成后再读入一个字符串，判断其是否为空，若不为空，则有多余的读入。

**Tip：**
不能在处理过程中直接输出，因为还有不合法的情况，因此用一个字符串记录答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
bool f = 1;
string s, ans;  //ans为答案
void input() {//处理函数
    if(cin >> s) {  //合法
        if(s == "pair") {
            ans += "pair<";
            input();
            ans += ",";
            input();
            ans += ">";
        }
        //递归
        else if(s == "int")
            ans += "int";
    }
    else  //缺少
        f = 0;
    return;
}
int main() {
    getline(cin, s);  //无用，吞掉
    input();
    if(!f)  //不够
        ans = "Error occurred";
    getline(cin, s);  //看看还有没有
    if(s.size())  //多余
        ans = "Error occurred";
    cout << ans;  //输出答案
    return 0;
}
```


---

