# Message

## 题目描述

Dr. Moriarty is about to send a message to Sherlock Holmes. He has a string $ s $ .

String $ p $ is called a substring of string $ s $ if you can read it starting from some position in the string $ s $ . For example, string "aba" has six substrings: "a", "b", "a", "ab", "ba", "aba".

Dr. Moriarty plans to take string $ s $ and cut out some substring from it, let's call it $ t $ . Then he needs to change the substring $ t $ zero or more times. As a result, he should obtain a fixed string $ u $ (which is the string that should be sent to Sherlock Holmes). One change is defined as making one of the following actions:

- Insert one letter to any end of the string.
- Delete one letter from any end of the string.
- Change one letter into any other one.

Moriarty is very smart and after he chooses some substring $ t $ , he always makes the minimal number of changes to obtain $ u $ .

Help Moriarty choose the best substring $ t $ from all substrings of the string $ s $ . The substring $ t $ should minimize the number of changes Moriarty should make to obtain the string $ u $ from it.

## 说明/提示

In the first sample Moriarty can take any substring of length $ 3 $ , and it will be equal to the required message $ u $ , so Moriarty won't have to make any changes.

In the second sample you should take a substring consisting of characters from second to fourth ("bca") or from fifth to sixth ("bc"). Then you will only have to make one change: to change or to add the last character.

In the third sample the initial string $ s $ doesn't contain any character that the message should contain, so, whatever string you choose, you will have to make at least $ 7 $ changes to obtain the required message.

## 样例 #1

### 输入

```
aaaaa
aaa
```

### 输出

```
0
```

## 样例 #2

### 输入

```
abcabc
bcd
```

### 输出

```
1
```

## 样例 #3

### 输入

```
abcdef
klmnopq
```

### 输出

```
7
```

# 题解

## 作者：yydfj (赞：8)

**这是本蒟蒻第十三次写的题解，如有错误点请好心指出！**

## 问题简述

__这道题我们可以换另一种思路去看待它，就容易理解了：__

给你两个字符串 $A$ 和 $B$，将 $B$ 字符串中的每个字符与 $A$ 字符串中的每个字符相对比，求出对于 $B$ 字符串中最少字符对比不相同的数量。

## 解法综述

我们可以用 dp 的思想来解决。

设 $dp[i][j]$ 表示对于 $A$ 字符串前 $i$ 个字符与 $B$ 字符串前 $j$ 个字符中有多少个字符对比相同，则状态转移方程为 $dp[i][j]=dp[i-1][j-1]+(A[i]==B[j])$。

最后取 $dp[i][j]$ 的最大值，即最多字符对比相同的数量。因为是对于 $B$ 字符串，所有只需将 $B$ 字符串的字符总数减去最多字符对比相同的数量，即可得出对于 $B$ 字符串中最少字符对比不相同的数量。

## 代码描述
```cpp
#include<cstdio>
#include<cstring>
#define max(a,b) (a>b?a:b)
char A[2005],B[2005];
int dp[2005][2005],ans;
int main()
{
	A[0]=B[0]=1;//因为状态转移方程中需要dp数组前一位的干涉，所以应将字符串输入后移一位，避免数组越界
	scanf("%s%s",&A[1],&B[1]);//字符串从数组第一位读入
	int lA=strlen(A)-1,lB=strlen(B)-1;
	for(int i=1;i<=lA;i++)
	for(int j=1;j<=lB;j++)
	{
		dp[i][j]=dp[i-1][j-1]+(A[i]==B[j]);//状态转移方程
		ans=max(ans,dp[i][j]);//用ans来存当前最多字符对比相同的数量
	}
	printf("%d",lB-ans);//得出对于B字符串中最少字符对比不相同的数量
	return 0;
}
```

---

## 作者：fuxuantong123 (赞：6)

# CF156A Message 题解
## 题意
题目翻译有误，只能两端删除插入。
## 思路
枚举 $b$ 的左端点，再暴力跑把 $b$ 变成 $a$ 的代价取最小就行了。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	string s,b;
	cin>>s>>b;
	int ans=2147483647;
	int fb=b.size();
	int fs=s.size();
	for(int i=-fb;i<fs;i++){
		int cnt=0;
		for(int j=0;j<fb;j++){
			if(i+j>=0 && i+j<fs && s[i+j]==b[j]){
				cnt++;
			}
		}
		ans=min(ans,fb-cnt);
	}
	printf("%d",ans);
return 0;
}
```


---

## 作者：mahaoming (赞：2)

# CF156A Message 题解

### 题意

见题目，题目写的很清楚。

### 思路

只要从左到右暴力枚举，然后暴力取最小值就可以了。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
char a[2005],b[2005];
int la,lb,s=0x3f3f3f3f,c;
int main(){
	cin>>a>>b;
	la=strlen(a),lb=strlen(b);
	for(int i=-lb;i<la;i++){
		for(int j=0;j<lb;j++)
			if((i+j>=0&&i+j<la)&&(a[i+j]==b[j]))c++;
		s=min(s,lb-c),c=0;
	}
	cout<<s<<endl;
	return 0;
}
```


---

## 作者：Real_Create (赞：1)

题目翻译有误（

添加和删除只能在两端。

------------
所以这个题就变得很简单力！

只要从左到右暴力枚举，然后暴力求就可以了。

样例 3 非常良心，告诉了我们可能 $B$ 的长度会大于 $A$。

然后应该没有容易错的地方了。

```
#include<bits/stdc++.h>
using namespace std;

int main()
{
	string a,b;
	int mini=INT_MAX;
	cin>>a>>b;
	int az=a.size();//没有这步就会不循环（
	for(int i=-b.size();i<=az;i++)
	{
		int ans=b.size();
		for(int j=0;j<b.size();j++)
		{
			ans-=(i+j>=0&&i+j<a.size()&&a[i+j]==b[j]);
		}
		mini=min(mini,ans);
	}
	cout<<mini;
	return 0;
}


```


---

## 作者：iiawaKL (赞：0)

###### 蒟蒻又写题解啦

今天我们来讲一道题，叫做Message，我自认为不是太难。

思路：简单的模拟。

我们可以枚举b开始的左端点，再从左往右循环，看看需要变成a的字串最小需要多少。

Code->

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s,u;
	cin>>s>>u;
	int t=s.size(),p=u.size();
	int ans=1e9;
	for(int i=-2000;i<t;i++){
		int cnt=0;
		for(int j=0;j<p;j++){
			if(i+j>=0&&i+j<s.size()){
				if(s[i+j]==u[j])cnt++;
			}
		}
		ans=min(ans,p-cnt);
	}
	cout<<ans<<endl;
	return 0;
}
```


---

