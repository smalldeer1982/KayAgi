# Polycarp and Letters

## 题目描述

Polycarp loves lowercase letters and dislikes uppercase ones. Once he got a string $ s $ consisting only of lowercase and uppercase Latin letters.

Let $ A $ be a set of positions in the string. Let's call it pretty if following conditions are met:

- letters on positions from $ A $ in the string are all distinct and lowercase;
- there are no uppercase letters in the string which are situated between positions from $ A $ (i.e. there is no such $ j $ that $ s[j] $ is an uppercase letter, and $ a_{1}<j<a_{2} $ for some $ a_{1} $ and $ a_{2} $ from $ A $ ).

Write a program that will determine the maximum number of elements in a pretty set of positions.

## 说明/提示

In the first example the desired positions might be $ 6 $ and $ 8 $ or $ 7 $ and $ 8 $ . Positions $ 6 $ and $ 7 $ contain letters 'a', position $ 8 $ contains letter 'b'. The pair of positions $ 1 $ and $ 8 $ is not suitable because there is an uppercase letter 'B' between these position.

In the second example desired positions can be $ 7 $ , $ 8 $ and $ 11 $ . There are other ways to choose pretty set consisting of three elements.

In the third example the given string $ s $ does not contain any lowercase letters, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
11
aaaaBaabAbA
```

### 输出

```
2
```

## 样例 #2

### 输入

```
12
zACaAbbaazzC
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3
ABC
```

### 输出

```
0
```

# 题解

## 作者：Moon_Lighter (赞：1)


### 解题思路：
给出一个字符串，由一个个大写字母分隔成多个区域。求各个区域中最多的不同的字母个数的数量。

**解题方法：**

模拟求解即可。

---

### [$\color{#52C41A}\texttt{AC CODE}$](https://www.luogu.com.cn/record/51547731)
```cpp
var
  l,i,ans,k:longint;ch:char;
  a:array['a'..'z'] of longint;
begin
  readln(l);
  for i:=1 to l do。
  begin
    read(ch);
    if (ch>='a')and(ch<='z') then
    begin
      inc(a[ch]);
      if a[ch]=1 then inc(k);
    end else
    begin
      if k>ans then ans:=k;
      k:=0;
      fillchar(a,sizeof(a),0);
    end;
  end;
  if k>ans then ans:=k;
  writeln(ans);
end.
```

---

## 作者：_Spectator_ (赞：1)


[可能更好的食用体验](/blog/523641/CF864B) $|$ 
[题目传送门](/problem/CF864B) $|$ 
[我的其他题解](/blog/523641/#type=题解)

------------

${\large\color{#00CD00}\text{主要思路}}$

不明白其他大佬的思路为什么那么复杂……

其实这道题目可以这么理解：找到连续的一段小写字母，统计里面出现的不同的字母的数量，数量最多的即为题目所求。

具体实现方式：

1. 循环遍历字符串里的每一个字符。
2. 如果是小写字母（可以使用`islower()`函数判断）且当前字母未出现，增加出现的字母数量，同时标记该字母。
3. 如果是大写字母（可以使用`isupper()`函数判断），统计最大的数量并清空标记数组。
4. 循环完毕输出时不要忘记再取一次最大值。

（表述能力欠佳，如果还有不明白的地方就看看代码吧 QwQ。）

------------

${\large\color{#00CD00}\text{完整代码}}$

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,len,ma;
string st;　
int js[128];
int main()　
{　
	cin>>n>>st;　
	for(int i=0;i<n;i++)
	{　
		if(islower(st[i])&&js[st[i]]==0)//如果是小写字母且当前字母未出现过，增加数量
			len++,js[st[i]]=1;　
		if(isupper(st[i]))//如果是大写字母，统计最大数量并清空计数 
			ma=max(ma,len),len=0,memset(js,0,sizeof(js));
	}　
	cout<<max(ma,len);//注意最后还要取一次较大值 
	return 0;
}　
```

**[${\color{Black}\textbf{xt\_\_}}$](/user/523641) 温馨提示：**


${\large\color{White}\text\colorbox{#AD8800}{题解千万条，理解第一条。直接粘题解，棕名两行泪。}} $

---

## 作者：houyinuo (赞：0)

其实这题正解应该是尺取吧，思路挺好想的，就是找到i后面的第一个大写字母，然后把i赋为这个大写字母的下标加1再找，然后取个最大值就好了（map什么的就不讲了）
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
char s[205];
map<char,int>mp;
int main (){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf ("%d",&n);
	scanf ("%s",s+1);
	int i=1,j=1;
	while (i<=n&&j<=n){
		while (s[j]<='z'&&s[j]>='a') mp[s[j]]++,j++;
//		printf ("%d %d\n",i,j);
		j++;
		int s=0;
		for (int k=0;k<26;k++) if (mp['a'+k]>0) s++;
		ans=max(s,ans);
		mp.clear();
		i=j;
	}
	printf ("%d",ans);
    return 0;
}

```


---

## 作者：happybob (赞：0)

STL大法好哦！

本题我采用的是unordered_map+string+暴力（n <= 200，限时2s暴力挺快的，不会TLE的）

那怎么做呢？

首先，我们读入一个字符串，用我们双重循环，枚举自区间，注意每次map都要clear，每次读取map的size并和maxn（max好像定义过，再定义成变量会CE（编译失败））做比较

代码如下，706ms：

```cpp
#include <iostream>
#include <cstring>
#include <unordered_map>
using namespace std;

int n, maxn = 0;

string s;

unordered_map <char, int> mp;

int main()
{
    cin >> n >> s;
    int x = s.length() - 1;
    for(int i = 0; i <= x; i++)
    {
        mp.clear();
        for(int j = i; j <= x; j++)
        {
            if(s[j] >= 'A' && s[j] <= 'Z')
            {
                break;
            }
            mp[s[j]] = 1;
        }
        int c = mp.size();
        if(c > maxn)
        {
            maxn = c;
        }
    }
    cout << maxn << endl;
    return 0;
}
```


---

## 作者：yxy666 (赞：0)

谢谢 $ClearLoveseven$ 的翻译，不然我连题目都看不懂。。。

题意是给定一个长度为 $n$ 的字符串，求最大的位置集合，每个位置都是小写字母且各不相同，每两个位置之间没有大写字母。

思路：可以采用暴力枚举来判断。处理的时候利用 $set$ 中存储的元素的唯一性去重。~~ ~~（本蒟蒻第一次用字符类型的集合，貌似，对了？~~~~）~~

$code$ :
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[205];
int n,ans,sum;
set<char>s;
set<char>::iterator x;
int main(){
    scanf("%d",&n);getchar();scanf("%s",a+1);
    for(int i=1;i<=n;i++){
        if(a[i]>='A'&&a[i]<='Z'){
            sum=s.size();
    		s.clear();
            ans=max(sum,ans);
        }
        else s.insert(a[i]);
    }
    sum=s.size();
    ans=max(ans,sum);
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：Fatelism (赞：0)

这道题其实就是让我们在整个字符串中，找一串连续的仅有小写字母构成的小字符串，使它的字母种类最多。  
所以我们可以读入之后，从头到尾遍历一遍，记录每一串由小写字母构成的小字符串的字母种类，然后选出一个种类最多的字符串，记录他的总数。  
```cpp
#include<iostream>
using namespace std;
int main(){
    string s;
    int x,ch[26]={};//ch数组用来记录种类 
    cin>>x>>s;//x其实一点用也没有 
    int max=0;
    for(int i=0;i<s.length();i++){
    	if(s[i]>='a'&&s[i]<='z')//如果是小写字母 
    		ch[s[i]-'a']=1;//记录已经出现 
    	else{//遇到大写字母,开始统计种类 
    		int k=0;
    		for(int j=0;j<26;j++)
    			if(ch[j]==1)k++;
    		if(k>max)max=k;//如果是目前统计种类最多的,那么记录 
    		for(int j=0;j<26;j++)//清零 
    			ch[j]=0;
		}
	}
	int k=0;
    for(int j=0;j<26;j++)//如果字符串以小写字母结尾，那么就会少统计一次 
    	if(ch[j]==1)k++;
    if(k>max)max=k;
    printf("%d",max);
	return 0;
}
```


---

## 作者：Tune_ (赞：0)

这是一道暴力小题题~

由于数据不大，只有200，可以暴力循环。

思路：

1. 在字符串中找到小写字母，把它作为集合的开头。
2. 向后找小写字母，并标记这个字母出现过。
1. 碰到大写字母，集合结束，退出循环。
1. 看看集合中有多少个不同的小写字母 。
1. 更新答案
1. 遍历完整个字符串的小写字母后，输出答案，结束程序。

这个程序有二重循环，最多循环200 * 200次只有40000，所以不会超时，放心暴力

( * ^▽^ * )

最后，附上完整代码：

```
#include<bits/stdc++.h>
using namespace std;
int bj[26]={0};//bj为标记数组
char c[205];
int n,ans=0; 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)//输入
		cin>>c[i];
	for(int i=1;i<=n;i++)
	{
		memset(bj,0,sizeof(bj));
		if(c[i]>='a'&&c[i]<='z')//如果找到一个小写字母
		{
			int s=0;
			for(int j=i;j<=n;j++)//找后面的小写字母
			{
				if(c[j]>='A'&&c[j]<='Z')//如果碰到大写字母
					break;//退出循环
				bj[c[j]-'a']=1;//标记这个小写字母
			}
			for(int i=0;i<26;i++)//有多少个不同的小写字母
				if(bj[i])
					s++;
			ans=max(s,ans);//更新答案
		}
	}
	cout<<ans;//输出
	return 0;//大功告成~~~
}

```

走过路过，点个赞呗~(〃'▽'〃)

---

## 作者：PC_DOS (赞：0)

这是一道字符串模拟题，对字符串进行暴力搜索，找到所有可行的集合，并输出所有可行集合中最大的一个即可。

这里使用STL的set来表示每一个可行的集合，用vector来存放每个集合的大小。

搜索的思路是:

从头到尾检查字符串，如果发现小写字母，则向set中添加这个字母，并以这个字母的下一个字母为起点，遍历字符串，如遇到小写字母，则尝试向set中添加这个字母(由于set具有集合的惟一性，因此添加已有字母的尝试将会失败)如遇到大写字母或抵达字符串末端则终止遍历。此时所得到的set即为一个可行的集合，在vector中记录其大小并清空set。最后，输vector中最大的元素。

代码:
```
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <sstream>
#include <set>
#include <queue>
#include <stack>
#include <cctype>
#include <map>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int iLength, i, j; //iLength-字符串长度；i、j-循环计数器
	string sInput; //存放输入的字符串
	vector<int> arrSize; //保存集合大小的动态数组
	set<char> setChars; //表示一个可行的集合
	cin >> iLength >> sInput; //读入长度和字符串
	for (i = 0; i <= iLength - 1; ++i){ //从头到尾检查字符串
		if (!islower(sInput[i])) //如果不是小写字母
			continue; //跳过下面的步骤
		setChars.insert(sInput[i]); //如果发现小写字母，则向set中添加这个字母
		for (j = i + 1; j <= iLength - 1; ++j){ //以这个字母的下一个字母为起点，遍历字符串
			if (!islower(sInput[j])) //如遇到大写字母或抵达字符串末端则终止遍历
				break; //终止遍历
			setChars.insert(sInput[j]); //如遇到小写字母，则尝试向set中添加这个字母(由于set具有集合的惟一性，因此添加已有字母的尝试将会失败)
		}
		arrSize.push_back(setChars.size()); //遍历结束，在vector中记录set的大小
		setChars.clear(); //清空set
	}
	if (arrSize.size() != 0) //如果存在可行的集合
		cout << *max_element(arrSize.begin(), arrSize.end()); //输出其大小的最大值
	else //否则
		cout << 0; //输出0
	return 0; //结束
}
```


---

