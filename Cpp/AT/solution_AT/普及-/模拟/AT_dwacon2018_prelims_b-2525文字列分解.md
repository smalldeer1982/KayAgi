# 2525文字列分解

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dwacon2018-prelims/tasks/dwacon2018_prelims_b

dwango社員のニワンゴくんは2525SNSという新しいSNSを開発しています。 2525SNSは2525文字列のみ投稿可能な画期的なSNSです。

この問題において、`25` の $ 1 $ 回以上の繰り返しで表される文字列を2525文字列と呼びます。 例えば、`25`,`2525`,`2525252525252525` などは2525文字列ですが、空文字列や `2255`,`2552`,`252` などは2525文字列ではありません。

まず、ニワンゴくんは2525文字列をいくつか作ることにしました。 ニワンゴくんは手元にあった文字列 $ s $ を $ 1 $ つ以上の部分列に分解し、分解された部分列それぞれが2525文字列となるようにしたいです。

最小でいくつの部分列に分解すればこれを達成可能ですか？どのように分解しても達成不可能な場合は `-1` を出力してください。分解についてはサンプル $ 1 $ の説明も参照してください。

## 说明/提示

### 制約

- $ 1\ \leq\ |s|\ \leq\ 2{,}525 $
- $ s $ は `2` と `5` のみからなる

### Sample Explanation 1

\- $ 1 $ つの部分列に分解した場合、`225525` は2525文字列ではないため条件を満たしません。 - その他の分解としては例えば $ ( $`25`,`2525`$ ) $ となるような分解と $ ( $`25`,`25`,`25`$ ) $ となるような分解が考えられます。それぞれについて正しい分解の例とそうでない例を示します。各部分列内において、$ s $ における相対的な出現順序が守られるように分解する必要があることに注意してください。 - $ ( $`25`,`2525`$ ) $ となるように $ 2 $ つの部分列に分解することで、それぞれの部分列が2525文字列となるように分解できます。 !\[062c9a95edb82917811ef52962f98a3e.png\](https://img.atcoder.jp/dwacon2018-prelims/062c9a95edb82917811ef52962f98a3e.png)

### Sample Explanation 2

\- 分解方法は $ 2 $ 通りありますが、それぞれの部分列が2525文字列となるように分解することはできません。 - `5` と `2` に分解したのち、それぞれの順序を入れ替えて `25` を作ることは不可能なことに注意してください。

## 样例 #1

### 输入

```
225525```

### 输出

```
2```

## 样例 #2

### 输入

```
52```

### 输出

```
-1```

## 样例 #3

### 输入

```
2255252252222555552522255255```

### 输出

```
5```

## 样例 #4

### 输入

```
25252```

### 输出

```
-1```

# 题解

## 作者：Carotrl (赞：0)

##### 简单的水题。

### 不难看出，答案是一个区间内2的个数与5的个数之差。

### 当然，若字符串长度不是2的倍数或区间内5的个数大于2的个数，则无解。

代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int s,n,ans;
char a[3000];
int main(){
	scanf("%s",a);
	n=strlen(a);
	if(n&1){ //判断无解
		printf("-1");
		return 0;
	}
	for(int i=0;i<n;i++){
		s+=(a[i]=='2');
		s-=(a[i]=='5');
		if(s<0){ //判断无解
			printf("-1");
			return 0;
		}
		ans=max(s,ans);//区间最大值
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：大头leo (赞：0)

找规律，我们可以发现答案就是某一阶段 _‘2’_ 与 _‘5’_ 的差的最大值，那么照着这个思路模拟即可。

需要注意的是，本题的字符串s似乎只含有2与5，否则此方法会失分。

我们需要先判断字符串s的长度是否是2的倍数，是则继续模拟，否则肯定是无解的。我们输出-1结束程序即可。

本人亲测本方法如果不加入上述判断会错。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int t,f,t2,t5;
int main()
{
	cin>>s;
	if(s.size()%2==1)
	{
		cout<<"-1"<<endl;
		return 0;
	}
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='2')	t++;
		if(s[i]=='5')	t--;
		if(t<0)
		{
			cout<<"-1"<<endl;
			return 0;
		}
		t2=max(t,t2);
	}
	cout<<t2<<endl;
}

```


---

## 作者：_Ayanami_ (赞：0)

方法一：O（n*ans）(n为字符串长度)
（思路简单，纯模拟）
1. 从前往后扫

2. 找出每一对可选的最前面的2和5并消去

3. 如果到扫到队尾
   - 如果一对都没找到就输出-1并退出，否则ans++

   - 如果全部匹配完输出ans并退出，否则回到步骤一

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int l,n=0,i,j,ans;//n记录已匹配的2、5数
bool flag;
string s;
int main()
{
	cin>>s;
	l=s.length();
	if(l%2==1)//长度为奇数肯定不行
	{
		printf("-1\n");
		return 0;
	}
	while(n<l)未全部匹配
	{
		i=0;
		flag=1;
		while(i<l)//扫一遍
		{
			while(s[i]!='2')
			{
				i++;
				if(i==l)
				{
					goto Next;
				}
			}
			j=i;
			while(s[i]!='5')
			{
				i++;
				if(i==l)
				{
					goto Next;
				}
			}
			s[i]=s[j]='0';//删去一对
			flag=0;
			n+=2;
		}
		Next:;
		if(flag)//没有找到
		{
			printf("-1\n");
			return 0;
		}
		ans++;
	}
	printf("%d\n",ans);
	return 0;
}
```
方法二:O（n）
（码量极小，线性复杂度）

一个叫相对差的东西

即从开头到某个位置的2的数量与5的数量之差

然后我们可以发现答案就是相对差的最大值

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int l,n=0,ans=0;//n存相对差
string s;
int main()
{
	cin>>s;
	l=s.length();
	if(l%2==1)
	{
		printf("-1\n");
		return 0;
	}
	for(register int i=0;i<l;++i)
	{
		if(s[i]=='2')n++;
		if(s[i]=='5')n--;
		if(n<0)//这个位置前5的数量大于2的数量，无解
		{
			printf("-1\n");
			return 0;
		}
		ans=max(n,ans);
	}
	printf("%d\n",ans);
}
```


---

