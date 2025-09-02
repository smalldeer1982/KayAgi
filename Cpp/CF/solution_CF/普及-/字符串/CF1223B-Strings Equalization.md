# Strings Equalization

## 题目描述

You are given two strings of equal length $ s $ and $ t $ consisting of lowercase Latin letters. You may perform any number (possibly, zero) operations on these strings.

During each operation you choose two adjacent characters in any string and assign the value of the first character to the value of the second or vice versa.

For example, if $ s $ is "acbc" you can get the following strings in one operation:

- "aabc" (if you perform $ s_2 = s_1 $ );
- "ccbc" (if you perform $ s_1 = s_2 $ );
- "accc" (if you perform $ s_3 = s_2 $ or $ s_3 = s_4 $ );
- "abbc" (if you perform $ s_2 = s_3 $ );
- "acbb" (if you perform $ s_4 = s_3 $ );

Note that you can also apply this operation to the string $ t $ .

Please determine whether it is possible to transform $ s $ into $ t $ , applying the operation above any number of times.

Note that you have to answer $ q $ independent queries.

## 说明/提示

In the first query, you can perform two operations $ s_1 = s_2 $ (after it $ s $ turns into "aabb") and $ t_4 = t_3 $ (after it $ t $ turns into "aabb").

In the second query, the strings are equal initially, so the answer is "YES".

In the third query, you can not make strings $ s $ and $ t $ equal. Therefore, the answer is "NO".

## 样例 #1

### 输入

```
3
xabb
aabx
technocup
technocup
a
z
```

### 输出

```
YES
YES
NO
```

# 题解

## 作者：jiangXxin (赞：5)

先看题目：

**题目简述：**

现在给你两个由小写字母组成的字符串s和t，你可以选择字符串任意一个位置，然后用它相邻的字母来替换它，比如：acbc

你可以把它换成：

aabc($s_2$替换$s_1$)

ccbc($s_1$替换$s_2$)

accc($s_3$替换$s_2$或者$s_3$替换$s_4$)

abbc($s_2$替换$s_3$)

acbb($s_4$替换$s_3$)

现在你需要回答能不能使用以上操作使s和t相等，能输出："YES",不能输出"NO"


------------------------------------------------------------
既然是相邻的就可以替换,那么我们就可以看这两个字符串有没有**相同的字符**，如果有，那么我们一定可以通过一直替换，得到两个相同的.

（举个栗子）：

**akioi**

**luogu**

**这两个字符串都有o**，那么我们就可以通过替换使$"akioi"$变成$"ooooo"$，使$"luogu"$变成$"ooooo"$，那么代码也就很明显了:


```cpp
/**
*    author:  a2954898606
*    created: 2019/10/08 19:30:22
**/
#include<bits/stdc++.h>
#define REP(A,B,I) for(int I=(A);I<=(B);I++)
#define PER(A,B,I) for(int I=(A);I>=(B);I--)
#define max(X,Y) ((X)<(Y)?(Y):(X))
#define min(Y,X) ((X)<(Y)?(X):(Y))
#define read(FILENAME) freopen((FILENAME + ".txt"), "r", stdin);
#define write(FILENAME) freopen((FILENAME + ".txt"), "w", stdout);
#define LL long long
#define mod 100000007
using namespace std;
long long quickpow(long long a,long long b){long long ret=1;while(b){if(b&1){ret=ret*a%mod;}}a=a*a%mod;b>>=1;return ret;}
string s,t;
int vis[520],tt;
int main(){
    //read(1)
    //write(1)
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin>>tt;
    REP(1,tt,ttt){
        cin>>s>>t;
        memset(vis,0,sizeof(vis));
        if(s.length()!=t.length()){
            cout<<"NO"<<endl;
            continue;
        }
        REP(0,s.length()-1,i){
            vis[s[i]-'a'+1]=true;
        }
        bool flag=false;
        REP(0,t.length()-1,i){
            if(vis[t[i]-'a'+1])flag=true;
        }
        if(flag)cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}

```



---

## 作者：sanjingshou14 (赞：3)

# 更新日志
upd on 2022.8.19：规范 $\LaTeX$ 公式的使用。

upd on 2022.8.21：删除不规范内容，更改细节。

# 前言
一开始看到这道题的时候，我被它震惊了。

修改没有次数限制！没有修改代价！还不用输出修改结果！~~太良心了！~~

言归正传，接下来讲讲这道题的方法。

# 前置知识
[c++ 字符串 find 函数的用法](https://wenku.baidu.com/view/d01c232f753231126edb6f1aff00bed5b9f373a8.html)

# 题目大意

[题目传送门](https://www.luogu.com.cn/problem/CF1223B)

见题意翻译部分。

# 简化题意

题目中告诉我们可以在任意一个字符串中将第 $i$ 位字符变为第 $j$ 位上的字符，并且没有限定修改次数。

那就是说，只要两个字符串中有一个字符相同，就可以通过多次修改变为相同的字符串。

所以，我们只需要用十分简单的字符串判断就可以解决这道题了。

# 解法
#### 方法一：find 函数查找
用 find 函数在第一个字符串中查找第二个字符串的每个字符，一旦找到一个字符是相同的，就跳出循环。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int q;
	cin>>q;
	for(int i=1;i<=q;i++){
		string s1,s2;
		cin>>s1;
		cin>>s2;
		if(s1.size()!=s2.size()){
			cout<<"NO"<<endl;
			continue;//这里注意，如果不特判两个字符串长度不同的情况就会WA，千万不要忘记！！！
		}
		bool f=false;
		for(int j=0;j<s2.size();j++){
			if(s1.find(s2[i])!=s1.npos){
				f=true;
				break;
			}
		}
		if(f) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```

#### 方法二：暴力查找

写一个双重循环，用第一个字符串中的每个字符去判断第二个字符串中的每个字符，找到相同就退出。因为数据范围小，最多循环 $10000$ 次，不会超时。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int q;
	cin>>q;
	for(int i=1;i<=q;i++){
		string s1,s2;
		cin>>s1;
		cin>>s2;
		if(s1.size()!=s2.size()){
			cout<<"NO"<<endl;
			continue;//同上，一定要特判！！
		}
		bool f=false;
		for(int j=0;j<s1.size();j++){
			for(int k=0;k<s2.size();k++){
				if(s1[j]==s2[k]){
					f=true;
					break;
				}
			}
		}
		if(f) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```

#### 方法三：桶

这个方法在楼下已经有过了，这里不再讲。

再说一次，一定要特判！

# 总结
这题总的来说是很简单的，就是容易想复杂。坑点只有一个~~但是一出场就是王炸~~。

千万记住，一定要特判！

---

## 作者：幽界の冥神 (赞：1)

本题用桶模拟即可。

因为无论如何，只要$|S|$中有$|T|$中的所有字母中的任何一个，就可以全部换为该字母，因此一定有解，反之一定无解。

代码就很简单了——

代码 : 

```cpp

#include <cstdio>
#include <cstring>
#include <iostream>

#define N 30

using namespace std;

int t, n;
bool f[N];
string a, b;

inline void calc () {
	for (int i = 0; i < n; ++i)
			if (f[b[i]]) {
				puts ("YES");
				return ;
			}
	puts ("NO");
}

int main () {
	scanf ("%d", &t);
	while (t --) {
		cin >> a >> b;
		n = a.size ();
      		memset (f, 0, sizeof (f));
		for (int i = 0; i < n; ++i) {
			a[i] -= 'a';
			b[i] -= 'a';
		}
		for (int i = 0; i < n; ++i) f[a[i]] = 1;
		calc ();
	}
	return 0;
}

```

---

## 作者：BlanketRice (赞：0)

### 前言
非常水的一道题，但是题意容易理解错。

### 题目描述
给定两个长度相等的字符串 $ S $ 和 $ T $，问能否在进行如下操作无限次后，使 $ S=T $。

操作：将两个相邻的字符的其中一个变为另一个。

### 思路
如果两个字符串中存在一个相同的字符，那就把两个字符串都变成这个字符，否则，就永远无法完成。

### 具体实现
用一个 `map` 写桶，设 $ S $ 和 $ T $，`S[c]` 表示在 $ S $ 里，字符 $ c $ 的出现次数，如果都不为 `0`，就输出 `YES`，否则输出 `NO`。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
map < char, int > S, T;
int tt;
signed main () {
    cin >> tt;
    while (tt --) {
        S.clear (), T.clear ();
        string x, y;
        cin >> x >> y;
        int lx = x.length (), ly = y.length ();
        for (register int i = 0; i < lx; ++ i) ++ S[x[i]];
        for (register int i = 0; i < ly; ++ i) ++ T[y[i]];
        bool ed = 0;
        for (register int i = 'a'; i <= 'z'; ++ i) {
            if (S[i] && T[i]) {
                ed = 1;
                break;
            }
        }
        if (ed) puts ("YES");
        else puts ("NO");
    }
    return 0;
}
```

---

## 作者：OoXiao_QioO (赞：0)

# 前言
怎么说呢，这道题其实还挺有趣的，一道代码十分简短的题，却会让一些人越想越复杂，什么排序啊，前缀和啊，等等。最后反而做不出来这道题，下面就给大家分享一下本蒟蒻的一些想法。

# 题目描述

有两个字符串 $S$，$T$，你可以在任意一个字符串内做以下操作：将第 $i$ 位字符变为第 $j$ 位上的字符。

问最终能不能使 $S=T$。

# 思路

首先看到这道题，我第一反应是，这么水的一道题真的是橙题吗？我直接排序一波，再来判断 $S$ 和 $T$ 的元素是否一一相符，输出一下不就完了？打了十多分钟的代码后，发现样例都过不了，因为我们没有考虑元素的重复性，所以去重一下不就好了？去重的办法是用桶，统计一下每个字符是否出现过，然后判断一下桶内的元素是否在两个字符串中都出现过，输出一下答案。自信提交上去，结果错在了下面的数据上：

输入
```
1
aa
ab
```
输出
```
YES
```
错误的原因是在于，装 $S$ 数组元素个数的桶 $a$ 内存入了 $a$ 这个字符，而装 $T$ 数组元素个数的桶 $b$ 内存入了 $a$，$b$ 字符，显然程序会输出 $\verb!NO!$。但我们只需要把 $T$ 数组内的 $b$ 换成 $a$ 不就完了吗？再想想，此时两个字符数组只剩下了一种元素 $a$！这说明了什么？只需要一个字符就可以判断一下是否能满足条件，那我们不就找一个字符，两个字符数组内都出现了这个字符不就可以输出 $\verb!YES!$ 吗？事实证明我们的思路是正确的，那么下面就给大家奉上代码。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	//定义
	 
	char s[101],t[101];
	int q,i,l,j,a[256]={0},b[256]={0};//用桶来判断是否存在两个字符串中都出现的字符。 
	int f;//f 表示是否满足条件。 
	
	//输入
	 
	cin>>q;
	
	//处理 
	while(q--)
	{
		//切记两个桶初始要清空！！ 
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		
		f = 0;//假设初始两个字符串不相同（事实也如此）。 
		scanf("%s %s",s,t);
		l = strlen(s);
		
		//统计元素是否出现过，下面的代码都是桶的基础部分，这里不再讲解。 
		for(i=0;i<l;i++)
			a[s[i]]++;
		for(i=0;i<l;i++)
			b[t[i]]++;
			
		//开始查找有没有满足条件的字符。 
		for(i='a';i<='z';i++)//从字符 a 查找到字符 z。 
			if(a[i]&&b[i])//找到这个字符了，条件是这个元素在两个桶中都出现过 。 
			{
				f = 1;//找到了，直接 break掉。 
				break;
			}
		//根据 f 的值来输出。 
		if(f)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
```


---

## 作者：Ofnoname (赞：0)

显然，由于同一个字符串里可以随意将一个字符赋值给另一个字符，所以只要两个字符串有至少一个公共字母就是`YES`，否则是`NO`。

```cpp
#include <bits/stdc++.h> 
#define MAXN (3000 + 7)
using namespace std;
 
int N, B[200]; //B做桶来存储字母的出现情况
 
int main()
{
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
    {
    	char s[200] = {}, t[200] = {};
		memset(B, 0, sizeof B);
		scanf("%s%s", s, t);
		for (int i = 0; s[i]; i++)
			B[s[i]] = 1;
		for (int i = 0; t[i]; i++)
			if (B[t[i]] == 1) B[t[i]] += 2;//那么B[i]为3就说明有公共字符
        for (int i = 0; i <= 150; i++)
			if (B[i] == 3)
			{
				puts("YES");
				goto END;
			}
		puts("NO");
		END: continue;
	}
}
```

---

