# ダブル文字列

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2015-qualb/tasks/codefestival_2015_qualB_a

今日の日付は `2015/10/25` です。

この日付を文字列としてみたとき、文字列に含まれる全ての文字（`2`,`0`,`1`,`5`,`/`）がちょうど $ 2 $ 回ずつ現れています。

このように文字列に含まれる全ての文字がちょうど $ 2 $ 回ずつ現れる文字列を「ダブル文字列」と呼ぶことにします。

あなたは小文字アルファベットのみからなる文字列 $ S $ を与えられるので、$ S $ に含まれる文字を全て含むようなダブル文字列を $ 1 $ つ出力してください。

出力する文字列には $ S $ に含まれない文字が含まれていても良いですが、小文字アルファベット以外の文字が含まれてはいけません。

## 说明/提示

### Sample Explanation 1

`onno`、`onon`、`oonn`、`lemonmelon` などの文字列も正解となります。

## 样例 #1

### 输入

```
on```

### 输出

```
noon```

## 样例 #2

### 输入

```
meat```

### 输出

```
teammate```

# 题解

## 作者：da32s1da (赞：5)

将字符串输入后**输出两遍**即可
```
#include<cstdio>
char s[50];
int main(){
    scanf("%s",s);
    printf("%s",s);puts(s);
}
```

---

## 作者：无颜ing (赞：5)

同志们，对于这道放在队列题库中的题，我们肯定要用队列来做！所以，这是一份简单的伪队列代码。
时间其实是多了的，O（n*n），但是这道题不会爆.所以可以说这道题简单到不行。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	string tack; //构造队列
	cin>>tack;//读入
	int head=0,cnt=0; //队首和计数
	while(cnt<2){//打印两遍
		head=0;//队首初始化
	while(head<tack.size()){//在队列未溢出之前
			cout<<tack[head];//打印数字
			head++;//出队
		}
		cnt++;//计数
	}
	return 0;//水水的结束
}

```

---

