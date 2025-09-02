# [ABC064D] Insertion

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc064/tasks/abc064_d

`(` と `)` で構成される $ N $ 文字の文字列 $ S $ が与えられる。$ S $ にいくつかの `(` または `)` を挿入することで正しい括弧列を作りたい。  
 ただし、正しい括弧列は次のように定義されている：

- `()` は正しい括弧列である。
- $ X $ が正しい括弧列であるとき、`(`、$ X $、`)` をこの順につなげたものは正しい括弧列である。
- $ X $、$ Y $ が正しい括弧列であるとき、$ X $ と $ Y $ をこの順につなげたものは正しい括弧列である。
- それ以外の括弧列は正しくない。

そのとき、作れる最も文字数が少ない正しい括弧列を求めなさい。このようなものが複数ある場合は、辞書順最小のものを求めなさい。

## 说明/提示

### 制約

- $ S $ の長さは $ N $ である。
- $ 1\ <\ =\ N\ <\ =\ 100 $
- $ S $ は `(` と `)` のみで構成されている。

## 样例 #1

### 输入

```
3
())```

### 输出

```
(())```

## 样例 #2

### 输入

```
6
)))())```

### 输出

```
(((()))())```

## 样例 #3

### 输入

```
8
))))((((```

### 输出

```
(((())))(((())))```

# 题解

## 作者：TRZ_2007 (赞：3)

## Remarks
发布翻译的来水一篇题解……  
本蒟蒻~~不~~相信，我的那篇翻译~~一定能让人看得懂~~  
所以还是水一篇题解来加深大佬们的思考。  
## Solution
这道题目实际有几个难点，看看样例三知道了。首先我们来分析一下怎么过掉前2个样例。先给出这两个样例。  
```
#1

Input.txt
3
())

Output.txt
(())


#2

Input.txt
6
)))())

Output.txt
(((()))())
```
首先我们来看看#1，输入就是3个字符，让你补全。我们很容易看出，这个字符串需要你补一个```(```，可是怎么来实现呢？

其实很简单，我们只需要一个变量$cut$来判断是否匹配，我们定义$cut$的运算：碰上```(```加一；碰上```)```减一。则，如果$cut$为正数，说明我们少了$cut$个```)```，若$cut$为负数，则我们少了$cut$个```(```。  

这部分的代码

```
for(int i=1;i<=n;i++)
{
    if (str[i] == '(') cut++;
    if (str[i] == ')') cut--;
}
```
### 难道这样就好了吗？
### 出题人：你想多了。
**来看看第三个样例**
```
#3

Input.txt
8
))))((((

Output.txt
(((())))(((())))

```
如果你还用我们上面提到的解法，那就会出错！因为```)```和```(```数量相等！

**怎么办呢？**

也简单，我们只需要……  
**注意，正解来了！！**

我们只需要再定义一个$cut2$，定义如果有出现```)```比```(```多的状况，$cut2$就加一，接下来$cut$就归0，以免重复计算。  

$code$

```
#include <bits/stdc++.h>
using namespace std;

const int N = 110;

char str[N];
int cut1,cut2,n;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>str[i];
	for(int i=1;i<=n;i++)
	{
		if(str[i]=='(')	cut1++;
		if(str[i]==')')
		{
			cut1--;
			if(cut1<0) cut2++,cut1 = 0;
		}
	}
	for(int i=1;i<=cut2;i++)
		cout<<"(";
	for(int i=1;i<=n;i++)
		cout<<str[i];
	for(int i=1;i<=cut1;i++)
		cout<<")";
	cout<<"\n";
}
```

望审核通过……  
$Line$：99

---

## 作者：W_fly_K (赞：1)


## 思路
本题用两个变量，$left$ 和 $right$ 分别储存左边和右边的需要配对的括号。左边的
补全的括号放在左边就行，右边的
补全的括号放在右边边就行。

## _code_
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	int left=0,right=0;
	string a;
	cin>>n>>a;          //输入
	for(int i=0;i<n;i++)//string是从零开始
	{
	if(a[i]=='(')       //判断有多少左括号需要配对
	left++;
	if(a[i]==')')
	{
	left--;             //左边括号减一，因为有右括号和它配对了
	if(left<0)          //当左边括号为0，说明左括号已经与右括号配对了
	{
	left=0;
	right++;            //判断有多少右括号需要配对
	}
	}
	}
	for(int i=1;i<=right;i++)
	cout<<"(";          //补全左括号
	cout<<a;
	for(int i=1;i<=left;i++)
	cout<<")";          //补全右括号
	cout<<endl;         //记得换行
	return 0;
} 
```


---

## 作者：liangbowen (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT2586)

小学生又来写题解啦!

怎么这么多人用栈，根本不需要!

先读入整个字符串，然后枚举每个字符。

如果当前字符是左括号，**往后搜**，有就匹配并消除。

然而消除这个动作太慢了，如果匹配到，只需把它标记为无用字符即可。

如果没有匹配到，表明右括号少了，对应计数器标记。

是右括号就**往前搜**，其余同理。

最后根据计数器补充输出。

## 送上满分代码：

```cpp
#include <iostream>
#include <cstdio>
#include <stack>
using namespace std;
int main()
{
	int len;
	string s;
	scanf("%d", &len);
	cin >> s; 
	string t = s; //操作时会改变原序列，因此要备份一下。 
	int cntL = 0, cntR = 0; //记录匹配完后还剩几个左右括号。 
	
	for (int i = 0; i < len; i++)
	{
		if (s[i] == '(') //往后搜。 
		{
			bool Is_find = true;
			for (int j = i+1; j < len; j++)
				if (s[j] == ')')  //匹配到了。 
				{
					Is_find = false;
					s[i] = s[j] = 'x';
					break;
				}
			if (Is_find) cntR++;   //匹配不到。 
		}
		else if (s[i] == ')') //往前搜。 
		{
			bool Is_find = true;
			for (int j = i-1; j >= 0; j--)
				if (s[j] == '(')
				{
					Is_find = false;
					s[i] = s[j] = 'x';
					break;
				}
			if (Is_find) cntL++;
		}
	}
	for (int i = 1; i <= cntL; i++) printf("(");
	cout << t;
	for (int i = 1; i <= cntR; i++) printf(")");
	printf("\n");  //别忘了换行。 
	return 0;
}
```

---

## 作者：tZEROちゃん (赞：1)

### Upd 2021.04.01
- 修改了排版不整齐的情况；
- 修改了把 $0$ 打成 $1$ 的问题；
- 修改了一处语病。

### Solution

显然是要在原字符串的左侧加上左括号，右侧加上右括号，原因详见原文。

> そのとき、作れる最も文字数が少ない正しい括弧列を求めなさい。このようなものが複数ある場合は、辞書順最小のものを求めなさい。

简单翻译了一下就是说：

> 找出正确的，可以用最少的字符数组成的小括号序列。如果有多个这样的（序列），就找一个字典序最小的。

所以我们开一个栈 $stk$，对于每一个字符，做如下操作：

- 如果 $ch$ 是左括号，将 $0$ 压栈；
- 如果 $ch$ 是右括号：
  - 如果 $stk$ 不是空栈，即可以与一个左括号配对，那么将栈顶元素出栈；
  - 否则让计数器 $lft$ 加 $1$。

然后我们计算出 $stk$ 里还有多少 $0$，这就是未被配对的左括号数，也就是说，这个数字便是要加上的右括号的个数。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
stack <int> stk;
int main() {
	int n;
	cin >> n;
	int lft = 0, rgt = 0;
	string s;
	for (int i = 1; i <= n; i++) {
		char ch; cin >> ch;
		s += ch; 
		if (ch == '(') stk.push(0);
		if (ch == ')') {
			if (stk.empty() == false) {
				stk.pop();
			} else {
				lft++;
			}
		}
	}
	while (stk.empty() == false) {
		stk.pop();
		rgt++;
	}
	while (lft--) cout << '(';
	cout << s;
	while (rgt--) cout << ')';
}
```

---

## 作者：EthanC_ (赞：0)

这道 $ D $ 题没有想象中的困难。
### 思路：
首先输入字符的个数 $ n $，再设两个计数器变量 $ a $ 和 $ b $ 然后边输入字符边判断:
- 如果这个字符为 `(`，那么我们就将第一个计数器 $ a $ 增加 $ 1 $，用 $ a $ 来记录左括号的数量。
- 如果这个字符为 `)`，那么我们就将计数器 $ a $ 减去 $ 1 $，那么剩下 $ a $ 的个数就是没有匹配括号的`(`的数目。
- 如果 $ a $ 小于 $ 0 $，那么我们就将计数器 $ b $ 增加 $ 1 $ 并将计数器 $ a $ 设为 $ 0 $。这个时候$ b $ 的个数表示的就是少的`)`的个数。

### 代码：
思路已经很详细了，代码就不多说了。
```cpp
#include<iostream>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    int n,a=0,b=0;
    char s[10001];
    cin>>n;
    for(int i=0;i<n;++i){
        cin>>s[i];
        if(s[i]=='(')a++;
        if(s[i]==')'){
            a--;
            if(a<0){b++;a=0;}
        }
    }
    for(int i=0;i<b;++i){
        cout<<"(";
    }
    for(int i=0;i<n;++i){
        cout<<s[i];
    }
    for(int i=0;i<a;++i){
        cout<<")";
    }
    return 0;
}   
```


---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15526608.html)

# 题目大意

给你一个只有 `(` 和 `)` 的字符串，请你把这个字符串补全，即让每一个 `(` 都和 `)` 配对。

# 题目分析

发现性质：

$\boxed{\texttt{1.任何一个答案数列都是在原数列的左右两侧添加括号。}}$

$\boxed{\texttt{2.左边添加的一定为 `(`，右边添加的一定为 `)`。}}$

于是好办了，我们用 $lft$ 表示需要在左边加几个 `(`，用 $rgt$ 表示需要在右边加几个 `)`。

至于统计 $lft$ 和 $rgt$，就按括号序列的套路来即可：

定义一个栈 $st$，

如果当前字符是 `(` 则打入 $1$；

如果当前字符是 `)`，若栈不为空，则弹出栈顶；否则则 $lgt\gets lgt+1$，表示栈空了，括号不匹配了，加一个 `(` 吧。

$rgt$ 即为匹配结束时栈内元素的个数。也很好理解：栈内还有元素（如果没有则不输出），这些都是没找到另一半的 `(`，于是我们手动配对即可。

# 代码

```cpp
const int ma=105;

char str[ma];

stack<int>st;

int main(void)
{
	int n=read();
	
	scanf("%s",str+1);
	
	int l(0),r(0);
	
	for(register int i=1;i<=n;i++)
	{
		char now=str[i];
		
		if(now=='(')
		{
			st.push(1);
		} 
		
		else
		{
			if(!st.empty())
			{
				st.pop();
			}
			
			else
			{
				l++;
			}
		}
	}
	
	r=st.size();
	
	while(l--)
	{
		printf("(");
	}
	
	printf("%s",str+1);
	
	while(r--)
	{
		printf(")");
	}
	
	return 0;
}
```

---

## 作者：SUNCHAOYI (赞：0)

读入整个字符串后统计 `(` 与 `)` 的个数是多少。

现在设左右括号需要再添加的个数为 $l,r$。

- 若读入一个 `(` 则说明需要加上一个 `)` 才能完整配对，即 `++r`。

- 若读入一个 `)` 则说明需要加上一个 `)` 才能完整配对，此时有两种情况：$l = 0$ 则说明需要增加 `(` 个数，即 `++l`；$l > 0$ 则说明一组括号已配对，`--l` 即可。

最后先输出增加的 $l$ 个 `(`，然后输出原字符串，最后输出增加的 $r$ 个 `)`。 

**代码：**

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	int n,l = 0,r = 0;
	string str;
	cin>>n>>str;
	for (int i = 0;i < n;++i)
	{
		if (str[i] == '(') ++r;//增加右括号数量
		if (str[i] == ')')//需要左括号
		{
			if (r > 0) --r;//成功配对，增加的右括号数量减少
			else ++l;//增加左括号数量
		}
	}
	for (int i = 1;i <= l;++i) cout<<'(';
	cout<<str;
	for (int i = 1;i <= r;++i) cout<<')';
	cout<<endl;
	return 0;
}

```

---

## 作者：大头leo (赞：0)

### 思路：
- 这题的话一开始我以为是可以在任何地方加括号的。看了样例才发现是只能在开头和结尾加，这样的话思路就会很简单了。

- 主要就是找出多余的括号然后加就可以了，我用了两个变量 _ans1_ 和 _ans2_ 分别记录。输出时输出我们添加的括号即可。

- 我们找到一个前括号就往后面配对，找到一个后括号就往前面配对，如果找到头了就说明它是多余的，此时计数变量相应加一即可。

- 防止判重我们还需要一个标记变量，记录每个括号是否被配对过。

### 注意点：
- 找到一组配对的括号，两者都要标记。且退出循环。

- 一定要换行！不然全wa

### code:
```
#include<bits/stdc++.h>
using namespace std;
char s[101];
int flag[101]={0},ans1,ans2,i,j,n,f;
int main()
{
	cin>>n>>s;
	for(i=0;i<n;i++)
	{
		f=1;
		if(s[i]==')'&&flag[i]==0)			//前括号 
		{
			for(int j=i;j>=0;j--)			//查找 
			{
				if(s[j]=='('&&flag[j]==0)	//如果找到了 
				{
					flag[j]=1;flag[i]=1;	f=0;	break;	//标记，退出循环 
				}
			}
			ans1+=f;						//计数器累加 
		}
		if(s[i]=='('&&flag[i]==0)		//与上一个过程相似 
		{
			for(int j=i;j<n;j++)
			{
				if(s[j]==')'&&flag[j]==0)
				{
					flag[j]=1;flag[i]=1;	f=0;	break;
				}
			}
			ans2+=f;
		}	
	}
	for(i=1;i<=ans1;i++)	cout<<"(";		//先输出多的前括号 
	cout<<s;								//输出本题 
	for(i=1;i<=ans2;i++)	cout<<")";		//最后输出多的后括号 
	cout<<endl;								//换行 
}

```


---

## 作者：智子·起源 (赞：0)

### 不那么多说，就是模拟。

结合程序讲思路：
```cpp
#include<iostream>
#include<string>
using namespace std;
int n,f[100],p,a,b;
string s;
int main()
{
  cin>>n>>s;
  for(int i=0;i<n;i++)
  {
    p=0;
	if(s[i]==')')//如果当前括号是')'
	{
	  for(int j=i-1;j>=0;j--)//那就往前找到一个和它匹配的'('
        if(s[j]=='('&&f[j]<1){f[j]=p=1;break;}//如果找到了，且当前括号没有和其他括号配对过，那就标记已经配对，退出。
      if(p<1)a++;//如果没有找到，那就加多一个输出前面的'('。
	}
    //当前括号是'('情况的也差不多，只不过是向后找。
    else
    {
      for(int j=i+1;j<n;j++)
        if(s[j]==')'&&f[j]<1){f[j]=p=1;break;}
      if(p<1)b++;
    }
  }
  for(int i=0;i<a;i++)cout<<'(';输出要加上的'('
  for(int i=0;i<n;i++)cout<<s[i];//输出原字符串
  for(int i=0;i<b;i++)cout<<')';//输出要加上的')'
  cout<<endl;//岛国题要换行！！
  return 0;
}
```


原代码：
```cpp
#include<iostream>
#include<string>
using namespace std;
int n,f[100],p,a,b;
string s;
int main()
{
  cin>>n>>s;
  for(int i=0;i<n;i++)
  {
    p=0;
	if(s[i]==')')
	{
	  for(int j=i-1;j>=0;j--)
        if(s[j]=='('&&f[j]<1){f[j]=p=1;break;}
      if(p<1)a++;
	}
    else
    {
      for(int j=i+1;j<n;j++)
        if(s[j]==')'&&f[j]<1){f[j]=p=1;break;}
      if(p<1)b++;
    }
  }
  for(int i=0;i<a;i++)cout<<'(';
  for(int i=0;i<n;i++)cout<<s[i];
  for(int i=0;i<b;i++)cout<<')';
  cout<<endl;
  return 0;
}
```


---

