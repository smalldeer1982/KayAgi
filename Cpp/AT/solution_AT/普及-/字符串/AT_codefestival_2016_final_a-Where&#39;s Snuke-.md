# Where&#39;s Snuke?

## 题目描述

[problemUrl]: https://atcoder.jp/contests/cf16-final/tasks/codefestival_2016_final_a

縦 $ H $ 行、横 $ W $ 列のマス目があります。

上から $ i $ 行目、左から $ j $ 列目には長さ $ 5 $ の文字列 $ S_{i,j} $ が書かれています。

行には上から順に $ 1 $~$ H $ の番号が、列には左から順に `A`~`Z` の番号がついています。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_codefestival_2016_final_a/d3b854eace34ecfd0d0564d0ea4b3c7c5a522480.png)

この中から `snuke` という文字列を探し、列と行の番号を順に続けて出力してください。

例えば $ 6 $ 行目の $ 8 $ 列目にあった場合は、`H6` のように出力してください。

## 说明/提示

### 制約

- $ 1≦H,\ W≦26 $
- $ S_{i,j} $ は小文字アルファベット（`a`-`z`）のみからなる長さ $ 5 $ の文字列である。
- 与えられる文字列のうち、ちょうど $ 1 $ つだけが `snuke` である。

## 样例 #1

### 输入

```
15 10
snake snake snake snake snake snake snake snake snake snake
snake snake snake snake snake snake snake snake snake snake
snake snake snake snake snake snake snake snake snake snake
snake snake snake snake snake snake snake snake snake snake
snake snake snake snake snake snake snake snake snake snake
snake snake snake snake snake snake snake snuke snake snake
snake snake snake snake snake snake snake snake snake snake
snake snake snake snake snake snake snake snake snake snake
snake snake snake snake snake snake snake snake snake snake
snake snake snake snake snake snake snake snake snake snake
snake snake snake snake snake snake snake snake snake snake
snake snake snake snake snake snake snake snake snake snake
snake snake snake snake snake snake snake snake snake snake
snake snake snake snake snake snake snake snake snake snake
snake snake snake snake snake snake snake snake snake snake```

### 输出

```
H6```

## 样例 #2

### 输入

```
1 1
snuke```

### 输出

```
A1```

# 题解

## 作者：LiveZoom (赞：0)

# 题解 AT2128 【Where's Snuke?】
此题就是一道字符串+循环的考查，没什么好讲，上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	int n,m;
	cin>>n>>m;//输入n,m
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){//循环
			cin>>s;
			if(s=="snuke"){//判断
				cout<<char(j-1+'A');//输出列
				cout<<i;//输出行
				cout<<endl;//AT的题目不要忘了输出换行（但这题好像没关系）
				return 0;
			}
		}
	}
	return 0;
}
```


---

## 作者：⚡zhangjingcan⚡ (赞：0)

这道题主要考察字符串的运用。

[题目传送门](https://www.luogu.com.cn/problem/AT2128)

我们只要循环读入。

找到“snuke”之后输出就可以。

```c
/*
	Name: None
	Copyright: zhangjingcan所有，未经允许不得转载
	Author: zhangjingcan
	Date:
	Description: C++文件
*/
#include <bits/stdc++.h>
using namespace std;
int n,m;//定义两个变量，n是行，m是列。
string s;//定义一个字符串
int main(int argc, char** argv) {
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++){//循环读入
		for(int j=1;j<=m;j++){
			cin>>s;
			if(s=="snuke"){//找到了
				cout<<char(j+'A'-1)<<i<<"\n";//列要输出字母，所以要强制类型转换（记住，一定要加1）
             //这里还考察ASCII码的运用，1的ASCII码就是1，加上‘A’后就变成了‘B’，所以要减1
			}
		}
	}
	return 0;//完美结束
}

```


---

## 作者：Egg_eating_master (赞：0)

其他的题解感觉对新人很不友好啊。。。

我来一个最无脑做法吧，适合新手~
```
#include<bits/std++.h>
using namespace std;
string s[101][101];//存整个字符串矩阵
int n,m;
int main(){
	cin>>n>>m;//输入行和烈
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=m;j++){//双重循环输入矩阵
	    	cin>>s[i][j];//输入该位置上的字符串
	    	if(s[i][j]=="snuke"){//发现了！！！
	    		cout<<(char)(j+'A'-1);//输出列，这是数字转大写字母的模板，最好背下来
	    		cout<<i;//输出行
	    		cout<<endl;//AT不换行，爆零两行泪
	    		return 0;//一旦发现snuke就不用继续了，直接结束程序
			}
		}
	return 0;//Happy Ending~
}
```
本题解已做防抄袭处理，请勿抄袭~

---

## 作者：ShineEternal (赞：0)

没人？我来一篇。

------------
# 此题注意考虑的应该是字符串的输入和判断。
```
#include<cstdio>
using namespace std；
char s[3412]；
int main()
{
	int n，m；
	scanf("%d%d",&n,&m)；
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%s",s)；//一个字符串
			if(s[0]=='s'&&s[1]=='n'&&s[2]=='u'&&s[3]=='k'&&s[4]=='e')//其实可以用cmp比较，但是只有五个字符，蒟蒻就一个一个比了。。。
			{
				printf("%c%d\n",'A'+j-1,i);//把列数转化为大写字母，行数直接打印
				
			}
		}
	}
	return 0；
} //友情提示：内有防抄袭bug
```

求过，求路赞

---

