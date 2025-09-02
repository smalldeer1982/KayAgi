# Accepted...?

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2017-beginner/tasks/tenka1_2017_a

すぬけ君はあるプログラミングコンテストのために、$ 6 $ 問の問題を用意しました。 りんごさんはすぬけ君の用意した各問題についてそれぞれ、プログラミングコンテストに採用するかどうかを決めました。

長さ $ 6 $ の文字列 $ S $ の $ i $ 文字目が `1` ならすぬけ君の用意した $ i $ 問目の問題が採用されたことを、`0` なら採用されなかったことを表します。

すぬけ君が用意した問題の中で、プログラミングコンテストに採用された問題は何問あるでしょうか。

## 说明/提示

### 制約

- $ S $ の長さは $ 6 $ である
- $ S $ は `0` と `1` のみからなる

### Sample Explanation 1

$ 1,2,3,4 $ 問目の合計 $ 4 $ 問が採用されました。

## 样例 #1

### 输入

```
111100```

### 输出

```
4```

## 样例 #2

### 输入

```
001001```

### 输出

```
2```

## 样例 #3

### 输入

```
000000```

### 输出

```
0```

# 题解

## 作者：sycqwq (赞：1)

大家都知道，求1的数量，就是求数列的和。

既然是求和，我们就可以用线段树来做（

代码：

```cpp
#include<bits/stdc++.h>
#define inf 2147283647
#define ll long long
using namespace std;
int sum[105],a[7];
void build(int l,int r,int rt)//建数
{
    if(l==r)
        {sum[rt]=a[l];return;}
    ll mid=(l+r)>>1;
    build(l,mid,rt<<1);//左子树
    build(mid+1,r,rt<<1|1);//右子树
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];//这个区间的和，当然等于左儿子加右儿子啦
}
int query(int l,int r,int rt,int i,int j)//区间求和
{
    if(l>=i&&r<=j)//这个在范围内
        return sum[rt];
    ll mid=(l+r)>>1;
    ll ans=0;
    if(i<=mid)ans+=query(l,mid,rt<<1,i,j);//在范围内，加左子树
    if(mid<j)ans+=query(mid+1,r,rt<<1|1,i,j);//加右子树
    return ans;
}
int read(){//快读
    int s=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=s*10+ch-'0';
        ch=getchar();
    }
    return s*f;
}
int main(){
    char c;
    for(int i=1;i<=6;i++)
        cin>>c,a[i]=c-'0';
    build(1,6,1);//建树
    cout<<query(1,6,1,1,6);//求和
    return 0;
}
```

是不是很简单呀！

---

## 作者：风人 (赞：0)



## Python代码如下
```python
a=input()
print(a.count("1"))
    
```
（当然你也可以把第二行a改成input（），写成一行。)

### 在代码中，我使用了count方法，在这里作以讲解：

用于统计字符串里某个字符出现的次数。可选参数为在字符串搜索的开始与结束位置。


使用模板：

```str.count(sub, start= 0,end=len(string))```


sub -- 搜索的子字符串。

start -- 字符串开始搜索的位置。默认为第一个字符,第一个字符索引值为0。

end -- 字符串中结束搜索的位置。字符中第一个字符的索引为 0。默认为字符串的最后一个位置。

其中start 和 end是可选参数，就像我并没有使用这两个参数。

~~我又水了一篇~~

---

## 作者：Aw顿顿 (赞：0)

这道题和CSP2019普及组的第一题是基本一样的。

首先，这个字符串只有 $6$ 位，而且只有 $1$ 和 $0$ 组成，那么我们会想到 $9$ 的余数特性，即除以 $9$ 的余数就是当中数码和除以 $9$ 的余数，此字符串各位数码和最大值只能为 $6$ ,且不会超过int类型，所以我们可以很容易写出以下程序：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a;
	cin>>a;
	cout<<a%9<<endl;
	return 0;
}
```

同时，附上一般方法，即遍历的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
short cnt;
int main()
{
    cin>>a;
    for(int i=0;i<6;i++)if(s[i]=='1')cnt++;
    cout<<cnt<<endl;
    return 0;
}
```

谢谢大家！

---

## 作者：xyn0901 (赞：0)

这题水到爆啊

题意上面的大佬已经讲过了

判断一即可
```pascal
var s:string;
i,max:integer;
begin
read(s);
max:=0;
for i:=1 to 6 do if 
ord(s[i])=49 then max:=max+1;
writeln(max);
end.
```

---

## 作者：RioBlu (赞：0)

~~这题马上就没了赶紧发个题解~~

直接判断字符串里有几个1
```
#include<iostream>
#include<iomanip>
using namespace std;
string a;
int b;
int main()
{
    cin>>a;
    for(int s=0;s<6;s++)
    if(a[s]=='1')b++;
    cout<<b<<endl;
    return 0;
}
```

---

## 作者：lzj666 (赞：0)

题目解释：输入一个长度为6的字符串，其中只含0和1，输出1的个数
```cpp
#include<bits/stdc++.h>  //万能头文件
using namespace std;
int main()
{
    int i,a=0;
    char s[7];
    gets(s);  //输入字符串
    for(i=0;i<=6;i++)
        if(s[i]=='1')  //字符串查找有多少个1
            a++;
    cout<<a;  //输出1的个数
    return 0;  //返回
}
```

---

