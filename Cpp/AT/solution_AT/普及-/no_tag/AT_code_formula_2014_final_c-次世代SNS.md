# 次世代SNS

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-formula-2014-final/tasks/code_formula_2014_final_c

あなたは、とあるSNSを作ろうとしています。

このSNSでは、`@username`という形式で、特定のユーザーにメッセージを送ることが可能であり、$ 1 $ つの発言に複数のユーザーを指定することで、複数のユーザーに同時にメッセージを送ることが可能になります。

このSNSは、以下のようなルールに従っています。

- 書き込まれるメッセージは、半角小文字アルファベット、半角スペース、`@`のみを含む。
- 書き込まれたメッセージに`@`が含まれていた場合、`@`直後の、アルファベットのみで構成される文字列のうち、最も長い文字列をユーザー名として扱い、そのユーザーにメッセージを届ける。
- `@`の直後がアルファベットでなかった場合は無視する。
- 複数回同じユーザーが指定されても、メッセージは $ 1 $ 回届ければ良い。

あなたは、このシステムを実装するために、書き込まれたメッセージに対し、メッセージを届けるべきユーザーを列挙するプログラムを作りたいです。

メッセージを送るべきユーザーを全て出力しなさい。なお、ユーザーが複数いる場合は、辞書順で出力しなさい。

## 说明/提示

### Sample Explanation 1

`codeformula`さんへのメッセージです。半角スペースが挟まれているので、`why`以降をユーザー名として認識することはありません。 また、`@`を出力する必要はありません。

### Sample Explanation 2

`a`が何度も指定されていますが、一度だけ出力する必要があります。 また、ユーザ名は辞書順で出力する必要があります。

### Sample Explanation 3

メッセージを送るべきユーザーがいない場合、何も出力しないで構いません。

## 样例 #1

### 输入

```
@codeformula why is this contest so easy```

### 输出

```
codeformula```

## 样例 #2

### 输入

```
myon @@c @a @aba@a @@bb bbb @@@@@ @a test  @ space  aaa test @a@a  test@takoyaki```

### 输出

```
a
aba
bb
c
takoyaki```

## 样例 #3

### 输入

```
no atmark```

### 输出

```
```

# 题解

## 作者：Wy_x (赞：1)

题外话：这道题原来的题号是 $\texttt{AT999}$。

[题目传送门](https://www.luogu.com.cn/problem/AT_code_formula_2014_final_c)

[更好的阅读体验？](https://www.luogu.com.cn/blog/73-54-16/solution-AT-999)

### 题意：

给一行一个字符串，其中只包含小写字母，空格和 `@`，`@` 之后接字母的情况才合法，求被 `@` 的人的名字。

- **注意：空串不算名字！**

### 思路：

- $1 \leq$ 字符串的长度 $\leq 140$，直接暴力。

- 可以读一个词块就判断一个词块，`cin` 以空格为界，省去处理空格的麻烦。

- `S.find(ss)` 是寻找字符串 $ss$ 在 $S$ 中**作为子串**出现时第一个字母的位置（从 $0$ 开始），若没有返回 $-1$。

- `S.substr(pos,n)` 返回的字符串是从 $pos$ 起的前 $n$ 个字符，注意不要越界。

- `cin` 读入失败返回 $0$，`scanf` 读入失败返回 $-1$。

- sort 内部排字符串的方法：

>1. 先比较首字符的大小（按照 $\texttt{ASCII}$ 码的大小）。
>2. 如果首字母不相等，可以直接按照给定标准排序（就是自己写的函数，默认由小到大）。
>3. 若相等，则按照 $2$ 的方法继续判断下一个字符，直到有一个字符串的所有字符都判断完了，此时长度短的小于长度长的，按照给定标准排序。

- AT 的题最后要换行！

- 注意细节。

### 代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
string s,ans[101];//ans存被 @ 的人的名字
int tot;//存答案数量
int main()
{
	while(cin>>s)//一直读一个单词，可以避免很多麻烦
	{
		int nw1=s.find('@'),flag=0;
		//nw1 是找 '@' 字符的位置
		//flag 标记是否搜到最后
		while(nw1!=-1)//有 '@'
		{
			int nw2=s.find('@',nw1+1);
			//从 nw1 的下一个字符开始，寻找 '@'
			if(nw2==-1)//没有 @' 了
			{
				nw2=s.size();
				//为了使下文的 substr 不用特判
				//在全文的末尾再加一个 '@'
				//这时 '@' 的位置就是 s.size()
				flag=1;//标记已经搜到了最后
			}
			
			string wait=s.substr(nw1+1,nw2-(nw1+1));
			tot++;
			ans[tot]=wait;
			//wait 等待判断是否有重复的人名
			//先假设没有重复，后面再判断
			
			if(wait.size()==0)
			{
				//不合法情况之一：
				//是空串
				tot--;
				//不合法，数量减 1
			}
			
			for(int i=1;i<=tot-1;i++)       
			{
				if(ans[i]==wait)
				{
					//不合法情况之二：
					//有重复
					tot--;
					//不合法，数量减 1
					break;
					//不用继续判断了，跳出循环
				}
			}
			if(flag)  break;//搜到末尾了，打破循环
			nw1=nw2;
			//下一次开始判断的位置
			//就是这次判断结束的位置
		}
	}
	
	sort(ans+1,ans+tot+1);
	//sort 默认就是按字典序由小到大排序
	
	for(int i=1;i<=tot;i++)
	{
		if(ans[i].size()!=0)
		{
			//如果这个字符串不是空的，就输出
			cout<<ans[i]<<endl;
			//一行一个名字，AT 的题最后需要换行
		}
	}
	
	return 0;
}      
```

最快 [$5ms$](https://www.luogu.com.cn/record/91050685)

---

## 作者：CZQ_King (赞：0)

**做法：模拟即可。**

**$Tips:$最后的排序$+$去重可以扔进$set$里面。**

------------
代码：
```
#include<bits/stdc++.h>
using namespace std;
set<string>a;//集合来一个
string s,v;
int main(){
    getline(cin,s);//要整行读入！
    for(int i=0;i<s.length();i++){
        if(s[i]=='@'&&isalpha(s[i+1])&&i!=s.length()-1){//如果这是一个用户名（后面要是字母）
            i++;//从@后面开始读入
            while(i<s.length()&&isalpha(s[i]))v+=s[i++];//直到不是字母
            a.insert(v);//扔进集合
            v.clear();//记得清空！
            i--;//这个字符可能也是@，所以要减一
        }
    }
    for(set<string>::iterator it=a.begin();it!=a.end();++it)cout<<*it<<endl;//输出整个集合
}
```

---

