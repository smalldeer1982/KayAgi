# Can you get AC?

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2017-qualc/tasks/code_festival_2017_qualc_a

すぬけ君は、あるプログラミングコンテストのためにジャッジシステムを作りました。

このジャッジシステムにプログラムを提出すると、文字列 $ S $ からある連続する $ 2 $ 文字を取り出した文字列が結果として返ってきます (どの連続する $ 2 $ 文字も結果として返ってくることがありえます)。

このジャッジシステムにプログラムを提出した結果として `AC` という文字列が返ってくることがありえるかどうか判定してください。

## 说明/提示

### 制約

- $ 2\ \leq\ |S|\ \leq\ 5 $
- $ S $ は英大文字からなる。

### Sample Explanation 1

`BACD` という文字列の $ 2 $ 文字目と $ 3 $ 文字目を取り出すと `AC` という文字列になります。

### Sample Explanation 2

`ABCD` という文字列の $ 1 $ 文字目と $ 3 $ 文字目を取り出してつなげると `AC` という文字列になりますが、これらの文字は連続した $ 2 $ 文字ではないので、 プログラムの提出結果として返ってくることはありません。

## 样例 #1

### 输入

```
BACD```

### 输出

```
Yes```

## 样例 #2

### 输入

```
ABCD```

### 输出

```
No```

## 样例 #3

### 输入

```
CABD```

### 输出

```
No```

## 样例 #4

### 输入

```
ACACA```

### 输出

```
Yes```

## 样例 #5

### 输入

```
XX```

### 输出

```
No```

# 题解

## 作者：LQHqwq (赞：6)

### 此题是一道kmp的模板题
### kmp算法主要是通过fail指针来匹配字符串
#### fail指针的含义：通过指向一个位置是两边字符串可以匹配,列如：
#### 0 1 2 3 4     //下标
#### A B A B A		// 模式串 
#### 则fail[4] = 2 因为从0~2为“ABA”,和相同长度的2~4为“ABA” 相等
## 代码如下:


------------
```cpp
#include<bits/stdc++.h>  // 万能头文件大法好~
using namespace std;
int n,len1,len2,fail[1000],bj,v,x,y;
```
#### 下面的find函数很容易理解，通过之前求出的fail指针来求当前的fail指针，打个比方，如果S1 = S2,那么S1 + 'a' = S2 + 'a'
```cpp
char S[10000],U[1000];  //S为文本串，U为模式串
int find(int i){ 
	while(U[i+1] != U[v]){
		if(i == -1) return -1;
		else i = fail[i];
	}
	return i+1;
}
```
#### 如果下一位不匹配则求出可以匹配的最长位置
```cpp
intf(int i){
	while(U[i+1] != S[y]){
		if(i == -1) return -1;
		else i = fail[i];
	}
	return i+1;
}
```
#### 主函数：
```cpp
int main(){
	scanf("%s",S);
	len1 = 2;
	len2 = strlen(S);
	U[0] = 'A';U[1] = 'C'; 
	fail[0] = -1;  // -1指向空的位置，而第一位一定是-1
	for(int i = 1; i < len1; ++i){ // 求出每一位的fail指针
		v = i;
		fail[v] = find(fail[v-1]);
	}
	x = -1;  //模式串的下标
	y = -1;  // 文本串的下标(其实可以用i代替，但这样易懂点)
	for(int i = 0; i < len2; ++i){
		y++;
		if(U[x+1] == S[y]) x++;//如果模式串下一位匹配成功那么下标移动到下一位
		else x = f(x); //否则返回到能匹配到的最长位置
		if(x == len1 - 1){//判断是否全都匹配完成
			printf("Yes");
			bj = 1; //标记匹配成功
			break;
		}
	}
	if(!bj) printf("No");
	return 0;
}
```


---

## 作者：Kiel (赞：4)

题目大意：

输入一个字符串s，如果你能在这个字符串中得到AC这个字符串，就输出Yes否则输出No。

注意：字符串长度最大为5。

并且所有的字母都是大写的。

直接暴力判断就可以了。

如果第一个是‘A’那么直接判断下一个是不是‘C’，即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){   
    string s;
    cin>>s;
    for(int i=0;s[i]!='\0';i++){
        if(s[i]=='A'&&s[i+1]=='C'){
            cout<<"Yes"<<endl;
            return 0;
        }
    }
    cout<<"No"<<endl;
	return 0;
}
```

---

## 作者：Error_502 (赞：3)

看到楼上daolao发的kmp，蒟蒻瑟瑟发抖～～～   

~~众所周知~~，C/C++自带库函数strstr()，用于判断字符串b是否包含于字符串a，用法为strstr(a,b)，所以这道题的代码就是非常~~简洁明了~~的

下面贴代码：
```cpp
#include <stdio.h>
#include <string.h>
//string.h 包含strstr()函数
int main()
{
	char a[6];
	scanf("%s",a);
	if(strstr(a,"AC")) printf("Yes\n");//判断是否包含
	else printf("No\n");
    return 0;//程序拜拜
}
```

---

## 作者：凑_友希那 (赞：1)

kmp裸题，话不多说，代码如下

[学习kmp](https://www.luogu.org/problemnew/show/P3375)

```cpp
#include <bits/stdc++.h>
using namespace std;

int kmp[1000010];
char s1[1000010], s2[1000010];

int main() {
    scanf("%s", s1 + 1);
    s2[1] = 'A';
    s2[2] = 'C';
    int len1 = strlen(s1 + 1);
    int len2 = strlen(s2 + 1);
    for(int i = 2; i <= len2; i++) {//匹配kmp数组
        int j = kmp[i - 1];
        while (j && s2[j + 1] != s2[i]) j = kmp[j];
        kmp[i] = j + (s2[j + 1] == s2[i]);
    }
    for(int i = 1, j = 0; i <= len1 + 1; i++) {
    //kmp匹配主过程
        if (j == len2){ printf("Yes\n"); return 0; }
        while (j && s2[j + 1] != s1[i]) j = kmp[j];
        j += (s2[j + 1] == s1[i]);
    }
    printf("No\n");
    return 0;
}
```

---

