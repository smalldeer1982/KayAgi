# Guess a number!

## 题目描述

A TV show called "Guess a number!" is gathering popularity. The whole Berland, the old and the young, are watching the show.

The rules are simple. The host thinks of an integer $ y $ and the participants guess it by asking questions to the host. There are four types of acceptable questions:

- Is it true that $ y $ is strictly larger than number $ x $ ?
- Is it true that $ y $ is strictly smaller than number $ x $ ?
- Is it true that $ y $ is larger than or equal to number $ x $ ?
- Is it true that $ y $ is smaller than or equal to number $ x $ ?

On each question the host answers truthfully, "yes" or "no".

Given the sequence of questions and answers, find any integer value of $ y $ that meets the criteria of all answers. If there isn't such value, print "Impossible".

## 样例 #1

### 输入

```
4
&gt;= 1 Y
&lt; 3 N
&lt;= -3 N
&gt; 55 N
```

### 输出

```
17
```

## 样例 #2

### 输入

```
2
&gt; 100 Y
&lt; -100 Y
```

### 输出

```
Impossible
```

# 题解

## 作者：CLCK (赞：2)

~~有点水，不过不告诉你我WA了5次~~

思路很简单，但逻辑一定要理清，尤其注意：当结果为 `N` 的时候对上下界的更新（要取反）。

其实就是根据输入在线更新取值的上界和下界了啦。

具体情况：

(1) 当 `Y` 时：

1. `>=` 更新下界

2. `>` 更新下界

3. `<=` 更新上界

4. `<` 更新上界

(2) 当 `N` 时：

1. `>=` 更新上界(等价于 `<`)

2. `>` 更新上界(等价于 `<=`)

3. `<=` 更新下界(等价于 `>`)

4. `<` 更新下界(等价于 `>=`)

好了，给一下代码：

```cpp
#include <iostream>
using namespace std;
int lb = -0x3f3f3f3f, ub = 0x3f3f3f3f; //注意这里为了考虑负数，初始值设为正（负）无穷
int n;
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s; int x; cin >> x; char c; cin >> c;
        //上面这句都是输入，压一下行
        if (s == ">=") {
            if (c == 'Y') {
                lb = max(lb, x); //(1)1
            } else {
                ub = min(ub, x - 1); //(2)1
            }
        }
        if (s == ">") {
            if (c == 'Y') {
                lb = max(lb, x + 1); //(1)2
            } else {
                ub = min(ub, x); //(2)2
            }
        }
        if (s == "<=") {
            if (c == 'Y') {
                ub = min(ub, x); //(1)3
            } else {
                lb = max(lb, x + 1); //(2)3
            }
        }
        if (s == "<") {
            if (c == 'Y') {
                ub = min(ub, x - 1); //(1)4
            } else {
                lb = max(lb, x); //(2)4
            }
        }
        //上面一段分别更新
    }
    if (lb <= ub) cout << lb << endl;
    else cout << "Impossible" << endl; //输出结果（记得还有Impossible的情况）
    return 0;
}
```

#### 完结撒花～

---

## 作者：江户川·萝卜 (赞：2)

## 题解 [CF416A 【Guess a number!】](https://www.luogu.com.cn/problem/CF416A)

[博客食用更佳](https://www.luogu.com.cn/blog/258085/solution-cf416a)

这道题只需要不断地根据输入更新x的上限和下限，最后判断就行了。
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n,y,low=-2e9,high=2e9;
  	            //下限   //上限
    string op;//存运算符
    char yn;//存Y/N
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>op>>y>>yn;
        if(yn=='Y'){
            if(op=="<") high=min(high,y-1);
            else if(op=="<=") high=min(high,y);
            else if(op==">") low=max(low,y+1);
            else if(op==">=") low=max(low,y);
        }
        else{
            if(op==">=") high=min(high,y-1);
            else if(op==">") high=min(high,y);
            else if(op=="<=") low=max(low,y+1);
            else if(op=="<") low=max(low,y);
        }
    }
    if(high-low+1>0) cout<<low;
    else cout<<"Impossible";
    return 0;
}
```


---

## 作者：CobaltChloride (赞：0)

```
#include<bits/stdc++.h>
using namespace std;
string s;
char c;
int n,i,p,l=-2000000001,r=2000000001;//初始值 
int min(int a,int b){
	return a>b?b:a;
}
int main(){
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>s>>p>>c;
		if(s==">"&&c=='Y'||s=="<="&&c=='N') l=max(l,p+1);//相当于>
		if(s=="<"&&c=='Y'||s==">="&&c=='N') r=min(r,p-1);//相当于<
		if(s==">="&&c=='Y'||s=="<"&&c=='N') l=max(l,p);//相当于>=
		if(s=="<="&&c=='Y'||s==">"&&c=='N') r=min(r,p);//相当于<= 
		//处理左右边界 
	}
	if(l<=r){
		if(l==-2000000001) cout<<r;
		else cout<<l;
		//注意不能输出初始值 
	}
	else cout<<"Impossible";//不可能 
	return 0;
}
```

---

## 作者：小水滴 (赞：0)

题目大意：猜一个数字，给出N个问题和回答，问题只有4种情况，分别是被猜数是否大于/小于/大于等于/小于等于一个给定的数。最后输出一个可能的解，如果没有可能的解输出"Impossible"。

分析：读入每个问题和回答后，都将回答转换为Yes，也就是说，将原来的大于等于变为小于，原来的小于等于变为大于，等等。然后再维护一个可能的区间，每次更新区间的左右边界。如果最后左边界大于右边界，那么输出"Impossible"（无解）；否则，输出左边界（输出一个解即可）。

参考代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int n,minn,maxx;
bool a1,a2;
int main()
{
    scanf("%d",&n);
    minn=-2*(1e+9);
    maxx=-minn;
    //左右区间赋值为无穷小和无穷大
    getchar();
    for(int i=1;i<=n;i++)
    {
        a1=0;a2=0;
        char _1=getchar(),_2=getchar();
        int a;char yon;
        scanf("%d %c\n",&a,&yon);
        if(_2=='=') a2=1;
        else a2=0;
        if(_1=='>') a1=1;
        else a1=0;
        if(yon=='N')
        {
            a1=!a1;
            a2=!a2;
        }
        //将结果转换为Yes
        if(a1)
        {
             if(a2) minn=max(minn,a);
             else minn=max(minn,a+1);
             //大于（等于）的情况，如果是没有等于号的，那么就要+1
        }
        else
        {
             if(a2) maxx=min(maxx,a);
             else maxx=min(maxx,a-1);
             //小于（等于）的情况，如果是没有等于号的，那么就要-1

        }
        //更新左右边界
    }
    if(minn>maxx) puts("Impossible");//无解
    else printf("%d\n",minn);
    return 0;
}
```

---

