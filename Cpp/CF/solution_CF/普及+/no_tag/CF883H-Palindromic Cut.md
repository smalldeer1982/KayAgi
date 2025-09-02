# Palindromic Cut

## 题目描述

Kolya有一个长度为 $n$ 的字符串 $s$ ，其中含有大小写英文字母和数字。

他想要重新编排 $s$ 中字符的顺序并将它切割为最少个子串，使得每个子串都为回文串且所有子串长度相等。回文串指的是从前往后读和从后往前读相同 的字符串，例如`madam`或`racecar`。

你的任务是帮助Kolya计算出所需切割出 $s$ 子串总数的最小值。

## 样例 #1

### 输入

```
6
aabaac
```

### 输出

```
2
aba aca ```

## 样例 #2

### 输入

```
8
0rTrT022
```

### 输出

```
1
02TrrT20 ```

## 样例 #3

### 输入

```
2
aA
```

### 输出

```
2
a A 
```

# 题解

## 作者：流绪 (赞：0)

先遍历字符串,记录每一个元素出现的次数,奇数的先提一个出来,然后就将字符串分成了两个部分,前半部分是单独的元素,后半部分是成对的元素

要让分割出来的子串数量最少,那么我们从小到大枚举子串的数量,如果能成立就退出枚举,然后构造回文串

实现的细节注释在代码里了

下面是 AC 代码
```cpp
#include<bits/stdc++.h>
#define maxn 1000010
using namespace std;
char s[maxn];
char a[maxn],b[maxn];
int v[200]={0};
int main()
{
	int n;
	cin >> n >> s;
	for(int i=0;i<n;i++)
		v[s[i]] ++;
	int l=1,r=n;
	for(int i=1;i<128;i++)
		if(v[i]&1)
			a[l++] = i,v[i]--;//取一个奇数的出来 
	for(int i=1;i<128;i++)
		if(v[i])
		{
			while(v[i]--)
				a[r--] = i;
		}//单个的放一起,成对的放一起 
	l--;
	int ans,len;
	for(ans=1;ans<=n;ans++)
	{
		if(n%ans)
			continue;
		len = n/ans;//每组的长度 
		if((n-l)/2 >= ans*(len/2))
			break;//总的有几对数 >= 每组中成对的数量*组数 
	}				//能够分了,退出 
	cout << ans<<endl;
	l=1,r=n;
	for(int i=1;i<=ans;i++)
	{			
		int ll=len/2,rr=len/2+1;//找到中间的位置
		if(len&1)
			b[rr++] = a[l++];//是奇数,把最中间换成一个单独的字母
		for(int j=1;j<=len/2;j++)
		{
			b[ll--] = a[r--];
			b[rr++] = a[r--];
		}//向两边增长
		for(int j=1;j<=len;j++)
			cout << b[j] ;
		cout << " ";
	}
} 
```


---

