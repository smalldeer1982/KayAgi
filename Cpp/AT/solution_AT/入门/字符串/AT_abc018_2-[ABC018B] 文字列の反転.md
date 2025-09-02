# [ABC018B] 文字列の反転

## 题目描述

给定一个只包含半角小写英文字母的字符串 $S$。对字符串 $S$ 依次进行编号从 $1$ 到 $N$ 的以下操作。

- 操作 $i$：将从左起第 $l_i$ 个字符作为左端点，从左起第 $r_i$ 个字符作为右端点的子串进行反转（$1 \leq l_i < r_i \leq |S|$）。

例如，对于字符串 `abcdef`，将从左起第 $3$ 个字符 `c` 到第 $5$ 个字符 `e` 的子串反转后，得到字符串 `abedcf`。

请输出依次进行操作 $1$ 到操作 $N$ 后得到的字符串。

## 说明/提示

### 样例解释 1

- 操作 $1$ 后，字符串变为 `abedcf`。
- 操作 $2$ 后，字符串变为 `debacf`。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
abcdef
2
3 5
1 4```

### 输出

```
debacf```

## 样例 #2

### 输入

```
redcoat
3
1 7
1 2
3 4```

### 输出

```
atcoder```

# 题解

## 作者：da32s1da (赞：4)

c++自带字符串翻转函数。
```
#include<cstdio>
#include<algorithm>
using namespace std;
char s[105];
int n,p,q;
int main(){
	scanf("%s%d",s,&n);
	for(int i=0;i^n;i++)
	scanf("%d%d",&p,&q),reverse(s+p-1,s+q);//读入操作并翻转
	puts(s);//自带回车
    return 0;
}
```

---

## 作者：Soyilieber (赞：2)

字符串操作


pascal代码如下：
```pascal
var
    a,b,i,j,n:longint;
    s,s2:string;
begin
    readln(s);
    readln(n);
    for i:=1 to n do
        begin
            readln(a,b);
            s2:=copy(s,a,b-a+1);//复制要转的部分
            for j:=1 to b-a+1 do s[b-j+1]:=s2[j];//反转，这里就是核心
        end;
    writeln(s);
end.
```

---

